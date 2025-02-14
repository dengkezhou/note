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
#include "deccfg.h"
#include "parselogmsg.h"
#include "assert.h"
#define ASSERT(expr) assert(expr)
extern int num_pp;
extern int num_pp_bitmap;

#ifdef VCD_LOGMSG
#define DEC_RET_STR_CASE(rv) case (rv): return(#rv)
char* ParseDecPictureFormat(enum DecPictureFormat output_format) {
  switch (output_format) {
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_4X4); /**< \brief Tiled 4x4 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_8X4);  /**< \brief obsoleted */
  DEC_RET_STR_CASE(DEC_OUT_FRM_RASTER_SCAN); /**< \brief Raster scan format (semi-planar 4:2:0, 8 bit) */
  DEC_RET_STR_CASE(DEC_OUT_FRM_PLANAR_420);  /**< \brief Planar 4:2:0 format, 8 bit */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_8X8); /**< \brief Tiled 8x8 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_16X16); /**< \brief Tiled 16x16 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_16X16_P010); /**< \brief Tiled 16x16 P010 format, 10&12 bit */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_32X8_COMP);          /**< \brief compressed Tiled 16x16 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_32X8_P010_COMP);    /**< \brief compressed Tiled 16x16 P010 format, 10&12 bit */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_16X16_COMP);        /**< \brief compressed Tiled 16x16 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_TILED_16X16_P010_COMP);   /**< \brief compressed Tiled 16x16 P010 format, 10&12 bit */
  DEC_RET_STR_CASE(DEC_OUT_FRM_MONOCHROME);       /**< \brief YUV 4:0:0 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_RFC); /**< \brief Reference frame compression */

  /* DEC400 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_DEC400_400SP);   /**< \brief DEC400 output YUV400 semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_DEC400_420SP);   /**< \brief DEC400 output YUV420 semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_DEC400_400TILE); /**< \brief DEC400 output YUV400 tile4x4 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_DEC400_420TILE); /**< \brief DEC400 output YUV420 tile4x4 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_DEC400_400P);    /**< \brief DEC400 output YUV400 planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_DEC400_420P);    /**< \brief DEC400 output YUV420 planar */
  /* YUV420 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE);     /**< \brief YUV420, 8-bit, tile4x4 none rfc dpb output*/
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_PACK10);   /**< \brief YUV420, 10-bit, tile4x4 none rfc dpb output*/
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_PACK12);   /**< \brief YUV420, 12-bit, tile4x4 none rfc dpb output*/
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_P010); /**< \brief YUV420, 16-bit, valid 10 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_I010); /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_L010); /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_P012); /**< \brief YUV420, 16-bit, valid 12 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_I012); /**< \brief YUV420, 16-bit, valid 12 bits stored in LSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_128X2); /**< \brief YUV420, 8-bit, tile128x2 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420TILE_128X2_P010); /**< \brief YUV420, 16-bit, tile128x2, valid 10 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP);        /**< \brief YUV420, 8-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_PACK10); /**< \brief YUV420, 10-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_PACK12); /**< \brief YUV420, 12-bit, semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_P010);   /**< \brief YUV420, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_I010);   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_L010);   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_P012);   /**< \brief YUV420, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_I012);   /**< \brief YUV420, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420SP_1010);   /**< \brief YUV420, 3 pixels in 4 bytes (LSB->MSB), semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P);        /**< \brief YUV420, 8-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_PACK10); /**< \brief YUV420, 10-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_PACK12); /**< \brief YUV420, 12-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_P010);   /**< \brief YUV420, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_I010);   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_L010);   /**< \brief YUV420, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_P012);   /**< \brief YUV420, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_I012);   /**< \brief YUV420, 16-bit, valid 12 bits stored in LSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV420P_1010);   /**<\brief YUV420, 3 pixels in 4 bytes (LSB->MSB), planar */
   /* YUV400 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE);      /**< \brief YUV400, 8-bit, tile4x4 none rfc dpb output */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_PACK10); /**< \brief YUV400, 10-bit, tile4x4 none rfc dpb output */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_P010); /**< \brief YUV400, 16-bit, valid 10 bits stored in MSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_I010); /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_L010); /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, tile4x4, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_P012); /**< \brief YUV400, 16-bit, valid 12 bits stored in MSB, tile4x4, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_I012); /**< \brief YUV400, 16-bit, valid 12 bits stored in LSB, tile4x4, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400);          /**< \brief YUV400, 8-bit */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_PACK10);          /**< \brief YUV400, 10-bit */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_PACK12);          /**< \brief YUV400, 12-bit [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_P010);     /**< \brief YUV400, 16-bit, valid 10 bits stored in MSB, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_I010);     /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_L010);     /**< \brief YUV400, 16-bit, valid 10 bits stored in LSB, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_P012);     /**< \brief YUV400, 16-bit, valid 12 bits stored in MSB, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400_I012);     /**< \brief YUV400, 16-bit, valid 12 bits stored in LSB, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_128X2); /**< \brief YUV400, 8-bit, tile128x2 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV400TILE_128X2_P010); /**< \brief YUV400, 16-bit, tile128x2,  valid 10 bits stored in MSB, padding 0 in right */
  /* YUV422 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP);        /**< \brief YUV422, 8-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_PACK10); /**< \brief YUV422, 10-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_PACK12); /**< \brief YUV422, 12-bit, semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_P010);   /**< \brief YUV422, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_I010);   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_L010);   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_P012);   /**< \brief YUV422, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_I012);   /**< \brief YUV422, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422SP_1010);   /**< \brief YUV422, 3 pixels in 4 bytes (LSB->MSB), semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P);        /**< \brief YUV422, 8-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_PACK10); /**< \brief YUV422, 10-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_PACK12); /**< \brief YUV422, 12-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_P010);   /**< \brief YUV422, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_I010);   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_L010);   /**< \brief YUV422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_P012);   /**< \brief YUV422, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422P_I012);   /**< \brief YUV422, 16-bit, valid 12 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422_YUYV);    /**< \brief YUV422, 8-bit, YUYV */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV422_UYVY);    /**< \brief YUV422, 8-bit, UYVY */
  /* YUV440 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV440);          /**< \brief YUV440, 8-bit [Not support] */
  /* YUV411 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV411SP);        /**< \brief YUV411, 8-bit, semi-planar [Not support] */
  /* YUV444 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP);        /**< \brief YUV444, 8-bit, semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_PACK10); /**< \brief YUV444, 10-bit, semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_PACK12); /**< \brief YUV444, 12-bit, semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_P010);   /**< \brief YUV444, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_I010);   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_L010);   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_P012);   /**< \brief YUV444, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_I012);   /**< \brief YUV444, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444SP_1010);   /**< \brief YUV444, 3 pixels in 4 bytes (LSB->MSB), semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P);        /**< \brief YUV444, 8-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_PACK10); /**< \brief YUV444, 10-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_PACK12); /**< \brief YUV444, 12-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_P010);   /**< \brief YUV444, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_I010);   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_L010);   /**< \brief YUV444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_P012);   /**< \brief YUV444, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_YUV444P_I012);   /**< \brief YUV444, 16-bit, valid 12 bits stored in LSB, planar, padding 0 in right [Not support] */
  /* NV21 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE);        /**< \brief NV21, 8-bit, tile4x4 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE_PACK10); /**< \brief NV21, 10-bit, tile4x4 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE_P010); /**< \brief NV21, 16-bit, valid 10 bits stored in MSB, semi-planar, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE_I010); /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE_L010); /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, tile4x4, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE_P012); /**< \brief NV21, 16-bit, valid 12 bits stored in MSB, semi-planar, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21TILE_I012); /**< \brief NV21, 16-bit, valid 12 bits stored in LSB, semi-planar, tile4x4, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP);        /**< \brief NV21, 8-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_PACK10); /**< \brief NV21, 10-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_PACK12); /**< \brief NV21, 12-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_P010);   /**< \brief NV21, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_I010);   /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_L010);   /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_P012);   /**< \brief NV21, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_I012);   /**< \brief NV21, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21SP_1010);   /**< \brief NV21, semi-planar, 3 pixels in 4 bytes */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P);         /**< \brief NV21, 8-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_PACK10);  /**< \brief NV21, 10-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_PACK12);  /**< \brief NV21, 12-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_P010);    /**< \brief NV21, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_I010);    /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_L010);    /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_P012);    /**< \brief NV21, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_I012);    /**< \brief NV21, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_NV21P_1010);    /**< \brief NV21, planar, 3 pixels in 4 bytes */
  /* 422 NV21 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP);        /**< \brief NV21, 422, 8-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_PACK10); /**< \brief NV21, 422, 10-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_PACK12); /**< \brief NV21, 422, 12-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_P010);   /**< \brief NV21, 422, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_I010);   /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_L010);   /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_P012);   /**< \brief NV21, 422, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_I012);   /**< \brief NV21, 422, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21SP_1010);   /**< \brief NV21, 422, semi-planar, 3 pixels in 4 bytes */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P);         /**< \brief NV21, 422, 8-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_PACK10);  /**< \brief NV21, 422, 10-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_PACK12);  /**< \brief NV21, 422, 12-bit, planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_P010);    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_I010);    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_L010);    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_P012);    /**< \brief NV21, 422, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_422_NV21P_I012);    /**< \brief NV21, 422, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right [Not support] */
  /* 444 NV21 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP);        /**< \brief NV21, 444, 8-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_PACK10); /**< \brief NV21, 444, 10-bit, semi-planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_PACK12); /**< \brief NV21, 444, 12-bit, semi-planar [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_P010);   /**< \brief NV21, 444, 16-bit, valid 10 bits stored in MSB, semi-planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_I010);   /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_L010);   /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, semi-planar, padding 0 in left [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_P012);   /**< \brief NV21, 444, 16-bit, valid 12 bits stored in MSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21SP_I012);   /**< \brief NV21, 444, 16-bit, valid 12 bits stored in LSB, semi-planar, padding 0 in right [Not support] */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P);         /**< \brief NV21, 444, 8-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_PACK10);  /**< \brief NV21, 444, 10-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_PACK12);  /**< \brief NV21, 444, 12-bit, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_P010);    /**< \brief NV21, 444, 16-bit, valid 10 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_I010);    /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_L010);    /**<\brief NV21, 444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in left */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_P012);    /**< \brief NV21, 444, 16-bit, valid 12 bits stored in MSB, planar, padding 0 in right */
  DEC_RET_STR_CASE(DEC_OUT_FRM_444_NV21P_I012);    /**< \brief NV21, 444, 16-bit, valid 10 bits stored in LSB, planar, padding 0 in right */
  /* RGB */
  /* sw_ppx_out_rgb_fmt == 0 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_RGB888_P); /**< \brief RGB (First R, then G, and then B in buffer), 8-bit each component, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_BGR888); /**< \brief BGR (B in MSB, R in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 1 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_BGR888_P);  /**< \brief BGR (First B, then G, and then R in buffer), 8-bit each component, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_RGB888); /**< \brief RGB (R in MSB, B in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 2 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_R16G16B16_P); /**< \brief RGB (First R, then G, and then B in buffer), 16-bit each component, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_B16G16R16); /**< \brief BGR (B in MSB, R in LSB), 16-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 3 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_B16G16R16_P); /**< \brief BGR (First B, then G, and then R in buffer), 16-bit each component, planar */
  DEC_RET_STR_CASE(DEC_OUT_FRM_R16G16B16); /**< \brief RGB (R in MSB, B in LSB), 16-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 4 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_ABGR888); /**< \brief ABGR (A in MSB, R in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 5 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_ARGB888); /**< \brief ARGB (A in MSB, B in LSB), 8-bit each component, packed */
  /* sw_ppx_out_rgb_fmt == 6 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_A2B10G10R10); /**< \brief ABGR (A in MSB, R in LSB), packed */
  /* sw_ppx_out_rgb_fmt == 7 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_A2R10G10B10); /**< \brief ARGB (A in MSB, B in LSB), packed */
  /* sw_ppx_out_rgb_fmt == 8 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_XBGR888);  /**< \brief XBGR (X in MSB, R in LSB), X means undetermined, packed */
  /* sw_ppx_out_rgb_fmt == 9 */
  DEC_RET_STR_CASE(DEC_OUT_FRM_XRGB888); /**< \brief XRGB (X in MSB, B in LSB), X means undetermined, packed */
  DEC_RET_STR_CASE(DEC_OUT_FRM_BGRA888); /**< \brief ABGR (B in MSB, A in LSB), 8-bit each component, packed */
  DEC_RET_STR_CASE(DEC_OUT_FRM_RGBA888); /**< \brief ARGB (R in MSB, A in LSB), 8-bit each component, packed */
  DEC_RET_STR_CASE(DEC_OUT_FRM_B10G10R10A2); /**< \brief BGRA (B in MSB, A in LSB), packed */
  DEC_RET_STR_CASE(DEC_OUT_FRM_R10G10B10A2); /**< \brief RGBA (R in MSB, A in LSB), packed */
  /* super_tile */
  DEC_RET_STR_CASE(DEC_OUT_FRM_ABGR888_TILED64X64); /**< \brief ABGR stored in Tiled 64x64 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_ARGB888_TILED64X64); /**< \brief ARGB stored in Tiled 64x64 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_A2B10G10R10_TILED64X64); /**< \brief A2B10G10R10 stored in Tiled 64x64 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_A2R10G10B10_TILED64X64); /**< \brief A2R10G10B10 stored in Tiled 64x64 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_XBGR888_TILED64X64); /**< \brief XBGR stored in Tiled 64x64 format */
  DEC_RET_STR_CASE(DEC_OUT_FRM_XRGB888_TILED64X64); /**< \brief XRGB stored in Tiled 64x64 format */
  default: return("Unknown output format.\n");
  }
}

