/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */
/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
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
 * Cadence Core driver for eXpanded Serial Peripheral Interface
 **********************************************************************/
#ifndef XSPI_STRUCTS_IF_H
#define XSPI_STRUCTS_IF_H

#include "cdn_stdtypes.h"
#include "xspi_if.h"

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
/** Command error info */
struct XSPI_CommandErrorDetails_s
{
    /** Device error occured */
    bool devError;
    /** CRC error occured */
    bool crcError;
    /** Bus error occured */
    bool busError;
    /** Invalid command sequence (for PIO and STIG mode) or invalid descriptor sequence (for CDMA mode) error */
    bool invalidSeqError;
    /** DQS error occured (in R004 applicable only for FULL/FULL_ASF configuration) */
    bool dqsError;
    /** ECC correctable error occured (only for SPI NAND devices, since R003) */
    bool eccError;
};

/** Command status information */
struct XSPI_CommandStatusInfo_s
{
    /** Status value */
    uint32_t statusValue;
    /** Data read from device in STIG short read mode */
    uint8_t dataFromDevice[2];
    /** Value of ECC status returned by SPI NAND device (since R003) */
    uint8_t eccStatus;
    /** Command status */
    XSPI_CommandStatus status;
    /** Error details */
    XSPI_CommandErrorDetails errorDetails;
};

/** Command phase options */
struct XSPI_SeqCommandPhase_s
{
    /** Selecting between SDR/DDR mode for command phase */
    XSPI_CmdEdgeMode edge;
    /** Number of lines used to send command */
    XSPI_NumberOfIos ios;
    /** Command mnemonic */
    uint8_t value;
};

/** Command extension options */
struct XSPI_SeqCommandExtension_s
{
    /** Enable command extension */
    bool enable;
    /** Command mnemonic */
    uint8_t value;
};

/** Address phase options */
struct XSPI_SeqAddressPhase_s
{
    /** Selecting between SDR/DDR mode for address phase */
    XSPI_AddrEdgeMode edge;
    /** Number of lines used to send address */
    XSPI_NumberOfIos ios;
    /** Number of address cycles */
    uint8_t count;
};

/** Data phase options */
struct XSPI_SeqDataPhase_s
{
    /** Selecting between SDR/DDR mode for data phase */
    XSPI_DataEdgeMode edge;
    /** Number of lines used to send data */
    XSPI_NumberOfIos ios;
};

/** Profile 1.0 instruction layout */
struct XSPI_StigProfile10Layout_s
{
    /** Profile 1.0 Autonomic instruction type */
    XSPI_Profile10AutonomicInstrType profile10InstrType;
    /** CRC_VARIANT field */
    XSPI_CrcVariant crcVariant;
    /** Enable XIP (only for READ_XIP_PROFILE_1 instruction) */
    bool xipEnable;
    /** Shifts address byte chain by one byte towards left and fills Least Significant Byte with zeroes providing Octal DDR Address fashion required by Adesto */
    bool addrShift;
    /** Opcode phase options */
    XSPI_SeqCommandPhase instrOpcodePhase;
    /** Opcode extension options */
    XSPI_SeqCommandExtension instrOpcodeExt;
    /** Address phase options */
    XSPI_SeqAddressPhase instrAddrPhase;
    /** DATA_NO_OF_BYTES field */
    uint8_t dataNoOfBytes;
    /** ADDRESS */
    uint64_t address;
    /** DATA */
    uint8_t data[2];
};

/** Profile 2.0 instruction layout */
struct XSPI_StigProfile20Layout_s
{
    /** Profile 2.0 Autonomic instruction type */
    XSPI_Profile20AutonomicInstrType profile20InstrType;
    /** Enable timing calculation (active device max cycles count, (setP2ActiveDevMaxCycles) API) */
    bool tCmsEn;
    /** EXT_CMD_MOD_EN field */
    bool extCmdModEnable;
    /** DATA_NO_OF_BYTES field */
    uint8_t dataNoOfBytes;
    /** R/W# field. */
    XSPI_DataTransDirection rw;
    /** TARGET field */
    XSPI_TargetSpace target;
    /** BURST_TYPE field */
    XSPI_BurstType burstType;
    /** ADDR field */
    uint64_t address;
    /** DATA field */
    uint8_t data[2];
};

/** Generic command instruction layout (CMD_SEQ) (in R004 applicable only for FULL/FULL_ASF configuration) */
struct XSPI_StigGenericCmdLayout_s
{
    /** EDGE_MODE field */
    XSPI_CmdEdgeMode edgeMode;
    /** NO_OF_IOS field */
    XSPI_NumberOfIos noOfIos;
    /** NO_OF_BYTES field */
    uint8_t noOfBytes;
    /** BYTE field */
    uint8_t bytes[10];
};

