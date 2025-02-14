#ifndef __PLAT_H__
#define __PLAT_H__

#include <stdio.h>

enum {
	SMEM_BYTE_ALIGN = 0,
	SMEM_WORD_ALIGN = 2,
	SMEM_DWORD_ALIGN = 3,
	CMEM_BYTE_ALIGN = 0x10,
	CMEM_DWORD_ALIGN = 0x13
};

extern void * memset(void *s, int c,size_t count);
extern void *memcpy(void *dst, const void *src, size_t len);
#endif
