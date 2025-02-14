/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
--         Copyright (c) 2011-2014, Google Inc. All rights reserved.          --
--         Copyright (c) 2007-2010, Hantro OY. All rights reserved.           --
--                                                                            --
-- This software is confidential and proprietary and may be used only as      --
--   expressly authorized by VeriSilicon in a written licensing agreement.    --
--                                                                            --
--         This entire notice must be reproduced on all copies                --
--                       and may not be removed.                              --
--                                                                            --
--------------------------------------------------------------------------------
-- Redistribution and use in source and binary forms, with or without         --
-- modification, are permitted provided that the following conditions are met:--
--   * Redistributions of source code must retain the above copyright notice, --
--       this list of conditions and the following disclaimer.                --
--   * Redistributions in binary form must reproduce the above copyright      --
--       notice, this list of conditions and the following disclaimer in the  --
--       documentation and/or other materials provided with the distribution. --
--   * Neither the names of Google nor the names of its contributors may be   --
--       used to endorse or promote products derived from this software       --
--       without specific prior written permission.                           --
--------------------------------------------------------------------------------
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"--
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  --
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE --
-- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  --
-- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        --
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       --
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   --
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    --
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    --
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE --
-- POSSIBILITY OF SUCH DAMAGE.                                                --
--------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

#ifndef SW_UTIL_H_
#define SW_UTIL_H_

#include "basetype.h"
#include "dwl.h"

#define HANTRO_OK 0
#define HANTRO_NOK 1

#define HANTRO_FALSE (0U)
#define HANTRO_TRUE (1U)

#define MEMORY_ALLOCATION_ERROR 0xFFFF
#define PARAM_SET_ERROR 0xFFF0

/* value to be returned by GetBits if stream buffer is empty */
#define END_OF_STREAM 0xFFFFFFFFU

/* macro to get smaller of two values */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* macro to get greater of two values */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* macro to get absolute value */
#define ABS(a) (((a) < 0) ? -(a) : (a))

/* macro to clip a value z, so that x <= z =< y */
#define CLIP3(x, y, z) (((z) < (x)) ? (x) : (((z) > (y)) ? (y) : (z)))

/* macro to clip a value z, so that 0 <= z =< 255 */
#define CLIP1(z) (((z) < 0) ? 0 : (((z) > 255) ? 255 : (z)))

/* macro to allocate memory */
#define ALLOCATE(ptr, count, type) \
  { ptr = DWLmalloc((count) * sizeof(type)); }

/* macro to free allocated memory */
#define FREE(ptr)      \
  {                    \
    if (ptr != NULL) { \
      DWLfree(ptr);    \
      ptr = NULL;      \
    }                  \
  }

/* macro to report syntax error */
#define SW_CHECK_SYNTAX_ELEMENT(rv, elem)                    \
  if (rv != HANTRO_OK) {                                     \
    fprintf(stderr, "error in syntax element '%s'\n", elem); \
    return rv;                                               \
  }

#define SW_CHECK_END_OF_STREAM(rv, elem)                             \
  if (rv == END_OF_STREAM) {                                         \
    fprintf(stderr, "end of stream in syntax element '%s'\n", elem); \
    return rv;                                                       \
  }

/* round to next multiple of n */
#define NEXT_MULTIPLE(value, n) (((value) + (n) - 1) & ~((n) - 1))
#define NEXT_MULTIPLE_1(value, n) (((value) + (n) - 1) / (n) * (n))
#define ALIGN(a) (1 << (a))

#define ROUNDUPX(val, mul) (((val) + ((mul)-1)) & (~((mul)-1)))

#if INTPTR_MAX == INT64_MAX
#ifdef VDK_STRICT_TEST
#define REG_WRITE_ADDR(reg, addr) \
  do {                            \
    if ((addr) != 0) { \
      reg##_msb = (u32)((u64)(addr) >> 32) ^ ENCRYP_CODE;   \
    } else { \
      reg##_msb = 0;   \
    } \
    reg = addr;                   \
  } while (0)
#else
#define REG_WRITE_ADDR(reg, addr) \
  do {                            \
    reg##_msb = (u32)((u64)(addr) >> 32);     \
    reg = addr;                   \
  } while (0)
#endif
#else
#define REG_WRITE_ADDR(reg, addr) \
  do {                            \
    reg = addr;                   \
  } while (0)
#endif

#define SET_REG_VALUE(regs, id, start_bits, bit_width, value) do {\
  u32 *p = (u32 *)(regs); \
  u32 tmp = p[id]; \
  tmp &= ~(((1 << (bit_width)) - 1) << (start_bits)); \
  tmp |= (value) << (start_bits); \
  p[id] = tmp; \
} while(0)

/* RFC table overflow */
/* All the CBS size except the last group may exceeds 1<<16 bytes, which may result in
   offset of the last CBS group overflows the 16-bit range. */
#ifdef RFC_WORD_ALIGN
#define RFC_MAY_OVERFLOW(w,bd) (1)
#else
#define RFC_MAY_OVERFLOW(w,bd) (NEXT_MULTIPLE((w)-128, 128)*bd >= (1<<16))
#endif

#define MAJOR_VERSION(hw_id) (((hw_id) & 0xF000) >> 12)
#define MINOR_VERSION(hw_id) (((hw_id) & 0x0FF0) >> 4)

/* legacy release based on product number */
#define IS_G1_LEGACY(hw_id) (((hw_id) >> 16) == 0x6731)
#define IS_G2_LEGACY(hw_id) (((hw_id) >> 16) == 0x6732)
#define IS_LEGACY(hw_id) ((((hw_id) >> 16) == 0x6731) || (((hw_id) >> 16) == 0x6732))

static inline int FloorLog2(u32 x) {
  if (x == 0)
  {
    // note: ceilLog2() expects -1 as return value
    return -1;
  }
#ifdef __GNUC__
  return 31 - __builtin_clz(x);
#else
#ifdef _MSC_VER
  unsigned long r = 0;
  _BitScanReverse(&r, x);
  return r;
#else
  int result = 0;
  if (x & 0xffff0000)
  {
    x >>= 16;
    result += 16;
  }
  if (x & 0xff00)
  {
    x >>= 8;
    result += 8;
  }
  if (x & 0xf0)
  {
    x >>= 4;
    result += 4;
  }
  if (x & 0xc)
  {
    x >>= 2;
    result += 2;
  }
  if (x & 0x2)
  {
    x >>= 1;
    result += 1;
  }
  return result;
#endif
#endif
}

static inline int CeilLog2(u32 x) {
  return (x==0) ? -1 : FloorLog2(x - 1) + 1;
}

u32 SwCountLeadingZeros(u32 value, u32 length);
u32 SwNumBits(u32 value);
u8* SwTurnAround(const u8 * strm, const u8* buf, u8* tmp_buf, u32 buf_size, u32 num_bits, struct strmInfo *stream_info);

#ifdef STACK_STAT
void StackStatInit();
void StackConsumption(const char *);
#else
#define StackStatInit()
#define StackConsumption(str)
#endif

#ifndef CUSTOM_UNIQUE_ID
#define UNIQUE_ID(id) (u16)((rand() & 0xFFFF) + (id))
#else
#define UNIQUE_ID(id) (u16)((CUSTOM_UNIQUE_ID) + (id))
#endif

#endif /* #ifdef SW_UTIL_H_ */
