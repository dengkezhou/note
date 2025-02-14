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
 * edd_rx.c
 * Ethernet DMA MAC Driver
 *
 * Rx-related functions source file
 *****************************************************************************/

#include <common.h>
#include <command.h>
#include <cache.h>

#include "cdn_stdint.h"
#include "cdn_errno.h"
#include "cdn_log.h"
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

/* hold offsets to specific address registers, relative to regbase */
volatile uint32_t* const specAddBottomReg[36] = {
    CEDI_RegOff(spec_add1_bottom),
    CEDI_RegOff(spec_add2_bottom),
    CEDI_RegOff(spec_add3_bottom),
    CEDI_RegOff(spec_add4_bottom),
    CEDI_RegOff(spec_add5_bottom),
    CEDI_RegOff(spec_add6_bottom),
    CEDI_RegOff(spec_add7_bottom),
    CEDI_RegOff(spec_add8_bottom),
    CEDI_RegOff(spec_add9_bottom),
    CEDI_RegOff(spec_add10_bottom),
    CEDI_RegOff(spec_add11_bottom),
    CEDI_RegOff(spec_add12_bottom),
    CEDI_RegOff(spec_add13_bottom),
    CEDI_RegOff(spec_add14_bottom),
    CEDI_RegOff(spec_add15_bottom),
    CEDI_RegOff(spec_add16_bottom),
    CEDI_RegOff(spec_add17_bottom),
    CEDI_RegOff(spec_add18_bottom),
    CEDI_RegOff(spec_add19_bottom),
    CEDI_RegOff(spec_add20_bottom),
    CEDI_RegOff(spec_add21_bottom),
    CEDI_RegOff(spec_add22_bottom),
    CEDI_RegOff(spec_add23_bottom),
    CEDI_RegOff(spec_add24_bottom),
    CEDI_RegOff(spec_add25_bottom),
    CEDI_RegOff(spec_add26_bottom),
    CEDI_RegOff(spec_add27_bottom),
    CEDI_RegOff(spec_add28_bottom),
    CEDI_RegOff(spec_add29_bottom),
    CEDI_RegOff(spec_add30_bottom),
    CEDI_RegOff(spec_add31_bottom),
    CEDI_RegOff(spec_add32_bottom),
    CEDI_RegOff(spec_add33_bottom),
    CEDI_RegOff(spec_add34_bottom),
    CEDI_RegOff(spec_add35_bottom),
    CEDI_RegOff(spec_add36_bottom)
};

static volatile uint32_t* const specAddTopReg[36] = {
    CEDI_RegOff(spec_add1_top),
    CEDI_RegOff(spec_add2_top),
    CEDI_RegOff(spec_add3_top),
    CEDI_RegOff(spec_add4_top),
    CEDI_RegOff(spec_add5_top),
    CEDI_RegOff(spec_add6_top),
    CEDI_RegOff(spec_add7_top),
    CEDI_RegOff(spec_add8_top),
    CEDI_RegOff(spec_add9_top),
    CEDI_RegOff(spec_add10_top),
    CEDI_RegOff(spec_add11_top),
    CEDI_RegOff(spec_add12_top),
    CEDI_RegOff(spec_add13_top),
    CEDI_RegOff(spec_add14_top),
    CEDI_RegOff(spec_add15_top),
    CEDI_RegOff(spec_add16_top),
    CEDI_RegOff(spec_add17_top),
    CEDI_RegOff(spec_add18_top),
    CEDI_RegOff(spec_add19_top),
    CEDI_RegOff(spec_add20_top),
    CEDI_RegOff(spec_add21_top),
    CEDI_RegOff(spec_add22_top),
    CEDI_RegOff(spec_add23_top),
    CEDI_RegOff(spec_add24_top),
    CEDI_RegOff(spec_add25_top),
    CEDI_RegOff(spec_add26_top),
    CEDI_RegOff(spec_add27_top),
    CEDI_RegOff(spec_add28_top),
    CEDI_RegOff(spec_add29_top),
    CEDI_RegOff(spec_add30_top),
    CEDI_RegOff(spec_add31_top),
    CEDI_RegOff(spec_add32_top),
    CEDI_RegOff(spec_add33_top),
    CEDI_RegOff(spec_add34_top),
    CEDI_RegOff(spec_add35_top),
    CEDI_RegOff(spec_add36_top)
};

static volatile uint32_t* const receivePtrReg[15] = {
    CEDI_RegOff(receive_q1_ptr),
    CEDI_RegOff(receive_q2_ptr),
    CEDI_RegOff(receive_q3_ptr),
    CEDI_RegOff(receive_q4_ptr),
    CEDI_RegOff(receive_q5_ptr),
    CEDI_RegOff(receive_q6_ptr),
    CEDI_RegOff(receive_q7_ptr),
    CEDI_RegOff(receive_q8_ptr),
    CEDI_RegOff(receive_q9_ptr),
    CEDI_RegOff(receive_q10_ptr),
    CEDI_RegOff(receive_q11_ptr),
    CEDI_RegOff(receive_q12_ptr),
    CEDI_RegOff(receive_q13_ptr),
    CEDI_RegOff(receive_q14_ptr),
    CEDI_RegOff(receive_q15_ptr)
};

/* hold offsets to type_2 compare registers, relative to regbase */
static volatile uint32_t* const type2CompareWord0Reg[32] = {
    CEDI_RegOff(type2_compare_0_word_0),
    CEDI_RegOff(type2_compare_1_word_0),
    CEDI_RegOff(type2_compare_2_word_0),
    CEDI_RegOff(type2_compare_3_word_0),
    CEDI_RegOff(type2_compare_4_word_0),
    CEDI_RegOff(type2_compare_5_word_0),
    CEDI_RegOff(type2_compare_6_word_0),
    CEDI_RegOff(type2_compare_7_word_0),
    CEDI_RegOff(type2_compare_8_word_0),
    CEDI_RegOff(type2_compare_9_word_0),
    CEDI_RegOff(type2_compare_10_word_0),
    CEDI_RegOff(type2_compare_11_word_0),
    CEDI_RegOff(type2_compare_12_word_0),
    CEDI_RegOff(type2_compare_13_word_0),
    CEDI_RegOff(type2_compare_14_word_0),
    CEDI_RegOff(type2_compare_15_word_0),
    CEDI_RegOff(type2_compare_16_word_0),
    CEDI_RegOff(type2_compare_17_word_0),
    CEDI_RegOff(type2_compare_18_word_0),
    CEDI_RegOff(type2_compare_19_word_0),
    CEDI_RegOff(type2_compare_20_word_0),
    CEDI_RegOff(type2_compare_21_word_0),
    CEDI_RegOff(type2_compare_22_word_0),
    CEDI_RegOff(type2_compare_23_word_0),
    CEDI_RegOff(type2_compare_24_word_0),
    CEDI_RegOff(type2_compare_25_word_0),
    CEDI_RegOff(type2_compare_26_word_0),
    CEDI_RegOff(type2_compare_27_word_0),
    CEDI_RegOff(type2_compare_28_word_0),
    CEDI_RegOff(type2_compare_29_word_0),
    CEDI_RegOff(type2_compare_30_word_0),
    CEDI_RegOff(type2_compare_31_word_0)
};

static volatile uint32_t* const type2CompareWord1Reg[32] = {
    CEDI_RegOff(type2_compare_0_word_1),
    CEDI_RegOff(type2_compare_1_word_1),
    CEDI_RegOff(type2_compare_2_word_1),
    CEDI_RegOff(type2_compare_3_word_1),
    CEDI_RegOff(type2_compare_4_word_1),
    CEDI_RegOff(type2_compare_5_word_1),
    CEDI_RegOff(type2_compare_6_word_1),
    CEDI_RegOff(type2_compare_7_word_1),
    CEDI_RegOff(type2_compare_8_word_1),
    CEDI_RegOff(type2_compare_9_word_1),
    CEDI_RegOff(type2_compare_10_word_1),
    CEDI_RegOff(type2_compare_11_word_1),
    CEDI_RegOff(type2_compare_12_word_1),
    CEDI_RegOff(type2_compare_13_word_1),
    CEDI_RegOff(type2_compare_14_word_1),
    CEDI_RegOff(type2_compare_15_word_1),
    CEDI_RegOff(type2_compare_16_word_1),
    CEDI_RegOff(type2_compare_17_word_1),
    CEDI_RegOff(type2_compare_18_word_1),
    CEDI_RegOff(type2_compare_19_word_1),
    CEDI_RegOff(type2_compare_20_word_1),
    CEDI_RegOff(type2_compare_21_word_1),
    CEDI_RegOff(type2_compare_22_word_1),
    CEDI_RegOff(type2_compare_23_word_1),
    CEDI_RegOff(type2_compare_24_word_1),
    CEDI_RegOff(type2_compare_25_word_1),
    CEDI_RegOff(type2_compare_26_word_1),
    CEDI_RegOff(type2_compare_27_word_1),
    CEDI_RegOff(type2_compare_28_word_1),
    CEDI_RegOff(type2_compare_29_word_1),
    CEDI_RegOff(type2_compare_30_word_1),
    CEDI_RegOff(type2_compare_31_word_1)
};

static volatile uint32_t* const type1ScreeningReg[16] = {
    CEDI_RegOff(screening_type_1_register_0),
    CEDI_RegOff(screening_type_1_register_1),
    CEDI_RegOff(screening_type_1_register_2),
    CEDI_RegOff(screening_type_1_register_3),
    CEDI_RegOff(screening_type_1_register_4),
    CEDI_RegOff(screening_type_1_register_5),
    CEDI_RegOff(screening_type_1_register_6),
    CEDI_RegOff(screening_type_1_register_7),
    CEDI_RegOff(screening_type_1_register_8),
    CEDI_RegOff(screening_type_1_register_9),
    CEDI_RegOff(screening_type_1_register_10),
    CEDI_RegOff(screening_type_1_register_11),
    CEDI_RegOff(screening_type_1_register_12),
    CEDI_RegOff(screening_type_1_register_13),
    CEDI_RegOff(screening_type_1_register_14),
    CEDI_RegOff(screening_type_1_register_15)
};

static volatile uint32_t* const type2ScreeningReg[16] = {
    CEDI_RegOff(screening_type_2_register_0),
    CEDI_RegOff(screening_type_2_register_1),
    CEDI_RegOff(screening_type_2_register_2),
    CEDI_RegOff(screening_type_2_register_3),
    CEDI_RegOff(screening_type_2_register_4),
    CEDI_RegOff(screening_type_2_register_5),
    CEDI_RegOff(screening_type_2_register_6),
    CEDI_RegOff(screening_type_2_register_7),
    CEDI_RegOff(screening_type_2_register_8),
    CEDI_RegOff(screening_type_2_register_9),
    CEDI_RegOff(screening_type_2_register_10),
    CEDI_RegOff(screening_type_2_register_11),
    CEDI_RegOff(screening_type_2_register_12),
    CEDI_RegOff(screening_type_2_register_13),
    CEDI_RegOff(screening_type_2_register_14),
    CEDI_RegOff(screening_type_2_register_15)
};

static volatile uint32_t* const type2ScreeningEthertypeReg[8] = {
    CEDI_RegOff(screening_type_2_ethertype_reg_0),
    CEDI_RegOff(screening_type_2_ethertype_reg_1),
    CEDI_RegOff(screening_type_2_ethertype_reg_2),
    CEDI_RegOff(screening_type_2_ethertype_reg_3),
    CEDI_RegOff(screening_type_2_ethertype_reg_4),
    CEDI_RegOff(screening_type_2_ethertype_reg_5),
    CEDI_RegOff(screening_type_2_ethertype_reg_6),
    CEDI_RegOff(screening_type_2_ethertype_reg_7),
};


static volatile uint32_t* const rxQueueFlushReg[16] = {
    CEDI_RegOff(rx_q0_flush),
    CEDI_RegOff(rx_q1_flush),
    CEDI_RegOff(rx_q2_flush),
    CEDI_RegOff(rx_q3_flush),
    CEDI_RegOff(rx_q4_flush),
    CEDI_RegOff(rx_q5_flush),
    CEDI_RegOff(rx_q6_flush),
    CEDI_RegOff(rx_q7_flush),
    CEDI_RegOff(rx_q8_flush),
    CEDI_RegOff(rx_q9_flush),
    CEDI_RegOff(rx_q10_flush),
    CEDI_RegOff(rx_q11_flush),
    CEDI_RegOff(rx_q12_flush),
    CEDI_RegOff(rx_q13_flush),
    CEDI_RegOff(rx_q14_flush),
    CEDI_RegOff(rx_q15_flush),
};

static volatile uint32_t* const scr2RateLimitReg[16] = {
    CEDI_RegOff(scr2_reg0_rate_limit),
    CEDI_RegOff(scr2_reg1_rate_limit),
    CEDI_RegOff(scr2_reg2_rate_limit),
    CEDI_RegOff(scr2_reg3_rate_limit),
    CEDI_RegOff(scr2_reg4_rate_limit),
    CEDI_RegOff(scr2_reg5_rate_limit),
    CEDI_RegOff(scr2_reg6_rate_limit),
    CEDI_RegOff(scr2_reg7_rate_limit),
    CEDI_RegOff(scr2_reg8_rate_limit),
    CEDI_RegOff(scr2_reg9_rate_limit),
    CEDI_RegOff(scr2_reg10_rate_limit),
    CEDI_RegOff(scr2_reg11_rate_limit),
    CEDI_RegOff(scr2_reg12_rate_limit),
    CEDI_RegOff(scr2_reg13_rate_limit),
    CEDI_RegOff(scr2_reg14_rate_limit),
    CEDI_RegOff(scr2_reg15_rate_limit),
};

