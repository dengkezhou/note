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

#ifndef __H264DECAPI_H__
#define __H264DECAPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "basetype.h"
#include "decapicommon.h"
#include "dectypes.h"
#include "dwl.h"
#include "decsei.h" /* sei_param */

/*------------------------------------------------------------------------------
    API type definitions
------------------------------------------------------------------------------*/
/**
 * \brief H264 Decoder instance
 * \ingroup h264_group
 */
typedef const void *H264DecInst;

/**
 * \struct H264DecInput
 * \brief the H264 decoder input. \n
 * H264DecInput : A typename for H264DecInput_.
 * \ingroup h264_group
 */
typedef struct H264DecInput_ {
  const u8 *stream;   /**< Pointer to the input buffer*/
  addr_t stream_bus_address; /**< DMA bus address of the input buffer */
  u32 data_len;          /**< Number of bytes to be decoded         */
  u8 *buffer;
  addr_t buffer_bus_address;
  u32 buff_len;
  u32 pic_id;            /**< Identifier for the next picture to be decoded */
  enum DecSkipFrameMode skip_frame; /* Skip some frames when decoding. */
  void *p_user_data; /* user data to be passed in multicore callback */
  struct SEI_buffer *sei_buffer; /**< SEI buffer */
} H264DecInput;

/**
 * \struct H264DecInfo
 * \brief stream info filled by H264DecGetInfo. \n
 * H264DecInfo A typename for H264DecInfo_.
 * \ingroup h264_group
 */
typedef struct H264DecInfo_ {
  u32 pic_width;        /**< decoded picture width in pixels */
  u32 pic_height;       /**< decoded picture height in pixels */
  u32 video_range;      /**< samples' video range */
  u32 colour_primaries;
  u32 transfer_characteristics;
  u32 colour_description_present_flag; /* indicate matrix_coefficients/
                      colour_primaries/transfer_characteristics present or not */
  u32 matrix_coefficients;
  struct DecCropParams crop_params;  /**< display cropping information */
  enum DecPictureFormat output_format;  /**< format of the output picture */
  u32 sar_width;        /**< sample aspect ratio */
  u32 sar_height;       /**< sample aspect ratio */
  u32 mono_chrome;      /**< is sequence monochrome */
  u32 interlaced_sequence;      /**< is sequence interlaced */
  u32 dpb_mode;         /**< DPB mode; frame, or field interlaced */
  u32 pic_buff_size;     /**< number of picture buffers allocated and used by decoder */
  u32 multi_buff_pp_size; /**< number of picture buffers needed in decoder+postprocessor multibuffer mode */
  u32 bit_depth;
  u32 pp_enabled;
  u32 base_mode;  /**< decode this stream in non-high10 mode and not use ringbuffer*/
  u32 chroma_format_idc; /*0 mono chrome; 1 yuv420; 2 yuv422*/
  /* time scale info */
  u32 timing_info_present_flag;
  u32 num_units_in_tick;
  u32 time_scale;
#ifdef ASIC_TRACE_SUPPORT
  u32 sim_mc;
#endif
} H264DecInfo;

/**
 * \struct H264DecPicture
 * \brief Output structure for H264DecNextPicture. \n
 * H264DecPicture A typename for H264DecPicture_.
 * \ingroup h264_group
 */
