/******************************************************************************
 * Copyright (C) 2016-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio_cq.c
 * Module implementing support for command queuing
 *****************************************************************************/

#include "cdn_errno.h"
#include "sdio_types.h"
#include "sdio_config.h"
#include "sdio_errors.h"
#include "sdio_host.h"
#include "sdio_utils.h"
#include "sdio_cq.h"
#include "sdio_debug.h"
#include "sdio_card_general.h"
#include "sdio_request.h"
#include "csdd_structs_if.h"

#define CQ_TRANS_DESC_MAX_BUFF_SIZE         (64U * 1024U)

/* prepare argument for CQ task management command */
static inline uint32_t CQ_TASK_MGMT_ARG(uint32_t taskId, uint32_t tmOpcode)
{
    return (((taskId & 0x1FU) << 16) | (tmOpcode & 0xFU));
}

/* task management argument - discard task */
#define  CQ_TASK_MGMT_ARG_TM_DISCARD_TASK      1U
/* task management argument - discard queue */
#define  CQ_TASK_MGMT_ARG_TM_DISCARD_QUEUE     2U

/* number of supported tasks */
#define  CQ_HOST_NUMBER_OF_TASKS   32U
/* direct command task ID */
#define  CQ_DCMD_TASK_ID           31U

/* macro checks if given task is direc to command task */
static inline bool CQ_IS_DIRECT_TASK(const CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    return ((pSlot->CQDcmdEnabled != 0U) && (taskId == CQ_DCMD_TASK_ID));
}

/* Task Descriptor Fields (for DCMD tasks) - 64 bit*/
typedef struct CQ_DcmdTaskDesc64_s {
    /* standard flags config
     * + timing, command index and response type */
    uint32_t flags;
    uint32_t argument;
} CQ_DcmdTaskDesc64;

/* Task Descriptor Fields (for DCMD tasks) - 128 bit*/
typedef struct CQ_DcmdTaskDesc128_s {
    /* standard flags config
     * + timing, command index and response type */
    uint32_t flags;
    uint32_t argument;
    uint32_t reserved[2];
} CQ_DcmdTaskDesc128;

typedef struct CQ_NopDesc64_s {
    uint32_t flags;
    uint32_t reserved;
} CQ_NopDesc64;

typedef struct CQ_NopDesc128_s {
    uint32_t flags;
    uint32_t reserved;
    uint32_t reserved2[2];
} CQ_NopDesc128;

typedef struct CQ_DcmdDesc64_s {
    CQ_DcmdTaskDesc64 dcmdTaskDesc;
    CQ_NopDesc64 nopDesc;
} CQ_DcmdDesc64;

typedef struct CQ_DcmdDesc128_s {
    CQ_DcmdTaskDesc128 dcmdTaskDesc;
    CQ_NopDesc128 nopDesc;
} CQ_DcmdDesc128;

typedef struct CQ_TransDesc64_s {
    uint16_t flags;
    /* Length of data buffer in bytes */
    uint16_t length;
    /* Data buffer address in host memory*/
    uint32_t addressLow;
} CQ_TransDesc64;

typedef struct CQ_TransDesc128_s {
    uint16_t flags;
    /* Length of data buffer in bytes */
    uint16_t length;
    /* Data buffer address in host memory, lower part */
    uint32_t addressLow;
    /* Data buffer address in host memory, higher part */
    uint32_t addressHigh;
    uint32_t reserved;
} CQ_TransDesc128;

typedef struct CQ_TaskDesc64_s {
    uint16_t flags;
    uint16_t blockCount;
    uint32_t blockAddress;
} CQ_TaskDesc64;

typedef struct CQ_TaskDesc128_s {
    uint16_t flags;
    uint16_t blockCount;
    uint32_t blockAddress;
    uint32_t reserved[2];
} CQ_TaskDesc128;

typedef struct CQ_Desc64_s {
    CQ_TaskDesc64 taskDesc;
    CQ_TransDesc64 transDesc;
} CQ_Desc64;

typedef struct CQ_Desc128_s {
    CQ_TaskDesc128 taskDesc;
    CQ_TransDesc128 transDesc;
} CQ_Desc128;

typedef struct  CQ_TaskErrorStatus_s {
    uint8_t taskId;
    uint8_t isDataError;
    uint8_t isCmdError;
}  CQ_TaskErrorStatus;

static void CQDumpRequest(const CSDD_CQRequest *pRequest, uint8_t isError)
{
    uint32_t i;
    if (isError != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "task ID=%d, numberOfBuffers=0x%lX, BlockCount=%lu, BlockAddress=%u\n",
                     (uint16_t)pRequest->taskId,
                     pRequest->numberOfBuffers, pRequest->blockCount,
                     pRequest->blockAddress);
        for (i = 0; i < pRequest->numberOfBuffers; i++) {
            DbgMsg(DBG_GEN_MSG, DBG_CRIT, "\tCQDumpRequest buffers[%d].buffPhyAddr=%lx, buffers[%d].bufferSize=%d\n",
                         i, pRequest->buffers[i].buffPhyAddr, i, pRequest->buffers[i].bufferSize);
        }
    }
    else {
        DbgMsg(DBG_GEN_MSG, DBG_FYI, "CQDumpRequest task ID=%d, numberOfBuffers=0x%lX, BlockCount=%lu, BlockAddress=%u\n",
                    (uint16_t)pRequest->taskId,
                    pRequest->numberOfBuffers, pRequest->blockCount,
                    pRequest->blockAddress);
        for (i = 0; i < pRequest->numberOfBuffers; i++) {
            DbgMsg(DBG_GEN_MSG, DBG_FYI, "\tCQDumpRequest buffers[%d].buffPhyAddr=%lx, buffers[%d].bufferSize=%d\n",
                        i, pRequest->buffers[i].buffPhyAddr, i, pRequest->buffers[i].bufferSize);
        }
    }
}

static void CQDumpDcmdRequest(const CSDD_CQDcmdRequest *pRequest, uint8_t isError)
{
    if (isError != 0U) {
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "command index %d, command argument %d \n",
                     pRequest->cmdIdx, pRequest->argument);
    }
    else {
        DbgMsg(DBG_GEN_MSG, DBG_FYI, "command index %d, command argument %d \n",
                    pRequest->cmdIdx, pRequest->argument);
    }
}

/* function finishes request but only if attached */
static void FinishRequest(CSDD_SDIO_Slot* pSlot, uint8_t taskId,
                          CSDD_CQReqStat status)
{
    if (pSlot->CQCurrentReq[taskId] != NULL) {
        if (status == CSDD_CQ_REQ_STAT_FAILED) {
            CQDumpRequest(pSlot->CQCurrentReq[taskId], 1);
        }

        pSlot->CQCurrentReq[taskId]->cQReqStat = status;
        pSlot->CQCurrentReq[taskId] = NULL;
    }
}

/* function finishes direct request but only if attached */
static void FinishDcmdRequest(CSDD_SDIO_Slot* pSlot, CSDD_CQReqStat status)
{
    if (pSlot->CQCurrentDcmdReq != NULL) {
        if (status == CSDD_CQ_REQ_STAT_FAILED) {
            CQDumpDcmdRequest(pSlot->CQCurrentDcmdReq, 1);
        }
        pSlot->CQCurrentDcmdReq->cQReqStat = status;
        pSlot->CQCurrentDcmdReq->response =
            CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS18);

        pSlot->CQCurrentDcmdReq = NULL;
    }
}

