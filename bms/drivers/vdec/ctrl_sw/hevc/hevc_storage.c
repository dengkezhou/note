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

#include "hevc_storage.h"
#include "hevc_dpb.h"
#include "hevc_nal_unit.h"
#include "hevc_slice_header.h"
#include "hevc_seq_param_set.h"
#include "hevc_util.h"
#include "hevc_vui.h"
#include "dwl.h"
#include "deccfg.h"
#include "hevc_container.h"
#include "dec_log.h"

/* Initializes storage structure. Sets contents of the storage to '0' except
 * for the active parameter set ids, which are initialized to invalid values.
 * */
void HevcInitStorage(struct Storage *storage) {

  ASSERT(storage);

  (void)DWLmemset(storage, 0, sizeof(struct Storage));

  storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
  storage->active_vps_id = MAX_NUM_VIDEO_PARAM_SETS;
  storage->old_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->num_tile_columns_old = 0;
  storage->log_max_coding_block_size_old = 0;
  storage->aub->first_call_flag = HANTRO_TRUE;
  storage->time_parameter.first_unit_flag = HANTRO_TRUE;
  storage->poc->pic_order_cnt = INIT_POC;
  storage->sei_param_curr = NULL;
  storage->sei_param_num = 0;
  storage->is_gdr_frame = HANTRO_FALSE;
}

/* Store sequence parameter set into the storage. If active SPS is overwritten
 * -> check if contents changes and if it does, set parameters to force
 *  reactivation of parameter sets. */
u32 HevcStoreSeqParamSet(struct Storage *storage,
                         struct SeqParamSet *seq_param_set) {

  u32 id;

  ASSERT(storage);
  ASSERT(seq_param_set);
  ASSERT(seq_param_set->seq_parameter_set_id < MAX_NUM_SEQ_PARAM_SETS);

  id = seq_param_set->seq_parameter_set_id;

  /* seq parameter set with id not used before -> allocate memory */
  if (storage->sps[id] == NULL) {
    ALLOCATE(storage->sps[id], 1, struct SeqParamSet);
    if (storage->sps[id] == NULL) return (MEMORY_ALLOCATION_ERROR);
  }
  /* sequence parameter set with id equal to id of active sps */
  else if (id == storage->active_sps_id) {
    /* TODO: if seq parameter set contents changes
     *    -> overwrite and re-activate when next IDR picture decoded
     *    ids of active param sets set to invalid values to force
     *    re-activation. Memories allocated for old sps freed
     * otherwise free memeries allocated for just decoded sps and
     * continue */
    if (HevcCompareSeqParamSets(seq_param_set, storage->active_sps) == 0 /*&&
        (seq_param_set->pic_width != storage->active_sps->pic_width ||
        seq_param_set->pic_height != storage->active_sps->pic_height)*/) {
      storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS + 1;
      storage->active_sps = NULL;
      storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS + 1;
      storage->active_pps = NULL;
    } else {
      return (HANTRO_OK);
    }
  }

  /* error case: log_max_coding_block_size change but sps_id don't change. */
  if (storage->active_sps)
    storage->log_max_coding_block_size_old = storage->active_sps->log_max_coding_block_size;
  *storage->sps[id] = *seq_param_set;

  return (HANTRO_OK);
}

/* Store picture parameter set into the storage. If active PPS is overwritten
 * -> check if active SPS changes and if it does -> set parameters to force
 *  reactivation of parameter sets. */
u32 HevcStorePicParamSet(struct Storage *storage,
                         struct PicParamSet *pic_param_set) {

  u32 id;

  ASSERT(storage);
  ASSERT(pic_param_set);
  ASSERT(pic_param_set->pic_parameter_set_id < MAX_NUM_PIC_PARAM_SETS);
  ASSERT(pic_param_set->seq_parameter_set_id < MAX_NUM_SEQ_PARAM_SETS);

  id = pic_param_set->pic_parameter_set_id;

  /* pic parameter set with id not used before -> allocate memory */
  if (storage->pps[id] == NULL) {
    ALLOCATE(storage->pps[id], 1, struct PicParamSet);
    if (storage->pps[id] == NULL) return (MEMORY_ALLOCATION_ERROR);
  }
  /* picture parameter set with id equal to id of active pps */
  else if (id == storage->active_pps_id) {
    /* check whether seq param set changes, force re-activation of
     * param set if it does. Set active_sps_id to invalid value to
     * accomplish this */
    if (pic_param_set->seq_parameter_set_id != storage->active_sps_id) {
      storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS + 1;
    }
  }
  /* overwrite pic param set other than active one -> free memories
   * allocated for old param set */
  else {
  }

  /* error case: num_tile_columns change but pps_id don't change. */
  if (storage->active_pps)
    storage->num_tile_columns_old = storage->active_pps->tile_info.num_tile_columns;
  *storage->pps[id] = *pic_param_set;

  return (HANTRO_OK);
}

/* Store video parameter set into the storage. If active VPS is overwritten
 * -> check if active VPS changes and if it does -> set parameters to force
 *  reactivation of parameter sets. */
u32 HevcStoreVideoParamSet(struct Storage *storage,
                           struct VideoParamSet *video_param_set) {

  u32 id;

  ASSERT(storage);
  ASSERT(video_param_set);
  ASSERT(video_param_set->vps_video_parameter_set_id < MAX_NUM_VIDEO_PARAM_SETS);

  id = video_param_set->vps_video_parameter_set_id;

  /* video parameter set with id not used before -> allocate memory */
  if (storage->vps[id] == NULL) {
    ALLOCATE(storage->vps[id], 1, struct VideoParamSet);
    if (storage->vps[id] == NULL) return (MEMORY_ALLOCATION_ERROR);
  }
  /*video parameter set with id equal to id of active vps */
  else if (id == storage->active_vps_id) {
    /* check whether video param set changes, force re-activation of
     * param set if it does. Set active_vps_id to invalid value to
     * accomplish this */
    if (HevcCompareVideoParamSets(video_param_set, storage->active_vps) == 0) {
      storage->active_vps_id = MAX_NUM_VIDEO_PARAM_SETS + 1;
      storage->active_vps = NULL;
      storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS + 1;
      storage->active_sps = NULL;
      storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS + 1;
      storage->active_pps = NULL;
    } else {
      return (HANTRO_OK);
    }
  }
  *storage->vps[id] = *video_param_set;

  return (HANTRO_OK);
}