static volatile uint32_t* const rxBuffThresholdCtrl[4] = {
        CEDI_RegOff(rx_descr_rd_buf_ctl_q03),
        CEDI_RegOff(rx_descr_rd_buf_ctl_q47),
        CEDI_RegOff(rx_descr_rd_buf_ctl_q8b),
        CEDI_RegOff(rx_descr_rd_buf_ctl_qcf),
};


/******************************************************************************
 * Private Driver functions
 *****************************************************************************/
static void getNumScreenRegs(const CEDI_PrivateData *pD, CEDI_NumScreeners *regNums)
{
    regNums->type1ScrRegs = pD->hwCfg.num_type1_screeners;
    regNums->type2ScrRegs = pD->hwCfg.num_type2_screeners;
    regNums->ethtypeRegs = pD->hwCfg.num_scr2_ethtype_regs;
    regNums->compareRegs = pD->hwCfg.num_scr2_compare_regs;
}

/* check if queue is used in screening, if it used then disable screening for that queue */
static uint32_t QueueCheckAndDisableScreening(CEDI_PrivateData *pD, uint8_t queueIdx)
{
    uint8_t i;
    CEDI_NumScreeners numScreeners;
    CEDI_T1Screen t1S;
    CEDI_T2Screen t2S;
    uint32_t status = CDN_EOK;

    getNumScreenRegs(pD, &numScreeners);

    for (i = 0; i < numScreeners.type1ScrRegs; i++){
        status = CEDI_GetType1ScreenReg(pD, i, &t1S);
        if (CDN_EOK == status) {
            if ((queueIdx == t1S.qNum) && (t1S.udpEnable || t1S.dstcEnable)){
                t1S.udpEnable = 0;
                t1S.dstcEnable = 0;
                status = CEDI_SetType1ScreenReg(pD, i, &t1S);
            }
        }

        if (CDN_EOK != status) {
            break;
        }
    }

    if (CDN_EOK == status) {
        for (i = 0; i < numScreeners.type2ScrRegs; i++){
            status = CEDI_GetType2ScreenReg(pD, i, &t2S);
            if (CDN_EOK == status) {
                if ((queueIdx == t2S.qNum) && (t2S.vlanEnable || t2S.eTypeEnable
                                               || t2S.compAEnable || t2S.compBEnable
                                               || t2S.compCEnable)){
                    t2S.vlanEnable = 0;
                    t2S.eTypeEnable = 0;
                    t2S.compAEnable = 0;
                    t2S.compBEnable = 0;
                    t2S.compCEnable = 0;
                    status = CEDI_SetType2ScreenReg(pD, i, &t2S);
                }
            }
            if (CDN_EOK != status) {
                 break;
            }
        }
    }

    return status;
}

void setRxQueueDisableBit(CEDI_PrivateData *pD, uint8_t queue, uint8_t disable)
{
    if (queue > 0) {
    uint32_t regTmp;
    volatile uint32_t *regPtr = NULL;

    regPtr = receivePtrReg[queue - 1];
    addRegBase(pD, &regPtr);
    regTmp = CPS_UncachedRead32(regPtr);
    EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__MODIFY(regTmp, disable);
    CPS_UncachedWrite32(regPtr, regTmp);
    }
}

static void getJumboFrameRxMaxLen(CEDI_PrivateData *pD, uint16_t *length)
{

    *length=EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__READ(
                                CPS_UncachedRead32(&(pD->regs->jumbo_max_length)));

}

static void get1536ByteFramesRx(CEDI_PrivateData *pD, uint8_t *enable)
{
    *enable= EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__READ(
                                       CPS_UncachedRead32(&(pD->regs->network_config)));
}

/******************************************************************************
 * Driver API functions
 *****************************************************************************/

uint32_t CEDI_GetJumboFrameRxMaxLen(CEDI_PrivateData *pD, uint16_t *length)
{
    uint32_t status = CEDI_GetJumboFrameRxMaxLenSF(pD, length);

    if (CDN_EOK == status) {
        getJumboFrameRxMaxLen(pD, length);
    }
    return status;
}

uint32_t CEDI_Get1536ByteFramesRx(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_Get1536ByteFramesRxSF(pD, enable);

    if (CDN_EOK == status) {
        get1536ByteFramesRx(pD, enable);
    }

    return status;
}

uint32_t CEDI_CalcMaxRxFrameSize(CEDI_PrivateData *pD, uint32_t *maxSize) {
    uint32_t status;
    uint16_t ram_word_size, ram_addr_bits;
    uint32_t ram_size_shift, ram_size, max_size, tmp;
    uint8_t enabled = 0;
    uint16_t length;

    status = CEDI_CalcMaxRxFrameSizeSF(pD, maxSize);

    if (CDN_EOK == status) {
        getJumboFramesRx(pD, &enabled);

        if (0 != enabled) {
            getJumboFrameRxMaxLen(pD, &length);
            max_size = length;
        } else {
            get1536ByteFramesRx(pD, &enabled);
            if (0 != enabled) {
                max_size = 1536;
            } else {
                max_size = 1518;
            }
        }
    }

    if (CDN_EOK == status) {
        if (CDN_EOK != CEDI_GetRxPartialStFwd(pD, &tmp, &enabled)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
    if ((!enabled) && pD->hwCfg.rx_pkt_buffer)
    {
            // What is word size of SRAM in bytes
            ram_word_size = (pD->hwCfg.rx_pbuf_data >> 1)+1;
            ram_addr_bits = pD->hwCfg.rx_pbuf_addr;
            ram_size_shift = (uint32_t)ram_addr_bits + (uint32_t)ram_word_size + 1;

            if(ram_size_shift < 32)
            {
                ram_size = (1<<ram_size_shift) - 96;
                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "RAM size = %u\n", ram_size);
            } else {
                status = CDN_EINVAL;
            }

            if (CDN_EOK == status) {
                if (ram_size<max_size) {
                    max_size = ram_size;
                }
            }
        }
        if (CDN_EOK == status) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Max Rx frame size = %u\n", max_size);

            *maxSize = max_size;
        }
    }
    return status;
}

uint32_t CEDI_AddRxBuf(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BuffAddr *buf, uint8_t init)
{
    uint32_t status;
    uint32_t tmp, bufLenWords;
    CEDI_RxQueue *rxQ = NULL;
    unsigned int regData = 0;

    status = CEDI_AddRxBufSF(pD, buf, init);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: Invalid Rx queue number: %u\n", queueNum);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if ((buf->vAddr == 0U) || (buf->pAddr == 0U)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: NULL buf parameter");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        rxQ = &(pD->rxQueue[queueNum]);

        if (rxQ->numRxBufs>=((pD->cfg).rxQLen[queueNum])) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Rx descriptor list full");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        /* alignment checking */
        switch (pD->cfg.dmaBusWidth) {
        case CEDI_DMA_BUS_WIDTH_32:
            tmp = 4; break;
        case CEDI_DMA_BUS_WIDTH_64:
            tmp = 8; break;
        case CEDI_DMA_BUS_WIDTH_128:
            tmp = 16; break;
        default: tmp = 4; break;
        }
        if (0 != ((buf->pAddr)%tmp)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Rx buffer not word-aligned");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        /* save virtual address */
        *(rxQ->rxEndVA) = buf->vAddr;

        bufLenWords = (uint32_t)(pD->cfg.rxBufLength[queueNum])<<4;
        if (0 != init) {
            for (tmp=0; tmp<bufLenWords; tmp++) {

                CPS_UncachedWrite32((uintptrToPtrU32(buf->vAddr))+tmp, 0);
            }
        }

        /* clear wrap & used on old end, add new buffer */
        CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[0]),
                                buf->pAddr & CEDI_RXD_ADDR_MASK);
        /* upper 32 bits if 64 bit addressing */
        if (0 != pD->cfg.dmaAddrBusWidth) {
#ifdef CEDI_64B_COMPILE
            /* 64-bit addressing */
            CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[2]),
                                 (buf->pAddr & 0xFFFFFFFF00000000)>>32);

	EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MODIFY(regData, (buf->pAddr & 0xFFFFFFFF00000000)>>32);
	CPS_UncachedWrite32(&(pD->regs->upper_rx_q_base_addr), regData);
#else
            /* 32-bit addressing */
                /* include only for test use */
                /* copy in faked upper 32 bits for testing in 32-bit env. */
            CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[2]),
                                 pD->cfg.upper32BuffRxQAddr);
    #endif
        }

        /* put known pattern into word[1] for debugging */
        CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[1]), CEDI_RXD_EMPTY);

        /* inc end & stop pointer */
        moveRxDescAddr(&(rxQ->rxDescEnd), pD->rxDescriptorSize[queueNum]);
        rxQ->rxDescStop = rxQ->rxDescEnd;

        /* inc VA end & stop pointers & buffer count */
        rxQ->rxEndVA++;
        rxQ->rxStopVA++;
        *(rxQ->rxStopVA) = 0;
        rxQ->numRxBufs++;

        /* write new end(-stop) descriptor */
        CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[0]),
                                 CEDI_RXD_WRAP | CEDI_RXD_USED );

    }
    return status;
}

uint32_t CEDI_NumRxBufs(const CEDI_PrivateData *pD, uint8_t queueNum, uint16_t *numBufs)
{
    uint32_t status = CEDI_NumRxBufsSF(pD, numBufs);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        *numBufs = (pD->rxQueue[queueNum]).numRxBufs;
    }
    return status;
}

uint32_t CEDI_NumRxUsed(CEDI_PrivateData *pD, uint8_t queueNum)
{
    uint32_t status;
    uint32_t retVal = 1U;
    uint32_t tmp, thisWd, count=0;
    CEDI_RxDesc *thisDesc;
    CEDI_RxQueue *rxQ;

    status = CEDI_NumRxUsedSF(pD);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
                retVal = 0;
        }
    } else {
        retVal = 0;
    }

    if (retVal == 1)
    {
        rxQ = &(pD->rxQueue[queueNum]);
        /* count forward from tail, until used not set */
        thisDesc =  rxQ->rxDescTail;
        for (tmp = 0; tmp<rxQ->numRxBufs; tmp++)
        {
            thisWd = CPS_UncachedRead32(&(thisDesc->word[0]));
            if (0 != (thisWd & CEDI_RXD_USED)) {
                count++;
            } else {
                break;
            }
            if (0 != (thisWd & CEDI_RXD_WRAP)) {
                thisDesc = rxQ->rxDescStart;
            } else {
                moveRxDescAddr(&thisDesc, (pD->rxDescriptorSize[queueNum]));
            }
        }
        retVal = count;
    }
    return retVal;
}

