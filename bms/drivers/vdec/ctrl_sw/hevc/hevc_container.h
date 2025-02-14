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

#ifndef HEVC_CONTAINER_H_
#define HEVC_CONTAINER_H_

#include "basetype.h"
#include "hevc_storage.h"
#include "hevc_fb_mngr.h"
#include "deccfg.h"
#include "decppif.h"
#include "dwl.h"
#include "input_queue.h"
#include "ppu.h"
#include "fifo.h"
#include "low_latency.h"
#include "commonfunction.h"

#ifdef RANDOM_CORRUPT_RFC
#include "stream_corrupt.h"
#endif

#if 0
enum DecBufferType {
  REFERENCE_BUFFER = 0, /* reference + compression table + DMV*/
  RASTERSCAN_OUT_BUFFER,
  DOWNSCALE_OUT_BUFFER,
  TILE_EDGE_BUFFER,  /* filter mem + bsd control mem */
  SEGMENT_MAP_BUFFER, /* segment map */
  MISC_LINEAR_BUFFER, /* tile info + prob table + entropy context counter */
  BUFFER_TYPE_NUM
};

#define IS_EXTERNAL_BUFFER(config, type) (((config) >> (type)) & 1)
#endif

/* asic interface */
struct HevcDecAsic {
  struct DWLLinearMem *out_buffer;
  struct DWLLinearMem misc_linear[MAX_ASIC_CORES];
  struct DWLLinearMem tile_edge[MAX_ASIC_CORES * 2];
  struct DWLLinearMem *out_pp_buffer;
  struct DWLLinearMem *out_dmv_buffer;
  u32 scaling_lists_offset;
  u32 tile_info_offset;
#ifdef USE_FAKE_RFC_TABLE
  u32 fake_table_offset;
  u32 fake_tbly_size;
  u32 fake_tblc_size;
#endif
  u32 filter_mem_offset[MAX_ASIC_CORES];
  u32 sao_mem_offset[MAX_ASIC_CORES];
  u32 bsd_control_mem_offset[MAX_ASIC_CORES];
  u32 rfc_offset[MAX_ASIC_CORES];
  u32 tile_edge_used_by[MAX_ASIC_CORES * 2];
  i32 chroma_qp_index_offset;
  i32 chroma_qp_index_offset2;
  u32 disable_out_writing;
  u32 asic_id;
};

struct StrmConsumedCallback {
  DecMCStreamConsumed *fn;
  const u8 *p_strm_buff; /* stream buffer passed in callback */
  const void *p_user_data; /* user data to be passed in callback */
};

struct HevcHwRdyCallbackArg {
  const u8 *stream;
  const void *p_user_data;
  u32 out_id;
  u32 dmv_out_id;
  struct DpbStorage *current_dpb;
  struct DWLLinearMem *pp_data;
  i32 ref_mem_idx[MAX_DPB_SIZE + 1];
  u32 ref_id[16];
  u32 pps_id;
  u32 sps_id;
};

struct HevcDecContainer {
  const void *checksum;

  enum {
    HEVCDEC_UNINITIALIZED,
    HEVCDEC_INITIALIZED,
    HEVCDEC_BUFFER_EMPTY,
    HEVCDEC_WAITING_FOR_BUFFER,
    HEVCDEC_ABORTED,
    HEVCDEC_NEW_HEADERS,
    HEVCDEC_EOS
  } dec_state;

  i32 core_id;
  u32 max_dec_pic_width;
  u32 max_dec_pic_height;
  u32 dpb_mode;
  u32 asic_running;
  u32 start_code_detected;

  enum DecErrorInfo error_info;
  enum DecErrorHandling error_handling;
  u32 error_policy;
  u32 error_ratio;
  u32 pic_number;
  const u8 *hw_stream_start;
  const u8 *hw_buffer;
  addr_t hw_stream_start_bus;
  addr_t hw_buffer_start_bus;
  u32 hw_buffer_length;
  u32 hw_bit_pos;
  u32 hw_length;
  u32 stream_pos_updated;
  u32 packet_decoded;

  u32 num_buffers; /* the buffer number specified by user */
  u32 use_ext_dpb_size; /* use dpb size which specified by user */
  /* flag to add an external dpb buffer when dpb size specified by user;
   * or flag to add an external pp buffer when added a new dpb buffer in
   * mode which the dpb size specified by user.*/
  u32 add_extra_ext_buf;

