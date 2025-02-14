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
 * xspi_core.c
 *****************************************************************************/
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <cps.h>
#include <cdn_log.h>
#include <cdn_errno.h>

#include "xspi_if.h"
#include "xspi_structs_if.h"

#include "xspi_priv.h"
#include "xspi_sanity.h"
#include "xspi_core.h"
#include "xspi_seq.h"

#include "xspi_full_addons.h"

/**
 * Internal function
 * Function waits till Auto Command Engine thread is busy.
 */
static uint32_t WaitForThread(XSPI_PrivateData * privateData, uint8_t thread)
{
    return WaitForRegValueMatch(&privateData->regs->trd_status,
        thread, 1U, 0, 10000U);
}

uint32_t XSPI_SetResetRecoveryDelay(XSPI_PrivateData * privateData, uint32_t resetRecoveryDelay)
{
    uint32_t result = CDN_EOK;
    uint32_t rst_recov_reg = 0U;

    if (XSPI_SetResetRecoveryDelaySF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        rst_recov_reg = CPS_FLD_WRITE(XSPI__RST_RECOVERY_REG, RST_RECOVERY, rst_recov_reg, resetRecoveryDelay);

        CPS_REG_WRITE(&privateData->regs->rst_recovery_reg, rst_recov_reg);
    }

    return result;
}

uint32_t XSPI_GetResetRecoveryDelay(XSPI_PrivateData * privateData, uint32_t * resetRecoveryDelay)
{
    uint32_t result = CDN_EOK;
    uint32_t rst_recov_reg = 0U;

    if (XSPI_GetResetRecoveryDelaySF(privateData, resetRecoveryDelay) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        rst_recov_reg = CPS_REG_READ(&privateData->regs->rst_recovery_reg);

        *resetRecoveryDelay = (uint32_t) CPS_FLD_READ(XSPI__RST_RECOVERY_REG, RST_RECOVERY, rst_recov_reg);
    }

    return result;
}

/**
 * Sets continue processing on descriptor error state
 * @param[in] privateData Pointer to driver private data object
 * @param[in] procOnErrEnabled Continue processing on descriptor error
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetContinueProcOnDescError(XSPI_PrivateData * privateData, bool procOnErrEnabled)
{
    uint32_t ctr_cfg_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetContinueProcOnDescErSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Wait for controller to be in IDLE state */
        result = WaitForIdle(privateData);

        ctr_cfg_reg = CPS_REG_READ(&privateData->regs->ctrl_config);

        ctr_cfg_reg = CPS_FLD_WRITE(XSPI__CTRL_CONFIG, CONT_ON_ERR, ctr_cfg_reg, ((procOnErrEnabled == true) ? 1U : 0U));

        CPS_REG_WRITE(&privateData->regs->ctrl_config, ctr_cfg_reg);
    }

    return result;
}

/**
 * Gets continue processing on descriptor error state
 * @param[in] privateData Pointer to driver private data object
 * @param[out] procOnErrEnabled Continue processing on descriptor error
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetContinueProcOnDescError(XSPI_PrivateData * privateData, bool * procOnErrEnabled)
{
    uint32_t ctr_cfg_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetContinueProcOnDescErSF(privateData, procOnErrEnabled) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        ctr_cfg_reg = CPS_REG_READ(&privateData->regs->ctrl_config);

        if (CPS_FLD_READ(XSPI__CTRL_CONFIG, CONT_ON_ERR, ctr_cfg_reg) == 0U) {
            *procOnErrEnabled = false;
        } else {
            *procOnErrEnabled = true;
        }
    }

    return result;
}

/**
 * Gets latest boot operation status
 * @param[in] privateData Pointer to driver private data object
 * @param[out] bootStatus Latest boot operation status
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetLatestBootStatus(XSPI_PrivateData *privateData, XSPI_LatestBootStatus *bootStatus)
{
    uint32_t boot_status_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetLatestBootStatusSF(privateData, bootStatus) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        boot_status_reg = CPS_REG_READ(&privateData->regs->boot_status);

        /* Get boot status */
        if (CPS_FLD_READ(XSPI__BOOT_STATUS, BOOT_BUS_ERR, boot_status_reg) == 0U) {
            bootStatus->busError = false;
        } else {
            bootStatus->busError = true;
        }

        if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {

            if (CPS_FLD_READ(XSPI__BOOT_STATUS, BOOT_CRC_ERR, boot_status_reg) == 1U) {
                bootStatus->crcError = true;
            } else {
                bootStatus->crcError = false;
            }

            if (CPS_FLD_READ(XSPI__BOOT_STATUS, BOOT_DQS_ERR, boot_status_reg) == 1U) {
                bootStatus->dqsError = true;
            } else {
                bootStatus->dqsError = false;
            }
        }
    }

    return result;
}

static uint32_t GetErsSectorSizeEnum(const uint32_t val, XSPI_EraseSeqSectorSize * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_EraseSeqSectorSize numOfSectSizeEnums[NUM_OF_SECT_SIZE_ENUM_CNT] = {
        [0U] = XSPI_ERASE_SEQ_SEC_SIZE_1B,
        [1U] = XSPI_ERASE_SEQ_SEC_SIZE_2B,
        [2U] = XSPI_ERASE_SEQ_SEC_SIZE_4B,
        [3U] = XSPI_ERASE_SEQ_SEC_SIZE_8B,
        [4U] = XSPI_ERASE_SEQ_SEC_SIZE_16B,
        [5U] = XSPI_ERASE_SEQ_SEC_SIZE_32B,
        [6U] = XSPI_ERASE_SEQ_SEC_SIZE_64B,
        [7U] = XSPI_ERASE_SEQ_SEC_SIZE_128B,
        [8U] = XSPI_ERASE_SEQ_SEC_SIZE_256B,
        [9U] = XSPI_ERASE_SEQ_SEC_SIZE_512B,
        [10U] = XSPI_ERASE_SEQ_SEC_SIZE_1KB,
        [11U] = XSPI_ERASE_SEQ_SEC_SIZE_2KB,
        [12U] = XSPI_ERASE_SEQ_SEC_SIZE_4KB,
        [13U] = XSPI_ERASE_SEQ_SEC_SIZE_8KB,
        [14U] = XSPI_ERASE_SEQ_SEC_SIZE_16KB,
        [15U] = XSPI_ERASE_SEQ_SEC_SIZE_32KB,
        [16U] = XSPI_ERASE_SEQ_SEC_SIZE_64KB,
        [17U] = XSPI_ERASE_SEQ_SEC_SIZE_128KB,
        [18U] = XSPI_ERASE_SEQ_SEC_SIZE_256KB,
        [19U] = XSPI_ERASE_SEQ_SEC_SIZE_512KB,
        [20U] = XSPI_ERASE_SEQ_SEC_SIZE_1MB,
        [21U] = XSPI_ERASE_SEQ_SEC_SIZE_2MB,
        [22U] = XSPI_ERASE_SEQ_SEC_SIZE_4MB,
        [23U] = XSPI_ERASE_SEQ_SEC_SIZE_8MB,
        [24U] = XSPI_ERASE_SEQ_SEC_SIZE_16MB,
        [25U] = XSPI_ERASE_SEQ_SEC_SIZE_32MB,
        [26U] = XSPI_ERASE_SEQ_SEC_SIZE_64MB,
        [27U] = XSPI_ERASE_SEQ_SEC_SIZE_128MB,
        [28U] = XSPI_ERASE_SEQ_SEC_SIZE_256MB,
        [29U] = XSPI_ERASE_SEQ_SEC_SIZE_512MB,
        [30U] = XSPI_ERASE_SEQ_SEC_SIZE_1GB,
        [31U] = XSPI_ERASE_SEQ_SEC_SIZE_2GB,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < NUM_OF_SECT_SIZE_ENUM_CNT; ++i) {
        if ((uint32_t) numOfSectSizeEnums[i] == val) {
            *enumVal = numOfSectSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static void SetDevDiscConfigP2(const XSPI_DeviceDiscoveryConfig *deviceDiscoveryConfig, uint32_t *dd_reg)
{
    uint8_t latencyCnt = 0U;
    uint8_t dummyCnt = 0U;
    uint8_t cmdType = 0U;
    uint8_t extopEn = 0U;
    uint8_t extopVal = 0U;

    /* Set latency clock cycles count */
    if (deviceDiscoveryConfig->p2Config.latencyCnt != 0U) {
        latencyCnt = deviceDiscoveryConfig->p2Config.latencyCnt - 1U;
    }

    dummyCnt = (latencyCnt >> P2_DISC_LATENCY_DUMMY_CNT_SHIFT) & P2_DISC_LATENCY_DUMMY_CNT_WIDTH;
    cmdType = (latencyCnt >> P2_DISC_LATENCY_CMD_TYPE_SHIFT) & P2_DISC_LATENCY_CMD_TYPE_WIDTH;
    extopEn = (latencyCnt >> P2_DISC_LATENCY_EXTOP_EN_SHIFT) & P2_DISC_LATENCY_EXTOP_EN_WIDTH;
    extopVal = (latencyCnt >> P2_DISC_LATENCY_EXTOP_VAL_SHIFT) & P2_DISC_LATENCY_EXTOP_VAL_WIDTH;

    /* Calculate register value for P2 discovery configuration */
    *dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_ABNUM, *dd_reg, ((deviceDiscoveryConfig->p2Config.hfBoundEn == true) ? 1U : 0U));
    *dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_DUMMY_CNT, *dd_reg, dummyCnt);
    *dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_CMD_TYPE, *dd_reg, cmdType);
    *dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_EN, *dd_reg, extopEn);
    *dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_VAL, *dd_reg, extopVal);
}

