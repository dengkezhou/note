/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#ifndef INCLUDE_EDD_DATA_H
#define INCLUDE_EDD_DATA_H

#include "edd_common.h"
#include "edd_int.h"
#include "cedi_if.h"
#include "cedi_obj_if.h"
#include "cedi_structs_if.h"

/* use test globals with this */
#define regAddr(gem, regname)  (&(privData[gem]->regs->regname))
#define eRegAddr(gem, regname) (&(eMacPrivData[gem]->regs->regname))

#define EMAC_NUM(pDat) (((((CEDI_PrivateData *)pDat)->cfg).regBase) == (uintptr_t)emac_reg_base[0]) ? 0 : ((((((CEDI_PrivateData *)pDat)->cfg).regBase) == (uintptr_t)emac_reg_base[1]) ? 1 : ((((((CEDI_PrivateData *)pDat)->cfg).regBase) == (uintptr_t)emac_reg_base[2]) ? 2 : 3))

/***********  Global test variables, externed elsewhere  *********************/

/* Register base addresses, replaced with mappings when in kernel. */
extern void *emac_reg_base[ETH_NUMS];

extern CEDI_PrivateData *privData[ETH_NUMS];
extern CEDI_Statistics *statRegs[ETH_NUMS];
extern CEDI_OBJ *emacObj[ETH_NUMS];

extern CEDI_BuffAddr aBuf[CEDI_MAX_RX_QUEUES][CEDI_MAX_RX_QUEUES]; /* initial rx buffers */
extern CEDI_BuffAddr nBuf[CEDI_MAX_RX_QUEUES][CEDI_MAX_RX_QUEUES]; /* new rx buffers to swap in */
//extern CEDI_BuffAddr aBuf[CEDI_MAX_RX_QUEUES][MAX_TEST_RBQ_LENGTH + 1]; /* initial rx buffers */
//extern CEDI_BuffAddr nBuf[CEDI_MAX_RX_QUEUES][MAX_TEST_RBQ_LENGTH + 1]; /* new rx buffers to swap in */
extern uint16_t rxBufLenBytes[CEDI_MAX_RX_QUEUES],
                oldIndex[CEDI_MAX_RX_QUEUES], newIndex[CEDI_MAX_RX_QUEUES];
extern uint8_t txBuffer[MAX_JUMBO_FRAME_LENGTH + 3];
extern uint8_t rxBuffer[MAX_JUMBO_FRAME_LENGTH];

/* vars used by callbacks for interrupt moderation test */
extern uint8_t txTiming;
extern uint8_t rxTiming;
extern uint8_t timerMac;
extern CEDI_1588TimerVal startTx, startRx;
extern int txDelay, rxDelay;
extern CEDI_1588TimerVal timeTxComplete, timeRxFrame;

