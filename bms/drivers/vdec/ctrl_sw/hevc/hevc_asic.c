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

#include "basetype.h"
#include "regdrv.h"
#include "hevc_asic.h"
#include "hevc_container.h"
#include "hevc_util.h"
#include "dwl.h"
#include "commonconfig.h"
#include "commonfunction.h"
#include "errorhandling.h"
#include "hevcdecmc_internals.h"
#include "vpufeature.h"
#include "ppu.h"
#include "delogo.h"
#include <string.h>
#include "dec_log.h"
#define HEVC_422
static void HevcStreamPosUpdate(struct HevcDecContainer *dec_cont);
u32 no_chroma = 0;
#ifndef TRACE_PP_CTRL
#define TRACE_PP_CTRL(...) \
  do {                     \
  } while (0)
#else
#undef TRACE_PP_CTRL
#define TRACE_PP_CTRL(...) printf(__VA_ARGS__)
#endif

const u32 ref_ybase[16] = {
  HWIF_REFER0_YBASE_LSB,  HWIF_REFER1_YBASE_LSB,  HWIF_REFER2_YBASE_LSB,
  HWIF_REFER3_YBASE_LSB,  HWIF_REFER4_YBASE_LSB,  HWIF_REFER5_YBASE_LSB,
  HWIF_REFER6_YBASE_LSB,  HWIF_REFER7_YBASE_LSB,  HWIF_REFER8_YBASE_LSB,
  HWIF_REFER9_YBASE_LSB,  HWIF_REFER10_YBASE_LSB, HWIF_REFER11_YBASE_LSB,
  HWIF_REFER12_YBASE_LSB, HWIF_REFER13_YBASE_LSB, HWIF_REFER14_YBASE_LSB,
  HWIF_REFER15_YBASE_LSB
};

const u32 ref_cbase[16] = {
  HWIF_REFER0_CBASE_LSB,  HWIF_REFER1_CBASE_LSB,  HWIF_REFER2_CBASE_LSB,
  HWIF_REFER3_CBASE_LSB,  HWIF_REFER4_CBASE_LSB,  HWIF_REFER5_CBASE_LSB,
  HWIF_REFER6_CBASE_LSB,  HWIF_REFER7_CBASE_LSB,  HWIF_REFER8_CBASE_LSB,
  HWIF_REFER9_CBASE_LSB,  HWIF_REFER10_CBASE_LSB, HWIF_REFER11_CBASE_LSB,
  HWIF_REFER12_CBASE_LSB, HWIF_REFER13_CBASE_LSB, HWIF_REFER14_CBASE_LSB,
  HWIF_REFER15_CBASE_LSB
};

const u32 ref_dbase[16] = {
  HWIF_REFER0_DBASE_LSB,  HWIF_REFER1_DBASE_LSB,  HWIF_REFER2_DBASE_LSB,
  HWIF_REFER3_DBASE_LSB,  HWIF_REFER4_DBASE_LSB,  HWIF_REFER5_DBASE_LSB,
  HWIF_REFER6_DBASE_LSB,  HWIF_REFER7_DBASE_LSB,  HWIF_REFER8_DBASE_LSB,
  HWIF_REFER9_DBASE_LSB,  HWIF_REFER10_DBASE_LSB, HWIF_REFER11_DBASE_LSB,
  HWIF_REFER12_DBASE_LSB, HWIF_REFER13_DBASE_LSB, HWIF_REFER14_DBASE_LSB,
  HWIF_REFER15_DBASE_LSB
};
const u32 ref_tybase[16] = {
  HWIF_REFER0_TYBASE_LSB, HWIF_REFER1_TYBASE_LSB, HWIF_REFER2_TYBASE_LSB,
  HWIF_REFER3_TYBASE_LSB, HWIF_REFER4_TYBASE_LSB, HWIF_REFER5_TYBASE_LSB,
  HWIF_REFER6_TYBASE_LSB, HWIF_REFER7_TYBASE_LSB, HWIF_REFER8_TYBASE_LSB,
  HWIF_REFER9_TYBASE_LSB, HWIF_REFER10_TYBASE_LSB, HWIF_REFER11_TYBASE_LSB,
  HWIF_REFER12_TYBASE_LSB, HWIF_REFER13_TYBASE_LSB, HWIF_REFER14_TYBASE_LSB,
  HWIF_REFER15_TYBASE_LSB
};
const u32 ref_tcbase[16] = {
  HWIF_REFER0_TCBASE_LSB, HWIF_REFER1_TCBASE_LSB, HWIF_REFER2_TCBASE_LSB,
  HWIF_REFER3_TCBASE_LSB, HWIF_REFER4_TCBASE_LSB, HWIF_REFER5_TCBASE_LSB,
  HWIF_REFER6_TCBASE_LSB, HWIF_REFER7_TCBASE_LSB, HWIF_REFER8_TCBASE_LSB,
  HWIF_REFER9_TCBASE_LSB, HWIF_REFER10_TCBASE_LSB, HWIF_REFER11_TCBASE_LSB,
  HWIF_REFER12_TCBASE_LSB, HWIF_REFER13_TCBASE_LSB, HWIF_REFER14_TCBASE_LSB,
  HWIF_REFER15_TCBASE_LSB
};

const u32 ref_ybase_msb[16] = {
  HWIF_REFER0_YBASE_MSB,  HWIF_REFER1_YBASE_MSB,  HWIF_REFER2_YBASE_MSB,
  HWIF_REFER3_YBASE_MSB,  HWIF_REFER4_YBASE_MSB,  HWIF_REFER5_YBASE_MSB,
  HWIF_REFER6_YBASE_MSB,  HWIF_REFER7_YBASE_MSB,  HWIF_REFER8_YBASE_MSB,
  HWIF_REFER9_YBASE_MSB,  HWIF_REFER10_YBASE_MSB, HWIF_REFER11_YBASE_MSB,
  HWIF_REFER12_YBASE_MSB, HWIF_REFER13_YBASE_MSB, HWIF_REFER14_YBASE_MSB,
  HWIF_REFER15_YBASE_MSB
};

const u32 ref_cbase_msb[16] = {
  HWIF_REFER0_CBASE_MSB,  HWIF_REFER1_CBASE_MSB,  HWIF_REFER2_CBASE_MSB,
  HWIF_REFER3_CBASE_MSB,  HWIF_REFER4_CBASE_MSB,  HWIF_REFER5_CBASE_MSB,
  HWIF_REFER6_CBASE_MSB,  HWIF_REFER7_CBASE_MSB,  HWIF_REFER8_CBASE_MSB,
  HWIF_REFER9_CBASE_MSB,  HWIF_REFER10_CBASE_MSB, HWIF_REFER11_CBASE_MSB,
  HWIF_REFER12_CBASE_MSB, HWIF_REFER13_CBASE_MSB, HWIF_REFER14_CBASE_MSB,
  HWIF_REFER15_CBASE_MSB
};

const u32 ref_dbase_msb[16] = {
  HWIF_REFER0_DBASE_MSB,  HWIF_REFER1_DBASE_MSB,  HWIF_REFER2_DBASE_MSB,
  HWIF_REFER3_DBASE_MSB,  HWIF_REFER4_DBASE_MSB,  HWIF_REFER5_DBASE_MSB,
  HWIF_REFER6_DBASE_MSB,  HWIF_REFER7_DBASE_MSB,  HWIF_REFER8_DBASE_MSB,
  HWIF_REFER9_DBASE_MSB,  HWIF_REFER10_DBASE_MSB, HWIF_REFER11_DBASE_MSB,
  HWIF_REFER12_DBASE_MSB, HWIF_REFER13_DBASE_MSB, HWIF_REFER14_DBASE_MSB,
  HWIF_REFER15_DBASE_MSB
};
const u32 ref_tybase_msb[16] = {
  HWIF_REFER0_TYBASE_MSB, HWIF_REFER1_TYBASE_MSB, HWIF_REFER2_TYBASE_MSB,
  HWIF_REFER3_TYBASE_MSB, HWIF_REFER4_TYBASE_MSB, HWIF_REFER5_TYBASE_MSB,
  HWIF_REFER6_TYBASE_MSB, HWIF_REFER7_TYBASE_MSB, HWIF_REFER8_TYBASE_MSB,
  HWIF_REFER9_TYBASE_MSB, HWIF_REFER10_TYBASE_MSB, HWIF_REFER11_TYBASE_MSB,
  HWIF_REFER12_TYBASE_MSB, HWIF_REFER13_TYBASE_MSB, HWIF_REFER14_TYBASE_MSB,
  HWIF_REFER15_TYBASE_MSB
};
const u32 ref_tcbase_msb[16] = {
  HWIF_REFER0_TCBASE_MSB, HWIF_REFER1_TCBASE_MSB, HWIF_REFER2_TCBASE_MSB,
  HWIF_REFER3_TCBASE_MSB, HWIF_REFER4_TCBASE_MSB, HWIF_REFER5_TCBASE_MSB,
  HWIF_REFER6_TCBASE_MSB, HWIF_REFER7_TCBASE_MSB, HWIF_REFER8_TCBASE_MSB,
  HWIF_REFER9_TCBASE_MSB, HWIF_REFER10_TCBASE_MSB, HWIF_REFER11_TCBASE_MSB,
  HWIF_REFER12_TCBASE_MSB, HWIF_REFER13_TCBASE_MSB, HWIF_REFER14_TCBASE_MSB,
  HWIF_REFER15_TCBASE_MSB
};
/*------------------------------------------------------------------------------
    Reference list initialization
------------------------------------------------------------------------------*/
#define IS_SHORT_TERM_FRAME(a) ((a).status == SHORT_TERM)
#define IS_LONG_TERM_FRAME(a) ((a).status == LONG_TERM)
#define IS_REFERENCE(a) IsReference(&(a))
static u32 IsReference(const struct DpbPicture *a) {
  return (a->status && a->status != EMPTY);
}

#define INVALID_IDX 0xFFFFFFFF
#define MIN_POC 0x80000000
#define MAX_POC 0x7FFFFFFF
#define MAX3(A,B,C) ((A)>(B)&&(A)>(C)?(A):((B)>(C)?(B):(C)))

