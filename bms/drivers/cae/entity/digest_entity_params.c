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

static uint8_t DummyAuthKey[64];

extern bool da_pec_hmac_precompute(md_ctx *ctx, SABuilder_Auth_t AuthAlgo,
				   uint8_t *AuthKey_p,
				   unsigned int AuthKeyByteCount,
				   uint8_t *Inner_p, uint8_t *Outer_p);

unsigned int
digest_confirm_sabuilder_params(md_ctx *ctx, SABuilder_Params_t *params,
				SABuilder_Params_Basic_t *basic_params,
				uint8_t *InnerDigest, uint8_t *OuterDigest)
{
	params->AuthAlgo = ctx->auth_algo;
	if (ctx->key) {
		if (strlen((char *)ctx->key) > 0) {
			if (params->AuthAlgo == SAB_AUTH_AES_XCBC_MAC ||
			    params->AuthAlgo == SAB_AUTH_AES_GCM ||
			    params->AuthAlgo == SAB_AUTH_AES_CMAC_128 ||
			    params->AuthAlgo == SAB_AUTH_AES_CMAC_192 ||
			    params->AuthAlgo == SAB_AUTH_AES_CMAC_256) {
				params->AuthKey1_p = ctx->key;
				params->AuthKey2_p = ctx->key;
				params->AuthKey3_p = ctx->key;
			} else {
				da_pec_hmac_precompute(ctx, ctx->auth_algo,
						       ctx->key,
						       strlen((char *)ctx->key),
						       InnerDigest,
						       OuterDigest);
				params->AuthKey1_p = InnerDigest;
				params->AuthKey2_p = OuterDigest;
			}
		} else {
			params->AuthKey1_p = DummyAuthKey;
		}
	} else {
		params->AuthKey1_p = DummyAuthKey;
	}
	/* Dummy authentication key must be supplied when SAB_FLAG_HASH_INTERMEDIATE is set. */
	if (ctx->multi_part_packet_flag)
		params->flags |= SAB_FLAG_HASH_SAVE |
				 SAB_FLAG_HASH_INTERMEDIATE;

	params->flags |= SAB_FLAG_SUPPRESS_PAYLOAD;
	basic_params->ICVByteCount = ctx->digest_len;
	return 0;
}
