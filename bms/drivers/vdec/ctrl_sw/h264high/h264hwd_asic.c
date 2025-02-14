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

#include "basetype.h"
#include "regdrv.h"
#include "h264hwd_asic.h"
#include "h264hwd_container.h"
#include "sw_debug.h"
#include "h264hwd_util.h"
#include "h264hwd_cabac.h"
#include "dwl.h"
#include "h264hwd_decoder.h"
#include "h264decmc_internals.h"
#include "vpufeature.h"
#include "ppu.h"
#include "delogo.h"
#include "commonconfig.h"
#include "commonfunction.h"
#include "errorhandling.h"
#include "dec_log.h"
#include "sw_stream.h"

#define ASIC_HOR_MV_MASK            0x07FFFU
#define ASIC_VER_MV_MASK            0x01FFFU

#define ASIC_HOR_MV_OFFSET          17U
#define ASIC_VER_MV_OFFSET          4U

#define DEC_X170_ALIGN_MASK         0x07

static void H264RefreshRegs(struct H264DecContainer * dec_cont);
static void H264FlushRegs(struct H264DecContainer * dec_cont);
static void h264StreamPosUpdate(struct H264DecContainer * dec_cont);
static void H264PrepareCabacInitTables(u32 *cabac_init);
static void h264PreparePOC(struct H264DecContainer *dec_cont);
static void h264PrepareScaleList(struct H264DecContainer *dec_cont);
static void h264CopyPocToHw(struct H264DecContainer *dec_cont);
#ifndef TRACE_PP_CTRL
#define TRACE_PP_CTRL(...)          do{}while(0)
#else
#undef TRACE_PP_CTRL
#define TRACE_PP_CTRL(...)          printf(__VA_ARGS__)
#endif

static const u32 ref_base[16] = {
  HWIF_REFER0_BASE_LSB, HWIF_REFER1_BASE_LSB, HWIF_REFER2_BASE_LSB,
  HWIF_REFER3_BASE_LSB, HWIF_REFER4_BASE_LSB, HWIF_REFER5_BASE_LSB,
  HWIF_REFER6_BASE_LSB, HWIF_REFER7_BASE_LSB, HWIF_REFER8_BASE_LSB,
  HWIF_REFER9_BASE_LSB, HWIF_REFER10_BASE_LSB, HWIF_REFER11_BASE_LSB,
  HWIF_REFER12_BASE_LSB, HWIF_REFER13_BASE_LSB, HWIF_REFER14_BASE_LSB,
  HWIF_REFER15_BASE_LSB
};
static const u32 ref_base_msb[16] = {
  HWIF_REFER0_BASE_MSB, HWIF_REFER1_BASE_MSB, HWIF_REFER2_BASE_MSB,
  HWIF_REFER3_BASE_MSB, HWIF_REFER4_BASE_MSB, HWIF_REFER5_BASE_MSB,
  HWIF_REFER6_BASE_MSB, HWIF_REFER7_BASE_MSB, HWIF_REFER8_BASE_MSB,
  HWIF_REFER9_BASE_MSB, HWIF_REFER10_BASE_MSB, HWIF_REFER11_BASE_MSB,
  HWIF_REFER12_BASE_MSB, HWIF_REFER13_BASE_MSB, HWIF_REFER14_BASE_MSB,
  HWIF_REFER15_BASE_MSB
};
/*
static const u32 ref_field_mode[16] = {
  HWIF_REFER0_FIELD_E, HWIF_REFER1_FIELD_E, HWIF_REFER2_FIELD_E,
  HWIF_REFER3_FIELD_E, HWIF_REFER4_FIELD_E, HWIF_REFER5_FIELD_E,
  HWIF_REFER6_FIELD_E, HWIF_REFER7_FIELD_E, HWIF_REFER8_FIELD_E,
  HWIF_REFER9_FIELD_E, HWIF_REFER10_FIELD_E, HWIF_REFER11_FIELD_E,
  HWIF_REFER12_FIELD_E, HWIF_REFER13_FIELD_E, HWIF_REFER14_FIELD_E,
  HWIF_REFER15_FIELD_E
};
*/
const u32 ref_topc[16] = {
  HWIF_REFER0_TOPC_E, HWIF_REFER1_TOPC_E, HWIF_REFER2_TOPC_E,
  HWIF_REFER3_TOPC_E, HWIF_REFER4_TOPC_E, HWIF_REFER5_TOPC_E,
  HWIF_REFER6_TOPC_E, HWIF_REFER7_TOPC_E, HWIF_REFER8_TOPC_E,
  HWIF_REFER9_TOPC_E, HWIF_REFER10_TOPC_E, HWIF_REFER11_TOPC_E,
  HWIF_REFER12_TOPC_E, HWIF_REFER13_TOPC_E, HWIF_REFER14_TOPC_E,
  HWIF_REFER15_TOPC_E
};

static const u32 ref_pic_num[16] = {
  HWIF_REFER0_NBR, HWIF_REFER1_NBR, HWIF_REFER2_NBR,
  HWIF_REFER3_NBR, HWIF_REFER4_NBR, HWIF_REFER5_NBR,
  HWIF_REFER6_NBR, HWIF_REFER7_NBR, HWIF_REFER8_NBR,
  HWIF_REFER9_NBR, HWIF_REFER10_NBR, HWIF_REFER11_NBR,
  HWIF_REFER12_NBR, HWIF_REFER13_NBR, HWIF_REFER14_NBR,
  HWIF_REFER15_NBR
};

static const u32 ref_cbase[16] = {
  HWIF_REFER0_CBASE_LSB,  HWIF_REFER1_CBASE_LSB,  HWIF_REFER2_CBASE_LSB,
  HWIF_REFER3_CBASE_LSB,  HWIF_REFER4_CBASE_LSB,  HWIF_REFER5_CBASE_LSB,
  HWIF_REFER6_CBASE_LSB,  HWIF_REFER7_CBASE_LSB,  HWIF_REFER8_CBASE_LSB,
  HWIF_REFER9_CBASE_LSB,  HWIF_REFER10_CBASE_LSB, HWIF_REFER11_CBASE_LSB,
  HWIF_REFER12_CBASE_LSB, HWIF_REFER13_CBASE_LSB, HWIF_REFER14_CBASE_LSB,
  HWIF_REFER15_CBASE_LSB
};

static const u32 ref_cbase_msb[16] = {
  HWIF_REFER0_CBASE_MSB,  HWIF_REFER1_CBASE_MSB,  HWIF_REFER2_CBASE_MSB,
  HWIF_REFER3_CBASE_MSB,  HWIF_REFER4_CBASE_MSB,  HWIF_REFER5_CBASE_MSB,
  HWIF_REFER6_CBASE_MSB,  HWIF_REFER7_CBASE_MSB,  HWIF_REFER8_CBASE_MSB,
  HWIF_REFER9_CBASE_MSB,  HWIF_REFER10_CBASE_MSB, HWIF_REFER11_CBASE_MSB,
  HWIF_REFER12_CBASE_MSB, HWIF_REFER13_CBASE_MSB, HWIF_REFER14_CBASE_MSB,
  HWIF_REFER15_CBASE_MSB
};

static const u32 ref_dbase[16] = {
  HWIF_REFER0_DBASE_LSB,  HWIF_REFER1_DBASE_LSB,  HWIF_REFER2_DBASE_LSB,
  HWIF_REFER3_DBASE_LSB,  HWIF_REFER4_DBASE_LSB,  HWIF_REFER5_DBASE_LSB,
  HWIF_REFER6_DBASE_LSB,  HWIF_REFER7_DBASE_LSB,  HWIF_REFER8_DBASE_LSB,
  HWIF_REFER9_DBASE_LSB,  HWIF_REFER10_DBASE_LSB, HWIF_REFER11_DBASE_LSB,
  HWIF_REFER12_DBASE_LSB, HWIF_REFER13_DBASE_LSB, HWIF_REFER14_DBASE_LSB,
  HWIF_REFER15_DBASE_LSB
};

static const u32 ref_dbase_msb[16] = {
  HWIF_REFER0_DBASE_MSB,  HWIF_REFER1_DBASE_MSB,  HWIF_REFER2_DBASE_MSB,
  HWIF_REFER3_DBASE_MSB,  HWIF_REFER4_DBASE_MSB,  HWIF_REFER5_DBASE_MSB,
  HWIF_REFER6_DBASE_MSB,  HWIF_REFER7_DBASE_MSB,  HWIF_REFER8_DBASE_MSB,
  HWIF_REFER9_DBASE_MSB,  HWIF_REFER10_DBASE_MSB, HWIF_REFER11_DBASE_MSB,
  HWIF_REFER12_DBASE_MSB, HWIF_REFER13_DBASE_MSB, HWIF_REFER14_DBASE_MSB,
  HWIF_REFER15_DBASE_MSB
};

static const u32 ref_tybase[16] = {
  HWIF_REFER0_TYBASE_LSB, HWIF_REFER1_TYBASE_LSB, HWIF_REFER2_TYBASE_LSB,
  HWIF_REFER3_TYBASE_LSB, HWIF_REFER4_TYBASE_LSB, HWIF_REFER5_TYBASE_LSB,
  HWIF_REFER6_TYBASE_LSB, HWIF_REFER7_TYBASE_LSB, HWIF_REFER8_TYBASE_LSB,
  HWIF_REFER9_TYBASE_LSB, HWIF_REFER10_TYBASE_LSB, HWIF_REFER11_TYBASE_LSB,
  HWIF_REFER12_TYBASE_LSB, HWIF_REFER13_TYBASE_LSB, HWIF_REFER14_TYBASE_LSB,
  HWIF_REFER15_TYBASE_LSB
};

static const u32 ref_tybase_msb[16] = {
  HWIF_REFER0_TYBASE_MSB, HWIF_REFER1_TYBASE_MSB, HWIF_REFER2_TYBASE_MSB,
  HWIF_REFER3_TYBASE_MSB, HWIF_REFER4_TYBASE_MSB, HWIF_REFER5_TYBASE_MSB,
  HWIF_REFER6_TYBASE_MSB, HWIF_REFER7_TYBASE_MSB, HWIF_REFER8_TYBASE_MSB,
  HWIF_REFER9_TYBASE_MSB, HWIF_REFER10_TYBASE_MSB, HWIF_REFER11_TYBASE_MSB,
  HWIF_REFER12_TYBASE_MSB, HWIF_REFER13_TYBASE_MSB, HWIF_REFER14_TYBASE_MSB,
  HWIF_REFER15_TYBASE_MSB
};

static const u32 ref_tcbase[16] = {
  HWIF_REFER0_TCBASE_LSB, HWIF_REFER1_TCBASE_LSB, HWIF_REFER2_TCBASE_LSB,
  HWIF_REFER3_TCBASE_LSB, HWIF_REFER4_TCBASE_LSB, HWIF_REFER5_TCBASE_LSB,
  HWIF_REFER6_TCBASE_LSB, HWIF_REFER7_TCBASE_LSB, HWIF_REFER8_TCBASE_LSB,
  HWIF_REFER9_TCBASE_LSB, HWIF_REFER10_TCBASE_LSB, HWIF_REFER11_TCBASE_LSB,
  HWIF_REFER12_TCBASE_LSB, HWIF_REFER13_TCBASE_LSB, HWIF_REFER14_TCBASE_LSB,
  HWIF_REFER15_TCBASE_LSB
};

static const u32 ref_tcbase_msb[16] = {
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
#define IS_SHORT_TERM_FRAME(a) ((a).status[0] == SHORT_TERM && \
                                (a).status[1] == SHORT_TERM)
#define IS_SHORT_TERM_FRAME_F(a) ((a).status[0] == SHORT_TERM || \
                                (a).status[1] == SHORT_TERM)
#define IS_LONG_TERM_FRAME(a) ((a).status[0] == LONG_TERM && \
                                (a).status[1] == LONG_TERM)
#define IS_LONG_TERM_FRAME_F(a) ((a).status[0] == LONG_TERM || \
                                (a).status[1] == LONG_TERM)
#define IS_REF_FRAME(a) ((a).status[0] && (a).status[0] != EMPTY && \
                         (a).status[1] && (a).status[1] != EMPTY )
#define IS_REF_FRAME_F(a) (((a).status[0] && (a).status[0] != EMPTY) || \
                           ((a).status[1] && (a).status[1] != EMPTY) )

/* a reference picture with one field missing */
#define IS_REF_MISSING_F(a) (((a).status[0] && (a).status[0] != EMPTY && \
                              (a).status[1] == EMPTY ) || \
                           ((a).status[1] && (a).status[1] != EMPTY && \
                              (a).status[0] == EMPTY))

#define FRAME_POC(a) MIN((a).pic_order_cnt[0], (a).pic_order_cnt[1])
#define FIELD_POC(a) MIN(((a).status[0] != EMPTY) ? \
                          (a).pic_order_cnt[0] : 0x7FFFFFFF,\
                         ((a).status[1] != EMPTY) ? \
                          (a).pic_order_cnt[1] : 0x7FFFFFFF)

#define INVALID_IDX 0xFFFFFFFF
#define MIN_POC 0x80000000
#define MAX_POC 0x7FFFFFFF

#define ABS(a) (((a) < 0) ? -(a) : (a))
#define GET_POC(pic)            GetPoc(&(pic))
// #define IS_REFERENCE_F(a)       IsReferenceField(&(a))
// #define IS_REFERENCE(a,f)       IsReference(&(a),f)

static u32 IsRefValid(u32 valid_flag, u32 index) {
  valid_flag = valid_flag >> 16;
  return ((valid_flag >> (15 - index)) & 1);
}

#define IS_REF_VALID(a,f)       IsRefValid(a,f)

static const u32 ref_pic_list0_g1[16] = {
  HWIF_BINIT_RLIST_F0, HWIF_BINIT_RLIST_F1, HWIF_BINIT_RLIST_F2,
  HWIF_BINIT_RLIST_F3, HWIF_BINIT_RLIST_F4, HWIF_BINIT_RLIST_F5,
  HWIF_BINIT_RLIST_F6, HWIF_BINIT_RLIST_F7, HWIF_BINIT_RLIST_F8,
  HWIF_BINIT_RLIST_F9, HWIF_BINIT_RLIST_F10, HWIF_BINIT_RLIST_F11,
  HWIF_BINIT_RLIST_F12, HWIF_BINIT_RLIST_F13, HWIF_BINIT_RLIST_F14,
  HWIF_BINIT_RLIST_F15
};

static const u32 ref_pic_list1_g1[16] = {
  HWIF_BINIT_RLIST_B0, HWIF_BINIT_RLIST_B1, HWIF_BINIT_RLIST_B2,
  HWIF_BINIT_RLIST_B3, HWIF_BINIT_RLIST_B4, HWIF_BINIT_RLIST_B5,
  HWIF_BINIT_RLIST_B6, HWIF_BINIT_RLIST_B7, HWIF_BINIT_RLIST_B8,
  HWIF_BINIT_RLIST_B9, HWIF_BINIT_RLIST_B10, HWIF_BINIT_RLIST_B11,
  HWIF_BINIT_RLIST_B12, HWIF_BINIT_RLIST_B13, HWIF_BINIT_RLIST_B14,
  HWIF_BINIT_RLIST_B15
};

