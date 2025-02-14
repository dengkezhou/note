/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#include "edd_support.h"
#include "edd_log.h"
#include <malloc.h>
#include <eth.h>

#ifdef __BARE_METAL__
long NCPS_freeHWMem(uintptr_t addr)
{
    free((void *)addr);
    return addr;
}
#endif

extern CEDI_Callbacks core_callbacks;

void insertEthHeader(ethHdr_t* header, CEDI_BuffAddr* buffer)
{
    uint8_t j;
    for (j = 0; j < (sizeof(ethHdr_t) / sizeof(uint8_t)); j++) {
        CPS_UncachedWrite8(((uint8_t*)(buffer->vAddr)) + j, ((uint8_t*)header)[j]);
    }
}

uint32_t initConfigMaxNumQs(uint8_t objInst, uint16_t txQSize,
                            uint16_t rxQSize,uint16_t rxBufLenBytes,
                            uint32_t intrEvents, CEDI_Config *cfg)
{
    uint8_t numQs;

    if (objInst > ETH_NUMS - 1) {
        return EINVAL;
    }

    numQs = cfgHwQs(objInst);

    return initConfig(objInst, numQs, txQSize, rxQSize, rxBufLenBytes,
                      intrEvents, cfg);
}

/* fill up an CEDI_Config struct with common values for testing */
uint32_t initConfig(uint8_t objInst, uint8_t numQs,
                    uint16_t txQSize, uint16_t rxQSize,
                    uint16_t rxBufLenBytes, uint32_t intrEvents,
                    CEDI_Config *cfg)
{
    uint8_t q;
#ifdef CSP
    uint32_t design_dbg1_reg, hwDMABusWidth;
#endif

    if ((objInst > ETH_NUMS - 1) || (cfg == NULL) ||
        (txQSize > CEDI_MAX_TBQ_LENGTH) || (rxQSize > CEDI_MAX_RBQ_LENGTH)) {
        return EINVAL;
    }

    memset(cfg, 0, sizeof(CEDI_Config));

    cfg->regBase = (uintptr_t)emac_reg_base[objInst];
    cfg->rxQs = numQs;
    cfg->txQs = numQs;
    for (q = 0; q < cfg->rxQs; q++) {
        cfg->rxQLen[q] = rxQSize;
    }

    for (q = 0; q < cfg->txQs; q++) {
        cfg->txQLen[q] = txQSize;
    }

    for (q = 0; q < cfg->rxQs; q++) {
        cfg->rxBufLength[q] = rxBufLenBytes >> 6;
    }

#ifdef CSP
    design_dbg1_reg = CPS_UncachedRead32(&(((struct emac_regs *)emac_reg_base[objInst])->designcfg_debug1));
    hwDMABusWidth = EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__READ(design_dbg1_reg);
    hwDMABusWidth <<= 5;

    switch (hwDMABusWidth) {
    case 32u:     // 001
        cfg->dmaBusWidth = CEDI_DMA_BUS_WIDTH_32;
        break;

    case 64u:     // 010
        cfg->dmaBusWidth = CEDI_DMA_BUS_WIDTH_64;
        break;

    case 128u:     // 100
        cfg->dmaBusWidth = CEDI_DMA_BUS_WIDTH_128;
        break;

    default:
        log_dbg_warn("WARNING: dbg_dma_bus_width is: %02X, setting 64-bit width\n", hwDMABusWidth >> 5);
        cfg->dmaBusWidth = CEDI_DMA_BUS_WIDTH_64;
        break;
    }

#else
    cfg->dmaBusWidth = CEDI_DMA_BUS_WIDTH_64;
#endif

    /* enable all Tx & Rx interrupts on start */
    cfg->intrEnable = intrEvents;
    cfg->rxPktBufSize = 3;
    cfg->txPktBufSize = 1;
    cfg->dmaDataBurstLen = CEDI_DMA_DBUR_LEN_4;
    cfg->dmaCfgFlags = 0;
#ifdef CEDI_64B_COMPILE
	if (cfg->regBase == EMAC_REG_BASE_ADDRESS3)
		cfg->dmaAddrBusWidth = CEDI_DMA_ADDR_BUS_WIDTH_32;
	else
		cfg->dmaAddrBusWidth = CEDI_DMA_ADDR_BUS_WIDTH_64;
#else
    cfg->dmaAddrBusWidth = CEDI_DMA_ADDR_BUS_WIDTH_32;
#endif
    setExtBDModeForAllQueues(cfg, TXTS_DISABLED, RXTS_DISABLED);
    cfg->aw2bMaxPipeline = 1;
    cfg->ar2rMaxPipeline = 1;
    cfg->pfcMultiQuantum = 0;
    cfg->enableMdio = 0;
    cfg->mdcPclkDiv = CEDI_MDC_DIV_BY_32;
    cfg->ifTypeSel = CEDI_IFSP_GMII;
    cfg->ifSpeedSel = CEDI_SPEED_1000M;
    cfg->altSgmiiEn = 0;
    cfg->fullDuplex = 1;
    cfg->enRxHalfDupTx = 0;
    cfg->extAddrMatch = 0;
    cfg->rxBufOffset = 0;
    cfg->rxLenErrDisc = 0;
    cfg->uniDirEnable = 0;
    cfg->disCopyPause = 0;
    cfg->chkSumOffEn = 0;
    cfg->rx1536ByteEn = 0;
    cfg->rxJumboFrEn = 0;
    cfg->enRxBadPreamble = 0;
    cfg->ignoreIpgRxEr = 0;
    cfg->storeUdpTcpOffset = 0;
    cfg->enExtTsuPort = 0;

    return CDN_EOK;
}

uint32_t testSetup (uint8_t objInst, uint16_t txQSize,
                    uint16_t rxQSize, uint16_t rxBufLenBytes, CEDI_Config *cfgPtr )
{
    uint32_t result;
    uint32_t eventsToEnable;

    CEDI_Config cfg;
    CEDI_SysReq req;

    emacObj[objInst] = CEDI_GetInstance();

    log_dbg_fyi("\n");

    if (cfgPtr == NULL) {
        memset(&cfg, 0, sizeof(cfg));

        eventsToEnable = CEDI_EVSET_TX_RX_EVENTS;

        /* setup default config */
        if (0 != (result = initConfigMaxNumQs(objInst, txQSize, rxQSize, rxBufLenBytes, eventsToEnable, &cfg))) {
            log_dbg_crit("Error in initConfig: returned %d\n", result);
            return result;
        }

    } else {
        memcpy(&cfg,cfgPtr,sizeof(cfg));        // copy the additional cfg settings.
    }

    if (CDN_EOK != (result = emacObj[objInst]->probe(&cfg, &req))) {
        log_dbg_crit("Invalid return value: %d\n", result);
        return result;
    }

    if (0 != (result = allocSysReqMem(objInst, &req, &cfg))) {
        log_dbg_crit("Error in allocSysReqMem: returned %d\n", result);
        return result;
    }

    /* if PCS is present, must test using TBI as wrapper is configured differently
     * (but don't override SGMII if that is selected) */
    if ((0 == EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(CPS_UncachedRead32(
                                                            &(((struct emac_regs *)emac_reg_base[objInst])->designcfg_debug1)))) &&
        ((cfg.ifTypeSel == CEDI_IFSP_MII) || (cfg.ifTypeSel == CEDI_IFSP_GMII))) {
        cfg.ifTypeSel = CEDI_IFSP_BASE_X;
        cfg.ifSpeedSel = CEDI_SPEED_1000M;
    }

    if (CDN_EOK != (result = emacObj[objInst]->init(privData[objInst], &cfg, &core_callbacks))) {
        log_dbg_crit("Error in emacObj%u->init: returned %d\n", objInst, result);
        return result;
    }

    return CDN_EOK;
}

void testTearDown(uint8_t objInst)
{
    if (emacObj[objInst]) {
        emacObj[objInst]->destroy(privData[objInst]);
    }

    if (privData[objInst]) {
        free(privData[objInst]);
    }
    privData[objInst] = NULL;

    if (statRegs[objInst]) {
        free(statRegs[objInst]);
    }
    statRegs[objInst] = NULL;
}

void setExtBDModeForAllQueues(CEDI_Config *cfg, uint8_t tx_extbd_enable, uint8_t rx_extbd_enable) {
    uint8_t q;
    for (q = 0; q < CEDI_MAX_TX_QUEUES; q++) {
        cfg->enTxExtBD[q] = tx_extbd_enable;
    }
    for (q = 0; q < CEDI_MAX_RX_QUEUES; q++) {
        cfg->enRxExtBD[q] = rx_extbd_enable;
    }
}

uint32_t allocSysReqMem(uint8_t objInst, CEDI_SysReq *req,CEDI_Config *cfg )
{
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (objInst == ETH3)
		privData[objInst] = (CEDI_PrivateData *)gmac3_mem_alloc();
	else
		privData[objInst] = malloc(req->privDataSize);
#else
	privData[objInst] = malloc(req->privDataSize);
#endif
    if (!privData[objInst]) {
        log_dbg_crit("Unable to allocate space for privData\n");
        return 1;
    }

    log_dbg_fyi("Private Data size: %d\n", req->privDataSize);

	/* Allocate Rx descriptor ring */
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (objInst == ETH3)
		cfg->rxQAddr = (uintptr_t)gmac3_mem_alloc();
	else
		cfg->rxQAddr = (uintptr_t)malloc(req->rxDescListSize);
#else
	cfg->rxQAddr = (uintptr_t)malloc(req->rxDescListSize);
#endif
    if (!cfg->rxQAddr) {
        log_dbg_crit("Unable to allocate space for Rx descriptors\n");
        return 2;
    }

    /* now get the physical address */
    CPS_WritePhysAddress32((uint32_t *)cfg->rxQAddr, cfg->rxQAddr);
    cfg->rxQPhyAddr = CPS_UncachedRead32((uint32_t *)cfg->rxQAddr);

	/* Allocate Tx descriptor ring */
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (objInst == ETH3)
		cfg->txQAddr = (uintptr_t)gmac3_mem_alloc();
	else
		cfg->txQAddr = (uintptr_t)malloc(req->txDescListSize);
#else
	cfg->txQAddr = (uintptr_t)malloc(req->txDescListSize);
#endif
    if (!cfg->txQAddr) {
        log_dbg_crit("Unable to allocate space for Tx descriptors\n");
        return 3;
    }

    /* now get the physical address */
    CPS_WritePhysAddress32((uint32_t *)cfg->txQAddr, cfg->txQAddr);
    cfg->txQPhyAddr = CPS_UncachedRead32((uint32_t *)cfg->txQAddr);

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (objInst == ETH3)
		statRegs[objInst] = (CEDI_Statistics *)gmac3_mem_alloc();
	else
		statRegs[objInst] = (CEDI_Statistics *)malloc(req->statsSize);
#else
	statRegs[objInst] = (CEDI_Statistics *)malloc(req->statsSize);
#endif
    cfg->statsRegs = (uintptr_t)statRegs[objInst];

    return 0;
}

uint8_t cfgHwQs(uint8_t emacInst) {

    #define IS_DMA_QUEUE(x) EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__READ(x)

    uint8_t qCount = 1;
    uint32_t reg = CPS_UncachedRead32(&(
                                          ((struct emac_regs *)emac_reg_base[emacInst])->designcfg_debug6 ));
    uint8_t i;

    for (i = 0; i < MAX_QUEUES_NUM - 1U; i++) {
        if (IS_DMA_QUEUE(reg >> i) != 0U) {
            qCount++;
        }
    }

    return qCount;
}

