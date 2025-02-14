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

#include <string.h>
#include "basetype.h"
#include "version.h"
#include "h264hwd_container.h"
#include "h264decapi.h"
#include "h264hwd_decoder.h"
#include "h264hwd_util.h"
#include "h264hwd_exports.h"
#include "h264hwd_dpb.h"
#include "h264hwd_neighbour.h"
#include "h264hwd_asic.h"
#include "regdrv.h"
#include "h264hwd_byte_stream.h"
#include "deccfg.h"
#include "tiledref.h"
#include "workaround.h"
#include "errorhandling.h"
#include "commonconfig.h"
#include "commonfunction.h"
#include "vpufeature.h"
#include "ppu.h"
#include "delogo.h"
#include "sw_stream.h"

#ifdef MODEL_SIMULATION
#include "asic.h"
#endif

#include "dwl.h"
#include "h264hwd_dpb_lock.h"
#include "h264decmc_internals.h"
#include "dec_log.h"

/*
 * DEC_TRACE         Trace H264 Decoder API function calls. H264DecTrace
 *                       must be implemented externally.
 * DEC_EVALUATION    Compile evaluation version, restricts number of frames
 *                       that can be decoded
 */

#ifndef TRACE_PP_CTRL
#define TRACE_PP_CTRL(...)          do{}while(0)
#else
#undef TRACE_PP_CTRL
#define TRACE_PP_CTRL(...)          printf(__VA_ARGS__)
#endif

#define IS_REFERENCE_F(a)       IsReferenceField(&(a))
static u32 IsReferenceField( const dpbPicture_t *a) {
  return (a->status[0] != UNUSED && a->status[0] != EMPTY) ||
         (a->status[1] != UNUSED && a->status[1] != EMPTY);
}
#define GET_POC(pic)            GetPoc(&(pic))
static i32 GetPoc(dpbPicture_t *pic) {
  i32 poc0 = (pic->status[0] == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt[0]);
  i32 poc1 = (pic->status[1] == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt[1]);
  return MIN(poc0,poc1);
}

static void h264UpdateAfterPictureDecode(struct H264DecContainer * dec_cont);
static u32 h264SpsSupported(const struct H264DecContainer * dec_cont);
static u32 h264PpsSupported(const struct H264DecContainer * dec_cont);
static u32 h264StreamIsBaseline(const struct H264DecContainer * dec_cont);

static u32 h264AllocateResources(struct H264DecContainer * dec_cont);
static void bsdDecodeReturn(u32 retval);
static void h264CorruptedProcess(struct H264DecContainer * dec_cont);

static void h264GetSarInfo(const storage_t * storage,
                           u32 * sar_width, u32 * sar_height);
static void h264CycleCount(struct H264DecContainer * dec_cont);
static void h264MCMarkOutputPicInfo(struct H264DecContainer *dec_cont,
                                    const H264HwRdyCallbackArg *info,
                                    enum DecErrorInfo error_info,
                                    const u32* dec_regs);
static void h264SCMarkOutputPicInfo(struct H264DecContainer * dec_cont, u32 picture_broken);
// static void H264DropCurrentPicutre(struct H264DecContainer *dec_cont);
static u32 h264ReplaceRefAvalible(struct H264DecContainer *dec_cont);

extern void h264PreparePpRun(struct H264DecContainer * dec_cont);

static void h264CheckReleasePpAndHw(struct H264DecContainer *dec_cont);

static enum DecRet h264DecNextPictureINTERNAL(H264DecInst dec_inst,
    H264DecPicture * output,
    u32 end_of_stream);
static enum DecRet h264ECDecisionOutput(struct H264DecContainer * dec_cont, H264DecPicture * output);

static void h264SetExternalBufferInfo(H264DecInst dec_inst, storage_t *storage) ;
static void h264SetMVCExternalBufferInfo(H264DecInst dec_inst, storage_t *storage);
static void h264EnterAbortState(struct H264DecContainer *dec_cont);
static void h264ExistAbortState(struct H264DecContainer *dec_cont);
static void h264StateReset(struct H264DecContainer *dec_cont);
static void h264CheckBufferRealloc(struct H264DecContainer *dec_cont);
#define DEC_DPB_NOT_INITIALIZED      -1
#define DEC_DPB_INVALID_IDX      -1

#ifdef CASE_INFO_STAT
extern CaseInfo case_info;
static void H264GetSimInfo(storage_t *storage, CaseInfo *case_info, u32 width, u32 height);
static void H264CaseInfoCollect(struct H264DecContainer *dec_cont, CaseInfo *case_info);
#endif
/*------------------------------------------------------------------------------

    Function: H264DecInit()

        Functional description:
            Initialize decoder software. Function reserves memory for the
            decoder instance and calls h264bsdInit to initialize the
            instance data.

        Inputs:
            dec_cfg->no_output_reordering
                                flag to indicate decoder that it doesn't have
                                to try to provide output pictures in display
                                order, saves memory
            dec_cfg->error_handling
                                Flag to determine which error concealment
                                method to use.

        Outputs:
            dec_inst             pointer to initialized instance is stored here

        Returns:
            DEC_OK        successfully initialized the instance
            DEC_INITFAIL  initialization failed
            DEC_PARAM_ERROR invalid parameters
            DEC_MEMFAIL   memory allocation failed
            DEC_DWL_ERROR error initializing the system interface
------------------------------------------------------------------------------*/

enum DecRet H264DecInit(H264DecInst * dec_inst,
                       const void *dwl,
                       struct H264DecConfig *dec_cfg) {

  /*@null@ */ struct H264DecContainer *dec_cont;

  u32 low_latency_sim = 0;
  const struct DecHwFeatures *hw_feature = NULL;
  enum DecRet ret;
  u32 client_type;
  //APITRACE("%s","H264DecInit#\n");

  /* check that right shift on negative numbers is performed signed */
  /*lint -save -e* following check causes multiple lint messages */
#if (((-1) >> 1) != (-1))
#error Right bit-shifting (>>) does not preserve the sign
#endif
  /*lint -restore */

  if(dec_inst == NULL) {
    APITRACEERR("%s","H264DecInit# dec_inst == NULL\n");
    return (DEC_PARAM_ERROR);
  }

  *dec_inst = NULL;   /* return NULL instance for any error */

  /* check that H.264 decoding supported in HW */
  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);
  if(!hw_feature->h264_support && !hw_feature->h264_adv_support) {
    APITRACEERR("%s","H264DecInit# H264 not supported in HW\n");
    return DEC_FORMAT_NOT_SUPPORTED;
  }

  if (!hw_feature->low_latency_mode_support &&
      (dec_cfg->decoder_mode & DEC_LOW_LATENCY)) {
    /* low lantency mode is NOT supported */
    return (DEC_PARAM_ERROR);
  }

  dec_cont = (struct H264DecContainer *) DWLmalloc(sizeof(struct H264DecContainer));
  if(dec_cont == NULL) {
    APITRACEERR("%s","H264DecInit# Memory allocation failed\n");
    return (DEC_MEMFAIL);
  }

  (void) DWLmemset(dec_cont, 0, sizeof(struct H264DecContainer));
  dec_cont->dwl = dwl;

  h264bsdInit(&dec_cont->storage, dec_cfg->no_output_reordering, 0);

  dec_cont->dec_stat = DEC_INITIALIZED;

  dec_cont->h264_regs[0] = DWLReadAsicID(DWL_CLIENT_TYPE_H264_DEC);

  if (!hw_feature->h264_adv_support) {
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE, DEC_MODE_H264);
  } else
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE, DEC_MODE_H264_H10P);

  dec_cont->high10p_mode = dec_cont->storage.high10p_mode = hw_feature->h264_adv_support;
  dec_cont->h264_high10p_support = hw_feature->h264_high10_support;
  dec_cont->h264_422_intra_support = hw_feature->h264_422_intra_support;

  if (dec_cfg->rlc_mode) {
    /* Force the decoder into RLC mode */
    dec_cont->force_rlc_mode = 1;
    dec_cont->rlc_mode = 1;
    dec_cont->try_vlc = 0;
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE, DEC_MODE_H264);
  }

  SetCommonConfigRegs(dec_cont->h264_regs);

  /* Set prediction filter taps */
  SetDecRegister(dec_cont->h264_regs, HWIF_PRED_BC_TAP_0_0, 1);
  SetDecRegister(dec_cont->h264_regs, HWIF_PRED_BC_TAP_0_1, (u32)(-5));
  SetDecRegister(dec_cont->h264_regs, HWIF_PRED_BC_TAP_0_2, 20);
  pthread_mutex_init(&dec_cont->protect_mutex, NULL);
  pthread_mutex_init(&dec_cont->dmv_buffer_mutex, NULL);
  /* CV to be signaled when a dmv buffer is consumed by Application */
  pthread_cond_init(&dec_cont->dmv_buffer_cv, NULL);
  if (dec_cfg->decoder_mode & DEC_LOW_LATENCY) {
#ifdef ASIC_TRACE_SUPPORT
    low_latency_sim = 1;
#else
    dec_cont->low_latency = 1;
    dec_cont->llstrminfo.updated_reg = 0;
#endif
    /* Set flag for using ddr_low_latency model and set pollmode and polltime swregs */
    SetDecRegister(dec_cont->h264_regs, HWIF_STREAM_STATUS_EXT_BUFFER_E, 1);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MC_POLLMODE, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MC_POLLTIME, 0);
    dec_cont->llstrminfo.strm_status_in_buffer = 1;
  }
  dec_cont->secure_mode = (dec_cfg->decoder_mode & DEC_SECURITY) ? 1 : 0;

  if(dec_cont->low_latency || low_latency_sim) {
    SetDecRegister(dec_cont->h264_regs, HWIF_BUFFER_EMPTY_INT_E, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_BLOCK_BUFFER_MODE_E, 1);
    dec_cont->disable_slice_mode = 1;
  } else if ( dec_cont->secure_mode) {

  } else {
    SetDecRegister(dec_cont->h264_regs, HWIF_BUFFER_EMPTY_INT_E, 1);
    SetDecRegister(dec_cont->h264_regs, HWIF_BLOCK_BUFFER_MODE_E, 0);
  }
  if (dec_cfg->decoder_mode & DEC_PARTIAL_DECODING)
    dec_cont->partial_decoding = 1;

  if (dec_cfg->decoder_mode & DEC_INTRA_ONLY)
    dec_cont->skip_non_intra = dec_cont->storage.skip_non_intra = 1;

  dec_cont->h264_profile_support = hw_feature->h264_support;

#ifdef MODEL_SIMULATION
  cmodel_ref_buf_alignment = MAX(16, ALIGN(dec_cont->align));
#endif

  /* for VCD, the max suporrted stream length is 32bit, consider SW memory allocation capability,
     the limitation is set to 2^30 Bytes length */

  dec_cont->max_strm_len = DEC_X170_MAX_STREAM_VCD;

  dec_cont->storage.release_buffer = 0;

  dec_cont->pp_buffer_queue = InputQueueInit(0);
  if (dec_cont->pp_buffer_queue == NULL) {
    ret = DEC_MEMFAIL;
    goto err;
  }
  dec_cont->storage.pp_buffer_queue = dec_cont->pp_buffer_queue;

  /* Custom DPB modes require tiled support >= 2 */
  dec_cont->dpb_mode = DEC_DPB_NOT_INITIALIZED;

  dec_cont->error_info = DEC_NO_ERROR;
  dec_cont->error_ratio = dec_cfg->error_ratio;
  dec_cont->error_handling = dec_cfg->error_handling;
  dec_cont->error_policy = HANTRO_FALSE;
  dec_cont->storage.picture_broken = HANTRO_FALSE;

  dec_cont->multi_frame_input_flag = dec_cfg->multi_frame_input_flag;
  dec_cont->use_video_compressor = dec_cfg->use_video_compressor;
  dec_cont->support_asofmo_stream = dec_cfg->support_asofmo_stream;
  dec_cont->storage.use_video_compressor = dec_cfg->use_video_compressor;
  dec_cont->storage.mvc = dec_cfg->mvc ? HANTRO_TRUE : HANTRO_FALSE;
  if(dec_cont->low_latency && dec_cfg->mvc){
    APITRACEERR("%s","H264DecDecode# DEC_STREAM_NOT_SUPPORTED, mvc mode can't use in low latency.\n");
    ret = DEC_FORMAT_NOT_SUPPORTED;
    goto err;
  }
  /* max decodable picture width */
  dec_cont->max_dec_pic_width = hw_feature->h264_max_dec_pic_width;
  dec_cont->max_dec_pic_height = hw_feature->h264_max_dec_pic_height;

  dec_cont->checksum = dec_cont;  /* save instance as a checksum */

#ifdef _ENABLE_2ND_CHROMA
  dec_cont->storage.enable2nd_chroma = 1;
#endif

  InitWorkarounds(DEC_MODE_H264, &dec_cont->workarounds);
  if (dec_cont->workarounds.h264.frame_num)
    dec_cont->frame_num_mask = 0x1000;

  /*  default single core */
  dec_cont->n_cores = 1;

  /* Init frame buffer list */
  InitList(&dec_cont->fb_list);

  dec_cont->storage.dpbs[0]->fb_list = &dec_cont->fb_list;
  dec_cont->storage.dpbs[1]->fb_list = &dec_cont->fb_list;

  dec_cont->storage.dpbs[0]->dmv_buffer_mutex = &dec_cont->dmv_buffer_mutex;
  dec_cont->storage.dpbs[1]->dmv_buffer_mutex = &dec_cont->dmv_buffer_mutex;

  dec_cont->storage.dpbs[0]->dmv_buffer_cv = &dec_cont->dmv_buffer_cv;
  dec_cont->storage.dpbs[1]->dmv_buffer_cv = &dec_cont->dmv_buffer_cv;

  dec_cont->use_adaptive_buffers = dec_cfg->use_adaptive_buffers;
  dec_cont->n_guard_size = dec_cfg->guard_size;

  dec_cont->qp_output_enable = dec_cont->storage.qp_output_enable =
        (dec_cfg->dump_auxinfo & DEC_AUX_QP);
  if (dec_cont->qp_output_enable && hw_feature->qp_dump_support == 0)
    dec_cont->qp_output_enable = dec_cont->storage.qp_output_enable = 0;

  dec_cont->dmv_output_enable = dec_cont->storage.dmv_output_enable =
        (dec_cfg->dump_auxinfo & DEC_AUX_MV);

  u32 hw_build_id, i, tmp = 0;
  dec_cont->n_cores = DWLReadAsicCoreCount();

#ifdef ASIC_TRACE_SUPPORT
  if (dec_cfg->mcinit_cfg.mc_enable) {
    dec_cfg->mcinit_cfg.mc_enable = 0;
    dec_cfg->sim_mc = 1;
    DWLSetSimMc(dec_cont->dwl);
  }
#endif

  if (dec_cfg->mcinit_cfg.mc_enable) {
    /* check how many cores support H264 */
    tmp = dec_cont->n_cores;
  }
  dec_cont->core_mask = 0;
  dec_cont->g1_core_mask = 0;
  dec_cont->g2_core_mask = 0;
  for(i = 0; i < dec_cont->n_cores; i++) {
    hw_build_id = DWLReadCoreHwBuildID(i);
    GetReleaseHwFeaturesByID(hw_build_id, &hw_feature);
    if (dec_cfg->mcinit_cfg.mc_enable) {
      if (!hw_feature->h264_support && !hw_feature->h264_adv_support)
        tmp--;
    }
    if(hw_feature->h264_support)
      dec_cont->g1_core_mask |= 1 << i;

    if(hw_feature->h264_high10_support)
      dec_cont->g2_core_mask |= 1 << i;

    if (dec_cont->h264_profile_support < hw_feature->h264_support)
      dec_cont->h264_profile_support = hw_feature->h264_support;
  }

  if (dec_cfg->mcinit_cfg.mc_enable) {
    dec_cont->n_cores_available = tmp;

    /* enable synchronization writing in multi-core HW */
    if(dec_cont->n_cores_available > 1) {
      dec_cont->b_mc = 1;
      dec_cont->stream_consumed_callback.fn = dec_cfg->mcinit_cfg.stream_consumed_callback;
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MULTICORE_E, 1);
      SetDecRegister(dec_cont->h264_regs, HWIF_DEC_WRITESTAT_E, 1);
    }
  }

  client_type = DWL_CLIENT_TYPE_H264_DEC << 16;
  dec_cont->g1_core_mask |= client_type;
  dec_cont->g2_core_mask |= client_type;

  *dec_inst = (H264DecInst) dec_cont;

  dec_cont->vcmd_used = DWLVcmdIsUsed();
  if (dec_cont->vcmd_used && dec_cont->b_mc) {
    /* Allows the maximum cmd buffers as real cores number. */
    FifoInit(dec_cont->n_cores_available, &dec_cont->fifo_core);
    for (i = 0; i < dec_cont->n_cores_available; i++) {
      FifoPush(dec_cont->fifo_core, (FifoObject)(addr_t)i, FIFO_EXCEPTION_DISABLE);
    }
  }

  //APITRACE("%s","H264DecInit# OK\n");

  return (DEC_OK);

err:
  pthread_mutex_destroy(&dec_cont->protect_mutex);
  pthread_mutex_destroy(&dec_cont->dmv_buffer_mutex);
  pthread_cond_destroy(&dec_cont->dmv_buffer_cv);
  if (dec_cont->pp_buffer_queue != NULL)
    InputQueueRelease(dec_cont->pp_buffer_queue);

  DWLfree(dec_cont);
  return ret;
}

/*------------------------------------------------------------------------------

    Function: H264DecGetInfo()

        Functional description:
            This function provides read access to decoder information. This
            function should not be called before H264DecDecode function has
            indicated that headers are ready.

        Inputs:
            dec_inst     decoder instance

        Outputs:
            dec_info    pointer to info struct where data is written

        Returns:
            DEC_OK            success
            DEC_PARAM_ERROR     invalid parameters
            DEC_HDRS_NOT_RDY  information not available yet

------------------------------------------------------------------------------*/
enum DecRet H264DecGetInfo(H264DecInst dec_inst, H264DecInfo * dec_info) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  u32 max_dpb_size,no_reorder;
  storage_t *storage;

  //APITRACE("%s","H264DecGetInfo#\n");

  if(dec_inst == NULL || dec_info == NULL) {
    APITRACEERR("%s","H264DecGetInfo# dec_inst or dec_info is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecGetInfo# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  storage = &dec_cont->storage;

  if(storage->active_sps == NULL || storage->active_pps == NULL) {
    APITRACEERR("%s","H264DecGetInfo# ERROR: Headers not decoded yet\n");
    return (DEC_HDRS_NOT_RDY);
  }

  /* h264bsdPicWidth and -Height return dimensions in macroblock units,
   * pic_width and -Height in pixels */
  dec_info->pic_width = h264bsdPicWidth(storage) << 4;
  dec_info->pic_height = h264bsdPicHeight(storage) << 4;

  dec_info->video_range = h264bsdVideoRange(storage);
  dec_info->matrix_coefficients = h264bsdMatrixCoefficients(storage);
  dec_info->colour_primaries = h264bsdColourPrimaries(storage);
  dec_info->transfer_characteristics = h264bsdTransferCharacteristics(storage);
  dec_info->colour_description_present_flag = h264bsdColourDescPresent(storage);
  dec_info->timing_info_present_flag = h264bsdTimingInfoPresent(storage);
  dec_info->num_units_in_tick = h264bsdNumUnitsInTick(storage);
  dec_info->time_scale = h264bsdTimeScale(storage);
  dec_info->pp_enabled = storage->pp_enabled;

  dec_info->mono_chrome = h264bsdIsMonoChrome(storage);
  dec_info->chroma_format_idc = h264bsdChromaFormatIdc(storage);
  dec_info->interlaced_sequence = storage->active_sps->frame_mbs_only_flag == 0 ? 1 : 0;
  if(storage->no_reordering ||
      storage->active_sps->pic_order_cnt_type == 2 ||
      (storage->active_sps->vui_parameters_present_flag &&
       storage->active_sps->vui_parameters->bitstream_restriction_flag &&
       !storage->active_sps->vui_parameters->num_reorder_frames))
    no_reorder = HANTRO_TRUE;
  else
    no_reorder = HANTRO_FALSE;
  if(storage->view == 0)
    max_dpb_size = storage->active_sps->max_dpb_size;
  else {
    /* stereo view dpb size at least equal to base view size (to make sure
     * that base view pictures get output in correct display order) */
    max_dpb_size = MAX(storage->active_sps->max_dpb_size,
                       storage->active_view_sps[0]->max_dpb_size);
  }
  /* restrict max dpb size of mvc (stereo high) streams, make sure that
   * base address 15 is available/restricted for inter view reference use */
  if(storage->mvc_stream)
    max_dpb_size = MIN(max_dpb_size, 8);
  if(no_reorder)
    dec_info->pic_buff_size = MAX(storage->active_sps->num_ref_frames,1) + 1;
  else
    dec_info->pic_buff_size = max_dpb_size + 1;

  if (dec_cont->skip_non_intra && !storage->mvc_stream) dec_info->pic_buff_size = 2;
  dec_info->multi_buff_pp_size =  storage->dpb->no_reordering? 2 : dec_info->pic_buff_size;
  dec_info->dpb_mode = dec_cont->dpb_mode;

  dec_info->bit_depth = (storage->active_sps->bit_depth_luma == 8 &&
                         storage->active_sps->bit_depth_chroma == 8) ? 8 : 10;

  if (storage->mvc)
    dec_info->multi_buff_pp_size *= 2;

  h264GetSarInfo(storage, &dec_info->sar_width, &dec_info->sar_height);

  h264bsdCroppingParams(storage, &dec_info->crop_params);

  if(dec_info->interlaced_sequence &&
      (dec_info->dpb_mode != DEC_DPB_INTERLACED_FIELD)) {
    if(dec_info->mono_chrome)
      dec_info->output_format = DEC_OUT_FRM_MONOCHROME;
    else
      dec_info->output_format = DEC_OUT_FRM_RASTER_SCAN;
  } else
    dec_info->output_format = DEC_OUT_FRM_TILED_4X4;


  dec_cont->ppb_mode = DEC_DPB_FRAME;

  //APITRACE("%s","H264DecGetInfo# OK\n");

  /* for interlace and baseline, using non-high10 mode */
  if (dec_cont->baseline_mode == 1)
    dec_info->base_mode = 1;
  else
    dec_info->base_mode = 0;

  return (DEC_OK);
}

void h264CheckBufferRealloc(struct H264DecContainer *dec_cont) {
  storage_t *storage = &dec_cont->storage;
  dpbStorage_t *dpb = storage->dpb;
  seqParamSet_t *p_sps = storage->active_sps;
  u32 is_high_supported = (dec_cont->h264_profile_support == H264_HIGH_PROFILE) ? 1 : 0;
  u32 is_high10_supported = dec_cont->high10p_mode;
  u32 n_cores = dec_cont->n_cores;
  u32 max_dpb_size = 0, new_pic_size = 0, new_tot_buffers = 0, dpb_size = 0, max_ref_frames = 0;
  u32 no_reorder = 0;
  struct dpbInitParams dpb_params;
  u32 rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 new_pic_size_in_mbs = 0;
  u32 new_pic_width_in_mbs = 0;
  u32 new_pic_height_in_mbs = 0;
  u32 out_w = 0, out_h = 0;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));
  u32 qp_mem_size = 0;

  if(dec_cont->b_mvc == 0) {
    new_pic_size_in_mbs = p_sps->pic_width_in_mbs * p_sps->pic_height_in_mbs;
    new_pic_width_in_mbs = p_sps->pic_width_in_mbs;
    new_pic_height_in_mbs = p_sps->pic_height_in_mbs;
  }
  else if(dec_cont->b_mvc == 1) {
    if(storage->sps[1] != 0) {
      new_pic_size_in_mbs = MAX(storage->sps[0]->pic_width_in_mbs * storage->sps[0]->pic_height_in_mbs,
                                storage->sps[1]->pic_width_in_mbs * storage->sps[1]->pic_height_in_mbs);
      new_pic_width_in_mbs = MAX(storage->sps[0]->pic_width_in_mbs, storage->sps[1]->pic_width_in_mbs);
      new_pic_height_in_mbs = MAX(storage->sps[0]->pic_height_in_mbs, storage->sps[1]->pic_height_in_mbs);
    }
    else {
      new_pic_size_in_mbs = storage->sps[0]->pic_width_in_mbs * storage->sps[0]->pic_height_in_mbs;
      new_pic_width_in_mbs = storage->sps[0]->pic_width_in_mbs;
      new_pic_height_in_mbs = storage->sps[0]->pic_height_in_mbs;
    }
  }

  if (storage->qp_output_enable)
    qp_mem_size = NEXT_MULTIPLE(p_sps->pic_width_in_mbs,  64) * p_sps->pic_height_in_mbs;
  else
    qp_mem_size = 0;

  /* dpb output reordering disabled if
   * 1) application set no_reordering flag
   * 2) POC type equal to 2
   * 3) num_reorder_frames in vui equal to 0 */
  if(storage->no_reordering ||
      p_sps->pic_order_cnt_type == 2 ||
      (p_sps->vui_parameters_present_flag &&
       p_sps->vui_parameters->bitstream_restriction_flag &&
       !p_sps->vui_parameters->num_reorder_frames))
    no_reorder = HANTRO_TRUE;
  else
    no_reorder = HANTRO_FALSE;

  if (storage->view == 0)
    max_dpb_size = p_sps->max_dpb_size;
  else {
    /* stereo view dpb size at least equal to base view size (to make sure
     * that base view pictures get output in correct display order) */
    max_dpb_size = MAX(p_sps->max_dpb_size, storage->active_view_sps[0]->max_dpb_size);
  }
  /* restrict max dpb size of mvc (stereo high) streams, make sure that
   * base address 15 is available/restricted for inter view reference use */
  if (storage->mvc_stream)
    max_dpb_size = MIN(max_dpb_size, 8);

  dpb_params.pic_size_in_mbs = new_pic_size_in_mbs;
  dpb_params.pic_width_in_mbs = new_pic_width_in_mbs;
  dpb_params.pic_height_in_mbs = new_pic_height_in_mbs;
  dpb_params.dpb_size = max_dpb_size;
  dpb_params.max_ref_frames = p_sps->num_ref_frames;
  if (dec_cont->skip_non_intra && !storage->mvc_stream) {
    dpb_params.dpb_size = 1;
    dpb_params.max_ref_frames = 1;
  }
  dpb_params.max_frame_num = p_sps->max_frame_num;
  dpb_params.no_reordering = no_reorder;
  dpb_params.display_smoothing = storage->use_smoothing;
  dpb_params.mono_chrome = p_sps->mono_chrome;
  dpb_params.chroma_format_idc = p_sps->chroma_format_idc;
  dpb_params.is_high_supported = is_high_supported;
  dpb_params.is_high10_supported = is_high10_supported;
  dpb_params.enable2nd_chroma = storage->enable2nd_chroma && !p_sps->mono_chrome;
  dpb_params.n_cores = n_cores;
  dpb_params.mvc_view = storage->view;
  dpb_params.pixel_width = (p_sps->bit_depth_luma == 8 &&
                            p_sps->bit_depth_chroma ==8) ? 8 : 10;


  H264GetRefFrmSize(storage, &rfc_luma_size, &rfc_chroma_size);
  dpb_params.tbl_sizey = NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align);
  dpb_params.tbl_sizec = NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);


  if (dpb_params.is_high_supported || dpb_params.is_high10_supported) {
    /* yuv picture + direct mode motion vectors */
    out_w = NEXT_MULTIPLE(4 * dpb_params.pic_width_in_mbs * 16 *
                          dpb_params.pixel_width / 8,
                          ALIGN(storage->align));
    out_h = dpb_params.pic_height_in_mbs * 4;
    if (dec_cont->skip_non_intra && dec_cont->pp_enabled)
      new_pic_size = 0;
    else {
      new_pic_size = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align) +
                      (dpb_params.mono_chrome ? 0 :
                      NEXT_MULTIPLE(out_w * out_h / 2, ref_buffer_align));
      new_pic_size += NEXT_MULTIPLE((dpb_params.pic_size_in_mbs + 32) *
                                    (dpb_params.is_high10_supported? 80 : 64), ref_buffer_align);

    }
    new_pic_size += NEXT_MULTIPLE(32, ref_buffer_align);
    /* compression table */
    new_pic_size += dpb_params.tbl_sizey + dpb_params.tbl_sizec;
  } else {
    out_w = NEXT_MULTIPLE(4 * dpb_params.pic_width_in_mbs * 16,
                          ALIGN(storage->align));
    out_h = dpb_params.pic_height_in_mbs * 4;
    if (dec_cont->skip_non_intra && dec_cont->pp_enabled)
      new_pic_size = 0;
    else
      new_pic_size = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                     + NEXT_MULTIPLE(out_w * out_h / 2, ref_buffer_align);
  }


  if (!dec_cont->pp_enabled)
    new_pic_size += qp_mem_size;

  dpb->n_new_pic_size = new_pic_size;
  max_ref_frames = MAX(dpb_params.max_ref_frames, 1);

  dpb_size = dpb_params.dpb_size;
  if(dpb_params.no_reordering)
    dpb_size = dec_cont->pp_enabled ? 1 : max_ref_frames;

  if (dec_cont->skip_non_intra && !storage->mvc_stream) dpb_size = 1;

  /* max DPB size is (16 + 1) buffers */
  new_tot_buffers = dpb_size + 1;

  /* figure out extra buffers for smoothing, pp, multicore, etc... */
  if (n_cores == 1) {
    /* single core configuration */
    if (storage->use_smoothing)
      new_tot_buffers += no_reorder ? 1 : dpb_size + 1;
  } else {
    /* multi core configuration */

    if (storage->use_smoothing && !no_reorder) {
      /* at least double buffers for smooth output */
      if (new_tot_buffers > n_cores) {
        new_tot_buffers *= 2;
      } else {
        new_tot_buffers += n_cores;
      }
    } else {
      /* one extra buffer for each core */
      /* do not allocate twice for multiview */
      if(!storage->view)
        new_tot_buffers += n_cores;
    }
  }

  storage->realloc_int_buf = 0;
  storage->realloc_ext_buf = 0;
  /* tile output */
  if (!dec_cont->pp_enabled) {
    if (dec_cont->use_adaptive_buffers) {
      /* Check if external buffer size is enouth */
      if (dpb->n_new_pic_size > dec_cont->n_ext_buf_size ||
          new_tot_buffers + dpb->n_guard_size > dec_cont->ext_buffer_num)
        storage->realloc_ext_buf = 1;
    }

    if (!dec_cont->use_adaptive_buffers) {
      /* use next_buf_size, beacase n_ext_buf_size has the align operation*/
      if (dpb->n_new_pic_size != dec_cont->next_buf_size ||
          new_tot_buffers > dec_cont->ext_buffer_num)
        storage->realloc_ext_buf = 1;
    }
    storage->realloc_int_buf = 0;

  } else { /* PP output*/
    u32 cur_ext_buff_size = CalcPpUnitBufferSize(dec_cont->ppu_cfg, 0) + qp_mem_size;
    if (dec_cont->use_adaptive_buffers) {
      if ((cur_ext_buff_size > dec_cont->n_ext_buf_size) ||
          (new_tot_buffers + dpb->n_guard_size > dec_cont->ext_buffer_num))
        storage->realloc_ext_buf = 1;
      if (dpb->n_new_pic_size > dpb->n_int_buf_size ||
          new_tot_buffers > dpb->tot_buffers)
        storage->realloc_int_buf = 1;
    }

    if (!dec_cont->use_adaptive_buffers) {
      /* use next_buf_size, beacase n_ext_buf_size has the align operation*/
      if ((cur_ext_buff_size != dec_cont->next_buf_size) ||
          (new_tot_buffers > dec_cont->ext_buffer_num))
        storage->realloc_ext_buf = 1;
      if (dpb->n_new_pic_size != dpb->n_int_buf_size ||
          new_tot_buffers > dpb->tot_buffers)
        storage->realloc_int_buf = 1;
    }
  }
}

