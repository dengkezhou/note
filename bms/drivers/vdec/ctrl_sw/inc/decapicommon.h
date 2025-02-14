/*--
          if (!ppu_cfg->monochrome && !mono_chrome)
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

#ifndef DECAPICOMMON_H
#define DECAPICOMMON_H

#include "basetype.h"

/**
 * \brief Maximum number of cores supported in multi-core configuration. For G2, multi-core currently not supported.
 * \ingroup common_group
*/
#define MAX_ASIC_CORES 4

/**
 * \addtogroup common_group
 *
 * @{
 */
#define MAX_REG_COUNT 768

#define HEVC_NOT_SUPPORTED (u32)(0x00)
#define HEVC_MAIN_PROFILE (u32)(0x01)
#define HEVC_MAIN10_PROFILE (u32)(0x02)
#define HEVC_SUPPORTED (u32)(0x01)
#define VP9_NOT_SUPPORTED (u32)(0x00)
#define VP9_PROFILE0 (u32)(0x01)
#define VP9_PROFILE2_10BITS (u32)(0x02)
#define MPEG4_NOT_SUPPORTED (u32)(0x00)
#define MPEG4_SIMPLE_PROFILE (u32)(0x01)
#define MPEG4_ADVANCED_SIMPLE_PROFILE (u32)(0x02)
#define MPEG4_CUSTOM_NOT_SUPPORTED (u32)(0x00)
#define MPEG4_CUSTOM_FEATURE_1 (u32)(0x01)
#define H264_NOT_SUPPORTED (u32)(0x00)
#define H264_BASELINE_PROFILE (u32)(0x01)
#define H264_MAIN_PROFILE (u32)(0x02)
#define H264_HIGH_PROFILE (u32)(0x03)
#define VC1_NOT_SUPPORTED (u32)(0x00)
#define VC1_SIMPLE_PROFILE        (u32)(0)
#define VC1_MAIN_PROFILE          (u32)(4)
#define VC1_ADVANCED_PROFILE      (u32)(12)
#define MPEG2_NOT_SUPPORTED (u32)(0x00)
#define MPEG2_MAIN_PROFILE (u32)(0x01)
#define JPEG_NOT_SUPPORTED (u32)(0x00)
#define JPEG_BASELINE (u32)(0x01)
#define JPEG_PROGRESSIVE (u32)(0x02)
#define JPEG_EXTENDED (u32)(0x03)
#define JPEG_NONINTERLEAVED (u32)(0x04)
#define PP_NOT_SUPPORTED (u32)(0x00)
#define PP_SUPPORTED (u32)(0x01)
#define PP_TILED_4X4 (u32)(0x20000000)
#define PP_DITHERING (u32)(0x10000000)
#define PP_SCALING (u32)(0x0C000000)
#define PP_DEINTERLACING (u32)(0x02000000)
#define PP_ALPHA_BLENDING (u32)(0x01000000)
#define PP_OUTP_ENDIAN (u32)(0x00040000)
#define PP_TILED_INPUT (u32)(0x0000C000)
#define PP_PIX_ACC_OUTPUT (u32)(0x40000000)
#define PP_ABLEND_CROP (u32)(0x80000000)
#define SORENSON_SPARK_NOT_SUPPORTED (u32)(0x00)
#define SORENSON_SPARK_SUPPORTED (u32)(0x01)
#define VP6_NOT_SUPPORTED (u32)(0x00)
#define VP6_SUPPORTED (u32)(0x01)
#define VP7_NOT_SUPPORTED (u32)(0x00)
#define VP7_SUPPORTED (u32)(0x01)
#define VP8_NOT_SUPPORTED (u32)(0x00)
#define VP8_SUPPORTED (u32)(0x01)
#define REF_BUF_INTERLACED (u32)(0x02)
#define REF_BUF_DOUBLE (u32)(0x04)
#define TILED_NOT_SUPPORTED (u32)(0x00)
#define TILED_8x4_SUPPORTED (u32)(0x01)
#define AVS_NOT_SUPPORTED (u32)(0x00)
#define AVS_SUPPORTED (u32)(0x01)
#define JPEG_EXT_NOT_SUPPORTED (u32)(0x00)
#define JPEG_EXT_SUPPORTED (u32)(0x01)
#define RV_NOT_SUPPORTED (u32)(0x00)
#define RV_SUPPORTED (u32)(0x01)
#define MVC_NOT_SUPPORTED (u32)(0x00)
#define MVC_SUPPORTED (u32)(0x01)
#define WEBP_NOT_SUPPORTED (u32)(0x00)
#define WEBP_SUPPORTED (u32)(0x01)
#define STRIDE_NOT_SUPPORTED (u32)(0x00)
#define STRIDE_SUPPORTED (u32)(0x01)
#define FIELD_DPB_NOT_SUPPORTED (u32)(0x00)
#define AVS_PLUS_NOT_SUPPORTED (u32)(0x00)
#define AVS_PLUS_SUPPORTED  (u32)(0x01)
#define ADDR64_ENV_NOT_SUPPORTED (u32)(0x00)
#define ADDR64_ENV_SUPPORTED (u32)(0x01)

#define H264_NOT_SUPPORTED_FUSE (u32)(0x00)
#define H264_FUSE_ENABLED (u32)(0x01)
#define MPEG4_NOT_SUPPORTED_FUSE (u32)(0x00)
#define MPEG4_FUSE_ENABLED (u32)(0x01)
#define MPEG2_NOT_SUPPORTED_FUSE (u32)(0x00)
#define MPEG2_FUSE_ENABLED (u32)(0x01)
#define SORENSON_SPARK_NOT_SUPPORTED_FUSE (u32)(0x00)
#define SORENSON_SPARK_ENABLED (u32)(0x01)
#define JPEG_NOT_SUPPORTED_FUSE (u32)(0x00)
#define JPEG_FUSE_ENABLED (u32)(0x01)
#define VP6_NOT_SUPPORTED_FUSE (u32)(0x00)
#define VP6_FUSE_ENABLED (u32)(0x01)
#define VP7_NOT_SUPPORTED_FUSE (u32)(0x00)
#define VP7_FUSE_ENABLED (u32)(0x01)
#define VP8_NOT_SUPPORTED_FUSE (u32)(0x00)
#define VP8_FUSE_ENABLED (u32)(0x01)
#define VC1_NOT_SUPPORTED_FUSE (u32)(0x00)
#define VC1_FUSE_ENABLED (u32)(0x01)
#define JPEG_PROGRESSIVE_NOT_SUPPORTED_FUSE (u32)(0x00)
#define JPEG_PROGRESSIVE_FUSE_ENABLED (u32)(0x01)
#define REF_BUF_NOT_SUPPORTED_FUSE (u32)(0x00)
#define REF_BUF_FUSE_ENABLED (u32)(0x01)
#define AVS_NOT_SUPPORTED_FUSE (u32)(0x00)
#define AVS_FUSE_ENABLED (u32)(0x01)
#define RV_NOT_SUPPORTED_FUSE (u32)(0x00)
#define RV_FUSE_ENABLED (u32)(0x01)
#define MVC_NOT_SUPPORTED_FUSE (u32)(0x00)
#define MVC_FUSE_ENABLED (u32)(0x01)

#define PP_NOT_SUPPORTED_FUSE (u32)(0x00)
#define PP_FUSE_ENABLED (u32)(0x01)
#define PP_FUSE_DEINTERLACING_ENABLED (u32)(0x40000000)
#define PP_FUSE_ALPHA_BLENDING_ENABLED (u32)(0x20000000)
#define MAX_PP_OUT_WIDHT_1920_FUSE_ENABLED (u32)(0x00008000)
#define MAX_PP_OUT_WIDHT_1280_FUSE_ENABLED (u32)(0x00004000)
#define MAX_PP_OUT_WIDHT_720_FUSE_ENABLED (u32)(0x00002000)
#define MAX_PP_OUT_WIDHT_352_FUSE_ENABLED (u32)(0x00001000)

#define BT601 0
#define BT601_L 1
#define BT709 2
#define BT709_L 3
#define BT2020 4
#define BT2020_L 5
#define IS_FULL_RANGE(fmt) \
        ((fmt == BT601) || (fmt == BT709) || (fmt == BT2020))

#define VSI_LINEAR 0
#define LANCZOS 1
#define NEAREST  2
#define BI_LINEAR 3
#define BICUBIC 4
#define SPLINE 5
#define BOX 6
#define FAST_LINEAR 7
#define FAST_BICUBIC 8

#define TILED4x4 0
#define TILED8x8 1
#define TILED16x16 2
#define TILED32x8 3
#define TILED128x2 4
#define TILED64x64 7

#define DOWN_ROUND 0
#define NO_ROUND   1
#define UP_ROUND   2

#define YUYV 0
#define UYVY 1

#define PP_YUV400 0
#define PP_YUV420 1
#define PP_YUV422 2
#define PP_YUV444 3

