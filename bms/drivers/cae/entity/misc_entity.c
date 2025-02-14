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
#include "sa_builder_srtp.h"
#include "sa_builder_ipsec.h"
#include "sa_builder_ssltls.h"

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
extern unsigned int misc_confirm_sabuilder_params(misc_ctx *ctx,
						  SABuilder_Params_t *params,
						  uint8_t *InnerDigest,
						  uint8_t *OuterDigest);
extern unsigned int
cipher_confirm_aad_params(cipher_ctx *ctx, TokenBuilder_Params_t *Tokenparams);

static unsigned int first_pkt = 1;

static DMABuf_Handle_t SAHandle = { 0 };
static DMABuf_Handle_t TokenHandle = { 0 };
static DMABuf_HostAddress_t TokenHostAddress;
static void *TCRData = 0;
static uint8_t InnerDigest[20], OuterDigest[20];
static DMABuf_HostAddress_t PktHostAddress;
static DMABuf_HostAddress_t SAHostAddress;
static SABuilder_Params_t params;
static DMABuf_Handle_t PktHandle = { 0 };

bool misc_env_alloc(misc_ctx *ctx)
{
	int rc;
	unsigned int SAWords = 0;
	unsigned int TokenMaxWords = 0;
	unsigned int TCRWords = 0;
	DMABuf_Status_t DMAStatus;
	DMABuf_Properties_t DMAProperties = { 0, 0, 0, 0 };
	cae_device *dev = ctx->dev;

	rc = misc_confirm_sabuilder_params(ctx, &params, InnerDigest,
					   OuterDigest);
	if (rc != 0) {
		LOG_CRIT("sa builder params error!\n");
		goto error_exit;
	}
	rc = SABuilder_GetSizes(ctx, &params, &SAWords, NULL, NULL);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: SA not created because of errors\n");
		goto error_exit;
	}

	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_SA;
	DMAProperties.Size = MAX(SAWords * 4, DA_PEC_MIN_SA_BYTE_COUNT);
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &SAHostAddress, &SAHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of outbound SA failed\n");
		goto error_exit;
	}
	rc = SABuilder_BuildSA(ctx, &params, (uint32_t *)SAHostAddress.p, NULL,
			       NULL);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: SA not created because of errors\n");
		goto error_exit;
	}

	rc = TokenBuilder_GetContextSize(&params, &TCRWords);
	if (rc != 0) {
		LOG_CRIT(
			"DA_PEC: TokenBuilder_GetContextSize returned errors\n");
		goto error_exit;
	}
	/* The Token Context Record does not need to be allocated in a DMA-safe buffer. */
	TCRData = da_pec_malloc(4 * TCRWords);
	if (!TCRData) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of outbound TCR failed\n");
		goto error_exit;
	}
	rc = TokenBuilder_BuildContext(&params, TCRData);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: TokenBuilder_BuildContext failed\n");
		goto error_exit;
	}
	rc = TokenBuilder_GetSize(TCRData, &TokenMaxWords);
	if (rc != 0) {
		LOG_CRIT("DA_PEC: TokenBuilder_GetSize failed\n");
		goto error_exit;
	}
	/* Allocate one buffer for the token and three packet buffers. */
	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_TOKEN;
	DMAProperties.Size = 4 * TokenMaxWords;
	DMAStatus = DMABuf_Alloc(dev, DMAProperties, &TokenHostAddress,
				 &TokenHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of token buffer failed.\n");
		goto error_exit;
	}
	DMAProperties.fCached = true;
	DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
	DMAProperties.Bank = DA_PEC_BANK_PACKET;
	DMAProperties.Size = ctx->digest.blk_size;
	DMAStatus =
		DMABuf_Alloc(dev, DMAProperties, &PktHostAddress, &PktHandle);
	if (DMAStatus != DMABUF_STATUS_OK) {
		rc = 1;
		LOG_CRIT("DA_PEC: Allocation of packet buffer failed.\n");
		goto error_exit;
	}
	/* Register the SAs. */
	rc = PEC_SA_Register(dev, INTERFACE_ID, SAHandle, DMABuf_NULLHandle,
			     DMABuf_NULLHandle);
	if (rc != PEC_STATUS_OK) {
		LOG_CRIT("PEC_SA_Register failed\n");
		goto error_exit;
	}
	return 1;
