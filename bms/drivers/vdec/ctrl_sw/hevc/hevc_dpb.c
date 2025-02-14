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

#include "hevc_cfg.h"
#include "hevc_dpb.h"
#include "hevc_slice_header.h"
#include "hevc_image.h"
#include "hevc_util.h"
#include "basetype.h"
#include "dwl.h"
#include "hevc_container.h"
#include "dec_log.h"

/* Function style implementation for IS_REFERENCE() macro to fix compiler
 * warnings */
static u32 IsReference(const struct DpbPicture *a) {
  return (a->status && a->status != EMPTY);
}

static u32 IsExisting(const struct DpbPicture *a) {
  return (a->status > NON_EXISTING && a->status != EMPTY);
}

static u32 IsShortTerm(const struct DpbPicture *a) {
  return (a->status == NON_EXISTING || a->status == SHORT_TERM);
}

static u32 IsLongTerm(const struct DpbPicture *a) {
  return a->status == LONG_TERM;
}

static void SetStatus(struct DpbPicture *pic, const enum DpbPictureStatus s) {
  pic->status = s;
}

static void SetPoc(struct DpbPicture *pic, const i32 poc) {
  pic->pic_order_cnt = poc;
}

static i32 GetPoc(struct DpbPicture *pic) {
  return (pic->status == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt);
}

#define IS_REFERENCE(a) IsReference(&(a))
#define IS_EXISTING(a) IsExisting(&(a))
#define IS_SHORT_TERM(a) IsShortTerm(&(a))
#define IS_LONG_TERM(a) IsLongTerm(&(a))
#define SET_STATUS(pic, s) SetStatus(&(pic), s)
#define SET_POC(pic, poc) SetPoc(&(pic), poc)
#define GET_POC(pic) GetPoc(&(pic))

#define MAX_NUM_REF_IDX_L0_ACTIVE 16

#define MEM_STAT_DPB 0x1
#define MEM_STAT_OUT 0x2
#define INVALID_MEM_IDX 0xFF

static void DpbBufFree(struct DpbStorage *dpb, u32 i);

static i32 FindDpbPic(struct DpbStorage *dpb, i32 poc);
static i32 FindArbitaryRefPic(struct DpbStorage *dpb);
static i32 FindDpbRefPic(struct DpbStorage *dpb, i32 poc, u32 type);

static /*@null@ */ struct DpbPicture *FindSmallestPicOrderCnt(
  struct DpbStorage *dpb);

static u32 OutputPicture(struct DpbStorage *dpb);

static u32 HevcDpbMarkAllUnused(struct DpbStorage *dpb);

static u32 HevcInitDpb(const void *dwl, struct DpbStorage *dpb,
                       struct DpbInitParams *dpb_params);

/* Output pictures if the are more outputs than reorder delay set in sps */
void HevcDpbCheckMaxLatency(struct DpbStorage *dpb, u32 max_latency) {
  u32 i;

  while (dpb->num_out_pics_buffered > max_latency) {
    i = OutputPicture(dpb);
    ASSERT(i == HANTRO_OK);
    (void)i;
  }
}

void HevcDpbCheckMaxLatency2(struct DpbStorage *dpb, u32 max_latency) {
  u32 i, j;
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (dpb->buffer[i].to_be_displayed &&
        dpb->buffer[i].pic_latency_count >= max_latency) {
      j = OutputPicture(dpb);
      ASSERT(j == HANTRO_OK);
      (void)j;
    }
  }
}

/* Update list of output pictures. To be called after slice header is decoded
 * and reference pictures determined based on that. */
void HevcDpbUpdateOutputList(struct DpbStorage *dpb) {
  u32 i;
  struct DpbPicture *tmp;
  struct Storage *storage = dpb->storage;

  /* dpb was initialized not to reorder the pictures -> output current
   * picture immediately */
  if (dpb->no_reordering) {
    /* we dont know the output buffer at this point as
     * HevcAllocateDpbImage() has not been called, yet
     */
  } else {
    u32 sublayer = storage->active_sps->max_sub_layers - 1;

    /* remove all unused buffers with pic_output_flag = 0 */
    for (i = 0; i <= dpb->dpb_size; i++) {
      tmp = NULL;
      if (dpb->buffer[i].to_be_displayed &&
          !IS_REFERENCE(dpb->buffer[i]) &&
          dpb->buffer[i].pic_output_flag == 0) {
        tmp = dpb->buffer + i;

        /* remove it from DPB */
        tmp->to_be_displayed = HANTRO_FALSE;
        if (!IS_REFERENCE(*tmp)) {
          if (dpb->fullness > 0)
            dpb->fullness--;
        }

        if (storage->pp_enabled) {
          InputQueueReturnBuffer(storage->pp_buffer_queue,
            DWL_GET_DEVMEM_ADDR(*(tmp->pp_data)));
          HevcReturnDMVBuffer(dpb, tmp->dmv_data->bus_address);
        }

        if (tmp->sei_param)
          tmp->sei_param->sei_status = SEI_UNUSED;
      }
    }

    /* C.5.2.2
     * The number of pictures in the DPB that are marked as "needed for output"
     * is greater than sps_max_num_reorder_pics[ HighestTid ].
     */
    while (dpb->num_out_pics_buffered >
           storage->active_sps->max_num_reorder_pics[sublayer]) {
      i = OutputPicture(dpb);
      ASSERT(i == HANTRO_OK);
      (void)i;
    }

    /* output pictures if buffer full. */
    while (dpb->fullness > dpb->real_size) {
      i = OutputPicture(dpb);
      if (i != HANTRO_OK) break;
    }
  }
}

/* Update list of output pictures. To be called before HDRS_RDY is returned and
   no_output_of_prior_pics_flag = 1 or CRA picture with no rasl output = 1 */
void HevcDpbUpdateOutputList2(struct DpbStorage *dpb) {
  u32 i;
  struct DpbPicture *tmp;
  struct Storage *storage = dpb->storage;

  /* dpb was initialized not to reorder the pictures -> output current
   * picture immediately */
  if (dpb->no_reordering) {
    /* we dont know the output buffer at this point as
     * HevcAllocateDpbImage() has not been called, yet
     */
  } else if(storage) {

    u32 sublayer = storage->active_sps->max_sub_layers - 1;

    /* remove all unused buffers with pic_output_flag = 0 */
    for (i = 0; i <= dpb->dpb_size; i++) {
      tmp = NULL;
      if (dpb->buffer[i].to_be_displayed &&
          !IS_REFERENCE(dpb->buffer[i]) &&
          dpb->buffer[i].pic_output_flag == 0) {
        tmp = dpb->buffer + i;

        /* remove it from DPB */
        tmp->to_be_displayed = HANTRO_FALSE;
        if (!IS_REFERENCE(*tmp)) {
          if (dpb->fullness > 0)
            dpb->fullness--;
        }

        if (storage->pp_enabled) {
          InputQueueReturnBuffer(storage->pp_buffer_queue,
            DWL_GET_DEVMEM_ADDR(*(tmp->pp_data)));
          HevcReturnDMVBuffer(dpb, tmp->dmv_data->bus_address);
        }

        if (tmp->sei_param)
          tmp->sei_param->sei_status = SEI_UNUSED;
      }
    }

    /* C.5.2.2
     * The number of pictures in the DPB that are marked as "needed for output"
     * is greater than sps_max_num_reorder_pics[ HighestTid ].
     */
    while (dpb->num_out_pics_buffered >
           storage->active_sps->max_num_reorder_pics[sublayer]) {
      i = OutputPicture(dpb);
      ASSERT(i == HANTRO_OK);
      (void)i;
    }

    if (storage->active_sps->max_latency_increase[sublayer]) {
      u32 max_latency =
        storage->active_sps->max_num_reorder_pics[sublayer] +
        storage->active_sps->max_latency_increase[sublayer] - 1;
      HevcDpbCheckMaxLatency2(storage->dpb, max_latency);
    }

    /* output pictures if buffer full */
    while (dpb->num_out_pics_buffered  > dpb->real_size) {
      OutputPicture(dpb);
    }
  }
}


/* Returns pointer to reference picture at location 'index' in the DPB. */
u8 *HevcGetRefPicData(const struct DpbStorage *dpb, u32 index) {

  if (index >= dpb->dpb_size)
    return (NULL);
  else if (!IS_EXISTING(dpb->buffer[index]))
    return (NULL);
  else
    return (u8 *)(dpb->buffer[index].data->virtual_address);
}

