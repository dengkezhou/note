/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */
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
#ifndef CEDI_STRUCTS_IF_H
#define CEDI_STRUCTS_IF_H

#include "cdn_stdtypes.h"
#include "cedi_if.h"

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
/**
 * Configuration parameters passed to probe & init.
 * Note that only the first eight fields are required for the probe call;
 * all are required by init
*/
struct CEDI_Config_s
{
    /** base address of EMAC registers */
    uintptr_t regBase;
    /**
     * number of Rx priority queues, up to 1 more than
     * highest defined dma_priority_queueN value
     * (for example, =4 if highest is dma_priority_queue3)
    */
    uint8_t rxQs;
    /** number of Tx priority queues, same limit as for rxQs */
    uint8_t txQs;
    /**
     * number of descriptors in each Tx
     * descriptor queue
    */
    uint16_t txQLen[CEDI_MAX_TX_QUEUES];
    /** number of Tx descriptors in express MAC */
    uint16_t eTxQLen[CEDI_MAX_TX_QUEUES];
    /**
     * number of descriptors in each Rx
     * descriptor queue
    */
    uint16_t rxQLen[CEDI_MAX_RX_QUEUES];
    /** number of Rx descriptors in express MAC */
    uint16_t eRxQLen[CEDI_MAX_RX_QUEUES];
    /** DMA address bus width. 0=32b , 1=64b */
    CEDI_DmaAddrBusWidth dmaAddrBusWidth;
    /** enable Tx extended BD mode */
    uint8_t enTxExtBD[CEDI_MAX_TX_QUEUES];
    /** enable Rx extended BD mode */
    uint8_t enRxExtBD[CEDI_MAX_RX_QUEUES];
    /**
     * sets endian swap for data buffers and descriptors
     * accesses: "OR'd combination of CEDI_END_SWAP_DESC
     * and CEDI_END_SWAP_DATA" $RANGE $FROM 0 $OR_MASK CEDI_END_SWAP_* $
    */
    uint8_t dmaEndianism;
    /** DMA bus width: 32, 64 or 128 bits */
    CEDI_DmaBusWidth dmaBusWidth;
    /**
     * events to enable on start, OR together bit-flags
     * defined in Interrupt control
    */
    uint32_t intrEnable;
    /**
     * Upper 32 bits of physical address of Tx descriptor queues.
     * Used only if DMA configured for 64-bit addressing.
     * This is the single upper address used for Tx & Rx descriptors by older
     * MAC h/w, in GEM_GXL before r1p06f2, and XGM_GXL up to r1p01
    */
    uint32_t upper32BuffTxQAddr;
    /**
     * Upper 32 bits of physical address of Rx descriptor queues.
     * Used only if DMA configured for 64-bit addressing
    */
    uint32_t upper32BuffRxQAddr;
    /**
     * start address of Tx descriptor queues (contiguous
     * block for all queues)
    */
    uintptr_t txQAddr;
    /** physical address of Tx descriptor queues */
    uint32_t txQPhyAddr;
    /**
     * start address of Rx descriptor queues (contiguous
     * block for all queues)
    */
    uintptr_t rxQAddr;
    /** physical address of Rx descriptor queues */
    uint32_t rxQPhyAddr;
    /**
     * length of rx buffers, as a multiple of 64 bytes,
     * e.g. 2 = 128 bytes
    */
    uint8_t rxBufLength[CEDI_MAX_RX_QUEUES];
    /**
     * transmit packet buffer size select
     * 1: Use full configured addressable space (4 Kb)
     * 0: Do not use top address bit (2 Kb)
    */
    uint8_t txPktBufSize;
    /**
     * receive packet buffer size select
     * 11: Use full configured addressable space (8 Kb)
     * 10: Do not use top address bit (4 Kb)
     * 01: Do not use top two address bits (2 Kb)
     * 00: Do not use top three address bits (1 Kb) $RANGE $FROM 0 $TO 3 $
    */
    uint8_t rxPktBufSize;
    /** fixed burst length for DMA data transfers */
    CEDI_DmaDatBLen dmaDataBurstLen;
    /**
     * DMA config register bits 24, 25 & 26.
     * OR the following bit-flags to set corresponding bits -
     * CEDI_CFG_DMA_DISC_RXP,
     * CEDI_CFG_DMA_FRCE_RX_BRST,
     * CEDI_CFG_DMA_FRCE_TX_BRST $RANGE $FROM 0 $OR_MASK CEDI_CFG_DMA_* $
    */
    uint8_t dmaCfgFlags;
    /**
     * set to 1 to initialise with MDIO enabled, or 0 to
     * disable
    */
    uint8_t enableMdio;
    /** divisor to generate MDC from pclk */
    CEDI_MdcClkDiv mdcPclkDiv;
    /** MII/GMII/RGMII/SGMII/BASE_X selection */
    CEDI_Interface ifTypeSel;
    /** Speed selection */
    CEDI_IfSpeed ifSpeedSel;
    /**
     * enable alternative SGMII mode (auto-negotiation
     * ACK driven differently)
    */
    uint8_t altSgmiiEn;
    /** full/half duplex operation */
    uint8_t fullDuplex;
    /** enable Rx in half-duplex while Tx */
    uint8_t enRxHalfDupTx;
    /** enable external address match interface */
    uint8_t extAddrMatch;
    /** start-of-frame offset for writing Rx data (0 to 3 bytes) $RANGE $FROM 0 $TO CEDI_RX_MAX_BUFFER_OFFSET $ */
    uint8_t rxBufOffset;
    /** enable discard of frames with length field error */
    uint8_t rxLenErrDisc;
    /** disable copying Rx pause frames to memory */
    uint8_t disCopyPause;
    /** enable uni-direction Tx operation */
    uint8_t uniDirEnable;
    /**
     * enable checksum offload operation - OR bit-flags
     * to enable in Tx and/or Rx:
     * CEDI_CFG_CHK_OFF_TX,  CEDI_CFG_CHK_OFF_RX $RANGE $FROM 0 $OR_MASK CEDI_CFG_CHK_OFF_* $
    */
    uint8_t chkSumOffEn;
    /** enable Rx of frames up to 1536 bytes $RANGE $FROM 0 $TO 1 $ */
    uint8_t rx1536ByteEn;
    /** enable Rx of jumbo frames $RANGE $FROM 0 $TO 1 $ */
    uint8_t rxJumboFrEn;
    /** enable Rx frames with non-standard preamble $RANGE $FROM 0 $TO 1 $ */
    uint8_t enRxBadPreamble;
    /** ignore IPG rx_er (NetCfg b30) $RANGE $FROM 0 $TO 1 $ */
    uint8_t ignoreIpgRxEr;
    /**
     * replace CRC upper 16 bits with offset to UDP/TCP
     * header for Rx frames $RANGE $FROM 0 $TO 1 $
    */
    uint8_t storeUdpTcpOffset;
    /** enable external TSU timer port $RANGE $FROM 0 $TO 1 $ */
    uint8_t enExtTsuPort;
    /**
     * Maximum number of outstanding AXI write requests,
     * that can be issued by DMA via the AW channel.
     * Must not be = 0 if using AXI as this would disable writes $RANGE $FROM 1 $TO 255 $TEST_SUBSET 16 $
    */
    uint8_t aw2bMaxPipeline;
    /**
     * Maximum number of outstanding AXI read requests,
     * that can be issued by DMA via the AR channel.
     * Must not be = 0 if using AXI as this would disable reads $RANGE $FROM 1 $TO 255 $TEST_SUBSET 16 $
    */
    uint8_t ar2rMaxPipeline;
    /** enable pfc multiple quantum (8 different priorities) $RANGE $FROM 0 $TO 1 $ */
    uint8_t pfcMultiQuantum;
    /**
     * address of CEDI_Statistics struct for driver to fill out: ignored if
     * no_stats = 1
    */
    uintptr_t statsRegs;
    /** if 1 then Interspersing Express Traffic feature will be handled by driver $RANGE $FROM 0 $TO 1 $ */
    uint8_t incExpressTraffic;
    /** preamble CRC coverage for Tx $RANGE $ENUM CEDI_PreCrcCover $ */
    uint8_t preInCrcTx;
    /** preamble CRC coverage for Rx $RANGE $ENUM CEDI_PreCrcCover $ */
    uint8_t preInCrcRx;
    /** Events to enable for PCS25G */
    uint32_t pcs25gEvEnable;
};

