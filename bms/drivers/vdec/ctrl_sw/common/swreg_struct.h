#ifndef INCLUDE_SW_REGISTERS0_H_
#define INCLUDE_SW_REGISTERS0_H_

#include "basetype.h"

struct SwRegisters {
  u8 sw_dec_scan_rdy;
  u8 sw_dec_pic_inf;
  u8 sw_dec_tile_int;
  u8 sw_dec_line_cnt_int;
  u8 sw_dec_ext_timeout_int;
  u8 sw_dec_no_slice_int;
  u8 sw_dec_last_slice_int;
  u8 sw_dec_timeout;
  u8 sw_dec_slice_int;
  u8 sw_dec_error_int;
  u8 sw_dec_aso_int;
  u8 sw_dec_buffer_int;
  u8 sw_dec_bus_int;
  u8 sw_dec_rdy_int;
  u8 sw_dec_abort_int;
  u8 sw_dec_irq;
  u8 sw_dec_tile_int_e;
  u8 sw_dec_self_reset_dis;
  u8 sw_dec_abort_e;
  u8 sw_dec_irq_dis;
  u8 sw_dec_timeout_source;
  u8 sw_dec_bus_int_dis;
  u8 sw_dec_strm_corrupted;
  u8 sw_dec_e;
  u8 sw_dec_strm_swap;
  u8 sw_dec_pic_swap;
  u8 sw_dec_dirmv_swap;
  u8 sw_tiled_mode_msb;
  u8 sw_dec_tab_swap;
  u8 sw_dec_clk_gate_e;
  u8 sw_tiled_mode_lsb;
  u8 sw_drm_e;
  u8 sw_dec_mode;
  u8 sw_skip_mode;
  u8 sw_divx3_e;
  u8 sw_pjpeg_width_div16;
  u8 sw_pjpeg_e;
  u8 sw_pic_type;
  u8 sw_rlc_mode_e;
  u8 sw_pic_interlace_e;
  u8 sw_pjpeg_last_scan_e;
  u8 sw_jpeg_interleaved_e;
  u8 sw_pjpeg_component_id;
  u8 sw_pic_fieldmode_e;
  u8 sw_pic_b_e;
  u8 sw_pic_inter_e;
  u8 sw_pic_typeb;
  u8 sw_pic_topfield_e;
  u8 sw_fwd_interlace_e;
  u8 sw_sorenson_e;
  u8 sw_ref_topfield_e;
  u8 sw_ec_word_align;
  u8 sw_dec_out_dis;
  u8 sw_filtering_dis;
  u8 sw_webp_e;
  u8 sw_mvc_e;
  u8 sw_pic_fixed_quant;
  u8 sw_write_mvs_e;
  u8 sw_reftopfirst_e;
  u8 sw_seq_mbaff_e;
  u8 sw_picord_count_e;
  u8 sw_dec_out_ec_bypass;
  u8 sw_apf_one_pid;
  u8 sw_slice_dec_dis;
  u8 sw_ref_read_dis;
  u8 sw_l2_shaper_e;
  u8 sw_buffer_empty_int_e;
  u8 sw_block_buffer_mode_e;
  u8 sw_last_buffer_e;
  u16 sw_pic_width_in_cbs;
  u16 sw_pic_height_in_cbs;
  u16 sw_pic_mb_width;
  u8 sw_mb_width_off_v0;
  u8 sw_pic_mb_height_p;
  u8 sw_mb_height_off_v0;
  u8 sw_alt_scan_e_v0;
  u8 sw_topfieldfirst_e;
  u8 sw_alt_scan_e;
  u8 sw_ref_frames;
  u8 sw_pic_mb_w_ext;
  u8 sw_pic_mb_h_ext;
  u8 sw_pic_width_pad;
  u8 sw_pic_height_pad;
  u8 sw_pic_refer_flag;
  u8 sw_strm_start_bit;
  u8 sw_scaling_list_e;
  u8 sw_type1_quant_e;
  u8 sw_ch_qp_offset;
  u8 sw_ch_qp_offset2;
  u8 sw_sign_data_hide;
  u8 sw_tempor_mvp_e;
  u8 sw_max_cu_qpd_depth;
  u8 sw_cu_qpd_e;
  u8 sw_fieldpic_flag_e;
  u8 sw_intradc_vlc_thr;
  u16 sw_vop_time_incr;
  u8 sw_dq_profile;
  u8 sw_dqbi_level;
  u8 sw_range_red_frm_e;
  u8 sw_fast_uvmc_e;
  u8 sw_transdctab;
  u8 sw_transacfrm;
  u8 sw_transacfrm2;
  u8 sw_mb_mode_tab;
  u8 sw_mvtab;
  u8 sw_cbptab;
  u8 sw_2mv_blk_pat_tab;
  u8 sw_4mv_blk_pat_tab;
  u8 sw_qscale_type;
  u8 sw_con_mv_e;
  u8 sw_intra_dc_prec;
  u8 sw_intra_vlc_tab;
  u8 sw_frame_pred_dct;
  u8 sw_jpeg_qtables;
  u8 sw_jpeg_mode;
  u8 sw_jpeg_filright_e;
  u8 sw_jpeg_stream_all;
  u8 sw_cr_ac_vlctable;
  u8 sw_cb_ac_vlctable;
  u8 sw_cr_dc_vlctable;
  u8 sw_cb_dc_vlctable;
  u8 sw_cr_dc_vlctable3;
  u8 sw_cb_dc_vlctable3;
  u8 sw_pjpeg_dc_sel0;
  u8 sw_pjpeg_dc_sel1;
  u8 sw_pjpeg_dc_sel2;
  u8 sw_pjpeg_ac_sel;
  u8 sw_strm1_start_bit;
  u8 sw_huffman_e;
  u8 sw_multistream_e;
  u8 sw_boolean_value;
  u8 sw_boolean_range;
  u8 sw_alpha_offset;
  u8 sw_beta_offset;
  u8 sw_cb_qp_delta;
  u8 sw_cr_qp_delta;
  u8 sw_bcbr_enable;
  u16 sw_time_ref;
  u8 sw_delta_lf_res_log;
  u8 sw_delta_lf_multi;
  u8 sw_delta_lf_present;
  u8 sw_preskip_segid;
  u8 sw_disable_cdf_update;
  u8 sw_allow_warp;
  u8 sw_superres_is_scaled;
  u8 sw_show_frame;
  u8 sw_switchable_motion_mode;
  u8 sw_enable_cdef;
  u8 sw_allow_masked_compound;
  u8 sw_allow_interintra;
  u8 sw_enable_intra_edge_filter;
  u8 sw_allow_filter_intra;
  u8 sw_enable_jnt_comp;
  u8 sw_enable_dual_filter;
  u8 sw_reduced_tx_set_used;
  u8 sw_allow_screen_content_tools;
  u8 sw_allow_intrabc;
  u8 sw_force_interger_mv;
  u8 sw_error_resilient;
  u8 sw_filt_level_base_gt32;
  u8 sw_ref_scaling_enable;
  u32 sw_stream_len;
  u8 sw_cabac_e;
  u8 sw_cabac_init_present;
  u8 sw_blackwhite_e;
  u8 sw_dir_8x8_infer_e;
  u8 sw_weight_pred_e;
  u8 sw_weight_bipr_idc;
  u8 sw_avs_h264_h_ext;
  u8 sw_ch_8pix_ileav_e;
  u8 sw_framenum_len;
  u16 sw_framenum;
  u8 sw_bitplane0_e;
  u8 sw_bitplane1_e;
  u8 sw_bitplane2_e;
  u8 sw_alt_pquant;
  u8 sw_dq_edges;
  u8 sw_ttmbf;
  u8 sw_pqindex;
  u8 sw_vc1_height_ext;
  u8 sw_bilin_mc_e;
  u8 sw_uniqp_e;
  u8 sw_halfqp_e;
  u8 sw_ttfrm;
  u8 sw_2nd_byte_emul_e;
  u8 sw_dquant_e;
  u8 sw_vc1_adv_e;
  u8 sw_pjpeg_fildown_e;
  u8 sw_pjpeg_ah;
  u8 sw_pjpeg_al;
  u8 sw_pjpeg_ss;
  u8 sw_pjpeg_se;
  u8 sw_dct1_start_bit;
  u8 sw_dct2_start_bit;
  u8 sw_ch_mv_res;
  u8 sw_init_dc_match0;
  u8 sw_init_dc_match1;
  u8 sw_vp7_version;
  u8 sw_alf_enable;
  u8 sw_alf_on_y;
  u8 sw_alf_on_u;
  u8 sw_alf_on_v;
  u8 sw_filt_slice_border;
  u8 sw_filt_tile_border;
  u8 sw_asym_pred_e;
  u8 sw_sao_e;
  u8 sw_pcm_filt_disable;
  u8 sw_slice_chqp_flag;
  u8 sw_depend_slice_e;
  u8 sw_filt_override_e;
  u8 sw_strong_smooth_e;
  u8 sw_nonsquare_intra_pred_e;
  u8 sw_filt_offset_beta;
  u8 sw_filt_offset_tc;
  u8 sw_slice_hdr_ext_e;
  u8 sw_slice_hdr_ebits;
  u16 sw_random_seed;
  u8 sw_chroma_scaling_from_luma;
  u8 sw_clip_to_restricted_range;
  u8 sw_overlap_flag;
  u8 sw_num_cr_points_b;
  u8 sw_num_cb_points_b;
  u8 sw_num_y_points_b;
  u8 sw_apply_grain;
  u8 sw_cdef_bits;
  u8 sw_cdef_damping;
  u8 sw_delta_q_res_log;
  u8 sw_delta_q_present;
  u8 sw_const_intra_e;
  u8 sw_filt_ctrl_pres;
  u8 sw_rdpic_cnt_pres;
  u8 sw_8x8trans_flag_e;
  u8 sw_refpic_mk_len;
  u16 sw_superres_pic_width;
  u8 sw_idr_pic_e;
  u16 sw_idr_pic_id;
  u8 sw_pcm_bitdepth_y;
  u8 sw_pcm_bitdepth_c;
  u8 sw_bit_depth_out_minus8;
  u8 sw_quant_base_qindex;
  u8 sw_bit_depth_y_minus8;
  u8 sw_bit_depth_c_minus8;
  u8 sw_scaling_shift;
  u8 sw_mv_scalefactor;
  u8 sw_ref_dist_fwd;
  u8 sw_ref_dist_bwd;
  u8 sw_loop_filt_limit;
  u8 sw_variance_test_e;
  u8 sw_mv_threshold;
  u16 sw_var_threshold;
  u8 sw_divx_idct_e;
  u8 sw_divx3_slice_size;
  u16 sw_pjpeg_rest_freq;
  u8 sw_rv_profile;
  u8 sw_rv_osv_quant;
  u16 sw_rv_fwd_scale;
  u16 sw_rv_bwd_scale;
  u16 sw_init_dc_comp0;
  u16 sw_init_dc_comp1;
  u8 sw_pps_id;
  u8 sw_refidx1_active;
  u8 sw_refidx0_active;
  u16 sw_hdr_skip_length;
  u8 sw_poc_length;
  u8 sw_mb_width_off;
  u8 sw_mb_height_off;
  u8 sw_icomp0_e;
  u8 sw_iscale0;
  u16 sw_ishift0;
  u16 sw_stream1_len;
  u16 sw_pic_slice_am;
  u8 sw_coeffs_part_am;
  u16 sw_context_update_tile_id;
  u8 sw_last_active_seg;
  u8 sw_scale_denom_minus9;
  u8 sw_mf3_type;
  u8 sw_mf2_type;
  u8 sw_mf1_type;
  u8 sw_ref6_sign_bias;
  u8 sw_ref5_sign_bias;
  u8 sw_ref4_sign_bias;
  u8 sw_pinit_rlist_f9;
  u8 sw_pinit_rlist_f8;
  u8 sw_pinit_rlist_f7;
  u8 sw_pinit_rlist_f6;
  u8 sw_pinit_rlist_f5;
  u8 sw_pinit_rlist_f4;
  u8 sw_icomp1_e;
  u8 sw_iscale1;
  u16 sw_ishift1;
  u8 sw_tile_mc_tile_start_x;
  u8 sw_num_tile_cols;
  u8 sw_num_tile_cols_8k;
  u8 sw_num_tile_rows;
  u8 sw_num_tile_rows_8k;
  u8 sw_num_tile_rows_8k_av1;
  u8 sw_tile_enable;
  u8 sw_tile_transpose;
  u8 sw_entr_code_synch_e;
  u8 sw_pinit_rlist_f15;
  u8 sw_pinit_rlist_f14;
  u8 sw_pinit_rlist_f13;
  u8 sw_pinit_rlist_f12;
  u8 sw_pinit_rlist_f11;
  u8 sw_pinit_rlist_f10;
  u8 sw_icomp2_e;
  u8 sw_iscale2;
  u16 sw_ishift2;
  u8 sw_dct3_start_bit;
  u8 sw_dct4_start_bit;
  u8 sw_dct5_start_bit;
  u8 sw_dct6_start_bit;
  u8 sw_dct7_start_bit;
  u8 sw_dec_tile_size_mag;
  u8 sw_transform_mode;
  u8 sw_second_transform_e;
  u8 sw_nonsquare_transform_e;
  u8 sw_dmh_e;
  u8 sw_multi_hypo_skip_e;
  u8 sw_dual_hypo_pred_e;
  u8 sw_weighted_skip_e;
  u8 sw_pmvr_e;
  u16 sw_alf_interval_x;
  u16 sw_alf_interval_y;
  u8 sw_tile_mc_tile_col;
  u8 sw_mcomp_filt_type;
  u8 sw_high_prec_mv_e;
  u8 sw_comp_pred_mode;
  u8 sw_use_temporal0_mvs;
  u8 sw_use_temporal1_mvs;
  u8 sw_use_temporal2_mvs;
  u8 sw_use_temporal3_mvs;
  u8 sw_sync_marker_e;
  u8 sw_pjpeg_qtable_sel0;
  u8 sw_pjpeg_qtable_sel1;
  u8 sw_pjpeg_qtable_sel2;
  u16 sw_idr_pic_id_h10;
  u8 sw_av1_comp_pred_fixed_ref;
  u8 sw_min_cb_size;
  u8 sw_max_cb_size;
  u8 sw_seg_quant_sign;
  u8 sw_min_pcm_size;
  u8 sw_max_pcm_size;
  u8 sw_pcm_e;
  u8 sw_transform_skip_e;
  u8 sw_transq_bypass_e;
  u8 sw_refpiclist_mod_e;
  u8 sw_start_code_e;
  u8 sw_init_qp;
  u8 sw_min_trb_size;
  u8 sw_max_trb_size;
  u8 sw_max_intra_hierdepth;
  u8 sw_max_inter_hierdepth;
  u8 sw_parallel_merge;
  u8 sw_qp_delta_y_dc;
  u8 sw_qp_delta_ch_dc;
  u8 sw_qp_delta_ch_ac;
  u8 sw_qp_delta_y_dc_av1;
  u8 sw_qp_delta_ch_dc_av1;
  u8 sw_qp_delta_ch_ac_av1;
  u8 sw_last_sign_bias;
  u8 sw_lossless_e;
  u8 sw_comp_pred_var_ref1;
  u8 sw_comp_pred_var_ref0;
  u8 sw_comp_pred_var_ref1_av1;
  u8 sw_comp_pred_var_ref0_av1;
  u8 sw_comp_pred_fixed_ref;
  u8 sw_segment_temp_upd_e;
  u8 sw_segment_upd_e;
  u8 sw_segment_e;
  u8 sw_init_rlist_b2;
  u8 sw_init_rlist_f2;
  u8 sw_init_rlist_b1;
  u8 sw_init_rlist_f1;
  u8 sw_init_rlist_b0;
  u8 sw_init_rlist_f0;
  u8 sw_filt_level0;
  u8 sw_filt_level;
  u8 sw_filt_level_delta0_seg0;
  u8 sw_av1_refpic_seg0;
  u8 sw_refpic_seg0;
  u8 sw_skip_seg0;
  u8 sw_filt_level_seg0;
  u8 sw_quant_seg0;
  u8 sw_jpeg_slice_h;
  u8 sw_init_rlist_b5;
  u8 sw_init_rlist_f5;
  u8 sw_init_rlist_b4;
  u8 sw_init_rlist_f4;
  u8 sw_init_rlist_b3;
  u8 sw_init_rlist_f3;
  u8 sw_filt_level1;
  u8 sw_filt_level_delta0_seg1;
  u8 sw_av1_refpic_seg1;
  u8 sw_refpic_seg1;
  u8 sw_skip_seg1;
  u8 sw_filt_level_seg1;
  u8 sw_quant_seg1;
  u8 sw_ac1_code6_cnt;
  u8 sw_ac1_code5_cnt;
  u8 sw_ac1_code4_cnt;
  u8 sw_ac1_code3_cnt;
  u8 sw_ac1_code2_cnt;
  u8 sw_ac1_code1_cnt;
  u8 sw_init_rlist_b8;
  u8 sw_init_rlist_f8;
  u8 sw_init_rlist_b7;
  u8 sw_init_rlist_f7;
  u8 sw_init_rlist_b6;
  u8 sw_init_rlist_f6;
  u8 sw_filt_level2;
  u8 sw_filt_level_delta0_seg2;
  u8 sw_av1_refpic_seg2;
  u8 sw_refpic_seg2;
  u8 sw_skip_seg2;
  u8 sw_filt_level_seg2;
  u8 sw_quant_seg2;
  u8 sw_ac1_code10_cnt;
  u8 sw_ac1_code9_cnt;
  u8 sw_ac1_code8_cnt;
  u8 sw_ac1_code7_cnt;
  u8 sw_init_rlist_b11;
  u8 sw_init_rlist_f11;
  u8 sw_init_rlist_b10;
  u8 sw_init_rlist_f10;
  u8 sw_init_rlist_b9;
  u8 sw_init_rlist_f9;
  u8 sw_filt_level3;
  u8 sw_filt_level_delta0_seg3;
  u8 sw_av1_refpic_seg3;
  u8 sw_refpic_seg3;
  u8 sw_skip_seg3;
  u8 sw_filt_level_seg3;
  u8 sw_quant_seg3;
  u16 sw_pic_header_len;
  u8 sw_pic_4mv_e;
  u8 sw_range_red_ref_e;
  u8 sw_vc1_difmv_range;
  u8 sw_mv_range;
  u8 sw_overlap_e;
  u8 sw_overlap_method;
  u8 sw_alt_scan_flag_e;
  u8 sw_fcode_fwd_hor;
  u8 sw_fcode_fwd_ver;
  u8 sw_fcode_bwd_hor;
  u8 sw_fcode_bwd_ver;
  u8 sw_mv_accuracy_fwd;
  u8 sw_mv_accuracy_bwd;
  u8 sw_mpeg4_vc1_rc;
  u8 sw_prev_anc_type;
  u8 sw_ac1_code14_cnt;
  u8 sw_ac1_code13_cnt;
  u8 sw_ac1_code12_cnt;
  u8 sw_ac1_code11_cnt;
  u8 sw_init_rlist_b14;
  u8 sw_init_rlist_f14;
  u8 sw_init_rlist_b13;
  u8 sw_init_rlist_f13;
  u8 sw_init_rlist_b12;
  u8 sw_init_rlist_f12;
  u8 sw_lr_type;
  u8 sw_filt_level_delta0_seg4;
  u8 sw_av1_refpic_seg4;
  u8 sw_refpic_seg4;
  u8 sw_skip_seg4;
  u8 sw_filt_level_seg4;
  u8 sw_quant_seg4;
  u32 sw_trb_per_trd_d0;
  u8 sw_icomp3_e;
  u8 sw_iscale3;
  u16 sw_ishift3;
  u8 sw_ac2_code4_cnt;
  u8 sw_ac2_code3_cnt;
  u8 sw_ac2_code2_cnt;
  u8 sw_ac2_code1_cnt;
  u8 sw_ac1_code16_cnt;
  u8 sw_ac1_code15_cnt;
  u8 sw_scan_map_1;
  u8 sw_scan_map_2;
  u8 sw_scan_map_3;
  u8 sw_scan_map_4;
  u8 sw_scan_map_5;
  u8 sw_init_rlist_b15;
  u8 sw_init_rlist_f15;
  u8 sw_lr_unit_size;
  u8 sw_filt_level_delta0_seg5;
  u8 sw_av1_refpic_seg5;
  u8 sw_refpic_seg5;
  u8 sw_skip_seg5;
  u8 sw_filt_level_seg5;
  u8 sw_quant_seg5;
  u32 sw_trb_per_trd_dm1;
  u8 sw_icomp4_e;
  u8 sw_iscale4;
  u16 sw_ishift4;
  u8 sw_ac2_code8_cnt;
  u8 sw_ac2_code7_cnt;
  u8 sw_ac2_code6_cnt;
  u8 sw_ac2_code5_cnt;
  u8 sw_scan_map_6;
  u8 sw_scan_map_7;
  u8 sw_scan_map_8;
  u8 sw_scan_map_9;
  u8 sw_scan_map_10;
  u8 sw_partial_ctb_x;
  u8 sw_partial_ctb_y;
  u16 sw_pic_width_4x4;
  u16 sw_pic_height_4x4;
  u16 sw_mf1_last_offset;
  u8 sw_global_mv_seg0;
  u8 sw_filt_level_delta3_seg0;
  u8 sw_filt_level_delta2_seg0;
  u8 sw_filt_level_delta1_seg0;
  u8 sw_y_stride_pow2;
  u8 sw_c_stride_pow2;
  u32 sw_trb_per_trd_d1;
  u8 sw_ac2_code12_cnt;
  u8 sw_ac2_code11_cnt;
  u8 sw_ac2_code10_cnt;
  u8 sw_ac2_code9_cnt;
  u8 sw_scan_map_11;
  u8 sw_scan_map_12;
  u8 sw_scan_map_13;
  u8 sw_scan_map_14;
  u8 sw_scan_map_15;
  u16 sw_mf1_last2_offset;
  u8 sw_global_mv_seg1;
  u8 sw_filt_level_delta3_seg1;
  u8 sw_filt_level_delta2_seg1;
  u8 sw_filt_level_delta1_seg1;
  u8 sw_ac2_code16_cnt;
  u8 sw_ac2_code15_cnt;
  u8 sw_ac2_code14_cnt;
  u8 sw_ac2_code13_cnt;
  u8 sw_scan_map_16;
  u8 sw_scan_map_17;
  u8 sw_scan_map_18;
  u8 sw_scan_map_19;
  u8 sw_scan_map_20;
  u16 sw_mf1_last3_offset;
  u8 sw_global_mv_seg2;
  u8 sw_filt_level_delta3_seg2;
  u8 sw_filt_level_delta2_seg2;
  u8 sw_filt_level_delta1_seg2;
  u8 sw_dc1_code8_cnt;
  u8 sw_dc1_code7_cnt;
  u8 sw_dc1_code6_cnt;
  u8 sw_dc1_code5_cnt;
  u8 sw_dc1_code4_cnt;
  u8 sw_dc1_code3_cnt;
  u8 sw_dc1_code2_cnt;
  u8 sw_dc1_code1_cnt;
  u8 sw_scan_map_21;
  u8 sw_scan_map_22;
  u8 sw_scan_map_23;
  u8 sw_scan_map_24;
  u8 sw_scan_map_25;
  u16 sw_mf1_golden_offset;
  u8 sw_global_mv_seg3;
  u8 sw_filt_level_delta3_seg3;
  u8 sw_filt_level_delta2_seg3;
  u8 sw_filt_level_delta1_seg3;
  u8 sw_dc1_code16_cnt;
  u8 sw_dc1_code15_cnt;
  u8 sw_dc1_code14_cnt;
  u8 sw_dc1_code13_cnt;
  u8 sw_dc1_code12_cnt;
  u8 sw_dc1_code11_cnt;
  u8 sw_dc1_code10_cnt;
  u8 sw_dc1_code9_cnt;
  u8 sw_scan_map_26;
  u8 sw_scan_map_27;
  u8 sw_scan_map_28;
  u8 sw_scan_map_29;
  u8 sw_scan_map_30;
  u16 sw_mf1_bwdref_offset;
  u8 sw_global_mv_seg4;
  u8 sw_filt_level_delta3_seg4;
  u8 sw_filt_level_delta2_seg4;
  u8 sw_filt_level_delta1_seg4;
  u8 sw_dc2_code8_cnt;
  u8 sw_dc2_code7_cnt;
  u8 sw_dc2_code6_cnt;
  u8 sw_dc2_code5_cnt;
  u8 sw_dc2_code4_cnt;
  u8 sw_dc2_code3_cnt;
  u8 sw_dc2_code2_cnt;
  u8 sw_dc2_code1_cnt;
  u8 sw_scan_map_31;
  u8 sw_scan_map_32;
  u8 sw_scan_map_33;
  u8 sw_scan_map_34;
  u8 sw_scan_map_35;
  u16 sw_mf1_altref2_offset;
  u8 sw_global_mv_seg5;
  u8 sw_filt_level_delta3_seg5;
  u8 sw_filt_level_delta2_seg5;
  u8 sw_filt_level_delta1_seg5;
  u8 sw_dc2_code16_cnt;
  u8 sw_dc2_code15_cnt;
  u8 sw_dc2_code14_cnt;
  u8 sw_dc2_code13_cnt;
  u8 sw_dc2_code12_cnt;
  u8 sw_dc2_code11_cnt;
  u8 sw_dc2_code10_cnt;
  u8 sw_dc2_code9_cnt;
  u8 sw_scan_map_36;
  u8 sw_scan_map_37;
  u8 sw_scan_map_38;
  u8 sw_scan_map_39;
  u8 sw_scan_map_40;
  u16 sw_mf1_altref_offset;
  u8 sw_global_mv_seg6;
  u8 sw_filt_level_delta3_seg6;
  u8 sw_filt_level_delta2_seg6;
  u8 sw_filt_level_delta1_seg6;
  u8 sw_dc3_code8_cnt;
  u8 sw_dc3_code7_cnt;
  u8 sw_dc3_code6_cnt;
  u8 sw_dc3_code5_cnt;
  u8 sw_dc3_code4_cnt;
  u8 sw_dc3_code3_cnt;
  u8 sw_dc3_code2_cnt;
  u8 sw_dc3_code1_cnt;
  u16 sw_mf2_last_offset;
  u8 sw_global_mv_seg7;
  u8 sw_filt_level_delta3_seg7;
  u8 sw_filt_level_delta2_seg7;
  u8 sw_filt_level_delta1_seg7;
  u16 sw_ref_invd_cur_1;
  u16 sw_ref_invd_cur_0;
  u8 sw_scan_map_41;
  u8 sw_scan_map_42;
  u8 sw_scan_map_43;
  u8 sw_scan_map_44;
  u8 sw_scan_map_45;
  u8 sw_dc3_code16_cnt;
  u8 sw_dc3_code15_cnt;
  u8 sw_dc3_code14_cnt;
  u8 sw_dc3_code13_cnt;
  u8 sw_dc3_code12_cnt;
  u8 sw_dc3_code11_cnt;
  u8 sw_dc3_code10_cnt;
  u8 sw_dc3_code9_cnt;
  u8 sw_quant_delta_v_dc;
  u8 sw_cb_mult;
  u8 sw_cb_luma_mult;
  u16 sw_cb_offset;
  u16 sw_ref_invd_cur_3;
  u16 sw_ref_invd_cur_2;
  u8 sw_scan_map_46;
  u8 sw_scan_map_47;
  u8 sw_scan_map_48;
  u8 sw_scan_map_49;
  u8 sw_scan_map_50;
  u8 sw_dc4_code8_cnt;
  u8 sw_dc4_code7_cnt;
  u8 sw_dc4_code6_cnt;
  u8 sw_dc4_code5_cnt;
  u8 sw_dc4_code4_cnt;
  u8 sw_dc4_code3_cnt;
  u8 sw_dc4_code2_cnt;
  u8 sw_dc4_code1_cnt;
  u8 sw_quant_delta_v_ac;
  u8 sw_cr_mult;
  u8 sw_cr_luma_mult;
  u16 sw_cr_offset;
  u16 sw_refer1_nbr;
  u16 sw_refer0_nbr;
  u16 sw_ref_dist_cur_1;
  u16 sw_ref_dist_cur_0;
  u8 sw_filt_type;
  u8 sw_filt_sharpness;
  u8 sw_filt_mb_adj_0;
  u8 sw_filt_mb_adj_1;
  u8 sw_filt_mb_adj_2;
  u8 sw_filt_mb_adj_3;
  u8 sw_filt_ref_adj_4;
  u8 sw_filt_ref_adj_5;
  u8 sw_dc4_code16_cnt;
  u8 sw_dc4_code15_cnt;
  u8 sw_dc4_code14_cnt;
  u8 sw_dc4_code13_cnt;
  u8 sw_dc4_code12_cnt;
  u8 sw_dc4_code11_cnt;
  u8 sw_dc4_code10_cnt;
  u8 sw_dc4_code9_cnt;
  u16 sw_refer3_nbr;
  u16 sw_refer2_nbr;
  u8 sw_scan_map_51;
  u8 sw_scan_map_52;
  u8 sw_scan_map_53;
  u8 sw_scan_map_54;
  u8 sw_scan_map_55;
  u16 sw_ref_dist_cur_3;
  u16 sw_ref_dist_cur_2;
  u8 sw_skip_ref0;
  u8 sw_filt_level_delta0_seg6;
  u8 sw_av1_refpic_seg6;
  u8 sw_refpic_seg6;
  u8 sw_skip_seg6;
  u8 sw_filt_level_seg6;
  u8 sw_quant_seg6;
  u8 sw_ac3_code6_cnt;
  u8 sw_ac3_code5_cnt;
  u8 sw_ac3_code4_cnt;
  u8 sw_ac3_code3_cnt;
  u8 sw_ac3_code2_cnt;
  u8 sw_ac3_code1_cnt;
  u16 sw_refer5_nbr;
  u16 sw_refer4_nbr;
  u8 sw_scan_map_56;
  u8 sw_scan_map_57;
  u8 sw_scan_map_58;
  u8 sw_scan_map_59;
  u8 sw_scan_map_60;
  u16 sw_ref_invd_col_1;
  u16 sw_ref_invd_col_0;
  u8 sw_filt_level_0;
  u8 sw_filt_level_1;
  u8 sw_filt_level_2;
  u8 sw_filt_level_3;
  u8 sw_skip_ref1;
  i8 sw_filt_level_delta0_seg7;
  u8 sw_av1_refpic_seg7;
  u8 sw_refpic_seg7;
  u8 sw_skip_seg7;
  u8 sw_filt_level_seg7;
  u8 sw_quant_seg7;
  u8 sw_ac3_code10_cnt;
  u8 sw_ac3_code9_cnt;
  u8 sw_ac3_code8_cnt;
  u8 sw_ac3_code7_cnt;
  u16 sw_refer7_nbr;
  u16 sw_refer6_nbr;
  u8 sw_scan_map_61;
  u8 sw_scan_map_62;
  u8 sw_scan_map_63;
  u16 sw_ref_invd_col_3;
  u16 sw_ref_invd_col_2;
  u8 sw_quant_delta_0;
  u8 sw_quant_delta_1;
  u16 sw_quant_0;
  u16 sw_quant_1;
  u16 sw_lref_width;
  u16 sw_lref_height;
  u16 sw_ref0_width;
  u16 sw_ref0_height;
  u8 sw_ac3_code14_cnt;
  u8 sw_ac3_code13_cnt;
  u8 sw_ac3_code12_cnt;
  u8 sw_ac3_code11_cnt;
  u16 sw_refer9_nbr;
  u16 sw_refer8_nbr;
  u16 sw_pred_bc_tap_0_3;
  u16 sw_pred_bc_tap_1_0;
  u16 sw_pred_bc_tap_1_1;
  u16 sw_gref_width;
  u16 sw_gref_height;
  u16 sw_ref1_width;
  u16 sw_ref1_height;
  u8 sw_ac4_code4_cnt;
  u8 sw_ac4_code3_cnt;
  u8 sw_ac4_code2_cnt;
  u8 sw_ac4_code1_cnt;
  u8 sw_ac3_code16_cnt;
  u8 sw_ac3_code15_cnt;
  u16 sw_refer11_nbr;
  u16 sw_refer10_nbr;
  u16 sw_pred_bc_tap_1_2;
  u16 sw_pred_bc_tap_1_3;
  u16 sw_pred_bc_tap_2_0;
  u16 sw_aref_width;
  u16 sw_aref_height;
  u16 sw_ref2_width;
  u16 sw_ref2_height;
  u8 sw_ac4_code8_cnt;
  u8 sw_ac4_code7_cnt;
  u8 sw_ac4_code6_cnt;
  u8 sw_ac4_code5_cnt;
  u16 sw_refer13_nbr;
  u16 sw_refer12_nbr;
  u16 sw_pred_bc_tap_2_1;
  u16 sw_pred_bc_tap_2_2;
  u16 sw_pred_bc_tap_2_3;
  u16 sw_lref_hor_scale;
  u16 sw_lref_ver_scale;
  u16 sw_ref0_hor_scale;
  u16 sw_ref0_ver_scale;
  u8 sw_ac4_code12_cnt;
  u8 sw_ac4_code11_cnt;
  u8 sw_ac4_code10_cnt;
  u8 sw_ac4_code9_cnt;
  u16 sw_refer15_nbr;
  u16 sw_refer14_nbr;
  u16 sw_pred_bc_tap_3_0;
  u16 sw_pred_bc_tap_3_1;
  u16 sw_pred_bc_tap_3_2;
  u16 sw_gref_hor_scale;
  u16 sw_gref_ver_scale;
  u16 sw_ref1_hor_scale;
  u16 sw_ref1_ver_scale;
  u8 sw_ac4_code16_cnt;
  u8 sw_ac4_code15_cnt;
  u8 sw_ac4_code14_cnt;
  u8 sw_ac4_code13_cnt;
  u32 sw_refer_lterm_e;
  u16 sw_pred_bc_tap_3_3;
  u16 sw_pred_bc_tap_4_0;
  u16 sw_pred_bc_tap_4_1;
  u16 sw_aref_hor_scale;
  u16 sw_aref_ver_scale;
  u16 sw_ref2_hor_scale;
  u16 sw_ref2_ver_scale;
  u8 sw_background_e;
  u8 sw_background_is_top;
  u8 sw_rps_referd_e;
  u32 sw_refer_valid_e;
  u16 sw_pred_bc_tap_4_2;
  u16 sw_pred_bc_tap_4_3;
  u16 sw_pred_bc_tap_5_0;
  u16 sw_ref3_hor_scale;
  u16 sw_ref3_ver_scale;
  u16 sw_ref4_hor_scale;
  u16 sw_ref4_ver_scale;
  u16 sw_ref5_hor_scale;
  u16 sw_ref5_ver_scale;
  u8 sw_binit_rlist_b2;
  u8 sw_binit_rlist_f2;
  u8 sw_binit_rlist_b1;
  u8 sw_binit_rlist_f1;
  u8 sw_binit_rlist_b0;
  u8 sw_binit_rlist_f0;
  u16 sw_pred_bc_tap_5_1;
  u16 sw_pred_bc_tap_5_2;
  u16 sw_pred_bc_tap_5_3;
  u8 sw_weight_qp_1;
  u8 sw_ref_delta_col_0;
  u8 sw_ref_delta_col_1;
  u8 sw_ref_delta_col_2;
  u8 sw_ref_delta_col_3;
  u8 sw_ref_delta_cur_0;
  u8 sw_ref_delta_cur_1;
  u8 sw_ref_delta_cur_2;
  u8 sw_ref_delta_cur_3;
  u16 sw_lref_y_stride;
  u16 sw_lref_c_stride;
  u16 sw_ref6_hor_scale;
  u16 sw_ref6_ver_scale;
  u8 sw_binit_rlist_b5;
  u8 sw_binit_rlist_f5;
  u8 sw_binit_rlist_b4;
  u8 sw_binit_rlist_f4;
  u8 sw_binit_rlist_b3;
  u8 sw_binit_rlist_f3;
  u16 sw_pred_bc_tap_6_0;
  u16 sw_pred_bc_tap_6_1;
  u16 sw_pred_bc_tap_6_2;
  u8 sw_weight_qp_2;
  u8 sw_weight_qp_3;
  u8 sw_weight_qp_4;
  u8 sw_weight_qp_5;
  u16 sw_gref_y_stride;
  u16 sw_gref_c_stride;
  u16 sw_ref3_width;
  u16 sw_ref3_height;
  u8 sw_binit_rlist_b8;
  u8 sw_binit_rlist_f8;
  u8 sw_binit_rlist_b7;
  u8 sw_binit_rlist_f7;
  u8 sw_binit_rlist_b6;
  u8 sw_binit_rlist_f6;
  u16 sw_pred_bc_tap_6_3;
  u16 sw_pred_bc_tap_7_0;
  u16 sw_pred_bc_tap_7_1;
  u8 sw_dec_avsp_ena;
  u8 sw_weight_qp_e;
  u8 sw_weight_qp_model;
  u8 sw_avs_aec_e;
  u8 sw_no_fwd_ref_e;
  u8 sw_pb_field_enhanced_e;
  u8 sw_qp_delta_cb;
  u8 sw_qp_delta_cr;
  u8 sw_weight_qp_0;
  u16 sw_aref_y_stride;
  u16 sw_aref_c_stride;
  u16 sw_ref4_width;
  u16 sw_ref4_height;
  u8 sw_binit_rlist_b11;
  u8 sw_binit_rlist_f11;
  u8 sw_binit_rlist_b10;
  u8 sw_binit_rlist_f10;
  u8 sw_binit_rlist_b9;
  u8 sw_binit_rlist_f9;
  u16 sw_pred_bc_tap_7_2;
  u16 sw_pred_bc_tap_7_3;
  u8 sw_pred_tap_2_m1;
  u8 sw_pred_tap_2_4;
  u8 sw_pred_tap_4_m1;
  u8 sw_pred_tap_4_4;
  u8 sw_pred_tap_6_m1;
  u8 sw_pred_tap_6_4;
  u16 sw_ref5_width;
  u16 sw_ref5_height;
  u8 sw_binit_rlist_b14;
  u8 sw_binit_rlist_f14;
  u8 sw_binit_rlist_b13;
  u8 sw_binit_rlist_f13;
  u8 sw_binit_rlist_b12;
  u8 sw_binit_rlist_f12;
  u8 sw_quant_delta_2;
  u8 sw_quant_delta_3;
  u16 sw_quant_2;
  u16 sw_quant_3;
  u8 sw_cur_poc_00;
  u8 sw_cur_poc_01;
  u8 sw_cur_poc_02;
  u8 sw_cur_poc_03;
  u8 sw_ref_num;
  u16 sw_pic_distance;
  u16 sw_poc_next;
  u16 sw_ref6_width;
  u16 sw_ref6_height;
  u8 sw_pinit_rlist_f3;
  u8 sw_pinit_rlist_f2;
  u8 sw_pinit_rlist_f1;
  u8 sw_pinit_rlist_f0;
  u8 sw_binit_rlist_b15;
  u8 sw_binit_rlist_f15;
  u8 sw_quant_delta_4;
  u16 sw_quant_4;
  u16 sw_quant_5;
  u8 sw_cur_poc_04;
  u8 sw_cur_poc_05;
  u8 sw_cur_poc_06;
  u8 sw_cur_poc_07;
  u16 sw_ref_dist0;
  u16 sw_ref_dist1;
  u16 sw_ref_dist2;
  u8 sw_qmlevel_y;
  u16 sw_mf2_golden_offset;
  u16 sw_mf2_last3_offset;
  u16 sw_mf2_last2_offset;
  u16 sw_startmb_x;
  u16 sw_startmb_y;
  u8 sw_error_conc_mode;
  u8 sw_cur_poc_08;
  u8 sw_cur_poc_09;
  u8 sw_cur_poc_10;
  u8 sw_cur_poc_11;
  u16 sw_ref_dist3;
  u16 sw_ref_dist4;
  u16 sw_ref_dist5;
  u8 sw_qmlevel_u;
  u16 sw_mf2_altref_offset;
  u16 sw_mf2_altref2_offset;
  u16 sw_mf2_bwdref_offset;
  u16 sw_pred_bc_tap_0_0;
  u16 sw_pred_bc_tap_0_1;
  u16 sw_pred_bc_tap_0_2;
  u8 sw_cur_poc_12;
  u8 sw_cur_poc_13;
  u8 sw_cur_poc_14;
  u8 sw_cur_poc_15;
  u16 sw_ref_dist6;
  u8 sw_qmlevel_v;
  u8 sw_filt_ref_adj_7;
  u8 sw_filt_ref_adj_6;
  u16 sw_ref0_poc0;
  u16 sw_ref0_poc1;
  u16 sw_ref0_poc2;
  u16 sw_superres_luma_step;
  u16 sw_superres_chroma_step;
  u16 sw_ref0_poc3;
  u16 sw_ref0_poc4;
  u16 sw_ref0_poc5;
  u16 sw_superres_init_luma_subpel_x;
  u16 sw_superres_init_chroma_subpel_x;
  u16 sw_ref0_poc6;
  u16 sw_cdef_luma_secondary_strength;
  u16 sw_cdef_chroma_secondary_strength;
  u8 sw_apf_disable;
  u8 sw_apf_single_pu_mode;
  u16 sw_apf_threshold;
  u8 sw_serv_merge_dis;
  u8 sw_dec_multicore_e;
  u8 sw_dec_writestat_e;
  u8 sw_dec_multicore_mode;
  u8 sw_dec_mc_pollmode;
  u16 sw_dec_mc_polltime;
  u8 sw_dec_refer_doublebuffer_e;
  u8 sw_dec_axi_rd_id_e;
  u8 sw_dec_axi_wd_id_e;
  u8 sw_dec_buswidth;
  u8 sw_dec_max_burst;
  u8 sw_ref3_sign_bias;
  u8 sw_ref2_sign_bias;
  u8 sw_ref1_sign_bias;
  u8 sw_ref0_sign_bias;
  u8 sw_gref_sign_bias;
  u8 sw_aref_sign_bias;
  u8 sw_filt_ref_adj_0;
  u8 sw_filt_ref_adj_1;
  u8 sw_filt_ref_adj_2;
  u8 sw_filt_ref_adj_3;
  u8 sw_background_ref_e;
  u16 sw_dec_axi_wr_id;
  u16 sw_dec_axi_rd_id;
  u16 sw_mb_location_x;
  u16 sw_mb_location_y;
  u16 sw_cu_location_x;
  u16 sw_cu_location_y;
  u32 sw_perf_cycle_count;
  u32 sw_dec_out_ybase_msb;
  u32 sw_dec_out_base_msb;
  u32 sw_dec_out_ybase;
  u32 sw_dec_out_base;
  u8 sw_dpb_ilace_mode;
  u32 sw_refer0_ybase_msb;
  u32 sw_refer0_base_msb;
  u32 sw_jpg_ch_out_base_msb;
  u32 sw_refer0_ybase;
  u32 sw_refer0_base;
  u8 sw_refer0_field_e;
  u8 sw_refer0_topc_e;
  u32 sw_jpg_ch_out_base;
  u32 sw_refer1_ybase_msb;
  u32 sw_refer1_base_msb;
  u32 sw_refer1_ybase;
  u32 sw_refer1_base;
  u8 sw_refer1_field_e;
  u8 sw_refer1_topc_e;
  u32 sw_refer2_ybase_msb;
  u32 sw_refer2_base_msb;
  u32 sw_refer2_ybase;
  u32 sw_refer2_base;
  u8 sw_refer2_field_e;
  u8 sw_refer2_topc_e;
  u32 sw_refer3_ybase_msb;
  u32 sw_refer3_base_msb;
  u32 sw_refer3_ybase;
  u32 sw_refer3_base;
  u8 sw_refer3_field_e;
  u8 sw_refer3_topc_e;
  u32 sw_refer4_ybase_msb;
  u32 sw_refer4_base_msb;
  u32 sw_refer4_ybase;
  u32 sw_refer4_base;
  u8 sw_refer4_field_e;
  u8 sw_refer4_topc_e;
  u32 sw_refer5_ybase_msb;
  u32 sw_refer5_base_msb;
  u32 sw_refer5_ybase;
  u32 sw_refer5_base;
  u8 sw_refer5_field_e;
  u8 sw_refer5_topc_e;
  u32 sw_refer6_ybase_msb;
  u32 sw_segment_write_base_msb;
  u32 sw_refer6_base_msb;
  u32 sw_vp8_dec_ch_base_msb;
  u32 sw_refer6_ybase;
  u32 sw_segment_write_base;
  u32 sw_refer6_base;
  u8 sw_refer6_field_e;
  u8 sw_refer6_topc_e;
  u32 sw_vp8_dec_ch_base;
  u8 sw_vp8_stride_e;
  u32 sw_refer7_ybase_msb;
  u32 sw_segment_read_base_msb;
  u32 sw_refer7_base_msb;
  u32 sw_refer7_ybase;
  u32 sw_segment_read_base;
  u32 sw_refer7_base;
  u8 sw_refer7_field_e;
  u8 sw_refer7_topc_e;
  u32 sw_refer8_ybase_msb;
  u32 sw_global_model_base_msb;
  u32 sw_refer8_base_msb;
  u32 sw_dct_strm1_base_msb;
  u32 sw_refer8_ybase;
  u32 sw_global_model_base;
  u32 sw_refer8_base;
  u32 sw_dct_strm1_base;
  u8 sw_refer8_field_e;
  u8 sw_refer8_topc_e;
  u32 sw_refer9_ybase_msb;
  u32 sw_cdef_colbuf_base_msb;
  u32 sw_refer9_base_msb;
  u32 sw_dct_strm2_base_msb;
  u32 sw_refer9_ybase;
  u32 sw_cdef_colbuf_base;
  u32 sw_refer9_base;
  u32 sw_dct_strm2_base;
  u8 sw_refer9_field_e;
  u8 sw_refer9_topc_e;
  u32 sw_refer10_ybase_msb;
  u32 sw_cdef_left_colbuf_base_msb;
  u32 sw_refer10_base_msb;
  u32 sw_dct_strm3_base_msb;
  u32 sw_refer10_ybase;
  u32 sw_cdef_left_colbuf_base;
  u32 sw_refer10_base;
  u32 sw_dct_strm3_base;
  u8 sw_refer10_field_e;
  u8 sw_refer10_topc_e;
  u32 sw_refer11_ybase_msb;
  u32 sw_superres_colbuf_base_msb;
  u32 sw_refer11_base_msb;
  u32 sw_dct_strm4_base_msb;
  u32 sw_refer11_ybase;
  u32 sw_superres_colbuf_base;
  u32 sw_refer11_base;
  u32 sw_dct_strm4_base;
  u8 sw_refer11_field_e;
  u8 sw_refer11_topc_e;
  u32 sw_refer12_ybase_msb;
  u32 sw_lr_colbuf_base_msb;
  u32 sw_refer12_base_msb;
  u32 sw_dct_strm5_base_msb;
  u32 sw_refer12_ybase;
  u32 sw_lr_colbuf_base;
  u32 sw_refer12_base;
  u32 sw_dct_strm5_base;
  u8 sw_refer12_field_e;
  u8 sw_refer12_topc_e;
  u32 sw_refer13_ybase_msb;
  u32 sw_superres_left_colbuf_base_msb;
  u32 sw_refer13_base_msb;
  u32 sw_bitpl_ctrl_base_msb;
  u32 sw_refer13_ybase;
  u32 sw_superres_left_colbuf_base;
  u32 sw_refer13_base;
  u8 sw_refer13_field_e;
  u8 sw_refer13_topc_e;
  u32 sw_bitpl_ctrl_base;
  u32 sw_refer14_ybase_msb;
  u32 sw_filmgrain_base_msb;
  u32 sw_refer14_base_msb;
  u32 sw_dct_strm6_base_msb;
  u32 sw_refer14_ybase;
  u32 sw_filmgrain_base;
  u32 sw_refer14_base;
  u32 sw_dct_strm6_base;
  u8 sw_refer14_field_e;
  u8 sw_refer14_topc_e;
  u32 sw_refer15_ybase_msb;
  u32 sw_lr_left_colbuf_base_msb;
  u32 sw_refer15_base_msb;
  u32 sw_dct_strm7_base_msb;
  u32 sw_refer15_ybase;
  u32 sw_lr_left_colbuf_base;
  u32 sw_refer15_base;
  u32 sw_dct_strm7_base;
  u8 sw_refer15_field_e;
  u8 sw_refer15_topc_e;
  u32 sw_dec_out_cbase_msb;
  u32 sw_dec_out_cbase;
  u32 sw_refer0_cbase_msb;
  u32 sw_refer0_cbase;
  u32 sw_refer1_cbase_msb;
  u32 sw_refer1_cbase;
  u32 sw_refer2_cbase_msb;
  u32 sw_refer2_cbase;
  u32 sw_refer3_cbase_msb;
  u32 sw_refer3_cbase;
  u32 sw_refer4_cbase_msb;
  u32 sw_refer4_cbase;
  u32 sw_refer5_cbase_msb;
  u32 sw_refer5_cbase;
  u32 sw_refer6_cbase_msb;
  u32 sw_refer6_cbase;
  u32 sw_refer7_cbase_msb;
  u32 sw_dec_left_vert_filt_base_msb;
  u32 sw_refer7_cbase;
  u32 sw_dec_left_vert_filt_base;
  u32 sw_superres_luma_step_invra;
  u32 sw_refer8_cbase_msb;
  u32 sw_dec_left_bsd_ctrl_base_msb;
  u32 sw_refer8_cbase;
  u32 sw_dec_left_bsd_ctrl_base;
  u32 sw_superres_chroma_step_invra;
  u32 sw_refer9_cbase_msb;
  u32 sw_rfc_colbuf_base_msb;
  u32 sw_refer9_cbase;
  u32 sw_rfc_colbuf_base;
  u32 sw_refer10_cbase_msb;
  u32 sw_rfc_left_colbuf_base_msb;
  u32 sw_refer10_cbase;
  u32 sw_rfc_left_colbuf_base;
  u32 sw_refer11_cbase_msb;
  u32 sw_refer11_cbase;
  u32 sw_refer12_cbase_msb;
  u32 sw_refer12_cbase;
  u32 sw_refer13_cbase_msb;
  u32 sw_refer13_cbase;
  u32 sw_refer14_cbase_msb;
  u32 sw_refer14_cbase;
  u32 sw_refer15_cbase_msb;
  u32 sw_refer15_cbase;
  u32 sw_dec_out_dbase_msb;
  u32 sw_dir_mv_base_msb;
  u32 sw_dec_out_dbase;
  u32 sw_dir_mv_base;
  u32 sw_refer0_dbase_msb;
  u32 sw_refer0_dbase;
  u32 sw_refer1_dbase_msb;
  u32 sw_refer1_dbase;
  u32 sw_refer2_dbase_msb;
  u32 sw_refer2_dbase;
  u32 sw_refer3_dbase_msb;
  u32 sw_refer3_dbase;
  u32 sw_refer4_dbase_msb;
  u32 sw_refer4_dbase;
  u32 sw_refer5_dbase_msb;
  u32 sw_refer5_dbase;
  u32 sw_refer6_dbase_msb;
  u32 sw_refer6_dbase;
  u32 sw_refer7_dbase_msb;
  u32 sw_refer7_dbase;
  u32 sw_refer8_dbase_msb;
  u32 sw_refer8_dbase;
  u32 sw_refer9_dbase_msb;
  u32 sw_refer9_dbase;
  u32 sw_refer10_dbase_msb;
  u32 sw_refer10_dbase;
  u32 sw_refer11_dbase_msb;
  u32 sw_refer11_dbase;
  u32 sw_refer12_dbase_msb;
  u32 sw_refer12_dbase;
  u32 sw_refer13_dbase_msb;
  u32 sw_refer13_dbase;
  u32 sw_refer14_dbase_msb;
  u32 sw_refer14_dbase;
  u32 sw_refer15_dbase_msb;
  u32 sw_refer15_dbase;
  u32 sw_tile_base_msb;
  u32 sw_tile_base;
  u32 sw_stream_base_msb;
  u32 sw_rlc_vlc_base_msb;
  u32 sw_stream_base;
  u32 sw_rlc_vlc_base;
  u32 sw_scale_list_base_msb;
  u32 sw_ctx_counter_base_msb;
  u32 sw_prob_tab_out_base_msb;
  u32 sw_mb_ctrl_base_msb;
  u32 sw_scale_list_base;
  u32 sw_ctx_counter_base;
  u32 sw_prob_tab_out_base;
  u32 sw_mb_ctrl_base;
  u32 sw_prob_tab_base_msb;
  u32 sw_alf_table_base_msb;
  u32 sw_diff_mv_base_msb;
  u32 sw_segment_base_msb;
  u32 sw_prob_tab_base;
  u32 sw_alf_table_base;
  u32 sw_diff_mv_base;
  u32 sw_segment_base;
  u32 sw_qtable_base_msb;
  u32 sw_tile_mc_sync_curr_base_msb;
  u32 sw_qtable_base;
  u32 sw_tile_mc_sync_curr_base;
  u32 sw_i4x4_or_dc_base_msb;
  u32 sw_pjpeg_dccb_base_msb;
  u32 sw_tile_mc_sync_left_base_msb;
  u32 sw_i4x4_or_dc_base;
  u32 sw_pjpeg_dccb_base;
  u32 sw_tile_mc_sync_left_base;
  u32 sw_dec_vert_filt_base_msb;
  u32 sw_pjpeg_dccr_base_msb;
  u32 sw_dec_vert_filt_base;
  u32 sw_pjpeg_dccr_base;
  u32 sw_dec_vert_sao_base_msb;
  u32 sw_dir_mv_base2_msb;
  u32 sw_dec_vert_sao_base;
  u32 sw_dec_bsd_ctrl_base_msb;
  u32 sw_dec_ch8pix_base_msb;
  u32 sw_dec_bsd_ctrl_base;
  u32 sw_dec_ch8pix_base;
  u8 sw_ref0_gm_mode;
  u16 sw_mf3_last_offset;
  u16 sw_cur_last_offset;
  u16 sw_cur_last_roffset;
  u8 sw_ref1_gm_mode;
  u16 sw_mf3_last2_offset;
  u16 sw_cur_last2_offset;
  u16 sw_cur_last2_roffset;
  u8 sw_ref2_gm_mode;
  u16 sw_mf3_last3_offset;
  u16 sw_cur_last3_offset;
  u16 sw_cur_last3_roffset;
  u8 sw_ref3_gm_mode;
  u16 sw_mf3_golden_offset;
  u16 sw_cur_golden_offset;
  u16 sw_cur_golden_roffset;
  u8 sw_ref4_gm_mode;
  u16 sw_mf3_bwdref_offset;
  u16 sw_cur_bwdref_offset;
  u16 sw_cur_bwdref_roffset;
  u32 sw_dec_out_tybase_msb;
  u32 sw_dec_out_tybase;
  u32 sw_refer0_tybase_msb;
  u32 sw_refer0_tybase;
  u32 sw_refer1_tybase_msb;
  u32 sw_refer1_tybase;
  u32 sw_refer2_tybase_msb;
  u32 sw_refer2_tybase;
  u32 sw_refer3_tybase_msb;
  u32 sw_refer3_tybase;
  u32 sw_refer4_tybase_msb;
  u32 sw_refer4_tybase;
  u32 sw_refer5_tybase_msb;
  u32 sw_refer5_tybase;
  u32 sw_refer6_tybase_msb;
  u32 sw_refer6_tybase;
  u32 sw_refer7_tybase_msb;
  u32 sw_refer7_tybase;
  u32 sw_refer8_tybase_msb;
  u32 sw_refer8_tybase;
  u32 sw_refer9_tybase_msb;
  u32 sw_refer9_tybase;
  u32 sw_refer10_tybase_msb;
  u32 sw_refer10_tybase;
  u32 sw_refer11_tybase_msb;
  u32 sw_refer11_tybase;
  u32 sw_refer12_tybase_msb;
  u32 sw_refer12_tybase;
  u32 sw_refer13_tybase_msb;
  u32 sw_refer13_tybase;
  u32 sw_refer14_tybase_msb;
  u32 sw_refer14_tybase;
  u32 sw_refer15_tybase_msb;
  u32 sw_refer15_tybase;
  u32 sw_dec_out_tcbase_msb;
  u32 sw_dec_out_tcbase;
  u32 sw_refer0_tcbase_msb;
  u32 sw_refer0_tcbase;
  u32 sw_refer1_tcbase_msb;
  u32 sw_refer1_tcbase;
  u32 sw_refer2_tcbase_msb;
  u32 sw_refer2_tcbase;
  u32 sw_refer3_tcbase_msb;
  u32 sw_refer3_tcbase;
  u32 sw_refer4_tcbase_msb;
  u32 sw_refer4_tcbase;
  u32 sw_refer5_tcbase_msb;
  u32 sw_refer5_tcbase;
  u32 sw_refer6_tcbase_msb;
  u32 sw_refer6_tcbase;
  u32 sw_refer7_tcbase_msb;
  u32 sw_refer7_tcbase;
  u32 sw_refer8_tcbase_msb;
  u32 sw_refer8_tcbase;
  u32 sw_refer9_tcbase_msb;
  u32 sw_refer9_tcbase;
  u32 sw_refer10_tcbase_msb;
  u32 sw_refer10_tcbase;
  u32 sw_refer11_tcbase_msb;
  u32 sw_refer11_tcbase;
  u32 sw_refer12_tcbase_msb;
  u32 sw_refer12_tcbase;
  u32 sw_refer13_tcbase_msb;
  u32 sw_refer13_tcbase;
  u32 sw_refer14_tcbase_msb;
  u32 sw_refer14_tcbase;
  u32 sw_refer15_tcbase_msb;
  u32 sw_refer15_tcbase;
  u8 sw_ref5_gm_mode;
  u16 sw_mf3_altref2_offset;
  u16 sw_cur_altref2_offset;
  u16 sw_cur_altref2_roffset;
  u32 sw_strm_buffer_len;
  u32 sw_strm_start_offset;
  u16 sw_error_addr_x;
  u16 sw_error_addr_y;
  u8 sw_error_slice_data;
  u8 sw_error_slice_header;
  u8 sw_dec_error_code;
  u8 sw_ref6_gm_mode;
  u16 sw_mf3_altref_offset;
  u16 sw_cur_altref_offset;
  u16 sw_cur_altref_roffset;
  u32 sw_cdef_luma_primary_strength;
  u32 sw_cdef_chroma_primary_strength;
  u8 sw_axi_wr_4k_dis;
  u16 sw_axi_rd_ostd_threshold;
  u16 sw_axi_wr_ostd_threshold;
  u8 sw_ignore_slice_error_e;
  u8 sw_error_conceal_e;
  u32 sw_skip8x8;
  u8 sw_qp_max;
  u8 sw_qp_min;
  u32 sw_qp_count;
  u32 sw_qp_sum;
  u16 sw_fwd_mvx_max;
  u16 sw_fwd_mvx_min;
  u16 sw_fwd_mvy_max;
  u16 sw_fwd_mvy_min;
  u32 sw_mvx_sum_fwd;
  u32 sw_mvx_sum_bwd;
  u32 sw_mvy_sum_fwd;
  u32 sw_mvy_sum_bwd;
  u32 sw_pb_inter_fwd_count;
  u32 sw_pb_inter_bwd_count;
  u32 sw_pb_intra_count;
  u16 sw_bwd_mvx_max;
  u16 sw_bwd_mvx_min;
  u16 sw_bwd_mvy_max;
  u16 sw_bwd_mvy_min;
  u32 sw_signed_mvx_sum_fwd;
  u32 sw_signed_mvx_sum_bwd;
  u32 sw_signed_mvy_sum_fwd;
  u32 sw_signed_mvy_sum_bwd;
  u32 sw_dec_hw_dram_read_bw;
  u32 sw_dec_hw_dram_write_bw;
  u16 sw_dec_out_y_stride;
  u16 sw_dec_out_c_stride;
  u16 sw_dec_alignment;
  u32 sw_strm_end_offset;
  u32 sw_tile_left;
  u32 sw_start_code_offset;
  u8 sw_line_cnt_int_e;
  u8 sw_pp_line_cnt_sel;
  u8 sw_line_cnt_stripe;
  u16 sw_line_cnt;
  u8 sw_ext_timeout_override_e;
  u32 sw_ext_timeout_cycles;
  u8 sw_timeout_override_e;
  u32 sw_timeout_cycles;
  u8 sw_pp_rgb_planar_u;
  u16 sw_rgb_range_max_u;
  u8 sw_pp_out_rgb_fmt_u;
  u8 sw_pp_out_p010_fmt_u;
  u8 sw_pp_status_u;
  u8 sw_pp_out_tile_e_u;
  u8 sw_pp_out_mode;
  u8 sw_pp_cr_first;
  u8 sw_pp_out_e_u;
  u8 sw_pp_in_a2_swap_u;
  u8 sw_pp_in_a1_swap_u;
  u8 sw_pp_out_swap_u;
  u8 sw_pp_in_swap_u;
  u16 sw_rgb_range_min_u;
  u8 sw_pp_in_format_u;
  u8 sw_hor_scale_mode_u;
  u8 sw_ver_scale_mode_u;
  u8 sw_pp_out_format_u;
  u32 sw_scale_hratio_u;
  u8 sw_rangemap_y_e_u;
  u8 sw_rangemap_c_e_u;
  u8 sw_ycbcr_range_u;
  u8 sw_pp_vc1_adv_e_u;
  u8 sw_rangemap_coef_y_u;
  u8 sw_rangemap_coef_c_u;
  u32 sw_scale_wratio_u;
  u16 sw_wscale_invra_u;
  u16 sw_hscale_invra_u;
  u32 sw_pp_out_lu_base_u_msb;
  u32 sw_pp_out_r_base_u_msb;
  u32 sw_pp_out_lu_base_u;
  u32 sw_pp_out_r_base_u;
  u32 sw_pp_out_ch_base_u_msb;
  u32 sw_pp_out_g_base_u_msb;
  u32 sw_pp_out_ch_base_u;
  u32 sw_pp_out_g_base_u;
  u16 sw_pp_out_y_stride;
  u16 sw_pp_out_c_stride;
  u8 sw_flip_mode_u;
  u16 sw_crop_startx_u;
  u8 sw_rotation_mode_u;
  u16 sw_crop_starty_u;
  u16 sw_pp_in_width_u;
  u16 sw_pp_in_height_u;
  u16 sw_pp_out_width_u;
  u16 sw_pp_out_height_u;
  u32 sw_pp_out_lu_bot_base_u_msb;
  u32 sw_pp_out_b_base_u_msb;
  u32 sw_pp_out_lu_bot_base_u;
  u32 sw_pp_out_b_base_u;
  u32 sw_pp_out_ch_bot_base_u_msb;
  u16 sw_pp_crop2_startx_u;
  u16 sw_pp_crop2_starty_u;
  u32 sw_pp_out_ch_bot_base_u;
  u16 sw_pp_crop2_out_width_u;
  u16 sw_pp_crop2_out_height_u;
  u16 sw_pp_in_y_stride;
  u16 sw_pp_in_c_stride;
  u32 sw_pp_in_lu_base_u_msb;
  u32 sw_pp_in_lu_base_u;
  u32 sw_pp_in_ch_base_u_msb;
  u32 sw_pp_in_ch_base_u;
  u8 sw_pp1_rgb_planar_u;
  u8 sw_pp1_out_rgb_fmt_u;
  u8 sw_pp1_out_p010_fmt_u;
  u8 sw_pp1_out_tile_e_u;
  u8 sw_pp1_out_mode;
  u8 sw_pp1_cr_first;
  u8 sw_pp1_out_e_u;
  u8 sw_pp1_out_swap_u;
  u8 sw_pp1_hor_scale_mode_u;
  u8 sw_pp1_ver_scale_mode_u;
  u8 sw_pp1_out_format_u;
  u32 sw_pp1_scale_hratio_u;
  u32 sw_pp1_scale_wratio_u;
  u16 sw_pp1_wscale_invra_u;
  u16 sw_pp1_hscale_invra_u;
  u32 sw_pp1_out_lu_base_u_msb;
  u32 sw_pp1_out_r_base_u_msb;
  u32 sw_pp1_out_lu_base_u;
  u32 sw_pp1_out_r_base_u;
  u32 sw_pp1_out_ch_base_u_msb;
  u32 sw_pp1_out_g_base_u_msb;
  u32 sw_pp1_out_ch_base_u;
  u32 sw_pp1_out_g_base_u;
  u16 sw_pp1_out_y_stride;
  u16 sw_pp1_out_c_stride;
  u8 sw_pp1_flip_mode_u;
  u16 sw_pp1_crop_startx_u;
  u8 sw_pp1_rotation_mode_u;
  u16 sw_pp1_crop_starty_u;
  u16 sw_pp1_in_width_u;
  u16 sw_pp1_in_height_u;
  u16 sw_pp1_out_width_u;
  u16 sw_pp1_out_height_u;
  u32 sw_pp1_out_lu_bot_base_u_msb;
  u32 sw_pp1_out_b_base_u_msb;
  u32 sw_pp1_out_lu_bot_base_u;
  u32 sw_pp1_out_b_base_u;
  u32 sw_pp1_out_ch_bot_base_u_msb;
  u16 sw_pp1_crop2_startx_u;
  u16 sw_pp1_crop2_starty_u;
  u32 sw_pp1_out_ch_bot_base_u;
  u16 sw_pp1_crop2_out_width_u;
  u16 sw_pp1_crop2_out_height_u;
  u8 sw_pp2_rgb_planar_u;
  u8 sw_pp2_out_rgb_fmt_u;
  u8 sw_pp2_out_p010_fmt_u;
  u8 sw_pp2_out_tile_e_u;
  u8 sw_pp2_out_mode;
  u8 sw_pp2_cr_first;
  u8 sw_pp2_out_e_u;
  u8 sw_pp2_out_swap_u;
  u8 sw_pp2_hor_scale_mode_u;
  u8 sw_pp2_ver_scale_mode_u;
  u8 sw_pp2_out_format_u;
  u32 sw_pp2_scale_hratio_u;
  u32 sw_pp2_scale_wratio_u;
  u16 sw_pp2_wscale_invra_u;
  u16 sw_pp2_hscale_invra_u;
  u32 sw_pp2_out_lu_base_u_msb;
  u32 sw_pp2_out_r_base_u_msb;
  u32 sw_pp2_out_lu_base_u;
  u32 sw_pp2_out_r_base_u;
  u32 sw_pp2_out_ch_base_u_msb;
  u32 sw_pp2_out_g_base_u_msb;
  u32 sw_pp2_out_ch_base_u;
  u32 sw_pp2_out_g_base_u;
  u16 sw_pp2_out_y_stride;
  u16 sw_pp2_out_c_stride;
  u8 sw_pp2_flip_mode_u;
  u16 sw_pp2_crop_startx_u;
  u8 sw_pp2_rotation_mode_u;
  u16 sw_pp2_crop_starty_u;
  u16 sw_pp2_in_width_u;
  u16 sw_pp2_in_height_u;
  u16 sw_pp2_out_width_u;
  u16 sw_pp2_out_height_u;
  u32 sw_pp2_out_lu_bot_base_u_msb;
  u32 sw_pp2_out_b_base_u_msb;
  u32 sw_pp2_out_lu_bot_base_u;
  u32 sw_pp2_out_b_base_u;
  u32 sw_pp2_out_ch_bot_base_u_msb;
  u16 sw_pp2_crop2_startx_u;
  u16 sw_pp2_crop2_starty_u;
  u32 sw_pp2_out_ch_bot_base_u;
  u16 sw_pp2_crop2_out_width_u;
  u16 sw_pp2_crop2_out_height_u;
  u8 sw_pp3_rgb_planar_u;
  u8 sw_pp3_out_rgb_fmt_u;
  u8 sw_pp3_out_p010_fmt_u;
  u8 sw_pp3_out_tile_e_u;
  u8 sw_pp3_out_mode;
  u8 sw_pp3_cr_first;
  u8 sw_pp3_out_e_u;
  u8 sw_pp3_out_swap_u;
  u8 sw_pp3_hor_scale_mode_u;
  u8 sw_pp3_ver_scale_mode_u;
  u8 sw_pp3_out_format_u;
  u32 sw_pp3_scale_hratio_u;
  u32 sw_pp3_scale_wratio_u;
  u16 sw_pp3_wscale_invra_u;
  u16 sw_pp3_hscale_invra_u;
  u32 sw_pp3_out_lu_base_u_msb;
  u32 sw_pp3_out_r_base_u_msb;
  u32 sw_pp3_out_lu_base_u;
  u32 sw_pp3_out_r_base_u;
  u32 sw_pp3_out_ch_base_u_msb;
  u32 sw_pp3_out_g_base_u_msb;
  u32 sw_pp3_out_ch_base_u;
  u32 sw_pp3_out_g_base_u;
  u16 sw_pp3_out_y_stride;
  u16 sw_pp3_out_c_stride;
  u8 sw_pp3_flip_mode_u;
  u16 sw_pp3_crop_startx_u;
  u8 sw_pp3_rotation_mode_u;
  u16 sw_pp3_crop_starty_u;
  u16 sw_pp3_in_width_u;
  u16 sw_pp3_in_height_u;
  u16 sw_pp3_out_width_u;
  u16 sw_pp3_out_height_u;
  u32 sw_pp3_out_lu_bot_base_u_msb;
  u32 sw_pp3_out_b_base_u_msb;
  u32 sw_pp3_out_lu_bot_base_u;
  u32 sw_pp3_out_b_base_u;
  u32 sw_pp3_out_ch_bot_base_u_msb;
  u16 sw_pp3_crop2_startx_u;
  u16 sw_pp3_crop2_starty_u;
  u32 sw_pp3_out_ch_bot_base_u;
  u16 sw_pp3_crop2_out_width_u;
  u16 sw_pp3_crop2_out_height_u;
  u8 sw_dither_select_r_u;
  u8 sw_dither_select_g_u;
  u8 sw_dither_select_b_u;
  u16 sw_contrast_off2_u;
  u16 sw_contrast_off1_u;
  u16 sw_contrast_thr1_u;
  u16 sw_contrast_thr2_u;
  u16 sw_color_coefff_u;
  u16 sw_color_coeffa2_u;
  u16 sw_color_coeffa1_u;
  u16 sw_color_coeffc_u;
  u16 sw_color_coeffb_u;
  u16 sw_color_coeffe_u;
  u16 sw_color_coeffd_u;
  u8 sw_pp1_dither_select_r_u;
  u8 sw_pp1_dither_select_g_u;
  u8 sw_pp1_dither_select_b_u;
  u16 sw_pp1_contrast_off2_u;
  u16 sw_pp1_contrast_off1_u;
  u16 sw_pp1_contrast_thr1_u;
  u16 sw_pp1_contrast_thr2_u;
  u16 sw_pp1_color_coefff_u;
  u16 sw_pp1_color_coeffa2_u;
  u16 sw_pp1_color_coeffa1_u;
  u16 sw_pp1_color_coeffc_u;
  u16 sw_pp1_color_coeffb_u;
  u16 sw_pp1_color_coeffe_u;
  u16 sw_pp1_color_coeffd_u;
  u8 sw_pp2_dither_select_r_u;
  u8 sw_pp2_dither_select_g_u;
  u8 sw_pp2_dither_select_b_u;
  u16 sw_pp2_contrast_off2_u;
  u16 sw_pp2_contrast_off1_u;
  u16 sw_pp2_contrast_thr1_u;
  u16 sw_pp2_contrast_thr2_u;
  u16 sw_pp2_color_coefff_u;
  u16 sw_pp2_color_coeffa2_u;
  u16 sw_pp2_color_coeffa1_u;
  u16 sw_pp2_color_coeffc_u;
  u16 sw_pp2_color_coeffb_u;
  u16 sw_pp2_color_coeffe_u;
  u16 sw_pp2_color_coeffd_u;
  u8 sw_pp3_dither_select_r_u;
  u8 sw_pp3_dither_select_g_u;
  u8 sw_pp3_dither_select_b_u;
  u16 sw_pp3_contrast_off2_u;
  u16 sw_pp3_contrast_off1_u;
  u16 sw_pp3_contrast_thr1_u;
  u16 sw_pp3_contrast_thr2_u;
  u16 sw_pp3_color_coefff_u;
  u16 sw_pp3_color_coeffa2_u;
  u16 sw_pp3_color_coeffa1_u;
  u16 sw_pp3_color_coeffc_u;
  u16 sw_pp3_color_coeffb_u;
  u16 sw_pp3_color_coeffe_u;
  u16 sw_pp3_color_coeffd_u;
  u8 sw_delogo0_mode_u;
  u8 sw_delogo0_show_border_u;
  u16 sw_delogo0_w_u;
  u16 sw_delogo0_h_u;
  u16 sw_delogo0_x_u;
  u16 sw_delogo0_y_u;
  u16 sw_delogo0_filly_u;
  u16 sw_delogo0_fillu_u;
  u16 sw_delogo0_fillv_u;
  u8 sw_delogo1_mode_u;
  u8 sw_delogo1_show_border_u;
  u16 sw_delogo1_w_u;
  u16 sw_delogo1_h_u;
  u16 sw_delogo1_x_u;
  u16 sw_delogo1_y_u;
  u16 sw_delogo1_filly_u;
  u16 sw_delogo1_fillu_u;
  u16 sw_delogo1_fillv_u;
  u16 sw_delogo0_ratio_w_u;
  u16 sw_delogo0_ratio_h_u;
  u8 sw_pp0_wscale_invra_ext_u;
  u8 sw_pp0_hcale_invra_ext_u;
  u8 sw_pp1_wscale_invra_ext_u;
  u8 sw_pp1_hcale_invra_ext_u;
  u32 sw_pp0_lanczos_tbl_base_u_msb;
  u32 sw_pp0_lanczos_tbl_base_u;
  u32 sw_pp1_lanczos_tbl_base_u_msb;
  u32 sw_pp1_lanczos_tbl_base_u;
  u8 sw_pp2_wscale_invra_ext_u;
  u8 sw_pp2_hcale_invra_ext_u;
  u8 sw_pp3_wscale_invra_ext_u;
  u8 sw_pp3_hcale_invra_ext_u;
  u32 sw_pp2_lanczos_tbl_base_u_msb;
  u32 sw_pp2_lanczos_tbl_base_u;
  u32 sw_pp3_lanczos_tbl_base_u_msb;
  u32 sw_pp3_lanczos_tbl_base_u;
  u8 sw_pp4_rgb_planar_u;
  u8 sw_pp4_out_rgb_fmt_u;
  u8 sw_pp4_out_p010_fmt_u;
  u8 sw_pp4_out_tile_e_u;
  u8 sw_pp4_out_mode;
  u8 sw_pp4_cr_first;
  u8 sw_pp4_out_e_u;
  u8 sw_pp4_out_swap_u;
  u8 sw_pp4_hor_scale_mode_u;
  u8 sw_pp4_ver_scale_mode_u;
  u8 sw_pp4_out_format_u;
  u32 sw_pp4_scale_hratio_u;
  u32 sw_pp4_scale_wratio_u;
  u16 sw_pp4_wscale_invra_u;
  u16 sw_pp4_hscale_invra_u;
  u32 sw_pp4_out_lu_base_u_msb;
  u32 sw_pp4_out_r_base_u_msb;
  u32 sw_pp4_out_lu_base_u;
  u32 sw_pp4_out_r_base_u;
  u32 sw_pp4_out_ch_base_u_msb;
  u32 sw_pp4_out_g_base_u_msb;
  u32 sw_pp4_out_ch_base_u;
  u32 sw_pp4_out_g_base_u;
  u16 sw_pp4_out_y_stride;
  u16 sw_pp4_out_c_stride;
  u8 sw_pp4_flip_mode_u;
  u16 sw_pp4_crop_startx_u;
  u8 sw_pp4_rotation_mode_u;
  u16 sw_pp4_crop_starty_u;
  u16 sw_pp4_in_width_u;
  u16 sw_pp4_in_height_u;
  u16 sw_pp4_out_width_u;
  u16 sw_pp4_out_height_u;
  u32 sw_pp4_out_lu_bot_base_u_msb;
  u32 sw_pp4_out_b_base_u_msb;
  u32 sw_pp4_out_lu_bot_base_u;
  u32 sw_pp4_out_b_base_u;
  u32 sw_pp4_out_ch_bot_base_u_msb;
  u16 sw_pp4_crop2_startx_u;
  u16 sw_pp4_crop2_starty_u;
  u32 sw_pp4_out_ch_bot_base_u;
  u16 sw_pp4_crop2_out_width_u;
  u16 sw_pp4_crop2_out_height_u;
  u8 sw_pp4_dither_select_r_u;
  u8 sw_pp4_dither_select_g_u;
  u8 sw_pp4_dither_select_b_u;
  u16 sw_pp4_contrast_off2_u;
  u16 sw_pp4_contrast_off1_u;
  u16 sw_pp4_contrast_thr1_u;
  u16 sw_pp4_contrast_thr2_u;
  u16 sw_pp4_color_coefff_u;
  u16 sw_pp4_color_coeffa2_u;
  u16 sw_pp4_color_coeffa1_u;
  u16 sw_pp4_color_coeffc_u;
  u16 sw_pp4_color_coeffb_u;
  u16 sw_pp4_color_coeffe_u;
  u16 sw_pp4_color_coeffd_u;
  u8 sw_pp4_wscale_invra_ext_u;
  u8 sw_pp4_hcale_invra_ext_u;
  u32 sw_pp4_lanczos_tbl_base_u_msb;
  u32 sw_pp4_lanczos_tbl_base_u;
  u8 sw_dec_timeout_e; /* g1 */
  u8 sw_dec_strswap32_e; /* g1 */
  u8 sw_dec_strendian_e; /* g1 */
  u8 sw_dec_inswap32_e; /* g1 */
  u8 sw_dec_outswap32_e; /* g1 */
  u8 sw_dec_data_disc_e; /* g1 */
  u8 sw_dec_2chan_dis; /* g1 */
  u8 sw_dec_out_tiled_e; /* g1 */
  u8 sw_dec_latency; /* g1 */
  u8 sw_dec_in_endian; /* g1 */
  u8 sw_dec_out_endian; /* g1 */
  u8 sw_priority_mode; /* g1 */
  u8 sw_dec_adv_pre_dis; /* g1 */
  u8 sw_dec_scmd_dis; /* g1 */
  u8 sw_dec_mode_g1v6; /* g1 */
  u8 sw_rlc_mode_e_g1v6; /* g1 */
  u8 sw_dec_ahb_hlock_e; /* g1 */
  u8 sw_stream_len_ext; /* g1 */
  u8 sw_vp8_ch_base_e; /* g1 */
  u32 sw_dir_mv_base2; /* g1 */
  u8 sw_refbu_e; /* g1 */
  u16 sw_refbu_thr; /* g1 */
  u8 sw_refbu_picid; /* g1 */
  u8 sw_refbu_eval_e; /* g1 */
  u8 sw_refbu_fparmod_e; /* g1 */
  u16 sw_refbu_y_offset; /* g1 */
  u16 sw_refbu_hit_sum; /* g1 */
  u16 sw_refbu_intra_sum; /* g1 */
  u32 sw_refbu_y_mv_sum; /* g1 */
  u8 sw_refbu2_buf_e; /* g1 */
  u16 sw_refbu2_thr; /* g1 */
  u8 sw_refbu2_picid; /* g1 */
  u16 sw_refbu_top_sum; /* g1 */
  u16 sw_refbu_bot_sum; /* g1 */
  u32 sw_dec_ch_base_msb; /* g1 */
  u8 sw_ch_base_msb_e; /* g1 */
  u32 sw_refer0_ch_base_msb; /* g1 */
  u32 sw_refer1_ch_base_msb; /* g1 */
  u32 sw_refer2_ch_base_msb; /* g1 */
  u32 sw_refer3_ch_base_msb; /* g1 */
  u32 sw_refer4_ch_base_msb; /* g1 */
  u32 sw_refer5_ch_base_msb; /* g1 */
  u32 sw_refer6_ch_base_msb; /* g1 */
  u32 sw_refer7_ch_base_msb; /* g1 */
  u32 sw_refer8_ch_base_msb; /* g1 */
  u32 sw_refer9_ch_base_msb; /* g1 */
  u32 sw_refer10_ch_base_msb; /* g1 */
  u32 sw_refer11_ch_base_msb; /* g1 */
  u32 sw_refer12_ch_base_msb; /* g1 */
  u32 sw_refer13_ch_base_msb; /* g1 */
  u32 sw_refer14_ch_base_msb; /* g1 */
  u32 sw_refer15_ch_base_msb; /* g1 */
  u32 sw_dir_mv_base_msb2; /* g1 */
  u8 sw_pp_bus_int; /* g1 */
  u8 sw_pp_rdy_int; /* g1 */
  u8 sw_pp_irq; /* g1 */
  u8 sw_pp_irq_dis; /* g1 */
  u8 sw_pp_pipeline_e; /* g1 */
  u8 sw_pp_e; /* g1 */
  u8 sw_pp_axi_rd_id; /* g1 */
  u8 sw_pp_axi_wr_id; /* g1 */
  u8 sw_pp_ahb_hlock_e; /* g1 */
  u8 sw_pp_scmd_dis; /* g1 */
  u8 sw_pp_in_a2_endsel; /* g1 */
  u8 sw_pp_in_a1_swap32; /* g1 */
  u8 sw_pp_in_a1_endian; /* g1 */
  u8 sw_pp_in_swap32_e; /* g1 */
  u8 sw_pp_data_disc_e; /* g1 */
  u8 sw_pp_clk_gate_e; /* g1 */
  u8 sw_pp_in_endian; /* g1 */
  u8 sw_pp_out_endian; /* g1 */
  u8 sw_pp_out_swap32_e; /* g1 */
  u8 sw_pp_max_burst; /* g1 */
  u8 sw_deint_e; /* g1 */
  u16 sw_deint_threshold; /* g1 */
  u8 sw_deint_blend_e; /* g1 */
  u16 sw_deint_edge_det; /* g1 */
  u32 sw_pp_in_lu_base; /* g1 */
  u32 sw_pp_in_cb_base; /* g1 */
  u32 sw_pp_in_cr_base; /* g1 */
  u32 sw_pp_out_lu_base; /* g1 */
  u32 sw_pp_out_ch_base; /* g1 */
  u8 sw_contrast_thr1; /* g1 */
  u16 sw_contrast_off2; /* g1 */
  u16 sw_contrast_off1; /* g1 */
  u8 sw_pp_in_start_ch; /* g1 */
  u8 sw_pp_in_cr_first; /* g1 */
  u8 sw_pp_out_start_ch; /* g1 */
  u8 sw_pp_out_cr_first; /* g1 */
  u16 sw_color_coeffa2; /* g1 */
  u16 sw_color_coeffa1; /* g1 */
  u8 sw_contrast_thr2; /* g1 */
  u8 sw_pp_out_h_ext; /* g1 */
  u16 sw_color_coeffd; /* g1 */
  u16 sw_color_coeffc; /* g1 */
  u16 sw_color_coeffb; /* g1 */
  u8 sw_pp_out_w_ext; /* g1 */
  u16 sw_crop_startx; /* g1 */
  u8 sw_rotation_mode; /* g1 */
  u8 sw_color_coefff; /* g1 */
  u16 sw_color_coeffe; /* g1 */
  u8 sw_crop_starty; /* g1 */
  u8 sw_rangemap_coef_y; /* g1 */
  u8 sw_pp_in_height; /* g1 */
  u16 sw_pp_in_width; /* g1 */
  u32 sw_pp_bot_yin_base; /* g1 */
  u32 sw_pp_bot_cin_base; /* g1 */
  u8 sw_rangemap_y_e; /* g1 */
  u8 sw_rangemap_c_e; /* g1 */
  u8 sw_ycbcr_range; /* g1 */
  u8 sw_rgb_pix_in32; /* g1 */
  u8 sw_rgb_r_padd; /* g1 */
  u8 sw_rgb_g_padd; /* g1 */
  u32 sw_scale_wratio; /* g1 */
  u8 sw_pp_fast_scale_e; /* g1 */
  u8 sw_pp_in_struct; /* g1 */
  u8 sw_hor_scale_mode; /* g1 */
  u8 sw_ver_scale_mode; /* g1 */
  u8 sw_rgb_b_padd; /* g1 */
  u32 sw_scale_hratio; /* g1 */
  u16 sw_wscale_invra; /* g1 */
  u16 sw_hscale_invra; /* g1 */
  u32 sw_r_mask; /* g1 */
  u32 sw_g_mask; /* g1 */
  u32 sw_b_mask; /* g1 */
  u8 sw_pp_in_format; /* g1 */
  u8 sw_pp_out_format; /* g1 */
  u16 sw_pp_out_height; /* g1 */
  u16 sw_pp_out_width; /* g1 */
  u8 sw_pp_out_tiled_e; /* g1 */
  u8 sw_pp_out_swap16_e; /* g1 */
  u8 sw_pp_crop8_r_e; /* g1 */
  u8 sw_pp_crop8_d_e; /* g1 */
  u8 sw_pp_in_format_es; /* g1 */
  u8 sw_rangemap_coef_c; /* g1 */
  u8 sw_mask1_ablend_e; /* g1 */
  u16 sw_mask1_starty; /* g1 */
  u16 sw_mask1_startx; /* g1 */
  u8 sw_mask1_startx_ext; /* g1 */
  u8 sw_mask1_starty_ext; /* g1 */
  u8 sw_mask2_startx_ext; /* g1 */
  u8 sw_mask2_starty_ext; /* g1 */
  u8 sw_mask2_ablend_e; /* g1 */
  u16 sw_mask2_starty; /* g1 */
  u16 sw_mask2_startx; /* g1 */
  u16 sw_ext_orig_width; /* g1 */
  u8 sw_mask1_e; /* g1 */
  u16 sw_mask1_endy; /* g1 */
  u16 sw_mask1_endx; /* g1 */
  u8 sw_mask1_endx_ext; /* g1 */
  u8 sw_mask1_endy_ext; /* g1 */
  u8 sw_mask2_endx_ext; /* g1 */
  u8 sw_mask2_endy_ext; /* g1 */
  u8 sw_mask2_e; /* g1 */
  u16 sw_mask2_endy; /* g1 */
  u16 sw_mask2_endx; /* g1 */
  u8 sw_right_cross_e; /* g1 */
  u8 sw_left_cross_e; /* g1 */
  u8 sw_up_cross_e; /* g1 */
  u8 sw_down_cross_e; /* g1 */
  u16 sw_up_cross; /* g1 */
  u8 sw_down_cross_ext; /* g1 */
  u16 sw_down_cross; /* g1 */
  u8 sw_dither_select_r; /* g1 */
  u8 sw_dither_select_g; /* g1 */
  u8 sw_dither_select_b; /* g1 */
  u8 sw_pp_tiled_mode; /* g1 */
  u16 sw_right_cross; /* g1 */
  u16 sw_left_cross; /* g1 */
  u8 sw_pp_in_h_ext; /* g1 */
  u8 sw_pp_in_w_ext; /* g1 */
  u8 sw_crop_starty_ext; /* g1 */
  u8 sw_crop_startx_ext; /* g1 */
  u8 sw_right_cross_ext; /* g1 */
  u8 sw_left_cross_ext; /* g1 */
  u8 sw_up_cross_ext; /* g1 */
  u16 sw_display_width; /* g1 */
  u32 sw_ablend1_base; /* g1 */
  u32 sw_ablend2_base; /* g1 */
  u16 sw_ablend2_scanl; /* g1 */
  u16 sw_ablend1_scanl; /* g1 */
  u32 sw_pp_in_lu_base_msb; /* g1 */
  u32 sw_pp_in_cb_base_msb; /* g1 */
  u32 sw_pp_in_cr_base_msb; /* g1 */
  u32 sw_pp_out_lu_base_msb; /* g1 */
  u32 sw_pp_out_ch_base_msb; /* g1 */
  u32 sw_pp_bot_yin_base_msb; /* g1 */
  u32 sw_pp_bot_cin_base_msb; /* g1 */
  u32 sw_ablend1_base_msb; /* g1 */
  u32 sw_ablend2_base_msb; /* g1 */
  u8 sw_buff_id; /* g1 */
  u8 sw_dec_out_swap; /* g1 */
  u8 sw_swap_64bit_r; /* g1 */
  u8 sw_swap_64bit_w; /* g1 */
  u8 sw_external_timeout_override_e; /* g1 */
  u32 sw_external_timeout_cycles; /* g1 */
  u8 sw_pp_axi_rd_id_u; /* g1 */
  u8 sw_pp_axi_wr_id_u; /* g1 */
  u16 sw_pp_out_pixel_lines_u; /* g1 */
  u8 sw_dec_busbusy; /* g2 */
  u8 sw_dec_tab0_swap; /* g2 */
  u8 sw_dec_tab1_swap; /* g2 */
  u8 sw_dec_tab2_swap; /* g2 */
  u8 sw_dec_tab3_swap; /* g2 */
  u8 sw_dec_rscan_swap; /* g2 */
  u8 sw_dec_comp_table_swap; /* g2 */
  u8 sw_dec_out_rs_e; /* g2 */
  u8 sw_output_8_bits; /* g2 */
  u8 sw_output_format; /* g2 */
  u8 sw_init_qp_v0; /* g2 */
  u8 sw_num_tile_cols_v0; /* g2 */
  u8 sw_num_tile_rows_v0; /* g2 */
  u32 sw_busbusy_cycles; /* g2 */
  u8 sw_dec_clk_gate_idle_e; /* g2 */
  u32 sw_dec_rsy_base_msb; /* g2 */
  u32 sw_dec_rsy_base; /* g2 */
  u32 sw_dec_rsc_base_msb; /* g2 */
  u32 sw_dec_rsc_base; /* g2 */
  u8 sw_dec_ds_e; /* g2 */
  u8 sw_dec_ds_y; /* g2 */
  u8 sw_dec_ds_x; /* g2 */
  u32 sw_dec_dsy_base_msb; /* g2 */
  u32 sw_dec_dsy_base; /* g2 */
  u32 sw_dec_dsc_base_msb; /* g2 */
  u32 sw_dec_dsc_base; /* g2 */
  u16 sw_unique_id;
};