/*------------------------------------------------------------------------------

    Function: H264DecRelease()

        Functional description:
            Release the decoder instance. Function calls h264bsdShutDown to
            release instance data and frees the memory allocated for the
            instance.

        Inputs:
            dec_inst     Decoder instance

        Outputs:
            none

        Returns:
            none

------------------------------------------------------------------------------*/

void H264DecRelease(H264DecInst dec_inst) {

  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  const void *dwl;
  u32 i;
  //APITRACE("%s","H264DecRelease#\n");

  if(dec_cont == NULL) {
    APITRACEERR("%s","H264DecRelease# dec_inst == NULL\n");
    return;
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecRelease# Decoder not initialized\n");
    return;
  }

  dwl = dec_cont->dwl;

  /* make sure all in sync in multicore mode, hw idle, output empty */
  if(dec_cont->b_mc) {
    h264MCWaitPicReadyAll(dec_cont);
  } else {
    u32 i;
    const dpbStorage_t *dpb = dec_cont->storage.dpb;

    /* Empty the output list. This is just so that fb_list does not
     * complaint about still referenced pictures
     */
    for(i = 0; i < dpb->tot_buffers; i++) {
      if(dpb->pic_buff_id[i] != FB_NOT_VALID_ID &&
        IsBufferOutput(&dec_cont->fb_list, dpb->pic_buff_id[i])) {
        ClearOutput(&dec_cont->fb_list, dpb->pic_buff_id[i]);
      }
    }
  }

  if(dec_cont->asic_running) {
    /* stop HW */
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 0);
    if (dec_cont->vcmd_used) {
      DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);
    }
    else {
      DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                   dec_cont->h264_regs[1] | DEC_IRQ_DISABLE);
      DWLReleaseHw(dwl, dec_cont->core_id);  /* release HW lock */
    }
    dec_cont->asic_running = 0;

    /* Decrement usage for DPB buffers */
    DecrementDPBRefCount(&dec_cont->storage.dpb[1]);
  } else if (dec_cont->keep_hw_reserved)
    DWLReleaseHw(dwl, dec_cont->core_id);  /* release HW lock */

#ifdef FPGA_PERF_AND_BW
  AveragePerfInfoPrint(&dec_cont->perf_info);
#endif

  /* TODO(atna): should it be enough to wait until all cores idle and
   *             not that output is empty !?
   */
#ifndef EXT_BUF_SAFE_RELEASE
  {
    int i;
    pthread_mutex_lock(&dec_cont->fb_list.ref_count_mutex);
    for (i = 0; i < MAX_PIC_BUFFERS; i++) {
      dec_cont->fb_list.fb_stat[i].n_ref_count = 0;
    }
    pthread_mutex_unlock(&dec_cont->fb_list.ref_count_mutex);
    if (dec_cont->pp_enabled)
      InputQueueReturnAllBuffer(dec_cont->pp_buffer_queue);
  }
#endif
#ifndef USE_OMXIL_BUFFER
#ifdef _HAVE_PTHREAD_H
  WaitListNotInUse(&dec_cont->fb_list);
#else
  int ret = 0;
  ret = WaitListNotInUse(&dec_cont->fb_list);
  (void)ret;
#endif
  if (dec_cont->pp_enabled)
    InputQueueWaitNotUsed(dec_cont->pp_buffer_queue);
#endif

  pthread_mutex_destroy(&dec_cont->protect_mutex);
  pthread_mutex_destroy(&dec_cont->dmv_buffer_mutex);
  /* CV to be signaled when a dmv buffer is consumed by Application */
  pthread_cond_destroy(&dec_cont->dmv_buffer_cv);

  h264bsdShutdown(&dec_cont->storage);

  h264bsdFreeDpb(
    dwl,
    dec_cont->storage.dpbs[0]);
  if (dec_cont->storage.dpbs[1]->dpb_size)
    h264bsdFreeDpb(
      dwl,
      dec_cont->storage.dpbs[1]);

  ReleaseAsicBuffers(dwl, dec_cont->asic_buff);
  if(dec_cont->llstrminfo.strm_status.virtual_address != NULL) {
    DWLFreeLinear(dwl, &dec_cont->llstrminfo.strm_status);
    dec_cont->llstrminfo.strm_status.virtual_address = NULL;
  }
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cont->ppu_cfg[i].lanczos_table.virtual_address) {
      DWLFreeLinear(dec_cont->dwl, &dec_cont->ppu_cfg[i].lanczos_table);
      dec_cont->ppu_cfg[i].lanczos_table.virtual_address = NULL;
    }
  }

  if (dec_cont->pp_buffer_queue) InputQueueRelease(dec_cont->pp_buffer_queue);

  if (dec_cont->vcmd_used && dec_cont->b_mc) {
    if (dec_cont->fifo_core)
      FifoRelease(dec_cont->fifo_core);
  }

  ReleaseList(&dec_cont->fb_list);
  dec_cont->checksum = NULL;
  DWLfree(dec_cont);
  //APITRACE("%s","H264DecRelease# OK\n");
  return;
}