/** Configuration of PCS25G block */
struct CEDI_Pcs25gCfg_s
{
    /** Frequency of symbols repeating for USXGMII. */
    CEDI_SerdesRate serdesRate;
    /** Set 'true' to bypass receive scrambler */
    bool rxScrBypass;
    /** Set 'true' to bypass transmit scrambler */
    bool txScrBypass;
    /**
     * "Set 'true' to enable FEC corruption of PCS block. When low
     *  uncorrectable FEC blocks have no effect"
    */
    bool fecErrInd;
    /** Set 'true' to enable FEC (Forward Error Correction) mode */
    bool fecEnable;
    /** Set 'true' to enable receive datapath. Set 'false' to reset */
    bool rxDatapathEnable;
    /** Set 'true' to enable the tx datapath or 'false' to disable */
    bool txDatapathEnable;
};

/** System requirements returned by probe */
struct CEDI_SysReq_s
{
    /** "size of memory required for driver's private data" */
    uint32_t privDataSize;
    /** size of contiguous block of Tx descriptor lists */
    uint32_t txDescListSize;
    /** size of contiguous block of Rx descriptor lists */
    uint32_t rxDescListSize;
    /**
     * size of memory for storing statistics register contents:
     * returned as 0 if no_stats was set to 1
    */
    uint32_t statsSize;
};

/** Configuration of AXI arbitration handling */
struct CEDI_AxiHostArbitrationCfg_s
{
    /**
     * Configuration for AW channel. Selects between the fixed priorities
     * and the round robin algorithm. $RANGE $ENUM CEDI_AxiWritePriority $
    */
    uint8_t axiWriterArbiter;
    /**
     * Configuration for AR channel. Selects between the fixed priorities
     * and the round robin algorithm. $RANGE $ENUM CEDI_AxiReadPriority $
    */
    uint8_t axiReadArbiter;
    /**
     * Prioritization of receive descriptor. When 'true', a fixed priority scheme
     * will be used and TX desc arbiter will always issue read AXI requests for
     * the highest active queue. When 'false', TX data requester will select packet
     * data requests use round robin.
     * fashion.
    */
    bool rxDescPriorFixed;
    /**
     * Prioritization of transmit descriptor. When 'true', a fixed priority scheme
     * will be used and RX desc arbiter will always issue read AXI requests for
     * the highest active queue. When 'false', TX data requester will select packet
     * data requests use round robin.
    */
    bool txDescPriorFixed;
    /**
     * Prioritization of transmit data. When 'true', a fixed priority scheme
     * will be used and TX data arbiter will always issue read AXI requests for
     * the highest active queue. When 'false', TX data requester will select packet
     * data requests use round robin.
    */
    bool txDataPriorFixed;
};

/**
 * Watermark levels for queue. The values represent a log base two
 * of the buffer level. So, value of 0 represents fill level of 1,
 * 1 represents a level of 2, etc. Max tested value is 4.
*/
struct CEDI_WatermarkLvl_s
{
    /** Low watermark level in bits for queue. $RANGE $ENUM CEDI_WatermarkLevel $ */
    uint8_t low;
    /** High watermark level in bits for queue. $RANGE $ENUM CEDI_WatermarkLevel $ */
    uint8_t high;
};

/** AXI outstanding transaction buffer configuration for qX */
struct CEDI_AxiBuffCfg_s
{
    /**
     * Defines maximum number of receive RX data write requests (for read) or
     * TX transmit data fetch (for write) from qX allowed in the outstanding
     * transaction buffer at ony one time. $RANGE $TYPE $TEST_SUBSET 8 $
    */
    uint8_t maxDataReqNum;
    /**
     * Defines maximum number of transmit descriptor R/W requests from qX allowed
     * in the outstanding transaction buffer at any one time. $RANGE $TYPE $TEST_SUBSET 8 $
    */
    uint8_t maxTxDescrReqNum;
    /**
     * Defines maximum number of receive descriptor R/W requests from qX allowed
     * in the outstanding transaction buffer at any one time. $RANGE $TYPE $TEST_SUBSET 8 $
    */
    uint8_t maxRxDescrReqNum;
};

