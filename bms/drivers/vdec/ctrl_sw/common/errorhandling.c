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

#include "errorhandling.h"
#include "dwl.h"
#include "deccfg.h"
#include "sw_util.h"
#include "dec_log.h"

#define MAGIC_WORD_LENGTH (8)

static const u8 magic_word[MAGIC_WORD_LENGTH] = "Rosebud\0";

#define NUM_OFFSETS 6

static const u32 row_offsets[] = {1, 2, 4, 8, 12, 16};

static u32 GetMbOffset(u32 mb_num, u32 vop_width, u32 vop_height);

u32 GetMbOffset(u32 mb_num, u32 vop_width, u32 vop_height) {
  u32 mb_row, mb_col;
  u32 offset;
  UNUSED(vop_height);

  mb_row = mb_num / vop_width;
  mb_col = mb_num % vop_width;
  offset = mb_row * 16 * 16 * vop_width + mb_col * 16;

  return offset;
}

/* Copy num_rows bottom mb rows from ref_pic to dec_out. */
void CopyRows(u32 num_rows, u8 *dec_out, const u8 *ref_pic, u32 vop_width,
              u32 vop_height) {

  u32 pix_width;
  u32 offset;
  u32 luma_size;
  u8 *src;
  u8 *dst;

  pix_width = 16 * vop_width;

  offset = (vop_height - num_rows) * 16 * pix_width;
  luma_size = 256 * vop_width * vop_height;

  dst = dec_out;
  src = (u8 *)ref_pic;

  dst += offset;
  src += offset;

  if (ref_pic)
    DWLmemcpy(dst, src, num_rows * 16 * pix_width);
  else
    DWLmemset(dst, 0, num_rows * 16 * pix_width);

  /* Chroma data */
  offset = (vop_height - num_rows) * 8 * pix_width;

  dst = dec_out;
  src = (u8 *)ref_pic;

  dst += luma_size;
  src += luma_size;
  dst += offset;
  src += offset;

  if (ref_pic)
    DWLmemcpy(dst, src, num_rows * 8 * pix_width);
  else
    DWLmemset(dst, 128, num_rows * 8 * pix_width);
}

void PreparePartialFreeze(u8 *dec_out, u32 vop_width, u32 vop_height) {

  u32 i, j;
  u8 *base;

  if (dec_out == NULL)
  	return;

  for (i = 0; i < NUM_OFFSETS && row_offsets[i] < vop_height / 4 &&
       row_offsets[i] <= DEC_X170_MAX_EC_COPY_ROWS;
       i++) {
    base = dec_out + GetMbOffset(vop_width * (vop_height - row_offsets[i]),
                                 vop_width, vop_height);

    for (j = 0; j < MAGIC_WORD_LENGTH; ++j) base[j] = magic_word[j];
  }
}

u32 ProcessPartialFreeze(u8 *dec_out, const u8 *ref_pic, u32 vop_width,
                         u32 vop_height, u32 copy) {

  u32 i, j;
  u8 *base;
  //u32 num_mbs;
  u32 match = HANTRO_TRUE;

  if (dec_out == NULL)
  	return HANTRO_FALSE;

  if (ref_pic == NULL)
  	return HANTRO_FALSE;

  //num_mbs = vop_width * vop_height;

  for (i = 0; i < NUM_OFFSETS && row_offsets[i] < vop_height / 4 &&
       row_offsets[i] <= DEC_X170_MAX_EC_COPY_ROWS;
       i++) {
    base = dec_out + GetMbOffset(vop_width * (vop_height - row_offsets[i]),
                                 vop_width, vop_height);

    for (j = 0; j < MAGIC_WORD_LENGTH && match; ++j)
      if (base[j] != magic_word[j]) match = HANTRO_FALSE;

    if (!match) {
      if (copy)
        CopyRows(row_offsets[i], dec_out, ref_pic, vop_width, vop_height);
      return HANTRO_TRUE;
    }
  }

  return HANTRO_FALSE;
}