typedef struct H264DecPicture_ {
  u32 sar_width;        /**< sample aspect ratio */
  u32 sar_height;       /**< sample aspect ratio */
  u32 pic_width;        /**< pixels width of the stream */
  u32 pic_height;       /**< pixels height of the stream */
  struct DecCropParams crop_params;  /**< cropping parameters */
  u32 pic_id;           /**< Identifier of the picture to be displayed */
  u32 decode_id[2];
  struct H264SEIParameters *sei_param[2];  /**< sei parameter data */
  u32 pic_coding_type[2];   /**< Picture coding type */
  u32 is_idr_picture[2];    /**< Indicates if picture is an IDR picture */
  u32 is_gdr_frame;    /**< Indicates if picture is an GDR picture */
  u32 error_ratio[2];  /**< The ratio of error mbs to whole picture mbs.(100 times) */
  enum DecErrorInfo error_info;     /**< Indicates that picture is error */
  u32 interlaced;      /**< flag, non-zero for interlaced picture */
  u32 field_picture;    /**< flag, non-zero if interlaced and only one field present */
  u32 corrupted_second_field; /**< flag, second field corrupted */
  u32 top_field;        /**< flag, if only one field, non-zero signals TOP field otherwise BOTTOM */
  u32 view_id;          /**< Identifies the view to which the output picture belongs */
  u32 pic_struct;       /**< pic_struct extracted from pic timing SEI */
  u32 bit_depth_luma;   /**< bit depth of luma plane */
  u32 bit_depth_chroma; /**< bit depth of chroma plane */
  u32 cycles_per_mb;
  u32 chroma_format_idc; /*0 mono chrome; 1 yuv420; 2 yuv422*/
#ifdef FPGA_PERF_AND_BW
  u32 bitrate_4k60fps; /**< The bitrate per macroblock of the picture */
  u32 bwrd_in_fs; /**< The read bandwidth per macroblock of the picture */
  u32 bwwr_in_fs; /**< The write bandwidth per macroblock of the picture */
#endif
  u32 dmv_size;
  const u32 *output_dmv;         /* Pointer to the DMV data */
  addr_t output_dmv_bus_address;    /* DMA bus address of the output DMV buffer */
  u32 qp_size;
  const u32 *output_qp;  /**< Pointer to the QP data */
  addr_t output_qp_bus_address;    /**< DMA bus address of the output QP buffer */
  const u32 *output_rfc_luma_base;   /**< Pointer to the rfc table */
  addr_t output_rfc_luma_bus_address;
  const u32 *output_rfc_chroma_base; /**< Pointer to the rfc chroma table */
  addr_t output_rfc_chroma_bus_address; /**< Bus address of the chrominance table */
  struct H264OutputInfo {
    u32 pic_width;        /**< pixels width of the picture as stored in memory */
    u32 pic_height;       /**< pixel height of the picture as stored in memory */
    u32 pic_stride;       /** < pic stride of each pixel line in bytes. */
    u32 pic_stride_ch;
    u32 chroma_format;
    const u32 *output_picture;  /**< Pointer to the picture data */
    addr_t output_picture_bus_address;    /**< DMA bus address of the output picture buffer */
    const u32 *output_picture_chroma;  /**< Pointer to the chroma picture data */
    addr_t output_picture_chroma_bus_address;    /**< DMA bus address of the output picture buffer */
    enum DecPictureFormat output_format; /**< Storage format of output picture. */
#ifdef SUPPORT_DEC400
    struct DWLLinearMem dec400_luma_table;           /**< Buffer properties *//*sunny add for tile status address*/
    struct DWLLinearMem dec400_chroma_table;           /**< Buffer properties *//*sunny add for tile status address*/
#endif
  } pictures[DEC_MAX_OUT_COUNT];
} H264DecPicture;


/**
 * \struct H264DecApiVersion
 * \brief API Version information. \n
 * H264DecApiVersion A typename for H264DecApiVersion_.
 * \ingroup h264_group
 */
typedef struct H264DecApiVersion_ {
  u32 major;           /**< API major version */
  u32 minor;           /**< API minor version */
  u32 micro;           /**< API micro version */
} H264DecApiVersion;

/**
 * \struct H264DecConfig
 * \brief Containing the H264-specific configuration.. \n
 * \ingroup h264_group
 */
struct H264DecConfig {
  u32 no_output_reordering;
  enum DecErrorHandling error_handling;
  u32 error_ratio;
  u32 use_video_compressor;
  enum DecDpbFlags dpb_flags;
  u32 multi_frame_input_flag; /**< Specifies the input stream of decoder contains at least two frames. */
  enum DecDecoderMode decoder_mode;
  u32 strm_status_in_buffer; /**< With low-latency decoding mode,
                            stream status is updated in buffer instead of registers. */
  u32 use_adaptive_buffers; // When sequence changes, if old output buffers (number/size) are sufficient for new sequence,
  // old buffers will be used instead of reallocating output buffer.
  u32 guard_size;       // The minimum difference between minimum buffers number and allocated buffers number
  // that will force to return HDRS_RDY even buffers number/size are sufficient
  // for new sequence.
  DecPicAlignment align;
  u32 hw_conceal;
  u32 dump_auxinfo;
  u32 disable_slice_mode;
  u32 mvc; /**< Indicates whether mvc stream */
  i8 max_temporal_layer; /**< The maximum temporal layer that the VCD supports decoding(only hevc/h264/vvc). */