/* Activate certain SPS/PPS combination. This function shall be called in
 * the beginning of each picture. Picture parameter set can be changed as
 * wanted, but sequence parameter set may only be changed when the starting
 * picture is an IDR picture. */
u32 HevcActivateParamSets(struct Storage *storage, u32 pps_id, u32 is_idr) {

  ASSERT(storage);
  ASSERT(pps_id < MAX_NUM_PIC_PARAM_SETS);

  /* check that pps and corresponding sps exist */
  if ((pps_id >= MAX_NUM_PIC_PARAM_SETS) ||
      (storage->pps[pps_id] == NULL) ||
      (storage->sps[storage->pps[pps_id]->seq_parameter_set_id] == NULL) ||
      (storage->vps[storage->sps[storage->pps[pps_id]->seq_parameter_set_id]->vps_id] == NULL)) {
    return (HANTRO_NOK);
  }

  /* first activation */
  if (storage->active_pps_id == MAX_NUM_PIC_PARAM_SETS) {
    storage->active_pps_id = pps_id;
    storage->active_pps = storage->pps[pps_id];
    storage->active_sps_id = storage->active_pps->seq_parameter_set_id;
    storage->active_sps = storage->sps[storage->active_sps_id];
    storage->active_vps_id = storage->sps[storage->active_pps->seq_parameter_set_id]->vps_id;
    storage->active_vps = storage->vps[storage->active_vps_id];
  } else if (pps_id != storage->active_pps_id) {
    /* sequence parameter set shall not change but before an IDR picture */
    if (storage->pps[pps_id]->seq_parameter_set_id != storage->active_sps_id ||
        storage->sps[storage->pps[pps_id]->seq_parameter_set_id]->vps_id != storage->active_vps_id) {
      STREAMTRACE_I("%s","SEQ PARAM SET CHANGING...\n");
      if (is_idr) {
        storage->active_pps_id = pps_id;
        storage->active_pps = storage->pps[pps_id];
        storage->active_sps_id = storage->active_pps->seq_parameter_set_id;
        storage->active_sps = storage->sps[storage->active_sps_id];
        storage->active_vps_id = storage->sps[storage->active_pps->seq_parameter_set_id]->vps_id;
        storage->active_vps = storage->vps[storage->active_vps_id];
      } else {
        STREAMTRACE_E("%s","TRYING TO CHANGE SPS IN NON-IDR SLICE\n");
        return (HANTRO_NOK);
      }
    } else {
      storage->active_pps_id = pps_id;
      storage->active_pps = storage->pps[pps_id];
    }
  }

  return (HANTRO_OK);
}

/* Reset contents of the storage. This should be called before processing of
 * new image is started. */
void HevcResetStorage(struct Storage *storage) {

  ASSERT(storage);
  storage->prev_idr_pic_ready = HANTRO_FALSE;
}

/* Determine if the decoder is in the start of a picture. This information is
 * needed to decide if HevcActivateParamSets function should be called.
 * Function considers that new picture is starting if no slice headers have
 * been successfully decoded for the current access unit. */
u32 HevcIsStartOfPicture(struct Storage *storage) {

  if (storage->valid_slice_in_access_unit == HANTRO_FALSE)
    return (HANTRO_TRUE);
  else
    return (HANTRO_FALSE);
}

/* Check if next NAL unit starts a new access unit. */
u32 HevcCheckAccessUnitBoundary(struct StrmData *strm, struct NalUnit *nu_next,
                                struct Storage *storage,
                                u32 *access_unit_boundary_flag) {

  ASSERT(strm);
  ASSERT(nu_next);
  ASSERT(storage);

  STREAMTRACE_I("%s","HevcCheckAccessUnitBoundary #\n");
  /* initialize default output to HANTRO_FALSE */
  *access_unit_boundary_flag = HANTRO_FALSE;

  if (nu_next->nal_unit_type == NAL_END_OF_SEQUENCE)
    storage->no_rasl_output = 1;
  else if (nu_next->nal_unit_type < NAL_CODED_SLICE_CRA)
    storage->no_rasl_output = 0;
  if (IS_RAP_NAL_UNIT(nu_next)) {
    if ((nu_next->nal_unit_type >= NAL_CODED_SLICE_BLA_W_LP && nu_next->nal_unit_type <= NAL_CODED_SLICE_IDR_N_LP) ||
        (nu_next->nal_unit_type == NAL_CODED_SLICE_CRA && storage->aub->first_call_flag))
      storage->no_rasl_output = 1;
  }


  if (nu_next->nal_unit_type == NAL_ACCESS_UNIT_DELIMITER ||
      nu_next->nal_unit_type == NAL_VIDEO_PARAM_SET ||
      nu_next->nal_unit_type == NAL_SEQ_PARAM_SET ||
      nu_next->nal_unit_type == NAL_PIC_PARAM_SET ||
      nu_next->nal_unit_type == NAL_PREFIX_SEI ||
      (nu_next->nal_unit_type >= 41 && nu_next->nal_unit_type <= 44)) {
    *access_unit_boundary_flag = HANTRO_TRUE;
    return (HANTRO_OK);
  } else if (!IS_SLICE_NAL_UNIT(nu_next)) {
    return (HANTRO_OK);
  }

  /* check if this is the very first call to this function */
  if (storage->aub->first_call_flag) {
    *access_unit_boundary_flag = HANTRO_TRUE;
    storage->aub->first_call_flag = HANTRO_FALSE;
  }

  if (SwShowBits(strm, 1)) *access_unit_boundary_flag = HANTRO_TRUE;

  *storage->aub->nu_prev = *nu_next;

  return (HANTRO_OK);
}

/* Check if any valid SPS/PPS combination exists in the storage.  Function
 * tries each PPS in the buffer and checks if corresponding SPS exists. */
