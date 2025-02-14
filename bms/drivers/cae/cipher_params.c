#include <cae.h>
#include "cipher.h"

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

#define CIPHER_DES_BLK_SIZE 8
#define CIPHER_3DES_BLK_SIZE 8
#define CIPHER_AES_BLK_SIZE 16

int cipher_type_init(cipher_ctx *ctx, const cipher type)
{
	int ret = 1;
	switch (type) {
	case CIPHER_DES_ECB:
		ctx->blk_size = CIPHER_DES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_DES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_ECB;
		break;
	case CIPHER_DES_CBC:
		ctx->blk_size = CIPHER_DES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_DES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_CBC;
		break;
	case CIPHER_3DES_ECB:
		ctx->blk_size = CIPHER_3DES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_3DES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_ECB;
		break;
	case CIPHER_3DES_CBC:
		ctx->blk_size = CIPHER_3DES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_3DES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_CBC;
		break;
	case CIPHER_AES_128_ECB:
	case CIPHER_AES_192_ECB:
	case CIPHER_AES_256_ECB:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_ECB;
		break;
	case CIPHER_AES_128_CBC:
	case CIPHER_AES_192_CBC:
	case CIPHER_AES_256_CBC:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_CBC;
		break;
	case CIPHER_AES_128_OFB128:
	case CIPHER_AES_192_OFB128:
	case CIPHER_AES_256_OFB128:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_OFB;
		break;
	case CIPHER_AES_128_CFB:
	case CIPHER_AES_192_CFB:
	case CIPHER_AES_256_CFB:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_CFB;
		break;
	case CIPHER_AES_128_CTR:
	case CIPHER_AES_192_CTR:
	case CIPHER_AES_256_CTR:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_CTR;
		break;
	case CIPHER_AES_128_ICM:
	case CIPHER_AES_192_ICM:
	case CIPHER_AES_256_ICM:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_ICM;
		break;
	case CIPHER_AES_128_CCM:
	case CIPHER_AES_192_CCM:
	case CIPHER_AES_256_CCM:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_CCM;
		break;
	case CIPHER_AES_128_GCM:
	case CIPHER_AES_192_GCM:
	case CIPHER_AES_256_GCM:
		ctx->blk_size = CIPHER_AES_BLK_SIZE;
		ctx->crypto_algo = SAB_CRYPTO_AES;
		ctx->crypto_mode = SAB_CRYPTO_MODE_GCM;
		break;
	default:
		ret = 0;
		goto err;
	}
err:
	return ret;
}