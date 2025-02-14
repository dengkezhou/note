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

#ifndef HEVC_DECODER_H_
#define HEVC_DECODER_H_

#include "basetype.h"
#include "hevc_storage.h"
#include "hevc_container.h"
#include "hevc_dpb.h"

/* enumerated return values of the functions */
enum HevcResult {
  HEVC_RDY, /* some nal unit don't support, just skip. */
  HEVC_PIC_RDY,
  HEVC_HDRS_RDY,
  HEVC_SEI_PARSED,
  HEVC_PARAM_SET_PARSED,
  HEVC_BUFFER_NOT_READY,
  HEVC_NEW_ACCESS_UNIT,
  HEVC_ABORTED,
  HEVC_NO_FREE_BUFFER, /* GetFreePicBuffer() returns no free buffer. */
  HEVC_WAITING_BUFFER,

  /* error case */
  HEVC_NO_REF = -1, /* current pic don't have ref pic, need skip. */
  HEVC_SEI_ERROR = -2,
  HEVC_PARAM_SET_ERROR = -3,
  HEVC_SLICE_HDR_ERROR = -4,
  HEVC_NONREF_PIC_SKIPPED = -5, /* current pic is nonrefrence pic, unsed in skip frame mode. */
  HEVC_PB_PIC_SKIPPED = -6, /* skip P/B pic, used in intra only mode. */
  HEVC_MEMFAIL = -7,
  HEVC_REF_PICS_ERROR = -8,
  HEVC_NALUNIT_ERROR = -9,
  HEVC_AU_BOUNDARY_ERROR = -10
};

void HevcInit(struct Storage *storage, u32 no_output_reordering);
u32 HevcDecode(struct HevcDecContainer *dec_cont, const u8 *byte_strm, u32 len,
               u32 pic_id, u32 *read_bytes);
void HevcShutdown(struct Storage *storage);

const struct DpbOutPicture *HevcNextOutputPicture(struct Storage *storage);
u32 HevcTimingInfoPresent(struct Storage *storage);
u32 HevcNumUnitsInTick(struct Storage *storage);
u32 HevcTimeScale(struct Storage *storage);
u32 HevcPicWidth(struct Storage *storage);
u32 HevcPicHeight(struct Storage *storage);
u32 HevcVideoRange(struct Storage *storage);
u32 HevcMatrixCoefficients(struct Storage *storage);
u32 HevcColourPrimaries(struct Storage *storage);
u32 HevcTransferCharacteristics(struct Storage *storage, u32 *vui_trc, u32 *sei_trc);
u32 HevcIsMonoChrome(struct Storage *storage);
void HevcCroppingParams(struct Storage *storage, u32 *cropping_flag, u32 *left,
                        u32 *width, u32 *top, u32 *height);

u32 HevcCheckValidParamSets(struct Storage *storage);

void HevcFlushBuffer(struct Storage *storage);

u32 HevcAspectRatioIdc(const struct Storage *storage);
void HevcSarSize(const struct Storage *storage, u32 *sar_width,
                 u32 *sar_height);

u32 HevcLumaBitDepth(struct Storage *storage);
u32 HevcChromaBitDepth(struct Storage *storage);

#endif /* #ifdef HEVC_DECODER_H_ */
