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

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include "basetype.h"
#include "sw_util.h"
#include "dwl.h"

/* function: generate fake table */
#ifdef USE_FAKE_RFC_TABLE
void GenerateFakeRFCTable(u8 *cmp_tble_addr,
                          u32 pic_width_in_cbsy,
                          u32 pic_height_in_cbsy,
                          u32 pic_width_in_cbsc,
                          u32 pic_height_in_cbsc,
                          u32 bit_depth,
                          u32 buffer_align);
#endif

#ifdef CASE_INFO_STAT
/* dec mode */
#define DEC_MODE_H264      0
#define DEC_MODE_MPEG4     1
#define DEC_MODE_H263      2
#define DEC_MODE_JPEG      3
#define DEC_MODE_VC1       4
#define DEC_MODE_MPEG2     5
#define DEC_MODE_MPEG1     6
#define DEC_MODE_VP6       7
#define DEC_MODE_RV        8
#define DEC_MODE_VP7       9
#define DEC_MODE_VP8       10
#define DEC_MODE_AVS       11
#define DEC_MODE_HEVC      12
#define DEC_MODE_VP9       13
#define DEC_MODE_H264_H10P 15
#define DEC_MODE_AVS2      16
#define DEC_MODE_AV1       17
#define DEC_MODE_VVC       18

typedef struct {
  u32 codec;
  u32 format;
  u32 display_width;
  u32 display_height;
  u32 decode_width;
  u32 decode_height;
  u32 frame_type[20];
  u32 scan_count;
  u32 slice_num[10];
  u32 pp_input_luma_size;
  u32 chroma_format_id;
  u8 depth_flag;
  u8 resolution_flag;
  u8 chroma_flag;
  u8 bit_depth;
  u32 frame_num;
  u8 crop_flag;
  u32 bitrate;
  u8 b_slice_flag;
  u8 p_slice_flag;
  u8 interlace_flag;
  u8 intrabc_flag;
  u8 tile_flag;
  u8 aso_flag;
  u8 fmo_flag;
  u8 pjpeg_flag;
  u8 thumb_flag;
  u8 cavlc_flag;
  u8 interintra;
  u8 palette_mode;
  u8 filter_intra_pred;
  u8 intra_edge_filter;
  u32 fieldmode[10];
  u32 fieldpic_flag[10];
  u32 num_tile_cols_8k[10];
  u32 blackwhite_e[10];
  u32 bit_depth_y_minus8[10];
  u32 bit_depth_c_minus8[10];
  u32 ppin_luma_size[10];
  u32 pic_width_in_cbs;
  u32 pic_height_in_cbs;
  u32 min_cb_size;
  u32 max_cb_size;
  u32 crop_x;
  u32 crop_y;
}CaseInfo;

enum{
  I_FRAME,
  B_FRAME,
  P_FRAME,
  GB_FRAME,
  F_FRAME,
  S_FRAME,
  G_FRAME,
  FI_FRAME,
  BI_FRAME,
  FIELD_I_I,
  FIELD_I_P,
  FIELD_P_I,
  FIELD_P_P,
  FIELD_B_B,
  FIELD_B_BI,
  FIELD_BI_B,
  FIELD_BI_BI,
  I_FIELED_0,
  P_FIELED_0,
  B_FIELED_0,
  I_FIELED_1,
  P_FIELED_1,
  B_FIELED_1,
};
#endif

#ifdef FPGA_PERF_AND_BW
typedef struct DWLPerfInfo DecPerfInfo;

void DecPerfInfoCount(u32 core_id, DecPerfInfo* perf_info, u64 pic_size, u32 bit_depth);
void AveragePerfInfoPrint(DecPerfInfo *perf_info);
#endif

#ifdef OPEN_HWCFG_TO_CLIENT
void GetHwConfig(const void *hw_feature, struct DecHwConfig *hw_cfg);
#endif

#endif /* COMMON_FUNCTION_H */
