#include <cae.h>
#include "digest.h"

extern bool digest_env_alloc(md_ctx *ctx);
extern bool calculate_digest(md_ctx *ctx, const void *in, unsigned long len);
extern bool calculate_digest_nonblock(md_ctx *ctx, const void *in,
				      unsigned long len);
extern bool calculate_final_digest(md_ctx *ctx, unsigned char *md,
				   unsigned int *len);
extern void digest_env_free(md_ctx *ctx);

md_ctx *md_alloc_resources(void)
{
	return (md_ctx *)malloc(sizeof(md_ctx));
}

int digest_init(md_ctx *ctx, const md type, unsigned char *key)
{
	int ret = 1;

	ret = digest_type_init(ctx, type);
	if (!ret)
		goto err;

	if (key) {
		if (strlen((char *)key) <= MAX_DIGEST_KEY_LEN &&
		    strlen((char *)key) > 0) {
			ctx->key = key;
		} else if (strlen((char *)key) == 0) {
			ctx->key = NULL;
		} else {
			ret = 0;
			goto err;
		}
	} else {
		ctx->key = NULL;
	}
	ctx->remain_len = 0;
	ret = digest_env_alloc(ctx);
err:
	return ret;
}

int digest_update(md_ctx *ctx, const void *in, unsigned long len, bool blocked)
{
	int ret = 1;
	int in_len = ctx->remain_len + len;

	ctx->blocked = blocked;

	if (ctx->blocked == CAE_UPDATE_NONBLOCK) {
		ctx->in_seek = 0;
		ctx->in = in;
		ctx->in_len = len;
		if (in_len <= ctx->blk_size) {
			memcpy(ctx->remain + ctx->remain_len, in, len);
			ctx->remain_len = ctx->remain_len + len;
			ctx->left_update_blks = 0;
			ctx->final_left_cnt = ctx->remain_len;
		} else if (in_len > ctx->blk_size) {
			if (in_len % ctx->blk_size == 0) {
				ctx->left_update_blks =
					in_len / ctx->blk_size - 1 - 1;
				ctx->final_left_cnt = ctx->blk_size;
				ret = calculate_digest_nonblock(ctx, in,
								ctx->blk_size);
				if (!ret)
					goto err;
			} else {
				ctx->left_update_blks =
					in_len / ctx->blk_size - 1;
				ctx->final_left_cnt = in_len % ctx->blk_size;
				ret = calculate_digest_nonblock(ctx, in,
								ctx->blk_size);
				if (!ret)
					goto err;
			}
		}
	} else {
		if (in_len < ctx->blk_size) {
			memcpy(ctx->remain + ctx->remain_len, in, len);
			ctx->remain_len = ctx->remain_len + len;
		} else if (in_len >= ctx->blk_size) {
			if (in_len % ctx->blk_size == 0) {
				ret = calculate_digest(
					ctx, in,
					in_len / ctx->blk_size * ctx->blk_size -
						ctx->blk_size);
				if (!ret)
					goto err;
				ctx->remain_len = ctx->blk_size;
				memcpy(ctx->remain, in + len - ctx->remain_len,
				       ctx->remain_len);
			} else {
				ret = calculate_digest(ctx, in, in_len);
				if (!ret)
					goto err;
				ctx->remain_len = in_len % ctx->blk_size;
				if (ctx->remain_len > 0)
					memcpy(ctx->remain,
					       in + len - ctx->remain_len,
					       ctx->remain_len);
			}
		}
	}
err:
	return ret;
}

static int wait_process_completed(md_ctx *ctx)
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

int digest_final(md_ctx *ctx, unsigned char *md, unsigned int *len)
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

	ctx->hash_final_pkt = 1;
	if (ctx->blocked == CAE_UPDATE_NONBLOCK)
		ctx->left_update_blks = 0;

	if (ctx->first_pkt) {
		digest_env_free(ctx);
		ctx->multi_part_packet_flag = 0;
		digest_env_alloc(ctx);
	}

	ret = calculate_final_digest(ctx, md, len);
	digest_env_free(ctx);
	ctx->hash_final_pkt = 0;
exit:
	return ret;
}

void md_free_resources(md_ctx *ctx)
{
	if (ctx)
		free(ctx);
}
