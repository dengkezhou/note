/******************************************************************************
 *
 * Copyright (C) 2014-2023 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * edd_tx.c
 * Ethernet DMA MAC Driver
 *
 * Tx-related functions source file
 *****************************************************************************/

#include <common.h>
#include <command.h>
#include <cache.h>

#include "cdn_stdint.h"
#include "cdn_errno.h"
#include "cdn_log.h"
#include "cdn_stdtypes.h"
#include "cps.h"
#include "cps_drv.h"
#include "emac_registers.h"

#include "cedi_if.h"
#include "cedi_priv.h"
#include "cedi_structs_if.h"
#include "cedi_sanity.h"
#include "edd_int.h"

/******************************************************************************
 * Register addresses tables
 *****************************************************************************/
volatile uint32_t* const transmitPtrReg[15] = {
    CEDI_RegOff(transmit_q1_ptr),
    CEDI_RegOff(transmit_q2_ptr),
    CEDI_RegOff(transmit_q3_ptr),
    CEDI_RegOff(transmit_q4_ptr),
    CEDI_RegOff(transmit_q5_ptr),
    CEDI_RegOff(transmit_q6_ptr),
    CEDI_RegOff(transmit_q7_ptr),
    CEDI_RegOff(transmit_q8_ptr),
    CEDI_RegOff(transmit_q9_ptr),
    CEDI_RegOff(transmit_q10_ptr),
    CEDI_RegOff(transmit_q11_ptr),
    CEDI_RegOff(transmit_q12_ptr),
    CEDI_RegOff(transmit_q13_ptr),
    CEDI_RegOff(transmit_q14_ptr),
    CEDI_RegOff(transmit_q15_ptr)
};
static volatile uint32_t* const enstStartTimeReg[8] = {
    CEDI_RegOff(enst_start_time_q8),
    CEDI_RegOff(enst_start_time_q9),
    CEDI_RegOff(enst_start_time_q10),
    CEDI_RegOff(enst_start_time_q11),
    CEDI_RegOff(enst_start_time_q12),
    CEDI_RegOff(enst_start_time_q13),
    CEDI_RegOff(enst_start_time_q14),
    CEDI_RegOff(enst_start_time_q15)
};

static volatile uint32_t* const enstOnTimeReg[8] = {
    CEDI_RegOff(enst_on_time_q8),
    CEDI_RegOff(enst_on_time_q9),
    CEDI_RegOff(enst_on_time_q10),
    CEDI_RegOff(enst_on_time_q11),
    CEDI_RegOff(enst_on_time_q12),
    CEDI_RegOff(enst_on_time_q13),
    CEDI_RegOff(enst_on_time_q14),
    CEDI_RegOff(enst_on_time_q15)
};

static volatile uint32_t* const enstOffTimeReg[8] = {
    CEDI_RegOff(enst_off_time_q8),
    CEDI_RegOff(enst_off_time_q9),
    CEDI_RegOff(enst_off_time_q10),
    CEDI_RegOff(enst_off_time_q11),
    CEDI_RegOff(enst_off_time_q12),
    CEDI_RegOff(enst_off_time_q13),
    CEDI_RegOff(enst_off_time_q14),
    CEDI_RegOff(enst_off_time_q15)
};

static volatile uint32_t* const txBuffThresholdCtrl[4] = {
        CEDI_RegOff(tx_descr_rd_buf_ctl_q03),
        CEDI_RegOff(tx_descr_rd_buf_ctl_q47),
        CEDI_RegOff(tx_descr_rd_buf_ctl_q8b),
        CEDI_RegOff(tx_descr_rd_buf_ctl_qcf),
};


/******************************************************************************
 * Private Driver functions
 *****************************************************************************/
/* Adds value of offset (which may be positive or negative) to Tx descriptor
 * pointer, in-place. Offset should have relatively small absolute value.
 * This function intentionally violates MISRA C rules, to allow pointer
 * casts and manipulations required for driver operation. */
static void moveTxDescAddr(CEDI_TxDesc **ptr, int32_t offset)
{
    *ptr = (CEDI_TxDesc *)(((uintptr_t)*ptr) + offset);
}


/* move descriptor pointer bd and virtual address pointer vp on to next in ring.
 * stat should be the status (word 1) of current descriptor */
static void inc_txbd(const CEDI_PrivateData *pD, uint32_t stat, CEDI_TxDesc **bd, uintptr_t **vp,
                        const CEDI_TxQueue *txQ, uint8_t queueNum) {
    if (0 != (stat & CEDI_TXD_WRAP)) {
        *bd = txQ->bdBase;
        *vp = txQ->vAddrList;
    } else {
        moveTxDescAddr(bd, pD->txDescriptorSize[queueNum]);
        ++(*vp);
    }
}

/* move descriptor and virtual address pointers back to previous in ring */
static void dec_txbd(const CEDI_PrivateData *pD, CEDI_TxDesc **bd, uintptr_t **vp,
        const CEDI_TxQueue *txQ, uint8_t queueNum) {
    if (*bd==txQ->bdBase) {
        moveTxDescAddr(bd, (txQ->descMax-1)*(pD->txDescriptorSize[queueNum]));
        *vp += (txQ->descMax-1);
    } else {
        moveTxDescAddr(bd, -(pD->txDescriptorSize[queueNum]));
        --(*vp);
    }
}


void setTxQueueDisableBit(CEDI_PrivateData *pD, uint8_t txQueue,
              uint8_t disable)
{
    if (txQueue > 0) {
        volatile uint32_t *regPtr = NULL;
        uint32_t regTmp;

        regPtr = transmitPtrReg[txQueue - 1];
        addRegBase(pD, &regPtr);
        regTmp = CPS_UncachedRead32(regPtr);
        EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__MODIFY(regTmp, disable);
        CPS_UncachedWrite32(regPtr, regTmp);
    }
}


static void txDescFree(const CEDI_PrivateData *pD, uint8_t queueNum, uint16_t *numFree)
{
    *numFree = pD->txQueue[queueNum].descFree;
}

/******************************************************************************
 * Public driver functions
 */

/******************************************************************************
 * Driver API functions
 *****************************************************************************/

uint32_t CEDI_CalcMaxTxFrameSize(CEDI_PrivateData *pD, CEDI_FrameSize *maxTxSize)
{
    uint32_t status;
    uint32_t i, watermark;
    uint16_t ram_word_size, ram_addr_bits, burst_len;
    uint16_t ram_size, num_segments, size_per_segment, tx_overhead;
    uint32_t num_segments_q[CEDI_MAX_TX_QUEUES];
    uint32_t frameSizeShift;
    uint8_t enabled = 0;

    status = CEDI_CalcMaxTxFrameSizeSF(pD, maxTxSize);

    if (CDN_EOK == status) {
        status = CEDI_GetTxPartialStFwd(pD, &watermark, &enabled);
    }

    if (CDN_EOK == status) {
        if ((!enabled) && pD->hwCfg.tx_pkt_buffer)
        {
            // What is word size of SRAM in bytes
            ram_word_size = (pD->hwCfg.tx_pbuf_data >> 1)+1;
            ram_addr_bits = pD->hwCfg.tx_pbuf_addr;

            ram_size = ram_addr_bits + ram_word_size + 1;
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "RAM size = %u\n", 1<<ram_size);

            // how many segments are there ?
            num_segments = pD->hwCfg.tx_pbuf_queue_segment_size;
            /* this is number of address lines used for segment selection,
             * e.g. if =3, there are 2^3 = 8 segments */
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Num segments = %u\n", 1<<num_segments);

            size_per_segment  = (ram_size - num_segments);
                                                      /* again, as a power of 2 */
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "RAM Size per segment = %u\n",
                    1<<size_per_segment);

            num_segments_q[0] = pD->hwCfg.tx_pbuf_num_segments_q0;
            num_segments_q[1] = pD->hwCfg.tx_pbuf_num_segments_q1;
            num_segments_q[2] = pD->hwCfg.tx_pbuf_num_segments_q2;
            num_segments_q[3] = pD->hwCfg.tx_pbuf_num_segments_q3;
            num_segments_q[4] = pD->hwCfg.tx_pbuf_num_segments_q4;
            num_segments_q[5] = pD->hwCfg.tx_pbuf_num_segments_q5;
            num_segments_q[6] = pD->hwCfg.tx_pbuf_num_segments_q6;
            num_segments_q[7] = pD->hwCfg.tx_pbuf_num_segments_q7;
            num_segments_q[8] = pD->hwCfg.tx_pbuf_num_segments_q8;
            num_segments_q[9] = pD->hwCfg.tx_pbuf_num_segments_q9;
            num_segments_q[10] = pD->hwCfg.tx_pbuf_num_segments_q10;
            num_segments_q[11] = pD->hwCfg.tx_pbuf_num_segments_q11;
            num_segments_q[12] = pD->hwCfg.tx_pbuf_num_segments_q12;
            num_segments_q[13] = pD->hwCfg.tx_pbuf_num_segments_q13;
            num_segments_q[14] = pD->hwCfg.tx_pbuf_num_segments_q14;
            num_segments_q[15] = pD->hwCfg.tx_pbuf_num_segments_q15;

            if (pD->hwCfg.moduleRev >= 0x0109){
        uint32_t status_;
                CEDI_SegmentsPerQueue cpq[CEDI_MAX_TX_QUEUES] = {0};
                status_ = DoGetSegAlloc(pD, cpq, pD->txQs);
        if (CDN_EOK == status_){
            for(i = 0; i < pD->txQs; i++){
            num_segments_q[i] = (uint32_t)cpq[i];
            }
            /* if feature is not supported it is not an error */
        } else  if (CDN_ENOTSUP != status_) {
            status = status_;
        }
        }

            if (CDN_EOK == status)
            {
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "number segments  Q0 = %u, Q1 = %u, Q2 = %u, Q3 = %u, \n",
                        num_segments_q[0], num_segments_q[1], num_segments_q[2],
                        num_segments_q[3]);
                vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "number segments  Q4 = %u, Q5 = %u, Q6 = %u, Q7 = %u, \n",
                        num_segments_q[4], num_segments_q[5], num_segments_q[6],
                        num_segments_q[7]);

                burst_len = EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__READ(
                                CPS_UncachedRead32(&(pD->regs->dma_config)));
                switch (burst_len) {
                    case CEDI_DMA_DBUR_LEN_8:
                        tx_overhead = ((pD->hwCfg.tx_pbuf_data << 5)/8)*26;
                        break;
                    case CEDI_DMA_DBUR_LEN_16:
                        tx_overhead = ((pD->hwCfg.tx_pbuf_data << 5)/8)*46;
                        break;
                    case CEDI_DMA_DBUR_LEN_1:
                    case CEDI_DMA_DBUR_LEN_4:
                    default:
                        tx_overhead = ((pD->hwCfg.tx_pbuf_data << 5)/8)*16;
                        break;
                }

                for (i=0; i<CEDI_MAX_TX_QUEUES; i++) {
                    if (i<pD->txQs) {
                        frameSizeShift = num_segments_q[i] + (uint32_t)size_per_segment;
                        if (frameSizeShift < 32) {
                            maxTxSize->FrameSize[i] = (1 << frameSizeShift) - tx_overhead;
                        } else {
                            status = CDN_EINVAL;
                        }
                        /* add in some extra overhead */
                        if (CDN_EOK == status) {
                            maxTxSize->FrameSize[i] = (maxTxSize->FrameSize[i]*9)/10;
                        }
                    } else {
                        maxTxSize->FrameSize[i] = 0;
                    }
                }
            }
        }
        else
        {
            for (i=0; i<CEDI_MAX_TX_QUEUES; i++) {
                if (i<pD->txQs) {
                    maxTxSize->FrameSize[i] = CEDI_TXD_LMASK;
                } else {
                    maxTxSize->FrameSize[i] = 0;
                }
            }
        }
    }

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "max_frm_size_Q0 = %u, Q1 = %u, Q2 = %u, Q3 = %u,\n",
                maxTxSize->FrameSize[0], maxTxSize->FrameSize[1],
                maxTxSize->FrameSize[2], maxTxSize->FrameSize[3]);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                "max_frm_size_Q4 = %u, Q5 = %u, Q6 = %u, Q7 = %u,\n",
                maxTxSize->FrameSize[4], maxTxSize->FrameSize[5],
                maxTxSize->FrameSize[6], maxTxSize->FrameSize[7]);
    }
    return status;
}