static const u32 ref_pic_list_p[16] = {
  HWIF_PINIT_RLIST_F0, HWIF_PINIT_RLIST_F1, HWIF_PINIT_RLIST_F2,
  HWIF_PINIT_RLIST_F3, HWIF_PINIT_RLIST_F4, HWIF_PINIT_RLIST_F5,
  HWIF_PINIT_RLIST_F6, HWIF_PINIT_RLIST_F7, HWIF_PINIT_RLIST_F8,
  HWIF_PINIT_RLIST_F9, HWIF_PINIT_RLIST_F10, HWIF_PINIT_RLIST_F11,
  HWIF_PINIT_RLIST_F12, HWIF_PINIT_RLIST_F13, HWIF_PINIT_RLIST_F14,
  HWIF_PINIT_RLIST_F15
};

static const u32 ref_pic_list0[16] = {
  HWIF_INIT_RLIST_F0,  HWIF_INIT_RLIST_F1,  HWIF_INIT_RLIST_F2,
  HWIF_INIT_RLIST_F3,  HWIF_INIT_RLIST_F4,  HWIF_INIT_RLIST_F5,
  HWIF_INIT_RLIST_F6,  HWIF_INIT_RLIST_F7,  HWIF_INIT_RLIST_F8,
  HWIF_INIT_RLIST_F9,  HWIF_INIT_RLIST_F10, HWIF_INIT_RLIST_F11,
  HWIF_INIT_RLIST_F12, HWIF_INIT_RLIST_F13, HWIF_INIT_RLIST_F14,
  HWIF_INIT_RLIST_F15
};

static const u32 ref_pic_list1[16] = {
  HWIF_INIT_RLIST_B0,  HWIF_INIT_RLIST_B1,  HWIF_INIT_RLIST_B2,
  HWIF_INIT_RLIST_B3,  HWIF_INIT_RLIST_B4,  HWIF_INIT_RLIST_B5,
  HWIF_INIT_RLIST_B6,  HWIF_INIT_RLIST_B7,  HWIF_INIT_RLIST_B8,
  HWIF_INIT_RLIST_B9,  HWIF_INIT_RLIST_B10, HWIF_INIT_RLIST_B11,
  HWIF_INIT_RLIST_B12, HWIF_INIT_RLIST_B13, HWIF_INIT_RLIST_B14,
  HWIF_INIT_RLIST_B15
};

static i32 GetPoc(dpbPicture_t *pic) {
  i32 poc0 = (pic->status[0] == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt[0]);
  i32 poc1 = (pic->status[1] == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt[1]);
  return MIN(poc0,poc1);
}

#if 0
static u32 IsReferenceField( const dpbPicture_t *a) {
  return (a->status[0] != UNUSED && a->status[0] != EMPTY) ||
         (a->status[1] != UNUSED && a->status[1] != EMPTY);
}

static u32 IsReference( const dpbPicture_t a, const u32 f ) {
  switch(f) {
    case TOPFIELD: return a->status[0] && a->status[0] != EMPTY;
    case BOTFIELD: return a->status[1] && a->status[1] != EMPTY;
    default: return a->status[0] && a->status[0] != EMPTY &&
                 a->status[1] && a->status[1] != EMPTY;
  }
}
#endif

#ifdef REORDER_ERROR_FIX
static u32 IsExisting(const dpbPicture_t *a, const u32 f) {
  if(f < FRAME) {
    return  (a->status[f] > NON_EXISTING) &&
            (a->status[f] != EMPTY);
  } else {
    return (a->status[0] > NON_EXISTING) &&
           (a->status[0] != EMPTY) &&
           (a->status[1] > NON_EXISTING) &&
           (a->status[1] != EMPTY);
  }
}
#endif

/*------------------------------------------------------------------------------
    Function name : AllocateAsicBuffers
    Description   :

    Return type   : i32
    Argument      : DecAsicBuffers_t * asic_buff
    Argument      : u32 mbs
------------------------------------------------------------------------------*/
u32 AllocateAsicBuffers(struct H264DecContainer * dec_cont, DecAsicBuffers_t * asic_buff,
                        u32 mbs) {
  i32 ret = 0;
  u32 tmp, i;

  if(dec_cont->rlc_mode) {
    tmp = ASIC_MB_CTRL_BUFFER_SIZE;
    asic_buff[0].mb_ctrl.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    ret = DWLMallocLinear(dec_cont->dwl, mbs * tmp, &asic_buff[0].mb_ctrl);

    tmp = ASIC_MB_MV_BUFFER_SIZE;
    asic_buff[0].mv.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    ret |= DWLMallocLinear(dec_cont->dwl, mbs * tmp, &asic_buff[0].mv);

    tmp = ASIC_MB_I4X4_BUFFER_SIZE;
    asic_buff[0].intra_pred.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    ret |=
      DWLMallocLinear(dec_cont->dwl, mbs * tmp, &asic_buff[0].intra_pred);

    tmp = ASIC_MB_RLC_BUFFER_SIZE;
    asic_buff[0].residual.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    ret |= DWLMallocLinear(dec_cont->dwl, mbs * tmp, &asic_buff[0].residual);
  }

  asic_buff[0].buff_status = 0;
  asic_buff[0].pic_size_in_mbs = mbs;

  if (dec_cont->h264_profile_support != H264_BASELINE_PROFILE ||
      dec_cont->hw_conceal) {
    if (!dec_cont->high10p_mode)
      tmp = ASIC_CABAC_INIT_BUFFER_SIZE + ASIC_SCALING_LIST_SIZE +
            ASIC_POC_BUFFER_SIZE;
    else
      tmp = ASIC_CABAC_INIT_BUFFER_SIZE + ASIC_SCALING_LIST_SIZE +
          ASIC_POC_BUFFER_SIZE_H10;

    for(i = 0; i < dec_cont->n_cores; i++) {
      asic_buff->cabac_init[i].mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE |
                                          DWL_MEM_TYPE_VPU_WORKING;
      ret |= DWLMallocLinear(dec_cont->dwl, tmp,
                             asic_buff->cabac_init + i);
      if(ret == 0) {
        H264PrepareCabacInitTables(
          asic_buff->cabac_init[i].virtual_address);
      }
    }
  }
  /* Allocate buffer for using ddr_low_latency model */
  if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
    dec_cont->llstrminfo.strm_status.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    ret |= DWLMallocLinear(dec_cont->dwl, 16 * 4, &dec_cont->llstrminfo.strm_status);
  }
  if(ret != 0)
    return 1;

#ifdef USE_FAKE_RFC_TABLE
  if (dec_cont->high10p_mode && (dec_cont->storage.use_video_compressor)) {
    /* Allocate and initialize fake RFC table for robustness. */
    u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));
    storage_t *storage = &dec_cont->storage;
    seqParamSet_t *sps = storage->active_sps;
    u32 pic_width_in_cbsy, pic_height_in_cbsy;
    u32 pic_width_in_cbsc, pic_height_in_cbsc;
    u32 bit_depth = (sps->bit_depth_luma == 8 && sps->bit_depth_chroma == 8) ? 8 : 10;

    pic_width_in_cbsy = ((sps->pic_width_in_mbs * 16 + 8 - 1)/8);
    pic_width_in_cbsy = NEXT_MULTIPLE(pic_width_in_cbsy, 16);
    pic_width_in_cbsc = ((sps->pic_width_in_mbs * 16 + 16 - 1)/16);
    pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
    pic_height_in_cbsy = (sps->pic_height_in_mbs * 16 + 8 - 1)/8;
    pic_height_in_cbsc = (sps->pic_height_in_mbs * 16/2 + 4 - 1)/4;
    if(sps->chroma_format_idc==2)
      pic_height_in_cbsc = (sps->pic_height_in_mbs * 16 + 4 - 1)/4;

    H264GetRefFrmSize(&dec_cont->storage,
                      &asic_buff[0].tbl_sizey,
                      &asic_buff[0].tbl_sizec);
    asic_buff[0].tbl_sizey = NEXT_MULTIPLE(asic_buff[0].tbl_sizey, ref_buffer_align);
    asic_buff[0].tbl_sizec = NEXT_MULTIPLE(asic_buff[0].tbl_sizec, ref_buffer_align);
    tmp = asic_buff[0].tbl_sizey + asic_buff[0].tbl_sizec;
#ifdef ASIC_TRACE_SUPPORT
    ret |= DWLMallocRefFrm(dec_cont->dwl, tmp, &asic_buff[0].fake_rfc_tbl);
#else
    ret |= DWLMallocLinear(dec_cont->dwl, tmp, &asic_buff[0].fake_rfc_tbl);
#endif
    if(ret != 0)
      return 1;

    GenerateFakeRFCTable((u8 *)asic_buff[0].fake_rfc_tbl.virtual_address,
                          pic_width_in_cbsy, pic_height_in_cbsy,
                          pic_width_in_cbsc, pic_height_in_cbsc,
                          bit_depth, ref_buffer_align);
  }
#endif
  return 0;
}

/*------------------------------------------------------------------------------
    Function name : ReleaseAsicBuffers
    Description   :

    Return type   : void
    Argument      : DecAsicBuffers_t * asic_buff
------------------------------------------------------------------------------*/
void ReleaseAsicBuffers(const void *dwl, DecAsicBuffers_t * asic_buff) {
  i32 i;

  if(asic_buff[0].mb_ctrl.virtual_address != NULL) {
    DWLFreeLinear(dwl, &asic_buff[0].mb_ctrl);
    asic_buff[0].mb_ctrl.virtual_address = NULL;
  }
  if(asic_buff[0].residual.virtual_address != NULL) {
    DWLFreeLinear(dwl, &asic_buff[0].residual);
    asic_buff[0].residual.virtual_address = NULL;
  }

  if(asic_buff[0].mv.virtual_address != NULL) {
    DWLFreeLinear(dwl, &asic_buff[0].mv);
    asic_buff[0].mv.virtual_address = NULL;
  }

  if(asic_buff[0].intra_pred.virtual_address != NULL) {
    DWLFreeLinear(dwl, &asic_buff[0].intra_pred);
    asic_buff[0].intra_pred.virtual_address = NULL;
  }

  for(i = 0; i < MAX_ASIC_CORES; i++) {
    if(asic_buff[0].cabac_init[i].virtual_address != NULL) {
      DWLFreeLinear(dwl, asic_buff[0].cabac_init + i);
      asic_buff[0].cabac_init[i].virtual_address = NULL;
    }
  }

#ifdef USE_FAKE_RFC_TABLE
  if (asic_buff[0].fake_rfc_tbl.virtual_address != NULL) {
#ifdef ASIC_TRACE_SUPPORT
    DWLFreeRefFrm(dwl, &asic_buff[0].fake_rfc_tbl);
#else
    DWLFreeLinear(dwl, &asic_buff[0].fake_rfc_tbl);
#endif
    asic_buff[0].fake_rfc_tbl.virtual_address = NULL;
  }
#endif
}