/**@}*/

/**
 * \brief Maximum output channels from xxxDecNexPicture().The maximum number of output channels supported is 6.
 * \ingroup common_group
 */
#define DEC_MAX_OUT_COUNT 6

#define PLANE_ALIGNMENT 1

#define PP_IN_NV12_8BIT 1
#define PP_IN_NV12_P010 10
#define PP_IN_TILED4x4  5
#define PP_IN_TILED4x4_P010 9
#define PP_IN_RGB888 20
#define PP_IN_BGR888 21
#define PP_IN_ARGB888 22 /* A8R8G8B8 */
#define PP_IN_ABGR888 23 /* A8B8G8R8 */
#define PP_IN_A2R10G10B10 24
#define PP_IN_A2B10G10R10 25
#define PP_IN_X2R10G10B10 26
#define PP_IN_X2B10G10R10 27
#define PP_IN_RFC         28
/* Picture dimensions are checked
   currently in vp9 and hevc api code */
#if !defined(MODEL_SIMULATION) || defined(HW_PIC_DIMENSIONS)
#define MIN_PIC_WIDTH 72
#define MIN_PIC_HEIGHT 72

#define MIN_PIC_WIDTH_VP9 72
#define MIN_PIC_HEIGHT_VP9 72

#define MIN_PIC_WIDTH_VVC 72
#define MIN_PIC_HEIGHT_VVC 72

/* DTRC minimum size = 96x8, So the minimum size for vp9 decoding
   should be redefined if DTRC is enabled */
#define MIN_PIC_WIDTH_VP9_EN_DTRC 96
#define MIN_PIC_HEIGHT_VP9_EN_DTRC 72

#else /* MODEL_SIMULATION */
#define MIN_PIC_WIDTH 8
#define MIN_PIC_HEIGHT 8

#define MIN_PIC_WIDTH_VP9 8
#define MIN_PIC_HEIGHT_VP9 8

#define MIN_PIC_WIDTH_VVC 8
#define MIN_PIC_HEIGHT_VVC 8

#define MIN_PIC_WIDTH_VP9_EN_DTRC 8
#define MIN_PIC_HEIGHT_VP9_EN_DTRC 8

#endif /* MODEL_SIMULATION */

/**
 * JPEG specific.
 * \ingroup jpeg_group
 */
enum {
  /** \brief No units, X and Y specify the pixel aspect ratio. */
  JPEGDEC_NO_UNITS = 0,
  /** \brief X and Y are dots per inch. */
  JPEGDEC_DOTS_PER_INCH = 1,
  /** \brief X and Y are dots per cm. */
  JPEGDEC_DOTS_PER_CM = 2
};

enum {
  JPEGDEC_THUMBNAIL_JPEG = 0x10,
  JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT = 0x11,
  JPEGDEC_NO_THUMBNAIL = 0x12
};

enum {
  JPEGDEC_IMAGE = 0,
  JPEGDEC_THUMBNAIL = 1
};

#ifdef OPEN_HWCFG_TO_CLIENT
#define MAX_CLIENT_TYPE 20
/**
 * \brief A structure to store hardware configuration.
 * \ingroup common_group
 */
struct DecHwConfig {
  u32 mpeg4_support;        /**< \brief one of the MPEG4 values defined above */
  u32 custom_mpeg4_support; /**< \brief one of the MPEG4 custom values defined above */
  u32 h264_support;         /**< \brief one of the H264 values defined above */
  u32 vc1_support;          /**< \brief one of the VC1 values defined above */
  u32 mpeg2_support;        /**< \brief one of the MPEG2 values defined above */
  u32 jpeg_support;         /**< \brief one of the JPEG values defined above */
  u32 max_dec_pic_width[MAX_CLIENT_TYPE];    /**< \brief maximum picture width in decoder */
  u32 max_dec_pic_height[MAX_CLIENT_TYPE];   /**< \brief maximum picture height in decoder */
  u32 pp_standalone;        /**< \brief PP_SUPPORTED or PP_NOT_SUPPORTED */
  u32 pp_config;            /**< \brief Bitwise list of PP function */
  u32 max_pp_out_pic_width;   /**< \brief maximum post-processor output picture width */
  u32 max_pp_out_pic_height;   /**< \brief maximum post-processor output picture height */
  u32 sorenson_spark_support; /**< \brief one of the SORENSON_SPARK values defined above */
  u32 vp6_support;           /**< \brief one of the VP6 values defined above */
  u32 vp7_support;           /**< \brief one of the VP7 values defined above */
  u32 vp8_support;           /**< \brief one of the VP8 values defined above */
  u32 vp9_support;           /**< \brief HW supports VP9 */
  u32 avs_support;           /**< \brief one of the AVS values defined above */
  u32 rv_support;            /**< \brief one of the HUKKA values defined above */
  u32 webp_support;          /**< \brief one of the WEBP values defined above */
  u32 stride_support;        /**< \brief HW supports separate Y and C strides */
  u32 avs_plus_support;      /**< \brief one of the AVS PLUS values defined above */
  u32 addr64_support;         /**< \brief HW supports 64bit addressing */
  u32 avs2_support;           /**< \brief HW supports AVS2 */
  u32 hevc_support;          /**< \brief HW supports HEVC */
  u32 av1_support;           /**< \brief HW supports AV1 */
  u32 vvc_support;           /**< \brief HW supports VVC */

  u32 hevc_main10_support;  /**< \brief HW supports HEVC Main10 profile*/
  u32 vp9_10bit_support;     /**< \briefHW supports VP9 10 bits profile */
  u32 ds_support;            /**< \brief HW supports down scaling. */
  u32 rfc_support;           /**< \brief HW supports reference frame compression. */
  u32 fmt_p010_support;      /**< \brief HW supports P010 format. */
};
#endif

/**
 * \brief Get API version.
 * \ingroup common_group
 */
struct DecApiVersion {
  u32 major;           /**< \brief API major version */
  u32 minor;           /**< \brief API minor version */
  u32 micro;           /**< \brief API micro version */
};

/**
 * \brief Sw and Hw Build information.
 * \ingroup common_group
 */
struct DecSwHwBuild {
  u32 sw_build;                 /**< \brief Software build ID */
  u32 asic_id;                  /**< \brief Hardware aisc ID */
  u32 hw_build_id[MAX_ASIC_CORES]; /**< \brief Hardware build ID */
#ifdef OPEN_HWCFG_TO_CLIENT
  struct DecHwConfig hw_config[MAX_ASIC_CORES]; /**< \brief Hardware configuration */
#endif
};


/**
 * DPB flags to control reference picture format etc.
 * \ingroup common_group
 */
enum DecDpbFlags {
  /** \brief Reference frame format is raster scan.[Not supported] */
  DEC_REF_FRM_RASTER_SCAN = 0x0,
  /** \brief Reference frame format is tiled (Default) */
  DEC_REF_FRM_TILED_DEFAULT = 0x1,
  /** \brief Flag to allow SW to use DPB field ordering on interlaced content.[Not supported] */
  DEC_DPB_ALLOW_FIELD_ORDERING = 0x40000000
};

#define DEC_REF_FRM_FMT_MASK 0x01
#define LOW_LATENCY_PACKET_SIZE 256

/**
 * Modes for storing content into DPB.
 * \ingroup common_group
 */
enum DecDpbMode {
  /** \brief DPB mode is frame. (default) */
  DEC_DPB_FRAME = 0,
  /** \brief DPB mode is interlaced field */
  DEC_DPB_INTERLACED_FIELD = 1
};

/**
 * Decoder working mode.
 * \ingroup common_group
 */
enum DecDecoderMode {
  /** \brief Normal decoding mode : Hardware should not be enabled until one frame
   * data is ready. The minimum hardware decode unit is one frame. */
  DEC_NORMAL =           0x00000000,
  /** \brief Low latency decoding mode : Hardware can be enabled first, then wait for
   * input stream data. The minimum hardware decode unit is 256 bytes. */
  DEC_LOW_LATENCY =      0x00000001,
  /** \brief Security playback mode. [Not supported] */
  DEC_SECURITY =         0x00000002,
  /** \brief Support to only decode key frame. */
  DEC_PARTIAL_DECODING = 0x00000004,
  /** \brief Intra only mode. */
  DEC_INTRA_ONLY =       0x00000008,
  /** \brief Dec heif format. */
  DEC_HEIF =             0x00000010
};


/**
 * Decoder auxiliary infomation.
 * \ingroup common_group
 */
enum DecAuxInfo {
  /** \brief No auxiliary infomation present. */
  DEC_AUX_NONE =          0x00000000,
  /** \brief  Enable QP info */
  DEC_AUX_QP =            0x00000001,
  /** \brief Enable MV info */
  DEC_AUX_MV =            0x00000002,
};


/**
 * Delogo filter mode.
 * \ingroup common_group
 */
