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

#include "basetype.h"
#include "jpegdeccontainer.h"
#include "jpegdecapi.h"
#include "jpegdecmarkers.h"
#include "jpegdecutils.h"
#include "jpegdechdrs.h"
#include "jpegdecinternal.h"
#include "dwl.h"
#include "deccfg.h"
#include "sw_util.h"
#include "regdrv.h"
#include "ppu.h"
#include "delogo.h"
#include "dec_log.h"
#ifdef JPEGDEC_ASIC_TRACE
#include "jpegasicdbgtrace.h"
#endif /* #ifdef JPEGDEC_TRACE */

#ifdef JPEGDEC_PP_TRACE
#include "ppinternal.h"
#endif /* #ifdef JPEGDEC_PP_TRACE */
/*------------------------------------------------------------------------------
    2. External compiler flags
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
    3. Module defines
------------------------------------------------------------------------------*/

#define JPEGDEC_SLICE_START_VALUE 0
#define JPEGDEC_VLC_LEN_START_REG 16
#define JPEGDEC_VLC_LEN_END_REG 29

#ifdef PJPEG_COMPONENT_TRACE
extern u32 pjpeg_component_id;
extern u32 *pjpeg_coeff_base;
extern u32 pjpeg_coeff_size;

#define TRACE_COMPONENT_ID(id) pjpeg_component_id = id
#else
#define TRACE_COMPONENT_ID(id)
#endif

/*------------------------------------------------------------------------------
    4. Local function prototypes
------------------------------------------------------------------------------*/
static void JpegDecSetHwStrmParams(JpegDecContainer * dec_cont);

/*------------------------------------------------------------------------------
    5. Functions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------

        Function name: JpegDecClearStructs

        Functional description:
          handles the initialisation of jpeg decoder data structure

        Inputs:

        Outputs:
          Returns OK when successful, NOK in case unknown message type is
          asked

------------------------------------------------------------------------------*/
void JpegDecClearStructs(JpegDecContainer * dec_cont, u32 mode) {
  u32 i;

  ASSERT(dec_cont);

  /* stream pointers */
  dec_cont->stream.stream_bus = 0;
  dec_cont->stream.p_start_of_stream = NULL;
  dec_cont->stream.p_start_of_buffer = NULL;
  dec_cont->stream.p_curr_pos = NULL;
  dec_cont->stream.bit_pos_in_byte = 0;
  dec_cont->stream.stream_length = 0;
  dec_cont->stream.strm_buff_size = 0;
  dec_cont->stream.read_bits = 0;
  dec_cont->stream.appn_flag = 0;
  dec_cont->stream.return_sos_marker = 0;

  /* output image pointers and variables */
  dec_cont->image.p_start_of_image = NULL;
  dec_cont->image.p_lum = NULL;
  dec_cont->image.p_cr = NULL;
  dec_cont->image.p_cb = NULL;
  dec_cont->image.header_ready = 0;
  dec_cont->image.image_ready = 0;
  dec_cont->image.ready = 0;
  dec_cont->image.size = 0;
  dec_cont->image.size_luma = 0;
  dec_cont->image.size_chroma = 0;
  for(i = 0; i < MAX_NUMBER_OF_COMPONENTS; i++) {
    dec_cont->image.columns[i] = 0;
    dec_cont->image.pixels_per_row[i] = 0;
  }

  /* frame info */
  dec_cont->frame.Lf = 0;
  dec_cont->frame.P = 0;
  //dec_cont->frame.Y = 0;
  //dec_cont->frame.X = 0;

  if(!mode) {
    dec_cont->frame.Y = 0;
    dec_cont->frame.X = 0;
    dec_cont->frame.hw_y = 0;
    dec_cont->frame.hw_x = 0;
    dec_cont->frame.hw_ytn = 0;
    dec_cont->frame.hw_xtn = 0;
    dec_cont->frame.full_x = 0;
    dec_cont->frame.full_y = 0;
    dec_cont->stream.thumbnail = 0;
  } else {
    if(dec_cont->stream.thumbnail) {
      dec_cont->frame.hw_y = dec_cont->frame.full_y;
      dec_cont->frame.hw_x = dec_cont->frame.full_x;
      dec_cont->stream.thumbnail = 0;
    }
  }

  dec_cont->frame.Nf = 0; /* Number of components in frame */
  dec_cont->frame.num_mcu_in_frame = 0;
  dec_cont->frame.num_mcu_in_row = 0;
  dec_cont->frame.mcu_number = 0;
  dec_cont->frame.Ri = 0;
  dec_cont->frame.row = 0;
  dec_cont->frame.col = 0;
  dec_cont->frame.dri_period = 0;
  dec_cont->frame.block = 0;
  dec_cont->frame.c_index = 0;
  dec_cont->frame.buffer_bus = 0;

  if(!mode) {
    dec_cont->frame.p_buffer = NULL;
    dec_cont->frame.p_buffer_cb = NULL;
    dec_cont->frame.p_buffer_cr = NULL;
    for (i = 0; i < MAX_ASIC_CORES; i ++) {
      dec_cont->frame.p_table_base[i].virtual_address = NULL;
      dec_cont->frame.p_table_base[i].bus_address = 0;
    }

    /* asic buffer */
    dec_cont->asic_buff.out_luma_buffer.virtual_address = NULL;
    dec_cont->asic_buff.out_chroma_buffer.virtual_address = NULL;
    dec_cont->asic_buff.out_chroma_buffer2.virtual_address = NULL;
    if(dec_cont->pp_enabled && dec_cont->info.user_alloc_mem) {
      dec_cont->asic_buff.pp_luma_buffer.virtual_address = NULL;
      dec_cont->asic_buff.pp_chroma_buffer.virtual_address = NULL;
      dec_cont->asic_buff.pp_luma_buffer.bus_address = 0;
      dec_cont->asic_buff.pp_chroma_buffer.bus_address = 0;
    }
    dec_cont->asic_buff.out_luma_buffer.bus_address = 0;
    dec_cont->asic_buff.out_chroma_buffer.bus_address = 0;
    dec_cont->asic_buff.out_chroma_buffer2.bus_address = 0;
    dec_cont->asic_buff.out_luma_buffer.size = 0;
    dec_cont->asic_buff.out_chroma_buffer.size = 0;
    dec_cont->asic_buff.out_chroma_buffer2.size = 0;

    /* pp instance */
    dec_cont->pp_status = 0;
    dec_cont->pp_instance = NULL;
    dec_cont->PPRun = NULL;
    dec_cont->PPEndCallback = NULL;
    dec_cont->pp_control.use_pipeline = 0;

    /* resolution */
    dec_cont->min_supported_width = 0;
    dec_cont->min_supported_height = 0;
    dec_cont->max_supported_width = 0;
    dec_cont->max_supported_height = 0;
    dec_cont->max_supported_pixel_amount = 0;
    dec_cont->max_supported_slice_size = 0;

    /* out bus tmp */
    dec_cont->info.out_luma.virtual_address = NULL;
    dec_cont->info.out_chroma.virtual_address = NULL;
    if(dec_cont->pp_enabled && dec_cont->info.user_alloc_mem) {
      dec_cont->info.out_pp_luma.virtual_address = NULL;
      dec_cont->info.out_pp_chroma.virtual_address = NULL;
    }
    dec_cont->info.out_chroma2.virtual_address = NULL;
    dec_cont->info.out_luma.bus_address = 0;
    dec_cont->info.out_chroma.bus_address = 0;
    dec_cont->info.out_chroma2.bus_address = 0;

    /* user allocated addresses */
    dec_cont->info.given_out_luma.virtual_address = NULL;
    dec_cont->info.given_out_chroma.virtual_address = NULL;
    dec_cont->info.given_out_chroma2.virtual_address = NULL;
    dec_cont->info.given_out_luma.bus_address = 0;
    dec_cont->info.given_out_chroma.bus_address = 0;
    dec_cont->info.given_out_chroma2.bus_address = 0;
  }

  /* asic running flag */
  dec_cont->asic_running = 0;

  /* PJPEG flags */
  dec_cont->last_scan = 0;
  DWLmemset(dec_cont->pjpeg_coeff_bit_map, 0, sizeof(u16)*64*3);

  /* image handling info */
  dec_cont->info.slice_height = 0;
  dec_cont->info.amount_of_qtables = 0;
  dec_cont->info.y_cb_cr_mode = 0;
  dec_cont->info.column = 0;
  dec_cont->info.X = 0;
  dec_cont->info.Y = 0;
  dec_cont->info.mem_size = 0;
  dec_cont->info.SliceCount = 0;
  dec_cont->info.SliceMBCutValue = 0;
  dec_cont->info.pipeline = 0;
  if(!mode)
    dec_cont->info.user_alloc_mem = 0;
  dec_cont->info.slice_start_count = 0;
  dec_cont->info.amount_of_slices = 0;
  dec_cont->info.no_slice_irq_for_user = 0;
  dec_cont->info.SliceReadyForPause = 0;
  dec_cont->info.slice_limit_reached = 0;
  dec_cont->info.slice_mb_set_value = 0;
  dec_cont->info.timeout = (u32) DEC_X170_TIMEOUT_LENGTH;
  dec_cont->info.rlc_mode = 0; /* JPEG always in VLC mode == 0 */
  dec_cont->info.luma_pos = 0;
  dec_cont->info.chroma_pos = 0;
  dec_cont->info.fill_right = 0;
  dec_cont->info.fill_bottom = 0;
  dec_cont->info.stream_end = 0;
  dec_cont->info.stream_end_flag = 0;
  dec_cont->info.input_buffer_empty = 0;
  dec_cont->info.input_streaming = 0;
  dec_cont->info.input_buffer_len = 0;
  dec_cont->info.decoded_stream_len = 0;
  dec_cont->info.init = 0;
  dec_cont->info.init_thumb = 0;
  dec_cont->info.init_buffer_size = 0;

  /* progressive */
  dec_cont->info.non_interleaved = 0;
  dec_cont->info.component_id = 0;
  dec_cont->info.operation_type = 0;
  dec_cont->info.operation_type_thumb = 0;

  if(!mode) {
    dec_cont->info.p_coeff_base.virtual_address = NULL;
    dec_cont->info.p_coeff_base.bus_address = 0;
    dec_cont->info.y_cb_cr_mode_orig = 0;
    dec_cont->info.get_info_ycb_cr_mode = 0;
    dec_cont->info.get_info_ycb_cr_mode_tn = 0;
  }

  dec_cont->info.allocated = 0;

  for(i = 0; i < MAX_NUMBER_OF_COMPONENTS; i++) {
    dec_cont->info.components[i] = 0;
    dec_cont->info.pred[i] = 0;
    dec_cont->info.dc_res[i] = 0;
    dec_cont->frame.num_blocks[i] = 0;
    dec_cont->frame.blocks_per_row[i] = 0;
    dec_cont->frame.use_ac_offset[i] = 0;
    dec_cont->frame.component[i].C = 0;
    dec_cont->frame.component[i].H = 0;
    dec_cont->frame.component[i].V = 0;
    dec_cont->frame.component[i].Tq = 0;
  }

  /* scan info */
  dec_cont->scan.Ls = 0;
  dec_cont->scan.Ns = 0;
  dec_cont->scan.Ss = 0;
  dec_cont->scan.Se = 0;
  dec_cont->scan.Ah = 0;
  dec_cont->scan.Al = 0;
  dec_cont->scan.index = 0;
  dec_cont->scan.num_idct_rows = 0;

  for(i = 0; i < MAX_NUMBER_OF_COMPONENTS; i++) {
    dec_cont->scan.Cs[i] = 0;
    dec_cont->scan.Td[i] = 0;
    dec_cont->scan.Ta[i] = 0;
    dec_cont->scan.pred[i] = 0;
  }

  /* huffman table lengths */
  dec_cont->vlc.default_tables = 0;
  dec_cont->vlc.ac_table0.table_length = 0;
  dec_cont->vlc.ac_table1.table_length = 0;
  dec_cont->vlc.ac_table2.table_length = 0;
  dec_cont->vlc.ac_table3.table_length = 0;

  dec_cont->vlc.dc_table0.table_length = 0;
  dec_cont->vlc.dc_table1.table_length = 0;
  dec_cont->vlc.dc_table2.table_length = 0;
  dec_cont->vlc.dc_table3.table_length = 0;

  /* Restart interval */
  dec_cont->frame.Ri = 0;

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

  /* pointer initialisation */
  dec_cont->vlc.ac_table0.vals = NULL;
  dec_cont->vlc.ac_table1.vals = NULL;
  dec_cont->vlc.ac_table2.vals = NULL;
  dec_cont->vlc.ac_table3.vals = NULL;

  dec_cont->vlc.dc_table0.vals = NULL;
  dec_cont->vlc.dc_table1.vals = NULL;
  dec_cont->vlc.dc_table2.vals = NULL;
  dec_cont->vlc.dc_table3.vals = NULL;

  dec_cont->frame.p_buffer = NULL;

  return;
}