/*------------------------------------------------------------------------------
    Function name : H264RunAsic
    Description   :

    Return type   : hw status
    Argument      : DecAsicBuffers_t * p_asic_buff
------------------------------------------------------------------------------*/
u32 H264RunAsic(struct H264DecContainer * dec_cont, DecAsicBuffers_t * p_asic_buff) {
  const seqParamSet_t *p_sps = dec_cont->storage.active_sps;
  const sliceHeader_t *p_slice_header = dec_cont->storage.slice_header;
  const picParamSet_t *p_pps = dec_cont->storage.active_pps;
  const storage_t *storage = &dec_cont->storage;
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  u32 chroma_base_offset = 0;
  u32 pixel_width = (p_sps->bit_depth_luma == 8 &&
                     p_sps->bit_depth_chroma == 8) ? 8 : 10;
  u32 dec_ystride, dec_cstride;
  u32 line_of_width = 0;
  u32 asic_status = 0;
  u32 b_slice_detected = 0;
  i32 ret = 0;
  const struct DecHwFeatures *hw_feature = NULL;
  struct DWLReqInfo info = {0};

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);

  if (dec_cont->rlc_mode) {
    dec_cont->high10p_mode = dec_cont->storage.high10p_mode = 0;
    dec_cont->use_video_compressor = 0;
    dec_cont->storage.use_video_compressor = 0;
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE, DEC_MODE_H264);
    SetDecRegister(dec_cont->h264_regs, HWIF_IDR_PIC_ID,
                   dec_cont->storage.slice_header->idr_pic_id);
  } else if (dec_cont->baseline_mode == 1) {
    dec_cont->high10p_mode = dec_cont->storage.high10p_mode = 0;
    dec_cont->use_video_compressor = 0;
    dec_cont->storage.use_video_compressor = 0;
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE, DEC_MODE_H264);
    SetDecRegister(dec_cont->h264_regs, HWIF_IDR_PIC_ID,
                   dec_cont->storage.slice_header->idr_pic_id);
  }
  SetDecRegister(dec_cont->h264_regs, HWIF_YCBCR422_E, p_sps->chroma_format_idc==2);

  /* Set the buffer bus address for using ddr_low_latency model */
  if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
    SET_ADDR_REG(dec_cont->h264_regs, HWIF_LG_STREAM_STATUS_BASE,
                 dec_cont->llstrminfo.strm_status.bus_address);
  }

  if(!dec_cont->asic_running) {
    u32 reserve_ret = 0;
    u32 i = 0, j = 0, k = 0;

    /* Stride registers only available since g1v8_2 */
    if(!dec_cont->high10p_mode) {
      if (dec_cont->use_video_compressor) {
        if (hw_feature->rfc_support) {
          line_of_width = 8;
          dec_ystride = NEXT_MULTIPLE(8 * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
          dec_cstride = NEXT_MULTIPLE(4 * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_Y_STRIDE, dec_ystride * 8 >> 6);
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_C_STRIDE, dec_cstride * 8 >> 6);
        } else {
          /* No stride for decoder ref output when compression is used. */
          line_of_width = 4;
          dec_ystride = 4 * p_sps->pic_width_in_mbs * 16 * pixel_width / 8;
          dec_cstride = dec_ystride;
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_Y_STRIDE, dec_ystride);
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_C_STRIDE, dec_cstride);
        }
      } else {
        /* No RFC. */
        line_of_width = 4;
        dec_ystride = NEXT_MULTIPLE(4 * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
        dec_cstride = dec_ystride;
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_Y_STRIDE, dec_ystride);
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_C_STRIDE, dec_cstride);
      }
    } else{
    if (dec_cont->use_video_compressor) {
      if (hw_feature->rfc_support) {
        line_of_width = 8;
        dec_ystride = NEXT_MULTIPLE(8 * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
        dec_cstride = NEXT_MULTIPLE(4 * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
      } else {
        /* No stride for decoder ref output when compression is used. */
        line_of_width = 4;
        dec_ystride = 4 * p_sps->pic_width_in_mbs * 16 * pixel_width / 8;
        dec_cstride = dec_ystride;
      }
    } else {
      /* No RFC. */
      line_of_width = TILE_HEIGHT;
      dec_ystride = NEXT_MULTIPLE(TILE_HEIGHT * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
      dec_cstride = NEXT_MULTIPLE(4 * p_sps->pic_width_in_mbs * 16 * pixel_width, ALIGN(dec_cont->align) * 8) / 8;
    }
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_Y_STRIDE, dec_ystride >> 3);  //in unit of 8 bytes
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_C_STRIDE, dec_cstride >> 3); //in unit of 8 bytes
    }
    /* In high10 profile mode, there are saperated chroma base regsiters (high10 profile mode only).*/
    if (dec_cont->high10p_mode)
      chroma_base_offset = NEXT_MULTIPLE(dec_ystride * p_sps->pic_height_in_mbs * 16 / line_of_width,
                                         MAX(16, ALIGN(dec_cont->align)));

    u8 replace_flags = 0; /* ERROR REF need replace ? */
    u8 fake_table_flags = 0;
    i32 replace_index = EC_INVALID_IDX;
    addr_t ref_pic_list = 0;
    addr_t ref_dmv_list = 0;

    (void)fake_table_flags;
    for (i = 0; i < MAX_DPB_SIZE; i++) {
      if (i < dpb->dpb_size) {
        ref_pic_list = p_asic_buff->ref_pic_list[i];
        ref_dmv_list = p_asic_buff->ref_dmv_list[i];
        replace_flags = 0;
        fake_table_flags = 0;
        replace_index = EC_INVALID_IDX;

        /* check ref pic valid flag. */
        if (dec_cont->high10p_mode && dec_cont->valid_flags) {
          if (!IsRefValid(dec_cont->valid_flags, i)) {
            ref_pic_list = p_asic_buff->default_ref_address;
            ref_dmv_list = p_asic_buff->default_dmv_address;
          }
        }

        /* slice mode: reference_frame == current_frame */
        if (!dec_cont->disable_slice_mode &&
            !IS_IDR_NAL_UNIT(storage->prev_nal_unit) &&
            p_asic_buff->ref_pic_list[i] == p_asic_buff->out_buffer->bus_address) {
          ref_pic_list = p_asic_buff->default_ref_address;
          ref_dmv_list = p_asic_buff->default_dmv_address;
          fake_table_flags = 1;
        }

        /* EC: DEC_EC_REF_REPLACE or DEC_EC_REF_REPLACE_ANYWAY*/
        if (dec_cont->error_policy & DEC_EC_REF_REPLACE ||
            dec_cont->error_policy & DEC_EC_REF_REPLACE_ANYWAY) {
          if (dpb->buffer[i].error_info != DEC_NO_ERROR) {
            for (j = 0; j <= dpb->dpb_size; j++) {
              if (dpb->buffer[i].mem_idx == p_asic_buff->ref_mem_idx[j]) {
                replace_index = H264ReplaceRefPic(dec_cont, i);
                ref_pic_list = (replace_index != EC_INVALID_IDX) ?
                               p_asic_buff->ref_pic_list[replace_index] : ref_pic_list;
                ref_dmv_list = (replace_index != EC_INVALID_IDX) ?
                               p_asic_buff->ref_dmv_list[replace_index] : ref_dmv_list;
                replace_flags = 1;
                break;
              }
            }
          }
        }
        if(ref_pic_list == 0x0) ref_pic_list = p_asic_buff->ref_pic_list[0];
        if(ref_dmv_list == 0x0) ref_dmv_list = p_asic_buff->ref_dmv_list[0];

        /* not find avalible replace ref */
        if (replace_flags == 1 && replace_index == EC_INVALID_IDX) {
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
        for (k = 0; k <= dpb->dpb_size; k++) {
          ref_pic_list = p_asic_buff->ref_pic_list[k];
          ref_dmv_list = p_asic_buff->ref_dmv_list[k];
          if (ref_pic_list == p_asic_buff->out_buffer->bus_address)
            continue;
          if (dpb->buffer[k].error_info == DEC_NO_ERROR) { /* this dpb buffer used for ref ? */
            for (j = 0; j <= dpb->dpb_size; j++) {
              if (dpb->buffer[k].mem_idx == p_asic_buff->ref_mem_idx[j])
                break;
            }
            if (j <= dpb->dpb_size) break;
          }
        }
        if (k > dpb->dpb_size) {
          ref_pic_list = p_asic_buff->ref_pic_list[0];
          ref_dmv_list = p_asic_buff->ref_dmv_list[0];
        }
        fake_table_flags = 1;
      }

      /* setting ref pic y_base registers */
      /* stream decoder may get invalid ref buffer index from errorneus
         stream. Initialize unused base addresses to safe values */
      SET_ADDR_REG2(dec_cont->h264_regs, ref_base[i], ref_base_msb[i], ref_pic_list);

      /* In high10 profile mode, there are saperated chroma base regsiters.
       * high10 profile mode only.*/
      if (dec_cont->high10p_mode) {
        ASSERT((chroma_base_offset & 0xF) == 0);
        ASSERT((dpb->dir_mv_offset & 0xF) == 0);

        /* setting ref pic cbcr_base registers */
        SET_ADDR_REG2(dec_cont->h264_regs, ref_cbase[i], ref_cbase_msb[i],
                      ref_pic_list + chroma_base_offset);
        /* setting dmv registers */
        SET_ADDR_REG2(dec_cont->h264_regs, ref_dbase[i], ref_dbase_msb[i],
                      ref_dmv_list);

#ifdef SUPPORT_GDR
        /* first frame is GDR(maybe not I frame, so need fake table) */
        if (dec_cont->storage.is_gdr_frame && dec_cont->pic_number == 0)
          fake_table_flags = 1;
#endif

        /* setting ref pic table register */
        if (dec_cont->use_video_compressor) {
#ifndef USE_FAKE_RFC_TABLE
          SET_ADDR_REG2(dec_cont->h264_regs, ref_tybase[i], ref_tybase_msb[i],
                        (ref_pic_list & ~0x3) + dpb->cbs_ytbl_offset);
          SET_ADDR_REG2(dec_cont->h264_regs, ref_tcbase[i], ref_tcbase_msb[i],
                        (ref_pic_list & ~0x3) + dpb->cbs_ctbl_offset);
#else
          if (IS_IDR_NAL_UNIT(storage->prev_nal_unit) || fake_table_flags == 1) {
            SET_ADDR_REG2(dec_cont->h264_regs, ref_tybase[i], ref_tybase_msb[i],
                          p_asic_buff->fake_rfc_tbl.bus_address);
            SET_ADDR_REG2(dec_cont->h264_regs, ref_tcbase[i], ref_tcbase_msb[i],
                          p_asic_buff->fake_rfc_tbl.bus_address +
                          p_asic_buff->tbl_sizey);
          } else {
            SET_ADDR_REG2(dec_cont->h264_regs, ref_tybase[i], ref_tybase_msb[i],
                          (ref_pic_list & ~0x3) + dpb->cbs_ytbl_offset);
            SET_ADDR_REG2(dec_cont->h264_regs, ref_tcbase[i], ref_tcbase_msb[i],
                          (ref_pic_list & ~0x3) + dpb->cbs_ctbl_offset);
          }
#endif
        } else {
          SET_ADDR_REG2(dec_cont->h264_regs, ref_tybase[i], ref_tybase_msb[i], 0L);
          SET_ADDR_REG2(dec_cont->h264_regs, ref_tcbase[i], ref_tcbase_msb[i], 0L);
        }
      }
    }

    /* inter-view reference picture */
    if (dec_cont->storage.view && !dec_cont->storage.non_inter_view_ref) {
      addr_t tmp;
      tmp = dec_cont->storage.dpbs[0]->current_out->data->bus_address;
      if (dec_cont->storage.dpbs[0]->current_out->is_field_pic)
        tmp |= 0x2;
      SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_BASE, tmp);
      if (dec_cont->high10p_mode) {
        ASSERT((chroma_base_offset & 0xF) == 0);
        ASSERT((dpb->dir_mv_offset & 0xF) == 0);

        SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_CBASE,
                     tmp + chroma_base_offset);
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_DBASE,
                     dec_cont->storage.dpbs[0]->current_out->dmv_data->bus_address
                    /*(tmp & ~0x3) + dpb->dir_mv_offset*/);
        if (dec_cont->use_video_compressor) {
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_TYBASE,
                       tmp + dec_cont->storage.dpbs[0]->cbs_ytbl_offset);
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_TCBASE,
                       tmp + dec_cont->storage.dpbs[0]->cbs_ctbl_offset);
        } else {
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_TYBASE, 0L);
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTER_VIEW_TCBASE, 0L);
        }
      }
      SetDecRegister(dec_cont->h264_regs, HWIF_REFER_VALID_E,
                     GetDecRegister(dec_cont->h264_regs, HWIF_REFER_VALID_E) |
                     (p_slice_header->field_pic_flag ? 0x3 : 0x10000) );
      /* mark interview pic as long term, just to "cheat" mvd to never
       * set colZeroFlag */
      SetDecRegister(dec_cont->h264_regs, HWIF_REFER_LTERM_E,
                     GetDecRegister(dec_cont->h264_regs, HWIF_REFER_LTERM_E) |
                     (p_slice_header->field_pic_flag ? 0x3 : 0x10000) );
    }
    SetDecRegister(dec_cont->h264_regs, HWIF_MVC_E,
                   dec_cont->storage.view != 0);

    SetDecRegister(dec_cont->h264_regs, HWIF_FILTERING_DIS,
                   p_asic_buff->filter_disable);
#if 1
    SetDecRegister(dec_cont->h264_regs, HWIF_QP_OUT_E,
                   dec_cont->qp_output_enable);

    if (!dec_cont->pp_enabled) {
      SET_ADDR_REG(dec_cont->h264_regs, HWIF_QP_OUT,
                     p_asic_buff->out_buffer->bus_address + dpb->out_qp_offset);
    } else {
      SET_ADDR_REG(dec_cont->h264_regs, HWIF_QP_OUT,
                     p_asic_buff->out_pp_buffer->bus_address + dec_cont->auxinfo_offset);
    }
#endif
#if 0
    fprintf(stderr, "\n\tCurrently decoding; %s 0x%08x\n",
            p_slice_header->field_pic_flag ?
            (p_slice_header->bottom_field_flag ? "FIELD BOTTOM" : "FIELD TOP") :
            "FRAME", p_asic_buff->out_buffer->bus_address);
#endif

    if(p_slice_header->field_pic_flag && p_slice_header->bottom_field_flag) {

      if(dec_cont->dpb_mode == DEC_DPB_FRAME) {
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_BASE,
                     p_asic_buff->out_buffer->bus_address +
                     p_sps->pic_width_in_mbs * 16);
      } else {
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_BASE,
                     p_asic_buff->out_buffer->bus_address);
      }
    } else {
      SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_BASE,
                   p_asic_buff->out_buffer->bus_address);
      if (dec_cont->high10p_mode) {
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_CBASE,
                   p_asic_buff->out_buffer->bus_address + chroma_base_offset);
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_DIR_MV_BASE,
                   p_asic_buff->out_dmv_buffer->bus_address /*+ dpb->dir_mv_offset*/);

        if (dec_cont->use_video_compressor) {
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_TYBASE,
                       p_asic_buff->out_buffer->bus_address +
                        dpb->cbs_ytbl_offset);
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_TCBASE,
                       p_asic_buff->out_buffer->bus_address +
                         dpb->cbs_ctbl_offset);
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_EC_BYPASS, 0);
          /* If the size of CBS row >= 64KB, which means it's possible that the
             offset may overflow in EC table, set the EC output in word alignment. */
          if (RFC_MAY_OVERFLOW(p_sps->pic_width_in_mbs * 16, pixel_width))
            SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_EC_BYTE_WORD, 1);
          else
            SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_EC_BYTE_WORD, 0);
        } else {
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_TYBASE, 0L);
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_OUT_TCBASE, 0L);
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_EC_BYPASS, 1);
        }
      }
    }
    SetDecRegister( dec_cont->h264_regs, HWIF_DPB_ILACE_MODE,
                    dec_cont->dpb_mode );

    SetDecRegister(dec_cont->h264_regs, HWIF_CH_QP_OFFSET,
                   p_asic_buff->chroma_qp_index_offset);
    SetDecRegister(dec_cont->h264_regs, HWIF_CH_QP_OFFSET2,
                   p_asic_buff->chroma_qp_index_offset2);

    if(dec_cont->rlc_mode) {

      SetDecRegister(dec_cont->h264_regs, HWIF_RLC_MODE_E, 1);

      SET_ADDR_REG(dec_cont->h264_regs, HWIF_MB_CTRL_BASE,
                   p_asic_buff->mb_ctrl.bus_address);

      SET_ADDR_REG(dec_cont->h264_regs, HWIF_RLC_VLC_BASE,
                   p_asic_buff->residual.bus_address);

      SetDecRegister(dec_cont->h264_regs, HWIF_REF_FRAMES,
                     p_sps->num_ref_frames);

      SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTRA_4X4_BASE,
                   p_asic_buff->intra_pred.bus_address);

      SET_ADDR_REG(dec_cont->h264_regs, HWIF_DIFF_MV_BASE,
                   p_asic_buff->mv.bus_address);

      SetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN, 0);
      SetDecRegister(dec_cont->h264_regs, HWIF_STRM_START_BIT, 0);
      if (hw_feature->h264_adv_support) {
        SetDecRegister(dec_cont->h264_regs, HWIF_BIT_DEPTH_Y_MINUS8,
                       p_sps->bit_depth_luma - 8);
        SetDecRegister(dec_cont->h264_regs, HWIF_BIT_DEPTH_C_MINUS8,
                       p_sps->bit_depth_chroma - 8);
      }
#ifdef SUPPORT_DMA
      DWLDMATransData((addr_t)dec_cont->asic_buff->mb_ctrl.bus_address,
                      (void *)dec_cont->asic_buff->mb_ctrl.virtual_address,
                      dec_cont->asic_buff->mb_ctrl.size, HOST_TO_DEVICE);
      DWLDMATransData((addr_t)dec_cont->asic_buff->mv.bus_address,
                      (void *)dec_cont->asic_buff->mv.virtual_address,
                      dec_cont->asic_buff->mv.size, HOST_TO_DEVICE);
      DWLDMATransData((addr_t)dec_cont->asic_buff->intra_pred.bus_address,
                      (void *)dec_cont->asic_buff->intra_pred.virtual_address,
                      dec_cont->asic_buff->intra_pred.size, HOST_TO_DEVICE);
      DWLDMATransData((addr_t)dec_cont->asic_buff->residual.bus_address,
                      (void *)dec_cont->asic_buff->residual.virtual_address,
                      dec_cont->asic_buff->residual.size, HOST_TO_DEVICE);
