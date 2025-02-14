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

#include "hevc_container.h"
#include "hevc_sei.h"
#include "hevc_decoder.h"
#include "hevc_asic.h"
#include "hevc_nal_unit.h"
#include "hevc_byte_stream.h"
#include "hevc_seq_param_set.h"
#include "hevc_pic_param_set.h"
#include "hevc_slice_header.h"
#include "hevc_util.h"
#include "hevc_dpb.h"
#include "hevc_vui.h"
#include "hevc_exp_golomb.h"
#include "dec_log.h"
#include "errorhandling.h"
/* Initializes the decoder instance. */
void HevcInit(struct Storage *storage, u32 no_output_reordering) {

  /* Variables */

  /* Code */

  ASSERT(storage);

  HevcInitStorage(storage);

  storage->no_reordering = no_output_reordering;
  storage->poc_last_display = INIT_POC;
}

/* check if pic needs to be skipped due to random access */
u32 SkipPicture(struct Storage *storage, struct NalUnit *nal_unit) {

  if ((nal_unit->nal_unit_type == NAL_CODED_SLICE_RASL_N ||
       nal_unit->nal_unit_type == NAL_CODED_SLICE_RASL_R) &&
      storage->poc->pic_order_cnt < storage->poc_last_display) {
    return HANTRO_TRUE;
  }
  /* CRA and not start of sequence -> all pictures may be output */
  if (storage->poc_last_display != INIT_POC &&
      nal_unit->nal_unit_type == NAL_CODED_SLICE_CRA)
    storage->poc_last_display = -INIT_POC;
  else if (IS_RAP_NAL_UNIT(nal_unit))
    storage->poc_last_display = storage->poc->pic_order_cnt;

  return HANTRO_FALSE;
}

/* Decode a NAL unit until a slice header. This function calls other modules
 * to perform tasks like
    - extract and decode NAL unit from the byte stream
    - decode parameter sets
    - decode slice header and slice data
    - conceal errors in the picture
    - perform deblocking filtering */
