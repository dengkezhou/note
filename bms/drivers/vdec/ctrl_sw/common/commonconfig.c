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

#include "commonconfig.h"
#include "dwl.h"
#include "deccfg.h"
#include "dectypes.h"
#include "regdrv.h"
#include "sw_util.h"
#include "swreg_struct.h"

#ifdef _ASSERT_USED
#ifndef ASSERT
#include <assert.h>
#define ASSERT(expr) assert(expr)
#endif
#else
#define ASSERT(expr)
#endif

#define DEC_MODE_HEVC 12
#define DEC_MODE_VP9  13
#define DEC_MODE_AVS2 16
#define DEC_MODE_AV1  17
#define DEC_MODE_VVC  18

/* These are globals, so that test code can meddle with them. On production
 * they will always retain their values. */
u32 dec_stream_swap = HANTRODEC_STREAM_SWAP;
u32 dec_pic_swap = HANTRODEC_STREAM_SWAP;
u32 dec_dirmv_swap = HANTRODEC_STREAM_SWAP;

/* For VC8000D, HW need little endian but all G1 format write big endian
  As for HEVC and VP9, this value will be overwritten to 0. */
u32 dec_tab_swap = HANTRODEC_STREAM_SWAP_8 | HANTRODEC_STREAM_SWAP_16;
u32 dec_burst_length = DEC_X170_BUS_BURST_LENGTH;
u32 dec_bus_width = DEC_X170_BUS_WIDTH;
#ifdef DEC_X170_REFBU_SEQ
u32 dec_apf_treshold = DEC_X170_REFBU_NONSEQ / DEC_X170_REFBU_SEQ;
#else
u32 dec_apf_treshold = DEC_X170_REFBU_NONSEQ;
#endif /* DEC_X170_REFBU_SEQ */
u32 dec_apf_disable = DEC_X170_APF_DISABLE;

u32 dec_clock_gating = DEC_X170_INTERNAL_CLOCK_GATING;

u32 dec_timeout_cycles = HANTRODEC_TIMEOUT_OVERRIDE;
u32 dec_axi_id_rd = DEC_X170_AXI_ID_R;
u32 dec_axi_id_rd_unique_enable = DEC_X170_AXI_ID_R_E;
u32 dec_axi_id_wr = DEC_X170_AXI_ID_W;
u32 dec_axi_id_wr_unique_enable = DEC_X170_AXI_ID_W_E;

/* partial tb_cfg.dec_params parameters. */
struct DecParams dec_params = {
  .bus_burst_length = DEC_X170_BUS_BURST_LENGTH,
  .clk_gate_decoder = DEC_X170_INTERNAL_CLOCK_GATING,
  .non_seq_clk = DEC_X170_REFBU_NONSEQ,
  .seq_clk = DEC_X170_REFBU_SEQ,
#ifdef DEC_X170_REFBU_SEQ
  .apf_threshold_value = DEC_X170_REFBU_NONSEQ / DEC_X170_REFBU_SEQ,
#else
  .apf_threshold_value = DEC_X170_REFBU_NONSEQ,
#endif
  .axi_wr_outstand = 0,
  .axi_rd_outstand = 0
};

void SetCommonConfigRegs(u32 *regs) {
  /* Check that the register count define DEC_X170_REGISTERS is
   * big enough for the defined HW registers in hw_dec_reg_spec */
  ASSERT(hw_dec_reg_spec[HWIF_LAST_REG - 3][0] < DEC_X170_REGISTERS);

  /* set parameters defined in deccfg.h */
  SetDecRegister(regs, HWIF_DEC_STRM_SWAP, dec_stream_swap);
  SetDecRegister(regs, HWIF_DEC_PIC_SWAP, dec_pic_swap);
  SetDecRegister(regs, HWIF_DEC_DIRMV_SWAP, dec_dirmv_swap);

  if (GetDecRegister(regs, HWIF_DEC_MODE) == DEC_MODE_HEVC ||
      GetDecRegister(regs, HWIF_DEC_MODE) == DEC_MODE_VP9 ||
      GetDecRegister(regs, HWIF_DEC_MODE) == DEC_MODE_AVS2 ||
      GetDecRegister(regs, HWIF_DEC_MODE) == DEC_MODE_AV1 ||
      GetDecRegister(regs, HWIF_DEC_MODE) == DEC_MODE_VVC)
    SetDecRegister(regs, HWIF_DEC_TAB_SWAP, 0);
  else
    SetDecRegister(regs, HWIF_DEC_TAB_SWAP, dec_tab_swap);

  SetDecRegister(regs, HWIF_DEC_BUSWIDTH, dec_bus_width);
  SetDecRegister(regs, HWIF_DEC_MAX_BURST, dec_burst_length);

#if (HWIF_APF_SINGLE_PU_MODE)
  SetDecRegister(regs, HWIF_APF_SINGLE_PU_MODE, 1);
  SetDecRegister(regs, HWIF_APF_DISABLE, 1);
  SetDecRegister(regs, HWIF_APF_THRESHOLD, 0);
#elif(DEC_X170_APF_DISABLE)
  SetDecRegister(regs, HWIF_APF_SINGLE_PU_MODE, 0);
  SetDecRegister(regs, HWIF_APF_DISABLE, 1);
  SetDecRegister(regs, HWIF_APF_THRESHOLD, 0);
#else
  {
    u32 apf_tmp_threshold = dec_apf_treshold;
    SetDecRegister(regs, HWIF_APF_DISABLE, dec_apf_disable);
    if (apf_tmp_threshold > 63) apf_tmp_threshold = 63;
    SetDecRegister(regs, HWIF_APF_THRESHOLD, apf_tmp_threshold);
  }
#endif

#if (DEC_X170_USING_IRQ == 0)
  SetDecRegister(regs, HWIF_DEC_IRQ_DIS, 1);
#else
  SetDecRegister(regs, HWIF_DEC_IRQ_DIS, 0);
#endif

  SetDecRegister(regs, HWIF_DEC_OUT_EC_BYPASS, 0);

  /* Clock gating parameters */
  SetDecRegister(regs, HWIF_DEC_CLK_GATE_E, dec_clock_gating);

  /* set AXI RW IDs */
  SetDecRegister(regs, HWIF_DEC_AXI_RD_ID,
                 (dec_axi_id_rd & 0xFFU));
  SetDecRegister(regs, HWIF_DEC_AXI_WR_ID,
                 (dec_axi_id_wr & 0xFFU));

  SetDecRegister(regs, HWIF_EXT_TIMEOUT_OVERRIDE_E, dec_timeout_cycles ? 1 : 0);
  SetDecRegister(regs, HWIF_EXT_TIMEOUT_CYCLES, dec_timeout_cycles);

  SetDecRegister(regs, HWIF_TIMEOUT_OVERRIDE_E, dec_timeout_cycles ? 1 : 0);
  SetDecRegister(regs, HWIF_TIMEOUT_CYCLES, dec_timeout_cycles);
  SetDecRegister(regs, HWIF_EMD_THRESHOLD_OVERRIDE_E, dec_timeout_cycles ? 1 : 0);
  SetDecRegister(regs, HWIF_EMD_CYCLES_THRESHOLD, dec_timeout_cycles - 64);

  /* AXI outstanding threshold */
  if ( dec_params.axi_wr_outstand != 0 )
    SetDecRegister(regs, HWIF_AXI_WR_OSTD_THRESHOLD,
                  dec_params.axi_wr_outstand);
  else
    SetDecRegister(regs, HWIF_AXI_WR_OSTD_THRESHOLD,
                  DEC_X170_MAX_WR_OUTSTANDING_THRESHOLD);
  if ( dec_params.axi_rd_outstand != 0 )
    SetDecRegister(regs, HWIF_AXI_RD_OSTD_THRESHOLD,
                  dec_params.axi_rd_outstand);
  else
    SetDecRegister(regs, HWIF_AXI_RD_OSTD_THRESHOLD,
                  DEC_X170_MAX_RD_OUTSTANDING_THRESHOLD);

  /* set parameters with dec_params */
  SetDecRegister(regs, HWIF_DEC_CLK_GATE_E, dec_params.clk_gate_decoder ? 1 : 0);
  SetDecRegister(regs, HWIF_DEC_MAX_BURST, dec_params.bus_burst_length);

  SetDecRegister(regs, HWIF_DEC_OUT_SHAPER_E, 1);
  SetDecRegister(regs, HWIF_TILE_EDGE_READ_THRESHOLD, 2000);
}

