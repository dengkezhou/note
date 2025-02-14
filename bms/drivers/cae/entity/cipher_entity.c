#include <cae.h>

/* configuration switches. */
#include "c_da_pec.h"

#include "da_pec_internal.h"
#include "api_pec.h"
#include "api_pec_sg.h"
#include "api_dmabuf.h"
#include "log.h"
#include "clib.h"
#include "sa_builder.h"
#include "sa_builder_basic.h"
#include "token_builder.h"

extern DMABuf_Status_t
DMABuf_Alloc(cae_device *dev, const DMABuf_Properties_t RequestedProperties,
	     DMABuf_HostAddress_t *const Buffer_p,
	     DMABuf_Handle_t *const Handle_p);
extern DMABuf_Status_t DMABuf_Release(cae_device *dev, DMABuf_Handle_t Handle);
extern PEC_Status_t PEC_Packet_Put(cae_device *dev,
				   const unsigned int InterfaceId,
				   const PEC_CommandDescriptor_t *Commands_p,
				   const unsigned int CommandsCount,
				   unsigned int *const PutCount_p);
extern PEC_Status_t PEC_SA_Register(cae_device *dev,
				    const unsigned int InterfaceId,
				    DMABuf_Handle_t SA_Handle1,
				    DMABuf_Handle_t SA_Handle2,
				    DMABuf_Handle_t SA_Handle3);
extern PEC_Status_t PEC_SA_UnRegister(cae_device *dev,
				      const unsigned int InterfaceId,
				      DMABuf_Handle_t SA_Handle1,
				      DMABuf_Handle_t SA_Handle2,
				      DMABuf_Handle_t SA_Handle3);
extern unsigned int
da_pec_pe_get_one(cae_device *dev, IOToken_Output_Dscr_t *const OutTokenDscr_p,
		  uint32_t *OutTokenData_p, PEC_ResultDescriptor_t *RD_p);
extern unsigned int cipher_confirm_sabuilder_params(cipher_ctx *ctx,
						    SABuilder_Params_t *params);
extern unsigned int
cipher_confirm_aad_params(cipher_ctx *ctx, TokenBuilder_Params_t *Tokenparams);
extern PEC_Status_t PEC_ResultNotify_Request(cae_device *dev,
					     const unsigned int InterfaceId,
					     PEC_NotifyFunction_t CBFunc_p,
					     void *args,
					     const unsigned int ResultsCount);

int calculate_cipher(cipher_ctx *ctx, unsigned char *out, int *out_len,
		     const unsigned char *in, int in_len);
int calculate_cipher_nonblock(cipher_ctx *ctx, const unsigned char *in,
			      int in_len);

void cipher_callback(void *args)
{
	cipher_ctx *ctx = (cipher_ctx *)args;
	cae_device *dev = ctx->dev;

	ZEROINIT(ctx->OutTokenDscr);

	if (ctx->blocked == 1) {
		if (da_pec_pe_get_one(dev, &ctx->OutTokenDscr, ctx->OutputToken,
				      &ctx->cipher_res) == 0) {
			LOG_CRIT("DA_PEC: error from da_pec_pe_get_one\n");
			ctx->rdr_done = -1;
		} else {
			ctx->rdr_done = 1;
		}
	} else {
		if (ctx->final_pkt == 1) {
			if (da_pec_pe_get_one(dev, &ctx->OutTokenDscr, ctx->OutputToken,
					      &ctx->cipher_res) == 0) {
				LOG_CRIT(
					"DA_PEC: error from da_pec_pe_get_one\n");
				ctx->rdr_done = -1;
			} else {
				ctx->rdr_done = 1;
			}
		} else if (ctx->left_update_blks > 0) {
			if (da_pec_pe_get_one(dev, &ctx->OutTokenDscr, ctx->OutputToken,
					      &ctx->cipher_res) == 0) {
				LOG_CRIT(
					"DA_PEC: error from da_pec_pe_get_one\n");
			} else {
				memcpy(ctx->out + *ctx->out_len,
				       ctx->OutPktHostAddress.p,
				       ctx->cipher_res.DstPkt_ByteCount);
				*ctx->out_len +=
					ctx->cipher_res.DstPkt_ByteCount;
			}
			ctx->left_update_blks--;
			calculate_cipher_nonblock(ctx, ctx->in + ctx->in_seek,
						  ctx->blk_size);
		} else if (ctx->left_update_blks == 0) {
			if (da_pec_pe_get_one(dev, &ctx->OutTokenDscr, ctx->OutputToken,
					      &ctx->cipher_res) == 0) {
				LOG_CRIT(
					"DA_PEC: error from da_pec_pe_get_one\n");
				ctx->rdr_done = -1;
			} else {
				memcpy(ctx->out + *ctx->out_len,
				       ctx->OutPktHostAddress.p,
				       ctx->cipher_res.DstPkt_ByteCount);
				*ctx->out_len +=
					ctx->cipher_res.DstPkt_ByteCount;
				ctx->rdr_done = 1;
			}
		}
	}
}