uint32_t CEDI_ReadRxBuf(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BuffAddr *buf,
                        uint8_t init, CEDI_RxDescData *descData)
{
    uint32_t status;
    uint32_t tmp, bufLenWords, descWd0;
    CEDI_BuffAddr oldbuf;
    uint8_t wdNum, tailWrap;
    uint32_t tsLowerWd, tsUpperWd;
    CEDI_RxQueue *rxQ;
    unsigned int regData = 0;

    status = CEDI_ReadRxBufSF(pD, buf, init, descData);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: Invalid Rx queue number - %u\n", queueNum);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if ((buf->vAddr==0) || (buf->pAddr==0)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: NULL buf address");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        /* alignment checking for new buffer */
        switch (pD->cfg.dmaBusWidth) {
        case CEDI_DMA_BUS_WIDTH_32:
            tmp = 4; break;
        case CEDI_DMA_BUS_WIDTH_64:
            tmp = 8; break;
        case CEDI_DMA_BUS_WIDTH_128:
            tmp = 16; break;
        default: tmp = 4; break;
        }
        if (0 != ((buf->pAddr)%tmp)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s\n", "Error: Rx buffer not word-aligned");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        rxQ = &(pD->rxQueue[queueNum]);

        /* get first descriptor & test used bit */
        descWd0 = CPS_UncachedRead32(&(rxQ->rxDescTail->word[0]));

        if (0 != (descWd0 & CEDI_RXD_USED)) {
            /* new data received - read & process descriptor */

            /* get old physical address */
            oldbuf.pAddr = (uintptr_t)descWd0 & CEDI_RXD_ADDR_MASK;
            /* upper 32 bits if 64 bit addressing */
            if (0 != pD->cfg.dmaAddrBusWidth) {
                oldbuf.pAddr |= ((uint64_t)CPS_UncachedRead32(
                                            &(rxQ->rxDescTail->word[2])))<<32;
            }

            /* get old virtual address & clear from list */
            oldbuf.vAddr = *(rxQ->rxTailVA);
            *(rxQ->rxTailVA) = 0;

            /* save new virtual address */
            *(rxQ->rxStopVA) = buf->vAddr;

            bufLenWords = (uint32_t)(pD->cfg.rxBufLength[queueNum])<<4;
            if (0 != init) {
                for (tmp=0; tmp<bufLenWords; tmp++) {
                    CPS_UncachedWrite32(uintptrToPtrU32((buf->vAddr)+((uintptr_t)tmp*4)), 0);
                }
            }

            /* read Rx status */
            descData->rxDescStat = CPS_UncachedRead32(&(rxQ->rxDescTail->word[1]));

            /* extract timestamp if available */
            if ((pD->cfg.enRxExtBD[queueNum]) && (descWd0 & CEDI_RXD_TS_VALID)) {
            uint32_t reg;
                descData->rxTsData.tsValid = 1;
                            // position depends on 32/64 bit addr
                wdNum = (0 != (pD->cfg.dmaAddrBusWidth))?4:2;

                tsLowerWd = CPS_UncachedRead32(&(rxQ->rxDescTail->word[wdNum]));
                tsUpperWd = CPS_UncachedRead32(&(rxQ->rxDescTail->word[wdNum+1]));

                descData->rxTsData.tsNanoSec = tsLowerWd & CEDI_TS_NANO_SEC_MASK;
                descData->rxTsData.tsSecs =
                        (((tsUpperWd & CEDI_TS_SEC1_MASK)<<CEDI_TS_SEC1_POS_SHIFT)
                            | (tsLowerWd >> CEDI_TS_SEC0_SHIFT));

            /* The timestamp only contains lower few bits of seconds, so add value from 1588 timer */
            reg =  CPS_UncachedRead32(&(pD->regs->tsu_timer_sec));
            /* If the top bit is set in the timestamp, but not in 1588 timer, it has rolled over, so subtract max size */
            if ((descData->rxTsData.tsSecs & (CEDI_TS_SEC_TOP>>1)) && (!(reg & (CEDI_TS_SEC_TOP>>1)))) {
                descData->rxTsData.tsSecs -= (CEDI_TS_SEC_TOP<<1);

            }
            descData->rxTsData.tsSecs += ((uint32_t)(~CEDI_TS_SEC_MASK) & EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(reg));
        } else {
            descData->rxTsData.tsValid = 0;
        }

            /* save this for later */
            tailWrap = descWd0 & CEDI_RXD_WRAP;

                    /* write back to descriptors */
            CPS_UncachedWrite32(&(rxQ->rxDescTail->word[1]), CEDI_RXD_EMPTY);
            /* zero buf physical address & set used - this will be new end-stop */
            CPS_UncachedWrite32(&(rxQ->rxDescTail->word[0]),
                                    CEDI_RXD_USED | ((0 != tailWrap)?CEDI_RXD_WRAP:0));

            /* handle old "stop" descriptor now */
            /* insert new buf physical address & clear used */
            descWd0 = CPS_UncachedRead32(&(rxQ->rxDescStop->word[0]));
            descWd0 = ((uint32_t)(buf->pAddr) & (uint32_t)CEDI_RXD_ADDR_MASK) |
                        (descWd0 & (uint32_t)CEDI_RXD_WRAP);
            CPS_UncachedWrite32(&(rxQ->rxDescStop->word[0]), descWd0);
            /* upper 32 bits if 64 bit addressing */
            if (0 != pD->cfg.dmaAddrBusWidth) {
#ifdef CEDI_64B_COMPILE
                /* 64-bit addressing */
                CPS_UncachedWrite32(&(rxQ->rxDescStop->word[2]),
                                 (buf->pAddr & 0xFFFFFFFF00000000)>>32);
		EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MODIFY(regData, (buf->pAddr & 0xFFFFFFFF00000000)>>32);
		CPS_UncachedWrite32(&(pD->regs->upper_rx_q_base_addr), regData);
#else
                /* 32-bit addressing */
                /* include only for test use */
                    /* copy in faked upper 32 bits for testing in 32-bit env. */
                CPS_UncachedWrite32(&(rxQ->rxDescStop->word[2]),
                                         pD->cfg.upper32BuffRxQAddr);
#endif
            }

            /* update pointers */
            rxQ->rxDescStop = rxQ->rxDescTail;
            rxQ->rxStopVA = rxQ->rxTailVA;
            if (0 != tailWrap) {
                rxQ->rxDescTail = rxQ->rxDescStart;
                rxQ->rxTailVA = rxQ->rxBufVAddr;
            }
            else {
                moveRxDescAddr(&(rxQ->rxDescTail), pD->rxDescriptorSize[queueNum]);
                rxQ->rxTailVA++;
            }

            /* return old buffer addresses */
            buf->pAddr = oldbuf.pAddr;
            buf->vAddr = oldbuf.vAddr;


            /* work out read frame status */
            if (0 != ((descData->rxDescStat) & CEDI_RXD_SOF)) {
                if (0 != ((descData->rxDescStat) & CEDI_RXD_EOF)) {
                    descData->status = CEDI_RXDATA_SOF_EOF;
                } else {
                    descData->status = CEDI_RXDATA_SOF_ONLY;
                }
            }
            else
            {
                if (0 != ((descData->rxDescStat) & CEDI_RXD_EOF)) {
                    descData->status = CEDI_RXDATA_EOF_ONLY;
                } else {
                    descData->status = CEDI_RXDATA_NO_FLAG;
                }
            }
        } else {
            descData->status = CEDI_RXDATA_NODATA;
        }
    }

    return status;
}

void CEDI_GetRxDescStat(CEDI_PrivateData *pD, uint32_t rxDStatWord, CEDI_RxDescStat *rxDStat)
{
    uint32_t network_config, dma_config, wd1;
    uint32_t status = CEDI_GetRxDescStatSF(pD, rxDStat);

    if (CDN_EOK == status) {
        network_config = CPS_UncachedRead32(&(pD->regs->network_config));
        dma_config = CPS_UncachedRead32(&(pD->regs->dma_config));

        wd1 = rxDStatWord;
        rxDStat->bufLen = wd1 & CEDI_RXD_LEN_MASK;
        if (EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(network_config) ||
            (EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__READ(network_config)==0)) {
            rxDStat->bufLen |= wd1 & CEDI_RXD_LEN13_FCS_STAT;
            rxDStat->fcsStatus = 0;
        } else {
            rxDStat->fcsStatus = (0 != (wd1 & CEDI_RXD_LEN13_FCS_STAT))?1:0;
        }

        rxDStat->sof = (0 != (wd1 & CEDI_RXD_SOF))?1:0;
        rxDStat->eof = (0 != (wd1 & CEDI_RXD_EOF))?1:0;

        if (0 != EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(dma_config)) {
            rxDStat->header = ((!rxDStat->eof) && (wd1 & CEDI_RXD_HDR))?1:0;
        } else
        {
            rxDStat->header = 0;
        }

        rxDStat->eoh = ((!rxDStat->eof) && (wd1 & CEDI_RXD_EOH))?1:0;
        rxDStat->vlanTagDet = (0 != (wd1 & CEDI_RXD_VLAN_TAG))?1:0;

        rxDStat->cfi = 0;
        rxDStat->crc = 0;
        if (0 != (wd1 & CEDI_RXD_EOF)) {
#ifdef EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__READ
            if (0 != EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__READ(dma_config)) {
                rxDStat->crc = (0 != (wd1 & CEDI_RXD_CRC))? 1 : 0;
            } else
#endif
            {
                rxDStat->cfi = ((wd1 & CEDI_RXD_CFI) && rxDStat->vlanTagDet)?1:0;
            }
        }

        if (0 != rxDStat->vlanTagDet) {
            rxDStat->vlanPri =
                    (wd1 & CEDI_RXD_VLAN_PRI_MASK)>>CEDI_RXD_VLAN_PRI_SHIFT;
        } else {
            rxDStat->vlanPri = 0;
        }
        rxDStat->priTagDet = (0 != (wd1 & CEDI_RXD_PRI_TAG))?1:0;
        if (0 != EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__READ(network_config)) {
            rxDStat->chkOffStat = (wd1 & CEDI_RXD_TYP_IDR_CHK_STA_MASK)\
                                        >>CEDI_RXD_TYP_IDR_CHK_STA_SHIFT;
            rxDStat->snapNoVlanCfi = (0 != (wd1 & CEDI_RXD_TYP_MAT_SNP_NCFI))?1:0;
            rxDStat->typeMatchReg = 0;
            rxDStat->typeIdMatch = 0;
        }
        else {
            rxDStat->chkOffStat = 0;
            rxDStat->snapNoVlanCfi = 0;
            rxDStat->typeMatchReg = (wd1 & CEDI_RXD_TYP_IDR_CHK_STA_MASK)\
                                        >>CEDI_RXD_TYP_IDR_CHK_STA_SHIFT;
            rxDStat->typeIdMatch = (0 != (wd1 & CEDI_RXD_TYP_MAT_SNP_NCFI))?1:0;
        }

        rxDStat->specAddReg = (wd1 & CEDI_RXD_SPEC_REG_MASK)\
                                    >>CEDI_RXD_SPEC_REG_SHIFT;
        if (pD->hwCfg.rx_pkt_buffer &&
                (pD->hwCfg.num_spec_add_filters>4))
        {   /* extra spec. addr matching variation */
            rxDStat->specAddReg += (((0 != ((wd1 & CEDI_RXD_SPEC_ADD_MAT)))?1:0) << 2);
            rxDStat->specAddMatch = (0 != (wd1 & CEDI_RXD_EXT_ADD_MAT))?1:0;
            rxDStat->extAddrMatch = 0;
        }
        else
        {
            rxDStat->specAddMatch = (0 != (wd1 & CEDI_RXD_SPEC_ADD_MAT))?1:0;
            rxDStat->extAddrMatch = (0 != (wd1 & CEDI_RXD_EXT_ADD_MAT))?1:0;
        }
        rxDStat->uniHashMatch = (0 != (wd1 & CEDI_RXD_UNI_HASH_MAT))?1:0;
        rxDStat->multiHashMatch = (0 != (wd1 & CEDI_RXD_MULTI_HASH_MAT))?1:0;
        rxDStat->broadcast = (0 != (wd1 & CEDI_RXD_BROADCAST_DET))?1:0;
    }
}

uint32_t CEDI_GetRxDescSize(const CEDI_PrivateData *pD, uint32_t *rxDescSize)
{
    uint32_t status = CEDI_GetRxDescSizeSF(pD, rxDescSize);

        if (CDN_EOK == status) {
        // if qx_status and qx_control registers are available,
        // descriptor size may be different for different queues.
        if (pD->hwCfg.gem_vm == true) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: Unsupported: gem_vm set, rx descriptor size may differ for different queues."
                    "\n Use CEDI_GetRxQDescSize function instead.", __func__);
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        *rxDescSize = pD->rxDescriptorSize[0]; // for non-vm configs, sizes are the same, return one.
    }
    return status;
}

uint32_t CEDI_GetRxQDescSize(const CEDI_PrivateData *pD, uint8_t queueNum, uint32_t *rxDescSize) {
    uint32_t status = CEDI_GetRxQDescSizeSF(pD, rxDescSize);

    if (CDN_EOK == status) {
        // manual queue number check (sanity doesn't do this)
        if (queueNum >= pD->rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available,
        // every queue has the same rx descriptor size
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm not set, qx_control registers unavailable: "
                    "every queue has the same rx descriptor size\n", __func__);
            *rxDescSize = pD->rxDescriptorSize[0];
        } else {
            *rxDescSize = pD->rxDescriptorSize[queueNum];
        }
    }

    return status;
}

uint32_t CEDI_RxEnabled(CEDI_PrivateData *pD)
{
    uint32_t retVal;
    uint32_t reg;
    uint32_t status = CEDI_RxEnabledSF(pD);

    if (CDN_EOK != status) {
        retVal = 0;
    } else {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        retVal = (EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__READ(reg));
    }
    return retVal;
}

void CEDI_EnableRx(CEDI_PrivateData *pD)
{
    uint32_t reg;
    uint32_t status = CEDI_EnableRxSF(pD);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__SET(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
}

void CEDI_DisableRx(CEDI_PrivateData *pD)
{
    uint32_t reg;
    uint32_t status = CEDI_DisableRxSF(pD);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_control));
        EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__CLR(reg);
        CPS_UncachedWrite32(&(pD->regs->network_control), reg);
    }
}

uint32_t CEDI_RemoveRxBuf(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_BuffAddr *buf)
{
    uint32_t status;
    uint32_t tmp;
    CEDI_RxQueue *rxQ;

    status = CEDI_RemoveRxBufSF(pD, buf);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: Invalid Rx queue number: %u\n", queueNum);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        rxQ = &(pD->rxQueue[queueNum]);

        if (0==rxQ->numRxBufs) {
            status = CDN_ENOENT;
        }
    }

    if (CDN_EOK == status) {
        /* skip "stop" descriptor since no buffer there */
        if ((rxQ->rxDescEnd==rxQ->rxDescStop) && (rxQ->rxDescEnd!=rxQ->rxDescStart))
        {
            moveRxDescAddr(&(rxQ->rxDescEnd), -(pD->rxDescriptorSize[queueNum]));
            rxQ->rxEndVA--;
        }

        /* get physical address */
        buf->pAddr = (uintptr_t)CPS_UncachedRead32(&(rxQ->rxDescEnd->word[0]))
                                                & CEDI_RXD_ADDR_MASK;
        /* get virtual address */
        buf->vAddr = *(rxQ->rxEndVA);

        /* dec end/tail pointers unless already at start of list */
        if (rxQ->rxDescEnd!=rxQ->rxDescStart) {
            moveRxDescAddr(&(rxQ->rxDescEnd), -(pD->rxDescriptorSize[queueNum]));
            rxQ->rxEndVA--;

            /* set wrap on new end descriptor */
            tmp = CPS_UncachedRead32(&(rxQ->rxDescEnd->word[0]));
            CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[0]), tmp | CEDI_RXD_WRAP);
        }
        rxQ->numRxBufs--;
    }

    return status;
}

