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

#include "h264hwd_container.h"

#include "h264hwd_decoder.h"
#include "h264hwd_nal_unit.h"
#include "h264hwd_byte_stream.h"
#include "h264hwd_seq_param_set.h"
#include "h264hwd_pic_param_set.h"
#include "h264hwd_slice_header.h"
#include "h264hwd_slice_data.h"
#include "h264hwd_neighbour.h"
#include "h264hwd_util.h"
#include "h264hwd_dpb.h"
#include "h264hwd_vlc.h"

#include "h264hwd_conceal.h"
#include "errorhandling.h"
#include "dec_log.h"

/* parse NAL UNIT TYPE */
char *ParseH264NalunitType(u16 nal_type){
  switch(nal_type){
    case NAL_CODED_SLICE: return "NAL_CODED_SLICE\n"; break;
    case NAL_CODED_SLICE_DP_A: return "NAL_CODED_SLICE_DP_A\n"; break;
    case NAL_CODED_SLICE_DP_B: return "NAL_CODED_SLICE_DP_B\n"; break;
    case NAL_CODED_SLICE_DP_C: return "NAL_CODED_SLICE_DP_C\n"; break;
    case NAL_CODED_SLICE_IDR: return "NAL_CODED_SLICE_IDR\n"; break;
    case NAL_SEI: return "NAL_SEI\n"; break;
    case NAL_SEQ_PARAM_SET: return "NAL_SEQ_PARAM_SET\n"; break;
    case NAL_PIC_PARAM_SET: return "NAL_PIC_PARAM_SET\n"; break;
    case NAL_ACCESS_UNIT_DELIMITER: return "NAL_ACCESS_UNIT_DELIMITER\n"; break;
    case NAL_END_OF_SEQUENCE: return "NAL_END_OF_SEQUENCE\n"; break;
    case NAL_END_OF_STREAM: return "NAL_END_OF_STREAM\n"; break;
    case NAL_FILLER_DATA: return "NAL_FILLER_DATA\n"; break;
    case NAL_SPS_EXT: return "NAL_SPS_EXT\n"; break;
    case NAL_PREFIX: return "NAL_PREFIX\n"; break;
    case NAL_SUBSET_SEQ_PARAM_SET: return "NAL_SUBSET_SEQ_PARAM_SET\n"; break;
    case NAL_CODED_SLICE_AUX: return "NAL_CODED_SLICE_AUX\n"; break;
    case NAL_CODED_SLICE_EXT: return "NAL_CODED_SLICE_EXT\n"; break;
    case NAL_UNSPECIFIED: return "NAL_UNSPECIFIED\n"; break;
    default: return "NAL_UNSPECIFIED NAL UNIT TYPE\n";
  }
}