/*------------------------------------------------------------------------------

    Function: H264DecDecode

        Functional description:
            Decode stream data. Calls h264bsdDecode to do the actual decoding.

        Input:
            dec_inst     decoder instance
            input      pointer to input struct

        Outputs:
            output     pointer to output struct

        Returns:
            DEC_NOT_INITIALIZED   decoder instance not initialized yet
            DEC_PARAM_ERROR         invalid parameters

            DEC_STRM_PROCESSED    stream buffer decoded
            DEC_HDRS_RDY    headers decoded, stream buffer not finished
            DEC_PIC_DECODED decoding of a picture finished
            DEC_STRM_ERROR  serious error in decoding, no valid parameter
                                sets available to decode picture data
            DEC_PENDING_FLUSH   next invocation of H264DecDecode() function
                                    flushed decoded picture buffer, application
                                    needs to read all output pictures (using
                                    H264DecNextPicture function) before calling
                                    H264DecDecode() again.

            DEC_HW_BUS_ERROR    decoder HW detected a bus error
            DEC_SYSTEM_ERROR    wait for hardware has failed
            DEC_MEMFAIL         decoder failed to allocate memory
            DEC_DWL_ERROR   System wrapper failed to initialize
            DEC_HW_TIMEOUT  HW timeout
            DEC_HW_RESERVED HW could not be reserved
------------------------------------------------------------------------------*/
enum DecRet H264DecDecode(H264DecInst dec_inst, const H264DecInput * input,
                         struct DecOutput * output) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  u32 strm_len;
  u32 input_data_len;  // used to generate error stream
  u8 *tmp_stream;
  enum DecRet return_value = DEC_STRM_PROCESSED;
  const struct DecHwFeatures *hw_feature = NULL;
  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);
  //APITRACE("%s","H264DecDecode#\n");
  /* Check that function input parameters are valid */
  if(input == NULL || output == NULL || dec_inst == NULL) {
    APITRACEERR("%s","H264DecDecode# NULL arg(s)\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecDecode# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  input_data_len = input->data_len;

  if(dec_cont->abort) {
    return (DEC_ABORTED);
  }

  if(input->data_len == 0 ||
      input->data_len > dec_cont->max_strm_len ||
      X170_CHECK_VIRTUAL_ADDRESS(input->stream) ||
      X170_CHECK_BUS_ADDRESS(input->stream_bus_address) ||
      X170_CHECK_VIRTUAL_ADDRESS(input->buffer) ||
      X170_CHECK_BUS_ADDRESS_AGLINED(input->buffer_bus_address)) {
    APITRACEERR("%s","H264DecDecode# Invalid arg value\n");
    return DEC_PARAM_ERROR;
  }

#ifdef DEC_EVALUATION
  if(dec_cont->pic_number > DEC_EVALUATION) {
    APITRACEERR("%s","H264DecDecode# FATAL DEC_EVALUATION_LIMIT_EXCEEDED\n");
    return DEC_EVALUATION_LIMIT_EXCEEDED;
  }
#endif

  dec_cont->stream_pos_updated = 0;
  output->strm_curr_pos = NULL;
  dec_cont->hw_stream_start_bus = input->stream_bus_address;
  dec_cont->p_hw_stream_start = (u8 *)input->stream;
  dec_cont->buff_start_bus = input->buffer_bus_address;
  dec_cont->hw_buffer = input->buffer;
  strm_len = dec_cont->hw_length = input_data_len;
  dec_cont->buff_length = input->buff_len;
  /* For low latency mode, strmLen is set as a large value */
  if(dec_cont->low_latency && !dec_cont->llstrminfo.stream_info.last_flag)
    strm_len = dec_cont->hw_length = input->buff_len;
  tmp_stream = (u8 *)input->stream;
  dec_cont->use_ringbuffer = ((input->stream + input_data_len) > (input->buffer + input->buff_len)) ? 1 : 0;
  dec_cont->stream_consumed_callback.p_strm_buff = input->stream;
  dec_cont->stream_consumed_callback.p_user_data = input->p_user_data;
  dec_cont->skip_frame = input->skip_frame;
  if(dec_cont->low_latency && dec_cont->use_ringbuffer){
    APITRACEERR("%s","H264DecDecode# DEC_STREAM_NOT_SUPPORTED, ringbuffer can't use in low latency mode.\n");
    return DEC_STREAM_NOT_SUPPORTED;
  }

  dec_cont->force_nal_mode = 0;

  /* If there are more buffers to be allocated or to be freed, waiting for buffers ready. */
  if (dec_cont->buf_to_free != NULL ||
      (dec_cont->next_buf_size != 0  && dec_cont->ext_buffer_num < dec_cont->buf_num)) {
    return_value = DEC_WAITING_FOR_BUFFER;
  }


  /* Switch to RLC mode, i.e. sw performs entropy decoding */
  if(dec_cont->reallocate) {
    if (!dec_cont->h264_profile_support) {
      output->strm_curr_pos = (u8 *)input->stream;
      output->strm_curr_bus_address = input->stream_bus_address;
      output->data_left = input->data_len;
      return DEC_STREAM_NOT_SUPPORTED;
    }
    APITRACE("%s",("H264DecDecode: Reallocate\n"));
    dec_cont->rlc_mode = 1;
    dec_cont->reallocate = 0;

    /* Reallocate only once */
    if(dec_cont->asic_buff->mb_ctrl.virtual_address == NULL) {
      if(h264AllocateResources(dec_cont) != 0) {
        /* signal that decoder failed to init parameter sets */
        dec_cont->storage.active_pps_id = MAX_NUM_PIC_PARAM_SETS;
        APITRACEERR("%s","H264DecDecode# Reallocation failed\n");
        return DEC_MEMFAIL;
      }

      h264bsdResetStorage(&dec_cont->storage);
    }

  }

  do {
    enum H264Result dec_result;
    u32 num_read_bytes = 0;
    storage_t *storage = &dec_cont->storage;
    storage->sei_buffer = input->sei_buffer; /**< SEI buffer */
    storage->align = dec_cont->align;

    APITRACEDEBUG("H264DecDecode: mode is %s\n",
                 dec_cont->rlc_mode ? "RLC" : "VLC");
    if(dec_cont->dec_stat == DEC_NEW_HEADERS) {
      dec_result = H264BSD_HDRS_RDY;
      dec_cont->dec_stat = DEC_INITIALIZED;
    } else if(dec_cont->dec_stat == DEC_BUFFER_EMPTY) {
      APITRACEDEBUG("%s","H264DecDecode: Skip h264bsdDecode\n");
      APITRACEDEBUG("%s","H264DecDecode: Jump to H264BSD_PIC_RDY\n");
      /* update stream pointers */
      strmData_t *strm = dec_cont->storage.strm;
      strm->p_strm_buff_start = input->buffer;
      strm->strm_curr_pos = tmp_stream;
      strm->strm_data_size = strm_len;
      strm->strm_buff_size = input->buff_len;
      strm->stream_info = &dec_cont->llstrminfo.stream_info;

      dec_result = H264BSD_PIC_RDY;
    }
    else if(dec_cont->dec_stat == DEC_WAIT_FOR_BUFFER) {
      dec_result = H264BSD_BUFFER_NOT_READY;
    } else {
      if (!dec_cont->no_decoding_buffer)
        dec_result = h264bsdDecode(dec_cont, tmp_stream, strm_len,
                                  input->pic_id, &num_read_bytes);

      /* "no_decoding_buffer" was set in previous loop, so do not
      enter h264bsdDecode() twice for the same slice */
      else {
        num_read_bytes = dec_cont->num_read_bytes;
        dec_result = dec_cont->dec_result;
      }

      if(dec_cont->storage.active_sps &&
        !dec_cont->storage.active_sps->frame_mbs_only_flag) {
        /* Only High10 progressive supported now. */
        dec_cont->high10p_mode = dec_cont->storage.high10p_mode = 0;
        dec_cont->use_video_compressor = 0;
        dec_cont->storage.use_video_compressor = 0;
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MODE, DEC_MODE_H264);
      }

      /* "alloc_buffer" is set in h264bsdDecode() to indicate if
         new output buffer is needed */

      /* no need to allocate buffer if H264BSD_RDY/H264BSD_SEI_PARSED...... returned */
      if (((dec_result == H264BSD_RDY ||
            dec_result == H264BSD_SEI_PARSED ||
            dec_result == H264BSD_PARAM_SET_PARSED ||
            dec_result == H264BSD_NO_REF ||
            dec_result == H264BSD_SEI_ERROR ||
            dec_result == H264BSD_PARAM_SET_ERROR ||
            dec_result == H264BSD_SLICE_HDR_ERROR ||
            dec_result == H264BSD_NONREF_PIC_SKIPPED ||
            dec_result == H264BSD_PB_PIC_SKIPPED ||
            dec_result == H264BSD_MEMFAIL ||
            dec_result == H264BSD_REF_PICS_ERROR ||
            dec_result == H264BSD_NALUNIT_ERROR ||
            dec_result == H264BSD_AU_BOUNDARY_ERROR ||
            dec_result == H264BSD_ERROR_DETECTED) &&
           !dec_cont->rlc_mode) &&
          (storage->active_pps && storage->active_pps->num_slice_groups == 1)) {
        dec_cont->alloc_buffer = 0;
      }
      /* when decode one pic, if stream error and need to re-allocate buffer, return the pp buffer*/
      if ((dec_cont->pp_enabled) && (dec_cont->alloc_buffer) && (storage->curr_image->data) &&
          (storage->dpb->current_out) && (storage->dpb->current_out->to_be_displayed == HANTRO_FALSE) &&
          (storage->dpb->current_out->status[0] == EMPTY && storage->dpb->current_out->status[1] == EMPTY) &&
           dec_cont->storage.dpb->current_out->ds_data != NULL &&
           InputQueueCheckBufUsed(dec_cont->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dec_cont->storage.dpb->current_out->ds_data)))) {
        dec_cont->alloc_buffer = 0;
      }
      if (dec_cont->alloc_buffer == 1) {
        storage->curr_image->data =
            h264bsdAllocateDpbImage(storage->dpb, input->pic_id);

        if (storage->curr_image->data == NULL) {
          if (dec_cont->abort)
            return DEC_ABORTED;
#ifdef GET_FREE_BUFFER_NON_BLOCK
          dec_cont->no_decoding_buffer = 1;
          dec_cont->dec_result = dec_result;
          dec_cont->num_read_bytes = num_read_bytes;
          dec_cont->stream_pos_updated = 0; /* not consume any input buffer */
          return_value = DEC_NO_DECODING_BUFFER;
          break;
#endif
        }
        storage->curr_image->pp_data = storage->dpb->current_out->ds_data;
        storage->curr_image->dmv_data = storage->dpb->current_out->dmv_data;
        storage->dpb->current_out->data = storage->curr_image->data;
        dec_cont->alloc_buffer = 0;
        dec_cont->pre_alloc_buffer[dec_cont->storage.view] = 1;
        dec_cont->no_decoding_buffer = 0;
      }

      /* In low latency mode or some error streams, numReadBytes may be greater than strmLen */
      if(num_read_bytes > strm_len || strm_len == DEC_X170_MAX_STREAM) {
        if (dec_cont->low_latency && dec_cont->llstrminfo.stream_info.last_flag) {
          strm_len = dec_cont->llstrminfo.stream_info.send_len;
        }
        if(num_read_bytes > strm_len)
          num_read_bytes = strm_len;
      }
      ASSERT(num_read_bytes <= strm_len);
      bsdDecodeReturn(dec_result);
    }

    /* when low latency mode error occur, input buffer should not be bigger than buffer len*/
    if (dec_cont->low_latency && ((num_read_bytes + tmp_stream - input->stream) > input->buff_len)) {
      return DEC_STRM_ERROR;
    }

    tmp_stream += num_read_bytes;
    if(tmp_stream >= dec_cont->hw_buffer + dec_cont->buff_length &&
       dec_cont->use_ringbuffer)
      tmp_stream -= dec_cont->buff_length;
    strm_len -= num_read_bytes;
    switch (dec_result) {
    case H264BSD_HDRS_RDY: {
      dec_cont->storage.dpb->b_updated = 0;
      dec_cont->storage.dpb->n_ext_buf_size_added = dec_cont->n_ext_buf_size;
      dec_cont->storage.dpb->use_adaptive_buffers = dec_cont->use_adaptive_buffers;
      dec_cont->storage.dpb->n_guard_size = dec_cont->n_guard_size;

      /* h264 422 intra only mode enable skip_non_intra feature */
      if (dec_cont->storage.active_sps &&
          dec_cont->storage.active_sps->chroma_format_idc == 2 &&
          dec_cont->h264_422_intra_support) {
        dec_cont->skip_non_intra = dec_cont->storage.skip_non_intra = 1;
      }

      /* intra only mode disable RFC and Reorder */
      if (dec_cont->skip_non_intra) {
        dec_cont->use_video_compressor = 0;
        dec_cont->storage.use_video_compressor = 0;
        H264DecSetNoReorder(dec_cont, 1);
      }

      if (dec_cont->storage.num_views &&
          dec_cont->storage.view == 0) {
        /* sps changes on base view */
        dec_cont->pic_number = 0;
      }

      /* reset decode mode for baseline and interlace, not change high10 profile */
      if (((dec_cont->support_asofmo_stream && h264StreamIsBaseline(dec_cont)) ||
           storage->active_sps->frame_mbs_only_flag == 0 ? 1 : 0) &&
          dec_cont->h264_profile_support &&
          dec_cont->storage.active_sps->bit_depth_chroma <= 8 &&
          dec_cont->storage.active_sps->bit_depth_luma <= 8) {
        dec_cont->baseline_mode = 1;
        dec_cont->high10p_mode = dec_cont->storage.high10p_mode = 0;
        dec_cont->use_video_compressor = 0;
        dec_cont->storage.use_video_compressor = 0;
	      /* g1 h264 not support ringbuffer */
	      if (dec_cont->use_ringbuffer) {
          return_value = DEC_STREAM_NOT_SUPPORTED;
          APITRACEERR("%s","H264DecDecode# ERROR: DEC_STREAM_NOT_SUPPORTED, ringbuffer can't use in g1 mode.\n");
	      }
        /* g1 h264 not support mc mode in HW */
        if (dec_cont->b_mc == 1) {
          dec_cont->b_mc = 0;
          dec_cont->n_cores = 1;
          dec_cont->n_cores_available = 0;
          dec_cont->stream_consumed_callback.fn = NULL;
          dec_cont->convert_to_single_core_mode = MC2SC_MODE;
          /* disable synchronization writing in multi-core HW */
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_MULTICORE_E, 0);
          SetDecRegister(dec_cont->h264_regs, HWIF_DEC_WRITESTAT_E, 0);
        }
        /* g1 h264 not support HW EC */
        if (dec_cont->hw_conceal) {
          if (dec_cont->error_handling == DEC_EC_FRAME_TOLERANT_ERROR) {
            dec_cont->error_policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_REPLACE | DEC_EC_NO_SKIP | DEC_EC_OUT_DECISION;
          } else if (dec_cont->error_handling == DEC_EC_FRAME_IGNORE_ERROR) {
            dec_cont->error_policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_REPLACE_ANYWAY | DEC_EC_NO_SKIP | DEC_EC_OUT_ALL;
          } else {
            /* do nothing. */
          }
          dec_cont->hw_conceal = 0;
        }
      }

      h264CheckReleasePpAndHw(dec_cont);

      if(storage->dpb->flushed && storage->dpb->num_out) {
        /* output first all DPB stored pictures */
        storage->dpb->flushed = 0;
        dec_cont->dec_stat = DEC_NEW_HEADERS;
        /* if display smoothing used -> indicate that all pictures
        * have to be read out */
        if(storage->dpb->tot_buffers >
            storage->dpb->dpb_size + 1) {
          return_value = DEC_PENDING_FLUSH;
        } else {
          return_value = DEC_STRM_PROCESSED;
        }

        /* base view -> flush another view dpb */
        if (dec_cont->storage.num_views &&
            dec_cont->storage.view == 0) {
          h264bsdFlushDpb(storage->dpbs[1]);
        }
        APITRACEDEBUG("%s","H264DecDecode# DEC_PIC_DECODED (DPB flush caused by new SPS)\n");
        strm_len = 0;

        break;
      } else if ((storage->dpb->tot_buffers >
                  storage->dpb->dpb_size + 1) && storage->dpb->num_out) {
        /* flush buffered output for display smoothing */
        storage->dpb->delayed_out = 0;
        storage->second_field = 0;
        dec_cont->dec_stat = DEC_NEW_HEADERS;
        return_value = DEC_PENDING_FLUSH;
        strm_len = 0;

        break;
      } else if (storage->pending_flush) {
        dec_cont->dec_stat = DEC_NEW_HEADERS;
        return_value = DEC_PENDING_FLUSH;
        strm_len = 0;

        if(dec_cont->b_mc) {
          h264MCWaitPicReadyAll(dec_cont);
        }
        if(dec_cont->convert_to_single_core_mode == MC2SC_MODE && dec_cont->vcmd_used) {
          h264MCWaitPicReadyAll(dec_cont);
          dec_cont->convert_to_single_core_mode = SC_MODE;
        }
#if 0
        int ret;
#ifdef _HAVE_PTHREAD_H
        WaitListNotInUse(&dec_cont->fb_list);
#else
        ret = WaitListNotInUse(&dec_cont->fb_list);
        if(ret) {
          strm_len = 0;
          dec_cont->dec_stat = DEC_NEW_HEADERS;
          return_value = DEC_PENDING_FLUSH;
          break;
        }
#endif
        if (dec_cont->pp_enabled) {
          ret = InputQueueWaitNotUsed(dec_cont->pp_buffer_queue);
          if (ret) {
            strm_len = 0;
            dec_cont->dec_stat = DEC_NEW_HEADERS;
            return_value = DEC_PENDING_FLUSH;
            break;
          }
        }
#endif
        h264bsdFlushDpb(storage->dpb);
        storage->pending_flush = 0;
        APITRACEDEBUG("%s","H264DecDecode# DEC_PIC_DECODED (DPB flush caused by new SPS)\n");

        break;
      }

#ifndef USE_OMXIL_BUFFER
      /* Make sure that all frame buffers are not in use before
      * reseting DPB (i.e. all HW cores are idle and all output
      * processed) */
      if(dec_cont->b_mc)
        h264MCWaitPicReadyAll(dec_cont);
      int ret;
#ifdef _HAVE_PTHREAD_H
      WaitListNotInUse(&dec_cont->fb_list);
#else
      ret = WaitListNotInUse(&dec_cont->fb_list);
      if(ret) {
        strm_len = 0;
        dec_cont->dec_stat = DEC_NEW_HEADERS;
        return_value = DEC_PENDING_FLUSH;
        break;
      }
#endif
      if (dec_cont->pp_enabled) {
        ret = InputQueueWaitNotUsed(dec_cont->pp_buffer_queue);
        if (ret) {
          strm_len = 0;
          dec_cont->dec_stat = DEC_NEW_HEADERS;
          //return_value = DEC_PENDING_FLUSH;
          break;
        }
      }
#endif

      if(!h264SpsSupported(dec_cont) ||
        (!h264StreamIsBaseline(dec_cont) && dec_cont->force_rlc_mode)) {
        storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
        storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
        storage->active_view_sps_id[0] =
          storage->active_view_sps_id[1] =
            MAX_NUM_SEQ_PARAM_SETS;
        storage->pic_started = HANTRO_FALSE;
        dec_cont->dec_stat = DEC_INITIALIZED;
        storage->prev_buf_not_finished = HANTRO_FALSE;
        output->data_left = 0;

        if(dec_cont->b_mc) {
          /* release buffer fully processed by SW */
          if(dec_cont->stream_consumed_callback.fn)
            dec_cont->stream_consumed_callback.fn((u8*)input->stream,
                                                  (void*)dec_cont->stream_consumed_callback.p_user_data);
        }

        APITRACEERR
        ("%s","H264DecDecode# DEC_STREAM_NOT_SUPPORTED\n");
        return DEC_STREAM_NOT_SUPPORTED;
      } else {
        dec_result = H264BSD_BUFFER_NOT_READY;
        dec_cont->dec_stat = DEC_WAIT_FOR_BUFFER;
        strm_len = 0;
        PushOutputPic(&dec_cont->fb_list, NULL, -2);
        /* new hdy need to clear the picture_broken, because the next slice should belong to I frame */
        dec_cont->storage.picture_broken = HANTRO_FALSE;
        return_value = DEC_HDRS_RDY;
      }

      if( !dec_cont->storage.active_sps->frame_mbs_only_flag)
        dec_cont->dpb_mode = DEC_DPB_INTERLACED_FIELD;
      else
        dec_cont->dpb_mode = DEC_DPB_FRAME;
      if (dec_cont->high10p_mode)
        dec_cont->core_mask = dec_cont->g2_core_mask;
      else
        dec_cont->core_mask = dec_cont->g1_core_mask;

      dec_cont->core_mask |= (dec_cont->secure_mode << 31);
      break;
    }
    case H264BSD_BUFFER_NOT_READY: {
      storage->align = dec_cont->align;

      h264CheckBufferRealloc(dec_cont);

      if (storage->realloc_ext_buf) {
        if(dec_cont->b_mvc == 0)
          h264SetExternalBufferInfo(dec_cont, storage);
        else if(dec_cont->b_mvc == 1)
          h264SetMVCExternalBufferInfo(dec_cont, storage);
      }

      if (dec_cont->pp_enabled) {
        dec_cont->prev_pp_width = dec_cont->ppu_cfg[0].scale.width;
        dec_cont->prev_pp_height = dec_cont->ppu_cfg[0].scale.height;
      }

      u32 ret = HANTRO_OK;
      if(dec_cont->b_mvc == 0)
        ret = h264bsdAllocateSwResources(dec_cont->dwl, storage,
                                         (dec_cont->
                                          h264_profile_support == H264_HIGH_PROFILE) ? 1 :
                                         0,
                                         dec_cont->high10p_mode,
                                         dec_cont->n_cores);
      else if(dec_cont->b_mvc == 1) {
        ret = h264bsdMVCAllocateSwResources(dec_cont->dwl, storage,
                                            (dec_cont->
                                             h264_profile_support == H264_HIGH_PROFILE) ? 1 :
                                            0,
                                            dec_cont->high10p_mode,
                                            dec_cont->n_cores);
        dec_cont->b_mvc = 2;
      }
      if (ret != HANTRO_OK) {
        goto RESOURCE_NOT_READY;
      }
      ret =  h264AllocateResources(dec_cont);
      if (ret != HANTRO_OK) goto RESOURCE_NOT_READY;

RESOURCE_NOT_READY:
      if(ret) {
        if(ret == DEC_WAITING_FOR_BUFFER) {
          dec_cont->buffer_index[0] = dec_cont->buffer_index[1] = 0;
          return_value = ret;
          strm_len = 0;
          break;
        } else {
          /* signal that decoder failed to init parameter sets */
          /* TODO: what about views? */
          storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
          storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;

          /* reset strm_len to force memfail return also for secondary
           * view */
          strm_len = 0;

          return_value = DEC_MEMFAIL;
          APITRACEERR("%s","H264DecDecode# ERROR: DEC_MEMFAIL\n");
        }
        strm_len = 0;
      } else {
        dec_cont->asic_buff->enable_dmv_and_poc = 0;
        storage->dpb->interlaced = (storage->active_sps->frame_mbs_only_flag == 0) ? 1 : 0;

        if((storage->active_pps->num_slice_groups != 1) &&
            (h264StreamIsBaseline(dec_cont) == 0)) {
          storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
          storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;

          return_value = DEC_STREAM_NOT_SUPPORTED;
          APITRACEERR("%s","H264DecDecode# ERROR: DEC_STREAM_NOT_SUPPORTED, FMO in Main/High Profile\n");
        } else if ((storage->active_pps->num_slice_groups != 1) && dec_cont->secure_mode) {
          storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
          storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
          return_value = DEC_STRM_ERROR;
          APITRACEERR("%s","H264DecDecode# ERROR: DEC_STREAM_ERROR, FMO in Secure Mode\n");
        } else if((storage->active_pps->num_slice_groups != 1) && (dec_cont->rlc_mode == 0)) {
          if (dec_cont->support_asofmo_stream) {
            /* FMO always decoded in rlc mode */
            /* set to uninit state */
            storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
            storage->active_view_sps_id[0] =
              storage->active_view_sps_id[1] =
                MAX_NUM_SEQ_PARAM_SETS;
            storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
            storage->pic_started = HANTRO_FALSE;
            dec_cont->dec_stat = DEC_INITIALIZED;
              dec_cont->rlc_mode = 1;

            storage->prev_buf_not_finished = HANTRO_FALSE;

            if (dec_cont->h264_profile_support) {
              return_value = DEC_ADVANCED_TOOLS;
              APITRACEDEBUG("%s","H264DecDecode# DEC_ADVANCED_TOOLS, FMO\n");
            } else {
              return_value = DEC_STREAM_NOT_SUPPORTED;
              APITRACEERR("%s","H264DecDecode# DON'T SUPPORT FMO\n");
            }
          } else {
            return_value = DEC_STREAM_NOT_SUPPORTED;
            APITRACEERR("%s","H264DecDecode# DON'T SUPPORT FMO\n");
          }
        } else {
          /* 1. enable direct MV writing and POC tables for high/main streams.
           * 2. enable it also for any "baseline" stream which have main/high tools enabled. */
          if((storage->active_sps->profile_idc > 66) ||
              (h264StreamIsBaseline(dec_cont) == 0) ||
             (dec_cont->b_mc && dec_cont->h264_profile_support != H264_BASELINE_PROFILE)) {
            dec_cont->asic_buff->enable_dmv_and_poc = 1;
          }
        }
      }

      if (!storage->view) {
        /* reset strm_len only for base view -> no HDRS_RDY to
         * application when param sets activated for stereo view */
        strm_len = 0;
        dec_cont->storage.second_field = 0;
      }

      /* Initialize DPB mode */
      if( !dec_cont->storage.active_sps->frame_mbs_only_flag)
        dec_cont->dpb_mode = DEC_DPB_INTERLACED_FIELD;
      else
        dec_cont->dpb_mode = DEC_DPB_FRAME;

      /* Initialize tiled mode */
      if(DecCheckTiledMode(
                             dec_cont->dpb_mode,
                             !dec_cont->storage.active_sps->frame_mbs_only_flag ) !=
          HANTRO_OK ) {
        return_value = DEC_PARAM_ERROR;
        APITRACEERR
        ("%s","H264DecDecode# ERROR: DEC_PARAM_ERROR, tiled reference "\
         "mode invalid\n");
      }

      /* reset reference addresses, this is important for multicore
       * as we use this list to track ref picture usage
       */
      DWLmemset(dec_cont->asic_buff->ref_pic_list, 0,
                sizeof(dec_cont->asic_buff->ref_pic_list));
      DWLmemset(dec_cont->asic_buff->ref_dmv_list, 0,
                sizeof(dec_cont->asic_buff->ref_dmv_list));
      dec_cont->dec_stat = DEC_INITIALIZED;
      break;
    }
    case H264BSD_PIC_RDY: {
      u32 i;
      u32 tmp;
      u32 asic_status;
      u32 picture_broken;
      u32 prev_irq_buffer = dec_cont->dec_stat == DEC_BUFFER_EMPTY; /* entry due to IRQ_BUFFER */
      DecAsicBuffers_t *p_asic_buff = dec_cont->asic_buff;
      dpbStorage_t *dpb = storage->dpb;
      dpbPicture_t *buffer = dpb->buffer;

      picture_broken = (storage->picture_broken &&
                        dec_cont->error_policy & DEC_EC_SEEK_NEXT_I &&
                        !IS_I_SLICE(storage->slice_header->slice_type));
      if (dec_cont->error_policy & DEC_EC_REF_REPLACE &&
          dec_cont->use_video_compressor &&
          !IS_IDR_NAL_UNIT(storage->prev_nal_unit) &&
          dec_cont->dec_stat != DEC_BUFFER_EMPTY) {
        /* need RFC enable: case which run in g1 core con't call this function */
        tmp = h264ReplaceRefAvalible(dec_cont);
        if (tmp == HANTRO_NOK) {
          /* not find avalible replace ref pic for error ref : SEEK NEXT I */
          picture_broken = HANTRO_TRUE;
          dec_cont->error_policy &= ~DEC_EC_NO_SKIP;
          dec_cont->error_policy |= DEC_EC_SEEK_NEXT_I;
        }
      }

      /* frame number workaround */
      if (!dec_cont->rlc_mode && dec_cont->workarounds.h264.frame_num &&
          !dec_cont->secure_mode) {
        u32 tmp;
        dec_cont->force_nal_mode =
          h264bsdFixFrameNum((u8*)tmp_stream - num_read_bytes,
                             strm_len + num_read_bytes,
                             storage->slice_header->frame_num,
                             storage->active_sps->max_frame_num, &tmp);

        /* stuff skipped before slice start code */
        if (dec_cont->force_nal_mode && tmp > 0) {
          dec_cont->p_hw_stream_start += tmp;
          dec_cont->hw_stream_start_bus += tmp;
          dec_cont->hw_length -= tmp;
        }
      }

      if( !(dec_cont->dec_stat == DEC_BUFFER_EMPTY) && !picture_broken) {
        /* check pps supported */
        if(!h264PpsSupported(dec_cont)) {
          storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
          storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;

          return_value = DEC_STREAM_NOT_SUPPORTED;
          APITRACEERR
          ("%s","H264DecDecode# DEC_STREAM_NOT_SUPPORTED, Main/High Profile tools detected\n");
          goto end;
        }

        /* I slice : reset dpb when DEC_EC_SEEK_NEXT_I enable */
        if (IS_I_SLICE(storage->slice_header->slice_type)) {
          dec_cont->error_info = DEC_NO_ERROR; /* the ERROR flag needs to be cleared. */
          if (storage->picture_broken && dec_cont->error_policy & DEC_EC_SEEK_NEXT_I) {
            /* error detected : I slice / I frame need reset DPB buffer */
            /* skipping pictures till next I slice, output all pictures
               in dpb and clear it, just like IDR. */
            (void)h264DpbMarkAllUnused(dpb);
            dpb->try_recover_dpb = HANTRO_FALSE;

            /* rollback DEC_EC_SEEK_NEXT_I to DEC_EC_NO_SKIP */
            if (dec_cont->error_policy & DEC_EC_REF_REPLACE &&
                dec_cont->use_video_compressor) {
              dec_cont->error_policy &= ~DEC_EC_SEEK_NEXT_I;
              dec_cont->error_policy |= DEC_EC_NO_SKIP;
            }
          }
        }

        /* setup the reference frame list; just at picture start */
        /* list in reorder */
        if(0 && (dec_cont->rlc_mode == 0)) {
          for(i = 0; i < dpb->dpb_size; i++) {
            p_asic_buff->ref_pic_list[i] =
              buffer[dpb->list[i]].data->bus_address;
            p_asic_buff->ref_dmv_list[i] = buffer[i].dmv_data ?
              buffer[dpb->list[i]].dmv_data->bus_address : 0;
          }
        } else {
          for(i = 0; i < dpb->dpb_size; i++) {
            p_asic_buff->ref_pic_list[i] =
              buffer[i].data->bus_address;
            p_asic_buff->ref_dmv_list[i] = buffer[i].dmv_data ?
              buffer[i].dmv_data->bus_address : 0;
          }
        }

        /* Multicore: increment usage for DPB buffers */
        IncrementDPBRefCount(dpb);

        p_asic_buff->max_ref_frm = dpb->max_ref_frames;
        p_asic_buff->out_buffer = storage->curr_image->data;
        p_asic_buff->out_pp_buffer = storage->curr_image->pp_data;
        p_asic_buff->out_dmv_buffer = storage->curr_image->dmv_data;

        p_asic_buff->chroma_qp_index_offset =
          storage->active_pps->chroma_qp_index_offset;
        p_asic_buff->chroma_qp_index_offset2 =
          storage->active_pps->chroma_qp_index_offset2;
        p_asic_buff->filter_disable = 0;

        h264bsdDecodePicOrderCnt(storage->poc,
                                 storage->active_sps,
                                 storage->slice_header,
                                 storage->prev_nal_unit);

#ifdef ENABLE_DPB_RECOVER
        if (IS_IDR_NAL_UNIT(storage->prev_nal_unit))
          storage->dpb->try_recover_dpb = HANTRO_FALSE;

        if (storage->dpb->try_recover_dpb
            /* && storage->slice_header->firstMbInSlice */
            && IS_I_SLICE(storage->slice_header->slice_type)
            && 2 * storage->dpb->max_ref_frames <= storage->dpb->max_frame_num)
          h264DpbRecover(storage->dpb, storage->slice_header->frame_num,
                         MIN(storage->poc->pic_order_cnt[0], storage->poc->pic_order_cnt[1]),
                         dec_cont->error_policy);
#endif
        if(dec_cont->rlc_mode) {
          if(storage->num_err_mbs == storage->pic_size_in_mbs) {
            p_asic_buff->whole_pic_concealed = 1;
            p_asic_buff->filter_disable = 1;
            p_asic_buff->chroma_qp_index_offset = 0;
            p_asic_buff->chroma_qp_index_offset2 = 0;
          } else {
            p_asic_buff->whole_pic_concealed = 0;
          }

          PrepareIntra4x4ModeData(storage, p_asic_buff);
          PrepareMvData(storage, p_asic_buff);
          PrepareRlcCount(storage, p_asic_buff);
        } else {
          H264SetupVlcRegs(dec_cont);
        }

        /* storage reference mem_idx for current pic */
        if (dec_cont->error_policy) {
          for (i = 0; i <= dpb->dpb_size; i++) {
            if (IS_REFERENCE_F(dpb->buffer[i])) {
              p_asic_buff->ref_mem_idx[i] = dpb->buffer[i].mem_idx;
            } else {
              p_asic_buff->ref_mem_idx[i] = DEC_DPB_INVALID_IDX;
            }
          }
        }

        APITRACEDEBUG("%s","Save DPB status\n");
        /* we trust our memcpy; ignore return value */
        (void) DWLmemcpy(&storage->dpb[1], &storage->dpb[0],
                         sizeof(*storage->dpb));

        APITRACEDEBUG("%s","Save POC status\n");
        (void) DWLmemcpy(&storage->poc[1], &storage->poc[0],
                         sizeof(*storage->poc));

        h264bsdCroppingParams(storage,
                              &storage->dpb->current_out->crop);

        /* prepare next frame ref status. */
        h264UpdateAfterPictureDecode(dec_cont);

        /* enable output writing by default */
        if (dec_cont->skip_non_intra &&
            dec_cont->pp_enabled)
          dec_cont->asic_buff->disable_out_writing = 1;
        else
          dec_cont->asic_buff->disable_out_writing = 0;
      } else {
        dec_cont->dec_stat = DEC_INITIALIZED;
      }

      /* disallow frame-mode DPB and tiled mode when decoding interlaced
       * content */
      if( dec_cont->dpb_mode == DEC_DPB_FRAME &&
          dec_cont->storage.active_sps &&
          !dec_cont->storage.active_sps->frame_mbs_only_flag &&
          dec_cont->tiled_reference_enable ) {
        APITRACEERR("%s"," ERROR: DPB mode does not support tiled reference "\
                    "pictures\n");
        return DEC_STRM_ERROR;
      }

      /* run asic and react to the status */
      if( !picture_broken ) {
        asic_status = H264RunAsic(dec_cont, p_asic_buff);
      } else {
        if( dec_cont->storage.pic_started ) {
          // if( !storage->slice_header->field_pic_flag ||
          //     !storage->second_field ) {
          //   h264UpdateAfterPictureDecode(dec_cont);
          // }
          h264UpdateAfterPictureDecode(dec_cont);
        }
        asic_status = DEC_HW_IRQ_ERROR;
      }

      // /* (EC): MVC case error test. */
      // if (dec_cont->storage.mvc == HANTRO_TRUE && input->pic_id == 3) {
      //   asic_status = DEC_HW_IRQ_ERROR;
      // }

      if (storage->view)
        storage->non_inter_view_ref = 0;

      /* Handle system error situations */
      if(asic_status == X170_DEC_TIMEOUT) {
        /* This timeout is DWL(software/os) generated */
        APITRACEERR
        ("%s","H264DecDecode# DEC_HW_TIMEOUT, SW generated\n");
        return DEC_HW_TIMEOUT;
      } else if(asic_status == X170_DEC_SYSTEM_ERROR) {
        APITRACEERR("%s","H264DecDecode# DEC_SYSTEM_ERROR\n");
        return DEC_SYSTEM_ERROR;
      } else if(asic_status == X170_DEC_FATAL_SYSTEM_ERROR) {
        APITRACEERR("%s","H264DecDecode# DEC_FATAL_SYSTEM_ERROR\n");
        return DEC_FATAL_SYSTEM_ERROR;
      } else if(asic_status == X170_DEC_HW_RESERVED) {
        APITRACE("%s","H264DecDecode# DEC_HW_RESERVED\n");
        return DEC_HW_RESERVED;
      }

      /* Handle possible common HW error situations */
      if(asic_status & DEC_HW_IRQ_BUS) {
        dec_cont->error_info = DEC_FRAME_ERROR;
        output->strm_curr_pos = (u8 *) input->stream;
        output->strm_curr_bus_address = input->stream_bus_address;
        if (dec_cont->llstrminfo.stream_info.low_latency) {
          while (!dec_cont->llstrminfo.stream_info.last_flag)
            sched_yield();
          input_data_len = dec_cont->llstrminfo.stream_info.send_len;
        }
        output->data_left = input_data_len;

        APITRACEERR("%s","H264DecDecode# DEC_HW_BUS_ERROR\n");
        return DEC_HW_BUS_ERROR;
      } else if (asic_status &  DEC_HW_IRQ_EXT_TIMEOUT) {
        dec_cont->error_info = DEC_FRAME_ERROR;
        return DEC_HW_EXT_TIMEOUT;
      }
      /* Handle stream error dedected in HW */
      else if((asic_status & DEC_HW_IRQ_TIMEOUT) ||
                (asic_status & DEC_HW_IRQ_ABORT)) {
        dec_cont->error_info = DEC_FRAME_ERROR;
        /* This timeout is HW generated */
        APITRACEERR("IRQ: HW %s\n", (asic_status & DEC_HW_IRQ_TIMEOUT) ? "TIMEOUT" : "ABORT");
#ifdef H264_TIMEOUT_ASSERT
        ASSERT(0);
#endif
        if(dec_cont->packet_decoded != HANTRO_TRUE) {
          APITRACEDEBUG("%s","reset pic_started\n");
          dec_cont->storage.pic_started = HANTRO_FALSE;
        }

#ifdef ENABLE_DPB_RECOVER
        dec_cont->storage.dpb->try_recover_dpb = HANTRO_TRUE;
#endif
        dec_cont->storage.picture_broken = HANTRO_TRUE;
        h264CorruptedProcess(dec_cont);

        if(!dec_cont->rlc_mode) {
          strmData_t *strm = dec_cont->storage.strm;
          strm->stream_info = &dec_cont->llstrminfo.stream_info;
          u32 next =
            H264NextStartCode(strm);

          if(next != END_OF_STREAM) {
            u32 consumed;

            tmp_stream -= num_read_bytes;
            if(tmp_stream < dec_cont->hw_buffer && dec_cont->use_ringbuffer)
              tmp_stream += dec_cont->buff_length;
            strm_len += num_read_bytes;

            if(strm->strm_curr_pos < tmp_stream && dec_cont->use_ringbuffer)
              consumed = (u32) (strm->strm_curr_pos - tmp_stream + dec_cont->buff_length);
            else
              consumed = (u32) (strm->strm_curr_pos - tmp_stream);
            tmp_stream += consumed;
            if(tmp_stream >= dec_cont->hw_buffer + dec_cont->buff_length &&
               dec_cont->use_ringbuffer)
              tmp_stream -= dec_cont->buff_length;
            strm_len -= consumed;
            if (picture_broken)
              dec_cont->hw_length -= consumed;
          }
        }

        dec_cont->stream_pos_updated = 0;
        dec_cont->pic_number++;

        dec_cont->packet_decoded = HANTRO_FALSE;
        storage->skip_redundant_slices = HANTRO_TRUE;

        /* Remove this NAL unit from stream */
        strm_len = 0;
        APITRACE("%s","H264DecDecode# DEC_PIC_DECODED\n");
        return_value = DEC_PIC_DECODED;
        break;
      }

      /* Handle RLC mode. */
      if(dec_cont->rlc_mode) {
        if (dec_cont->hw_conceal)
          dec_cont->error_info = GetDecRegister(dec_cont->h264_regs, HWIF_ERROR_INFO);
        else
          dec_cont->error_info = DEC_NO_ERROR;

        if(asic_status & DEC_HW_IRQ_ERROR) {
          dec_cont->error_info = DEC_FRAME_ERROR;
          APITRACEERR("%s","H264DecDecode# IRQ_STREAM_ERROR in RLC mode)!\n");
        }

        /* It was rlc mode, but switch back to vlc when allowed */
        if(dec_cont->try_vlc) {
          storage->prev_buf_not_finished = HANTRO_FALSE;
          APITRACEERR("%s","H264DecDecode: RLC mode used, but try VLC again\n");
          /* start using VLC mode again */
          dec_cont->rlc_mode = 0;
          dec_cont->try_vlc = 0;
          dec_cont->mode_change = 0;
        }
#ifdef CASE_INFO_STAT
        H264CaseInfoCollect(dec_cont, &case_info);
#endif
        h264CycleCount(dec_cont);
        h264SCMarkOutputPicInfo(dec_cont, picture_broken);
        dec_cont->pic_number++;
        storage->prev_idr_pic_ready = IS_IDR_NAL_UNIT(storage->prev_nal_unit);
        APITRACE("%s","H264DecDecode# DEC_PIC_DECODED\n");
        return_value = DEC_PIC_DECODED;
        strm_len = 0;
        break;
      }

      /* Handle VLC mode */
      /* in High/Main streams if HW model returns ASO interrupt, it
       * really means that there is a generic stream error. */
      if((asic_status & DEC_HW_IRQ_ASO) &&
          (p_asic_buff->enable_dmv_and_poc != 0 || h264StreamIsBaseline(dec_cont) == 0)) {
        dec_cont->error_info = DEC_FRAME_ERROR;
        APITRACEERR("%s","ASO received in High/Main stream => STREAM_ERROR\n");
        asic_status &= ~DEC_HW_IRQ_ASO;
        asic_status |= DEC_HW_IRQ_ERROR;
      }
      /* in Secure mode if HW model returns ASO interrupt, decoder treat
         it as error */
      if ((asic_status & DEC_HW_IRQ_ASO) && dec_cont->secure_mode) {
        dec_cont->error_info = DEC_FRAME_ERROR;
        APITRACEERR("%s","ASO received in secure mode => STREAM_ERROR\n");
        asic_status &= ~DEC_HW_IRQ_ASO;
        asic_status |= DEC_HW_IRQ_ERROR;
      }
      /* Handle ASO(only g1 support) */
      if (asic_status & DEC_HW_IRQ_ASO) {
        if (dec_cont->support_asofmo_stream) {
          APITRACEDEBUG("%s","IRQ: ASO detected\n");
          ASSERT(dec_cont->rlc_mode == 0);

          dec_cont->reallocate = 1;
          dec_cont->try_vlc = 1;
          dec_cont->mode_change = 1;

#ifdef CASE_INFO_STAT
        H264CaseInfoCollect(dec_cont, &case_info);
#endif
          /* restore DPB status */
          APITRACEDEBUG("%s","Restore DPB status\n");

          /* remove any pictures marked for output */
          if (storage->dpb[0].num_out >= storage->dpb[1].num_out)
            h264RemoveNoBumpOutput(&storage->dpb[0], &storage->dpb[1]);
          else {
            /*this is must call the h264bsdMarkDecRefPic and find it is IDR, and clean the buffer*/
            storage->dpb[1].num_out = 0;
            storage->dpb[1].out_index_w = storage->dpb[1].out_index_r = 0;
          }
          /* we trust our memcpy; ignore return value */
          (void) DWLmemcpy(&storage->dpb[0], &storage->dpb[1],
                          sizeof(dpbStorage_t));
          APITRACEDEBUG("%s","Restore POC status\n");
          (void) DWLmemcpy(&storage->poc[0], &storage->poc[1],
                          sizeof(*storage->poc));

          storage->skip_redundant_slices = HANTRO_FALSE;
          storage->aso_detected = 1;

          if (dec_cont->h264_profile_support) {
            return_value = DEC_ADVANCED_TOOLS;
            APITRACEDEBUG("%s","H264DecDecode# DEC_ADVANCED_TOOLS, ASO\n");
          } else {
            return_value = DEC_STREAM_NOT_SUPPORTED;
            APITRACEERR("%s","H264DecDecode# DON'T SUPPORT ASO\n");
          }
          goto end;
        } else {
          return_value = DEC_STREAM_NOT_SUPPORTED;
          APITRACEERR("%s","H264DecDecode# DON'T SUPPORT ASO\n");
          goto end;
        }
      }

      if (asic_status & DEC_HW_IRQ_BUFFER) {
        APITRACEDEBUG("%s","IRQ: BUFFER EMPTY\n");

#ifdef CASE_INFO_STAT
        if(case_info.frame_num < 10)
        case_info.slice_num[case_info.frame_num]++;
#endif
        /* Check for CABAC zero words here */
        if ( dec_cont->storage.active_pps->entropy_coding_mode_flag &&
             !dec_cont->secure_mode) {
          u32 tmp;
          u32 check_words = 1;
          strmData_t strm_tmp = *dec_cont->storage.strm;
          tmp = dec_cont->p_hw_stream_start - strm_tmp.p_strm_buff_start;
          strm_tmp.strm_curr_pos = dec_cont->p_hw_stream_start;
          strm_tmp.strm_buff_read_bits = 8*tmp;
          strm_tmp.bit_pos_in_word = 0;
          strm_tmp.stream_info = &dec_cont->llstrminfo.stream_info;
          if (dec_cont->low_latency) {
            while (!dec_cont->llstrminfo.stream_info.last_flag)
              sched_yield();
            input_data_len = dec_cont->llstrminfo.stream_info.send_len;
          }
          strm_tmp.strm_data_size = input_data_len -
                                    (strm_tmp.p_strm_buff_start - input->stream);

          tmp = GetDecRegister(dec_cont->h264_regs, HWIF_START_CODE_E);
          /* In NAL unit mode, if NAL unit was of type
           * "reserved" or sth other unsupported one, we need
           * to skip zero word check. */
          if( tmp == 0 ) {
            tmp = SwLowLatencyReadByte(input->stream, strm_tmp.strm_data_size, strm_tmp.stream_info) & 0x1F;
            if( tmp != NAL_CODED_SLICE &&
                tmp != NAL_CODED_SLICE_IDR )
              check_words = 0;
          }

          if(check_words) {
            tmp = h264CheckCabacZeroWords( &strm_tmp );
            if( tmp != HANTRO_OK ) {
              APITRACEERR("%s","CABAC_ZERO_WORD error after packet => STREAM_ERROR\n");
            } /* cabacZeroWordError */
          }
        }

        /* a packet successfully decoded, don't reset pic_started flag if
         * there is a need for rlc mode */
        dec_cont->dec_stat = DEC_BUFFER_EMPTY;
        dec_cont->packet_decoded = HANTRO_TRUE;
        output->data_left = 0;
        APITRACE("%s","H264DecDecode# DEC_STRM_PROCESSED, give more data\n");
        return DEC_BUF_EMPTY;
      } else if(asic_status & DEC_HW_IRQ_ERROR) {
        /* Handle stream error detected in HW */
        dec_cont->error_info = DEC_FRAME_ERROR;
        APITRACEERR("%s",("IRQ: STREAM ERROR detected\n"));
        if(dec_cont->packet_decoded != HANTRO_TRUE) {
          APITRACEDEBUG("%s","reset pic_started\n");
          dec_cont->storage.pic_started = HANTRO_FALSE;
        }

        strmData_t *strm = dec_cont->storage.strm;

        strm->stream_info = &dec_cont->llstrminfo.stream_info;
        if (prev_irq_buffer) {
          /* Call H264DecDecode() due to DEC_HW_IRQ_ERROR,
             reset strm to input buffer. */
          strm->p_strm_buff_start = input->buffer;
          strm->strm_curr_pos = input->stream;
          strm->strm_buff_size = input->buff_len;
          if (dec_cont->low_latency && dec_cont->llstrminfo.stream_info.last_flag)
            input_data_len = dec_cont->llstrminfo.stream_info.send_len;
          strm->strm_data_size = input_data_len;
          strm->strm_buff_read_bits = (u32)(strm->strm_curr_pos - strm->p_strm_buff_start) * 8;
          strm->is_rb = dec_cont->use_ringbuffer;;
          strm->remove_emul3_byte = 0;
          strm->bit_pos_in_word = 0;
        }

        u32 next =
          H264NextStartCode(strm);

        if(next == HANTRO_OK) {
          u32 consumed;

          tmp_stream -= num_read_bytes;
          if(tmp_stream < dec_cont->hw_buffer && dec_cont->use_ringbuffer)
            tmp_stream += dec_cont->buff_length;
          strm_len += num_read_bytes;

          if(strm->strm_curr_pos < tmp_stream)
            consumed = (u32) (strm->strm_curr_pos + strm->strm_buff_size - tmp_stream);
          else
            consumed = (u32) (strm->strm_curr_pos - tmp_stream);

          tmp_stream += consumed;
          if(tmp_stream >= dec_cont->hw_buffer + dec_cont->buff_length &&
             dec_cont->use_ringbuffer)
            tmp_stream -= dec_cont->buff_length;
          strm_len -= consumed;
          if (picture_broken)
            dec_cont->hw_length -= consumed;
        }

        /* REMEMBER TO UPDATE(RESET) STREAM POSITIONS */
        ASSERT(dec_cont->rlc_mode == 0);

        dec_cont->storage.picture_broken = HANTRO_TRUE;
        h264CorruptedProcess(dec_cont);

        /* HW returned stream position is not valid in this case */
        dec_cont->stream_pos_updated = 0;
      } else { /* OK in here */
        if (dec_cont->hw_conceal)
          dec_cont->error_info = GetDecRegister(dec_cont->h264_regs, HWIF_ERROR_INFO);
        else
          dec_cont->error_info = DEC_NO_ERROR;

        if(IS_IDR_NAL_UNIT(storage->prev_nal_unit) || dec_cont->error_policy & DEC_EC_NO_SKIP ||
           IS_I_SLICE(storage->slice_header->slice_type)) {
          dec_cont->storage.picture_broken = HANTRO_FALSE;
        }
#ifdef CASE_INFO_STAT
        H264CaseInfoCollect(dec_cont, &case_info);
#endif
      }

      if (dec_cont->storage.active_pps->entropy_coding_mode_flag &&
          ((asic_status & DEC_HW_IRQ_ERROR) == 0) &&
          !dec_cont->b_mc &&
          !dec_cont->secure_mode) {
        u32 tmp;

        strmData_t strm_tmp = *dec_cont->storage.strm;
        /* dec_cont->p_hw_stream_start indicates the current consumed stream place */
        if(dec_cont->p_hw_stream_start <= input->stream)  /* need to consider turnaround */
          tmp = dec_cont->buff_length - (input->stream - dec_cont->p_hw_stream_start);
        else
          tmp = dec_cont->p_hw_stream_start - input->stream;
        strm_tmp.strm_curr_pos = dec_cont->p_hw_stream_start;
        strm_tmp.strm_buff_read_bits = 8*tmp;
        strm_tmp.bit_pos_in_word = 0;
        strm_tmp.stream_info = &dec_cont->llstrminfo.stream_info;
        if (dec_cont->low_latency) {
          while (!dec_cont->llstrminfo.stream_info.last_flag)
            sched_yield();
          strm_len = dec_cont->llstrminfo.stream_info.send_len;
          /* correct input_data_len to avoid inaccurate send_len */
          if (dec_cont->llstrminfo.stream_info.strm_bus_addr <= input->stream_bus_address)
            input_data_len = dec_cont->buff_length - (input->stream_bus_address -
                             dec_cont->llstrminfo.stream_info.strm_bus_addr);
          else
            input_data_len = dec_cont->llstrminfo.stream_info.strm_bus_addr - input->stream_bus_address;
        }
        strm_tmp.strm_data_size = input_data_len;

        /* In low latency mode, do not use input_data_len to compute buffer size */
        //  strm_tmp.strm_buff_size = (stream_info.strm_bus_addr - stream_info.strm_bus_start_addr) -
        //      (strm_tmp.p_strm_buff_start - input->stream);
        tmp = h264CheckCabacZeroWords( &strm_tmp );
        if( tmp != HANTRO_OK ) {
          APITRACEERR("%s","Error decoding CABAC zero words\n");
          {
            strmData_t *strm = dec_cont->storage.strm;
            u32 next =
              H264NextStartCode(strm);

            if(next != END_OF_STREAM) {
              u32 consumed;

              tmp_stream -= num_read_bytes;
              if(tmp_stream < dec_cont->hw_buffer && dec_cont->use_ringbuffer)
                tmp_stream += dec_cont->buff_length;
              strm_len += num_read_bytes;
              if(strm->strm_curr_pos < tmp_stream && dec_cont->use_ringbuffer)
                consumed = (u32) (strm->strm_curr_pos - tmp_stream + dec_cont->buff_length);
              else
                consumed = (u32) (strm->strm_curr_pos - tmp_stream);
              tmp_stream += consumed;
              if(tmp_stream >= dec_cont->hw_buffer + input->buff_len &&
                 dec_cont->use_ringbuffer)
                tmp_stream -= dec_cont->buff_length;
              strm_len -= consumed;
              if (picture_broken)
                dec_cont->hw_length -= consumed;
            }
          }

          ASSERT(dec_cont->rlc_mode == 0);
        } else {
          /* buffer_consumed_bytes including bytes cosumed by sw and hw */
          i32 remain = 0, buffer_consumed_bytes = 0;
          if(strm_tmp.strm_curr_pos <= input->stream)  { /* need to concern input buffer around back */
            buffer_consumed_bytes = dec_cont->buff_length - (input->stream - strm_tmp.strm_curr_pos);
          }
          else
            buffer_consumed_bytes = strm_tmp.strm_curr_pos - input->stream;
          remain = input_data_len - buffer_consumed_bytes;
          /* byte stream format if starts with 0x000001 or 0x000000 */
          if (remain > 3 && (h264bsdShowBits(&strm_tmp, 24) == 0x000000 ||
              h264bsdShowBits(&strm_tmp, 24) == 0x000001)) {
            u32 next =
                H264NextStartCode(&strm_tmp);

            u32 consumed;
            if(next != END_OF_STREAM)
              if(strm_tmp.strm_curr_pos < input->stream && dec_cont->use_ringbuffer)
                consumed = (u32) (strm_tmp.strm_curr_pos - input->stream +
                                  dec_cont->buff_length);
              else
                consumed = (u32) (strm_tmp.strm_curr_pos - input->stream);
            else
              consumed = input_data_len;

            if(consumed != 0) {
              dec_cont->stream_pos_updated = 0;
              tmp_stream = (u8 *)input->stream + consumed;
              if(tmp_stream >= dec_cont->hw_buffer + dec_cont->buff_length &&
                 dec_cont->use_ringbuffer)
                tmp_stream -= dec_cont->buff_length;
            }
          }
        }
      }

      if (dec_cont->b_mc) {
        tmp_stream = (u8 *)input->stream + input_data_len;
        strm_len = 0;
        dec_cont->stream_pos_updated = 0;
      }

      /* For the switch between modes */
      /* this is a sign for RLC mode + mb error conceal NOT to reset pic_started flag */
      dec_cont->packet_decoded = HANTRO_FALSE;

      //if (!picture_broken) {
        APITRACEDEBUG("%s","Skip redundant VLC\n");
        storage->skip_redundant_slices = HANTRO_TRUE;
        dec_cont->pic_number++;
        h264CycleCount(dec_cont);
        h264SCMarkOutputPicInfo(dec_cont, picture_broken);
        storage->prev_idr_pic_ready = IS_IDR_NAL_UNIT(storage->prev_nal_unit);
        APITRACE("%s","H264DecDecode# DEC_PIC_DECODED\n");
        return_value = DEC_PIC_DECODED;
        strm_len = 0;
      //}
      break;
    }
    case H264BSD_PARAM_SET_ERROR: {
      if(h264bsdCheckValidParamSets(&dec_cont->storage) == HANTRO_NOK && strm_len == 0) {
        APITRACEERR("%s","H264DecDecode# DEC_STRM_ERROR, Invalid parameter set(s)\n");
        return_value = DEC_PARAM_SET_ERROR;
      }

      /* update HW buffers if VLC mode */
      if(!dec_cont->rlc_mode) {
        dec_cont->hw_length -= num_read_bytes;
        dec_cont->p_hw_stream_start = tmp_stream;
        if(tmp_stream >= input->stream) {
           dec_cont->hw_stream_start_bus =
          input->stream_bus_address + (u32)(tmp_stream - input->stream);
        } else {
          dec_cont->hw_stream_start_bus =
            input->buffer_bus_address + (u32)(tmp_stream - input->buffer);
        }
      }

      /* If no active sps, no need to check */
      if(storage->active_sps && !h264SpsSupported(dec_cont)) {
        storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
        storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
        storage->active_view_sps_id[0] =
          storage->active_view_sps_id[1] =
            MAX_NUM_SEQ_PARAM_SETS;
        storage->pic_started = HANTRO_FALSE;
        dec_cont->dec_stat = DEC_INITIALIZED;
        storage->prev_buf_not_finished = HANTRO_FALSE;

        if(dec_cont->b_mc) {
          /* release buffer fully processed by SW */
          if(dec_cont->stream_consumed_callback.fn)
            dec_cont->stream_consumed_callback.fn((u8*)input->stream,
                                                  (void*)dec_cont->stream_consumed_callback.p_user_data);
        }
        APITRACEERR("%s","H264DecDecode# DEC_STREAM_NOT_SUPPORTED\n");
        return_value = DEC_STREAM_NOT_SUPPORTED;
        goto end;
      }

      return_value = DEC_PARAM_SET_ERROR;
      if (dec_cont->storage.dpb->current_out)
        SET_SEI_UNUSED(dec_cont->storage.dpb->current_out->sei_param);
      break;
    }
    case H264BSD_NEW_ACCESS_UNIT: {
      h264CheckReleasePpAndHw(dec_cont);

      dec_cont->stream_pos_updated = 0;
      dec_cont->storage.picture_broken = HANTRO_TRUE;

      // H264DropCurrentPicutre(dec_cont);
      h264CorruptedProcess(dec_cont);
      h264UpdateAfterPictureDecode(dec_cont);
      /* make sure that output pic sync memory is cleared */
      if (dec_cont->b_mc) {
#ifndef MEM_ONLY_DEV_CHECK
        char *sync_base;
        if (dec_cont->high10p_mode)
          sync_base = (char *) (dec_cont->storage.dpb->current_out->dmv_data->virtual_address) - 32;
        else
          sync_base = (char *) (dec_cont->storage.dpb->current_out->dmv_data->virtual_address) + dec_cont->storage.dmv_mem_size;
        u32 sync_size = 16; /* 16 bytes for each field */
        if (!dec_cont->storage.slice_header->field_pic_flag) {
          sync_size += 16; /* reset all 32 bytes */
        } else if (dec_cont->storage.slice_header->bottom_field_flag) {
          sync_base += 16; /* bottom field sync area*/
        }

        (void) DWLmemset(sync_base, 0xF, sync_size);
#endif
#ifdef SUPPORT_DMA
        if (dec_cont->high10p_mode)
          DWLDMATransData((addr_t)((u8*)dec_cont->asic_buff->out_dmv_buffer->bus_address - 32),
                          (void *)((u8*)dec_cont->asic_buff->out_dmv_buffer->virtual_address - 32),
                          32, HOST_TO_DEVICE);
        else
          DWLDMATransData((addr_t)((u8*)dec_cont->asic_buff->out_dmv_buffer->bus_address + dec_cont->storage.dmv_mem_size),
                          (void *)((u8*)dec_cont->asic_buff->out_dmv_buffer->virtual_address + dec_cont->storage.dmv_mem_size),
                          32, HOST_TO_DEVICE);
#endif
      }
      if(dec_cont->pp_enabled && dec_cont->storage.dpb->current_out) {
        InputQueueReturnBuffer(dec_cont->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dec_cont->storage.dpb->current_out->ds_data)));
        SET_SEI_UNUSED(dec_cont->storage.dpb->current_out->sei_param);
      }
      H264ReturnDMVBuffer(dec_cont->storage.dpb,
          dec_cont->storage.dpb->current_out->dmv_data->bus_address);

      /* PP will run in H264DecNextPicture() for this concealed picture */

      if (dec_cont->storage.current_marked &&
          dec_cont->storage.dpb->delayed_out == 0 &&
          dec_cont->storage.dpb->no_reordering) {
        dec_cont->storage.dpb->num_out--;
        if (dec_cont->storage.dpb->out_index_w == 0)
          dec_cont->storage.dpb->out_index_w = MAX_DPB_SIZE;
        else
          dec_cont->storage.dpb->out_index_w--;
        ClearOutput(dec_cont->storage.dpb->fb_list, dec_cont->storage.dpb->current_out->mem_idx);
        }

      APITRACE("%s","H264DecDecode# DEC_PIC_DECODED, NEW_ACCESS_UNIT\n");
      return_value = DEC_PIC_DECODED;

      // dec_cont->pic_number++;
      strm_len = 0;

      break;
    }
    case H264BSD_FMO: { /* If picture parameter set changed and FMO detected */
      if (dec_cont->support_asofmo_stream) {
        APITRACEDEBUG("%s","FMO detected\n");
        ASSERT(dec_cont->rlc_mode == 0);
        ASSERT(dec_cont->reallocate == 1);

        if (dec_cont->h264_profile_support) {
          return_value = DEC_ADVANCED_TOOLS;
          APITRACEDEBUG("%s","H264DecDecode# DEC_ADVANCED_TOOLS, FMO\n");
        } else {
          return_value = DEC_STREAM_NOT_SUPPORTED;
          APITRACEERR("%s","H264DecDecode# DON'T SUPPORT FMO\n");
        }

        strm_len = 0;
        break;
      } else {
        return_value = DEC_STREAM_NOT_SUPPORTED;
        APITRACEERR("%s","H264DecDecode# DON'T SUPPORT FMO\n");
        goto end;
      }
    }
    case H264BSD_UNPAIRED_FIELD: {
      /* unpaired field detected and PP still running (wait after
       * second field decoded) -> wait here */
      h264CheckReleasePpAndHw(dec_cont);

      APITRACEDEBUG("%s","H264DecDecode# DEC_PIC_DECODED, UNPAIRED_FIELD\n");
      return_value = DEC_PIC_DECODED;

      strm_len = 0;
      break;
    }
    case H264BSD_ABORTED: {
      dec_cont->dec_stat = DEC_ABORTED;
      return DEC_ABORTED;
    }
    case H264BSD_ERROR_DETECTED: {
      return_value = DEC_STREAM_ERROR_DEDECTED;
      strm_len = 0;
      if (dec_cont->storage.dpb->current_out)
        SET_SEI_UNUSED(dec_cont->storage.dpb->current_out->sei_param);
      break;
    }
    case H264BSD_NO_FREE_BUFFER: {
      tmp_stream = (u8 *)input->stream;
      strm_len = 0;
      H264UpdateSeiInfo(storage->sei_buffer, storage->sei_param_curr);
      return_value = DEC_NO_DECODING_BUFFER;
      break;
    }
    case H264BSD_MEMFAIL: {
      /* make sure all in sync in multicore mode, hw idle, output empty */
      if(dec_cont->b_mc)
        h264MCWaitPicReadyAll(dec_cont);
      return_value = DEC_MEMFAIL;
      goto end;
    }
    case H264BSD_RDY:
    case H264BSD_NONREF_PIC_SKIPPED:
    case H264BSD_PB_PIC_SKIPPED:
    case H264BSD_NO_REF:
    case H264BSD_PARAM_SET_PARSED:
    case H264BSD_SEI_PARSED:
    case H264BSD_SEI_ERROR:
    case H264BSD_SLICE_HDR_ERROR:
    case H264BSD_REF_PICS_ERROR:
    case H264BSD_NALUNIT_ERROR:
    case H264BSD_AU_BOUNDARY_ERROR:
    /* fall through */
    default: {
      /* update HW buffers */
      dec_cont->hw_length -= num_read_bytes;
      dec_cont->p_hw_stream_start = tmp_stream;
      if(tmp_stream >= input->stream) {
        dec_cont->hw_stream_start_bus =
          input->stream_bus_address + (u32)(tmp_stream - input->stream);
      } else {
        dec_cont->hw_stream_start_bus =
          input->buffer_bus_address + (u32)(tmp_stream - input->buffer);
      }
    }
      /* set return_value by dec_result */
    if (dec_result == H264BSD_RDY) return_value = DEC_STRM_PROCESSED;
    if (dec_result == H264BSD_NONREF_PIC_SKIPPED) return_value = DEC_NONREF_PIC_SKIPPED;
    if (dec_result == H264BSD_PB_PIC_SKIPPED) return_value = DEC_PB_PIC_SKIPPED;
    if (dec_result == H264BSD_NO_REF) return_value = DEC_NO_REFERENCE;
    if (dec_result == H264BSD_PARAM_SET_PARSED) return_value = DEC_PARAM_SET_PARSED;
    if (dec_result == H264BSD_SEI_PARSED) return_value = DEC_SEI_PARSED;
    if (dec_result == H264BSD_SEI_ERROR)return_value = DEC_SEI_ERROR;
    if (dec_result == H264BSD_SLICE_HDR_ERROR) return_value = DEC_SLICE_HDR_ERROR;
    if (dec_result == H264BSD_REF_PICS_ERROR) return_value = DEC_REF_PICS_ERROR;
    if (dec_result == H264BSD_NALUNIT_ERROR) return_value = DEC_NALUNIT_ERROR;
    if (dec_result == H264BSD_AU_BOUNDARY_ERROR) return_value = DEC_AU_BOUNDARY_ERROR;
    /* SW error detected */
    if (dec_result < 0) {
#ifdef SUPPORT_GDR
      /* SW consumed data of one frame: recovery_frame_cnt-- */
      if (tmp_stream == (input->stream + input_data_len) &&
          dec_cont->storage.is_gdr_frame &&
          dec_cont->storage.sei_param_curr)
        dec_cont->storage.sei_param_curr->recovery_param.recovery_frame_cnt--;
#endif
      break;
    }
    }
  } while(strm_len);