enum DelogoMode {
  /** \brief do not use delogo filter */
  PIXEL_NO_DELOGO = 0,
  /** \brief replace mode */
  PIXEL_REPLACE = 1,
  /** \brief interpolation mode */
  PIXEL_INTERPOLATION = 2
};
/* DEPRECATED!!! do not use in new applications! */
#define DEC_DPB_DEFAULT DEC_DPB_FRAME

/**
 * Output picture format types.
 * packed      means all components in one planar
   planar      means each plane for each component
   semi-planar means CbCr shares same plane.
 * \ingroup common_group
 */
enum DecPictureFormat {
  DEC_OUT_FRM_TILED_4X4 = 0, /**< \brief Tiled 4x4 format */
  DEC_OUT_FRM_TILED_8X4 = 1,  /**< \brief obsoleted */
  DEC_OUT_FRM_RASTER_SCAN = 2, /**< \brief Raster scan format (semi-planar 4:2:0, 8 bit) */
  DEC_OUT_FRM_PLANAR_420 = 3,  /**< \brief Planar 4:2:0 format, 8 bit */
  DEC_OUT_FRM_TILED_8X8 = 4, /**< \brief Tiled 8x8 format */
  DEC_OUT_FRM_TILED_16X16 = 5, /**< \brief Tiled 16x16 format */
  DEC_OUT_FRM_TILED_16X16_P010 = 6, /**< \brief Tiled 16x16 P010 format, 10&12 bit */
  DEC_OUT_FRM_MONOCHROME,       /**< \brief YUV 4:0:0 */
  DEC_OUT_FRM_RFC, /**< \brief Reference frame compression */

  /* FBC */
  DEC_OUT_FRM_TILED_32X8_COMP,          /**< \brief compressed Tiled 16x16 format */
  DEC_OUT_FRM_TILED_32X8_P010_COMP,    /**< \brief compressed Tiled 16x16 P010 format, 10&12 bit */
  DEC_OUT_FRM_TILED_16X16_COMP,        /**< \brief compressed Tiled 16x16 format */
  DEC_OUT_FRM_TILED_16X16_P010_COMP,   /**< \brief compressed Tiled 16x16 P010 format, 10&12 bit */