  PpUnitConfig ppu_cfg[DEC_MAX_OUT_COUNT];
  DelogoConfig delogo_params[2];
  struct DecMCConfig mcinit_cfg;
  u32 rlc_mode;
  u32 support_asofmo_stream; /**< 1: support aso/fmo stream decoding, 0: not support aso/fmo stream decoding */
#ifdef ASIC_TRACE_SUPPORT
  u32 sim_mc;
#endif
};

/**
 * \brief Initializes decoder software. \n
 * - Single core decoder can decode both byte streams and NAL units.
 * FMO and ASO streams are supported also, but these will require an
 * internal switch to less hardware acceleration. For FMO and ASO stream
 * the entropy decoding is done in software.
 * - Every instance has to be released with H264DecRelease().
 * - Use H264DecMCInit() for creating an instance with multicore support.
 * \ingroup h264_group
 * \param [in]     dec_inst       Pointer to the location where this function returns a decoder instance.
                                  This instance is later passed to other decoder API functions.
 * \param [in]     dwl            Pointer to a DWL structure.
                                  Refer to the Hantro DWL API for Video Decoders document for more information.
 * \param [in]     dec_cfg        Pointer to the decoder initialization parameters (H264DecConfig).
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_MEMFAIL, DEC_FORMAT_NOT_SUPPORTED.
 */
enum DecRet H264DecInit(H264DecInst *dec_inst,
                       const void *dwl,
                       struct H264DecConfig *dec_cfg);

/**
 * \brief This function is called by the client to set the decoder configuration. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     dec_cfg        Pointer to the decoder configure parameters (H264DecConfig).
 * \param [out]    DecRet         value: DEC_OK, DEC_NOT_INITIALIZED, DEC_PARAM_ERROR
 */
enum DecRet H264DecSetInfo(H264DecInst dec_inst,
                          struct H264DecConfig *dec_cfg);

/**
 * \brief Releases the decoder instance. \n
 * Function calls H264ShutDown to release instance data and frees the memory allocated for the instance.
 * \ingroup h264_group
 * \param [in]     dec_inst       The decoder instance to be released. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [out]    void           None.
 */
void H264DecRelease(H264DecInst dec_inst);

/**
 * \brief This function decodes one or more NAL units from the current stream. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     input          Pointer to the decoder input structure H264DecInput.
 * \param [in]     output         Pointer to the decoder output structure struct DecOutput
 * \param [out]    DecRet         value: DEC_PIC_DECODED, DEC_HDRS_RDY, DEC_PARAM_ERROR, DEC_STRM_ERROR,
 *                                DEC_NOT_INITIALIZED, DEC_HW_BUS_ERROR, DEC_HW_TIMEOUT, DEC_MEMFAIL,
 *                                DEC_STREAM_NOT_SUPPORTED, DEC_NONREF_PIC_SKIPPED, DEC_WAITING_FOR_BUFFER,
 *                                DEC_ABORTED, DEC_STRM_PROCESSED, DEC_SYSTEM_ERROR, DEC_HW_RESERVED,
 *                                DEC_PENDING_FLUSH, DEC_NO_DECODING_BUFFER, DEC_BUF_EMPTY
 */
enum DecRet H264DecDecode(H264DecInst dec_inst,
                         const H264DecInput *input,
                         struct DecOutput *output);

/**
 * \brief Provides access to the next picture in display order.
 * \warning Do not use with multicore instances! Use instead H264DecMCNextPicture().
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     picture        Pointer to an H264DecPicture structure used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED,
 *                                DEC_END_OF_STREAM, DEC_ABORTED, DEC_FLUSHED
 */