error_exit:
	DMABuf_Release(dev, SAHandle);
	DMABuf_Release(dev, TokenHandle);
	DMABuf_Release(dev, PktHandle);
	if (TCRData != NULL)
		da_pec_free(TCRData);
	return rc == 0;
}

bool calculate_misc(misc_ctx *ctx, const void *in, unsigned long in_len)
{
	int ret;
	PEC_CommandDescriptor_t Cmd;
	PEC_ResultDescriptor_t Res;
	uint32_t InputToken[IOTOKEN_IN_WORD_COUNT];
	uint32_t OutputToken[IOTOKEN_OUT_WORD_COUNT];
	unsigned int count;
	IOToken_Input_Dscr_t InTokenDscr;
	IOToken_Output_Dscr_t OutTokenDscr;
	TokenBuilder_Params_t TokenParams;
	unsigned int TokenWords = 0;
	uint32_t TokenHeaderWord;
	int pkthostaddress_cnt = 0;
	int block = in_len / ctx->cipher.blk_size;
	cae_device *dev = ctx->dev;

	while (block--) {
		ZEROINIT(InTokenDscr);
		ZEROINIT(OutTokenDscr);
		ZEROINIT(Cmd);
		/* Set Token Parameters if specified in test vector. */
		ZEROINIT(TokenParams);
		cipher_confirm_aad_params(&ctx->cipher, &TokenParams);
		if (first_pkt) {
			TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFIRST;
			first_pkt = 0;
		}
		TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHAPPEND;

		/* Copy input packet into source packet buffer. */
		if (!in) {
			memcpy(PktHostAddress.p, ctx->cipher.remain,
			       ctx->cipher.remain_len);
			ctx->cipher.remain_len = 0;
		} else if (ctx->cipher.remain_len > 0) {
			memcpy(PktHostAddress.p, ctx->cipher.remain,
			       ctx->cipher.remain_len);
			pkthostaddress_cnt = ctx->cipher.remain_len;
			memcpy(PktHostAddress.p, in,
			       ctx->cipher.blk_size - pkthostaddress_cnt);
			ctx->cipher.remain_len = 0;
		} else if (ctx->cipher.remain_len == 0) {
			memcpy(PktHostAddress.p,
			       in + ctx->cipher.blk_size - pkthostaddress_cnt,
			       ctx->cipher.blk_size);
		}

		/* Prepare a token to process the packet. */
		ret = TokenBuilder_BuildToken(ctx, TCRData,
					      (uint8_t *)PktHostAddress.p,
					      ctx->cipher.blk_size,
					      &TokenParams,
					      (uint32_t *)TokenHostAddress.p,
					      &TokenWords, &TokenHeaderWord);
		if (ret != TKB_STATUS_OK) {
			if (ret == TKB_BAD_PACKET) {
				LOG_CRIT(
					"Token not created because packet size is invalid\n");
			} else {
				LOG_CRIT("Token builder failed\n");
			}
			goto error_exit_unregister;
		}

		Cmd.User_p = 0;
		Cmd.Token_Handle = TokenHandle;
		Cmd.Token_WordCount = TokenWords;
		Cmd.SrcPkt_Handle = PktHandle;
		Cmd.SrcPkt_ByteCount = ctx->cipher.blk_size;
		Cmd.DstPkt_Handle = PktHandle;
		Cmd.Bypass_WordCount = 0;
		Cmd.SA_Handle1 = SAHandle;
		Cmd.SA_Handle2 = DMABuf_NULLHandle;
		Cmd.SA_WordCount = 128;

		InTokenDscr.TknHdrWordInit = TokenHeaderWord;
		if (!da_pec_iotoken_create(&InTokenDscr, NULL, InputToken,
					   &Cmd)) {
			ret = 1;
			goto error_exit_unregister;
		}
		ret = PEC_Packet_Put(dev, INTERFACE_ID, &Cmd, 1, &count);
		if (ret != PEC_STATUS_OK && count != 1) {
			ret = 1;
			LOG_CRIT("calculate_misc PEC_Packet_Put error\n");
			goto error_exit_unregister;
		}
		if (da_pec_pe_get_one(dev, &OutTokenDscr, OutputToken, &Res) ==
		    0) {
			ret = 1;
			LOG_CRIT("error from da_pec_pe_get_one\n");
			goto error_exit_unregister;
		}
	}

	return 1;

error_exit_unregister:
	return ret == 0;
}