/**
 * Sets device discovery config
 * @param[in] privateData Pointer to driver private data object
 * @param[in] deviceDiscoveryConfig Device discovery config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetDeviceDiscoveryConfig(XSPI_PrivateData *privateData, const XSPI_DeviceDiscoveryConfig *deviceDiscoveryConfig)
{
    uint32_t dd_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetDeviceDiscoveryConfiSF(privateData, deviceDiscoveryConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Read original device discovery config */
        dd_reg = CPS_REG_READ(&privateData->regs->discovery_control);

        dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_BANK, dd_reg, deviceDiscoveryConfig->bankSelect);
        dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_NUM_LINES, dd_reg, deviceDiscoveryConfig->numLines);

        if (deviceDiscoveryConfig->numLines == XSPI_DEV_DISC_LINES_8L_P2) {
            SetDevDiscConfigP2(deviceDiscoveryConfig, &dd_reg);
        } else {
            dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_ABNUM, dd_reg, ((deviceDiscoveryConfig->p1Config.enable4bAddr == true) ? 1U : 0U));
            dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_DUMMY_CNT, dd_reg, deviceDiscoveryConfig->p1Config.discoveryDummyCnt);
            dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_CMD_TYPE, dd_reg, deviceDiscoveryConfig->p1Config.cmdType);
            dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_EN, dd_reg, ((deviceDiscoveryConfig->p1Config.enableExtendOpCode == true) ? 1U : 0U));
            dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_VAL, dd_reg, deviceDiscoveryConfig->p1Config.extendOpCodeVal);
        }

        dd_reg = CPS_FLD_WRITE(XSPI__DISCOVERY_CONTROL, DISCOVERY_REQ_TYPE, dd_reg, deviceDiscoveryConfig->reqType);

        /* Write new device discovery config */
        CPS_REG_WRITE(&privateData->regs->discovery_control, dd_reg);
    }

    return result;
}

/* Internal function */
static uint32_t GetDiscoveryNumLinesEnum(const uint32_t val, XSPI_DeviceDiscoveryLines * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_DeviceDiscoveryLines discoveryNumLinesEnums[DISCOVERY_LINES_ENUM_CNT] = {
        [0U] = XSPI_DEV_DISC_LINES_AUTO,
        [1U] = XSPI_DEV_DISC_LINES_1L, 
        [2U] = XSPI_DEV_DISC_LINES_2L,
        [3U] = XSPI_DEV_DISC_LINES_4L,
        [4U] = XSPI_DEV_DISC_LINES_8L,
        [5U] = XSPI_DEV_DISC_LINES_8L_P2,
        [6U] = XSPI_DEV_DISC_LINES_1L_SPI_NAND,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < DISCOVERY_LINES_ENUM_CNT; ++i) {
        if ((uint32_t) discoveryNumLinesEnums[i] == val) {
            *enumVal = discoveryNumLinesEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static uint32_t GetDiscoveryCmdTypeEnum(const uint32_t val, XSPI_DeviceDiscoveryCmdType * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_DeviceDiscoveryCmdType discoveryCmdTypeEnums[DISCOVERY_CMD_TYPE_ENUM_CNT] = {
        [0U] = XSPI_DEV_DISC_CMD_SDR_MODE,
        [1U] = XSPI_DEV_DISC_CMD_DDR_MODE, 
        [2U] = XSPI_DEV_DISC_CMD_DTR_MODE,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < DISCOVERY_CMD_TYPE_ENUM_CNT; ++i) {
        if ((uint32_t) discoveryCmdTypeEnums[i] == val) {
            *enumVal = discoveryCmdTypeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Internal function */
static void GetDevDiscConfigP2(XSPI_DeviceDiscoveryConfig *deviceDiscoveryConfig, uint32_t dd_reg)
{
    uint8_t latencyCnt;
    uint8_t dummyCnt;
    uint8_t cmdType;
    uint8_t extopEn;
    uint8_t extopVal;

    dummyCnt = (uint8_t) CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_DUMMY_CNT, dd_reg);
    cmdType = (uint8_t) CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_CMD_TYPE, dd_reg);
    extopEn = (uint8_t) CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_EN, dd_reg);
    extopVal = (uint8_t) CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_VAL, dd_reg);

    /* Get latency clock cycles count */
    latencyCnt = (extopVal << P2_DISC_LATENCY_EXTOP_VAL_SHIFT) |
                 (extopEn << P2_DISC_LATENCY_EXTOP_EN_SHIFT)   |
                 (cmdType << P2_DISC_LATENCY_CMD_TYPE_SHIFT)   |
                 (dummyCnt << P2_DISC_LATENCY_DUMMY_CNT_SHIFT);

    deviceDiscoveryConfig->p2Config.latencyCnt = latencyCnt + 1U;

    /* Get inter-page crossing enable for hyperflash */
    if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_ABNUM, dd_reg) == 0U) {
        deviceDiscoveryConfig->p2Config.hfBoundEn = false;
    } else {
        deviceDiscoveryConfig->p2Config.hfBoundEn = true;
    }
}

/* Internal function */
static uint32_t GetDevDiscConfigP1(XSPI_DeviceDiscoveryConfig *deviceDiscoveryConfig, uint32_t dd_reg)
{
    uint32_t result = CDN_EOK;

    /* Get address bytes information */
    if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_ABNUM, dd_reg) == 0U) {
        deviceDiscoveryConfig->p1Config.enable4bAddr = false;
    } else {
        deviceDiscoveryConfig->p1Config.enable4bAddr = true;
    }

    /* Get number of dummy clock cycles */
    if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_DUMMY_CNT, dd_reg) == 1U) {
        deviceDiscoveryConfig->p1Config.discoveryDummyCnt = XSPI_DEV_DISC_TWENTY_CLOCK_CYCLES;
    } else {
        deviceDiscoveryConfig->p1Config.discoveryDummyCnt = XSPI_DEV_DISC_EIGHT_CLOCK_CYCLES;
    }

    result = GetDiscoveryCmdTypeEnum(CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_CMD_TYPE, dd_reg), &deviceDiscoveryConfig->p1Config.cmdType);

    /* Get extended opcode enable information */
    if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_EN, dd_reg) == 0U) {
        deviceDiscoveryConfig->p1Config.enableExtendOpCode = false;
    } else {
        deviceDiscoveryConfig->p1Config.enableExtendOpCode = true;
    }

    /* Get extended opcode value  */
    if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_EXTOP_VAL, dd_reg) == 1U) {
        deviceDiscoveryConfig->p1Config.extendOpCodeVal = XSPI_DEV_DISC_EXT_OPCODE_5A;
    } else {
        deviceDiscoveryConfig->p1Config.extendOpCodeVal = XSPI_DEV_DISC_EXT_OPCODE_A5;
    }

    return result;
}

