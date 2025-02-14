#ifndef __MISC_H__
#define __MISC_H__

misc_ctx *misc_alloc_resources(void);
int misc_init(misc_ctx *ctx, misc_params *misc_paras);
int misc_set_padding(misc_ctx *ctx, int pad);
int misc_update(misc_ctx *ctx, const void *in, unsigned long in_len);
int misc_final(misc_ctx *ctx, unsigned char *md, unsigned int *len);
void misc_free_resources(misc_ctx *ctx);

#endif