end:

  /*  If Hw decodes stream, update stream buffers from "storage" */
  if(dec_cont->stream_pos_updated || dec_cont->multi_frame_input_flag) {
    if (dec_cont->secure_mode)
      output->data_left = 0;
    else {
      output->strm_curr_pos = (u8 *) dec_cont->p_hw_stream_start;
      output->strm_curr_bus_address = dec_cont->hw_stream_start_bus;
      output->data_left = dec_cont->hw_length;
    }
  } else {
    /* else update based on SW stream decode stream values */
    u32 data_consumed = (u32) (tmp_stream - input->stream);
    if(tmp_stream >= input->stream)
      data_consumed = (u32)(tmp_stream - input->stream);
    else
      data_consumed = (u32)(tmp_stream + dec_cont->buff_length - input->stream);

    output->strm_curr_pos = (u8 *) tmp_stream;
    output->strm_curr_bus_address = input->stream_bus_address + data_consumed;
    if(output->strm_curr_bus_address >= (input->buffer_bus_address + input->buff_len))
      output->strm_curr_bus_address -= input->buff_len;

    output->data_left = input_data_len - data_consumed;
  }
  ASSERT(output->strm_curr_bus_address <= (input->buffer_bus_address + input->buff_len));

  if (dec_cont->storage.sei_param_curr &&
      dec_cont->storage.sei_param_curr->decode_id == input->pic_id &&
      dec_cont->storage.sei_param_curr->bufperiod_present_flag &&
      dec_cont->storage.sei_param_curr->pictiming_present_flag) {
    if(return_value == DEC_PIC_DECODED && dec_cont->dec_stat != DEC_NEW_HEADERS) {
      dec_cont->storage.compute_time_info.access_unit_size = output->strm_curr_pos - input->stream;
      dec_cont->storage.bumping_flag = 1;
    }
  }

  /* Workaround for too big data_left value from error stream */
  if (output->data_left > input_data_len) {
    output->data_left = input_data_len;
  }

  FinalizeOutputAll(&dec_cont->fb_list);

  if(return_value == DEC_PIC_DECODED || return_value == DEC_STREAM_ERROR_DEDECTED) {
    dec_cont->gaps_checked_for_this = HANTRO_FALSE;
  }
  if (!dec_cont->b_mc) {
    u32 ret;
    H264DecPicture output;
    u32 flush_all = 0;

    if (return_value == DEC_PENDING_FLUSH)
      flush_all = 1;

    //if(return_value == DEC_PIC_DECODED || return_value == DEC_PENDING_FLUSH)
    {
      do {
        DWLmemset(&output, 0, sizeof(H264DecPicture));
        ret = h264DecNextPictureINTERNAL(dec_cont, &output, flush_all);
      } while( ret == DEC_PIC_RDY);
    }
  }
  if(dec_cont->b_mc) {
    h264MCPushOutputAll(dec_cont);
    if(output->data_left == 0 && return_value != DEC_PIC_DECODED && return_value != DEC_PENDING_FLUSH) {
      /* release buffer fully processed by SW */
      if(dec_cont->stream_consumed_callback.fn)
        dec_cont->stream_consumed_callback.fn((u8*)input->stream,
                                              (void*)dec_cont->stream_consumed_callback.p_user_data);

    }
  }
#ifdef SKIP_OPENB_FRAME
  if (return_value == DEC_PIC_DECODED &&
      dec_cont->storage.dpb->current_out->openB_flag)
    return_value = DEC_STRM_PROCESSED;
#endif

  if(dec_cont->abort)
    return(DEC_ABORTED);
  else
    return (return_value);
}

/*------------------------------------------------------------------------------

    Function: H264DecNextPicture

        Functional description:
            Get next picture in display order if any available.

        Input:
            dec_inst     decoder instance.
            end_of_stream force output of all buffered pictures

        Output:
            output     pointer to output structure

        Returns:
            DEC_OK            no pictures available for display
            DEC_PIC_RDY       picture available for display
            DEC_PARAM_ERROR     invalid parameters
            DEC_NOT_INITIALIZED   decoder instance not initialized yet

------------------------------------------------------------------------------*/
enum DecRet H264DecNextPicture(H264DecInst dec_inst,
                              H264DecPicture * output, u32 end_of_stream) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  const struct DecHwFeatures *hw_feature = NULL;

  //APITRACE("%s","H264DecNextPicture#\n");

  if(dec_inst == NULL || output == NULL) {
    APITRACEERR("%s","H264DecNextPicture# dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecNextPicture# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  u32 ret = DEC_OK;

  if(dec_cont->dec_stat == DEC_END_OF_STREAM &&
      IsOutputEmpty(&dec_cont->fb_list)) {
    //APITRACE("%s","H264DecNextPicture# DEC_END_OF_STREAM\n");
    return (DEC_END_OF_STREAM);
  }

  if((ret = PeekOutputPic(&dec_cont->fb_list, output))) {
    if(ret == ABORT_MARKER) {
      //APITRACE("%s","H264DecNextPicture# DEC_ABORTED\n");
      return (DEC_ABORTED);
    }
    if(ret == FLUSH_MARKER) {
      //APITRACE("%s","H264DecNextPicture# DEC_FLUSHED\n");
      return (DEC_FLUSHED);
    }
    DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);

    if (dec_cont->pp_enabled) {
      output->crop_params.crop_left_offset = dec_cont->ppu_cfg[0].crop.x;
      output->crop_params.crop_top_offset = dec_cont->ppu_cfg[0].crop.y;
      output->crop_params.crop_out_width = dec_cont->ppu_cfg[0].crop.width;
      output->crop_params.crop_out_height = dec_cont->ppu_cfg[0].crop.height;
    }

    /* complete output pic EC policy */
    /* decision pic output */
    if (h264ECDecisionOutput(dec_cont, output) != DEC_PIC_RDY)
      return DEC_DISCARD_INTERNAL;

    //APITRACE("%s","H264DecNextPicture# DEC_PIC_RDY\n");
    return (DEC_PIC_RDY);
  } else {
    //APITRACE("%s","H264DecNextPicture# DEC_OK\n");
    return (DEC_OK);
  }
  (void) end_of_stream;
  return (DEC_OK);
}

/*------------------------------------------------------------------------------
    Function name : h264UpdateAfterPictureDecode
    Description   :

    Return type   : void
    Argument      : struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
void h264UpdateAfterPictureDecode(struct H264DecContainer * dec_cont) {

  u32 tmp_ret = HANTRO_OK;
  storage_t *storage = &dec_cont->storage;
  sliceHeader_t *slice_header = storage->slice_header;
  u32 interlaced;
  u32 pic_code_type;
  u32 second_field = 0;
  u32 is_idr = 0;
#ifdef SKIP_OPENB_FRAME
  i32 poc;
#endif

  (void)second_field;

  h264bsdResetStorage(storage);

  ASSERT((storage));

  /* determine initial reference picture lists */
  H264InitRefPicList(dec_cont);

  if(storage->slice_header->field_pic_flag == 0)
    storage->curr_image->pic_struct = FRAME;
  else
    storage->curr_image->pic_struct = storage->slice_header->bottom_field_flag;

  if (storage->curr_image->pic_struct < FRAME) {
    if (storage->dpb->current_out->status[(u32)!storage->curr_image->pic_struct] != EMPTY)
      second_field = 1;
  }

  h264GetSarInfo(storage, &storage->curr_image->sar_width, &storage->curr_image->sar_height);

  if(storage->poc->contains_mmco5) {
    u32 tmp;

    tmp = MIN(storage->poc->pic_order_cnt[0], storage->poc->pic_order_cnt[1]);
    storage->poc->pic_order_cnt[0] -= tmp;
    storage->poc->pic_order_cnt[1] -= tmp;
  }

  storage->current_marked = storage->valid_slice_in_access_unit;

  /* Setup tiled mode for picture before updating DPB */
  interlaced = !dec_cont->storage.active_sps->frame_mbs_only_flag;

  dec_cont->tiled_reference_enable =
    DecSetupTiledReference( dec_cont->h264_regs,
                            dec_cont->dpb_mode,
                            interlaced );

  if(storage->valid_slice_in_access_unit) {
    if(IS_I_SLICE(slice_header->slice_type))
      pic_code_type = DEC_PIC_TYPE_I;
    else if(IS_P_SLICE(slice_header->slice_type))
      pic_code_type = DEC_PIC_TYPE_P;
    else
      pic_code_type = DEC_PIC_TYPE_B;

#ifdef SKIP_OPENB_FRAME
    if (!dec_cont->first_entry_point) {
      if(storage->curr_image->pic_struct < FRAME) {
        if (!second_field)
          dec_cont->entry_is_IDR = IS_IDR_NAL_UNIT(storage->prev_nal_unit);
        else {
          dec_cont->entry_POC = MIN(storage->poc->pic_order_cnt[0],
                                   storage->poc->pic_order_cnt[1]);
          dec_cont->first_entry_point = 1;
        }
      } else {
        dec_cont->entry_is_IDR = IS_IDR_NAL_UNIT(storage->prev_nal_unit);
        dec_cont->entry_POC = MIN(storage->poc->pic_order_cnt[0],
                                 storage->poc->pic_order_cnt[1]);
        dec_cont->first_entry_point = 1;
      }
    }
    if (dec_cont->skip_b < 2) {
      if (storage->curr_image->pic_struct < FRAME) {
        if(second_field) {
          if((pic_code_type == DEC_PIC_TYPE_I) || (pic_code_type == DEC_PIC_TYPE_P) ||
             (storage->dpb->current_out->pic_code_type[(u32)!storage->curr_image->pic_struct] == DEC_PIC_TYPE_I) ||
             (storage->dpb->current_out->pic_code_type[(u32)!storage->curr_image->pic_struct] == DEC_PIC_TYPE_P))
            dec_cont->skip_b++;
          else {
            poc = MIN(storage->poc->pic_order_cnt[0],
                      storage->poc->pic_order_cnt[1]);
            if(!dec_cont->entry_is_IDR && (poc < dec_cont->entry_POC))
              storage->dpb->current_out->openB_flag = 1;
          }
        } else {
          /* In case the open B frame is output before the second field is ready,
             that is, before openB_flag is set, it may be output wrongly. */
          poc = storage->poc->pic_order_cnt[storage->curr_image->pic_struct];
          if(!dec_cont->entry_is_IDR && (poc < dec_cont->entry_POC))
            storage->dpb->current_out->openB_flag = 1;
        }
      } else {
        if((pic_code_type == DEC_PIC_TYPE_I) || (pic_code_type == DEC_PIC_TYPE_P))
          dec_cont->skip_b++;
        else {
          poc = MIN(storage->poc->pic_order_cnt[0],
                    storage->poc->pic_order_cnt[1]);
          if(!dec_cont->entry_is_IDR && (poc < dec_cont->entry_POC))
            storage->dpb->current_out->openB_flag = 1;
        }
      }
    }
#endif

    if(storage->prev_nal_unit->nal_ref_idc) {
      is_idr = IS_IDR_NAL_UNIT(storage->prev_nal_unit);
      tmp_ret = h264bsdMarkDecRefPic(storage->dpb,
                                     &slice_header->dec_ref_pic_marking,
                                     storage->curr_image,
                                     slice_header->frame_num,
                                     storage->poc->pic_order_cnt,
                                     is_idr,
                                     storage->current_pic_id,
                                     storage->num_err_mbs,
                                     dec_cont->tiled_reference_enable,
                                     pic_code_type);
    } else {
      /* non-reference picture, just store for possible display
       * reordering */
      tmp_ret = h264bsdMarkDecRefPic(storage->dpb, NULL,
                                     storage->curr_image,
                                     slice_header->frame_num,
                                     storage->poc->pic_order_cnt,
                                     HANTRO_FALSE,
                                     storage->current_pic_id,
                                     storage->num_err_mbs,
                                     dec_cont->tiled_reference_enable,
                                     pic_code_type);
    }

    if (tmp_ret != HANTRO_OK && storage->view == 0)
      storage->second_field = 0;

    if(storage->dpb->delayed_out == 0) {
      h264DpbUpdateOutputList(storage->dpb);

      if (storage->view == 0)
        storage->last_base_num_out = storage->dpb->num_out;
      /* make sure that there are equal number of output pics available
       * for both views */
      else if (storage->dpb->num_out < storage->last_base_num_out)
        h264DpbAdjStereoOutput(storage->dpb, storage->last_base_num_out);
      else if (storage->last_base_num_out &&
               storage->last_base_num_out + 1 < storage->dpb->num_out)
        h264DpbAdjStereoOutput(storage->dpbs[0],
                               storage->dpb->num_out - 1);
      else if (storage->last_base_num_out == 0 && storage->dpb->num_out)
        h264DpbAdjStereoOutput(storage->dpbs[0],
                               storage->dpb->num_out);

      /* check if current_out already in output buffer and second
       * field to come -> delay output */
      if(storage->curr_image->pic_struct != FRAME &&
          (storage->view == 0 ? storage->second_field :
           !storage->base_opposite_field_pic)) {
        u32 i, tmp;

        tmp = storage->dpb->out_index_r;
        for (i = 0; i < storage->dpb->num_out; i++, tmp++) {
          if (tmp == storage->dpb->dpb_size + 1)
            tmp = 0;

          if(storage->dpb->current_out->data ==
              storage->dpb->out_buf[tmp].data) {
            storage->dpb->delayed_id = tmp;
            APITRACEDEBUG("%s","h264UpdateAfterPictureDecode: Current frame in output list\n");
            storage->dpb->delayed_out = 1;
            break;
          }
        }
      }
    } else {
      if (!storage->dpb->no_reordering)
        h264DpbUpdateOutputList(storage->dpb);
      APITRACEDEBUG("%s","h264UpdateAfterPictureDecode: Output all delayed pictures!\n");
      storage->dpb->delayed_out = 0;
      storage->dpb->current_out->to_be_displayed = 0;   /* remove it from output list */
      SET_SEI_UNUSED(storage->dpb->current_out->sei_param);
    }

  } else {
    storage->dpb->delayed_out = 0;
    storage->second_field = 0;
  }

  /*after the mark, if the pic index can be re-use((!dpb->current_out->to_be_displayed && !IS_REFERENCE_F(*(dpb->current_out))), the pp buffer should return*/
  if (storage->dpb->current_out)
    RemoveUnmarkedPpBuffer(storage->dpb);
  if ((storage->valid_slice_in_access_unit && tmp_ret == HANTRO_OK) ||
      storage->view)
    storage->next_view ^= 0x1;
  storage->pic_started = HANTRO_FALSE;
  storage->valid_slice_in_access_unit = HANTRO_FALSE;
  storage->aso_detected = 0;
}

