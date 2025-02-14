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
extern unsigned int
digest_confirm_sabuilder_params(md_ctx *ctx, SABuilder_Params_t *params,
				SABuilder_Params_Basic_t *basic_params,
				uint8_t *InnerDigest, uint8_t *OuterDigest);
extern PEC_Status_t PEC_ResultNotify_Request(cae_device *dev,
					     const unsigned int InterfaceId,
					     PEC_NotifyFunction_t CBFunc_p,
					     void *args,
					     const unsigned int ResultsCount);

bool calculate_digest_nonblock(md_ctx *ctx, const void *in, unsigned long len);

void digest_callback(void *args)
{
	uint32_t OutputToken[IOTOKEN_OUT_WORD_COUNT];
	IOToken_Output_Dscr_t OutTokenDscr;
	md_ctx *ctx = (md_ctx *)args;
	cae_device *dev = ctx->dev;

	ZEROINIT(OutTokenDscr);

	if (ctx->blocked == 1) {
		if (da_pec_pe_get_one(dev, &OutTokenDscr, OutputToken,
				      &ctx->hash_res) < 1) {
			LOG_CRIT("DA_PEC: error from da_pec_pe_get_one\n");
			ctx->rdr_done = -1;
		} else {
			ctx->rdr_done = 1;
		}
	} else {
		if (ctx->hash_final_pkt == 1) {
			if (da_pec_pe_get_one(dev, &OutTokenDscr, OutputToken,
					      &ctx->hash_res) < 1) {
				LOG_CRIT(
					"DA_PEC: error from da_pec_pe_get_one\n");
				ctx->rdr_done = -1;
			} else {
				ctx->rdr_done = 1;
			}
		} else if (ctx->left_update_blks > 0) {
			if (da_pec_pe_get_one(dev, &OutTokenDscr, OutputToken,
					      &ctx->hash_res) < 1)
				LOG_CRIT(
					"DA_PEC: error from da_pec_pe_get_one\n");

			ctx->left_update_blks--;
			calculate_digest_nonblock(ctx, ctx->in + ctx->in_seek,
						  ctx->blk_size);
		} else if (ctx->left_update_blks == 0) {
			if (da_pec_pe_get_one(dev, &OutTokenDscr, OutputToken,
					      &ctx->hash_res) < 1) {
				LOG_CRIT(
					"DA_PEC: error from da_pec_pe_get_one\n");
				ctx->rdr_done = -1;
			} else {
				ctx->rdr_done = 1;
			}
		}
	}
}

bool digest_env_alloc(md_ctx *ctx)
{
	int rc;
	unsigned int SAWords = 0;
	unsigned int TCRWords = 0;
	unsigned int TokenMaxWords = 0;
	DMABuf_Status_t DMAStatus;
	DMABuf_Properties_t DMAProperties;
	cae_device *dev = ctx->dev;

	memset(&DMAProperties, 0, sizeof(DMAProperties));
	rc = SABuilder_Init_Basic(&ctx->params, &ctx->BasicParams,
				  SAB_DIRECTION_OUTBOUND);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: SABuilder_Init_Basic failed\n");
		goto error_exit;
	}
	rc = digest_confirm_sabuilder_params(ctx, &ctx->params,
					     &ctx->BasicParams,
					     ctx->InnerDigest,
					     ctx->OuterDigest);
	if (rc != 0) {
		LOG_CRIT("sa builder ctx->params error!\n");
		goto error_exit;
	}
	rc = SABuilder_GetSizes(ctx, &ctx->params, &SAWords, NULL, NULL);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: SA not created because of errors\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_SA;
	DMAProperties.Size = MAX(SAWords * 4, DA_PEC_MIN_SA_BYTE_COUNT);
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->SAHostAddress,
				 &ctx->SAHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of SA failed\n");
		goto error_exit;
	}
	rc = SABuilder_BuildSA(ctx, &ctx->params,
			       (uint32_t *)ctx->SAHostAddress.p, NULL, NULL);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: SA not created because of errors\n");
		goto error_exit;
	}

	rc = TokenBuilder_GetContextSize(&ctx->params, &TCRWords);
	if (rc != 0) {
		LOG_CRIT(
			"DA_PEC: TokenBuilder_GetContextSize returned errors\n");
		goto error_exit;
	}
	/* The Token Context Record does not need to be allocated in a DMA-safe buffer. */
	ctx->TCRData = da_pec_malloc(4 * TCRWords);
	if (!ctx->TCRData) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of TCR failed\n");
		goto error_exit;
	}
	rc = TokenBuilder_BuildContext(&ctx->params, ctx->TCRData);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: TokenBuilder_BuildContext failed\n");
		goto error_exit;
	}
	rc = TokenBuilder_GetSize(ctx->TCRData, &TokenMaxWords);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: TokenBuilder_GetSize failed\n");
		goto error_exit;
	}

	/* Allocate one buffer for the token and two packet buffers. */
	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_TOKEN;
	DMAProperties.Size = TokenMaxWords * sizeof(uint32_t);
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->TokenHostAddress,
				 &ctx->TokenHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of token buffer failed.\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_PACKET;
	DMAProperties.Size = ctx->blk_size;
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->InPktHostAddress,
				 &ctx->InPktHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT(
			"DA_PEC: Allocation of source packet buffer failed.\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_PACKET;
	DMAProperties.Size = ctx->blk_size;
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &ctx->OutPktHostAddress,
				 &ctx->OutPktHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of packet buffer failed.\n");
		goto error_exit;
	}

	/* Register the SA. */
	rc = PEC_SA_Register(dev, INTERFACE_ID, ctx->SAHandle,
			     DMABuf_NULLHandle, DMABuf_NULLHandle);
	if (rc != PEC_STATUS_OK) {
		LOG_CRIT("DA_PEC: PEC_SA_Register failed\n");
		goto error_exit;
	}
	if (ctx->first_pkt) {
		if (!ctx->multi_part_packet_flag)
			PEC_ResultNotify_Request(dev, INTERFACE_ID,
						 digest_callback, ctx, 1);
	}
	return 1;
