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

#ifndef VCDECAPI_H
#define VCDECAPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "basetype.h"
#include "dectypes.h"
#include "dwl.h"

/*------------------------------------------------------------------------------
VCDecAPI : used in decapi.c or testbench
------------------------------------------------------------------------------*/
/**
 * Returns the decoder’s API version.
 * This function does not require the creation of a decoder instance.
 * \ingroup common_group
 * \param [in]     void               None.
 * \return         DecApiVersion      struct DecApiVersion.
 */
struct DecApiVersion VCDecGetAPIVersion(void);

/**
 * Returns the decoder’s hardware and software build information.
 * This function does not require the creation of a decoder instance.
 * \ingroup common_group
 * \param [in]     client_type           Specifies the client type.
 * \return         DecSwHwBuild   struct DecSwHwBuild.
 */
struct DecSwHwBuild VCDecGetBuild(u32 client_type);

/**
 * This function read number of HW cores available (Multicore specific).
 * This function does not require the creation of a decoder instance.
 * \ingroup common_group
 * \param [in]     void           None.
 * \return         u32            The number of available hardware decoding cores..
 */
u32 VCDecMCGetCoreCount(void); /* new, special one */

/**
 * Unpacks metadata elements for sequence header C from buffer,
 * when metadata is packed according to SMPTE VC-1 Standard Annex J(VC1 specific).
 * This function does not require the creation of a decoder instance.
 * \ingroup common_group
 * \param [in]     codec          Specifies the decoder types.
 * \param [in]     p_buffer       Pointer to buffer containing packed metadata. Buffer
                                  must contain at least 4 bytes.
 * \param [in]     buffer_size    Buffer size in bytes.
 * \param [in]     p_meta_data    Pointer to stream metadata container.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_METADATA_FAIL.
 */
enum DecRet VCDecUnpackMetaData(enum DecCodec codec, const u8 *p_buffer, u32 buffer_size,
                                struct DecMetaData* p_meta_data);

/**
 * Initializes decoder software.
 * Function reserves memory for the decoder instance and calls xxxInit to initialize the instance data.
 * \ingroup common_group
 * \param [in]     inst           Pointer to the location where this function returns a decoder instance.
                                  This instance is later passed to other decoder API functions.
 * \param [in]     dec_cfg        Pointer to the decoder initialization parameters.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_MEMFAIL, DEC_FORMAT_NOT_SUPPORTED.
 */
enum DecRet VCDecInit(const void** inst, struct DecInitConfig *init_config);

/**
 * This function provides read access to decoder information. This function should not
 * be called before VCDecDecode function has indicated that headers are ready.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     info           Pointer to an DecSequenceInfo structure where the decoder information will be returned.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_HDRS_NOT_RDY, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecGetInfo(void* inst, struct DecSequenceInfo* info);

/**
 * This function is called by the client to set the decoder configuration.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     config         Pointer to the decoder configure parameters (DecConfig).
 * \return         DecRet         value: DEC_OK, DEC_NOT_INITIALIZED, DEC_PARAM_ERROR
 */
enum DecRet VCDecSetInfo(void* inst, struct DecConfig *config);

/**
 * This function decodes one or more NAL units from the current stream.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     output         Pointer to the decoder output parameters.
 * \param [in]     param          Pointer to the decoder input parameters.
 * \return         DecRet         value: DEC_PIC_DECODED, DEC_HDRS_RDY, DEC_PARAM_ERROR, DEC_STRM_ERROR,
 *                                DEC_NOT_INITIALIZED, DEC_HW_BUS_ERROR, DEC_HW_TIMEOUT, DEC_MEMFAIL,
 *                                DEC_STREAM_NOT_SUPPORTED, DEC_NONREF_PIC_SKIPPED, DEC_WAITING_FOR_BUFFER,
 *                                DEC_ABORTED, DEC_STRM_PROCESSED, DEC_SYSTEM_ERROR, DEC_HW_RESERVED,
 *                                DEC_PENDING_FLUSH, DEC_NO_DECODING_BUFFER, DEC_BUF_EMPTY
 */
enum DecRet VCDecDecode(void* inst, struct DecOutput* output, struct DecInputParameters* param);

/**
 * Provides access to the next picture in display order.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     pic            Pointer to a DecPictures structure which used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \return         DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED,
 *                                DEC_END_OF_STREAM, DEC_ABORTED, DEC_FLUSHED
 */
