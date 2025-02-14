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

#include "version.h"
#include "dwl.h"
#include "basetype.h"
#include "jpegdecapi.h"
#include "jpegdeccontainer.h"
#include "jpegdecmarkers.h"
#include "jpegdecinternal.h"
#include "jpegdecutils.h"
#include "jpegdechdrs.h"
#include "regdrv.h"
#include "jpeg_pp_pipeline.h"
#include "commonconfig.h"
#include "sw_util.h"
#include "vpufeature.h"
#include "ppu.h"
#include "delogo.h"
#include <string.h>
#include <assert.h>
#include "dec_log.h"
#include "low_latency.h"
#include "commonfunction.h"
#ifdef JPEGDEC_ASIC_TRACE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jpegasicdbgtrace.h"
#endif /* #ifdef JPEGDEC_ASIC_TRACE */

#ifdef JPEGDEC_PP_TRACE
#include "ppapi.h"
#endif /* #ifdef JPEGDEC_PP_TRACE */

static void JpegDecPreparePp(JpegDecContainer * dec_cont);
static enum DecRet JpegDecSetInfo_INTERNAL(JpegDecContainer * dec_cont);
static u32 InitList(FrameBufferList *fb_list);
static void ReleaseList(FrameBufferList *fb_list);
static void ClearHWOutput(FrameBufferList *fb_list, u32 id, u32 type);
static void MarkHWOutput(FrameBufferList *fb_list, u32 id, u32 type);
static void PushOutputPic(FrameBufferList *fb_list, const JpegDecOutput *pic, const JpegDecImageInfo *info);
static u32 JpegCycleCount(JpegDecContainer * dec_cont);
static u32 PeekOutputPic(FrameBufferList *fb_list, JpegDecOutput *pic, JpegDecImageInfo *info);
static void JpegMCSetHwRdyCallback(JpegDecInst dec_inst);
static void JpegRiMCSetHwRdyCallback(JpegDecInst dec_inst);

#ifdef CASE_INFO_STAT
extern CaseInfo case_info;
static void JpegCaseInfoCollect(JpegDecContainer *dec_cont, CaseInfo *case_info);
#endif

#ifdef ASIC_TRACE_SUPPORT
extern u32 stream_buffer_id;
#endif

/*------------------------------------------------------------------------------
    2. External compiler flags
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    3. Module defines
------------------------------------------------------------------------------*/

#define JPEGDEC_CLEAR_IRQ  SetDecRegister(dec_cont->jpeg_regs, \
                                          HWIF_DEC_IRQ_STAT, 0); \
                           SetDecRegister(dec_cont->jpeg_regs, \
                                          HWIF_DEC_IRQ, 0);
#define ABORT_MARKER                 3

/*------------------------------------------------------------------------------
    4. Local function prototypes
------------------------------------------------------------------------------*/
static u32 JpegParseRST(JpegDecInst dec_inst, u8 *img_buf, u32 img_len,
                             u8 **ri_array);

/*------------------------------------------------------------------------------
    5. Functions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------

    Function name: JpegDecInit

        Functional description:
            Init jpeg decoder

        Inputs:
            JpegDecInst * dec_inst     a reference to the jpeg decoder instance is
                                         stored here

        Outputs:
            DEC_OK
            DEC_INITFAIL
            DEC_PARAM_ERROR
            DEC_DWL_ERROR
            DEC_MEMFAIL

------------------------------------------------------------------------------*/
enum DecRet JpegDecInit(JpegDecInst * dec_inst, const void *dwl, struct JpegDecConfig *dec_cfg) {
  JpegDecContainer *dec_cont;
  u32 i = 0, hw_build_id;
  enum DecRet ret;
  u32 client_type;

  const struct DecHwFeatures *hw_feature = NULL;
  u32 low_latency_sim = 0;

  APITRACE("%s","JpegDecInit#\n");

  /* check that right shift on negative numbers is performed signed */
  /*lint -save -e* following check causes multiple lint messages */
  if(((-1) >> 1) != (-1)) {
    APITRACEERR("%s","JpegDecInit# ERROR: Right shift is not signed\n");
    return (DEC_INITFAIL);
  }

  /*lint -restore */
  if(dec_inst == NULL || dwl == NULL) {
    APITRACEERR("%s","JpegDecInit# ERROR: dec_inst == NULL\n");
    return (DEC_PARAM_ERROR);
  }
  *dec_inst = NULL;   /* return NULL instance for any error */

  /* check for proper hardware */
  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  if(!hw_feature->jpeg_support) {
    APITRACEERR("%s","JpegDecInit# ERROR: JPEG not supported in HW\n");
    return DEC_FORMAT_NOT_SUPPORTED;
  }

  dec_cont = (JpegDecContainer *) DWLmalloc(sizeof(JpegDecContainer));
  if(dec_cont == NULL) {
    return (DEC_MEMFAIL);
  }

  (void)DWLmemset(dec_cont, 0, sizeof(JpegDecContainer));

  dec_cont->dwl = dwl;

  /* reset internal structures */
  JpegDecClearStructs(dec_cont, 0);

  /* Reset shadow registers */
  (void)DWLmemset(dec_cont->jpeg_regs, 0, TOTAL_X170_REGISTERS*sizeof(u32));
  dec_cont->jpeg_regs[0] = DWLReadAsicID(DWL_CLIENT_TYPE_JPEG_DEC);

  dec_cont->pp_buffer_queue = InputQueueInit(0);
  if (dec_cont->pp_buffer_queue == NULL) {
    ret = (DEC_MEMFAIL);
    goto err;
  }

  /* G1V8 (major/minor version: 8/01):
     JPEG always outputs through PP instead of decoder. */

  dec_cont->pp_enabled = 1;

  dec_cont->align = dec_cfg->align;

  dec_cont->use_adaptive_buffers = dec_cfg->use_adaptive_buffers;
  dec_cont->secure_mode = (dec_cfg->decoder_mode & DEC_SECURITY) ? 1 : 0;

  SetCommonConfigRegs(dec_cont->jpeg_regs);

  /* set HW related config's */
  dec_cont->max_supported_width = hw_feature->img_max_dec_width;
  dec_cont->max_supported_height = hw_feature->img_max_dec_height;
  dec_cont->max_supported_pixel_amount = hw_feature->img_max_dec_width *
                                           hw_feature->img_max_dec_height;
  /* max */
  if(hw_feature->webp_support) { /* webp implicates 256Mpix support */
    dec_cont->max_supported_slice_size = JPEGDEC_MAX_SLICE_SIZE_WEBP;
  } else {
    dec_cont->max_supported_slice_size = JPEGDEC_MAX_SLICE_SIZE_8190;
  }

  /* min */
  dec_cont->min_supported_width = JPEGDEC_MIN_WIDTH;
  dec_cont->min_supported_height = JPEGDEC_MIN_HEIGHT;

  if (dec_cfg->decoder_mode & DEC_LOW_LATENCY) {
#ifdef MODEL_SIMULATION
    low_latency_sim = 1;
#else
    dec_cont->low_latency = 1;
#endif
    /* Set flag for using ddr latency and set pollmode and polltime swregs */
    SetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_STATUS_EXT_BUFFER_E, 1);
    SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_MC_POLLMODE, 0);
    SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_MC_POLLTIME, 0);
    dec_cont->strm_status_in_buffer = 1;
  }

  if(dec_cont->low_latency || low_latency_sim) {
    SetDecRegister(dec_cont->jpeg_regs, HWIF_BUFFER_EMPTY_INT_E, 0);
    SetDecRegister(dec_cont->jpeg_regs, HWIF_BLOCK_BUFFER_MODE_E, 1);
  } else {
    SetDecRegister(dec_cont->jpeg_regs, HWIF_BUFFER_EMPTY_INT_E, 1);
    SetDecRegister(dec_cont->jpeg_regs, HWIF_BLOCK_BUFFER_MODE_E, 0);
  }

  dec_cont->n_cores = 1;
  dec_cont->stream_consumed_callback.fn = dec_cfg->mcinit_cfg.stream_consumed_callback;
  dec_cont->b_mc = dec_cfg->mcinit_cfg.mc_enable;
  dec_cont->ri_mc_enabled = RI_MC_UNDETERMINED;
#ifdef RI_MC_SW_PARSE
  dec_cont->allow_sw_ri_parse = 1;
#endif

  dec_cont->n_cores = DWLReadAsicCoreCount();

  /* check how many cores support JPEG */
  u32 tmp = dec_cont->n_cores;
  dec_cont->core_mask = 0;
  for(i = 0; i < dec_cont->n_cores; i++) {
    hw_build_id = DWLReadCoreHwBuildID(i);
    GetReleaseHwFeaturesByID(hw_build_id, &hw_feature);
    if (!hw_feature->jpeg_support)
      tmp--;
    else
      dec_cont->core_mask |= 1 << i;
  }
  client_type = DWL_CLIENT_TYPE_JPEG_DEC << 16;
  dec_cont->core_mask |= client_type;
  dec_cont->core_mask |= (dec_cont->secure_mode << 31);
  dec_cont->n_cores_available = tmp;

  if (dec_cont->b_mc) {
    if(dec_cont->n_cores > 1) {
      SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_MULTICORE_E, 0);
    }
  }
  /* Init frame buffer list */
  InitList(&dec_cont->fb_list);

  *dec_inst = (JpegDecContainer *) dec_cont;

  dec_cont->hw_feature = (struct DecHwFeatures *)hw_feature;
  dec_cont->vcmd_used = DWLVcmdIsUsed();

  APITRACE("%s","JpegDecInit# OK\n");
  return (DEC_OK);

err:
  DWLfree(dec_cont);
  return ret;
}

/*------------------------------------------------------------------------------

    Function name: JpegDecRelease

        Functional description:
            Release Jpeg decoder

        Inputs:
            JpegDecInst dec_inst    jpeg decoder instance

            void

------------------------------------------------------------------------------*/
void JpegDecRelease(JpegDecInst dec_inst) {

  JpegDecContainer *dec_cont = (JpegDecContainer *)dec_inst;
  const void *dwl;
  u32 i=0;

  APITRACE("%s","JpegDecRelease#\n");

  if(dec_cont == NULL) {
    APITRACEERR("%s","JpegDecRelease# ERROR: dec_inst == NULL\n");
    return;
  }

  dwl = dec_cont->dwl;

  if(dec_cont->asic_running) {
    if (!dec_cont->vcmd_used) {
      /* Release HW */
      DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, 0);
      DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
    }
    else {
      DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
    }
  }

  if(dec_cont->vlc.ac_table0.vals) {
    DWLfree(dec_cont->vlc.ac_table0.vals);
  }
  if(dec_cont->vlc.ac_table1.vals) {
    DWLfree(dec_cont->vlc.ac_table1.vals);
  }
  if(dec_cont->vlc.ac_table2.vals) {
    DWLfree(dec_cont->vlc.ac_table2.vals);
  }
  if(dec_cont->vlc.ac_table3.vals) {
    DWLfree(dec_cont->vlc.ac_table3.vals);
  }
  if(dec_cont->vlc.dc_table0.vals) {
    DWLfree(dec_cont->vlc.dc_table0.vals);
  }
  if(dec_cont->vlc.dc_table1.vals) {
    DWLfree(dec_cont->vlc.dc_table1.vals);
  }
  if(dec_cont->vlc.dc_table2.vals) {
    DWLfree(dec_cont->vlc.dc_table2.vals);
  }
  if(dec_cont->vlc.dc_table3.vals) {
    DWLfree(dec_cont->vlc.dc_table3.vals);
  }
  if(dec_cont->frame.p_buffer) {
    DWLfree(dec_cont->frame.p_buffer);
  }
  if (dec_cont->frame.ri_array) {
    DWLfree(dec_cont->frame.ri_array);
  }
  /* progressive */
  if(dec_cont->info.p_coeff_base.virtual_address) {
    DWLFreeLinear(dwl, &(dec_cont->info.p_coeff_base));
    dec_cont->info.p_coeff_base.virtual_address = NULL;
  }
  if(dec_cont->frame.p_table_base[0].virtual_address) {
    for (i =0 ; i < dec_cont->n_cores; i++) {
      DWLFreeLinear(dwl, &(dec_cont->frame.p_table_base[i]));
      dec_cont->frame.p_table_base[i].virtual_address = NULL;
    }
  }

  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cont->ppu_cfg[i].lanczos_table.virtual_address) {
      DWLFreeLinear(dec_cont->dwl, &dec_cont->ppu_cfg[i].lanczos_table);
      dec_cont->ppu_cfg[i].lanczos_table.virtual_address = NULL;
    }
  }
  if (dec_cont->strm_status.virtual_address){
    DWLFreeLinear(dec_cont->dwl, &dec_cont->strm_status);
  }
  if (dec_cont->pp_buffer_queue) InputQueueRelease(dec_cont->pp_buffer_queue);

  ReleaseList(&dec_cont->fb_list);
  if(dec_inst) {
    DWLfree(dec_cont);
  }

  APITRACE("%s","JpegDecRelease# OK\n");

  return;

}

/*------------------------------------------------------------------------------

    Function name: JpegDecGetImageInfo

        Functional description:
            Get image information of the JFIF

        Inputs:
            JpegDecInst dec_inst     jpeg decoder instance
            JpegDecInput *p_dec_in    input stream information
            JpegDecImageInfo *p_image_info
                    structure where the image info is written

        Outputs:
            DEC_OK
            DEC_ERROR
            DEC_UNSUPPORTED
            DEC_PARAM_ERROR
            DEC_INCREASE_INPUT_BUFFER
            DEC_INVALID_STREAM_LENGTH
            DEC_INVALID_INPUT_BUFFER_SIZE

------------------------------------------------------------------------------*/
/* Get image information of the JFIF */
enum DecRet JpegDecGetImageInfo(JpegDecInst dec_inst, JpegDecInput * p_dec_in,
                               JpegDecImageInfo * p_image_info) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)dec_inst;
  u32 Nf = 0;
  u32 Ns = 0;
  u32 NsThumb = 0;
  u32 i, j = 0;
  u32 init = 0;
  u32 init_thumb = 0;
  u32 H[MAX_NUMBER_OF_COMPONENTS];
  u32 V[MAX_NUMBER_OF_COMPONENTS];
  u32 Htn[MAX_NUMBER_OF_COMPONENTS];
  u32 Vtn[MAX_NUMBER_OF_COMPONENTS];
  u32 Hmax = 0;
  u32 Vmax = 0;
  u32 header_length = 0;
  u32 current_byte = 0;
  u32 current_bytes = 0;
  u32 app_length = 0;
  u32 app_bits = 0;
  u32 thumbnail = 0;
  u32 error_code = 0;
  u32 new_header_value = 0;
  u32 marker_byte = 0;
  u32 output_width = 0;
  u32 output_height = 0;
  u32 output_width_thumb = 0;
  u32 output_height_thumb = 0;
  u32 component_id = 0;
  u32 width = 0;
  u32 height = 0;
  u32 tmp1 = 0;
  u32 tmp2 = 0;
  u32 size = 0;
  const struct DecHwFeatures *hw_feature = NULL;
  StreamStorage tmp_stream;

  APITRACE("%s","JpegDecGetImageInfo#\n");

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  /* check pointers & parameters */
  if(dec_inst == NULL || p_dec_in == NULL || p_image_info == NULL ||
      X170_CHECK_VIRTUAL_ADDRESS(p_dec_in->stream_buffer.virtual_address) ||
      X170_CHECK_BUS_ADDRESS(p_dec_in->stream_buffer.bus_address)) {
    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: NULL parameter\n");
    return (DEC_PARAM_ERROR);
  }

  /* Check the stream lenth */
  if(p_dec_in->stream_length < 1) {
    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: p_dec_in->stream_length\n");
    return (DEC_INVALID_STREAM_LENGTH);
  }

  /* Check the stream lenth */
  if((p_dec_in->stream_length > DEC_X170_MAX_STREAM_VCD) &&
      (p_dec_in->buffer_size < JPEGDEC_X170_MIN_BUFFER ||
       p_dec_in->buffer_size > JPEGDEC_X170_MAX_BUFFER)) {
    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: p_dec_in->buffer_size\n");
    return (DEC_INVALID_INPUT_BUFFER_SIZE);
  }

  /* Check the stream buffer size */
  if(p_dec_in->buffer_size && (p_dec_in->buffer_size < JPEGDEC_X170_MIN_BUFFER ||
                               p_dec_in->buffer_size > JPEGDEC_X170_MAX_BUFFER)) {
    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: p_dec_in->buffer_size\n");
    return (DEC_INVALID_INPUT_BUFFER_SIZE);
  }

  /* Check the stream buffer size */
  if(p_dec_in->buffer_size && ((p_dec_in->buffer_size % 8) != 0)) {
    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: (p_dec_in->buffer_size %% 8) != 0\n");
    return (DEC_INVALID_INPUT_BUFFER_SIZE);
  }

  /* reset sampling factors */
  for(i = 0; i < MAX_NUMBER_OF_COMPONENTS; i++) {
    H[i] = 0;
    V[i] = 0;
    Htn[i] = 0;
    Vtn[i] = 0;
  }

  /* imageInfo initialization */
  p_image_info->display_width = 0;
  p_image_info->display_height = 0;
  p_image_info->output_width = 0;
  p_image_info->output_height = 0;
  p_image_info->version = 0;
  p_image_info->units = 0;
  p_image_info->x_density = 0;
  p_image_info->y_density = 0;
  p_image_info->output_format = 0;

  /* Default value to "Thumbnail" */
  p_image_info->thumbnail_type = JPEGDEC_NO_THUMBNAIL;
  p_image_info->display_width_thumb = 0;
  p_image_info->display_height_thumb = 0;
  p_image_info->output_width_thumb = 0;
  p_image_info->output_height_thumb = 0;
  p_image_info->output_format_thumb = 0;

  /* Store the stream parameters */
  DWLmemset(&dec_cont->hw_stream, 0, sizeof(StreamStorage));
  dec_cont->stream.bit_pos_in_byte = 0;
  dec_cont->stream.p_start_of_stream =
    dec_cont->stream.p_curr_pos = (u8 *) p_dec_in->stream;
  dec_cont->stream.stream_bus = p_dec_in->stream_buffer.bus_address;
  dec_cont->stream.p_start_of_buffer =
    (u8 *) p_dec_in->stream_buffer.virtual_address;
  dec_cont->stream.strm_buff_size = p_dec_in->stream_buffer.logical_size;
  dec_cont->stream.read_bits = 0;
  dec_cont->stream.stream_length = p_dec_in->stream_length;
  dec_cont->stream.appn_flag = 0;

  /* stream length */
  if(!p_dec_in->buffer_size)
    dec_cont->stream.stream_length = p_dec_in->stream_length;
  else
    dec_cont->stream.stream_length = p_dec_in->buffer_size;

  /* Read decoding parameters */
  for(dec_cont->stream.read_bits = 0; (dec_cont->stream.read_bits / 8) < dec_cont->stream.stream_length;) {
    /* Look for marker prefix byte from stream */
    tmp_stream = dec_cont->stream;
    marker_byte = JpegDecGetByte(&(dec_cont->stream));
    if(marker_byte == 0xFF) {
      current_byte = JpegDecGetByte(&(dec_cont->stream));
      while (current_byte == 0xFF)
        current_byte = JpegDecGetByte(&(dec_cont->stream));

      /* switch to certain header decoding */
      switch (current_byte) {
      /* baseline marker */
      case SOF0:
      /* extended marker */
      case SOF1:
      /* progresive marker */
      case SOF2:
        if(current_byte == SOF0)
          p_image_info->coding_mode = dec_cont->info.operation_type =
                                        JPEG_BASELINE;
        else if (current_byte == SOF1) {
          p_image_info->coding_mode = dec_cont->info.operation_type =
                                        JPEG_EXTENDED;
        } else {
          if(!hw_feature->jpeg_support)
            return (DEC_FORMAT_NOT_SUPPORTED);
          p_image_info->coding_mode = dec_cont->info.operation_type =
                                        JPEG_PROGRESSIVE;
        }

        /* Frame header */
        i++;
        Hmax = 0;
        Vmax = 0;

        /* SOF0/SOF2 length */
        header_length = dec_cont->frame.Lf = JpegDecGet2Bytes(&(dec_cont->stream));

        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }

        /* Sample precision (only 8 bits/sample supported in baseline) */
        current_byte = JpegDecGetByte(&(dec_cont->stream));
        dec_cont->frame.P = current_byte;

        /* Number of Lines */
        p_image_info->output_height = JpegDecGet2Bytes(&(dec_cont->stream));
        p_image_info->display_height = p_image_info->output_height;

        if(p_image_info->output_height < 1) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_height Unsupported\n");
          return (DEC_UNSUPPORTED);
        }

        /* check if height changes (MJPEG) */
        if(dec_cont->frame.Y != 0 &&
            (dec_cont->frame.Y != p_image_info->output_height)) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_height changed (MJPEG)\n");
          new_header_value = 1;
        }

        /* Height only round up to next multiple-of-8 instead of 16 */
        p_image_info->output_height += 0x7;
        p_image_info->output_height &= ~(0x7);

        /* Number of Samples per Line */
        p_image_info->output_width = JpegDecGet2Bytes(&(dec_cont->stream));
        p_image_info->display_width = p_image_info->output_width;
        if(p_image_info->output_width < 1) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_width unsupported\n");
          return (DEC_UNSUPPORTED);
        }

        /* check if width changes (MJPEG) */
        if(dec_cont->frame.X != 0 &&
            (dec_cont->frame.X != p_image_info->output_width)) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_width changed (MJPEG)\n");
          new_header_value = 1;
        }

          p_image_info->output_width += 0x7;
          p_image_info->output_width &= ~(0x7);