bool calculate_final_misc(misc_ctx *ctx, unsigned char *md, unsigned int *len)
{
	int ret;
	PEC_CommandDescriptor_t Cmd;
	PEC_ResultDescriptor_t Res;
	uint32_t InputToken[IOTOKEN_IN_WORD_COUNT];
	uint32_t OutputToken[IOTOKEN_OUT_WORD_COUNT];
	unsigned int count;
	IOToken_Input_Dscr_t InTokenDscr;
	IOToken_Output_Dscr_t OutTokenDscr;
	TokenBuilder_Params_t TokenParams;
	unsigned int TokenWords = 0;
	uint32_t TokenHeaderWord;
	cae_device *dev = ctx->dev;

	ZEROINIT(InTokenDscr);
	ZEROINIT(OutTokenDscr);
	ZEROINIT(Cmd);
	/* Set Token Parameters if specified in test vector. */
	ZEROINIT(TokenParams);
	cipher_confirm_aad_params(&ctx->cipher, &TokenParams);
	TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHAPPEND;
	TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFINAL;

	/* Copy input packet into source packet buffer. */
	if (ctx->cipher.remain_len > 0) {
		memcpy(PktHostAddress.p, ctx->cipher.remain,
		       ctx->cipher.remain_len);
		ctx->cipher.remain_len = 0;
	}

	/* Prepare a token to process the data. */
	ret = TokenBuilder_BuildToken(ctx, TCRData, (uint8_t *)PktHostAddress.p,
				      ctx->cipher.blk_size, &TokenParams,
				      (uint32_t *)TokenHostAddress.p,
				      &TokenWords, &TokenHeaderWord);
	if (ret != TKB_STATUS_OK) {
		if (ret == TKB_BAD_PACKET) {
			LOG_CRIT(
				"DA_PEC: Token not created because packet size is invalid\n");
		} else {
			LOG_CRIT("DA_PEC: Token builder failed\n");
		}
		goto error_exit_unregister;
	}

	Cmd.User_p = 0;
	Cmd.Token_Handle = TokenHandle;
	Cmd.Token_WordCount = TokenWords;
	Cmd.SrcPkt_Handle = PktHandle;
	Cmd.SrcPkt_ByteCount = ctx->cipher.blk_size;
	Cmd.DstPkt_Handle = PktHandle;
	Cmd.Bypass_WordCount = 0;
	Cmd.SA_Handle1 = SAHandle;
	Cmd.SA_Handle2 = DMABuf_NULLHandle;
	Cmd.SA_WordCount = 128;

#ifndef DA_PEC_USE_INVALIDATE_COMMANDS
	Cmd.Control1 = TokenHeaderWord;
	Cmd.Control2 = 0;
#endif
	InTokenDscr.TknHdrWordInit = TokenHeaderWord;
	if (!da_pec_iotoken_create(&InTokenDscr, NULL, InputToken, &Cmd)) {
		ret = 1;
		goto error_exit_unregister;
	}

	ret = PEC_Packet_Put(dev, INTERFACE_ID, &Cmd, 1, &count);
	if (ret != PEC_STATUS_OK && count != 1) {
		ret = 1;
		LOG_CRIT("calculate_final_misc PEC_Packet_Put error\n");
		goto error_exit_unregister;
	}

	if (da_pec_pe_get_one(dev, &OutTokenDscr, OutputToken, &Res) < 1) {
		ret = 1;
		LOG_CRIT("DA_PEC: error from da_pec_pe_get_one\n");
		goto error_exit_unregister;
	}

	if (Res.DstPkt_ByteCount != ctx->digest.digest_len) {
		printf("length not equal. digest failed.\n");
		ret = 1;
		goto error_exit_unregister;
	}
	memcpy(md, PktHostAddress.p, ctx->digest.digest_len);
	*len = ctx->digest.digest_len;
	first_pkt = 1;
error_exit_unregister:
	return ret == 0;
}

void misc_env_free(misc_ctx *ctx)
{
	cae_device *dev = ctx->dev;

	PEC_SA_UnRegister(dev, INTERFACE_ID, SAHandle, DMABuf_NULLHandle,
			  DMABuf_NULLHandle);
	DMABuf_Release(dev, SAHandle);
	DMABuf_Release(dev, TokenHandle);
	DMABuf_Release(dev, PktHandle);
	if (TCRData != NULL)
		da_pec_free(TCRData);
}