uint32_t CEDI_QueueTxBuf(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BuffAddr *bufAdd,
        uint32_t length, uint8_t flags)
{
    uint32_t status;
    CEDI_TxQueue *txQ;
    CEDI_TxDesc *freeDesc;
    CEDI_TxDesc *bd1stBuf;
    uint32_t stat, ncr;
    uint16_t nFree;
    unsigned int regData = 0;

    status = CEDI_QueueTxBufSF(pD, bufAdd, length);
    if (CDN_EOK == status) {
        if((queueNum >= pD->txQs) || (bufAdd->pAddr == 0)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txQ = &(pD->txQueue[queueNum]);
        freeDesc = txQ->bdHead;
        bd1stBuf = txQ->bd1stBuf;
    }

    if (CDN_EOK == status) {
        txDescFree(pD, queueNum, &nFree);
        if (0 == nFree) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: insufficient buffer descriptors");
            status = CDN_ENOENT;
        }
    }

    if (CDN_EOK == status) {
        /* preserve wrap bit if present in status word */
        stat = CPS_UncachedRead32(&freeDesc->word[1]) & CEDI_TXD_WRAP;
        stat |= ((0 != (flags & CEDI_TXB_LAST_BUFF))?CEDI_TXD_LAST_BUF:0)
                | ((0 != (flags & CEDI_TXB_NO_AUTO_CRC))?CEDI_TXD_NO_AUTO_CRC:0)
                | length;

        /* Handle a multi-buffer frame */
        if ((!(flags & CEDI_TXB_LAST_BUFF)) && (NULL == bd1stBuf)) {
            /* This is the 1st buf of several; prevent it from going and remember its BD. */
            stat |= CEDI_TXD_USED;
            txQ->bd1stBuf = freeDesc;
        }

        *txQ->vHead = bufAdd->vAddr;
        CPS_UncachedWrite32(&freeDesc->word[0], bufAdd->pAddr & 0xFFFFFFFFU);
        /* upper 32 bits if 64 bit addressing */
        if (0 != pD->cfg.dmaAddrBusWidth) {
#ifdef CEDI_64B_COMPILE
            /* 64-bit addressing */
            CPS_UncachedWrite32(&freeDesc->word[2],
                                 (bufAdd->pAddr & 0xFFFFFFFF00000000)>>32);

	EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__MODIFY(regData, (bufAdd->pAddr & 0xFFFFFFFF00000000)>>32);
	CPS_UncachedWrite32(&(pD->regs->upper_tx_q_base_addr), regData);
#else
            /* 32-bit addressing */
            /* include only for test use */
                /* copy in faked upper 32 bits for testing in 32-bit env. */
            CPS_UncachedWrite32(&freeDesc->word[2],
                                 pD->cfg.upper32BuffTxQAddr);
#endif
        }
        CPS_UncachedWrite32(&freeDesc->word[1], stat);

    if ((flags & CEDI_TXB_LAST_BUFF) && (NULL != bd1stBuf)) {
        /* Last buffer of a multibuffer frame is in place, 1st buffer can go. */
        CPS_UncachedWrite32(&bd1stBuf->word[1],
                CPS_UncachedRead32(&bd1stBuf->word[1]) & ~CEDI_TXD_USED);
            txQ->bd1stBuf = NULL;
        }

        --txQ->descFree;
        txDescFree(pD, queueNum, &nFree);
        vDbgMsg(DBG_GEN_MSG, 15, "len=%u, queue=%u, txbdHead=%p, buffV=%p, buffP=%p, descFree=%u\n",
                length, queueNum, freeDesc, (void *)bufAdd->vAddr, (void *)bufAdd->pAddr, nFree);
        inc_txbd(pD, stat, &freeDesc, &txQ->vHead, txQ, queueNum);
        txQ->bdHead = freeDesc;

	itcs_dcache_flush();
        /* set going if complete frame queued */
        if ((flags & CEDI_TXB_LAST_BUFF) && (!(flags & CEDI_TXB_NO_AUTO_START))) {
            ncr = CPS_UncachedRead32(&(pD->regs->network_control));
            EMAC_REGS__NETWORK_CONTROL__TRANSMIT_START__SET(ncr);
            CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
        }
    }
    return status;
}

uint32_t CEDI_QTxBuf(CEDI_PrivateData *pD, CEDI_qTxBufParams *prm)
{
    uint32_t status;
    CEDI_TxQueue *txQ;
    CEDI_TxDesc *freeDesc;
    CEDI_TxDesc *bd1stBuf;
    uint32_t stat, ncr;
    uint32_t mssMfsStats;
    uint32_t tcpStreamShifted;
    uint16_t nFree;
    unsigned int regData = 0;

    status = CEDI_QTxBufSF(pD, prm);

    if (CDN_EOK == status) {
        if ((prm->queueNum>=pD->txQs) || (prm->bufAdd==NULL) || (prm->bufAdd->pAddr==0)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txQ = &(pD->txQueue[prm->queueNum]);
        freeDesc = txQ->bdHead;
        bd1stBuf = txQ->bd1stBuf;

        if ((!prm->length) || (prm->length > CEDI_TXD_LMASK)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: bad length specified: %u\n",
                    prm->length);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txDescFree(pD, prm->queueNum, &nFree);
        if (0 == nFree) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: insufficient buffer descriptors");
            status = CDN_ENOENT;
        }
    }

    if (CDN_EOK == status) {
        if (prm->flags & CEDI_TXB_ENABLE_TLT) {
                        if (0 == IsGem1p11(pD)) {
                status = CDN_ENOTSUP;
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Time base scheduling is not supported in your version of GEM");
            } else if (0 == pD->cfg.enTxExtBD[prm->queueNum]) {
                status = CDN_ENOTSUP;
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: TX extended BD mode is not enabled");
            }
                    }
    }

    if (CDN_EOK == status) {
        if (NULL!=bd1stBuf) {     /* inc counter after 1st in frame */
            txQ->descNum++;
        }

        mssMfsStats = ((uint32_t)(prm->mssMfs) << CEDI_TXD_MSSMFS_SHIFT) & (uint32_t)CEDI_TXD_MSSMFS_MASK;

        /* preserve wrap bit if present in status word */
        stat = CPS_UncachedRead32(&freeDesc->word[1]) & CEDI_TXD_WRAP;
        stat |= ((0 != (prm->flags & CEDI_TXB_LAST_BUFF))?CEDI_TXD_LAST_BUF:0)
                | ((0 != (prm->flags & CEDI_TXB_NO_AUTO_CRC))?CEDI_TXD_NO_AUTO_CRC:0)
                | prm->length
                | ((txQ->descNum>=1) ? mssMfsStats : 0);
                                    // only set MSS/MFS on second or later descriptor

        /* Handle a multi-buffer frame */
        tcpStreamShifted = ((uint32_t)(prm->tcpStream)<<CEDI_TXD_STREAM_SHIFT);
        if ((!(prm->flags & CEDI_TXB_LAST_BUFF)) && (NULL==bd1stBuf)) {
            /* This is the 1st buf of several; prevent it from going and remember its BD. */
            stat |= CEDI_TXD_USED
             /* Also use this condition to set encapsulation flags & TCP stream -
              * must not set stream if TSO bit clear */
                    | ((0 != (prm->flags & CEDI_TXB_TCP_ENCAP))?
                            /* TSO settings */
                        (CEDI_TXD_TSO_ENABLE|
                          (tcpStreamShifted & CEDI_TXD_STREAM_MASK)|
                          ((0 != (prm->flags & CEDI_TXB_TSO_AUTO_SEQ))?CEDI_TXD_AUTOSEQ_SEL:0)) :
                            /* UFO bit only */
                      ((0 != (prm->flags & CEDI_TXB_UDP_ENCAP))?CEDI_TXD_UFO_ENABLE:0));
            txQ->bd1stBuf = freeDesc;
        }

        *txQ->vHead = prm->bufAdd->vAddr;
        CPS_UncachedWrite32(&freeDesc->word[0], prm->bufAdd->pAddr & 0xFFFFFFFFU);

        /* upper 32 bits if 64 bit addressing */
        if (0 != pD->cfg.dmaAddrBusWidth) {
#ifdef CEDI_64B_COMPILE
            /* 64-bit addressing */
            CPS_UncachedWrite32(&freeDesc->word[2],
                                 (prm->bufAdd->pAddr & 0xFFFFFFFF00000000)>>32);
	EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__MODIFY(regData, (prm->bufAdd->pAddr & 0xFFFFFFFF00000000)>>32);
	CPS_UncachedWrite32(&(pD->regs->upper_tx_q_base_addr), regData);
#else
            /* include only for test use */
                /* copy in faked upper 32 bits for testing in 32-bit env. */
            CPS_UncachedWrite32(&freeDesc->word[2],
                                 pD->cfg.upper32BuffTxQAddr);
#endif
        }
        CPS_UncachedWrite32(&freeDesc->word[1], stat);

    if (prm->flags & CEDI_TXB_ENABLE_TLT){
        uint8_t wdNum;
        uint32_t tlt = prm->launchTime.nanoSecs & CEDI_TLT_NANO_SEC_MASK;
        tlt |= (prm->launchTime.secs >> CEDI_TLT_SECS_SHIFT);

        // position depends on 32/64 bit addr
        wdNum = (0 != (pD->cfg.dmaAddrBusWidth))?4:2;
        CPS_UncachedWrite32(&(freeDesc->word[wdNum]), tlt);
        CPS_UncachedWrite32(&(freeDesc->word[wdNum+1]), CEDI_TLT_UTLT);
    }

    if ((prm->flags & CEDI_TXB_LAST_BUFF) && (NULL!=bd1stBuf)) {
        /* Last buffer of a multibuffer frame is in place, 1st buffer can go. */
        CPS_UncachedWrite32(&bd1stBuf->word[1],
                CPS_UncachedRead32(&bd1stBuf->word[1]) & ~CEDI_TXD_USED);
        txQ->bd1stBuf = NULL;
        txQ->descNum = 0;
    }

    --txQ->descFree;
        inc_txbd(pD, stat, &freeDesc, &txQ->vHead, txQ, prm->queueNum);
        txQ->bdHead = freeDesc;

        /* set going if complete frame queued */
        if ((prm->flags & CEDI_TXB_LAST_BUFF) && (!(prm->flags & CEDI_TXB_NO_AUTO_START))) {
              ncr = CPS_UncachedRead32(&(pD->regs->network_control));
            EMAC_REGS__NETWORK_CONTROL__TRANSMIT_START__SET(ncr);
              CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
        }
    }
    return status;
}

uint32_t CEDI_DeQTxBuf(CEDI_PrivateData *pD, CEDI_qTxBufParams *prm)
{
    uint32_t status;
    CEDI_TxQueue *txQ;
    CEDI_TxDesc *descToFree;
    uint32_t stat;

    status = CEDI_DeQTxBufSF(pD, prm);

    if (CDN_EOK == status) {
        if((prm->bufAdd==NULL) || (prm->queueNum>=pD->txQs)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txQ = &(pD->txQueue[prm->queueNum]);
        descToFree = txQ->bdHead;

    /* Check if any in queue */
        if (txQ->bdTail==txQ->bdHead) {
            status = CDN_ENOENT;
        }
    }

    if (CDN_EOK == status) {
        /* unwind head pointers */
        dec_txbd(pD, &descToFree, &txQ->vHead, txQ, prm->queueNum);
        txQ->bdHead = descToFree;

        /* get virtual address */
        prm->bufAdd->vAddr = *txQ->vHead;

        /* get phys address */
        prm->bufAdd->pAddr = CPS_UncachedRead32(&descToFree->word[0]);
#ifdef CEDI_64B_COMPILE
        /* upper 32 bits if 64 bit addressing */
        if (0 != pD->cfg.dmaAddrBusWidth) {
#ifdef CONFIG_C920
            prm->bufAdd->pAddr |= ((unsigned long)CPS_UncachedRead32(&descToFree->word[2])<<32);
#endif
        }
#endif

        /* get length */
        stat = CPS_UncachedRead32(&descToFree->word[1]);
        prm->length = stat & CEDI_TXD_LEN_MASK;
        /* set used bit */
        CPS_UncachedWrite32(&descToFree->word[1], stat | CEDI_TXD_USED);

        if (txQ->descNum>0) {
            txQ->descNum--;
        }

        ++txQ->descFree;
    }

    return status;
}

uint32_t CEDI_TxDescFree(const CEDI_PrivateData *pD, uint8_t queueNum, uint16_t *numFree)
{
    uint32_t status = CEDI_TxDescFreeSF(pD, numFree);

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txDescFree(pD, queueNum, numFree);
    }

    return status;
}