/*------------------------------------------------------------------------------

        Function name: JpegDecInitHW

        Functional description:
          Set up HW regs for decode

        Inputs:
          JpegDecContainer *dec_cont

        Outputs:
          Returns OK when successful, NOK in case unknown message type is
          asked

------------------------------------------------------------------------------*/
enum DecRet JpegDecInitHW(JpegDecContainer * dec_cont) {
  u32 i;
  addr_t coeff_buffer = 0;
  u32 core_id = 0;
  const struct DecHwFeatures *hw_feature = NULL;
  ASSERT(dec_cont);
  struct DWLReqInfo info = {0};

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  TRACE_COMPONENT_ID(dec_cont->info.component_id);

  /* Check if first InitHw call */
  if(dec_cont->info.slice_start_count == 0) {
    /* Check if HW resource is available */
    info.core_mask = dec_cont->core_mask;
    info.width = dec_cont->info.X;
    info.height = dec_cont->info.Y;
    if (!dec_cont->vcmd_used) {
      if(DWLReserveHw(dec_cont->dwl,  &info, &dec_cont->core_id) == DWL_ERROR) {
        APITRACEERR("%s","JpegDecInitHW: ERROR hw resource unavailable\n");
        return DEC_HW_RESERVED;
      }
    } else {
      /* Always store registers in jpeg_regs[0] when VCMD is used.*/
#if 0
      core_id = dec_cont->core_id + 1;
      core_id = (core_id>=MAX_MC_CB_ENTRIES)?0:core_id;
      dec_cont->core_id = core_id;
#endif
      dec_cont->core_id = 0;
      if (DWLReserveCmdBuf(dec_cont->dwl, &info, &dec_cont->cmd_buf_id) == DWL_ERROR) {
        APITRACEERR("%s","JpegDecInitHW: ERROR command buffer unavailable\n");
        return DEC_HW_RESERVED;
      }
    }

    if (dec_cont->b_mc) {
      if (!dec_cont->vcmd_used)
        dec_cont->dec_status[dec_cont->core_id] = DEC_RUNNING;
    }
  }

  core_id = dec_cont->b_mc ? dec_cont->core_id : 0;
  /*************** Set swreg4 data ************/

  APITRACEDEBUG("%s","INTERNAL: Set Frame width\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PIC_WIDTH_IN_CBS,
                  dec_cont->info.X >> 3);

  APITRACEDEBUG("%s","INTERNAL: Set Frame height\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PIC_HEIGHT_IN_CBS,
                  dec_cont->info.Y >> 3);



