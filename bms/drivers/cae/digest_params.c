#include <cae.h>
#include "digest.h"

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

/* They are block size not real group size. */
#define MD_MD5_BLK_SIZE 64
#define MD_SHA1_BLK_SIZE 64
#define MD_SHA2_224_256_BLK_SIZE 64
#define MD_SHA2_384_512_BLK_SIZE 128
#define MD_AES_XCBC_MAC_BLK_SIZE 64
#define MD_AES_128_CMAC_BLK_SIZE 16
#define MD_AES_192_CMAC_BLK_SIZE 24
#define MD_AES_256_CMAC_BLK_SIZE 32
#define MD_GHASH_BLK_SIZE 16

/* Digest result length. */
#define MD_MD5_DIGEST_LEN 16
#define MD_SHA1_DIGEST_LEN 20
#define MD_SHA2_224_DIGEST_LEN 28
#define MD_SHA2_256_DIGEST_LEN 32
#define MD_SHA2_384_DIGEST_LEN 48
#define MD_SHA2_512_DIGEST_LEN 64
#define MD_AES_XCBC_MAC_DIGEST_LEN 64
#define MD_AES_CMAC_DIGEST_LEN 16
#define MD_GHASH_DIGEST_LEN 16

int digest_type_init(md_ctx *ctx, const md type)
{
	int ret = 1;
	switch (type) {
	case HASH_CRC32:
	case HASH_MD5:
		ctx->auth_algo = SAB_AUTH_HASH_MD5;
		ctx->blk_size = MD_MD5_BLK_SIZE;
		ctx->digest_len = MD_MD5_DIGEST_LEN;
		break;
	case HASH_SHA1:
		ctx->auth_algo = SAB_AUTH_HASH_SHA1;
		ctx->blk_size = MD_SHA1_BLK_SIZE;
		ctx->digest_len = MD_SHA1_DIGEST_LEN;
		break;
	case HASH_SHA2_224:
		ctx->auth_algo = SAB_AUTH_HASH_SHA2_224;
		ctx->blk_size = MD_SHA2_224_256_BLK_SIZE;
		ctx->digest_len = MD_SHA2_224_DIGEST_LEN;
		break;
	case HASH_SHA2_256:
		ctx->auth_algo = SAB_AUTH_HASH_SHA2_256;
		ctx->blk_size = MD_SHA2_224_256_BLK_SIZE;
		ctx->digest_len = MD_SHA2_256_DIGEST_LEN;
		break;
	case HASH_SHA2_384:
		ctx->auth_algo = SAB_AUTH_HASH_SHA2_384;
		ctx->blk_size = MD_SHA2_384_512_BLK_SIZE;
		ctx->digest_len = MD_SHA2_384_DIGEST_LEN;
		break;
	case HASH_SHA2_512:
		ctx->auth_algo = SAB_AUTH_HASH_SHA2_512;
		ctx->blk_size = MD_SHA2_384_512_BLK_SIZE;
		ctx->digest_len = MD_SHA2_512_DIGEST_LEN;
		break;
	case HASH_HMAC_MD5:
		ctx->auth_algo = SAB_AUTH_HMAC_MD5;
		ctx->blk_size = MD_MD5_BLK_SIZE;
		ctx->digest_len = MD_MD5_DIGEST_LEN;
		break;
	case HASH_HMAC_SHA1:
		ctx->auth_algo = SAB_AUTH_HMAC_SHA1;
		ctx->blk_size = MD_SHA1_BLK_SIZE;
		ctx->digest_len = MD_SHA1_DIGEST_LEN;
		break;
	case HASH_HMAC_SHA2_224:
		ctx->auth_algo = SAB_AUTH_HMAC_SHA2_224;
		ctx->blk_size = MD_SHA2_224_256_BLK_SIZE;
		ctx->digest_len = MD_SHA2_224_DIGEST_LEN;
		break;
	case HASH_HMAC_SHA2_256:
		ctx->auth_algo = SAB_AUTH_HMAC_SHA2_256;
		ctx->blk_size = MD_SHA2_224_256_BLK_SIZE;
		ctx->digest_len = MD_SHA2_256_DIGEST_LEN;
		break;
	case HASH_HMAC_SHA2_384:
		ctx->auth_algo = SAB_AUTH_HMAC_SHA2_384;
		ctx->blk_size = MD_SHA2_384_512_BLK_SIZE;
		ctx->digest_len = MD_SHA2_384_DIGEST_LEN;
		break;
	case HASH_HMAC_SHA2_512:
		ctx->auth_algo = SAB_AUTH_HMAC_SHA2_512;
		ctx->blk_size = MD_SHA2_384_512_BLK_SIZE;
		ctx->digest_len = MD_SHA2_512_DIGEST_LEN;
		break;
	case HASH_AES_128_XCBC_MAC_96:
	case HASH_AES_192_XCBC_MAC_96:
	case HASH_AES_256_XCBC_MAC_96:
	case HASH_AES_128_XCBC_MAC_PRF:
	case HASH_AES_192_XCBC_MAC_PRF:
	case HASH_AES_256_XCBC_MAC_PRF:
		ctx->auth_algo = SAB_AUTH_AES_XCBC_MAC;
		ctx->blk_size = MD_AES_XCBC_MAC_BLK_SIZE;
		ctx->digest_len = MD_AES_XCBC_MAC_DIGEST_LEN;
		break;
	case HASH_AES_128_CBC_MAC:
	case HASH_AES_128_CMAC:
		ctx->auth_algo = SAB_AUTH_AES_CMAC_128;
		ctx->blk_size = MD_AES_128_CMAC_BLK_SIZE;
		ctx->digest_len = MD_AES_CMAC_DIGEST_LEN;
		break;
	case HASH_AES_192_CBC_MAC:
	case HASH_AES_192_CMAC:
		ctx->auth_algo = SAB_AUTH_AES_CMAC_192;
		ctx->blk_size = MD_AES_192_CMAC_BLK_SIZE;
		ctx->digest_len = MD_AES_CMAC_DIGEST_LEN;
		break;
	case HASH_AES_256_CBC_MAC:
	case HASH_AES_256_CMAC:
		ctx->auth_algo = SAB_AUTH_AES_CMAC_256;
		ctx->blk_size = MD_AES_256_CMAC_BLK_SIZE;
		ctx->digest_len = MD_AES_CMAC_DIGEST_LEN;
		break;
	case HASH_GHASH:
		ctx->auth_algo = SAB_AUTH_AES_GCM;
		ctx->blk_size = MD_GHASH_BLK_SIZE;
		ctx->digest_len = MD_GHASH_DIGEST_LEN;
		break;
	case HASH_SSLMAC_SHA1:
		ctx->auth_algo = SAB_AUTH_SSLMAC_SHA1;
		ctx->blk_size = MD_SHA1_BLK_SIZE;
		ctx->digest_len = MD_MD5_DIGEST_LEN;
		break;
	default:
		ret = 0;
		goto err;
	}
err:
	return ret;
}