const u32 ref_pic_list0[16] = {
  HWIF_INIT_RLIST_F0,  HWIF_INIT_RLIST_F1,  HWIF_INIT_RLIST_F2,
  HWIF_INIT_RLIST_F3,  HWIF_INIT_RLIST_F4,  HWIF_INIT_RLIST_F5,
  HWIF_INIT_RLIST_F6,  HWIF_INIT_RLIST_F7,  HWIF_INIT_RLIST_F8,
  HWIF_INIT_RLIST_F9,  HWIF_INIT_RLIST_F10, HWIF_INIT_RLIST_F11,
  HWIF_INIT_RLIST_F12, HWIF_INIT_RLIST_F13, HWIF_INIT_RLIST_F14,
  HWIF_INIT_RLIST_F15
};

const u32 ref_pic_list1[16] = {
  HWIF_INIT_RLIST_B0,  HWIF_INIT_RLIST_B1,  HWIF_INIT_RLIST_B2,
  HWIF_INIT_RLIST_B3,  HWIF_INIT_RLIST_B4,  HWIF_INIT_RLIST_B5,
  HWIF_INIT_RLIST_B6,  HWIF_INIT_RLIST_B7,  HWIF_INIT_RLIST_B8,
  HWIF_INIT_RLIST_B9,  HWIF_INIT_RLIST_B10, HWIF_INIT_RLIST_B11,
  HWIF_INIT_RLIST_B12, HWIF_INIT_RLIST_B13, HWIF_INIT_RLIST_B14,
  HWIF_INIT_RLIST_B15
};

static const u32 ref_poc_regs[16] = {
  HWIF_CUR_POC_00, HWIF_CUR_POC_01, HWIF_CUR_POC_02, HWIF_CUR_POC_03,
  HWIF_CUR_POC_04, HWIF_CUR_POC_05, HWIF_CUR_POC_06, HWIF_CUR_POC_07,
  HWIF_CUR_POC_08, HWIF_CUR_POC_09, HWIF_CUR_POC_10, HWIF_CUR_POC_11,
  HWIF_CUR_POC_12, HWIF_CUR_POC_13, HWIF_CUR_POC_14, HWIF_CUR_POC_15
};

static struct DpbPicture *HevcReplaceRefPic(struct HevcDecContainer *dec_cont,
                                            struct DpbPicture *buffer) {
  u32 i = 0;
  u32 curr_poc = 0;
  struct DpbStorage *dpb = &dec_cont->storage.dpb[0];
  struct Storage *storage = &dec_cont->storage;

  i32 find_idx = EC_INVALID_IDX;
  u32 poc_delta = 0x7FFFFFFF;
  u32 poc_delta_pre = 0x7FFFFFFF;

  u32 correct_count[MAX_DPB_SIZE + 1] = {0};
  u32 ref_error_count[MAX_DPB_SIZE + 1] = {0};
  u32 tolerable_error_count[MAX_DPB_SIZE + 1] = {0};
  u32 frame_error_count[MAX_DPB_SIZE + 1] = {0};

  /* NO_RFC: if error_ratio less than 10%, don't replace it, use it as correct. */
  if (!dec_cont->use_video_compressor &&
      buffer->error_ratio <= EC_RATIO_THRESHOLD)
    return buffer;

  /* ref_buffer error info count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (IS_REFERENCE(dpb->buffer[i])) {
      /* skip self. */
      if (dpb->buffer[i].pic_order_cnt == storage->dpb->current_out->pic_order_cnt)
        continue;

      if (dpb->buffer[i].error_info == DEC_NO_ERROR)
        correct_count[i]++;
      else if (dpb->buffer[i].error_info == DEC_REF_ERROR)
        ref_error_count[i]++;
      else {
        /* NO_RFC: if error_ratio less than 10%, use it as correct. */
        if (!dec_cont->use_video_compressor &&
            dpb->buffer[i].error_ratio <= EC_RATIO_THRESHOLD)
          tolerable_error_count[i]++;
        else
          frame_error_count[i]++;
      }
    }
  }

  curr_poc = buffer->pic_order_cnt;
  /* firstly: find from correct_count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (correct_count[i]) {
      poc_delta = dpb->buffer[i].pic_order_cnt > curr_poc ?
                  dpb->buffer[i].pic_order_cnt - curr_poc :
                  curr_poc - dpb->buffer[i].pic_order_cnt;
      poc_delta_pre = poc_delta_pre > poc_delta ? poc_delta : poc_delta_pre;
      if (poc_delta_pre == poc_delta) find_idx = i;
    }
  }
  if (find_idx != EC_INVALID_IDX)
    return &dpb->buffer[find_idx];

  /* secondly: find from ref_error_count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (ref_error_count[i]) {
      poc_delta = dpb->buffer[i].pic_order_cnt > curr_poc ?
                  dpb->buffer[i].pic_order_cnt - curr_poc :
                  curr_poc - dpb->buffer[i].pic_order_cnt;
      poc_delta_pre = poc_delta_pre > poc_delta ? poc_delta : poc_delta_pre;
      if (poc_delta_pre == poc_delta) find_idx = i;
    }
  }
  if (find_idx != EC_INVALID_IDX)
    return &dpb->buffer[find_idx];

  /* Thirdly: find from tolerable_error_count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (tolerable_error_count[i]) {
      poc_delta = dpb->buffer[i].pic_order_cnt > curr_poc ?
                  dpb->buffer[i].pic_order_cnt - curr_poc :
                  curr_poc - dpb->buffer[i].pic_order_cnt;
      poc_delta_pre = poc_delta_pre > poc_delta ? poc_delta : poc_delta_pre;
      if (poc_delta_pre == poc_delta) find_idx = i;
    }
  }
  if (find_idx != EC_INVALID_IDX)
    return &dpb->buffer[find_idx];

  /* not find */
  return NULL;
}

u32 AllocateAsicBuffers(struct HevcDecContainer *dec_cont,
                        struct HevcDecAsic *asic_buff) {
//  i32 ret = 0;
  u32 size, i;

  /* cabac tables and scaling lists in separate bases, but memory allocated
   * in one chunk */
  size = NEXT_MULTIPLE(ASIC_SCALING_LIST_SIZE, MAX(16, ALIGN(dec_cont->align)));
  /* max number of tiles times width and height (2 bytes each),
   * rounding up to next 16 bytes boundary + one extra 16 byte
   * chunk (HW guys wanted to have this) */
  size += NEXT_MULTIPLE((MAX_TILE_COLS * MAX_TILE_ROWS * 4 * sizeof(u16) + 15 +
                         16) & ~0xF, MAX(16, ALIGN(dec_cont->align)));
#ifdef USE_FAKE_RFC_TABLE
  if (dec_cont->use_video_compressor) {
    asic_buff->fake_table_offset = size;
    size += asic_buff->fake_tbly_size + asic_buff->fake_tblc_size;
  }
#endif
  asic_buff->scaling_lists_offset = 0;
  asic_buff->tile_info_offset = NEXT_MULTIPLE(ASIC_SCALING_LIST_SIZE,
                                              MAX(16, ALIGN(dec_cont->align)));

  if (asic_buff->misc_linear[0].virtual_address == NULL) {
    i32 ret = 0;
    for (i = 0; i < dec_cont->n_cores; i++) {
      asic_buff->misc_linear[i].mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE |
                                            DWL_MEM_TYPE_VPU_WORKING;
#ifdef ASIC_TRACE_SUPPORT
        ret = DWLMallocRefFrm(dec_cont->dwl, size, &asic_buff->misc_linear[i]);
#else
        ret = DWLMallocLinear(dec_cont->dwl, size, &asic_buff->misc_linear[i]);
#endif
        if (ret) return 1;
      }
   }
  /* Allocate buffer for ddr_low_latency model */
  if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
    dec_cont->llstrminfo.strm_status.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    if(DWLMallocLinear(dec_cont->dwl, 16 * 4, &dec_cont->llstrminfo.strm_status))
      return 1;
   }

#ifdef USE_FAKE_RFC_TABLE
  if (dec_cont->use_video_compressor) {
    u32 pic_width_in_cbsy, pic_height_in_cbsy;
    u32 pic_width_in_cbsc, pic_height_in_cbsc;
    const struct SeqParamSet *sps = dec_cont->storage.active_sps;
    u32 bit_depth = (sps->bit_depth_luma == 8 && sps->bit_depth_chroma == 8) ? 8 : 10;

    pic_width_in_cbsy = ((sps->pic_width + 8 - 1)/8);
    pic_width_in_cbsy = NEXT_MULTIPLE(pic_width_in_cbsy, 16);
    pic_width_in_cbsc = ((sps->pic_width + 16 - 1)/16);
    pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
    pic_height_in_cbsy = (sps->pic_height + 8 - 1)/8;
    pic_height_in_cbsc = (sps->pic_height/2 + 4 - 1)/4;

    if (sps->chroma_format_idc == 0) {
      pic_width_in_cbsc = pic_height_in_cbsc = 0;
    }

    for (i = 0; i < dec_cont->n_cores; i++) {
      GenerateFakeRFCTable((u8 *)asic_buff->misc_linear[i].virtual_address+asic_buff->fake_table_offset,
                           pic_width_in_cbsy,
                           pic_height_in_cbsy,
                           pic_width_in_cbsc,
                           pic_height_in_cbsc,
                           bit_depth,
                           MAX(16, ALIGN(dec_cont->align)));
    }
  }
#endif
  return 0;
}

i32 ReleaseAsicBuffers(struct HevcDecContainer *dec_cont, struct HevcDecAsic *asic_buff) {
  u32 i;
  const void *dwl = dec_cont->dwl;

  for(i = 0; i < MAX_ASIC_CORES; i++) {
    if (asic_buff->misc_linear[i].virtual_address != NULL) {
#ifdef ASIC_TRACE_SUPPORT
        DWLFreeRefFrm(dwl, &asic_buff->misc_linear[i]);
#else
        DWLFreeLinear(dwl, &asic_buff->misc_linear[i]);
#endif
        asic_buff->misc_linear[i].virtual_address = NULL;
        asic_buff->misc_linear[i].size = 0;
    }
  }
  if(dec_cont->llstrminfo.strm_status.virtual_address != NULL){
    DWLFreeLinear(dwl, &dec_cont->llstrminfo.strm_status);
    dec_cont->llstrminfo.strm_status.virtual_address = NULL;
  }
  return 0;
}