/*------------------------------------------------------------------------------
    Function name : h264SpsSupported
    Description   :

    Return type   : u32
    Argument      : const struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
u32 h264SpsSupported(const struct H264DecContainer * dec_cont) {
  const seqParamSet_t *sps = dec_cont->storage.active_sps;

  if(sps == NULL)
    return 0;

  /* check picture size */
  if(sps->pic_width_in_mbs * 16 > NEXT_MULTIPLE(dec_cont->max_dec_pic_width, 16)||
     sps->pic_height_in_mbs * 16 > NEXT_MULTIPLE (dec_cont->max_dec_pic_height, 16) ||
     sps->pic_width_in_mbs < 3 || sps->pic_height_in_mbs < 3) {
    APITRACEERR("%s",("Picture size not supported!\n"));
    return 0;
  }

#ifdef DTRC_MIN_SIZE_LIMITED
  /* If tile mode is enabled, should take DTRC minimum size(96x48) into consideration */

  if (sps->pic_width_in_mbs < 6) {
    APITRACEERR("%s",("Picture size not supported!\n"));
    return 0;
  }

#endif

  if(dec_cont->h264_profile_support == H264_BASELINE_PROFILE) {
    if(sps->frame_mbs_only_flag != 1) {
      APITRACEERR("%s",("INTERLACED!!! Not supported in baseline decoder\n"));
      return 0;
    }
    if(sps->chroma_format_idc != 1) {
      APITRACEERR("%s",("CHROMA!!! Only 4:2:0 supported in baseline decoder\n"));
      return 0;
    }
    if(sps->scaling_matrix_present_flag != 0) {
      APITRACEERR("%s",("SCALING Matrix!!! Not supported in baseline decoder\n"));
      return 0;
    }
  }
  if (sps->bit_depth_luma > 8 || sps->bit_depth_chroma > 8) {
    if (!dec_cont->h264_high10p_support) {
      APITRACEERR("%s",("BITDEPTH > 8!!! Only supported in High10 progressive decoder\n"));
      return 0;
    }
    if (sps->frame_mbs_only_flag != 1) {
      APITRACEERR("%s",("INTERLACED!!! Not supported in High10 progressive decoder\n"));
      return 0;
    }
  }
  if (sps->frame_mbs_only_flag != 1) {
    if (dec_cont->h264_profile_support <= H264_BASELINE_PROFILE) {
      APITRACEERR("%s",("INTERLACED!!! Not supported in baseline or High10 progressive decoder\n"));
      return 0;
    }
  }

  if (!dec_cont->h264_422_intra_support && sps->chroma_format_idc == 2) {
    APITRACEERR("%s",("422 profile!!! Not supported by HW\n"));
    return 0;
  }

  return 1;
}

/*------------------------------------------------------------------------------
    Function name : h264PpsSupported
    Description   :

    Return type   : u32
    Argument      : const struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
u32 h264PpsSupported(const struct H264DecContainer * dec_cont) {
  const picParamSet_t *pps = dec_cont->storage.active_pps;

  if(dec_cont->h264_profile_support == H264_BASELINE_PROFILE) {
    if(pps->entropy_coding_mode_flag != 0) {
      APITRACEERR("%s",("CABAC!!! Not supported in baseline decoder\n"));
      return 0;
    }
    if(pps->weighted_pred_flag != 0 || pps->weighted_bi_pred_idc != 0) {
      APITRACEERR("%s",("WEIGHTED Pred!!! Not supported in baseline decoder\n"));
      return 0;
    }
    if(pps->transform8x8_flag != 0) {
      APITRACEERR("%s",("TRANSFORM 8x8!!! Not supported in baseline decoder\n"));
      return 0;
    }
    if(pps->scaling_matrix_present_flag != 0) {
      APITRACEERR("%s",("SCALING Matrix!!! Not supported in baseline decoder\n"));
      return 0;
    }
  }
  return 1;
}

/*------------------------------------------------------------------------------
    Function name   : h264StreamIsBaseline
    Description     :
    Return type     : u32
    Argument        : const struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
u32 h264StreamIsBaseline(const struct H264DecContainer * dec_cont) {
  const picParamSet_t *pps = dec_cont->storage.active_pps;
  const seqParamSet_t *sps = dec_cont->storage.active_sps;

  if(sps->profile_idc > 66) {
    return 0;
  }
  if(sps->frame_mbs_only_flag != 1) {
    return 0;
  }
  if(sps->chroma_format_idc != 1) {
    return 0;
  }
  if(sps->scaling_matrix_present_flag != 0) {
    return 0;
  }
  if(pps->entropy_coding_mode_flag != 0) {
    return 0;
  }
  if(pps->weighted_pred_flag != 0 || pps->weighted_bi_pred_idc != 0) {
    return 0;
  }
  if(pps->transform8x8_flag != 0) {
    return 0;
  }
  if(pps->scaling_matrix_present_flag != 0) {
    return 0;
  }
  return 1;
}

/*------------------------------------------------------------------------------
    Function name : h264AllocateResources
    Description   :

    Return type   : u32
    Argument      : struct H264DecContainer * dec_cont
------------------------------------------------------------------------------*/
u32 h264AllocateResources(struct H264DecContainer * dec_cont) {
  u32 ret, mbs_in_pic;
  DecAsicBuffers_t *asic = dec_cont->asic_buff;
  storage_t *storage = &dec_cont->storage;
  const seqParamSet_t *sps = storage->active_sps;
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);

  SetDecRegister(dec_cont->h264_regs, HWIF_MIN_CB_SIZE, 3);
  SetDecRegister(dec_cont->h264_regs, HWIF_MAX_CB_SIZE, 4);
  SetDecRegister(dec_cont->h264_regs, HWIF_PIC_WIDTH_IN_CBS,
                  sps->pic_width_in_mbs << 1);
  SetDecRegister(dec_cont->h264_regs, HWIF_PIC_HEIGHT_IN_CBS,
                  sps->pic_height_in_mbs << 1);

#if 1
    /* Not used in G2_H264. */
  SetDecRegister(dec_cont->h264_regs, HWIF_PARTIAL_CTB_X, 0);
  SetDecRegister(dec_cont->h264_regs, HWIF_PARTIAL_CTB_Y, 0);
  SetDecRegister(dec_cont->h264_regs, HWIF_PIC_WIDTH_4X4,
                  sps->pic_width_in_mbs << 2);
  SetDecRegister(dec_cont->h264_regs, HWIF_PIC_HEIGHT_4X4,
                  sps->pic_height_in_mbs << 2);
#endif


  ReleaseAsicBuffers(dec_cont->dwl, asic);
  if(dec_cont->llstrminfo.strm_status.virtual_address != NULL) {
    DWLFreeLinear(dec_cont->dwl, &dec_cont->llstrminfo.strm_status);
    dec_cont->llstrminfo.strm_status.virtual_address = NULL;
  }

  ret = AllocateAsicBuffers(dec_cont, asic, storage->pic_size_in_mbs);
  if(dec_cont->llstrminfo.strm_status_in_buffer == 1){
    dec_cont->llstrminfo.strm_status_addr = dec_cont->llstrminfo.strm_status.virtual_address;
  }
  if(ret == 0) {
    SET_ADDR_REG(dec_cont->h264_regs, HWIF_INTRA_4X4_BASE,
                 asic->intra_pred.bus_address);
    SET_ADDR_REG(dec_cont->h264_regs, HWIF_DIFF_MV_BASE,
                 asic->mv.bus_address);

    if(dec_cont->rlc_mode) {
      /* release any previously allocated stuff */
      FREE(storage->mb);
      FREE(storage->slice_group_map);

      mbs_in_pic = sps->pic_width_in_mbs * sps->pic_height_in_mbs;

      APITRACEDEBUG("ALLOCATE storage->mb            - %8d bytes\n",
                   mbs_in_pic * sizeof(mbStorage_t));
      storage->mb = DWLcalloc(mbs_in_pic, sizeof(mbStorage_t));

      APITRACEDEBUG("ALLOCATE storage->slice_group_map - %8d bytes\n",
                   mbs_in_pic * sizeof(u32));

      ALLOCATE(storage->slice_group_map, mbs_in_pic, u32);

      if(storage->mb == NULL || storage->slice_group_map == NULL) {
        ret = MEMORY_ALLOCATION_ERROR;
      } else {
        h264bsdInitMbNeighbours(storage->mb, sps->pic_width_in_mbs,
                                storage->pic_size_in_mbs);
      }
    } else {
      storage->mb = NULL;
      storage->slice_group_map = NULL;
    }
  }

  return ret;
}

void h264CorruptedProcess(struct H264DecContainer * dec_cont) {
  storage_t *storage = &dec_cont->storage;
  u8 bottom_field_flag = 0;

  bottom_field_flag = dec_cont->storage.slice_header->bottom_field_flag;
  if (dec_cont->storage.slice_header->field_pic_flag == 0 ||
      (dec_cont->storage.slice_header->field_pic_flag == 1 &&
       storage->dpb[0].current_out->status[!bottom_field_flag] == EMPTY)) {
    /* top_filed corrupt */
    storage->dpb[0].current_out->corrupted_first_field_or_frame = 1;
    /* reset DMV storage for erroneous pictures */
    if(dec_cont->asic_buff->enable_dmv_and_poc != 0) {
      const u32 dvm_mem_size = (storage->pic_size_in_mbs + 32) *
                                (dec_cont->high10p_mode ? 80 : 64);
      void * dvm_base = (u8*)storage->curr_image->dmv_data->virtual_address;
      if (!(dec_cont->skip_non_intra && dec_cont->pp_enabled))
        (void) DWLmemset(dvm_base, 0, dvm_mem_size);
    }
    if(dec_cont->qp_output_enable) {
      u32 qp_mem_size = NEXT_MULTIPLE(storage->active_sps->pic_width_in_mbs, 64)*storage->active_sps->pic_height_in_mbs;
      void * qpm_base;
      if (!dec_cont->pp_enabled) {
        qpm_base = (u8*)storage->curr_image->data->virtual_address +
                        dec_cont->storage.dpb->out_qp_offset;
      } else {
        qpm_base = (u8*)storage->curr_image->pp_data->virtual_address +
                        dec_cont->auxinfo_offset;
      }
      (void) DWLmemset(qpm_base, 0, qp_mem_size);
    }
  } else {
    if (!storage->dpb[0].current_out->corrupted_first_field_or_frame) {
      storage->dpb[0].current_out->corrupted_second_field = 1;
      if (bottom_field_flag)
        storage->dpb[0].current_out->pic_struct = BOTFIELD;
      else
        storage->dpb[0].current_out->pic_struct = TOPFIELD;
    }
  }

  /* no-reordering */
  dpbStorage_t *dpb = &storage->dpb[0];
  if (dpb->no_reordering) {
    dpbOutPicture_t *dpb_out = &dpb->out_buf[(dpb->out_index_w + dpb->dpb_size) % (dpb->dpb_size + 1)];
    dpb_out->field_picture = dec_cont->storage.slice_header->field_pic_flag;
    dpb_out->corrupted_second_field = dpb->current_out->corrupted_second_field;
    dpb_out->pic_struct = dpb->current_out->pic_struct;
  }
}

/*------------------------------------------------------------------------------
    Function name : bsdDecodeReturn
    Description   :

    Return type   : void
    Argument      : bsd decoder return value
------------------------------------------------------------------------------*/
static void bsdDecodeReturn(u32 retval) {
  APITRACEDEBUG("%s",("H264bsdDecode returned: \n"));
  switch (retval) {
  case H264BSD_RDY:
    APITRACEDEBUG("%s",("H264BSD_RDY\n"));
    break;
  case H264BSD_PIC_RDY:
    APITRACEDEBUG("%s",("H264BSD_PIC_RDY\n"));
    break;
  case H264BSD_HDRS_RDY:
    APITRACEDEBUG("%s",("H264BSD_HDRS_RDY\n"));
    break;
  case H264BSD_SEI_PARSED:
    APITRACEDEBUG("%s",("H264BSD_SEI_PARSED\n"));
    break;
  case H264BSD_PARAM_SET_PARSED:
    APITRACEDEBUG("%s",("H264BSD_PARAM_SET_PARSED\n"));
    break;
  case H264BSD_BUFFER_NOT_READY:
    APITRACEDEBUG("%s",("H264BSD_BUFFER_NOT_READY\n"));
    break;
  case H264BSD_NEW_ACCESS_UNIT:
    APITRACEDEBUG("%s",("H264BSD_NEW_ACCESS_UNIT\n"));
    break;
  case H264BSD_FMO:
    APITRACEDEBUG("%s",("H264BSD_FMO\n"));
    break;
  case H264BSD_UNPAIRED_FIELD:
    APITRACEDEBUG("%s",("H264BSD_UNPAIRED_FIELD\n"));
    break;
  case H264BSD_ABORTED:
    APITRACEDEBUG("%s",("H264BSD_ABORTED\n"));
    break;
  case H264BSD_NO_FREE_BUFFER:
    APITRACEERR("%s",("H264BSD_NO_FREE_BUFFER\n"));
    break;

  /* error case */
  case H264BSD_NO_REF:
    APITRACEDEBUG("%s",("H264BSD_NO_REF\n"));
    break;
  case H264BSD_SEI_ERROR:
    APITRACEDEBUG("%s",("H264BSD_SEI_ERROR\n"));
    break;
  case H264BSD_PARAM_SET_ERROR:
    APITRACEDEBUG("%s",("H264BSD_PARAM_SET_ERROR\n"));
    break;
  case H264BSD_SLICE_HDR_ERROR:
    APITRACEDEBUG("%s",("H264BSD_SLICE_HDR_ERROR\n"));
    break;
  case H264BSD_NONREF_PIC_SKIPPED:
    APITRACEERR("%s",("H264BSD_NONREF_PIC_SKIPPED\n"));
    break;
  case H264BSD_PB_PIC_SKIPPED:
    APITRACEERR("%s",("H264BSD_PB_PIC_SKIPPED\n"));
    break;
  case H264BSD_MEMFAIL:
    APITRACEDEBUG("%s",("H264BSD_MEMFAIL\n"));
    break;
  case H264BSD_REF_PICS_ERROR:
    APITRACEDEBUG("%s",("H264BSD_REF_PICS_ERROR\n"));
    break;
  case H264BSD_NALUNIT_ERROR:
    APITRACEERR("%s",("H264BSD_NALUNIT_ERROR\n"));
    break;
  case H264BSD_AU_BOUNDARY_ERROR:
    APITRACEDEBUG("%s",("H264BSD_AU_BOUNDARY_ERROR\n"));
    break;
  case H264BSD_ERROR_DETECTED:
    APITRACEDEBUG("%s",("H264BSD_ERROR_DETECTED\n"));
    break;
  default:
    APITRACEERR("%s",("UNKNOWN\n"));
    break;
  }
}

/*------------------------------------------------------------------------------
    Function name   : h264GetSarInfo
    Description     : Returns the sample aspect ratio size info
    Return type     : void
    Argument        : storage_t *storage - decoder storage
    Argument        : u32 * sar_width - SAR width returned here
    Argument        : u32 *sar_height - SAR height returned here
------------------------------------------------------------------------------*/
void h264GetSarInfo(const storage_t * storage, u32 * sar_width,
                    u32 * sar_height) {
  switch (h264bsdAspectRatioIdc(storage)) {
  case 0:
    *sar_width = 0;
    *sar_height = 0;
    break;
  case 1:
    *sar_width = 1;
    *sar_height = 1;
    break;
  case 2:
    *sar_width = 12;
    *sar_height = 11;
    break;
  case 3:
    *sar_width = 10;
    *sar_height = 11;
    break;
  case 4:
    *sar_width = 16;
    *sar_height = 11;
    break;
  case 5:
    *sar_width = 40;
    *sar_height = 33;
    break;
  case 6:
    *sar_width = 24;
    *sar_height = 1;
    break;
  case 7:
    *sar_width = 20;
    *sar_height = 11;
    break;
  case 8:
    *sar_width = 32;
    *sar_height = 11;
    break;
  case 9:
    *sar_width = 80;
    *sar_height = 33;
    break;
  case 10:
    *sar_width = 18;
    *sar_height = 11;
    break;
  case 11:
    *sar_width = 15;
    *sar_height = 11;
    break;
  case 12:
    *sar_width = 64;
    *sar_height = 33;
    break;
  case 13:
    *sar_width = 160;
    *sar_height = 99;
    break;
  case 255:
    h264bsdSarSize(storage, sar_width, sar_height);
    break;
  default:
    *sar_width = 0;
    *sar_height = 0;
  }
}

/*------------------------------------------------------------------------------
    Function name   : h264CheckReleasePpAndHw
    Description     : Release HW lock and wait for PP to finish, need to be
                      called if errors/problems after first field of a picture
                      finished and PP left running
    Return type     : void
    Argument        :
    Argument        :
    Argument        :
------------------------------------------------------------------------------*/
void h264CheckReleasePpAndHw(struct H264DecContainer *dec_cont) {
  if (dec_cont->keep_hw_reserved) {
    dec_cont->keep_hw_reserved = 0;
    DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
  }

}

/*------------------------------------------------------------------------------

    Function: H264DecPeek

        Functional description:
            Get last decoded picture if any available. No pictures are removed
            from output nor DPB buffers.

        Input:
            dec_inst     decoder instance.

        Output:
            output     pointer to output structure

        Returns:
            DEC_OK            no pictures available for display
            DEC_PIC_RDY       picture available for display
            DEC_PARAM_ERROR   invalid parameters

------------------------------------------------------------------------------*/
enum DecRet H264DecPeek(H264DecInst dec_inst, H264DecPicture * output) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  dpbPicture_t *current_out = dec_cont->storage.dpb->current_out;
  u32 bit_depth = 0;
  u32 i = 0;
  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
  u32 *output_picture = NULL;

  //APITRACE("%s","H264DecPeek#\n");

  if(dec_inst == NULL || output == NULL) {
    APITRACEERR("%s","H264DecPeek# dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecPeek# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  if (dec_cont->dec_stat != DEC_NEW_HEADERS &&
      dec_cont->storage.dpb->fullness && current_out != NULL &&
      (current_out->status[0] != EMPTY || current_out->status[1] != EMPTY)) {

    bit_depth = (current_out->bit_depth_luma == 8 && current_out->bit_depth_chroma == 8) ? 8 : 10;

    output->output_dmv = current_out->dmv_data->virtual_address;
    output->output_dmv_bus_address = current_out->dmv_data->bus_address;
    output->dmv_size = dec_cont->storage.dmv_mem_size;

    if (!dec_cont->pp_enabled) {
      output->output_qp = (u32 *)((addr_t)current_out->data->virtual_address +
          dec_cont->storage.dpb->out_qp_offset);
      output->output_qp_bus_address = current_out->data->bus_address +
          dec_cont->storage.dpb->out_qp_offset;
      output->qp_size = dec_cont->storage.qp_mem_size;
      output->pictures[0].output_picture = current_out->data->virtual_address;
      output->pictures[0].output_picture_bus_address = current_out->data->bus_address;
      #ifdef TILE_8x8
      output->pictures[0].output_format = dec_cont->use_video_compressor ? DEC_OUT_FRM_RFC :
       (current_out->tiled_mode ? (bit_depth == 8 ? (current_out->mono_chrome ? DEC_OUT_FRM_YUV400TILE8x8 : DEC_OUT_FRM_YUV420TILE8x8) :
                                                        (current_out->mono_chrome ? DEC_OUT_FRM_YUV400TILE8x8_PACK10 : DEC_OUT_FRM_YUV420TILE8x8_PACK10)) :
                                      DEC_OUT_FRM_RASTER_SCAN);
      #else
      output->pictures[0].output_format = dec_cont->use_video_compressor ? DEC_OUT_FRM_RFC :
          (current_out->tiled_mode ? (bit_depth == 8 ? (current_out->mono_chrome ? DEC_OUT_FRM_YUV400TILE : DEC_OUT_FRM_YUV420TILE) :
                                                        (current_out->mono_chrome ? DEC_OUT_FRM_YUV400TILE_PACK10 : DEC_OUT_FRM_YUV420TILE_PACK10)) :
                                      DEC_OUT_FRM_RASTER_SCAN);
      #endif
      output->pictures[0].pic_width = h264bsdPicWidth(&dec_cont->storage) << 4;
      output->pictures[0].pic_height = h264bsdPicHeight(&dec_cont->storage) << 4;
      if (output->pictures[0].output_format != DEC_OUT_FRM_RFC)
        output->pictures[0].pic_stride = NEXT_MULTIPLE(output->pictures[0].pic_width *
                                         bit_depth * TILE_HEIGHT, ALIGN(dec_cont->align) * 8) / 8;
      else
        output->pictures[0].pic_stride = output->pictures[0].pic_width * bit_depth * 4 / 8;
      #ifdef TILE_8x8
      output->pictures[0].pic_stride_ch = NEXT_MULTIPLE(output->pictures[0].pic_width *
                                         bit_depth * 4, ALIGN(dec_cont->align) * 8) / 8;
      #else
      output->pictures[0].pic_stride_ch = output->pictures[0].pic_stride;
      #endif

      if (current_out->mono_chrome) {
        output->pictures[0].output_picture_chroma = NULL;
        output->pictures[0].output_picture_chroma_bus_address = 0;
      } else {
        output->pictures[0].output_picture_chroma = output->pictures[0].output_picture +
                           output->pictures[0].pic_stride * output->pictures[0].pic_height / 16;
        output->pictures[0].output_picture_chroma_bus_address =
            output->pictures[0].output_picture_bus_address +
            output->pictures[0].pic_stride * output->pictures[0].pic_height / 4;
      }
      if (dec_cont->use_video_compressor) {
        /* Compression table info. */
        output->output_rfc_luma_base = current_out->data->virtual_address +
                                      dec_cont->storage.dpb[0].cbs_ytbl_offset / 4;
        output->output_rfc_luma_bus_address = current_out->data->bus_address + dec_cont->storage.dpb[0].cbs_ytbl_offset;
        if (current_out->mono_chrome) {
          output->output_rfc_chroma_base = NULL;
          output->output_rfc_chroma_bus_address = 0;
        } else {
          output->output_rfc_chroma_base = current_out->data->virtual_address +
                                          dec_cont->storage.dpb[0].cbs_ctbl_offset / 4;
          output->output_rfc_chroma_bus_address = current_out->data->bus_address + dec_cont->storage.dpb[0].cbs_ctbl_offset;
        }
      }
    } else {
      output->output_qp = (u32 *)((addr_t)current_out->ds_data->virtual_address +
          dec_cont->auxinfo_offset);
      output->output_qp_bus_address = current_out->ds_data->bus_address +
          dec_cont->auxinfo_offset;
      output->qp_size = dec_cont->storage.qp_mem_size;

      for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
        if (!ppu_cfg->enabled) continue;
        output->pictures[i].output_picture = (u32 *)((addr_t)current_out->ds_data->virtual_address + ppu_cfg->luma_offset);
        output->pictures[i].output_picture_bus_address = current_out->ds_data->bus_address + ppu_cfg->luma_offset;
        if (dec_cont->ppu_cfg[i].monochrome) {
          output->pictures[i].output_picture_chroma = NULL;
          output->pictures[i].output_picture_chroma_bus_address = 0;
        } else {
          output->pictures[i].output_picture_chroma = (u32 *)((addr_t)current_out->ds_data->virtual_address + ppu_cfg->chroma_offset);
          output->pictures[i].output_picture_chroma_bus_address = current_out->ds_data->bus_address + ppu_cfg->chroma_offset;
        }
        if (output_picture == NULL)
          output_picture = (u32 *)output->pictures[i].output_picture;
        output->pictures[i].output_format = TransUnitConfig2Format(&dec_cont->ppu_cfg[i]);
        if (ppu_cfg->crop2.enabled) {
          output->pictures[i].pic_width = dec_cont->ppu_cfg[i].crop2.width;
          output->pictures[i].pic_height = dec_cont->ppu_cfg[i].crop2.height;
        } else {
          output->pictures[i].pic_width = dec_cont->ppu_cfg[i].scale.width;
          output->pictures[i].pic_height = dec_cont->ppu_cfg[i].scale.height;
        }
        output->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
        output->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
      }
    }

    output->pic_id = current_out->pic_id;
    output->pic_coding_type[0] = current_out->pic_code_type[0];
    output->pic_coding_type[1] = current_out->pic_code_type[1];
    output->is_idr_picture[0] = current_out->is_idr[0];
    output->is_idr_picture[1] = current_out->is_idr[1];
    output->decode_id[0] = current_out->decode_id[0];
    output->decode_id[1] = current_out->decode_id[1];
    output->error_ratio[0] = current_out->error_ratio[0];
    output->error_ratio[1] = current_out->error_ratio[1];

    output->interlaced = dec_cont->storage.dpb->interlaced;
    output->field_picture = current_out->is_field_pic;

    output->top_field = 0;
    output->pic_struct = current_out->pic_struct;

    if (output->field_picture) {
      /* just one field in buffer -> that is the output */
      if(current_out->status[0] == EMPTY || current_out->status[1] == EMPTY) {
        output->top_field = (current_out->status[0] == EMPTY) ? 0 : 1;
      }
      /* both fields decoded -> check field parity from slice header */
      else
        output->top_field =
          dec_cont->storage.slice_header->bottom_field_flag == 0;
    } else
      output->top_field = 1;

    output->crop_params = current_out->crop;


    APITRACE("%s","H264DecPeek# DEC_PIC_RDY\n");
    return (DEC_PIC_RDY);
  } else {
    APITRACE("%s","H264DecPeek# DEC_OK\n");
    return (DEC_OK);
  }

}