  /* DEC400 */
  DEC_OUT_FRM_DEC400_400SP,   /**< \brief DEC400 output YUV400 semi-planar */
  DEC_OUT_FRM_DEC400_420SP,   /**< \brief DEC400 output YUV420 semi-planar */
  DEC_OUT_FRM_DEC400_400TILE, /**< \brief DEC400 output YUV400 tile4x4 */
  DEC_OUT_FRM_DEC400_420TILE, /**< \brief DEC400 output YUV420 tile4x4 */
  DEC_OUT_FRM_DEC400_400P,    /**< \brief DEC400 output YUV400 planar */
  DEC_OUT_FRM_DEC400_420P,    /**< \brief DEC400 output YUV420 planar */
  /* YUV420 */
  DEC_OUT_FRM_YUV420TILE,     /**< \brief YUV420, 8-bit, tile4x4 none rfc dpb output*/
  DEC_OUT_FRM_YUV420TILE_PACK10,   /**< \brief YUV420, 10-bit, tile4x4 none rfc dpb output*/
  DEC_OUT_FRM_YUV420TILE_PACK12,   /**< \brief YUV420, 12-bit, tile4x4 none rfc dpb output*/
  DEC_OUT_FRM_YUV420TILE8x8,     /**< \brief YUV420, 8-bit, tile8x8 none rfc dpb output*/
  DEC_OUT_FRM_YUV420TILE8x8_PACK10,   /**< \brief YUV420, 10-bit, tile8x8 none rfc dpb output*/
  DEC_OUT_FRM_YUV420TILE8x8_PACK12,   /**< \brief YUV420, 12-bit, tile8x8 none rfc dpb output*/
  DEC_OUT_FRM_YUV420TILE_P010, /**< \brief YUV420, 16-bit, valid 10 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV420TILE_I010, /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV420TILE_L010, /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in left */
  DEC_OUT_FRM_YUV420TILE_P012, /**< \brief YUV420, 16-bit, valid 12 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV420TILE_I012, /**< \brief YUV420, 16-bit, valid 12 bits stored in LSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV420TILE_128X2, /**< \brief YUV420, 8-bit, tile128x2 */
  DEC_OUT_FRM_YUV420TILE_128X2_P010, /**< \brief YUV420, 16-bit, tile128x2, valid 10 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV420SP,        /**< \brief YUV420, 8-bit, semi-planar */
  DEC_OUT_FRM_YUV420SP_PACK10, /**< \brief YUV420, 10-bit, semi-planar */
  DEC_OUT_FRM_YUV420SP_PACK12, /**< \brief YUV420, 12-bit, semi-planar [Not support] */
  DEC_OUT_FRM_YUV420SP_P010,   /**< \brief YUV420, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_YUV420SP_I010,   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_YUV420SP_L010,   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_OUT_FRM_YUV420SP_P012,   /**< \brief YUV420, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_YUV420SP_I012,   /**< \brief YUV420, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_YUV420SP_1010,   /**< \brief YUV420, 3 pixels in 4 bytes (LSB->MSB), semi-planar */
  DEC_OUT_FRM_YUV420P,        /**< \brief YUV420, 8-bit, planar */
  DEC_OUT_FRM_YUV420P_PACK10, /**< \brief YUV420, 10-bit, planar */
  DEC_OUT_FRM_YUV420P_PACK12, /**< \brief YUV420, 12-bit, planar */
  DEC_OUT_FRM_YUV420P_P010,   /**< \brief YUV420, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_YUV420P_I010,   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_OUT_FRM_YUV420P_L010,   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left */
  DEC_OUT_FRM_YUV420P_P012,   /**< \brief YUV420, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_YUV420P_I012,   /**< \brief YUV420, 16-bit, valid 12 bits stored in LSB, planar, padding 0 in right */
  DEC_OUT_FRM_YUV420P_1010,   /**<\brief YUV420, 3 pixels in 4 bytes (LSB->MSB), planar */
   /* YUV400 */
  DEC_OUT_FRM_YUV400TILE,      /**< \brief YUV400, 8-bit, tile4x4 none rfc dpb output */
  DEC_OUT_FRM_YUV400TILE_PACK10,/**< \brief YUV400, 10-bit, tile4x4 none rfc dpb output */
  DEC_OUT_FRM_YUV400TILE8x8,      /**< \brief YUV400, 8-bit, tile8x8 none rfc dpb output */
  DEC_OUT_FRM_YUV400TILE8x8_PACK10,/**< \brief YUV400, 10-bit, tile8x8 none rfc dpb output */
  DEC_OUT_FRM_YUV400TILE_P010, /**< \brief YUV400, 16-bit, valid 10 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV400TILE_I010, /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in right */
  DEC_OUT_FRM_YUV400TILE_L010, /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in left */
  DEC_OUT_FRM_YUV400TILE_P012, /**< \brief YUV400, 16-bit, valid 12 bits stored in MSB, tile4x4, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV400TILE_I012, /**< \brief YUV400, 16-bit, valid 12 bits stored in LSB, tile4x4, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV400,          /**< \brief YUV400, 8-bit */
  DEC_OUT_FRM_YUV400_PACK10,          /**< \brief YUV400, 10-bit */
  DEC_OUT_FRM_YUV400_PACK12,          /**< \brief YUV400, 12-bit [Not support] */
  DEC_OUT_FRM_YUV400_P010,     /**< \brief YUV400, 16-bit, valid 10 bits stored in MSB, padding 0 in right */
  DEC_OUT_FRM_YUV400_I010,     /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, padding 0 in right */
  DEC_OUT_FRM_YUV400_L010,     /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, padding 0 in left */
  DEC_OUT_FRM_YUV400_P012,     /**< \brief YUV400, 16-bit, valid 12 bits stored in MSB, padding 0 in right */
  DEC_OUT_FRM_YUV400_I012,     /**< \brief YUV400, 16-bit, valid 12 bits stored in LSB, padding 0 in right */
  DEC_OUT_FRM_YUV400TILE_128X2, /**< \brief YUV400, 8-bit, tile128x2 */
  DEC_OUT_FRM_YUV400TILE_128X2_P010, /**< \brief YUV400, 16-bit, tile128x2,  valid 10 bits stored in MSB, padding 0 in right */
  /* YUV422 */
  DEC_OUT_FRM_YUV422SP,        /**< \brief YUV422, 8-bit, semi-planar */
  DEC_OUT_FRM_YUV422SP_PACK10, /**< \brief YUV422, 10-bit, semi-planar */
  DEC_OUT_FRM_YUV422SP_PACK12, /**< \brief YUV422, 12-bit, semi-planar [Not support] */
  DEC_OUT_FRM_YUV422SP_P010,   /**< \brief YUV422, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_YUV422SP_I010,   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_YUV422SP_L010,   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_OUT_FRM_YUV422SP_P012,   /**< \brief YUV422, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV422SP_I012,   /**< \brief YUV422, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV422SP_1010,   /**< \brief YUV422, 3 pixels in 4 bytes (LSB->MSB), semi-planar */
  DEC_OUT_FRM_YUV422P,        /**< \brief YUV422, 8-bit, planar [Not support] */
  DEC_OUT_FRM_YUV422P_PACK10, /**< \brief YUV422, 10-bit, planar [Not support] */
  DEC_OUT_FRM_YUV422P_PACK12, /**< \brief YUV422, 12-bit, planar [Not support] */
  DEC_OUT_FRM_YUV422P_P010,   /**< \brief YUV422, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_YUV422P_I010,   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV422P_L010,   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left [Not support] */
  DEC_OUT_FRM_YUV422P_P012,   /**< \brief YUV422, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV422P_I012,   /**< \brief YUV422, 16-bit, valid 12 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV422_YUYV,    /**< \brief YUV422, 8-bit, YUYV */
  DEC_OUT_FRM_YUV422_UYVY,    /**< \brief YUV422, 8-bit, UYVY */
  /* YUV440 */
  DEC_OUT_FRM_YUV440,          /**< \brief YUV440, 8-bit [Not support] */
  /* YUV411 */
  DEC_OUT_FRM_YUV411SP,        /**< \brief YUV411, 8-bit, semi-planar [Not support] */
  /* YUV444 */
  DEC_OUT_FRM_YUV444SP,        /**< \brief YUV444, 8-bit, semi-planar [Not support] */
  DEC_OUT_FRM_YUV444SP_PACK10, /**< \brief YUV444, 10-bit, semi-planar [Not support] */
  DEC_OUT_FRM_YUV444SP_PACK12, /**< \brief YUV444, 12-bit, semi-planar [Not support] */
  DEC_OUT_FRM_YUV444SP_P010,   /**< \brief YUV444, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV444SP_I010,   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV444SP_L010,   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left [Not support] */
  DEC_OUT_FRM_YUV444SP_P012,   /**< \brief YUV444, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV444SP_I012,   /**< \brief YUV444, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV444SP_1010,   /**< \brief YUV444, 3 pixels in 4 bytes (LSB->MSB), semi-planar [Not support] */
  DEC_OUT_FRM_YUV444P,        /**< \brief YUV444, 8-bit, planar */
  DEC_OUT_FRM_YUV444P_PACK10, /**< \brief YUV444, 10-bit, planar [Not support] */
  DEC_OUT_FRM_YUV444P_PACK12, /**< \brief YUV444, 12-bit, planar [Not support] */
  DEC_OUT_FRM_YUV444P_P010,   /**< \brief YUV444, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_YUV444P_I010,   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV444P_L010,   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left [Not support] */
  DEC_OUT_FRM_YUV444P_P012,   /**< \brief YUV444, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_YUV444P_I012,   /**< \brief YUV444, 16-bit, valid 12 bits stored in LSB, planar, padding 0 in right [Not support] */
  /* NV21 */
  DEC_OUT_FRM_NV21TILE,        /**< \brief NV21, 8-bit, tile4x4 */
  DEC_OUT_FRM_NV21TILE_PACK10, /**< \brief NV21, 10-bit, tile4x4 */
  DEC_OUT_FRM_NV21TILE_P010, /**< \brief NV21, 16-bit, valid 10 bits stored in MSB, semi-planar, tile4x4, padding 0 in right */
  DEC_OUT_FRM_NV21TILE_I010, /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, tile4x4, padding 0 in right */
  DEC_OUT_FRM_NV21TILE_L010, /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, tile4x4, padding 0 in left */
  DEC_OUT_FRM_NV21TILE_P012, /**< \brief NV21, 16-bit, valid 12 bits stored in MSB, semi-planar, tile4x4, padding 0 in right */
  DEC_OUT_FRM_NV21TILE_I012, /**< \brief NV21, 16-bit, valid 12 bits stored in LSB, semi-planar, tile4x4, padding 0 in right */
  DEC_OUT_FRM_NV21SP,        /**< \brief NV21, 8-bit, semi-planar */
  DEC_OUT_FRM_NV21SP_PACK10, /**< \brief NV21, 10-bit, semi-planar */
  DEC_OUT_FRM_NV21SP_PACK12, /**< \brief NV21, 12-bit, semi-planar */
  DEC_OUT_FRM_NV21SP_P010,   /**< \brief NV21, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_NV21SP_I010,   /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_NV21SP_L010,   /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_OUT_FRM_NV21SP_P012,   /**< \brief NV21, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_NV21SP_I012,   /**< \brief NV21, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_NV21SP_1010,   /**< \brief NV21, semi-planar, 3 pixels in 4 bytes */
  DEC_OUT_FRM_NV21P,         /**< \brief NV21, 8-bit, planar */
  DEC_OUT_FRM_NV21P_PACK10,  /**< \brief NV21, 10-bit, planar */
  DEC_OUT_FRM_NV21P_PACK12,  /**< \brief NV21, 12-bit, planar [Not support] */
  DEC_OUT_FRM_NV21P_P010,    /**< \brief NV21, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_NV21P_I010,    /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_OUT_FRM_NV21P_L010,    /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left */
  DEC_OUT_FRM_NV21P_P012,    /**< \brief NV21, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_NV21P_I012,    /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_OUT_FRM_NV21P_1010,    /**< \brief NV21, planar, 3 pixels in 4 bytes */
  /* 422 NV21 */
  DEC_OUT_FRM_422_NV21SP,        /**< \brief NV21, 422, 8-bit, semi-planar */
  DEC_OUT_FRM_422_NV21SP_PACK10, /**< \brief NV21, 422, 10-bit, semi-planar */
  DEC_OUT_FRM_422_NV21SP_PACK12, /**< \brief NV21, 422, 12-bit, semi-planar */
  DEC_OUT_FRM_422_NV21SP_P010,   /**< \brief NV21, 422, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_422_NV21SP_I010,   /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_422_NV21SP_L010,   /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_OUT_FRM_422_NV21SP_P012,   /**< \brief NV21, 422, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_422_NV21SP_I012,   /**< \brief NV21, 422, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_422_NV21SP_1010,   /**< \brief NV21, 422, semi-planar, 3 pixels in 4 bytes */
  DEC_OUT_FRM_422_NV21P,         /**< \brief NV21, 422, 8-bit, planar */
  DEC_OUT_FRM_422_NV21P_PACK10,  /**< \brief NV21, 422, 10-bit, planar */
  DEC_OUT_FRM_422_NV21P_PACK12,  /**< \brief NV21, 422, 12-bit, planar [Not support] */
  DEC_OUT_FRM_422_NV21P_P010,    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_422_NV21P_I010,    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_422_NV21P_L010,    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left [Not support] */
  DEC_OUT_FRM_422_NV21P_P012,    /**< \brief NV21, 422, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_422_NV21P_I012,    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  /* 444 NV21 */
  DEC_OUT_FRM_444_NV21SP,        /**< \brief NV21, 444, 8-bit, semi-planar */
  DEC_OUT_FRM_444_NV21SP_PACK10, /**< \brief NV21, 444, 10-bit, semi-planar */
  DEC_OUT_FRM_444_NV21SP_PACK12, /**< \brief NV21, 444, 12-bit, semi-planar [Not support] */
  DEC_OUT_FRM_444_NV21SP_P010,   /**< \brief NV21, 444, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_OUT_FRM_444_NV21SP_I010,   /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_444_NV21SP_L010,   /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left [Not support] */
  DEC_OUT_FRM_444_NV21SP_P012,   /**< \brief NV21, 444, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_444_NV21SP_I012,   /**< \brief NV21, 444, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_OUT_FRM_444_NV21P,         /**< \brief NV21, 444, 8-bit, planar */
  DEC_OUT_FRM_444_NV21P_PACK10,  /**< \brief NV21, 444, 10-bit, planar */
  DEC_OUT_FRM_444_NV21P_PACK12,  /**< \brief NV21, 444, 12-bit, planar */
  DEC_OUT_FRM_444_NV21P_P010,    /**< \brief NV21, 444, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_444_NV21P_I010,    /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_OUT_FRM_444_NV21P_L010,    /**<\brief NV21, 444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left */
  DEC_OUT_FRM_444_NV21P_P012,    /**< \brief NV21, 444, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right */
  DEC_OUT_FRM_444_NV21P_I012,    /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  /* RGB */
  /* sw_ppx_out_rgb_fmt == 0 */
  DEC_OUT_FRM_RGB888_P, /**< \brief RGB (First R, then G, and then B in buffer), 8-bit each component, planar */
  DEC_OUT_FRM_BGR888, /**< \brief BGR (B in MSB, R in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 1 */
  DEC_OUT_FRM_BGR888_P,  /**< \brief BGR (First B, then G, and then R in buffer), 8-bit each component, planar */
  DEC_OUT_FRM_RGB888, /**< \brief RGB (R in MSB, B in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 2 */
  DEC_OUT_FRM_R16G16B16_P, /**< \brief RGB (First R, then G, and then B in buffer), 16-bit each component, planar */
  DEC_OUT_FRM_B16G16R16, /** \brief BGR (B in MSB, R in LSB), 16-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 3 */
  DEC_OUT_FRM_B16G16R16_P, /**< \brief BGR (First B, then G, and then R in buffer), 16-bit each component, planar */
  DEC_OUT_FRM_R16G16B16, /**< \brief RGB (R in MSB, B in LSB), 16-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 4 */
  DEC_OUT_FRM_ABGR888, /**< \brief ABGR (A in MSB, R in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 5 */
  DEC_OUT_FRM_ARGB888, /**< \brief ARGB (A in MSB, B in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 6 */
  DEC_OUT_FRM_A2B10G10R10, /**< \brief ABGR (A in MSB, R in LSB), packed */
  /* sw_ppx_out_rgb_fmt == 7 */
  DEC_OUT_FRM_A2R10G10B10, /**< \brief ARGB (A in MSB, B in LSB), packed */
  /* sw_ppx_out_rgb_fmt == 8 */
  DEC_OUT_FRM_XBGR888,  /**< \brief XBGR (X in MSB, R in LSB), X means undetermined, packed */
  /* sw_ppx_out_rgb_fmt == 9 */
  DEC_OUT_FRM_XRGB888, /**< \brief XRGB (X in MSB, B in LSB), X means undetermined, packed */
  DEC_OUT_FRM_BGRA888, /**< \brief ABGR (B in MSB, A in LSB), 8-bit each component, packed */
  DEC_OUT_FRM_RGBA888, /**< \brief ARGB (R in MSB, A in LSB), 8-bit each component, packed */
  DEC_OUT_FRM_B10G10R10A2, /**< \brief BGRA (B in MSB, A in LSB), packed */
  DEC_OUT_FRM_R10G10B10A2, /**< \brief RGBA (R in MSB, A in LSB), packed */
  /* super_tile */
  DEC_OUT_FRM_ABGR888_TILED64X64, /**< \brief ABGR stored in Tiled 64x64 format */
  DEC_OUT_FRM_ARGB888_TILED64X64, /**< \brief ARGB stored in Tiled 64x64 format */
  DEC_OUT_FRM_A2B10G10R10_TILED64X64, /**< \brief A2B10G10R10 stored in Tiled 64x64 format */
  DEC_OUT_FRM_A2R10G10B10_TILED64X64, /**< \brief A2R10G10B10 stored in Tiled 64x64 format */
  DEC_OUT_FRM_XBGR888_TILED64X64, /**< \brief XBGR stored in Tiled 64x64 format */
  DEC_OUT_FRM_XRGB888_TILED64X64, /**< \brief XRGB stored in Tiled 64x64 format */