uint32_t findQBaseAddr(const CEDI_PrivateData *pD, uint8_t queueNum, CEDI_RxQueue *rxQ,
        uint32_t *pAddr, uintptr_t *vAddr) {
    uint8_t q = 0;
    uint32_t sumRxDescSize;
    uint32_t status = (pD == NULL) ? CDN_EINVAL : CDN_EOK;

    if (status == CDN_EOK) {
        // limit of queue number cannot be checked by sanity
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (status == CDN_EOK) {
        /* find start addresses for this rxQ */
        *vAddr = pD->cfg.rxQAddr;
        *pAddr = pD->cfg.rxQPhyAddr;
        if (queueNum > 0) {
            rxQ->rxBufVAddr = (pD->rxQueue[0].rxBufVAddr);
        }

        while (q < queueNum) {
            sumRxDescSize = (uint32_t) (pD->rxQueue[q].numRxDesc)
                    * (uint32_t) (pD->rxDescriptorSize[q]);
            *vAddr += (uintptr_t) sumRxDescSize;
            *pAddr += sumRxDescSize;
            rxQ->rxBufVAddr += pD->rxQueue[q].numRxDesc;
            q++;
        }
        vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s: base address Q%u virt=%08lX phys=%08X vAddrList=%p\n",
                __func__, queueNum, *vAddr, *pAddr, rxQ->rxBufVAddr);
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: invalid arguments\n", __func__);
    }
    return status;
}

uint32_t CEDI_ResetRxQ(CEDI_PrivateData *pD, uint8_t queueNum, uint8_t ptrsOnly)
{
    uint32_t status;
    uint32_t regTmp;
    uint16_t i;
    uint32_t pAddr;
    uintptr_t vAddr;
    CEDI_RxDesc* descPtr;
    CEDI_RxQueue *rxQ;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_ResetRxQSF(pD, ptrsOnly);

    if (CDN_EOK == status ) {
        if (queueNum>=pD->rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status ) {
        CEDI_DisableRx(pD);

        rxQ = &(pD->rxQueue[queueNum]);
        findQBaseAddr(pD, queueNum, rxQ, &pAddr, &vAddr);

        /* want the virtual addresses here: */
        if (0 != ptrsOnly) {
            if (rxQ->rxDescStop!=rxQ->rxDescEnd) {
            /* copy buffer addresses from new "stop" descriptor to old one,
             * before reset pointers */
                CPS_UncachedWrite32((uint32_t *)&(rxQ->rxDescStop->word[0]),
                    CPS_UncachedRead32((uint32_t *)&(rxQ->rxDescEnd->word[0])));
                *(rxQ->rxStopVA) = *(rxQ->rxEndVA);
            }
        }
        else
        {
            rxQ->rxDescStart = rxDescAddrToPtr(vAddr);
            rxQ->rxDescEnd = rxDescAddrToPtr(vAddr);
        }
        rxQ->rxDescStop = rxDescAddrToPtr(vAddr);
        rxQ->rxDescTail = rxDescAddrToPtr(vAddr);
        rxQ->rxTailVA = rxQ->rxBufVAddr;
        rxQ->rxStopVA = rxQ->rxBufVAddr;
        if (0 == ptrsOnly) {
            rxQ->rxEndVA = rxQ->rxBufVAddr;
            *(rxQ->rxStopVA) = 0;
            rxQ->numRxBufs = 0;
        }

        /* full reset: clear used flags except stop & set wrap flag, only expand
         * available size as buffers are added - if ptrsOnly, then buffers already
         * in ring, preserve addresses & only clear used bits/wd1  */
        descPtr = rxQ->rxDescStart;
        for (i = 0; i<rxQ->numRxDesc; i++) {
            if (0 != ptrsOnly) {
                if (rxQ->rxDescStop==rxQ->rxDescEnd) {
                    CPS_UncachedWrite32((uint32_t *)&(rxQ->rxDescStop->word[0]),
                                              CEDI_RXD_WRAP|CEDI_RXD_USED );
                    CPS_UncachedWrite32(&(rxQ->rxDescStop->word[1]), CEDI_RXD_EMPTY);
                    *(rxQ->rxStopVA) = 0;
                }
                else
                {
                    pAddr = CPS_UncachedRead32((uint32_t *)&(rxQ->rxDescStop->word[0]));
                    CPS_UncachedWrite32((uint32_t *)&(rxQ->rxDescStop->word[0]),
                                        pAddr & ~(CEDI_RXD_WRAP|CEDI_RXD_USED));
                    CPS_UncachedWrite32(&(rxQ->rxDescStop->word[1]), CEDI_RXD_EMPTY);
                    /* inc stop pointer */
                    moveRxDescAddr(&(rxQ->rxDescStop), pD->rxDescriptorSize[queueNum]);
                    /* inc VA stop pointer */
                    rxQ->rxStopVA++;
                }
            }
            else {
                CPS_UncachedWrite32((uint32_t *)
                        &(descPtr->word[0]), (0 != i)?0:(CEDI_RXD_WRAP|CEDI_RXD_USED));
                CPS_UncachedWrite32((uint32_t *)
                        &(descPtr->word[1]), CEDI_RXD_EMPTY);
                moveRxDescAddr(&descPtr, pD->rxDescriptorSize[queueNum]);
            }
        }

        if (0 == ptrsOnly) {
            if (queueNum == 0) {

                regTmp = CPS_UncachedRead32(&(pD->regs->receive_q_ptr));
                /* Disable queue to change queue address */
                EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__SET(regTmp);
                CPS_REG_WRITE(&(pD->regs->receive_q_ptr), regTmp);

                EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__MODIFY(regTmp, (pAddr >> 2));
                CPS_REG_WRITE(&(pD->regs->receive_q_ptr), regTmp);

                /* Write new queue address and enable queue */
                EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__CLR(regTmp);
                CPS_REG_WRITE(&(pD->regs->receive_q_ptr), regTmp);

            } else {
                regPtr = receivePtrReg[queueNum-1];
                addRegBase(pD, &regPtr);
                regTmp = CPS_REG_READ(regPtr);

                EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__SET(regTmp);
                CPS_REG_WRITE(regPtr, regTmp);

                EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__MODIFY(regTmp, pAddr>>2);
                CPS_REG_WRITE(regPtr, regTmp);

                EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__CLR(regTmp);
                CPS_REG_WRITE(regPtr, regTmp);
            }
        }
    }
    return status;
}

uint32_t CEDI_GetRxStatus(CEDI_PrivateData *pD, CEDI_RxStatus *status)
{
    uint32_t retVal;
    uint32_t reg;
    uint32_t r_status;

    r_status = CEDI_GetRxStatusSF(pD, status);

    if (CDN_EOK != r_status) {
        retVal = 0;
    } else {
        reg = CPS_UncachedRead32(&(pD->regs->receive_status));

        status->buffNotAvail =
                EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__READ(reg);
        status->frameRx =
                EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__READ(reg);
        status->rxOverrun =
                EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__READ(reg);
        status->hRespNotOk =
                EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__READ(reg);
        retVal = (0 != reg)?1:0;
    }

    return retVal;
}

uint32_t CEDI_GetQRxStatus(CEDI_PrivateData *pD, uint8_t queueNum, CEDI_RxQStatus *rxQstatus) {
    uint32_t status = CEDI_GetQRxStatusSF(pD, rxQstatus);

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
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxStatusRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);

        rxQstatus->usedBitRead = EMAC_REGS__Q_STATUS__RX_USED_BIT_READ__READ(val);
        rxQstatus->frameRx = EMAC_REGS__Q_STATUS__FRAME_RECEIVED__READ(val);
    }
    return status;
}

uint32_t CEDI_ClearRxStatus(const CEDI_PrivateData *pD, uint32_t resetStatus)
{
    uint32_t reg = 0U;
    uint32_t status = CEDI_ClearRxStatusSF(pD, resetStatus);

    if (CDN_EOK == status) {

        if (0U != (resetStatus & CEDI_RXS_NO_BUFF)) {
            reg |= CEDI_RXS_NO_BUFF;
        }

        if (0U != (resetStatus & CEDI_RXS_FRAME_RX)) {
            reg |= CEDI_RXS_FRAME_RX;
        }

        if (0U != (resetStatus & CEDI_RXS_OVERRUN)) {
            reg |= CEDI_RXS_OVERRUN;
        }

        if (0U != (resetStatus & CEDI_RXS_HRESP_ERR)) {
            reg |= CEDI_RXS_HRESP_ERR;
        }

        CPS_UncachedWrite32(&(pD->regs->receive_status), reg);
    }

    return status;

}

uint32_t CEDI_ClearQRxStatus(CEDI_PrivateData *pD, uint8_t queueNum, uint32_t resetStatus) {
    uint32_t status = CEDI_ClearQRxStatusSF(pD, resetStatus);

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

        if (0 != (resetStatus & CEDI_RXSQ_FRAME_RX)) {
            val |= CEDI_RXSQ_FRAME_RX;
        }

        if (0 != (resetStatus & CEDI_RXSQ_USED_BIT_READ)) {
            val |= CEDI_RXSQ_USED_BIT_READ;
        }

        CPS_UncachedWrite32(regPtr, val);
    }
    return status;
}

uint32_t CEDI_SetHdrDataSplit(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_SetHdrDataSplitSF(pD, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.hdr_split==0) {
            status = CDN_ENOTSUP;
        }
    }
    // Partly supported on 1p13 with gem_vm option (for backward compatibility)
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are available, set same value for all queues
        if ((IsGem1p13(pD) == 1U) && (pD->hwCfg.gem_vm == true)) {
            uint8_t q;
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: gem_vm set, possible different per queue values. "
                    "Function will set the requested value for all queues.\n"
                    "For per-queue control use CEDI_SetQHdrDataSplit function instead.\n", __func__);
            for (q = 0; q < pD->rxQs; q++) {
                status = CEDI_SetQHdrDataSplit(pD, q, (bool) enable);
                if (CDN_EOK != status) {
                    break;
                }
            }
        }
    }
    if (CDN_EOK == status) {
        // in both cases use dma_config register additionally
        reg = CPS_UncachedRead32(&(pD->regs->dma_config));
        if (0 != enable) {
            EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__SET(reg);
        } else {
            EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->dma_config), reg);
    }
    return status;
}

/**
 *  For configurations with per-queue header data splitting support.
 *
 *  Enable/disable header-data split feature for given queue.
 *  When enabled, frame L2/L3/L4 headers will be written to separate
 *  buffer, before data starts in a second buffer (if not zero payload)
 */
uint32_t CEDI_SetQHdrDataSplit(CEDI_PrivateData *pD, uint8_t queueNum, bool enable) {
    uint32_t status = CEDI_SetQHdrDataSplitSF(pD);

    // Per queue Header splitting only available on 1p13 with gem_vm
    if (CDN_EOK == status) {
        if (0U == IsGem1p13(pD)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: Unsupported: IP must be version 1p13.\n", __func__);
            status = CDN_ENOTSUP;
        }
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
        if (pD->hwCfg.hdr_split==0) {
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);
        EMAC_REGS__Q_CONTROL__HDR_DATA_SPLITTING_EN__MODIFY(val, enable ? 1U : 0U);
        CPS_UncachedWrite32(regPtr, val);
    }
    return status;
}

/**
 * Read enable/disable status for header-data split feature
 */
uint32_t CEDI_GetHdrDataSplit(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetHdrDataSplitSF(pD, enable);

    // Unsupported on 1p13 with gem_vm option
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are available, return CDN_ENOTSUP
        if ((IsGem1p13(pD) == 1U) && (pD->hwCfg.gem_vm == true)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN,
                    "%s: Unsupported: gem_vm set, possible different per queue values.\n"
                    "Use CEDI_GetQHdrDataSplit function instead.\n", __func__);
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->hwCfg.hdr_split==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        *enable = EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(
                    CPS_UncachedRead32(&(pD->regs->dma_config)));
    }
    return status;
}

/**
 * For configurations with per-queue hader data splitting support.
 * Read enable/disable status for header-data split feature for given queue.
 */
uint32_t CEDI_GetQHdrDataSplit(CEDI_PrivateData *pD, uint8_t queueNum, bool *enabled) {
    uint32_t status = CEDI_GetQHdrDataSplitSF(pD, enabled);

    // Per queue Header splitting only available on 1p13 with gem_vm
    if (CDN_EOK == status) {
        if (0U == IsGem1p13(pD)) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: Unsupported: IP must be version 1p13. \n", __func__);
            status = CDN_ENOTSUP;
        }
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
        if (pD->hwCfg.hdr_split==0) {
            status = CDN_ENOTSUP;
        }
    }
    // manual check of queue number (not checked in sanity)
    if (CDN_EOK == status) {
        if (queueNum >= pD->cfg.rxQs) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        volatile uint32_t *regPtr = getQxControlRegAddr(pD, queueNum);

        uint32_t val = CPS_UncachedRead32(regPtr);
        if (EMAC_REGS__Q_CONTROL__HDR_DATA_SPLITTING_EN__READ(val) == 0U) {
            *enabled = false;
        } else {
            *enabled = true;
        }
    }
    return status;
}

