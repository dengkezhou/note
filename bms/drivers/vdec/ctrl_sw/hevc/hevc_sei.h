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

#ifndef HEVC_SEI_H_
#define HEVC_SEI_H_

#include "basetype.h"
#include "sw_stream.h"
#include "hevc_cfg.h"
#include "hevc_seq_param_set.h"
#include "decsei.h" /* sei_param */

/**
 * \enum HevcSEIType
 * \brief SEI types of HEVC and corresponding num.
 * \ingroup hevc_group
 */
enum HevcSEIType {
  SEI_BUFFERING_PERIOD = 0,
  SEI_PIC_TIMING = 1,
  SEI_PAN_SCAN_RECT = 2,
  SEI_FILLER_PAYLOAD = 3,
  SEI_USER_DATA_REGISTERED_ITU_T_T35 = 4,
  SEI_USER_DATA_UNREGISTERED = 5,
  SEI_RECOVERY_POINT = 6,
  SEI_SCENE_INFO = 9,
  SEI_PICTURE_SNAPSHOT = 15,
  SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START = 16,
  SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END = 17,
  SEI_FILM_GRAIN_CHARACTERISTICS = 19,
  SEI_POST_FILTER_HINTS = 22,
  SEI_TONE_MAPPING_INFO = 23,
  SEI_FRAME_PACKING_ARRANGEMENT = 45,
  SEI_DISPLAY_ORIENTATION = 47,
  SEI_STRUCTURE_OF_PICTURES_INFO = 128,
  SEI_ACTIVE_PARAMETER_SETS = 129,
  SEI_DECODING_UNIT_INFO = 130,
  SEI_TEMPORAL_SUB_LAYER_ZERO_INDEX = 131,
  SEI_DECODED_PICTURE_HASH = 132,
  SEI_SCALABLE_NESTING = 133,
  SEI_REGION_REFRESH_INFO = 134,
  SEI_TIME_CODE = 136,
  SEI_MASTERING_DISPLAY_COLOR_VOLUME = 137,
  SEI_CONTENT_LIGHT_LEVEL_INFO  = 144,
  SEI_ALTERNATIVE_TRANSFER_CHARACTERISTICS = 147,
  SEI_ALPHA_CHANNEL_INFO = 165
};

u32 HevcPrepareCurrentSEIParameters(struct HevcSEIParameters **sei_param,
                                    struct HevcSEIParameters **sei_param_curr,
                                    u32 sei_param_num, u32 pic_id);

u32 HevcAllocateSEIParameters(struct HevcSEIParameters **sei_param,
                              struct HevcSEIParameters **sei_param_curr,
                              u32 *sei_param_num, u32 ext_buffer_num);

u32 HevcResetSEIParameters(struct HevcSEIParameters *sei_param_curr,
                           u32 sei_param_num, u32 pic_id);

u32 HevcDecodeSEIParameters(struct StrmData *stream, int layerid,
                            struct HevcSEIParameters *sei_params,
                            struct SeqParamSet **sps, u32 decode_id);

u32 HevcGetSEIStreamDatas(struct StrmData *stream,
                          struct SEI_buffer *sei_buffer);

void HevcUpdateSeiInfo(struct SEI_buffer *sei_buffer, struct HevcSEIParameters *sei_param_curr);

#endif /* #ifdef HEVC_SEI_H */
