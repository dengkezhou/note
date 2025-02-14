/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
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

#include "dwl.h"
#include "basetype.h"
#include "h264hwd_vlc.h"
#include "h264hwd_stream.h"
#include "h264hwd_util.h"
#include "h264hwd_sei.h"
#include "dec_log.h"


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 0.
 * @param[in]    stream             input stream
 * @param[in]    buf_param          H264BufPeriodParameters of SEI
 * @param[in]    sps                sequence parameter set
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : invalid input stream data
 *                                  -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodeBufferingPeriodInfo(strmData_t *stream,
                                            struct H264BufPeriodParameters *buf_param,
                                            seqParamSet_t **sps) {
  u32 tmp, i, value;
  vuiParameters_t *p_vui_param;
  u32 initial_cpb_len;

  if (stream == NULL || buf_param == NULL || sps == NULL)
    return HANTRO_NOK;

  /* seq_parameter_set_id */
  tmp = h264bsdDecodeExpGolombUnsigned(stream, &value);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (value >= MAX_NUM_SEQ_PARAM_SETS) return (HANTRO_NOK);
  if (sps[value] == NULL) return HANTRO_NOK;
  buf_param->seq_parameter_set_id = value;

  if (!sps[value]->vui_parameters_present_flag)
    return HANTRO_NOK;
  if (sps[value]->vui_parameters == NULL || sps[value]->vui_parameters->error_hrdparameter_flag)
    return (HANTRO_NOK);
  p_vui_param = sps[value]->vui_parameters;
  initial_cpb_len = p_vui_param->nal_hrd_parameters.initial_cpb_removal_delay_length;

  /* need to do better */
  if (p_vui_param->nal_hrd_parameters_present_flag) {
    if (p_vui_param->nal_hrd_parameters.cpb_cnt == 0)
      p_vui_param->nal_hrd_parameters.cpb_cnt = 1;
    for (i = 0; i <= p_vui_param->nal_hrd_parameters.cpb_cnt; i++) {
      tmp = h264bsdShowBits(stream, initial_cpb_len);
      if (h264bsdFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
        return (END_OF_STREAM);
      if (tmp < 1) return (END_OF_STREAM);
      buf_param->initial_cpb_removal_delay[i] = tmp;

      tmp = h264bsdShowBits(stream, initial_cpb_len);
      if (h264bsdFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
        return (END_OF_STREAM);
      buf_param->initial_cpb_removal_delay_offset[i] = tmp;
    }
  }

  /* need to do better */
  if (p_vui_param->vcl_hrd_parameters_present_flag) {
    if (p_vui_param->nal_hrd_parameters.cpb_cnt == 0)
      p_vui_param->nal_hrd_parameters.cpb_cnt = 1;
    for (i = 0; i <= p_vui_param->vcl_hrd_parameters.cpb_cnt; i++) {
      tmp = h264bsdShowBits(stream, initial_cpb_len);
      if (h264bsdFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
        return (END_OF_STREAM);
      if (tmp < 1) return (END_OF_STREAM);
      buf_param->initial_cpb_removal_delay[i] = tmp;

      tmp = h264bsdShowBits(stream, initial_cpb_len);
      if (h264bsdFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
        return (END_OF_STREAM);
      buf_param->initial_cpb_removal_delay_offset[i] = tmp;
    }
  }
  return (HANTRO_OK);
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 1.
 * @param[in]    stream             input stream
 * @param[in]    buf_param          H264BufPeriodParameters of SEI
 * @param[in]    pic_param          H264PicTimingParameters of SEI
 * @param[in]    sps                sequence parameter set
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : invalid input stream data
 *                                  -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodePicTimingInfo(strmData_t *stream,
                                      struct H264BufPeriodParameters *buf_param,
                                      struct H264PicTimingParameters *pic_param,
                                      seqParamSet_t **sps) {
  u32 tmp, i;
  u32 CpbDpbDelaysPresentFlag;
  u32 cpb_removal_len = 0, dpb_output_len = 0;
  u32 pic_struct_present_flag;
  u32 NumClockTs = 0;
  u32 time_offset_length;
  u32 sps_id;
  vuiParameters_t *p_vui_param;

  if (stream == NULL || buf_param == NULL || pic_param == NULL || sps == NULL)
    return HANTRO_NOK;
  sps_id = buf_param->seq_parameter_set_id;
  if (sps[sps_id] == NULL || (!sps[sps_id]->vui_parameters_present_flag))
    return HANTRO_NOK;
  if (sps[sps_id]->vui_parameters == NULL || sps[sps_id]->vui_parameters->error_hrdparameter_flag)
    return HANTRO_NOK;

  p_vui_param = sps[sps_id]->vui_parameters;
  CpbDpbDelaysPresentFlag = sps[sps_id]->vui_parameters_present_flag &&
                            ((p_vui_param->nal_hrd_parameters_present_flag != 0) ||
                            (p_vui_param->vcl_hrd_parameters_present_flag != 0));
  if (CpbDpbDelaysPresentFlag) {
    if (sps[sps_id]->vui_parameters_present_flag) {
      if (p_vui_param->nal_hrd_parameters_present_flag) {
        cpb_removal_len =
            p_vui_param->nal_hrd_parameters.cpb_removal_delay_length;
        dpb_output_len =
            p_vui_param->nal_hrd_parameters.dpb_output_delay_length;
      }
      if (p_vui_param->vcl_hrd_parameters_present_flag) {
        cpb_removal_len =
            p_vui_param->vcl_hrd_parameters.cpb_removal_delay_length;
        dpb_output_len =
            p_vui_param->vcl_hrd_parameters.dpb_output_delay_length;
      }
    }
    if (p_vui_param->nal_hrd_parameters_present_flag ||
        p_vui_param->vcl_hrd_parameters_present_flag) {
      /* cpb_removal_delay */
      tmp = h264bsdShowBits(stream, cpb_removal_len);
      if (h264bsdFlushBits(stream, cpb_removal_len) == END_OF_STREAM)
        return (END_OF_STREAM);
      pic_param->cpb_removal_delay = tmp;
      /* dpb_output_delay */
      tmp = h264bsdShowBits(stream, dpb_output_len);
      if (h264bsdFlushBits(stream, dpb_output_len) == END_OF_STREAM)
        return (END_OF_STREAM);
      pic_param->dpb_output_delay = tmp;
    }
  }

  if (!sps[sps_id]->vui_parameters_present_flag)
    pic_struct_present_flag = 0;
  else
    pic_struct_present_flag = p_vui_param->pic_struct_present_flag;

  if (pic_struct_present_flag) {
    /* pic_struct */
    tmp = h264bsdGetBits(stream, 4);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 8) return HANTRO_NOK;
    pic_param->pic_struct = tmp;

    switch (pic_param->pic_struct) {
    case 0:
    case 1:
    case 2:
      NumClockTs = 1;
      break;

    case 3:
    case 4:
    case 7:
      NumClockTs = 2;
      break;

    case 5:
    case 6:
    case 8:
      NumClockTs = 3;
      break;
    default:
      break;
    }

    for (i = 0; i < NumClockTs; i++) {
      /* clock_timestamp_flag[i] */
      tmp = h264bsdGetBits(stream, 1);
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      pic_param->clock_timestamp_flag[i] = tmp;

      if (pic_param->clock_timestamp_flag[i]) {
        /* ct_type */
        tmp = h264bsdGetBits(stream, 2);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        if (tmp > 2) return HANTRO_NOK;
        pic_param->ct_type = tmp;

        /* nuit_field_based_flag */
        tmp = h264bsdGetBits(stream, 1);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        pic_param->nuit_field_based_flag = tmp;

        /* counting_type */
        tmp = h264bsdGetBits(stream, 5);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        if (tmp > 6) return HANTRO_NOK;
        pic_param->counting_type = tmp;

        /* full_timestamp_flag */
        tmp = h264bsdGetBits(stream, 1);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        pic_param->full_timestamp_flag = tmp;

        /* discontinuity_flag */
        tmp = h264bsdGetBits(stream, 1);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        pic_param->discontinuity_flag = tmp;

        /* cnt_dropped_flag */
        tmp = h264bsdGetBits(stream, 1);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        pic_param->cnt_dropped_flag = tmp;

        /* n_frames */
        tmp = h264bsdGetBits(stream, 8);
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        pic_param->n_frames = tmp;

        if (pic_param->full_timestamp_flag) {
          /* seconds_value */
          tmp = h264bsdGetBits(stream, 6);
          if (tmp == END_OF_STREAM) return (END_OF_STREAM);
          if (tmp > 59) return HANTRO_NOK;
          pic_param->seconds_value = tmp;

          /* minutes_value */
          tmp = h264bsdGetBits(stream, 6);
          if (tmp == END_OF_STREAM) return (END_OF_STREAM);
          if (tmp > 59) return HANTRO_NOK;
          pic_param->minutes_value = tmp;

          /* hours_value */
          tmp = h264bsdGetBits(stream, 5);
          if (tmp == END_OF_STREAM) return (END_OF_STREAM);
          if (tmp > 23) return HANTRO_NOK;
          pic_param->hours_value = tmp;
        } else {
          /* seconds_flag */
          tmp = h264bsdGetBits(stream, 1);
          if (tmp == END_OF_STREAM) return (END_OF_STREAM);
          pic_param->seconds_flag = tmp;

          if (pic_param->seconds_flag) {
            /* seconds_value */
            tmp = h264bsdGetBits(stream, 6);
            if (tmp == END_OF_STREAM) return (END_OF_STREAM);
            if (tmp > 59) return HANTRO_NOK;
            pic_param->seconds_value = tmp;

            /* minutes_flag */
            tmp = h264bsdGetBits(stream, 1);
            if (tmp == END_OF_STREAM)
              return (END_OF_STREAM);
            pic_param->minutes_flag = tmp;

            if (pic_param->minutes_flag) {
              /* minutes_value */
              tmp = h264bsdGetBits(stream, 6);
              if (tmp == END_OF_STREAM) return (END_OF_STREAM);
              if (tmp > 59) return HANTRO_NOK;
              pic_param->minutes_value = tmp;

              /* hours_flag */
              tmp = h264bsdGetBits(stream, 1);
              if (tmp == END_OF_STREAM) return (END_OF_STREAM);
              pic_param->hours_flag = tmp;

              if (pic_param->hours_flag) {
                /* hours_value */
                tmp = h264bsdGetBits(stream, 5);
                if (tmp == END_OF_STREAM) return (END_OF_STREAM);
                if (tmp > 23) return HANTRO_NOK;
                pic_param->hours_value = tmp;
              }
            }
          }
        }

        if (p_vui_param->vcl_hrd_parameters_present_flag) {
          time_offset_length =
              p_vui_param->vcl_hrd_parameters.time_offset_length;
        } else if (p_vui_param->nal_hrd_parameters_present_flag) {
          time_offset_length =
              p_vui_param->nal_hrd_parameters.time_offset_length;
        } else
          time_offset_length = 24;

        if (time_offset_length) {
          tmp = h264bsdGetBits(stream, 5);
          if (tmp == END_OF_STREAM) return (END_OF_STREAM);
          pic_param->time_offset = (i32)tmp;
        } else
          pic_param->time_offset = 0;
      }
    }
  }
  return (HANTRO_OK);
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 4.
 * @param[in]    stream             input stream
 * @param[in]    t35_param  T35Parameters of SEI
 * @param[in]    pay_load_size      pay_load_size
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : invalid input stream data
 *                                  -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodeUserDataRegisteredInfo(strmData_t *stream,
                                               struct T35Parameters *t35_param,
                                               u32 pay_load_size) {
  u32 i, tmp, size;
  u8 *buffer;
  struct DecSEIBuffer *payload_byte;
  struct T35Parameters *param;

  if (stream == NULL || t35_param == NULL)
    return HANTRO_NOK;

  i = 0, tmp = 0;
  buffer = NULL;
  param = t35_param;
  payload_byte = &param->payload_byte;

  /* check buffer */
  if (payload_byte->buffer == NULL) { /* first decode this SEI in one frame */
    buffer = (u8*)DWLmalloc(pay_load_size << 2);
    if (buffer == NULL) return (HANTRO_NOK);
    DWLmemset(buffer, 0, pay_load_size << 2);
    payload_byte->buffer = buffer;
    payload_byte->buffer_size = pay_load_size << 2;
    payload_byte->available_size = 0;
  } else { /* second decode this SEI in one frame */
    if ((payload_byte->buffer_size - payload_byte->available_size) < pay_load_size) {
      /* don't have enough buffer, and reallocate buffer to quadruple capacity */
      size = payload_byte->buffer_size + (pay_load_size << 2);
      buffer = (u8*)DWLmalloc(size);
      if (buffer == NULL) return (HANTRO_NOK);
      DWLmemset(buffer, 0, size);
      DWLmemcpy(buffer, payload_byte->buffer, payload_byte->available_size);
      DWLfree(payload_byte->buffer);
      payload_byte->buffer = buffer;
      payload_byte->buffer_size = size;
    }
  }

  /* itu_t_t35_country_code */
  tmp = h264bsdShowBits(stream, 8);
  if (h264bsdFlushBits(stream, 8) == END_OF_STREAM) return(END_OF_STREAM);
  if (tmp > 0xFF) return HANTRO_NOK;
  *(param->itu_t_t35_country_code + param->counter) = tmp;

  /* itu_t_t35_country_code_extension_byte */
  if (tmp != 0xFF) {
    i = 1;
  } else { /* tmp == 0xFF */
    tmp = h264bsdShowBits(stream, 8);
    if (h264bsdFlushBits(stream, 8) == END_OF_STREAM)
      return(END_OF_STREAM);
    if (tmp > 0xFF) return HANTRO_NOK;
    *(param->itu_t_t35_country_code_extension_byte + param->counter) = tmp;
    i = 2;
  }

  if (pay_load_size < i) return HANTRO_NOK;

  /* itu_t_t35_payload_byte : struct DecSEIBuffer */
  do {
    tmp = h264bsdShowBits(stream, 8);
    if (h264bsdFlushBits(stream, 8) == END_OF_STREAM)
      return (END_OF_STREAM);
    if (tmp > 0xFF) return HANTRO_NOK;
    *(payload_byte->buffer + payload_byte->available_size) = tmp;
    i++;

    payload_byte->available_size++;
    (*(param->payload_byte_length + param->counter))++;
  } while (i < pay_load_size);

  /* counter : in one frame */
  param->counter++;
  RESET_SEI_COUNTER(&param->counter);

  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 5.
 * @param[in]    stream               input stream
 * @param[in]    userdataunreg_param  H264UserDataUnRegParameters of SEI
 * @param[in]    pay_load_size        pay_load_size
 * @param[out]   u32                  return value :
 *                                    -HANTRO_OK : SEI parser successful
 *                                    -HANTRO_NOK : invalid input stream data
 *                                    -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodeUserDataUnRegisteredInfo(strmData_t *stream,
                                               struct H264UserDataUnRegParameters *userdataunreg_param,
                                               u32 pay_load_size) {
  u32 i, tmp, size;
  u8 *buffer;
  struct DecSEIBuffer *payload_byte;
  struct H264UserDataUnRegParameters *param;

  if (stream == NULL || userdataunreg_param == NULL) return HANTRO_NOK;
  if (pay_load_size < 16 || pay_load_size > INI_MAX) return HANTRO_NOK;

  i = 0, tmp = 0;
  buffer = NULL;
  param = userdataunreg_param;
  payload_byte = &param->payload_byte;

  /* check buffer */
  if (payload_byte->buffer == NULL) { /* first decode this SEI in one frame */
    buffer = (u8*)DWLmalloc(pay_load_size << 2);
    if (buffer == NULL) return (HANTRO_NOK);
    DWLmemset(buffer, 0, pay_load_size << 2);
    payload_byte->buffer = buffer;
    payload_byte->buffer_size = pay_load_size << 2;
    payload_byte->available_size = 0;
  } else { /* second decode this SEI in one frame */
    if ((payload_byte->buffer_size - payload_byte->available_size) < pay_load_size) {
      /* don't have enough buffer, and reallocate buffer to quadruple capacity */
      size = payload_byte->buffer_size + (pay_load_size << 2);
      buffer = (u8*)DWLmalloc(size);
      if (buffer == NULL) return (HANTRO_NOK);
      DWLmemset(buffer, 0, size);
      DWLmemcpy(buffer, payload_byte->buffer, payload_byte->available_size);
      DWLfree(payload_byte->buffer);
      payload_byte->buffer = buffer;
      payload_byte->buffer_size = size;
    }
  }

  /* uuid_iso_iec_11578 */
  for (i = 0; i < 16; i++) {
    tmp = h264bsdGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 0xFF) return HANTRO_NOK;
    param->uuid_iso_iec_11578[param->userdataunreg_counter][i] = tmp;
  }

  /* itu_t_t35_payload_byte : struct DecSEIBuffer */
  for (i = 16; i < pay_load_size; i++) {
    tmp = h264bsdShowBits(stream, 8);
    if (h264bsdGetBits(stream, 8) == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 0xFF) return HANTRO_NOK;
    *(payload_byte->buffer + payload_byte->available_size) = tmp;

    payload_byte->available_size++;
    (*(param->payload_byte_length + param->userdataunreg_counter))++;
  }

  /* userdataunreg_counter : in one frame */
  param->userdataunreg_counter++;
  RESET_SEI_COUNTER(&param->userdataunreg_counter);

  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 6.
 * @param[in]    stream             input stream
 * @param[in]    buf_param          H264BufPeriodParameters of SEI
 * @param[in]    recovery_param     H264RecoveryPointParameters of SEI
 * @param[in]    sps                sequence parameter set
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : invalid input stream data
 *                                  -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodeRecoveryPointInfo(strmData_t *stream,
                                          struct H264BufPeriodParameters *buf_param,
                                          struct H264RecoveryPointParameters *recovery_param,
                                          seqParamSet_t **sps) {
  u32 tmp, sps_id, value;

  sps_id = buf_param->seq_parameter_set_id;
  if (sps[sps_id] == NULL) return HANTRO_NOK;
  if (!sps[sps_id]->max_pic_order_cnt_lsb) return HANTRO_NOK;

  /* recovery_frame_cnt */
  tmp = h264bsdDecodeExpGolombUnsigned(stream, &value);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (tmp > 65535) return HANTRO_NOK;
  recovery_param->recovery_frame_cnt = value;

  /* exact_match_flag */
  tmp = h264bsdGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  recovery_param->exact_match_flag = tmp;

  /* broken_link_flag */
  tmp = h264bsdGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  recovery_param->broken_link_flag = tmp;

  /* changing_slice_group_idc */
  tmp = h264bsdGetBits(stream, 2);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (tmp > 2) return HANTRO_NOK;
  recovery_param->changing_slice_group_idc = tmp;

  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 137.
 * @param[in]    stream             input stream
 * @param[in]    masterdis_param    MasterDisplayParameters of SEI
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : invalid input stream data
 *                                  -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodeMasteringDispalyInfo(strmData_t *stream,
                                             struct MasterDisplayParameters *masterdis_param) {
  u32 tmp;

  if (stream == NULL || masterdis_param == NULL) return HANTRO_NOK;

  /* display_primaries */
  for (int i = 0; i < 3; i++) {
    tmp = h264bsdGetBits(stream, 16);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 50000) return HANTRO_NOK;
    masterdis_param->display_primaries_x[i] = tmp;
    tmp = h264bsdGetBits(stream, 16);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 50000) return HANTRO_NOK;
    masterdis_param->display_primaries_y[i] = tmp;
  }

  /* white_point */
  tmp = h264bsdGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (tmp > 50000) return HANTRO_NOK;
  masterdis_param->white_point_x = tmp;
  tmp = h264bsdGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (tmp > 50000) return HANTRO_NOK;
  masterdis_param->white_point_y = tmp;

  /* max and min display_mastering_luminance */
  tmp = h264bsdShowBits(stream, 32);
  if (h264bsdFlushBits(stream, 32) == END_OF_STREAM)
    return(END_OF_STREAM);
  if (tmp < 1) return HANTRO_NOK;
  masterdis_param->max_display_mastering_luminance = tmp;
  tmp = h264bsdShowBits(stream, 32);
  if (h264bsdFlushBits(stream, 32) == END_OF_STREAM)
    return(END_OF_STREAM);
  if (tmp > masterdis_param->max_display_mastering_luminance - 1)
    return HANTRO_NOK;
  masterdis_param->min_display_mastering_luminance = tmp;

  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 144.
 * @param[in]    stream             input stream
 * @param[in]    light_param        LightLevelParameters of SEI
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : invalid input stream data
 *                                  -END_OF_STREAM : end of stream
*/
static u32 h264bsdDecodeContenLightLevelInfo(strmData_t *stream,
                                    struct LightLevelParameters *light_param) {
  u32 tmp;

  if (stream == NULL || light_param == NULL) return HANTRO_NOK;

  /* max_content_light_level */
  tmp = h264bsdGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  light_param->max_content_light_level = tmp;

  /* max_pic_average_light_level */
  tmp = h264bsdGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  light_param->max_pic_average_light_level = tmp;

  return HANTRO_OK;
}


/**@brief Select an available SEI parameters buffer(H264).
 * @param[in]    sei_param          the sei_param array(sei_param[MAX_FRAME_BUFFER_NUMBER])
 * @param[in]    sei_param_curr     the current sei_param in sei_param array
 * @param[in]    sei_param_num      the effective number of sei_param in sei_param array
 * @param[in]    pic_id             the current picture decode id
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : sei_param allocate successful
 *                                  -HANTRO_NOK : sei_param allocate unsuccessful
*/
u32 H264bsdPrepareCurrentSEIParameters(struct H264SEIParameters **sei_param,
                                       struct H264SEIParameters **sei_param_curr,
                                       u32 sei_param_num, u32 pic_id) {
  u32 i;

  if (sei_param_num == 0 || (*sei_param_curr) == NULL)
    return HANTRO_NOK;

  if ((*sei_param_curr)->decode_id != pic_id) {
    for (i = 0; i < sei_param_num; i++) {
      if (sei_param[i]->sei_status == SEI_UNUSED) {
        (*sei_param_curr) = sei_param[i];
        (*sei_param_curr)->sei_status = SEI_CURRENT;
        STREAMTRACE_I("SEI : select sei_param[%d]. \n", i);
        return HANTRO_OK;
      }
    }
    if (i == sei_param_num) return HANTRO_NOK;
  }

  return HANTRO_OK;
}


/**@brief Allocate SEI parameters buffer(H264).
 * @param[in]    sei_param          the sei_param array(sei_param[MAX_FRAME_BUFFER_NUMBER])
 * @param[in]    sei_param_curr     the current sei_param in sei_param array
 * @param[in]    sei_param_num      the effective number of sei_param in sei_param array
 * @param[in]    ext_buffer_num     the pp buffer num
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : sei_param allocate successful
 *                                  -HANTRO_NOK : sei_param allocate unsuccessful
*/
u32 H264bsdAllocateSEIParameters(struct H264SEIParameters **sei_param,
                                 struct H264SEIParameters **sei_param_curr,
                                 u32 *sei_param_num, u32 ext_buffer_num) {

  if (*sei_param_num < ext_buffer_num || *sei_param_num < (MAX_DPB_SIZE + MAX_DPB_SIZE + 1 + 1)) {
    sei_param[*sei_param_num] =
      (struct H264SEIParameters*)DWLmalloc(sizeof(struct H264SEIParameters));
    if (sei_param[*sei_param_num] == NULL) {
      STREAMTRACE_E("%s","SEI : Memory allocation failed.\n ");
      return HANTRO_NOK;
    }
    DWLmemset(sei_param[*sei_param_num], 0, sizeof(struct H264SEIParameters));

    /* this is a new sei_param, used it */
    (*sei_param_curr) = sei_param[*sei_param_num];
    (*sei_param_curr)->sei_status = SEI_CURRENT;
    STREAMTRACE_I("SEI : select sei_param[%d], which is a new sei_param. \n", *sei_param_num);
    (*sei_param_num)++;
      return HANTRO_OK;
  }

  STREAMTRACE_E("%s","SEI : No SEI_param is available.\n ");
  return HANTRO_NOK;
}


/**@brief Reset SEI parameters buffer(264). \n
 * Clear the original data in sei_param.
 * @param[in]    sei_param_curr     the current sei_param in sei_param array
 * @param[in]    sei_param_num      the effective number of sei_param in sei_param array
 * @param[in]    pic_id             the current picture decode id
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : sei_param allocate successful
 *                                  -HANTRO_NOK : sei_param allocate unsuccessful
*/
u32 H264bsdResetSEIParameters(struct H264SEIParameters *sei_param_curr,
                              u32 sei_param_num, u32 pic_id) {
  u32 sei_status;
  struct DecSEIBuffer payload_reg;
  struct DecSEIBuffer payload_unreg;

  if (sei_param_num == 0 || sei_param_curr == NULL)
    return HANTRO_NOK;

  if (sei_param_curr->decode_id != pic_id) {
    payload_reg = sei_param_curr->t35_param.payload_byte;
    payload_unreg = sei_param_curr->userdataunreg_param.payload_byte;
    sei_status    = sei_param_curr->sei_status;
    DWLmemset(sei_param_curr, 0, sizeof(struct H264SEIParameters));
    if (payload_reg.buffer != NULL) {
      DWLmemset(payload_reg.buffer, 0, payload_reg.available_size);
      payload_reg.available_size = 0;
    }
    if (payload_unreg.buffer != NULL) {
      DWLmemset(payload_unreg.buffer, 0, payload_unreg.available_size);
      payload_unreg.available_size = 0;
    }
    sei_param_curr->t35_param.payload_byte = payload_reg;
    sei_param_curr->userdataunreg_param.payload_byte = payload_unreg;
    sei_param_curr->sei_status = sei_status;
    sei_param_curr->decode_id = pic_id;
  }

  return HANTRO_OK;
}


/**@brief Decode SEI parameters(H264). \n
 * Decode SEI parameters from the stream. See standard for details.
 * @param[in]    stream             input stream
 * @param[in]    sei_param          decoded SEI information is stored here(current sei_param)
 * @param[in]    sps                sequence parameter set
 * @param[in]    decode_id          current picture decode id
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
u32 h264bsdDecodeSeiParameters(strmData_t *stream,
                               struct H264SEIParameters *sei_param,
                               seqParamSet_t **sps, u32 decode_id) {
  u32 tmp;
  u32 pay_load_type = 0;
  u32 pay_load_size = 0;
  u32 last_pay_load_type_byte;
  u32 last_pay_load_size_byte;
  strmData_t tmpstream;
  u32 count;

  ASSERT(stream);

  if (sei_param == NULL || sps == NULL) return HANTRO_NOK;

  do {
    /* pay_load_type */
    pay_load_type = 0;
    while (h264bsdShowBits(stream, 8) == 0xFF) {
      pay_load_type += 255;
      if (h264bsdFlushBits(stream, 8) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
    tmp = h264bsdGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    last_pay_load_type_byte = tmp;
    pay_load_type += last_pay_load_type_byte;

    /* pay_load_size */
    pay_load_size = 0;
    while (h264bsdShowBits(stream, 8) == 0xFF) {
      pay_load_size += 255;
      if (h264bsdFlushBits(stream, 8) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
    tmp = h264bsdGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    last_pay_load_size_byte = tmp;
    pay_load_size += last_pay_load_size_byte;

    tmpstream = *stream;
    switch (pay_load_type) {
    case SEI_BUFFERING_PERIOD:
      tmp = h264bsdDecodeBufferingPeriodInfo(&tmpstream, &sei_param->buf_param, sps);
      if (tmp != HANTRO_OK) {
        sei_param->bufperiod_present_flag = 0;
        STREAMTRACE_E("SEI : buf_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->bufperiod_present_flag = 1;
        STREAMTRACE_I("SEI : buf_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_PIC_TIMING:
      tmp = h264bsdDecodePicTimingInfo(&tmpstream,
                                       &sei_param->buf_param,
                                       &sei_param->pic_param, sps);
      if (tmp != HANTRO_OK) {
        sei_param->pictiming_present_flag = 0;
        STREAMTRACE_E("SEI : pic_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->pictiming_present_flag = 1;
        STREAMTRACE_I("SEI : pic_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_PAN_SCAN_RECT:
      break;

    case SEI_FILLER_PAYLOAD:
      break;

    case SEI_USER_DATA_REGISTERED_ITU_T_T35:
      tmp = h264bsdDecodeUserDataRegisteredInfo(&tmpstream,
                                                &sei_param->t35_param,
                                                pay_load_size);
      if (tmp != HANTRO_OK) {
        sei_param->t35_present_flag = 0;
        STREAMTRACE_E("SEI : userdatareg_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->t35_present_flag = 1;
        STREAMTRACE_I("SEI : userdatareg_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_USER_DATA_UNREGISTERED:
      tmp = h264bsdDecodeUserDataUnRegisteredInfo(&tmpstream,
                                                  &sei_param->userdataunreg_param,
                                                  pay_load_size);
      if (tmp != HANTRO_OK) {
        sei_param->userdata_unreg_present_flag = 0;
        STREAMTRACE_E("SEI : userdataunreg_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->userdata_unreg_present_flag = 1;
        STREAMTRACE_I("SEI : userdataunreg_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_RECOVERY_POINT:
      tmp = h264bsdDecodeRecoveryPointInfo(&tmpstream,
                                           &sei_param->buf_param,
                                           &sei_param->recovery_param,
                                           sps);
      if (tmp != HANTRO_OK) {
        sei_param->recovery_point_present_flag = 0;
        STREAMTRACE_E("SEI : recovery_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->recovery_point_present_flag = 1;
        STREAMTRACE_I("SEI : recovery_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_DEC_REF_PIC_MARKING_REPETITION:
      break;

    case SEI_SPARE_PIC:
      break;

    case SEI_SCENE_INFO:
      break;

    case SEI_SUB_SEQ_INFO:
      break;

    case SEI_SUB_SEQ_LAYER_CHARACTERISTICS:
      break;

    case SEI_SUB_SEQ_CHARACTERISTICS:
      break;

    case SEI_FULL_FRAME_FREEZE:
      break;

    case SEI_FULL_FRAME_FREEZE_RELEASE:
      break;

    case SEI_FULL_FRAME_SNAPSHOT:
      break;

    case SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START:
      break;

    case SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END:
      break;

    case SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET:
      break;

    case SEI_FILM_GRAIN_CHARACTERISTICS:
      break;

    case SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE:
      break;

    case SEI_STEREO_VIDEO_INFO:
      break;

    case SEI_TONE_MAPPING:
      break;

    case SEI_POST_FILTER_HINTS:
      break;

    case SEI_FRAME_PACKING_ARRANGEMENT:
      break;

    case SEI_GREEN_METADATA:
      break;

    case SEI_MASTERING_DISPLAY_COLOR_VOLUME:
      tmp = h264bsdDecodeMasteringDispalyInfo(&tmpstream, &sei_param->masterdis_param);
      if (tmp != HANTRO_OK) {
        sei_param->mastering_display_present_flag = 0;
        STREAMTRACE_E("SEI : masterdis_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->mastering_display_present_flag = 1;
        STREAMTRACE_I("SEI : masterdis_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_CONTENT_LIGHT_LEVEL_INFO:
      tmp = h264bsdDecodeContenLightLevelInfo(&tmpstream, &sei_param->light_param);
      if (tmp != HANTRO_OK) {
        sei_param->lightlevel_present_flag = 0;
        STREAMTRACE_E("SEI : light_param(type = %d) decode failed \n", pay_load_type);
      } else {
        sei_param->lightlevel_present_flag = 1;
        STREAMTRACE_I("SEI : light_param(type = %d) decode successful \n", pay_load_type);
      }
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      break;

    case SEI_ALTERNATIVE_TRANSFER_CHARACTERISTICS:
      break;

    default:
      break;
    }
#if 1
    /* Flush byte by byte Here */
    count = 0;
    while (count + 32 <= 8 * pay_load_size) {
      count += 32;
      if (h264bsdFlushBits(stream, 32) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
    if (8 * pay_load_size - count > 0) {
      if (h264bsdFlushBits(stream, 8 * pay_load_size - count) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
#else
    if (h264bsdFlushBits(stream, pay_load_size * 8) == END_OF_STREAM)
      return (END_OF_STREAM);
#endif
  } while (h264bsdMoreRbspData(stream));
  return (HANTRO_OK);
}

/**
 * Get SEI Stream data(H264)
 *
 * @brief Get SEI stream data and put it into SEI_buffer.
 *
 * @param[in, out] sei_buffer  Point to memory, where the captured SEI
 *                             header and payload will be stored.
 * @param[in] stream           input stream, the SEI will be captured from here.
 *
 * @return Unsigned integer of value
 *                                   HANTRO_OK for capture success;
 *                                   HANTRO_NOK for capture failed;
 *                                   END_OF_STREAM for not enough input stream.
 *
 * @note This function only captures SEI data and does not parser SEI data.
 */
u32 h264bsdGetSEIStreamDatas(strmData_t *stream,
                             struct SEI_buffer *sei_buffer) {
  u32 tmp;
  u32 pay_load_type = 0;
  u32 pay_load_size = 0;
  u32 count = 0;
  struct SEI_header *sei_header =
    (struct SEI_header *)(sei_buffer->buffer + sei_buffer->available_size);

  ASSERT(stream);

  do {
    /* parse pay_load_type */
    pay_load_type = 0;
    while (h264bsdShowBits(stream, 8) == 0xFF) {
      pay_load_type += 255;
      if (h264bsdFlushBits(stream, 8) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
    tmp = h264bsdGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    pay_load_type += tmp;
    /* find intrested SEI in bitmask: see if bit pay_load_type of bitmask is 1 ?
     * Find the (pay_load_type % 8) bit of the array sei_buffer->bitmask[pay_load_type / 8]
     * Note:
     *      pay_load_type >> 3 == pay_load_type / 8
     *      pay_load_type & 7 == pay_load_type % 8
     */
    tmp = (u8)(*(sei_buffer->bitmask + (pay_load_type >> 3)) >> (pay_load_type & 7));
    if (0 == (tmp & 0x01)) return (HANTRO_NOK);

    /* parse pay_load_size */
    pay_load_size = 0;
    while (h264bsdShowBits(stream, 8) == 0xFF) {
      pay_load_size += 255;
      if (h264bsdFlushBits(stream, 8) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
    tmp = h264bsdGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    pay_load_size += tmp;


    /* store SEI count in sei_buffer */
    /* SEI count fixed, it is saved at buffer[0] */
    *(sei_buffer->buffer + 0) += 1;
    /* Discarded: The remaining buffer is less than one_header bytes */
    if (sei_buffer->available_size + sizeof(struct SEI_header) > sei_buffer->total_size)
      return (HANTRO_NOK);
    /* Discarded: only 2 Bytes to store the number of pay_load_size */
    if (pay_load_size >= 65536) return (HANTRO_NOK);

    /* store SEI pay_load_type in sei_buffer */
    /* normal/zero-size/dropped: the buffer can write at least one more header */
    sei_buffer->available_size += sizeof(struct SEI_header);
    sei_header->type = (u8)pay_load_type;

    /* store SEI pay_load_size in sei_buffer(2 Bytes) */
    sei_header->size = (u16)pay_load_size;

    /* store SEI status in sei_buffer */
    /*
     * status : Normal/Zero-size == 1 and Dropped == 0
     * Dose the rest of SEI buffer hold the payload ?
     */
    sei_header->status = ((sei_buffer->available_size + pay_load_size) >
                           sei_buffer->total_size) ? 0 : 1;


    /* store SEI payload in sei_buffer */
    /* payload : copy data to SEI buffer. And tmp is the status */
    if (sei_header->status == 1) {
      /* Normal, Zero-size */
      DWLmemcpy(sei_buffer->buffer + sei_buffer->available_size, stream->strm_curr_pos, pay_load_size);
      sei_buffer->available_size += pay_load_size;
    } else {
      /* Dropped: do nothing */
    }


    /* Flush byte by byte Here */
    count = 0;
    while (count + 32 <= 8 * pay_load_size) {
      count += 32;
      if (h264bsdFlushBits(stream, 32) == END_OF_STREAM)
        return (END_OF_STREAM);
    }
    if (8 * pay_load_size - count > 0) {
      if (h264bsdFlushBits(stream, 8 * pay_load_size - count) == END_OF_STREAM)
        return (END_OF_STREAM);
    }

  } while (h264bsdMoreRbspData(stream));
  return (HANTRO_OK);
}

void H264UpdateSeiInfo(struct SEI_buffer *sei_buffer, struct H264SEIParameters *sei_param_curr) {
  if (sei_buffer && sei_buffer->buffer)
    sei_buffer->available_size -= (*sei_buffer->buffer) * sizeof(struct SEI_header);

#ifdef SUPPORT_SEI
  if (sei_param_curr) {
    u32 tmp_pic_id = sei_param_curr->decode_id;
    enum DecSEIStatus tmp_status = sei_param_curr->sei_status;
    DWLmemset(sei_param_curr, 0, sizeof(struct H264SEIParameters));
    sei_param_curr->decode_id = tmp_pic_id;
    sei_param_curr->sei_status = tmp_status;
  }
#endif
}