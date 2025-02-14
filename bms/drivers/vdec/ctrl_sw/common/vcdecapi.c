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

#include <string.h>
#include "version.h"
#include "vcdecapi.h"
#include "decapicommon.h"
#include "sw_debug.h"
#include "sw_util.h"
#include "commonfunction.h"
#include "dec_log.h"
#include "parselogmsg.h"
#include "sw_stream.h"
#ifdef PERFORMANCE_TEST
#include "sw_activity_trace.h"
extern u32 hw_time_use;
#endif
#ifdef USE_RANDOM_ERROR_TEST
#include "string.h"
#include "stream_corrupt.h"
#endif

/* Standalone Post-Processing */
#ifdef ENABLE_PPDEC_SUPPORT
#include "ppapi.h"
#endif /* ENABLE_PPEDC_SUPPORT */

/* Advanced formats */
#ifdef ENABLE_VVC_SUPPORT
#include "vvcdecapi.h"
#endif /* ENABLE_VVC_SUPPORT */
#ifdef ENABLE_HEVC_SUPPORT
#include "hevcdecapi.h"
#endif /* ENABLE_HEVC_SUPPORT */
#ifdef ENABLE_H264_SUPPORT
#include "h264decapi.h"
#endif /* ENABLE_H264_SUPPORT */
#ifdef ENABLE_VP9_SUPPORT
#include "vp9decapi.h"
#endif /* ENABLE_VP9_SUPPORT */
#ifdef ENABLE_AVS2_SUPPORT
#include "avs2decapi.h"
#endif /* ENABLE_AVS2_SUPPORT */
#ifdef ENABLE_AV1_SUPPORT
#include "av1decapi.h"
#endif /* ENABLE_AV1_SUPPORT */

/* Legacy formats */
#ifdef ENABLE_VP8_SUPPORT
#include "vp8decapi.h"
#endif /* ENABLE_VP8_SUPPORT */
#ifdef ENABLE_JPEG_SUPPORT
#include "jpegdecapi.h"
#endif /* ENABLE_JPEG_SUPPORT */
#ifdef ENABLE_VP6_SUPPORT
#include "vp6decapi.h"
#endif /* ENABLE_VP6_SUPPORT */
#ifdef ENABLE_MPEG2_SUPPORT
#include "mpeg2decapi.h"
#endif /* ENABLE_MPEG2_SUPPORT */
#ifdef ENABLE_MPEG4_SUPPORT
#include "mp4decapi.h"
#endif /* ENABLE_MPEG4_SUPPORT */
#ifdef ENABLE_AVS_SUPPORT
#include "avsdecapi.h"
#endif /* ENABLE_AVS_SUPPORT */
#ifdef ENABLE_VC1_SUPPORT
#include "vc1decapi.h"
#endif /* ENABLE_VC1_SUPPORT */
#ifdef ENABLE_RV_SUPPORT
#include "rvdecapi.h"
#endif /* ENABLE_RV_SUPPORT */

/*------------------------------------------------------------------------------*/
/* macro define */

#ifdef CASE_INFO_STAT
#include "commonfunction.h"
extern CaseInfo case_info;
static void VCDecInfoCollect(CaseInfo* case_info);
#endif

// #define DOWN_SCALE_SIZE(w, ds) (((w)/(ds)) & ~0x1)

#if defined(ENABLE_VP9_SUPPORT) || defined(ENABLE_AV1_SUPPORT)
/* function copied from the libvpx */
static void ParseSuperframeIndex(const u8* data, size_t data_sz,
                                 const u8* buf, size_t buf_sz,
                                 u32 sizes[8], i32* count, int av1baseline,
                                 struct strmInfo *stream_info);

static void GetOutPicBufferSize(u32 height, u32 luma_stride, u32 chroma_stride,
	                              enum DecPictureFormat output_format,
                                u32* luma_size, u32* chroma_size);
#endif /* #if defined(ENABLE_VP9_SUPPORT) || defined(ENABLE_AV1_SUPPORT) */

#ifdef ENABLE_AV1_SUPPORT
static int Av1Leb128(const u8* p, int* len, const u8 *buf, u32 buf_len);
#endif /* #ifdef ENABLE_AV1_SUPPORT */
/* parse enum DecRet*/

#ifdef USE_DUMP_INPUT_STREAM
struct IVF_HEADER {
  unsigned char signature[4];  //='DKIF';
  unsigned short version;      //= 0;
  unsigned short headersize;   //= 32;
  unsigned int FourCC;
  unsigned short width;
  unsigned short height;
  unsigned int rate;
  unsigned int scale;
  unsigned int length;
  unsigned char unused[4];
};
#endif

#ifdef USE_RANDOM_ERROR_TEST
/* random error: partial tb_cfg.tb_params parameters. */
  struct ErrorParams random_error_params = {
    .seed = 0,
    .truncate_stream = 0,
    .truncate_stream_odds = "0",
    .swap_bits_in_stream = 0,
    .swap_bit_odds = "0",
    .lose_packets = 0,
    .packet_loss_odds = "0",
    .random_error_enabled = 0
  };
#endif

/* VCDec Wrapper */
typedef struct VCDecInst {
  enum DecCodec codec;
  void *inst; /* pointer to real decoder instance created by xxxDecInit API. */
  enum DecRet (*VCDecInit)(struct VCDecInst *inst, struct DecInitConfig *init_config);
  enum DecRet (*VCDecGetInfo)(struct VCDecInst *vcdec, struct DecSequenceInfo *info);
  enum DecRet (*VCDecSetInfo)(struct VCDecInst *vcdec, struct DecConfig *config);
  enum DecRet (*VCDecDecode)(struct VCDecInst *vcdec, struct DecOutput *output, struct DecInputParameters *param);
  enum DecRet (*VCDecNextPicture)(struct VCDecInst *vcdec, struct DecPictures *pic);
  enum DecRet (*VCDecPictureConsumed)(struct VCDecInst *vcdec, struct DecPictures *pic);
  enum DecRet (*VCDecEndOfStream)(struct VCDecInst *vcdec);
  enum DecRet (*VCDecGetBufferInfo)(struct VCDecInst *vcdec, struct DecBufferInfo *buf_info);
  enum DecRet (*VCDecAddBuffer)(struct VCDecInst *vcdec, struct DWLLinearMem *buf);
  enum DecRet (*VCDecUseExtraFrmBuffers)(struct VCDecInst *vcdec, u32 n);
  enum DecRet (*VCDecPeek)(struct VCDecInst *vcdec, struct DecPictures *pic); /* new */
  enum DecRet (*VCDecAbort)(struct VCDecInst *vcdec); /* new */
  enum DecRet (*VCDecAbortAfter)(struct VCDecInst *vcdec); /* new */
  void (*VCDecSetNoReorder)(struct VCDecInst *vcdec, u32 no_reorder); /* new */
  void (*VCDecRelease)(struct VCDecInst *vcdec);
  void (*VCDecUpdateStrmInfoCtrl)(struct VCDecInst *vcdec, struct strmInfo info);
  enum DecRet (*VCDecGetUserData)(struct VCDecInst *vcdec, struct DecInputParameters *param,
                                  struct DecUserConf *user_data_config); /* mpeg4 specific */
  enum DecRet (*VCDecSetCustomInfo)(struct VCDecInst *vcdec, const u32 width, const u32 height); /* mpeg4 specific */
  /* VC1 specific : VCDecUnpackMetaData */

#ifdef PERFORMANCE_TEST
  struct ActivityTrace activity;
#endif

#ifdef USE_RANDOM_ERROR_TEST
  struct ErrorParams error_params;
  u32 stream_not_consumed;
  u32 prev_input_len;
  struct DecMCConfig mcinit_cfg;
#endif

#ifdef USE_DUMP_INPUT_STREAM
  bool ivf_header_enable_flag;
  FILE *ferror_stream;
  FILE *fp_index;
#endif

  /* low latency: input stream info, for vp9&av1 */
  struct strmInfo stream_info;
#ifdef ENABLE_AV1_SUPPORT
  /* Data wil be used in Av1Decode*/
  struct Av1UserData {
    bool annexb;
    bool plainobu;
  } av1_data;
#endif /* #ifdef ENABLE_AV1_SUPPORT */

#if defined(ENABLE_AV1_SUPPORT) || defined(ENABLE_VP9_SUPPORT)
/* for ivf super frame*/
  i32 sf_num_frms;
  i32 sf_cur_frm_id;
  u32 sf_frm_sizes[8];
#endif /* ENABLE_AV1_SUPPORT || ENABLE_VP9_SUPPORT*/
} VCDecInst;

/* VVC codec wrappers. */
#ifdef ENABLE_VVC_SUPPORT
static enum DecRet VCDecVvcInit(struct VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecVvcGetInfo(VCDecInst *vcdec, struct DecSequenceInfo *info);
static enum DecRet VCDecVvcSetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecVvcDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecVvcNextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecVvcPictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecVvcEndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecVvcGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecVvcAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecVvcUseExtraFrmBuffers(VCDecInst *vcdec, u32 n);
static enum DecRet VCDecVvcPeek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecVvcAbort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecVvcAbortAfter(VCDecInst *vcdec); /* new */
static void VCDecVvcSetNoReorder(VCDecInst *vcdec, u32 no_reorder); /* new */
static void VCDecVvcRelease(VCDecInst *vcdec);
static void VCDecVvcUpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_VVC_SUPPORT */

/* Hevc codec wrappers. */
#ifdef ENABLE_HEVC_SUPPORT
static enum DecRet VCDecHevcInit(struct VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecHevcGetInfo(VCDecInst *vcdec, struct DecSequenceInfo *info);
static enum DecRet VCDecHevcSetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecHevcDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecHevcNextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecHevcPictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecHevcEndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecHevcGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecHevcAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecHevcUseExtraFrmBuffers(VCDecInst *vcdec, u32 n);
static enum DecRet VCDecHevcPeek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecHevcAbort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecHevcAbortAfter(VCDecInst *vcdec); /* new */
static void VCDecHevcSetNoReorder(VCDecInst *vcdec, u32 no_reorder); /* new */
static void VCDecHevcRelease(VCDecInst *vcdec);
static void VCDecHevcUpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_HEVC_SUPPORT */

/* H264 codec wrappers. */
#ifdef ENABLE_H264_SUPPORT
static enum DecRet VCDecH264Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecH264GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecH264SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecH264Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecH264NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecH264PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecH264EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecH264GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecH264AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecH264Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecH264Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecH264AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecH264SetNoReorder(VCDecInst *vcdec, u32 no_reorder); /* new */
static void VCDecH264Release(VCDecInst *vcdec);
static void VCDecH264UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_H264_SUPPORT */

/* VP9 codec wrappers. */
#ifdef ENABLE_VP9_SUPPORT
static enum DecRet VCDecVp9Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecVp9GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecVp9SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecVp9Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecVp9NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecVp9PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecVp9EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecVp9GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecVp9AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecVp9UseExtraFrmBuffers(VCDecInst *vcdec, u32 n);
static enum DecRet VCDecVp9Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecVp9AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecVp9Release(VCDecInst *vcdec);
static void VCDecVp9UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_VP9_SUPPORT */

/* AVS2 codec wrappers. */
#ifdef ENABLE_AVS2_SUPPORT
static enum DecRet VCDecAvs2Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecAvs2GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecAvs2SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecAvs2Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecAvs2NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecAvs2PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecAvs2EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecAvs2GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecAvs2AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecAvs2UseExtraFrmBuffers(VCDecInst *vcdec, u32 n);
static enum DecRet VCDecAvs2Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecAvs2Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecAvs2AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecAvs2SetNoReorder(VCDecInst *vcdec, u32 no_reorder); /* new */
static void VCDecAvs2Release(VCDecInst *vcdec);
static void VCDecAvs2UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_AVS2_SUPPORT */

/* AV1 codec wrappers. */
#ifdef ENABLE_AV1_SUPPORT
static enum DecRet VCDecAv1Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecAv1GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecAv1SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecAv1Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecAv1NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecAv1PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecAv1EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecAv1GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecAv1AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecAv1Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecAv1AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecAv1Release(VCDecInst *vcdec);
static void VCDecAv1UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_AV1_SUPPORT */

/* VP8 codec wrappers. */
#ifdef ENABLE_VP8_SUPPORT
static enum DecRet VCDecVp8Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecVp8GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecVp8SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecVp8Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecVp8NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecVp8PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecVp8EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecVp8GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecVp8AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecVp8Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecVp8Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecVp8AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecVp8Release(VCDecInst *vcdec);
#endif /* ENABLE_VP8_SUPPORT */

/* JPEG codec wrappers. */
#ifdef ENABLE_JPEG_SUPPORT
static enum DecRet VCDecJpegInit(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecJpegGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info); /* JpegDecGetImageInfo */
static enum DecRet VCDecJpegSetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecJpegDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecJpegNextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecJpegPictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecJpegEndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecJpegGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecJpegAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecJpegAbort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecJpegAbortAfter(VCDecInst *vcdec); /* new */
static void VCDecJpegRelease(VCDecInst *vcdec);
static void VCDecJpegUpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info);
#endif /* ENABLE_JPEG_SUPPORT */

/* VP6 codec wrappers. */
#ifdef ENABLE_VP6_SUPPORT
static enum DecRet VCDecVp6Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecVp6GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecVp6SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecVp6Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecVp6NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecVp6PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecVp6EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecVp6GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecVp6AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecVp6Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecVp6Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecVp6AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecVp6Release(VCDecInst *vcdec);
#endif /* ENABLE_VP6_SUPPORT */

/* MPEG2 codec wrappers. */
#ifdef ENABLE_MPEG2_SUPPORT
static enum DecRet VCDecMpeg2Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecMpeg2GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecMpeg2SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecMpeg2Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecMpeg2NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecMpeg2PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecMpeg2EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecMpeg2GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecMpeg2AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecMpeg2Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecMpeg2Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecMpeg2AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecMpeg2Release(VCDecInst *vcdec);
#endif /* ENABLE_MPEG2_SUPPORT */

/* MPEG4 codec wrappers. */
#ifdef ENABLE_MPEG4_SUPPORT
static enum DecRet VCDecMpeg4Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecMpeg4GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecMpeg4SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecMpeg4Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecMpeg4NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecMpeg4PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecMpeg4EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecMpeg4GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecMpeg4AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecMpeg4Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecMpeg4Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecMpeg4AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecMpeg4Release(VCDecInst *vcdec);
static enum DecRet VCDecMpeg4GetUserData(VCDecInst *vcdec, struct DecInputParameters* param,
                                         struct DecUserConf* user_data_config); /* mpeg4 specific */
static enum DecRet VCDecMpeg4SetCustomInfo(VCDecInst *vcdec, const u32 width, const u32 height); /* mpeg4 specific */
#endif /* ENABLE_MPEG4_SUPPORT */

/* AVS codec wrappers. */
#ifdef ENABLE_AVS_SUPPORT
static enum DecRet VCDecAvsInit(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecAvsGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecAvsSetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecAvsDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecAvsNextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecAvsPictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecAvsEndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecAvsGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecAvsAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecAvsPeek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecAvsAbort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecAvsAbortAfter(VCDecInst *vcdec); /* new */
static void VCDecAvsRelease(VCDecInst *vcdec);
#endif /* ENABLE_AVS_SUPPORT */

/* VC1 codec wrappers. */
#ifdef ENABLE_VC1_SUPPORT
static enum DecRet VCDecVc1Init(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecVc1GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecVc1SetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecVc1Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecVc1NextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecVc1PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecVc1EndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecVc1GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecVc1AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecVc1Peek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecVc1Abort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecVc1AbortAfter(VCDecInst *vcdec); /* new */
static void VCDecVc1Release(VCDecInst *vcdec);
/* VC1 specific : VCDecUnpackMetaData */
#endif /* ENABLE_VC1_SUPPORT */

/* RV codec wrappers. */
#ifdef ENABLE_RV_SUPPORT
static enum DecRet VCDecRvInit(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecRvGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info);
static enum DecRet VCDecRvSetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecRvDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecRvNextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static enum DecRet VCDecRvPictureConsumed(VCDecInst *vcdec, struct DecPictures *pic);
static enum DecRet VCDecRvEndOfStream(VCDecInst *vcdec);
static enum DecRet VCDecRvGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info);
static enum DecRet VCDecRvAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf);
static enum DecRet VCDecRvPeek(VCDecInst *vcdec, struct DecPictures *pic); /* new */
static enum DecRet VCDecRvAbort(VCDecInst *vcdec); /* new */
static enum DecRet VCDecRvAbortAfter(VCDecInst *vcdec); /* new */
static void VCDecRvRelease(VCDecInst *vcdec);
#endif /* ENABLE_RV_SUPPORT */

/* Standalone Pp wrappers. */
#ifdef ENABLE_PPDEC_SUPPORT
static enum DecRet VCDecPpInit(VCDecInst *vcdec, struct DecInitConfig *init_config);
static enum DecRet VCDecPpSetInfo(VCDecInst *vcdec, struct DecConfig *config);
static enum DecRet VCDecPpDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param);
static enum DecRet VCDecPpNextPicture(VCDecInst *vcdec, struct DecPictures* pic);
static void VCDecPpRelease(VCDecInst *vcdec);
#endif /* ENABLE_PPDEC_SUPPORT */

/*------------------------------------------------------------------------------*/
/* VCDecAPI : used in decapi.c or testbench */

struct DecApiVersion VCDecGetAPIVersion(void) {
  struct DecApiVersion ver;

  ver.major = VCDSW_VERSION_MAJOR;
  ver.minor = VCDSW_VERSION_MINOR;
  ver.micro = VCDSW_VERSION_MICRO;

  APITRACE("%s\n","VCDecGetAPIVersion# OK");

  return ver;
}

struct DecSwHwBuild VCDecGetBuild(u32 client_type) {
  struct DecSwHwBuild build;
  u16 i;
  (void)DWLmemset(&build, 0, sizeof(build));

  build.sw_build = VCDEC_BUILD_CLNUM;
  build.asic_id = DWLReadAsicID(client_type);
  u32 core_nums = DWLReadAsicCoreCount();
  if(core_nums <= MAX_ASIC_CORES) {
    for(i=0 ;i<core_nums; i++) {
      build.hw_build_id[i] = DWLReadCoreHwBuildID(i);
#ifdef OPEN_HWCFG_TO_CLIENT
      const struct DecHwFeatures *cfg;
      GetReleaseHwFeaturesByID(build.hw_build_id[i], &cfg);
      GetHwConfig(cfg, &build.hw_config[i]);
#endif
    }
  }
  else {
    APITRACEERR("%s\n","VDEC core numbers bigger than MAX_ASIC_CORES, which should be defined as the numbers of subsys");
  }

  return build;
}

u32 VCDecMCGetCoreCount(void) {
  return DWLReadAsicCoreCount();
}

enum DecRet VCDecUnpackMetaData(enum DecCodec codec, const u8 *p_buffer,
                                u32 buffer_size, struct DecMetaData* p_meta_data) {
#ifdef ENABLE_VC1_SUPPORT
  if(codec == DEC_VC1)
    return VC1DecUnpackMetaData(p_buffer, buffer_size, p_meta_data);
#endif
  return DEC_FORMAT_NOT_SUPPORTED;
}

enum DecRet VCDecInit(const void** inst, struct DecInitConfig *init_config) {
  APITRACE("%s\n","VCDecInit#");
  if (init_config == NULL) {
    APITRACEERR("%s\n","VDEC can't decode in DEC_PARAM_ERROR");
    return DEC_PARAM_ERROR;
  }
  ParseDecInitConfig(init_config);

#ifdef CASE_INFO_STAT
  if(case_info.thumb_flag) {
    DWLmemset(&case_info, 0, sizeof(case_info));
    case_info.thumb_flag = 1;
  }
  else
    DWLmemset(&case_info, 0, sizeof(case_info));
  case_info.format = init_config->codec;
#endif

  VCDecInst *vcdec = (VCDecInst *)DWLmalloc(sizeof(VCDecInst));
  if (vcdec == NULL) return DEC_MEMFAIL;