uint32_t CEDI_FreeTxDesc(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_TxDescData *descData)
{
    uint32_t status;
    CEDI_TxQueue *txQ;
    uint8_t wdNum;
    uint32_t tsLowerWd, tsUpperWd;

    status = CEDI_FreeTxDescSF(pD, descData);

    if (CDN_EOK == status) {
        if (queueNum>=pD->txQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txQ = &(pD->txQueue[queueNum]);
        /* Check if any to free */
        if (txQ->bdTail == txQ->bdHead)
        {
            descData->status = CEDI_TXDATA_NONE_FREED;
            status = CDN_ENOENT;
        }
    }

    if (CDN_EOK == status) {
        /* check, if there is no incomplete multi-buffer frame still to be completed */
        if (txQ->bd1stBuf == txQ->bdTail) {
            descData->status = CEDI_TXDATA_NONE_FREED;
            status = CDN_EAGAIN;
        }
    }

    if (CDN_EOK == status) {
        /* Free next used descriptor in this frame */
        descData->txDescStat = CPS_UncachedRead32(&(txQ->bdTail->word[1]));
        if (0 != txQ->firstToFree)
        {
            /* look ahead to next desc */

            /* Only test used bit state for first buffer in frame. */
            if (0 == (descData->txDescStat & CEDI_TXD_USED)) {
                descData->status = CEDI_TXDATA_NONE_FREED;
                status = CDN_EAGAIN;
            }

            if (CDN_EOK == status) {
                /* extract timestamp if available */
                if ((pD->cfg.enTxExtBD[queueNum]) &&
                        (descData->txDescStat & CEDI_TXD_TS_VALID))
                {
                    uint32_t reg;
                        descData->txTsData.tsValid = 1;
                    // position depends on 32/64 bit addr
                        wdNum = (0 != (pD->cfg.dmaAddrBusWidth))?4:2;
                        tsLowerWd = CPS_UncachedRead32(&(txQ->bdTail->word[wdNum]));
                        tsUpperWd = CPS_UncachedRead32(&(txQ->bdTail->word[wdNum+1]));

                        descData->txTsData.tsNanoSec = tsLowerWd & CEDI_TS_NANO_SEC_MASK;
                        descData->txTsData.tsSecs = ((tsUpperWd & CEDI_TS_SEC1_MASK)
                                                        <<CEDI_TS_SEC1_POS_SHIFT)
                                                       | (tsLowerWd >> CEDI_TS_SEC0_SHIFT);

                            /* The timestamp only contains lower few bits of seconds, so add value from 1588 timer */
                    reg =  CPS_UncachedRead32(&(pD->regs->tsu_timer_sec));
                    /* If the top bit is set in the timestamp, but not in 1588 timer, it has rolled over, so subtract max size */
                    if ((descData->txTsData.tsSecs & (CEDI_TS_SEC_TOP>>1)) && (!(reg & (CEDI_TS_SEC_TOP>>1)))) {
                        descData->txTsData.tsSecs -= CEDI_TS_SEC_TOP;
                    }
                    descData->txTsData.tsSecs += ((uint32_t)(~CEDI_TS_SEC_MASK) & EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(reg));
                        }
                else {
                    descData->txTsData.tsValid = 0;
                }

                if (0 != (descData->txDescStat & CEDI_TXD_LAST_BUF)) {
                    descData->status = CEDI_TXDATA_1ST_AND_LAST;
                } else {
                    txQ->firstToFree = 0;
                    descData->status = CEDI_TXDATA_1ST_NOT_LAST;
                }
            }
        }
        else
        {
            /* set later used bits in frame, for consistency */
            CPS_UncachedWrite32(&(txQ->bdTail->word[1]),
                                    descData->txDescStat | CEDI_TXD_USED);
            if (0 != (descData->txDescStat & CEDI_TXD_LAST_BUF)) {
                descData->status = CEDI_TXDATA_LAST_BUFFER;
                txQ->firstToFree = 1;
            } else {
                descData->status = CEDI_TXDATA_MID_BUFFER;
            }
        }
    }

    if (CDN_EOK == status) {
        descData->bufAdd.pAddr = CPS_UncachedRead32(&(txQ->bdTail->word[0]));
        /* upper 32 bits if 64 bit addressing */
        if ((pD->cfg.dmaAddrBusWidth) &&
                    (sizeof(descData->bufAdd.pAddr)==sizeof(uint64_t))) {
            descData->bufAdd.pAddr |=
                    ((uint64_t)CPS_UncachedRead32(&(txQ->bdTail->word[2])))<<32;
        }

        descData->bufAdd.vAddr = *txQ->vTail;

        /* move queue pointers on */
        inc_txbd(pD, descData->txDescStat, &txQ->bdTail, &txQ->vTail, txQ, queueNum);
        ++txQ->descFree;

        /* paranoid - empty and no last buffer flag (on last freed)? */
        if ((0==((descData->txDescStat) & CEDI_TXD_LAST_BUF)) &&
                ((txQ->descFree)==((txQ->descMax)-CEDI_MIN_TXBD))) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: txQueue %u: LAST bit of frame not found!\n", queueNum);
            txQ->firstToFree = 1;
            status = CDN_EIO;
        }
    }

    if (CDN_EAGAIN == status) {
        status = CDN_EOK;
    }
    return status;
}

void CEDI_GetTxDescStat(const CEDI_PrivateData *pD, uint32_t txDStatWord, CEDI_TxDescStat *txDStat)
{
    uint32_t wd1;
    uint32_t status = CEDI_GetTxDescStatSF(pD, txDStat);

    if (CDN_EOK == status) {

        wd1 = txDStatWord;
        txDStat->chkOffErr = (wd1 & CEDI_TXD_CHKOFF_MASK) >> CEDI_TXD_CHKOFF_SHIFT;
        txDStat->lateColl = (0 != (wd1 & CEDI_TXD_LATE_COLL))?1:0;
        txDStat->frameCorr = (0 != (wd1 & CEDI_TXD_FR_CORR))?1:0;
        txDStat->txUnderrun = (0 != (wd1 & CEDI_TXD_UNDERRUN))?1:0;
        txDStat->retryExc = (0 != (wd1 & CEDI_TXD_RETRY_EXC))?1:0;
    }
}

uint32_t CEDI_GetTxDescSize(const CEDI_PrivateData *pD, uint32_t *txDescSize)
{
    uint32_t status = CEDI_GetTxDescSizeSF(pD, txDescSize);

        if (CDN_EOK == status) {
        // if qx_status and qx_control registers are available,
        // descriptor size may be different for different queues.
        if (pD->hwCfg.gem_vm == true) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: Unsupported: gem_vm set, tx descriptor size may differ for different queues."
                    "\n Use CEDI_GetTxQDescSize function instead.", __func__);
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        *txDescSize = pD->txDescriptorSize[0]; // for non-vm configs, sizes are the same, return one.
    }
    return status;
}

uint32_t CEDI_GetTxQDescSize(const CEDI_PrivateData *pD, uint8_t queueNum, uint32_t *txDescSize) {
    uint32_t status = CEDI_GetTxQDescSizeSF(pD, txDescSize);

    if (CDN_EOK == status) {
        // manual queue number check (sanity doesn't do this)
        if (queueNum >= pD->txQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available,
        // every queue has the same tx descriptor size
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable: "
                    "every queue has the same tx descriptor size\n", __func__);
            *txDescSize = pD->txDescriptorSize[0];
        } else {
            *txDescSize = pD->txDescriptorSize[queueNum];
        }
    }

    return status;
}


uint32_t CEDI_ResetTxQ(CEDI_PrivateData *pD, uint8_t queueNum)
{
    uint32_t status;
    uint32_t regTmp;
    CEDI_TxQueue *txQ;
    CEDI_TxDesc *descStartPerQ;
    uint32_t pAddr;
    uintptr_t vAddr;
    uint16_t q, i;
    uint32_t sumTxDescSize;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_ResetTxQSF(pD);

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        txQ = &(pD->txQueue[queueNum]);
        txQ->descFree = pD->cfg.txQLen[queueNum];
        txQ->descMax = txQ->descFree + CEDI_MIN_TXBD;
        vAddr = pD->cfg.txQAddr;
        pAddr = pD->cfg.txQPhyAddr;
        q = 0;
        /* find start addresses for this txQ */
        txQ->vAddrList = pD->txQueue[0].vAddrList;
        while (q<queueNum) {
            CEDI_TxQueue *txQ1 = &(pD->txQueue[q]);

            sumTxDescSize = (uint32_t)(txQ1->descMax) * (uint32_t)(pD->txDescriptorSize[q]);
            vAddr += (uintptr_t)sumTxDescSize;
            pAddr += sumTxDescSize;
            txQ->vAddrList += txQ1->descMax;
            q++;
        }
        vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s: base address Q%u virt=%08lX phys=%08X vAddrList=%p\n",
                __func__, queueNum, vAddr, pAddr, txQ->vAddrList);
        txQ->bdBase = (CEDI_TxDesc *)vAddr;

        txQ->bdTail = txQ->bdBase;
        txQ->bdHead = txQ->bdBase;
        txQ->bd1stBuf = NULL;
        txQ->vHead = txQ->vAddrList;
        txQ->vTail = txQ->vAddrList;
        txQ->firstToFree = 1;
        txQ->descNum = 0;

        /* set used flags & last wrap flag */
        descStartPerQ = txQ->bdBase;
        for (i = 0; i<txQ->descMax; i++) {
            CPS_UncachedWrite32((uint32_t *)&(descStartPerQ->word[0]), 0);
            CPS_UncachedWrite32((uint32_t *)&(descStartPerQ->word[1]),
                    CEDI_TXD_USED | ((i==((txQ->descMax)-1))?CEDI_TXD_WRAP:0));
            moveTxDescAddr(&descStartPerQ, (pD->txDescriptorSize[queueNum]));
        }

        if (q == 0) {
            regTmp = CPS_REG_READ(&(pD->regs->transmit_q_ptr));
            EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__SET(regTmp);
            CPS_REG_WRITE(&(pD->regs->transmit_q_ptr), regTmp);

            EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__MODIFY(regTmp, pAddr >> 2);
            CPS_REG_WRITE(&(pD->regs->transmit_q_ptr), regTmp);

            EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__CLR(regTmp);
            CPS_REG_WRITE(&(pD->regs->transmit_q_ptr), regTmp);
        } else {
            regPtr = transmitPtrReg[q-1];
            addRegBase(pD, &regPtr);
            regTmp = CPS_REG_READ(regPtr);

            EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__SET(regTmp);
            CPS_REG_WRITE(regPtr, regTmp);

            EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__MODIFY(regTmp, pAddr >> 2);
            CPS_REG_WRITE(regPtr, regTmp);

            EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__CLR(regTmp);
            CPS_REG_WRITE(regPtr, regTmp);
        }
    }
    return status;
}

uint32_t CEDI_StartTx(CEDI_PrivateData *pD)
{
    uint32_t status;
    uint32_t qNum;
    uint8_t ok = 0;
    CEDI_TxQueue *txQ;
    uint32_t ncr;

    status = CEDI_StartTxSF(pD);

    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered\n", __func__);

        if (0 == CEDI_GetTxEnabled(pD)) {
            CEDI_EnableTx(pD);
        }

        /* if anything to transmit, start transmission */
        for (qNum = 0; qNum < pD->txQs; ++qNum) {
            txQ = &(pD->txQueue[qNum]);
            if (txQ->bdHead != txQ->bdTail) {
                ok = 1;
                break;
            }
        }
        if (0 == ok) {
            status = CDN_ECANCELED;
        } else {
            ncr = CPS_UncachedRead32(&(pD->regs->network_control));
            EMAC_REGS__NETWORK_CONTROL__TRANSMIT_START__SET(ncr);
            CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
        }
    }
    return status;
}