static void CheckTaskCompletion(CSDD_SDIO_Slot* pSlot)
{
    uint8_t i;

    uint32_t reg;
    reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS11);
    /* clear all caught notifications */
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS11, reg);

    uint8_t numOfTasks = ((pSlot->pDevice != NULL) ? pSlot->pDevice->cQDepth : 0U);

    if ((pSlot->CQDcmdEnabled != 0U) && (numOfTasks == CQ_HOST_NUMBER_OF_TASKS)) {
        numOfTasks--;
    }

    for (i = 0; i < numOfTasks; i++) {
        if (CQRS11_GET_TASK_COMPL(reg, i) != 0U) {
            FinishRequest(pSlot, i, CSDD_CQ_REQ_STAT_FINISHED);
        }
    }
    if (pSlot->CQDcmdEnabled != 0U) {
        if (CQRS11_GET_TASK_COMPL(reg, CQ_DCMD_TASK_ID) != 0U) {
            FinishDcmdRequest(pSlot, CSDD_CQ_REQ_STAT_FINISHED);
        }
    }
}

static void DiscardAllRequests(CSDD_SDIO_Slot* pSlot)
{
    uint8_t i;
    uint8_t numOfTasks;

    numOfTasks = pSlot->pDevice->cQDepth;
    if ((pSlot->CQDcmdEnabled != 0U) && (numOfTasks == CQ_HOST_NUMBER_OF_TASKS)) {
        numOfTasks--;
    }

    for (i = 0; i < numOfTasks; i++) {
        FinishRequest(pSlot, i, CSDD_CQ_REQ_STAT_FAILED);
    }
    if (pSlot->CQDcmdEnabled != 0U) {
        FinishDcmdRequest(pSlot, CSDD_CQ_REQ_STAT_FAILED);
    }
}

static uint8_t TaskClear(CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS14);

    reg |= CQRS14_SET_TASK_CLEAR(taskId);
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS14, reg);

    if (WaitForValue(&pSlot->RegOffset->CQRS.CQRS14,
                     CQRS14_SET_TASK_CLEAR(taskId), 1,
                     COMMANDS_TIMEOUT) != SDIO_ERR_NO_ERROR) {
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "Clear task %d failed.\n", taskId);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    }

    return (status);
}

static uint8_t AllTasksClear(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS03);

    reg |= (uint32_t)CQRS03_CLEAR_ALL_TASKS;
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS03, reg);

    if (WaitForValue(&pSlot->RegOffset->CQRS.CQRS03,
                     (uint32_t)CQRS03_CLEAR_ALL_TASKS, 1,
                     COMMANDS_TIMEOUT) != SDIO_ERR_NO_ERROR) {
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "Clear all taks failed\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    }

    return (status);
}

static uint8_t ErrorRecoveryCheckCmdDat(CSDD_SDIO_Slot* pSlot, uint32_t IntStatus)
{
    uint8_t Error = SDIO_ERR_NO_ERROR;

    // CMD Line error occurs
    if ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12)
         & (SRS12_COMMAND_TIMEOUT_ERROR | SRS12_COMMAND_CRC_ERROR
            | SRS12_COMMAND_END_BIT_ERROR | SRS12_COMMAND_INDEX_ERROR | SRS12_RESPONSE_ERROR)) != 0U) {
        // reset CMD line
        Error = ResetLines(pSlot, 1, 0);
        if (Error != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s",
                         "Error - Can't reset CMD Line\n");
            // restore interrupt settings
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
        }
    }

    if (Error == SDIO_ERR_NO_ERROR) {
        // DAT Line error occurs
        if ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12)
             & (SRS12_DATA_END_BIT_ERROR | SRS12_DATA_CRC_ERROR
                | SRS12_DATA_TIMEOUT_ERROR)) != 0U) {

            // reset DAT line
            Error = ResetLines(pSlot, 0, 1);
            if (Error != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s",
                             "Error - Can't reset DAT Line\n");
                // restore interrupt settings
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
            }
        }
    }

    return (Error);
}

static uint32_t ErrorRecoveryCheckSrs12StatusReg(CSDD_SDIO_Slot* pSlot, const CSDD_Request* pRequest)
{
    uint32_t srs12Reg = 0U;

    while (pRequest->status == SDIO_STATUS_PENDING) {
        srs12Reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
        // clear interrupt status
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, srs12Reg);
        SDIOHost_CheckInterrupt(pSlot, srs12Reg);
    }

    return (srs12Reg);
}

static uint8_t ErrorRecoveryExecCmd12(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest,
                                      uint32_t SRS12, uint32_t* srs12Reg)
{
    uint8_t status;

    //clear error interrupt
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12);

    SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD12, .arg = 0, .cmdType = CSDD_CMD_TYPE_ABORT,
                                                        .respType = CSDD_RESPONSE_R1B, .hwRespCheck = 0}));

    // execute CMD12 command to abort command
    SDIOHost_ExecCardCommand(pSlot, pRequest);

    // interrupts are disabled on the begin of this function
    // so we have to check status register here because it will not be
    // checked neither in SDIOHost_ExecCardCommand function
    // nor SDIOHost_CheckInterrupt function
    *srs12Reg = ErrorRecoveryCheckSrs12StatusReg(pSlot, pRequest);

    // reset command and data line
    status = ResetLines(pSlot, 1, 1);
    if (status != SDIO_ERR_NO_ERROR) {
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error - Can't reset CMD and DAT Line\n");
    }

    return (status);
}

static uint8_t ErrorRecoveryExecCmd13(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t srs12Reg;

    SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD13, .arg = ((uint32_t)pSlot->pDevice->RCA << 16),
                                                        .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

    SDIOHost_ExecCardCommand(pSlot, pRequest);

    while (pRequest->status == SDIO_STATUS_PENDING) {
        srs12Reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
        // clear occurred normal status interrupts
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, srs12Reg
                     & SRS12_NORMAL_STAUS_MASK);
        SDIOHost_CheckInterrupt(pSlot, srs12Reg);
    }

    if((pRequest->response[0] & CARD_STATUS_CS_MASK) != CARD_STATUS_CS_TRAN) {
        /* device is not in transfer state */
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "Error - Card state should be 4 but it is %d\n", ((pRequest->response[0] >> 9) & 0xFU));
        status = SDIO_ERR_UNRECOVERABLE_ERROR;
    }

    return (status);
}

static uint8_t ProcessErrorRecovery(CSDD_SDIO_Slot* pSlot, uint32_t SRS12, uint32_t IntStatus)
{
    uint32_t srs12Reg;
    CSDD_Request request;

    uint8_t Error = ErrorRecoveryExecCmd12(pSlot, &request, SRS12, &srs12Reg);

    if (Error == SDIO_ERR_NO_ERROR) {

        if ((srs12Reg & SRS12_ERROR_CMD_LINE) != 0U) {
            Error = ErrorRecoveryExecCmd13(pSlot, &request);
        }
        else if ((srs12Reg & SRS12_DATA_TIMEOUT_ERROR) != 0U) {
            Error = SDIO_ERR_UNRECOVERABLE_ERROR;
        } else {
            // All 'if ... else if' constructs shall be terminated with an 'else' statement
            // (MISRA2012-RULE-15_7-3)
        }

        if (Error != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                         "E%d %s", (uint16_t)Error, SDIO_Errors_GetText(Error));
        }
        /* recovery interrupt settings */
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
    }

    return (Error);
}

