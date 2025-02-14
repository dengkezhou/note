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

#ifndef H264HWD_DECODER_H
#define H264HWD_DECODER_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "basetype.h"
#include "h264decapi.h"

#include "h264hwd_storage.h"
#include "h264hwd_container.h"
#include "h264hwd_dpb.h"

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/

/* enumerated return values of the functions */
enum H264Result {
  H264BSD_RDY, /* some nal unit or feature don't support, just skip. */
  H264BSD_PIC_RDY,
  H264BSD_HDRS_RDY,
  H264BSD_SEI_PARSED,
  H264BSD_PARAM_SET_PARSED,
  H264BSD_BUFFER_NOT_READY,
  H264BSD_NEW_ACCESS_UNIT,
  H264BSD_FMO,
  H264BSD_UNPAIRED_FIELD,
  H264BSD_ABORTED,
  H264BSD_NO_FREE_BUFFER,

  /* error case */
  H264BSD_NO_REF = -1, /* current pic don't have ref pic, need skip. */
  H264BSD_SEI_ERROR = -2,
  H264BSD_PARAM_SET_ERROR = -3,
  H264BSD_SLICE_HDR_ERROR = -4,
  H264BSD_NONREF_PIC_SKIPPED = -5, /* current pic is nonrefrence pic, unsed in skip frame mode. */
  H264BSD_PB_PIC_SKIPPED = -6, /* skip P/B pic, used in intra only mode. */
  H264BSD_MEMFAIL = -7,
  H264BSD_REF_PICS_ERROR = -8,
  H264BSD_NALUNIT_ERROR = -9,
  H264BSD_AU_BOUNDARY_ERROR = -10,
  H264BSD_ERROR_DETECTED = -11 /* syntax element error found in stream */
};

/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

void h264bsdInit(storage_t * storage, u32 no_output_reordering,
                 u32 use_smoothing_buffer);
u32 h264bsdDecode(struct H264DecContainer * dec_cont, const u8 * byte_strm, u32 len,
                  u32 pic_id, u32 * read_bytes);
void h264bsdShutdown(storage_t * storage);

const dpbOutPicture_t *h264bsdNextOutputPicture(storage_t * storage);

u32 h264bsdPicWidth(storage_t * storage);
u32 h264bsdPicHeight(storage_t * storage);
u32 h264bsdVideoRange(storage_t * storage);
u32 h264bsdMatrixCoefficients(storage_t * storage);
u32 h264bsdTransferCharacteristics(storage_t * storage);
u32 h264bsdColourPrimaries(storage_t * storage);
u32 h264bsdColourDescPresent(storage_t * storage);
u32 h264bsdTimingInfoPresent(storage_t * storage);
u32 h264bsdNumUnitsInTick(storage_t * storage);
u32 h264bsdTimeScale(storage_t * storage);
u32 h264bsdIsMonoChrome(storage_t * storage);
u32 h264bsdChromaFormatIdc(storage_t * storage);
void h264bsdCroppingParams(storage_t *storage, struct DecCropParams *p_crop);

u32 h264bsdCheckValidParamSets(storage_t * storage);

void h264bsdFlushBuffer(storage_t * storage);

u32 h264bsdAspectRatioIdc(const storage_t * storage);
void h264bsdSarSize(const storage_t * storage, u32 * sar_width,
                    u32 * sar_height);

u32 h264bsdFixFrameNum(u8 *stream, u32 strm_len, u32 frame_num, u32 max_frame_num,
                       u32 *skipped_bytes);
u32 h264bsdCheckErrorFrameAU(struct H264DecContainer * dec_cont, const u8 * byte_strm, u32 len);
#endif /* #ifdef H264HWD_DECODER_H */