#endif
    } else {
      if(dec_cont->h264_profile_support == H264_BASELINE_PROFILE) {
        goto skipped_high_profile;  /* leave high profile stuff disabled */
      }

      /* direct mv writing not enabled if HW config says that
       * SW_DEC_H264_PROF="10" */
      if(p_asic_buff->enable_dmv_and_poc && dec_cont->h264_profile_support != H264_BASELINE_PROFILE) {
        u32 dir_mv_offset = 0;

        if (dec_cont->storage.mvc && dec_cont->storage.view == 0)
          SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E,
                         dec_cont->storage.non_inter_view_ref == 0 ||
                         dec_cont->storage.prev_nal_unit->nal_ref_idc != 0);
        else
          SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E,
                         dec_cont->storage.prev_nal_unit->nal_ref_idc != 0);

        if(p_slice_header->bottom_field_flag)
          dir_mv_offset += dpb->pic_size_in_mbs * 32;

        if(!dec_cont->high10p_mode)
          SET_ADDR_REG(dec_cont->h264_regs, HWIF_DIR_MV_BASE,
                       p_asic_buff->out_dmv_buffer->bus_address + dir_mv_offset);
      } else
        SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E, 0);

      if (dec_cont->skip_non_intra && dec_cont->pp_enabled)
        SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E, 0);

      /* make sure that output pic sync memory is cleared */
      if (dec_cont->b_mc) {
#ifndef MEM_ONLY_DEV_CHECK
        char *sync_base;
        if (dec_cont->high10p_mode)
          sync_base = (char *) (p_asic_buff->out_dmv_buffer->virtual_address) - 32;
        else
          sync_base = (char *) (p_asic_buff->out_dmv_buffer->virtual_address) + storage->dmv_mem_size;
        u32 sync_size = 16; /* 16 bytes for each field */
        if (!p_slice_header->field_pic_flag) {
          sync_size += 16; /* reset all 32 bytes */
        } else if (p_slice_header->bottom_field_flag) {
          sync_base += 16; /* bottom field sync area*/
        }

        (void) DWLmemset(sync_base, 0, sync_size);
#endif
#ifdef SUPPORT_DMA
        if (dec_cont->high10p_mode)
          DWLDMATransData((addr_t)((u8*)p_asic_buff->out_dmv_buffer->bus_address - 32),
                          (void *)((u8*)p_asic_buff->out_dmv_buffer->virtual_address - 32),
                          32, HOST_TO_DEVICE);
        else
          DWLDMATransData((addr_t)((u8*)p_asic_buff->out_dmv_buffer->bus_address + storage->dmv_mem_size),
                          (void *)((u8*)p_asic_buff->out_dmv_buffer->virtual_address + storage->dmv_mem_size),
                          32, HOST_TO_DEVICE);
#endif
      }

      SetDecRegister(dec_cont->h264_regs, HWIF_DIR_8X8_INFER_E,
                     p_sps->direct8x8_inference_flag);
      SetDecRegister(dec_cont->h264_regs, HWIF_WEIGHT_PRED_E,
                     p_pps->weighted_pred_flag);
      SetDecRegister(dec_cont->h264_regs, HWIF_WEIGHT_BIPR_IDC,
                     p_pps->weighted_bi_pred_idc);
      SetDecRegister(dec_cont->h264_regs, HWIF_REFIDX1_ACTIVE,
                     p_pps->num_ref_idx_l1_active);
      SetDecRegister(dec_cont->h264_regs, HWIF_FIELDPIC_FLAG_E,
                     !p_sps->frame_mbs_only_flag);
      SetDecRegister(dec_cont->h264_regs, HWIF_PIC_INTERLACE_E,
                     !p_sps->frame_mbs_only_flag &&
                     (p_sps->mb_adaptive_frame_field_flag || p_slice_header->field_pic_flag));

      SetDecRegister(dec_cont->h264_regs, HWIF_PIC_FIELDMODE_E,
                     p_slice_header->field_pic_flag);

#ifdef ASIC_TRACE_SUPPORT
      /* When trace is enabled, CModel need to clear PP output buffer at the
         first field for top verification. We make use of HWIF_TOPFIELDFIRST_E,
         which is in fact not used in H264 HW decoding. */
      if (p_slice_header->field_pic_flag) {
        if (dec_cont->storage.dpbs[0]->current_out->status[0] == EMPTY)
          SetDecRegister(dec_cont->h264_regs, HWIF_TOPFIELDFIRST_E, 0);
        else if (dec_cont->storage.dpbs[0]->current_out->status[1] == EMPTY)
          SetDecRegister(dec_cont->h264_regs, HWIF_TOPFIELDFIRST_E, 1);
      } else {
        SetDecRegister(dec_cont->h264_regs, HWIF_TOPFIELDFIRST_E, 0);
      }
#endif

      APITRACEDEBUG("framembs %d, mbaff %d, fieldpic %d\n",
                   p_sps->frame_mbs_only_flag,
                   p_sps->mb_adaptive_frame_field_flag, p_slice_header->field_pic_flag);

      SetDecRegister(dec_cont->h264_regs, HWIF_PIC_TOPFIELD_E,
                     !p_slice_header->bottom_field_flag);

      SetDecRegister(dec_cont->h264_regs, HWIF_SEQ_MBAFF_E,
                     p_sps->mb_adaptive_frame_field_flag);

      SetDecRegister(dec_cont->h264_regs, HWIF_8X8TRANS_FLAG_E,
                     p_pps->transform8x8_flag);

      SetDecRegister(dec_cont->h264_regs, HWIF_BLACKWHITE_E,
                     p_sps->profile_idc >= 100 &&
                     p_sps->chroma_format_idc == 0);
      if (dec_cont->high10p_mode) {
        SetDecRegister(dec_cont->h264_regs, HWIF_BIT_DEPTH_Y_MINUS8,
                       p_sps->bit_depth_luma - 8);
        SetDecRegister(dec_cont->h264_regs, HWIF_BIT_DEPTH_C_MINUS8,
                       p_sps->bit_depth_chroma - 8);
      }
      SetDecRegister(dec_cont->h264_regs, HWIF_TYPE1_QUANT_E,
                     p_pps->scaling_matrix_present_flag || p_sps->scaling_matrix_present_flag);
    }

    /***************************************************************************/
skipped_high_profile:
    if (dec_cont->partial_decoding && dec_cont->pp_enabled) {
      SetDecRegister(dec_cont->h264_regs, HWIF_REF_READ_DIS, 1);
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS, 1);
      SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E, 0);
    } else if (dec_cont->skip_non_intra && dec_cont->pp_enabled) {
      SetDecRegister(dec_cont->h264_regs, HWIF_REF_READ_DIS, 1);
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS, 1);
      SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E, 0);
    } else {
      if (dec_cont->skip_frame == DEC_SKIP_NON_REF_RECON &&
          dec_cont->pp_enabled &&
          GetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE) == DEC_MODE_H264_H10P &&
          (!dec_cont->storage.mvc && /* not used for inter prediction */
            dec_cont->storage.last_nal_unit->nal_ref_idc == 0)) {
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS,  1);
        SetDecRegister(dec_cont->h264_regs, HWIF_WRITE_MVS_E, 0);
      } else {
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS, p_asic_buff->disable_out_writing);
      }
    }

    if (dec_cont->storage.enable2nd_chroma &&
        !dec_cont->storage.active_sps->mono_chrome) {
      SetDecRegister(dec_cont->h264_regs, HWIF_CH_8PIX_ILEAV_E, 1);
      if(p_slice_header->field_pic_flag && p_slice_header->bottom_field_flag) {
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_CH8PIX_BASE,
                     p_asic_buff->out_buffer->bus_address + dpb->ch2_offset+
                     p_sps->pic_width_in_mbs * 16);
      } else {
        SET_ADDR_REG(dec_cont->h264_regs, HWIF_DEC_CH8PIX_BASE,
                     p_asic_buff->out_buffer->bus_address + dpb->ch2_offset);
      }
    } else
      SetDecRegister(dec_cont->h264_regs, HWIF_CH_8PIX_ILEAV_E, 0);

    if (!dec_cont->keep_hw_reserved) {

      info.core_mask = dec_cont->core_mask;
      info.width = p_sps->pic_width_in_mbs * 16;
      info.height = p_sps->pic_height_in_mbs * 16;
      if (dec_cont->vcmd_used) {
        FifoObject obj;
        dec_cont->core_id = 0;
        dec_cont->mc_buf_id = 0;
        if (dec_cont->b_mc) {
          FifoPop(dec_cont->fifo_core, &obj, FIFO_EXCEPTION_DISABLE);
          dec_cont->mc_buf_id = (i32)(addr_t)obj;
        }
        reserve_ret = DWLReserveCmdBuf(dec_cont->dwl, &info, &dec_cont->cmdbuf_id);
      } else
        reserve_ret = DWLReserveHw(dec_cont->dwl, &info, &dec_cont->core_id);

      if(reserve_ret != DWL_OK) {
        /* Decrement usage for DPB buffers */
        DecrementDPBRefCount(&storage->dpb[1]);

        return X170_DEC_HW_RESERVED;
      }

      /* Set dec_status to RUNNING in MC mode */
      if (dec_cont->b_mc && !dec_cont->vcmd_used) {
        dec_cont->dec_status[dec_cont->core_id] = DEC_RUNNING;
      }
    }

    /* core id is to used as index of buffer, generatlly, it is 0 if not multi core decode */
    const u32 core_id = dec_cont->b_mc ? (dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id) : 0;

    SetDecRegister(dec_cont->h264_regs, HWIF_PP_IN_FORMAT_U, 1);
    SetDecRegister(dec_cont->h264_regs, HWIF_UNIQUE_ID,
                   UNIQUE_ID(dec_cont->pic_number));

    if (dec_cont->pp_enabled && hw_feature->max_ppu_count) {
      PpUnitIntConfig *ppu_cfg = &dec_cont->ppu_cfg[0];
      addr_t ppu_out_bus_addr = p_asic_buff->out_pp_buffer->bus_address;
      u32 bottom_flag = p_slice_header->field_pic_flag &&
                        p_slice_header->bottom_field_flag;
      InitPpUnitBoundCoeff(hw_feature, p_slice_header->field_pic_flag, ppu_cfg);
      PPSetRegs(dec_cont->h264_regs, hw_feature, ppu_cfg, ppu_out_bus_addr,
                0, bottom_flag);
      PPSetLancozsScaleRegs(dec_cont->h264_regs, hw_feature, ppu_cfg, core_id);
      PPSetFbcRegs(dec_cont->h264_regs, hw_feature, ppu_cfg, 0);
      DelogoSetRegs(dec_cont->h264_regs, hw_feature, dec_cont->delogo_params);
      if (dec_cont->partial_decoding && (!(IS_IDR_NAL_UNIT(dec_cont->storage.prev_nal_unit)))) {
        SetDecRegister(dec_cont->h264_regs, HWIF_PP_OUT_E_U, 0);
      }
    }

    if (dec_cont->h264_profile_support != H264_BASELINE_PROFILE ||
        dec_cont->hw_conceal) {
      h264PrepareScaleList(dec_cont);

      SET_ADDR_REG(dec_cont->h264_regs, HWIF_QTABLE_BASE, p_asic_buff->cabac_init[core_id].bus_address);
    }

    if (dec_cont->vcmd_used)
      DWLReadPpConfigure(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->ppu_cfg, 0);
    else
      DWLReadPpConfigure(dec_cont->dwl, dec_cont->core_id, dec_cont->ppu_cfg, 0);
#ifndef ASIC_TRACE_SUPPORT
    if(dec_cont->b_mc)
#endif

    DWLReadMcRefBuffer(dec_cont->dwl, dec_cont->core_id,
        p_asic_buff->out_buffer->logical_size - dpb->sync_mc_offset - 32, 16);

    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 1);

    /* when b_mc is 0, the callback callback_arg has been clear up in DWLReserveHw/DWLReserveCmdBuf */
    if(dec_cont->b_mc) {
      h264CopyPocToHw(dec_cont);
      h264MCSetHwRdyCallback(dec_cont);
#ifdef SUPPORT_GDR
      /* MC mode: recovery_frame_cnt-- */
      if (dec_cont->storage.is_gdr_frame && dec_cont->storage.sei_param_curr)
        dec_cont->storage.sei_param_curr->recovery_param.recovery_frame_cnt--;
#endif
    }

#ifdef SUPPORT_DMA
    /* the [scaling list], [poc buffer] and [cabac buffer] are all in cabac_init buffer.
    * [scaling list] : if(dec_cont->h264_profile_support != H264_BASELINE_PROFILE).
    * [poc buffer] : if(dec_cont->h264_profile_support != H264_BASELINE_PROFILE).
    *                if(dec_cont->b_mc).
    * [cabac buffer] : always needs DMA.
    */
    {
      DWLDMATransData((addr_t)dec_cont->asic_buff->cabac_init[core_id].bus_address,
                      (void *)dec_cont->asic_buff->cabac_init[core_id].virtual_address,
                      dec_cont->asic_buff->cabac_init[core_id].size, HOST_TO_DEVICE);
    }
#endif

    H264FlushRegs(dec_cont);

    H264EnableDMVBuffer(dpb, dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id);

    if (dec_cont->vcmd_used)
      DWLEnableCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);
    else
      DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                  dec_cont->h264_regs[1]);

    dec_cont->asic_running = 1;

    if (dec_cont->pp_enabled)
      IncreaseInputQueueCnt(dec_cont->pp_buffer_queue, dec_cont->asic_buff->out_pp_buffer->virtual_address);

    if(dec_cont->b_mc) {
      /* reset shadow HW status reg values so that we dont end up writing
       * some garbage to next core regs */
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 0);
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT, 0);
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ, 0);

      dec_cont->asic_running = 0;
      dec_cont->keep_hw_reserved = 0;
      return DEC_HW_IRQ_RDY;
    }
  } else {
    /* buffer was empty or stream error and now we restart with new stream values */

    ASSERT(!dec_cont->b_mc);

    h264StreamPosUpdate(dec_cont);
    /* For some case that the last slice of an IDR is missing (and followed by a
       a non-IDR slice). */
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 8, dec_cont->h264_regs[8]);

    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 5, dec_cont->h264_regs[5]);
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 6, dec_cont->h264_regs[6]);
    if (IS_LEGACY(dec_cont->h264_regs[0]))
      DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 12, dec_cont->h264_regs[12]);
    else
      DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 169, dec_cont->h264_regs[169]);
    if (sizeof(addr_t) == 8) {
      if (hw_feature->addr64_support) {
        if (IS_LEGACY(dec_cont->h264_regs[0]))
          DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 122, dec_cont->h264_regs[122]);
        else
          DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 168, dec_cont->h264_regs[168]);
      } else {
        //ASSERT(dec_cont->h264_regs[122] == 0);
        //ASSERT(dec_cont->h264_regs[168] == 0);
      }
    } else {
      if (hw_feature->addr64_support) {
        if (IS_LEGACY(dec_cont->h264_regs[0])) {
          dec_cont->h264_regs[122] = 0;
          DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 122, 0);
        }
        else {
          dec_cont->h264_regs[168] = 0;
          DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 168, 0);
        }
      }
    }
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 258, dec_cont->h264_regs[258]);
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * 259, dec_cont->h264_regs[259]);

    H264EnableDMVBuffer(dpb, dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id);

    /* start HW by clearing IRQ_BUFFER_EMPTY status bit */
    if (dec_cont->vcmd_used)
      DWLCmdPushSliceRegs(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->h264_regs);
    else
      DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, dec_cont->h264_regs[1]);
  }

  if (dec_cont->vcmd_used)
    ret = DWLWaitCmdBufReady(dec_cont->dwl, dec_cont->cmdbuf_id);
  else
    ret = DWLWaitHwReady(dec_cont->dwl, dec_cont->core_id, (u32) DEC_X170_TIMEOUT_LENGTH);

  H264DisableDMVBuffer(dpb, dec_cont->vcmd_used? dec_cont->mc_buf_id : dec_cont->core_id);

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
    u32 pic_size = dec_cont->high10p_mode ? dec_cont->storage.dpb->sync_mc_offset :
                                            dec_cont->storage.dpb->dir_mv_offset;
    DWLDMATransData((addr_t)dec_cont->asic_buff->out_buffer->bus_address,
                    (void *)dec_cont->asic_buff->out_buffer->virtual_address,
                    /* dec_cont->asic_buff->out_buffer->size */
                    pic_size, DEVICE_TO_HOST);
  }
