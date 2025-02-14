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

#define DES_3DES_CIPHER_MIN_OUTPUT_LEN 8
#define AES_CIPHER_MIN_OUTPUT_LEN 16

#define AES_128_KEY_LEN 16
#define AES_192_KEY_LEN 24
#define AES_256_KEY_LEN 32
#define DES_KEY_LEN 8
#define DES_EDE3_KEY_LEN 24

unsigned int cipher_confirm_sabuilder_params(cipher_ctx *ctx,
					     SABuilder_Params_t *params)
{
	params->CryptoAlgo = ctx->crypto_algo;
	params->CryptoMode = ctx->crypto_mode;
	params->Key_p = ctx->key;
	if (ctx->crypto_algo == SAB_CRYPTO_AES) {
		if (ctx->key_len != AES_128_KEY_LEN &&
		    ctx->key_len != AES_192_KEY_LEN &&
		    ctx->key_len != AES_256_KEY_LEN)
			return 0;

		params->KeyByteCount = ctx->key_len;
		if (ctx->nonce)
			params->Nonce_p = ctx->nonce;
		else
			params->Nonce_p = NULL;
	} else if (ctx->crypto_algo == SAB_CRYPTO_DES) {
		params->KeyByteCount = DES_KEY_LEN;
	} else if (ctx->crypto_algo == SAB_CRYPTO_3DES) {
		params->KeyByteCount = DES_EDE3_KEY_LEN;
	}
	if (ctx->iv_len > 0)
		params->IV_p = ctx->iv;

	params->IVSrc =
		SAB_IV_SRC_SA; //SAB_IV_SRC_TOKEN;//SAB_IV_SRC_SA;//SAB_IV_SRC_PRNG;//SAB_IV_SRC_INPUT;
	//params->flags |= SAB_FLAG_COPY_IV;
	return 0;
}

unsigned int cipher_confirm_aad_params(cipher_ctx *ctx,
				       TokenBuilder_Params_t *Tokenparams)
{
	if (ctx->aad) {
		Tokenparams->AAD_p = ctx->aad;
		Tokenparams->AdditionalValue = strlen((char *)ctx->aad);
	} else {
		Tokenparams->AAD_p = NULL;
		Tokenparams->AdditionalValue = 0;
	}
	return 0;
}
