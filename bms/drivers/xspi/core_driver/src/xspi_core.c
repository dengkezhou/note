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
 * This file contains implementation of core functions for XSPI controller.
 *
 *****************************************************************************/

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <cps.h>
#include <cdn_log.h>
#include <cdn_errno.h>

#include "xspi_if.h"
#include "xspi_structs_if.h"

#include "xspi_core.h"
#include "xspi_sanity.h"

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */

/**
 * Set configurations for controller to work in XIP mode
 * @param[in] privateData Pointer to driver private data object
 * @param[in] xipModeBitsConfig XIP configuration to set
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetXipModeBitsConfig(XSPI_PrivateData * privateData, const XSPI_XipModeBitsConfig * xipModeBitsConfig)
{
    uint32_t xip_mode_cfg_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetXipModeBitsConfigSF(privateData, xipModeBitsConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        xip_mode_cfg_reg = CPS_FLD_WRITE(XSPI__XIP_MODE_CFG, XIP_EN_MB_VAL, xip_mode_cfg_reg, xipModeBitsConfig->xipEnBits);
        xip_mode_cfg_reg = CPS_FLD_WRITE(XSPI__XIP_MODE_CFG, XIP_DIS_MB_VAL, xip_mode_cfg_reg, xipModeBitsConfig->xipDisBits);
        xip_mode_cfg_reg = CPS_FLD_WRITE(XSPI__XIP_MODE_CFG, XIP_EN, xip_mode_cfg_reg, xipModeBitsConfig->xipEnableBanks);

        CPS_REG_WRITE(&privateData->regs->xip_mode_cfg, xip_mode_cfg_reg);
    }

    return result;
}

/**
 * Get current XIP configurations of controller
 * @param[in] privateData Pointer to driver private data object
 * @param[out] xipModeBitsConfig Returns current xip configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetXipModeBitsConfig(XSPI_PrivateData * privateData, XSPI_XipModeBitsConfig * xipModeBitsConfig)
{
    uint32_t xip_mode_cfg_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetXipModeBitsConfigSF(privateData, xipModeBitsConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        xip_mode_cfg_reg = CPS_REG_READ(&privateData->regs->xip_mode_cfg);

        xipModeBitsConfig->xipEnBits = (uint8_t) CPS_FLD_READ(XSPI__XIP_MODE_CFG, XIP_EN_MB_VAL, xip_mode_cfg_reg);
        xipModeBitsConfig->xipDisBits = (uint8_t) CPS_FLD_READ(XSPI__XIP_MODE_CFG, XIP_DIS_MB_VAL, xip_mode_cfg_reg);
        xipModeBitsConfig->xipEnableBanks = (uint8_t) CPS_FLD_READ(XSPI__XIP_MODE_CFG, XIP_EN, xip_mode_cfg_reg);
    }

    return result;
}

/**
 * Internal function
 * Function waits till register field value matches with dest_value for specified timeout.
 */
uint32_t WaitForRegValueMatch(volatile uint32_t * reg_addr, uint32_t shift, uint32_t mask, uint32_t dest_value, uint32_t timeout_max)
{
    uint32_t result = CDN_EOK;
    volatile uint32_t reg = 0;
    uint32_t timeout_counter = timeout_max;

    if (shift < 32U) {
        /* Check till timeout */
        for (;timeout_counter != 0U;timeout_counter--) {
            reg = CPS_REG_READ(reg_addr);
            if ((((reg >> shift) & mask) == dest_value)) {
                break;
            }
        }

        /* Update error status */
        if (((reg >> shift) & mask) != dest_value) {
            result = CDN_EBUSY;
        }
    } else {
        result = CDN_EINVAL;
    }

    return result;
}

/**
 * Internal function
 * Function waits till XSPI controller completes its reset and initialization process.
 */
static uint32_t WaitForInitComplete(XSPI_PrivateData * privateData)
{
    return WaitForRegValueMatch(&privateData->regs->ctrl_status,
        XSPI__CTRL_STATUS__INIT_COMP_SHIFT, 1U, 1, 10U);
}

/**
 * Internal function
 * Function waits till XSPI controller is in busy state
 */
