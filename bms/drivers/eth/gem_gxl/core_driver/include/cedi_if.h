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

#ifndef CEDI_IF_H
#define CEDI_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */

#include "cdn_stdint.h"
#include "emac_registers.h"
#include "cdn_errno.h"
#include "cdn_stdtypes.h"

#define ETH_NUMS 4

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/**
 * General config.
 * @xmlonly <defstofollow>4</defstofollow> REMOVE_ME @endxmlonly
 * Max number of Rx priority queues supported by driver
*/
#define	CEDI_MAX_RX_QUEUES (16U)

/** Max number of Tx priority queues supported by driver */
#define	CEDI_MAX_TX_QUEUES (16U)

/** Allows en/disabling of events on all priority queues */
#define	CEDI_ALL_QUEUES (255U)

/** Max size of each Rx buffer descriptor list */
#define	CEDI_MAX_RBQ_LENGTH (1000U)

/** max size of each Tx buffer descriptor list */
#define	CEDI_MAX_TBQ_LENGTH (1000U)

#define	CEDI_RX_MAX_BUFFER_OFFSET 3U

/** Bit-flags to specify DMA endianism. @xmlonly <defstofollow>1</defstofollow> REMOVE_ME @endxmlonly */
#define	CEDI_END_SWAP_DESC (0x01U)

#define	CEDI_END_SWAP_DATA (0x02U)

/** Bit-flags to specify DMA config register bits 24-27; see EMAC User Guide for details. @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly */
#define	CEDI_CFG_DMA_DISC_RXP (0x01U)

#define	CEDI_CFG_DMA_FRCE_RX_BRST (0x02U)

#define	CEDI_CFG_DMA_FRCE_TX_BRST (0x04U)

/**
 * Bit-flags to specify checksum offload operation.
 * @xmlonly <defstofollow>1</defstofollow> REMOVE_ME @endxmlonly
*/
#define	CEDI_CFG_CHK_OFF_TX (0x01U)

#define	CEDI_CFG_CHK_OFF_RX (0x02U)

/**
 * Bit-flags for selecting interrupts to enable/disable/read.
 * @xmlonly <defstofollow>28</defstofollow> REMOVE_ME @endxmlonly
 * Frame has been transmitted successfully
*/
#define	CEDI_EV_TX_COMPLETE (0x00000001U)

/** Used bit set has been read in Tx descriptor list */
#define	CEDI_EV_TX_USED_READ (0x00000002U)

/** Tx underrun */
#define	CEDI_EV_TX_UNDERRUN (0x00000004U)

/** Retry limit exceeded or late collision */
#define	CEDI_EV_TX_RETRY_EX_LATE_COLL (0x00000008U)

/** Tx frame corruption */
#define	CEDI_EV_TX_FR_CORRUPT (0x00000010U)

/** Frame received successfully and stored */
#define	CEDI_EV_RX_COMPLETE (0x00000020U)

/** Used bit set has been read in Rx descriptor list */
#define	CEDI_EV_RX_USED_READ (0x00000040U)

/** Rx overrun error */
#define	CEDI_EV_RX_OVERRUN (0x00000080U)

/** DMA hresp not OK */
#define	CEDI_EV_HRESP_NOT_OK (0x00000100U)

/** PCS auto-negotiation link partner page received */
#define	CEDI_EV_PCS_LP_PAGE_RX (0x00000200U)

/** PCS auto-negotiation has completed */
#define	CEDI_EV_PCS_AN_COMPLETE (0x00000400U)

/** Link status change detected by PCS */
#define	CEDI_EV_PCS_LINK_CHANGE_DET (0x00000800U)

/** Pause frame transmitted */
#define	CEDI_EV_PAUSE_FRAME_TX (0x00001000U)

/** Pause time reaches zero or zeroq pause frame received */
#define	CEDI_EV_PAUSE_TIME_ZERO (0x00002000U)

/** Pause frame with non-zero quantum received */
#define	CEDI_EV_PAUSE_NZ_QU_RX (0x00004000U)

/** PTP delay_req frame transmitted */
#define	CEDI_EV_PTP_TX_DLY_REQ (0x00008000U)

/** PTP sync frame transmitted */
#define	CEDI_EV_PTP_TX_SYNC (0x00010000U)

/** PTP pdelay_req frame transmitted */
#define	CEDI_EV_PTP_TX_PDLY_REQ (0x00020000U)

/** PTP pdelay_resp frame transmitted */
#define	CEDI_EV_PTP_TX_PDLY_RSP (0x00040000U)

/** PTP delay_req frame received */
#define	CEDI_EV_PTP_RX_DLY_REQ (0x00080000U)

/** PTP sync frame received */
#define	CEDI_EV_PTP_RX_SYNC (0x00100000U)

/** PTP pdelay_req frame received */
#define	CEDI_EV_PTP_RX_PDLY_REQ (0x00200000U)

/** PTP pdelay_resp frame received */
#define	CEDI_EV_PTP_RX_PDLY_RSP (0x00400000U)

/** TSU seconds register increment */
#define	CEDI_EV_TSU_SEC_INC (0x00800000U)

/** TSU timer count match */
#define	CEDI_EV_TSU_TIME_MATCH (0x01000000U)

/** Management Frame Sent */
#define	CEDI_EV_MAN_FRAME (0x02000000U)

/** LPI indication status bit change received */
#define	CEDI_EV_LPI_CH_RX (0x04000000U)

/** Wake on LAN event received */
#define	CEDI_EV_WOL_RX (0x08000000U)

/** External input interrupt detected */
#define	CEDI_EV_EXT_INTR (0x10000000U)

/** RX lockup has been detected */
#define	CEDI_EV_RX_LOCKUP (0x40000000U)

/** TX lockup has been detected */
#define	CEDI_EV_TX_LOCKUP (0x80000000U)

/** Bit-flags for indicating functionality supported by the driver/EMAC @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly Large Segmentation Offload */
#define	CEDI_CAP_LSO (0x00000001U)

/** Receive Side Coalescing offload */
#define	CEDI_CAP_RSC (0x00000002U)

/** Receive Side Scaling offload */
#define	CEDI_CAP_RSS (0x00000004U)

/** Bit-flags for selecting Tx Status fields to reset. @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly */
#define	CEDI_TXS_USED_READ (0x0001U)

#define	CEDI_TXS_COLLISION (0x0002U)

#define	CEDI_TXS_RETRY_EXC (0x0004U)

#define	CEDI_TXS_FRAME_ERR (0x0010U)

#define	CEDI_TXS_TX_COMPLETE (0x0020U)

#define	CEDI_TXS_UNDERRUN (0x0040U)

#define	CEDI_TXS_LATE_COLL (0x0080U)

#define	CEDI_TXS_HRESP_ERR (0x0100U)

/** Bit-flags for selecting Tx-related q_status fields to reset. @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly */
#define	CEDI_TXSQ_TX_COMPLETE 16U

#define	CEDI_TXSQ_USED_BIT_READ 32U

#define	CEDI_TXSQ_BUFF_EX_MID 64U

/**
 * Bit-flags for selecting Rx Status fields to reset.
 * @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly
*/
#define	CEDI_RXS_NO_BUFF (0x0001U)

#define	CEDI_RXS_FRAME_RX (0x0002U)

#define	CEDI_RXS_OVERRUN (0x0004U)

#define	CEDI_RXS_HRESP_ERR (0x0008U)

/**
 * Bit-flags for selecting Rx-related q_status fields to reset.
 * @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly
*/
#define	CEDI_RXSQ_FRAME_RX 1U

#define	CEDI_RXSQ_USED_BIT_READ 2U

/** High bit error status triggered */
#define	CEDI_EV_PCS25G_BER 0x00000008U

/** Block lock for PCS frame was achieved */
#define	CEDI_EV_PCS25G_FEC_BLOCK_LOCK 0x00000100U

/** FEC uncorrectable error occurred */
#define	CEDI_EV_PCS25G_FEC_UNCORRECT 0x00010000U

/** FEC correctable error occurred */
#define	CEDI_EV_PCS25G_FEC_CORRECT 0x00100000U

/** All events for PCS25G */
#define	CEDI_EVSET_PCS25G_ALL_EVENTS 0x00110108U

/**
 * Transmit IP/TCP/UDP checksum generation offload errors
 * reported in Tx descriptor status.
 * @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly
*/
#define	CEDI_TXD_CHKOFF_NO_ERROR (0U)

#define	CEDI_TXD_CHKOFF_VLAN_HDR_ERR (1U)

#define	CEDI_TXD_CHKOFF_SNAP_HDR_ERR (2U)

#define	CEDI_TXD_CHKOFF_INVALID_IP (3U)

#define	CEDI_TXD_CHKOFF_INVALID_PKT (4U)

#define	CEDI_TXD_CHKOFF_PKT_FRAGMENT (5U)

#define	CEDI_TXD_CHKOFF_NON_TCP_UDP (6U)

#define	CEDI_TXD_CHKOFF_PREM_END_PKT (7U)

/**
 * Bit-flags to control queueTxBuf/qTxBuf behaviour.
 * @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly
 * Indicates last buffer in frame
*/
#define	CEDI_TXB_LAST_BUFF (0x01U)

/** EMAC will not calculate & insert frame CRC. */
#define	CEDI_TXB_NO_AUTO_CRC (0x02U)

/**
 * Prevents transmission being started automatically
 * after queueing the last buffer in the frame;
 * has no effect if CEDI_TXB_LAST_BUFF not also present.
*/
#define	CEDI_TXB_NO_AUTO_START (0x04U)

/** select TCP encapsulation for the current frame - must be set for first and second buffers in frame, ie header and first data buffers */
#define	CEDI_TXB_TCP_ENCAP (0x08U)

/** select UFO fragmentation for the current frame - only relevant for first buffer in frame, which includes the header only; Ignored if CEDI_TXB_TCP_ENCAP is set. */
#define	CEDI_TXB_UDP_ENCAP (0x10U)

/**
 * select auto sequence-number generation, based on the current value of
 * the EMAC sequence number counter for this stream
*/
#define	CEDI_TXB_TSO_AUTO_SEQ (0x20U)

/** Enable Transmit Launch Time */
#define	CEDI_TXB_ENABLE_TLT (0x40U)

/** Max length accepted by queueTxBuf */
#define	CEDI_TXD_LMASK (0x4000U - 1U)

/** TCP flags (standard, some used to control RSC) @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly */
#define	CEDI_TCP_FLG_FIN (0x0001U)

#define	CEDI_TCP_FLG_SYN (0x0002U)

#define	CEDI_TCP_FLG_RST (0x0004U)

#define	CEDI_TCP_FLG_PSH (0x0008U)

#define	CEDI_TCP_FLG_ACK (0x0010U)

#define	CEDI_TCP_FLG_URG (0x0020U)

/**
 * Bit-flags to control MDIO write/read operations.
 * @xmlonly <defstofollow>2</defstofollow> REMOVE_ME @endxmlonly
*/
#define	CEDI_MDIO_FLG_CLAUSE_22 (0x00U)
#define	CEDI_MDIO_FLG_CLAUSE_45 (0x01U)

#define	CEDI_MDIO_FLG_SET_ADDR (0x02U)

#define	CEDI_MDIO_FLG_INC_ADDR (0x04U)

/**
 * PFC Priority based pause frame support:
 * Maximum number of quantum priorities supported.
*/
#define	CEDI_QUANTA_PRIORITY_MAX 8U

/**
 * Bit-flags for selecting MMSL-related interrupts to enable/disable/read.
 * @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly
*/
#define	CEDI_MMSL_EV_RCV_R_ERR (0x01U)

#define	CEDI_MMSL_EV_RCV_V_ERR (0x02U)

#define	CEDI_MMSL_EV_SMDS_ERR (0x04U)

#define	CEDI_MMSL_EV_SMDC_ERR (0x08U)

#define	CEDI_MMSL_EV_FR_COUNT_ERR (0x10U)

#define	CEDI_MMSL_EV_SMD_ERR (0x20U)

/** Maximum number of words allowed in a descriptor */
#define	CEDI_DESC_WORD_NUM_MAX 6U

/**
 *  @}
 */

#define	CEDI_EVSET_ALL_Q0_EVENTS (CEDI_EV_TX_COMPLETE|CEDI_EV_TX_USED_READ| CEDI_EV_TX_UNDERRUN|CEDI_EV_TX_FR_CORRUPT| CEDI_EV_TX_RETRY_EX_LATE_COLL| CEDI_EV_RX_COMPLETE|CEDI_EV_RX_USED_READ|CEDI_EV_RX_OVERRUN|CEDI_EV_HRESP_NOT_OK| CEDI_EV_PCS_LP_PAGE_RX|CEDI_EV_PCS_AN_COMPLETE|CEDI_EV_PCS_LINK_CHANGE_DET| CEDI_EV_PAUSE_FRAME_TX|CEDI_EV_PAUSE_TIME_ZERO|CEDI_EV_PAUSE_NZ_QU_RX| CEDI_EV_PTP_TX_DLY_REQ|CEDI_EV_PTP_TX_SYNC|CEDI_EV_PTP_TX_PDLY_REQ| CEDI_EV_PTP_TX_PDLY_RSP|CEDI_EV_PTP_RX_DLY_REQ|CEDI_EV_PTP_RX_SYNC| CEDI_EV_PTP_RX_PDLY_REQ|CEDI_EV_PTP_RX_PDLY_RSP| CEDI_EV_TSU_SEC_INC|CEDI_EV_TSU_TIME_MATCH| CEDI_EV_MAN_FRAME|CEDI_EV_LPI_CH_RX|CEDI_EV_WOL_RX| CEDI_EV_RX_LOCKUP|CEDI_EV_TX_LOCKUP| CEDI_EV_EXT_INTR )

#define	CEDI_EVSET_ALL_QN_EVENTS (CEDI_EV_TX_COMPLETE| CEDI_EV_TX_RETRY_EX_LATE_COLL| CEDI_EV_TX_FR_CORRUPT|CEDI_EV_RX_COMPLETE| CEDI_EV_RX_USED_READ|CEDI_EV_HRESP_NOT_OK)

#define	CEDI_EVSET_TX_RX_EVENTS (CEDI_EV_TX_COMPLETE|CEDI_EV_TX_USED_READ|CEDI_EV_TX_UNDERRUN| CEDI_EV_TX_RETRY_EX_LATE_COLL| CEDI_EV_TX_FR_CORRUPT|CEDI_EV_RX_COMPLETE| CEDI_EV_RX_USED_READ|CEDI_EV_RX_OVERRUN| CEDI_EV_HRESP_NOT_OK)


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Forward declarations
 **********************************************************************/
typedef struct CEDI_Config_s CEDI_Config;
typedef struct CEDI_Pcs25gCfg_s CEDI_Pcs25gCfg;
typedef struct CEDI_SysReq_s CEDI_SysReq;
typedef struct CEDI_AxiHostArbitrationCfg_s CEDI_AxiHostArbitrationCfg;
typedef struct CEDI_WatermarkLvl_s CEDI_WatermarkLvl;
typedef struct CEDI_AxiBuffCfg_s CEDI_AxiBuffCfg;
typedef struct CEDI_Pcs25gStatus_s CEDI_Pcs25gStatus;
typedef struct CEDI_TestPatternSeed_s CEDI_TestPatternSeed;
typedef struct CEDI_FecError_s CEDI_FecError;
typedef struct CEDI_TxStatus_s CEDI_TxStatus;
typedef struct CEDI_TxQStatus_s CEDI_TxQStatus;
typedef struct CEDI_RxStatus_s CEDI_RxStatus;
typedef struct CEDI_RxQStatus_s CEDI_RxQStatus;
typedef struct CEDI_BuffAddr_s CEDI_BuffAddr;
typedef struct CEDI_TimeStampData_s CEDI_TimeStampData;
typedef struct CEDI_TransmitLaunchTime_s CEDI_TransmitLaunchTime;
typedef struct CEDI_TxDescData_s CEDI_TxDescData;
typedef struct CEDI_TxDescStat_s CEDI_TxDescStat;
typedef struct CEDI_RxDescData_s CEDI_RxDescData;
typedef struct CEDI_RxDescStat_s CEDI_RxDescStat;
typedef struct CEDI_qTxBufParams_s CEDI_qTxBufParams;
typedef struct CEDI_FrameSize_s CEDI_FrameSize;
typedef struct CEDI_MacAddress_s CEDI_MacAddress;
typedef struct CEDI_Statistics_s CEDI_Statistics;
typedef struct CEDI_NumScreeners_s CEDI_NumScreeners;
typedef struct CEDI_T1Screen_s CEDI_T1Screen;
typedef struct CEDI_T2Screen_s CEDI_T2Screen;
typedef struct CEDI_T2Compare_s CEDI_T2Compare;
typedef struct CEDI_1588TimerVal_s CEDI_1588TimerVal;
typedef struct CEDI_TsuTimerVal_s CEDI_TsuTimerVal;
typedef struct CEDI_TimerIncrement_s CEDI_TimerIncrement;
typedef struct CEDI_AnAdvPage_s CEDI_AnAdvPage;
typedef struct CEDI_defLpAbility_s CEDI_defLpAbility;
typedef struct CEDI_sgmLpAbility_s CEDI_sgmLpAbility;
typedef struct CEDI_LpAbility_s CEDI_LpAbility;
typedef struct CEDI_LpAbilityPage_s CEDI_LpAbilityPage;
typedef struct CEDI_AnNextPage_s CEDI_AnNextPage;
typedef struct CEDI_LpNextPage_s CEDI_LpNextPage;
typedef struct CEDI_LpPage_s CEDI_LpPage;
typedef struct CEDI_LpPageRx_s CEDI_LpPageRx;
typedef struct CEDI_NetAnStatus_s CEDI_NetAnStatus;
typedef struct CEDI_WakeOnLanReg_s CEDI_WakeOnLanReg;
typedef struct CEDI_LpiStats_s CEDI_LpiStats;
typedef struct CEDI_EnstTimeConfig_s CEDI_EnstTimeConfig;
typedef struct CEDI_DesignCfg_s CEDI_DesignCfg;
typedef struct CEDI_Callbacks_s CEDI_Callbacks;
typedef struct CEDI_TxDesc_s CEDI_TxDesc;
typedef struct CEDI_TxQueue_s CEDI_TxQueue;
typedef struct CEDI_RxDesc_s CEDI_RxDesc;
typedef struct CEDI_RxQueue_s CEDI_RxQueue;
typedef struct CEDI_QueueSegAlloc_s CEDI_QueueSegAlloc;
typedef struct CEDI_FrameEliminationConfig_s CEDI_FrameEliminationConfig;
typedef struct CEDI_FrameEliminationTagConfig_s CEDI_FrameEliminationTagConfig;
typedef struct CEDI_FrameEliminationStats_s CEDI_FrameEliminationStats;
typedef struct CEDI_PreemptionConfig_s CEDI_PreemptionConfig;
typedef struct CEDI_MmslStats_s CEDI_MmslStats;
typedef struct CEDI_MmslStatus_s CEDI_MmslStatus;
typedef struct CEDI_LockupConfig_s CEDI_LockupConfig;
typedef struct CEDI_RxQFlushConfig_s CEDI_RxQFlushConfig;
typedef struct CEDI_Type2ScreenerRateLimit_s CEDI_Type2ScreenerRateLimit;
typedef struct CEDI_AxiQosConfig_s CEDI_AxiQosConfig;
typedef struct CEDI_AsfInfo_s CEDI_AsfInfo;

typedef struct CEDI_PrivateData_s CEDI_PrivateData;

/**********************************************************************
 * Enumerations
 **********************************************************************/
/** @defgroup DataStructure Dynamic Data Structures This section defines the data structures used by the driver to provide hardware information, modification, and dynamic operation of the driver. These data structures are defined in the header file of the core driver and utilized by the API. @{ */
typedef enum
{
    CEDI_DMA_BUS_WIDTH_32 = 0U,
    CEDI_DMA_BUS_WIDTH_64 = 1U,
    CEDI_DMA_BUS_WIDTH_128 = 2U
} CEDI_DmaBusWidth;