u32  GetPartialFreezePos( u8 * dec_out, u32 vop_width, u32 vop_height) {

  u32 i, j;
  u8 * base;
  u32 pos = vop_width * vop_height;
  u8 decoding_pos_found = 0;

  for (i = 0; i < NUM_OFFSETS && row_offsets[i] < vop_height/4 &&
       row_offsets[i] <= DEC_X170_MAX_EC_COPY_ROWS; i++) {
    base = dec_out + GetMbOffset(vop_width * (vop_height - row_offsets[i]),
                                     vop_width, vop_height );

    for( j = 0 ; j < MAGIC_WORD_LENGTH; ++j )
      if( base[j] != magic_word[j] ) {
        decoding_pos_found = 1;
        break;
      }

    if (decoding_pos_found) {
      if( i != 0)
        pos = row_offsets[i-1] * vop_width;
      else
        pos = 0;

      break;
    }
  }

  return pos;
}

int GetErrorCtbCount(struct ErrorPicInfo *error_pic_info) {
  u32 ctb_x = 0;
  u32 ctb_y = 0;
  u32 tile_x = 0;
  u32 tile_y = 0;
  u32 tile_ctb_x = 0;
  u32 tile_ctb_y = 0; /* starting ctb of current tile */
  u32 pic_width_in_ctb = 0;
  u32 pic_height_in_ctb = 0;
  struct PicTileInfo *tile_info = NULL;
  u32 good_ctb_num = 0;

  ctb_x = error_pic_info->error_x >> error_pic_info->log2_ctb_size;
  ctb_y = error_pic_info->error_y >> error_pic_info->log2_ctb_size;
  pic_width_in_ctb = error_pic_info->pic_width_in_ctb;
  pic_height_in_ctb = error_pic_info->pic_height_in_ctb;
  tile_info = &error_pic_info->tile_info;

  if (tile_info == NULL ||
      (tile_info->num_tile_columns == 1 && tile_info->num_tile_rows == 1)) {
    /* Only one tile: such as legacy formats or H264. */
    return (pic_width_in_ctb * pic_height_in_ctb - (ctb_y * pic_width_in_ctb + ctb_x));
  }

  tile_ctb_y = 0;
  for (tile_y = 0; tile_y < tile_info->num_tile_rows; tile_y++) {
    tile_ctb_x = 0;
    for (tile_x = 0; tile_x < tile_info->num_tile_columns; tile_x++) {
      /* in current tile */
      if (ctb_x >= tile_ctb_x &&
          ctb_x <  tile_ctb_x + tile_info->col_width[tile_x] &&
          ctb_y >= tile_ctb_y &&
          ctb_y <  tile_ctb_y + tile_info->row_height[tile_y]) {
        /* error in current tile */
        good_ctb_num += (ctb_y - tile_ctb_y) * tile_info->col_width[tile_x] +
                        (ctb_x - tile_ctb_x);
        return (pic_width_in_ctb * pic_height_in_ctb) - good_ctb_num;
      }
      tile_ctb_x += tile_info->col_width[tile_x];
      good_ctb_num += tile_info->col_width[tile_x] * tile_info->row_height[tile_y];
    }
    tile_ctb_y += tile_info->row_height[tile_y];
  }

  return(0);
}

/* function: decide whether need discard current picture */
u32 IsECDropOutput(const u32 policy, const u32 tolerate_ratio,
                   enum DecErrorInfo info, u32 output_ratio) {
  u32 discard_pic = 0;
  u32 con1 = (policy & DEC_EC_OUT_NO_ERROR) && (info != DEC_NO_ERROR);
  u32 con2 = ((policy & DEC_EC_OUT_DECISION) &&
              (info != DEC_NO_ERROR) && (output_ratio > tolerate_ratio * 100));

  discard_pic = con1 || con2;
  return discard_pic;
}