  DWLmemset(&vcdec->stream_info, 0, sizeof(vcdec->stream_info));

#ifdef PERFORMANCE_TEST
  char* codec_type = NULL; /* used for sw performance test. */
#endif
#ifdef USE_DUMP_INPUT_STREAM
  char* file_name = NULL; /* used for dump inpiut stream.*/
  struct IVF_HEADER *ivf_file_header = NULL;
  vcdec->ivf_header_enable_flag = FALSE;
#endif
  switch (init_config->codec) {
#ifdef ENABLE_VVC_SUPPORT
  case DEC_VVC: {
#ifdef PERFORMANCE_TEST
    codec_type = "VVC TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.vvc";
#endif
    vcdec->VCDecInit = VCDecVvcInit;
    vcdec->VCDecGetInfo = VCDecVvcGetInfo;
    vcdec->VCDecSetInfo = VCDecVvcSetInfo;
    vcdec->VCDecDecode = VCDecVvcDecode;
    vcdec->VCDecNextPicture = VCDecVvcNextPicture;
    vcdec->VCDecPictureConsumed = VCDecVvcPictureConsumed;
    vcdec->VCDecEndOfStream = VCDecVvcEndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecVvcGetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecVvcAddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = VCDecVvcUseExtraFrmBuffers;
    vcdec->VCDecPeek = VCDecVvcPeek; /* new */
    vcdec->VCDecAbort = VCDecVvcAbort; /* new */
    vcdec->VCDecAbortAfter = VCDecVvcAbortAfter; /* new */
    vcdec->VCDecSetNoReorder = VCDecVvcSetNoReorder; /* new */
    vcdec->VCDecRelease = VCDecVvcRelease;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecVvcUpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_HEVC_SUPPORT
  case DEC_HEVC: {
#ifdef PERFORMANCE_TEST
    codec_type = "HEVC TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.hevc";
#endif
    vcdec->VCDecInit = VCDecHevcInit;
    vcdec->VCDecGetInfo = VCDecHevcGetInfo;
    vcdec->VCDecSetInfo = VCDecHevcSetInfo;
    vcdec->VCDecDecode = VCDecHevcDecode;
    vcdec->VCDecNextPicture = VCDecHevcNextPicture;
    vcdec->VCDecPictureConsumed = VCDecHevcPictureConsumed;
    vcdec->VCDecEndOfStream = VCDecHevcEndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecHevcGetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecHevcAddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = VCDecHevcUseExtraFrmBuffers;
    vcdec->VCDecPeek = VCDecHevcPeek; /* new */
    vcdec->VCDecAbort = VCDecHevcAbort; /* new */
    vcdec->VCDecAbortAfter = VCDecHevcAbortAfter; /* new */
    vcdec->VCDecSetNoReorder = VCDecHevcSetNoReorder; /* new */
    vcdec->VCDecRelease = VCDecHevcRelease;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecHevcUpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_H264_SUPPORT
  case DEC_H264: {
#ifdef PERFORMANCE_TEST
    codec_type = "H264_H10P TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.h264_h10p";
#endif
    vcdec->VCDecInit = VCDecH264Init;
    vcdec->VCDecGetInfo = VCDecH264GetInfo;
    vcdec->VCDecSetInfo = VCDecH264SetInfo;
    vcdec->VCDecDecode = VCDecH264Decode;
    vcdec->VCDecNextPicture = VCDecH264NextPicture;
    vcdec->VCDecPictureConsumed = VCDecH264PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecH264EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecH264GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecH264AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecH264Peek; /* new */
    vcdec->VCDecAbort = VCDecH264Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecH264AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = VCDecH264SetNoReorder; /* new */
    vcdec->VCDecRelease = VCDecH264Release;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecH264UpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_VP9_SUPPORT
  case DEC_VP9: {
#ifdef PERFORMANCE_TEST
    codec_type = "VP9 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.vp9";
    ivf_file_header = (struct IVF_HEADER *)DWLmalloc(sizeof(struct IVF_HEADER));
    strncpy((char *)&ivf_file_header->signature, "DKIF", 4);
    strncpy((char *)&ivf_file_header->FourCC, "VP90", 4);
    ivf_file_header->version = 0;
    ivf_file_header->headersize = 32;
    vcdec->ivf_header_enable_flag = TRUE;
#endif
    vcdec->VCDecInit = VCDecVp9Init;
    vcdec->VCDecGetInfo = VCDecVp9GetInfo;
    vcdec->VCDecSetInfo = VCDecVp9SetInfo;
    vcdec->VCDecDecode = VCDecVp9Decode;
    vcdec->VCDecNextPicture = VCDecVp9NextPicture;
    vcdec->VCDecPictureConsumed = VCDecVp9PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecVp9EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecVp9GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecVp9AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = VCDecVp9UseExtraFrmBuffers;
    vcdec->VCDecPeek = NULL; /* new */
    vcdec->VCDecAbort = VCDecVp9Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecVp9AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecVp9Release;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecVp9UpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_AVS2_SUPPORT
  case DEC_AVS2: {
#ifdef PERFORMANCE_TEST
    codec_type = "AVS2 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.avs2";
#endif
    vcdec->VCDecInit = VCDecAvs2Init;
    vcdec->VCDecGetInfo = VCDecAvs2GetInfo;
    vcdec->VCDecSetInfo = VCDecAvs2SetInfo;
    vcdec->VCDecDecode = VCDecAvs2Decode;
    vcdec->VCDecNextPicture = VCDecAvs2NextPicture;
    vcdec->VCDecPictureConsumed = VCDecAvs2PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecAvs2EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecAvs2GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecAvs2AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = VCDecAvs2UseExtraFrmBuffers;
    vcdec->VCDecPeek = VCDecAvs2Peek; /* new */
    vcdec->VCDecAbort = VCDecAvs2Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecAvs2AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = VCDecAvs2SetNoReorder; /* new */
    vcdec->VCDecRelease = VCDecAvs2Release;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecAvs2UpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_AV1_SUPPORT
  case DEC_AV1: {
#ifdef PERFORMANCE_TEST
    codec_type = "AV1 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.av1";
    ivf_file_header = (struct IVF_HEADER *)DWLmalloc(sizeof(struct IVF_HEADER));
    strncpy((char *)&ivf_file_header->signature, "DKIF", 4);
    strncpy((char *)&ivf_file_header->FourCC, "AV01", 4);
    ivf_file_header->version = 0;
    ivf_file_header->headersize = 32;
    vcdec->ivf_header_enable_flag = TRUE;
#endif
    vcdec->VCDecInit = VCDecAv1Init;
    vcdec->VCDecGetInfo = VCDecAv1GetInfo;
    vcdec->VCDecSetInfo = VCDecAv1SetInfo;
    vcdec->VCDecDecode = VCDecAv1Decode;
    vcdec->VCDecNextPicture = VCDecAv1NextPicture;
    vcdec->VCDecPictureConsumed = VCDecAv1PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecAv1EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecAv1GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecAv1AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = NULL; /* new */
    vcdec->VCDecAbort = VCDecAv1Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecAv1AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecAv1Release;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecAv1UpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_VP8_SUPPORT
  case DEC_VP8: {
#ifdef PERFORMANCE_TEST
    codec_type = "VP8 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    if (init_config->dec_format == DEC_INPUT_VP7) {
      file_name = "random_error.vp7";
    } else {
      file_name = "random_error.vp8";
      ivf_file_header = (struct IVF_HEADER *)DWLmalloc(sizeof(struct IVF_HEADER));
      strncpy((char *)&ivf_file_header->signature, "DKIF", 4);
      strncpy((char *)&ivf_file_header->FourCC, "VP80", 4);
      ivf_file_header->version = 0;
      ivf_file_header->headersize = 32;
      vcdec->ivf_header_enable_flag = TRUE;
    }
#endif
    vcdec->VCDecInit = VCDecVp8Init;
    vcdec->VCDecGetInfo = VCDecVp8GetInfo;
    vcdec->VCDecSetInfo = VCDecVp8SetInfo;
    vcdec->VCDecDecode = VCDecVp8Decode;
    vcdec->VCDecNextPicture = VCDecVp8NextPicture;
    vcdec->VCDecPictureConsumed = VCDecVp8PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecVp8EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecVp8GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecVp8AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecVp8Peek; /* new */
    vcdec->VCDecAbort = VCDecVp8Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecVp8AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecVp8Release;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_JPEG_SUPPORT
  case DEC_JPEG: {
#ifdef PERFORMANCE_TEST
    codec_type = "JPEG TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.jpeg";
#endif
    vcdec->VCDecInit = VCDecJpegInit;
    vcdec->VCDecGetInfo = VCDecJpegGetInfo;
    vcdec->VCDecSetInfo = VCDecJpegSetInfo;
    vcdec->VCDecDecode = VCDecJpegDecode;
    vcdec->VCDecNextPicture = VCDecJpegNextPicture;
    vcdec->VCDecPictureConsumed = VCDecJpegPictureConsumed;
    vcdec->VCDecEndOfStream = VCDecJpegEndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecJpegGetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecJpegAddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = NULL; /* new */
    vcdec->VCDecAbort = VCDecJpegAbort; /* new */
    vcdec->VCDecAbortAfter = VCDecJpegAbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecJpegRelease;
    vcdec->VCDecUpdateStrmInfoCtrl = VCDecJpegUpdateStrmInfoCtrl;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_VP6_SUPPORT
  case DEC_VP6: {
#ifdef PERFORMANCE_TEST
    codec_type = "VP6 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.vp6";
#endif
    vcdec->VCDecInit = VCDecVp6Init;
    vcdec->VCDecGetInfo = VCDecVp6GetInfo;
    vcdec->VCDecSetInfo = VCDecVp6SetInfo;
    vcdec->VCDecDecode = VCDecVp6Decode;
    vcdec->VCDecNextPicture = VCDecVp6NextPicture;
    vcdec->VCDecPictureConsumed = VCDecVp6PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecVp6EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecVp6GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecVp6AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecVp6Peek; /* new */
    vcdec->VCDecAbort = VCDecVp6Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecVp6AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecVp6Release;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_MPEG2_SUPPORT
  case DEC_MPEG2: {
#ifdef PERFORMANCE_TEST
    codec_type = "MPEG2 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.mpeg2";
#endif
    vcdec->VCDecInit = VCDecMpeg2Init;
    vcdec->VCDecGetInfo = VCDecMpeg2GetInfo;
    vcdec->VCDecSetInfo = VCDecMpeg2SetInfo;
    vcdec->VCDecDecode = VCDecMpeg2Decode;
    vcdec->VCDecNextPicture = VCDecMpeg2NextPicture;
    vcdec->VCDecPictureConsumed = VCDecMpeg2PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecMpeg2EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecMpeg2GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecMpeg2AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecMpeg2Peek; /* new */
    vcdec->VCDecAbort = VCDecMpeg2Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecMpeg2AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecMpeg2Release;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_MPEG4_SUPPORT
  case DEC_MPEG4: {
#ifdef PERFORMANCE_TEST
    codec_type = "MPEG4 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.mpeg4";
#endif
    vcdec->VCDecInit = VCDecMpeg4Init;
    vcdec->VCDecGetInfo = VCDecMpeg4GetInfo;
    vcdec->VCDecSetInfo = VCDecMpeg4SetInfo;
    vcdec->VCDecDecode = VCDecMpeg4Decode;
    vcdec->VCDecNextPicture = VCDecMpeg4NextPicture;
    vcdec->VCDecPictureConsumed = VCDecMpeg4PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecMpeg4EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecMpeg4GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecMpeg4AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecMpeg4Peek; /* new */
    vcdec->VCDecAbort = VCDecMpeg4Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecMpeg4AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecMpeg4Release;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = VCDecMpeg4GetUserData;
    vcdec->VCDecSetCustomInfo = VCDecMpeg4SetCustomInfo;
    break;
  }
#endif
#ifdef ENABLE_AVS_SUPPORT
  case DEC_AVS: {
#ifdef PERFORMANCE_TEST
    codec_type = "AVS TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.avs";
#endif
    vcdec->VCDecInit = VCDecAvsInit;
    vcdec->VCDecGetInfo = VCDecAvsGetInfo;
    vcdec->VCDecSetInfo = VCDecAvsSetInfo;
    vcdec->VCDecDecode = VCDecAvsDecode;
    vcdec->VCDecNextPicture = VCDecAvsNextPicture;
    vcdec->VCDecPictureConsumed = VCDecAvsPictureConsumed;
    vcdec->VCDecEndOfStream = VCDecAvsEndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecAvsGetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecAvsAddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecAvsPeek; /* new */
    vcdec->VCDecAbort = VCDecAvsAbort; /* new */
    vcdec->VCDecAbortAfter = VCDecAvsAbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecAvsRelease;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_VC1_SUPPORT
  case DEC_VC1: {
#ifdef PERFORMANCE_TEST
    codec_type = "VC1 TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.vc1";
#endif
    vcdec->VCDecInit = VCDecVc1Init;
    vcdec->VCDecGetInfo = VCDecVc1GetInfo;
    vcdec->VCDecSetInfo = VCDecVc1SetInfo;
    vcdec->VCDecDecode = VCDecVc1Decode;
    vcdec->VCDecNextPicture = VCDecVc1NextPicture;
    vcdec->VCDecPictureConsumed = VCDecVc1PictureConsumed;
    vcdec->VCDecEndOfStream = VCDecVc1EndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecVc1GetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecVc1AddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecVc1Peek; /* new */
    vcdec->VCDecAbort = VCDecVc1Abort; /* new */
    vcdec->VCDecAbortAfter = VCDecVc1AbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecVc1Release;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_RV_SUPPORT
  case DEC_RV: {
#ifdef PERFORMANCE_TEST
    codec_type = "RV TOTAL";
#endif
#ifdef USE_DUMP_INPUT_STREAM
    file_name = "random_error.rv";
#endif
    vcdec->VCDecInit = VCDecRvInit;
    vcdec->VCDecGetInfo = VCDecRvGetInfo;
    vcdec->VCDecSetInfo = VCDecRvSetInfo;
    vcdec->VCDecDecode = VCDecRvDecode;
    vcdec->VCDecNextPicture = VCDecRvNextPicture;
    vcdec->VCDecPictureConsumed = VCDecRvPictureConsumed;
    vcdec->VCDecEndOfStream = VCDecRvEndOfStream;
    vcdec->VCDecGetBufferInfo = VCDecRvGetBufferInfo;
    vcdec->VCDecAddBuffer = VCDecRvAddBuffer;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = VCDecRvPeek; /* new */
    vcdec->VCDecAbort = VCDecRvAbort; /* new */
    vcdec->VCDecAbortAfter = VCDecRvAbortAfter; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecRvRelease;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
#ifdef ENABLE_PPDEC_SUPPORT
  case DEC_PPDEC: {
#ifdef PERFORMANCE_TEST
    codec_type = "PPDEC TOTAL";
#endif
// #ifdef USE_DUMP_INPUT_STREAM
//     file_name = "random_error.pp";
// #endif
    vcdec->VCDecInit = VCDecPpInit;
    vcdec->VCDecGetInfo = NULL;
    vcdec->VCDecSetInfo = VCDecPpSetInfo;
    vcdec->VCDecDecode = VCDecPpDecode;
    vcdec->VCDecNextPicture = VCDecPpNextPicture;
    vcdec->VCDecPictureConsumed = NULL;
    vcdec->VCDecEndOfStream = NULL;
    vcdec->VCDecGetBufferInfo = NULL;
    vcdec->VCDecAddBuffer = NULL;
    vcdec->VCDecUseExtraFrmBuffers = NULL;
    vcdec->VCDecPeek = NULL; /* new */
    vcdec->VCDecAbort = NULL; /* new */
    vcdec->VCDecAbortAfter = NULL; /* new */
    vcdec->VCDecSetNoReorder = NULL; /* new */
    vcdec->VCDecRelease = VCDecPpRelease;
    vcdec->VCDecUpdateStrmInfoCtrl = NULL;
    vcdec->VCDecGetUserData = NULL;
    vcdec->VCDecSetCustomInfo = NULL;
    break;
  }
#endif
  default:
    DWLfree(vcdec);
    return DEC_FORMAT_NOT_SUPPORTED;
  }

/* measure sw overhead */
#ifdef PERFORMANCE_TEST
    SwActivityTraceInit(&vcdec->activity, codec_type);
#endif
/* ramdom error injection */
#ifdef USE_RANDOM_ERROR_TEST
    vcdec->error_params = random_error_params;
    InitializeRandom(&vcdec->error_params,
                     vcdec->error_params.truncate_stream_odds,
                     vcdec->error_params.swap_bit_odds,
                     vcdec->error_params.packet_loss_odds,
                     vcdec->error_params.seed);
    vcdec->mcinit_cfg = init_config->mc_cfg;
#endif
/* dump input stream */
#ifdef USE_DUMP_INPUT_STREAM
    vcdec->ferror_stream = fopen(file_name, "wb");
    if(vcdec->ferror_stream == NULL) {
      APITRACEERR("VCDecInit# VDEC can't decode in: Unable to open file %s\n", file_name);
      return DEC_MEMFAIL;
    }
    if (ivf_file_header != NULL) {
      fwrite(ivf_file_header, 1, 32, vcdec->ferror_stream);
      DWLfree(ivf_file_header);
    }
#endif

  vcdec->codec = init_config->codec;

  *inst = vcdec; /* let dec_inst point to vcdec */
  enum DecRet rv = (vcdec->VCDecInit(vcdec, init_config));
  APITRACE("VCDecInit# %s",ParseDecRet(rv));
  return rv;
}

enum DecRet VCDecGetInfo(void *inst, struct DecSequenceInfo* info) {
  APITRACE("%s\n","VCDecGetInfo#");
  ParseDecSequenceInfo(info);
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecGetInfo != NULL){
    enum DecRet rv = vcdec->VCDecGetInfo(vcdec, info);
    APITRACE("VCDecGetInfo# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecGetInfo# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecSetInfo(void *inst, struct DecConfig *config) {
  APITRACE("%s\n","VCDecSetInfo#");
  ParseDecConfig(config);
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecSetInfo != NULL){
    enum DecRet rv = (vcdec->VCDecSetInfo(vcdec, config));
    APITRACE("VCDecSetInfo# %s",ParseDecRet(rv));
    return rv;

  }
  APITRACEERR("%s\n","VCDecSetInfo# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecDecode(void *inst, struct DecOutput* output, struct DecInputParameters* param) {
  APITRACE("%s\n","VCDecDecode#");
  VCDecInst *vcdec = (VCDecInst *)inst;
#ifdef USE_RANDOM_ERROR_TEST
  u32 input_data_len = 0;
#endif
#ifdef USE_DUMP_INPUT_STREAM
  u32 frame_len = 0;
#endif
  StackStatInit();
  if (vcdec != NULL && vcdec->VCDecDecode != NULL) {
    if (vcdec->codec != DEC_PPDEC) {
      ParseDecInputParameters(param);
      APITRACEDEBUG("VCDecDecode# Input strm_len: %lu\n",param->strm_len);
#ifdef USE_RANDOM_ERROR_TEST
      input_data_len = param->strm_len;
      if (vcdec->error_params.random_error_enabled) {
        // error type: lose packets;
        if (vcdec->error_params.lose_packets && !vcdec->stream_not_consumed) {
          u8 lose_packet = 0;
          if (RandomizePacketLoss(vcdec->error_params.packet_loss_odds, &lose_packet)) {
            APITRACEERR("%s\n","VCDecDecode# ERROR: Packet loss simulator error (wrong config?)");
          }
          if (lose_packet) {
            input_data_len = 0;
            output->data_left = 0;
            vcdec->stream_not_consumed = 0;
            if(vcdec->mcinit_cfg.mc_enable) {
              /* release buffer fully processed by SW */
              if(vcdec->mcinit_cfg.stream_consumed_callback)
                vcdec->mcinit_cfg.stream_consumed_callback((u8*)param->stream, (void*)param->p_user_data);
            }
            return DEC_STRM_PROCESSED;
          }
        }

        // error type: truncate stream(random len for random packet);
        if (vcdec->error_params.truncate_stream && !vcdec->stream_not_consumed) {
          /* compute odds. */
          u8 truncate_stream = 0;
          if (RandomizePacketLoss(vcdec->error_params.truncate_stream_odds, &truncate_stream)) {
            APITRACEERR("%s\n","VCDecDecode# ERROR: Truncate stream simulator error (wrong config?)");
          }
          if (truncate_stream) {
            u32 random_size = input_data_len;
            if (RandomizeU32(&random_size)) {
              APITRACEERR("%s\n","VCDecDecode# ERROR: Truncate randomizer error (wrong config?)");
            }
            input_data_len = random_size;
          }

          vcdec->prev_input_len = input_data_len;

          if (input_data_len == 0) {
            output->data_left = 0;
            vcdec->stream_not_consumed = 0;
            /* release buffer fully processed by SW */
            if(vcdec->mcinit_cfg.mc_enable) {
              /* release buffer fully processed by SW */
              if(vcdec->mcinit_cfg.stream_consumed_callback)
                vcdec->mcinit_cfg.stream_consumed_callback((u8*)param->stream, (void*)param->p_user_data);
            }
            return DEC_STRM_PROCESSED;
          }
        }

        /*  stream is truncated but not consumed at first time, the same truncated length
            at the second time */
        if (vcdec->error_params.truncate_stream && vcdec->stream_not_consumed)
          input_data_len = vcdec->prev_input_len;

        // error type: swap bits;
        if (vcdec->error_params.swap_bits_in_stream && !vcdec->stream_not_consumed) {
          u8 *p_tmp = (u8 *)param->stream;
          u32 use_ringbuffer = (p_tmp + input_data_len) > ((u8 *)param->stream_buffer.virtual_address + param->stream_buffer.size) ? 1 : 0;
          if (RandomizeBitSwapInStream(p_tmp, (u8*)param->stream_buffer.virtual_address,
                                      param->stream_buffer.size, input_data_len,
                                      vcdec->error_params.swap_bit_odds,
                                      use_ringbuffer)) {
            APITRACEDEBUG("%s\n","VCDecDecode# ERROR: Bitswap randomizer error (wrong config?)");
          }
        }
      }
      param->strm_len = input_data_len; /* input_data_len change in here and will be used in xxxDecDecode function */
#endif
#ifdef PERFORMANCE_TEST
      SwActivityTraceStartDec(&vcdec->activity);
#endif
    }

    enum DecRet rv = (vcdec->VCDecDecode(vcdec, output, param));

    if (vcdec->codec != DEC_PPDEC) {
      APITRACE("VCDecDecode# Input stream buffer virtual address: %p, bus_address: %p\n", (void*)param->stream_buffer.virtual_address,(void*)param->stream_buffer.bus_address);
      APITRACE("VCDecDecode# Input stream len: %u  data left: %u\n", param->strm_len,output->data_left);
      APITRACE("VCDecDecode# %s",ParseDecRet(rv));
#ifdef PERFORMANCE_TEST
      SwActivityTraceStopDec(&vcdec->activity);
#endif
#ifdef USE_RANDOM_ERROR_TEST
      if (output->data_left != input_data_len || output->data_left == 0)
        vcdec->stream_not_consumed = 0;
      else
        vcdec->stream_not_consumed = 1;
#endif
#ifdef USE_DUMP_INPUT_STREAM
      if (vcdec->ivf_header_enable_flag) {
        if (output->data_left == 0) {
          u8 ivf_frame_header[12] = {0};
          u32 tmp_value = param->strm_len;
          ivf_frame_header[3] = tmp_value >> 24;
          tmp_value = tmp_value - (ivf_frame_header[3] << 24);
          ivf_frame_header[2] = tmp_value >> 16;
          tmp_value = tmp_value - (ivf_frame_header[2] << 16);
          ivf_frame_header[1] = tmp_value >> 8;
          tmp_value = tmp_value - (ivf_frame_header[1] << 8);
          ivf_frame_header[0] = tmp_value;
          fwrite(ivf_frame_header, 1, 12, vcdec->ferror_stream);
        }
      } else if (vcdec->codec == DEC_VP6 || vcdec->codec == DEC_VP8) {
        if (output->data_left == 0) {
          /* write first 4 bytes of frame header for VP7 */
          u8 vp7_frame_header[4] = {0};
          u32 tmp_value = param->strm_len;
          vp7_frame_header[3] = tmp_value >> 24;
          tmp_value = tmp_value - (vp7_frame_header[3] << 24);
          vp7_frame_header[2] = tmp_value >> 16;
          tmp_value = tmp_value - (vp7_frame_header[2] << 16);
          vp7_frame_header[1] = tmp_value >> 8;
          tmp_value = tmp_value - (vp7_frame_header[1] << 8);
          vp7_frame_header[0] = tmp_value;
          fwrite(vp7_frame_header, 1, 4, vcdec->ferror_stream);
        }
      }

      if (output->strm_curr_pos > param->stream) {
        frame_len = output->strm_curr_pos - param->stream;
        fwrite(param->stream, 1, frame_len, vcdec->ferror_stream);
      } else if (output->strm_curr_pos == param->stream) {
        if (output->data_left == 0) {
          /* is ring buffer & strm_len == buffer_size */
          frame_len = param->strm_len;
          fwrite(param->stream, 1, frame_len, vcdec->ferror_stream);
        } else {
          /* stream_not_consumed */
        }
      } else {
        frame_len = (u32)(((u8*)param->stream_buffer.virtual_address + param->stream_buffer.size) - param->stream);
        frame_len += (u32)(output->strm_curr_pos - (u8*)param->stream_buffer.virtual_address);
        if (frame_len != param->strm_len - output->data_left)
          printf("Error: dump input stream buffer.\n");
        fwrite(param->stream, 1,
          (u32)(((u8*)param->stream_buffer.virtual_address + param->stream_buffer.size) - param->stream),
          vcdec->ferror_stream);
        fwrite(param->stream_buffer.virtual_address, 1,
          (u32)(output->strm_curr_pos - (u8*)param->stream_buffer.virtual_address),
          vcdec->ferror_stream);
      }
      if (!vcdec->fp_index)
        vcdec->fp_index = fopen("index.cfg", "w");
      if(vcdec->fp_index && frame_len > 0)
        fprintf(vcdec->fp_index, "%d\n", frame_len);
#endif
    }
    return rv;
  }
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecNextPicture(void *inst, struct DecPictures* pic) {
  //APITRACE("VCDecNextPicture# \n");
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecNextPicture != NULL){
    enum DecRet rv = (vcdec->VCDecNextPicture(vcdec, pic));
    if (rv == DEC_PIC_RDY)
      APITRACE("VCDecNextPicture# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecNextPicture# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecPictureConsumed(void *inst, struct DecPictures *pic) {
  APITRACE("%s\n","VCDecPictureConsumed#");
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecPictureConsumed != NULL)
  {
    enum DecRet rv = (vcdec->VCDecPictureConsumed(vcdec, pic));
    APITRACE("VCDecPictureConsumed# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecPictureConsumed# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecEndOfStream(void *inst) {
  APITRACE("%s\n","VCDecEndOfStream#");
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecEndOfStream != NULL){
    enum DecRet rv = (vcdec->VCDecEndOfStream(vcdec));
    APITRACE("VCDecEndOfStream# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecEndOfStream# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecGetBufferInfo(void *inst, struct DecBufferInfo *buf_info) {
  APITRACE("%s\n","VCDecGetBufferInfo#");
  ParseDecBufferInfo(buf_info);
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecGetBufferInfo != NULL){
    enum DecRet rv;
    rv = (vcdec->VCDecGetBufferInfo(vcdec, buf_info));
    APITRACE("VCDecGetBufferInfo# %s",ParseDecRet(rv));
    APITRACE("VCDecGetBufferInfo# buffers num: %u\n",buf_info->buf_num);
    APITRACE("VCDecGetBufferInfo# next_buf_size: %u\n",buf_info->next_buf_size);
    return rv;
  }
  APITRACEERR("%s\n","VCDecGetBufferInfo# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecAddBuffer(void *inst, struct DWLLinearMem *buf) {
  APITRACE("%s\n","VCDecAddBuffer#");
  APITRACEDEBUG("VCDecAddBuffer# DWLLinearMem# Virtual_address: 0x%x\n",buf->virtual_address);
  APITRACEDEBUG("VCDecAddBuffer# DWLLinearMem# Bus_address: 0x%x\n",buf->bus_address);
  APITRACEDEBUG("VCDecAddBuffer# DWLLinearMem# Size: 0x%x\n",buf->size);
  APITRACEDEBUG("VCDecAddBuffer# DWLLinearMem# Logical Size: 0x%x\n",buf->logical_size);
  APITRACEDEBUG("VCDecAddBuffer# DWLLinearMem# Mem type: %s\n",ParseDWLMemType(buf->mem_type));
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecAddBuffer != NULL){
    enum DecRet rv = (vcdec->VCDecAddBuffer(vcdec, buf));
    APITRACE("VCDecAddBuffer# virtual address: %p\n",(void*)buf->virtual_address);
    //APITRACE("bus address: %08x\n",buf->bus_address);
    APITRACE("VCDecAddBuffer# logical_size: %u\n",buf->logical_size);
    APITRACE("VCDecAddBuffer# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecAddBuffer# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecUseExtraFrmBuffers(void *inst, u32 n) {
  APITRACE("%s\n","VCDecUseExtraFrmBuffers#");
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecUseExtraFrmBuffers != NULL)
  {
    enum DecRet rv;
    rv = (vcdec->VCDecUseExtraFrmBuffers(vcdec, n));
    APITRACE("VCDecUseExtraFrmBuffers# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecUseExtraFrmBuffers# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecPeek(void *inst, struct DecPictures *pic) {
  VCDecInst *vcdec = (VCDecInst *)inst;
  APITRACE("%s\n","VCDecPeek#");
  if (vcdec != NULL && vcdec->VCDecPeek != NULL)
  {
    enum DecRet rv;
    rv = (vcdec->VCDecPeek(vcdec, pic));
    APITRACE("VCDecPeek# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecPeek# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecAbort(void *inst) {
  APITRACE("%s\n","VCDecAbort#");
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecAbort != NULL){
    enum DecRet rv;
    rv = (vcdec->VCDecAbort(vcdec));
    APITRACE("VCDecAbort# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecAbort# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecAbortAfter(void *inst) {
  VCDecInst *vcdec = (VCDecInst *)inst;
  APITRACE("%s\n","VCDecAbortAfter#");
  if (vcdec != NULL && vcdec->VCDecAbortAfter != NULL){
    enum DecRet rv;
    rv = (vcdec->VCDecAbortAfter(vcdec));
    APITRACE("VCDecAbortAfter# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecAbortAfter# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

void VCDecSetNoReorder(void *inst, u32 no_reorder) {
  APITRACE("%s\n","VCDecSetNoReorder#");
  APITRACE("VCDecSetNoReorder# No reorder: %d\n", no_reorder);
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecSetNoReorder != NULL){
   vcdec->VCDecSetNoReorder(vcdec, no_reorder);
  }
}

void VCDecRelease(void *inst) {
  APITRACE("%s\n","VCDecRelease#");
  VCDecInst *vcdec = (VCDecInst *)inst;
#ifdef CASE_INFO_STAT
  VCDecInfoCollect(&case_info);
#endif
  if (vcdec != NULL && vcdec->VCDecRelease != NULL) {
    (vcdec->VCDecRelease(vcdec));
#ifdef PERFORMANCE_TEST
    SwActivityTraceRelease(&vcdec->activity);
    printf("VCDecRelease# SW consumed time = %lld ms\n", vcdec->activity.active_time/100 - hw_time_use);
#endif
#ifdef USE_DUMP_INPUT_STREAM
  if (vcdec->ferror_stream) fclose(vcdec->ferror_stream);
  if (vcdec->fp_index)
    fclose(vcdec->fp_index);
#endif
  }
  DWLfree(vcdec);
}

void VCDecUpdateStrmInfoCtrl(void *inst, struct strmInfo info) {
  VCDecInst *vcdec = (VCDecInst *)inst;
  if (vcdec != NULL && vcdec->VCDecUpdateStrmInfoCtrl != NULL)
    (vcdec->VCDecUpdateStrmInfoCtrl(vcdec, info));
}

enum DecRet VCDecGetUserData(void *inst, struct DecInputParameters* param,
                             struct DecUserConf* user_data_config) {

  VCDecInst *vcdec = (VCDecInst *)inst;
  APITRACE("%s\n","VCDecGetUserData#");
  if (vcdec != NULL && vcdec->VCDecGetUserData != NULL){
    enum DecRet rv;
    rv = (vcdec->VCDecGetUserData(vcdec, param, user_data_config));
    APITRACE("VCDecGetUserData# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecGetUserData# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

enum DecRet VCDecSetCustomInfo(void *inst, const u32 width, const u32 height) {

  VCDecInst *vcdec = (VCDecInst *)inst;
  APITRACE("%s\n","VCDecSetCustomInfo#");
  APITRACE("VCDecSetCustomInfo# Width: %d\n", width);
  APITRACE("VCDecSetCustomInfo# Height: %d\n", height);
  if (vcdec != NULL && vcdec->VCDecSetCustomInfo != NULL){
    enum DecRet rv;
    rv = (vcdec->VCDecSetCustomInfo(vcdec, width, height));
    APITRACE("VCDecSetCustomInfo# %s",ParseDecRet(rv));
    return rv;
  }
  APITRACEERR("%s\n","VCDecSetCustomInfo# VDEC can't decode in DEC_PARAM_ERROR");
  return DEC_PARAM_ERROR;
}

/*------------------------------------------------------------------------------*/
#ifdef ENABLE_VVC_SUPPORT
static enum DecRet VCDecVvcInit(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct VvcDecConfig dec_cfg = {0, };
  enum DecRet rv = 0;
  dec_cfg.multi_frame_input_flag = config->multi_frame_input_flag;
  dec_cfg.no_output_reordering = config->disable_picture_reordering;
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_video_compressor = config->use_video_compressor;
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.num_buffers = config->num_frame_buffers;
  dec_cfg.mcinit_cfg = config->mc_cfg;
  dec_cfg.dump_auxinfo = config->auxinfo;

  rv = VvcDecInit((const void **)&vcdec->inst, config->dwl_inst, &dec_cfg);
#ifdef ASIC_TRACE_SUPPORT
  config->sim_mc = dec_cfg.sim_mc;
#endif
  return rv;
}

static enum DecRet VCDecVvcGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  struct VvcDecInfo vvc_info;
  DWLmemset(&vvc_info, 0, sizeof(struct VvcDecInfo));
  enum DecRet rv = VvcDecGetInfo(vcdec->inst, &vvc_info);
  info->pic_width = vvc_info.pic_width;
  info->pic_height = vvc_info.pic_height;
  info->sar_width = vvc_info.sar_width;
  info->sar_height = vvc_info.sar_height;
  info->crop_params.crop_left_offset = vvc_info.crop_params.crop_left_offset;
  info->crop_params.crop_out_width = vvc_info.crop_params.crop_out_width;
  info->crop_params.crop_top_offset = vvc_info.crop_params.crop_top_offset;
  info->crop_params.crop_out_height = vvc_info.crop_params.crop_out_height;
  info->video_range = vvc_info.video_range;
  info->matrix_coefficients = vvc_info.matrix_coefficients;
  info->is_mono_chrome = vvc_info.mono_chrome;
  info->is_interlaced = vvc_info.interlaced_sequence;
  info->num_of_ref_frames = vvc_info.pic_buff_size;
  info->bit_depth_luma = info->bit_depth_chroma = vvc_info.bit_depth;
  info->chroma_format_idc=vvc_info.chroma_format_idc;
  info->timing_info_present_flag = vvc_info.timing_info_present_flag;
  info->num_units_in_tick = vvc_info.num_units_in_tick;
  info->time_scale = vvc_info.time_scale;
  info->dis_comformance_window = vvc_info.dis_comformance_window;
  return rv;
}

static enum DecRet VCDecVvcSetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct VvcDecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.hw_conceal = config->hw_conceal;
  dec_cfg.disable_slice_mode = config->disable_slice;
  dec_cfg.align = config->align;
  dec_cfg.max_temporal_layer = config->max_temporal_layer;
  DWLmemcpy(dec_cfg.ppu_cfg, config->ppu_cfg, sizeof(config->ppu_cfg));
  DWLmemcpy(dec_cfg.delogo_params, config->delogo_params,sizeof(config->delogo_params));
#if 0
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cfg.ppu_cfg[i].enabled &&
        (!dec_cfg.ppu_cfg[i].scale.enabled ||
         dec_cfg.ppu_cfg[i].scale.scale_by_ratio)) {
      /* Convert fixed ratio scale to ppu_cfg[i] */
      if (!config->ppu_cfg[i].crop.enabled) {
        dec_cfg.ppu_cfg[i].crop.enabled = 1;
        dec_cfg.ppu_cfg[i].crop.x = info->crop_params.crop_left_offset;
        dec_cfg.ppu_cfg[i].crop.y = info->crop_params.crop_top_offset;
        dec_cfg.ppu_cfg[i].crop.width = (info->crop_params.crop_out_width + 1) & (~0x1);
        dec_cfg.ppu_cfg[i].crop.height = (info->crop_params.crop_out_height + 1) & (~0x1);
      }
      if (dec_cfg.ppu_cfg[i].scale.scale_by_ratio) {
        dec_cfg.ppu_cfg[i].scale.enabled = 1;
        dec_cfg.ppu_cfg[i].scale.width = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.width,
                                                         dec_cfg.ppu_cfg[i].scale.ratio_x);
        dec_cfg.ppu_cfg[i].scale.height = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.height,
                                                          dec_cfg.ppu_cfg[i].scale.ratio_y);
      }
    }
  }
#endif
  return VvcDecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecVvcDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  struct VvcDecInput vvc_input;
  struct DecOutput vvc_output;
  DWLmemset(&vvc_input, 0, sizeof(vvc_input));
  DWLmemset(&vvc_output, 0, sizeof(vvc_output));
  vvc_input.stream = param->stream;
  vvc_input.stream_bus_address = param->stream_buffer.bus_address +
                                ((addr_t)param->stream - (addr_t)param->stream_buffer.virtual_address);
  vvc_input.data_len = param->strm_len;
  vvc_input.buffer = (u8 *)param->stream_buffer.virtual_address;
  vvc_input.buffer_bus_address = param->stream_buffer.bus_address;
  vvc_input.buff_len = param->stream_buffer.size;
  vvc_input.pic_id = param->pic_id;
  vvc_input.skip_frame= param->skip_frame;
  vvc_input.sei_buffer = param->sei_buffer;
  vvc_input.p_user_data = param->p_user_data;

  /* TODO(vmr): vvc must not acquire the resources automatically after
   *            successful header decoding. */
  rv = VvcDecDecode(vcdec->inst, &vvc_input, &vvc_output);
  output->strm_curr_pos = vvc_output.strm_curr_pos;
  output->strm_curr_bus_address = vvc_output.strm_curr_bus_address;
  output->data_left = vvc_output.data_left;
  if (param->low_latency) {
    u32 data_consumed = 0;
    if (vvc_output.strm_curr_pos < param->stream) {
      data_consumed += (u32)(vvc_output.strm_curr_pos + param->stream_buffer.size - (u8*)param->stream);
    } else {
      data_consumed += (u32)(vvc_output.strm_curr_pos - param->stream);
    }
    output->data_left = param->frame_len - data_consumed;
    if (data_consumed >= param->frame_len) {
      output->data_left = 0;
      data_consumed = 0;
      param->pic_decoded = 1;
    }
  }
  return rv;
}

static enum DecRet VCDecVvcNextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  enum DecRet rv;
  u32 stride, stride_ch, i;
  struct VvcDecPicture hpic;
  DWLmemset(&hpic, 0, sizeof(struct VvcDecPicture));
  rv = VvcDecNextPicture(vcdec->inst, &hpic);

  DWLmemset(pic, 0, sizeof(struct DecPictures));
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    if (!hpic.pp_enabled) {
      stride = hpic.pictures[0].pic_stride;
      stride_ch = hpic.pictures[0].pic_stride_ch;
    } else {
      stride = hpic.pictures[i].pic_stride;
      stride_ch = hpic.pictures[i].pic_stride_ch;
    }
    pic->pictures[i].luma.virtual_address = (u32*)hpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = hpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].dmv.virtual_address = (u32*)hpic.output_dmv;
    pic->pictures[i].dmv.bus_address = hpic.output_dmv_bus_address;
    pic->pictures[i].dmv.logical_size = hpic.dmv_size;
    pic->pictures[i].qp.virtual_address = (u32*)hpic.output_qp;
    pic->pictures[i].qp.bus_address = hpic.output_qp_bus_address;
    pic->pictures[i].qp.logical_size = hpic.qp_size;

    if (IS_PIC_TILE(hpic.pictures[i].output_format)) {
      pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 4) / 4);
      pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
    } else if (IS_PIC_PLANAR(hpic.pictures[i].output_format)) {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
      pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height;
    } else if (hpic.pictures[i].output_format == DEC_OUT_FRM_RFC) {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height / 4;
      pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 8;
    } else if (IS_PIC_REF_TILED8x8(hpic.pictures[i].output_format)) {
        pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 8) / 8);
        pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
    } else {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
      if (!IS_PIC_RGB(hpic.pictures[i].output_format))
        pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 2;
    }
    /* TODO temporal solution to set chroma base here */
    pic->pictures[i].chroma.virtual_address = (u32*)hpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = hpic.pictures[i].output_picture_chroma_bus_address;
    /* TODO(vmr): find out for real also if it is B frame */
    // pic->pictures[i].picture_info.pic_coding_type =
    //   hpic.is_idr_picture ? DEC_PIC_TYPE_I : DEC_PIC_TYPE_P;
    pic->pictures[i].picture_info.pic_coding_type = hpic.pic_coding_type;
    pic->pictures[i].picture_info.format = hpic.pictures[i].output_format;
    pic->pictures[i].picture_info.pic_id = hpic.pic_id;
    pic->pictures[i].picture_info.decode_id = hpic.decode_id;
    pic->pictures[i].picture_info.cycles_per_mb = hpic.cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
    pic->pictures[i].picture_info.bitrate_4k60fps = hpic.bitrate_per_mb;
    pic->pictures[i].picture_info.bwrd_in_fs = hpic.bwrd_per_mb;
    pic->pictures[i].picture_info.bwwr_in_fs = hpic.bwwr_per_mb;
#endif
    pic->pictures[i].picture_info.luma_stride = hpic.pictures[i].pic_stride;
    pic->pictures[i].picture_info.chroma_stride = hpic.pictures[i].pic_stride_ch;
    pic->pictures[i].sequence_info.pic_width = hpic.pictures[i].pic_width;
    pic->pictures[i].sequence_info.pic_height = hpic.pictures[i].pic_height;
    pic->pictures[i].sequence_info.crop_params.crop_left_offset =
      hpic.crop_params.crop_left_offset;
    pic->pictures[i].sequence_info.crop_params.crop_out_width =
      hpic.crop_params.crop_out_width;
    pic->pictures[i].sequence_info.crop_params.crop_top_offset =
      hpic.crop_params.crop_top_offset;
    pic->pictures[i].sequence_info.crop_params.crop_out_height =
      hpic.crop_params.crop_out_height;
    pic->pictures[i].sequence_info.sar_width = hpic.dec_info.sar_width;
    pic->pictures[i].sequence_info.sar_height = hpic.dec_info.sar_height;
    pic->pictures[i].sequence_info.video_range = hpic.dec_info.video_range;
    pic->pictures[i].sequence_info.matrix_coefficients =
      hpic.dec_info.matrix_coefficients;
    pic->pictures[i].sequence_info.is_mono_chrome = 0;//hpic.dec_info.mono_chrome;
    pic->pictures[i].sequence_info.chroma_format_idc = hpic.dec_info.chroma_format_idc;
    pic->pictures[i].sequence_info.is_interlaced = hpic.dec_info.interlaced_sequence;
    pic->pictures[i].sequence_info.num_of_ref_frames =
      hpic.dec_info.pic_buff_size;
    pic->pictures[i].sequence_info.bit_depth_luma = hpic.bit_depth_luma;
    pic->pictures[i].sequence_info.bit_depth_chroma = hpic.bit_depth_chroma;
    pic->pictures[i].sei_param.vvc = hpic.sei_param; /*sei_param */
    pic->pictures[i].pic_width = hpic.pictures[i].pic_width;
    pic->pictures[i].pic_height = hpic.pictures[i].pic_height;
    pic->pictures[i].pic_stride = hpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = hpic.pictures[i].pic_stride_ch;
    pic->pictures[i].chroma_format = hpic.pictures[i].chroma_format;
    pic->pictures[i].pp_enabled = hpic.pp_enabled;
  }
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    if (pic->pictures[i].luma.size) {
#ifdef SUPPORT_DEC400
      pic->pictures[i].luma_table.virtual_address = hpic.pictures[i].dec400_luma_table.virtual_address;
      pic->pictures[i].luma_table.bus_address= hpic.pictures[i].dec400_luma_table.bus_address;
      pic->pictures[i].luma_table.size = hpic.pictures[i].dec400_luma_table.size;
      if (pic->pictures[i].chroma.virtual_address) {
        pic->pictures[i].chroma_table.virtual_address = hpic.pictures[i].dec400_chroma_table.virtual_address;
        pic->pictures[i].chroma_table.bus_address= hpic.pictures[i].dec400_chroma_table.bus_address;
        pic->pictures[i].chroma_table.size = hpic.pictures[i].dec400_chroma_table.size;
      }
#endif
    }
  }

  return rv;
}

static enum DecRet VCDecVvcPictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  struct VvcDecPicture hpic;
  u32 i;
  DWLmemset(&hpic, 0, sizeof(struct VvcDecPicture));
  /* TODO update chroma luma/chroma base */
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    hpic.pictures[i].output_picture = pic->pictures[i].luma.virtual_address;
    hpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  hpic.output_dmv = pic->pictures[0].dmv.virtual_address;
  hpic.output_dmv_bus_address = pic->pictures[0].dmv.bus_address;
  hpic.is_idr_picture = pic->pictures[0].picture_info.pic_coding_type == DEC_PIC_TYPE_I;
  hpic.sei_param = pic->pictures[0].sei_param.vvc; /* sei_param */
  return VvcDecPictureConsumed(vcdec->inst, &hpic);
}

static enum DecRet VCDecVvcEndOfStream(VCDecInst *vcdec) {
  return VvcDecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecVvcGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  DWLmemset(&hbuf, 0, sizeof(hbuf));
  enum DecRet rv;

  rv = VvcDecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->buf_to_free = hbuf.buf_to_free;
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->add_extra_ext_buf = hbuf.add_extra_ext_buf;
  return rv;
}

static enum DecRet VCDecVvcAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return VvcDecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecVvcUseExtraFrmBuffers(VCDecInst *vcdec, u32 n) {
  return VvcDecUseExtraFrmBuffers(vcdec->inst, n);
}

static enum DecRet VCDecVvcPeek(VCDecInst *vcdec, struct DecPictures *pic) {
  // struct VvcDecPicture hpic;
  // u32 i;
  // DWLmemset(&hpic, 0, sizeof(struct VvcDecPicture));
  // return VvcDecPeek(vcdec->inst, &pic);
  enum DecRet rv = {0};
  return rv;
}

static enum DecRet VCDecVvcAbort(VCDecInst *vcdec) {
  return VvcDecAbort(vcdec->inst);
}

static enum DecRet VCDecVvcAbortAfter(VCDecInst *vcdec) {
  return VvcDecAbortAfter(vcdec->inst);
}

static void VCDecVvcSetNoReorder(VCDecInst *vcdec, u32 no_reorder) {
  VvcDecSetNoReorder(vcdec->inst, no_reorder);
}

static void VCDecVvcRelease(VCDecInst *vcdec) {
  VvcDecRelease(vcdec->inst);
}

static void VCDecVvcUpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  VvcDecUpdateStrmInfoCtrl(vcdec->inst, info);
}

#endif /* ENABLE_VVC_SUPPORT */

#ifdef ENABLE_HEVC_SUPPORT
static enum DecRet VCDecHevcInit(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct HevcDecConfig dec_cfg = {0, };
  enum DecRet rv = 0;
  dec_cfg.multi_frame_input_flag = config->multi_frame_input_flag;
  dec_cfg.no_output_reordering = config->disable_picture_reordering;
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_video_compressor = config->use_video_compressor;
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.num_buffers = config->num_frame_buffers;
  dec_cfg.mcinit_cfg = config->mc_cfg;
  dec_cfg.dump_auxinfo = config->auxinfo;

  rv = HevcDecInit((const void **)&vcdec->inst, config->dwl_inst, &dec_cfg);
#ifdef ASIC_TRACE_SUPPORT
  config->sim_mc = dec_cfg.sim_mc;
#endif
  return rv;
}

static enum DecRet VCDecHevcGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  struct HevcDecInfo hevc_info;
  DWLmemset(&hevc_info, 0, sizeof(struct HevcDecInfo));
  enum DecRet rv = HevcDecGetInfo(vcdec->inst, &hevc_info);
  info->pic_width = hevc_info.pic_width;
  info->pic_height = hevc_info.pic_height;
  info->sar_width = hevc_info.sar_width;
  info->sar_height = hevc_info.sar_height;
  info->crop_params.crop_left_offset = hevc_info.crop_params.crop_left_offset;
  info->crop_params.crop_out_width = hevc_info.crop_params.crop_out_width;
  info->crop_params.crop_top_offset = hevc_info.crop_params.crop_top_offset;
  info->crop_params.crop_out_height = hevc_info.crop_params.crop_out_height;
  info->video_range = hevc_info.video_range;
  info->matrix_coefficients = hevc_info.matrix_coefficients;
  info->is_mono_chrome = hevc_info.mono_chrome;
  info->is_interlaced = hevc_info.interlaced_sequence;
  info->num_of_ref_frames = hevc_info.pic_buff_size;
  info->bit_depth_luma = info->bit_depth_chroma = hevc_info.bit_depth;
  info->chroma_format_idc=hevc_info.chroma_format_idc;
  info->timing_info_present_flag = hevc_info.timing_info_present_flag;
  info->num_units_in_tick = hevc_info.num_units_in_tick;
  info->time_scale = hevc_info.time_scale;
  info->trc_status = hevc_info.trc_status;
  info->transfer_characteristics = hevc_info.transfer_characteristics;
  info->preferred_transfer_characteristics = hevc_info.preferred_transfer_characteristics;
  return rv;
}

static enum DecRet VCDecHevcSetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct HevcDecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.hw_conceal = config->hw_conceal;
  dec_cfg.disable_slice_mode = config->disable_slice;
  dec_cfg.align = config->align;
  dec_cfg.max_temporal_layer = config->max_temporal_layer;
  DWLmemcpy(dec_cfg.ppu_cfg, config->ppu_cfg, sizeof(config->ppu_cfg));
  DWLmemcpy(dec_cfg.delogo_params, config->delogo_params,sizeof(config->delogo_params));
#if 0
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cfg.ppu_cfg[i].enabled &&
        (!dec_cfg.ppu_cfg[i].scale.enabled ||
         dec_cfg.ppu_cfg[i].scale.scale_by_ratio)) {
      /* Convert fixed ratio scale to ppu_cfg[i] */
      if (!config->ppu_cfg[i].crop.enabled) {
        dec_cfg.ppu_cfg[i].crop.enabled = 1;
        dec_cfg.ppu_cfg[i].crop.x = info->crop_params.crop_left_offset;
        dec_cfg.ppu_cfg[i].crop.y = info->crop_params.crop_top_offset;
        dec_cfg.ppu_cfg[i].crop.width = (info->crop_params.crop_out_width + 1) & (~0x1);
        dec_cfg.ppu_cfg[i].crop.height = (info->crop_params.crop_out_height + 1) & (~0x1);
      }
      if (dec_cfg.ppu_cfg[i].scale.scale_by_ratio) {
        dec_cfg.ppu_cfg[i].scale.enabled = 1;
        dec_cfg.ppu_cfg[i].scale.width = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.width,
                                                         dec_cfg.ppu_cfg[i].scale.ratio_x);
        dec_cfg.ppu_cfg[i].scale.height = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.height,
                                                          dec_cfg.ppu_cfg[i].scale.ratio_y);
      }
    }
  }
#endif
  return HevcDecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecHevcDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  struct HevcDecInput hevc_input;
  struct DecOutput hevc_output;
  DWLmemset(&hevc_input, 0, sizeof(hevc_input));
  DWLmemset(&hevc_output, 0, sizeof(hevc_output));
  hevc_input.stream = param->stream;
  hevc_input.stream_bus_address = param->stream_buffer.bus_address +
                                ((addr_t)param->stream - (addr_t)param->stream_buffer.virtual_address);
  hevc_input.data_len = param->strm_len;
  hevc_input.buffer = (u8 *)param->stream_buffer.virtual_address;
  hevc_input.buffer_bus_address = param->stream_buffer.bus_address;
  hevc_input.buff_len = param->stream_buffer.size;
  hevc_input.pic_id = param->pic_id;
  hevc_input.skip_frame= param->skip_frame;
  hevc_input.sei_buffer = param->sei_buffer;
  hevc_input.p_user_data = param->p_user_data;

  /* TODO(vmr): hevc must not acquire the resources automatically after
   *            successful header decoding. */
  rv = HevcDecDecode(vcdec->inst, &hevc_input, &hevc_output);
  output->strm_curr_pos = hevc_output.strm_curr_pos;
  output->strm_curr_bus_address = hevc_output.strm_curr_bus_address;
  output->data_left = hevc_output.data_left;
  if (param->low_latency) {
    u32 data_consumed = 0;
    if (hevc_output.strm_curr_pos < param->stream) {
      data_consumed += (u32)(hevc_output.strm_curr_pos + param->stream_buffer.size - (u8*)param->stream);
    } else {
      data_consumed += (u32)(hevc_output.strm_curr_pos - param->stream);
    }
    output->data_left = param->frame_len - data_consumed;
    if (data_consumed >= param->frame_len) {
      output->data_left = 0;
      data_consumed = 0;
      param->pic_decoded = 1;
    }
  }
  return rv;
}

static enum DecRet VCDecHevcNextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  enum DecRet rv;
  u32 stride, stride_ch, i, index;
  struct HevcDecPicture hpic;
  DWLmemset(&hpic, 0, sizeof(struct HevcDecPicture));
  rv = HevcDecNextPicture(vcdec->inst, &hpic);
  if (rv != DEC_OK)
    APITRACE("VCDecHevcNextPicture# %s",ParseDecRet(rv));

  if (rv != DEC_PIC_RDY)
    return rv;

  index = hpic.pp_enabled ? DEC_MAX_OUT_COUNT : 1;
  DWLmemset(pic, 0, sizeof(struct DecPictures));
  for (i = 0; i < index; i++) {
    if (!hpic.pp_enabled) {
      stride = hpic.pictures[0].pic_stride;
      stride_ch = hpic.pictures[0].pic_stride_ch;
    } else {
      stride = hpic.pictures[i].pic_stride;
      stride_ch = hpic.pictures[i].pic_stride_ch;
    }
    pic->pictures[i].luma.virtual_address = (u32*)hpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = hpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].dmv.virtual_address = (u32*)hpic.output_dmv;
    pic->pictures[i].dmv.bus_address = hpic.output_dmv_bus_address;
    pic->pictures[i].dmv.logical_size = hpic.dmv_size;
    pic->pictures[i].qp.virtual_address = (u32*)hpic.output_qp;
    pic->pictures[i].qp.bus_address = hpic.output_qp_bus_address;
    pic->pictures[i].qp.logical_size = hpic.qp_size;
    pic->pictures[i].is_gdr_frame = hpic.is_gdr_frame;

    if (IS_PIC_TILE(hpic.pictures[i].output_format)) {
      pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 4) / 4);
      pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
    } else if (IS_PIC_PLANAR(hpic.pictures[i].output_format)) {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
      pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height;
    } else if (hpic.pictures[i].output_format == DEC_OUT_FRM_RFC) {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height / 4;
      pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 8;
    } else if (IS_PIC_REF_TILED8x8(hpic.pictures[i].output_format)) {
        pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 8) / 8);
        pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
      } else {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
      if (!IS_PIC_RGB(hpic.pictures[i].output_format))
        pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 2;
    }
    /* TODO temporal solution to set chroma base here */
    pic->pictures[i].chroma.virtual_address = (u32*)hpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = hpic.pictures[i].output_picture_chroma_bus_address;
    /* TODO(vmr): find out for real also if it is B frame */
    // pic->pictures[i].picture_info.pic_coding_type =
    //   hpic.is_idr_picture ? DEC_PIC_TYPE_I : DEC_PIC_TYPE_P;
    pic->pictures[i].picture_info.pic_coding_type = hpic.pic_coding_type;
    pic->pictures[i].picture_info.format = hpic.pictures[i].output_format;
    pic->pictures[i].picture_info.pic_id = hpic.pic_id;
    pic->pictures[i].picture_info.poc = hpic.poc;
    pic->pictures[i].picture_info.cycles_per_mb = hpic.cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
    pic->pictures[i].picture_info.bitrate_4k60fps = hpic.bitrate_4k60fps;
    pic->pictures[i].picture_info.bwrd_in_fs = hpic.bwrd_in_fs;
    pic->pictures[i].picture_info.bwwr_in_fs = hpic.bwwr_in_fs;
#endif
    pic->pictures[i].picture_info.luma_stride = hpic.pictures[i].pic_stride;
    pic->pictures[i].picture_info.chroma_stride = hpic.pictures[i].pic_stride_ch;
    pic->pictures[i].sequence_info.pic_width = hpic.pictures[i].pic_width;
    pic->pictures[i].sequence_info.pic_height = hpic.pictures[i].pic_height;
    pic->pictures[i].sequence_info.crop_params.crop_left_offset =
      hpic.crop_params.crop_left_offset;
    pic->pictures[i].sequence_info.crop_params.crop_out_width =
      hpic.crop_params.crop_out_width;
    pic->pictures[i].sequence_info.crop_params.crop_top_offset =
      hpic.crop_params.crop_top_offset;
    pic->pictures[i].sequence_info.crop_params.crop_out_height =
      hpic.crop_params.crop_out_height;
    pic->pictures[i].sequence_info.sar_width = hpic.dec_info.sar_width;
    pic->pictures[i].sequence_info.sar_height = hpic.dec_info.sar_height;
    pic->pictures[i].sequence_info.video_range = hpic.dec_info.video_range;
    pic->pictures[i].sequence_info.matrix_coefficients =
      hpic.dec_info.matrix_coefficients;
    pic->pictures[i].sequence_info.is_mono_chrome = 0;//hpic.dec_info.mono_chrome;
    pic->pictures[i].sequence_info.chroma_format_idc = hpic.dec_info.chroma_format_idc;
    pic->pictures[i].sequence_info.is_interlaced = hpic.dec_info.interlaced_sequence;
    pic->pictures[i].sequence_info.num_of_ref_frames =
      hpic.dec_info.pic_buff_size;
    pic->pictures[i].sequence_info.bit_depth_luma = hpic.bit_depth_luma;
    pic->pictures[i].sequence_info.bit_depth_chroma = hpic.bit_depth_chroma;
    pic->pictures[i].sei_param.hevc = hpic.sei_param; /*sei_param */
    pic->pictures[i].pic_width = hpic.pictures[i].pic_width;
    pic->pictures[i].pic_height = hpic.pictures[i].pic_height;
    pic->pictures[i].pic_stride = hpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = hpic.pictures[i].pic_stride_ch;
    pic->pictures[i].chroma_format = hpic.pictures[i].chroma_format;
    pic->pictures[i].pp_enabled = hpic.pp_enabled;
  }
  for (i = 0; i < index; i++) {
    if (!hpic.pp_enabled || IS_PIC_DEC400(hpic.pictures[i].output_format)) {
      if (pic->pictures[i].luma.size) {
        DWLmemcpy(&pic->pictures[i].luma_table, &hpic.pictures[i].luma_table, sizeof(hpic.pictures[i].luma_table));
        if (pic->pictures[i].chroma.virtual_address) {
          DWLmemcpy(&pic->pictures[i].chroma_table, &hpic.pictures[i].chroma_table, sizeof(hpic.pictures[i].chroma_table));
        }
      }
    }
  }

  return DEC_PIC_RDY;
}