#if 0
        /* check if height changes (MJPEG) */
        if(dec_cont->frame.hw_y != 0 &&
            (dec_cont->frame.hw_y != p_image_info->output_height)) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_height changed (MJPEG)");
          new_header_value = 1;
        }

        /* check if width changes (MJPEG) */
        if(dec_cont->frame.hw_x != 0 &&
            (dec_cont->frame.hw_x != p_image_info->output_width)) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_width changed (MJPEG)");
          new_header_value = 1;
        }
#endif

        /* check for minimum and maximum dimensions */
        if(p_image_info->output_width < dec_cont->min_supported_width ||
            p_image_info->output_height < dec_cont->min_supported_height ||
            p_image_info->output_width > dec_cont->max_supported_width ||
            p_image_info->output_height > dec_cont->max_supported_height ||
            (p_image_info->output_width * p_image_info->output_height) >
            dec_cont->max_supported_pixel_amount) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Unsupported size\n");
          return (DEC_UNSUPPORTED);
        }

        /* Number of Image Components per Frame */
        Nf = dec_cont->frame.Nf = JpegDecGetByte(&(dec_cont->stream));
        dec_cont->info.amount_of_qtables  = dec_cont->frame.Nf;
        if(Nf != 3 && Nf != 1) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Number of Image Components per Frame\n");
          return (DEC_UNSUPPORTED);
        }
        /* length 8 + 3 x Nf */
        if(header_length != (8 + (3 * Nf))) {
          APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Incorrect SOF0 header length");
          return (DEC_UNSUPPORTED);
        }
        for(j = 0; j < Nf; j++) {
          /* component identifier */
          component_id = dec_cont->frame.component[j].C = JpegDecGetByte(&(dec_cont->stream));
          if((dec_cont->info.operation_type == JPEG_PROGRESSIVE) && (component_id > 3)) {
            APITRACEERR
            ("%s","JpegDecGetImageInfo# ERROR: Illegal Image Component ID\n");
            return (DEC_UNSUPPORTED);
          }
          if(j == 0) { /* for the first component */
            /* if first component id is something else than 1 (jfif) */
            dec_cont->scan.index = dec_cont->frame.component[j].C;
          } else {
            /* if component ids 'jumps' */
            if((dec_cont->frame.component[j - 1].C + 1) !=
              dec_cont->frame.component[j].C) {
              JPEGDEC_TRACE_INTERNAL(("component ids 'jumps'\n"));
              return (DEC_UNSUPPORTED);
            }
          }

          /* Horizontal sampling factor */
          current_byte = JpegDecGetByte(&(dec_cont->stream));
          H[j] = dec_cont->frame.component[j].H = (current_byte >> 4);
          /* Vertical sampling factor */
          V[j] = dec_cont->frame.component[j].V = (current_byte & 0xF);

          /* jump over Tq */
          dec_cont->frame.component[j].Tq  = JpegDecGetByte(&(dec_cont->stream));

          if(H[j] > Hmax)
            Hmax = H[j];
          if(V[j] > Vmax)
            Vmax = V[j];
        }

        if(dec_cont->frame.Nf == 1) {
          Hmax = Vmax = 1;
          dec_cont->frame.component[0].H = 1;
          dec_cont->frame.component[0].V = 1;
        } else if(Hmax == 0 || Vmax == 0) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Hmax == 0 || Vmax == 0\n");
          return (DEC_UNSUPPORTED);
        }

        /* check format */
        if(H[0] == 2 && V[0] == 2 &&
            H[1] == 1 && V[1] == 1 && H[2] == 1 && V[2] == 1) {
          p_image_info->output_format = DEC_OUT_FRM_YUV420SP;
          dec_cont->frame.num_mcu_in_row = (p_image_info->output_width / 16);
          dec_cont->frame.num_mcu_in_frame = ((p_image_info->output_width *
                                               p_image_info->output_height) /
                                              256);
          dec_cont->frame.mcu_height = 16;
        } else if(H[0] == 2 && V[0] == 1 &&
                  H[1] == 1 && V[1] == 1 && H[2] == 1 && V[2] == 1) {
          p_image_info->output_format = DEC_OUT_FRM_YUV422SP;
          dec_cont->frame.num_mcu_in_row = (p_image_info->output_width / 16);
          dec_cont->frame.num_mcu_in_frame = ((p_image_info->output_width *
                                               p_image_info->output_height) /
                                              128);
          dec_cont->frame.mcu_height = 8;
        } else if(H[0] == 1 && V[0] == 2 &&
                  H[1] == 1 && V[1] == 1 && H[2] == 1 && V[2] == 1) {
          p_image_info->output_format = DEC_OUT_FRM_YUV440;
          dec_cont->frame.num_mcu_in_row = (p_image_info->output_width / 8);
          dec_cont->frame.num_mcu_in_frame = ((p_image_info->output_width *
                                               p_image_info->output_height) /
                                              128);
          dec_cont->frame.mcu_height = 16;
        } else if(H[0] == 1 && V[0] == 1 &&
                  H[1] == 0 && V[1] == 0 && H[2] == 0 && V[2] == 0) {
          p_image_info->output_format = DEC_OUT_FRM_YUV400;
          dec_cont->frame.num_mcu_in_row = (p_image_info->output_width / 8);
          dec_cont->frame.num_mcu_in_frame = ((p_image_info->output_width *
                                               p_image_info->output_height) /
                                              64);
          dec_cont->frame.mcu_height = 8;
        } else if(H[0] == 4 && V[0] == 1 &&
                  H[1] == 1 && V[1] == 1 && H[2] == 1 && V[2] == 1) {
          /* YUV411 output has to be 32 pixel multiple */
          if(p_image_info->output_width & 0x1F) {
            p_image_info->output_width += 16;
          }

          /* check for maximum dimensions */
          if(p_image_info->output_width > dec_cont->max_supported_width ||
              (p_image_info->output_width * p_image_info->output_height) >
              dec_cont->max_supported_pixel_amount) {
            APITRACEERR
            ("%s","JpegDecGetImageInfo# ERROR: Unsupported size\n");
            return (DEC_UNSUPPORTED);
          }

          p_image_info->output_format = DEC_OUT_FRM_YUV411SP;
          dec_cont->frame.num_mcu_in_row = (p_image_info->output_width / 32);
          dec_cont->frame.num_mcu_in_frame = ((p_image_info->output_width *
                                               p_image_info->output_height) /
                                              256);
          dec_cont->frame.mcu_height = 8;
        } else if(H[0] == 1 && V[0] == 1 &&
                  H[1] == 1 && V[1] == 1 && H[2] == 1 && V[2] == 1) {
          p_image_info->output_format = DEC_OUT_FRM_YUV444SP;
          dec_cont->frame.num_mcu_in_row = (p_image_info->output_width / 8);
          dec_cont->frame.num_mcu_in_frame = ((p_image_info->output_width *
                                               p_image_info->output_height) /
                                              64);
          dec_cont->frame.mcu_height = 8;
        } else {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Unsupported YCbCr format\n");
          return (DEC_UNSUPPORTED);
        }
        output_width = p_image_info->output_width;
        output_height = p_image_info->output_height;

        for(j = 0; j < Nf; j++) {
          /* set image pointers, calculate pixelPerRow for each component */
          width = ((dec_cont->frame.hw_x + Hmax * 8 - 1) / (Hmax * 8)) * Hmax * 8;
          height = ((dec_cont->frame.hw_y + Vmax * 8 - 1) / (Vmax * 8)) * Vmax * 8;
          tmp1 = (width * dec_cont->frame.component[j].H + Hmax - 1) / Hmax;
          tmp2 = (height * dec_cont->frame.component[j].V + Vmax - 1) / Vmax;
          size += tmp1 * tmp2;
          /* pixels per row */
          dec_cont->image.pixels_per_row[j] = tmp1;
          dec_cont->image.columns[j] = tmp2;

          if(j == 0) {
            dec_cont->image.size_luma = size;
          }

          dec_cont->frame.num_blocks[j] =
            (((NEXT_MULTIPLE(output_width, 8 * dec_cont->frame.component[j].H) *
            dec_cont->frame.component[j].H) / Hmax +
            7) >> 3) * (((NEXT_MULTIPLE(output_height, 8 * dec_cont->frame.component[j].V) *
                      dec_cont->frame.component[j].V) / Vmax + 7) >> 3);
        }

        dec_cont->image.size = size;
        dec_cont->image.size_chroma = size - dec_cont->image.size_luma;

        /* check if output format changes (MJPEG) */
        if(dec_cont->info.get_info_ycb_cr_mode != 0 &&
            (dec_cont->info.get_info_ycb_cr_mode != p_image_info->output_format)) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: YCbCr format changed (MJPEG)\n");
          new_header_value = 1;
        }
        if (JpegDecSetInfo_INTERNAL(dec_cont) != DEC_OK) {
          APITRACEERR
          ("%s","JpegDecDecode# JpegDecSetInfo_INTERNAL err\n");
          error_code = 1;
          break;
        }
        dec_cont->image.header_ready = 1;

        if (dec_cont->hw_stream.strm_buff_size == 0)
          dec_cont->hw_stream = tmp_stream;

        break;
      case SOS:
        /* SOS length */
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          if(!dec_cont->low_latency)
          {
            error_code = 1;
            break;
          }
        }

        /* check if interleaved or non-ibnterleaved */
        Ns = JpegDecGetByte(&(dec_cont->stream));
        if(Ns == MIN_NUMBER_OF_COMPONENTS &&
            p_image_info->output_format != DEC_OUT_FRM_YUV400 &&
            p_image_info->coding_mode == JPEG_BASELINE) {
          p_image_info->coding_mode = dec_cont->info.operation_type =
                                        JPEG_NONINTERLEAVED;
            APITRACEERR
           ("%s","JpegDecGetImageInfo# ERROR: Unsupported coding mode\n");
           return (DEC_UNSUPPORTED);
        }
        /* Number of Image Components */
        if(Ns != 3 && Ns != 1) {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Number of Image Components\n");
          return (DEC_UNSUPPORTED);
        }
        /* length 6 + 2 x Ns */
        if(header_length != (6 + (2 * Ns))) {
          APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Incorrect SOS header length\n");
          return (DEC_UNSUPPORTED);
        }
        /* jump over SOS header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
          if (dec_cont->stream.p_curr_pos >=
             (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
            dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
        }

        /* SOF should be parsed before SOS */
        if(((dec_cont->stream.read_bits + 8) < (8 * dec_cont->stream.stream_length) || dec_cont->low_latency) && Nf) {
          dec_cont->info.init = 1;
          init = 1;
        } else {
          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Needs to increase input buffer\n");
          return (DEC_INCREASE_INPUT_BUFFER);
        }
        break;
      case DQT:
        /* table is decoded by HW */
        if (dec_cont->image.header_ready == 0 && dec_cont->hw_stream.strm_buff_size == 0) {
          dec_cont->hw_stream = tmp_stream;
        }

        /* DQT length */
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length >= (2 + 65) (baseline) */
        if(header_length < (2 + 65)) {
          APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Incorrect DQT header length\n");
          return (DEC_UNSUPPORTED);
        }
        /* jump over DQT header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
          if (dec_cont->stream.p_curr_pos >=
             (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
            dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
        }

        break;
      case DHT:
        /* DHT length */
        if (dec_cont->image.header_ready == 0 && dec_cont->hw_stream.strm_buff_size == 0) {
          dec_cont->hw_stream = tmp_stream;
        }
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length >= 2 + 17 */
        if(header_length < 19) {
          APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Incorrect DHT header length\n");
          return (DEC_UNSUPPORTED);
        }
        /* jump over DHT header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
          if (dec_cont->stream.p_curr_pos >=
             (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
            dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
        }

        break;
      case DRI:
        /* DRI is decoded by HW */
        if (dec_cont->image.header_ready == 0 && dec_cont->hw_stream.strm_buff_size == 0) {
          dec_cont->hw_stream = tmp_stream;
        }
        /* DRI length */
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length == 4 */
        if(header_length != 4) {
          APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Incorrect DRI header length\n");
          return (DEC_UNSUPPORTED);
        }
        /* jump over DRI header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
        }
        dec_cont->frame.Ri = header_length;
        break;
      /* Restart with modulo 8 count m */
      case RST0:
      case RST1:
      case RST2:
      case RST3:
      case RST4:
      case RST5:
      case RST6:
      case RST7:
        /* initialisation of DC predictors to zero value !!! */
        for(i = 0; i < MAX_NUMBER_OF_COMPONENTS; i++) {
          dec_cont->scan.pred[i] = 0;
        }
        APITRACEDEBUG("%s","JpegDecDecode# DC predictors init\n");
        break;
      /* application segments */
      case APP0:
        APITRACE("%s","JpegDecGetImageInfo# APP0 in GetImageInfo\n");
        /* reset */
        app_bits = 0;
        app_length = 0;
        dec_cont->stream.appn_flag = 0;
        if (p_dec_in->thumbnail_done == 1) {
           /* Flush unsupported thumbnail */
          current_bytes = JpegDecGet2Bytes(&(dec_cont->stream));

          /* length > 2 */
          if(current_bytes < 2)
            break;

          dec_cont->stream.appn_flag = 1;
          if(JpegDecFlushBits
              (&(dec_cont->stream),
               ((current_bytes - 2) * 8)) == STRM_ERROR) {
            APITRACEERR("%s","JpegDecDecode# ERROR: Stream error\n");
            error_code = 1;
          }
          dec_cont->stream.appn_flag = 0;
          break;
        }
        /* APP0 length */
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length > 2 */
        if(header_length < 2)
          break;
        app_length = header_length;
        if(app_length < 16) {
          dec_cont->stream.appn_flag = 1;
          if(JpegDecFlushBits(&(dec_cont->stream), ((app_length * 8) - 16)) ==
              STRM_ERROR) {
            error_code = 1;
            break;
          }
          break;
        }
        app_bits += 16;

        /* check identifier */
        current_bytes = JpegDecGet2Bytes(&(dec_cont->stream));
        app_bits += 16;
        if(current_bytes != 0x4A46) {
          dec_cont->stream.appn_flag = 1;
          if(JpegDecFlushBits(&(dec_cont->stream), ((app_length * 8) - app_bits))
              == STRM_ERROR) {
            error_code = 1;
            break;
          }
          break;
        }
        current_bytes = JpegDecGet2Bytes(&(dec_cont->stream));
        app_bits += 16;
        if(current_bytes != 0x4946 && current_bytes != 0x5858) {
          dec_cont->stream.appn_flag = 1;
          if(JpegDecFlushBits(&(dec_cont->stream), ((app_length * 8) - app_bits))
              == STRM_ERROR) {
            error_code = 1;
            break;
          }
          break;
        }

        /* APP0 Extended */
        if(current_bytes == 0x5858) {
          thumbnail = 1;
        }
        current_byte = JpegDecGetByte(&(dec_cont->stream));
        app_bits += 8;
        if(current_byte != 0x00) {
          dec_cont->stream.appn_flag = 1;
          if(JpegDecFlushBits(&(dec_cont->stream), ((app_length * 8) - app_bits))
              == STRM_ERROR) {
            error_code = 1;
            break;
          }
          dec_cont->stream.appn_flag = 0;
          break;
        }

        /* APP0 Extended thumb type */
        if(thumbnail) {
          /* extension code */
          current_byte = JpegDecGetByte(&(dec_cont->stream));
          if(current_byte == JPEGDEC_THUMBNAIL_JPEG) {
            p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_JPEG;
            app_bits += 8;
            dec_cont->stream.appn_flag = 1;
            dec_cont->stream.thumbnail = 1;
            /* check thumbnail data */
            Hmax = 0;
            Vmax = 0;

            /* Read decoding parameters */
            for(; (dec_cont->stream.read_bits / 8) < dec_cont->stream.stream_length;) {
              /* Look for marker prefix byte from stream */
              app_bits += 8;
              tmp_stream = dec_cont->stream;
              marker_byte = JpegDecGetByte(&(dec_cont->stream));
              /* check if APP0 decoded */
              if( ((app_bits + 8) / 8) >= app_length)
                break;
              if(marker_byte == 0xFF) {
                /* switch to certain header decoding */
                app_bits += 8;

                current_byte = JpegDecGetByte(&(dec_cont->stream));
                while (current_byte == 0xFF)
                {
                  app_bits += 8;
                  current_byte = JpegDecGetByte(&(dec_cont->stream));
                }

                switch (current_byte) {
                /* baseline marker */
                case SOF0:
                /* externed marker */
                case SOF1:
                /* progresive marker */
                case SOF2:
                  if(current_byte == SOF0)
                    p_image_info->coding_mode_thumb =
                      dec_cont->info.operation_type_thumb =
                        JPEG_BASELINE;
                  else if (current_byte == SOF1) {
                    p_image_info->coding_mode_thumb =
                      dec_cont->info.operation_type_thumb =
                        JPEG_EXTENDED;
                  }
                  else {
                    if(!hw_feature->jpeg_support)
                      return (DEC_FORMAT_NOT_SUPPORTED);
                    p_image_info->coding_mode_thumb =
                      dec_cont->info.operation_type_thumb =
                        JPEG_PROGRESSIVE;
                  }
                  /* Frame header */
                  i++;

                  /* jump over Lf field */
                  header_length = dec_cont->frame.Lf = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR ||
                      ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
                       (8 * dec_cont->stream.stream_length))) {
                    error_code = 1;
                    break;
                  }
                  app_bits += 16;

                  /* Sample precision (only 8 bits/sample supported) */
                  current_byte = JpegDecGetByte(&(dec_cont->stream));
                  app_bits += 8;

                  /* Number of Lines */
                  p_image_info->output_height_thumb =
                    JpegDecGet2Bytes(&(dec_cont->stream));
                  app_bits += 16;
                  p_image_info->display_height_thumb =
                    p_image_info->output_height_thumb;
                  if(p_image_info->output_height_thumb < 1) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_height_thumb unsupported\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }

                  /* round up to next multiple-of-7 */
                  p_image_info->output_height_thumb += 0x7;
                  p_image_info->output_height_thumb &= ~(0x7);

                  /* Number of Samples per Line */
                  p_image_info->output_width_thumb =
                    JpegDecGet2Bytes(&(dec_cont->stream));
                  app_bits += 16;
                  p_image_info->display_width_thumb =
                    p_image_info->output_width_thumb;
                  if(p_image_info->output_width_thumb < 1) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_width_thumb unsupported\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }

                  p_image_info->output_width_thumb += 0x7;
                  p_image_info->output_width_thumb &= ~(0x7);

                  /* check if height changes (MJPEG) */
                  if(dec_cont->frame.hw_ytn != 0 &&
                      (dec_cont->frame.hw_ytn != p_image_info->output_height_thumb)) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_height_thumb changed (MJPEG)\n");
                    new_header_value = 1;
                  }

                  /* check if width changes (MJPEG) */
                  if(dec_cont->frame.hw_xtn != 0 &&
                      (dec_cont->frame.hw_xtn != p_image_info->output_width_thumb)) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: p_image_info->output_width_thumb changed (MJPEG)\n");
                    new_header_value = 1;
                  }

                  if(p_image_info->output_width_thumb <
                      dec_cont->min_supported_width ||
                      p_image_info->output_height_thumb <
                      dec_cont->min_supported_height ||
                      p_image_info->output_width_thumb >
                      JPEGDEC_MAX_WIDTH_TN ||
                      p_image_info->output_height_thumb >
                      JPEGDEC_MAX_HEIGHT_TN) {

                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Thumbnail Unsupported size\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }

                  /* Number of Image Components per Frame */
                  Nf = dec_cont->frame.Nf = JpegDecGetByte(&(dec_cont->stream));
                  dec_cont->info.amount_of_qtables  = dec_cont->frame.Nf;
                  app_bits += 8;
                  if(Nf != 3 && Nf != 1) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Thumbnail Number of Image Components per Frame\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }
                  /* length 8 + 3 x Nf */
                  if(header_length != (8 + (3 * Nf))) {
                    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Thumbnail Incorrect SOF0 header length\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }
                  for(j = 0; j < Nf; j++) {

                     /* component identifier */
                    component_id = dec_cont->frame.component[j].C = JpegDecGetByte(&(dec_cont->stream));
                    app_bits += 8;
                    if(j == 0) { /* for the first component */
                      /* if first component id is something else than 1 (jfif) */
                      dec_cont->scan.index = dec_cont->frame.component[j].C;
                    } else {
                      /* if component ids 'jumps' */
                      if((dec_cont->frame.component[j - 1].C + 1) !=
                        dec_cont->frame.component[j].C) {
                        JPEGDEC_TRACE_INTERNAL(("component ids 'jumps'\n"));
                        return (DEC_UNSUPPORTED);
                      }
                    }

                    /* Horizontal sampling factor */
                    current_byte = JpegDecGetByte(&(dec_cont->stream));
                    app_bits += 8;

                    Htn[j] = dec_cont->frame.component[j].H = (current_byte >> 4);
                    /* Vertical sampling factor */
                    Vtn[j] = dec_cont->frame.component[j].V = (current_byte & 0xF);

                    /* jump over Tq */
                    dec_cont->frame.component[j].Tq  = JpegDecGetByte(&(dec_cont->stream));
                    app_bits += 8;

                    if(Htn[j] > Hmax)
                      Hmax = Htn[j];
                    if(Vtn[j] > Vmax)
                      Vmax = Vtn[j];
                  }

                  if(dec_cont->frame.Nf == 1) {
                    Hmax = Vmax = 1;
                    dec_cont->frame.component[0].H = 1;
                    dec_cont->frame.component[0].V = 1;
                  } else if(Hmax == 0 || Vmax == 0) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Thumbnail Hmax == 0 || Vmax == 0\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }

                  /* check format */
                  if(Htn[0] == 2 && Vtn[0] == 2 &&
                      Htn[1] == 1 && Vtn[1] == 1 &&
                      Htn[2] == 1 && Vtn[2] == 1) {
                    p_image_info->output_format_thumb =
                      DEC_OUT_FRM_YUV420SP;
                  } else if(Htn[0] == 2 && Vtn[0] == 1 &&
                            Htn[1] == 1 && Vtn[1] == 1 &&
                            Htn[2] == 1 && Vtn[2] == 1) {
                    p_image_info->output_format_thumb =
                      DEC_OUT_FRM_YUV422SP;
                  } else if(Htn[0] == 1 && Vtn[0] == 2 &&
                            Htn[1] == 1 && Vtn[1] == 1 &&
                            Htn[2] == 1 && Vtn[2] == 1) {
                    p_image_info->output_format_thumb =
                      DEC_OUT_FRM_YUV440;
                  } else if(Htn[0] == 1 && Vtn[0] == 1 &&
                            Htn[1] == 0 && Vtn[1] == 0 &&
                            Htn[2] == 0 && Vtn[2] == 0) {
                    p_image_info->output_format_thumb =
                      DEC_OUT_FRM_YUV400;
                  } else if(Htn[0] == 4 && Vtn[0] == 1 &&
                            Htn[1] == 1 && Vtn[1] == 1 &&
                            Htn[2] == 1 && Vtn[2] == 1) {
                    p_image_info->output_format_thumb =
                      DEC_OUT_FRM_YUV411SP;
                  } else if(Htn[0] == 1 && Vtn[0] == 1 &&
                            Htn[1] == 1 && Vtn[1] == 1 &&
                            Htn[2] == 1 && Vtn[2] == 1) {
                    p_image_info->output_format_thumb =
                      DEC_OUT_FRM_YUV444SP;
                  } else {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Thumbnail Unsupported YCbCr format\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }
                  output_width_thumb = p_image_info->output_width_thumb;
                  output_height_thumb = p_image_info->output_height_thumb;