u32 HevcValidParamSets(struct Storage *storage) {

  u32 i;

  ASSERT(storage);

  for (i = 0; i < MAX_NUM_PIC_PARAM_SETS; i++) {
    if (storage->pps[i] &&
        storage->sps[storage->pps[i]->seq_parameter_set_id]) {
      return (HANTRO_OK);
    }
  }

  return (HANTRO_NOK);
}

void HevcClearStorage(struct Storage *storage) {

  /* Variables */

  /* Code */
  u32 i;
  ASSERT(storage);
  
  (void)i;

  HevcResetStorage(storage);

#ifdef CLEAR_HDRINFO_IN_SEEK
  storage->old_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
  storage->active_sps = NULL;
  storage->active_pps = NULL;

  for (i = 0; i < MAX_NUM_VIDEO_PARAM_SETS; i++) {
    if (storage->vps[i]) {
      FREE(storage->vps[i]);
    }
  }

  for (i = 0; i < MAX_NUM_SEQ_PARAM_SETS; i++) {
    if (storage->sps[i]) {
      FREE(storage->sps[i]);
    }
  }

  for (i = 0; i < MAX_NUM_PIC_PARAM_SETS; i++) {
    if (storage->pps[i]) {
      FREE(storage->pps[i]);
    }
  }

#endif

  storage->bumping_flag = 0;
  storage->frame_rate = 0;
  storage->pic_started = HANTRO_FALSE;
  storage->valid_slice_in_access_unit = HANTRO_FALSE;
  storage->checked_aub = 0;
  storage->prev_buf_not_finished = HANTRO_FALSE;
  storage->prev_buf_pointer = NULL;
  storage->prev_bytes_consumed = 0;
  storage->picture_broken = 0;
  storage->poc_last_display = INIT_POC;
  storage->pending_out_pic = NULL;
  storage->no_rasl_output = 0;
  storage->realloc_int_buf = 0;
  storage->realloc_ext_buf = 0;

  (void)DWLmemset(&storage->poc, 0, 2 * sizeof(struct PocStorage));
  (void)DWLmemset(&storage->aub, 0, sizeof(struct AubCheck));
  (void)DWLmemset(&storage->curr_image, 0, sizeof(struct Image));
  (void)DWLmemset(&storage->prev_nal_unit, 0, sizeof(struct NalUnit));
  (void)DWLmemset(&storage->slice_header, 0, 2 * sizeof(struct SliceHeader));
  (void)DWLmemset(&storage->strm, 0, sizeof(struct StrmData));

  /* clear sei_param */
#ifdef SUPPORT_SEI
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (storage->sei_param[i] && storage->sei_param[i]->sei_status != SEI_UNUSED) {
      storage->sei_param[i]->sei_status = SEI_UNUSED;
      storage->sei_param[i]->decode_id = -1;
      if (storage->sei_param[i]->t35_param.payload_byte.buffer) {
        storage->sei_param[i]->t35_param.payload_byte.available_size = 0;
        storage->sei_param[i]->t35_param.counter = 0;
      }
      if (storage->sei_param[i]->userdataunreg_param.payload_byte.buffer) {
        storage->sei_param[i]->userdataunreg_param.payload_byte.available_size = 0;
        storage->sei_param[i]->userdataunreg_param.userdataunreg_counter = 0;
      }
    }
  }
#endif
}

/* Allocates SW resources after parameter set activation. */
void HevcCheckBufferRealloc(void *dec_inst, struct Storage *storage) {
  const struct SeqParamSet *sps = storage->active_sps;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  u32 luma_size = 0, chroma_size = 0, rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 buff_size, pp_size = 0, pic_size;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));
  struct DpbStorage *dpb = storage->dpb;
  u32 qp_mem_size = 0;

  HevcGetRefFrmSize(dec_cont, &luma_size, &chroma_size,
                      &rfc_luma_size, &rfc_chroma_size);

  /* TODO: next cb or ctb multiple? */
  av_unused u32 pic_width_in_ctbs =
    (sps->pic_width + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
  av_unused u32 pic_height_in_ctbs =
    (sps->pic_height + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;

#if 0
  /* buffer size of dpb pic = pic_size + dir_mv_size + tbl_size */
  u32 dmv_mem_size =
    /* num ctbs */
    (pic_width_in_ctbs * pic_height_in_ctbs *
     /* num 16x16 blocks in ctbs */
     (1 << (2 * (sps->log_max_coding_block_size - 4))) *
     /* num bytes per 16x16 */
     16);
#else
  /* Calculate dir_mv_size based on the max resolution, so that the changing in
     CTB size of given resolution won't result in the external buffer
     re-allocation. */
  u32 pic_width_in_ctb64 = (sps->pic_width + (1 << 6) - 1) >> 6;
  u32 pic_height_in_ctb64 = (sps->pic_height + (1 << 6) - 1) >> 6;

  u32 dmv_mem_size;
  /* buffer size of dpb pic = pic_size + dir_mv_size + tbl_size */

  if (!(dec_cont->skip_non_intra && dec_cont->pp_enabled)) {
    dmv_mem_size =
    /* num ctbs */
    NEXT_MULTIPLE((pic_width_in_ctb64 * pic_height_in_ctb64 *
     /* num 16x16 blocks in ctbs */
     (1 << (2 * (6 - 4))) *
     /* num bytes per 16x16 */
     16), ref_buffer_align);
  } else {
    dmv_mem_size = 0;
  }
#endif

  pic_size = NEXT_MULTIPLE(luma_size, ref_buffer_align);

  u32 n_extra_frm_buffers = storage->n_extra_frm_buffers;

  /* allocate 32 bytes for multicore status fields */
  /* locate it after picture and before direct MV */
  u32 ref_buff_size = pic_size
                      + NEXT_MULTIPLE(pic_size / 2, ref_buffer_align)
                      + dmv_mem_size
                      + NEXT_MULTIPLE(32, ref_buffer_align);

  u32 min_buffer_num, dpb_size;

  /* set dpb buffer numbers according to user's configuration */
  if (dec_cont->use_ext_dpb_size)
    dpb_size = dec_cont->num_buffers;
  else
    dpb_size = sps->max_dpb_size + 1;

  if (dec_cont->skip_non_intra) dpb_size = 1;
  if (dec_cont->heif_mode) {
    if (dec_cont->skip_non_intra) dpb_size = 0;
  }
  if (dec_cont->qp_output_enable) { //QP output mem
    qp_mem_size = NEXT_MULTIPLE((((sps->pic_width + (1 << sps->log_max_coding_block_size) - 1)
                                     >> sps->log_max_coding_block_size)
                                     << ((sps->log_max_coding_block_size - 4) * 2)) , 64) *
                 ((sps->pic_height + (1 << sps->log_max_coding_block_size) - 1)
                                     >> sps->log_max_coding_block_size);
  } else
    qp_mem_size = 0;

  if (!dec_cont->pp_enabled)
    ref_buff_size += qp_mem_size;

  if (storage->use_video_compressor) {
    /* luma table size */
    ref_buff_size += NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align);
    /* chroma table size */
    ref_buff_size += NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);
  }

  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
  pp_size = CalcPpUnitBufferSize(ppu_cfg, sps->mono_chrome) + qp_mem_size;
  dec_cont->auxinfo_offset = pp_size - qp_mem_size;

  u32 tot_buffers = dpb_size + 2 + n_extra_frm_buffers;
