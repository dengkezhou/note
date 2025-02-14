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
 * xspi_main.c
 * This file contains implementation of initialization functions for driver.
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

#include "xspi_priv.h"
#include "xspi_core.h"

#include "xspi_sanity.h"

/* Function gives available number of threads configured in the controller */
void GetMaxThreadCnt(volatile XSPI_Regs * regsBase, uint8_t * max_thread_cnt)
{
    uint32_t ctrl_features_reg = 0U;
    uint8_t n_threads;

    /* Read ctrl_features register */
    ctrl_features_reg = CPS_REG_READ(&regsBase->ctrl_features_reg);

    n_threads = (uint8_t) CPS_FLD_READ(XSPI__CTRL_FEATURES_REG, N_THREADS, ctrl_features_reg);

    /* Get available thread count */
    switch(n_threads) {
    case 0U :
        *max_thread_cnt = 1U;
        break;
    case 1U :
        *max_thread_cnt = 2U;
        break;
    case 2U :
        *max_thread_cnt = 4U;
        break;
    case 3U :
        *max_thread_cnt = 8U;
        break;
    default :
        *max_thread_cnt = 1U;
        break;
    }
}

/**
 * Gets the driver memory requirements to support specified configuration
 * @param[in] config Driver/hardware configuration required
 * @param[out] sysReq Returns the size of memory allocations required
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_Probe(XSPI_Config * config, XSPI_SysReq * sysReq)
{
    uint32_t result = CDN_EOK;
    size_t cdma_desc_size = sizeof(XSPI_CdmaCommandDescriptor);
    size_t private_data_size = sizeof(XSPI_PrivateData);
    uint32_t total_cdma_desc_count;

    uint32_t ctrl_version;
    uint16_t ctrl_magic_num;

    /* Check parameters */
    if (XSPI_ProbeSF(config, sysReq) != CDN_EOK) {
        result = CDN_EINVAL;
    } else if (config->regsBase == NULL) {
        result = CDN_EINVAL;
    } else {
        ctrl_version = CPS_REG_READ(&config->regsBase->xspi_ctrl_version);

        ctrl_magic_num = CPS_FLD_READ(XSPI__XSPI_CTRL_VERSION, XSPI_CTRL_MAGIC_NUMBER, ctrl_version);

        switch (ctrl_magic_num) {
            case XSPI_MAGIC_NUMBER_IOT_CONFIG:
                config->xSpiIot = true;
                break;

            case XSPI_MAGIC_NUMBER_FULL_CONFIG:
                config->xSpiIot = false;
                break;

            default:
                printf("xspi version magic number check failed!\n");
                result = CDN_EIO;
        }
    }

    /* Calculate system requirements sizes */
    if (result == CDN_EOK) {

        /* On FULL configuration read number of threads and calculate size for CDMA descriptors */
        if (!config->xSpiIot) {
            GetMaxThreadCnt(config->regsBase, &config->maxThreadNum);

            total_cdma_desc_count = (uint32_t)config->cdmaCmdsMaxNum * config->maxThreadNum;

            sysReq->cdmaCmdsDescTotalSize = (size_t)total_cdma_desc_count * cdma_desc_size;
            /* Add some buffer space to make address aligned */
            sysReq->cdmaCmdsDescTotalSize += 15U;
        }

        sysReq->privateDataSize = private_data_size;
    }

    return result;
}

