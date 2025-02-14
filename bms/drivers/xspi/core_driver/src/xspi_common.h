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
 * xspi_common.h
 *****************************************************************************/
#ifndef XSPI_COMMON_H
#define XSPI_COMMON_H

#include <stdint.h>
#include <stdlib.h>

#include "xspi_regs.h"
#include "xspi_regs_macros.h"

#include <xspi_structs_if.h>
#include <xspi_priv.h>
#include <xspi_sanity.h>

#define LEGACY_STAT_SEQ_CFG_6_REG           0x0468U

#define OPEN_DRAIN_PIN_INDEX_0              0U
#define OPEN_DRAIN_PIN_INDEX_1              1U
#define OPEN_DRAIN_PIN_INDEX_2              2U
#define OPEN_DRAIN_PIN_INDEX_3              3U

/* parasoft-begin-suppress MISRA2012-DIR-4_9 "Do not define function-like macro: ACMD_ECC_STAT_FIELD", DRV-5110" */
#define ACMD_ECC_STAT_FIELD(status)        ((uint8_t)(((status) & ((uint32_t)0x00FF0000U)) >> 16U))
/* parasoft-end-suppress MISRA2012-DIR-4_9 */

#endif
