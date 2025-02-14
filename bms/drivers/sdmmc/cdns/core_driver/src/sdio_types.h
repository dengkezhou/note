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
 * sdio_types.h
 * SD Host controller driver - types definition module
 *****************************************************************************/

#ifndef SDIO_TYPES_H
#define SDIO_TYPES_H

#include "sdio_config.h"
#include "csdd_if.h"
#include "cps.h"
#include "sd4hc_regs.h"

//---------------------------------------------------------------------------
/// @name Definitions of the mutex type and functions
//---------------------------------------------------------------------------
#define MUTEX char
#define MUTEX_LOCK(MUTEX_VAR)
#define MUTEX_UNLOCK(MUTEX_VAR)
#define MUTEX_INIT(MUTEX_VAR)
//---------------------------------------------------------------------------

/**
 * @struct LIST_NODE
 * @brief Structure defines a list node
 */
typedef struct LIST_NODE_S {
    CSDD_DeviceInfo* Item;
    struct LIST_NODE_S *Next;
} LIST_NODE;


#endif // SDIO_TYPES_H