/**
 *  Enable/disable Receive Segment Coalescing function.
 *  When enabled, consecutive TCP/IP frames on a priority queue
 *  will be combined to form a single large frame
 */
uint32_t CEDI_SetRscEnable(CEDI_PrivateData *pD, uint8_t queue, uint8_t enable)
{
    uint32_t status;
    uint32_t reg, enableField;
    uint8_t queueShift;

    status = CEDI_SetRscEnableSF(pD, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.pbuf_rsc==0) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if ((queue<1) || (queue>=(pD->rxQs))) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        if (CEDI_MAC_TYPE_EMAC == pD->macType) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        queueShift = queue-1;

        reg = CPS_UncachedRead32(&(pD->regs->rsc_control));
        enableField = EMAC_REGS__RSC_CONTROL__RSC_CONTROL__READ(reg);

        if (queueShift < 15) {
            if (0 != enable) {
                enableField |= (1 << queueShift);
            } else {
                enableField &= ~(1 << queueShift);
            }
        }

        EMAC_REGS__RSC_CONTROL__RSC_CONTROL__MODIFY(reg, enableField);
        CPS_UncachedWrite32(&(pD->regs->rsc_control), reg);
    }

    return status;
}

uint32_t CEDI_GetRscEnable(CEDI_PrivateData *pD, uint8_t queue, uint8_t *enable)
{
    uint32_t status;
    uint32_t reg;
    uint8_t queueShift;

    status = CEDI_GetRscEnableSF(pD, enable);

    if (CDN_EOK == status) {
        if ((queue<1) || (queue>=(pD->rxQs)) || (CEDI_MAC_TYPE_EMAC == pD->macType)) {
            status = CDN_EINVAL;
        }
    }
    if (CDN_EOK == status) {
        if (pD->hwCfg.pbuf_rsc==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        queueShift = queue-1;

        reg = CPS_UncachedRead32(&(pD->regs->rsc_control));
        if (queueShift < 15) {
            *enable = (0 != (EMAC_REGS__RSC_CONTROL__RSC_CONTROL__READ(reg)
                                & (1<<queueShift)))?1:0;
        }
    }

    return status;
}

uint32_t CEDI_SetRscClearMask(CEDI_PrivateData *pD, uint8_t setMask)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_SetRscClearMaskSF(pD, setMask);

    if (CDN_EOK == status) {
        if ((pD->hwCfg.pbuf_rsc==0) || (CEDI_MAC_TYPE_EMAC == pD->macType)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->rsc_control));
        if (0 != setMask) {
            reg |= 0x10000U; /* (1 << 16) */
        } else {
            reg &= ~0x10000U; /* (1 << 16) */
        }
        CPS_UncachedWrite32(&(pD->regs->rsc_control), reg);
    }

    return status;
}

uint32_t CEDI_SetRxPartialStFwd(CEDI_PrivateData *pD, uint32_t watermark, uint8_t enable)
{
    uint32_t status;
    uint32_t reg;
    uint32_t rx_pbuf_addr;

    status = CEDI_SetRxPartialStFwdSF(pD, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.rx_pkt_buffer==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        rx_pbuf_addr = pD->hwCfg.rx_pbuf_addr;
        if (rx_pbuf_addr < 16) {
            if (watermark>((1<<rx_pbuf_addr)-1)) {
                status = CDN_EINVAL;
            }
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n",
                    "Warning: Wrong rx_pbuf_addr read from hardware");
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pbuf_rxcutthru));
        if (0 != enable) {
            EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__MODIFY(reg,
                    watermark);
            EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__SET(reg);
        } else {
            EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__CLR(reg);
        }

        CPS_UncachedWrite32(&(pD->regs->pbuf_rxcutthru), reg);
    }

    return status;
}

uint32_t CEDI_GetRxPartialStFwd(CEDI_PrivateData *pD, uint32_t *watermark, uint8_t *enable)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_GetRxPartialStFwdSF(pD, watermark, enable);

    if (CDN_EOK == status) {
        if (pD->hwCfg.rx_pkt_buffer==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->pbuf_rxcutthru));
        (*enable) = EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__READ(reg);

        if (0 != (*enable)) {
            *watermark =
                    EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__READ(reg);
        }
    }

    return status;
}

/******************************** Rx Filtering ******************************/

uint32_t CEDI_SetSpecificAddr(CEDI_PrivateData *pD, uint8_t addrNum, const CEDI_MacAddress *addr,
                            uint8_t specFilterType, uint8_t byteMask)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t *bottomPtr = NULL;
    volatile uint32_t *topPtr = NULL;

    status = CEDI_SetSpecificAddrSF(pD, addr, specFilterType, byteMask);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_spec_add_filters==0) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if ((!addrNum) || (addrNum>(pD->hwCfg.num_spec_add_filters))) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regVal = 0;

        bottomPtr = specAddBottomReg[addrNum-1];
        addRegBase(pD, &bottomPtr);

        topPtr = specAddTopReg[addrNum-1];
        addRegBase(pD, &topPtr);

        EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__MODIFY(regVal,
                          (uint32_t)(addr->byte[0]) +
                          ((uint32_t)(addr->byte[1])<<8) +
                          ((uint32_t)(addr->byte[2])<<16) +
                          ((uint32_t)(addr->byte[3])<<24));
        CPS_UncachedWrite32(bottomPtr, regVal);

        regVal = 0;
        if (1 == addrNum) {
            EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__MODIFY(regVal,
                (uint32_t)(addr->byte[4]) + ((uint32_t)(addr->byte[5])<<8));
            EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__MODIFY(regVal,
                specFilterType);
        } else {
            EMAC_REGS__SPEC_ADD_TOP__ADDRESS__MODIFY(regVal,
                (uint32_t)(addr->byte[4]) + ((uint32_t)(addr->byte[5])<<8));
            EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__MODIFY(regVal,
                specFilterType);
            EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__MODIFY(regVal, byteMask);
        }
        CPS_UncachedWrite32(topPtr, regVal);
    }

    return status;
}

uint32_t CEDI_GetSpecificAddr(CEDI_PrivateData *pD, uint8_t addrNum, CEDI_MacAddress *addr,
                        uint8_t *specFilterType, uint8_t *byteMask)
{
    uint32_t status;
    volatile uint32_t *bottomPtr = NULL;
    volatile uint32_t *topPtr = NULL;
    uint32_t regAddrTop, regAddrBottom, regTopVal;

    status = CEDI_GetSpecificAddrSF(pD, addr, specFilterType, byteMask);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_spec_add_filters==0) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if ((!addrNum) || (addrNum>(pD->hwCfg.num_spec_add_filters))) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regAddrTop = 0;
        regAddrBottom = 0;

        bottomPtr = specAddBottomReg[addrNum-1];
        addRegBase(pD, &bottomPtr);

        topPtr = specAddTopReg[addrNum-1];
        addRegBase(pD, &topPtr);

        regAddrBottom = EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__READ(
            CPS_UncachedRead32(bottomPtr));
        regTopVal = CPS_UncachedRead32(topPtr);
        if (1 == addrNum) {
            regAddrTop = EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__READ(
                regTopVal);
            *specFilterType =
                EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__READ(regTopVal);
            *byteMask = 0;
        } else {
            regAddrTop = EMAC_REGS__SPEC_ADD_TOP__ADDRESS__READ(regTopVal);
            *specFilterType =
                EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__READ(regTopVal);
            *byteMask =
                EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__READ(regTopVal);}

        addr->byte[0] = (regAddrBottom & 0xFF);
        addr->byte[1] = ((regAddrBottom>>8) & 0xFF);
        addr->byte[2] = ((regAddrBottom>>16) & 0xFF);
        addr->byte[3] = ((regAddrBottom>>24) & 0xFF);
        addr->byte[4] = (regAddrTop & 0xFF);
        addr->byte[5] = ((regAddrTop>>8) & 0xFF);
    }
    return status;
}

uint32_t CEDI_SetSpecificAddr1Mask(CEDI_PrivateData *pD, const CEDI_MacAddress *mask)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_SetSpecificAddr1MaskSF(pD, mask);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_spec_add_filters==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = 0;
        EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__MODIFY(reg,
                ((uint32_t)(mask->byte[0]) +
                ((uint32_t)(mask->byte[1])<<8) +
                ((uint32_t)(mask->byte[2])<<16) +
                ((uint32_t)(mask->byte[3])<<24)));
        CPS_UncachedWrite32((&(pD->regs->mask_add1_bottom)), reg);
        reg = 0;
        EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__MODIFY(reg,
                (uint32_t)(mask->byte[4]) +
                ((uint32_t)(mask->byte[5])<<8));
        CPS_UncachedWrite32((&(pD->regs->mask_add1_top)), reg);
    }
    return status;
}

uint32_t CEDI_GetSpecificAddr1Mask(CEDI_PrivateData *pD, CEDI_MacAddress *mask)
{
    uint32_t status;
    uint32_t reg1, reg2;

    status = CEDI_GetSpecificAddr1MaskSF(pD, mask);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_spec_add_filters==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg1 = EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__READ(
                CPS_UncachedRead32(&(pD->regs->mask_add1_bottom)));
        reg2 = EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__READ(
                CPS_UncachedRead32(&(pD->regs->mask_add1_top)));

        mask->byte[0] = (reg1 & 0xFF);
        mask->byte[1] = ((reg1>>8) & 0xFF);
        mask->byte[2] = ((reg1>>16) & 0xFF);
        mask->byte[3] = ((reg1>>24) & 0xFF);
        mask->byte[4] = (reg2 & 0xFF);
        mask->byte[5] = ((reg2>>8) & 0xFF);
    }
    return status;
}

uint32_t CEDI_DisableSpecAddr(const CEDI_PrivateData *pD, uint8_t addrNum)
{
    uint32_t status;
    volatile uint32_t *bottomPtr = NULL;

    status = CEDI_DisableSpecAddrSF(pD);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_spec_add_filters == 0U) {
            status = CDN_ENOTSUP;
        }
    }
    if (CDN_EOK == status) {
        if ((addrNum == 0U) || (addrNum > (pD->hwCfg.num_spec_add_filters))) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        bottomPtr = specAddBottomReg[addrNum-1U];
        addRegBase(pD, &bottomPtr);

        CPS_UncachedWrite32(bottomPtr, 0U);
    }

    return status;
}

uint32_t CEDI_SetTypeIdMatch(CEDI_PrivateData *pD, uint8_t matchSel, uint16_t typeId,
        uint8_t enable)
{
    uint32_t status;
    uint32_t regVal = 0;

    status = CEDI_SetTypeIdMatchSF(pD, matchSel, typeId, enable);

    if (CDN_EOK == status) {
        switch (matchSel) {
        case 1:
            if (0 != enable) {
                EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__SET(regVal);
                EMAC_REGS__SPEC_TYPE1__MATCH__MODIFY(regVal, typeId);
            }
            CPS_UncachedWrite32(&(pD->regs->spec_type1), regVal);
            break;
        case 2:
            if (0 != enable) {
                EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__SET(regVal);
                EMAC_REGS__SPEC_TYPE2__MATCH__MODIFY(regVal, typeId);
            }
            CPS_UncachedWrite32(&(pD->regs->spec_type2), regVal);
            break;
        case 3:
            if (0 != enable) {
                EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__SET(regVal);
                EMAC_REGS__SPEC_TYPE3__MATCH__MODIFY(regVal, typeId);
            }
            CPS_UncachedWrite32(&(pD->regs->spec_type3), regVal);
            break;
        case 4:
            if (0 != enable) {
                EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__SET(regVal);
                EMAC_REGS__SPEC_TYPE4__MATCH__MODIFY(regVal, typeId);
            }
            CPS_UncachedWrite32(&(pD->regs->spec_type4), regVal);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }

    return status;
}

uint32_t CEDI_GetTypeIdMatch(CEDI_PrivateData *pD, uint8_t matchSel, uint16_t *typeId,
        uint8_t *enabled)
{
    uint32_t status;
    uint32_t regVal = 0;

    status = CEDI_GetTypeIdMatchSF(pD, matchSel, typeId, enabled);

    if (CDN_EOK == status) {
        if ((*enabled) && (typeId==NULL)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        switch (matchSel) {
        case 1:
            regVal = CPS_UncachedRead32(&(pD->regs->spec_type1));
            *enabled = EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__READ(regVal);
            *typeId = EMAC_REGS__SPEC_TYPE1__MATCH__READ(regVal);
            break;
        case 2:
            regVal = CPS_UncachedRead32(&(pD->regs->spec_type2));
            *enabled = EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__READ(regVal);
            *typeId = EMAC_REGS__SPEC_TYPE2__MATCH__READ(regVal);
            break;
        case 3:
            regVal = CPS_UncachedRead32(&(pD->regs->spec_type3));
            *enabled = EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__READ(regVal);
            *typeId = EMAC_REGS__SPEC_TYPE3__MATCH__READ(regVal);
            break;
        case 4:
            regVal = CPS_UncachedRead32(&(pD->regs->spec_type4));
            *enabled = EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__READ(regVal);
            *typeId = EMAC_REGS__SPEC_TYPE4__MATCH__READ(regVal);
            break;
        default:
            status = CDN_EINVAL;
            break;
        }
    }

    return status;
}

void CEDI_SetUnicastEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetUnicastEnableSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != enable) {
            EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetUnicastEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetUnicastEnableSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

void CEDI_SetMulticastEnable(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetMulticastEnableSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != enable) {
            EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetMulticastEnable(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetMulticastEnableSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__READ(
            CPS_UncachedRead32(&(pD->regs->network_config)));
    }
    return status;
}

void CEDI_SetNoBroadcast(CEDI_PrivateData *pD, uint8_t reject)
{
    uint32_t reg;
    uint32_t status = CEDI_SetNoBroadcastSF(pD, reject);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != reject) {
            EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetNoBroadcast(CEDI_PrivateData *pD, uint8_t *reject)
{
    uint32_t status = CEDI_GetNoBroadcastSF(pD, reject);

    if (CDN_EOK == status) {
        *reject= EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

void CEDI_SetVlanOnly(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetVlanOnlySF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != enable) {
            EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetVlanOnly(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetVlanOnlySF(pD, enable);

    if (CDN_EOK == status) {
        *enable= EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

void CEDI_SetStackedVlanReg(CEDI_PrivateData *pD, uint8_t enable, uint16_t vlanType)
{
    uint32_t reg;
    uint32_t status = CEDI_SetStackedVlanRegSF(pD, enable, vlanType);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->stacked_vlan));

        if (0 != enable) {
            EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__SET(reg);
            EMAC_REGS__STACKED_VLAN__MATCH__MODIFY(reg, vlanType);
        } else {
            EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->stacked_vlan), reg);
    }
}

void CEDI_GetStackedVlanReg(CEDI_PrivateData *pD, uint8_t *enable, uint16_t *vlanType)
{
    uint32_t reg;
    uint32_t status = CEDI_GetStackedVlanRegSF(pD, enable, vlanType);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->stacked_vlan));
        *enable = EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__READ(reg);
        *vlanType = EMAC_REGS__STACKED_VLAN__MATCH__READ(reg);
    }
}

void CEDI_SetCopyAllFrames(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetCopyAllFramesSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));

        if (0 != enable) {
            EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__CLR(reg);
        }

        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetCopyAllFrames(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetCopyAllFramesSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }

    return status;
}