typedef enum
{
    CEDI_DMA_DBUR_LEN_1 = 1U,
    CEDI_DMA_DBUR_LEN_4 = 4U,
    CEDI_DMA_DBUR_LEN_8 = 8U,
    CEDI_DMA_DBUR_LEN_16 = 16U,
    CEDI_DMA_DBUR_LEN_256 = 0U
} CEDI_DmaDatBLen;

typedef enum
{
    CEDI_MDC_DIV_BY_8 = 0U,
    CEDI_MDC_DIV_BY_16 = 1U,
    CEDI_MDC_DIV_BY_32 = 2U,
    CEDI_MDC_DIV_BY_48 = 3U,
    CEDI_MDC_DIV_BY_64 = 4U,
    CEDI_MDC_DIV_BY_96 = 5U,
    CEDI_MDC_DIV_BY_128 = 6U,
    CEDI_MDC_DIV_BY_224 = 7U
} CEDI_MdcClkDiv;

typedef enum
{
    CEDI_MDIO_DEV_PMD_PMA = 1U,
    CEDI_MDIO_DEV_WIS = 2U,
    CEDI_MDIO_DEV_PCS = 3U,
    CEDI_MDIO_DEV_PHY_XS = 4U,
    CEDI_MDIO_DEV_DTE_XS = 5U
} CEDI_MdioDevType;

typedef enum
{
    CEDI_IFSP_MII = 0U,
    CEDI_IFSP_GMII = 1U,
    CEDI_IFSP_RGMII = 2U,
    CEDI_IFSP_SGMII = 3U,
    CEDI_IFSP_BASE_X = 4U,
    CEDI_IFSP_XGMII = 5U,
    CEDI_IFSP_USXGMII = 6U
} CEDI_Interface;

typedef enum
{
    CEDI_TX_TS_DISABLED = 0U,
    CEDI_TX_TS_PTP_EVENT_ONLY = 1U,
    CEDI_TX_TS_PTP_ALL = 2U,
    CEDI_TX_TS_ALL = 3U
} CEDI_TxTsMode;

typedef enum
{
    CEDI_RX_TS_DISABLED = 0U,
    CEDI_RX_TS_PTP_EVENT_ONLY = 1U,
    CEDI_RX_TS_PTP_ALL = 2U,
    CEDI_RX_TS_ALL = 3U
} CEDI_RxTsMode;

typedef enum
{
    CEDI_LINK_FAULT_INDICATION_OK = 0U,
    CEDI_LINK_FAULT_INDICATION_LOCAL_FAULT = 1U,
    CEDI_LINK_FAULT_INDICATION_REMOTE_FAULT = 2U,
    CEDI_LINK_FAULT_INDICATION_LINK_INTERRUPTION = 3U
} CEDI_LinkFaultIndication;

typedef enum
{
    CEDI_PRE_CRC_NO_COVER = 0U,
    CEDI_PRE_CRC_7MS_COVER = 1U,
    CEDI_PRE_CRC_ALL8_COVER = 2U,
    CEDI_PRE_CRC_4MS_COVER = 3U
} CEDI_PreCrcCover;

typedef enum
{
    CEDI_REDUNDANCY_TAG_SIZE_4 = 0U,
    CEDI_REDUNDANCY_TAG_SIZE_6 = 1U
} CEDI_RedundancyTagSize;

/** Describes max pipeline bits due to GEM version */
typedef enum
{
    /** GEM version greater/equal 1p13 */
    CEDI_AXI_MAX_PIPELINE_BITS_1P13 = 6U,
    /** GEM version lower/equal 1p12 */
    CEDI_AXI_MAX_PIPELINE_BITS_1P12 = 4U
} CEDI_AxiMaxPipelineBits;

/** AXI transaction channels */
typedef enum
{
    CEDI_AXI_CHANNEL_READ = 0U,
    CEDI_AXI_CHANNEL_WRITE = 1U
} CEDI_AxiChannelType;

/**
 * Priorities for AXI AW arbitration
 * TXDSC  - TxDescriptor
 * RXDSC  - RxDescriptor
 * RXDATA - RxData
*/
typedef enum
{
    CEDI_AW_ROUND_ROBIN = 0U,
    CEDI_AW_TXDSC_RXDSC_RXDATA = 1U,
    CEDI_AW_TXDSC_RXDATA_RXDSC = 2U,
    CEDI_AW_RXDSC_TXDSC_RXDATA = 3U,
    CEDI_AW_RXDSC_RXDATA_TXDSC = 4U,
    CEDI_AW_RXDATA_TXDSC_RXDSC = 5U,
    CEDI_AW_RXDATA_RXDSC_TXDSC = 6U
} CEDI_AxiWritePriority;

/**
 * Priorities for AXI AR arbitration
 * TXDSC  - TxDescriptor
 * RXDSC  - RxDescriptor
 * TXDATA - TxData
*/
typedef enum
{
    CEDI_AR_ROUND_ROBIN = 0U,
    CEDI_AR_RXDSC_TXDATA_TXDSC = 1U,
    CEDI_AR_RXDSC_TXDSC_TXDATA = 2U,
    CEDI_AR_TXDATA_RXDSC_TXDSC = 3U,
    CEDI_AR_TXDATA_TXDSC_RXDSC = 4U,
    CEDI_AR_TXDSC_RXDSC_TXDATA = 5U,
    CEDI_AR_TXDSC_TXDATA_RXDSC = 6U
} CEDI_AxiReadPriority;

/** Watermark levels for queues. */
typedef enum
{
    CEDI_WATERMARK_LEVEL_1 = 0U,
    CEDI_WATERMARK_LEVEL_2 = 1U,
    CEDI_WATERMARK_LEVEL_4 = 2U,
    CEDI_WATERMARK_LEVEL_8 = 3U,
    CEDI_WATERMARK_LEVEL_16 = 4U
} CEDI_WatermarkLevel;

/** Describes how symbols are repeated for USXGMII operation */
typedef enum
{
    /** rate is 5.15625 Gbps */
    CEDI_SERDES_RATE_5G = 0U,
    /** rate is 10.3125 Gpbs */
    CEDI_SERDES_RATE_10G = 1U,
    /** rate is 25.78125 Gpbs */
    CEDI_SERDES_RATE_25G = 2U
} CEDI_SerdesRate;

/**
 * Describes patterns for PCS25G test pattern mode.
 * CEDI_SQUARE_WAVE is available only for Tx
*/
typedef enum
{
    CEDI_NORMAL_OPERATION = 0U,
    CEDI_SCRAMBLED_LOCAL_FAULT = 1U,
    CEDI_SCRAMBLED_IDLE = 2U,
    CEDI_SCRAMBLED_ZERO = 3U,
    CEDI_PRBS_9 = 4U,
    CEDI_PRBS_31 = 5U,
    CEDI_SQUARE_WAVE = 6U
} CEDI_TestPatternMode;

/** Describes operation mode for PCS25G */
typedef enum
{
    CEDI_TEST_PATTERN_MODE = 0U,
    CEDI_MII_LOOPBACK_MODE = 1U,
    CEDI_SCRAMBLER_LOOPBACK_MODE = 2U
} CEDI_Pcs25gOperationMode;

/** Used to get/set seed value (A or B) */
typedef enum
{
    CEDI_TEST_SEED_A = 0U,
    CEDI_TEST_SEED_B = 1U
} CEDI_TestSeedReg;

/** Width of DMA address bus (as defined in dma_config register) */
typedef enum
{
    CEDI_DMA_ADDR_BUS_WIDTH_32 = 0U,
    CEDI_DMA_ADDR_BUS_WIDTH_64 = 1U
} CEDI_DmaAddrBusWidth;

/** Enum defining speed selection or indication */
typedef enum
{
    CEDI_SPEED_10M = 0U,
    CEDI_SPEED_100M = 1U,
    CEDI_SPEED_1000M = 2U,
    CEDI_SPEED_2500M = 3U,
    CEDI_SPEED_5G = 4U,
    CEDI_SPEED_10G = 5U,
    CEDI_SPEED_25G = 6U
} CEDI_IfSpeed;

/** Minimum Inter Packet Gap (IPG) in bytes */
typedef enum
{
    CEDI_MINIMUM_IPG_12 = 0U,
    CEDI_MINIMUM_IPG_24 = 1U,
    CEDI_MINIMUM_IPG_32 = 2U,
    CEDI_MINIMUM_IPG_CUSTOM = 3U
} CEDI_MinIpg;

/** Log base 2 of Burst Length for Tx and Rx use on AMBA (AHB/AXI) */
typedef enum
{
    CEDI_BURST_LEN_1 = 0U,
    CEDI_BURST_LEN_2 = 1U,
    CEDI_BURST_LEN_4 = 2U,
    CEDI_BURST_LEN_8 = 3U,
    CEDI_BURST_LEN_16 = 4U,
    CEDI_BURST_LEN_32 = 5U,
    CEDI_BURST_LEN_64 = 6U,
    CEDI_BURST_LEN_128 = 7U,
    CEDI_BURST_LEN_256 = 8U
} CEDI_BurstLen;

/** Enum defining Tx free descriptor call status */
typedef enum
{
    CEDI_TXDATA_1ST_NOT_LAST = 0U,
    CEDI_TXDATA_1ST_AND_LAST = 1U,
    CEDI_TXDATA_MID_BUFFER = 2U,
    CEDI_TXDATA_LAST_BUFFER = 3U,
    CEDI_TXDATA_NONE_FREED = 4U
} CEDI_TxFreeDStat;

/** Enum defining Rx data buffer read status */
typedef enum
{
    CEDI_RXDATA_SOF_EOF = 0U,
    CEDI_RXDATA_SOF_ONLY = 1U,
    CEDI_RXDATA_NO_FLAG = 2U,
    CEDI_RXDATA_EOF_ONLY = 3U,
    CEDI_RXDATA_NODATA = 4U
} CEDI_RxRdStat;

/** enum defining offset for screener type 2 compare values. Note the offset is applied after the specified point, e.g. T2COMP_OFF_ETYPE denotes the ethertype field, so an offset of 12 bytes from this would be the source IP address in an IP header. */
typedef enum
{
    CEDI_T2COMP_OFF_SOF = 0U,
    CEDI_T2COMP_OFF_ETYPE = 1U,
    CEDI_T2COMP_OFF_IPHDR = 2U,
    CEDI_T2COMP_OFF_TCPUDP = 3U,
    CEDI_T2COMP_OFF_VID_C_TAG = 4U,
    CEDI_T2COMP_OFF_VID_S_TAG = 5U
} CEDI_T2Offset;

/** enum defines number of segments of SRAM memory per TX queue */
typedef enum
{
    CEDI_SEGMENTS_PER_QUEUE_1 = 0U,
    CEDI_SEGMENTS_PER_QUEUE_2 = 1U,
    CEDI_SEGMENTS_PER_QUEUE_4 = 2U,
    CEDI_SEGMENTS_PER_QUEUE_8 = 3U,
    CEDI_SEGMENTS_PER_QUEUE_16 = 4U,
    CEDI_SEGMENTS_PER_QUEUE_32 = 5U,
    CEDI_SEGMENTS_PER_QUEUE_64 = 6U,
    CEDI_SEGMENTS_PER_QUEUE_128 = 7U
} CEDI_SegmentsPerQueue;

/** Type of scheduling algorithm of transmit queue */
typedef enum
{
    CEDI_TX_SCHED_TYPE_FIXED = 0U,
    CEDI_TX_SCHED_TYPE_CBS = 1U,
    CEDI_TX_SCHED_TYPE_DWRR = 2U,
    CEDI_TX_SCHED_TYPE_ETS = 3U
} CEDI_TxSchedType;

/** enum defining pause capability in auto-negotiation */
typedef enum
{
    CEDI_AN_PAUSE_CAP_NONE = 0U,
    CEDI_AN_PAUSE_CAP_SYM = 1U,
    CEDI_AN_PAUSE_CAP_ASYM = 2U,
    CEDI_AN_PAUSE_CAP_BOTH = 3U
} CEDI_PauseCap;

/** enum defining loopback mode selection */
typedef enum
{
    CEDI_NO_LOOPBACK = 0U,
    CEDI_LOCAL_LOOPBACK = 1U,
    CEDI_SERDES_LOOPBACK = 2U
} CEDI_LoopbackMode;

/** enum defining remote fault indication by link partner in auto-negotiation */
typedef enum
{
    CEDI_AN_REM_FLT_NONE = 0U,
    CEDI_AN_REM_FLT_LNK_FAIL = 1U,
    CEDI_AN_REM_FLT_OFFLINE = 2U,
    CEDI_AN_REM_FLT_AN_ERR = 3U
} CEDI_RemoteFault;

/** MAC object type. */
typedef enum
{
    /** express MAC */
    CEDI_MAC_TYPE_EMAC = 0U,
    /** preemptive MAC */
    CEDI_MAC_TYPE_PMAC = 1U,
    /** normal MAC(mac (when Express traffic is not supported or unwanted) */
    CEDI_MAC_TYPE_MAC = 2U
} CEDI_MacType;

/** defines what should be used to identify sequence number, redundancy tag or value at specific offset */
typedef enum
{
    CEDI_SEQ_NUM_IDEN_OFFSET = 0U,
    CEDI_SEQ_NUM_IDEN_TAG = 1U
} CEDI_SeqNumIdentification;

/** defines possible values of add frag size which is number of bytes which the pMAC has to send before the pre-emption will be allowed */
typedef enum
{
    /** 64 bytes */
    CEDI_FRAG_SIZE_64 = 0U,
    /** 128 bytes */
    CEDI_FRAG_SIZE_128 = 1U,
    /** 192 bytes */
    CEDI_FRAG_SIZE_192 = 2U,
    /** 256 bytes */
    CEDI_FRAG_SIZE_256 = 3U
} CEDI_FragSize;

/** defines possible values of return states of the respond state machine. */
typedef enum
{
    CEDI_R_IDLE = 0U,
    CEDI_SEND_RESPOND = 1U
} CEDI_RespondStatus;

/** defines possible values of return states of the verification state machine. */
typedef enum
{
    CEDI_INIT_VERIFICATION = 0U,
    CEDI_VERIFICATION_IDLE = 1U,
    CEDI_SEND_VERIFY = 2U,
    CEDI_WAIT_FOR_RESPONSE = 3U,
    CEDI_VERIFIED = 4U,
    CEDI_VERIFY_FAIL = 5U
} CEDI_VerifyStatus;

/** Defines possible modes of receive queue flushing. */
typedef enum
{
    /** Disables Rx flushing based on limits. */
    CEDI_FLUSH_MODE_OFF = 0U,
    /** Mode depending on received bytes. */
    CEDI_FLUSH_MODE_LIMIT_NUM_BYTES = 1U,
    /** Mode depending on received frames size. */
    CEDI_FLUSH_MODE_LIMIT_FRAME_SIZE = 2U
} CEDI_RxQFlushMode;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/**
 * Reports PHY Management frame tx complete.
 * Params: read = 1 if a read operation, = 0 if a write operation, and
 * readData - data from the PHY, if read operation.
*/
typedef void (*CEDI_CbPhyManComplete)(CEDI_PrivateData* pD, uint8_t read, uint16_t readData);

/**
 * Reports Tx completed / Tx used bit read events.
 * Params: event - indicates two types of event, which are OR'd together if both
 * occurred (CEDI_EV_TX_COMPLETE: frame has been transmitted successfully,
 * and CEDI_EV_TX_USED_READ: used bit set has been read in Tx descriptor list),
 * and queueNum- the priority queue number (only relevant to TX_COMPLETE)
 * range 0 to txQs-1.
*/
typedef void (*CEDI_CbTxEvent)(CEDI_PrivateData* pD, uint32_t event, uint8_t queueNum);

/**
 * Reports Tx errors.  Params: error - indicates one or more of three
 * possible events, OR'd together (CEDI_EV_TX_UNDERRUN: Tx underrun,
 * CEDI_EV_TX_RETRY_EX_LATE_COLL: retry limit exceeded or late collision,
 * CEDI_EV_TX_FR_CORRUPT: Tx frame corruption), and queueNum - the priority
 * queue number, range 0 to txQs-1 (not relevant to TX_UNDERRUN).
*/
typedef void (*CEDI_CbTxError)(CEDI_PrivateData* pD, uint32_t error, uint8_t queueNum);

/**
 * Reports Frame Rx completed successfully.  Param: queueNum - the priority
 * queue number, range 0 to rxQs-1.
*/
typedef void (*CEDI_CbRxFrame)(CEDI_PrivateData* pD, uint8_t queueNum);

/**
 * Reports Rx errors.  Params: error - one or more of two possible errors,
 * together (CEDI_EV_RX_USED_READ: used bit set has been read in Rx descriptor
 * list; CEDI_EV_RX_OVERRUN: Rx overrun error),
 * and queueNum - the priority queue number, range 0 to rxQs-1.
*/
typedef void (*CEDI_CbRxError)(CEDI_PrivateData* pD, uint32_t error, uint8_t queueNum);

/**
 * Reports Hresp not OK error.  Param: queueNum - number of the Tx or Rx
 * queue being accessed (range 0 to rxQs-1).
*/
typedef void (*CEDI_CbHrespError)(CEDI_PrivateData* pD, uint8_t queueNum);

/**
 * Reports PCS auto-negotiation page received. Param: pageRx - pointer to a
 * struct containing the link partner base or next page data.
*/
typedef void (*CEDI_CbLpPageRx)(CEDI_PrivateData* pD, CEDI_LpPageRx* pageRx);

/**
 * Reports PCS auto-negotiation completed. Param: netStat - pointer to a
 * struct with the network resolution status.
*/
typedef void (*CEDI_CbAnComplete)(CEDI_PrivateData* pD, CEDI_NetAnStatus* netStat);

/**
 * Reports Link Status Changed. Param: linkState - link status: if
 * auto-negotiation enabled, when =1 link is up, else link is down;
 * if auto-negotiation not enabled, this will indicate the synchronisation
 * status.  If link status has gone down, the value will not return to 1
 * until after it has been read, therefore to see current state must
 * re-read with a getLinkStatus call.
*/
typedef void (*CEDI_CbLinkChange)(CEDI_PrivateData* pD, uint8_t linkState);

/**
 * Reports Lockup Event occurred. Param: event - indicates one of two events,
 * OR'd together (CEDI_EV_RX_LOCKUP: RX lockup detected;
 * CEDI_EV_TX_LOCKUP: RX lockup detected).
*/
typedef void (*CEDI_CbLockupEvent)(CEDI_PrivateData* pD, uint32_t event);

/**
 * Reports TSU Event occurred. Param: event - indicates one of two events,
 * OR'd together (CEDI_EV_TSU_SEC_INC: TSU seconds register increment;
 * CEDI_EV_TSU_TIME_MATCH: TSU timer count match).
*/
typedef void (*CEDI_CbTsuEvent)(CEDI_PrivateData* pD, uint32_t event);

/**
 * Reports Pause Event occurred.  Param: event - indicates one or more of
 * three event types, OR'd together (CEDI_EV_PAUSE_FRAME_TX: Pause frame
 * transmitted; CEDI_EV_PAUSE_TIME_ZERO: Pause time zero;
 * CEDI_EV_PAUSE_NZ_QU_RX: Pause frame with non-zero quantum received).
*/
typedef void (*CEDI_CbPauseEvent)(CEDI_PrivateData* pD, uint32_t event);

/**
 * Reports PTP Primary Frame transmitted.  Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_TX_DLY_REQ:
 * delay_req; CEDI_EV_PTP_TX_SYNC: sync)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * transmitted.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPriFrameTx)(CEDI_PrivateData* pD, uint32_t type, CEDI_1588TimerVal* timeVal);

/**
 * Reports PTP Peer Frame transmitted. Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_TX_PDLY_REQ:
 * pdelay_req; CEDI_EV_PTP_TX_PDLY_RSP: pdelay_rsp)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * transmitted.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPeerFrameTx)(CEDI_PrivateData* pD, uint32_t type, CEDI_1588TimerVal* timeVal);

/**
 * Reports PTP Primary Frame received. Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_RX_DLY_REQ:
 * delay_req; CEDI_EV_PTP_RX_SYNC: sync)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * received.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPriFrameRx)(CEDI_PrivateData* pD, uint32_t type, CEDI_1588TimerVal* timeVal);

/**
 * Reports PTP Peer Frame received. Params: type - indicates
 * one of two frame types, OR together (CEDI_EV_PTP_RX_PDLY_REQ:
 * pdelay_req; CEDI_EV_PTP_RX_PDLY_RSP: pdelay_rsp)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * received.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPeerFrameRx)(CEDI_PrivateData* pD, uint32_t type, CEDI_1588TimerVal* timeVal);

/** Reports LPI Status changed. */
typedef void (*CEDI_CbLpiStatus)(CEDI_PrivateData* pD);

