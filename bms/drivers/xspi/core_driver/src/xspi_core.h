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
 * xspi_core.h
 *****************************************************************************/
#ifndef XSPI_CORE_H
#define XSPI_CORE_H

#include <stdint.h>
#include <stdlib.h>

#include "xspi_common.h"

#include "xspi_if.h"
#include "xspi_structs_if.h"
#include "xspi_priv.h"

#define DMA_WORD_SIZE_ENUM_CNT              4U
#define CTRL_REV_ENUM_CNT                   3U

uint32_t CoreInit(XSPI_PrivateData *privateData);
uint32_t WaitForRegValueMatch(volatile uint32_t * reg_addr, uint32_t shift, uint32_t mask, uint32_t dest_value, uint32_t timeout_max);
uint32_t WaitForIdle(XSPI_PrivateData * privateData);
void XSPI_GetLastCommandStatus(XSPI_PrivateData *privateData, XSPI_CommandStatusInfo *commandStatusInfo, bool is_cdma);

#endif
