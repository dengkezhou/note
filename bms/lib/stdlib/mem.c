/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stddef.h> /* size_t */
#include <_stdint.h> /* uint32_t */

#if 0
/*
 * Copy @len bytes from @src to @dst
 */
void *memcpy(void *dst, const void *src, size_t len) {
  const char *s = src;
  char *d       = dst;

  if (((uintptr_t)s & 0x3) || ((uintptr_t)d & 0x3))
    goto skip;

  while (len >= 4) {
    *(uint32_t *)d = *(uint32_t *)s;
    d += 4;
    s += 4;
    len = len >= 4 ? len - 4 : len;
  }

skip:
  while (len--)
    *d++ = *s++;

  return dst;
}
#endif

#ifndef __HAVE_ARCH_MEMCHR
/*
 * Scan @len bytes of @src for value @c
 */
void *memchr(const void *src, int c, size_t len) {
  const char *s = src;

  while (len--) {
    if (*s == c)
      return (void *)s;
    s++;
  }

  return NULL;
}
#endif