  /* Note: Please update the function of ParseDecPictureFormat in parselogmsg.c synchornously if changing this enum */
};

#define IS_RGB_4PLANE(fmt) (\
        DEC_OUT_FRM_ABGR888 ||\
        DEC_OUT_FRM_ARGB888 ||\
        DEC_OUT_FRM_A2B10G10R10 ||\
        DEC_OUT_FRM_A2R10G10B10 ||\
        DEC_OUT_FRM_XBGR888 ||\
        DEC_OUT_FRM_XRGB888 ||\
        DEC_OUT_FRM_BGRA888 ||\
        DEC_OUT_FRM_RGBA888 ||\
        DEC_OUT_FRM_B10G10R10A2 ||\
        DEC_OUT_FRM_R10G10B10A2 ||\
        DEC_OUT_FRM_ABGR888_TILED64X64 ||\
        DEC_OUT_FRM_ARGB888_TILED64X64 ||\
        DEC_OUT_FRM_A2B10G10R10_TILED64X64 ||\
        DEC_OUT_FRM_A2R10G10B10_TILED64X64 ||\
        DEC_OUT_FRM_XBGR888_TILED64X64 ||\
        DEC_OUT_FRM_XRGB888_TILED64X64\
        )

/**
 * \addtogroup common_group
 *
 * @{
 */
#define IS_PIC_PACKED_RGB(fmt) (\
  (fmt) == DEC_OUT_FRM_RGB888 || \
  (fmt) == DEC_OUT_FRM_BGR888 || \
  (fmt) == DEC_OUT_FRM_R16G16B16 || \
  (fmt) == DEC_OUT_FRM_B16G16R16 || \
  (fmt) == DEC_OUT_FRM_ARGB888 || \
  (fmt) == DEC_OUT_FRM_ABGR888 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10 || \
  (fmt) == DEC_OUT_FRM_XRGB888 || \
  (fmt) == DEC_OUT_FRM_XBGR888 || \
  (fmt) == DEC_OUT_FRM_R10G10B10A2 || \
  (fmt) == DEC_OUT_FRM_B10G10R10A2 || \
  (fmt) == DEC_OUT_FRM_RGBA888 || \
  (fmt) == DEC_OUT_FRM_BGRA888 || \
  (fmt) == DEC_OUT_FRM_ABGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_ARGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XBGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XRGB888_TILED64X64)

#define IS_PIC_PLANAR_RGB(fmt) ((fmt) == DEC_OUT_FRM_RGB888_P || \
  (fmt) == DEC_OUT_FRM_BGR888_P || \
  (fmt) == DEC_OUT_FRM_R16G16B16_P || \
  (fmt) == DEC_OUT_FRM_B16G16R16_P)

#define IS_PIC_RGB(fmt) (\
  (fmt) == DEC_OUT_FRM_RGB888 || \
  (fmt) == DEC_OUT_FRM_BGR888 || \
  (fmt) == DEC_OUT_FRM_R16G16B16 || \
  (fmt) == DEC_OUT_FRM_B16G16R16 || \
  (fmt) == DEC_OUT_FRM_ARGB888 || \
  (fmt) == DEC_OUT_FRM_ABGR888 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10 || \
  (fmt) == DEC_OUT_FRM_XRGB888 || \
  (fmt) == DEC_OUT_FRM_RGB888_P || \
  (fmt) == DEC_OUT_FRM_BGR888_P || \
  (fmt) == DEC_OUT_FRM_R16G16B16_P || \
  (fmt) == DEC_OUT_FRM_B16G16R16_P || \
  (fmt) == DEC_OUT_FRM_XBGR888 || \
  (fmt) == DEC_OUT_FRM_RGBA888 || \
  (fmt) == DEC_OUT_FRM_BGRA888 || \
  (fmt) == DEC_OUT_FRM_R10G10B10A2 || \
  (fmt) == DEC_OUT_FRM_B10G10R10A2 || \
  (fmt) == DEC_OUT_FRM_ABGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_ARGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XBGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XRGB888_TILED64X64)

#define IS_PIC_ALPHA_FORMAT(fmt) (\
  (fmt) == DEC_OUT_FRM_ARGB888 || \
  (fmt) == DEC_OUT_FRM_ABGR888 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10 || \
  (fmt) == DEC_OUT_FRM_RGBA888 || \
  (fmt) == DEC_OUT_FRM_BGRA888 || \
  (fmt) == DEC_OUT_FRM_R10G10B10A2 || \
  (fmt) == DEC_OUT_FRM_B10G10R10A2 || \
  (fmt) == DEC_OUT_FRM_ABGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_ARGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10_TILED64X64)

#define IS_PIC_XRGB_FORMAT(fmt) (\
  (fmt) == DEC_OUT_FRM_XRGB888 || \
  (fmt) == DEC_OUT_FRM_XBGR888 || \
  (fmt) == DEC_OUT_FRM_XBGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XRGB888_TILED64X64)

#define IS_PIC_MONOCHROME(fmt) (\
  (fmt) == DEC_OUT_FRM_MONOCHROME || \
  (fmt) == DEC_OUT_FRM_YUV400TILE || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I012 || \
  (fmt) == DEC_OUT_FRM_YUV400 || \
  (fmt) == DEC_OUT_FRM_YUV400_P010 || \
  (fmt) == DEC_OUT_FRM_YUV400_I010 || \
  (fmt) == DEC_OUT_FRM_YUV400_L010 || \
  (fmt) == DEC_OUT_FRM_YUV400_P012 || \
  (fmt) == DEC_OUT_FRM_YUV400_I012 || \
  (fmt) == DEC_OUT_FRM_YUV400_PACK10 || \
  (fmt) == DEC_OUT_FRM_DEC400_400SP || \
  (fmt) == DEC_OUT_FRM_DEC400_400P || \
  (fmt) == DEC_OUT_FRM_DEC400_400TILE || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_128X2 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_128X2_P010)

