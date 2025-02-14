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

#ifndef COMMON_SEI_H_
#define COMMON_SEI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "basetype.h"

#define MAX_DPB_SIZE 16
#define MAX_CPB_CNT 32
#define HEVC_MAX_NUM_SEQ_PARAM_SETS 16
#define MAX_PAYLOAD_NUM 64 /**< This limit will easily cover all sane streams. */
#define RESET_SEI_COUNTER(counter) do{ \
                                     if (*counter == MAX_PAYLOAD_NUM) { \
                                       *counter = 0; \
                                     } \
                                   }while(0)
#define MAX_SLICE_SEGMENTS 600
#define PAYLOAD_BYTE_SIZE 1024
#define INI_MAX 2147483647 /**< maximum (signed) int value */


/**
 * it's SEI_param status.
 * \ingroup common_group
 */
enum DecSEIStatus {
  /** \brief the sei_param is available */
  SEI_UNUSED = 0,
  /** \brief the sei_param is in use */
  SEI_CURRENT = 1,
  /** \brief the sei_param is not available */
  SEI_USED = 2
};

/**
 * \brief it's used for SEI message of variable length (The length of
 * SEI message cannot be determined before parsing).
 * \ingroup common_group
 */
typedef struct DecSEIBuffer {
  u8 *buffer; /**< \brief buffer pointer */
  u32 buffer_size; /**< \brief buffer size */
  u32 available_size; /**< \brief available data size in buffer */
} DecMetadataBuffer;

/**
 * \brief structure to store User data registered t35 SEI parameters
 * \ingroup common_group
 */
struct T35Parameters {
  u8 itu_t_t35_country_code[MAX_PAYLOAD_NUM];
  u8 itu_t_t35_country_code_extension_byte[MAX_PAYLOAD_NUM];

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< \brief length of each SEI */
  u32 counter; /**< \brief num of User data registered t35 SEI message in one frame */
};
/**
 * \brief structure to store Mastering Display Colour Volume SEI parameters
 * \ingroup common_group
 */
struct MasterDisplayParameters {
  u16 display_primaries_x[3];
  u16 display_primaries_y[3];
  u16 white_point_x;
  u16 white_point_y;
  u32 max_display_mastering_luminance;
  u32 min_display_mastering_luminance;
};

/**
 * \brief structure to store Content Light Level Info SEI parameters
 * \ingroup common_group
 */
struct LightLevelParameters {
  u16 max_content_light_level;
  u16 max_pic_average_light_level;
};

/*------------------------------------------------------------------------------
-- HEVC SEI DATA STRUCTURE
------------------------------------------------------------------------------*/
/**
 * \brief structure to store Buffering period SEI parameters
 * \ingroup hevc_group
 */
struct HevcBufPeriodParameters {
  u8 bp_seq_parameter_set_id;
  u8 irap_cpb_params_present_flag;
  u32 cpb_delay_offset;
  u32 dpb_delay_offset;
  u8 concatenation_flag;
  u32 au_cpb_removal_delay_delta; /**< \brief au_cpb_removal_delay_delta_minus1 + 1 */

  u32 nal_initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 nal_initial_cpb_removal_offset[MAX_CPB_CNT];
  u32 nal_initial_alt_cpb_removal_delay[MAX_CPB_CNT];
  u32 nal_initial_alt_cpb_removal_offset[MAX_CPB_CNT];

  u32 vcl_initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 vcl_initial_cpb_removal_offset[MAX_CPB_CNT];
  u32 vcl_initial_alt_cpb_removal_delay[MAX_CPB_CNT];
  u32 vcl_initial_alt_cpb_removal_offset[MAX_CPB_CNT];
};

/**
 * \brief structure to store Picture timing SEI parameters
 * \ingroup hevc_group
 */
struct HevcPicTimingParameters {
  u8 pic_struct;
  u8 source_scan_type;
  u8 duplicate_flage;
  u32 au_cpb_removal_delay; /**< \brief au_cpb_removal_delay_minus1 + 1 */
  u32 pic_dpb_output_delay;
  u32 pic_dpb_output_du_delay;

