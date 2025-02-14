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

extern unsigned int cipher_confirm_sabuilder_params(cipher_ctx *ctx,
						    SABuilder_Params_t *params);
extern unsigned int digest_confirm_sabuilder_params(md_ctx *ctx,
						    SABuilder_Params_t *params,
						    uint8_t *InnerDigest,
						    uint8_t *OuterDigest);

static SABuilder_Params_Basic_t ProtocolParams;
static SABuilder_Params_IPsec_t IPsecParams;
static SABuilder_Params_SRTP_t SRTPParams;
static SABuilder_Params_SSLTLS_t SSLTLSParams;

unsigned int misc_confirm_sabuilder_params(misc_ctx *ctx,
					   SABuilder_Params_t *params,
					   uint8_t *InnerDigest,
					   uint8_t *OuterDigest)
{
	int rc = 1;
	switch (ctx->proto_type) {
	case PROTO_NULL:
		rc = SABuilder_Init_Basic(params, &ProtocolParams,
					  !ctx->cipher.enc);
		if (ctx->hash_first)
			ProtocolParams.BasicFlags |=
				SAB_BASIC_FLAG_ENCRYPT_AFTER_HASH;
		break;
	case PROTO_IPSEC:
		IPsecParams.IPsecFlags = 0;
		rc = SABuilder_Init_ESP(params, &IPsecParams, 0xdeadbeef,
					SAB_IPSEC_TUNNEL, SAB_IPSEC_IPV4,
					!ctx->cipher.enc);
		IPsecParams.IPsecFlags |= SAB_IPSEC_LONG_SEQ |
					  SAB_IPSEC_MASK_128;
		IPsecParams.IPsecFlags |= SAB_IPSEC_FIXED_SEQ_PFFSET;
		IPsecParams.SequenceMaskBitCount = 128;
		IPsecParams.PadAlignment = 8;
		break;
	case PROTO_SSL:
		rc = SABuilder_Init_SSLTLS(params, &SSLTLSParams,
					   SAB_TLS_VERSION_1_3,
					   !ctx->cipher.enc);
		SSLTLSParams.SSLTLSFlags |= SAB_DTLS_FIXED_SEQ_PFFSET;
		SSLTLSParams.SequenceMaskBitCount = 128;
		break;
	case PROTO_MACSEC:
		break;
	case PROTO_SRTP:
		rc = SABuilder_Init_SRTP(params, &SRTPParams, true,
					 !ctx->cipher.enc);
		SRTPParams.SRTPFlags |= SAB_SRTP_FLAG_INCLUDE_MKI;
		SRTPParams.MKI = 0xdeadbeef;
		SRTPParams.ICVByteCount = 20;
		break;
	default:
		rc = 1;
		break;
	}
	if (rc != 0) {
		LOG_CRIT("DA_PEC: SABuilder_Init_Basic failed\n");
		goto error_exit;
	}

	rc = cipher_confirm_sabuilder_params(&ctx->cipher, params);
	if (rc != 0) {
		LOG_CRIT("sa builder params error!\n");
		goto error_exit;
	}
	rc = digest_confirm_sabuilder_params(&ctx->digest, params, InnerDigest,
					     OuterDigest);
	if (rc != 0) {
		LOG_CRIT("sa builder params error!\n");
		goto error_exit;
	}
error_exit:
	return rc == 0;
}
