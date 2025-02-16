/*-
 * Copyright (c) 2002 Mike Barcroft <mike@FreeBSD.org>
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	From: @(#)ansi.h	8.2 (Berkeley) 1/4/94
 *	From: @(#)types.h	8.3 (Berkeley) 1/5/94
 * $FreeBSD$
 */

#ifndef _MACHINE__TYPES_H_
#define _MACHINE__TYPES_H_

#ifndef _SYS_CDEFS_H_
#error this file needs sys/cdefs.h as a prerequisite
#endif

#include <generated/autoconf.h>

/*
 * Basic types upon which most other types are built.
 */
typedef __signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
#ifdef CONFIG_64BIT
typedef long __int64_t;
typedef unsigned long __uint64_t;
#else
typedef long long __int64_t;
typedef unsigned long long __uint64_t;
#endif

/*
 * Standard type definitions.
 */
typedef double __double_t;
typedef float __float_t;
typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;

#ifdef CONFIG_64BIT
typedef long int __intptr_t;
typedef unsigned long int __uintptr_t;
#else
typedef int __intptr_t;
typedef unsigned int __uintptr_t;
#endif

typedef signed char __int_fast8_t;
#ifdef CONFIG_64BIT
typedef long int __int_fast16_t;
typedef long int __int_fast32_t;
typedef long int __int_fast64_t;
#else
typedef int __int_fast16_t;
typedef int __int_fast32_t;
__extension__ typedef long long int __int_fast64_t;
#endif
typedef __int8_t __int_least8_t;
typedef __int16_t __int_least16_t;
typedef __int32_t __int_least32_t;
typedef __int64_t __int_least64_t;

#ifdef CONFIG_64BIT
typedef long int __ptrdiff_t; /* ptr1 - ptr2 */
typedef unsigned long int __size_t;
typedef long int __ssize_t; /* byte count or error */
#else
typedef int __ptrdiff_t; /* ptr1 - ptr2 */
typedef unsigned int __size_t;
typedef int __ssize_t; /* byte count or error */
#endif

typedef unsigned char __uint_fast8_t;
#ifdef CONFIG_64BIT
typedef unsigned long int __uint_fast16_t;
typedef unsigned long int __uint_fast32_t;
typedef unsigned long int __uint_fast64_t;
#else
typedef unsigned int __uint_fast16_t;
typedef unsigned int __uint_fast32_t;
__extension__ typedef unsigned long long int __uint_fast64_t;
#endif

typedef __uint8_t __uint_least8_t;
typedef __uint16_t __uint_least16_t;
typedef __uint32_t __uint_least32_t;
typedef __uint64_t __uint_least64_t;

/*
 * Unusual type definitions.
 */
#ifdef __GNUCLIKE_BUILTIN_VARARGS
typedef __builtin_va_list __va_list; /* internally known to gcc */
#else
typedef char *__va_list;
#endif /* __GNUCLIKE_BUILTIN_VARARGS */
#if defined(__GNUCLIKE_BUILTIN_VAALIST) && !defined(__GNUC_VA_LIST) &&         \
    !defined(__NO_GNUC_VA_LIST)
#define __GNUC_VA_LIST
typedef __va_list __gnuc_va_list; /* compatibility w/GNU headers*/
#endif

#endif /* !_MACHINE__TYPES_H_ */
