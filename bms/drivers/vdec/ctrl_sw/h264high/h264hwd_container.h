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

#ifndef H264HWD_CONTAINER_H
#define H264HWD_CONTAINER_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "basetype.h"
#include "h264hwd_storage.h"
#include "h264hwd_util.h"
#include "deccfg.h"
#include "decppif.h"
#include "workaround.h"

#include "h264hwd_dpb_lock.h"
#include "input_queue.h"
#include "ppu.h"
#include "fifo.h"
#include "low_latency.h"
#include "commonfunction.h"

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

#define DEC_UNINITIALIZED   0U
#define DEC_INITIALIZED     1U
#define DEC_BUFFER_EMPTY    2U
#define DEC_NEW_HEADERS     3U
#define DEC_WAIT_FOR_BUFFER 4U


/* asic interface */
typedef struct DecAsicBuffers {
  u32 buff_status;
  struct DWLLinearMem mb_ctrl;
  struct DWLLinearMem mv;
  struct DWLLinearMem intra_pred;
  struct DWLLinearMem residual;
  struct DWLLinearMem *out_buffer;
  struct DWLLinearMem *out_pp_buffer;
  struct DWLLinearMem *out_dmv_buffer;
  struct DWLLinearMem cabac_init[MAX_ASIC_CORES];
  i32 ref_mem_idx[16+1];
  addr_t ref_pic_list[16+1];
  addr_t ref_dmv_list[16+1];
  u32 max_ref_frm;
  u32 filter_disable;
  i32 chroma_qp_index_offset;
  i32 chroma_qp_index_offset2;
  u32 current_mb;
  u32 not_coded_mask;
  u32 rlc_words;
  u32 pic_size_in_mbs;
  u32 whole_pic_concealed;
  u32 disable_out_writing;
  u32 enable_dmv_and_poc;
  addr_t default_ref_address;
  addr_t default_dmv_address;
#ifdef USE_FAKE_RFC_TABLE
  struct DWLLinearMem fake_rfc_tbl;
  u32 tbl_sizey;
  u32 tbl_sizec;
#endif
} DecAsicBuffers_t;

typedef struct {
  const u8 *stream;
  const void *p_user_data;
  u32 is_field_pic;
  u32 is_bottom_field;
  u32 out_id;
  u32 dmv_out_id;
  dpbStorage_t *current_dpb;
  struct DWLLinearMem *pp_data;
  i32 ref_mem_idx[16+1];
  u32 ref_id[16];
  u32 is_high10_mode;
  enum DecPicCodingType pic_code_type[2];
} H264HwRdyCallbackArg;

struct H264DecContainer {
  const void *checksum;
  u32 dec_stat;
  u32 nal_mode;
  u32 pic_number;
  u32 asic_running;
  u32 start_code_detected;
  u32 rlc_mode;
  u32 baseline_mode;
  u32 try_vlc;
  u32 hw_conceal;
  u32 disable_slice_mode;
  u32 reallocate;
  u8 *p_hw_stream_start;
  u8 *hw_buffer;
  addr_t hw_stream_start_bus;
  addr_t buff_start_bus;
  u32 buff_length;
  u32 first_mb_offset;
  u32 error_frame_au;
  u32 original_word;
  u32 hw_bit_pos;
  u32 hw_length;
  u32 stream_pos_updated;
  u32 nal_start_code;
  u32 mode_change;
  u32 gaps_checked_for_this;
  u32 packet_decoded;
  u32 force_rlc_mode;        /* by default stays 0, testing can set it to 1 for RLC mode */

  u32 h264_regs[TOTAL_X170_REGISTERS];
  u32 mc_refresh_regs[MAX_ASIC_CORES][REDA_STATUS_REGS_COUNT];
  storage_t storage;       /* h264bsd storage */
  DecAsicBuffers_t asic_buff[1];
  const void *dwl;         /* DWL instance */
  i32 core_id;
  u32 tiled_reference_enable;
  u32 h264_profile_support;
  u32 max_dec_pic_width;
  u32 max_dec_pic_height;
  u32 dpb_mode;

  u32 keep_hw_reserved;
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
  u32 skip_non_intra;  /* flag to decode I frame only */
  i8 max_temporal_layer; /* The maximum temporal layer that the VCD supports decoding(only hevc/h264/vvc). */

  workaround_t workarounds;
  u32 frame_num_mask; /* for workaround */
  u32 force_nal_mode;