#endif
#endif

  if(ret != DWL_HW_WAIT_OK) {
    APITRACEERR("%s\n","DWLWaitHwReady");
    APITRACEERR("DWLWaitHwReady returned: %d\n", ret);

    /* reset HW */
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 0);

    dec_cont->asic_running = 0;
    dec_cont->keep_hw_reserved = 0;
    if (dec_cont->vcmd_used)
      (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);
    else {
      DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, dec_cont->h264_regs[1]);
      (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
    }

    /* Decrement usage for DPB buffers */
    DecrementDPBRefCount(&storage->dpb[1]);
    return (ret == DWL_HW_WAIT_ERROR) ?
           X170_DEC_SYSTEM_ERROR : X170_DEC_TIMEOUT;
  }

  H264RefreshRegs(dec_cont);

  /* React to the HW return value */

  asic_status = GetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT);
  b_slice_detected = GetDecRegister(dec_cont->h264_regs, HWIF_DEC_PIC_INF);

  SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT, 0);
  SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ, 0);    /* just in case */

  /* any B stuff detected by HW? (note reg name changed from
   * b_detected to pic_inf) */
  if(b_slice_detected) {
    ASSERT(dec_cont->h264_profile_support != H264_BASELINE_PROFILE);
    if((dec_cont->h264_profile_support != H264_BASELINE_PROFILE) &&
        (p_asic_buff->enable_dmv_and_poc == 0)) {
      APITRACEDEBUG("%s","HW Detected B slice in baseline profile stream!!!\n");
      p_asic_buff->enable_dmv_and_poc = 1;
    }
    /* update results for current output */
    {
      dpbStorage_t *dpb = &storage->dpb[0];
      i32 i = dpb->num_out;
      u32 tmp = dpb->out_index_r;

      while((i--) > 0) {
        if (tmp == dpb->dpb_size + 1)
          tmp = 0;
        if(dpb->out_buf[tmp].data == storage->curr_image->data) {
          dpb->out_buf[tmp].pic_code_type[0] = DEC_PIC_TYPE_B;
          dpb->out_buf[tmp].pic_code_type[1] = DEC_PIC_TYPE_B;
          break;
        }
        tmp++;
      }

      i = dpb->dpb_size + 1;
      while((i--) > 0) {
        if(dpb->buffer[i].data == storage->curr_image->data) {
          dpb->buffer[i].pic_code_type[0] = DEC_PIC_TYPE_B;
          dpb->buffer[i].pic_code_type[1] = DEC_PIC_TYPE_B;
          ASSERT(&dpb->buffer[i] == dpb->current_out);
          break;
        }
      }
    }
    /* reset the reg */
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_PIC_INF, 0);
  }

  if(!(asic_status & DEC_HW_IRQ_BUFFER)){
    /* HW done, release it! */
    dec_cont->asic_running = 0;

    /* Do synchronization after HW ready in low latency mode */
    while(dec_cont->low_latency && (!dec_cont->llstrminfo.updated_reg)){
      sched_yield();
    }
    if(dec_cont->low_latency)
      dec_cont->llstrminfo.updated_reg = 0;

    dec_cont->keep_hw_reserved = 0;

    if (dec_cont->pp_enabled)
      DecreaseInputQueueCnt(dec_cont->pp_buffer_queue, dec_cont->asic_buff->out_pp_buffer->virtual_address);

    if (!dec_cont->keep_hw_reserved) {
      if (dec_cont->vcmd_used)
        (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);
      else
        (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
    }

    /* Decrement usage for DPB buffers */
    DecrementDPBRefCount(&storage->dpb[1]);

#ifdef SUPPORT_GDR
    /* SC mode: recovery_frame_cnt-- */
    if (dec_cont->storage.is_gdr_frame && dec_cont->storage.sei_param_curr)
      dec_cont->storage.sei_param_curr->recovery_param.recovery_frame_cnt--;
#endif
  }
  /* update reference buffer stat */
  if(dec_cont->asic_running == 0 &&
      (asic_status & DEC_HW_IRQ_RDY)) {
    u32 *p_mv = p_asic_buff->out_dmv_buffer->virtual_address;
    u32 tmp = 0;

    if(p_slice_header->field_pic_flag && p_slice_header->bottom_field_flag) {
      tmp += dpb->pic_size_in_mbs * 32;
    }
    p_mv = (u32 *) ((u8*)p_mv + tmp);

  }

  if(!dec_cont->rlc_mode) {
    if (!dec_cont->secure_mode) {
      addr_t last_read_address;
      u32 bytes_processed;
      addr_t start_address, offset_bytes;

      if (!dec_cont->high10p_mode) {
        start_address = dec_cont->hw_stream_start_bus & (~DEC_X170_ALIGN_MASK);
        offset_bytes = dec_cont->hw_stream_start_bus & DEC_X170_ALIGN_MASK;
      } else {
        start_address = dec_cont->hw_stream_start_bus & (~DEC_HW_ALIGN_MASK);
        offset_bytes = dec_cont->hw_stream_start_bus & DEC_HW_ALIGN_MASK;
      }

      last_read_address =
        GET_ADDR_REG(dec_cont->h264_regs, HWIF_RLC_VLC_BASE);

      bytes_processed = last_read_address - start_address;

      if ((asic_status & DEC_HW_IRQ_RDY) &&
          last_read_address == dec_cont->hw_stream_start_bus) {
        last_read_address = start_address + dec_cont->buff_length;
      }

      if(last_read_address <= start_address)
        bytes_processed = dec_cont->buff_length - (u32)(start_address - last_read_address);
      else
        bytes_processed = (u32)(last_read_address - start_address);


      APITRACEDEBUG("HW updated stream position: %16x\n"
                   "           processed bytes: %8d\n"
                   "     of which offset bytes: %8d\n",
                   last_read_address, bytes_processed, offset_bytes);

      if(asic_status & DEC_HW_IRQ_BUFFER) {
        dec_cont->p_hw_stream_start += dec_cont->hw_length;
        dec_cont->hw_stream_start_bus += dec_cont->hw_length;
        dec_cont->hw_length = 0; /* no bytes left */
      } else if (!(asic_status & DEC_HW_IRQ_ASO)) {
        /* from start of the buffer add what HW has decoded */

        /* end - start smaller or equal than maximum */
        if(dec_cont->low_latency)
          dec_cont->hw_length = dec_cont->llstrminfo.tmp_length;

        if((bytes_processed - offset_bytes) > dec_cont->hw_length) {

          if(!(asic_status & ( DEC_HW_IRQ_ABORT |
                               DEC_HW_IRQ_ERROR |
                               DEC_HW_IRQ_TIMEOUT |
                               DEC_HW_IRQ_BUS ))) {
            APITRACEDEBUG("%s","New stream position out of range!\n");
            APITRACEDEBUG("Buffer size %d, and next start would be %d\n",
                         dec_cont->hw_length,
                         (bytes_processed - offset_bytes));
            //ASSERT(0);
          }

          /* consider all buffer processed */
          dec_cont->p_hw_stream_start += dec_cont->hw_length;
          dec_cont->hw_stream_start_bus += dec_cont->hw_length;
          dec_cont->hw_length = 0; /* no bytes left */
        } else {
          dec_cont->hw_length -= (bytes_processed - offset_bytes);
          dec_cont->p_hw_stream_start += (bytes_processed - offset_bytes);
          dec_cont->hw_stream_start_bus += (bytes_processed - offset_bytes);

          if ((asic_status & DEC_HW_IRQ_ERROR)) {
            if (dec_cont->error_frame_au) {
              u32 bytes = dec_cont->first_mb_offset / 8;
              u32 bit = dec_cont->first_mb_offset % 8;
              dec_cont->original_word = *(dec_cont->p_hw_stream_start + bytes);
              u8 *tmp_strm = dec_cont->p_hw_stream_start;
              u8 a = *(tmp_strm + bytes) | (0x01 << (7 - bit));
              *(tmp_strm + bytes) = a;
              dec_cont->p_hw_stream_start = tmp_strm;
            }
          }
        }
        /* if turnaround */
        if(dec_cont->p_hw_stream_start > (dec_cont->hw_buffer + dec_cont->buff_length)) {
          dec_cont->p_hw_stream_start -= dec_cont->buff_length;
          dec_cont->hw_stream_start_bus -= dec_cont->buff_length;
        }
      }
      /* else will continue decoding from the beginning of buffer */
    } else {
      dec_cont->p_hw_stream_start += dec_cont->hw_length;
      dec_cont->hw_stream_start_bus += dec_cont->hw_length;
      dec_cont->hw_length = 0; /* no bytes left */
    }

    dec_cont->stream_pos_updated = 1;
  }

  return asic_status;
}

/*------------------------------------------------------------------------------
    Function name : PrepareMvData
    Description   :

    Return type   : void
    Argument      : storage_t * storage
    Argument      : DecAsicBuffers_t * p_asic_buff
------------------------------------------------------------------------------*/
void PrepareMvData(storage_t * storage, DecAsicBuffers_t * p_asic_buff) {
  const mbStorage_t *p_mb = storage->mb;

  u32 mbs = storage->pic_size_in_mbs;
  u32 tmp, n;
  u32 *p_mv_ctrl, *p_mv_ctrl_base = p_asic_buff->mv.virtual_address;
  const u32 *p_mb_ctrl = p_asic_buff->mb_ctrl.virtual_address;

  if(p_asic_buff->whole_pic_concealed != 0) {
    if(p_mb->mb_type_asic == P_Skip) {
      tmp = (u32)p_mb->ref_id[0];

      p_mv_ctrl = p_mv_ctrl_base;

      for(n = mbs; n > 0; n--) {
        *p_mv_ctrl = tmp;
        p_mv_ctrl += (ASIC_MB_MV_BUFFER_SIZE / 4);
      }
    }

    return;
  }

  for(n = mbs; n > 0; n--, p_mb++, p_mv_ctrl_base += (ASIC_MB_MV_BUFFER_SIZE / 4),
      p_mb_ctrl += (ASIC_MB_CTRL_BUFFER_SIZE / 4)) {
    const mv_t *mv = p_mb->mv;

    p_mv_ctrl = p_mv_ctrl_base;

    switch (p_mb->mb_type_asic) {
    case P_Skip:
      tmp = (u32)p_mb->ref_id[0];
      *p_mv_ctrl++ = tmp;
      break;

    case P_L0_16x16:
      tmp = ((u32) (mv[0].hor & ASIC_HOR_MV_MASK)) << ASIC_HOR_MV_OFFSET;
      tmp |= ((u32) (mv[0].ver & ASIC_VER_MV_MASK)) << ASIC_VER_MV_OFFSET;
      tmp |= (u32)p_mb->ref_id[0];
      *p_mv_ctrl++ = tmp;

      break;
    case P_L0_L0_16x8:
      tmp = ((u32) (mv[0].hor & ASIC_HOR_MV_MASK)) << ASIC_HOR_MV_OFFSET;
      tmp |= ((u32) (mv[0].ver & ASIC_VER_MV_MASK)) << ASIC_VER_MV_OFFSET;
      tmp |= (u32)p_mb->ref_id[0];

      *p_mv_ctrl++ = tmp;

      tmp = ((u32) (mv[8].hor & ASIC_HOR_MV_MASK)) << ASIC_HOR_MV_OFFSET;
      tmp |= ((u32) (mv[8].ver & ASIC_VER_MV_MASK)) << ASIC_VER_MV_OFFSET;
      tmp |= (u32)p_mb->ref_id[1];

      *p_mv_ctrl++ = tmp;

      break;
    case P_L0_L0_8x16:
      tmp = ((u32) (mv[0].hor & ASIC_HOR_MV_MASK)) << ASIC_HOR_MV_OFFSET;
      tmp |= ((u32) (mv[0].ver & ASIC_VER_MV_MASK)) << ASIC_VER_MV_OFFSET;
      tmp |= (u32)p_mb->ref_id[0];

      *p_mv_ctrl++ = tmp;

      tmp = ((u32) (mv[4].hor & ASIC_HOR_MV_MASK)) << ASIC_HOR_MV_OFFSET;
      tmp |= ((u32) (mv[4].ver & ASIC_VER_MV_MASK)) << ASIC_VER_MV_OFFSET;
      tmp |= (u32)p_mb->ref_id[1];

      *p_mv_ctrl++ = tmp;

      break;
    case P_8x8:
    case P_8x8ref0: {
      u32 i;
      u32 sub_mb_type = *p_mb_ctrl;

      for(i = 0; i < 4; i++) {
        switch ((sub_mb_type >> (u32) (27 - 2 * i)) & 0x03) {
        case MB_SP_8x8:
          tmp =
            ((u32) ((*mv).hor & ASIC_HOR_MV_MASK)) <<
            ASIC_HOR_MV_OFFSET;
          tmp |=
            ((u32) ((*mv).ver & ASIC_VER_MV_MASK)) <<
            ASIC_VER_MV_OFFSET;
          tmp |= (u32)p_mb->ref_id[i];
          *p_mv_ctrl++ = tmp;
          mv += 4;
          break;

        case MB_SP_8x4:
          tmp =
            ((u32) ((*mv).hor & ASIC_HOR_MV_MASK)) <<
            ASIC_HOR_MV_OFFSET;
          tmp |=
            ((u32) ((*mv).ver & ASIC_VER_MV_MASK)) <<
            ASIC_VER_MV_OFFSET;
          tmp |= (u32)p_mb->ref_id[i];
          *p_mv_ctrl++ = tmp;
          mv += 2;

          tmp =
            ((u32) ((*mv).hor & ASIC_HOR_MV_MASK)) <<
            ASIC_HOR_MV_OFFSET;
          tmp |=
            ((u32) ((*mv).ver & ASIC_VER_MV_MASK)) <<
            ASIC_VER_MV_OFFSET;
          tmp |= (u32)p_mb->ref_id[i];
          *p_mv_ctrl++ = tmp;
          mv += 2;
          break;

        case MB_SP_4x8:
          tmp =
            ((u32) ((*mv).hor & ASIC_HOR_MV_MASK)) <<
            ASIC_HOR_MV_OFFSET;
          tmp |=
            ((u32) ((*mv).ver & ASIC_VER_MV_MASK)) <<
            ASIC_VER_MV_OFFSET;
          tmp |= (u32)p_mb->ref_id[i];
          *p_mv_ctrl++ = tmp;
          mv++;
          tmp =
            ((u32) ((*mv).hor & ASIC_HOR_MV_MASK)) <<
            ASIC_HOR_MV_OFFSET;
          tmp |=
            ((u32) ((*mv).ver & ASIC_VER_MV_MASK)) <<
            ASIC_VER_MV_OFFSET;
          tmp |= (u32)p_mb->ref_id[i];
          *p_mv_ctrl++ = tmp;
          mv += 3;

          break;

        case MB_SP_4x4: {
          u32 j;

          for(j = 4; j > 0; j--) {
            tmp =
              ((u32) ((*mv).hor & ASIC_HOR_MV_MASK)) <<
              ASIC_HOR_MV_OFFSET;
            tmp |=
              ((u32) ((*mv).ver & ASIC_VER_MV_MASK)) <<
              ASIC_VER_MV_OFFSET;
            tmp |= (u32)p_mb->ref_id[i];
            *p_mv_ctrl++ = tmp;
            mv++;
          }
        }
        break;
        default:
          ASSERT(0);
        }
      }
    }
    break;
    default:
      break;
    }
  }
}