  u16 num_decoding_units; /**< \brief num_decoding_units_minus1 + 1 */
  u8  du_common_cpb_removal_delay_flag;
  u32 du_common_cpb_removal_delay_increment; /**< \brief du_common_cpb_removal_delay_increment_minus1 + 1 */
  u16 num_nalus_in_du[MAX_SLICE_SEGMENTS]; /**< \brief num_nalus_in_du_minus1 + 1 */
  u32 du_cpb_removal_delay_increment[MAX_SLICE_SEGMENTS]; /**< \brief du_cpb_removal_delay_increment_minus1 + 1 */
};

/**
 * \brief structure to store User Data UnRegistered SEI parameters
 * \ingroup hevc_group
 */
struct HevcUserDataUnRegParameters {
  u8 uuid_iso_iec_11578[MAX_PAYLOAD_NUM][16]; /**< \brief 128bit */

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< \brief length of each SEI */
  u32 userdataunreg_counter; /**< \brief num of User data unregistered SEI message in one frame */
};

/**
 * \brief structure to store Recovery Point SEI parameters
 * \ingroup hevc_group
 */
struct HevcRecoveryPointParameters {
  i16 recovery_poc_cnt;
  u8 exact_match_flag;
  u8 broken_link_flag;
};

/**
 * \brief structure to store Active Parameter Sets SEI parameters
 * \ingroup hevc_group
 */
struct HevcActiveParameterSet {
  u8 active_video_parameter_set_id;
  u8 self_contained_cvs_flag;
  u8 no_parameter_set_update_flag;
  u8 num_sps_ids; /**< \brief num_sps_ids_minus1 + 1 */
  u8 active_seq_parameter_set_id[HEVC_MAX_NUM_SEQ_PARAM_SETS];
};

/**
 * \brief structure to store all SEI parameters of HEVC
 * \ingroup hevc_group
 */
struct HevcSEIParameters {
  u32 bufperiod_present_flag; /**< \brief value of 1 : buf_param decode successful */
  u32 pictiming_present_flag; /**< \brief value of 1 : pic_param decode successful */
  u32 t35_present_flag; /**< \brief value of 1 : t35_param decode successful */
  u32 userdata_unreg_present_flag; /**< \brief value of 1 : userdataunreg_param decode successful */
  u32 recovery_point_present_flag; /**< \brief value of 1 : recovery_param decode successful */
  u32 active_ps_present_flag; /**< \brief value of 1 : activeps_param decode successful */
  u32 mastering_display_present_flag; /**< \brief value of 1 : masterdis_param decode successful */
  u32 lightlevel_present_flag; /**< \brief value of 1 : light_param decode successful */
  u32 preferred_trc_present_flag; /**< \brief value of 1 : preferred_transfer_characteristics decode successful */
  u32 decode_id; /**< \brief all the SEI message belong to picture with decode_id */
  enum DecSEIStatus sei_status; /**< \brief current state of SEI_param */
  struct HevcBufPeriodParameters buf_param; /**< \brief Buffering period SEI message */
  struct HevcPicTimingParameters pic_param; /**< \brief Picture timing SEI message */
  struct T35Parameters t35_param; /**< \brief User data registered t35 SEI message */
  struct HevcUserDataUnRegParameters userdataunreg_param; /**< \brief User data unregistered SEI message */
  struct HevcRecoveryPointParameters recovery_param; /**< \brief Recovery point SEI message */
  struct HevcActiveParameterSet activeps_param; /**< \brief Active parameter sets SEI message */
  struct MasterDisplayParameters masterdis_param; /**< \brief Mastering display colour volume SEI message */
  struct LightLevelParameters light_param; /**< \brief Content light level information SEI message */
  u32 preferred_transfer_characteristics; /**< \brief preferred transfer characteristics information SEI message */
};

