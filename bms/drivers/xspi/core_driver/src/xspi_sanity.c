/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.06.f48696b
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core driver for eXpanded Serial Peripheral Interface
 **********************************************************************/

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10, DRV-4789" */
/* parasoft-begin-suppress METRIC.CC-3 "Follow the Cyclomatic Complexity limit of 30, DRV-4417" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4, DRV-4790" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit, DRV-4139" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "xspi_regs.h"
#include "xspi_if.h"
#include "xspi_structs_if.h"
#include "xspi_priv.h"
#include "xspi_sanity.h"

/**
 * Function to validate struct DmaConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_DmaConfigSF(const XSPI_DmaConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->wordSize != XSPI_DMA_WORD_SIZE_BYTE) &&
            (obj->wordSize != XSPI_DMA_WORD_SIZE_16B_WORD) &&
            (obj->wordSize != XSPI_DMA_WORD_SIZE_32B_WORD) &&
            (obj->wordSize != XSPI_DMA_WORD_SIZE_64B_WORD)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct XipModeBitsConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_XipModeBitsConfigSF(const XSPI_XipModeBitsConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->xipEnableBanks > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct SpiNandGlobCmdParams
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_SpiNandGlobCmdParamsSF(const XSPI_SpiNandGlobCmdParams *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->planeCnt != XSPI_SPI_NAND_1_PLANE) &&
            (obj->planeCnt != XSPI_SPI_NAND_2_PLANES) &&
            (obj->planeCnt != XSPI_SPI_NAND_4_PLANES)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->pageCaSize != XSPI_SPI_NAND_CA_SIZE_12) &&
            (obj->pageCaSize != XSPI_SPI_NAND_CA_SIZE_13)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct GlobalCommandParameters
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_GlobalCommandParametersSF(const XSPI_GlobalCommandParameters *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->seqType != XSPI_SEQUENCE_TYPE_P1_SPI_NOR) &&
            (obj->seqType != XSPI_SEQUENCE_TYPE_P2_HYPER_FLASH) &&
            (obj->seqType != XSPI_SEQUENCE_TYPE_P2_HYPER_RAM) &&
            (obj->seqType != XSPI_SEQUENCE_TYPE_P1_SPI_NAND)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->dataPerAddress != XSPI_DATA_PER_ADDRESS_1B) &&
            (obj->dataPerAddress != XSPI_DATA_PER_ADDRESS_2B)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_4B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_8B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_16B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_32B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_64B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_128B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_256B) &&
            (obj->crcChunkSize != XSPI_CRC_CHUNK_SIZE_512B)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->crcVariant != XSPI_CRC_VARIANT_CALC_ADDR_PHASE) &&
            (obj->crcVariant != XSPI_CRC_VARIANT_CALC_ALL_PHASES)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_1B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_2B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_4B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_8B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_16B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_32B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_64B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_128B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_256B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_512B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_1024B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_2048B) &&
            (obj->pgmPageSize != XSPI_PROGRAM_PAGE_SIZE_4096B)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_1B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_2B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_4B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_8B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_16B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_32B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_64B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_128B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_256B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_512B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_1024B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_2048B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_4096B) &&
            (obj->rdPageSize != XSPI_READ_PAGE_SIZE_UNLIMITED)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DirectCmd
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_DirectCmdSF(const XSPI_DirectCmd *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->direction != XSPI_DATA_TRANS_DIR_READ) &&
            (obj->direction != XSPI_DATA_TRANS_DIR_WRITE)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DirectModeConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_DirectModeConfigSF(const XSPI_DirectModeConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dacAddrMask > (0x1FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->bankSelect > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ProgramSeqP1Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ProgramSeqP1ConfigSF(const XSPI_ProgramSeqP1Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (XSPI_SeqDataPhaseSF(&obj->progSeqData) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqAddressPhaseSF(&obj->progSeqAddr) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqCommandPhaseSF(&obj->progSeqCmd) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ProgramSeqP2Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ProgramSeqP2ConfigSF(const XSPI_ProgramSeqP2Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->progSeqTarget != XSPI_TARGET_SPACE_MEMORY) &&
            (obj->progSeqTarget != XSPI_TARGET_SPACE_REGISTER)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->progSeqBurstType != XSPI_BURST_TYPE_WRAPPED) &&
            (obj->progSeqBurstType != XSPI_BURST_TYPE_LINEAR)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ReadSeqP1Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ReadSeqP1ConfigSF(const XSPI_ReadSeqP1Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->readSeqDummyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqDataPhaseSF(&obj->readSeqData) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqAddressPhaseSF(&obj->readSeqAddr) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqCommandPhaseSF(&obj->readSeqCmd) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (obj->readSeqMbDummyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ReadSeqP2Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ReadSeqP2ConfigSF(const XSPI_ReadSeqP2Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->readSeqLatencyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->readSeqBurstType != XSPI_BURST_TYPE_WRAPPED) &&
            (obj->readSeqBurstType != XSPI_BURST_TYPE_LINEAR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->readSeqTarget != XSPI_TARGET_SPACE_MEMORY) &&
            (obj->readSeqTarget != XSPI_TARGET_SPACE_REGISTER)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct WelSeqConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_WelSeqConfigSF(const XSPI_WelSeqConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (XSPI_SeqCommandPhaseSF(&obj->welSeqCmd) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct StatSeqP1Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_StatSeqP1ConfigSF(const XSPI_StatSeqP1Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (XSPI_SeqDataPhaseSF(&obj->statSeqData) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqAddrEdge != XSPI_ADDR_EDGE_MODE_SDR) &&
            (obj->statSeqAddrEdge != XSPI_ADDR_EDGE_MODE_DDR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqAddrIos != XSPI_NUMBER_OF_IOS_1) &&
            (obj->statSeqAddrIos != XSPI_NUMBER_OF_IOS_2) &&
            (obj->statSeqAddrIos != XSPI_NUMBER_OF_IOS_4) &&
            (obj->statSeqAddrIos != XSPI_NUMBER_OF_IOS_8)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqAddrCnt != XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE) &&
            (obj->statSeqAddrCnt != XSPI_STAT_SEQ_ADDR_COUNT_2_ADDR_BYTES) &&
            (obj->statSeqAddrCnt != XSPI_STAT_SEQ_ADDR_COUNT_3_ADDR_BYTES) &&
            (obj->statSeqAddrCnt != XSPI_STAT_SEQ_ADDR_COUNT_4_ADDR_BYTES)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqCmdEdge != XSPI_CMD_EDGE_MODE_SDR) &&
            (obj->statSeqCmdEdge != XSPI_CMD_EDGE_MODE_DDR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqCmdIos != XSPI_NUMBER_OF_IOS_1) &&
            (obj->statSeqCmdIos != XSPI_NUMBER_OF_IOS_2) &&
            (obj->statSeqCmdIos != XSPI_NUMBER_OF_IOS_4) &&
            (obj->statSeqCmdIos != XSPI_NUMBER_OF_IOS_8)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->statSeqErsFailDummyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->statSeqProgFailDummyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->statSeqDevRdyDummyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct StatSeqP2Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_StatSeqP2ConfigSF(const XSPI_StatSeqP2Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->statSeqLatencyCnt > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct CommStatSeqConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_CommStatSeqConfigSF(const XSPI_CommStatSeqConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->statSeqProgFailSize != XSPI_STAT_STATUS_WORD_SIZE_8_BIT) &&
            (obj->statSeqProgFailSize != XSPI_STAT_STATUS_WORD_SIZE_16_BIT)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqProgFailVal != XSPI_STAT_POLARITY_0) &&
            (obj->statSeqProgFailVal != XSPI_STAT_POLARITY_1)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->statSeqProgFailIdx > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqErsFailSize != XSPI_STAT_STATUS_WORD_SIZE_8_BIT) &&
            (obj->statSeqErsFailSize != XSPI_STAT_STATUS_WORD_SIZE_16_BIT)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqErsFailVal != XSPI_STAT_POLARITY_0) &&
            (obj->statSeqErsFailVal != XSPI_STAT_POLARITY_1)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->statSeqErsFailIdx > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqDevRdySize != XSPI_STAT_STATUS_WORD_SIZE_8_BIT) &&
            (obj->statSeqDevRdySize != XSPI_STAT_STATUS_WORD_SIZE_16_BIT)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->statSeqDevRdyVal != XSPI_STAT_POLARITY_0) &&
            (obj->statSeqDevRdyVal != XSPI_STAT_POLARITY_1)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->statSeqDevRdyIdx > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct StatSeqSpiNandConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_StatSeqSpiNandConfigSF(const XSPI_StatSeqSpiNandConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->statSeqCRdyVal != XSPI_STAT_POLARITY_0) &&
            (obj->statSeqCRdyVal != XSPI_STAT_POLARITY_1)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ResetDeviceConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ResetDeviceConfigSF(const XSPI_ResetDeviceConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->hwResetType != XSPI_HARDWARE_RESET_OPTION_RESET_PIN) &&
            (obj->hwResetType != XSPI_HARDWARE_RESET_OPTION_DQ3_PIN)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DeviceRelativeDelays
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_DeviceRelativeDelaysSF(const XSPI_DeviceRelativeDelays *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct JedecResetTimingConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_JedecResetTimingConfigSF(const XSPI_JedecResetTimingConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ConfigSF(const XSPI_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct PollingConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_PollingConfigSF(const XSPI_PollingConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct DeviceDiscoveryConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_DeviceDiscoveryConfigSF(const XSPI_DeviceDiscoveryConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->bankSelect > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->numLines != XSPI_DEV_DISC_LINES_AUTO) &&
            (obj->numLines != XSPI_DEV_DISC_LINES_1L) &&
            (obj->numLines != XSPI_DEV_DISC_LINES_2L) &&
            (obj->numLines != XSPI_DEV_DISC_LINES_4L) &&
            (obj->numLines != XSPI_DEV_DISC_LINES_8L) &&
            (obj->numLines != XSPI_DEV_DISC_LINES_8L_P2) &&
            (obj->numLines != XSPI_DEV_DISC_LINES_1L_SPI_NAND)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->reqType != XSPI_DEV_DISC_REQ_TYPE_FULL_DISCOVERY) &&
            (obj->reqType != XSPI_DEV_DISC_REQ_TYPE_CONFIGURE_REGISTERS_ONLY)
        )
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_DevDiscParamsP1SF(&obj->p1Config) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ResetSeqConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ResetSeqConfigSF(const XSPI_ResetSeqConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->rstSeqCmdEdge != XSPI_CMD_EDGE_MODE_SDR) &&
            (obj->rstSeqCmdEdge != XSPI_CMD_EDGE_MODE_DDR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->rstSeqCmdIos != XSPI_NUMBER_OF_IOS_1) &&
            (obj->rstSeqCmdIos != XSPI_NUMBER_OF_IOS_2) &&
            (obj->rstSeqCmdIos != XSPI_NUMBER_OF_IOS_4) &&
            (obj->rstSeqCmdIos != XSPI_NUMBER_OF_IOS_8)
        )
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqDataPhaseSF(&obj->rstSeqData) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct EraseSecSeqConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_EraseSecSeqConfigSF(const XSPI_EraseSecSeqConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (XSPI_SeqAddressPhaseSF(&obj->erssSeqAddr) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (XSPI_SeqCommandPhaseSF(&obj->erssSeqCmd) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_1B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_2B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_4B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_8B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_16B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_32B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_64B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_128B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_256B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_512B) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_1KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_2KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_4KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_8KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_16KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_32KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_64KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_128KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_256KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_512KB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_1MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_2MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_4MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_8MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_16MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_32MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_64MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_128MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_256MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_512MB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_1GB) &&
            (obj->erssSeqSecSize != XSPI_ERASE_SEQ_SEC_SIZE_2GB)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ChipEraseSeqConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_ChipEraseSeqConfigSF(const XSPI_ChipEraseSeqConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (XSPI_SeqCommandPhaseSF(&obj->ersaSeqCmd) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct HyperFlashOffsetConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_HyperFlashOffsetConfigSF(const XSPI_HyperFlashOffsetConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->offsetSize > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->offsetIndex > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_PhyConfigSF(const XSPI_PhyConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dfiCtrlUpdtReq > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->sdrActiveEdge != XSPI_SDR_ACTIVE_EDGE_POSITIVE) &&
            (obj->sdrActiveEdge != XSPI_SDR_ACTIVE_EDGE_NEGATIVE)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsLastDataDropEn > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->resyncHighWaitCount > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PrivateData
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_PrivateDataSF(const XSPI_PrivateData *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (XSPI_CtrlFeaturesInfoSF(&obj->ctrlFeatures) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->ctrlRev != XSPI_CTRL_REV_R001) &&
            (obj->ctrlRev != XSPI_CTRL_REV_R002) &&
            (obj->ctrlRev != XSPI_CTRL_REV_R003) &&
            (obj->ctrlRev != XSPI_CTRL_REV_R004)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct SeqCommandPhase
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_SeqCommandPhaseSF(const XSPI_SeqCommandPhase *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->edge != XSPI_CMD_EDGE_MODE_SDR) &&
            (obj->edge != XSPI_CMD_EDGE_MODE_DDR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->ios != XSPI_NUMBER_OF_IOS_1) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_2) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_4) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_8)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct SeqAddressPhase
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_SeqAddressPhaseSF(const XSPI_SeqAddressPhase *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->edge != XSPI_ADDR_EDGE_MODE_SDR) &&
            (obj->edge != XSPI_ADDR_EDGE_MODE_DDR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->ios != XSPI_NUMBER_OF_IOS_1) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_2) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_4) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_8)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->count > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct SeqDataPhase
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_SeqDataPhaseSF(const XSPI_SeqDataPhase *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->edge != XSPI_DATA_EDGE_MODE_SDR) &&
            (obj->edge != XSPI_DATA_EDGE_MODE_DDR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->ios != XSPI_NUMBER_OF_IOS_1) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_2) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_4) &&
            (obj->ios != XSPI_NUMBER_OF_IOS_8)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct CtrlFeaturesInfo
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_CtrlFeaturesInfoSF(const XSPI_CtrlFeaturesInfo *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->dmaDataWidth != XSPI_DMA_DATA_WIDTH_32B) &&
            (obj->dmaDataWidth != XSPI_DMA_DATA_WIDTH_64B)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->dmaAddrWidth != XSPI_DMA_ADDR_WIDTH_32B) &&
            (obj->dmaAddrWidth != XSPI_DMA_ADDR_WIDTH_64B)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DevDiscParamsP1
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t XSPI_DevDiscParamsP1SF(const XSPI_DevDiscParamsP1 *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->discoveryDummyCnt != XSPI_DEV_DISC_EIGHT_CLOCK_CYCLES) &&
            (obj->discoveryDummyCnt != XSPI_DEV_DISC_TWENTY_CLOCK_CYCLES)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->cmdType != XSPI_DEV_DISC_CMD_SDR_MODE) &&
            (obj->cmdType != XSPI_DEV_DISC_CMD_DDR_MODE) &&
            (obj->cmdType != XSPI_DEV_DISC_CMD_DTR_MODE)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->extendOpCodeVal != XSPI_DEV_DISC_EXT_OPCODE_A5) &&
            (obj->extendOpCodeVal != XSPI_DEV_DISC_EXT_OPCODE_5A)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] config Driver/hardware configuration required.
 * @param[out] sysReq Returns the size of memory allocations required.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction1(const XSPI_Config* config, const XSPI_SysReq* sysReq)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (sysReq == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Memory pointer to the uninitialized private data of the size specified by probe.
 * @param[in] config Specifies driver/hardware configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction2(const XSPI_PrivateData* privateData, const XSPI_Config* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction3(const XSPI_PrivateData* privateData)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] workMode Controller work mode to be set
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction7(const XSPI_PrivateData* privateData, const XSPI_WorkMode workMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (workMode != XSPI_WORK_MODE_DIRECT) &&
        (workMode != XSPI_WORK_MODE_STIG) &&
        (workMode != XSPI_WORK_MODE_UNKNOWN) &&
        (workMode != XSPI_WORK_MODE_AUTO_COMMAND)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] workMode Controller work mode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction8(const XSPI_PrivateData* privateData, const XSPI_WorkMode* workMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (workMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] events Enabled events
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction10(const XSPI_PrivateData* privateData, const uint32_t* events)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (events == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] callbacks Returns registered callbacks
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction12(const XSPI_PrivateData* privateData, const XSPI_Callbacks* callbacks)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (callbacks == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] writeProtectEnabled Write protect state
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction14(const XSPI_PrivateData* privateData, const bool* writeProtectEnabled)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (writeProtectEnabled == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] dmaConfig DMA configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction15(const XSPI_PrivateData* privateData, const XSPI_DmaConfig* dmaConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_DmaConfigSF(dmaConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] dmaConfig DMA configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction16(const XSPI_PrivateData* privateData, const XSPI_DmaConfig* dmaConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (dmaConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] spiClockMode SPI clock mode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction17(const XSPI_PrivateData* privateData, const XSPI_SpiClockMode spiClockMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (spiClockMode != XSPI_SPI_CLOCK_MODE_0) &&
        (spiClockMode != XSPI_SPI_CLOCK_MODE_3)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] spiClockMode SPI clock mode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction18(const XSPI_PrivateData* privateData, const XSPI_SpiClockMode* spiClockMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (spiClockMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetBankCfg Reset configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction19(const XSPI_PrivateData* privateData, const XSPI_ResetDeviceConfig* resetBankCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ResetDeviceConfigSF(resetBankCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] deviceRelativeDelays Device relative delays
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction23(const XSPI_PrivateData* privateData, const XSPI_DeviceRelativeDelays* deviceRelativeDelays)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_DeviceRelativeDelaysSF(deviceRelativeDelays) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceRelativeDelays Device relative delays
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction24(const XSPI_PrivateData* privateData, const XSPI_DeviceRelativeDelays* deviceRelativeDelays)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (deviceRelativeDelays == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] globalCmdParameters Global command parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction25(const XSPI_PrivateData* privateData, const XSPI_GlobalCommandParameters* globalCmdParameters)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_GlobalCommandParametersSF(globalCmdParameters) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] globalCmdParameters Global command parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction26(const XSPI_PrivateData* privateData, const XSPI_GlobalCommandParameters* globalCmdParameters)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (globalCmdParameters == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] spiNandCmdParams SPI NAND global command parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction27(const XSPI_PrivateData* privateData, const XSPI_SpiNandGlobCmdParams* spiNandCmdParams)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_SpiNandGlobCmdParamsSF(spiNandCmdParams) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] spiNandCmdParams SPI NAND global command parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction28(const XSPI_PrivateData* privateData, const XSPI_SpiNandGlobCmdParams* spiNandCmdParams)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (spiNandCmdParams == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] xipModeBitsConfig XIP mode bits config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction29(const XSPI_PrivateData* privateData, const XSPI_XipModeBitsConfig* xipModeBitsConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_XipModeBitsConfigSF(xipModeBitsConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] xipModeBitsConfig XIP mode bits config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction30(const XSPI_PrivateData* privateData, const XSPI_XipModeBitsConfig* xipModeBitsConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (xipModeBitsConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] directCmd Pointer to direct mode command structure
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction31(const XSPI_PrivateData* privateData, const XSPI_DirectCmd* directCmd)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_DirectCmdSF(directCmd) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] directModeConfig Pointer to direct mode config structure
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction33(const XSPI_PrivateData* privateData, const XSPI_DirectModeConfig* directModeConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_DirectModeConfigSF(directModeConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] directModeConfig Pointer to direct mode config structure
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction34(const XSPI_PrivateData* privateData, const XSPI_DirectModeConfig* directModeConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (directModeConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] progSeqP1Cfg PROGRAM P1 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction37(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP1Config* progSeqP1Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ProgramSeqP1ConfigSF(progSeqP1Cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] progSeqP1Cfg PROGRAM P1 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction38(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP1Config* progSeqP1Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (progSeqP1Cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] progSeqP2Cfg PROGRAM P2 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction39(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP2Config* progSeqP2Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ProgramSeqP2ConfigSF(progSeqP2Cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] progSeqP2Cfg PROGRAM P2 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction40(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP2Config* progSeqP2Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (progSeqP2Cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] readSeqP1Cfg READ P1 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction41(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP1Config* readSeqP1Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ReadSeqP1ConfigSF(readSeqP1Cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] readSeqP1Cfg READ P1 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction42(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP1Config* readSeqP1Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (readSeqP1Cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] readSeqP2Cfg READ P2 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction43(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP2Config* readSeqP2Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ReadSeqP2ConfigSF(readSeqP2Cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] readSeqP2Cfg READ P2 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction44(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP2Config* readSeqP2Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (readSeqP2Cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] welSeqCfg WEL sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction45(const XSPI_PrivateData* privateData, const XSPI_WelSeqConfig* welSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_WelSeqConfigSF(welSeqCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] welSeqCfg WEL sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction46(const XSPI_PrivateData* privateData, const XSPI_WelSeqConfig* welSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (welSeqCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] commStatSeqConfig Common STAT sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction47(const XSPI_PrivateData* privateData, const XSPI_CommStatSeqConfig* commStatSeqConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_CommStatSeqConfigSF(commStatSeqConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] commStatSeqConfig Common STAT sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction48(const XSPI_PrivateData* privateData, const XSPI_CommStatSeqConfig* commStatSeqConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (commStatSeqConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqP1Cfg STAT P1 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction49(const XSPI_PrivateData* privateData, const XSPI_StatSeqP1Config* statSeqP1Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_StatSeqP1ConfigSF(statSeqP1Cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqP1Cfg STAT P1 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction50(const XSPI_PrivateData* privateData, const XSPI_StatSeqP1Config* statSeqP1Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (statSeqP1Cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqP2Cfg STAT P2 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction51(const XSPI_PrivateData* privateData, const XSPI_StatSeqP2Config* statSeqP2Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_StatSeqP2ConfigSF(statSeqP2Cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqP2Cfg STAT P2 sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction52(const XSPI_PrivateData* privateData, const XSPI_StatSeqP2Config* statSeqP2Cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (statSeqP2Cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction53(const XSPI_PrivateData* privateData, const XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_StatSeqSpiNandConfigSF(statSeqSpiNandCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction54(const XSPI_PrivateData* privateData, const XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (statSeqSpiNandCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] stigCommand Pointer to STIG command
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction55(const XSPI_PrivateData* privateData, const XSPI_StigCommand* stigCommand)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (stigCommand == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] stigCommand Stig command containing status information
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction56(const XSPI_PrivateData* privateData, const XSPI_StigCommand* stigCommand)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (stigCommand == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] jedecRstTiming JEDEC RESET timing config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction57(const XSPI_PrivateData* privateData, const XSPI_JedecResetTimingConfig* jedecRstTiming)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_JedecResetTimingConfigSF(jedecRstTiming) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] jedecRstTiming JEDEC RESET timing config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction58(const XSPI_PrivateData* privateData, const XSPI_JedecResetTimingConfig* jedecRstTiming)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (jedecRstTiming == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] bootStatus Latest boot operation status
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction62(const XSPI_PrivateData* privateData, const XSPI_LatestBootStatus* bootStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (bootStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] deviceDiscoveryConfig Device discovery config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction63(const XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_DeviceDiscoveryConfigSF(deviceDiscoveryConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceDiscoveryConfig Device discovery config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction64(const XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (deviceDiscoveryConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceDiscoveryStatus Status of device discovery operation
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction66(const XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryStatus* deviceDiscoveryStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (deviceDiscoveryStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] pollingConfig Polling configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction69(const XSPI_PrivateData* privateData, const XSPI_PollingConfig* pollingConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PollingConfigSF(pollingConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] pollingConfig Polling configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction70(const XSPI_PrivateData* privateData, const XSPI_PollingConfig* pollingConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pollingConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] hfOffsetCfg HyperFlash offset config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction71(const XSPI_PrivateData* privateData, const XSPI_HyperFlashOffsetConfig* hfOffsetCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_HyperFlashOffsetConfigSF(hfOffsetCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] hfOffsetCfg HyperFlash offset config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction72(const XSPI_PrivateData* privateData, const XSPI_HyperFlashOffsetConfig* hfOffsetCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (hfOffsetCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] phyConfig PHY configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction73(const XSPI_PrivateData* privateData, const XSPI_PhyConfig* phyConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PhyConfigSF(phyConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] phyConfig PHY configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction74(const XSPI_PrivateData* privateData, const XSPI_PhyConfig* phyConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (phyConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] dllReset DLL reset value
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction75(const XSPI_PrivateData* privateData, const uint8_t dllReset)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (dllReset > (0x1U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] cdmaCmd Pointer to CDMA command
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction76(const XSPI_PrivateData* privateData, const XSPI_CdmaCommand* cdmaCmd)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cdmaCmd == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] cdmaCmdChain Pointer to CDMA commands chain structure
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction78(const XSPI_PrivateData* privateData, const XSPI_CdmaCommandChain* cdmaCmdChain)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cdmaCmdChain == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] pioCmd Pointer to PIO command
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction80(const XSPI_PrivateData* privateData, const XSPI_PioCommand* pioCmd)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pioCmd == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] cmdStatus Pointer to command status structure
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction82(const XSPI_PrivateData* privateData, const XSPI_CommandStatusInfo* cmdStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cmdStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetSeqCfg RESET sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction83(const XSPI_PrivateData* privateData, const XSPI_ResetSeqConfig* resetSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ResetSeqConfigSF(resetSeqCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] resetSeqCfg RESET sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction84(const XSPI_PrivateData* privateData, const XSPI_ResetSeqConfig* resetSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (resetSeqCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] eraseSecSeqCfg ERASE SECTOR sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction85(const XSPI_PrivateData* privateData, const XSPI_EraseSecSeqConfig* eraseSecSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_EraseSecSeqConfigSF(eraseSecSeqCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] eraseSecSeqCfg ERASE SECTOR sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction86(const XSPI_PrivateData* privateData, const XSPI_EraseSecSeqConfig* eraseSecSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (eraseSecSeqCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[in] chipEraseSeqCfg CHIP ERASE sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction87(const XSPI_PrivateData* privateData, const XSPI_ChipEraseSeqConfig* chipEraseSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_ChipEraseSeqConfigSF(chipEraseSeqCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] privateData Pointer to driver private data object
 * @param[out] chipEraseSeqCfg CHIP ERASE sequence config
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t XSPI_SanityFunction88(const XSPI_PrivateData* privateData, const XSPI_ChipEraseSeqConfig* chipEraseSeqCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (chipEraseSeqCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (XSPI_PrivateDataSF(privateData) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
