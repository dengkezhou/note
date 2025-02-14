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

#ifndef VCD_BASE_TYPE_H
#define VCD_BASE_TYPE_H

#include <stddef.h>
#include <stdbool.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifndef OK
#define OK 0
#endif
#ifndef NOK
#define NOK -1
#endif

/**
 * \brief Macro to signal unused parameter.
 * \ingroup common_group
*/
#define UNUSED(x) (void)(x)

/**
 * \brief Transfer 32bit between LSB and MSB.
 * \ingroup common_group
*/
#define TRANSE32(x) ((((u32)(x) & 0xff000000) >> 24 ) |\
                     (((u32)(x) & 0x00ff0000) >> 8 ) |\
                     (((u32)(x) & 0x0000ff00) << 8 )|\
                     (((u32)(x) & 0x000000ff) << 24 ))
/** \ingroup common_group */
typedef unsigned char u8;
/** \ingroup common_group */
typedef signed char i8;
/** \ingroup common_group */
typedef unsigned short u16;
/** \ingroup common_group */
typedef signed short i16;
/** \ingroup common_group */
typedef unsigned int u32;
/** \ingroup common_group */
typedef signed int i32;
/** \ingroup common_group */
typedef long long i64;
/** \ingroup common_group */
typedef unsigned long long u64;

/**
 * \brief Boolean Type
 * \ingroup common_group
*/
#ifndef FALSE
#define FALSE  0
#endif
#ifndef TRUE
#define TRUE 1
#endif
typedef enum { False, True } Boolean;

#ifndef __cplusplus
typedef Boolean vsi_bool;
#endif

#ifdef __FREERTOS__

#ifndef FREERTOS_SIMULATOR
typedef unsigned long long addr_t;  /** \brief Now the FreeRTOS Simulator just support the 64bit env */
typedef size_t  ptr_t;
#else
typedef size_t addr_t;
#endif

#else

typedef size_t addr_t;
#endif

/**
 * \brief SW decoder 16 bits types
 * \ingroup common_group
*/
#if defined(VC1SWDEC_16BIT) || defined(MP4ENC_ARM11)
typedef unsigned short u16x;
typedef signed short i16x;
#else
typedef unsigned int u16x;
typedef signed int i16x;
#endif

#endif /* VCD_BASE_TYPE_H */
