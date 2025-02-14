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
 * xspi_seq.c
 * This file contains code for sequence registers configuration.
 *
 *****************************************************************************/

#include <stdint.h>

#include <cps.h>
#include <cdn_log.h>
#include <cdn_errno.h>

#include "xspi_if.h"
#include "xspi_structs_if.h"

#include "xspi_priv.h"
#include "xspi_seq.h"

#include "xspi_sanity.h"

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */

/* Internal function */
static uint32_t GetReadPageSizeEnum(const uint32_t val, XSPI_ReadPageSize * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_ReadPageSize readPageSizeEnums[RD_PAGE_SIZE_ENUM_CNT] = {
        [0U] = XSPI_READ_PAGE_SIZE_1B,
        [1U] = XSPI_READ_PAGE_SIZE_2B,
        [2U] = XSPI_READ_PAGE_SIZE_4B,
        [3U] = XSPI_READ_PAGE_SIZE_8B,
        [4U] = XSPI_READ_PAGE_SIZE_16B,
        [5U] = XSPI_READ_PAGE_SIZE_32B,
        [6U] = XSPI_READ_PAGE_SIZE_64B,
        [7U] = XSPI_READ_PAGE_SIZE_128B,
        [8U] = XSPI_READ_PAGE_SIZE_256B,
        [9U] = XSPI_READ_PAGE_SIZE_512B,
        [10U] = XSPI_READ_PAGE_SIZE_1024B,
        [11U] = XSPI_READ_PAGE_SIZE_2048B,
        [12U] = XSPI_READ_PAGE_SIZE_4096B,
        [13U] = XSPI_READ_PAGE_SIZE_UNLIMITED,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < RD_PAGE_SIZE_ENUM_CNT; ++i) {
        if ((uint32_t) readPageSizeEnums[i] == val) {
            *enumVal = readPageSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static uint32_t GetProgramPageSizeEnum(const uint32_t val, XSPI_ProgramPageSize * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_ProgramPageSize programPageSizeEnums[PROG_PAGE_SIZE_ENUM_CNT] = {
        [0U] = XSPI_PROGRAM_PAGE_SIZE_1B,
        [1U] = XSPI_PROGRAM_PAGE_SIZE_2B,
        [2U] = XSPI_PROGRAM_PAGE_SIZE_4B,
        [3U] = XSPI_PROGRAM_PAGE_SIZE_8B,
        [4U] = XSPI_PROGRAM_PAGE_SIZE_16B,
        [5U] = XSPI_PROGRAM_PAGE_SIZE_32B,
        [6U] = XSPI_PROGRAM_PAGE_SIZE_64B,
        [7U] = XSPI_PROGRAM_PAGE_SIZE_128B,
        [8U] = XSPI_PROGRAM_PAGE_SIZE_256B,
        [9U] = XSPI_PROGRAM_PAGE_SIZE_512B,
        [10U] = XSPI_PROGRAM_PAGE_SIZE_1024B,
        [11U] = XSPI_PROGRAM_PAGE_SIZE_2048B,
        [12U] = XSPI_PROGRAM_PAGE_SIZE_4096B,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < PROG_PAGE_SIZE_ENUM_CNT; ++i) {
        if ((uint32_t) programPageSizeEnums[i] == val) {
            *enumVal = programPageSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static uint32_t GetCrcChunkSizeEnum(const uint32_t val, XSPI_CrcChunkSize * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_CrcChunkSize crcChunkSizeEnums[CRC_CHUNK_SIZE_ENUM_CNT] = {
        [0U] = XSPI_CRC_CHUNK_SIZE_4B,
        [1U] = XSPI_CRC_CHUNK_SIZE_8B,
        [2U] = XSPI_CRC_CHUNK_SIZE_16B,
        [3U] = XSPI_CRC_CHUNK_SIZE_32B,
        [4U] = XSPI_CRC_CHUNK_SIZE_64B,
        [5U] = XSPI_CRC_CHUNK_SIZE_128B,
        [6U] = XSPI_CRC_CHUNK_SIZE_256B,
        [7U] = XSPI_CRC_CHUNK_SIZE_512B,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < CRC_CHUNK_SIZE_ENUM_CNT; ++i) {
        if ((uint32_t) crcChunkSizeEnums[i] == val) {
            *enumVal = crcChunkSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

uint32_t GetNumOfIosEnum(const uint32_t val, XSPI_NumberOfIos * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_NumberOfIos numOfIosEnums[NUM_OF_IOS_ENUM_CNT] = {
        [0U] = XSPI_NUMBER_OF_IOS_1,
        [1U] = XSPI_NUMBER_OF_IOS_2,
        [2U] = XSPI_NUMBER_OF_IOS_4,
        [3U] = XSPI_NUMBER_OF_IOS_8,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < NUM_OF_IOS_ENUM_CNT; ++i) {
        if ((uint32_t) numOfIosEnums[i] == val) {
            *enumVal = numOfIosEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static uint32_t GetNumOfAddrBytesEnum(const uint32_t val, XSPI_StatSeqAddrCount * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_StatSeqAddrCount numOfAddrBytesEnums[NUM_OF_ADDR_BYTES_ENUM_CNT] = {
        [0U] = XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE,
        [1U] = XSPI_STAT_SEQ_ADDR_COUNT_2_ADDR_BYTES,
        [2U] = XSPI_STAT_SEQ_ADDR_COUNT_3_ADDR_BYTES,
        [3U] = XSPI_STAT_SEQ_ADDR_COUNT_4_ADDR_BYTES,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < NUM_OF_ADDR_BYTES_ENUM_CNT; ++i) {
        if ((uint32_t) numOfAddrBytesEnums[i] == val) {
            *enumVal = numOfAddrBytesEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static uint32_t GetSeqStatPolarityEnum(const uint32_t val, XSPI_StatPolarity *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_StatPolarity seqStatPolarityEnums[STAT_SEQ_POLARITY_ENUM_CNT] = {
        [0U] = XSPI_STAT_POLARITY_0,
        [1U] = XSPI_STAT_POLARITY_1,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < STAT_SEQ_POLARITY_ENUM_CNT; ++i) {
        if ((uint32_t) seqStatPolarityEnums[i] == val) {
            *enumVal = seqStatPolarityEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

/* Internal function */
static uint32_t GetSeqStatStatusWordSizeEnum(const uint32_t val, XSPI_StatStatusWordSize *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_StatStatusWordSize statusWordSizeEnums[STATUS_WORD_SIZE_ENUM_CNT] = {
        [0U] = XSPI_STAT_STATUS_WORD_SIZE_8_BIT,
        [1U] = XSPI_STAT_STATUS_WORD_SIZE_16_BIT,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < STATUS_WORD_SIZE_ENUM_CNT; ++i) {
        if ((uint32_t) statusWordSizeEnums[i] == val) {
            *enumVal = statusWordSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

uint32_t GetCmdEdgeModeEnum(const uint32_t val, XSPI_CmdEdgeMode *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_CmdEdgeMode cmdEdgeModeEnums[EDGE_MODE_ENUM_CNT] = {
        [0U] = XSPI_CMD_EDGE_MODE_SDR,
        [1U] = XSPI_CMD_EDGE_MODE_DDR,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < EDGE_MODE_ENUM_CNT; ++i) {
        if ((uint32_t) cmdEdgeModeEnums[i] == val) {
            *enumVal = cmdEdgeModeEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

uint32_t GetAddrEdgeModeEnum(const uint32_t val, XSPI_AddrEdgeMode *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_AddrEdgeMode addrEdgeModeEnums[EDGE_MODE_ENUM_CNT] = {
        [0U] = XSPI_ADDR_EDGE_MODE_SDR,
        [1U] = XSPI_ADDR_EDGE_MODE_DDR,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < EDGE_MODE_ENUM_CNT; ++i) {
        if ((uint32_t) addrEdgeModeEnums[i] == val) {
            *enumVal = addrEdgeModeEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

uint32_t GetDataEdgeModeEnum(const uint32_t val, XSPI_DataEdgeMode *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_DataEdgeMode dataEdgeModeEnums[EDGE_MODE_ENUM_CNT] = {
        [0U] = XSPI_DATA_EDGE_MODE_SDR,
        [1U] = XSPI_DATA_EDGE_MODE_DDR,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < EDGE_MODE_ENUM_CNT; ++i) {
        if ((uint32_t) dataEdgeModeEnums[i] == val) {
            *enumVal = dataEdgeModeEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

/* Internal function */
static uint32_t GetBurstTypeEnum(const uint32_t val, XSPI_BurstType *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_BurstType burstTypeEnums[BURST_TYPE_ENUM_CNT] = {
        [0U] = XSPI_BURST_TYPE_WRAPPED,
        [1U] = XSPI_BURST_TYPE_LINEAR,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < BURST_TYPE_ENUM_CNT; ++i) {
        if ((uint32_t) burstTypeEnums[i] == val) {
            *enumVal = burstTypeEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

/* Internal function */
static uint32_t GetTargetSpaceEnum(const uint32_t val, XSPI_TargetSpace *enumVal)
{
    uint8_t i;
    uint32_t result = CDN_EINVAL;

    const XSPI_TargetSpace targetSpaceEnums[TARGET_SPACE_ENUM_CNT] = {
        [0U] = XSPI_TARGET_SPACE_MEMORY,
        [1U] = XSPI_TARGET_SPACE_REGISTER,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < TARGET_SPACE_ENUM_CNT; ++i) {
        if ((uint32_t) targetSpaceEnums[i] == val) {
            *enumVal = targetSpaceEnums[i];
            result = CDN_EOK;
        }
    }

    return result; 
}

/* Internal function */
static uint32_t GetPlaneCntEnum(const uint32_t planeCntVal, XSPI_SpiNandPlaneCount * planeCnt)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_SpiNandPlaneCount planeCntEnums[SPI_NAND_PLANE_CNT_ENUM_CNT] = {
        [0U] = XSPI_SPI_NAND_1_PLANE,
        [1U] = XSPI_SPI_NAND_2_PLANES,
        [2U] = XSPI_SPI_NAND_4_PLANES,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < SPI_NAND_PLANE_CNT_ENUM_CNT; i++) {
        if ((uint32_t)planeCntEnums[i] == planeCntVal) {
            *planeCnt = planeCntEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static uint32_t GetCaSizeEnum(const uint32_t caSizeVal, XSPI_SpiNandCaSize * spiNandCaSize)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_SpiNandCaSize caSizeEnums[SPI_NAND_CA_SIZE_ENUM_CNT] = {
        [0U] = XSPI_SPI_NAND_CA_SIZE_12,
        [1U] = XSPI_SPI_NAND_CA_SIZE_13,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < SPI_NAND_CA_SIZE_ENUM_CNT; i++) {
        if ((uint32_t)caSizeEnums[i] == caSizeVal) {
            *spiNandCaSize = caSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/**
 * Internal function
 * Function sets CRC parameters.
 */
static void SetGlobalCmdCrcParams(XSPI_PrivateData * privateData, const XSPI_GlobalCommandParameters * globalCmdParameters, uint32_t * globalCmdParams)
{
    /* Common CRC parameters for sequences in ACMD and Direct work modes */

    if (!privateData->xSpiIot) {
        *globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_VARIANT, *globalCmdParams, globalCmdParameters->crcVariant);
    }

    *globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_OE, *globalCmdParams, ((globalCmdParameters->crcToogleData == true) ? 1U : 0U));
    *globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_CHUNK_SIZE, *globalCmdParams, globalCmdParameters->crcChunkSize);
    *globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_UAL_CHUNK_EN, *globalCmdParams, ((globalCmdParameters->crcUalChunkEn == true) ? 1U : 0U));
    *globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_UAL_CHUNK_CHK, *globalCmdParams, ((globalCmdParameters->crcUalChunkChk == true) ? 1U : 0U));
}

static uint32_t CheckPageProgReadSizes(const XSPI_PrivateData * privateData, const XSPI_GlobalCommandParameters * globalCmdParameters)
{
    uint32_t result = CDN_EOK;
    /* Some program/read page sizes are not supported below R003 controller revision */
    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
        /* Check for greater program page size values */
        if ((globalCmdParameters->pgmPageSize >= XSPI_PROGRAM_PAGE_SIZE_1024B) &&
            (globalCmdParameters->pgmPageSize <= XSPI_PROGRAM_PAGE_SIZE_4096B)) {

            result = CDN_ENOTSUP;
        }

        if (result == CDN_EOK) {
            /* Check for greater read page size values */
            if ((globalCmdParameters->rdPageSize >= XSPI_READ_PAGE_SIZE_1024B) &&
                (globalCmdParameters->rdPageSize <= XSPI_READ_PAGE_SIZE_4096B)) {

                result = CDN_ENOTSUP;
            }
        }
    }

    return result;
}

/**
 * Sets global command parameters having common values for sequences in
 * CDMA, PIO and Direct work modes.
 * @param[in] privateData Pointer to driver private data object
 * @param[in] globalCmdParameters Global command parameters
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP for not supported parameters
 */
uint32_t XSPI_SetGlobalCmdParameters(XSPI_PrivateData * privateData, const XSPI_GlobalCommandParameters * globalCmdParameters)
{
    uint32_t globalCmdParams = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetGlobalCmdParametersSF(privateData, globalCmdParameters) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        result = CheckPageProgReadSizes((const XSPI_PrivateData *)privateData, globalCmdParameters);

        if (result == CDN_EOK)
        {
            if (!privateData->xSpiIot) {
                globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_PAGE_SIZE_RD, globalCmdParams, globalCmdParameters->rdPageSize);
            }

            globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_PAGE_SIZE_PGM, globalCmdParams, globalCmdParameters->pgmPageSize);

            globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_DATA_SWAP, globalCmdParams,((globalCmdParameters->dataSwap == true) ? 1U : 0U));

            if (!privateData->xSpiIot) {
                globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_DATA_PER_ADDR, globalCmdParams, globalCmdParameters->dataPerAddress);
            }

            globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_TYPE, globalCmdParams, globalCmdParameters->seqType);

            globalCmdParams = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_EN, globalCmdParams, ((globalCmdParameters->crcDynamicCalcEnable == true) ? 1U : 0U));

            /* Set CRC parameters */
            SetGlobalCmdCrcParams(privateData, globalCmdParameters, &globalCmdParams);

            /* Write global sequence config register */
            CPS_REG_WRITE(&privateData->regs->global_seq_cfg, globalCmdParams);
        }
    }

    return result;
}

/**
 * Internal function
 * Function reads CRC parameters.
 */
static uint32_t GetGlobalCmdCrcParams(XSPI_PrivateData * privateData, XSPI_GlobalCommandParameters * globalCmdParameters, uint32_t globalCmdParams)
{
    uint32_t result = CDN_EOK;

    /* Dynamic CRC calculation */
    if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_EN, globalCmdParams) == 0U) {
        globalCmdParameters->crcDynamicCalcEnable = false;
    } else {
        globalCmdParameters->crcDynamicCalcEnable = true;
    }

    if (!privateData->xSpiIot) {
        /* CRC variant */
        if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_VARIANT, globalCmdParams) == 0U) {
            globalCmdParameters->crcVariant = XSPI_CRC_VARIANT_CALC_ADDR_PHASE;
        } else {
            globalCmdParameters->crcVariant = XSPI_CRC_VARIANT_CALC_ALL_PHASES;
        }
    }

    /* CRC data toggling */
    if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_OE, globalCmdParams) == 0U) {
        globalCmdParameters->crcToogleData = false;
    } else {
        globalCmdParameters->crcToogleData = true;
    }

    /* Number of bytes after which CRC occurs */
    result |= GetCrcChunkSizeEnum(CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_CHUNK_SIZE, globalCmdParams), &globalCmdParameters->crcChunkSize);

    if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_UAL_CHUNK_EN, globalCmdParams) == 0U) {
        globalCmdParameters->crcUalChunkEn = false;
    } else {
        globalCmdParameters->crcUalChunkEn = true;
    }

    if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_CRC_UAL_CHUNK_CHK, globalCmdParams) == 0U) {
        globalCmdParameters->crcUalChunkChk = false;
    } else {
        globalCmdParameters->crcUalChunkChk = true;
    }

    return result;
}

static uint32_t GetSeqTypeEnum(const uint32_t seqType, XSPI_SequenceType * seqTypeEnum)
{
    uint32_t result = CDN_EOK;

    /* Convert uint32_t to enum */
    switch (seqType) {
    case 0U:
        /* Profile 1.0 SPI NOR memory types */
        *seqTypeEnum = XSPI_SEQUENCE_TYPE_P1_SPI_NOR;
        break;

    case 1U:
        /* Profile 2.0 HyperFlash memory types */
        *seqTypeEnum = XSPI_SEQUENCE_TYPE_P2_HYPER_FLASH;
        break;

    case 2U:
        /* Profile 2.0 HyperRAM memory types */
        *seqTypeEnum = XSPI_SEQUENCE_TYPE_P2_HYPER_RAM;
        break;

    case 3U:
        /* Profile 1.0 SPI NAND memory types */
        *seqTypeEnum = XSPI_SEQUENCE_TYPE_P1_SPI_NAND;
        break;

    default:
        result = CDN_EINVAL;
        break;
    }

    return result;
}

/**
 * Gets global command parameters having common values for sequences in
 * CDMA, PIO and Direct work modes.
 * @param[in] privateData Pointer to driver private data object
 * @param[out] globalCmdParameters Global command parameters
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetGlobalCmdParameters(XSPI_PrivateData * privateData, XSPI_GlobalCommandParameters * globalCmdParameters)
{
    uint32_t result = CDN_EOK;
    uint32_t globalCmdParams = 0U;

    /* Check parameters */
    if (XSPI_GetGlobalCmdParametersSF(privateData, globalCmdParameters) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        globalCmdParams = CPS_REG_READ(&privateData->regs->global_seq_cfg);

        if (!privateData->xSpiIot) {
            /* Page size of device for read operation */
            result = GetReadPageSizeEnum(CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_PAGE_SIZE_RD, globalCmdParams), &globalCmdParameters->rdPageSize);
        }

        /* Page size of device for program operation */
        result |= GetProgramPageSizeEnum(CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_PAGE_SIZE_PGM, globalCmdParams), &globalCmdParameters->pgmPageSize);

        result |= GetGlobalCmdCrcParams(privateData, globalCmdParameters, globalCmdParams);

        /* Reversed byte order */
        if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_DATA_SWAP, globalCmdParams) == 0U) {
            globalCmdParameters->dataSwap = false;
        } else {
            globalCmdParameters->dataSwap = true;
        }

        if (!privateData->xSpiIot) {
            if (CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_DATA_PER_ADDR, globalCmdParams) == 0U) {
                globalCmdParameters->dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
            } else {
                globalCmdParameters->dataPerAddress = XSPI_DATA_PER_ADDRESS_2B;
            }
        }

        /* Sequence type */
        result = GetSeqTypeEnum(CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG, SEQ_TYPE, globalCmdParams), &globalCmdParameters->seqType);
    }
    return result;
}

/**
 * Internal function
 * Configures command extension phase for program sequence
 */
static void SetProgramSeqP1CmdExtConfig(XSPI_PrivateData * privateData, const XSPI_ProgramSeqP1Config * progSeqP1Cfg)
{
    uint32_t prog_p1_seq_cfg1_reg = 0U;

    prog_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_1, PROG_SEQ_P1_CMD_EXT_EN, prog_p1_seq_cfg1_reg, ((progSeqP1Cfg->progSeqCmdExt.enable == true) ? 1U : 0U));
    prog_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_1, PROG_SEQ_P1_CMD_EXT_VAL, prog_p1_seq_cfg1_reg, progSeqP1Cfg->progSeqCmdExt.value);

    CPS_REG_WRITE(&privateData->regs->prog_seq_cfg_1, prog_p1_seq_cfg1_reg);
}

/**
 * Sets PROGRAM sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] progSeqP1Cfg PROGRAM P1 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetProgramSeqP1Config(XSPI_PrivateData * privateData, const XSPI_ProgramSeqP1Config * progSeqP1Cfg)
{
    uint32_t prog_p1_seq_cfg0_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetProgramSeqP1ConfigSF(privateData, progSeqP1Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Command phase */
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_CMD_VAL,      prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqCmd.value);
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_CMD_IOS,      prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqCmd.ios);
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_CMD_EDGE,     prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqCmd.edge);

        /* Address phase */
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_ADDR_CNT,     prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqAddr.count);
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_ADDR_IOS,     prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqAddr.ios);
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_ADDR_EDGE,    prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqAddr.edge);

        /* Data phase */
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_DATA_IOS,     prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqData.ios);
        prog_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_DATA_EDGE,    prog_p1_seq_cfg0_reg, progSeqP1Cfg->progSeqData.edge);

        CPS_REG_WRITE(&privateData->regs->prog_seq_cfg_0, prog_p1_seq_cfg0_reg);

        SetProgramSeqP1CmdExtConfig(privateData, progSeqP1Cfg);
    }

    return result;
}