/**
 * Initialize the driver as specified in the Config structure.
 * Must be called before all other access APIs.
 * @param[in] privateData Memory pointer to the uninitialized private data of the size specified by probe
 * @param[in] config Specifies driver/hardware configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_Init(XSPI_PrivateData * privateData, const XSPI_Config * config)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if ((privateData == NULL) || (config == NULL)) {
        printf("privateData NULL or config NULL\n");
        result = CDN_EINVAL;
    } else {
        (void) memset(privateData, 0, sizeof(*privateData));

        if (!config->xSpiIot) {
            privateData->cdmaCmdsDescBase = config->cdmaCmdsDescBase;

            /* Get the CDMA descriptor base address aligned */
            while ((privateData->cdmaCmdsDescBase % 8U) != 0U) {
                privateData->cdmaCmdsDescBase += 1U;
            }

            privateData->cdmaCmdsMaxNum = config->cdmaCmdsMaxNum;
        }

        privateData->regs = (volatile XSPI_Regs *)config->regsBase;
        privateData->callbacks = config->callbacks;
        privateData->lastCommandIgnored = false;
        privateData->xSpiIot = config->xSpiIot;
        privateData->maxThreadNum = config->maxThreadNum;

        /* parasoft-begin-suppress MISRA2012-RULE-11_4-4 "Pointer to object type 'volatile XSPI_Regs *' should not be converted to integral type 'unsigned int'", DRV-5060" */
        privateData->legacyStatSeqReg6Addr = (volatile XSPI_Regs *)(((uintptr_t)config->regsBase) + LEGACY_STAT_SEQ_CFG_6_REG);
        /* parasoft-end-suppress MISRA2012-RULE-11_4-4 */
        result = CoreInit(privateData);
    }
    return result;
}

/**
 * Destructor for the driver
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_Destroy(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;

    /* Check parameters */
    if (XSPI_DestroySF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        (void) memset(privateData, 0x00, sizeof(XSPI_PrivateData));
    }

    return result;
}

/**
 * Start the XSPI driver, enabling interrupts. This is called after the
 * client has successfully initialized the driver and hooked the driver's
 * ISR (the isr member of this struct) to the IRQ.
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_Start(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t intr_en_reg;

    /* Check parameters */
    if (XSPI_StartSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        intr_en_reg = CPS_REG_READ(&privateData->regs->intr_enable);
        intr_en_reg = CPS_FLD_SET(XSPI__INTR_ENABLE, INTR_EN, intr_en_reg);
        CPS_REG_WRITE(&privateData->regs->intr_enable, intr_en_reg);
    }

    return result;
}

/**
 * Stops the XSPI driver by disabling interrupts
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_Stop(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t intr_en_reg;

    /* Check parameters */
    if (XSPI_StopSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        intr_en_reg = CPS_REG_READ(&privateData->regs->intr_enable);
        intr_en_reg = CPS_FLD_CLEAR(XSPI__INTR_ENABLE, INTR_EN, intr_en_reg);
        CPS_REG_WRITE(&privateData->regs->intr_enable, intr_en_reg);
    }

    return result;
}

/* Function handles command completed interrupt for ACMD mode */
static uint32_t HandleAcmdCmdCompInt(XSPI_PrivateData * privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t trd_comp_intr_status_reg, trd_err_intr_status_reg;
    uint8_t trd_comp_mask, trd_err_stat;
    XSPI_WorkMode workMode = XSPI_WORK_MODE_UNKNOWN;
    volatile XSPI_Regs * regs;

    /* Check controller work mode */
    if (XSPI_GetWorkMode(privateData, &workMode) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        if (workMode == XSPI_WORK_MODE_AUTO_COMMAND) {
            regs = privateData->regs;

            /* Get completion status */
            trd_comp_intr_status_reg = CPS_REG_READ(&regs->trd_comp_intr_status);
            /* Write to clear */
            CPS_REG_WRITE(&regs->trd_comp_intr_status, trd_comp_intr_status_reg);

            trd_comp_mask = (uint8_t)(trd_comp_intr_status_reg & 0xFFU);

            /* Get error status */
            trd_err_intr_status_reg = CPS_REG_READ(&regs->trd_error_intr_status);
            /* Write to clear */
            CPS_REG_WRITE(&regs->trd_error_intr_status, trd_err_intr_status_reg);

            trd_err_stat = (uint8_t)(trd_err_intr_status_reg & 0xFFU);

            if ((trd_comp_mask != 0U) && (privateData->callbacks.acmdCmdCompleteHandler != NULL)) {
                privateData->callbacks.acmdCmdCompleteHandler(privateData, trd_comp_mask, trd_err_stat);
            }
        }
    }

    return result;
}