/* Returns pointer to location where next picture shall be stored. */
void *HevcAllocateDpbImage(struct DpbStorage *dpb, i32 pic_order_cnt,
                           i32 pic_order_cnt_lsb, u32 is_idr,
                           u32 current_pic_id, u32 is_tsa_ref,
                           const void *dec_inst) {
  u32 i, j;
  u32 dmv_buf_id = 0;
  u32 to_be_displayed;
  u32 *p;
  struct Storage *storage = dpb->storage;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
#ifndef ASIC_TRACE_SUPPORT
  /* find first unused dmv buffer */
  if (dpb->tot_dmv_buffers > 0 && storage->pp_enabled) {
    pthread_mutex_lock(dpb->dmv_buffer_mutex);
    for (dmv_buf_id = 0; dmv_buf_id < dpb->tot_dmv_buffers; dmv_buf_id++) {
      if (dpb->dmv_buf_status[dmv_buf_id] == BUF_FREE) {
        break;
      }
    }
    pthread_mutex_unlock(dpb->dmv_buffer_mutex);

#ifdef GET_FREE_BUFFER_NON_BLOCK
    if (dmv_buf_id == dpb->tot_dmv_buffers)
      return NULL;
#else
    if (dmv_buf_id == dpb->tot_dmv_buffers) {
      pthread_mutex_lock(dpb->dmv_buffer_mutex);
      dmv_buf_id = 0;
      while (dmv_buf_id < dpb->tot_dmv_buffers) {
        if (dpb->dmv_buf_status[dmv_buf_id] == BUF_FREE) {
          break;
        }

        dmv_buf_id++;
        if (dmv_buf_id == dpb->tot_dmv_buffers) {
          pthread_cond_wait(dpb->dmv_buffer_cv, dpb->dmv_buffer_mutex);
          dmv_buf_id = 0;
        }
      }
      pthread_mutex_unlock(dpb->dmv_buffer_mutex);
    }
#endif
  }
#endif

  /* find first unused and not-to-be-displayed pic */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (!dpb->buffer[i].to_be_displayed && !IS_REFERENCE(dpb->buffer[i]) &&
        ((!IsBufferReferenced(dpb->fb_list, dpb->buffer[i].mem_idx) &&
         dec_cont->use_ext_dpb_size) || !dec_cont->use_ext_dpb_size))
      break;
  }

  /* for interal dpb buffer */
  if (dec_cont->use_ext_dpb_size && i > MIN(dpb->dpb_size, dpb->tot_buffers) &&
      !IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    if (i < MAX_DPB_SIZE + 1) {
      for (j = i; j < dpb->tot_buffers; j++) {
        if (IsFreeById(dpb->fb_list, dpb->pic_buff_id[j]) == HANTRO_OK ||
            dpb->buffer[j].data == NULL)
          break;
      }
      HevcAddOneIntDpb(dec_cont, dpb, j);

      /* also need add a new pp buffer if necessary. */
      goto RETURN_ADD_EXT_DPB;
    } else {
      j = i;
      HevcAddOneIntDpb(dec_cont, dpb, j);

      /* also need add a new pp buffer if necessary. */
      goto RETURN_ADD_EXT_DPB;
    }
  } else if (dec_cont->use_ext_dpb_size &&
      IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    if (dpb->dpb_size == MAX_DPB_SIZE && i > dpb->dpb_size) {
      /* we will find a new free buffer replace to current pointed buffer when dpb is full*/
      i = dpb->dpb_size;
    }
  }

#ifdef GET_FREE_BUFFER_NON_BLOCK
  if (i > MIN(dpb->dpb_size, dpb->tot_buffers))
    goto RETURN_ADD_EXT_DPB;
#endif

  /* Though i should NOT exceed dpb_size, in some error streams it does happen.
   * As a workaround, we set it to 0. */
  if (i > dpb->dpb_size)
    i = 0;

  //ASSERT(i <= dpb->dpb_size);
  dpb->current_out = &dpb->buffer[i];
  dpb->current_out_pos = i;
  dpb->current_out->status = EMPTY;

  if (storage->pp_enabled) {
    dpb->current_out->pp_data = InputQueueGetBuffer(
                                  storage->pp_buffer_queue, 0);
    if (dpb->current_out->pp_data == NULL) {
      /* can't get pp buffer, so return sei_param */
      if (storage->sei_param_curr != NULL)
        storage->sei_param_curr->sei_status = SEI_UNUSED;
      goto RETURN_NULL;
    }
    /* please not change memset logic for FPGA verification */
#ifdef ENABLE_FPGA_VERIFICATION
/* for multilayer stream can't clean the pp buffer.*/
    if (!dec_cont->heif_mode) {
      if (dpb->current_out->pp_data->virtual_address != NULL) {
        DWLmemset(dpb->current_out->pp_data->virtual_address, 0x0, dpb->current_out->pp_data->size);
      }
    }
#ifdef SUPPORT_DMA
    /* update device buffer by host buffer */
    DWLDMATransData((addr_t)dpb->current_out->pp_data->bus_address,
                    (void *)dpb->current_out->pp_data->virtual_address,
                    dpb->current_out->pp_data->size, HOST_TO_DEVICE);
#endif
#endif
  }

#if !defined(ASIC_TRACE_SUPPORT) || !defined(SUPPORT_MULTI_CORE)
  /* To avoid multicore top simultion buffer confliction, we always find a new
     free buffer. */
  if (IsBufferReferenced(dpb->fb_list, dpb->current_out->mem_idx))
#endif
  {
    u32 new_id = GetFreePicBuffer(dpb->fb_list, dpb->current_out->mem_idx);

    if(new_id == FB_NOT_VALID_ID) {
      if (storage->pp_enabled) {
        if (dpb->current_out->pp_data != NULL) {
          InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->current_out->pp_data)));
        }
      }
      /* can't get reference buffer, so return sei_param */
      if (storage->sei_param_curr != NULL)
        storage->sei_param_curr->sei_status = SEI_UNUSED;

      goto RETURN_NULL;
    }

    if (new_id != dpb->current_out->mem_idx) {
      SetFreePicBuffer(dpb->fb_list, dpb->current_out->mem_idx);
      dpb->current_out->mem_idx = new_id;
      dpb->current_out->data = GetDataById(dpb->fb_list, new_id);
    }
  }
#if 0
  if (dpb->bumping_flag) {
    while(HevcDpbHrdBumping(dpb) == HANTRO_OK);
    dpb->bumping_flag = 0;
  }
#endif
  ASSERT(dpb->current_out->data);
  if (dpb->current_out->data == NULL) return NULL;

  to_be_displayed = dpb->no_reordering ? HANTRO_FALSE : HANTRO_TRUE;

  {
    struct DpbPicture *current_out = dpb->current_out;
#ifndef ASIC_TRACE_SUPPORT
    if (storage->pp_enabled) {
      current_out->dmv_data = &dpb->dmv_buffers[dmv_buf_id];
      current_out->dmv_mem_idx = dmv_buf_id;
    } else
#endif
    {
      current_out->dmv_mem_idx = dpb->current_out->mem_idx;
      current_out->dmv_data = &dpb->dmv_buffers[dpb->current_out->mem_idx];
      current_out->dmv_data->bus_address =
          current_out->data->bus_address + dpb->dir_mv_offset;
      current_out->dmv_data->virtual_address =
          (u32 *)((u8 *)(current_out->data->virtual_address) + dpb->dir_mv_offset);
    }
    if ((dec_cont->skip_frame == DEC_SKIP_NON_REF_RECON &&
        dec_cont->pp_enabled &&
        IS_SLNR_NAL_UNIT(dec_cont->storage.prev_nal_unit) &&
        dec_cont->storage.active_vps->vps_max_sub_layers == 1) ||
        (dec_cont->pp_enabled && dec_cont->skip_non_intra) ||
        (dec_cont->pp_enabled && dec_cont->partial_decoding) ||
        (dec_cont->asic_buff->disable_out_writing == 1))
      current_out->dec_out_dis = 1;
    else
      current_out->dec_out_dis = 0;
    current_out->is_idr = is_idr;
    if(IS_I_SLICE(storage->slice_header->slice_type))
      current_out->pic_code_type = DEC_PIC_TYPE_I;
    else if(IS_P_SLICE(storage->slice_header->slice_type))
      current_out->pic_code_type = DEC_PIC_TYPE_P;
    else
      current_out->pic_code_type = DEC_PIC_TYPE_B;
    current_out->is_tsa_ref = is_tsa_ref;
    current_out->error_ratio = 0;
    current_out->error_info = DEC_NO_ERROR;
    current_out->num_tile_columns = storage->active_pps->tile_info.num_tile_columns;
    current_out->num_tile_rows = storage->active_pps->tile_info.num_tile_rows;
    current_out->pic_num = (i32)current_pic_id;
    current_out->pic_id = (i32)current_pic_id;
    if (storage->sei_param_curr &&
        storage->sei_param_curr->decode_id == (i32)current_pic_id) {
      current_out->sei_param = storage->sei_param_curr;
      current_out->sei_param->sei_status = SEI_USED;
    } else {
      current_out->sei_param = NULL;
    }
    // current_out->sei_param = storage->sei_param_curr;
    // if (current_out->sei_param)
    //   current_out->sei_param->sei_status = SEI_USED;
    current_out->pic_output_flag = storage->slice_header->pic_output_flag;
    current_out->pic_latency_count = 0;
    current_out->chroma_format_idc = dpb->chroma_format_idc;
    SET_STATUS(*current_out, SHORT_TERM);
    HevcBindDMVBuffer(dpb, current_out->dmv_data);
    SET_POC(*current_out, pic_order_cnt);
    current_out->pic_order_cnt_lsb = pic_order_cnt_lsb;
    current_out->to_be_displayed = to_be_displayed;
    current_out->is_gdr_frame = storage->is_gdr_frame;
    HevcOutputDMVBuffer(dpb, current_out->dmv_data->bus_address);
    if (current_out->to_be_displayed && current_out->pic_output_flag)
      dpb->num_out_pics_buffered++;
    dpb->fullness++;
    dpb->num_ref_frames++;

    /* update pic_latency_count */
    for (i = 0; i <= dpb->dpb_size; i++) {
      if (dpb->buffer[i].to_be_displayed &&
          GET_POC(dpb->buffer[i]) > pic_order_cnt) {
        dpb->buffer[i].pic_latency_count++;
      }
    }
  }

  /* store POCs of ref pic buffer for current pic */
  p = dpb->current_out->ref_poc;
  for (i = 0; i < MAX_DPB_SIZE; i++) *p++ = dpb->buffer[i].pic_order_cnt;

  (void) dmv_buf_id;
  return dpb->current_out->data;