/** Data sequence layout (DATA_SEQ) */
struct XSPI_StigDataSeqLayout_s
{
    /** CRC_CHUNK_SIZE field */
    XSPI_CrcChunkSize crcChunkSize;
    /** It determines if the controller requests one more status slice to check its data integrity. The expectation is that the redundant data chunk will be inverted */
    bool crcInversion;
    /** CRC_OE field */
    bool crcOe;
    /** CRC Unaligned chunk enable */
    bool crcUalChunkEn;
    /** CRC Unaligned chunk check */
    bool crcUalChunkChk;
    /** Data swap */
    bool dataSwap;
    /** Data phase options */
    XSPI_SeqDataPhase instrDataPhase;
    /** DIR field */
    XSPI_DataTransDirection dir;
    /** DATA_PER_ADDR field */
    XSPI_DataPerAddress dataPerAddress;
    /** NO_OF_DUMMY field */
    uint8_t noOfDummy;
    /** HF_READ_BOUND_EN field */
    bool hfReadBoundEnable;
    /** DATA_NO_OF_BYTES field */
    uint32_t dataNoOfBytes;
    /** Read mode based on number of bytes to read */
    XSPI_ReadDataMode rdMode;
    /** Slave DMA buffer pointer */
    uintptr_t sysMemPtr;
};

