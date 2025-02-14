/**********************************************************************
 * Copyright (C) 2014-2023 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.06.f48696b
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core Driver for the Cadence Ethernet MAC (EMAC) core. This
 * header file lists the API providing a HAL (hardware abstraction
 * layer) interface for the EMAC core, GEM_GXL  part no. IP7014
 **********************************************************************/

#ifndef CEDI_PRIV_H
#define CEDI_PRIV_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */
/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */

#include "cedi_if.h"
#include "cedi_structs_if.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** Tx Descriptor flags/status - word 1 only */
#define	CEDI_TXD_LAST_BUF (1UL << 15U)

#define	CEDI_TXD_NO_AUTO_CRC (1UL << 16U)

#define	CEDI_TXD_UFO_ENABLE (1UL << 17U)

#define	CEDI_TXD_TSO_ENABLE (1UL << 18U)

#define	CEDI_TXD_AUTOSEQ_SEL (1UL << 19U)

#define	CEDI_TXD_CHKOFF_SHIFT 20U

#define	CEDI_TXD_CHKOFF_MASK (7UL << CEDI_TXD_CHKOFF_SHIFT)

#define	CEDI_TXD_TS_VALID (1UL << 23U)

#define	CEDI_TXD_STREAM_SHIFT 24U

#define	CEDI_TXD_STREAM_MASK (3UL << CEDI_TXD_STREAM_SHIFT)

#define	CEDI_TXD_LATE_COLL (1UL << 26U)

#define	CEDI_TXD_FR_CORR (1UL << 27U)

#define	CEDI_TXD_UNDERRUN (1UL << 28U)

#define	CEDI_TXD_RETRY_EXC (1UL << 29U)

#define	CEDI_TXD_WRAP (1UL << 30U)

#define	CEDI_TXD_USED (1UL << 31U)

/** MSS/MFS only used on word 1 of 2nd descriptor */
#define	CEDI_TXD_MSSMFS_SHIFT 16U

#define	CEDI_TXD_MSSMFS_MASK (0x3FFFUL << CEDI_TXD_MSSMFS_SHIFT)

#define	CEDI_TXD_LEN_MASK ((1UL << 14U) - 1U)

/** Rx Descriptor flags - word 0 */
#define	CEDI_RXD_USED (1UL << 0U)

#define	CEDI_RXD_WRAP (1UL << 1U)

#define	CEDI_RXD_TS_VALID (1UL << 2U)

#define	CEDI_RXD_ADDR_MASK (0xFFFFFFFCU)

#define	CEDI_RXD_ADDR_SHIFT 2U

/** Rx Descriptor flags/status - word 1 only */
#define	CEDI_RXD_LEN_MASK ((1UL << 13U) - 1U)

/** *** need to include bit 13 if jumbo frames enabled *** */
#define	CEDI_RXD_LEN13_FCS_STAT (1UL << 13U)

#define	CEDI_RXD_SOF (1UL << 14U)

#define	CEDI_RXD_EOF (1UL << 15U)

#define	CEDI_RXD_CFI (1UL << 16U)

#define	CEDI_RXD_VLAN_PRI_SHIFT 17U

#define	CEDI_RXD_VLAN_PRI_MASK (7UL << CEDI_RXD_VLAN_PRI_SHIFT)

/** if header-data splitting, these definitions are valid when not EOF: header buffer */
#define	CEDI_RXD_HDR (1UL << 16U)

/** end of header */
#define	CEDI_RXD_EOH (1UL << 17U)

/**
 * CRC error when reporting bad FCS
 * in bit 16 of word 1 of the receive buffer descriptor is enabled
 *
*/
#define	CEDI_RXD_CRC (1UL << 16U)

#define	CEDI_RXD_PRI_TAG (1UL << 20U)

#define	CEDI_RXD_VLAN_TAG (1UL << 21U)

/** either Type ID match register or (if Rx chksum offload enabled) checksum status */
#define	CEDI_RXD_TYP_IDR_CHK_STA_SHIFT 22U

#define	CEDI_RXD_TYP_IDR_CHK_STA_MASK (3UL << CEDI_RXD_TYP_IDR_CHK_STA_SHIFT)

/** either Type ID matched or (if Rx chksum offload enabled) SNAP encoded and no CFI */
#define	CEDI_RXD_TYP_MAT_SNP_NCFI (1UL << 24U)

#define	CEDI_RXD_SPEC_REG_SHIFT 25U

#define	CEDI_RXD_SPEC_REG_MASK (3UL << CEDI_RXD_SPEC_REG_SHIFT)

#define	CEDI_RXD_SPEC_ADD_MAT (1UL << 27U)

#define	CEDI_RXD_EXT_ADD_MAT (1UL << 28U)

#define	CEDI_RXD_UNI_HASH_MAT (1UL << 29U)

#define	CEDI_RXD_MULTI_HASH_MAT (1UL << 30U)

#define	CEDI_RXD_BROADCAST_DET (1UL << 31U)