#define IS_PIC_YCbCr420(fmt) ( \
  ((fmt) >= DEC_OUT_FRM_NV21SP && \
   (fmt) <= DEC_OUT_FRM_NV21P_1010) || \
  ((fmt) >= DEC_OUT_FRM_YUV420SP && \
   (fmt) <= DEC_OUT_FRM_YUV420P_1010))

#define IS_PIC_YCbCr422(fmt) ( \
  ((fmt) >= DEC_OUT_FRM_YUV422SP && \
   (fmt) <= DEC_OUT_FRM_YUV422_UYVY) || \
   ((fmt) >= DEC_OUT_FRM_422_NV21SP && \
   (fmt) <= DEC_OUT_FRM_422_NV21P_I012))

#define IS_PIC_YCbCr444(fmt) ( \
  ((fmt) >= DEC_OUT_FRM_YUV444SP && \
   (fmt) <= DEC_OUT_FRM_YUV444P_I012) || \
   ((fmt) >= DEC_OUT_FRM_444_NV21SP && \
   (fmt) <= DEC_OUT_FRM_444_NV21P_I012))

#define IS_PIC_PLANAR(fmt) (\
  (fmt) == DEC_OUT_FRM_PLANAR_420 || \
  (fmt) == DEC_OUT_FRM_YUV420P || \
  (fmt) == DEC_OUT_FRM_YUV420P_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV422P_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV420P_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420P_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420P_L010 || \
  (fmt) == DEC_OUT_FRM_YUV420P_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420P_I012 || \
  (fmt) == DEC_OUT_FRM_YUV420P_1010 || \
  (fmt) == DEC_OUT_FRM_NV21P || \
  (fmt) == DEC_OUT_FRM_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21P_PACK12 || \
  (fmt) == DEC_OUT_FRM_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_NV21P_L010 || \
  (fmt) == DEC_OUT_FRM_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_NV21P_1010 || \
  (fmt) == DEC_OUT_FRM_YUV422P || \
  (fmt) == DEC_OUT_FRM_YUV422P_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV422P_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV422P_P010 || \
  (fmt) == DEC_OUT_FRM_YUV422P_I010 || \
  (fmt) == DEC_OUT_FRM_YUV422P_L010 || \
  (fmt) == DEC_OUT_FRM_YUV422P_P012 || \
  (fmt) == DEC_OUT_FRM_YUV422P_I012 || \
  (fmt) == DEC_OUT_FRM_422_NV21P || \
  (fmt) == DEC_OUT_FRM_422_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_PACK12 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_L010 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_YUV444P || \
  (fmt) == DEC_OUT_FRM_YUV444P_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV444P_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV444P_P010 || \
  (fmt) == DEC_OUT_FRM_YUV444P_I010 || \
  (fmt) == DEC_OUT_FRM_YUV444P_L010 || \
  (fmt) == DEC_OUT_FRM_YUV444P_P012 || \
  (fmt) == DEC_OUT_FRM_YUV444P_I012 || \
  (fmt) == DEC_OUT_FRM_444_NV21P || \
  (fmt) == DEC_OUT_FRM_444_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_PACK12 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_L010 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_DEC400_400P || \
  (fmt) == DEC_OUT_FRM_DEC400_420P || \
  IS_PIC_PLANAR_RGB(fmt))
#define IS_PIC_FIELD_PLANAR(fmt) ((fmt) == DEC_OUT_FRM_PLANAR_420 || \
    (fmt) == DEC_OUT_FRM_YUV420P || \
    (fmt) == DEC_OUT_FRM_YUV420P_P010 || \
    (fmt) == DEC_OUT_FRM_YUV420P_I010 )

#define IS_PIC_1010(fmt) ( \
   (fmt) == DEC_OUT_FRM_NV21P_1010 || \
   (fmt) == DEC_OUT_FRM_NV21SP_1010 || \
   (fmt) == DEC_OUT_FRM_YUV420P_1010 || \
   (fmt) == DEC_OUT_FRM_YUV420SP_1010 || \
   (fmt) == DEC_OUT_FRM_YUV422SP_1010 || \
   (fmt) == DEC_OUT_FRM_422_NV21SP_1010)

#define IS_PIC_NV21(fmt) (\
  (fmt) == DEC_OUT_FRM_NV21TILE || \
  (fmt) == DEC_OUT_FRM_NV21TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_L010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I012 || \
  (fmt) == DEC_OUT_FRM_NV21SP || \
  (fmt) == DEC_OUT_FRM_NV21SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21SP_P010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_I010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_L010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_P012 || \
  (fmt) == DEC_OUT_FRM_NV21SP_I012 || \
  (fmt) == DEC_OUT_FRM_NV21P || \
  (fmt) == DEC_OUT_FRM_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_NV21P_L010 )

#define IS_PIC_SEMIPLANAR(fmt) (\
  (fmt) == DEC_OUT_FRM_YUV420SP || \
  (fmt) == DEC_OUT_FRM_YUV420SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_L010 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_I012 || \
  (fmt) == DEC_OUT_FRM_NV21SP || \
  (fmt) == DEC_OUT_FRM_NV21SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21SP_P010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_I010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_L010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_P012 || \
  (fmt) == DEC_OUT_FRM_NV21SP_I012 || \
  (fmt) == DEC_OUT_FRM_RASTER_SCAN)

#define IS_PIC_8BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_YUV420TILE || \
  (fmt) == DEC_OUT_FRM_YUV420SP || \
  (fmt) == DEC_OUT_FRM_YUV420P || \
  (fmt) == DEC_OUT_FRM_YUV422SP || \
  (fmt) == DEC_OUT_FRM_YUV422P || \
  (fmt) == DEC_OUT_FRM_YUV444SP || \
  (fmt) == DEC_OUT_FRM_YUV444P || \
  (fmt) == DEC_OUT_FRM_YUV400TILE || \
  (fmt) == DEC_OUT_FRM_YUV400 || \
  (fmt) == DEC_OUT_FRM_NV21TILE || \
  (fmt) == DEC_OUT_FRM_NV21SP || \
  (fmt) == DEC_OUT_FRM_NV21P || \
  (fmt) == DEC_OUT_FRM_422_NV21SP || \
  (fmt) == DEC_OUT_FRM_422_NV21P || \
  (fmt) == DEC_OUT_FRM_444_NV21SP || \
  (fmt) == DEC_OUT_FRM_444_NV21P || \
  (fmt) == DEC_OUT_FRM_RGB888_P || \
  (fmt) == DEC_OUT_FRM_BGR888_P || \
  (fmt) == DEC_OUT_FRM_RGB888 || \
  (fmt) == DEC_OUT_FRM_BGR888 || \
  (fmt) == DEC_OUT_FRM_ARGB888 || \
  (fmt) == DEC_OUT_FRM_ABGR888 || \
  (fmt) == DEC_OUT_FRM_XRGB888 || \
  (fmt) == DEC_OUT_FRM_XBGR888 || \
  (fmt) == DEC_OUT_FRM_RGBA888 || \
  (fmt) == DEC_OUT_FRM_BGRA888 || \
  (fmt) == DEC_OUT_FRM_ABGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_ARGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XBGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XRGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_TILED_16X16 || \
  (fmt) == DEC_OUT_FRM_TILED_16X16_COMP || \
  (fmt) == DEC_OUT_FRM_TILED_32X8_COMP || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_128X2 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE8x8 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE8x8 || \
  (fmt) == DEC_OUT_FRM_YUV422_YUYV || \
  (fmt) == DEC_OUT_FRM_YUV422_UYVY)

#define IS_PIC_10BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_YUV420SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV420P_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV422SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV422P_PACK10 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV444SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV444P_PACK10 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_PACK10 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV400_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE8x8_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE8x8_PACK10)

#define IS_PIC_12BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_YUV420SP_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV400_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV420P_PACK12 || \
  (fmt) == DEC_OUT_FRM_NV21SP_PACK12 || \
  (fmt) == DEC_OUT_FRM_NV21P_PACK12  || \
  (fmt) == DEC_OUT_FRM_YUV422SP_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV422P_PACK12 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_PACK12 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_PACK12  || \
  (fmt) == DEC_OUT_FRM_YUV444SP_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV444P_PACK12 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_PACK12 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE8x8_PACK12)