#if defined(ASIC_TRACE_SUPPORT) && defined(SUPPORT_MULTI_CORE)
  tot_buffers += 10;
#endif
  if (tot_buffers > MAX_PIC_BUFFERS)
    tot_buffers = MAX_PIC_BUFFERS;
  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    min_buffer_num = dpb_size + 2;   /* We need at least (dpb_size+2) output buffers before starting decoding. */
    buff_size = ref_buff_size;
  } else {
    if(dpb->no_reordering)
      min_buffer_num = 1 + 1; /* one is output, one is decode */
    else
      min_buffer_num = dpb_size + 1;
    ASSERT(IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, DOWNSCALE_OUT_BUFFER));
    buff_size = pp_size;
  }

  storage->realloc_int_buf = 0;
  storage->realloc_ext_buf = 0;
  /* tile output */
  if (!dec_cont->pp_enabled) {
    if (dec_cont->use_adaptive_buffers) {
      /* Check if external buffer size is enough */
      if (buff_size > dec_cont->ext_buffer_size ||
          (!dec_cont->use_ext_dpb_size &&
           min_buffer_num + dec_cont->guard_size > dec_cont->ext_buffer_num))
        storage->realloc_ext_buf = 1;
    }

    if (!dec_cont->use_adaptive_buffers) {
      /* use next_buf_size, beacase ext_buffer_size has the align operation*/
      if (buff_size != dec_cont->next_buf_size ||
          tot_buffers > dpb->tot_buffers)
        storage->realloc_ext_buf = 1;
    }
    storage->realloc_int_buf = 0;
  } else { /* PP output*/
    if (dec_cont->use_adaptive_buffers) {
      if (buff_size > dec_cont->ext_buffer_size ||
          (!dec_cont->use_ext_dpb_size &&
           min_buffer_num + dec_cont->guard_size > dec_cont->ext_buffer_num))
        storage->realloc_ext_buf = 1;
      if (ref_buff_size > dpb->n_int_buf_size ||
          (!dec_cont->use_ext_dpb_size &&
           tot_buffers > dpb->tot_buffers))
        storage->realloc_int_buf = 1;
    }

    if (!dec_cont->use_adaptive_buffers) {
      /* use next_buf_size, beacase n_ext_buf_size has the align operation*/
      if ((buff_size != dec_cont->next_buf_size) ||
          (min_buffer_num + dec_cont->guard_size > dec_cont->ext_buffer_num))
        storage->realloc_ext_buf = 1;
      if (ref_buff_size != dpb->n_int_buf_size ||
          tot_buffers > dpb->tot_buffers)
        storage->realloc_int_buf = 1;
    }
  }
}

void HevcSetExternalBufferInfo(void *dec_inst, struct Storage *storage) {
  const struct SeqParamSet *sps = storage->active_sps;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  u32 buff_size = 0, pp_size = 0, pic_size = 0;
  u32 luma_size = 0, chroma_size = 0, rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));
  u32 qp_mem_size = 0;
  HevcGetRefFrmSize(dec_cont, &luma_size, &chroma_size,
                      &rfc_luma_size, &rfc_chroma_size);

  /* TODO: next cb or ctb multiple? */