/*------------------------------------------------------------------------------
    2. External compiler flags
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
    3. Module defines
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    4. Local function prototypes
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------

    Function name: h264bsdInit

        Functional description:
            Initialize the decoder.

        Inputs:
            no_output_reordering  flag to indicate the decoder that it does not
                                have to perform reordering of display images.

        Outputs:
            storage            pointer to initialized storage structure

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdInit(storage_t * storage, u32 no_output_reordering,
                 u32 use_smoothing_buffer) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  h264bsdInitStorage(storage);

  storage->no_reordering = no_output_reordering;
  storage->use_smoothing = use_smoothing_buffer;
  storage->dpb = storage->dpbs[0];
  storage->slice_header = storage->slice_headers[0];

}

/*------------------------------------------------------------------------------

    Function: h264bsdDecodeVlc

        Functional description:
            Decode a NAL unit until a slice header. This function calls other modules to perform
            tasks like
                * extract and decode NAL unit from the byte stream
                * decode parameter sets
                * decode slice header and slice data
                * conceal errors in the picture
                * perform deblocking filtering

            This function contains top level control logic of the decoder.

        Inputs:
            storage        pointer to storage data structure
            byte_strm        pointer to stream buffer given by application
            len             length of the buffer in bytes
            pic_id           identifier for a picture, assigned by the
                            application

        Outputs:
            read_bytes       number of bytes read from the stream is stored
                            here

        Returns:
            H264BSD_RDY             decoding finished, nothing special
            H264BSD_PIC_RDY         decoding of a picture finished
            H264BSD_HDRS_RDY        param sets activated, information like
                                    picture dimensions etc can be read
            H264BSD_PARAM_SET_ERROR serious error in decoding, failed to
                                    activate param sets

------------------------------------------------------------------------------*/
u32 h264bsdDecode(struct H264DecContainer * dec_cont, const u8 * byte_strm, u32 len,
                  u32 pic_id, u32 * read_bytes) {

  /* Variables */

  u32 tmp, pps_id, sps_id, slice_type;
  u32 access_unit_boundary_flag = HANTRO_FALSE;
  u32 pic_ready = HANTRO_FALSE;
  storage_t *storage;
  nalUnit_t nal_unit;
  seqParamSet_t seq_param_set;
  picParamSet_t pic_param_set;
  strmData_t strm;
  u8 *strm_buf = dec_cont->hw_buffer;
  u32 buf_len = dec_cont->buff_length;
  enum H264Result ret = H264BSD_RDY;

  /* Code */
  ASSERT(dec_cont);
  ASSERT(byte_strm);
  ASSERT(strm_buf);
  ASSERT(len);
  ASSERT(buf_len);
  ASSERT(read_bytes);

  storage = &dec_cont->storage;
  ASSERT(storage);

  strm.is_rb = dec_cont->use_ringbuffer;

  STREAMTRACE_I("Valid slice in access unit %d\n",
               storage->valid_slice_in_access_unit);
  strm.emul_byte_count = 0;

  if(dec_cont->rlc_mode) {
    storage->strm[0].remove_emul3_byte = 1;
    strm.remove_emul3_byte = 1;
  } else {
    storage->strm[0].remove_emul3_byte = 0;
    strm.remove_emul3_byte = 0;
  }
  strm.stream_info = &dec_cont->stream_info;

  /* if previous buffer was not finished and same pointer given -> skip NAL
   * unit extraction */
  if(storage->prev_buf_not_finished && byte_strm == storage->prev_buf_pointer) {
    strm = storage->strm[0];
    *read_bytes = storage->prev_bytes_consumed;
    strm.stream_info = &dec_cont->stream_info;
  } else {
    tmp =
      h264bsdExtractNalUnit(byte_strm, len, strm_buf, buf_len, &strm, read_bytes,
                            dec_cont->rlc_mode, &dec_cont->start_code_detected);
    if(tmp != HANTRO_OK) {
      STREAMTRACE_E("%s","BYTE_STREAM\n");
      return H264BSD_NALUNIT_ERROR;
    }
    /* store stream */
    storage->strm[0] = strm;
    storage->prev_bytes_consumed = *read_bytes;
    storage->prev_buf_pointer = byte_strm;
  }

  storage->prev_buf_not_finished = HANTRO_FALSE;

  tmp = h264bsdDecodeNalUnit(&strm, &nal_unit);
  if(tmp != HANTRO_OK) {
    ret = H264BSD_NALUNIT_ERROR;
    goto NEXT_NAL;
  }
  if (storage->bumping_flag) {
    if (nal_unit.nal_unit_type != 12) {
      if(h264bsdStoreSEIInfoForCurrentPic(storage) == HANTRO_OK) {
        storage->compute_time_info.access_unit_size = 0;
        storage->bumping_flag = 0;
        storage->dpb->bumping_flag = 1;
      }
    }
  }
  /* Discard unspecified, reserved, SPS extension and auxiliary picture slices */
  if (nal_unit.nal_unit_type == 0 ||
      (nal_unit.nal_unit_type >= 13 &&
       (storage->mvc == 0 &&
        (nal_unit.nal_unit_type != 14 &&
         nal_unit.nal_unit_type != 15 &&
         nal_unit.nal_unit_type != 20)))) {
    STREAMTRACE_I("%s","DISCARDED NAL (UNSPECIFIED, REGISTERED, SPS ext or AUX slice)\n");
    ret = H264BSD_RDY;
    goto NEXT_NAL;
  }

  if (nal_unit.svc_extension_flag) {
    storage->dpb->svc_info.pic_id = pic_id;
    storage->dpb->svc_info.temporal_id = nal_unit.svc_ext.temporal_id;
    // printf("JZQ: pic_id = %d, temporal_id = %d\n", pic_id, nal_unit.svc_ext.temporal_id);
    /* Discard those NALUs whose temporal_id is greater than max_temporal_layer. */
    if (dec_cont->max_temporal_layer != -1 && nal_unit.svc_ext.temporal_id > dec_cont->max_temporal_layer) {
      STREAMTRACE_I("%s","DISCARDED NAL (temporal_id is greater than max_temporal_layer)\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    }
  } else {
    if (nal_unit.nal_unit_type == NAL_CODED_SLICE_EXT && storage->mvc == 0) {
      /* svc_extension_flag == 0 ? */
      STREAMTRACE_I("%s","DISCARDED NAL (temporal_id is greater than max_temporal_layer)\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    }
    /* Discard those NALUs whose temporal_id is greater than max_temporal_layer. */
    if (dec_cont->max_temporal_layer != -1 &&
        storage->dpb->svc_info.pic_id == pic_id &&
        storage->dpb->svc_info.temporal_id > dec_cont->max_temporal_layer) {
      STREAMTRACE_I("%s","DISCARDED NAL (temporal_id is greater than max_temporal_layer)\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    }
  }

  if(dec_cont->skip_frame == DEC_SKIP_NON_REF && nal_unit.nal_ref_idc == 0 ) {
    STREAMTRACE_I("%s","DISCARDED NAL (NON-REFERENCE PICTURE)\n");
    ret = H264BSD_NONREF_PIC_SKIPPED;
    goto NEXT_NAL;
  }

  if(!storage->checked_aub) {
    storage->aub->prev_mod_frame_num =
      storage->aub->prev_frame_num & ~dec_cont->frame_num_mask;
    tmp = h264bsdCheckAccessUnitBoundary(&strm,
                                         &nal_unit,
                                         storage, &access_unit_boundary_flag,
                                         0, dec_cont->rlc_mode);
    DWLmemcpy(storage->tmp_aub, storage->aub, sizeof(aubCheck_t));
    if(tmp != HANTRO_OK) {
      STREAMTRACE_E("%s","ACCESS UNIT BOUNDARY CHECK\n");
      if(tmp == PARAM_SET_ERROR)
        ret = (H264BSD_PARAM_SET_ERROR);
      else
        ret = (H264BSD_AU_BOUNDARY_ERROR);
      goto NEXT_NAL;
    }
  } else {
    storage->checked_aub = 0;
  }

  storage->last_nal_unit[0] = nal_unit;

  if (access_unit_boundary_flag) {
    STREAMTRACE_I("Access unit boundary, NAL TYPE %d\n",
                 nal_unit.nal_unit_type);

    /* conceal if picture started and param sets activated */
    if(storage->pic_started && storage->active_sps != NULL) {
      if(dec_cont->rlc_mode) { /* Error conceal in RLC mode */
        DecAsicBuffers_t *p_asic_buff = dec_cont->asic_buff;
        ASSERT(p_asic_buff);
        ASSERT(p_asic_buff->mb_ctrl.virtual_address);
        STREAMTRACE_I("%s","CONCEALING...\n");

        if(!storage->valid_slice_in_access_unit) {
          STREAMTRACE_I("%s","!valid_sliceunit\n");
          dec_cont->alloc_buffer = 1;
          h264bsdInitRefPicList(storage->dpb);
          h264bsdConceal(storage, p_asic_buff, P_SLICE);
        } else {
          STREAMTRACE_I("%s","valid_sliceunit\n");
          h264bsdConceal(storage, p_asic_buff,
                         storage->slice_header->slice_type);
        }

        /* RLC mode: get num_err_mbs before start HW */
        if (storage->num_err_mbs != 0) {
          dec_cont->error_info = DEC_FRAME_ERROR;
        }

        pic_ready = HANTRO_TRUE;

        /* current NAL unit should be decoded on next activation -> set
         * read_bytes to 0 */
        *read_bytes = 0;
        storage->prev_buf_not_finished = HANTRO_TRUE;
        STREAMTRACE_I("%s","...DONE\n");

      } else { /* VLC  mode */
        STREAMTRACE_I("%s","New access unit and previous not finished\n");
        STREAMTRACE_I("%s","PICTURE FREEZE CONCEAL...\n");

        if(!storage->valid_slice_in_access_unit) {
          STREAMTRACE_I("%s","!valid_sliceunit\n");
          if (!storage->view && !storage->second_field) {
            dec_cont->alloc_buffer = 1;
            storage->slice_header->field_pic_flag = 0;
          } else if (storage->view) {
            storage->valid_slice_in_access_unit = 1;
            if (!storage->base_opposite_field_pic) {
              dec_cont->alloc_buffer = 1;
            } else {
              storage->base_opposite_field_pic = 0;
              storage->curr_image->data =
                storage->dpb->current_out->data;
              storage->curr_image->pp_data =
                storage->dpb->current_out->ds_data;
              storage->curr_image->dmv_data =
                storage->dpb->current_out->dmv_data;
            }
            storage->slice_header = storage->slice_headers[0];
          }
          h264bsdInitRefPicList(storage->dpb);
        }

        storage->skip_redundant_slices = HANTRO_FALSE;

        /* current NAL unit should be decoded on next activation -> set
         * read_bytes to 0 */
        *read_bytes = 0;
        storage->prev_buf_not_finished = HANTRO_TRUE;
        STREAMTRACE_I("%s","...DONE\n");

        return (H264BSD_NEW_ACCESS_UNIT);
      }
    } else {
      STREAMTRACE_I("%s","valid slice false\n");
      storage->valid_slice_in_access_unit = HANTRO_FALSE;
    }

    storage->skip_redundant_slices = HANTRO_FALSE;
  }

  if(!pic_ready) {
    STREAMTRACE_I("nal unit type: %s", ParseH264NalunitType(nal_unit.nal_unit_type));

    switch (nal_unit.nal_unit_type) {
    case NAL_SEQ_PARAM_SET:
    case NAL_SUBSET_SEQ_PARAM_SET:
      STREAMTRACE_I("%s","SEQ PARAM SET\n");
      tmp = h264bsdDecodeSeqParamSet(&strm, &seq_param_set,
                                     nal_unit.nal_unit_type == NAL_SEQ_PARAM_SET ? 0 : 1);
      if(tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","SEQ_PARAM_SET decoding\n");
        FREE(seq_param_set.offset_for_ref_frame);
        FREE(seq_param_set.vui_parameters);
        ret = H264BSD_PARAM_SET_ERROR;
        goto NEXT_NAL;
      } else {
        tmp = h264bsdStoreSeqParamSet(storage, &seq_param_set);
        if(tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","SEQ_PARAM_SET allocation\n");
          ret = H264BSD_MEMFAIL;
          goto NEXT_NAL;
        }
        dec_cont->b_mvc = 0;
        if (nal_unit.nal_unit_type == NAL_SUBSET_SEQ_PARAM_SET) {
          storage->view_id[0] = seq_param_set.mvc.view_id[0];
          storage->view_id[1] = seq_param_set.mvc.view_id[1];
          dec_cont->b_mvc = 1;
        }
      }
      UNUSED(ret);
      ret = H264BSD_PARAM_SET_PARSED;
      goto NEXT_NAL;

    case NAL_PIC_PARAM_SET:
      STREAMTRACE_I("%s","PIC PARAM SET\n");
      tmp = h264bsdDecodePicParamSet(&strm, &pic_param_set,storage->sps);
      if(tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","PIC_PARAM_SET decoding\n");
        FREE(pic_param_set.run_length);
        FREE(pic_param_set.top_left);
        FREE(pic_param_set.bottom_right);
        FREE(pic_param_set.slice_group_id);
        ret = H264BSD_PARAM_SET_ERROR;
        goto NEXT_NAL;
        UNUSED(ret);
      } else {
        tmp = h264bsdStorePicParamSet(storage, &pic_param_set);
        /* allocated new memory inside h264bsdStorePicParamSet */
        FREE(pic_param_set.run_length);
        FREE(pic_param_set.top_left);
        FREE(pic_param_set.bottom_right);
        FREE(pic_param_set.slice_group_id);
        if(tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","PIC_PARAM_SET allocation\n");
          ret = H264BSD_MEMFAIL;
          goto NEXT_NAL;
          UNUSED(ret);
        }
      }
      ret = H264BSD_PARAM_SET_PARSED;
      goto NEXT_NAL;

    case NAL_CODED_SLICE_IDR:
      STREAMTRACE_I("%s","IDR\n");
    /* fall through */
    case NAL_CODED_SLICE:
    case NAL_CODED_SLICE_EXT:
      STREAMTRACE_I("%s","decode slice header\n");

      if (nal_unit.nal_unit_type == NAL_CODED_SLICE_EXT) {
        /* base not yet initialized -> skip */
        if (storage->active_view_sps[0] == NULL)
          goto NEXT_NAL;

        storage->view = 1;
        /* view_id not equal to view_id of the 1. non-base view or
         * base view picture missing -> skip */
        if (nal_unit.mvc_ext.view_id != storage->view_id[storage->view] ||
            (storage->num_views && storage->next_view == 0) ||
            nal_unit.mvc_ext.view_id == storage->view_id[0]) {
          goto NEXT_NAL;
        }
      } else
        storage->view = 0;

      /* base view detected, but stereo expected -> go back and freeze
       * previous stereo view picture */
      if (storage->view == 0 && storage->num_views &&
          storage->next_view != 0 && storage->active_view_sps[0]) {
        *read_bytes = 0;
        storage->prev_buf_not_finished = HANTRO_TRUE;
        storage->view = 1;
        storage->dpb = storage->dpbs[storage->view];

        storage->valid_slice_in_access_unit = 1;

        if (!storage->base_opposite_field_pic) {
          dec_cont->alloc_buffer = 1;
        } else {
          storage->base_opposite_field_pic = 0;
          storage->curr_image->data =
            storage->dpb->current_out->data;
          storage->curr_image->pp_data =
            storage->dpb->current_out->ds_data;
          storage->curr_image->dmv_data =
            storage->dpb->current_out->dmv_data;
        }
        h264bsdInitRefPicList(storage->dpb);

        return (H264BSD_NEW_ACCESS_UNIT);
      }

      /* picture successfully finished and still decoding same old
       * access unit -> no need to decode redundant slices */
      if(storage->skip_redundant_slices) {
        STREAMTRACE_I("%s","skipping redundant slice\n");
        ret = H264BSD_RDY;
        goto NEXT_NAL;
      }

      storage->pic_started = HANTRO_TRUE;

      if(h264bsdIsStartOfPicture(storage)) {
        storage->num_err_mbs = 0;
        storage->current_pic_id = pic_id;

        tmp = h264bsdCheckPpsId(&strm, &pps_id, &slice_type);
        if(tmp != HANTRO_OK) {
          ret = H264BSD_PARAM_SET_ERROR;
          goto NEXT_NAL;
        }
        /* store old active_sps_id and return headers ready
         * indication if active_sps changes */
        sps_id = storage->active_view_sps_id[storage->view];

        tmp = h264bsdActivateParamSets(storage, pps_id, slice_type,
                                       IS_IDR_NAL_UNIT(&nal_unit) ?
                                       HANTRO_TRUE : HANTRO_FALSE);
        if(tmp != HANTRO_OK || storage->active_sps == NULL ||
            storage->active_pps == NULL) {
          STREAMTRACE_E("%s","Param set activation\n");
          ret = H264BSD_PARAM_SET_ERROR;
          if (storage->view &&
              storage->active_sps == NULL)
            storage->num_views = 0;
          goto NEXT_NAL;
        }

        if(sps_id != storage->active_sps_id) {
          seqParamSet_t *old_sps = NULL;
          seqParamSet_t *new_sps = storage->active_sps;
          u32 no_output_of_prior_pics_flag = 1;

          if(storage->old_sps_id < MAX_NUM_SEQ_PARAM_SETS) {
            old_sps = storage->sps[storage->old_sps_id];
          }

          *read_bytes = 0;
          storage->prev_buf_not_finished = HANTRO_TRUE;

          if(IS_IDR_NAL_UNIT(&nal_unit)) {
            tmp =
              h264bsdCheckPriorPicsFlag(&no_output_of_prior_pics_flag,
                                        &strm, new_sps,
                                        storage->active_pps);
          } else {
            tmp = HANTRO_NOK;
          }

          if((tmp != HANTRO_OK) ||
              (no_output_of_prior_pics_flag != 0) ||
              (storage->dpb->no_reordering) ||
              (old_sps == NULL) ||
              (old_sps->pic_width_in_mbs != new_sps->pic_width_in_mbs) ||
              (old_sps->pic_height_in_mbs != new_sps->pic_height_in_mbs) ||
              (old_sps->max_dpb_size != new_sps->max_dpb_size)) {
            storage->dpb->flushed = 0;
          } else {
            h264bsdFlushDpb(storage->dpb);
          }

          storage->old_sps_id = storage->active_sps_id;
          storage->pic_started = HANTRO_FALSE;
          storage->checked_aub = 1;
          return (H264BSD_HDRS_RDY);
        }

        if(storage->active_pps->num_slice_groups != 1 && !dec_cont->rlc_mode) {
          /* FMO is not supported in secure mode */
          if (dec_cont->secure_mode) {
            ret = H264BSD_RDY;
            goto NEXT_NAL;
          }

          dec_cont->reallocate = 1;
          dec_cont->try_vlc = 0;
          storage->pic_started = HANTRO_FALSE;
          *read_bytes = 0;
          return (H264BSD_FMO);
        }

        if(storage->active_pps->num_slice_groups == 1 &&
           dec_cont->rlc_mode &&
           storage->aso_detected == 0) {
          if(dec_cont->force_rlc_mode)
            dec_cont->try_vlc = 0;
          else {
            STREAMTRACE_I("%s","h264bsdDecode: no FMO/ASO detected, switch to VLC\n");
            dec_cont->try_vlc = 1;

            /* we have removed emulation prevention 3B from stream,
             * cannot go to VLC for this frame; but try the
             * next one */

            /* dec_cont->rlc_mode = 0; */
          }
        }
      }

      tmp = h264bsdDecodeSliceHeader(&strm, storage->slice_header + 1,
                                     storage->active_sps,
                                     storage->active_pps, &nal_unit);
      if(tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","SLICE_HEADER");
        ret = H264BSD_SLICE_HDR_ERROR;
        goto NEXT_NAL;
      }

      /*
       * 1. new I slice: maybe is I frame, the ERROR flag needs to be cleared.
       * 2. new GDR start frame: the ERROR flag needs to be cleared.
       */
      if (
          IS_I_SLICE(storage->slice_header[1].slice_type)
#ifdef SUPPORT_GDR
          || (!IS_I_SLICE(storage->slice_header[1].slice_type) &&
              storage->sei_param_curr &&
              storage->sei_param_curr->decode_id == pic_id &&
              storage->sei_param_curr->recovery_point_present_flag == 1)
#endif
      ) {
        dec_cont->error_info = DEC_NO_ERROR; /* the ERROR flag needs to be cleared. */
      }
#ifdef SUPPORT_GDR
      /*  // used test, no I frame in case:
      if (IS_I_SLICE(storage->slice_header[1].slice_type))
        storage->slice_header[1].slice_type = 1;
      */
      if (!IS_I_SLICE(storage->slice_header[1].slice_type) &&
           dec_cont->pic_number == 0 &&
           ((storage->sei_param_curr == NULL) ||
            (storage->sei_param_curr->decode_id != pic_id) ||
            (storage->sei_param_curr->recovery_point_present_flag == 0))) {
        /* API return DEC_NO_REF: discard this frame */
        STREAMTRACE_I("%s","SKIP P/B frames before the first I frame or GDR frame\n");
        storage->pic_started = HANTRO_FALSE;
        ret = H264BSD_NO_REF;
        goto NEXT_NAL;
      }
      if (!IS_I_SLICE(storage->slice_header[1].slice_type) &&
          storage->sei_param_curr &&
          storage->sei_param_curr->recovery_param.recovery_frame_cnt != 0) {
        /* GDR frame: don't include recovery point frame */
        dec_cont->storage.is_gdr_frame = HANTRO_TRUE;
      } else {
        dec_cont->storage.is_gdr_frame = HANTRO_FALSE;
      }
#else
      /* GDR : don't skip P/B frame before the first I frame. */
      if (!IS_I_SLICE(storage->slice_header[1].slice_type) &&
           dec_cont->pic_number == 0) {
        STREAMTRACE_I("%s","SKIP P/B frames before the first I frame\n");
        storage->pic_started = HANTRO_FALSE;
        ret = H264BSD_NO_REF;
        goto NEXT_NAL;
      }
#endif

      if (dec_cont->skip_non_intra &&
           !IS_I_SLICE(storage->slice_header[1].slice_type)) {
        STREAMTRACE_I("%s","DISCARDED P/B PICTURE)\n");
        ret = H264BSD_PB_PIC_SKIPPED;
        goto NEXT_NAL;
      }

      if(h264bsdIsStartOfPicture(storage)) {
        /* stereo view picture, non-matching field pic flag or bottom
         * field flag -> freeze previous stereo view frame of field
         * (frame/field and top/bottom info from base view) */
        if (storage->view &&
            ((storage->slice_header[1].field_pic_flag !=
              storage->slice_headers[0][1].field_pic_flag) ||
             (storage->slice_header[1].bottom_field_flag !=
              storage->slice_headers[0][1].bottom_field_flag))) {
          storage->valid_slice_in_access_unit = 1;
          storage->slice_header = storage->slice_headers[0];

          if (!storage->base_opposite_field_pic) {
            dec_cont->alloc_buffer = 1;
          } else {
            storage->curr_image->data =
              storage->dpb->current_out->data;
            storage->curr_image->pp_data = storage->dpb->current_out->ds_data;
            storage->curr_image->dmv_data = storage->dpb->current_out->dmv_data;
          }
          h264bsdInitRefPicList(storage->dpb);

          return (H264BSD_NEW_ACCESS_UNIT);
        }

        tmp = storage->second_field;
        if(storage->view ?
            storage->base_opposite_field_pic :
            (storage->base_opposite_field_pic =
               h264bsdIsOppositeFieldPic(storage->slice_header + 1,
                                         storage->slice_header + 0,
                                         &storage->second_field,
                                         storage->dpb->prev_ref_frame_num,
                                         storage->aub->new_picture))) {
          /* TODO: make sure that current_out->status[field] is
           * EMPTY */
          if(storage->dpb->delayed_out != 0) {
            /* we delayed the output while waiting for second field */
            storage->dpb->out_buf[storage->dpb->delayed_id].field_picture = 0;   /* mark both fields available */
            storage->dpb->out_buf[storage->dpb->delayed_id].top_field = 0;   /* mark both fields available */
            STREAMTRACE_I("%s","Second field coming...\n");
          }
          if (dec_cont->pre_alloc_buffer[dec_cont->storage.view]) {
            storage->curr_image->data = storage->dpb->current_out->data;
            storage->curr_image->pp_data = storage->dpb->current_out->ds_data;
            storage->curr_image->dmv_data = storage->dpb->current_out->dmv_data;
            dec_cont->pre_alloc_buffer[dec_cont->storage.view] = 0;
#ifdef SUPPORT_SEI
            /* the secode filed */
            storage->dpb->current_out->sei_param[1] = storage->sei_param_curr;
            if (storage->dpb->current_out->sei_param[1])
              storage->dpb->current_out->sei_param[1]->sei_status = SEI_USED;
#endif
          } else {
            ret = H264BSD_ERROR_DETECTED;
            goto NEXT_NAL;
          }
        } else {
          if(storage->dpb->delayed_out != 0) {
            storage->second_field = 0;
            STREAMTRACE_I("%s","Second field missing...Output delayed stuff\n");
            *read_bytes = 0;
            storage->prev_buf_not_finished = HANTRO_TRUE;
            storage->dpb->delayed_out = 0;
            storage->checked_aub = 1;
            return (H264BSD_UNPAIRED_FIELD);
          }

          if(!IS_IDR_NAL_UNIT(&nal_unit) &&
              !dec_cont->mode_change && !dec_cont->gaps_checked_for_this) {
            STREAMTRACE_I("Check gaps in frame num; mode change %d\n",
                         dec_cont->mode_change);

            /* avoid framp gap error after SEEK or P/B pic skip mode */
            if (dec_cont->pic_number == 0 || dec_cont->skip_non_intra)
              storage->dpb->prev_ref_frame_num = storage->slice_header[1].frame_num - 1;
            tmp = h264bsdCheckGapsInFrameNum(storage->dpb,
                                             storage->
                                             slice_header[1].
                                             frame_num,
                                             nal_unit.nal_ref_idc !=
                                             0 ? HANTRO_TRUE :
                                             HANTRO_FALSE,
                                             storage->active_sps->
                                             gaps_in_frame_num_value_allowed_flag);

            dec_cont->gaps_checked_for_this = HANTRO_TRUE;
            if(tmp != HANTRO_OK) {
              dec_cont->gaps_checked_for_this = HANTRO_FALSE;
              STREAMTRACE_E("%s","Gaps in frame num\n");
              if (dec_cont->error_policy & DEC_EC_SEEK_NEXT_I &&
                 !IS_I_SLICE(storage->slice_header[1].slice_type)) {
                dec_cont->packet_loss = 1;
                ret = H264BSD_NO_REF;
                goto NEXT_NAL;
              } else
                dec_cont->packet_loss = 0;
            }
          }

          dec_cont->alloc_buffer = 1;

#ifdef SET_EMPTY_PICTURE_DATA   /* USE THIS ONLY FOR DEBUGGING PURPOSES */
          {
            i32 bgd = SET_EMPTY_PICTURE_DATA;

            DWLmemset(storage->curr_image->data->virtual_address,
                      bgd, storage->curr_image->data->size);
          }
#endif
        }
      } else {
        if(!dec_cont->rlc_mode &&
            storage->slice_header[1].redundant_pic_cnt != 0) {
          ret = H264BSD_RDY;
          goto NEXT_NAL;
        }
      }

      STREAMTRACE_I("%s","vali slice TRUE\n");

      /* store slice header to storage if successfully decoded */
      storage->slice_header[0] = storage->slice_header[1];
      storage->valid_slice_in_access_unit = HANTRO_TRUE;
      storage->prev_nal_unit[0] = nal_unit;

      if(IS_B_SLICE(storage->slice_header[1].slice_type)) {
        if((dec_cont->h264_profile_support == H264_BASELINE_PROFILE) ||
            (dec_cont->rlc_mode != 0)) {
          STREAMTRACE_E("%s","B_SLICE not allowed in baseline decoder\n");
          ret = H264BSD_RDY;
          goto NEXT_NAL;
        }

        if(dec_cont->asic_buff->enable_dmv_and_poc == 0) {
          STREAMTRACE_I("%s","B_SLICE in baseline stream!!! DMV and POC writing were not enabled!\n");
          STREAMTRACE_I("%s","B_SLICE decoding will not be accurate for a while!\n");

          /* enable DMV and POC writing */
          dec_cont->asic_buff->enable_dmv_and_poc = 1;
        }
      }

      /* For VLC mode, end SW decode here */
      if(!dec_cont->rlc_mode) {
        STREAMTRACE_I("%s","\tVlc mode! Skip slice data decoding\n");

        SetPicNums(storage->dpb, storage->slice_header->frame_num);
        /* FIXME: below code may cause side-effect, need to be refined */
#ifdef REORDER_ERROR_FIX
        tmp = h264bsdReorderRefPicListCheck(storage->dpb,
                                            &storage->slice_header->ref_pic_list_reordering,
                                            storage->slice_header->frame_num,
                                            storage->slice_header->num_ref_idx_l0_active,
                                            storage->active_sps->gaps_in_frame_num_value_allowed_flag,
                                            storage->base_opposite_field_pic,
                                            storage->slice_header->field_pic_flag
                                           );
        if(tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","h264bsdReorderRefPicListCheck failed\n");
          *read_bytes = len;
          return (H264BSD_ERROR_DETECTED);
        }
#endif

        return (H264BSD_PIC_RDY);
      }

      /* follow-up code for RLC mode. */
      /* SetPicNums called inside h264bsdReorderRefPicList() */
      h264bsdInitRefPicList(storage->dpb);
      tmp = h264bsdReorderRefPicList(storage->dpb,
                                     &storage->slice_header->
                                     ref_pic_list_reordering,
                                     storage->slice_header->frame_num,
                                     storage->slice_header->
                                     num_ref_idx_l0_active);
      if(tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","h264bsdReorderRefPicList failed\n");
        ret = H264BSD_REF_PICS_ERROR;
        goto NEXT_NAL;
      }

      h264bsdComputeSliceGroupMap(storage,
                                  storage->slice_header->
                                  slice_group_change_cycle);

      tmp = h264bsdDecodeSliceData(dec_cont, &strm,
                                   storage->slice_header);
      if(tmp != HANTRO_OK) {
        h264bsdMarkSliceCorrupted(storage,
                                  storage->slice_header->
                                  first_mb_in_slice);
        return (H264BSD_ERROR_DETECTED);
      }

      if(h264bsdIsEndOfPicture(storage)) {
        pic_ready = HANTRO_TRUE;
        STREAMTRACE_I("%s","Skip redundant RLC\n");
        storage->skip_redundant_slices = HANTRO_TRUE;
      }
      break;

    case NAL_SEI:
      if (storage->sei_buffer != NULL && storage->sei_buffer->buffer != NULL) {
        tmp = h264bsdGetSEIStreamDatas(&strm, storage->sei_buffer);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_I("%s","there is no SEI_buffer\n");
          ret = H264BSD_SEI_ERROR;
          goto NEXT_NAL;
        }
      }
#ifdef SUPPORT_SEI
      else {
        STREAMTRACE_I("%s","SEI : Start Decoding.\n");
        /* select an available sei_param : if found or don't need to find
        * a new one, execute the function of HevcResetSEIParameters,
        * otherwise execute the function of HevcAllocateSEIParameters. */
        tmp = H264bsdPrepareCurrentSEIParameters(storage->sei_param,
                                                 &storage->sei_param_curr,
                                                 storage->sei_param_num,
                                                 pic_id);
        if (tmp != HANTRO_OK) {
          /* no available swi_param : allocate a new.
          * note : there is a limit on the number of sei_param array. */
          tmp = H264bsdAllocateSEIParameters(storage->sei_param,
                                             &storage->sei_param_curr,
                                             &storage->sei_param_num,
                                             dec_cont->ext_buffer_num);
          if (tmp != HANTRO_OK) {
            /* will be waiting for sei_param[i] to become available in here. */
            return H264BSD_NO_FREE_BUFFER;
          }
        }

        /* reset current sei_param memory : the sei_param_curr cannot be NULL. */
        tmp = H264bsdResetSEIParameters(storage->sei_param_curr, storage->sei_param_num, pic_id);
        if (tmp != HANTRO_OK) {
          return H264BSD_NO_FREE_BUFFER;
        }

        /* decode sei */
        tmp = h264bsdDecodeSeiParameters(&strm, storage->sei_param_curr, storage->sps, pic_id);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","SEI : Decoding Failed.\n");
          ret = H264BSD_SEI_ERROR;
          goto NEXT_NAL;
        }
      }
#endif
      ret = H264BSD_SEI_PARSED;
      goto NEXT_NAL;
    case NAL_ACCESS_UNIT_DELIMITER:
      STREAMTRACE_I("%s","NAL_ACCESS_UNIT_DELIMITER, NOT DECODED\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    case NAL_END_OF_SEQUENCE:
      STREAMTRACE_I("%s","END_OF_SEQUENCE, NOT DECODED\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    case NAL_END_OF_STREAM:
      STREAMTRACE_I("%s","END_OF_STREAM, NOT DECODED\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    case NAL_FILLER_DATA:
      STREAMTRACE_I("%s","NAL_FILLER_DATA, NOT DECODED\n");
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    case NAL_PREFIX:
      storage->view = 0;
      storage->non_inter_view_ref = nal_unit.mvc_ext.inter_view_flag == 0;
      /* set flag to indicate that this is probably mvc stream, affects
       * base layer param set activation */
      storage->mvc_stream = storage->mvc;
      goto NEXT_NAL;
    default:
      STREAMTRACE_I("NOT IMPLEMENTED YET %s\n", ParseH264NalunitType(nal_unit.nal_unit_type));
      ret = H264BSD_RDY;
      goto NEXT_NAL;
    }
  }

  if(pic_ready) {
    return (H264BSD_PIC_RDY);
  } else
    return (H264BSD_RDY);

NEXT_NAL:
  storage->last_nal_unit[0] = nal_unit;

  if(!dec_cont->rlc_mode) {
    tmp = H264NextStartCode(&strm);
    if (tmp == HANTRO_OK) {
      if (strm.strm_curr_pos < byte_strm)
        *read_bytes = (u32)(strm.strm_curr_pos - byte_strm + strm.strm_buff_size);
      else
        *read_bytes = (u32)(strm.strm_curr_pos - byte_strm);
      storage->prev_bytes_consumed = *read_bytes;
    } else if (tmp == HANTRO_NOK) {
      storage->prev_bytes_consumed = *read_bytes = strm.strm_data_size;
    } else {
      /*END_OF_STREAM*/
      storage->prev_bytes_consumed = *read_bytes = len;
    }

    if (storage->bumping_flag) {
      if (nal_unit.nal_unit_type == 12)
        storage->compute_time_info.access_unit_size += *read_bytes;
    }
  }

  return ret;

}

/*------------------------------------------------------------------------------

    Function: h264bsdShutdown

        Functional description:
            Shutdown a decoder instance. Function frees all the memories
            allocated for the decoder instance.

        Inputs:
            storage    pointer to storage data structure

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdShutdown(storage_t * storage) {

  /* Variables */

  u32 i;

  /* Code */

  ASSERT(storage);

  for(i = 0; i < MAX_NUM_SEQ_PARAM_SETS; i++) {
    if(storage->sps[i]) {
      FREE(storage->sps[i]->offset_for_ref_frame);
      FREE(storage->sps[i]->vui_parameters);
      FREE(storage->sps[i]);
    }
  }

  for(i = 0; i < MAX_NUM_PIC_PARAM_SETS; i++) {
    if(storage->pps[i]) {
      FREE(storage->pps[i]->run_length);
      FREE(storage->pps[i]->top_left);
      FREE(storage->pps[i]->bottom_right);
      FREE(storage->pps[i]->slice_group_id);
      FREE(storage->pps[i]);
    }
  }

  FREE(storage->mb);
  FREE(storage->slice_group_map);

  /* free sei_param */
  #ifdef SUPPORT_SEI
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (storage->sei_param[i]) {
      if (storage->sei_param[i]->t35_param.payload_byte.buffer) {
        FREE(storage->sei_param[i]->t35_param.payload_byte.buffer);
      }
      if (storage->sei_param[i]->userdataunreg_param.payload_byte.buffer) {
        FREE(storage->sei_param[i]->userdataunreg_param.payload_byte.buffer);
      }
      FREE(storage->sei_param[i]);
    }
  }
  #endif
}

/*------------------------------------------------------------------------------

    Function: h264bsdNextOutputPicture

        Functional description:
            Get next output picture in display order.

        Inputs:
            storage    pointer to storage data structure

        Returns:
            pointer to the picture data
            NULL if no pictures available for display

------------------------------------------------------------------------------*/

const dpbOutPicture_t *h264bsdNextOutputPicture(storage_t * storage) {
  /* Variables */

  const dpbOutPicture_t *p_out;

  /* Code */

  ASSERT(storage);

  p_out = h264bsdDpbOutputPicture(storage->dpb);

  /* store pointer to alternate chroma output if needed */
  if (storage->enable2nd_chroma && p_out &&
      (!storage->active_sps || !storage->active_sps->mono_chrome)) {
    storage->p_ch2 =
      (u32 *)((u8*)p_out->data->virtual_address + storage->dpb->ch2_offset);
    storage->b_ch2 = p_out->data->bus_address + storage->dpb->ch2_offset;
  } else {
    storage->p_ch2 = NULL;
    storage->b_ch2 = 0;
  }

  return p_out;
}

/*------------------------------------------------------------------------------

    Function: h264bsdPicWidth

        Functional description:
            Get width of the picture in macroblocks

        Inputs:
            storage    pointer to storage data structure

        Outputs:
            none

        Returns:
            picture width
            0 if parameters sets not yet activated

------------------------------------------------------------------------------*/

u32 h264bsdPicWidth(storage_t * storage) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  if(storage->active_sps)
    return (storage->active_sps->pic_width_in_mbs);
  else
    return (0);

}

/*------------------------------------------------------------------------------

    Function: h264bsdPicHeight

        Functional description:
            Get height of the picture in macroblocks

        Inputs:
            storage    pointer to storage data structure

        Outputs:
            none

        Returns:
            picture width
            0 if parameters sets not yet activated

------------------------------------------------------------------------------*/

u32 h264bsdPicHeight(storage_t * storage) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  if(storage->active_sps)
    return (storage->active_sps->pic_height_in_mbs);
  else
    return (0);

}

/*------------------------------------------------------------------------------

    Function: h264bsdIsMonoChrome

        Functional description:

        Inputs:
            storage    pointer to storage data structure

        Outputs:

        Returns:

------------------------------------------------------------------------------*/

u32 h264bsdIsMonoChrome(storage_t * storage) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  if(storage->active_sps)
    return (storage->active_sps->mono_chrome);
  else
    return (0);

}

/*------------------------------------------------------------------------------

    Function: h264bsdChromaFormatIdc

        Functional description:

        Inputs:
            storage    pointer to storage data structure

        Outputs:

        Returns:

------------------------------------------------------------------------------*/

u32 h264bsdChromaFormatIdc(storage_t * storage) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  if(storage->active_sps)
    return (storage->active_sps->chroma_format_idc);
  else
    return (0);

}


/*------------------------------------------------------------------------------

    Function: h264bsdFlushBuffer

        Functional description:
            Flush the decoded picture buffer, see dpb.c for details

        Inputs:
            storage    pointer to storage data structure

------------------------------------------------------------------------------*/

void h264bsdFlushBuffer(storage_t * storage) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  h264bsdFlushDpb(storage->dpbs[0]);
  h264bsdFlushDpb(storage->dpbs[1]);
}