static enum DecRet VCDecHevcPictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  struct HevcDecPicture hpic;
  u32 i;
  DWLmemset(&hpic, 0, sizeof(struct HevcDecPicture));
  /* TODO update chroma luma/chroma base */
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    hpic.pictures[i].output_picture = pic->pictures[i].luma.virtual_address;
    hpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  hpic.output_dmv = pic->pictures[0].dmv.virtual_address;
  hpic.output_dmv_bus_address = pic->pictures[0].dmv.bus_address;
  hpic.is_idr_picture = pic->pictures[0].picture_info.pic_coding_type == DEC_PIC_TYPE_I;
  hpic.sei_param = pic->pictures[0].sei_param.hevc; /* sei_param */
  return HevcDecPictureConsumed(vcdec->inst, &hpic);
}

static enum DecRet VCDecHevcEndOfStream(VCDecInst *vcdec) {
  return HevcDecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecHevcGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  DWLmemset(&hbuf, 0, sizeof(hbuf));
  enum DecRet rv;
  u32 i;

  rv = HevcDecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->buf_to_free = hbuf.buf_to_free;
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->add_extra_ext_buf = hbuf.add_extra_ext_buf;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecHevcAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return HevcDecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecHevcUseExtraFrmBuffers(VCDecInst *vcdec, u32 n) {
  return HevcDecUseExtraFrmBuffers(vcdec->inst, n);
}

static enum DecRet VCDecHevcPeek(VCDecInst *vcdec, struct DecPictures *pic) {
  // struct HevcDecPicture hpic;
  // u32 i;
  // DWLmemset(&hpic, 0, sizeof(struct HevcDecPicture));
  // return HevcDecPeek(vcdec->inst, &pic);
  enum DecRet rv = {0};
  return rv;
}

static enum DecRet VCDecHevcAbort(VCDecInst *vcdec) {
  return HevcDecAbort(vcdec->inst);
}

static enum DecRet VCDecHevcAbortAfter(VCDecInst *vcdec) {
  return HevcDecAbortAfter(vcdec->inst);
}

static void VCDecHevcSetNoReorder(VCDecInst *vcdec, u32 no_reorder) {
  HevcDecSetNoReorder(vcdec->inst, no_reorder);
}

static void VCDecHevcRelease(VCDecInst *vcdec) {
  HevcDecRelease(vcdec->inst);
}

static void VCDecHevcUpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  HevcDecUpdateStrmInfoCtrl(vcdec->inst, info);
}