void ParseFeatureList(struct DecHwFeatures *cfg){
  CONFIGTRACE_I("Feature List# id: 0x%x\n",cfg->id);
  CONFIGTRACE_I("Feature List# id mask: 0x%x\n", cfg->id_mask);
  CONFIGTRACE_I("Feature List# hevc_support: %d\n", cfg->hevc_support);
  CONFIGTRACE_I("Feature List# hevc_main10_support: %d\n", cfg->hevc_main10_support);
  CONFIGTRACE_I("Feature List# hevc_422_intra_support: %d\n", cfg->hevc_422_intra_support);
  CONFIGTRACE_I("Feature List# vp9_support: %d\n", cfg->vp9_support);
  CONFIGTRACE_I("Feature List# vp9_profile2_support: %d\n", cfg->vp9_profile2_support);
  CONFIGTRACE_I("Feature List# h264_support: %d\n", cfg->h264_support);
  CONFIGTRACE_I("Feature List# h264_adv_support: %d\n", cfg->h264_adv_support);
  CONFIGTRACE_I("Feature List# h264_high10_support: %d\n", cfg->h264_high10_support);

  CONFIGTRACE_I("Feature List# h264_422_intra_support: %d\n", cfg->h264_422_intra_support);
  CONFIGTRACE_I("Feature List# mpeg4_support: %d\n", cfg->mpeg4_support);
  CONFIGTRACE_I("Feature List# custom_mpeg4_support: %d\n", cfg->custom_mpeg4_support);
  CONFIGTRACE_I("Feature List# mpeg2_support: %d\n", cfg->mpeg2_support);
  CONFIGTRACE_I("Feature List# sorenson_spark_support: %d\n", cfg->sorenson_spark_support);
  CONFIGTRACE_I("Feature List# vc1_support: %d\n", cfg->vc1_support);

  CONFIGTRACE_I("Feature List# jpeg_support: %d\n", cfg->jpeg_support);
  CONFIGTRACE_I("Feature List# rv_support: %d\n", cfg->rv_support);
  CONFIGTRACE_I("Feature List# vp8_support: %d\n", cfg->vp8_support);
  CONFIGTRACE_I("Feature List# webp_support: %d\n", cfg->webp_support);
  CONFIGTRACE_I("Feature List# vp7_support: %d\n", cfg->vp7_support);
  CONFIGTRACE_I("Feature List# vp6_support: %d\n", cfg->vp6_support);
  CONFIGTRACE_I("Feature List# avs_support: %d\n", cfg->avs_support);

  CONFIGTRACE_I("Feature List# avs_plus_support: %d\n", cfg->avs_plus_support);
  CONFIGTRACE_I("Feature List# avs2_support: %d\n", cfg->avs2_support);
  CONFIGTRACE_I("Feature List# avs2_main10_support: %d\n", cfg->avs2_main10_support);
  CONFIGTRACE_I("Feature List# av1_support: %d\n", cfg->av1_support);
  CONFIGTRACE_I("Feature List# av1_max_dec_pic_width: %d\n", cfg->av1_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# av1_max_dec_pic_height: %d\n", cfg->av1_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# hevc_max_dec_pic_width: %d\n", cfg->hevc_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# hevc_max_dec_pic_height: %d\n", cfg->hevc_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# vp9_max_dec_pic_width: %d\n", cfg->vp9_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# vp9_max_dec_pic_height: %d\n", cfg->vp9_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# h264_max_dec_pic_width: %d\n", cfg->h264_max_dec_pic_width);

  CONFIGTRACE_I("Feature List# h264_max_dec_pic_height: %d\n", cfg->h264_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# mpeg4_max_dec_pic_width: %d\n", cfg->mpeg4_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# mpeg4_max_dec_pic_height: %d\n", cfg->mpeg4_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# mpeg2_max_dec_pic_width: %d\n", cfg->mpeg2_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# mpeg2_max_dec_pic_height: %d\n", cfg->mpeg2_max_dec_pic_height);


  CONFIGTRACE_I("Feature List# sspark_max_dec_pic_width: %d\n", cfg->sspark_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# sspark_max_dec_pic_height: %d\n", cfg->sspark_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# vc1_max_dec_pic_width: %d\n", cfg->vc1_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# vc1_max_dec_pic_height: %d\n", cfg->vc1_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# rv_max_dec_pic_width: %d\n", cfg->rv_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# rv_max_dec_pic_height: %d\n", cfg->rv_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# vp8_max_dec_pic_width: %d\n", cfg->vp8_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# vp8_max_dec_pic_height: %d\n", cfg->vp8_max_dec_pic_height);

  CONFIGTRACE_I("Feature List# vp7_max_dec_pic_width: %d\n", cfg->vp7_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# vp7_max_dec_pic_height: %d\n", cfg->vp7_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# vp6_max_dec_pic_width: %d\n", cfg->vp6_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# avs_max_dec_pic_width: %d\n", cfg->avs_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# avs_max_dec_pic_height: %d\n", cfg->avs_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# divx_max_dec_pic_width: %d\n", cfg->divx_max_dec_pic_width);
  CONFIGTRACE_I("Feature List# divx_max_dec_pic_height: %d\n", cfg->divx_max_dec_pic_height);
  CONFIGTRACE_I("Feature List# img_max_dec_width: %d\n", cfg->img_max_dec_width);
  CONFIGTRACE_I("Feature List# img_max_dec_height: %d\n", cfg->img_max_dec_height);
  CONFIGTRACE_I("Feature List# addr64_support: %d\n", cfg->addr64_support);
  CONFIGTRACE_I("Feature List# rfc_support: %d\n", cfg->rfc_support);
  CONFIGTRACE_I("Feature List# qp_dump_support: %d\n", cfg->qp_dump_support);
  CONFIGTRACE_I("Feature List# low_latency_mode_support: %d\n", cfg->low_latency_mode_support);
  CONFIGTRACE_I("Feature List# partial_decoding_support: %d\n", cfg->partial_decoding_support);

  CONFIGTRACE_I("Feature List# max_ppu_count: %d\n", cfg->max_ppu_count);

  switch(cfg->pp_version) {
    case 0: CONFIGTRACE_I("Feature List# pp_version: %s\n", "NO_PP"); break;
    case 1: CONFIGTRACE_I("Feature List# pp_version: %s\n", "UNFIED_PP"); break;
    default:
      CONFIGTRACE_I("Feature List# pp_version: %s\n", "ILLEGAL_PP_VERISON"); break;

  }
  CONFIGTRACE_I("Feature List# crop_step_rshift: %d\n", cfg->crop_step_rshift);
  CONFIGTRACE_I("Feature List# pp_yuv420_101010_support: %d\n", cfg->pp_yuv420_101010_support);
  CONFIGTRACE_I("Feature List# pp_area_optimize: %d\n", cfg->pp_area_optimize);
  CONFIGTRACE_I("Feature List# fmt_p010_support: %d\n", cfg->fmt_p010_support);

  int i;
  char *pp, v[20];
  pp = (char *)malloc(20 * DEC_MAX_PPU_COUNT);
  if (pp == NULL) return;
  memset(pp,0,20 * DEC_MAX_PPU_COUNT);
  for (i = 0; i < num_pp - 1; i++){
    if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->max_pp_out_pic_width[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }
  }
  sprintf(v, "%d", cfg->max_pp_out_pic_width[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# max_pp_out_pic_width: {%s}\n", pp);
  free(pp);

  pp = (char *)malloc(4 * DEC_MAX_PPU_COUNT);
  if (pp == NULL) return;
  memset(pp,0,4 * DEC_MAX_PPU_COUNT);
  //printf("num_pp_bitmap=%d\n",num_pp_bitmap);
  for (i = 0; i < num_pp - 1; i++){
    if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->max_pp_out_pic_height[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }

  }
  sprintf(v, "%d", cfg->max_pp_out_pic_height[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# max_pp_out_pic_height: {%s}\n", pp);
  free(pp);

 pp = (char *)malloc(4 * DEC_MAX_PPU_COUNT);
 if (pp == NULL) return;
 memset(pp,0,4 * DEC_MAX_PPU_COUNT);
  for (i = 0; i < num_pp - 1; i++){
    if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->dscale_support[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }
  }
  sprintf(v, "%d", cfg->dscale_support[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# dscale_support: {%s}\n", pp);
  free(pp);

  pp = (char *)malloc(4 * DEC_MAX_PPU_COUNT);
  if (pp == NULL) return;
  memset(pp,0,4 * DEC_MAX_PPU_COUNT);
  for (i = 0; i < num_pp - 1; i++){
     if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->uscale_support[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }
  }
  sprintf(v, "%d", cfg->uscale_support[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# uscale_support: {%s}\n", pp);
  free(pp);

  pp = (char *)malloc(4 * DEC_MAX_PPU_COUNT);
  if (pp == NULL) return;
  memset(pp,0,4 * DEC_MAX_PPU_COUNT);
  for (i = 0; i < num_pp - 1; i++){
    if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->fmt_tile_support[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }
  }
  sprintf(v, "%d", cfg->fmt_tile_support[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# fmt_tile_support: {%s}\n", pp);
  free(pp);

  pp = (char *)malloc(4 * DEC_MAX_PPU_COUNT);
  if (pp == NULL) return;
  memset(pp,0,4 * DEC_MAX_PPU_COUNT);
  for (i = 0; i < num_pp - 1; i++){
    if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->fmt_rgb_support[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }
  }
  sprintf(v, "%d", cfg->fmt_rgb_support[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# fmt_rgb_support: {%s}\n", pp);
  free(pp);
  //printf("num_pp_bitmap=%d\n",num_pp_bitmap);
  pp = (char *)malloc(4 * DEC_MAX_PPU_COUNT);
  if (pp == NULL) return;
  memset(pp,0,4 * DEC_MAX_PPU_COUNT);
  for (i = 0; i < num_pp - 1; i++){
    if (num_pp_bitmap & (i+1)){
      sprintf(v, "%d, ", cfg->pp_planar_support[i]);
      strcat(pp, v);
    } else {
      sprintf(v, "%d, ", 0);
      strcat(pp, v);
    }
  }
  sprintf(v, "%d", cfg->pp_planar_support[i+1]);
  strcat(pp, v);
  CONFIGTRACE_I("Feature List# pp_planar_support: {%s}\n", pp);
  free(pp);

  switch(cfg->shaper_alignment){
    case ALIGN_1B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_1B"); break;
    case ALIGN_8B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_8B"); break;
    case ALIGN_16B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_16B"); break;
    case ALIGN_32B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_32B"); break;
    case ALIGN_64B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_64B"); break;
    case ALIGN_128B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_128B"); break;
    case ALIGN_256B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_256B"); break;
    case ALIGN_512B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_512B"); break;
    case ALIGN_1024B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_1024B"); break;
    case ALIGN_2048B:  CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ALIGN_2048B"); break;
    default:
      CONFIGTRACE_I("Feature List# shaper_alignment: %s\n", "ILLEGAL_ALIGNMENT"); break;
  }
}

char *ParseDecRet(enum DecRet rv) {
  switch (rv) {
  DEC_RET_STR_CASE(DEC_OK);
  DEC_RET_STR_CASE(DEC_STRM_PROCESSED);
  DEC_RET_STR_CASE(DEC_PIC_RDY);
  DEC_RET_STR_CASE(DEC_PIC_DECODED);
  DEC_RET_STR_CASE(DEC_HDRS_RDY);
  DEC_RET_STR_CASE(DEC_DP_HDRS_RDY);
  DEC_RET_STR_CASE(DEC_ADVANCED_TOOLS);
  DEC_RET_STR_CASE(DEC_SLICE_RDY);
  DEC_RET_STR_CASE(DEC_PENDING_FLUSH);
  DEC_RET_STR_CASE(DEC_NONREF_PIC_SKIPPED);
  DEC_RET_STR_CASE(DEC_END_OF_STREAM);
  DEC_RET_STR_CASE(DEC_END_OF_SEQ);
  DEC_RET_STR_CASE(DEC_WAITING_FOR_BUFFER);
  DEC_RET_STR_CASE(DEC_SCAN_PROCESSED);
  DEC_RET_STR_CASE(DEC_ABORTED);
  DEC_RET_STR_CASE(DEC_FLUSHED);
  DEC_RET_STR_CASE(DEC_BUF_EMPTY);
  DEC_RET_STR_CASE(DEC_RESOLUTION_CHANGED);
  DEC_RET_STR_CASE(DEC_VOS_END);
  DEC_RET_STR_CASE(DEC_PARAM_SET_PARSED);
  DEC_RET_STR_CASE(DEC_SEI_PARSED);
  DEC_RET_STR_CASE(DEC_PB_PIC_SKIPPED);
  DEC_RET_STR_CASE(DEC_PARAM_ERROR);
  DEC_RET_STR_CASE(DEC_STRM_ERROR);
  DEC_RET_STR_CASE(DEC_NOT_INITIALIZED);
  DEC_RET_STR_CASE(DEC_MEMFAIL);
  DEC_RET_STR_CASE(DEC_INITFAIL);
  DEC_RET_STR_CASE(DEC_HDRS_NOT_RDY);
  DEC_RET_STR_CASE(DEC_STREAM_NOT_SUPPORTED);
  DEC_RET_STR_CASE(DEC_EXT_BUFFER_REJECTED);
  DEC_RET_STR_CASE(DEC_INFOPARAM_ERROR);
  DEC_RET_STR_CASE(DEC_ERROR);
  DEC_RET_STR_CASE(DEC_UNSUPPORTED);
  DEC_RET_STR_CASE(DEC_INVALID_STREAM_LENGTH);
  DEC_RET_STR_CASE(DEC_INVALID_INPUT_BUFFER_SIZE);
  DEC_RET_STR_CASE(DEC_INCREASE_INPUT_BUFFER);
  DEC_RET_STR_CASE(DEC_SLICE_MODE_UNSUPPORTED);
  DEC_RET_STR_CASE(DEC_METADATA_FAIL);
  DEC_RET_STR_CASE(DEC_NO_REFERENCE);
  DEC_RET_STR_CASE(DEC_PARAM_SET_ERROR);
  DEC_RET_STR_CASE(DEC_SEI_ERROR);
  DEC_RET_STR_CASE(DEC_SLICE_HDR_ERROR);
  DEC_RET_STR_CASE(DEC_REF_PICS_ERROR);
  DEC_RET_STR_CASE(DEC_NALUNIT_ERROR);
  DEC_RET_STR_CASE(DEC_AU_BOUNDARY_ERROR);
  DEC_RET_STR_CASE(DEC_STREAM_ERROR_DEDECTED);
  DEC_RET_STR_CASE(DEC_NO_DECODING_BUFFER);
  DEC_RET_STR_CASE(DEC_HW_RESERVED);
  DEC_RET_STR_CASE(DEC_HW_TIMEOUT);
  DEC_RET_STR_CASE(DEC_HW_BUS_ERROR);
  DEC_RET_STR_CASE(DEC_SYSTEM_ERROR);
  DEC_RET_STR_CASE(DEC_DWL_ERROR);
  DEC_RET_STR_CASE(DEC_FATAL_SYSTEM_ERROR);
  DEC_RET_STR_CASE(DEC_HW_EXT_TIMEOUT);
  DEC_RET_STR_CASE(DEC_EVALUATION_LIMIT_EXCEEDED);
  DEC_RET_STR_CASE(DEC_FORMAT_NOT_SUPPORTED);
  default: return("Unknown return code.\n");
  }
}

char *ParseDWLMemType(int i){
  switch(i){
    case DWL_MEM_TYPE_CPU: return("DWL_MEM_TYPE_CPU");break;
    case DWL_MEM_TYPE_SLICE: return("DWL_MEM_TYPE_SLICE");break;
    case DWL_MEM_TYPE_DPB: return("DWL_MEM_TYPE_DPB");break;
    case DWL_MEM_TYPE_VPU_WORKING: return("DWL_MEM_TYPE_VPU_WORKING");break;
    case DWL_MEM_TYPE_VPU_WORKING_SPECIAL: return("DWL_MEM_TYPE_VPU_WORKING_SPECIAL");break;
    case DWL_MEM_TYPE_VPU_ONLY: return("DWL_MEM_TYPE_VPU_ONLY");break;
    case DWL_MEM_TYPE_VPU_CPU: return("DWL_MEM_TYPE_VPU_CPU");break;
    case DWL_MEM_TYPE_DMA_DEVICE_ONLY: return("DWL_MEM_TYPE_DMA_DEVICE_ONLY");break;
    case DWL_MEM_TYPE_DMA_HOST_TO_DEVICE: return("DWL_MEM_TYPE_DMA_HOST_TO_DEVICE");break;
    case DWL_MEM_TYPE_DMA_DEVICE_TO_HOST: return("DWL_MEM_TYPE_DMA_DEVICE_TO_HOST");break;
    case DWL_MEM_TYPE_DMA_HOST_AND_DEVICE: return("DWL_MEM_TYPE_DMA_HOST_AND_DEVICE");break;
    default:return("INVALID DWL_MEM_TYPE");
  }
}

void ParseDecInitConfig(struct DecInitConfig *cfg){
  switch(cfg->codec){
    case DEC_MPEG4: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_MPEG4");break;
    case DEC_MPEG2: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_MPEG2");break;
    case DEC_VP6: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_VP6");break;
    case DEC_VP8: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_VP8");break;
    case DEC_VP9: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_VP9");break;
    case DEC_HEVC: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_HEVC");break;
    case DEC_H264: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_H264");break;
    case DEC_AVS: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_AVS");break;
    case DEC_AVS2: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_AVS2");break;
    case DEC_AV1: APITRACEDEBUG("DecInitConfig# Codec: %s\n","DEC_AV1");break;
    case DEC_JPEG: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_JPEG");break;
    case DEC_VC1: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_VC1");break;
    case DEC_RV: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_RV");break;
    case DEC_VVC: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_VVC");break;
    case DEC_PPDEC: APITRACEDEBUG("DecInitConfig# Codec: %s\n", "DEC_PPDEC");break;
    default:
      ASSERT(0);
      break;
  }
  APITRACEDEBUG("DecInitConfig# Disable pic reodering: %d\n", cfg->disable_picture_reordering);
  APITRACEDEBUG("DecInitConfig# Error handling: %d\n", cfg->error_handling);
  APITRACEDEBUG("DecInitConfig# Use video compressor: %d\n", cfg->use_video_compressor);
  APITRACEDEBUG("DecInitConfig# Full stream mode: %d\n", cfg->multi_frame_input_flag);
  APITRACEDEBUG("DecInitConfig# Full Guard size: %d\n", cfg->guard_size);
  APITRACEDEBUG("DecInitConfig# Use adaptive buffers: %d\n", cfg->use_adaptive_buffers);
  APITRACEDEBUG("DecInitConfig# Num frame buffers: %d\n", cfg->num_frame_buffers);
  APITRACEDEBUG("DecInitConfig# RLC mode: %d\n", cfg->rlc_mode);

  switch(cfg->error_handling){
    case DEC_EC_FRAME_TOLERANT_ERROR: APITRACEDEBUG("DecInitConfig# Error Handling mode: %s\n", "DEC_EC_FRAME_TOLERANT_ERROR");break;
    case DEC_EC_FRAME_IGNORE_ERROR: APITRACEDEBUG("DecInitConfig# Error Handling mode: %s\n", "DEC_EC_FRAME_IGNORE_ERROR");break;
    case DEC_EC_FRAME_NO_ERROR: APITRACEDEBUG("DecInitConfig# Error Handling mode: %s\n", "DEC_EC_FRAME_NO_ERROR");break;
    default:
       APITRACEDEBUG("DecInitConfig# Error Handling mode: %s\n", "ILLEGAL ERROR HANDLING MODE");
      //ASSERT(0);
      break;
  }

  APITRACEDEBUG("DecInitConfig# MAX num pics to decode: %d\n", cfg->max_num_pics_to_decode);
  APITRACEDEBUG("DecInitConfig# MC CFG# MC enabled: %d\n", cfg->mc_cfg.mc_enable);

  switch(cfg->skip_frame){
    case DEC_SKIP_NON_REF_RECON:APITRACEDEBUG("DecInitConfig# Skip frame mode: %s\n", "DEC_SKIP_NON_REF_RECON");break;
    case DEC_SKIP_NON_REF:APITRACEDEBUG("DecInitConfig# Skip frame mode: %s\n", "DEC_SKIP_NON_REF");break;
    case DEC_SKIP_NONE:APITRACEDEBUG("DecInitConfig# Skip frame mode: %s\n", "DEC_SKIP_NONE");break;
    default:
      ASSERT(0);
      break;
  }
  APITRACEDEBUG("DecInitConfig# Auxinfo: %d\n",cfg->auxinfo);

  switch(cfg->dec_format){
    case DEC_INPUT_VP7:APITRACEDEBUG("DecInitConfig# Dec input format: %s\n", "DEC_INPUT_VP7");break;
    case DEC_INPUT_VP8:APITRACEDEBUG("DecInitConfig# Dec input format: %s\n", "DEC_INPUT_VP8");break;
    case DEC_INPUT_WEBP:APITRACEDEBUG("DecInitConfig# Dec input format: %s\n", "DEC_INPUT_WEBP");break;
    case DEC_INPUT_MPEG4:APITRACEDEBUG("DecInitConfig# Dec input format: %s\n", "DEC_INPUT_MPEG4");break;
    case DEC_INPUT_SORENSON:APITRACEDEBUG("DecInitConfig# Dec input format: %s\n", "DEC_INPUT_SORENSON");break;
    case DEC_INPUT_CUSTOM_1:APITRACEDEBUG("DecInitConfig# Dec input format: %s\n", "DEC_INPUT_CUSTOM_1");break;
    default:
      APITRACEDEBUG("DecInitConfig# Dec input format: %d\n", cfg->dec_format);
      break;
  }
  APITRACEDEBUG("DecInitConfig# Frame code length: %d\n",cfg->frame_code_length);
  APITRACEDEBUG("DecInitConfig# RV version: %d\n",cfg->rv_version);
  APITRACEDEBUG("DecInitConfig# MAX frame width: %d\n",cfg->max_frame_width);
  APITRACEDEBUG("DecInitConfig# MAX frame height: %d\n",cfg->max_frame_height);

  APITRACEDEBUG("DecInitConfig# META DATA# MAX coded width : %d\n",cfg->meta_data.max_coded_width);
  APITRACEDEBUG("DecInitConfig# META DATA# MAX coded height : %d\n",cfg->meta_data.max_coded_height);
  APITRACEDEBUG("DecInitConfig# META DATA# VS transform : %d\n",cfg->meta_data.vs_transform);
  APITRACEDEBUG("DecInitConfig# META DATA# Overlap : %d\n",cfg->meta_data.overlap);
  APITRACEDEBUG("DecInitConfig# META DATA# Sync marker : %d\n",cfg->meta_data.sync_marker);
  APITRACEDEBUG("DecInitConfig# META DATA# Quantizer : %d\n",cfg->meta_data.quantizer);
  APITRACEDEBUG("DecInitConfig# META DATA# Frame interpolation : %d\n",cfg->meta_data.frame_interp);
  APITRACEDEBUG("DecInitConfig# META DATA# MAX consecutive b-frames  : %d\n",cfg->meta_data.max_bframes);
  APITRACEDEBUG("DecInitConfig# META DATA# Fast uv mc  : %d\n",cfg->meta_data.fast_uv_mc);
  APITRACEDEBUG("DecInitConfig# META DATA# Extended mv  : %d\n",cfg->meta_data.extended_mv);
  APITRACEDEBUG("DecInitConfig# META DATA# Multi res: %d\n",cfg->meta_data.multi_res);
  APITRACEDEBUG("DecInitConfig# META DATA# Range reduction: %d\n",cfg->meta_data.range_red);
  APITRACEDEBUG("DecInitConfig# META DATA# Dquant: %d\n",cfg->meta_data.dquant);
  APITRACEDEBUG("DecInitConfig# META DATA# Loop filter: %d\n",cfg->meta_data.loop_filter);
  APITRACEDEBUG("DecInitConfig# META DATA# Profile: %d\n",cfg->meta_data.profile);

  APITRACEDEBUG("DecInitConfig# Disable clock gating: %d\n",cfg->disable_clock_gating);
  APITRACEDEBUG("DecInitConfig# Enable dram throttle: %d\n",cfg->enable_dram_throttle);
  APITRACEDEBUG("DecInitConfig# Annexb: %d\n",cfg->annexb);
  APITRACEDEBUG("DecInitConfig# Plainobu: %d\n",cfg->plainobu);
  APITRACEDEBUG("DecInitConfig# Multi core poll period: %d\n",cfg->multicore_poll_period);
  APITRACEDEBUG("DecInitConfig# Tile transpose: %d\n",cfg->tile_transpose);
  APITRACEDEBUG("DecInitConfig# Oppoints: %d\n",cfg->oppoints);
}

void ParseDecSequenceInfo(struct DecSequenceInfo *seq)
{
  APITRACEDEBUG("DecSequenceInfo# VP version: %d\n",seq->vp_version);
  APITRACEDEBUG("DecSequenceInfo# VP profile: %d\n",seq->vp_profile);
  APITRACEDEBUG("DecSequenceInfo# PIC width: %d\n",seq->pic_width);
  APITRACEDEBUG("DecSequenceInfo# PIC height: %d\n",seq->pic_height);
  APITRACEDEBUG("DecSequenceInfo# Scaled width: %d\n",seq->scaled_width);
  APITRACEDEBUG("DecSequenceInfo# Scaled height: %d\n",seq->scaled_height);
  APITRACEDEBUG("DecSequenceInfo# Pic width thumb: %d\n",seq->pic_width_thumb);
  APITRACEDEBUG("DecSequenceInfo# Pic height thumb: %d\n",seq->pic_height_thumb);
  APITRACEDEBUG("DecSequenceInfo# Scaled width thumb: %d\n",seq->scaled_width_thumb);
  APITRACEDEBUG("DecSequenceInfo# Sar width: %d\n",seq->sar_width);
  APITRACEDEBUG("DecSequenceInfo# Sar height: %d\n",seq->sar_height);

  APITRACEDEBUG("DecSequenceInfo# Crop left offset# : %d\n",seq->crop_params.crop_left_offset);
  APITRACEDEBUG("DecSequenceInfo# Crop top offset# : %d\n",seq->crop_params.crop_top_offset);
  APITRACEDEBUG("DecSequenceInfo# Crop out width# : %d\n",seq->crop_params.crop_out_width);

  switch(seq->video_range){
    case DEC_VIDEO_RANGE_NORMAL: APITRACEDEBUG("DecSequenceInfo# Video range: %s\n","DEC_VIDEO_RANGE_NORMAL(DEC_VIDEO_STUDIO_SWING)");break;
    case DEC_VIDEO_RANGE_FULL: APITRACEDEBUG("DecSequenceInfo# Video range: %s\n","DEC_VIDEO_RANGE_FULL(DEC_VIDEO_FULL_SWING)");break;
    default:
      //ASSERT(0);
      APITRACEDEBUG("DecSequenceInfo# Video range: %d\n",seq->video_range);
      break;
  }
  APITRACEDEBUG("DecSequenceInfo# Matric coefficients: %d\n",seq->matrix_coefficients);
  APITRACEDEBUG("DecSequenceInfo# Is mono chrome: %d\n",seq->is_mono_chrome);
  APITRACEDEBUG("DecSequenceInfo# Is interlaced: %d\n",seq->is_interlaced);
  APITRACEDEBUG("DecSequenceInfo# Num of ref frames: %d\n",seq->num_of_ref_frames);
  switch(seq->chroma_format_idc){
    case 0:  APITRACEDEBUG("DecSequenceInfo# Chroma format idc: %s\n","mono chrome");break;
    case 1:  APITRACEDEBUG("DecSequenceInfo# Chroma format idc: %s\n","yuv420");break;
    case 2:  APITRACEDEBUG("DecSequenceInfo# Chroma format idc: %s\n","yuv422");break;
    case 3:  APITRACEDEBUG("DecSequenceInfo# Chroma format idc: %s\n","yuv444");break;
    default:
      ASSERT(0);
      break;
  }

  APITRACEDEBUG("DecSequenceInfo# Bit depth luma: %d\n",seq->bit_depth_luma);
  APITRACEDEBUG("DecSequenceInfo# Bit depth chroma: %d\n",seq->bit_depth_chroma);
  if (seq->dpb_mode == 0)
    APITRACEDEBUG("DecSequenceInfo# DPB mode: %s\n","DEC_DPB_FRAME");
  if (seq->dpb_mode == 1)
    APITRACEDEBUG("DecSequenceInfo# DPB mode: %s\n","DEC_DPB_INTERLACED_FIELD");

  APITRACEDEBUG("DecSequenceInfo# Output format: %s\n",ParseDecPictureFormat(seq->output_format));
  APITRACEDEBUG("DecSequenceInfo# Output format thumb: %s\n",ParseDecPictureFormat(seq->output_format_thumb));
  switch(seq->coding_mode){
    case JPEG_NOT_SUPPORTED: APITRACEDEBUG("DecSequenceInfo# Jpeg code type: %s\n","JPEG_NOT_SUPPORTED"); break;
    case JPEG_BASELINE: APITRACEDEBUG("DecSequenceInfo# Jpeg code type: %s\n","JPEG_BASELINE"); break;
    case JPEG_PROGRESSIVE: APITRACEDEBUG("DecSequenceInfo# Jpeg code type: %s\n","JPEG_PROGRESSIVE"); break;
    case JPEG_EXTENDED: APITRACEDEBUG("DecSequenceInfo# Jpeg code type: %s\n","JPEG_EXTENDED"); break;
    case JPEG_NONINTERLEAVED: APITRACEDEBUG("DecSequenceInfo# Jpeg code type: %s\n","JPEG_NONINTERLEAVED"); break;
    default:
      ASSERT(0);
      break;
  }

  switch(seq->coding_mode_thumb){
    case JPEG_NOT_SUPPORTED: APITRACEDEBUG("DecSequenceInfo# Jpeg code type in thumbnail: %s\n","JPEG_NOT_SUPPORTED"); break;
    case JPEG_BASELINE: APITRACEDEBUG("DecSequenceInfo# Jpeg code type in thumbnail: %s\n","JPEG_BASELINE"); break;
    case JPEG_PROGRESSIVE: APITRACEDEBUG("DecSequenceInfo# Jpeg code type in thumbnail: %s\n","JPEG_PROGRESSIVE"); break;
    case JPEG_EXTENDED: APITRACEDEBUG("DecSequenceInfo# Jpeg code type in thumbnail: %s\n","JPEG_EXTENDED"); break;
    case JPEG_NONINTERLEAVED: APITRACEDEBUG("DecSequenceInfo# Jpeg code type in thumbnail: %s\n","JPEG_NONINTERLEAVED"); break;
    default:
      ASSERT(0);
      break;
  }
  switch(seq->thumbnail_type){
    case JPEGDEC_THUMBNAIL_JPEG: APITRACEDEBUG("DecSequenceInfo# Thumbnail type: %s\n","JPEGDEC_THUMBNAIL_JPEG"); break;
    case JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT: APITRACEDEBUG("DecSequenceInfo# Thumbnail type: %s\n","JPEGDEC_THUMBNAIL_NOT_SUPPORTED_FORMAT"); break;
    case JPEGDEC_NO_THUMBNAIL: APITRACEDEBUG("DecSequenceInfo# Thumbnail type: %s\n","JPEGDEC_NO_THUMBNAIL"); break;
    default:
      APITRACEDEBUG("DecSequenceInfo# Thumbnail type: %s\n","INVALID_THUMBNAIL_TYPE"); break;
  }
  APITRACEDEBUG("DecSequenceInfo# PP enabled: %d\n",seq->pp_enabled);
  APITRACEDEBUG("DecSequenceInfo# H264 base mode: %d\n",seq->h264_base_mode);
  APITRACEDEBUG("DecSequenceInfo# Frame rate numerator: %d\n",seq->frame_rate_numerator);
  APITRACEDEBUG("DecSequenceInfo# Frame rate denominator: %d\n",seq->frame_rate_denominator);
  APITRACEDEBUG("DecSequenceInfo# Buf release flag: %d\n",seq->buf_release_flag);

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Pic id: %d\n",seq->jpeg_input_info.pic_id);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream len: %d\n",seq->jpeg_input_info.strm_len);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream bus address: 0x%x\n",seq->jpeg_input_info.stream_bus_address);

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream Buffer# Virtual address: 0x%x\n",seq->jpeg_input_info.stream_buffer.virtual_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream Buffer# Bus address: 0x%x\n",seq->jpeg_input_info.stream_buffer.bus_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream Buffer# Size: %d\n",seq->jpeg_input_info.stream_buffer.size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream Buffer# Logical Size: %d\n",seq->jpeg_input_info.stream_buffer.logical_size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Stream Buffer# Mem type: %s\n",ParseDWLMemType(seq->jpeg_input_info.stream_buffer.mem_type));

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Buffer size: %d\n",seq->jpeg_input_info.buffer_size);

  switch(seq->jpeg_input_info.dec_image_type){
    case JPEGDEC_IMAGE: APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Dec iamge type: %s\n","JPEGDEC_IMAGE");break;
    case JPEGDEC_THUMBNAIL: APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Dec image type: %s\n","JPEGDEC_THUMBNAIL");break;
    default:
      APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Dec image type: %s\n","INVALID_DEC_IMAGE_TYPE");break;
  }
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Slice mb set: %d\n",seq->jpeg_input_info.slice_mb_set);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Count of restart interval: %d\n",seq->jpeg_input_info.ri_count);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Low latency: %d\n",seq->jpeg_input_info.low_latency);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Frame len: %d\n",seq->jpeg_input_info.frame_len);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Pic decoded: %d\n",seq->jpeg_input_info.pic_decoded);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Exit send thread: %d\n",seq->jpeg_input_info.exit_send_thread);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Slice height: %d\n",seq->jpeg_input_info.slice_height);
  switch(seq->jpeg_input_info.skip_frame){
    case DEC_SKIP_NON_REF_RECON:APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Skip frame mode: %s\n", "DEC_SKIP_NON_REF_RECON");break;
    case DEC_SKIP_NON_REF:APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Skip frame mode: %s\n", "DEC_SKIP_NON_REF");break;
    case DEC_SKIP_NONE:APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Skip frame mode: %s\n", "DEC_SKIP_NONE");break;
    default:
      ASSERT(0);
      break;
  }

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# SEI Buffer: Bit mask: 0x%x\n",seq->jpeg_input_info.sei_buffer->bitmask);
  //APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# SEI Buffer: Total size: 0x%x\n",seq->jpeg_input_info.sei_buffer->total_size); //core dumped
  //APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# SEI Buffer: Avaliable size: 0x%x\n",seq->jpeg_input_info.sei_buffer->available_size); //core dumped

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Enable deblock: 0x%x\n",seq->jpeg_input_info.enable_deblock);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# P pic buffer y: 0x%x\n",seq->jpeg_input_info.p_pic_buffer_y);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# P pic buffer c: 0x%x\n",seq->jpeg_input_info.p_pic_buffer_c);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# The bus address for luminance output: 0x%x\n",seq->jpeg_input_info.pic_buffer_bus_address_c);

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer y# Virtual address: 0x%x\n",seq->jpeg_input_info.picture_buffer_y.virtual_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer y# Bus address: 0x%x\n",seq->jpeg_input_info.picture_buffer_y.bus_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer y# Size: %d\n",seq->jpeg_input_info.picture_buffer_y.size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer y# Logical size: %d\n",seq->jpeg_input_info.picture_buffer_y.logical_size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer y# Mem type: %s\n",ParseDWLMemType(seq->jpeg_input_info.picture_buffer_y.mem_type));

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cb Cr# Virtual address: 0x%x\n",seq->jpeg_input_info.picture_buffer_cb_cr.virtual_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cb Cr# Bus address: 0x%x\n",seq->jpeg_input_info.picture_buffer_cb_cr.bus_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cb Cr# Size: %d\n",seq->jpeg_input_info.picture_buffer_cb_cr.size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cb Cr# Logical size: %d\n",seq->jpeg_input_info.picture_buffer_cb_cr.logical_size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cb Cr# Mem type: %s\n",ParseDWLMemType(seq->jpeg_input_info.picture_buffer_cb_cr.mem_type));

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cr# Virtual address: 0x%x\n",seq->jpeg_input_info.picture_buffer_cr.virtual_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cr# Bus address: 0x%x\n",seq->jpeg_input_info.picture_buffer_cr.bus_address);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cr# Size: %d\n",seq->jpeg_input_info.picture_buffer_cr.size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cr# Logical size: %d\n",seq->jpeg_input_info.picture_buffer_cr.logical_size);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Picture Buffer Cr# Mem type: %s\n",ParseDWLMemType(seq->jpeg_input_info.picture_buffer_cr.mem_type));

  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Time stamp: %d\n",seq->jpeg_input_info.timestamp);
  APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# Slice info num: %d\n",seq->jpeg_input_info.slice_info_num);

  //APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# DecSliceInfo# Slice info: %p\n",seq->jpeg_input_info.slice_info);
  //APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# DecSliceInfo# Is valid: %d\n",seq->jpeg_input_info.slice_info->is_valid);

  APITRACEDEBUG("DecSequenceInfo# Image max decode width: %d\n",seq->img_max_dec_width);
  APITRACEDEBUG("DecSequenceInfo# Image max decode height: %d\n",seq->img_max_dec_height);
  APITRACEDEBUG("DecSequenceInfo# Profile id: %d\n",seq->profile_id);
  APITRACEDEBUG("DecSequenceInfo# Level id: %d\n",seq->level_id);
  APITRACEDEBUG("DecSequenceInfo# Profile and level indication: %d\n",seq->profile_and_level_indication);
  APITRACEDEBUG("DecSequenceInfo# Display aspect ratio: %d\n",seq->display_aspect_ratio);
  APITRACEDEBUG("DecSequenceInfo# Stream format: %d\n",seq->stream_format);
  APITRACEDEBUG("DecSequenceInfo# Video format: %d\n",seq->video_format);
  APITRACEDEBUG("DecSequenceInfo# Colour primaries: %d\n",seq->colour_primaries);
  APITRACEDEBUG("DecSequenceInfo# Transfer characteristics: %d\n",seq->transfer_characteristics);
  APITRACEDEBUG("DecSequenceInfo# Colour description present flag: %d\n",seq->colour_description_present_flag);
  APITRACEDEBUG("DecSequenceInfo# Multi buff pp size: %d\n",seq->multi_buff_pp_size);
  APITRACEDEBUG("DecSequenceInfo# User data voslen: %d\n",seq->user_data_voslen);
  APITRACEDEBUG("DecSequenceInfo# User data visolen: %d\n",seq->user_data_visolen);
  APITRACEDEBUG("DecSequenceInfo# User data vollen: %d\n",seq->user_data_vollen);
  APITRACEDEBUG("DecSequenceInfo# User data govlen: %d\n",seq->user_data_govlen);
  APITRACEDEBUG("DecSequenceInfo# Gmc support: %d\n",seq->gmc_support);
  APITRACEDEBUG("DecSequenceInfo# Out picture code width: %d\n",seq->out_pic_coded_width);
  APITRACEDEBUG("DecSequenceInfo# Out picture code height: %d\n",seq->out_pic_coded_height);
  APITRACEDEBUG("DecSequenceInfo# Out picture state: %s\n",ParseDecRet(seq->out_pic_stat));
}

char* ParseDecPicAlignment(int i){
  switch(i){
    case DEC_ALIGN_1B: return("DEC_ALIGN_1B"); break;
    case DEC_ALIGN_8B: return("DEC_ALIGN_8B"); break;
    case DEC_ALIGN_16B: return("DEC_ALIGN_16B"); break;
    case DEC_ALIGN_32B: return("DEC_ALIGN_32B"); break;
    case DEC_ALIGN_64B: return("DEC_ALIGN_64B"); break;
    case DEC_ALIGN_128B: return("DEC_ALIGN_128B"); break;
    case DEC_ALIGN_256B: return("DEC_ALIGN_256B"); break;
    case DEC_ALIGN_512B: return("DEC_ALIGN_512B"); break;
    case DEC_ALIGN_1024B: return("DEC_ALIGN_1024B"); break;
    case DEC_ALIGN_2048B: return("DEC_ALIGN_2048B"); break;
    default:
      return("ILLEGAL_ALIGNMENT"); break;
  }
}

void ParseDecConfig(struct DecConfig *config){
 //ppu_cfg has been alreadly parsed in CheckPpunitConfig
 int i;
  for(i =0; i < 2; i++){
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# Enabled: %d\n",i, config->delogo_params->enabled);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# x: %d\n",i, config->delogo_params->x);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# y: %d\n",i, config->delogo_params->y);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# width: %d\n",i, config->delogo_params->w);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# height: %d\n",i, config->delogo_params->h);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# delogo filter level: %d\n",i, config->delogo_params->show);
    switch(config->delogo_params->mode){
      case PIXEL_NO_DELOGO: APITRACEDEBUG("DecConfig# DELOGO Params [%d]# Mode: %s\n",i, "PIXEL_NO_DELOGO"); break;
      case PIXEL_REPLACE: APITRACEDEBUG("DecConfig# DELOGO Params [%d]# Mode: %s\n",i, "PIXEL_REPLACE"); break;
      case PIXEL_INTERPOLATION: APITRACEDEBUG("DecConfig# DELOGO Params [%d]# Mode: %s\n",i, "PIXEL_INTERPOLATION"); break;
      default:
        APITRACEDEBUG("DecConfig# DELOGO Params [%d]# Mode: %s\n",i, "ILLEGAL_DELOGO_MODE"); break;

      }
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# Y: %d\n",i, config->delogo_params->Y);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# U: %d\n",i, config->delogo_params->U);
    APITRACEDEBUG("DecConfig# DELOGO Params [%d]# V: %d\n",i, config->delogo_params->V);
 }
  APITRACEDEBUG("DecConfig# Align: %s\n", ParseDecPicAlignment(config->align));
  //APITRACEDEBUG("DecConfig# HW conceal: %d\n", config->hw_conceal);
  //APITRACEDEBUG("DecConfig# Disable slice: %d\n", config->disable_slice);
  APITRACEDEBUG("DecConfig# Disable slice: %d\n", config->disable_slice);

  switch(config->dec_image_type){
    case JPEGDEC_IMAGE: APITRACEDEBUG("DecConfig# Dec iamge type: %s\n","JPEGDEC_IMAGE");break;
    case JPEGDEC_THUMBNAIL: APITRACEDEBUG("DecConfig# Dec image type: %s\n","JPEGDEC_THUMBNAIL");break;
    default:
      APITRACEDEBUG("DecConfig# Dec image type: %s\n","INVALID_DEC_IMAGE_TYPE");break;
  }
  switch(config->chroma_format){
    case 0: APITRACEDEBUG("DecConfig# Chroma format: %s\n","YUV400");break;
    case 1: APITRACEDEBUG("DecConfig# Chroma format: %s\n","YUV420");break;
    case 2: APITRACEDEBUG("DecConfig# Chroma format: %s\n","YUV422");break;
    case 3: APITRACEDEBUG("DecConfig# Chroma format: %s\n","YUV444");break;
    default:
      APITRACEDEBUG("DecConfig# Chroma format: %s\n","ILLEGAL_CHROMA_FORMAT");break;
  }

}

void ParseDecInputParameters(struct DecInputParameters* param){
  APITRACEDEBUG("DecInputParameters# Pic id: %d\n",param->pic_id);
  APITRACEDEBUG("DecInputParameters# Stream len: %d\n",param->strm_len);
  APITRACEDEBUG("DecInputParameters# Stream bus address: 0x%x\n",param->stream_bus_address);

  APITRACEDEBUG("DecInputParameters# Stream Buffer# Virtual address: 0x%x\n",param->stream_buffer.virtual_address);
  APITRACEDEBUG("DecInputParameters# Stream Buffer# Bus address: 0x%x\n",param->stream_buffer.bus_address);
  APITRACEDEBUG("DecInputParameters# Stream Buffer# Size: %d\n",param->stream_buffer.size);
  APITRACEDEBUG("DecInputParameters# Stream Buffer# Logical Size: %d\n",param->stream_buffer.logical_size);
  APITRACEDEBUG("DecInputParameters# Stream Buffer# Mem type: %s\n",ParseDWLMemType(param->stream_buffer.mem_type));

  APITRACEDEBUG("DecInputParameters# Buffer size: %d\n",param->buffer_size);

  switch(param->dec_image_type){
    case JPEGDEC_IMAGE: APITRACEDEBUG("DecInputParameters# Dec iamge type: %s\n","JPEGDEC_IMAGE");break;
    case JPEGDEC_THUMBNAIL: APITRACEDEBUG("DecInputParameters# JDec image type: %s\n","JPEGDEC_THUMBNAIL");break;
    default:
      APITRACEDEBUG("DecInputParameters# Dec image type: %s\n","INVALID_DEC_IMAGE_TYPE");break;
  }
  APITRACEDEBUG("DecInputParameters# Slice mb set: %d\n",param->slice_mb_set);
  APITRACEDEBUG("DecInputParameters# Count of restart interval: %d\n",param->ri_count);
  APITRACEDEBUG("DecInputParameters# Low latency: %d\n",param->low_latency);
  APITRACEDEBUG("DecInputParameters# Frame len: %d\n",param->frame_len);
  APITRACEDEBUG("DecInputParameters# Pic decoded: %d\n",param->pic_decoded);
  APITRACEDEBUG("DecInputParameters# Exit send thread: %d\n",param->exit_send_thread);
  APITRACEDEBUG("DecInputParameters# Slice height: %d\n",param->slice_height);
  switch(param->skip_frame){
    case DEC_SKIP_NON_REF_RECON:APITRACEDEBUG("DecInputParameters# Skip frame mode: %s\n", "DEC_SKIP_NON_REF_RECON");break;
    case DEC_SKIP_NON_REF:APITRACEDEBUG("DecInputParameters# Skip frame mode: %s\n", "DEC_SKIP_NON_REF");break;
    case DEC_SKIP_NONE:APITRACEDEBUG("DecInputParameters# Skip frame mode: %s\n", "DEC_SKIP_NONE");break;
    default:
      ASSERT(0);
      break;
  }

  APITRACEDEBUG("DecInputParameters# SEI Buffer: Bit mask: 0x%x\n",param->sei_buffer->bitmask);
  //APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# SEI Buffer: Total size: 0x%x\n",seq->jpeg_input_info.sei_buffer->total_size); //core dumped
  //APITRACEDEBUG("DecSequenceInfo# JPEG Input Info# SEI Buffer: Avaliable size: 0x%x\n",seq->jpeg_input_info.sei_buffer->available_size); //core dumped

  APITRACEDEBUG("DecInputParameters# Enable deblock: 0x%x\n",param->enable_deblock);
  APITRACEDEBUG("DecInputParameters# P pic buffer y: 0x%x\n",param->p_pic_buffer_y);
  APITRACEDEBUG("DecInputParameters# P pic buffer c: 0x%x\n",param->p_pic_buffer_c);
  APITRACEDEBUG("DecInputParameters# The bus address for luminance output: 0x%x\n",param->pic_buffer_bus_address_c);

  APITRACEDEBUG("DecInputParameters# Picture Buffer y# Virtual address: 0x%x\n",param->picture_buffer_y.virtual_address);
  APITRACEDEBUG("DecInputParameters# Picture Buffer y# Bus address: 0x%x\n",param->picture_buffer_y.bus_address);
  APITRACEDEBUG("DecInputParameters# Picture Buffer y# Size: %d\n",param->picture_buffer_y.size);
  APITRACEDEBUG("DecInputParameters# Picture Buffer y# Logical size: %d\n",param->picture_buffer_y.logical_size);
  APITRACEDEBUG("DecInputParameters# Picture Buffer y# Mem type: %s\n",ParseDWLMemType(param->picture_buffer_y.mem_type));

  APITRACEDEBUG("DecInputParameters# Picture Buffer Cb Cr# Virtual address: 0x%x\n",param->picture_buffer_cb_cr.virtual_address);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cb Cr# Bus address: 0x%x\n",param->picture_buffer_cb_cr.bus_address);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cb Cr# Size: %d\n",param->picture_buffer_cb_cr.size);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cb Cr# Logical size: %d\n",param->picture_buffer_cb_cr.logical_size);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cb Cr# Mem type: %s\n",ParseDWLMemType(param->picture_buffer_cb_cr.mem_type));

  APITRACEDEBUG("DecInputParameters# Picture Buffer Cr# Virtual address: 0x%x\n",param->picture_buffer_cr.virtual_address);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cr# Bus address: 0x%x\n",param->picture_buffer_cr.bus_address);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cr# Size: %d\n",param->picture_buffer_cr.size);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cr# Logical size: %d\n",param->picture_buffer_cr.logical_size);
  APITRACEDEBUG("DecInputParameters# Picture Buffer Cr# Mem type: %s\n",ParseDWLMemType(param->picture_buffer_cr.mem_type));

  APITRACEDEBUG("DecInputParameters# Time stamp: %d\n",param->timestamp);
  APITRACEDEBUG("DecInputParameters# Slice info num: %d\n",param->slice_info_num);

}

void ParseDecBufferInfo(struct DecBufferInfo *buf_info){
  APITRACEDEBUG("DecBufferInfo# Next buffer size: %d\n",buf_info->next_buf_size);
  APITRACEDEBUG("DecBufferInfo# Extra buffer number: %d\n",buf_info->buf_num);
  APITRACEDEBUG("DecBufferInfo# Number of extra buffer has been added : %d\n",buf_info->add_extra_ext_buf);
  APITRACEDEBUG("DecBufferInfo# DWLLinearMem# Virtual_address: 0x%x\n",buf_info->buf_to_free.virtual_address);
  APITRACEDEBUG("DecBufferInfo# DWLLinearMem# Bus_address: 0x%x\n",buf_info->buf_to_free.bus_address);
  APITRACEDEBUG("DecBufferInfo# DWLLinearMem# Size: 0x%x\n",buf_info->buf_to_free.size);
  APITRACEDEBUG("DecBufferInfo# DWLLinearMem# Logical Size: 0x%x\n",buf_info->buf_to_free.logical_size);
  APITRACEDEBUG("DecBufferInfo# DWLLinearMem# Mem type: %s\n",ParseDWLMemType(buf_info->buf_to_free.mem_type));
}
#else // #ifdef VCD_LOGMSG
char* ParseDecPictureFormat(enum DecPictureFormat output_format){return "\n";};
void ParseFeatureList(struct DecHwFeatures *cfg){}
char *ParseDecRet(enum DecRet rv){return "\n";}
char *ParseDWLMemType(int i){return "\n";}
void ParseDecInitConfig(struct DecInitConfig *cfg){}
void ParseDecSequenceInfo(struct DecSequenceInfo *seq){}
char *ParseDecPicAlignment(int i){return "\n";}
void ParseDecConfig(struct DecConfig *config){}
void ParseDecInputParameters(struct DecInputParameters* param){}
void ParseDecBufferInfo(struct DecBufferInfo *buf_info){}
#endif // #ifdef VCD_LOGMSG




