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

#ifndef DECTYPES_H
#define DECTYPES_H

#include "basetype.h"
#include "dwl.h"
#include "decapicommon.h"
#include "decsei.h"

/**
 * Specifies the decoder types.
 * \ingroup common_group
 */
enum DecCodec {
   /** \brief Support MPEG4 video decoder */
  DEC_MPEG4,
   /** \brief Support MPEG2 video decoder */
  DEC_MPEG2,
  /** \brief Support VP6 video decoder */
  DEC_VP6,
  /** \brief Support VP8 video decoder */
  DEC_VP8,
  /** \brief Support VP9 video decoder */
  DEC_VP9,
  /** \brief Support HEVC video decoder */
  DEC_HEVC,
  /** \brief Support H264 video decoder */
  DEC_H264,
  /** \brief Support AVS video decoder */
  DEC_AVS,
  /** \brief Support AVS2 video decoder */
  DEC_AVS2,
  /** \brief Support AV1 video decoder */
  DEC_AV1,
  /** \brief Support JPEG image decoder */
  DEC_JPEG,
  /** \brief Support VC1 video decoder */
  DEC_VC1,
  /** \brief Support RV video decoder */
  DEC_RV,
  /** \brief Support VVC video decoder */
  DEC_VVC,
  /** \brief Support Standalone Post-Processing decoder */
  DEC_PPDEC,
  /** \brief The limit on the input value of this parameter */
  DEC_FMT_MAX
};

/**
 * Specifies the return values for the decoder API functions.
 * \ingroup common_group
 */
enum DecRet {
  /** \brief Success */
  DEC_OK = 0, /**<\hideinitializer */
  /** \brief Stream processed */
  DEC_STRM_PROCESSED = 1, /**<\hideinitializer */
  /** \brief Picture available for output */
  DEC_PIC_RDY = 2, /**<\hideinitializer */
  /** \brief Picture decoded */
  DEC_PIC_DECODED = 3, /**<\hideinitializer */
  /** \brief New stream headers decoded */
  DEC_HDRS_RDY = 4, /**<\hideinitializer */
  /** \brief New stream headers decoded, data partitioned stream(mpeg4 specific) */
  DEC_DP_HDRS_RDY = 5, /**<\hideinitializer */
  /** \brief Advanced coding tools detected in stream */
  DEC_ADVANCED_TOOLS = 6, /**<\hideinitializer */
  /** \brief A slice was decoded */
  DEC_SLICE_RDY = 7, /**<\hideinitializer */
  /** \brief Output pictures must be retrieved before continuing decode */
  DEC_PENDING_FLUSH = 8, /**<\hideinitializer */
  /** \brief Skipped decoding non-reference picture */
  DEC_NONREF_PIC_SKIPPED = 9, /**<\hideinitializer */
  /** \brief End-of-stream state set in the decoder */
  DEC_END_OF_STREAM = 10,         /**<\hideinitializer */
  /** \brief End of video sequence */
  DEC_END_OF_SEQ = 11,         /**<\hideinitializer */
  /** \brief Waiting for external buffers allocated. */
  DEC_WAITING_FOR_BUFFER = 12,    /**<\hideinitializer */
  /** \brief Scan Processed(pjpeg specific) */
  DEC_SCAN_PROCESSED = 13,     /**<\hideinitializer */
  /** \brief Decoder is aborted */
  DEC_ABORTED = 14,              /**<\hideinitializer */
  /** \brief All pics have been flushed */
  DEC_FLUSHED = 15,              /**<\hideinitializer */
  /** \brief The input buffer has consumed, but the decoding has not been completed */
  DEC_BUF_EMPTY = 16,              /**<\hideinitializer */
  /** \brief Resolution changed in multiresolution video */
  DEC_RESOLUTION_CHANGED = 17,    /**<\hideinitializer */
  /** \brief video Object Sequence end marker dedected */
  DEC_VOS_END = 18,    /**<\hideinitializer */
  /** \brief VPS, PPS or SPS parse success */
  DEC_PARAM_SET_PARSED = 19,
  /** \brief SEI parse success */
  DEC_SEI_PARSED = 20,
  /** \brief Skipped decoding P/B picture. */
  DEC_PB_PIC_SKIPPED = 21,
  /** \brief Output picture is discarded internally. */
  DEC_DISCARD_INTERNAL = 22,