uint32_t WaitForIdle(XSPI_PrivateData * privateData)
{
    return WaitForRegValueMatch(&privateData->regs->ctrl_status,
        XSPI__CTRL_STATUS__CTRL_BUSY_SHIFT, 1U, 0, 10000U);
}

/* Function gives maximum number of banks currently supported by hardware */
static void GetMaxBankCnt(uint32_t ctrl_features_reg, uint8_t * maxBankNum)
{
    uint8_t n_banks;

    /* Read register field */
    n_banks = (uint8_t) CPS_FLD_READ(XSPI__CTRL_FEATURES_REG, N_BANKS, ctrl_features_reg);

    /* Get max banks count */
    switch (n_banks) {
    case 0U :
        *maxBankNum = 1U;
        break;
    case 1U :
        *maxBankNum = 2U;
        break;
    case 2U :
        *maxBankNum = 4U;
        break;
    default :
        *maxBankNum = 8U;
        break;
    }
}

/* Function gets controller revision */
static uint32_t GetCtrlRevEnum(const uint32_t ctrlRev, XSPI_ControllerRevision * enumCtrlRev)
{
    uint32_t i, result = CDN_EINVAL;

    /* Controller revision enums */
    const XSPI_ControllerRevision ctrlRevEnums[CTRL_REV_ENUM_CNT] = {
        [0U] = XSPI_CTRL_REV_R002,
        [1U] = XSPI_CTRL_REV_R003,
        [2U] = XSPI_CTRL_REV_R004,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < CTRL_REV_ENUM_CNT; i++) {
        if ((uint32_t) ctrlRevEnums[i] == ctrlRev) {
            *enumCtrlRev = ctrlRevEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/* Function initializes xSPI controller */
uint32_t CoreInit(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t ctrl_features_reg = 0U;
    uint32_t xspi_ctrl_version_reg = 0U;
    volatile XSPI_Regs * regs = privateData->regs;
    XSPI_CtrlFeaturesInfo * ctrlFeatures = &privateData->ctrlFeatures;

    /* Wait till controller completes its reset and initialization process */
    result = WaitForInitComplete(privateData);

    if (result == CDN_EOK) {
        if (!privateData->xSpiIot) {
            CPS_REG_WRITE(&regs->trd_error_intr_en, 0xFFFFFFFFU);
        }

        /* Read ctrl_features_reg register */
        ctrl_features_reg = CPS_REG_READ(&regs->ctrl_features_reg);

        /* Read ctrl_version register */
        //xspi_ctrl_version_reg = CPS_REG_READ(&regs->xspi_ctrl_version);
        xspi_ctrl_version_reg = 0x65220204;
        
        /* Get available hardware features of the controller */
        GetMaxBankCnt(ctrl_features_reg, &ctrlFeatures->maxBankNum);

        /* Get DMA data width */
        if (CPS_FLD_READ(XSPI__CTRL_FEATURES_REG, DMA_DATA_WIDTH, ctrl_features_reg) == 1U) {
            ctrlFeatures->dmaDataWidth = XSPI_DMA_DATA_WIDTH_64B;
        } else {
            ctrlFeatures->dmaDataWidth = XSPI_DMA_DATA_WIDTH_32B;
        }

        /* Get DMA address width */
        if (CPS_FLD_READ(XSPI__CTRL_FEATURES_REG, DMA_ADDR_WIDTH, ctrl_features_reg) == 1U) {
            ctrlFeatures->dmaAddrWidth = XSPI_DMA_ADDR_WIDTH_64B;
        } else {
            ctrlFeatures->dmaAddrWidth = XSPI_DMA_ADDR_WIDTH_32B;
        }

        if (!privateData->xSpiIot) {
            /* Get boot available feature */
            if (CPS_FLD_READ(XSPI__CTRL_FEATURES_REG, BOOT_AVAILABLE, ctrl_features_reg) == 0U) {
                ctrlFeatures->bootAvailable = false;
            } else {
                ctrlFeatures->bootAvailable = true;
            }

            /* Get maximum number of threads */
            ctrlFeatures->maxThreadNum = privateData->maxThreadNum;
        }

        /* Get major and minor revision number of the controller */
        privateData->ctrlVersion.minorRevNumber   = (uint8_t) CPS_FLD_READ(XSPI__XSPI_CTRL_VERSION, XSPI_CTRL_FIX, xspi_ctrl_version_reg);
        privateData->ctrlVersion.majorRevNumber   = (uint8_t) CPS_FLD_READ(XSPI__XSPI_CTRL_VERSION, XSPI_CTRL_REV, xspi_ctrl_version_reg);

        /* Get controller revision */
        result = GetCtrlRevEnum(privateData->ctrlVersion.majorRevNumber, &privateData->ctrlRev);
    }else{
        printf("WaitForInitComplete failed, result = %d\r\n", result);
    }

    if ((result == CDN_EOK) && (!privateData->xSpiIot)) {
        if (CPS_FLD_READ(XSPI__CTRL_FEATURES_REG, ASF_AVAILABLE, ctrl_features_reg) == 0U) {
            ctrlFeatures->asfAvailable = false;
        } else {
            ctrlFeatures->asfAvailable = true;
        }
    }

    return result;
}

/**
 * Internal function
 * Function updates error details for a failed command
 */
static void GetFailedStatusInfo(const XSPI_PrivateData * privateData, XSPI_CommandStatusInfo * commandStatusInfo)
{
    /* Update command status structure with cause of error */
    if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_DEVICE_ERROR) != 0U) {
        commandStatusInfo->errorDetails.devError = true;
    }

    if (!privateData->xSpiIot) {
        /* DQS error */
        if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_DQS_ERROR) != 0U) {
            commandStatusInfo->errorDetails.dqsError = true;
        }
    }

    /* CRC error */
    if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_CRC_ERROR) != 0U) {
        commandStatusInfo->errorDetails.crcError = true;
    }

    /* BUS error */
    if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_BUS_ERROR) != 0U) {
        commandStatusInfo->errorDetails.busError = true;
    }

    /* Invalid sequence error */
    if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_INVALID_SEQ_ERROR) != 0U) {
        commandStatusInfo->errorDetails.invalidSeqError = true;
    }

    if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
        /* Correctable ECC error */
        if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_ECC_CORR_ERROR) != 0U) {
            commandStatusInfo->errorDetails.eccError = true;
        }

        commandStatusInfo->eccStatus = ACMD_ECC_STAT_FIELD(commandStatusInfo->statusValue);
    }
}