/* Enable & start the transmit circuit for given queue. Not required during normal
 * operation, as queueTxBuf will automatically start Tx when complete frame
 * has been queued, but may be used to restart after a Tx error.
 *
 * For configurations with per-queue transmission start support
 * (gem_vm == true, ip version at least 1p13)
 */
uint32_t CEDI_StartQTx(CEDI_PrivateData *pD, uint8_t queueNum) {
    uint32_t status = CEDI_StartQTxSF(pD);
    CEDI_TxQueue *txQ;

    // only available on 1p13
    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }
    // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
    if (CDN_EOK == status) {
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s entered\n", __func__);

        if (CDN_EOK == CEDI_GetTxEnabled(pD)) {
            CEDI_EnableTx(pD);
        }

        /* if anything to transmit, start transmission */
        txQ = &(pD->txQueue[queueNum]);
        if (txQ->bdHead == txQ->bdTail) { // if nothing to transmit
            status = CDN_ECANCELED;
        } else {
            volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

            uint32_t val = CPS_UncachedRead32(regPtr);
            EMAC_REGS__Q_CONTROL__TRANSMIT_START__SET(val);
            CPS_UncachedWrite32(regPtr, val);
        }
    }
    return status;
}


/* Halt transmission as soon as current frame Tx has finished
 * @param pD - driver private state info specific to this instance
 */
uint32_t CEDI_StopTx(CEDI_PrivateData *pD)
{
    uint32_t ncr;
    uint32_t status = CEDI_StopTxSF(pD);

    if (CDN_EOK == status) {
        ncr = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__TRANSMIT_HALT__SET(ncr);
        CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
    }
    return status;
}

/** Halt transmission for the given queue as soon as current frame Tx has finished.
 *
 * For configurations with per-queue transmission start support
 * (gem_vm == true, ip version at least 1p13)
 */
uint32_t CEDI_StopQTx(CEDI_PrivateData *pD, uint8_t queueNum) {
    uint32_t status = CEDI_StopQTxSF(pD);

    // only available on 1p13
    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }
    // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
    if (CDN_EOK == status) {
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);
        EMAC_REGS__Q_CONTROL__TRANSMIT_HALT__SET(val);
        CPS_UncachedWrite32(regPtr, val);
    }
    return status;
}


/* Immediately disable transmission without waiting for completion.
 * Since the EMAC will reset to point to the start of transmit descriptor
 * list, the buffer queues may have to be reset after this call.
 * @param pD - driver private state info specific to this instance
 */
void CEDI_AbortTx(CEDI_PrivateData *pD)
{
    uint32_t ncr;
    uint32_t status = CEDI_AbortTxSF(pD);

    if (CDN_EOK == status) {
        ncr = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__CLR(ncr);
        CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
    }
}

/* Get state of transmitter
 * @param pD - driver private state info specific to this instance
 * @return 1 if active
 * @return 0 if idle or pD==NULL
 */
uint32_t CEDI_Transmitting(CEDI_PrivateData *pD)
{
    uint32_t retVal;
    uint32_t reg;

    retVal = CEDI_TransmittingSF(pD);

    if (CDN_EOK == retVal) {
        reg = CPS_UncachedRead32(&(pD->regs->transmit_status));
        retVal = EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__READ(reg);
    } else {
        retVal = 0U;
    }
    return retVal;
}

void CEDI_EnableTx(CEDI_PrivateData *pD)
{
    uint32_t ncr;
    uint32_t status = CEDI_EnableTxSF(pD);

    if (CDN_EOK == status) {
        /* Enable the transmitter */
        ncr = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__SET(ncr);
        CPS_UncachedWrite32(&(pD->regs->network_control), ncr);
    }
}

uint32_t CEDI_GetTxEnabled(CEDI_PrivateData *pD)
{
    uint32_t retVal;
    uint32_t status = CEDI_GetTxEnabledSF(pD);

    if (CDN_EOK != status) {
        retVal = 0;
    } else {
        retVal = (EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__READ(
                CPS_UncachedRead32(&(pD->regs->network_control))));
    }

    return retVal;
}

uint32_t CEDI_GetTxStatus(CEDI_PrivateData *pD, CEDI_TxStatus *txStatus)
{
    uint32_t reg = 0U;
    uint32_t status = CEDI_GetTxStatusSF(pD, txStatus);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->transmit_status));

        txStatus->txComplete =
                EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__READ(reg);
        txStatus->usedBitRead =
                EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__READ(reg);
        txStatus->collisionOcc =
                EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__READ(reg);
        txStatus->retryLimExc =
                EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__READ(reg);
        txStatus->lateCollision =
                EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__READ(reg);
        txStatus->txActive =
                EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__READ(reg);
        txStatus->txFrameErr =
                EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__READ(reg);
        txStatus->txUnderRun =
                EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__READ(reg);
        txStatus->hRespNotOk =
                EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__READ(reg);
    }
    return reg;
}

uint32_t CEDI_GetQTxStatus(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_TxQStatus *txQstatus) {
    uint32_t status = CEDI_GetQTxStatusSF(pD, txQstatus);

    // only available on 1p13
    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxStatusRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);

        txQstatus->usedBitRead = EMAC_REGS__Q_STATUS__TX_USED_BIT_READ__READ(val);
        txQstatus->buffExMid = EMAC_REGS__Q_STATUS__TX_USED_BIT_READ_MIDFRAME__READ(val);
        txQstatus->txComplete = EMAC_REGS__Q_STATUS__TRANSMIT_COMPLETE__READ(val);
    }
    return status;
}

uint32_t CEDI_ClearTxStatus(const CEDI_PrivateData *pD, uint32_t resetStatus)
{
    uint32_t dst = 0U;
    uint32_t status = CEDI_ClearTxStatusSF(pD, resetStatus);

    if (CDN_EOK == status) {
        if (0U != (resetStatus & CEDI_TXS_USED_READ)) {
            EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__MODIFY(dst, 1U);
        }
        if (0U != (resetStatus & CEDI_TXS_COLLISION)) {
            EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__MODIFY(dst, 1U);
        }
        if (0U != (resetStatus & CEDI_TXS_RETRY_EXC)) {
            EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__MODIFY(dst, 1U);
        }
        if (0U != (resetStatus & CEDI_TXS_LATE_COLL)) {
            EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__MODIFY(dst, 1U);
        }
        /* txActive not resettable */
        if (0U != (resetStatus & CEDI_TXS_FRAME_ERR)) {
            EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__MODIFY(dst, 1U);
        }
        if (0U != (resetStatus & CEDI_TXS_TX_COMPLETE)) {
            EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__MODIFY(dst, 1U);
        }
        if (0U != (resetStatus & CEDI_TXS_UNDERRUN)) {
            EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__MODIFY(dst, 1U);
        }
        if (0U != (resetStatus & CEDI_TXS_HRESP_ERR)) {
            EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__MODIFY(dst, 1U);
        }
        if (0U != dst) {
            CPS_UncachedWrite32(&(pD->regs->transmit_status), dst);
        }
    }

    return status;
}

uint32_t CEDI_ClearQTxStatus(CEDI_PrivateData *pD, uint8_t queueNum, uint32_t resetStatus) {
    uint32_t status = CEDI_ClearQTxStatusSF(pD, resetStatus);

    // only available on 1p13
    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable\n", __func__);
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        uint32_t val = 0U;
        volatile uint32_t *regPtr = getQxStatusRegAddr(pD, queueNum);

        if (0 != (resetStatus & CEDI_TXSQ_TX_COMPLETE)) {
            val |= CEDI_TXSQ_TX_COMPLETE;
        }

        if (0 != (resetStatus & CEDI_TXSQ_USED_BIT_READ)) {
            val |= CEDI_TXSQ_USED_BIT_READ;
        }

        if (0 != (resetStatus & CEDI_TXSQ_BUFF_EX_MID)) {
            val |= CEDI_TXSQ_BUFF_EX_MID;
        }

        CPS_UncachedWrite32(regPtr, val);
    }
    return status;
}

uint32_t CEDI_SetTxPartialStFwd(CEDI_PrivateData *pD, uint32_t watermark, uint8_t enable)
{
    uint32_t status;
    uint32_t reg;
    uint32_t txPbufAddrShifted;
    uint8_t txPbufAddr;

    status = CEDI_SetTxPartialStFwdSF(pD, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.tx_pkt_buffer==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        txPbufAddr = pD->hwCfg.tx_pbuf_addr;
        if (txPbufAddr < 16) {
            txPbufAddrShifted = 1 << txPbufAddr;
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "ERROR: Wrong tx_pbuf_num_segments read from hardware register");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if ((enable==1) &&
            ((watermark<0x14) || (watermark>=txPbufAddrShifted))) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pbuf_txcutthru));
        if (0 != enable) {
            EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__MODIFY(reg,
                    watermark);
            EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__SET(reg);
        } else {
            EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__CLR(reg);
        }

        CPS_UncachedWrite32(&(pD->regs->pbuf_txcutthru), reg);
    }

    return status;
}

uint32_t CEDI_GetTxPartialStFwd(CEDI_PrivateData *pD, uint32_t *watermark, uint8_t *enable)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_GetTxPartialStFwdSF(pD, watermark, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.tx_pkt_buffer==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pbuf_txcutthru));
        (*enable) = EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__READ(reg);
        if (0 != (*enable)) {
            (*watermark) = EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__READ(reg);
        }
    }
        return status;
}


uint32_t CEDI_EnableCbs(CEDI_PrivateData *pD, uint8_t qSel, uint32_t idleSlope)
{
    uint32_t status;
    uint32_t tmp;
    uint8_t enabled;
    uint32_t reg;

    status = CEDI_EnableCbsSF(pD, qSel);

    if (CDN_EOK == status) {
        if (pD->hwCfg.exclude_cbs==1) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->txQs==1) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        status = CEDI_GetCbsQSetting(pD, qSel, &enabled, &tmp);
    }

    if (CDN_EOK == status) {
        if (0 != enabled) {
            CEDI_DisableCbs(pD, qSel);
        }

        reg = 0;
        if (0 != qSel) {   /* i.e. queue B */
            EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__MODIFY(reg, idleSlope);
            CPS_UncachedWrite32(&(pD->regs->cbs_idleslope_q_b), reg);
        }
        else {
            EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__MODIFY(reg, idleSlope);
            CPS_UncachedWrite32(&(pD->regs->cbs_idleslope_q_a), reg);
        }

        reg = CPS_UncachedRead32(&(pD->regs->cbs_control));
        if (0 != qSel)   /* i.e. queue B */ {
            EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__MODIFY(reg, 1);
        } else {
            EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__MODIFY(reg, 1);
        }
        CPS_UncachedWrite32(&(pD->regs->cbs_control), reg);
    }

    return status;
}

void CEDI_DisableCbs(CEDI_PrivateData *pD, uint8_t qSel)
{
    uint32_t reg;
    uint32_t status = CEDI_DisableCbsSF(pD, qSel);

    if (CDN_EOK == status) {
        if (pD->hwCfg.exclude_cbs == 0) {
            reg = CPS_UncachedRead32(&(pD->regs->cbs_control));
            if (0 != qSel) {  /* i.e. queue B */
                EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__MODIFY(reg, 0);
            } else {
                EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__MODIFY(reg, 0);
            }
            CPS_UncachedWrite32(&(pD->regs->cbs_control), reg);
        }
    }
}

uint32_t CEDI_GetCbsQSetting(CEDI_PrivateData *pD, uint8_t qSel,
               uint8_t *enable, uint32_t *idleSlope)
{
    uint32_t status;
    uint32_t reg, enabled;

    status = CEDI_GetCbsQSettingSF(pD, qSel, enable, idleSlope);

    if (CDN_EOK == status) {
        if (pD->hwCfg.exclude_cbs==1) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->cbs_control));
        if (0 != qSel) { /* i.e. queue B */
            enabled = EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__READ(reg);
            if (enabled && (idleSlope!=NULL)) {
                reg = CPS_UncachedRead32(&(pD->regs->cbs_idleslope_q_b));
                *idleSlope = EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__READ(reg);
            }
        }
        else {
            enabled = EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__READ(reg);
            if (enabled && (idleSlope!=NULL)) {
                reg = CPS_UncachedRead32(&(pD->regs->cbs_idleslope_q_a));
                *idleSlope = EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__READ(reg);
            }
        }
        *enable=enabled;
    }
    return status;
}