  /** \brief Invalid parameter was used */
  DEC_PARAM_ERROR = -1,          /**<\hideinitializer */
  /** \brief An unrecoverable error in decoding */
  DEC_STRM_ERROR = -2,           /**<\hideinitializer */
  /** \brief The decoder has not been initialized */
  DEC_NOT_INITIALIZED = -3,      /**<\hideinitializer */
  /** \brief Memory allocation failed */
  DEC_MEMFAIL = -4,              /**<\hideinitializer */
  /** \brief Initialization failed */
  DEC_INITFAIL = -5,             /**<\hideinitializer */
  /** \brief Video sequence information is not available because stream headers have not been decoded */
  DEC_HDRS_NOT_RDY = -6,         /**<\hideinitializer */
  /** \brief Video sequence frame size or tools not supported */
  DEC_STREAM_NOT_SUPPORTED = -8, /**<\hideinitializer */
  /** \brief External buffer rejected. (Too much than requested) */
  DEC_EXT_BUFFER_REJECTED = -9,    /**<\hideinitializer */
  /** \brief Invalid pp parameter was used */
  DEC_INFOPARAM_ERROR = -10,    /**<\hideinitializer */
  /** \brief ERROR */
  DEC_ERROR = -11,              /**<\hideinitializer */
  /** \brief Unsupported */
  DEC_UNSUPPORTED = -12,        /**<\hideinitializer */
  /** \brief Invalid stream length used */
  DEC_INVALID_STREAM_LENGTH = -13, /**<\hideinitializer */
  /** \brief Invalid input buffer size used */
  DEC_INVALID_INPUT_BUFFER_SIZE = -14, /**<\hideinitializer */
  /** \brief Needs to increase input buffer */
  DEC_INCREASE_INPUT_BUFFER = -15, /**<\hideinitializer */
  /** \brief Slice mode not supported for this operation type */
  DEC_SLICE_MODE_UNSUPPORTED = -16, /**<\hideinitializer */
  /** \brief Supplied metadata is in wrong format */
  DEC_METADATA_FAIL = -17,     /**<\hideinitializer */
  /** \brief Current pic don't have ref pic, need skip. */
  DEC_NO_REFERENCE = -18,
  /** \brief When parsing the VPS/SPS/PPS encounters an error */
  DEC_PARAM_SET_ERROR = -19,
  /** \brief When extracting or parsing the SEI encounters an error */
  DEC_SEI_ERROR = -20,
  /** \brief When parsing the slice header encounters an error */
  DEC_SLICE_HDR_ERROR = -21,
  /** \brief When setting ref pic for current pic encounters an error */
  DEC_REF_PICS_ERROR = -22,
  /** \brief When extracting or parsing the SEI encounters an error */
  DEC_NALUNIT_ERROR = -23,
  /** \brief When checking AU bundary encounters an error */
  DEC_AU_BOUNDARY_ERROR = -24,
  /** \brief Syntax element error found in stream */
  DEC_STREAM_ERROR_DEDECTED = -25,  /**<\hideinitializer */
  /** \brief The decoder has no available buffer */
  DEC_NO_DECODING_BUFFER = -99,  /**<\hideinitializer */
  /** \brief Driver could not reserve decoder hardware */
  DEC_HW_RESERVED = -254,        /**<\hideinitializer */
  /** \brief Hardware timeout occurred */
  DEC_HW_TIMEOUT = -255,         /**<\hideinitializer */
  /** \brief Hardware received error status from system bus */
  DEC_HW_BUS_ERROR = -256,       /**<\hideinitializer */
  /** \brief Hardware encountered an unrecoverable system error */
  DEC_SYSTEM_ERROR = -257,       /**<\hideinitializer */
  /** \brief Decoder wrapper encountered an error */
  DEC_DWL_ERROR = -258,          /**<\hideinitializer */
  /** \brief Hardware encountered an fatal system error */
  DEC_FATAL_SYSTEM_ERROR = -259,       /**<\hideinitializer */
  /** \brief Hardware EXT_Timeout occurred */
  DEC_HW_EXT_TIMEOUT = -260,         /**<\hideinitializer */
  /** \brief Evaluation limit exceeded */
  DEC_EVALUATION_LIMIT_EXCEEDED = -999, /**<\hideinitializer */
  /** \brief Video format not supported */
  DEC_FORMAT_NOT_SUPPORTED = -1000 /**<\hideinitializer */
    /* TODO(vmr): Prune what is not needed from these. */
};

/**
 * DAR : Display aspect ratio(Only used in AVS and MPEG2).
 * \ingroup common_group
 */
enum DecDARFormat{
  /** \brief Display aspect ratio 1 : 1 */
  DEC_1_1 = 0x01, /**<\hideinitializer */
  /** \brief Display aspect ratio 4 : 3 */
  DEC_4_3 = 0x02, /**<\hideinitializer */
  /** \brief Display aspect ratio 16 : 9 */
  DEC_16_9 = 0x03, /**<\hideinitializer */
  /** \brief Display aspect ratio 2.21 : 1 */
  DEC_2_21_1 = 0x04 /**<\hideinitializer */
};

/**
 * Format of the input sequence.
 * \ingroup common_group
 */
enum DecInputFormat {
  /** \brief The format of the input sequence is VP7 */
  DEC_INPUT_VP7 = 0x01, /**<\hideinitializer */
  /** \brief The format of the input sequence is VP8 */
  DEC_INPUT_VP8, /**<\hideinitializer */
  /** \brief The format of the input sequence is WEBP */
  DEC_INPUT_WEBP, /**<\hideinitializer */
  /** \brief The format of the input sequence is MPEG4 */
  DEC_INPUT_MPEG4, /**<\hideinitializer */
  /** \brief The format of the input sequence is SORENSON */
  DEC_INPUT_SORENSON, /**<\hideinitializer */
  /** \brief The format of the input sequence is CUSTOM_1 */
  DEC_INPUT_CUSTOM_1 /**<\hideinitializer */
};