/** STIG structure with one instruction sequence */
struct XSPI_StigInstruction_s
{
    /** STIG instruction layout type */
    XSPI_StigInstructionType stigInstrType;
    /** Profile 1.0 instruction */
    XSPI_StigProfile10Layout profile10Instr;
    /** Profile 2.0 instruction */
    XSPI_StigProfile20Layout profile20Instr;
    /** Generic instruction (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_StigGenericCmdLayout genCmdInstr;
};

/** STIG command structure with minicontroller instruction sequences */
struct XSPI_StigCommand_s
{
    /** Points to chain of minicontroller instruction sequences */
    XSPI_StigInstruction* instructionChain;
    /** Length of the instruction chain */
    uint8_t instrChainLength;
    /** Bank number field. Selects memory device on which sequence needs to be executed */
    uint8_t commBankSelect;
    /** CRC_EN field common for all instructions */
    bool commCrcEnable;
    /** Data sequence instruction. This must be the last instruction in the instruction chain */
    XSPI_StigDataSeqLayout* dataSeqInstr;
    /** Command status information */
    XSPI_CommandStatusInfo statusInfo;
};

/** DMA config (common for both Master and Slave interface) */
struct XSPI_DmaConfig_s
{
    /** DMA word size (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_DmaWordSize wordSize;
    /** If this bit is set then ERROR response will be returned if host tries to access unprepared Slave DMA interface. If this bit will be cleared the OK response is returned */
    bool sdmaErrorResp;
    /** Outstanding transaction enable. It only applies to the master interface, the slave interface will ignore this bit and will accept all incoming transactions (in R004 applicable only for FULL/FULL_ASF configuration) */
    bool otEnable;
    /** Sets the burst used by data DMA for transferring data to/from flash device. The maximum burst size can be calculated as burst_sel + 1 (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t burstSelect;
};

/** XIP mode bits */
struct XSPI_XipModeBitsConfig_s
{
    /** XIP mode enable for selected memory bank. Each bit corresponds to one memory bank. */
    uint8_t xipEnableBanks;
    /** XIP disable bits */
    uint8_t xipDisBits;
    /** XIP enable bits */
    uint8_t xipEnBits;
};

/** Global command parameters for CDMA, PIO and DIRECT work mode (applies only to SPI NAND devices) (Since R003) */
struct XSPI_SpiNandGlobCmdParams_s
{
    /** Number of planes in SPI NAND device */
    XSPI_SpiNandPlaneCount planeCnt;
    /** Number of pages per block */
    uint8_t pagesPerBlock;
    /** Width of COLUMN address */
    XSPI_SpiNandCaSize pageCaSize;
    /** Determines extended page size area (spare area size) */
    uint16_t extPageSize;
};

/** Global command parameters for CMDA, PIO and DIRECT work modes */
struct XSPI_GlobalCommandParameters_s
{
    /** Selects profile 1.0 or profile 2.0 sequences */
    XSPI_SequenceType seqType;
    /** Indicates how many bytes of data is assigned to the single Flash Memory addres (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    XSPI_DataPerAddress dataPerAddress;
    /** Enables reverse byte order */
    bool dataSwap;
    /** Enables checking correctness of CRC unaligned chunk from Flash device. */
    bool crcUalChunkChk;
    /** Enables taking into consideration the command address to determine after how many bytes CRC data slice expected to be returned from device */
    bool crcUalChunkEn;
    /** Number of bytes after which CRC occurs */
    XSPI_CrcChunkSize crcChunkSize;
    /** If set, the controller expects the xSPI device to toggle CRC data on both SPI clock edges in CRC->CRC# sequence */
    bool crcToogleData;
    /** Selecting of CRC variant (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    XSPI_CrcVariant crcVariant;
    /** If set, dynamic CRC calculation is enabled */
    bool crcDynamicCalcEnable;
    /** Determines page size of device being used for PROGRAM */
    XSPI_ProgramPageSize pgmPageSize;
    /** Determines page size of device being used for READ */
    XSPI_ReadPageSize rdPageSize;
};

/** Direct mode command configuration */
struct XSPI_DirectCmd_s
{
    /** Transfer size in bytes for read or write data transfer */
    uint32_t transferSize;
    /** xSPI transfer address */
    uint32_t transferAddr;
    /** Read or Write direction */
    XSPI_DataTransDirection direction;
    /** Slave DMA buffer pointer */
    uintptr_t sysMemPtr;
};

/** Configuration for direct work mode */
struct XSPI_DirectModeConfig_s
{
    /** This mask is used for anding bits [44:32] of the system address for read/write transfers in Legacy Hyperflash and xSPI Profile 2.0 mode */
    uint32_t dacAddrMask;
    /** Enables Slave Data interface address rempping. When set to 1, the incoming Slave Data Interface address will be adopted and sent to the Flash device */
    bool remapAddrEn;
    /** If set, disable auto-polling of memory device */
    bool disableAutoPoll;
    /** If set, disable automatic issuing of WEL instruction before write operation (involves profile 1.0 sequence type) */
    bool disableAutoWelInstr;
    /** Disable XIP with modebits */
    bool disXipMb;
    /** Enable XIP with modebits */
    bool enXipMb;
    /** Target device */
    uint8_t bankSelect;
    /** Remapping of incoming address on Slave Data Interface to a different address used by the Flash device (below R003 this field is 32 bits width) */
    uint64_t remapAddrVal;
};

/** Profile 1.0 PROGRAM sequence config */
struct XSPI_ProgramSeqP1Config_s
{
    /** Data phase options */
    XSPI_SeqDataPhase progSeqData;
    /** Address phase options */
    XSPI_SeqAddressPhase progSeqAddr;
    /** Command phase options */
    XSPI_SeqCommandPhase progSeqCmd;
    /** Command extension options */
    XSPI_SeqCommandExtension progSeqCmdExt;
};

/** Profile 2.0 PROGRAM sequence config */
struct XSPI_ProgramSeqP2Config_s
{
    /** Number of latency cycles for PROFILE 2 - HR only. Setting this bit to 0 will disable latency cycles. This value should be set to 'N-1', where 'N' is the number of latency clock cycles expected by the memory device. */
    uint8_t progSeqLatCount;
    /** Determines command extension variant for Legacy HyperFlash and xSPI profile 2.0 instruction */
    bool progSeqExtCmdMod;
    /** Target space for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    XSPI_TargetSpace progSeqTarget;
    /** Burst type for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    XSPI_BurstType progSeqBurstType;
};

/** Profile 1.0 READ sequence config */
struct XSPI_ReadSeqP1Config_s
{
    /** Number of dummy cycles (if 0 - disabled) */
    uint8_t readSeqDummyCnt;
    /** Data phase options */
    XSPI_SeqDataPhase readSeqData;
    /** Address phase options */
    XSPI_SeqAddressPhase readSeqAddr;
    /** Command phase options */
    XSPI_SeqCommandPhase readSeqCmd;
    /** If set to 1, mode bits are sent following the address bytes */
    bool readSeqMbEn;
    /** Number of dummy cycles (if 0 - disabled). Used when sending mode bits is enabled in ACMD or Direct work modes. */
    uint8_t readSeqMbDummyCnt;
    /** Command extension options */
    XSPI_SeqCommandExtension readSeqCmdExt;
    /** This bit changes behavior of the Read sequence to utilize the Read Page Cache Random/Read Page Cache Random Last commands. (not used in DIRECT mode) (Since R003) (in R004 applicable only for FULL/FULL_ASF configuration) */
    bool cacheRandomReadEn;
};

/** Profile 2.0 READ sequence config */
struct XSPI_ReadSeqP2Config_s
{
    /** Number of latency cycles */
    uint8_t readSeqLatencyCnt;
    /** Enabled calculating read transaction crossing page boundary */
    bool readSeqHfBoundEn;
    /** Determines command extension variant for Legacy HyperFlash and xSPI profile 2.0 instruction */
    bool readSeqExtCmdMod;
    /** Burst type for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    XSPI_BurstType readSeqBurstType;
    /** Target space for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    XSPI_TargetSpace readSeqTarget;
};

/** Structure to configure write enable sequence */
struct XSPI_WelSeqConfig_s
{
    /** Command extension options */
    XSPI_SeqCommandExtension welSeqCmdExt;
    /** Command phase options */
    XSPI_SeqCommandPhase welSeqCmd;
};

/** Profile 1.0 sequence config */
struct XSPI_StatSeqP1Config_s
{
    /** Data phase options */
    XSPI_SeqDataPhase statSeqData;
    /** Selecting SDR/DDR mode for address phase */
    XSPI_AddrEdgeMode statSeqAddrEdge;
    /** Number of lines used to send address */
    XSPI_NumberOfIos statSeqAddrIos;
    /** Number of address bytes for all status sequences */
    XSPI_StatSeqAddrCount statSeqAddrCnt;
    /** Extended command enable */
    bool statSeqCmdExtEn;
    /** Selecting SDR/DDR mode for command phase */
    XSPI_CmdEdgeMode statSeqCmdEdge;
    /** Number of lines used to send command */
    XSPI_NumberOfIos statSeqCmdIos;
    /** Enables address phase for checking fail status after ERASE operation (in R004 applicable only for FULL/FULL_ASF configuration) */
    bool statSeqErsFailAddrEn;
    /** Number of dummy clock cycles utilized to check fail status after ERASE operation (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t statSeqErsFailDummyCnt;
    /** Enables address phase for checking fail status after PROGRAM operation */
    bool statSeqProgFailAddrEn;
    /** Number of dummy clock cycles utilized to check fail status after PROGRAM operation */
    uint8_t statSeqProgFailDummyCnt;
    /** Enables address phase for checking ready/busy status after after ERASE operation */
    bool statSeqDevRdyAddrEn;
    /** Number of dummy clock cycles utilized to check ready/busy status after PROGRAM/ERASE and SOFT RESET/READ (only for SPI NAND) operation */
    uint8_t statSeqDevRdyDummyCnt;
    /** Command mnemonic for PROGRAM fail checking */
    uint8_t statSeqProgFailCmdVal;
    /** Command mnemonic for ERASE fail checking */
    uint8_t statSeqErsFailCmdVal;
    /** Command mnemonic for ERASE ready/busy checking */
    uint8_t statSeqDevRdyCmdVal;
    /** Command extension mnemonic for PROGRAM fail checking */
    uint8_t statSeqProgFailCmdExtVal;
    /** Command extension mnemonic for ERASE fail checking (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t statSeqErsFailCmdExtVal;
    /** Command extension mnemonic for ERASE ready/busy checking */
    uint8_t statSeqDevRdyCmdExtVal;
};

/** Profile 2.0 ISEQ_STAT sequence config */
struct XSPI_StatSeqP2Config_s
{
    /** Number of latency cycles (0-15) between CA and STATUS reading */
    uint8_t statSeqLatencyCnt;
    /** Determines xSPI profile 2.0 command extension variant */
    bool statSeqExtCmdMod;
};

/** Common sequence config */
struct XSPI_CommStatSeqConfig_s
{
    /** Enables checking fail status after PROGRAM operation */
    bool statSeqProgFailEn;
    /** Number of status bits which will be read (8b or 16b) to check device fail status after PROGRAM command (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_StatStatusWordSize statSeqProgFailSize;
    /** Polarity of fail status information after the PROGRAM command */
    XSPI_StatPolarity statSeqProgFailVal;
    /** Position of bit which provide fail status information after the PROGRAM command */
    uint8_t statSeqProgFailIdx;
    /** Enables checking fail status after ERASE operation (in R004 applicable only for FULL/FULL_ASF configuration) */
    bool statSeqErsFailEn;
    /** Number of status bits which will be read (8b or 16b) to check device fail status after ERASE command (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_StatStatusWordSize statSeqErsFailSize;
    /** Polarity of fail status information after the ERASE command (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_StatPolarity statSeqErsFailVal;
    /** Position of bit which provide the fail status information after the ERASE command (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t statSeqErsFailIdx;
    /** Enables checking ready/busy status after PROGRAM operation (Since R004) */
    bool statSeqDevRdyEn;
    /** Number of status bits which will be read (8b or 16b) to check device ready status after ERASE command (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_StatStatusWordSize statSeqDevRdySize;
    /** Polarity of ready/busy status information after the ERASE command */
    XSPI_StatPolarity statSeqDevRdyVal;
    /** Position of bit which provide the ready/busy status inforamtion after ERASE command */
    uint8_t statSeqDevRdyIdx;
    /** Value of address utilized to check rdy/busy status after PROGRAM operation */
    uint32_t statSeqDevRdyAddr;
    /** Value of address utilized to check fail status after PROGRAM operation */
    uint32_t statSeqProgFailAddr;
    /** Value of address utilized to check fail status after ERASE operation (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint32_t statSeqErsFailAddr;
};

/** Status sequence settings for SPI NAND devices (Since R003) */
struct XSPI_StatSeqSpiNandConfig_s
{
    /** Enables checking ECC status after READ PAGE operation */
    bool statSeqEccFailEn;
    /** Value which will be compared with selected status bit in order to detect is the device in ready state after the Read Page Cache Random operation (CRBSY bit). This field is not used in DIRECT work mode (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_StatPolarity statSeqCRdyVal;
    /** This field determine which bit of the status word contains the Cache Read Busy (CRBSY) bit information for the SPI NAND Read Page Cache Random operation. This field is not used in DIRECT work mode (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t statSeqCRdyIdx;
    /** Value which will be compared with status word masked by the stat_seq_ecc_fail_mask field in order to detect if the device returned the correctable ECC error during SPI NAND Page Read operation. This method allows to detect single range of correctable errors returned by the XSPI device */
    uint8_t statSeqEccCorrVal;
    /** Value which will be compared with status word masked by the stat_seq_ecc_fail_mask field in order to detect if the device returned the uncorrectable ECC error during SPI NAND Page Read operation */
    uint8_t statSeqEccFailVal;
    /** Mask utilized to select which bits of status word carries the ECC status. It applies for both uncorrectable and correctable error checking */
    uint8_t statSeqEccFailMask;
};

/** Controller version info */
struct XSPI_VersionInfo_s
{
    /** Minor revision number */
    uint8_t minorRevNumber;
    /** Controller revision number */
    uint8_t majorRevNumber;
};

/** Controller supported features info */
struct XSPI_CtrlFeaturesInfo_s
{
    /** Maximum number of banks supported by hardware */
    uint8_t maxBankNum;
    /** DMA data width */
    XSPI_DmaDataWidth dmaDataWidth;
    /** DMA address width */
    XSPI_DmaAddrWidth dmaAddrWidth;
    /** Boot feature present */
    bool bootAvailable;
    /** Number of threads available in controller (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t maxThreadNum;
    /** Denotes if ASF module is present in xSPI */
    bool asfAvailable;
};

/** Reset bank settings */
struct XSPI_ResetDeviceConfig_s
{
    /** Each bit selects the corresponding bank for hardware reset. This field takes effect for banks which use HARDWARE_RESET_OPTION_RESET_PIN option. */
    uint8_t bankSelectMask;
    /** Denotes reset type. When HARDWARE_RESET_OPTION_DQ3_PIN option is selected, bankSelectMask field will not be considered and all the banks connected using DQ3 reset pin will be reset. */
    XSPI_HardwareResetOption hwResetType;
};

/** Device relative delays settings */
struct XSPI_DeviceRelativeDelays_s
{
    /** CSDA_MIN  Minimum Chip Select de-assertion timing */
    uint8_t csdaMinDelay;
    /** CSEOT  Chip Select End Of Transfer. It allows to improve last active clock edge to CS de-assertion device timing */
    uint8_t cseotDelay;
    /** CSSOT  Chip Select Start Of Transfer. It allows to improve CS de-assertion device timing to first active clock edge */
    uint8_t cssotDelay;
};

/** JEDEC RESET timing config (since R003) */
struct XSPI_JedecResetTimingConfig_s
{
    /** Defines how many xspi_clk cycles constitute tCSL timing of JEDEC Reset Instruction. */
    uint8_t tCSL;
    /** Defines how many xspi_clk cycles constitute tCSH timing of JEDEC Reset Instruction. */
    uint8_t tCSH;
};

/** Stig mode SDMA information structure */
struct XSPI_StigSdmaIrqInfo_s
{
    /** Slave DMA direction */
    XSPI_DataTransDirection direction;
    /** Slave DMA transaction buffer */
    uintptr_t stigSdmaBuff;
    /** Slave DMA transaction transfer size */
    uint32_t transferSize;
};

/** Direct mode SDMA information structure */
struct XSPI_DirectSdmaTransInfo_s
{
    /** Slave DMA direction */
    XSPI_DataTransDirection direction;
    /** Slave DMA transaction buffer */
    uintptr_t directSdmaBuff;
    /** Slave DMA transaction transfer size */
    uint32_t transferSize;
    /** xSPI transfer address */
    uint32_t transferAddr;
};

/** ACMD mode SDMA information structure (in R004 applicable only for FULL/FULL_ASF configuration) */
struct XSPI_AcmdSdmaIrqInfo_s
{
    /** Thread number associated with transferred data block */
    uint8_t thread;
    /** Slave DMA direction */
    XSPI_DataTransDirection direction;
    /** Slave DMA transaction buffer */
    uint64_t acmdSdmaBuff;
    /** Slave DMA transaction transfer size */
    uint32_t transferSize;
};

/** Slave DMA callbacks structure */
struct XSPI_SdmaCallbacks_s
{
    /** Slave DMA not allowed access error */
    XSPI_CbSdmaError sdmaErrorHandler;
    /** Slave DMA trigger condition is met in STIG mode */
    XSPI_CbStigSdmaTransaction stigSdmaTransactionHandler;
    /** Slave DMA trigger condition is met in ACMD mode (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_CbAcmdSdmaTransaction acmdSdmaTransactionHandler;
    /** Slave DMA transfer callback in Direct mode */
    XSPI_CbDirectSdmaTransaction directSdmaTransactionHandler;
};

/** Direct mode errors callbacks structure */
struct XSPI_DirectErrorCallbacks_s
{
    /** Invalid command sequence detected error */
    XSPI_CbDirInvalidCommandSeq dirInvalidCommandSeqHandler;
    /** DQS underrun or overflow (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_CbDirDqsError dirDqsErrorHandler;
    /** CRC error after read transaction */
    XSPI_CbDirCrcError dirCrcErrorHandler;
    /** Correctable ECC error occured (Since R003) */
    XSPI_CbDirCorrEccError dirCorrEccErrorHandler;
    /** Uncorrectable ECC error occured (Since R003) */
    XSPI_CbDirUncorrEccError dirUncorrEccErrorHandler;
};

/** Open drain pins callbacks (Since R003) */
struct XSPI_OpenDrainCallbacks_s
{
    /** State changed occured on xspi_dfi_gp_open_drain[3] pin (Since R003) */
    XSPI_CbOpenDrainStateChanged openDrainPin3ChangedHandler;
    /** State changed occured on xspi_dfi_gp_open_drain[2] pin (Since R003) */
    XSPI_CbOpenDrainStateChanged openDrainPin2ChangedHandler;
    /** State changed occured on xspi_dfi_gp_open_drain[1] pin (Since R003) */
    XSPI_CbOpenDrainStateChanged openDrainPin1ChangedHandler;
    /** State changed occured on xspi_dfi_gp_open_drain[0] pin (Since R003) */
    XSPI_CbOpenDrainStateChanged openDrainPin0ChangedHandler;
};

/** Controller callbacks structure */
struct XSPI_Callbacks_s
{
    /** Slave DMA callbacks */
    XSPI_SdmaCallbacks sdmaCb;
    /** Direct mode error callbacks */
    XSPI_DirectErrorCallbacks directErrorCb;
    /** ACMD mode command completed callback (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_CbAcmdCmdComplete acmdCmdCompleteHandler;
    /** Instruction in glued chain is completed */
    XSPI_CbStigDone stigDoneHandler;
    /** Ignored command detected */
    XSPI_CbCommandIgnored commandIgnoredHandler;
    /** Master Data DMA Target error. Will be set if Master Data DMA engine module detects system bus error (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_CbMasterDataDMAError masterDataDMAErrorHandler;
    /** Command DMA Target error. Will be set if Auto Command engine detects system bus error (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_CbCommandDMAError commandDMAErrorHandler;
    /** Occurs, when controller is in IDLE state */
    XSPI_CbIdleStateDetected idleStateDetHandler;
    /** Open drain pins callbacks (Since R003) */
    XSPI_OpenDrainCallbacks openDrainCallbacks;
};

/** xSPI Controller configuration */
struct XSPI_Config_s
{
    /** Base address of xSPI registers */
    volatile XSPI_Regs* regsBase;
    /** Max number of CDMA commands allocated in memory (in R004 applicable only for FULL/FULL_ASF configuration) */
    uint8_t cdmaCmdsMaxNum;
    /** Base address of CDMA commands descriptors (in R004 applicable only for FULL/FULL_ASF configuration) */
    uintptr_t cdmaCmdsDescBase;
    /** Base address of private data structure */
    uintptr_t privateDataBase;
    /** Controller callbacks */
    XSPI_Callbacks callbacks;
    /** Read-only flag denotes if IOT configuration detected */
    bool xSpiIot;
    /** Read-only number of threads */
    uint8_t maxThreadNum;
};

/** xSPI driver memory requirements */
struct XSPI_SysReq_s
{
    /** CDMA commands descritprs total size (in R004 applicable only for FULL/FULL_ASF configuration) */
    size_t cdmaCmdsDescTotalSize;
    /** Private data structure size */
    size_t privateDataSize;
};

/** Auto command parameters */
struct XSPI_AcmdCommandParameters_s
{
    /** Auto command type */
    XSPI_AcmdCommandType cmdType;
    /** Auto command DMA type */
    XSPI_AcmdDmaSelect dmaSelect;
    /** Target bank */
    uint8_t bankSelect;
    /** xSPI address (since R003, field is split into ROW and COLUMN addresses for SPI NAND devices) */
    uint64_t xSpiAddr;
    /** System memory pointer */
    uintptr_t sysMemPtr;
    /** Callback after command is processed */
    bool raiseCmdCompleteCb;
    /** Disable XIP with mode bits (only for READ commands) */
    bool disXipMb;
    /** Enable XIP with mode bits (only for READ commands) */
    bool enXipMb;
    /** Command count */
    uint32_t cmdCount;
};

/** CDMA command */
struct XSPI_CdmaCommand_s
{
    /** CDMA command parameters */
    XSPI_AcmdCommandParameters params;
    /** Denotes if controller should use existing xSpiAddr field instead from current command */
    bool ignoreXSpiAddr;
    /** Denotes if controller should use existing sysMemPtr field instead from current command */
    bool ignoreSysMemPtr;
    /** Command status information */
    XSPI_CommandStatusInfo statusInfo;
};

/** CDMA command chain status */
struct XSPI_CdmaChainStatus_s
{
    /** CDMA command chain status completed */
    bool isCompleted;
    /** CDMA command chain status failed */
    bool isFailed;
    /** Index of failed CDMA command */
    uint8_t failCmdIndex;
};

/** CDMA command chain */
struct XSPI_CdmaCommandChain_s
{
    /** CDMA command chain length */
    uint8_t chainLength;
    /** Thread number */
    uint8_t thread;
    /** Command chain pointer */
    XSPI_CdmaCommand* chain;
    /** Status of CDMA commands in a chain */
    XSPI_CdmaChainStatus chainStatus;
};

/** PIO command */
struct XSPI_PioCommand_s
{
    /** Command parameters */
    XSPI_AcmdCommandParameters params;
    /** Command status information */
    XSPI_CommandStatusInfo statusInfo;
};

/** Latest boot status */
struct XSPI_LatestBootStatus_s
{
    /** Denotes if boot process failed due to bus interface receiving an error response from target */
    bool busError;
    /** Denotes if boot process failed due to CRC error on xSPI interface (since R003) */
    bool crcError;
    /** Denotes if boot process failed due to DQS error on xSPI interface (since R003) */
    bool dqsError;
};

/** Controller polling config */
struct XSPI_PollingConfig_s
{
    /** Number of system clock cycles after issue of erase/write operation before the controller starts to check device status (ready/busy and fail/pass) */
    uint16_t longPolling;
    /** Number of minimum system clocks after long polling delay before the controller starts to poll for status if first status poll attempt returned information that controller is busy */
    uint16_t shortPolling;
};

/** Device discovery settings for Profile 1.0 memories */
struct XSPI_DevDiscParamsP1_s
{
    /** Enable discovery 4-bit addressing */
    bool enable4bAddr;
    /** Device Discovery number of dummy clock cycles */
    XSPI_DeviceDiscoveryDummyCnt discoveryDummyCnt;
    /** Discovery command type mode enable */
    XSPI_DeviceDiscoveryCmdType cmdType;
    /** Enable discovery extended opcode */
    bool enableExtendOpCode;
    /** Device discovery extended opcode value */
    XSPI_DeviceDiscoveryExtOpVal extendOpCodeVal;
};

/** Device discovery settings for Hyperflash and Profile 2.0 memories */
struct XSPI_DevDiscParamsP2_s
{
    /** Enables detection of inter-pages crossing for hyperflash memories. */
    bool hfBoundEn;
    /** Number of latency clock cycles */
    uint8_t latencyCnt;
};

/** Device discovery settings */
struct XSPI_DeviceDiscoveryConfig_s
{
    /** Discovery bank select */
    uint8_t bankSelect;
    /** Device discovery mode */
    XSPI_DeviceDiscoveryLines numLines;
    /** Device discovery request type */
    XSPI_DeviceDiscoveryReqType reqType;
    /** Device discovery parameters for Profile 1.0 memories */
    XSPI_DevDiscParamsP1 p1Config;
    /** Device discovery parameters for Hyperflash and Profile 2.0 memories */
    XSPI_DevDiscParamsP2 p2Config;
};

/** RESET sequence config (profile 1.0) */
struct XSPI_ResetSeqConfig_s
{
    /** Selecting SDR/DDR mode for both command phases */
    XSPI_CmdEdgeMode rstSeqCmdEdge;
    /** Number of lines used to send both command phases */
    XSPI_NumberOfIos rstSeqCmdIos;
    /** Enable for optional CMD0 phase */
    bool rstSeqCmd0En;
    /** Menomonic for CMD1 phase */
    uint8_t rstSeqCmd1Val;
    /** Mnemonic for CMD0 phase */
    uint8_t rstSeqCmd0Val;
    /** Command 0 extension options */
    XSPI_SeqCommandExtension rstSeqCmd0Ext;
    /** Command 1 extension options */
    XSPI_SeqCommandExtension rstSeqCmd1Ext;
    /** Data phase options */
    XSPI_SeqDataPhase rstSeqData;
    /** Enable sending data phase (confirmation byte) */
    bool rstSeqDataEn;
    /** Confirmation byte value */
    uint8_t rstSeqDataVal;
    /** Value of tPOR timing specified in a number of system clock cycles (applicable for SPI NAND devices) (since R003) */
    uint32_t tPORTiming;
};

/** ERASE_SECTOR sequence config (profile 1.0) Note - Every ERASE sequence utilize the internal WE (Write Enable) and STAT (Check Status) sequences. They both must be configured correctly before invoking the ERASE sequence */
struct XSPI_EraseSecSeqConfig_s
{
    /** Address phase options */
    XSPI_SeqAddressPhase erssSeqAddr;
    /** Command extension options */
    XSPI_SeqCommandExtension erssSeqCmdExt;
    /** Command phase options */
    XSPI_SeqCommandPhase erssSeqCmd;
    /** Sector size */
    XSPI_EraseSeqSectorSize erssSeqSecSize;
};

/** CHIP_ERASE sequence config (profile 1.0) Note - Every ERASE sequence utilize the internal WE (Write Enable) and STAT (Check Status) sequences. They both must be configured correctly before invoking the ERASE sequence */
struct XSPI_ChipEraseSeqConfig_s
{
    /** Command extension options */
    XSPI_SeqCommandExtension ersaSeqCmdExt;
    /** Command phase options */
    XSPI_SeqCommandPhase ersaSeqCmd;
};

/** HyperFlash decode address settings (takes reserved area into account) */
struct XSPI_HyperFlashOffsetConfig_s
{
    /** Offset size of reserved area in command format */
    uint8_t offsetSize;
    /** Starting index of reserved area in command format */
    uint8_t offsetIndex;
};

/** PHY configuration */
struct XSPI_PhyConfig_s
{
    /** Signal to resynchronize the DLLs and read and write FIFO pointers(dfi_ctrlupd_req). To send update request set this field to high and wait until this field is low. This field should be used only when resyncCount field is zero */
    uint8_t dfiCtrlUpdtReq;
    /** This field defines the time interval to send an update to the PHY to resynchronize the slave DLL values with that of the master DLL and to also resynchronize the read and write FIFO pointers in the read path */
    uint32_t resyncCount;
    /** Selects positive or negative edge of phy sampling clock from which controller propagates data while in SDR mode. */
    XSPI_SdrActiveEdge sdrActiveEdge;
    /** This field should be set when flash device issues data on negative edge of flash clock and returns them with DQS and PHY is configured to sample data in DQS mode. */
    uint8_t dqsLastDataDropEn;
    /** This field defines the number of Minicontroller clock cycles (xspi_clk) for which the DLL update request (dfi_ctrlupd_req) has to be asserted to resynchronize the DLLs and read and write FIFO pointers */
    uint8_t resyncHighWaitCount;
    /** This field defines the wait time (in terms of Minicontroller clock cycles (xspi_clk)) between the deassertion of the DLL update request (dfi_ctrlupd_req) and resuming traffic to the PHY */
    uint8_t resyncIdleCount;
};

/**
 *  @}
 */

#endif	/* XSPI_STRUCTS_IF_H */