/* Internal function */
static void GetProgramSeqP1CmdExtConfig(XSPI_PrivateData * privateData, XSPI_ProgramSeqP1Config * progSeqP1Cfg)
{
    uint32_t prog_p1_seq_cfg1_reg = 0U;

    /* Get command extension config for program sequence */
    prog_p1_seq_cfg1_reg = CPS_REG_READ(&privateData->regs->prog_seq_cfg_1);

    if (CPS_FLD_READ(XSPI__PROG_SEQ_CFG_1, PROG_SEQ_P1_CMD_EXT_EN,  prog_p1_seq_cfg1_reg) == 0U) {
        progSeqP1Cfg->progSeqCmdExt.enable = false;
    } else {
        progSeqP1Cfg->progSeqCmdExt.enable = true;
    }
    progSeqP1Cfg->progSeqCmdExt.value = (uint8_t) CPS_FLD_READ(XSPI__PROG_SEQ_CFG_1, PROG_SEQ_P1_CMD_EXT_VAL, prog_p1_seq_cfg1_reg);

}

/* Internal function */
static uint32_t GetProgSeqP1AddrConfig(XSPI_ProgramSeqP1Config * progSeqP1Cfg, uint32_t prog_p1_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Address phase */
    progSeqP1Cfg->progSeqAddr.count = (uint8_t) CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_ADDR_CNT, prog_p1_seq_cfg0_reg);

    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_ADDR_IOS, prog_p1_seq_cfg0_reg), &progSeqP1Cfg->progSeqAddr.ios);

    result |= GetAddrEdgeModeEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_ADDR_EDGE, prog_p1_seq_cfg0_reg), &progSeqP1Cfg->progSeqAddr.edge);

    return result;
}