/**
 * Gets device discovery config
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceDiscoveryConfig Device discovery config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetDeviceDiscoveryConfig(XSPI_PrivateData *privateData, XSPI_DeviceDiscoveryConfig *deviceDiscoveryConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t dd_reg;

    /* Check parameters */
    if (XSPI_GetDeviceDiscoveryConfiSF(privateData, deviceDiscoveryConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Read register */
        dd_reg = CPS_REG_READ(&privateData->regs->discovery_control);

        deviceDiscoveryConfig->bankSelect = (uint8_t) CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_BANK, dd_reg);

        /* Get discovery mode */
        result = GetDiscoveryNumLinesEnum(CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_NUM_LINES, dd_reg), &deviceDiscoveryConfig->numLines);

        if (deviceDiscoveryConfig->numLines == XSPI_DEV_DISC_LINES_8L_P2) {
            GetDevDiscConfigP2(deviceDiscoveryConfig, dd_reg);
        } else {
            result |= GetDevDiscConfigP1(deviceDiscoveryConfig, dd_reg);
        }

        /* Get discovery request type */
        if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_REQ_TYPE, dd_reg) == 1U) {
            deviceDiscoveryConfig->reqType = XSPI_DEV_DISC_REQ_TYPE_CONFIGURE_REGISTERS_ONLY;
        } else {
            deviceDiscoveryConfig->reqType = XSPI_DEV_DISC_REQ_TYPE_FULL_DISCOVERY;
        }
    }
    return result;
}

/**
 * Runs device discovery with current discovery settings
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_RunDeviceDiscovery(XSPI_PrivateData * privateData)
{
    uint32_t dd_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_RunDeviceDiscoverySF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Read register */
        dd_reg = CPS_REG_READ(&privateData->regs->discovery_control);

        /* Set discovery request field */
        dd_reg = CPS_FLD_SET(XSPI__DISCOVERY_CONTROL, DISCOVERY_REQ, dd_reg);

        /* Trigger device discovery operation */
        CPS_REG_WRITE(&privateData->regs->discovery_control, dd_reg);
    }

    return result;
}

/**
 * Gets status of device discovery operation
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceDiscoveryStatus Status of device discovery operation
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetDeviceDiscoveryStatus(XSPI_PrivateData * privateData, XSPI_DeviceDiscoveryStatus * deviceDiscoveryStatus)
{
    uint32_t dd_reg;
    uint32_t dd_result;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetDeviceDiscoveryStatuSF(privateData, deviceDiscoveryStatus) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Read register */
        dd_reg = CPS_REG_READ(&privateData->regs->discovery_control);

        /* Get result of last discovery operation */
        if (CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_COMP, dd_reg) != 0U) {
            dd_result = CPS_FLD_READ(XSPI__DISCOVERY_CONTROL, DISCOVERY_FAIL, dd_reg);
            switch (dd_result) {
                case 0:
                    *deviceDiscoveryStatus = XSPI_DEV_DISC_STATUS_XSPI_DEV; 
                    break;
                case 1:
                    *deviceDiscoveryStatus = XSPI_DEV_DISC_STATUS_FAILED;
                    break;
                case 2:
                    *deviceDiscoveryStatus = XSPI_DEV_DISC_STATUS_LEGACY_SPI_DEV;
                    break;
                default:
                    *deviceDiscoveryStatus = XSPI_DEV_DISC_STATUS_UNKNOWN;
                    break;
            }
        } else {
            /* Discovery operation is in progress */
            *deviceDiscoveryStatus = XSPI_DEV_DISC_STATUS_PENDING;
        }
    }
    return result;
}

/**
 * Sets HyperFlash offset config
 * @param[in] privateData Pointer to driver private data object
 * @param[in] hfOffsetCfg HyperFlash offset config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetHyperFlashOffsetConfig(XSPI_PrivateData * privateData, const XSPI_HyperFlashOffsetConfig * hfOffsetCfg)
{
    uint32_t hf_offset_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetHyperFlashOffsetConfSF(privateData, hfOffsetCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        hf_offset_reg = CPS_REG_READ(&privateData->regs->hf_offset_reg);
        hf_offset_reg = CPS_FLD_WRITE(XSPI__HF_OFFSET_REG, HF_OFFSET_SIZE, hf_offset_reg, hfOffsetCfg->offsetSize);
        hf_offset_reg = CPS_FLD_WRITE(XSPI__HF_OFFSET_REG, HF_OFFSET_INDEX, hf_offset_reg, hfOffsetCfg->offsetIndex);

        /* Set Hyperflash offset in register */
        CPS_REG_WRITE(&privateData->regs->hf_offset_reg, hf_offset_reg);
    }

    return result;
}

/**
 * Gets HyperFlash offset config
 * @param[in] privateData Pointer to driver private data object
 * @param[out] hfOffsetCfg HyperFlash offset config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetHyperFlashOffsetConfig(XSPI_PrivateData * privateData, XSPI_HyperFlashOffsetConfig * hfOffsetCfg)
{
    uint32_t hf_offset_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetHyperFlashOffsetConfSF(privateData, hfOffsetCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        hf_offset_reg = CPS_REG_READ(&privateData->regs->hf_offset_reg);

        hfOffsetCfg->offsetSize = (uint8_t) CPS_FLD_READ(XSPI__HF_OFFSET_REG, HF_OFFSET_SIZE, hf_offset_reg);
        hfOffsetCfg->offsetIndex = (uint8_t) CPS_FLD_READ(XSPI__HF_OFFSET_REG, HF_OFFSET_INDEX, hf_offset_reg);
    }

    return result;
}

/**
 * Function sets the polling configuration for controller to check device status
 * after issue of erase/write operation
 * @param[in] privateData Pointer to driver private data object
 * @param[in] pollingConfig Polling configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetPollingConfig(XSPI_PrivateData * privateData, const XSPI_PollingConfig * pollingConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t long_polling_reg = 0U, short_polling_reg = 0U;

    /* Check parameters */
    if (XSPI_SetPollingConfigSF(privateData, pollingConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        long_polling_reg = CPS_FLD_WRITE(XSPI__LONG_POLLING, LONG_POLLING, long_polling_reg, pollingConfig->longPolling);
        short_polling_reg = CPS_FLD_WRITE(XSPI__SHORT_POLLING, SHORT_POLLING, short_polling_reg, pollingConfig->shortPolling);

        CPS_REG_WRITE(&privateData->regs->long_polling, long_polling_reg);
        CPS_REG_WRITE(&privateData->regs->short_polling, short_polling_reg);
    }
    return result;
}

/**
 * Function gets the polling configuration for controller to check device status
 * @param[in] privateData Pointer to driver private data object
 * @param[out] pollingConfig Polling configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetPollingConfig(XSPI_PrivateData * privateData, XSPI_PollingConfig * pollingConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t long_polling_reg, short_polling_reg;

    /* Check parameters */
    if (XSPI_GetPollingConfigSF(privateData, pollingConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        long_polling_reg = CPS_REG_READ(&privateData->regs->long_polling);
        short_polling_reg = CPS_REG_READ(&privateData->regs->short_polling);

        pollingConfig->longPolling = (uint16_t) CPS_FLD_READ(XSPI__LONG_POLLING, LONG_POLLING, long_polling_reg);
        pollingConfig->shortPolling = (uint16_t) CPS_FLD_READ(XSPI__SHORT_POLLING, SHORT_POLLING, short_polling_reg);
    }
    return result;
}


/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */

/* This function gives the address of the first command descriptor for the given thread from descriptors table. */
static void CdmaGetBaseDescAddr(const XSPI_PrivateData * privateData, uint8_t thread, XSPI_CdmaCommandDescriptor **cmd_desc)
{
    uint8_t i, j;
    XSPI_CdmaCommandDescriptor * cmd_desc_tbl_base;

    /* parasoft-begin-suppress MISRA2012-RULE-11_4-4 "A conversion should not be performed between pointer to object and an integer type, DRV-4363" */
    cmd_desc_tbl_base = (XSPI_CdmaCommandDescriptor *) privateData->cdmaCmdsDescBase;
    /* parasoft-end-suppress MISRA2012-RULE-11_4-4 */

    /* Get first descriptor address for thread */
    for (i = 0U; i < thread; i++) {
        for (j = 0U; j < privateData->cdmaCmdsMaxNum; j++) {
            cmd_desc_tbl_base++;
        }
    }
    *cmd_desc = cmd_desc_tbl_base;
}