void zeroCallbackCounters(void) {
    uint32_t i, q;
    for (i = 0; i < ETH_NUMS; i++) {
        phyManCompleteCount[i] = 0;
        oldPhyManCompleteCount[i] = 0;
        mdioReadData[i] = 0;
        txUsedRead[i] = 0;
        oldTxUsedRead[i] = 0;
        txUnderrun[i] = 0;
        oldTxUnderrun[i] = 0;
        rxPauseFrNonZQ[i] = 0;
        oldRxPauseFrNonZQ[i] = 0;
        pauseTimeZero[i] = 0;
        oldPauseTimeZero[i] = 0;
        txPauseFr[i] = 0;
        oldTxPauseFr[i] = 0;
        ptpTxSyncFr[i] = 0;
        oldPtpTxSyncFr[i] = 0;
        ptpTxDelayReqFr[i] = 0;
        oldPtpTxDelayReqFr[i] = 0;
        ptpRxSyncFr[i] = 0;
        oldPtpRxSyncFr[i] = 0;
        ptpRxDelayReqFr[i] = 0;
        oldPtpRxDelayReqFr[i] = 0;
        ptpTxPDelReqFr[i] = 0;
        oldPtpTxPDelReqFr[i] = 0;
        ptpTxPDelRspFr[i] = 0;
        oldPtpTxPDelRspFr[i] = 0;
        ptpRxPDelReqFr[i] = 0;
        oldPtpRxPDelReqFr[i] = 0;
        ptpRxPDelRspFr[i] = 0;
        oldPtpRxPDelRspFr[i] = 0;
        tsuSecsInc[i] = 0;
        oldTsuSecsInc[i] = 0;
        tsuTimeMatch[i] = 0;
        oldTsuTimeMatch[i] = 0;
        pcsAnPageRx[i] = 0;
        oldPcsAnPageRx[i] = 0;
        memset(&pcsAnLpPage[i], 0, sizeof(CEDI_LpPageRx));
        pcsAnComplete[i] = 0;
        oldPcsAnComplete[i] = 0;
        memset(&pcsNetStat[i], 0, sizeof(CEDI_NetAnStatus));
        pcsLinkChange[i] = 0;
        oldPcsLinkChange[i] = 0;
        pcsLinkState[i] = 0;
        lockupRx[i] = 0;
        lockupTx[i] = 0;
        oldLockupRx[i] = 0;
        oldLockupTx[i] = 0;
        lpiIndChange[i] = 0;
        oldLpiIndChange[i] = 0;
        wakeOnLanEvent[i] = 0;
        oldWakeOnLanEvent[i] = 0;
        extInputEvent[i] = 0;
        oldExtInputEvent[i] = 0;

        for (q = 0; q < CEDI_MAX_TX_QUEUES; q++) {
            rxFrameCount[i][q] = 0;
            oldRxFrameCount[i][q] = 0;
            rxUsedRead[i][q] = 0;
            oldRxUsedRead[i][q] = 0;
            rxOverrun[i][q] = 0;
            oldRxOverrun[i][q] = 0;
            txFrComplete[i][q] = 0;
            oldTxFrComplete[i][q] = 0;
            txRetryExc[i][q] = 0;
            oldTxRetryExc[i][q] = 0;
            txFrCorr[i][q] = 0;
            oldTxFrCorr[i][q] = 0;
            hrespNotOk[i][q] = 0;
            oldHrespNotOk[i][q] = 0;
        }
    }
}

uint32_t allocBuffer(uint32_t bytes, uint32_t fill, CEDI_BuffAddr *buf) {

    uint32_t tmp, blockLen;

    /* round up size to multiple of 32 bits */
    blockLen = 4 * (bytes / 4 + ((bytes % 4)   ? 1   : 0));

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (is_gmac3)
		buf->vAddr = (uintptr_t)gmac3_mem_alloc();
	else
		buf->vAddr = (uintptr_t)malloc(blockLen);
#else
	buf->vAddr = (uintptr_t)malloc(blockLen);
#endif
    if (!(buf->vAddr)) {
        return CDN_EINVAL;
    }

#ifdef CEDI_64B_COMPILE
    //CPS_WritePhysAddress32((uint32_t *)buf->vAddr, (uint32_t)(buf->vAddr & 0xFFFFFFFF));
    //CPS_WritePhysAddress32((uint32_t *)(buf->vAddr + 4), 0);
    //buf->pAddr = (uint64_t)(((unsigned long)CPS_UncachedRead32((uint32_t *)(buf->vAddr + 4)) << 32) | CPS_UncachedRead32((uint32_t *)buf->vAddr));
	buf->pAddr = buf->vAddr;
#else
    /* get the physical buffer address */
    CPS_WritePhysAddress32((uint32_t *)buf->vAddr, buf->vAddr);
    buf->pAddr = CPS_UncachedRead32((uint32_t *)buf->vAddr);
#endif

    /* --> remove the pattern-filling to speed up regression testing... */
    for (tmp = 0; tmp < bytes; tmp += 4) {
        CPS_UncachedWrite32((uint32_t *)(buf->vAddr + tmp), fill + tmp); // use pattern for debugging
    }

    return CDN_EOK;
}