/* Internal function */
static uint32_t GetProgSeqP1CmdConfig(XSPI_ProgramSeqP1Config * progSeqP1Cfg, uint32_t prog_p1_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Command phase */
    progSeqP1Cfg->progSeqCmd.value = (uint8_t) CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_CMD_VAL, prog_p1_seq_cfg0_reg);

    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_CMD_IOS, prog_p1_seq_cfg0_reg), &progSeqP1Cfg->progSeqCmd.ios);

    result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_CMD_EDGE, prog_p1_seq_cfg0_reg), &progSeqP1Cfg->progSeqCmd.edge);

    return result;
}

/* Internal function */
static uint32_t GetProgSeqP1DataConfig(XSPI_ProgramSeqP1Config * progSeqP1Cfg, uint32_t prog_p1_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Data phase */
    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_DATA_IOS, prog_p1_seq_cfg0_reg), &progSeqP1Cfg->progSeqData.ios);

    result |= GetDataEdgeModeEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_0, PROG_SEQ_P1_DATA_EDGE, prog_p1_seq_cfg0_reg), &progSeqP1Cfg->progSeqData.edge);

    return result;
}

/**
 * Gets PROGRAM sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] progSeqP1Cfg PROGRAM P1 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetProgramSeqP1Config(XSPI_PrivateData * privateData, XSPI_ProgramSeqP1Config * progSeqP1Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t prog_p1_seq_cfg0_reg = 0U;

    /* Check parameters */
    if (XSPI_GetProgramSeqP1ConfigSF(privateData, progSeqP1Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        prog_p1_seq_cfg0_reg = CPS_REG_READ(&privateData->regs->prog_seq_cfg_0);

        /* Command phase */
        result |= GetProgSeqP1CmdConfig(progSeqP1Cfg, prog_p1_seq_cfg0_reg);

        /* Address phase */
        result |= GetProgSeqP1AddrConfig(progSeqP1Cfg, prog_p1_seq_cfg0_reg);

        /* Data phase */
        result |= GetProgSeqP1DataConfig(progSeqP1Cfg, prog_p1_seq_cfg0_reg);

        GetProgramSeqP1CmdExtConfig(privateData, progSeqP1Cfg);
    }

    return result;
}

/**
 * Sets PROGRAM sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] progSeqP2Cfg PROGRAM P2 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetProgramSeqP2Config(XSPI_PrivateData * privateData, const XSPI_ProgramSeqP2Config * progSeqP2Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t prog_p2_seq_cfg2_reg = 0U;

    /* Check parameters */
    if (XSPI_SetProgramSeqP2ConfigSF(privateData, progSeqP2Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        prog_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_LATENCY_CNT, prog_p2_seq_cfg2_reg, progSeqP2Cfg->progSeqLatCount);
        prog_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_MASK_CMD_MOD, prog_p2_seq_cfg2_reg, ((progSeqP2Cfg->progSeqExtCmdMod == true) ? 1U : 0U));

        if (!privateData->xSpiIot) {
            prog_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_BURST_TYPE, prog_p2_seq_cfg2_reg, progSeqP2Cfg->progSeqBurstType);
            prog_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_TARGET, prog_p2_seq_cfg2_reg, progSeqP2Cfg->progSeqTarget);
        }

        CPS_REG_WRITE(&privateData->regs->prog_seq_cfg_2, prog_p2_seq_cfg2_reg);
    }

    return result;
}

/**
 * Gets PROGRAM sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] progSeqP2Cfg PROGRAM P2 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetProgramSeqP2Config(XSPI_PrivateData * privateData, XSPI_ProgramSeqP2Config * progSeqP2Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t prog_p2_seq_cfg2_reg = 0U;

    /* Check parameters */
    if (XSPI_GetProgramSeqP2ConfigSF(privateData, progSeqP2Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        prog_p2_seq_cfg2_reg = CPS_REG_READ(&privateData->regs->prog_seq_cfg_2);

        /* Set program latency count */
        progSeqP2Cfg->progSeqLatCount = (uint8_t) CPS_FLD_READ(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_LATENCY_CNT, prog_p2_seq_cfg2_reg);

        /* Get program command extension */
        if (CPS_FLD_READ(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_MASK_CMD_MOD, prog_p2_seq_cfg2_reg) == 0U) {
            progSeqP2Cfg->progSeqExtCmdMod = false;
        } else {
            progSeqP2Cfg->progSeqExtCmdMod = true;
        }

        if (!privateData->xSpiIot) {
            /* Get burst type */
            result |= GetBurstTypeEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_BURST_TYPE, prog_p2_seq_cfg2_reg), &progSeqP2Cfg->progSeqBurstType);

            /* Get target space */
            result |= GetTargetSpaceEnum(CPS_FLD_READ(XSPI__PROG_SEQ_CFG_2, PROG_SEQ_P2_TARGET, prog_p2_seq_cfg2_reg), &progSeqP2Cfg->progSeqTarget);
        }
    }

    return result;
}

/* Internal function */
static void SetReadSeqP1CmdExtConfig(XSPI_PrivateData * privateData, const XSPI_ReadSeqP1Config * readSeqP1Cfg)
{
    uint32_t read_p1_seq_cfg1_reg = 0U;

    /* Mode bits configuration for XIP */
    read_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_MB_EN,  read_p1_seq_cfg1_reg, ((readSeqP1Cfg->readSeqMbEn == true) ? 1U : 0U));
    read_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_MB_DUMMY_CNT, read_p1_seq_cfg1_reg, readSeqP1Cfg->readSeqMbDummyCnt);

    /* Command extension configuration */
    read_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_CMD_EXT_EN,  read_p1_seq_cfg1_reg, ((readSeqP1Cfg->readSeqCmdExt.enable == true) ? 1U : 0U));
    read_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_CMD_EXT_VAL, read_p1_seq_cfg1_reg, readSeqP1Cfg->readSeqCmdExt.value);

    if (!privateData->xSpiIot && (privateData->ctrlRev >= XSPI_CTRL_REV_R003)) {
        read_p1_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_CACHE_RANDOM_READ_EN, read_p1_seq_cfg1_reg, ((readSeqP1Cfg->cacheRandomReadEn == true) ? 1U : 0U));
    }

    CPS_REG_WRITE(&privateData->regs->read_seq_cfg_1, read_p1_seq_cfg1_reg);
}

/* Internal function */
static void SetReadSeqP1CmdAddrPhase(const XSPI_ReadSeqP1Config * readSeqP1Cfg, uint32_t * read_p1_seq_cfg0_reg)
{
    uint32_t cfg_reg = *read_p1_seq_cfg0_reg;

    /* Command phase */
    cfg_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_CMD_VAL,    cfg_reg, readSeqP1Cfg->readSeqCmd.value);
    cfg_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_CMD_IOS,    cfg_reg, readSeqP1Cfg->readSeqCmd.ios);
    cfg_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_CMD_EDGE,   cfg_reg, readSeqP1Cfg->readSeqCmd.edge);

    /* Address phase */
    cfg_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_ADDR_CNT,   cfg_reg, readSeqP1Cfg->readSeqAddr.count);
    cfg_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_ADDR_IOS,   cfg_reg, readSeqP1Cfg->readSeqAddr.ios);
    cfg_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_ADDR_EDGE,  cfg_reg, readSeqP1Cfg->readSeqAddr.edge);

    *read_p1_seq_cfg0_reg = cfg_reg;
}

/**
 * Sets READ sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] readSeqP1Cfg READ P1 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetReadSeqP1Config(XSPI_PrivateData * privateData, const XSPI_ReadSeqP1Config * readSeqP1Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t read_p1_seq_cfg0_reg = 0U;

    /* Check parameters */
    if (XSPI_SetReadSeqP1ConfigSF(privateData, readSeqP1Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        SetReadSeqP1CmdAddrPhase(readSeqP1Cfg, &read_p1_seq_cfg0_reg);

        /* Data phase */
        read_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_DATA_IOS,   read_p1_seq_cfg0_reg, readSeqP1Cfg->readSeqData.ios);
        read_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_DATA_EDGE,  read_p1_seq_cfg0_reg, readSeqP1Cfg->readSeqData.edge);
        read_p1_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_DUMMY_CNT,  read_p1_seq_cfg0_reg, readSeqP1Cfg->readSeqDummyCnt);

        CPS_REG_WRITE(&privateData->regs->read_seq_cfg_0, read_p1_seq_cfg0_reg);

        SetReadSeqP1CmdExtConfig(privateData, readSeqP1Cfg);
    }

    return result;
}