#endif /* ENABLE_HEVC_SUPPORT */

#ifdef ENABLE_H264_SUPPORT
static enum DecRet VCDecH264Init(VCDecInst *vcdec, struct DecInitConfig* config) {
  struct H264DecConfig dec_cfg = {0, };
  enum DecRet rv;
  dec_cfg.multi_frame_input_flag = config->multi_frame_input_flag;
  dec_cfg.no_output_reordering = config->disable_picture_reordering;
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_video_compressor = config->use_video_compressor;
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.mcinit_cfg = config->mc_cfg;
  dec_cfg.rlc_mode = config->rlc_mode;
  dec_cfg.dump_auxinfo = config->auxinfo;
  dec_cfg.mvc = config->mvc;
  dec_cfg.support_asofmo_stream = config->support_asofmo_stream;

  rv = H264DecInit((const void **)&vcdec->inst, config->dwl_inst, &dec_cfg);
#ifdef ASIC_TRACE_SUPPORT
  config->sim_mc = dec_cfg.sim_mc;
#endif
  return rv;
}

static enum DecRet VCDecH264GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  H264DecInfo h264_info;
  DWLmemset(&h264_info, 0, sizeof(h264_info));
  enum DecRet rv = (enum DecRet)H264DecGetInfo(vcdec->inst, &h264_info);
  info->pic_width = h264_info.pic_width;
  info->pic_height = h264_info.pic_height;
  info->video_range = h264_info.video_range;
  info->matrix_coefficients = h264_info.matrix_coefficients;
  info->crop_params.crop_left_offset = h264_info.crop_params.crop_left_offset;
  info->crop_params.crop_out_width = h264_info.crop_params.crop_out_width;
  info->crop_params.crop_top_offset = h264_info.crop_params.crop_top_offset;
  info->crop_params.crop_out_height = h264_info.crop_params.crop_out_height;
  info->sar_width = h264_info.sar_width;
  info->sar_height = h264_info.sar_height;
  info->is_mono_chrome = h264_info.mono_chrome;
  info->is_interlaced = h264_info.interlaced_sequence;
  info->num_of_ref_frames = h264_info.pic_buff_size;
  info->bit_depth_luma = info->bit_depth_chroma = h264_info.bit_depth;
  info->pp_enabled = h264_info.pp_enabled;
  info->h264_base_mode = h264_info.base_mode;
  info->chroma_format_idc=h264_info.chroma_format_idc;
  info->timing_info_present_flag = h264_info.timing_info_present_flag;
  info->num_units_in_tick = h264_info.num_units_in_tick;
  info->time_scale = h264_info.time_scale;
  return rv;
}

static enum DecRet VCDecH264SetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct H264DecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.hw_conceal = config->hw_conceal;
  dec_cfg.disable_slice_mode = config->disable_slice;
  dec_cfg.align = config->align;
  dec_cfg.max_temporal_layer = config->max_temporal_layer;
  DWLmemcpy(dec_cfg.ppu_cfg, config->ppu_cfg, sizeof(config->ppu_cfg));
  DWLmemcpy(dec_cfg.delogo_params, config->delogo_params,sizeof(config->delogo_params));
#if 0
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cfg.ppu_cfg[i].enabled &&
        (!dec_cfg.ppu_cfg[i].scale.enabled ||
         dec_cfg.ppu_cfg[i].scale.scale_by_ratio)) {
      /* Convert fixed ratio scale to ppu_cfg[i] */
      if (!config->ppu_cfg[i].crop.enabled) {
        dec_cfg.ppu_cfg[i].crop.enabled = 1;
        dec_cfg.ppu_cfg[i].crop.x = info->crop_params.crop_left_offset;
        dec_cfg.ppu_cfg[i].crop.y = info->crop_params.crop_top_offset;
        dec_cfg.ppu_cfg[i].crop.width = (info->crop_params.crop_out_width + 1) & (~0x1);
        dec_cfg.ppu_cfg[i].crop.height = (info->crop_params.crop_out_height + 1) & (~0x1);
      }
      if (dec_cfg.ppu_cfg[i].scale.scale_by_ratio) {
        dec_cfg.ppu_cfg[i].scale.enabled = 1;
        dec_cfg.ppu_cfg[i].scale.width = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.width,
                                                         dec_cfg.ppu_cfg[i].scale.ratio_x);
        dec_cfg.ppu_cfg[i].scale.height = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.height,
                                                          dec_cfg.ppu_cfg[i].scale.ratio_y);
      }
    }
  }
#endif
  return (enum DecRet)H264DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecH264Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  H264DecInput H264_input;
  struct DecOutput H264_output;
  DWLmemset(&H264_input, 0, sizeof(H264_input));
  DWLmemset(&H264_output, 0, sizeof(H264_output));
  H264_input.stream = (u8*)param->stream;
  H264_input.stream_bus_address = param->stream_buffer.bus_address +
                                  ((addr_t)param->stream - (addr_t)param->stream_buffer.virtual_address);
  H264_input.data_len = param->strm_len;
  H264_input.buffer = (u8 *)param->stream_buffer.virtual_address;
  H264_input.buffer_bus_address = param->stream_buffer.bus_address;
  H264_input.buff_len = param->stream_buffer.size;
  H264_input.pic_id = param->pic_id;
  H264_input.skip_frame= param->skip_frame;
  H264_input.p_user_data = param->p_user_data;
  H264_input.sei_buffer = param->sei_buffer;

  /* TODO(vmr): H264 must not acquire the resources automatically after
   *            successful header decoding. */
  rv = H264DecDecode(vcdec->inst, &H264_input, &H264_output);
  output->strm_curr_pos = H264_output.strm_curr_pos;
  output->strm_curr_bus_address = H264_output.strm_curr_bus_address;
  output->data_left = H264_output.data_left;
  if (param->low_latency) {
    u32 data_consumed = 0;
    if (H264_output.strm_curr_pos < param->stream) {
      data_consumed += (u32)(H264_output.strm_curr_pos + param->stream_buffer.size - (u8*)param->stream);
    } else {
      data_consumed += (u32)(H264_output.strm_curr_pos - param->stream);
    }
    output->data_left = param->frame_len - data_consumed;
    if (data_consumed >= param->frame_len || (data_consumed && (rv == DEC_PIC_DECODED))) {
      output->data_left = 0;
      data_consumed = 0;
      param->pic_decoded = 1;
    }
    if (rv == DEC_STREAM_NOT_SUPPORTED) {
      param->exit_send_thread = 1;
    }
  }
  return rv;
}

static enum DecRet VCDecH264NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  enum DecRet rv;
  u32 stride, stride_ch, i;
  H264DecPicture hpic;
  DWLmemset(&hpic, 0, sizeof(hpic));
  rv = H264DecNextPicture(vcdec->inst, &hpic, 0);

  DWLmemset(pic, 0, sizeof(struct DecPictures));
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    stride = hpic.pictures[i].pic_stride;
    stride_ch = hpic.pictures[i].pic_stride_ch;
    pic->pictures[i].luma.virtual_address = (u32*)hpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = hpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].dmv.virtual_address = (u32*)hpic.output_dmv;
    pic->pictures[i].dmv.bus_address = hpic.output_dmv_bus_address;
    pic->pictures[i].dmv.logical_size = hpic.dmv_size;
    pic->pictures[i].qp.virtual_address = (u32*)hpic.output_qp;
    pic->pictures[i].qp.bus_address = hpic.output_qp_bus_address;
    pic->pictures[i].qp.logical_size = hpic.qp_size;
    pic->pictures[i].is_gdr_frame = hpic.is_gdr_frame;
#if 0
  if (hpic.output_format == DEC_OUT_FRM_RASTER_SCAN)
    hpic.pic_width = NEXT_MULTIPLE(hpic.pic_width, 16);
#endif
    if (IS_PIC_TILE(hpic.pictures[i].output_format)) {
      pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 4) / 4);
      pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
    } else if (IS_PIC_PLANAR(hpic.pictures[i].output_format)) {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
      pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height;
    } else if (hpic.pictures[i].output_format == DEC_OUT_FRM_RFC) {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height / 4;
      pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 8;
    } else if (IS_PIC_REF_TILED8x8(hpic.pictures[i].output_format)) {
        pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 8) / 8);
        pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
      } else {
      pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
      if (!IS_PIC_RGB(hpic.pictures[i].output_format))
        pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 2;
    }
    /* TODO temporal solution to set chroma base here */
    pic->pictures[i].chroma.virtual_address = (u32*)hpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = hpic.pictures[i].output_picture_chroma_bus_address;
    /* TODO(vmr): find out for real also if it is B frame */
    pic->pictures[i].picture_info.pic_coding_type = hpic.pic_coding_type[0];
    pic->pictures[i].picture_info.format = hpic.pictures[i].output_format;
    pic->pictures[i].picture_info.pic_id = hpic.pic_id;
    pic->pictures[i].picture_info.decode_id = hpic.decode_id[0];
    pic->pictures[i].picture_info.cycles_per_mb = hpic.cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
    pic->pictures[i].picture_info.bitrate_4k60fps = hpic.bitrate_4k60fps;
    pic->pictures[i].picture_info.bwrd_in_fs = hpic.bwrd_in_fs;
    pic->pictures[i].picture_info.bwwr_in_fs = hpic.bwwr_in_fs;
#endif
    pic->pictures[i].sequence_info.pic_width = hpic.pictures[i].pic_width;
    pic->pictures[i].sequence_info.pic_height = hpic.pictures[i].pic_height;
    pic->pictures[i].sequence_info.crop_params.crop_left_offset =
      hpic.crop_params.crop_left_offset;
    pic->pictures[i].sequence_info.crop_params.crop_out_width =
      hpic.crop_params.crop_out_width;
    pic->pictures[i].sequence_info.crop_params.crop_top_offset =
      hpic.crop_params.crop_top_offset;
    pic->pictures[i].sequence_info.crop_params.crop_out_height =
      hpic.crop_params.crop_out_height;
    pic->pictures[i].sequence_info.sar_width = hpic.sar_width;
    pic->pictures[i].sequence_info.sar_height = hpic.sar_height;
    pic->pictures[i].sequence_info.video_range = 0; //hpic.video_range;
    pic->pictures[i].sequence_info.matrix_coefficients =
      0; //hpic.matrix_coefficients;
    pic->pictures[i].sequence_info.is_mono_chrome =
      0; //hpic.mono_chrome;
    pic->pictures[i].sequence_info.chroma_format_idc = hpic.chroma_format_idc;
    pic->pictures[i].sequence_info.is_interlaced = hpic.interlaced;
    pic->pictures[i].sequence_info.num_of_ref_frames =
      0; //hpic.dec_info.pic_buff_size;
    pic->pictures[i].sequence_info.bit_depth_luma = hpic.bit_depth_luma;
    pic->pictures[i].sequence_info.bit_depth_chroma = hpic.bit_depth_chroma;
    pic->pictures[i].sei_param.h264[0] = hpic.sei_param[0]; /*sei_param */
    pic->pictures[i].sei_param.h264[1] = hpic.sei_param[1]; /*sei_param */
    pic->pictures[i].pic_width = hpic.pictures[i].pic_width;
    pic->pictures[i].pic_height = hpic.pictures[i].pic_height;
    pic->pictures[i].pic_stride = hpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = hpic.pictures[i].pic_stride_ch;
    pic->pictures[i].chroma_format = hpic.pictures[i].chroma_format;
    pic->pictures[i].pp_enabled = 0; //hpic.pp_enabled;
  }
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    if (pic->pictures[i].luma.size) {
#ifdef SUPPORT_DEC400
      DWLmemcpy(&pic->pictures[i].luma_table, &hpic.pictures[i].dec400_luma_table, sizeof(hpic.pictures[i].dec400_luma_table));
      if (pic->pictures[i].chroma.virtual_address) {
        DWLmemcpy(&pic->pictures[i].chroma_table, &hpic.pictures[i].dec400_chroma_table, sizeof(hpic.pictures[i].dec400_chroma_table));
      }
#endif
    }
  }

  return rv;
}

static enum DecRet VCDecH264PictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  H264DecPicture hpic;
  u32 i;
  DWLmemset(&hpic, 0, sizeof(H264DecPicture));
  /* TODO update chroma luma/chroma base */
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    hpic.pictures[i].output_picture = pic->pictures[i].luma.virtual_address;
    hpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  hpic.output_dmv = pic->pictures[0].dmv.virtual_address;
  hpic.output_dmv_bus_address = pic->pictures[0].dmv.bus_address;
  hpic.is_idr_picture[0] = pic->pictures[0].picture_info.pic_coding_type == DEC_PIC_TYPE_I;
  hpic.sei_param[0] = pic->pictures[0].sei_param.h264[0]; /* sei_param */
  hpic.sei_param[1] = pic->pictures[0].sei_param.h264[1]; /* sei_param */
  return H264DecPictureConsumed(vcdec->inst, &hpic);
}

static enum DecRet VCDecH264EndOfStream(VCDecInst *vcdec) {
  return H264DecEndOfStream(vcdec->inst, 1);
}

static enum DecRet VCDecH264GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  DWLmemset(&hbuf, 0, sizeof(hbuf));
  enum DecRet rv;
  u32 i;

  rv = H264DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->buf_to_free = hbuf.buf_to_free;
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecH264AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return H264DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecH264Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  // return H264DecPeek(vcdec->inst, pic);
  enum DecRet rv = {0};
  return rv;
}

static enum DecRet VCDecH264Abort(VCDecInst *vcdec) {
  return H264DecAbort(vcdec->inst);
}

static enum DecRet VCDecH264AbortAfter(VCDecInst *vcdec) {
  return H264DecAbortAfter(vcdec->inst);
}

static void VCDecH264SetNoReorder(VCDecInst *vcdec, u32 no_reorder) {
  H264DecSetNoReorder(vcdec->inst, no_reorder);
}

static void VCDecH264Release(VCDecInst *vcdec) {
  H264DecRelease(vcdec->inst);
}

static void VCDecH264UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  H264DecUpdateStrmInfoCtrl(vcdec->inst, info);
}

#endif /* ENABLE_H264_SUPPORT */

#ifdef ENABLE_VP9_SUPPORT
static enum DecRet VCDecVp9Init(VCDecInst *vcdec, struct DecInitConfig* config) {
  vcdec->sf_num_frms = 0;
  vcdec->sf_cur_frm_id = 0;
  DWLmemset(vcdec->sf_frm_sizes, 0, sizeof(vcdec->sf_frm_sizes));

  struct Vp9DecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.num_frame_buffers = 9;
  dec_cfg.use_video_compressor = config->use_video_compressor;
  dec_cfg.tile_transpose =config->tile_transpose;
  dec_cfg.multicore_poll_period = config->multicore_poll_period;
  dec_cfg.mcinit_cfg = config->mc_cfg;
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;

  return Vp9DecInit((const void **)&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecVp9GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  struct Vp9DecInfo vp9_info;
  DWLmemset(&vp9_info, 0, sizeof(vp9_info));
  enum DecRet rv = Vp9DecGetInfo(vcdec->inst, &vp9_info);
  info->pic_width = vp9_info.frame_width;
  info->pic_height = vp9_info.frame_height;
  info->sar_width = 1;
  info->sar_height = 1;
  info->crop_params.crop_left_offset = 0;
  info->crop_params.crop_out_width = vp9_info.coded_width;
  info->crop_params.crop_top_offset = 0;
  info->crop_params.crop_out_height = vp9_info.coded_height;
  /* TODO(vmr): Consider adding scaled_width & scaled_height. */
  info->num_of_ref_frames = vp9_info.pic_buff_size;
  info->video_range = DEC_VIDEO_RANGE_NORMAL;
  info->matrix_coefficients = 0;
  info->is_mono_chrome = 0;
  info->is_interlaced = 0;
  info->bit_depth_luma = info->bit_depth_chroma = vp9_info.bit_depth;
  info->chroma_format_idc = 1;
  return rv;
}

static enum DecRet VCDecVp9SetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct Vp9DecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_cfg, config->ppu_cfg, sizeof(config->ppu_cfg));
  DWLmemcpy(dec_cfg.delogo_params, config->delogo_params,sizeof(config->delogo_params));
#if 0
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cfg.ppu_cfg[i].enabled &&
        (!dec_cfg.ppu_cfg[i].scale.enabled ||
         dec_cfg.ppu_cfg[i].scale.scale_by_ratio)) {
      /* Convert fixed ratio scale to ppu_cfg[i] */
      if (!config->ppu_cfg[i].crop.enabled) {
        dec_cfg.ppu_cfg[i].crop.enabled = 1;
        dec_cfg.ppu_cfg[i].crop.x = info->crop_params.crop_left_offset;
        dec_cfg.ppu_cfg[i].crop.y = info->crop_params.crop_top_offset;
        dec_cfg.ppu_cfg[i].crop.width = (info->crop_params.crop_out_width + 1) & (~0x1);
        dec_cfg.ppu_cfg[i].crop.height = (info->crop_params.crop_out_height + 1) & (~0x1);
      }
      if (dec_cfg.ppu_cfg[i].scale.scale_by_ratio) {
        dec_cfg.ppu_cfg[i].scale.enabled = 1;
        dec_cfg.ppu_cfg[i].scale.width = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.width,
                                                         dec_cfg.ppu_cfg[i].scale.ratio_x);
        dec_cfg.ppu_cfg[i].scale.height = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.height,
                                                          dec_cfg.ppu_cfg[i].scale.ratio_y);
      }
    }
  }
#endif
  return Vp9DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecVp9Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv = DEC_OK;
  struct Vp9DecInput vp9_input;
  struct DecOutput vp9_output;
  DWLmemset(&vp9_input, 0, sizeof(vp9_input));
  DWLmemset(&vp9_output, 0, sizeof(vp9_output));
  vp9_input.stream = (u8*)param->stream;
  vp9_input.stream_bus_address = param->stream_buffer.bus_address +
                                 ((addr_t)param->stream - (addr_t)param->stream_buffer.virtual_address);
  vp9_input.data_len = param->strm_len;
  vp9_input.frame_len = param->frame_len;
  vp9_input.buffer = (u8*)param->stream_buffer.virtual_address;
  vp9_input.buffer_bus_address = param->stream_buffer.bus_address;
  vp9_input.buff_len = param->stream_buffer.size;
  vp9_input.p_user_data = param->p_user_data;
  vp9_input.pic_id = param->pic_id;

  u32 data_sz = vp9_input.data_len;
  u32 data_len = vp9_input.data_len;
  u32 consumed_sz = 0;
  const u8* data_start = vp9_input.stream;
  const u8* buf_end = vp9_input.buffer + vp9_input.buff_len;
  //const u8* data_end = data_start + data_sz;

  /* TODO(vmr): vp9 must not acquire the resources automatically after
   *            successful header decoding. */

  /* low latency: super frame don't support in low latency mode. */
  if (!param->low_latency) {
    /* TODO: Is this correct place to handle superframe indexes? */
    ParseSuperframeIndex(vp9_input.stream, data_sz,
                         vp9_input.buffer, param->stream_buffer.size,
                         vcdec->sf_frm_sizes, &vcdec->sf_num_frms,
                         0, &vcdec->stream_info);
  } else
    vcdec->sf_num_frms = 0;
  do {
    if (!param->low_latency) {
      /* Skip over the superframe index, if present */
      if (data_sz && (DWLPrivateAreaReadByte(data_start) & 0xe0) == 0xc0) {
        const u8 marker = DWLPrivateAreaReadByte(data_start);
        const u32 frames = (marker & 0x7) + 1;
        const u32 mag = ((marker >> 3) & 0x3) + 1;
        const u32 index_sz = 2 + mag * frames;
        u8 index_value;
        if(data_start + index_sz - 1 < buf_end)
          index_value = DWLPrivateAreaReadByte(data_start + index_sz - 1);
        else
          index_value = DWLPrivateAreaReadByte(data_start + (i32)index_sz - 1 - (i32)vp9_input.buff_len);

        if (data_sz >= index_sz && index_value == marker) {
          data_start += index_sz;
          if (data_start >= buf_end)
            data_start -= vp9_input.buff_len;
          if (consumed_sz < data_len)
            vp9_input.data_len += index_sz;
          consumed_sz += index_sz;
          data_sz -= index_sz;
          if (consumed_sz < data_len)
            continue;
          else {
            vcdec->sf_num_frms = 0;
            vcdec->sf_cur_frm_id = 0;
            break;
          }
        }
      }
    }

    /* Use the correct size for this frame, if an index is present. */
    if (vcdec->sf_num_frms) {
      u32 this_sz = vcdec->sf_frm_sizes[vcdec->sf_cur_frm_id];
      if (data_sz < this_sz) {
        /* printf("Invalid frame size in index\n"); */
        return DEC_STRM_ERROR;
      }

      data_sz = this_sz;
      // vcdec->sf_cur_frm_id++;
    }

    /* For superframe, although there are several pictures, stream is consumed only once */
    if (vcdec->sf_num_frms > 1 && vcdec->sf_cur_frm_id < vcdec->sf_num_frms - 1)
      vp9_input.p_user_data = NULL;
    else
      vp9_input.p_user_data = param->p_user_data;

    vp9_input.stream_bus_address =
      param->stream_buffer.bus_address + (addr_t)data_start - (addr_t)param->stream_buffer.virtual_address;
    vp9_input.stream = (u8*)data_start;
    vp9_input.data_len = data_sz;

    rv = Vp9DecDecode(vcdec->inst, &vp9_input, &vp9_output);

    /* Headers decoded or error occurred */
    if (rv == DEC_HDRS_RDY || (rv != DEC_PIC_DECODED && rv != DEC_STRM_PROCESSED)) break;
    else if (vcdec->sf_num_frms) vcdec->sf_cur_frm_id++;

    data_start += data_sz;
    consumed_sz += data_sz;
    if (data_start >= buf_end)
      data_start -= vp9_input.buff_len;

    /* Account for suboptimal termination by the encoder. */
    while (consumed_sz < data_len && *data_start == 0) {
      data_start++;
      consumed_sz++;
      if (data_start >= buf_end)
        data_start -= vp9_input.buff_len;
    }

    data_sz = data_len - consumed_sz;

  } while (vcdec->sf_num_frms && (consumed_sz < data_len) && (vcdec->sf_cur_frm_id <= vcdec->sf_num_frms));

  /* TODO(vmr): output is complete garbage on on VP9. Fix in the code decoding
   *            the frame headers. */
  /*output->strm_curr_pos = vp9_output.strm_curr_pos;
    output->strm_curr_bus_address = vp9_output.strm_curr_bus_address;
    output->data_left = vp9_output.data_left;*/
  switch (rv) {/* Workaround */
  case DEC_HDRS_RDY:
    output->strm_curr_pos = (u8*)vp9_input.stream;
    output->strm_curr_bus_address = vp9_input.stream_bus_address;
    output->data_left = data_len;
    break;
  case DEC_WAITING_FOR_BUFFER:
    output->strm_curr_pos = (u8*)vp9_input.stream;
    output->strm_curr_bus_address = vp9_input.stream_bus_address;
    output->data_left = data_len - consumed_sz;
    break;
  case DEC_NO_DECODING_BUFFER:
    output->strm_curr_pos = (u8*)vp9_input.stream;
    output->strm_curr_bus_address = vp9_input.stream_bus_address;
    output->data_left = data_len - consumed_sz;
    break;
  default:
    if ((vp9_input.stream + vp9_input.data_len) >= buf_end) {
      output->strm_curr_pos = (u8*)(vp9_input.stream + vp9_input.data_len
                                    - vp9_input.buff_len);
      output->strm_curr_bus_address = vp9_input.stream_bus_address + vp9_input.data_len
                                      - vp9_input.buff_len;
    } else {
      output->strm_curr_pos = (u8*)(vp9_input.stream + vp9_input.data_len);
      output->strm_curr_bus_address = vp9_input.stream_bus_address + vp9_input.data_len;
    }
    output->data_left = 0;
    break;
  }
  if (param->low_latency) {
    u32 data_consumed = 0;
    if (vp9_output.strm_curr_pos < param->stream) {
      data_consumed += (u32)(vp9_output.strm_curr_pos + param->stream_buffer.size - (u8*)param->stream);
    } else {
      data_consumed += (u32)(vp9_output.strm_curr_pos - param->stream);
    }
    output->data_left = param->frame_len - data_consumed;
    if (data_consumed >= param->frame_len) {
      output->data_left = 0;
      data_consumed = 0;
      param->pic_decoded = 1;
    }
  }
  return rv;
}

