/* Copyright (C) 1991,1992,1994-2001,2003,2004,2007
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 *	ISO C99 Standard: 7.2 Diagnostics	<assert.h>
 */

#ifndef _ASSERT_H
#define _ASSERT_H

/* This prints an "Assertion failed" message and aborts.  */
extern void __assert_fail(__const char *__assertion, __const char *__file,
                          unsigned int __line, __const char *__function)
    __attribute__((__noreturn__));

/* Likewise, but prints the error text for ERRNUM.  */
extern void __assert_perror_fail(int __errnum, __const char *__file,
                                 unsigned int __line, __const char *__function)
    __attribute__((__noreturn__));

/* The following is not at all used here but needed for standard
   compliance.  */
extern void __assert(const char *__assertion, const char *__file, int __line)
    __attribute__((__noreturn__));

#define assert(condition)                                                      \
  if (!(condition))                                                            \
  __assert_fail("ERR", __FILE__, __LINE__, __func__)

#if __STDC_VERSION__ >= 201112L && !defined __cplusplus
# define static_assert _Static_assert
#endif

#endif /* NDEBUG.  */