/** Reports Wake On LAN event received. */
typedef void (*CEDI_CbWolEvent)(CEDI_PrivateData* pD);

/** Reports External input interrupt occurred. */
typedef void (*CEDI_CbExtInpIntr)(CEDI_PrivateData* pD);

/** Callback function for MMSL-related interrupts. */
typedef void (*CEDI_CbMmslEvent)(CEDI_PrivateData* pD, uint32_t events);

/** Reports FEC error detected. */
typedef void (*CEDI_CbFecError)(CEDI_PrivateData* pD, uint32_t events, CEDI_FecError* fecErrors);

/** Reports Block Lock status change detected. */
typedef void (*CEDI_CbSyncEvent)(CEDI_PrivateData* pD, uint8_t blockLockedStatus);

/** Reports High bit error status triggered. */
typedef void (*CEDI_CbHighBitError)(CEDI_PrivateData* pD, uint32_t bitErrorCount);

/**
 *  @}
 */

/** @defgroup DriverFunctionAPI Driver Function API
 *  Prototypes for the driver API functions. The user application can link statically to the
 *  necessary API functions and call them directly.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/

/**
 * Get the driver's memory requirements to support the given
 * configuration. If config->txQs or config->rxQs specify more than
 * the number of queues available in the h/w configuration, they will
 * be reduced to match the latter value, and the memReq values will be
 * based on this.
 * @param[in] config driver/hardware configuration required
 * @param[out] memReq returns the size of memory allocations required
 * @return CDN_EOK on success (requirements struct filled)
 * @return CDN_EINVAL if config is NULL, or hardware not present
 * @return CDN_ENOTSUP if configuration cannot be supported due to driver/hardware constraints
 * $VALIDFAIL if (1) $RETURN $COMMENT Not in mechanical tests, covered by functional testing $
 */
uint32_t CEDI_Probe(CEDI_Config* config, CEDI_SysReq* memReq);

/**
 * Initialise the driver instance and state, configure the EMAC as
 * specified in the 'config' settings, set up Tx & Rx descriptor
 * lists.
 * @param[out] pD driver state info specific to this instance
 * @param[in,out] config specifies driver/hardware configuration
 * @param[in] callbacks client-supplied callback functions
 * @return CDN_EOK on success
 * @return CDN_EINVAL if illegal/inconsistent values in 'config'
 * @return CDN_EIO if driver encountered an error accessing hardware
 * @return CDN_ENOTSUP if hardware has an inconsistent configuration or doesn't support feature(s) required by 'config' parameters
 * $VALIDFAIL if (1) $RETURN $COMMENT Not in mechanical tests, covered by functional testing $
 */
uint32_t CEDI_Init(CEDI_PrivateData* pD, const CEDI_Config* config, const CEDI_Callbacks* callbacks);

/**
 * Destroy the driver (automatically performs a stop)
 * @param[in] pD driver state info specific to this instance
 */
void CEDI_Destroy(CEDI_PrivateData* pD);

/**
 * Start the EMAC driver, enabling interrupts and PCS auto-
 * negotiation.
 * @param[in] pD driver state info specific to this instance
 */
void CEDI_Start(CEDI_PrivateData* pD);

/**
 * Stop the driver. This should disable the hardware, including its
 * interrupt at the source, and make a best-effort to cancel any
 * pending transactions.
 * @param[in] pD driver state info specific to this instance
 */
void CEDI_Stop(CEDI_PrivateData* pD);

/**
 * Driver ISR.  Platform-specific code is responsible for ensuring
 * this gets called when the corresponding hardware's interrupt is
 * asserted. Registering the ISR should be done after calling init,
 * and before calling start. The driver's ISR will not attempt to lock
 * any locks, but will perform client callbacks. If the client wishes
 * to defer processing to non-interrupt time, it is responsible for
 * doing so.
 * @param[in] pD driver state info specific to this instance
 * @return CDN_EOK if any interrupt detected (and callback)
 * @return CDN_ECANCELED if no interrupt bit detected
 * @return CDN_EINVAL for invalid pD pointer
 * $VALIDFAIL if (1) $EXPECT_RETURN CDN_ECANCELED $
 */
uint32_t CEDI_Isr(CEDI_PrivateData* pD);

/**
 * Enable or disable the specified interrupts. mechanical test will
 * always fail as no callback pointers are given
 * @param[in] pD driver private state info specific to this instance
 * @param[in] events OR'd combination of bit-flags selecting the events to be enabled or disabled
 * @param[in] enable if =1 enable the events, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @param[in] queueNum between 0 and config->rxQs-1, or = CEDI_ALL_QUEUES
 *     - number of Tx or Rx priority queue,
 *    relevant to some of Tx and Rx events: CEDI_EV_TX_COMPLETE,
 *    CEDI_EV_TX_RETRY_EX_LATE_COLL, CEDI_EV_TX_FR_CORRUPT, CEDI_EV_RX_COMPLETE,
 *    CEDI_EV_RX_USED_READ, CEDI_EV_RX_OVERRUN, CEDI_EV_HRESP_NOT_OK.
 *    Must be = 0 or CEDI_ALL_QUEUES for other events.
 *    To dis/enable on all available Qs, set queueNum to CEDI_ALL_QUEUES
 *    and set events to CEDI_EVSET_ALL_Q0_EVENTS.
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)&&(queueNum<%P_ALL_QUEUES)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if (((queueNum==0)||(queueNum==%P_ALL_QUEUES)) && (events & ~%P_EVSET_ALL_Q0_EVENTS)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if (((queueNum>0)&&(queueNum<%P_Config.rxQs)) && (events & ~%P_EVSET_ALL_QN_EVENTS)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((enable==1)&&((queueNum<%P_Config.rxQs)||(queueNum==%P_ALL_QUEUES))&&(events!=0)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetEventEnable(CEDI_PrivateData* pD, uint32_t events, uint8_t enable, uint8_t queueNum);

/**
 * Read the enabled state of the specifed interrupts. OR the returned
 * event value with the CEDI_EV_ event bit-flags to determine if
 * event(s) are enabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum Tx or Rx priority queue to report events for
 * @param[out] event returned enabled events
 * @return CDN_EINVAL for invalid pointer or queueNum
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetEventEnable(CEDI_PrivateData* pD, uint8_t queueNum, uint32_t* event);

/**
 * Set the value of the Tx & Rx interrupt moderation register fields.
 * A non-zero value in either field introduces an interrupt stand-off
 * delay of the 8-bit value in units of 800ns before the corresponding
 * frame complete event causes an interrupt, limiting the interrupt
 * rate.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txIntDelay Interrupt delay to apply to Tx frame complete $RANGE $FROM 0 $TO 255 $
 * @param[in] rxIntDelay Interrupt delay to apply to Rx frame complete $RANGE $FROM 0 $TO 255 $
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetIntrptModerate(CEDI_PrivateData* pD, uint8_t txIntDelay, uint8_t rxIntDelay);

/**
 * Read the values of the interrupt moderation register fields
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txIntDelay Interrupt delay to apply to Tx frame complete
 * @param[out] rxIntDelay Interrupt delay to apply to Rx frame complete
 * @return CDN_EINVAL for invalid pointers
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetIntrptModerate(CEDI_PrivateData* pD, uint8_t* txIntDelay, uint8_t* rxIntDelay);

/**
 * Set the value of the Tx & Rx frame threshold interrupt moderation
 * register fields. A non-zero value in either field introduces an
 * interrupt stand-off delay until programmed number of frames is
 * transmitted/received.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txIntFrameThreshold Count of frames to transmit before assering interrupt. $RANGE $FROM 0 $TO 255 $
 * @param[in] rxIntFrameThreshold Count of frames to receive before assering interrupt. $RANGE $FROM 0 $TO 255 $
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetIntrptModerateThreshold(CEDI_PrivateData* pD, uint8_t txIntFrameThreshold, uint8_t rxIntFrameThreshold);

/**
 * Read the value of the Tx & Rx frame threshold interrupt moderation
 * register fields.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txIntFrameThreshold Count of frames to transmit before assering interrupt.
 * @param[out] rxIntFrameThreshold Count of frames to receive before assering interrupt.
 * @return CDN_EINVAL for invalid pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetIntrptModerateThreshold(CEDI_PrivateData* pD, uint8_t* txIntFrameThreshold, uint8_t* rxIntFrameThreshold);

/**
 * Select 10/100/1000/2500Mbps operation speed.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] speedSel a CEDI_IfSpeed enum indicating Tx/Rx speed
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 * $VALIDFAIL if (((%P_DesignCfg.moduleId == 0x00A) || (%P_DesignCfg.moduleId == 0x20A)) && (speedSel == %P_SPEED_2500M)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.ifTypeSel == %P_IFSP_XGMII) && (speedSel == %P_SPEED_10M)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if (!(%P_Config.ifTypeSel < %P_IFSP_XGMII) && (speedSel > %P_SPEED_2500M)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetIfSpeed(CEDI_PrivateData* pD, CEDI_IfSpeed speedSel);

/**
 * Read selected operation speed
 * @param[in] pD driver private state info specific to this instance
 * @param[out] speedSel returns CEDI_IfSpeed enum indicating Tx/Rx speed "
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_EIO if read wrong value from register
 */
uint32_t CEDI_GetIfSpeed(CEDI_PrivateData* pD, CEDI_IfSpeed* speedSel);

/**
 * Enable/disable reception of jumbo frames
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable jumbo frames accept, if =0 disable.  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetJumboFramesRx(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read jumbo frames enable status
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if jumbo frames accept enabled; equal 0 if disabled.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetJumboFramesRx(const CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set maximum length of jumbo frames to be received. (This is
 * initialised to gem_jumbo_max_length bytes.) Disables jumbo frame
 * reception temporarily while changing max length.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] length max. length to receive, in bytes.  Maximum is 16383 $RANGE $FROM 0 $TO 16383 $
 * @return CDN_EINVAL if length greater than 16383
 * @return CDN_EOK if successful
 */
uint32_t CEDI_SetJumboFrameRxMaxLen(CEDI_PrivateData* pD, uint16_t length);

/**
 * Read maximum length of jumbo frames to be received
 * @param[in] pD driver private state info specific to this instance
 * @param[out] length returns max. length to receive, in bytes
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetJumboFrameRxMaxLen(CEDI_PrivateData* pD, uint16_t* length);

/**
 * Enable/disable uni-direction transmit operation.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_EPERM if interface is CEDI_IFSP_USXGMII
 * $VALIDFAIL if(%P_Config.ifTypeSel == %P_IFSP_USXGMII) $EXPECT_RETURN CDN_EPERM $
 */
