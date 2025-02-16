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

#include <stdio.h>
#include <stdarg.h>
#include <common.h>

extern char __lds_print[];
extern char __lds_print_size[];

/* Choose max of 128 chars for now. */
#define PRINT_BUFFER_SIZE 128
int printf(const char *fmt, ...) {
  va_list args;
  char printbuffer[PRINT_BUFFER_SIZE];
  static char *buf = __lds_print;
  int count;

#ifdef CONFIG_COMPILE_POSTSIM
  return;
#endif

  if ((long)__lds_print_size == 1)
    buf = printbuffer;
  else if ((buf - __lds_print + PRINT_BUFFER_SIZE) > (long)__lds_print_size)
    buf = __lds_print;

  va_start(args, fmt);
  count = vsnprintf(buf, PRINT_BUFFER_SIZE - 1, fmt, args);
  va_end(args);

  /* Use putchar directly as 'puts()' adds a newline. */
  buf[PRINT_BUFFER_SIZE - 1] = '\0';
  puts(buf);

#ifndef CONFIG_COMPILE_RTL
  if ((long)__lds_print_size != 1)
    buf += count;
#else
	for (int i = 0; i < (count + 1); i++) {
		*__lds_print = buf[i];
#ifdef CONFIG_C920
		asm("sync.i");
#endif
	}

  #ifdef CONFIG_C920
    asm("sync.i");
  #endif

#endif
  return count;
}
