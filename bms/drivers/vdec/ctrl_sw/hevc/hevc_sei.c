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
#include "hevc_vui.h"
#include "basetype.h"
#include "hevc_exp_golomb.h"
#include "hevc_nal_unit.h"
#include "hevc_util.h"
#include "sw_stream.h"
#include "sw_util.h"
#include "hevc_sei.h"
#include "dec_log.h"
#include <string.h>
#include <math.h>


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 0.
 * @param[in]    layerid            sub_layer id
 * @param[in]    stream             input stream
 * @param[in]    buf_param          HevcBufPeriodParameters of SEI
 * @param[in]    sps                sequence parameter set
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 buffering_period(int layerid, struct StrmData *stream,
                     struct HevcBufPeriodParameters *buf_param,
                     struct SeqParamSet **sps) {
  u32 tmp, i, value;
  struct VuiParameters *vui_param;
  u32 initial_cpb_len;
  u32 cpb_delay_len, dpb_delay_len;
  u32 CpbSize = 0, BitRate = 0;

  if (stream == NULL || buf_param == NULL || sps == NULL)
    return HANTRO_NOK;

  /* bp_seq_parameter_set_id */
  tmp = HevcDecodeExpGolombUnsigned(stream, &value);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (value >= MAX_NUM_SEQ_PARAM_SETS) return (HANTRO_NOK);
  if (sps[value] == NULL) return HANTRO_NOK;
  buf_param->bp_seq_parameter_set_id = value;

  if (!sps[value]->vui_parameters_present_flag ||
      !sps[value]->vui_parameters.vui_hrd_parameters_present_flag)
      return HANTRO_NOK;
  vui_param = &(sps[value]->vui_parameters);

  /* irap_cpb_params_present_flag */
  if (!vui_param->hrd_parameters.sub_pic_hrd_params_present_flag) {
    tmp = SwGetBits(stream, 1);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    buf_param->irap_cpb_params_present_flag = tmp;
  } else {
    buf_param->irap_cpb_params_present_flag = 0;
  }

  /* cpb_delay_offset and dpb_delay_offset */
  if (buf_param->irap_cpb_params_present_flag) {
    /* added one when it parse. */
    cpb_delay_len = vui_param->hrd_parameters.au_cpb_removal_delay_length;
    tmp = SwShowBits(stream, cpb_delay_len);
    if (SwFlushBits(stream, cpb_delay_len) == END_OF_STREAM)
      return(END_OF_STREAM);
    buf_param->cpb_delay_offset = tmp;

    /* added one when it parse. */
    dpb_delay_len = vui_param->hrd_parameters.dpb_output_delay_length;
    tmp = SwShowBits(stream, dpb_delay_len);
    if (SwFlushBits(stream, dpb_delay_len) == END_OF_STREAM)
      return(END_OF_STREAM);
    buf_param->dpb_delay_offset = tmp;
  } else {
    buf_param->cpb_delay_offset = 0;
    buf_param->dpb_delay_offset = 0;
  }

  /* concatenation_flag */
  tmp = SwGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  buf_param->concatenation_flag = tmp;

  /* au_cpb_removal_delay_delta */
  cpb_delay_len = vui_param->hrd_parameters.au_cpb_removal_delay_length;
  tmp = SwShowBits(stream, cpb_delay_len);
  if (SwFlushBits(stream, cpb_delay_len) == END_OF_STREAM)
    return(END_OF_STREAM);
  buf_param->au_cpb_removal_delay_delta = tmp + 1;

  if (vui_param->hrd_parameters.nal_hrd_parameters_present_flag) {
    for (i = 0; i <= vui_param->hrd_parameters.cpb_cnt[layerid]; i++) {
      if (vui_param->hrd_parameters.sub_pic_hrd_params_present_flag) {
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_du_value[i]) {
          CpbSize = vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_du_value[i] <<
                   (4 + vui_param->hrd_parameters.cpb_size_du_scale);
        }
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_du_value[i]) {
          BitRate = vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_du_value[i] <<
                 (6 + vui_param->hrd_parameters.bit_rate_scale);
        }
      } else {
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_value[i]) {
          CpbSize = vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_value[i] <<
                   (4 + vui_param->hrd_parameters.cpb_size_scale);
        }
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_value[i]) {
          BitRate = vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_value[i] <<
                 (6 + vui_param->hrd_parameters.bit_rate_scale);
        }
      }
      initial_cpb_len = vui_param->hrd_parameters.initial_cpb_removal_delay_length;

      if (CpbSize !=0 && BitRate != 0) {
        tmp = SwShowBits(stream, initial_cpb_len);
        if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
          return(END_OF_STREAM);
        if (tmp == 0 || tmp > 90000 * (CpbSize / BitRate))
          return(HANTRO_NOK);
        buf_param->nal_initial_cpb_removal_delay[i] = tmp;

        tmp = SwShowBits(stream, initial_cpb_len);
        if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
          return(END_OF_STREAM);
        buf_param->nal_initial_cpb_removal_offset[i] = tmp;

        if (vui_param->hrd_parameters.sub_pic_hrd_params_present_flag ||
            buf_param->irap_cpb_params_present_flag) {
          tmp = SwShowBits(stream, initial_cpb_len);
          if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
            return(END_OF_STREAM);
          if (tmp == 0 || tmp > 90000 * (CpbSize / BitRate))
            return(HANTRO_NOK);
          buf_param->nal_initial_alt_cpb_removal_delay[i] = tmp;

          tmp = SwShowBits(stream, initial_cpb_len);
          if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
            return(END_OF_STREAM);
          buf_param->nal_initial_alt_cpb_removal_offset[i] = tmp;
        }
      }
    }
  }

  if (vui_param->hrd_parameters.vcl_hrd_parameters_present_flag) {
    for (i=0; i<=vui_param->hrd_parameters.cpb_cnt[layerid]; i++) {
      if (vui_param->hrd_parameters.sub_pic_hrd_params_present_flag) {
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_du_value[i]) {
          CpbSize = vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_du_value[i] <<
                   (4 + vui_param->hrd_parameters.cpb_size_du_scale);
        }
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_du_value[i]) {
          BitRate = vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_du_value[i] <<
                 (6 + vui_param->hrd_parameters.bit_rate_scale);
        }
      } else {
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_value[i]) {
          CpbSize = vui_param->hrd_parameters.sub_hrd_parameters[layerid].cpb_size_value[i] <<
                   (4 + vui_param->hrd_parameters.cpb_size_scale);
        }
        if (vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_value[i]) {
          BitRate = vui_param->hrd_parameters.sub_hrd_parameters[layerid].bit_rate_value[i] <<
                 (6 + vui_param->hrd_parameters.bit_rate_scale);
        }
      }
      initial_cpb_len = vui_param->hrd_parameters.initial_cpb_removal_delay_length;

      if (CpbSize !=0 && BitRate != 0) {
        tmp = SwShowBits(stream, initial_cpb_len);
        if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
          return(END_OF_STREAM);
        if (tmp == 0 || tmp > 90000 * (CpbSize / BitRate))
          return(HANTRO_NOK);
        buf_param->vcl_initial_cpb_removal_delay[i] = tmp;

        tmp = SwShowBits(stream, initial_cpb_len);
        if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
          return(END_OF_STREAM);
        buf_param->vcl_initial_cpb_removal_offset[i] = tmp;

        if (vui_param->hrd_parameters.sub_pic_hrd_params_present_flag ||
            buf_param->irap_cpb_params_present_flag) {
          tmp = SwShowBits(stream, initial_cpb_len);
          if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
            return(END_OF_STREAM);
          if (tmp == 0 || tmp > 90000 * (CpbSize / BitRate))
          return(HANTRO_NOK);
          buf_param->vcl_initial_alt_cpb_removal_delay[i] = tmp;

          tmp = SwShowBits(stream, initial_cpb_len);
          if (SwFlushBits(stream, initial_cpb_len) == END_OF_STREAM)
            return(END_OF_STREAM);
          buf_param->vcl_initial_alt_cpb_removal_offset[i] = tmp;
        }
      }
    }
  }
  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 1.
 * @param[in]    stream             input stream
 * @param[in]    buf_param          HevcBufPeriodParameters of SEI
 * @param[in]    pic_param          HevcPicTimingParameters of SEI
 * @param[in]    sps                sequence parameter set
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 pic_timing(struct StrmData *stream,
               struct HevcBufPeriodParameters *buf_param,
               struct HevcPicTimingParameters *pic_param,
               struct SeqParamSet **sps) {
  u32 tmp, value, i;
  struct VuiParameters *vui_param;
  u32 cpb_delay_len, cpb_delay_du_len, dpb_delay_len, dpb_delay_du_len;
  u32 sps_id;

  if (stream == NULL || buf_param == NULL || pic_param == NULL || sps == NULL)
    return HANTRO_NOK;

  sps_id = buf_param->bp_seq_parameter_set_id;
  if (sps[sps_id] == NULL || (!sps[sps_id]->vui_parameters_present_flag))
    return HANTRO_NOK;

  vui_param = &(sps[sps_id]->vui_parameters);
  cpb_delay_len = vui_param->hrd_parameters.au_cpb_removal_delay_length;
  cpb_delay_du_len = vui_param->hrd_parameters.du_cpb_removal_delay_increment_length;
  dpb_delay_len = vui_param->hrd_parameters.dpb_output_delay_length;
  dpb_delay_du_len = vui_param->hrd_parameters.dpb_output_delay_du_length;

  if (vui_param->frame_field_info_present_flag) {
    /* pic_struct */
    tmp = SwGetBits(stream, 4);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 12) return(HANTRO_NOK);
    pic_param->pic_struct = tmp;

    /* source_scan_type */
    tmp = SwGetBits(stream, 2);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 2) tmp = 2;
    if (sps[sps_id]->profile.progressive_source_flag == 0 &&
        sps[sps_id]->profile.interlaced_source_flag == 1)
      tmp = 0;
    if (sps[sps_id]->profile.progressive_source_flag == 1 &&
        sps[sps_id]->profile.interlaced_source_flag == 0)
      tmp = 1;
    if (sps[sps_id]->profile.progressive_source_flag == 0 &&
        sps[sps_id]->profile.interlaced_source_flag == 0)
      tmp = 2;
    pic_param->source_scan_type = tmp;

    /* duplicate_flag */
    tmp = SwGetBits(stream, 1);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    pic_param->duplicate_flage = tmp;
  } else {
    pic_param->pic_struct = 0;
    tmp = 2 - 2 * sps[sps_id]->profile.interlaced_source_flag -
                  sps[sps_id]->profile.progressive_source_flag;
    pic_param->source_scan_type = tmp;
    pic_param->duplicate_flage = 0;
  }

  if (!sps[sps_id]->vui_parameters_present_flag ||
      !sps[sps_id]->vui_parameters.vui_hrd_parameters_present_flag)
    return HANTRO_NOK;

  if (vui_param->hrd_parameters.nal_hrd_parameters_present_flag ||
      vui_param->hrd_parameters.vcl_hrd_parameters_present_flag) {
    /* au_cpb_removal_delay */
    tmp = SwShowBits(stream, cpb_delay_len);
    if (SwFlushBits(stream, cpb_delay_len) == END_OF_STREAM)
      return(END_OF_STREAM);
    pic_param->au_cpb_removal_delay = tmp + 1;

    /* pic_dpb_output_delay */
    tmp = SwShowBits(stream, dpb_delay_len);
    if (SwFlushBits(stream, dpb_delay_len) == END_OF_STREAM)
      return(END_OF_STREAM);
    pic_param->pic_dpb_output_delay = tmp;

    /* pic_dpb_output_du_delay */
    if (vui_param->hrd_parameters.sub_pic_hrd_params_present_flag) {
      tmp = SwShowBits(stream, dpb_delay_du_len);
      if (SwFlushBits(stream, dpb_delay_du_len) == END_OF_STREAM)
        return(END_OF_STREAM);
      pic_param->pic_dpb_output_du_delay = tmp;
    }

    if (vui_param->hrd_parameters.sub_pic_hrd_params_present_flag &&
        vui_param->hrd_parameters.sub_pic_cpb_params_in_pic_timing_sei_flag) {
      /* Each decoding unit must contain at least one slice segment. */
      tmp = HevcDecodeExpGolombUnsigned(stream, &value);
      if (tmp != HANTRO_OK) return(tmp);
      if (value >= MAX_SLICE_SEGMENTS) return HANTRO_NOK;
      pic_param->num_decoding_units = value + 1;

      /* du_common_cpb_removal_delay_flag */
      tmp = SwGetBits(stream, 1);
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
      pic_param->du_common_cpb_removal_delay_flag = tmp;

      /* du_common_cpb_removal_delay_increment */
      if (pic_param->du_common_cpb_removal_delay_flag) {
        tmp = SwShowBits(stream, cpb_delay_du_len);
        if (SwFlushBits(stream, cpb_delay_du_len) == END_OF_STREAM)
          return(END_OF_STREAM);
        pic_param->du_common_cpb_removal_delay_increment = tmp + 1;
      }

      for (i = 0; i <= pic_param->num_decoding_units - 1; i++) {
        /* num_nalus_in_du[i] */
        tmp = HevcDecodeExpGolombUnsigned(stream, &value);
        if (tmp != HANTRO_OK) return(tmp);
        if (value >= MAX_SLICE_SEGMENTS) return HANTRO_NOK;
        pic_param->num_nalus_in_du[i] = value + 1;

        /* du_cpb_removal_delay_increment[i] */
        if (!pic_param->du_common_cpb_removal_delay_flag &&
            i < pic_param->num_decoding_units - 1) {
          tmp = SwShowBits(stream, cpb_delay_du_len);
          if (SwFlushBits(stream, cpb_delay_du_len) == END_OF_STREAM)
            return(END_OF_STREAM);
          pic_param->du_cpb_removal_delay_increment[i] = tmp + 1;
        }
      }
    }
  }
  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 4.
 * @param[in]    stream             input stream
 * @param[in]    t35_param  T35Parameters of SEI
 * @param[in]    pay_load_size      pay_load_size
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 user_data_registered_itu_t_t35(struct StrmData *stream,
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
  tmp = SwShowBits(stream, 8);
  if (SwFlushBits(stream, 8) == END_OF_STREAM) return(END_OF_STREAM);
  if (tmp > 0xFF) return HANTRO_NOK;
  *(param->itu_t_t35_country_code + param->counter) = tmp;

  /* itu_t_t35_country_code_extension_byte */
  if (tmp != 0xFF) {
    i = 1;
  } else { /* tmp == 0xFF */
    tmp = SwShowBits(stream, 8);
    if (SwFlushBits(stream, 8) == END_OF_STREAM)
      return(END_OF_STREAM);
    if (tmp > 0xFF) return HANTRO_NOK;
    *(param->itu_t_t35_country_code_extension_byte + param->counter) = tmp;
    i = 2;
  }

  if (pay_load_size < i) return HANTRO_NOK;

  /* itu_t_t35_payload_byte : struct DecSEIBuffer */
  do {
    tmp = SwShowBits(stream, 8);
    if (SwFlushBits(stream, 8) == END_OF_STREAM)
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
 * @param[in]    userdataunreg_param  HevcUserDataUnRegParameters of SEI
 * @param[in]    pay_load_size        pay_load_size
 * @param[out]   u32                  return value :
 *                                    -HANTRO_OK : SEI parser successful
 *                                    -HANTRO_NOK : SEI parser unsuccessful
 *                                    -END_OF_STREAM : don't have enough input stream
*/
static u32 user_data_unregistered(struct StrmData *stream,
                                  struct HevcUserDataUnRegParameters *userdataunreg_param,
                                  u32 pay_load_size) {
  u32 i, tmp, size;
  u8 *buffer;
  struct DecSEIBuffer *payload_byte;
  struct HevcUserDataUnRegParameters *param;

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
    tmp = SwGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 0xFF) return HANTRO_NOK;
    param->uuid_iso_iec_11578[param->userdataunreg_counter][i] = tmp;
  }

  /* itu_t_t35_payload_byte : struct DecSEIBuffer */
  for (i = 16; i < pay_load_size; i++) {
    tmp = SwShowBits(stream, 8);
    if (SwGetBits(stream, 8) == END_OF_STREAM) return (END_OF_STREAM);
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
 * @param[in]    buf_param          HevcBufPeriodParameters of SEI
 * @param[in]    recovery_param     HevcRecoveryPointParameters of SEI
 * @param[in]    sps                sequence parameter set
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 recovery_point(struct StrmData *stream,
                          struct HevcBufPeriodParameters *buf_param,
                          struct HevcRecoveryPointParameters *recovery_param,
                          struct SeqParamSet **sps) {
  u32 tmp, sps_id;
  i32 ivalue, iMaxPicOrderCntLsb;

  if (stream == NULL || buf_param == NULL || recovery_param == NULL || sps == NULL)
    return HANTRO_NOK;

  sps_id = buf_param->bp_seq_parameter_set_id;
  if (sps[sps_id] == NULL) return HANTRO_NOK;
  if (!sps[sps_id]->max_pic_order_cnt_lsb) return HANTRO_NOK;

  /* recovery_poc_cnt */
  tmp = HevcDecodeExpGolombSigned(stream, &ivalue);
  if (tmp != HANTRO_OK)
    return(tmp);
  /* iMaxPicOrderCntLsb == 65536 ? */
  /* if (ivalue < -32768 || ivalue > 32767) */
  iMaxPicOrderCntLsb = (i32)sps[sps_id]->max_pic_order_cnt_lsb;
  if (ivalue < -iMaxPicOrderCntLsb/2 ||
      ivalue >  iMaxPicOrderCntLsb/2 - 1)
      return HANTRO_NOK;
  recovery_param->recovery_poc_cnt = ivalue;

  /* exact_match_flag */
  tmp = SwGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return(END_OF_STREAM);
  recovery_param->exact_match_flag = tmp;

  /* broken_link_flag */
  tmp = SwGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return(END_OF_STREAM);
  recovery_param->broken_link_flag = tmp;

  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 129.
 * @param[in]    stream             input stream
 * @param[in]    activeps_param     HevcActiveParameterSet of SEI
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 active_parameter_set(struct StrmData *stream,
                                struct HevcActiveParameterSet *activeps_param) {

  u32 tmp, value, i;

  if (stream == NULL || activeps_param == NULL) return(HANTRO_NOK);

  /* active_video_parameter_set_id */
  tmp = SwGetBits(stream, 4);
  if (tmp == END_OF_STREAM) return(END_OF_STREAM);
  if (tmp >= MAX_NUM_VIDEO_PARAM_SETS) return(HANTRO_NOK);
  activeps_param->active_video_parameter_set_id = tmp;

  /* self_contained_cvs_flag */
  tmp = SwGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return(END_OF_STREAM);
  activeps_param->self_contained_cvs_flag = tmp;

  /* no_parameter_set_update_flag */
  tmp = SwGetBits(stream, 1);
  if (tmp == END_OF_STREAM) return(END_OF_STREAM);
  activeps_param->no_parameter_set_update_flag = tmp;

  /* num_sps_ids */
  tmp = HevcDecodeExpGolombUnsigned(stream, &value);
  if (tmp != HANTRO_OK) return (tmp);
  if (value >= MAX_NUM_SEQ_PARAM_SETS) return(HANTRO_NOK);
  activeps_param->num_sps_ids = value + 1;

  /* active_seq_parameter_set_id[i] */
  for (i = 0; i <= activeps_param->num_sps_ids - 1; i++) {
    tmp = HevcDecodeExpGolombUnsigned(stream, &value);
    if (tmp != HANTRO_OK) return (tmp);
    if (value >= MAX_NUM_SEQ_PARAM_SETS) return(HANTRO_NOK);
    activeps_param->active_seq_parameter_set_id[i] = value;
  }

  return HANTRO_OK;
}


/**@brief SEI parser function. \n
 * pic_timing : pay_load_type == 137.
 * @param[in]    stream             input stream
 * @param[in]    masterdis_param    MasterDisplayParameters of SEI
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 mastering_display_colour_volume(struct StrmData *stream,
                                    struct MasterDisplayParameters *masterdis_param) {
  u32 tmp;

  if (stream == NULL || masterdis_param == NULL) return HANTRO_NOK;

  /* display_primaries */
  for (int i = 0; i < 3; i++) {
    tmp = SwGetBits(stream, 16);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 50000) return HANTRO_NOK;
    masterdis_param->display_primaries_x[i] = tmp;
    tmp = SwGetBits(stream, 16);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    if (tmp > 50000) return HANTRO_NOK;
    masterdis_param->display_primaries_y[i] = tmp;
  }

  /* white_point */
  tmp = SwGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (tmp > 50000) return HANTRO_NOK;
  masterdis_param->white_point_x = tmp;
  tmp = SwGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  if (tmp > 50000) return HANTRO_NOK;
  masterdis_param->white_point_y = tmp;

  /* max and min display_mastering_luminance */
  tmp = SwShowBits(stream, 32);
  if (SwFlushBits(stream, 32) == END_OF_STREAM)
    return(END_OF_STREAM);
  if (tmp < 1) return HANTRO_NOK;
  masterdis_param->max_display_mastering_luminance = tmp;
  tmp = SwShowBits(stream, 32);
  if (SwFlushBits(stream, 32) == END_OF_STREAM)
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
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
static u32 content_light_level_info(struct StrmData *stream,
                                    struct LightLevelParameters *light_param) {
  u32 tmp;

  if (stream == NULL || light_param == NULL) return HANTRO_NOK;

  /* max_content_light_level */
  tmp = SwGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  light_param->max_content_light_level = tmp;

  /* max_pic_average_light_level */
  tmp = SwGetBits(stream, 16);
  if (tmp == END_OF_STREAM) return (END_OF_STREAM);
  light_param->max_pic_average_light_level = tmp;

  return HANTRO_OK;
}


/**@brief Select an available SEI parameters buffer(HEVC).
 * @param[in]    sei_param          the sei_param array(sei_param[MAX_PIC_BUFFERS])
 * @param[in]    sei_param_curr     the current sei_param in sei_param array
 * @param[in]    sei_param_num      the effective number of sei_param in sei_param array
 * @param[in]    pic_id             the current picture decode id
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : sei_param prepare successful
 *                                  -HANTRO_NOK : sei_param prepare unsuccessful
*/
u32 HevcPrepareCurrentSEIParameters(struct HevcSEIParameters **sei_param,
                                    struct HevcSEIParameters **sei_param_curr,
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


/**@brief Allocate SEI parameters buffer(HEVC).
 * @param[in]    sei_param          the sei_param array(sei_param[MAX_PIC_BUFFERS])
 * @param[in]    sei_param_curr     the current sei_param in sei_param array
 * @param[in]    sei_param_num      the effective number of sei_param in sei_param array
 * @param[in]    ext_buffer_num     the pp buffer num
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : sei_param allocate successful
 *                                  -HANTRO_NOK : sei_param allocate unsuccessful
*/
u32 HevcAllocateSEIParameters(struct HevcSEIParameters **sei_param,
                              struct HevcSEIParameters **sei_param_curr,
                              u32 *sei_param_num, u32 ext_buffer_num) {

  if (*sei_param_num < ext_buffer_num || *sei_param_num < MAX_DPB_SIZE + 1) {
    sei_param[*sei_param_num] =
      (struct HevcSEIParameters*)DWLmalloc(sizeof(struct HevcSEIParameters));
    if (sei_param[*sei_param_num] == NULL) {
      STREAMTRACE_E("%s","SEI : Memory allocation failed.\n ");
      return HANTRO_NOK;
    }
    DWLmemset(sei_param[*sei_param_num], 0, sizeof(struct HevcSEIParameters));

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


/**@brief Reset SEI parameters buffer(HEVC). \n
 * Clear the original data in sei_param.
 * @param[in]    sei_param_curr     the current sei_param in sei_param array
 * @param[in]    sei_param_num      the effective number of sei_param in sei_param array
 * @param[in]    pic_id             the current picture decode id
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : sei_param reset successful
 *                                  -HANTRO_NOK : sei_param reset unsuccessful
*/
u32 HevcResetSEIParameters(struct HevcSEIParameters *sei_param_curr,
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
    DWLmemset(sei_param_curr, 0, sizeof(struct HevcSEIParameters));
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


/**@brief Decode SEI parameters(HEVC). \n
 * Decode SEI parameters from the stream. See standard for details.
 * @param[in]    stream             input stream
 * @param[in]    layerid            sub_layer id
 * @param[in]    sei_param          decoded SEI information is stored here(current sei_param)
 * @param[in]    sps                sequence parameter set
 * @param[in]    decode_id          current picture decode id
 * @param[out]   u32                return value :
 *                                  -HANTRO_OK : SEI parser successful
 *                                  -HANTRO_NOK : SEI parser unsuccessful
 *                                  -END_OF_STREAM : don't have enough input stream
*/
u32 HevcDecodeSEIParameters(struct StrmData *stream, int layerid,
                            struct HevcSEIParameters *sei_param,
                            struct SeqParamSet **sps, u32 decode_id) {
  u32 tmp;
  enum HevcSEIType pay_load_type = 0;
  u32 pay_load_size = 0;
  u32 count;
  struct StrmData tmpstream;

  ASSERT(stream);

  if (sei_param == NULL || sps == NULL) return HANTRO_NOK;

  do {
    /* pay_load_type */
    pay_load_type = 0;
    while (SwShowBits(stream, 8) == 0xFF) {
      pay_load_type += 255;
      tmp = SwFlushBits(stream, 8);
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    }
    tmp = SwGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    pay_load_type += tmp;

    /* pay_load_size */
    pay_load_size = 0;
    while(SwShowBits(stream, 8) == 0xFF) {
      pay_load_size += 255;
      tmp = SwFlushBits(stream, 8);
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    }
    tmp = SwGetBits(stream, 8);
    if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    pay_load_size += tmp;

    tmpstream = *stream;
    switch (pay_load_type) {
      case SEI_BUFFERING_PERIOD: {
        tmp = buffering_period(layerid, &tmpstream, &sei_param->buf_param, sps);
        if (tmp != HANTRO_OK) {
          sei_param->bufperiod_present_flag = 0;
          STREAMTRACE_E("SEI : buf_param(type = %d) decode failed \n", pay_load_type);
        } else {
          sei_param->bufperiod_present_flag = 1;
          STREAMTRACE_I("SEI : buf_param(type = %d) decode successful \n", pay_load_type);
        }
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        break;
      }
      case SEI_PIC_TIMING: {
        tmp = pic_timing(&tmpstream, &sei_param->buf_param, &sei_param->pic_param, sps);
        if (tmp != HANTRO_OK) {
          sei_param->pictiming_present_flag = 0;
          STREAMTRACE_E("SEI : pic_param(type = %d) decode failed \n", pay_load_type);
        } else {
          sei_param->pictiming_present_flag = 1;
          STREAMTRACE_I("SEI : pic_param(type = %d) decode successful \n", pay_load_type);
        }
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        break;
      }
      case SEI_PAN_SCAN_RECT:
        break;

      case SEI_FILLER_PAYLOAD:
        break;

      case SEI_USER_DATA_REGISTERED_ITU_T_T35: {
        tmp = user_data_registered_itu_t_t35(&tmpstream,
                                            &sei_param->t35_param,
                                            pay_load_size);
        if (tmp != HANTRO_OK) {
          sei_param->t35_present_flag = 0;
          STREAMTRACE_E("SEI : t35_param(type = %d) decode failed \n", pay_load_type);
        } else {
          sei_param->t35_present_flag = 1;
          STREAMTRACE_I("SEI : t35_param(type = %d) decode successful \n", pay_load_type);
        }
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        break;
      }
      case SEI_USER_DATA_UNREGISTERED: {
        tmp = user_data_unregistered(&tmpstream,
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
      }
      case SEI_RECOVERY_POINT: {
        tmp = recovery_point(&tmpstream,
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
      }
      case SEI_SCENE_INFO:
        break;

      case SEI_PICTURE_SNAPSHOT:
        break;

      case SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START:
        break;

      case SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END:
        break;

      case SEI_FILM_GRAIN_CHARACTERISTICS:
        break;

      case SEI_POST_FILTER_HINTS:
        break;

      case SEI_TONE_MAPPING_INFO:
        break;

      case SEI_FRAME_PACKING_ARRANGEMENT:
        break;

      case SEI_DISPLAY_ORIENTATION:
        break;

      case SEI_STRUCTURE_OF_PICTURES_INFO:
        break;

      case SEI_ACTIVE_PARAMETER_SETS: {
        tmp = active_parameter_set(&tmpstream, &sei_param->activeps_param);
        if (tmp != HANTRO_OK) {
          sei_param->active_ps_present_flag = 0;
          STREAMTRACE_E("SEI : activeps_param(type = %d) decode failed \n", pay_load_type);
        } else {
          sei_param->active_ps_present_flag = 1;
          STREAMTRACE_I("SEI : activeps_param(type = %d) decode successful \n", pay_load_type);
        }
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        break;
      }
      case SEI_DECODING_UNIT_INFO:
        break;

      case SEI_TEMPORAL_SUB_LAYER_ZERO_INDEX:
        break;

      case SEI_SCALABLE_NESTING:
        break;

      case SEI_REGION_REFRESH_INFO:
        break;

      case SEI_MASTERING_DISPLAY_COLOR_VOLUME: {
        tmp = mastering_display_colour_volume(&tmpstream, &sei_param->masterdis_param);
        if (tmp != HANTRO_OK) {
          sei_param->mastering_display_present_flag = 0;
          STREAMTRACE_E("SEI : masterdis_param(type = %d) decode failed \n", pay_load_type);
        } else {
          sei_param->mastering_display_present_flag = 1;
          STREAMTRACE_I("SEI : masterdis_param(type = %d) decode successful \n", pay_load_type);
        }
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        break;
      }
      case SEI_CONTENT_LIGHT_LEVEL_INFO: {
        tmp = content_light_level_info(&tmpstream, &sei_param->light_param);
        if (tmp != HANTRO_OK) {
          sei_param->lightlevel_present_flag = 0;
          STREAMTRACE_E("SEI : light_param(type = %d) decode failed \n", pay_load_type);
        } else {
          sei_param->lightlevel_present_flag = 1;
          STREAMTRACE_I("SEI : light_param(type = %d) decode successful \n", pay_load_type);
        }
        if (tmp == END_OF_STREAM) return (END_OF_STREAM);
        break;
      }
      default:
        break;
    }
#if 1
    /* Flush byte by byte Here */
    count = 0;
    while (count + 32 <= 8 * pay_load_size) {
      count += 32;
      if (SwFlushBits(stream, 32) == END_OF_STREAM)
        return(END_OF_STREAM);
    }
    if (8 * pay_load_size - count > 0) {
      if (SwFlushBits(stream, 8 * pay_load_size - count) == END_OF_STREAM)
        return(END_OF_STREAM);
    }
#else
    if (SwFlushBits(stream, 8 * pay_load_size) == END_OF_STREAM)
      return(END_OF_STREAM);
#endif
  } while(HevcMoreRbspData(stream));
  return HANTRO_OK;
}


/**
 * Get SEI Stream data(HEVC)
 *
 * @brief Get SEI stream data and put it into SEI_buffer.
 *
 * @param[in, out] sei_buffer  Point to memory, where the captured SEI
 *                             header and payload will be stored.
 * @param[in] stream           input stream, the SEI will be captured from here.
 *
 * @return Unsigned integer of value
 *                                   HANTRO_OK for capture success;
 *                                   HANTRO_NOK for capture successful;
 *                                   END_OF_STREAM for not enough input stream.
 *
 * @note This function only captures SEI data and does not parser SEI data.
 */
u32 HevcGetSEIStreamDatas(struct StrmData *stream,
                          struct SEI_buffer *sei_buffer) {
  u32 tmp;
  enum HevcSEIType pay_load_type = 0;
  u32 pay_load_size = 0;
  u32 count = 0;
  struct SEI_header *sei_header =
    (struct SEI_header *)(sei_buffer->buffer + sei_buffer->available_size);

  ASSERT(stream);

  do {
    /* parse pay_load_type */
    pay_load_type = 0;
    while (SwShowBits(stream, 8) == 0xFF) {
      pay_load_type += 255;
      tmp = SwFlushBits(stream, 8);
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    }
    tmp = SwGetBits(stream, 8);
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
    while(SwShowBits(stream, 8) == 0xFF) {
      pay_load_size += 255;
      tmp = SwFlushBits(stream, 8);
      if (tmp == END_OF_STREAM) return (END_OF_STREAM);
    }
    tmp = SwGetBits(stream, 8);
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
      if (SwFlushBits(stream, 32) == END_OF_STREAM)
        return(END_OF_STREAM);
    }
    if (8 * pay_load_size - count > 0) {
      if (SwFlushBits(stream, 8 * pay_load_size - count) == END_OF_STREAM)
        return(END_OF_STREAM);
    }

  } while(HevcMoreRbspData(stream));
  return HANTRO_OK;
}

void HevcUpdateSeiInfo(struct SEI_buffer *sei_buffer, struct HevcSEIParameters *sei_param_curr) {
  if (sei_buffer && sei_buffer->buffer)
    sei_buffer->available_size -= (*sei_buffer->buffer) * sizeof(struct SEI_header);

#ifdef SUPPORT_SEI
  if (sei_param_curr) {
    u32 tmp_pic_id = sei_param_curr->decode_id;
    enum DecSEIStatus tmp_status = sei_param_curr->sei_status;
    DWLmemset(sei_param_curr, 0, sizeof(struct HevcSEIParameters));
    sei_param_curr->decode_id = tmp_pic_id;
    sei_param_curr->sei_status = tmp_status;
  }
#endif
}