  APITRACEDEBUG("%s","INTERNAL: Set decoding mode: JPEG\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_MODE, DEC_MODE_JPEG);


  APITRACEDEBUG("%s","INTERNAL: Set output write disabled\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_OUT_DIS, 1);


  APITRACEDEBUG("%s","INTERNAL: Set filtering disabled\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_FILTERING_DIS, 1);

  APITRACEDEBUG("%s","INTERNAL: Set amount of QP Table\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_QTABLES,
                 dec_cont->info.amount_of_qtables);

  APITRACEDEBUG("%s","INTERNAL: Set input format\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_MODE,
                 dec_cont->info.y_cb_cr_mode_orig);

  APITRACEDEBUG("%s","INTERNAL: RLC mode enable, JPEG == disable\n");
  /* In case of JPEG: Always VLC mode used (0) */
  //SetDecRegister(dec_cont->jpeg_regs, HWIF_RLC_MODE_E, dec_cont->info.rlc_mode);

  /*************** Set swreg15 data ************/
  APITRACEDEBUG("%s","INTERNAL: Set slice/full mode: 0 full; other = slice\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_SLICE_H,
                 dec_cont->info.slice_height);

  /*************** Set swreg52 data ************/
  if(dec_cont->info.operation_type != JPEG_PROGRESSIVE) {
    /* Set JPEG operation mode */
    APITRACEDEBUG("%s","INTERNAL: Set JPEG operation mode\n");
    SetDecRegister(dec_cont->jpeg_regs, HWIF_PJPEG_E, 0);
  } else {
    /* Set JPEG operation mode */
    APITRACEDEBUG("%s","INTERNAL: Set JPEG operation mode\n");
    SetDecRegister(dec_cont->jpeg_regs, HWIF_PJPEG_E, 1);

    /* write coeff table base */
    APITRACEDEBUG("%s","INTERNAL: Set coefficient buffer base address\n");
    coeff_buffer = dec_cont->info.p_coeff_base.bus_address;
    SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_PJPEG_COEFF_BUF,
                 coeff_buffer);
  }

  dec_cont->stream = dec_cont->hw_stream;
  /* Set JPEG operation mode */
  APITRACEDEBUG("%s","INTERNAL: Set JPEG operation mode\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_FRAME_MODE, dec_cont->info.operation_type);
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_12BIT_E, (dec_cont->frame.P == 12 ? 1 : 0));
  SetDecRegister(dec_cont->jpeg_regs, HWIF_BIT_DEPTH_Y_MINUS8,
                  (dec_cont->frame.P == 8 ? 0 : 2));
  SetDecRegister(dec_cont->jpeg_regs, HWIF_BIT_DEPTH_C_MINUS8,
                  (dec_cont->frame.P == 8 ? 0 : 2));

  /* write Qtable selector */
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PJPEG_QTABLE_SEL0,
                  dec_cont->frame.component[0].Tq);
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PJPEG_QTABLE_SEL1,
                  dec_cont->frame.component[1].Tq);
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PJPEG_QTABLE_SEL2,
                  dec_cont->frame.component[2].Tq);

  SetDecRegister(dec_cont->jpeg_regs, HWIF_UNIQUE_ID, UNIQUE_ID(0));

  /* set up stream position for HW decode */
  APITRACEDEBUG("%s","INTERNAL: Set stream position for HW\n");
  JpegDecSetHwStrmParams(dec_cont);
  /* Handle PP and output base addresses */
  /* Set the buffer bus address for using ddr_low_latency */
  if(dec_cont->strm_status_in_buffer == 1){
    SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_LG_STREAM_STATUS_BASE,
                   dec_cont->strm_status.bus_address);
    dec_cont->strm_status_addr = dec_cont->strm_status.virtual_address;
    *dec_cont->strm_status_addr = 0;
  }
  /* PP depending register writes */
  if(dec_cont->pp_instance != NULL && dec_cont->pp_control.use_pipeline) {
    /*************** Set swreg4 data ************/

    APITRACEDEBUG("%s","INTERNAL: Set output write disabled\n");
    SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_OUT_DIS, 1);

    /* set output to zero, because of pp */
    /*************** Set swreg13 data ************/
    /* Luminance output */
    APITRACEDEBUG("%s","INTERNAL: Set LUMA OUTPUT data base address\n");
    SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_DEC_OUT_BASE, (addr_t)0);

    /*************** Set swreg14 data ************/
    /* Chrominance output */
    if(dec_cont->image.size_chroma) {
      /* write output base */
      APITRACEDEBUG("%s","INTERNAL: Set CHROMA OUTPUT data base address\n");
      SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_JPG_CH_OUT_BASE, (addr_t)0);
    }

    if(dec_cont->info.slice_start_count == JPEGDEC_SLICE_START_VALUE) {
      /* Enable pp */
      APITRACEDEBUG("%s","INTERNAL: Set Enable pp\n");
      dec_cont->PPRun(dec_cont->pp_instance, &dec_cont->pp_control);

      dec_cont->pp_control.pp_status = DECPP_RUNNING;
    }

    dec_cont->info.pipeline = 1;
  } else {

    ASSERT(dec_cont->pp_enabled);
    if (dec_cont->pp_enabled /*&& ((asic_id & 0x0000F000) >> 12 >= 7)*/) {
      PpUnitIntConfig *ppu_cfg = &dec_cont->ppu_cfg[0];
      PpUnitIntConfig tmp_ppu_cfg[DEC_MAX_PPU_COUNT];
      DWLmemcpy(tmp_ppu_cfg, dec_cont->ppu_cfg, sizeof(dec_cont->ppu_cfg));
      if (RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
        u32 ri_height = dec_cont->frame.num_mcu_rows_in_interval *
                        dec_cont->frame.mcu_height;
        for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
          u32 full_crop_h = ppu_cfg->crop.height;
          u32 full_scale_h = ppu_cfg->scale.height;
          if (!ppu_cfg->enabled ||
              /* Not in cropping window. */
              dec_cont->ri_index < dec_cont->start_ri_index[i] ||
              dec_cont->ri_index > dec_cont->end_ri_index[i]) {
              ppu_cfg->enabled = 0;
              continue;
          }
          if (dec_cont->ri_index == dec_cont->start_ri_index[i]) {
            /* First restart interval:
             * Update:
             *    crop.y
             *    crop.height
             *    scale.height
             */
            /* Becareful of overflow & underflow, especially for 16/32K jpeg. */
            ppu_cfg->crop.y = ppu_cfg->crop.y % ri_height;
            ppu_cfg->crop.height = ri_height - ppu_cfg->crop.y;
          } else {
            /* Middle/last restart intervals:
             * Update:
             *    crop.y -> 0
             *    crop.height -> restart interval height / real height in ri
             *    scale.height
             *    luma_offset/chroma_offset
             */
            if (dec_cont->ri_index == dec_cont->end_ri_index[i]) {
              ppu_cfg->crop.height = (ppu_cfg->crop.y + ppu_cfg->crop.height) % ri_height;
              if (!ppu_cfg->crop.height)
                ppu_cfg->crop.height = ri_height;
            } else {
              ppu_cfg->crop.height = ri_height;
            }
            ppu_cfg->luma_offset += ppu_cfg->luma_size / full_crop_h *
                                    (dec_cont->ri_index * ri_height -
                                     ppu_cfg->crop.y);
            ppu_cfg->chroma_offset += ppu_cfg->chroma_size / full_crop_h *
                                      (dec_cont->ri_index * ri_height -
                                       ppu_cfg->crop.y);
            ppu_cfg->crop.y = 0;
          }
          ppu_cfg->scale.height = ppu_cfg->crop.height *
                                    full_scale_h / full_crop_h;
          }
        }
        /* PPSetRegs need to add slice_mb_set_value support in future  */
        DelogoSetRegs(dec_cont->jpeg_regs, hw_feature, dec_cont->delogo_params);
        PPSetRegs(dec_cont->jpeg_regs, hw_feature, dec_cont->ppu_cfg,
                  dec_cont->asic_buff.pp_luma_buffer.bus_address, 0, 0);
        PPSetLancozsScaleRegs(dec_cont->jpeg_regs, hw_feature, dec_cont->ppu_cfg, core_id);
        if (RI_MC_ENABLED(dec_cont->ri_mc_enabled)) {
          /* Restore ppu config. */
          DWLmemcpy(dec_cont->ppu_cfg, tmp_ppu_cfg, sizeof(dec_cont->ppu_cfg));
          dec_cont->ri_running_cores++;
        }
      }
      /* Crop when hight is multiple of 8 instead of 16. */
      if (((dec_cont->frame.Y + 7) >> 3) & 1) {
        SetDecRegister(dec_cont->jpeg_regs, HWIF_MB_HEIGHT_OFF, 8);
      } else
        SetDecRegister(dec_cont->jpeg_regs, HWIF_MB_HEIGHT_OFF, 0);

  }
  /* In slice decoding mode, HW is only reserved once, but HW must be reserved for each
   * ri in ri-based multicore decoding. */
  if (!RI_MC_ENABLED(dec_cont->ri_mc_enabled))
    dec_cont->info.slice_start_count = 1;