#if 0
  u32 pic_width_in_ctbs =
    (sps->pic_width + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
  u32 pic_height_in_ctbs =
    (sps->pic_height + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
#else
  /* Calculate dir_mv_size based on the max resolution, so that the changing in
     CTB size of given resolution won't result in the external buffer
     re-allocation. */
  u32 pic_width_in_ctb64 = (sps->pic_width + (1 << 6) - 1) >> 6;
  u32 pic_height_in_ctb64 = (sps->pic_height + (1 << 6) - 1) >> 6;
#endif

  pic_size = NEXT_MULTIPLE(luma_size, ref_buffer_align);

  u32 n_extra_frm_buffers = storage->n_extra_frm_buffers;

  u32 dmv_mem_size;
  /* buffer size of dpb pic = pic_size + dir_mv_size + tbl_size */
  if (!(dec_cont->skip_non_intra && dec_cont->pp_enabled)) {
    dmv_mem_size =
    /* num ctbs */
    NEXT_MULTIPLE((pic_width_in_ctb64 * pic_height_in_ctb64 *
     /* num 16x16 blocks in ctbs */
     (1 << (2 * (6 - 4))) *
     /* num bytes per 16x16 */
     16), ref_buffer_align);
  } else {
    dmv_mem_size = 0;
  }

  /* allocate 32 bytes for multicore status fields */
  /* locate it after picture and before direct MV */
  u32 ref_buff_size = pic_size
                      + NEXT_MULTIPLE(pic_size / 2, ref_buffer_align)
                      + dmv_mem_size
                      + NEXT_MULTIPLE(32, ref_buffer_align);
  u32 dpb_size;
  if (dec_cont->use_ext_dpb_size)
    dpb_size = dec_cont->num_buffers;
  else
    dpb_size = sps->max_dpb_size + 1;
  if (dec_cont->skip_non_intra) dpb_size = 1;
  if (dec_cont->heif_mode) {
    if (dec_cont->skip_non_intra) dpb_size = 0;
  }


  u32 min_buffer_num;
  enum DecBufferType buf_type;
  if (dec_cont->qp_output_enable) { //QP output mem
    qp_mem_size = NEXT_MULTIPLE((((sps->pic_width + (1 << sps->log_max_coding_block_size) - 1)
                                     >> sps->log_max_coding_block_size)
                                     << ((sps->log_max_coding_block_size - 4) * 2)) , 64) *
                     ((sps->pic_height + (1 << sps->log_max_coding_block_size) - 1)
                                     >> sps->log_max_coding_block_size);
  } else
    qp_mem_size = 0;

  if (!dec_cont->pp_enabled) {
    storage->dpb->out_qp_offset = ref_buff_size;
    ref_buff_size += qp_mem_size;
  }

  if (storage->use_video_compressor) {
    /* luma table size */
    ref_buff_size += NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align);
    /* chroma table size */
    ref_buff_size += NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);
  }


  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
  pp_size = CalcPpUnitBufferSize(ppu_cfg, sps->mono_chrome) + qp_mem_size;
  dec_cont->auxinfo_offset = pp_size - qp_mem_size;

  u32 tot_buffers = dpb_size + 2 + n_extra_frm_buffers;
#if defined(ASIC_TRACE_SUPPORT) && defined(SUPPORT_MULTI_CORE)
  tot_buffers += 10;
#endif
  if (tot_buffers > MAX_PIC_BUFFERS)
    tot_buffers = MAX_PIC_BUFFERS;
  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    min_buffer_num = dpb_size + 2;   /* We need at least (dpb_size+2) output buffers before starting decoding. */
    buff_size = ref_buff_size;
    buf_type = REFERENCE_BUFFER;
  } else {
    if(dec_cont->storage.no_reordering)
      min_buffer_num = 1 + 1; /* one is output, one is decode */
    else
      min_buffer_num = dpb_size + 1;
    buff_size = pp_size;
    buf_type = DOWNSCALE_OUT_BUFFER;
  }

  dec_cont->buf_num = min_buffer_num;
  dec_cont->next_buf_size = buff_size;
  dec_cont->buf_type = buf_type;
}

u32 HevcAllocateSwResources(const void *dwl, struct Storage *storage, void *dec_inst, u32 n_cores) {
  u32 tmp;
  const struct SeqParamSet *sps = storage->active_sps;
  struct DpbInitParams *dpb_params = &storage->dpb_params;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  u32 luma_size = 0, chroma_size = 0, rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));

  HevcGetRefFrmSize(dec_cont, &luma_size, &chroma_size,
                      &rfc_luma_size, &rfc_chroma_size);

  /* TODO: next cb or ctb multiple? */
  storage->pic_width_in_cbs = sps->pic_width >> sps->log_min_coding_block_size;
  storage->pic_height_in_cbs =
    sps->pic_height >> sps->log_min_coding_block_size;
  storage->pic_width_in_ctbs =
    (sps->pic_width + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
  storage->pic_height_in_ctbs =
    (sps->pic_height + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;

  storage->pic_size = NEXT_MULTIPLE(luma_size, ref_buffer_align);
  storage->curr_image->width = sps->pic_width;
  storage->curr_image->height = sps->pic_height;

  /* dpb output reordering disabled if
   * 1) application set no_reordering flag
   * 2) num_reorder_frames equal to 0 */
  if (storage->no_reordering)
    dpb_params->no_reordering = HANTRO_TRUE;
  else
    dpb_params->no_reordering = HANTRO_FALSE;

  dpb_params->n_cores = n_cores;
  dpb_params->dpb_size = sps->max_dpb_size;
  if (dec_cont->skip_non_intra) dpb_params->dpb_size = 0;
  dpb_params->mono_chrome = sps->mono_chrome;
  dpb_params->chroma_format_idc = sps->chroma_format_idc;
  dpb_params->pic_size = storage->pic_size;
  dpb_params->n_extra_frm_buffers = storage->n_extra_frm_buffers;

  /* Calculate dir_mv_size based on the max resolution, so that the changing in
     CTB size of given resolution won't result in the external buffer
     re-allocation. */
  u32 pic_width_in_ctb64 = (sps->pic_width + (1 << 6) - 1) >> 6;
  u32 pic_height_in_ctb64 = (sps->pic_height + (1 << 6) - 1) >> 6;

  /* buffer size of dpb pic = pic_size + dir_mv_size + tbl_size */
  if (!(dec_cont->skip_non_intra && dec_cont->pp_enabled)) {
    storage->dmv_mem_size =
    /* num ctbs */
    NEXT_MULTIPLE((pic_width_in_ctb64 * pic_height_in_ctb64 *
     /* num 16x16 blocks in ctbs */
     (1 << (2 * (6 - 4))) *
     /* num bytes per 16x16 */
     16), ref_buffer_align);
  } else {
    storage->dmv_mem_size = 0;
  }

  /* allocate 32 bytes for multicore status fields */
  /* locate it after picture and before direct MV */
  dpb_params->buff_size = storage->pic_size
                         + (sps->mono_chrome ? 0 :
			   NEXT_MULTIPLE(storage->pic_size / (sps->chroma_format_idc == 2 ? 1 : 2), ref_buffer_align))
                         + storage->dmv_mem_size
                         + NEXT_MULTIPLE(32, ref_buffer_align);

  if (dec_cont->qp_output_enable) {
    storage->qp_mem_size = NEXT_MULTIPLE((((sps->pic_width + (1 << sps->log_max_coding_block_size) - 1)
                                     >> sps->log_max_coding_block_size)
                                     << ((sps->log_max_coding_block_size - 4) * 2)) , 64) *
                         ((sps->pic_height + (1 << sps->log_max_coding_block_size) - 1)
                                     >> sps->log_max_coding_block_size);
  } else
    storage->qp_mem_size = 0;

  if (!dec_cont->pp_enabled) {
    storage->dpb->out_qp_offset = dpb_params->buff_size;
    dpb_params->buff_size += storage->qp_mem_size;
  }

  if (storage->use_video_compressor) {
    /* luma table size */
    dpb_params->buff_size += NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align);
    /* chroma table size */
    dpb_params->buff_size += NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);

    dpb_params->tbl_sizey = NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align);
    dpb_params->tbl_sizec = NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);
