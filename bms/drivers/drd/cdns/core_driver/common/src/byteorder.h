/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * byteorder.h
 * File contains Endian handling
 ******************************************************************************/

#ifndef BYTEORDER_H
#define BYTEORDER_H

#ifndef CONFIG_E906
#define PLATFORM_64_BIT
#else
#define PLATFORM_32_BIT
#endif

#if !defined(CPU_LITTLE_ENDIAN) && !defined(CPU_BIG_ENDIAN)
#define CPU_LITTLE_ENDIAN
#endif
/* XHCI is LE order so we don't need to have BE macros */

#include "cdn_stdtypes.h"

/* parasoft-begin-suppress MISRA2012-DIR-4_9-4 "Do not define function-like
 * macro, DRV-4346" */
#define swap64(x)                                                              \
  ((uint64_t)((((uint64_t)(x)&0x00000000000000FFULL) << 56U) |                 \
              (((uint64_t)(x)&0x000000000000FF00ULL) << 40U) |                 \
              (((uint64_t)(x)&0x0000000000FF0000ULL) << 24U) |                 \
              (((uint64_t)(x)&0x00000000FF000000ULL) << 8U) |                  \
              (((uint64_t)(x)&0x000000FF00000000ULL) >> 8U) |                  \
              (((uint64_t)(x)&0x0000FF0000000000ULL) >> 24U) |                 \
              (((uint64_t)(x)&0x00FF000000000000ULL) >> 40U) |                 \
              (((uint64_t)(x)&0xFF00000000000000ULL) >> 56U)))

#define swap32(x)                                                              \
  ((uint32_t)((((uint32_t)(x)&0x000000FFUL) << 24U) |                          \
              (((uint32_t)(x)&0x0000FF00UL) << 8U) |                           \
              (((uint32_t)(x)&0x00FF0000UL) >> 8U) |                           \
              (((uint32_t)(x)&0xFF000000UL) >> 24U)))

#define swap16(x)                                                              \
  ((uint16_t)((((uint16_t)(x)&0x00FFU) << 8U) |                                \
              (((uint16_t)(x)&0xFF00U) >> 8U)))

#ifdef CPU_BIG_ENDIAN
#define cpuToLe64(x) swap64(x)
#define cpuToLe32(x) swap32(x)
#define cpuToLe16(x) swap16(x)
#define le64ToCpu(x) swap64(x)
#define le32ToCpu(x) swap32(x)
#define le16ToCpu(x) swap16(x)
#define cpuToBe64(x) (x)
#define cpuToBe32(x) (x)
#define cpuToBe16(x) (x)
#define be64ToCpu(x) (x)
#define be32ToCpu(x) (x)
#define be16ToCpu(x) (x)
#else
#define cpuToLe64(x) (x)
#define cpuToLe32(x) (x)
#define cpuToLe16(x) (x)
#define le64ToCpu(x) (x)
#define le32ToCpu(x) (x)
#define le16ToCpu(x) (x)
#define cpuToBe64(x) swap64(x)
#define cpuToBe32(x) swap32(x)
#define cpuToBe16(x) swap16(x)
#define be64ToCpu(x) swap64(x)
#define be32ToCpu(x) swap32(x)
#define be16ToCpu(x) swap16(x)
#endif

#ifdef PLATFORM_64_BIT
#define leXToCpu le64ToCpu
#else
#define leXToCpu le32ToCpu
#endif
/* parasoft-end-suppress MISRA2012-DIR-4_9-4 "Do not define function-like macro"
 */
#endif /* BYTEORDER_H */
