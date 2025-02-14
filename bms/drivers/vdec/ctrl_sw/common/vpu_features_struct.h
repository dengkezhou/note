#ifndef __VPU_FEATURES_STRUCT_H__
#define __VPU_FEATURES_STRUCT_H__
struct DecHwFeatures {
  u32 id;
  u32 id_mask;
  /* decoding formats related */
  u32 hevc_support;
  u32 hevc_main10_support;
  u32 hevc_422_intra_support;
  u32 vp9_support;
  u32 vp9_profile2_support;
  /* G1_H264 - 0: H264 not supported; 1 - Baseline; 2 - Main; 3 - High */
  u32 h264_support;
  u32 h264_adv_support;
  u32 h264_high10_support;
  u32 h264_422_intra_support;
  u32 mpeg4_support;
  u32 custom_mpeg4_support;
  u32 mpeg2_support;
  u32 sorenson_spark_support;
  u32 vc1_support;
  u32 jpeg_support;
  u32 rv_support;
  u32 vp8_support;
  u32 webp_support;
  u32 vp7_support;
  u32 vp6_support;
  u32 avs_support;
  u32 avs_plus_support;
  u32 avs2_support;
  u32 avs2_main10_support;
  u32 av1_support;
  u32 vvc_support;
  /* resolution related */
  u32 vvc_max_dec_pic_width;
  u32 vvc_max_dec_pic_height;
  u32 av1_max_dec_pic_width;
  u32 av1_max_dec_pic_height;
  u32 hevc_max_dec_pic_width;
  u32 hevc_max_dec_pic_height;
  u32 vp9_max_dec_pic_width;
  u32 vp9_max_dec_pic_height;
  u32 h264_max_dec_pic_width;
  u32 h264_max_dec_pic_height;
  u32 mpeg4_max_dec_pic_width;
  u32 mpeg4_max_dec_pic_height;
  u32 mpeg2_max_dec_pic_width;
  u32 mpeg2_max_dec_pic_height;
  u32 sspark_max_dec_pic_width;
  u32 sspark_max_dec_pic_height;
  u32 vc1_max_dec_pic_width;
  u32 vc1_max_dec_pic_height;
  u32 rv_max_dec_pic_width;
  u32 rv_max_dec_pic_height;
  u32 vp8_max_dec_pic_width;
  u32 vp8_max_dec_pic_height;
  u32 vp7_max_dec_pic_width;
  u32 vp7_max_dec_pic_height;
  u32 vp6_max_dec_pic_width;
  u32 vp6_max_dec_pic_height;
  u32 avs_max_dec_pic_width;
  u32 avs_max_dec_pic_height;
  u32 divx_max_dec_pic_width;
  u32 divx_max_dec_pic_height;
  u32 img_max_dec_width;
  u32 img_max_dec_height;
  /* Other features */
  u32 addr64_support;
  u32 rfc_support;
  u32 qp_dump_support;
  /* decoding flow supported */
  u32 low_latency_mode_support;
  u32 vp9_hw_prob_support;
  u32 partial_decoding_support;
  /* pp related features */
  u32 max_ppu_count;
  u32 pp_standalone;
  enum {
    NO_PP = 0,
    UNFIED_PP
  } pp_version;
  u32 max_pp_out_pic_width[6];
  u32 max_pp_out_pic_height[6];
  /* down scaling is also supported when pp input size (i.e., cropping output) exceeds pp max output size */
  u32 dscale_support[6];
  u32 uscale_support[6];
  u32 crop_step_rshift;
  /* output format supported */
  u32 fmt_tile_support[6];
  u32 fmt_supertile_support[6];
  u32 fmt_p010_support;
  u32 fmt_rgb_support[6];
  u32 pp_planar_support[6];
  u32 pp_yuv420_101010_support;
  u32 second_crop_support;
  u32 fbc_support;
  u32 fbc_comp_support[6];
  u32 pp_tiled_stride_shift;
  u32 pp_support_6x;
  u32 pp_area_optimize;
  /* sub_system supported */
  enum {
  ALIGN_1B = 0,
  ALIGN_8B = 3,
  ALIGN_16B = 4,
  ALIGN_32B,
  ALIGN_64B,
  ALIGN_128B,
  ALIGN_256B,
  ALIGN_512B,
  ALIGN_1024B,
  ALIGN_2048B
  } shaper_alignment;
};
#endif