/*------------------------------------------------------------------------------

    Function: H264DecPictureConsumed()

        Functional description:
            Release the frame displayed and sent by APP

        Inputs:
            dec_inst     Decoder instance

            picture    pointer of picture structure to be released

        Outputs:
            none

        Returns:
            DEC_PARAM_ERROR       Decoder instance or picture is null
            DEC_NOT_INITIALIZED   Decoder instance isn't initialized
            DEC_OK                picture release success

------------------------------------------------------------------------------*/
enum DecRet H264DecPictureConsumed(H264DecInst dec_inst,
                                  const H264DecPicture *picture) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  dpbStorage_t *dpb;
  u32 id = FB_NOT_VALID_ID, i;
  DWLMemAddr output_picture = (DWLMemAddr)NULL;
  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;

 // APITRACE("%s","H264DecPictureConsumed#\n");

  if(dec_inst == NULL || picture == NULL) {
    APITRACEERR("%s","H264DecPictureConsumed# dec_inst or picture is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecPictureConsumed# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  if (!dec_cont->pp_enabled) {
    /* find the mem descriptor for this specific buffer, base view first */
    dpb = dec_cont->storage.dpbs[0];
    for(i = 0; i < dpb->tot_buffers; i++) {
      if(picture->pictures[0].output_picture_bus_address == dpb->pic_buffers[i].bus_address
#ifndef MEM_ONLY_DEV_CHECK
	    && picture->pictures[0].output_picture == dpb->pic_buffers[i].virtual_address
#endif
		) {
        id = i;
        break;
      }
    }

    /* if not found, search other view for MVC mode */
    if(id == FB_NOT_VALID_ID && dec_cont->storage.mvc == HANTRO_TRUE) {
      dpb = dec_cont->storage.dpbs[1];
      /* find the mem descriptor for this specific buffer */
      for(i = 0; i < dpb->tot_buffers; i++) {
        if(picture->pictures[0].output_picture_bus_address == dpb->pic_buffers[i].bus_address
#ifndef MEM_ONLY_DEV_CHECK
		  && picture->pictures[0].output_picture == dpb->pic_buffers[i].virtual_address
#endif
		  ) {
          id = i;
          break;
        }
      }
    }

    if(id == FB_NOT_VALID_ID)
      return DEC_PARAM_ERROR;

    PopOutputPic(&dec_cont->fb_list, dpb->pic_buff_id[id]);

    SET_SEI_UNUSED(picture->sei_param);
  } else {
    for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
      if (!ppu_cfg->enabled)
        continue;
      else {
#ifndef MEM_ONLY_DEV_CHECK
        output_picture = (DWLMemAddr)picture->pictures[i].output_picture;
#else
        output_picture = (DWLMemAddr)picture->pictures[i].output_picture_bus_address;
#endif
        break;
      }
    }
    InputQueueReturnBuffer(dec_cont->pp_buffer_queue, output_picture);

    SET_SEI_UNUSED(picture->sei_param);

    if (dec_cont->dmv_output_enable) {
      dpb = dec_cont->storage.dpbs[0];
      H264ReturnDMVBuffer(&dpb[0], picture->output_dmv_bus_address);
      if (dec_cont->storage.mvc == HANTRO_TRUE) {
        dpb = dec_cont->storage.dpbs[1];
        H264ReturnDMVBuffer(&dpb[0], picture->output_dmv_bus_address);
      }
    }
  }

  return DEC_OK;
}


/*------------------------------------------------------------------------------

    Function: h264DecNextPictureINTERNAL

        Functional description:
            Push next picture in display order into output list if any available.

        Input:
            dec_inst     decoder instance.
            end_of_stream force output of all buffered pictures

        Output:
            output     pointer to output structure

        Returns:
            DEC_OK            no pictures available for display
            DEC_PIC_RDY       picture available for display
            DEC_PARAM_ERROR     invalid parameters
            DEC_NOT_INITIALIZED   decoder instance not initialized yet

------------------------------------------------------------------------------*/
enum DecRet h264DecNextPictureINTERNAL(H264DecInst dec_inst,
                                       H264DecPicture * output,
                                       u32 end_of_stream) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  const dpbOutPicture_t *out_pic = NULL;
  u32 bit_depth = 8;
  dpbStorage_t *out_dpb = NULL, *dpb = NULL;
  storage_t *storage = NULL;
  sliceHeader_t *p_slice_hdr = NULL;
  u32 i = 0;
  u32 line_of_width = 0;
  u32 chroma_base_offset = 0;
  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
  DWLMemAddr output_picture = (DWLMemAddr)NULL;
  u32 discard_error_pic = 0;
#ifdef SUPPORT_DEC400
  const u32 *tile_status_virtual_address = NULL;
  addr_t tile_status_bus_address = 0;
#endif

  if(output == NULL) {
    APITRACEERR("%s","h264DecNextPictureINTERNAL# output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  storage = &dec_cont->storage;
  p_slice_hdr = storage->slice_header;
  out_dpb = dec_cont->storage.dpbs[dec_cont->storage.out_view];

  /* if display order is the same as decoding order and PP is used and
   * cannot be used in pipeline (rotation) -> do not perform PP here but
   * while decoding next picture (parallel processing instead of
   * DEC followed by PP followed by DEC...) */
  if(out_dpb->no_reordering == 0) {
    if(!out_dpb->delayed_out) {
      dpbStorage_t *dpb = dec_cont->storage.dpb;
      dec_cont->storage.dpb =
        dec_cont->storage.dpbs[dec_cont->storage.out_view];

      out_pic = h264bsdNextOutputPicture(&dec_cont->storage);

      if ( (dec_cont->storage.num_views ||
            dec_cont->storage.out_view) && out_pic != NULL) {
        output->view_id =
          dec_cont->storage.view_id[dec_cont->storage.out_view];
        dec_cont->storage.out_view ^= 0x1;
      }
      dec_cont->storage.dpb = dpb;
    }
  } else {
    /* no reordering of output pics AND stereo was activated after base
     * picture was output -> output stereo view pic if available */
    if (dec_cont->storage.num_views &&
        dec_cont->storage.view && dec_cont->storage.out_view == 0 &&
        out_dpb->num_out == 0 &&
        dec_cont->storage.dpbs[dec_cont->storage.view]->num_out > 0) {
      dec_cont->storage.out_view ^= 0x1;
      out_dpb = dec_cont->storage.dpbs[dec_cont->storage.out_view];
    }

    if(!end_of_stream &&
        ((out_dpb->num_out == 1 && out_dpb->delayed_out) ||
         (p_slice_hdr->field_pic_flag && storage->second_field))) {
      /* have second filed: do nothing */
    } else {
      dec_cont->storage.dpb =
        dec_cont->storage.dpbs[dec_cont->storage.out_view];

      out_pic = h264bsdNextOutputPicture(&dec_cont->storage);

      output->view_id =
        dec_cont->storage.view_id[dec_cont->storage.out_view];
      if ( (dec_cont->storage.num_views ||
            dec_cont->storage.out_view) && out_pic != NULL)
        dec_cont->storage.out_view ^= 0x1;
    }
  }

  if(out_pic != NULL) {
    if (!dec_cont->storage.num_views)
      output->view_id = 0;

    bit_depth = (out_pic->bit_depth_luma == 8 && out_pic->bit_depth_chroma == 8) ? 8 : 10;

    output->output_dmv = (u32*)((addr_t)out_pic->dmv_data->virtual_address);
    output->output_dmv_bus_address = out_pic->dmv_data->bus_address;
    output->dmv_size = dec_cont->storage.dmv_mem_size;

    if (!dec_cont->pp_enabled) {
      output->output_qp = (u32*)((addr_t)out_pic->data->virtual_address +
          dec_cont->storage.dpb->out_qp_offset);
      output->output_qp_bus_address = out_pic->data->bus_address +
          dec_cont->storage.dpb->out_qp_offset;
      output->qp_size = dec_cont->storage.qp_mem_size;
      output->pictures[0].output_picture = out_pic->data->virtual_address;
      output->pictures[0].output_picture_bus_address = out_pic->data->bus_address;
      #ifdef TILE_8x8
      output->pictures[0].output_format = dec_cont->use_video_compressor ? DEC_OUT_FRM_RFC :
        (out_pic->tiled_mode ? (bit_depth == 8 ? (out_pic->mono_chrome ? DEC_OUT_FRM_YUV400TILE8x8 : DEC_OUT_FRM_YUV420TILE8x8) :
                                                  (out_pic->mono_chrome ? DEC_OUT_FRM_YUV400TILE8x8_PACK10 : DEC_OUT_FRM_YUV420TILE8x8_PACK10)) :
                                DEC_OUT_FRM_RASTER_SCAN);
      #else
      output->pictures[0].output_format = dec_cont->use_video_compressor ? DEC_OUT_FRM_RFC :
        (out_pic->tiled_mode ? (bit_depth == 8 ? (out_pic->mono_chrome ? DEC_OUT_FRM_YUV400TILE : DEC_OUT_FRM_YUV420TILE) :
                                                  (out_pic->mono_chrome ? DEC_OUT_FRM_YUV400TILE_PACK10 : DEC_OUT_FRM_YUV420TILE_PACK10)) :
                                DEC_OUT_FRM_RASTER_SCAN);
      #endif
      output->pictures[0].pic_width = out_pic->pic_width;
      output->pictures[0].pic_height = out_pic->pic_height;
      output->pictures[0].chroma_format=out_pic->chroma_format_idc;
      if (output->pictures[0].output_format == DEC_OUT_FRM_RFC) {
        line_of_width = 8;
        output->pictures[0].pic_stride = NEXT_MULTIPLE(8 * output->pictures[0].pic_width * bit_depth,
                                                       ALIGN(dec_cont->align) * 8) / 8;
        output->pictures[0].pic_stride_ch = NEXT_MULTIPLE(4 * output->pictures[0].pic_width * bit_depth,
                                                       ALIGN(dec_cont->align) * 8) / 8;
      } else if (output->pictures[0].output_format != DEC_OUT_FRM_RFC) {
        output->pictures[0].pic_stride = NEXT_MULTIPLE(TILE_HEIGHT * output->pictures[0].pic_width * bit_depth,
                                                       ALIGN(dec_cont->align) * 8) / 8;
        #ifdef TILE_8x8
        line_of_width = 8;
        output->pictures[0].pic_stride_ch = NEXT_MULTIPLE(4 * output->pictures[0].pic_width * bit_depth,
                                                       ALIGN(dec_cont->align) * 8) / 8;
        #else
        line_of_width = 4;
        output->pictures[0].pic_stride_ch = output->pictures[0].pic_stride;
        #endif
      }
      chroma_base_offset = NEXT_MULTIPLE(output->pictures[0].pic_stride * output->pictures[0].pic_height
                                         / line_of_width, MAX(16, ALIGN(dec_cont->align)));
      if (out_pic->mono_chrome) {
        output->pictures[0].output_picture_chroma = NULL;
        output->pictures[0].output_picture_chroma_bus_address = 0;
      } else {
        output->pictures[0].output_picture_chroma =
          (u32*)((u8*)output->pictures[0].output_picture + chroma_base_offset);
        output->pictures[0].output_picture_chroma_bus_address =
          output->pictures[0].output_picture_bus_address + chroma_base_offset;
      }
    } else {
      output->output_qp = (u32*)((addr_t)out_pic->pp_data->virtual_address + dec_cont->auxinfo_offset);
      output->output_qp_bus_address = out_pic->pp_data->bus_address + dec_cont->auxinfo_offset;
      output->qp_size = dec_cont->storage.qp_mem_size;
      for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
        if (!ppu_cfg->enabled) continue;
        output->pictures[i].output_picture = (u32*)((addr_t)out_pic->pp_data->virtual_address + ppu_cfg->luma_offset);
        output->pictures[i].output_picture_bus_address = out_pic->pp_data->bus_address + ppu_cfg->luma_offset;
        if (dec_cont->ppu_cfg[i].monochrome) {
          output->pictures[i].output_picture_chroma = NULL;
          output->pictures[i].output_picture_chroma_bus_address = 0;
        } else {
          output->pictures[i].output_picture_chroma = (u32*)((addr_t)out_pic->pp_data->virtual_address + ppu_cfg->chroma_offset);
          output->pictures[i].output_picture_chroma_bus_address = out_pic->pp_data->bus_address + ppu_cfg->chroma_offset;
        }
        if (!output_picture) {
#ifndef MEM_ONLY_DEV_CHECK
          output_picture = (DWLMemAddr)output->pictures[i].output_picture;
#else
          output_picture = (DWLMemAddr)output->pictures[i].output_picture_bus_address;
#endif
        }
        output->pictures[i].output_format = TransUnitConfig2Format(&dec_cont->ppu_cfg[i]);
        if (ppu_cfg->crop2.enabled) {
          output->pictures[i].pic_width = dec_cont->ppu_cfg[i].crop2.width;
          output->pictures[i].pic_height = dec_cont->ppu_cfg[i].crop2.height;
        } else {
          output->pictures[i].pic_width = dec_cont->ppu_cfg[i].scale.width;
          output->pictures[i].pic_height = dec_cont->ppu_cfg[i].scale.height;
        }
        output->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
        output->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
        //output->pictures[i].chroma_format = dec_cont->ppu_cfg[i].pp_chroma_format;
      }
#ifdef SUPPORT_DEC400
      /* dec400_table_buffer is put into the end region of all pp buffer */
      ppu_cfg = dec_cont->ppu_cfg;
      for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
        if (!ppu_cfg->enabled) continue;
        if (ppu_cfg->luma_size) {
          if(tile_status_bus_address == 0) {
            tile_status_virtual_address = output->pictures[i].output_picture;
            tile_status_bus_address = output->pictures[i].output_picture_bus_address;
          }
        }
      }

      ppu_cfg = dec_cont->ppu_cfg;
      for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
        if (!ppu_cfg->enabled || !ppu_cfg->dec400_enabled || ppu_cfg->rgb) continue;
        PpFillDec400TblInfo(ppu_cfg,
                          tile_status_virtual_address,
                          tile_status_bus_address,
                          &output->pictures[i].dec400_luma_table,
                          &output->pictures[i].dec400_chroma_table);
      }
#endif
    }

    output->sar_width = out_pic->sar_width;
    output->sar_height = out_pic->sar_height;
    output->pic_width = out_pic->pic_width;
    output->pic_height = out_pic->pic_height;
    output->pic_id = out_pic->pic_id;
    output->pic_coding_type[0] = out_pic->pic_code_type[0];
    output->pic_coding_type[1] = out_pic->pic_code_type[1];
    output->is_idr_picture[0] = out_pic->is_idr[0];
    output->is_idr_picture[1] = out_pic->is_idr[1];
    output->decode_id[0] = out_pic->decode_id[0];
    output->decode_id[1] = out_pic->decode_id[1];
    output->error_ratio[0] = out_pic->error_ratio[0];
    output->error_ratio[1] = out_pic->error_ratio[1];
    output->error_info = out_pic->error_info;
    output->sei_param[0] = out_pic->sei_param[0];
    output->sei_param[1] = out_pic->sei_param[1];

    output->interlaced = out_pic->interlaced;
    output->field_picture = out_pic->field_picture;
    output->corrupted_second_field = out_pic->corrupted_second_field;
    output->top_field = out_pic->top_field;
    output->bit_depth_luma = out_pic->bit_depth_luma;
    output->bit_depth_chroma = out_pic->bit_depth_chroma;
    output->cycles_per_mb = out_pic->cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
    output->bitrate_4k60fps = out_pic->bitrate_4k60fps;
    output->bwrd_in_fs = out_pic->bwrd_in_fs;
    output->bwwr_in_fs = out_pic->bwwr_in_fs;
#endif
    output->chroma_format_idc=out_pic->chroma_format_idc;
    output->crop_params = out_pic->crop;
    output->pic_struct = out_pic->pic_struct;
    output->is_gdr_frame = out_pic->is_gdr_frame;
    /* JZQ: for svct debug */
    // static u32 disp_id = 1;
    // printf("[SVC DEBUG INFO] PIC %2d/%2d, temporal_id = %d\n", disp_id++, out_pic->pic_id, out_pic->temporal_id);

#ifdef SKIP_OPENB_FRAME
    if (out_pic->is_openb) discard_error_pic = 1;
#endif
    if (discard_error_pic) {
      if(IsBufferOutput(&dec_cont->fb_list, out_pic->mem_idx))
        ClearOutput(&dec_cont->fb_list, out_pic->mem_idx);
      if (dec_cont->pp_enabled) {
        InputQueueReturnBuffer(dec_cont->pp_buffer_queue, output_picture);
        H264ReturnDMVBuffer(dec_cont->storage.dpb, output->output_dmv_bus_address);
        SET_SEI_UNUSED(output->sei_param);
      }
    } else {
      if (dec_cont->pp_enabled)
        InputQueueSetBufAsUsed(dec_cont->pp_buffer_queue, output_picture);
      if (IsBufferOutput(&dec_cont->fb_list, out_pic->mem_idx))
        PushOutputPic(&dec_cont->fb_list, output, out_pic->mem_idx);
    }

    /* If reference buffer is not external, consume it and return it to DPB list. */
    /* Consume reference buffer when only output pp buffer. */
    if (dec_cont->pp_enabled) {
      if (!discard_error_pic) {
        PopOutputPic(&dec_cont->fb_list, out_pic->mem_idx);
        if (!dec_cont->dmv_output_enable) {
          dpb = dec_cont->storage.dpbs[0];
          H264ReturnDMVBuffer(&dpb[0], output->output_dmv_bus_address);
          if (dec_cont->storage.mvc == HANTRO_TRUE) {
            dpb = dec_cont->storage.dpbs[1];
            H264ReturnDMVBuffer(&dpb[0], output->output_dmv_bus_address);
          }
        }
      }
    }
    return (DEC_PIC_RDY);
  } else {
    //APITRACE("%s","h264DecNextPictureINTERNAL# DEC_OK\n");
    return (DEC_OK);
  }
}


void h264CycleCount(struct H264DecContainer * dec_cont) {
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  dpbPicture_t *current_out = dpb->current_out;
  u32 cycles = 0;
  u32 mbs = h264bsdPicWidth(&dec_cont->storage) *
             h264bsdPicHeight(&dec_cont->storage);
#ifdef FPGA_PERF_AND_BW
  u64 bwrd_in_fs, bwwr_in_fs;
  u32 bit_depth = dec_cont->storage.active_sps->bit_depth_luma;
  u32 pic_size = h264bsdPicWidth(&dec_cont->storage) * h264bsdPicHeight(&dec_cont->storage) << 8;
  u32 bitrate = ((60 * GetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN) * 8/ (h264bsdPicWidth(&dec_cont->storage) * 16)) * 3840/ (h264bsdPicHeight(&dec_cont->storage) * 16)) *2160;
#endif
  if (mbs)
    cycles = GetDecRegister(dec_cont->h264_regs, HWIF_PERF_CYCLE_COUNT) / mbs;

  current_out->cycles_per_mb = cycles;
#ifdef FPGA_PERF_AND_BW
  current_out->bitrate_4k60fps = bitrate;

  bwrd_in_fs = DWLReadBw(dec_cont->dwl, 0, 0);// 0 is read bandwidth
  bwwr_in_fs = DWLReadBw(dec_cont->dwl, 0, 1);// 1 is write bandwidth
  if (dec_cont->storage.active_sps->bit_depth_luma == 10){
    bwrd_in_fs *= 0.8;
    bwwr_in_fs *= 0.8;
  }
  current_out->bwrd_in_fs = bwrd_in_fs * 16 * 1000/ pic_size;
  current_out->bwwr_in_fs = bwwr_in_fs * 16 * 1000/ pic_size;
#endif
#ifdef FPGA_PERF_AND_BW
  printf("no_reordering cycles/mb %d\n", cycles);
#endif

  if(dpb->no_reordering) {
    dpbOutPicture_t *dpb_out = &dpb->out_buf[(dpb->out_index_w + dpb->dpb_size) % (dpb->dpb_size + 1)];
    dpb_out->cycles_per_mb = cycles;
#ifdef FPGA_PERF_AND_BW
    dpb_out->bitrate_4k60fps = bitrate;
    dpb_out->bwrd_in_fs = bwrd_in_fs * 16 * 1000/ pic_size;
    dpb_out->bwwr_in_fs = bwwr_in_fs * 16 * 1000/ pic_size;
#endif
  }
#ifdef FPGA_PERF_AND_BW
  if(!dec_cont->b_mc) {
    DecPerfInfoCount(dec_cont->core_id, &dec_cont->perf_info, pic_size, bit_depth);
  }
#endif
}

/* mark corrupt picture in output queue */
void h264MCMarkOutputPicInfo(struct H264DecContainer *dec_cont,
                             const H264HwRdyCallbackArg *info,
                             enum DecErrorInfo error_info,
                             const u32* dec_regs) {
  const dpbStorage_t *dpb = NULL;
  struct DWLLinearMem *p_out = NULL;
  struct ErrorPicInfo error_pic_info;
  OutputPicInfo pic_info;

  u32 i = 0;
  u32 j = 0;
  u32 tmp = 0;
  enum DecPicCodingType pic_code_type;
  u32 num_err_mbs = 0;
  u32 error_ratio = 0;
  u32 cycles = 0;
  u32 mbs = 0;

  dpb = info->current_dpb;
  p_out = (struct DWLLinearMem *)GetDataById(dpb->fb_list, info->out_id);
  pic_code_type = GetDecRegister(dec_regs, HWIF_DEC_PIC_INF) ? DEC_PIC_TYPE_B : info->pic_code_type[0];

  /* cycles count */
  mbs = (h264bsdPicWidth(&dec_cont->storage) *
             h264bsdPicHeight(&dec_cont->storage));
  if (mbs && dec_cont->high10p_mode)
    cycles = GetDecRegister(dec_regs, HWIF_PERF_CYCLE_COUNT) / mbs;

  /* error_info of mbs_num. */
  if (error_info != DEC_NO_ERROR &&
      error_info != DEC_REF_ERROR) {
    if (dec_cont->hw_conceal)
      num_err_mbs = GetDecRegister(dec_regs, HWIF_TOTAL_ERROR_CTBS);
    else {
      error_pic_info.error_x = GetDecRegister(dec_regs, HWIF_MB_LOCATION_X);
      error_pic_info.error_y = GetDecRegister(dec_regs, HWIF_MB_LOCATION_Y);
      error_pic_info.pic_width_in_ctb  = dec_cont->storage.active_sps->pic_width_in_mbs;
      error_pic_info.pic_height_in_ctb = dec_cont->storage.active_sps->pic_height_in_mbs;
      error_pic_info.log2_ctb_size = 4;
      error_pic_info.tile_info.num_tile_rows    = 1; /* h264 no tile */
      error_pic_info.tile_info.num_tile_columns = 1;
      num_err_mbs = GetErrorCtbCount(&error_pic_info);
    }
    /* the error can be ignored. */
    if (num_err_mbs == 0)
      error_info = DEC_NO_ERROR;
  }
  error_ratio = num_err_mbs * EC_ROUND_COEFF / dec_cont->storage.pic_size_in_mbs;

  /* check error_info of ref_list */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (dpb->buffer[i].error_info != DEC_NO_ERROR) {
      for (j = 0; j <= dpb->dpb_size; j++) {
        if (dpb->buffer[i].mem_idx == info->ref_mem_idx[j]) {
          error_info |= DEC_REF_ERROR;
          break;
        }
      }
    }
  }

  /* update out_buf: in NextPictureInternal */
  i = dpb->num_out;
  tmp = dpb->out_index_r;
  while((i--) > 0) {
    if (tmp == dpb->dpb_size + 1)
      tmp = 0;
    dpbOutPicture_t *dpb_pic = (dpbOutPicture_t *)dpb->out_buf + tmp;
    if(dpb_pic->data == p_out) {
      dpb_pic->error_info = error_info;
      dpb_pic->cycles_per_mb = cycles;
      if (info->is_field_pic) {
        dpb_pic->error_ratio[0] = error_ratio;
        dpb_pic->error_ratio[1] = error_ratio;
        dpb_pic->pic_code_type[0] = pic_code_type;
        dpb_pic->pic_code_type[1] = pic_code_type;
      } else {
        dpb_pic->error_ratio[info->is_bottom_field] = error_ratio;
        dpb_pic->pic_code_type[info->is_bottom_field] = pic_code_type;
      }
      break;
    }
    tmp++;
  }

  /* update in DPB */
  i = dpb->dpb_size + 1;
  while((i--) > 0) {
    dpbPicture_t *dpb_pic = (dpbPicture_t *)dpb->buffer + i;
    if(dpb_pic->data == p_out) {
      dpb_pic->error_info = error_info;
      dpb_pic->cycles_per_mb = cycles;
      if (info->is_field_pic) {
        dpb_pic->error_ratio[0] = error_ratio;
        dpb_pic->error_ratio[1] = error_ratio;
        dpb_pic->pic_code_type[0] = pic_code_type;
        dpb_pic->pic_code_type[1] = pic_code_type;
      } else {
        dpb_pic->error_ratio[info->is_bottom_field] = error_ratio;
        dpb_pic->pic_code_type[info->is_bottom_field] = pic_code_type;
      }
      break;
    }
  }

  /* update in fb_list */
  pic_info.id = info->out_id;
  pic_info.error_ratio = error_ratio;
  pic_info.cycles = cycles;
  pic_info.is_field_pic = info->is_field_pic;
  pic_info.is_bottom_field = info->is_bottom_field;
  pic_info.pic_code_type = pic_code_type;
  pic_info.error_info = error_info;
  MarkOutputPicInfo(dpb->fb_list, &pic_info);
}

void h264SCMarkOutputPicInfo(struct H264DecContainer *dec_cont, u32 picture_broken) {
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  dpbPicture_t *current_out = dpb->current_out;
  DecAsicBuffers_t *p_asic_buff = dec_cont->asic_buff;
  struct ErrorPicInfo error_pic_info;
  u32 num_err_mbs = 0;
  u32 error_ratio = 0;
  u32 i = 0, j = 0;

  if (dec_cont->rlc_mode) {
    /* only SC mode */
    num_err_mbs = dec_cont->storage.num_err_mbs;
    dec_cont->error_info = num_err_mbs ? DEC_FRAME_ERROR : DEC_NO_ERROR;
  } else {
    /* error_info of mbs_num. */
    if (dec_cont->error_info != DEC_NO_ERROR &&
        dec_cont->error_info != DEC_REF_ERROR) {
      if (dec_cont->hw_conceal)
        num_err_mbs = GetDecRegister(dec_cont->h264_regs, HWIF_TOTAL_ERROR_CTBS);
      else {
        error_pic_info.error_x = GetDecRegister(dec_cont->h264_regs, HWIF_MB_LOCATION_X);
        error_pic_info.error_y = GetDecRegister(dec_cont->h264_regs, HWIF_MB_LOCATION_Y);
        error_pic_info.pic_width_in_ctb  = dec_cont->storage.active_sps->pic_width_in_mbs;
        error_pic_info.pic_height_in_ctb = dec_cont->storage.active_sps->pic_height_in_mbs;
        error_pic_info.log2_ctb_size = 4;
        error_pic_info.tile_info.num_tile_rows    = 1; /* h264 no tile */
        error_pic_info.tile_info.num_tile_columns = 1;
        num_err_mbs = GetErrorCtbCount(&error_pic_info);
      }
      /* the error can be ignored. */
      if (num_err_mbs == 0)
        dec_cont->error_info = DEC_NO_ERROR;
    }
  }
  if (picture_broken) /* skip HW run, 100% error. */
    error_ratio = 1 * EC_ROUND_COEFF;
  else
    error_ratio = num_err_mbs * EC_ROUND_COEFF / dec_cont->storage.pic_size_in_mbs;

  /* check error_info of ref_list */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (dpb->buffer[i].error_info != DEC_NO_ERROR) {
      for (j = 0; j <= dpb->dpb_size; j++) {
        if (dpb->buffer[i].mem_idx == p_asic_buff->ref_mem_idx[j]) {
          dec_cont->error_info |= DEC_REF_ERROR;
          break;
        }
      }
    }
  }

  /* reordering */
  current_out->error_info = dec_cont->error_info;
  current_out->error_ratio[dec_cont->storage.slice_header->bottom_field_flag] = error_ratio;

  /* no-reordering */
  if (dpb->no_reordering) {
    dpbOutPicture_t *dpb_out = &dpb->out_buf[(dpb->out_index_w + dpb->dpb_size) % (dpb->dpb_size + 1)];
    dpb_out->error_info = dec_cont->error_info;
    dpb_out->error_ratio[dec_cont->storage.slice_header->bottom_field_flag] = error_ratio;
  }
}

enum DecRet h264ECDecisionOutput(struct H264DecContainer *dec_cont, H264DecPicture * output) {
  u8 discard_error_pic = 0;

  /* complete output pic EC policy */
  discard_error_pic = (((dec_cont->error_policy & DEC_EC_OUT_NO_ERROR) &&
                        (output->error_info != DEC_NO_ERROR)) ||
                       ((!output->field_picture) &&
                        (dec_cont->error_policy & DEC_EC_OUT_DECISION) &&
                        (output->error_info != DEC_NO_ERROR) &&
                        (output->error_ratio[0] > dec_cont->error_ratio * 100)) ||
                       ((output->field_picture) &&
                        (dec_cont->error_policy & DEC_EC_OUT_DECISION) &&
                        (output->error_info != DEC_NO_ERROR) &&
                        (output->error_ratio[0] > dec_cont->error_ratio * 100 &&
                         output->error_ratio[1] > dec_cont->error_ratio * 100)));
  if (output->error_info != DEC_NO_ERROR) {
    ECErrorInfoReturn(output->error_info, output->error_ratio[0], output->pic_id);
    if (output->field_picture)
      ECErrorInfoReturn(output->error_info, output->error_ratio[1], output->pic_id);
  }
  if (discard_error_pic) {
    /* picture consumed: call API function */
    return H264DecPictureConsumed((void*)dec_cont, output);
  }

  return DEC_PIC_RDY;
}