/*------------------------------------------------------------------------------
    Function name : PrepareIntra4x4ModeData
    Description   :

    Return type   : void
    Argument      : storage_t * storage
    Argument      : DecAsicBuffers_t * p_asic_buff
------------------------------------------------------------------------------*/
void PrepareIntra4x4ModeData(storage_t * storage, DecAsicBuffers_t * p_asic_buff) {
  u32 n;
  u32 mbs = storage->pic_size_in_mbs;
  u32 *p_intra_pred, *p_intra_pred_base = p_asic_buff->intra_pred.virtual_address;
  const mbStorage_t *p_mb = storage->mb;

  if(p_asic_buff->whole_pic_concealed != 0) {
    return;
  }

  /* write out "INTRA4x4 mode" to ASIC */
  for(n = mbs; n > 0;
      n--, p_mb++, p_intra_pred_base += (ASIC_MB_I4X4_BUFFER_SIZE / 4)) {
    u32 tmp = 0, block;

    p_intra_pred = p_intra_pred_base;

    if(h264bsdMbPartPredMode(p_mb->mb_type_asic) != PRED_MODE_INTRA4x4)
      continue;

    for(block = 0; block < 16; block++) {
      u8 mode = p_mb->intra4x4_pred_mode_asic[block];

      tmp <<= 4;
      tmp |= (u32)mode;

      if(block == 7) {
        *p_intra_pred++ = tmp;
        tmp = 0;
      }
    }
    *p_intra_pred++ = tmp;
  }
}

/*------------------------------------------------------------------------------
    Function name   : PrepareRlcCount
    Description     :
    Return type     : void
    Argument        : storage_t * storage
    Argument        : DecAsicBuffers_t * p_asic_buff
------------------------------------------------------------------------------*/
void PrepareRlcCount(storage_t * storage, DecAsicBuffers_t * p_asic_buff) {
  u32 n;
  u32 mbs = storage->pic_size_in_mbs;
  u32 *p_mb_ctrl = p_asic_buff->mb_ctrl.virtual_address + 1;

  if(p_asic_buff->whole_pic_concealed != 0) {
    return;
  }

  for(n = mbs - 1; n > 0; n--, p_mb_ctrl += (ASIC_MB_CTRL_BUFFER_SIZE / 4)) {
    u32 tmp = (*(p_mb_ctrl + (ASIC_MB_CTRL_BUFFER_SIZE / 4))) << 4;

    (*p_mb_ctrl) |= (tmp >> 23);
  }
}

/*------------------------------------------------------------------------------
    Function name   : H264RefreshRegs
    Description     :
    Return type     : void
    Argument        : struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
static void H264RefreshRegs(struct H264DecContainer * dec_cont) {
  i32 i;
  u32 *dec_regs = dec_cont->h264_regs;

  if(dec_cont->vcmd_used) {
    DWLRefreshRegister(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->h264_regs);
  }
  else {
    for (i = 1; i < DEC_X170_REGISTERS; i++) {
      dec_regs[i] = DWLReadReg(dec_cont->dwl, dec_cont->core_id, 4 * i);
    }
  }

#if 0
  printf("Cycles/MB in current frame is %d\n",
      dec_cont->h264_regs[63]/(dec_cont->storage.active_sps->pic_height_in_mbs *
      dec_cont->storage.active_sps->pic_width_in_mbs));
#endif

}

/*------------------------------------------------------------------------------
    Function name   : H264FlushRegs
    Description     :
    Return type     : void
    Argument        : struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
static void H264FlushRegs(struct H264DecContainer * dec_cont) {
  i32 i;
  const u32 *dec_regs = dec_cont->h264_regs;    /* Don't write ID reg */

#ifdef TRACE_START_MARKER
  /* write ID register to trigger logic analyzer */
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x00, ~0);
#endif

  if(dec_cont->vcmd_used) {
    if(dec_cont->mc_buf_id >= dec_cont->n_cores_available) {
      dec_cont->mc_buf_id = 0; /* in theory, shouldn't reach here */
    }
    DWLFlushRegister(dec_cont->dwl, dec_cont->cmdbuf_id, dec_cont->h264_regs,
                     dec_cont->mc_refresh_regs[dec_cont->mc_buf_id], dec_cont->mc_buf_id, (void *)dec_cont);
  }
  else {
    for (i = 2; i < DEC_X170_REGISTERS; i++) {
      DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 4 * i, dec_regs[i]);
    }
  }
}

/*------------------------------------------------------------------------------
    Function name : H264SetupVlcRegs
    Description   : set up registers for vlc mode

    Return type   :
    Argument      : container
------------------------------------------------------------------------------*/
void H264SetupVlcRegs(struct H264DecContainer * dec_cont) {
  u32 tmp, i = 0;
  u32 long_termflags = 0;
  u32 valid_flags = 0;
  u32 long_term_tmp = 0;
  i32 diff_poc, curr_poc, itmp;
  i32 tmp_frame_num = 0;
  u32 j = 0;

  const seqParamSet_t *p_sps = dec_cont->storage.active_sps;
  const sliceHeader_t *p_slice_header = dec_cont->storage.slice_header;
  const picParamSet_t *p_pps = dec_cont->storage.active_pps;
  dpbStorage_t *p_dpb = dec_cont->storage.dpb;
  const storage_t *storage = &dec_cont->storage;
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);
  if (!dec_cont->partial_decoding) {
    if (dec_cont->skip_non_intra && dec_cont->pp_enabled)
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS, 1);
    else
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS, 0);
  }
  else {
    SetDecRegister(dec_cont->h264_regs, HWIF_REF_READ_DIS, 1);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_OUT_DIS, 1);
  }

  SetDecRegister(dec_cont->h264_regs, HWIF_RLC_MODE_E, 0);

  if (dec_cont->high10p_mode)
    SetDecRegister(dec_cont->h264_regs, HWIF_ERROR_CONCEAL_E, dec_cont->hw_conceal);
  SetDecRegister(dec_cont->h264_regs, HWIF_SLICE_DEC_DIS, dec_cont->disable_slice_mode);

  u32 pic_init_qp;
  if ((i32)p_pps->pic_init_qp < (-(i32)(6 * (p_sps->bit_depth_luma - 8))))
    pic_init_qp = -(i32)(6 * (p_sps->bit_depth_luma - 8));
  else
    pic_init_qp = p_pps->pic_init_qp;

  SetDecRegister(dec_cont->h264_regs, HWIF_INIT_QP, pic_init_qp);

  SetDecRegister(dec_cont->h264_regs, HWIF_REFIDX0_ACTIVE,
                 p_pps->num_ref_idx_l0_active);

  SetDecRegister(dec_cont->h264_regs, HWIF_REF_FRAMES, p_sps->num_ref_frames);

  i = 0;
  while(p_sps->max_frame_num >> i) {
    i++;
  }
  SetDecRegister(dec_cont->h264_regs, HWIF_FRAMENUM_LEN, i - 1);

  SetDecRegister(dec_cont->h264_regs, HWIF_FRAMENUM,
                 p_slice_header->frame_num & ~(dec_cont->frame_num_mask));

  SetDecRegister(dec_cont->h264_regs, HWIF_CONST_INTRA_E,
                 p_pps->constrained_intra_pred_flag);

  SetDecRegister(dec_cont->h264_regs, HWIF_FILT_CTRL_PRES,
                 p_pps->deblocking_filter_control_present_flag);

  SetDecRegister(dec_cont->h264_regs, HWIF_RDPIC_CNT_PRES,
                 p_pps->redundant_pic_cnt_present_flag);

  SetDecRegister(dec_cont->h264_regs, HWIF_REFPIC_MK_LEN,
                 p_slice_header->dec_ref_pic_marking.strm_len);

  SetDecRegister(dec_cont->h264_regs, HWIF_IDR_PIC_E,
                 IS_IDR_NAL_UNIT(storage->prev_nal_unit));
  if (dec_cont->high10p_mode) {
    SetDecRegister(dec_cont->h264_regs, HWIF_IDR_PIC_ID_H10,
                   p_slice_header->idr_pic_id);
  } else
    SetDecRegister(dec_cont->h264_regs, HWIF_IDR_PIC_ID,
                   p_slice_header->idr_pic_id);

  SetDecRegister(dec_cont->h264_regs, HWIF_PPS_ID, storage->active_pps_id);
  SetDecRegister(dec_cont->h264_regs, HWIF_POC_LENGTH,
                 p_slice_header->poc_length_hw);

  /* reference picture flags */

  struct DWLLinearMem buf;
  H264InvalidDMVBuffer(p_dpb);
  H264ValidDMVBuffer(p_dpb, p_dpb->current_out->dmv_data);
  /* TODO separate fields */
  if(p_slice_header->field_pic_flag) {
    ASSERT(dec_cont->h264_profile_support != H264_BASELINE_PROFILE);

    for(i = 0; i < 32; i++) {
      long_term_tmp = p_dpb->buffer[i / 2].status[i & 1] == 3;
      long_termflags = long_termflags << 1 | long_term_tmp;

      /* For case TOPFIELD (I) + BOTTOM (P), and BOTTOM P refers to P itself. */
      if (p_slice_header->bottom_field_flag &&
          p_slice_header->num_ref_idx_l0_active > 1 &&
          p_dpb->current_out == &p_dpb->buffer[i/2] &&
          (p_dpb->current_out->pic_code_type[0] == DEC_PIC_TYPE_I
           && p_dpb->current_out->is_idr[0] == 0) &&
          IS_P_SLICE(p_slice_header->slice_type) &&
          (i & 1) && dec_cont->pic_number == 1) {
        buf = h264bsdGetRefPicDataVlcMode(p_dpb, i-1, 1);
        tmp = DWL_DEVMEM_VAILD(buf);
      }
      else {
        buf = h264bsdGetRefPicDataVlcMode(p_dpb, i, 1);
        tmp = DWL_DEVMEM_VAILD(buf);
      }
      if (tmp) {
        H264ValidDMVBuffer(p_dpb, p_dpb->buffer[i / 2].dmv_data);
      }
      valid_flags = valid_flags << 1 | tmp;
    }
    SetDecRegister(dec_cont->h264_regs, HWIF_REFER_LTERM_E, long_termflags);
  } else {
    for(i = 0; i < 16; i++) {
      u32 n = i;

      long_term_tmp = p_dpb->buffer[n].status[0] == 3 &&
                      p_dpb->buffer[n].status[1] == 3;
      long_termflags = long_termflags << 1 | long_term_tmp;

      buf = h264bsdGetRefPicDataVlcMode(p_dpb, n, 0);
      tmp = DWL_DEVMEM_VAILD(buf);
      valid_flags = valid_flags << 1 | tmp;
      if (tmp) H264ValidDMVBuffer(p_dpb, p_dpb->buffer[i].dmv_data);
    }

    valid_flags <<= 16;

    SetDecRegister(dec_cont->h264_regs, HWIF_REFER_LTERM_E, long_termflags << 16);
  }

  if(p_slice_header->field_pic_flag) {
    curr_poc = storage->poc->pic_order_cnt[p_slice_header->bottom_field_flag];
  } else {
    curr_poc = MIN(storage->poc->pic_order_cnt[0],
                   storage->poc->pic_order_cnt[1]);
  }
  for(i = 0; i < 16; i++) {
    u32 n = i;

    if(p_dpb->buffer[n].status[0] == 3 || p_dpb->buffer[n].status[1] == 3) {
      SetDecRegister(dec_cont->h264_regs, ref_pic_num[i],
                     p_dpb->buffer[n].pic_num);
    } else {
      /* if frame_num workaround activated and bit 12 of frame_num is
       * non-zero -> modify frame numbers of reference pictures so
       * that reference picture list reordering works as usual */
      if (p_slice_header->frame_num & dec_cont->frame_num_mask) {
        i32 tmp = p_dpb->buffer[n].frame_num - dec_cont->frame_num_mask;
        if (tmp < 0) tmp += p_sps->max_frame_num;
        SetDecRegister(dec_cont->h264_regs, ref_pic_num[i], tmp);
      } else {
        /*FIXME: below caode may cause side-effect, need to be refined */
#ifdef REORDER_ERROR_FIX
        if ((p_slice_header->ref_pic_list_reordering.ref_pic_list_reordering_flag_l0 ||
             p_slice_header->ref_pic_list_reordering_l1.ref_pic_list_reordering_flag_l0)) {
          if (IsExisting(&p_dpb->buffer[n], FRAME) ||
              (p_slice_header->field_pic_flag && p_slice_header->bottom_field_flag &&
               p_dpb->current_out == &p_dpb->buffer[n] && IsExisting(&p_dpb->buffer[n], TOPFIELD)))
            tmp_frame_num = p_dpb->buffer[n].frame_num;
          else if (j < p_dpb->invalid_pic_num_count) {
            /* next invalid pic_num */
            tmp_frame_num = p_dpb->pic_num_invalid[j++];
            if(p_slice_header->field_pic_flag)
              valid_flags |= 0x3 << (30-2*n);
            else
              valid_flags |= 1 << (31-n);

            H264ValidDMVBuffer(p_dpb, p_dpb->buffer[n].dmv_data);
            /* Set invalid pic buffer to dpb->buffer[0] */
            dec_cont->asic_buff->ref_pic_list[i] = dec_cont->asic_buff->ref_pic_list[0];
            dec_cont->asic_buff->ref_dmv_list[i] = dec_cont->asic_buff->ref_dmv_list[0];
          } else {
            tmp_frame_num = p_dpb->buffer[n].frame_num;
          }
        } else
#endif
        {
          tmp_frame_num = p_dpb->buffer[n].frame_num;
          (void)j;
        }
        SetDecRegister(dec_cont->h264_regs, ref_pic_num[i], tmp_frame_num);

      }

    }
    diff_poc = ABS(p_dpb->buffer[i].pic_order_cnt[0] - curr_poc);
    itmp = ABS(p_dpb->buffer[i].pic_order_cnt[1] - curr_poc);

    if(dec_cont->asic_buff->ref_pic_list[i])
      dec_cont->asic_buff->ref_pic_list[i] |=
        (addr_t)(diff_poc < itmp ? 0x1 : 0) | (addr_t)(p_dpb->buffer[i].is_field_pic ? 0x2 : 0);
  }

  if (dec_cont->skip_non_intra)
    SetDecRegister(dec_cont->h264_regs, HWIF_REFER_VALID_E, 0);
  else
    SetDecRegister(dec_cont->h264_regs, HWIF_REFER_VALID_E, valid_flags);

  dec_cont->valid_flags = valid_flags;
  if(dec_cont->h264_profile_support != H264_BASELINE_PROFILE ||
     dec_cont->hw_conceal) {
    h264PreparePOC(dec_cont);

    SetDecRegister(dec_cont->h264_regs, HWIF_CABAC_E,
                   p_pps->entropy_coding_mode_flag);
  }