void SetECPolicy(const enum DecErrorHandling error_handling,
                 const u32 is_hw_conceal, u32 *policy) {

  if (error_handling == DEC_EC_FRAME_TOLERANT_ERROR) {
    if (is_hw_conceal)
      *policy = DEC_EC_PIC_HWEC | DEC_EC_REF_ERROR_IGNORE | DEC_EC_NO_SKIP | DEC_EC_OUT_DECISION;
    else
      *policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_REPLACE | DEC_EC_NO_SKIP | DEC_EC_OUT_DECISION;
  } else if (error_handling == DEC_EC_FRAME_IGNORE_ERROR) {
    if (is_hw_conceal)
      *policy = DEC_EC_PIC_HWEC | DEC_EC_REF_ERROR_IGNORE | DEC_EC_NO_SKIP | DEC_EC_OUT_ALL;
    else
      *policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_REPLACE_ANYWAY | DEC_EC_NO_SKIP | DEC_EC_OUT_ALL;
  } else if (error_handling == DEC_EC_FRAME_NO_ERROR) { /* DEC_EC_FRAME_NO_ERROR */
    *policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_RESET | DEC_EC_SEEK_NEXT_I | DEC_EC_OUT_NO_ERROR;
  } else {  /* Defualt as DEC_EC_FRAME_NO_ERROR */
    APITRACEERR("SetECPolicy# EC Error: Get wrongly error_handling value %d\n", error_handling);
    *policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_RESET | DEC_EC_SEEK_NEXT_I | DEC_EC_OUT_NO_ERROR;
  }
}

/* print error info of EC */
void ECErrorInfoReturn(enum DecErrorInfo error_info, u32 error_ratio, u32 pic_id) {
  double ratio = error_ratio / 100.00;
  if (error_ratio > 0) {
    if (error_info & DEC_NALU_HEADER_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_NALU_HEADER_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & DEC_SLICE_HEADER_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_SLICE_HEADER_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & DEC_SLICE_DATA_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_SLICE_DATA_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & DEC_SYNC_WORD_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_SYNC_WORD_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & DEC_TRAILING_BITS_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_TRAILING_BITS_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & DEC_POLLING_STREAM_LEN_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_POLLING_STREAM_LEN_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & DEC_FRAME_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_FRAME_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
  } else {
    if (error_info & DEC_REF_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get DEC_REF_ERROR \
with error_ratio = %.2f%%\n", pic_id, ratio);
    if (error_info & ~DEC_REF_ERROR)
      APITRACEERR("xxxDecNextPicture# EC Error: PIC %d (decode order) get error_info = 0x%x \
with error_ratio = %.2f%%\n", pic_id, error_info, ratio);
  }
  return;
}

static void PrepareG1ErrPicInfo(u32 error_x, u32 error_y,
    u32 width, u32 height,
    struct ErrorPicInfo *error_pic_info)
{
  error_pic_info->error_x = error_x;
  error_pic_info->error_y = error_y;
  error_pic_info->pic_width_in_ctb  = NEXT_MULTIPLE(width, 16) >> 4;
  error_pic_info->pic_height_in_ctb = NEXT_MULTIPLE(height, 16) >> 4;
  error_pic_info->log2_ctb_size = 4;
  error_pic_info->tile_info.num_tile_rows    = 1; //no tile info for g1 format
  error_pic_info->tile_info.num_tile_columns = 1;
}

u32 getG1OutDataErrorRatio(u32 width, u32 height, u32 error_x, u32 error_y) {
  struct ErrorPicInfo error_pic_info = {0};
  u32 error_ratio = 0;
  u32 total_mbs = (NEXT_MULTIPLE(width, 16) * NEXT_MULTIPLE(height, 16)) >> 8;

  PrepareG1ErrPicInfo(error_x, error_y,
                      width, height,
                      &error_pic_info);

  u32 nbr_err_mbs = GetErrorCtbCount(&error_pic_info);
  if (nbr_err_mbs == 0 ) {
    nbr_err_mbs = total_mbs;
  }

  error_ratio = (nbr_err_mbs) * EC_ROUND_COEFF / total_mbs;
  return error_ratio;
}