/** For Tx/Rx time stamp extraction from descriptor words */
#define	CEDI_TS_NANO_SEC_MASK 0x3FFFFFFFU

#define	CEDI_TS_SEC0_SHIFT 30U

#define	CEDI_TS_SEC1_MASK 0x0FU

#define	CEDI_TS_SEC1_POS_SHIFT 2U

#define	CEDI_TS_SEC_WIDTH 6U

#define	CEDI_TS_SEC_TOP (1UL << CEDI_TS_SEC_WIDTH)

#define	CEDI_TS_SEC_MASK (CEDI_TS_SEC_TOP - 1U)

/** For Tx time launch time configuration in descriptor words */
#define	CEDI_TLT_NANO_SEC_MASK 0x3FFFFFFFU

#define	CEDI_TLT_SECS_SHIFT 30U

#define	CEDI_TLT_UTLT (1UL << 31U)

/** Offset of registers for Express MAC relative to Preemptive MAC. */
#define	CEDI_EXPRESS_MAC_REGS_OFFSET 0x1000U

/** Offset of registers for ASF relative to MAC registers */
#define	CEDI_ASF_REGS_OFFSET 0xE00U

#define	CEDI_RXD_EMPTY 0xFFAA0000U

#define	CEDI_PHY_ADDR_OP 0U

#define	CEDI_PHY_WRITE_OP 1U

#define	CEDI_PHY_CL22_READ_OP 2U

#define	CEDI_PHY_CL45_READ_INC_OP 2U

#define	CEDI_PHY_CL45_READ_OP 3U

/** Size required for two buffer descriptor word (in bytes). */
#define	CEDI_TWO_BD_WORD_SIZE 8U

/** Shift variable for number of bytes in a word */
#define	CEDI_BYTES_PER_WORD_SHIFT 2U

#define	CEDI_MIN_TXBD 1U

#define	CEDI_MIN_RXBD 1U

/** maximum index of screener type 2 register */
#define	CEDI_COMPARE_MAX_INDEX 31U

/** number of available speeds for high-speed mode */
#define	CEDI_HS_AVAILABLE_SPEEDS_NUM 6U

/** number of attemps of polling PCS25G synchronization */
#define	CEDI_PCS25G_MAX_POLLING_ATTEMPS 500U

/** time beetwen next sync polling attemp for PCS25G in nanoseconds */
#define	CEDI_PCS25G_POLLING_WAIT_NS 1000U

/** Number of queues supported by EnST (always highest) */
#define	CEDI_TX_ENST_QUEUES 8U

/**
 *  @}
 */


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */


/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** Forward declaration of structure for private data */
struct CEDI_PrivateData_s
{
    /** copy of CEDI_Config info supplied to init */
    CEDI_Config cfg;
    /** pointers to callback functions */
    CEDI_Callbacks cb;
    /** copy of DesignCfg Debug registers */
    CEDI_DesignCfg hwCfg;
    /** typed pointer to register devices */
    struct emac_regs* regs;
    /** number of Qs in this h/w config */
    uint8_t numQs;
    /** number of transmit queues */
    uint8_t txQs;
    /** number of receive queues */
    uint8_t rxQs;
    /** tx queue info */
    CEDI_TxQueue txQueue[CEDI_MAX_TX_QUEUES];
    /** rx queue info */
    CEDI_RxQueue rxQueue[CEDI_MAX_RX_QUEUES];
    /** retain link status (low) until read */
    uint8_t anLinkStat;
    /** retain link partner remote fault status (high) until read */
    uint8_t anRemFault;
    /** auto-negotiation in progress flag */
    uint8_t autoNegActive;
    /** data expected from link partner: set initially to indicate base page, clear after first received to denote next page  expected. Set on start auto-negotiation. */
    uint8_t basePageExp;
    /** reserved for passing page Rx in callback */
    CEDI_LpPageRx lpPageRx;
    /** reserved for a-n status in callback */
    CEDI_NetAnStatus anStatus;
    /** reserved for passing ptp event times */
    CEDI_1588TimerVal ptpTime;
    /** bytes per Tx descriptor */
    uint16_t txDescriptorSize[CEDI_MAX_TX_QUEUES];
    /** bytes per Rx descriptor */
    uint16_t rxDescriptorSize[CEDI_MAX_RX_QUEUES];
    /** flags containing information, whether or not FRER is enabled */
    uint8_t frerEnabled[CEDI_MAX_RX_QUEUES];
    /** pointer to second mac (is set only if mac type is pMac or eMac) */
    CEDI_PrivateData* otherMac;
    /** MAC Type eMac, pMac, mac (default MAC) */
    CEDI_MacType macType;
    /**
     * Describes if Tx datapath is enabled for Tx PCS25G.
     * If PCS is not set, value is 'false'
    */
    bool isTxDatapathEnabled;
    /**
     * Desicribes if Rx datapath is enabled for Rx PCS25G.
     * If PCS is not set, value is 'false'
    */
    bool isRxDatapathEnabled;
};

/**
 *  @}
 */

/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* CEDI_PRIV_H */