static uint8_t ErrorRecovery(CSDD_SDIO_Slot* pSlot, uint32_t SRS12)
{
    uint8_t Error;
    uint32_t IntStatus, Tmp;

    IntStatus = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS14);
    // disable all errors interrupt signal, and command complete interrupt signal
    Tmp = IntStatus & (uint32_t)(~(SRS14_COMMAND_COMPLETE_SIG_EN
                                   | SRS14_TRANSFER_COMPLETE_SIG_EN
                                   | SRS14_COMMAND_TIMEOUT_ERR_SIG_EN
                                   | SRS14_COMMAND_CRC_ERR_SIG_EN
                                   | SRS14_COMMAND_END_BIT_ERR_SIG_EN
                                   | SRS14_COMMAND_INDEX_ERR_SIG_EN
                                   | SRS14_DATA_TIMEOUT_ERR_SIG_EN
                                   | SRS14_DATA_CRC_ERR_SIG_EN
                                   | SRS14_DATA_END_BIT_ERR_SIG_EN
                                   | SRS14_CURRENT_LIMIT_ERR_SIG_EN
                                   | SRS14_AUTO_CMD12_ERR_SIG_EN));
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, Tmp);

    Error = ErrorRecoveryCheckCmdDat(pSlot, IntStatus);

    if (Error == SDIO_ERR_NO_ERROR) {

        Error = ProcessErrorRecovery(pSlot, SRS12, IntStatus);
    }

    return (Error);
}

static void CQDeviceDiscardTaskCheckRequest(CSDD_SDIO_Slot* pSlot, uint8_t fromIsr, CSDD_Request* pRequest)
{
    uint32_t srs12;

    if (fromIsr != 0U) {
        while (pRequest->status == SDIO_STATUS_PENDING) {
            srs12 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
            // clear occurred normal status interrupts
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, srs12
                         & SRS12_NORMAL_STAUS_MASK);
            SDIOHost_CheckInterrupt(pSlot, srs12);
        }
    } else {
        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
    }
}

static uint8_t CQDeviceDiscardTask(CSDD_SDIO_Slot* pSlot, uint8_t taskId, uint8_t fromIsr)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    CSDD_Request request = {0};
    uint32_t arg =  CQ_TASK_MGMT_ARG(taskId,  CQ_TASK_MGMT_ARG_TM_DISCARD_TASK);

    SDIO_REQ_INIT_CMD(&request, &((SD_CsddRequesParams){.cmd = SDIO_CMD48, .arg = arg,
                                                        .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
    SDIOHost_ExecCardCommand(pSlot, &request);
    CQDeviceDiscardTaskCheckRequest(pSlot, fromIsr, &request);

    if (request.status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "E%d %s", (uint16_t)(request.status), SDIO_Errors_GetText(request.status));
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    }

    return (status);
}

static uint8_t CQDeviceDiscardAllTasks(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    CSDD_Request request = {0};

    uint32_t arg =  CQ_TASK_MGMT_ARG(0,  CQ_TASK_MGMT_ARG_TM_DISCARD_QUEUE);
    SDIO_REQ_INIT_CMD(&request, &((SD_CsddRequesParams){.cmd = SDIO_CMD48, .arg = arg,
                                                        .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
    SDIOHost_ExecCardCommand(pSlot, &request);
    SDIOHost_CheckBusy(request.pSdioHost, &request);

    if (request.status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "E%d %s", (uint16_t)(request.status), SDIO_Errors_GetText(request.status));
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    }

    return (status);
}

static void CQErrorRecovery(CSDD_SDIO_Slot* pSlot, uint32_t intStatus,
                            const CQ_TaskErrorStatus *errStatus)
{
    uint8_t status = SDIOHost_CQ_Halt(pSlot, 1);

    if (status == SDIO_ERR_NO_ERROR) {

        pSlot->ErrorRecorvering = 1;
        (void)ErrorRecovery(pSlot, intStatus);
        pSlot->ErrorRecorvering = 0;

        if (errStatus->isDataError != 0U) {
            (void)CQDeviceDiscardTask(pSlot, errStatus->taskId, 1);
            (void)TaskClear(pSlot, errStatus->taskId);
        }

        (void)SDIOHost_CQ_Halt(pSlot, 0);
    }
}
static void CQCheckResponseError(CSDD_SDIO_Slot* pSlot)
{
    uint32_t response = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS23);
    uint8_t status = CheckResponseError(&response, (uint8_t)CSDD_RESPONSE_R1, pSlot);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                 "E%d %s", (uint16_t)status, SDIO_Errors_GetText(status));
    }
}

static void CheckTaskErrorCmdResp(CSDD_SDIO_Slot* pSlot, CQ_TaskErrorStatus* status, uint32_t reg)
{
    if ((reg & CQRS21_RM_ERR_FIELDS_RVID) != 0U) {
        uint8_t taskId = (uint8_t)CQRS21_GET_RM_ERR_TASK_ID(reg);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "Command response error detected during command execution on task %d command %d\n",
                     taskId, (uint8_t)CQRS21_GET_RM_ERR_CMD_IDX(reg));

        CQCheckResponseError(pSlot);
        status->isCmdError = 1;
        status->taskId = taskId;
        if (CQ_IS_DIRECT_TASK(pSlot, taskId)) {
            FinishDcmdRequest(pSlot, CSDD_CQ_REQ_STAT_FAILED);
        }
        else {
            FinishRequest(pSlot, taskId, CSDD_CQ_REQ_STAT_FAILED);
        }
    }
}

static void CheckTaskErrorDataTransfer(CSDD_SDIO_Slot* pSlot, CQ_TaskErrorStatus* status, uint32_t reg)
{
    if ((reg & CQRS21_DT_ERR_FIELDS_RVID) != 0U) {
        uint8_t taskId = (uint8_t)CQRS21_GET_DT_ERR_TASK_ID(reg);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "Data transfer error detected during command execution on task %d command %d\n",
                     taskId, (uint8_t)CQRS21_GET_DT_ERR_CMD_IDX(reg));
        CQCheckResponseError(pSlot);
        FinishRequest(pSlot, taskId, CSDD_CQ_REQ_STAT_FAILED);
        status->taskId = taskId;
        status->isDataError = 1;
    }
}

static void CheckTaskError(CSDD_SDIO_Slot* pSlot,  CQ_TaskErrorStatus *status)
{
    uint32_t reg;
    status->isCmdError = 0;
    status->isDataError = 0;

    reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS21);

    CheckTaskErrorCmdResp(pSlot, status, reg);

    CheckTaskErrorDataTransfer(pSlot, status, reg);
}

static void HandleInterruptCoalescing(CSDD_SDIO_Slot* pSlot)
{
    uint32_t reg;

    if (pSlot->CQIntCoalescingEn != 0U) {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS07);

        /* if At least one task completion has been counted
         * and interrupt occurs then reset timer and task counter */
        if ((reg & CQRS07_INT_COAL_STATUS_BIT) != 0U) {
            reg |= (uint32_t)CQRS07_INT_COAL_COUNTER_TIMER_RESET;
            CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS07, reg);
        }
    }
}

static void CheckCQInterrupt(CSDD_SDIO_Slot* pSlot)
{
    uint32_t reg;
    reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS04);
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS04, reg);

    if (pSlot->pDevice == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Device is NULL fatal ERROR\n");
    }

    if ((reg & CQRS04_RESP_ERR_INT) != 0U) {
        CQ_TaskErrorStatus status;
        CheckTaskError(pSlot, &status);
        CQErrorRecovery(pSlot, 0, &status);
    }

    if ((reg & CQRS04_TASK_COMPLETE_INT) != 0U) {
        HandleInterruptCoalescing(pSlot);
        CheckTaskCompletion(pSlot);
    }

}

void SDIOHost_CQ_CheckInterrupt(CSDD_SDIO_Slot* pSlot)
{
    uint32_t reg;

    if (pSlot->pDevice == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Device is NULL fatal ERROR\n");
    }

    reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);

    if ((reg & SRS12_ERROR_INTERRUPT) != 0U) {
        CQ_TaskErrorStatus status;
        if ((reg & SRS12_ADMA_ERROR) != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "ADMA Error occurs\n");
        }

        CheckTaskError(pSlot, &status);
        CQErrorRecovery(pSlot,reg, &status);
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12,
                     reg & SRS12_ERROR_STATUS_MASK);
    }

    if ((reg & SRS12_CMD_QUEUING_INT) != 0U) {
        CheckCQInterrupt(pSlot);
    }

}