#if 0
                  if(dec_cont->pp_enabled && !(dec_cont->info.user_alloc_mem) &&
                     (dec_cont->hw_major_ver == 7 && dec_cont->hw_minor_ver >= 1)) {
                    p_image_info->output_width_thumb = p_image_info->output_width_thumb >> dec_cont->dscale_shift_x;
                    p_image_info->output_height_thumb = p_image_info->output_height_thumb >> dec_cont->dscale_shift_y;
                    p_image_info->display_width_thumb = p_image_info->display_width_thumb >> dec_cont->dscale_shift_x;
                    p_image_info->display_height_thumb = p_image_info->display_height_thumb >> dec_cont->dscale_shift_y;
                  }
#endif
                  for(j = 0; j < Nf; j++) {
                    /* set image pointers, calculate pixelPerRow for each component */
                    width = ((dec_cont->frame.hw_x + Hmax * 8 - 1) / (Hmax * 8)) * Hmax * 8;
                    height = ((dec_cont->frame.hw_y + Vmax * 8 - 1) / (Vmax * 8)) * Vmax * 8;
                    tmp1 = (width * dec_cont->frame.component[j].H + Hmax - 1) / Hmax;
                    tmp2 = (height * dec_cont->frame.component[j].V + Vmax - 1) / Vmax;
                    size += tmp1 * tmp2;
                    /* pixels per row */
                    dec_cont->image.pixels_per_row[j] = tmp1;
                    dec_cont->image.columns[j] = tmp2;

                    if(j == 0) {
                      dec_cont->image.size_luma = size;
                    }

                    dec_cont->frame.num_blocks[j] =
                      (((NEXT_MULTIPLE(output_width, 8 * dec_cont->frame.component[j].H) *
                      dec_cont->frame.component[j].H) / Hmax +
                      7) >> 3) * (((NEXT_MULTIPLE(output_height, 8 * dec_cont->frame.component[j].V) *
                                dec_cont->frame.component[j].V) / Vmax + 7) >> 3);
                  }

                  dec_cont->image.size = size;
                  dec_cont->image.size_chroma = size - dec_cont->image.size_luma;
                  /* check if output format changes (MJPEG) */
                  if(dec_cont->info.get_info_ycb_cr_mode_tn != 0 &&
                      (dec_cont->info.get_info_ycb_cr_mode_tn != p_image_info->output_format_thumb)) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Thumbnail YCbCr format changed (MJPEG)\n");
                    new_header_value = 1;
                  }
                  if (JpegDecSetInfo_INTERNAL(dec_cont) != DEC_OK) {
                    APITRACEERR
                    ("%s","JpegDecDecode# JpegDecSetInfo_INTERNAL err\n");
                    error_code = 1;
                    break;
                  }
                  dec_cont->image.header_ready = 1;
                  if (dec_cont->hw_stream.strm_buff_size == 0)
                    dec_cont->hw_stream = tmp_stream;
                  break;
                case SOS:
                  /* SOS length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR ||
                      ((dec_cont->stream.read_bits +
                        ((header_length * 8) - 16)) >
                       (8 * dec_cont->stream.stream_length))) {
                    error_code = 1;
                    break;
                  }

                  /* check if interleaved or non-ibnterleaved */
                  NsThumb = JpegDecGetByte(&(dec_cont->stream));
                  if(NsThumb == MIN_NUMBER_OF_COMPONENTS &&
                      p_image_info->output_format_thumb !=
                      DEC_OUT_FRM_YUV400 &&
                      p_image_info->coding_mode_thumb ==
                      JPEG_BASELINE) {
                    p_image_info->coding_mode_thumb =
                      dec_cont->info.operation_type_thumb =
                        JPEG_NONINTERLEAVED;
                  }
                  if(NsThumb != 3 && NsThumb != 1) {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Thumbnail Number of Image Components\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }
                  /* length 6 + 2 x NsThumb */
                  if(header_length != (6 + (2 * NsThumb))) {
                    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Thumbnail Incorrect SOS header length\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                  }
                  /* jump over SOS header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }

                  if((dec_cont->stream.read_bits + 8) <
                      (8 * dec_cont->stream.stream_length)) {
                    dec_cont->info.init_thumb = 1;
                    init_thumb = 1;
                  } else {
                    APITRACEERR
                    ("%s","JpegDecGetImageInfo# ERROR: Needs to increase input buffer\n");
                    return (DEC_INCREASE_INPUT_BUFFER);
                  }
                  break;
                case DQT:
                  if (dec_cont->image.header_ready == 0 && dec_cont->hw_stream.strm_buff_size == 0) {
                    dec_cont->hw_stream = tmp_stream;
                  }
                  /* DQT length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  /* length >= (2 + 65) (baseline) */
                  if(header_length < (2 + 65)) {
                    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Thumbnail Incorrect DQT header length\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                    break;
                  }
                  /* jump over DQT header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }
                  app_bits += (header_length * 8);
                  break;
                case DHT:
                  if (dec_cont->image.header_ready == 0 && dec_cont->hw_stream.strm_buff_size == 0) {
                    dec_cont->hw_stream = tmp_stream;
                  }
                  /* DHT length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  /* length >= 2 + 17 */
                  if(header_length < 19) {
                    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Thumbnail Incorrect DHT header length\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                    break;
                  }
                  /* jump over DHT header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }
                  app_bits += (header_length * 8);
                  break;
                case DRI:
                  if (dec_cont->image.header_ready == 0 && dec_cont->hw_stream.strm_buff_size == 0) {
                    dec_cont->hw_stream = tmp_stream;
                  }
                  /* DRI length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  /* length == 4 */
                  if(header_length != 4) {
                    APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Thumbnail Incorrect DRI header length\n");
                    p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
                    break;
                  }
                  /* jump over DRI header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }
                  app_bits += (header_length * 8);
                  break;
                case APP0:
                case APP1:
                case APP2:
                case APP3:
                case APP4:
                case APP5:
                case APP6:
                case APP7:
                case APP8:
                case APP9:
                case APP10:
                case APP11:
                case APP12:
                case APP13:
                case APP14:
                case APP15:
                  /* APPn length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  /* header_length > 2 */
                  if(header_length < 2)
                    break;
                  /* jump over APPn header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }
                  app_bits += (header_length * 8);
                  break;
                case DNL:
                  /* DNL length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  /* length == 4 */
                  if(header_length != 4)
                    break;
                  /* jump over DNL header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }
                  app_bits += (header_length * 8);
                  break;
                case COM:
                  /* COM length */
                  header_length = JpegDecGet2Bytes(&(dec_cont->stream));
                  if(header_length == STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  /* length > 2 */
                  if(header_length < 2)
                    break;
                  /* jump over COM header */
                  if(header_length != 0) {
                    dec_cont->stream.read_bits +=
                      ((header_length * 8) - 16);
                    dec_cont->stream.p_curr_pos +=
                      (((header_length * 8) - 16) / 8);
                    if (dec_cont->stream.p_curr_pos >=
                       (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
                      dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
                  }
                  app_bits += (header_length * 8);
                  break;
                /* unsupported coding styles */
                case SOF3:
                case SOF5:
                case SOF6:
                case SOF7:
                case SOF9:
                case SOF10:
                case SOF11:
                case SOF13:
                case SOF14:
                case SOF15:
                case DAC:
                case DHP:
                  APITRACEERR
                  ("%s","JpegDecGetImageInfo# ERROR: Unsupported coding styles\n");
                  return (DEC_UNSUPPORTED);
                default:
                  break;
                }
                if(dec_cont->info.init_thumb && init_thumb) {
                  /* flush the rest of thumbnail data */
                  if(JpegDecFlushBits
                      (&(dec_cont->stream),
                       ((app_length * 8) - app_bits)) ==
                      STRM_ERROR) {
                    error_code = 1;
                    break;
                  }
                  dec_cont->stream.appn_flag = 0;
                  break;
                }
              } else {
                if(!dec_cont->info.init_thumb &&
                    ((dec_cont->stream.read_bits + 8) >= (dec_cont->stream.stream_length * 8)) &&
                    p_dec_in->buffer_size)
                  return (DEC_INCREASE_INPUT_BUFFER);

                if(marker_byte == STRM_ERROR )
                  return (DEC_STRM_ERROR);
              }
            }
            if(!dec_cont->info.init_thumb && !init_thumb) {
              APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Thumbnail contains no data\n");
              p_image_info->thumbnail_type = JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
            }
            break;
          } else {
            app_bits += 8;
            p_image_info->thumbnail_type =
              JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT;
            dec_cont->stream.appn_flag = 1;
            if(JpegDecFlushBits
                (&(dec_cont->stream),
                 ((app_length * 8) - app_bits)) == STRM_ERROR) {
              error_code = 1;
              break;
            }
            dec_cont->stream.appn_flag = 0;
            break;
          }
        } else {
          /* version */
          p_image_info->version = JpegDecGet2Bytes(&(dec_cont->stream));
          app_bits += 16;

          /* units */
          current_byte = JpegDecGetByte(&(dec_cont->stream));
          if(current_byte == 0) {
            p_image_info->units = JPEGDEC_NO_UNITS;
          } else if(current_byte == 1) {
            p_image_info->units = JPEGDEC_DOTS_PER_INCH;
          } else if(current_byte == 2) {
            p_image_info->units = JPEGDEC_DOTS_PER_CM;
          }
          app_bits += 8;

          /* Xdensity */
          p_image_info->x_density = JpegDecGet2Bytes(&(dec_cont->stream));
          app_bits += 16;

          /* Ydensity */
          p_image_info->y_density = JpegDecGet2Bytes(&(dec_cont->stream));
          app_bits += 16;

          /* jump over rest of header data */
          dec_cont->stream.appn_flag = 1;
          if(JpegDecFlushBits(&(dec_cont->stream), ((app_length * 8) - app_bits))
              == STRM_ERROR) {
            error_code = 1;
            break;
          }
          dec_cont->stream.appn_flag = 0;
          break;
        }
      case APP1:
      case APP2:
      case APP3:
      case APP4:
      case APP5:
      case APP6:
      case APP7:
      case APP8:
      case APP9:
      case APP10:
      case APP11:
      case APP12:
      case APP13:
      case APP14:
      case APP15:
        /* APPn length */
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length > 2 */
        if(header_length < 2)
          break;
        /* jump over APPn header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
          if (dec_cont->stream.p_curr_pos >=
             (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
            dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
        }
        break;
      case DNL:
        /* DNL length */
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length == 4 */
        if(header_length != 4)
          break;
        /* jump over DNL header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
          if (dec_cont->stream.p_curr_pos >=
             (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
            dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
        }
        break;
      case COM:
        header_length = JpegDecGet2Bytes(&(dec_cont->stream));
        if(header_length == STRM_ERROR ||
            ((dec_cont->stream.read_bits + ((header_length * 8) - 16)) >
             (8 * dec_cont->stream.stream_length))) {
          error_code = 1;
          break;
        }
        /* length > 2 */
        if(header_length < 2)
          break;
        /* jump over COM header */
        if(header_length != 0) {
          dec_cont->stream.read_bits += ((header_length * 8) - 16);
          dec_cont->stream.p_curr_pos += (((header_length * 8) - 16) / 8);
          if (dec_cont->stream.p_curr_pos >=
             (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
            dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
        }
        break;
      /* unsupported coding styles */
      case SOF3:
      case SOF5:
      case SOF6:
      case SOF7:
      case SOF9:
      case SOF10:
      case SOF11:
      case SOF13:
      case SOF14:
      case SOF15:
      case DAC:
      case DHP:
        APITRACEERR
        ("%s","JpegDecGetImageInfo# ERROR: Unsupported coding styles\n");
        return (DEC_UNSUPPORTED);
      case EOI:
        break;
      default:
        break;
      }
      if(dec_cont->info.init && init) {
        dec_cont->frame.hw_y = dec_cont->frame.full_y = output_height;
        dec_cont->frame.hw_x = dec_cont->frame.full_x = output_width;
        /* restore output format */
        dec_cont->info.y_cb_cr_mode = dec_cont->info.get_info_ycb_cr_mode =
                                        p_image_info->output_format;
        if(thumbnail) {
          dec_cont->frame.hw_ytn = output_height_thumb;
          dec_cont->frame.hw_xtn = output_width_thumb;
          dec_cont->frame.hw_y = output_height_thumb;
          dec_cont->frame.hw_x = output_width_thumb;
          /* restore output format for thumb */
          dec_cont->info.get_info_ycb_cr_mode_tn = p_image_info->output_format_thumb;
          dec_cont->frame.component[0].H = Htn[0];
          dec_cont->frame.component[0].V = Vtn[0];
          dec_cont->frame.component[1].H = Htn[1];
          dec_cont->frame.component[1].V = Vtn[1];
          dec_cont->frame.component[2].H = Htn[2];
          dec_cont->frame.component[2].V = Vtn[2];
        }
        break;
      }

      if(error_code) {
        if(p_dec_in->buffer_size) {
          /* reset to ensure that big enough buffer will be allocated for decoding */
          if(new_header_value) {
            p_image_info->output_height = dec_cont->frame.hw_y;
            p_image_info->output_width = dec_cont->frame.hw_x;
            p_image_info->output_format = dec_cont->info.get_info_ycb_cr_mode;
            if(thumbnail) {
              p_image_info->output_height_thumb = dec_cont->frame.hw_ytn;
              p_image_info->output_width_thumb = dec_cont->frame.hw_xtn;
              p_image_info->output_format_thumb = dec_cont->info.get_info_ycb_cr_mode_tn;
            }
          }

          APITRACEERR
          ("%s","JpegDecGetImageInfo# ERROR: Image info failed, Needs to increase input buffer\n");
          return (DEC_INCREASE_INPUT_BUFFER);
        } else {
          APITRACEERR("%s","JpegDecGetImageInfo# ERROR: Stream error\n");
          return (DEC_STRM_ERROR);
        }
      }
    } else {
      if(!dec_cont->info.init && (dec_cont->stream.read_bits + 8 >= (dec_cont->stream.stream_length * 8)) )
        return (DEC_INCREASE_INPUT_BUFFER);

      if(marker_byte == STRM_ERROR )
        return (DEC_STRM_ERROR);
    }
  }
  dec_cont->hw_stream.appn_flag = dec_cont->stream.appn_flag;
  if(dec_cont->info.init) {
    p_image_info->bit_depth = dec_cont->frame.P == 8 ? 8 : 12;
    if(p_dec_in->buffer_size)
      dec_cont->info.init_buffer_size = p_dec_in->buffer_size;

    p_image_info->output_width = NEXT_MULTIPLE(p_image_info->output_width, ALIGN(dec_cont->align));
    p_image_info->output_width_thumb = NEXT_MULTIPLE(p_image_info->output_width_thumb, ALIGN(dec_cont->align));

    p_image_info->align = dec_cont->align;
    if (dec_cont->hw_feature) {
      p_image_info->img_max_dec_width = dec_cont->hw_feature->img_max_dec_width;
      p_image_info->img_max_dec_height = dec_cont->hw_feature->img_max_dec_height;
    }

    dec_cont->p_image_info = *p_image_info;
    APITRACE("%s","JpegDecGetImageInfo# OK\n");
    return (DEC_OK);
  } else {
    APITRACEERR("%s","JpegDecGetImageInfo# ERROR\n");
    return (DEC_ERROR);
  }
}