uint32_t CEDI_SetUniDirEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable status for uni-direction transmit operation
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetUniDirEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable Tx IP, TCP and UDP checksum generation offload. Only
 * valid if using DMA packet buffering mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if packet buffering not enabled or null pointer
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetTxChecksumOffload(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable of Tx IP, TCP and UDP checksum generation
 * offload
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetTxChecksumOffload(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set Rx buffer offset for writing start of frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] offset offset to use, range 0 to 3 bytes  $RANGE $FROM 0 $TO 3 $
 * @return CDN_EINVAL if offset invalid or null pointer
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetRxBufOffset(CEDI_PrivateData* pD, uint8_t offset);

/**
 * Read Rx buffer offset for writing start of frame
 * @param[in] pD driver private state info specific to this instance
 * @param[out] offset offset in use, range 0 to 3 bytes
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRxBufOffset(CEDI_PrivateData* pD, uint8_t* offset);

/**
 * "Set the DMA receive buffer size in external AMBA (AHB/AXI) system
 * memory for the given queue"
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Rx queue
 * @param[in] bufferSizeMultiple64Bytes The size of buffer (in multiples of 64 bytes) to use in main system memory
 *    when writing received data.
 *    Possible values are 1 to 255 which gives 64 to 16320 bytes. $RANGE $FROM 1 $TO 255 $
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetRxQBufferSize(const CEDI_PrivateData* pD, uint8_t queueNum, uint8_t bufferSizeMultiple64Bytes);

/**
 * "Get the DMA receive buffer size in external AMBA (AHB/AXI) system
 * memory of the given queue"
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Rx queue
 * @param[out] bufferSizeMultiple64Bytes The size of buffer (in multiples of 64 bytes) to use in main system memory
 *    when writing received data.
 *    Possible values are 1 to 255 which gives 64 to 16320 bytes.
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxQBufferSize(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t bufferSizeMultiple64Bytes);

/**
 * Select the per queue max Rx burst length to use on the AMBA
 * (AHB/AXI) when writing frame data to external memory.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Rx queue
 * @param[in] burstLength burst length to use for given queue
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetRxQBurstLength(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BurstLen burstLength);

/**
 * Read max Rx burst length per queue to use on the AMBA (AHB/AXI)
 * when writing frame data to external memory.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Rx queue
 * @param[out] burstLenth burst length to use for given queue
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_GetRxQBurstLength(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BurstLen burstLenth);

/**
 * Select the per queue max Tx burst length to use on the AMBA
 * (AHB/AXI) when reading frame data from external memory.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @param[in] burstLength burst length to use for given queue
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetTxQBurstLength(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BurstLen burstLength);

/**
 * Read max Tx burst length per queue to use on the AMBA (AHB/AXI)
 * when reading data from external memory.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @param[out] burstLenth burst length to use for given queue
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_GetTxQBurstLength(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BurstLen burstLenth);

/**
 * Enable/disable reception of frames up to 1536 bytes, instead of
 * normal 1518 bytes limit
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable 1536-byte frames accept, if =0 disable $RANGE $FROM 0 $TO 1 $
 */
void CEDI_Set1536ByteFramesRx(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read 1536-byte frames Rx enable status
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if 1536-byte frames accept enabled equal 0 if disabled.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_Get1536ByteFramesRx(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable Rx IP, TCP and UDP checksum offload. When enabled,
 * frames with bad IP, TCP or UDP checksums will be discarded.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetRxChecksumOffload(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable of Rx IP, TCP and UDP checksum offload
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRxChecksumOffload(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable FCS remove feature. When enabled, received frames
 * will be written without frame check sequence (last four bytes).
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetFcsRemove(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable status for FCS remove feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetFcsRemove(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable partial store and forward Tx mode if possible
 * @param[in] pD driver private state info specific to this instance
 * @param[in] watermark value to control data forwarding - ignored if enable==0  $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[in] enable if =1 then enables partial store and forward Tx mode, if =0 then disables $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 * @return CDN_ENOTSUP if not in tx packet buffer mode
 * $VALIDFAIL if (%P_DesignCfg.tx_pkt_buffer==0) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetTxPartialStFwd(CEDI_PrivateData* pD, uint32_t watermark, uint8_t enable);

/**
 * Get watermark value for partial store and forward Tx mode
 * @param[in] pD driver private state info specific to this instance
 * @param[out] watermark returns value to control data forwarding if partial store and forward Tx mode enabled
 * @param[out] enable =1 if partial store and forward Tx mode enabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_ENOTSUP if not in tx packet buffer mode
 * $VALIDFAIL if (%P_DesignCfg.tx_pkt_buffer==0) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetTxPartialStFwd(CEDI_PrivateData* pD, uint32_t* watermark, uint8_t* enable);

/**
 * Enable/disable partial store and forward Rx mode if possible
 * @param[in] pD driver private state info specific to this instance
 * @param[in] watermark value to control data forwarding $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[in] enable if =1 then enables partial store and forward Rx mode, if =0 then disables $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_ENOTSUP if not in rx packet buffer mode
 * $VALIDFAIL if (%P_DesignCfg.rx_pkt_buffer==0) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetRxPartialStFwd(CEDI_PrivateData* pD, uint32_t watermark, uint8_t enable);

/**
 * Get watermark value for partial store and forward Rx mode
 * @param[in] pD driver private state info specific to this instance
 * @param[out] watermark pointer for returning watermark value set (undefined if partial store & forward not enabled)
 * @param[out] enable =1 if partial store and forward Rx mode enabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_ENOTSUP if not in rx packet buffer mode
 * $VALIDFAIL if (%P_DesignCfg.rx_pkt_buffer==0) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetRxPartialStFwd(CEDI_PrivateData* pD, uint32_t* watermark, uint8_t* enable);

/**
 * Set the fields of the Rx DMA Data Buffer Address Mask register,
 * which allows any/all of bits 31:28 of rx data buffer address to be
 * forced to a particular value
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enableBit 4-bit field selecting bits to force value on  $RANGE $FROM 0 $TO 0xf $
 * @param[in] bitValues 4-bit field specifying values to force address bits 31:28 to, if corresponding bit in enableBit is set to 1  $RANGE $FROM 0 $TO 0xf $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter value invalid
 */
uint32_t CEDI_SetRxDmaDataAddrMask(CEDI_PrivateData* pD, uint8_t enableBit, uint8_t bitValues);

/**
 * Read the fields of the Rx DMA Data Buffer Address Mask register,
 * which allows any/all of bits 31:28 of rx data buffer address to be
 * forced to a particular value
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enableBit pointer for returning 4-bit field selecting bits to force value on
 * @param[out] bitValues pointer for returning 4-bit field specifying values to force address bits to, if corresponding bit in enableBit is set to 1
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if any parameter equal NULL
 */
uint32_t CEDI_GetRxDmaDataAddrMask(CEDI_PrivateData* pD, uint8_t* enableBit, uint8_t* bitValues);

/**
 * Enable/disable receive bad preamble feature. When enabled, frames
 * with non-standard preamble will not be rejected.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetRxBadPreamble(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable status for receive bad preamble feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRxBadPreamble(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Select full/half duplex operation.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 select full duplex operation if =0 select half duplex.  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_SetFullDuplex(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read full/half duplex operation
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if full duplex operation enabled equal 0 if half duplex.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetFullDuplex(const CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable ignore FCS feature. When enabled, frames with
 * FCS/CRC errors will not be rejected.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetIgnoreFcsRx(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable status for FCS ignore feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetIgnoreFcsRx(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable frame Rx in half-duplex mode while transmitting.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetRxHalfDuplexInTx(const CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable status for frame Rx in half-duplex mode while
 * transmitting
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRxHalfDuplexInTx(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set coverage of preamble by CRC, for Tx & Rx
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txCrcPreCover preamble Crc coverage for Tx
 * @param[in] rxCrcPreCover preamble Crc coverage for Rx
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetPreambleCrcCover(CEDI_PrivateData* pD, CEDI_PreCrcCover txCrcPreCover, CEDI_PreCrcCover rxCrcPreCover);

/**
 * Read settings for coverage of preamble by CRC, for Tx & Rx
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txCrcPreCover preamble Crc coverage for Tx
 * @param[in] rxCrcPreCover preamble Crc coverage for Rx
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_GetPreambleCrcCover(CEDI_PrivateData* pD, CEDI_PreCrcCover* txCrcPreCover, CEDI_PreCrcCover* rxCrcPreCover);

/**
 * Return capabilities supported by the driver/EMAC hardware
 * @param[in] pD driver private state info specific to this instance
 * @param[out] cap pointer for returning supported capabilities, OR combination of CEDI_CAP_XXX flags $RANGE $FROM 0 $OR_MASK CEDI_CAP_* $
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetIfCapabilities(const CEDI_PrivateData* pD, uint32_t* cap);

/**
 * Enable or disable loop back mode in the EMAC.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] mode enum selecting mode enable/disable. =CEDI_SERDES_LOOPBACK: select loopback mode in PHY transceiver, if available; =CEDI_LOCAL_LOOPBACK: select internal loopback mode. Tx and Rx should be disabled when enabling or disabling this mode. Only available if int_loopback defined; =CEDI_NO_LOOPBACK: disable loopback mode $RANGE $ENUM CEDI_LoopbackMode $
 * @return CDN_ENOTSUP if CEDI_SERDES_LOOPBACK selected and no_pcs defined, or if CEDI_LOCAL_LOOPBACK selected and either (no_int_loopback defined or PCS mode is selected)
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetLoopback(CEDI_PrivateData* pD, uint8_t mode);

/**
 * Return loopback mode, same values as for setLoopbackMode.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mode returns enum for mode enable/disable. =CEDI_SERDES_LOOPBACK: selected loopback mode in PHY transceiver, if available; =CEDI_LOCAL_LOOPBACK: selected internal loopback mode. Only available if int_loopback defined; =CEDI_NO_LOOPBACK: disabled loopback mode
 */
uint32_t CEDI_GetLoopback(CEDI_PrivateData* pD, uint8_t* mode);

/**
 * Identify max Tx pkt size for queues. When using full store &
 * forward packet buffering, this is based on the sram size for each
 * queue, otherwise it is limited by an internal counter to 16kB.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] maxTxSize pointer for returning array of sizes for queues
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if any parameter equal NULL
 */
uint32_t CEDI_CalcMaxTxFrameSize(CEDI_PrivateData* pD, CEDI_FrameSize* maxTxSize);

/**
 * Add a buffer containing Tx data to the end of the transmit queue.
 * Use repeated calls for multi-buffer frames, setting lastBuffer on
 * the last call, to indicate the end of the frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @param[in] bufAdd pointer to address of buffer
 * @param[in] length length of data in buffer $RANGE $FROM 1 $TO CEDI_TXD_LMASK $
 * @param[in] flags bit-flags (CEDI_TXB_xx) specifying last buffer/auto CRC
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid queueNum, length or buffer alignment, NULL pointers or buffer address
 * @return CDN_ENOENT if no available descriptors
 * $VALIDFAIL if (1) $RETURN $COMMENT Return depends on dynamic variable nFree $
 */
uint32_t CEDI_QueueTxBuf(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BuffAddr* bufAdd, uint32_t length, uint8_t flags);

/**
 * Add a buffer containing Tx data to the end of the transmit queue.
 * Use repeated calls for multi-buffer frames, setting
 * CEDI_TXB_LAST_BUFF in the flags on the last call, to indicate the
 * end of the frame. This function is required for utilising TSO/UFO.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] params pointer to struct for all parameters required by the function
 * @return CDN_EOK if successful
 * @return CDN_ENOENT if no available descriptors
 * @return CDN_ENOTSUP if CEDI_TXB_ENABLE_TLT is selected and Time Base Scheduling is not supported
 * @return CDN_EINVAL if invalid queueNum, length or buffer alignment, NULL pointers or buffer address or prm->flags specifies CEDI_TXB_LAST_BUFF at same time as CEDI_TXB_TCP_ENCAP or CEDI_TXB_UDP_ENCAP
 * $VALIDFAIL if (1) $RETURN $COMMENT Return depends on dynamic variable nFree $
 */
uint32_t CEDI_QTxBuf(CEDI_PrivateData* pD, CEDI_qTxBufParams* params);

/**
 * Remove buffer from head of transmit queue in case of error during
 * queueing and free the corresponding descriptor.  Caller must have
 * knowledge of queueing status, i.e. latest frame has not been
 * completed for transmission (first used bit still set) and how many
 * descriptors have been queued for untransmitted frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[in,out] params pointer to struct for parameters to be returned. Not all fields are used - queueNum must be specified, and bufAdd and length are returned
 * @return CDN_EOK if successful
 * @return CDN_ENOENT if no unfree descriptors
 * @return CDN_EINVAL if invalid queueNum or NULL parameters
 * $VALIDFAIL if (1) $RETURN $COMMENT Return depends on state of descriptor queue $
 */
uint32_t CEDI_DeQTxBuf(CEDI_PrivateData* pD, CEDI_qTxBufParams* params);

/**
 * Get number of free descriptors in specified Tx queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @param[out] numFree pointer for returning number of free descriptors
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_TxDescFree(const CEDI_PrivateData* pD, uint8_t queueNum, uint16_t* numFree);

/**
 * Read Tx descriptor queue and free used descriptor.\n Struct
 * fields:\n CEDI_BuffAddr bufAdd - addresses of buffer freed up
 * uint32_t txDescStat - descriptor status word. Only valid if first
 * buffer of frame. uint8_t status  - descriptor queue status, one of
 * the following values: CEDI_TXDATA_1ST_NOT_LAST :a first descriptor
 * was freed,                         frame not finished:
 * bufAdd & txDescStat are valid CEDI_TXDATA_1ST_AND_LAST :a first
 * descriptor was freed,                         frame is finished:
 * bufAdd & txDescStat are valid CEDI_TXDATA_MID_BUFFER   :a
 * descriptor was freed,                         (not first in frame),
 * frame not finished: bufAdd valid,
 * txDescStat not valid CEDI_TXDATA_LAST_BUFFER  :a descriptor was
 * freed, frame is finished:                         bufAdd valid,
 * txDescStat not valid CEDI_TXDATA_NONE_FREED   :no used descriptor
 * to free:                         bufAdd & txDescStat not valid
 * CEDI_TimeStampData txTsData - Tx descriptor timestamp when valid
 * (txTsData->tsValid will be set to 1).
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @param[out] descData pointer for returning status & descriptor data
 * @return CDN_ENOENT if the queue is empty (status equal CEDI_TXDATA_NONE_FREED)
 * @return CDN_EIO if an incomplete frame was detected (no lastBuffer flag in queue)
 * @return CDN_EINVAL if any parameter invalid
 * @return CDN_EOK if successful (and status is set)
 * $VALIDFAIL if (queueNum<%P_Config.txQs) $EXPECT_RETURN CDN_ENOENT $
 */
uint32_t CEDI_FreeTxDesc(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_TxDescData* descData);

/**
 * Decode the Tx descriptor status into a bit-field struct
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txDStatWord - Tx descriptor status word
 * @param[out] txDStat - pointer to bit-field struct for decoded status fields
 */
void CEDI_GetTxDescStat(const CEDI_PrivateData* pD, uint32_t txDStatWord, CEDI_TxDescStat* txDStat);

/**
 * Provides the size of Tx descriptor calculated for current
 * configuration.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txDescSize - pointer to Tx descriptor size
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_GetTxDescSize(const CEDI_PrivateData* pD, uint32_t* txDescSize);

/**
 * Provides the size of Tx descriptor calculated for current
 * configuration for given queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Tx queue
 * @param[out] txDescSize pointer to Tx descriptor size
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetTxQDescSize(const CEDI_PrivateData* pD, uint8_t queueNum, uint32_t* txDescSize);

/**
 * Reset transmit buffer queue. Any untransmitted buffer data will be
 * discarded and must be re-queued.  Transmission must be disabled
 * before calling this function.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_ResetTxQ(CEDI_PrivateData* pD, uint8_t queueNum);

/**
 * Enable & start the transmit circuit. Not required during normal
 * operation, as queueTxBuf will automatically start Tx when complete
 * frame has been queued, but may be used to restart after a Tx error.
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_ECANCELED if no entries in buffer
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $EXPECT_RETURN CDN_ECANCELED $
 */
uint32_t CEDI_StartTx(CEDI_PrivateData* pD);

/**
 * Enable & start the transmit circuit for given queue. Not required
 * during normal operation, as queueTxBuf will automatically start Tx
 * when complete frame has been queued, but may be used to restart
 * after a Tx error. For configurations with per-queue transmission
 * start support.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if per-queue transmission starting is not supported
 * @return CDN_ECANCELED if no entries in buffer
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $EXPECT_RETURN CDN_ECANCELED $
 */
uint32_t CEDI_StartQTx(CEDI_PrivateData* pD, uint8_t queueNum);

/**
 * Halt transmission as soon as current frame Tx has finished
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_StopTx(CEDI_PrivateData* pD);

/**
 * Halt transmission for the given queue as soon as current frame Tx
 * has finished. For configurations with per-queue transmission halt
 * support.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Tx queue
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if per-queue transmission halting is not supported
 * @return CDN_EOK for success
 */
uint32_t CEDI_StopQTx(CEDI_PrivateData* pD, uint8_t queueNum);

/**
 * Immediately disable transmission without waiting for completion.
 * Since the EMAC will reset to point to the start of transmit
 * descriptor list, the buffer queues may have to be reset after this
 * call.
 * @param[in] pD driver private state info specific to this instance
 */
void CEDI_AbortTx(CEDI_PrivateData* pD);

/**
 * Get state of transmitter
 * @param[in] pD driver private state info specific to this instance
 * @return 1 if active
 * @return 0 if idle or pD equal NULL
 */
uint32_t CEDI_Transmitting(CEDI_PrivateData* pD);

/**
 * Enable the transmit circuit.  This will be done automatically when
 * call startTx, but it may be desirable to call this earlier, since
 * some functionality depends on transmit being enabled.
 * @param[in] pD driver private state info specific to this instance
 */
void CEDI_EnableTx(CEDI_PrivateData* pD);

/**
 * Get state of transmision enabled
 * @param[in] pD driver private state info specific to this instance
 * @return 1 if transmission enabled
 * @return 0 if transmission disabled or pD equal NULL
 */
uint32_t CEDI_GetTxEnabled(CEDI_PrivateData* pD);

/**
 * Get the content of EMAC transmit status register
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txStatus pointer to struct with fields for each flag
 * @return number raw Tx status value read
 * @return 0 if no status bits set or status equal NULL
 */
uint32_t CEDI_GetTxStatus(CEDI_PrivateData* pD, CEDI_TxStatus* txStatus);

/**
 * Get the Tx-related content of q_status register for the given queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Tx queue
 * @param[out] txQstatus pointer to struct with fields for each flag
 * @return CDN_EOK if successful
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if gem version not 1p13 or virtualization not enabled
 */
uint32_t CEDI_GetQTxStatus(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_TxQStatus* txQstatus);

/**
 * Reset the bits of EMAC transmit status register as selected in
 * resetStatus
 * @param[in] pD driver private state info specific to this instance
 * @param[in] resetStatus OR'd combination of CEDI_TXS_ bit-flags  $RANGE $FROM 0 $OR_MASK CEDI_TXS_* $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_ClearTxStatus(const CEDI_PrivateData* pD, uint32_t resetStatus);

/**
 * Reset the Tx-related bits of the q_status register as selected in
 * resetStatus for the given queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Tx queue
 * @param[in] resetStatus OR'd combination of CEDI_TXSQ_ bit-flags  $RANGE $FROM 0 $OR_MASK CEDI_TXSQ_* $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if gem version not 1p13 or virtualization not enabled
 */
uint32_t CEDI_ClearQTxStatus(CEDI_PrivateData* pD, uint8_t queueNum, uint32_t resetStatus);

/**
 * Enable credit-based shaping (CBS) on the specified queue.  If
 * already enabled then first disables, sets a new idle slope value
 * for the queue, and re-enables CBS
 * @param[in] pD driver private state info specific to this instance
 * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selects next-highest priority queue (queue B)  $RANGE $FROM 0 $TO 1 $
 * @param[in] idleSlope new idle slope value (in bytes/sec)
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if priority queueing not enabled (i.e. only one Tx queue) or invalid parameter
 * @return CDN_ENOTSUP if CBS not present in h/w config
 * $VALIDFAIL if (%P_Config.txQs==1) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_EnableCbs(CEDI_PrivateData* pD, uint8_t qSel, uint32_t idleSlope);

/**
 * Disable CBS on the specified queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selectsnext-highest priority queue (queue B)  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_DisableCbs(CEDI_PrivateData* pD, uint8_t qSel);

/**
 * Read CBS setting for the specified queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selects next-highest priority queue (queue B)  $RANGE $FROM 0 $TO 1 $
 * @param[out] enable returns: 1 if CBS enabled for the specified queue 0 if not enabled
 * @param[out] idleSlope pointer for returning the idleSlope value for selected queue.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if CBS not present in h/w config
 */
uint32_t CEDI_GetCbsQSetting(CEDI_PrivateData* pD, uint8_t qSel, uint8_t* enable, uint32_t* idleSlope);

/**
 * Enable/disable the inter-packet gap (IPG) stretch function.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable IPG stretch, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @param[in] multiplier multiplying factor applied to previous Tx frame length.  Ignored if enable equal 0. $RANGE $FROM 0 $TO 255 $TEST_SUBSET 8 $
 * @param[in] divisor after multiplying previous frame length, divide by (divisor+1) - if result>96 bits,
 *    this is used for the Tx IPG. Ignored if enable equal 0. $RANGE $FROM 0 $TO 255 $TEST_SUBSET 8 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK if successful
 */
uint32_t CEDI_SetIpgStretch(CEDI_PrivateData* pD, uint8_t enable, uint8_t multiplier, uint8_t divisor);

/**
 * Read the inter-packet gap (IPG) stretch settings.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning enabled state: returns 1 if IPG stretch enabled, 0 if disabled.
 * @param[out] multiplier pointer for returning IPG multiplying factor
 * @param[out] divisor pointer for returning IPG divisor
 * @return CDN_EINVAL if any parameter equal NULL
 * @return CDN_EOK if successful
 */
uint32_t CEDI_GetIpgStretch(CEDI_PrivateData* pD, uint8_t* enable, uint8_t* multiplier, uint8_t* divisor);

/**
 * Set minimum inter-packet gap (IPG) function.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] minIpg Minimum Inter Packet Gap
 * @param[in] MinIpgInBytes Minimum Inter Packet Gap for custom selection
 * @return CDN_EINVAL if any parameter equal NULL
 * @return CDN_ENOTSUP if set minimum IPG is not supported
 * @return CDN_EOK if successful
 */
uint32_t CEDI_SetMinIpg(CEDI_PrivateData* pD, CEDI_MinIpg minIpg, uint8_t MinIpgInBytes);

/**
 * En/disable the tx defer capability.  This can be used to pause tx
 * when a link interruption ordered set is received (as indicated by
 * the link fault status change interrupt and link interruption in the
 * interrupt status and network status registers respectively).
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable Set to enable tx defer.
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if pD equal NULL or enable invalid
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetTxDefer(CEDI_PrivateData* pD, bool enable);

/**
 * Get state of transmision defer
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable Returns true if txDefer is enabled
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if NULL parameters
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_GetTxDefer(CEDI_PrivateData* pD, bool* enable);

/**
 * Identify max Rx pkt size for queues - determined by size of Rx
 * packet buffer (if using full store & forward mode), and the current
 * maximum frame size, e.g. 1518, 1536 or jumbo frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] maxSize pointer for returning max frame size same for each Rx queue
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if NULL parameters
 */
uint32_t CEDI_CalcMaxRxFrameSize(CEDI_PrivateData* pD, uint32_t* maxSize);

/**
 * Add a buffer (size determined by rxBufLength in CEDI_Config) to the
 * end of the receive buffer queue.  This function is intended to be
 * used during setting up the receive buffers, and should not be
 * called while Rx is enabled or unread data remains in the queue.
 * Note that one extra descriptor is reserved, to provide wrap-around
 * protection (must always have one used bit set).
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[in] buf pointer to address of buffer. Checked for word-alignment in 64/128-bit width cases.
 * @param[in] init if >0 then initialise the buffer data to all zeros  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid queueNum, buffer alignment, or bufStart pointer/addresses
 * $VALIDFAIL if (1) $RETURN $COMMENT Not supported $
 */
uint32_t CEDI_AddRxBuf(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BuffAddr* buf, uint8_t init);

/**
 * Get the total number of buffers/descriptors present in the
 * specified Rx queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[out] numBufs pointer for returning number of descriptors
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_NumRxBufs(const CEDI_PrivateData* pD, uint8_t queueNum, uint16_t* numBufs);

/**
 * Get the number of buffers/descriptors marked "used" in the
 * specified Rx    queue, i.e. those holding unread data.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @return number of used buffers
 * @return 0 if invalid parameter or NULL pointer
 */
uint32_t CEDI_NumRxUsed(CEDI_PrivateData* pD, uint8_t queueNum);

/**
 * Read first unread descriptor (at tail of queue): if new data is
 * available it swaps out the buffer and replaces it with a new one,
 * clears the descriptor for re-use, then updates the driver queue-
 * pointer. Checks for Start Of Frame (SOF) and End Of Frame (EOF)
 * flags in the descriptors, passing back in status parameter. If EOF
 * set, the descriptor status is returned via rxDescStat.   Struct
 * fields:    uint32_t rxDescStat  - Rx descriptor status word
 * uint8_t status    - Rx data status, one of the following values:
 * CEDI_RXDATA_SOF_EOF  :data available, single-buffer frame (SOF &
 * EOF                            set)      CEDI_RXDATA_SOF_ONLY :data
 * available, start of multi-buffer frame      CEDI_RXDATA_NO_FLAG
 * :data available, intermediate buffer of multi-
 * buffer frame      CEDI_RXDATA_EOF_ONLY :data available, end of
 * multi-buffer frame      CEDI_RXDATA_NODATA   :no data available
 * CEDI_TimeStampData rxTsData - Rx descriptor timestamp when valid
 * (rxTsData->tsValid will be set to 1)
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[in,out] buf pointer to address of memory for new buffer to add to Rx descriptor queue; if data is available the buffer addresses for this are returned in buf, else if no data available then the new buffer can be re-used. Physical address of buffer is checked for word-alignment in 64/128-bit width cases.
 * @param[in] init if >0 then initialise the (new) buffer data to all zeros. Ignored if no data available. $RANGE $FROM 0 $TO 1 $
 * @param[out] descData pointer for returning status & descriptor data
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid queueNum, buf, rxDescStat or status parameters
 * $VALIDFAIL if (1) $RETURN $COMMENT Not supported, covered by functional testing $
 */
uint32_t CEDI_ReadRxBuf(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BuffAddr* buf, uint8_t init, CEDI_RxDescData* descData);

/**
 * Decode the Rx descriptor status into a bit-field struct.  Note that
 * most of these fields are only valid when End Of Frame bit15 is set
 * - see hardware user guide
 * @param[in] pD driver private state info specific to this instance
 * @param[in] rxDStatWord - Rx descriptor status word
 * @param[out] rxDStat pointer to bit-field struct for decoded status fields
 */
void CEDI_GetRxDescStat(CEDI_PrivateData* pD, uint32_t rxDStatWord, CEDI_RxDescStat* rxDStat);

/**
 * Provides the size of Rx descriptor calculated for current
 * configuration.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] rxDescSize - pointer to Rx descriptor size
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_GetRxDescSize(const CEDI_PrivateData* pD, uint32_t* rxDescSize);

/**
 * Provides the size of Rx descriptor calculated for current
 * configuration for given queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[out] rxDescSize pointer to Rx descriptor size
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxQDescSize(const CEDI_PrivateData* pD, uint8_t queueNum, uint32_t* rxDescSize);

/**
 * Get state of receiver
 * @param[in] pD driver private state info specific to this instance
 * @return 1 if enabled
 * @return 0 if disabled or pD equal NULL
 */
uint32_t CEDI_RxEnabled(CEDI_PrivateData* pD);

/**
 * Enable the receive circuit.
 * @param[in] pD driver private state info specific to this instance
 */
void CEDI_EnableRx(CEDI_PrivateData* pD);

/**
 * Disable the receive circuit.
 * @param[in] pD driver private state info specific to this instance
 */
void CEDI_DisableRx(CEDI_PrivateData* pD);

/**
 * Remove a buffer from the end of the receive buffer queue.  This
 * function is intended to be used when shutting down the driver,
 * prior to deallocating the receive buffers, and should not be called
 * while Rx is enabled or unread data remains in the queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[out] buf pointer to struct for returning virtual and physical addresses of buffer.
 * @return CDN_EINVAL if invalid queueNum
 * @return CDN_ENOENT if no buffers left to free (mechanical success)
 * @return CDN_EOK if successful
 * $VALIDFAIL if (1) $RETURN $COMMENT Not supported $
 */
uint32_t CEDI_RemoveRxBuf(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_BuffAddr* buf);

/**
 * Reset Rx buffer descriptor list to initial empty state (if
 * ptrsOnly=0), clearing all descriptors.  For use after a fatal
 * error.  Disables receive circuit.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[in] ptrsOnly "flag to allow full queue to be reset after link down/up (enableRx).
 *    if =1 then only reset tail & stop pointers and clear used bits" $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_ResetRxQ(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t ptrsOnly);

/**
 * Return the content of EMAC receive status register
 * @param[in] pD driver private state info specific to this instance
 * @param[out] status pointer to struct with fields for each flag
 * @return 1 if any flags set
 * @return 0 if not or status equal NULL
 */
uint32_t CEDI_GetRxStatus(CEDI_PrivateData* pD, CEDI_RxStatus* status);

/**
 * Get the Rx-related content of q_status register for the given queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[out] rxQstatus pointer to struct with fields for each flag
 * @return CDN_EOK if successful
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if gem version not 1p13 or virtualization not enabled
 */
uint32_t CEDI_GetQRxStatus(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_RxQStatus* rxQstatus);

/**
 * Reset the bits of EMAC receive status register as selected in
 * resetStatus
 * @param[in] pD driver private state info specific to this instance
 * @param[in] resetStatus OR'd combination of CEDI_RXS_ bit-flags  $RANGE $FROM 0 $OR_MASK CEDI_RXS_* $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_ClearRxStatus(const CEDI_PrivateData* pD, uint32_t resetStatus);

/**
 * Reset the Rx-related bits of the q_status register as selected in
 * resetStatus for the given queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of the Rx queue
 * @param[in] resetStatus OR'd combination of CEDI_RXSQ_ bit-flags  $RANGE $FROM 0 $OR_MASK CEDI_RXSQ_* $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if gem version not 1p13 or virtualization not enabled
 */
uint32_t CEDI_ClearQRxStatus(CEDI_PrivateData* pD, uint8_t queueNum, uint32_t resetStatus);

/**
 * Enable/disable header-data split feature. When enabled, frame
 * L2/L3/L4 headers will written to separate buffer, before data
 * starts in a second buffer (if not zero payload)
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable; if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if success
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_SetHdrDataSplit(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable status for header-data split feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning enabled status
 * @return CDN_EOK successful
 * @return CDN_ENOTSUP if ip version is 1p13 with gem_vm option - per queue values possible
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_GetHdrDataSplit(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable or disable header data splitting for given queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Rx queue
 * @param[in] enable Enable header data Splitting. When true, receive frames will be forwarded to main memory
 *    using a minimum of two DMA data buffers.
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if ip version not 1p13 or gem_vm == false - functionality not supported
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetQHdrDataSplit(CEDI_PrivateData* pD, uint8_t queueNum, bool enable);

/**
 * Read the state of header data splitting function for given queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum number of Rx queue
 * @param[out] enabled Enable state of header data splitting function
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if ip version not 1p13 or gem_vm == false - functionality not supported
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetQHdrDataSplit(CEDI_PrivateData* pD, uint8_t queueNum, bool* enabled);

/**
 * Enable/disable Receive Segment Coalescing function. When enabled,
 * consecutive TCP/IP frames on a priority queue will be combined to
 * form a single large frame
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queue priority queue to enable or disable RSC on
 * @param[in] enable if =1 enable RSC on selected priority queue(s), else disable it $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameter
 * @return CDN_ENOTSUP if feature not available
 * $VALIDFAIL if (%P_Config.rxQs==1) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((enable==0) && ((queue<1)||(queue>%P_Config.rxQs-1))) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetRscEnable(CEDI_PrivateData* pD, uint8_t queue, uint8_t enable);

/**
 * Read enabled status of RSC on a specified priority queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queue priority queue to read RSC enabled status for
 * @param[out] enable pointer for returning enabled status
 * @return CDN_EOK successful
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_ENOTSUP if feature not available
 * $VALIDFAIL if (%P_Config.rxQs==1) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetRscEnable(CEDI_PrivateData* pD, uint8_t queue, uint8_t* enable);

/**
 * "Set/Clear Mask of Receive Segment Coalescing disabling. When mask
 * is set and RSC is enabled, the RSC operation is not disabled by
 * receipt of frame with an end-coalesce flag set (SYN/FIN/RST/URG)"
 * @param[in] pD driver private state info specific to this instance
 * @param[in] setMask if =1 prevents RSC disabling by end-coalesce flags (SYN/FIN/RST/URG) - applies to all queues $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_ENOTSUP if feature not available
 */
uint32_t CEDI_SetRscClearMask(CEDI_PrivateData* pD, uint8_t setMask);

/**
 * Set specific address register to the given address value
 * @param[in] pD driver private state info specific to this instance
 * @param[in] addrNum number of specific address filter, in range 1 - num_spec_add_filters
 * @param[in] addr pointer to the 6-byte MAC address value to write
 * @param[in] specFilterType flag specifying whether to use MAC source or destination address to be compared for filtering. Source filter when =1. $RANGE $FROM 0 $TO 1 $
 * @param[in] byteMask Bits masking out bytes of specific address from comparison. $RANGE $FROM 0 $TO 0x3F $TEST_SUBSET 8 $
 * @return CDN_EOK if success
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_ENOTSUP if no specific address registers available
 * $VALIDFAIL if (addrNum==1) $SKIP $
 * $VALIDFAIL if (%P_DesignCfg.num_spec_add_filters==0) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetSpecificAddr(CEDI_PrivateData* pD, uint8_t addrNum, const CEDI_MacAddress* addr, uint8_t specFilterType, uint8_t byteMask);

/**
 * Get the value of a specific address register destination address
 * for filtering. When set to 1 use source address.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] addrNum number of specific address filter, in range 1 - num_spec_add_filters
 * @param[out] addr pointer to a 6-byte MAC address struct for returning the address value
 * @param[out] specFilterType flag specifying whether to use MAC source or destination address to be
 *    compared for filtering. =1 for source address
 * @param[out] byteMask "Bits masking out bytes of specific address from comparison.  When high,
 *    the associated address byte will be ignored. e.g. LSB of byteMask=1
 *    implies first byte received should not be compared."
 * @return CDN_EOK if success
 * @return CDN_EINVAL if invalid parameter
 * @return CDN_ENOTSUP if no specific address registers available
 * $VALIDFAIL if (addrNum==1) $SKIP $
 * $VALIDFAIL if (%P_DesignCfg.num_spec_add_filters==0) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetSpecificAddr(CEDI_PrivateData* pD, uint8_t addrNum, CEDI_MacAddress* addr, uint8_t* specFilterType, uint8_t* byteMask);

/**
 * Set the specific address 1 mask register to the given value,
 * allowing address matching against a portion of the specific address
 * 1 register
 * @param[in] pD driver private state info specific to this instance
 * @param[in] mask pointer to the address mask value to write
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if mask equal NULL
 * @return CDN_ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
 */
uint32_t CEDI_SetSpecificAddr1Mask(CEDI_PrivateData* pD, const CEDI_MacAddress* mask);

/**
 * Get the value of specific address 1 mask register
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mask pointer to a 6-byte MAC address struct for returning the mask value
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if mask equal NULL
 * @return CDN_ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
 */
uint32_t CEDI_GetSpecificAddr1Mask(CEDI_PrivateData* pD, CEDI_MacAddress* mask);

/**
 * Disable the specific address match stored at given register, by
 * writing 0 to lower address register
 * @param[in] pD - driver private state info specific to this instance
 * @param[in] addrNum - number of specific address filters, in range 1 - num_spec_add_filters
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if ((addrNum==0) || (addrNum>CEDI_DesignCfg.num_spec_add_filters))
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.num_spec_add_filters==0)
 */
uint32_t CEDI_DisableSpecAddr(const CEDI_PrivateData* pD, uint8_t addrNum);

/**
 * En/Disable Type ID match field of the specified register, and set
 * type Id value if enabling
 * @param[in] pD driver private state info specific to this instance
 * @param[in] matchSel number of TypeID Match register, range 1 - 4  $RANGE $FROM 1 $TO 4 $
 * @param[in] typeId the Type ID match value to write ignored if enable equal 0 $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 32 $
 * @param[in] enable if =1 enables the type matching for this ID, if =0 then disables type matching for this ID  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if matchSel invalid
 * $VALIDFAIL if ((enable==0)&&((matchSel<1)||(matchSel>4))) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetTypeIdMatch(CEDI_PrivateData* pD, uint8_t matchSel, uint16_t typeId, uint8_t enable);

/**
 * Read the specified Type ID match register settings
 * @param[in] pD driver private state info specific to this instance
 * @param[in] matchSel number of TypeID Match register, range 1 - 4  $RANGE $FROM 1 $TO 4 $
 * @param[out] typeId pointer for returning the Type ID match value read ignored if disabled
 * @param[out] enable "pointer for returning enabled status: equal 1 if typeId matching is
 *    enabled for this register, equal 0 if disabled"
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if matchSel invalid
 */
uint32_t CEDI_GetTypeIdMatch(CEDI_PrivateData* pD, uint8_t matchSel, uint16_t* typeId, uint8_t* enable);

/**
 * En/disable reception of unicast frames when hash register matched
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enables reception, if =0 then disables  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetUnicastEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Return state of unicast frame matching
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if reception enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetUnicastEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * En/disable reception of multicast frames when hash register matched
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enables, if =0 then disables  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetMulticastEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Return state of multicast frame matching
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetMulticastEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Dis/Enable receipt of broadcast frames
 * @param[in] pD driver private state info specific to this instance
 * @param[in] reject if =0 broadcasts are accepted, if =1 they are rejected.  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetNoBroadcast(CEDI_PrivateData* pD, uint8_t reject);

/**
 * Return broadcast rejection setting
 * @param[in] pD driver private state info specific to this instance
 * @param[out] reject returns 0 if broadcasts are accepted, 1 if they are rejected
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetNoBroadcast(CEDI_PrivateData* pD, uint8_t* reject);

/**
 * Enable or disable Send Broadcast/Multicast frames to all queues
 * feature. If enabled, broadcast frames will be redirected to all
 * receive queues, multicast frames will be redirected to all receive
 * queues matched by the screener registers.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable requested feature status - true if enable, false if disable
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if gem version unsupported (feature only supported on 1p13 with vm)
 */
uint32_t CEDI_SetSendBroadcastToAllQs(const CEDI_PrivateData* pD, bool enable);

/**
 * Get status of Send Broadcast/Multicast frames to all queues
 * feature.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enabled feature status - true if enabled, false if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if gem version unsupported (feature only supported on 1p13 with vm)
 */
uint32_t CEDI_GetSendBroadcastToAllQs(const CEDI_PrivateData* pD, bool* enabled);

/**
 * En/Disable receipt of only frames which have been VLAN tagged
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 reject non-VLAN-tagged frames, if =0 then accept  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetVlanOnly(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Return VLAN-tagged filter setting
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable returns 1 if non-VLAN-tagged frames rejected
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetVlanOnly(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * En/Disable stacked VLAN processing mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enables stacked VLAN processing, if =0 disables it  $RANGE $FROM 0 $TO 1 $
 * @param[in] vlanType sets user defined VLAN type for matching first VLAN tag. Ignored if enable equal 0. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 32 $
 */
void CEDI_SetStackedVlanReg(CEDI_PrivateData* pD, uint8_t enable, uint16_t vlanType);

/**
 * Reads stacked VLAN register settings.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning Enabled field equal 1 if enabled equal 0 if disabled.
 * @param[out] vlanType pointer for returning VLAN type field
 */
void CEDI_GetStackedVlanReg(CEDI_PrivateData* pD, uint8_t* enable, uint16_t* vlanType);

/**
 * En/Disable copy all frames mode
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enables copy all frames mode, if =0 then this is disabled  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetCopyAllFrames(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Get "copy all" setting
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if copy all frames mode enabled equal 0 if this is disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetCopyAllFrames(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set the hash address register.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] hAddrTop most significant 32 bits of hash register $RANGE $FROM 0 $TO 0xFFFFFFFF $TEST_SUBSET 32 $
 * @param[in] hAddrBot least significant 32 bits of hash register $RANGE $FROM 0 $TO 0xFFFFFFFF $TEST_SUBSET 32 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetHashAddr(const CEDI_PrivateData* pD, uint32_t hAddrTop, uint32_t hAddrBot);

/**
 * Read the hash address register.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] hAddrTop pointer for returning most significant 32 bits of hash register
 * @param[out] hAddrBot pointer for returning least significant 32 bits of hash register
 * @return CDN_EINVAL if any parameter equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetHashAddr(const CEDI_PrivateData* pD, uint32_t* hAddrTop, uint32_t* hAddrBot);

/**
 * Enable/disable discard of frames with length shorter than given in
 * length field
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetLenErrDiscard(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable status for discard of frames with length
 * shorter than given in length field.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetLenErrDiscard(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Read numbers of screener, ethtype & compare registers
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regNums points to a CEDI_NumScreeners struct for returning the numbers of registers
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_GetNumScreenRegs(const CEDI_PrivateData* pD, CEDI_NumScreeners* regNums);

/**
 * Write Rx frame matching values to a Type 1 screening register, for
 * allocating to a priority queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 1 register number, range 0 to CEDI_DesignCfg.num_type1_screeners-1
 * @param[in] regVals points to a CEDI_T1Screen struct with the match parameters to be written
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_SetType1ScreenReg(const CEDI_PrivateData* pD, uint8_t regNum, const CEDI_T1Screen* regVals);

/**
 * Read Rx frame matching values from a Type1 screening register
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 1 register number, range 0 to CEDI_DesignCfg.num_type1_screeners-1
 * @param[out] regVals points to a CEDI_T1Screen struct for returning the match parameters
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_GetType1ScreenReg(const CEDI_PrivateData* pD, uint8_t regNum, CEDI_T1Screen* regVals);

/**
 * Write Rx frame matching values to a Type 2 screening register, for
 * allocating to a priority queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1  $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[in] regVals points to a CEDI_T2Screen struct with the match parameters to be written
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_SetType2ScreenReg(const CEDI_PrivateData* pD, uint8_t regNum, const CEDI_T2Screen* regVals);

/**
 * Read Rx frame matching values from a Type 2 screening register
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1 $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[out] regVals points to a CEDI_T2Screen struct for returning the match parameters
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_GetType2ScreenReg(const CEDI_PrivateData* pD, uint8_t regNum, CEDI_T2Screen* regVals);

/**
 * Write the ethertype compare value at the given index in the
 * Ethertype registers
 * @param[in] pD driver private state info specific to this instance
 * @param[in] index Type 2 ethertype register number, range 0 to CEDI_DesignCfg.num_scr2_ethtype_regs-1 $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[in] eTypeVal Ethertype compare value to write $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_SetType2EthertypeReg(CEDI_PrivateData* pD, uint8_t index, uint16_t eTypeVal);

/**
 * Read the ethertype compare value at the given index in the
 * Ethertype registers
 * @param[in] pD driver private state info specific to this instance
 * @param[in] index Type 2 ethertype register number, range 0 to CEDI_DesignCfg.num_scr2_ethtype_regs-1 $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[out] eTypeVal pointer for returning the Ethertype compare value $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_GetType2EthertypeReg(CEDI_PrivateData* pD, uint8_t index, uint16_t* eTypeVal);

/**
 * Write the compare value at the given index in the Type 2 compare
 * register
 * @param[in] pD driver private state info specific to this instance
 * @param[in] index Type 2 compare register number, range 0 to CEDI_DesignCfg.num_scr2_compare_regs-1 $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[in] regVals points to a CEDI_T2Compare struct with the compare parameters to be written
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_SetType2CompareReg(CEDI_PrivateData* pD, uint8_t index, const CEDI_T2Compare* regVals);

/**
 * Read the compare value at the given index in the Type 2 compare
 * register
 * @param[in] pD driver private state info specific to this instance
 * @param[in] index Type 2 compare register number, range 0 to CEDI_DesignCfg.num_scr2_compare_regs-1 $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[out] regVals points to a CEDI_T2Compare struct for returning the compare parameters
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if parameter invalid
 */
uint32_t CEDI_GetType2CompareReg(CEDI_PrivateData* pD, uint8_t index, CEDI_T2Compare* regVals);

/**
 * Enable/disable pausing after valid non-zero (non-PFC) pause frame
 * received
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetPauseEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable of pausing after valid non-zero (non-PFC) pause
 * frame received.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetPauseEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Transmit a normal pause frame
 * @param[in] pD driver private state info specific to this instance
 */
void CEDI_TxPauseFrame(CEDI_PrivateData* pD);

/**
 * Transmit a pause frame with zero quantum value
 * @param[in] pD driver private state info specific to this instance
 */
void CEDI_TxZeroQPause(CEDI_PrivateData* pD);

/**
 * Return the current value of received pause quantum
 * @param[in] pD driver private state info specific to this instance
 * @param[out] value returns transmit pause quantum value
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRxPauseQuantum(CEDI_PrivateData* pD, uint16_t* value);

/**
 * Set the pause quantum value to use when transmitting non-zero
 * quantum pause frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] value transmit pause quantum value $RANGE $FROM 0 $TO 0xFFFF $TEST_SUBSET 32 $
 * @param[in] qpriority quantum priority, the priority for the pause quantum $RANGE $FROM 0 $TO CEDI_QUANTA_PRIORITY_MAX-1 $
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 * $VALIDFAIL if ((%P_DesignCfg.pfc_multi_quantum==0) && (qpriority>0)) $
 */
uint32_t CEDI_SetTxPauseQuantum(CEDI_PrivateData* pD, uint16_t value, uint8_t qpriority);

/**
 * Read the non-zero transmit pause quantum value
 * @param[in] pD driver private state info specific to this instance
 * @param[out] value returns transmit pause quantum value
 * @param[in] qpriority quantum priority,the priority for the pause quantum $RANGE $FROM 0 $TO CEDI_QUANTA_PRIORITY_MAX-1 $
 * @return CDN_EOK for success
 * @return CDN_EINVAL if invalid parameter
 * $VALIDFAIL if ((%P_DesignCfg.pfc_multi_quantum==0) && (qpriority>0)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetTxPauseQuantum(CEDI_PrivateData* pD, uint16_t* value, uint8_t qpriority);

/**
 * Disable/Enable copying of valid Rx pause frames to memory.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] disable if =1 disable, if =0 enable $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetCopyPauseDisable(CEDI_PrivateData* pD, uint8_t disable);

/**
 * Read disable/enable state for copying of valid Rx pause frames to
 * memory.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] disable if =1 disabled, if =0 enabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetCopyPauseDisable(CEDI_PrivateData* pD, uint8_t* disable);

/**
 * Enable/disable PFC negotiation and reception of priority based
 * pause frames.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable, if =0 then disable $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetPfcPriorityBasedPauseRx(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable state of reception for priority based pause
 * frames, and negotiation state. value can be decoded with two
 * constants:   if (OR with CEDI_PFC_PBP_RX_EN) not equal 0 then
 * PFC priority based pause frame Rx enabled   if (OR with
 * CEDI_PFC_PBP_NEG) not equal 0 then     PFC priority based pause has
 * been negotiated
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable returns combined enabled Rx state and negotiated state
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetPfcPriorityBasedPauseRx(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Transmit PFC Priority Based Pause Frame, taking field values as
 * defined by setTxPfcPauseFrameFields.
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_EINVAL if NULL pointer or not using full duplex mode or if transmission is disabled (mechanical success)
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $RETURN $COMMENT Not supported $
 */
uint32_t CEDI_TxPfcPriorityBasedPause(CEDI_PrivateData* pD);

/**
 * Set priority enable vector and zero quantum select vector fields of
 * the Tx PFC Pause Frame (see User Guide for description)
 * @param[in] pD driver private state info specific to this instance
 * @param[in] priEnVector written to priority enable vector of PFC priority based pause frame
 * @param[in] zeroQSelVector selects pause quantum fields to set to zero
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if pD equal NULL
 */
uint32_t CEDI_SetTxPfcPauseFrameFields(CEDI_PrivateData* pD, uint8_t priEnVector, uint8_t zeroQSelVector);

/**
 * Read priority enable vector and zero quantum select vector fields
 * selected by setTxPfcPauseFrameFields.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] priEnVector pointer for returning priority enable vector to be written to PFC priority based pause frame
 * @param[out] zeroQSelVector pointer for returning vector selecting pause quantum fields to set to zero
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if any parameter equal NULL
 */
uint32_t CEDI_GetTxPfcPauseFrameFields(CEDI_PrivateData* pD, uint8_t* priEnVector, uint8_t* zeroQSelVector);

/**
 * Set Enable bit for multiple PFC pause quantums, one per pause
 * priority.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enMultiPfcPause set this field to 1 to enable multiple PFC pause quantums. $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if pD equal NULL
 * $VALIDFAIL if ((%P_DesignCfg.pfc_multi_quantum==0) && (enMultiPfcPause==1)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetEnableMultiPfcPauseQuantum(CEDI_PrivateData* pD, uint8_t enMultiPfcPause);

/**
 * Get the Enable bit for multiple PFC pause quantums, one per pause
 * priority.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enMultiPfcPause equal 1 if multiple PFC pause quantums enabled
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if any parameter equal NULL
 * $VALIDFAIL if ((%P_DesignCfg.pfc_multi_quantum==0) && (enMultiPfcPause==1)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetEnableMultiPfcPauseQuantum(CEDI_PrivateData* pD, uint8_t* enMultiPfcPause);

/**
 * Enable/disable detection of unicast PTP frames.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetUnicastPtpDetect(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable state for detection of unicast PTP frames.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameters
 */
uint32_t CEDI_GetUnicastPtpDetect(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set Unicast IP destination address for detection of PTP Rx frames.
 * Unicast PTP frame recognition must be disabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] rxAddr IP destination address $RANGE $FROM 0 $TO 0xFFFFFFFF $TEST_SUBSET 32 $
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if unicast PTP frame recognition enabled
 * @return CDN_EOK if successful
 */
uint32_t CEDI_SetPtpRxUnicastIpAddr(CEDI_PrivateData* pD, uint32_t rxAddr);

/**
 * Read Unicast IP destination address for detection of PTP Rx frames.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] rxAddr returns IP destination address
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetPtpRxUnicastIpAddr(CEDI_PrivateData* pD, uint32_t* rxAddr);

/**
 * Set Unicast IP destination address for detection of PTP Tx frames.
 * Unicast PTP frame recognition must be disabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txAddr IP destination address $RANGE $FROM 0 $TO 0xFFFFFFFF $TEST_SUBSET 32 $
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_ENOTSUP if unicast PTP frame recognition enabled
 * @return CDN_EOK if successful
 */
uint32_t CEDI_SetPtpTxUnicastIpAddr(CEDI_PrivateData* pD, uint32_t txAddr);

/**
 * Returns Unicast IP destination address for detection of PTP Tx
 * frames.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txAddr returns IP destination address
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetPtpTxUnicastIpAddr(CEDI_PrivateData* pD, uint32_t* txAddr);

/**
 * Write 1588 timer registers.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] timeVal pointer to CEDI_1588TimerVal struct with values to write to timer registers
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_Set1588Timer(CEDI_PrivateData* pD, const CEDI_1588TimerVal* timeVal);

/**
 * Read 1588 timer registers.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning timer registers contents
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $RETURN $COMMENT Not supported by mechanical tests, covered in functional testing $
 */
uint32_t CEDI_Get1588Timer(CEDI_PrivateData* pD, CEDI_1588TimerVal* timeVal);

/**
 * Adjust the 1588 timer by adding or subtracting the specified number
 * of nanoseconds.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] nSecAdjust nanoseconds to adjust timer by: - if =1, enable time stamp storing, else disable (restore normal operation)  $RANGE $FROM -0x3FFFFFFF $TO 0x3FFFFFFF $
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_Adjust1588Timer(CEDI_PrivateData* pD, int32_t nSecAdjust);

/**
 * Set 1588 timer initial and alternative increments, and when to
 * switch to alternative increment. The initial, or normal, increment
 * is how many nanoseconds are added to the timer value on each pclk
 * or tsu_clk cycle (if tsu_clk equal 1 in DesignCfgReg5). If
 * altIncCount>0, after altIncCount increments the altNanoSInc value
 * is used for one cycle, then the increment returns to the initial
 * value. See EMAC User Guide [01] for further description.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] incSettings pointer to CEDI_TimerIncrement struct for defining how much to increment the timer each clock cycle
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_Set1588TimerInc(CEDI_PrivateData* pD, const CEDI_TimerIncrement* incSettings);

/**
 * Read 1588 timer increment settings.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] incSettings pointer to a CEDI_TimerIncrement struct for returning how the timer increment values
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 * $VALIDFAIL if (((%P_DesignCfg.moduleRev<0x0106) || ((%P_DesignCfg.moduleRev==0x0106) && (%P_DesignCfg.fixNumber==0))) && (incSettings.lsbSubNsInc>0)) $RETURN $
 */
uint32_t CEDI_Get1588TimerInc(CEDI_PrivateData* pD, CEDI_TimerIncrement* incSettings);

/**
 * Write TSU timer comparison value.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] timeVal pointer to CEDI_TsuTimerVal struct with values to write to comparison registers
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetTsuTimerCompVal(CEDI_PrivateData* pD, const CEDI_TsuTimerVal* timeVal);

/**
 * Read TSU timer comparison value.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_TsuTimerVal struct for returning comparison registers settings
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetTsuTimerCompVal(CEDI_PrivateData* pD, CEDI_TsuTimerVal* timeVal);

/**
 * Read 1588 timer value latched when SFD of PTP transmit primary
 * event crosses MII interface.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPtpFrameTxTime(CEDI_PrivateData* pD, CEDI_1588TimerVal* timeVal);

/**
 * Read 1588 timer value latched when SFD of PTP receive primary event
 * crosses MII interface.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPtpFrameRxTime(CEDI_PrivateData* pD, CEDI_1588TimerVal* timeVal);

/**
 * Read 1588 timer value latched when SFD of PTP transmit peer event
 * crosses MII interface.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPtpPeerFrameTxTime(CEDI_PrivateData* pD, CEDI_1588TimerVal* timeVal);

/**
 * Read 1588 timer value latched when SFD of PTP receive peer event
 * crosses MII interface.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPtpPeerFrameRxTime(CEDI_PrivateData* pD, CEDI_1588TimerVal* timeVal);

/**
 * Read nanoseconds and seconds (lo & hi words) from 1588 Timer Sync
 * Strobe registers
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_Get1588SyncStrobeTime(CEDI_PrivateData* pD, CEDI_1588TimerVal* timeVal);

/**
 * Enable/disable use of external time stamp port.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if ext_tsu_timer equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetExtTsuPortEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable status for use of external time stamp port.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 * $VALIDFAIL  $RETURN $COMMENT External TSU not available $
 */
uint32_t CEDI_GetExtTsuPortEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable one-step Tx sync mode in which timestamp field of
 * every transmitted 1588 sync frame is replaced with the current TSU
 * timestamp.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if tsu equals 0
 * @return CDN_EINVAL for invalid parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_Set1588OneStepTxSyncEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable state of one-step 1588 Tx sync mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning state equal 1 if enabled equal 0 if disabled.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_Get1588OneStepTxSyncEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set the descriptor time stamp mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txMode TX Descriptor timestamp insertion mode
 * @param[in] rxMode RX Descriptor timestamp insertion mode
 * @return CDN_EINVAL if pD is NULL/parameters out of range
 * @return CDN_EOK for success
 * $VALIDFAIL if (((%P_Config.enTxExtBD==0)&& (txMode!=0))|| ((%P_Config.enRxExtBD==0)&& (rxMode!=0))) $SKIP $
 */
uint32_t CEDI_SetDescTimeStampMode(CEDI_PrivateData* pD, CEDI_TxTsMode txMode, CEDI_RxTsMode rxMode);

/**
 * Get the descriptor time stamp mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txMode TX Descriptor timestamp insertion mode
 * @param[out] rxMode RX Descriptor timestamp insertion mode
 * @return CDN_EINVAL if pD is NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((%P_Config.enTxExtBD==0)||(%P_Config.enRxExtBD==0)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetDescTimeStampMode(CEDI_PrivateData* pD, CEDI_TxTsMode* txMode, CEDI_RxTsMode* rxMode);

/**
 * Enable/disable storing of nanoseconds field of Rx time stamp in CRC
 * field of received frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if tsu equal 0
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetStoreRxTimeStamp(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read Enable/disable state for storing nanoseconds Rx time stamp in
 * CRC field of received frame.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if time stamp storing enabled equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetStoreRxTimeStamp(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Does a PCS reset. After this, software can monitor getPcsReady to
 * determine when this has finished.
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_ENOTSUP if no_pcs defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_ResetPcs(CEDI_PrivateData* pD);

/**
 * Read PCS software reset bit, which goes high when resetPcs is
 * called, and returns low when the reset has completed, provided PCS
 * is enabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] ready pointer for returning 1 when PCS ready, i.e. reset has gone low or 0 if still in reset.
 * @return CDN_ENOTSUP if PCS not enabled
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPcsReady(CEDI_PrivateData* pD, uint8_t* ready);

/**
 * Enables and restarts auto-negotiation after writing the specified
 * abilities to the auto-negotiation advertisement register.  After
 * this, normal progress of auto-negotiation will lead to a lpPageRx
 * callback, which includes the ability register data received from
 * the link partner.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] advDat pointer to CEDI_AnAdvPage struct for setting the advertised abilities register
 * @return CDN_EBUSY if auto-negotiation already in progress
 * @return CDN_ENOTSUP if no_pcs defined or in SGMII mode
 * @return CDN_EINVAL if NULL parameter, invalid struct fields or completion event not enabled
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_StartAutoNegotiation(CEDI_PrivateData* pD, const CEDI_AnAdvPage* advDat);

/**
 * Enable/disable PCS auto-negotiation functionality.  If auto-
 * negotiation is in progress,  disabling will halt it.  If enabling
 * while underway, an error is returned.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if in SGMII mode
 * @return CDN_EBUSY if enable = 1 when auto-negotiation is under way
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetAutoNegEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable of PCS auto-negotiation functionality.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning state, equal 1 if enabled equal 0 if disabled.
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetAutoNegEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * If auto-negotiation is enabled, this reads the status of connection
 * to link partner, else it reads the synchronisation status. If link
 * goes down, status remains low until this is read. The driver will
 * remember the low condition when read from register (by this or
 * other PCS functions), and this will only update to current state
 * when this function is called (i.e. after reading the value to
 * return), or when link status is reported via the AnComplete
 * callback. Therefore, if getLinkStatus reports link down, the
 * function should be called again if the current status is required.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] status pointer returning 1 if link up (or sync) 0 if link down.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetLinkStatus(CEDI_PrivateData* pD, uint8_t* status);

/**
 * Read the remote fault status reported by link partner. Driver will
 * remember the high state when read from register, and only reset
 * when this function is called.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] status pointer returning 1 if remote fault indicated by link partner, 0 otherwise.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetAnRemoteFault(CEDI_PrivateData* pD, uint8_t* status);

/**
 * Read the auto-negotiation complete status. Completion will also be
 * reported by the anComplete callback, provided the
 * CEDI_EV_PCS_AN_COMPLETE interrupt is enabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] status pointer returning 1 if auto-negotiation complete 0 if incomplete.
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL for invalid pointer
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetAnComplete(CEDI_PrivateData* pD, uint8_t* status);

/**
 * Set advertisement base page fields.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] advDat - pointer to advertisement register data
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetAnAdvPage(CEDI_PrivateData* pD, const CEDI_AnAdvPage* advDat);

/**
 * Get advertisement base page fields, extracted into a CEDI_AnAdvPage
 * struct
 * @param[in] pD driver private state info specific to this instance
 * @param[out] advDat - pointer for returning the advertisement register data
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetAnAdvPage(CEDI_PrivateData* pD, CEDI_AnAdvPage* advDat);

/**
 * Get link partner ability page fields, extracted into a
 * CEDI_LpAbilityPage struct.  This is a struct of two different
 * structs, since the format depends on whether SGMII mode is in use
 * (network config bit 27)
 * @param[in] pD driver private state info specific to this instance
 * @param[out] lpAbl pointer for returning the link partner ability data
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetLpAbilityPage(CEDI_PrivateData* pD, CEDI_LpAbilityPage* lpAbl);

/**
 * Read flag from auto-negotiation expansion register, indicating a
 * base or next page has been received from the link partner.
 * @param[in] pD driver private state info specific to this instance
 * @return 1 if page received and no_pcs not defined
 * @return 0 if page not received or invalid pointer
 */
uint32_t CEDI_GetPageRx(CEDI_PrivateData* pD);

/**
 * Set next page register fields for auto-negotiation with fields
 * specified in a CEDI_AnNextPage struct.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] npDat - pointer to struct containing next page data to transmit
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter or invalid struct fields
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetNextPageTx(CEDI_PrivateData* pD, const CEDI_AnNextPage* npDat);

/**
 * Read next page register field data.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] npDat - pointer to struct for returning next page register data.
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetNextPageTx(CEDI_PrivateData* pD, CEDI_AnNextPage* npDat);

/**
 * Read next page data received from link partner.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] npDat - pointer to CEDI_LpNextPage struct for returning link partner next page data.
 * @return CDN_ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetLpNextPage(CEDI_PrivateData* pD, CEDI_LpNextPage* npDat);

/**
 * Get PCS PHY upper ID (= EMAC Module ID) & PCS PHY lower ID (= EMAC
 * Rev)
 * @param[in] pD driver private state info specific to this instance
 * @param[out] phyId composed of PCS PHY upper ID (= EMAC Module ID) in the upper 16 bits, and PCS PHY
 *    lower ID (= EMAC Rev) in the lower 16 bits.
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetPhyId(CEDI_PrivateData* pD, uint32_t* phyId);

/**
 * Enable/disable MDIO interface
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable MDIO interface, if =0 then disable it  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_SetMdioEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Get en/disable state of MDIO interface
 * @param[in] pD driver private state info specific to this instance
 * @return 0 if MDIO interface disabled or pD equal NULL, or NULL parameter
 * @return 1 if MDIO interface enabled
 */
uint32_t CEDI_GetMdioEnable(CEDI_PrivateData* pD);

/**
 * Initiate a write or set address operation on the MDIO interface.
 * Clause 45 devices require a call to set the register address (if
 * this is changing since last access), and then a write or read
 * operation. The command writes to the shift register, which starts
 * output on the MDIO interface. Write completion is signalled by the
 * phyManComplete callback, or by polling getMdioIdle.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] flags Combination of 2 bit-flags: if CEDI_MDIO_FLG_CLAUSE_45 present, specifies
 *    clause 45 PHY (else clause 22),
 *    if CEDI_MDIO_FLG_SET_ADDR present, specifies a set address operation (else
 *    do a write operation) - if not clause 45, this will be ignored. $RANGE $FROM 0 $OR_MASK CEDI_MDIO_FLG_* $
 * @param[in] phyAddr PHY address $RANGE $FROM 0 $TO 0x1F $TEST_SUBSET 8 $
 * @param[in] devReg device type (clause 45) or register address (clause 22) - enum CEDI_MdioDevType
 *    is available to specify the device type $RANGE $FROM 0 $TO 0x1F $TEST_SUBSET 8 $
 * @param[in] addrData register address (if CEDI_MDIO_FLG_SET_ADDR) or data to write
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 * $VALIDFAIL if (flags & %P_MDIO_FLG_INC_ADDR) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_PhyStartMdioWrite(CEDI_PrivateData* pD, uint8_t flags, uint8_t phyAddr, uint8_t devReg, uint16_t addrData);

/**
 * Initiate a read operation on the MDIO interface.  If clause 45, the
 * register address will need to be set by a preceding
 * phyStartMdioWrite call, unless same as for last operation.
 * Completion is signalled by the phyManComplete callback, which will
 * return the read data by a pointer parameter. Alternatively polling
 * getMdioIdle will indicate when the operation completes, then
 * getMdioReadDat will return the data.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] flags Combination of 2 bit-flags: if CEDI_MDIO_FLG_CLAUSE_45 present,
 *    specifies clause 45 PHY (else clause 22),
 *    If CEDI_MDIO_FLG_INC_ADDR present, and clause 45, then address will be
 *    incremented after the read operation. $RANGE $FROM 0 $OR_MASK CEDI_MDIO_FLG_* $
 * @param[in] phyAddr PHY address $RANGE $FROM 0 $TO 0x1F $TEST_SUBSET 8 $
 * @param[in] devReg device type (clause 45) or register address (clause 22) - enum CEDI_MdioDevType
 *    is available to specify the device type $RANGE $FROM 0 $TO 0x1F $TEST_SUBSET 8 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 * $VALIDFAIL if (flags & %P_MDIO_FLG_SET_ADDR) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_PhyStartMdioRead(CEDI_PrivateData* pD, uint8_t flags, uint8_t phyAddr, uint8_t devReg);

/**
 * Get data read from the PHY during a read operation.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] readData PHY read data, from in lower 16 bits of maintenance register
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetMdioReadData(CEDI_PrivateData* pD, uint16_t* readData);

/**
 * Read status of PHY management logic
 * @param[in] pD driver private state info specific to this instance
 * @return 1 for idle (mechanical success)
 * @return 0 for busy, or pD equal NULL
 * $VALIDFAIL if (1) $RETURN $COMMENT Not supported $
 */
uint32_t CEDI_GetMdioIdle(CEDI_PrivateData* pD);

/**
 * Copy the statistics registers contents into the statsRegs struct
 * reserved by client
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_ENOTSUP if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_ReadStats(CEDI_PrivateData* pD);

/**
 * Clear the statistics registers.
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_ENOTSUP if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_ClearStats(const CEDI_PrivateData* pD);

/**
 * Record snapshot of current statistics counts into snapshot
 * registers.
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_ENOTSUP if no_snapshot or no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_TakeSnapshot(CEDI_PrivateData* pD);

/**
 * Define action taken when statistics registers are read
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if no_snapshot or no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetReadSnapshot(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read state of ReadSnapshot flag
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning ReadSnapshot flag: if =1 then read
 *    snapshot is enabled; if =0 registers will show current statistics
 * @return CDN_ENOTSUP if no_snapshot or no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetReadSnapshot(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Set Wake On LAN (WOL) register using CEDI_WakeOnLanReg struct
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regVals pointer to CEDI_WakeOnLanReg struct for register values to set
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_SetWakeOnLanReg(CEDI_PrivateData* pD, const CEDI_WakeOnLanReg* regVals);

/**
 * Read Wake On LAN register using CEDI_WakeOnLanReg struct
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regVals pointer to CEDI_WakeOnLanReg struct for returning WOL register contents
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_GetWakeOnLanReg(CEDI_PrivateData* pD, CEDI_WakeOnLanReg* regVals);

/**
 * Enable/disable low power indication (LPI) transmission.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_SetLpiTxEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Get LPI transmission status
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CEDI_GetLpiTxEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Read LPI transitions & time in both Tx and Rx directions.  The
 * registers are all cleared on read.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] lpiStats pointer to a CEDI_LpiStats struct for returning the LPI statistics.
 * @return CDN_EOK if successful
 * @return CDN_EINVAL if invalid parameter
 */
uint32_t CEDI_GetLpiStats(CEDI_PrivateData* pD, CEDI_LpiStats* lpiStats);

/**
 * Copies all design configuration register fields into a
 * CEDI_DesignCfg struct declared by client software.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] hwCfg pointer to struct for receiving configuration data
 * @return CDN_EINVAL if any parameters =NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetDesignConfig(const CEDI_PrivateData* pD, CEDI_DesignCfg* hwCfg);

/**
 * Enable/disable writing to the statistics registers for debugging.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable writing, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetWriteStatsEnable(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable state of writing to the statistics registers
 * for debugging.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning state: equal 1 if writing enabled equal 0 if disabled.
 * @return CDN_EINVAL if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetWriteStatsEnable(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Increments all statistics registers contents by 1 for debugging.
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_EINVAL if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_IncStatsRegs(CEDI_PrivateData* pD);

/**
 * Enable/disable back pressure to force collisions an all received
 * frames in 10M or 100M half duplex mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable back pressure, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetRxBackPressure(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read Enable/disable state of back pressure to force collisions an
 * all received frames in 10M or 100M half duplex mode.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if enabled, equal 0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRxBackPressure(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable forcing collisions by PCS on transmit.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable forcing collisions, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if no_pcs defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetCollisionTest(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable state for forcing collisions by PCS on
 * transmit.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning state: equal 1 if forcing collisions enabled, equal 0 if disabled.
 * @return CDN_ENOTSUP if no_pcs defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetCollisionTest(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Enable/disable functionality to set backoff between collisions to
 * one slot time. This helps test for too many retries, and also
 * shortens pause countdown time in pause frame tests.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable retry test, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 */
void CEDI_SetRetryTest(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Read enable/disable status of retry test functionality.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable =1 if retry test enabled, =0 if disabled
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRetryTest(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Write to the user_out_width user outputs.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] outVal value to write to the user outputs
 * @return CDN_ENOTSUP if user_io not defined
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_WriteUserOutputs(CEDI_PrivateData* pD, uint16_t outVal);

/**
 * Read from the user_out_width user outputs.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] outVal pointer for returning value read from the user outputs
 * @return CDN_ENOTSUP if user_io not defined
 * @return CDN_EINVAL if NULL parameters
 * @return CDN_EOK for success
 */
uint32_t CEDI_ReadUserOutputs(CEDI_PrivateData* pD, uint16_t* outVal);

/**
 * Set the state of the specified user output pin.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] pin pin number to set, range 0 to user_out_width-1
 * @param[in] state level to set on the pin 1 for high, 0 for low  $RANGE $FROM 0 $TO 1 $
 * @return CDN_ENOTSUP if user_io not defined
 * @return CDN_EINVAL if pin out of range, or pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetUserOutPin(CEDI_PrivateData* pD, uint8_t pin, uint8_t state);

/**
 * Read from the user_in_width user inputs.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] inVal pointer for returning value read from the user inputs
 * @return CDN_ENOTSUP if user_io not defined
 * @return CDN_EINVAL if NULL parameter
 * @return CDN_EOK for success
 */
uint32_t CEDI_ReadUserInputs(CEDI_PrivateData* pD, uint16_t* inVal);

/**
 * Get the state of the specified user input pin.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] pin pin number to read
 * @param[out] state pointer for returning level present on the pin, 1 for high, 0 for low
 * @return CDN_ENOTSUP if user_io not defined
 * @return CDN_EINVAL if pin out of range, or pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetUserInPin(CEDI_PrivateData* pD, uint8_t pin, uint8_t* state);

/**
 * Read the state of the MDIO pin
 * @param[in] pD driver private state info specific to this instance
 * @param[out] state 1 for high, 0 for low
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetMdioInState(CEDI_PrivateData* pD, uint8_t* state);

/**
 * Direct read of register contents
 * @param[in] pD driver private state info specific to this instance
 * @param[in] offs address offset to register $RANGE $FROM 0 $TO sizeof(struct emac_regs) $
 * @param[out] data pointer for returning data read
 * @return CDN_EINVAL if offs out of range, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $RETURN $COMMENT Mechanical tests not supported - diagnostic only $
 */
uint32_t CEDI_ReadReg(const CEDI_PrivateData* pD, uint32_t offs, uint32_t* data);

/**
 * Direct write to register
 * @param[in] pD driver private state info specific to this instance
 * @param[in] offs address offset to register $RANGE $FROM 0 $TO sizeof(struct emac_regs) $
 * @param[in] data data to write
 * @return CDN_EINVAL if offs out of range, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $RETURN $COMMENT Mechanical tests not supported - diagnostic only $
 */
uint32_t CEDI_WriteReg(const CEDI_PrivateData* pD, uint32_t offs, uint32_t data);

/**
 * Change TX priority queues number. It is done by disabling or
 * enabling queues. If new queue number is lower than before it means
 * that some queues will be disabled. A Tx queue should only be
 * disabled after everything that has been queued into the descriptors
 * have been transmitted.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] numQueues number of TX priority queues $RANGE $FROM 1 $TO CEDI_MAX_TX_QUEUES $
 * @return CDN_EINVAL if number of queues is bigger than availble, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((numQueues>%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((numQueues<1)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetTxQueueNum(CEDI_PrivateData* pD, uint8_t numQueues);

/**
 * Return TX priority queues number.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] numQueues number of TX priority queues
 * @return CDN_EINVAL pD or numQueues equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetTxQueueNum(const CEDI_PrivateData* pD, uint8_t* numQueues);

/**
 * Change RX priority queues number. It is done by disabling or
 * enabling queues. If new queue number is lower than before it means
 * that some queues will be disabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] numQueues Number of RX priority queues. At least one queue must be enabled. $RANGE $FROM 1 $TO CEDI_MAX_RX_QUEUES $
 * @return CDN_EINVAL if number of queues is bigger than available, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((numQueues>%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((numQueues<1)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetRxQueueNum(CEDI_PrivateData* pD, uint8_t numQueues);

/**
 * Returns RX priority queues number
 * @param[in] pD driver private state info specific to this instance
 * @param[out] numQueues Number of RX priority queues.
 * @return CDN_EINVAL pD or numQueues is NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxQueueNum(const CEDI_PrivateData* pD, uint8_t* numQueues);

/**
 * configure number of memory segments assigned to a Tx queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueSegAlloc new configuration of segment allocation
 * @return CDN_EINVAL if segment allocation configuration is wrong, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if (1) $RETURN $COMMENT Not in mechanical tests, covered by functional testing $
 */
uint32_t CEDI_SetTxQueueSegAlloc(CEDI_PrivateData* pD, const CEDI_QueueSegAlloc* queueSegAlloc);

/**
 * function configures scheduler options for a TX queue. It is
 * possible to select one of four schedulers.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to configure
 * @param[in] schedType new scheduler type
 * @return CDN_EINVAL if TX queue scheduler configuration is wrong, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.txQs>2) && (queueNum<%P_Config.txQs - 2) && (schedType == %P_TX_SCHED_TYPE_CBS)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetTxQueueScheduler(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_TxSchedType schedType);

/**
 * get scheduler type for a TX queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to read configuration
 * @param[out] schedType returned scheduler type
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.txQs>2) && (queueNum<%P_Config.txQs - 2) && (schedType == %P_TX_SCHED_TYPE_CBS)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetTxQueueScheduler(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_TxSchedType* schedType);

/**
 * Configure rate limit for ETS or DWRR scheduler
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to read configuration
 * @param[in] limit Rate limit value
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_SetRateLimit(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t limit);

/**
 * Get rate limit for ETS or DWRR scheduler
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to read configuration
 * @param[out] limit Rate limit value
 * @return CDN_EOK for success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CEDI_GetRateLimit(const CEDI_PrivateData* pD, uint8_t queueNum, uint8_t* limit);

/**
 * function configures DWRR weight for DWRR scheduling algorithm for a
 * queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to configure
 * @param[in] dwrrWeightingVal new dwrr weighting value
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetDwrrWeighting(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t dwrrWeightingVal);

/**
 * function configures ETS bandwidth allocation for ETS scheduling
 * algorithm for a queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to configure ETS bandwidth allocation
 * @param[in] etsBandAlloc new ets bandwith allocation value
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetEtsBandAlloc(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t etsBandAlloc);

/**
 * function gets DWRR weight for DWRR scheduling algorithm for a queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get value from
 * @param[out] dwrrWeightingVal returned dwrr weighting value
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetDwrrWeighting(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t* dwrrWeightingVal);

/**
 * function gets ETS bandwidth allocation for ETS scheduling algorithm
 * for a queue
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get ETS bandwidth allocation value from
 * @param[out] etsBandAlloc returned ets bandwith allocation value
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetEtsBandAlloc(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t* etsBandAlloc);

/**
 * set timing configuration for Enhancement for Scheduled Traffic
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to configure $RANGE $TYPE $TEST_SUBSET 10 $
 * @param[in] enstTimeConfig new timing configuration
 * @return CDN_EINVAL if TX queue time scheduler configuration is wrong, or pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.txQs > 8) && (queueNum < (%P_Config.txQs - 8))) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetEnstTimeConfig(CEDI_PrivateData* pD, uint8_t queueNum, const CEDI_EnstTimeConfig* enstTimeConfig);

/**
 * get timing configuration for Enhancement for Scheduled Traffic
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get configuration
 * @param[out] enstTimeConfig new timing configuration
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.txQs > 8) && (queueNum < (%P_Config.txQs - 8))) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetEnstTimeConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_EnstTimeConfig* enstTimeConfig);

/**
 * Function enables or disables ENST time scheduling for queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queue priority queue to enable/disable ENST time scheduling
 * @param[in] enable if 0 then disable ENST, if 1 then enable ENST $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL or if ENST is not supported for particular queue
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queue>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.txQs > 8) && (queue < (%P_Config.txQs - 8))) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetEnstEnable(CEDI_PrivateData* pD, uint8_t queue, uint8_t enable);

/**
 * Function gets configuration of ENST time scheduling for queue state
 * can be 1 - means enabled, 0 - means disabled
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queue priority queue to get status of ENST time scheduling
 * @param[out] enable if 1 then ENST is enabled, if 0 then ENST is disabled $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL or if ENST is not supported for particular queue
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queue>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_Config.txQs > 8) && (queue < (%P_Config.txQs - 8))) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetEnstEnable(CEDI_PrivateData* pD, uint8_t queue, uint8_t* enable);

/**
 * Functions checks if core supports EnST
 * @param[in] pD driver private state info specific to this instance
 * @param[out] supported value "1" means that EnST is supported. "0" otherwise $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL or if supported equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetEnstSupported(CEDI_PrivateData* pD, uint8_t* supported);

/**
 * function configures report FCS/CRC error in receive buffer
 * descriptor,
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if 1 enable reporting FCS/CRC, if 0 disable reporting FCS/CRC $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetReportingBadFCS(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Function gets state of reporting FCS/CRC error in receive buffer
 * descriptor,
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable if 1 reporting FCS/CRC i enabled, if 0 reporting FCS/CRC is disabled $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetReportingBadFCS(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Function sets enables or disables 1588 One Step Correction Field
 * Update feature in controller,
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if 1 enable ptp one step correction, if 0 disable PTP one step correction $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetPtpSingleStep(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Function gets configuration enables of 1588 One Step Correction
 * Field Update feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable if 1 means that ptp one step correction is enabled, if 0 means that ptp one step correction is disabled $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPtpSingleStep(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Function enables or disables feature whis allows to execute MII
 * operation on RGMII interface
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable 1 - enable MII operation on RGMII interface, 0 -  enable MII operation on RGMII interface $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetMiiOnRgmii(CEDI_PrivateData* pD, uint8_t enable);

/**
 * Function gets configuration of feature allowing to execute MII
 * operation on RGMII interface
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable 1 - MII operation on RGMII interface is enabled, 0 - MII operation on RGMII interface is disabled
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetMiiOnRgmii(CEDI_PrivateData* pD, uint8_t* enable);

/**
 * Function sets a new idle slope value for the queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to set new idle slop value
 * @param[in] idleSlope new idle slop value $RANGE $TYPE $TEST_SUBSET 10 $
 * @return CDN_EINVAL if there is only one active queue
 * @return CDN_EOK for success
 * $VALIDFAIL if (%P_Config.txQs==1) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if (queueNum<%P_Config.txQs - 2) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetCbsIdleSlope(CEDI_PrivateData* pD, uint8_t queueNum, uint32_t idleSlope);

/**
 * Function gets  idle slope value for the queue.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to set new idle slop value
 * @param[out] idleSlope new idle slop value
 * @return CDN_EINVAL if there is only one active queue
 * @return CDN_EOK for success
 * $VALIDFAIL if (%P_Config.txQs==1) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if (queueNum<%P_Config.txQs - 2) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetCbsIdleSlope(CEDI_PrivateData* pD, uint8_t queueNum, uint32_t* idleSlope);

/**
 * Function gets link fault indication status
 * @param[in] pD driver private state info specific to this instance
 * @param[out] linkFault pointer to read link fault status
 * @return CDN_EINVAL for invalid linkFault
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 * $VALIDFAIL if (%P_DesignCfg.moduleRev < 0x010C) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetLinkFaultIndication(CEDI_PrivateData* pD, CEDI_LinkFaultIndication* linkFault);

/**
 * Function sets frame elimination tag size (4 or 6)
 * @param[in] pD driver private state info specific to this instance
 * @param[in] tagSize tag size 4 or 6 as enum
 * @return CDN_EINVAL for invalid tagSize
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 * $VALIDFAIL if ((tagSize != 0) && (tagSize != 1)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((%P_DesignCfg.moduleRev < 0x010C) && (tagSize == 0)) $EXPECT_RETURN CDN_EOK $
 * $VALIDFAIL if ((%P_DesignCfg.moduleRev < 0x010C) && (tagSize == 1)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetFrameEliminationTagSize(CEDI_PrivateData* pD, CEDI_RedundancyTagSize tagSize);

/**
 * Function gets frame elimination tag size
 * @param[in] pD driver private state info specific to this instance
 * @param[out] tagSize pointer to read current tag size
 * @return CDN_EINVAL if tagSize equal NULL
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetFrameEliminationTagSize(CEDI_PrivateData* pD, CEDI_RedundancyTagSize* tagSize);

/**
 * Function enable/disable elimination of received frames
 * functionality
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to enable disable  elimination frames $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[in] enable if 1 then enable frame elimination, if 0 disable it. $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetFrameEliminationEnable(CEDI_PrivateData* pD, uint8_t queueNum, uint8_t enable);

/**
 * Function returns state of elimination of received frames
 * functionality.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to check elimination frames $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[out] enable if 1 then frame elimination is enabled, if 0 it is disabled
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetFrameEliminationEnable(const CEDI_PrivateData* pD, uint8_t queueNum, uint8_t* enable);

/**
 * Function enable/disable sequence recovery reset timer for
 * elimination of received frames functionality
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to enable disable  elimination frames $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[in] enable 1 - enable sequence recovery reset timer. 0 otherwise. $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetFrameEliminationSeqRecRstTmrEnable(const CEDI_PrivateData* pD, uint8_t queueNum, uint8_t enable);

/**
 * Function returns state of sequence recovery reset timer for
 * elimination of received frames functionality.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to check elimination frames $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[out] enable 1 - sequence recovery reset timer is enabled. 0 otherwise.
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetFrameEliminationSeqRecRstTmrEnable(const CEDI_PrivateData* pD, uint8_t queueNum, uint8_t* enable);

/**
 * Function sets set configuration of frame elimination feature
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to configure elimination frames feature $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[in] fec configuration of frame elimination
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if (pD->frerEnabled[queueNum]) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetFrameEliminationConfig(const CEDI_PrivateData* pD, uint8_t queueNum, const CEDI_FrameEliminationConfig* fec);

/**
 * Function gets configuration of frame elimination feature
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get frame elimination configuration $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[out] fec configuration of frame elimination
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetFrameEliminationConfig(const CEDI_PrivateData* pD, uint8_t queueNum, CEDI_FrameEliminationConfig* fec);

/**
 * Function sets tag configuration of frame elimination feature
 * @param[in] pD driver private state info specific to this instance
 * @param[in] fetc tag configuration of frame elimination
 * @return CDN_EINVAL if fetc equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetFrameEliminationTagConfig(CEDI_PrivateData* pD, const CEDI_FrameEliminationTagConfig* fetc);

/**
 * Function gets tag configuration of frame elimination feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] fetc tag configuration of frame elimination
 * @return CDN_EINVAL if fetc equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetFrameEliminationTagConfig(CEDI_PrivateData* pD, CEDI_FrameEliminationTagConfig* fetc);

/**
 * Function sets configuration of timeout period
 * @param[in] pD driver private state info specific to this instance
 * @param[in] timeout Count of 8192 rx_clk periods
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetFrameEliminationTimoutConfig(CEDI_PrivateData* pD, uint16_t timeout);

/**
 * Function gets frame elimination statistics
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get statistics of FRER $RANGE $FROM 0 $TO CEDI_MAX_RX_QUEUES $
 * @param[out] stats Frame elimination statistcs
 * @return CDN_EINVAL for invalid queueNum
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>=%P_Config.rxQs)) $EXPECT_RETURN CDN_EINVAL $
 * $VALIDFAIL if ((queueNum>=%P_DesignCfg.num_cb_streams)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetFrameEliminationStats(const CEDI_PrivateData* pD, uint8_t queueNum, CEDI_FrameEliminationStats* stats);

/**
 * Function gets express MAC object
 * @param[in] pD driver private state info specific to this instance
 * @param[out] emacPrivateData express MAC private data object
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetEmac(CEDI_PrivateData* pD, CEDI_PrivateData** emacPrivateData);

/**
 * Function gets pre-emptive MAC object
 * @param[in] pD driver private state info specific to this instance
 * @param[out] pmacPrivateData pre-emption MAC private data object
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPmac(CEDI_PrivateData* pD, CEDI_PrivateData** pmacPrivateData);

/**
 * Function gets type of private data object
 * @param[in] pD driver private state info specific to this instance
 * @param[out] macType type of MAC private data object
 * @return CDN_EINVAL if macType equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetMacType(const CEDI_PrivateData* pD, CEDI_MacType* macType);

/**
 * Function sets configuration of preemption feature
 * @param[in] pD driver private state info specific to this instance
 * @param[in] preCfg configuration of preemption
 * @return CDN_EINVAL if preCfg equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetPreemptionConfig(CEDI_PrivateData* pD, const CEDI_PreemptionConfig* preCfg);

/**
 * Function gets configuration of preemption feature
 * @param[in] pD driver private state info specific to this instance
 * @param[out] preCfg read configuration of preemption
 * @return CDN_EINVAL if preCfg equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetPreemptionConfig(CEDI_PrivateData* pD, CEDI_PreemptionConfig* preCfg);

/**
 * Function initiate the verification procedure
 * @param[in] pD driver private state info specific to this instance
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_PreemptionRestartVerification(CEDI_PrivateData* pD);

/**
 * Enable or disable the specified MMSL interrupts
 * @param[in] pD driver private state info specific to this instance
 * @param[in] events OR'd combination of bit-flags selecting the events to be enabled or disabled
 * @param[in] enable if =1 enable the events, if =0 then disable  $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetMmslEventEnable(CEDI_PrivateData* pD, uint32_t events, uint8_t enable);

/**
 * Read the specified MMSL interrupts OR the returned event value with
 * the event bit-flags to determine if event(s) are enabled.
 * @param[in] pD driver private state info specific to this instance
 * @param[out] events returned enabled events
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetMmslEventEnable(CEDI_PrivateData* pD, uint32_t* events);

/**
 * reads MMSL statistics
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mmslStats mmsl statistics
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_ENOTSUP if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_ReadMmslStats(CEDI_PrivateData* pD, CEDI_MmslStats* mmslStats);

/**
 * reads MMSL status
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mmslStatus mmsl status
 * @return CDN_EINVAL if pD equal NULL
 * @return CDN_ENOTSUP if no_stats defined
 * @return CDN_EOK for success
 */
uint32_t CEDI_ReadMmslStatus(CEDI_PrivateData* pD, CEDI_MmslStatus* mmslStatus);

/**
 * Function sets lockup detection and recovery configuration
 * @param[in] pD driver private state info specific to this instance
 * @param[in] lockupCfg lockup detection and recovery configuration
 * @return CDN_EINVAL if lockupCfg equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetLockupConfig(CEDI_PrivateData* pD, const CEDI_LockupConfig* lockupCfg);

/**
 * Function gets lockup detection and recovery configuration
 * @param[in] pD driver private state info specific to this instance
 * @param[out] lockupCfg lockup detection and recovery configuration
 * @return CDN_EINVAL if lockupCfg equal NULL
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetLockupConfig(CEDI_PrivateData* pD, CEDI_LockupConfig* lockupCfg);

/**
 * Enable or disable dropping frames matching given type 1 screening
 * register.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 1 register number, range 0 to CEDI_DesignCfg.num_type1_screeners-1
 * @param[in] enable if =1 then enable dropping, if =0 then disable dropping. $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetType1ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum, uint8_t enable);

/**
 * Get status (enabled/disabled) of dropping frames matching given
 * type 1 screening registers.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 1 register number, range 0 to CEDI_DesignCfg.num_type1_screeners-1
 * @param[out] enable if =1 then enable dropping, if =0 then disable dropping.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetType1ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum, uint8_t* enable);

/**
 * Enable or disable dropping frames matching given type 2 screening
 * register.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1
 * @param[in] enable if =1 then enable dropping, if =0 then disable dropping. $RANGE $FROM 0 $TO 1 $
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetType2ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum, uint8_t enable);

/**
 * Get status (enabled/disabled) of dropping frames matching given
 * type 2 screening registers.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1
 * @param[out] enable if =1 then enable dropping, if =0 then disable dropping.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetType2ScreenRegDropEnable(CEDI_PrivateData* pD, uint8_t regNum, uint8_t* enable);

/**
 * Sets RX queue flush configuration.
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] queueNum number of the Rx queue.
 * @param[in] rxQFlushConfig Rx queue flush configuration.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetRxQFlushConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_RxQFlushConfig* rxQFlushConfig);

/**
 * Gets RX queue flush configuration.
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] queueNum number of the Rx queue.
 * @param[out] rxQFlushConfig Rx queue flush configuration.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxQFlushConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_RxQFlushConfig* rxQFlushConfig);

/**
 * Gets count of flushed RX packets.
 * @param[in] pD driver private state info specific to this instance.
 * @param[out] count number of flushed RX packets.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxDmaFlushedPacketsCount(CEDI_PrivateData* pD, uint16_t* count);

/**
 * Sets maximum receive data rate for traffic matching type 2
 * screening register. Setting interval time to '0' disables limiting
 * for given type 2 screener.
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1
 * @param[in] rateLimit Configuration of rate limiting for given screening register.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetType2ScreenerRateLimit(CEDI_PrivateData* pD, uint8_t regNum, CEDI_Type2ScreenerRateLimit* rateLimit);

/**
 * Gets maximum receive data rate for traffic matching type 2
 * screening register.
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1
 * @param[out] rateLimit Configuration of rate limiting for given screening register.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetType2ScreenerRateLimit(CEDI_PrivateData* pD, uint8_t regNum, CEDI_Type2ScreenerRateLimit* rateLimit);

/**
 * Gets status, whether or not rate limiting has been triggered for
 * given type 2 screening register.
 * @param[in] pD driver private state info specific to this instance.
 * @param[out] status ORed combination of bit flags for each type 2 screening register
 *    (bit 0 - screener 0, bit 15 - screener 15). If bit is set to '1',
 *    rate limiting mechanism for given screener has been triggered.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxType2RateLimitTriggered(CEDI_PrivateData* pD, uint16_t* status);

/**
 * Set receive watermark levels, related to sending PAUSE frames.
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] rxHighWatermark If not set to zero and receive SRAM fill level exceeds this value, a pause frame is transmitted. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $
 * @param[in] rxLowWatermark If not set to zero and receive SRAM fill level falls below this value, a zero-length pause frame is transmitted. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_SetRxWatermark(CEDI_PrivateData* pD, uint16_t rxHighWatermark, uint16_t rxLowWatermark);

/**
 * Get receive watermark levels, related to sending PAUSE frames.
 * @param[in] pD driver private state info specific to this instance.
 * @param[out] rxHighWatermark If not set to zero and receive SRAM fill level exceeds this value, a pause frame is transmitted.
 * @param[out] rxLowWatermark If not set to zero and receive SRAM fill level falls below this value, a zero-length pause frame is transmitted.
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 */
uint32_t CEDI_GetRxWatermark(CEDI_PrivateData* pD, uint16_t* rxHighWatermark, uint16_t* rxLowWatermark);

/**
 * Set AXI quality of service configuration for a specific queue
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] queueNum number of Tx queue $RANGE $FROM 0 $TO CEDI_MAX_TX_QUEUES-1 $
 * @param[in] axiQosConfig conifiguration of AXI QoS to set
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_SetAxiQosConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_AxiQosConfig* axiQosConfig);

/**
 * Get AXI quality of service configuration for a specific queue
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] queueNum number of Tx queue $RANGE $FROM 0 $TO CEDI_MAX_TX_QUEUES-1 $
 * @param[out] axiQosConfig read conifiguration of AXI QoS
 * @return CDN_EINVAL for invalid arguments values or NULL pointers
 * @return CDN_ENOTSUP if feature is not available
 * @return CDN_EOK for success
 * $VALIDFAIL if ((queueNum>%P_Config.txQs)) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetAxiQosConfig(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_AxiQosConfig* axiQosConfig);

/**
 * Get the information about ASF module
 * @param[in] pD Specific driver's Private Data structure
 * @param[out] asfInfo returns information about ASF module. It informs if ASF is included to GEM,
 *    how many instances of ASF are included and what are the register base offsets if any.
 *    ASF module has own Core Driver which does not connected with GEM Core Driver.
 * @return CDN_EOK on success
 * @return CDN_EINVAL if config is NULL, or hardware not present
 * $VALIDFAIL if (pD.regs==NULL) $EXPECT_RETURN CDN_EINVAL $
 */
uint32_t CEDI_GetAsfInfo(const CEDI_PrivateData* pD, CEDI_AsfInfo* asfInfo);

/**
 * Set watermark levels for queue for RX channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] watermarkLvl Pointer to struct with watermark levels (both: high and low)
 *    for queue.
 * @param[in] queueNum Number of queue which will be configured
 * @return CDN_EOK on success
 * @return CDN_EINVAL if pD or watermarkLvl is NULL, or queueNum is out of range
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetRxThresholdControl(CEDI_PrivateData* pD, const CEDI_WatermarkLvl* watermarkLvl, uint8_t queueNum);

/**
 * Get watermark levels for queue for RX channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] watermarkLvl Pointer to struct with watermark levels (both: high and low)
 *    for queue.
 * @param[in] queueNum Number of queue for which watermark levels will be read
 * @return CDN_EOK on success
 * @return CDN_EINVAL if pD or watermarkLvl is NULL, or queueNum is out of range
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_GetRxThresholdControl(const CEDI_PrivateData* pD, CEDI_WatermarkLvl* watermarkLvl, uint8_t queueNum);

/**
 * Set watermark levels for queue for TX channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] watermarkLvl Pointer to struct with watermark levels (both: high and low)
 *    for queue.
 * @param[in] queueNum Number of queue which will be configured
 * @return CDN_EOK on success
 * @return CDN_EINVAL if pD or watermarkLvl is NULL, or queueNum is out of range
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetTxThresholdControl(CEDI_PrivateData* pD, const CEDI_WatermarkLvl* watermarkLvl, uint8_t queueNum);

/**
 * Get watermark level for queue for TX channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] watermarkLvl Pointer to struct with watermark levels (both: high and low)
 *    for queue.
 * @param[in] queueNum Number of queue for which watermark level will be read
 * @return CDN_EOK on success
 * @return CDN_EINVAL if pD or watermarkLvl is NULL, or queueNum is out of range
 * @return CDN_ENOTSUP if function is not supported for GEM version
 */
uint32_t CEDI_GetTxThresholdControl(const CEDI_PrivateData* pD, CEDI_WatermarkLvl* watermarkLvl, uint8_t queueNum);

/**
 * Set priority configuration for AXI arbitration handling.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] axiCfg Pointer to struct with axi configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL if pD or axiCfg is NULL
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetAxiArbitrationCfg(CEDI_PrivateData* pD, const CEDI_AxiHostArbitrationCfg* axiCfg);

/**
 * Return priority configuration for AXI arbitration handling.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] axiCfg Pointer to axi configuration struct.
 * @return CDN_EOK on success
 * @return CDN_EINVAL if pD or axiCfg is NULL
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_GetAxiArbitrationCfg(const CEDI_PrivateData* pD, CEDI_AxiHostArbitrationCfg* axiCfg);

/**
 * Set maximum requests number from queue for each type of AXI
 * transaction allowed in the outstanding transaction buffer at any
 * one time for read channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] queueNum TX queue number $RANGE $TYPE $TEST_SUBSET 15 $
 * @param[in] axiChannel AXI channel type
 * @param[in] axiBuffCfg Pointer to struct with AXI outstanding transaction buffer configuration
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or axiBuffCfg is NULL or queue is out of range
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetAxiReqNum(CEDI_PrivateData* pD, uint8_t queueNum, CEDI_AxiChannelType axiChannel, const CEDI_AxiBuffCfg* axiBuffCfg);

/**
 * Get maximum requests number from queue for each type of AXI
 * transaction allowed in the outstanding transaction buffer at any
 * one time for read channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] queueNum TX queue number
 * @param[in] axiChannel AXI channel type
 * @param[out] axiBuffCfg Pointer to AXI outstanding transaction buffer configuration struct
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or axiBuffCfg is NULL or queue is out of range
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_GetAxiReqNum(const CEDI_PrivateData* pD, uint8_t queueNum, CEDI_AxiChannelType axiChannel, CEDI_AxiBuffCfg* axiBuffCfg);

/**
 * Set to convert received and accepted non-standard preamble to IEEE
 * 802.3 standard preamble.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if not-standard preamble should be converted
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is NULL or pD data are wrong
 * @return CDN_ENOTSUP if function is not supported for GEM version
 */
uint32_t CEDI_SetPreambleConversion(CEDI_PrivateData* pD, bool enable);

/**
 * Get if received and accepted non-standard preamble are converted to
 * IEEE 802.3 standard preamble.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable pointer to get not-standard preamble conversion status
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is NULL or pD data are wrong
 * @return CDN_ENOTSUP if function is not supported for GEM version
 */
uint32_t CEDI_GetPreambleConversion(const CEDI_PrivateData* pD, bool* enable);

/**
 * Set pause transmission on link interrupt.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable if 'true' transmission will be paused on link interrupt.
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is NULL or pD data are wrong
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_SetDeferOnLinkIntEnable(CEDI_PrivateData* pD, bool enable);

/**
 * Get if transmission is paused on link interrupt.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable if 'true' transmission is paused on link interrupt.
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is NULL or pD data are wrong
 * @return CDN_ENOTSUP if function is not supported by GEM version
 */
uint32_t CEDI_GetDeferOnLinkIntEnable(CEDI_PrivateData* pD, bool* enable);

/**
 * Function used to set SerDes interface rate for USXGMII PCS.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] serDes Value of SerDes rate
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null or pD, serDes data are wrong
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gSerdesRate(CEDI_PrivateData* pD, CEDI_SerdesRate serDes);

/**
 * Function used to get SerDes interface rate for USXGMII PCS.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] serDes Value of SerDes rate
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null or pD, serDes data are wrong
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW
 * @return CDN_EIO if wrong value was read from register
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gSerdesRate(CEDI_PrivateData* pD, CEDI_SerdesRate* serDes);

/**
 * Function used to set FEC functionality for USXGMII PCS.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable if 'true' FEC will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null or pD data are wrong
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW or HS is not set by SW
 * @return CDN_EIO if Tx or Rx Datapaths for PCS is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_usx_include_fec == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gFecEnable(CEDI_PrivateData* pD, bool enable);

/**
 * Function used to get if FEC functionality for USXGMII PCS is
 * enabled.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable if 'true' FEC is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null or pD data are wrong
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_usx_include_fec == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gFecEnable(const CEDI_PrivateData* pD, bool* enable);

/**
 * Function used to set operation mode for PCS25G (when available)
 * @param[in] pD Driver state info specific to this instance
 * @param[in] opMode Operation mode for PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null, pD data are wrong or opMode is out of range
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW or HS is not set by SW
 * @return CDN_EIO if Tx or Rx Datapaths for PCS is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gOperationMode(CEDI_PrivateData* pD, CEDI_Pcs25gOperationMode opMode);

/**
 * Function used to get current operation mode for PCS25G (when
 * available)
 * @param[in] pD Driver state info specific to this instance
 * @param[out] opMode Operation mode for PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null, pD data are wrong or opMode is out of range
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW or HS is not set by SW
 * @return CDN_EIO if incorrect data was read from register
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gOperationMode(const CEDI_PrivateData* pD, CEDI_Pcs25gOperationMode* opMode);

/**
 * Function used to set PCS25G test pattern mode (when available) for
 * Rx channel. This function can be called only when operation mode is
 * set on CEDI_TEST_PATTERN_MODE.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] patternMode Test pattern for PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null, pD data are wrong or patternMode is out of range
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW, HS is not set by SW or current operation mode is not CEDI_TEST_PATTERN_MODE
 * @return CDN_EIO if Rx datapath for PCS25G is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gRxTestPatternMode(CEDI_PrivateData* pD, CEDI_TestPatternMode patternMode);

/**
 * Function used to get PCS25G test pattern mode (when available) for
 * Rx channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] patternMode Test pattern for PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null, pD data are wrong or patternMode is out of range
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gRxTestPatternMode(const CEDI_PrivateData* pD, CEDI_TestPatternMode* patternMode);

/**
 * Function used to set PCS25G test pattern mode (when available) for
 * Tx channel. This function can be called only when operation mode is
 * set on CEDI_TEST_PATTERN_MODE.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] patternMode Test pattern for PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null, pD data are wrong or patternMode is out of range
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW, HS is not set by SW or current operation mode is not CEDI_TEST_PATTERN_MODE
 * @return CDN_EIO if Rx datapath for PCS25G is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gTxTestPatternMode(CEDI_PrivateData* pD, CEDI_TestPatternMode patternMode);

/**
 * Function used to get PCS25G test pattern mode (when available) for
 * Tx channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] patternMode Test pattern for PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is null, pD data are wrong or patternMode is out of range
 * @return CDN_ENOTSUP if HS or PCS is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gTxTestPatternMode(const CEDI_PrivateData* pD, CEDI_TestPatternMode* patternMode);

/**
 * Function used to get PCS25G status mode (when available) for Rx
 * channel.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] pcsStatus Status of PCS25G
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gStatus(const CEDI_PrivateData* pD, CEDI_Pcs25gStatus* pcsStatus);

/**
 * Function used to set test pattern seed for pseud random counter
 * transmission.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] testSeedReg Describes where (A or B) test pattern we be wrote
 * @param[in] testPatternSeed Struct with test pattern values
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * @return CDN_EIO if Tx datapath for PCS25G is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gTxTestPatternSeed(CEDI_PrivateData* pD, CEDI_TestSeedReg testSeedReg, const CEDI_TestPatternSeed* testPatternSeed);

/**
 * Function used to set test pattern seed for pseud random counter
 * transmission.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] testSeedReg Describes from where (A or B) test pattern will be read
 * @param[out] testPatternSeed Struct to save test pattern values
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * @return CDN_EIO if Tx datapath for PCS25G is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gTxTestPatternSeed(const CEDI_PrivateData* pD, CEDI_TestSeedReg testSeedReg, CEDI_TestPatternSeed* testPatternSeed);

/**
 * Function used to get block error count from Rx decoder
 * @param[in] pD Driver state info specific to this instance
 * @param[out] blockErrorCount Pointer to save block error count
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gRxDecoderErrCount(const CEDI_PrivateData* pD, uint8_t* blockErrorCount);

/**
 * "Function used to get test pattern checker error count (scrambled
 * idle errors if CEDI_SCRAMBLED_IDLE and pseudo random test pattern
 * errors for other)"
 * @param[in] pD Driver state info specific to this instance
 * @param[out] testPatternErrorCount Pointer to save test pattern checker error count
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gTestPatternErrCount(const CEDI_PrivateData* pD, uint16_t* testPatternErrorCount);

/**
 * "Function used to get PRBS Rx pattern error count"
 * @param[in] pD Driver state info specific to this instance
 * @param[out] prbsPatternErrorCount Pointer to save prbs pattern error count
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gPrbsErrorCount(const CEDI_PrivateData* pD, uint16_t* prbsPatternErrorCount);

/**
 * "Function used to get bit error count from BER monitor. Count of
 * errors in the sync bits."
 * @param[in] pD Driver state info specific to this instance
 * @param[out] bitErrorCount Pointer to save bit error count
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gBitErrorCount(const CEDI_PrivateData* pD, uint32_t* bitErrorCount);

/**
 * "Function used to get FEC error count"
 * @param[in] pD Driver state info specific to this instance
 * @param[out] fecError Pointer to struct to save FEC error count
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gFecErrorCount(const CEDI_PrivateData* pD, CEDI_FecError* fecError);

/**
 * Function used to set supported events for PCS25G module.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] events Events to enable/disable
 * @param[in] enable Enable events if 'true', disable if 'false'
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gEventEnable(CEDI_PrivateData* pD, uint32_t events, bool enable);

/**
 * Function used to get currently supported events for PCS25G module.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] events Events to enable/disable
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gEventEnable(const CEDI_PrivateData* pD, uint32_t* events);

/**
 * Function used to set Tx scrambler bypassing for PCS25G.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if tx scrambler will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * @return CDN_EIO if any of Rx&Tx datapaths is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gTxScrBypassEnable(CEDI_PrivateData* pD, bool enable);

/**
 * Function used to get if Tx scrambler is bypassed for PCS25G.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable true if tx scrambler is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gTxScrBypassEnable(CEDI_PrivateData* pD, bool* enable);

/**
 * Function used to set Rx descrambler bypassing for PCS25G.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if Rx descrambler will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * @return CDN_EIO if any of Rx&Tx datapaths is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gRxDescrBypassEnable(CEDI_PrivateData* pD, bool enable);

/**
 * Function used to get if Rx descrambler is bypassed for PCS25G
 * (USXGMII).
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable true if rx descrambler is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gRxDescrBypassEnable(CEDI_PrivateData* pD, bool* enable);

/**
 * "Function used to enable FEC corruption of PCS blocks on an
 * uncorrectable FEC block.  When disable, uncorrectable FEC block
 * have no effect on PCS sync headers."
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if Rx scrambler will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * @return CDN_EIO if Rx datapath is enabled
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gFecErrIndEnable(CEDI_PrivateData* pD, bool enable);

/**
 * "Function used to get if FEC corruption of PCS blocks on an
 * uncorrectable FEC block is enable."
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable true if rx scrambler is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gFecErrIndEnable(const CEDI_PrivateData* pD, bool* enable);

/**
 * "Function used to set Tx datapath enable."
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if Tx datapath will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gTxDatapathEnable(CEDI_PrivateData* pD, bool enable);

/**
 * Function used to get Tx datapath enable.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable true if Tx datapath is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gTxDatapathEnable(CEDI_PrivateData* pD, bool* enable);

/**
 * "Function used to set Rx datapath enable."
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if Rx datapath will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gRxDatapathEnable(CEDI_PrivateData* pD, bool enable);

/**
 * Function used to get Rx datapath enable.
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable true if Rx datapath is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gRxDatapathEnable(CEDI_PrivateData* pD, bool* enable);

/**
 * "Function used to enable PCS25G."
 * @param[in] pD Driver state info specific to this instance
 * @param[in] enable true if USXGMII will be enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_SetPcs25gEnable(CEDI_PrivateData* pD, bool enable);

/**
 * "Function used to get if PCS25G is enabled."
 * @param[in] pD Driver state info specific to this instance
 * @param[out] enable true if USXGMII is enabled
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD or pcsStatus is null, pD data are wrong
 * @return CDN_ENOTSUP if PCS25G is not supported by HW or HS is not set by SW
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_DesignCfg.gem_high_speed == 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if ((%P_DesignCfg.moduleId == 0x0008U) || (%P_DesignCfg.moduleId == 0x000BU) || (%P_DesignCfg.moduleRev < 0x010DU)) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_GetPcs25gEnable(const CEDI_PrivateData* pD, bool* enable);

/**
 * Function used to setup PCS25G
 * @param[in] pD Driver state info specific to this instance
 * @param[in] pcsCfg Pointer to structure with PCS25G configuration
 * @param[in] enable Set high to enable PCS25G after setup
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is wrong or macType is eMac
 * @return CDN_ENOTSUP if PCS25G is not included into design or choosen interface is not SERDES
 * @return CDN_EIO if synchronization was not achieved or register access error
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_Pcs25gSetup(CEDI_PrivateData* pD, const CEDI_Pcs25gCfg* pcsCfg, bool enable);

/**
 * Function used for polling PCS25G synchronization
 * @param[in] pD Driver state info specific to this instance
 * @return CDN_EOK if success
 * @return CDN_EINVAL if pD is wrong or macType is eMac
 * @return CDN_ENOTSUP if PCS25G is not included into design or choosen interface is not SERDES
 * @return CDN_EIO if synchronization was not achieved
 * $VALIDFAIL if (%P_DesignCfg.no_pcs != 0U) $EXPECT_RETURN CDN_ENOTSUP $
 * $VALIDFAIL if (%P_Config.ifTypeSel != CEDI_IFSP_USXGMII) $EXPECT_RETURN CDN_ENOTSUP $
 */
uint32_t CEDI_CheckPcs25gSync(const CEDI_PrivateData* pD);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* CEDI_IF_H */
