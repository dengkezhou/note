/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#include "edd_common.h"
#include "edd_data.h"

#define NS_PER_SEC          (1000000000)

/***********************************************************************
 * MAC Interrupt callbacks
 **********************************************************************/

/**
 * An MDIO operation completed.
 * @param   pD      Pointer to core private data
 * @param   read        read/write flag (1=read)
 * @param   readData    data read, if read==1
 */
static void _ev_phyManComplete(CEDI_PrivateData *pD,
                               uint8_t read, uint16_t readData) {
    phyManCompleteCount[EMAC_NUM(pD)]++;
    if (read == 1) {
        mdioReadData[EMAC_NUM(pD)] = 0x80000000 | readData;
    }
}

/**
 * Frame Received interrupt occurred.
 * @param   pD      Pointer to core private data
 * @param   queueNum    Number of the RX queue.
 */
static void _ev_rxFrame(CEDI_PrivateData *pD, uint8_t queueNum) {
    rxFrameCount[EMAC_NUM(pD)][queueNum]++;

    if (rxTiming) {
        /* record Rx delay from tx frame complete */
        /* do double-read to avoid clock-sync problem */
        emacObj[timerMac]->get1588Timer(privData[timerMac],
                                        &timeRxFrame);
        emacObj[timerMac]->get1588Timer(privData[timerMac],
                                        &timeRxFrame);
        rxDelay = (timeRxFrame.nanosecs - startRx.nanosecs);
        if (rxDelay < 0) {rxDelay += NS_PER_SEC;}
        rxDelay += (timeRxFrame.secsLower - startRx.secsLower);
        rxTiming = 0;   /* ready to restart timing */
    }

}

/**
 * Frame Rx Error interrupt occurred.
 * @param   pD      Pointer to core private data
 * @param   error       Error type:
 *  CEDI_EV_RX_USED_READ - Descriptor ring full
 *  CEDI_EV_RX_OVERRUN   - Rx Overrun
 * @param   queueNum    RX queue index
 */
static void _ev_rxError(CEDI_PrivateData *pD, uint32_t error, uint8_t queueNum) {
    if (error & CEDI_EV_RX_USED_READ) {rxUsedRead[EMAC_NUM(pD)][queueNum]++;}
    if (error & CEDI_EV_RX_OVERRUN) {rxOverrun[EMAC_NUM(pD)][queueNum]++;}
}

/**
 * Transmit event occurred
 * @param   pD      Pointer to core private data
 * @param   event       Event mask containing:
 *  CEDI_EV_TX_COMPLETE  - Frame transmitted successfully
 *  CEDI_EV_TX_USED_READ - Descriptor ring empty
 * @param   queueNum    Tx queue index
 */
static void _ev_txEvent(CEDI_PrivateData *pD, uint32_t event, uint8_t queueNum) {

    if (event & CEDI_EV_TX_USED_READ) {txUsedRead[EMAC_NUM(pD)]++;}
    if (event & CEDI_EV_TX_COMPLETE) {
        txFrComplete[EMAC_NUM(pD)][queueNum]++;
        if (txTiming) {
            /* record Tx delay since queuing the frame */
            /* do double-read to avoid clock-sync problem */
            emacObj[timerMac]->get1588Timer(privData[timerMac],
                                            &timeTxComplete);
            emacObj[timerMac]->get1588Timer(privData[timerMac],
                                            &timeTxComplete);
            txDelay = (timeTxComplete.nanosecs - startTx.nanosecs);
            if (txDelay < 0) {txDelay += NS_PER_SEC;}
            txDelay += (timeTxComplete.secsLower - startTx.secsLower);
            txTiming = 0;   /* ready to restart timing */
            if (!rxTiming) {
                startRx.nanosecs = timeTxComplete.nanosecs;
                startRx.secsLower = timeTxComplete.secsLower;
                rxTiming = 1;
            }
        }
    }
}

/**
 * Transmit error occurred
 * @param   pD      Pointer to core private data
 * @param   error       Error type:
 *  CEDI_EV_TX_UNDERRUN  - Tx underrun
   [% IF CONFIGURATION!="xgm_gxl" -%]
 *  CEDI_EV_TX_RETRY_EX_LATE_COLL    - Retry limit exceeded
   [% END -%]
 *  CEDI_EV_TX_FR_CORRUPT        - Tx frame corruption
 * @param   queueNum    Tx queue index
 */
static void _ev_txError(CEDI_PrivateData *pD, uint32_t error, uint8_t queueNum) {
    if (error & CEDI_EV_TX_UNDERRUN) {txUnderrun[EMAC_NUM(pD)]++;}

    if (error & CEDI_EV_TX_RETRY_EX_LATE_COLL) {
        txRetryExc[EMAC_NUM(pD)][queueNum]++;
    }

    if (error & CEDI_EV_TX_FR_CORRUPT) {txFrCorr[EMAC_NUM(pD)][queueNum]++;}
}

/**
 * A DMA Hresp not OK error has occurred
 * @param   pD          Pointer to core private data
 * @param   queueNum    queue index of Tx or Rx queue being accessed
 */
