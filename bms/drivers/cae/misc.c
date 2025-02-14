#include <cae.h>
#include "cipher.h"
#include "digest.h"
#include "misc.h"

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

extern bool misc_env_alloc(misc_ctx *ctx);
extern bool calculate_misc(misc_ctx *ctx, const void *in, unsigned long in_len);
extern bool calculate_final_misc(misc_ctx *ctx, unsigned char *md,
				 unsigned int *len);
extern void misc_env_free(misc_ctx *ctx);

misc_ctx *misc_alloc_resources(void)
{
	return (misc_ctx *)malloc(sizeof(misc_ctx));
}

int misc_init(misc_ctx *ctx, misc_params *misc_paras)
{
	int ret = 1;

	ret = cipher_type_init(&ctx->cipher, misc_paras->crypto_type);
	if (!ret)
		goto err;

	ret = digest_type_init(&ctx->digest, misc_paras->hash_type);
	if (!ret)
		goto err;

	if (strlen((char *)misc_paras->crypto_key) <= MAX_CRYPTO_KEY_LEN &&
	    strlen((char *)misc_paras->crypto_key) >= 0) {
		strcpy((char *)ctx->cipher.key, (char *)misc_paras->crypto_key);
	} else {
		ret = 0;
		goto err;
	}
	if (strlen((char *)misc_paras->iv) <= MAX_IV_LEN &&
	    strlen((char *)misc_paras->iv) >= 0) {
		strcpy((char *)ctx->cipher.iv, (char *)misc_paras->iv);
	} else {
		ret = 0;
		goto err;
	}
	ctx->cipher.enc = misc_paras->enc;
	ctx->cipher.remain_len = 0;
	ctx->cipher.nonce = NULL;
	ctx->cipher.aad = NULL;

	if (strlen((char *)misc_paras->hash_key) <= MAX_DIGEST_KEY_LEN &&
	    strlen((char *)misc_paras->hash_key) >= 0) {
		strcpy((char *)ctx->digest.key, (char *)misc_paras->hash_key);
	} else {
		ret = 0;
		goto err;
	}
	ctx->digest.remain_len = 0;
	ctx->proto_type = misc_paras->proto_type;
	ctx->hash_first = misc_paras->hash_first;
	ret = misc_env_alloc(ctx);
err:
	return ret;
}

int misc_set_padding(misc_ctx *ctx, int pad)
{
	ctx->cipher.pad = pad;
	return 1;
}

int misc_update(misc_ctx *ctx, const void *in, unsigned long in_len)
{
	int ret = 1;
	int len = ctx->cipher.remain_len + in_len;

	if (len < ctx->cipher.blk_size) {
		memcpy(ctx->cipher.remain + ctx->cipher.remain_len, in, in_len);
	} else if (len >= ctx->cipher.blk_size) {
		ret = calculate_misc(ctx, in,
				     len / ctx->cipher.blk_size *
					     ctx->cipher.blk_size);
		if (!ret)
			goto err;

		ctx->cipher.remain_len = len % ctx->cipher.blk_size;
		if (ctx->cipher.remain_len > 0)
			memcpy(ctx->cipher.remain,
			       in + in_len - ctx->cipher.remain_len,
			       ctx->cipher.remain_len);
	}

err:
	return ret;
}

int misc_final(misc_ctx *ctx, unsigned char *md, unsigned int *len)
{
	int ret = 1;
	if (ctx->cipher.remain_len > 0)
		ret = calculate_final_misc(ctx, md, len);

	misc_env_free(ctx);
	return ret;
}

void misc_free_resources(misc_ctx *ctx)
{
	if (ctx)
		free(ctx);
}
