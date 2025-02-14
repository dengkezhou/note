/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#include "cedi_obj_if.h"
#include "cedi_if.h"
#include "cedi_structs_if.h"

#ifdef __BARE_METAL__
#include "wrapper_control.h"
#endif //__BARE_METAL__

#include "edd_common.h"
#include "edd_int.h"

/* Register base addresses, replaced with mappings when in kernel. */
void *emac_reg_base[ETH_NUMS] = {(void *)EMAC_REG_BASE_ADDRESS0, (void *)EMAC_REG_BASE_ADDRESS1, (void *)EMAC_REG_BASE_ADDRESS2, (void *)EMAC_REG_BASE_ADDRESS3};

CEDI_PrivateData *privData[ETH_NUMS];
CEDI_Statistics *statRegs[ETH_NUMS];
CEDI_OBJ *emacObj[ETH_NUMS];

CEDI_BuffAddr aBuf[CEDI_MAX_RX_QUEUES][CEDI_MAX_RX_QUEUES];
CEDI_BuffAddr nBuf[CEDI_MAX_RX_QUEUES][CEDI_MAX_RX_QUEUES];
//CEDI_BuffAddr aBuf[CEDI_MAX_RX_QUEUES][MAX_TEST_RBQ_LENGTH + 1]; /* initial rx buffers */
//CEDI_BuffAddr nBuf[CEDI_MAX_RX_QUEUES][MAX_TEST_RBQ_LENGTH + 1]; /* new rx buffers to swap in */
uint16_t rxBufLenBytes[CEDI_MAX_RX_QUEUES] = {0};
uint16_t oldIndex[CEDI_MAX_RX_QUEUES] = {0};
uint16_t newIndex[CEDI_MAX_RX_QUEUES] = {0};
uint8_t txBuffer[MAX_JUMBO_FRAME_LENGTH + 3] = {0};
uint8_t rxBuffer[MAX_JUMBO_FRAME_LENGTH] = {0};

/* vars used by callbacks for interrupt moderation test */
uint8_t txTiming;
uint8_t rxTiming;
uint8_t timerMac;
CEDI_1588TimerVal startTx, startRx;
int txDelay, rxDelay;
CEDI_1588TimerVal timeTxComplete, timeRxFrame;

/* callback event counters and "old" ones for detecting callback */
uint32_t phyManCompleteCount[ETH_NUMS];
uint32_t oldPhyManCompleteCount[ETH_NUMS];
uint32_t mdioReadData[ETH_NUMS];   /* set top bit if read, save read data in lower 16 bits */
uint32_t rxFrameCount[ETH_NUMS][CEDI_MAX_RX_QUEUES];
uint32_t oldRxFrameCount[ETH_NUMS][CEDI_MAX_RX_QUEUES];
uint32_t rxUsedRead[ETH_NUMS][CEDI_MAX_RX_QUEUES];
uint32_t oldRxUsedRead[ETH_NUMS][CEDI_MAX_RX_QUEUES];
uint32_t rxOverrun[ETH_NUMS][CEDI_MAX_RX_QUEUES];
uint32_t oldRxOverrun[ETH_NUMS][CEDI_MAX_RX_QUEUES];
uint32_t txUsedRead[ETH_NUMS];
uint32_t oldTxUsedRead[ETH_NUMS];
uint32_t txFrComplete[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t oldTxFrComplete[ETH_NUMS][CEDI_MAX_TX_QUEUES];
/* params for Tx frame complete - */
uint32_t txFrBufAddr[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t txCbDescStat[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t txUnderrun[ETH_NUMS];
uint32_t oldTxUnderrun[ETH_NUMS];
uint32_t txRetryExc[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t oldTxRetryExc[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t txFrCorr[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t oldTxFrCorr[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t hrespNotOk[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t oldHrespNotOk[ETH_NUMS][CEDI_MAX_TX_QUEUES];
uint32_t rxPauseFrNonZQ[ETH_NUMS];
uint32_t oldRxPauseFrNonZQ[ETH_NUMS];
uint32_t pauseTimeZero[ETH_NUMS];
uint32_t oldPauseTimeZero[ETH_NUMS];
uint32_t txPauseFr[ETH_NUMS];
uint32_t oldTxPauseFr[ETH_NUMS];
uint32_t ptpTxSyncFr[ETH_NUMS];
uint32_t oldPtpTxSyncFr[ETH_NUMS];
uint32_t ptpTxDelayReqFr[ETH_NUMS];
uint32_t oldPtpTxDelayReqFr[ETH_NUMS];
uint32_t ptpRxSyncFr[ETH_NUMS];
uint32_t oldPtpRxSyncFr[ETH_NUMS];
uint32_t ptpRxDelayReqFr[ETH_NUMS];
uint32_t oldPtpRxDelayReqFr[ETH_NUMS];
uint32_t ptpTxPDelReqFr[ETH_NUMS];
uint32_t oldPtpTxPDelReqFr[ETH_NUMS];
uint32_t ptpTxPDelRspFr[ETH_NUMS];
uint32_t oldPtpTxPDelRspFr[ETH_NUMS];
uint32_t ptpRxPDelReqFr[ETH_NUMS];
uint32_t oldPtpRxPDelReqFr[ETH_NUMS];
uint32_t ptpRxPDelRspFr[ETH_NUMS];
uint32_t oldPtpRxPDelRspFr[ETH_NUMS];
CEDI_1588TimerVal ptpFrTime[ETH_NUMS];
uint32_t tsuSecsInc[ETH_NUMS];
uint32_t oldTsuSecsInc[ETH_NUMS];
uint32_t tsuTimeMatch[ETH_NUMS];
uint32_t oldTsuTimeMatch[ETH_NUMS];
uint32_t pcsAnPageRx[ETH_NUMS];
uint32_t oldPcsAnPageRx[ETH_NUMS];
CEDI_LpPageRx pcsAnLpPage[ETH_NUMS];
uint32_t pcsAnComplete[ETH_NUMS];
uint32_t oldPcsAnComplete[ETH_NUMS];
CEDI_NetAnStatus pcsNetStat[ETH_NUMS];
uint32_t pcsLinkChange[ETH_NUMS];
uint32_t oldPcsLinkChange[ETH_NUMS];
uint8_t pcsLinkState[ETH_NUMS];
uint8_t lockupRx[ETH_NUMS];
uint8_t lockupTx[ETH_NUMS];
uint8_t oldLockupRx[ETH_NUMS];
uint8_t oldLockupTx[ETH_NUMS];
uint32_t lpiIndChange[ETH_NUMS];
uint32_t oldLpiIndChange[ETH_NUMS];
uint32_t wakeOnLanEvent[ETH_NUMS];
uint32_t oldWakeOnLanEvent[ETH_NUMS];
uint32_t extInputEvent[ETH_NUMS];
uint32_t oldExtInputEvent[ETH_NUMS];
uint32_t blockLockEvent[ETH_NUMS];
uint32_t oldBlockLockEvent[ETH_NUMS];
uint32_t berEvent[ETH_NUMS];
uint32_t oldBerEvent[ETH_NUMS];