RETURN_ADD_EXT_DPB:
  if (dec_cont->use_ext_dpb_size) {
    if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
      /* configure to add a new external dpb buffer when there are no decoding buffer */
      dec_cont->buf_to_free = NULL;
      dec_cont->buf_type = REFERENCE_BUFFER;
      dec_cont->buf_num = 1;
      dec_cont->add_extra_ext_buf = 1;
    } else {
      /* configure to add a new external pp buffer when added a new internal dpb buffer */
      dec_cont->buf_to_free = NULL;
      dec_cont->buf_type = DOWNSCALE_OUT_BUFFER;
      dec_cont->buf_num = 1;
      dec_cont->add_extra_ext_buf = 1;
    }
  }
RETURN_NULL:
  return NULL;
}

/* Initializes DPB.  Reserves memories for the buffer, reference picture list
 * and output buffer. dpb_size indicates the maximum DPB size indicated by the
 * level_idc in the stream.  If no_reordering flag is HANTRO_FALSE the DPB
 * stores dpb_size pictures for display reordering purposes. On the other hand,
 * if the flag is HANTRO_TRUE the DPB only stores max_ref_frames reference
 * pictures and outputs all the pictures immediately. */
/* This function is only called when DPB are external buffer, and the DPB is sufficient
 * for new sequence and no re-allocating is needed. Just setting new offsets are needed. */
u32 HevcReInitDpb(const void *dec_inst, struct DpbStorage *dpb,
                  struct DpbInitParams *dpb_params) {
  u32 i;
  struct FrameBufferList *fb_list = dpb->fb_list;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  u32 old_dpb_size = dpb->dpb_size;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));

  //ASSERT(dpb_params->pic_size);
  //ASSERT(dpb_params->dpb_size);

  dpb->pic_size = dpb_params->pic_size;
  dpb->buff_size = dpb_params->buff_size;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;

  if (dec_cont->use_ext_dpb_size) {
    /* not change the size */
    dpb->real_size = dpb->real_size;
    dpb->dpb_size = dpb->dpb_size;
  } else {
    dpb->real_size = dpb_params->dpb_size;
    dpb->dpb_size = dpb_params->dpb_size + 1;
  }

  dpb->max_ref_frames = dpb_params->dpb_size;
  dpb->no_reordering = dpb_params->no_reordering;
  dpb->fullness = 0;
  (void)HevcDpbMarkAllUnused(dpb);
  RemoveTempOutputAll(dpb->fb_list, dpb);
  dpb->num_out = 0;
  dpb->out_index_w = dpb->out_index_r = 0;

  /* as all dpb set unused, set all sei status unused. */
  if (dec_cont->storage.sei_param_num) {
    for (u32 i = 0; i < dec_cont->storage.sei_param_num; i++)
      dec_cont->storage.sei_param[i]->sei_status = SEI_UNUSED;
  }
  dpb->num_out_pics_buffered = 0;
  dpb->num_ref_frames = 0;
  dpb->prev_ref_frame_num = 0;
  dpb->prev_out_idx = INVALID_MEM_IDX;

#if 0
  dpb->tot_buffers = dpb->dpb_size + 2 + dpb_params->n_extra_frm_buffers;
  if (dpb->tot_buffers > MAX_PIC_BUFFERS)
    dpb->tot_buffers = MAX_PIC_BUFFERS;
  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER))
    dec_cont->min_buffer_num = dpb->dpb_size + 2;   /* We need at least (dpb_size+2) output buffers before starting decoding. */
  else
    dec_cont->min_buffer_num = dpb->dpb_size + 1;
#endif

  /* allocate 32 bytes for multicore status fields */
  /* locate it after picture and before direct MV */
  /* align sync_mc buffer, storage sync bytes adjoining to dir mv*/
  /* Update DMV buffer info */
  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  dpb->dir_mv_offset = dpb_params->pic_size + (dpb_params->mono_chrome ? 0 :
                       NEXT_MULTIPLE(dpb_params->pic_size / (dpb_params->chroma_format_idc == 2 ? 1 : 2), ref_buffer_align)) +
                       NEXT_MULTIPLE(32, ref_buffer_align);

  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    dpb->dmv_buffers[i].bus_address = dpb->pic_buffers[i].bus_address + dpb->dir_mv_offset;
    dpb->dmv_buffers[i].virtual_address = (u32 *)((u8 *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset);
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);

  dpb->sync_mc_offset = dpb->dir_mv_offset - 32;

  if (dpb_params->tbl_sizey) {
    dpb->cbs_tbl_offsety = dpb_params->buff_size - dpb_params->tbl_sizey
                           - dpb_params->tbl_sizec;
    dpb->cbs_tbl_offsetc = dpb_params->buff_size - dpb_params->tbl_sizec;
    dpb->cbs_tbl_size = dpb_params->tbl_sizey + dpb_params->tbl_sizec;
  }

  if (old_dpb_size < dpb->dpb_size) {
    //ReInitList(fb_list);

    for (i = old_dpb_size + 1; i < dpb->dpb_size + 1; i++) {
      /* Find a unused buffer j. */
      u32 j, id;
      for (j = 0; j < MAX_PIC_BUFFERS; j++) {
        u32 found = 0;
        for (u32 k = 0; k < i; k++) {
          if (dpb->pic_buffers[j].bus_address == dpb->buffer[k].data->bus_address) {
            found = 1;
            break;
          }
        }
        if (!found)
          break;
      }
      ASSERT(j < MAX_PIC_BUFFERS);
      dpb->buffer[i].data = dpb->pic_buffers + j;
      id = GetIdByData(fb_list, (void *)dpb->buffer[i].data);
      MarkIdAllocated(fb_list, id);
      dpb->buffer[i].mem_idx = id;
      dpb->pic_buff_id[j] = id;
    }
  } else if (old_dpb_size > dpb->dpb_size) {
    for (i = dpb->dpb_size + 1; i < old_dpb_size + 1; i++) {
      /* Remove extra dpb buffers from DPB. */
      MarkIdFree(fb_list, dpb->buffer[i].mem_idx);
    }
  }

  (void) ref_buffer_align;

  return (HANTRO_OK);
}

u32 HevcInitDpb(const void *dec_inst, struct DpbStorage *dpb,
                struct DpbInitParams *dpb_params) {
  u32 i;
  struct FrameBufferList *fb_list = dpb->fb_list;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  static int memset_done = 0;
  u32 ref_buffer_align = MAX(16, ALIGN(dec_cont->align));

  //ASSERT(dpb_params->pic_size);
  //ASSERT(dpb_params->dpb_size);

  /* we trust our memset; ignore return value */
  /* TODO(min): memset only once. */
  if (!memset_done) {
    (void)DWLmemset(dpb, 0, sizeof(*dpb)); /* make sure all is clean */
    (void)DWLmemset(dpb->pic_buff_id, FB_NOT_VALID_ID, sizeof(dpb->pic_buff_id));
    memset_done = 1;
  }

  dpb->storage = &dec_cont->storage;

  /* restore value */
  dpb->fb_list = fb_list;
  dpb->dmv_buffer_mutex = &dec_cont->dmv_buffer_mutex;
  dpb->dmv_buffer_cv = &dec_cont->dmv_buffer_cv;

  dpb->pic_size = dpb_params->pic_size;
  dpb->buff_size = dpb_params->buff_size;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;

  dpb->real_size = dpb_params->dpb_size;

  /* set dpb buffer numbers according to user's configuration */
  if (dec_cont->use_ext_dpb_size)
    dpb->dpb_size = dec_cont->num_buffers;
  else
    dpb->dpb_size = dpb_params->dpb_size + 1;

  dpb->max_ref_frames = dpb_params->dpb_size;
  dpb->no_reordering = dpb_params->no_reordering;
  dpb->chroma_format_idc = dpb_params->chroma_format_idc;
  dpb->fullness = 0;
  dpb->num_out_pics_buffered = 0;
  dpb->num_ref_frames = 0;
  dpb->prev_ref_frame_num = 0;
  dpb->num_out = 0;
  dpb->out_index_w = 0;
  dpb->out_index_r = 0;
  dpb->prev_out_idx = INVALID_MEM_IDX;

  dpb->tot_buffers = dpb->dpb_size + 2 + dpb_params->n_extra_frm_buffers;
  /* figure out extra buffers for multicore */
  if (dpb_params->n_cores > 1) {
    /* one extra buffer for each core */
    /* do not allocate twice for multiview */
    dpb->tot_buffers += dpb_params->n_cores;
  }
#if defined(ASIC_TRACE_SUPPORT) && defined(SUPPORT_MULTI_CORE)
  dpb->tot_buffers += 10;
#endif

  if (dpb->tot_buffers > MAX_PIC_BUFFERS)
    dpb->tot_buffers = MAX_PIC_BUFFERS;
  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER) && (!dec_cont->storage.realloc_ext_buf)) {
    dec_cont->min_buffer_num = dpb->dpb_size + 2;   /* We need at least (dpb_size+2) output buffers before starting decoding. */
    dec_cont->ext_buffer_num = 0;
  } else { //pp buffer
    if(dpb->no_reordering)
      dec_cont->min_buffer_num = 1 + 1; /* one is output, one is decode */
    else
      dec_cont->min_buffer_num = dpb->dpb_size + 1;
  }

  /* allocate 32 bytes for multicore status fields */
  /* locate it after picture and before direct MV */
  /* align sync_mc buffer, storage sync bytes adjoining to dir mv*/
  dpb->dir_mv_offset = dpb_params->pic_size + (dpb_params->mono_chrome ? 0 :
                       NEXT_MULTIPLE(dpb_params->pic_size / (dpb_params->chroma_format_idc == 2 ? 1 : 2), ref_buffer_align)) +
                       NEXT_MULTIPLE(32, ref_buffer_align);
  dpb->sync_mc_offset = dpb->dir_mv_offset - 32;

  if (dpb_params->tbl_sizey) {
    dpb->cbs_tbl_offsety = dpb_params->buff_size - dpb_params->tbl_sizey
                           - dpb_params->tbl_sizec;
    dpb->cbs_tbl_offsetc = dpb_params->buff_size - dpb_params->tbl_sizec;
    dpb->cbs_tbl_size = dpb_params->tbl_sizey + dpb_params->tbl_sizec;
  }
  dpb->dpb_reset = 1;
  memset_done = 0;
  if (!dpb->out_buf) {
    dpb->out_buf = DWLmalloc((MAX_DPB_SIZE + 1) * sizeof(struct DpbOutPicture));

    if (dpb->out_buf == NULL) {
      return (MEMORY_ALLOCATION_ERROR);
    }
  }

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  dpb->tot_dmv_buffers = dpb->tot_buffers;
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    for (i = 0; i < dpb->tot_buffers; i++) {
      /* yuv picture + direct mode motion vectors */
      /* TODO(min): request external buffers. */
      if (DWL_DEVMEM_COMPARE(dpb->pic_buffers[i], DWL_DEVMEM_INIT)) {
        dec_cont->next_buf_size = dpb_params->buff_size;
        dec_cont->buf_to_free = NULL;
        dec_cont->buf_type = REFERENCE_BUFFER;
        dec_cont->buf_num = dpb->tot_buffers;
        dec_cont->buffer_index = i;
        dec_cont->release_buffer = 1;
        return DEC_WAITING_FOR_BUFFER;
      }
    }
  } else {
    for (i = 0; i < dpb->tot_buffers; i++) {
      /* yuv picture + direct mode motion vectors */
      if (dpb->storage->realloc_int_buf) {
        dpb->n_int_buf_size = dpb_params->buff_size;
        dpb->pic_buffers[i].mem_type = DWL_MEM_TYPE_DPB;
        if (DWLMallocRefFrm(dec_cont->dwl, dpb_params->buff_size, dpb->pic_buffers + i) != 0)
          return (MEMORY_ALLOCATION_ERROR);
        pthread_mutex_lock(dpb->dmv_buffer_mutex);
        dpb->dmv_buffers[i].bus_address = dpb->pic_buffers[i].bus_address + dpb->dir_mv_offset;
        dpb->dmv_buffers[i].virtual_address = (u32 *)((u8 *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset);
        dpb->dmv_buf_status[i] = BUF_FREE;
        pthread_mutex_unlock(dpb->dmv_buffer_mutex);
      }

      if (i < dpb->dpb_size + 1 && (i < (MAX_DPB_SIZE + 1))) {
        u32 id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + i);
        if (id == FB_NOT_VALID_ID) return MEMORY_ALLOCATION_ERROR;

        dpb->buffer[i].data = dpb->pic_buffers + i;
        dpb->buffer[i].mem_idx = id;
        dpb->pic_buff_id[i] = id;
      } else {
        u32 id = AllocateIdFree(dpb->fb_list, dpb->pic_buffers + i);
        if (id == FB_NOT_VALID_ID) return MEMORY_ALLOCATION_ERROR;

        dpb->pic_buff_id[i] = id;
      }

#ifndef MEM_ONLY_DEV_CHECK
      {
        void *base =
          //(char *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset;
          (char *)(dpb->dmv_buffers[i].virtual_address);
        (void)DWLmemset(base, 0, dpb_params->buff_size - dpb->dir_mv_offset);
      }
#endif
    }
  }

  return (HANTRO_OK);
}