u32 HevcDecode(struct HevcDecContainer *dec_cont, const u8 *byte_strm, u32 strm_len,
               u32 pic_id, u32 *read_bytes) {

  enum HevcResult ret = HEVC_RDY;
  u32 tmp, pps_id, sps_id, pps_id_old;
  u32 is_idr = 0;
  u32 access_unit_boundary_flag = HANTRO_FALSE;
  struct Storage *storage;
  struct NalUnit nal_unit;
  struct SeqParamSet seq_param_set;
  struct PicParamSet pic_param_set;
  struct VideoParamSet video_param_set;
  struct StrmData strm = {0};
  const u8 *strm_buf = dec_cont->hw_buffer;
  u32 buf_len = dec_cont->hw_buffer_length;
#ifdef GET_FREE_BUFFER_NON_BLOCK
  struct PocStorage prev_poc;
  i32 prev_poc_last_display;
#endif

  STREAMTRACE_I("%s", "HevcDecode\n");
  ASSERT(dec_cont);
  ASSERT(byte_strm);
  ASSERT(strm_buf);
  ASSERT(strm_len);
  ASSERT(buf_len);
  ASSERT(read_bytes);

  storage = &dec_cont->storage;
  ASSERT(storage);

  STREAMTRACE_I("%s: %d\n",
    "Valid slice in access unit", storage->valid_slice_in_access_unit);

  strm.remove_emul3_byte = 0;
  strm.is_rb = dec_cont->use_ringbuffer;
  strm.stream_info = &dec_cont->llstrminfo.stream_info;

  /* if previous buffer was not finished and same pointer given -> skip NAL
   * unit extraction */
  if (storage->prev_buf_not_finished &&
      byte_strm == storage->prev_buf_pointer) {
    strm = storage->strm[0];
    *read_bytes = storage->prev_bytes_consumed;
    strm.stream_info = &dec_cont->llstrminfo.stream_info;
  } else {
    tmp = HevcExtractNalUnit(byte_strm, strm_len, strm_buf, buf_len, &strm,
                             read_bytes, &dec_cont->start_code_detected);
    if (tmp != HANTRO_OK) {
      STREAMTRACE_E("%s","BYTE_STREAM");
      if (dec_cont->low_latency) {
        while (!dec_cont->llstrminfo.stream_info.last_flag)
          sched_yield();
        *read_bytes = dec_cont->llstrminfo.stream_info.send_len;
      }
      return HEVC_NALUNIT_ERROR;
    }
    /* store stream */
    storage->strm[0] = strm;
    storage->prev_bytes_consumed = *read_bytes;
    storage->prev_buf_pointer = byte_strm;
  }

  storage->prev_buf_not_finished = HANTRO_FALSE;

  tmp = HevcDecodeNalUnit(&strm, &nal_unit, dec_cont->heif_mode);
  if (tmp != HANTRO_OK) {
    /* the strange data pattern from demux, repeated 00000001 in input bit stream data */
    struct StrmData tmp_strm;
    tmp_strm = strm;
    tmp_strm.bit_pos_in_word = 0;
    if (dec_cont->low_latency) {
      while (!dec_cont->llstrminfo.stream_info.last_flag)
        sched_yield();
      strm_len = dec_cont->llstrminfo.stream_info.send_len;
    }
    if (SwShowBits(&tmp_strm, 32) == 0x00000001) {
      *read_bytes = strm_len;
      return HEVC_NALUNIT_ERROR;
    }
    ret = HEVC_NALUNIT_ERROR;
    goto NEXT_NAL;
  }

  if (storage->bumping_flag) {
    if (nal_unit.nal_unit_type != NAL_FILLER_DATA) {
      if(HevcStoreSEIInfoForCurrentPic(storage) == HANTRO_OK) {
        storage->bumping_flag = 0;
        storage->stream_len = 0;
        storage->dpb->bumping_flag = 1;
      }
    }
  }

  /* Discard unspecified and  reserved */
  if ((nal_unit.nal_unit_type >= 10 && nal_unit.nal_unit_type <= 15) ||
      nal_unit.nal_unit_type >= 41) {
    STREAMTRACE_I("%s","DISCARDED NAL (UNSPECIFIED, RESERVED etc)\n");
    ret = HEVC_RDY;
    goto NEXT_NAL;
  }

  /* Discard non-reference nal unit */
  if (dec_cont->skip_frame == DEC_SKIP_NON_REF && IS_SLNR_NAL_UNIT(&nal_unit)) {
    STREAMTRACE_I("%s","DISCARDED NAL (NON-REFERENCE PICTURE)\n");
    ret = HEVC_NONREF_PIC_SKIPPED;
    goto NEXT_NAL;
  }

  /* Discard those NALUs whose temporal_id is greater than max_temporal_layer. */
  if (dec_cont->max_temporal_layer != -1 && nal_unit.temporal_id > dec_cont->max_temporal_layer) {
    STREAMTRACE_I("%s","DISCARDED NAL (temporal_id is greater than max_temporal_layer)\n");
    ret = HEVC_RDY;
    goto NEXT_NAL;
  }

  /* FIXME: Sometimes SPS/PPS NAL following the filler data NAL,
     The stream is consumed incorrectly if discard the whole buffer here */
#if 0
  if (!dec_cont->multi_frame_input_flag) {
    /* Discard filler data */
    if(nal_unit.nal_unit_type == 38) {
      *read_bytes = strm_len;
      return HEVC_RDY;
    }
  }
#endif

  if (!storage->checked_aub) {
    tmp = HevcCheckAccessUnitBoundary(&strm, &nal_unit, storage,
                                      &access_unit_boundary_flag);
    if (tmp != HANTRO_OK) {
      STREAMTRACE_E("%s","ACCESS UNIT BOUNDARY CHECK\n");
      ret = HEVC_AU_BOUNDARY_ERROR;
      goto NEXT_NAL;
    }
  } else {
    storage->checked_aub = 0;
  }

  if (access_unit_boundary_flag) {
    if (storage->dpb->bumping_flag) {
      while (HevcDpbHrdBumping(storage->dpb) == HANTRO_OK);
      storage->dpb->bumping_flag = 0;
    }

    STREAMTRACE_I("%s: %d","Access unit boundary, NAL TYPE", nal_unit.nal_unit_type);
    storage->valid_slice_in_access_unit = HANTRO_FALSE;
  }
  STREAMTRACE_I("%s: %d","nal unit type", nal_unit.nal_unit_type);

  switch (nal_unit.nal_unit_type) {
    case NAL_SEQ_PARAM_SET: {
      STREAMTRACE_I("%s","SEQ PARAM SET\n");
      tmp = HevcDecodeSeqParamSet(&strm, &seq_param_set,  &(storage->vui_parameters_update_flag));
      if (tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","SEQ_PARAM_SET decoding\n");
        ret = HEVC_PARAM_SET_ERROR;
        goto NEXT_NAL;
      } else {
        tmp = HevcStoreSeqParamSet(storage, &seq_param_set);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","SEQ_PARAM_SET allocation\n");
          ret = HEVC_MEMFAIL;
          goto NEXT_NAL;
        }
      }
      ret = HEVC_PARAM_SET_PARSED;
      goto NEXT_NAL;
    }
    case NAL_PIC_PARAM_SET: {
      STREAMTRACE_I("%s","PIC PARAM SET\n");
      tmp = HevcDecodePicParamSet(&strm, &pic_param_set);
      if (tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","PIC_PARAM_SET decoding");
        ret = HEVC_PARAM_SET_ERROR;
        goto NEXT_NAL;
      } else {
        tmp = HevcCheckTileInfo(storage, &pic_param_set);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","PIC_PARAM_SET decoding");
          ret = HEVC_PARAM_SET_ERROR;
          goto NEXT_NAL;
        } else {
          tmp = HevcStorePicParamSet(storage, &pic_param_set);
          if (tmp != HANTRO_OK) {
            STREAMTRACE_E("%s","PIC_PARAM_SET allocation");
            ret = HEVC_MEMFAIL;
            goto NEXT_NAL;
          }
        }
      }
      ret = HEVC_PARAM_SET_PARSED;
      goto NEXT_NAL;
    }
    case NAL_VIDEO_PARAM_SET: {
      STREAMTRACE_I("%s","VIDEO PARAM SET\n");
      tmp = HevcDecodeVideoParamSet(&strm, &video_param_set);
      if (tmp != HANTRO_OK) {
        STREAMTRACE_E("%s","VIDEO_PARAM_SET decoding");
        ret = HEVC_PARAM_SET_ERROR;
        goto NEXT_NAL;
      } else {
        tmp = HevcStoreVideoParamSet(storage, &video_param_set);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","VIDEO_PARAM_SET allocation");
          ret = HEVC_MEMFAIL;
          goto NEXT_NAL;
        }
      }
      ret = HEVC_PARAM_SET_PARSED;
      goto NEXT_NAL;
    }
    case NAL_PREFIX_SEI:
    case NAL_SUFFIX_SEI: {
      if (storage->sei_buffer != NULL && storage->sei_buffer->buffer != NULL) {
        tmp = HevcGetSEIStreamDatas(&strm, storage->sei_buffer);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_I("%s","there is no SEI_buffer\n");
          ret = HEVC_SEI_ERROR;
          goto NEXT_NAL;
        }
      }