static void HandleDirectEccErrInt(XSPI_PrivateData *privateData, uint32_t intr_status_reg, const XSPI_DirectErrorCallbacks *directErrorCb)
{
    if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
        /* Correctable ECC error */
        if (((intr_status_reg & XSPI_EVENT_DWM_CORR_ECC_ERROR) != 0U) && (directErrorCb->dirCorrEccErrorHandler != NULL)) {
            directErrorCb->dirCorrEccErrorHandler(privateData);
        }

        /* Uncorrectable ECC error */
        if (((intr_status_reg & XSPI_EVENT_DWM_UNCORR_ECC_ERROR) != 0U) && (directErrorCb->dirUncorrEccErrorHandler != NULL)) {
            directErrorCb->dirUncorrEccErrorHandler(privateData);
        }
    }
}

/* Function handles Direct mode error interrupts */
static void HandleDirectErrInt(XSPI_PrivateData *privateData, uint32_t intr_status_reg)
{
    XSPI_DirectErrorCallbacks *directErrorCb = &privateData->callbacks.directErrorCb;

    /* Invalid command sequence error */
    if (((intr_status_reg & XSPI_EVENT_DWM_CMD_ERROR) != 0U) && (directErrorCb->dirInvalidCommandSeqHandler != NULL)) {
        directErrorCb->dirInvalidCommandSeqHandler(privateData);
    }

    /* DQS underrun or overflow error */
    if (!privateData->xSpiIot) {
        if (((intr_status_reg & XSPI_EVENT_DWM_DQS_ERROR) != 0U) && (directErrorCb->dirDqsErrorHandler != NULL)) {
            directErrorCb->dirDqsErrorHandler(privateData);
        }
    }

    /* CRC error */
    if (((intr_status_reg & XSPI_EVENT_DWM_CRC_ERROR) != 0U) && (directErrorCb->dirCrcErrorHandler != NULL)) {
        directErrorCb->dirCrcErrorHandler(privateData);
    }

    HandleDirectEccErrInt(privateData, intr_status_reg, (const XSPI_DirectErrorCallbacks *)directErrorCb);
}

/* Function handles Master Data DMA and Command DMA target error interrupts */
static void HandleTargetErrInt(XSPI_PrivateData *privateData, uint32_t intr_status_reg)
{
    uint32_t dma_target_errl_reg, dma_target_errh_reg;
    uint64_t dmaTargetErrorAddr;
    volatile XSPI_Regs *regs = privateData->regs;

    dma_target_errl_reg = CPS_REG_READ(&regs->dma_target_error_l);
    dma_target_errh_reg = CPS_REG_READ(&regs->dma_target_error_h);
    dmaTargetErrorAddr = ((uint64_t)dma_target_errh_reg << 32U) | dma_target_errl_reg;

    /* Data DMA Master target error interrupt */
    if (((intr_status_reg & XSPI_EVENT_DMA_MASTER_TGT_ERROR) != 0U) && (privateData->callbacks.masterDataDMAErrorHandler != NULL)) {
        privateData->callbacks.masterDataDMAErrorHandler(privateData, dmaTargetErrorAddr);
    }

    /* Auto CMD Engine target error interrupt */
    if (((intr_status_reg & XSPI_EVENT_ACMD_TARGET_ERROR) != 0U) && (privateData->callbacks.commandDMAErrorHandler != NULL)) {
        privateData->callbacks.commandDMAErrorHandler(privateData, dmaTargetErrorAddr);
    }
}

