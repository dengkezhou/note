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

extern int cipher_env_alloc(cipher_ctx *ctx);
extern int calculate_cipher(cipher_ctx *ctx, unsigned char *out, int *out_len,
			    const unsigned char *in, int in_len);
extern int calculate_cipher_nonblock(cipher_ctx *ctx, const unsigned char *in,
				     int in_len);
extern int calculate_final_cipher(cipher_ctx *ctx, unsigned char *out,
				  int *out_len, const unsigned char *in,
				  int in_len);
extern void cipher_env_free(cipher_ctx *ctx);

cipher_ctx *cipher_alloc_resources(void)
{
	return (cipher_ctx *)malloc(sizeof(cipher_ctx));
}

static int hex_str_to_hex_int(unsigned char *out, unsigned char *in,
			      int format_len)
{
	unsigned int len = strlen((char *)in);
	char hex_str[2] = { 0 };
	int i = 0, j = 0;
	unsigned int hex_int = 0;

	if (format_len == 2) {
		len = len / format_len;
		while (len--) {
			memcpy(hex_str, in + i, format_len);
			i = i + 2;
			hex_int = simple_strtoul(hex_str, NULL, 16);
			memcpy(out + j, &hex_int, format_len);
			j = j + 1;
		}
	}
	return 0;
}

int cipher_init(cipher_ctx *ctx, const cipher type, unsigned char *key,
		unsigned char *iv, int enc)
{
	int ret = 1;
	int key_len = strlen((char *)key) / 2;
	int iv_len = strlen((char *)iv) / 2;

	ret = cipher_type_init(ctx, type);
	if (!ret)
		goto err;

	if (key_len <= MAX_CRYPTO_KEY_LEN && key_len > 0) {
		hex_str_to_hex_int(ctx->key, key, 2);
		ctx->key_len = key_len;
	} else {
		ctx->key_len = 0;
	}

	if (iv_len <= MAX_IV_LEN && iv_len > 0) {
		hex_str_to_hex_int(ctx->iv, iv, 2);
		ctx->iv_len = iv_len;
	} else {
		ctx->iv_len = 0;
	}

	ctx->nonce = NULL;
	ctx->aad = NULL;

	if (enc == 1)
		ctx->enc = SAB_DIRECTION_OUTBOUND;
	else if (enc == 0)
		ctx->enc = SAB_DIRECTION_INBOUND;

	ctx->remain_len = 0;
	if (ctx->allocated == 1) {
		cipher_env_free(ctx);
		ctx->allocated = 0;
	}
	ret = cipher_env_alloc(ctx);
	if (ret == 1)
		ctx->allocated = 1;
err:
	return ret;
}

int cipher_set_padding(cipher_ctx *ctx, int pad)
{
	ctx->pad = pad;
	return 1;
}

int cipher_update(cipher_ctx *ctx, unsigned char *out, int *out_len,
		  const unsigned char *in, int in_len, bool blocked)
{
	int ret = 1;
	int len = ctx->remain_len + in_len;

	ctx->blocked = blocked;

	if (ctx->blocked == CAE_UPDATE_NONBLOCK) {
		ctx->in_seek = 0;
		ctx->in = in;
		ctx->in_len = in_len;
		ctx->out = out;
		*out_len = 0;
		ctx->out_len = out_len;
		if (len <= ctx->blk_size) {
			ctx->first_pkt = 1;
			memcpy(ctx->remain + ctx->remain_len, in, in_len);
			ctx->remain_len = ctx->remain_len + in_len;
			ctx->left_update_blks = 0;
			ctx->final_left_cnt = ctx->remain_len;
		} else if (len > ctx->blk_size) {
			ctx->first_pkt = 0;
			if (len % ctx->blk_size == 0) {
				ctx->left_update_blks =
					len / ctx->blk_size - 1 - 1;
				ctx->final_left_cnt = ctx->blk_size;
				ret = calculate_cipher_nonblock(ctx, in,
								ctx->blk_size);
				if (!ret)
					goto err;
			} else {
				ctx->left_update_blks = len / ctx->blk_size - 1;
				ctx->final_left_cnt = len % ctx->blk_size;
				ret = calculate_cipher_nonblock(ctx, in,
								ctx->blk_size);
				if (!ret)
					goto err;
			}
		}
	} else {
		if (len <= ctx->blk_size) {
			memcpy(ctx->remain + ctx->remain_len, in, in_len);
			ctx->remain_len = ctx->remain_len + in_len;
		} else if (len > ctx->blk_size) {
			if (len % ctx->blk_size == 0) {
				ret = calculate_cipher(
					ctx, out, out_len, in,
					len / ctx->blk_size * ctx->blk_size -
						ctx->blk_size);
				if (!ret)
					goto err;

				ctx->remain_len = ctx->blk_size;
				memcpy(ctx->remain,
				       in + in_len - ctx->remain_len,
				       ctx->remain_len);
			} else {
				ret = calculate_cipher(ctx, out, out_len, in,
						       len / ctx->blk_size *
							       ctx->blk_size);
				if (!ret)
					goto err;
				ctx->remain_len = len % ctx->blk_size;
				if (ctx->remain_len > 0)
					memcpy(ctx->remain,
					       in + in_len - ctx->remain_len,
					       ctx->remain_len);
			}
		}
	}
err:
	return ret;
}

static int wait_process_completed(cipher_ctx *ctx)
{
	while (1) {
		if (ctx->rdr_done == 1) {
			ctx->rdr_done = 0;
			return 0;
		} else if (ctx->rdr_done == -1) {
			ctx->rdr_done = 0;
			return -1;
		}
	}
}

int cipher_final(cipher_ctx *ctx, unsigned char *out, int *out_len)
{
	int ret = 1;

	if (ctx->blocked == CAE_UPDATE_NONBLOCK) {
		if (!ctx->first_pkt) {
			if (wait_process_completed(ctx) == -1) {
				ret = 0;
				goto exit;
			}
			ctx->remain_len = ctx->final_left_cnt;
			memcpy(ctx->remain,
			       ctx->in + ctx->in_len - ctx->final_left_cnt,
			       ctx->remain_len);
		}
	}

	ctx->final_pkt = 1;
	if (ctx->blocked == CAE_UPDATE_NONBLOCK)
		ctx->left_update_blks = 0;

	ret = calculate_final_cipher(ctx, out, out_len, ctx->remain,
				     ctx->remain_len);
	ctx->final_pkt = 0;
exit:
	return ret;
}

void cipher_free_resources(cipher_ctx *ctx)
{
	if (ctx->allocated == 1) {
		cipher_env_free(ctx);
		ctx->allocated = 0;
	}
	if (ctx)
		free(ctx);
}
