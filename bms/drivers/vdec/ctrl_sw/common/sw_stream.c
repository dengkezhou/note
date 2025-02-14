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

#include <stdarg.h>
#include "sw_util.h"
#include "sw_stream.h"
#include "sw_debug.h"

//#define STREAM_TRACE

#ifdef STREAM_TRACE
static FILE *trace_stream_txt = NULL;
char flushed_bit_string[10*1024];
#endif

extern volatile struct strmInfo stream_info;
static const u8* SwRingBufferProtect(const u8 *strm, int size, struct StrmData *stream) {
  const u8 *p = NULL;

  ASSERT(strm);
  ASSERT(stream);

  if (strm != stream->strm_curr_pos) {
    /* SwTurnAround has been called. */
    p = strm + size;
    return p;
  }

  if (size < 0)
    p = (strm + size >= stream->strm_buff_start ? (strm + size) : (strm + size + stream->strm_buff_size));
  else if (size > 0) {
    p = (strm + size <= stream->strm_buff_start + stream->strm_buff_size) ?
        (strm + size) : (strm + size - stream->strm_buff_size);
  }
  else
    p = strm;
  return p;
}

u32 SwGetBits(struct StrmData *stream, u32 num_bits) {

  u32 out;

  ASSERT(stream);
  ASSERT(num_bits <= 32);

  if (num_bits == 0) return 0;

  out = SwShowBits(stream, 32) >> (32 - num_bits);

  if (SwFlushBits(stream, num_bits) == HANTRO_OK) {
    return (out);
  } else {
    return (END_OF_STREAM);
  }
}

u32 SwGetBits32(struct StrmData *stream) {

  u32 out;

  ASSERT(stream);

  out = SwShowBits(stream, 32);

  (void)SwFlushBits(stream, 32);

  return out;
}

u32 SwGetBitsUnsignedMax(struct StrmData *stream, u32 max_value) {
  i32 bits = 0;
  u32 num_values = max_value;
  u32 value;

  /* Bits for unsigned value */
  if (num_values > 1) {
    num_values--;
    while (num_values > 0) {
      bits++;
      num_values >>= 1;
    }
  }

  value = SwGetBits(stream, bits);
  return (value > max_value) ? max_value : value;
}