/*------------------------------------------------------------------------------

    Function name: JpegDecDecode

        Functional description:
            Decode JFIF

        Inputs:
            JpegDecInst dec_inst     jpeg decoder instance
            JpegDecInput *p_dec_in    pointer to structure where the decoder
                                    stores input information
            JpegDecOutput *p_dec_out  pointer to structure where the decoder
                                    stores output frame information

        Outputs:
            DEC_PIC_RDY
            DEC_PARAM_ERROR
            DEC_INVALID_STREAM_LENGTH
            DEC_INVALID_INPUT_BUFFER_SIZE
            DEC_UNSUPPORTED
            DEC_ERROR
            DEC_STRM_ERROR
            DEC_HW_BUS_ERROR
            DEC_HW_TIMEOUT
            DEC_SYSTEM_ERROR
            DEC_HW_RESERVED
            DEC_STRM_PROCESSED

  ------------------------------------------------------------------------------*/
enum DecRet JpegDecDecode(JpegDecInst dec_inst, JpegDecInput * p_dec_in,
                         JpegDecOutput * p_dec_out) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)dec_inst;
#define JPG_FRM  dec_cont->frame
#define JPG_INFO  dec_cont->info
  i32 dwlret = -1;
  u32 i = 0;
  u32 current_byte = 0;
  u32 asic_status = 0;
  u32 HINTdec = 0;
  u32 asic_slice_bit = 0;
  u32 int_dec = 0;
  enum DecRet info_ret;
  enum DecRet ret_code; /* Returned code container */
  JpegDecImageInfo info_tmp = {0};
  u32 mcu_size_divider = 0;
  addr_t current_pos = 0;
  u32 hw_consumed;
#ifdef SUPPORT_DEC400
  u32 *tile_status_virtual_address = NULL;
  addr_t tile_status_bus_address = 0;
#endif
  struct DWLLinearMem *pp_buffer = NULL;

  APITRACE("%s","JpegDecDecode#\n");

  /* check null */
  if(dec_inst == NULL || p_dec_in == NULL ||
      X170_CHECK_VIRTUAL_ADDRESS(p_dec_in->stream_buffer.virtual_address) ||
      X170_CHECK_BUS_ADDRESS(p_dec_in->stream_buffer.bus_address) ||
      p_dec_out == NULL) {
    APITRACEERR("%s","JpegDecDecode# ERROR: NULL parameter\n");
    return (DEC_PARAM_ERROR);
  }

  /* check image decoding type */
  if(p_dec_in->dec_image_type != 0 && p_dec_in->dec_image_type != 1) {
    APITRACEERR("%s","JpegDecDecode# ERROR: dec_image_type\n");
    return (DEC_PARAM_ERROR);
  }

  /* check user allocated null */
  if((p_dec_in->picture_buffer_y.virtual_address != NULL &&
       p_dec_in->picture_buffer_y.bus_address == 0) ||
      (p_dec_in->picture_buffer_cb_cr.virtual_address != NULL &&
       p_dec_in->picture_buffer_cb_cr.bus_address == 0)) {
    APITRACEERR("%s","JpegDecDecode# ERROR: NULL parameter\n");
    return (DEC_PARAM_ERROR);
  }

  if(dec_cont->abort)
    return (DEC_ABORTED);

  /* Check the stream lenth */
  if(p_dec_in->stream_length < 1) {
    APITRACEERR("%s","JpegDecDecode# ERROR: p_dec_in->stream_length\n");
    return (DEC_INVALID_STREAM_LENGTH);
  }

  /* check the input buffer settings ==>
   * checks are discarded for last buffer */
  if(!dec_cont->info.stream_end_flag) {
    /* Check the stream lenth */
    if(!dec_cont->info.input_buffer_empty &&
        (p_dec_in->stream_length > DEC_X170_MAX_STREAM_VCD) &&
        (p_dec_in->buffer_size < JPEGDEC_X170_MIN_BUFFER ||
         p_dec_in->buffer_size > JPEGDEC_X170_MAX_BUFFER)) {
      APITRACEERR("%s","JpegDecDecode# ERROR: p_dec_in->buffer_size\n");
      return (DEC_INVALID_INPUT_BUFFER_SIZE);
    }

    /* Check the stream buffer size */
    if(!dec_cont->info.input_buffer_empty &&
        p_dec_in->buffer_size && (p_dec_in->buffer_size < JPEGDEC_X170_MIN_BUFFER
                                  || p_dec_in->buffer_size >
                                  JPEGDEC_X170_MAX_BUFFER)) {
      APITRACEERR("%s","JpegDecDecode# ERROR: p_dec_in->buffer_size\n");
      return (DEC_INVALID_INPUT_BUFFER_SIZE);
    }

    /* Check the stream buffer size */
    if(!dec_cont->info.input_buffer_empty &&
        p_dec_in->buffer_size && ((p_dec_in->buffer_size % 256) != 0)) {
      APITRACEERR("%s","JpegDecDecode# ERROR: (p_dec_in->buffer_size %% 256) != 0\n");
      return (DEC_INVALID_INPUT_BUFFER_SIZE);
    }

    if(!dec_cont->info.input_buffer_empty &&
        dec_cont->info.init &&
        (p_dec_in->buffer_size < dec_cont->info.init_buffer_size)) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: Increase input buffer size!\n");
      return (DEC_INVALID_INPUT_BUFFER_SIZE);
    }
  }

  if(!dec_cont->info.init && !dec_cont->info.SliceReadyForPause &&
      !dec_cont->info.input_buffer_empty) {
    APITRACEERR("%s","JpegDecDecode#: Get Image Info!\n");

    info_ret = JpegDecGetImageInfo(dec_inst, p_dec_in, &info_tmp);

    if(info_ret != DEC_OK) {
      APITRACEERR("%s","JpegDecDecode# ERROR: Image info failed!\n");
      return (info_ret);
    }
  }

  p_dec_out->bit_depth = 0;
  for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
    p_dec_out->pictures[i].output_picture_y.virtual_address = NULL;
    p_dec_out->pictures[i].output_picture_y.bus_address = 0;
    p_dec_out->pictures[i].output_picture_cb_cr.virtual_address = NULL;
    p_dec_out->pictures[i].output_picture_cb_cr.bus_address = 0;
    p_dec_out->pictures[i].output_picture_cr.virtual_address = NULL;
    p_dec_out->pictures[i].output_picture_cr.bus_address = 0;
    p_dec_out->pictures[i].output_width = 0;
    p_dec_out->pictures[i].output_height = 0;
    p_dec_out->pictures[i].display_width = 0;
    p_dec_out->pictures[i].display_height = 0;
    p_dec_out->pictures[i].output_width_thumb = 0;
    p_dec_out->pictures[i].output_height_thumb = 0;
    p_dec_out->pictures[i].display_width_thumb = 0;
    p_dec_out->pictures[i].display_height_thumb = 0;
    p_dec_out->pictures[i].pic_stride = 0;
    p_dec_out->pictures[i].pic_stride_ch = 0;
  }

  dec_cont->stream_consumed_callback.p_strm_buff = (u8 *)p_dec_in->stream_buffer.virtual_address;
  dec_cont->stream_consumed_callback.p_user_data = p_dec_in->p_user_data;
  /* set mcu/slice value */
  dec_cont->info.slice_mb_set_value = p_dec_in->slice_mb_set;

  /* check HW supported features */
  if(0) {
    /* return if not valid HW and unsupported operation type */
    if(dec_cont->info.operation_type == JPEG_NONINTERLEAVED ||
        dec_cont->info.operation_type == JPEG_PROGRESSIVE) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: Operation type not supported\n");
      return (DEC_UNSUPPORTED);
    }

    if(dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV400 ||
        dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV440 ||
        dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV444SP)
      mcu_size_divider = 2;
    else
      mcu_size_divider = 1;

    /* check slice config */
    if((p_dec_in->slice_mb_set * (JPG_FRM.num_mcu_in_row / mcu_size_divider)) >
        dec_cont->max_supported_slice_size) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: slice_mb_set  > JPEGDEC_MAX_SLICE_SIZE\n");
      return (DEC_PARAM_ERROR);
    }

    /* check frame size */
    if((!p_dec_in->slice_mb_set) &&
        JPG_FRM.num_mcu_in_frame > dec_cont->max_supported_slice_size) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: mcu_in_frame > JPEGDEC_MAX_SLICE_SIZE\n");
      return (DEC_PARAM_ERROR);
    }
  } else {
    /* check slice config */
    if((p_dec_in->slice_mb_set && p_dec_in->dec_image_type == JPEGDEC_IMAGE &&
        dec_cont->info.operation_type != JPEG_BASELINE) ||
        (p_dec_in->slice_mb_set && p_dec_in->dec_image_type == JPEGDEC_THUMBNAIL &&
         dec_cont->info.operation_type_thumb != JPEG_BASELINE)) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: Slice mode not supported for this operation type\n");
      return (DEC_SLICE_MODE_UNSUPPORTED);
    }

#ifdef SLICE_MODE_LARGE_PIC
    /* check if frame size over 16M */
    if((!p_dec_in->slice_mb_set) &&
        ((JPG_FRM.hw_x * JPG_FRM.hw_y) > dec->hw_feature.img_max_dec_width*
          dec->hw_feature.img_max_dec_height)) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: Resolution > 16M ==> use slice mode!\n");
      return (DEC_PARAM_ERROR);
    }
#endif

    if(dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV400 ||
        dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV440 ||
        dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV444SP)
      mcu_size_divider = 2;
    else
      mcu_size_divider = 1;

    /* check slice config */
    if((p_dec_in->slice_mb_set * (JPG_FRM.num_mcu_in_row / mcu_size_divider)) >
        dec_cont->max_supported_slice_size) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: slice_mb_set  > JPEGDEC_MAX_SLICE_SIZE\n");
      return (DEC_PARAM_ERROR);
    }
  }

  if(p_dec_in->slice_mb_set > 255) {
    APITRACEERR
    ("%s","JpegDecDecode# ERROR: slice_mb_set  > Maximum slice size\n");
    return (DEC_PARAM_ERROR);
  }

  /* check slice size */
  if(p_dec_in->slice_mb_set &&
      !dec_cont->info.SliceReadyForPause && !dec_cont->info.input_buffer_empty) {
    if(dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV400 ||
        dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV440 ||
        dec_cont->info.get_info_ycb_cr_mode == DEC_OUT_FRM_YUV444SP)
      mcu_size_divider = 2;
    else
      mcu_size_divider = 1;

    if((p_dec_in->slice_mb_set * (JPG_FRM.num_mcu_in_row / mcu_size_divider)) >
        JPG_FRM.num_mcu_in_frame) {
      APITRACEERR
      ("%s","JpegDecDecode# ERROR: (slice_mb_set * Number of MCU's in row) > Number of MCU's in frame\n");
      return (DEC_PARAM_ERROR);
    }
  }

  /* Handle stream/hw parameters after buffer empty */
  if(dec_cont->info.input_buffer_empty) {
    /* Store the stream parameters */
    dec_cont->stream.bit_pos_in_byte = 0;
    dec_cont->stream.p_start_of_stream =
      dec_cont->stream.p_curr_pos = (u8 *) p_dec_in->stream;
    dec_cont->stream.stream_bus = p_dec_in->stream_buffer.bus_address;
    dec_cont->stream.p_start_of_buffer =
      (u8 *) p_dec_in->stream_buffer.virtual_address;
    dec_cont->stream.strm_buff_size =  p_dec_in->stream_buffer.logical_size;

    /* update hw parameters */
    dec_cont->info.input_streaming = 1;
    if(p_dec_in->buffer_size)
      dec_cont->info.input_buffer_len = p_dec_in->buffer_size;
    else
      dec_cont->info.input_buffer_len = p_dec_in->stream_length;

    /* decoded stream */
    dec_cont->info.decoded_stream_len += dec_cont->info.input_buffer_len;

    if(dec_cont->info.decoded_stream_len > p_dec_in->stream_length) {
      APITRACEERR
      ("%s","JpegDecDecode# Error: All input stream already processed\n");
      return DEC_STRM_ERROR;
    }
  }

  /* update user allocated output */
  dec_cont->info.given_out_luma.virtual_address =
    p_dec_in->picture_buffer_y.virtual_address;
  dec_cont->info.given_out_luma.bus_address = p_dec_in->picture_buffer_y.bus_address;
  dec_cont->info.given_out_chroma.virtual_address =
    p_dec_in->picture_buffer_cb_cr.virtual_address;
  dec_cont->info.given_out_chroma.bus_address =
    p_dec_in->picture_buffer_cb_cr.bus_address;
  dec_cont->info.given_out_chroma2.virtual_address =
    p_dec_in->picture_buffer_cr.virtual_address;
  dec_cont->info.given_out_chroma2.bus_address =
    p_dec_in->picture_buffer_cr.bus_address;

  /* check if input streaming used */
  if(!dec_cont->info.SliceReadyForPause &&
      !dec_cont->info.input_buffer_empty && p_dec_in->buffer_size) {
    dec_cont->info.input_streaming = 1;
    dec_cont->info.input_buffer_len = p_dec_in->buffer_size;
    dec_cont->info.decoded_stream_len += dec_cont->info.input_buffer_len;
  }

  /* if use Pre-added Buffer mode */
  if(p_dec_in->picture_buffer_y.virtual_address == NULL) {
    if (dec_cont->ext_buffer_num == 0) {
      p_dec_out->output.data_left = p_dec_in->stream_length;
      p_dec_out->output.strm_curr_pos = (u8 *)p_dec_in->stream;
      dec_cont->prev_pp_width = dec_cont->ppu_cfg[0].scale.width;
      dec_cont->prev_pp_height = dec_cont->ppu_cfg[0].scale.height;
      return (DEC_WAITING_FOR_BUFFER);
    }

    if (!dec_cont->realloc_buffer) {
      pp_buffer = InputQueueGetBuffer(dec_cont->pp_buffer_queue, 0);
      if (pp_buffer == NULL) {
        if (dec_cont->abort)
          return DEC_ABORTED;
        else {
          p_dec_out->output.data_left = p_dec_in->stream_length;
          p_dec_out->output.strm_curr_pos = (u8 *)p_dec_in->stream;
          return DEC_NO_DECODING_BUFFER;
        }
      }

      /* reallocate buffer */
      if ((pp_buffer->size < dec_cont->next_buf_size && dec_cont->use_adaptive_buffers) ||
          ((dec_cont->prev_pp_width != dec_cont->ppu_cfg[0].scale.width ||
            dec_cont->prev_pp_height != dec_cont->ppu_cfg[0].scale.height) &&
            !dec_cont->use_adaptive_buffers)) {
        for (i = 0; i < 16; i++) {
          if (pp_buffer->virtual_address == dec_cont->ext_buffers[i].virtual_address)
            break;
        }
        ASSERT(i < 16);
        dec_cont->buffer_queue_index = InputQueueFindBufferId(dec_cont->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*pp_buffer));
        dec_cont->buffer_index = i;
        dec_cont->realloc_buffer = 1;
        dec_cont->buf_to_free = &dec_cont->ext_buffers[i];
        dec_cont->buf_num = 1;
        p_dec_out->output.data_left = p_dec_in->stream_length;
        p_dec_out->output.strm_curr_pos = (u8 *)p_dec_in->stream;
        dec_cont->prev_pp_width = dec_cont->ppu_cfg[0].scale.width;
        dec_cont->prev_pp_height = dec_cont->ppu_cfg[0].scale.height;
        return DEC_WAITING_FOR_BUFFER;
      }

      dec_cont->asic_buff.pp_luma_buffer = *pp_buffer;
    } else {
      if (dec_cont->ext_buffers[dec_cont->buffer_index].size < dec_cont->next_buf_size) {
        dec_cont->buf_to_free = &dec_cont->ext_buffers[dec_cont->buffer_index];
        dec_cont->buf_num = 1;
        p_dec_out->output.data_left = p_dec_in->stream_length;
        p_dec_out->output.strm_curr_pos = (u8 *)p_dec_in->stream;
        return DEC_WAITING_FOR_BUFFER;
      }
      dec_cont->realloc_buffer = 0;
      dec_cont->asic_buff.pp_luma_buffer = dec_cont->ext_buffers[dec_cont->buffer_index];
    }
#ifdef ENABLE_FPGA_VERIFICATION
    DWLmemset(dec_cont->asic_buff.pp_luma_buffer.virtual_address, 0x0,
              dec_cont->asic_buff.pp_luma_buffer.size);
#ifdef SUPPORT_DMA
    DWLDMATransData((addr_t)dec_cont->asic_buff.pp_luma_buffer.bus_address,
                    (void *)dec_cont->asic_buff.pp_luma_buffer.virtual_address,
                    dec_cont->asic_buff.pp_luma_buffer.size, HOST_TO_DEVICE);
#endif
#else
    for (u32 i = 0; i < DEC_MAX_PPU_COUNT; i++) {
      if(dec_cont->ppu_cfg[i].enabled && dec_cont->ppu_cfg[i].pp_comp) {
        DWLmemset(dec_cont->asic_buff.pp_luma_buffer.virtual_address, 0x0,
                  dec_cont->asic_buff.pp_luma_buffer.size);
        break;
      }
    }