/**
 * Skip some frames when decoding.
 * \ingroup common_group
 */
enum DecSkipFrameMode {
  /** \brief non_ref_recon : default value, decode all frame, but dont output
   *  recon data of non-reference frames(only hevc & h264_high10). */
  DEC_SKIP_NON_REF_RECON = 0, /**<\hideinitializer */
  /** \brief non_ref : dont decode non-reference frames. */
  DEC_SKIP_NON_REF = 1, /**<\hideinitializer */
  /** \brief none : close this feature for all function. */
  DEC_SKIP_NONE /**<\hideinitializer */
};

/**
 * Sample range of the YCbCr samples in the decoded picture.
 * \ingroup common_group
 */
enum DecVideoRange {
  /** \brief Sample range [16, 235] */
  DEC_VIDEO_RANGE_NORMAL = 0x0, /**<\hideinitializer */
  /** \brief Sample range [0, 255] */
  DEC_VIDEO_RANGE_FULL = 0x1, /**<\hideinitializer */
  /** \brief similar to DEC_VIDEO_RANGE_NORMAL */
  DEC_VIDEO_STUDIO_SWING = 0x0, /**<\hideinitializer */
  /** \brief similar to DEC_VIDEO_RANGE_FULL */
  DEC_VIDEO_FULL_SWING = 0x1 /**<\hideinitializer */
};

/**
 * Color space which be selected in the decoded picture.
 * \ingroup common_group
 */
enum DecColorSpace {
  /** \brief Color spac : YUV */
  DEC_YCbCr_BT601 = 0x0, /**<\hideinitializer */
  /** \brief Color spac : self define */
  DEC_CUSTOM = 0x1, /**<\hideinitializer */
  /** \brief Color spac : RGB */
  DEC_RGB = 0x7 /**<\hideinitializer */
};

/**
 * The type of buffer allocated.
 * \ingroup common_group
 */
enum DecBufferType {
  /** \brief reference + compression table + DMV */
  REFERENCE_BUFFER = 0, /**<\hideinitializer */
  /** \brief douwnscale scan out buffer */
  DOWNSCALE_OUT_BUFFER, /**<\hideinitializer */
  /** \brief The limit on the input value of this parameter */
  BUFFER_TYPE_NUM /**<\hideinitializer */
};

/**
 * User data type(Only used in MPEG4).
 * \ingroup common_group
 */
enum DecUserDataType {
  /** \brief The data type is VOS */
  DEC_USER_DATA_VOS = 0, /**<\hideinitializer */
  /** \brief The data type is VISO */
  DEC_USER_DATA_VISO, /**<\hideinitializer */
  /** \brief The data type is VOL */
  DEC_USER_DATA_VOL, /**<\hideinitializer */
  /** \brief The data type is GOV */
  DEC_USER_DATA_GOV /**<\hideinitializer */
};

/**
 * \brief partial tb_cfg.dec_params parameters..
 * \ingroup common_group
 */
struct DecParams {
  /**< \brief how long are the hardware data bursts; better left unchanged. */
  u32 bus_burst_length;
  /**< \brief clock is gated from decoder between images and for disabled codecs. */
  u32 clk_gate_decoder;
  /**< \brief reference buffer : memory wait states for non_seq_clk. */
  u32 non_seq_clk;
  /**< \brief reference buffer : memory wait states for seq_clk. */
  u32 seq_clk;
  /**< \brief APF threshold value. */
  i32 apf_threshold_value;
  /**< \brief AXI outstanding threshold for write. */
  u32 axi_wr_outstand;
  /**< \brief AXI outstanding threshold for read. */
  u32 axi_rd_outstand;
};

/**
 * \brief partial tb_cfg.tb_params parameters for randome error..
 * \ingroup common_group
 */
struct ErrorParams {
  /**< \brief random seed. */
  u32 seed;
  /**< \brief truncate the stream by randomize the stream length. */
  u8 truncate_stream;
  /**< \brief truncate odds. */
  char truncate_stream_odds[24];
  /**< \brief swap the stream by random swap the stream bits. */
  u8 swap_bits_in_stream;
  /**< \brief swap odds. */
  char swap_bit_odds[24];
  /**< \brief discard the stream by random discard the packets. */
  u8 lose_packets;
  /**< \brief discard odds. */
  char packet_loss_odds[24];
  /**< \brief enable or disable random error function. */
  u32 random_error_enabled;
};

/**
 * \brief User data configuration(Only used in MPEG4).
 * \ingroup common_group
 */