/**
 * Internal function
 * Function gets the command status value for the last executed command and
 * updates the status structure accordingly.
 */
void XSPI_GetLastCommandStatus(XSPI_PrivateData *privateData, XSPI_CommandStatusInfo *commandStatusInfo, bool is_cdma)
{
    if (is_cdma == false) {
        (void) memset(commandStatusInfo, 0, sizeof(*commandStatusInfo));

        /* Read status value from status register if the command is other than CDMA command */
        commandStatusInfo->statusValue = CPS_REG_READ(&privateData->regs->cmd_status);
        //printf("statusValue = 0x%x\r\n", commandStatusInfo->statusValue);
    }

    if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_COMPLETED) != 0U) {

        if ((commandStatusInfo->statusValue & XSPI_CMD_STAT_FAILED) != 0U) {
            commandStatusInfo->status = XSPI_COMMAND_STATUS_FAILURE;

            /* Update error details for a failed command */
            GetFailedStatusInfo((const XSPI_PrivateData *)privateData, commandStatusInfo);

        } else {
            commandStatusInfo->status = XSPI_COMMAND_STATUS_SUCCESS;
        }

    } else {
        if (privateData->lastCommandIgnored == true) {
            privateData->lastCommandIgnored = false;
            commandStatusInfo->status = XSPI_COMMAND_STATUS_IGNORED;
        } else {
            commandStatusInfo->status = XSPI_COMMAND_STATUS_PENDING;
        }
    }
}

/**
 * Sets controller's work mode
 * @param[in] privateData Pointer to driver private data object
 * @param[in] workMode Controller work mode to be set
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EBUSY when controller is busy
 */
uint32_t XSPI_SetWorkMode(XSPI_PrivateData * privateData, const XSPI_WorkMode workMode)
{
    uint32_t ctr_cfg_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetWorkModeSF(privateData, workMode) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Wait for controller to be in IDLE state */
        result = WaitForIdle(privateData);

        ctr_cfg_reg = CPS_REG_READ(&privateData->regs->ctrl_config);    
        ctr_cfg_reg = CPS_FLD_WRITE(XSPI__CTRL_CONFIG, WORK_MODE, ctr_cfg_reg, (uint32_t)workMode);

        /* Set work mode in register */
        CPS_REG_WRITE(&privateData->regs->ctrl_config, ctr_cfg_reg);
    }

    return result;
}