/** Struct used to collect PCS25G status */
struct CEDI_Pcs25gStatus_s
{
    /** The internal clock tolerance compensation FIFO's have overflowed or underflowed */
    uint8_t clockToleranceFault;
    /** High bit error rate (BER) detected */
    uint8_t highBer;
    /** TX Encoder state machine has entered into the error state */
    uint8_t txFault;
    /** RX Decoder state machine has entered into the error state */
    uint8_t rxFault;
    /** PCS has achieved block synchronization */
    uint8_t blockLock;
};

/** Struct used to set test pattern seed for PCS25G */
struct CEDI_TestPatternSeed_s
{
    /** Test pattern seed for pseudo random counter transmission, bits [57:32] $RANGE $FROM 0U $TO 67108863 $TEST_SUBSET 16 $ */
    uint32_t seedUpper;
    /** Test pattern seed for pseudo random counter transmission, bits [31:0] $RANGE $FROM 0U $TO 4294967295 $TEST_SUBSET 16 $ */
    uint32_t seedLow;
};

/** Struct used to collect number of blocks detected as errors */
struct CEDI_FecError_s
{
    /** Number of FEC blocks received that were detected as error and were uncorrectable */
    uint16_t uncorrect;
    /** Number of FEC blocks received that were detected as error and were corrected */
    uint16_t correct;
};

/** struct for returning contents of the Tx Status register */
struct CEDI_TxStatus_s
{
    uint8_t usedBitRead;
    uint8_t collisionOcc;
    uint8_t retryLimExc;
    uint8_t txActive;
    uint8_t txFrameErr;
    uint8_t txComplete;
    uint8_t txUnderRun;
    uint8_t lateCollision;
    uint8_t hRespNotOk;
    uint8_t txMacLockup;
    uint8_t txDmaLockup;
};

/** struct for returning Tx-related contents of the per Q Status register */
struct CEDI_TxQStatus_s
{
    uint8_t usedBitRead;
    uint8_t buffExMid;
    uint8_t txComplete;
};

/** Bit-field struct for returning contents of the Rx Status register */
struct CEDI_RxStatus_s
{
    uint8_t buffNotAvail;
    uint8_t frameRx;
    uint8_t rxOverrun;
    uint8_t hRespNotOk;
    uint8_t rxMacLockup;
    uint8_t rxDmaLockup;
};

/** struct for returning Tx-related contents of the per Q Status register */
struct CEDI_RxQStatus_s
{
    uint8_t usedBitRead;
    uint8_t frameRx;
};

/** Struct for virtual & physical addresses of DMA-addressable data buffer */
struct CEDI_BuffAddr_s
{
    unsigned long vAddr;
    unsigned long pAddr;
};

/** Struct describing  time stamp data allocated in descriptor */
struct CEDI_TimeStampData_s
{
    /** TS valid - set to 1 if valid data stored */
    uint8_t tsValid;
    /** Timestamp nanoseconds[29:0] - word2/4[29:0] */
    uint32_t tsNanoSec;
    /** Timestamp seconds[1:0] from word2/4[31:30], seconds[5:2]from word3/5[5:2] */
    uint32_t tsSecs;
};

/**
 * Struct describing time launch time data allocated in descriptor.
 * It is used to specify on a per-frame basis the TSU time (launch time)
 * at which a frame is to be transmitted
*/
struct CEDI_TransmitLaunchTime_s
{
    /** Time launch time nanoseconds[29:0] - word2/4[29:0] */
    uint32_t nanoSecs;
    /** Time launch time seconds[1:0] word2/4[31:30] */
    uint32_t secs;
};

/** struct for returning tx descriptor data */
struct CEDI_TxDescData_s
{
    /** physical & virtual addresses of buffer freed up */
    CEDI_BuffAddr bufAdd;
    /** Tx descriptor status word - only valid if first buffer of frame */
    uint32_t txDescStat;
    /** descriptor queue status, see freeTxDesc for description */
    uint8_t status;
    /** Tx descriptor timestamp when valid (txTsData.tsValid will be set to 1) */
    CEDI_TimeStampData txTsData;
};

/** struct for returning tx descriptor status fields */
struct CEDI_TxDescStat_s
{
    /** IP/TCP/UDP checksum offload errors - see CEDI_TXD_CHKOFF_ constants */
    uint8_t chkOffErr;
    /** late collision Tx error detected */
    uint8_t lateColl;
    /** DMA frame corruption */
    uint8_t frameCorr;
    /** Tx Underrun error detected */
    uint8_t txUnderrun;
    /** Tx error, retries limit exceeded */
    uint8_t retryExc;
};

/** struct for returning rx descriptor data */
struct CEDI_RxDescData_s
{
    /** Rx descriptor status word */
    uint32_t rxDescStat;
    /** Rx data status, see readRxBuf for description */
    uint8_t status;
    /** Rx descriptor timestamp when valid (rxTsData.tsValid will be set to 1) */
    CEDI_TimeStampData rxTsData;
};

/** struct for rx descriptor status fields */
struct CEDI_RxDescStat_s
{
    /** valid when eoh (length of header) or eof (total frame length) - includes b13 if not ignore fcs enabled */
    uint16_t bufLen;
    /** ignore if jumbo frames enabled */
    uint8_t fcsStatus;
    /** Start Of Frame in this buffer */
    uint8_t sof;
    /** End Of Frame in this buffer */
    uint8_t eof;
    /** Header-data split: header buffer */
    uint8_t header;
    /** Header-data split: End Of Header in this buffer */
    uint8_t eoh;
    /** Canonical Format Indicator */
    uint8_t cfi;
    /** VLAN Priority */
    uint8_t vlanPri;
    /** Priority tag detected */
    uint8_t priTagDet;
    /** VLAN tag detected */
    uint8_t vlanTagDet;
    /** only set if rx chksum offload disabled */
    uint8_t typeIdMatch;
    /** Type ID match register if typeIdMatch set (RegNumber-1, i.e. 0 => reg. 1 ) */
    uint8_t typeMatchReg;
    /** ignore if rx chksum offload disabled */
    uint8_t snapNoVlanCfi;
    /** chksum offload checking status */
    uint8_t chkOffStat;
    /**
     * specific address register match (b27 OR b28)
     * If packet buffer mode and extra specific address
     * registers are used, this indicates match in
     * one of the first eight registers
    */
    uint8_t specAddMatch;
    /**
     * specific addr match register if specAddMatch set
     * (RegNumber-1, i.e. 0 => reg. 1 )
    */
    uint8_t specAddReg;
    /** external address match */
    uint8_t extAddrMatch;
    /** unicast hash match */
    uint8_t uniHashMatch;
    /** multicast hash match */
    uint8_t multiHashMatch;
    /** all-1's broadcast address detected */
    uint8_t broadcast;
    /** FCS/CRC error */
    uint8_t crc;
};