struct DecUserConf {
  /** \brief The type of buffer allocated. */
  enum DecUserDataType user_data_type;
  /** \brief The pointer to VOS data */
  u8  *p_user_data_vos;
  /** \brief The VOS data max length */
  u32  user_data_vosmax_len;
  /** \brief The pointer to VISO data */
  u8  *p_user_data_viso;
  /** \brief The VISO data max length */
  u32  user_data_visomax_len;
  /** \brief The pointer to VOL data */
  u8  *p_user_data_vol;
  /** \brief The VOL data max length */
  u32  user_data_volmax_len;
  /** \brief The pointer to GOV data */
  u8  *p_user_data_gov;
  /** \brief The GOV data max length */
  u32  user_data_govmax_len;
};

/**
 * \brief Cropping info.
 * \ingroup common_group
 */
struct DecCropParams {
  /** \brief The left offset value */
  u32 crop_left_offset;
  /** \brief The wigth value */
  u32 crop_out_width;
  /** \brief The top offset value */
  u32 crop_top_offset;
  /** \brief The height value */
  u32 crop_out_height;
};

/**
 * \brief Container for the metadata of the stream(Only used in VC1). \n
 * Contains a wide range of information about the stream, e.g. what kind of
 * tools are needed to decode the stream.
 * \ingroup common_group
 */
struct DecMetaData {
  u32     max_coded_width;  /**< \brief Specifies the maximum coded width in
                                  *  pixels of picture within the sequence.
                                  *  Valid range [2,8192] (even values).*/
  u32     max_coded_height; /**< \brief Specifies the maximum coded height in
                                  *  pixels of picture within the sequence.
                                  *  Valid range [2,8192] (even values).*/
  u32     vs_transform;    /**< \brief Indicates whether variable sized transform
                                  *  is enabled for the sequence. Valid range [0,1].*/
  u32     overlap;        /**< \brief Indicates whether overlap smoothing is
                                  *  enabled for the sequence. Valid range [0,1].*/
  u32     sync_marker;     /**< \brief Indicates whether there are syncronization markers in
                                  *  the stream. Valid range [0,1].*/
  u32     quantizer;      /**< \brief Indicates quantizer type used for the
                                  *  sequence. Valid range [0,3].*/
  u32     frame_interp;     /**< \brief Indicates whether the INTERPFRM flag (which
                                  *  provides information to display process)
                                  *  exists in the picture headers. Valid range [0,1].*/
  u32     max_bframes;     /**< \brief Specifies the maximum amount of consecutive
                                  *  B-frames within the sequence. Valid range [0,7].*/
  u32     fast_uv_mc;       /**< \brief Indicates whether the rounding of color
                                  *  difference motion vectors is enabled. Valid range [0,1].*/
  u32     extended_mv;     /**< \brief Indicates whether extended motion
                                  *  vectors are enabled for the sequence. Valid range [0,1].*/
  u32     multi_res;       /**< \brief Indicates whether frames may be coded
                                  *  at smaller resolutions than
                                  *  the specified frame resolution. Valid range [0,1].*/
  u32     range_red;       /**< \brief Indicates whether range reduction is used
                                  *  in the sequence. Valid range [0,1].*/
  u32     dquant;         /**< \brief Indicates whether the quantization step
                                  *  may vary within a frame. Valid range [0,2].*/
  u32     loop_filter;    /**< \brief Indicates whether loop filtering is
                                  *  enabled for the sequence. Valid range [0,1].*/
  u32     profile;        /**< \brief Specifies profile of the input video bitstream. */
};

/**
 * \brief Time info(Only used in AVS, MP2 and MP4).
 * \ingroup common_group
 */
struct DecTime {
  u32 hours; /**< \brief hours information */
  u32 minutes; /**< \brief minutes information */
  u32 seconds; /**< \brief seconds information */
  u32 pictures; /**< \brief pictures information */
  u32 time_incr; /**< \brief vop time increment : mpeg4 specific */
  u32 time_res; /**< \brief vop time increment resolution : mpeg4 specific */
};

#pragma pack(push, 1)
struct SEI_header {
  /* TODO(JZQ) : need fix, it has to be a compact struct */
  /** \brief The SEI type */
  u8 type;
  /** \brief The SEI data size */
  u16 size;
  /** \brief The SEI status */
  u8 status;
};
#pragma pack()

/**
 * \brief It stores captured SEI stream data.
 * \ingroup common_group
 */
struct SEI_buffer {
  u8 bitmask[32]; /**< \brief 256bit, Indicata which SEI is interested */
  u8 *buffer; /**< \brief SEI buffer pointer */
  u32 total_size; /**< \brief 32bit, the buffer size */
  u32 available_size; /**< \brief the available data size in SEI buffer */
};

/**
 * \brief The decoder input.
 * \ingroup common_group
 */
struct DecInput {
  struct DWLLinearMem buffer; /**< \brief Pointer to the input buffer. */
  u8* stream[2];              /**< \brief stream[0]: stream start before inputting.
                               *   stream[1]: stream end after inputting.   */
  u32 data_len;               /**< \brief Number of bytes to be decoded. */
  struct SEI_buffer *sei_buffer; /**< \brief SEI buffer */
  u32 pic_id; /**< \brief current pic_id for the input frame */
  enum DecRet dec_ret; /**< \brief the irq status for the input frame */
};