/*------------------------------------------------------------------------------
-- VVC SEI DATA STRUCTURE
------------------------------------------------------------------------------*/
/**
 * \brief structure to store Buffering period SEI parameters
 * \ingroup hevc_group
 */
struct VvcBufPeriodParameters {
  u8 bp_seq_parameter_set_id;
  u8 irap_cpb_params_present_flag;
  u32 cpb_delay_offset;
  u32 dpb_delay_offset;
  u8 concatenation_flag;
  u32 au_cpb_removal_delay_delta_minus1;

  u32 nal_initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 nal_initial_cpb_removal_offset[MAX_CPB_CNT];
  u32 nal_initial_alt_cpb_removal_delay[MAX_CPB_CNT];
  u32 nal_initial_alt_cpb_removal_offset[MAX_CPB_CNT];

  u32 vcl_initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 vcl_initial_cpb_removal_offset[MAX_CPB_CNT];
  u32 vcl_initial_alt_cpb_removal_delay[MAX_CPB_CNT];
  u32 vcl_initial_alt_cpb_removal_offset[MAX_CPB_CNT];
};

/**
 * \brief structure to store Picture timing SEI parameters
 * \ingroup hevc_group
 */
struct VvcPicTimingParameters {
  u8 pic_struct;
  u8 source_scan_type;
  u8 duplicate_flage;
  u32 au_cpb_removal_delay; /**< \brief minus1 */
  u32 pic_dpb_output_delay;
  u32 pic_dpb_output_du_delay;

  u16 num_decoding_units_minus1;
  u8  du_common_cpb_removal_delay_flag;
  u32 du_common_cpb_removal_delay_increment_minus1;
  u16 num_nalus_in_du_minus1[MAX_SLICE_SEGMENTS];
  u32 du_cpb_removal_delay_increment_minus1[MAX_SLICE_SEGMENTS];
};

/**
 * \brief structure to store User Data Registered SEI parameters
 * \ingroup hevc_group
 */
struct VvcUserDataRegParameters {
  u8 itu_t_t35_country_code[MAX_PAYLOAD_NUM];
  u8 itu_t_t35_country_code_extension_byte[MAX_PAYLOAD_NUM];

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< \brief length of each SEI */
  u32 userdatareg_counter; /**< \brief num of User data registered SEI message in one frame */
};

/**
 * \brief structure to store User Data UnRegistered SEI parameters
 * \ingroup hevc_group
 */
struct VvcUserDataUnRegParameters {
  u8 uuid_iso_iec_11578[MAX_PAYLOAD_NUM][16]; /**< \brief 128bit */

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< \brief length of each SEI */
  u32 userdataunreg_counter; /**< \brief num of User data unregistered SEI message in one frame */
};

/**
 * \brief structure to store Recovery Point SEI parameters
 * \ingroup hevc_group
 */
struct VvcRecoveryPointParameters {
  i16 recovery_poc_cnt;
  u8 exact_match_flag;
  u8 broken_link_flag;
};

/**
 * \brief structure to store Active Parameter Sets SEI parameters
 * \ingroup hevc_group
 */
struct VvcActiveParameterSet {
  u8 active_video_parameter_set_id;
  u8 self_contained_cvs_flag;
  u8 no_parameter_set_update_flag;
  u8 num_sps_ids_minus1;
  u8 active_seq_parameter_set_id[HEVC_MAX_NUM_SEQ_PARAM_SETS];
};

/**
 * \brief structure to store Mastering Display Colour Volume SEI parameters
 * \ingroup hevc_group
 */
struct VvcMasterDisParameters {
  u16 display_primaries_x[3];
  u16 display_primaries_y[3];
  u16 white_point_x;
  u16 white_point_y;
  u32 max_display_mastering_luminance;
  u32 min_display_mastering_luminance;
};

/**
 * \brief structure to store Content Light Level Info SEI parameters
 * \ingroup hevc_group
 */
struct VvcLightLevelParameters {
  u16 max_content_light_level;
  u16 max_pic_average_light_level;
};