/** parameters for qTxBuf function */
struct CEDI_qTxBufParams_s
{
    /** number of Tx queue $RANGE $FROM 0 $TO CEDI_MAX_TX_QUEUES-1 $ */
    uint8_t queueNum;
    /** pointer to struct containing physical & virtual addresses of buffer - virtual field is for upper layer use only, can contain other reference/status if required */
    CEDI_BuffAddr* bufAdd;
    /** length of data in buffer */
    uint32_t length;
    /** bit-flags (CEDI_TXB_xx) specifying last buffer/auto CRC and LSO controls */
    uint8_t flags;
    /** Segment/fragment size (MSS for TCP or MFS for UDP) - used for all data descriptors */
    uint16_t mssMfs;
    /** TCP Stream number, determines which auto-sequence counter to use - only for first (header) descriptor used when flags includes CEDI_TXB_TSO_AUTO_SEQ and CEDI_TXB_TCP_ENCAP */
    uint8_t tcpStream;
    /** Transmit launch time for start frame */
    CEDI_TransmitLaunchTime launchTime;
};

/** Q buffer sizes */
struct CEDI_FrameSize_s
{
    /** array of sizes per queue */
    uint32_t FrameSize[16];
};

/** struct for MAC address */
struct CEDI_MacAddress_s
{
    uint8_t byte[6];
};

/** struct containing all statistics register values (144 bytes long) */
struct CEDI_Statistics_s
{
    /** b31:0 of octets transmitted */
    uint32_t octetsTxLo;
    /** b47:32 of octets transmitted */
    uint16_t octetsTxHi;
    uint32_t framesTx;
    uint32_t broadcastTx;
    uint32_t multicastTx;
    uint16_t pauseFrTx;
    uint32_t fr64byteTx;
    uint32_t fr65_127byteTx;
    uint32_t fr128_255byteTx;
    uint32_t fr256_511byteTx;
    uint32_t fr512_1023byteTx;
    uint32_t fr1024_1518byteTx;
    uint32_t fr1519_byteTx;
    uint16_t underrunFrTx;
    uint32_t singleCollFrTx;
    uint32_t multiCollFrTx;
    uint16_t excessCollFrTx;
    uint16_t lateCollFrTx;
    uint32_t deferredFrTx;
    uint16_t carrSensErrsTx;
    /** b31:0 of octets received */
    uint32_t octetsRxLo;
    /** b47:32 of octets received */
    uint16_t octetsRxHi;
    uint32_t framesRx;
    uint32_t broadcastRx;
    uint32_t multicastRx;
    uint16_t pauseFrRx;
    uint32_t fr64byteRx;
    uint32_t fr65_127byteRx;
    uint32_t fr128_255byteRx;
    uint32_t fr256_511byteRx;
    uint32_t fr512_1023byteRx;
    uint32_t fr1024_1518byteRx;
    uint32_t fr1519_byteRx;
    uint16_t undersizeFrRx;
    uint16_t oversizeFrRx;
    uint16_t jabbersRx;
    uint16_t fcsErrorsRx;
    uint16_t lenChkErrRx;
    uint16_t rxSymbolErrs;
    uint16_t alignErrsRx;
    uint32_t rxResourcErrs;
    uint16_t overrunFrRx;
    uint16_t ipChksumErrs;
    uint16_t tcpChksumErrs;
    uint16_t udpChksumErrs;
    uint16_t dmaRxPBufFlush;
};

/** struct for returning number of screening registers */
struct CEDI_NumScreeners_s
{
    /** number of Type1 screener registers */
    uint8_t type1ScrRegs;
    /** number of Type2 screener registers */
    uint8_t type2ScrRegs;
    /** number of ethtype registers */
    uint8_t ethtypeRegs;
    /** number of compare registers */
    uint8_t compareRegs;
};

/** struct for writing/reading Type1 screening registers */
struct CEDI_T1Screen_s
{
    /** the priority queue allocated if match found, */
    uint8_t qNum;
    /** if =1, enable UDP port matching $RANGE $FROM 0 $TO 1 $ */
    uint8_t udpEnable;
    /** UDP port number to match if udpEnable=1 (ignored otherwise) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t udpPort;
    /** if =1, enable DS/TC field matching $RANGE $FROM 0 $TO 1 $ */
    uint8_t dstcEnable;
    /** DS field (IPv4) or TC field (IPv6) value to match against $RANGE $FROM 0 $TO 255 $TEST_SUBSET 8 $ */
    uint8_t dstcMatch;
};

