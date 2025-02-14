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

#include "commonfunction.h"
#include "dec_log.h"
#include "vpufeature.h"
#include <memory.h>

/* function: generate fake table */
#ifdef USE_FAKE_RFC_TABLE
void GenerateFakeRFCTable(u8 *cmp_tble_addr,
                          u32 pic_width_in_cbsy,
                          u32 pic_height_in_cbsy,
                          u32 pic_width_in_cbsc,
                          u32 pic_height_in_cbsc,
                          u32 bit_depth,
                          u32 buffer_align) {
  u8 cbs_size_y = 0, cbs_size_c = 0;
  u8 ec_word_align = 1;
#ifdef FAKE_RFC_TBL_LITTLE_ENDIAN
  u8 cbs_sizes_8bit[14] = {64, 32, 16, 8, 4, 2, 129, 64, 32, 16, 8, 4, 2, 129};
  u8 cbs_sizes_10bit[14] = {80, 40, 20, 10, 0x85, 0x42, 0xa1, 80, 40, 20, 10, 0x85, 0x42, 0xa1};
#else
  u8 cbs_sizes_8bit[14] = {129, 2, 4, 8, 16, 32, 64, 129, 2, 4, 8, 16, 32, 64};
  u8 cbs_sizes_10bit[14] = {0xa1, 0x42, 0x85, 10, 20, 40, 80, 0xa1, 0x42, 0x85, 10, 20, 40, 80};
#endif
  u32 i, j, offset;
  u8 *pcbs, *ptbl = NULL;
  if (bit_depth == 8) {
    cbs_size_y = cbs_size_c = 64;
    ptbl = cbs_sizes_8bit;
  } else if (bit_depth == 10) {
    cbs_size_y = cbs_size_c = 80;
    ptbl = cbs_sizes_10bit;
  }
  /*
  LOG(SDK_DEBUG_OUT, "%s#  0x%08x Y: (%d x %d), C: (%d x %d) bitdepth %d\n",
              __FUNCTION__,
              cmp_tble_addr,
              pic_width_in_cbsy,
              pic_height_in_cbsy,
              pic_width_in_cbsc,
              pic_height_in_cbsc,
              bit_depth);
  */

  // Compression table for Y
  pcbs = cmp_tble_addr;
  for (i = 0; i < pic_height_in_cbsy; i++) {
    offset = 0;
    for (j = 0; j < pic_width_in_cbsy/16; j++) {
#ifdef FAKE_RFC_TBL_LITTLE_ENDIAN
      *(u16 *)pcbs = offset;
      if (ptbl != NULL) memcpy(pcbs+2, ptbl, 14);
#else
      if (ptbl != NULL) memcpy(pcbs, ptbl, 14);
      *(pcbs+14) = offset >> 8;
      *(pcbs+15) = offset & 0xff;
#endif
      pcbs += 16;
      offset += (16 * cbs_size_y) >> ec_word_align;
    }
  }

  pcbs = cmp_tble_addr +
    NEXT_MULTIPLE(pic_height_in_cbsy * pic_width_in_cbsy, buffer_align);

  // Compression table for C
  for (i = 0; i < pic_height_in_cbsc; i++) {
    offset = 0;
    for (j = 0; j < pic_width_in_cbsc/16; j++) {
#ifdef FAKE_RFC_TBL_LITTLE_ENDIAN
      *(u16 *)pcbs = offset;
      if (ptbl != NULL) memcpy(pcbs+2, ptbl, 14);
#else
      if (ptbl != NULL) memcpy(pcbs, ptbl, 14);
      *(pcbs+14) = offset >> 8;
      *(pcbs+15) = offset & 0xff;
#endif
      pcbs += 16;
      offset += (16 * cbs_size_c) >> ec_word_align;
    }
  }

  /*
    u8 *p = cmp_tble_addr;
    printf("Fake RFC table:\n");
    for (i = 0; i < 8; i++) {
      printf("0x%02x 0x%02x 0x%02x 0x%02x ", p[0], p[1], p[2], p[3]);
      p += 4;
    }
    printf("\n");
  */
}
#endif
#ifdef CASE_INFO_STAT
CaseInfo case_info;
#endif