#ifdef ENABLE_FPGA_VERIFICATION
  if (!dec_cont->pp_enabled && dec_cont->dpb_mode != DEC_DPB_INTERLACED_FIELD) {
    DWLmemset(dec_cont->asic_buff->out_buffer->virtual_address, 0,
              dec_cont->asic_buff->out_buffer->size);
#ifdef SUPPORT_DMA
    /* update device buffer by host buffer */
    DWLDMATransData((addr_t)dec_cont->asic_buff->out_buffer->bus_address,
                    (void *)dec_cont->asic_buff->out_buffer->virtual_address,
                    dec_cont->asic_buff->out_buffer->size,
                    HOST_TO_DEVICE);
#endif
  }
#else
  for (u32 i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if(dec_cont->ppu_cfg[i].enabled && dec_cont->ppu_cfg[i].pp_comp) {
      DWLmemset(dec_cont->asic_buff->out_buffer->virtual_address, 0,
                dec_cont->asic_buff->out_buffer->size);
      break;
    }
  }
#endif

  h264StreamPosUpdate(dec_cont);

}

/*------------------------------------------------------------------------------
    Function name   : H264InitRefPicList1
    Description     :
    Return type     : void
    Argument        : struct H264DecContainer *dec_cont
    Argument        : u32 *list0
    Argument        : u32 *list1
------------------------------------------------------------------------------*/
void H264InitRefPicList1(struct H264DecContainer * dec_cont, u32 * list0, u32 * list1) {
  u32 tmp, i;
  u32 idx, idx0, idx1, idx2;
  i32 ref_poc;
  const storage_t *storage = &dec_cont->storage;
  const dpbPicture_t *pic;

  ref_poc = MIN(storage->poc->pic_order_cnt[0], storage->poc->pic_order_cnt[1]);
  i = 0;

  pic = storage->dpb->buffer;
  while(IS_SHORT_TERM_FRAME(pic[list0[i]]) &&
        MIN(pic[list0[i]].pic_order_cnt[0], pic[list0[i]].pic_order_cnt[1]) <
        ref_poc)
    i++;

  idx0 = i;

  while(IS_SHORT_TERM_FRAME(pic[list0[i]]))
    i++;

  idx1 = i;

  while(IS_LONG_TERM_FRAME(pic[list0[i]]))
    i++;

  idx2 = i;

  /* list L1 */
  for(i = idx0, idx = 0; i < idx1; i++, idx++)
    list1[idx] = list0[i];

  for(i = 0; i < idx0; i++, idx++)
    list1[idx] = list0[i];

  for(i = idx1; idx < 16; idx++, i++)
    list1[idx] = list0[i];

  if(idx2 > 1) {
    tmp = 0;
    for(i = 0; i < idx2; i++) {
      tmp += (list0[i] != list1[i]) ? 1 : 0;
    }
    /* lists are equal -> switch list1[0] and list1[1] */
    if(!tmp) {
      i = list1[0];
      list1[0] = list1[1];
      list1[1] = i;
    }
  }
}

/*------------------------------------------------------------------------------
    Function name   : H264InitRefPicList1F
    Description     :
    Return type     : void
    Argument        : struct H264DecContainer *dec_cont
    Argument        : u32 *list0
    Argument        : u32 *list1
------------------------------------------------------------------------------*/
void H264InitRefPicList1F(struct H264DecContainer * dec_cont, u32 * list0, u32 * list1) {
  u32 i;
  u32 idx, idx0, idx1;
  i32 ref_poc;
  const storage_t *storage = &dec_cont->storage;
  const dpbPicture_t *pic;

  ref_poc =
    storage->poc->pic_order_cnt[storage->slice_header[0].bottom_field_flag];
  i = 0;

  pic = storage->dpb->buffer;
  while(IS_SHORT_TERM_FRAME_F(pic[list0[i]]) &&
        FIELD_POC(pic[list0[i]]) <= ref_poc)
    i++;

  idx0 = i;

  while(IS_SHORT_TERM_FRAME_F(pic[list0[i]]))
    i++;

  idx1 = i;

  /* list L1 */
  for(i = idx0, idx = 0; i < idx1; i++, idx++)
    list1[idx] = list0[i];

  for(i = 0; i < idx0; i++, idx++)
    list1[idx] = list0[i];

  for(i = idx1; idx < 16; idx++, i++)
    list1[idx] = list0[i];

}

/*------------------------------------------------------------------------------
    Function name   : H264InitRefPicList
    Description     :
    Return type     : void
    Argument        : struct H264DecContainer *dec_cont
------------------------------------------------------------------------------*/
void H264InitRefPicList(struct H264DecContainer * dec_cont) {
  sliceHeader_t *p_slice_header = dec_cont->storage.slice_header;
  pocStorage_t *poc = dec_cont->storage.poc;
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  DecAsicBuffers_t *p_asic_buff = dec_cont->asic_buff;
  u32 i, is_idr;
  u32 list0[34] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33
  };
  u32 list1[34] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33
  };
  u32 list_p[34] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33
  };

  /* determine if alternate view is IDR -> reference only inter-view ref
   * pic */
  is_idr = IS_IDR_NAL_UNIT(dec_cont->storage.prev_nal_unit);

  /* B lists */
  if(!dec_cont->rlc_mode) {
    if(p_slice_header->field_pic_flag) {
      /* list 0 */
      ShellSortF(dpb, list0, 1,
                 poc->pic_order_cnt[p_slice_header->bottom_field_flag]);
      if (dec_cont->storage.view && !dec_cont->storage.non_inter_view_ref) {
        i = 0;
        while (!is_idr && IS_REF_FRAME_F(dpb->buffer[list0[i]])) i++;
        list0[i] = 15;
      }
      /* list 1 */
      H264InitRefPicList1F(dec_cont, list0, list1);
      for(i = 0; i < 16; i++) {
        if (dec_cont->high10p_mode) {
          SetDecRegister(dec_cont->h264_regs, ref_pic_list0[i], list0[i]);
          SetDecRegister(dec_cont->h264_regs, ref_pic_list1[i], list1[i]);
        } else {
          SetDecRegister(dec_cont->h264_regs, ref_pic_list0_g1[i], list0[i]);
          SetDecRegister(dec_cont->h264_regs, ref_pic_list1_g1[i], list1[i]);
        }
      }
    } else {
      /* list 0 */
      ShellSort(dpb, list0, 1,
                MIN(poc->pic_order_cnt[0], poc->pic_order_cnt[1]));
      if (dec_cont->storage.view && !dec_cont->storage.non_inter_view_ref) {
        i = 0;
        while (!is_idr && IS_REF_FRAME(dpb->buffer[list0[i]])) i++;
        list0[i] = 15;
      }
      /* list 1 */
      H264InitRefPicList1(dec_cont, list0, list1);
      for(i = 0; i < 16; i++) {
        if (dec_cont->high10p_mode) {
          SetDecRegister(dec_cont->h264_regs, ref_pic_list0[i], list0[i]);
          SetDecRegister(dec_cont->h264_regs, ref_pic_list1[i], list1[i]);
        } else {
          SetDecRegister(dec_cont->h264_regs, ref_pic_list0_g1[i], list0[i]);
          SetDecRegister(dec_cont->h264_regs, ref_pic_list1_g1[i], list1[i]);
        }
      }
    }
  }

  /* P list */
  if(p_slice_header->field_pic_flag) {
    if(!dec_cont->rlc_mode) {
      ShellSortF(dpb, list_p, 0, 0);
      if (dec_cont->storage.view && !dec_cont->storage.non_inter_view_ref) {
        i = 0;
        while (!is_idr && IS_REF_FRAME_F(dpb->buffer[list_p[i]])) i++;
        list_p[i] = 15;
      }
      for(i = 0; i < 16; i++) {
        SetDecRegister(dec_cont->h264_regs, ref_pic_list_p[i], list_p[i]);

        /* copy to dpb for error handling purposes */
        dpb[0].list[i] = list_p[i];
        dpb[1].list[i] = list_p[i];
      }
    }
  } else {
    ShellSort(dpb, list_p, 0, 0);
    if (dec_cont->storage.view && !dec_cont->storage.non_inter_view_ref) {
      i = 0;
      while (!is_idr && IS_REF_FRAME(dpb->buffer[list_p[i]])) i++;
      list_p[i] = 15;
    }

    if (dec_cont->high10p_mode && dec_cont->valid_flags) {
      for(i = 0; i < 16; i++) {
        if (IsRefValid(dec_cont->valid_flags, list_p[i])) {
          p_asic_buff->default_ref_address = p_asic_buff->ref_pic_list[list_p[i]];
          p_asic_buff->default_dmv_address = p_asic_buff->ref_dmv_list[list_p[i]];
          break;
        }
      }
    }

    for(i = 0; i < 16; i++) {
      if(!dec_cont->rlc_mode) {
        SetDecRegister(dec_cont->h264_regs, ref_pic_list_p[i], list_p[i]);
      }
      /* copy to dpb for error handling purposes */
      dpb[0].list[i] = list_p[i];
      dpb[1].list[i] = list_p[i];
    }
  }
}

/*------------------------------------------------------------------------------
    Function name : h264StreamPosUpdate
    Description   : Set stream base and length related registers

    Return type   :
    Argument      : container
------------------------------------------------------------------------------*/
void h264StreamPosUpdate(struct H264DecContainer * dec_cont) {
  addr_t tmp;
  u8 *p_tmp;
  u32 is_rb;
  const struct DecHwFeatures *hw_feature = NULL;
  SwReadByteFn *fn_read_byte;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);

  APITRACEDEBUG("%s","h264StreamPosUpdate:\n");
  tmp = 0;
  is_rb = dec_cont->use_ringbuffer;

  p_tmp = dec_cont->p_hw_stream_start;

  fn_read_byte = SwGetReadByteFunc(&dec_cont->llstrminfo.stream_info);
  /* NAL start prefix in stream start is 0 0 0 or 0 0 1 */
  if (dec_cont->p_hw_stream_start + 2 >= dec_cont->hw_buffer + dec_cont->buff_length) {
    u8 i, start_prefix[3];
    for(i = 0; i < 3; i++) {
      if (dec_cont->p_hw_stream_start + i < dec_cont->hw_buffer + dec_cont->buff_length)
        start_prefix[i] = fn_read_byte(dec_cont->p_hw_stream_start + i, dec_cont->buff_length,
                                       &dec_cont->llstrminfo.stream_info);
      else
        start_prefix[i] = fn_read_byte(dec_cont->p_hw_stream_start + i - dec_cont->buff_length,
                                       dec_cont->buff_length, &dec_cont->llstrminfo.stream_info);
    }
    if (!(*start_prefix + *(start_prefix + 1))) {
      if (*(start_prefix + 2) < 2) {
        tmp = 1;
      }
    }
  } else {
    if(!(fn_read_byte(dec_cont->p_hw_stream_start, dec_cont->buff_length, &dec_cont->llstrminfo.stream_info) +
        fn_read_byte(dec_cont->p_hw_stream_start + 1, dec_cont->buff_length, &dec_cont->llstrminfo.stream_info))) {
      if(fn_read_byte(dec_cont->p_hw_stream_start + 2, dec_cont->buff_length, &dec_cont->llstrminfo.stream_info) < 2) {
        tmp = 1;
      }
    }
  }

  /* stuff related to frame_num workaround, if used -> advance stream by
   * start code prefix and HW is set to decode in NAL unit mode */
  if (tmp && dec_cont->force_nal_mode) {
    tmp = 0;
    /* skip start code prefix */
    while (fn_read_byte(p_tmp++, dec_cont->buff_length, &dec_cont->llstrminfo.stream_info) == 0);

    dec_cont->hw_stream_start_bus += p_tmp - dec_cont->p_hw_stream_start;
    dec_cont->p_hw_stream_start = p_tmp;
    dec_cont->hw_length -= p_tmp - dec_cont->p_hw_stream_start;
  }

  if (dec_cont->start_code_detected)
      tmp = 1;

  APITRACEDEBUG("\tByte stream   %8d\n", tmp);
  SetDecRegister(dec_cont->h264_regs, HWIF_START_CODE_E, tmp);
  dec_cont->nal_mode = !tmp;

  /* bit offset if base is unaligned */

  tmp = (dec_cont->hw_stream_start_bus & DEC_HW_ALIGN_MASK) * 8;


  APITRACEDEBUG("\tStart bit pos %8d\n", tmp);

  SetDecRegister(dec_cont->h264_regs, HWIF_STRM_START_BIT, tmp);

  dec_cont->hw_bit_pos = tmp;

  if(!dec_cont->high10p_mode) {
    tmp = dec_cont->hw_stream_start_bus;   /* unaligned base */

   /* In some releases, G1 uses G2 stream feeding method. */
       tmp &= (~(addr_t)DEC_HW_ALIGN_MASK);


    APITRACEDEBUG("\tStream base   %08x\n", tmp);
    if(dec_cont->low_latency)
      dec_cont->llstrminfo.ll_strm_bus_address = tmp;
    SET_ADDR_REG(dec_cont->h264_regs, HWIF_RLC_VLC_BASE, tmp);

    tmp = dec_cont->hw_length;   /* unaligned stream */
    tmp += dec_cont->hw_bit_pos / 8;  /* add the alignmet bytes */

    APITRACEDEBUG("\tStream length %8d\n", tmp);
    if(dec_cont->low_latency) {
      dec_cont->llstrminfo.ll_strm_len = tmp;
      dec_cont->llstrminfo.first_update = 1;
      SetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN, 0);
      SetDecRegister(dec_cont->h264_regs, HWIF_LAST_BUFFER_E, 0);
      if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
        *dec_cont->llstrminfo.strm_status_addr = 0;
      }
      dec_cont->llstrminfo.update_reg_flag = 1;
    } else
      SetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN, tmp);


    SetDecRegister(dec_cont->h264_regs, HWIF_STRM_START_OFFSET, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_STRM_BUFFER_LEN, tmp);

