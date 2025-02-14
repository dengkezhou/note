#ifndef __DIGEST_H__
#define __DIGEST_H__

md_ctx *md_alloc_resources(void);
int digest_init(md_ctx *ctx, const md type, unsigned char *key);
int digest_update(md_ctx *ctx, const void *in, unsigned long len, bool blocked);
int digest_final(md_ctx *ctx, unsigned char *md, unsigned int *len);
void md_free_resources(md_ctx *ctx);

extern int digest_type_init(md_ctx *ctx, const md type);

#endif