/*------------------------------------------------------------------------------

    Function: h264bsdCheckValidParamSets

        Functional description:
            Check if any valid parameter set combinations (SPS/PPS) exists.

        Inputs:
            storage    pointer to storage structure

        Returns:
            1       at least one valid SPS/PPS combination found
            0       no valid param set combinations found

------------------------------------------------------------------------------*/

u32 h264bsdCheckValidParamSets(storage_t * storage) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  return (h264bsdValidParamSets(storage));

}

/*------------------------------------------------------------------------------

    Function: h264bsdAspectRatioIdc

        Functional description:
            Get value of aspect_ratio_idc received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of aspect_ratio_idc if received
            0   otherwise (this is the default value)

------------------------------------------------------------------------------*/
u32 h264bsdAspectRatioIdc(const storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->aspect_ratio_present_flag)
    return (sps->vui_parameters->aspect_ratio_idc);
  else    /* default unspecified */
    return (0);

}

/*------------------------------------------------------------------------------

    Function: h264bsdSarSize

        Functional description:
            Get value of sample_aspect_ratio size received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            values of sample_aspect_ratio size if received
            0   otherwise (this is the default value)

------------------------------------------------------------------------------*/
void h264bsdSarSize(const storage_t * storage, u32 * sar_width,
                    u32 * sar_height) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && storage->active_sps->vui_parameters_present_flag &&
      sps->vui_parameters->aspect_ratio_present_flag &&
      sps->vui_parameters->aspect_ratio_idc == 255) {
    *sar_width = sps->vui_parameters->sar_width;
    *sar_height = sps->vui_parameters->sar_height;
  } else {
    *sar_width = 0;
    *sar_height = 0;
  }

}