static uint8_t DeviceCQConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable)
{
    uint8_t Status;
    uint8_t cQSupport;

    if (pSlot->pDevice == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        Status = EINVAL;
    } else {

        // Read Extended CSD register from a card
        Status = SDIOHost_ReadExCSD(pSlot, (uint8_t*)pSlot->AuxBuff);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {

            // get byte for EXT_CSD register
            cQSupport = GET_BYTE_FROM_BUFFER(pSlot->AuxBuff, MMC_EXCSD_CQ_SUPPORT);
            // bit zero informs if command queuing is supported
            if ((cQSupport & 1U) == 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not supported by a device\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", CDN_ENOTSUP);
                Status = CDN_ENOTSUP;
            } else {

                // calculate maximum task ID supported by the device
                pSlot->pDevice->cQDepth
                    = GET_BYTE_FROM_BUFFER(pSlot->AuxBuff, MMC_EXCSD_CQ_DEPTH) + 1U;

                // enable command queuing in a emmc device
                const uint8_t arg = ((enable != 0U) ? 1U : 0U);
                Status = SDIOHost_MmcSetExtCsd(pSlot, MMC_EXCSD_CQ_MODE_EN, arg, 1U);
                if (Status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Enabling/Disabling CQ in device failed\n");
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
                    Status = EIO;
                }
            }
        }
    }

    return (Status);
}

static uint8_t isTaskQueueEmpty(CSDD_SDIO_Slot* pSlot)
{
    /* if any doorbell bit is set it means that command queue is not empty */
    return ((CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS10) == 0U) ? 1U : 0U);
}

static uint8_t IsHwTaskPending(CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS13);

    /* if task is not marked by HW as pending it can be ready */
    return ((CQRS13_GET_TASK_PEND(reg, taskId) != 0U) ? 1U : 0U);
}

/* function checks if request is not pending (normal request not DCMD request) */
static uint8_t IsRequestPending(const CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint8_t result;

    /* if no request attached it is not pending */
    if (pSlot->CQCurrentReq[taskId] == NULL) {
        result = 0U;
    } else {

        switch(pSlot->CQCurrentReq[taskId]->cQReqStat) {
        case CSDD_CQ_REQ_STAT_FINISHED:
        case CSDD_CQ_REQ_STAT_FAILED:
        case CSDD_CQ_REQ_STAT_ATTACHED:
            result = 0U;
            break;
        case CSDD_CQ_REQ_STAT_PENDING:
            result = 1U;
            break;
        default:
            result = 1U;
            break;
        }
    }

    return (result);
}

/* function checks if request is attached (normal request not DCMD request) */
static uint8_t IsRequestAttached(const CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint8_t result = 0U;

    if ((pSlot->CQCurrentReq[taskId] != NULL)
        && (pSlot->CQCurrentReq[taskId]->cQReqStat == CSDD_CQ_REQ_STAT_ATTACHED)) {
        result = 1U;
    }

    return (result);
}

static void
PrepareTaskDescFlags(const CSDD_CQRequest *request, uint16_t *flags)
{
    *flags = (uint16_t)(CQ_DESC_VALID |  CQ_DESC_END
                        | CQ_DESC_ACT_TASK);

    *flags |= CQ_DESC_SET_CONTEXT_ID(request->contextId);

    if (request->transferDirection == CSDD_TRANSFER_READ) {
        *flags |= (uint16_t)CQ_DESC_DATA_DIR_READ_NOT_WRITE;
    }

    if (request->highPriorityEn != 0U) {
        *flags |= (uint16_t)CQ_DESC_PRIORITY_HIGH;
    }

    if (request->queueBarrierEn != 0U) {
        *flags |= (uint16_t)CQ_DESC_QUEUE_BARRIER;
    }

    if (request->forceProgEn != 0U) {
        *flags |= (uint16_t)CQ_DESC_FORCE_PROG;
    }

    if (request->tagRequestEn != 0U) {
        *flags |= (uint16_t)CQ_DESC_TAG_REQUEST;
    }

    if (request->reliableWriteEn != 0U) {
        *flags |= (uint16_t)CQ_DESC_RELIABLE_WRITE;
    }

    if (request->intCoalEn == 0U) {
        *flags |= (uint16_t)CQ_DESC_INT;
    }
}

static void
PrepareTaskDesc64(const CSDD_CQRequest *request, CQ_TaskDesc64 *descPtr)
{
    uint16_t flags;
    PrepareTaskDescFlags(request, &flags);
    descPtr->flags = flags;
    descPtr->blockCount = request->blockCount;
    descPtr->blockAddress = request->blockAddress;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 8, "Task descriptor 64 bit");
}

static void
PrepareTaskDesc128(const CSDD_CQRequest *request, CQ_TaskDesc128 *descPtr)
{
    uint16_t flags;
    PrepareTaskDescFlags(request, &flags);
    descPtr->flags = flags;
    descPtr->blockCount = request->blockCount;
    descPtr->blockAddress = request->blockAddress;
    descPtr->reserved[0] = 0;
    descPtr->reserved[1] = 0;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 16, "Task descriptor 128 bit");
}

static void
PrepareTransLinkDesc64(CQ_TransDesc64 *descPtr, uintptr_t descDataPhyAddr,
                       uint16_t descSize)
{
    descPtr->flags = (uint16_t)(CQ_DESC_VALID | CQ_DESC_ACT_LINK);
    descPtr->length = descSize;
    descPtr->addressLow = (uint32_t)descDataPhyAddr;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 8, "Link descriptor 64 bit");
}

static void
PrepareTransLinkDesc128(CQ_TransDesc128 *descPtr, uintptr_t descDataPhyAddr,
                        uint16_t descSize)
{
    descPtr->flags = (uint16_t)(CQ_DESC_VALID | CQ_DESC_ACT_LINK);
    descPtr->length = descSize;
    descPtr->addressLow = (uint32_t)(descDataPhyAddr & 0xFFFFFFFFUL);
    descPtr->addressHigh = (uint32_t)(((uint64_t)descDataPhyAddr) >> 32);
    descPtr->reserved = 0;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 16, "Link descriptor 128 bit");
}

static void
PrepareTransDesc64(CQ_TransDesc64 *descPtr, const CSDD_CQRequestData *buffers,
                   uint32_t numberOfBuffers)
{
    uint32_t i;

    for (i = 0; i < numberOfBuffers; i++) {
        descPtr[i].flags = (uint16_t)(CQ_DESC_VALID | CQ_DESC_ACT_TRAN);
        descPtr[i].length = (uint16_t)buffers[i].bufferSize;
        descPtr[i].addressLow = (uint32_t)buffers[i].buffPhyAddr;
    }
    if (numberOfBuffers > 0U) {
        descPtr[numberOfBuffers - 1U].flags |= (uint16_t)CQ_DESC_END;
    }
    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 8U * numberOfBuffers,
                        "Transfer descriptors 64 bit");
}

static void
PrepareTransDesc128(CQ_TransDesc128 *descPtr, const CSDD_CQRequestData *buffers,
                    uint32_t numberOfBuffers)
{
    uint32_t i;

    for (i = 0; i < numberOfBuffers; i++) {
        descPtr[i].flags = (uint16_t)(CQ_DESC_VALID | CQ_DESC_ACT_TRAN);
        descPtr[i].length = (uint16_t)buffers[i].bufferSize;
        descPtr[i].addressLow = (uint32_t)(buffers[i].buffPhyAddr & 0xFFFFFFFFUL);
        descPtr[i].addressHigh = (uint32_t)(((uint64_t)buffers[i].buffPhyAddr) >> 32);
        descPtr[i].reserved = 0;
    }
    if (numberOfBuffers > 0U) {
        descPtr[numberOfBuffers - 1U].flags |= (uint16_t)CQ_DESC_END;
    }

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 16U * numberOfBuffers,
                        "Transfer descriptors 128 bit");
}