error_exit:
	DMABuf_Release(dev, ctx->SAHandle);
	DMABuf_Release(dev, ctx->TokenHandle);
	DMABuf_Release(dev, ctx->OutPktHandle);
	DMABuf_Release(dev, ctx->InPktHandle);
	if (ctx->TCRData != NULL)
		da_pec_free(ctx->TCRData);
	return rc == 0;
}

bool calculate_digest_nonblock(md_ctx *ctx, const void *in, unsigned long len)
{
	int ret = 0;
	unsigned int count;
	cae_device *dev = ctx->dev;

	if (ctx->first_pkt)
		PEC_ResultNotify_Request(dev, INTERFACE_ID, digest_callback,
					 ctx, 1);

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

	if (ctx->first_pkt) {
		ctx->TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFIRST;
		ctx->first_pkt = 0;
	}
	ctx->TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHAPPEND;

	/* Prepare a token to process the data. */
	ret = TokenBuilder_BuildToken(ctx, ctx->TCRData,
				      (uint8_t *)ctx->InPktHostAddress.p,
				      ctx->blk_size, &ctx->TokenParams,
				      (uint32_t *)ctx->TokenHostAddress.p,
				      &ctx->TokenWords, &ctx->TokenHeaderWord);
	if (ret != TKB_STATUS_OK) {
		if (ret == TKB_BAD_PACKET) {
			LOG_CRIT(
				"DA_PEC: Token not created because packet size is invalid\n");
		} else {
			LOG_CRIT("DA_PEC: Token builder failed\n");
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
#ifndef DA_PEC_USE_INVALIDATE_COMMANDS
	ctx->Cmd.Control1 = ctx->TokenHeaderWord;
	ctx->Cmd.Control2 = 0;
#endif
#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
	defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
	InTokenDscrExt.HW_Services = FIRMWARE_EIP207_CMD_PKT_LAC;
#endif
	ctx->InTokenDscr.TknHdrWordInit = ctx->TokenHeaderWord;
	if (!da_pec_iotoken_create(&ctx->InTokenDscr, NULL, ctx->InputToken,
				   &ctx->Cmd)) {
		ret = 1;
		goto error_exit_unregister;
	}
	ret = PEC_Packet_Put(dev, INTERFACE_ID, &ctx->Cmd, 1, &count);
	if (ret != PEC_STATUS_OK && count != 1) {
		ret = 1;
		LOG_CRIT("calculate_digest PEC_Packet_Put error\n");
		goto error_exit_unregister;
	}
error_exit_unregister:
	return ret == 0;
}

bool calculate_digest(md_ctx *ctx, const void *in, unsigned long len)
{
	int ret = 0;
	unsigned int TokenWords = 0;
	unsigned int TokenHeaderWord;
	TokenBuilder_Params_t TokenParams;
	unsigned int count;
	IOToken_Input_Dscr_t InTokenDscr;
	uint32_t InputToken[IOTOKEN_IN_WORD_COUNT];
	int pkthostaddress_cnt = 0, blk_cnt = 0;
	int block = len / ctx->blk_size;
	cae_device *dev = ctx->dev;

	if (ctx->first_pkt)
		PEC_ResultNotify_Request(dev, INTERFACE_ID, digest_callback,
					 ctx, 1);

	if (ctx->remain_len > 0) {
		memcpy(ctx->InPktHostAddress.p, ctx->remain, ctx->remain_len);
		pkthostaddress_cnt = ctx->remain_len;
		memcpy(ctx->InPktHostAddress.p + ctx->remain_len, in,
		       ctx->blk_size - pkthostaddress_cnt);
	} else if (ctx->remain_len == 0) {
		memcpy(ctx->InPktHostAddress.p, in, ctx->blk_size);
	}

	while (block--) {
		ZEROINIT(InTokenDscr);
		ZEROINIT(ctx->Cmd);
		/* Set Token Parameters if specified in test vector. */
		ZEROINIT(TokenParams);

		if (ctx->first_pkt) {
			TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFIRST;
			ctx->first_pkt = 0;
		}
		TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHAPPEND;
		/* Copy input packet into source packet buffer. */
		if (blk_cnt >= 1) {
			memcpy(ctx->InPktHostAddress.p,
			       (in + ctx->blk_size - pkthostaddress_cnt) +
				       (blk_cnt - 1) * ctx->blk_size,
			       ctx->blk_size);
		}
		blk_cnt++;

		/* Prepare a token to process the data. */
		ret = TokenBuilder_BuildToken(
			ctx, ctx->TCRData, (uint8_t *)ctx->InPktHostAddress.p,
			ctx->blk_size, &TokenParams,
			(uint32_t *)ctx->TokenHostAddress.p, &TokenWords,
			&TokenHeaderWord);
		if (ret != TKB_STATUS_OK) {
			if (ret == TKB_BAD_PACKET) {
				LOG_CRIT(
					"DA_PEC: Token not created because packet size is invalid\n");
			} else {
				LOG_CRIT("DA_PEC: Token builder failed\n");
			}
			goto error_exit_unregister;
		}

		ctx->Cmd.User_p = 0;
		ctx->Cmd.Token_Handle = ctx->TokenHandle;
		ctx->Cmd.Token_WordCount = TokenWords;
		ctx->Cmd.SrcPkt_Handle = ctx->InPktHandle;
		ctx->Cmd.SrcPkt_ByteCount = ctx->blk_size;
		ctx->Cmd.DstPkt_Handle = ctx->OutPktHandle;
		ctx->Cmd.Bypass_WordCount = 0;
		ctx->Cmd.SA_Handle1 = ctx->SAHandle;
		ctx->Cmd.SA_Handle2 = DMABuf_NULLHandle;
		ctx->Cmd.SA_WordCount = 128;
#ifndef DA_PEC_USE_INVALIDATE_COMMANDS
		ctx->Cmd.Control1 = TokenHeaderWord;
		ctx->Cmd.Control2 = 0;
#endif
#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
	defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
		InTokenDscrExt.HW_Services = FIRMWARE_EIP207_CMD_PKT_LAC;
#endif
		InTokenDscr.TknHdrWordInit = TokenHeaderWord;
		if (!da_pec_iotoken_create(&InTokenDscr, NULL, InputToken,
					   &ctx->Cmd)) {
			ret = 1;
			goto error_exit_unregister;
		}
		ret = PEC_Packet_Put(dev, INTERFACE_ID, &ctx->Cmd, 1, &count);
		if (ret != PEC_STATUS_OK && count != 1) {
			ret = 1;
			LOG_CRIT("calculate_digest PEC_Packet_Put error\n");
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
	}
error_exit_unregister:
	return ret == 0;
}

bool calculate_final_digest(md_ctx *ctx, unsigned char *md, unsigned int *len)
{
	int ret = 1;
	unsigned int TokenWords = 0;
	unsigned int TokenHeaderWord;
	TokenBuilder_Params_t TokenParams;
	unsigned int count;
	IOToken_Input_Dscr_t InTokenDscr;
	IOToken_Output_Dscr_t OutTokenDscr;
	uint32_t InputToken[IOTOKEN_IN_WORD_COUNT];
	void *InTokenDscrExt_p = NULL;
	cae_device *dev = ctx->dev;
#ifdef DA_PEC_IOTOKEN_EXT
	IOToken_Input_Dscr_Ext_t InTokenDscrExt;

	ZEROINIT(InTokenDscrExt);
	InTokenDscrExt_p = &InTokenDscrExt;
#endif
	ZEROINIT(InTokenDscr);
	ZEROINIT(OutTokenDscr);
	ZEROINIT(ctx->Cmd);
	/* Set Token Parameters if specified in test vector. */
	ZEROINIT(TokenParams);

	TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHAPPEND;
	TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFINAL;

	/* Copy input packet into source packet buffer. */
	if (ctx->remain_len > 0) {
		memcpy(ctx->InPktHostAddress.p, ctx->remain, ctx->remain_len);
		/* Prepare a token to process the data. */
		ret = TokenBuilder_BuildToken(
			ctx, ctx->TCRData, (uint8_t *)ctx->InPktHostAddress.p,
			ctx->remain_len, &TokenParams,
			(uint32_t *)ctx->TokenHostAddress.p, &TokenWords,
			&TokenHeaderWord);
		if (ret != TKB_STATUS_OK) {
			if (ret == TKB_BAD_PACKET) {
				LOG_CRIT(
					"DA_PEC: Token not created because packet size is invalid\n");
			} else {
				LOG_CRIT("DA_PEC: Token builder failed\n");
			}
			goto error_exit_unregister;
		}

		ctx->Cmd.User_p = 0;
		ctx->Cmd.Token_Handle = ctx->TokenHandle;
		ctx->Cmd.Token_WordCount = TokenWords;
		ctx->Cmd.SrcPkt_Handle = ctx->InPktHandle;
		ctx->Cmd.SrcPkt_ByteCount = ctx->remain_len;
		ctx->Cmd.DstPkt_Handle = ctx->OutPktHandle;
		ctx->Cmd.Bypass_WordCount = 0;
		ctx->Cmd.SA_Handle1 = ctx->SAHandle;
		ctx->Cmd.SA_Handle2 = DMABuf_NULLHandle;
		ctx->Cmd.SA_WordCount = 128;
#ifndef DA_PEC_USE_INVALIDATE_COMMANDS
		ctx->Cmd.Control1 = TokenHeaderWord;
		ctx->Cmd.Control2 = 0;
#endif
#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
	defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
		InTokenDscrExt.HW_Services = FIRMWARE_EIP207_CMD_PKT_LAC;
#endif
		InTokenDscr.TknHdrWordInit = TokenHeaderWord;
		if (!da_pec_iotoken_create(&InTokenDscr, InTokenDscrExt_p,
					   InputToken, &ctx->Cmd)) {
			ret = 1;
			goto error_exit_unregister;
		}
		ret = PEC_Packet_Put(dev, INTERFACE_ID, &ctx->Cmd, 1, &count);
		if (ret != PEC_STATUS_OK && count != 1) {
			ret = 1;
			LOG_CRIT(
				"calculate_final_digest PEC_Packet_Put error\n");
			goto error_exit_unregister;
		}

		while (1) {
			if (ctx->rdr_done == 1) {
				ctx->rdr_done = 0;
				if (ctx->hash_res.DstPkt_ByteCount !=
				    ctx->digest_len) {
					printf("length not equal. digest failed.\n");
					ret = 1;
					goto error_exit_unregister;
				}
				memcpy(md, ctx->OutPktHostAddress.p,
				       ctx->digest_len);
				*len = ctx->digest_len;
				ctx->first_pkt = 1;
				ctx->remain_len = 0;
				break;
			} else if (ctx->rdr_done == -1) {
				ret = 1;
				ctx->rdr_done = 0;
				goto error_exit_unregister;
			}
		}
error_exit_unregister:
		return ret == 0;
	} else {
		return 0;
	}
}

void digest_env_free(md_ctx *ctx)
{
	cae_device *dev = ctx->dev;

	PEC_SA_UnRegister(dev, INTERFACE_ID, ctx->SAHandle, DMABuf_NULLHandle,
			  DMABuf_NULLHandle);
	DMABuf_Release(dev, ctx->SAHandle);
	DMABuf_Release(dev, ctx->TokenHandle);
	DMABuf_Release(dev, ctx->OutPktHandle);
	DMABuf_Release(dev, ctx->InPktHandle);
	if (ctx->TCRData != NULL)
		da_pec_free(ctx->TCRData);
}