/* Function to fill different control flags for operation of CDMA command */
static void CdmaFillDescFlags(XSPI_CdmaCommand * cdmaCmd, uint16_t * desc_flags)
{
    XSPI_AcmdCommandParameters * params = &cdmaCmd->params;

    /* Target device number for sequence execution */
    *desc_flags = ((uint16_t)(params->bankSelect) & 0x07U);

    /* Check if interrupt should be issued after the completion of descriptor processing */
    if (params->raiseCmdCompleteCb) {
        *desc_flags |= ACMD_CDMA_FL_GEN_INT;
    }

    /* XIP flags for read sequence */
    if (params->cmdType == XSPI_ACMD_COMMAND_TYPE_READ_SEQ) {
        if (params->enXipMb) {
            *desc_flags |= ACMD_CDMA_FL_EN_XIP;
        }

        if (params->disXipMb) {
            *desc_flags |= ACMD_CDMA_FL_DIS_XIP;
        }
    }

    /* Check if existing pointer values are to be used */
    if (cdmaCmd->ignoreXSpiAddr) {
        *desc_flags |= ACMD_CDMA_FL_XSPI_PTR_CONT;
    }

    if (cdmaCmd->ignoreSysMemPtr) {
        *desc_flags |= ACMD_CDMA_FL_SYS_PTR_CONT;
    }

}

/* This function checks support of JEDEC RESET command */
static uint32_t CheckJedecResetSupport(const XSPI_PrivateData * privateData, const XSPI_AcmdCommandType cmdType)
{
    uint32_t result = CDN_EOK;

    /* Check if JEDEC RESET command is supported on this controller version */
    if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
        if (cmdType == XSPI_ACMD_COMMAND_TYPE_DEVICE_JEDEC_RESET_SEQ) {
            result = CDN_ENOTSUP;
        }
    }

    return result;
}

/* Function fills the command descriptor structure as per the CDMA command received */
static uint32_t CdmaPrepareCmdDesc(const XSPI_PrivateData * privateData, XSPI_CdmaCommand *cdmaCmd, XSPI_CdmaCommandDescriptor *cmd_desc)
{
    uint32_t result = CDN_EOK;
    uint16_t desc_flags = 0U;
    XSPI_AcmdCommandParameters * params = &cdmaCmd->params;

    (void) memset(cmd_desc, 0, sizeof(XSPI_CdmaCommandDescriptor));

    cmd_desc->cmdType = (uint16_t) params->cmdType;

    /* Update descriptor flags */
    CdmaFillDescFlags(cdmaCmd, &desc_flags);

    /* Check support of JEDEC RESET command */
    result = CheckJedecResetSupport(privateData, params->cmdType);

    if (result == CDN_EOK) {
        switch(params->cmdType){
        case XSPI_ACMD_COMMAND_TYPE_DEVICE_JEDEC_RESET_SEQ:
        case XSPI_ACMD_COMMAND_TYPE_DEVICE_RESET_SEQ:
        case XSPI_ACMD_COMMAND_TYPE_FULL_CHIP_ERASE_SEQ:
            break;

        case XSPI_ACMD_COMMAND_TYPE_ERASE_SEC_SEQ:
            cmd_desc->cmdCounter = params->cmdCount - 1U;
            cmd_desc->xSpiPtr = (uint64_t)(params->xSpiAddr);
            break;

        case XSPI_ACMD_COMMAND_TYPE_READ_SEQ:
        case XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ:
            cmd_desc->cmdCounter = params->cmdCount - 1U;

            cmd_desc->xSpiPtr = (uint64_t)params->xSpiAddr;
            cmd_desc->sysMemPtr = (uint64_t)params->sysMemPtr;

            /* Select DMA interface */
            if (params->dmaSelect == XSPI_ACMD_DMA_SELECT_MASTER) {
                desc_flags |= ACMD_CDMA_FL_DMA_SEL_MASTER;
            } else {
                desc_flags |= ACMD_CDMA_FL_DMA_SEL_SLAVE;
            }
            break;
        default:
            /* Invalid command type */
            result = CDN_EINVAL;
            break;
        }
    }

    cmd_desc->cmdFlags = desc_flags;
    cmd_desc->nextDescPtr = 0ULL;
    cmd_desc->reserved = 0ULL;
    cmd_desc->status = 0U;

    /* Cache flush */
    CPS_CacheFlush((void*)cmd_desc, sizeof(XSPI_CdmaCommandDescriptor), 0);

    return result;
}

/* Function prepares chain of command descriptors */
static uint32_t CdmaCreateDescChain(const XSPI_PrivateData *privateData, XSPI_CdmaCommandChain *cdmaCmdChain, uint64_t *cdma_desc_addr)
{
    uint32_t result = CDN_EOK;
    XSPI_CdmaCommandDescriptor * cmd_desc;
    XSPI_CdmaCommandDescriptor * cmd_desc_next;
    uint8_t thread, i;

    thread = cdmaCmdChain->thread;

    /* Get first descriptor address for thread */
    CdmaGetBaseDescAddr(privateData, thread, &cmd_desc);

    /* parasoft-begin-suppress MISRA2012-RULE-11_4-4 "A conversion should not be performed between pointer to object and an integer type, DRV-4363" */
    *cdma_desc_addr = (uint64_t)((uintptr_t)cmd_desc);
    /* parasoft-end-suppress MISRA2012-RULE-11_4-4 */

    for (i = 0U; i < cdmaCmdChain->chainLength; i++) {

        result = CdmaPrepareCmdDesc(privateData, &cdmaCmdChain->chain[i], cmd_desc);
        if (result == CDN_EOK) {
            if (i < (cdmaCmdChain->chainLength - 1U)) {
                cmd_desc_next = cmd_desc;
                cmd_desc_next++;
                /* parasoft-begin-suppress MISRA2012-RULE-11_4-4 "A conversion should not be performed between pointer to object and an integer type, DRV-4363" */
                cmd_desc->nextDescPtr = (uint64_t)((uintptr_t)(cmd_desc_next));
                /* parasoft-end-suppress MISRA2012-RULE-11_4-4 */
                cmd_desc->cmdFlags |= ACMD_CDMA_FL_DESC_CONT;
            } else {
                cmd_desc->nextDescPtr = 0ULL;
            }
            /* Cache flush */
            CPS_CacheFlush((void*)cmd_desc, sizeof(XSPI_CdmaCommandDescriptor), 0);

            cmd_desc++;
        } else {
            break;
        }
    }

    return result;
}

/* This function triggers the execution of CDMA command */
static uint32_t CdmaExecuteCommand(XSPI_PrivateData * privateData, uint8_t thread, uint64_t cdma_desc_addr)
{
    uint32_t result = CDN_EOK;
    uint32_t cmd_reg0, cmd_reg2, cmd_reg3;

    /* Wait till the corresponding thread is busy */
    result = WaitForThread(privateData, thread);

    if (result == CDN_EOK) {
        /* Select CDMA mode */
        cmd_reg0 = ACMD_CMD_TYPE_CDMA_COMMAND;
        cmd_reg0 |= ((uint32_t)((uint32_t)(thread) & 0x07U) << 24);

        cmd_reg2 = (uint32_t)(cdma_desc_addr & 0xFFFFFFFFU);
        cmd_reg3 = (uint32_t)(((uint64_t)(cdma_desc_addr >> 32)) & (uint64_t)0xFFFFFFFFU);

        CPS_REG_WRITE(&privateData->regs->cmd_reg3, cmd_reg3);
        CPS_REG_WRITE(&privateData->regs->cmd_reg2, cmd_reg2);
        CPS_REG_WRITE(&privateData->regs->cmd_reg0, cmd_reg0);
    }

    return result;

}