uint32_t CEDI_SetIpgStretch(CEDI_PrivateData *pD, uint8_t enable, uint8_t multiplier,
        uint8_t divisor)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_SetIpgStretchSF(pD, enable, multiplier, divisor);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != enable) {
            EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__SET(reg);
            CPS_UncachedWrite32(&(pD->regs->network_config), reg);
            reg = CPS_UncachedRead32(&(pD->regs->stretch_ratio));
            EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__MODIFY(reg,
                    ((uint32_t)divisor << 8) | multiplier);
            CPS_UncachedWrite32(&(pD->regs->stretch_ratio), reg);
        }
        else {
            EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__CLR(reg);
            CPS_UncachedWrite32(&(pD->regs->network_config), reg);
        }
    }
    return status;
}

uint32_t CEDI_GetIpgStretch(CEDI_PrivateData *pD, uint8_t *enabled, uint8_t *multiplier,
        uint8_t *divisor)
{
    uint32_t status;
    uint32_t reg, stretch;

    status = CEDI_GetIpgStretchSF(pD, enabled, multiplier, divisor);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__READ(reg)) {
            *enabled = 1;
            reg = CPS_UncachedRead32(&(pD->regs->stretch_ratio));
            stretch = EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__READ(reg);
            *multiplier = (stretch & 0xFF);
            *divisor = (stretch >> 8) & 0xFF;
        }
        else {
            *enabled = 0;
            *multiplier = 0;
            *divisor = 0;
        }
    }
    return status;
}

uint32_t CEDI_SetMinIpg(CEDI_PrivateData* pD, CEDI_MinIpg minIpg, uint8_t MinIpgInBytes)
{
    uint32_t status = CDN_EOK;
    volatile uint32_t reg;

    status = CEDI_SetMinIpgSF(pD, minIpg);

    if (CDN_EOK == status) {
        if (0 == IsSetMinIpgSupported(pD)) {
            status = CDN_ENOTSUP;
        } else {
            reg = CPS_UncachedRead32(&(pD->regs->stretch_ratio));
            switch (minIpg) {
                case CEDI_MINIMUM_IPG_12:
#ifdef CEDI_GEM_GXL_701X 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG_24_BYTES__CLR(reg);
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG_32_BYTES__CLR(reg);
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, 0U); 
#else
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, 0U); 
#endif				
                    break;

                case CEDI_MINIMUM_IPG_24:
#ifdef CEDI_GEM_GXL_701X 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG_24_BYTES__SET(reg); 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG_32_BYTES__CLR(reg); 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, 0U); 
#else
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, 6U); 
#endif				
                    break;

                case CEDI_MINIMUM_IPG_32:
#ifdef CEDI_GEM_GXL_701X 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG_24_BYTES__CLR(reg); 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG_32_BYTES__SET(reg); 
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, 0U);
#else
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, 8U);
#endif				
                    break;

                case CEDI_MINIMUM_IPG_CUSTOM:
                    EMAC_REGS__STRETCH_RATIO__MIN_IPG__MODIFY(reg, (MinIpgInBytes/4U)); 
                    break;
		
                default:
                    status = CDN_EINVAL;
                    break;
            }

            if (CDN_EOK == status) {
                CPS_UncachedWrite32(&(pD->regs->stretch_ratio), reg);
            }
        }
    }
    return status;
}

uint32_t CEDI_SetTxDefer(CEDI_PrivateData *pD, bool enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_SetTxDeferSF(pD);

        if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {

        /* defer/release transmission */
                regVal = CPS_REG_READ(&(pD->regs->hs_mac_config));

        if (enable) {
            EMAC_REGS__HS_MAC_CONFIG__TX_DEFER__SET(regVal);
        } else {
            EMAC_REGS__HS_MAC_CONFIG__TX_DEFER__CLR(regVal);
        }

        CPS_REG_WRITE(&(pD->regs->hs_mac_config), regVal);
            }
    return status;
}

uint32_t CEDI_GetTxDefer(CEDI_PrivateData *pD, bool* enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetTxDeferSF(pD, enable);

        if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
                regVal = CPS_REG_READ(&(pD->regs->hs_mac_config));
        *enable = (EMAC_REGS__HS_MAC_CONFIG__TX_DEFER__READ(regVal) != 0U);

    }
    return status;
}


/* set memory segments per queue */
uint32_t DoSetSegAlloc(CEDI_PrivateData *pD, const CEDI_SegmentsPerQueue *seqmentsPerQueue,
        uint8_t numOfQueues) {
    uint32_t status = CDN_EOK;
    uint32_t tx_q_seg_alloc_q_lower, tx_q_seg_alloc_q_upper = 0;

    if ((numOfQueues < 1) || (numOfQueues > 16)) {
        status = CDN_EINVAL;
    }
    if ((CDN_EOK == status) && (numOfQueues < 2)) {
        status = CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        tx_q_seg_alloc_q_lower = CPS_UncachedRead32(&(pD->regs->tx_q_seg_alloc_q_lower));
        if (numOfQueues > 8)
        {
            tx_q_seg_alloc_q_upper = CPS_UncachedRead32(&(pD->regs->tx_q_seg_alloc_q_upper));
        }

        if (numOfQueues >= 16) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q15__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[15]);
        }
        if (numOfQueues >= 15) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q14__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[14]);
        }
        if (numOfQueues >= 14) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q13__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[13]);
        }
        if (numOfQueues >= 13) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q12__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[12]);
        }
        if (numOfQueues >= 12) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q11__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[11]);
        }
        if (numOfQueues >= 11) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q10__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[10]);
        }
        if (numOfQueues >= 10) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q9__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[9]);
        }
        if (numOfQueues >= 9) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q8__MODIFY(tx_q_seg_alloc_q_upper, seqmentsPerQueue[8]);
        }
        if (numOfQueues >= 8) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q7__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[7]);
        }
        if (numOfQueues >= 7) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q6__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[6]);
        }
        if (numOfQueues >= 6) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q5__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[5]);
        }
        if (numOfQueues >= 5) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q4__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[4]);
        }
        if (numOfQueues >= 4) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q3__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[3]);
        }
        if (numOfQueues >= 3) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q2__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[2]);
        }
        if (numOfQueues >= 2) {
            EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q1__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[1]);
        }

        EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q0__MODIFY(tx_q_seg_alloc_q_lower, seqmentsPerQueue[0]);

        CPS_UncachedWrite32(&(pD->regs->tx_q_seg_alloc_q_lower), tx_q_seg_alloc_q_lower);
        if (numOfQueues > 8)
        {
            CPS_UncachedWrite32(&(pD->regs->tx_q_seg_alloc_q_upper), tx_q_seg_alloc_q_upper);
        }
    }

    return status;
}

/* get memory segments per queue */
uint32_t DoGetSegAlloc(CEDI_PrivateData *pD, CEDI_SegmentsPerQueue *seqmentsPerQueue,
        uint8_t numOfQueues) {
    uint32_t status = CDN_EOK;

    uint32_t tx_q_seg_alloc_q_lower, tx_q_seg_alloc_q_upper = 0;

    if((numOfQueues < 1) || (numOfQueues > 16)) {
        status = CDN_EINVAL;
    }
    if ((CDN_EOK == status) && (numOfQueues < 2)) {
        status = CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        tx_q_seg_alloc_q_lower = CPS_UncachedRead32(&(pD->regs->tx_q_seg_alloc_q_lower));
        if (numOfQueues > 8) {
            tx_q_seg_alloc_q_upper = CPS_UncachedRead32(&(pD->regs->tx_q_seg_alloc_q_upper));
        }

        if (numOfQueues >= 16) {
            seqmentsPerQueue[15] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q15__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 15) {
            seqmentsPerQueue[14] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q14__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 14) {
            seqmentsPerQueue[13] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q13__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 13) {
            seqmentsPerQueue[12] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q12__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 12) {
            seqmentsPerQueue[11] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q11__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 11) {
            seqmentsPerQueue[10] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q10__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 10) {
            seqmentsPerQueue[9] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q9__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 9) {
            seqmentsPerQueue[8] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_UPPER__SEGMENT_ALLOC_Q8__READ(tx_q_seg_alloc_q_upper);
        }
        if (numOfQueues >= 8) {
            seqmentsPerQueue[7] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q7__READ(tx_q_seg_alloc_q_lower);
        }
        if (numOfQueues >= 7) {
            seqmentsPerQueue[6] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q6__READ(tx_q_seg_alloc_q_lower);
        }
        if (numOfQueues >= 6) {
            seqmentsPerQueue[5] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q5__READ(tx_q_seg_alloc_q_lower);
        }
        if (numOfQueues >= 5) {
            seqmentsPerQueue[4] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q4__READ(tx_q_seg_alloc_q_lower);
        }
        if (numOfQueues >= 4) {
            seqmentsPerQueue[3] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q3__READ(tx_q_seg_alloc_q_lower);
        }
        if (numOfQueues >= 3) {
            seqmentsPerQueue[2] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q2__READ(tx_q_seg_alloc_q_lower);
        }
        if (numOfQueues >= 2) {
            seqmentsPerQueue[1] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q1__READ(tx_q_seg_alloc_q_lower);
        }
        seqmentsPerQueue[0] = EMAC_REGS__TX_Q_SEG_ALLOC_Q_LOWER__SEGMENT_ALLOC_Q0__READ(tx_q_seg_alloc_q_lower);
    }

    return status;
}

/* functions check if sum of segments for each queue does not exceed
 * all segments count. Calculation is made for given queue count.
 * Function also verify if queue size value is proper - does not
 * exceed maximum value */
static uint32_t CheckSegAlloc(const CEDI_PrivateData *pD, const CEDI_SegmentsPerQueue *seqmentsPerQueue, uint8_t segAllocCount)
{
    uint32_t status = CDN_EOK;
    uint8_t i;
    uint32_t SegAllocsSummary = 0;
    uint8_t txPbufQSegSizeShift = pD->hwCfg.tx_pbuf_queue_segment_size;
    const uint8_t maxSegsPerQueue = (uint8_t)CEDI_SEGMENTS_PER_QUEUE_128;
    uint8_t currSegsPerQueue;

    for (i = 0; i < segAllocCount; i++){
        currSegsPerQueue = (uint8_t)seqmentsPerQueue[i];
        if (currSegsPerQueue <= maxSegsPerQueue) {
            SegAllocsSummary += (1 << currSegsPerQueue);
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Number of queues to configure are different than active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (txPbufQSegSizeShift < 16) {
            if (SegAllocsSummary > (1 << txPbufQSegSizeShift)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                        "Error: Number of segments for all active queues: %d, "
                        "is bigger than number of available segments %d\n", SegAllocsSummary,
                         (1 << txPbufQSegSizeShift));
                status = CDN_EINVAL;
            }
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Wrong tx_pbuf_queue_segment_size read from hardware "\
                    "register.");
            status = CDN_EINVAL;
        }
    }

    return status;
}