#ifdef USE_FAKE_RFC_TABLE
    dec_cont->asic_buff->fake_tbly_size = dpb_params->tbl_sizey;
    dec_cont->asic_buff->fake_tblc_size = dpb_params->tbl_sizec;
#endif
  } else
    dpb_params->tbl_sizey = dpb_params->tbl_sizec = 0;

  /* note that calling ResetDpb here results in losing all
   * pictures currently in DPB -> nothing will be output from
   * the buffer even if no_output_of_prior_pics_flag is HANTRO_FALSE */
  tmp = HevcResetDpb(dec_inst, storage->dpb, dpb_params);

  storage->dpb->pic_width = sps->pic_width;
  storage->dpb->pic_height = sps->pic_height;
  storage->dpb->bit_depth_luma = sps->bit_depth_luma;
  storage->dpb->bit_depth_chroma = sps->bit_depth_chroma;
  storage->dpb->mono_chrome = sps->mono_chrome;

  {
    struct DecCropParams *crop = &storage->dpb->crop_params;
    const struct SeqParamSet *sps = storage->active_sps;

    if (sps->pic_cropping_flag) {
      u32 tmp1 = (sps->mono_chrome ? 1 : 2);
      u32 tmp2 = 1;

      crop->crop_left_offset = tmp1 * sps->pic_crop_left_offset;
      crop->crop_out_width =
        sps->pic_width -
        tmp1 * (sps->pic_crop_left_offset + sps->pic_crop_right_offset);

      crop->crop_top_offset = tmp1 * tmp2 * sps->pic_crop_top_offset;
      crop->crop_out_height =
        sps->pic_height - tmp1 * tmp2 * (sps->pic_crop_top_offset +
                                         sps->pic_crop_bottom_offset);
    } else {
      crop->crop_left_offset = 0;
      crop->crop_top_offset = 0;
      crop->crop_out_width = sps->pic_width;
      crop->crop_out_height = sps->pic_height;
    }
  }

  if (tmp != HANTRO_OK) return (tmp);

  /* Issue the external buffer request here when necessary. */
  if (storage->pp_enabled && storage->realloc_ext_buf) {
    PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
    u32 pp_size = 0;
    dec_cont->release_buffer = 1;

    pp_size = CalcPpUnitBufferSize(ppu_cfg, sps->mono_chrome) + storage->qp_mem_size;
    dec_cont->auxinfo_offset = pp_size - storage->qp_mem_size;
    dec_cont->min_buffer_num = sps->max_dpb_size + 2;

    dec_cont->buf_type = DOWNSCALE_OUT_BUFFER;
    dec_cont->next_buf_size = pp_size;
    dec_cont->buf_to_free = NULL;
    dec_cont->buf_num = dec_cont->min_buffer_num;
    if (dec_cont->heif_mode && dec_cont->skip_non_intra) dec_cont->buf_num = 1;

    return DEC_WAITING_FOR_BUFFER;
  }

  /*
    {
      struct DecCropParams *crop = &storage->dpb->crop_params;
      const struct SeqParamSet *sps = storage->active_sps;

      if (sps->pic_cropping_flag) {
        u32 tmp1 = 2, tmp2 = 1;

        crop->crop_left_offset = tmp1 * sps->pic_crop_left_offset;
        crop->crop_out_width =
            sps->pic_width -
            tmp1 * (sps->pic_crop_left_offset + sps->pic_crop_right_offset);

        crop->crop_top_offset = tmp1 * tmp2 * sps->pic_crop_top_offset;
        crop->crop_out_height =
            sps->pic_height - tmp1 * tmp2 * (sps->pic_crop_top_offset +
                                             sps->pic_crop_bottom_offset);
      } else {
        crop->crop_left_offset = 0;
        crop->crop_top_offset = 0;
        crop->crop_out_width = sps->pic_width;
        crop->crop_out_height = sps->pic_height;
      }
    }
  */

  return HANTRO_OK;
}

u32 HevcStoreSEIInfoForCurrentPic(struct Storage *storage) {
  u32 tmp;
  struct DpbStorage *dpb = storage->dpb;

  tmp = HevcDecodeHRDParameters(storage, storage->prev_nal_unit);
  if (tmp != HANTRO_OK)
    return HANTRO_NOK;

  dpb->cpb_removal_time = storage->time_parameter.cpb_removal_time;;
  dpb->current_out->dpb_output_time = storage->time_parameter.dpb_output_time;
  dpb->current_out->pic_struct = storage->sei_param_curr ?
                                 storage->sei_param_curr->pic_param.pic_struct : 0;
  return HANTRO_OK;
}

static double Ceil(double a) {
  u32 tmp;
  tmp = (u32) a;
  if ((double) (tmp) < a)
    return ((double) (tmp + 1));
  else
    return ((double) (tmp));
}