  FrameBufferList fb_list;
  u32 b_mc; /* flag to indicate MC mode status */
  enum {
    INIT_MODE = 0,    /* status: initial mode */
    MC2SC_MODE,       /* status: indicate G2 MC mode is going to G1 SC mode... */
    SC_MODE           /* status: already converted to SC mode. */
  } convert_to_single_core_mode; /*flag to indicate G2 MC mode go to G1 SC mode*/
  u32 n_cores;
  u32 n_cores_available;
  struct {
    DecMCStreamConsumed *fn;
    const u8 *p_strm_buff; /* stream buffer passed in callback */
    const void *p_user_data; /* user data to be passed in callback */
  } stream_consumed_callback;

  H264HwRdyCallbackArg hw_rdy_callback_arg[MAX_ASIC_CORES];
  i32 poc[34];
  u32 next_buf_size;  /* size of the requested external buffer */
  u32 buf_num;        /* number of buffers (with size of next_buf_size) requested to be allocated externally */
  struct DWLLinearMem *buf_to_free;
  u32 buffer_index[2];
  u32 ext_min_buffer_num;
  u32 ext_buffer_num;  /* number of external buffers added */
  u32 n_ext_buf_size;        // size of external buffers added

  u32 b_mvc;
  struct DWLLinearMem ext_buffers[MAX_PIC_BUFFERS];  /* external buffers descriptors*/
  u32 abort;
  pthread_mutex_t protect_mutex;
  pthread_mutex_t dmv_buffer_mutex;
  pthread_cond_t dmv_buffer_cv;

  DecPicAlignment align;  /* buffer alignment for both reference/pp output */
  u32 packet_loss;  /* packet loss flag due to frame num gap */

  enum DecErrorInfo error_info;
  enum DecErrorHandling error_handling;
  u32 error_policy;
  u32 error_ratio;
  u32 use_video_compressor;
  u32 use_ringbuffer;
  u32 support_asofmo_stream; /* 1: support aso/fmo stream decoding, 0: not support aso/fmo stream decoding */

  /* For open B picture handling. */
  u32 first_entry_point;
  u32 entry_is_IDR;
  i32 entry_POC;
  u32 skip_b;

  u32 alloc_buffer;
  u32 pre_alloc_buffer[2];  /* 2 for multi-view */
  u32 no_decoding_buffer;
  u32 dec_result;
  u32 num_read_bytes;

  u32 use_adaptive_buffers;
  u32 n_guard_size;
  u32 secure_mode;

  u32 pp_enabled;     /* set to 1 to enable pp */
  u32 dscale_shift_x;
  u32 dscale_shift_y;

  PpUnitIntConfig ppu_cfg[DEC_MAX_PPU_COUNT];

  DelogoConfig delogo_params[2];
  u32 ppb_mode;   /* postposed picture buffer mode: 0 - FRAME, 1 - FIELD */

  InputQueue pp_buffer_queue;

  u32 low_latency;
  struct LLStrmInfo llstrminfo;

  u32 max_strm_len;
  u32 high10p_mode;
  u32 h264_high10p_support;
  u32 h264_422_intra_support;
  u32 prev_pp_width;
  u32 prev_pp_height;
  u32 partial_decoding;
  u32 qp_output_enable;
  u32 dmv_output_enable;
  u32 auxinfo_offset;
  u32 valid_flags;

  u32 vcmd_used;
  u32 cmdbuf_id;
  FifoInst fifo_core;
  u32 mc_buf_id;  /* cabac_mem index used for vcmd multicore. */
  u32 multi_frame_input_flag; /**< Specifies the input stream of decoder contains at least two frames. */
  struct strmInfo stream_info;

  enum {
    DEC_IDLE = 0,       /* DEC is idle */
    DEC_RUNNING         /* DEC is running */
  } dec_status[MAX_ASIC_CORES]; /* used to track each core's status in MC mode */

#ifdef FPGA_PERF_AND_BW
  DecPerfInfo perf_info;
#endif
  /* core mask that select to support G1 or G2 */
  u32 core_mask;
  /* core mask that can support G2 high10 stream from hardware feature */
  u32 g2_core_mask;
  /* core mask that can support G1 stream from hardware feature */
  u32 g1_core_mask;
};

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

#endif /* #ifdef H264HWD_CONTAINER_H */