/*------------------------------------------------------------------------------

    Function: h264bsdVideoRange

        Functional description:
            Get value of video_full_range_flag received in the VUI data.

        Inputs:
            storage    pointer to storage structure

        Returns:
            1   video_full_range_flag received and value is 1
            0   otherwise

------------------------------------------------------------------------------*/

u32 h264bsdVideoRange(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->video_signal_type_present_flag &&
      sps->vui_parameters->video_full_range_flag)
    return (1);
  else    /* default value of video_full_range_flag is 0 */
    return (0);

}

/*------------------------------------------------------------------------------

    Function: h264bsdMatrixCoefficients

        Functional description:
            Get value of matrix_coefficients received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of matrix_coefficients if received
            2   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdMatrixCoefficients(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->video_signal_type_present_flag &&
      sps->vui_parameters->colour_description_present_flag)
    return (sps->vui_parameters->matrix_coefficients);
  else    /* default unspecified */
    return (2);

}

/*------------------------------------------------------------------------------

    Function: h264bsdTransferCharacteristics

        Functional description:
            Get value of transfer_characteristics received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of transfer_characteristics if received
            2   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdTransferCharacteristics(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->video_signal_type_present_flag &&
      sps->vui_parameters->colour_description_present_flag)
    return (sps->vui_parameters->transfer_characteristics);
  else    /* default unspecified */
    return (2);

}

