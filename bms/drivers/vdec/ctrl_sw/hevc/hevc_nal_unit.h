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

#ifndef HEVC_NAL_UNIT_H_
#define HEVC_NAL_UNIT_H_

#include "basetype.h"
#include "sw_stream.h"
#include "hevc_nal_unit_type.h"

/* macro to determine if NAL unit pointed by nal_unit contains an IDR slice */
#define IS_IDR_NAL_UNIT(nal_unit)                           \
  ((nal_unit)->nal_unit_type == NAL_CODED_SLICE_IDR_W_LP || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_IDR_N_LP)

#define IS_RAP_NAL_UNIT(nal_unit) \
  ((nal_unit)->nal_unit_type >=   \
   NAL_CODED_SLICE_BLA_W_LP&&(nal_unit)->nal_unit_type <= NAL_CODED_SLICE_CRA)

#define IS_BLA_NAL_UNIT(nal_unit)                           \
  ((nal_unit)->nal_unit_type == NAL_CODED_SLICE_BLA_W_LP || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_BLA_W_DLP || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_BLA_N_LP)

#define IS_SLICE_NAL_UNIT(nal_unit)                             \
  (/*(nal_unit)->nal_unit_type >= NAL_CODED_SLICE_TRAIL_N && */ \
   (nal_unit)->nal_unit_type <= NAL_CODED_SLICE_CRA)

/* SLNR : a sub_layer non_reference picture */
#define IS_SLNR_NAL_UNIT(nal_unit)                             \
  ((nal_unit)->nal_unit_type == NAL_CODED_SLICE_TRAIL_N || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_TSA_N || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_STSA_N || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_RADL_N || \
   (nal_unit)->nal_unit_type == NAL_CODED_SLICE_RASL_N)

struct NalUnit {
  enum NalUnitType nal_unit_type;
  u32 temporal_id;
};

u32 HevcDecodeNalUnit(struct StrmData* stream, struct NalUnit* nal_unit, u32 heif_mode);

#endif /* #ifdef HEVC_NAL_UNIT_H_ */