/* Function handles Slave DMA trigger interrupt */
static uint32_t HandleSdmaTrigInt(XSPI_PrivateData *privateData, uint32_t intr_status_reg)
{
    uint32_t result = CDN_EOK;
    uint32_t sdma_trd_info_reg, sdma_addr0_reg, sdma_addr1_reg, sdmaTransSize;
    XSPI_DataTransDirection sdmaDir;
    XSPI_StigSdmaIrqInfo stigIrqInfo;
    XSPI_AcmdSdmaIrqInfo acmdIrqInfo;
    XSPI_WorkMode workMode = XSPI_WORK_MODE_UNKNOWN;

    /* Get controller work mode */
    if (XSPI_GetWorkMode(privateData, &workMode) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        if ((intr_status_reg & XSPI_EVENT_SDMA_TRIGGER) != 0U) {
            sdmaTransSize = CPS_REG_READ(&privateData->regs->sdma_size);
            sdma_trd_info_reg = CPS_REG_READ(&privateData->regs->sdma_trd_info);

            /* Get SDMA direction */
            if (CPS_FLD_READ(XSPI__SDMA_TRD_INFO, SDMA_DIR, sdma_trd_info_reg) == 0U) {
                sdmaDir = XSPI_DATA_TRANS_DIR_READ;
            } else {
                sdmaDir = XSPI_DATA_TRANS_DIR_WRITE;
            }

            if (workMode == XSPI_WORK_MODE_STIG) {
                stigIrqInfo.transferSize = sdmaTransSize;
                stigIrqInfo.direction = sdmaDir;
                stigIrqInfo.stigSdmaBuff = privateData->stigSdmaBuff;
                if (privateData->callbacks.sdmaCb.stigSdmaTransactionHandler != NULL) {
                    privateData->callbacks.sdmaCb.stigSdmaTransactionHandler(privateData, stigIrqInfo);
                } else {
                    /* Return error as SDMA handler for STIG mode is not set */
                    result = CDN_EINVAL;
                }
            } else if (!privateData->xSpiIot && (workMode == XSPI_WORK_MODE_AUTO_COMMAND)) {
                acmdIrqInfo.transferSize = sdmaTransSize;
                acmdIrqInfo.direction = sdmaDir;
                /* Get SDMA destination/source address */
                sdma_addr0_reg = CPS_REG_READ(&privateData->regs->sdma_addr0);
                sdma_addr1_reg = CPS_REG_READ(&privateData->regs->sdma_addr1);
                acmdIrqInfo.acmdSdmaBuff = ((uint64_t)sdma_addr1_reg << 32U) | sdma_addr0_reg;
                acmdIrqInfo.thread = (uint8_t) CPS_FLD_READ(XSPI__SDMA_TRD_INFO, SDMA_TRD, sdma_trd_info_reg);
                if (privateData->callbacks.sdmaCb.acmdSdmaTransactionHandler != NULL) {
                    privateData->callbacks.sdmaCb.acmdSdmaTransactionHandler(privateData, acmdIrqInfo);
                } else {
                    /* Return error as SDMA handler for ACMD mode is not set */
                    result = CDN_EINVAL;
                }
            } else {
                /* Misra Violation */
            }
        }
    }
    return result;
}

/* Function handles open drain pins interrupts */
static void HandleOpenDrainInts(XSPI_PrivateData * privateData, uint32_t intr_status_reg)
{
    /* Check controller revision */
    if (privateData->ctrlRev >= XSPI_CTRL_REV_R003) {
        if (((intr_status_reg & XSPI_EVENT_OPEN_DRAIN_3_PIN_CHANGED) != 0U) &&
            (privateData->callbacks.openDrainCallbacks.openDrainPin3ChangedHandler != NULL)) {

            /* Handle open drain pin 3 interrupt */
            privateData->callbacks.openDrainCallbacks.openDrainPin3ChangedHandler(privateData, OPEN_DRAIN_PIN_INDEX_3);
        }

        if (((intr_status_reg & XSPI_EVENT_OPEN_DRAIN_2_PIN_CHANGED) != 0U) &&
            (privateData->callbacks.openDrainCallbacks.openDrainPin2ChangedHandler != NULL)) {

            /* Handle open drain pin 2 interrupt */
            privateData->callbacks.openDrainCallbacks.openDrainPin2ChangedHandler(privateData, OPEN_DRAIN_PIN_INDEX_2);
        }

        if (((intr_status_reg & XSPI_EVENT_OPEN_DRAIN_1_PIN_CHANGED) != 0U) &&
            (privateData->callbacks.openDrainCallbacks.openDrainPin1ChangedHandler != NULL)) {

            /* Handle open drain pin 1 interrupt */
            privateData->callbacks.openDrainCallbacks.openDrainPin1ChangedHandler(privateData, OPEN_DRAIN_PIN_INDEX_1);
        }

        if (((intr_status_reg & XSPI_EVENT_OPEN_DRAIN_0_PIN_CHANGED) != 0U) &&
            (privateData->callbacks.openDrainCallbacks.openDrainPin0ChangedHandler != NULL)) {

            /* Handle open drain pin 0 interrupt */
            privateData->callbacks.openDrainCallbacks.openDrainPin0ChangedHandler(privateData, OPEN_DRAIN_PIN_INDEX_0);
        }
    }
}