#ifdef SUPPORT_DMA
    DWLDMATransData((addr_t)dec_cont->hw_stream_start_bus,
                    (void *)dec_cont->p_hw_stream_start,
                    dec_cont->hw_length, HOST_TO_DEVICE);
#endif
  } else {
    addr_t tmp_addr;
    if (is_rb) {
      /* stream data base address */
      tmp_addr = dec_cont->buff_start_bus; /* unaligned base */
      ASSERT((tmp_addr & 0xF) == 0);
      SET_ADDR_REG(dec_cont->h264_regs, HWIF_STREAM_BASE, tmp_addr);

      /* stream data start offset */
      tmp = dec_cont->hw_stream_start_bus - dec_cont->buff_start_bus; /* unaligned base */
      tmp &= (~(addr_t)DEC_HW_ALIGN_MASK);         /* align the base */
      SetDecRegister(dec_cont->h264_regs, HWIF_STRM_START_OFFSET, tmp);
    } else {
      /* stream data base address */
      tmp_addr = dec_cont->hw_stream_start_bus; /* unaligned base */
      tmp_addr &= (~(addr_t)DEC_HW_ALIGN_MASK);         /* align the base */
      ASSERT((tmp_addr & (addr_t)DEC_HW_ALIGN_MASK) == 0);

      SET_ADDR_REG(dec_cont->h264_regs, HWIF_STREAM_BASE, tmp_addr);

      /* stream data start offset */
      SetDecRegister(dec_cont->h264_regs, HWIF_STRM_START_OFFSET, 0);
    }

    /* stream data length */
    tmp = dec_cont->hw_length;       /* unaligned stream */
    tmp += dec_cont->hw_bit_pos / 8; /* add the alignmet bytes */

    if(dec_cont->low_latency) {
      dec_cont->llstrminfo.ll_strm_bus_address = dec_cont->hw_stream_start_bus & (~DEC_HW_ALIGN_MASK);
      dec_cont->llstrminfo.ll_strm_len = tmp;
      dec_cont->llstrminfo.first_update = 1;
      SetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN, 0);
      SetDecRegister(dec_cont->h264_regs, HWIF_LAST_BUFFER_E, 0);
      if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
        *dec_cont->llstrminfo.strm_status_addr = 0;
      }
      dec_cont->llstrminfo.update_reg_flag = 1;
    } else
      SetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN, tmp);

    /* stream buffer size */
    if (is_rb)
      tmp = dec_cont->buff_length;       /* stream buffer size */
    else
      tmp = dec_cont->buff_start_bus + dec_cont->buff_length - tmp_addr;
      //tmp = dec_cont->buff_start_bus + dec_cont->hw_length + (dec_cont->hw_bit_pos / 8) - tmp_addr;
    SetDecRegister(dec_cont->h264_regs, HWIF_STRM_BUFFER_LEN, tmp);

#ifdef SUPPORT_DMA
    DWLDMATransData((addr_t)dec_cont->buff_start_bus,
                    (void *)dec_cont->hw_buffer,
                    dec_cont->buff_length, HOST_TO_DEVICE);
#endif
  }
}

/*------------------------------------------------------------------------------
    Function name : H264PrepareCabacInitTables
    Description   : Prepare CABAC initialization tables

    Return type   : void
    Argument      : u32 *cabac_init
------------------------------------------------------------------------------*/
void H264PrepareCabacInitTables(u32 *cabac_init) {
  ASSERT(cabac_init != NULL);
  (void) DWLmemcpy(cabac_init, h264_cabac_init_values, 4 * 460 * 2);
}

void h264CopyPocToHw(struct H264DecContainer *dec_cont) {
  const u32 core_id = dec_cont->b_mc ? (dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id) : 0;
  struct DWLLinearMem *cabac_mem = dec_cont->asic_buff->cabac_init + core_id;
  i32 *poc_base = (i32 *) ((u8 *) cabac_mem->virtual_address +
                           ASIC_CABAC_INIT_BUFFER_SIZE);

  if(dec_cont->asic_buff->enable_dmv_and_poc) {
    DWLmemcpy(poc_base, dec_cont->poc, sizeof(dec_cont->poc));
  }
}

void h264PreparePOC(struct H264DecContainer *dec_cont) {
  const sliceHeader_t *p_slice_header = dec_cont->storage.slice_header;
  const seqParamSet_t *p_sps = dec_cont->storage.active_sps;
  const dpbStorage_t *p_dpb = dec_cont->storage.dpb;
  const pocStorage_t *poc = dec_cont->storage.poc;

  int i;

  i32 *poc_base, curr_poc;

  if(dec_cont->b_mc) {
    /* For multicore we cannot write to HW buffer
     * as the core is not yet reserved.
     */
    poc_base = dec_cont->poc;
  } else {
    struct DWLLinearMem *cabac_mem = dec_cont->asic_buff->cabac_init;
    poc_base = (i32 *) ((u8 *) cabac_mem->virtual_address +
                        ASIC_CABAC_INIT_BUFFER_SIZE);
  }

  if(!dec_cont->asic_buff->enable_dmv_and_poc) {
    SetDecRegister(dec_cont->h264_regs, HWIF_PICORD_COUNT_E, 0);
    if (!dec_cont->hw_conceal)
      return;
  } else
    SetDecRegister(dec_cont->h264_regs, HWIF_PICORD_COUNT_E, 1);

  if (p_slice_header->field_pic_flag) {
    curr_poc = poc->pic_order_cnt[p_slice_header->bottom_field_flag ? 1 : 0];
  } else {
    curr_poc = MIN(poc->pic_order_cnt[0], poc->pic_order_cnt[1]);
  }

  for (i = 0; i < 32; i++) {
    *poc_base++ = p_dpb->buffer[i / 2].pic_order_cnt[i & 0x1];
  }

  if (p_slice_header[0].field_pic_flag || !p_sps->mb_adaptive_frame_field_flag) {
    *poc_base++ = curr_poc;
    *poc_base = 0;
  } else {
    *poc_base++ = poc->pic_order_cnt[0];
    *poc_base++ = poc->pic_order_cnt[1];
  }
}

void h264PrepareScaleList(struct H264DecContainer *dec_cont) {
  const picParamSet_t *p_pps = dec_cont->storage.active_pps;
  const u8 (*scaling_list)[64];
  const seqParamSet_t *p_sps = dec_cont->storage.active_sps;
  const u32 core_id = dec_cont->b_mc ? (dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id) : 0;
  u32 i, j, tmp;
  u32 *p;

  struct DWLLinearMem *cabac_mem = dec_cont->asic_buff->cabac_init + core_id;

  if (!p_pps->scaling_matrix_present_flag && !p_sps->scaling_matrix_present_flag)
    return;

  if (!dec_cont->high10p_mode)
    p = (u32 *) ((u8 *) cabac_mem->virtual_address +
                 ASIC_CABAC_INIT_BUFFER_SIZE +
                 ASIC_POC_BUFFER_SIZE);
  else
    p = (u32 *) ((u8 *) cabac_mem->virtual_address +
                 ASIC_CABAC_INIT_BUFFER_SIZE +
                 ASIC_POC_BUFFER_SIZE_H10);

  scaling_list = p_pps->scaling_list;
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 4; j++) {
      tmp = (scaling_list[i][4 * j + 0] << 24) |
            (scaling_list[i][4 * j + 1] << 16) |
            (scaling_list[i][4 * j + 2] << 8) |
            (scaling_list[i][4 * j + 3]);
      *p++ = tmp;
    }
  }
  for (i = 6; i < 8; i++) {
    for (j = 0; j < 16; j++) {
      tmp = (scaling_list[i][4 * j + 0] << 24) |
            (scaling_list[i][4 * j + 1] << 16) |
            (scaling_list[i][4 * j + 2] << 8) |
            (scaling_list[i][4 * j + 3]);
      *p++ = tmp;
    }
  }
}

void H264UpdateAfterHwRdy(struct H264DecContainer *dec_cont, u32 *h264_regs) {
  DecAsicBuffers_t *p_asic_buff = dec_cont->asic_buff;

  /* any B stuff detected by HW? (note reg name changed from
   * b_detected to pic_inf)
   */
  if(GetDecRegister(h264_regs, HWIF_DEC_PIC_INF)) {
    if((dec_cont->h264_profile_support != H264_BASELINE_PROFILE) &&
        (p_asic_buff->enable_dmv_and_poc == 0)) {
      APITRACEDEBUG("%s","HW Detected B slice in baseline profile stream!!!\n");
      p_asic_buff->enable_dmv_and_poc = 1;
    }

    /* reset the reg */
    SetDecRegister(h264_regs, HWIF_DEC_PIC_INF, 0);
  }
  /*  TODO(atna): Do we support RefBuff in multicore? */
}

i32 H264ReplaceRefPic(struct H264DecContainer *dec_cont, u32 dpb_index) {
  u32 i = 0, j = 0;
  DecAsicBuffers_t *p_asic_buff = dec_cont->asic_buff;
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  storage_t *storage = &dec_cont->storage;
  u32 curr_poc = 0;
  u32 buff_poc = 0;

  i32 find_idx = EC_INVALID_IDX;
  u32 poc_delta = 0x7FFFFFFF;
  u32 poc_delta_pre = 0x7FFFFFFF;

  u32 correct_count[MAX_DPB_SIZE + 1] = {0};
  u32 ref_error_count[MAX_DPB_SIZE + 1] = {0};
  u32 tolerable_error_count[MAX_DPB_SIZE + 1] = {0};
  u32 frame_error_count[MAX_DPB_SIZE + 1] = {0};

  /* ignore rlc mode. */
  if (dec_cont->rlc_mode)
    return EC_INVALID_IDX;

  /* NO_RFC: if error_ratio less than 10%, don't replace it, use it as correct. */
  if (storage->slice_header->field_pic_flag) {
    if (!dec_cont->use_video_compressor &&
        dpb->buffer[dpb_index].error_ratio[0] <= EC_RATIO_THRESHOLD &&
        dpb->buffer[dpb_index].error_ratio[1] <= EC_RATIO_THRESHOLD)
      return dpb_index;
  } else {
    if (!dec_cont->use_video_compressor &&
        dpb->buffer[dpb_index].error_ratio[0] <= EC_RATIO_THRESHOLD)
      return dpb_index;
  }

  /* ref_buffer error info count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    for (j = 0; j <= dpb->dpb_size; j++) {
      if (dpb->buffer[i].mem_idx == p_asic_buff->ref_mem_idx[j]) {
        if (storage->slice_header->field_pic_flag) {
          curr_poc = storage->poc->pic_order_cnt[storage->slice_header->bottom_field_flag];
          buff_poc = dpb->buffer[i].pic_order_cnt[storage->slice_header->bottom_field_flag];
        } else {
          curr_poc = GET_POC(*storage->dpb->current_out);
          buff_poc = GET_POC(dpb->buffer[i]);
        }
        /* skip self dpb buffer. */
        if (buff_poc == curr_poc)
          continue;

        if (dpb->buffer[i].error_info == DEC_NO_ERROR)
          correct_count[i]++;
        else if (dpb->buffer[i].error_info == DEC_REF_ERROR)
          ref_error_count[i]++;
        else {
          /* NO_RFC: if error_ratio less than 10%, use it as correct. */
          if (storage->slice_header->field_pic_flag) {
            if (!dec_cont->use_video_compressor &&
                dpb->buffer[i].error_ratio[0] <= EC_RATIO_THRESHOLD &&
                dpb->buffer[i].error_ratio[1] <= EC_RATIO_THRESHOLD)
              tolerable_error_count[i]++;
            else
              frame_error_count[i]++;
          } else {
            if (!dec_cont->use_video_compressor &&
                dpb->buffer[i].error_ratio[0] <= EC_RATIO_THRESHOLD)
              tolerable_error_count[i]++;
            else
              frame_error_count[i]++;
          }
        }
        break;
      }
    }
  }

  if (storage->slice_header->field_pic_flag) {
    curr_poc = dpb->buffer[dpb_index].pic_order_cnt[storage->slice_header->bottom_field_flag];
  } else {
    curr_poc = GET_POC(dpb->buffer[dpb_index]);
  }
  /* firstly: find from correct_count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (correct_count[i]) {
      if (storage->slice_header->field_pic_flag) {
        buff_poc = dpb->buffer[i].pic_order_cnt[storage->slice_header->bottom_field_flag];
      } else {
        buff_poc = GET_POC(dpb->buffer[i]);
      }
      poc_delta = buff_poc > curr_poc ? buff_poc - curr_poc : curr_poc - buff_poc;
      poc_delta_pre = poc_delta_pre > poc_delta ? poc_delta : poc_delta_pre;
      if (poc_delta_pre == poc_delta) find_idx = i;
    }
  }
  if (find_idx != EC_INVALID_IDX)
    return find_idx;

  /* secondly: find from ref_error_count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (ref_error_count[i]) {
      if (storage->slice_header->field_pic_flag) {
        buff_poc = dpb->buffer[i].pic_order_cnt[storage->slice_header->bottom_field_flag];
      } else {
        buff_poc = GET_POC(dpb->buffer[i]);
      }
      poc_delta = buff_poc > curr_poc ? buff_poc - curr_poc : curr_poc - buff_poc;
      poc_delta_pre = poc_delta_pre > poc_delta ? poc_delta : poc_delta_pre;
      if (poc_delta_pre == poc_delta) find_idx = i;
    }
  }
  if (find_idx != EC_INVALID_IDX)
    return find_idx;

  /* Thirdly: find from tolerable_error_count */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (tolerable_error_count[i]) {
      if (storage->slice_header->field_pic_flag) {
        buff_poc = dpb->buffer[i].pic_order_cnt[storage->slice_header->bottom_field_flag];
      } else {
        buff_poc = GET_POC(dpb->buffer[i]);
      }
      poc_delta = buff_poc > curr_poc ? buff_poc - curr_poc : curr_poc - buff_poc;
      poc_delta_pre = poc_delta_pre > poc_delta ? poc_delta : poc_delta_pre;
      if (poc_delta_pre == poc_delta) find_idx = i;
    }
  }
  if (find_idx != EC_INVALID_IDX)
    return find_idx;

  /* not find */
  return EC_INVALID_IDX;
}

u32 H264CheckHwStatus(struct H264DecContainer *dec_cont)
{
   u32 tmp = 0;
   if (dec_cont->vcmd_used) {
     tmp = dec_cont->h264_regs[1];
   } else {
     tmp = DWLReadRegFromHw(dec_cont->dwl, dec_cont->core_id, 4 * 1);
   }

   if(tmp & 0x01)
     return 1;
   else
     return 0;
}
