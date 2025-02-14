/*
 * Copyright (c) 1993 Martin Birgmeier
 * All rights reserved.
 *
 * You may redistribute unmodified or modified versions of this source
 * code provided that the above copyright notice and this and the
 * following conditions are retained.
 *
 * This software is provided ``as is'', and comes with no warranties
 * of any kind. I shall in no event be liable for anything that happens
 * to anyone/anything when using this software.
 *
 *	$OpenBSD: rand48.h,v 1.3 2002/02/16 21:27:24 millert Exp $
 */

#ifndef _RAND48_H_
#define _RAND48_H_

void __dorand48(unsigned short[3]);

#define RAND48_SEED_0 (0x330e)
#define RAND48_SEED_1 (0xabcd)
#define RAND48_SEED_2 (0x1234)
#define RAND48_MULT_0 (0xe66d)
#define RAND48_MULT_1 (0xdeec)
#define RAND48_MULT_2 (0x0005)
#define RAND48_ADD    (0x000b)

extern long lrand48(void);
extern void srand48(long seed);

#define RAND_MAX 0x7fffffff
static __inline__ int rand(void) { return (int)lrand48(); }
static __inline__ void srand(unsigned int __s) { srand48(__s); }
static __inline__ long random(void) { return lrand48(); }
static __inline__ void srandom(unsigned int __s) { srand48(__s); }

#endif /* _RAND48_H_ */
