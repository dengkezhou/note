#ifndef _LINUX_BITOPS_H
#define _LINUX_BITOPS_H

/*
 * ffs: find first bit set. This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */

static inline int generic_ffs(int x) {
  int r = 1;

  if (!x)
    return 0;
  if (!(x & 0xffff)) {
    x >>= 16;
    r += 16;
  }
  if (!(x & 0xff)) {
    x >>= 8;
    r += 8;
  }
  if (!(x & 0xf)) {
    x >>= 4;
    r += 4;
  }
  if (!(x & 3)) {
    x >>= 2;
    r += 2;
  }
  if (!(x & 1)) {
    x >>= 1;
    r += 1;
  }
  return r;
}

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static inline unsigned long __ffs(unsigned long word) {
  int num = 0;

#if BITS_PER_LONG == 64
  if ((word & 0xffffffff) == 0) {
    num += 32;
    word >>= 32;
  }
#endif
  if ((word & 0xffff) == 0) {
    num += 16;
    word >>= 16;
  }
  if ((word & 0xff) == 0) {
    num += 8;
    word >>= 8;
  }
  if ((word & 0xf) == 0) {
    num += 4;
    word >>= 4;
  }
  if ((word & 0x3) == 0) {
    num += 2;
    word >>= 2;
  }
  if ((word & 0x1) == 0)
    num += 1;
  return num;
}

/*
 * fls: find last bit set.
 */

static inline int generic_fls(int x) {
  int r = 32;

  if (!x)
    return 0;
  if (!(x & 0xffff0000u)) {
    x <<= 16;
    r -= 16;
  }
  if (!(x & 0xff000000u)) {
    x <<= 8;
    r -= 8;
  }
  if (!(x & 0xf0000000u)) {
    x <<= 4;
    r -= 4;
  }
  if (!(x & 0xc0000000u)) {
    x <<= 2;
    r -= 2;
  }
  if (!(x & 0x80000000u)) {
    x <<= 1;
    r -= 1;
  }
  return r;
}

/*
 * hweightN: returns the hamming weight (i.e. the number
 * of bits set) of a N-bit word
 */

static inline unsigned int generic_hweight32(unsigned int w) {
  unsigned int res = (w & 0x55555555) + ((w >> 1) & 0x55555555);
  res              = (res & 0x33333333) + ((res >> 2) & 0x33333333);
  res              = (res & 0x0F0F0F0F) + ((res >> 4) & 0x0F0F0F0F);
  res              = (res & 0x00FF00FF) + ((res >> 8) & 0x00FF00FF);
  return (res & 0x0000FFFF) + ((res >> 16) & 0x0000FFFF);
}

static inline unsigned int generic_hweight16(unsigned int w) {
  unsigned int res = (w & 0x5555) + ((w >> 1) & 0x5555);
  res              = (res & 0x3333) + ((res >> 2) & 0x3333);
  res              = (res & 0x0F0F) + ((res >> 4) & 0x0F0F);
  return (res & 0x00FF) + ((res >> 8) & 0x00FF);
}

static inline unsigned int generic_hweight8(unsigned int w) {
  unsigned int res = (w & 0x55) + ((w >> 1) & 0x55);
  res              = (res & 0x33) + ((res >> 2) & 0x33);
  return (res & 0x0F) + ((res >> 4) & 0x0F);
}

#include <asm/bitops.h>

#endif