uint32_t CEDI_SetTxQueueSegAlloc(CEDI_PrivateData *pD, const CEDI_QueueSegAlloc *queueSegAlloc)
{
    uint32_t status;
    uint8_t i;
    CEDI_SegmentsPerQueue seqmentsPerQueue[CEDI_MAX_TX_QUEUES] = {0};

    status = CEDI_SetTxQueueSegAllocSF(pD, queueSegAlloc);

    if (CDN_EOK == status) {
        if (queueSegAlloc->segAllocCount > pD->cfg.txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Number of queues to configure are bigger than supported queue number\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        status = CheckSegAlloc(pD, queueSegAlloc->segAlloc, queueSegAlloc->segAllocCount);
    }

    if (CDN_EOK == status) {
        for (i = 0; i < queueSegAlloc->segAllocCount; i++){
                seqmentsPerQueue[i] = queueSegAlloc->segAlloc[i];
        }
    }

    if (CDN_EOK == status) {
        status = DoSetSegAlloc(pD, seqmentsPerQueue, pD->cfg.txQs);
    }

    return status;
}

/** function gets number of memory segments used by Tx queue */
uint32_t getAllSegAlloctCount(const CEDI_PrivateData *pD, uint32_t *numberOfSegments) {
    uint32_t status = CDN_EOK;
    uint8_t txPbufQSegSizeShift;
    if ((pD == NULL) || (numberOfSegments == NULL)) {
        status = CDN_EINVAL;
    } else {
        txPbufQSegSizeShift = pD->hwCfg.tx_pbuf_queue_segment_size;

        if (txPbufQSegSizeShift < 16) {
            *numberOfSegments = (1uL << txPbufQSegSizeShift);
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Wrong tx_pbuf_queue_segment_size read from hardware "\
                    "register.");
            status = CDN_EINVAL;
        }
    }
    return status;
}

/* get memory segments per queue */
uint32_t getSegAlloc(CEDI_PrivateData *pD, CEDI_QueueSegAlloc *queueSegAlloc) {
    uint32_t status = CDN_EOK;

    if ((pD == NULL) || (queueSegAlloc == NULL)) {
        status = CDN_EINVAL;
    }

    if (CDN_EOK == status) {
        if (queueSegAlloc->segAllocCount > pD->cfg.txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Number of queues to configure are bigger than supported queue number\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        status = DoGetSegAlloc(pD, queueSegAlloc->segAlloc, queueSegAlloc->segAllocCount);
    }

    return status;
}

uint32_t CEDI_SetTxQueueNum(CEDI_PrivateData *pD, uint8_t numQueues)
{
    uint32_t status;
    CEDI_SegmentsPerQueue seqmentsPerQueue[CEDI_MAX_TX_QUEUES];

    status = CEDI_SetTxQueueNumSF(pD,numQueues);

    if (CDN_EOK == status) {
        /* number of queues cannot be bigger than set during driver initialization */
        if (numQueues >  pD->cfg.txQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (numQueues == pD->txQs) {
            /* Do nothing */
            status = CDN_EAGAIN;
        }
    }

    if (CDN_EOK == status) {
        if (0 == IsGem1p09(pD)){
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "Warning: changing queue number is not supported\n");
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        /* Transmission must be disabled before calling this function */
        if (0 != CEDI_GetTxEnabled(pD)) { // this function return 0 or 1
            status = CDN_EIO;
        }
    }

    /* if we have only one queue then we do not need to check which segments are used
     * because one queue can use all existing segments */
    if (numQueues > 1U){
    if (CDN_EOK == status) {
        /* get current segment allocation setting */
        status = DoGetSegAlloc(pD, seqmentsPerQueue, numQueues);
    }

    if (CDN_EOK == status) {
        /* check if new queue settings make using segments above available segments */
        status = CheckSegAlloc(pD, seqmentsPerQueue, numQueues);
    }
    }

    if (CDN_EOK == status) {
    uint8_t i;

    /* enable all queues with number below numQueues) */
    for (i = numQueues - 1; i < pD->cfg.txQs; i++) {
        setTxQueueDisableBit(pD, i, 0U);
    }

        /* disable all queues with number equal to or above numQueues) */
    for (i = numQueues; i < pD->cfg.txQs; i++) {
        setTxQueueDisableBit(pD, i, 1U);
    }

        /* set new tx priority queues number */
        pD->txQs = numQueues;
    }

    if (CDN_EAGAIN == status) {
        status = CDN_EOK;
    }

    return status;
}

uint32_t CEDI_GetTxQueueNum(const CEDI_PrivateData *pD, uint8_t* numQueues)
{
    uint32_t status = CEDI_GetTxQueueNumSF(pD, numQueues);

    if (CDN_EOK == status) {
        *numQueues = pD->txQs;
    }
    return status;
}

uint32_t CEDI_SetTxQueueScheduler(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_TxSchedType schedType)
{
    uint32_t status;
    uint32_t regTmp;
    uint8_t txQs;

    status = CEDI_SetTxQueueSchedulerSF(pD, schedType);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        txQs = pD->txQs;

        if (queueNum >= txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if ((schedType == CEDI_TX_SCHED_TYPE_CBS) && (txQs > 2)
            && (queueNum < (txQs - 2))){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: CBS can be set only to highest priority queue and second highest priority queue \n");
            status = CDN_EINVAL;
        }
    }
#ifdef __EMAC_REGS__TX_SCHED_CTRL_MACRO__
    if (CDN_EOK == status) {
        if (0 == IsGem1p09(pD)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Feature not supported- current moduleId:%0x , expected is above:%0x \n",
                    pD->hwCfg.moduleId , GEM_GXL_MODULE_ID_V1 );
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->tx_sched_ctrl));
        switch(queueNum){
        case 0:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q0__MODIFY(regTmp, schedType);
            break;
        case 1:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__MODIFY(regTmp, schedType);
            break;
        case 2:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__MODIFY(regTmp, schedType);
            break;
        case 3:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__MODIFY(regTmp, schedType);
            break;
        case 4:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__MODIFY(regTmp, schedType);
            break;
        case 5:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__MODIFY(regTmp, schedType);
            break;
        case 6:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__MODIFY(regTmp, schedType);
            break;
        case 7:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__MODIFY(regTmp, schedType);
            break;
        case 8:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__MODIFY(regTmp, schedType);
            break;
        case 9:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__MODIFY(regTmp, schedType);
            break;
        case 10:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__MODIFY(regTmp, schedType);
            break;
        case 11:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__MODIFY(regTmp, schedType);
            break;
        case 12:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__MODIFY(regTmp, schedType);
            break;
        case 13:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__MODIFY(regTmp, schedType);
            break;
        case 14:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__MODIFY(regTmp, schedType);
            break;
        case 15:
        EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__MODIFY(regTmp, schedType);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }

    if (CDN_EOK == status) {
        CPS_UncachedWrite32(&(pD->regs->tx_sched_ctrl), regTmp);
    }

#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

uint32_t CEDI_GetTxQueueScheduler(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_TxSchedType *schedType)
{
    uint32_t status;
    uint32_t regTmp;

    status = CEDI_GetTxQueueSchedulerSF(pD, schedType);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }


#ifdef __EMAC_REGS__TX_SCHED_CTRL_MACRO__
    if (CDN_EOK == status) {
        regTmp = CPS_UncachedRead32(&(pD->regs->tx_sched_ctrl));
        switch(queueNum){
        case 0:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q0__READ(regTmp);
            break;
        case 1:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__READ(regTmp);
            break;
        case 2:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__READ(regTmp);
            break;
        case 3:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__READ(regTmp);
            break;
        case 4:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__READ(regTmp);
            break;
        case 5:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__READ(regTmp);
            break;
        case 6:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__READ(regTmp);
            break;
        case 7:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__READ(regTmp);
            break;
        case 8:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__READ(regTmp);
            break;
        case 9:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__READ(regTmp);
            break;
        case 10:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__READ(regTmp);
            break;
        case 11:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__READ(regTmp);
            break;
        case 12:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__READ(regTmp);
            break;
        case 13:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__READ(regTmp);
            break;
        case 14:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__READ(regTmp);
            break;
        case 15:
        *schedType = EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__READ(regTmp);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif

    return status;
}

uint32_t CEDI_SetRateLimit(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t limit)
{
    uint32_t status;
    uint32_t regTmp;


    status = CEDI_SetRateLimitSF(pD);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }
#ifdef __EMAC_REGS__BW_RATE_LIMIT_Q0TO3_MACRO__
    if (CDN_EOK == status) {
        if (0 == IsGem1p09(pD)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Feature not supported- current moduleId:%0x , expected is above:%0x \n",
                    pD->hwCfg.moduleId , GEM_GXL_MODULE_ID_V1 );
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        switch(queueNum){
        case 0:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q0to3), regTmp);
            break;
        case 1:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q0to3), regTmp);
            break;
        case 2:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q0to3), regTmp);
            break;
        case 3:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q0to3), regTmp);
            break;
        case 4:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q4to7), regTmp);
            break;
        case 5:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q4to7), regTmp);
            break;
        case 6:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q4to7), regTmp);
            break;
        case 7:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q4to7), regTmp);
            break;
        case 8:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q8to11), regTmp);
            break;
        case 9:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q8to11), regTmp);
            break;
        case 10:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q8to11), regTmp);
            break;
        case 11:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q8to11), regTmp);
            break;
        case 12:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q12to15), regTmp);
            break;
        case 13:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q12to15), regTmp);
            break;
        case 14:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q12to15), regTmp);
            break;
        case 15:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__MODIFY(regTmp, limit);
            CPS_UncachedWrite32(&(pD->regs->bw_rate_limit_q12to15), regTmp);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }

#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;
}

uint32_t CEDI_GetRateLimit(const CEDI_PrivateData *pD, uint8_t queueNum, uint8_t *limit)
{
    uint32_t status;
    uint32_t regTmp;

    status = CEDI_GetRateLimitSF(pD, limit);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }
#ifdef __EMAC_REGS__BW_RATE_LIMIT_Q0TO3_MACRO__
    if (CDN_EOK == status) {
        if (0 == IsGem1p09(pD)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Feature not supported- current moduleId:%0x , expected is above:%0x \n",
                    pD->hwCfg.moduleId , GEM_GXL_MODULE_ID_V1 );
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        switch(queueNum){
        case 0:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__READ(regTmp);
            break;
        case 1:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__READ(regTmp);
            break;
        case 2:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__READ(regTmp);
            break;
        case 3:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q0to3));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__READ(regTmp);
            break;
        case 4:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__READ(regTmp);
            break;
        case 5:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__READ(regTmp);
            break;
        case 6:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__READ(regTmp);
            break;
        case 7:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q4to7));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__READ(regTmp);
            break;
        case 8:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__READ(regTmp);
            break;
        case 9:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__READ(regTmp);
            break;
        case 10:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__READ(regTmp);
            break;
        case 11:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q8to11));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__READ(regTmp);
            break;
        case 12:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__READ(regTmp);
            break;
        case 13:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__READ(regTmp);
            break;
        case 14:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__READ(regTmp);
            break;
        case 15:
        regTmp = CPS_UncachedRead32(&(pD->regs->bw_rate_limit_q12to15));
        *limit = EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__READ(regTmp);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }

#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;

}

uint32_t CEDI_SetDwrrWeighting(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t dwrrWeighting)
{
    uint32_t status;
    CEDI_TxSchedType schedType = CEDI_TX_SCHED_TYPE_FIXED;

    status = CEDI_SetDwrrWeightingSF(pD);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0 == (CEDI_GetTxQueueScheduler(pD, queueNum, &schedType))) {
            if (schedType != CEDI_TX_SCHED_TYPE_DWRR) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Warning: Wrong scheduler type is set. Change it to \"CEDI_TX_SCHED_TYPE_DWRR\" \n");
            }
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "Warning: Could not read queue scheduler type\n");
        }
        status = CEDI_SetRateLimit(pD, queueNum, dwrrWeighting);
    }

    return status;
}

uint32_t CEDI_SetEtsBandAlloc(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t etsBandAlloc)
{
    uint32_t status;
    CEDI_TxSchedType schedType = CEDI_TX_SCHED_TYPE_FIXED;

    status = CEDI_SetEtsBandAllocSF(pD);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0 == (CEDI_GetTxQueueScheduler(pD, queueNum, &schedType))) {
            if (schedType != CEDI_TX_SCHED_TYPE_ETS){
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Warning: Wrong scheduler type is set. Change it to \"CEDI_TX_SCHED_TYPE_ETS\" \n");
            }
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "Warning: Could not read queue scheduler type\n");
        }
        status = (CEDI_SetRateLimit(pD, queueNum, etsBandAlloc));
    }

    return status;
}

uint32_t CEDI_GetDwrrWeighting(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t *dwrrWeighting)
{
    uint32_t status;
    CEDI_TxSchedType schedType = CEDI_TX_SCHED_TYPE_FIXED;

    status = CEDI_GetDwrrWeightingSF(pD, dwrrWeighting);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to get value from is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0 == (CEDI_GetTxQueueScheduler(pD, queueNum, &schedType))) {
            if (schedType != CEDI_TX_SCHED_TYPE_DWRR) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Warning: \"CEDI_TX_SCHED_TYPE_DWRR\" is not current scheduler type. \n");
            }
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "Warning: Could not read queue scheduler type\n");
        }
        status = CEDI_GetRateLimit(pD, queueNum, dwrrWeighting);
    }

    return status;
}