#endif

    u32 pp_width = 0, pp_height_luma = 0, pp_stride = 0, pp_buff_size = 0;
    PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
    if (dec_cont->info.slice_mb_set_value) {
      if (ppu_cfg->tiled_e) {
        pp_width = dec_cont->info.X >> dec_cont->dscale_shift_x;
        pp_height_luma = NEXT_MULTIPLE(dec_cont->info.slice_mb_set_value * 16 >>
                           dec_cont->dscale_shift_y, 4) / 4;
        pp_stride = NEXT_MULTIPLE(4 * pp_width, ALIGN(ppu_cfg->align));
      } else {
        pp_width = dec_cont->info.X >> dec_cont->dscale_shift_x;
        pp_height_luma = dec_cont->info.slice_mb_set_value * 16 >>
                           dec_cont->dscale_shift_y;
        pp_stride = NEXT_MULTIPLE(pp_width, ALIGN(ppu_cfg->align));
        pp_buff_size = pp_stride * pp_height_luma;
      }
    }
    if (dec_cont->info.slice_mb_set_value) {
      dec_cont->asic_buff.pp_chroma_buffer.virtual_address =
        dec_cont->asic_buff.pp_luma_buffer.virtual_address + pp_buff_size/4;
      dec_cont->asic_buff.pp_chroma_buffer.bus_address =
        dec_cont->asic_buff.pp_luma_buffer.bus_address + pp_buff_size;
    } else {
      dec_cont->asic_buff.pp_chroma_buffer.virtual_address =
        dec_cont->asic_buff.pp_luma_buffer.virtual_address;
      dec_cont->asic_buff.pp_chroma_buffer.bus_address =
        dec_cont->asic_buff.pp_luma_buffer.bus_address;
    }
  }

  /* reset mcuNumbers */
  dec_cont->frame.mcu_number = 0;
  dec_cont->frame.row = dec_cont->frame.col = 0;

  /* set mode & calculate rlc tmp size */
  ret_code = JpegDecMode(dec_cont);
  if(ret_code == DEC_UNSUPPORTED) {
    APITRACEERR("%s","JpegDecDecode# UNSUPPORTED: DEC_UNSUPPORTED\n");
    goto end;
  }

  if(!dec_cont->info.allocated) {
    ret_code = JpegDecAllocateResidual(dec_cont);
    if(ret_code != DEC_OK) {
      APITRACEERR("%s","SCAN: ALLOCATE ERROR\n");
      goto end;
    }
    /* update */
    dec_cont->info.allocated = 1;
  }

  /* check SOF header ready */
  if (dec_cont->image.header_ready == 0) {
    JpegDecClearStructs(dec_inst, 1);
    APITRACEERR("%s","JpegDecDecode# ERROR: No frame header before Scan header \n");
    goto end;
  }

  dec_cont->frame.hw_x = dec_cont->frame.X;

  /* round up to next multiple-of-8 */
  dec_cont->frame.hw_x += 0x7;
  dec_cont->frame.hw_x &= ~(0x7);
  /* for internal() */
  dec_cont->info.X = dec_cont->frame.hw_x;
  dec_cont->info.Y = dec_cont->frame.hw_y;

  ret_code = DEC_OK;

  /* Handle decoded image here */
  if(dec_cont->image.header_ready) {
    if (!dec_cont->frame.intervals)
      dec_cont->ri_mc_enabled = RI_MC_DISABLED_BY_RI;
    if (RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
      dec_cont->frame.ri_array = (u8 **)DWLmalloc(dec_cont->frame.intervals * sizeof(u8*));
      ASSERT(dec_cont->frame.ri_array);
      if (p_dec_in->ri_count > 1 && p_dec_in->ri_array) {
        for (i = 0; i < p_dec_in->ri_count; i++) {
          if (p_dec_in->ri_array[i]) {
            dec_cont->frame.ri_array[i] = dec_cont->stream.p_start_of_stream +
                                          p_dec_in->ri_array[i];
            if (dec_cont->frame.ri_array[i] >=
               (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
              dec_cont->frame.ri_array[i] -= dec_cont->stream.strm_buff_size;
          }
          else {
            /* Missing restart interval. */
            dec_cont->frame.ri_array[i] = NULL;
          }
        }
      } else if (dec_cont->allow_sw_ri_parse) {
        JpegParseRST(dec_cont, dec_cont->stream.p_start_of_stream,
                    dec_cont->stream.stream_length,
                    dec_cont->frame.ri_array);
      }
      dec_cont->ri_running_cores = 0;
      dec_cont->ri_index = dec_cont->first_ri_index;
    }
    /* loop until decoding control should return for user */
    do {
      /* if pp enabled ==> set pp control */
      if(dec_cont->pp_instance != NULL) {
        dec_cont->pp_config_query.tiled_mode = 0;
        dec_cont->PPConfigQuery(dec_cont->pp_instance,
                                &dec_cont->pp_config_query);

        dec_cont->pp_control.use_pipeline =
          dec_cont->pp_config_query.pipeline_accepted;

        /* set pp for combined mode */
        if(dec_cont->pp_control.use_pipeline)
          JpegDecPreparePp(dec_cont);
      }

      /* check if we had to load imput buffer or not */
      if(!dec_cont->info.input_buffer_empty) {
        /* if slice mode ==> set slice height */
        if(dec_cont->info.slice_mb_set_value &&
            dec_cont->pp_control.use_pipeline == 0) {
          JpegDecSliceSizeCalculation(dec_cont);
        }

        /* Start HW or continue after pause */
        if(!dec_cont->info.SliceReadyForPause) {
          APITRACEDEBUG("%s","JpegDecDecode# Start HW init\n");
          if (dec_cont->ri_index && RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
            dec_cont->stream.p_curr_pos = dec_cont->frame.ri_array[dec_cont->ri_index];
            dec_cont->stream.bit_pos_in_byte = 0;
            if (!dec_cont->stream.p_curr_pos) {
              /* Missing restart interval. */
              dec_cont->ri_index++;
              continue;
            }
          }
          ret_code = JpegDecInitHW(dec_cont);
          if(ret_code != DEC_OK) {
            /* return DEC_HW_RESERVED */
            goto end;
          }
        } else {
          APITRACEDEBUG
          ("%s","JpegDecDecode# Continue HW decoding after slice ready\n");
          JpegDecInitHWContinue(dec_cont);
        }

        dec_cont->info.SliceCount++;

      } else {
        APITRACEDEBUG
        ("%s","JpegDecDecode# Continue HW decoding after input buffer has been loaded\n");
        JpegDecInitHWInputBuffLoad(dec_cont);

        /* buffer loaded ==> reset flag */
        dec_cont->info.input_buffer_empty = 0;
      }

      if (dec_cont->b_mc || RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
        /* reset shadow HW status reg values so that we dont end up writing
         * some garbage to next core regs */
        JpegRefreshRegs(dec_cont);
        SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_E, 0);
        SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_IRQ_STAT, 0);
        SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_IRQ, 0);
        if (RI_MC_DISABLED(dec_cont->ri_mc_enabled)) {
          JpegMCSetHwRdyCallback(dec_cont);
          dec_cont->asic_running = 0;
          dwlret = DWL_HW_WAIT_OK;
          asic_status = DEC_HW_IRQ_RDY;
        } else {
          JpegRiMCSetHwRdyCallback(dec_cont);
          dwlret = DWL_HW_WAIT_OK;
          asic_status = DEC_HW_IRQ_RDY;
        }
      } else {
#ifdef JPEGDEC_PERFORMANCE
        dwlret = DWL_HW_WAIT_OK;
#else
        /* wait hw ready */
        if (!dec_cont->vcmd_used)
          dwlret = DWLWaitHwReady(dec_cont->dwl, dec_cont->core_id,
                                  dec_cont->info.timeout);
        else
          dwlret = DWLWaitCmdBufReady(dec_cont->dwl, dec_cont->cmd_buf_id);
#endif /* #ifdef JPEGDEC_PERFORMANCE */
        /* Refresh regs */
        JpegRefreshRegs(dec_cont);
      }

#ifdef SUPPORT_DMA
#ifdef ENABLE_FPGA_VERIFICATION /* Just uesd for FPGA verification,
                                   the customer can remove it according to demand. */
/* - pp enable : the DMA transfers pp_buffer from device to host for verification.
 * - pp disable : the DMA transfers out_buffer from device to host for verification.
 */
  if (dec_cont->pp_enabled) /* pp enable */ /* luma/chroma both in pp_luma_buffer */
    DWLDMATransData((addr_t)dec_cont->asic_buff.pp_luma_buffer.bus_address,
                    (void *)dec_cont->asic_buff.pp_luma_buffer.virtual_address,
                    dec_cont->asic_buff.pp_luma_buffer.size, DEVICE_TO_HOST);
  else { /* pp disable */
    DWLDMATransData((addr_t)dec_cont->asic_buff.out_luma_buffer.bus_address,
                    (void *)dec_cont->asic_buff.out_luma_buffer.virtual_address,
                    dec_cont->asic_buff.out_luma_buffer.size, DEVICE_TO_HOST);
    DWLDMATransData((addr_t)dec_cont->asic_buff.out_chroma_buffer.bus_address,
                    (void *)dec_cont->asic_buff.out_chroma_buffer.virtual_address,
                    dec_cont->asic_buff.out_chroma_buffer.size, DEVICE_TO_HOST);
    DWLDMATransData((addr_t)dec_cont->asic_buff.out_chroma_buffer2.bus_address,
                    (void *)dec_cont->asic_buff.out_chroma_buffer2.virtual_address,
                    dec_cont->asic_buff.out_chroma_buffer2.size, DEVICE_TO_HOST);
  }
#endif
  /* if use Pre-added Buffer mode */
  if(p_dec_in->picture_buffer_y.virtual_address != NULL)
    DWLDMATransData((addr_t)p_dec_in->picture_buffer_y.bus_address,
                    (void *)p_dec_in->picture_buffer_y.virtual_address,
                    p_dec_in->picture_buffer_y.size, DEVICE_TO_HOST);
  if(p_dec_in->picture_buffer_cb_cr.virtual_address != NULL)
    DWLDMATransData((addr_t)p_dec_in->picture_buffer_cb_cr.bus_address,
                    (void *)p_dec_in->picture_buffer_cb_cr.virtual_address,
                    p_dec_in->picture_buffer_cb_cr.size, DEVICE_TO_HOST);
  if(p_dec_in->picture_buffer_cr.virtual_address != NULL)
    DWLDMATransData((addr_t)p_dec_in->picture_buffer_cr.bus_address,
                    (void *)p_dec_in->picture_buffer_cr.virtual_address,
                    p_dec_in->picture_buffer_cr.size, DEVICE_TO_HOST);
#endif

      if(dwlret == DWL_HW_WAIT_OK) {
        APITRACEDEBUG("%s","JpegDecDecode# DWL_HW_WAIT_OK\n");

#ifdef JPEGDEC_ASIC_TRACE
        {
          APITRACEDEBUG("%s","Jpeg_dec_decode# AFTER DWL_HW_WAIT_OK\n");
          PrintJPEGReg(dec_cont->jpeg_regs);
        }
#endif /* #ifdef JPEGDEC_ASIC_TRACE */
        /* check && reset status */
        if (!dec_cont->b_mc && RI_MC_DISABLED(dec_cont->ri_mc_enabled)) {
          asic_status =
            GetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_IRQ_STAT);
        }

        if(asic_status & DEC_HW_IRQ_BUS) {
          /* check PP status... and go */
          if(dec_cont->pp_instance != NULL) {
            /* End PP co-operation */
            if(dec_cont->pp_control.pp_status == DECPP_RUNNING) {
              APITRACEDEBUG("%s","JpegDecDecode# PP END CALL\n");
              dec_cont->PPEndCallback(dec_cont->pp_instance);
              dec_cont->pp_control.pp_status = DECPP_PIC_READY;
            }
          }

          APITRACEERR
          ("%s","JpegDecDecode# DEC_HW_IRQ_BUS\n");
          /* clear interrupts */
          JPEGDEC_CLEAR_IRQ;

          SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_E, 0);
          if (!dec_cont->vcmd_used) {
            DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                         dec_cont->jpeg_regs[1]);
            /* Release HW */
            (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
          }
          else {
            DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
          }
          /* update asic_running */
          dec_cont->asic_running = 0;

          ret_code = DEC_HW_BUS_ERROR;
          goto end;
        } else if(asic_status & DEC_HW_IRQ_ERROR ||
                  asic_status & DEC_HW_IRQ_TIMEOUT ||
                  asic_status & DEC_HW_IRQ_ABORT ) {
          /* check PP status... and go */
          if(dec_cont->pp_instance != NULL) {
            /* End PP co-operation */
            if(dec_cont->pp_control.pp_status == DECPP_RUNNING) {
              APITRACEDEBUG("%s","JpegDecDecode# PP END CALL\n");
              dec_cont->PPEndCallback(dec_cont->pp_instance);
            }

            dec_cont->pp_control.pp_status = DECPP_PIC_READY;
          }

          if(asic_status & DEC_HW_IRQ_ERROR) {
            APITRACEERR
            ("%s","JpegDecDecode# DEC_HW_IRQ_ERROR\n");
          } else if(asic_status & DEC_HW_IRQ_TIMEOUT) {
            APITRACEERR
            ("%s","JpegDecDecode# DEC_HW_IRQ_TIMEOUT\n");
          } else {
            APITRACEERR
            ("%s","JpegDecDecode# JPEGDEC_X170_IRQ_ABORT\n");
          }

          /* clear interrupts */
          JPEGDEC_CLEAR_IRQ;

          SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_E, 0);
          /* Release HW */
          if (!dec_cont->vcmd_used) {
            DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1,
                         dec_cont->jpeg_regs[1]);

            (void)DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
          } else
            DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);

          /* update asic_running */
          dec_cont->asic_running = 0;

          /* output set */
          if(dec_cont->pp_instance == NULL) {
            if (dec_cont->info.user_alloc_mem) {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_y.virtual_address =
                  (u32*)((u8*)dec_cont->info.out_luma.virtual_address + ppu_cfg->luma_offset);
              }
            }
            else {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_y.virtual_address =
                (u32*)((addr_t)dec_cont->info.out_pp_luma.virtual_address + ppu_cfg->luma_offset);
              }
            }

            /* output set */
            if (dec_cont->info.user_alloc_mem) {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_y.bus_address =
                  dec_cont->info.out_luma.bus_address + ppu_cfg->luma_offset;
              }
            }
            else {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_y.bus_address =
                  dec_cont->info.out_pp_luma.bus_address + ppu_cfg->luma_offset;
              }
            }

            /* if not grayscale */
            if(dec_cont->image.size_chroma || (dec_cont->pp_enabled && !(dec_cont->info.user_alloc_mem))) {
              if (dec_cont->info.user_alloc_mem) {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  p_dec_out->pictures[i].output_picture_cb_cr.virtual_address =
                    (u32*)((u8*)dec_cont->info.out_chroma.virtual_address + ppu_cfg->chroma_offset);
                }
              }
              else {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                   p_dec_out->pictures[i].output_picture_cb_cr.virtual_address =
                   (u32*)((addr_t)dec_cont->info.out_pp_chroma.virtual_address + ppu_cfg->chroma_offset);
                }
              }

              if (dec_cont->info.user_alloc_mem) {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  p_dec_out->pictures[i].output_picture_cb_cr.bus_address =
                    dec_cont->info.out_chroma.bus_address + ppu_cfg->chroma_offset;
                }
              }
              else {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                   p_dec_out->pictures[i].output_picture_cb_cr.bus_address =
                     dec_cont->info.out_pp_chroma.bus_address + ppu_cfg->chroma_offset;
                }
              }

              p_dec_out->pictures[0].output_picture_cr.virtual_address =
                dec_cont->info.out_chroma2.virtual_address;
              p_dec_out->pictures[0].output_picture_cr.bus_address =
                dec_cont->info.out_chroma2.bus_address;
            }
            // if(dec_cont->pp_enabled)
            {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              p_dec_out->bit_depth = dec_cont->frame.P;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                if (!p_dec_in->dec_image_type) {
                  if (dec_cont->ppu_cfg[i].crop2.enabled) {
                    p_dec_out->pictures[i].output_width = ((dec_cont->ppu_cfg[i].crop2.width + 15) >> 4) << 4;
                    p_dec_out->pictures[i].output_height = dec_cont->ppu_cfg[i].crop2.height;
                    p_dec_out->pictures[i].display_width = dec_cont->ppu_cfg[i].crop2.width;
                    p_dec_out->pictures[i].display_height = dec_cont->ppu_cfg[i].crop2.height;
                  } else {
                    p_dec_out->pictures[i].output_width = ((dec_cont->ppu_cfg[i].scale.width + 15) >> 4) << 4;
                    p_dec_out->pictures[i].output_height = dec_cont->ppu_cfg[i].scale.height;
                    p_dec_out->pictures[i].display_width = dec_cont->ppu_cfg[i].scale.enabled ? dec_cont->ppu_cfg[i].scale.width : dec_cont->frame.X;
                    p_dec_out->pictures[i].display_height = dec_cont->ppu_cfg[i].scale.height;
                  }
                  p_dec_out->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
                  p_dec_out->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
                  p_dec_out->pictures[i].output_format = TransUnitConfig2Format(ppu_cfg);
                } else {
                  if (ppu_cfg->crop2.enabled) {
                    p_dec_out->pictures[i].output_width_thumb = ((dec_cont->ppu_cfg[i].crop2.width + 15) >> 4) << 4;
                    p_dec_out->pictures[i].output_height_thumb = dec_cont->ppu_cfg[i].crop2.height;
                    p_dec_out->pictures[i].display_width_thumb = dec_cont->ppu_cfg[i].crop2.width;
                    p_dec_out->pictures[i].display_height_thumb = dec_cont->ppu_cfg[i].crop2.height;
                  } else {
                    p_dec_out->pictures[i].output_width_thumb = ((dec_cont->ppu_cfg[i].scale.width + 15) >> 4) << 4;
                    p_dec_out->pictures[i].output_height_thumb = dec_cont->ppu_cfg[i].scale.height;
                    p_dec_out->pictures[i].display_width_thumb = dec_cont->ppu_cfg[i].scale.enabled ? dec_cont->ppu_cfg[i].scale.width : dec_cont->frame.X;
                    p_dec_out->pictures[i].display_height_thumb = dec_cont->ppu_cfg[i].scale.height;
                  }
                  p_dec_out->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
                  p_dec_out->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
                  p_dec_out->pictures[i].output_format = TransUnitConfig2Format(ppu_cfg);
                }
              }
            }
#ifdef SUPPORT_DEC400
            PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
            for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
              if (!ppu_cfg->enabled) continue;
              if (ppu_cfg->luma_size) {
                if(tile_status_bus_address == 0) {
                  tile_status_virtual_address = p_dec_out->pictures[i].output_picture_y.virtual_address;
                  tile_status_bus_address = p_dec_out->pictures[i].output_picture_y.bus_address;
                }
              }
            }
            ppu_cfg = dec_cont->ppu_cfg;
            for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
              if (!ppu_cfg->enabled || !ppu_cfg->dec400_enabled || ppu_cfg->rgb) continue;
              PpFillDec400TblInfo(ppu_cfg,
                          tile_status_virtual_address,
                          tile_status_bus_address,
                          &p_dec_out->pictures[i].dec400_luma_table,
                          &p_dec_out->pictures[i].dec400_chroma_table);
            }