u32 GetAsicTileEdgeMemsSize(struct HevcDecContainer *dec_cont) {
  u32 num_tile_cols = dec_cont->storage.active_pps->tile_info.num_tile_columns;
  struct SeqParamSet *sps = dec_cont->storage.active_sps;
  u32 pixel_width = (sps->bit_depth_luma == 8 && sps->bit_depth_chroma == 8) ? 8 : 10;

  u32 ctb_size = 1 << sps->log_max_coding_block_size;
  u32 height64 = (dec_cont->storage.active_sps->pic_height + 63) & ~63;
  u32 asic_vert_filt_ram_size = dec_cont->storage.active_sps->chroma_format_idc == 2 ? ASIC_VERT_FILTER_RAM_SIZE_422 : ASIC_VERT_FILTER_RAM_SIZE;
  u32 asic_vert_sao_ram_size = dec_cont->storage.active_sps->chroma_format_idc == 2 ? ASIC_VERT_SAO_RAM_SIZE_422 : ASIC_VERT_SAO_RAM_SIZE;
  u32 rfc_size = ASIC_RFC_RAM_SIZE / ((ctb_size >= 32) ? 32 : 16);
  u32 size = asic_vert_filt_ram_size * height64 * (num_tile_cols - 1) * pixel_width / 8
             + ASIC_BSD_CTRL_RAM_SIZE * height64 * (num_tile_cols - 1)
             + asic_vert_sao_ram_size * height64 * (num_tile_cols - 1) * pixel_width / 8
             + (dec_cont->use_video_compressor ? rfc_size * height64 * (num_tile_cols - 1) : 0);
  if (dec_cont->pp_enabled) {
    size += PPGetLancozsColumnBufferSize(dec_cont->ppu_cfg, sps->pic_height, pixel_width, 1);
  }
  return size;
}

u32 AllocateAsicTileEdgeMems(struct HevcDecContainer *dec_cont) {
  struct HevcDecAsic *asic_buff = dec_cont->asic_buff;
  u32 num_tile_cols = dec_cont->storage.active_pps->tile_info.num_tile_columns;
  if (num_tile_cols < 2) return HANTRO_OK;

  u32 i = 0;
  u32 size = 0;
  u32 count = 0;
  size = GetAsicTileEdgeMemsSize(dec_cont);

  for (i = 0; i < dec_cont->n_cores * 2; i++) {
    if (asic_buff->tile_edge_used_by[i] == 0 && asic_buff->tile_edge[i].size >= size)
      count++;
    if (asic_buff->tile_edge_used_by[i] == 0 && asic_buff->tile_edge[i].size < size) {
      /* release old */
      ReleaseAsicTileEdgeMems(dec_cont, i);
      /* reallocate new */
      asic_buff->tile_edge[i].mem_type = DWL_MEM_TYPE_DMA_DEVICE_ONLY | DWL_MEM_TYPE_VPU_ONLY;
      i32 dwl_ret = DWLMallocLinear(dec_cont->dwl, size, &asic_buff->tile_edge[i]);
      if (dwl_ret != DWL_OK) return HANTRO_NOK;
      count++;
    }
    if (count == dec_cont->n_cores) break;
  }

  for (++i; i < dec_cont->n_cores * 2; i++){
    /* release excess buffer */
    if(asic_buff->tile_edge_used_by[i] == 0)
      ReleaseAsicTileEdgeMems(dec_cont, i);
  }

  return HANTRO_OK;
}

u32 BindAsicTileEdgeMemsToCore(struct HevcDecContainer *dec_cont, u32 core_id) {
  if (dec_cont->storage.active_pps == NULL || dec_cont->storage.active_sps == NULL) return core_id;

  struct HevcDecAsic *asic_buff = dec_cont->asic_buff;
  u32 num_tile_cols = dec_cont->storage.active_pps->tile_info.num_tile_columns;
  struct SeqParamSet *sps = dec_cont->storage.active_sps;
  u32 pixel_width = (sps->bit_depth_luma == 8 && sps->bit_depth_chroma == 8) ? 8 : 10;
  u32 i = 0, j = 0, count = 0;
  u32 pp_scale_size = 0;
  u32 pp_scale_out_size = 0;
  u32 pp_reorder_offset = 0;
  u32 scale_offset = 0;
  u32 scale_out_offset = 0;
  u32 ctb_size = 1 << sps->log_max_coding_block_size;
  if (num_tile_cols < 2) return core_id;

  u32 height64 = (dec_cont->storage.active_sps->pic_height + 63) & ~63;
  u32 asic_vert_filt_ram_size = dec_cont->storage.active_sps->chroma_format_idc == 2 ? ASIC_VERT_FILTER_RAM_SIZE_422 : ASIC_VERT_FILTER_RAM_SIZE;
  u32 asic_vert_sao_ram_size = dec_cont->storage.active_sps->chroma_format_idc == 2 ? ASIC_VERT_SAO_RAM_SIZE_422 : ASIC_VERT_SAO_RAM_SIZE;
  u32 rfc_size = ASIC_RFC_RAM_SIZE / ((ctb_size >= 32) ? 32 : 16);

  asic_buff->filter_mem_offset[core_id] = 0;
  asic_buff->bsd_control_mem_offset[core_id] = asic_buff->filter_mem_offset[core_id]
                                      + asic_vert_filt_ram_size * height64 * (num_tile_cols - 1) * pixel_width / 8;
  asic_buff->sao_mem_offset[core_id] = asic_buff->bsd_control_mem_offset[core_id] + ASIC_BSD_CTRL_RAM_SIZE * height64 * (num_tile_cols - 1);
  asic_buff->rfc_offset[core_id] =  asic_buff->sao_mem_offset[core_id] + asic_vert_sao_ram_size * height64 * (num_tile_cols - 1) * pixel_width / 8;

  /* find a idle & enought tile_edge_buffer */
  u32 size = GetAsicTileEdgeMemsSize(dec_cont);
  for (j = 0; j < dec_cont->n_cores * 2; j++) {
    if (asic_buff->tile_edge_used_by[j] == 0 && asic_buff->tile_edge[j].size >= size)
      break;
  }
  if (j == dec_cont->n_cores * 2) ASSERT(0);

  /* bind tile_edge_buffer to core_id */
  if (dec_cont->pp_enabled) {
    for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
      if (dec_cont->ppu_cfg[i].enabled)
        count++;
    }
  }
  pp_scale_size = 0;
  pp_scale_out_size = 0;
  /* after tile8x8 optimize, buffer HWIF_RFC_COLBUF_BASE_LSB is always used no matter if RFC is enable or not */
  // pp_reorder_offset = asic_buff->rfc_offset[core_id] + (dec_cont->use_video_compressor ? rfc_size * height64 * (num_tile_cols - 1) : 0);
  pp_reorder_offset = asic_buff->rfc_offset[core_id] + rfc_size * height64 * (num_tile_cols - 1);
  scale_offset = pp_reorder_offset + dec_cont->ppu_cfg[0].reorder_size;
  scale_out_offset = scale_offset + count * dec_cont->ppu_cfg[0].scale_size;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cont->ppu_cfg[i].enabled) {
      dec_cont->ppu_cfg[i].reorder_buf_bus[core_id] = asic_buff->tile_edge[j].bus_address + pp_reorder_offset;
      dec_cont->ppu_cfg[i].scale_buf_bus[core_id] = asic_buff->tile_edge[j].bus_address + scale_offset + pp_scale_size;
      dec_cont->ppu_cfg[i].scale_out_buf_bus[core_id] = asic_buff->tile_edge[j].bus_address + scale_out_offset + pp_scale_out_size;
      pp_scale_size += dec_cont->ppu_cfg[i].scale_size;
      pp_scale_out_size += dec_cont->ppu_cfg[i].scale_out_size;
    }
  }

  if (dec_cont->vcmd_used) {
    asic_buff->tile_edge_used_by[j] = dec_cont->cmdbuf_id + 1;
  } else {
    asic_buff->tile_edge_used_by[j] = core_id + 1;
  }

  return j;
}

void UnbindAsicTileEdgeMemsFromCore(struct HevcDecContainer *dec_cont, u32 core_id) {
  struct HevcDecAsic *asic_buff = dec_cont->asic_buff;
  u32 i = 0;

  for (i = 0; i < dec_cont->n_cores * 2; i++) {
    if (asic_buff->tile_edge_used_by[i] - 1 == core_id) {
      asic_buff->tile_edge_used_by[i] = 0;
      break;
    }
  }

  return;
}

void ReleaseAsicTileEdgeMems(struct HevcDecContainer *dec_cont, u32 core_id) {
  struct HevcDecAsic *asic_buff = dec_cont->asic_buff;
  if (DWL_DEVMEM_VAILD(asic_buff->tile_edge[core_id])) {
    DWLFreeLinear(dec_cont->dwl, &asic_buff->tile_edge[core_id]);
    asic_buff->tile_edge[core_id].virtual_address = NULL;
    asic_buff->tile_edge[core_id].bus_address = 0;
    asic_buff->tile_edge[core_id].size = 0;
  }
}