/** struct for writing/reading Type2 screening registers */
struct CEDI_T2Screen_s
{
    /** the priority queue allocated if match found, $RANGE $TYPE $TEST_SUBSET 4 $ */
    uint8_t qNum;
    /** if =1, enable VLAN priority matching $RANGE $FROM 0U $TO 1U $ */
    uint8_t vlanEnable;
    /** VLAN priority to match if vlanEnable=1 (ignored otherwise) $RANGE $FROM 0U $TO 7U $ */
    uint8_t vlanPriority;
    /** if =1, enable EtherType field matching $RANGE $FROM 0U $TO 1U $ */
    uint8_t eTypeEnable;
    /** Index of EtherType match register: when supported up to: CEDI_DesignCfg.num_scr2_ethtype_regs $RANGE $FROM 0U $TO 7U $ */
    uint8_t ethTypeIndex;
    /** if =1, enable compare A matching $RANGE $FROM 0U $TO 1U $ */
    uint8_t compAEnable;
    /** Index of compare register for compare A match. When supported up to: CEDI_DesignCfg.num_scr2_compare_regs $RANGE $FROM 0U $TO CEDI_COMPARE_MAX_INDEX $ */
    uint8_t compAIndex;
    /** if =1, enable compare B matching $RANGE $FROM 0U $TO 1U $ */
    uint8_t compBEnable;
    /** Index of compare register for compare B match. When supported up to: CEDI_DesignCfg.num_scr2_compare_regs $RANGE $FROM 0U $TO CEDI_COMPARE_MAX_INDEX $ */
    uint8_t compBIndex;
    /** if =1, enable compare C matching $RANGE $FROM 0U $TO 1U $ */
    uint8_t compCEnable;
    /** Index of compare register for compare C match. When supported up to: CEDI_DesignCfg.num_scr2_compare_regs $RANGE $FROM 0U $TO CEDI_COMPARE_MAX_INDEX $ */
    uint8_t compCIndex;
};

/** struct for writing/reading screener Type 2 compare registers */
struct CEDI_T2Compare_s
{
    /** Mask Value field (or 1st 16 bits of compare when disableMask set) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t compMask;
    /** Compare Value field (or 2nd 16 bits of compare when disableMask set) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t compValue;
    /** Offset value $RANGE $FROM 0 $TO 63 $TEST_SUBSET 4 $ */
    uint8_t offsetVal;
    /** Position in frame to apply offset */
    CEDI_T2Offset offsetPosition;
    /** Disable mask value function, to extend compare value to 4 bytes. Set to 1 to disable mask. $RANGE $FROM 0 $TO 1 $ */
    uint8_t disableMask;
};

/** struct for writing/reading 1588 timer */
struct CEDI_1588TimerVal_s
{
    /** Upper 16 bits of seconds value */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value */
    uint32_t secsLower;
    /** Nanoseconds value (30 bits) $RANGE $FROM 0 $TO 1073741823 $TEST_SUBSET 4 $ */
    uint32_t nanosecs;
};

/** struct for writing/reading TSU timer */
struct CEDI_TsuTimerVal_s
{
    /** Upper 16 bits of seconds value $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value $RANGE $FROM 0 $TO 4294967295 $TEST_SUBSET 4 $ */
    uint32_t secsLower;
    /** Upper 22 bits of nanoseconds value $RANGE $FROM 0 $TO 4194303 $TEST_SUBSET 4 $ */
    uint32_t nanosecs;
};