#ifdef FPGA_PERF_AND_BW
#define DEBUG_PRINT(str) printf str


void DecPerfInfoCount(u32 core_id, DecPerfInfo* perf_info, u64 pic_size, u32 bit_depth) {
  struct DWLPerfInfo perf_count;
  u32 mbs;

  DWLPerfInfoCollect(core_id, &perf_count);

  if(perf_count.bitrate)
    perf_count.bitrate = 60 * perf_count.bitrate * 8 * 3840 * 2160 / pic_size / 1024 / 1024  ;
  mbs = pic_size >> 8;
  if(mbs)
    perf_count.cycles = perf_count.cycles / mbs;
  perf_count.read_bw = perf_count.read_bw * 16 * 1000 / pic_size;
  perf_count.write_bw = perf_count.write_bw * 16 * 1000 / pic_size;
  if(bit_depth == 10) {
    perf_count.read_bw = perf_count.read_bw * 8 / 10;
    perf_count.write_bw = perf_count.write_bw * 8 / 10 ;
  } else if ( bit_depth == 12) {
    perf_count.read_bw = perf_count.read_bw * 8 / 12;
    perf_count.write_bw = perf_count.write_bw * 8 /12;
  }

  PERFTRACE_I("PIC_ID %d , %4d Mbps (4k@60fps),%4d cycles / mb, BW R/W: %0.3f/%0.3f (x FRAME)\n",
              perf_info->pic_num + 1, (u32)perf_count.bitrate,
              perf_count.cycles, (double)perf_count.read_bw/ 1000 / 1.5,
              (double)perf_count.write_bw/ 1000 / 1.5);


  perf_info->bitrate += perf_count.bitrate;
  perf_info->read_bw += perf_count.read_bw;
  perf_info->write_bw += perf_count.write_bw;
  perf_info->cycles += perf_count.cycles;
  perf_info->pic_num ++;
}

void AveragePerfInfoPrint(DecPerfInfo *perf_info) {
  PERFTRACE_I("Average bitrate/frame (4k@60fps): %4d Mbps, Average cycles/MB: %4d, Average BW R/W (x FRAME): %0.3f / %0.3f , %0.3f \n",
              (u32)(perf_info->bitrate/perf_info->pic_num), perf_info->cycles/perf_info->pic_num,
              (double)perf_info->read_bw / perf_info->pic_num / 1000 / 1.5,
              (double)perf_info->write_bw / perf_info->pic_num / 1000 / 1.5,
              (double)(perf_info->read_bw + perf_info->write_bw) / perf_info->pic_num / 1000/ 1.5);

}
#endif

