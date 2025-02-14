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

#ifndef ERRORHANDLING_H_DEFINED
#define ERRORHANDLING_H_DEFINED

#include "basetype.h"
#include "decapicommon.h"

/* VP9: SB_size = 64x64, MB_size = 16x16 */
#define MB_NUM_IN_SB 16

// #define EC_MAX_TILE_COLS 20
// #define EC_MAX_TILE_ROWS 22

/* indicates unavailable value */
#define EC_INVALID_IDX -1
/* Avoid decimal arithmetic */
#define EC_ROUND_COEFF 10000
/* Reference frame error ratio threshold, default 10%. */
#define EC_RATIO_THRESHOLD 10 * 100

/* Similar to TileInfo structure in HEVC. */
/* TODO(min): use one structure as TileInfo instead. */
struct PicTileInfo {
  u32 num_tile_columns;
  u32 num_tile_rows;
  u32 uniform_spacing;
  u32 *col_width;
  u32 *row_height;
};
/* used to calculate correct error mb/ctb number when decoding error happens. */
struct ErrorPicInfo {
  u32 error_x;
  u32 error_y;
  u32 pic_width_in_ctb;
  u32 pic_height_in_ctb;
  int log2_ctb_size;
  struct PicTileInfo tile_info;
};
/**
 * \enum ECDataState
 * \brief State of error conceal operation.
 * \ingroup common_group
 */
enum ECDataState {
  EC_STATE_NONE = 0,
  EC_STATE_REPLACE,
  EC_STATE_DISCARD,
  EC_STATE_SEEK,
};

/**
 * \enum ErrorPolicy
 * \brief Error Process Policy.
 * \ingroup common_group
 */
enum ErrorPolicy {
  /* Current pic EC policy */
  DEC_EC_PIC_HWEC = 0x1, /**< Use HW EC(HEVC/H264 only) */
  DEC_EC_PIC_NO_RECOVERY = 0x2, /**< Do nothing for the data in current picture buffer */
  /* Reference pic EC policy */
  DEC_EC_REF_REPLACE = 0x10, /**< If ref error detected, relpace it with nearest correct ref picture in POC distance.
                                  If not find, seek next I frame. */
  DEC_EC_REF_REPLACE_ANYWAY = 0x20, /**< If ref error detected, relpace it with nearest correct ref picture in POC distance.
                                         If not file, use FAKE REF & FAKE TABEL.(RFC only) */
  DEC_EC_REF_ERROR_IGNORE = 0x40, /**< If ref error detected, use as a normal ref.(ignore any error info) */
  DEC_EC_REF_RESET = 0x80, /**< If ref error detected, Reset DPB buffer for the next I pic.(DEC_EC_SEEK_NEXT_I only) */
  /* Follow-up pic EC policy */
  DEC_EC_SEEK_NEXT_I = 0x100, /**< If error detected, mark follow-up pic as erroneous directly until a new I pic. */
  DEC_EC_NO_SKIP = 0x200, /**< If error detected, follow-up pic decode normaly. */
  /* Output pic EC policy */
  DEC_EC_OUT_ALL = 0x1000, /**< Output all pictures including the picture marked as erroneous picture. */
  DEC_EC_OUT_NO_ERROR = 0x2000, /**< Output correct pictures, other pictures are discarded. */
  DEC_EC_OUT_DECISION = 0x4000 /**< Output correct pictures and the pictures contain correct 1st field, other pictures are discarded. */
  // DEC_EC_OUT_FIRST_FIELD_OK = 0x4000, /* Always enable when DEC_EC_OUT_DECISION enable.(interlace or mvc case only) */
};
int GetErrorCtbCount(struct ErrorPicInfo *error_pic_info);

/* print error info of EC */
void ECErrorInfoReturn(enum DecErrorInfo error_info, u32 error_ratio, u32 pic_id);

u32 IsECDropOutput(const u32 policy, const u32 scale,
    enum DecErrorInfo info, u32 ratio);

void SetECPolicy(const enum DecErrorHandling error_handling,
                 const u32 is_hw_conceal, u32 *policy);

u32 getG1OutDataErrorRatio(u32 width, u32 height, u32 error_x, u32 error_y);

void PreparePartialFreeze(u8 *dec_out, u32 vop_width, u32 vop_height);
u32 ProcessPartialFreeze(u8 *dec_out, const u8 *ref_pic, u32 vop_width,
                         u32 vop_height, u32 copy);
u32  GetPartialFreezePos( u8 * dec_out, u32 vop_width, u32 vop_height);

#endif /* ERRORHANDLING_H_DEFINED */
