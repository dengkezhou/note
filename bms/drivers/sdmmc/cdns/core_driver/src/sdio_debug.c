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
 * sdio_debug.c
 * SD Host controller driver debug module
 *****************************************************************************/

#include "sdio_debug.h"
#include "cdn_log.h"

#ifdef DEBUG

void DebugDumpBuffer32(const uint32_t *bufferPtr, uint32_t bufferSize, const char* description)
{
    uint8_t i;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", description);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "buffer address %p\n", bufferPtr);
    for (i = 0U; i < (bufferSize / 4U); i++) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%08lx \n", bufferPtr[i]);
    }
}

#endif