#ifdef JPEGDEC_ASIC_TRACE
  {
    FILE *fd;

    fd = fopen("picture_ctrl_dec.trc", "at");
    DumpJPEGCtrlReg(dec_cont->jpeg_regs, fd);
    fclose(fd);

    fd = fopen("picture_ctrl_dec.hex", "at");
    HexDumpJPEGCtrlReg(dec_cont->jpeg_regs, fd);
    fclose(fd);

    fd = fopen("jpeg_tables.hex", "at");
    HexDumpJPEGTables(dec_cont->jpeg_regs, dec_cont, fd);
    fclose(fd);

    fd = fopen("registers.hex", "at");
    HexDumpRegs(dec_cont->jpeg_regs, fd);
    fclose(fd);
  }
#endif /* #ifdef JPEGDEC_ASIC_TRACE */

#ifdef JPEGDEC_PP_TRACE
  ppRegDump(((PPContainer_t *) dec_cont->pp_instance)->pp_regs);
#endif /* #ifdef JPEGDEC_PP_TRACE */
  dec_cont->asic_running = 1;

  /* Enable jpeg mode and set slice mode */
  APITRACEDEBUG("%s","INTERNAL: Enable jpeg\n");
  DWLReadPpConfigure(dec_cont->dwl, dec_cont->vcmd_used ? dec_cont->cmd_buf_id : dec_cont->core_id,
                     dec_cont->ppu_cfg, dec_cont->pjpeg_coeff_size_for_cache);
  SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_E, 1);

  /* Flush regs to hw register */
  JpegFlushRegs(dec_cont);

#ifdef SUPPORT_DMA
  for (i =0; i < dec_cont->n_cores; i ++) {
    if(dec_cont->frame.p_table_base[i].virtual_address != NULL)
      DWLDMATransData((addr_t)dec_cont->frame.p_table_base[i].bus_address,
                      (void *)dec_cont->frame.p_table_base[i].virtual_address,
                      dec_cont->frame.p_table_base[i].size, HOST_TO_DEVICE);
  }
#endif
  if (!dec_cont->vcmd_used)
    DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 4 * 1, dec_cont->jpeg_regs[1]);
  else
    DWLEnableCmdBuf(dec_cont->dwl, dec_cont->cmd_buf_id);
  return DEC_OK;
}

/*------------------------------------------------------------------------------

        Function name: JpegDecInitHWContinue

        Functional description:
          Set up HW regs for decode

        Inputs:
          JpegDecContainer *dec_cont

        Outputs:
          Returns OK when successful, NOK in case unknown message type is
          asked

------------------------------------------------------------------------------*/
void JpegDecInitHWContinue(JpegDecContainer * dec_cont) {
  ASSERT(dec_cont);
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  /* update slice counter */
  dec_cont->info.amount_of_slices++;

  if(dec_cont->pp_instance == NULL &&
      dec_cont->info.user_alloc_mem == 1 && dec_cont->info.slice_start_count > 0) {
    /* if user allocated memory ==> new addresses */
    dec_cont->asic_buff.out_luma_buffer.virtual_address =
      dec_cont->info.given_out_luma.virtual_address;
    dec_cont->asic_buff.out_luma_buffer.bus_address =
      dec_cont->info.given_out_luma.bus_address;
    dec_cont->asic_buff.out_chroma_buffer.virtual_address =
      dec_cont->info.given_out_chroma.virtual_address;
    dec_cont->asic_buff.out_chroma_buffer.bus_address =
      dec_cont->info.given_out_chroma.bus_address;
  }

  /* Update only register/values that might have been changed */

  /*************** Set swreg1 data ************/
  /* clear status bit */
  SetDecRegister(dec_cont->jpeg_regs, HWIF_DEC_SLICE_INT, 0);

  /*************** Set swreg5 data ************/
  APITRACEDEBUG("%s","INTERNAL CONTINUE: Set stream last buffer bit\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_STREAM_ALL,
                 dec_cont->info.stream_end);

  /*************** Set swreg13 data ************/
  /* PP depending register writes */
  if(dec_cont->pp_instance == NULL) {
    /* Luminance output */
    APITRACEDEBUG("%s","INTERNAL CONTINUE: Set LUMA OUTPUT data base address\n");
    SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_DEC_OUT_BASE,
                 dec_cont->asic_buff.out_luma_buffer.bus_address);

    /*************** Set swreg14 data ************/

    /* Chrominance output */
    if(dec_cont->image.size_chroma) {
      /* write output base */
      APITRACEDEBUG("%s","INTERNAL CONTINUE: Set CHROMA OUTPUT data base address\n");
      SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_JPG_CH_OUT_BASE,
                   dec_cont->asic_buff.out_chroma_buffer.bus_address);
    }

    dec_cont->info.pipeline = 0;
  }

  /*************** Set swreg13 data ************/
  /* PP depending register writes */
  if(dec_cont->pp_instance != NULL && dec_cont->pp_control.use_pipeline == 0) {
    if(dec_cont->info.y_cb_cr_mode == JPEGDEC_YUV420) {
      dec_cont->info.luma_pos = (dec_cont->info.X *
                                 (dec_cont->info.slice_mb_set_value * 16));
      dec_cont->info.chroma_pos = ((dec_cont->info.X) *
                                   (dec_cont->info.slice_mb_set_value * 8));
    } else if(dec_cont->info.y_cb_cr_mode == JPEGDEC_YUV422) {
      dec_cont->info.luma_pos = (dec_cont->info.X *
                                 (dec_cont->info.slice_mb_set_value * 16));
      dec_cont->info.chroma_pos = ((dec_cont->info.X) *
                                   (dec_cont->info.slice_mb_set_value * 16));
    } else if(dec_cont->info.y_cb_cr_mode == JPEGDEC_YUV440) {
      dec_cont->info.luma_pos = (dec_cont->info.X *
                                 (dec_cont->info.slice_mb_set_value * 16));
      dec_cont->info.chroma_pos = ((dec_cont->info.X) *
                                   (dec_cont->info.slice_mb_set_value * 16));
    } else {
      dec_cont->info.luma_pos = (dec_cont->info.X *
                                 (dec_cont->info.slice_mb_set_value * 16));
      dec_cont->info.chroma_pos = 0;
    }

    /* update luma/chroma position */
    dec_cont->info.luma_pos = (dec_cont->info.luma_pos *
                               dec_cont->info.amount_of_slices);
    if(dec_cont->info.chroma_pos) {
      dec_cont->info.chroma_pos = (dec_cont->info.chroma_pos *
                                   dec_cont->info.amount_of_slices);
    }

    /* Luminance output */
    APITRACEDEBUG("%s","INTERNAL CONTINUE: Set LUMA OUTPUT data base address\n");
    SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_DEC_OUT_BASE,
                 dec_cont->asic_buff.out_luma_buffer.bus_address +
                 dec_cont->info.luma_pos);

    /*************** Set swreg14 data ************/

    /* Chrominance output */
    if(dec_cont->image.size_chroma) {
      /* write output base */
      APITRACEDEBUG("%s","INTERNAL CONTINUE: Set CHROMA OUTPUT data base address\n");
      SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_JPG_CH_OUT_BASE,
                   dec_cont->asic_buff.out_chroma_buffer.bus_address +
                   dec_cont->info.chroma_pos);
    }

    dec_cont->info.pipeline = 0;
  }

  /*************** Set swreg15 data ************/
  APITRACEDEBUG("%s","INTERNAL CONTINUE: Set slice/full mode: 0 full; other = slice\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_SLICE_H,
                 dec_cont->info.slice_height);

  /* Flush regs to hw register */
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x34,
              dec_cont->jpeg_regs[13]);
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x38,
              dec_cont->jpeg_regs[14]);
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x3C,
              dec_cont->jpeg_regs[15]);
  if(sizeof(addr_t) == 8) {
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x1EC,
                dec_cont->jpeg_regs[123]);
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x1F0,
                dec_cont->jpeg_regs[124]);
    DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x1F4,
                dec_cont->jpeg_regs[125]);
  }
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x14,
              dec_cont->jpeg_regs[5]);
  DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 0x4,
              dec_cont->jpeg_regs[1]);