/**
 * \brief structure to store all SEI parameters of HEVC
 * \ingroup hevc_group
 */
struct VvcSEIParameters {
  u32 bufperiod_present_flag; /**< \brief value of 1 : buf_param decode successful */
  u32 pictiming_present_flag; /**< \brief value of 1 : pic_param decode successful */
  u32 userdata_reg_present_flag; /**< \brief value of 1 : userdatareg_param decode successful */
  u32 userdata_unreg_present_flag; /**< \brief value of 1 : userdataunreg_param decode successful */
  u32 recovery_point_present_flag; /**< \brief value of 1 : recovery_param decode successful */
  u32 active_ps_present_flag; /**< \brief value of 1 : activeps_param decode successful */
  u32 mastering_display_present_flag; /**< \brief value of 1 : masterdis_param decode successful */
  u32 lightlevel_present_flag; /**< \brief value of 1 : light_param decode successful */
  u32 decode_id; /**< \brief all the SEI message belong to picture with decode_id */
  enum DecSEIStatus sei_status; /**< \brief current state of SEI_param */
  struct VvcBufPeriodParameters buf_param; /**< \brief Buffering period SEI message */
  struct VvcPicTimingParameters pic_param; /**< \brief Picture timing SEI message */
  struct VvcUserDataRegParameters userdatareg_param; /**< \brief User data registered SEI message */
  struct VvcUserDataUnRegParameters userdataunreg_param; /**< \brief User data unregistered SEI message */
  struct VvcRecoveryPointParameters recovery_param; /**< \brief Recovery point SEI message */
  struct VvcActiveParameterSet activeps_param; /**< \brief Active parameter sets SEI message */
  struct VvcMasterDisParameters masterdis_param; /**< \brief Mastering display colour volume SEI message */
  struct VvcLightLevelParameters light_param; /**< \brief Content light level information SEI message */
};


/*------------------------------------------------------------------------------
-- H264 SEI DATA STRUCTURE
------------------------------------------------------------------------------*/
/**
 * \brief structure to store Buffering period SEI parameters
 * \ingroup h264_group
 */
struct H264BufPeriodParameters {
  u8 seq_parameter_set_id;
  u32 initial_cpb_removal_delay[MAX_CPB_CNT];
  u32 initial_cpb_removal_delay_offset[MAX_CPB_CNT];
};

/**
 * \brief structure to store Picture timing SEI parameters
 * \ingroup h264_group
 */
struct H264PicTimingParameters {
  u32 cpb_removal_delay;
  u32 dpb_output_delay;
  u8 pic_struct;
  u8 clock_timestamp_flag[3];
  u8 ct_type;
  u8 nuit_field_based_flag;
  u8 counting_type;
  u8 full_timestamp_flag;
  u8 discontinuity_flag;
  u8 cnt_dropped_flag;
  u8 n_frames;
  u8 seconds_value;
  u8 minutes_value;
  u8 hours_value;
  u8 seconds_flag;
  u8 minutes_flag;
  u8 hours_flag;
  i32 time_offset;
};

/**
 * \brief structure to store User Data UnRegistered SEI parameters
 * \ingroup h264_group
 */
struct H264UserDataUnRegParameters {
  u8 uuid_iso_iec_11578[MAX_PAYLOAD_NUM][16]; /**< \brief 128bit */

  /* PayloadByteInfo */
  struct DecSEIBuffer payload_byte;
  u32 payload_byte_length[MAX_PAYLOAD_NUM]; /**< \brief length of each SEI */
  u32 userdataunreg_counter; /**< \brief num of User data unregistered SEI message in one frame */
};

/**
 * \brief structure to store Recovery Point SEI parameters
 * \ingroup h264_group
 */
struct H264RecoveryPointParameters {
  u16 recovery_frame_cnt;
  u8 exact_match_flag;
  u8 broken_link_flag;
  u8 changing_slice_group_idc;
};

/**
 * \brief structure to store all SEI parameters of H264
 * \ingroup h264_group
 */
