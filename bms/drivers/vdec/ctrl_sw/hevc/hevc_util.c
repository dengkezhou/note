/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
--         Copyright (c) 2011-2014, Google Inc. All rights reserved.          --
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

#include "hevc_util.h"

static u32 MoreRbspTrailingData(struct StrmData *stream);

u32 HevcRbspTrailingBits(struct StrmData *stream) {

  u32 stuffing;
  u32 stuffing_length;

  ASSERT(stream);
  ASSERT(stream->bit_pos_in_word < 8);

  stuffing_length = 8 - stream->bit_pos_in_word;

  stuffing = SwGetBits(stream, stuffing_length);
  if (stuffing == END_OF_STREAM) return (HANTRO_NOK);

  return (HANTRO_OK);
}

u32 MoreRbspTrailingData(struct StrmData *stream) {

  i32 bits;

  ASSERT(stream);
  //TODO: This assert is necessary?
  //ASSERT(stream->strm_buff_read_bits <= 8 * stream->strm_data_size);

  bits = (i32)stream->strm_data_size * 8 - (i32)stream->strm_buff_read_bits;
  if (bits >= 8)
    return (HANTRO_TRUE);
  else
    return (HANTRO_FALSE);
}

u32 HevcMoreRbspData(struct StrmData *stream) {

  u32 bits;

  ASSERT(stream);
  ASSERT(stream->strm_buff_read_bits <= 8 * stream->strm_data_size);

  bits = stream->strm_data_size * 8 - stream->strm_buff_read_bits;

  if (bits == 0) return (HANTRO_FALSE);

  if (bits > 8) {
    if (stream->remove_emul3_byte) return (HANTRO_TRUE);

    bits &= 0x7;
    if (!bits) bits = 8;
    if (SwShowBits(stream, bits) != (1U << (bits - 1)) ||
        (SwShowBits(stream, 23 + bits) << 9))
      return (HANTRO_TRUE);
    else
      return (HANTRO_FALSE);
  } else if (SwShowBits(stream, bits) != (1U << (bits - 1)))
    return (HANTRO_TRUE);
  else
    return (HANTRO_FALSE);
}

u32 HevcCheckCabacZeroWords(struct StrmData *strm_data) {

  u32 tmp;

  ASSERT(strm_data);

  if (MoreRbspTrailingData(strm_data)) {
    tmp = SwGetBits(strm_data, 16);
    if (tmp == END_OF_STREAM)
      return HANTRO_OK;
    else if (tmp == 0xFFFF) {
      /* Workaround: some testing streams use 0xFFFF instead of 0x0000
       * as cabac_zero_words, which is not completely compatable with spec. */
      return HANTRO_OK;
    }
    else if (tmp)
      return HANTRO_NOK;
  }

  return HANTRO_OK;
}

void HevcGetRefFrmSize(struct HevcDecContainer *dec_cont,
                       u32 *luma_size, u32 *chroma_size,
                       u32 *rfc_luma_size, u32 *rfc_chroma_size) {
  struct Storage *storage = &dec_cont->storage;
  struct SeqParamSet *sps = storage->active_sps;
  u32 tbl_sizey, tbl_sizec;

  u32 out_w, out_h;
  u32 ref_size;
  u32 pixel_width = (sps->bit_depth_luma == 8 && sps->bit_depth_chroma == 8) ? 8 : 10;

#if 0
  /* TODO: next cb or ctb multiple? */
  u32 pic_width_in_ctbs =
    (sps->pic_width + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
  u32 pic_height_in_ctbs =
    (sps->pic_height + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
#endif

  out_w = NEXT_MULTIPLE(4 * sps->pic_width * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
  out_h = sps->pic_height / 4;
  ref_size = out_w * out_h;
  if (dec_cont->skip_non_intra && dec_cont->pp_enabled)
    ref_size = 0;

  if (luma_size) *luma_size = ref_size;

  if (chroma_size) {
    if (!sps->mono_chrome) {
      if (sps->chroma_format_idc == 1)
        *chroma_size = ref_size / 2;
      else if (sps->chroma_format_idc == 2)
        *chroma_size = ref_size;
      else if (sps->chroma_format_idc == 3)
        *chroma_size = ref_size * 2;
    }
    else                    *chroma_size = 0;
  }

  /* buffer size of dpb pic = pic_size + dir_mv_size + tbl_size */
#if 0
  u32 dmv_mem_size =
    /* num ctbs */
    (pic_width_in_ctbs * pic_height_in_ctbs *
     /* num 16x16 blocks in ctbs */
     (1 << (2 * (sps->log_max_coding_block_size - 4))) *
     /* num bytes per 16x16 */
     16);
  ref_size = NEXT_MULTIPLE(ref_size * 3 / 2, 16) + dmv_mem_size;
#endif

  if (storage->use_video_compressor) {
    u32 pic_width_in_cbsy, pic_height_in_cbsy;
    u32 pic_width_in_cbsc, pic_height_in_cbsc;
    pic_width_in_cbsy = ((sps->pic_width + 8 - 1)/8);
    pic_width_in_cbsy = NEXT_MULTIPLE(pic_width_in_cbsy, 16);
    pic_height_in_cbsy = (sps->pic_height + 8 - 1)/8;
    if (sps->chroma_format_idc == 1) {
      pic_width_in_cbsc = ((sps->pic_width + 16 - 1)/16);
      pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
      pic_height_in_cbsc = (sps->pic_height / 2 + 4 - 1)/4;
    } else if (sps->chroma_format_idc == 2) {
      pic_width_in_cbsc = ((sps->pic_width + 16 - 1)/16);
      pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
      pic_height_in_cbsc = (sps->pic_height + 4 - 1)/4;
    } else/*if (sps->chroma_format_idc == 3)*/ {
      pic_width_in_cbsc = ((sps->pic_width * 2 + 16 - 1)/16);
      pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
      pic_height_in_cbsc = (sps->pic_height + 4 - 1)/4;
    }

    /* luma table size */
    tbl_sizey = NEXT_MULTIPLE(pic_width_in_cbsy * pic_height_in_cbsy, 16);
    tbl_sizec = NEXT_MULTIPLE(pic_width_in_cbsc * pic_height_in_cbsc, 16);
  } else
    tbl_sizey = tbl_sizec = 0;

  if (rfc_luma_size) *rfc_luma_size = tbl_sizey;
  if (rfc_chroma_size) {
    if (!sps->mono_chrome)  *rfc_chroma_size = tbl_sizec;
    else                    *rfc_chroma_size = 0;
  }
}