#ifdef SUPPORT_SEI
      else {
        STREAMTRACE_I("%s","SEI : Start Decoding.\n");
        /* select an available sei_param : if found or don't need to find
        * a new one, execute the function of HevcResetSEIParameters,
        * otherwise execute the function of HevcAllocateSEIParameters. */
        tmp = HevcPrepareCurrentSEIParameters(storage->sei_param,
                                              &storage->sei_param_curr,
                                              storage->sei_param_num,
                                              pic_id);
        if (tmp != HANTRO_OK) {
          /* no available swi_param : allocate a new.
          * note : there is a limit on the number of sei_param array. */
          tmp = HevcAllocateSEIParameters(storage->sei_param,
                                          &storage->sei_param_curr,
                                          &storage->sei_param_num,
                                          dec_cont->ext_buffer_num);
          if (tmp != HANTRO_OK) {
            /* will be waiting for sei_param[i] to become available in here. */
            return HEVC_NO_FREE_BUFFER;
          }
        }

        /* reset current sei_param memory : the sei_param_curr cannot be NULL. */
        tmp = HevcResetSEIParameters(storage->sei_param_curr, storage->sei_param_num, pic_id);
        if (tmp != HANTRO_OK) {
          return HEVC_NO_FREE_BUFFER;
        }

        /* decode sei */
        tmp = HevcDecodeSEIParameters(&strm, nal_unit.temporal_id, storage->sei_param_curr,
                                      (struct SeqParamSet**)(&(storage->sps)), pic_id);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","SEI : Decoding Failed.\n");
          ret = HEVC_SEI_ERROR;
          goto NEXT_NAL;
        }
      }
