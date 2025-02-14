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

#ifndef CONFIG_H_DEFINED
#define CONFIG_H_DEFINED

#include "basetype.h"
#include "swreg_struct.h"
/* tile border coefficients of filter */
#define ASIC_VERT_FILTER_RAM_SIZE 8 /* bytes per pixel row */
#define ASIC_VERT_FILTER_RAM_SIZE_422 12 /* bytes per pixel row */
#define ASIC_VERT_FILTER_RAM_SIZE_VP9 20 /* bytes per pixel row */

#define ASIC_RFC_RAM_SIZE 128
/* BSD control data of current picture at tile border
 * 128 bits per 4x4 tile = 128/(8*4) bytes per row */
#define ASIC_BSD_CTRL_RAM_SIZE 4 /* bytes per pixel row */
#define ASIC_BSD_CTRL_RAM_SIZE_VP9 8 /* bytes per pixel row */

/* Common config for PP max/min size supported */
#define PP_CROP_MIN_WIDTH           48
#define PP_CROP_MIN_HEIGHT          48
#define PP_CROP_MAX_X               16382
#define PP_CROP_MAX_Y               16382
#define JPEG_PP_SCALE_IN_MAX_WIDTH  16384
#define JPEG_PP_SCALE_IN_MAX_HEIGHT 16384
#define PP_SCALE_OUT_MAX_WIDTH      4096
#define PP_SCALE_OUT_MAX_HEIGHT     2304
void SetCommonConfigRegs(u32 *regs);
void SetSwCtrl(u32 *regs, struct SwRegisters *sw_ctrl);

#ifdef TILE_8x8
#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#else
#define TILE_WIDTH 4
#define TILE_HEIGHT 4
#endif

#endif /* CONFIG_H_DEFINED */