u32 HevcRunAsic(struct HevcDecContainer *dec_cont,
                struct HevcDecAsic *asic_buff) {

  u32 asic_status = 0;
  i32 ret = 0;
  u32 core_id, tile_buf_id;
  u32 i, j, tmp;
  u32 long_term_flags;
  struct PicParamSet *pps = dec_cont->storage.active_pps;
  struct SeqParamSet *sps = dec_cont->storage.active_sps;
  struct DpbStorage *dpb = dec_cont->storage.dpb;
  struct Storage *storage = &dec_cont->storage;
  u32 ctb_size = 1 << sps->log_max_coding_block_size;
  const struct DecHwFeatures *hw_feature = NULL;
  struct DWLReqInfo info = {0};

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_HEVC_DEC, (const void **)&hw_feature);

  no_chroma = 0;

  /* start new picture */
  if (!dec_cont->asic_running) {
    u32 reserve_ret = 0;
    info.core_mask = dec_cont->core_mask;
    info.width = sps->pic_width;
    info.height = sps->pic_height;
    if (dec_cont->vcmd_used) {
      dec_cont->core_id = 0;
      dec_cont->cmdbuf_id = 0;
      if (dec_cont->b_mc) {
        FifoObject obj;
        FifoPop(dec_cont->fifo_core, &obj, FIFO_EXCEPTION_DISABLE);
        dec_cont->mc_buf_id = (i32)(addr_t)obj;
      }
      reserve_ret = DWLReserveCmdBuf(dec_cont->dwl, &info, &dec_cont->cmdbuf_id);
    } else {
      reserve_ret = DWLReserveHw(dec_cont->dwl, &info, &dec_cont->core_id);
    }
    if (reserve_ret != DWL_OK) {
      return X170_DEC_HW_RESERVED;
    }

    /* Set dec_status to RUNNING in MC mode */
    if (dec_cont->b_mc && !dec_cont->vcmd_used) {
      dec_cont->dec_status[dec_cont->core_id] = DEC_RUNNING;
    }

    /* core id is to used as index of buffer, generatlly, it is 0 if not multi core decode */
    core_id = dec_cont->b_mc ? (dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id) : 0;

   /* Set the buffer bus address for using ddr_low_latency */
    if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
      SET_ADDR_REG(dec_cont->hevc_regs, HWIF_LG_STREAM_STATUS_BASE,
                   dec_cont->llstrminfo.strm_status.bus_address);
    }
    /* Bind tile_edge buffer with core_id. */
    tile_buf_id = BindAsicTileEdgeMemsToCore(dec_cont, core_id);

    PPSetLancozsScaleRegs(dec_cont->hevc_regs, hw_feature, dec_cont->ppu_cfg, core_id);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_TILE_BASE,
                 asic_buff->misc_linear[core_id].bus_address + asic_buff->tile_info_offset);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_VERT_FILT_BASE,
                 asic_buff->tile_edge[tile_buf_id].bus_address + asic_buff->filter_mem_offset[core_id]);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_VERT_SAO_BASE,
                 asic_buff->tile_edge[tile_buf_id].bus_address + asic_buff->sao_mem_offset[core_id]);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_BSD_CTRL_BASE,
                 asic_buff->tile_edge[tile_buf_id].bus_address + asic_buff->bsd_control_mem_offset[core_id]);
    /*frame level muti-core, set the cur and left register same.*/
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_RFC_COLBUF_BASE,
                 asic_buff->tile_edge[tile_buf_id].bus_address + asic_buff->rfc_offset[core_id]);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_RFC_LEFT_COLBUF_BASE,
                 asic_buff->tile_edge[tile_buf_id].bus_address + asic_buff->rfc_offset[core_id]);

    SetDecRegister(dec_cont->hevc_regs, HWIF_TILE_ENABLE,
               pps->tiles_enabled_flag);
    PPSetFbcRegs(dec_cont->hevc_regs, hw_feature, dec_cont->ppu_cfg, (pps->tile_info.num_tile_columns * pps->tile_info.num_tile_rows > 1));
    if (pps->tiles_enabled_flag) {
      u32 j, h;
      u16 *p = (u16 *)((u8 *)asic_buff->misc_linear[core_id].virtual_address + asic_buff->tile_info_offset);
      SetDecRegister(dec_cont->hevc_regs, HWIF_NUM_TILE_COLS_8K,
                      pps->tile_info.num_tile_columns);
      SetDecRegister(dec_cont->hevc_regs, HWIF_NUM_TILE_ROWS_8K,
                      pps->tile_info.num_tile_rows);

      /* write width + height for each tile in pic */
      if (!pps->tile_info.uniform_spacing) {
        u32 tmp_w = 0, tmp_h = 0;

        for (i = 0; i < pps->tile_info.num_tile_rows; i++) {
          if (i == pps->tile_info.num_tile_rows - 1)
            h = storage->pic_height_in_ctbs - tmp_h;
          else
            h = pps->tile_info.row_height[i];
          tmp_h += h;
          if (i == 0 && h == 1 && ctb_size == 16)
            no_chroma = 1;
          for (j = 0, tmp_w = 0; j < pps->tile_info.num_tile_columns - 1; j++) {
            tmp_w += pps->tile_info.col_width[j];
            *p++ = pps->tile_info.col_width[j];
            *p++ = h;
            if (i == 0 && h == 1 && ctb_size == 16)
            no_chroma = 1;
          }
          /* last column */
          *p++ = storage->pic_width_in_ctbs - tmp_w;
          *p++ = h;
        }
      } else { /* uniform spacing */
        u32 prev_h, prev_w;

        for (i = 0, prev_h = 0; i < pps->tile_info.num_tile_rows; i++) {
          tmp = (i + 1) * storage->pic_height_in_ctbs /
                pps->tile_info.num_tile_rows;
          h = tmp - prev_h;
          prev_h = tmp;
          if (i == 0 && h == 1 && ctb_size == 16)
            no_chroma = 1;
          for (j = 0, prev_w = 0; j < pps->tile_info.num_tile_columns; j++) {
            tmp = (j + 1) * storage->pic_width_in_ctbs /
                  pps->tile_info.num_tile_columns;
            *p++ = tmp - prev_w;
            *p++ = h;
            if (j == 0 && pps->tile_info.col_width[0] == 1 && ctb_size == 16)
              no_chroma = 1;
            prev_w = tmp;
          }
        }
      }
    } else {
      /* just one "tile", dimensions equal to pic size */
      u16 *p = (u16 *)((u8 *)asic_buff->misc_linear[core_id].virtual_address + asic_buff->tile_info_offset);
      SetDecRegister(dec_cont->hevc_regs, HWIF_NUM_TILE_COLS_8K, 1);
      SetDecRegister(dec_cont->hevc_regs, HWIF_NUM_TILE_ROWS_8K, 1);
      p[0] = storage->pic_width_in_ctbs;
      p[1] = storage->pic_height_in_ctbs;
    }

    SetDecRegister(dec_cont->hevc_regs, HWIF_QP_OUT_E,
                   dec_cont->qp_output_enable);

    if (!dec_cont->pp_enabled) {
      SET_ADDR_REG(dec_cont->hevc_regs, HWIF_QP_OUT,
                     asic_buff->out_buffer->bus_address + dpb->out_qp_offset);
    } else {
      SET_ADDR_REG(dec_cont->hevc_regs, HWIF_QP_OUT,
                     asic_buff->out_pp_buffer->bus_address + dec_cont->auxinfo_offset);
    }

    /* write all bases */
    long_term_flags = 0;
    u8 replace_flags = 0;
    u8 fake_table_flags = 0;
    struct DpbPicture *buffer = NULL;
    struct DpbPicture *replace_buffer = NULL; /* error ref replace */
    /* there are dpb->dpb_size+1 used dpb buffers according to InitDpb function,
     * so i~[0,dpb->dpb_size] all should be writed. but we only have 16 dpb
     * registers in hw*/
    for (i = 0; i < MAX_DPB_SIZE; i++) {
      if (i < dpb->dpb_size) {
        buffer = &dpb->buffer[i];
        replace_flags = 0;
        fake_table_flags = 0;

        /* slice mode: reference_frame == current_frame */
        if (!dec_cont->disable_slice_mode &&
            !IS_RAP_NAL_UNIT(dec_cont->storage.prev_nal_unit) &&
            asic_buff->out_buffer->bus_address == buffer->data->bus_address) {
          for (j = 0; j <= dpb->dpb_size; j++) {
            if (IS_REFERENCE(dpb->buffer[j]) &&
                dpb->buffer[j].data->bus_address != buffer->data->bus_address)
              break;
          }
          if (j == dpb->dpb_size + 1) { /* not find */
            replace_buffer = NULL;
            fake_table_flags = 1;
          } else { /* find */
            replace_buffer = &dpb->buffer[j];
          }
          buffer = replace_buffer ? replace_buffer : &dpb->buffer[0];
        }

        /* EC: DEC_EC_REF_REPLACE or DEC_EC_REF_REPLACE_ANYWAY*/
        if (dec_cont->error_policy & DEC_EC_REF_REPLACE ||
            dec_cont->error_policy & DEC_EC_REF_REPLACE_ANYWAY) {
          if (IS_REFERENCE(*buffer) && buffer->error_info != DEC_NO_ERROR) {
            replace_buffer = HevcReplaceRefPic(dec_cont, buffer);
            buffer = replace_buffer ? replace_buffer : buffer;
            replace_flags = 1;
          }
        }

        /* not find avalible replace ref */
        if (replace_flags == 1 && replace_buffer == NULL) {
          if (dec_cont->use_video_compressor) {
            /* have rfc:
             * 1. DEC_EC_REF_REPLACE: will seek next I, can't call this function, so do nothing in here.
             * 2. DEC_EC_REF_REPLACE_ANYWAY: use FALE_TABLE.
             */
            fake_table_flags = 1;
          } else {
            /* no rfc: just use error ref, so do nothing in here. */
          }
        }
      } else {
        /* The redundant ref_regs need configured as the address of first right dpb_buffer */
        for (j = 0; j <= dpb->dpb_size; j++) {
          buffer = &dpb->buffer[j];
          if (asic_buff->out_buffer->bus_address == buffer->data->bus_address)
            continue;
          if (IS_REFERENCE(*buffer) && buffer->error_info == DEC_NO_ERROR)
            break;
        }
        if (j > dpb->dpb_size) buffer = &dpb->buffer[0];
        fake_table_flags = 1;
      }

      /* setting ref pic registers */
      SET_ADDR_REG2(dec_cont->hevc_regs, ref_ybase[i], ref_ybase_msb[i],
                    buffer->data->bus_address);
      SET_ADDR_REG2(dec_cont->hevc_regs, ref_cbase[i], ref_cbase_msb[i],
                    buffer->data->bus_address + storage->pic_size);
      long_term_flags |= (IS_LONG_TERM_FRAME(*buffer))<<(15-i);
      SET_ADDR_REG2(dec_cont->hevc_regs, ref_dbase[i], ref_dbase_msb[i],
                   (buffer->dmv_data == NULL ? asic_buff->out_dmv_buffer->bus_address :
                    buffer->dmv_data->bus_address));

#ifdef SUPPORT_GDR
      /* first frame is GDR(maybe not I frame, so need fake table) */
      if (dec_cont->storage.is_gdr_frame && dec_cont->pic_number == 0)
        fake_table_flags = 1;
#endif

      /* setting ref pic table register */
      if (dec_cont->use_video_compressor) {
#ifndef USE_FAKE_RFC_TABLE
        SET_ADDR_REG2(dec_cont->hevc_regs, ref_tybase[i], ref_tybase_msb[i],
                      buffer->data->bus_address + dpb->cbs_tbl_offsety);
        SET_ADDR_REG2(dec_cont->hevc_regs, ref_tcbase[i], ref_tcbase_msb[i],
                      buffer->data->bus_address + dpb->cbs_tbl_offsetc);
#else
        if (IS_RAP_NAL_UNIT(dec_cont->storage.prev_nal_unit) || fake_table_flags == 1) {
          SET_ADDR_REG2(dec_cont->hevc_regs, ref_tybase[i], ref_tybase_msb[i],
                        asic_buff->misc_linear[core_id].bus_address + asic_buff->fake_table_offset);
          SET_ADDR_REG2(dec_cont->hevc_regs, ref_tcbase[i], ref_tcbase_msb[i],
                        asic_buff->misc_linear[core_id].bus_address + asic_buff->fake_table_offset + asic_buff->fake_tbly_size);
        } else {
          SET_ADDR_REG2(dec_cont->hevc_regs, ref_tybase[i], ref_tybase_msb[i],
                        buffer->data->bus_address + dpb->cbs_tbl_offsety);
          SET_ADDR_REG2(dec_cont->hevc_regs, ref_tcbase[i], ref_tcbase_msb[i],
                        buffer->data->bus_address + dpb->cbs_tbl_offsetc);
        }
#endif
      } else {
        SET_ADDR_REG2(dec_cont->hevc_regs, ref_tybase[i], ref_tybase_msb[i], 0L);
        SET_ADDR_REG2(dec_cont->hevc_regs, ref_tcbase[i], ref_tcbase_msb[i], 0L);
      }
      (void)fake_table_flags;
    }

    SetDecRegister(dec_cont->hevc_regs, HWIF_REFER_LTERM_E, long_term_flags);

    /* scaling lists */
    SetDecRegister(dec_cont->hevc_regs, HWIF_SCALING_LIST_E,
                   sps->scaling_list_enable);
    if (sps->scaling_list_enable) {
      u32 s, j, k;
      u8 *p;

      u8(*scaling_list)[6][64];

      /* determine where to read lists from */
      if (pps->scaling_list_present_flag)
        scaling_list = pps->scaling_list;
      else {
        if (!sps->scaling_list_present_flag)
          DefaultScalingList(sps->scaling_list);
        scaling_list = sps->scaling_list;
      }

      p = (u8 *)dec_cont->asic_buff->misc_linear[core_id].virtual_address;
      ASSERT(!((addr_t)p & 0x7));
      SET_ADDR_REG(dec_cont->hevc_regs, HWIF_SCALE_LIST_BASE,
                   dec_cont->asic_buff->misc_linear[core_id].bus_address);

      /* dc coeffs of 16x16 and 32x32 lists, stored after 16 coeffs of first
       * 4x4 list */
      for (i = 0; i < 8; i++) *p++ = scaling_list[0][0][16 + i];
      /* next 128b boundary */
      p += 8;

      /* write scaling lists column by column */

      /* 4x4 */
      for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++)
          for (k = 0; k < 4; k++) *p++ = scaling_list[0][i][4 * k + j];
      }
      /* 8x8 -> 32x32 */
      for (s = 1; s < 4; s++) {
        for (i = 0; i < (s == 3 ? 2 : 6); i++) {
          for (j = 0; j < 8; j++)
            for (k = 0; k < 8; k++) *p++ = scaling_list[s][i][8 * k + j];
        }
      }
    }

