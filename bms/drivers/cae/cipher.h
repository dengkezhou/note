#ifndef __CIPHER_H__
#define __CIPHER_H__

cipher_ctx *cipher_alloc_resources(void);
int cipher_init(cipher_ctx *ctx, const cipher type, unsigned char *key,
		unsigned char *iv, int enc);
int cipher_set_padding(cipher_ctx *ctx, int pad);
int cipher_update(cipher_ctx *ctx, unsigned char *out, int *out_len,
		  const unsigned char *in, int in_len, bool block);
int cipher_final(cipher_ctx *ctx, unsigned char *out, int *out_len);
void cipher_free_resources(cipher_ctx *ctx);

extern int cipher_type_init(cipher_ctx *ctx, const cipher type);

#endif