/**
 * Gets controller's current work mode
 * @param[in] privateData Pointer to driver private data object
 * @param[out] workMode Controller work mode
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetWorkMode(XSPI_PrivateData * privateData, XSPI_WorkMode * workMode)
{
    uint32_t ctr_cfg_reg;
    uint32_t mode;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetWorkModeSF(privateData, workMode) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Read register */
        ctr_cfg_reg = CPS_REG_READ(&privateData->regs->ctrl_config);

        /* Read work mode field */
        mode = CPS_FLD_READ(XSPI__CTRL_CONFIG, WORK_MODE, ctr_cfg_reg);
        switch (mode) {
        case 0U:
            *workMode = XSPI_WORK_MODE_DIRECT;
            break;
        case 1U:
            *workMode = XSPI_WORK_MODE_STIG;
            break;
        case 3U:
            *workMode = XSPI_WORK_MODE_AUTO_COMMAND;
            break;
        default:
            *workMode = XSPI_WORK_MODE_UNKNOWN;
            result = CDN_EINVAL;
            break;
        }
    }

    return result;
}

/**
 * Sets events to enable or disable corresponding interrupts
 * @param[in] privateData Pointer to driver private data object
 * @param[in] events Mask of Events to be enabled or disabled
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetEventEnable(XSPI_PrivateData * privateData, uint32_t events)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetEventEnableSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        CPS_REG_WRITE(&privateData->regs->intr_enable, events);
    }

    return result;
}

/**
 * Gets enabled events
 * @param[in] privateData Pointer to driver private data object
 * @param[out] events Enabled events
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetEventEnable(XSPI_PrivateData * privateData, uint32_t * events)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetEventEnableSF(privateData, events) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        *events = CPS_REG_READ(&privateData->regs->intr_enable);
    }

    return result;
}

/**
 * Sets callbacks for different events
 * @param[in] privateData Pointer to driver private data object
 * @param[in] callbacks Callback functions to register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetCallbacks(XSPI_PrivateData* privateData, const XSPI_Callbacks callbacks)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetCallbacksSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        privateData->callbacks = callbacks;
    }
    return result;
}

/**
 * Gets registered callback functions
 * @param[in] privateData Pointer to driver private data object
 * @param[out] callbacks Returns registered callbacks
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetCallbacks(const XSPI_PrivateData* privateData, XSPI_Callbacks* callbacks)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetCallbacksSF(privateData, callbacks) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        *callbacks = privateData->callbacks;
    }
    return result;
}

/**
 * Sets write protection state for all devices
 * @param[in] privateData Pointer to driver private data object
 * @param[in] writeProtectEnabled Write protect state
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EBUSY when controller is busy
 */
uint32_t XSPI_SetWriteProtect(XSPI_PrivateData * privateData, bool writeProtectEnabled)
{
    uint32_t wp_settings_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetWriteProtectSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        wp_settings_reg = CPS_REG_READ(&privateData->regs->wp_settings);

        wp_settings_reg = CPS_FLD_WRITE(XSPI__WP_SETTINGS, WP_ENABLE, wp_settings_reg, ((writeProtectEnabled == true) ? 1U : 0U));
        wp_settings_reg = CPS_FLD_WRITE(XSPI__WP_SETTINGS, WP, wp_settings_reg, ((writeProtectEnabled == true) ? 0U : 1U));

        /* Wait for controller to be in IDLE state */
        result = WaitForIdle(privateData);

        CPS_REG_WRITE(&privateData->regs->wp_settings, wp_settings_reg);
    }

    return result;
}