int cipher_env_alloc(cipher_ctx *ctx)
{
	int ret = 0;
	unsigned int SAWords = 0;
	unsigned int TCRWords = 0;
	unsigned int TokenMaxWords = 0;
	DMABuf_Status_t DMAStatus;
	DMABuf_Properties_t DMAProperties;
	cae_device *dev = ctx->dev;

	memset(&DMAProperties, 0, sizeof(DMAProperties));
	ret = SABuilder_Init_Basic(&ctx->params, &ctx->ProtocolParams,
				   ctx->enc);
	if (ret != 0) {
		LOG_CRIT("SABuilder_Init_Basic failed\n");
		goto error_exit;
	}
	//ctx->ProtocolParams.
	//ctx->ProtocolParams.ICVByteCount  =16;
	ret = cipher_confirm_sabuilder_params(ctx, &ctx->params);
	if (ret != 0) {
		LOG_CRIT("sa builder ctx->params error!\n");
		goto error_exit;
	}

	ret = SABuilder_GetSizes(ctx, &ctx->params, &SAWords, NULL, NULL);
	if (ret != 0) {
		LOG_CRIT("SA not created because of errors\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_SA;
	DMAProperties.Size = MAX(4 * SAWords, DA_PEC_MIN_SA_BYTE_COUNT);
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->SAHostAddress,
				 &ctx->SAHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		ret = 1;
		LOG_CRIT("Allocation of SA failed\n");
		goto error_exit;
	}

	ret = SABuilder_BuildSA(ctx, &ctx->params,
				(uint32_t *)ctx->SAHostAddress.p, NULL, NULL);
	if (ret != 0) {
		LOG_CRIT("SA not created because of errors\n");
		goto error_exit;
	}

	ret = TokenBuilder_GetContextSize(&ctx->params, &TCRWords);
	if (ret != 0) {
		LOG_CRIT("TokenBuilder_GetContextSize returned errors\n");
		goto error_exit;
	}

	/* The Token Context Record does not need to be allocated in a DMA-safe buffer. */
	ctx->TCRData = da_pec_malloc(4 * TCRWords);
	if (!ctx->TCRData) {
		ret = 1;
		LOG_CRIT("Allocation of TCR failed\n");
		goto error_exit;
	}

	ret = TokenBuilder_BuildContext(&ctx->params, ctx->TCRData);
	if (ret != 0) {
		LOG_CRIT("TokenBuilder_BuildContext failed\n");
		goto error_exit;
	}

	ret = TokenBuilder_GetSize(ctx->TCRData, &TokenMaxWords);
	if (ret != 0) {
		LOG_CRIT("TokenBuilder_GetSize failed\n");
		goto error_exit;
	}

	/* Allocate one buffer for the token and two packet buffers. */
	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_TOKEN;
	DMAProperties.Size = 4 * TokenMaxWords;
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->TokenHostAddress,
				 &ctx->TokenHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		ret = 1;
		LOG_CRIT("Allocation of token buffer failed.\n");
		goto error_exit;
	}

	/* Register the SA. */
	ret = PEC_SA_Register(dev, INTERFACE_ID, ctx->SAHandle,
			      DMABuf_NULLHandle, DMABuf_NULLHandle);
	if (ret != PEC_STATUS_OK) {
		LOG_CRIT("PEC_SA_Register failed\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_PACKET;
	DMAProperties.Size = ctx->blk_size;
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->InPktHostAddress,
				 &ctx->InPktHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		ret = 1;
		LOG_CRIT("Allocation of source packet buffer failed.\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_PACKET;
	/* for pkcs7 the last packet, output may be more than one block and reaching to 2 blocks. */
	DMAProperties.Size = ctx->blk_size * 2;
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->OutPktHostAddress,
				 &ctx->OutPktHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		ret = 1;
		LOG_CRIT("Allocation of source packet buffer failed.\n");
		goto error_exit;
	}

	PEC_ResultNotify_Request(dev, INTERFACE_ID, cipher_callback, ctx, 1);
	return 1;
error_exit:
	DMABuf_Release(dev, ctx->SAHandle);
	DMABuf_Release(dev, ctx->TokenHandle);
	if (ctx->TCRData != NULL)
		da_pec_free(ctx->TCRData);

	return ret == 0;
}

int calculate_cipher_nonblock(cipher_ctx *ctx, const unsigned char *in,
			      int in_len)
{
	int ret = 0;
	unsigned int count;
	cae_device *dev = ctx->dev;

	if (ctx->remain_len > 0) {
		memcpy(ctx->InPktHostAddress.p, ctx->remain, ctx->remain_len);
		memcpy(ctx->InPktHostAddress.p + ctx->remain_len, in,
		       ctx->blk_size - ctx->remain_len);
		ctx->in_seek += ctx->blk_size - ctx->remain_len;
	} else if (ctx->remain_len == 0) {
		memcpy(ctx->InPktHostAddress.p, in, ctx->blk_size);
		ctx->in_seek += ctx->blk_size;
	}
	ctx->remain_len = 0;

	ZEROINIT(ctx->InTokenDscr);
	ZEROINIT(ctx->Cmd);
	/* Set Token Parameters if specified in test vector. */
	ZEROINIT(ctx->TokenParams);

	//TokenParams.PacketFlags = 0;
	//TokenParams.PadByte = 0x01;
	//TokenParams.BypassByteCount = 0;
	//TokenParams.IV_p = ctx->iv;
	//TokenParams.AdditionalValue = 0;
	//cipher_confirm_aad_params(ctx, &TokenParams);

	/* Prepare a token to process the packet. */
	ret = TokenBuilder_BuildToken(ctx, ctx->TCRData,
				      (uint8_t *)ctx->InPktHostAddress.p,
				      ctx->blk_size, &ctx->TokenParams,
				      (uint32_t *)ctx->TokenHostAddress.p,
				      &ctx->TokenWords, &ctx->TokenHeaderWord);
	if (ret != TKB_STATUS_OK) {
		if (ret == TKB_BAD_PACKET) {
			LOG_CRIT(
				"Token not created because packet size is invalid\n");
		} else {
			LOG_CRIT("Token builder failed\n");
		}
		goto error_exit_unregister;
	}

	ctx->Cmd.User_p = 0;
	ctx->Cmd.Token_Handle = ctx->TokenHandle;
	ctx->Cmd.Token_WordCount = ctx->TokenWords;
	ctx->Cmd.SrcPkt_Handle = ctx->InPktHandle;
	ctx->Cmd.SrcPkt_ByteCount = ctx->blk_size;
	ctx->Cmd.DstPkt_Handle = ctx->OutPktHandle;
	ctx->Cmd.Bypass_WordCount = 0;
	ctx->Cmd.SA_Handle1 = ctx->SAHandle;
	ctx->Cmd.SA_Handle2 = DMABuf_NULLHandle;
	ctx->Cmd.SA_WordCount = 128;

	ctx->InTokenDscr.TknHdrWordInit = ctx->TokenHeaderWord;
	if (!da_pec_iotoken_create(&ctx->InTokenDscr, NULL, ctx->InputToken,
				   &ctx->Cmd)) {
		ret = 1;
		goto error_exit_unregister;
	}
	ret = PEC_Packet_Put(dev, INTERFACE_ID, &ctx->Cmd, 1, &count);
	if (ret != PEC_STATUS_OK && count != 1) {
		LOG_CRIT("calculate_cipher_nonblock PEC_Packet_Put error\n");
		ret = 1;
		goto error_exit_unregister;
	}
	return 1;
error_exit_unregister:
	return ret == 0;
}

int calculate_cipher(cipher_ctx *ctx, unsigned char *out, int *out_len,
		     const unsigned char *in, int in_len)
{
	int ret = 0;
	unsigned int count;
	int pkthostaddress_cnt = 0, blk_cnt = 0;
	int block = in_len / ctx->blk_size;
	cae_device *dev = ctx->dev;

	*out_len = 0;

	if (ctx->remain_len > 0) {
		memcpy(ctx->InPktHostAddress.p, ctx->remain, ctx->remain_len);
		pkthostaddress_cnt = ctx->remain_len;
		memcpy(ctx->InPktHostAddress.p + ctx->remain_len, in,
		       ctx->blk_size - pkthostaddress_cnt);
	} else if (ctx->remain_len == 0) {
		memcpy(ctx->InPktHostAddress.p, in, ctx->blk_size);
	}

	if (block == 0)
		block = 1;

	while (block--) {
		ZEROINIT(ctx->InTokenDscr);
		ZEROINIT(ctx->Cmd);
		/* Set Token Parameters if specified in test vector. */
		ZEROINIT(ctx->TokenParams);

		//TokenParams.PacketFlags = 0;
		//TokenParams.PadByte = 0x01;
		//TokenParams.BypassByteCount = 0;
		//TokenParams.IV_p = ctx->iv;
		//TokenParams.AdditionalValue = 0;
		//cipher_confirm_aad_params(ctx, &TokenParams);

		/* Copy input packet into source packet buffer. */
		if (blk_cnt >= 1) {
			memcpy(ctx->InPktHostAddress.p,
			       (in + ctx->blk_size - pkthostaddress_cnt) +
				       (blk_cnt - 1) * ctx->blk_size,
			       ctx->blk_size);
		}
		blk_cnt++;

		/* Prepare a token to process the packet. */
		ret = TokenBuilder_BuildToken(
			ctx, ctx->TCRData, (uint8_t *)ctx->InPktHostAddress.p,
			ctx->blk_size, &ctx->TokenParams,
			(uint32_t *)ctx->TokenHostAddress.p, &ctx->TokenWords,
			&ctx->TokenHeaderWord);
		if (ret != TKB_STATUS_OK) {
			if (ret == TKB_BAD_PACKET) {
				LOG_CRIT(
					"Token not created because packet size is invalid\n");
			} else {
				LOG_CRIT("Token builder failed\n");
			}
			goto error_exit_unregister;
		}

		ctx->Cmd.User_p = 0;
		ctx->Cmd.Token_Handle = ctx->TokenHandle;
		ctx->Cmd.Token_WordCount = ctx->TokenWords;
		ctx->Cmd.SrcPkt_Handle = ctx->InPktHandle;
		ctx->Cmd.SrcPkt_ByteCount = ctx->blk_size;
		ctx->Cmd.DstPkt_Handle = ctx->OutPktHandle;
		ctx->Cmd.Bypass_WordCount = 0;
		ctx->Cmd.SA_Handle1 = ctx->SAHandle;
		ctx->Cmd.SA_Handle2 = DMABuf_NULLHandle;
		ctx->Cmd.SA_WordCount = 128;

		ctx->InTokenDscr.TknHdrWordInit = ctx->TokenHeaderWord;
		if (!da_pec_iotoken_create(&ctx->InTokenDscr, NULL,
					   ctx->InputToken, &ctx->Cmd)) {
			ret = 1;
			goto error_exit_unregister;
		}

		ret = PEC_Packet_Put(dev, INTERFACE_ID, &ctx->Cmd, 1, &count);
		if (ret != PEC_STATUS_OK && count != 1) {
			ret = 1;
			LOG_CRIT("calculate_cipher PEC_Packet_Put error\n");
			goto error_exit_unregister;
		}

		while (1) {
			if (ctx->rdr_done == 1) {
				ctx->rdr_done = 0;
				break;
			} else if (ctx->rdr_done == -1) {
				ret = 1;
				ctx->rdr_done = 0;
				goto error_exit_unregister;
			}
		}
		memcpy(out + *out_len, ctx->OutPktHostAddress.p,
		       ctx->cipher_res.DstPkt_ByteCount);
		*out_len += ctx->cipher_res.DstPkt_ByteCount;
	}
	return 1;
error_exit_unregister:
	return ret == 0;
}

int calculate_final_cipher(cipher_ctx *ctx, unsigned char *out, int *out_len,
			   const unsigned char *in, int in_len)
{
	int ret = 0;
	unsigned int count;
	unsigned int pad_len = 0;
	int i = 0;
	cae_device *dev = ctx->dev;

	*out_len = 0;

	ZEROINIT(ctx->InTokenDscr);
	ZEROINIT(ctx->Cmd);
	/* Set Token Parameters if specified in test vector. */
	ZEROINIT(ctx->TokenParams);

	//ctx->TokenParams.PacketFlags = 0;
	//ctx->TokenParams.PadByte = 0x08;
	//ctx->TokenParams.BypassByteCount = 8;
	//ctx->TokenParams.IV_p = NULL;
	// ctx->TokenParams.AdditionalValue = 0;
	//cipher_confirm_aad_params(ctx, &ctx->TokenParams);

	/* Copy input packet into source packet buffer. */
	memcpy(ctx->InPktHostAddress.p, ctx->remain, in_len);

	/* Prepare a token to process the packet. */
	ret = TokenBuilder_BuildToken(ctx, ctx->TCRData,
				      (uint8_t *)ctx->InPktHostAddress.p,
				      in_len, &ctx->TokenParams,
				      (uint32_t *)ctx->TokenHostAddress.p,
				      &ctx->TokenWords, &ctx->TokenHeaderWord);
	if (ret != TKB_STATUS_OK) {
		if (ret == TKB_BAD_PACKET) {
			LOG_CRIT(
				"Token not created because packet size is invalid\n");
		} else {
			LOG_CRIT("Token builder failed\n");
		}
		goto error_exit_unregister;
	}

	ctx->Cmd.User_p = 0;
	ctx->Cmd.Token_Handle = ctx->TokenHandle;
	ctx->Cmd.Token_WordCount = ctx->TokenWords;
	ctx->Cmd.SrcPkt_Handle = ctx->InPktHandle;
	ctx->Cmd.SrcPkt_ByteCount = in_len;
	ctx->Cmd.DstPkt_Handle = ctx->OutPktHandle;
	ctx->Cmd.Bypass_WordCount = 0;
	ctx->Cmd.SA_Handle1 = ctx->SAHandle;
	ctx->Cmd.SA_Handle2 = DMABuf_NULLHandle;
	ctx->Cmd.SA_WordCount = 128;
	ctx->InTokenDscr.TknHdrWordInit = ctx->TokenHeaderWord;
	if (!da_pec_iotoken_create(&ctx->InTokenDscr, NULL, ctx->InputToken, &ctx->Cmd)) {
		ret = 1;
		goto error_exit_unregister;
	}

	ret = PEC_Packet_Put(dev, INTERFACE_ID, &ctx->Cmd, 1, &count);
	if (ret != PEC_STATUS_OK && count != 1) {
		ret = 1;
		LOG_CRIT("calculate_final_cipher PEC_Packet_Put error\n");
		goto error_exit_unregister;
	}

	while (1) {
		if (ctx->rdr_done == 1) {
			ctx->rdr_done = 0;
			break;
		} else if (ctx->rdr_done == -1) {
			ret = 1;
			ctx->rdr_done = 0;
			goto error_exit_unregister;
		}
	}

	if (ctx->enc == SAB_DIRECTION_INBOUND) {
		if (ctx->pad == PADDING_PKCS7) {
			pad_len = *((unsigned char *)ctx->OutPktHostAddress.p +
				    ctx->cipher_res.DstPkt_ByteCount - 1);
			memcpy(out, ctx->OutPktHostAddress.p,
			       ctx->blk_size - pad_len);
			*out_len = ctx->blk_size - pad_len;
		} else if (ctx->pad == PADDING_ZERO) {
			for (i = ctx->blk_size - 1; i >= 0; i--) {
				if (*((unsigned char *)ctx->OutPktHostAddress.p +
				      i) == 0)
					continue;
				else
					break;
			}
			if (i < 0)
				pad_len = ctx->blk_size;
			else
				pad_len = ctx->blk_size - 1 - i;
			memcpy(out, ctx->OutPktHostAddress.p,
			       ctx->blk_size - pad_len);
			*out_len = ctx->blk_size - pad_len;
		}
	} else {
		memcpy(out, ctx->OutPktHostAddress.p,
		       ctx->cipher_res.DstPkt_ByteCount);
		*out_len = ctx->cipher_res.DstPkt_ByteCount;
	}
	return 1;
error_exit_unregister:
	return ret == 0;
}

void cipher_env_free(cipher_ctx *ctx)
{
	cae_device *dev = ctx->dev;

	DMABuf_Release(dev, ctx->InPktHandle);
	DMABuf_Release(dev, ctx->OutPktHandle);
	if (ctx->TCRData != NULL)
		da_pec_free(ctx->TCRData);
	PEC_SA_UnRegister(dev, INTERFACE_ID, ctx->SAHandle, DMABuf_NULLHandle,
			  DMABuf_NULLHandle);

	DMABuf_Release(dev, ctx->SAHandle);
	DMABuf_Release(dev, ctx->TokenHandle);
}