#endif
          }

          if (dec_cont->b_mc ||
             (p_dec_in->picture_buffer_y.virtual_address == NULL &&
             ((dec_cont->ri_mc_enabled == RI_MC_ENA &&
             dec_cont->ri_index == dec_cont->last_ri_index) ||
             dec_cont->ri_mc_enabled != RI_MC_ENA)) ||
             dec_cont->info.user_alloc_mem) {
            p_dec_out->cycles_per_mb = JpegCycleCount(dec_cont);
            PushOutputPic(&dec_cont->fb_list, p_dec_out, &(dec_cont->p_image_info));
          }

          JpegDecClearStructs(dec_inst, 1);
          ret_code = DEC_STRM_ERROR;
          goto end;
        } else if(asic_status & DEC_HW_IRQ_BUFFER) {
          /* check if frame is ready */
          if(!(asic_status & DEC_HW_IRQ_RDY)) {
            APITRACEDEBUG
            ("%s","JpegDecDecode# DEC_HW_IRQ_BUFFER/STREAM PROCESSED\n");

#ifdef CASE_INFO_STAT
            if(case_info.frame_num < 10)
              case_info.slice_num[case_info.frame_num]++;
#endif
            /* clear interrupts */
            SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_BUFFER_INT,
                           0);

            /* flag to load buffer */
            dec_cont->info.input_buffer_empty = 1;

            /* check if all stream should be processed with the
             * next buffer ==> may affect to some API checks */
            if((dec_cont->info.decoded_stream_len +
                dec_cont->info.input_buffer_len) >=
                dec_cont->stream.stream_length) {
              dec_cont->info.stream_end_flag = 1;
            }

            /* output set */
            if(dec_cont->pp_instance == NULL) {
              if (dec_cont->info.user_alloc_mem) {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  p_dec_out->pictures[i].output_picture_y.virtual_address =
                    (u32*)((u8*)dec_cont->info.out_luma.virtual_address + ppu_cfg->luma_offset);
                }
              }
              else {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  p_dec_out->pictures[i].output_picture_y.virtual_address =
                  (u32*)((addr_t)dec_cont->info.out_pp_luma.virtual_address + ppu_cfg->luma_offset);
                }
              }

              /* output set */
              if (dec_cont->info.user_alloc_mem) {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  p_dec_out->pictures[i].output_picture_y.bus_address =
                    dec_cont->info.out_luma.bus_address + ppu_cfg->luma_offset;
                }
              }
              else {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  p_dec_out->pictures[i].output_picture_y.bus_address =
                    dec_cont->info.out_pp_luma.bus_address + ppu_cfg->luma_offset;
                }
              }

              /* if not grayscale */
              if(dec_cont->image.size_chroma || (dec_cont->pp_enabled && !(dec_cont->info.user_alloc_mem))) {
                if (dec_cont->info.user_alloc_mem) {
                  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                  for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                    if (!ppu_cfg->enabled) continue;
                    p_dec_out->pictures[i].output_picture_cb_cr.virtual_address =
                      (u32*)((u8*)dec_cont->info.out_chroma.virtual_address + ppu_cfg->chroma_offset);
                  }
                }
                else {
                  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                  for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                    if (!ppu_cfg->enabled) continue;
                     p_dec_out->pictures[i].output_picture_cb_cr.virtual_address =
                     (u32*)((addr_t)dec_cont->info.out_pp_chroma.virtual_address + ppu_cfg->chroma_offset);
                  }
                }

                if (dec_cont->info.user_alloc_mem) {
                  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                  for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                    if (!ppu_cfg->enabled) continue;
                    p_dec_out->pictures[i].output_picture_cb_cr.bus_address =
                      dec_cont->info.out_chroma.bus_address + ppu_cfg->chroma_offset;
                  }
                }
                else {
                  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                  for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                    if (!ppu_cfg->enabled) continue;
                    p_dec_out->pictures[i].output_picture_cb_cr.bus_address =
                      dec_cont->info.out_pp_chroma.bus_address + ppu_cfg->chroma_offset;
                  }
                }

                p_dec_out->pictures[0].output_picture_cr.virtual_address =
                  dec_cont->info.out_chroma2.virtual_address;
                p_dec_out->pictures[0].output_picture_cr.bus_address =
                  dec_cont->info.out_chroma2.bus_address;
              }
              // if(dec_cont->pp_enabled)
              {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                p_dec_out->bit_depth = dec_cont->frame.P;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  if (!p_dec_in->dec_image_type) {
                    if (dec_cont->ppu_cfg[i].crop2.enabled) {
                      p_dec_out->pictures[i].output_width = ((dec_cont->ppu_cfg[i].crop2.width + 15) >> 4) << 4;
                      p_dec_out->pictures[i].output_height = dec_cont->ppu_cfg[i].crop2.height;
                      p_dec_out->pictures[i].display_width = dec_cont->ppu_cfg[i].crop2.width;
                      p_dec_out->pictures[i].display_height = dec_cont->ppu_cfg[i].crop2.height;
                    } else {
                      p_dec_out->pictures[i].output_width = ((dec_cont->ppu_cfg[i].scale.width + 15) >> 4) << 4;
                      p_dec_out->pictures[i].output_height = dec_cont->ppu_cfg[i].scale.height;
                      p_dec_out->pictures[i].display_width = dec_cont->ppu_cfg[i].scale.enabled ? dec_cont->ppu_cfg[i].scale.width : dec_cont->frame.X;
                      p_dec_out->pictures[i].display_height = dec_cont->ppu_cfg[i].scale.height;
                    }
                    p_dec_out->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
                    p_dec_out->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
                    p_dec_out->pictures[i].output_format = TransUnitConfig2Format(ppu_cfg);
                  } else {
                    if (dec_cont->ppu_cfg[i].crop2.enabled) {
                      p_dec_out->pictures[i].output_width_thumb = ((dec_cont->ppu_cfg[i].crop2.width + 15) >> 4) << 4;
                      p_dec_out->pictures[i].output_height_thumb = dec_cont->ppu_cfg[i].crop2.height;
                      p_dec_out->pictures[i].display_width_thumb = dec_cont->ppu_cfg[i].crop2.width;
                      p_dec_out->pictures[i].display_height_thumb = dec_cont->ppu_cfg[i].crop2.height;
                    } else {
                      p_dec_out->pictures[i].output_width_thumb = ((dec_cont->ppu_cfg[i].scale.width + 15) >> 4) << 4;
                      p_dec_out->pictures[i].output_height_thumb = dec_cont->ppu_cfg[i].scale.height;
                      p_dec_out->pictures[i].display_width_thumb = dec_cont->ppu_cfg[i].scale.enabled ? dec_cont->ppu_cfg[i].scale.width : dec_cont->frame.X;
                      p_dec_out->pictures[i].display_height_thumb = dec_cont->ppu_cfg[i].scale.height;
                    }
                    p_dec_out->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
                    p_dec_out->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
                    p_dec_out->pictures[i].output_format = TransUnitConfig2Format(ppu_cfg);
                  }
                }
              }
#ifdef SUPPORT_DEC400
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                if (ppu_cfg->luma_size) {
                  if(tile_status_bus_address == 0) {
                    tile_status_virtual_address = p_dec_out->pictures[i].output_picture_y.virtual_address;
                    tile_status_bus_address = p_dec_out->pictures[i].output_picture_y.bus_address;
                  }
                }
              }
              ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled || !ppu_cfg->dec400_enabled || ppu_cfg->rgb) continue;
                PpFillDec400TblInfo(ppu_cfg,
                          tile_status_virtual_address,
                          tile_status_bus_address,
                          &p_dec_out->pictures[i].dec400_luma_table,
                          &p_dec_out->pictures[i].dec400_chroma_table);
              }
#endif
            }

            ret_code = DEC_STRM_PROCESSED;
            goto end;
          }
        }

        SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_RDY_INT, 0);
        HINTdec = GetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_IRQ);
        if(HINTdec) {
          APITRACEDEBUG("%s","JpegDecDecode# CLEAR interrupt\n");
          SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_IRQ, 0);
        }
        SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_IRQ_STAT, 0);

        /* check if slice ready */
        asic_slice_bit = GetDecRegister(dec_cont->jpeg_regs,
                                        HWIF_JPEG_SLICE_H);
        int_dec = GetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_SLICE_INT);

        /* slice ready ==> reset interrupt */
        if(asic_slice_bit && int_dec && !dec_cont->b_mc &&
           RI_MC_DISABLED(dec_cont->ri_mc_enabled)) {
          /* if x170 pp not in use */
          if(dec_cont->pp_instance == NULL)
            dec_cont->info.SliceReadyForPause = 1;
          else
            dec_cont->info.SliceReadyForPause = 0;

          if(dec_cont->pp_instance != NULL &&
              !dec_cont->pp_control.use_pipeline) {
            dec_cont->info.SliceReadyForPause = 1;
          }

          /* if user allocated memory return given base */
          if(dec_cont->info.user_alloc_mem == 1 &&
              dec_cont->info.SliceReadyForPause == 1) {
            /* output addresses */
            p_dec_out->pictures[0].output_picture_y.virtual_address =
              dec_cont->info.given_out_luma.virtual_address;
            p_dec_out->pictures[0].output_picture_y.bus_address =
              dec_cont->info.given_out_luma.bus_address;
            if(dec_cont->image.size_chroma) {
              p_dec_out->pictures[0].output_picture_cb_cr.virtual_address =
                dec_cont->info.given_out_chroma.virtual_address;
              p_dec_out->pictures[0].output_picture_cb_cr.bus_address =
                dec_cont->info.given_out_chroma.bus_address;
              p_dec_out->pictures[0].output_picture_cr.virtual_address =
                dec_cont->info.given_out_chroma2.virtual_address;
              p_dec_out->pictures[0].output_picture_cr.bus_address =
                dec_cont->info.given_out_chroma2.bus_address;
            }
          }

          /* if not user allocated memory return slice base */
          if(dec_cont->info.user_alloc_mem == 0 &&
              dec_cont->info.SliceReadyForPause == 1) {
            /* output addresses */
            if (dec_cont->info.user_alloc_mem) {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_y.virtual_address =
                  (u32*)((u8*)dec_cont->info.out_luma.virtual_address + ppu_cfg->luma_offset);
                p_dec_out->pictures[i].output_picture_y.bus_address =
                  dec_cont->info.out_luma.bus_address + ppu_cfg->luma_offset;
              }
            }
            else {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_y.virtual_address =
                (u32*)((addr_t)dec_cont->info.out_pp_luma.virtual_address + ppu_cfg->luma_offset);
                p_dec_out->pictures[i].output_picture_y.bus_address = dec_cont->info.out_pp_luma.bus_address + ppu_cfg->luma_offset;
              }
            }
            if(dec_cont->image.size_chroma || dec_cont->pp_enabled) {
              if (!dec_cont->pp_enabled) {
                p_dec_out->pictures[0].output_picture_cb_cr.virtual_address =
                  dec_cont->info.out_chroma.virtual_address;
                p_dec_out->pictures[0].output_picture_cb_cr.bus_address =
                  dec_cont->info.out_chroma.bus_address;
              }
              else {
                PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                   p_dec_out->pictures[i].output_picture_cb_cr.virtual_address =
                   (u32*)((addr_t)dec_cont->info.out_pp_chroma.virtual_address + ppu_cfg->chroma_offset);
                   p_dec_out->pictures[i].output_picture_cb_cr.bus_address = dec_cont->info.out_pp_chroma.bus_address + ppu_cfg->chroma_offset;
                }
#ifdef SUPPORT_DEC400
                ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled) continue;
                  if (ppu_cfg->luma_size) {
                    if(tile_status_bus_address == 0) {
                      tile_status_virtual_address = p_dec_out->pictures[i].output_picture_y.virtual_address;
                      tile_status_bus_address = p_dec_out->pictures[i].output_picture_y.bus_address;
                    }
                  }
                }
                ppu_cfg = dec_cont->ppu_cfg;
                for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
                  if (!ppu_cfg->enabled || !ppu_cfg->dec400_enabled || ppu_cfg->rgb) continue;
                  PpFillDec400TblInfo(ppu_cfg,
                          tile_status_virtual_address,
                          tile_status_bus_address,
                          &p_dec_out->pictures[i].dec400_luma_table,
                          &p_dec_out->pictures[i].dec400_chroma_table);
                }
#endif
              }
              p_dec_out->pictures[0].output_picture_cr.virtual_address =
                dec_cont->info.out_chroma2.virtual_address;
              p_dec_out->pictures[0].output_picture_cr.bus_address =
                dec_cont->info.out_chroma2.bus_address;
            }
          }

          /* No slice output in case decoder + PP (no pipeline) */
          if(dec_cont->pp_instance != NULL &&
              dec_cont->pp_control.use_pipeline == 0) {
            /* output addresses */
            p_dec_out->pictures[0].output_picture_y.virtual_address = NULL;
            p_dec_out->pictures[0].output_picture_y.bus_address = 0;
            if(dec_cont->image.size_chroma) {
              p_dec_out->pictures[0].output_picture_cb_cr.virtual_address = NULL;
              p_dec_out->pictures[0].output_picture_cb_cr.bus_address = 0;
              p_dec_out->pictures[0].output_picture_cr.virtual_address = NULL;
              p_dec_out->pictures[0].output_picture_cr.bus_address = 0;
            }

            APITRACEDEBUG("%s","JpegDecDecode# Decoder + PP (Rotation/Flip), Slice ready\n");
            /* PP not in pipeline, continue do <==> while */
            dec_cont->info.no_slice_irq_for_user = 1;
          } else {
            APITRACEDEBUG("%s","JpegDecDecode# Slice ready\n");
            return DEC_SLICE_RDY;
          }
        } else {
          if(!dec_cont->b_mc &&
              RI_MC_DISABLED(dec_cont->ri_mc_enabled)) {
            /* discard : use jpeg process flow to process pjpeg. */
            current_pos = GET_ADDR_REG(dec_cont->jpeg_regs, HWIF_RLC_VLC_BASE);
            if (current_pos >= dec_cont->jpeg_hw_start_bus)
              hw_consumed = current_pos - dec_cont->jpeg_hw_start_bus;
            else
              hw_consumed = dec_cont->stream.strm_buff_size + current_pos -
                  dec_cont->jpeg_hw_start_bus;
            assert(hw_consumed);
            dec_cont->stream.p_curr_pos = dec_cont->stream.p_curr_pos + hw_consumed;
            dec_cont->stream.read_bits += hw_consumed * 8;
            if (dec_cont->stream.p_curr_pos >=
               (dec_cont->stream.p_start_of_buffer + dec_cont->stream.strm_buff_size))
              dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;

            /* eat EOI marker */
            for(i = 0;
                i <
                ((dec_cont->stream.stream_length -
                  (dec_cont->stream.read_bits / 8))); i++) {
              current_byte = JpegDecShowByte(&dec_cont->stream, i);
              if(current_byte == 0xFF) {
                current_byte = JpegDecShowByte(&dec_cont->stream, i+1);
                if(current_byte > 0x00  && current_byte != 0xD9) {
                  break;
                }
              }
            }

            dec_cont->stream.p_curr_pos += i;
            current_pos += i;
            dec_cont->stream.read_bits += i * 8;
            if (dec_cont->stream.p_curr_pos >=
               (dec_cont->stream.p_start_of_buffer +
                dec_cont->stream.strm_buff_size)) {
              dec_cont->stream.p_curr_pos -= dec_cont->stream.strm_buff_size;
              current_pos -= dec_cont->stream.strm_buff_size;
            }

            p_dec_out->output.strm_curr_pos = (u8 *) dec_cont->stream.p_curr_pos;
            p_dec_out->output.strm_curr_bus_address = current_pos;
            p_dec_out->output.data_left = p_dec_in->stream_length - (dec_cont->stream.read_bits >> 3);
          } else {
            /* PP not in pipeline, continue do <==> while */
            dec_cont->info.no_slice_irq_for_user = 0;
          }
        }

        if(dec_cont->info.no_slice_irq_for_user == 0) {
          /* Release HW */
          if (!dec_cont->b_mc && RI_MC_DISABLED(dec_cont->ri_mc_enabled)) {
            if (!dec_cont->vcmd_used)
              (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
            else
              (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
          }
          /* update asic_running */
          dec_cont->asic_running = 0;

          APITRACEDEBUG("%s","JpegDecDecode# FRAME READY\n");

          /* set image ready */
          dec_cont->image.image_ready = 1;
        }

        /* check PP status... and go */
        if(dec_cont->pp_instance != NULL &&
            !dec_cont->info.no_slice_irq_for_user) {
          /* set pp for stand alone */
          if(!dec_cont->pp_control.use_pipeline) {
            JpegDecPreparePp(dec_cont);

            APITRACEDEBUG("%s","INTERNAL: Set output write disabled\n");
            SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_OUT_DIS, 1);

            /* Enable pp */
            APITRACEDEBUG("%s","INTERNAL: Set Enable pp\n");
            dec_cont->PPRun(dec_cont->pp_instance,
                            &dec_cont->pp_control);

            dec_cont->pp_control.pp_status = DECPP_RUNNING;
            dec_cont->info.pipeline = 1;

            /* Flush regs to hw register */
            JpegFlushRegs(dec_cont);
          }

          /* End PP co-operation */
          if(dec_cont->pp_control.pp_status == DECPP_RUNNING) {
            APITRACEDEBUG("%s","JpegDecDecode# PP END CALL\n");
            dec_cont->PPEndCallback(dec_cont->pp_instance);
          }

          dec_cont->pp_control.pp_status = DECPP_PIC_READY;
        }

        /* output set */
        if(dec_cont->pp_instance == NULL &&
            !dec_cont->info.no_slice_irq_for_user) {
          /* output set */
          if (dec_cont->info.user_alloc_mem) {
            PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
            for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
              if (!ppu_cfg->enabled) continue;
              p_dec_out->pictures[i].output_picture_y.virtual_address =
                (u32*)((u8*)dec_cont->info.out_luma.virtual_address + ppu_cfg->luma_offset);
              p_dec_out->pictures[i].output_picture_y.bus_address =
                dec_cont->info.out_luma.bus_address + ppu_cfg->luma_offset;
            }
          }
          else {
            PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
            for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
              if (!ppu_cfg->enabled) continue;
              p_dec_out->pictures[i].output_picture_y.virtual_address =
              (u32*)((addr_t)dec_cont->info.out_pp_luma.virtual_address + ppu_cfg->luma_offset);
              p_dec_out->pictures[i].output_picture_y.bus_address = dec_cont->info.out_pp_luma.bus_address + ppu_cfg->luma_offset;
            }
          }

          /* if not grayscale */
          if(dec_cont->image.size_chroma || dec_cont->pp_enabled) {
            if (!dec_cont->pp_enabled || dec_cont->info.user_alloc_mem) {
              p_dec_out->pictures[0].output_picture_cb_cr.virtual_address =
                dec_cont->info.out_chroma.virtual_address;
              p_dec_out->pictures[0].output_picture_cb_cr.bus_address =
                dec_cont->info.out_chroma.bus_address;
            }
            else {
              PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
              for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
                if (!ppu_cfg->enabled) continue;
                p_dec_out->pictures[i].output_picture_cb_cr.virtual_address =
                (u32*)((addr_t)dec_cont->info.out_pp_chroma.virtual_address + ppu_cfg->chroma_offset);
                p_dec_out->pictures[i].output_picture_cb_cr.bus_address = dec_cont->info.out_pp_chroma.bus_address + ppu_cfg->chroma_offset;
              }
            }

            p_dec_out->pictures[0].output_picture_cr.virtual_address =
              dec_cont->info.out_chroma2.virtual_address;
            p_dec_out->pictures[0].output_picture_cr.bus_address =
              dec_cont->info.out_chroma2.bus_address;
          }
          // if(dec_cont->pp_enabled)
          {
            PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
            p_dec_out->bit_depth = dec_cont->frame.P;
            for (i = 0; i < DEC_MAX_OUT_COUNT; i++, ppu_cfg++) {
              if (!ppu_cfg->enabled) continue;
              if (!p_dec_in->dec_image_type) {
                if (dec_cont->ppu_cfg[i].crop2.enabled) {
                  p_dec_out->pictures[i].output_width = NEXT_MULTIPLE(dec_cont->ppu_cfg[i].crop2.width, ALIGN(ppu_cfg->align));
                  p_dec_out->pictures[i].output_height = dec_cont->ppu_cfg[i].crop2.height;
                  p_dec_out->pictures[i].display_width = dec_cont->ppu_cfg[i].crop2.width;
                  p_dec_out->pictures[i].display_height = dec_cont->ppu_cfg[i].crop2.height;
                } else {
                  p_dec_out->pictures[i].output_width = NEXT_MULTIPLE(dec_cont->ppu_cfg[i].scale.width, ALIGN(ppu_cfg->align));
                  p_dec_out->pictures[i].output_height = dec_cont->ppu_cfg[i].scale.height;
                  p_dec_out->pictures[i].display_width = dec_cont->ppu_cfg[i].scale.enabled ? dec_cont->ppu_cfg[i].scale.width : dec_cont->frame.X;
                  p_dec_out->pictures[i].display_height = dec_cont->ppu_cfg[i].scale.height;
                }
                p_dec_out->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
                p_dec_out->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
                p_dec_out->pictures[i].output_format = TransUnitConfig2Format(ppu_cfg);
              } else {
                if (dec_cont->ppu_cfg[i].crop2.enabled) {
                  p_dec_out->pictures[i].output_width_thumb = NEXT_MULTIPLE(dec_cont->ppu_cfg[i].crop2.width, ALIGN(ppu_cfg->align));;
                  p_dec_out->pictures[i].output_height_thumb = dec_cont->ppu_cfg[i].crop2.height;
                  p_dec_out->pictures[i].display_width_thumb = dec_cont->ppu_cfg[i].crop2.width;
                  p_dec_out->pictures[i].display_height_thumb = dec_cont->ppu_cfg[i].crop2.height;
                } else {
                  p_dec_out->pictures[i].output_width_thumb = NEXT_MULTIPLE(dec_cont->ppu_cfg[i].scale.width, ALIGN(ppu_cfg->align));;
                  p_dec_out->pictures[i].output_height_thumb = dec_cont->ppu_cfg[i].scale.height;
                  p_dec_out->pictures[i].display_width_thumb = dec_cont->ppu_cfg[i].scale.enabled ? dec_cont->ppu_cfg[i].scale.width : dec_cont->frame.X;
                  p_dec_out->pictures[i].display_height_thumb = dec_cont->ppu_cfg[i].scale.height;
                }
                p_dec_out->pictures[i].pic_stride = dec_cont->ppu_cfg[i].ystride;
                p_dec_out->pictures[i].pic_stride_ch = dec_cont->ppu_cfg[i].cstride;
                p_dec_out->pictures[i].output_format = TransUnitConfig2Format(ppu_cfg);
              }
            }
          }
#ifdef SUPPORT_DEC400
          PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
          for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
            if (!ppu_cfg->enabled) continue;
            if (ppu_cfg->luma_size) {
              if(tile_status_bus_address == 0) {
                tile_status_virtual_address = p_dec_out->pictures[i].output_picture_y.virtual_address;
                tile_status_bus_address = p_dec_out->pictures[i].output_picture_y.bus_address;
              }
            }
          }
          ppu_cfg = dec_cont->ppu_cfg;
          for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
            if (!ppu_cfg->enabled || !ppu_cfg->dec400_enabled || ppu_cfg->rgb) continue;
            PpFillDec400TblInfo(ppu_cfg,
                          tile_status_virtual_address,
                          tile_status_bus_address,
                          &p_dec_out->pictures[i].dec400_luma_table,
                          &p_dec_out->pictures[i].dec400_chroma_table);
          }