static void GetReadSeqP1CmdExtConfig(XSPI_PrivateData * privateData, XSPI_ReadSeqP1Config * readSeqP1Cfg)
{
    uint32_t read_p1_seq_cfg1_reg = 0U;

    read_p1_seq_cfg1_reg = CPS_REG_READ(&privateData->regs->read_seq_cfg_1);

    /* Get Mode bits configuration for XIP */
    if (CPS_FLD_READ(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_MB_EN,  read_p1_seq_cfg1_reg) == 0U) {
        readSeqP1Cfg->readSeqMbEn = false;
    } else {
        readSeqP1Cfg->readSeqMbEn = true;
    }

    /* Get dummy cycles count (XIP) */
    readSeqP1Cfg->readSeqMbDummyCnt = (uint8_t) CPS_FLD_READ(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_MB_DUMMY_CNT, read_p1_seq_cfg1_reg);

    /* Get Command extension configuration */
    if (CPS_FLD_READ(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_CMD_EXT_EN,  read_p1_seq_cfg1_reg) == 0U) {
        readSeqP1Cfg->readSeqCmdExt.enable = false;
    } else {
        readSeqP1Cfg->readSeqCmdExt.enable = true;
    }

    /* Get command extension opcode */
    readSeqP1Cfg->readSeqCmdExt.value = (uint8_t) CPS_FLD_READ(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_CMD_EXT_VAL, read_p1_seq_cfg1_reg);

    /* Check controller revision */
    if (!privateData->xSpiIot && (privateData->ctrlRev >= XSPI_CTRL_REV_R003)) {
        /* Get random read enable */
        if (CPS_FLD_READ(XSPI__READ_SEQ_CFG_1, READ_SEQ_P1_CACHE_RANDOM_READ_EN, read_p1_seq_cfg1_reg) == 0U) {
            readSeqP1Cfg->cacheRandomReadEn = false;
        } else {
            readSeqP1Cfg->cacheRandomReadEn = true;
        }
    }
}

/* Internal function */
static uint32_t GetReadSeqP1CmdConfig(XSPI_ReadSeqP1Config * readSeqP1Cfg, uint32_t read_p1_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Command phase */
    readSeqP1Cfg->readSeqCmd.value = (uint8_t) CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_CMD_VAL, read_p1_seq_cfg0_reg);

    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_CMD_IOS, read_p1_seq_cfg0_reg), &readSeqP1Cfg->readSeqCmd.ios);

    result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_CMD_EDGE, read_p1_seq_cfg0_reg), &readSeqP1Cfg->readSeqCmd.edge);

    return result;
}

/* Internal function */
static uint32_t GetReadSeqP1AddrConfig(XSPI_ReadSeqP1Config * readSeqP1Cfg, uint32_t read_p1_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Address phase */
    readSeqP1Cfg->readSeqAddr.count = (uint8_t) CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_ADDR_CNT, read_p1_seq_cfg0_reg);

    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_ADDR_IOS, read_p1_seq_cfg0_reg), &readSeqP1Cfg->readSeqAddr.ios); 

    result |= GetAddrEdgeModeEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_ADDR_EDGE, read_p1_seq_cfg0_reg), &readSeqP1Cfg->readSeqAddr.edge);

    return result;
}

/* Internal function */
static uint32_t GetReadSeqP1DataConfig(XSPI_ReadSeqP1Config * readSeqP1Cfg, uint32_t read_p1_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Data phase */
    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_DATA_IOS, read_p1_seq_cfg0_reg), &readSeqP1Cfg->readSeqData.ios);

    result |= GetDataEdgeModeEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_DATA_EDGE, read_p1_seq_cfg0_reg), &readSeqP1Cfg->readSeqData.edge);

    return result;
}

/**
 * Gets READ sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] readSeqP1Cfg READ P1 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetReadSeqP1Config(XSPI_PrivateData * privateData, XSPI_ReadSeqP1Config * readSeqP1Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t read_p1_seq_cfg0_reg = 0U;

    /* Check parameters */
    if (XSPI_GetReadSeqP1ConfigSF(privateData, readSeqP1Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        read_p1_seq_cfg0_reg = CPS_REG_READ(&privateData->regs->read_seq_cfg_0);

        /* Command phase */
        result |= GetReadSeqP1CmdConfig(readSeqP1Cfg, read_p1_seq_cfg0_reg);

        /* Address phase */
        result |= GetReadSeqP1AddrConfig(readSeqP1Cfg, read_p1_seq_cfg0_reg);

        /* Data phase */
        result |= GetReadSeqP1DataConfig(readSeqP1Cfg, read_p1_seq_cfg0_reg);

        readSeqP1Cfg->readSeqDummyCnt = (uint8_t) CPS_FLD_READ(XSPI__READ_SEQ_CFG_0, READ_SEQ_P1_DUMMY_CNT, read_p1_seq_cfg0_reg);

        GetReadSeqP1CmdExtConfig(privateData, readSeqP1Cfg);
    }

    return result;
}

/**
 * Sets READ sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] readSeqP2Cfg READ P2 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetReadSeqP2Config(XSPI_PrivateData * privateData, const XSPI_ReadSeqP2Config * readSeqP2Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t read_p2_seq_cfg2_reg = 0U;
    uint8_t latencyCnt = 0U;

    /* Check parameters */
    if (XSPI_SetReadSeqP2ConfigSF(privateData, readSeqP2Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Controller expects value 'N-1' for 'N' latency clock cycles */
        if (readSeqP2Cfg->readSeqLatencyCnt != 0U) {
            latencyCnt = readSeqP2Cfg->readSeqLatencyCnt - 1U;
        }
        read_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_LATENCY_CNT, read_p2_seq_cfg2_reg, latencyCnt);

        read_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_HF_BOUND_EN, read_p2_seq_cfg2_reg, ((readSeqP2Cfg->readSeqHfBoundEn == true) ? 1U : 0U));

        read_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_MASK_CMD_MOD, read_p2_seq_cfg2_reg, ((readSeqP2Cfg->readSeqExtCmdMod == true) ? 1U : 0U));

        if (!privateData->xSpiIot) {
            read_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_BURST_TYPE, read_p2_seq_cfg2_reg, readSeqP2Cfg->readSeqBurstType);
            read_p2_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_TARGET, read_p2_seq_cfg2_reg, readSeqP2Cfg->readSeqTarget);
        }

        CPS_REG_WRITE(&privateData->regs->read_seq_cfg_2, read_p2_seq_cfg2_reg);
    }

    return result;
}

/**
 * Gets READ sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] readSeqP2Cfg READ P2 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetReadSeqP2Config(XSPI_PrivateData * privateData, XSPI_ReadSeqP2Config * readSeqP2Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t read_p2_seq_cfg2_reg = 0U;

    /* Check parameters */
    if (XSPI_GetReadSeqP2ConfigSF(privateData, readSeqP2Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        read_p2_seq_cfg2_reg = CPS_REG_READ(&privateData->regs->read_seq_cfg_2);

        /* Number of latency cycles */
        readSeqP2Cfg->readSeqLatencyCnt = (uint8_t) CPS_FLD_READ(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_LATENCY_CNT, read_p2_seq_cfg2_reg);
        /* Increment latency count by 1 */
        if (readSeqP2Cfg->readSeqLatencyCnt != 0U) {
            readSeqP2Cfg->readSeqLatencyCnt++;
        }

        if (CPS_FLD_READ(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_HF_BOUND_EN, read_p2_seq_cfg2_reg) == 0U) {
            readSeqP2Cfg->readSeqHfBoundEn = false;
        } else {
            readSeqP2Cfg->readSeqHfBoundEn = true;
        }

        if (CPS_FLD_READ(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_MASK_CMD_MOD, read_p2_seq_cfg2_reg) == 0U) {
            readSeqP2Cfg->readSeqExtCmdMod = false;
        } else {
            readSeqP2Cfg->readSeqExtCmdMod = true;
        }

        if (!privateData->xSpiIot) {
            /* Burst type */
            result |= GetBurstTypeEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_BURST_TYPE, read_p2_seq_cfg2_reg), &readSeqP2Cfg->readSeqBurstType);

            /* Target space */
            result |= GetTargetSpaceEnum(CPS_FLD_READ(XSPI__READ_SEQ_CFG_2, READ_SEQ_P2_TARGET, read_p2_seq_cfg2_reg), &readSeqP2Cfg->readSeqTarget);
        }
    }

    return result;
}

/**
 * Sets Write Enable(WEL) sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] welSeqCfg WEL sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetWelSeqConfig(XSPI_PrivateData * privateData, const XSPI_WelSeqConfig * welSeqCfg)
{
    uint32_t wel_seq_cfg_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetWelSeqConfigSF(privateData, welSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        wel_seq_cfg_reg = CPS_FLD_WRITE(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_VAL,     wel_seq_cfg_reg, welSeqCfg->welSeqCmd.value);
        wel_seq_cfg_reg = CPS_FLD_WRITE(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_IOS,     wel_seq_cfg_reg, welSeqCfg->welSeqCmd.ios);
        wel_seq_cfg_reg = CPS_FLD_WRITE(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_EDGE,    wel_seq_cfg_reg, welSeqCfg->welSeqCmd.edge);

        wel_seq_cfg_reg = CPS_FLD_WRITE(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_EXT_EN,  wel_seq_cfg_reg, ((welSeqCfg->welSeqCmdExt.enable == true) ? 1U : 0U));
        wel_seq_cfg_reg = CPS_FLD_WRITE(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_EXT_VAL, wel_seq_cfg_reg, welSeqCfg->welSeqCmdExt.value);

        wel_seq_cfg_reg |= (1<<24);
        CPS_REG_WRITE(&privateData->regs->we_seq_cfg_0, wel_seq_cfg_reg);
    }

    return result;
}

/**
 * Gets Write Enable(WEL) sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] welSeqCfg WEL sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetWelSeqConfig(XSPI_PrivateData * privateData, XSPI_WelSeqConfig * welSeqCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t wel_seq_cfg_reg = 0U;

    /* Check parameters */
    if (XSPI_GetWelSeqConfigSF(privateData, welSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        wel_seq_cfg_reg = CPS_REG_READ(&privateData->regs->we_seq_cfg_0);

        /* Command phase */
        welSeqCfg->welSeqCmd.value = (uint8_t) CPS_FLD_READ(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_VAL,   wel_seq_cfg_reg);

        result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_IOS, wel_seq_cfg_reg), &welSeqCfg->welSeqCmd.ios);

        result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_EDGE,  wel_seq_cfg_reg), &welSeqCfg->welSeqCmd.edge);

        if (CPS_FLD_READ(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_EXT_EN,   wel_seq_cfg_reg) == 0U) {
            welSeqCfg->welSeqCmdExt.enable = false;
        } else {
            welSeqCfg->welSeqCmdExt.enable = true;
        }

        welSeqCfg->welSeqCmdExt.value = (uint8_t) CPS_FLD_READ(XSPI__WE_SEQ_CFG_0, WE_SEQ_P1_CMD_EXT_VAL,  wel_seq_cfg_reg);
    }

    return result;
}