static void _ev_hrespError(CEDI_PrivateData *pD, uint8_t queueNum) {
    hrespNotOk[EMAC_NUM(pD)][queueNum]++;
}

/**
 * PCS auto-negotiation page received
 * @param   pD      Pointer to core private data
 * @param   nextPage    Nonzero if not the last page
 * @param   pageRx      Struct containing the link partner base
 *              or next page data
 */
static void _ev_lpPageRx(CEDI_PrivateData *pD, CEDI_LpPageRx *pageRx) {
    pcsAnPageRx[EMAC_NUM(pD)]++;
    memcpy(&pcsAnLpPage[EMAC_NUM(pD)], pageRx, sizeof(CEDI_LpPageRx));
}

/**
 * PCS auto-negotiation is complete
 * @param   pD      Pointer to core private data
 * @param   netStat     Struct containing link resolution status
 */
static void _ev_anComplete(CEDI_PrivateData *pD, CEDI_NetAnStatus *netStat) {
    pcsAnComplete[EMAC_NUM(pD)]++;
    memcpy(&pcsNetStat[EMAC_NUM(pD)], netStat, sizeof(CEDI_NetAnStatus));
}

/**
 * PCS event detected
 * @param   pD      Pointer to core private data
 * @param   linkState   Link synchronization status.
 *              If auto-negotiation is enabled:
 *              0:  link is down
 *              <>0:    link is up
 *
 */
static void _ev_linkChange(CEDI_PrivateData *pD, uint8_t linkState) {
    pcsLinkChange[EMAC_NUM(pD)]++;
    pcsLinkState[EMAC_NUM(pD)] = linkState;
}

static void _ev_lockup(CEDI_PrivateData *pD, uint32_t event) {
    if (event & CEDI_EV_RX_LOCKUP) {lockupTx[EMAC_NUM(pD)]++;}
    if (event & CEDI_EV_TX_LOCKUP) {lockupRx[EMAC_NUM(pD)]++;}
}

/**
 * Time stamp unit event has occurred.
 * @param   pD      Pointer to core private data
 * @param   event       Event type:
 *  CEDI_EV_TSU_SEC_INC  - TSU seconds register increment
 *  CEDI_EV_TSU_TIME_MATCH   - TSU timer count match
 */

static void _ev_tsuEvent(CEDI_PrivateData *pD, uint32_t event) {
    if (event & CEDI_EV_TSU_SEC_INC) {tsuSecsInc[EMAC_NUM(pD)]++;}
    if (event & CEDI_EV_TSU_TIME_MATCH) {tsuTimeMatch[EMAC_NUM(pD)]++;}
}

/**
 * Pause event detected
 * @param   pD      Pointer to core private data
 * @param   event       Event type:
 *  CEDI_EV_PAUSE_FRAME_TX   - Pause frame transmitted
 *  CEDI_EV_PAUSE_TIME_ZERO  - Pause time zero or zero quantum rx
 *  CEDI_EV_PAUSE_NZ_QU_RX   - Nonzero quantum received
 */
static void _ev_pauseEvent(CEDI_PrivateData *pD, uint32_t event) {
    if (event & CEDI_EV_PAUSE_FRAME_TX) {txPauseFr[EMAC_NUM(pD)]++;}
    if (event & CEDI_EV_PAUSE_TIME_ZERO) {pauseTimeZero[EMAC_NUM(pD)]++;}
    if (event & CEDI_EV_PAUSE_NZ_QU_RX) {rxPauseFrNonZQ[EMAC_NUM(pD)]++;}
}

/**
 * PTP primary frame has been transmitted
 * @param   pD      Pointer to core private data
 * @param   frType      PTP frame type:
 *  CEDI_EV_PTP_TX_DLY_REQ   - Delay_req
 *  CEDI_EV_PTP_TX_SYNC      - Sync
 * @param   time        PTP timer value
 */
static void _ev_ptpPriFrameTx(CEDI_PrivateData *pD, uint32_t frType, CEDI_1588TimerVal *time) {

    if (frType & CEDI_EV_PTP_TX_SYNC) {ptpTxSyncFr[EMAC_NUM(pD)]++;}
    if (frType & CEDI_EV_PTP_TX_DLY_REQ) {ptpTxDelayReqFr[EMAC_NUM(pD)]++;}

    ptpFrTime[EMAC_NUM(pD)].nanosecs = time->nanosecs;
    ptpFrTime[EMAC_NUM(pD)].secsLower = time->secsLower;
    ptpFrTime[EMAC_NUM(pD)].secsUpper = time->secsUpper;
}

/**
 * PTP peer frame has been transmitted
 * @param   pD      Pointer to core private data
 * @param   frType      PTP frame type:
 *  CEDI_EV_PTP_TX_PDLY_REQ  - Pdelay_req
 *  CEDI_EV_PTP_TX_PDLY_RSP  - Pdelay_resp
 * @param   time        PTP timer value
 */