uint32_t CEDI_SetHashAddr(const CEDI_PrivateData *pD, uint32_t hAddrTop, uint32_t hAddrBot)
{
    uint32_t status = CEDI_SetHashAddrSF(pD, hAddrTop, hAddrBot);
    uint32_t regVal;

    if (CDN_EOK == status) {
        regVal = EMAC_REGS__HASH_BOTTOM__ADDRESS__WRITE(hAddrBot);
        CPS_UncachedWrite32(&(pD->regs->hash_bottom), regVal);

        regVal = EMAC_REGS__HASH_TOP__ADDRESS__WRITE(hAddrTop);
        CPS_UncachedWrite32(&(pD->regs->hash_top), regVal);
    }
    return status;
}

uint32_t CEDI_GetHashAddr(const CEDI_PrivateData *pD, uint32_t *hAddrTop, uint32_t *hAddrBot)
{
    uint32_t status = CEDI_GetHashAddrSF(pD, hAddrTop, hAddrBot);
    uint32_t regVal;

    if (CDN_EOK == status) {

        regVal = CPS_UncachedRead32(&(pD->regs->hash_bottom));
        *hAddrBot = EMAC_REGS__HASH_BOTTOM__ADDRESS__READ(regVal);

        regVal = CPS_UncachedRead32(&(pD->regs->hash_top));
        *hAddrTop = EMAC_REGS__HASH_TOP__ADDRESS__READ(regVal);
    }
    return status;
}

void CEDI_SetLenErrDiscard(CEDI_PrivateData *pD, uint8_t enable)
{
    uint32_t reg;
    uint32_t status = CEDI_SetLenErrDiscardSF(pD, enable);

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->network_config));
        if (0 != enable) {
            EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SET(reg);
        } else {
            EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__CLR(reg);
        }
        CPS_UncachedWrite32(&(pD->regs->network_config), reg);
    }
}

uint32_t CEDI_GetLenErrDiscard(CEDI_PrivateData *pD, uint8_t *enable)
{
    uint32_t status = CEDI_GetLenErrDiscardSF(pD, enable);

    if (CDN_EOK == status) {
        *enable= EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__READ(
                CPS_UncachedRead32(&(pD->regs->network_config)));
    }
    return status;
}

/******************************** Rx Priority Queues ******************************/

uint32_t CEDI_GetNumScreenRegs(const CEDI_PrivateData *pD, CEDI_NumScreeners *regNums)
{
    uint32_t status = CEDI_GetNumScreenRegsSF(pD, regNums);

    if (CDN_EOK == status) {
        getNumScreenRegs(pD, regNums);
    }
    return status;
}

uint32_t CEDI_SetType1ScreenReg(const CEDI_PrivateData *pD, uint8_t regNum, const CEDI_T1Screen *regVals)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetType1ScreenRegSF(pD, regVals);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type1_screeners==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if ((regNum>=pD->hwCfg.num_type1_screeners) ||
            (regVals->qNum>=pD->rxQs)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = type1ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__MODIFY(reg, regVals->qNum);
        EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__MODIFY(reg, regVals->dstcEnable);
        EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__MODIFY(reg, regVals->dstcMatch);
        EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__MODIFY(reg, regVals->udpEnable);
        EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__MODIFY(reg, regVals->udpPort);

        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint8_t isIngressTrafficSupported(CEDI_PrivateData* pD)
{
    return IsGem1p11(pD);
}

uint32_t CEDI_GetType1ScreenReg(const CEDI_PrivateData *pD, uint8_t regNum, CEDI_T1Screen *regVals)
{
    uint32_t status;
    uint32_t reg = 0;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetType1ScreenRegSF(pD, regVals);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type1_screeners==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type1_screeners) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = type1ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        regVals->qNum = EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__READ(reg);
        regVals->dstcMatch = EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__READ(reg);
        regVals->udpPort = EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__READ(reg);
        regVals->dstcEnable = EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__READ(reg);
        regVals->udpEnable =  EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetType2ScreenReg(const CEDI_PrivateData *pD, uint8_t regNum, const CEDI_T2Screen *regVals)
{
    uint32_t status;
    uint32_t reg;
    const CEDI_DesignCfg* hwCfg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetType2ScreenRegSF(pD, regVals);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type2_screeners == 0U) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {

        hwCfg = &(pD->hwCfg);

        if (regNum >= hwCfg->num_type2_screeners) {
            status = CDN_EINVAL;
        }
        if (regVals->qNum >= pD->rxQs) {
            status = CDN_EINVAL;
        }

        if ((regVals->eTypeEnable == 1U) && (regVals->ethTypeIndex >= hwCfg->num_scr2_ethtype_regs)) {
            status = CDN_EINVAL;
        }

        if ((regVals->compAEnable == 1U) && (regVals->compAIndex >= hwCfg->num_scr2_compare_regs)) {
            status = CDN_EINVAL;
        }

        if ((regVals->compBEnable == 1U) && (regVals->compBIndex >= hwCfg->num_scr2_compare_regs)) {
            status = CDN_EINVAL;
        }

        if ((regVals->compCEnable == 1U) && (regVals->compCIndex >= hwCfg->num_scr2_compare_regs)) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = type2ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__MODIFY(reg,
                                                                regVals->qNum);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__MODIFY(reg,
                                                        regVals->vlanEnable);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__MODIFY(reg,
                                                        regVals->vlanPriority);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__MODIFY(reg,
                                                        regVals->eTypeEnable);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_REG_INDEX__MODIFY(reg,
                                                        regVals->ethTypeIndex);

        EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__MODIFY(reg,
                                                        regVals->compAEnable);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__MODIFY(reg,
                                                        regVals->compAIndex);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__MODIFY(reg,
                                                        regVals->compBEnable);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__MODIFY(reg,
                                                        regVals->compBIndex);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__MODIFY(reg,
                                                        regVals->compCEnable);
        EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__MODIFY(reg,
                                                        regVals->compCIndex);

        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetType2ScreenReg(const CEDI_PrivateData *pD, uint8_t regNum, CEDI_T2Screen *regVals)
{
    uint32_t status;
    uint32_t reg = 0;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetType2ScreenRegSF(pD, regVals);

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type2_screeners==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type2_screeners) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = type2ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        regVals->qNum =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__READ(reg);
        regVals->vlanPriority =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__READ(reg);
        regVals->vlanEnable =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__READ(reg);
        regVals->ethTypeIndex =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_REG_INDEX__READ(reg);
        regVals->eTypeEnable =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__READ(reg);
        regVals->compAIndex =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__READ(reg);
        regVals->compAEnable =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__READ(reg);
        regVals->compBIndex =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__READ(reg);
        regVals->compBEnable =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__READ(reg);
        regVals->compCIndex =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__READ(reg);
        regVals->compCEnable =
                EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetType2EthertypeReg(CEDI_PrivateData *pD, uint8_t index, uint16_t eTypeVal)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetType2EthertypeRegSF(pD, eTypeVal);

    if (CDN_EOK == status) {
        if ((pD->hwCfg.num_type2_screeners==0) ||
                (pD->hwCfg.num_scr2_ethtype_regs==0)) {
        status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (index>=pD->hwCfg.num_scr2_ethtype_regs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        reg = 0;
        EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__MODIFY(reg,
                                                                        eTypeVal);

        regPtr = type2ScreeningEthertypeReg[index];
        addRegBase(pD, &regPtr);
        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetType2EthertypeReg(CEDI_PrivateData *pD, uint8_t index, uint16_t *eTypeVal)
{
    uint32_t status;
    uint32_t reg = 0;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetType2EthertypeRegSF(pD, eTypeVal);

    if (CDN_EOK == status) {
        if ((pD->hwCfg.num_type2_screeners==0) ||
                (pD->hwCfg.num_scr2_ethtype_regs==0)) {
        status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (index>=pD->hwCfg.num_scr2_ethtype_regs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        regPtr = type2ScreeningEthertypeReg[index];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        *eTypeVal = (uint16_t)(
                EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__READ(reg));
    }
    return status;
}

uint32_t CEDI_SetType2CompareReg(CEDI_PrivateData *pD, uint8_t index, const CEDI_T2Compare *regVals)
{
    uint32_t status;
    volatile uint32_t *word0Ptr = NULL;
    volatile uint32_t *word1Ptr = NULL;
    uint32_t reg0, reg1;

    status = CEDI_SetType2CompareRegSF(pD, regVals);

    if (CDN_EOK == status) {
        if ((pD->hwCfg.num_type2_screeners==0U) ||
                (pD->hwCfg.num_scr2_compare_regs==0U)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        switch (regVals->offsetPosition){
        case CEDI_T2COMP_OFF_VID_S_TAG:
        case CEDI_T2COMP_OFF_VID_C_TAG:

            if (0U == IsGem1p12(pD)) {
                status = CDN_ENOTSUP;
            }

            if (CDN_EOK == status) {
                word1Ptr = type2CompareWord1Reg[index];
                addRegBase(pD, &word1Ptr);

                reg1 = CPS_UncachedRead32(word1Ptr);
                EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_VLAN_ID__SET(reg1);
                EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__CLR(reg1);
                reg1 &= ~EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MASK;
                reg1 &= ~EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MASK;

                /* if S-TAG VID comparison set bit 7 */
                if (regVals->offsetPosition == CEDI_T2COMP_OFF_VID_S_TAG) {
                    reg1 |= EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__WRITE(0x01);
                }

                CPS_UncachedWrite32(word1Ptr, reg1);
            }
        break;

        case CEDI_T2COMP_OFF_SOF:
        case CEDI_T2COMP_OFF_ETYPE:
        case CEDI_T2COMP_OFF_IPHDR:
        case CEDI_T2COMP_OFF_TCPUDP:

            if ((index>=pD->hwCfg.num_scr2_compare_regs)
                || (regVals->offsetVal>0x3FU)
                || (regVals->disableMask>1U)) {
                status = CDN_EINVAL;
            }

            if (CDN_EOK == status) {
                word0Ptr = type2CompareWord0Reg[index];
                addRegBase(pD, &word0Ptr);

                word1Ptr = type2CompareWord1Reg[index];
                addRegBase(pD, &word1Ptr);

                reg0 = 0;
                reg1 = 0;
                EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__MODIFY(reg0,
                                                                    regVals->compMask);
                EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__MODIFY(reg0,
                                                                    regVals->compValue);
                EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MODIFY(reg1,
                                                                    regVals->offsetVal);
                EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MODIFY(reg1,
                                                                regVals->offsetPosition);
                            EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__MODIFY(reg1,
                                                                regVals->disableMask);

                CPS_UncachedWrite32(word0Ptr, reg0);
                CPS_UncachedWrite32(word1Ptr, reg1);
            }

        break;

        default:
            status = CDN_EINVAL;
        break;
        }
    }

    return status;
}

uint32_t CEDI_GetType2CompareReg(CEDI_PrivateData *pD, uint8_t index, CEDI_T2Compare *regVals)
{
    uint32_t status;
    uint32_t reg0 = 0, reg1 = 0;
    uint32_t compareOffset;
    volatile uint32_t *word0Ptr = NULL;
    volatile uint32_t *word1Ptr = NULL;

    status = CEDI_GetType2CompareRegSF(pD, regVals);

    if (CDN_EOK == status) {
        if ((pD->hwCfg.num_type2_screeners==0) ||
                (pD->hwCfg.num_scr2_compare_regs==0)) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (index>=pD->hwCfg.num_scr2_compare_regs) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        word0Ptr = type2CompareWord0Reg[index];
        addRegBase(pD, &word0Ptr);

        word1Ptr = type2CompareWord1Reg[index];
        addRegBase(pD, &word1Ptr);

        reg0 = CPS_UncachedRead32(word0Ptr);
        reg1 = CPS_UncachedRead32(word1Ptr);

        compareOffset = EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__READ(reg1);

        regVals->compMask = (uint16_t)(
            EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__READ(reg0));
        regVals->compValue = (uint16_t)(
            EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__READ(reg0));
        regVals->offsetVal = (uint8_t)(
            EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__READ(reg1));
        regVals->offsetPosition = (CEDI_T2Offset)compareOffset;
        regVals->disableMask = (uint8_t)(
            EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__READ(reg1));
    }

    return status;
}

uint32_t CEDI_SetRxQueueNum(CEDI_PrivateData *pD, uint8_t numQueues)
{
    uint32_t status;
    uint8_t i;
#ifdef EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__MODIFY
    uint32_t retVal;
#endif

    status = CEDI_SetRxQueueNumSF(pD, numQueues);

    if (CDN_EOK == status) {
        if (numQueues >  pD->cfg.rxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                    "Error: number of queues cannot be bigger than set during "
                    "driver initialization which is %d\n", pD->cfg.rxQs);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        /* nothing to do. New setting equals current setting. */
        if (numQueues == pD->rxQs) {
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
#ifdef EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__MODIFY
        if (0 != CEDI_RxEnabled(pD)){
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s\n",
                    "Error: Cannot change number of queues when transmission is not disabled\n");
            status = CDN_EIO;
        }

        if (CDN_EOK == status) {
            /* disable screening for each of queues to disable
             * to ensure frames are not routed to disabled queues*/
            for (i = numQueues - 1; i <  pD->cfg.rxQs; i++){
                retVal = QueueCheckAndDisableScreening(pD, i);
                if (CDN_EOK != retVal) {
                    vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "CEDI_SetRxQueueNum: QueueCheckAndDisableScreening "\
                        "returned with code: %u for queue %u\n", retVal, i);
                }
            }

        /* enable all queues with number below numQueues) */
        for (i = numQueues - 1; i > 0; i--) {
        setRxQueueDisableBit(pD, i, 0);
        }

        /* disable all queues with number equal to or above numQueues) */
        for (i = numQueues; i < pD->cfg.rxQs; i++) {
        setRxQueueDisableBit(pD, i, 1);
        }

            /* set new rx priority queues number */
            pD->rxQs = numQueues;
        }
#else
        status = CDN_ENOTSUP;
#endif
    }
    if (CDN_EAGAIN == status) {
        status = CDN_EOK;
    }
    return status;
}

uint32_t CEDI_GetRxQueueNum(const CEDI_PrivateData *pD, uint8_t *numQueues)
{
    uint32_t status = CEDI_GetRxQueueNumSF(pD, numQueues);

    if (CDN_EOK == status) {
        *numQueues = pD->rxQs;
    }
    return status;
}


uint32_t CEDI_SetType1ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum,
                     uint8_t enable)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetType1ScreenRegDropEnSF(pD, enable);

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type1_screeners==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type1_screeners) {
            status = CDN_EINVAL;
        }
    }

   if (CDN_EOK == status) {
        regPtr = type1ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

    EMAC_REGS__SCREENING_TYPE_1_REGISTER__DROP_ON_MATCH__MODIFY(reg, enable);
        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetType1ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum,
                     uint8_t *enable)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetType1ScreenRegDropEnSF(pD, enable);

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type1_screeners==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type1_screeners) {
            status = CDN_EINVAL;
        }
    }

   if (CDN_EOK == status) {
        regPtr = type1ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

    *enable = EMAC_REGS__SCREENING_TYPE_1_REGISTER__DROP_ON_MATCH__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetType2ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum, uint8_t enable)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetType2ScreenRegDropEnSF(pD, enable);

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type2_screeners == 0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (regNum >= pD->hwCfg.num_type2_screeners) {
            status = CDN_EINVAL;
        }
    }

   if (CDN_EOK == status) {
        regPtr = type2ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        EMAC_REGS__SCREENING_TYPE_2_REGISTER__DROP_ON_MATCH__MODIFY(reg, enable);
        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetType2ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum,
                     uint8_t *enable)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetType2ScreenRegDropEnSF(pD, enable);

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (pD->hwCfg.num_type2_screeners==0) {
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type2_screeners) {
            status = CDN_EINVAL;
        }
    }

   if (CDN_EOK == status) {
        regPtr = type2ScreeningReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

    *enable = EMAC_REGS__SCREENING_TYPE_2_REGISTER__DROP_ON_MATCH__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetRxQFlushConfig(CEDI_PrivateData* pD, uint8_t queueNum,
                   CEDI_RxQFlushConfig* rxQFlushConfig)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetRxQFlushConfigSF(pD, rxQFlushConfig);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: Invalid Rx queue number: %u\n", queueNum);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regPtr = rxQueueFlushReg[queueNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);


        EMAC_REGS__RX_Q_FLUSH__DROP_ALL_FRAMES__MODIFY(reg, rxQFlushConfig->dropAllFrames);
        EMAC_REGS__RX_Q_FLUSH__DROP_ON_RESOURCE_ERR__MODIFY(reg, rxQFlushConfig->dropOnRsrcErr);

        if (rxQFlushConfig->rxQFlushMode == CEDI_FLUSH_MODE_LIMIT_NUM_BYTES){
            EMAC_REGS__RX_Q_FLUSH__LIMIT_NUM_BYTES__MODIFY(reg, 1);
        }
        else {
            EMAC_REGS__RX_Q_FLUSH__LIMIT_NUM_BYTES__MODIFY(reg, 0);
        }

        if (rxQFlushConfig->rxQFlushMode == CEDI_FLUSH_MODE_LIMIT_FRAME_SIZE){
            EMAC_REGS__RX_Q_FLUSH__LIMIT_FRAME_SIZE__MODIFY(reg, 1);
        }
        else {
            EMAC_REGS__RX_Q_FLUSH__LIMIT_FRAME_SIZE__MODIFY(reg, 0);
        }

        EMAC_REGS__RX_Q_FLUSH__MAX_VAL__MODIFY(reg, rxQFlushConfig->maxVal);

        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;

}