#ifdef SUPPORT_DMA
    /* the [scaling list], [tile map] and [fake table] are all in misc_linear buffer.
    * [scaling list] : if (sps->scaling_list_enable).
    * [tile map] : always needs DMA.
    * [fake table] : #ifdef USE_FAKE_RFC_TABLE.
    */
    DWLDMATransData((addr_t)dec_cont->asic_buff->misc_linear[core_id].bus_address,
                    (void *)dec_cont->asic_buff->misc_linear[core_id].virtual_address,
                    dec_cont->asic_buff->misc_linear[core_id].size, HOST_TO_DEVICE);
#endif

    SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_TILE_INT_E, 0);

    if (dec_cont->partial_decoding && dec_cont->pp_enabled) {
      SetDecRegister(dec_cont->hevc_regs, HWIF_REF_READ_DIS, 1);
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_DIS, 1);
      SetDecRegister(dec_cont->hevc_regs, HWIF_WRITE_MVS_E, 0);
    } else if (dec_cont->skip_non_intra && dec_cont->pp_enabled) {
      SetDecRegister(dec_cont->hevc_regs, HWIF_REF_READ_DIS, 1);
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_DIS, 1);
      SetDecRegister(dec_cont->hevc_regs, HWIF_WRITE_MVS_E, 0);
    } else {
      if (dec_cont->skip_frame == DEC_SKIP_NON_REF_RECON &&
          dec_cont->pp_enabled &&
          IS_SLNR_NAL_UNIT(dec_cont->storage.prev_nal_unit) &&
          dec_cont->storage.active_vps->vps_max_sub_layers == 1) {
        SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_DIS, 1);
        SetDecRegister(dec_cont->hevc_regs, HWIF_WRITE_MVS_E, 0);
      } else {
        SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_DIS, asic_buff->disable_out_writing);
      }
    }

    if (dec_cont->vcmd_used)
      DWLReadPpConfigure(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->ppu_cfg, 0);
    else
      DWLReadPpConfigure(dec_cont->dwl, dec_cont->core_id, dec_cont->ppu_cfg, 0);
#ifndef ASIC_TRACE_SUPPORT
    if(dec_cont->b_mc)
#endif
      DWLReadMcRefBuffer(dec_cont->dwl, core_id, asic_buff->out_buffer->logical_size - dpb->sync_mc_offset - 32, dpb->dpb_size);
    SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_E, 1);
    if(dec_cont->vcmd_used) {
      if(dec_cont->mc_buf_id >= dec_cont->n_cores_available) {
        dec_cont->mc_buf_id = 0; /* in theory, shouldn't reach here */
      }
      DWLFlushRegister(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->hevc_regs,
                       dec_cont->mc_refresh_regs[dec_cont->mc_buf_id], dec_cont->mc_buf_id, (void *)dec_cont);
    }
    else {
      FlushDecRegisters(dec_cont->dwl, dec_cont->core_id, dec_cont->hevc_regs,
                        hw_feature->max_ppu_count);
    }

    /* when b_mc is 0, the callback callback_arg has been clear up in DWLReserveHw/DWLReserveCmdBuf */
    if(dec_cont->b_mc) {
      HevcMCSetHwRdyCallback(dec_cont);
#ifdef SUPPORT_GDR
      /* MC mode: recovery_poc_cnt-- */
      if (dec_cont->storage.is_gdr_frame && dec_cont->storage.sei_param_curr)
        dec_cont->storage.sei_param_curr->recovery_param.recovery_poc_cnt--;
#endif
    }

    HevcEnableDMVBuffer(dpb, dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id);

    if (dec_cont->vcmd_used)
      DWLEnableCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);
    else
      DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                  dec_cont->hevc_regs[1]);

    dec_cont->asic_running = 1;

    if (dec_cont->pp_enabled)
      IncreaseInputQueueCnt(dec_cont->pp_buffer_queue, dec_cont->asic_buff->out_pp_buffer->virtual_address);

    if(dec_cont->b_mc) {
      /* reset shadow HW status reg values so that we dont end up writing
       * some garbage to next core regs */
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_E, 0);
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ_STAT, 0);
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ, 0);

      dec_cont->asic_running = 0;
      return DEC_HW_IRQ_RDY;
    }

  } else { /* buffer was empty and now we restart with new stream values */
    ASSERT(!dec_cont->b_mc);
    HevcStreamPosUpdate(dec_cont);

    /* HWIF_STRM_START_BIT */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 5,
                dec_cont->hevc_regs[5]);
    /* HWIF_STREAM_DATA_LEN */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 6,
                dec_cont->hevc_regs[6]);
    /* HWIF_STREAM_BASE_MSB */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 168,
                dec_cont->hevc_regs[168]);
    /* HWIF_STREAM_BASE_LSB */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 169,
                dec_cont->hevc_regs[169]);
    /* HWIF_STREAM_BUFFER_LEN */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 258,
                dec_cont->hevc_regs[258]);
    /* HWIF_STREAM_START_OFFSET */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 259,
                dec_cont->hevc_regs[259]);

    HevcEnableDMVBuffer(dpb, dec_cont->core_id);

    /* start HW by clearing IRQ_BUFFER_EMPTY status bit */
    if (dec_cont->vcmd_used)
      DWLCmdPushSliceRegs(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->hevc_regs);
    else
      DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, dec_cont->hevc_regs[1]);
  }

  if (dec_cont->vcmd_used) {
    ret = DWLWaitCmdBufReady(dec_cont->dwl, dec_cont->cmdbuf_id);
  } else {
    ret = DWLWaitHwReady(dec_cont->dwl, dec_cont->core_id,
                         (u32)DEC_X170_TIMEOUT_LENGTH);
  }

#ifdef SUPPORT_DMA
#ifdef ENABLE_FPGA_VERIFICATION /* Just uesd for FPGA verification,
                                   the customer can remove it according to demand. */