/*------------------------------------------------------------------------------

    Function: h264bsdColourPrimaries

        Functional description:
            Get value of colour_primaries received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of colour_primaries if received
            2   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdColourPrimaries(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->video_signal_type_present_flag &&
      sps->vui_parameters->colour_description_present_flag)
    return (sps->vui_parameters->colour_primaries);
  else    /* default unspecified */
    return (2);

}

/*------------------------------------------------------------------------------

    Function: h264bsdColourDescPresent

        Functional description:
            Get value of colour_description_present_flag received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of colour_description_present_flag if received
            0   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdColourDescPresent(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->video_signal_type_present_flag)
    return (sps->vui_parameters->colour_description_present_flag);
  else    /* default 0 */
    return (0);
}

/*------------------------------------------------------------------------------

    Function: h264bsdTimingInfoPresent

        Functional description:
            Get value of timing_info_present_flag received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            1   timing_info_present_flag received and value is 1
            0   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdTimingInfoPresent(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->timing_info_present_flag)
    return (1);
  else    /* default value of timing_info_present_flag is 0 */
    return (0);
}

/*------------------------------------------------------------------------------

    Function: h264bsdNumUnitsInTick

        Functional description:
            Get value of num_units_in_tick received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of num_units_in_tick if received
            0   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdNumUnitsInTick(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->timing_info_present_flag)
    return (sps->vui_parameters->num_units_in_tick);
  else    /* default unspecified */
    return (2);
}