/* Reset the DPB. This function should be called when an IDR slice (other than
 * the first) activates new sequence parameter set.  Function calls
 * HevcFreeDpb to free old allocated memories and HevcInitDpb to
 * re-initialize the DPB. Same inputs, outputs and returns as for
 * HevcInitDpb. */
u32 HevcResetDpb(const void *dec_inst, struct DpbStorage *dpb,
                 struct DpbInitParams *dpb_params) {
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  dpb->dpb_reset = 0;

  // Only reset DPB once for a sequence.
  if (dec_cont->reset_dpb_done)
    return HANTRO_OK;

  if ((!dec_cont->use_adaptive_buffers && dpb->pic_size == dpb_params->pic_size) ||
      (dec_cont->use_adaptive_buffers &&
       ((IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER) &&
         dec_cont->ext_buffer_size >= dpb_params->buff_size) ||
        (!IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER) &&
         dpb->n_int_buf_size >= dpb_params->buff_size)))) {
    dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;

    dpb->no_reordering = dpb_params->no_reordering;
    dpb->flushed = 0;

    /*
     * 1. DPB are external buffers,
     *    a) no adaptive method: dpb size are same as old ones;
     *    b) use new adaptive method, there are enough "guard buffers" added;
     * 2. DPB are internal buffers, and number of dpb buffer are same.
     */
    if ((IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER) &&
         ((!dec_cont->use_adaptive_buffers && dpb->real_size == dpb_params->dpb_size) ||
          (dec_cont->use_adaptive_buffers && !dec_cont->storage.realloc_ext_buf))) ||
        (!IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER) &&
         !dec_cont->storage.realloc_int_buf)) {
      /* number of pictures and DPB size are not changing */
      /* no need to reallocate DPB */
      dec_cont->reset_dpb_done = 1;
      HevcReInitDpb(dec_inst, dpb, dpb_params);
      return (HANTRO_OK);
    }
  }

  dec_cont->reset_dpb_done = 1;
  HevcFreeDpbExt(dec_inst, dpb);

  return HevcInitDpb(dec_inst, dpb, dpb_params);
}

/* add a new dpb buffer when there are no decoding buffer for internal ref frame. */
u32 HevcAddOneIntDpb(const void *dec_inst, struct DpbStorage *dpb, u32 index) {
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  u32 id;

  if (index < MAX_DPB_SIZE + 1) {

    /* if had free dpb, move free dpb to tail and reset free dpb data */
    if (index < dpb->tot_buffers) {
      id = GetIdByData(dpb->fb_list, dpb->pic_buffers + index);
      dpb->pic_buffers[dpb->tot_buffers] = dpb->pic_buffers[index];
      dpb->pic_buff_id[dpb->tot_buffers] = dpb->pic_buff_id[index];
      ResetDataById(dpb->fb_list, dpb->pic_buffers + dpb->tot_buffers, id);
    }

    /* then add a new dpb */
    dpb->pic_buffers[index].mem_type = DWL_MEM_TYPE_DPB;
    if (DWLMallocRefFrm(dec_cont->dwl, dpb->n_int_buf_size, dpb->pic_buffers + index) != 0)
      return (MEMORY_ALLOCATION_ERROR);

    u32 id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + index);
    if (id == FB_NOT_VALID_ID) {
      DWLFreeRefFrm(dec_cont->dwl, dpb->pic_buffers + index);
      return MEMORY_ALLOCATION_ERROR;
    }

    dpb->buffer[index].data = dpb->pic_buffers + index;
    dpb->buffer[index].mem_idx = id;
    dpb->pic_buff_id[index] = id;

    dpb->dpb_size++;
  } else {
    index = dpb->tot_buffers;
    /* add a new dpb */
    dpb->pic_buffers[index].mem_type = DWL_MEM_TYPE_DPB;
    if (DWLMallocRefFrm(dec_cont->dwl, dpb->n_int_buf_size, dpb->pic_buffers + index) != 0)
      return (MEMORY_ALLOCATION_ERROR);
    id = AllocateIdFree(dpb->fb_list, dpb->pic_buffers + index);
    if (id == FB_NOT_VALID_ID) return MEMORY_ALLOCATION_ERROR;

    dpb->pic_buff_id[index] = id;
  }
  dpb->tot_buffers++;

#ifndef MEM_ONLY_DEV_CHECK
  {
    void *base =
      (char *)(dpb->pic_buffers[index].virtual_address) + dpb->dir_mv_offset;
    (void)DWLmemset(base, 0, dpb->n_int_buf_size - dpb->dir_mv_offset);
  }
#endif

  return (HANTRO_OK);
}

/* add a new dpb buffer when there are no decoding buffer for external ref frame. */
u32 HevcAddOneExtDpb(const void *dec_inst, struct DpbStorage *dpb, u32 index,
                          struct DWLLinearMem *info) {
  u32 id;

  if (index >= dpb->tot_buffers && index < MAX_DPB_SIZE + 1) {
    /* no free dpb: add a new dpb directly*/
    dpb->pic_buffers[index] = *info;
    id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + index);
    if (id == FB_NOT_VALID_ID) return MEMORY_ALLOCATION_ERROR;

    dpb->buffer[index].data = dpb->pic_buffers + index;
    dpb->buffer[index].mem_idx = id;
    dpb->pic_buff_id[index] = id;

    dpb->dpb_size++;
  } else if (index < dpb->tot_buffers && index < MAX_DPB_SIZE + 1) {
    /* if had free dpb, move free dpb to tail */
    id = GetIdByData(dpb->fb_list, dpb->pic_buffers + index);
    dpb->pic_buffers[dpb->tot_buffers] = dpb->pic_buffers[index];
    dpb->pic_buff_id[dpb->tot_buffers] = dpb->pic_buff_id[index];
    ResetDataById(dpb->fb_list, dpb->pic_buffers + dpb->tot_buffers, id);

    /* then add a new dpb */
    dpb->pic_buffers[index] = *info;
    id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + index);
    if (id == FB_NOT_VALID_ID) return MEMORY_ALLOCATION_ERROR;

    dpb->buffer[index].data = dpb->pic_buffers + index;
    dpb->buffer[index].mem_idx = id;
    dpb->pic_buff_id[index] = id;

    dpb->dpb_size++;
  } else if (index >= MAX_DPB_SIZE + 1) {
    index = dpb->tot_buffers;

    dpb->pic_buffers[index] = *info;
    /* Here we need allocate a USED id, so that this buffer will be added as free buffer in SetFreePicBuffer. */
    id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + index);
    if (id == FB_NOT_VALID_ID) return MEMORY_ALLOCATION_ERROR;
    dpb->pic_buff_id[index] = id;

    SetFreePicBuffer(dpb->fb_list, id);
  }

  dpb->tot_buffers++;