/**
 * Gets write protection state
 * @param[in] privateData Pointer to driver private data object
 * @param[out] writeProtectEnabled Write protect state
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetWriteProtect(XSPI_PrivateData * privateData, bool * writeProtectEnabled)
{
    uint32_t wp_settings_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetWriteProtectSF(privateData, writeProtectEnabled) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        wp_settings_reg = CPS_REG_READ(&privateData->regs->wp_settings);

        if (CPS_FLD_READ(XSPI__WP_SETTINGS, WP_ENABLE, wp_settings_reg) == 0U) {
            *writeProtectEnabled = false;
        } else {
            *writeProtectEnabled = true;
        }
    }

    return result;
}

/**
 * Sets DMA configuration
 * @param[in] privateData Pointer to driver private data object
 * @param[in] dmaConfig DMA configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetDmaConfig(XSPI_PrivateData * privateData, const XSPI_DmaConfig * dmaConfig)
{
    uint32_t dma_settings_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetDmaConfigSF(privateData, dmaConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        if (!privateData->xSpiIot) {
            dma_settings_reg = CPS_FLD_WRITE(XSPI__DMA_SETTINGS, WORD_SIZE, dma_settings_reg, dmaConfig->wordSize);
            dma_settings_reg = CPS_FLD_WRITE(XSPI__DMA_SETTINGS, OTE, dma_settings_reg, ((dmaConfig->otEnable == true) ? 1U : 0U));
            dma_settings_reg = CPS_FLD_WRITE(XSPI__DMA_SETTINGS, BURST_SEL, dma_settings_reg, dmaConfig->burstSelect);
        }

        dma_settings_reg = CPS_FLD_WRITE(XSPI__DMA_SETTINGS, SDMA_ERR_RSP, dma_settings_reg, ((dmaConfig->sdmaErrorResp == true) ? 1U : 0U));

        /* Wait for controller to be in IDLE state */
        result = WaitForIdle(privateData);

        CPS_REG_WRITE(&privateData->regs->dma_settings, dma_settings_reg);
    }

    return result;
}

/* Internal function */
static uint32_t GetDmaWordSizeEnum(const uint32_t val, XSPI_DmaWordSize * enumVal)
{
    uint32_t i, result = CDN_EINVAL;

    const XSPI_DmaWordSize dmaWordSizeEnums[DMA_WORD_SIZE_ENUM_CNT] = {
        [0U] = XSPI_DMA_WORD_SIZE_BYTE,
        [1U] = XSPI_DMA_WORD_SIZE_16B_WORD,
        [2U] = XSPI_DMA_WORD_SIZE_32B_WORD,
        [3U] = XSPI_DMA_WORD_SIZE_64B_WORD,
    };

    /* Converts uint32_t to enum */
    for (i = 0U; i < DMA_WORD_SIZE_ENUM_CNT; ++i) {
        if ((uint32_t) dmaWordSizeEnums[i] == val) {
            *enumVal = dmaWordSizeEnums[i];
            result = CDN_EOK;
        }
    }

    return result;
}

/**
 * Gets DMA configuration
 * @param[in] privateData Pointer to driver private data object
 * @param[out] dmaConfig DMA configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetDmaConfig(XSPI_PrivateData * privateData, XSPI_DmaConfig * dmaConfig)
{
    uint32_t dma_settings_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetDmaConfigSF(privateData, dmaConfig) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        /* Read register to get DMA configuration */
        dma_settings_reg = CPS_REG_READ(&privateData->regs->dma_settings);

        if (CPS_FLD_READ(XSPI__DMA_SETTINGS, SDMA_ERR_RSP, dma_settings_reg) == 0U) {
            dmaConfig->sdmaErrorResp = false;
        } else {
            dmaConfig->sdmaErrorResp = true;
        }

        if (!privateData->xSpiIot) {
            if (CPS_FLD_READ(XSPI__DMA_SETTINGS, OTE, dma_settings_reg) == 0U) {
                dmaConfig->otEnable = false;
            } else {
                dmaConfig->otEnable = true;
            }

            dmaConfig->burstSelect = (uint8_t) CPS_FLD_READ(XSPI__DMA_SETTINGS, BURST_SEL, dma_settings_reg);

            result |= GetDmaWordSizeEnum(CPS_FLD_READ(XSPI__DMA_SETTINGS, WORD_SIZE, dma_settings_reg), &dmaConfig->wordSize);
        }
    }
    return result;
}