enum DecRet VCDecNextPicture(void* inst, struct DecPictures* pic);

/**
 * This function informs the decoder that the client has finished processing the specific
 * picture and releases the picture buffer for the decoder to process the next picture.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     pic            Pointer to a DecPictures structure which used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecPictureConsumed(void* inst, struct DecPictures *pic);

/**
 * This function informs the decoder that it should not be expecting any more input stream and to
 * finish decoding and outputting all the buffers that are currently pending in the component.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_INIT_FAIL
 */
enum DecRet VCDecEndOfStream(void* inst);

/**
 * This function is called by the client to get the frame buffer information
 * requested by the decoder, including the requested buffer size and buffer numbers.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     buf_info       Pointer to a DecBufferInfo structure which used to return the buffer info.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_WAITING_FOR_BUFFER
 */
enum DecRet VCDecGetBufferInfo(void *inst, struct DecBufferInfo *buf_info);

/**
 * This function is called by the client to add an external frame buffer into the decoder.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     buf            Pointer to a DWLLinearMem structure.
 * \return         DecRet         value: DEC_PARAM_ERROR, DEC_EXT_BUFFER_REJECTED, DEC_WAITING_FOR_BUFFER
 */
enum DecRet VCDecAddBuffer(void *inst, struct DWLLinearMem *buf);

/**
 * This function is called by the client to indicates that 'n' extra frames in DPB are needed.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     n              Need 'n' extra frames in DPB.
 * \return         DecRet         value: DEC_OK.
 */
enum DecRet VCDecUseExtraFrmBuffers(void* inst, u32 n);

/**
 * Get last decoded picture if any available. No pictures are removed from output nor DPB buffers.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     pic            Pointer to a DecPictures structure which used to return the picture parameters.
 *                                The picture parameters are valid only when the return value indicates that an
 *                                output picture is available.
 * \return         DecRet         value: DEC_OK, DEC_PIC_RDY, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecPeek(void* inst, struct DecPictures *pic);

/**
 * This function is called by the client to abort the decoder.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecAbort(void* inst);

/**
 * This function is called by the client to reset the decoder after the decoder is aborted.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \return         DecRet         value: DEC_OK, DEC_PARAM_ERROR, DEC_NOT_INITIALIZED
 */
enum DecRet VCDecAbortAfter(void* inst);

/**
 * This function is called by client to set the decoder output picture order as either
 * decoding order or display order.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     no_reorder     Set the output model to no_reording.
 * \return         void           None.
 */
void VCDecSetNoReorder(void* inst, u32 no_reorder);

/**
 * Releases the decoder instance.
 * Function used to release instance data and frees the memory allocated for the instance.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 *                                The decoder instance to be released.
 * \return         void           None.
 */
void VCDecRelease(void* inst);

/**
 * This function is related to low latency mode and is called by the client to update
 * the decoder stream length register at the specified address.
 * \ingroup common_group
 * \param [in]     inst           A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     info           Stream information data structure.
 * \return         void           None.
 */
void VCDecUpdateStrmInfoCtrl(void* inst, struct strmInfo info);

/**
 * This function is used to get user data information (mpeg4 specific).
 * \ingroup common_group
 * \param [in]     inst                A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     param               Pointer to the input parameters.
 * \param [in]     user_data_config    Pointer to the user data configuration.
 * \return         DecRet              value: DEC_OK, DEC_PARAM_ERROR.
 */
enum DecRet VCDecGetUserData(void* inst, struct DecInputParameters* param,
                             struct DecUserConf* user_data_config);

/**
 * Provide external information to decoder. Used for some custom streams
 *        which do not contain all necessary information in the elementary bitstream.
 *        (mpeg4 specific).
 * \ingroup common_group
 * \param [in]     inst                A decoder instance created earlier with a call to VCDecInit.
 * \param [in]     width               Frame width in pixels.
 * \param [in]     height              Frame height in pixels.
 * \return         DecRet              value: DEC_OK, DEC_PARAM_ERROR.
 */
enum DecRet VCDecSetCustomInfo(void* inst, const u32 width, const u32 height);

/**
 * Retrieve the string of decoder return code.
 * \ingroup common_group
 * \param [in]    DecRet              Decoder return code.
 * \return        char *              Pointer to human readable string of return code.
 */
char *VCDecRetStr(enum DecRet rv);

#ifdef __cplusplus
}
#endif

#endif // VCDECAPI_H
