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

#ifndef SW_STREAM_H_
#define SW_STREAM_H_

#include "basetype.h"

struct StrmData {
  const u8 *strm_buff_start; /* pointer to start of stream buffer */
  const u8 *strm_curr_pos;   /* current read address in stream buffer */
  u32 bit_pos_in_word;       /* bit position in stream buffer byte */
  u32 strm_buff_size;        /* size of stream buffer (bytes) */
  u32 strm_data_size;        /* size of stream data (bytes) */
  u32 strm_buff_read_bits;   /* number of bits read from stream buffer */
  u32 remove_emul3_byte;     /* signal the pre-removal of emulation prevention 3
                    bytes */
  u32 emul_byte_count; /* counter incremented for each removed byte */
  u32 is_rb;               /* ring buffer used? */
  u32 remove_avs_fake_2bits;     /* = 1 to remove 2-bit '10' for  fake start code  */
  struct strmInfo *stream_info;
};

typedef u8 SwReadByteFn(const u8 *p, u32 size, struct strmInfo *stream_info);
u32 SwGetBits(struct StrmData *stream, u32 num_bits);
u32 SwGetBits32(struct StrmData *stream);
u32 SwGetBitsUnsignedMax(struct StrmData *stream, u32 max_value);
u32 SwShowBits(struct StrmData *stream, u32 num_bits);
u32 SwFlushBits(struct StrmData *stream, u32 num_bits);
u32 SwIsByteAligned(const struct StrmData *);
u8 SwNoLatencyReadByte(const u8 *p, u32 size, struct strmInfo *stream_info);
u8 SwLowLatencyReadByte(const u8 *p, u32 buf_size, struct strmInfo *stream_info);
SwReadByteFn *SwGetReadByteFunc(struct strmInfo *stream_info);
void SwUpdateStrmDataSize(struct StrmData *stream);
void SwStreamTraceOpen();
void SwStreamTrace(char *format, ...);
void SwStreamTraceClose();

/* utils for u(v) */
static inline int floorLog2(u32 x) {
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

static inline int ceilLog2(u32 x)
{
  return (x==0) ? -1 : floorLog2(x - 1) + 1;
}

#define READ_CODE(stream, n, syntax, str) do { \
  u32 ucode = SwGetBits(stream, (n)); \
  if (ucode == END_OF_STREAM) return(HANTRO_NOK); \
  SwStreamTrace("%s : %d", str, ucode); \
  syntax = ucode; \
} while (0)

#define READ_FLAG(stream, syntax, str) READ_CODE(stream, 1, syntax, str)

#define READ_CODE_ARGS(stream, n, syntax, str, ...) do { \
  u32 ucode = SwGetBits(stream, (n)); \
  char tmp_str[128]; \
  if (ucode == END_OF_STREAM) return(HANTRO_NOK); \
  snprintf(tmp_str, 128, str, ##__VA_ARGS__); \
  SwStreamTrace("%s : %d", tmp_str, ucode); \
  syntax = ucode; \
} while (0)

#define READ_FLAG_ARGS(stream, syntax, str, ...) READ_CODE_ARGS(stream, 1, syntax, str, ##__VA_ARGS__)

#define CHECK_SYNTAX(cond, msg) do { \
  if (cond) { \
    ERROR_PRINT(msg); \
    return (HANTRO_NOK); \
  } \
} while (0)

#define CHECK_SYNTAX_2(cond, msg) do { \
  if (cond) { \
    ERROR_PRINT(msg); \
    return; \
  } \
} while (0)

#define CHECK_ALLOCATION(cond, msg, target) do { \
  if (cond) { \
    ERROR_PRINT(msg); \
    goto target; \
  } \
} while (0)
#endif /* #ifdef SW_STREAM_H_ */