/* - pp enable : the DMA transfers pp_buffer from device to host for verification.
 * - pp disable : the DMA transfers out_buffer from device to host for verification.
 */
  if (dec_cont->pp_enabled) /* pp enable */
    DWLDMATransData((addr_t)dec_cont->asic_buff->out_pp_buffer->bus_address,
                    (void *)dec_cont->asic_buff->out_pp_buffer->virtual_address,
                    dec_cont->asic_buff->out_pp_buffer->size, DEVICE_TO_HOST);
  else /* pp disable */ {
    /* buffer size of dpb pic = pic_size + sync_mc_size + dir_mv_size + tbl_size */
    u32 pic_size = dec_cont->storage.dpb->sync_mc_offset;
    DWLDMATransData((addr_t)dec_cont->asic_buff->out_buffer->bus_address,
                    (void *)dec_cont->asic_buff->out_buffer->virtual_address,
                    /* dec_cont->asic_buff->out_buffer->size */
                    pic_size, DEVICE_TO_HOST);
  }
#endif
#endif
  HevcDisableDMVBuffer(dpb, dec_cont->vcmd_used? dec_cont->mc_buf_id : dec_cont->core_id);
  if (ret != DWL_HW_WAIT_OK) {
    APITRACEDEBUG("%s","DWLWaitHwReady\n");
    APITRACEDEBUG("%s: %d\n", "DWLWaitHwReady returned",ret);

    /* Reset HW */
    SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ_STAT, 0);
    SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ, 0);

    dec_cont->asic_running = 0;
    if (!dec_cont->vcmd_used) {
      DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                   dec_cont->hevc_regs[1]);
      (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
    }
    else
      (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);

    /* Unbind tile_edge buffer with core_id */
    if (!dec_cont->vcmd_used)
      UnbindAsicTileEdgeMemsFromCore(dec_cont, dec_cont->core_id);
    else
      UnbindAsicTileEdgeMemsFromCore(dec_cont, dec_cont->cmdbuf_id);

    return (ret == DWL_HW_WAIT_ERROR) ? X170_DEC_SYSTEM_ERROR
           : X170_DEC_TIMEOUT;
  }
  if(dec_cont->vcmd_used) {
    DWLRefreshRegister(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->hevc_regs);
  }
  else {
    RefreshDecRegisters(dec_cont->dwl, dec_cont->core_id, dec_cont->hevc_regs,
                        hw_feature->max_ppu_count);
  }
  asic_status = GetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ_STAT);

  SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ_STAT, 0);
  SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_IRQ, 0); /* just in case */

  if (!(asic_status & DEC_HW_IRQ_BUFFER)) {
    /* HW done, release it! */
    dec_cont->asic_running = 0;

    while(dec_cont->low_latency && (!dec_cont->llstrminfo.updated_reg)){
      sched_yield();
    }
    if(dec_cont->low_latency)
      dec_cont->llstrminfo.updated_reg = 0;

    if (dec_cont->pp_enabled)
      DecreaseInputQueueCnt(dec_cont->pp_buffer_queue, dec_cont->asic_buff->out_pp_buffer->virtual_address);

    if (!dec_cont->vcmd_used)
      (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
    else
      (void)  DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);

    /* Unbind tile_edge buffer with core_id */
    if (!dec_cont->vcmd_used)
      UnbindAsicTileEdgeMemsFromCore(dec_cont, dec_cont->core_id);
    else
      UnbindAsicTileEdgeMemsFromCore(dec_cont, dec_cont->cmdbuf_id);

#ifdef SUPPORT_GDR
    /* SC mode: recovery_poc_cnt-- */
    if (dec_cont->storage.is_gdr_frame && dec_cont->storage.sei_param_curr)
      dec_cont->storage.sei_param_curr->recovery_param.recovery_poc_cnt--;
#endif
  }

  if (!dec_cont->secure_mode) {
    addr_t last_read_address;
    u32 bytes_processed;
    u32 total_error_ctbs = 0;
    const addr_t start_address =
      dec_cont->hw_stream_start_bus & (~DEC_HW_ALIGN_MASK);
    const u32 offset_bytes = dec_cont->hw_stream_start_bus & DEC_HW_ALIGN_MASK;

    last_read_address =
      GetDecRegister(dec_cont->hevc_regs, HWIF_STREAM_BASE_LSB);
    total_error_ctbs = GetDecRegister(dec_cont->hevc_regs, HWIF_TOTAL_ERROR_CTBS);

    if(sizeof(addr_t) == 8)
      last_read_address |= ((u64)GetDecRegister(dec_cont->hevc_regs, HWIF_STREAM_BASE_MSB))<<32;

    if (asic_status == DEC_HW_IRQ_RDY && last_read_address == dec_cont->hw_stream_start_bus &&
        !(dec_cont->hw_conceal && total_error_ctbs)) {
      last_read_address = start_address + dec_cont->hw_buffer_length;
    }

    if(last_read_address < start_address)
      bytes_processed = dec_cont->hw_buffer_length - (u32)(start_address - last_read_address);
    else
      bytes_processed = (u32)(last_read_address - start_address);

    APITRACEDEBUG("%s:%08lx\n","HW updated stream position",last_read_address);
    APITRACEDEBUG("%s:%8d\n","processed bytes",bytes_processed);
    APITRACEDEBUG("%s:%8d\n","of which offset bytes",offset_bytes);

    if (asic_status & DEC_HW_IRQ_BUFFER) {
      dec_cont->hw_stream_start += dec_cont->hw_length;
      dec_cont->hw_stream_start_bus += dec_cont->hw_length;
      dec_cont->hw_length = 0; /* no bytes left */
    } else {

      /* from start of the buffer add what HW has decoded */
      /* end - start smaller or equal than maximum */
      if(dec_cont->low_latency)
        dec_cont->hw_length = dec_cont->llstrminfo.tmp_length;
      if ((bytes_processed - offset_bytes) > dec_cont->hw_length) {

        if ((asic_status & DEC_HW_IRQ_RDY) || (asic_status & DEC_HW_IRQ_BUFFER)) {
          APITRACEDEBUG("%s","New stream position out of range!\n");
          // ASSERT(0);
          dec_cont->hw_stream_start += dec_cont->hw_length;
          dec_cont->hw_stream_start_bus += dec_cont->hw_length;
          dec_cont->hw_length = 0; /* no bytes left */
          dec_cont->stream_pos_updated = 1;

          /* Though asic_status returns DEC_HW_IRQ_BUFFER, the stream consumed is abnormal,
           * so we consider it's an errorous stream and release HW. */
          if (asic_status & DEC_HW_IRQ_BUFFER) {
            dec_cont->asic_running = 0;
            if (!dec_cont->vcmd_used)
              (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
            else
              (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);

            /* Unbind tile_edge buffer with core_id */
            if (!dec_cont->vcmd_used)
              UnbindAsicTileEdgeMemsFromCore(dec_cont, dec_cont->core_id);
            else
              UnbindAsicTileEdgeMemsFromCore(dec_cont, dec_cont->cmdbuf_id);

          }

          return DEC_HW_IRQ_RDY;
        }

        /* consider all buffer processed */
        dec_cont->hw_stream_start += dec_cont->hw_length;
        dec_cont->hw_stream_start_bus += dec_cont->hw_length;
        dec_cont->hw_length = 0; /* no bytes left */
      } else {
        dec_cont->hw_length -= (bytes_processed - offset_bytes);
        dec_cont->hw_stream_start += (bytes_processed - offset_bytes);
        dec_cont->hw_stream_start_bus += (bytes_processed - offset_bytes);
      }

      /* if turnaround */
      if(dec_cont->hw_stream_start > (dec_cont->hw_buffer + dec_cont->hw_buffer_length)) {
        dec_cont->hw_stream_start -= dec_cont->hw_buffer_length;
        dec_cont->hw_stream_start_bus -= dec_cont->hw_buffer_length;
      }
    }
    /* else will continue decoding from the beginning of buffer */
  } else {
    dec_cont->hw_stream_start += dec_cont->hw_length;
    dec_cont->hw_stream_start_bus += dec_cont->hw_length;
    dec_cont->hw_length = 0; /* no bytes left */
  }

  dec_cont->stream_pos_updated = 1;

  return asic_status;
}