#define IS_PIC_16BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_YUV420TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420P_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420P_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420P_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_I012 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_I012 || \
  (fmt) == DEC_OUT_FRM_YUV420P_I012 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV420SP_L010 || \
  (fmt) == DEC_OUT_FRM_YUV420P_L010 || \
  (fmt) == DEC_OUT_FRM_YUV422SP_P010 || \
  (fmt) == DEC_OUT_FRM_YUV422P_P010 || \
  (fmt) == DEC_OUT_FRM_YUV422SP_P012 || \
  (fmt) == DEC_OUT_FRM_YUV422P_P012 || \
  (fmt) == DEC_OUT_FRM_YUV422SP_I010 || \
  (fmt) == DEC_OUT_FRM_YUV422P_I010 || \
  (fmt) == DEC_OUT_FRM_YUV422SP_I012 || \
  (fmt) == DEC_OUT_FRM_YUV422P_I012 || \
  (fmt) == DEC_OUT_FRM_YUV422SP_L010 || \
  (fmt) == DEC_OUT_FRM_YUV422P_L010 || \
  (fmt) == DEC_OUT_FRM_YUV444SP_P010 || \
  (fmt) == DEC_OUT_FRM_YUV444P_P010 || \
  (fmt) == DEC_OUT_FRM_YUV444SP_P012 || \
  (fmt) == DEC_OUT_FRM_YUV444P_P012 || \
  (fmt) == DEC_OUT_FRM_YUV444SP_I010 || \
  (fmt) == DEC_OUT_FRM_YUV444P_I010 || \
  (fmt) == DEC_OUT_FRM_YUV444SP_I012 || \
  (fmt) == DEC_OUT_FRM_YUV444P_I012 || \
  (fmt) == DEC_OUT_FRM_YUV444SP_L010 || \
  (fmt) == DEC_OUT_FRM_YUV444P_L010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV400_P010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV400_P012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV400_I010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I012 || \
  (fmt) == DEC_OUT_FRM_YUV400_I012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV400_L010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_P010 || \
  (fmt) == DEC_OUT_FRM_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P012 || \
  (fmt) == DEC_OUT_FRM_NV21SP_P012 || \
  (fmt) == DEC_OUT_FRM_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_I010 || \
  (fmt) == DEC_OUT_FRM_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_I012 || \
  (fmt) == DEC_OUT_FRM_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_L010 || \
  (fmt) == DEC_OUT_FRM_NV21SP_L010 || \
  (fmt) == DEC_OUT_FRM_NV21P_L010 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_P010 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_P012 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_I010 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_I012 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_422_NV21SP_L010 || \
  (fmt) == DEC_OUT_FRM_422_NV21P_L010 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_P010 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_P010 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_P012 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_P012 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_I010 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_I010 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_I012 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_I012 || \
  (fmt) == DEC_OUT_FRM_444_NV21SP_L010 || \
  (fmt) == DEC_OUT_FRM_444_NV21P_L010 || \
  (fmt) == DEC_OUT_FRM_R16G16B16_P || \
  (fmt) == DEC_OUT_FRM_B16G16R16_P || \
  (fmt) == DEC_OUT_FRM_R16G16B16 || \
  (fmt) == DEC_OUT_FRM_B16G16R16 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_128X2_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_128X2_P010)

#define IS_PIC_24BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_RGB888 || \
  (fmt) == DEC_OUT_FRM_BGR888)

#define IS_PIC_32BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_ARGB888 || \
  (fmt) == DEC_OUT_FRM_ABGR888 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10 || \
  (fmt) == DEC_OUT_FRM_XRGB888 || \
  (fmt) == DEC_OUT_FRM_XBGR888 || \
  (fmt) == DEC_OUT_FRM_RGBA888 || \
  (fmt) == DEC_OUT_FRM_BGRA888 || \
  (fmt) == DEC_OUT_FRM_R10G10B10A2 || \
  (fmt) == DEC_OUT_FRM_B10G10R10A2 || \
  (fmt) == DEC_OUT_FRM_ABGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_ARGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XBGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XRGB888_TILED64X64)

#define IS_PIC_48BIT(fmt) (\
  (fmt) == DEC_OUT_FRM_R16G16B16 || \
  (fmt) == DEC_OUT_FRM_B16G16R16)

#define IS_PIC_TILE(fmt) (\
  (fmt) == DEC_OUT_FRM_TILED_4X4 || \
  (fmt) == DEC_OUT_FRM_TILED_8X4 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_I012 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21TILE || \
  (fmt) == DEC_OUT_FRM_NV21TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_L010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I012 || \
  (fmt) == DEC_OUT_FRM_DEC400_400TILE || \
  (fmt) == DEC_OUT_FRM_DEC400_420TILE)

#define IS_PIC_RFC(fmt) ((fmt) == DEC_OUT_FRM_RFC)

#define IS_PIC_DEC400(fmt) (\
  (fmt) == DEC_OUT_FRM_DEC400_400SP || \
  (fmt) == DEC_OUT_FRM_DEC400_420SP || \
  (fmt) == DEC_OUT_FRM_DEC400_400P || \
  (fmt) == DEC_OUT_FRM_DEC400_420P || \
  (fmt) == DEC_OUT_FRM_DEC400_400TILE || \
  (fmt) == DEC_OUT_FRM_DEC400_420TILE)

#define IS_PIC_TILED4x4(fmt) (\
  (fmt) == DEC_OUT_FRM_TILED_4X4 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE_I012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_L010 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_P012 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE_I012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE || \
  (fmt) == DEC_OUT_FRM_NV21TILE_PACK10 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_L010 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_I012 || \
  (fmt) == DEC_OUT_FRM_NV21TILE_P010)

#define IS_PIC_REF_TILED8x8(fmt) (\
  (fmt) == DEC_OUT_FRM_YUV420TILE8x8 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE8x8_PACK10 || \
  (fmt) == DEC_OUT_FRM_YUV420TILE8x8_PACK12 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE8x8 || \
  (fmt) == DEC_OUT_FRM_YUV400TILE8x8_PACK10)

#define IS_PIC_TILED8x8(fmt) ((fmt) == DEC_OUT_FRM_TILED_8X8)

#define IS_PIC_TILED16x16(fmt) ((fmt) == DEC_OUT_FRM_TILED_16X16 || (fmt) == DEC_OUT_FRM_TILED_16X16_P010)

#define IS_PIC_TILED16x16_COMP(fmt) ((fmt) == DEC_OUT_FRM_TILED_16X16_COMP || (fmt) == DEC_OUT_FRM_TILED_16X16_P010_COMP)

#define IS_PIC_TILED32x8_COMP(fmt) ((fmt) == DEC_OUT_FRM_TILED_32X8_COMP || (fmt) == DEC_OUT_FRM_TILED_32X8_P010_COMP)

#define IS_PIC_422PACKED(fmt) ((fmt) == DEC_OUT_FRM_YUV422_YUYV || (fmt) == DEC_OUT_FRM_YUV422_UYVY)

#define IS_PIC_TILED128x2(fmt) ((fmt) == DEC_OUT_FRM_YUV400TILE_128X2 || \
                                (fmt) == DEC_OUT_FRM_YUV420TILE_128X2 || \
                                (fmt) == DEC_OUT_FRM_YUV400TILE_128X2_P010 || \
                                (fmt) == DEC_OUT_FRM_YUV420TILE_128X2_P010)

#define IS_PIC_RGB_TILED64x64(fmt) ( \
  (fmt) == DEC_OUT_FRM_ABGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_ARGB888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2B10G10R10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_A2R10G10B10_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XBGR888_TILED64X64 || \
  (fmt) == DEC_OUT_FRM_XRGB888_TILED64X64)

#define IS_PP_IN_P010(fmt) \
        ((fmt == PP_IN_NV12_P010) || (fmt == PP_IN_TILED4x4_P010))

#define IS_PP_IN_TILED4x4(fmt) \
        ((fmt == PP_IN_TILED4x4) || (fmt == PP_IN_TILED4x4_P010))

#define IS_PP_IN_RGB(fmt) \
        ((fmt == PP_IN_RGB888) || \
         (fmt == PP_IN_BGR888) || \
         (fmt == PP_IN_ARGB888) || \
         (fmt == PP_IN_ABGR888) || \
         (fmt == PP_IN_A2R10G10B10) || \
         (fmt == PP_IN_A2B10G10R10) || \
         (fmt == PP_IN_X2R10G10B10) || \
         (fmt == PP_IN_X2B10G10R10))

#define IS_PP_IN_8BIT(fmt) \
        ((fmt == PP_IN_NV12_8BIT) || \
         (fmt == PP_IN_TILED4x4) || \
         (fmt == PP_IN_RGB888) || \
         (fmt == PP_IN_BGR888) || \
         (fmt == PP_IN_ARGB888) || \
         (fmt == PP_IN_ABGR888))

#define IS_PP_IN_10BIT(fmt) \
        ((fmt == PP_IN_NV12_P010) || \
         (fmt == PP_IN_TILED4x4_P010) || \
         (fmt == PP_IN_A2R10G10B10) || \
         (fmt == PP_IN_A2B10G10R10) || \
         (fmt == PP_IN_X2R10G10B10) || \
         (fmt == PP_IN_X2B10G10R10))

#define IS_PP_IN_RFC(fmt) \
        (fmt == PP_IN_RFC)
/**@}*/