/**
 * Sets SPI clock mode. Allowed to change for SDR transfers only.
 * @param[in] privateData Pointer to driver private data object
 * @param[in] spiClockMode SPI clock mode
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetSpiClockMode(XSPI_PrivateData * privateData, XSPI_SpiClockMode spiClockMode)
{
    uint32_t clk_mode_settings_reg = 0U;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetSpiClockModeSF(privateData, spiClockMode) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        clk_mode_settings_reg = CPS_REG_READ(&privateData->regs->clock_mode_settings);
        clk_mode_settings_reg = CPS_FLD_WRITE(XSPI__CLOCK_MODE_SETTINGS, SPI_CLOCK_MODE, clk_mode_settings_reg, spiClockMode);

        CPS_REG_WRITE(&privateData->regs->clock_mode_settings, clk_mode_settings_reg);
    }

    return result;
}

/**
 * Gets SPI clock mode.
 * @param[in] privateData Pointer to driver private data object
 * @param[out] spiClockMode SPI clock mode
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetSpiClockMode(XSPI_PrivateData * privateData, XSPI_SpiClockMode * spiClockMode)
{
    uint32_t clk_mode_settings_reg;
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetSpiClockModeSF(privateData, spiClockMode) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        clk_mode_settings_reg = CPS_REG_READ(&privateData->regs->clock_mode_settings);

        if (CPS_FLD_READ(XSPI__CLOCK_MODE_SETTINGS, SPI_CLOCK_MODE, clk_mode_settings_reg) == 0U) {
            *spiClockMode = XSPI_SPI_CLOCK_MODE_0;
        } else {
            *spiClockMode = XSPI_SPI_CLOCK_MODE_3;
        }
    }
    return result;
}

/**
 * Function sets the reset configuration which is used to reset memory banks
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetBankCfg Reset configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetResetConfig(XSPI_PrivateData * privateData, const XSPI_ResetDeviceConfig * resetBankCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t reset_pin_settings_reg = 0U;
    uint8_t i, bankOffset;

    /* Check parameters */
    if (XSPI_SetResetConfigSF(privateData, resetBankCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        reset_pin_settings_reg = CPS_REG_READ(&privateData->regs->reset_pin_settings);

        if (resetBankCfg->hwResetType == XSPI_HARDWARE_RESET_OPTION_RESET_PIN) {
            for (i = 0U; i < privateData->ctrlFeatures.maxBankNum; i++) {
                bankOffset = XSPI__RESET_PIN_SETTINGS__SW_CTRLED_HW_RST_BANK0_SHIFT + i;
                if ((i < 32U) && (bankOffset < 32U) && ((((uint32_t)resetBankCfg->bankSelectMask >> i) & 1U) == 1U)) {
                    reset_pin_settings_reg |= ((uint32_t)1U << bankOffset);
                }
            }
        } else {
            reset_pin_settings_reg = CPS_FLD_WRITE(XSPI__RESET_PIN_SETTINGS, RST_DQ3_ENABLE, reset_pin_settings_reg, 1U);
        }

        /* Set hardware reset option */
        reset_pin_settings_reg = CPS_FLD_WRITE(XSPI__RESET_PIN_SETTINGS, SW_CTRLED_HW_RST_OPTION, reset_pin_settings_reg, resetBankCfg->hwResetType);

        CPS_REG_WRITE(&privateData->regs->reset_pin_settings, reset_pin_settings_reg); 
    }

    return result;
}

/**
 * Function gets the reset configuration currently set.
 * @param[in] privateData pointer to driver private data object
 * @param[out] resetBankCfg Reset configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetResetConfig(XSPI_PrivateData * privateData, XSPI_ResetDeviceConfig * resetBankCfg)
{
    uint32_t result = CDN_EOK;
    uint32_t reset_pin_settings_reg = 0U;

    /* Check parameters */
    if (XSPI_GetResetConfigSF(privateData, resetBankCfg) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        reset_pin_settings_reg = CPS_REG_READ(&privateData->regs->reset_pin_settings);

        if (CPS_FLD_READ(XSPI__RESET_PIN_SETTINGS, SW_CTRLED_HW_RST_OPTION, reset_pin_settings_reg) == 1U) {
            resetBankCfg->hwResetType = XSPI_HARDWARE_RESET_OPTION_DQ3_PIN;
        } else {
            resetBankCfg->hwResetType = XSPI_HARDWARE_RESET_OPTION_RESET_PIN;
        }

        resetBankCfg->bankSelectMask = (uint8_t) ((reset_pin_settings_reg >> XSPI__RESET_PIN_SETTINGS__SW_CTRLED_HW_RST_BANK0_SHIFT) & 0xFFU);
    }

    return result;
}