u32 HevcDecodeHRDParameters(struct Storage *storage, struct NalUnit *nal_unit) {
  u32 cpb_delay_offset, dpb_delay_offset;
  u32 init_cpb_dalay, init_cpb_delay_offset;
  u32 bit_rate;
  double au_nominal_remove_time;
  double base_time;
  double init_arrival_earliest_time;
  double init_arrival_time;
  double au_finall_arrival_time;
  u32 tmp_cpb_removal_delay;
  u32 cpb_removal_delay_val, max_cpb_removal_delay_val;
  u32 cpb_removal_delay_msb;
  u32 layerid = nal_unit->temporal_id;
  struct SeqParamSet *sps;
  struct DpbOutDelay *time_parameter;
  struct VuiParameters *vui_parameters;
  struct HevcSEIParameters *sei_parameters;
  u32 stream_len;
  u32 *vui_parameters_update_flag;
  sps = storage->active_sps;
  sei_parameters = storage->sei_param_curr;
  vui_parameters = &sps->vui_parameters;
  time_parameter = &storage->time_parameter;
  vui_parameters_update_flag = &storage->vui_parameters_update_flag;
  stream_len = storage->stream_len;

  if (sps == NULL || sei_parameters == NULL)
    return HANTRO_NOK;
  if (!sei_parameters->pic_param.au_cpb_removal_delay &&
      !sei_parameters->pic_param.pic_dpb_output_delay)
    return HANTRO_NOK;

#if 0
  time_parameter->first_unit_flag = nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_W_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_W_DLP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_N_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_IDR_W_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_IDR_N_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_CRA;
#endif
  u32 first_unit_flag = nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_W_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_W_DLP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_N_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_IDR_W_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_IDR_N_LP ||
                                    nal_unit->nal_unit_type == NAL_CODED_SLICE_CRA;

  if (time_parameter->first_unit_flag) {
    if (*vui_parameters_update_flag)
      time_parameter->hrd_init_flag = 1;
    else
      time_parameter->hrd_init_flag = 0;
    *vui_parameters_update_flag = 0;
  }
  if (time_parameter->first_unit_flag) {
    if ((nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_W_DLP ||
         nal_unit->nal_unit_type == NAL_CODED_SLICE_BLA_N_LP) &&
        (sei_parameters->buf_param.irap_cpb_params_present_flag))
      time_parameter->alt_flag = 1;
    else
      time_parameter->alt_flag = 0;
  }
  time_parameter->pre_nondiscard_flag = ((nal_unit->temporal_id == 0) &&
                                         (nal_unit->nal_unit_type != NAL_CODED_SLICE_RADL_N &&
                                          nal_unit->nal_unit_type != NAL_CODED_SLICE_RADL_R &&
                                          nal_unit->nal_unit_type != NAL_CODED_SLICE_RASL_N &&
                                          nal_unit->nal_unit_type != NAL_CODED_SLICE_RASL_R)) ||
                                        ((nal_unit->temporal_id != 0) &&
                                         (nal_unit->nal_unit_type == NAL_CODED_SLICE_TRAIL_N ||
                                          nal_unit->nal_unit_type == NAL_CODED_SLICE_TSA_N ||
                                          nal_unit->nal_unit_type == NAL_CODED_SLICE_STSA_N ||
                                          nal_unit->nal_unit_type == NAL_CODED_SLICE_RADL_N ||
                                          nal_unit->nal_unit_type == NAL_CODED_SLICE_RASL_N));

  time_parameter->clock_tick = ((double) vui_parameters->vui_num_units_in_tick) / vui_parameters->vui_time_scale;
  if (vui_parameters->hrd_parameters.sub_pic_hrd_params_present_flag)
    time_parameter->clock_sub_tick = time_parameter->clock_tick / vui_parameters->hrd_parameters.tick_divisor;
  if (time_parameter->alt_flag) {
    cpb_delay_offset = sei_parameters->buf_param.cpb_delay_offset;
    dpb_delay_offset = sei_parameters->buf_param.dpb_delay_offset;
    if (vui_parameters->hrd_parameters.nal_hrd_parameters_present_flag) {
      init_cpb_dalay = sei_parameters->buf_param.nal_initial_alt_cpb_removal_delay[0];
      init_cpb_delay_offset = sei_parameters->buf_param.nal_initial_alt_cpb_removal_offset[0];
    } else {
      init_cpb_dalay = sei_parameters->buf_param.vcl_initial_alt_cpb_removal_delay[0];
      init_cpb_delay_offset = sei_parameters->buf_param.vcl_initial_alt_cpb_removal_offset[0];
    }
  } else {
    cpb_delay_offset = 0;
    dpb_delay_offset = 0;
    if (vui_parameters->hrd_parameters.nal_hrd_parameters_present_flag) {
      init_cpb_dalay = sei_parameters->buf_param.nal_initial_cpb_removal_delay[0];
      init_cpb_delay_offset = sei_parameters->buf_param.nal_initial_cpb_removal_offset[0];
    } else {
      init_cpb_dalay = sei_parameters->buf_param.vcl_initial_cpb_removal_delay[0];
      init_cpb_delay_offset = sei_parameters->buf_param.vcl_initial_cpb_removal_offset[0];
    }
  }

  if (vui_parameters->hrd_parameters.sub_pic_hrd_params_present_flag)
    bit_rate = vui_parameters->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_du_value[0] <<
               (6 + vui_parameters->hrd_parameters.bit_rate_scale);
  else
    bit_rate = vui_parameters->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_value[0] <<
               (6 + vui_parameters->hrd_parameters.bit_rate_scale);
  if (time_parameter->hrd_init_flag) {
    cpb_removal_delay_val = sei_parameters->pic_param.au_cpb_removal_delay;
    cpb_removal_delay_msb = 0;
  } else {
    max_cpb_removal_delay_val = 1 << vui_parameters->hrd_parameters.au_cpb_removal_delay_length;
    if (sei_parameters->pic_param.au_cpb_removal_delay <= time_parameter->precpb_removal_delay)
      cpb_removal_delay_msb = time_parameter->precpb_removal_delay_msb + max_cpb_removal_delay_val;
    else
      cpb_removal_delay_msb = time_parameter->precpb_removal_delay_msb;
    cpb_removal_delay_val = cpb_removal_delay_msb + sei_parameters->pic_param.au_cpb_removal_delay;
  }

  if (time_parameter->pre_nondiscard_flag) {
    time_parameter->precpb_removal_delay = sei_parameters->pic_param.au_cpb_removal_delay;
    time_parameter->precpb_removal_delay_msb = cpb_removal_delay_msb;
  }

  if (time_parameter->first_unit_flag) {
    if (time_parameter->hrd_init_flag) {
      au_nominal_remove_time = init_cpb_dalay / 90000.0;
    } else {
      if (sei_parameters->buf_param.concatenation_flag) {
        base_time = time_parameter->prefirstpic_au_nominal_time;
        tmp_cpb_removal_delay = cpb_removal_delay_val;
      } else {
        base_time = time_parameter->prenondiscardable_au_nominal_time;
        tmp_cpb_removal_delay = MAX(sei_parameters->buf_param.au_cpb_removal_delay_delta,
                                    Ceil(init_cpb_dalay / 90000.0 + (time_parameter->pre_au_finall_arrival_time -
                                         time_parameter->pre_au_nominal_remove_time) / time_parameter->clock_tick));
      }
      au_nominal_remove_time = base_time +
                               time_parameter->clock_tick * (tmp_cpb_removal_delay - cpb_delay_offset);
    }
  } else {
    au_nominal_remove_time = time_parameter->firstpic_au_nominal_time +
                             time_parameter->clock_tick * (cpb_removal_delay_val - cpb_delay_offset);
  }
  if (first_unit_flag) {
    time_parameter->firstpic_au_nominal_time = au_nominal_remove_time;
    time_parameter->prefirstpic_au_nominal_time = au_nominal_remove_time;
  }
  if (time_parameter->pre_nondiscard_flag)
    time_parameter->prenondiscardable_au_nominal_time = au_nominal_remove_time;
  time_parameter->pre_au_nominal_remove_time = au_nominal_remove_time;
  if (time_parameter->first_unit_flag)
    init_arrival_earliest_time = au_nominal_remove_time - (init_cpb_dalay / 90000.0);
  else
    init_arrival_earliest_time = au_nominal_remove_time - ((init_cpb_dalay + init_cpb_delay_offset) /90000.0);
  if (time_parameter->first_unit_flag)
    init_arrival_time = 0;
  else {
    if (vui_parameters->hrd_parameters.sub_hrd_parameters[layerid].cbr_flag[0])
      init_arrival_time = time_parameter->pre_au_finall_arrival_time;
    else
      init_arrival_time = MAX(time_parameter->pre_au_finall_arrival_time, init_arrival_earliest_time);
  }
  au_finall_arrival_time = init_arrival_time + ((double) stream_len) / bit_rate;
  time_parameter->pre_au_finall_arrival_time = au_finall_arrival_time;
  if ((!vui_parameters->hrd_parameters.low_delay_hrd_flag[layerid]) ||
      (au_nominal_remove_time >= au_finall_arrival_time))
    time_parameter->cpb_removal_time = au_nominal_remove_time;
  else
    time_parameter->cpb_removal_time = au_nominal_remove_time + time_parameter->clock_tick *
                                       Ceil((au_finall_arrival_time - au_nominal_remove_time) / time_parameter->clock_tick);
  if (/*!vui_parameters->hrd_parameters.sub_pic_hrd_params_present_flag*/1) {
    time_parameter->dpb_output_time = time_parameter->cpb_removal_time +
                                      time_parameter->clock_tick * sei_parameters->pic_param.pic_dpb_output_delay;
    if (time_parameter->first_unit_flag)
      time_parameter->dpb_output_time -= time_parameter->clock_tick * dpb_delay_offset;
  } else {
    time_parameter->dpb_output_time = time_parameter->cpb_removal_time +
        time_parameter->clock_sub_tick * sei_parameters->pic_param.pic_dpb_output_du_delay;
  }
  time_parameter->first_unit_flag = 0;
#if 0
  printf("*********************************************************\n");
  printf("init_arrival_time ========================= %f\n", init_arrival_time);
  printf("final_arrival_time ======================== %f\n", au_finall_arrival_time);
  printf("nominal remove time ======================= %f\n", au_nominal_remove_time);
  printf("cpb removal time ========================== %f\n", time_parameter->cpb_removal_time);
  printf("dpb output time =========================== %f\n", time_parameter->dpb_output_time);
  printf("*********************************************************\n");
#endif
  return (HANTRO_OK);
}