static enum DecRet VCDecVp9NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  enum DecRet rv;
  u32 i;

  struct Vp9DecPicture vpic = {0};
  rv = Vp9DecNextPicture(vcdec->inst, &vpic);

  DWLmemset(pic, 0, sizeof(struct DecPicture));
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_luma_base;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_luma_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_chroma_base;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_chroma_bus_address;
    GetOutPicBufferSize(vpic.pictures[i].frame_height, vpic.pictures[i].pic_stride, vpic.pictures[i].pic_stride_ch,
		        vpic.pictures[i].output_format, &pic->pictures[i].luma.size, &pic->pictures[i].chroma.size);
    pic->pictures[i].pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].chroma_format = 1;

    /* TODO(vmr): find out for real also if it is B frame */
    pic->pictures[i].picture_info.pic_coding_type =
      vpic.is_intra_frame ? DEC_PIC_TYPE_I : DEC_PIC_TYPE_P;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
    pic->pictures[i].sequence_info.crop_params.crop_left_offset = 0;
    pic->pictures[i].sequence_info.crop_params.crop_out_width = vpic.coded_width;
    pic->pictures[i].sequence_info.crop_params.crop_top_offset = 0;
    pic->pictures[i].sequence_info.crop_params.crop_out_height = vpic.coded_height;
    pic->pictures[i].sequence_info.video_range = DEC_VIDEO_RANGE_NORMAL;
    pic->pictures[i].sequence_info.matrix_coefficients = 0;
    pic->pictures[i].sequence_info.is_mono_chrome = 0;
    pic->pictures[i].sequence_info.is_interlaced = 0;
    pic->pictures[i].sequence_info.num_of_ref_frames = pic->pictures[i].sequence_info.num_of_ref_frames;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
    pic->pictures[i].picture_info.bitrate_4k60fps = vpic.bitrate_4k60fps;
    pic->pictures[i].picture_info.bwrd_in_fs = vpic.bwrd_in_fs;
    pic->pictures[i].picture_info.bwwr_in_fs = vpic.bwwr_in_fs;
#endif
    pic->pictures[i].sequence_info.bit_depth_luma = vpic.bit_depth_luma;
    pic->pictures[i].sequence_info.bit_depth_chroma = vpic.bit_depth_chroma;
  }
    for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
#ifdef SUPPORT_DEC400
      if (pic->pictures[i].luma.size && vpic.pictures[i].dec400_luma_table.size) {
        pic->pictures[i].luma_table.virtual_address = (u32*)((addr_t)pic->pictures[i].luma.virtual_address +
                                        pic->pictures[i].luma.size);
        pic->pictures[i].luma_table.bus_address = pic->pictures[i].luma.bus_address + pic->pictures[i].luma.size;
        pic->pictures[i].luma_table.logical_size = vpic.pictures[i].dec400_luma_table.logical_size;
        pic->pictures[i].luma_table.size = vpic.pictures[i].dec400_luma_table.size;
        if (pic->pictures[i].chroma.virtual_address) {
          pic->pictures[i].chroma_table.virtual_address = (u32*)((addr_t)pic->pictures[i].chroma.virtual_address +
                                        pic->pictures[i].chroma.size);
          pic->pictures[i].chroma_table.bus_address= pic->pictures[i].chroma.bus_address + pic->pictures[i].chroma.size;
          pic->pictures[i].chroma_table.logical_size = vpic.pictures[i].dec400_chroma_table.logical_size;
          pic->pictures[i].chroma_table.size = vpic.pictures[i].dec400_chroma_table.size;
        }
      }
#endif
    }

  return rv;
}

static enum DecRet VCDecVp9PictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  struct Vp9DecPicture vpic;
  u32 i;
  DWLmemset(&vpic, 0, sizeof(struct Vp9DecPicture));
  /* TODO chroma base needed? */
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_luma_base = pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_luma_bus_address = pic->pictures[i].luma.bus_address;
  }
  vpic.is_intra_frame = pic->pictures[0].picture_info.pic_coding_type == DEC_PIC_TYPE_I;
  return Vp9DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecVp9EndOfStream(VCDecInst *vcdec) {
  return Vp9DecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecVp9GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo vbuf;
  DWLmemset(&vbuf, 0, sizeof(vbuf));
  enum DecRet rv;
  u32 i;

  rv = Vp9DecGetBufferInfo(vcdec->inst, &vbuf);
  buf_info->buf_to_free = vbuf.buf_to_free;
  buf_info->next_buf_size = vbuf.next_buf_size;
  buf_info->buf_num = vbuf.buf_num;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = vbuf.ystride[i];
    buf_info->cstride[i] = vbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecVp9AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return Vp9DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecVp9UseExtraFrmBuffers(VCDecInst *vcdec, u32 n) {
  return Vp9DecUseExtraFrmBuffers(vcdec->inst, n);
}

static enum DecRet VCDecVp9Abort(VCDecInst *vcdec) {
  return Vp9DecAbort(vcdec->inst);
}

static enum DecRet VCDecVp9AbortAfter(VCDecInst *vcdec) {
  return Vp9DecAbortAfter(vcdec->inst);
}

static void VCDecVp9UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  Vp9DecUpdateStrmInfoCtrl(vcdec->inst, info);
}

static void VCDecVp9Release(VCDecInst *vcdec) {
  Vp9DecRelease(vcdec->inst);
}
#endif /* ENABLE_VP9_SUPPORT */

#ifdef ENABLE_AVS2_SUPPORT
static enum DecRet VCDecAvs2Init(VCDecInst *vcdec, struct DecInitConfig* config) {
  struct Avs2DecConfig dec_cfg = {0, };
  enum DecRet rv = 0;
  dec_cfg.multi_frame_input_flag = config->multi_frame_input_flag;
  dec_cfg.no_output_reordering = config->disable_picture_reordering;
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_video_compressor = config->use_video_compressor;
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.guard_size = 0;
  dec_cfg.use_adaptive_buffers = 0;
  dec_cfg.mcinit_cfg = config->mc_cfg;

  rv = Avs2DecInit((const void **)&vcdec->inst, config->dwl_inst, &dec_cfg);
#ifdef ASIC_TRACE_SUPPORT
  config->sim_mc = dec_cfg.sim_mc;
#endif
  return rv;
}

static enum DecRet VCDecAvs2GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  struct Avs2DecInfo avs2_info;
  DWLmemset(&avs2_info, 0, sizeof(avs2_info));
  enum DecRet rv = (enum DecRet)Avs2DecGetInfo(vcdec->inst, &avs2_info);
  info->pic_width = avs2_info.pic_width;
  info->pic_height = avs2_info.pic_height;
  info->sar_width = avs2_info.sar_width;
  info->sar_height = avs2_info.sar_height;
  info->crop_params.crop_left_offset = avs2_info.crop_params.crop_left_offset;
  info->crop_params.crop_out_width = avs2_info.crop_params.crop_out_width;
  info->crop_params.crop_top_offset = avs2_info.crop_params.crop_top_offset;
  info->crop_params.crop_out_height = avs2_info.crop_params.crop_out_height;
  info->video_range = avs2_info.video_range;
  //info->matrix_coefficients = avs2_info.matrix_coefficients;
  info->is_mono_chrome = avs2_info.mono_chrome;
  info->is_interlaced = avs2_info.interlaced_sequence;
  info->num_of_ref_frames = avs2_info.pic_buff_size;
  info->bit_depth_luma = info->bit_depth_chroma = avs2_info.bit_depth;
  info->out_bit_depth = avs2_info.out_bit_depth;
  info->chroma_format_idc = 1;
  return rv;
}

static enum DecRet VCDecAvs2SetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct Avs2DecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_cfg, config->ppu_cfg, sizeof(config->ppu_cfg));
#if 0
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cfg.ppu_cfg[i].enabled &&
        (!dec_cfg.ppu_cfg[i].scale.enabled ||
         dec_cfg.ppu_cfg[i].scale.scale_by_ratio)) {
      /* Convert fixed ratio scale to ppu_cfg[i] */
      if (!config->ppu_cfg[i].crop.enabled) {
        dec_cfg.ppu_cfg[i].crop.enabled = 1;
        dec_cfg.ppu_cfg[i].crop.x = info->crop_params.crop_left_offset;
        dec_cfg.ppu_cfg[i].crop.y = info->crop_params.crop_top_offset;
        dec_cfg.ppu_cfg[i].crop.width = (info->crop_params.crop_out_width + 1) & (~0x1);
        dec_cfg.ppu_cfg[i].crop.height = (info->crop_params.crop_out_height + 1) & (~0x1);
      }
      if (dec_cfg.ppu_cfg[i].scale.scale_by_ratio) {
        dec_cfg.ppu_cfg[i].scale.enabled = 1;
        dec_cfg.ppu_cfg[i].scale.width = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.width,
                                                         dec_cfg.ppu_cfg[i].scale.ratio_x);
        dec_cfg.ppu_cfg[i].scale.height = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.height,
                                                          dec_cfg.ppu_cfg[i].scale.ratio_y);
      }
    }
  }
#endif
  return Avs2DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecAvs2Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  struct Avs2DecInput Avs2_input;
  struct DecOutput Avs2_output;
  DWLmemset(&Avs2_input, 0, sizeof(Avs2_input));
  DWLmemset(&Avs2_output, 0, sizeof(Avs2_output));
  Avs2_input.stream = (u8*)param->stream;
  Avs2_input.stream_bus_address = param->stream_buffer.bus_address +
                                  ((addr_t)param->stream - (addr_t)param->stream_buffer.virtual_address);
  Avs2_input.data_len = param->strm_len;
  Avs2_input.buffer = (u8 *)param->stream_buffer.virtual_address;
  Avs2_input.buffer_bus_address = param->stream_buffer.bus_address;
  Avs2_input.buff_len = param->stream_buffer.size;
  Avs2_input.pic_id = param->pic_id;
  Avs2_input.p_user_data = param->p_user_data;
  /* TODO(vmr): H264 must not acquire the resources automatically after
   *            successful header decoding. */
  rv = Avs2DecDecode(vcdec->inst, &Avs2_input, &Avs2_output);
  output->strm_curr_pos = Avs2_output.strm_curr_pos;
  output->strm_curr_bus_address = Avs2_output.strm_curr_bus_address;
  output->data_left = Avs2_output.data_left;
  if (param->low_latency) {
    u32 data_consumed = 0;
    if (Avs2_output.strm_curr_pos < param->stream) {
      data_consumed += (u32)(Avs2_output.strm_curr_pos + param->stream_buffer.size - (u8*)param->stream);
    } else {
      data_consumed += (u32)(Avs2_output.strm_curr_pos - param->stream);
    }
    output->data_left = param->frame_len - data_consumed;
    if (data_consumed >= param->frame_len) {
      output->data_left = 0;
      data_consumed = 0;
      param->pic_decoded = 1;
    }
  }
  return rv;
}
static enum DecRet VCDecAvs2NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  enum DecRet rv;
  u32 stride, stride_ch, i;
  struct Avs2DecPicture hpic;
  DWLmemset(&hpic, 0, sizeof(hpic));
  rv = Avs2DecNextPicture(vcdec->inst, &hpic);

  DWLmemset(pic, 0, sizeof(struct DecPictures));
  if (rv==DEC_PIC_RDY) {
    for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
      stride = hpic.pictures[i].pic_stride;
      stride_ch = hpic.pictures[i].pic_stride_ch;
      pic->pictures[i].luma.virtual_address = (u32*)hpic.pictures[i].output_picture;
      pic->pictures[i].luma.bus_address = hpic.pictures[i].output_picture_bus_address;
#if 0
    if (hpic.output_format == DEC_OUT_FRM_RASTER_SCAN)
      hpic.pic_width = NEXT_MULTIPLE(hpic.pic_width, 16);
#endif
      if (IS_PIC_TILE(hpic.pictures[i].output_format)) {
        pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 4) / 4);
        pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
      } else if (IS_PIC_PLANAR(hpic.pictures[i].output_format)) {
        pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
        pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height;
      } else if (IS_PIC_REF_TILED8x8(hpic.pictures[i].output_format)) {
        pic->pictures[i].luma.size = stride * (NEXT_MULTIPLE(hpic.pictures[i].pic_height, 8) / 8);
        pic->pictures[i].chroma.size = stride_ch * (NEXT_MULTIPLE(hpic.pictures[i].pic_height / 2, 4) / 4);
      } else {
        pic->pictures[i].luma.size = stride * hpic.pictures[i].pic_height;
        if (!IS_PIC_RGB(hpic.pictures[i].output_format))
          pic->pictures[i].chroma.size = stride_ch * hpic.pictures[i].pic_height / 2;
      }
      /* TODO temporal solution to set chroma base here */
      pic->pictures[i].chroma.virtual_address = (u32*)hpic.pictures[i].output_picture_chroma;
      pic->pictures[i].chroma.bus_address = hpic.pictures[i].output_picture_chroma_bus_address;
      /* TODO(vmr): find out for real also if it is B frame */
      pic->pictures[i].picture_info.pic_coding_type = (int)hpic.type; //FIXME
      pic->pictures[i].picture_info.format = hpic.pictures[i].output_format;
      pic->pictures[i].picture_info.pic_id = hpic.pic_id;
      pic->pictures[i].picture_info.decode_id = hpic.decode_id; //[0];
      pic->pictures[i].picture_info.cycles_per_mb = hpic.cycles_per_mb;
      pic->pictures[i].sequence_info.pic_width = hpic.pictures[i].pic_width;
      pic->pictures[i].sequence_info.pic_height = hpic.pictures[i].pic_height;
      if (!hpic.pp_enabled) {
        pic->pictures[i].sequence_info.crop_params.crop_left_offset =
          hpic.crop_params.crop_left_offset;
        pic->pictures[i].sequence_info.crop_params.crop_out_width =
          hpic.crop_params.crop_out_width;
        pic->pictures[i].sequence_info.crop_params.crop_top_offset =
          hpic.crop_params.crop_top_offset;
        pic->pictures[i].sequence_info.crop_params.crop_out_height =
          hpic.crop_params.crop_out_height;
      } else {
        pic->pictures[i].sequence_info.crop_params.crop_left_offset = 0;
        pic->pictures[i].sequence_info.crop_params.crop_out_width =
          hpic.pictures[i].pic_width;
        pic->pictures[i].sequence_info.crop_params.crop_top_offset = 0;
        pic->pictures[i].sequence_info.crop_params.crop_out_height =
          hpic.pictures[i].pic_height;
      }
      //pic->pictures[i].sequence_info.sar_width = hpic.sar_width;
      //pic->pictures[i].sequence_info.sar_height = hpic.sar_height;
      pic->pictures[i].sequence_info.video_range = 0; //hpic.video_range;
      pic->pictures[i].sequence_info.matrix_coefficients =
        0; //hpic.matrix_coefficients;
      pic->pictures[i].sequence_info.is_mono_chrome =
        0; //hpic.mono_chrome;
      pic->pictures[i].sequence_info.is_interlaced = hpic.dec_info.interlaced_sequence;
      pic->pictures[i].sequence_info.num_of_ref_frames =
        0; //hpic.dec_info.pic_buff_size;
      if (hpic.sample_bit_depth!=hpic.output_bit_depth) {
        if (hpic.pp_enabled) {
          pic->pictures[i].sequence_info.bit_depth_luma =
          pic->pictures[i].sequence_info.bit_depth_chroma = 8;
        } else {
          pic->pictures[i].sequence_info.bit_depth_luma = hpic.sample_bit_depth | (hpic.output_bit_depth<<8);
          pic->pictures[i].sequence_info.bit_depth_chroma = hpic.sample_bit_depth | (hpic.output_bit_depth<<8);
        }
      } else {
        pic->pictures[i].sequence_info.bit_depth_luma = hpic.sample_bit_depth;
        pic->pictures[i].sequence_info.bit_depth_chroma = hpic.sample_bit_depth;
      }
      pic->pictures[i].pic_width = hpic.pictures[i].pic_width;
      pic->pictures[i].pic_height = hpic.pictures[i].pic_height;
      pic->pictures[i].pic_stride = hpic.pictures[i].pic_stride;
      pic->pictures[i].pic_stride_ch = hpic.pictures[i].pic_stride_ch;
      pic->pictures[i].chroma_format = 1;
      pic->pictures[i].pp_enabled = 0; //hpic.pp_enabled;
      pic->pictures[i].top_field_first=hpic.pictures[i].top_field_first;
      pic->pictures[i].fields_in_picture=hpic.pictures[i].fields_in_picture;
    }
    for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
      if (pic->pictures[i].luma.size) {
#ifdef SUPPORT_DEC400
        DWLmemcpy(&pic->pictures[i].luma_table, &hpic.pictures[i].dec400_luma_table, sizeof(hpic.pictures[i].dec400_luma_table));
        if (pic->pictures[i].chroma.virtual_address) {
          DWLmemcpy(&pic->pictures[i].chroma_table, &hpic.pictures[i].dec400_chroma_table, sizeof(hpic.pictures[i].dec400_chroma_table));
        }
#endif
      }
    }
  }

  return rv;
}

static enum DecRet VCDecAvs2PictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  struct Avs2DecPicture hpic;
  u32 i;
  DWLmemset(&hpic, 0, sizeof(hpic));
  /* TODO update chroma luma/chroma base */
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    hpic.pictures[i].output_picture = pic->pictures[i].luma.virtual_address;
    hpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  hpic.type = pic->pictures[0].picture_info.pic_coding_type;
  return Avs2DecPictureConsumed(vcdec->inst, &hpic);
}

static enum DecRet VCDecAvs2EndOfStream(VCDecInst *vcdec) {
  return Avs2DecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecAvs2GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = Avs2DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->buf_to_free = hbuf.buf_to_free;
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecAvs2AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return Avs2DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecAvs2UseExtraFrmBuffers(VCDecInst *vcdec, u32 n) {
  return Avs2DecUseExtraFrmBuffers(vcdec->inst, n);
}

static enum DecRet VCDecAvs2Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  // return Avs2DecPeek(vcdec->inst, pic);
  enum DecRet rv = {0};
  return rv;
}

static enum DecRet VCDecAvs2Abort(VCDecInst *vcdec) {
  return Avs2DecAbort(vcdec->inst);
}

static enum DecRet VCDecAvs2AbortAfter(VCDecInst *vcdec) {
  return Avs2DecAbortAfter(vcdec->inst);
}

static void VCDecAvs2SetNoReorder(VCDecInst *vcdec, u32 no_reorder) {
  Avs2DecSetNoReorder(vcdec->inst, no_reorder);
}

static void VCDecAvs2UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  Avs2DecUpdateStrmInfoCtrl(vcdec->inst, info);
}

static void VCDecAvs2Release(VCDecInst *vcdec) {
  Avs2DecRelease(vcdec->inst);
}
#endif /* ENABLE_AVS2_SUPPORT */

#ifdef ENABLE_AV1_SUPPORT
static enum DecRet VCDecAv1Init(VCDecInst *vcdec, struct DecInitConfig *config) {
  vcdec->av1_data.annexb = config->annexb;
  vcdec->av1_data.plainobu = config->plainobu;
  vcdec->sf_num_frms = 0;
  vcdec->sf_cur_frm_id = 0;
  DWLmemset(vcdec->sf_frm_sizes, 0, sizeof(vcdec->sf_frm_sizes));

  struct Av1DecConfig dec_cfg = {0, };
  dec_cfg.multi_frame_input_flag = config->multi_frame_input_flag;
  dec_cfg.mc_enable = config->mc_cfg.mc_enable;
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.num_frame_buffers = 10 + config->num_frame_buffers;
  dec_cfg.use_video_compressor = config->use_video_compressor;
  dec_cfg.annexb = config->annexb;
  dec_cfg.plainobu = config->plainobu;
  dec_cfg.tile_transpose = config->tile_transpose;
  dec_cfg.oppoints = config->oppoints;
  dec_cfg.disable_late_hw_sync = config->disable_late_hw_sync;
  dec_cfg.disable_clock_gating = config->disable_clock_gating;
  dec_cfg.enable_dram_throttle = config->enable_dram_throttle;
  dec_cfg.multicore_poll_period = config->multicore_poll_period;
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;

  return Av1DecInit((const void **)&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecAv1GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  struct Av1DecInfo av1_info;
  DWLmemset(&av1_info, 0, sizeof(av1_info));
  enum DecRet rv = Av1DecGetInfo(vcdec->inst, &av1_info);
  info->pic_width = av1_info.frame_width;
  info->pic_height = av1_info.frame_height;
  info->sar_width = 1;
  info->sar_height = 1;
  info->crop_params.crop_left_offset = 0;
  info->crop_params.crop_out_width = av1_info.coded_width;
  info->crop_params.crop_top_offset = 0;
  info->crop_params.crop_out_height = av1_info.coded_height;
  info->crop_params.crop_out_width = av1_info.superres_width;
  /* TODO(vmr): Consider adding scaled_width & scaled_height. */
  info->num_of_ref_frames = av1_info.pic_buff_size;
  info->video_range = DEC_VIDEO_RANGE_NORMAL;
  info->matrix_coefficients = 0;
  info->is_mono_chrome = 0;
  info->is_mono_chrome = av1_info.monochrome;
  info->is_interlaced = 0;
  info->bit_depth_luma = info->bit_depth_chroma = av1_info.bit_depth;
  info->chroma_format_idc = 1;
  info->timing_info_present_flag = av1_info.timing_info_present_flag;
  info->num_units_in_tick = av1_info.num_units_in_tick;
  info->time_scale = av1_info.time_scale;
  return rv;
}

static enum DecRet VCDecAv1SetInfo(VCDecInst *vcdec, struct DecConfig *config) {
  struct Av1DecConfig dec_cfg;
  dec_cfg.align = config->align;
  /* AV1 HW_EC always enable */
  // dec_cfg.hw_conceal = config->hw_conceal;
  DWLmemcpy(dec_cfg.ppu_cfg, config->ppu_cfg, sizeof(config->ppu_cfg));
#if 0
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cfg.ppu_cfg[i].enabled &&
        (!dec_cfg.ppu_cfg[i].scale.enabled ||
         dec_cfg.ppu_cfg[i].scale.scale_by_ratio)) {
      /* Convert fixed ratio scale to ppu_cfg[i] */
      if (!config->ppu_cfg[i].crop.enabled) {
        dec_cfg.ppu_cfg[i].crop.enabled = 1;
        dec_cfg.ppu_cfg[i].crop.x = info->crop_params.crop_left_offset;
        dec_cfg.ppu_cfg[i].crop.y = info->crop_params.crop_top_offset;
        dec_cfg.ppu_cfg[i].crop.width = (info->crop_params.crop_out_width + 1) & (~0x1);
        dec_cfg.ppu_cfg[i].crop.height = (info->crop_params.crop_out_height + 1) & (~0x1);
      }
      if (dec_cfg.ppu_cfg[i].scale.scale_by_ratio) {
        dec_cfg.ppu_cfg[i].scale.enabled = 1;
        dec_cfg.ppu_cfg[i].scale.width = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.width,
                                                         dec_cfg.ppu_cfg[i].scale.ratio_x);
        dec_cfg.ppu_cfg[i].scale.height = DOWN_SCALE_SIZE(dec_cfg.ppu_cfg[i].crop.height,
                                                          dec_cfg.ppu_cfg[i].scale.ratio_y);
      }
    }
  }