/**
 * Asserts the software controlled hardware reset signal. 
 * Reset configuration must be set before calling this function.
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EBUSY when controller is busy
 */
uint32_t XSPI_AssertReset(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t reset_pin_settings_reg = 0U;

    /* Check parameters */
    if (XSPI_AssertResetSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        reset_pin_settings_reg = CPS_REG_READ(&privateData->regs->reset_pin_settings);

        reset_pin_settings_reg = CPS_FLD_WRITE(XSPI__RESET_PIN_SETTINGS, SW_CTRLED_HW_RST, reset_pin_settings_reg, 0U);

        /* Wait for controller to be in IDLE state */
        result = WaitForIdle(privateData);

        CPS_REG_WRITE(&privateData->regs->reset_pin_settings, reset_pin_settings_reg);
    }

    return result;
}

/**
 * Deasserts the software controlled hardware reset signal. 
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EBUSY when controller is busy
 */
uint32_t XSPI_DeAssertReset(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t reset_pin_settings_reg = 0U;

    /* Check parameters */
    if (XSPI_DeAssertResetSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        reset_pin_settings_reg = CPS_REG_READ(&privateData->regs->reset_pin_settings);

        reset_pin_settings_reg = CPS_FLD_WRITE(XSPI__RESET_PIN_SETTINGS, RST_DQ3_ENABLE, reset_pin_settings_reg, 0U);

        reset_pin_settings_reg = CPS_FLD_WRITE(XSPI__RESET_PIN_SETTINGS, SW_CTRLED_HW_RST, reset_pin_settings_reg, 1U);

        /* Wait for controller to be in IDLE state */
        result = WaitForIdle(privateData);

        CPS_REG_WRITE(&privateData->regs->reset_pin_settings, reset_pin_settings_reg);
    }

    return result;
}

/**
 * Function sets relative device selection and reset recovery delays
 * @param[in] privateData Pointer to driver private data object
 * @param[in] deviceRelativeDelays Device relative delays
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_SetDeviceRelativeDelays(XSPI_PrivateData * privateData, const XSPI_DeviceRelativeDelays * deviceRelativeDelays)
{
    uint32_t result = CDN_EOK;
    uint32_t dev_delay_reg = 0U;

    /* Check parameters */
    if (XSPI_SetDeviceRelativeDelaysSF(privateData, deviceRelativeDelays) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        dev_delay_reg = CPS_FLD_WRITE(XSPI__DEV_DELAY_REG, CSDA_MIN_DELAY, dev_delay_reg, deviceRelativeDelays->csdaMinDelay);
        dev_delay_reg = CPS_FLD_WRITE(XSPI__DEV_DELAY_REG, CSEOT_DELAY, dev_delay_reg, deviceRelativeDelays->cseotDelay);
        dev_delay_reg = CPS_FLD_WRITE(XSPI__DEV_DELAY_REG, CSSOT_DELAY, dev_delay_reg, deviceRelativeDelays->cssotDelay);

        CPS_REG_WRITE(&privateData->regs->dev_delay_reg, dev_delay_reg);
    }

    return result;
}

/**
 * Function gets device relative delays
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceRelativeDelays Device relative delays
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_GetDeviceRelativeDelays(XSPI_PrivateData * privateData, XSPI_DeviceRelativeDelays * deviceRelativeDelays)
{
    uint32_t result = CDN_EOK;
    uint32_t dev_delay_reg = 0U;

    /* Check parameters */
    if (XSPI_GetDeviceRelativeDelaysSF(privateData, deviceRelativeDelays) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        dev_delay_reg = CPS_REG_READ(&privateData->regs->dev_delay_reg);

        deviceRelativeDelays->csdaMinDelay = (uint8_t) CPS_FLD_READ(XSPI__DEV_DELAY_REG, CSDA_MIN_DELAY, dev_delay_reg);
        deviceRelativeDelays->cseotDelay = (uint8_t) CPS_FLD_READ(XSPI__DEV_DELAY_REG, CSEOT_DELAY, dev_delay_reg);
        deviceRelativeDelays->cssotDelay = (uint8_t) CPS_FLD_READ(XSPI__DEV_DELAY_REG, CSSOT_DELAY, dev_delay_reg);
    }

    return result;
}