static void PrepareDescs64(void *descHeadPtr, CSDD_CQRequest *request)
{
    CQ_Desc64 *descPtr = (CQ_Desc64*)descHeadPtr;
    PrepareTaskDesc64(request, &descPtr[request->taskId].taskDesc);

    if (request->numberOfBuffers == 1U) {
        PrepareTransDesc64(&descPtr[request->taskId].transDesc,
                           request->buffers, request->numberOfBuffers);
    }
    else {
        /* prepare link descriptor pointing to group of data transfer descriptors */
        PrepareTransLinkDesc64(&descPtr[request->taskId].transDesc,
                               request->descDataPhyAddr,
                               request->numberOfBuffers * (uint16_t)sizeof(CQ_TransDesc64));
        /* create group of data transfer descriptors */
        PrepareTransDesc64((CQ_TransDesc64*)request->descDataBuffer,
                           request->buffers,
                           request->numberOfBuffers);
    }

}

static void PrepareDescs128(void *descHeadPtr, CSDD_CQRequest *request)
{
    CQ_Desc128 *descPtr = (CQ_Desc128*)descHeadPtr;
    PrepareTaskDesc128(request, &descPtr[request->taskId].taskDesc);

    if (request->numberOfBuffers == 1U) {
        PrepareTransDesc128(&descPtr[request->taskId].transDesc,
                            request->buffers, request->numberOfBuffers);
    }
    else {
        /* prepare link descriptor pointing to group of data transfer descriptors */
        PrepareTransLinkDesc128(&descPtr[request->taskId].transDesc,
                                request->descDataPhyAddr,
                                request->numberOfBuffers * (uint16_t)sizeof(CQ_TransDesc128));
        /* create group of data transfer descriptors */
        PrepareTransDesc128((CQ_TransDesc128*)request->descDataBuffer,
                            request->buffers,
                            request->numberOfBuffers);
    }
}

/* prepare flags for direct command descriptor */
static void PrepareDcmdDescFlags(const CSDD_CQDcmdRequest *request, uint32_t *flags)
{
    // first prepare general task flags
    *flags = (uint32_t)(CQ_DESC_VALID |  CQ_DESC_END
                        | CQ_DESC_ACT_TASK | CQ_DESC_INT);

    if (request->queueBarrierEn != 0U) {
        *flags |= (uint32_t)CQ_DESC_QUEUE_BARRIER;
    }

    // now prepare direct command specific flags
    *flags |= CQ_DESC_DCMD_SET_CMD_INDEX(request->cmdIdx);

    switch(request->responseType) {
    case CSDD_RESPONSE_NO_RESP:
        *flags |= (uint32_t)CQ_DESC_DCMD_RESP_TYPE_NO_RESP;
        break;
    case CSDD_RESPONSE_R1:
    case CSDD_RESPONSE_R4:
    case CSDD_RESPONSE_R5:
        *flags |= (uint32_t)CQ_DESC_DCMD_RESP_TYPE_R1_R4_R5;
        break;
    case CSDD_RESPONSE_R1B:
        *flags |= (uint32_t)CQ_DESC_DCMD_RESP_TYPE_R1B;
        break;
    default:
        //
        break;
    }

    if (request->cmdTiming != 0U) {
        *flags |= (uint32_t)CQ_DESC_DCMD_CMD_TIMING;
    }
}

static void PrepareDcmdTaskDesc64(CQ_DcmdTaskDesc64 *descPtr, const CSDD_CQDcmdRequest *request)
{
    uint32_t flags;

    PrepareDcmdDescFlags(request, &flags);
    descPtr->flags = flags;
    descPtr->argument = request->argument;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 8, "Direct task descriptor 64 bit");
}

static void PrepareDcmdTaskDesc128(CQ_DcmdTaskDesc128 *descPtr, const CSDD_CQDcmdRequest *request)
{
    uint32_t flags;

    PrepareDcmdDescFlags(request, &flags);
    descPtr->flags = flags;
    descPtr->argument = request->argument;
    descPtr->reserved[0] = 0;
    descPtr->reserved[1] = 0;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 16, "Direct task descriptor 128 bit");
}

static void PrepareNopDesc64(CQ_NopDesc64 *descPtr)
{
    descPtr->flags = (uint32_t)(CQ_DESC_VALID |  CQ_DESC_END
                                | CQ_DESC_ACT_NOP);
    descPtr->reserved = 0;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 8, "NOP descriptor 64 bit");
}

static void PrepareNopDesc128(CQ_NopDesc128 *descPtr)
{
    descPtr->flags = (uint32_t)(CQ_DESC_VALID |  CQ_DESC_END
                                | CQ_DESC_ACT_NOP);
    descPtr->reserved = 0;
    descPtr->reserved2[0] = 0;
    descPtr->reserved2[1] = 0;

    DEBUG_DUMP_BUFFER32((uint32_t*)descPtr, 16, "NOP descriptor 128 bit");
}

static void PrepareDcmdDescs64(CQ_DcmdDesc64 *descPtr, const CSDD_CQDcmdRequest *request)
{
    PrepareDcmdTaskDesc64(&descPtr->dcmdTaskDesc, request);
    PrepareNopDesc64(&descPtr->nopDesc);
}

static void PrepareDcmdDescs128(CQ_DcmdDesc128 *descPtr, const CSDD_CQDcmdRequest *request)
{
    PrepareDcmdTaskDesc128(&descPtr->dcmdTaskDesc, request);
    PrepareNopDesc128(&descPtr->nopDesc);
}

static void PrepareDcmdDescs(const CSDD_SDIO_Slot* pSlot, const CSDD_CQDcmdRequest *request)
{
    if (pSlot->CQDescSize == CSDD_CQ_TASK_DESC_SIZE_64BIT) {
        CQ_DcmdDesc64 *dcmdDesc64 = (CQ_DcmdDesc64*)pSlot->CQDescriptorBuffer;
        PrepareDcmdDescs64(&dcmdDesc64[ CQ_DCMD_TASK_ID], request);
    }
    else {
        CQ_DcmdDesc128 *dcmdDesc128 = (CQ_DcmdDesc128*)pSlot->CQDescriptorBuffer;
        PrepareDcmdDescs128(&dcmdDesc128[ CQ_DCMD_TASK_ID], request);
    }
}

static uint8_t VerifyRequestDataBuffers(const CSDD_CQRequest *request)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t i;

    if ((request->buffers == NULL) || (request->blockCount == 0U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "No data to be sent. Error %d\n", EINVAL);
        status = EINVAL;
    } else {

        for (i = 0; i < request->numberOfBuffers; i++) {
            if ((request->buffers[i].buffPhyAddr == 0U) || (request->buffers[i].bufferSize == 0U)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Data buffers are misconfigured. Error %d\n", EINVAL);
                status = EINVAL;
            } else if (request->buffers[i].bufferSize > CQ_TRANS_DESC_MAX_BUFF_SIZE) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "buffer %d size %d is bigger than %d\n",
                             i, request->buffers[i].bufferSize, CQ_TRANS_DESC_MAX_BUFF_SIZE);
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
                status = EINVAL;
            } else {
                /*
                 * All 'if ... else if' constructs shall be terminated with an 'else' statement
                 * (MISRA2012-RULE-15_7-3)
                 */
            }



            if (status != SDIO_ERR_NO_ERROR) {
                break;
            }
        }
    }

    return (status);
}

