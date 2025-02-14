/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#include "edd_log.h"
#include "edd_data.h"

void printTxDescList(const CEDI_PrivateData *pD, uint8_t qNum)
{
    uint32_t i,j;
    uint32_t wd[6];
    uint32_t numWd;
    const CEDI_TxQueue *txQ = &(pD->txQueue[qNum]);
    const CEDI_TxDesc *thisDesc;

    log_simple_fyi("\n---  Tx Descriptor List Queue %u  ---\n", qNum);

    thisDesc = txQ->bdBase;
    numWd = (pD->txDescriptorSize[qNum]) >> CEDI_BYTES_PER_WORD_SHIFT;

    for (i = 0; i < ((pD->cfg.txQLen)[qNum]) + 1; i++) {

        log_simple_fyi("d%3u ",i);

        for (j = 0; j < numWd; j++) {
            wd[j] = CPS_UncachedRead32(&thisDesc->word[j]);
            log_simple_fyi("wd%u:%08X  ", j, wd[j]);
        }

        log_simple_fyi("u:%u w:%u l:%u tsV:%u len:%4u %s%s\n",
                    (wd[1] & CEDI_TXD_USED) ? 1 : 0,
                    (wd[1] & CEDI_TXD_WRAP) ? 1 : 0,
                    (wd[1] & CEDI_TXD_LAST_BUF) ? 1 : 0,
                    (wd[1] & CEDI_TXD_TS_VALID) ? 1 : 0,
                    wd[1] & CEDI_TXD_LMASK,
                    (thisDesc == txQ->bdTail) ? "<--tail" : "",
                    (thisDesc == txQ->bdHead) ? "<--head" : "");

        thisDesc = (const CEDI_TxDesc*)(((uintptr_t)thisDesc) + (pD->txDescriptorSize)[qNum]);
    }

    log_simple_fyi("\n");
}

void printRxDescList(const CEDI_PrivateData *pD, uint8_t qNum)
{
    uint32_t i, j, len,numWd, wd[6];
    CEDI_RxDesc* descCounter;
    uintptr_t *thisVP = pD->rxQueue[qNum].rxBufVAddr;

    numWd = (pD->rxDescriptorSize[qNum]) >> CEDI_BYTES_PER_WORD_SHIFT;
    log_simple_fyi("\n---  Rx Descriptor List Queue %u  ---\n", qNum);
    for (i = 0; i <= (pD->cfg.rxQLen)[qNum]; i++) {

        descCounter = (CEDI_RxDesc*)((uint32_t)(pD->rxQueue[qNum].rxDescStart) + i * (pD->rxDescriptorSize)[qNum]);
        log_simple_fyi("d%3u ",i);

        for (j = 0; j < numWd; j++) {
            wd[j] = CPS_UncachedRead32((uint32_t *) &(descCounter->word[j]));
            log_simple_fyi("wd%u:%08X  ",j,wd[j]);
        }

        len = wd[1] & CEDI_RXD_LEN_MASK;

        if (EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(CPS_UncachedRead32(&(pD->regs->network_config)))) {
            len |= (wd[1] & CEDI_RXD_LEN13_FCS_STAT);
        }

        log_simple_fyi("u:%u w:%u s:%u e:%u  add:%08X tsv:%u len:%4u  %s\n",
                    (wd[0] & CEDI_RXD_USED) ? 1 : 0, (wd[0] & CEDI_RXD_WRAP) ? 1 : 0,
                    (wd[1] & CEDI_RXD_SOF) ? 1 : 0, (wd[1] & CEDI_RXD_EOF) ? 1 : 0,
                    wd[0] & CEDI_RXD_ADDR_MASK,(wd[0] & CEDI_RXD_TS_VALID) ? 1 : 0,
                    len,
                    (thisVP == (pD->rxQueue[qNum].rxTailVA)) ? "<-tail" : "");

        if ((wd[0] & CEDI_RXD_USED) && (wd[1] & CEDI_RXD_EOF)) {
            log_simple_fyi("  fcsErr:%u cfi:%u vPri:%u pTag:%u vTag:%u " \
                        "tyReg:%u tyMat:%u sReg:%u sAdd:%u ext:%u uni:%u " \
                        "mul:%u brd:%u\n",
                        (wd[1] & CEDI_RXD_LEN13_FCS_STAT) ? 1 : 0,
                        (wd[1] & CEDI_RXD_CFI) ? 1 : 0,
                        (wd[1] & CEDI_RXD_VLAN_PRI_MASK) >> CEDI_RXD_VLAN_PRI_SHIFT,
                        (wd[1] & CEDI_RXD_PRI_TAG) ? 1 : 0,
                        (wd[1] & CEDI_RXD_VLAN_TAG) ? 1 : 0,
                        (wd[1] & CEDI_RXD_TYP_IDR_CHK_STA_MASK) >> CEDI_RXD_TYP_IDR_CHK_STA_SHIFT,
                        (wd[1] & CEDI_RXD_TYP_MAT_SNP_NCFI) ? 1 : 0,
                        (wd[1] & CEDI_RXD_SPEC_REG_MASK) >> CEDI_RXD_SPEC_REG_SHIFT,
                        (wd[1] & CEDI_RXD_SPEC_ADD_MAT) ? 1 : 0,
                        (wd[1] & CEDI_RXD_EXT_ADD_MAT) ? 1 : 0,
                        (wd[1] & CEDI_RXD_UNI_HASH_MAT) ? 1 : 0,
                        (wd[1] & CEDI_RXD_MULTI_HASH_MAT) ? 1 : 0,
                        (wd[1] & CEDI_RXD_BROADCAST_DET) ? 1 : 0);
        }
#ifdef EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ
        else   /* show header-split flags when relevant */
        if (pD->hwCfg.hdr_split && (wd[0] & CEDI_RXD_USED) && !(wd[1] & CEDI_RXD_EOF)
            && EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(
                CPS_UncachedRead32(&(pD->regs->dma_config)))) {
            log_simple_fyi("                                   hdr:%u eoh:%u\n",
                        (wd[1] & CEDI_RXD_HDR) ? 1 : 0, (wd[1] & CEDI_RXD_EOH) ? 1 : 0);
        }
#endif
        thisVP++;
    }

    log_simple_fyi("\n");
}