#ifdef JPEGDEC_ASIC_TRACE
  {
    APITRACEDEBUG("%s","INTERNAL CONTINUE: REGS BEFORE IRQ CLEAN\n");
    PrintJPEGReg(dec_cont->jpeg_regs);
  }
#endif /* #ifdef JPEGDEC_ASIC_TRACE */

}

/*------------------------------------------------------------------------------

        Function name: JpegDecInitHWInputBuffLoad

        Functional description:
          Set up HW regs for decode after input buffer load

        Inputs:
          JpegDecContainer *dec_cont

        Outputs:
          Returns OK when successful, NOK in case unknown message type is
          asked

------------------------------------------------------------------------------*/
void JpegDecInitHWInputBuffLoad(JpegDecContainer * dec_cont) {
  const struct DecHwFeatures *hw_feature = NULL;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  ASSERT(dec_cont);

  /* Update only register/values that might have been changed */
  /*************** Set swreg4 data ************/

  APITRACEDEBUG("%s","INTERNAL: Set Frame width\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PIC_WIDTH_IN_CBS,
                  ((dec_cont->info.X >> 4) << 1));

    /* frame size, round up the number of mbs */
  APITRACEDEBUG("%s","INTERNAL: Set Frame height\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_PIC_HEIGHT_IN_CBS,
                  (dec_cont->info.Y >> 4) << 1);


  /* Only used in PJPEG 411 to indicate pic_width is filled to 32 or not */
  if(dec_cont->info.operation_type == JPEG_PROGRESSIVE)
    SetDecRegister(dec_cont->jpeg_regs, HWIF_PJPEG_WIDTH_DIV16,
                   dec_cont->info.wdiv16);

  /*************** Set swreg5 data ************/
  APITRACEDEBUG("%s","INTERNAL BUFFER LOAD: Set stream start bit\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_BIT,
                 dec_cont->stream.bit_pos_in_byte);

  /*************** Set swreg6 data ************/
  APITRACEDEBUG("%s","INTERNAL BUFFER LOAD: Set stream length\n");

  /* check if all stream will processed in this buffer */
  if((dec_cont->info.decoded_stream_len) >= dec_cont->stream.stream_length) {
    dec_cont->info.stream_end = 1;
  }

  SetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_LEN,
                 dec_cont->info.input_buffer_len);
  SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_BUFFER_LEN,
                 dec_cont->info.input_buffer_len);
  SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_OFFSET, 0);

#ifdef SUPPORT_DMA
  DWLDMATransData((addr_t)dec_cont->stream.stream_bus,
                  (void *)dec_cont->stream.p_start_of_buffer,
                  dec_cont->stream.strm_buff_size, HOST_TO_DEVICE);
#endif

  /*************** Set swreg4 data ************/
  APITRACEDEBUG("%s","INTERNAL BUFFER LOAD: Set stream last buffer bit\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_STREAM_ALL,
                 dec_cont->info.stream_end);

  /*************** Set swreg12 data ************/
  APITRACEDEBUG("%s","INTERNAL BUFFER LOAD: Set stream start address\n");
  SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_RLC_VLC_BASE,
               dec_cont->stream.stream_bus);
  dec_cont->jpeg_hw_start_bus = dec_cont->stream.stream_bus;

  APITRACEDEBUG("INTERNAL BUFFER LOAD: Stream bus start 0x%08lx\n",
                          dec_cont->stream.stream_bus);
  APITRACEDEBUG("INTERNAL BUFFER LOAD: Bit position 0x%08x\n",
                          dec_cont->stream.bit_pos_in_byte);
  APITRACEDEBUG("INTERNAL BUFFER LOAD: Stream length 0x%08x\n",
                          dec_cont->stream.stream_length);

  /* Flush regs to hw register */
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x2A0,
              dec_cont->jpeg_regs[168]);
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x2A4,
              dec_cont->jpeg_regs[169]);
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x10,
              dec_cont->jpeg_regs[4]);
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x14,
              dec_cont->jpeg_regs[5]);
  DWLWriteReg(dec_cont->dwl, dec_cont->core_id, 0x18,
              dec_cont->jpeg_regs[6]);
  DWLEnableHw(dec_cont->dwl, dec_cont->core_id, 0x04,
              dec_cont->jpeg_regs[1]);

#ifdef JPEGDEC_ASIC_TRACE
  {
    APITRACEDEBUG("%s","INTERNAL BUFFER LOAD: REGS BEFORE IRQ CLEAN\n");
    PrintJPEGReg(dec_cont->jpeg_regs);
  }
#endif /* #ifdef JPEGDEC_ASIC_TRACE */

}

/*------------------------------------------------------------------------------

        Function name: JpegDecSetHwStrmParams

        Functional description:
          set up hw stream start position

        Inputs:
          JpegDecContainer *dec_cont

        Outputs:
          void

------------------------------------------------------------------------------*/
static void JpegDecSetHwStrmParams(JpegDecContainer * dec_cont) {
#define JPG_STR     dec_cont->stream
  addr_t addr_tmp = 0;
  u32 amount_of_stream = 0;
  const struct DecHwFeatures *hw_feature = NULL;
  addr_t mask;

  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);

  /* calculate and set stream start address to hw */
  APITRACEDEBUG("INTERNAL: read bits %d\n", JPG_STR.read_bits);
  APITRACEDEBUG("INTERNAL: read bytes %d\n", JPG_STR.read_bits / 8);
  APITRACEDEBUG("INTERNAL: Stream bus start 0x%08lx\n",
                          JPG_STR.stream_bus);
  APITRACEDEBUG("INTERNAL: Stream virtual start 0x%p\n",
                          JPG_STR.p_start_of_stream);


  mask = 15;


  /* calculate and set stream start address to hw */
  addr_tmp = (JPG_STR.stream_bus +
              (addr_t)(JPG_STR.p_curr_pos - JPG_STR.p_start_of_buffer)) & (~mask);

  if(dec_cont->low_latency)
    dec_cont->ll_strm_bus_address = addr_tmp;

  SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_RLC_VLC_BASE, addr_tmp);
  //SET_ADDR_REG(dec_cont->jpeg_regs, HWIF_RLC_VLC_BASE, JPG_STR.stream_bus);
  dec_cont->jpeg_hw_start_bus = addr_tmp;

  APITRACEDEBUG("INTERNAL: Stream bus start 0x%08lx\n",
                          JPG_STR.stream_bus);

  /* calculate and set stream start bit to hw */

  /* change current pos to bus address style */
  /* remove three lowest bits and add the difference to bitPosInWord */
  /* used as bit pos in word not as bit pos in byte actually... */