u32 HevcCheckTileInfo(struct Storage *storage,
                         struct PicParamSet *pps) {
  struct TileInfo *tile_info = &pps->tile_info;
  struct SeqParamSet *sps = storage->sps[pps->seq_parameter_set_id];
  u32 tmp, i, j;
  u32 prev_h, prev_w;

  if (sps == NULL) return HANTRO_OK;

  if (!pps->tiles_enabled_flag)
    return HANTRO_OK;

  u32 pic_width_in_ctbs =
    (sps->pic_width + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;
  u32 pic_height_in_ctbs =
    (sps->pic_height + (1 << sps->log_max_coding_block_size) - 1) >>
    sps->log_max_coding_block_size;

  if (pic_height_in_ctbs < tile_info->num_tile_rows ||
      pic_width_in_ctbs < tile_info->num_tile_columns)
    return HANTRO_NOK;

  if (!tile_info->uniform_spacing) {
    tmp = 0;
    for (i = 0; i < tile_info->num_tile_columns - 1; i++) {
      tmp += tile_info->col_width[i];
      if (tmp > pic_width_in_ctbs)
        return HANTRO_NOK;
    }

    tmp = 0;
    for (i = 0; i < tile_info->num_tile_rows - 1; i++) {
      tmp += tile_info->row_height[i];
      if (tmp > pic_height_in_ctbs)
        return HANTRO_NOK;
    }
  } else {
    tmp = 0;
    for (i = 0, prev_h = 0; i < tile_info->num_tile_rows; i++) {
      tmp = (i + 1) * pic_height_in_ctbs /
            tile_info->num_tile_rows;
      tile_info->row_height[i] = tmp - prev_h;
      prev_h = tmp;
      for (j = 0, prev_w = 0; j < tile_info->num_tile_columns; j++) {
        tmp = (j + 1) * pic_width_in_ctbs /
              tile_info->num_tile_columns;
        tile_info->col_width[j] = tmp - prev_w;
        prev_w = tmp;
      }
    }
  }
  return HANTRO_OK;
}