#endif
  return Av1DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecAv1Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv = DEC_OK;
  struct Av1DecInput av1_input;
  struct DecOutput av1_output;
  DWLmemset(&av1_input, 0, sizeof(av1_input));
  DWLmemset(&av1_output, 0, sizeof(av1_output));
  av1_input.stream = (u8*)param->stream;
  av1_input.stream_bus_address = param->stream_buffer.bus_address +
                                 ((addr_t)param->stream - (addr_t)param->stream_buffer.virtual_address);
  av1_input.data_len = param->strm_len;
  av1_input.buffer = (u8*)param->stream_buffer.virtual_address;
  av1_input.buffer_bus_address = param->stream_buffer.bus_address;
  av1_input.buff_len = param->stream_buffer.size;
  av1_input.frame_len = param->frame_len;
  av1_input.pic_id = param->pic_id;

  u32 data_sz = av1_input.frame_len;
  u32 data_len = av1_input.frame_len;
  u32 consumed_sz = 0;
  const u8* data_start = av1_input.stream;
  const u8* buf_end = av1_input.buffer + av1_input.buff_len;
  // TODO(min): think of another way to remove Av1DecContainer.
  bool av1baseline = 1; //((struct Av1DecContainer*)(vcdec->inst))->decoder.av1baseline;
  bool annexb = vcdec->av1_data.annexb; //((struct Av1DecContainer*)(vcdec->inst))->annexb;
  bool plainobu = vcdec->av1_data.plainobu; //((struct Av1DecContainer*)(vcdec->inst))->plainobu;
  if (param->low_latency)
    vcdec->stream_info.low_latency = 1;
  SwReadByteFn *fn_read_byte;

  fn_read_byte = SwGetReadByteFunc(&vcdec->stream_info);

  /* TODO(vmr): vp9 must not acquire the resources automatically after
   *            successful header decoding. */

  /* TODO: Is this correct place to handle superframe indexes? */
  if (!annexb && !plainobu)
    ParseSuperframeIndex(av1_input.stream, data_sz,
                         av1_input.buffer, param->stream_buffer.size,
                         vcdec->sf_frm_sizes, &vcdec->sf_num_frms,
                         av1baseline, &vcdec->stream_info);


  struct Av1DecInput frame_start = av1_input;
  bool dec_pic_decode_flag = HANTRO_FALSE;
  do {
    /* Skip over the superframe index, if present */
    if (!annexb && !plainobu && data_sz &&
        (fn_read_byte(data_start, av1_input.buff_len, &vcdec->stream_info) & 0xe0) == 0xc0) {
      const u8 marker = *data_start;
      const u32 frames = (marker & 0x7) + 1;
      const u32 mag = ((marker >> 3) & 0x3) + 1;
      const u32 index_sz = 2 + mag * (frames - av1baseline);
      u8 index_value;
      if(data_start + index_sz - 1 < buf_end)
        index_value = fn_read_byte(data_start + index_sz - 1, av1_input.buff_len, &vcdec->stream_info);
      else
        index_value = fn_read_byte(data_start + (i32)index_sz - 1 - (i32)av1_input.buff_len,
                                   av1_input.buff_len, &vcdec->stream_info);

      if (data_sz >= index_sz && index_value == marker) {
        data_start += index_sz;
        if (data_start >= buf_end)
          data_start -= av1_input.buff_len;
        consumed_sz += index_sz;
        data_sz -= index_sz;
        if (consumed_sz < data_len)
          continue;
        else {
          vcdec->sf_num_frms = 0;
          vcdec->sf_cur_frm_id = 0;
          break;
        }
      }
    }

    /* Use the correct size for this frame, if an index is present. */
    if (vcdec->sf_num_frms) {
      u32 this_sz = vcdec->sf_frm_sizes[vcdec->sf_cur_frm_id];

      if (data_sz < this_sz) {
        /* printf("Invalid frame size in index\n"); */
        return DEC_STRM_ERROR;
      }

      data_sz = this_sz;
      //vcdec->sf_cur_frm_id++;
    } else if (annexb) {
      // store position at start of each frame within temporal unit
      frame_start.stream_bus_address =
          param->stream_buffer.bus_address + (u32)(data_start - (u8*)param->stream_buffer.virtual_address);
      frame_start.stream = (u8*)data_start;
      frame_start.data_len = param->stream_buffer.size -
          (u32)(data_start - (u8*)param->stream_buffer.virtual_address);
      int len = 0;
      if (param->low_latency) {
        const u8 *read_end = data_start + 7;
	if (read_end > (av1_input.buffer + av1_input.buff_len)) read_end -= av1_input.buff_len;
        do {
          if (read_end >= vcdec->stream_info.strm_vir_start_addr)
            len = read_end - vcdec->stream_info.strm_vir_start_addr;
          else
            len = read_end + av1_input.buff_len - vcdec->stream_info.strm_vir_start_addr;
          sched_yield();
        } while ((len > vcdec->stream_info.send_len) && !vcdec->stream_info.last_flag);
      }
      len = 0;
      data_sz = Av1Leb128(data_start, &len, av1_input.buffer, av1_input.buff_len);
      data_start += len;
      if (data_start >= buf_end)
        data_start -= av1_input.buff_len;
    }

    int local_data_sz = data_sz;

    av1_input.stream_bus_address =
        param->stream_buffer.bus_address + (u32)(data_start - (u8*)param->stream_buffer.virtual_address);
    av1_input.stream = (u8*)data_start;
    av1_input.data_len = local_data_sz;
    av1_input.usr_ptr = NULL; //((struct Av1DecContainer*)(vcdec->inst))->usr_ptr;
    av1_input.use_multicore = 0; //((struct Av1DecContainer*)(vcdec->inst))->use_multicore;

    rv = Av1DecDecode(vcdec->inst, &av1_input, &av1_output);

    if (rv == DEC_PIC_DECODED)
      dec_pic_decode_flag = HANTRO_TRUE;
    /* Headers decoded or error occurred */
    if (rv == DEC_HDRS_RDY ||
        ((!annexb || rv != DEC_STRM_ERROR) && rv != DEC_PIC_DECODED && rv != DEC_STRM_PROCESSED)) break;
    else if (vcdec->sf_num_frms) vcdec->sf_cur_frm_id++;

    if (av1baseline && !annexb) {
      local_data_sz =  av1_input.data_len - av1_output.data_left;
    }
    data_start += local_data_sz;
    consumed_sz += local_data_sz;
    if (data_start >= buf_end)
      data_start -= av1_input.buff_len;

    data_sz =  data_len - consumed_sz;

    //if (plainobu && rv == DEC_PIC_DECODED)
    //  break;
#if 0
    if (!av1baseline) {
    /* Account for suboptimal termination by the encoder. */
    while (data_start < data_end && *data_start == 0) data_start++;
    data_sz = data_end - data_start;
    }
#endif
  } while (consumed_sz < data_len);

  // if decDecode invoked by multiple time for only one input from upper layer,
  // one case is at the frame tail contain the redundant data, another is supper frame, or no OBU_TD between two frame?
  // maintain the return value to update upper pic_id or make app has chance to try to fetch output frame by call DecNextPicture
  if (dec_pic_decode_flag && (rv!=DEC_WAITING_FOR_BUFFER) && (rv!=DEC_NO_DECODING_BUFFER) && (rv!=DEC_HDRS_RDY))
    rv = DEC_PIC_DECODED;

  switch (rv) {/* Workaround */
    case DEC_HDRS_RDY:
      output->strm_curr_pos = (u8*)frame_start.stream;
      output->strm_curr_bus_address = frame_start.stream_bus_address;
      output->data_left = frame_start.data_len;
      break;
    case DEC_WAITING_FOR_BUFFER:
      output->strm_curr_pos = (u8*)av1_output.strm_curr_pos;
      output->strm_curr_bus_address = av1_output.strm_curr_bus_address;
      output->data_left = av1_output.data_left;
      break;
    case DEC_NO_DECODING_BUFFER:
      output->strm_curr_pos = (u8*)av1_output.strm_curr_pos;
      output->strm_curr_bus_address = av1_output.strm_curr_bus_address;
      output->data_left = av1_output.data_left;
      break;
    default:
      if ((av1_input.stream + av1_input.data_len) >= buf_end) {
        output->strm_curr_pos = (u8*)(av1_input.stream + av1_input.data_len
                                      - av1_input.buff_len);
        output->strm_curr_bus_address = av1_input.stream_bus_address + av1_input.data_len
                                      - av1_input.buff_len;
      } else {
        output->strm_curr_pos = (u8*)(av1_input.stream + av1_input.data_len);
        output->strm_curr_bus_address = av1_input.stream_bus_address + av1_input.data_len;
      }
      output->data_left = 0;
      break;
  }
  if (param->low_latency) {
    u32 data_consumed = 0;
    if (av1_output.strm_curr_pos < param->stream) {
      data_consumed += (u32)(av1_output.strm_curr_pos + param->stream_buffer.size - (u8*)param->stream);
    } else {
      data_consumed += (u32)(av1_output.strm_curr_pos - param->stream);
    }
    output->data_left = param->frame_len - data_consumed;
    if (data_consumed >= param->frame_len) {
      output->data_left = 0;
      data_consumed = 0;
      param->pic_decoded = 1;
    }
  }
  return rv;
}
static enum DecRet VCDecAv1NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  enum DecRet rv = DEC_OK;
  u32 i;

  struct Av1DecPicture vpic;
  rv = Av1DecNextPicture(vcdec->inst, &vpic);
  DWLmemset(pic, 0, sizeof(struct DecPicture));
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].hdr.virtual_address = (u32*)vpic.pictures[i].output_hdr_base;
    pic->pictures[i].hdr.bus_address = vpic.pictures[i].output_hdr_bus_address;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_luma_base;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_luma_bus_address;
    GetOutPicBufferSize(vpic.pictures[i].frame_height, vpic.pictures[i].pic_stride, vpic.pictures[i].pic_stride_ch,
		        vpic.pictures[i].output_format, &pic->pictures[i].luma.size, &pic->pictures[i].chroma.size);
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_chroma_base;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_chroma_bus_address;
    pic->pictures[i].sei_param.av1 = vpic.metadata_param; /*metadata_param */
    pic->pictures[i].pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;

    /* TODO(vmr): find out for real also if it is B frame */
    pic->pictures[i].picture_info.pic_coding_type =
      vpic.is_intra_frame ? DEC_PIC_TYPE_I : DEC_PIC_TYPE_P;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
    pic->pictures[i].sequence_info.crop_params.crop_left_offset = 0;
    pic->pictures[i].sequence_info.crop_params.crop_out_width = vpic.coded_width;
    pic->pictures[i].sequence_info.crop_params.crop_top_offset = 0;
    pic->pictures[i].sequence_info.crop_params.crop_out_height = vpic.coded_height;
    pic->pictures[i].sequence_info.video_range = DEC_VIDEO_RANGE_NORMAL;
    pic->pictures[i].sequence_info.matrix_coefficients = 0;
    pic->pictures[i].sequence_info.is_mono_chrome = 0;
    pic->pictures[i].sequence_info.is_interlaced = 0;
    pic->pictures[i].sequence_info.num_of_ref_frames = pic->pictures[i].sequence_info.num_of_ref_frames;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
#ifdef FPGA_PERF_AND_BW
    pic->pictures[i].picture_info.bitrate_4k60fps = vpic.bitrate_4k60fps;
    pic->pictures[i].picture_info.bwrd_in_fs = vpic.bwrd_in_fs;
    pic->pictures[i].picture_info.bwwr_in_fs = vpic.bwwr_in_fs;
#endif
    pic->pictures[i].sequence_info.bit_depth_luma = vpic.bits_per_sample;
    pic->pictures[i].sequence_info.bit_depth_chroma = vpic.bits_per_sample;
    pic->pictures[i].chroma_format = 1;
  }

  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
#ifdef SUPPORT_DEC400
    if (pic->pictures[i].luma.size && vpic.pictures[i].dec400_luma_table.size) {
      pic->pictures[i].luma_table.virtual_address = (u32*)((addr_t)pic->pictures[i].luma.virtual_address +
                                      pic->pictures[i].luma.size);
      pic->pictures[i].luma_table.bus_address = pic->pictures[i].luma.bus_address + pic->pictures[i].luma.size;
      pic->pictures[i].luma_table.logical_size = vpic.pictures[i].dec400_luma_table.logical_size;
      pic->pictures[i].luma_table.size = vpic.pictures[i].dec400_luma_table.size;
      if (pic->pictures[i].chroma.virtual_address) {
        pic->pictures[i].chroma_table.virtual_address = (u32*)((addr_t)pic->pictures[i].chroma.virtual_address +
                                      pic->pictures[i].chroma.size);
        pic->pictures[i].chroma_table.bus_address= pic->pictures[i].chroma.bus_address + pic->pictures[i].chroma.size;
        pic->pictures[i].chroma_table.logical_size = vpic.pictures[i].dec400_chroma_table.logical_size;
        pic->pictures[i].chroma_table.size = vpic.pictures[i].dec400_chroma_table.size;
      }
    }
#endif
  }
  return rv;
}

static enum DecRet VCDecAv1PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic) {
  struct Av1DecPicture vpic;
  u32 i = 0;
  DWLmemset(&vpic, 0, sizeof(struct Av1DecPicture));

  /* TODO chroma base needed? */
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    vpic.pictures[i].output_luma_base = pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_luma_bus_address = pic->pictures[i].luma.bus_address;
    vpic.pictures[i].output_hdr_base = pic->pictures[i].hdr.virtual_address;
    vpic.pictures[i].output_hdr_bus_address = pic->pictures[i].hdr.bus_address;
  }

  //vpic.is_intra_frame = pic->picture_info.pic_coding_type == DEC_PIC_TYPE_I;
#ifdef SUPPORT_METADATA
  vpic.metadata_param = pic->pictures[0].sei_param.av1;
#endif
  return Av1DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecAv1EndOfStream(VCDecInst *vcdec) {
  return Av1DecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecAv1GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo abuf;
  enum DecRet rv;
  u32 i;

  rv = Av1DecGetBufferInfo(vcdec->inst, &abuf);
  buf_info->buf_to_free = abuf.buf_to_free;
  buf_info->next_buf_size = abuf.next_buf_size;
  buf_info->buf_num = abuf.buf_num;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = abuf.ystride[i];
    buf_info->cstride[i] = abuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecAv1AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return Av1DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecAv1Abort(VCDecInst *vcdec) {
  return Av1DecAbort(vcdec->inst);
}

static enum DecRet VCDecAv1AbortAfter(VCDecInst *vcdec) {
  return Av1DecAbortAfter(vcdec->inst);
}

static void VCDecAv1UpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  vcdec->stream_info = info;
  Av1DecUpdateStrmInfoCtrl(vcdec->inst, info);
}

static void VCDecAv1Release(VCDecInst *vcdec) {
   Av1DecRelease(vcdec->inst);
}
#endif /* ENABLE_AV1_SUPPORT */

#ifdef ENABLE_VP8_SUPPORT
static enum DecRet VCDecVp8Init(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct VP8DecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.dec_format = config->dec_format;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.decoder_mode = config->decoder_mode;
  return VP8DecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecVp8GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  VP8DecInfo vp8_info;
  DWLmemset(&vp8_info, 0, sizeof(vp8_info));
  enum DecRet rv = VP8DecGetInfo(vcdec->inst, &vp8_info);
  info->vp_version = vp8_info.vp_version;
  info->vp_profile = vp8_info.vp_profile;
  info->num_of_ref_frames = vp8_info.pic_buff_size;
  info->crop_params.crop_left_offset = 0;
  info->crop_params.crop_top_offset = 0;
  info->crop_params.crop_out_width = vp8_info.coded_width;
  info->crop_params.crop_out_height = vp8_info.coded_height;
  info->pic_width = vp8_info.frame_width;
  info->pic_height = vp8_info.frame_height;
  info->scaled_width = vp8_info.scaled_width;
  info->scaled_height = vp8_info.scaled_height;
  info->sar_width = 1;
  info->sar_height = 1;
  info->dpb_mode = vp8_info.dpb_mode;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  if (vp8_info.output_format == VP8DEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  return rv;
}

static enum DecRet VCDecVp8SetInfo(VCDecInst *vcdec, struct DecConfig *config) {
  struct VP8DecConfig dec_cfg;
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return VP8DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecVp8Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  VP8DecInput vp8_input;
  struct DecOutput vp8_output;
  DWLmemset(&vp8_input, 0, sizeof(vp8_input));
  DWLmemset(&vp8_output, 0, sizeof(vp8_output));
  vp8_input.stream = (u8*)param->stream;
  vp8_input.stream_bus_address = (addr_t)param->stream_bus_address;
  vp8_input.data_len = param->strm_len;
  vp8_input.pic_id = param->pic_id;
  vp8_input.slice_height = param->slice_height;
  vp8_input.p_pic_buffer_y = param->p_pic_buffer_y;
  vp8_input.pic_buffer_bus_address_y = param->pic_buffer_bus_address_y;
  vp8_input.p_pic_buffer_c = param->p_pic_buffer_c;
  vp8_input.pic_buffer_bus_address_c = param->pic_buffer_bus_address_c;
  vp8_input.p_user_data = param->p_user_data;
  rv = VP8DecDecode(vcdec->inst, &vp8_input, &vp8_output);
  output->strm_curr_pos = vp8_output.strm_curr_pos;
  output->strm_curr_bus_address = vp8_output.strm_curr_bus_address;
  output->data_left = vp8_output.data_left;
  output->slice_height = vp8_output.slice_height;
  param->strm_len = vp8_input.data_len;
  return rv;
}

static enum DecRet VCDecVp8GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = VP8DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecVp8AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return VP8DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecVp8NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  VP8DecPicture vpic;
  enum DecRet rv = VP8DecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    // pic->pictures[i].picture_info.pic_coding_type =
    //   vpic.is_intra_frame ? DEC_PIC_TYPE_I : DEC_PIC_TYPE_P;
    pic->pictures[i].picture_info.pic_coding_type = vpic.is_intra_frame;
    pic->pictures[i].picture_info.is_golden_frame = vpic.is_golden_frame;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.nbr_of_err_mbs;
    pic->pictures[i].picture_info.num_slice_rows = vpic.num_slice_rows;
    pic->pictures[i].picture_info.last_slice = vpic.last_slice;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
    pic->pictures[i].picture_info.luma_stride = vpic.pictures[i].luma_stride;
    pic->pictures[i].picture_info.chroma_stride = vpic.pictures[i].chroma_stride;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].p_output_frame;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_frame_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].p_output_frame_c;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_frame_bus_address_c;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecVp8PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic) {
  VP8DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(VP8DecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.num_slice_rows = pic->pictures[i].picture_info.num_slice_rows;
    vpic.last_slice = pic->pictures[i].picture_info.last_slice;
    vpic.pictures[i].p_output_frame = pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_frame_bus_address = pic->pictures[i].luma.bus_address;
    vpic.pictures[i].p_output_frame_c = pic->pictures[i].chroma.virtual_address;
    vpic.pictures[i].output_frame_bus_address_c = pic->pictures[i].chroma.bus_address;
  }
  return VP8DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecVp8Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  VP8DecPicture vpic;
  enum DecRet rv = VP8DecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    // pic->pictures[i].picture_info.pic_coding_type =
    //   vpic.is_intra_frame ? DEC_PIC_TYPE_I : DEC_PIC_TYPE_P;
    pic->pictures[i].picture_info.pic_coding_type = vpic.is_intra_frame;
    pic->pictures[i].picture_info.is_golden_frame = vpic.is_golden_frame;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.nbr_of_err_mbs;
    pic->pictures[i].picture_info.num_slice_rows = vpic.num_slice_rows;
    pic->pictures[i].picture_info.last_slice = vpic.last_slice;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
    pic->pictures[i].picture_info.luma_stride = vpic.pictures[i].luma_stride;
    pic->pictures[i].picture_info.chroma_stride = vpic.pictures[i].chroma_stride;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].p_output_frame;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_frame_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].p_output_frame_c;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_frame_bus_address_c;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecVp8Abort(VCDecInst *vcdec) {
  return VP8DecAbort(vcdec->inst);
}

static enum DecRet VCDecVp8AbortAfter(VCDecInst *vcdec) {
  return VP8DecAbortAfter(vcdec->inst);
}

static enum DecRet VCDecVp8EndOfStream(VCDecInst *vcdec) {
  return VP8DecEndOfStream(vcdec->inst);
}

static void VCDecVp8Release(VCDecInst *vcdec) {
   VP8DecRelease(vcdec->inst);
}
#endif /* ENABLE_VP8_SUPPORT */

#ifdef ENABLE_JPEG_SUPPORT
static enum DecRet VCDecJpegInit(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct JpegDecConfig dec_cfg = {0, };
  dec_cfg.decoder_mode = config->decoder_mode;
  dec_cfg.mcinit_cfg = config->mc_cfg;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  return JpegDecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecJpegGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  JpegDecInput jpeg_in;
  JpegDecImageInfo image_info;
  jpeg_in.stream_buffer = info->jpeg_input_info.stream_buffer;
  jpeg_in.stream_length = info->jpeg_input_info.strm_len;
  jpeg_in.buffer_size = info->jpeg_input_info.buffer_size;
  jpeg_in.stream = info->jpeg_input_info.stream;
  jpeg_in.thumbnail_done = info->thumbnail_done;
  DWLmemset(&image_info, 0, sizeof(image_info));
  enum DecRet rv = JpegDecGetImageInfo(vcdec->inst, &jpeg_in, &image_info);
  info->scaled_width = image_info.display_width;
  info->scaled_height = image_info.display_height;
  info->pic_width = image_info.output_width;
  info->pic_height = image_info.output_height;
  info->scaled_width_thumb = image_info.display_width_thumb;
  info->scaled_height_thumb = image_info.display_height_thumb;
  info->pic_width_thumb = image_info.output_width_thumb;
  info->pic_height_thumb = image_info.output_height_thumb;
  info->output_format = image_info.output_format;
  info->output_format_thumb = image_info.output_format_thumb;
  info->coding_mode = image_info.coding_mode;
  info->coding_mode_thumb = image_info.coding_mode_thumb;
  info->thumbnail_type = image_info.thumbnail_type;
  info->img_max_dec_width = image_info.img_max_dec_width;
  info->img_max_dec_height = image_info.img_max_dec_height;
  info->bit_depth_luma = info->bit_depth_chroma = image_info.bit_depth;
  return rv;
}

static enum DecRet VCDecJpegSetInfo(VCDecInst *vcdec, struct DecConfig *config) {
  struct JpegDecConfig dec_cfg;
  dec_cfg.dec_image_type = config->dec_image_type;
  dec_cfg.chroma_format = config->chroma_format;
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  DWLmemcpy(dec_cfg.delogo_params, config->delogo_params, sizeof(config->delogo_params));
  return JpegDecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecJpegDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  JpegDecInput jpeg_in;
  JpegDecOutput jpeg_out;
  DWLmemset(&jpeg_in, 0, sizeof(jpeg_in));
  DWLmemset(&jpeg_out, 0, sizeof(jpeg_out));

  jpeg_in.stream_buffer = param->stream_buffer;
  jpeg_in.stream_length = param->strm_len;
  jpeg_in.buffer_size = param->buffer_size;
  jpeg_in.dec_image_type = param->dec_image_type;
  jpeg_in.slice_mb_set = param->slice_mb_set;
  jpeg_in.ri_count = param->ri_count;
  jpeg_in.ri_array = param->ri_array;
  jpeg_in.picture_buffer_y = param->picture_buffer_y;
  jpeg_in.picture_buffer_cb_cr = param->picture_buffer_cb_cr;
  jpeg_in.picture_buffer_cr = param->picture_buffer_cr;
  jpeg_in.p_user_data = param->p_user_data;
  jpeg_in.stream = param->stream;
  rv = JpegDecDecode(vcdec->inst, &jpeg_in, &jpeg_out);
  /* do not support output in here. */
  output->strm_curr_pos = jpeg_out.output.strm_curr_pos;
  output->strm_curr_bus_address = jpeg_out.output.strm_curr_bus_address;
  output->data_left = jpeg_out.output.data_left;
  return rv;
}

static enum DecRet VCDecJpegGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = JpegDecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecJpegAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return JpegDecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecJpegNextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  JpegDecOutput vpic;
  JpegDecImageInfo info;
  enum DecRet rv = JpegDecNextPicture(vcdec->inst, &vpic, &info);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].luma = vpic.pictures[i].output_picture_y;
    pic->pictures[i].chroma = vpic.pictures[i].output_picture_cb_cr;
    pic->pictures[i].chroma_cr = vpic.pictures[i].output_picture_cr;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].output_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].output_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].display_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].display_height;
    pic->pictures[i].sequence_info.pic_width_thumb = vpic.pictures[i].output_width_thumb;
    pic->pictures[i].sequence_info.pic_height_thumb = vpic.pictures[i].output_height_thumb;
    pic->pictures[i].sequence_info.scaled_width_thumb = vpic.pictures[i].display_width_thumb;
    pic->pictures[i].sequence_info.scaled_height_thumb = vpic.pictures[i].display_height_thumb;
    pic->pictures[i].sequence_info.bit_depth_luma = vpic.bit_depth;
    pic->pictures[i].sequence_info.bit_depth_chroma = vpic.bit_depth;
    pic->pictures[i].sequence_info.crop_params.crop_left_offset = 0;
    pic->pictures[i].sequence_info.crop_params.crop_top_offset = 0;
    pic->pictures[i].sequence_info.crop_params.crop_out_width = vpic.pictures[i].display_width;
    pic->pictures[i].sequence_info.crop_params.crop_out_height = vpic.pictures[i].display_height;
    pic->pictures[i].pic_width = vpic.pictures[i].output_width;
    pic->pictures[i].pic_height = vpic.pictures[i].output_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = info.bit_depth;
    pic->pictures[i].sequence_info.bit_depth_chroma = info.bit_depth;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  pic->pictures[0].sequence_info.output_format = info.output_format;
  pic->pictures[0].sequence_info.output_format_thumb = info.output_format_thumb;
  pic->pictures[0].sequence_info.coding_mode = info.coding_mode;
  pic->pictures[0].sequence_info.coding_mode_thumb = info.coding_mode_thumb;
  pic->pictures[0].sequence_info.thumbnail_type = info.thumbnail_type;

  return rv;
}

static enum DecRet VCDecJpegPictureConsumed(VCDecInst *vcdec, struct DecPictures *pic) {
  JpegDecOutput vpic;
  DWLmemset(&vpic, 0, sizeof(JpegDecOutput));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_picture_y = pic->pictures[i].luma;
  }
  return JpegDecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecJpegAbort(VCDecInst *vcdec) {
  return JpegDecAbort(vcdec->inst);
}

static enum DecRet VCDecJpegAbortAfter(VCDecInst *vcdec) {
  return JpegDecAbortAfter(vcdec->inst);
}

static enum DecRet VCDecJpegEndOfStream(VCDecInst *vcdec) {
  return JpegDecEndOfStream(vcdec->inst);
}

static void VCDecJpegUpdateStrmInfoCtrl(VCDecInst *vcdec, struct strmInfo info) {
  JpegDecUpdateStrmInfoCtrl(vcdec->inst, info);
}

static void VCDecJpegRelease(VCDecInst *vcdec) {
   JpegDecRelease(vcdec->inst);
}
#endif /* ENABLE_JPEG_SUPPORT */