struct VvcSwCtrl {
  /* VPS */
  u32 vps_max_layer:7;    /* FIXME: just for cmodel printing. */
  /* SPS */
  u32 sps_bit_depth:4;
  u32 sps_6param_affine_enabled_flag:1;
  u32 sps_act_enabled_flag:1;
  u32 sps_affine_amvr_enabled_flag:1;
  u32 sps_affine_enabled_flag:1;
  u32 sps_alf_enabled_flag:1;
  u32 sps_amvr_enabled_flag:1;
  u32 sps_bcw_enabled_flag:1;
  u32 sps_bdpcm_enabled_flag:1;
  u32 sps_ccalf_enabled_flag:1;
  u32 sps_chroma_format_idc;
  u32 sps_ciip_enabled_flag:1;
  u32 sps_entropy_coding_sync_enabled_flag:1;
  u32 sps_entry_point_offsets_present_flag:1;
  u32 sps_explicit_mts_inter_enabled_flag:1;
  u32 sps_explicit_mts_intra_enabled_flag:1;
  u32 sps_gpm_enabled_flag:1;
  u32 sps_idr_rpl_present_flag:1;
  u32 sps_inter_layer_prediction_enabled_flag:1;
  u32 sps_joint_cbcr_enabled_flag:1;
  u32 sps_lmcs_enabled_flag:1;
  u32 sps_lfnst_enabled_flag:1;
  u32 sps_long_term_ref_pics_flag:1;
  u32 sps_log2_ctu_size:3;
  u32 sps_log2_min_luma_coding_block_size:3;
  u32 sps_log2_transform_skip_max_size_minus2:2;
  u32 sps_log2_parallel_merge_level_minus2:3;
  u32 sps_max_luma_transform_size_64_flag:1;
  u32 sps_mts_enabled_flag:1;
  u32 sps_num_ref_pic_lists0:7;
  u32 sps_num_ref_pic_lists1:7;
  u32 sps_palette_enabled_flag:1;
  u32 sps_qtbtt_dual_tree_intra_flag:1;
  u32 sps_sao_enabled_flag:1;
  u32 sps_sbt_enabled_flag:1;
  u32 sps_smvd_enabled_flag:1;
  u32 sps_subpic_info_present_flag:1;
  u32 sps_transform_skip_enabled_flag:1;
  u32 sps_temporal_mvp_enabled_flag:1;
  u32 sps_mmvd_enabled_flag:1;
  u32 sps_isp_enabled_flag:1;
  u32 sps_mrl_enabled_flag:1;
  u32 sps_mip_enabled_flag:1;
  u32 sps_cclm_enabled_flag:1;
  u32 sps_chroma_horizontal_collocated_flag:1;
  u32 sps_chroma_vertical_collocated_flag:1;
  u32 sps_ibc_enabled_flag:1;
  u32 sps_ladf_enabled_flag:1;
  i32 sps_ladf_lowest_interval_qp_offset:7;
  u32 sps_num_ladf_intervals_minus2:2;
  i32 sps_ladf_qp_offset[4]; /* 7 bits */
  u32 sps_scaling_matrix_for_lfnst_disabled_flag:1;
  u32 sps_scaling_matrix_for_alternative_colour_space_disabled_flag:1;
  u32 sps_scaling_matrix_designated_colour_space_flag:1;
  u32 sps_dep_quant_enabled_flag:1;
  u32 sps_sign_data_hiding_enabled_flag:1;
  u32 sps_sbtmvp_enabled_flag:1;
  u32 sps_weighted_bipred_flag:1;
  u32 sps_weighted_pred_flag:1;
  /* pps */
  u32 pps_cabac_init_present_flag:1;
  u32 pps_alf_info_in_ph_flag:1;
  //i32 pps_cb_beta_offset_div2:5;
  i32 pps_cb_qp_offset:5;
  i8  pps_cb_qp_offset_list[6];   /* 5 bits, 6 elements*/
  i8  pps_cr_qp_offset_list[6];   /* 5 bits, 6 elements*/
  i8  pps_joint_cbcr_qp_offset_list[6];   /* 5 bits, 6 elements*/
  //i32 pps_cb_tc_offset_div2:5;
  u32 pps_chroma_tool_offsets_present_flag:1;
  //i32 pps_cr_beta_offset_div2:5;
  i32 pps_cr_qp_offset:5;
  //i32 pps_cr_tc_offset_div2:5;
  u32 pps_cu_chroma_qp_offset_list_enabled_flag:1;
  u32 pps_chroma_qp_offset_list_len_minus1:3;
  u32 pps_cu_qp_delta_enabled_flag:1;
  u32 pps_dbf_info_in_ph_flag:1;
  u32 pps_deblocking_filter_disabled_flag:1;
  u32 pps_deblocking_filter_override_enabled_flag:1;
  i32 pps_init_qp_minus26:7;
  i32 pps_joint_cbcr_qp_offset_value:5;
  u32 pps_loop_filter_across_slices_enabled_flag:1;
  u32 pps_loop_filter_across_tiles_enabled_flag:1;
  //i32 pps_luma_beta_offset_div2:5;
  //i32 pps_luma_tc_offset_div2:5;
  u32 pps_mixed_nalu_types_in_pic_flag:1;
  u32 pps_num_ref_idx_default_active[2];  // 4 bits
  u32 pps_num_slices_in_pic;
  u32 pps_num_subpics;
  u32 pps_num_tile_columns:5;
  u32 pps_num_tile_rows:9;
  u32 pps_num_tiles;
  u32 pps_pic_height_in_luma_samples;
  u32 pps_pic_width_in_luma_samples;
  u32 pps_qp_delta_info_in_ph_flag:1;
  u32 pps_rect_slice_flag:1;
  u32 pps_ref_wraparound_enabled_flag:1;
  u32 pps_ref_wraparound_offset:12;
  u32 pps_rpl1_idx_present_flag:1;
  u32 pps_rpl_info_in_ph_flag:1;
  u32 pps_sao_info_in_ph_flag:1;
  i32 pps_scaling_win_bottom_offset;
  i32 pps_scaling_win_left_offset;
  i32 pps_scaling_win_right_offset;
  i32 pps_scaling_win_top_offset;
  u32 pps_single_slice_per_subpic_flag;
  u32 pps_slice_chroma_qp_offsets_present_flag:1;
  u32 pps_slice_header_extension_present_flag:1;
  u32 pps_subpic_id_len_minus1:4;
  u32 pps_subpic_id_mapping_present_flag:1;
  u32 pps_sh_slice_address_len:9;   /* TODO: should be saved in buffer with slice info*/
  u32 pps_tile_column_width;
  u32 pps_tile_row_height;
  u32 pps_weighted_bipred_flag:1;
  u32 pps_weighted_pred_flag:1;
  u32 pps_wp_info_in_ph_flag:1;
  /* picture header */
  u32 ph_mmvd_fullpel_only_flag:1;
  u32 ph_bdof_disabled_flag:1;
  u32 ph_dmvr_disabled_flag:1;
  u32 ph_prof_disabled_flag:1;
  i32 ph_qp_delta:8;
  u32 ph_partition_constraints_override_flag:1;
  u32 ph_chroma_residual_scale_flag:1;
  u32 ph_explicit_scaling_list_enabled_flag:1;
  u32 ph_inter_slice_allowed_flag:1;
  u32 ph_intra_slice_allowed_flag:1;
  u32 ph_joint_cbcr_sign_flag:1;
  u32 ph_lmcs_enabled_flag:1;
  u32 ph_mvd_l1_zero_flag:1;
  u32 ph_sao_luma_enabled_flag:1;
  u32 ph_sao_chroma_enabled_flag:1;
  u32 ph_temporal_mvp_enabled_flag:1;
  u32 ph_collocated_from_l0_flag:1;
  u32 ph_collocated_ref_idx:4;
  u32 ph_deblocking_filter_disabled_flag:1;
  u32 ph_alf_enabled_flag:1;
  u32 ph_alf_cb_enabled_flag:1;
  u32 ph_alf_cr_enabled_flag:1;
  u32 ph_num_alf_aps_ids_luma:3;
  u8 ph_alf_aps_id_luma[8]; /* FIXME: use 3 bits instead */
  u32 ph_alf_aps_id_chroma:3;
  u32 ph_alf_cc_cb_enabled_flag:1;
  u32 ph_alf_cc_cr_enabled_flag:1;
  u32 ph_alf_cc_cb_aps_id:3;
  u32 ph_alf_cc_cr_aps_id:3;
  i32 ph_luma_beta_offset_div2:5;
  i32 ph_luma_tc_offset_div2:5;
  i32 ph_cb_beta_offset_div2:5;
  i32 ph_cb_tc_offset_div2:5;
  i32 ph_cr_beta_offset_div2:5;
  i32 ph_cr_tc_offset_div2:5;
  u32 luma_log2_weight_denom:3;
  u32 chroma_log2_weight_denom:3;
  /* alf */
  struct {
    u32 alf_reserve_bit1:1;
    u32 alf_chroma_num_alt_filters_minus1:3;
    u32 alf_cc_cb_filters_signalled_minus1:2;
    u32 alf_cc_cr_filters_signalled_minus1:2;
  } alf_ctrl[8];
  /* derived values from spec (not syntax but intermediate variables)*/
  u32 poc_length;  /* 5 bit */
  u8 cu_qp_delta_subdiv[2];  /* 5 bit */
  u8 cu_chroma_qp_offset_subdiv[2]; /* 5 bit */
  u16 ladf_interval_lower_bound[4]; /* 12 bits */
  u8 log2_min_qt_size[3];   // 0: I slice luma; 1: P/B slice; 2: I slice chroma
  u8 max_mtt_hierarchy_depth[3];
  u8 log2_max_bt_size[3];
  u8 log2_max_tt_size[3];
  u32 num_extra_sh_bits:5;
  u32 sps_min_qp_prime_ts:4;
  u32 log2_par_mrg_level:4;
  u32 max_num_merge_cand:3;
  u32 max_num_gpm_merge_cand:3;
  u32 max_num_ibc_merge_cand:3;
  u32 max_num_subblock_merge_cand:3;
  u32 virtual_boundaries_present_flag:1;
  u32 num_ver_virtual_boundaries:2;
  u32 num_hor_virtual_boundaries:2;
  u32 virtual_boundary_pos_x[3]; // 10 bits, in unit of 8 luma samples
  u32 virtual_boundary_pos_y[3]; // 10 bits, in unit of 8 luma samples
  i32 curr_poc; /* current poc */
  u32 lmcs_min_bin_idx;
  u32 lmcs_max_bin_idx;
  u32 unique_id;
  u32 slice_info_var_size;