#if 0
  switch ((addr_t) JPG_STR.p_curr_pos & (7)) {
  case 0:
    break;
  case 1:
    JPG_STR.bit_pos_in_byte += 8;
    break;
  case 2:
    JPG_STR.bit_pos_in_byte += 16;
    break;
  case 3:
    JPG_STR.bit_pos_in_byte += 24;
    break;
  case 4:
    JPG_STR.bit_pos_in_byte += 32;
    break;
  case 5:
    JPG_STR.bit_pos_in_byte += 40;
    break;
  case 6:
    JPG_STR.bit_pos_in_byte += 48;
    break;
  case 7:
    JPG_STR.bit_pos_in_byte += 56;
    break;
  default:
    ASSERT(0);
    break;
  }
#endif

  JPG_STR.bit_pos_in_byte += ((addr_t) JPG_STR.p_curr_pos & mask) * 8;
  SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_BIT,
                 JPG_STR.bit_pos_in_byte);

  /* set up stream length for HW.
   * length = size of original buffer - stream we already decoded in SW */
  JPG_STR.p_curr_pos = (u8 *) ((addr_t) JPG_STR.p_curr_pos & (~mask));

  if(dec_cont->info.input_streaming) {
    amount_of_stream = (dec_cont->info.input_buffer_len -
                        (u32) (JPG_STR.p_curr_pos - JPG_STR.p_start_of_stream));

    if(dec_cont->low_latency) {
      dec_cont->ll_strm_len = amount_of_stream;
      SetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_LEN, 0);
    } else {
      SetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_LEN, amount_of_stream);
    }
    SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_BUFFER_LEN, amount_of_stream);
    SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_OFFSET, 0);
    //SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_BUFFER_LEN, dec_cont->info.input_buffer_len);
    //SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_OFFSET, (addr_tmp - JPG_STR.stream_bus) & (~mask));
  } else {
    amount_of_stream = (JPG_STR.stream_length -
                        (u32) ((JPG_STR.read_bits - JPG_STR.bit_pos_in_byte) >> 3));

    if(dec_cont->low_latency) {
      dec_cont->ll_strm_len = amount_of_stream;
      SetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_LEN, 0);
    } else {
      SetDecRegister(dec_cont->jpeg_regs, HWIF_STREAM_LEN, amount_of_stream);
    }
    SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_BUFFER_LEN, amount_of_stream);
    SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_OFFSET, 0);
    //SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_START_OFFSET, (addr_tmp - JPG_STR.stream_bus) & (~mask));
    //SetDecRegister(dec_cont->jpeg_regs, HWIF_STRM_BUFFER_LEN, JPG_STR.strm_buff_size);

    /* because no input streaming, frame should be ready during decoding this buffer */
    dec_cont->info.stream_end = 1;
  }

  if(dec_cont->low_latency) {
    dec_cont->first_update = 1;
    dec_cont->update_reg_flag = 1;
  }

  JPG_STR.read_bits -= JPG_STR.bit_pos_in_byte;

  /*************** Set swreg4 data ************/
  APITRACEDEBUG("%s","INTERNAL: Set stream last buffer bit\n");
  SetDecRegister(dec_cont->jpeg_regs, HWIF_JPEG_STREAM_ALL,
                 dec_cont->info.stream_end);

  APITRACEDEBUG("INTERNAL: JPG_STR.stream_length %d\n",
                          JPG_STR.stream_length);
  APITRACEDEBUG("INTERNAL: JPG_STR.p_curr_pos 0x%p\n",
                          JPG_STR.p_curr_pos);
  APITRACEDEBUG("INTERNAL: JPG_STR.p_start_of_stream 0x%p\n",
                          JPG_STR.p_start_of_stream);
  APITRACEDEBUG("INTERNAL: JPG_STR.bit_pos_in_byte 0x%08x\n",
                          JPG_STR.bit_pos_in_byte);
#ifdef SUPPORT_DMA
  DWLDMATransData((addr_t)dec_cont->stream.stream_bus,
                  (void *)dec_cont->stream.p_start_of_buffer,
                  dec_cont->stream.strm_buff_size, HOST_TO_DEVICE);
#endif

  return;

#undef JPG_STR

}

/*------------------------------------------------------------------------------

        Function name: JpegDecAllocateResidual

        Functional description:
          Allocates residual buffer

        Inputs:
          JpegDecContainer *dec_cont  Pointer to DecData structure

        Outputs:
          OK
          DEC_MEMFAIL

------------------------------------------------------------------------------*/
enum DecRet JpegDecAllocateResidual(JpegDecContainer * dec_cont) {

  i32 tmp = DEC_ERROR;
  u32 block_coeff_size = 0, total_coeff_size = 0;
  u32 i;
  const struct DecHwFeatures *hw_feature = NULL;
  DWLGetReleaseHwFeaturesByClientType(DWL_CLIENT_TYPE_JPEG_DEC, (const void **)&hw_feature);
  ASSERT(dec_cont);

  if(dec_cont->info.operation_type == JPEG_PROGRESSIVE) {

    if (dec_cont->frame.P == 8)
      block_coeff_size = JPEGDEC_COEFF_SIZE;
    else
      block_coeff_size = JPEGDEC_COEFF_SIZE_12BIT;

    for(i = 0; i < dec_cont->frame.Nf; i++) {
      total_coeff_size += NEXT_MULTIPLE_1(dec_cont->frame.num_blocks[i] * block_coeff_size, 384);
    }
    /* allocate coefficient buffer */
    dec_cont->info.p_coeff_base.mem_type = DWL_MEM_TYPE_DMA_DEVICE_ONLY | DWL_MEM_TYPE_VPU_ONLY;

    if (dec_cont->info.p_coeff_base.logical_size < total_coeff_size) {

      if (dec_cont->info.p_coeff_base.logical_size)
        DWLFreeLinear(dec_cont->dwl, &(dec_cont->info.p_coeff_base));
      tmp = DWLMallocLinear(dec_cont->dwl, (sizeof(u8) * total_coeff_size), &(dec_cont->info.p_coeff_base));
      if(tmp == -1) {
        return (DEC_MEMFAIL);
      }
    }
#ifdef PJPEG_COMPONENT_TRACE
    pjpeg_coeff_base = dec_cont->info.p_coeff_base.virtual_address;
    pjpeg_coeff_size = total_coeff_size;
#endif
    dec_cont->pjpeg_coeff_size_for_cache = total_coeff_size;
    APITRACEDEBUG("ALLOCATE: COEFF virtual %p bus %08lx\n",
                            (void*)dec_cont->info.p_coeff_base.virtual_address,
                            dec_cont->info.p_coeff_base.bus_address);
  }

  if(dec_cont->pp_instance != NULL) {
    dec_cont->pp_config_query.tiled_mode = 0;
    dec_cont->PPConfigQuery(dec_cont->pp_instance, &dec_cont->pp_config_query);

    dec_cont->pp_control.use_pipeline =
      dec_cont->pp_config_query.pipeline_accepted;

    if(!dec_cont->pp_control.use_pipeline) {
      dec_cont->image.size_luma = (dec_cont->info.X * dec_cont->info.Y);
      if(dec_cont->image.size_chroma) {
        if(dec_cont->info.y_cb_cr_mode == JPEGDEC_YUV420)
          dec_cont->image.size_chroma = (dec_cont->image.size_luma / 2);
        else if(dec_cont->info.y_cb_cr_mode == JPEGDEC_YUV422 ||
                dec_cont->info.y_cb_cr_mode == JPEGDEC_YUV440)
          dec_cont->image.size_chroma = dec_cont->image.size_luma;
      }
    }
  }

