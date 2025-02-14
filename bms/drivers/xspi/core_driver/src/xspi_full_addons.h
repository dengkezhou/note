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
 * xspi_iot_addons.h
 *****************************************************************************/
#ifndef XSPI_FULL_ADDONS_H
#define XSPI_FULL_ADDONS_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define P2_DISC_LATENCY_DUMMY_CNT_SHIFT     4U
#define P2_DISC_LATENCY_DUMMY_CNT_WIDTH     1U
#define P2_DISC_LATENCY_CMD_TYPE_SHIFT      2U
#define P2_DISC_LATENCY_CMD_TYPE_WIDTH      3U
#define P2_DISC_LATENCY_EXTOP_EN_SHIFT      1U
#define P2_DISC_LATENCY_EXTOP_EN_WIDTH      1U
#define P2_DISC_LATENCY_EXTOP_VAL_SHIFT     0U
#define P2_DISC_LATENCY_EXTOP_VAL_WIDTH     1U

#define DISCOVERY_LINES_ENUM_CNT            7U
#define DISCOVERY_CMD_TYPE_ENUM_CNT         3U

#define ACMD_CMD_TYPE_PIO_COMMAND          0x40000000U
#define ACMD_CMD_TYPE_CDMA_COMMAND         0x00000000U

#define ACMD_CDMA_FL_DMA_SEL_MASTER         ((uint16_t)0x0400)
#define ACMD_CDMA_FL_DMA_SEL_SLAVE          ((uint16_t)0x0000)
#define ACMD_CDMA_FL_DESC_CONT              ((uint16_t)0x0200)
#define ACMD_CDMA_FL_GEN_INT                ((uint16_t)0x0100)
#define ACMD_CDMA_FL_DIS_XIP                ((uint16_t)0x0080)
#define ACMD_CDMA_FL_EN_XIP                 ((uint16_t)0x0040)
#define ACMD_CDMA_FL_XSPI_PTR_CONT          ((uint16_t)0x0020)
#define ACMD_CDMA_FL_SYS_PTR_CONT           ((uint16_t)0x0010)

#define ACMD_PIO_FIELD_GEN_INT             ((uint32_t)0x00040000U)
#define ACMD_PIO_FIELD_DMA_SEL_SLAVE       ((uint32_t)0x00000000U)
#define ACMD_PIO_FIELD_DMA_SEL_MASTER      ((uint32_t)0x00080000U)
#define ACMD_PIO_FIELD_DIS_XIP             ((uint32_t)0x00020000U)
#define ACMD_PIO_FIELD_EN_XIP              ((uint32_t)0x00010000U)

#define ACMD_CMD_REGS_MAX_NUM              6U

#endif