uint32_t CEDI_GetRxQFlushConfig(CEDI_PrivateData* pD, uint8_t queueNum,
                   CEDI_RxQFlushConfig* rxQFlushConfig)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetRxQFlushConfigSF(pD, rxQFlushConfig);

    if (CDN_EOK == status) {
        if (queueNum>=pD->rxQs) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Error: Invalid Rx queue number: %u\n", queueNum);
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regPtr = rxQueueFlushReg[queueNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        rxQFlushConfig->dropAllFrames = EMAC_REGS__RX_Q_FLUSH__DROP_ALL_FRAMES__READ(reg);
        rxQFlushConfig->dropOnRsrcErr = EMAC_REGS__RX_Q_FLUSH__DROP_ON_RESOURCE_ERR__READ(reg);


        if (EMAC_REGS__RX_Q_FLUSH__LIMIT_NUM_BYTES__READ(reg) == 1)
            rxQFlushConfig->rxQFlushMode = CEDI_FLUSH_MODE_LIMIT_NUM_BYTES;
        else if (EMAC_REGS__RX_Q_FLUSH__LIMIT_FRAME_SIZE__READ(reg) == 1)
            rxQFlushConfig->rxQFlushMode = CEDI_FLUSH_MODE_LIMIT_FRAME_SIZE;
        else
            rxQFlushConfig->rxQFlushMode = CEDI_FLUSH_MODE_OFF;

        rxQFlushConfig->maxVal = EMAC_REGS__RX_Q_FLUSH__MAX_VAL__READ(reg);
    }

    return status;
}

uint32_t CEDI_GetRxDmaFlushedPacketsCount(CEDI_PrivateData* pD, uint16_t* count)
{
    uint32_t status;
    uint32_t reg;

    status = CEDI_GetRxDmaFlushedPacketsCSF(pD, count);

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        reg = CPS_UncachedRead32(&(pD->regs->auto_flushed_pkts));

        *count = EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__READ(reg);
    }

    return status;
}

uint32_t CEDI_SetType2ScreenerRateLimit(CEDI_PrivateData* pD, uint8_t regNum,
                       CEDI_Type2ScreenerRateLimit* rateLimit)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_SetType2ScreenerRateLimSF(pD, rateLimit);

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type2_screeners) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
        if (isIngressTrafficSupported(pD) == 0){
            status = CDN_ENOTSUP;
        }
    }

    if (CDN_EOK == status) {
        regPtr = scr2RateLimitReg[regNum];
        addRegBase(pD, &regPtr);
        reg = CPS_UncachedRead32(regPtr);

        EMAC_REGS__SCR2_RATE_LIMIT__INTERVAL_TIME__MODIFY(reg, rateLimit->intervalTime);
        EMAC_REGS__SCR2_RATE_LIMIT__MAX_RATE_VAL__MODIFY(reg, rateLimit->maxRateVal);

        CPS_UncachedWrite32(regPtr, reg);
    }

    return status;
}

uint32_t CEDI_GetType2ScreenerRateLimit(CEDI_PrivateData* pD, uint8_t regNum,
                       CEDI_Type2ScreenerRateLimit* rateLimit)
{
    uint32_t status;
    uint32_t reg;
    volatile uint32_t *regPtr = NULL;

    status = CEDI_GetType2ScreenerRateLimSF(pD, rateLimit);

    if (CDN_EOK == status) {
        if (regNum>=pD->hwCfg.num_type2_screeners) {
            status = CDN_EINVAL;
        }
    }

    if (CDN_EOK == status) {
    if (isIngressTrafficSupported(pD) == 0){
        status = CDN_ENOTSUP;
    }
    }

    if (CDN_EOK == status) {
    regPtr = scr2RateLimitReg[regNum];
    addRegBase(pD, &regPtr);
    reg = CPS_UncachedRead32(regPtr);

    rateLimit->intervalTime = EMAC_REGS__SCR2_RATE_LIMIT__INTERVAL_TIME__READ(reg);
    rateLimit->maxRateVal = EMAC_REGS__SCR2_RATE_LIMIT__MAX_RATE_VAL__READ(reg);
    }

    return status;
}

uint32_t CEDI_GetRxType2RateLimitTriggered(CEDI_PrivateData* pD,
                      uint16_t* status)
{
    uint32_t ret = 0;
    uint32_t reg;

    ret = CEDI_GetRxType2RateLimitTrigSF(pD, status);

    if (0 == ret) {
        if (isIngressTrafficSupported(pD) == 0){
            ret = CDN_ENOTSUP;
        }
    }

    if (0 == ret) {
        reg = CPS_UncachedRead32(&(pD->regs->scr2_rate_status));

        *status = reg & ~EMAC_REGS__SCR2_RATE_STATUS__RESERVED_31_16__MASK;
    }

    return ret;
}

uint32_t CEDI_SetRxWatermark(CEDI_PrivateData* pD, uint16_t rxHighWatermark, uint16_t rxLowWatermark)
{
    uint32_t ret = 0;
    uint32_t reg;

    ret =  CEDI_SetRxWatermarkSF(pD, rxHighWatermark, rxLowWatermark);

    if (0 == ret) {
        if (IsGem1p11(pD) == 0){
            ret = CDN_ENOTSUP;
        }
    }

    if (0 == ret) {
        CPS_UncachedWrite32(&(pD->regs->rx_water_mark), 0);

        reg = EMAC_REGS__RX_WATER_MARK__RX_HIGH_WATERMARK__WRITE(rxHighWatermark);
        reg |= EMAC_REGS__RX_WATER_MARK__RX_LOW_WATERMARK__WRITE(rxLowWatermark);

        CPS_UncachedWrite32(&(pD->regs->rx_water_mark), reg);
    }

    return ret;
}

uint32_t CEDI_GetRxWatermark(CEDI_PrivateData* pD, uint16_t* rxHighWatermark, uint16_t* rxLowWatermark)
{
    uint32_t ret = 0;
    uint32_t reg;

    ret = CEDI_GetRxWatermarkSF(pD, rxHighWatermark, rxLowWatermark);

    if (0 == ret) {
        if (IsGem1p11(pD) == 0){
            ret = CDN_ENOTSUP;
        }
    }

    if (0 == ret) {
        reg = CPS_UncachedRead32(&(pD->regs->rx_water_mark));
        *rxHighWatermark = EMAC_REGS__RX_WATER_MARK__RX_HIGH_WATERMARK__READ(reg);
        *rxLowWatermark |= EMAC_REGS__RX_WATER_MARK__RX_LOW_WATERMARK__READ(reg);
    }

    return ret;
}