/* Internal function */
static void SetCommStatSeqAddrConfig(const XSPI_PrivateData * privateData, const XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    uint32_t stat_seq_cfg8_reg = 0U;
    uint32_t stat_seq_cfg9_reg = 0U;
    volatile XSPI_Regs * regs = privateData->regs;

    /* Address phase for checking fail status */
    stat_seq_cfg8_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_8, STAT_SEQ_PROG_FAIL_ADDR,  stat_seq_cfg8_reg, commStatSeqConfig->statSeqProgFailAddr);

    CPS_REG_WRITE(&regs->stat_seq_cfg_8, stat_seq_cfg8_reg);

    if (!privateData->xSpiIot) {
        stat_seq_cfg9_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_9, STAT_SEQ_ERS_FAIL_ADDR,   stat_seq_cfg9_reg, commStatSeqConfig->statSeqErsFailAddr);

        CPS_REG_WRITE(&regs->stat_seq_cfg_9, stat_seq_cfg9_reg);
    }
}

/* Internal function */
static void SetCommStatSeqProgConfig(const XSPI_PrivateData * privateData, const XSPI_CommStatSeqConfig * commStatSeqConfig, uint32_t * stat_seq_cfg5_reg)
{
    /* Status config for program sequence */
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_IDX,  *stat_seq_cfg5_reg, commStatSeqConfig->statSeqProgFailIdx);
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_VAL,  *stat_seq_cfg5_reg, commStatSeqConfig->statSeqProgFailVal);
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_EN,   *stat_seq_cfg5_reg, ((commStatSeqConfig->statSeqProgFailEn == true) ? 1U : 0U));

    if (!privateData->xSpiIot) {
        *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_SIZE, *stat_seq_cfg5_reg, commStatSeqConfig->statSeqProgFailSize);
    }
}

/* Internal function */
static void SetCommStatSeqErsConfig(const XSPI_CommStatSeqConfig * commStatSeqConfig, uint32_t * stat_seq_cfg5_reg)
{
    /* Status config for erase sequence */
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_IDX,   *stat_seq_cfg5_reg, commStatSeqConfig->statSeqErsFailIdx);
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_VAL,   *stat_seq_cfg5_reg, commStatSeqConfig->statSeqErsFailVal);
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_SIZE,  *stat_seq_cfg5_reg, commStatSeqConfig->statSeqErsFailSize);
    *stat_seq_cfg5_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_EN,    *stat_seq_cfg5_reg, ((commStatSeqConfig->statSeqErsFailEn == true) ? 1U : 0U));

}

static void LegacyStatSeqCommErsRdyParams(const XSPI_PrivateData * privateData, uint32_t * stat_seq_cfg_5, const XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    /* Erase ready index */
    *stat_seq_cfg_5 = *stat_seq_cfg_5 & ~LEGACY_STAT_SEQ_CFG_5_ERS_RDY_IDX_MASK;
    *stat_seq_cfg_5 |= (((uint32_t)commStatSeqConfig->statSeqDevRdyIdx) << LEGACY_STAT_SEQ_CFG_5_ERS_RDY_IDX_SHIFT);

    /* Erase ready value */
    *stat_seq_cfg_5 = *stat_seq_cfg_5 & ~LEGACY_STAT_SEQ_CFG_5_ERS_RDY_VAL_MASK;
    *stat_seq_cfg_5 |= (((uint32_t)commStatSeqConfig->statSeqDevRdyVal) << LEGACY_STAT_SEQ_CFG_5_ERS_RDY_VAL_SHIFT);

    if (!privateData->xSpiIot) {
        /* Erase ready size */
        *stat_seq_cfg_5 = *stat_seq_cfg_5 & ~LEGACY_STAT_SEQ_CFG_5_ERS_RDY_SIZE_MASK;
        *stat_seq_cfg_5 |= (((uint32_t)commStatSeqConfig->statSeqDevRdySize) << LEGACY_STAT_SEQ_CFG_5_ERS_RDY_SIZE_SHIFT);
    }
}

static void LegacyStatSeqCommPrgRdyParams(const XSPI_PrivateData * privateData, uint32_t * stat_seq_cfg_5, const XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    /* Program ready index */
    *stat_seq_cfg_5 = *stat_seq_cfg_5 & ~LEGACY_STAT_SEQ_CFG_5_PROG_RDY_IDX_MASK;
    *stat_seq_cfg_5 |= (((uint32_t)commStatSeqConfig->statSeqDevRdyIdx) << LEGACY_STAT_SEQ_CFG_5_PROG_RDY_IDX_SHIFT);

    /* Program ready value */
    *stat_seq_cfg_5 = *stat_seq_cfg_5 & ~LEGACY_STAT_SEQ_CFG_5_PROG_RDY_VAL_MASK;
    *stat_seq_cfg_5 |= (((uint32_t)commStatSeqConfig->statSeqDevRdyVal) << LEGACY_STAT_SEQ_CFG_5_PROG_RDY_VAL_SHIFT);

    if (!privateData->xSpiIot) {
        /* Program ready size */
        *stat_seq_cfg_5 = *stat_seq_cfg_5 & ~LEGACY_STAT_SEQ_CFG_5_PROG_RDY_SIZE_MASK;
        *stat_seq_cfg_5 |= (((uint32_t)commStatSeqConfig->statSeqDevRdySize) << LEGACY_STAT_SEQ_CFG_5_PROG_RDY_SIZE_SHIFT);    
    }
}

static void SetStatSeqCommDevRdyParams(XSPI_PrivateData * privateData, const XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    uint32_t stat_seq_cfg_5;

    stat_seq_cfg_5 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_5);

    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {

        /* Set common erase ready parameters */
        LegacyStatSeqCommErsRdyParams(privateData, &stat_seq_cfg_5, commStatSeqConfig);

        /* Set common program ready parameters */
        LegacyStatSeqCommPrgRdyParams(privateData, &stat_seq_cfg_5, commStatSeqConfig);

        /* Write stat_seq_cfg_6 register with same value as in stat_seq_cfg_7,
         * both params (stat_seq_prog_rdy_addr and stat_seq_ers_rdy_addr) have been
         * merged into stat_seq_dev_rdy_addr one which is in stat_seq_cfg_7 in R003.
         * So for R002 write both params */
        
        /* parasoft-begin-suppress MISRA2012-RULE-11_3-2 "Pointer to object type 'volatile XSPI_Regs *' is cast to pointer to different object type 'volatile uint32_t *'", DRV-5060" */
        CPS_REG_WRITE(privateData->legacyStatSeqReg6Addr, commStatSeqConfig->statSeqDevRdyAddr);
        /* parasoft-end-suppress MISRA2012-RULE-11_3-2 */

    } else {

        /* Single write to device ready field */
        stat_seq_cfg_5 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_DEV_RDY_IDX,  stat_seq_cfg_5, (uint32_t)commStatSeqConfig->statSeqDevRdyIdx);
        stat_seq_cfg_5 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_DEV_RDY_VAL,  stat_seq_cfg_5, (uint32_t)commStatSeqConfig->statSeqDevRdyVal);

        if (!privateData->xSpiIot) {
            stat_seq_cfg_5 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_DEV_RDY_SIZE, stat_seq_cfg_5, (uint32_t)commStatSeqConfig->statSeqDevRdySize);
        }
    }

    CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_5, stat_seq_cfg_5);
    CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_7, commStatSeqConfig->statSeqDevRdyAddr);
}

static uint32_t GetStatSeqCommDevRdyParams(XSPI_PrivateData * privateData, XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg_5, fld_value;

    stat_seq_cfg_5 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_5);

    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {

        /* Read device ready bit index (from program ready) */
        fld_value = stat_seq_cfg_5 & LEGACY_STAT_SEQ_CFG_5_PROG_RDY_IDX_MASK;
        fld_value >>= LEGACY_STAT_SEQ_CFG_5_PROG_RDY_IDX_SHIFT;

        commStatSeqConfig->statSeqDevRdyIdx = (uint8_t)fld_value;

        /* Read device ready value opcode (from program ready) */
        fld_value = stat_seq_cfg_5 & LEGACY_STAT_SEQ_CFG_5_PROG_RDY_VAL_MASK;
        fld_value >>= LEGACY_STAT_SEQ_CFG_5_PROG_RDY_VAL_SHIFT;

        result = GetSeqStatPolarityEnum(fld_value, &commStatSeqConfig->statSeqDevRdyVal);

        if (!privateData->xSpiIot && (result == CDN_EOK)) {
            /* Read device ready response value size (from program ready) */

            fld_value = stat_seq_cfg_5 & LEGACY_STAT_SEQ_CFG_5_PROG_RDY_SIZE_MASK;
            fld_value >>= LEGACY_STAT_SEQ_CFG_5_PROG_RDY_SIZE_SHIFT;

            result = GetSeqStatStatusWordSizeEnum(fld_value, &commStatSeqConfig->statSeqDevRdySize);
        }

    } else {

        /* Single read from device ready field */
        commStatSeqConfig->statSeqDevRdyIdx = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_DEV_RDY_IDX, stat_seq_cfg_5);

        result = GetSeqStatPolarityEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_DEV_RDY_VAL, stat_seq_cfg_5), &commStatSeqConfig->statSeqDevRdyVal);

        if (!privateData->xSpiIot && (result == CDN_EOK)) {
            result = GetSeqStatStatusWordSizeEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_DEV_RDY_SIZE, stat_seq_cfg_5), &commStatSeqConfig->statSeqDevRdySize);
        }
    }

    /*
     * While reading device ready sequence address
     * read only stat_seq_cfg_7 register. Its value is same
     * in stat_seq_cfg_6, so for latest driver read only stat_seq_cfg_7
     */
    commStatSeqConfig->statSeqDevRdyAddr = CPS_REG_READ(&privateData->regs->stat_seq_cfg_7);

    return result;
}

