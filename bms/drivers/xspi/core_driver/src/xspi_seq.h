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
 * xspi_seq.h
 *****************************************************************************/
#ifndef XSPI_SEQ_H
#define XSPI_SEQ_H

#include <stdint.h>

#include "xspi_structs_if.h"
#include "xspi_if.h"

#define RD_PAGE_SIZE_ENUM_CNT           14U
#define PROG_PAGE_SIZE_ENUM_CNT         13U
#define CRC_CHUNK_SIZE_ENUM_CNT         8U
#define NUM_OF_IOS_ENUM_CNT             4U
#define NUM_OF_ADDR_BYTES_ENUM_CNT      4U
#define NUM_OF_SECT_SIZE_ENUM_CNT       32U
#define STAT_SEQ_POLARITY_ENUM_CNT      2U
#define STATUS_WORD_SIZE_ENUM_CNT       2U
#define EDGE_MODE_ENUM_CNT              2U
#define BURST_TYPE_ENUM_CNT             2U
#define TARGET_SPACE_ENUM_CNT           2U
#define SPI_NAND_PLANE_CNT_ENUM_CNT     3U
#define SPI_NAND_CA_SIZE_ENUM_CNT       2U

#define LEGACY_STAT_SEQ_CFG_1_PRG_RDY_DUMMY_CNT_MASK    ((uint32_t)0x0000003FU)
#define LEGACY_STAT_SEQ_CFG_1_PRG_RDY_DUMMY_CNT_SHIFT   ((uint32_t)0U)
#define LEGACY_STAT_SEQ_CFG_1_PRG_RDY_ADDR_EN_MASK      ((uint32_t)0x00000040U)
#define LEGACY_STAT_SEQ_CFG_1_PRG_RDY_ADDR_EN_SHIFT     ((uint32_t)6U)

#define LEGACY_STAT_SEQ_CFG_1_ERS_RDY_DUMMY_CNT_MASK    ((uint32_t)0x00003F00U)
#define LEGACY_STAT_SEQ_CFG_1_ERS_RDY_DUMMY_CNT_SHIFT   ((uint32_t)8U)
#define LEGACY_STAT_SEQ_CFG_1_ERS_RDY_ADDR_EN_MASK      ((uint32_t)0x00004000U)
#define LEGACY_STAT_SEQ_CFG_1_ERS_RDY_ADDR_EN_SHIFT     ((uint32_t)14U)

#define LEGACY_STAT_SEQ_CFG_2_ERS_RDY_CMD_VAL_MASK      ((uint32_t)0x000000FFU)
#define LEGACY_STAT_SEQ_CFG_2_ERS_RDY_CMD_VAL_SHIFT     ((uint32_t)0U)
#define LEGACY_STAT_SEQ_CFG_2_PRG_RDY_CMD_VAL_MASK      ((uint32_t)0x00FF0000U)
#define LEGACY_STAT_SEQ_CFG_2_PRG_RDY_CMD_VAL_SHIFT     ((uint32_t)16U)

#define LEGACY_STAT_SEQ_CFG_3_ERS_RDY_CMD_EXT_VAL_MASK      ((uint32_t)0x000000FFU)
#define LEGACY_STAT_SEQ_CFG_3_ERS_RDY_CMD_EXT_VAL_SHIFT     ((uint32_t)0U)
#define LEGACY_STAT_SEQ_CFG_3_PRG_RDY_CMD_EXT_VAL_MASK      ((uint32_t)0x00FF0000U)
#define LEGACY_STAT_SEQ_CFG_3_PRG_RDY_CMD_EXT_VAL_SHIFT     ((uint32_t)16U)

#define LEGACY_STAT_SEQ_CFG_5_ERS_RDY_IDX_MASK              ((uint32_t)0x0000000FU)
#define LEGACY_STAT_SEQ_CFG_5_ERS_RDY_IDX_SHIFT             ((uint32_t)0U)
#define LEGACY_STAT_SEQ_CFG_5_ERS_RDY_VAL_MASK              ((uint32_t)0x00000010U)
#define LEGACY_STAT_SEQ_CFG_5_ERS_RDY_VAL_SHIFT             ((uint32_t)4U)
#define LEGACY_STAT_SEQ_CFG_5_ERS_RDY_SIZE_MASK             ((uint32_t)0x00000020U)
#define LEGACY_STAT_SEQ_CFG_5_ERS_RDY_SIZE_SHIFT            ((uint32_t)5U)

#define LEGACY_STAT_SEQ_CFG_5_PROG_RDY_IDX_MASK             ((uint32_t)0x000F0000U)
#define LEGACY_STAT_SEQ_CFG_5_PROG_RDY_IDX_SHIFT            ((uint32_t)16U)
#define LEGACY_STAT_SEQ_CFG_5_PROG_RDY_VAL_MASK             ((uint32_t)0x00100000U)
#define LEGACY_STAT_SEQ_CFG_5_PROG_RDY_VAL_SHIFT            ((uint32_t)20U)
#define LEGACY_STAT_SEQ_CFG_5_PROG_RDY_SIZE_MASK            ((uint32_t)0x00200000U)
#define LEGACY_STAT_SEQ_CFG_5_PROG_RDY_SIZE_SHIFT           ((uint32_t)21U)

uint32_t GetNumOfIosEnum(const uint32_t val, XSPI_NumberOfIos * enumVal);
uint32_t GetDataEdgeModeEnum(const uint32_t val, XSPI_DataEdgeMode *enumVal);
uint32_t GetCmdEdgeModeEnum(const uint32_t val, XSPI_CmdEdgeMode *enumVal);
uint32_t GetAddrEdgeModeEnum(const uint32_t val, XSPI_AddrEdgeMode *enumVal);

#endif