uint32_t CEDI_GetEtsBandAlloc(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t *etsBandAlloc)
{
    uint32_t status;
    CEDI_TxSchedType schedType = CEDI_TX_SCHED_TYPE_FIXED;

    status = CEDI_GetEtsBandAllocSF(pD, etsBandAlloc);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to get value from is bigger than number of active queues\n");
           status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (0 == (CEDI_GetTxQueueScheduler(pD, queueNum, &schedType))) {
            if (schedType != CEDI_TX_SCHED_TYPE_ETS) {
                vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                        "Warning: \"CEDI_TX_SCHED_TYPE_ETS\" is not current scheduler type. \n");
            }
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n",
                    "Warning: Could not read queue scheduler type\n");
        }
        status = (CEDI_GetRateLimit(pD, queueNum, etsBandAlloc));
    }

    return status;
}

uint32_t CEDI_SetEnstTimeConfig(CEDI_PrivateData *pD, uint8_t queueNum, const CEDI_EnstTimeConfig *enstTimeConfig)
{
    uint32_t status;
    uint32_t regTmp;
    uint8_t queueIdx, txQs;
    volatile uint32_t *startPtr = NULL;
    volatile uint32_t *onPtr = NULL;
    volatile uint32_t *offPtr = NULL;

    status = CEDI_SetEnstTimeConfigSF(pD, enstTimeConfig);

    if (CDN_EOK == status) {
        txQs = pD->txQs;

        if (queueNum >= txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if ((txQs > 8) && (queueNum < (txQs - 8))){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                    "Error: Queue number must bigger than %d\n", txQs - 8);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (enstTimeConfig->startTimeS > 3){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Start time is bigger than maximum supported value: 3\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (enstTimeConfig->startTimeNs >= 0x40000000U){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Start time nano second is bigger than maximum supported value: 0x3FFFFFFF\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (enstTimeConfig->onTime >= 0x20000U){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: On time is bigger than maximum supported value: 0x1FFFF\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (enstTimeConfig->offTime >= 0x20000U){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Off time is bigger than maximum supported value: 0x1FFFF\n");
            status = CDN_EINVAL;
        }
    }


#ifdef __EMAC_REGS__ENST_START_TIME_Q8_MACRO__
    if (CDN_EOK == status) {
        if (IsEnstSupported(pD) == 0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (txQs < 9) {
            queueIdx = queueNum + 8;
        }
        else {
            queueIdx = queueNum + (16 - txQs);
        }

        if (queueIdx >=8) {

            startPtr = enstStartTimeReg[queueIdx - 8];
            addRegBase(pD, &startPtr);

            onPtr = enstOnTimeReg[queueIdx - 8];
            addRegBase(pD, &onPtr);

            offPtr = enstOffTimeReg[queueIdx - 8];
            addRegBase(pD, &offPtr);

            /* Using macros for Q8, since they're all identical. */
            regTmp = CPS_UncachedRead32(startPtr);
            EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__MODIFY(regTmp,
                        enstTimeConfig->startTimeNs);
            EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__MODIFY(regTmp,
                        enstTimeConfig->startTimeS);
            CPS_UncachedWrite32(startPtr, regTmp);

            regTmp = CPS_UncachedRead32(onPtr);
            EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__MODIFY(regTmp,
                        enstTimeConfig->onTime);
            CPS_UncachedWrite32(onPtr, regTmp);

            regTmp = CPS_UncachedRead32(offPtr);
            EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__MODIFY(regTmp,
                        enstTimeConfig->offTime);
            CPS_UncachedWrite32(offPtr, regTmp);

        } else {
            status = CDN_EINVAL;
        }
    }

#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif
    return status;

}

uint32_t CEDI_GetEnstTimeConfig(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_EnstTimeConfig *enstTimeConfig)
{
    uint32_t status;
    uint32_t regTmp;
    uint8_t txQs;
    uint8_t queueIdx;
    volatile uint32_t *startPtr = NULL;
    volatile uint32_t *onPtr = NULL;
    volatile uint32_t *offPtr = NULL;

    status = CEDI_GetEnstTimeConfigSF(pD, enstTimeConfig);

    if (CDN_EOK == status) {
    txQs = pD->txQs;

        if (queueNum >= txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if ((txQs > 8) && (queueNum < (txQs - 8))){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                    "Error: Queue number must bigger than %d\n", txQs - 8);
            status = CDN_EINVAL;
        }
    }

#ifdef __EMAC_REGS__ENST_START_TIME_Q8_MACRO__
    if (CDN_EOK == status) {
        if (IsEnstSupported(pD) == 0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (txQs < 9) {
            queueIdx = queueNum + 8;
        }
        else {
            queueIdx = queueNum + (16 - txQs);
        }

        if (queueIdx >=8) {

            startPtr = enstStartTimeReg[queueIdx - 8];
            addRegBase(pD, &startPtr);

            onPtr = enstOnTimeReg[queueIdx - 8];
            addRegBase(pD, &onPtr);

            offPtr = enstOffTimeReg[queueIdx - 8];
            addRegBase(pD, &offPtr);

            /* Using macros for Q8, since they're all identical. */
            regTmp = CPS_UncachedRead32(startPtr);
            enstTimeConfig->startTimeNs = \
                    EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__READ(regTmp);
            enstTimeConfig->startTimeS = \
                    EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__READ(regTmp);
            regTmp = CPS_UncachedRead32(onPtr);
            enstTimeConfig->onTime = \
                    EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__READ(regTmp);
            regTmp = CPS_UncachedRead32(offPtr);
            enstTimeConfig->offTime = \
                    EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__READ(regTmp);

        } else {
            status = CDN_EINVAL;
        }
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif

    return status;
}

static uint8_t calculateEnstQsIndex(uint8_t txQs, uint8_t qNum)
{
    uint8_t qIndex;

    if (txQs > CEDI_TX_ENST_QUEUES) {
        qIndex = qNum + (CEDI_MAX_TX_QUEUES - txQs);
    } else {
        qIndex = qNum + CEDI_TX_ENST_QUEUES;
    }

    return qIndex;
}

static uint32_t checkQueueNumForEnst(uint8_t txQs, uint8_t qNum)
{
    uint32_t retVal = CDN_EOK;
    uint8_t minTxQs;

    if (txQs > CEDI_TX_ENST_QUEUES) {
        minTxQs = txQs - CEDI_TX_ENST_QUEUES;
        if (qNum < minTxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                    "Error: Queue number must bigger than %d\n", minTxQs);
            retVal = CDN_EINVAL;
        }
    }

    return retVal;
}

uint32_t CEDI_SetEnstEnable(CEDI_PrivateData *pD, uint8_t queue, uint8_t enable)
{
    uint32_t status;
    uint32_t regTmp;
    uint8_t queueIdx, txQs;

    status = CEDI_SetEnstEnableSF(pD, enable);

    if (CDN_EOK == status) {
        txQs = pD->txQs;

        if (queue >= txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        status = checkQueueNumForEnst(txQs, queue);
    }


#ifdef __EMAC_REGS__ENST_CONTROL_MACRO__

    if (CDN_EOK == status) {
        if (IsEnstSupported(pD) == 0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        queueIdx = calculateEnstQsIndex(txQs, queue);

        regTmp = CPS_UncachedRead32(&(pD->regs->enst_control));
        switch (queueIdx){
        case 8U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__MODIFY(regTmp, enable);
            break;
        case 9U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__MODIFY(regTmp, enable);
            break;
        case 10U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__MODIFY(regTmp, enable);
            break;
        case 11U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__MODIFY(regTmp, enable);
            break;
        case 12U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__MODIFY(regTmp, enable);
            break;
        case 13U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__MODIFY(regTmp, enable);
            break;
        case 14U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__MODIFY(regTmp, enable);
            break;
        case 15U:
            EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__MODIFY(regTmp, enable);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    /* to be be backward compatible */
        regTmp |= (uint32_t)!enable << (16 + queue);

        CPS_UncachedWrite32(&(pD->regs->enst_control), regTmp);
    }

#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif

    return status;
}

uint32_t CEDI_GetEnstEnable(CEDI_PrivateData *pD, uint8_t queue, uint8_t *enable)
{
    uint32_t status;
    uint32_t regTmp;
    uint8_t queueIdx, txQs;

    status = CEDI_GetEnstEnableSF(pD, enable);

    if (CDN_EOK == status) {
        txQs = pD->txQs;
        if (queue >= txQs){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Queue number to configure is bigger than number of active queues\n");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        status = checkQueueNumForEnst(txQs, queue);
    }

#ifdef __EMAC_REGS__ENST_CONTROL_MACRO__
    if (CDN_EOK == status) {
        if (IsEnstSupported(pD) == 0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        queueIdx = calculateEnstQsIndex(txQs, queue);

        regTmp = CPS_UncachedRead32(&(pD->regs->enst_control));
        switch (queueIdx){
        case 8U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__READ(regTmp);
            break;
        case 9U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__READ(regTmp);
            break;
        case 10U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__READ(regTmp);
            break;
        case 11U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__READ(regTmp);
            break;
        case 12U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__READ(regTmp);
            break;
        case 13U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__READ(regTmp);
            break;
        case 14U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__READ(regTmp);
            break;
        case 15U:
            *enable = EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__READ(regTmp);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }
#else
    if (CDN_EOK == status) {
        status = CDN_ENOTSUP;
    }
#endif

    return status;
}

/* check, if EnST is supported by core */
uint32_t CEDI_GetEnstSupported(CEDI_PrivateData *pD, uint8_t *supported)
{
    uint32_t status = CEDI_GetEnstSupportedSF(pD, supported);

    if (CDN_EOK == status) {
        *supported = IsEnstSupported(pD);
    }
    return status;
}

uint32_t CEDI_SetCbsIdleSlope(CEDI_PrivateData *pD, uint8_t queueNum, uint32_t idleSlope)
{
    uint32_t status;
    uint32_t reg;
    CEDI_TxSchedType schedType = CEDI_TX_SCHED_TYPE_FIXED;

    status = CEDI_SetCbsIdleSlopeSF(pD);

    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }

        if (pD->hwCfg.exclude_cbs==1) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->txQs==1) {
            status = CDN_EINVAL;
        }

        if (queueNum >= pD->txQs) {
            status = CDN_EINVAL;
        }

        if (queueNum < (pD->txQs - 2)) {
            status = CDN_EINVAL;
        }
    }


    if (CDN_EOK == status) {
        status = CEDI_GetTxQueueScheduler(pD, queueNum, &schedType);
    }

    if (CDN_EOK == status) {
        if (schedType == CEDI_TX_SCHED_TYPE_CBS){
            status = CEDI_SetTxQueueScheduler(pD, queueNum, CEDI_TX_SCHED_TYPE_FIXED);
        }
    }

    if (CDN_EOK == status) {
        reg = 0;
        if (queueNum == (pD->txQs - 2)) {   /* i.e. queue B */
            EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__MODIFY(reg, idleSlope);
            CPS_UncachedWrite32(&(pD->regs->cbs_idleslope_q_b), reg);
        } else {
            if (queueNum == (pD->txQs - 1)) {   /* i.e. queue A */
                EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__MODIFY(reg, idleSlope);
                CPS_UncachedWrite32(&(pD->regs->cbs_idleslope_q_a), reg);
            }
        }

        /* recover CBS scheduler type */
        if (schedType == CEDI_TX_SCHED_TYPE_CBS){
            status = CEDI_SetTxQueueScheduler(pD, queueNum, CEDI_TX_SCHED_TYPE_CBS);
        }
    }

    return status;
}

uint32_t CEDI_GetCbsIdleSlope(CEDI_PrivateData *pD, uint8_t queueNum, uint32_t *idleSlope)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_GetCbsIdleSlopeSF(pD, idleSlope);

    if (CDN_EOK == status) {
        if ((CEDI_MAC_TYPE_EMAC == pD->macType) || (pD->hwCfg.exclude_cbs==1)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if ((pD->txQs==1) || (queueNum >= pD->txQs) ||(queueNum < (pD->txQs - 2))) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum == (pD->txQs - 2)) {   /* i.e. queue B */
            reg = CPS_UncachedRead32(&(pD->regs->cbs_idleslope_q_b));
            *idleSlope = EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__READ(reg);
        } else {
            if (queueNum == (pD->txQs - 1)) {   /* i.e. queue A */
                reg = CPS_UncachedRead32(&(pD->regs->cbs_idleslope_q_a));
                *idleSlope = EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__READ(reg);
            }
        }
    }

    return status;
}


uint32_t CEDI_SetTxThresholdControl(CEDI_PrivateData* pD,
                                   const CEDI_WatermarkLvl* watermarkLvl,
                                   uint8_t queueNum)
{
    uint32_t status;
    uint8_t queueOff;
    uint32_t reg;
    uint8_t high;
    uint8_t low;
    volatile uint32_t* regAddr;


    status = CEDI_SetTxThresholdControlSF(pD, watermarkLvl);

    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
        high = watermarkLvl->high;
        low = watermarkLvl->low;

        if (high <= low) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s",
                    "Error: Wrong watermarks level. High <= Low\n");

            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: Queue number %u is out of configured range. "
                    "Currently number of queues is configured to %u\n", queueNum, pD->txQs);

            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regAddr  = txBuffThresholdCtrl[queueNum / 4U];
        addRegBase(pD, &regAddr);

        queueOff = queueNum % 4U;

        reg = CPS_REG_READ(regAddr);


        // Macros are the same for each register (q03, q47, q8b, qcf)
        if (queueOff == 0U) {
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_0_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_0_LOW_WATERMARK__MODIFY(reg, low);
        } else if (queueOff == 1U) {
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_1_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_1_LOW_WATERMARK__MODIFY(reg, low);
        } else if (queueOff == 2U) {
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_2_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_2_LOW_WATERMARK__MODIFY(reg, low);
        } else {
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_3_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_3_LOW_WATERMARK__MODIFY(reg, low);
        }

        CPS_REG_WRITE(regAddr, reg);
    }

    return status;
}

uint32_t CEDI_GetTxThresholdControl(const CEDI_PrivateData* pD,
                               CEDI_WatermarkLvl* watermarkLvl,
                               uint8_t queueNum)
{
    uint32_t status;
    uint8_t queueOff;
    uint32_t reg;
    uint8_t high;
    uint8_t low;
    volatile uint32_t* regAddr;

    status = CEDI_GetTxThresholdControlSF(pD, watermarkLvl);

    if (CDN_EOK == status) {
        status = checkFunctionSupport(pD, IsGem1p13, __func__);
    }

    if (CDN_EOK == status) {
        if (queueNum >= pD->txQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "Error: Queue number %u is out of configured range. "
                    "Currently number of queues is configured to %u\n", queueNum, pD->txQs);

            status = CDN_EINVAL;
        }
    }


    if (CDN_EOK == status) {
        regAddr  = txBuffThresholdCtrl[queueNum / 4U];
        addRegBase(pD, &regAddr);

        queueOff = queueNum % 4U;

        reg = CPS_REG_READ(regAddr);

        // Macros are the same for each register (q03, q47, q8b, qcf)
        if (queueOff == 0U) {
            high = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_0_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_0_LOW_WATERMARK__READ(reg);
        } else if (queueOff == 1U) {
            high = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_1_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_1_LOW_WATERMARK__READ(reg);
        } else if (queueOff == 2U) {
            high = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_2_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_2_LOW_WATERMARK__READ(reg);
        } else {
            high = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_3_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__TX_DESCR_RD_BUF_CTL_Q03__Q_3_LOW_WATERMARK__READ(reg);
        }

        watermarkLvl->high = high;
        watermarkLvl->low = low;
    }

    return status;
}

static void setTxTestPatternMode(CEDI_TestPatternMode patternMode, uint32_t* regVal)
{
    /* Clear pattern mode bits */
     *regVal &= ~(EMAC_REGS__USX_TEST_CONTROL__TX_SQW_EN__MASK      |
                  EMAC_REGS__USX_TEST_CONTROL__TX_PRBS9_EN__MASK    |
                  EMAC_REGS__USX_TEST_CONTROL__TX_PRBS31_EN__MASK   |
                  EMAC_REGS__USX_TEST_CONTROL__TX_TST_EN__MASK      |
                  EMAC_REGS__USX_TEST_CONTROL__TX_TST_DAT_SEL__MASK |
                  EMAC_REGS__USX_TEST_CONTROL__TX_SCR_IDLE_EN__MASK);

    /* for CEDI_NORMAL_OPERATION need not set any bits */
    if (patternMode != CEDI_NORMAL_OPERATION) {
        if (patternMode == CEDI_PRBS_9) {
            EMAC_REGS__USX_TEST_CONTROL__TX_PRBS9_EN__SET(*regVal);
        } else if (patternMode == CEDI_SQUARE_WAVE) {
            EMAC_REGS__USX_TEST_CONTROL__TX_SQW_EN__SET(*regVal);
        } else if (patternMode == CEDI_PRBS_31) {
            EMAC_REGS__USX_TEST_CONTROL__TX_PRBS31_EN__SET(*regVal);
        } else if (patternMode == CEDI_SCRAMBLED_ZERO) {
            EMAC_REGS__USX_TEST_CONTROL__TX_TST_EN__SET(*regVal);
            EMAC_REGS__USX_TEST_CONTROL__TX_TST_DAT_SEL__SET(*regVal);
        } else if (patternMode == CEDI_SCRAMBLED_IDLE) {
            EMAC_REGS__USX_TEST_CONTROL__TX_TST_EN__SET(*regVal);
            EMAC_REGS__USX_TEST_CONTROL__TX_SCR_IDLE_EN__SET(*regVal);
        } else {
            /* condition for CEDI_SCRAMBLED_LOCAL_FAULT */
            EMAC_REGS__USX_TEST_CONTROL__TX_TST_EN__SET(*regVal);
        }
    }
}

uint32_t CEDI_SetPcs25gTxTestPatternMode(CEDI_PrivateData* pD, CEDI_TestPatternMode patternMode)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;
    uint32_t mask;

    status = CEDI_SetPcs25gTxTestPatternMSF(pD, patternMode);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    /* check if PCS25G is supported */
    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        if (pD->isTxDatapathEnabled) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Cannot use %s when Tx datapath is enabled. "
                    "Please, disable it first.\n", __func__);
            status = CDN_EIO;
        }
    }

    if (CDN_EOK == status) {

        regAddr = &(pD->regs->usx_test_control);
        regVal = CPS_REG_READ(regAddr);

        /* check if PCS25G is in CEDI_TEST_PATTERN_MODE */
        mask = EMAC_REGS__USX_TEST_CONTROL__MII_LPBK_EN__MASK
             | EMAC_REGS__USX_TEST_CONTROL__SCR_LPBK_EN__MASK;

        if ((regVal & mask) != (uint8_t)CEDI_NORMAL_OPERATION) {
            status = CDN_ENOTSUP;
        } else {
            setTxTestPatternMode(patternMode, &regVal);
            CPS_REG_WRITE(regAddr, regVal);
        }
    }

    return status;
}