void printNetControlReg(const CEDI_PrivateData *pD)
{
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->network_control));

    log_simple_fyi("\nNetCtrlReg (regBase %08X) - loop:%u lbkloc:%u rxEn:%u txEn:%u mdioEn:%u " \
                "wrStat:%u bPres:%u\n               rdSnap:%u rxTStmp:%u enRxPfc:%u enLpi:%u" \
                " uniPtp:%u altSgmii:%u wrUdpOff:%u extTsu:%u oneStepSync:%u pfcCtrl:%u\n",
                pD->cfg.regBase,
                EMAC_REGS__NETWORK_CONTROL__LOOPBACK__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__READ(reg),
                EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__READ(reg));
}

void printDesignCfg(const CEDI_PrivateData *pD)
{
    /* just print registers now - later compare with
     * copied data for testing */
    uint32_t reg;

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug1));
    log_simple_fyi("\nDesign Config Reg 1 - %08X\n", reg);
    log_simple_fyi("   no_pcs:%u",
                EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(reg));
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__SERDES__READ
    log_simple_fyi("  serdes:%u  RDC_50:%u  TDC_50:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__SERDES__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__RDC_50__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__TDC_50__READ(reg));
#endif
    log_simple_fyi("   int_loopback:%u  ext_fifo_ = CPS_UncachedRead32(&(pD->regs->transmit_status));interface:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__READ(reg));
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__NO_INT_LOOPBACK__READ
    log_simple_fyi("   no_int_loopback:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__NO_INT_LOOPBACK__READ(reg));
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV1__READ
    log_simple_fyi("   apb_rev1:%u  apb_rev2:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV1__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV2__READ(reg));
#endif
    log_simple_fyi("   user_io:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__READ(reg));
    log_simple_fyi("   user_out_width:%u  user_in_width:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__READ(reg));
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__NO_SCAN_PINS__READ
    log_simple_fyi("   no_scan_pins:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__NO_SCAN_PINS__READ(reg));
#endif
    log_simple_fyi("   no_stats:%u  no_snapshot:%u  irq_read_clear:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__READ(reg));
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ
    log_simple_fyi("   exclude_cbs:%u  dma_bus_width:%u  axi_cache_value:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__READ(reg));
#else
    log_simple_fyi("   dma_bus_width:%u  axi_cache_value:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__READ(reg));
#endif
    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug2));
    log_simple_fyi("Design Config Reg 2 - %08X\n", reg);
    log_simple_fyi("   jumbo_max_length:%u  hprot_value:%u  :%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__READ(reg));
    log_simple_fyi("   tx_pkt_buffer:%u  rx_pbuf_addr:%u  tx_pbuf_addr:%u  axi:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG2__AXI__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug3));
    log_simple_fyi("Design Config Reg 3 - %08X\n", reg);
    log_simple_fyi("   num_spec_add_filters:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug4));
    log_simple_fyi("Design Config Reg 4 - %08X\n", reg);

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug5));
    log_simple_fyi("Design Config Reg 5 - %08X\n", reg);
    log_simple_fyi("   rx_fifo_cnt_width:%u  tx_fifo_cnt_width:%u  tsu:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__TSU__READ(reg));
    log_simple_fyi("   phy_ident:%u  dma_bus_width_def:%u  mdc_clock_div:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__READ(reg));
    log_simple_fyi("   endian_swap_def:%u  rx_pbuf_size_def:%u  tx_pbuf_size_def:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__READ(reg));
    log_simple_fyi("   rx_buffer_length_def:%u  tsu_clk:%u  axi_prot_value:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug6));
    log_simple_fyi("Design Config Reg 6 - %08X\n", reg);
    log_simple_fyi("   dma_priority_queue1:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__READ(reg));
    log_simple_fyi("   dma_priority_queue2:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__READ(reg));
    log_simple_fyi("   dma_priority_queue3:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__READ(reg));
    log_simple_fyi("   dma_priority_queue4:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__READ(reg));
    log_simple_fyi("   dma_priority_queue5:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__READ(reg));
    log_simple_fyi("   dma_priority_queue6:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__READ(reg));
    log_simple_fyi("   dma_priority_queue7:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__READ(reg));
    log_simple_fyi("   dma_priority_queue8:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__READ(reg));
    log_simple_fyi("   dma_priority_queue9:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__READ(reg));
    log_simple_fyi("   dma_priority_queue10:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__READ(reg));
    log_simple_fyi("   dma_priority_queue11:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__READ(reg));
    log_simple_fyi("   dma_priority_queue12:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__READ(reg));
    log_simple_fyi("   dma_priority_queue13:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__READ(reg));
    log_simple_fyi("   dma_priority_queue14:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__READ(reg));
    log_simple_fyi("   dma_priority_queue15:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__READ(reg));
    log_simple_fyi("   tx_pbuf_queue_segment_size:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__READ(reg));
    log_simple_fyi("   ext_tsu_timer:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__READ(reg));
    log_simple_fyi("   tx_add_fifo_if:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__READ(reg));
    log_simple_fyi("   host_if_soft_select:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__READ(reg));
    log_simple_fyi("   emac_dma_addr_width_is_64b:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__READ(reg));
    log_simple_fyi("   pfc_multi_quantum:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__READ(reg));
/*[% IF GEM_PBUF_LSO=="1" -%]*/
//  log_simple_fyi("   pbuf_lso:%u  ", EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__READ(reg));
/*[% ELSE -%]*/
//  log_simple_fyi("   pbuf_lso:0  ");
/*[% END -%]*/
    log_simple_fyi("intrpt_mod:%u  hdr_split:%u\n",
                pD->hwCfg.intrpt_mod, pD->hwCfg.hdr_split);
    log_simple_fyi("   pbuf_cutthru:%u\n", EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug7));
    log_simple_fyi("Design Config Reg 7 - %08X\n", reg);
    log_simple_fyi("   tx_pbuf_num_segments_q0:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q1:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q2:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q3:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q4:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q5:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q6:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q7:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug8));
    log_simple_fyi("Design Config Reg 8 - %08X\n", reg);
    log_simple_fyi("   num_type1_screeners:%u  num_type2_screeners:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__READ(reg));
    log_simple_fyi("   num_scr2_ethtype_regs:%u  num_scr2_compare_regs:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__READ(reg),
                EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug9));
    log_simple_fyi("Design Config Reg 9 - %08X\n", reg);
    log_simple_fyi("   tx_pbuf_num_segments_q8:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q9:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q10:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q11:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q12:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q13:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q14:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__READ(reg));
    log_simple_fyi("   tx_pbuf_num_segments_q15:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__READ(reg));

    reg = CPS_UncachedRead32(&(pD->regs->designcfg_debug10));
    log_simple_fyi("Design Config Reg 10 - %08X\n", reg);
    log_simple_fyi("   axi_rx_descr_wr_buff_bits:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_WR_BUFF_BITS__READ(reg));
    log_simple_fyi("   axi_tx_descr_wr_buff_bits:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_WR_BUFF_BITS__READ(reg));
    log_simple_fyi("   axi_rx_descr_rd_buff_bits:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_RD_BUFF_BITS__READ(reg));
    log_simple_fyi("   axi_tx_descr_rd_buff_bits:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_RD_BUFF_BITS__READ(reg));
    log_simple_fyi("   axi_access_pipeline_bits:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__READ(reg));
    log_simple_fyi("   rx_pbuf_data:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__READ(reg));
    log_simple_fyi("   tx_pbuf_data:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__READ(reg));
    log_simple_fyi("   emac_bus_width:%u\n",
                EMAC_REGS__DESIGNCFG_DEBUG10__EMAC_BUS_WIDTH__READ(reg));
}

void printNetConfigReg(const CEDI_PrivateData *pD)
{
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->network_config));

    log_simple_fyi("\nNetwork Config Reg (regBase %08X)-\n" \
                "         speed:%7s  fulldup:%u      vlanOnly:%u         jumbo:%u\n" \
                "       copyAll:%u        noBroad:%u       multiEn:%u     unicastEn:%u\n" \
                "        rx1536:%u       extAddEn:%u    gigabit_En:%u        p = CPS_UncachedRead32(&(pD->regs->transmit_status));csSel:%u\n" \
                "     retryTest:%u        pauseEn:%u     rxBufOffs:%u  rxLenErrDisc:%u\n" \
                "     fcsRemove:%u      mdcClkDiv:%u     dBusWidth:%u  disCopyPause:%u\n" \
                "    rxChkOffEn:%u  rxHalfDupTxEn:%u   ignoreRxCrc:%u       sgmiiEn:%u\n" \
                "    ipgStretch:%u  rxBadPreamble:%u  ignoreIpgErr:%u      uniDirEn:%u\n",
                pD->cfg.regBase,
                EMAC_REGS__NETWORK_CONFIG__SPEED__READ(reg) ? "100Mbps" : "10Mbps ",
                EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__NSP_ACCEPT__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__READ(reg),
                EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__READ(reg)
                );
}

void printNetStatusReg(const CEDI_PrivateData *pD)
{
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->network_status));
    log_simple_fyi("\nNetwork Status Reg = %08X\n", reg);
}

void printDmaConfigReg(const CEDI_PrivateData *pD)
{
    uint32_t reg = CPS_UncachedRead32(&(pD->regs->dma_config));
    log_simple_fyi("\nDMA Config Reg = %08X\n", reg);
}

void printTxStatus(uint8_t emacObj)
{
    CEDI_TxStatus txStatus;
    uint32_t result = CEDI_GetTxStatus(privData[emacObj], &txStatus);

    if (result != CDN_EOK) {
        log_simple_fyi("Cannot read MAC%u TxStatus\n", emacObj);
    } else {
        log_simple_fyi("MAC TxStatus: %s %s %s %s %s %s %s %s %s\n",
                    txStatus.txComplete ? "txFrComplete" : "",
                    txStatus.usedBitRead ? "usedRead" : "",
                    txStatus.collisionOcc ? "collision" : "",
                    txStatus.retryLimExc ? "retryExceeded" : "",
                    txStatus.txActive ? "txActive" : "",
                    txStatus.txFrameErr ? "frameErr" : "",
                    txStatus.txUnderRun ? "txUnderrun" : "",
                    txStatus.lateCollision ? "lateColl" : "",
                    txStatus.hRespNotOk ? "HrespNotOk" : "");
    }
}

void printRxVAddrList(CEDI_PrivateData *pD, uint8_t qNum)
{
    uint32_t i;
    uintptr_t *thisVP = pD->rxQueue[qNum].rxBufVAddr;

    log_simple_fyi("---  Rx Buffer Virtual Addresses List Queue %u  ---\n", qNum);
    for (i = 0; i <= (pD->cfg.rxQLen)[qNum]; i++) {
        log_simple_fyi("d%3u  virt: %08X  %s\n", i,
                    (pD->rxQueue[qNum].rxBufVAddr[i]),
                    (thisVP == (pD->rxQueue[qNum].rxTailVA)) ? "<-tail" : "");
        thisVP++;
    }
}

void printStatsCopy(const CEDI_PrivateData *pD)
{
    log_simple_fyi("\nStatistics regs copy (MAC%u)-\n" \
                "          octetsTx:  0x%08X %08X\n" \
                "          framesTx:%3u        broadcastTx:%u         multicastTx:%u           pauseFrTx:%u  \n" \
                "        fr64byteTx:%u       fr65_127byteTx:%u     fr128_255byteTx:%u     fr256_511byteTx:%u\n" \
                "  fr512_1023byteTx:%u    fr1024_1518byteTx:%u       fr1519_byteTx:%u        underrunFrTx:%u\n" \
                "    singleCollFrTx:%u        multiCollFrTx:%u      excessCollFrTx:%u        lateCollFrTx:%u\n" \
                "      deferredFrTx:%u       carrSensErrsTx:%u\n" \
                "          octetsRx:  0x%08X %08X\n" \
                "          framesRx:%3u        broadcastRx:%u         multicastRx:%u           pauseFrRx:%u  \n" \
                "        fr64byteRx:%u       fr65_127byteRx:%u     fr128_255byteRx:%u     fr256_511byteRx:%u\n" \
                "  fr512_1023byteRx:%u    fr1024_1518byteRx:%u       fr1519_byteRx:%u       undersizeFrRx:%u\n" \
                "      oversizeFrRx:%u            jabbersRx:%u         fcsErrorsRx:%u         lenChkErrRx:%u\n" \
                "      rxSymbolErrs:%u          alignErrsRx:%u       rxResourcErrs:%u         overrunFrRx:%u\n" \
                "      ipChksumErrs:%u        tcpChksumErrs:%u       udpChksumErrs:%u      dmaRxPBufFlush:%u\n",
                (pD->cfg.regBase == (uintptr_t)emac_reg_base[0]) ? 0 : 1,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->octetsTxHi,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->octetsTxLo,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->framesTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->broadcastTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->multicastTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->pauseFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr64byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr65_127byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr128_255byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr256_511byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr512_1023byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr1024_1518byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr1519_byteTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->underrunFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->singleCollFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->multiCollFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->excessCollFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->lateCollFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->deferredFrTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->carrSensErrsTx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->octetsRxHi,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->octetsRxLo,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->framesRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->broadcastRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->multicastRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->pauseFrRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr64byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr65_127byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr128_255byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr256_511byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr512_1023byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr1024_1518byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fr1519_byteRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->undersizeFrRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->oversizeFrRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->jabbersRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->fcsErrorsRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->lenChkErrRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->rxSymbolErrs,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->alignErrsRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->rxResourcErrs,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->overrunFrRx,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->ipChksumErrs,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->tcpChksumErrs,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->udpChksumErrs,
                ((CEDI_Statistics *)pD->cfg.statsRegs)->dmaRxPBufFlush );
}

void printRxStatus(uint8_t emacInst)
{
    CEDI_RxStatus rxStatus;
    uint32_t set = emacObj[emacInst]->getRxStatus(privData[emacInst], &rxStatus);
    if (!set) {
        log_simple_fyi("MAC%u RxStatus = (all clear)\n", emacInst);
    } else {
        log_simple_fyi("MAC%u RxStatus = %s %s %s %s\n",
                    emacInst,
                    rxStatus.buffNotAvail ? "bufNotAvail" : "",
                    rxStatus.frameRx ? "rxFrame" : "",
                    rxStatus.rxOverrun ? "rxOverrun" : "",
                    rxStatus.hRespNotOk ? "HrespNotOk" : "");
    }
}

void printEthHeader(CEDI_BuffAddr* buffer, uint16_t bufNum, uint16_t extraBytes)
{
    uint16_t j, i;
    uint8_t data;
    uint8_t* addr;
    //CEDI_BuffAddr* localBuf;

    for (i = 0; i < bufNum; i++) {
        //localBuf = &(buffer[i]);
        for (j = 0; j < (sizeof(ethHdr_t)/sizeof(uint8_t)) + extraBytes; j++) {
            addr = ((uint8_t*)(buffer->vAddr))+ j;
            data = CPS_UncachedRead8(addr);
            log_simple_fyi("%02X ", byte0(data));
        }
        log_simple_fyi("\n");
    }
}