static void _ev_ptpPeerFrameTx(CEDI_PrivateData *pD, uint32_t frType, CEDI_1588TimerVal *time) {

    if (frType & CEDI_EV_PTP_TX_PDLY_REQ) {ptpTxPDelReqFr[EMAC_NUM(pD)]++;}
    if (frType & CEDI_EV_PTP_TX_PDLY_RSP) {ptpTxPDelRspFr[EMAC_NUM(pD)]++;}

    ptpFrTime[EMAC_NUM(pD)].nanosecs = time->nanosecs;
    ptpFrTime[EMAC_NUM(pD)].secsLower = time->secsLower;
    ptpFrTime[EMAC_NUM(pD)].secsUpper = time->secsUpper;
}

/**
 * PTP primary frame has been received
 * @param   pD      Pointer to core private data
 * @param   frType      PTP frame type:
 *  CEDI_EV_PTP_RX_DLY_REQ   - Delay_req
 *  CEDI_EV_PTP_RX_SYNC      - Sync
 * @param   time        PTP timer value
 */
static void _ev_ptpPriFrameRx(CEDI_PrivateData *pD, uint32_t frType, CEDI_1588TimerVal *time) {

    if (frType & CEDI_EV_PTP_RX_SYNC) {ptpRxSyncFr[EMAC_NUM(pD)]++;}
    if (frType & CEDI_EV_PTP_RX_DLY_REQ) {ptpRxDelayReqFr[EMAC_NUM(pD)]++;}

    ptpFrTime[EMAC_NUM(pD)].nanosecs = time->nanosecs;
    ptpFrTime[EMAC_NUM(pD)].secsLower = time->secsLower;
    ptpFrTime[EMAC_NUM(pD)].secsUpper = time->secsUpper;
}

/**
 * PTP peer frame has been received
 * @param   pD      Pointer to core private data
 * @param   frType      PTP frame type:
 *  CEDI_EV_PTP_RX_PDLY_REQ  - Pdelay_req
 *  CEDI_EV_PTP_RX_PDLY_RSP  - Pdelay_resp
 * @param   time        PTP timer value
 */
static void _ev_ptpPeerFrameRx(CEDI_PrivateData *pD, uint32_t frType, CEDI_1588TimerVal *time) {

    if (frType & CEDI_EV_PTP_RX_PDLY_REQ) {ptpRxPDelReqFr[EMAC_NUM(pD)]++;}
    if (frType & CEDI_EV_PTP_RX_PDLY_RSP) {ptpRxPDelRspFr[EMAC_NUM(pD)]++;}

    ptpFrTime[EMAC_NUM(pD)].nanosecs = time->nanosecs;
    ptpFrTime[EMAC_NUM(pD)].secsLower = time->secsLower;
    ptpFrTime[EMAC_NUM(pD)].secsUpper = time->secsUpper;
}

/**
 * LPI indication status bit has changed.
 * @param   pD      Pointer to core private data
 */
static void _ev_lpiStatus(CEDI_PrivateData *pD) {
    lpiIndChange[EMAC_NUM(pD)]++;
}

/**
 * Wake on LAN event detected.
 * @param   pD      Pointer to core private data
 */
static void _ev_wolEvent(CEDI_PrivateData *pD) {
    wakeOnLanEvent[EMAC_NUM(pD)]++;
}

/**
 * External Input Interrupt detected.
 * @param   pD      Pointer to core private data
 */
static void _ev_extInpIntr(CEDI_PrivateData *pD) {
    extInputEvent[EMAC_NUM(pD)]++;
}

/**
 * PCS25G synchronization change event
 */
static void _ev_blockLock(CEDI_PrivateData* pD, uint8_t val) {
    blockLockEvent[EMAC_NUM(pD)]++;
}

/**
 * Bit Error Ratio event 
 */
static void _ev_BER(CEDI_PrivateData* pD, uint32_t berCount) {
    berEvent[EMAC_NUM(pD)]++;
}

CEDI_Callbacks core_callbacks = {
    .phyManComplete     = _ev_phyManComplete,
    .rxFrame            = _ev_rxFrame,
    .rxError            = _ev_rxError,
    .txEvent            = _ev_txEvent,
    .txError            = _ev_txError,
    .hrespError         = _ev_hrespError,
    .lpPageRx           = _ev_lpPageRx,
    .anComplete         = _ev_anComplete,
    .linkChange         = _ev_linkChange,
    .lockupEvent        = _ev_lockup,
    .tsuEvent           = _ev_tsuEvent,
    .pauseEvent         = _ev_pauseEvent,
    .ptpPriFrameTx      = _ev_ptpPriFrameTx,
    .ptpPeerFrameTx     = _ev_ptpPeerFrameTx,
    .ptpPriFrameRx      = _ev_ptpPriFrameRx,
    .ptpPeerFrameRx     = _ev_ptpPeerFrameRx,
    .lpiStatus          = _ev_lpiStatus,
    .wolEvent           = _ev_wolEvent,
    .extInpIntr         = _ev_extInpIntr,
    .syncEvent          = _ev_blockLock,
    .highBitError       = _ev_BER
};
