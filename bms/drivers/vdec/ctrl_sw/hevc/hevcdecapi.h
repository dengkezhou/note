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

#ifndef HEVCDECAPI_H
#define HEVCDECAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "basetype.h"
#include "decapicommon.h"
#include "dectypes.h"
#include "sw_util.h"
#include "decsei.h" /* sei_param */

/*------------------------------------------------------------------------------
    API type definitions
------------------------------------------------------------------------------*/
/**
 * \brief HEVC Decoder instance
 * \ingroup hevc_group
 */
typedef const void *HevcDecInst;

/**
 * \struct HevcDecInput
 * \brief the HEVC decoder input.
 * \ingroup hevc_group
 */
struct HevcDecInput {
  u8 *stream;             /**< Pointer to the input */
  addr_t stream_bus_address; /**< DMA bus address of the input stream */
  u32 data_len;           /**< Number of bytes to be decoded */
  u8 *buffer;
  addr_t buffer_bus_address;
  u32 buff_len;           /**< Stream buffer byte length */
  u32 pic_id;             /**< Identifier for the picture to be decoded */
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
  u32 *raster_out_y;
  addr_t raster_out_bus_address_y; /**< DMA bus address of the input stream */
  u32 *raster_out_c;
  addr_t raster_out_bus_address_c;
  void *p_user_data; /**< Pointer to user data to be passed in multicore callback */
  struct SEI_buffer *sei_buffer; /**< SEI buffer */
};

/**
 * \struct HevcDecInfo
 * \brief stream info filled by HevcDecGetInfo.
 * \ingroup hevc_group
 */
struct HevcDecInfo {
  u32 pic_width;   /**< decoded picture width in pixels */
  u32 pic_height;  /**< decoded picture height in pixels */
  u32 video_range; /**< samples' video range */
  u32 matrix_coefficients;
  u32 colour_primaries; /**< indicates the chromaticity coordinates of the source primaries */
  struct DecCropParams crop_params;   /**< display cropping information */
  enum DecPictureFormat output_format; /**< format of the output picture */
  u32 sar_width;                       /**< sample aspect ratio */
  u32 sar_height;                      /**< sample aspect ratio */
  u32 mono_chrome;                     /**< is sequence monochrome */
  u32 interlaced_sequence;             /**< is sequence interlaced */
  u32 dpb_mode;      /**< DPB mode; frame, or field interlaced */
  u32 pic_buff_size; /**< number of picture buffers allocated&used by decoder */
  u32 multi_buff_pp_size; /**< number of picture buffers needed in
                             decoder+postprocessor multibuffer mode */
  u32 bit_depth;     /**< bit depth per pixel stored in memory */
  u32 pic_stride;         /**< Byte width of the pixel as stored in memory */

  u32 transfer_characteristics; /**< for HDR */
  u32 chroma_format_idc; /*0 mono chrome; 1 yuv420; 2 yuv422*/
  /* time scale info */
  u32 timing_info_present_flag;
  u32 num_units_in_tick;
  u32 time_scale;
  u32 trc_status; /**< \brief 0-both filled
                       * 1-only filled transfer_characteristics
                       * 2-only filled preferred_transfer_characteristics
                       */
  u32 preferred_transfer_characteristics;
#ifdef ASIC_TRACE_SUPPORT
  u32 sim_mc;
#endif
};

/**
 * \struct HevcDecPicture
 * \brief Output structure for HevcDecNextPicture.
 * \ingroup hevc_group
 */