/*------------------------------------------------------------------------------

    Function: h264bsdTimeScale

        Functional description:
            Get value of time_scale received in the VUI data

        Inputs:
            storage    pointer to storage structure

        Outputs:
            value of time_scale if received
            0   otherwise (this is the default value)

------------------------------------------------------------------------------*/

u32 h264bsdTimeScale(storage_t * storage) {
  /* Variables */
  const seqParamSet_t *sps;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters->timing_info_present_flag)
    return (sps->vui_parameters->time_scale);
  else    /* default unspecified */
    return (2);
}

/*------------------------------------------------------------------------------

    Function: hh264bsdCroppingParams

        Functional description:
            Get cropping parameters of the active SPS

        Inputs:
            storage    pointer to storage structure

        Outputs:
            p_crop       cropping information

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdCroppingParams(storage_t *storage, struct DecCropParams *p_crop) {
  /* Variables */
  const seqParamSet_t *sps;
  u32 tmp2;

  /* Code */

  ASSERT(storage);
  sps = storage->active_sps;

  if(sps && sps->frame_cropping_flag) {
    u32 tmp1[4]={1,2,2,1};//width
    u32 tmph[4]={1,2,1,1};//height
    tmp2 = sps->frame_mbs_only_flag ? 1 : 2;

    p_crop->crop_left_offset = tmp1[sps->chroma_format_idc] * sps->frame_crop_left_offset;
    p_crop->crop_out_width = 16 * sps->pic_width_in_mbs -
                             tmp1[sps->chroma_format_idc] * (sps->frame_crop_left_offset + sps->frame_crop_right_offset);

    p_crop->crop_top_offset = tmph[sps->chroma_format_idc] * tmp2 * sps->frame_crop_top_offset;
    p_crop->crop_out_height = 16 * sps->pic_height_in_mbs -
                              tmph[sps->chroma_format_idc] * tmp2 * (sps->frame_crop_top_offset +
                                  sps->frame_crop_bottom_offset);
  } else {
    p_crop->crop_left_offset = 0;
    p_crop->crop_out_width = sps ? sps->pic_width_in_mbs * 16 : 0;
    p_crop->crop_top_offset = 0;
    p_crop->crop_out_height = sps ? sps->pic_height_in_mbs * 16 : 0;
  }

}