uint32_t CEDI_GetPcs25gTxTestPatternMode(const CEDI_PrivateData* pD, CEDI_TestPatternMode* patternMode)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPcs25gTxTestPatternMSF(pD, patternMode);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->usx_test_control));

        if (EMAC_REGS__USX_TEST_CONTROL__TX_PRBS9_EN__READ(regVal) == 1U) {
            *patternMode = CEDI_PRBS_9;
        } else if (EMAC_REGS__USX_TEST_CONTROL__TX_PRBS31_EN__READ(regVal) == 1U) {
            *patternMode = CEDI_PRBS_31;
        } else if (EMAC_REGS__USX_TEST_CONTROL__TX_SQW_EN__READ(regVal) == 1U) {
            *patternMode = CEDI_SQUARE_WAVE;
        } else if (EMAC_REGS__USX_TEST_CONTROL__TX_TST_EN__READ(regVal) == 1U) {

            if (EMAC_REGS__USX_TEST_CONTROL__TX_TST_DAT_SEL__READ(regVal) == 1U) {
                *patternMode = CEDI_SCRAMBLED_ZERO;
            } else if (EMAC_REGS__USX_TEST_CONTROL__TX_SCR_IDLE_EN__READ(regVal) == 1U) {
                *patternMode = CEDI_SCRAMBLED_IDLE;
            } else {
                *patternMode = CEDI_SCRAMBLED_LOCAL_FAULT;
            }
        } else {
            *patternMode = CEDI_NORMAL_OPERATION;
        }
    }

    return status;
}

uint32_t CEDI_SetPcs25gTxTestPatternSeed(CEDI_PrivateData* pD,
                                         CEDI_TestSeedReg testSeedReg,
                                         const CEDI_TestPatternSeed* testPatternSeed)
{
    uint32_t status;
    /* address for lowest part of test seed (bits [31:0])*/
    volatile uint32_t* lowRegAddr;
    /* address for highest part of test seed (bits [57:32])*/
    volatile uint32_t* highRegAddr;

    status = CEDI_SetPcs25gTxTestPatternSSF(pD, testSeedReg, testPatternSeed);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        if (pD->isTxDatapathEnabled) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Cannot use %s when Tx datapath is enabled. "
                    "Please, disable it first.\n", __func__);
            status = CDN_EIO;
        }
    }

    if (CDN_EOK == status) {

        if (testSeedReg == CEDI_TEST_SEED_A) {
            lowRegAddr = &(pD->regs->usx_test_seed_a_lower);
            highRegAddr = &(pD->regs->usx_test_seed_a_upper);
        } else {
            lowRegAddr = &(pD->regs->usx_test_seed_b_lower);
            highRegAddr = &(pD->regs->usx_test_seed_b_upper);
        }

        CPS_REG_WRITE(lowRegAddr, testPatternSeed->seedLow);
        CPS_REG_WRITE(highRegAddr, testPatternSeed->seedUpper);
    }

    return status;
}

uint32_t CEDI_GetPcs25gTxTestPatternSeed(const CEDI_PrivateData* pD,
                                        CEDI_TestSeedReg testSeedReg,
                                        CEDI_TestPatternSeed* testPatternSeed)
{
    uint32_t status;
    /* address for lowest part of test seed (bits [31:0])*/
    volatile uint32_t* lowRegAddr;
    /* address for highest part of test seed (bits [57:32])*/
    volatile uint32_t* highRegAddr;

    status = CEDI_GetPcs25gTxTestPatternSSF(pD, testSeedReg, testPatternSeed);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {

        if (testSeedReg == CEDI_TEST_SEED_A) {
            lowRegAddr = &(pD->regs->usx_test_seed_a_lower);
            highRegAddr = &(pD->regs->usx_test_seed_a_upper);
        } else {
            lowRegAddr = &(pD->regs->usx_test_seed_b_lower);
            highRegAddr = &(pD->regs->usx_test_seed_b_upper);
        }

        testPatternSeed->seedLow = CPS_REG_READ(lowRegAddr);
        testPatternSeed->seedUpper = CPS_REG_READ(highRegAddr);
    }

    return status;
}

uint32_t CEDI_SetPcs25gTxScrBypassEnable(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_SetPcs25gTxScrBypassEnaSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        if (isPcs25gDatapathsEnabled(pD, __func__)) {
            status = CDN_EIO;
        }
    }

    if (status == CDN_EOK) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        if (enable) {
            EMAC_REGS__USX_CONTROL_REGISTER__TX_SCR_BYPASS__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__TX_SCR_BYPASS__CLR(regVal);
        }
        CPS_REG_WRITE(regAddr, regVal);
    }

    return status;
}

uint32_t CEDI_GetPcs25gTxScrBypassEnable(CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPcs25gTxScrBypassEnaSF(pD, enable);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        regVal = CPS_REG_READ(&(pD->regs->usx_control_register));
        *enable = EMAC_REGS__USX_CONTROL_REGISTER__TX_SCR_BYPASS__READ(regVal) != 0U;
    }

    return status;
}

uint32_t CEDI_SetPcs25gTxDatapathEnable(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_SetPcs25gTxDatapathEnabSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        if (enable) {
            EMAC_REGS__USX_CONTROL_REGISTER__TX_DATAPATH_EN__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__TX_DATAPATH_EN__CLR(regVal);
        }
        CPS_REG_WRITE(regAddr, regVal);
        pD->isTxDatapathEnabled = enable;
    }

    return status;
}

uint32_t CEDI_GetPcs25gTxDatapathEnable(CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status = CEDI_GetPcs25gTxDatapathEnabSF(pD, enable);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        *enable = pD->isTxDatapathEnabled;
    }

    return status;
}