/**
 * \brief The decoder output.
 * \ingroup common_group
 */
struct DecOutput {
  u8* strm_curr_pos; /**< \brief Pointer to stream position where decoding ended */
  addr_t strm_curr_bus_address; /**< \brief The bus address location where the decoding ended */
  u32 data_left; /**< \brief How many bytes left undecoded */
  u8* strm_buff; /**< \brief Pointer to stream buffer start */
  addr_t strm_buff_bus_address; /**< \brief The bus address location where the stream buffer start */
  u32 buff_size; /**< \brief The stream buffer size */
  struct SEI_buffer *sei_buffer; /**< \brief SEI buffer */

  /* VP8 specific */
  u32 slice_height;     /**< \brief height of WebP slice, unused for other formats */
};

/**
 * \brief Pointer to the slice info(Only used in RV). \n
 * It contains offset value of each slice in the data buffer,
 * \ingroup common_group
 */
struct DecSliceInfo {
  /**< \brief The offset value of each slice in the data buffer,
   * including start point "0" and end point "data_len". */
  u32 offset;
  /**< \brief Indicates whether slice info is available */
  u32 is_valid;
};

/**
 * \brief Decoder input data
 * \ingroup common_group
 */
struct DecInputParameters {
  u32 pic_id; /**< \brief picture decoded id number */
  void* p_user_data; /**< \brief potint to user data */
  u8* stream; /**< \brief input stream virtual address */
  u32 strm_len; /**< \brief input stream length */
  addr_t stream_bus_address; /**< \brief input stream bus address */
  enum DecSkipFrameMode skip_frame; /**< \brief Skip some frames when decoding. */
  struct DWLLinearMem stream_buffer;  /**< \brief input stream buffer */
  struct SEI_buffer *sei_buffer; /**< \brief SEI buffer, HEVC and H264 apecific */

  /* low_latency mode used */
  u32 low_latency; /**< \brief Indicates whether low latency is available */
  u32 pic_decoded; /**< \brief flag : this pic has been decoded in low latency mode. */
  u32 exit_send_thread; /**< \brief flag : exit the data send thread. */
  u32 frame_len; /**< \brief The one frame data length in low latency mode. */

  /* MPEG4 specific */
  u32 enable_deblock;  /**< \brief Enable deblocking of post processed picture.
                        * NOTE: This parameter is not valid if the decoder
                        * is not used in pipeline mode with the post
                        * processor i.e. it has no effect on the
                        * decoding process */

  /* VP8 specific */
  u32 slice_height;     /**< \brief height of WebP slice, unused for other formats */
  u32 *p_pic_buffer_y;    /**< \brief luminance output address of user allocated buffer,
                             used in conjunction with external buffer allocation */
  addr_t pic_buffer_bus_address_y; /**< \brief The bus address for luminance output */
  u32 *p_pic_buffer_c;    /**< \brief chrominance output address of user allocated buffer,
                             used in conjunction with external buffer allocation */
  addr_t pic_buffer_bus_address_c; /**< \brief The bus address for luminance output */

  /* JPEG specific */
  u32 dec_image_type;   /**< \brief Full image or Thumbnail to be decoded */
  u32 slice_mb_set; /**< \brief slice mode: mcu rows to decode */
  u32 ri_count;     /**< \brief count of restart intervals in input stream */
  u32 *ri_array;    /**< \brief offsets of beginnings of restart intervals */
  u32 buffer_size; /**< \brief input stream buffer size in input stream buffering mode */
  struct DWLLinearMem picture_buffer_y;    /**< \brief luma output address ==> if user allocated */
  struct DWLLinearMem picture_buffer_cb_cr; /**< \brief chroma output address ==> if user allocated */
  struct DWLLinearMem picture_buffer_cr; /**< \brief chroma output address ==> if user allocated */

  /* RV specific */
  u32 timestamp;     /**< \brief timestamp of current picture from rv frame header.
                      * NOTE: timestamp of a B-frame should be adjusted referring
                      * to its forward reference frame's timestamp */
  u32 slice_info_num;    /**< \brief The number of slice offset entries. */
  struct DecSliceInfo *slice_info;     /**< \brief Pointer to the slice_info. */
};

/**
 * \brief Stream consumed callback prototype.
 * This callback is invoked by the decoder to notify the application that
 * a stream buffer was fully processed and can be reused.
 * \ingroup common_group
 * \param [in]     stream                    Base address of a buffer that was set as input when calling xxxDecDecode()
 * \param [in]     p_user_data               Application provided pointer to some private data.This is set at decoder initialization time.
 * \param [out]    void                      None
 */
typedef void DecMCStreamConsumed(void *stream, void *p_user_data);

/**
 * \brief Multicore decoder init configuration.
 * \ingroup common_group
 */
struct DecMCConfig {
  /**< \brief Indicates whether multicore is available */
  u32 mc_enable;
  /**< \brief Application provided callback for stream buffer processed */
  DecMCStreamConsumed *stream_consumed_callback;
};