/*------------------------------------------------------------------------------

    Function: h264bsdFixFrameNum

        Functional description:
            Fix frame numbers in slice headers of current frame. This
            implements SW workaround for hardware fault (bit 12 of frame_num
            field shall be 0 to not break inter prediction).

        Inputs:

        Outputs:

        Returns:

------------------------------------------------------------------------------*/
u32 h264bsdFixFrameNum(u8 *stream, u32 strm_len, u32 frame_num, u32 max_frame_num,
                       u32 *skipped_bytes) {

#define BIT 12
  u8 *p, *p_end;
  u32 value, tmp, first = 1;
  strmData_t strm_data = {0};
  u32 frame_num_len = 0;
  u32 bit_pos;
  u32 loop = 0;

  *skipped_bytes = 0;

  if (!(frame_num & (1 << BIT)))
    return 0;

  /* log2(max_frame_num) -> num bits to represent frame_num */
  while(max_frame_num >> frame_num_len)
    frame_num_len++;
  frame_num_len--;

  ASSERT(frame_num_len > BIT);

  p = stream;
  p_end = p + strm_len;

  if (p[0] == 0 && p[1] == 0 && p[2] <= 1) {
    /* skip prefix */
    while (*p++ == 0);

    *skipped_bytes = p - stream;

    /* if e.g. prefix NAL unit in the beginning of current stream
     * buffer -> loop to find slice header to fix the frame num */
    loop = 1;
  }

  while (1) {

    tmp = (*p++) & 0x1F; /* nal unit type */
    if (tmp == NAL_CODED_SLICE ||
        tmp == NAL_CODED_SLICE_IDR ||
        tmp == NAL_CODED_SLICE_EXT) {
      /* skip nal unit header extension */
      if (tmp == NAL_CODED_SLICE_EXT)
        p += 3;

      if (p >= p_end)
        return 0;

      strm_data.p_strm_buff_start = p;
      strm_data.strm_curr_pos = strm_data.p_strm_buff_start;
      strm_data.bit_pos_in_word = 0;
      strm_data.strm_buff_read_bits = 0;
      strm_data.strm_data_size = p_end - p;

      /* first_mb_in_slice */
      tmp = h264bsdDecodeExpGolombUnsigned(&strm_data, &value);
      if(tmp != HANTRO_OK)
        return 0;

      /* start of frame */
      if (value == 0 && !first)
        return 0;

      /* skip slice_type */
      tmp = h264bsdDecodeExpGolombUnsigned(&strm_data, &value);
      if(tmp != HANTRO_OK)
        return 0;

      /* skip pic_parameter_set_id */
      tmp = h264bsdDecodeExpGolombUnsigned(&strm_data, &value);
      if(tmp != HANTRO_OK)
        return 0;

      /* frame_num */
      tmp = h264bsdShowBits(&strm_data, frame_num_len);
      if(tmp != frame_num)
        return 0;

      bit_pos = strm_data.bit_pos_in_word + frame_num_len - 1 - BIT;
      p = (u8*)strm_data.strm_curr_pos + bit_pos/8;
      bit_pos &= 0x7;
      /* reset bit */
      *p &= ~(0x80 >> bit_pos);

      /* if loop is set -> stream contains start code prefixes and
       * nal unit mode needs to be forced */
      return (loop ? 1 : 0);
    }

    /* h264bsdFindNextStartCode starts with one byte offset -> compensate */
    if (loop) {
      p = (u8*)h264bsdFindNextStartCode(p, p_end - p);
      if (p == NULL)
        return 0;
    } else
      break;
  };

  return 0;

#undef BIT
}