#endif
      ret = HEVC_SEI_PARSED;
      goto NEXT_NAL;
    }
    case NAL_END_OF_SEQUENCE: {
      storage->poc_last_display = INIT_POC;
      break;
    }
    default: {
      if (IS_SLICE_NAL_UNIT(&nal_unit)) {
        STREAMTRACE_I("%s","decode slice header\n");

        storage->pic_started = HANTRO_TRUE;

        if (HevcIsStartOfPicture(storage)) {
          storage->current_pic_id = pic_id;

          tmp = HevcCheckPpsId(&strm, &pps_id, IS_RAP_NAL_UNIT(&nal_unit));
          if (tmp != HANTRO_OK) {
            STREAMTRACE_E("%s","Param set activation");
            ret = HEVC_PARAM_SET_ERROR;
            goto NEXT_NAL;
          }
          /* store old active_sps_id and return headers ready
          * indication if active_sps changes */
          sps_id = storage->active_sps_id;

          /* store old active_pps_id */
          pps_id_old = storage->active_pps_id;

          tmp = HevcActivateParamSets(storage, pps_id,
                                      IS_RAP_NAL_UNIT(&nal_unit));
          if (tmp != HANTRO_OK || storage->active_sps == NULL ||
              storage->active_pps == NULL) {
            STREAMTRACE_E("%s","Param set activation");
            ret = HEVC_PARAM_SET_ERROR;
            goto NEXT_NAL;
          }

          /* reallocate tile_edge_buffer when active pps each time */
          if ((storage->old_sps_id == storage->active_sps_id &&
              pps_id_old != storage->active_pps_id) ||
              (storage->num_tile_columns_old !=
              storage->active_pps->tile_info.num_tile_columns) ||
              (storage->log_max_coding_block_size_old !=
              storage->active_sps->log_max_coding_block_size)) {
            tmp = AllocateAsicTileEdgeMems(dec_cont);
            if (tmp != HANTRO_OK) {
              ret = HEVC_MEMFAIL;
              goto NEXT_NAL;
            }
          }

          if (sps_id != storage->active_sps_id) {
            struct SeqParamSet *old_sps = NULL;
            /*struct SeqParamSet *new_sps = storage->active_sps;*/
            u32 no_output_of_prior_pics_flag = 1;
            if (storage->active_vps->vps_timing_info_present_flag &&
                (storage->active_sps->vui_parameters_present_flag &&
                storage->active_sps->vui_parameters.vui_timing_info_present_flag)) {
              if ((storage->active_vps->vps_time_scale == storage->active_sps->vui_parameters.vui_time_scale) &&
                  (storage->active_vps->vps_num_units_in_tick == storage->active_sps->vui_parameters.vui_num_units_in_tick))
                storage->frame_rate = ((double)storage->active_vps->vps_time_scale) /
                                      storage->active_vps->vps_num_units_in_tick;
            } else {
              if (storage->active_vps->vps_timing_info_present_flag)
                storage->frame_rate = ((double)storage->active_vps->vps_time_scale) /
                                      storage->active_vps->vps_num_units_in_tick;

              else if (storage->active_sps->vui_parameters_present_flag &&
                      storage->active_sps->vui_parameters.vui_timing_info_present_flag)
                storage->frame_rate = ((double)storage->active_sps->vui_parameters.vui_time_scale) /
                                      storage->active_sps->vui_parameters.vui_num_units_in_tick;

              else
                storage->frame_rate = 0;
            }
            if (storage->old_sps_id < MAX_NUM_SEQ_PARAM_SETS) {
              old_sps = storage->sps[storage->old_sps_id];
            }

            *read_bytes = 0;
            storage->prev_buf_not_finished = HANTRO_TRUE;

            if (IS_RAP_NAL_UNIT(&nal_unit)) {
              tmp =
                HevcCheckPriorPicsFlag(&no_output_of_prior_pics_flag, &strm);
              /* TODO: why? */
              /*tmp = HANTRO_NOK;*/
            } else {
              tmp = HANTRO_NOK;
            }

            if ((tmp != HANTRO_OK) || (no_output_of_prior_pics_flag != 0) ||
                (nal_unit.nal_unit_type == NAL_CODED_SLICE_CRA && storage->no_rasl_output) ||
                (storage->dpb->no_reordering) || (old_sps == NULL) /*||
                        (old_sps->pic_width != new_sps->pic_width) ||
                        (old_sps->pic_height != new_sps->pic_height) ||
                        (old_sps->max_dpb_size != new_sps->max_dpb_size)*/) {
              storage->dpb->flushed = 0;

              /* Bump DPB to make sure dpb->num_out_pics_buffered <= dpb->real_size */
              if (no_output_of_prior_pics_flag != 0 ||
                (nal_unit.nal_unit_type == NAL_CODED_SLICE_CRA && storage->no_rasl_output)) {
                storage->dpb->flushed = 1;
                HevcDpbUpdateOutputList2(storage->dpb);
              }
            } else {
              HevcFlushDpb(storage->dpb);
            }

            storage->old_sps_id = storage->active_sps_id;
            storage->pic_started = HANTRO_FALSE;


            if (nal_unit.nal_unit_type == NAL_CODED_SLICE_CRA &&
                storage->no_rasl_output) {
              HevcDpbMarkOlderUnused(storage->dpb, 0x7FFFFFFF, 0);
            }

            return (HEVC_HDRS_RDY);
          }
        }

        tmp = HevcDecodeSliceHeader(&strm, storage->slice_header + 1,
                                    storage->active_sps, storage->active_pps,
                                    &nal_unit);
        if (tmp != HANTRO_OK) {
          STREAMTRACE_E("%s","SLICE_HEADER");
          ret = HEVC_SLICE_HDR_ERROR;
          if (storage->sei_param_num > 0 &&
              storage->sei_param_curr != NULL &&
              storage->sei_param_curr->decode_id == pic_id )
            storage->sei_param_curr->sei_status = SEI_UNUSED;
          goto NEXT_NAL;
        }

        STREAMTRACE_I("%s","valid slice TRUE\n");

        /* store slice header to storage if successfully decoded */
        storage->slice_header[0] = storage->slice_header[1];
        storage->prev_nal_unit[0] = nal_unit;

  #ifdef GET_FREE_BUFFER_NON_BLOCK
        prev_poc = storage->poc[0];
        prev_poc_last_display = storage->poc_last_display;
  #endif

        HevcDecodePicOrderCnt(storage->poc,
                              storage->active_sps->max_pic_order_cnt_lsb,
                              storage->slice_header, &nal_unit, storage->no_rasl_output);

        /* check if picture shall be skipped (non-decodable picture after
        * random access etc) */
        if (SkipPicture(storage, &nal_unit)) {
          STREAMTRACE_I("%s: %d","SKIP DECODING\n", nal_unit.nal_unit_type);
          ret = HEVC_RDY;
          if (storage->sei_param_num > 0 &&
              storage->sei_param_curr != NULL &&
              storage->sei_param_curr->decode_id == pic_id )
            storage->sei_param_curr->sei_status = SEI_UNUSED;
          goto NEXT_NAL;
        }

        /*
        * 1. new I slice: maybe is I frame, the ERROR flag needs to be cleared.
        * 2. new GDR start frame: the ERROR flag needs to be cleared.
        */
        if (
            IS_I_SLICE(storage->slice_header->slice_type)
#ifdef SUPPORT_GDR
            || (!IS_RAP_NAL_UNIT(dec_cont->storage.prev_nal_unit) &&
                storage->sei_param_curr &&
                storage->sei_param_curr->decode_id == pic_id &&
                storage->sei_param_curr->recovery_point_present_flag == 1)
#endif
        ) {
          dec_cont->error_info = DEC_NO_ERROR; /* the ERROR flag needs to be cleared. */
          if (storage->picture_broken && dec_cont->error_policy & DEC_EC_SEEK_NEXT_I) {
            is_idr = 1; /* error detected : I slice / I frame need reset DPB buffer */
            if (dec_cont->error_policy & DEC_EC_REF_REPLACE &&
                dec_cont->use_video_compressor) {
              dec_cont->error_policy &= ~DEC_EC_SEEK_NEXT_I;
              dec_cont->error_policy |= DEC_EC_NO_SKIP;
            }
          } else {
            is_idr = IS_IDR_NAL_UNIT(&nal_unit) || IS_BLA_NAL_UNIT(&nal_unit);
          }
        }
        if(!dec_cont->heif_mode) {
#ifdef SUPPORT_GDR
          /*  // used test, no I frame in case:
          if (IS_RAP_NAL_UNIT(dec_cont->storage.prev_nal_unit))
            dec_cont->storage.prev_nal_unit->nal_unit_type = 1;
          */
          if (!IS_RAP_NAL_UNIT(dec_cont->storage.prev_nal_unit) &&
              dec_cont->pic_number == 0 &&
              ((storage->sei_param_curr == NULL) ||
                (storage->sei_param_curr->decode_id != pic_id) ||
                (storage->sei_param_curr->recovery_point_present_flag == 0))) {
            /* API return DEC_NO_REF: discard this frame */
            STREAMTRACE_I("%s","SKIP P/B frames before the first I frame or GDR frame\n");
            storage->pic_started = HANTRO_FALSE;
            ret = HEVC_NO_REF;
            if (storage->sei_param_num > 0 &&
                storage->sei_param_curr != NULL &&
                storage->sei_param_curr->decode_id == pic_id )
              storage->sei_param_curr->sei_status = SEI_UNUSED;
            goto NEXT_NAL;
          }
          if (!IS_RAP_NAL_UNIT(dec_cont->storage.prev_nal_unit) &&
              storage->sei_param_curr &&
              storage->sei_param_curr->recovery_param.recovery_poc_cnt != 0) {
            /* GDR frame: don't include recovery point frame */
            dec_cont->storage.is_gdr_frame = HANTRO_TRUE;
          } else {
            dec_cont->storage.is_gdr_frame = HANTRO_FALSE;
          }
#endif
        }
        u32 ret_tmp = HevcSetRefPics(storage->dpb, storage->slice_header,
                          storage->poc->pic_order_cnt,
                          storage->active_sps,
                          is_idr,
                          nal_unit.nal_unit_type == NAL_CODED_SLICE_CRA &&
                          storage->no_rasl_output,
                          storage->sei_param_curr &&
                          storage->sei_param_curr->decode_id == pic_id &&
                          storage->sei_param_curr->bufperiod_present_flag &&
                          storage->sei_param_curr->pictiming_present_flag,
                          dec_cont);

        if (DEC_PARAM_ERROR == ret_tmp ||
          (dec_cont->skip_non_intra &&
          (!IS_I_SLICE(storage->slice_header->slice_type) ||
          storage->ref_num_curr_pic > 0))) {
          if (DEC_PARAM_ERROR == ret_tmp) {
            ret = HEVC_REF_PICS_ERROR;
            if (dec_cont->heif_mode) ret = HEVC_RDY;
          }
          else
            ret = HEVC_PB_PIC_SKIPPED;

          if (!dec_cont->multi_frame_input_flag) {
            if (dec_cont->low_latency) {
              while (!dec_cont->llstrminfo.stream_info.last_flag)
                sched_yield();
              strm.strm_data_size = dec_cont->llstrminfo.stream_info.send_len;
              strm_len = dec_cont->llstrminfo.stream_info.send_len;
            }
            strm.strm_curr_pos = strm.strm_buff_start + strm.strm_data_size;
            storage->prev_bytes_consumed = strm.strm_data_size;
            *read_bytes = strm_len;
            return ret;
          }
          if (storage->sei_param_num > 0 &&
              storage->sei_param_curr != NULL &&
              storage->sei_param_curr->decode_id == pic_id )
            storage->sei_param_curr->sei_status = SEI_UNUSED;
          goto NEXT_NAL;
        }

        if (IS_RAP_NAL_UNIT(&nal_unit) && storage->no_rasl_output)
          storage->no_rasl_output = 0;

        HevcDpbUpdateOutputList(storage->dpb);

        if (HevcIsStartOfPicture(storage)) {
          storage->curr_image->data = HevcAllocateDpbImage(
                                        storage->dpb, storage->poc->pic_order_cnt,
                                        storage->slice_header->pic_order_cnt_lsb,
                                        IS_IDR_NAL_UNIT(storage->prev_nal_unit), storage->current_pic_id,
                                        nal_unit.nal_unit_type == NAL_CODED_SLICE_TSA_R ||
                                        nal_unit.nal_unit_type == NAL_CODED_SLICE_STSA_R, dec_cont);

          if(storage->curr_image->data == NULL) {
            if (dec_cont->abort)
              return HEVC_ABORTED;
            else if (dec_cont->add_extra_ext_buf == 1) {
              return HEVC_WAITING_BUFFER;
            }
#ifdef GET_FREE_BUFFER_NON_BLOCK
            else {
              storage->poc[0] = prev_poc;
              storage->poc_last_display = prev_poc_last_display;
              HevcUpdateSeiInfo(storage->sei_buffer, storage->sei_param_curr);
              return HEVC_NO_FREE_BUFFER;
            }
#endif
          }

 #ifdef SET_EMPTY_PICTURE_DATA /* USE THIS ONLY FOR DEBUGGING PURPOSES */
          {
            i32 bgd = SET_EMPTY_PICTURE_DATA;

            DWLPrivateAreaMemset(storage->curr_image->data->virtual_address, bgd,
                                storage->curr_image->data->size);
          }
#endif

          storage->curr_image->pp_data = storage->dpb->current_out->pp_data;
          storage->curr_image->dmv_data = storage->dpb->current_out->dmv_data;

          if (storage->dpb->no_reordering) {
            /* output this picture next */
            struct DpbStorage *dpb = storage->dpb;
            struct DpbOutPicture *dpb_out = &dpb->out_buf[dpb->out_index_w];
            const struct DpbPicture *current_out = dpb->current_out;

            dpb_out->pp_data = current_out->pp_data;
            dpb_out->data = current_out->data;
            dpb_out->dmv_data = current_out->dmv_data;
            dpb_out->is_idr = current_out->is_idr;
            dpb_out->pic_code_type = current_out->pic_code_type;
            dpb_out->pic_id = current_out->pic_id;
            dpb_out->poc = current_out->pic_order_cnt;
            dpb_out->sei_param = current_out->sei_param;
            dpb_out->error_ratio = current_out->error_ratio;
            dpb_out->mem_idx = current_out->mem_idx;
            dpb_out->tiled_mode = current_out->tiled_mode;
            dpb_out->pic_output_flag = current_out->pic_output_flag;
            dpb_out->is_gdr_frame = current_out->is_gdr_frame;

            dpb_out->pic_width = dpb->pic_width;
            dpb_out->pic_height = dpb->pic_height;
            dpb_out->crop_params = dpb->crop_params;
            dpb_out->bit_depth_luma = dpb->bit_depth_luma;
            dpb_out->bit_depth_chroma = dpb->bit_depth_chroma;
            dpb_out->mono_chrome = dpb->mono_chrome;

            dpb->num_out++;
            dpb->out_index_w++;
            if (dpb->out_index_w == MAX_DPB_SIZE + 1) dpb->out_index_w = 0;

            MarkTempOutput(dpb->fb_list, current_out->mem_idx);
          }
        }

        storage->valid_slice_in_access_unit = HANTRO_TRUE;

        return (HEVC_PIC_RDY);
      } else {
        STREAMTRACE_I("%s: %d","SKIP DECODING\n", nal_unit.nal_unit_type);
        ret = HEVC_RDY;
        goto NEXT_NAL;
      }
    }
  }