/**
 * Sets maximum number of xspi_clk cycles through CS# will be active
 * @param[in] privateData           Pointer to driver private data object
 * @param[in] activeDevMaxCycles    Maximum number of max cycles during device is active
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetP2ActiveDevMaxCycles(XSPI_PrivateData * privateData, uint32_t activeDevMaxCycles)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_SetP2ActiveDevMaxCyclesSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Set device active cycles */
        CPS_REG_WRITE(&privateData->regs->dev_active_max_reg, activeDevMaxCycles);
    }

    return result;
}

/**
 * Gets maximum number of xspi_clk cycles through CS# will be active
 * @param[in] privateData           Pointer to driver private data object
 * @param[out] activeDevMaxCycles   Pointer to maximum number of max cycles during device is active
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetP2ActiveDevMaxCycles(XSPI_PrivateData * privateData, uint32_t * activeDevMaxCycles)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_GetP2ActiveDevMaxCyclesSF(privateData, activeDevMaxCycles) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Get device active cycles */
        *activeDevMaxCycles = CPS_REG_READ(&privateData->regs->dev_active_max_reg);
    }

    return result;
}

/**
 * Sets relative device selection delay applicable for JEDEC Reset command (Since R003)
 * @param[in]  privateData    Pointer to driver private data object
 * @param[in]  tCSLDelay      tCSL delay timing for JEDEC RESET command
 *
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_SetJedecResetTimingConfig(XSPI_PrivateData * privateData, const XSPI_JedecResetTimingConfig * jedecRstTiming)
{
    uint32_t result = CDN_EOK;
    uint32_t jedec_rst_timing_reg = 0U;

    /* Check parameters */
    if (XSPI_SetJedecResetTimingConfSF(privateData, jedecRstTiming) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Check controller revision */
        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {
            /* Set tCSH timing */
            jedec_rst_timing_reg = CPS_FLD_WRITE(XSPI__JEDEC_RST_TIMING_REG, TCSH_DELAY, jedec_rst_timing_reg, (uint32_t)jedecRstTiming->tCSH);

            /* Set tCSL timing */
            jedec_rst_timing_reg = CPS_FLD_WRITE(XSPI__JEDEC_RST_TIMING_REG, TCSL_DELAY, jedec_rst_timing_reg, (uint32_t)jedecRstTiming->tCSL);
            CPS_REG_WRITE(&privateData->regs->jedec_rst_timing_reg, jedec_rst_timing_reg);
        }
    }

    return result;
}

/**
 * Gets relative device selection delay applicable for JEDEC Reset command (Since R003)
 * @param[in]  privateData   Pointer to driver private data object
 * @param[out] tCSLDelay     tCSL delay timing for JEDEC RESET command
 *
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_GetJedecResetTimingConfig(XSPI_PrivateData * privateData, XSPI_JedecResetTimingConfig * jedecRstTiming)
{
    uint32_t result = CDN_EOK;
    uint32_t jedec_rst_timing_reg;

    /* Check parameters */
    if (XSPI_GetJedecResetTimingConfSF(privateData, jedecRstTiming) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {

        /* Check controller revision */
        if (privateData->ctrlRev < XSPI_CTRL_REV_R003) {
            result = CDN_ENOTSUP;
        } else {
            jedec_rst_timing_reg = CPS_REG_READ(&privateData->regs->jedec_rst_timing_reg);

            /* Get tCSL timing */
            jedecRstTiming->tCSL = (uint8_t) CPS_FLD_READ(XSPI__JEDEC_RST_TIMING_REG, TCSL_DELAY, jedec_rst_timing_reg);

            /* Get tCSH timing */
            jedecRstTiming->tCSH = (uint8_t) CPS_FLD_READ(XSPI__JEDEC_RST_TIMING_REG, TCSH_DELAY, jedec_rst_timing_reg);
        }
    }

    return result;
}

/* parasoft-end-suppress METRICS-36-3 */