uint32_t detectCallback(uint8_t mac)
{
    uint32_t q;
    uint8_t change = 0;

    if (phyManCompleteCount[mac] > oldPhyManCompleteCount[mac]) {
        oldPhyManCompleteCount[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u PHY Management Frame Sent cb counted\n", mac);
    }
    if (txUsedRead[mac] > oldTxUsedRead[mac]) {
        oldTxUsedRead[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u txUsedRead cb counted\n", mac);
    }
    if (txUnderrun[mac] > oldTxUnderrun[mac]) {
        oldTxUnderrun[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u txUnderrun cb counted\n", mac);
    }
    if (rxPauseFrNonZQ[mac] > oldRxPauseFrNonZQ[mac]) {
        oldRxPauseFrNonZQ[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u rxPauseFrNonZeroQuantum cb counted\n", mac);
    }
    if (pauseTimeZero[mac] > oldPauseTimeZero[mac]) {
        oldPauseTimeZero[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u pauseTimeZero cb counted\n", mac);
    }
    if (txPauseFr[mac] > oldTxPauseFr[mac]) {
        oldTxPauseFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u txPauseFr cb counted\n", mac);
    }
    if (ptpTxSyncFr[mac] > oldPtpTxSyncFr[mac]) {
        oldPtpTxSyncFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpTxSyncFr cb counted\n", mac);
    }
    if (ptpTxDelayReqFr[mac] > oldPtpTxDelayReqFr[mac]) {
        oldPtpTxDelayReqFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpTxDelayReqFr cb counted\n", mac);
    }
    if (ptpRxSyncFr[mac] > oldPtpRxSyncFr[mac]) {
        oldPtpRxSyncFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpRxSyncFr cb counted\n", mac);
    }
    if (ptpRxDelayReqFr[mac] > oldPtpRxDelayReqFr[mac]) {
        oldPtpRxDelayReqFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpRxDelayReqFr cb counted\n", mac);
    }
    if (ptpTxPDelReqFr[mac] > oldPtpTxPDelReqFr[mac]) {
        oldPtpTxPDelReqFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpTxPDelayReqFr cb counted\n", mac);
    }
    if (ptpTxPDelRspFr[mac] > oldPtpTxPDelRspFr[mac]) {
        oldPtpTxPDelRspFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpTxPDelayRespFr cb counted\n", mac);
    }
    if (ptpRxPDelReqFr[mac] > oldPtpRxPDelReqFr[mac]) {
        oldPtpRxPDelReqFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpRxPDelayReqFr cb counted\n", mac);
    }
    if (ptpRxPDelRspFr[mac] > oldPtpRxPDelRspFr[mac]) {
        oldPtpRxPDelRspFr[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u ptpRxPDelayRespFr cb counted\n", mac);
    }

    if (tsuSecsInc[mac] > oldTsuSecsInc[mac]) {
        oldTsuSecsInc[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u tsuSecsInc cb counted\n", mac);
    }
    if (tsuTimeMatch[mac] > oldTsuTimeMatch[mac]) {
        oldTsuTimeMatch[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u tsuTimeMatch cb counted\n", mac);
    }

    if (pcsAnPageRx[mac] > oldPcsAnPageRx[mac]) {
        oldPcsAnPageRx[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u pcsAnPageRx cb counted\n", mac);
    }
    if (pcsAnComplete[mac] > oldPcsAnComplete[mac]) {
        oldPcsAnComplete[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u pcsAnComplete cb counted\n", mac);
    }
    if (lockupRx[mac] > oldLockupRx[mac]) {
        oldLockupRx[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u lockupRx cb counted\n", mac);
    }
    if (lockupTx[mac] > oldLockupTx[mac]) {
        oldLockupTx[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u lockupTx cb counted\n", mac);
    }

    if (lpiIndChange[mac] > oldLpiIndChange[mac]) {
        oldLpiIndChange[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u lpiIndChange cb counted\n", mac);
    }
    if (wakeOnLanEvent[mac] > oldWakeOnLanEvent[mac]) {
        oldWakeOnLanEvent[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u wakeOnLanEvent cb counted\n", mac);
    }
    if (extInputEvent[mac] > oldExtInputEvent[mac]) {
        oldExtInputEvent[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u extInputEvent cb counted\n", mac);
    }

    if (berEvent[mac] > oldBerEvent[mac]) {
        oldBerEvent[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u berEvent cb counted\n", mac);
    }

    if (blockLockEvent[mac] > oldBlockLockEvent[mac]) {
        oldBlockLockEvent[mac]++;
        change = 1;
        log_dbg_fyi("--- MAC%u berEvent cb counted\n", mac);
    }

    for (q = 0; q < privData[mac]->numQs; q++) {
        if (rxFrameCount[mac][q] > oldRxFrameCount[mac][q]) {
            change = 1;
            oldRxFrameCount[mac][q]++;
            log_dbg_fyi("--- MAC%u rxFrame cb counted, q=%u\n", mac, q);
        }
        if (rxUsedRead[mac][q] > oldRxUsedRead[mac][q]) {
            oldRxUsedRead[mac][q]++;
            change = 1;
            log_dbg_fyi("--- MAC%u rxUsedRead cb counted, q=%u\n", mac, q);
        }
        if (rxOverrun[mac][q] > oldRxOverrun[mac][q]) {
            oldRxOverrun[mac][q]++;
            change = 1;
            log_dbg_fyi("--- MAC%u rxOverrun cb counted, q=%u\n", mac, q);
        }
        if (txFrComplete[mac][q] > oldTxFrComplete[mac][q]) {
            oldTxFrComplete[mac][q]++;
            change = 1;
            log_dbg_fyi("--- MAC%u txFrComplete cb counted, q=%u\n", mac, q);
        }
        if (txRetryExc[mac][q] > oldTxRetryExc[mac][q]) {
            oldTxRetryExc[mac][q]++;
            change = 1;
            log_dbg_fyi("--- MAC%u txRetryExc cb counted, q=%u\n", mac, q);
        }
        if (txFrCorr[mac][q] > oldTxFrCorr[mac][q]) {
            oldTxFrCorr[mac][q]++;
            change = 1;
            log_dbg_fyi("--- MAC%u txFrCorr cb counted, q=%u\n", mac, q);
        }
        if (hrespNotOk[mac][q] > oldHrespNotOk[mac][q]) {
            oldHrespNotOk[mac][q]++;
            change = 1;
            log_dbg_fyi("--- MAC%u hresp not OK cb counted, q=%u\n", mac, q);
        }
    }
    return change;
}

void loopDelay(uint32_t loops)
{
    uint32_t j;
    for (j = 0; j < loops; j++) {
        /* small delay by read to a global var */
        CPS_UncachedRead32(regAddr(0,revision_reg));
    }
}

uint32_t compareRxDescFlags(uint8_t emacInst, uint8_t numQ, uint16_t index,
                            uint8_t used, uint8_t wrap, uint8_t sof, uint8_t eof)
{
    uint32_t wd0, wd1;
    CEDI_RxDesc*  descStartPerQ;

    descStartPerQ = (CEDI_RxDesc*) (((unsigned long)((privData[emacInst]->rxQueue[numQ].rxDescStart))) +
                                    (index * (privData[emacInst]->rxDescriptorSize[numQ])));
    wd0 = CPS_UncachedRead32((uint32_t *)
                             &(descStartPerQ->word[0]));

    wd1 = CPS_UncachedRead32((uint32_t *)
                             &(descStartPerQ->word[1]));

    if (used != ((wd0 & CEDI_RXD_USED) ? 1 : 0) || wrap != ((wd0 & CEDI_RXD_WRAP)   ? 1   : 0) ||
        sof != ((wd1 & CEDI_RXD_SOF) ? 1 : 0) || eof != ((wd1 & CEDI_RXD_EOF)   ? 1   : 0))
    {
        log_dbg_fyi("compareRxDescFlags(%u,%u,%u, exp- u:%u w:%u s:%u e:%u read- u:%u w:%u s:%u e:%u)\n",
                    emacInst, numQ, index, used, wrap, sof, eof,
                    (wd0 & CEDI_RXD_USED) ? 1 : 0, (wd0 & CEDI_RXD_WRAP)   ? 1   : 0,
                    (wd1 & CEDI_RXD_SOF) ? 1 : 0, (wd1 & CEDI_RXD_EOF)   ? 1   : 0);
        return CDN_EINVAL;
    }
    else{
        return CDN_EOK;
    }
}

uint32_t getRxDescBufAddr(uint8_t emacInst, uint8_t numQ, uint16_t index)
{
    CEDI_RxDesc* descStartPerQ =
        (CEDI_RxDesc*) (((unsigned long)((privData[emacInst]->rxQueue[numQ].rxDescStart))) +
                        (index * (privData[emacInst]->rxDescriptorSize[numQ])));

    uint32_t wd0 = CPS_UncachedRead32((uint32_t *) &(descStartPerQ->word[0]));

    return wd0 & CEDI_RXD_ADDR_MASK;
}

/* TODO: function should be refactored */
uint32_t txRxPollTestFrame(int emacTx, uint8_t *txDat, uint32_t txLen,
                           int emacRx, uint8_t *rxDat, uint32_t *rxLen,
                           CEDI_RxDescStat *rxdStat, uint32_t toutCount)
{
    uint32_t result, i, j, t = 0, qNum;
    int dataErr = 0;
    uint8_t txOk, rxOk;
    CEDI_BuffAddr txBuf;
    uint32_t copyLen, bufLen;
    CEDI_TxDescData txDescDat;
    CEDI_RxDescData rxDescDat;
    uint16_t rxBufs = 0, rxBufsExp = 0;
    uint32_t wMark, rDat;
    uint8_t enabled;
    CEDI_FrameSize maxTxFrSize;
    char PStr[40];

    qNum = 0;

    bufLen = txLen + 4;      /* add 4 for FCS */

    emacObj[emacTx]->calcMaxTxFrameSize(privData[emacTx], &maxTxFrSize);
    emacObj[emacTx]->getTxPartialStFwd(privData[emacTx], &wMark, &enabled);

    if ((bufLen > maxTxFrSize.FrameSize[qNum]) && (!enabled)) {
        log_dbg_fyi("***  Frame too long for Tx buffer in full store mode!\n");
        return 1004;
    }

    for (i = 0; i < bufLen + 4; i += rxBufLenBytes[qNum]) {
        rxBufsExp++;
    }

    /* round up txLen to multiple of 4 bytes for copying */
    copyLen = 4 * (txLen / 4 + ((txLen % 4)   ? 1   : 0));

    /* Allocate a buffer for tx frame and fill with pattern */
    result = allocBuffer(copyLen, 0xBADA5500, &txBuf);
    validateResult(CDN_EOK, "Allocating Tx buffer");

    /* copy in data (32-bit words) */
    for (i = 0; i < copyLen / sizeof(uint32_t); i++) {
        CPS_UncachedWrite32((uint32_t *)(txBuf.vAddr) + i, ((uint32_t *)txDat)[i]);
    }

    /* Queue frame for Tx, using auto-CRC */
    result = emacObj[emacTx]->queueTxBuf(privData[emacTx], qNum, &txBuf, txLen, CEDI_TXB_LAST_BUFF);
    validateResult(CDN_EOK, "QueueTxBuf() call failed");

    txOk = 0;
    rxOk = 0;

    /* now wait for tx frame complete & rx status to clear */
    for (t = toutCount; (!txOk || !rxOk) && t; --t) {

        result = emacObj[emacTx]->isr(privData[emacTx]);
        validateNResult(CDN_EINVAL, "Isr() call failed for MAC%u", emacTx);

        if (!txOk) {
            result = emacObj[emacTx]->freeTxDesc(privData[emacTx], 0, &txDescDat);
            validateResult(CDN_EOK, "FreeTxDesc() call failed");
            txOk = (txDescDat.status == CEDI_TXDATA_1ST_AND_LAST);
        }

        result = emacObj[emacRx]->isr(privData[emacRx]);
        validateNResult(CDN_EINVAL, "Isr() call failed for MAC%u", emacRx);

        if (!rxOk)
        {
            /* if numRxUsed then call readRxBuf */
            if (emacObj[emacRx]->numRxUsed(privData[emacRx], qNum))
            {
                result = emacObj[emacRx]->readRxBuf(privData[emacRx], 0, &nBuf[qNum][newIndex[qNum]], 0, &rxDescDat);
                validateResult(CDN_EOK, "ReadRxBuf() call failed");

                if (rxDescDat.status != CEDI_RXDATA_NODATA) {    /* data was read */
                    if (rxBufsExp == 1) {
                        rxOk = 1;
                        validateUint(rxDescDat.status, CEDI_RXDATA_SOF_EOF, "readRxBuf single buffer", "status");
                    } else if (rxBufs == 0) {
                        validateUint(rxDescDat.status, CEDI_RXDATA_SOF_ONLY, "readRxBuf first buffer", "status");
                    } else if (rxBufs < (rxBufsExp - 1)) {
                        validateUint(rxDescDat.status, CEDI_RXDATA_NO_FLAG, "readRxBuf middle buffer", "status");
                    } else {
                        rxOk = 1;
                        validateUint(rxDescDat.status, CEDI_RXDATA_EOF_ONLY, "readRxBuf last buffer", "status");
                    }

                    /* update descriptor reference for checking freed buffers */
                    rxBufs++;
                    newIndex[qNum] = (newIndex[qNum] + 1) % privData[emacRx]->cfg.rxQLen[qNum];

                    /* Allocate another buffer to swap in */
                    result = allocBuffer(rxBufLenBytes[qNum], 0xABCD0000, &nBuf[qNum][newIndex[qNum]]);
                    validateResult(CDN_EOK, "Allocating new Rx buffer [%u][%u]", qNum, newIndex[qNum]);
                    validateNUint(rxBufs, MAX_TEST_RBQ_LENGTH, "Not enough Rx descriptors for q%u", qNum);
                }
            }
        }

        sprintf(PStr, "Unexpected MAC%u callback detected", emacTx);
        validateNUint(detectCallback(emacTx), 1, PStr, "value");

        sprintf(PStr, "Unexpected MAC%u callback detected", emacRx);
        validateNUint(detectCallback(emacRx), 1, PStr, "value");
    }

    validateTxRxTimeout(t, txOk, rxOk);
    log_dbg_fyi("Timeout count reached %u\n", t);

    emacObj[emacRx]->getRxDescStat(privData[emacRx], rxDescDat.rxDescStat, rxdStat);
    *rxLen = rxdStat->bufLen;

    /* transfer back from Rx buffer(s) */
    j = oldIndex[qNum]; /* buffer count */
    i = 0; /* byte count */
    while (i < (*rxLen)) {
        rDat = CPS_UncachedRead32((uint32_t *)(nBuf[qNum][j].vAddr) + (i % rxBufLenBytes[qNum]) / sizeof(uint32_t));
        rxDat[i++] = rDat & 0x000000FF;
        if (i < *rxLen) {
            rxDat[i++] = (rDat & 0x0000FF00) >> 8;
        }

        if (i < *rxLen) {
            rxDat[i++] = (rDat & 0x00FF0000) >> 16;
        }

        if (i < *rxLen) {
            rxDat[i++] = (rDat & 0xFF000000) >> 24;
        }

        if ((i % rxBufLenBytes[qNum]) == 0) {
            j = (j + 1) % privData[emacRx]->cfg.rxQLen[qNum];
        }
    }

    /* compare rx with tx */
    for (i = 0; (i < txLen); i++) {
        sprintf(PStr, "Rx data\[\%u]", i);
        compareXint(rxDat[i], txDat[i], PStr, "read");
        if (!dataErr && (passed != TEST_SUCCESS)) {
            dataErr = 1;
        }
    }

done:
    /* free Tx buffer */
    NCPS_freeHWMem((uint32_t)txBuf.vAddr);

    /* free Rx buffers except initial spare one */
    for (; oldIndex[qNum] != newIndex[qNum]; ) {
        NCPS_freeHWMem((uint32_t)nBuf[qNum][oldIndex[qNum]].vAddr);
        oldIndex[qNum] = (oldIndex[qNum] + 1) % privData[emacRx]->cfg.rxQLen[qNum];
    }

    if (t == 0) {
        return 1002;
    }
    else if (dataErr) {
        return 1005;
    }
    else{
        return passed;
    }
}

uint32_t prepareTxRx(uint8_t emacTx, uint8_t emacRx)
{
    uint32_t result, i, qNum;

    zeroCallbackCounters();

    /* prepare Rx */
    for (qNum = 0; qNum < privData[emacRx]->cfg.rxQs; qNum++) {

        rxBufLenBytes[qNum] = privData[emacRx]->cfg.rxBufLength[qNum] << 6;

        for (i = 0; i < privData[emacRx]->cfg.rxQLen[qNum]; i++) {
            /* Allocate some buffers */
            if (0 != allocBuffer(rxBufLenBytes[qNum], 0xFAFA0000, &aBuf[qNum][i])) {
                log_dbg_fyi("Error allocating Rx buffer\[\%u]\n", i);
                return 1001;
            }

            if (CDN_EOK != (result = emacObj[emacRx]->addRxBuf(privData[emacRx], qNum, &aBuf[qNum][i], 0)))
            {
                log_dbg_fyi("error in AddRxBuf call: returned %u\n", result);
                return 1001;
            }
        }
        /* oldIndex is first swap-in (or "new") buffer in nBuf array */
        oldIndex[qNum] = 0;
        /* newIndex is where to add new buffer in nBuf[] */
        newIndex[qNum] = oldIndex[qNum];

        /* Allocate a spare buffer to swap in */
        if (0 != allocBuffer(rxBufLenBytes[qNum], 0xABCD0000, &nBuf[qNum][newIndex[qNum]])) {
            log_dbg_fyi("Error allocating new Rx buffer\[\%u]\[\%u]\n", qNum, newIndex[qNum]);
            return 1001;
        }
    }

    /* start Rx MAC + enable Rx & Tx */
    emacObj[emacRx]->start(privData[emacRx]);
    emacObj[emacRx]->enableRx(privData[emacRx]);
    emacObj[emacRx]->enableTx(privData[emacRx]);

    /* prepare Tx */
    emacObj[emacTx]->start(privData[emacTx]);
    emacObj[emacTx]->enableTx(privData[emacTx]);

    return CDN_EOK;
}

void freeBuffersStopTxRx(uint8_t emacTx, uint8_t emacRx)
{
    uint32_t result, i, qNum;
    uint16_t nBufs;
    CEDI_BuffAddr freeBuf;

    if ((emacObj[emacTx] != NULL) && (privData[emacTx] != NULL)) {
        emacObj[emacTx]->stop(privData[emacTx]);
    }

    if (privData[emacRx] != NULL) {
        if (emacObj[emacRx] != NULL) {
            emacObj[emacRx]->stop(privData[emacRx]);
        }

        /* Free Rx buffers */
        for (qNum = 0; qNum < privData[emacRx]->cfg.rxQs; qNum++) {
            result = CDN_EOK;

            if (emacObj[emacRx] != NULL) {
                emacObj[emacRx]->numRxBufs(privData[emacRx], qNum, &nBufs);
                for (i = nBufs - 1; result != CDN_ENOENT; i--) {
                    /* buffers in descriptor list */
                    result = emacObj[emacRx]->removeRxBuf(privData[emacRx], qNum, &freeBuf);
                    if (result == CDN_EOK) {
                        if (0 == NCPS_freeHWMem((uint32_t)freeBuf.vAddr)) {
                            log_dbg_fyi("Error freeing Rx buffer\[\%u]\[\%u]\n", qNum, i);
                        }
                    }
                    else if (result != CDN_ENOENT) {
                        log_dbg_fyi("Error from removeRxBuf call- result = %u\n", result);
                    }
                }
                /* swapped-out or spare Rx buffers */
                while (oldIndex[qNum] != newIndex[qNum]) {
                    if (0 == NCPS_freeHWMem((uint32_t)nBuf[qNum][oldIndex[qNum]].vAddr)) {
                        log_dbg_fyi("Error freeing unused Rx buffer nBuf\[\%u]\[\%u]\n", qNum, oldIndex[qNum]);
                    }
                    oldIndex[qNum] = (oldIndex[qNum] + 1) % privData[emacRx]->cfg.rxQLen[qNum];
                }
                if (0 == NCPS_freeHWMem((uint32_t)nBuf[qNum][oldIndex[qNum]].vAddr)) {
                    log_dbg_fyi("Error freeing spare Rx buffer nBuf\[\%u]\[\%u]\n", qNum, oldIndex[qNum]);
                }

                emacObj[emacRx]->resetRxQ(privData[emacRx], qNum, 0);
            }
        }

        if ((emacObj[emacTx] != NULL) && (privData[emacTx] != NULL)) {
            for (qNum = 0; qNum < privData[emacTx]->cfg.txQs; qNum++) {
                emacObj[emacTx]->resetTxQ(privData[emacTx], qNum);
            }
        }
    }
}

uint32_t txRxEventTestFrame(uint8_t emacTx, uint8_t *txDat, uint32_t txLen, uint8_t autoCrc,
                            uint8_t emacRx, uint8_t *rxDat, uint32_t *rxLen,
                            CEDI_RxDescStat *rxdStat, uint16_t *rxBufsExp)
{
    uint32_t result, i, j, t;
    int timeout = 0;
    int txOverFlow = 0;
    int passed = TEST_SUCCESS;
    uint8_t txOk, rxOk, enabled;
    CEDI_BuffAddr txBuf;
    uint32_t copyLen, bufLen;
    uint16_t rxBufs = 0;
    uint32_t rDat;
    CEDI_TxDescData txDescDat;
    CEDI_RxDescData rxDescDat;
    uint8_t txQNum, rxQNum;
    CEDI_FrameSize maxTxFrSize;
    char PStr[40];

    if (0 != emacObj[emacRx]->getFcsRemove(privData[emacRx], &enabled)) {
        return 1000;
    }

    if (!enabled) {
        bufLen = txLen + (autoCrc  ? 4  : 0);      /* add 4 for FCS */
    }
    else{
        bufLen = txLen;
    }

    emacObj[emacTx]->calcMaxTxFrameSize(privData[emacTx], &maxTxFrSize);
    txQNum = 0;

    rxQNum = 0;
    *rxBufsExp = 0;
    for (i = 0; i < bufLen; i += rxBufLenBytes[rxQNum]) {
        (*rxBufsExp)++;
    }

    /* round up txLen to multiple of 4 bytes for copying */
    copyLen = 4 * (txLen / 4 + ((txLen % 4)  ? 1  : 0));

    /* Allocate a buffer for tx frame and fill with pattern */
    if (0 != allocBuffer(copyLen, 0xBADA5500, &txBuf)) {
        log_dbg_fyi("***  Error allocating Tx buffer\n");
        return 1001;
    }

    /* copy in data (32-bit words) */
    for (i = 0; i < copyLen / sizeof(uint32_t); i++) {
        CPS_UncachedWrite32((uint32_t *)(txBuf.vAddr) + i, ((uint32_t *)txDat)[i]);
    }

    /* Queue frame for Tx, using auto-CRC if requested */
    result = emacObj[emacTx]->queueTxBuf(privData[emacTx], txQNum, &txBuf, txLen,
                                         CEDI_TXB_LAST_BUFF | (autoCrc  ? 0  : CEDI_TXB_NO_AUTO_CRC));

    printTxDescList(privData[emacTx], txQNum);

    if (0 != result) {
        log_dbg_fyi("***  queueTxBuf(): Invalid return value: %d\n", result);
        passed = TEST_FAILED;
        /* report error due to oversized frame length */
        if (txLen > CEDI_TXD_LMASK) {
            txOverFlow = 1;
        }
        goto done;
    }

    txOk = 0;
    rxOk = 0;

    /* now wait for tx frame complete & rx status to clear */
    for (t = 3000; (!txOk || !rxOk) && t; --t) {
        if ((t % 100) == 0) {
            log_simple_fyi("counter left = %d\n", t);
        }
        Idle();

        if (!txOk) {
            emacObj[emacTx]->isr(privData[emacTx]);

            if (txFrComplete[emacTx][txQNum] > oldTxFrComplete[emacTx][txQNum]) {
                txOk = 1;

                oldTxFrComplete[emacTx][txQNum]++;
            }

            if (txUsedRead[emacTx] > oldTxUsedRead[emacTx]) {
                oldTxUsedRead[emacTx]++;
            }
        }

        if (!rxOk)
        {
            emacObj[emacRx]->isr(privData[emacRx]);

            /* check for rxFrame callback */
            if (rxFrameCount[emacRx][rxQNum] > oldRxFrameCount[emacRx][rxQNum]) {

                /* now loop until numRxUsed reads 0 */
                while (emacObj[emacRx]->numRxUsed(privData[emacRx], rxQNum)) {
                    if (CDN_EOK != (result = emacObj[emacRx]->readRxBuf(privData[emacRx], rxQNum,
                                                                        &nBuf[rxQNum][newIndex[rxQNum]], 0, &rxDescDat))) {
                        log_dbg_fyi("***  Error readRxBuf returned %u\n", result);
                        passed = TEST_FAILED;
                        goto done;
                    }
                    if (rxDescDat.status != CEDI_RXDATA_NODATA) {    /* data was read */
                        if (*rxBufsExp == 1) {  /* be careful with if..elses using validate... macros ! */
                            validateUint(rxDescDat.status, CEDI_RXDATA_SOF_EOF, "readRxBuf single buffer", "status");
                        }
                        else if (rxBufs == 0) {
                            validateUint(rxDescDat.status, CEDI_RXDATA_SOF_ONLY, "readRxBuf first buffer", "status");
                        } else if (rxBufs < (*rxBufsExp - 1)) {
                            validateUint(rxDescDat.status, CEDI_RXDATA_NO_FLAG, "readRxBuf middle buffer", "status");
                        } else {
                            validateUint(rxDescDat.status, CEDI_RXDATA_EOF_ONLY, "readRxBuf last buffer", "status");
                        }

                        rxBufs++;
                        newIndex[rxQNum] = (newIndex[rxQNum] + 1) % privData[emacRx]->cfg.rxQLen[rxQNum];

                        /* Allocate another buffer to swap in */
                        if (0 != allocBuffer(rxBufLenBytes[rxQNum], 0xABCD0000, &nBuf[rxQNum][newIndex[rxQNum]])) {
                            log_dbg_fyi("***  Error allocating new Rx buffer\[\%u]\n", rxQNum);
                            passed = TEST_FAILED;
                            goto done;
                        }

                        if (rxBufs == MAX_TEST_RBQ_LENGTH) {
                            log_dbg_fyi("***  Not enough Rx descriptors!!!\n", rxQNum);
                            passed = TEST_FAILED;
                            goto done;
                        }
                    }

                }
                rxOk = rxFrameCount[emacRx][rxQNum];
                oldRxFrameCount[emacRx][rxQNum]++;
            }
        }

        /* handle case of Tx buffer too small - leads to Frame Corruption errors */
        if (txFrCorr[emacTx][txQNum] > oldTxFrCorr[emacTx][txQNum]) {
            log_dbg_fyi("**** Tx Frame corrupted, too large for buffer ****\n", emacTx);
            oldTxFrCorr[emacTx][txQNum]++;
            passed = TEST_FAILED;
            txOverFlow = 1;
            goto done;
        }

        if (detectCallback(emacTx)) {
            log_dbg_fyi("**** Error - Unexpected MAC%u callback detected ****\n", emacTx);
            passed = TEST_FAILED;
            goto done;
        }
        if (detectCallback(emacRx)) {
            log_dbg_fyi("**** Error - Unexpected MAC%u callback detected ****\n", emacRx);
            passed = TEST_FAILED;
            goto done;
        }
    }
    printRxDescList(privData[emacRx], rxQNum);

    if (CDN_EOK != (result = emacObj[emacTx]->freeTxDesc(privData[emacTx], txQNum, &txDescDat))) {
        log_dbg_fyi("Error freeing Tx descriptor: returned %u\n", result);
    }

    if (!t) {
        if (txOk && !rxOk) {
            log_dbg_fyi("***  Receive timed out.\n");
            timeout = 1;
        }
        else if (!rxOk && !txOk) {
            log_dbg_fyi("***  Transmit timed out.\n");
            timeout = 2;
        }
        else {
            log_dbg_fyi("***  Timeout - Transmit not detected! (Rx OK)\n");
            timeout = 3;
        }
        goto done;
    }
    log_dbg_fyi("timeout count reached %u\n", t);

    emacObj[emacRx]->getRxDescStat(privData[emacRx], rxDescDat.rxDescStat, rxdStat);
    *rxLen = rxdStat->bufLen;

    /* transfer back from Rx buffer(s) */
    j = oldIndex[rxQNum]; /* buffer index */
    i = 0; /* byte count */
    while (i < (*rxLen)) {
        rDat = CPS_UncachedRead32((uint32_t *)(nBuf[rxQNum][j].vAddr) + (i % rxBufLenBytes[rxQNum]) / sizeof(uint32_t));
        rxDat[i++] = rDat & 0x000000FF;
        if (i < *rxLen) {rxDat[i++] = (rDat & 0x0000FF00) >> 8;}
        if (i < *rxLen) {rxDat[i++] = (rDat & 0x00FF0000) >> 16;}
        if (i < *rxLen) {rxDat[i++] = (rDat & 0xFF000000) >> 24;}
        if ((i % rxBufLenBytes[rxQNum]) == 0) {
            j = (j + 1) % privData[emacRx]->cfg.rxQLen[rxQNum];
        }
    }

    /* compare rx with tx */
    j = 0;
    for (i = 0; (i < txLen) && (j < 20); i++) {   /* limit number of errors reported */
        sprintf(PStr, "Rx data\[\%u]", i);
        validateXint(rxDat[i], txDat[i], PStr, "read");
        if (rxDat[i] != txDat[i]) {j++;}
    }
    if (i < txLen) {
        log_dbg_fyi("%s", "----- Data mismatch reports limited to max. of 20 -----\n");
    }

done:
    /* free Tx buffer */
    if (txBuf.vAddr) {
        if (txBuf.vAddr != (result = NCPS_freeHWMem((uint32_t)txBuf.vAddr))) {
            log_dbg_fyi("***  Error freeing Tx data buffer: returned %08X\n", result);
        }
    }
    /* free Rx buffers except initial spare one */
    for (; oldIndex[rxQNum] != newIndex[rxQNum]; ) {
        if (0 == NCPS_freeHWMem((uint32_t)nBuf[rxQNum][oldIndex[rxQNum]].vAddr)) {
            log_dbg_fyi("***  Error freeing Rx buffer nBuf\[\%u]\[\%u]\n", rxQNum, oldIndex[rxQNum]);
        }
        oldIndex[rxQNum] = (oldIndex[rxQNum] + 1) % privData[emacRx]->cfg.rxQLen[rxQNum];
    }

    if (timeout == 1) { /* Rx timeout */
        return RX_TIMEOUT;
    }
    else if (timeout == 2) { /* Tx (& Rx) timeout */
        return TX_TIMEOUT;
    }
    else if (timeout == 3) { /* Timeout - tx not detected */
        return TX_TIMEOUT_RX_OK;
    }
    else if (txOverFlow) {
        return TX_OVERFLOW;
    }
    else{
        return passed;
    }
}

void Idle(void)
{
#ifdef CSP
    uint32_t reg;

    if ((emacObj[0] == NULL) || (privData[0] == NULL)) {
        return;
    }

    emacObj[0]->readReg(privData[0], 0xFC, &reg);
#endif
}

uint32_t doTxAndValidate(const int emacA, const int emacB, uint32_t numQs,uint32_t txLen)
{
    uint32_t result, i, t, qNum = 0;
    uint8_t txOk, rxOk;
    CEDI_BuffAddr txBuf;
    CEDI_BuffAddr tmpBuf;
    CEDI_TxDescData txDescDat;
    CEDI_RxDescData rxDescDat;
    ethHdr_t header1;
    char PStr[40];

    CEDI_MacAddress emacAddr1 = { {100, 0, 1,   2, 3, 4} };
    CEDI_MacAddress emacAddr2 = { {100, 0, 200, 2, 3, 4} };

    result = prepareTxRx(emacA, emacB);
    validateResult(CDN_EOK, "preaparing Rx descriptor buffers");

    /* disable Tx complete & used read, and Rx complete events */
    emacObj[emacA]->setEventEnable(privData[emacA], (CEDI_EV_TX_COMPLETE | CEDI_EV_TX_USED_READ), 0, CEDI_ALL_QUEUES);
    emacObj[emacB]->setEventEnable(privData[emacB], CEDI_EV_RX_COMPLETE, 0, CEDI_ALL_QUEUES);

    /* Allocate a buffer for tx frame and fill with pattern */
    result = allocBuffer(txLen, 0xBADA5500, &txBuf);
    validateResult(CDN_EOK, "Allocating Tx buffer");

    /* set up frame header */
    memset(&header1, 0, sizeof(ethHdr_t));
    memcpy(&header1.dest, &emacAddr2, sizeof(CEDI_MacAddress));
    memcpy(&header1.srce, &emacAddr1, sizeof(CEDI_MacAddress));
    header1.typeLenMsb = 0x08;
    header1.typeLenLsb = 0x00;

    /* copy into data buffer (16-bit words) */
    for (i = 0; i < sizeof(ethHdr_t) / sizeof(uint16_t); i++) {
        CPS_UncachedWrite16((uint16_t *)(txBuf.vAddr) + i, ((uint16_t *)&header1)[i]);
    }

    /* set up specific address to match frame */
    emacObj[emacB]->setSpecificAddr(privData[emacB], 1, &emacAddr2, 0, 0);

    for (qNum = 0; qNum < numQs; qNum++)
    {
        log_dbg_fyi("\n---  Sending frame on Q%u  ---\n\n", qNum);

        emacObj[emacB]->clearStats(privData[emacB]);

        /* Queue frame for Tx, using auto-CRC */
        result = emacObj[emacA]->queueTxBuf(privData[emacA], qNum, &txBuf, txLen, CEDI_TXB_LAST_BUFF);
        validateResult(CDN_EOK, "queueTxBuf()");

        txOk = 0;
        rxOk = 0;

        /* now wait for tx frame complete & rx status to clear */
        for (t = 300; (!txOk || !rxOk) && t; --t) {

            emacObj[emacA]->isr(privData[emacA]);

            if (txOk == 0) {
                result = emacObj[emacA]->freeTxDesc(privData[emacA], qNum, &txDescDat);
                validateNResult(CDN_EINVAL, "Freeing Tx descriptor");

                if (result == CDN_EOK) {
                    txOk = (txDescDat.status == CEDI_TXDATA_1ST_AND_LAST);
                }
            }

            emacObj[emacB]->isr(privData[emacB]);

            if (rxOk == 0)
            {
                /* if numRxUsed then call readRxBuf */
                if (emacObj[emacB]->numRxUsed(privData[emacB], 0) > 0)
                {
                    /* note new buf until we see if swap in */
                    tmpBuf.vAddr = nBuf[0][newIndex[0]].vAddr;
                    tmpBuf.pAddr = nBuf[0][newIndex[0]].pAddr;

                    result = emacObj[emacB]->readRxBuf(privData[emacB], 0,
                                                       &nBuf[0][newIndex[0]], 0, &rxDescDat);
                    validateResult(CDN_EOK, "ReadRxBuf()");

                    if (rxDescDat.status != CEDI_RXDATA_NODATA) {    /* data was read */
                        rxOk = 1;
                        /* update descriptor reference for checking freed buffers */
                        aBuf[0][newIndex[0]].vAddr = tmpBuf.vAddr;
                        aBuf[0][newIndex[0]].pAddr = tmpBuf.pAddr;
                        newIndex[0] = (newIndex[0] + 1) % privData[emacB]->cfg.rxQLen[0];

                        /* Allocate another buffer to swap in */
                        result = allocBuffer(rxBufLenBytes[0], 0xABCD0000, &nBuf[0][newIndex[0]]);
                        sprintf(PStr, "Allocating new Rx buffer(%u)(%u)", 0, newIndex[0]);
                        validateResult(CDN_EOK, PStr);
                    }
                }
            }
        }

        validateTxRxTimeout(t, txOk, rxOk);

done:
        /* free Rx buffers except initial spare one */
        for (; oldIndex[0] != newIndex[0]; ) {
            if (0 == NCPS_freeHWMem((uint32_t)nBuf[0][oldIndex[0]].vAddr)) {
                log_dbg_fyi("Error freeing Rx buffer nBuf(%u)(%u)\n", 0, oldIndex[0]);
            }
            oldIndex[0] = (oldIndex[0] + 1) % privData[emacB]->cfg.rxQLen[0];
        }

        /* Free Rx buffers and break test for another queue, if test for
           previous queue fail */
        if (passed != TEST_SUCCESS) {
            break;
        }
    }

    /* free Tx buffer */
    if (txBuf.vAddr) {
        if (txBuf.vAddr != NCPS_freeHWMem((uint32_t)txBuf.vAddr)) {
            log_dbg_fyi("Error freeing Tx data buffer: returned %08X\n");
        }
    }

    return result;
}

uint32_t sendAndValidateDSframes(const int emacA, const int emacB, uint8_t numQs )
{
    uint32_t result, i, j, t, tst, tDat;
    uint32_t txLen, rxLen;
    CEDI_TxDescData txDescDat;
    CEDI_RxDescData rxDescDat;
    CEDI_RxDescStat rxDStat;
    ethHdr_t header1;
    iPv4Hdr_t header2;
    CEDI_BuffAddr txBuf, tmpBuf;
    uint8_t qNum, rxOk, txOk;
    CEDI_T1Screen scrn1, scrnRd;

    char PStr[40];

    CEDI_MacAddress emacAddr1 = { {0x64, 0,    1,  2,  3,  4} };
    CEDI_MacAddress emacAddr2 = { {0x64, 0, 0xC8,  2,  3,  4} };

    uint16_t numDsTc = 10;

    int dstcMap[10][2] = {{ 1,  20},     /* map DSTC=20 to Q1 etc. */
                          { 2,  33},
                          { 3,  56},
                          { 4, 102},
                          { 5, 200},
                          { 6, 255},
                          { 7,  43},
                          { 0,   2},
                          { 4, 212},
                          { 2,  50}};
    /* array for validating results */
    int dstcRes[10][2];

    result = prepareTxRx(emacA, emacB);
    validateResult(CDN_EOK, "Preparing Rx descriptor buffers");

    /* Allocate buffer for tx frame */
    txLen = 100;
    result = allocBuffer(txLen, 0xABCDEF00, &txBuf);
    validateResult(CDN_EOK, "Allocating Tx buffer");

    /* set up specific address to match frame */
    emacObj[emacB]->setSpecificAddr(privData[emacB], 1, &emacAddr2, 0, 0);

    /* disable all events - using polling methods only */
    emacObj[emacA]->setEventEnable(privData[emacA], CEDI_EVSET_ALL_Q0_EVENTS, 0, CEDI_ALL_QUEUES);
    emacObj[emacB]->setEventEnable(privData[emacB], CEDI_EVSET_ALL_Q0_EVENTS, 0, CEDI_ALL_QUEUES);

    log_dbg_fyi("\n---  Setting Type1 screening registers to match DS values  ---\n\n");

    numDsTc = (privData[emacB]->hwCfg.num_type1_screeners > 10) ? 10 : privData[emacB]->hwCfg.num_type1_screeners;
    for (tst = 0; tst < numDsTc; tst++) {
        /* set up screening Type1 registers for each value to match  */
        /* limit qNum to available queues */
        if (dstcMap[tst][0] < 8) {
            dstcMap[tst][0] = dstcMap[tst][0] % numQs;
        }
        scrn1.qNum = dstcMap[tst][0];
        scrn1.dstcMatch = dstcMap[tst][1];
        scrn1.dstcEnable = 1;
        scrn1.udpPort = 0;
        scrn1.udpEnable = 0;

        if (scrn1.qNum == 8) {continue;}

        result = emacObj[emacB]->setType1ScreenReg(privData[emacB], tst, &scrn1);
        validateResult(CDN_EOK, "SetType1ScreenReg() enable call");

        /* read back settings - direct reads first (for some regs) */
        if (tst < 8) {
            switch (tst) {
            case 0: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_0)); break;
            case 1: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_1)); break;
            case 2: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_2)); break;
            case 3: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_3)); break;
            case 4: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_4)); break;
            case 5: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_5)); break;
            case 6: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_6)); break;
            case 7: result = CPS_UncachedRead32(regAddr(emacB, screening_type_1_register_7)); break;
            }

            sprintf(PStr, "ScreenerType1 reg %u", tst);
            compareUint((EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__READ(result)),
                         scrn1.qNum, PStr, "screenReg queueNum");
            compareUint((EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__READ(result)),
                         scrn1.dstcMatch, PStr, "screenReg DSTC match");
            compareUint((EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__READ(result)),
                         scrn1.dstcEnable, PStr, "screenReg DSTC enable");
            compareUint((EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__READ(result)),
                         scrn1.udpPort, PStr, "screenReg UDP Port match");
            validateUint((EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__READ(result)),
                         scrn1.udpEnable, PStr, "screenReg UDP match enable");
        }
        /* then using get function */
        result = emacObj[emacB]->getType1ScreenReg(privData[emacB], tst, &scrnRd);
        validateResult(CDN_EOK, "GetType1ScreenReg()");

        compareUint(scrnRd.qNum, scrn1.qNum, "screenReg queueNum", "read");
        compareUint(scrnRd.dstcMatch, scrn1.dstcMatch, "screenReg DSTC match", "read");
        compareUint(scrnRd.dstcEnable, scrn1.dstcEnable, "screenReg DSTC enable", "read");
        compareUint(scrnRd.udpPort, scrn1.udpPort, "screenReg UDP Port match", "read");
        validateUint(scrnRd.udpEnable, scrn1.udpEnable, "screenReg UDP Port match enable", "read");

        log_dbg_fyi("Screener Type1 reg %u will match DS=%u for queue %u\n", tst, scrnRd.dstcMatch, scrnRd.qNum);
    }

    /* set up frame header */
    memset(&header1, 0, sizeof(ethHdr_t));
    memcpy(&header1.dest, &emacAddr2, sizeof(CEDI_MacAddress));
    memcpy(&header1.srce, &emacAddr1, sizeof(CEDI_MacAddress));
    header1.typeLenMsb = 0x08;  /* IPv4 */
    header1.typeLenLsb = 0x00;

    log_dbg_fyi("\n---  Sending IP frames with various DS field values  ---\n\n");

    for (tst = 0; tst < numDsTc; tst++) {

        /* set up (some of) IPv4 header */
        memset(&header2, 0, sizeof(iPv4Hdr_t));
        header2.dsCp = dstcMap[tst][1];
        header2.ihlVers = 0x45;     /* IpV=4, 5-word (x32 bits) header */
        header2.flgsFragOffset = 0;  /* clear DF, MF & fragOffset - fragmented frames not
                                        supported for IP header decode */

        /* transfer into tx buffer */
        memcpy(txBuffer, &header1, sizeof(ethHdr_t));
        memcpy(&txBuffer[sizeof(ethHdr_t)], &header2, sizeof(iPv4Hdr_t));

        /* append some data - make sure total length is a multiple of 4 */
        for (i = sizeof(ethHdr_t) + sizeof(iPv4Hdr_t); i < txLen; i += 4) {
            txBuffer[i]   = (0xAABB0000 + i) & 0xFF;
            txBuffer[i + 1] = ((0xAABB0000 + i) >> 8) & 0xFF;
            txBuffer[i + 2] = ((0xAABB0000 + i) >> 16) & 0xFF;
            txBuffer[i + 3] = ((0xAABB0000 + i) >> 24) & 0xFF;
        }

        log_dbg_fyi("--------  Txing Frame with DS = %u\n", header2.dsCp);
        /* Queue frame for Tx */
        /* copy into data buffer (32-bit words) */
        for (j = 0; j < txLen / sizeof(uint32_t); j++) {
            CPS_UncachedWrite32((uint32_t *)(txBuf.vAddr) + j, ((uint32_t *)txBuffer)[j]);
        }

        result = emacObj[emacA]->queueTxBuf(privData[emacA], 0, &txBuf, txLen,
                                            CEDI_TXB_LAST_BUFF);
        validateResult(CDN_EOK, "queueTxBuf()");

        txOk = 0;
        rxOk = 0;

        for (t = 40000; (!rxOk) && t; --t) {

            if (!txOk) {
                Idle();
                result = emacObj[emacA]->freeTxDesc(privData[emacA], 0, &txDescDat);
                validateNResult(CDN_EINVAL, "Freeing Tx descriptor");
                txOk = (result == CDN_ENOENT);
            }

            if (!rxOk)
            {
                Idle();
                for (qNum = 0; qNum < numQs; qNum++) {
                    /* poll numRxUsed for all queues until read a frame */
                    if (emacObj[emacB]->numRxUsed(privData[emacB], qNum)) {
                        /* note new buf until we see if swap in */
                        tmpBuf.vAddr = nBuf[qNum][newIndex[qNum]].vAddr;
                        tmpBuf.pAddr = nBuf[qNum][newIndex[qNum]].pAddr;
                        printRxDescList( privData[emacB], qNum);

                        result = emacObj[emacB]->readRxBuf(privData[emacB], qNum,
                                                           &nBuf[qNum][newIndex[qNum]], 0, &rxDescDat);
                        validateResult(CDN_EOK, "ReadRxBuf()");

                        if (rxDescDat.status != CEDI_RXDATA_NODATA) {    /* data was read */
                            validateUint(rxDescDat.status, CEDI_RXDATA_SOF_EOF, "readRxBuf single buffer", "status");

                            aBuf[qNum][newIndex[qNum]].vAddr = tmpBuf.vAddr;
                            aBuf[qNum][newIndex[qNum]].pAddr = tmpBuf.pAddr;
                            newIndex[qNum] = (newIndex[qNum] + 1) % privData[emacB]->cfg.rxQLen[qNum];

                            /* Allocate another buffer to swap in */
                            result = allocBuffer(rxBufLenBytes[qNum], 0xABCD0000, &nBuf[qNum][newIndex[qNum]]);
                            validateResult(CDN_EOK, "Allocating new Rx buffer");

                            emacObj[emacB]->getRxDescStat(privData[emacB], rxDescDat.rxDescStat, &rxDStat);
                            rxLen = rxDStat.bufLen;

                            /* transfer back from Rx buffer(s) */
                            i = 0; /* byte count */
                            while (i < (rxLen)) {
                                tDat = CPS_UncachedRead32((uint32_t *)(nBuf[qNum][oldIndex[qNum]].vAddr) + i / sizeof(uint32_t));
                                rxBuffer[i++] = tDat & 0x000000FF;
                                rxBuffer[i++] = (tDat & 0x0000FF00) >> 8;
                                rxBuffer[i++] = (tDat & 0x00FF0000) >> 16;
                                rxBuffer[i++] = (tDat & 0xFF000000) >> 24;
                            }

                            memcpy(&header1, rxBuffer, sizeof(ethHdr_t));
                            memcpy(&header2, &rxBuffer[sizeof(ethHdr_t)], sizeof(iPv4Hdr_t));
                            log_dbg_fyi("Rx Frame header dest=%02X:%02X:%02X:%02X:%02X:%02X src=%02X:%02X:%02X:%02X:%02X:%02X typeLenMsb=%02X typeLenLsb=%02X\n",
                                        header1.dest.byte[0],header1.dest.byte[1],header1.dest.byte[2],header1.dest.byte[3],header1.dest.byte[4],header1.dest.byte[5],
                                        header1.srce.byte[0],header1.srce.byte[1],header1.srce.byte[2],header1.srce.byte[3],header1.srce.byte[4],header1.srce.byte[5],
                                        header1.typeLenMsb, header1.typeLenLsb);
                            log_dbg_fyi("Rx Frame IP header ihlVers=0x%02X  DSCP=0x%02X\n", header2.ihlVers, header2.dsCp);

                            log_dbg_fyi("--------  Frame received in Rx queue %u, with DS = %u\n", qNum, header2.dsCp);
                            dstcRes[tst][0] = qNum;
                            dstcRes[tst][1] = header2.dsCp;

                            /* free next Rx buffer */
                            if (0 == NCPS_freeHWMem((uint32_t)nBuf[qNum][oldIndex[qNum]].vAddr)) {
                                log_dbg_fyi("Error freeing Rx buffer nBuf\[\%u]\[\%u]\n", qNum, oldIndex[qNum]);
                            }
                            oldIndex[qNum] = (oldIndex[qNum] + 1) % privData[emacB]->cfg.rxQLen[qNum];

                            rxOk = 1;
                        }
                    }
                }
            }
        }

        validateTxRxTimeout(t, txOk, rxOk);
        log_dbg_fyi("timeout countdown reached %u.\n", t);

    }

    /* validate received frames */
    for (tst = 0; tst < numDsTc; tst++) {
        sprintf(PStr, "DS Match #%u", tst);
        compareUint(dstcRes[tst][0], dstcMap[tst][0], PStr, "qNum");
        validateUint(dstcRes[tst][1], dstcMap[tst][1], PStr, "DS");
    }

    /* free Tx buffer */
    if (txBuf.vAddr) {
        //        log_dbg_fyi("Freeing Tx data buffer:  virt=0x%08X phys=0x%08X\n", txBuf.vAddr, txBuf.pAddr);
        if (txBuf.vAddr != (result = NCPS_freeHWMem((uint32_t)txBuf.vAddr))) {
            log_dbg_fyi("Error freeing Tx data buffer: returned %08X\n", result);
        }
    }

    /* disable screener regs */
    for (tst = 0; tst < numDsTc; tst++) {
        /* set all fields back to 0  */
        scrn1.dstcEnable = 0;
        scrn1.udpEnable = 0;
        scrn1.qNum = 0;
        scrn1.dstcMatch = 0;
        scrn1.udpPort = 0;

        result = emacObj[emacB]->setType1ScreenReg(privData[emacB], tst, &scrn1);
        validateResult(CDN_EOK, "setType1ScreenReg() disable call");

        /* validate */
        result = emacObj[emacB]->getType1ScreenReg(privData[emacB], tst, &scrnRd);
        validateResult(CDN_EOK, "getType1ScreenReg() disable call");

        compareUint(scrnRd.dstcEnable, 0, "screenReg DSTC match enable cleared", "read");
        compareUint(scrnRd.udpEnable, 0, "screenReg UDP Port match enable cleared", "read");
        compareUint(scrnRd.qNum, 0, "screenReg Q Number cleared", "read");
        compareUint(scrnRd.dstcMatch, 0, "screenReg DSTC match value cleared", "read");
        validateUint(scrnRd.udpPort, 0, "screenReg UDP Port match value cleared", "read");
    }
    /* disable specific address */
    emacObj[emacB]->disableSpecAddr(privData[emacB], 1);

done:
    return result;

}

uint32_t setScrnT2Reg(const int emac, CEDI_MacAddress SrcAddr, uint8_t screenReg, uint8_t compReg, uint8_t queueNum)
{
    uint32_t result;
    CEDI_T2Screen scrn1 = {0}, scrnRd = {0};
    CEDI_T2Compare cmp0, cmp1, cmp2, cmpRd;

    /* offset from SOF for ethernet source address */
    cmp0.offsetPosition = CEDI_T2COMP_OFF_SOF;
    cmp0.offsetVal = 6;         /* in bytes */

    cmp0.compValue = (SrcAddr.byte[1] << 8) | SrcAddr.byte[0];  /* first 2 bytes of address */
    cmp0.compMask = 0xFFFF;     /* set 1s to compare bits */
    cmp0.disableMask = 0;

    result = emacObj[emac]->setType2CompareReg(privData[emac], compReg, &cmp0);
    validateResult(CDN_EOK, "setType2CompareReg enable reg%u", compReg);

    /* verify using get function */
    result = emacObj[emac]->getType2CompareReg(privData[emac], compReg, &cmpRd);
    validateResult(CDN_EOK, "getType2CompareReg enable reg%u", compReg);

    validateUint(cmpRd.offsetPosition, cmp0.offsetPosition, "compareReg0 offsetPosition", "read");
    validateUint(cmpRd.offsetVal, cmp0.offsetVal, "compareReg0 offsetVal", "read");
    validateUint(cmpRd.compMask, cmp0.compMask, "compareReg0 compMask", "read");
    validateUint(cmpRd.compValue, cmp0.compValue, "compareReg0 compValue", "read");

    cmp1.offsetPosition = CEDI_T2COMP_OFF_SOF;
    cmp1.offsetVal = 8;         /* in bytes */
    cmp1.compMask = 0xFFFF;     /* set 1s to compare bits */
    cmp1.compValue = (SrcAddr.byte[3] << 8) | SrcAddr.byte[2];  /* middle 2 bytes of address */
    cmp1.disableMask = 0;

    result = emacObj[emac]->setType2CompareReg(privData[emac], compReg + 1, &cmp1);
    validateResult(CDN_EOK, "setType2CompareReg enable reg%u", compReg + 1);

    /* verify using get function */
    result = emacObj[emac]->getType2CompareReg(privData[emac], compReg + 1, &cmpRd);
    validateResult(CDN_EOK, "getType2CompareReg enable reg%u", compReg + 1);

    validateUint(cmpRd.offsetPosition, cmp1.offsetPosition, "compareReg1 offsetPosition", "read");
    validateUint(cmpRd.offsetVal, cmp1.offsetVal, "compareReg1 offsetVal", "read");
    validateUint(cmpRd.compMask, cmp1.compMask, "compareReg1 compMask", "read");
    validateUint(cmpRd.compValue, cmp1.compValue, "compareReg1 compValue", "read");

    cmp2.offsetPosition = CEDI_T2COMP_OFF_SOF;
    cmp2.offsetVal = 10;         /* in bytes */
    cmp2.compMask = 0xFFFF;     /* set 1s to compare bits */
    cmp2.compValue = (SrcAddr.byte[5] << 8) | SrcAddr.byte[4];  /* last 2 bytes of address */
    cmp2.disableMask = 0;

    result = emacObj[emac]->setType2CompareReg(privData[emac], compReg + 2, &cmp2);
    validateResult(CDN_EOK, "setType2CompareReg enable reg%u", compReg + 2);

    /* verify using get function */
    result = emacObj[emac]->getType2CompareReg(privData[emac], compReg + 2, &cmpRd);
    validateResult(CDN_EOK, "getType2CompareReg enable reg%u", compReg + 2);

    validateUint(cmpRd.offsetPosition, cmp2.offsetPosition, "compareReg2 offsetPosition", "read");
    validateUint(cmpRd.offsetVal, cmp2.offsetVal, "compareReg2 offsetVal", "read");
    validateUint(cmpRd.compMask, cmp2.compMask, "compareReg2 compMask", "read");
    validateUint(cmpRd.compValue, cmp2.compValue, "compareReg2 compValue", "read");

    /* set up screening Type2 registers to match source addresses */
    scrn1.vlanEnable = 0;
    scrn1.eTypeEnable = 0;
    scrn1.compAEnable = 1;
    scrn1.compAIndex = compReg;
    scrn1.compBEnable = 1;
    scrn1.compBIndex = compReg + 1;
    scrn1.compCEnable = 1;
    scrn1.compCIndex = compReg + 2;
    scrn1.qNum = queueNum;

    result = emacObj[emac]->setType2ScreenReg(privData[emac], screenReg, &scrn1);
    validateResult(CDN_EOK, "setType2ScreenReg() enable reg%u", screenReg);

    result = emacObj[emac]->getType2ScreenReg(privData[emac], screenReg, &scrnRd);
    validateResult(CDN_EOK, "getType2ScreenReg() enable reg%u", screenReg);

    validateUint(scrnRd.qNum, scrn1.qNum, "screenReg queueNum", "read");
    validateUint(scrnRd.vlanEnable, scrn1.vlanEnable, "screenReg VLAN enable", "read");
    validateUint(scrnRd.eTypeEnable, scrn1.eTypeEnable, "screenReg ethType enable", "read");
    validateUint(scrnRd.compAEnable, scrn1.compAEnable, "screenReg CompA enable", "read");
    validateUint(scrnRd.compAIndex, scrn1.compAIndex, "screenReg CompA index", "read");
    validateUint(scrnRd.compBEnable, scrn1.compBEnable, "screenReg CompB enable", "read");
    validateUint(scrnRd.compBIndex, scrn1.compBIndex, "screenReg CompB index", "read");
    validateUint(scrnRd.compCEnable, scrn1.compCEnable, "screenReg CompC enable", "read");
    validateUint(scrnRd.compCIndex, scrn1.compCIndex, "screenReg CompC index", "read");

    log_dbg_fyi("Screener Type2 reg %u, will match %02X:%02X:%02X:%02X:%02X:%02X source address for queue=%u\n",
                screenReg, (cmp0.compValue & 0xFF), (cmp0.compValue & 0xFF00) >> 8,
                (cmp1.compValue & 0xFF), (cmp1.compValue & 0xFF00) >> 8,
                (cmp2.compValue & 0xFF), (cmp2.compValue & 0xFF00) >> 8, queueNum);

done:

    return result;
}

uint32_t checkResult(uint8_t expRxOk, uint8_t expTxOk, uint8_t rxOk, uint8_t txOk, uint32_t t)
{
    if (!t) {
        if (txOk && !rxOk) {
            if (expRxOk == 0) {
                log_dbg_crit("--------  Receive timed out as suspected\n");
            }
            else {
                log_dbg_crit("--------  Error receive timed out.\n");
                return 1;
            }

        }
        else if (!rxOk && !txOk) {
            if (expTxOk == 0) {
                log_dbg_crit("--------  Transmit timed out as suspected\n");
            } 
            else {
                log_dbg_crit("--------  Error transmit timed out.\n");
                return 1;
            }
        }
        else {
            log_dbg_crit("--------  Error timeout - Transmit not detected! (Rx OK)\n");
            return 1;
        }
    }
    else {
        if (rxOk && !expRxOk) {
            log_dbg_crit("--------  Error frame was received but receive timeout was expected\n");
            return 1;
        }
    }

    return 0;
}


void initTcpUdpHeader(tcpUdpParams_t *prm, uint8_t udpNotTcp, void *hdr) {

    udpHeader1_t *udpHdr;
    tcpHeader1_t *tcpHdr;

    if (udpNotTcp)
    {                       /* UDP */
        memset(hdr, 0, sizeof(udpHeader1_t));

        udpHdr = (udpHeader1_t *)hdr;
        memcpy(&udpHdr->dest, &prm->dstMac, sizeof(CEDI_MacAddress));
        memcpy(&udpHdr->srce, &prm->srcMac, sizeof(CEDI_MacAddress));
        udpHdr->typeLenMsb = 0x08;         /* IPv4 */
        udpHdr->typeLenLsb = 0x00;
        /* IP header */
        udpHdr->ihlVers = 0x45;           /* IPv4, min header len 5x32bits */
        udpHdr->frLengthMsb = byte1((sizeof(udpHeader1_t) - sizeof(ethHdr_t)) + prm->dataLen);
        udpHdr->frLengthLsb = byte0((sizeof(udpHeader1_t) - sizeof(ethHdr_t)) + prm->dataLen);
        udpHdr->idMsb = byte1(prm->id);
        udpHdr->idLsb = byte0(prm->id);
        udpHdr->flgsFrOffsMsb = 0;
        udpHdr->fragOffsLsb = 0;
        udpHdr->prot = 0x11;              /* UDP */
        memcpy(&udpHdr->srcIpAddr, &prm->srcIpAddr, sizeof(CEDI_IPv4Add));
        memcpy(&udpHdr->dstIpAddr, &prm->dstIpAddr, sizeof(CEDI_IPv4Add));
        /* UDP header */
        udpHdr->srcPortMsb = byte1(prm->srcPort);
        udpHdr->srcPortLsb = byte0(prm->srcPort);
        udpHdr->dstPortMsb = byte1(prm->dstPort);
        udpHdr->dstPortLsb = byte0(prm->dstPort);
        udpHdr->udpLengthMsb = byte1(prm->udpLength);
        udpHdr->udpLengthLsb = byte0(prm->udpLength);
        udpHdr->udpChksumMsb = byte1(prm->udpChksum);
        udpHdr->udpChksumLsb = byte0(prm->udpChksum);
    }
    else
    {                       /* TCP */
        memset(hdr, 0, sizeof(tcpHeader1_t));

        tcpHdr = (tcpHeader1_t *)hdr;
        memcpy(&tcpHdr->dest, &prm->dstMac, sizeof(CEDI_MacAddress));
        memcpy(&tcpHdr->srce, &prm->srcMac, sizeof(CEDI_MacAddress));
        tcpHdr->typeLenMsb = 0x08;         /* IPv4 */
        tcpHdr->typeLenLsb = 0x00;
        /* IP header */
        tcpHdr->ihlVers = 0x45;           /* IPv4, min header len 5x32bits */
        tcpHdr->frLengthMsb = byte1((sizeof(tcpHeader1_t) - sizeof(ethHdr_t)) + prm->dataLen);
        tcpHdr->frLengthLsb = byte0((sizeof(tcpHeader1_t) - sizeof(ethHdr_t)) + prm->dataLen);
        tcpHdr->idMsb = byte1(prm->id);
        tcpHdr->idLsb = byte0(prm->id);
        tcpHdr->flgsFrOffsMsb = 0;
        tcpHdr->fragOffsLsb = 0;
        tcpHdr->prot = 0x06;              /* TCP */
        memcpy(&tcpHdr->srcIpAddr, &prm->srcIpAddr, sizeof(CEDI_IPv4Add));
        memcpy(&tcpHdr->dstIpAddr, &prm->dstIpAddr, sizeof(CEDI_IPv4Add));
        /* TCP header */
        tcpHdr->srcPortMsb = byte1(prm->srcPort);
        tcpHdr->srcPortLsb = byte0(prm->srcPort);
        tcpHdr->dstPortMsb = byte1(prm->dstPort);
        tcpHdr->dstPortLsb = byte0(prm->dstPort);
        tcpHdr->seqNum.byte3 = byte3(prm->seqNum);  /* MSByte tx'd first */
        tcpHdr->seqNum.byte2 = byte2(prm->seqNum);
        tcpHdr->seqNum.byte1 = byte1(prm->seqNum);
        tcpHdr->seqNum.byte0 = byte0(prm->seqNum);
        tcpHdr->ackNum.byte3 = byte3(prm->ackNum);
        tcpHdr->ackNum.byte2 = byte2(prm->ackNum);
        tcpHdr->ackNum.byte1 = byte1(prm->ackNum);
        tcpHdr->ackNum.byte0 = byte0(prm->ackNum);
        tcpHdr->datOffsFlgsMsb = ((sizeof(tcpHeader1_t)-sizeof(ethHdr_t)
                                    -sizeof(iPv4Hdr_t))/sizeof(uint32_t))<<4 | byte1(prm->flags);
        tcpHdr->tcpFlagsLsb = byte0(prm->flags);
        tcpHdr->windowSizeMsb = byte1(prm->window);
        tcpHdr->windowSizeLsb = byte0(prm->window);
    }
}

uint32_t validateRxTcpFrame(char *tstFrStr, tcpHeader1_t *txTcpHdr, tcpHeader1_t *rxTcpHdr,
                            uint8_t skipSeqAckChksum, uint16_t txInd, uint16_t rxInd, uint16_t datLen) {
    char PStr[40];
    uint16_t i, j;

    /* compare ethernet/IP headers */
    for (i=0; i<6; i++) {
        sprintf(PStr, "MACdstadd byte #%u", i);
        compareUint(rxTcpHdr->dest.byte[i], txTcpHdr->dest.byte[i], tstFrStr, PStr);
    }

    for (i=0; i<6; i++) {
        sprintf(PStr, "MACsrcaddbyte #%u", i);
        compareUint(rxTcpHdr->srce.byte[i], txTcpHdr->srce.byte[i], tstFrStr, PStr);
    }

    compareXint(rxTcpHdr->typeLenMsb, txTcpHdr->typeLenMsb, tstFrStr, "typeLenMsb");
    compareXint(rxTcpHdr->typeLenLsb, txTcpHdr->typeLenLsb, tstFrStr, "typeLenLsb");
    compareXint(rxTcpHdr->ihlVers, txTcpHdr->ihlVers, tstFrStr, "ihlVers");
    compareXint(rxTcpHdr->dsCp, txTcpHdr->dsCp, tstFrStr, "dsCp");
    compareXint(rxTcpHdr->frLengthMsb, txTcpHdr->frLengthMsb, tstFrStr, "frLengthMsb");
    compareXint(rxTcpHdr->frLengthLsb, txTcpHdr->frLengthLsb, tstFrStr, "frLengthLsb");
    compareXint(rxTcpHdr->idMsb, txTcpHdr->idMsb, tstFrStr, "idMsb");
    compareXint(rxTcpHdr->idLsb, txTcpHdr->idLsb, tstFrStr, "idLsb");
    compareXint(rxTcpHdr->flgsFrOffsMsb, txTcpHdr->flgsFrOffsMsb, tstFrStr, "flgsFrOffsMsb");
    compareXint(rxTcpHdr->fragOffsLsb, txTcpHdr->fragOffsLsb, tstFrStr, "fragOffsLsb");
    compareXint(rxTcpHdr->ttL, txTcpHdr->ttL, tstFrStr, "ttL");
    compareXint(rxTcpHdr->prot, txTcpHdr->prot, tstFrStr, "prot");

    for (i=0; i<4; i++) {
        sprintf(PStr, "srcIpAdd byte #%u", i);
        compareUint(rxTcpHdr->srcIpAddr.byte[i], txTcpHdr->srcIpAddr.byte[i], tstFrStr, PStr);
    }

    for (i=0; i<4; i++) {
        sprintf(PStr, "dstIpAdd byte #%u", i);
        compareUint(rxTcpHdr->dstIpAddr.byte[i], txTcpHdr->dstIpAddr.byte[i], tstFrStr, PStr);
    }

    compareXint(rxTcpHdr->srcPortMsb, txTcpHdr->srcPortMsb, tstFrStr, "srcPortMsb");
    compareXint(rxTcpHdr->srcPortLsb, txTcpHdr->srcPortLsb, tstFrStr, "srcPortLsb");
    compareXint(rxTcpHdr->dstPortMsb, txTcpHdr->dstPortMsb, tstFrStr, "dstPortMsb");
    compareXint(rxTcpHdr->dstPortLsb, txTcpHdr->dstPortLsb, tstFrStr, "dstPortLsb");

    for (i=0; i<4; i++) {
        sprintf(PStr, "dstIpAdd byte #%u", i);
        compareUint(rxTcpHdr->dstIpAddr.byte[i], txTcpHdr->dstIpAddr.byte[i], tstFrStr, PStr);
    }

    if (!skipSeqAckChksum) {
        compareXint(word32val(rxTcpHdr->seqNum), word32val(txTcpHdr->seqNum), tstFrStr, "seqNum");
        compareXint(word32val(rxTcpHdr->ackNum), word32val(txTcpHdr->ackNum), tstFrStr, "ackNum");
    }

    compareXint(rxTcpHdr->datOffsFlgsMsb, txTcpHdr->datOffsFlgsMsb, tstFrStr, "datOffsFlgsMsb");
    compareXint(rxTcpHdr->tcpFlagsLsb, txTcpHdr->tcpFlagsLsb, tstFrStr, "tcpFlagsLsb");

    if (!skipSeqAckChksum) {
        compareXint(rxTcpHdr->windowSizeMsb, txTcpHdr->windowSizeMsb, tstFrStr, "windowSizeMsb");
        compareXint(rxTcpHdr->windowSizeLsb, txTcpHdr->windowSizeLsb, tstFrStr, "windowSizeLsb");
    }

    if (!skipSeqAckChksum) {
        compareXint(rxTcpHdr->tcpChksumMsb, txTcpHdr->tcpChksumMsb, tstFrStr, "tcpChksumMsb");
        compareXint(rxTcpHdr->tcpChksumLsb, txTcpHdr->tcpChksumLsb, tstFrStr, "tcpChksumLsb");
    }

    compareXint(rxTcpHdr->urgentPtrMsb, txTcpHdr->urgentPtrMsb, tstFrStr, "urgentPtrMsb");
    compareXint(rxTcpHdr->urgentPtrLsb, txTcpHdr->urgentPtrLsb, tstFrStr, "urgentPtrLsb");

    /* data validation */
    j = 0;
    for (i=rxInd; (i<datLen) && (j<20); i++) {   /* limit number of errors reported */
        sprintf(PStr, "Rx data(%u)", i);
        compareXint(rxBuffer[i], txBuffer[txInd], tstFrStr, PStr);
        if (rxBuffer[i]!=txBuffer[txInd]) j++;
        txInd++;
    }

    if (j==20)
        log_dbg_fyi("%s", "----- Data mismatch reports limited to max. of 20 -----\n");

    return (passed != TEST_SUCCESS);
}

uint32_t readOneRxBuf(int emacRx, uint8_t qNum, uint8_t *bufNum,
                      CEDI_RxDescStat *rxdStat, uint32_t *toutCount,
                      uint16_t *rxLen, uint8_t *rxDat)
{
    uint32_t result, i;
    uint32_t t;
    uint8_t rxOk = 0;
    CEDI_RxDescData rxDescDat;
    uint32_t rDat;

    printRxDescList(privData[emacRx], qNum);

    for (t = *toutCount; !rxOk && t; --t) {

        emacObj[emacRx]->isr(privData[emacRx]);

        if (!rxOk && (emacObj[emacRx]->numRxUsed(privData[emacRx], qNum)))
        {
            result = emacObj[emacRx]->readRxBuf(privData[emacRx], qNum,
                                                                    &nBuf[qNum][newIndex[qNum]], 0, &rxDescDat);
            validateResult(CDN_EOK, "readRxBuf() call failed");

            if (rxDescDat.status!=CEDI_RXDATA_NODATA) {    /* data was read */
                log_dbg_fyi("readRxBuf returned data in buffer: virt=0x%08X, phys=0x%08X\n",
                              nBuf[qNum][newIndex[qNum]].vAddr, nBuf[qNum][newIndex[qNum]].pAddr);
                if ((rxDescDat.status==CEDI_RXDATA_SOF_EOF) || (rxDescDat.status==CEDI_RXDATA_EOF_ONLY))
                    oldRxFrameCount[emacRx][qNum]++;

                rxOk = 1;
                (*bufNum)++;

                /* update descriptor reference for checking freed buffers */
                newIndex[qNum] = (newIndex[qNum]+1) % privData[emacRx]->cfg.rxQLen[qNum];

                /* Allocate another buffer to swap in */
                result = allocBuffer(rxBufLenBytes[qNum], 0xABCD0000, &nBuf[qNum][newIndex[qNum]]);
                validateResult(CDN_EOK, "Allocating new Rx buffer [%u][%u]", qNum, newIndex[qNum]);
            }
        }
    }

    *toutCount = t;

    if (rxOk) {
        i = 0;
        emacObj[emacRx]->getRxDescStat(privData[emacRx], rxDescDat.rxDescStat, rxdStat);
        /* Must have a "bufLen" for header buffer as well as data buffer */
        *rxLen = rxdStat->bufLen;
        log_dbg_fyi("Buffer rx len = %u\n", *rxLen);

        /* transfer data back from Rx buffer */
        while (i<(*rxLen)) {
            /* read word from j'th new data buffer at offset i */
            rDat = CPS_UncachedRead32((uint32_t *)(nBuf[qNum][oldIndex[qNum]].vAddr+(i%rxBufLenBytes[qNum])));
            rxDat[i++] = rDat & 0x000000FF;
            if (i<*rxLen) {
                rxDat[i++] = (rDat & 0x0000FF00)>>8;
            }
            if (i<*rxLen) {
                rxDat[i++] = (rDat & 0x00FF0000)>>16;
            }
            if (i<*rxLen) {
                rxDat[i++] = (rDat & 0xFF000000)>>24;
            }
        }

        log_dbg_fyi("Start of Rx buffer: %02X:%02X:%02X:%02X %02X:%02X:%02X:%02X %02X:%02X:%02X:%02X %02X:%02X:%02X:%02X\n"\
                      "                    %02X:%02X:%02X:%02X %02X:%02X:%02X:%02X %02X:%02X:%02X:%02X %02X:%02X:%02X:%02X\n",
                      rxDat[0], rxDat[1], rxDat[2], rxDat[3], rxDat[4], rxDat[5], rxDat[6], rxDat[7],
                      rxDat[8], rxDat[9], rxDat[10], rxDat[11], rxDat[12], rxDat[13], rxDat[14], rxDat[15],
                      rxDat[16], rxDat[17], rxDat[18], rxDat[19], rxDat[20], rxDat[21], rxDat[22], rxDat[23],
                      rxDat[24], rxDat[25], rxDat[26], rxDat[27], rxDat[28], rxDat[28], rxDat[30], rxDat[31]);
    }

    done:
    /* free new Rx buffer */
    for (; oldIndex[qNum]!=newIndex[qNum]; ) {
        NCPS_freeHWMem((uint32_t)nBuf[qNum][oldIndex[qNum]].vAddr);
        oldIndex[qNum] = (oldIndex[qNum]+1) % privData[emacRx]->cfg.rxQLen[qNum];
    }

    return rxOk;
}

void DoTxRxFrameWithEvents(int emacA, int emacB, uint32_t txLen,
                           uint8_t rxQ, int *passedPtr, uint8_t *rxOk, uint8_t *txOk,
                           uint32_t *timeout)
{
    uint32_t result, j, t;
    CEDI_BuffAddr txBuf, tmpBuf;
    CEDI_TxDescData txDescDat;
    CEDI_RxDescData rxDescDat;

    /* Allocate buffer for tx frame */
    result = allocBuffer(txLen, 0xABCDEF00, &txBuf);
    validateResult(0, "Error allocating Tx buffer\n");

    /* copy into data buffer (32-bit words) */
    for (j=0; j<txLen/sizeof(uint32_t); j++)
        CPS_UncachedWrite32((uint32_t *)(txBuf.vAddr)+j, ((uint32_t *)txBuffer)[j]);

    /* queue frame for Tx */
    result = emacObj[emacA]->queueTxBuf(privData[emacA], 0, &txBuf, txLen,
                                        CEDI_TXB_LAST_BUFF);
    validateResult(CDN_EOK, "queueTxBuf(): Invalid return value");

    /* add single isr calling to to prevent loss of interrupt
     * is because tests works in polling mode - polls interrupt register*/
    emacObj[emacA]->isr(privData[emacA]);
    emacObj[emacB]->isr(privData[emacB]);

    *txOk = 0;
    *rxOk = 0;

    for (t = 1000; (!*rxOk) && t; --t) {
        if (!*txOk) {
            emacObj[emacA]->isr(privData[emacA]);
            if (CDN_EINVAL==(result = emacObj[emacA]->freeTxDesc(privData[emacA], 0, &txDescDat)))
                log_dbg_crit("Error freeing Tx descriptor: returned %u\n", result);
            *txOk = (result==CDN_ENOENT);
        }

        if (!*rxOk)
        {
            emacObj[emacB]->isr(privData[emacB]);
            /* poll numRxUsed until read a frame */
            if (emacObj[emacB]->numRxUsed(privData[emacB], rxQ)) {
                /* note new buf until we see if swap in */
                tmpBuf.vAddr = nBuf[rxQ][newIndex[rxQ]].vAddr;
                tmpBuf.pAddr = nBuf[rxQ][newIndex[rxQ]].pAddr;
                printRxDescList(privData[emacB], rxQ);

                result = emacObj[emacB]->readRxBuf(privData[emacB], rxQ, &nBuf[rxQ][newIndex[rxQ]],
                        0, &rxDescDat);
                validateResult(CDN_EOK, "Error readRxBuf ");

                if (rxDescDat.status!=CEDI_RXDATA_NODATA) {    /* data was read */
                    validateUint(rxDescDat.status, CEDI_RXDATA_SOF_EOF, "readRxBuf single buffer", "status");

                    aBuf[rxQ][newIndex[rxQ]].vAddr = tmpBuf.vAddr;
                    aBuf[rxQ][newIndex[rxQ]].pAddr = tmpBuf.pAddr;
                    newIndex[rxQ] = (newIndex[rxQ]+1) % privData[emacB]->cfg.rxQLen[rxQ];

                    /* Allocate another buffer to swap in */
                    result = allocBuffer(rxBufLenBytes[rxQ], 0xABCD0000, &nBuf[rxQ][newIndex[rxQ]]);
                    validateResult(CDN_EOK, "Error allocating new Rx buffer\[\%u]\n", rxQ);

                    log_simple_crit("--------  Frame received in Rx queue %u\n", rxQ);

                    /* free next Rx buffer */
                    NCPS_freeHWMem((uint32_t)nBuf[rxQ][oldIndex[rxQ]].vAddr);
                    oldIndex[rxQ] = (oldIndex[rxQ]+1) % privData[emacB]->cfg.rxQLen[rxQ];

                    *rxOk = 1;
                }
            }
        }
        Idle();
    }

    *timeout = t;

done:
    *passedPtr = passed;
    /* free Tx buffer */
    if (txBuf.vAddr) {
        //        cInst->printf("Freeing Tx data buffer:  virt=0x%08X phys=0x%08X\n", txBuf.vAddr, txBuf.pAddr);
        NCPS_freeHWMem((uint32_t)txBuf.vAddr);
    }
}

uint32_t txRxFrameWithEvents(int emacA, int emacB, uint32_t txLen, uint8_t rxQ, int *passedPtr) {
    uint32_t t, retVal = CDN_EINVAL;
    uint8_t rxOk, txOk;

    DoTxRxFrameWithEvents(emacA, emacB, txLen, rxQ, passedPtr, &rxOk, &txOk, &t);

    if (!t) {
        if (txOk && !rxOk) {
            log_simple_crit("Receive timed out.\n");
        } else if (!rxOk && !txOk) {
            log_simple_crit("Transmit timed out.\n");
        } else {
            log_simple_crit("Timeout - Transmit not detected! (Rx OK)\n");
        }
        *passedPtr = TEST_FAILED;
    }
    else {
        log_simple_crit("timeout countdown reached %u.\n", t);
    }

    if (*passedPtr == TEST_SUCCESS)
        retVal = CDN_EOK;

    return retVal;
}

void DoTxRxFrames2(int macA, int macB, uint32_t txLen[],
                   uint8_t qNum, int *passedPtr, uint8_t *rxCount, uint8_t txCount,
                   uint32_t *timeout)
{
   // uint32_t result,j , t, rxLen;
    uint32_t result,j , t;
    CEDI_BuffAddr txBuf, tmpBuf;
    CEDI_TxDescData txDescDat;
    CEDI_RxDescData rxDescDat;
    uint8_t txOk = 0;
    CEDI_RxDescStat rxDStat;

    uint32_t maxTxLen = txLen[0];
    for(j = 0; j < txCount; j++){
        if (txLen[j] > maxTxLen)
            maxTxLen = txLen[j];
    }

    *rxCount = 0;
    /* Allocate buffer for tx frame */
    result = allocBuffer(maxTxLen, 0xABCDEF00, &txBuf);
    validateResult(CDN_EOK, "Allocating Tx buffer");

    /* copy into data buffer (32-bit words) */
    for (j=0; j<maxTxLen/sizeof(uint32_t); j++)
        CPS_UncachedWrite32((uint32_t *)(txBuf.vAddr)+j, ((uint32_t *)txBuffer)[j]);


    for (j = 0; j < txCount; j++){
        result = emacObj[macA]->queueTxBuf(privData[macA], 0, &txBuf, txLen[j],
                                           CEDI_TXB_LAST_BUFF|CEDI_TXB_NO_AUTO_START);
        validateResult(CDN_EOK, "queueTxBuf(): iteration 1, for queue %u", j);
    }

    emacObj[macA]->startTx(privData[macA]);

    for (t = 1000; ((*rxCount < txCount) || !txOk)  && t; --t){

        Idle();

        result = emacObj[macA]->isr(privData[macA]);
        validateNResult(CDN_EINVAL, "Isr() call failed for MAC%u", macA);
        if (!txOk) {
            result = emacObj[macA]->freeTxDesc(privData[macA], 0, &txDescDat);
            validateNResult(CDN_EINVAL, "FreeTxdesc() call failed");
            txOk = (result==CDN_ENOENT);
        }

        result = emacObj[macB]->isr(privData[macB]);
        validateNResult(CDN_EINVAL, "Isr() call failed for MAC%u", macB);
        if ((*rxCount < txCount) &txOk) {

            /* poll numRxUsed until read a frame */
            if (emacObj[macB]->numRxUsed(privData[macB], qNum)) {
                /* note new buf until we see if swap in */
                tmpBuf.vAddr = nBuf[qNum][newIndex[qNum]].vAddr;
                tmpBuf.pAddr = nBuf[qNum][newIndex[qNum]].pAddr;

                result = emacObj[macB]->readRxBuf(privData[macB], qNum, &nBuf[qNum][newIndex[qNum]],
                                                  0, &rxDescDat);
                validateResult(CDN_EOK, "ReadrxBuf() call failed");

                if (rxDescDat.status!=CEDI_RXDATA_NODATA) {    /* data was read */

                    aBuf[qNum][newIndex[qNum]].vAddr = tmpBuf.vAddr;
                    aBuf[qNum][newIndex[qNum]].pAddr = tmpBuf.pAddr;
                    newIndex[qNum] = (newIndex[qNum]+1) % privData[macB]->cfg.rxQLen[qNum];

                    /* Allocate another buffer to swap in */
                    result = allocBuffer(rxBufLenBytes[qNum], 0xABCD0000, &nBuf[qNum][newIndex[qNum]]);
                    validateResult(CDN_EOK, "Allocating new Rx buffer(%u)", qNum);

                    emacObj[macB]->getRxDescStat(privData[macB], rxDescDat.rxDescStat, &rxDStat);
                    //rxLen = rxDStat.bufLen;

                    NCPS_freeHWMem((uint32_t)nBuf[qNum][oldIndex[qNum]].vAddr);
                    oldIndex[qNum] = (oldIndex[qNum]+1) % privData[macB]->cfg.rxQLen[qNum];

                    (*rxCount)++;
                    //log_simple_fyi("Frame %u (length %u) received with countdown at %u.\n", *rxCount, rxLen, t);
                    j=0;
                }
            }
        }
    }

    if (*rxCount < txCount){
        int i;
        for (i = *rxCount; i < txCount; i++){
            log_simple_fyi("Frame %u (length %u) not received \n", i + 1, txLen[i] + 4);
        }
    }

    if (!txOk) {
        log_simple_crit("Transmit timed out.\n");
    }

    *timeout = t;

done:
    /* free Tx buffer */
   NCPS_freeHWMem((uint32_t)txBuf.vAddr);

}

void DoTxRxFrame(int emacA, int emacB, uint32_t txLen,
                 uint8_t rxQ, int *passedPtr, uint8_t *rxOk, uint8_t *txOk,
                 uint32_t *timeout)
{
    /* disable all events - using polling methods only */
    emacObj[emacA]->setEventEnable(privData[emacA], CEDI_EVSET_ALL_Q0_EVENTS, 0, CEDI_ALL_QUEUES);
    emacObj[emacB]->setEventEnable(privData[emacB], CEDI_EVSET_ALL_Q0_EVENTS, 0, CEDI_ALL_QUEUES);
    DoTxRxFrameWithEvents(emacA, emacB, txLen, rxQ, passedPtr, rxOk, txOk, timeout);
}

bool is2p5GSupported(uint8_t mac)
{

    return ((privData[mac]->hwCfg.moduleId == GEM_GXL_MODULE_ID_V2) ||
            (privData[mac]->hwCfg.moduleId == GEM_AUTO_MODULE_ID_V1) ||
            (privData[mac]->hwCfg.moduleId == GEM_10G_MODULE_ID_V0) ||
            (privData[mac]->hwCfg.moduleId == GEM_10G_MODULE_ID_V1));
}