/**
 * Sets status checking sequence configuration common for Profile 1 and 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] commStatSeqConfig Common STAT sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetCommStatSeqConfig(XSPI_PrivateData * privateData, const XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    uint32_t stat_seq_cfg5_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetCommStatSeqConfigSF(privateData, commStatSeqConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        if (!privateData->xSpiIot) {
            SetCommStatSeqErsConfig(commStatSeqConfig, &stat_seq_cfg5_reg);
        }

        SetCommStatSeqProgConfig(privateData, commStatSeqConfig, &stat_seq_cfg5_reg);

        CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_5, stat_seq_cfg5_reg);

        SetCommStatSeqAddrConfig(privateData, commStatSeqConfig);

        SetStatSeqCommDevRdyParams(privateData, commStatSeqConfig);
    }

    return result;
}

/* Internal function */
static void GetCommStatSeqAddrConfig(const XSPI_PrivateData * privateData, XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    uint32_t stat_seq_cfg8_reg = 0U;
    uint32_t stat_seq_cfg9_reg = 0U;
    volatile XSPI_Regs * regs = privateData->regs;

    stat_seq_cfg8_reg = CPS_REG_READ(&regs->stat_seq_cfg_8);

    /* Address phase for checking fail status */
    commStatSeqConfig->statSeqProgFailAddr = CPS_FLD_READ(XSPI__STAT_SEQ_CFG_8, STAT_SEQ_PROG_FAIL_ADDR, stat_seq_cfg8_reg);

    if (!privateData->xSpiIot) {
        stat_seq_cfg9_reg = CPS_REG_READ(&regs->stat_seq_cfg_9);

        commStatSeqConfig->statSeqErsFailAddr = CPS_FLD_READ(XSPI__STAT_SEQ_CFG_9, STAT_SEQ_ERS_FAIL_ADDR, stat_seq_cfg9_reg);
    }
}

/* Internal function */
static uint32_t GetCommStatSeqErsConfig(XSPI_CommStatSeqConfig * commStatSeqConfig, uint32_t stat_seq_cfg5_reg)
{
    uint32_t result = CDN_EOK;

    /* Fail status */
    commStatSeqConfig->statSeqErsFailIdx = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_IDX, stat_seq_cfg5_reg);

    result |= GetSeqStatPolarityEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_VAL, stat_seq_cfg5_reg), &commStatSeqConfig->statSeqErsFailVal);

    result |= GetSeqStatStatusWordSizeEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_SIZE,  stat_seq_cfg5_reg), &commStatSeqConfig->statSeqErsFailSize);

    if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_ERS_FAIL_EN, stat_seq_cfg5_reg) == 0U) {
        commStatSeqConfig->statSeqErsFailEn = false;
    } else {
        commStatSeqConfig->statSeqErsFailEn = true;
    }

    return result;
}

/* Internal function */
static uint32_t GetCommStatSeqProgConfig(const XSPI_PrivateData * privateData, XSPI_CommStatSeqConfig * commStatSeqConfig, uint32_t stat_seq_cfg5_reg)
{
    uint32_t result = CDN_EOK;

    /* Fail status */
    commStatSeqConfig->statSeqProgFailIdx = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_IDX, stat_seq_cfg5_reg);
    result |= GetSeqStatPolarityEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_VAL, stat_seq_cfg5_reg), &commStatSeqConfig->statSeqProgFailVal);

    if (!privateData->xSpiIot) {
        result |= GetSeqStatStatusWordSizeEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_SIZE, stat_seq_cfg5_reg), &commStatSeqConfig->statSeqProgFailSize);
    }

    if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_5, STAT_SEQ_PROG_FAIL_EN, stat_seq_cfg5_reg) == 0U) {
        commStatSeqConfig->statSeqProgFailEn = false;
    } else {
        commStatSeqConfig->statSeqProgFailEn = true;
    }

    return result;
}

/**
 * Gets status checking sequence configuration common for Profile 1 and 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] commStatSeqConfig Common STAT sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetCommStatSeqConfig(XSPI_PrivateData * privateData, XSPI_CommStatSeqConfig * commStatSeqConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg5_reg = 0U;

    /* Check parameters */
    if (XSPI_GetCommStatSeqConfigSF(privateData, commStatSeqConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        stat_seq_cfg5_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_5);

        if (!privateData->xSpiIot) {
            result |= GetCommStatSeqErsConfig(commStatSeqConfig, stat_seq_cfg5_reg);
        }

        result |= GetCommStatSeqProgConfig(privateData, commStatSeqConfig, stat_seq_cfg5_reg);

        GetCommStatSeqAddrConfig(privateData, commStatSeqConfig);

        result |= GetStatSeqCommDevRdyParams(privateData, commStatSeqConfig);
    }

    return result;
}

/* Internal function */
static void SetStatSeqP1ValConfig(const XSPI_PrivateData * privateData, const XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg2_reg = 0U;
    uint32_t stat_seq_cfg3_reg = 0U;
    volatile XSPI_Regs * regs = privateData->regs;

    if (!privateData->xSpiIot) {
        /* Command values to check status after erase operation */
        stat_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_2, STAT_SEQ_P1_ERS_FAIL_CMD_VAL,   stat_seq_cfg2_reg, statSeqP1Cfg->statSeqErsFailCmdVal);

        /* Command extension values to check status after erase operation */
        stat_seq_cfg3_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_3, STAT_SEQ_P1_ERS_FAIL_CMD_EXT_VAL,   stat_seq_cfg3_reg, statSeqP1Cfg->statSeqErsFailCmdExtVal);
    }

    /* Command values to check status after program operation */
    stat_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_2, STAT_SEQ_P1_PROG_FAIL_CMD_VAL,  stat_seq_cfg2_reg, statSeqP1Cfg->statSeqProgFailCmdVal);

    /* Command extension values to check status after program operation */
    stat_seq_cfg3_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_3, STAT_SEQ_P1_PROG_FAIL_CMD_EXT_VAL,  stat_seq_cfg3_reg, statSeqP1Cfg->statSeqProgFailCmdExtVal);

    CPS_REG_WRITE(&regs->stat_seq_cfg_2, stat_seq_cfg2_reg);
    CPS_REG_WRITE(&regs->stat_seq_cfg_3, stat_seq_cfg3_reg);
}

/* Internal function */
static void SetStatSeqP1ProgErsConfig(XSPI_PrivateData * privateData, const XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg1_reg = 0U;

    /* Fail status */
    stat_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_PROG_FAIL_DUMMY_CNT,  stat_seq_cfg1_reg, statSeqP1Cfg->statSeqProgFailDummyCnt);
    stat_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_PROG_FAIL_ADDR_EN,    stat_seq_cfg1_reg, ((statSeqP1Cfg->statSeqProgFailAddrEn == true) ? 1U : 0U));

    if (!privateData->xSpiIot) {
        stat_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_ERS_FAIL_DUMMY_CNT,   stat_seq_cfg1_reg, statSeqP1Cfg->statSeqErsFailDummyCnt);
        stat_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_ERS_FAIL_ADDR_EN,     stat_seq_cfg1_reg, ((statSeqP1Cfg->statSeqErsFailAddrEn == true) ? 1U : 0U));
    }

    CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_1, stat_seq_cfg1_reg);

    SetStatSeqP1ValConfig(privateData, statSeqP1Cfg);
}

static void SetStatSeqP1ErsLegacyParams(uint32_t * stat_seq_cfg_1, uint32_t * stat_seq_cfg_2, uint32_t * stat_seq_cfg_3, const XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    /* Erase dummy count */
    *stat_seq_cfg_1 = *stat_seq_cfg_1 & ~LEGACY_STAT_SEQ_CFG_1_ERS_RDY_DUMMY_CNT_MASK;
    *stat_seq_cfg_1 |= ((uint32_t)statSeqP1Cfg->statSeqDevRdyDummyCnt) << LEGACY_STAT_SEQ_CFG_1_ERS_RDY_DUMMY_CNT_SHIFT;

    /* Erase ready address enable */
    *stat_seq_cfg_1 = *stat_seq_cfg_1 & ~LEGACY_STAT_SEQ_CFG_1_ERS_RDY_ADDR_EN_MASK;
    *stat_seq_cfg_1 |= ((uint32_t)((statSeqP1Cfg->statSeqDevRdyAddrEn == true) ? 1U : 0U)) << LEGACY_STAT_SEQ_CFG_1_ERS_RDY_ADDR_EN_SHIFT;

    /* Erase ready command opcode */
    *stat_seq_cfg_2 = *stat_seq_cfg_2 & ~LEGACY_STAT_SEQ_CFG_2_ERS_RDY_CMD_VAL_MASK;
    *stat_seq_cfg_2 |= ((uint32_t)statSeqP1Cfg->statSeqDevRdyCmdVal) << LEGACY_STAT_SEQ_CFG_2_ERS_RDY_CMD_VAL_SHIFT;

    /* Erase ready command extension opcode */
    *stat_seq_cfg_3 = *stat_seq_cfg_3 & ~LEGACY_STAT_SEQ_CFG_3_ERS_RDY_CMD_EXT_VAL_MASK;
    *stat_seq_cfg_3 |= ((uint32_t)statSeqP1Cfg->statSeqDevRdyCmdExtVal) << LEGACY_STAT_SEQ_CFG_3_ERS_RDY_CMD_EXT_VAL_SHIFT;
}

static void SetStatSeqP1ProgLegacyParams(uint32_t * stat_seq_cfg_1, uint32_t * stat_seq_cfg_2, uint32_t * stat_seq_cfg_3, const XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    /* Program ready dummy count */
    *stat_seq_cfg_1 = *stat_seq_cfg_1 & ~LEGACY_STAT_SEQ_CFG_1_PRG_RDY_DUMMY_CNT_MASK;
    *stat_seq_cfg_1 |= ((uint32_t)statSeqP1Cfg->statSeqDevRdyDummyCnt) << LEGACY_STAT_SEQ_CFG_1_PRG_RDY_DUMMY_CNT_SHIFT;

    /* Program ready address enable */
    *stat_seq_cfg_1 = *stat_seq_cfg_1 & ~LEGACY_STAT_SEQ_CFG_1_PRG_RDY_ADDR_EN_MASK;
    *stat_seq_cfg_1 |= ((uint32_t)((statSeqP1Cfg->statSeqDevRdyAddrEn == true) ? 1U : 0U)) << LEGACY_STAT_SEQ_CFG_1_PRG_RDY_ADDR_EN_SHIFT;

    /* Program ready command opcode */
    *stat_seq_cfg_2 = *stat_seq_cfg_2 & ~LEGACY_STAT_SEQ_CFG_2_PRG_RDY_CMD_VAL_MASK;
    *stat_seq_cfg_2 |= ((uint32_t)statSeqP1Cfg->statSeqDevRdyCmdVal) << LEGACY_STAT_SEQ_CFG_2_PRG_RDY_CMD_VAL_SHIFT;

    /* Program ready command extension opcode */
    *stat_seq_cfg_3 = *stat_seq_cfg_3 & ~LEGACY_STAT_SEQ_CFG_3_PRG_RDY_CMD_EXT_VAL_MASK;
    *stat_seq_cfg_3 |= ((uint32_t)statSeqP1Cfg->statSeqDevRdyCmdExtVal) << LEGACY_STAT_SEQ_CFG_3_PRG_RDY_CMD_EXT_VAL_SHIFT;
}