static uint8_t VerifyRequest(const CSDD_SDIO_Slot* pSlot, const CSDD_CQRequest *request)
{
    uint8_t status;
    /* descriptor size in bytes */
    uint32_t descSize;

    if (request->taskId >= pSlot->pDevice->cQDepth) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Given task ID %d is bigger than max supported by device %d\n",
                     request->taskId, pSlot->pDevice->cQDepth);

    }

    if ((pSlot->CQDcmdEnabled != 0U) && (request->taskId ==  CQ_DCMD_TASK_ID)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Given task ID %d is used for direct command %d. \
                     So it cannot be used to execute normal request\n",
                     request->taskId,  CQ_DCMD_TASK_ID);
    }

    status = VerifyRequestDataBuffers(request);

    if (status == SDIO_ERR_NO_ERROR) {
        if (pSlot->CQDescSize == CSDD_CQ_TASK_DESC_SIZE_64BIT) {
            descSize = 8;
        } else {
            descSize = 16;
        }

        if (request->numberOfBuffers > 1U) {
            if (request->descDataSize < ((uintptr_t)request->numberOfBuffers * descSize)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Buffer for data transfer descriptors is to small\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
                status = EINVAL;
            } else if ((request->descDataPhyAddr == 0U) || (request->descDataBuffer == NULL)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Buffer for data transfer descriptors is NULL\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
                status = EINVAL;
            } else {
                // All 'if ... else if' constructs shall be terminated with an 'else' statement
                // (MISRA2012-RULE-15_7-3)
            }
        }
    }

    return (status);
}

static uint8_t VerifyDcmdRequest(const CSDD_CQDcmdRequest *request)
{
    uint8_t status;

    switch(request->responseType) {
    case CSDD_RESPONSE_NO_RESP:
    case CSDD_RESPONSE_R1:
    case CSDD_RESPONSE_R4:
    case CSDD_RESPONSE_R5:
    case CSDD_RESPONSE_R1B:
        status = SDIO_ERR_NO_ERROR;
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Unsupported response type\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        status = EINVAL;
        break;
    }

    return (status);
}

static void SDIOHost_ProcessCQInit(CSDD_SDIO_Slot* pSlot, uint32_t reg)
{
    uint32_t i;
    uintptr_t descAddr, descPhyAddr;
    uint64_t descAddr64;

    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS02, reg);

    pSlot->CQEnabled = 0;
    pSlot->CQHalted = 0;
    pSlot->CQDcmdEnabled = 0;
    pSlot->CQIntCoalescingEn = 0;
    pSlot->CQDescriptorBuffer = NULL;
    pSlot->CQCurrentDcmdReq = NULL;
    for (i = 0; i <  CQ_HOST_NUMBER_OF_TASKS; i++) {
        pSlot->CQCurrentReq[i] = NULL;
    }

    /* init descriptor pointer and physical address */
    descAddr = (uintptr_t)pSlot->DescriptorBuffer;
    descAddr += MAX_DESCR_BUFF_SIZE - CQ_DESC_LIST_SIZE_WITH_ALIGN_MARGIN;
    descPhyAddr = (uintptr_t)pSlot->DescriptorDMAAddr;
    descPhyAddr += MAX_DESCR_BUFF_SIZE - CQ_DESC_LIST_SIZE_WITH_ALIGN_MARGIN;
    if ((descAddr & CQ_TDLBA_ALIGN_MASK) != 0U) {
        descAddr += (CQ_TDLBA_ALIGN_MASK + 1U) - (descAddr & CQ_TDLBA_ALIGN_MASK);
        descPhyAddr += (CQ_TDLBA_ALIGN_MASK + 1U) - (descPhyAddr & CQ_TDLBA_ALIGN_MASK);
    }

    pSlot->CQDescriptorBuffer = (uint32_t*)descAddr;
    pSlot->CQDescriptorDmaAddr = descPhyAddr;

    /* Task Descriptor List address configuration */
    descAddr64 = pSlot->CQDescriptorDmaAddr;
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS08, (uint32_t)(descAddr64 & 0xFFFFFFFFU));
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS09, (uint32_t)((descAddr64 >> 32) & 0xFFFFFFFFU));
}

uint8_t SDIOHost_CQ_Init(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t reg;

   /* task descriptor size configuration */
    reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS02);
    reg &= ~(uint32_t)CQRS02_TASK_DESCRIPTOR_SIZE_MASK;

    if (pSlot->SlotSettings.DMA64_En != 0U) {
        pSlot->CQDescSize = CSDD_CQ_TASK_DESC_SIZE_128BIT;
        reg |= (uint32_t)CQRS02_TASK_DESCRIPTOR_SIZE_128;
    }
    else {
        pSlot->CQDescSize = CSDD_CQ_TASK_DESC_SIZE_64BIT;
        reg |= (uint32_t)CQRS02_TASK_DESCRIPTOR_SIZE_64;
    }

    SDIOHost_ProcessCQInit(pSlot, reg);

    return (status);
}

static uint8_t SetInitConfig(CSDD_SDIO_Slot* pSlot, const CSDD_CQInitConfig *cqConfig)
{
    uint32_t reg;

    reg = CQRS16_SET_CMD_BLOCK_COUNTER(cqConfig->sendStatBlckCount)
          | CQRS16_SET_CMD_IDLE_TIMER(cqConfig->sendStatIdleTimer);
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS16, reg);

    return SDIO_ERR_NO_ERROR;
}

uint8_t SDIOHost_CQ_InterruptConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable)
{
    uint32_t reg = 0;

    if (pSlot->CQEnabled != 0U) {

        if (enable != 0U) {
            reg |=  (uint32_t)(CQRS06_TASK_COMPLETE_INT_SIG_EN
                               | CQRS06_RESP_ERR_INT_SIG_EN);
        }

        CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS06, reg);
    }

    return SDIO_ERR_NO_ERROR;
}