/**
 * Sends CDMA command for execution
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[in] cdmaCmd Pointer to CDMA command
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SendCdmaCommand(XSPI_PrivateData * privateData, uint8_t thread, XSPI_CdmaCommand * cdmaCmd)
{
    uint32_t result = CDN_EOK;
    uint64_t cdma_desc_addr;
    XSPI_CdmaCommandDescriptor * cmd_desc;

    /* Check parameters */
    if (XSPI_SendCdmaCommandSF(privateData, cdmaCmd) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        CdmaGetBaseDescAddr(privateData, thread, &cmd_desc);

        /* Prepare command descriptor for the CDMA command received */
        result = CdmaPrepareCmdDesc((const XSPI_PrivateData *)privateData, cdmaCmd, cmd_desc);
        if (result == CDN_EOK) {
            /* parasoft-begin-suppress MISRA2012-RULE-11_4-4 "A conversion should not be performed between pointer to object and an integer type, DRV-4363" */
            cdma_desc_addr = (uintptr_t) cmd_desc;
            /* parasoft-end-suppress MISRA2012-RULE-11_4-4 */

            result = CdmaExecuteCommand(privateData, thread, cdma_desc_addr);
        }
    }

    return result;
}

/**
 * Sends multiple CDMA commands for execution by forming a chain
 * @param[in] privateData Pointer to driver private data object
 * @param[in] cdmaCmdChain Pointer to CDMA commands chain structure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SendCdmaCommandChain(XSPI_PrivateData * privateData, XSPI_CdmaCommandChain * cdmaCmdChain)
{
    uint32_t result = CDN_EOK;
    uint64_t cdma_desc_addr;

    /* Check parameters */
    if (XSPI_SendCdmaCommandChainSF(privateData, cdmaCmdChain) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Create command descriptors chain */
        result = CdmaCreateDescChain(privateData, cdmaCmdChain, &cdma_desc_addr);
        if (result == CDN_EOK) {
            /* Send CDMA command chain of descriptors for processing */
            result = CdmaExecuteCommand(privateData, cdmaCmdChain->thread, cdma_desc_addr);
        }
    }
    return result;
}

/* Function reads the CDMA descriptor status field */
static void GetCdmaDescStatus(XSPI_PrivateData * privateData, XSPI_CdmaCommandDescriptor * cmd_desc, XSPI_CdmaCommand * cdmaCmd)
{
    /* Cache invalidate */
    CPS_CacheInvalidate((void*)cmd_desc, sizeof(XSPI_CdmaCommandDescriptor), 0);

    cdmaCmd->statusInfo.statusValue = cmd_desc->status;

    XSPI_GetLastCommandStatus(privateData, &cdmaCmd->statusInfo, true);
}

/**
 * Gets CDMA command status
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[out] cdmaCmd Pointer to CDMA command, contains status structure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetCdmaCommandStatus(XSPI_PrivateData * privateData, uint8_t thread, XSPI_CdmaCommand * cdmaCmd)
{
    uint32_t result = CDN_EOK;
    XSPI_CdmaCommandDescriptor * cmd_desc;

    /* Check parameters */
    if (XSPI_GetCdmaCommandStatusSF(privateData, cdmaCmd) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Get first descriptor address for thread */
        CdmaGetBaseDescAddr(privateData, thread, &cmd_desc);

        GetCdmaDescStatus(privateData, cmd_desc, cdmaCmd);
    }

    return result;

}

/**
 * Gets CDMA chain status
 * @param[in] privateData Pointer to driver private data object
 * @param[out] cdmaCmdChain Pointer to CDMA commands chain structure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetCdmaChainStatus(XSPI_PrivateData *privateData, XSPI_CdmaCommandChain *cdmaCmdChain)
{
    uint32_t result = CDN_EOK;
    XSPI_CdmaCommandDescriptor *cmd_desc;
    uint8_t thread, i;

    /* Check parameters */
    if (XSPI_GetCdmaChainStatusSF(privateData, cdmaCmdChain) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        thread = cdmaCmdChain->thread;

        /* Get first descriptor address for thread */
        CdmaGetBaseDescAddr(privateData, thread, &cmd_desc);

        for (i = 0U; i < cdmaCmdChain->chainLength; i++) {
            /* Get individual command descriptor status */
            GetCdmaDescStatus(privateData, cmd_desc, &cdmaCmdChain->chain[i]);
            cmd_desc++;
        }

        /* Fill ChainStatus struct */
        for (i = 0U; i < cdmaCmdChain->chainLength; i++) {
            if (cdmaCmdChain->chain[i].statusInfo.status == XSPI_COMMAND_STATUS_PENDING) {
                cdmaCmdChain->chainStatus.isCompleted = false;
            } else if (cdmaCmdChain->chain[i].statusInfo.status == XSPI_COMMAND_STATUS_SUCCESS) {
                cdmaCmdChain->chainStatus.isFailed = false;
                cdmaCmdChain->chainStatus.isCompleted = true;
                continue;
            } else {
                cdmaCmdChain->chainStatus.isFailed = true;
                cdmaCmdChain->chainStatus.failCmdIndex = i;
                cdmaCmdChain->chainStatus.isCompleted = true;
            }
            break;
        }
    }

    return result;
}

/* parasoft-end-suppress METRICS-36-3 */

/* Function sets register values for program and read sequences in PIO mode */
static void PioSetProgReadRegVal(const XSPI_PrivateData * privateData, const XSPI_AcmdCommandParameters * params, uint32_t * cmd_reg)
{
    volatile XSPI_Regs * regs = privateData->regs;
    uint32_t cmdCount = 0U;

    /* XIP flags for read sequence */
    if (params->cmdType == XSPI_ACMD_COMMAND_TYPE_READ_SEQ) {
        if (params->enXipMb) {
            cmd_reg[0] |= ACMD_PIO_FIELD_EN_XIP;
        }

        if (params->disXipMb) {
            cmd_reg[0] |= ACMD_PIO_FIELD_DIS_XIP;
        }
    }

    cmdCount = params->cmdCount - 1U;

    cmd_reg[4] = cmdCount;
    cmd_reg[3] = (uint32_t)(((uint64_t)params->sysMemPtr) >> (uint64_t)32);
    cmd_reg[2] = (uint32_t)(params->sysMemPtr & 0xFFFFFFFFU);
    cmd_reg[1] = (uint32_t)params->xSpiAddr;

    /* Select DMA interface */
    if (params->dmaSelect == XSPI_ACMD_DMA_SELECT_MASTER) {
        cmd_reg[0] |= ACMD_PIO_FIELD_DMA_SEL_MASTER;
    } else {
        cmd_reg[0] |= ACMD_PIO_FIELD_DMA_SEL_SLAVE;
    }

    if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {

        /* Write high address of xSPI_PTR */
        cmd_reg[5] = (uint32_t)((params->xSpiAddr >> 32) & 0xFFFFFFFFU);
        CPS_REG_WRITE(&regs->cmd_reg5, cmd_reg[5]);
    }

    /* Fill command registers */
    CPS_REG_WRITE(&regs->cmd_reg4, cmd_reg[4]);
    CPS_REG_WRITE(&regs->cmd_reg3, cmd_reg[3]);
    CPS_REG_WRITE(&regs->cmd_reg2, cmd_reg[2]);
    CPS_REG_WRITE(&regs->cmd_reg1, cmd_reg[1]);
}

/* Checks if passed parameters to PIO command are correct and supported */
static uint32_t PioCommandParamsCheck(const XSPI_PrivateData * privateData, const XSPI_PioCommand * pioCmd)
{
    uint32_t result = CDN_EOK;
    XSPI_WorkMode workMode;
    XSPI_GlobalCommandParameters globalCmdParams;

    /* Check parameters */
    if (XSPI_SendPioCommandSF(privateData, pioCmd) != CDN_EOK) {
        result = CDN_EINVAL;
    }

    if (result == CDN_EOK) {
        result = XSPI_GetWorkMode((XSPI_PrivateData *)privateData, &workMode);

        if (workMode != XSPI_WORK_MODE_AUTO_COMMAND) {
            result = CDN_EINVAL;
        }
    }

    if (result == CDN_EOK) {
        result = XSPI_GetGlobalCmdParameters((XSPI_PrivateData *)privateData, &globalCmdParams);

        switch (globalCmdParams.seqType) {
            case XSPI_SEQUENCE_TYPE_P2_HYPER_RAM:
                if ((pioCmd->params.cmdType == XSPI_ACMD_COMMAND_TYPE_ERASE_SEC_SEQ) ||
                    (pioCmd->params.cmdType == XSPI_ACMD_COMMAND_TYPE_FULL_CHIP_ERASE_SEQ) || 
                    (pioCmd->params.cmdType == XSPI_ACMD_COMMAND_TYPE_DEVICE_RESET_SEQ)) {
                    result = CDN_ENOTSUP;
                }
                break;

            case XSPI_SEQUENCE_TYPE_P1_SPI_NAND:
                if (pioCmd->params.cmdType == XSPI_ACMD_COMMAND_TYPE_FULL_CHIP_ERASE_SEQ) {
                    result = CDN_ENOTSUP;
                }
                break;

            default:
                /* Other sequences */
                break;
        }
    }

    /* Check command count */
    if (result == CDN_EOK) {
        if (pioCmd->params.cmdCount == 0U) {
            result = CDN_EINVAL;
        }
    }

    /* Check support of JEDEC RESET if used */
    if (result == CDN_EOK) {
        result = CheckJedecResetSupport(privateData, pioCmd->params.cmdType);
    }

    return result;
}