enum DecRet H264DecNextPicture(H264DecInst dec_inst,
                              H264DecPicture *picture, u32 end_of_stream);

/**
 * \brief This function informs the decoder that the client has finished processing the specific
 * picture and releases the picture buffer for the decoder to process the next picture. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     picture        Pointer to an H264DecPicture structure used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet H264DecPictureConsumed(H264DecInst dec_inst,
                                  const H264DecPicture *picture);

/**
 * \brief This function informs the decoder that it should not be expecting any more input stream and to
 * finish decoding and outputting all the buffers that are currently pending in the component. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     strm_end_flag
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_INIT_FAIL
 */
enum DecRet H264DecEndOfStream(H264DecInst dec_inst, u32 strm_end_flag);

/**
 * \brief This function is called by the client to abort the decoder. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet H264DecAbort(H264DecInst dec_inst);

/**
 * \brief This function is called by the client to reset the decoder after the decoder is aborted. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet H264DecAbortAfter(H264DecInst dec_inst);

/**
 * \brief This function provides read access to decoder information. This function should not
 * be called before H264DecDecode function has indicated that headers are ready. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     dec_info       Pointer to an H264DecInfo structure where the decoder information will be returned.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_HDRS_NOT_RDY, DEC_NOT_INITIALIZED
 */
enum DecRet H264DecGetInfo(H264DecInst dec_inst, H264DecInfo *dec_info);

/**
 * \brief Get last decoded picture if any available. No pictures are removed from output nor DPB buffers. \n
 * \warning Do not use with multicore instances! Use instead H264DecMCNextPicture().
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     output         Pointer to an H264DecPicture structure where this function will return information
 *                                about the decoded picture.
 * \param [out]    DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet H264DecPeek(H264DecInst dec_inst, H264DecPicture *picture);

/**
 * \brief This function is called by the client to add an external frame buffer into the decoder. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     info           Pointer to a DWLLinearMem structure.
 * \param [out]    DecRet         value: DEC_PARAM_ERROR, DEC_EXT_BUFFER_REJECTED, DEC_WAITING_FOR_BUFFER
 */
enum DecRet H264DecAddBuffer(H264DecInst dec_inst, struct DWLLinearMem *info);

/**
 * \brief This function is called by the client to get the frame buffer information
 * requested by the decoder, including the requested buffer size and buffer numbers. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     mem_info       Pointer to a struct DecBufferInfo structure.
 * \param [out]    DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_WAITING_FOR_BUFFER
 */
enum DecRet H264DecGetBufferInfo(H264DecInst dec_inst, struct DecBufferInfo *mem_info);

/**
 * \brief This function is called by client to set the decoder output picture order as either
 * decoding order or display order. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     no_reorder     Set the output model to no_reording.
 * \param [out]    void           None.
 */
enum DecRet H264DecSetNoReorder(H264DecInst dec_inst, u32 no_output_reordering);

/**
 * \brief This function is related to low latency mode and is called by the client to update
 * the H264 decoder stream length register at the specified address. \n
 * \ingroup h264_group
 * \param [in]     dec_inst       A decoder instance created earlier with a call to H264DecInit. \n
                                  H264DecInst is defined as: typedef const void *H264DecInst.
 * \param [in]     info           Stream information data structure.
 */
void H264DecUpdateStrmInfoCtrl(H264DecInst dec_inst, struct strmInfo info);

/**
 * \brief This function traces all API entries and returns. This must be implemented by
 * the application using the decoder API.
 * \ingroup h264_group
 * \param [in]     string         string Pointer to a NULL terminated char string.
 * \param [out]    void           None.
 */
void H264DecTrace(const char *string);

/*!\example h264dectrace.c
  * This is an example of how to implement H264DecTrace() in an application.
  *
  *!\example h264decmc_output_handling.c
  * This is an example of how to handle the decoder output in a
  * multi-threaded application.
  */

#ifdef __cplusplus
}
#endif

#endif                       /* __H264DECAPI_H__ */