#endif
          if (dec_cont->b_mc ||
             (p_dec_in->picture_buffer_y.virtual_address == NULL &&
             ((dec_cont->ri_mc_enabled == RI_MC_ENA &&
             dec_cont->ri_index == dec_cont->last_ri_index) ||
             dec_cont->ri_mc_enabled != RI_MC_ENA)) ||
             dec_cont->info.user_alloc_mem) {
            p_dec_out->cycles_per_mb = JpegCycleCount(dec_cont);
            PushOutputPic(&dec_cont->fb_list, p_dec_out, &(dec_cont->p_image_info));
          }
        }

#ifdef JPEGDEC_ASIC_TRACE
        {
          APITRACEDEBUG("%s","\nJpeg_dec_decode# TEST\n");
          PrintJPEGReg(dec_cont->jpeg_regs);
        }
#endif /* #ifdef JPEGDEC_ASIC_TRACE */
      } else if(dwlret == DWL_HW_WAIT_TIMEOUT) {
        APITRACEERR("%s","SCAN: DWL HW TIMEOUT\n");

        /* Release HW */
        if (dec_cont->vcmd_used)
          (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
        else
          (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);

        /* update asic_running */
        dec_cont->asic_running = 0;

        ret_code = DEC_HW_TIMEOUT;
        goto end;
      } else if(dwlret == DWL_HW_WAIT_ERROR) {
        APITRACEERR("%s","SCAN: DWL HW ERROR\n");

        /* Release HW */
        if (dec_cont->vcmd_used)
          (void) DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
        else
          (void) DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);

        /* update asic_running */
        dec_cont->asic_running = 0;

        ret_code = DEC_SYSTEM_ERROR;
        goto end;
      }
      dec_cont->ri_index++;
    } while(!dec_cont->image.image_ready ||
              (RI_MC_ENABLED(dec_cont->ri_mc_enabled) &&
               dec_cont->ri_index <= dec_cont->last_ri_index));
    //dec_cont->n_cores_available = 1;
  }

  if (RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
    sem_wait(&dec_cont->sem_ri_mc_done);
    dwlret = DWL_HW_WAIT_OK;
    asic_status = DEC_HW_IRQ_RDY;
  }

  if(dec_cont->image.image_ready) {
    APITRACE("%s","JpegDecDecode# IMAGE READY\n");
    APITRACE("%s","JpegDecDecode# OK\n");

    /* reset image status */
    dec_cont->image.image_ready = 0;
    dec_cont->image.header_ready = 0;

#ifdef CASE_INFO_STAT
    JpegCaseInfoCollect(dec_cont, &case_info);
#endif
    /* reset */
    JpegDecClearStructs(dec_cont, 1);

    return (DEC_PIC_RDY);
  } else {
    APITRACEERR("%s","JpegDecDecode# ERROR\n");
    ret_code = DEC_ERROR;
  }

end:
  p_dec_out->output.data_left = 0;
  p_dec_out->output.strm_curr_pos = (u8 *)p_dec_in->stream + p_dec_in->stream_length;
  InputQueueReturnBuffer(dec_cont->pp_buffer_queue,
                         DWL_GET_DEVMEM_ADDR(dec_cont->asic_buff.pp_luma_buffer));
  return (ret_code);
#undef JPG_FRM
#undef PTR_INFO
}

/*------------------------------------------------------------------------------

    Function name: JpegDecPreparePp

    Functional description:
        Setup PP interface

    Input:
        container

    Return values:
        void

------------------------------------------------------------------------------*/
static void JpegDecPreparePp(JpegDecContainer * dec_cont) {
  dec_cont->pp_control.pic_struct = 0;
  dec_cont->pp_control.top_field = 0;

  {
    u32 tmp = GetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_OUT_ENDIAN);

    dec_cont->pp_control.little_endian =
      (tmp == DEC_X170_LITTLE_ENDIAN) ? 1 : 0;
  }
  dec_cont->pp_control.word_swap = GetDecRegister(dec_cont->jpeg_regs,
                                        HWIF_DEC_OUTSWAP32_E) ? 1
                                        : 0;

  /* pipeline */
  if(dec_cont->pp_control.use_pipeline) {
    /* luma */
    dec_cont->pp_control.input_bus_luma = 0;
    /* chroma */
    dec_cont->pp_control.input_bus_chroma = 0;
  } else {
    /* luma */
    dec_cont->pp_control.input_bus_luma =
      dec_cont->asic_buff.out_luma_buffer.bus_address;
    /* chroma */
    dec_cont->pp_control.input_bus_chroma =
      dec_cont->asic_buff.out_chroma_buffer.bus_address;
  }

  /* dimensions */
  dec_cont->pp_control.inwidth =
    dec_cont->pp_control.cropped_w = dec_cont->info.X;

  dec_cont->pp_control.inheight =
    dec_cont->pp_control.cropped_h = dec_cont->info.Y;
}

/*------------------------------------------------------------------------------
    5.8. Function name   : jpegRegisterPP
         Description     : Called internally by PP to enable the pipeline
         Return type     : i32 - return 0 for success or a negative error code
         Argument        : const void * dec_inst - decoder instance
         Argument        : const void  *pp_inst - post-processor instance
         Argument        : (*PPRun)(const void *) - decoder calls this to start PP
         Argument        : void (*PPEndCallback)(const void *) - decoder calls this
                           to notify PP that a picture was done.
------------------------------------------------------------------------------*/
i32 jpegRegisterPP(const void *dec_inst, const void *pp_inst,
                   void (*PPRun) (const void *, const DecPpInterface *),
                   void (*PPEndCallback) (const void *),
                   void (*PPConfigQuery) (const void *, DecPpQuery *)) {
  JpegDecContainer *dec_cont;

  dec_cont = (JpegDecContainer *) dec_inst;

  if(dec_inst == NULL || dec_cont->pp_instance != NULL ||
      pp_inst == NULL || PPRun == NULL || PPEndCallback == NULL)
    return -1;

  if(dec_cont->asic_running)
    return -2;

  dec_cont->pp_instance = pp_inst;
  dec_cont->PPEndCallback = PPEndCallback;
  dec_cont->PPRun = PPRun;
  dec_cont->PPConfigQuery = PPConfigQuery;

  return 0;
}

/*------------------------------------------------------------------------------
    5.9. Function name   : jpegUnregisterPP
         Description     : Called internally by PP to disable the pipeline
         Return type     : i32 - return 0 for success or a negative error code
         Argument        : const void * dec_inst - decoder instance
         Argument        : const void  *pp_inst - post-processor instance
------------------------------------------------------------------------------*/
i32 jpegUnregisterPP(const void *dec_inst, const void *pp_inst) {
  JpegDecContainer *dec_cont;

  dec_cont = (JpegDecContainer *) dec_inst;

  ASSERT(dec_inst != NULL && pp_inst == dec_cont->pp_instance);

  if(dec_inst == NULL || pp_inst != dec_cont->pp_instance)
    return -1;

  if(dec_cont->asic_running)
    return -2;

  dec_cont->pp_instance = NULL;
  dec_cont->PPEndCallback = NULL;
  dec_cont->PPRun = NULL;

  return 0;
}

enum DecRet JpegDecSetInfo(JpegDecInst dec_inst,
                            struct JpegDecConfig *dec_cfg) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)dec_inst;
  PpUnitConfig *ppu_cfg = &dec_cfg->ppu_config[0];
  const struct DecHwFeatures *hw_feature = NULL;
  u32 i = 0;
  u32 shaper_alignment = 0;
  u32 pixel_width = (dec_cont->frame.P == 8 ? 8 : 12);

  switch(dec_cfg->chroma_format) {
    case DEC_OUT_FRM_YUV420SP: dec_cont->pp_chroma_format = PP_CHROMA_420; break;
    case DEC_OUT_FRM_YUV422SP: dec_cont->pp_chroma_format = PP_CHROMA_422; break;
    case DEC_OUT_FRM_YUV411SP: dec_cont->pp_chroma_format = PP_CHROMA_411; break;
    case DEC_OUT_FRM_YUV440: dec_cont->pp_chroma_format = PP_CHROMA_440; break;
    case DEC_OUT_FRM_YUV444SP: dec_cont->pp_chroma_format = PP_CHROMA_444; break;
    default: dec_cont->pp_chroma_format = PP_CHROMA_400; break;
  }

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  if (pixel_width == 12)
    pixel_width = 10;

  shaper_alignment = (u32)hw_feature->shaper_alignment;
  /* ref aligment */
  dec_cont->align = dec_cfg->align;
  /* ppu alignment */
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    dec_cfg->ppu_config[i].align = dec_cfg->align;
    if ((u32)dec_cfg->ppu_config[i].align < shaper_alignment) {
      if (dec_cfg->ppu_config[i].dec400_enabled) {
        dec_cfg->ppu_config[i].align = shaper_alignment;
      } else {
        dec_cfg->ppu_config[i].shaper_no_pad = 1;
      }
    }
  }

  dec_cont->dec_image_type = dec_cfg->dec_image_type;
  PpUnitSetIntConfig(dec_cont->ppu_cfg, ppu_cfg, pixel_width , 1, dec_cont->pp_chroma_format == PP_CHROMA_400);
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    if (dec_cont->ppu_cfg[i].lanczos_table.virtual_address == NULL) {
      u32 size = LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16) * dec_cont->n_cores;
      dec_cont->ppu_cfg[i].lanczos_table.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_CPU;
      i32 ret = DWLMallocLinear(dec_cont->dwl, size, &dec_cont->ppu_cfg[i].lanczos_table);
      if (ret != 0)
        return(DEC_MEMFAIL);
    }
  }
  /* Allocate buffer for ddr_low_latency model */
  if (dec_cont->strm_status_in_buffer == 1){
    dec_cont->strm_status.mem_type = DWL_MEM_TYPE_DMA_HOST_TO_DEVICE | DWL_MEM_TYPE_VPU_WORKING;
    if(DWLMallocLinear(dec_cont->dwl, 16 * 4, &dec_cont->strm_status));
  }
  if (CheckPpUnitConfig(hw_feature, 0, 0, 0, pixel_width, dec_cont->pp_chroma_format, dec_cont->ppu_cfg))
    return DEC_PARAM_ERROR;
  memcpy(dec_cont->delogo_params, dec_cfg->delogo_params, sizeof(dec_cont->delogo_params));
  if (CheckDelogo(dec_cont->delogo_params, 8, 8))
    return DEC_PARAM_ERROR;
  return(DEC_OK);
}

enum DecRet JpegDecSetInfo_INTERNAL(JpegDecContainer *dec_cont) {
  u32 pic_width = (dec_cont->frame.X + 1) & ~0x1;
  u32 pic_height = (dec_cont->frame.Y + 1) & ~0x1;
  u32 pixel_width = (dec_cont->frame.P == 8 ? 8 : 12);
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);
  if (pixel_width == 12)
    pixel_width = 10;

  if (CheckPpUnitConfig(hw_feature, pic_width, pic_height, 0, pixel_width, dec_cont->pp_chroma_format, dec_cont->ppu_cfg))
    return DEC_PARAM_ERROR;

  /* Check whether pp height satisfies restart interval based multicore. */
  if (RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
    u32 i = 0;
    u32 ri_height = dec_cont->frame.num_mcu_rows_in_interval *
                       dec_cont->frame.mcu_height;
    PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
    //u32 first_ri_index, last_ri_index;

    dec_cont->first_ri_index = (u32)-1;
    dec_cont->last_ri_index = 0;
    for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
      u32 first_slice_height, last_slice_height;
      if (!ppu_cfg->enabled) continue;

      first_slice_height = ri_height - (ppu_cfg->crop.y % ri_height);
      last_slice_height = (ppu_cfg->crop.y + ppu_cfg->crop.height) %
                           ri_height;
      if ((first_slice_height * ppu_cfg->scale.height % ppu_cfg->crop.height) ||
          (ri_height * ppu_cfg->scale.height % ppu_cfg->crop.height) ||
          (last_slice_height * ppu_cfg->scale.height % ppu_cfg->crop.height)) {
        dec_cont->ri_mc_enabled = RI_MC_DISABLED_BY_PP;
        break;
      }

      dec_cont->start_ri_index[i] = ppu_cfg->crop.y / ri_height;
      dec_cont->end_ri_index[i] = (ppu_cfg->crop.y + ppu_cfg->crop.height - 1) /
                                   ri_height;

      if (dec_cont->start_ri_index[i] < dec_cont->first_ri_index)
        dec_cont->first_ri_index = dec_cont->start_ri_index[i];
      if (dec_cont->end_ri_index[i] > dec_cont->last_ri_index)
        dec_cont->last_ri_index = dec_cont->end_ri_index[i];
    }
  }

  return (DEC_OK);
}

static u32 InitList(FrameBufferList *fb_list) {
  (void) DWLmemset(fb_list, 0, sizeof(*fb_list));

  sem_init(&fb_list->out_count_sem, 0, 0);
  pthread_mutex_init(&fb_list->out_count_mutex, NULL);

  pthread_mutex_init(&fb_list->ref_count_mutex, NULL );

  /* this CV is used to signal the HW has finished processing a picture
   * that is needed for output ( FB_OUTPUT | FB_HW_ONGOING )
   */
  pthread_cond_init(&fb_list->hw_rdy_cv, NULL);

  fb_list->b_initialized = 1;
  return 0;
}

static void ReleaseList(FrameBufferList *fb_list) {
  if (!fb_list->b_initialized)
    return;

  fb_list->b_initialized = 0;

  pthread_mutex_destroy(&fb_list->ref_count_mutex);

  pthread_mutex_destroy(&fb_list->out_count_mutex);
  pthread_cond_destroy(&fb_list->hw_rdy_cv);

  sem_destroy(&fb_list->out_count_sem);
}