struct HevcDecPicture {
  struct DecCropParams crop_params; /**< cropping parameters */
  u32 pic_id;         /**< Identifier of the decoing order of the picture */
  i32 poc;
  u32 is_idr_picture; /**< Indicates if picture is an IDR picture */
  u32 is_gdr_frame; /**< Indicates if picture is a GDR picture */
  u32 pic_coding_type;   /**< Picture coding type */
  u32 error_ratio;     /**< The ratio of error ctbs to whole picture ctbs.(100 times) */
  enum DecErrorInfo error_info; /**< Indicates that picture is error */
  u32 bit_depth_luma;
  u32 bit_depth_chroma;
  u32 pp_enabled;
  u32 num_tile_columns;
  struct HevcSEIParameters *sei_param; /**< sei parameter data */
  const u32 *output_rfc_luma_base;   /**< Pointer to the rfc table */
  addr_t output_rfc_luma_bus_address;
  const u32 *output_rfc_chroma_base; /**< Pointer to the rfc chroma table */
  addr_t output_rfc_chroma_bus_address; /**< Bus address of the chrominance table */
  u32 dmv_size;
  const u32 *output_dmv;         /* Pointer to the DMV data */
  addr_t output_dmv_bus_address;    /* DMA bus address of the output DMV buffer */
  u32 qp_size;
  const u32 *output_qp;         /* Pointer to the QP data */
  addr_t output_qp_bus_address;    /* DMA bus address of the output QP buffer */
  u32 cycles_per_mb;   /**< Avarage cycle count per macroblock */
#ifdef FPGA_PERF_AND_BW
  u32 bitrate_4k60fps; /**< The bitrate per macroblock of the picture */
  u32 bwrd_in_fs; /**< The read bandwidth per macroblock of the picture */
  u32 bwwr_in_fs; /**< The write bandwidth per macroblock of the picture */
#endif
  struct HevcDecInfo dec_info; /**< Stream info by HevcDecGetInfo */
  struct HevcOutputInfo {
    u32 pic_width;  /**< pixels width of the picture as stored in memory */
    u32 pic_height; /**< pixel height of the picture as stored in memory */
    u32 pic_stride;       /**< Byte width of the picture as stored in memory */
    u32 pic_stride_ch;
    u32 chroma_format;
    const u32 *output_picture;         /**< Pointer to the picture */
    addr_t output_picture_bus_address;    /**< DMA bus address of the output picture buffer */
    const u32 *output_picture_chroma;         /**< Pointer to the picture */
    addr_t output_picture_chroma_bus_address;    /**< DMA bus address of the output picture buffer */
    enum DecPictureFormat output_format;
    struct DWLLinearMem luma_table;
    struct DWLLinearMem chroma_table;
  } pictures[DEC_MAX_OUT_COUNT];
};

/**
 * \struct HevcDecConfig
 * \brief Containing the HEVC-specific configuration.
 * \ingroup hevc_group
 */
struct HevcDecConfig {
  u32 no_output_reordering;
  enum DecErrorHandling error_handling;
  u32 error_ratio;
  u32 use_video_compressor;
  u32 multi_frame_input_flag; /**< Specifies the input stream of decoder contains at least two frames. */
  enum DecDecoderMode decoder_mode;
  u32 use_adaptive_buffers; /**< When sequence changes, if old output buffers (number/size) are sufficient for new sequence,
                                 old buffers will be used instead of reallocating output buffer. */
  u32 num_buffers; /* decoder buffer number specified by user */
  u32 guard_size; /**< The minimum difference between minimum buffers number and allocated buffers number
                       that will force to return HDRS_RDY even buffers number/size are sufficient for new sequence. */
  DecPicAlignment align;
  u32 hw_conceal;
  u32 dump_auxinfo;
  u32 disable_slice_mode;
  u32 strm_status_in_buffer; /**< With low-latency decoding mode, stream status is updated in buffer instead of registers. */
  i8 max_temporal_layer; /**< The maximum temporal layer that the VCD supports decoding(only hevc/h264/vvc). */

  PpUnitConfig ppu_cfg[DEC_MAX_OUT_COUNT];
  DelogoConfig delogo_params[2];
  struct DecMCConfig mcinit_cfg;
#ifdef ASIC_TRACE_SUPPORT
  u32 sim_mc;
#endif
};

/*------------------------------------------------------------------------------
    Prototypes of Decoder API functions
------------------------------------------------------------------------------*/
/**
 * \brief Initializes decoder software. \n
 * Function reserves memory for the decoder instance and calls HevcInit to initialize the instance data.
 * \ingroup hevc_group
 * \param [in]     dec_inst       Pointer to the location where this function returns a decoder instance.
                                  This instance is later passed to other decoder API functions.
 * \param [in]     dwl            Pointer to a DWL structure.
                                  Refer to the Hantro DWL API for Video Decoders document for more information.
 * \param [in]     dec_cfg        Pointer to the decoder initialization parameters (HevcDecConfig).
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_MEMFAIL, DEC_FORMAT_NOT_SUPPORTED.
 */
enum DecRet HevcDecInit(HevcDecInst *dec_inst, const void *dwl, struct HevcDecConfig *dec_cfg);

/**
 * \brief Releases the decoder instance. \n
 * Function calls HevcShutDown to release instance data and frees the memory allocated for the instance.
 * \ingroup hevc_group
 * \param [in]     dec_inst       The decoder instance to be released. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [out]    void           None.
 */
void HevcDecRelease(HevcDecInst dec_inst);