uint8_t SDIOHost_CQ_ExecuteDcmdRequest(CSDD_SDIO_Slot*          pSlot,
                                       CSDD_CQDcmdRequest *request)
{
    uint8_t status;
    uint32_t reg;

    if (pSlot->CQDcmdEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Direct command is not enabled in controller.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        status = EINVAL;
    } else {

        CQDumpDcmdRequest(request, 0);

        /* check if request is ok */
        status = VerifyDcmdRequest(request);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            /* prepare direct command descriptors */
            PrepareDcmdDescs(pSlot, request);

            request->cQReqStat = CSDD_CQ_REQ_STAT_PENDING;
            pSlot->CQCurrentDcmdReq = request;

            /* set doorbell to start processing descriptors by controller */
            reg = CQRS10_SET_TASK_DORBELL(CQ_DCMD_TASK_ID);
            CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS10, reg);
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_AttachRequest(CSDD_SDIO_Slot* pSlot, CSDD_CQRequest *request)
{
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else if (pSlot->pDevice == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        status = EINVAL;
    } else if (IsHwTaskPending(pSlot, request->taskId) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else if (IsRequestPending(pSlot, request->taskId) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else {

        CQDumpRequest(request, 0);

        status = VerifyRequest(pSlot, request);
        if (status != SDIO_ERR_NO_ERROR) {
            request->cQReqStat = CSDD_CQ_REQ_STAT_FAILED;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            if (pSlot->CQDescSize == CSDD_CQ_TASK_DESC_SIZE_64BIT) {
                PrepareDescs64(pSlot->CQDescriptorBuffer, request);
            } else {
                PrepareDescs128(pSlot->CQDescriptorBuffer, request);
            }

            request->cQReqStat = CSDD_CQ_REQ_STAT_ATTACHED;
            pSlot->CQCurrentReq[request->taskId] = request;

            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_StartExecuteTask(CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint32_t reg;
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else if (IsHwTaskPending(pSlot, taskId) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "HW task %d is currently ocuppied\n", taskId);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else if ( CQ_IS_DIRECT_TASK(pSlot, taskId)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Direct tasks are executed right after attach\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else if (IsRequestAttached(pSlot, taskId) == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Request task %d is not attached\n", taskId);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else {

        pSlot->CQCurrentReq[taskId]->cQReqStat = CSDD_CQ_REQ_STAT_PENDING;

        /* set doorbell to start processing descriptors by controller */
        reg = CQRS10_SET_TASK_DORBELL(taskId);
        CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS10, reg);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

uint8_t SDIOHost_CQ_GetUnusedTaskId(CSDD_SDIO_Slot* pSlot, uint8_t *taskId)
{
    uint8_t status;
    uint8_t i;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else if (pSlot->pDevice == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        status = EINVAL;
    } else {

        for (i = 0; i < pSlot->pDevice->cQDepth; i++) {
            if ((pSlot->CQCurrentReq[i] == NULL) && (IsHwTaskPending(pSlot, i) == 0U)) {
                *taskId = i;
                break;
            }
        }

        if ((pSlot->CQDcmdEnabled != 0U) && (*taskId ==  CQ_DCMD_TASK_ID)) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "There is no unused task.\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
            status = EBUSY;
        } else if (i == pSlot->pDevice->cQDepth) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "There is no unused task.\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
            status = EBUSY;
        } else {
            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_GetInitConfig(CSDD_SDIO_Slot* pSlot, CSDD_CQInitConfig *cqConfig)
{
    uint8_t status;
    uint32_t reg;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {
        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS16);

        cqConfig->sendStatBlckCount = (uint8_t)CQRS16_GET_CMD_BLOCK_COUNTER(reg);
        cqConfig->sendStatIdleTimer = (uint16_t)CQRS16_GET_CMD_IDLE_TIMER(reg);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

uint8_t SDIOHost_CQ_Disable(CSDD_SDIO_Slot* pSlot)
{
    uint8_t i;
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t reg;

    /* if command queuing is disabled just exit */
    if (pSlot->CQEnabled != 0U) {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS13);

        for (i = 0; i <  CQ_HOST_NUMBER_OF_TASKS; i++) {
            if (IsHwTaskPending(pSlot, i) != 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Command queuing cannot be disabled until all tasks are finished. Task %d is pending\n", i);
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
                status = EBUSY;
                break;
            }
        }

        if (status ==  SDIO_ERR_NO_ERROR) {
            /* disable command queuing */
            reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS02);
            reg &= ~(uint32_t)CQRS02_COMMAND_QUEUING_ENABLE;
            CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS02, reg);

            /* disable signaling command queuing interrupts */
            CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS05, 0);

            /* mark CQ as disabled for driver purposes */
            pSlot->CQEnabled = 0;

            /* recover transfer complete and command complete interrupts */
            if (pSlot->pSdioHost->intEn != 0U) {
                reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS14);
                reg |= (uint32_t)(SRS14_COMMAND_COMPLETE_SIG_EN | SRS14_TRANSFER_COMPLETE_SIG_EN);
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, reg | 3U);
            }

            /* disable command queuing in a eMMC device */
            status = DeviceCQConfig(pSlot, 0);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }
    }

    return (status);
}

static void SDIOHost_ProcessCQEnable(CSDD_SDIO_Slot* pSlot)
{
    /* enable signaling command queuing interrupts */
    uint32_t reg = (uint32_t)(CQRS05_TASK_CLEARED_STAT_EN
                              | CQRS05_RESP_ERR_STAT_EN
                              | CQRS05_TASK_COMPLETE_STAT_EN);
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS05, reg);

    // clear all interrupts
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS04, 0xFFFFFFFFU);

    /* set 16-bit RCA value which is send as an argument in SEND_QUEUE_STATUS */
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS17, pSlot->pDevice->RCA);

    /* enable command queuing engine in SD host controller */
    reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS02);
    reg |= (uint32_t)CQRS02_COMMAND_QUEUING_ENABLE;
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS02, reg);

    pSlot->CQEnabled = 1;

    (void)SDIOHost_CQ_InterruptConfig(pSlot, pSlot->pSdioHost->intEn);
}

uint8_t SDIOHost_CQ_Enable(CSDD_SDIO_Slot*               pSlot,
                           const CSDD_CQInitConfig *cqConfig)
{
    uint32_t reg;
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pSlot->CQEnabled == 0U) {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS00);
        if ((CQRS00_GET_EMMC_MAJOR_VERSION(reg) < 5U)
            || (CQRS00_GET_EMMC_MINOR_VERSION(reg) < 1U)) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not supported by the Host\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", CDN_ENOTSUP);
            status = CDN_ENOTSUP;
        } else {

            /* enable command queuing in emmc device */
            status = DeviceCQConfig(pSlot, 1);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {

                /* configure command queuing engine in SD host*/
                status = SetInitConfig(pSlot, cqConfig);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                } else {
                    SDIOHost_ProcessCQEnable(pSlot);
                }
            }
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_GetDirectCmdConfig(CSDD_SDIO_Slot* pSlot, uint8_t *enable)
{
    uint8_t status;
    uint32_t reg;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS02);
        if ((reg & CQRS02_DIRECT_CMD_ENABLE) != 0U) {
            *enable = 1;
        } else {
            *enable = 0;
        }

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

uint8_t SDIOHost_CQ_SetDirectCmdConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable)
{
    uint8_t status;
    uint32_t reg;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else if (IsHwTaskPending(pSlot, CQ_DCMD_TASK_ID) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "HW task %d is currently ocuppied. Cannot configure Direct Command\n", CQ_DCMD_TASK_ID);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS02);
        if (enable != 0U) {
            reg |= (uint32_t)CQRS02_DIRECT_CMD_ENABLE;
            /* it is unused when direct command is enabled */
            pSlot->CQCurrentReq[CQ_DCMD_TASK_ID] = NULL;
        }
        else {
            reg &= ~(uint32_t)CQRS02_DIRECT_CMD_ENABLE;
            /* direct request is unused when direct command is disabled */
            pSlot->CQCurrentDcmdReq = NULL;
        }
        CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS02, reg);

        pSlot->CQDcmdEnabled = enable;

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

uint8_t SDIOHost_CQ_GetIntCoalescingTimeoutBase(CSDD_SDIO_Slot* pSlot,
                                               uint32_t * clockFreqKHz)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t reg;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS01);

        *clockFreqKHz = CQRS01_GET_ITCFVAL(reg);

        switch(CQRS01_GET_ITCFMUL(reg)) {
        case CQRS01_ITCFMUL_1KHZ:
            *clockFreqKHz *= 1U;
            break;
        case CQRS01_ITCFMUL_10KHZ:
            *clockFreqKHz *= 10U;
            break;
        case CQRS01_ITCFMUL_100KHZ:
            *clockFreqKHz *= 100U;
            break;
        case CQRS01_ITCFMUL_1MHZ:
            *clockFreqKHz *= 1000U;
            break;
        case CQRS01_ITCFMUL_10MHZ:
            *clockFreqKHz *= 10000U;
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Unsuspected Internal Timer Clock Frequency Multiplier value\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
            status = EIO;
            break;
        }
    }

    return (status);
}