/** struct for writing/reading the 1588 timer increment registers */
struct CEDI_TimerIncrement_s
{
    /** Whole nanoseconds to increment timer each clock cycle $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t nanoSecsInc;
    /** Sub-nanoseconds to increment the timer (16 bits) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 32 $ */
    uint16_t subNsInc;
    /** Lower 8 bits of sub-nanoseconds to increment the timer $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t lsbSubNsInc;
    /** Number of increments before changing to alternative increment. If = 0 then never use alternative increment. $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t altIncCount;
    /** Alternative nanoseconds increment to apply $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t altNanoSInc;
};

/**
 * struct for returning contents of the auto-negotiation advertisement
 * register
*/
struct CEDI_AnAdvPage_s
{
    /** full duplex capability $RANGE $FROM 0 $TO 1 $ */
    uint8_t fullDuplex;
    /** half duplex capability $RANGE $FROM 0 $TO 1 $ */
    uint8_t halfDuplex;
    /** pause capability */
    CEDI_PauseCap pauseCap;
    /** remote fault condition */
    CEDI_RemoteFault remFlt;
    /** next page exchange required $RANGE $FROM 0 $TO 1 $ */
    uint8_t nextPage;
};

/** struct for default (non-SGMII) auto-negotiation link partner abilities */
struct CEDI_defLpAbility_s
{
    /** full duplex capability */
    uint8_t fullDuplex;
    /** half duplex capability */
    uint8_t halfDuplex;
    /** pause capability */
    CEDI_PauseCap pauseCap;
    /** remote fault condition */
    CEDI_RemoteFault remFlt;
    /** link partner acknowledge indication */
    uint8_t lpAck;
    /** next page exchange required */
    uint8_t lpNextPage;
};

/** struct for SGMII mode auto-negotiation link partner abilities */
struct CEDI_sgmLpAbility_s
{
    /** speed, = 10/100/1000Mbps */
    CEDI_IfSpeed speed;
    /**
     * duplex capability, = 0 for half duplex,
     * =1 for full duplex
    */
    uint8_t duplex;
    /** link partner acknowledge indication */
    uint8_t lpAck;
    /** =0 if link down, =1 if link up */
    uint8_t linkStatus;
};

/**
 * struct of two possible link partner ability structs,
 * one for default configuration and one for SGMII configuration
*/
struct CEDI_LpAbility_s
{
    CEDI_defLpAbility defLpAbl;
    CEDI_sgmLpAbility sgmLpAbl;
};

/** Struct for link partner ability page info. If sgmii =0 then read default ability page struct from ablInfo. If sgmii =1 then read SGMII mode ability page struct from ablInfo. */
struct CEDI_LpAbilityPage_s
{
    CEDI_LpAbility ablInfo;
    uint8_t sgmii;
};

/** Struct for auto-negotiation next page register data */
struct CEDI_AnNextPage_s
{
    /** message data as defined by message page indicator (11 bits) $RANGE $FROM 0 $TO 0x7ff $ */
    uint16_t message;
    /** acknowledge 2 $RANGE $FROM 0 $TO 1 $ */
    uint8_t ack2;
    /** message page indicator $RANGE $FROM 0 $TO 1 $ */
    uint8_t msgPage;
    /** set if another next page to transmit $RANGE $FROM 0 $TO 1 $ */
    uint8_t np;
};

/** struct for auto-negotiation link partner next page data */
struct CEDI_LpNextPage_s
{
    /** message data as defined by message page indicator (11 bits) */
    uint16_t message;
    /** toggles for each received page */
    uint8_t toggle;
    /** acknowledge 2 */
    uint8_t ack2;
    /** message page indicator */
    uint8_t msgPage;
    /**
     * indicates if link partner successfully
     * received last message
    */
    uint8_t ack;
    /** set if another next page to transmit */
    uint8_t np;
};

/** struct for link partner page data - ability page or next page */
struct CEDI_LpPage_s
{
    CEDI_LpAbilityPage lpBasePage;
    CEDI_LpNextPage lpNextPage;
};

/** Struct for returning page data from link partner. If nextPage = 0 then read link partner base page from lpPage.lpBasePage, else read next page from lpPage.lpNextPage */
struct CEDI_LpPageRx_s
{
    CEDI_LpPage lpPageDat;
    uint8_t nextPage;
};

/** Struct for returning network status related to auto-negotiation */
struct CEDI_NetAnStatus_s
{
    /**
     * if auto-negotiation enabled: = 1 if LINK up,
     * = 0 if LINK down
     * else synchronisation status
    */
    uint8_t linkState;
    /** if = 1 then both devices full duplex */
    uint8_t duplexRes;
    /** enable pause Tx */
    uint8_t pauseTxRes;
    /** enable pause Rx */
    uint8_t pauseRxRes;
};

/** Struct for writing/reading the Wake On LAN register */
struct CEDI_WakeOnLanReg_s
{
    /** Least significant 16 bits of target IP address to match */
    uint16_t wolReqAddr;
    /** Magic packet events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint8_t magPktEn;
    /** ARP request events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint8_t arpEn;
    /** Specific address 1 events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint8_t specAd1En;
    /** Multicast hash events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint8_t multiHashEn;
};

/** Struct for returning the LPI Tx and Rx statistics */
struct CEDI_LpiStats_s
{
    /** Number of transitions to Rx low power idle */
    uint16_t rxLpiTrans;
    /** Counts time in Rx LPI indication */
    uint32_t rxLpiTime;
    /** Number of transitions to LPI Tx enable */
    uint16_t txLpiTrans;
    /** Counts time in LPI Tx enable */
    uint32_t txLpiTime;
};

/** time configuration of Enhancement for Scheduled Traffic */
struct CEDI_EnstTimeConfig_s
{
    /** time at which queue the queue will start (whole seconds part) $RANGE $FROM 0 $TO 3 $TEST_SUBSET 7 $ */
    uint8_t startTimeS;
    /** time at which queue the queue will start (nanoseconds part) $RANGE $FROM 0 $TO 0x3FFFFFFF $TEST_SUBSET 7 $ */
    uint32_t startTimeNs;
    /** time in which the gate for a queue has to be open, expressed in bytes $RANGE $FROM 0 $TO 0x1FFFF $TEST_SUBSET 7 $ */
    uint32_t onTime;
    /** time in which the gate for a queue has to be closed, expressed in bytes $RANGE $FROM 0 $TO 0x1FFFF $TEST_SUBSET 7 $ */
    uint32_t offTime;
};

/** Struct containing all design configuration fields, plus some other features which are revision-dependent, e.g. intrp_mod */
struct CEDI_DesignCfg_s
{
    uint16_t moduleId;
    uint16_t moduleRev;
    uint8_t fixNumber;
    uint8_t numQueues;
    uint8_t no_pcs;
    uint8_t serdes;
    uint8_t RDC_50;
    uint8_t TDC_50;
    uint8_t int_loopback;
    uint8_t no_int_loopback;
    uint8_t ext_fifo_interface;
    uint8_t apb_rev1;
    uint8_t apb_rev2;
    uint8_t user_io;
    uint8_t user_out_width;
    uint8_t user_in_width;
    uint8_t no_scan_pins;
    uint8_t no_stats;
    uint8_t no_snapshot;
    uint8_t irq_read_clear;
    uint8_t exclude_cbs;
    uint8_t exclude_qbv;
    uint8_t num_spec_add_filters;
    uint8_t dma_bus_width;
    uint8_t axi_cache_value;
    uint16_t jumbo_max_length;
    uint8_t hprot_value;
    uint8_t rx_pkt_buffer;
    uint8_t tx_pkt_buffer;
    uint8_t rx_pbuf_addr;
    uint8_t tx_pbuf_addr;
    uint8_t axi;
    uint8_t rx_fifo_cnt_width;
    uint8_t tx_fifo_cnt_width;
    uint8_t tsu;
    uint8_t phy_ident;
    uint8_t dma_bus_width_def;
    uint8_t mdc_clock_div;
    uint8_t endian_swap_def;
    uint8_t rx_pbuf_size_def;
    uint8_t tx_pbuf_size_def;
    uint8_t rx_buffer_length_def;
    uint8_t tsu_clk;
    uint8_t axi_prot_value;
    uint8_t tx_pbuf_queue_segment_size;
    uint8_t ext_tsu_timer;
    uint8_t tx_add_fifo_if;
    uint8_t host_if_soft_select;
    uint8_t tx_pbuf_num_segments_q0;
    uint8_t tx_pbuf_num_segments_q1;
    uint8_t tx_pbuf_num_segments_q2;
    uint8_t tx_pbuf_num_segments_q3;
    uint8_t tx_pbuf_num_segments_q4;
    uint8_t tx_pbuf_num_segments_q5;
    uint8_t tx_pbuf_num_segments_q6;
    uint8_t tx_pbuf_num_segments_q7;
    uint8_t dma_addr_width;
    uint8_t tx_pbuf_num_segments_q8;
    uint8_t tx_pbuf_num_segments_q9;
    uint8_t tx_pbuf_num_segments_q10;
    uint8_t tx_pbuf_num_segments_q11;
    uint8_t tx_pbuf_num_segments_q12;
    uint8_t tx_pbuf_num_segments_q13;
    uint8_t tx_pbuf_num_segments_q14;
    uint8_t tx_pbuf_num_segments_q15;
    uint8_t num_type1_screeners;
    uint8_t num_type2_screeners;
    uint8_t num_scr2_ethtype_regs;
    uint8_t num_scr2_compare_regs;
    uint8_t axi_access_pipeline_bits;
    uint8_t pfc_multi_quantum;
    uint8_t pbuf_rsc;
    uint8_t pbuf_lso;
    uint8_t intrpt_mod;
    uint8_t hdr_split;
    uint8_t num_cb_streams;
    bool gem_vm;
    uint8_t gem_high_speed;
    uint8_t gem_usx_include_fec;
    uint8_t lockup_supported;
    uint8_t rx_pbuf_data;
    uint8_t tx_pbuf_data;
};

/**
 * "struct containing function pointers for event notification callbacks issued
 * by isr().
 * <para>Each call passes the driver's privateData (pD) pointer for instance
 * identification if necessary, and may also pass data related to the event.</para>"
*/
struct CEDI_Callbacks_s
{
    CEDI_CbPhyManComplete phyManComplete;
    CEDI_CbTxEvent txEvent;
    CEDI_CbTxError txError;
    CEDI_CbRxFrame rxFrame;
    CEDI_CbRxError rxError;
    CEDI_CbHrespError hrespError;
    CEDI_CbLpPageRx lpPageRx;
    CEDI_CbAnComplete anComplete;
    CEDI_CbLinkChange linkChange;
    CEDI_CbLockupEvent lockupEvent;
    CEDI_CbTsuEvent tsuEvent;
    CEDI_CbPauseEvent pauseEvent;
    CEDI_CbPtpPriFrameTx ptpPriFrameTx;
    CEDI_CbPtpPeerFrameTx ptpPeerFrameTx;
    CEDI_CbPtpPriFrameRx ptpPriFrameRx;
    CEDI_CbPtpPeerFrameRx ptpPeerFrameRx;
    CEDI_CbLpiStatus lpiStatus;
    CEDI_CbWolEvent wolEvent;
    CEDI_CbExtInpIntr extInpIntr;
    CEDI_CbMmslEvent mmslEvent;
    CEDI_CbFecError fecError;
    CEDI_CbSyncEvent syncEvent;
    CEDI_CbHighBitError highBitError;
};

/** Tx Descriptor defs */
struct CEDI_TxDesc_s
{
    uint32_t word[CEDI_DESC_WORD_NUM_MAX];
};

struct CEDI_TxQueue_s
{
    /** base address of descriptor ring */
    CEDI_TxDesc* bdBase;
    /** first available descriptor */
    CEDI_TxDesc* bdHead;
    /** first descriptor waiting to be freed */
    CEDI_TxDesc* bdTail;
    /** first buffer of current frame */
    CEDI_TxDesc* bd1stBuf;
    /** total number of descriptors */
    uint16_t descMax;
    /** number of descriptors that can accept buffers */
    uint16_t descFree;
    /** virt address corresponding to head BD */
    uintptr_t* vHead;
    /** end of virt address circular array */
    uintptr_t* vTail;
    /** pointer to virt addresses storage */
    uintptr_t* vAddrList;
    /** flag indicating stage of frame clean-up: set when about to clear first buffer of frame */
    uint8_t firstToFree;
    /** descriptor counter used by qTxBuf: stays at 0 until start 2nd desc of frame, then inc to 1, etc. */
    uint8_t descNum;
};

/** Rx Descriptor defs */
struct CEDI_RxDesc_s
{
    uint32_t word[CEDI_DESC_WORD_NUM_MAX];
};

struct CEDI_RxQueue_s
{
    /** start of Rx descriptor list */
    CEDI_RxDesc* rxDescStart;
    /** end-stop Rx descriptor, trails behind 'Tail'; always kept 'used' but with no buffer */
    CEDI_RxDesc* rxDescStop;
    /** next Rx descriptor to process (one after end-stop) */
    CEDI_RxDesc* rxDescTail;
    /** last descriptor in Rx list */
    CEDI_RxDesc* rxDescEnd;
    /** total number of descriptors in the list, including unused end-stop */
    uint16_t numRxDesc;
    /** number of useable buffers/descriptors in list */
    uint16_t numRxBufs;
    /** tail Rx virtual addr */
    uintptr_t* rxTailVA;
    /** end-stop Rx virtual addr, corr. to rxDescStop */
    uintptr_t* rxStopVA;
    /** end Rx virtual addr */
    uintptr_t* rxEndVA;
    /** list of buffer virtual addresses in sync with physical addresses held in descriptor lists */
    uintptr_t* rxBufVAddr;
};

/**
 * Struct contains configuration of SRAM memory distribution acors the priority queues.
 * It defines how many segments will be distributed to each queue.
*/
struct CEDI_QueueSegAlloc_s
{
    /**
     * Array with segments allocation settings.
     * Element 0 of array defines number of segments allocated to queue 0
     * element 1 of array defines number of segments allocated to queue 1, etc.
    */
    CEDI_SegmentsPerQueue* segAlloc;
    /** Number of elements in SegmentsPerQueue size. It should be the same as number of active queues. */
    uint8_t segAllocCount;
};

/**
 * Frame elimination configuration
 *
*/
struct CEDI_FrameEliminationConfig_s
{
    /** if 1 enable vector recovery algorithm $RANGE $FROM 0 $TO 1 $ */
    uint8_t enVectAlg;
    /** selects  what should be used to identify sequence number */
    CEDI_SeqNumIdentification seqNumIdentification;
    /** Offset value in bytes from the start packet delimiter to the most significant byte of the 802.1CB sequence number. (0-511) $RANGE $FROM 0 $TO 511 $TEST_SUBSET 4 $ */
    uint16_t offsetValue;
    /** first screener type 2 register used for member stream identification $RANGE $FROM 0 $TO 15 $TEST_SUBSET 4 $ */
    uint8_t smemberStream1;
    /** second screener type 2 register used for member stream identification $RANGE $FROM 0 $TO 15 $TEST_SUBSET 4 $ */
    uint8_t smemberStream2;
    /** number of significant bits of 802.1CB sequence number. (1-15) $RANGE $FROM 0 $TO 16 $TEST_SUBSET 4 $ */
    uint8_t seqNumLength;
    /** Vector recovery window, defines window size used by the vector recovery algorithm to determine whether to reject a packet. $RANGE $FROM 0 $TO 63 $TEST_SUBSET 4 $ */
    uint8_t seqRecWindow;
};

/**
 * Frame elimination tag configuration
 *
*/
struct CEDI_FrameEliminationTagConfig_s
{
    /** Ethertype value used to identify the redundancy tag */
    uint16_t redundancyTag;
    /** If 1 the redundancy tag is stripped from receive frames. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enStripRedTag;
};

/**
 * Frame elimination statistics
 *
*/
struct CEDI_FrameEliminationStats_s
{
    /** Count of sequence numbers seen without a duplicate */
    uint16_t latentErrors;
    /** Count of number of frames dropped by the vector recovery algorithm for being out of range */
    uint16_t vecRecRogue;
    /** Count of out of order sequence numbers received */
    uint16_t outOfOreder;
    /** count of number of times the sequence recovery reset timer decrements to zero */
    uint16_t seqRstCount;
};

/**
 * Configuration of preemption feature
 *
*/
struct CEDI_PreemptionConfig_s
{
    /** route all received traffic to the pmac rather than the emac when pre_active is 0 in the MMSL status. $RANGE $FROM 0 $TO 1 $ */
    uint8_t routeRxToPmac;
    /** enabling/disabling the pre-emption operation. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enPreeption;
    /** enabling/disabling the verification procedure which will determine if the link partner can support 802.3br $RANGE $FROM 0 $TO 1 $ */
    uint8_t enVerify;
    /** minimum number of bytes which the pMAC has to send before the pre-emption will be allowed. min_frag_size = (64*(1+addFragSize)-4) */
    CEDI_FragSize addFragSize;
};

/**
 * mmsl statistics
 *
*/
struct CEDI_MmslStats_s
{
    /** A count of MAC frames with reassembly errors */
    uint8_t assErrorCount;
    /** A count of received MAC frames / MAC frame fragments rejected due to unknown SMD value or arriving with an SMD-C when no frame is in progress */
    uint8_t smdErrorCount;
    /** A count of MAC frames that were successfully reassembled and delivered to MAC */
    uint32_t assOkCount;
    /** A count of the number of additional mPackets received due to preemption */
    uint32_t fragCountRx;
    /** A count of the number of additional mPackets transmitted due to preemption */
    uint32_t fragCountTx;
};

/**
 * mmsl status
 *
*/
struct CEDI_MmslStatus_s
{
    /** Set to one if pre-emption capability is active */
    uint8_t preActive;
    /** Return state of the Respond state machine */
    CEDI_RespondStatus respondStatus;
    /** Return state of the verification state machine */
    CEDI_VerifyStatus verifyStatus;
    /** MMSL interrupt flags */
    uint8_t events;
};

/**
 * Lockup detection and recovery configuration.
 *
*/
struct CEDI_LockupConfig_s
{
    /** defines a prescaler value which is the number of tx_clk periods used to scale the dmaLockupTime, txLockupTime and rxLockupTime $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $ */
    uint16_t prescaler;
    /** Time after which transmit and receive DMA lockup detection $RANGE $FROM 0 $TO 2047 $TEST_SUBSET 16 $ */
    uint16_t dmaLockupTime;
    /** The time after which the transmit  MAC lockup detection monitor will trigger. $RANGE $FROM 0 $TO 2047 $TEST_SUBSET 16 $ */
    uint16_t txLockupTime;
    /** The time after which the receive MAC lockup detection monitor will trigger. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $ */
    uint16_t rxLockupTime;
    /** Lockup recovery. If this bit is set then the module will go into a soft reset state if a lockup is detected. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enLockupRecovery;
    /** Enable the RX MAC lockup detector. Enable the monitor that detects lockups in the MAC receive path. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enRxMacLockupMon;
    /** Enable the RX DMA lockup detector. Enable the monitor that detects lockups in the receive DMA. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enRxDmaLockupMon;
    /** Enable the RX MAC lockup detector. Enable the monitor that detects lockups in the MAC transmit path. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enTxMacLockupMon;
    /** Enable the TX DMA lockup detector. Enable the monitor that detects lockups in the transmit DMA. $RANGE $FROM 0 $TO 1 $ */
    uint8_t enTxDmaLockupMon;
    /** ORed combination of bit flags DMA TX lockup timer for each queue (bit 0 - timer for queue 0, bit 15 - timer for queue 15). Set bit means that timer is enabled. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $ */
    uint16_t enTxDmaTimers;
};

/** Receive queue flushing configuration. */
struct CEDI_RxQFlushConfig_s
{
    /** If set to 1, all frames for this queue will be dropped. $RANGE $FROM 0 $TO 1 $ */
    uint8_t dropAllFrames;
    /** If set to 1, and free DMA descriptor for queue cannot be obtained, frames will be dropped. $RANGE $FROM 0 $TO 1 $ */
    uint8_t dropOnRsrcErr;
    /** Used to select queue flushing mode isung limits. */
    CEDI_RxQFlushMode rxQFlushMode;
    /** Used for receive queue flushing modes using limits. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $ */
    uint16_t maxVal;
};

/** Used to configure max receive rate for type 2 screening register. */
struct CEDI_Type2ScreenerRateLimit_s
{
    /** Interval time at which number of received bytes is compared against max_rate_val. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $ */
    uint16_t intervalTime;
    /** Maximium number of bytes screener is permitted to match in interval time. $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 16 $ */
    uint16_t maxRateVal;
};

/** AXI quality of service configuration */
struct CEDI_AxiQosConfig_s
{
    /** Determines what value to drive to the ARQOS and AWQOS outputs (4-bits each) for queue 0 descriptor accesses. $RANGE $FROM 0 $TO 15 $TEST_SUBSET 16 $ */
    uint8_t descriptorQos;
    /** Determines what value to drive to the ARQOS and AWQOS outputs (4-bits each) for queue 0 data accesses $RANGE $FROM 0 $TO 15 $TEST_SUBSET 16 $ */
    uint8_t dataQos;
};

/**
 * Information about ASF in GEM controller. There could be 0, 1 or two instances ASF componets.
 * 0 - if ASF is not included to current configuration
 * 1 - if ASF is included but gem_has_802p3_br hardware configuration option is disabled
 * 2 - if ASF is included and gem_has_802p3_br hardware configuration option is enabled
*/
struct CEDI_AsfInfo_s
{
    /** Number of ASF instances, 0 - means that there is no ASF */
    uint8_t asfCount;
    /** ASF register start addresses */
    uintptr_t asfRegBases[2];
    /** ASF hardware version */
    uint32_t asfVersion;
};

/**
 *  @}
 */

#endif	/* CEDI_STRUCTS_IF_H */