NEXT_NAL:
  if (HevcNextStartCode(&strm) == HANTRO_OK) {
    if (strm.strm_curr_pos < byte_strm)
      *read_bytes = (u32)(strm.strm_curr_pos - byte_strm + strm.strm_buff_size);
    else
      *read_bytes = (u32)(strm.strm_curr_pos - byte_strm);
    storage->prev_bytes_consumed = *read_bytes;
  } else {
    /*END_OF_STREAM*/
    storage->prev_bytes_consumed = *read_bytes = strm_len;
  }
  if (storage->bumping_flag) {
    if (nal_unit.nal_unit_type == NAL_FILLER_DATA)
      storage->stream_len += *read_bytes;
  }

  return ret;
}

/* Shutdown a decoder instance. Function frees all the memories allocated
 * for the decoder instance. */
void HevcShutdown(struct Storage *storage) {

  u32 i;

  ASSERT(storage);

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

/* Get next output picture in display order. */
const struct DpbOutPicture *HevcNextOutputPicture(struct Storage *storage) {

  const struct DpbOutPicture *out;

  ASSERT(storage);

  out = HevcDpbOutputPicture(storage->dpb);

  return out;
}

/* Returns picture width in samples. */
u32 HevcPicWidth(struct Storage *storage) {

  ASSERT(storage);

  if (storage->active_sps) {
    return (storage->active_sps->pic_width);
  } else
    return (0);
}

/* Returns picture height in samples. */
u32 HevcPicHeight(struct Storage *storage) {

  ASSERT(storage);

  if (storage->active_sps)
    return (storage->active_sps->pic_height);
  else
    return (0);
}

/* Returns true if chroma format is 4:0:0. */
u32 HevcIsMonoChrome(struct Storage *storage) {

  ASSERT(storage);

  if (storage->active_sps)
    return (storage->active_sps->mono_chrome);
  else
    return (0);
}

/* Flushes the decoded picture buffer, see dpb.c for details. */
void HevcFlushBuffer(struct Storage *storage) {

  ASSERT(storage);

  HevcFlushDpb(storage->dpb);
}

/* Get value of aspect_ratio_idc received in the VUI data. */
u32 HevcAspectRatioIdc(const struct Storage *storage) {

  const struct SeqParamSet *sps;

  ASSERT(storage);
  sps = storage->active_sps;

  if (sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters.aspect_ratio_present_flag)
    return (sps->vui_parameters.aspect_ratio_idc);
  else /* default unspecified */
    return (0);
}

/* Get value of sample_aspect_ratio size received in the VUI data. */
void HevcSarSize(const struct Storage *storage, u32 *sar_width,
                 u32 *sar_height) {

  const struct SeqParamSet *sps;

  ASSERT(storage);
  sps = storage->active_sps;

  if (sps && storage->active_sps->vui_parameters_present_flag &&
      sps->vui_parameters.aspect_ratio_present_flag &&
      sps->vui_parameters.aspect_ratio_idc == 255) {
    *sar_width = sps->vui_parameters.sar_width;
    *sar_height = sps->vui_parameters.sar_height;
  } else {
    *sar_width = 0;
    *sar_height = 0;
  }
}

/* Get value of video_full_range_flag received in the VUI data. */
u32 HevcVideoRange(struct Storage *storage) {

  const struct SeqParamSet *sps;

  ASSERT(storage);
  sps = storage->active_sps;

  if (sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters.video_signal_type_present_flag &&
      sps->vui_parameters.video_full_range_flag)
    return (1);
  else /* default value of video_full_range_flag is 0 */
    return (0);
}

/* Get value of matrix_coefficients received in the VUI data. */
u32 HevcMatrixCoefficients(struct Storage *storage) {

  const struct SeqParamSet *sps;

  ASSERT(storage);
  sps = storage->active_sps;

  if (sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters.video_signal_type_present_flag &&
      sps->vui_parameters.colour_description_present_flag)
    return (sps->vui_parameters.matrix_coefficients);
  else /* default unspecified */
    return (2);
}

/* Get value of colour_primaries received in the VUI data. */
u32 HevcColourPrimaries(struct Storage *storage) {

  const struct SeqParamSet *sps;

  ASSERT(storage);
  sps = storage->active_sps;

  if (sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters.video_signal_type_present_flag &&
      sps->vui_parameters.colour_description_present_flag)
    return (sps->vui_parameters.colour_primaries);
  else /* default unspecified */
    return (2);
}

/**
 * Get value of transfer_characteristics received in the VUI data.
 *
 * \param [out] vui_trc pointer to fill with value in sps vui. Filled with value 2 if it is not exist;
 * \param [out] sei_trc pointer to fille with value in SEI. Filled with value 2 in vui if it is not exist;
 * \return 0 valid value is filled fot both and sei;
 * \return 1 only sps_trc is filled;
 * \return 2 only sei_trc is filled;
 * \return -1 no information in vui or sei. Filled both as (2), which means TC_UNSPECIFIED;
*/
u32 HevcTransferCharacteristics(struct Storage *storage, u32 *vui_trc, u32 *sei_trc) {

  const struct SeqParamSet *sps;
  const struct HevcSEIParameters *sei;

  ASSERT(storage);
  sps = storage->active_sps;
  sei = storage->sei_param_curr;

  *vui_trc = *sei_trc = 2;
  if (sps && sps->vui_parameters_present_flag &&
      sps->vui_parameters.video_signal_type_present_flag &&
      sps->vui_parameters.colour_description_present_flag)
    *vui_trc = (sps->vui_parameters.transfer_characteristics);
  if (sei && sei->preferred_trc_present_flag &&
             sei->preferred_transfer_characteristics != 2)
    *sei_trc = sei->preferred_transfer_characteristics;

  if ((*vui_trc!=2) && (*sei_trc!=2))
    return 0;
  else if((*vui_trc!=2) && (*sei_trc==2))
    return 1;
  else
    return 2; /*(*vui_trc==2) && (*sei_trc!=2) */
}

/* Get value of vui_timing_info_present_flag received in the VUI data. */
u32 HevcTimingInfoPresent(struct Storage *storage) {

  const struct VideoParamSet *vps;
  const struct SeqParamSet *sps;

  ASSERT(storage);
  vps = storage->active_vps;
  sps = storage->active_sps;

  if (vps && vps->vps_timing_info_present_flag) {
    return (1);
  } else {
    if (sps && sps->vui_parameters_present_flag &&
        sps->vui_parameters.vui_timing_info_present_flag)
      return (1);
    else /* default value of vui_timing_info_present_flag is 0 */
      return (0);
  }
}

/* Get value of vui_num_units_in_tick received in the VUI data. */
u32 HevcNumUnitsInTick(struct Storage *storage) {

  const struct VideoParamSet *vps;
  const struct SeqParamSet *sps;

  ASSERT(storage);
  vps = storage->active_vps;
  sps = storage->active_sps;

  if (vps && vps->vps_timing_info_present_flag) {
    return (vps->vps_num_units_in_tick);
  } else {
    if (sps && sps->vui_parameters_present_flag &&
        sps->vui_parameters.vui_timing_info_present_flag)
      return (sps->vui_parameters.vui_num_units_in_tick);
    else /* default unspecified */
      return (2);
  }
}

/* Get value of vui_time_scale received in the VUI data. */
u32 HevcTimeScale(struct Storage *storage) {

  const struct VideoParamSet *vps;
  const struct SeqParamSet *sps;

  ASSERT(storage);
  vps = storage->active_vps;
  sps = storage->active_sps;

  if (vps && vps->vps_timing_info_present_flag) {
    return (vps->vps_time_scale);
  } else {
    if (sps && sps->vui_parameters_present_flag &&
        sps->vui_parameters.vui_timing_info_present_flag)
      return (sps->vui_parameters.vui_time_scale);
    else /* default unspecified */
      return (2);
  }
}

/* Get cropping parameters of the active SPS. */
void HevcCroppingParams(struct Storage *storage, u32 *cropping_flag,
                        u32 *left_offset, u32 *width, u32 *top_offset,
                        u32 *height) {

  const struct SeqParamSet *sps;

  ASSERT(storage);
  sps = storage->active_sps;

  if (sps && sps->pic_cropping_flag) {
    u32 tmp1[4]={1,2,2,1};//width
    u32 tmph[4]={1,2,1,1};//height
    u32 tmp2 = 1;
    *cropping_flag = 1;
    *left_offset = tmp1[sps->chroma_format_idc] * sps->pic_crop_left_offset;
    *width = sps->pic_width -
             tmp1[sps->chroma_format_idc] * (sps->pic_crop_left_offset + sps->pic_crop_right_offset);

    *top_offset = tmph[sps->chroma_format_idc] * tmp2 * sps->pic_crop_top_offset;
    *height = sps->pic_height - tmph[sps->chroma_format_idc] * tmp2 * (sps->pic_crop_top_offset +
              sps->pic_crop_bottom_offset);
  } else {
    *cropping_flag = 0;
    *left_offset = 0;
    *width = 0;
    *top_offset = 0;
    *height = 0;
  }
}

/* Returns luma bit depth. */
u32 HevcLumaBitDepth(struct Storage *storage) {

  ASSERT(storage);

  if (storage->active_sps)
    return (storage->active_sps->bit_depth_luma);
  else
    return (0);
}

/* Returns chroma bit depth. */
u32 HevcChromaBitDepth(struct Storage *storage) {

  ASSERT(storage);

  if (storage->active_sps)
    return (storage->active_sps->bit_depth_chroma);
  else
    return (0);
}