#ifndef MEM_ONLY_DEV_CHECK
  {
    void *base =
      (char *)(dpb->pic_buffers[index].virtual_address) + dpb->dir_mv_offset;
    (void)DWLmemset(base, 0, info->logical_size - dpb->dir_mv_offset);
  }
#endif

  return (HANTRO_OK);
}


/* Determines picture order counts of the reference pictures (of current
 * and subsequenct pictures) based on delta values in ref pic sets. */
void HevcSetRefPicPocList(struct DpbStorage *dpb,
                          struct SliceHeader *slice_header, i32 pic_order_cnt,
                          struct SeqParamSet *sps) {

  u32 i, j, k;
  i32 poc, poc_lsb;
  u32 tot_long_term;
  u32 tot_ref_num;
  struct StRefPicSet *ref;
  u32 old_dpb_size;

  ref = &slice_header->st_ref_pic_set;

  for (i = 0, j = 0, k = 0; i < ref->num_negative_pics; i++) {
    if (ref->elem[i].used_by_curr_pic)
      dpb->poc_st_curr[j++] = pic_order_cnt + ref->elem[i].delta_poc;
    else
      dpb->poc_st_foll[k++] = pic_order_cnt + ref->elem[i].delta_poc;
  }
  dpb->num_poc_st_curr_before = j;
  for (; i < ref->num_positive_pics + ref->num_negative_pics; i++) {
    if (ref->elem[i].used_by_curr_pic)
      dpb->poc_st_curr[j++] = pic_order_cnt + ref->elem[i].delta_poc;
    else
      dpb->poc_st_foll[k++] = pic_order_cnt + ref->elem[i].delta_poc;
  }
  dpb->num_poc_st_curr = j;
  dpb->num_poc_st_foll = k;

  tot_long_term =
    slice_header->num_long_term_pics + slice_header->num_long_term_sps;
  for (i = 0, j = 0, k = 0; i < tot_long_term; i++) {
    if (i < slice_header->num_long_term_sps)
      poc_lsb = sps->lt_ref_pic_poc_lsb[slice_header->lt_idx_sps[i]];
    else
      poc_lsb = slice_header->poc_lsb_lt[i];
    poc = poc_lsb;

    if (slice_header->delta_poc_msb_present_flag[i]) {
      poc += pic_order_cnt - (i32)slice_header->delta_poc_msb_cycle_lt[i] *
             (i32)sps->max_pic_order_cnt_lsb -
             (i32)slice_header->pic_order_cnt_lsb;
    }

    if (slice_header->used_by_curr_pic_lt[i])
      dpb->poc_lt_curr[j++] = poc;
    else
      dpb->poc_lt_foll[k++] = poc;
  }
  dpb->num_poc_lt_curr = j;
  dpb->num_poc_lt_foll = k;

  /* For some streams the DPB size in VPS/SPS just indicate reference frame number,
        not follow spec to mean all decoding frame buffer number.
        And some error streams will get bigger reference frame number than all allocated frames buffer,
        in this case the refenrece frame number should be limited with orginal DPB size+1. */
  tot_ref_num = dpb->num_poc_st_curr + dpb->num_poc_lt_curr;
  if (tot_ref_num > dpb->real_size) {
    if (tot_ref_num > dpb->dpb_size + 1) {
      tot_ref_num = dpb->dpb_size;
      dpb->num_poc_st_curr = tot_ref_num;
      dpb->num_poc_lt_curr = 0;
    }
    dpb->real_size = MIN(MIN(tot_ref_num, dpb->tot_buffers - 2), MAX_DPB_SIZE-1);
    old_dpb_size = dpb->dpb_size;
    dpb->dpb_size = dpb->real_size + 1;

    for (i = old_dpb_size + 1; i < dpb->dpb_size + 1; i++) {
      /* Find a unused buffer j. */
      u32 j, id;
      for (j = 0; j < MAX_PIC_BUFFERS; j++) {
        u32 found = 0;
        for (u32 k = 0; k < i; k++) {
          if (dpb->pic_buffers[j].bus_address == dpb->buffer[k].data->bus_address) {
            found = 1;
            break;
          }
        }
        if (!found)
          break;
      }
      ASSERT(j < MAX_PIC_BUFFERS);
      dpb->buffer[i].data = dpb->pic_buffers + j;
      id = GetIdByData(dpb->fb_list, (void *)dpb->buffer[i].data);
      MarkIdAllocated(dpb->fb_list, id);
      dpb->buffer[i].mem_idx = id;
      dpb->pic_buff_id[j] = id;
    }

  }
}

void HevcDpbMarkOlderUnused(struct DpbStorage *dpb, i32 pic_order_cnt, u32 hrd_present) {
  u32 i;
  for (i = 0; i < MAX_DPB_SIZE; i++) {

    if (dpb->buffer[i].is_tsa_ref ||
        (/*IS_REFERENCE(dpb->buffer[i]) &&*/
         GET_POC(dpb->buffer[i]) <= pic_order_cnt)) {
      HevcUnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
      if (dpb->buffer[i].to_be_displayed && dpb->buffer[i].pic_output_flag) {
        dpb->num_out_pics_buffered--;
        dpb->buffer[i].to_be_displayed = 0;
        if(!IS_REFERENCE(dpb->buffer[i]) && dpb->fullness > 0)
          dpb->fullness--;
        /* For raster/dscale buffer, return to input buffer queue. */
        if (dpb->storage->pp_enabled) {
          InputQueueReturnBuffer(dpb->storage->pp_buffer_queue,
              DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].pp_data)));
          HevcReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
        }
        if (dpb->buffer[i].sei_param)
          dpb->buffer[i].sei_param->sei_status = SEI_UNUSED;
      }
      if (hrd_present) {
        RemoveTempOutputId(dpb->fb_list, dpb->buffer[i].mem_idx);
      }

      if (IS_REFERENCE(dpb->buffer[i]))
        DpbBufFree(dpb, i);
      SET_STATUS(dpb->buffer[i], UNUSED);
    }
  }
  /* output all pictures */
  while (OutputPicture(dpb) == HANTRO_OK)
    ;
}