#ifdef ENABLE_VP6_SUPPORT
static enum DecRet VCDecVp6Init(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct VP6DecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.decoder_mode = config->decoder_mode;
  return VP6DecInit((const void**)&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecVp6GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  VP6DecInfo vp6_info;
  DWLmemset(&vp6_info, 0, sizeof(vp6_info));
  enum DecRet rv = VP6DecGetInfo(vcdec->inst, &vp6_info);
  info->vp_version = vp6_info.vp6_version;
  info->vp_profile = vp6_info.vp6_profile;
  info->num_of_ref_frames = vp6_info.pic_buff_size;
  info->pic_width = vp6_info.frame_width;
  info->pic_height = vp6_info.frame_height;
  info->scaled_width = vp6_info.scaled_width;
  info->scaled_height = vp6_info.scaled_height;
  info->sar_width = 1;
  info->sar_height = 1;
  info->dpb_mode = vp6_info.dpb_mode;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  // info->output_format = vp6_info.output_format;
  if (vp6_info.output_format == VP6DEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  return rv;
}

static enum DecRet VCDecVp6SetInfo(VCDecInst *vcdec, struct DecConfig *config) {
  struct VP6DecConfig dec_cfg;
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return VP6DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecVp6Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  VP6DecInput vp6_input;
  struct DecOutput vp6_output;
  DWLmemset(&vp6_input, 0, sizeof(vp6_input));
  DWLmemset(&vp6_output, 0, sizeof(vp6_output));
  vp6_input.stream = (u8*)param->stream;
  vp6_input.stream_bus_address = (addr_t)param->stream_bus_address;
  vp6_input.data_len = param->strm_len;
  vp6_input.pic_id = param->pic_id;
  rv = VP6DecDecode(vcdec->inst, &vp6_input, &vp6_output);
  output->strm_curr_pos = vp6_output.strm_curr_pos;
  output->strm_curr_bus_address = vp6_output.strm_curr_bus_address;
  output->data_left = vp6_output.data_left;
  return rv;
}

static enum DecRet VCDecVp6GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = VP6DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecVp6AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return VP6DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecVp6NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  VP6DecPicture vpic;
  enum DecRet rv = VP6DecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].picture_info.is_intra_frame = vpic.is_intra_frame;
    pic->pictures[i].picture_info.is_golden_frame = vpic.is_golden_frame;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.nbr_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].p_output_frame;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_frame_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecVp6PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic) {
  VP6DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(VP6DecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.pictures[i].p_output_frame = pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_frame_bus_address = pic->pictures[i].luma.bus_address;
  }
  return VP6DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecVp6Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  VP6DecPicture vpic;
  enum DecRet rv = VP6DecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].picture_info.is_intra_frame = vpic.is_intra_frame;
    pic->pictures[i].picture_info.is_golden_frame = vpic.is_golden_frame;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.nbr_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].p_output_frame;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_frame_bus_address;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecVp6Abort(VCDecInst *vcdec) {
  return VP6DecAbort(vcdec->inst);
}

static enum DecRet VCDecVp6AbortAfter(VCDecInst *vcdec) {
  return VP6DecAbortAfter(vcdec->inst);
}

static enum DecRet VCDecVp6EndOfStream(VCDecInst *vcdec) {
  return VP6DecEndOfStream(vcdec->inst);
}

static void VCDecVp6Release(VCDecInst *vcdec) {
   VP6DecRelease(vcdec->inst);
}
#endif /* ENABLE_VP6_SUPPORT */

#ifdef ENABLE_MPEG2_SUPPORT
static enum DecRet VCDecMpeg2Init(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct Mpeg2DecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.decoder_mode = config->decoder_mode;
  return Mpeg2DecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecMpeg2GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  Mpeg2DecInfo mpeg2_info;
  DWLmemset(&mpeg2_info, 0, sizeof(mpeg2_info));
  enum DecRet rv = Mpeg2DecGetInfo(vcdec->inst, &mpeg2_info);
  info->pic_width = mpeg2_info.frame_width;
  info->pic_height = mpeg2_info.frame_height;
  info->scaled_width = mpeg2_info.coded_width;
  info->scaled_height = mpeg2_info.coded_height;
  info->crop_params.crop_left_offset = 0;
  info->crop_params.crop_top_offset = 0;
  info->crop_params.crop_out_width = mpeg2_info.coded_width;
  info->crop_params.crop_out_height = mpeg2_info.coded_height;
  info->sar_width = 1;
  info->sar_height = 1;
  info->profile_and_level_indication = mpeg2_info.profile_and_level_indication;
  info->display_aspect_ratio = mpeg2_info.display_aspect_ratio;
  info->stream_format = mpeg2_info.stream_format;
  info->video_format = mpeg2_info.video_format;
  info->colour_primaries = mpeg2_info.colour_primaries;
  info->transfer_characteristics = mpeg2_info.transfer_characteristics;
  info->matrix_coefficients = mpeg2_info.matrix_coefficients;
  info->colour_description_present_flag = mpeg2_info.colour_description_present_flag;
  info->is_interlaced = mpeg2_info.interlaced_sequence;
  info->dpb_mode = mpeg2_info.dpb_mode;
  info->num_of_ref_frames = mpeg2_info.pic_buff_size;
  info->multi_buff_pp_size = mpeg2_info.multi_buff_pp_size;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  // info->output_format = mpeg2_info.output_format;
  if (mpeg2_info.output_format == MPEG2DEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  return rv;
}

static enum DecRet VCDecMpeg2SetInfo(VCDecInst *vcdec, struct DecConfig *config) {
  struct Mpeg2DecConfig dec_cfg;
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return Mpeg2DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecMpeg2Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  Mpeg2DecInput mpeg2_input;
  struct DecOutput mpeg2_output;
  DWLmemset(&mpeg2_input, 0, sizeof(mpeg2_input));
  DWLmemset(&mpeg2_output, 0, sizeof(mpeg2_output));
  mpeg2_input.stream = (u8*)param->stream;
  mpeg2_input.stream_bus_address = (addr_t)param->stream_bus_address;
  mpeg2_input.data_len = param->strm_len;
  mpeg2_input.pic_id = param->pic_id;
  mpeg2_input.skip_frame= param->skip_frame;
  mpeg2_output.strm_curr_pos = output->strm_curr_pos;
  rv = Mpeg2DecDecode(vcdec->inst, &mpeg2_input, &mpeg2_output);
  output->strm_curr_pos = mpeg2_output.strm_curr_pos;
  output->strm_curr_bus_address = mpeg2_output.strm_curr_bus_address;
  output->data_left = mpeg2_output.data_left;
  param->strm_len = mpeg2_input.data_len;
  return rv;
}

static enum DecRet VCDecMpeg2GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = Mpeg2DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecMpeg2AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return Mpeg2DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecMpeg2NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  Mpeg2DecPicture vpic;
  enum DecRet rv = Mpeg2DecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type[0];
    pic->pictures[i].picture_info.pic_coding_type_field = vpic.pic_coding_type[1];
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.first_field =vpic.first_field;
    pic->pictures[i].picture_info.repeat_first_field =vpic.repeat_first_field;
    pic->pictures[i].picture_info.single_field =vpic.single_field;
    pic->pictures[i].picture_info.output_other_field =vpic.output_other_field;
    pic->pictures[i].picture_info.repeat_frame_count =vpic.repeat_frame_count;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.dpb_mode = vpic.dpb_mode;
    pic->pictures[i].picture_info.time_code.hours = vpic.time_code.hours;
    pic->pictures[i].picture_info.time_code.minutes = vpic.time_code.minutes;
    pic->pictures[i].picture_info.time_code.seconds = vpic.time_code.seconds;
    pic->pictures[i].picture_info.time_code.pictures = vpic.time_code.pictures;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecMpeg2PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic) {
  Mpeg2DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(Mpeg2DecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.pictures[i].output_picture = (u8*)pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  return Mpeg2DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecMpeg2Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  Mpeg2DecPicture vpic;
  enum DecRet rv = Mpeg2DecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type[0] - 1;
    pic->pictures[i].picture_info.pic_coding_type_field = vpic.pic_coding_type[1] - 1;
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.first_field =vpic.first_field;
    pic->pictures[i].picture_info.repeat_first_field =vpic.repeat_first_field;
    pic->pictures[i].picture_info.single_field =vpic.single_field;
    pic->pictures[i].picture_info.output_other_field =vpic.output_other_field;
    pic->pictures[i].picture_info.repeat_frame_count =vpic.repeat_frame_count;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.dpb_mode = vpic.dpb_mode;
    pic->pictures[i].picture_info.time_code.hours = vpic.time_code.hours;
    pic->pictures[i].picture_info.time_code.minutes = vpic.time_code.minutes;
    pic->pictures[i].picture_info.time_code.seconds = vpic.time_code.seconds;
    pic->pictures[i].picture_info.time_code.pictures = vpic.time_code.pictures;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecMpeg2Abort(VCDecInst *vcdec) {
  return Mpeg2DecAbort(vcdec->inst);
}

static enum DecRet VCDecMpeg2AbortAfter(VCDecInst *vcdec) {
  return Mpeg2DecAbortAfter(vcdec->inst);
}

static enum DecRet VCDecMpeg2EndOfStream(VCDecInst *vcdec) {
  return Mpeg2DecEndOfStream(vcdec->inst);
}

static void VCDecMpeg2Release(VCDecInst *vcdec) {
   Mpeg2DecRelease(vcdec->inst);
}
#endif /* ENABLE_MPEG2_SUPPORT */

#ifdef ENABLE_MPEG4_SUPPORT
static enum DecRet VCDecMpeg4Init(VCDecInst *vcdec, struct DecInitConfig *config) {
  struct MP4DecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.rlc_mode = config->rlc_mode;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.decoder_mode = config->decoder_mode;
  /* check format */
  switch (config->dec_format) {
  case DEC_INPUT_MPEG4:
    dec_cfg.strm_fmt = MP4DEC_MPEG4;
    break;
  case DEC_INPUT_SORENSON:
    dec_cfg.strm_fmt = MP4DEC_SORENSON;
    break;
  case DEC_INPUT_CUSTOM_1:
    dec_cfg.strm_fmt = MP4DEC_CUSTOM_1;
    break;
  default:

    break;
  }
  return MP4DecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecMpeg4GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  MP4DecInfo mpeg4_info;
  DWLmemset(&mpeg4_info, 0, sizeof(mpeg4_info));
  enum DecRet rv = MP4DecGetInfo(vcdec->inst, &mpeg4_info);
  info->pic_width = mpeg4_info.frame_width;
  info->pic_height = mpeg4_info.frame_height;
  info->scaled_width = mpeg4_info.coded_width;
  info->scaled_height = mpeg4_info.coded_height;
  info->stream_format = mpeg4_info.stream_format;
  info->profile_and_level_indication = mpeg4_info.profile_and_level_indication;
  info->video_format = mpeg4_info.video_format;
  info->video_range = mpeg4_info.video_range;
  info->sar_width = mpeg4_info.par_width;
  info->sar_height = mpeg4_info.par_height;
  info->user_data_voslen = mpeg4_info.user_data_voslen;
  info->user_data_visolen = mpeg4_info.user_data_visolen;
  info->user_data_vollen = mpeg4_info.user_data_vollen;
  info->user_data_govlen = mpeg4_info.user_data_govlen;
  info->is_interlaced = mpeg4_info.interlaced_sequence;
  info->dpb_mode = mpeg4_info.dpb_mode;
  info->num_of_ref_frames = mpeg4_info.pic_buff_size;
  info->multi_buff_pp_size = mpeg4_info.multi_buff_pp_size;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  // info->output_format = mpeg4_info.output_format;
  if (mpeg4_info.output_format == MP4DEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  info->gmc_support = mpeg4_info.gmc_support;

  return rv;
}

static enum DecRet VCDecMpeg4SetInfo(VCDecInst *vcdec, struct DecConfig *config) {
  struct MP4DecConfig dec_cfg;
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return MP4DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecMpeg4Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  MP4DecInput mpeg4_input;
  struct DecOutput mpeg4_output;
  DWLmemset(&mpeg4_input, 0, sizeof(mpeg4_input));
  DWLmemset(&mpeg4_output, 0, sizeof(mpeg4_output));
  mpeg4_input.stream = (u8*)param->stream;
  mpeg4_input.stream_bus_address = (addr_t)param->stream_bus_address;
  mpeg4_input.data_len = param->strm_len;
  mpeg4_input.enable_deblock = param->enable_deblock;
  mpeg4_input.pic_id = param->pic_id;
  mpeg4_input.skip_frame= param->skip_frame;
  mpeg4_output.strm_curr_pos = output->strm_curr_pos;
  rv = MP4DecDecode(vcdec->inst, &mpeg4_input, &mpeg4_output);
  output->strm_curr_pos = (u8 *)mpeg4_output.strm_curr_pos;
  output->strm_curr_bus_address = mpeg4_output.strm_curr_bus_address;
  output->data_left = mpeg4_output.data_left;
  //param->strm_len = mpeg4_input.data_len;
  return rv;
}

static enum DecRet VCDecMpeg4GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = MP4DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecMpeg4AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return MP4DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecMpeg4NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  MP4DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(vpic));
  enum DecRet rv = MP4DecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.nbr_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].picture_info.time_code.hours = vpic.time_code.hours;
    pic->pictures[i].picture_info.time_code.minutes = vpic.time_code.minutes;
    pic->pictures[i].picture_info.time_code.seconds = vpic.time_code.seconds;
    pic->pictures[i].picture_info.time_code.time_incr = vpic.time_code.time_incr;
    pic->pictures[i].picture_info.time_code.time_res = vpic.time_code.time_res;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecMpeg4PictureConsumed(VCDecInst *vcdec, struct DecPictures *pic) {
  MP4DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(MP4DecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.pictures[i].output_picture = (u8*)pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  return MP4DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecMpeg4Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  MP4DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(vpic));
  enum DecRet rv = MP4DecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.nbr_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].picture_info.time_code.hours = vpic.time_code.hours;
    pic->pictures[i].picture_info.time_code.minutes = vpic.time_code.minutes;
    pic->pictures[i].picture_info.time_code.seconds = vpic.time_code.seconds;
    pic->pictures[i].picture_info.time_code.time_incr = vpic.time_code.time_incr;
    pic->pictures[i].picture_info.time_code.time_res = vpic.time_code.time_res;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecMpeg4Abort(VCDecInst *vcdec) {
  return MP4DecAbort(vcdec->inst);
}

static enum DecRet VCDecMpeg4AbortAfter(VCDecInst *vcdec) {
  return MP4DecAbortAfter(vcdec->inst);
}

static enum DecRet VCDecMpeg4EndOfStream(VCDecInst *vcdec) {
  return MP4DecEndOfStream(vcdec->inst);
}

static void VCDecMpeg4Release(VCDecInst *vcdec) {
   MP4DecRelease(vcdec->inst);
}

static enum DecRet VCDecMpeg4GetUserData(VCDecInst *vcdec, struct DecInputParameters* param,
                                         struct DecUserConf* user_data_config) {
  MP4DecInput mpeg4_input;
  DWLmemset(&mpeg4_input, 0, sizeof(mpeg4_input));
  mpeg4_input.stream = (u8*)param->stream;
  mpeg4_input.stream_bus_address = (addr_t)param->stream_bus_address;
  mpeg4_input.data_len = param->strm_len;
  mpeg4_input.enable_deblock = param->enable_deblock;
  mpeg4_input.pic_id = param->pic_id;
  mpeg4_input.skip_frame= param->skip_frame;
  return MP4DecGetUserData(vcdec->inst, &mpeg4_input, user_data_config);
}

static enum DecRet VCDecMpeg4SetCustomInfo(VCDecInst *vcdec, const u32 width, const u32 height) {
  return MP4DecSetCustomInfo(vcdec->inst, width, height);
}
#endif /* ENABLE_MPEG4_SUPPORT */

#ifdef ENABLE_AVS_SUPPORT
static enum DecRet VCDecAvsInit(VCDecInst *vcdec, struct DecInitConfig* config) {
  struct AvsDecConfig dec_cfg = {0, };
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.decoder_mode = config->decoder_mode;
  return AvsDecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecAvsGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  AvsDecInfo avs_info;
  DWLmemset(&avs_info, 0, sizeof(avs_info));
  enum DecRet rv = AvsDecGetInfo(vcdec->inst, &avs_info);
  info->pic_width = avs_info.frame_width;
  info->pic_height = avs_info.frame_height;
  info->scaled_width = avs_info.coded_width;
  info->scaled_height = avs_info.coded_height;
  info->profile_id = avs_info.profile_id;
  info->level_id = avs_info.level_id;
  info->display_aspect_ratio = avs_info.display_aspect_ratio;
  info->video_format = avs_info.video_format;
  info->video_range = avs_info.video_range;
  info->is_interlaced = avs_info.interlaced_sequence;
  info->dpb_mode = avs_info.dpb_mode;
  info->num_of_ref_frames = avs_info.pic_buff_size;
  info->multi_buff_pp_size = avs_info.multi_buff_pp_size;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  // info->output_format = avs_info.output_format;
  if (avs_info.output_format == AVSDEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  return rv;
}

static enum DecRet VCDecAvsSetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct AvsDecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return AvsDecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecAvsDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  AvsDecInput avs_input;
  struct DecOutput avs_output;
  DWLmemset(&avs_input, 0, sizeof(avs_input));
  DWLmemset(&avs_output, 0, sizeof(avs_output));
  avs_input.stream = (u8*)param->stream;
  avs_input.stream_bus_address = (addr_t)param->stream_bus_address;
  avs_input.data_len = param->strm_len;
  avs_input.pic_id = param->pic_id;
  avs_input.skip_frame= param->skip_frame;
  avs_output.strm_curr_pos = output->strm_curr_pos; /* used in AvsDecDecode */
  rv = AvsDecDecode(vcdec->inst, &avs_input, &avs_output);
  output->strm_curr_pos = avs_output.strm_curr_pos;
  output->strm_curr_bus_address = avs_output.strm_curr_bus_address;
  output->data_left = avs_output.data_left;
  // param->strm_len = avs_input.data_len;
  return rv;
}

static enum DecRet VCDecAvsNextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  AvsDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(vpic));
  enum DecRet rv = AvsDecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.first_field =vpic.first_field;
    pic->pictures[i].picture_info.repeat_first_field =vpic.repeat_first_field;
    pic->pictures[i].picture_info.repeat_frame_count =vpic.repeat_frame_count;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].picture_info.time_code.hours = vpic.time_code.hours;
    pic->pictures[i].picture_info.time_code.minutes = vpic.time_code.minutes;
    pic->pictures[i].picture_info.time_code.seconds = vpic.time_code.seconds;
    pic->pictures[i].picture_info.time_code.pictures = vpic.time_code.pictures;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecAvsPictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  AvsDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(AvsDecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.pictures[i].output_picture = (u8*)pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  return AvsDecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecAvsEndOfStream(VCDecInst *vcdec) {
  return AvsDecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecAvsGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  DWLmemset(&hbuf, 0, sizeof(hbuf));
  rv = AvsDecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecAvsAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return AvsDecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecAvsPeek(VCDecInst *vcdec, struct DecPictures *pic) {
  AvsDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(vpic));
  enum DecRet rv = AvsDecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.first_field =vpic.first_field;
    pic->pictures[i].picture_info.repeat_first_field =vpic.repeat_first_field;
    pic->pictures[i].picture_info.repeat_frame_count =vpic.repeat_frame_count;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].picture_info.time_code.hours = vpic.time_code.hours;
    pic->pictures[i].picture_info.time_code.minutes = vpic.time_code.minutes;
    pic->pictures[i].picture_info.time_code.seconds = vpic.time_code.seconds;
    pic->pictures[i].picture_info.time_code.pictures = vpic.time_code.pictures;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecAvsAbort(VCDecInst *vcdec) {
  return AvsDecAbort(vcdec->inst);
}

static enum DecRet VCDecAvsAbortAfter(VCDecInst *vcdec) {
  return AvsDecAbortAfter(vcdec->inst);
}

static void VCDecAvsRelease(VCDecInst *vcdec) {
  AvsDecRelease(vcdec->inst);
}
#endif /* ENABLE_AVS_SUPPORT */

#ifdef ENABLE_VC1_SUPPORT
static enum DecRet VCDecVc1Init(VCDecInst *vcdec, struct DecInitConfig* config) {
  struct VC1DecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.p_meta_data = &config->meta_data;
  dec_cfg.decoder_mode = config->decoder_mode;
  return VC1DecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecVc1GetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  VC1DecInfo vc1_info;
  DWLmemset(&vc1_info, 0, sizeof(vc1_info));
  enum DecRet rv = VC1DecGetInfo(vcdec->inst, &vc1_info);
  info->pic_width = vc1_info.max_coded_width;
  info->pic_height = vc1_info.max_coded_height;
  info->scaled_width = vc1_info.coded_width;
  info->scaled_height = vc1_info.coded_height;
  info->sar_width = vc1_info.par_width;
  info->sar_height = vc1_info.par_height;
  info->frame_rate_numerator = vc1_info.frame_rate_numerator;
  info->frame_rate_denominator = vc1_info.frame_rate_denominator;
  info->is_interlaced = vc1_info.interlaced_sequence;
  info->dpb_mode = vc1_info.dpb_mode;
  info->buf_release_flag = vc1_info.buf_release_flag;
  info->multi_buff_pp_size = vc1_info.multi_buff_pp_size;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  if (vc1_info.output_format == VC1DEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  return rv;
}

static enum DecRet VCDecVc1SetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct VC1DecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return VC1DecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecVc1Decode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  VC1DecInput vc1_input;
  struct DecOutput vc1_output;
  DWLmemset(&vc1_input, 0, sizeof(vc1_input));
  DWLmemset(&vc1_output, 0, sizeof(vc1_output));
  vc1_input.stream = (const u8*)param->stream;
  vc1_input.stream_bus_address = (addr_t)param->stream_bus_address;
  vc1_input.stream_size = param->strm_len;
  vc1_input.pic_id = param->pic_id;
  vc1_input.skip_frame= param->skip_frame;
  rv = VC1DecDecode(vcdec->inst, &vc1_input, &vc1_output);
  output->strm_curr_pos = vc1_output.strm_curr_pos;
  output->strm_curr_bus_address = vc1_output.strm_curr_bus_address;
  output->data_left = vc1_output.data_left;
  return rv;
}

static enum DecRet VCDecVc1NextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  VC1DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(vpic));
  enum DecRet rv = VC1DecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id[0];
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type[0];
    pic->pictures[i].picture_info.pic_coding_type_field = vpic.pic_coding_type[1];
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.first_field =vpic.first_field;
    pic->pictures[i].picture_info.repeat_first_field =vpic.repeat_first_field;
    pic->pictures[i].picture_info.repeat_frame_count =vpic.repeat_frame_count;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecVc1PictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  VC1DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(VC1DecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.pictures[i].output_picture = (u8*)pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  return VC1DecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecVc1EndOfStream(VCDecInst *vcdec) {
  return VC1DecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecVc1GetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  DWLmemset(&hbuf, 0, sizeof(hbuf));
  rv = VC1DecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecVc1AddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return VC1DecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecVc1Peek(VCDecInst *vcdec, struct DecPictures *pic) {
  VC1DecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(vpic));
  enum DecRet rv = VC1DecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id[0];
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type[0];
    pic->pictures[i].picture_info.pic_coding_type_field = vpic.pic_coding_type[1];
    pic->pictures[i].sequence_info.is_interlaced = vpic.interlaced;
    pic->pictures[i].picture_info.field_picture =vpic.field_picture;
    pic->pictures[i].picture_info.top_field =vpic.top_field;
    pic->pictures[i].picture_info.first_field =vpic.first_field;
    pic->pictures[i].picture_info.repeat_first_field =vpic.repeat_first_field;
    pic->pictures[i].picture_info.repeat_frame_count =vpic.repeat_frame_count;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecVc1Abort(VCDecInst *vcdec) {
  return VC1DecAbort(vcdec->inst);
}

static enum DecRet VCDecVc1AbortAfter(VCDecInst *vcdec) {
  return VC1DecAbortAfter(vcdec->inst);
}

static void VCDecVc1Release(VCDecInst *vcdec) {
  VC1DecRelease(vcdec->inst);
}

#endif /* ENABLE_VC1_SUPPORT */

#ifdef ENABLE_RV_SUPPORT
static enum DecRet VCDecRvInit(VCDecInst *vcdec, struct DecInitConfig* config) {
  struct RvDecConfig dec_cfg = {0, };
  dec_cfg.error_handling = config->error_handling;
  dec_cfg.error_ratio = config->error_ratio;
  dec_cfg.use_adaptive_buffers = config->use_adaptive_buffers;
  dec_cfg.guard_size = config->guard_size;
  dec_cfg.frame_code_length = config->frame_code_length;
  dec_cfg.num_frame_buffers = config->num_frame_buffers;
  dec_cfg.frame_sizes = config->frame_sizes;
  dec_cfg.rv_version = config->rv_version;
  dec_cfg.max_frame_width = config->max_frame_width;
  dec_cfg.max_frame_height = config->max_frame_height;
  dec_cfg.decoder_mode = config->decoder_mode;

  return RvDecInit(&vcdec->inst, config->dwl_inst, &dec_cfg);
}

static enum DecRet VCDecRvGetInfo(VCDecInst *vcdec, struct DecSequenceInfo* info) {
  RvDecInfo rv_info;
  DWLmemset(&rv_info, 0, sizeof(rv_info));
  enum DecRet rv = RvDecGetInfo(vcdec->inst, &rv_info);
  info->pic_width = rv_info.frame_width;
  info->pic_height = rv_info.frame_height;
  info->scaled_width = rv_info.coded_width;
  info->scaled_height = rv_info.coded_height;
  info->multi_buff_pp_size = rv_info.multi_buff_pp_size;
  info->num_of_ref_frames = rv_info.pic_buff_size;
  info->dpb_mode = rv_info.dpb_mode;
  info->bit_depth_luma = info->bit_depth_chroma = 8;
  if (rv_info.output_format == RVDEC_SEMIPLANAR_YUV420)
    info->output_format = DEC_OUT_FRM_YUV420SP;
  else
    info->output_format = DEC_OUT_FRM_YUV420TILE;
  info->out_pic_coded_width = rv_info.out_pic_coded_width;
  info->out_pic_coded_height = rv_info.out_pic_coded_height;
  info->out_pic_stat = rv_info.out_pic_stat;
  return rv;
}

static enum DecRet VCDecRvSetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  struct RvDecConfig dec_cfg;
  DWLmemset(&dec_cfg, 0, sizeof(dec_cfg));
  dec_cfg.align = config->align;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return RvDecSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecRvDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  RvDecInput rv_input;
  struct DecOutput rv_output;
  DWLmemset(&rv_input, 0, sizeof(rv_input));
  DWLmemset(&rv_output, 0, sizeof(rv_output));
  rv_input.stream = (u8*)param->stream;
  rv_input.stream_bus_address = (addr_t)param->stream_bus_address;
  rv_input.data_len = param->strm_len;
  rv_input.pic_id = param->pic_id;
  rv_input.timestamp = param->timestamp;
  rv_input.slice_info_num = param->slice_info_num;
  rv_input.slice_info = (struct DecSliceInfo*)param->slice_info;
  rv_input.skip_frame= param->skip_frame;
  rv_output.strm_curr_pos = output->strm_curr_pos; /* it will be used in RvDecDecode. */
  rv = RvDecDecode(vcdec->inst, &rv_input, &rv_output);
  output->strm_curr_pos = rv_output.strm_curr_pos;
  output->strm_curr_bus_address = rv_output.strm_curr_bus_address;
  output->data_left = rv_output.data_left;
  return rv;
}

static enum DecRet VCDecRvNextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  RvDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(RvDecPicture));
  enum DecRet rv = RvDecNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecRvPictureConsumed(VCDecInst *vcdec, struct DecPictures* pic) {
  RvDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(RvDecPicture));
  u32 i;
  for (i = 0; i < DEC_MAX_OUT_COUNT;i++) {
    vpic.pictures[i].output_format = pic->pictures[i].picture_info.format;
    vpic.pictures[i].output_picture = (u8*)pic->pictures[i].luma.virtual_address;
    vpic.pictures[i].output_picture_bus_address = pic->pictures[i].luma.bus_address;
  }
  return RvDecPictureConsumed(vcdec->inst, &vpic);
}

