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

#ifndef H264HWD_SEI_H
#define H264HWD_SEI_H

#include "basetype.h"
#include "h264hwd_seq_param_set.h"
#include "h264hwd_stream.h"
#include "dectypes.h" /* SEI buffer */
#include "decsei.h" /* sei_param */

/**
 * \enum H264SEIType
 * \brief SEI types of HEVC and corresponding num.
 * \ingroup h264_group
 */
enum H264SEIType {
  SEI_BUFFERING_PERIOD = 0,
  SEI_PIC_TIMING = 1,
  SEI_PAN_SCAN_RECT = 2,
  SEI_FILLER_PAYLOAD = 3,
  SEI_USER_DATA_REGISTERED_ITU_T_T35 = 4,
  SEI_USER_DATA_UNREGISTERED = 5,
  SEI_RECOVERY_POINT = 6,
  SEI_DEC_REF_PIC_MARKING_REPETITION = 7,
  SEI_SPARE_PIC = 8,
  SEI_SCENE_INFO = 9,
  SEI_SUB_SEQ_INFO = 10,
  SEI_SUB_SEQ_LAYER_CHARACTERISTICS = 11,
  SEI_SUB_SEQ_CHARACTERISTICS = 12,
  SEI_FULL_FRAME_FREEZE = 13,
  SEI_FULL_FRAME_FREEZE_RELEASE = 14,
  SEI_FULL_FRAME_SNAPSHOT = 15,
  SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START = 16,
  SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END = 17,
  SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET = 18,
  SEI_FILM_GRAIN_CHARACTERISTICS = 19,
  SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE = 20,
  SEI_STEREO_VIDEO_INFO = 21,
  SEI_POST_FILTER_HINTS = 22,
  SEI_TONE_MAPPING = 23,
  SEI_SCALABILITY_INFO = 24,
  SEI_SUB_PIC_SCALABLE_LAYER = 25,
  SEI_NON_REQUIRED_LAYER_REP = 26,
  SEI_PRIORITY_LAYER_INFO = 27,
  SEI_LAYERS_NOT_PRESENT = 28,
  SEI_LAYER_DEPENDENCY_CHANGE = 29,
  SEI_SCALABLE_NESTING = 30,
  SEI_BASE_LAYER_TEMPORAL_HRD = 31,
  SEI_QUALITY_LAYER_INTEGRITY_CHECK = 32,
  SEI_REDUNDANT_PIC_PROPERTY = 33,
  SEI_TL0_DEP_REP_INDEX = 34,
  SEI_TL_SWITCHING_POINT = 35,
  SEI_PARALLEL_DECODING_INFO = 36,
  SEI_MVC_SCALABLE_NESTING = 37,
  SEI_VIEW_SCALABILITY_INFO = 38,
  SEI_MULTIVIEW_SCENE_INFO = 39,
  SEI_MULTIVIEW_ACQUISITION_INFO = 40,
  SEI_NON_REQUIRED_VIEW_COMPONENT = 41,
  SEI_VIEW_DEPENDENCY_CHANGE = 42,
  SEI_OPERATION_POINTS_NOT_PRESENT = 43,
  SEI_BASE_VIEW_TEMPORAL_HRD = 44,
  SEI_FRAME_PACKING_ARRANGEMENT = 45,
  SEI_GREEN_METADATA=56,
  SEI_MASTERING_DISPLAY_COLOR_VOLUME = 137,
  SEI_CONTENT_LIGHT_LEVEL_INFO  = 144,
  SEI_ALTERNATIVE_TRANSFER_CHARACTERISTICS = 147,
};

u32 H264bsdPrepareCurrentSEIParameters(struct H264SEIParameters **sei_param,
                                       struct H264SEIParameters **sei_param_curr,
                                       u32 sei_param_num, u32 pic_id);

u32 H264bsdAllocateSEIParameters(struct H264SEIParameters **sei_param,
                                 struct H264SEIParameters **sei_param_curr,
                                 u32 *sei_param_num, u32 ext_buffer_num);

u32 H264bsdResetSEIParameters(struct H264SEIParameters *sei_param_curr,
                              u32 sei_param_num, u32 pic_id);

u32 h264bsdDecodeSeiParameters(strmData_t *stream,
                               struct H264SEIParameters *sei_param,
                               seqParamSet_t **sps, u32 decode_id);

u32 h264bsdGetSEIStreamDatas(strmData_t *stream,
                             struct SEI_buffer *sei_buffer);
void H264UpdateSeiInfo(struct SEI_buffer *sei_buffer, struct H264SEIParameters *sei_param_curr);

#endif /* #ifdef H264HWD_SEI_H */