/**
 * \brief Decoder initialization params, will be used in VCDecInit.
 * \ingroup common_group
 */
struct DecInitConfig {
  const void* dwl_inst;       /**< \brief struct DWL instance. */
  enum DecCodec codec; /**< \brief Specifies the decoder types. */
  u32 disable_picture_reordering; /**< \brief Output in decoding order. */
  enum DecErrorHandling error_handling; /**< \brief Error handling mode. */
  u32 error_ratio; /**< \brief Error ratio, used for DEC_EC_OUT_DECISION. */
  u32 use_video_compressor; /**< \brief Indicates whether RFC is available */
  u32 multi_frame_input_flag; /**< \brief Specifies the input stream of decoder contains at least two frames. */
  enum DecDecoderMode decoder_mode; /**< \brief Decoder working mode. */
  u32 guard_size; /**< \brief The minimum difference between minimum buffers number and allocated
                       buffers number that will force to return HDRS_RDY even buffers
                       number/size are sufficient for new sequence. */
  u32 use_adaptive_buffers; /**< \brief When sequence changes, if old output buffers (number/size)
                                 are sufficient for new sequence, old buffers will be used
                                 instead of reallocating output buffer. */
  u32 support_asofmo_stream; /**< \brief Indicates whether aso/fmo stream is supported */
  u32 num_frame_buffers; /**< \brief To use n frame buffers in decoder specified by user */
  u32 rlc_mode; /**< \brief Indicates whether rlc mode is available(H264/MPEG4 only) */
  u32 max_num_pics_to_decode; /**< \brief limits the decoding to N pictures. 0 for unlimited. */
  struct DecMCConfig mc_cfg; /**< \brief Multicore decoder init configuration. */
  enum DecSkipFrameMode skip_frame; /**< \brief Skip some frames when decoding. */
  u32 auxinfo; /**< \brief aux info enable */
  enum DecInputFormat dec_format; /**< \brief Format of the input sequence(vp8/mpeg4 only). */
  /* h264 specific */
  u32 mvc; /**< \brief Indicates whether mvc stream */
  /* rv specific */
  u32 frame_code_length; /**< \brief Frame code length */
  u32 *frame_sizes; /**< \brief Frame size */
  u32 rv_version; /**< \brief RV version : RV8 RV9 RV10 */
  u32 max_frame_width; /**< \brief Max frame width */
  u32 max_frame_height; /**< \brief Max frame heigth */
  /* vc1 specific */
  struct DecMetaData meta_data; /**< \brief The metadata of the stream(Only used in VC1) */
  /* av1 specific */
  u32 disable_late_hw_sync;
  u32 disable_clock_gating;
  u32 enable_dram_throttle;
  u32 annexb;
  u32 plainobu;
  u32 multicore_poll_period;
  u32 tile_transpose;
  u32 oppoints;
#ifdef ASIC_TRACE_SUPPORT
  u32 sim_mc;
#endif
};

/**
 * \brief Decoder setting params, will be used in VCDecSetInfo.
 * \ingroup common_group
 */
struct DecConfig {
  PpUnitConfig ppu_cfg[DEC_MAX_OUT_COUNT]; /**< \brief A structure containing PP unit configuration information. */
  DelogoConfig delogo_params[2]; /**< \brief delogo config parameters */
  DecPicAlignment align; /**< \brief Stride alignment: aligned to 1/8/16/.../512 bytes. */
  u32 hw_conceal; /**< \brief Use Hw error concealment(only hevc/h264/av1).*/
  u32 disable_slice; /**< \brief disable slice mode(only hevc/h264). */
  i8 max_temporal_layer; /**< \brief The maximum temporal layer that the VCD supports decoding(only hevc/h264/vvc). */
  /* jpeg specific */
  u32 dec_image_type; /**< \brief decode image type : JPEGDEC_IMAGE or JPEGDEC_THUMBNAIL */
  u32 chroma_format; /**< \brief decode chroma foramt : 420,422 etc */
  /* standalone pp specific */
  u32 in_format;  /**< \brief The format of input. */
  u32 in_stride; /**< \brief pic stride of the input. */
  u32 in_height; /**< \brief pixels height of the input. */
  u32 in_width;  /**< \brief pixels width of the input. */
  u32 in_lu_stride;  /**< \brief input stride of RFC Luma data. */
  u32 in_ch_stride;  /**< \brief input stride of RFC Chroma data. */
  u32 in_lut_stride;  /**< \brief input stride of RFC Luma table data. */
  u32 in_cht_stride;  /**< \brief input stride of RFC Chroma table data. */
  u32 in_luma_bitdepth;  /**< \brief input bitdepth of RFC Luma data. */
  u32 in_chroma_bitdepth;  /**< \brief input bitdepth of RFC Chroma data. */
  u8 in_rfc;  /**< \brief flag to indicate rfc input. */
  struct DWLLinearMem pp_in_buffer; /**< \brief The buffer malloced for pp input */
  struct DWLLinearMem pp_out_buffer; /**< \brief The buffer malloced for pp output */
};