void HevcSetRegs(struct HevcDecContainer *dec_cont) {
  u32 i;
  i8 poc_diff;
  struct HevcDecAsic *asic_buff = dec_cont->asic_buff;

  struct SeqParamSet *sps = dec_cont->storage.active_sps;
  struct PicParamSet *pps = dec_cont->storage.active_pps;
  const struct SliceHeader *slice_header = dec_cont->storage.slice_header;
  const struct DpbStorage *dpb = dec_cont->storage.dpb;
  const struct Storage *storage = &dec_cont->storage;
  u32 pixel_width = (sps->bit_depth_luma == 8 && sps->bit_depth_chroma == 8) ? 8 : 10;
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_HEVC_DEC, (const void **)&hw_feature);

  /* mono chrome */
  SetDecRegister(dec_cont->hevc_regs, HWIF_BLACKWHITE_E, sps->chroma_format_idc == 0);

  SetDecRegister(dec_cont->hevc_regs, HWIF_BIT_DEPTH_Y_MINUS8,
                 sps->bit_depth_luma - 8);
  SetDecRegister(dec_cont->hevc_regs, HWIF_BIT_DEPTH_C_MINUS8,
                 sps->bit_depth_chroma - 8);

  SetDecRegister(dec_cont->hevc_regs, HWIF_ERROR_CONCEAL_E, dec_cont->hw_conceal);
  SetDecRegister(dec_cont->hevc_regs, HWIF_SLICE_DEC_DIS, dec_cont->disable_slice_mode);
  SetDecRegister(dec_cont->hevc_regs, HWIF_PCM_E, sps->pcm_enabled);
  SetDecRegister(dec_cont->hevc_regs, HWIF_PCM_BITDEPTH_Y,
                 sps->pcm_bit_depth_luma);
  SetDecRegister(dec_cont->hevc_regs, HWIF_PCM_BITDEPTH_C,
                 sps->pcm_bit_depth_chroma);

  SetDecRegister(dec_cont->hevc_regs, HWIF_REFPICLIST_MOD_E,
                 pps->lists_modification_present_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_MIN_CB_SIZE,
                 sps->log_min_coding_block_size);
  SetDecRegister(dec_cont->hevc_regs, HWIF_MAX_CB_SIZE,
                 sps->log_max_coding_block_size);
  SetDecRegister(dec_cont->hevc_regs, HWIF_MIN_TRB_SIZE,
                 sps->log_min_transform_block_size);
  SetDecRegister(dec_cont->hevc_regs, HWIF_MAX_TRB_SIZE,
                 sps->log_max_transform_block_size);
  SetDecRegister(dec_cont->hevc_regs, HWIF_MIN_PCM_SIZE,
                 sps->log_min_pcm_block_size);
  SetDecRegister(dec_cont->hevc_regs, HWIF_MAX_PCM_SIZE,
                 sps->log_max_pcm_block_size);

  SetDecRegister(dec_cont->hevc_regs, HWIF_MAX_INTER_HIERDEPTH,
                 sps->max_transform_hierarchy_depth_inter);
  SetDecRegister(dec_cont->hevc_regs, HWIF_MAX_INTRA_HIERDEPTH,
                 sps->max_transform_hierarchy_depth_intra);

  SetDecRegister(dec_cont->hevc_regs, HWIF_ASYM_PRED_E,
                 sps->asymmetric_motion_partitions_enable);
  SetDecRegister(dec_cont->hevc_regs, HWIF_SAO_E,
                 sps->sample_adaptive_offset_enable);

  SetDecRegister(dec_cont->hevc_regs, HWIF_PCM_FILT_DISABLE,
                 sps->pcm_loop_filter_disable);

  SetDecRegister(
    dec_cont->hevc_regs, HWIF_TEMPOR_MVP_E,
    sps->temporal_mvp_enable && !IS_IDR_NAL_UNIT(storage->prev_nal_unit));

  SetDecRegister(dec_cont->hevc_regs, HWIF_SIGN_DATA_HIDE,
                 pps->sign_data_hiding_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_CABAC_INIT_PRESENT,
                 pps->cabac_init_present);

  SetDecRegister(dec_cont->hevc_regs, HWIF_REFIDX0_ACTIVE,
                 pps->num_ref_idx_l0_active);
  SetDecRegister(dec_cont->hevc_regs, HWIF_REFIDX1_ACTIVE,
                 pps->num_ref_idx_l1_active);

  SetDecRegister(dec_cont->hevc_regs, HWIF_PPS_ID, storage->active_pps_id);

  SetDecRegister(dec_cont->hevc_regs, HWIF_INIT_QP, pps->pic_init_qp);

  SetDecRegister(dec_cont->hevc_regs, HWIF_CONST_INTRA_E,
                 pps->constrained_intra_pred_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_TRANSFORM_SKIP_E,
                 pps->transform_skip_enable);

  SetDecRegister(dec_cont->hevc_regs, HWIF_CU_QPD_E, pps->cu_qp_delta_enabled);

  SetDecRegister(dec_cont->hevc_regs, HWIF_MAX_CU_QPD_DEPTH,
                 pps->diff_cu_qp_delta_depth);

  SetDecRegister(dec_cont->hevc_regs, HWIF_CH_QP_OFFSET,
                 asic_buff->chroma_qp_index_offset);
  SetDecRegister(dec_cont->hevc_regs, HWIF_CH_QP_OFFSET2,
                 asic_buff->chroma_qp_index_offset2);

  SetDecRegister(dec_cont->hevc_regs, HWIF_SLICE_CHQP_FLAG,
                 pps->slice_level_chroma_qp_offsets_present);

  SetDecRegister(dec_cont->hevc_regs, HWIF_WEIGHT_PRED_E,
                 pps->weighted_pred_flag);
  SetDecRegister(dec_cont->hevc_regs, HWIF_WEIGHT_BIPR_IDC,
                 pps->weighted_bi_pred_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_TRANSQ_BYPASS_E,
                 pps->trans_quant_bypass_enable);

  SetDecRegister(dec_cont->hevc_regs, HWIF_DEPEND_SLICE_E,
                 pps->dependent_slice_segments_enabled);

  SetDecRegister(dec_cont->hevc_regs, HWIF_SLICE_HDR_EBITS,
                 pps->num_extra_slice_header_bits);

  SetDecRegister(dec_cont->hevc_regs, HWIF_STRONG_SMOOTH_E,
                 sps->strong_intra_smoothing_enable);

  /* make sure that output pic sync memory is cleared */
  if (dec_cont->b_mc) {
#ifndef MEM_ONLY_DEV_CHECK
    char *sync_base = (char *) (asic_buff->out_dmv_buffer->virtual_address) - 32;
    (void) DWLmemset(sync_base, 0, 32);
#endif
#ifdef SUPPORT_DMA
    DWLDMATransData((addr_t)(asic_buff->out_dmv_buffer->bus_address - 32),
                    (void *)((u8*)asic_buff->out_dmv_buffer->virtual_address - 32),
                    32, HOST_TO_DEVICE);
#endif
  }

  SetDecRegister(dec_cont->hevc_regs, HWIF_ENTR_CODE_SYNCH_E,
                 pps->entropy_coding_sync_enabled_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_FILT_SLICE_BORDER,
                 pps->loop_filter_across_slices_enabled_flag);
  SetDecRegister(dec_cont->hevc_regs, HWIF_FILT_TILE_BORDER,
                 pps->loop_filter_across_tiles_enabled_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_FILT_CTRL_PRES,
                 pps->deblocking_filter_control_present_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_FILT_OVERRIDE_E,
                 pps->deblocking_filter_override_enabled_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_FILTERING_DIS,
                 pps->disable_deblocking_filter_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_FILT_OFFSET_BETA,
                 pps->beta_offset / 2);
  SetDecRegister(dec_cont->hevc_regs, HWIF_FILT_OFFSET_TC, pps->tc_offset / 2);

  SetDecRegister(dec_cont->hevc_regs, HWIF_PARALLEL_MERGE,
                 pps->log_parallel_merge_level);

  SetDecRegister(dec_cont->hevc_regs, HWIF_IDR_PIC_E,
                 IS_RAP_NAL_UNIT(storage->prev_nal_unit));

  SetDecRegister(dec_cont->hevc_regs, HWIF_HDR_SKIP_LENGTH,
                 slice_header->hw_skip_bits);
#ifdef HEVC_422
  SetDecRegister(dec_cont->hevc_regs, HWIF_YCBCR422_E, sps->chroma_format_idc==2);
#endif

#ifdef ENABLE_FPGA_VERIFICATION
  if (!dec_cont->pp_enabled) {
    DWLmemset(asic_buff->out_buffer->virtual_address, 0, asic_buff->out_buffer->size);
  #ifdef SUPPORT_DMA
    /* update device buffer by host buffer */
    DWLDMATransData((addr_t)asic_buff->out_buffer->bus_address,
                    (void *)asic_buff->out_buffer->virtual_address,
                    /* storage->pic_size +
                    NEXT_MULTIPLE(storage->pic_size / 2, MAX(16, ALIGN(dec_cont->align)))*/
                    asic_buff->out_buffer->size,
                    HOST_TO_DEVICE);
  #endif
  }
#else
  for (u32 i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if(dec_cont->ppu_cfg[i].enabled && dec_cont->ppu_cfg[i].pp_comp) {
      DWLmemset(asic_buff->out_pp_buffer->virtual_address, 0, asic_buff->out_pp_buffer->size);
      break;
    }
  }
#endif

  SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_YBASE,
               asic_buff->out_buffer->bus_address);

  /* offset to beginning of chroma part of out and ref pics */
  SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_CBASE,
               asic_buff->out_buffer->bus_address + storage->pic_size);

  if (dec_cont->skip_non_intra && dec_cont->pp_enabled)
    SetDecRegister(dec_cont->hevc_regs, HWIF_WRITE_MVS_E, 0);
  else
    SetDecRegister(dec_cont->hevc_regs, HWIF_WRITE_MVS_E, 1);

  SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_DBASE, asic_buff->out_dmv_buffer->bus_address
               /*asic_buff->out_buffer->bus_address + dpb->dir_mv_offset*/);

  if (dec_cont->error_policy & DEC_EC_SEEK_NEXT_I ||
      dec_cont->error_policy & DEC_EC_REF_REPLACE) {
    SetDecRegister(dec_cont->hevc_regs, HWIF_REF_FRAMES,
                  (dpb->num_poc_st_curr + dpb->num_poc_lt_curr));
  } else {
    /* reference pictures */
    /* we always set HWIF_REF_FRAMES as a positive value to
       avoid HW hang when decoding erroneous I frame */
    if (dec_cont->hw_conceal) {
      SetDecRegister(dec_cont->hevc_regs, HWIF_REF_FRAMES,
                    (dpb->num_poc_st_curr + dpb->num_poc_lt_curr));
    } else {
      SetDecRegister(dec_cont->hevc_regs, HWIF_REF_FRAMES,
                    ((dpb->num_poc_st_curr + dpb->num_poc_lt_curr) == 0) ? 1 :
                    (dpb->num_poc_st_curr + dpb->num_poc_lt_curr));
    }
  }

  if (dec_cont->use_video_compressor) {
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_TYBASE,
                 asic_buff->out_buffer->bus_address + dpb->cbs_tbl_offsety);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_TCBASE,
                 asic_buff->out_buffer->bus_address + dpb->cbs_tbl_offsetc);
    SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_EC_BYPASS, 0);
    /* If the size of CBS row >= 64KB, which means it's possible that the offset
       may overflow in EC table, set the EC output in word alignment. */
    if (RFC_MAY_OVERFLOW(sps->pic_width, pixel_width))
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_EC_BYTE_WORD, 1);
    else
      SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_EC_BYTE_WORD, 0);
  } else {
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_TYBASE, 0L);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_DEC_OUT_TCBASE, 0L);
    SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_EC_BYPASS, 1);
  }

  SetDecRegister(dec_cont->hevc_regs, HWIF_SLICE_HDR_EXT_E,
                 pps->slice_header_extension_present_flag);

  SetDecRegister(dec_cont->hevc_regs, HWIF_UNIQUE_ID,
                 UNIQUE_ID(dec_cont->pic_number));

  /* Raster output configuration. */
  if (dec_cont->pp_enabled) {
    struct DWLLinearMem *pp_buffer = asic_buff->out_pp_buffer;

    /* Flexible PP */
    PpUnitIntConfig *ppu_cfg = &dec_cont->ppu_cfg[0];
    addr_t ppu_out_bus_addr = pp_buffer->bus_address;

    SetDecRegister(dec_cont->hevc_regs, HWIF_PP_IN_FORMAT_U, 1);
    PPSetRegs(dec_cont->hevc_regs, hw_feature, ppu_cfg, ppu_out_bus_addr, 0, 0);
    DelogoSetRegs(dec_cont->hevc_regs, hw_feature, dec_cont->delogo_params);
    if (dec_cont->partial_decoding && (!(IS_RAP_NAL_UNIT(storage->prev_nal_unit)))) {
      SetDecRegister(dec_cont->hevc_regs, HWIF_PP_OUT_E_U, 0);
    }
  }

  /* No stride when compression is used. */
  u32 out_w = storage->pic_width_in_cbs * (1 << sps->log_min_coding_block_size);
  u32 out_w_y, out_w_c;
  if (!dec_cont->use_video_compressor) {
    out_w_y =  NEXT_MULTIPLE(TILE_HEIGHT * out_w * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
    out_w_c = NEXT_MULTIPLE(4 * out_w * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
  } else {
    if (hw_feature->rfc_support) {
      out_w_y = NEXT_MULTIPLE(8 * out_w * pixel_width, ALIGN(dec_cont->align) * 8) >> 3;
      out_w_c = NEXT_MULTIPLE(4 * out_w * pixel_width, ALIGN(dec_cont->align) * 8) >> 3;
    } else {
      out_w_y = out_w_c = 4 * out_w * pixel_width / 8;
    }
  }
  SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_Y_STRIDE, out_w_y /8);  //in unit of 8 bytes
  SetDecRegister(dec_cont->hevc_regs, HWIF_DEC_OUT_C_STRIDE, out_w_c / 8); //in unit of 8 bytes


  /* POCs of reference pictures */
  for (i = 0; i < MAX_DPB_SIZE; i++) {
    poc_diff = CLIP3(-128, 127, (i32)storage->poc->pic_order_cnt -
                     (i32)dpb->current_out->ref_poc[i]);
    SetDecRegister(dec_cont->hevc_regs, ref_poc_regs[i], poc_diff);
  }

  HevcStreamPosUpdate(dec_cont);
}

