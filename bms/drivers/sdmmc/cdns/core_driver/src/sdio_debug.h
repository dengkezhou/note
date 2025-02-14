/******************************************************************************
 * Copyright (C) 2013-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio_debug.h
 * SD Host controller driver debug module
 *****************************************************************************/

#ifndef SDIO_DEBUG_H
#define SDIO_DEBUG_H

#include "sdio_config.h"
#include <cdn_stdint.h>

#ifdef DEBUG
    #define DEBUG_DUMP_BUFFER32(b, bs, d) DebugDumpBuffer32((b), (bs), (d))
/*****************************************************************************/
/*!
 * @fn      void DebugDumpBuffer32(const uint32_t *bufferPtr, uint8_t bufferSize,
 *                                 const char* description)
 * @brief   Function dumps buffer
 * @param	bufferPtr - pointer to buffer with data to dump
 * @param	bufferSize - size of buffer in bytes it should be aligned to 4
 * @param	description - header of buffer dumped buffer
 *                  it is printed before buffer content
 * @param   Format Charaters of format
 */
/*****************************************************************************/
void DebugDumpBuffer32(const uint32_t *bufferPtr, uint32_t bufferSize,
                       const char* description);

#else
    #define DEBUG_DUMP_BUFFER32(b, bs, d)
#endif

#endif