/**
 * Sends PIO command for execution
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[in] pioCmd Pointer to PIO command
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SendPioCommand(XSPI_PrivateData * privateData, uint8_t thread, XSPI_PioCommand * pioCmd)
{
    uint32_t result = CDN_EOK;
    uint32_t cmd_reg[ACMD_CMD_REGS_MAX_NUM] = {0}, cmdCount = 0U;
    volatile XSPI_Regs * regs;
    XSPI_AcmdCommandParameters * params;

    /* Check PIO command parameters */
    result = PioCommandParamsCheck((const XSPI_PrivateData *)privateData, (const XSPI_PioCommand *)pioCmd);

    if (result == CDN_EOK) {
        regs = privateData->regs;
        params = &pioCmd->params;

        /* Wait till the corresponding thread is busy */
        result = WaitForThread(privateData, thread);

        /* Select PIO mode */
        cmd_reg[0] = ACMD_CMD_TYPE_PIO_COMMAND;
        cmd_reg[0] |= ((uint32_t)(params->cmdType) & 0xFFFFU);
        cmd_reg[0] |= ((uint32_t)((uint32_t)(thread) & 0x07U) << 24);
        cmd_reg[0] |= ((uint32_t)((uint32_t)(params->bankSelect) & 0x07U) << 20);

        if (params->raiseCmdCompleteCb) {
            cmd_reg[0] |= ACMD_PIO_FIELD_GEN_INT;
        }

        switch(params->cmdType){
            case XSPI_ACMD_COMMAND_TYPE_DEVICE_JEDEC_RESET_SEQ:
            case XSPI_ACMD_COMMAND_TYPE_DEVICE_RESET_SEQ:
            case XSPI_ACMD_COMMAND_TYPE_FULL_CHIP_ERASE_SEQ:
                break;

            case XSPI_ACMD_COMMAND_TYPE_ERASE_SEC_SEQ:
                /* Erase sector sequence */
                cmdCount = params->cmdCount - 1U;

                cmd_reg[4] = (uint32_t) (cmdCount & 0xFFFFU);
                cmd_reg[1] = (uint32_t)params->xSpiAddr;

                if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {

                    /* Write high address of xSPI_PTR */
                    cmd_reg[5] = (uint32_t)((params->xSpiAddr >> 32) & 0xFFFFFFFFU);
                    CPS_REG_WRITE(&regs->cmd_reg5, cmd_reg[5]);
                }

                CPS_REG_WRITE(&regs->cmd_reg4, cmd_reg[4]);
                CPS_REG_WRITE(&regs->cmd_reg1, cmd_reg[1]);
                break;

            case XSPI_ACMD_COMMAND_TYPE_READ_SEQ:
            case XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ:
                /* Program and read sequences */
                PioSetProgReadRegVal(privateData, params, cmd_reg);
                break;

            default:
                result = CDN_EINVAL;
                break;
        }

        if (result == CDN_EOK) {
            /* Trigger the execution */
            CPS_REG_WRITE(&regs->cmd_reg0, cmd_reg[0]);
        }
    }

    return result;
}

/**
 * Gets PIO command status
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[out] pioCmd Pointer to PIO command
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetPioCommandStatus(XSPI_PrivateData * privateData, uint8_t thread, XSPI_PioCommand * pioCmd)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetPioCommandStatusSF(privateData, pioCmd) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        CPS_REG_WRITE(&privateData->regs->cmd_status_ptr, (uint32_t) thread);

        XSPI_GetLastCommandStatus(privateData, &pioCmd->statusInfo, false);
    }

    return result;
}

/**
 * Gets the status of last command executed in ACMD mode
 * (both for CDMA and PIO modes)
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[out] cmdStatus Returns status information of the command
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetAcmdLastCmdStatus(XSPI_PrivateData * privateData, uint8_t thread, XSPI_CommandStatusInfo * cmdStatus)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetAcmdLastCmdStatusSF(privateData, cmdStatus) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        CPS_REG_WRITE(&privateData->regs->cmd_status_ptr, (uint32_t) thread);

        XSPI_GetLastCommandStatus(privateData, cmdStatus, false);
    }

    return result;
}

static void SetResetSeqConfigCmd0(uint32_t * rst_seq_cfg0_reg, uint32_t * rst_seq_cfg1_reg, const XSPI_ResetSeqConfig * resetSeqCfg)
{
    /* Command 0 settings */
    *rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD0_VAL, *rst_seq_cfg0_reg, resetSeqCfg->rstSeqCmd0Val);
    *rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD0_EN, *rst_seq_cfg0_reg, ((resetSeqCfg->rstSeqCmd0En == true) ? 1U : 0U));
    *rst_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD0_EXT_EN, *rst_seq_cfg1_reg, ((resetSeqCfg->rstSeqCmd0Ext.enable == true) ? 1U : 0U));
    *rst_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD0_EXT_VAL, *rst_seq_cfg1_reg, resetSeqCfg->rstSeqCmd0Ext.value);
}

static void SetResetSeqConfigCmd1(uint32_t * rst_seq_cfg0_reg, uint32_t * rst_seq_cfg1_reg, const XSPI_ResetSeqConfig * resetSeqCfg)
{
    /* Command 1 settings */
    *rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD1_VAL, *rst_seq_cfg0_reg, resetSeqCfg->rstSeqCmd1Val);
    *rst_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD1_EXT_EN, *rst_seq_cfg1_reg, ((resetSeqCfg->rstSeqCmd1Ext.enable == true) ? 1U : 0U));
    *rst_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD1_EXT_VAL, *rst_seq_cfg1_reg, resetSeqCfg->rstSeqCmd1Ext.value);
}

/**
 * Sets RESET sequence configuration for Profile 1 in CDMA and PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetSeqCfg Reset sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetResetSeqConfig(const XSPI_PrivateData * privateData, const XSPI_ResetSeqConfig * resetSeqCfg)
{
    uint32_t rst_seq_cfg0_reg = 0U;
    uint32_t rst_seq_cfg1_reg = 0U;
    uint32_t rst_seq_cfg2_reg = 0U;
    volatile XSPI_Regs * regs;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetResetSeqConfigSF(privateData, resetSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        regs = privateData->regs;

        /* Command 0 config */
        SetResetSeqConfigCmd0(&rst_seq_cfg0_reg, &rst_seq_cfg1_reg, resetSeqCfg);

        /* Command 1 config */
        SetResetSeqConfigCmd1(&rst_seq_cfg0_reg, &rst_seq_cfg1_reg, resetSeqCfg);

        /* Reset data phase parameters config */
        rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_DATA_IOS, rst_seq_cfg0_reg, resetSeqCfg->rstSeqData.ios);
        rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_DATA_EDGE, rst_seq_cfg0_reg, resetSeqCfg->rstSeqData.edge);
        rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_DATA_EN, rst_seq_cfg0_reg, ((resetSeqCfg->rstSeqDataEn == true) ? 1U : 0U));

        /* Command phase config */
        rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD_IOS, rst_seq_cfg0_reg, resetSeqCfg->rstSeqCmdIos);
        rst_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD_EDGE, rst_seq_cfg0_reg, resetSeqCfg->rstSeqCmdEdge);

        /* Get reset data phase opcode */
        rst_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_DATA_VAL, rst_seq_cfg1_reg, resetSeqCfg->rstSeqDataVal);

        /* Check controller revision */
        if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
            rst_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__RST_SEQ_CFG_2, RST_SEQ_P1_TPOR, rst_seq_cfg2_reg, resetSeqCfg->tPORTiming);
            CPS_REG_WRITE(&regs->rst_seq_cfg_2, rst_seq_cfg2_reg);
        }

        /* Write reset sequence config register */
        CPS_REG_WRITE(&regs->rst_seq_cfg_0, rst_seq_cfg0_reg);
        CPS_REG_WRITE(&regs->rst_seq_cfg_1, rst_seq_cfg1_reg);
    }

    return result;
}