/**
 * \brief This function decodes one or more NAL units from the current stream. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     input          Pointer to the decoder input structure HevcDecInput.
 * \param [in]     output         Pointer to the decoder output structure DecOutput
 * \param [out]    DecRet         value: DEC_PIC_DECODED, DEC_HDRS_RDY, DEC_PARAM_ERROR, DEC_STRM_ERROR,
 *                                DEC_NOT_INITIALIZED, DEC_HW_BUS_ERROR, DEC_HW_TIMEOUT, DEC_MEMFAIL,
 *                                DEC_STREAM_NOT_SUPPORTED, DEC_NONREF_PIC_SKIPPED, DEC_WAITING_FOR_BUFFER,
 *                                DEC_ABORTED, DEC_STRM_PROCESSED, DEC_SYSTEM_ERROR, DEC_HW_RESERVED,
 *                                DEC_PENDING_FLUSH, DEC_NO_DECODING_BUFFER, DEC_BUF_EMPTY
 */
enum DecRet HevcDecDecode(HevcDecInst dec_inst, const struct HevcDecInput *input,
                          struct DecOutput *output);

/**
 * \brief Provides access to the next picture in display order. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     picture        Pointer to an HevcDecPicture structure used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED,
 *                                DEC_END_OF_STREAM, DEC_ABORTED, DEC_FLUSHED
 */
enum DecRet HevcDecNextPicture(HevcDecInst dec_inst,
                               struct HevcDecPicture *picture);

/**
 * \brief This function informs the decoder that the client has finished processing the specific
 * picture and releases the picture buffer for the decoder to process the next picture. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     picture        Pointer to an HevcDecPicture structure used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet HevcDecPictureConsumed(HevcDecInst dec_inst,
                                   const struct HevcDecPicture *picture);

/**
 * \brief This function informs the decoder that it should not be expecting any more input stream and to
 * finish decoding and outputting all the buffers that are currently pending in the component. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_INIT_FAIL
 */
enum DecRet HevcDecEndOfStream(HevcDecInst dec_inst);

/**
 * \brief This function provides read access to decoder information. This function should not
 * be called before HevcDecDecode function has indicated that headers are ready. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     dec_info       Pointer to an HevcDecInfo structure where the decoder information will be returned.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_HDRS_NOT_RDY, DEC_NOT_INITIALIZED
 */
enum DecRet HevcDecGetInfo(HevcDecInst dec_inst, struct HevcDecInfo *dec_info);

/**
 * \brief Get last decoded picture if any available. No pictures are removed from output nor DPB buffers. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     output         Pointer to an HevcDecPicture structure where this function will return information
 *                                about the decoded picture.
 * \param [out]    DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet HevcDecPeek(HevcDecInst dec_inst, struct HevcDecPicture *output);

/**
 * \brief This function is called by the client to add an external frame buffer into the decoder. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     info           Pointer to a DWLLinearMem structure.
 * \param [out]    DecRet         value: DEC_PARAM_ERROR, DEC_EXT_BUFFER_REJECTED, DEC_WAITING_FOR_BUFFER
 */
enum DecRet HevcDecAddBuffer(HevcDecInst dec_inst, struct DWLLinearMem *info);

/**
 * \brief This function is called by the client to get the frame buffer information
 * requested by the decoder, including the requested buffer size and buffer numbers. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     mem_info       Pointer to a DecBufferInfo structure.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_WAITING_FOR_BUFFER
 */
enum DecRet HevcDecGetBufferInfo(HevcDecInst dec_inst, struct DecBufferInfo *mem_info);

/**
 * \brief This function is called by the client to abort the decoder. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet HevcDecAbort(HevcDecInst dec_inst);

/**
 * \brief This function is called by the client to reset the decoder after the decoder is aborted. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet HevcDecAbortAfter(HevcDecInst dec_inst);

/**
 * \brief This function is called by client to set the decoder output picture order as either
 * decoding order or display order. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     no_reorder     Set the output model to no_reording.
 * \param [out]    void           None.
 */
void HevcDecSetNoReorder(HevcDecInst dec_inst, u32 no_reorder);

/**
 * \brief This function is called by the client to set the decoder configuration. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     dec_cfg        Pointer to the decoder configure parameters (HevcDecConfig).
 * \param [out]    DecRet         value: DEC_OK, DEC_NOT_INITIALIZED, DEC_PARAM_ERROR
 */
enum DecRet HevcDecSetInfo(HevcDecInst dec_inst, struct HevcDecConfig *dec_cfg);

/**
 * \brief This function is related to low latency mode and is called by the client to update
 * the HEVC decoder stream length register at the specified address. \n
 * \ingroup hevc_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to HevcDecInit. \n
                                  HevcDecInst is defined as: typedef const void *HevcDecInst.
 * \param [in]     info           Stream information data structure.
 */
void HevcDecUpdateStrmInfoCtrl(HevcDecInst dec_inst, struct strmInfo info);

enum DecRet HevcDecUseExtraFrmBuffers(HevcDecInst dec_inst, u32 n);

#ifdef __cplusplus
}
#endif

#endif /* HEVCDECAPI_H */