void HevcInitRefPicList(struct HevcDecContainer *dec_cont) {
  struct DpbStorage *dpb = dec_cont->storage.dpb;
  u32 i, j;
  u32 list0[16] = {0};
  u32 list1[16] = {0};

  /* list 0, short term before + short term after + long term */
  for (i = 0, j = 0; i < dpb->num_poc_st_curr; i++)
    list0[j++] = dpb->ref_pic_set_st[i];
  for (i = 0; i < dpb->num_poc_lt_curr; i++)
    list0[j++] = dpb->ref_pic_set_lt[i];

  /* fill upto 16 elems, copy over and over */
  i = 0;
  while (j < 16) list0[j++] = list0[i++];

  /* list 1, short term after + short term before + long term */
  /* after */
  for (i = dpb->num_poc_st_curr_before, j = 0; i < dpb->num_poc_st_curr; i++)
    list1[j++] = dpb->ref_pic_set_st[i];
  /* before */
  for (i = 0; i < dpb->num_poc_st_curr_before; i++)
    list1[j++] = dpb->ref_pic_set_st[i];
  for (i = 0; i < dpb->num_poc_lt_curr; i++)
    list1[j++] = dpb->ref_pic_set_lt[i];

  /* fill upto 16 elems, copy over and over */
  i = 0;
  while (j < 16) list1[j++] = list1[i++];

  /* TODO: size? */
  for (i = 0; i < MAX_DPB_SIZE; i++) {
    SetDecRegister(dec_cont->hevc_regs, ref_pic_list0[i], list0[i]);
    SetDecRegister(dec_cont->hevc_regs, ref_pic_list1[i], list1[i]);
  }
}

void HevcStreamPosUpdate(struct HevcDecContainer *dec_cont) {
  u32 tmp, is_rb;
  addr_t tmp_addr;
  SwReadByteFn *fn_read_byte;

  tmp = 0;
  is_rb = dec_cont->use_ringbuffer;
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_HEVC_DEC, (const void **)&hw_feature);

  fn_read_byte = SwGetReadByteFunc(&dec_cont->llstrminfo.stream_info);

  /* NAL start prefix in stream start is 0 0 0 or 0 0 1 */
  if (dec_cont->hw_stream_start + 2 >= dec_cont->hw_buffer + dec_cont->hw_buffer_length) {
    u8 i, start_prefix[3];
    for(i = 0; i < 3; i++) {
      if (dec_cont->hw_stream_start + i < dec_cont->hw_buffer + dec_cont->hw_buffer_length)
        start_prefix[i] = fn_read_byte(dec_cont->hw_stream_start + i, dec_cont->hw_buffer_length,
                                       &dec_cont->llstrminfo.stream_info);
      else
        start_prefix[i] = fn_read_byte(dec_cont->hw_stream_start + i - dec_cont->hw_buffer_length,
                                       dec_cont->hw_buffer_length, &dec_cont->llstrminfo.stream_info);
    }
    if (!(*start_prefix + *(start_prefix + 1))) {
      if (*(start_prefix + 2) < 2) {
        tmp = 1;
      }
    }
  } else {
    if (!(fn_read_byte(dec_cont->hw_stream_start, dec_cont->hw_buffer_length, &dec_cont->llstrminfo.stream_info) +
          fn_read_byte(dec_cont->hw_stream_start + 1, dec_cont->hw_buffer_length, &dec_cont->llstrminfo.stream_info))) {
      if (fn_read_byte(dec_cont->hw_stream_start + 2, dec_cont->hw_buffer_length, &dec_cont->llstrminfo.stream_info) < 2) {
        tmp = 1;
      }
    }
  }

  if (dec_cont->start_code_detected)
      tmp = 1;

  SetDecRegister(dec_cont->hevc_regs, HWIF_START_CODE_E, tmp);

  /* bit offset if base is unaligned */
  tmp = (dec_cont->hw_stream_start_bus & DEC_HW_ALIGN_MASK) * 8;

  SetDecRegister(dec_cont->hevc_regs, HWIF_STRM_START_BIT, tmp);

  dec_cont->hw_bit_pos = tmp;

  if(is_rb) {
    /* stream buffer base address */
    tmp_addr = dec_cont->hw_buffer_start_bus; /* aligned base */
    ASSERT((tmp_addr & 0xF) == 0);
    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_STREAM_BASE, tmp_addr);

    /* stream data start offset */
    tmp = dec_cont->hw_stream_start_bus - dec_cont->hw_buffer_start_bus; /* unaligned base */
    tmp &= (~DEC_HW_ALIGN_MASK);         /* align the base */

      SetDecRegister(dec_cont->hevc_regs, HWIF_STRM_START_OFFSET, tmp);

    /* stream data length */
    tmp = dec_cont->hw_length;       /* unaligned stream */
    tmp += dec_cont->hw_bit_pos / 8; /* add the alignmet bytes */

    if(dec_cont->low_latency) {
      dec_cont->llstrminfo.ll_strm_bus_address = dec_cont->hw_stream_start_bus;
      dec_cont->llstrminfo.ll_strm_len = tmp;
      dec_cont->llstrminfo.first_update = 1;
      SetDecRegister(dec_cont->hevc_regs, HWIF_STREAM_LEN, 0);
      SetDecRegister(dec_cont->hevc_regs, HWIF_LAST_BUFFER_E, 0);
      if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
        *dec_cont->llstrminfo.strm_status_addr = 0;
      }
      dec_cont->llstrminfo.update_reg_flag = 1;
    } else
      SetDecRegister(dec_cont->hevc_regs, HWIF_STREAM_LEN, tmp);

    /* stream buffer size */
    tmp = dec_cont->hw_buffer_length;       /* stream buffer size */

    SetDecRegister(dec_cont->hevc_regs, HWIF_STRM_BUFFER_LEN, tmp);
  } else {
    /* stream data base address */
    tmp_addr = dec_cont->hw_stream_start_bus; /* unaligned base */
    tmp_addr &= (~((addr_t)DEC_HW_ALIGN_MASK));         /* align the base */
    ASSERT((tmp_addr & 0xF) == 0);

    SET_ADDR_REG(dec_cont->hevc_regs, HWIF_STREAM_BASE, tmp_addr);

    /* stream data start offset */
    SetDecRegister(dec_cont->hevc_regs, HWIF_STRM_START_OFFSET, 0);

    /* stream data length */
    tmp = dec_cont->hw_length;       /* unaligned stream */
    tmp += dec_cont->hw_bit_pos / 8; /* add the alignmet bytes */

    if(dec_cont->low_latency) {
      dec_cont->llstrminfo.ll_strm_bus_address = dec_cont->hw_stream_start_bus;
      dec_cont->llstrminfo.ll_strm_len = tmp;
      dec_cont->llstrminfo.first_update = 1;
      SetDecRegister(dec_cont->hevc_regs, HWIF_STREAM_LEN, 0);
      SetDecRegister(dec_cont->hevc_regs, HWIF_LAST_BUFFER_E, 0);
      if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
        *dec_cont->llstrminfo.strm_status_addr = 0;
      }
      dec_cont->llstrminfo.update_reg_flag = 1;
    } else
      SetDecRegister(dec_cont->hevc_regs, HWIF_STREAM_LEN, tmp);

    /* stream buffer size */
    tmp = dec_cont->hw_buffer_start_bus + dec_cont->hw_buffer_length - tmp_addr;

    SetDecRegister(dec_cont->hevc_regs, HWIF_STRM_BUFFER_LEN, tmp);
  }

#ifdef SUPPORT_DMA
  DWLDMATransData((addr_t)dec_cont->hw_buffer_start_bus,
                  (void *)dec_cont->hw_buffer,
                  dec_cont->hw_buffer_length, HOST_TO_DEVICE);
#endif
}

u32 HevcCheckHwStatus(struct HevcDecContainer *dec_cont) {
   u32 tmp = 0;
   if (dec_cont->vcmd_used) {
     tmp = dec_cont->hevc_regs[1];
   } else {
     tmp = DWLReadRegFromHw(dec_cont->dwl, dec_cont->core_id, 4 * 1);
   }

   if(tmp & 0x01)
     return 1;
   else
     return 0;
}