uint32_t CEDI_SetRxThresholdControl(CEDI_PrivateData* pD,
                                   const CEDI_WatermarkLvl* watermarkLvl,
                                   uint8_t queueNum)
{
    uint32_t status;
    uint8_t queueOff;
    uint32_t reg;
    uint8_t high;
    uint8_t low;
    volatile uint32_t* regAddr;

    status = CEDI_SetRxThresholdControlSF(pD, watermarkLvl);

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
        regAddr  = rxBuffThresholdCtrl[queueNum / 4U];
        addRegBase(pD, &regAddr);

        queueOff = queueNum % 4U;

        reg = CPS_REG_READ(regAddr);

        // Macros are the same for each register (q03, q47, q8b, qcf)
        if (queueOff == 0U) {
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_0_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_0_LOW_WATERMARK__MODIFY(reg, low);
        } else if (queueOff == 1U) {
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_1_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_1_LOW_WATERMARK__MODIFY(reg, low);
        } else if (queueOff == 2U) {
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_2_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_2_LOW_WATERMARK__MODIFY(reg, low);
        } else {
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_3_HIGH_WATERMARK__MODIFY(reg, high);
            EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_3_LOW_WATERMARK__MODIFY(reg, low);
        }

        CPS_REG_WRITE(regAddr, reg);
    }

    return status;
}

uint32_t CEDI_GetRxThresholdControl(const CEDI_PrivateData* pD,
                                    CEDI_WatermarkLvl* watermarkLvl,
                                    uint8_t queueNum)
{
    uint32_t status;
    uint8_t queueOff;
    uint32_t reg;
    uint8_t high;
    uint8_t low;
    volatile uint32_t* regAddr;

    status = CEDI_GetRxThresholdControlSF(pD, watermarkLvl);

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
        regAddr  = rxBuffThresholdCtrl[queueNum / 4U];
        addRegBase(pD, &regAddr);

        queueOff = queueNum % 4U;

        reg = CPS_REG_READ(regAddr);

        // Macros are the same for each register (q03, q47, q8b, qcf)
        if (queueOff == 0U) {
            high = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_0_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_0_LOW_WATERMARK__READ(reg);
        } else if (queueOff == 1U) {
            high = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_1_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_1_LOW_WATERMARK__READ(reg);
        } else if (queueOff == 2U) {
            high = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_2_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_2_LOW_WATERMARK__READ(reg);
        } else {
            high = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_3_HIGH_WATERMARK__READ(reg);
            low = EMAC_REGS__RX_DESCR_RD_BUF_CTL_Q03__Q_3_LOW_WATERMARK__READ(reg);
        }

        watermarkLvl->high = high;
        watermarkLvl->low = low;
    }

    return status;
}

uint32_t CEDI_SetPreambleConversion(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_SetPreambleConversionSF(pD);

    if (CDN_EOK == status) {
        status = (pD->cfg.ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        regAddr = &(pD->regs->hs_mac_config);
        regVal = CPS_REG_READ(regAddr);

        if (enable) {
            EMAC_REGS__HS_MAC_CONFIG__NSP_CHANGE__SET(regVal);
        } else {
            EMAC_REGS__HS_MAC_CONFIG__NSP_CHANGE__CLR(regVal);
        }
        CPS_REG_WRITE(regAddr, regVal);
    }

    return status;
}

uint32_t CEDI_GetPreambleConversion(const CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPreambleConversionSF(pD, enable);

    if (CDN_EOK == status) {
        status = (pD->cfg.ifTypeSel >= CEDI_IFSP_XGMII) ? CDN_EOK : CDN_ENOTSUP;
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->hs_mac_config));
        *enable = (EMAC_REGS__HS_MAC_CONFIG__NSP_CHANGE__READ(regVal) != 0U);
    }

    return status;
}

static void setRxTestPatternMode(CEDI_TestPatternMode patternMode, uint32_t* regVal)
{
    /* Clear pattern mode bits */
    *regVal &= ~(EMAC_REGS__USX_TEST_CONTROL__RX_PRBS9_EN__MASK    |
                 EMAC_REGS__USX_TEST_CONTROL__RX_PRBS31_EN__MASK   |
                 EMAC_REGS__USX_TEST_CONTROL__RX_TST_EN__MASK      |
                 EMAC_REGS__USX_TEST_CONTROL__RX_TST_DAT_SEL__MASK |
                 EMAC_REGS__USX_TEST_CONTROL__RX_SCR_IDLE_EN__MASK);

    /* for CEDI_NORMAL_OPERATION need not set any bits */
    if (patternMode != CEDI_NORMAL_OPERATION) {
        if (patternMode == CEDI_PRBS_9) {
            EMAC_REGS__USX_TEST_CONTROL__RX_PRBS9_EN__SET(*regVal);
        } else if (patternMode == CEDI_PRBS_31) {
            EMAC_REGS__USX_TEST_CONTROL__RX_PRBS31_EN__SET(*regVal);
        } else if (patternMode == CEDI_SCRAMBLED_ZERO) {
            EMAC_REGS__USX_TEST_CONTROL__RX_TST_EN__SET(*regVal);
            EMAC_REGS__USX_TEST_CONTROL__RX_TST_DAT_SEL__SET(*regVal);
        } else if (patternMode == CEDI_SCRAMBLED_IDLE) {
            EMAC_REGS__USX_TEST_CONTROL__RX_TST_EN__SET(*regVal);
            EMAC_REGS__USX_TEST_CONTROL__RX_SCR_IDLE_EN__SET(*regVal);
        } else {
            /* condition for CEDI_SCRAMBLED_LOCAL_FAULT */
            EMAC_REGS__USX_TEST_CONTROL__RX_TST_EN__SET(*regVal);
        }
    }
}

uint32_t CEDI_SetPcs25gRxTestPatternMode(CEDI_PrivateData* pD, CEDI_TestPatternMode patternMode)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;
    uint32_t mask;

    status = CEDI_SetPcs25gRxTestPatternMSF(pD, patternMode);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        /* CEDI_SQUARE_WAVE is only for Tx */
        if (patternMode == CEDI_SQUARE_WAVE) {
            status = CDN_EINVAL;
        }
    }

    /* check if PCS25G is supported */
    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        if (pD->isRxDatapathEnabled) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "Cannot use %s when Rx datapath is enabled."
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

        if ((regVal & mask) != (uint8_t)CEDI_TEST_PATTERN_MODE) {
            status = CDN_ENOTSUP;
        } else {
            setRxTestPatternMode(patternMode, &regVal);
            CPS_REG_WRITE(regAddr, regVal);
        }
    }

    return status;
}

uint32_t CEDI_GetPcs25gRxTestPatternMode(const CEDI_PrivateData* pD, CEDI_TestPatternMode* patternMode)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPcs25gRxTestPatternMSF(pD, patternMode);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        regVal = CPS_REG_READ(&(pD->regs->usx_test_control));

        if (EMAC_REGS__USX_TEST_CONTROL__RX_PRBS9_EN__READ(regVal) == 1U) {
            *patternMode = CEDI_PRBS_9;
        } else if (EMAC_REGS__USX_TEST_CONTROL__RX_PRBS31_EN__READ(regVal) == 1U) {
            *patternMode = CEDI_PRBS_31;
        } else if (EMAC_REGS__USX_TEST_CONTROL__RX_TST_EN__READ(regVal) == 1U) {

            if (EMAC_REGS__USX_TEST_CONTROL__RX_TST_DAT_SEL__READ(regVal) == 1U) {
                *patternMode = CEDI_SCRAMBLED_ZERO;
            } else if (EMAC_REGS__USX_TEST_CONTROL__RX_SCR_IDLE_EN__READ(regVal) == 1U) {
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

uint32_t CEDI_GetPcs25gRxDecoderErrCount(const CEDI_PrivateData* pD, uint8_t* blockErrorCount)
{
    uint32_t status = CEDI_GetPcs25gRxDecoderErrCoSF(pD, blockErrorCount);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        *blockErrorCount = (uint8_t)CPS_REG_READ(&(pD->regs->usx_rx_decoder_error_counter));

        /* reset counter */
        CPS_REG_WRITE(&(pD->regs->usx_rx_decoder_error_counter), 0U);
    }

    return status;
}

uint32_t CEDI_GetPcs25gTestPatternErrCount(const CEDI_PrivateData* pD, uint16_t* testPatternErrorCount)
{
    uint32_t status = CEDI_GetPcs25gTestPatternErrSF(pD, testPatternErrorCount);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (CDN_EOK == status) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (CDN_EOK == status) {
        *testPatternErrorCount = (uint16_t)CPS_REG_READ(&(pD->regs->usx_test_pattern_error_counter));

        /* reset counter */
        CPS_REG_WRITE(&(pD->regs->usx_test_pattern_error_counter), 0U);
    }

    return status;
}

uint32_t CEDI_GetPcs25gPrbsErrorCount(const CEDI_PrivateData* pD, uint16_t* prbsPatternErrorCount)
{
    uint32_t status = CEDI_GetPcs25gPrbsErrorCountSF(pD, prbsPatternErrorCount);

    if (CDN_EOK == status) {
        *prbsPatternErrorCount = (uint16_t)CPS_REG_READ(&(pD->regs->usx_prbs_error_counter));

        /* reset counter */
        CPS_REG_WRITE(&(pD->regs->usx_prbs_error_counter), 0U);
    }

    return status;
}

uint32_t CEDI_SetPcs25gRxDescrBypassEnable(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_SetPcs25gRxDescrBypassESF(pD);

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
            EMAC_REGS__USX_CONTROL_REGISTER__RX_SCR_BYPASS__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__RX_SCR_BYPASS__CLR(regVal);
        }
        CPS_REG_WRITE(regAddr, regVal);
    }

    return status;
}

uint32_t CEDI_GetPcs25gRxDescrBypassEnable(CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status;
    uint32_t regVal;

    status = CEDI_GetPcs25gRxDescrBypassESF(pD, enable);

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

uint32_t CEDI_SetPcs25gRxDatapathEnable(CEDI_PrivateData* pD, bool enable)
{
    uint32_t status;
    uint32_t regVal;
    volatile uint32_t* regAddr;

    status = CEDI_SetPcs25gRxDatapathEnabSF(pD);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        regAddr = &(pD->regs->usx_control_register);
        regVal = CPS_REG_READ(regAddr);
        if (!enable) {
            EMAC_REGS__USX_CONTROL_REGISTER__RX_SYNC_RESET__SET(regVal);
        } else {
            EMAC_REGS__USX_CONTROL_REGISTER__RX_SYNC_RESET__CLR(regVal);
        }
        CPS_REG_WRITE(regAddr, regVal);
        pD->isRxDatapathEnabled = enable;
    }

    return status;
}

uint32_t CEDI_GetPcs25gRxDatapathEnable(CEDI_PrivateData* pD, bool* enable)
{
    uint32_t status = CEDI_GetPcs25gRxDatapathEnabSF(pD, enable);

    if (CDN_EOK == status) {
        status = checkIfEmac(pD, __func__) ? CDN_EINVAL : CDN_EOK;
    }

    if (status == CDN_EOK) {
        status = isPcs25gSupported(&(pD->cfg), &(pD->hwCfg));
    }

    if (status == CDN_EOK) {
        *enable = pD->isRxDatapathEnabled;
    }

    return status;
}

/** Set status of Send Broadcast/Multicast frames to all queues feature */
uint32_t CEDI_SetSendBroadcastToAllQs(const CEDI_PrivateData *pD, bool enable)
{
    uint32_t status = CEDI_SetSendBroadcastToAllQsSF(pD);

    // Feature is available in 1p13 and up, with virtualization.
    if (status == CDN_EOK) {
        status = IsGem1p13(pD) ? CDN_EOK : CDN_ENOTSUP;
    }
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: gem_vm not set, feature not available\n", __func__);
            status = CDN_ENOTSUP;
        }
    }

    if (status == CDN_EOK) {
        uint32_t regVal = CPS_REG_READ(&pD->regs->dma_config);
        if (enable) {
            EMAC_REGS__DMA_CONFIG__SEND_BCAST_TO_ALL_QS__SET(regVal);
        } else {
            EMAC_REGS__DMA_CONFIG__SEND_BCAST_TO_ALL_QS__CLR(regVal);
        }
        CPS_REG_WRITE(&pD->regs->dma_config, regVal);
    }
    return status;
}

/** Get status of Send Broadcast/Multicast frames to all queues feature */
uint32_t CEDI_GetSendBroadcastToAllQs(const CEDI_PrivateData *pD, bool *enabled)
{
    uint32_t status = CEDI_GetSendBroadcastToAllQsSF(pD, enabled);

    // Feature is available in 1p13 and up, with virtualization.
    if (status == CDN_EOK) {
        status = IsGem1p13(pD) ? CDN_EOK : CDN_ENOTSUP;
    }
    if (CDN_EOK == status) {
        // if qx_status and qx_control registers are not available, return CDN_ENOTSUP
        if (pD->hwCfg.gem_vm == false) {
            vDbgMsg(DBG_GEN_MSG, DBG_WARN, "%s: gem_vm not set, feature not available\n", __func__);
            status = CDN_ENOTSUP;
        }
    }

    if (status == CDN_EOK) {
        uint32_t regVal = CPS_REG_READ(&pD->regs->dma_config);
        *enabled = EMAC_REGS__DMA_CONFIG__SEND_BCAST_TO_ALL_QS__READ(regVal);
    }
    return status;
}