static void SetStatSeqP1DevRdyParams(XSPI_PrivateData * privateData, const XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg_1, stat_seq_cfg_2, stat_seq_cfg_3;

    stat_seq_cfg_1 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_1);
    stat_seq_cfg_2 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_2);
    stat_seq_cfg_3 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_3);

    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {

        /* Set legacy parameters (erase) */
        SetStatSeqP1ErsLegacyParams(&stat_seq_cfg_1, &stat_seq_cfg_2, &stat_seq_cfg_3, statSeqP1Cfg);

        /* Set legacy parameters (program) */
        SetStatSeqP1ProgLegacyParams(&stat_seq_cfg_1, &stat_seq_cfg_2, &stat_seq_cfg_3, statSeqP1Cfg);

    } else {

        /* Single write to device ready field */
        stat_seq_cfg_1 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_DEV_RDY_DUMMY_CNT,    stat_seq_cfg_1, statSeqP1Cfg->statSeqDevRdyDummyCnt);
        stat_seq_cfg_1 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_DEV_RDY_ADDR_EN,      stat_seq_cfg_1, ((statSeqP1Cfg->statSeqDevRdyAddrEn == true) ? 1U : 0U));

        stat_seq_cfg_2 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_2, STAT_SEQ_P1_DEV_RDY_CMD_VAL,     stat_seq_cfg_2, statSeqP1Cfg->statSeqDevRdyCmdVal);
        stat_seq_cfg_3 = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_3, STAT_SEQ_P1_DEV_RDY_CMD_EXT_VAL, stat_seq_cfg_3, statSeqP1Cfg->statSeqDevRdyCmdExtVal);
    }

    CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_1, stat_seq_cfg_1);
    CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_2, stat_seq_cfg_2);
    CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_3, stat_seq_cfg_3);
}

static void GetStatSeqP1DevRdyParams(XSPI_PrivateData * privateData, XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg_1, stat_seq_cfg_2, stat_seq_cfg_3, fld_value;

    stat_seq_cfg_1 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_1);
    stat_seq_cfg_2 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_2);
    stat_seq_cfg_3 = CPS_REG_READ(&privateData->regs->stat_seq_cfg_3);

    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {

        /* Single read from program ready field */

        /* Get device ready address enable */
        if ((stat_seq_cfg_1 & LEGACY_STAT_SEQ_CFG_1_PRG_RDY_ADDR_EN_MASK) == 0U) {
            statSeqP1Cfg->statSeqDevRdyAddrEn = false;
        } else {
            statSeqP1Cfg->statSeqDevRdyAddrEn = true;
        }

        /* Get device ready dummy count */
        fld_value = stat_seq_cfg_1 & LEGACY_STAT_SEQ_CFG_1_PRG_RDY_DUMMY_CNT_MASK;
        fld_value >>= LEGACY_STAT_SEQ_CFG_1_PRG_RDY_DUMMY_CNT_SHIFT;

        statSeqP1Cfg->statSeqDevRdyDummyCnt = (uint8_t)fld_value;


        /* Get device ready command opcode */
        fld_value = stat_seq_cfg_2 & LEGACY_STAT_SEQ_CFG_2_PRG_RDY_CMD_VAL_MASK;
        fld_value >>= LEGACY_STAT_SEQ_CFG_2_PRG_RDY_CMD_VAL_SHIFT;

        statSeqP1Cfg->statSeqDevRdyCmdVal = (uint8_t)fld_value;


        /* Get device ready command extension opcode */
        fld_value = stat_seq_cfg_3 & LEGACY_STAT_SEQ_CFG_3_PRG_RDY_CMD_EXT_VAL_MASK;
        fld_value >>= LEGACY_STAT_SEQ_CFG_3_PRG_RDY_CMD_EXT_VAL_SHIFT;

        statSeqP1Cfg->statSeqDevRdyCmdExtVal = (uint8_t)fld_value;

    } else {

        /* Single read from device ready field */

        statSeqP1Cfg->statSeqDevRdyDummyCnt  = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_DEV_RDY_DUMMY_CNT, stat_seq_cfg_1);
        statSeqP1Cfg->statSeqDevRdyCmdVal    = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_2, STAT_SEQ_P1_DEV_RDY_CMD_VAL, stat_seq_cfg_2);
        statSeqP1Cfg->statSeqDevRdyCmdExtVal = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_3, STAT_SEQ_P1_DEV_RDY_CMD_EXT_VAL, stat_seq_cfg_3);

        if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_DEV_RDY_ADDR_EN, stat_seq_cfg_1) == 0U) {
            statSeqP1Cfg->statSeqDevRdyAddrEn = false;
        } else {
            statSeqP1Cfg->statSeqDevRdyAddrEn = true;
        }
    }
}

/**
 * Sets status checking sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqP1Cfg STAT P1 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetStatSeqP1Config(XSPI_PrivateData * privateData, const XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg0_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetStatSeqP1ConfigSF(privateData, statSeqP1Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Command phase */
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_CMD_IOS,     stat_seq_cfg0_reg, statSeqP1Cfg->statSeqCmdIos);
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_CMD_EDGE,    stat_seq_cfg0_reg, statSeqP1Cfg->statSeqCmdEdge);
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_CMD_EXT_EN,  stat_seq_cfg0_reg, ((statSeqP1Cfg->statSeqCmdExtEn == true) ? 1U : 0U));
        /* Address phase */
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_ADDR_CNT,    stat_seq_cfg0_reg, statSeqP1Cfg->statSeqAddrCnt);
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_ADDR_IOS,    stat_seq_cfg0_reg, statSeqP1Cfg->statSeqAddrIos);
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_ADDR_EDGE,   stat_seq_cfg0_reg, statSeqP1Cfg->statSeqAddrEdge);
        /* Data phase */
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_DATA_IOS,    stat_seq_cfg0_reg, statSeqP1Cfg->statSeqData.ios);
        stat_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_DATA_EDGE,   stat_seq_cfg0_reg, statSeqP1Cfg->statSeqData.edge);

        CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_0, stat_seq_cfg0_reg);

        SetStatSeqP1ProgErsConfig(privateData, statSeqP1Cfg);

        SetStatSeqP1DevRdyParams(privateData, statSeqP1Cfg);
    }

    return result;
}

/* Internal function */
static void GetStatSeqP1ValConfig(const XSPI_PrivateData * privateData, XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg2_reg = 0U;
    uint32_t stat_seq_cfg3_reg = 0U;
    volatile XSPI_Regs * regs = privateData->regs;

    stat_seq_cfg2_reg = CPS_REG_READ(&regs->stat_seq_cfg_2);
    stat_seq_cfg3_reg = CPS_REG_READ(&regs->stat_seq_cfg_3);

    if (!privateData->xSpiIot) {
        /* Command values to check status after erase operation */
        statSeqP1Cfg->statSeqErsFailCmdVal = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_2, STAT_SEQ_P1_ERS_FAIL_CMD_VAL,    stat_seq_cfg2_reg);

        /* Command extension values to check status after erase operation */
        statSeqP1Cfg->statSeqErsFailCmdExtVal = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_3, STAT_SEQ_P1_ERS_FAIL_CMD_EXT_VAL,   stat_seq_cfg3_reg);
    }

    /* Command values to check status after program operation */
    statSeqP1Cfg->statSeqProgFailCmdVal = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_2, STAT_SEQ_P1_PROG_FAIL_CMD_VAL,   stat_seq_cfg2_reg);

    /* Command extension values to check status after program operation */
    statSeqP1Cfg->statSeqProgFailCmdExtVal = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_3, STAT_SEQ_P1_PROG_FAIL_CMD_EXT_VAL,  stat_seq_cfg3_reg);
}

/* Internal function */
static void GetStatSeqP1DummyCnt(XSPI_PrivateData * privateData, XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg1_reg = 0U;

    stat_seq_cfg1_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_1);

    statSeqP1Cfg->statSeqProgFailDummyCnt = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_PROG_FAIL_DUMMY_CNT,  stat_seq_cfg1_reg);

    if (!privateData->xSpiIot) {
        statSeqP1Cfg->statSeqErsFailDummyCnt = (uint8_t) CPS_FLD_READ(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_ERS_FAIL_DUMMY_CNT,   stat_seq_cfg1_reg);
    }
}

/* Internal function */
static void GetStatSeqP1ProgErsConfig(XSPI_PrivateData * privateData, XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t stat_seq_cfg1_reg = 0U;

    stat_seq_cfg1_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_1);

    /* Fail status */
    if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_PROG_FAIL_ADDR_EN, stat_seq_cfg1_reg) == 0U) {
        statSeqP1Cfg->statSeqProgFailAddrEn = false;
    } else {
        statSeqP1Cfg->statSeqProgFailAddrEn = true;
    }

    if (!privateData->xSpiIot) {
        if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_1, STAT_SEQ_P1_ERS_FAIL_ADDR_EN, stat_seq_cfg1_reg) == 0U) {
            statSeqP1Cfg->statSeqErsFailAddrEn = false;
        } else {
            statSeqP1Cfg->statSeqErsFailAddrEn = true;
        }
    }

    /* Get dummy count */
    GetStatSeqP1DummyCnt(privateData, statSeqP1Cfg);

    /* Get command values for program and erase sequences */
    GetStatSeqP1ValConfig(privateData, statSeqP1Cfg);
}

/* Internal function */
static uint32_t GetStatSeqP1CmdConfig(XSPI_StatSeqP1Config * statSeqP1Cfg, uint32_t stat_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Command phase */
    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_CMD_IOS, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqCmdIos);

    result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_CMD_EDGE, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqCmdEdge);

    if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_CMD_EXT_EN,  stat_seq_cfg0_reg) == 0U) {
        statSeqP1Cfg->statSeqCmdExtEn = false;
    } else {
        statSeqP1Cfg->statSeqCmdExtEn = true;
    }

    return result;
}

/* Internal function */
static uint32_t GetStatSeqP1AddrConfig(XSPI_StatSeqP1Config * statSeqP1Cfg, uint32_t stat_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Address phase */
    result |= GetNumOfAddrBytesEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_ADDR_CNT, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqAddrCnt);

    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_ADDR_IOS, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqAddrIos);

    result |= GetAddrEdgeModeEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_ADDR_EDGE, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqAddrEdge);

    return result;
}

/* Internal function */
static uint32_t GetStatSeqP1DataConfig(XSPI_StatSeqP1Config * statSeqP1Cfg, uint32_t stat_seq_cfg0_reg)
{
    uint32_t result = CDN_EOK;

    /* Data phase */
    result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_DATA_IOS, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqData.ios);

    result |= GetDataEdgeModeEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_0, STAT_SEQ_P1_DATA_EDGE, stat_seq_cfg0_reg), &statSeqP1Cfg->statSeqData.edge);

    return result;
}