  /* if pipelined PP -> decoder's output is not written external memory */
  if(dec_cont->pp_instance == NULL ||
      (dec_cont->pp_instance != NULL && !dec_cont->pp_control.use_pipeline)) {
    if(DWL_DEVMEM_COMPARE(dec_cont->info.given_out_luma, DWL_DEVMEM_INIT)) {
      /* allocate luminance output */

      /* luma bus address to output */
      dec_cont->info.out_luma = dec_cont->asic_buff.out_luma_buffer;
      if (dec_cont->pp_enabled) {
        dec_cont->info.out_pp_luma = dec_cont->asic_buff.pp_luma_buffer;
        dec_cont->info.out_pp_chroma = dec_cont->asic_buff.pp_chroma_buffer;
      }
    } else {
      dec_cont->asic_buff.out_luma_buffer.virtual_address =
        dec_cont->info.given_out_luma.virtual_address;
      dec_cont->asic_buff.out_luma_buffer.bus_address =
        dec_cont->info.given_out_luma.bus_address;

      dec_cont->info.out_pp_luma = dec_cont->asic_buff.pp_luma_buffer =
      dec_cont->info.given_out_luma;
      dec_cont->info.out_pp_chroma = dec_cont->asic_buff.pp_chroma_buffer =
        dec_cont->info.given_out_luma; //dec_cont->info.given_out_chroma;
      /* luma bus address to output */
      dec_cont->info.out_luma = dec_cont->asic_buff.out_luma_buffer;

      /* Chroma output buffer address */
      dec_cont->asic_buff.out_chroma_buffer.virtual_address =
        dec_cont->info.given_out_chroma.virtual_address;
      dec_cont->asic_buff.out_chroma_buffer.bus_address =
        dec_cont->info.given_out_chroma.bus_address;

      /* Chroma bus address to output */
      dec_cont->info.out_chroma = dec_cont->asic_buff.out_luma_buffer; //out_chroma_buffer;

      /* when PP is enabled, because user just allocate one set of output buffer,
              output buffer just use as PP output buffer */
      if (dec_cont->pp_enabled) {
        dec_cont->asic_buff.pp_luma_buffer = dec_cont->info.out_luma;
        dec_cont->asic_buff.pp_chroma_buffer = dec_cont->info.out_chroma;

        dec_cont->info.out_pp_luma = dec_cont->asic_buff.pp_luma_buffer;
        dec_cont->info.out_pp_chroma = dec_cont->asic_buff.pp_chroma_buffer;

        /* Just to set chroma offset. */
        CalcPpUnitBufferSize(dec_cont->ppu_cfg, 0);
      }

      /* flag to release */
      dec_cont->info.user_alloc_mem = 1;
    }

    APITRACEDEBUG("ALLOCATE: Luma virtual %p bus %08lx\n",
                            (void*)dec_cont->asic_buff.out_luma_buffer.virtual_address,
                            dec_cont->asic_buff.out_luma_buffer.bus_address);

    /* allocate chrominance output */
    if(dec_cont->image.size_chroma) {

      dec_cont->asic_buff.out_chroma_buffer.virtual_address =
        dec_cont->info.given_out_chroma.virtual_address;
      dec_cont->asic_buff.out_chroma_buffer.bus_address =
        dec_cont->info.given_out_chroma.bus_address;
      dec_cont->asic_buff.out_chroma_buffer2.virtual_address =
        dec_cont->info.given_out_chroma2.virtual_address;
      dec_cont->asic_buff.out_chroma_buffer2.bus_address =
        dec_cont->info.given_out_chroma2.bus_address;



      /* chroma bus address to output */
      dec_cont->info.out_chroma = dec_cont->asic_buff.out_chroma_buffer;
      dec_cont->info.out_chroma2 = dec_cont->asic_buff.out_chroma_buffer2;

      APITRACEDEBUG("ALLOCATE: Chroma virtual %p bus %08lx\n",
                              (void*)dec_cont->asic_buff.out_chroma_buffer.virtual_address,
                              dec_cont->asic_buff.out_chroma_buffer.bus_address);
    }
  }
  return DEC_OK;
}

/*------------------------------------------------------------------------------

        Function name: JpegDecSliceSizeCalculation

        Functional description:
          Calculates slice size

        Inputs:
          JpegDecContainer *dec_cont

        Outputs:
          void

------------------------------------------------------------------------------*/
void JpegDecSliceSizeCalculation(JpegDecContainer * dec_cont) {

  if(((dec_cont->info.SliceCount +
       1) * (dec_cont->info.slice_mb_set_value * 16)) > dec_cont->info.Y) {
    dec_cont->info.slice_height = ((dec_cont->info.Y / 16) -
                                   (dec_cont->info.SliceCount *
                                    dec_cont->info.slice_height));
  } else {
    /* TODO! other sampling formats also than YUV420 */
    if(dec_cont->info.operation_type == JPEG_PROGRESSIVE &&
        dec_cont->info.component_id != 0)
      dec_cont->info.slice_height = dec_cont->info.slice_mb_set_value / 2;
    else
      dec_cont->info.slice_height = dec_cont->info.slice_mb_set_value;
  }
}