struct H264SEIParameters {
  u32 bufperiod_present_flag; /**< \brief value of 1 : buf_param decode successful */
  u32 pictiming_present_flag; /**< \brief value of 1 : pic_param decode successful */
  u32 t35_present_flag; /**< \brief value of 1 : t35_param decode successful */
  u32 userdata_unreg_present_flag; /**< \brief value of 1 : userdataunreg_param decode successful */
  u32 recovery_point_present_flag; /**< \brief value of 1 : recovery_param decode successful */
  u32 mastering_display_present_flag; /**< \brief value of 1 : masterdis_param decode successful */
  u32 lightlevel_present_flag; /**< \brief value of 1 : light_param decode successful */
  u32 decode_id; /**< \brief all the SEI message belong to picture with decode_id */
  enum DecSEIStatus sei_status; /**< \brief current state of SEI_param */
  struct H264BufPeriodParameters buf_param; /**< \brief Buffering period SEI message */
  struct H264PicTimingParameters pic_param; /**< \brief Picture timing SEI message */
  struct T35Parameters t35_param; /**< \brief User data registered t35 SEI message */
  struct H264UserDataUnRegParameters userdataunreg_param; /**< \brief User data unregistered SEI message */
  struct H264RecoveryPointParameters recovery_param; /**< \brief Recovery point SEI message */
  struct MasterDisplayParameters masterdis_param; /**< \brief Mastering display colour volume SEI message */
  struct LightLevelParameters light_param; /**< \brief Content light level information SEI message */
};

/**
 * OBU metadata types.
 * \ingroup common_group
 */
typedef enum {
  OBU_METADATA_TYPE_AOM_RESERVED_0 = 0,
  OBU_METADATA_TYPE_HDR_CLL = 1,
  OBU_METADATA_TYPE_HDR_MDCV = 2,
  OBU_METADATA_TYPE_SCALABILITY = 3,
  OBU_METADATA_TYPE_ITUT_T35 = 4,
  OBU_METADATA_TYPE_TIMECODE = 5,
} OBU_METADATA_TYPE;

/**
 * it's METADATA status.
 * \ingroup common_group
 */
enum MetadataStatus {
  /** \brief the metadata_param is not available */
  METADATA_UNUSED = 0,
  /** \brief the metadata_param is in use */
  METADATA_CURRENT = 1,
  /** \brief the metadata_param is available */
  METADATA_USED = 2
};

/**
 * \brief structure to store all METADATA parameters of AV1
 * \ingroup av1_group
 */
struct MetadataParameters {
  u32 t35_present_flag; /**< \brief value of 1 : t35_param decode successful */
  u32 mastering_display_present_flag; /**< \brief value of 1 : masterdis_param decode successful */
  u32 lightlevel_present_flag; /**< \brief value of 1 : light_param decode successful */
  u32 decode_id; /**< \brief all the METADATA message belong to picture with decode_id */
  enum MetadataStatus metadata_status; /**< \brief current state of METADATA_param */
  struct T35Parameters t35_param; /**< \brief User data registered t35 METADATA message */
  struct MasterDisplayParameters mdcv_param; /**< \brief Mastering display colour volume METADATA message */
  struct LightLevelParameters cll_param; /**< \brief Content light level information METADATA message */
};

/*------------------------------------------------------------------------------
-- SEI DATA STRUCTURE OF ALL DECODER
------------------------------------------------------------------------------*/
/**
 * \brief structure to store SEI parameters of all formats
 * \ingroup common_group
 */
struct DecSEIParameters {
  struct VvcSEIParameters *vvc; /**< \brief SEI parameters of VVC */
  struct HevcSEIParameters *hevc; /**< \brief SEI parameters of HEVC */
  struct H264SEIParameters *h264[2]; /**< \brief SEI parameters of H264 */
  struct MetadataParameters *av1; /**< \brief METADATA parameters of av1 */
};

#ifdef __cplusplus
}
#endif

#endif /* #ifdef COMMON_SEI_H_ */