u32 h264ReplaceRefAvalible(struct H264DecContainer *dec_cont) {
  u32 i = 0;
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  storage_t *storage = &dec_cont->storage;
  u32 curr_poc = GET_POC(*storage->dpb->current_out);

  u32 frame_error_num = 0;

  /* interlace case can't call this function. */

  /* ignore rlc mode. */
  if (dec_cont->rlc_mode)
    return HANTRO_OK;

  /* ref_buffer error info count num */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (IS_REFERENCE_F(dpb->buffer[i])) {
      /* skip self. */
      if (GET_POC(dpb->buffer[i]) == curr_poc)
        continue;

      if (dpb->buffer[i].error_info == DEC_NO_ERROR)
        return HANTRO_OK;
      else if (dpb->buffer[i].error_info == DEC_REF_ERROR)
        return HANTRO_OK;
      else {
        // /* if error_ratio less than 10%, don't replace it, use it as correct. */
        // if (dpb->buffer[i].error_ratio[0] <= EC_RATIO_THRESHOLD)
        //   return HANTRO_OK;
        // else
          frame_error_num++;
      }
    }
  }

  if (frame_error_num != 0)
    return HANTRO_NOK; /* have error_ref can't be replaced */
  else
    return HANTRO_OK; /* ignore this error_ref */
}

enum DecRet H264DecEndOfStream(H264DecInst dec_inst, u32 strm_end_flag) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  u32 count = 0;

  //APITRACE("%s","H264DecEndOfStream#\n");

  if(dec_inst == NULL) {
    APITRACEERR("%s","H264DecEndOfStream# dec_inst is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecEndOfStream# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }
  if(dec_cont->dec_stat == DEC_END_OF_STREAM) {
    return (DEC_OK);
  }

  if (dec_cont->n_cores > 1) {
    if (!dec_cont->vcmd_used) {
      /* Check all Core in idle state */
      for(count = 0; count < dec_cont->n_cores_available; count++) {
        while (dec_cont->dec_status[count] == DEC_RUNNING)
          sched_yield();
      }
    }
  } else {
    if (dec_cont->asic_running) {
      if (dec_cont->vcmd_used) {
        /* abort vcd */
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 1);
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_DIS, 0);
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_ABORT_E, 1);
        DWLWriteRegToHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, dec_cont->h264_regs[1]);
        DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmdbuf_id);
      } else {
        /* stop HW */
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT, 0);
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ, 0);
        SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 0);
        DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                     dec_cont->h264_regs[1] | DEC_IRQ_DISABLE);
        DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);  /* release HW lock */
      }
      dec_cont->asic_running = 0;

      /* Decrement usage for DPB buffers */
      DecrementDPBRefCount(&dec_cont->storage.dpb[1]);
      dec_cont->dec_stat = DEC_INITIALIZED;
      // H264DropCurrentPicutre(dec_cont);
    } else if (dec_cont->keep_hw_reserved) {
      DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);  /* release HW lock */
      dec_cont->keep_hw_reserved = 0;
    }
  }

  if (dec_cont->vcmd_used)
    DWLWaitCmdbufsDone(dec_cont->dwl, dec_inst);

  /* flush any remaining pictures form DPB */
  h264bsdFlushBuffer(&dec_cont->storage);

  FinalizeOutputAll(&dec_cont->fb_list);

  count = 0;
  {
    H264DecPicture output;
    DWLmemset(&output, 0, sizeof(H264DecPicture));
    while(h264DecNextPictureINTERNAL(dec_inst, &output, 1) == DEC_PIC_RDY) {
      DWLmemset(&output, 0, sizeof(H264DecPicture));
      count++;
    }
  }

  /* After all output pictures were pushed, update decoder status to
   * reflect the end-of-stream situation. This way the H264DecMCNextPicture
   * will not block anymore once all output was handled.
   */
  if(strm_end_flag)
    dec_cont->dec_stat = DEC_END_OF_STREAM;

  /* wake-up output thread */
  PushOutputPic(&dec_cont->fb_list, NULL, -1);

  //APITRACE("%s","H264DecEndOfStream# DEC_OK\n");
  return (DEC_OK);
}


void h264SetExternalBufferInfo(H264DecInst dec_inst, storage_t *storage) {
  u32 pic_size_in_mbs = 0, pic_size = 0, dmv_mem_size = 0, ref_buff_size = 0, out_w = 0, out_h = 0;
  u32 qp_mem_size = 0;
  u32 rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 tbl_size = 0;
  struct H264DecContainer *dec_cont = (struct H264DecContainer *)dec_inst;
  seqParamSet_t *sps = storage->active_sps;
  u32 pixel_width = (sps->bit_depth_luma == 8 &&
                     sps->bit_depth_chroma == 8) ? 8 : 10;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));

  pic_size_in_mbs = storage->active_sps->pic_width_in_mbs * storage->active_sps->pic_height_in_mbs;
  out_w = NEXT_MULTIPLE(4 * storage->active_sps->pic_width_in_mbs * 16 *
                        pixel_width / 8, ALIGN(dec_cont->align));
  out_h = storage->active_sps->pic_height_in_mbs * 4;
  pic_size = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
              + (storage->active_sps->mono_chrome ? 0 :
                NEXT_MULTIPLE(((sps->chroma_format_idc==2)?out_w * out_h : out_w * out_h / 2), ref_buffer_align));
  dmv_mem_size = NEXT_MULTIPLE((pic_size_in_mbs + 32) *
                 (dec_cont->high10p_mode ? 80 : 64), ref_buffer_align);

  if(storage->qp_output_enable)
    qp_mem_size = NEXT_MULTIPLE(storage->active_sps->pic_width_in_mbs,  64)*storage->active_sps->pic_height_in_mbs;
  else
    qp_mem_size = 0;
  H264GetRefFrmSize(storage, &rfc_luma_size, &rfc_chroma_size);
  tbl_size = NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align)
             + NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);

  ref_buff_size = pic_size  + dmv_mem_size
                  + NEXT_MULTIPLE(32, ref_buffer_align)
                  + tbl_size;

  if (!dec_cont->pp_enabled)
    ref_buff_size += qp_mem_size;

  u32 min_buffer_num, max_dpb_size, no_reorder, tot_buffers;
  u32 ext_buffer_size;
  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;

  if(storage->no_reordering ||
      storage->active_sps->pic_order_cnt_type == 2 ||
      (storage->active_sps->vui_parameters_present_flag &&
       storage->active_sps->vui_parameters->bitstream_restriction_flag &&
       !storage->active_sps->vui_parameters->num_reorder_frames))
    no_reorder = HANTRO_TRUE;
  else
    no_reorder = HANTRO_FALSE;

  if(storage->view == 0)
    max_dpb_size = storage->active_sps->max_dpb_size;
  else {
    /* stereo view dpb size at least equal to base view size (to make sure
     * that base view pictures get output in correct display order) */
    max_dpb_size = MAX(storage->active_sps->max_dpb_size, storage->active_view_sps[0]->max_dpb_size);
  }
  /* restrict max dpb size of mvc (stereo high) streams, make sure that
   * base address 15 is available/restricted for inter view reference use */
  if(storage->mvc_stream)
    max_dpb_size = MIN(max_dpb_size, 8);

  tot_buffers = max_dpb_size + 1;
  if(no_reorder) {
    tot_buffers = MAX(storage->active_sps->num_ref_frames,1) + 1;
    if(dec_cont->pp_enabled)
      tot_buffers = 1 + 1; /* one is output, one is decode */
  }

  if (dec_cont->skip_non_intra && !storage->mvc_stream) {
    tot_buffers = 2;
  }

  /* TODO(min): add extra 10 buffers for top simulation guard buffers.
     To be commented after verification */
#if defined(ASIC_TRACE_SUPPORT) && defined(SUPPORT_MULTI_CORE)
    tot_buffers += 10;
#endif
  if (dec_cont->n_cores == 1) {
    /* single core configuration */
    if (storage->use_smoothing)
      tot_buffers += no_reorder ? 1 : tot_buffers;
  } else {
    /* multi core configuration */

    if (storage->use_smoothing && !no_reorder) {
      /* at least double buffers for smooth output */
      if (tot_buffers > dec_cont->n_cores) {
        tot_buffers *= 2;
      } else {
        tot_buffers += dec_cont->n_cores;
      }
    } else {
      /* one extra buffer for each core */
      /* do not allocate twice for multiview */
      if(!storage->view)
        tot_buffers += dec_cont->n_cores;
    }
  }
  if(tot_buffers > MAX_PIC_BUFFERS)
    tot_buffers = MAX_PIC_BUFFERS;

  min_buffer_num = tot_buffers;
  ext_buffer_size =  ref_buff_size;

  if (dec_cont->pp_enabled) {
    ext_buffer_size = dec_cont->auxinfo_offset =
        CalcPpUnitBufferSize(ppu_cfg, storage->active_sps->mono_chrome);
    ext_buffer_size += qp_mem_size;
  }

  dec_cont->buf_num = min_buffer_num;
  dec_cont->next_buf_size = ext_buffer_size;
}

void h264SetMVCExternalBufferInfo(H264DecInst dec_inst, storage_t *storage) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *)dec_inst;
  u32 pic_size_in_mbs, pic_size, out_w1, out_h1, out_w2, out_h2, tbl_size;
  u32 qp_mem_size = 0;
  u32 rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 min_buffer_num;
  u32 ext_buffer_size, ref_buff_size;
  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
  seqParamSet_t *sps = storage->active_sps;
  u32 pixel_width = (sps->bit_depth_luma == 8 &&
                     sps->bit_depth_chroma == 8) ? 8 : 10;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));

  if(storage->sps[1] != 0)
    pic_size_in_mbs = MAX(storage->sps[0]->pic_width_in_mbs * storage->sps[0]->pic_height_in_mbs,
                          storage->sps[1]->pic_width_in_mbs * storage->sps[1]->pic_height_in_mbs);
  else
    pic_size_in_mbs = storage->sps[0]->pic_width_in_mbs * storage->sps[0]->pic_height_in_mbs;
  if(storage->sps[1] != 0) {
    out_w1 = NEXT_MULTIPLE(4 * storage->sps[0]->pic_width_in_mbs * 16 *
                            pixel_width / 8, ALIGN(dec_cont->align));
    out_h1 = storage->sps[0]->pic_height_in_mbs * 4;
    out_w2 = NEXT_MULTIPLE(4 * storage->sps[1]->pic_width_in_mbs * 16 *
                            pixel_width / 8, ALIGN(dec_cont->align));
    out_h2 = storage->sps[1]->pic_height_in_mbs * 4;
    pic_size = NEXT_MULTIPLE(MAX(out_w1 * out_h1, out_w2 * out_h2), ref_buffer_align)
                + (storage->sps[0]->mono_chrome ? 0 :
                  NEXT_MULTIPLE(MAX(out_w1 * out_h1, out_w2 * out_h2) / 2, ref_buffer_align));
  } else {
    out_w1 = NEXT_MULTIPLE(4 * storage->sps[0]->pic_width_in_mbs * 16, ALIGN(dec_cont->align));
    out_h1 = storage->sps[0]->pic_height_in_mbs * 4;
    pic_size = NEXT_MULTIPLE(out_w1 * out_h1, ref_buffer_align)
               + (storage->sps[0]->mono_chrome ? 0 :
                 NEXT_MULTIPLE(out_w1 * out_h1 / 2, ref_buffer_align));
  }

  if(storage->qp_output_enable)
    qp_mem_size = NEXT_MULTIPLE(storage->active_sps->pic_width_in_mbs,  64)*storage->active_sps->pic_height_in_mbs;
  else
    qp_mem_size = 0;

  H264GetRefFrmSize(storage, &rfc_luma_size, &rfc_chroma_size);
  tbl_size = NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align)
             + NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);

  /* buffer size of dpb pic = pic_size + dir_mv_size + tbl_size */
  u32 dmv_mem_size = NEXT_MULTIPLE((pic_size_in_mbs + 32) * (dec_cont->high10p_mode ? 80 : 64), ref_buffer_align);
  ref_buff_size = pic_size  + dmv_mem_size
                  + NEXT_MULTIPLE(32, ref_buffer_align) + tbl_size;

  if (!dec_cont->pp_enabled) {
    ref_buff_size += qp_mem_size;
  }

  min_buffer_num = 0;
  u32 j = 0;
  for(u32 i = 0; i < 2; i ++) {
    u32 max_dpb_size, no_reorder, tot_buffers;
    if(storage->no_reordering ||
        storage->sps[j]->pic_order_cnt_type == 2 ||
        (storage->sps[j]->vui_parameters_present_flag &&
         storage->sps[j]->vui_parameters->bitstream_restriction_flag &&
         !storage->sps[j]->vui_parameters->num_reorder_frames))
      no_reorder = HANTRO_TRUE;
    else
      no_reorder = HANTRO_FALSE;

    max_dpb_size = storage->sps[j]->max_dpb_size;

    /* restrict max dpb size of mvc (stereo high) streams, make sure that
    * base address 15 is available/restricted for inter view reference use */
    max_dpb_size = MIN(max_dpb_size, 8);

    if(no_reorder)
      tot_buffers = MAX(storage->sps[j]->num_ref_frames, 1) + 1;
    else
      tot_buffers = max_dpb_size + 1;

    /* TODO(min): add extra 10 buffers for top simulation guard buffers.
       To be commented after verification */
#if defined(ASIC_TRACE_SUPPORT) && defined(SUPPORT_MULTI_CORE)
      tot_buffers += 10;
#endif

    min_buffer_num += tot_buffers;
    if(storage->sps[1] != 0)
      j ++;
  }

  ext_buffer_size =  ref_buff_size;

  if (dec_cont->pp_enabled) {
    ext_buffer_size = dec_cont->auxinfo_offset =
        CalcPpUnitBufferSize(ppu_cfg, storage->active_sps->mono_chrome);
    ext_buffer_size += qp_mem_size;
  }

  dec_cont->buf_num = min_buffer_num;
  dec_cont->next_buf_size = ext_buffer_size;
  if(dec_cont->buf_num > MAX_PIC_BUFFERS)
    dec_cont->buf_num = MAX_PIC_BUFFERS;
}


enum DecRet H264DecGetBufferInfo(H264DecInst dec_inst, struct DecBufferInfo *mem_info) {
  struct H264DecContainer  * dec_cont = (struct H264DecContainer *)dec_inst;

  struct DWLLinearMem empty;
  (void)DWLmemset(&empty, 0, sizeof(struct DWLLinearMem));
  struct DWLLinearMem *buffer = NULL;
  u32 i;

  if(dec_cont == NULL || mem_info == NULL) {
    return DEC_PARAM_ERROR;
  }

  (void) DWLmemset(mem_info, 0, sizeof(struct DecBufferInfo));

  if (!dec_cont->pp_enabled) {
    storage_t *storage = &dec_cont->storage;
    u32 bit_depth = (storage->active_sps->bit_depth_luma == 8 && storage->active_sps->bit_depth_chroma == 8) ? 8 : 10;
    if (!dec_cont->use_video_compressor) {
      mem_info->cstride[0] = mem_info->ystride[0] =
                             NEXT_MULTIPLE(storage->active_sps->pic_width_in_mbs * 16 * bit_depth * 4, ALIGN(dec_cont->align) * 8) / 8;
    } else {
      mem_info->ystride[0] = mem_info->cstride[0] = storage->active_sps->pic_width_in_mbs * 16 * bit_depth * 4 / 8;
    }
  } else {
    for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
      if (!dec_cont->ppu_cfg[i].enabled) continue;
      mem_info->ystride[i] = dec_cont->ppu_cfg[i].ystride;
      mem_info->cstride[i] = dec_cont->ppu_cfg[i].cstride;
    }
  }

  if (dec_cont->storage.release_buffer) {
    /* Release old buffers from input queue. */
    //buffer = InputQueueGetBuffer(dec_cont->pp_buffer_queue, 0);
    buffer = NULL;
    if (dec_cont->ext_buffer_num) {
      buffer = &dec_cont->ext_buffers[dec_cont->ext_buffer_num - 1];
      dec_cont->ext_buffer_num--;
    }
    if (buffer == NULL) {
      /* All buffers have been released. */
      dec_cont->storage.release_buffer = 0;
      InputQueueRelease(dec_cont->pp_buffer_queue);
      dec_cont->pp_buffer_queue = InputQueueInit(0);
      if (dec_cont->pp_buffer_queue == NULL) {
        return (DEC_MEMFAIL);
      }
      dec_cont->storage.pp_buffer_queue = dec_cont->pp_buffer_queue;
      dec_cont->storage.ext_buffer_added = 0;
      mem_info->buf_to_free = empty;
      mem_info->next_buf_size = dec_cont->next_buf_size;
      mem_info->buf_num = dec_cont->buf_num + dec_cont->n_guard_size;
      return (DEC_OK);
    } else {
      mem_info->buf_to_free = *buffer;
      mem_info->next_buf_size = 0;
      mem_info->buf_num = 0;
      return DEC_WAITING_FOR_BUFFER;
    }
  }

  if(dec_cont->buf_to_free == NULL && dec_cont->next_buf_size == 0) {
    /* External reference buffer: release done. */
    mem_info->buf_to_free = empty;
    mem_info->next_buf_size = dec_cont->next_buf_size;
    mem_info->buf_num = dec_cont->buf_num + dec_cont->n_guard_size;
    return DEC_OK;
  }

  if(dec_cont->buf_to_free) {
    mem_info->buf_to_free = *dec_cont->buf_to_free;
    dec_cont->buf_to_free->virtual_address = NULL;
    dec_cont->buf_to_free->bus_address = 0;
    dec_cont->buf_to_free = NULL;
  } else
    mem_info->buf_to_free = empty;

  mem_info->next_buf_size = dec_cont->next_buf_size;
  mem_info->buf_num = dec_cont->buf_num + dec_cont->n_guard_size;

  ASSERT((mem_info->buf_num && mem_info->next_buf_size) ||
         (DWL_DEVMEM_VAILD(mem_info->buf_to_free)));

  return DEC_WAITING_FOR_BUFFER;
}

enum DecRet H264DecAddBuffer(H264DecInst dec_inst, struct DWLLinearMem *info) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *)dec_inst;
  enum DecRet dec_ret = DEC_OK;

  if(dec_inst == NULL || info == NULL ||
#ifndef MEM_ONLY_DEV_CHECK
      X170_CHECK_VIRTUAL_ADDRESS(info->virtual_address) ||
#endif
      X170_CHECK_BUS_ADDRESS_AGLINED(info->bus_address) ||
      info->size < dec_cont->next_buf_size) {
    return DEC_PARAM_ERROR;
  }

  dec_cont->n_ext_buf_size = dec_cont->storage.ext_buffer_size = info->size;
  dec_cont->ext_buffers[dec_cont->ext_buffer_num] = *info;
  dec_cont->ext_buffer_num++;
  dec_cont->storage.ext_buffer_added = 1;
  if (dec_cont->ext_buffer_num < dec_cont->buf_num)
    dec_ret = DEC_WAITING_FOR_BUFFER;

  if(!dec_cont->b_mvc) {
    u32 i = dec_cont->buffer_index[0];
    u32 id;
    dpbStorage_t *dpb = dec_cont->storage.dpbs[0];
    if (dec_cont->pp_enabled == 0) {
      if(i < dpb->tot_buffers) {
        dpb->pic_buffers[i] = *info;
        if (dec_cont->storage.dpbs[0]->n_ext_buf_size_added < info->size)
          dec_cont->storage.dpbs[0]->n_ext_buf_size_added = info->size;
        if(i < dpb->dpb_size + 1) {
          id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + i);
          if(id == FB_NOT_VALID_ID) {
            return MEMORY_ALLOCATION_ERROR;
          }

          dpb->buffer[i].data = dpb->pic_buffers + i;
          dpb->buffer[i].mem_idx = id;
          dpb->buffer[i].error_ratio[0] = 0;
          dpb->buffer[i].error_ratio[1] = 0;
          dpb->pic_buff_id[i] = id;
        } else {
          id = AllocateIdFree(dpb->fb_list, dpb->pic_buffers + i);
          if(id == FB_NOT_VALID_ID) {
            return MEMORY_ALLOCATION_ERROR;
          }

          dpb->pic_buff_id[i] = id;
        }

#ifndef MEM_ONLY_DEV_CHECK
        void *base =
          (char *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset;
        (void)DWLmemset(base, 0, info->size - dpb->dir_mv_offset);
#endif

        dec_cont->buffer_index[0]++;
        if(dec_cont->buffer_index[0] < dpb->tot_buffers)
          dec_ret = DEC_WAITING_FOR_BUFFER;
      } else {
        /* Adding extra buffers. */
        if(dec_cont->buffer_index[0] >= MAX_PIC_BUFFERS) {
          /* Too much buffers added. */
          dec_cont->ext_buffer_num--;
          return DEC_EXT_BUFFER_REJECTED;
        }

        dpb->pic_buffers[i] = *info;
        dpb[1].pic_buffers[i] = *info;
        /* Need the allocate a USED id to be added as free buffer in SetFreePicBuffer. */
        id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + i);
        if(id == FB_NOT_VALID_ID) {
          return MEMORY_ALLOCATION_ERROR;
        }
        dpb->pic_buff_id[i] = id;
        dpb[1].pic_buff_id[i] = id;

#ifndef MEM_ONLY_DEV_CHECK
        void *base =
          (char *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset;
        (void)DWLmemset(base, 0, info->size - dpb->dir_mv_offset);
#endif

        dec_cont->buffer_index[0]++;
        dpb->tot_buffers++;
        dpb[1].tot_buffers++;

        SetFreePicBuffer(dpb->fb_list, id);
      }
    } else {
      /* Add down scale buffer. */
      InputQueueAddBuffer(dec_cont->pp_buffer_queue, info);
    }
  } else {
    u32 * idx = dec_cont->buffer_index;
    if (dec_cont->pp_enabled == 0) {
      if(idx[0] < dec_cont->storage.dpbs[0]->tot_buffers || idx[1] < dec_cont->storage.dpbs[1]->tot_buffers) {
        for(u32 i = 0; i < 2; i ++) {
          u32 id;
          dpbStorage_t *dpb = dec_cont->storage.dpbs[i];
          if(idx[i] < dpb->tot_buffers) {
            dpb->pic_buffers[idx[i]] = *info;
            if(idx[i] < dpb->dpb_size + 1) {
              id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + idx[i]);
              if(id == FB_NOT_VALID_ID) {
                return MEMORY_ALLOCATION_ERROR;
              }

              dpb->buffer[idx[i]].data = dpb->pic_buffers + idx[i];
              dpb->buffer[idx[i]].mem_idx = id;
              dpb->pic_buff_id[idx[i]] = id;
            } else {
              id = AllocateIdFree(dpb->fb_list, dpb->pic_buffers + idx[i]);
              if(id == FB_NOT_VALID_ID) {
                return MEMORY_ALLOCATION_ERROR;
              }

              dpb->pic_buff_id[idx[i]] = id;
            }

#ifndef MEM_ONLY_DEV_CHECK
            void *base =
              (char *)(dpb->pic_buffers[idx[i]].virtual_address) + dpb->dir_mv_offset;
            (void)DWLmemset(base, 0, info->size - dpb->dir_mv_offset);
#endif

            dec_cont->buffer_index[i]++;
            if(dec_cont->buffer_index[i] < dpb->tot_buffers)
              dec_ret = DEC_WAITING_FOR_BUFFER;
            break;
          }
        }
      } else {
        /* Adding extra buffers. */
        if((idx[0] + idx[1]) >= MAX_PIC_BUFFERS) {
          /* Too much buffers added. */
          dec_cont->ext_buffer_num--;
          return DEC_EXT_BUFFER_REJECTED;
        }
        u32 i = idx[0] < idx[1] ? 0 : 1;
        dpbStorage_t *dpb = dec_cont->storage.dpbs[i];
        dpb->pic_buffers[idx[i]] = *info;
        /* Need the allocate a USED id to be added as free buffer in SetFreePicBuffer. */
        u32 id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + idx[i]);
        if(id == FB_NOT_VALID_ID) {
          return MEMORY_ALLOCATION_ERROR;
        }
        dpb->pic_buff_id[idx[i]] = id;

#ifndef MEM_ONLY_DEV_CHECK
        void *base =
          (char *)(dpb->pic_buffers[idx[i]].virtual_address) + dpb->dir_mv_offset;
        (void)DWLmemset(base, 0, info->size - dpb->dir_mv_offset);
#endif

        dec_cont->buffer_index[i]++;
        dpb->tot_buffers++;

        SetFreePicBuffer(dpb->fb_list, id);
      }
    }else {
      /* Add down scale buffer. */
      InputQueueAddBuffer(dec_cont->pp_buffer_queue, info);
    }
  }

  return dec_ret;
}


void h264EnterAbortState(struct H264DecContainer *dec_cont) {
  SetAbortStatusInList(&dec_cont->fb_list);
  if (dec_cont->pp_enabled)
    InputQueueSetAbort(dec_cont->pp_buffer_queue);
  dec_cont->abort = 1;
}

void h264ExistAbortState(struct H264DecContainer *dec_cont) {
  ClearAbortStatusInList(&dec_cont->fb_list);
  if (dec_cont->pp_enabled)
    InputQueueClearAbort(dec_cont->pp_buffer_queue);
  dec_cont->abort = 0;
}

void h264StateReset(struct H264DecContainer *dec_cont) {
  dpbStorage_t *dpb = dec_cont->storage.dpbs[0];

  /* Clear parameters in dpb */
  h264EmptyDpb(dpb);
  if (dec_cont->storage.mvc_stream) {
    dpb = dec_cont->storage.dpbs[1];
    h264EmptyDpb(dpb);
  }

  /* Clear parameters in storage */
  h264bsdClearStorage(&dec_cont->storage);

  /* Clear parameters in decContainer */
  dec_cont->dec_stat = DEC_INITIALIZED;
  dec_cont->start_code_detected = 0;
  dec_cont->pic_number = 0;
#ifdef CLEAR_HDRINFO_IN_SEEK
  dec_cont->rlc_mode = 0;
  dec_cont->try_vlc = 0;
  dec_cont->mode_change = 0;
#endif
  dec_cont->reallocate = 0;
  dec_cont->gaps_checked_for_this = 0;
  dec_cont->packet_decoded = 0;
  dec_cont->keep_hw_reserved = 0;
  dec_cont->force_nal_mode = 0;
#ifdef USE_OMXIL_BUFFER
  dec_cont->buffer_index[0] = 0;
  dec_cont->buffer_index[1] = 0;
  dec_cont->ext_buffer_num = 0;
#endif

#ifdef SKIP_OPENB_FRAME
  dec_cont->entry_is_IDR = 0;
  dec_cont->entry_POC = 0;
  dec_cont->first_entry_point = 0;
  dec_cont->skip_b = 0;
#endif

  dec_cont->alloc_buffer = 0;
  dec_cont->pre_alloc_buffer[0] =
    dec_cont->pre_alloc_buffer[1] = 0;
  dec_cont->no_decoding_buffer = 0;
  if (dec_cont->pp_enabled)
    InputQueueReset(dec_cont->pp_buffer_queue);
}

enum DecRet H264DecAbort(H264DecInst dec_inst) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  if(dec_inst == NULL) {
    APITRACEERR("%s","H264DecAbort# dec_inst is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecAbort# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  pthread_mutex_lock(&dec_cont->protect_mutex);
  /* Abort frame buffer waiting and rs/ds buffer waiting */
  h264EnterAbortState(dec_cont);
  pthread_mutex_unlock(&dec_cont->protect_mutex);
  return (DEC_OK);
}

enum DecRet H264DecAbortAfter(H264DecInst dec_inst) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  u32 i;
  i32 core_id[MAX_ASIC_CORES];
  struct DWLReqInfo info = {0};
  const seqParamSet_t *p_sps = dec_cont->storage.active_sps;

  if(dec_inst == NULL) {
    APITRACEERR("%s","H264DecAbortAfter# dec_inst is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecAbortAfter# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  pthread_mutex_lock(&dec_cont->protect_mutex);

#if 0
  /* If normal EOS is waited, return directly */
  if(dec_cont->dec_stat == DEC_END_OF_STREAM) {
    pthread_mutex_unlock(&dec_cont->protect_mutex);
    return (DEC_OK);
  }
#endif

  if(dec_cont->asic_running && !dec_cont->b_mc) {
    /* stop HW */
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ_STAT, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_IRQ, 0);
    SetDecRegister(dec_cont->h264_regs, HWIF_DEC_E, 0);
    if(!dec_cont->vcmd_used) {
      DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                  dec_cont->h264_regs[1] | DEC_IRQ_DISABLE);
      DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);  /* release HW lock */
    }
    else {
      DWLWaitCmdbufsDone(dec_cont->dwl, dec_inst);
    }
    DecrementDPBRefCount(dec_cont->storage.dpb);
    dec_cont->asic_running = 0;

  }

  /* In multi-Core senario, waithwready is executed through listener thread,
          here to check whether HW is finished */
  if(dec_cont->b_mc) {
    if(!dec_cont->vcmd_used) {
      info.core_mask = dec_cont->core_mask;
      info.width = p_sps->pic_width_in_mbs * 16;
      info.height = p_sps->pic_height_in_mbs * 16;
      for(i = 0; i < dec_cont->n_cores_available; i++) {
        DWLReserveHw(dec_cont->dwl, &info, &core_id[i]);
      }
      /* All HW Core finished */
      for(i = 0; i < dec_cont->n_cores_available; i++) {
        DWLReleaseHw(dec_cont->dwl, core_id[i]);
      }
    }
    else {
      DWLWaitCmdbufsDone(dec_cont->dwl, dec_inst);
    }
  }


  /* Clear internal parameters */
  h264StateReset(dec_cont);
  h264ExistAbortState(dec_cont);