void SetSwCtrl(u32 *regs, struct SwRegisters *sw_ctrl) {
  if (sw_ctrl->sw_dec_mode == DEC_MODE_AV1) {
    SetDecRegister(regs, HWIF_DEC_IRQ_STAT, 0);
    SetDecRegister(regs, HWIF_DEC_IRQ, sw_ctrl->sw_dec_irq);
    SetDecRegister(regs, HWIF_DEC_MODE, sw_ctrl->sw_dec_mode);
    SetDecRegister(regs, HWIF_SKIP_MODE, sw_ctrl->sw_skip_mode);
    SetDecRegister(regs, HWIF_DEC_OUT_EC_BYTE_WORD, sw_ctrl->sw_ec_word_align);
    SetDecRegister(regs, HWIF_DEC_OUT_DIS, sw_ctrl->sw_dec_out_dis);
    SetDecRegister(regs, HWIF_FILTERING_DIS, sw_ctrl->sw_filtering_dis);
    SetDecRegister(regs, HWIF_WRITE_MVS_E, sw_ctrl->sw_write_mvs_e);
    SetDecRegister(regs, HWIF_DEC_OUT_EC_BYPASS, sw_ctrl->sw_dec_out_ec_bypass);
    SetDecRegister(regs, HWIF_PIC_WIDTH_IN_CBS, sw_ctrl->sw_pic_width_in_cbs);
    SetDecRegister(regs, HWIF_PIC_HEIGHT_IN_CBS, sw_ctrl->sw_pic_height_in_cbs);
    SetDecRegister(regs, HWIF_REF_FRAMES, sw_ctrl->sw_ref_frames);
    SetDecRegister(regs, HWIF_PIC_WIDTH_PAD, sw_ctrl->sw_pic_width_pad);
    SetDecRegister(regs, HWIF_PIC_HEIGHT_PAD, sw_ctrl->sw_pic_height_pad);
    SetDecRegister(regs, HWIF_STRM_START_BIT, sw_ctrl->sw_strm_start_bit);
    SetDecRegister(regs, HWIF_TEMPOR_MVP_E, sw_ctrl->sw_tempor_mvp_e);
    SetDecRegister(regs, HWIF_DELTA_LF_RES_LOG, sw_ctrl->sw_delta_lf_res_log);
    SetDecRegister(regs, HWIF_DELTA_LF_MULTI, sw_ctrl->sw_delta_lf_multi);
    SetDecRegister(regs, HWIF_DELTA_LF_PRESENT, sw_ctrl->sw_delta_lf_present);
    SetDecRegister(regs, HWIF_PRESKIP_SEGID, sw_ctrl->sw_preskip_segid);
    SetDecRegister(regs, HWIF_DISABLE_CDF_UPDATE, sw_ctrl->sw_disable_cdf_update);
    SetDecRegister(regs, HWIF_ALLOW_WARP, sw_ctrl->sw_allow_warp);
    SetDecRegister(regs, HWIF_SUPERRES_IS_SCALED, sw_ctrl->sw_superres_is_scaled);
    SetDecRegister(regs, HWIF_SHOW_FRAME, sw_ctrl->sw_show_frame);
    SetDecRegister(regs, HWIF_SWITCHABLE_MOTION_MODE, sw_ctrl->sw_switchable_motion_mode);
    SetDecRegister(regs, HWIF_ENABLE_CDEF, sw_ctrl->sw_enable_cdef);
    SetDecRegister(regs, HWIF_ALLOW_MASKED_COMPOUND, sw_ctrl->sw_allow_masked_compound);
    SetDecRegister(regs, HWIF_ALLOW_INTERINTRA, sw_ctrl->sw_allow_interintra);
    SetDecRegister(regs, HWIF_ENABLE_INTRA_EDGE_FILTER, sw_ctrl->sw_enable_intra_edge_filter);
    SetDecRegister(regs, HWIF_ALLOW_FILTER_INTRA, sw_ctrl->sw_allow_filter_intra);
    SetDecRegister(regs, HWIF_ENABLE_JNT_COMP, sw_ctrl->sw_enable_jnt_comp);
    SetDecRegister(regs, HWIF_ENABLE_DUAL_FILTER, sw_ctrl->sw_enable_dual_filter);
    SetDecRegister(regs, HWIF_REDUCED_TX_SET_USED, sw_ctrl->sw_reduced_tx_set_used);
    SetDecRegister(regs, HWIF_ALLOW_SCREEN_CONTENT_TOOLS, sw_ctrl->sw_allow_screen_content_tools);
    SetDecRegister(regs, HWIF_ALLOW_INTRABC, sw_ctrl->sw_allow_intrabc);
    SetDecRegister(regs, HWIF_FORCE_INTERGER_MV, sw_ctrl->sw_force_interger_mv);
    SetDecRegister(regs, HWIF_ERROR_RESILIENT, sw_ctrl->sw_error_resilient);
    SetDecRegister(regs, HWIF_FILT_LEVEL_BASE_GT32, sw_ctrl->sw_filt_level_base_gt32);
    SetDecRegister(regs, HWIF_REF_SCALING_ENABLE, sw_ctrl->sw_ref_scaling_enable);
    SetDecRegister(regs, HWIF_STREAM_LEN, sw_ctrl->sw_stream_len);
    SetDecRegister(regs, HWIF_BLACKWHITE_E, sw_ctrl->sw_blackwhite_e);
    SetDecRegister(regs, HWIF_RANDOM_SEED, sw_ctrl->sw_random_seed);
    SetDecRegister(regs, HWIF_CHROMA_SCALING_FROM_LUMA, sw_ctrl->sw_chroma_scaling_from_luma);
    SetDecRegister(regs, HWIF_CLIP_TO_RESTRICTED_RANGE, sw_ctrl->sw_clip_to_restricted_range);
    SetDecRegister(regs, HWIF_OVERLAP_FLAG, sw_ctrl->sw_overlap_flag);
    SetDecRegister(regs, HWIF_NUM_CR_POINTS_B, sw_ctrl->sw_num_cr_points_b);
    SetDecRegister(regs, HWIF_NUM_CB_POINTS_B, sw_ctrl->sw_num_cb_points_b);
    SetDecRegister(regs, HWIF_NUM_Y_POINTS_B, sw_ctrl->sw_num_y_points_b);
    SetDecRegister(regs, HWIF_APPLY_GRAIN, sw_ctrl->sw_apply_grain);
    SetDecRegister(regs, HWIF_CDEF_BITS, sw_ctrl->sw_cdef_bits);
    SetDecRegister(regs, HWIF_CDEF_DAMPING, sw_ctrl->sw_cdef_damping);
    SetDecRegister(regs, HWIF_DELTA_Q_RES_LOG, sw_ctrl->sw_delta_q_res_log);
    SetDecRegister(regs, HWIF_DELTA_Q_PRESENT, sw_ctrl->sw_delta_q_present);
    SetDecRegister(regs, HWIF_SUPERRES_PIC_WIDTH, sw_ctrl->sw_superres_pic_width);
    SetDecRegister(regs, HWIF_IDR_PIC_E, sw_ctrl->sw_idr_pic_e);
    SetDecRegister(regs, HWIF_QUANT_BASE_QINDEX, sw_ctrl->sw_quant_base_qindex);
    SetDecRegister(regs, HWIF_BIT_DEPTH_Y_MINUS8, sw_ctrl->sw_bit_depth_y_minus8);
    SetDecRegister(regs, HWIF_BIT_DEPTH_C_MINUS8, sw_ctrl->sw_bit_depth_c_minus8);
    SetDecRegister(regs, HWIF_SCALING_SHIFT, sw_ctrl->sw_scaling_shift);
    SetDecRegister(regs, HWIF_CONTEXT_UPDATE_TILE_ID, sw_ctrl->sw_context_update_tile_id);
    SetDecRegister(regs, HWIF_LAST_ACTIVE_SEG, sw_ctrl->sw_last_active_seg);
    SetDecRegister(regs, HWIF_SCALE_DENOM_MINUS9, sw_ctrl->sw_scale_denom_minus9);
    SetDecRegister(regs, HWIF_MF3_TYPE, sw_ctrl->sw_mf3_type);
    SetDecRegister(regs, HWIF_MF2_TYPE, sw_ctrl->sw_mf2_type);
    SetDecRegister(regs, HWIF_MF1_TYPE, sw_ctrl->sw_mf1_type);
    SetDecRegister(regs, HWIF_REF6_SIGN_BIAS, sw_ctrl->sw_ref6_sign_bias);
    SetDecRegister(regs, HWIF_REF5_SIGN_BIAS, sw_ctrl->sw_ref5_sign_bias);
    SetDecRegister(regs, HWIF_REF4_SIGN_BIAS, sw_ctrl->sw_ref4_sign_bias);
    SetDecRegister(regs, HWIF_TILE_MC_TILE_START_X, sw_ctrl->sw_tile_mc_tile_start_x);
    SetDecRegister(regs, HWIF_NUM_TILE_COLS_8K, sw_ctrl->sw_num_tile_cols_8k);
    SetDecRegister(regs, HWIF_NUM_TILE_ROWS_8K_AV1, sw_ctrl->sw_num_tile_rows_8k_av1);
    SetDecRegister(regs, HWIF_TILE_ENABLE, sw_ctrl->sw_tile_enable);
    SetDecRegister(regs, HWIF_TILE_TRANSPOSE, sw_ctrl->sw_tile_transpose);
    SetDecRegister(regs, HWIF_DEC_TILE_SIZE_MAG, sw_ctrl->sw_dec_tile_size_mag);
    SetDecRegister(regs, HWIF_TRANSFORM_MODE, sw_ctrl->sw_transform_mode);
    SetDecRegister(regs, HWIF_TILE_MC_TILE_COL, sw_ctrl->sw_tile_mc_tile_col);
    SetDecRegister(regs, HWIF_MCOMP_FILT_TYPE, sw_ctrl->sw_mcomp_filt_type);
    SetDecRegister(regs, HWIF_HIGH_PREC_MV_E, sw_ctrl->sw_high_prec_mv_e);
    SetDecRegister(regs, HWIF_COMP_PRED_MODE, sw_ctrl->sw_comp_pred_mode);
    SetDecRegister(regs, HWIF_USE_TEMPORAL0_MVS, sw_ctrl->sw_use_temporal0_mvs);
    SetDecRegister(regs, HWIF_USE_TEMPORAL1_MVS, sw_ctrl->sw_use_temporal1_mvs);
    SetDecRegister(regs, HWIF_USE_TEMPORAL2_MVS, sw_ctrl->sw_use_temporal2_mvs);
    SetDecRegister(regs, HWIF_USE_TEMPORAL3_MVS, sw_ctrl->sw_use_temporal3_mvs);
    SetDecRegister(regs, HWIF_AV1_COMP_PRED_FIXED_REF, sw_ctrl->sw_av1_comp_pred_fixed_ref);
    SetDecRegister(regs, HWIF_MIN_CB_SIZE, sw_ctrl->sw_min_cb_size);
    SetDecRegister(regs, HWIF_MAX_CB_SIZE, sw_ctrl->sw_max_cb_size);
    SetDecRegister(regs, HWIF_SEG_QUANT_SIGN, sw_ctrl->sw_seg_quant_sign);
    SetDecRegister(regs, HWIF_QP_DELTA_Y_DC_AV1, sw_ctrl->sw_qp_delta_y_dc_av1);
    SetDecRegister(regs, HWIF_QP_DELTA_CH_DC_AV1, sw_ctrl->sw_qp_delta_ch_dc_av1);
    SetDecRegister(regs, HWIF_QP_DELTA_CH_AC_AV1, sw_ctrl->sw_qp_delta_ch_ac_av1);
    SetDecRegister(regs, HWIF_LAST_SIGN_BIAS, sw_ctrl->sw_last_sign_bias);
    SetDecRegister(regs, HWIF_LOSSLESS_E, sw_ctrl->sw_lossless_e);
    SetDecRegister(regs, HWIF_COMP_PRED_VAR_REF1_AV1, sw_ctrl->sw_comp_pred_var_ref1_av1);
    SetDecRegister(regs, HWIF_COMP_PRED_VAR_REF0_AV1, sw_ctrl->sw_comp_pred_var_ref0_av1);
    SetDecRegister(regs, HWIF_SEGMENT_TEMP_UPD_E, sw_ctrl->sw_segment_temp_upd_e);
    SetDecRegister(regs, HWIF_SEGMENT_UPD_E, sw_ctrl->sw_segment_upd_e);
    SetDecRegister(regs, HWIF_SEGMENT_E, sw_ctrl->sw_segment_e);
    SetDecRegister(regs, HWIF_FILT_LEVEL0, sw_ctrl->sw_filt_level0);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG0, sw_ctrl->sw_filt_level_delta0_seg0);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG0, sw_ctrl->sw_refpic_seg0);
    SetDecRegister(regs, HWIF_SKIP_SEG0, sw_ctrl->sw_skip_seg0);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG0, sw_ctrl->sw_filt_level_seg0);
    SetDecRegister(regs, HWIF_QUANT_SEG0, sw_ctrl->sw_quant_seg0);
    SetDecRegister(regs, HWIF_FILT_LEVEL1, sw_ctrl->sw_filt_level1);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG1, sw_ctrl->sw_filt_level_delta0_seg1);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG1, sw_ctrl->sw_refpic_seg1);
    SetDecRegister(regs, HWIF_SKIP_SEG1, sw_ctrl->sw_skip_seg1);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG1, sw_ctrl->sw_filt_level_seg1);
    SetDecRegister(regs, HWIF_QUANT_SEG1, sw_ctrl->sw_quant_seg1);
    SetDecRegister(regs, HWIF_FILT_LEVEL2, sw_ctrl->sw_filt_level2);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG2, sw_ctrl->sw_filt_level_delta0_seg2);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG2, sw_ctrl->sw_refpic_seg2);
    SetDecRegister(regs, HWIF_SKIP_SEG2, sw_ctrl->sw_skip_seg2);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG2, sw_ctrl->sw_filt_level_seg2);
    SetDecRegister(regs, HWIF_QUANT_SEG2, sw_ctrl->sw_quant_seg2);
    SetDecRegister(regs, HWIF_FILT_LEVEL3, sw_ctrl->sw_filt_level3);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG3, sw_ctrl->sw_filt_level_delta0_seg3);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG3, sw_ctrl->sw_refpic_seg3);
    SetDecRegister(regs, HWIF_SKIP_SEG3, sw_ctrl->sw_skip_seg3);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG3, sw_ctrl->sw_filt_level_seg3);
    SetDecRegister(regs, HWIF_QUANT_SEG3, sw_ctrl->sw_quant_seg3);
    SetDecRegister(regs, HWIF_LR_TYPE, sw_ctrl->sw_lr_type);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG4, sw_ctrl->sw_filt_level_delta0_seg4);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG4, sw_ctrl->sw_refpic_seg4);
    SetDecRegister(regs, HWIF_SKIP_SEG4, sw_ctrl->sw_skip_seg4);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG4, sw_ctrl->sw_filt_level_seg4);
    SetDecRegister(regs, HWIF_QUANT_SEG4, sw_ctrl->sw_quant_seg4);
    SetDecRegister(regs, HWIF_LR_UNIT_SIZE, sw_ctrl->sw_lr_unit_size);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG5, sw_ctrl->sw_filt_level_delta0_seg5);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG5, sw_ctrl->sw_refpic_seg5);
    SetDecRegister(regs, HWIF_SKIP_SEG5, sw_ctrl->sw_skip_seg5);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG5, sw_ctrl->sw_filt_level_seg5);
    SetDecRegister(regs, HWIF_QUANT_SEG5, sw_ctrl->sw_quant_seg5);
    SetDecRegister(regs, HWIF_MF1_LAST_OFFSET, sw_ctrl->sw_mf1_last_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG0, sw_ctrl->sw_global_mv_seg0);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG0, sw_ctrl->sw_filt_level_delta3_seg0);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG0, sw_ctrl->sw_filt_level_delta2_seg0);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG0, sw_ctrl->sw_filt_level_delta1_seg0);
    SetDecRegister(regs, HWIF_MF1_LAST2_OFFSET, sw_ctrl->sw_mf1_last2_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG1, sw_ctrl->sw_global_mv_seg1);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG1, sw_ctrl->sw_filt_level_delta3_seg1);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG1, sw_ctrl->sw_filt_level_delta2_seg1);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG1, sw_ctrl->sw_filt_level_delta1_seg1);
    SetDecRegister(regs, HWIF_MF1_LAST3_OFFSET, sw_ctrl->sw_mf1_last3_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG2, sw_ctrl->sw_global_mv_seg2);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG2, sw_ctrl->sw_filt_level_delta3_seg2);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG2, sw_ctrl->sw_filt_level_delta2_seg2);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG2, sw_ctrl->sw_filt_level_delta1_seg2);
    SetDecRegister(regs, HWIF_MF1_GOLDEN_OFFSET, sw_ctrl->sw_mf1_golden_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG3, sw_ctrl->sw_global_mv_seg3);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG3, sw_ctrl->sw_filt_level_delta3_seg3);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG3, sw_ctrl->sw_filt_level_delta2_seg3);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG3, sw_ctrl->sw_filt_level_delta1_seg3);
    SetDecRegister(regs, HWIF_MF1_BWDREF_OFFSET, sw_ctrl->sw_mf1_bwdref_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG4, sw_ctrl->sw_global_mv_seg4);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG4, sw_ctrl->sw_filt_level_delta3_seg4);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG4, sw_ctrl->sw_filt_level_delta2_seg4);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG4, sw_ctrl->sw_filt_level_delta1_seg4);
    SetDecRegister(regs, HWIF_MF1_ALTREF2_OFFSET, sw_ctrl->sw_mf1_altref2_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG5, sw_ctrl->sw_global_mv_seg5);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG5, sw_ctrl->sw_filt_level_delta3_seg5);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG5, sw_ctrl->sw_filt_level_delta2_seg5);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG5, sw_ctrl->sw_filt_level_delta1_seg5);
    SetDecRegister(regs, HWIF_MF1_ALTREF_OFFSET, sw_ctrl->sw_mf1_altref_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG6, sw_ctrl->sw_global_mv_seg6);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG6, sw_ctrl->sw_filt_level_delta3_seg6);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG6, sw_ctrl->sw_filt_level_delta2_seg6);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG6, sw_ctrl->sw_filt_level_delta1_seg6);
    SetDecRegister(regs, HWIF_MF2_LAST_OFFSET, sw_ctrl->sw_mf2_last_offset);
    SetDecRegister(regs, HWIF_GLOBAL_MV_SEG7, sw_ctrl->sw_global_mv_seg7);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA3_SEG7, sw_ctrl->sw_filt_level_delta3_seg7);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA2_SEG7, sw_ctrl->sw_filt_level_delta2_seg7);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA1_SEG7, sw_ctrl->sw_filt_level_delta1_seg7);
    SetDecRegister(regs, HWIF_QUANT_DELTA_V_DC, sw_ctrl->sw_quant_delta_v_dc);
    SetDecRegister(regs, HWIF_CB_MULT, sw_ctrl->sw_cb_mult);
    SetDecRegister(regs, HWIF_CB_LUMA_MULT, sw_ctrl->sw_cb_luma_mult);
    SetDecRegister(regs, HWIF_CB_OFFSET, sw_ctrl->sw_cb_offset);
    SetDecRegister(regs, HWIF_QUANT_DELTA_V_AC, sw_ctrl->sw_quant_delta_v_ac);
    SetDecRegister(regs, HWIF_CR_MULT, sw_ctrl->sw_cr_mult);
    SetDecRegister(regs, HWIF_CR_LUMA_MULT, sw_ctrl->sw_cr_luma_mult);
    SetDecRegister(regs, HWIF_CR_OFFSET, sw_ctrl->sw_cr_offset);
    SetDecRegister(regs, HWIF_FILT_SHARPNESS, sw_ctrl->sw_filt_sharpness);
    SetDecRegister(regs, HWIF_FILT_MB_ADJ_0, sw_ctrl->sw_filt_mb_adj_0);
    SetDecRegister(regs, HWIF_FILT_MB_ADJ_1, sw_ctrl->sw_filt_mb_adj_1);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_4, sw_ctrl->sw_filt_ref_adj_4);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_5, sw_ctrl->sw_filt_ref_adj_5);
    SetDecRegister(regs, HWIF_SKIP_REF0, sw_ctrl->sw_skip_ref0);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG6, sw_ctrl->sw_filt_level_delta0_seg6);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG6, sw_ctrl->sw_refpic_seg6);
    SetDecRegister(regs, HWIF_SKIP_SEG6, sw_ctrl->sw_skip_seg6);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG6, sw_ctrl->sw_filt_level_seg6);
    SetDecRegister(regs, HWIF_QUANT_SEG6, sw_ctrl->sw_quant_seg6);
    SetDecRegister(regs, HWIF_SKIP_REF1, sw_ctrl->sw_skip_ref1);
    SetDecRegister(regs, HWIF_FILT_LEVEL_DELTA0_SEG7, sw_ctrl->sw_filt_level_delta0_seg7);
    SetDecRegister(regs, HWIF_AV1_REFPIC_SEG7, sw_ctrl->sw_refpic_seg7);
    SetDecRegister(regs, HWIF_SKIP_SEG7, sw_ctrl->sw_skip_seg7);
    SetDecRegister(regs, HWIF_FILT_LEVEL_SEG7, sw_ctrl->sw_filt_level_seg7);
    SetDecRegister(regs, HWIF_QUANT_SEG7, sw_ctrl->sw_quant_seg7);
    SetDecRegister(regs, HWIF_REF0_WIDTH, sw_ctrl->sw_ref0_width);
    SetDecRegister(regs, HWIF_REF0_HEIGHT, sw_ctrl->sw_ref0_height);
    SetDecRegister(regs, HWIF_REF1_WIDTH, sw_ctrl->sw_ref1_width);
    SetDecRegister(regs, HWIF_REF1_HEIGHT, sw_ctrl->sw_ref1_height);
    SetDecRegister(regs, HWIF_REF2_WIDTH, sw_ctrl->sw_ref2_width);
    SetDecRegister(regs, HWIF_REF2_HEIGHT, sw_ctrl->sw_ref2_height);
    SetDecRegister(regs, HWIF_REF0_HOR_SCALE, sw_ctrl->sw_ref0_hor_scale);
    SetDecRegister(regs, HWIF_REF0_VER_SCALE, sw_ctrl->sw_ref0_ver_scale);
    SetDecRegister(regs, HWIF_REF1_HOR_SCALE, sw_ctrl->sw_ref1_hor_scale);
    SetDecRegister(regs, HWIF_REF1_VER_SCALE, sw_ctrl->sw_ref1_ver_scale);
    SetDecRegister(regs, HWIF_REF2_HOR_SCALE, sw_ctrl->sw_ref2_hor_scale);
    SetDecRegister(regs, HWIF_REF2_VER_SCALE, sw_ctrl->sw_ref2_ver_scale);
    SetDecRegister(regs, HWIF_REF3_HOR_SCALE, sw_ctrl->sw_ref3_hor_scale);
    SetDecRegister(regs, HWIF_REF3_VER_SCALE, sw_ctrl->sw_ref3_ver_scale);
    SetDecRegister(regs, HWIF_REF4_HOR_SCALE, sw_ctrl->sw_ref4_hor_scale);
    SetDecRegister(regs, HWIF_REF4_VER_SCALE, sw_ctrl->sw_ref4_ver_scale);
    SetDecRegister(regs, HWIF_REF5_HOR_SCALE, sw_ctrl->sw_ref5_hor_scale);
    SetDecRegister(regs, HWIF_REF5_VER_SCALE, sw_ctrl->sw_ref5_ver_scale);
    SetDecRegister(regs, HWIF_REF6_HOR_SCALE, sw_ctrl->sw_ref6_hor_scale);
    SetDecRegister(regs, HWIF_REF6_VER_SCALE, sw_ctrl->sw_ref6_ver_scale);
    SetDecRegister(regs, HWIF_REF3_WIDTH, sw_ctrl->sw_ref3_width);
    SetDecRegister(regs, HWIF_REF3_HEIGHT, sw_ctrl->sw_ref3_height);
    SetDecRegister(regs, HWIF_REF4_WIDTH, sw_ctrl->sw_ref4_width);
    SetDecRegister(regs, HWIF_REF4_HEIGHT, sw_ctrl->sw_ref4_height);
    SetDecRegister(regs, HWIF_REF5_WIDTH, sw_ctrl->sw_ref5_width);
    SetDecRegister(regs, HWIF_REF5_HEIGHT, sw_ctrl->sw_ref5_height);
    SetDecRegister(regs, HWIF_REF6_WIDTH, sw_ctrl->sw_ref6_width);
    SetDecRegister(regs, HWIF_REF6_HEIGHT, sw_ctrl->sw_ref6_height);
    SetDecRegister(regs, HWIF_QMLEVEL_Y, sw_ctrl->sw_qmlevel_y);
    SetDecRegister(regs, HWIF_MF2_GOLDEN_OFFSET, sw_ctrl->sw_mf2_golden_offset);
    SetDecRegister(regs, HWIF_MF2_LAST3_OFFSET, sw_ctrl->sw_mf2_last3_offset);
    SetDecRegister(regs, HWIF_MF2_LAST2_OFFSET, sw_ctrl->sw_mf2_last2_offset);
    SetDecRegister(regs, HWIF_QMLEVEL_U, sw_ctrl->sw_qmlevel_u);
    SetDecRegister(regs, HWIF_MF2_ALTREF_OFFSET, sw_ctrl->sw_mf2_altref_offset);
    SetDecRegister(regs, HWIF_MF2_ALTREF2_OFFSET, sw_ctrl->sw_mf2_altref2_offset);
    SetDecRegister(regs, HWIF_MF2_BWDREF_OFFSET, sw_ctrl->sw_mf2_bwdref_offset);
    SetDecRegister(regs, HWIF_QMLEVEL_V, sw_ctrl->sw_qmlevel_v);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_7, sw_ctrl->sw_filt_ref_adj_7);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_6, sw_ctrl->sw_filt_ref_adj_6);
    SetDecRegister(regs, HWIF_SUPERRES_LUMA_STEP, sw_ctrl->sw_superres_luma_step);
    SetDecRegister(regs, HWIF_SUPERRES_CHROMA_STEP, sw_ctrl->sw_superres_chroma_step);
    SetDecRegister(regs, HWIF_SUPERRES_INIT_LUMA_SUBPEL_X, sw_ctrl->sw_superres_init_luma_subpel_x);
    SetDecRegister(regs, HWIF_SUPERRES_INIT_CHROMA_SUBPEL_X, sw_ctrl->sw_superres_init_chroma_subpel_x);
    SetDecRegister(regs, HWIF_CDEF_LUMA_SECONDARY_STRENGTH, sw_ctrl->sw_cdef_luma_secondary_strength);
    SetDecRegister(regs, HWIF_CDEF_CHROMA_SECONDARY_STRENGTH, sw_ctrl->sw_cdef_chroma_secondary_strength);
    SetDecRegister(regs, HWIF_DEC_MULTICORE_MODE, sw_ctrl->sw_dec_multicore_mode);
    SetDecRegister(regs, HWIF_DEC_MULTICORE_E, sw_ctrl->sw_dec_multicore_e);
    SetDecRegister(regs, HWIF_DEC_WRITESTAT_E, sw_ctrl->sw_dec_writestat_e);
    SetDecRegister(regs, HWIF_DEC_MC_POLLMODE, sw_ctrl->sw_dec_mc_pollmode);
    SetDecRegister(regs, HWIF_DEC_MC_POLLTIME, sw_ctrl->sw_dec_mc_polltime);
    SetDecRegister(regs, HWIF_REF3_SIGN_BIAS, sw_ctrl->sw_ref3_sign_bias);
    SetDecRegister(regs, HWIF_REF2_SIGN_BIAS, sw_ctrl->sw_ref2_sign_bias);
    SetDecRegister(regs, HWIF_REF1_SIGN_BIAS, sw_ctrl->sw_ref1_sign_bias);
    SetDecRegister(regs, HWIF_REF0_SIGN_BIAS, sw_ctrl->sw_ref0_sign_bias);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_0, sw_ctrl->sw_filt_ref_adj_0);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_1, sw_ctrl->sw_filt_ref_adj_1);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_2, sw_ctrl->sw_filt_ref_adj_2);
    SetDecRegister(regs, HWIF_FILT_REF_ADJ_3, sw_ctrl->sw_filt_ref_adj_3);
    SetDecRegister(regs, HWIF_DEC_OUT_YBASE_MSB, sw_ctrl->sw_dec_out_ybase_msb);
    SetDecRegister(regs, HWIF_DEC_OUT_YBASE_LSB, sw_ctrl->sw_dec_out_ybase);
    SetDecRegister(regs, HWIF_REFER0_YBASE_MSB, sw_ctrl->sw_refer0_ybase_msb);
    SetDecRegister(regs, HWIF_REFER0_YBASE_LSB, sw_ctrl->sw_refer0_ybase);
    SetDecRegister(regs, HWIF_REFER1_YBASE_MSB, sw_ctrl->sw_refer1_ybase_msb);
    SetDecRegister(regs, HWIF_REFER1_YBASE_LSB, sw_ctrl->sw_refer1_ybase);
    SetDecRegister(regs, HWIF_REFER2_YBASE_MSB, sw_ctrl->sw_refer2_ybase_msb);
    SetDecRegister(regs, HWIF_REFER2_YBASE_LSB, sw_ctrl->sw_refer2_ybase);
    SetDecRegister(regs, HWIF_REFER3_YBASE_MSB, sw_ctrl->sw_refer3_ybase_msb);
    SetDecRegister(regs, HWIF_REFER3_YBASE_LSB, sw_ctrl->sw_refer3_ybase);
    SetDecRegister(regs, HWIF_REFER4_YBASE_MSB, sw_ctrl->sw_refer4_ybase_msb);
    SetDecRegister(regs, HWIF_REFER4_YBASE_LSB, sw_ctrl->sw_refer4_ybase);
    SetDecRegister(regs, HWIF_REFER5_YBASE_MSB, sw_ctrl->sw_refer5_ybase_msb);
    SetDecRegister(regs, HWIF_REFER5_YBASE_LSB, sw_ctrl->sw_refer5_ybase);
    SetDecRegister(regs, HWIF_REFER6_YBASE_MSB, sw_ctrl->sw_refer6_ybase_msb);
    SetDecRegister(regs, HWIF_REFER6_YBASE_LSB, sw_ctrl->sw_refer6_ybase);
    SetDecRegister(regs, HWIF_SEGMENT_READ_BASE_MSB, sw_ctrl->sw_segment_read_base_msb);
    SetDecRegister(regs, HWIF_SEGMENT_READ_BASE_LSB, sw_ctrl->sw_segment_read_base);
    SetDecRegister(regs, HWIF_GLOBAL_MODEL_BASE_MSB, sw_ctrl->sw_global_model_base_msb);
    SetDecRegister(regs, HWIF_GLOBAL_MODEL_BASE_LSB, sw_ctrl->sw_global_model_base);
    SetDecRegister(regs, HWIF_CDEF_COLBUF_BASE_MSB, sw_ctrl->sw_cdef_colbuf_base_msb);
    SetDecRegister(regs, HWIF_CDEF_COLBUF_BASE_LSB, sw_ctrl->sw_cdef_colbuf_base);
    SetDecRegister(regs, HWIF_CDEF_LEFT_COLBUF_BASE_MSB, sw_ctrl->sw_cdef_left_colbuf_base_msb);
    SetDecRegister(regs, HWIF_CDEF_LEFT_COLBUF_BASE_LSB, sw_ctrl->sw_cdef_left_colbuf_base);
    SetDecRegister(regs, HWIF_SUPERRES_COLBUF_BASE_MSB, sw_ctrl->sw_superres_colbuf_base_msb);
    SetDecRegister(regs, HWIF_SUPERRES_COLBUF_BASE_LSB, sw_ctrl->sw_superres_colbuf_base);
    SetDecRegister(regs, HWIF_LR_COLBUF_BASE_MSB, sw_ctrl->sw_lr_colbuf_base_msb);
    SetDecRegister(regs, HWIF_LR_COLBUF_BASE_LSB, sw_ctrl->sw_lr_colbuf_base);
    SetDecRegister(regs, HWIF_SUPERRES_LEFT_COLBUF_BASE_MSB, sw_ctrl->sw_superres_left_colbuf_base_msb);
    SetDecRegister(regs, HWIF_SUPERRES_LEFT_COLBUF_BASE_LSB, sw_ctrl->sw_superres_left_colbuf_base);
    SetDecRegister(regs, HWIF_FILMGRAIN_BASE_MSB, sw_ctrl->sw_filmgrain_base_msb);
    SetDecRegister(regs, HWIF_FILMGRAIN_BASE_LSB, sw_ctrl->sw_filmgrain_base);
    SetDecRegister(regs, HWIF_LR_LEFT_COLBUF_BASE_MSB, sw_ctrl->sw_lr_left_colbuf_base_msb);
    SetDecRegister(regs, HWIF_LR_LEFT_COLBUF_BASE_LSB, sw_ctrl->sw_lr_left_colbuf_base);
    SetDecRegister(regs, HWIF_RFC_COLBUF_BASE_MSB, sw_ctrl->sw_rfc_colbuf_base_msb);
    SetDecRegister(regs, HWIF_RFC_COLBUF_BASE_LSB, sw_ctrl->sw_rfc_colbuf_base);
    SetDecRegister(regs, HWIF_RFC_LEFT_COLBUF_BASE_MSB, sw_ctrl->sw_rfc_left_colbuf_base_msb);
    SetDecRegister(regs, HWIF_RFC_LEFT_COLBUF_BASE_LSB, sw_ctrl->sw_rfc_left_colbuf_base);
    SetDecRegister(regs, HWIF_DEC_OUT_CBASE_MSB, sw_ctrl->sw_dec_out_cbase_msb);
    SetDecRegister(regs, HWIF_DEC_OUT_CBASE_LSB, sw_ctrl->sw_dec_out_cbase);
    SetDecRegister(regs, HWIF_REFER0_CBASE_MSB, sw_ctrl->sw_refer0_cbase_msb);
    SetDecRegister(regs, HWIF_REFER0_CBASE_LSB, sw_ctrl->sw_refer0_cbase);
    SetDecRegister(regs, HWIF_REFER1_CBASE_MSB, sw_ctrl->sw_refer1_cbase_msb);
    SetDecRegister(regs, HWIF_REFER1_CBASE_LSB, sw_ctrl->sw_refer1_cbase);
    SetDecRegister(regs, HWIF_REFER2_CBASE_MSB, sw_ctrl->sw_refer2_cbase_msb);
    SetDecRegister(regs, HWIF_REFER2_CBASE_LSB, sw_ctrl->sw_refer2_cbase);
    SetDecRegister(regs, HWIF_REFER3_CBASE_MSB, sw_ctrl->sw_refer3_cbase_msb);
    SetDecRegister(regs, HWIF_REFER3_CBASE_LSB, sw_ctrl->sw_refer3_cbase);
    SetDecRegister(regs, HWIF_REFER4_CBASE_MSB, sw_ctrl->sw_refer4_cbase_msb);
    SetDecRegister(regs, HWIF_REFER4_CBASE_LSB, sw_ctrl->sw_refer4_cbase);
    SetDecRegister(regs, HWIF_REFER5_CBASE_MSB, sw_ctrl->sw_refer5_cbase_msb);
    SetDecRegister(regs, HWIF_REFER5_CBASE_LSB, sw_ctrl->sw_refer5_cbase);
    SetDecRegister(regs, HWIF_REFER6_CBASE_MSB, sw_ctrl->sw_refer6_cbase_msb);
    SetDecRegister(regs, HWIF_REFER6_CBASE_LSB, sw_ctrl->sw_refer6_cbase);
    SetDecRegister(regs, HWIF_SUPERRES_LUMA_STEP_INVRA, sw_ctrl->sw_superres_luma_step_invra);
    SetDecRegister(regs, HWIF_SUPERRES_CHROMA_STEP_INVRA, sw_ctrl->sw_superres_chroma_step_invra);
    SetDecRegister(regs, HWIF_REF0_GM_MODE, sw_ctrl->sw_ref0_gm_mode);
    SetDecRegister(regs, HWIF_MF3_LAST_OFFSET, sw_ctrl->sw_mf3_last_offset);
    SetDecRegister(regs, HWIF_CUR_LAST_OFFSET, sw_ctrl->sw_cur_last_offset);
    SetDecRegister(regs, HWIF_CUR_LAST_ROFFSET, sw_ctrl->sw_cur_last_roffset);
    SetDecRegister(regs, HWIF_REF1_GM_MODE, sw_ctrl->sw_ref1_gm_mode);
    SetDecRegister(regs, HWIF_MF3_LAST2_OFFSET, sw_ctrl->sw_mf3_last2_offset);
    SetDecRegister(regs, HWIF_CUR_LAST2_OFFSET, sw_ctrl->sw_cur_last2_offset);
    SetDecRegister(regs, HWIF_CUR_LAST2_ROFFSET, sw_ctrl->sw_cur_last2_roffset);
    SetDecRegister(regs, HWIF_REF2_GM_MODE, sw_ctrl->sw_ref2_gm_mode);
    SetDecRegister(regs, HWIF_MF3_LAST3_OFFSET, sw_ctrl->sw_mf3_last3_offset);
    SetDecRegister(regs, HWIF_CUR_LAST3_OFFSET, sw_ctrl->sw_cur_last3_offset);
    SetDecRegister(regs, HWIF_CUR_LAST3_ROFFSET, sw_ctrl->sw_cur_last3_roffset);
    SetDecRegister(regs, HWIF_REF3_GM_MODE, sw_ctrl->sw_ref3_gm_mode);
    SetDecRegister(regs, HWIF_MF3_GOLDEN_OFFSET, sw_ctrl->sw_mf3_golden_offset);
    SetDecRegister(regs, HWIF_CUR_GOLDEN_OFFSET, sw_ctrl->sw_cur_golden_offset);
    SetDecRegister(regs, HWIF_CUR_GOLDEN_ROFFSET, sw_ctrl->sw_cur_golden_roffset);
    SetDecRegister(regs, HWIF_REF4_GM_MODE, sw_ctrl->sw_ref4_gm_mode);
    SetDecRegister(regs, HWIF_MF3_BWDREF_OFFSET, sw_ctrl->sw_mf3_bwdref_offset);
    SetDecRegister(regs, HWIF_CUR_BWDREF_OFFSET, sw_ctrl->sw_cur_bwdref_offset);
    SetDecRegister(regs, HWIF_CUR_BWDREF_ROFFSET, sw_ctrl->sw_cur_bwdref_roffset);
    SetDecRegister(regs, HWIF_REF5_GM_MODE, sw_ctrl->sw_ref5_gm_mode);
    SetDecRegister(regs, HWIF_MF3_ALTREF2_OFFSET, sw_ctrl->sw_mf3_altref2_offset);
    SetDecRegister(regs, HWIF_CUR_ALTREF2_OFFSET, sw_ctrl->sw_cur_altref2_offset);
    SetDecRegister(regs, HWIF_CUR_ALTREF2_ROFFSET, sw_ctrl->sw_cur_altref2_roffset);
    SetDecRegister(regs, HWIF_REF6_GM_MODE, sw_ctrl->sw_ref6_gm_mode);
    SetDecRegister(regs, HWIF_MF3_ALTREF_OFFSET, sw_ctrl->sw_mf3_altref_offset);
    SetDecRegister(regs, HWIF_CUR_ALTREF_OFFSET, sw_ctrl->sw_cur_altref_offset);
    SetDecRegister(regs, HWIF_CUR_ALTREF_ROFFSET, sw_ctrl->sw_cur_altref_roffset);
    SetDecRegister(regs, HWIF_CDEF_LUMA_PRIMARY_STRENGTH, sw_ctrl->sw_cdef_luma_primary_strength);
    SetDecRegister(regs, HWIF_CDEF_CHROMA_PRIMARY_STRENGTH, sw_ctrl->sw_cdef_chroma_primary_strength);
    SetDecRegister(regs, HWIF_ERROR_CONCEAL_E, sw_ctrl->sw_error_conceal_e);
    SetDecRegister(regs, HWIF_DEC_OUT_DBASE_MSB, sw_ctrl->sw_dec_out_dbase_msb);
    SetDecRegister(regs, HWIF_DEC_OUT_DBASE_LSB, sw_ctrl->sw_dec_out_dbase);
    SetDecRegister(regs, HWIF_REFER0_DBASE_MSB, sw_ctrl->sw_refer0_dbase_msb);
    SetDecRegister(regs, HWIF_REFER0_DBASE_LSB, sw_ctrl->sw_refer0_dbase);
    SetDecRegister(regs, HWIF_REFER1_DBASE_MSB, sw_ctrl->sw_refer1_dbase_msb);
    SetDecRegister(regs, HWIF_REFER1_DBASE_LSB, sw_ctrl->sw_refer1_dbase);
    SetDecRegister(regs, HWIF_REFER2_DBASE_MSB, sw_ctrl->sw_refer2_dbase_msb);
    SetDecRegister(regs, HWIF_REFER2_DBASE_LSB, sw_ctrl->sw_refer2_dbase);
    SetDecRegister(regs, HWIF_REFER3_DBASE_MSB, sw_ctrl->sw_refer3_dbase_msb);
    SetDecRegister(regs, HWIF_REFER3_DBASE_LSB, sw_ctrl->sw_refer3_dbase);
    SetDecRegister(regs, HWIF_REFER4_DBASE_MSB, sw_ctrl->sw_refer4_dbase_msb);
    SetDecRegister(regs, HWIF_REFER4_DBASE_LSB, sw_ctrl->sw_refer4_dbase);
    SetDecRegister(regs, HWIF_REFER5_DBASE_MSB, sw_ctrl->sw_refer5_dbase_msb);
    SetDecRegister(regs, HWIF_REFER5_DBASE_LSB, sw_ctrl->sw_refer5_dbase);
    SetDecRegister(regs, HWIF_REFER6_DBASE_MSB, sw_ctrl->sw_refer6_dbase_msb);
    SetDecRegister(regs, HWIF_REFER6_DBASE_LSB, sw_ctrl->sw_refer6_dbase);
    SetDecRegister(regs, HWIF_TILE_BASE_MSB, sw_ctrl->sw_tile_base_msb);
    SetDecRegister(regs, HWIF_TILE_BASE_LSB, sw_ctrl->sw_tile_base);
    SetDecRegister(regs, HWIF_STREAM_BASE_MSB, sw_ctrl->sw_stream_base_msb);
    SetDecRegister(regs, HWIF_STREAM_BASE_LSB, sw_ctrl->sw_stream_base);
    SetDecRegister(regs, HWIF_PROB_TAB_OUT_BASE_MSB, sw_ctrl->sw_prob_tab_out_base_msb);
    SetDecRegister(regs, HWIF_PROB_TAB_OUT_BASE_LSB, sw_ctrl->sw_prob_tab_out_base);
    SetDecRegister(regs, HWIF_PROB_TAB_BASE_MSB, sw_ctrl->sw_prob_tab_base_msb);
    SetDecRegister(regs, HWIF_PROB_TAB_BASE_LSB, sw_ctrl->sw_prob_tab_base);
    SetDecRegister(regs, HWIF_TILE_MC_SYNC_CURR_BASE_MSB, sw_ctrl->sw_tile_mc_sync_curr_base_msb);
    SetDecRegister(regs, HWIF_TILE_MC_SYNC_CURR_BASE_LSB, sw_ctrl->sw_tile_mc_sync_curr_base);
    SetDecRegister(regs, HWIF_TILE_MC_SYNC_LEFT_BASE_MSB, sw_ctrl->sw_tile_mc_sync_left_base_msb);
    SetDecRegister(regs, HWIF_TILE_MC_SYNC_LEFT_BASE_LSB, sw_ctrl->sw_tile_mc_sync_left_base);
    SetDecRegister(regs, HWIF_DEC_VERT_FILT_BASE_MSB, sw_ctrl->sw_dec_vert_filt_base_msb);
    SetDecRegister(regs, HWIF_DEC_VERT_FILT_BASE_LSB, sw_ctrl->sw_dec_vert_filt_base);
    SetDecRegister(regs, HWIF_DEC_LEFT_VERT_FILT_BASE_MSB, sw_ctrl->sw_dec_left_vert_filt_base_msb);
    SetDecRegister(regs, HWIF_DEC_LEFT_VERT_FILT_BASE_LSB, sw_ctrl->sw_dec_left_vert_filt_base);
    SetDecRegister(regs, HWIF_DEC_BSD_CTRL_BASE_MSB, sw_ctrl->sw_dec_bsd_ctrl_base_msb);
    SetDecRegister(regs, HWIF_DEC_BSD_CTRL_BASE_LSB, sw_ctrl->sw_dec_bsd_ctrl_base);
    SetDecRegister(regs, HWIF_DEC_LEFT_BSD_CTRL_BASE_MSB, sw_ctrl->sw_dec_left_bsd_ctrl_base_msb);
    SetDecRegister(regs, HWIF_DEC_LEFT_BSD_CTRL_BASE_LSB, sw_ctrl->sw_dec_left_bsd_ctrl_base);
    SetDecRegister(regs, HWIF_DEC_OUT_TYBASE_MSB, sw_ctrl->sw_dec_out_tybase_msb);
    SetDecRegister(regs, HWIF_DEC_OUT_TYBASE_LSB, sw_ctrl->sw_dec_out_tybase);
    SetDecRegister(regs, HWIF_REFER0_TYBASE_MSB, sw_ctrl->sw_refer0_tybase_msb);
    SetDecRegister(regs, HWIF_REFER0_TYBASE_LSB, sw_ctrl->sw_refer0_tybase);
    SetDecRegister(regs, HWIF_REFER1_TYBASE_MSB, sw_ctrl->sw_refer1_tybase_msb);
    SetDecRegister(regs, HWIF_REFER1_TYBASE_LSB, sw_ctrl->sw_refer1_tybase);
    SetDecRegister(regs, HWIF_REFER2_TYBASE_MSB, sw_ctrl->sw_refer2_tybase_msb);
    SetDecRegister(regs, HWIF_REFER2_TYBASE_LSB, sw_ctrl->sw_refer2_tybase);
    SetDecRegister(regs, HWIF_REFER3_TYBASE_MSB, sw_ctrl->sw_refer3_tybase_msb);
    SetDecRegister(regs, HWIF_REFER3_TYBASE_LSB, sw_ctrl->sw_refer3_tybase);
    SetDecRegister(regs, HWIF_REFER4_TYBASE_MSB, sw_ctrl->sw_refer4_tybase_msb);
    SetDecRegister(regs, HWIF_REFER4_TYBASE_LSB, sw_ctrl->sw_refer4_tybase);
    SetDecRegister(regs, HWIF_REFER5_TYBASE_MSB, sw_ctrl->sw_refer5_tybase_msb);
    SetDecRegister(regs, HWIF_REFER5_TYBASE_LSB, sw_ctrl->sw_refer5_tybase);
    SetDecRegister(regs, HWIF_REFER6_TYBASE_MSB, sw_ctrl->sw_refer6_tybase_msb);
    SetDecRegister(regs, HWIF_REFER6_TYBASE_LSB, sw_ctrl->sw_refer6_tybase);
    SetDecRegister(regs, HWIF_DEC_OUT_TCBASE_MSB, sw_ctrl->sw_dec_out_tcbase_msb);
    SetDecRegister(regs, HWIF_DEC_OUT_TCBASE_LSB, sw_ctrl->sw_dec_out_tcbase);
    SetDecRegister(regs, HWIF_REFER0_TCBASE_MSB, sw_ctrl->sw_refer0_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER0_TCBASE_LSB, sw_ctrl->sw_refer0_tcbase);
    SetDecRegister(regs, HWIF_REFER1_TCBASE_MSB, sw_ctrl->sw_refer1_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER1_TCBASE_LSB, sw_ctrl->sw_refer1_tcbase);
    SetDecRegister(regs, HWIF_REFER2_TCBASE_MSB, sw_ctrl->sw_refer2_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER2_TCBASE_LSB, sw_ctrl->sw_refer2_tcbase);
    SetDecRegister(regs, HWIF_REFER3_TCBASE_MSB, sw_ctrl->sw_refer3_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER3_TCBASE_LSB, sw_ctrl->sw_refer3_tcbase);
    SetDecRegister(regs, HWIF_REFER4_TCBASE_MSB, sw_ctrl->sw_refer4_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER4_TCBASE_LSB, sw_ctrl->sw_refer4_tcbase);
    SetDecRegister(regs, HWIF_REFER5_TCBASE_MSB, sw_ctrl->sw_refer5_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER5_TCBASE_LSB, sw_ctrl->sw_refer5_tcbase);
    SetDecRegister(regs, HWIF_REFER6_TCBASE_MSB, sw_ctrl->sw_refer6_tcbase_msb);
    SetDecRegister(regs, HWIF_REFER6_TCBASE_LSB, sw_ctrl->sw_refer6_tcbase);
    SetDecRegister(regs, HWIF_STRM_BUFFER_LEN, sw_ctrl->sw_strm_buffer_len);
    SetDecRegister(regs, HWIF_STRM_START_OFFSET, sw_ctrl->sw_strm_start_offset);
    SetDecRegister(regs, HWIF_DEC_OUT_Y_STRIDE, sw_ctrl->sw_dec_out_y_stride);
    SetDecRegister(regs, HWIF_DEC_OUT_C_STRIDE, sw_ctrl->sw_dec_out_c_stride);
    SetDecRegister(regs, HWIF_DEC_ALIGNMENT, sw_ctrl->sw_dec_alignment);
    SetDecRegister(regs, HWIF_APF_DISABLE, sw_ctrl->sw_apf_disable);
    SetDecRegister(regs, HWIF_UNIQUE_ID, sw_ctrl->sw_unique_id);
  }
  SetDecRegister(regs, HWIF_DEC_E, 1);
}