u32 h264bsdCheckErrorFrameAU(struct H264DecContainer * dec_cont, const u8 * byte_strm, u32 len) {
  /* Variables */

  u32 tmp, read_bytes;
  u32 access_unit_boundary_flag = HANTRO_FALSE;
  nalUnit_t nal_unit;
  strmData_t strm = {0};
  storage_t *storage = &dec_cont->storage;
  u8 *strm_buf = dec_cont->hw_buffer;
  u32 buf_len = dec_cont->buff_length;
  u32 ret = 0;
  tmp = h264bsdExtractNalUnit(byte_strm, len, strm_buf, buf_len, &strm,
                              &read_bytes, dec_cont->rlc_mode, &dec_cont->start_code_detected);
  if(tmp != HANTRO_OK) {
    STREAMTRACE_E("%s","BYTE_STREAM\n");
    return (H264BSD_NALUNIT_ERROR);
  }
  dec_cont->first_mb_offset = (len - strm.strm_data_size) * 8;
  tmp = h264bsdDecodeNalUnit(&strm, &nal_unit);
  if(tmp != HANTRO_OK) {
    return (H264BSD_NALUNIT_ERROR);
  }
  dec_cont->first_mb_offset += strm.strm_buff_read_bits;
  storage->tmp_aub->prev_mod_frame_num =
    storage->tmp_aub->prev_frame_num & ~dec_cont->frame_num_mask;
  tmp = h264bsdCheckAccessUnitBoundary(&strm,
                                       &nal_unit,
                                       storage, &access_unit_boundary_flag, 1, dec_cont->rlc_mode);
  if(tmp != HANTRO_OK) {
    STREAMTRACE_E("%s","ACCESS UNIT BOUNDARY CHECK\n");
    if(tmp == PARAM_SET_ERROR)
      ret = (H264BSD_PARAM_SET_ERROR);
    else
      ret = (H264BSD_AU_BOUNDARY_ERROR);
    return (ret);
  }
  if ( access_unit_boundary_flag)
    dec_cont->error_frame_au = 1;
  else
    dec_cont->error_frame_au = 0;
  return (ret);
}