/**
 * \brief Video sequence information.
 * \ingroup common_group
 */
struct DecSequenceInfo {
  u32 vp_version;       /**< \brief VP codec version defined in input stream */
  u32 vp_profile;       /**< \brief VP cocec profile defined in input stream */
  u32 pic_width;                    /**< \brief decoded picture width in pixels */
  u32 pic_height;                   /**< \brief decoded picture height in pixels */
  u32 scaled_width;     /**< \brief scaled width of the displayed video */
  u32 scaled_height;    /**< \brief scaled height of the displayed video */
  u32 pic_width_thumb;                   /**< \brief decoded picture width in pixels in Thumbnail */
  u32 pic_height_thumb;                  /**< \brief decoded picture height in pixels in Thumbnail */
  u32 scaled_width_thumb;     /**< \brief scaled width of the displayed video in Thumbnail */
  u32 scaled_height_thumb;    /**< \brief scaled height of the displayed video in Thumbnail */
  u32 sar_width;                    /**< \brief sample aspect ratio */
  u32 sar_height;                   /**< \brief sample aspect ratio */
  u32 dis_comformance_window;            /**< \brief  comformance window disabled*/
  struct DecCropParams crop_params; /**< \brief Cropping parameters for the picture */
  enum DecVideoRange video_range;   /**< \brief YUV sample video range */
  u32 matrix_coefficients; /**< \brief matrix coefficients RGB->YUV conversion */
  u32 is_mono_chrome;      /**< \brief is sequence monochrome */
  u32 is_interlaced;       /**< \brief is sequence interlaced */
  u32 num_of_ref_frames;   /**< \brief Maximum number of reference frames */
  u32 chroma_format_idc; /**< \brief 0 mono chrome; 1 yuv420; 2 yuv422*/
  u32 bit_depth_luma;    /**< \brief Bit depth of stored picture for luma */
  u32 bit_depth_chroma; /**< \brief Bit depth of stored picture for chroma */
  u32 out_bit_depth;  /**< \brief Bit depth of output picture(avs2 special) */
  enum DecDpbMode dpb_mode;             /**< \brief DPB mode : frame, or field interlaced */
  enum DecPictureFormat output_format; /**< \brief Format of the output picture */
  enum DecPictureFormat output_format_thumb; /**< \brief Format of the output picture in thumbnail */
  u32 coding_mode; /**< \brief JPEG code type :
                         * JPEG_BASELINE
                         * JPEG_PROGRESSIVE
                         * JPEG_NONINTERLEAVED
                         */
  u32 coding_mode_thumb;    /**< \brief JPEG code type in thumbnail :
                                 * JPEG_BASELINE
                                 * JPEG_PROGRESSIVE
                                 * JPEG_NONINTERLEAVED
                                 */
  u32 thumbnail_type;  /**< \brief Thumbnail exist or not or not supported */

  /* H264 specific */
  u32 pp_enabled; /**< \brief post process is available */
  u32 h264_base_mode;    /**< \brief baseline profile, only H264 */
  /* VC1 specific */
  u32 frame_rate_numerator;
  u32 frame_rate_denominator;
  u32 buf_release_flag;
  /* JPEG specific */
  struct DecInputParameters jpeg_input_info; /**< \brief Decoder input data(Only jpeg in here) */
  u32 img_max_dec_width; /**< \brief Maximum supported decoding width for jpeg */
  u32 img_max_dec_height; /**< \brief Maximum supported decoding height for jpeg */
  /* AVS specific */
  u32 profile_id; /**< \brief The profile id */
  u32 level_id; /**< \brief The level id */
  /* MPEG2 MPEG4 AVS specific */
  u32 profile_and_level_indication;
  u32 display_aspect_ratio;
  u32 stream_format;
  /* HDR */
  u32 video_format;
  u32 colour_primaries;
  u32 transfer_characteristics;
  u32 colour_description_present_flag;
  u32 trc_status; /**< \brief 0-both filled
                       * 1-only filled transfer_characteristics
                       * 2-only filled preferred_transfer_characteristics
                       */
  u32 preferred_transfer_characteristics;

  u32 multi_buff_pp_size;
  /* MPEG4 specific */
  u32 user_data_voslen; /**< \brief length of VOS data */
  u32 user_data_visolen; /**< \brief length of VIS0 data */
  u32 user_data_vollen; /**< \brief length of VOL data */
  u32 user_data_govlen; /**< \brief length of GOV data */
  u32 gmc_support;
  /* RV specific */
  u32 out_pic_coded_width; /**< \brief output picture width */
  u32 out_pic_coded_height; /**< \brief output picture height */
  u32 out_pic_stat;
  /* time scale info */
  u32 timing_info_present_flag;
  u32 num_units_in_tick;
  u32 time_scale;
  u32 thumbnail_done;
};

/**
 * \brief Picture specific information.
 * \ingroup common_group
 */