/* callback event counters and "old" ones for detecting callback */
extern uint32_t phyManCompleteCount[ETH_NUMS];
extern uint32_t oldPhyManCompleteCount[ETH_NUMS];
extern uint32_t mdioReadData[ETH_NUMS];   /* set top bit if read, save read data in lower 16 bits */
extern uint32_t rxFrameCount[ETH_NUMS][CEDI_MAX_RX_QUEUES];
extern uint32_t oldRxFrameCount[ETH_NUMS][CEDI_MAX_RX_QUEUES];
extern uint32_t rxUsedRead[ETH_NUMS][CEDI_MAX_RX_QUEUES];
extern uint32_t oldRxUsedRead[ETH_NUMS][CEDI_MAX_RX_QUEUES];
extern uint32_t rxOverrun[ETH_NUMS][CEDI_MAX_RX_QUEUES];
extern uint32_t oldRxOverrun[ETH_NUMS][CEDI_MAX_RX_QUEUES];
extern uint32_t txUsedRead[ETH_NUMS];
extern uint32_t oldTxUsedRead[ETH_NUMS];
extern uint32_t txFrComplete[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t oldTxFrComplete[ETH_NUMS][CEDI_MAX_TX_QUEUES];
/* params for Tx frame complete - */
extern uint32_t txFrBufAddr[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t txCbDescStat[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t txUnderrun[ETH_NUMS];
extern uint32_t oldTxUnderrun[ETH_NUMS];
extern uint32_t txRetryExc[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t oldTxRetryExc[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t txFrCorr[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t oldTxFrCorr[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t hrespNotOk[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t oldHrespNotOk[ETH_NUMS][CEDI_MAX_TX_QUEUES];
extern uint32_t rxPauseFrNonZQ[ETH_NUMS];
extern uint32_t oldRxPauseFrNonZQ[ETH_NUMS];
extern uint32_t pauseTimeZero[ETH_NUMS];
extern uint32_t oldPauseTimeZero[ETH_NUMS];
extern uint32_t txPauseFr[ETH_NUMS];
extern uint32_t oldTxPauseFr[ETH_NUMS];
extern uint32_t ptpTxSyncFr[ETH_NUMS];
extern uint32_t oldPtpTxSyncFr[ETH_NUMS];
extern uint32_t ptpTxDelayReqFr[ETH_NUMS];
extern uint32_t oldPtpTxDelayReqFr[ETH_NUMS];
extern uint32_t ptpRxSyncFr[ETH_NUMS];
extern uint32_t oldPtpRxSyncFr[ETH_NUMS];
extern uint32_t ptpRxDelayReqFr[ETH_NUMS];
extern uint32_t oldPtpRxDelayReqFr[ETH_NUMS];
extern uint32_t ptpTxPDelReqFr[ETH_NUMS];
extern uint32_t oldPtpTxPDelReqFr[ETH_NUMS];
extern uint32_t ptpTxPDelRspFr[ETH_NUMS];
extern uint32_t oldPtpTxPDelRspFr[ETH_NUMS];
extern uint32_t ptpRxPDelReqFr[ETH_NUMS];
extern uint32_t oldPtpRxPDelReqFr[ETH_NUMS];
extern uint32_t ptpRxPDelRspFr[ETH_NUMS];
extern uint32_t oldPtpRxPDelRspFr[ETH_NUMS];
extern CEDI_1588TimerVal ptpFrTime[ETH_NUMS];
extern uint32_t tsuSecsInc[ETH_NUMS];
extern uint32_t oldTsuSecsInc[ETH_NUMS];
extern uint32_t tsuTimeMatch[ETH_NUMS];
extern uint32_t oldTsuTimeMatch[ETH_NUMS];
extern uint32_t pcsAnPageRx[ETH_NUMS];
extern uint32_t oldPcsAnPageRx[ETH_NUMS];
extern CEDI_LpPageRx pcsAnLpPage[ETH_NUMS];
extern uint32_t pcsAnComplete[ETH_NUMS];
extern uint32_t oldPcsAnComplete[ETH_NUMS];
extern CEDI_NetAnStatus pcsNetStat[ETH_NUMS];
extern uint32_t pcsLinkChange[ETH_NUMS];
extern uint32_t oldPcsLinkChange[ETH_NUMS];
extern uint8_t pcsLinkState[ETH_NUMS];
extern uint8_t lockupRx[ETH_NUMS];
extern uint8_t lockupTx[ETH_NUMS];
extern uint8_t oldLockupRx[ETH_NUMS];
extern uint8_t oldLockupTx[ETH_NUMS];
extern uint32_t lpiIndChange[ETH_NUMS];
extern uint32_t oldLpiIndChange[ETH_NUMS];
extern uint32_t wakeOnLanEvent[ETH_NUMS];
extern uint32_t oldWakeOnLanEvent[ETH_NUMS];
extern uint32_t extInputEvent[ETH_NUMS];
extern uint32_t oldExtInputEvent[ETH_NUMS];
extern uint32_t blockLockEvent[ETH_NUMS];
extern uint32_t oldBlockLockEvent[ETH_NUMS];
extern uint32_t berEvent[ETH_NUMS];
extern uint32_t oldBerEvent[ETH_NUMS];

#endif //INCLUDE_EDD_DATA_H