static uint8_t SDIOHost_ProcessCQSetIntCoalescingConfig(CSDD_SDIO_Slot* pSlot, const CSDD_CQIntCoalescingCfg *config)
{
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS07);

    /* configure interrupt coalescing counter threshold */
    reg &= ~(uint32_t)CQRS07_INT_COAL_COUNT_THRESHOLD_MASK;
    reg |= CQRS07_SET_INT_COAL_COUNT_THRESHOLD(config->threshold);
    reg |= (uint32_t)CQRS07_INT_COAL_COUNT_THRESHOLD_WE;

    /* configure interrupt coalescing timeout value */
    reg &= ~CQRS07_INT_COAL_TIMEOUT_VAL_MASK;
    reg |= CQRS07_SET_INT_COAL_TIMEOUT_VAL(config->timeout);
    reg |= (uint32_t)CQRS07_INT_COAL_TIMEOUT_WE;

    /* enable or disable interrupt coalescing
     * additionaly reset counters in case of enabling */
    if (config->enable != 0U) {
        reg |= (uint32_t)CQRS07_INT_COAL_ENABLE;
        reg |= (uint32_t)CQRS07_INT_COAL_COUNTER_TIMER_RESET;
    }
    else {
        reg &= ~(uint32_t)CQRS07_INT_COAL_ENABLE;
    }

    /* apply ne interrupt coalescing configuration */
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS07, reg);

    pSlot->CQIntCoalescingEn = config->enable;

    return SDIO_ERR_NO_ERROR;
}

uint8_t SDIOHost_CQ_SetIntCoalescingCfg(CSDD_SDIO_Slot* pSlot, const CSDD_CQIntCoalescingCfg *config)
{
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else if (isTaskQueueEmpty(pSlot) == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Cannot change interrupt coalescing configuration when task queue is not empty.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
        status = EBUSY;
    } else if (config->timeout > 127U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Interrupt coalescing timeout %d is bigger than maximum supported value 127.\n", config->timeout);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        status = EINVAL;
    } else if (config->threshold > (CQ_HOST_NUMBER_OF_TASKS - 1U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Interrupt coalescing threshold %d is bigger than maximum supported value %d.\n",
                     config->threshold, CQ_HOST_NUMBER_OF_TASKS - 1U);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EINVAL);
        status = EINVAL;
    } else {
        status = SDIOHost_ProcessCQSetIntCoalescingConfig(pSlot, config);
    }

    return (status);
}

uint8_t SDIOHost_CQ_GetIntCoalescingCfg(CSDD_SDIO_Slot* pSlot, CSDD_CQIntCoalescingCfg *config)
{
    uint8_t status;
    uint32_t reg;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS07);

        config->timeout = (uint8_t)CQRS07_GET_INT_COAL_TIMEOUT_VAL(reg);
        config->threshold = (uint8_t)CQRS07_GET_INT_COAL_COUNT_THRESHOLD(reg);

        if ((reg & CQRS07_INT_COAL_ENABLE) != 0U) {
            config->enable = 1;
        } else {
            config->enable = 0;
        }

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

static uint8_t SDIOHost_CheckTasksReady(CSDD_SDIO_Slot* pSlot, uint32_t taskIdsBitMask)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t taskId;

    /* first check if all request are ready to start */
    for (taskId = 0; taskId < CQ_HOST_NUMBER_OF_TASKS; taskId++) {
        if ((taskIdsBitMask & (1UL << taskId)) != 0U) {
            bool doBreak = false;
            if (IsHwTaskPending(pSlot, taskId) != 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "HW task %d is currently ocuppied\n", taskId);
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
                status = EBUSY;
                doBreak = true;
            } else if (CQ_IS_DIRECT_TASK(pSlot, taskId)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Direct tasks are executed right after attach\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
                status = EBUSY;
                doBreak = true;
            } else if (IsRequestAttached(pSlot, taskId) == 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Request task %d is not attached\n", taskId);
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EBUSY);
                status = EBUSY;
                doBreak = true;
            } else {
                continue;
            }

            if (doBreak) {
                break;
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_ProcessCQStartExecuteTasks(CSDD_SDIO_Slot* pSlot, uint32_t taskIdsBitMask)
{
    uint8_t taskId;

    /* update statuses of tasks */
    for (taskId = 0; taskId < CQ_HOST_NUMBER_OF_TASKS; taskId++) {
        if ((taskIdsBitMask & (1UL << taskId)) != 0U) {
            pSlot->CQCurrentReq[taskId]->cQReqStat = CSDD_CQ_REQ_STAT_PENDING;
        }
    }

    /* set doorbell to start processing descriptors by controller */
    CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS10, taskIdsBitMask);

    return SDIO_ERR_NO_ERROR;
}

uint8_t SDIOHost_CQ_StartExecuteTasks(CSDD_SDIO_Slot* pSlot, uint32_t taskIdsBitMask)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        status = SDIOHost_CheckTasksReady(pSlot, taskIdsBitMask);

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_ProcessCQStartExecuteTasks(pSlot, taskIdsBitMask);
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_Halt(CSDD_SDIO_Slot* pSlot, uint8_t set)
{
    uint8_t status;
    uint32_t reg;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS03);
        if (set != 0U) {
            reg |= (uint32_t)CQRS03_HALT;
        } else {
            reg &= ~(uint32_t)CQRS03_HALT;
        }
        CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS03, reg);

        if (WaitForValue(&pSlot->RegOffset->CQRS.CQRS03, (uint32_t)CQRS03_HALT, set,
                         COMMANDS_TIMEOUT) != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Halt cannot be finished\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
            status = EIO;
        } else {
            pSlot->CQHalted = set;

            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}

static void SDIOHost_ProcessCQTaskDiscardFinishSwRequest(CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    /* finish SW requests */
    if (CQ_IS_DIRECT_TASK(pSlot, taskId)) {
        FinishDcmdRequest(pSlot, CSDD_CQ_REQ_STAT_FAILED);
    } else {
        FinishRequest(pSlot, taskId, CSDD_CQ_REQ_STAT_FAILED);
    }
}

static void SDIOHost_ProcessCQTaskDiscard(CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS10);
    /* check if task is not completed */
    if (CQRS10_GET_TASK_DORBELL(reg, taskId) == 1U) {
        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS10);
        /* check if task is queued to device */
        if (CQRS13_GET_TASK_PEND(reg, taskId) == 1U) {
            (void)CQDeviceDiscardTask(pSlot, taskId, 0);
        }
        /* clear task in controller */
        (void)TaskClear(pSlot, taskId);

        SDIOHost_ProcessCQTaskDiscardFinishSwRequest(pSlot, taskId);
    }
}

uint8_t SDIOHost_CQ_TaskDiscard(CSDD_SDIO_Slot* pSlot, uint8_t taskId)
{
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        status = SDIOHost_CQ_Halt(pSlot, 1);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            SDIOHost_ProcessCQTaskDiscard(pSlot, taskId);

            (void)SDIOHost_CQ_Halt(pSlot, 0);
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_AllTasksDiscard(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        /* enter halt state */
        status = SDIOHost_CQ_Halt(pSlot, 1);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            /* discard all tasks in device */
            status = CQDeviceDiscardAllTasks(pSlot);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Dicarding all tasks in a device failed\n");
            } else {

                /* clear all tasks in host */
                (void)AllTasksClear(pSlot);

                /* discard all SW requests */
                DiscardAllRequests(pSlot);

                /* exit halt state */
                (void)SDIOHost_CQ_Halt(pSlot, 0);
            }
        }
    }

    return (status);
}

uint8_t SDIOHost_CQ_ResetIntCoalCounters(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;
    uint32_t reg;
    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        reg = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS07);
        reg |= (uint32_t)CQRS07_INT_COAL_COUNTER_TIMER_RESET;
        CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS07, reg);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

uint8_t SDIOHost_CQ_SetResponseErrMask(CSDD_SDIO_Slot* pSlot, uint32_t errorMask)
{
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        CPS_REG_WRITE(&pSlot->RegOffset->CQRS.CQRS20, errorMask);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}

uint8_t SDIOHost_CQ_GetResponseErrMask(CSDD_SDIO_Slot* pSlot, uint32_t *errorMask)
{
    uint8_t status;

    if (pSlot->CQEnabled == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command queuing is not enabled.\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", EIO);
        status = EIO;
    } else {

        *errorMask = CPS_REG_READ(&pSlot->RegOffset->CQRS.CQRS20);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}