static enum DecRet VCDecRvEndOfStream(VCDecInst *vcdec) {
  return RvDecEndOfStream(vcdec->inst);
}

static enum DecRet VCDecRvGetBufferInfo(VCDecInst *vcdec, struct DecBufferInfo *buf_info) {
  struct DecBufferInfo hbuf;
  enum DecRet rv;
  u32 i;

  rv = RvDecGetBufferInfo(vcdec->inst, &hbuf);
  buf_info->next_buf_size = hbuf.next_buf_size;
  buf_info->buf_num = hbuf.buf_num;
  buf_info->buf_to_free = hbuf.buf_to_free;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    buf_info->ystride[i] = hbuf.ystride[i];
    buf_info->cstride[i] = hbuf.cstride[i];
  }
  return rv;
}

static enum DecRet VCDecRvAddBuffer(VCDecInst *vcdec, struct DWLLinearMem *buf) {
  return RvDecAddBuffer(vcdec->inst, buf);
}

static enum DecRet VCDecRvPeek(VCDecInst *vcdec, struct DecPictures *pic) {
  RvDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(RvDecPicture));
  enum DecRet rv = RvDecPeek(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].picture_info.is_intra_frame = vpic.key_picture;
    pic->pictures[i].picture_info.pic_id = vpic.pic_id;
    pic->pictures[i].picture_info.decode_id = vpic.decode_id;
    pic->pictures[i].picture_info.pic_coding_type = vpic.pic_coding_type;
    pic->pictures[i].picture_info.nbr_of_err_mbs = vpic.number_of_err_mbs;
    pic->pictures[i].picture_info.cycles_per_mb = vpic.cycles_per_mb;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].frame_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].frame_height;
    pic->pictures[i].sequence_info.scaled_width = vpic.pictures[i].coded_width;
    pic->pictures[i].sequence_info.scaled_height = vpic.pictures[i].coded_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].pic_width = vpic.pictures[i].coded_width;
    pic->pictures[i].pic_height = vpic.pictures[i].coded_height;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.crop_params = vpic.pictures[i].crop_params;
    pic->pictures[i].sequence_info.bit_depth_luma = 8;
    pic->pictures[i].sequence_info.bit_depth_chroma = 8;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static enum DecRet VCDecRvAbort(VCDecInst *vcdec) {
  return RvDecAbort(vcdec->inst);
}

static enum DecRet VCDecRvAbortAfter(VCDecInst *vcdec) {
  return RvDecAbortAfter(vcdec->inst);
}

static void VCDecRvRelease(VCDecInst *vcdec) {
  RvDecRelease(vcdec->inst);
}

#endif /* ENABLE_RV_SUPPORT */

#ifdef ENABLE_PPDEC_SUPPORT
static enum DecRet VCDecPpInit(VCDecInst *vcdec, struct DecInitConfig* config) {
  return PPInit(&vcdec->inst, config->dwl_inst);
}

static enum DecRet VCDecPpSetInfo(VCDecInst *vcdec, struct DecConfig* config) {
  PPConfig dec_cfg;
  dec_cfg.in_format = config->in_format;
  dec_cfg.in_stride = config->in_stride;
  dec_cfg.in_height = config->in_height;
  dec_cfg.in_width = config->in_width;
  dec_cfg.in_lu_stride = config->in_lu_stride;
  dec_cfg.in_ch_stride = config->in_ch_stride;
  dec_cfg.in_lut_stride = config->in_lut_stride;
  dec_cfg.in_cht_stride = config->in_cht_stride;
  dec_cfg.in_luma_bitdepth = config->in_luma_bitdepth;
  dec_cfg.in_chroma_bitdepth = config->in_chroma_bitdepth;
  dec_cfg.in_rfc = config->in_rfc;
  dec_cfg.chroma_format_idc = config->chroma_format;
  dec_cfg.align = config->align;
  dec_cfg.pp_in_buffer = config->pp_in_buffer;
  dec_cfg.pp_out_buffer = config->pp_out_buffer;
  DWLmemcpy(dec_cfg.ppu_config, config->ppu_cfg, sizeof(config->ppu_cfg));
  return PPSetInfo(vcdec->inst, &dec_cfg);
}

static enum DecRet VCDecPpDecode(VCDecInst *vcdec, struct DecOutput* output, struct DecInputParameters* param) {
  enum DecRet rv;
  rv = PPDecode(vcdec->inst);
  return rv;
}

static enum DecRet VCDecPpNextPicture(VCDecInst *vcdec, struct DecPictures* pic) {
  PPDecPicture vpic;
  DWLmemset(&vpic, 0, sizeof(PPDecPicture));
  enum DecRet rv = PPNextPicture(vcdec->inst, &vpic);
  for (u32 i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    pic->pictures[i].pic_width = vpic.pictures[i].pic_width;
    pic->pictures[i].pic_height = vpic.pictures[i].pic_height;
    pic->pictures[i].pic_stride = vpic.pictures[i].pic_stride;
    pic->pictures[i].pic_stride_ch = vpic.pictures[i].pic_stride_ch;
    pic->pictures[i].luma.virtual_address = (u32*)vpic.pictures[i].output_picture;
    pic->pictures[i].luma.bus_address = vpic.pictures[i].output_picture_bus_address;
    pic->pictures[i].chroma.virtual_address = (u32*)vpic.pictures[i].output_picture_chroma;
    pic->pictures[i].chroma.bus_address = vpic.pictures[i].output_picture_chroma_bus_address;
    pic->pictures[i].picture_info.format = vpic.pictures[i].output_format;
    pic->pictures[i].sequence_info.pic_width = vpic.pictures[i].pic_width;
    pic->pictures[i].sequence_info.pic_height = vpic.pictures[i].pic_height;
    pic->pictures[i].sequence_info.bit_depth_luma = vpic.pictures[i].bit_depth_luma;
    pic->pictures[i].sequence_info.bit_depth_chroma = vpic.pictures[i].bit_depth_chroma;
    pic->pictures[i].sequence_info.sar_width = 1;
    pic->pictures[i].sequence_info.sar_height = 1;
#ifdef SUPPORT_DEC400
    pic->pictures[i].luma_table = vpic.pictures[i].dec400_luma_table;
    pic->pictures[i].chroma_table = vpic.pictures[i].dec400_chroma_table;
#endif
  }
  return rv;
}

static void VCDecPpRelease(VCDecInst *vcdec) {
  PPRelease(vcdec->inst);
}
#endif /* ENABLE_PPDEC_SUPPORT */

/*------------------------------------------------------------------------------*/
#if defined(ENABLE_VP9_SUPPORT) || defined(ENABLE_AV1_SUPPORT)
/* function copied from the libvpx */
static void ParseSuperframeIndex(const u8* data, size_t data_sz, const u8* buf,
                                 size_t buf_sz, u32 sizes[8], i32* count,
                                 int av1baseline, struct strmInfo *stream_info) {
  u8 marker;
  SwReadByteFn *fn_read_byte;
  u8* buf_end = (u8*)buf + buf_sz;

  fn_read_byte = SwGetReadByteFunc(stream_info);

  if (av1baseline)
    marker = data[0];
  else {
    if ((data + data_sz - 1) < buf_end)
      marker = fn_read_byte(data + data_sz - 1, buf_sz, stream_info);
    else
      marker = fn_read_byte(data + (i32)data_sz - 1 - (i32)buf_sz, buf_sz, stream_info);
  }
  *count = 0;

  if ((marker & 0xe0) == 0xc0) {
    const u32 frames = (marker & 0x7) + 1;
    const u32 mag = ((marker >> 3) & 0x3) + 1;
    const u32 index_sz = 2 + mag * frames;

    if (av1baseline) {
      u32 frame_sz_sum = 0;
      if (data_sz >= index_sz && data[index_sz - 1] == marker) {
        u32 i, j;
        if (stream_info->low_latency) {
	  const u8* read_end = data + 1 + ((frames - 1) * (mag - 1));
	  if (read_end > (buf + buf_sz)) read_end -= buf_sz;
	  u32 len = 0;
	  do {
            if (read_end >= stream_info->strm_vir_start_addr)
              len = read_end - stream_info->strm_vir_start_addr;
            else
              len = read_end + buf_sz - stream_info->strm_vir_start_addr;
            sched_yield();
          } while (len > stream_info->send_len && !stream_info->last_flag);
        }
        const u8* x = data + 1;

        for (i = 0; i < frames - 1; i++) {
          u32 this_sz = 0;

          for (j = 0; j < mag; j++) this_sz |= (*x++) << (j * 8);
          this_sz += 1;
          sizes[i] = this_sz;
          frame_sz_sum += this_sz;
        }

        sizes[i] = data_sz - index_sz - frame_sz_sum;

        *count = frames;
      }
    } else {
      u8 index_value;
      u32 turn_around = 0;
      if((data + data_sz - index_sz) < buf_end)
        index_value = fn_read_byte(data + data_sz - index_sz, buf_sz, stream_info);
      else {
        index_value = fn_read_byte(data + data_sz - index_sz - buf_sz, buf_sz, stream_info);
        turn_around = 1;
      }
      if (data_sz >= index_sz && index_value == marker) {
        /* found a valid superframe index */
        u32 i, j;
        const u8* x = data + data_sz - index_sz + 1;
        if(turn_around)
          x = data + data_sz - index_sz + 1 - buf_sz;

        for (i = 0; i < frames; i++) {
          u32 this_sz = 0;

          for (j = 0; j < mag; j++) {
            if (x == buf + buf_sz)
              x = buf;
            this_sz |= fn_read_byte(x, buf_sz, stream_info) << (j * 8);
            x++;
          }
          sizes[i] = this_sz;
        }

        *count = frames;
      }
    }
  }
}

static void GetOutPicBufferSize(u32 height, u32 luma_stride, u32 chroma_stride,
	                              enum DecPictureFormat output_format,
                                u32* luma_size, u32* chroma_size) {
  if (IS_PIC_TILE(output_format)) {
    *luma_size = luma_stride * (NEXT_MULTIPLE(height, 4) / 4);
    *chroma_size = chroma_stride * (NEXT_MULTIPLE(height / 2, 4) / 4);
  } else if (IS_PIC_PLANAR(output_format)) {
    if (IS_PIC_RGB(output_format)) {
      *luma_size = luma_stride * height * 3;
      *chroma_size = 0;
    } else {
      *luma_size = luma_stride * height;
      *chroma_size = chroma_stride * height;
    }
  } else if (output_format == DEC_OUT_FRM_RFC) {
    *luma_size = luma_stride * height / 4;
    *chroma_size = chroma_stride * height / 8;
  } else if (IS_PIC_REF_TILED8x8(output_format)) {
        *luma_size = luma_stride * (NEXT_MULTIPLE(height, 8) / 8);
        *chroma_size = chroma_stride * (NEXT_MULTIPLE(height / 2, 4) / 4);
  } else {
    *luma_size = luma_stride * height;
    if (!IS_PIC_RGB(output_format))
      *chroma_size = chroma_stride * height / 2;
  }
}
#endif /* #if defined(ENABLE_VP9_SUPPORT) || defined(ENABLE_AV1_SUPPORT) */

#ifdef ENABLE_AV1_SUPPORT
static int Av1Leb128(const u8* p, int* len, const u8 *buf, u32 buf_len) {
  int s = 0;
  for (int i = 0; i < 8; i++) {
    u8 b = *p++;
    if (p >= buf + buf_len)
      p -= buf_len;
    s |= ((u64)(b & 0x7f)) << (i * 7);
    if (!(b & 0x80)) {
      *len = i + 1;
      break;
    }
  }
  return s;
}
#endif /* #ifdef ENABLE_AV1_SUPPORT */

#define DEC_RET_STR_CASE(rv) case (rv): return(#rv)
char *VCDecRetStr(enum DecRet rv) {
  switch (rv) {
  DEC_RET_STR_CASE(DEC_OK);
  DEC_RET_STR_CASE(DEC_STRM_PROCESSED);
  DEC_RET_STR_CASE(DEC_DISCARD_INTERNAL);
  DEC_RET_STR_CASE(DEC_PIC_RDY);
  DEC_RET_STR_CASE(DEC_PIC_DECODED);
  DEC_RET_STR_CASE(DEC_HDRS_RDY);
  DEC_RET_STR_CASE(DEC_DP_HDRS_RDY);
  DEC_RET_STR_CASE(DEC_ADVANCED_TOOLS);
  DEC_RET_STR_CASE(DEC_SLICE_RDY);
  DEC_RET_STR_CASE(DEC_PENDING_FLUSH);
  DEC_RET_STR_CASE(DEC_NONREF_PIC_SKIPPED);
  DEC_RET_STR_CASE(DEC_END_OF_STREAM);
  DEC_RET_STR_CASE(DEC_END_OF_SEQ);
  DEC_RET_STR_CASE(DEC_WAITING_FOR_BUFFER);
  DEC_RET_STR_CASE(DEC_SCAN_PROCESSED);
  DEC_RET_STR_CASE(DEC_ABORTED);
  DEC_RET_STR_CASE(DEC_FLUSHED);
  DEC_RET_STR_CASE(DEC_BUF_EMPTY);
  DEC_RET_STR_CASE(DEC_RESOLUTION_CHANGED);
  DEC_RET_STR_CASE(DEC_VOS_END);
  DEC_RET_STR_CASE(DEC_PARAM_SET_PARSED);
  DEC_RET_STR_CASE(DEC_SEI_PARSED);
  DEC_RET_STR_CASE(DEC_PB_PIC_SKIPPED);
  DEC_RET_STR_CASE(DEC_PARAM_ERROR);
  DEC_RET_STR_CASE(DEC_STRM_ERROR);
  DEC_RET_STR_CASE(DEC_NOT_INITIALIZED);
  DEC_RET_STR_CASE(DEC_MEMFAIL);
  DEC_RET_STR_CASE(DEC_INITFAIL);
  DEC_RET_STR_CASE(DEC_HDRS_NOT_RDY);
  DEC_RET_STR_CASE(DEC_STREAM_NOT_SUPPORTED);
  DEC_RET_STR_CASE(DEC_EXT_BUFFER_REJECTED);
  DEC_RET_STR_CASE(DEC_INFOPARAM_ERROR);
  DEC_RET_STR_CASE(DEC_ERROR);
  DEC_RET_STR_CASE(DEC_UNSUPPORTED);
  DEC_RET_STR_CASE(DEC_INVALID_STREAM_LENGTH);
  DEC_RET_STR_CASE(DEC_INVALID_INPUT_BUFFER_SIZE);
  DEC_RET_STR_CASE(DEC_INCREASE_INPUT_BUFFER);
  DEC_RET_STR_CASE(DEC_SLICE_MODE_UNSUPPORTED);
  DEC_RET_STR_CASE(DEC_METADATA_FAIL);
  DEC_RET_STR_CASE(DEC_NO_REFERENCE);
  DEC_RET_STR_CASE(DEC_PARAM_SET_ERROR);
  DEC_RET_STR_CASE(DEC_SEI_ERROR);
  DEC_RET_STR_CASE(DEC_SLICE_HDR_ERROR);
  DEC_RET_STR_CASE(DEC_REF_PICS_ERROR);
  DEC_RET_STR_CASE(DEC_NALUNIT_ERROR);
  DEC_RET_STR_CASE(DEC_AU_BOUNDARY_ERROR);
  DEC_RET_STR_CASE(DEC_STREAM_ERROR_DEDECTED);
  DEC_RET_STR_CASE(DEC_NO_DECODING_BUFFER);
  DEC_RET_STR_CASE(DEC_HW_RESERVED);
  DEC_RET_STR_CASE(DEC_HW_TIMEOUT);
  DEC_RET_STR_CASE(DEC_HW_BUS_ERROR);
  DEC_RET_STR_CASE(DEC_SYSTEM_ERROR);
  DEC_RET_STR_CASE(DEC_DWL_ERROR);
  DEC_RET_STR_CASE(DEC_FATAL_SYSTEM_ERROR);
  DEC_RET_STR_CASE(DEC_HW_EXT_TIMEOUT);
  DEC_RET_STR_CASE(DEC_EVALUATION_LIMIT_EXCEEDED);
  DEC_RET_STR_CASE(DEC_FORMAT_NOT_SUPPORTED);
  default: return("Unknown return code.\n");
  }
}

#ifdef CASE_INFO_STAT
static void WriteInfo(u32* info, u32 num,  FILE* caseprint) {
  u8 i = 0;

  if(num == 0) {
    fprintf(caseprint, "%s", " |");
    return;
  }
  for(i = 0; i < num ;i++) {
    if(i == 0)
      fprintf(caseprint, "%s", "[");
    if(i == 0 && num == 1)
      fprintf(caseprint, "%d%s|",info[i], "]");
    else if(i == num - 1)
      fprintf(caseprint,"%d%s|", info[i],"]");
    else
      fprintf(caseprint,"%d,", info[i]);
  }
}
static void VCDecInfoCollect(CaseInfo* case_info){
  FILE* cp = fopen("caseprint.txt", "wb");

  char f[10];
  u8 i;
  u8 j = 0;
  u32 num;
  char p[10],s[100];
  memset(s, 0, 100);

  switch(case_info->format) {
    case DEC_MPEG4:
      if(!case_info->codec)  case_info->codec = DEC_MODE_MPEG4;
      sprintf(f, "%s", "mpeg4");
      break;
    case DEC_MPEG2:
      if(!case_info->codec)  case_info->codec = DEC_MODE_MPEG2;
      sprintf(f, "%s", "mpeg2");
      break;
    case DEC_VP6:
      if(!case_info->codec)  case_info->codec = DEC_MODE_VP6;
      sprintf(f, "%s", "vp6");
      break;
    case DEC_VP8:
      if(!case_info->codec)  case_info->codec = DEC_MODE_VP8;
      sprintf(f, "%s", "vp8");
      break;
    case DEC_VP9:
      if(!case_info->codec)  case_info->codec = DEC_MODE_VP8;
      sprintf(f, "%s", "vp9");
      break;
    case DEC_HEVC:
      if(!case_info->codec)  case_info->codec = DEC_MODE_HEVC;
      sprintf(f, "%s", "hevc");
      break;
    case DEC_H264:
      sprintf(f, "%s", "h264"); break;
    case DEC_AVS:
      if(!case_info->codec)  case_info->codec = DEC_MODE_AVS;
      sprintf(f, "%s", "avs");
      break;
    case DEC_AVS2:
      if(!case_info->codec)  case_info->codec = DEC_MODE_AVS2;
      sprintf(f, "%s", "avs2");
      break;
    case DEC_AV1:
      if(!case_info->codec)  case_info->codec = DEC_MODE_AV1;
      sprintf(f, "%s", "av1");
      break;
    case DEC_JPEG:
      if(!case_info->codec)  case_info->codec = DEC_MODE_JPEG;
      sprintf(f, "%s", "jpeg");
      break;
    case DEC_VC1:
      if(!case_info->codec)  case_info->codec = DEC_MODE_VC1;
      sprintf(f, "%s", "vc1");
      break;
    case DEC_RV:
      if(!case_info->codec)  case_info->codec = DEC_MODE_RV;
      sprintf(f, "%s", "rv");
      break;
    case DEC_VVC:
      if(!case_info->codec)  case_info->codec = DEC_MODE_VVC;
      sprintf(f, "%s", "vvc");
      break;
  }

  for(i=0; i<20 && j<case_info->frame_num && j<10; i++) {
    if(case_info->codec == DEC_JPEG) break;
    switch(case_info->frame_type[i]) {
      case I_FRAME: strcat(s, "I,"); break;
      case B_FRAME: strcat(s, "B,"); break;
      case P_FRAME: strcat(s, "P,"); break;
      case GB_FRAME: strcat(s, "GB,"); break;
      case F_FRAME: strcat(s, "F,"); break;
      case S_FRAME: strcat(s, "S,"); break;
      case G_FRAME: strcat(s, "G,"); break;
      case BI_FRAME: strcat(s, "BI,"); break;
      case FIELD_I_I: strcat(s, "[I,I],"); break;
      case FIELD_I_P: strcat(s, "[I,P],"); break;
      case FIELD_P_I: strcat(s, "[I,P],"); break;
      case FIELD_P_P: strcat(s, "[P,P],"); break;
      case FIELD_B_B: strcat(s, "[B,B],"); break;
      case FIELD_BI_B: strcat(s, "[BI,B],"); break;
      case FIELD_B_BI: strcat(s, "[B,BI],"); break;
      case FIELD_BI_BI: strcat(s, "[BI,BI],"); break;
      case I_FIELED_0:
        if (i < 19  && case_info->frame_type[i+1] > B_FIELED_0 )
          strcat(s, "[I:");
        else
          strcat(s, "I,");
        break;
      case P_FIELED_0:
        if (i < 19 && case_info->frame_type[i+1] > B_FIELED_0 )
          strcat(s, "[P:");
        else
          strcat(s, "P,");
        break;
      case B_FIELED_0:
        if (i < 19 && case_info->frame_type[i+1] > B_FIELED_0 )
          strcat(s, "[B:");
        else
          strcat(s, "B,");
        break;
      case I_FIELED_1: strcat(s, "I],"); break;
      case P_FIELED_1: strcat(s, "P],"); break;
      case B_FIELED_1: strcat(s, "B],"); break;
    }
    if(case_info->frame_type[i] >= I_FIELED_1 || case_info->frame_type[i] < I_FIELED_0)
      j++;
  }
  s[strlen(s)-1] = '\0';

  switch(case_info->chroma_format_id) {
    case 0: sprintf(p, "%s", "YUV400"); break;
    case 1: sprintf(p, "%s", "YUV420"); break;
    case 2: sprintf(p, "%s", "YUV422"); break;
    case 3: sprintf(p, "%s", "YUV411"); break;
    case 4: sprintf(p, "%s", "YUV440"); break;
    case 5: sprintf(p, "%s", "YUV444"); break;
    }

  fprintf(cp, "%s|%d|%s%s%s|%d|%d|%d|%d|%d|%d|%d|%s%d,%d%s|%d|%d|%s|",
          f, case_info->codec,"[", s, "]", case_info->frame_num > 0? case_info->frame_num : 1, case_info->scan_count,
          case_info->min_cb_size, case_info->max_cb_size, case_info->bit_depth,
          case_info->display_width, case_info->display_height, "(",case_info->crop_x, case_info->crop_y, ")",
          case_info->decode_width, case_info->decode_height, case_info->frame_num > 0? p : " " );

  num = case_info->frame_num > 10 ? 10 : case_info->frame_num;
  WriteInfo(case_info->slice_num, num, cp);
  WriteInfo(case_info->ppin_luma_size, num, cp);
  WriteInfo(case_info->bit_depth_y_minus8, num, cp);
  WriteInfo(case_info->bit_depth_c_minus8, num, cp);
  WriteInfo(case_info->blackwhite_e, num, cp);
  WriteInfo(case_info->num_tile_cols_8k, num, cp);
  WriteInfo(case_info->fieldpic_flag, num, cp);
  WriteInfo(case_info->fieldmode, num, cp);

  if(case_info->frame_num)
    fprintf(cp,"%d|",case_info->bitrate/case_info->frame_num);
  else
    fprintf(cp,"%s|", "invalid");

  fprintf(cp, "%s|%s|%s|%s|%s%s%s%s%s%s%s%s%s%s", case_info->crop_flag? "x":" ", case_info->chroma_flag?  "x":" ",
          case_info->depth_flag?  "x":" ", case_info->resolution_flag? "x":" ",
          case_info->interlace_flag? "interlace ":"", case_info->intrabc_flag? "intrabc ":"",
          case_info->tile_flag? "tile ":"", case_info->aso_flag? "aso ":"",
          case_info->fmo_flag? "fmo ":"", case_info->pjpeg_flag? "pjpeg ":"",
          case_info->interintra ? "interintra ":"", case_info->palette_mode ? "palette_mode ":"",
          case_info->filter_intra_pred ? "filter_intra_pred ":"", case_info->intra_edge_filter? "intra_edge_filter ":"");

  if(!case_info->interlace_flag && !case_info->intrabc_flag && !case_info->tile_flag && !case_info->aso_flag
     && !case_info->fmo_flag && !case_info->pjpeg_flag && !case_info->thumb_flag && !case_info->cavlc_flag
     && !case_info->interintra && !case_info->palette_mode && !case_info->filter_intra_pred
     && !case_info->intra_edge_filter)
     fprintf(cp, "%s", " ");
  if(cp) fclose(cp);
}
#endif
