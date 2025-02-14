#ifndef __ASM_ARM_STRING_H
#define __ASM_ARM_STRING_H

/*
 * We don't do inline string functions, since the
 * optimised inline asm versions are not small.
 */

#undef __HAVE_ARCH_STRRCHR
extern char *strrchr(const char *s, int c);

#undef __HAVE_ARCH_STRCHR
extern char *strchr(const char *s, int c);

#undef __HAVE_ARCH_MEMCPY
extern void *memcpy(void *, const void *, size_t);

#undef __HAVE_ARCH_MEMMOVE
extern void *memmove(void *, const void *, size_t);

#undef __HAVE_ARCH_MEMCHR
extern void *memchr(const void *, int, size_t);

#undef __HAVE_ARCH_MEMZERO
#undef __HAVE_ARCH_MEMSET
extern void *memset(void *, int, size_t);

#if 0
extern void __memzero(void *ptr, __kernel_size_t n);

#define memset(p, v, n)                                                        \
  ({                                                                           \
    if ((n) != 0) {                                                            \
      if (__builtin_constant_p((v)) && (v) == 0)                               \
        __memzero((p), (n));                                                   \
      else                                                                     \
        memset((p), (v), (n));                                                 \
    }                                                                          \
    (p);                                                                       \
  })

#define memzero(p, n)                                                          \
  ({                                                                           \
    if ((n) != 0)                                                              \
      __memzero((p), (n));                                                     \
    (p);                                                                       \
  })
#else
extern void memzero(void *ptr, size_t n);
#endif
int memcmp(const void *, const void *, size_t);

#endif