/* Determines reference pictures for current and subsequent pictures. */
u32 HevcSetRefPics(struct DpbStorage *dpb, struct SliceHeader *slice_header,
                   i32 pic_order_cnt, struct SeqParamSet *sps, u32 is_idr,
                   u32 is_cra, u32 hrd_present, const void *dec_inst) {

  u32 i;
  i32 idx = 0;
  u32 st_count[MAX_DPB_SIZE + 1] = {0};
  u32 lt_count[MAX_DPB_SIZE + 1] = {0};
  u32 ret = DEC_OK;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;

  dpb->storage->ref_num_curr_pic = 0;

  /* TODO: skip for IDR/BLA */
  if (is_idr) {
    (void)HevcDpbMarkAllUnused(dpb);

    /* if no_output_of_prior_pics_flag was set -> the pictures preceding the
     * IDR picture shall not be output -> set output buffer empty */
    if (slice_header->no_output_of_prior_pics_flag) {
      RemoveTempOutputAll(dpb->fb_list, dpb);
      dpb->num_out = 0;
      dpb->out_index_w = dpb->out_index_r = 0;
    }

    (void)DWLmemset(dpb->poc_lt_curr, 0, sizeof(dpb->poc_lt_curr));
    (void)DWLmemset(dpb->poc_lt_foll, 0, sizeof(dpb->poc_lt_foll));
    (void)DWLmemset(dpb->poc_st_curr, 0, sizeof(dpb->poc_st_curr));
    (void)DWLmemset(dpb->poc_st_foll, 0, sizeof(dpb->poc_st_foll));
    (void)DWLmemset(dpb->ref_pic_set_lt, 0, sizeof(dpb->ref_pic_set_lt));
    (void)DWLmemset(dpb->ref_pic_set_st, 0, sizeof(dpb->ref_pic_set_st));
    dpb->num_poc_lt_curr = 0;
    dpb->num_poc_st_curr = 0;
    return ret;
  } else if (is_cra) {
    (void)HevcDpbMarkOlderUnused(dpb, pic_order_cnt, hrd_present);
    return ret;
  }

  HevcSetRefPicPocList(dpb, slice_header, pic_order_cnt, sps);
  if(IS_RAP_NAL_UNIT(dpb->storage->prev_nal_unit)) {
    dpb->num_poc_lt_curr = 0;
    dpb->num_poc_st_curr = 0;
  }

  dpb->storage->ref_num_curr_pic = dpb->num_poc_lt_curr + dpb->num_poc_st_curr;
  if (dpb->storage->ref_num_curr_pic && dpb->storage->skip_non_intra)
    return DEC_PARAM_ERROR;

  if(!IS_I_SLICE(slice_header->slice_type) && dpb->storage->ref_num_curr_pic == 0)
    return DEC_PARAM_ERROR;

  /* TODO: delta poc msb present */
  for (i = 0; i < dpb->num_poc_lt_curr; i++) {
    /* TODO: is it possible to have both long and short term with same
     * poc (at least lsb)? If not, should remove the flag from FindDpbPic */
    idx = FindDpbRefPic(dpb, dpb->poc_lt_curr[i], 1);
    if (idx < 0) idx = FindDpbRefPic(dpb, dpb->poc_lt_curr[i], 0);
    if (idx < 0) idx = FindDpbPic(dpb, dpb->poc_lt_curr[i]);
    if (idx < 0) idx = FindArbitaryRefPic(dpb);
    if (idx < 0) return DEC_PARAM_ERROR;
    dpb->ref_pic_set_lt[i] = idx;
    if (idx >= 0) lt_count[idx]++;
  }
  for (i = 0; i < dpb->num_poc_lt_foll; i++) {
    idx = FindDpbRefPic(dpb, dpb->poc_lt_foll[i], 1);
    if (idx < 0) idx = FindDpbRefPic(dpb, dpb->poc_lt_foll[i], 0);
    if (idx < 0) idx = FindDpbPic(dpb, dpb->poc_lt_foll[i]);
    //if (idx < 0) idx = FindArbitaryRefPic(dpb);
    if (idx >= 0) lt_count[idx]++;
  }

#if 0
  /* both before and after */
  for (i = 0; i < dpb->num_poc_st_curr; i++) {
    idx = FindDpbRefPic(dpb, dpb->poc_st_curr[i], 0);
    if (idx < 0) idx = FindDpbPic(dpb, dpb->poc_st_curr[i]);
    if (idx < 0) {
      ret= DEC_PARAM_ERROR;
    }
    dpb->ref_pic_set_st[i] = idx;
    if (idx >= 0) st_count[idx]++;
  }
#else
  for (i = 0; i < dpb->num_poc_st_curr_before; i++) {
    idx = FindDpbRefPic(dpb, dpb->poc_st_curr[i], 0);
    if (idx < 0) idx = FindDpbPic(dpb, dpb->poc_st_curr[i]);
    if (idx < 0) idx = FindArbitaryRefPic(dpb);
    if (idx < 0) {
#ifdef SUPPORT_GDR
      if (dpb->storage->is_gdr_frame) {
        /* first GDR frame need reference. */
        idx = 0;
        dpb->buffer[idx].dmv_data = &dpb->dmv_buffers[0];
        /* make sure the reference of first GDR frame has been decoded. */
        {
          char *sync_base =
            (char *) (dpb->buffer[idx].dmv_data->virtual_address) - 32;
          u32 sync_size = 32; /* 32 bytes for each field */
          (void) DWLmemset(sync_base, 0xFF, sync_size);
        }
      } else
#endif
      {
        if (i > 0)
          idx = dpb->ref_pic_set_st[0];
        else
          return DEC_PARAM_ERROR;
        if (idx < 0) return DEC_PARAM_ERROR;
      }
    }
    dpb->ref_pic_set_st[i] = idx;
    if (idx >= 0) st_count[idx]++;
  }
  for( ; i < dpb->num_poc_st_curr; i++) {
    idx = FindDpbRefPic(dpb, dpb->poc_st_curr[i], 0);
    if (idx < 0) idx = FindDpbPic(dpb, dpb->poc_st_curr[i]);
    if (idx < 0) idx = FindArbitaryRefPic(dpb);
    if (idx < 0) {
      if(i < dpb->num_poc_st_curr_before + slice_header->num_ref_idx_l1_active)
        return DEC_PARAM_ERROR;
      else {
        /* For risk that idx = -1 => dpb->ref_pic_set_st[i] = -1, which is
           32 in 5-bit unsigned register and result in DPB error in erroneous
           streams. */
        if (i > 0)
          idx = dpb->ref_pic_set_st[0];
        else
          return DEC_PARAM_ERROR;
        if (idx < 0) return DEC_PARAM_ERROR;
      }
    }
    dpb->ref_pic_set_st[i] = idx;
    if (idx >= 0) st_count[idx]++;
  }
#endif
  for (i = 0; i < dpb->num_poc_st_foll; i++) {
    idx = FindDpbRefPic(dpb, dpb->poc_st_foll[i], 0);
    if (idx >= 0) st_count[idx]++;
  }

  /* mark pics in dpb */
  for (i = 0; i <= dpb->dpb_size; i++) {
    if (st_count[i]) {
      SET_STATUS(dpb->buffer[i], SHORT_TERM);
      HevcBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
    }
    else if (lt_count[i]) {
      SET_STATUS(dpb->buffer[i], LONG_TERM);
      HevcBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
    }
    /* picture marked as not used */
    else if (IS_REFERENCE(dpb->buffer[i])) {
      SET_STATUS(dpb->buffer[i], UNUSED);
      HevcUnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
      DpbBufFree(dpb, i);
    }
  }

  /* if last element (index dpb_size) is used as reference -> swap with an
   * unused element earlier in the list (probably not necessary if dpb_size
   * less than 16, but done anyway) */
  idx = MAX_DPB_SIZE + 1;
  if (IS_REFERENCE(dpb->buffer[dpb->dpb_size])) {
    for (i = 0; i < dpb->dpb_size; i++) {
      if (!IS_REFERENCE(dpb->buffer[i])) {
        idx = i;
        break;
      }
    }
    /* should not swap element when dpb size specified by user and all dpb are used
     * as ref, because swap ref dpb will cause ref pic confusion and we will add new
     * dpb buffer at this time.*/
    if ((dec_cont->use_ext_dpb_size && idx < dpb->dpb_size) ||
        !dec_cont->use_ext_dpb_size) {
      ASSERT(idx < dpb->dpb_size);
      {
        struct DpbPicture tmp_pic = dpb->buffer[i];

        if (idx < 0)
          return DEC_PARAM_ERROR;
        dpb->buffer[idx] = dpb->buffer[dpb->dpb_size];
        dpb->buffer[dpb->dpb_size] = tmp_pic;
      }
      /* check ref pic lists */
      for (i = 0; i < dpb->num_poc_lt_curr; i++) {
        if (dpb->ref_pic_set_lt[i] == dpb->dpb_size) dpb->ref_pic_set_lt[i] = idx;
      }
      for (i = 0; i < dpb->num_poc_st_curr; i++) {
        if (dpb->ref_pic_set_st[i] == dpb->dpb_size) dpb->ref_pic_set_st[i] = idx;
      }
    }
  }

  if(IS_RAP_NAL_UNIT(dpb->storage->prev_nal_unit))
    ret = DEC_OK;
  return ret;
}


/* Find an arbitary reference picture from the buffer. */
static i32 FindArbitaryRefPic(struct DpbStorage *dpb) {

  u32 i = 0;

  while (i <= dpb->dpb_size) {
    if (IS_REFERENCE(dpb->buffer[i]) &&
        !dpb->buffer[i].dec_out_dis) {
      return i;
    }
    i++;
  }

  return (-1);
}


/* Find a picture from the buffer. The picture to be found is
 * identified by poc */
static i32 FindDpbPic(struct DpbStorage *dpb, i32 poc) {

  u32 i = 0;

  while (i <= dpb->dpb_size) {
    if ((dpb->buffer[i].pic_order_cnt == poc ||
         dpb->buffer[i].pic_order_cnt_lsb == poc) &&
        IS_REFERENCE(dpb->buffer[i]) &&
        !dpb->buffer[i].dec_out_dis) {
      return i;
    }
    i++;
  }

  return (-1);
}

/* Find a reference picture from the buffer. The picture to be found is
 * identified by poc and long_term flag. */
static i32 FindDpbRefPic(struct DpbStorage *dpb, i32 poc, u32 long_term) {

  u32 i = 0;

  while (i <= dpb->dpb_size) {
    if (dpb->buffer[i].pic_order_cnt == poc ||
        (long_term && dpb->buffer[i].pic_order_cnt_lsb == poc)) {
      if ((!long_term ? IS_SHORT_TERM(dpb->buffer[i]) : IS_LONG_TERM(dpb->buffer[i])) &&
           !dpb->buffer[i].dec_out_dis)
        return i;
    }
    i++;
  }

  return (-1);
}

/* Finds picture with smallest picture order count. This will be the next
 * picture in display order. */
struct DpbPicture *FindSmallestPicOrderCnt(struct DpbStorage *dpb) {

  u32 i;
  i32 pic_order_cnt;
  struct DpbPicture *tmp;

  ASSERT(dpb);

  pic_order_cnt = 0x7FFFFFFF;
  tmp = NULL;

  for (i = 0; i <= dpb->dpb_size; i++) {
    /* TODO: currently only outputting frames, asssumes that fields of a
     * frame are output consecutively */
    if (dpb->buffer[i].to_be_displayed &&
        GET_POC(dpb->buffer[i]) < pic_order_cnt) {
      tmp = dpb->buffer + i;
      pic_order_cnt = GET_POC(dpb->buffer[i]);
    }
  }

  return (tmp);
}