/**
 * Internal function
 * Function reads command extension config for reset sequence
 */
static void GetResetSeqCmdExtConfig(XSPI_PrivateData * privateData, XSPI_ResetSeqConfig * resetSeqCfg)
{
    uint32_t rst_seq_cfg1_reg = 0U;
    XSPI_SeqCommandExtension * rstSeqCmdExt;

    rst_seq_cfg1_reg = CPS_REG_READ(&privateData->regs->rst_seq_cfg_1);

    /* Get reset data phase opcode */
    resetSeqCfg->rstSeqDataVal = (uint8_t)CPS_FLD_READ(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_DATA_VAL, rst_seq_cfg1_reg);

    /* Command extension config for CMD0 */
    rstSeqCmdExt = &resetSeqCfg->rstSeqCmd0Ext;

    if (CPS_FLD_READ(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD0_EXT_EN, rst_seq_cfg1_reg) == 0U) {
        rstSeqCmdExt->enable = false;
    } else {
        rstSeqCmdExt->enable = true;
    }

    rstSeqCmdExt->value  = (uint8_t) CPS_FLD_READ(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD0_EXT_VAL, rst_seq_cfg1_reg);

    /* Command extension config for CMD1 */
    rstSeqCmdExt = &resetSeqCfg->rstSeqCmd1Ext;

    if (CPS_FLD_READ(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD1_EXT_EN, rst_seq_cfg1_reg) == 0U) {
        rstSeqCmdExt->enable = false;
    } else {
        rstSeqCmdExt->enable = true;
    }

    rstSeqCmdExt->value  = (uint8_t) CPS_FLD_READ(XSPI__RST_SEQ_CFG_1, RST_SEQ_P1_CMD1_EXT_VAL, rst_seq_cfg1_reg);
}

/**
 * Gets RESET sequence configuration for Profile 1 in CDMA and PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] resetSeqCfg Reset sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetResetSeqConfig(XSPI_PrivateData * privateData, XSPI_ResetSeqConfig * resetSeqCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t rst_seq_cfg0_reg = 0U;
    uint32_t rst_seq_cfg2_reg = 0U;

    /* Check parameters */
    if (XSPI_GetResetSeqConfigSF(privateData, resetSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        rst_seq_cfg0_reg = CPS_REG_READ(&privateData->regs->rst_seq_cfg_0);

        /* Command mnemonic */
        resetSeqCfg->rstSeqCmd0Val = (uint8_t) CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD0_VAL, rst_seq_cfg0_reg);
        resetSeqCfg->rstSeqCmd1Val = (uint8_t) CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD1_VAL, rst_seq_cfg0_reg);

        /* Get command 0 phase enable */
        if (CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD0_EN, rst_seq_cfg0_reg) == 0U) {
            resetSeqCfg->rstSeqCmd0En = false;
        } else {
            resetSeqCfg->rstSeqCmd0En = true;
        }

        /* Check controller revision */
        result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_DATA_IOS, rst_seq_cfg0_reg), &resetSeqCfg->rstSeqData.ios);
        result |= GetDataEdgeModeEnum(CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_DATA_EDGE, rst_seq_cfg0_reg), &resetSeqCfg->rstSeqData.edge);

        if (CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_DATA_EN, rst_seq_cfg0_reg) == 0U) {
            resetSeqCfg->rstSeqDataEn = false;
        } else {
            resetSeqCfg->rstSeqDataEn = true;
        }

        /* Get IOS enum */
        result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD_IOS, rst_seq_cfg0_reg), &resetSeqCfg->rstSeqCmdIos);

        /* Get command edge enum */
        result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__RST_SEQ_CFG_0, RST_SEQ_P1_CMD_EDGE, rst_seq_cfg0_reg), &resetSeqCfg->rstSeqCmdEdge);

        /* Get command extension config */
        GetResetSeqCmdExtConfig(privateData, resetSeqCfg);

        if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
            rst_seq_cfg2_reg = CPS_REG_READ(&privateData->regs->rst_seq_cfg_2);
            resetSeqCfg->tPORTiming = (uint32_t)CPS_FLD_READ(XSPI__RST_SEQ_CFG_2, RST_SEQ_P1_TPOR, rst_seq_cfg2_reg);
        }
    }

    return result;
}

/**
 * Sets ERASE SECTOR sequence configuration for Profile 1 in CDMA and PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] eraseSecSeqCfg ERASE SECTOR sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetEraseSecConfig(XSPI_PrivateData * privateData, const XSPI_EraseSecSeqConfig * eraseSecSeqCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t ers_seq_cfg0_reg = 0U;
    uint32_t ers_seq_cfg1_reg = 0U;

    /* Check parameters */
    if (XSPI_SetEraseSecConfigSF(privateData, eraseSecSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Address phase */
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_ADDR_EDGE, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqAddr.edge);
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_ADDR_IOS, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqAddr.ios);
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_ADDR_CNT, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqAddr.count);

        /* Command phase */
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_EXT_EN, ers_seq_cfg0_reg, ((eraseSecSeqCfg->erssSeqCmdExt.enable == true) ? 1U : 0U));
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_EXT_VAL, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqCmdExt.value);

        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_EDGE, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqCmd.edge);
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_IOS, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqCmd.ios);
        ers_seq_cfg0_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_VAL, ers_seq_cfg0_reg, eraseSecSeqCfg->erssSeqCmd.value);

        ers_seq_cfg1_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_1, ERSS_SEQ_P1_SECT_SIZE, ers_seq_cfg1_reg, eraseSecSeqCfg->erssSeqSecSize);

        CPS_REG_WRITE(&privateData->regs->ers_seq_cfg_0, ers_seq_cfg0_reg);
        CPS_REG_WRITE(&privateData->regs->ers_seq_cfg_1, ers_seq_cfg1_reg);
    }

    return result;
}

/**
 * Gets ERASE SECTOR sequence configuration for Profile 1 in CDMA and PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] eraseSecSeqCfg ERASE SECTOR sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetEraseSecConfig(XSPI_PrivateData * privateData, XSPI_EraseSecSeqConfig * eraseSecSeqCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t ers_seq_cfg0_reg = 0U;
    uint32_t ers_seq_cfg1_reg = 0U;

    /* Check parameters */
    if (XSPI_GetEraseSecConfigSF(privateData, eraseSecSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        ers_seq_cfg0_reg = CPS_REG_READ(&privateData->regs->ers_seq_cfg_0);
        ers_seq_cfg1_reg = CPS_REG_READ(&privateData->regs->ers_seq_cfg_1);

        /* Address phase */
        eraseSecSeqCfg->erssSeqAddr.count = (uint8_t) CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_ADDR_CNT, ers_seq_cfg0_reg);

        result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_ADDR_IOS, ers_seq_cfg0_reg), &eraseSecSeqCfg->erssSeqAddr.ios);

        result |= GetAddrEdgeModeEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_ADDR_EDGE, ers_seq_cfg0_reg), &eraseSecSeqCfg->erssSeqAddr.edge);

        /* Command phase */
        if (CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_EXT_EN, ers_seq_cfg0_reg) == 0U) {
            eraseSecSeqCfg->erssSeqCmdExt.enable = false;
        } else {
            eraseSecSeqCfg->erssSeqCmdExt.enable = true;
        }

        eraseSecSeqCfg->erssSeqCmdExt.value = (uint8_t) CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_EXT_VAL, ers_seq_cfg0_reg);

        result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_IOS, ers_seq_cfg0_reg), &eraseSecSeqCfg->erssSeqCmd.ios);
        result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_EDGE, ers_seq_cfg0_reg), &eraseSecSeqCfg->erssSeqCmd.edge);

        eraseSecSeqCfg->erssSeqCmd.value = (uint8_t) CPS_FLD_READ(XSPI__ERS_SEQ_CFG_0, ERSS_SEQ_P1_CMD_VAL, ers_seq_cfg0_reg);

        result |= GetErsSectorSizeEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_1, ERSS_SEQ_P1_SECT_SIZE, ers_seq_cfg1_reg), &eraseSecSeqCfg->erssSeqSecSize);
        
    }

    return result;
}

