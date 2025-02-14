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
 * sdio_cq.h
 * Module implementing support for command queuing
 *****************************************************************************/

#ifndef SDIO_CQ_H
#define SDIO_CQ_H

#include "sdio_types.h"
#include "csdd_if.h"

/* size of descriptor list. Start address should be aligned to 1024 bytes.
 * Maximum size of descriptor list is 1024. */
#define CQ_DESC_LIST_SIZE_WITH_ALIGN_MARGIN 2048U

/* Command Queuing Task Descriptor List Base Address aligment mask*/
#define  CQ_TDLBA_ALIGN_MASK    ((1UL << 10) - 1U)

//-----------------------------------------------------------------------------
/// @name Task Descriptor Fields
//-----------------------------------------------------------------------------
//@{
/* The descriptor is valid */
#define CQ_DESC_VALID                        (1UL <<  0)
/* it is the last descriptor */
#define CQ_DESC_END                          (1UL <<  1)
/* Hardware shall generate an interrupt upon the task's completion */
#define CQ_DESC_INT                          (1UL <<  2)
/* Descriptor type - Task descriptor */
#define CQ_DESC_ACT_TASK                     (5UL << 3)
/* Descriptor type - Data Transfer descriptor */
#define CQ_DESC_ACT_TRAN                     (4UL << 3)
/* Descriptor type - Link descriptor */
#define CQ_DESC_ACT_LINK                     (6UL << 3)
/* Descriptor type - No operation*/
#define CQ_DESC_ACT_NOP                      (0UL << 3)
/* enable force programming */
#define CQ_DESC_FORCE_PROG                   (6UL << 1)
/* set context ID */
static inline uint16_t CQ_DESC_SET_CONTEXT_ID(uint16_t id)
{
    return ((id & 0xFU) << 7);
}
#define CQ_DESC_TAG_REQUEST                  (1UL <<  11)
/* Data read direction */
#define CQ_DESC_DATA_DIR_READ_NOT_WRITE      (1UL <<  12)
/* High priority task  */
#define CQ_DESC_PRIORITY_HIGH                (1UL <<  13)
#define CQ_DESC_QUEUE_BARRIER                (1UL <<  14)
#define CQ_DESC_RELIABLE_WRITE               (1UL <<  15)
/* set data block count to transfer */
static inline uint32_t CQ_DESC_SET_BLOCK_COUNT(uint32_t count)
{
    return ((count & 0xFFFFU) << 16);
}
/* Length of data buffer in bytes. A value of 0000 means 64 KB */
static inline uint32_t CQ_DESC_SET_DATA_LEN(uint32_t len)
{
    return ((len & 0xFFFFU) << 16);
}

static inline uint32_t CQ_DESC_DCMD_SET_CMD_INDEX(uint32_t idx)
{
    return ((idx & 0x3FU) << 16);
}
/* Command may be sent to device during data activity or busy time */
#define CQ_DESC_DCMD_CMD_TIMING              (1UL << 22)
/* expected reponse on direct command - R1 or R4 or R5*/
#define CQ_DESC_DCMD_RESP_TYPE_R1_R4_R5      (2UL << 23)
/* expected reponse on direct command - R1B */
#define CQ_DESC_DCMD_RESP_TYPE_R1B           (3UL << 23)
/* no expected reponse on direct command */
#define CQ_DESC_DCMD_RESP_TYPE_NO_RESP       (0UL << 23)

//@}
//-----------------------------------------------------------------------------

void SDIOHost_CQ_CheckInterrupt(CSDD_SDIO_Slot* pSlot);
uint8_t SDIOHost_CQ_Init(CSDD_SDIO_Slot* pSlot);
uint8_t SDIOHost_CQ_InterruptConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable);

uint8_t SDIOHost_CQ_Disable(CSDD_SDIO_Slot* pSlot);
uint8_t SDIOHost_CQ_Enable(CSDD_SDIO_Slot*               pSlot,
                           const CSDD_CQInitConfig *cqConfig);
uint8_t SDIOHost_CQ_GetInitConfig(CSDD_SDIO_Slot*         pSlot,
                                  CSDD_CQInitConfig *cqConfig);
uint8_t SDIOHost_CQ_GetUnusedTaskId(CSDD_SDIO_Slot* pSlot, uint8_t *taskId);
uint8_t SDIOHost_CQ_StartExecuteTask(CSDD_SDIO_Slot* pSlot, uint8_t taskId);
uint8_t SDIOHost_CQ_AttachRequest(CSDD_SDIO_Slot* pSlot, CSDD_CQRequest *request);
uint8_t SDIOHost_CQ_ExecuteDcmdRequest(CSDD_SDIO_Slot*          pSlot,
                                       CSDD_CQDcmdRequest *request);
uint8_t SDIOHost_CQ_GetDirectCmdConfig(CSDD_SDIO_Slot* pSlot, uint8_t *enable);
uint8_t SDIOHost_CQ_SetDirectCmdConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable);
uint8_t SDIOHost_CQ_SetIntCoalescingCfg(CSDD_SDIO_Slot*                     pSlot,
                                           const CSDD_CQIntCoalescingCfg *config);
uint8_t SDIOHost_CQ_GetIntCoalescingCfg(CSDD_SDIO_Slot*               pSlot,
                                           CSDD_CQIntCoalescingCfg *config);
uint8_t SDIOHost_CQ_GetIntCoalescingTimeoutBase(CSDD_SDIO_Slot* pSlot,
                                               uint32_t * clockFreqKHz);
uint8_t SDIOHost_CQ_StartExecuteTasks(CSDD_SDIO_Slot* pSlot, uint32_t taskIdsBitMask);
uint8_t SDIOHost_CQ_Halt(CSDD_SDIO_Slot* pSlot, uint8_t set);
uint8_t SDIOHost_CQ_TaskDiscard(CSDD_SDIO_Slot* pSlot, uint8_t taskId);
uint8_t SDIOHost_CQ_AllTasksDiscard(CSDD_SDIO_Slot* pSlot);
uint8_t SDIOHost_CQ_ResetIntCoalCounters(CSDD_SDIO_Slot* pSlot);

uint8_t SDIOHost_CQ_SetResponseErrMask(CSDD_SDIO_Slot* pSlot, uint32_t errorMask);
uint8_t SDIOHost_CQ_GetResponseErrMask(CSDD_SDIO_Slot* pSlot, uint32_t *errorMask);

#endif