/* Function to put next display order picture into the output buffer. */
u32 OutputPicture(struct DpbStorage *dpb) {

  struct DpbPicture *tmp;
  struct DpbOutPicture *dpb_out;
  struct Storage *storage = dpb->storage;

  ASSERT(dpb);

  if (dpb->no_reordering) return (HANTRO_NOK);

  tmp = FindSmallestPicOrderCnt(dpb);

  /* no pictures to be displayed */
  if (tmp == NULL) return (HANTRO_NOK);

  /* if output buffer full -> ignore oldest */
  if (dpb->num_out == dpb->dpb_size + 1) {
    // TODO(atna) figure out how to safely handle output overflow

    /* it seems that output overflow can occur with corrupted streams
     * and display smoothing mode
     */

    ClearOutput(dpb->fb_list, dpb->out_buf[dpb->out_index_r].mem_idx);

    dpb->out_index_r++;
    if (dpb->out_index_r == MAX_DPB_SIZE + 1) dpb->out_index_r = 0;
    dpb->num_out--;
  }
  /* remove it from DPB */
  tmp->to_be_displayed = HANTRO_FALSE;
  if (tmp->pic_output_flag)
    dpb->num_out_pics_buffered--;
  if (!IS_REFERENCE(*tmp)) {
    if (dpb->fullness > 0)
      dpb->fullness--;
  }

  /* pic_output_flag comes from slice header, if 0, no nouput */
  if (tmp->pic_output_flag == 0) {
    if (storage->pp_enabled) {
      InputQueueReturnBuffer(storage->pp_buffer_queue,
        DWL_GET_DEVMEM_ADDR(*(tmp->pp_data)));
      HevcReturnDMVBuffer(dpb, tmp->dmv_data->bus_address);
    }
    if (tmp->sei_param)
      tmp->sei_param->sei_status = SEI_UNUSED;
    return (HANTRO_OK);
  }

  /* updated output list */
  dpb_out = &dpb->out_buf[dpb->out_index_w]; /* next output */
  dpb_out->data = tmp->data;
  dpb_out->pp_data = tmp->pp_data;
  dpb_out->dmv_data = tmp->dmv_data;
  dpb_out->is_idr = tmp->is_idr;
  dpb_out->pic_code_type = tmp->pic_code_type;
  dpb_out->is_tsa_ref = tmp->is_tsa_ref;
  dpb_out->pic_id = tmp->pic_id;
  dpb_out->poc = tmp->pic_order_cnt;
  dpb_out->sei_param = tmp->sei_param;
  dpb_out->num_tile_columns = tmp->num_tile_columns;
  dpb_out->num_tile_rows = tmp->num_tile_rows;
  dpb_out->error_ratio = tmp->error_ratio;
  dpb_out->error_info = tmp->error_info;
  dpb_out->mem_idx = tmp->mem_idx;
  dpb_out->tiled_mode = tmp->tiled_mode;
  dpb_out->cycles_per_mb = tmp->cycles_per_mb;

#ifdef FPGA_PERF_AND_BW
  dpb_out->bitrate_4k60fps = tmp->bitrate_4k60fps;
  dpb_out->bwrd_in_fs = tmp->bwrd_in_fs;
  dpb_out->bwwr_in_fs = tmp->bwwr_in_fs;
#endif
  dpb_out->pic_width = dpb->pic_width;
  dpb_out->pic_height = dpb->pic_height;
  dpb_out->crop_params = dpb->crop_params;
  dpb_out->bit_depth_luma = dpb->bit_depth_luma;
  dpb_out->bit_depth_chroma = dpb->bit_depth_chroma;
  dpb_out->mono_chrome = dpb->mono_chrome;
  dpb_out->chroma_format_idc = dpb->chroma_format_idc;
  dpb_out->pic_output_flag = tmp->pic_output_flag;
  dpb_out->is_gdr_frame = tmp->is_gdr_frame;

  dpb->num_out++;
  dpb->out_index_w++;
  if (dpb->out_index_w == MAX_DPB_SIZE + 1) dpb->out_index_w = 0;

  MarkTempOutput(dpb->fb_list, tmp->mem_idx);

  return (HANTRO_OK);
}

/* Get next display order picture from the output buffer. */
struct DpbOutPicture *HevcDpbOutputPicture(struct DpbStorage *dpb) {

  u32 tmp_idx;
  APITRACEDEBUG("%s %d %s %d\n","HevcDpbOutputPicture: index",(dpb->num_out -
                ((dpb->out_index_w - dpb->out_index_r + MAX_DPB_SIZE + 1) %
                 (MAX_DPB_SIZE + 1))),"outnum",dpb->num_out);
  if (dpb->num_out) {
    tmp_idx = dpb->out_index_r++;
    if (dpb->out_index_r == MAX_DPB_SIZE + 1) dpb->out_index_r = 0;
    dpb->num_out--;
    dpb->prev_out_idx = dpb->out_buf[tmp_idx].mem_idx;

    return (dpb->out_buf + tmp_idx);
  } else
    return (NULL);
}

/* Flush the DPB. Function puts all pictures needed for display into the
 * output buffer. This function shall be called in the end of the stream to
 * obtain pictures buffered for display re-ordering purposes. */
void HevcFlushDpb(struct DpbStorage *dpb) {

  dpb->flushed = 1;
  /* output all pictures */
  while (OutputPicture(dpb) == HANTRO_OK)
    ;
}

/* Frees the memories reserved for the DPB. */
i32 HevcFreeDpbExt(const void *dec_inst, struct DpbStorage *dpb) {

  u32 i;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;

  ASSERT(dpb);

  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    /* Client will make sure external memory to be freed.*/
    for (i = 0; i < dpb->tot_buffers; i++) {
      if (DWL_DEVMEM_VAILD(dpb->pic_buffers[i])) {
        if (dpb->pic_buff_id[i] != FB_NOT_VALID_ID)
          ReleaseId(dpb->fb_list, dpb->pic_buff_id[i]);
        /*
                dec_cont->buf_to_free = dpb->pic_buffers + i;
                dec_cont->next_buf_size = 0;
                return DEC_WAITING_FOR_BUFFER;
        */
      }
    }
  } else {
    for (i = 0; i < dpb->tot_buffers; i++) {
      if (DWL_DEVMEM_VAILD(dpb->pic_buffers[i])) {
        if (dpb->storage->realloc_int_buf)
          DWLFreeRefFrm(dec_cont->dwl, dpb->pic_buffers + i);
        if (dpb->pic_buff_id[i] != FB_NOT_VALID_ID)
          ReleaseId(dpb->fb_list, dpb->pic_buff_id[i]);
      }
    }
  }

  return 0;
}

i32 HevcFreeDpb(const void *dec_inst, struct DpbStorage *dpb) {

  u32 i;
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;

  ASSERT(dpb);

  for (i = 0; i < dpb->tot_buffers; i++) {
    if DWL_DEVMEM_VAILD((dpb->pic_buffers[i])) {
      if (!IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER))
        DWLFreeRefFrm(dec_cont->dwl, dpb->pic_buffers + i);
      if (dpb->pic_buff_id[i] != FB_NOT_VALID_ID)
        ReleaseId(dpb->fb_list, dpb->pic_buff_id[i]);
    }
  }

  if (dpb->out_buf != NULL) {
    DWLfree(dpb->out_buf);
    dpb->out_buf = NULL;
  }

  return 0;
}

/* Updates DPB ref frame count (and fullness) after marking a ref pic as
 * unused */
void DpbBufFree(struct DpbStorage *dpb, u32 i) {

  dpb->num_ref_frames--;

  if (!dpb->buffer[i].to_be_displayed) {
    if(dpb->fullness > 0)
      dpb->fullness--;
  }
}

/* Marks all reference pictures as unused and outputs all the pictures. */
u32 HevcDpbMarkAllUnused(struct DpbStorage *dpb) {

  u32 i;

  for (i = 0; i < MAX_DPB_SIZE; i++) {
    if (IS_REFERENCE(dpb->buffer[i])) {
      SET_STATUS(dpb->buffer[i], UNUSED);
      HevcUnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
      DpbBufFree(dpb, i);
    }
  }

  /* output all pictures */
  while (OutputPicture(dpb) == HANTRO_OK)
    ;
  dpb->num_ref_frames = 0;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
  dpb->prev_ref_frame_num = 0;

  return (HANTRO_OK);
}

struct DpbPicture *FindSmallestDpbOutputTime(struct DpbStorage *dpb) {

  u32 i;
  u32 dpb_time, cpb_time;
  //i32 pic_order_cnt = 0x7FFFFFFF;
  struct DpbPicture *tmp;
  struct DpbPicture *tmppoc;

  ASSERT(dpb);

  tmp = NULL;
  tmppoc = NULL;

  cpb_time = (u32) (dpb->cpb_removal_time * 1000);

  for (i = 0; i <= dpb->dpb_size; i++) {
    /* TODO: currently only outputting frames, asssumes that fields of a
     * frame are output consecutively */
    dpb_time = (u32) (dpb->buffer[i].dpb_output_time * 1000);
    if (dpb->buffer[i].to_be_displayed && dpb_time <= cpb_time && !IS_REFERENCE(dpb->buffer[i])) {
      tmp = dpb->buffer + i;
      cpb_time = dpb_time;
    }
  }

#if 0
  if (tmp != NULL) {
    for (i = 0; i <= dpb->dpb_size; i++) {
      /* TODO: currently only outputting frames, asssumes that fields of a
       * frame are output consecutively */
      if (dpb->buffer[i].to_be_displayed &&
          GET_POC(dpb->buffer[i]) < pic_order_cnt) {
        tmppoc = dpb->buffer + i;
        pic_order_cnt = GET_POC(dpb->buffer[i]);
      }
    }
  }
#endif
  return (tmp);
  if (tmp == tmppoc)
    return (tmp);
  else
    return (tmppoc);
}