u32 SwShowBits(struct StrmData *stream, u32 num_bits) {

  i32 bits;
  u32 out, out_bits;
  u32 tmp_read_bits;
  const u8 *strm;
  SwReadByteFn *fn_read_byte;
  /* used to copy stream data when ringbuffer turnaround */
  u8 tmp_strm_buf[32], *tmp;

  ASSERT(stream);
  ASSERT(stream->strm_curr_pos);
  ASSERT(stream->bit_pos_in_word < 8);
  ASSERT(stream->bit_pos_in_word == (stream->strm_buff_read_bits & 0x7));
  ASSERT(num_bits <= 32);

  strm = stream->strm_curr_pos;
  fn_read_byte = SwGetReadByteFunc(stream->stream_info);

  /* bits left in the buffer */
  SwUpdateStrmDataSize(stream);

  bits = (i32)stream->strm_data_size * 8 - (i32)stream->strm_buff_read_bits;
  if (!bits) {
    return (0);
  }

  if (stream->is_rb)
    tmp = SwTurnAround(stream->strm_curr_pos, stream->strm_buff_start,
                       tmp_strm_buf, stream->strm_buff_size,
                       MIN(bits, num_bits + stream->bit_pos_in_word + 32), stream->stream_info);
  else
    tmp = NULL;

  if(tmp != NULL)
    strm = tmp;

  if (!stream->remove_emul3_byte) {

    out = out_bits = 0;
    tmp_read_bits = stream->strm_buff_read_bits;

    if (stream->bit_pos_in_word) {
      out = (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << (24 + stream->bit_pos_in_word);
      strm++;
      out_bits = 8 - stream->bit_pos_in_word;
      bits -= out_bits;
      tmp_read_bits += out_bits;
    }

    while (bits && out_bits < num_bits) {

      /* check emulation prevention byte */
      if (tmp_read_bits >= 16 &&
          (fn_read_byte(SwRingBufferProtect(strm, -2, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(SwRingBufferProtect(strm, -1, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0x3) {
        strm++;
        tmp_read_bits += 8;
        bits -= 8;
        /* emulation prevention byte shall not be the last byte of the
         * stream */
        if (bits <= 0) break;
      }

      tmp_read_bits += 8;

      if (out_bits <= 24) {
        out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << (24 - out_bits);
        strm++;
      } else {
        out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) >> (out_bits - 24);
        strm++;
      }

      out_bits += 8;
      bits -= 8;
    }

    return (out >> (32 - num_bits));

  }
  else if(stream->remove_avs_fake_2bits)
  {
    out = out_bits = 0;
    tmp_read_bits = stream->strm_buff_read_bits;

    if (stream->bit_pos_in_word) {
      out = (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << (24 + stream->bit_pos_in_word);


      /* check emulation prevention byte */
      if (tmp_read_bits >= 16 &&
          (fn_read_byte(SwRingBufferProtect(strm, -2, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(SwRingBufferProtect(strm, -1, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0x2) {
        strm++;
        tmp_read_bits += 8 - stream->bit_pos_in_word;
        bits -= 8 - stream->bit_pos_in_word;

        out_bits = 8 - stream->bit_pos_in_word - 2;

        out &=~((1<<(32-out_bits))-1);
      }
      else
      {
        strm++;
        tmp_read_bits += 8 - stream->bit_pos_in_word;
        bits -= 8 - stream->bit_pos_in_word;
        out_bits = 8 - stream->bit_pos_in_word;
      }

    }

    while (bits && out_bits < num_bits) {

      /* check emulation prevention byte */
      if (tmp_read_bits >= 16 &&
          (fn_read_byte(SwRingBufferProtect(strm, -2, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(SwRingBufferProtect(strm, -1, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0x2) {

        if (out_bits <= 24) {
          out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << (24 - out_bits);
        } else {
          out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) >> (out_bits - 24);
        }

        strm++;
        tmp_read_bits += 8;
        bits -= 8;
        out_bits += 6;
        out &=~((1<<(32-out_bits))-1);
      }
      else
      {
          if (out_bits <= 24) {
            out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << (24 - out_bits);
          } else {
            out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) >> (out_bits - 24);
          }

          strm++;
          tmp_read_bits += 8;
          bits -= 8;
          out_bits += 8;
      }
    }

    return (out >> (32 - num_bits));
  }
  else {
    u32 shift;

    /* at least 32-bits in the buffer */
    if (bits >= 32) {
      u32 bit_pos_in_word = stream->bit_pos_in_word;

      out = ((u32)(fn_read_byte(SwRingBufferProtect(strm, 3, stream), stream->strm_buff_size, stream->stream_info))) |
            ((u32)(fn_read_byte(SwRingBufferProtect(strm, 2, stream), stream->strm_buff_size, stream->stream_info)) << 8) |
            ((u32)(fn_read_byte(SwRingBufferProtect(strm, 1, stream), stream->strm_buff_size, stream->stream_info)) << 16) |
            ((u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << 24);

      if (bit_pos_in_word) {
        out <<= bit_pos_in_word;
        out |= (u32)(fn_read_byte(SwRingBufferProtect(strm, 4, stream), stream->strm_buff_size, stream->stream_info)) >> (8 - bit_pos_in_word);
      }

      return (out >> (32 - num_bits));
    }
    /* at least one bit in the buffer */
    else if (bits > 0) {
      shift = (i32)(24 + stream->bit_pos_in_word);
      out = (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << shift;
      strm++;
      bits -= (i32)(8 - stream->bit_pos_in_word);
      while (bits > 0) {
        shift -= 8;
        out |= (u32)(fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) << shift;
        strm++;
        bits -= 8;
      }
      return (out >> (32 - num_bits));
    } else
      return (0);
  }
}

u32 SwFlushBits(struct StrmData *stream, u32 num_bits) {
  u32 bytes_left;
  const u8 *strm, *strm_bak;
  u8 tmp_strm_buf[32], *tmp;
  i32 bits;
  u32 out_bits;
  u32 tmp_read_bits;
  SwReadByteFn *fn_read_byte;

  ASSERT(stream);
  ASSERT(stream->strm_buff_start);
  ASSERT(stream->strm_curr_pos);
  ASSERT(stream->bit_pos_in_word < 8);
  ASSERT(stream->bit_pos_in_word == (stream->strm_buff_read_bits & 0x7));

  strm = stream->strm_curr_pos;
  fn_read_byte = SwGetReadByteFunc(stream->stream_info);

  SwUpdateStrmDataSize(stream);

  bits = (i32)stream->strm_data_size * 8 - (i32)stream->strm_buff_read_bits;

  if (!bits) {
    return (END_OF_STREAM);
  }

  /* used to copy stream data when ringbuffer turnaround */
  if (stream->is_rb)
    tmp = SwTurnAround(stream->strm_curr_pos, stream->strm_buff_start,
                       tmp_strm_buf, stream->strm_buff_size,
                       MIN(bits, num_bits + stream->bit_pos_in_word + 32), stream->stream_info);
  else
    tmp = NULL;

  if(tmp != NULL)
    strm = tmp;

#ifdef STREAM_TRACE
  if (trace_stream_txt) {
    u32 i, bits, tmp_num_bits;
    tmp_num_bits = num_bits;
    flushed_bit_string[0] = '\0';
    while (tmp_num_bits > 32) {
      tmp_num_bits -= 32;
      bits = SwShowBits(stream, 32);
      for (i = 0; i < 32; i++) {
        strcat(flushed_bit_string, (bits & 0x80000000) ? "1" : "0");
        bits <<= 1;
      }
    }
    ASSERT(tmp_num_bits <= 32);
    bits = SwShowBits(stream, tmp_num_bits);
    bits <<= 32 - tmp_num_bits;
    for (i = 0; i < tmp_num_bits; i++) {
      strcat(flushed_bit_string, (bits & 0x80000000) ? "1" : "0");
      bits <<= 1;
    }
  }
#endif

  if (!stream->remove_emul3_byte) {
    if ((stream->strm_buff_read_bits + num_bits) >
        (8 * stream->strm_data_size)) {
      stream->strm_buff_read_bits = 8 * stream->strm_data_size;
      stream->bit_pos_in_word = 0;
      stream->strm_curr_pos = stream->strm_buff_start + stream->strm_buff_size;
      return (END_OF_STREAM);
    } else {
      bytes_left =
        (8 * stream->strm_data_size - stream->strm_buff_read_bits) / 8;
      if(tmp != NULL)
        strm = tmp;
      else
        strm = stream->strm_curr_pos;
      strm_bak = strm;

      if (stream->bit_pos_in_word) {
        if (num_bits < 8 - stream->bit_pos_in_word) {
          stream->strm_buff_read_bits += num_bits;
          stream->bit_pos_in_word += num_bits;
          return (HANTRO_OK);
        }
        num_bits -= 8 - stream->bit_pos_in_word;
        stream->strm_buff_read_bits += 8 - stream->bit_pos_in_word;
        stream->bit_pos_in_word = 0;
        strm++;

        if (stream->strm_buff_read_bits >= 16 && bytes_left &&
            (fn_read_byte(SwRingBufferProtect(strm, -2, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
            (fn_read_byte(SwRingBufferProtect(strm, -1, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
            (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0x3) {
          strm++;
          stream->strm_buff_read_bits += 8;
          bytes_left--;
          stream->emul_byte_count++;
        }
      }

      while (num_bits >= 8 && bytes_left) {
        if (bytes_left > 2 && (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0 &&
            (fn_read_byte(SwRingBufferProtect(strm, 1, stream), stream->strm_buff_size, stream->stream_info)) == 0 &&
            (fn_read_byte(SwRingBufferProtect(strm, 2, stream), stream->strm_buff_size, stream->stream_info)) <= 1) {
          /* trying to flush part of start code prefix -> error */
          /* need consum data: will hang if not consumed. */
          strm++;
          stream->strm_buff_read_bits += 8;
          bytes_left--;
          return (HANTRO_NOK);
        }

        strm++;
        stream->strm_buff_read_bits += 8;
        bytes_left--;

        /* check emulation prevention byte */
        if (stream->strm_buff_read_bits >= 16 && bytes_left &&
            (fn_read_byte(SwRingBufferProtect(strm, -2, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
            (fn_read_byte(SwRingBufferProtect(strm, -1, stream), stream->strm_buff_size, stream->stream_info))== 0x0 &&
            (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0x3) {
          strm++;
          stream->strm_buff_read_bits += 8;
          bytes_left--;
          stream->emul_byte_count++;
        }
        num_bits -= 8;
      }

      if (num_bits && bytes_left) {
        if (bytes_left > 2 && (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0 &&
            (fn_read_byte(SwRingBufferProtect(strm, 1, stream), stream->strm_buff_size, stream->stream_info)) == 0 &&
            (fn_read_byte(SwRingBufferProtect(strm, 2, stream), stream->strm_buff_size, stream->stream_info)) <= 1) {
          /* trying to flush part of start code prefix -> error */
          /* need consum data: will hang if not consumed. */
          strm++;
          stream->strm_buff_read_bits += 8;
          bytes_left--;
          return (HANTRO_NOK);
        }

        stream->strm_buff_read_bits += num_bits;
        stream->bit_pos_in_word = num_bits;
        num_bits = 0;
      }

      stream->strm_curr_pos += strm - strm_bak;
      if (stream->is_rb && stream->strm_curr_pos >= (stream->strm_buff_start + stream->strm_buff_size))
        stream->strm_curr_pos -= stream->strm_buff_size;

      if (num_bits)
        return (END_OF_STREAM);
      else
        return (HANTRO_OK);
    }
  }
  else if(stream->remove_avs_fake_2bits)
  {
    u32 bit_shift=0;
    u32 bytes_shift = 0;
    u32 bit_left = 0;
    out_bits = 0;
    tmp_read_bits = stream->strm_buff_read_bits;

    do
    {
      /* check emulation prevention byte */
      if (tmp_read_bits >= 16 &&
          (fn_read_byte(SwRingBufferProtect(strm, -2, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(SwRingBufferProtect(strm, -1, stream), stream->strm_buff_size, stream->stream_info)) == 0x0 &&
          (fn_read_byte(strm, stream->strm_buff_size, stream->stream_info)) == 0x2) {
        bit_left = (8 - (tmp_read_bits%8));
        if(num_bits>=out_bits+bit_left-2)
        {
            bit_shift +=2;
            out_bits += bit_left-2;
            strm++;
            tmp_read_bits += bit_left;
            bits -= bit_left;
        }
        else
        {
            tmp_read_bits += num_bits-out_bits;
            bits -= num_bits-out_bits;
            out_bits = num_bits;
        }

      }
      else
      {
        bit_left = (8 - (tmp_read_bits%8));
        if(num_bits>=out_bits+bit_left)
        {
            out_bits += bit_left;
            strm++;
            tmp_read_bits += bit_left;
            bits -= bit_left;
        }
        else
        {
            tmp_read_bits += num_bits-out_bits;
            bits -= num_bits-out_bits;
            out_bits = num_bits;
        }
      }

    }while(out_bits < num_bits && bits > 0);

    bytes_shift = (stream->bit_pos_in_word + num_bits + bit_shift) >> 3;
    stream->strm_buff_read_bits += num_bits + bit_shift;
    stream->bit_pos_in_word = stream->strm_buff_read_bits & 0x7;
    if ((stream->strm_buff_read_bits) <= (8 * stream->strm_data_size)) {
      stream->strm_curr_pos += bytes_shift;
      if (stream->is_rb && stream->strm_curr_pos >= (stream->strm_buff_start + stream->strm_buff_size))
        stream->strm_curr_pos -= stream->strm_buff_size;
      return (HANTRO_OK);
    } else
      return (END_OF_STREAM);
  }
  else {
    u32 bytes_shift = (stream->bit_pos_in_word + num_bits) >> 3;
    stream->strm_buff_read_bits += num_bits;
    stream->bit_pos_in_word = stream->strm_buff_read_bits & 0x7;
    if ((stream->strm_buff_read_bits) <= (8 * stream->strm_data_size)) {
      stream->strm_curr_pos += bytes_shift;
      if (stream->is_rb && stream->strm_curr_pos >= (stream->strm_buff_start + stream->strm_buff_size))
        stream->strm_curr_pos -= stream->strm_buff_size;
      return (HANTRO_OK);
    } else
      return (END_OF_STREAM);
  }
}

u32 SwIsByteAligned(const struct StrmData *stream) {

  if (!stream->bit_pos_in_word)
    return (HANTRO_TRUE);
  else
    return (HANTRO_FALSE);
}

u8 SwNoLatencyReadByte(const u8 *p, u32 size, struct strmInfo *stream_info) {
  (void)size;
  stream_info = NULL;
  return DWLReadByte(p);
}

u8 SwLowLatencyReadByte(const u8 *p, u32 buf_size, struct strmInfo *stream_info) {
  u32 len = 0;
  if (!stream_info)
    return 0xFF;
  do {
    if (p >= stream_info->strm_vir_start_addr)
      len = p - stream_info->strm_vir_start_addr;
    else
      len = buf_size + p - stream_info->strm_vir_start_addr;
    sched_yield();
  } while ((len > stream_info->send_len) && !stream_info->last_flag);

  if (stream_info->last_flag && len > stream_info->send_len)
    return 0xFF;
  return DWLReadByte(p);
}

SwReadByteFn *SwGetReadByteFunc(struct strmInfo *stream_info) {
  if (stream_info && stream_info->low_latency) {
    return SwLowLatencyReadByte;
  }
  return SwNoLatencyReadByte;
}

void SwUpdateStrmDataSize(struct StrmData *stream){
  if (stream->stream_info && stream->stream_info->low_latency && stream->stream_info->last_flag)
    stream->strm_data_size = stream->stream_info->send_len;
}

#ifdef STREAM_TRACE
void SwStreamTraceOpen() {
  /* Code */
  if (!trace_stream_txt) {
    trace_stream_txt = fopen("sw_stream.txt", "w");
  }
}

void SwStreamTrace(char *format, ...) {

  /* Variables */
  va_list ap;

  char tmp[128], final_format[128] = "", *ptr, length_string[13] = {0};
  u32 i, length;

  /* Code */
  if (trace_stream_txt) {
    va_start(ap, format);

    strcpy(tmp, format);
    i = 0;
    ptr = strtok(tmp, "%");
    if (ptr == tmp) {
      /* No "%x" found in input format, which means just to print a simple string */
      fprintf(trace_stream_txt,"%s\n", ptr);
      return;
    }
    while (ptr != NULL) {
      sprintf(length_string, "%s-%u", "%", i > 0 ? 6 : 64);
      strcat(final_format, length_string);
      strcat(final_format, ptr);
      ptr = strtok(NULL, "%");
      i++;
    }

    vfprintf(trace_stream_txt, final_format, ap);

    /* print empty fields if only two or three fields printed */
    while (i < 4) {
      i++;
      fprintf(trace_stream_txt,"%-6s", "");
    }

    fprintf(trace_stream_txt,"%-17s", flushed_bit_string);

    /* print flushed bit string length */
    length = strlen(flushed_bit_string);
    if (length) {
      sprintf(length_string, "[%u]", length);
      fprintf(trace_stream_txt,"%s", length_string);
    }

    fprintf(trace_stream_txt, "\n");
    fflush(trace_stream_txt);

    /* reset flushed bit string */
    flushed_bit_string[0] = '\0';

    va_end(ap);
  }
}

void SwStreamTraceClose() {
  if (trace_stream_txt) {
    fclose(trace_stream_txt);
    trace_stream_txt = NULL;
  }
}
#else
void SwStreamTraceOpen() {}
void SwStreamTrace(char *format, ...) {}
void SwStreamTraceClose() {}
#endif