#if 0
/*------------------------------------------------------------------------------

        Function name: JpegDecWriteTablesUnified

        Functional description:
          Writes q/ac/dc tables to the HW format as specified in HW regs

        Inputs:
          JpegDecContainer *dec_cont

        Outputs:
          void

------------------------------------------------------------------------------*/
void JpegDecWriteTablesUnified(JpegDecContainer * dec_cont) {

#define JPG_SCN     dec_cont->scan
#define JPG_VLC     dec_cont->vlc
#define JPG_QTB     dec_cont->quant
#define JPG_FRM     dec_cont->frame

  u32 i = 0, j = 0;
  u32 table_word = 0;
  u16 table_tmp[64] = { 0 };
  u16 *p_tmp;
  u32 *p_table_base = NULL;
  u32 first = 0, count = 0;
  u32 len = 0, num_words = 0;
  u32 *vals;
  u32 *p_table;
  u32 dc_table = 0;
  u32 core_id = dec_cont->b_mc ? dec_cont->core_id : 0;
  u8 *val_table0;
  u32 *val_table1;
  u32 k = 0;

  ASSERT(dec_cont);
  ASSERT(dec_cont->frame.p_table_base[core_id].virtual_address);
  ASSERT(dec_cont->frame.p_table_base[core_id].bus_address);
  ASSERT(dec_cont->frame.p_table_base[core_id].size);

  /* Reset the table memory */
  (void) DWLmemset(dec_cont->frame.p_table_base[core_id].virtual_address, 0,
                   (sizeof(u8) * dec_cont->frame.table_size));

  p_table_base = dec_cont->frame.p_table_base[core_id].virtual_address;

  /* Prepare all QP tables for PJPEG */
  if(dec_cont->frame.Nf == 1) {
    first = dec_cont->info.component_id;
    count = 1;
  } else {
    first = 0;
    count = 3;
  }

  /* QP tables for all components */
  for(j = first; j < first + count; j++) {
    switch (JPG_FRM.component[j].Tq) {
    case 0:
      p_table = JPG_QTB.table0;
    case 1:
      p_table = JPG_QTB.table1;
    case 2:
      p_table = JPG_QTB.table2;
    case 3:
      p_table = JPG_QTB.table3;

    }

    for(i = 0; i < 64; i++) {
      table_tmp[zz_order[i]] = (u16) p_table[i];
    }

    p_tmp = table_tmp;
    if (JPG_QTB.Pq == 0) {
      for(i = 0; i < 16; i++) {
        table_word = (((u8)p_tmp[0]) << 24) | (((u8)p_tmp[1]) << 16) |
                     (((u8)p_tmp[2]) << 8) | (((u8)p_tmp[3]) << 0);
        *p_table_base++ = table_word;
        p_tmp += 4;
      }
    } else {
      for(i = 0; i < 16; i++) {
        table_word = (p_tmp[0] << 16) | (p_tmp[1] << 0);
        *p_table_base++ = table_word;
        p_tmp += 2;
        table_word = (p_tmp[2] << 16) | (p_tmp[3] << 0);
        *p_table_base++ = table_word;
        p_tmp += 2;
      }
    }
  }

  /* set pointer */
  u8 *ac_table_base = (u8 *)dec_cont->frame.p_table_base[core_id].virtual_address +
      dec_cont->frame.Nf * (dec_cont->quant.Pq ?
      JPEGDEC_16BIT_QP_TABLE_SIZE : JPEGDEC_8BIT_QP_TABLE_SIZE);
  u8 *dc_table_base =  ac_table_base +
     (dec_cont->info.operation_type == JPEG_BASELINE ? 2 : 4) *
     (dec_cont->frame.P == 8 ? 162 : 226);

  for(i = 0; i < (dec_cont->info.operation_type == JPEG_BASELINE ? 4 : 8); i++) {
    if(i < (dec_cont->info.operation_type == JPEG_BASELINE ? 2 : 4)) { /* DC */
      dc_table = 1;
      num_words = (dec_cont->frame.P == 8) ? 12 : 16;
      switch (i) {
      case 0:
        vals = JPG_VLC.dc_table0.vals;
        len = JPG_VLC.dc_table0.table_length;
        p_table_base = (u32 *)dc_table_base + 0 * (num_words >> 2);
        break;
      case 1:
        vals = JPG_VLC.dc_table1.vals;
        len = JPG_VLC.dc_table1.table_length;
        p_table_base = (u32 *)dc_table_base + 1 * (num_words >> 2);
        break;
      case 2:
        vals = JPG_VLC.dc_table2.vals;
        len = JPG_VLC.dc_table2.table_length;
        p_table_base = (u32 *)dc_table_base + 2 * (num_words >> 2);
        break;
      default:
        vals = JPG_VLC.dc_table3.vals;
        len = JPG_VLC.dc_table3.table_length;
        p_table_base = (u32 *)dc_table_base + 3 * (num_words >> 2);
        break;
      }
    } else {
      num_words = (dec_cont->frame.P == 8) ? 162 : 226;
      switch (i - (dec_cont->info.operation_type == JPEG_BASELINE ? 2 : 4)) {
      case 0:
        vals = JPG_VLC.ac_table0.vals;
        len = JPG_VLC.ac_table0.table_length;
        p_table_base = (u32 *)ac_table_base + 0 * (num_words >> 2);
        break;
      case 1:
        vals = JPG_VLC.ac_table1.vals;
        len = JPG_VLC.ac_table1.table_length;
        p_table_base = (u32 *)ac_table_base + 1 * (num_words >> 2);
        break;
      case 2:
        vals = JPG_VLC.ac_table2.vals;
        len = JPG_VLC.ac_table2.table_length;
        p_table_base = (u32 *)ac_table_base + 2 * (num_words >> 2);
        break;
      default:
        vals = JPG_VLC.ac_table3.vals;
        len = JPG_VLC.ac_table3.table_length;
        p_table_base = (u32 *)ac_table_base + 3 * (num_words >> 2);
        break;
      }
    }

    val_table0 = (u8 *)p_table_base;
    val_table1 = vals;
    k = 0;

    if (dc_table == 0) {
      if (i == 2 || i == 4 || i == 6) {
        for(k = 0; k < num_words/4; k++) {
          val_table0[k*4+0] = ((k*4+3) < len) ? val_table1[k*4+3] : 0;
          val_table0[k*4+1] = ((k*4+2) < len) ? val_table1[k*4+2] : 0;
          val_table0[k*4+2] = ((k*4+1) < len) ? val_table1[k*4+1] : 0;
          val_table0[k*4+3] = ((k*4+0) < len) ? val_table1[k*4+0] : 0;
        }
        k = num_words/4;
        val_table0[k*4+2] = ((k*4+1) < len) ? val_table1[k*4+1] : 0;
        val_table0[k*4+3] = ((k*4+0) < len) ? val_table1[k*4+0] : 0;
      } else {
        val_table0 += 2;
        val_table0[-2+0] = (1 < len) ? val_table1[1] : 0;
        val_table0[-2+1] = (0 < len) ? val_table1[0] : 0;

        for(k = 0; k < num_words/4; k++) {
          val_table0[k*4+0+2] = ((k*4+3+2) < len) ? val_table1[k*4+3+2] : 0;
          val_table0[k*4+1+2] = ((k*4+2+2) < len) ? val_table1[k*4+2+2] : 0;
          val_table0[k*4+2+2] = ((k*4+1+2) < len) ? val_table1[k*4+1+2] : 0;
          val_table0[k*4+3+2] = ((k*4+0+2) < len) ? val_table1[k*4+0+2] : 0;
        }
      }

    } else {
      for(k = 0; k < num_words/4; k++) {
        val_table0[k*4+0] = ((k*4+3) < len) ? val_table1[k*4+3] : 0;
        val_table0[k*4+1] = ((k*4+2) < len) ? val_table1[k*4+2] : 0;
        val_table0[k*4+2] = ((k*4+1) < len) ? val_table1[k*4+1] : 0;
        val_table0[k*4+3] = ((k*4+0) < len) ? val_table1[k*4+0] : 0;
      }
    }

    /* reset */
    dc_table = 0;
  }

#ifdef SUPPORT_DMA
  DWLDMATransData((addr_t)dec_cont->frame.p_table_base[core_id].bus_address,
                  (void *)dec_cont->frame.p_table_base[core_id].virtual_address,
                  dec_cont->frame.p_table_base[core_id].size, HOST_TO_DEVICE);
#endif

#undef JPG_SCN
#undef JPG_VLC
#undef JPG_QTB
#undef JPG_FRM

}
#endif


/*------------------------------------------------------------------------------
    Function name   : JpegRefreshRegs
    Description     :
    Return type     : void
    Argument        : PPContainer * ppC
------------------------------------------------------------------------------*/
void JpegRefreshRegs(JpegDecContainer * dec_cont) {
  u32 *dec_regs = dec_cont->jpeg_regs;

  if(dec_cont->vcmd_used) {
    DWLRefreshRegister(dec_cont->dwl, dec_cont->cmd_buf_id, dec_regs);
    if(dec_cont->b_mc)
      DWLVcmdMCRefreshStatusRegs(dec_cont->dwl, dec_regs, dec_cont->cmd_buf_id);
  }
  else {
    DWLReadRegs(dec_cont->dwl, dec_cont->core_id, 4*1, &dec_regs[1], DEC_X170_REGISTERS - 1);
  }
}

/*------------------------------------------------------------------------------
    Function name   : JpegFlushRegs
    Description     :
    Return type     : void
    Argument        : PPContainer * ppC
------------------------------------------------------------------------------*/
void JpegFlushRegs(JpegDecContainer * dec_cont) {
  u32 *dec_regs = dec_cont->jpeg_regs;

  if(dec_cont->vcmd_used) {
    DWLFlushRegister(dec_cont->dwl, dec_cont->cmd_buf_id, dec_cont->jpeg_regs,
                     dec_cont->mc_refresh_regs[dec_cont->core_id], dec_cont->core_id, (void *)dec_cont);
    return;
  }

#ifdef JPEGDEC_ASIC_TRACE
  {
    APITRACEDEBUG("%s","INTERNAL: REGS BEFORE HW ENABLE\n");
    PrintJPEGReg(dec_cont->jpeg_regs);
  }
#endif /* #ifdef JPEGDEC_ASIC_TRACE */

  DWLWriteRegs(dec_cont->dwl,dec_cont->core_id, 4 * 2, &dec_regs[2], DEC_X170_REGISTERS - 2, 1);
}

u32 JpegCheckHwStatus(JpegDecContainer *dec_cont)
{
   u32 tmp = 0;
   if (dec_cont->vcmd_used) {
     tmp = dec_cont->jpeg_regs[1];
   } else {
     tmp = DWLReadRegFromHw(dec_cont->dwl, dec_cont->core_id, 4 * 1);
   }

  if(tmp & 0x01)
    return 1;
  else
    return 0;
}