/**
 * Gets status checking sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqP1Cfg STAT P1 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetStatSeqP1Config(XSPI_PrivateData * privateData, XSPI_StatSeqP1Config * statSeqP1Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg0_reg = 0U;

    /* Check parameters */
    if (XSPI_GetStatSeqP1ConfigSF(privateData, statSeqP1Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        stat_seq_cfg0_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_0);

        /* Command phase */
        result |= GetStatSeqP1CmdConfig(statSeqP1Cfg, stat_seq_cfg0_reg);

        /* Address phase */
        result |= GetStatSeqP1AddrConfig(statSeqP1Cfg, stat_seq_cfg0_reg);

        /* Data phase */
        result |= GetStatSeqP1DataConfig(statSeqP1Cfg, stat_seq_cfg0_reg);

        GetStatSeqP1ProgErsConfig(privateData, statSeqP1Cfg);

        GetStatSeqP1DevRdyParams(privateData, statSeqP1Cfg);
    }

    return result;
}

/**
 * Sets status checking sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqP2Cfg STAT P2 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetStatSeqP2Config(XSPI_PrivateData * privateData, const XSPI_StatSeqP2Config * statSeqP2Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg4_reg = 0U;
    uint8_t latencyCnt = 0U;

    /* Check parameters */
    if (XSPI_SetStatSeqP2ConfigSF(privateData, statSeqP2Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Controller expects value 'N-1' for 'N' latency clock cycles */
        if (statSeqP2Cfg->statSeqLatencyCnt != 0U) {
            latencyCnt = statSeqP2Cfg->statSeqLatencyCnt - 1U;
        }
        stat_seq_cfg4_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_4, STAT_SEQ_P2_LATENCY_CNT, stat_seq_cfg4_reg, latencyCnt);
        stat_seq_cfg4_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_4, STAT_SEQ_P2_MASK_CMD_MOD, stat_seq_cfg4_reg, ((statSeqP2Cfg->statSeqExtCmdMod == true) ? 1U : 0U));

        CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_4, stat_seq_cfg4_reg);
    }

    return result;
}

/**
 * Gets status checking sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqP2Cfg STAT P2 sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetStatSeqP2Config(XSPI_PrivateData * privateData, XSPI_StatSeqP2Config * statSeqP2Cfg)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg4_reg = 0U;

    /* Check parameters */
    if (XSPI_GetStatSeqP2ConfigSF(privateData, statSeqP2Cfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        stat_seq_cfg4_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_4);

        statSeqP2Cfg->statSeqLatencyCnt = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_4, STAT_SEQ_P2_LATENCY_CNT, stat_seq_cfg4_reg);
        /* Increment latency count by 1 */
        if (statSeqP2Cfg->statSeqLatencyCnt != 0U) {
            statSeqP2Cfg->statSeqLatencyCnt++;
        }

        if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_4, STAT_SEQ_P2_MASK_CMD_MOD, stat_seq_cfg4_reg) == 0U) {
            statSeqP2Cfg->statSeqExtCmdMod = false;
        } else {
            statSeqP2Cfg->statSeqExtCmdMod = true;
        }
    }

    return result;
}

/**
 * Sets status sequence settings for NAND SPI devices (Since R003)
 * @param[in]  privateData        Pointer to driver private data object
 * @param[in]  statSeqSpiNandCfg  Status sequence settings for NAND SPI devices
 * 
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if controller version is below R003
 */
uint32_t XSPI_SetStatSeqSpiNandConfig(XSPI_PrivateData * privateData, const XSPI_StatSeqSpiNandConfig * statSeqSpiNandCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg_10_reg;

    if (XSPI_SetStatSeqSpiNandConfigSF(privateData, statSeqSpiNandCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {
            stat_seq_cfg_10_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_10);

            /* Set ECC fail enable */
            stat_seq_cfg_10_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_FAIL_EN, stat_seq_cfg_10_reg, ((statSeqSpiNandCfg->statSeqEccFailEn == true) ? 1U : 0U));

            if (!privateData->xSpiIot) {
                stat_seq_cfg_10_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_CRDY_VAL, stat_seq_cfg_10_reg, statSeqSpiNandCfg->statSeqCRdyVal);

                /* Set cache busy index */
                stat_seq_cfg_10_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_CRDY_IDX, stat_seq_cfg_10_reg, statSeqSpiNandCfg->statSeqCRdyIdx);
            }

            /* Set ECC correction value */
            stat_seq_cfg_10_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_CORR_VAL, stat_seq_cfg_10_reg, statSeqSpiNandCfg->statSeqEccCorrVal);

            /* Set ECC fail value */
            stat_seq_cfg_10_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_FAIL_VAL, stat_seq_cfg_10_reg, statSeqSpiNandCfg->statSeqEccFailVal);

            /* Set ECC fail mask */
            stat_seq_cfg_10_reg = CPS_FLD_WRITE(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_FAIL_MASK, stat_seq_cfg_10_reg, statSeqSpiNandCfg->statSeqEccFailMask);

            CPS_REG_WRITE(&privateData->regs->stat_seq_cfg_10, stat_seq_cfg_10_reg);
        }
    }

    return result;
}

/**
 * Gets status sequence settings for NAND SPI devices (Since R003)
 * @param[in]  privateData Pointer to driver private data object
 * @param[out] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
 *
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if controller version is below R003
 */
uint32_t XSPI_GetStatSeqSpiNandConfig(XSPI_PrivateData * privateData, XSPI_StatSeqSpiNandConfig * statSeqSpiNandCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t stat_seq_cfg_10_reg = 0U;

    if (XSPI_GetStatSeqSpiNandConfigSF(privateData, statSeqSpiNandCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Check controller revision */
        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {

            /* Read stat seq config 10 register */
            stat_seq_cfg_10_reg = CPS_REG_READ(&privateData->regs->stat_seq_cfg_10);

            /* Get ECC fail enable */
            if (CPS_FLD_READ(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_FAIL_EN, stat_seq_cfg_10_reg) == 0U) {
                statSeqSpiNandCfg->statSeqEccFailEn = false;
            } else {
                statSeqSpiNandCfg->statSeqEccFailEn = true;
            }

            if (!privateData->xSpiIot) {
                /* Get cache busy bit index */
                statSeqSpiNandCfg->statSeqCRdyIdx = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_CRDY_IDX, stat_seq_cfg_10_reg);

                /* Get cache busy bit polarity value */
                result = GetSeqStatPolarityEnum(CPS_FLD_READ(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_CRDY_VAL, stat_seq_cfg_10_reg), &statSeqSpiNandCfg->statSeqCRdyVal);
            }

            if (result == CDN_EOK) {
                /* Get ECC correction value */
                statSeqSpiNandCfg->statSeqEccCorrVal = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_CORR_VAL, stat_seq_cfg_10_reg);

                /* Get ECC fail value and mask */
                statSeqSpiNandCfg->statSeqEccFailVal = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_FAIL_VAL, stat_seq_cfg_10_reg);
                statSeqSpiNandCfg->statSeqEccFailMask = (uint8_t)CPS_FLD_READ(XSPI__STAT_SEQ_CFG_10, STAT_SEQ_ECC_FAIL_MASK, stat_seq_cfg_10_reg);
            }
        }
    }

    return result;
}

/**
 * Sets global command parameters for SPI NAND devices (Since R003)
 * @param[in]  privateData Pointer to driver private data object
 * @param[in]  spiNandCmdParams SPI NAND global command parameters
 *
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if controller version is below R003
 */
uint32_t XSPI_SetSpiNandCmdParameters(XSPI_PrivateData * privateData, const XSPI_SpiNandGlobCmdParams * spiNandCmdParams)
{
    uint32_t result = CDN_EOK;
    uint32_t global_seq_cfg_1_reg;

    if (XSPI_SetSpiNandCmdParametersSF(privateData, spiNandCmdParams) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Check controller revision */
        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {
            /* Read global sequence parameters */
            global_seq_cfg_1_reg = CPS_REG_READ(&privateData->regs->global_seq_cfg_1);

            global_seq_cfg_1_reg = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PLANE_CNT, global_seq_cfg_1_reg, (uint32_t)spiNandCmdParams->planeCnt);
            global_seq_cfg_1_reg = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PAGE_PER_BLOCK, global_seq_cfg_1_reg, (uint32_t)spiNandCmdParams->pagesPerBlock);
            global_seq_cfg_1_reg = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PAGE_CA_SIZE, global_seq_cfg_1_reg, (uint32_t)spiNandCmdParams->pageCaSize);

            if (!privateData->xSpiIot) {
                global_seq_cfg_1_reg = CPS_FLD_WRITE(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PAGE_SIZE_EXT, global_seq_cfg_1_reg, (uint32_t)spiNandCmdParams->extPageSize);
            }

            /* Write global sequence parameters */
            CPS_REG_WRITE(&privateData->regs->global_seq_cfg_1, global_seq_cfg_1_reg);
        }
    }

    return result;
}

/**
 * Gets global command parameters for SPI NAND devices (Since R003)
 * @param[in]  privateData Pointer to driver private data object
 * @param[out] spiNandCmdParams SPI NAND global command parameters
 *
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if controller version is below R003
 */
uint32_t XSPI_GetSpiNandCmdParameters(XSPI_PrivateData * privateData, XSPI_SpiNandGlobCmdParams * spiNandCmdParams)
{
    uint32_t result = CDN_EOK;
    uint32_t global_seq_cfg_1_reg = 0U;

    if (XSPI_GetSpiNandCmdParametersSF(privateData, spiNandCmdParams) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Check controller revision */
        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {

            /* Read global sequence parameters */
            global_seq_cfg_1_reg = CPS_REG_READ(&privateData->regs->global_seq_cfg_1);

            spiNandCmdParams->pagesPerBlock = (uint8_t) CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PAGE_PER_BLOCK, global_seq_cfg_1_reg);

            if (!privateData->xSpiIot) {
                spiNandCmdParams->extPageSize  = (uint16_t) CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PAGE_SIZE_EXT, global_seq_cfg_1_reg);
            }

            /* Get Command/Address bit enum */
            result = GetCaSizeEnum(CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PAGE_CA_SIZE, global_seq_cfg_1_reg), &spiNandCmdParams->pageCaSize);

            if (result == CDN_EOK) {
                /* Get plane count */
                result = GetPlaneCntEnum(CPS_FLD_READ(XSPI__GLOBAL_SEQ_CFG_1, SEQ_PLANE_CNT, global_seq_cfg_1_reg), &spiNandCmdParams->planeCnt);
            }
        }
    }

    return result;
}


/* parasoft-end-suppress METRICS-36-3 */