u32 HevcDpbHrdBumping(struct DpbStorage *dpb) {
  struct DpbPicture *tmp;
  struct DpbOutPicture *dpb_out;
  ASSERT(dpb);

  if (dpb->no_reordering) return (HANTRO_NOK);

  tmp = FindSmallestDpbOutputTime(dpb);

  /* no pictures to be displayed */
  if (tmp == NULL) return (HANTRO_NOK);

  /* if output buffer full -> ignore oldest */
  if (dpb->num_out == dpb->dpb_size + 1) {
    // TODO(atna) figure out how to safely handle output overflow
    /* it seems that output overflow can occur with corrupted streams
    * and display smoothing mode
    */

    ClearOutput(dpb->fb_list, dpb->out_buf[dpb->out_index_r].mem_idx);

    dpb->out_index_r++;
    if (dpb->out_index_r == MAX_DPB_SIZE + 1) dpb->out_index_r = 0;
    dpb->num_out--;
  }
  /* remove it from DPB */
  tmp->to_be_displayed = HANTRO_FALSE;
  dpb->num_out_pics_buffered--;
  /* updated output list */
  dpb_out = &dpb->out_buf[dpb->out_index_w]; /* next output */
  dpb_out->data = tmp->data;
  dpb_out->pp_data = tmp->pp_data;
  dpb_out->dmv_data = tmp->dmv_data;
  dpb_out->is_idr = tmp->is_idr;
  dpb_out->pic_code_type = tmp->pic_code_type;
  dpb_out->is_tsa_ref = tmp->is_tsa_ref;
  dpb_out->pic_id = tmp->pic_id;
  dpb_out->poc = tmp->pic_order_cnt;
  dpb_out->sei_param = tmp->sei_param;
  dpb_out->num_tile_columns = tmp->num_tile_columns;
  dpb_out->num_tile_rows = tmp->num_tile_rows;
  dpb_out->error_ratio = tmp->error_ratio;
  dpb_out->error_info = tmp->error_info;
  dpb_out->mem_idx = tmp->mem_idx;
  dpb_out->tiled_mode = tmp->tiled_mode;
  dpb_out->cycles_per_mb = tmp->cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
  dpb_out->bitrate_4k60fps = tmp->bitrate_4k60fps;
  dpb_out->bwrd_in_fs = tmp->bwrd_in_fs;
  dpb_out->bwwr_in_fs = tmp->bwwr_in_fs;
#endif
  dpb_out->pic_struct = tmp->pic_struct;
  dpb_out->pic_width = dpb->pic_width;
  dpb_out->pic_height = dpb->pic_height;
  dpb_out->crop_params = dpb->crop_params;
  dpb_out->bit_depth_luma = dpb->bit_depth_luma;
  dpb_out->bit_depth_chroma = dpb->bit_depth_chroma;
  dpb_out->mono_chrome = dpb->mono_chrome;
  dpb_out->chroma_format_idc = dpb->chroma_format_idc;
  dpb_out->pic_output_flag = tmp->pic_output_flag;
  dpb_out->is_gdr_frame = tmp->is_gdr_frame;

  dpb->num_out++;
  dpb->out_index_w++;
  if (dpb->out_index_w == MAX_DPB_SIZE + 1) dpb->out_index_w = 0;

  if (!IS_REFERENCE(*tmp)) {
    if(dpb->fullness > 0)
      dpb->fullness--;
  }

  MarkTempOutput(dpb->fb_list, tmp->mem_idx);

  return (HANTRO_OK);
}

void HevcEmptyDpb(const void *dec_inst, struct DpbStorage *dpb) {
  struct HevcDecContainer *dec_cont = (struct HevcDecContainer *)dec_inst;
  i32 i;

  for (i = 0; i < MAX_DPB_SIZE + 1; i++) {
    if (dpb->buffer[i].to_be_displayed == HANTRO_TRUE) {
      /* If the allocated buffer is still in DPB and not output to
       * dpb->out_buf by OutputPicture yet, return the coupled
       * raster/downscal buffer. */
      if (dpb->storage->pp_enabled) {
        InputQueueReturnBuffer(dpb->storage->pp_buffer_queue,
                          DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].pp_data)));
        HevcReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
      }
      if (dpb->buffer[i].sei_param)
        dpb->buffer[i].sei_param->sei_status = SEI_UNUSED;
    }
    SET_STATUS(dpb->buffer[i], UNUSED);
    HevcUnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
    dpb->buffer[i].to_be_displayed = 0;
    dpb->buffer[i].error_ratio = 0;
    dpb->buffer[i].error_info = DEC_NO_ERROR;
    dpb->buffer[i].pic_num = 0;
    dpb->buffer[i].pic_order_cnt = 0;
    dpb->buffer[i].pic_order_cnt_lsb = 0;
    dpb->buffer[i].is_idr = 0;
    dpb->buffer[i].pic_code_type = 0;
    dpb->buffer[i].is_tsa_ref = 0;
    dpb->buffer[i].cycles_per_mb = 0;
#ifdef FPGA_PERF_AND_BW
    dpb->buffer[i].bitrate_4k60fps = 0;
    dpb->buffer[i].bwrd_in_fs = 0;
    dpb->buffer[i].bwwr_in_fs = 0;
#endif
    dpb->buffer[i].pic_struct = 0;
    dpb->buffer[i].dpb_output_time = 0;
    dpb->buffer[i].dec_out_dis = 0;

#ifdef USE_OMXIL_BUFFER
    dpb->buffer[i].pp_data = NULL;
    if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
      dpb->buffer[i].mem_idx = INVALID_MEM_IDX;
      dpb->buffer[i].data = NULL;
    }
#endif
  }

  RemoveTempOutputAll(dpb->fb_list, dpb);
  RemoveOutputAll(dpb->fb_list, dpb);

#ifdef USE_OMXIL_BUFFER
  if (dpb->storage && dpb->storage->pp_enabled)
    InputQueueReturnAllBuffer(dpb->storage->pp_buffer_queue);

  if (IS_EXTERNAL_BUFFER(dec_cont->ext_buffer_config, REFERENCE_BUFFER)) {
    for (i = 0; i < dpb->tot_buffers; i++) {
      if (DWL_DEVMEM_VAILD(dpb->pic_buffers[i])) {
        if (dpb->pic_buff_id[i] != FB_NOT_VALID_ID) {
          ReleaseId(dpb->fb_list, dpb->pic_buff_id[i]);
        }
      }
    }
    dpb->fb_list->free_buffers = 0;
  }
#endif

  ResetOutFifoInList(dpb->fb_list);

  dpb->current_out = NULL;
  dpb->current_out_pos = 0;
  dpb->cpb_removal_time = 0;
  dpb->bumping_flag = 0;
  dpb->num_out = 0;
  dpb->out_index_w = 0;
  dpb->out_index_r = 0;
  dpb->dpb_reset = 0;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
  dpb->num_ref_frames = 0;
  dpb->fullness = 0;
  dpb->num_out_pics_buffered = 0;
  dpb->prev_ref_frame_num = 0;
  dpb->flushed = 0;
  dpb->prev_out_idx = INVALID_MEM_IDX;
#ifdef USE_OMXIL_BUFFER
  dpb->tot_buffers = dpb->dpb_size + 2 + dec_cont->storage.n_extra_frm_buffers;
  /* figure out extra buffers for multicore */
  if (dec_cont->n_cores > 1) {
    /* one extra buffer for each core */
    /* do not allocate twice for multiview */
    dpb->tot_buffers += dec_cont->n_cores;
  }

  if (dpb->tot_buffers > MAX_PIC_BUFFERS)
    dpb->tot_buffers = MAX_PIC_BUFFERS;
#endif

  dpb->num_poc_st_curr = 0;
  dpb->num_poc_st_curr_before = 0;
  dpb->num_poc_st_foll = 0;
  dpb->num_poc_lt_curr = 0;
  dpb->num_poc_lt_foll = 0;

  (void)DWLmemset(dpb->poc_lt_curr, 0, sizeof(dpb->poc_lt_curr));
  (void)DWLmemset(dpb->poc_lt_foll, 0, sizeof(dpb->poc_lt_foll));
  (void)DWLmemset(dpb->poc_st_curr, 0, sizeof(dpb->poc_st_curr));
  (void)DWLmemset(dpb->poc_st_foll, 0, sizeof(dpb->poc_st_foll));
  (void)DWLmemset(dpb->ref_pic_set_lt, 0, sizeof(dpb->ref_pic_set_lt));
  (void)DWLmemset(dpb->ref_pic_set_st, 0, sizeof(dpb->ref_pic_set_st));

  if (dpb->storage && dpb->storage->pp_enabled)
    InputQueueReset(dpb->storage->pp_buffer_queue);
  (void)dec_cont;
}

void HevcBindDMVBuffer(struct DpbStorage *dpb, struct DWLLinearMem *dmv) {
  u32 i;

  if (dmv == NULL)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address == dmv->bus_address) {
      dpb->dmv_buf_status[i] |= BUF_BIND;
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void HevcUnBindDMVBuffer(struct DpbStorage *dpb, struct DWLLinearMem *dmv) {
  u32 i;

  if (dmv == NULL)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
    for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address ==dmv->bus_address) {
      dpb->dmv_buf_status[i] &= ~BUF_BIND;
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}

void HevcOutputDMVBuffer(struct DpbStorage *dpb, addr_t dmv_bus_address) {
  u32 i;

  if (!dmv_bus_address)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
    for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address ==dmv_bus_address) {
      dpb->dmv_buf_status[i] |= BUF_OUTPUT;
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void HevcReturnDMVBuffer(struct DpbStorage *dpb, addr_t dmv_bus_address) {
  u32 i;
  addr_t dpb_buf_addr;

  if (!dmv_bus_address)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    dpb_buf_addr = dpb->dmv_buffers[i].bus_address  - dpb->dir_mv_offset;
    if (dmv_bus_address > dpb_buf_addr && dmv_bus_address <= dpb_buf_addr + dpb->n_int_buf_size) {
      dpb->dmv_buf_status[i] &= ~BUF_OUTPUT;
      pthread_cond_signal(dpb->dmv_buffer_cv);
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}

void HevcEnableDMVBuffer(struct DpbStorage *dpb, u32 core_id) {
  u32 i;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buf_status[i] & BUF_BIND)
      dpb->dmv_buf_status[i] |= (1 << (BUF_USED + core_id));
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void HevcDisableDMVBuffer(struct DpbStorage *dpb, u32 core_id) {
  u32 i;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    //if (dpb->dmv_buf_status[i] & (1 << (BUF_USED + core_id)))
      dpb->dmv_buf_status[i] &= ~(1 << (BUF_USED + core_id));
  }
  pthread_cond_signal(dpb->dmv_buffer_cv);
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}