#ifdef USE_OMXIL_BUFFER
  pthread_mutex_lock(&dec_cont->fb_list.ref_count_mutex);
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    dec_cont->fb_list.fb_stat[i].n_ref_count = 0;
  }
  pthread_mutex_unlock(&dec_cont->fb_list.ref_count_mutex);
#endif

  pthread_mutex_unlock(&dec_cont->protect_mutex);
  return (DEC_OK);
}

enum DecRet H264DecSetNoReorder(H264DecInst dec_inst, u32 no_output_reordering) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  if(dec_inst == NULL) {
    APITRACEERR("%s","H264DecSetNoReorder# dec_inst is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check for valid decoder instance */
  if(dec_cont->checksum != dec_cont) {
    APITRACEERR("%s","H264DecSetNoReorder# Decoder not initialized\n");
    return (DEC_NOT_INITIALIZED);
  }

  pthread_mutex_lock(&dec_cont->protect_mutex);

  dec_cont->storage.no_reordering = no_output_reordering;
  if(dec_cont->storage.dpb != NULL)
    dec_cont->storage.dpb->no_reordering = no_output_reordering;

  pthread_mutex_unlock(&dec_cont->protect_mutex);
  return (DEC_OK);
}

enum DecRet H264DecSetInfo(H264DecInst dec_inst,
                          struct H264DecConfig *dec_cfg) {

  /*@null@ */ struct H264DecContainer *dec_cont = (struct H264DecContainer *)dec_inst;
  storage_t *storage = &dec_cont->storage;
  const seqParamSet_t *p_sps = dec_cont->storage.active_sps;
  u32 pic_width = h264bsdPicWidth(storage) << 4;
  u32 pic_height = h264bsdPicHeight(storage) << 4;
  u32 i = 0;
  u32 shaper_alignment = 0;

  const struct DecHwFeatures *hw_feature = NULL;
  seqParamSet_t *sps = storage->active_sps;
  u32 pixel_width = (sps->bit_depth_luma == 8 &&
                     sps->bit_depth_chroma == 8) ? 8 : 10;

  //APITRACE("%s","H264DecSetInfo#\n");
  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);
  /* TODO: Add valication check here. */

  shaper_alignment = (u32)hw_feature->shaper_alignment;
  /* ref aligment */
  dec_cont->align = storage->align = dec_cfg->align;
  /* ppu alignment */
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    dec_cfg->ppu_cfg[i].align = dec_cfg->align;
    if ((u32)dec_cfg->ppu_cfg[i].align < shaper_alignment) {
      if (dec_cfg->ppu_cfg[i].dec400_enabled) {
        dec_cfg->ppu_cfg[i].align = shaper_alignment;
      } else {
        dec_cfg->ppu_cfg[i].shaper_no_pad = 1;
      }
    }
  }

#ifdef MODEL_SIMULATION
  cmodel_ref_buf_alignment = MAX(16, ALIGN(dec_cont->align));
#endif

  PpUnitSetIntConfig(dec_cont->ppu_cfg, dec_cfg->ppu_cfg, pixel_width,
                     p_sps->frame_mbs_only_flag,
                     storage->active_sps->mono_chrome);

  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cont->ppu_cfg[i].lanczos_table.virtual_address == NULL) {
      u32 size = LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16) * dec_cont->n_cores;
      dec_cont->ppu_cfg[i].lanczos_table.mem_type |= DWL_MEM_TYPE_DMA_HOST_TO_DEVICE;
      i32 ret = DWLMallocLinear(dec_cont->dwl, size, &dec_cont->ppu_cfg[i].lanczos_table);
      if (ret != 0)
        return(DEC_MEMFAIL);
    }
  }
  if (CheckPpUnitConfig(hw_feature, pic_width, pic_height,
                        !p_sps->frame_mbs_only_flag, pixel_width,
                        storage->active_sps->chroma_format_idc, dec_cont->ppu_cfg))
    return DEC_PARAM_ERROR;

  memcpy(dec_cont->delogo_params, dec_cfg->delogo_params, sizeof(dec_cont->delogo_params));
  if (CheckDelogo(dec_cont->delogo_params, sps->bit_depth_luma, sps->bit_depth_chroma))
    return DEC_PARAM_ERROR;

  /* config error process policy. */
  if (dec_cont->error_handling == DEC_EC_FRAME_TOLERANT_ERROR) {
    if (dec_cfg->hw_conceal)
      dec_cont->error_policy = DEC_EC_PIC_HWEC | DEC_EC_REF_ERROR_IGNORE | DEC_EC_NO_SKIP | DEC_EC_OUT_DECISION;
    else
      dec_cont->error_policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_REPLACE | DEC_EC_NO_SKIP | DEC_EC_OUT_DECISION;
  } else if (dec_cont->error_handling == DEC_EC_FRAME_IGNORE_ERROR) {
    if (dec_cfg->hw_conceal)
      dec_cont->error_policy = DEC_EC_PIC_HWEC | DEC_EC_REF_ERROR_IGNORE | DEC_EC_NO_SKIP | DEC_EC_OUT_ALL;
    else
      dec_cont->error_policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_REPLACE_ANYWAY | DEC_EC_NO_SKIP | DEC_EC_OUT_ALL;
  } else {
    dec_cont->error_policy = DEC_EC_PIC_NO_RECOVERY | DEC_EC_REF_RESET | DEC_EC_SEEK_NEXT_I | DEC_EC_OUT_NO_ERROR;
    dec_cfg->hw_conceal = 0;
    APITRACEDEBUG("%s","H264DecSetInfo# DON'T SUPPORT HWEC IN NO ERROR POLICY.\n");
  }
  if (dec_cont->b_mc && dec_cont->error_handling) {
    if (dec_cont->error_policy & DEC_EC_SEEK_NEXT_I ||
        dec_cont->error_policy & DEC_EC_REF_RESET ||
        dec_cont->error_policy & DEC_EC_REF_REPLACE ||
        dec_cont->error_policy & DEC_EC_REF_REPLACE_ANYWAY) {
      APITRACEERR("%s","DON'T SUPPORT THIS ERROR POLICY IN MC MODE.\n");
      return DEC_PARAM_ERROR;
    }
  }

  /* config HWEC. */
  dec_cont->hw_conceal = (dec_cfg->hw_conceal && dec_cont->high10p_mode) ? dec_cfg->hw_conceal : 0;
  /* config slice mode. */
  if (!dec_cont->disable_slice_mode)
    dec_cont->disable_slice_mode = dec_cfg->disable_slice_mode;

  if (dec_cont->b_mc &&
      dec_cont->hw_conceal &&
      !dec_cont->disable_slice_mode) {
    APITRACEERR("%s","H264DecSetInfo# Don't support slice_level_ec in MC mode.\n");
    return DEC_PARAM_ERROR;
  }

  /* config max temporal layer to decoding */
  dec_cont->max_temporal_layer = dec_cfg->max_temporal_layer;
  if (dec_cont->max_temporal_layer < -1 || dec_cont->max_temporal_layer > 7) {
    APITRACEERR("%s","H264DecSetInfo# THE VALUE OF TEMPORAL LAYER ID SHALL BE IN THE RANGE OF -1 TO 7 IN H264.\n");
    return DEC_PARAM_ERROR;
  }

  dec_cont->pp_enabled = 0;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++)
    dec_cont->pp_enabled |= dec_cont->ppu_cfg[i].enabled;

  storage->pp_enabled = dec_cont->pp_enabled;

  return (DEC_OK);
}

void H264DecUpdateStrmInfoCtrl(H264DecInst dec_inst, struct strmInfo info) {
  struct H264DecContainer *dec_cont = (struct H264DecContainer *) dec_inst;
  static u32 len_update = 1;
  struct LLStrmInfo *llstrminfo = &dec_cont->llstrminfo;
  llstrminfo->stream_info = info;
  if (llstrminfo->update_reg_flag) {
    /* wait for hw ready if it's the first time to update length register */
    if (llstrminfo->first_update) {
      while (!dec_cont->asic_running)
        sched_yield();
      llstrminfo->first_update = 0;
      llstrminfo->ll_strm_len = 0;
      len_update = 1;
    }

    SwUpdateStrmInfoCtrl(info.strm_bus_addr, llstrminfo->strm_status_addr,
                         &llstrminfo->ll_strm_bus_address, &llstrminfo->ll_strm_len,
                         info.last_flag, &len_update);

    /* check hw status */
    if (!llstrminfo->first_update && !dec_cont->asic_running) {
      llstrminfo->tmp_length = llstrminfo->ll_strm_len;
      llstrminfo->update_reg_flag = 0;
      llstrminfo->updated_reg = 1;
    }
  }
}

void h264MCPushOutputAll(struct H264DecContainer *dec_cont) {
  u32 ret;
  H264DecPicture output;
  do {
    DWLmemset(&output, 0, sizeof(H264DecPicture));
    ret = h264DecNextPictureINTERNAL(dec_cont, &output, 0);
  } while( ret == DEC_PIC_RDY );
}

void h264MCWaitOutFifoEmpty(struct H264DecContainer *dec_cont) {
  WaitOutputEmpty(&dec_cont->fb_list);
}

void h264MCWaitPicReadyAll(struct H264DecContainer *dec_cont) {
#ifdef USE_OMXIL_BUFFER
  if (!dec_cont->pp_enabled) {
    MarkListNotInUse(&dec_cont->fb_list);
  }
#endif
  WaitListNotInUse(&dec_cont->fb_list);
}

void h264MCSetRefPicStatus(volatile u8 *p_sync_mem, u32 is_field_pic,
                           u32 is_bottom_field) {
  if (is_field_pic == 0) {
    /* frame status */
    DWLmemset((void*)p_sync_mem, 0xFF, 32);
  } else if (is_bottom_field == 0) {
    /* top field status */
    DWLmemset((void*)p_sync_mem, 0xFF, 16);
  } else {
    /* bottom field status */
    p_sync_mem += 16;
    DWLmemset((void*)p_sync_mem, 0xFF, 16);
  }
}

static u32 MCGetRefPicStatus(const u8 *p_sync_mem, u32 is_field_pic,
                             u32 is_bottom_field, u32 high10p_mode) {
  u32 ret;

  /* LE for vcd H264 */
  if (high10p_mode)
    ret = ( p_sync_mem[1] << 8) + p_sync_mem[0];
  else {
    if (is_field_pic == 0) {
      /* frame status */
      ret = ( p_sync_mem[0] << 8) + p_sync_mem[1];
    } else if (is_bottom_field == 0) {
      /* top field status */
      ret = ( p_sync_mem[0] << 8) + p_sync_mem[1];
    } else {
      /* bottom field status */
      p_sync_mem += 16;
      ret = ( p_sync_mem[0] << 8) + p_sync_mem[1];
    }
  }
  return ret;
}

static void MCValidateRefPicStatus(const u32 *h264_regs,
                                   H264HwRdyCallbackArg *info) {
  const u8* p_ref_stat;
  const struct DWLLinearMem *p_dmv_out;
  const dpbStorage_t *dpb = info->current_dpb;
  storage_t *storage = dpb->storage;
  u32 status, expected;
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_H264_DEC, (const void **)&hw_feature);

  p_dmv_out = &dpb->dmv_buffers[info->dmv_out_id];

  if (info->is_high10_mode)
    p_ref_stat = (u8*)p_dmv_out->virtual_address - 32;
  else
    p_ref_stat = (u8*)p_dmv_out->virtual_address + storage->dmv_mem_size;

  status = MCGetRefPicStatus(p_ref_stat, info->is_field_pic,
      info->is_bottom_field, info->is_high10_mode);


  expected = (GetDecRegister(h264_regs, HWIF_PIC_HEIGHT_IN_CBS) + 1) >> 1;


  expected *= 16;

  if(info->is_field_pic)
    expected /= 2;

  if(status < expected) {
    ASSERT(status == expected);
#ifndef MEM_ONLY_DEV_CHECK
    h264MCSetRefPicStatus((u8*)p_ref_stat,
                          info->is_field_pic, info->is_bottom_field);
#endif
#ifdef SUPPORT_DMA
  if (info->is_high10_mode)
    DWLDMATransData((addr_t)((u8*)p_dmv_out->bus_address - 32),
                    (void *)((u8*)p_dmv_out->virtual_address - 32),
                    32, HOST_TO_DEVICE);
  else
    DWLDMATransData((addr_t)((u8*)p_dmv_out->bus_address + storage->dmv_mem_size),
                    (void *)((u8*)p_dmv_out->virtual_address + storage->dmv_mem_size),
                    32, HOST_TO_DEVICE);
#endif
  }
}

/* core_id: for vcmd, it's cmd buf id; otherwise, it's real core id. */
void h264MCHwRdyCallback(void *args, i32 core_id) {
  u32 dec_regs[DEC_X170_REGISTERS];

  struct H264DecContainer *dec_cont = (struct H264DecContainer *)args;
  H264HwRdyCallbackArg info;

  const void *dwl = NULL;
  const dpbStorage_t *dpb = NULL;

  u32 core_status = 0;
  u32 type = 0;
  u32 i = 0, cmdbuf_id = 0xFFFFFF;
  struct DWLLinearMem *p_out = NULL;
  struct DWLLinearMem *p_dmv_out = NULL;
  enum DecErrorInfo error_info = DEC_NO_ERROR;

#ifdef FPGA_PERF_AND_BW
  u32 pic_size = h264bsdPicWidth(&dec_cont->storage) * h264bsdPicHeight(&dec_cont->storage) << 8;
  u32 bit_depth = dec_cont->storage.active_sps->bit_depth_luma;
#endif

  ASSERT(dec_cont != NULL);
  ASSERT(core_id < MAX_ASIC_CORES || (dec_cont->vcmd_used && core_id < MAX_MC_CB_ENTRIES));

  dwl = dec_cont->dwl;

  if(dec_cont->vcmd_used) {
    cmdbuf_id = core_id;
    core_id = DWLGetVcmdMCVirtualCoreId(dwl, cmdbuf_id);
  }
  /* take a copy of the args as after we release the HW they
   * can be overwritten.
   */
  info = dec_cont->hw_rdy_callback_arg[core_id];
  dpb = info.current_dpb;

  /* read all hw regs */
  if(dec_cont->vcmd_used) {
    if (dec_cont->convert_to_single_core_mode == SC_MODE)
      return;
    DWLVcmdMCRefreshStatusRegs(dwl, dec_regs, cmdbuf_id);
  }
  else {
    for (i = 0; i < DEC_X170_REGISTERS; i++) {
      dec_regs[i] = DWLReadReg(dwl, core_id, i * 4);
    }
  }
#if 0
  printf("Cycles/MB in current frame is %d\n",
      dec_regs[63]/(dec_cont->storage.active_sps->pic_height_in_mbs *
      dec_cont->storage.active_sps->pic_width_in_mbs));
#endif

  /* React to the HW return value */
  core_status = GetDecRegister(dec_regs, HWIF_DEC_IRQ_STAT);

  if (dec_cont->pp_enabled)
    DecreaseInputQueueCnt(dec_cont->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(info.pp_data)));

  p_out = (struct DWLLinearMem *)GetDataById(dpb->fb_list, info.out_id);
  if (p_out == NULL) return;
  p_dmv_out = (struct DWLLinearMem *)&dpb->dmv_buffers[info.dmv_out_id];

  /* check if DEC_RDY, all other status are errors */
  if (!(core_status & DEC_HW_IRQ_RDY)) {
    error_info = DEC_FRAME_ERROR;
    APITRACEERR("Core %d \"bad\" IRQ = 0x%08x\n", core_id, core_status);
    /* reset HW if still enabled */
    if (core_status & DEC_HW_IRQ_BUFFER) {
      error_info = DEC_NO_ERROR;
      /*  reset HW; we don't want an IRQ after reset so disable it */
      if (!dec_cont->vcmd_used) {
        DWLDisableHw(dwl, core_id, 0x04,
                     core_status | DEC_IRQ_DISABLE | DEC_ABORT);
      }
    }
#ifndef MEM_ONLY_DEV_CHECK
    /* reset DMV storage for erroneous pictures */
    {
      u32 dvm_mem_size = (dec_cont->storage.pic_size_in_mbs + 32) *
                         (dec_cont->high10p_mode? 80 : 64);
      u8 *dvm_base = (u8*)p_dmv_out->virtual_address;

      if(info.is_field_pic) {
        dvm_mem_size /= 2;
        if(info.is_bottom_field)
          dvm_base += dvm_mem_size;
      }

      (void) DWLmemset(dvm_base, 0, dvm_mem_size);
    }

    u8 *p_ref_stat;
    if (dec_cont->high10p_mode)
      p_ref_stat = (u8*)p_dmv_out->virtual_address - 32;
    else
      p_ref_stat = (u8*)p_dmv_out->virtual_address + dec_cont->storage.dmv_mem_size;

    h264MCSetRefPicStatus(p_ref_stat, info.is_field_pic, info.is_bottom_field);
#endif

#ifdef SUPPORT_DMA
    if (dec_cont->high10p_mode)
      DWLDMATransData((addr_t)((u8*)p_dmv_out->bus_address - 32),
                      (void *)((u8*)p_dmv_out->virtual_address - 32),
                      32, HOST_TO_DEVICE);
    else
      DWLDMATransData((addr_t)((u8*)p_dmv_out->bus_address + dec_cont->storage.dmv_mem_size),
                      (void *)((u8*)p_dmv_out->virtual_address + dec_cont->storage.dmv_mem_size),
                      32, HOST_TO_DEVICE);
#endif
  } else {
    if (dec_cont->hw_conceal)
      error_info = GetDecRegister(dec_regs, HWIF_ERROR_INFO);
    else
      error_info = DEC_NO_ERROR;

#ifdef SUPPORT_DMA
    if (dec_cont->high10p_mode)
      DWLDMATransData((addr_t)((u8*)p_dmv_out->bus_address - 32),
                      (void *)((u8*)p_dmv_out->virtual_address - 32),
                      32, DEVICE_TO_HOST);
    else
      DWLDMATransData((addr_t)((u8*)p_dmv_out->bus_address + dec_cont->storage.dmv_mem_size),
                      (void *)((u8*)p_dmv_out->virtual_address + dec_cont->storage.dmv_mem_size),
                      32, DEVICE_TO_HOST);
#endif
    if (GetDecRegister(dec_regs, HWIF_DEC_OUT_DIS) == 0)
      MCValidateRefPicStatus(dec_regs, &info);
  }

#ifdef FPGA_PERF_AND_BW
  DecPerfInfoCount(core_id, &dec_cont->perf_info, pic_size, bit_depth);
#endif

  /* mark corrupt picture in output queue */
  h264MCMarkOutputPicInfo(dec_cont, &info, error_info, dec_regs);
  H264DisableDMVBuffer((dpbStorage_t *)dpb, core_id);

  /* clear IRQ status reg and release HW core */
  if (dec_cont->vcmd_used) {
    DWLReleaseCmdBuf(dwl, cmdbuf_id);
    if (dec_cont->b_mc)
      FifoPush(dec_cont->fifo_core, (FifoObject)(addr_t)core_id, FIFO_EXCEPTION_DISABLE);
  } else {
    dec_cont->dec_status[core_id] = DEC_IDLE;  /* set dec status to idle */
    DWLReleaseHw(dwl, core_id);
  }

  H264UpdateAfterHwRdy(dec_cont, dec_regs);

  /* release the stream buffer. Callback provided by app */
  if(dec_cont->stream_consumed_callback.fn)
    dec_cont->stream_consumed_callback.fn((u8*)info.stream,
                                          (void*)info.p_user_data);

  if(info.is_field_pic) {
    if(info.is_bottom_field)
      type = FB_HW_OUT_FIELD_BOT;
    else
      type = FB_HW_OUT_FIELD_TOP;
  } else {
    type = FB_HW_OUT_FRAME;
  }

  ClearHWOutput(dpb->fb_list, info.out_id, type, dec_cont->pp_enabled);

  /* decrement buffer usage in our buffer handling */
  DecrementDPBRefCountExt((dpbStorage_t *)dpb, info.ref_id);
}


void h264MCSetHwRdyCallback(struct H264DecContainer *dec_cont) {
  dpbStorage_t *dpb = dec_cont->storage.dpb;
  u32 type, i;

  u32 core_id = dec_cont->vcmd_used ? dec_cont->mc_buf_id : dec_cont->core_id;
  H264HwRdyCallbackArg *arg = &dec_cont->hw_rdy_callback_arg[core_id];

  arg->stream = dec_cont->stream_consumed_callback.p_strm_buff;
  arg->p_user_data = dec_cont->stream_consumed_callback.p_user_data;
  arg->is_field_pic = dpb->current_out->is_field_pic;
  arg->is_bottom_field = dpb->current_out->is_bottom_field;
  arg->out_id = dpb->current_out->mem_idx;
  arg->dmv_out_id = dpb->current_out->dmv_mem_idx;
  if (dec_cont->pp_enabled)
    arg->pp_data = dpb->current_out->ds_data;
  arg->current_dpb = dpb;
  arg->is_high10_mode = dec_cont->high10p_mode;
  arg->pic_code_type[0] = dpb->current_out->pic_code_type[0];
  arg->pic_code_type[1] = dpb->current_out->pic_code_type[1];

  /* don't work */
  for (i = 0; i < dpb->dpb_size; i++) {
    const struct DWLLinearMem *ref;
    ref = (struct DWLLinearMem *)GetDataById(&dec_cont->fb_list, dpb->ref_id[i]);
    //ASSERT(ref->bus_address == (dec_cont->asic_buff->ref_pic_list[i] & (~3)));
    (void)ref;
    arg->ref_id[i] = dpb->ref_id[i];
  }

  /* storage reference mem_idx for current pic */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (IS_REFERENCE_F(dpb->buffer[i]))
      arg->ref_mem_idx[i] = dpb->buffer[i].mem_idx;
    else
      arg->ref_mem_idx[i] = DEC_DPB_INVALID_IDX;
  }

  DWLSetIRQCallback(dec_cont->dwl, dec_cont->vcmd_used ? dec_cont->cmdbuf_id : core_id, h264MCHwRdyCallback, dec_cont);

  if(arg->is_field_pic) {
    if(arg->is_bottom_field)
      type = FB_HW_OUT_FIELD_BOT;
    else
      type = FB_HW_OUT_FIELD_TOP;
  } else {
    type = FB_HW_OUT_FRAME;
  }

  MarkHWOutput(&dec_cont->fb_list, dpb->current_out->mem_idx, type);
}

#ifdef CASE_INFO_STAT
void H264CaseInfoCollect(struct H264DecContainer *dec_cont, CaseInfo *case_info) {
  storage_t *storage = &dec_cont->storage;
  struct DecCropParams crop_params;
  u32 pic_width, pic_height, bit_depth;

  bit_depth = (storage->active_sps->bit_depth_luma == 8 &&
                         storage->active_sps->bit_depth_chroma == 8) ? 8 : 10;
  case_info->min_cb_size = 3;
  case_info->max_cb_size = 4;
  case_info->pic_width_in_cbs = h264bsdPicWidth(storage) << 1;
  case_info->pic_height_in_cbs = h264bsdPicHeight(storage) << 1;
  pic_width = h264bsdPicWidth(storage) << 4;
  pic_height = h264bsdPicHeight(storage) << 4;
  h264bsdCroppingParams(storage, &crop_params);
  if (storage->active_sps->frame_cropping_flag)
    case_info->crop_flag = 1;

  if (case_info->frame_num == 0) {
    case_info->decode_width = pic_width;
    case_info->decode_height = pic_height;
    case_info->display_height = crop_params.crop_out_height;
    case_info->display_width = crop_params.crop_out_width;
    case_info->chroma_format_id = h264bsdChromaFormatIdc(storage);
    case_info->bit_depth = bit_depth;
    case_info->crop_x = crop_params.crop_left_offset;
    case_info->crop_y = crop_params.crop_top_offset;
  } else {
    if (case_info->decode_width != pic_width
    || case_info->decode_height!= pic_height) {
      case_info->decode_width = MAX (pic_width, case_info->decode_width);
      case_info->decode_height = MAX (pic_height, case_info->decode_height);
      case_info->resolution_flag = 1;
    }
    case_info->display_height = MIN (crop_params.crop_out_height, case_info->display_height);
    case_info->display_width = MIN (crop_params.crop_out_width, case_info->display_width);
    if (case_info->chroma_format_id != h264bsdChromaFormatIdc(storage)) {
      case_info->chroma_flag = 1;
    }
    if (case_info->bit_depth != bit_depth) {
      case_info->bit_depth = MAX (bit_depth, case_info->bit_depth);
      case_info->depth_flag = 1;
    }
  }

  if(dec_cont->mode_change) {
    if (case_info->frame_num < 10) {
      if (IS_B_SLICE(storage->slice_header->slice_type))
        case_info->frame_type[dec_cont->pic_number] = B_FRAME;
      else if (IS_P_SLICE(storage->slice_header->slice_type))
        case_info->frame_type[dec_cont->pic_number] = P_FRAME;
      else
        case_info->frame_type[dec_cont->pic_number] = I_FRAME;
      H264GetSimInfo(storage, case_info, crop_params.crop_out_width, crop_params.crop_out_height);
    }
    case_info->frame_num++;
    if (storage->active_pps->num_slice_groups != 1)
      case_info->fmo_flag = 1;
    else
      case_info->aso_flag = 1;
  } else {
    if (!storage->active_sps->frame_mbs_only_flag && storage->curr_image->pic_struct < FRAME) {
      if (storage->dpb->current_out->status[(u32)!storage->curr_image->pic_struct] != EMPTY){
        if (case_info->frame_num < 10) {
          if (case_info->b_slice_flag)
            case_info->frame_type[dec_cont->pic_number] = B_FIELED_1;
          else if (case_info->p_slice_flag)
            case_info->frame_type[dec_cont->pic_number] = P_FIELED_1;
          else
            case_info->frame_type[dec_cont->pic_number] = I_FIELED_1;
          H264GetSimInfo(storage, case_info, crop_params.crop_out_width, crop_params.crop_out_height);
          case_info->slice_num[case_info->frame_num]++;
        }
        case_info->frame_num++;
      } else {
        if (case_info->frame_num < 10) {
          if (case_info->b_slice_flag)
            case_info->frame_type[dec_cont->pic_number] = B_FIELED_0;
          else if (case_info->p_slice_flag)
            case_info->frame_type[dec_cont->pic_number] = P_FIELED_0;
          else
            case_info->frame_type[dec_cont->pic_number] = I_FIELED_0;
          case_info->slice_num[case_info->frame_num]++;
        }
      }
    } else {
      if (case_info->frame_num < 10) {
        if (case_info->b_slice_flag)
          case_info->frame_type[dec_cont->pic_number] = B_FRAME;
        else if (case_info->p_slice_flag)
          case_info->frame_type[dec_cont->pic_number] = P_FRAME;
        else
          case_info->frame_type[dec_cont->pic_number] = I_FRAME;
        case_info->slice_num[case_info->frame_num]++;
        H264GetSimInfo(storage, case_info, crop_params.crop_out_width, crop_params.crop_out_height);
      }
      case_info->frame_num++;
    }
  }

  case_info->codec = dec_cont->high10p_mode ? DEC_MODE_H264_H10P : DEC_MODE_H264;
  case_info->cavlc_flag = case_info->cavlc_flag == 1? 1: dec_cont->storage.active_pps->entropy_coding_mode_flag ? 0 : 1;
  case_info->interlace_flag = case_info->interlace_flag == 1 ? 1 : storage->active_sps->frame_mbs_only_flag == 0 ? 1 : 0;
  case_info->bitrate += ((60 * GetDecRegister(dec_cont->h264_regs, HWIF_STREAM_LEN) * 8/ (h264bsdPicWidth(&dec_cont->storage) * 16))
                        * 3840/ (h264bsdPicHeight(&dec_cont->storage) * 16)) * 2160/ 1024/ 1024;

}
static void H264GetSimInfo(storage_t *storage, CaseInfo *case_info, u32 width, u32 height) {
  u32 bit_depth, raster_stride;

  bit_depth = (storage->active_sps->bit_depth_luma == 8 &&
                         storage->active_sps->bit_depth_chroma == 8) ? 8 : 10;
  if(bit_depth == 8)
    raster_stride = NEXT_MULTIPLE(width, 16);
  else
    raster_stride = NEXT_MULTIPLE(width * 2, 16);

  case_info->bit_depth_y_minus8[case_info->frame_num] = storage->active_sps->bit_depth_luma - 8;
  case_info->bit_depth_c_minus8[case_info->frame_num] = storage->active_sps->bit_depth_chroma - 8;
  case_info->blackwhite_e[case_info->frame_num] = storage->active_sps->chroma_format_idc == 0 ? 1 : 0;
  case_info->ppin_luma_size[case_info->frame_num] = height * raster_stride;
  case_info->fieldmode[case_info->frame_num] = storage->slice_header->field_pic_flag;
  case_info->fieldpic_flag[case_info->frame_num] = storage->active_sps->frame_mbs_only_flag == 0 ? 1 : 0;
}
#endif