struct DecPictureInfo {
  enum DecPicCodingType pic_coding_type; /**< \brief Picture coding type */
  enum DecPicCodingType pic_coding_type_field; /**< \brief Picture coding type for bottom field */
  u32 is_corrupted;             /**< \brief Tells whether picture is corrupted */
  enum DecPictureFormat format; /**< \brief Color format of the picture */
  struct DecTime time_code; /**< \brief Time info(Only used in AVS, MP2 and MP4). */
  u32 cycles_per_mb;            /**< \brief Avarage decoding time in cycles per mb */
#ifdef FPGA_PERF_AND_BW
  u32 bitrate_4k60fps; /**< \brief The bitrate per picture (4k60fps)*/
  u32 bwrd_in_fs; /**< \brief The read bandwidth in luma frame size */
  u32 bwwr_in_fs; /**< \brief The write bandwidth in luma frame size */
#endif
  u32 pic_id;                   /**< \brief  Identifier for the picture to be decoded */
  u32 decode_id;               /**< \brief  Identifier for the picture to be decoded */
  i32 poc;
  u32 is_intra_frame;    /**< \brief  Indicates if Frame is an Intra Frame */
  u32 is_intra_frame_field;    /**< \brief  Indicates if Frame is an Intra Frame for bottom field */
  u32 is_golden_frame;   /**< \brief Indicates if Frame is a Golden reference Frame */
  u32 field_picture; /**< \brief Indicates if Frame is a field Frame */
  u32 top_field; /**< \brief Indicates if this is a top field */
  u32 first_field; /**< \brief Indicates if this is a first field */
  u32 repeat_first_field;
  u32 single_field;
  u32 output_other_field;
  u32 repeat_frame_count;
  u32 nbr_of_err_mbs;     /**< \brief Number of concealed macroblocks in the frame  */
  u32 num_slice_rows;    /**< \brief Number of luminance pixels rows in WebP output picture buffer.
                             If set to 0, whole picture ready.*/
  u32 last_slice;       /**< \brief last slice flag  */
  u32 luma_stride;      /**< \brief pixel row stride for luminance */
  u32 chroma_stride;    /**< \brief pixel row stride for chrominance */

  /* H264 specific */
  u32 view_id;          /**< \brief Identifies the view to which the output picture belongs */
};

/**
 * \brief Structure to carry information about decoded pictures.
 * \ingroup common_group
 */
struct DecPicture {
  struct DecSequenceInfo sequence_info; /**< \brief Sequence coding parameters used */
  struct DWLLinearMem luma;             /**< \brief Buffer properties */
  struct DWLLinearMem chroma;           /**< \brief Buffer properties : cb */
  struct DWLLinearMem chroma_cr;           /**< \brief Buffer properties : cr */
  struct DWLLinearMem dmv;           /**< \brief DMV Buffer properties */
  struct DWLLinearMem qp;           /**< \brief QP Buffer properties */
  struct DWLLinearMem luma_table;           /**< \brief Buffer properties for luma tile status address of dec or rfc */
  struct DWLLinearMem chroma_table;           /**< Buffer properties for chroma tile status address of dec or rfc*/
  struct DecPictureInfo picture_info;   /**< \brief Picture specific parameters */
  struct DecSEIParameters sei_param; /**< \brief SEI parameters of all formats */
  struct DWLLinearMem hdr;
  u32 pic_width; /**< \brief picture width */
  u32 pic_height; /**< \brief picture height */
  u32 pic_stride; /**< \brief picture stride for luma */
  u32 pic_stride_ch; /**< \brief picture stride for chroma */
  u32 chroma_format;
  u32 pp_enabled; /**< \brief post process is available */
  u32 is_gdr_frame; /**< \brief Indicates if picture is a GDR picture */

	/*if sequence_info.is_interlaced==1*/
  u32 top_field_first;                  /**< \brief 1-top field firs; 0-bottom field first */
  u32 fields_in_picture;                /**< \brief how many fields in picture:0-no field;1-one field;2-two fields */
};

/**
 * \brief Structure to carry information about decoded pictures for 'n' pp channal.
 * \ingroup common_group
 */
struct DecPictures {
  struct DecPicture pictures[DEC_MAX_OUT_COUNT];
};

/**
 * \brief A structure containing the reference buffer information.
 * \ingroup common_group
 */
struct DecBufferInfo {
  u32 next_buf_size; /**< \brief extra buffer size */
  u32 buf_num; /**< \brief extra buffer number */
  u32 add_extra_ext_buf; /**< \brief number of extra buffer has been added */
  struct DWLLinearMem buf_to_free; /**< \brief the initialized buffer */
#ifdef ASIC_TRACE_SUPPORT
  u32 is_frame_buffer; /**< \brief Indicates if the buffer is a frame buffer */
#endif
  u32 ystride[DEC_MAX_OUT_COUNT];
  u32 cstride[DEC_MAX_OUT_COUNT];
};

enum PfcTileMode{
  TILED_16X16_COMP = 1,
  TILED_32X8_COMP = 2
};

#define IS_EXTERNAL_BUFFER(config, type) (((config) >> (type)) & 1)

#endif /* DECTYPES_H */