/**
 * Picture coding type.
 * \ingroup common_group
 */
enum DecPicCodingType {
  DEC_PIC_TYPE_I           = 0,
  DEC_PIC_TYPE_P           = 1,
  DEC_PIC_TYPE_B           = 2,
  DEC_PIC_TYPE_D           = 3,
  DEC_PIC_TYPE_FI          = 4,
  DEC_PIC_TYPE_BI          = 5
};

enum SeqErrorState {
  SEQ_CLEAN = 0x0,
  SEQ_DIRTY = 1,
};

/**
 * Error information.
 * \ingroup common_group
 */
enum DecErrorInfo {
  DEC_NO_ERROR = 0x0,
  /** HW EC only */
  DEC_NALU_HEADER_ERROR = 0x1,
  DEC_SLICE_HEADER_ERROR = 0x2,
  DEC_SLICE_DATA_ERROR = 0x4,
  DEC_SYNC_WORD_ERROR = 0x8,
  DEC_TRAILING_BITS_ERROR = 0x10,
  DEC_POLLING_STREAM_LEN_ERROR = 0x20,
  /** All use */
  DEC_FRAME_ERROR = 0x100,
  DEC_REF_ERROR = 0x200
};

/**
 * Error handling mode.
 * \ingroup common_group
 */
enum DecErrorHandling {
  /** \brief Balanced mode: output correct frames and some error frames
   * (determined by error_ratio, default error_ratio=10%). */
  DEC_EC_FRAME_TOLERANT_ERROR = 1,
  /** \brief Fluency first mode: output all frames(include error frames). */
  DEC_EC_FRAME_IGNORE_ERROR = 2,
  /** \brief Clarity first mode: output correct frames only. */
  DEC_EC_FRAME_NO_ERROR = 3
};

/**
 * \ingroup common_group
 */
struct DecCropCfg {
  u32 crop_x;
  u32 crop_y;
  u32 crop_w;
  u32 crop_h;
  u32 crop_enabled;
};

/**
 * \ingroup common_group
 */
enum SCALE_MODE {
  NON_SCALE,
  FIXED_DOWNSCALE,
  FLEXIBLE_SCALE
} ;

/**
 * Stride alignment: aligned to 1/8/16/.../512 bytes.
 * \ingroup common_group
 */
typedef enum {
  DEC_ALIGN_1B = 0, /**< \brief Alignment: 1 byte */
  DEC_ALIGN_8B = 3, /**< \brief Alignment: 8 bytes */
  DEC_ALIGN_16B,    /**< \brief Alignment: 16 bytes */
  DEC_ALIGN_32B,    /**< \brief Alignment: 32 bytes */
  DEC_ALIGN_64B,    /**< \brief Alignment: 64 bytes */
  DEC_ALIGN_128B,   /**< \brief Alignment: 128 bytes */
  DEC_ALIGN_256B,   /**< \brief Alignment: 256 bytes */
  DEC_ALIGN_512B,   /**< \brief Alignment: 512 bytes */
  DEC_ALIGN_1024B,  /**< \brief Alignment: 1024 bytes */
  DEC_ALIGN_2048B,  /**< \brief Alignment: 2048 bytes */
} DecPicAlignment;
/**
 * \brief Delogo filter config parameters.
 * \ingroup common_group
 */
typedef struct _DelogoConfig {
  u32 enabled; /**< \brief Indicates whether delogo filter is available */
  u32 x; /**< \brief Coordinates : x */
  u32 y; /**< \brief Coordinates : y */
  u32 w; /**< \brief Size : width */
  u32 h; /**< \brief Size : height */
  u32 show; /**< \brief delogo filter level */
  enum DelogoMode mode; /**< \brief delogo filter mode */
  u32 Y; /**< \brief YUV : Y */
  u32 U; /**< \brief YUV : U */
  u32 V; /**< \brief YUV : V */
} DelogoConfig;

/**
 * \brief A structure containing PP unit configuration information.
 * \ingroup common_group
 */
typedef struct _PpUnitConfig {
  u32 enabled;    /**< \brief PP unit enabled */
  u32 tiled_e;    /**< \brief PP unit tiled4x4 output enabled */
  u32 rgb;        /**< \brief RGB output enabled */
  u32 rgb_planar; /**< \brief RGB output planar output enabled */
  u32 cr_first;   /**< \brief CrCb instead of CbCr */
  u32 shaper_enabled; /**< \brief Hardware shaper feature enabled */
  u32 shaper_no_pad;  /**< \brief shaper no need to pad for frame right edge */
  u32 dec400_enabled; /**< \brief sw control shaper and dec400  */
  u32 planar;     /**< \brief Planar output */
  DecPicAlignment align;  /**< \brief pp output alignment */
  DecPicAlignment align_h;  /**< \brief pp output height alignment */
  u32 ystride; /**< \brief Stride for Y plane : If set to 0, software should use the stride calculated
                    from software. When not 0, software should check the validation of the value. */
  u32 cstride; /**< \brief Stride for C plane : If set to 0, software should use the stride calculated
                    from software. When not 0, software should check the validation of the value. */
  struct {
    u32 enabled; /**< \brief whether cropping is enabled */
    u32 set_by_user; /**< \brief cropping set by user, use this variable to record
                            whether user set crop.*/
    u32 x;        /**< \brief cropping start x */
    u32 y;        /**< \brief cropping start y */
    u32 width;    /**< \brief cropping width */
    u32 height;   /**< \brief cropping height */
  } crop;
  struct {
    u32 enabled;
    u32 x;        /**< \brief cropping start x */
    u32 y;        /**< \brief cropping start y */
    u32 width;    /**< \brief cropping width */
    u32 height;   /**< \brief cropping height */
  } crop2;
  struct {
    u32 enabled;  /**< \brief whether scaling is enabled */
    u32 scale_by_ratio;   /**< \brief scaling output size will be calculated by ratio */
    u32 ratio_x;  /**< 0 \brief indicate flexiable mode, or 1/2/4/8 indicate ratio */
    u32 ratio_y;  /**< 0 \brief indicate flexiable mode, or 1/2/4/8 indicate ratio */
    u32 width;    /**< \brief scaled output width */
    u32 height;   /**< \brief scaled output height */
  } scale;
  u32 monochrome; /**< \brief PP output monochrome (luma only) for YUV output */
  u32 out_p010; /**< \brief P010 output with the  MSB bits valid */
  u32 out_1010; /**< \brief Each channel(Y,U,V) use 10bits */
  u32 out_I010; /**< \brief P010 output with the low 10bits valid */
  u32 out_L010; /**< \brief L010 output with the LSB bits valid. */
  u32 out_p012; /**< \brief P012 output with the  MSB bits valid */
  u32 out_I012; /**< \brief Each channel(Y,U,V) use 12bits */
  u32 out_be; /**< \brief absolute */
  u32 out_cut_8bits; /**< \brief Force 8 bit output */
  u32 out_yuyv; /**< \brief 422 output packed YUYV */
  u32 out_uyvy; /**< \brief 422 output packed UYVY */
  u32 video_range;  /**< \brief 1 - full range, 0 - limited range */
  u32 range_max; /**< \brief limited max to video range */
  u32 range_min; /**< \brief limited min to video range */
  u32 rgb_format;   /**< \brief RGB output format: RGB888/BGR888/R16G16B16/... */
  u32 rgb_stan;     /**< \brief color conversion standard applied to set coeffs */
  u32 rgb_alpha;  /**< \brief alpha channel value for RGB format */
  u32 pp_filter;  /**< \brief selector for pp scale algorithm */
  u32 x_filter_param; /**< \brief when select LANCZOS scale, set the horizontal window param */
  u32 y_filter_param; /**< \brief when select LANCZOS scale, set the vertical window param */
  u32 tile_mode; /**< \brief when pp tile enable, set the tiled format */
  u32 pp_comp; /**< \brief Enable TILED16x16 or TILED32x8 compression in PP */
  u32 src_sel_mode; /**< \brief set the center point select algorithm for pp scale, default is DOWN ROUND */
  u32 pad_sel; /**< \brief whether pad value is used for pp scale for the picture boundary */
  u32 pad_Y; /**< \brief the luma pad value */
  u32 pad_U; /**< \brief the Cb pad value */
  u32 pad_V; /**< \brief the Cr pad value */
  u32 chroma_format; /**< \brief the output YCbCr format */
  u32 lc_stripe;  /**< \brief number of lines to trigger line counter interrupt */
  u32 out1to1;
  u32 luma_offset; /**< \brief begin offset for luma date wirte in pp output buffer(heif special) */
  u32 chroma_offset; /**< \brief begin offset for chroma date wirte in pp output buffer(heif special) */
  u32 buf_off_set_by_user; /**< \brief the tag of set luma and chroma offset in pp output buffer by TB (heif special) */
} PpUnitConfig;
#endif /* DECAPICOMMON_H */