  /* DPB related info */
  struct DpbPics {
    u32 rpr_constraints_active_flag:1; /*RprConstraintsAcitveFlag */
    u32 lterm_e:1;  /* LTRP */
    i32 scaling_win_left_offset:18;    /* pps_scaling_win_left_offset */
    u32 pic_width_in_luma_samples:12;  /* pps_pic_width_in_luma_samples / 8 */
    i32 scaling_win_top_offset:18;     /* pps_scaling_win_top_offset */
    u32 pic_height_in_luma_samples:12; /* pps_pic_height_in_luma_samples / 8 */
    u32 pic_hor_scale:16;  /* RefPicScale[i][j][0] */
    u32 pic_ver_scale:16;  /* RefPicScale[i][j][1] */
    addr_t ybase; /* luma */
    addr_t cbase; /* chroma */
    addr_t dbase; /* dmv */
    addr_t tybase;  /* RFC luma table */
    addr_t tcbase;  /* RFC Chroma table */

    u32 ystride;
    u32 cstride;
  } dpb[16];
  i16 ref_diff_poc[16]; // 16 bits poc diff with current poc
  u32 num_ref_pics:4; // total reference pictures used
  u32 long_term_flags;  // bit i indicating whether picture (15-i) is a LTRP

  /* external buffers as input to HW */
  u8 *slice_info;   /* info for slice scanning */
  u8 *chroma_qp_table;  /* chroma qp table */
  u8 *rpl;    /* RPL structs for RPL0/RPL1 from SPS, or PRL struct from picture header*/
  u16 *lmcs;  /* */
};

#endif // INCLUDE_SW_REGISTERS_H_