/* Function handles miscellaneous interrupts */
static void HandleMiscInt(XSPI_PrivateData *privateData, uint32_t intr_status_reg)
{
    if (!privateData->xSpiIot) {
        /* Target error interrupts */
        HandleTargetErrInt(privateData, intr_status_reg);
    }

    /* Handle open drain interrupts */
    HandleOpenDrainInts(privateData, intr_status_reg);

    /* Not allowed access to slave DMA interface interrupt */
    if (((intr_status_reg & XSPI_EVENT_SDMA_ERROR) != 0U) && (privateData->callbacks.sdmaCb.sdmaErrorHandler != NULL)) {
        privateData->callbacks.sdmaCb.sdmaErrorHandler(privateData);
    }

    /* Stig done interrupt */
    if (((intr_status_reg & XSPI_EVENT_STIG_DONE) != 0U) && (privateData->callbacks.stigDoneHandler != NULL)) {
        privateData->callbacks.stigDoneHandler(privateData);
    }

    /* Command ignored interrupt */
    if ((intr_status_reg & XSPI_EVENT_COMMAND_IGNORED) != 0U) {
        privateData->lastCommandIgnored = true;
        if (privateData->callbacks.commandIgnoredHandler != NULL) {
            privateData->callbacks.commandIgnoredHandler(privateData);
        }
    }

    /* Controller idle interrupt */
    if (((intr_status_reg & XSPI_EVENT_IDLE_STATE) != 0U) && (privateData->callbacks.idleStateDetHandler != NULL)) {
        privateData->callbacks.idleStateDetHandler(privateData);
    }
}

/**
 * Driver ISR. Platform-specific code is responsible for ensuring this gets called
 * when the corresponding hardware's interrupt is asserted. Registering the ISR
 * should be done after calling init, and before calling start. The driver's ISR
 * will not attempt to lock any locks, but will perform client callbacks. If the
 * client wishes to defer processing to non-interrupt time, it is responsible for
 * doing so. This function must not be called after calling destroy and releasing
 * private data memory.
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t XSPI_Isr(XSPI_PrivateData *privateData)
{
    uint32_t result = CDN_EOK;
    uint32_t intr_status_reg;

    /* Check parameters */
    if (XSPI_IsrSF(privateData) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        intr_status_reg = CPS_REG_READ(&privateData->regs->intr_status);
        /* Write to clear */
        CPS_REG_WRITE(&privateData->regs->intr_status, intr_status_reg);

        /* Direct mode error interrupts */
        HandleDirectErrInt(privateData, intr_status_reg);

        /* Trigger condition for slave DMA met interrupt */
        result |= HandleSdmaTrigInt(privateData, intr_status_reg);

        if (!privateData->xSpiIot) {
            /* Command completed interrupt */
            result |= HandleAcmdCmdCompInt(privateData);
        }

        /* Other interrupts */
        HandleMiscInt(privateData, intr_status_reg);

    }
    return result;
}