  u32 pp_enabled;
  u32 down_scale_x;
  u32 down_scale_y;
  u32 dscale_shift_x;
  u32 dscale_shift_y;

  PpUnitIntConfig ppu_cfg[DEC_MAX_PPU_COUNT];

  DelogoConfig delogo_params[2];
  u32 hevc_main10_support;
  u32 hevc_422_intra_support;

  u32 use_ringbuffer;
  u32 use_video_compressor;
  u32 compressor_bypass;

  const void *dwl; /* DWL instance */
  struct FrameBufferList fb_list;

  struct Storage storage;
  struct HevcDecAsic asic_buff[1];
  u32 hevc_regs[DEC_X170_REGISTERS];
  u32 mc_refresh_regs[MAX_ASIC_CORES][REDA_STATUS_REGS_COUNT];

  u32 ext_buffer_config;  /* Bit map config for external buffers. */
  u32 use_adaptive_buffers;
  u32 guard_size;
  u32 secure_mode;
  u32 heif_mode;
  u32 ext_buffer_size;    /* size of external buffers allocated already */
  u32 reset_dpb_done;

  u32 buffer_num_requested; /* total buffers requested */
  u32 ext_buffer_num;     /* num of buffers already added to decoder */
  u32 min_buffer_num;       /* minimum num of buffers needed */

  u32 next_buf_size;  /* size of the requested external buffer */
  u32 buf_num;        /* number of buffers (with size of next_buf_size) requested to be allocated externally */
  struct DWLLinearMem _buf_to_free; /* For internal temp use, holding the info of linear mem to be released. */
  struct DWLLinearMem *buf_to_free;
  enum DecBufferType buf_type;
  u32 buffer_index;

  u32 qp_output_enable;
  u32 dmv_output_enable;
  u32 auxinfo_offset;
  u32 resource_ready;
  struct DWLLinearMem tiled_buffers[MAX_PIC_BUFFERS];

  InputQueue pp_buffer_queue;
  u32 ext_min_buffer_num;
  u32 n_ext_buf_size;  /* size of external buffers added */
  struct DWLLinearMem ext_buffers[MAX_PIC_BUFFERS];  /* added external buffers descriptors*/
  u32 release_buffer;    /* there is still old external buffers need releasing */
  u32 abort;
  pthread_mutex_t protect_mutex;
  pthread_mutex_t dmv_buffer_mutex;
  pthread_cond_t dmv_buffer_cv;

#ifdef RANDOM_CORRUPT_RFC
  struct ErrorParams error_params;
#endif

  u32 hw_conceal;
  u32 disable_slice_mode;
  DecPicAlignment align;  /* buffer alignment for both reference/pp output */
  u32 low_latency;
  struct LLStrmInfo llstrminfo;

  /* multi-core relative params */
  u32 b_mc; /* flag to indicate MC mode status */
  u32 n_cores;
  u32 n_cores_available; /* cores available for HEVC */
  struct StrmConsumedCallback stream_consumed_callback;
  struct HevcHwRdyCallbackArg hw_rdy_callback_arg[MAX_ASIC_CORES];
  u32 prev_pp_width;
  u32 prev_pp_height;
  u32 partial_decoding;

  u32 vcmd_used;  /* flga to indicate VCMD is used.flga to indicate VCMD is used. */
  u32 cmdbuf_id;
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
  u32 skip_non_intra; /* flag to decode I frame only. */
  i8 max_temporal_layer; /* The maximum temporal layer that the VCD supports decoding(only hevc/h264/vvc). */
  FifoInst fifo_core;
  u32 mc_buf_id;  /* misc_linear/tile_edge index used for vcmd multicore. */
  u32 multi_frame_input_flag; /**< Specifies the input stream of decoder contains at least two frames. */

  enum {
    DEC_IDLE = 0,       /* DEC is idle */
    DEC_RUNNING         /* DEC is running */
  } dec_status[MAX_ASIC_CORES]; /* used to track each core's status in MC mode */

#ifdef FPGA_PERF_AND_BW
  DecPerfInfo perf_info;
#endif
  u32 core_mask;
};

#endif /* #ifdef HEVC_CONTAINER_H_ */