static void ClearHWOutput(FrameBufferList *fb_list, u32 id, u32 type) {
  u32 *bs = fb_list->fb_stat + id;

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  ASSERT(*bs & (FB_HW_ONGOING));

  *bs &= ~type;

  if ((*bs & FB_HW_ONGOING) == 0) {
    /* signal that this buffer is done by HW */
    pthread_cond_signal(&fb_list->hw_rdy_cv);
  }

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

static void MarkHWOutput(FrameBufferList *fb_list, u32 id, u32 type) {

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  ASSERT( fb_list->fb_stat[id] ^ type );

  fb_list->fb_stat[id] |= type;

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

static void PushOutputPic(FrameBufferList *fb_list, const JpegDecOutput *pic, const JpegDecImageInfo *info) {
  if (pic != NULL && info != NULL) {
    pthread_mutex_lock(&fb_list->out_count_mutex);

    while(fb_list->num_out == MAX_FRAME_NUMBER) {
      /* make sure we do not overflow the output */
      /* pthread_cond_signal(&fb_list->out_empty_cv); */
      pthread_mutex_unlock(&fb_list->out_count_mutex);
      sched_yield();
      pthread_mutex_lock(&fb_list->out_count_mutex);
    }

    /* push to tail */
    if (fb_list->wr_id >= MAX_FRAME_NUMBER)
      fb_list->wr_id = 0;

    fb_list->out_fifo[fb_list->wr_id].pic = *pic;
    fb_list->out_fifo[fb_list->wr_id].info = *info;
    fb_list->out_fifo[fb_list->wr_id].mem_idx = fb_list->wr_id;
    fb_list->num_out++;
    fb_list->wr_id++;

    ASSERT(fb_list->num_out <= MAX_FRAME_NUMBER);

    pthread_mutex_unlock(&fb_list->out_count_mutex);
  } else {
    fb_list->end_of_stream = 1;
  }
  sem_post(&fb_list->out_count_sem);
}

static u32 JpegCycleCount(JpegDecContainer * dec_cont) {
  u32 cycles = 0;
  u32 mbs;
#ifdef FPGA_PERF_AND_BW
  u64 pic_size = NEXT_MULTIPLE(dec_cont->info.X, 16) * NEXT_MULTIPLE(dec_cont->info.Y, 16);
  u32 bit_depth = dec_cont->frame.P == 8? 8 : 12;
  DecPerfInfoCount(dec_cont->core_id, &dec_cont->perf_info, pic_size, bit_depth);
#endif
  mbs = (NEXT_MULTIPLE(dec_cont->info.X, 16) *
             NEXT_MULTIPLE(dec_cont->info.Y, 16)) >> 8;

  if (mbs)
    cycles = GetDecRegister(dec_cont->jpeg_regs, HWIF_PERF_CYCLE_COUNT) / mbs;

  return cycles;
}

static void SetAbortStatusInList(FrameBufferList *fb_list) {
  if(fb_list == NULL || !fb_list->b_initialized)
    return;

  pthread_mutex_lock(&fb_list->ref_count_mutex);
  fb_list->abort = 1;
  pthread_mutex_unlock(&fb_list->ref_count_mutex);
  sem_post(&fb_list->out_count_sem);
}

static void ClearAbortStatusInList(FrameBufferList *fb_list) {
  if(fb_list == NULL || !fb_list->b_initialized)
    return;

  pthread_mutex_lock(&fb_list->ref_count_mutex);
  fb_list->abort = 0;
  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

static void ResetOutFifoInList(FrameBufferList *fb_list) {
  (void)DWLmemset(fb_list->out_fifo, 0, MAX_FRAME_NUMBER * sizeof(struct OutElement_));
  fb_list->wr_id = 0;
  fb_list->rd_id = 0;
  fb_list->num_out = 0;
}


static u32 PeekOutputPic(FrameBufferList *fb_list, JpegDecOutput *pic, JpegDecImageInfo *info) {
  u32 mem_idx;
  JpegDecOutput *out;
  JpegDecImageInfo *info_tmp;
#ifndef GET_OUTPUT_BUFFER_NON_BLOCK
#ifdef _HAVE_PTHREAD_H
  sem_wait(&fb_list->out_count_sem);
#else
  if(sem_wait(&fb_list->out_count_sem)) return 0;
#endif
#endif
  if (fb_list->abort)
    return ABORT_MARKER;

  pthread_mutex_lock(&fb_list->out_count_mutex);
  if (!fb_list->num_out) {
    if (fb_list->end_of_stream) {
      pthread_mutex_unlock(&fb_list->out_count_mutex);
      return 2;
    } else {
      pthread_mutex_unlock(&fb_list->out_count_mutex);
      return 0;
    }
  }
  pthread_mutex_unlock(&fb_list->out_count_mutex);

  out = &fb_list->out_fifo[fb_list->rd_id].pic;
  info_tmp = &fb_list->out_fifo[fb_list->rd_id].info;
  mem_idx = fb_list->out_fifo[fb_list->rd_id].mem_idx;

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  while((fb_list->fb_stat[mem_idx] & FB_HW_ONGOING) != 0)
    pthread_cond_wait(&fb_list->hw_rdy_cv, &fb_list->ref_count_mutex);

  pthread_mutex_unlock(&fb_list->ref_count_mutex);

  /* pop from head */
  (void)DWLmemcpy(pic, out, sizeof(JpegDecOutput));
  (void)DWLmemcpy(info, info_tmp, sizeof(JpegDecImageInfo));

  pthread_mutex_lock(&fb_list->out_count_mutex);

  fb_list->num_out--;

  /* go to next output */
  fb_list->rd_id++;
  if (fb_list->rd_id >= MAX_FRAME_NUMBER)
    fb_list->rd_id = 0;

  pthread_mutex_unlock(&fb_list->out_count_mutex);

  return 1;
}

enum DecRet JpegDecNextPicture(JpegDecInst dec_inst,
                              JpegDecOutput * output,
                              JpegDecImageInfo *info) {
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  u32 ret;

  if(dec_inst == NULL || output == NULL) {
    APITRACEERR("%s","JpegDecNextPicture# ERROR: dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  if((ret = PeekOutputPic(&dec_cont->fb_list, output, info))) {
    if (ret == 3) {
      APITRACE("%s","JpegDecNextPicture# DEC_ABORTED\n");
      return (DEC_ABORTED);
    }
    if(ret == 2) {
      APITRACE("%s","JpegDecNextPicture# DEC_END_OF_STREAM\n");
      return (DEC_END_OF_STREAM);
    }
    if(ret == 1) {
     APITRACE("%s","JpegDecNextPicture# JPEGDEC_PIC_RDY\n");
      return (DEC_PIC_RDY);
    }
    if (ret == 0) {
      APITRACE("%s","JpegDecNextPicture# DEC_OK\n");
      return (DEC_OK);
    }
  }
  return (DEC_OK);
}

enum DecRet JpegDecPictureConsumed(JpegDecInst dec_inst, JpegDecOutput * output) {
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  u32 i;
  DWLMemAddr output_picture = (DWLMemAddr)NULL;
  PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
  APITRACE("%s","JpegDecPictureConsumed#\n");

  if(dec_inst == NULL || output == NULL) {
    APITRACEERR("%s","JpegDecPictureConsumed# ERROR: dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
    if (!ppu_cfg->enabled)
      continue;
    else {
#ifndef MEM_ONLY_DEV_CHECK
      output_picture = (DWLMemAddr)output->pictures[i].output_picture_y.virtual_address;
#else
      output_picture = (DWLMemAddr)output->pictures[i].output_picture_y.bus_address;
#endif
      break;
    }
  }
  InputQueueReturnBuffer(dec_cont->pp_buffer_queue, output_picture);
  return (DEC_OK);
}

enum DecRet JpegDecEndOfStream(JpegDecInst dec_inst) {
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  u32 count = 0;

  if(dec_inst == NULL) {
    APITRACEERR("%s","JpegDecNextPicture# ERROR: dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  if(dec_cont->vcmd_used){
#if 0
    DWLReserveCmdBuf(dec_cont->dwl, DWL_CLIENT_TYPE_JPEG_DEC,
                      dec_cont->info.X, dec_cont->info.Y,
                      &dec_cont->cmd_buf_id);
    DWLReleaseCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
#else
    DWLWaitCmdbufsDone(dec_cont->dwl, dec_inst);
#endif
  } else {
    /* Check all Core in idle state */
    for(count = 0; count < dec_cont->n_cores_available; count++) {
      while (dec_cont->dec_status[count] == DEC_RUNNING)
        sched_yield();
    }
  }

  /* wake-up output thread */
  PushOutputPic(&dec_cont->fb_list, NULL, NULL);
  return (DEC_OK);
}

static void JpegMCHwRdyCallback(void *args, i32 core_id) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)args;
  JpegHwRdyCallbackArg info;

  const void *dwl;

  u32 type = FB_HW_ONGOING;

  ASSERT(dec_cont != NULL);
  ASSERT(core_id < MAX_ASIC_CORES || (dec_cont->vcmd_used && core_id < MAX_MC_CB_ENTRIES));

  /* take a copy of the args as after we release the HW they
   * can be overwritten.
   */
  dwl = dec_cont->dwl;
  info = dec_cont->hw_rdy_callback_arg[core_id];

  /* React to the HW return value */

  /* clear IRQ status reg and release HW core */
  if (!dec_cont->vcmd_used) {
    DWLDisableHw(dwl, core_id, 0x04, 0);
    dec_cont->dec_status[info.core_id] = DEC_IDLE;
    DWLReleaseHw(dwl, info.core_id);
  } else {
    DWLReleaseCmdBuf(dwl, info.core_id);
  }
  if(dec_cont->stream_consumed_callback.fn)
    dec_cont->stream_consumed_callback.fn((u8*)info.stream,
                                          (void*)info.p_user_data);
  ClearHWOutput(&dec_cont->fb_list, info.out_id, type);

}

static void JpegMCSetHwRdyCallback(JpegDecInst dec_inst) {
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  u32 type = FB_HW_ONGOING;
  JpegHwRdyCallbackArg *arg = &dec_cont->hw_rdy_callback_arg[dec_cont->core_id];
  i32 core_id = dec_cont->core_id;

  if (dec_cont->vcmd_used) {
    arg = &dec_cont->hw_rdy_callback_arg[dec_cont->cmd_buf_id];
    core_id = dec_cont->cmd_buf_id;
  }
  arg->core_id = core_id;
  arg->stream = dec_cont->stream_consumed_callback.p_strm_buff;
  arg->p_user_data = dec_cont->stream_consumed_callback.p_user_data;
  arg->out_id = dec_cont->fb_list.wr_id;

  DWLSetIRQCallback(dec_cont->dwl, core_id, JpegMCHwRdyCallback,
                    dec_cont);

  MarkHWOutput(&dec_cont->fb_list, arg->out_id, type);
}

static void JpegRiMCHwRdyCallback(void *args, i32 core_id) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)args;
  JpegHwRdyCallbackArg info;
  const void *dwl;

  ASSERT(dec_cont != NULL);
  ASSERT(core_id < MAX_ASIC_CORES);

  /* take a copy of the args as after we release the HW they
   * can be overwritten.
   */
  dwl = dec_cont->dwl;
  info = dec_cont->hw_rdy_callback_arg[core_id];
  dec_cont->ri_running_cores--;

  /* React to the HW return value */
#if 0
  u32 perf_cycles;
  perf_cycles = DWLReadReg(dwl, core_id, 63 * 4);
  printf("Core[%d] cycles %d/MB\n", core_id,
          perf_cycles /
          (dec_cont->info.X * dec_cont->frame.mcu_height *
           dec_cont->frame.num_mcu_rows_in_interval / 256));
#endif

  /* clear IRQ status reg and release HW core */
  DWLDisableHw(dwl, core_id, 0x04, 0);
  DWLReleaseHw(dwl, info.core_id);

  if (dec_cont->ri_index > dec_cont->last_ri_index &&
      dec_cont->ri_running_cores == 0) {
    sem_post(&dec_cont->sem_ri_mc_done);
  }
  dec_cont->dec_status[info.core_id] = DEC_IDLE;
}

static void JpegRiMCSetHwRdyCallback(JpegDecInst dec_inst) {
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  JpegHwRdyCallbackArg *arg = &dec_cont->hw_rdy_callback_arg[dec_cont->core_id];

  arg->core_id = dec_cont->core_id;

  DWLSetIRQCallback(dec_cont->dwl, dec_cont->core_id, JpegRiMCHwRdyCallback,
                    dec_cont);
}

/* TODO: consider case with missing restart intervals. */
static u32 JpegParseRST(JpegDecInst dec_inst, u8 *img_buf, u32 img_len,
                             u8 **ri_array) {
  u8 *p = img_buf;
  u32 rst_markers = 0;
  u32 last_rst, i;
  while (p < img_buf + img_len) {
    if (p[0] == 0xFF && p[1] >= 0xD0 && p[1] <= 0xD7) {
      if (!rst_markers) {
        rst_markers++;
      } else {
        /* missing restart intervals */
        u32 missing_rst_count = (p[1] - 0xD7 + 8 - last_rst - 1) % 8;
        for (i = 0; i < missing_rst_count; i++)
          ri_array[++rst_markers] = NULL;
        rst_markers++;
      }
      last_rst = p[1] - 0xD7;
      ri_array[rst_markers]  = p + 2;
#if 0
      printf("RST%d @ offset %d: %02X%02X\n", p[1] - 0xD0,
            (u32)(p - img_buf), p[0], p[1]);
#endif
    }
    p++;
  }
  return (rst_markers);

  rst_markers++;
  return (rst_markers);
}

void JpegSetExternalBufferInfo(JpegDecInst dec_inst) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)dec_inst;
  u32 ext_buffer_size = 0;
  u32 pp_width = 0, pp_height_luma = 0,
      pp_stride = 0, pp_buff_size = 0;

  u32 buffers = 1;

  if (dec_cont->pp_enabled) {
    PpUnitIntConfig *ppu_cfg = dec_cont->ppu_cfg;
    if (dec_cont->info.slice_mb_set_value) {
      if (ppu_cfg->tiled_e) {
        pp_width = dec_cont->info.X >> dec_cont->dscale_shift_x;
        pp_height_luma = NEXT_MULTIPLE(dec_cont->info.slice_mb_set_value * 16 >> dec_cont->dscale_shift_y, 4) / 4;
        pp_stride = NEXT_MULTIPLE(4 * pp_width, ALIGN(ppu_cfg->align));
        pp_buff_size = pp_stride * pp_height_luma;
      } else {
        pp_width = dec_cont->info.X >> dec_cont->dscale_shift_x;
        pp_height_luma = dec_cont->info.slice_mb_set_value * 16 >> dec_cont->dscale_shift_y;
        pp_stride = NEXT_MULTIPLE(pp_width, ALIGN(ppu_cfg->align));
        pp_buff_size = pp_stride * pp_height_luma;
      }
      dec_cont->ppu_cfg[0].luma_offset = 0;
      dec_cont->ppu_cfg[0].chroma_offset = pp_buff_size;
    } else {
      ext_buffer_size = CalcPpUnitBufferSize(ppu_cfg, 0);
    }
  }

  dec_cont->tot_buffers = dec_cont->buf_num =  buffers;
  dec_cont->pre_buf_size = dec_cont->next_buf_size;
  dec_cont->next_buf_size = ext_buffer_size;
}

enum DecRet JpegDecGetBufferInfo(JpegDecInst dec_inst, struct DecBufferInfo *mem_info) {

  JpegDecContainer  * dec_cont = (JpegDecContainer *)dec_inst;
  u32 i;

  if(dec_cont == NULL || mem_info == NULL) {
    return DEC_PARAM_ERROR;
  }

  (void) DWLmemset(mem_info, 0, sizeof(struct DecBufferInfo));

  if (dec_cont->pp_enabled) {
    for (i = 0; i < DEC_MAX_OUT_COUNT; i++) {
      if (!dec_cont->ppu_cfg[i].enabled) continue;
      mem_info->ystride[i] = dec_cont->ppu_cfg[i].ystride;
      mem_info->cstride[i] = dec_cont->ppu_cfg[i].cstride;
    }
  }

  dec_cont->frame.X = dec_cont->dec_image_type ?
                      dec_cont->p_image_info.display_width_thumb :
                      dec_cont->p_image_info.display_width;
  dec_cont->frame.Y = dec_cont->dec_image_type ?
                      dec_cont->p_image_info.display_height_thumb :
                      dec_cont->p_image_info.display_height;

  u32 pic_width = (dec_cont->frame.X + 1) & ~0x1;
  u32 pic_height = (dec_cont->frame.Y + 1) & ~0x1;
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);
  if (CheckPpUnitConfig(hw_feature, pic_width, pic_height, 0, (dec_cont->frame.P == 12 ? 12 : 8),
                        dec_cont->pp_chroma_format, dec_cont->ppu_cfg))
    return DEC_PARAM_ERROR;

  JpegSetExternalBufferInfo(dec_cont);

  struct DWLLinearMem empty = {0, 0, 0};

  if(dec_cont == NULL || mem_info == NULL) {
    return DEC_PARAM_ERROR;
  }

  if(dec_cont->buf_to_free == NULL && dec_cont->next_buf_size == 0) {
    /* External reference buffer: release done. */
    mem_info->buf_to_free = empty;
    mem_info->next_buf_size = dec_cont->next_buf_size;
    mem_info->buf_num = dec_cont->buf_num;
    return DEC_OK;
  }

  if(dec_cont->buf_to_free) {
    mem_info->buf_to_free = *dec_cont->buf_to_free;
    dec_cont->buf_to_free->virtual_address = NULL;
    dec_cont->buf_to_free = NULL;
  } else
    mem_info->buf_to_free = empty;

  /* Instant buffer mode: if new image size is bigger than previous, reallocate buffer. */
  if (dec_cont->info.user_alloc_mem && dec_cont->pre_buf_size != 0 &&
      dec_cont->next_buf_size > dec_cont->pre_buf_size) {
    mem_info->buf_to_free = dec_cont->info.given_out_luma;
    mem_info->next_buf_size = dec_cont->next_buf_size;
    mem_info->buf_num = dec_cont->buf_num;
    return DEC_WAITING_FOR_BUFFER;
  }

  mem_info->next_buf_size = dec_cont->next_buf_size;
  mem_info->buf_num = dec_cont->buf_num;

  ASSERT((mem_info->buf_num && mem_info->next_buf_size) ||
         (mem_info->buf_to_free.virtual_address != NULL));

  return DEC_OK;
}

enum DecRet JpegDecAddBuffer(JpegDecInst dec_inst, struct DWLLinearMem *info) {
  JpegDecContainer *dec_cont = (JpegDecContainer *)dec_inst;
  enum DecRet dec_ret = DEC_OK;

  if(dec_inst == NULL || info == NULL ||
      X170_CHECK_VIRTUAL_ADDRESS(info->virtual_address) ||
      X170_CHECK_BUS_ADDRESS_AGLINED(info->bus_address) ||
      info->size < dec_cont->next_buf_size) {
    return DEC_PARAM_ERROR;
  }

  dec_cont->n_ext_buf_size = info->size;
  if (!dec_cont->realloc_buffer) {
    dec_cont->ext_buffers[dec_cont->ext_buffer_num] = *info;
    dec_cont->ext_buffer_num++;

    InputQueueAddBuffer(dec_cont->pp_buffer_queue, info);
  } else {
    dec_cont->ext_buffers[dec_cont->buffer_index] = *info;
    InputQueueUpdateBuffer(dec_cont->pp_buffer_queue, info, dec_cont->buffer_queue_index);
  }

  return dec_ret;
}


void JpegExistAbortState(JpegDecContainer *dec_cont) {
  ClearAbortStatusInList(&dec_cont->fb_list);
  InputQueueClearAbort(dec_cont->pp_buffer_queue);
  dec_cont->abort = 0;
}


enum DecRet JpegDecAbort(JpegDecInst dec_inst) {
  if(dec_inst == NULL) {
    APITRACEERR("%s","JpegDecAbort# ERROR: dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;

  SetAbortStatusInList(&dec_cont->fb_list);
  InputQueueSetAbort(dec_cont->pp_buffer_queue);
  dec_cont->abort = 1;

  return (DEC_OK);
}



enum DecRet JpegDecAbortAfter(JpegDecInst dec_inst) {
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  u32 i = 0;
  i32 core_id[MAX_ASIC_CORES];
  struct DWLReqInfo info = {0};

  if(dec_inst == NULL) {
    APITRACEERR("%s","JpegDecAbortAfter# ERROR: dec_inst or output is NULL\n");
    return (DEC_PARAM_ERROR);
  }

  if(dec_cont->asic_running && !dec_cont->b_mc) {
    /* Release HW */
    if(!dec_cont->vcmd_used) {
      DWLDisableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, 0);
      DWLReleaseHw(dec_cont->dwl, dec_cont->core_id);
    }
    else {
      DWLWaitCmdbufsDone(dec_cont->dwl, dec_inst);
    }
  }

  /* In multi-Core senario, waithwready is executed through listener thread,
          here to check whether HW is finished */
  if(dec_cont->b_mc) {
    if(!dec_cont->vcmd_used) {
      info.core_mask = dec_cont->core_mask;
      info.width = dec_cont->info.X;
      info.height = dec_cont->info.Y;
      for(i = 0; i < dec_cont->n_cores_available; i++) {
        DWLReserveHw(dec_cont->dwl, &info, &core_id[i]);
      }
      /* All HW Core finished */
      for(i = 0; i < dec_cont->n_cores_available; i++) {
        DWLReleaseHw(dec_cont->dwl, core_id[i]);
      }
    }
    else {
      DWLWaitCmdbufsDone(dec_cont->dwl, dec_inst);
    }
  }

  ResetOutFifoInList(&dec_cont->fb_list);
  InputQueueReset(dec_cont->pp_buffer_queue);
  JpegDecClearStructs(dec_cont, 1);
  dec_cont->ext_buffer_num = 0;
  ClearAbortStatusInList(&dec_cont->fb_list);
  InputQueueClearAbort(dec_cont->pp_buffer_queue);
  return (DEC_OK);
}

/*------------------------------------------------------------------------------
         Function name   : JpegDecUpdateStrmInfoCtrl
         Description     : called in low latency to set relative registers dynamically.
------------------------------------------------------------------------------*/
void JpegDecUpdateStrmInfoCtrl(JpegDecInst dec_inst,
                               struct strmInfo info)
{
  JpegDecContainer *dec_cont = (JpegDecContainer *) dec_inst;
  static u32 len_update = 1;

  if(dec_cont->update_reg_flag)
  {
    /* wait for hw ready if it's the first time to update length register */
    if(dec_cont->first_update)
    {
      while(!JpegCheckHwStatus(dec_cont))
        sched_yield();
      dec_cont->first_update = 0;
      dec_cont->ll_strm_len = 0;
      len_update = 1;
    }
    SwUpdateStrmInfoCtrl(info.strm_bus_addr, dec_cont->strm_status_addr,
                         &dec_cont->ll_strm_bus_address, &dec_cont->ll_strm_len,
                         info.last_flag, &len_update);
    /* update strm length register */
    if(JpegCheckHwStatus(dec_cont) == 0)
      dec_cont->update_reg_flag = 0;
  }
}

#ifdef CASE_INFO_STAT
void JpegCaseInfoCollect(JpegDecContainer *dec_cont, CaseInfo *case_info) {
  u32 display_width, display_height;
  u32 pic_width, pic_height, bit_depth;

  display_width = (dec_cont->frame.X + 1) &~ 0x1;
  display_height = (dec_cont->frame.Y + 1) &~ 0x1;
  pic_width = dec_cont->frame.hw_x;
  pic_height = dec_cont->frame.hw_y;
  bit_depth = dec_cont->frame.P == 8 ? 8 : 12;

  if(pic_width != display_width || pic_height != display_height)
    case_info->crop_flag = 1;

  if(!case_info->frame_num) {
    case_info->display_width = (dec_cont->frame.X + 1) &~ 0x1;
    case_info->display_height = (dec_cont->frame.Y + 1) &~ 0x1;
    case_info->decode_width = dec_cont->frame.hw_x;
    case_info->decode_height = dec_cont->frame.hw_y;
    case_info->bit_depth = bit_depth;
  } else {
    if(case_info->decode_width != pic_width
    || case_info->decode_height != pic_height) {
      case_info->decode_width = MAX (pic_width , case_info->decode_width);
      case_info->decode_height = MAX (pic_height, case_info->decode_height);
      case_info->resolution_flag = 1;
    }
    case_info->display_height = MIN (display_height, case_info->display_height);
    case_info->display_width = MIN (display_width, case_info->display_width);
    case_info->bit_depth = MAX (bit_depth, case_info->bit_depth);
  }

  switch(dec_cont->info.get_info_ycb_cr_mode) {
    case DEC_OUT_FRM_YUV420SP: case_info->chroma_format_id = PP_CHROMA_420; break;
    case DEC_OUT_FRM_YUV422SP: case_info->chroma_format_id = PP_CHROMA_422; break;
    case DEC_OUT_FRM_YUV411SP: case_info->chroma_format_id = PP_CHROMA_411; break;
    case DEC_OUT_FRM_YUV440: case_info->chroma_format_id = PP_CHROMA_440; break;
    case DEC_OUT_FRM_YUV444SP: case_info->chroma_format_id = PP_CHROMA_444; break;
    default: case_info->chroma_format_id = PP_CHROMA_400; break;
  }

  if(dec_cont->stream.thumbnail || case_info->thumb_flag)
    case_info->thumb_flag = 1;
  if(dec_cont->info.operation_type == JPEG_PROGRESSIVE)
    case_info->pjpeg_flag = 1;

  if(case_info->frame_num < 10)
    case_info->slice_num[case_info->frame_num]++;

  case_info->codec = DEC_MODE_JPEG;
  case_info->frame_num ++;
  case_info->bitrate = ((60 * GetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_LEN) * 8 / case_info->decode_width)
                          * 3840/ case_info->decode_height) * 2160 / 1024 / 1024;
}
#endif