/**
 * Sets CHIP ERASE sequence configuration for Profile 1 in CDMA and PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] chipEraseSeqCfg CHIP ERASE sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetChipEraseSeqConfig(XSPI_PrivateData * privateData, const XSPI_ChipEraseSeqConfig * chipEraseSeqCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t ers_seq_cfg2_reg = 0U;

    /* Check parameters */
    if (XSPI_SetChipEraseSeqConfigSF(privateData, chipEraseSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        ers_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_EDGE, ers_seq_cfg2_reg, chipEraseSeqCfg->ersaSeqCmd.edge);
        ers_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_IOS, ers_seq_cfg2_reg, chipEraseSeqCfg->ersaSeqCmd.ios);
        ers_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_VAL, ers_seq_cfg2_reg, chipEraseSeqCfg->ersaSeqCmd.value);

        ers_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_EXT_EN, ers_seq_cfg2_reg, ((chipEraseSeqCfg->ersaSeqCmdExt.enable == true) ? 1U : 0U));
        ers_seq_cfg2_reg = CPS_FLD_WRITE(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_EXT_VAL, ers_seq_cfg2_reg, chipEraseSeqCfg->ersaSeqCmdExt.value);

        CPS_REG_WRITE(&privateData->regs->ers_seq_cfg_2, ers_seq_cfg2_reg);
    }

    return result;
}

/**
 * Gets CHIP ERASE sequence configuration for Profile 1 in CDMA and PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] chipEraseSeqCfg CHIP ERASE sequence config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetChipEraseSeqConfig(XSPI_PrivateData * privateData, XSPI_ChipEraseSeqConfig * chipEraseSeqCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t ers_seq_cfg2_reg = 0U;

    /* Check parameters */
    if (XSPI_GetChipEraseSeqConfigSF(privateData, chipEraseSeqCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Read register */
        ers_seq_cfg2_reg = CPS_REG_READ(&privateData->regs->ers_seq_cfg_2);

        if (CPS_FLD_READ(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_EXT_EN, ers_seq_cfg2_reg) == 0U) {
            chipEraseSeqCfg->ersaSeqCmdExt.enable = false;
        } else {
            chipEraseSeqCfg->ersaSeqCmdExt.enable = true;
        }

        chipEraseSeqCfg->ersaSeqCmdExt.value = (uint8_t) CPS_FLD_READ(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_EXT_VAL, ers_seq_cfg2_reg);

        result |= GetNumOfIosEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_IOS, ers_seq_cfg2_reg), &chipEraseSeqCfg->ersaSeqCmd.ios);
        result |= GetCmdEdgeModeEnum(CPS_FLD_READ(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_EDGE, ers_seq_cfg2_reg), &chipEraseSeqCfg->ersaSeqCmd.edge);

        chipEraseSeqCfg->ersaSeqCmd.value = (uint8_t) CPS_FLD_READ(XSPI__ERS_SEQ_CFG_2, ERSA_SEQ_P1_CMD_VAL, ers_seq_cfg2_reg);
        
    }

    return result;
}


/**
 * Sets configuration of the resynchronization of slave DLL of PHY
 * @param[in] privateData pointer to driver private data object
 * @param[in] phyConfig PHY configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetPhyConfig(XSPI_PrivateData * privateData, const XSPI_PhyConfig * phyConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t dll_phy_updt_cnt_reg = 0U, dll_phy_ctrl_reg = 0U;

    /* Check parameters */
    if (XSPI_SetPhyConfigSF(privateData, phyConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        dll_phy_ctrl_reg = CPS_REG_READ(&privateData->regs->dll_phy_ctrl);



        /* Set PHY resynchronization config parameters */
        dll_phy_updt_cnt_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_UPDATE_CNT, RESYNC_CNT, dll_phy_updt_cnt_reg, phyConfig->resyncCount);

        dll_phy_ctrl_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_CTRL, DFI_CTRLUPD_REQ, dll_phy_ctrl_reg, phyConfig->dfiCtrlUpdtReq);
        dll_phy_ctrl_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_CTRL, SDR_EDGE_ACTIVE, dll_phy_ctrl_reg, phyConfig->sdrActiveEdge);
        dll_phy_ctrl_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_CTRL, DQS_LAST_DATA_DROP_EN, dll_phy_ctrl_reg, phyConfig->dqsLastDataDropEn);
        dll_phy_ctrl_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_CTRL, RESYNC_HIGH_WAIT_CNT, dll_phy_ctrl_reg, phyConfig->resyncHighWaitCount);
        dll_phy_ctrl_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_CTRL, RESYNC_IDLE_CNT, dll_phy_ctrl_reg, phyConfig->resyncIdleCount);

        CPS_REG_WRITE(&privateData->regs->dll_phy_update_cnt, dll_phy_updt_cnt_reg);
        CPS_REG_WRITE(&privateData->regs->dll_phy_ctrl, dll_phy_ctrl_reg);
    }

    return result;
}

/**
 * Gets configuration of the resynchronization of slave DLL of PHY
 * @param[in] privateData pointer to driver private data object
 * @param[out] phyConfig PHY configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetPhyConfig(XSPI_PrivateData * privateData, XSPI_PhyConfig * phyConfig)
{
    uint32_t result = CDN_EOK;
    uint32_t dll_phy_updt_cnt_reg = 0U, dll_phy_ctrl_reg = 0U;

    /* Check parameters */
    if (XSPI_GetPhyConfigSF(privateData, phyConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        dll_phy_updt_cnt_reg = CPS_REG_READ(&privateData->regs->dll_phy_update_cnt);
        dll_phy_ctrl_reg = CPS_REG_READ(&privateData->regs->dll_phy_ctrl);

        /* Get PHY resynchronization config parameters */
        phyConfig->resyncCount = CPS_FLD_READ(XSPI__DLL_PHY_UPDATE_CNT, RESYNC_CNT, dll_phy_updt_cnt_reg);

        phyConfig->dfiCtrlUpdtReq = (uint8_t) CPS_FLD_READ(XSPI__DLL_PHY_CTRL, DFI_CTRLUPD_REQ, dll_phy_ctrl_reg);

        /* Get active edge */
        if (CPS_FLD_READ(XSPI__DLL_PHY_CTRL, SDR_EDGE_ACTIVE, dll_phy_ctrl_reg) == 0U) {
            phyConfig->sdrActiveEdge = XSPI_SDR_ACTIVE_EDGE_POSITIVE;
        } else {
            phyConfig->sdrActiveEdge = XSPI_SDR_ACTIVE_EDGE_NEGATIVE;
        }

        phyConfig->dqsLastDataDropEn = (uint8_t) CPS_FLD_READ(XSPI__DLL_PHY_CTRL, DQS_LAST_DATA_DROP_EN, dll_phy_ctrl_reg);

        phyConfig->resyncHighWaitCount = (uint8_t) CPS_FLD_READ(XSPI__DLL_PHY_CTRL, RESYNC_HIGH_WAIT_CNT, dll_phy_ctrl_reg);

        phyConfig->resyncIdleCount = (uint8_t) CPS_FLD_READ(XSPI__DLL_PHY_CTRL, RESYNC_IDLE_CNT, dll_phy_ctrl_reg);
    }

    return result;
}

/**
 * Writes signal value to reset the DLLs of the PHY
 * @param[in] privateData pointer to driver private data object
 * @param[in] dllReset DLL reset value
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_PhyWriteDllReset(XSPI_PrivateData * privateData, uint8_t dllReset)
{
    uint32_t result = CDN_EOK;
    uint32_t dll_phy_ctrl_reg = 0U;

    /* Check parameters */
    if (XSPI_PhyWriteDllResetSF(privateData, dllReset) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        dll_phy_ctrl_reg = CPS_REG_READ(&privateData->regs->dll_phy_ctrl);

        dll_phy_ctrl_reg = CPS_FLD_WRITE(XSPI__DLL_PHY_CTRL, DLL_RST_N, dll_phy_ctrl_reg, dllReset);

        CPS_REG_WRITE(&privateData->regs->dll_phy_ctrl, dll_phy_ctrl_reg);
    }

    return result;
}