#ifdef OPEN_HWCFG_TO_CLIENT
void GetHwConfig(const void *p_hw_feature, struct DecHwConfig *hw_cfg) {
  u32 tmp;
  const struct DecHwFeatures *hw_feature = (const struct DecHwFeatures *)p_hw_feature;

  (void)DWLmemset(hw_feature, 0, sizeof(struct DecHwFeatures));

  hw_cfg->hevc_main10_support = hw_feature->hevc_main10_support;
  hw_cfg->vp9_10bit_support = hw_feature->vp9_profile2_support;
  hw_cfg->ds_support = hw_feature->dscale_support[0] |
                       hw_feature->dscale_support[1] |
                       hw_feature->dscale_support[2] |
                       hw_feature->dscale_support[3];
  hw_cfg->rfc_support = hw_feature->rfc_support;
  hw_cfg->addr64_support = hw_feature->addr64_support;
  hw_cfg->fmt_p010_support = hw_feature->fmt_p010_support;
  hw_cfg->max_pp_out_pic_width = hw_feature->max_pp_out_pic_width[0];
  hw_cfg->max_pp_out_pic_height = hw_feature->max_pp_out_pic_height[0];

  hw_cfg->h264_support = hw_feature->h264_support;
  if(hw_cfg->h264_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_H264_DEC] = hw_feature->h264_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_H264_DEC] = hw_feature->h264_max_dec_pic_height;
  }
  hw_cfg->vp9_support = hw_feature->vp9_support;
  if(hw_cfg->vp9_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_VP9_DEC] = hw_feature->vp9_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_VP9_DEC] = hw_feature->vp9_max_dec_pic_height;
  }
  hw_cfg->hevc_support = hw_feature->hevc_support;
  if(hw_cfg->hevc_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_HEVC_DEC] = hw_feature->hevc_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_HEVC_DEC] = hw_feature->hevc_max_dec_pic_height;
  }
  hw_cfg->avs2_support = hw_feature->avs2_support;
  if(hw_cfg->avs2_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_AVS2_DEC] = hw_feature->avs2_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_AVS2_DEC] = hw_feature->avs2_max_dec_pic_height;
  }
  hw_cfg->jpeg_support = hw_feature->jpeg_support;
  if(hw_cfg->jpeg_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_JPEG_DEC] = hw_feature->img_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_JPEG_DEC] = hw_feature->img_max_dec_pic_height;
  }
  hw_cfg->mpeg4_support = hw_feature->mpeg4_support;
  if(hw_cfg->mpeg4_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_MPEG4_DEC] = hw_feature->mpeg4_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_MPEG4_DEC] = hw_feature->mpeg4_max_dec_pic_height;
  }
  hw_cfg->mpeg2_support = hw_feature->mpeg2_support;
  if(hw_cfg->mpeg2_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_MPEG2_DEC] = hw_feature->mpeg2_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_MPEG2_DEC] = hw_feature->mpeg2_max_dec_pic_height;
  }
  hw_cfg->vc1_support = hw_feature->vc1_support;
  if(hw_cfg->vc1_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_VC1_DEC] = hw_feature->vc1_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_VC1_DEC] = hw_feature->vc1_max_dec_pic_height;
  }
  hw_cfg->vp6_support = hw_feature->vp6_support;
  if(hw_cfg->vp6_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_VP6_DEC] = hw_feature->vp6_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_VP6_DEC] = hw_feature->vp6_max_dec_pic_height;
  }
  hw_cfg->vp7_support = hw_feature->vp7_support;
  hw_cfg->vp8_support = hw_feature->vp8_support;
  if(hw_cfg->vp8_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_VP8_DEC] = hw_feature->vp8_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_VP8_DEC] = hw_feature->vp8_max_dec_pic_height;
  }
  hw_cfg->av1_support = hw_feature->av1_support;
  if(hw_cfg->av1_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_AV1_DEC] = hw_feature->av1_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_AV1_DEC] = hw_feature->av1_max_dec_pic_height;
  }
  hw_cfg->vvc_support = hw_feature->vvc_support;
  if(hw_cfg->vvc_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_VVC_DEC] = hw_feature->vvc_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_VVC_DEC] = hw_feature->vvc_max_dec_pic_height;
  }

  hw_cfg->custom_mpeg4_support = hw_feature->custom_mpeg4_support;
  hw_cfg->pp_standalone = hw_feature->pp_standalone;
  tmp = 0;
  if (hw_feature->dscale_support[0] || hw_feature->uscale_support[0]) {
    u32 scaling_bits;
    scaling_bits = 0x3;
    scaling_bits <<= 26;
    tmp |= scaling_bits; /* PP_SCALING */
  }

  hw_cfg->pp_config = tmp;
  hw_cfg->sorenson_spark_support = hw_feature->sorenson_spark_support;
#ifdef DEC_X170_APF_DISABLE
  if (DEC_X170_APF_DISABLE) {

  }
#endif /* DEC_X170_APF_DISABLE */

  hw_cfg->avs_support = hw_feature->avs_support;
  if(hw_cfg->avs_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_AVS_DEC] = hw_feature->avs_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_AVS_DEC] = hw_feature->avs_max_dec_pic_height;
  }
  if (hw_feature->avs_support == 2)
    hw_cfg->avs_plus_support = 1;
  else
    hw_cfg->avs_plus_support = 0;

  hw_cfg->rv_support = hw_feature->rv_support;
  if(hw_cfg->rv_support) {
    hw_cfg->max_dec_pic_width[DWL_CLIENT_TYPE_RV_DEC] = hw_feature->rv_max_dec_pic_width;
    hw_cfg->max_dec_pic_height[DWL_CLIENT_TYPE_RV_DEC] = hw_feature->rv_max_dec_pic_height;
  }
  hw_cfg->webp_support = hw_feature->webp_support;
}
#endif