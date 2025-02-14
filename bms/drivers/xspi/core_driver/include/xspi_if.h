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

#ifndef XSPI_IF_H
#define XSPI_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "xspi_regs.h"
#include "xspi_regs_macros.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** Operation is complete */
#define	XSPI_CMD_STAT_COMPLETED 0x8000U

/** Operation failed */
#define	XSPI_CMD_STAT_FAILED 0x4000U

/** When set it informs that the controller detected a crc error */
#define	XSPI_CMD_STAT_CRC_ERROR 0x0004U

/** When set it informs that the controller got an error response on the system DMA interface */
#define	XSPI_CMD_STAT_BUS_ERROR 0x0002U

/** This flag denotes that an invalid command sequence has been detected */
#define	XSPI_CMD_STAT_INVALID_SEQ_ERROR 0x0001U

/** ECC correctable error was detected during page read, field valid only for SPI NAND devices (Since R003) */
#define	XSPI_CMD_STAT_ECC_CORR_ERROR 0x0020U

/** Device error was detected during read status operation */
#define	XSPI_CMD_STAT_DEVICE_ERROR 0x0010U

/** This bit is set when uncorrectable ECC error occured in DIRECT work mode (Since R003) */
#define	XSPI_EVENT_DWM_UNCORR_ECC_ERROR 0x10000000U

/** This bit is set when correctable ECC error occured in DIRECT work mode (Since R003) */
#define	XSPI_EVENT_DWM_CORR_ECC_ERROR 0x08000000U

/** This bit is set when an invalid command sequence has been detected in DIRECT work mode */
#define	XSPI_EVENT_DWM_CMD_ERROR 0x04000000U

/** This bit is set when Minicontroller returns CRC error after read transaction in DIRECT work mode */
#define	XSPI_EVENT_DWM_CRC_ERROR 0x01000000U

/** This bit is set when last instruction in glued chain is completed */
#define	XSPI_EVENT_STIG_DONE 0x00800000U

/** Enables interrupt when not allowed access to the Slave DMA interface is detected */
#define	XSPI_EVENT_SDMA_ERROR 0x00400000U

/** Enables interrupt when trigger condition for the Slave DMA is met */
#define	XSPI_EVENT_SDMA_TRIGGER 0x00200000U

/** Interrupt enable for detecting of ignored command */
#define	XSPI_EVENT_COMMAND_IGNORED 0x00100000U

/** Interrupt enable for detecting Controller IDLE */
#define	XSPI_EVENT_IDLE_STATE 0x00010000U

/** Interrupt enable for detecting status change on xspi_dfi_gp_open_drain[3] input pin (since R003) */
#define	XSPI_EVENT_OPEN_DRAIN_3_PIN_CHANGED 0x00008000U

/** Interrupt enable for detecting status change on xspi_dfi_gp_open_drain[2] input pin (since R003) */
#define	XSPI_EVENT_OPEN_DRAIN_2_PIN_CHANGED 0x00004000U

/** Interrupt enable for detecting status change on xspi_dfi_gp_open_drain[1] input pin (since R003) */
#define	XSPI_EVENT_OPEN_DRAIN_1_PIN_CHANGED 0x00002000U

/** Interrupt enable for detecting status change on xspi_dfi_gp_open_drain[0] input pin (since R003) */
#define	XSPI_EVENT_OPEN_DRAIN_0_PIN_CHANGED 0x00001000U

/** Incorrect number of DQS pulses detected */
#define	XSPI_CMD_STAT_DQS_ERROR 0x0008U

/** This bit is set when Minicontroller returns DQS underrun or overflow flag after read transaction in DIRECT work mode */
#define	XSPI_EVENT_DWM_DQS_ERROR 0x02000000U

/** Interrupt enable for detecting Data DMA Master target error */
#define	XSPI_EVENT_DMA_MASTER_TGT_ERROR 0x00040000U

/** Interrupt enable for detecting Auto CMD Engine target error */
#define	XSPI_EVENT_ACMD_TARGET_ERROR 0x00020000U

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
 * Forward declarations
 **********************************************************************/
typedef struct XSPI_CommandErrorDetails_s XSPI_CommandErrorDetails;
typedef struct XSPI_CommandStatusInfo_s XSPI_CommandStatusInfo;
typedef struct XSPI_SeqCommandPhase_s XSPI_SeqCommandPhase;
typedef struct XSPI_SeqCommandExtension_s XSPI_SeqCommandExtension;
typedef struct XSPI_SeqAddressPhase_s XSPI_SeqAddressPhase;
typedef struct XSPI_SeqDataPhase_s XSPI_SeqDataPhase;
typedef struct XSPI_StigProfile10Layout_s XSPI_StigProfile10Layout;
typedef struct XSPI_StigProfile20Layout_s XSPI_StigProfile20Layout;
typedef struct XSPI_StigGenericCmdLayout_s XSPI_StigGenericCmdLayout;
typedef struct XSPI_StigDataSeqLayout_s XSPI_StigDataSeqLayout;
typedef struct XSPI_StigInstruction_s XSPI_StigInstruction;
typedef struct XSPI_StigCommand_s XSPI_StigCommand;
typedef struct XSPI_DmaConfig_s XSPI_DmaConfig;
typedef struct XSPI_XipModeBitsConfig_s XSPI_XipModeBitsConfig;
typedef struct XSPI_SpiNandGlobCmdParams_s XSPI_SpiNandGlobCmdParams;
typedef struct XSPI_GlobalCommandParameters_s XSPI_GlobalCommandParameters;
typedef struct XSPI_DirectCmd_s XSPI_DirectCmd;
typedef struct XSPI_DirectModeConfig_s XSPI_DirectModeConfig;
typedef struct XSPI_ProgramSeqP1Config_s XSPI_ProgramSeqP1Config;
typedef struct XSPI_ProgramSeqP2Config_s XSPI_ProgramSeqP2Config;
typedef struct XSPI_ReadSeqP1Config_s XSPI_ReadSeqP1Config;
typedef struct XSPI_ReadSeqP2Config_s XSPI_ReadSeqP2Config;
typedef struct XSPI_WelSeqConfig_s XSPI_WelSeqConfig;
typedef struct XSPI_StatSeqP1Config_s XSPI_StatSeqP1Config;
typedef struct XSPI_StatSeqP2Config_s XSPI_StatSeqP2Config;
typedef struct XSPI_CommStatSeqConfig_s XSPI_CommStatSeqConfig;
typedef struct XSPI_StatSeqSpiNandConfig_s XSPI_StatSeqSpiNandConfig;
typedef struct XSPI_VersionInfo_s XSPI_VersionInfo;
typedef struct XSPI_CtrlFeaturesInfo_s XSPI_CtrlFeaturesInfo;
typedef struct XSPI_ResetDeviceConfig_s XSPI_ResetDeviceConfig;
typedef struct XSPI_DeviceRelativeDelays_s XSPI_DeviceRelativeDelays;
typedef struct XSPI_JedecResetTimingConfig_s XSPI_JedecResetTimingConfig;
typedef struct XSPI_StigSdmaIrqInfo_s XSPI_StigSdmaIrqInfo;
typedef struct XSPI_DirectSdmaTransInfo_s XSPI_DirectSdmaTransInfo;
typedef struct XSPI_AcmdSdmaIrqInfo_s XSPI_AcmdSdmaIrqInfo;
typedef struct XSPI_SdmaCallbacks_s XSPI_SdmaCallbacks;
typedef struct XSPI_DirectErrorCallbacks_s XSPI_DirectErrorCallbacks;
typedef struct XSPI_OpenDrainCallbacks_s XSPI_OpenDrainCallbacks;
typedef struct XSPI_Callbacks_s XSPI_Callbacks;
typedef struct XSPI_Config_s XSPI_Config;
typedef struct XSPI_SysReq_s XSPI_SysReq;
typedef struct XSPI_AcmdCommandParameters_s XSPI_AcmdCommandParameters;
typedef struct XSPI_CdmaCommand_s XSPI_CdmaCommand;
typedef struct XSPI_CdmaChainStatus_s XSPI_CdmaChainStatus;
typedef struct XSPI_CdmaCommandChain_s XSPI_CdmaCommandChain;
typedef struct XSPI_PioCommand_s XSPI_PioCommand;
typedef struct XSPI_LatestBootStatus_s XSPI_LatestBootStatus;
typedef struct XSPI_PollingConfig_s XSPI_PollingConfig;
typedef struct XSPI_DevDiscParamsP1_s XSPI_DevDiscParamsP1;
typedef struct XSPI_DevDiscParamsP2_s XSPI_DevDiscParamsP2;
typedef struct XSPI_DeviceDiscoveryConfig_s XSPI_DeviceDiscoveryConfig;
typedef struct XSPI_ResetSeqConfig_s XSPI_ResetSeqConfig;
typedef struct XSPI_EraseSecSeqConfig_s XSPI_EraseSecSeqConfig;
typedef struct XSPI_ChipEraseSeqConfig_s XSPI_ChipEraseSeqConfig;
typedef struct XSPI_HyperFlashOffsetConfig_s XSPI_HyperFlashOffsetConfig;
typedef struct XSPI_PhyConfig_s XSPI_PhyConfig;

typedef struct XSPI_PrivateData_s XSPI_PrivateData;

/**********************************************************************
 * Enumerations
 **********************************************************************/
/** xSPI controller revision */
typedef enum
{
    /** R001 version */
    XSPI_CTRL_REV_R001 = 1U,
    /** R002 version */
    XSPI_CTRL_REV_R002 = 2U,
    /** R003 version */
    XSPI_CTRL_REV_R003 = 3U,
    /** R004 version */
    XSPI_CTRL_REV_R004 = 4U
} XSPI_ControllerRevision;

/** Command status */
typedef enum
{
    /** Pending status of command */
    XSPI_COMMAND_STATUS_PENDING = 0U,
    /** Command completed with failed status */
    XSPI_COMMAND_STATUS_FAILURE = 1U,
    /** Command completed with success status */
    XSPI_COMMAND_STATUS_SUCCESS = 2U,
    /** Detected sending command to busy STIG engine/thread and ignored it */
    XSPI_COMMAND_STATUS_IGNORED = 3U
} XSPI_CommandStatus;

/** Selecting CRC variant */
typedef enum
{
    /** CRC is calculated for all bytes of address transfer phase only and put on the bus after address transfer phase */
    XSPI_CRC_VARIANT_CALC_ADDR_PHASE = 0U,
    /** CRC is calculated for all bytes in sequence and put on the bus after all bytes in sequence */
    XSPI_CRC_VARIANT_CALC_ALL_PHASES = 1U
} XSPI_CrcVariant;

/** Number of IOS lines */
typedef enum
{
    /** 1 line used to send command */
    XSPI_NUMBER_OF_IOS_1 = 0U,
    /** 2 lines used to send command */
    XSPI_NUMBER_OF_IOS_2 = 1U,
    /** 4 lines used to send command */
    XSPI_NUMBER_OF_IOS_4 = 2U,
    /** 8 lines used to send command */
    XSPI_NUMBER_OF_IOS_8 = 3U
} XSPI_NumberOfIos;

/** Command EdgeMode */
typedef enum
{
    /** Use SDR mode */
    XSPI_CMD_EDGE_MODE_SDR = 0U,
    /** Use DDR mode */
    XSPI_CMD_EDGE_MODE_DDR = 1U
} XSPI_CmdEdgeMode;

/** Address EdgeMode */
typedef enum
{
    /** Use SDR mode */
    XSPI_ADDR_EDGE_MODE_SDR = 0U,
    /** Use DDR mode */
    XSPI_ADDR_EDGE_MODE_DDR = 1U
} XSPI_AddrEdgeMode;

/** Data EdgeMode */
typedef enum
{
    /** Use SDR mode */
    XSPI_DATA_EDGE_MODE_SDR = 0U,
    /** Use DDR mode */
    XSPI_DATA_EDGE_MODE_DDR = 1U
} XSPI_DataEdgeMode;

/** Profile 1.0 Autonomic instruction type (with SPI NAND) */
typedef enum
{
    /** Read array */
    XSPI_P10_INSTR_READ_ARRAY = 0U,
    /** Read array XIP */
    XSPI_P10_INSTR_READ_ARRAY_XIP = 1U,
    /** Write array */
    XSPI_P10_INSTR_WRITE_ARRAY = 2U,
    /** Write Enable Latch */
    XSPI_P10_INSTR_WRITE_ENABLE_LATCH = 3U,
    /** Write Disable Latch */
    XSPI_P10_INSTR_WRITE_DISABLE_LATCH = 4U,
    /** Erase sector */
    XSPI_P10_INSTR_ERASE_SECTOR = 5U,
    /** Chip erase */
    XSPI_P10_INSTR_CHIP_ERASE = 6U,
    /** Program/Erase suspend */
    XSPI_P10_INSTR_PROGRAM_ERASE_SUSPEND = 7U,
    /** Program/Erase resume */
    XSPI_P10_INSTR_PROGRAM_ERASE_RESUME = 8U,
    /** Read memory register */
    XSPI_P10_INSTR_READ_MEMORY_REGISTER = 9U,
    /** Write memory register */
    XSPI_P10_INSTR_WRITE_MEMORY_REGISTER = 10U,
    /** Setup read burst */
    XSPI_P10_INSTR_SETUP_READ_BURST = 11U,
    /** Clear flag register */
    XSPI_P10_INSTR_CLEAR_FLAG_REGISTER = 12U,
    /** Enter deep power down */
    XSPI_P10_INSTR_ENTER_DEEP_POWER_DOWN = 13U,
    /** Exit deep power down */
    XSPI_P10_INSTR_EXIT_DEEP_POWER_DOWN = 14U,
    /** Reset enable */
    XSPI_P10_INSTR_RESET_ENABLE = 15U,
    /** Soft reset */
    XSPI_P10_INSTR_SOFT_RESET = 16U,
    /** Read JEDEC ID */
    XSPI_P10_INSTR_READ_JEDEC_ID = 17U,
    /** Read SFDP */
    XSPI_P10_INSTR_READ_SFDP = 18U,
    /** Enter default protocol mode */
    XSPI_P10_INSTR_ENTER_DEF_PROT_MODE = 19U,
    /** Enable SDR octal mode */
    XSPI_P10_INSTR_ENABLE_SDR_OCTAL_MODE = 20U,
    /** Global protection */
    XSPI_P10_INSTR_GLOBAL_PROTECTION = 21U,
    /** Global unprotection */
    XSPI_P10_INSTR_GLOBAL_UNPROTECTION = 22U,
    /** Protect sector */
    XSPI_P10_INSTR_PROTECT_SECTOR = 23U,
    /** Unprotect sector */
    XSPI_P10_INSTR_UNPROTECT_SECTOR = 24U,
    /** Enter 4-byte address mode */
    XSPI_P10_INSTR_ENTER_4BYTE_ADDR_MODE = 25U,
    /** Exit 4-byte address mode */
    XSPI_P10_INSTR_EXIT_4BYTE_ADDR_MODE = 26U,
    /** Read page */
    XSPI_P10_INSTR_SNA_READ_PAGE = 27U,
    /** Read from cache */
    XSPI_P10_INSTR_SNA_READ_CACHE = 28U,
    /** Read page cache random */
    XSPI_P10_INSTR_SNA_RAND_READ_PAGE_CACHE = 29U,
    /** Read page cache last */
    XSPI_P10_INSTR_SNA_LAST_READ_PAGE_CACHE = 30U,
    /** Program load */
    XSPI_P10_INSTR_SNA_PROGRAM_LOAD = 31U,
    /** Program load random */
    XSPI_P10_INSTR_SNA_RAND_PROGRAM_LOAD = 32U,
    /** Program execute */
    XSPI_P10_INSTR_SNA_PROGRAM_EXEC = 33U,
    /** Set features */
    XSPI_P10_INSTR_SNA_SET_FEATURES = 34U,
    /** Get features */
    XSPI_P10_INSTR_SNA_GET_FEATURES = 35U,
    /** Read ID */
    XSPI_P10_INSTR_SNA_READ_ID = 36U
} XSPI_Profile10AutonomicInstrType;

/** Profile 2.0 Autonomic instruction type */
typedef enum
{
    /** CMD code sequence */
    XSPI_P20_INSTR_CMD_CODE_SEQ = 32U,
    /** WREN1 sequence */
    XSPI_P20_INSTR_WREN1_SEQ = 33U,
    /** WREN2 sequence */
    XSPI_P20_INSTR_WREN2_SEQ = 34U,
    /** Read array */
    XSPI_P20_INSTR_READ_ARRAY = 35U,
    /** Write array */
    XSPI_P20_INSTR_WRITE_ARRAY = 36U,
    /** Sector erase */
    XSPI_P20_INSTR_SECTOR_ERASE = 37U,
    /** Chip erase */
    XSPI_P20_INSTR_CHIP_ERASE = 38U,
    /** Erase suspend */
    XSPI_P20_INSTR_ERASE_SUSPEND = 39U,
    /** Erase resume */
    XSPI_P20_INSTR_ERASE_RESUME = 40U,
    /** Program suspend */
    XSPI_P20_INSTR_PROGRAM_SUSPEND = 41U,
    /** Program resume */
    XSPI_P20_INSTR_PROGRAM_RESUME = 42U,
    /** Read status */
    XSPI_P20_INSTR_READ_STATUS = 43U,
    /** Read volatile memory register */
    XSPI_P20_INSTR_READ_VOLATILE_MEM_REG = 44U,
    /** Read non-volatile memory register */
    XSPI_P20_INSTR_READ_NONVOLATILE_MEM_REG = 45U,
    /** Read custom memory register */
    XSPI_P20_INSTR_READ_CUSTOM_MEM_REG = 47U,
    /** Status register clear */
    XSPI_P20_INSTR_STATUS_REG_CLEAR = 48U,
    /** Write volatile memory register */
    XSPI_P20_INSTR_WRITE_VOLATILE_MEM_REG = 49U,
    /** Write non-volatile memory register */
    XSPI_P20_INSTR_WRITE_NONVOLATILE_MEM_REG = 50U,
    /** Write custom memory register enable */
    XSPI_P20_INSTR_WRITE_CUSTOM_MEM_REG_EN = 51U,
    /** Enter deep power down */
    XSPI_P20_INSTR_ENTER_DEEP_POWER_DOWN = 52U,
    /** Reset/ASO Exit */
    XSPI_P20_INSTR_RESET_ASO_EXIT = 53U,
    /** Enter default protocol mode */
    XSPI_P20_INSTR_ENTER_DEF_PROT_MODE = 54U,
    /** Read SFDP */
    XSPI_P20_INSTR_READ_SFDP = 55U
} XSPI_Profile20AutonomicInstrType;

/** Data transfer direction */
typedef enum
{
    /** Data transfer read transaction */
    XSPI_DATA_TRANS_DIR_READ = 0U,
    /** Data transfer write transaction */
    XSPI_DATA_TRANS_DIR_WRITE = 1U
} XSPI_DataTransDirection;

/** Target space for PROFILE_2 instruction */
typedef enum
{
    /** Use memory space */
    XSPI_TARGET_SPACE_MEMORY = 0U,
    /** Use register space */
    XSPI_TARGET_SPACE_REGISTER = 1U
} XSPI_TargetSpace;

/** Burst type for PROFILE_2 sequence */
typedef enum
{
    /** Use wrapped burst */
    XSPI_BURST_TYPE_WRAPPED = 0U,
    /** Use linear burst */
    XSPI_BURST_TYPE_LINEAR = 1U
} XSPI_BurstType;

/** Data bytes per Flash Memory address */
typedef enum
{
    /** 1 byte per addres */
    XSPI_DATA_PER_ADDRESS_1B = 0U,
    /** 2 bytes per addres */
    XSPI_DATA_PER_ADDRESS_2B = 1U
} XSPI_DataPerAddress;

/** CRC chunk size */
typedef enum
{
    /** 4B chunk size */
    XSPI_CRC_CHUNK_SIZE_4B = 0U,
    /** 8B chunk size */
    XSPI_CRC_CHUNK_SIZE_8B = 1U,
    /** 16B chunk size */
    XSPI_CRC_CHUNK_SIZE_16B = 2U,
    /** 32B chunk size */
    XSPI_CRC_CHUNK_SIZE_32B = 3U,
    /** 64B chunk size */
    XSPI_CRC_CHUNK_SIZE_64B = 4U,
    /** 128B chunk size */
    XSPI_CRC_CHUNK_SIZE_128B = 5U,
    /** 256B chunk size */
    XSPI_CRC_CHUNK_SIZE_256B = 6U,
    /** 512B chunk size */
    XSPI_CRC_CHUNK_SIZE_512B = 7U
} XSPI_CrcChunkSize;

/** Read mode based on number of bytes to read (in STIG mode) */
typedef enum
{
    /** When read data is more than 2 bytes */
    XSPI_READ_DATA_EXTENDED_MODE = 0U,
    /** When read data is 1 or 2 bytes */
    XSPI_READ_DATA_SHORT_MODE = 1U
} XSPI_ReadDataMode;

/** STIG instruction layout type */
typedef enum
{
    /** Legacy SPI and XSPI profile 1.0 Instruction */
    XSPI_STIG_INSTR_TYPE_PROFILE_10 = 1U,
    /** Legacy Hyperflash and XSPI profile 2.0 Instruction */
    XSPI_STIG_INSTR_TYPE_PROFILE_20 = 2U,
    /** Generic instruction type (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_STIG_INSTR_TYPE_GENERIC_SEQ = 3U
} XSPI_StigInstructionType;

/** xSPI controller work mode */
typedef enum
{
    /** DIRECT work mode */
    XSPI_WORK_MODE_DIRECT = 0x00U,
    /** STIG work mode */
    XSPI_WORK_MODE_STIG = 0x01U,
    /** Invalid work mode value */
    XSPI_WORK_MODE_UNKNOWN = 0x02U,
    /** Auto command work mode (in R004 applicable only for FULL/FULL_ASF configuration) */
    XSPI_WORK_MODE_AUTO_COMMAND = 0x03U
} XSPI_WorkMode;

/** DMA word size */
typedef enum
{
    /** One byte */
    XSPI_DMA_WORD_SIZE_BYTE = 0U,
    /** 16-bit word */
    XSPI_DMA_WORD_SIZE_16B_WORD = 1U,
    /** 32-bit word */
    XSPI_DMA_WORD_SIZE_32B_WORD = 2U,
    /** 64-bit word */
    XSPI_DMA_WORD_SIZE_64B_WORD = 3U
} XSPI_DmaWordSize;

/** Sequence type for CDMA, PIO and DIRECT mode (Profile 1.0 or Profile 2.0) */
typedef enum
{
    /** Use profile 1.0 sequences (Legacy SPI and xSPI devices) */
    XSPI_SEQUENCE_TYPE_P1_SPI_NOR = 0U,
    /** Use profile 2.0 sequences (HyperFlash) */
    XSPI_SEQUENCE_TYPE_P2_HYPER_FLASH = 1U,
    /** Use profile 2.0 sequences (HyperRAM) */
    XSPI_SEQUENCE_TYPE_P2_HYPER_RAM = 2U,
    /** Use profile 1.0 sequences (SPI NAND) (Since R003) */
    XSPI_SEQUENCE_TYPE_P1_SPI_NAND = 3U
} XSPI_SequenceType;

/** Program page size */
typedef enum
{
    /** 1B program page size */
    XSPI_PROGRAM_PAGE_SIZE_1B = 0U,
    /** 2B program page size */
    XSPI_PROGRAM_PAGE_SIZE_2B = 1U,
    /** 4B program page size */
    XSPI_PROGRAM_PAGE_SIZE_4B = 2U,
    /** 8B program page size */
    XSPI_PROGRAM_PAGE_SIZE_8B = 3U,
    /** 16B program page size */
    XSPI_PROGRAM_PAGE_SIZE_16B = 4U,
    /** 32B program page size */
    XSPI_PROGRAM_PAGE_SIZE_32B = 5U,
    /** 64B program page size */
    XSPI_PROGRAM_PAGE_SIZE_64B = 6U,
    /** 128B program page size */
    XSPI_PROGRAM_PAGE_SIZE_128B = 7U,
    /** 256B program page size */
    XSPI_PROGRAM_PAGE_SIZE_256B = 8U,
    /** 512B program page size */
    XSPI_PROGRAM_PAGE_SIZE_512B = 9U,
    /** 1024B program page size (Since R003) */
    XSPI_PROGRAM_PAGE_SIZE_1024B = 10U,
    /** 2048B program page size (Since R003) */
    XSPI_PROGRAM_PAGE_SIZE_2048B = 11U,
    /** 4096B program page size (Since R003) */
    XSPI_PROGRAM_PAGE_SIZE_4096B = 12U
} XSPI_ProgramPageSize;

/** Read page size */
typedef enum
{
    /** 1B read page size */
    XSPI_READ_PAGE_SIZE_1B = 0U,
    /** 2B read page size */
    XSPI_READ_PAGE_SIZE_2B = 1U,
    /** 4B read page size */
    XSPI_READ_PAGE_SIZE_4B = 2U,
    /** 8B read page size */
    XSPI_READ_PAGE_SIZE_8B = 3U,
    /** 16B read page size */
    XSPI_READ_PAGE_SIZE_16B = 4U,
    /** 32B read page size */
    XSPI_READ_PAGE_SIZE_32B = 5U,
    /** 64B read page size */
    XSPI_READ_PAGE_SIZE_64B = 6U,
    /** 128B read page size */
    XSPI_READ_PAGE_SIZE_128B = 7U,
    /** 256B read page size */
    XSPI_READ_PAGE_SIZE_256B = 8U,
    /** 512B read page size */
    XSPI_READ_PAGE_SIZE_512B = 9U,
    /** 1024B read page size (Since R003) */
    XSPI_READ_PAGE_SIZE_1024B = 10U,
    /** 2048B read page size (Since R003) */
    XSPI_READ_PAGE_SIZE_2048B = 11U,
    /** 4096B read page size (Since R003) */
    XSPI_READ_PAGE_SIZE_4096B = 12U,
    /** Unlimited read page size */
    XSPI_READ_PAGE_SIZE_UNLIMITED = 0xFU
} XSPI_ReadPageSize;

/** Number of planes in SPI NAND device (since R003) */
typedef enum
{
    /** Single plane */
    XSPI_SPI_NAND_1_PLANE = 0U,
    /** Two planes */
    XSPI_SPI_NAND_2_PLANES = 1U,
    /** Four planes */
    XSPI_SPI_NAND_4_PLANES = 2U
} XSPI_SpiNandPlaneCount;

/** Describes the width of COULMN address for SPI NAND device (since R003) */
typedef enum
{
    /** 12 bits of COLUMN address */
    XSPI_SPI_NAND_CA_SIZE_12 = 0U,
    /** 13 bits of COLUMN address */
    XSPI_SPI_NAND_CA_SIZE_13 = 1U
} XSPI_SpiNandCaSize;

/** Number of address bytes for all status sequences */
typedef enum
{
    /** One address byte */
    XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE = 0U,
    /** Two address bytes */
    XSPI_STAT_SEQ_ADDR_COUNT_2_ADDR_BYTES = 1U,
    /** Three address bytes */
    XSPI_STAT_SEQ_ADDR_COUNT_3_ADDR_BYTES = 2U,
    /** Four address bytes */
    XSPI_STAT_SEQ_ADDR_COUNT_4_ADDR_BYTES = 3U
} XSPI_StatSeqAddrCount;

/** ISEQ_STAT command status word size */
typedef enum
{
    /** 8 bits status word size */
    XSPI_STAT_STATUS_WORD_SIZE_8_BIT = 0U,
    /** 16 bits status word size */
    XSPI_STAT_STATUS_WORD_SIZE_16_BIT = 1U
} XSPI_StatStatusWordSize;

/** ISEQ_STAT command polarity information */
typedef enum
{
    /** 0 value of polarity */
    XSPI_STAT_POLARITY_0 = 0U,
    /** 1 value of polarity */
    XSPI_STAT_POLARITY_1 = 1U
} XSPI_StatPolarity;

/** DMA data width */
typedef enum
{
    /** 32-bit DMA data */
    XSPI_DMA_DATA_WIDTH_32B = 0U,
    /** 64-bit DMA data */
    XSPI_DMA_DATA_WIDTH_64B = 1U
} XSPI_DmaDataWidth;

/** DMA address width */
typedef enum
{
    /** 32-bit DMA address */
    XSPI_DMA_ADDR_WIDTH_32B = 0U,
    /** 64-bit DMA address */
    XSPI_DMA_ADDR_WIDTH_64B = 1U
} XSPI_DmaAddrWidth;

/** Hardware reset type */
typedef enum
{
    /** Device RESET# pin will be used for toggling Device Hardware Reset functionality */
    XSPI_HARDWARE_RESET_OPTION_RESET_PIN = 0U,
    /** Device DQ3 pin will be used for toggling Device Hardware Reset functionality */
    XSPI_HARDWARE_RESET_OPTION_DQ3_PIN = 1U
} XSPI_HardwareResetOption;

/** Clock mode settings */
typedef enum
{
    /** Clock is low when SPI bus is in idle state */
    XSPI_SPI_CLOCK_MODE_0 = 0U,
    /** Clock is high when SPI bus is in idle state */
    XSPI_SPI_CLOCK_MODE_3 = 1U
} XSPI_SpiClockMode;

/** Auto command DMA type */
typedef enum
{
    /** Select DMA master data interface */
    XSPI_ACMD_DMA_SELECT_MASTER = 0U,
    /** Select DMA slave data interface */
    XSPI_ACMD_DMA_SELECT_SLAVE = 1U
} XSPI_AcmdDmaSelect;

/** Auto command type (CDMA or PIO) */
typedef enum
{
    /** Erase sector sequence */
    XSPI_ACMD_COMMAND_TYPE_ERASE_SEC_SEQ = 0x1000U,
    /** Full chip erase sequence */
    XSPI_ACMD_COMMAND_TYPE_FULL_CHIP_ERASE_SEQ = 0x1001U,
    /** Device reset sequence */
    XSPI_ACMD_COMMAND_TYPE_DEVICE_RESET_SEQ = 0x1100U,
    /** Device JEDEC reset sequence (since R003) */
    XSPI_ACMD_COMMAND_TYPE_DEVICE_JEDEC_RESET_SEQ = 0x1101U,
    /** Program sequence */
    XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ = 0x2100U,
    /** Read sequence */
    XSPI_ACMD_COMMAND_TYPE_READ_SEQ = 0x2200U
} XSPI_AcmdCommandType;

/** Discovery mode. This is a 4-bit value. Writing a value selects number of xSPI I/Os used by Device Discovery */
typedef enum
{
    /** Auto */
    XSPI_DEV_DISC_LINES_AUTO = 0x00U,
    /** One line */
    XSPI_DEV_DISC_LINES_1L = 0x01U,
    /** Two lines */
    XSPI_DEV_DISC_LINES_2L = 0x02U,
    /** Four lines */
    XSPI_DEV_DISC_LINES_4L = 0x04U,
    /** Eight lines */
    XSPI_DEV_DISC_LINES_8L = 0x08U,
    /** Eight lines for Legacy Hyperflash and xspi Profile 2.0 */
    XSPI_DEV_DISC_LINES_8L_P2 = 0x0CU,
    /** One line for SPI NAND devices (Since R003) */
    XSPI_DEV_DISC_LINES_1L_SPI_NAND = 0x0EU
} XSPI_DeviceDiscoveryLines;

/** Device discovery status */
typedef enum
{
    /** Pending status */
    XSPI_DEV_DISC_STATUS_PENDING = 0x00U,
    /** Device discovery failed */
    XSPI_DEV_DISC_STATUS_FAILED = 0x01U,
    /** xSPI device detected */
    XSPI_DEV_DISC_STATUS_XSPI_DEV = 0x02U,
    /** Legacy SPI device detected */
    XSPI_DEV_DISC_STATUS_LEGACY_SPI_DEV = 0x03U,
    /** Device discovery status unknown */
    XSPI_DEV_DISC_STATUS_UNKNOWN = 0x04U
} XSPI_DeviceDiscoveryStatus;

/** Device discovery number of dummy clock cycles */
typedef enum
{
    /** 8 Dummy clock cycles */
    XSPI_DEV_DISC_EIGHT_CLOCK_CYCLES = 0x00U,
    /** 20 Dummy clock cycles */
    XSPI_DEV_DISC_TWENTY_CLOCK_CYCLES = 0x01U
} XSPI_DeviceDiscoveryDummyCnt;

/** Device discovery command type mode enable */
typedef enum
{
    /** Single Data Rate mode enabled */
    XSPI_DEV_DISC_CMD_SDR_MODE = 0x00U,
    /** Double Data Rate mode enabled */
    XSPI_DEV_DISC_CMD_DDR_MODE = 0x01U,
    /** Double Transfer Rate mode enabled */
    XSPI_DEV_DISC_CMD_DTR_MODE = 0x02U
} XSPI_DeviceDiscoveryCmdType;

/** Device discovery extended opcode value */
typedef enum
{
    /** Extended opcode is 0xA5 */
    XSPI_DEV_DISC_EXT_OPCODE_A5 = 0x00U,
    /** Extended opcode is 0x5A */
    XSPI_DEV_DISC_EXT_OPCODE_5A = 0x01U
} XSPI_DeviceDiscoveryExtOpVal;

/** Device discovery request type */
typedef enum
{
    /** Perform full discovery process */
    XSPI_DEV_DISC_REQ_TYPE_FULL_DISCOVERY = 0x00U,
    /** Configure registers only */
    XSPI_DEV_DISC_REQ_TYPE_CONFIGURE_REGISTERS_ONLY = 0x01U
} XSPI_DeviceDiscoveryReqType;

/** Sector size for erase sequence */
typedef enum
{
    /** 1B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_1B = 0U,
    /** 2B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_2B = 1U,
    /** 4B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_4B = 2U,
    /** 8B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_8B = 3U,
    /** 16B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_16B = 4U,
    /** 32B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_32B = 5U,
    /** 64B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_64B = 6U,
    /** 128B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_128B = 7U,
    /** 256B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_256B = 8U,
    /** 512B sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_512B = 9U,
    /** 1KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_1KB = 10U,
    /** 2KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_2KB = 11U,
    /** 4KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_4KB = 12U,
    /** 8KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_8KB = 13U,
    /** 16KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_16KB = 14U,
    /** 32KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_32KB = 15U,
    /** 64KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_64KB = 16U,
    /** 128KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_128KB = 17U,
    /** 256KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_256KB = 18U,
    /** 512KB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_512KB = 19U,
    /** 1MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_1MB = 20U,
    /** 2MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_2MB = 21U,
    /** 4MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_4MB = 22U,
    /** 8MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_8MB = 23U,
    /** 16MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_16MB = 24U,
    /** 32MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_32MB = 25U,
    /** 64MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_64MB = 26U,
    /** 128MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_128MB = 27U,
    /** 256MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_256MB = 28U,
    /** 512MB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_512MB = 29U,
    /** 1GB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_1GB = 30U,
    /** 2GB sector size */
    XSPI_ERASE_SEQ_SEC_SIZE_2GB = 31U
} XSPI_EraseSeqSectorSize;

/** Active edge in SDR mode */
typedef enum
{
    /** Controller propagates data from positive edge of PHY sampling clock */
    XSPI_SDR_ACTIVE_EDGE_POSITIVE = 0U,
    /** Controller propagates data from negative edge of PHY sampling clock */
    XSPI_SDR_ACTIVE_EDGE_NEGATIVE = 1U
} XSPI_SdrActiveEdge;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/** Called when trigger condition for the Slave DMA is met in ACMD mode (in R004 applicable only for FULL/FULL_ASF configuration) */
typedef void (*XSPI_CbAcmdSdmaTransaction)(XSPI_PrivateData* pdPtr, XSPI_AcmdSdmaIrqInfo irqInfo);

/** Called after DOS underrun or overflow detected in Direct mode (in R004 applicable only for FULL/FULL_ASF configuration) */
typedef void (*XSPI_CbDirDqsError)(XSPI_PrivateData* pdPtr);

/** Called when command operation is finished in ACMD mode (in R004 applicable only for FULL/FULL_ASF configuration) */
typedef void (*XSPI_CbAcmdCmdComplete)(XSPI_PrivateData* pdPtr, uint8_t thread, uint8_t thread_err);

/** Called when master Data DMA error occured (in R004 applicable only for FULL/FULL_ASF configuration) */
typedef void (*XSPI_CbMasterDataDMAError)(XSPI_PrivateData* pdPtr, uint64_t dmaTargetErrorAddr);

/** Called when access to descriptor failed (in R004 applicable only for FULL/FULL_ASF configuration) */
typedef void (*XSPI_CbCommandDMAError)(XSPI_PrivateData* pdPtr, uint64_t dmaTargetErrorAddr);

/** Called when not allowed access to the Slave DMA interface is detected */
typedef void (*XSPI_CbSdmaError)(XSPI_PrivateData* pdPtr);

/** Called when trigger condition for the Slave DMA is met in STIG mode */
typedef void (*XSPI_CbStigSdmaTransaction)(XSPI_PrivateData* pdPtr, XSPI_StigSdmaIrqInfo irqInfo);

/** Slave DMA transfer callback in Direct mode */
typedef void (*XSPI_CbDirectSdmaTransaction)(XSPI_PrivateData* pdPtr, XSPI_DirectSdmaTransInfo sdmaInfo);

/** Called when invalid command sequence detected in Direct mode */
typedef void (*XSPI_CbDirInvalidCommandSeq)(XSPI_PrivateData* pdPtr);

/** Called when CRC error detected in Direct mode */
typedef void (*XSPI_CbDirCrcError)(XSPI_PrivateData* pdPtr);

/** Called when correctable ECC error occured */
typedef void (*XSPI_CbDirCorrEccError)(XSPI_PrivateData* pdPtr);

/** Called when Uncorrectable ECC error occured */
typedef void (*XSPI_CbDirUncorrEccError)(XSPI_PrivateData* pdPtr);

/** Called when instruction in glued chain is completed */
typedef void (*XSPI_CbStigDone)(XSPI_PrivateData* pdPtr);

/** Called when sending command to busy thread, and ignoring it */
typedef void (*XSPI_CbCommandIgnored)(XSPI_PrivateData* pdPtr);

/** Called when xSPI controller is in IDLE state */
typedef void (*XSPI_CbIdleStateDetected)(XSPI_PrivateData* pdPtr);

/** Called when detected change of state on open drain pin (since R003) */
typedef void (*XSPI_CbOpenDrainStateChanged)(XSPI_PrivateData* pdPtr, uint8_t pinIdx);

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
 * Gets the driver memory requirements to support specified
 * configuration
 * @param[in] config Driver/hardware configuration required.
 * @param[out] sysReq Returns the size of memory allocations required.
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_Probe(XSPI_Config* config, XSPI_SysReq* sysReq);

/**
 * Initialize the driver as specified in the Config structure. Must be
 * called before all other access APIs.
 * @param[in] privateData Memory pointer to the uninitialized private data of the size specified by probe.
 * @param[in] config Specifies driver/hardware configuration.
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_Init(XSPI_PrivateData* privateData, const XSPI_Config* config);

/**
 * Destructor for the driver
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_Destroy(XSPI_PrivateData* privateData);

/**
 * "Start the XSPI driver, enabling interrupts.   This is called after
 * the client has successfully initialized the driver and hooked   the
 * driver's ISR (the isr member of this struct) to the IRQ."
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_Start(XSPI_PrivateData* privateData);

/**
 * Stops the XSPI driver by disabling interrupts.
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_Stop(XSPI_PrivateData* privateData);

/**
 * "Driver ISR. Platform-specific code is responsible for ensuring
 * this gets called when the corresponding hardware's interrupt is
 * asserted. Registering the ISR should be done after calling init,
 * and before calling start. The driver's ISR will not attempt to lock
 * any locks, but will perform client callbacks. If the client wishes
 * to defer processing to non-interrupt time, it is responsible for
 * doing so. This function must not be called after calling destroy
 * and releasing private data memory."
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_Isr(XSPI_PrivateData* privateData);

/**
 * Sets controller's work mode
 * @param[in] privateData Pointer to driver private data object
 * @param[in] workMode Controller work mode to be set
 * @return CDN_EOK On success
 * @return CDN_EINVAL If workMode is invalid
 * @return CDN_EBUSY When controller is busy
 */
uint32_t XSPI_SetWorkMode(XSPI_PrivateData* privateData, const XSPI_WorkMode workMode);

/**
 * Gets controller's current work mode
 * @param[in] privateData Pointer to driver private data object
 * @param[out] workMode Controller work mode
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetWorkMode(XSPI_PrivateData* privateData, XSPI_WorkMode* workMode);

/**
 * Sets events to enable or disable corresponding interrupts
 * @param[in] privateData Pointer to driver private data object
 * @param[in] events Mask of Events to be enabled or disabled.
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetEventEnable(XSPI_PrivateData* privateData, uint32_t events);

/**
 * Gets enabled events
 * @param[in] privateData Pointer to driver private data object
 * @param[out] events Enabled events
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetEventEnable(XSPI_PrivateData* privateData, uint32_t* events);

/**
 * Sets callbacks for different events
 * @param[in] privateData Pointer to driver private data object
 * @param[in] callbacks Callback functions to register
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetCallbacks(XSPI_PrivateData* privateData, const XSPI_Callbacks callbacks);

/**
 * Gets registered callback functions
 * @param[in] privateData Pointer to driver private data object
 * @param[out] callbacks Returns registered callbacks
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetCallbacks(const XSPI_PrivateData* privateData, XSPI_Callbacks* callbacks);

/**
 * Sets write protection state for all devices
 * @param[in] privateData Pointer to driver private data object
 * @param[in] writeProtectEnabled Write protect state
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_EBUSY When controller is busy
 */
uint32_t XSPI_SetWriteProtect(XSPI_PrivateData* privateData, bool writeProtectEnabled);

/**
 * Gets write protection state
 * @param[in] privateData Pointer to driver private data object
 * @param[out] writeProtectEnabled Write protect state
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetWriteProtect(XSPI_PrivateData* privateData, bool* writeProtectEnabled);

/**
 * Sets DMA configuration
 * @param[in] privateData Pointer to driver private data object
 * @param[in] dmaConfig DMA configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetDmaConfig(XSPI_PrivateData* privateData, const XSPI_DmaConfig* dmaConfig);

/**
 * Gets DMA configuration
 * @param[in] privateData Pointer to driver private data object
 * @param[out] dmaConfig DMA configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetDmaConfig(XSPI_PrivateData* privateData, XSPI_DmaConfig* dmaConfig);

/**
 * Sets SPI clock mode. Allowed to change for SDR transfers only.
 * @param[in] privateData Pointer to driver private data object
 * @param[in] spiClockMode SPI clock mode
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetSpiClockMode(XSPI_PrivateData* privateData, XSPI_SpiClockMode spiClockMode);

/**
 * Gets SPI clock mode
 * @param[in] privateData Pointer to driver private data object
 * @param[out] spiClockMode SPI clock mode
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetSpiClockMode(XSPI_PrivateData* privateData, XSPI_SpiClockMode* spiClockMode);

/**
 * Function gets the reset configuration currently set.
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetBankCfg Reset configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetResetConfig(XSPI_PrivateData* privateData, XSPI_ResetDeviceConfig* resetBankCfg);

/**
 * Function sets the reset configuration which is used to reset memory
 * banks.
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetBankCfg Reset configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetResetConfig(XSPI_PrivateData* privateData, const XSPI_ResetDeviceConfig* resetBankCfg);

/**
 * Asserts the software controlled hardware reset signal. Reset
 * configuration must be set before calling this function.
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_EBUSY When controller is busy
 */
uint32_t XSPI_AssertReset(XSPI_PrivateData* privateData);

/**
 * Deasserts the software controlled hardware reset signal.
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_EBUSY When controller is busy
 */
uint32_t XSPI_DeAssertReset(XSPI_PrivateData* privateData);

/**
 * Sets relative device selection and reset recovery delays
 * @param[in] privateData Pointer to driver private data object
 * @param[in] deviceRelativeDelays Device relative delays
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetDeviceRelativeDelays(XSPI_PrivateData* privateData, const XSPI_DeviceRelativeDelays* deviceRelativeDelays);

/**
 * Gets device relative delays
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceRelativeDelays Device relative delays
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetDeviceRelativeDelays(XSPI_PrivateData* privateData, XSPI_DeviceRelativeDelays* deviceRelativeDelays);

/**
 * Sets global command parameters having common values for sequences
 * in CDMA, PIO and Direct work modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] globalCmdParameters Global command parameters
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetGlobalCmdParameters(XSPI_PrivateData* privateData, const XSPI_GlobalCommandParameters* globalCmdParameters);

/**
 * Gets global command parameters having common values for sequences
 * in CDMA, PIO and Direct work modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] globalCmdParameters Global command parameters
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetGlobalCmdParameters(XSPI_PrivateData* privateData, XSPI_GlobalCommandParameters* globalCmdParameters);

/**
 * Sets global command parameters for SPI NAND devices (Since R003)
 * @param[in] privateData Pointer to driver private data object
 * @param[in] spiNandCmdParams SPI NAND global command parameters
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_SetSpiNandCmdParameters(XSPI_PrivateData* privateData, const XSPI_SpiNandGlobCmdParams* spiNandCmdParams);

/**
 * Gets global command parameters for SPI NAND devices (Since R003)
 * @param[in] privateData Pointer to driver private data object
 * @param[out] spiNandCmdParams SPI NAND global command parameters
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_GetSpiNandCmdParameters(XSPI_PrivateData* privateData, XSPI_SpiNandGlobCmdParams* spiNandCmdParams);

/**
 * Sets XIP mode bits
 * @param[in] privateData Pointer to driver private data object
 * @param[in] xipModeBitsConfig XIP mode bits config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetXipModeBitsConfig(XSPI_PrivateData* privateData, const XSPI_XipModeBitsConfig* xipModeBitsConfig);

/**
 * Gets XIP mode bits
 * @param[in] privateData Pointer to driver private data object
 * @param[out] xipModeBitsConfig XIP mode bits config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetXipModeBitsConfig(XSPI_PrivateData* privateData, XSPI_XipModeBitsConfig* xipModeBitsConfig);

/**
 * Send command in Direct mode
 * @param[in] privateData Pointer to driver private data object
 * @param[in] directCmd Pointer to direct mode command structure
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SendDirectCommand(XSPI_PrivateData* privateData, const XSPI_DirectCmd* directCmd);

/**
 * Checks busy status of Direct command generator module
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_EBUSY When controller is busy
 */
uint32_t XSPI_IsDirectCmdEngBusy(XSPI_PrivateData* privateData);

/**
 * Sets direct work mode config
 * @param[in] privateData Pointer to driver private data object
 * @param[in] directModeConfig Pointer to direct mode config structure
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetDirectModeConfig(XSPI_PrivateData* privateData, const XSPI_DirectModeConfig* directModeConfig);

/**
 * Gets direct work mode config
 * @param[in] privateData Pointer to driver private data object
 * @param[out] directModeConfig Pointer to direct mode config structure
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetDirectModeConfig(XSPI_PrivateData* privateData, XSPI_DirectModeConfig* directModeConfig);

/**
 * Sets maximum number of xspi_clk cycles through CS# will be active
 * @param[in] privateData Pointer to driver private data object
 * @param[in] activeDevMaxCycles Active device max cycles (HyperRAM only)
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetP2ActiveDevMaxCycles(XSPI_PrivateData* privateData, uint32_t activeDevMaxCycles);

/**
 * Gets maximum number of xspi_clk cycles through CS# will be active
 * @param[in] privateData Pointer to driver private data object
 * @param[out] activeDevMaxCycles Active device max cycles (HyperRAM only)
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetP2ActiveDevMaxCycles(XSPI_PrivateData* privateData, uint32_t* activeDevMaxCycles);

/**
 * Sets PROGRAM sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] progSeqP1Cfg PROGRAM P1 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetProgramSeqP1Config(XSPI_PrivateData* privateData, const XSPI_ProgramSeqP1Config* progSeqP1Cfg);

/**
 * Gets PROGRAM sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] progSeqP1Cfg PROGRAM P1 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetProgramSeqP1Config(XSPI_PrivateData* privateData, XSPI_ProgramSeqP1Config* progSeqP1Cfg);

/**
 * Sets PROGRAM sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] progSeqP2Cfg PROGRAM P2 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetProgramSeqP2Config(XSPI_PrivateData* privateData, const XSPI_ProgramSeqP2Config* progSeqP2Cfg);

/**
 * Gets PROGRAM sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] progSeqP2Cfg PROGRAM P2 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetProgramSeqP2Config(XSPI_PrivateData* privateData, XSPI_ProgramSeqP2Config* progSeqP2Cfg);

/**
 * Sets READ sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] readSeqP1Cfg READ P1 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetReadSeqP1Config(XSPI_PrivateData* privateData, const XSPI_ReadSeqP1Config* readSeqP1Cfg);

/**
 * Gets READ sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] readSeqP1Cfg READ P1 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetReadSeqP1Config(XSPI_PrivateData* privateData, XSPI_ReadSeqP1Config* readSeqP1Cfg);

/**
 * Sets READ sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] readSeqP2Cfg READ P2 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetReadSeqP2Config(XSPI_PrivateData* privateData, const XSPI_ReadSeqP2Config* readSeqP2Cfg);

/**
 * Gets READ sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] readSeqP2Cfg READ P2 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetReadSeqP2Config(XSPI_PrivateData* privateData, XSPI_ReadSeqP2Config* readSeqP2Cfg);

/**
 * Sets Write Enable(WEL) sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] welSeqCfg WEL sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetWelSeqConfig(XSPI_PrivateData* privateData, const XSPI_WelSeqConfig* welSeqCfg);

/**
 * Gets Write Enable(WEL) sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] welSeqCfg WEL sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetWelSeqConfig(XSPI_PrivateData* privateData, XSPI_WelSeqConfig* welSeqCfg);

/**
 * Sets status checking sequence configuration common for Profile 1
 * and 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] commStatSeqConfig Common STAT sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetCommStatSeqConfig(XSPI_PrivateData* privateData, const XSPI_CommStatSeqConfig* commStatSeqConfig);

/**
 * Gets status checking sequence configuration common for Profile 1
 * and 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] commStatSeqConfig Common STAT sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetCommStatSeqConfig(XSPI_PrivateData* privateData, XSPI_CommStatSeqConfig* commStatSeqConfig);

/**
 * Sets status checking sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqP1Cfg STAT P1 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetStatSeqP1Config(XSPI_PrivateData* privateData, const XSPI_StatSeqP1Config* statSeqP1Cfg);

/**
 * Gets status checking sequence configuration for Profile 1
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqP1Cfg STAT P1 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetStatSeqP1Config(XSPI_PrivateData* privateData, XSPI_StatSeqP1Config* statSeqP1Cfg);

/**
 * Sets status checking sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqP2Cfg STAT P2 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetStatSeqP2Config(XSPI_PrivateData* privateData, const XSPI_StatSeqP2Config* statSeqP2Cfg);

/**
 * Gets status checking sequence configuration for Profile 2
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqP2Cfg STAT P2 sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetStatSeqP2Config(XSPI_PrivateData* privateData, XSPI_StatSeqP2Config* statSeqP2Cfg);

/**
 * Sets status sequence settings for NAND SPI devices (Since R003)
 * @param[in] privateData Pointer to driver private data object
 * @param[in] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_SetStatSeqSpiNandConfig(XSPI_PrivateData* privateData, const XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg);

/**
 * Gets status sequence settings for NAND SPI devices (Since R003)
 * @param[in] privateData Pointer to driver private data object
 * @param[out] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_GetStatSeqSpiNandConfig(XSPI_PrivateData* privateData, XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg);

/**
 * Sends STIG command for execution
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] stigCommand Pointer to STIG command
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SendStigCommand(XSPI_PrivateData* privateData, XSPI_StigCommand* stigCommand);

/**
 * Gets last command status (in STIG work mode)
 * @param[in] privateData Pointer to driver private data object
 * @param[out] stigCommand Stig command containing status information
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetStigStatus(XSPI_PrivateData* privateData, XSPI_StigCommand* stigCommand);

/**
 * Sets relative device selection delay applicable for JEDEC Reset
 * command (Since R003)
 * @param[in] privateData Pointer to driver private data object
 * @param[in] jedecRstTiming JEDEC RESET timing config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_SetJedecResetTimingConfig(XSPI_PrivateData* privateData, const XSPI_JedecResetTimingConfig* jedecRstTiming);

/**
 * Gets relative device selection delay applicable for JEDEC Reset
 * command (Since R003)
 * @param[in] privateData Pointer to driver private data object
 * @param[out] jedecRstTiming JEDEC RESET timing config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_GetJedecResetTimingConfig(XSPI_PrivateData* privateData, XSPI_JedecResetTimingConfig* jedecRstTiming);

/**
 * Sends JEDEC RESET command in STIG work mode
 * @param[in] privateData Pointer to driver piravte data object
 * @param[in] bankSelect Selected bank to which JEDEC RESET instruction should be sent
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 * @return CDN_ENOTSUP If controller version is below R003
 */
uint32_t XSPI_SendStigJedecReset(XSPI_PrivateData* privateData, uint8_t bankSelect);

/**
 * Sets continue processing on descriptor error state
 * @param[in] privateData Pointer to driver private data object
 * @param[in] procOnErrEnabled Continue processing on descriptor error
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetContinueProcOnDescError(XSPI_PrivateData* privateData, bool procOnErrEnabled);

/**
 * Gets continue processing on descriptor error state
 * @param[in] privateData Pointer to driver private data object
 * @param[out] procOnErrEnabled Continue processing on descriptor error
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetContinueProcOnDescError(XSPI_PrivateData* privateData, bool* procOnErrEnabled);

/**
 * Gets latest boot operation status
 * @param[in] privateData Pointer to driver private data object
 * @param[out] bootStatus Latest boot operation status
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetLatestBootStatus(XSPI_PrivateData* privateData, XSPI_LatestBootStatus* bootStatus);

/**
 * Sets device discovery config
 * @param[in] privateData Pointer to driver private data object
 * @param[in] deviceDiscoveryConfig Device discovery config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetDeviceDiscoveryConfig(XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig);

/**
 * Gets device discovery config
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceDiscoveryConfig Device discovery config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetDeviceDiscoveryConfig(XSPI_PrivateData* privateData, XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig);

/**
 * Runs device discovery with current discovery settings
 * @param[in] privateData Pointer to driver private data object
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_RunDeviceDiscovery(XSPI_PrivateData* privateData);

/**
 * Gets status of device discovery operation
 * @param[in] privateData Pointer to driver private data object
 * @param[out] deviceDiscoveryStatus Status of device discovery operation
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetDeviceDiscoveryStatus(XSPI_PrivateData* privateData, XSPI_DeviceDiscoveryStatus* deviceDiscoveryStatus);

/**
 * Sets the relative reset recovery delay with respect to generated
 * xSPI flash interface
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetRecovery Reset recovery delay
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetResetRecoveryDelay(XSPI_PrivateData* privateData, uint32_t resetRecovery);

/**
 * Gets the relative reset recovery delay with respect to generated
 * xSPI flash interface
 * @param[in] privateData Pointer to driver private data object
 * @param[out] resetRecovery Reset recovery delay
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetResetRecoveryDelay(XSPI_PrivateData* privateData, uint32_t* resetRecovery);

/**
 * Sets the polling configuration for controller to check device
 * status after issue of erase/write operation
 * @param[in] privateData Pointer to driver private data object
 * @param[in] pollingConfig Polling configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetPollingConfig(XSPI_PrivateData* privateData, const XSPI_PollingConfig* pollingConfig);

/**
 * Gets polling configuration for controller to check device status
 * @param[in] privateData Pointer to driver private data object
 * @param[out] pollingConfig Polling configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetPollingConfig(XSPI_PrivateData* privateData, XSPI_PollingConfig* pollingConfig);

/**
 * Sets HyperFlash offset config
 * @param[in] privateData Pointer to driver private data object
 * @param[in] hfOffsetCfg HyperFlash offset config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetHyperFlashOffsetConfig(XSPI_PrivateData* privateData, const XSPI_HyperFlashOffsetConfig* hfOffsetCfg);

/**
 * Gets HyperFlash offset config
 * @param[in] privateData Pointer to driver private data object
 * @param[out] hfOffsetCfg HyperFlash offset config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetHyperFlashOffsetConfig(XSPI_PrivateData* privateData, XSPI_HyperFlashOffsetConfig* hfOffsetCfg);

/**
 * Sets configuration of the resynchronization of slave DLL of PHY
 * @param[in] privateData Pointer to driver private data object
 * @param[in] phyConfig PHY configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetPhyConfig(XSPI_PrivateData* privateData, const XSPI_PhyConfig* phyConfig);

/**
 * Gets configuration of the resynchronization of slave DLL of PHY
 * @param[in] privateData Pointer to driver private data object
 * @param[out] phyConfig PHY configuration
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetPhyConfig(XSPI_PrivateData* privateData, XSPI_PhyConfig* phyConfig);

/**
 * Writes signal value to reset the DLLs of the PHY
 * @param[in] privateData Pointer to driver private data object
 * @param[in] dllReset DLL reset value
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_PhyWriteDllReset(XSPI_PrivateData* privateData, uint8_t dllReset);

/**
 * Sends CDMA command for execution
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[in,out] cdmaCmd Pointer to CDMA command
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SendCdmaCommand(XSPI_PrivateData* privateData, uint8_t thread, XSPI_CdmaCommand* cdmaCmd);

/**
 * Gets CDMA command status
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[in,out] cdmaCmd Pointer to CDMA command, contains status structure
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetCdmaCommandStatus(XSPI_PrivateData* privateData, uint8_t thread, XSPI_CdmaCommand* cdmaCmd);

/**
 * Sends multiple CDMA commands for execution by forming a chain
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] cdmaCmdChain Pointer to CDMA commands chain structure
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SendCdmaCommandChain(XSPI_PrivateData* privateData, XSPI_CdmaCommandChain* cdmaCmdChain);

/**
 * Gets CDMA chain status
 * @param[in] privateData Pointer to driver private data object
 * @param[in,out] cdmaCmdChain Pointer to CDMA commands chain
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetCdmaChainStatus(XSPI_PrivateData* privateData, XSPI_CdmaCommandChain* cdmaCmdChain);

/**
 * Sends PIO command for execution
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[in,out] pioCmd Pointer to PIO command
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SendPioCommand(XSPI_PrivateData* privateData, uint8_t thread, XSPI_PioCommand* pioCmd);

/**
 * Gets PIO command status
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[in,out] pioCmd Pointer to PIO command
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetPioCommandStatus(XSPI_PrivateData* privateData, uint8_t thread, XSPI_PioCommand* pioCmd);

/**
 * Gets the status of last command executed in ACMD mode (both for
 * CDMA and PIO modes) and STIG work mode
 * @param[in] privateData Pointer to driver private data object
 * @param[in] thread Thread number
 * @param[out] cmdStatus Pointer to command status structure
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetAcmdLastCmdStatus(XSPI_PrivateData* privateData, uint8_t thread, XSPI_CommandStatusInfo* cmdStatus);

/**
 * Sets RESET sequence configuration for Profile 1 in CDMA and PIO
 * modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] resetSeqCfg RESET sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetResetSeqConfig(const XSPI_PrivateData* privateData, const XSPI_ResetSeqConfig* resetSeqCfg);

/**
 * Gets RESET sequence configuration for Profile 1 in CDMA and PIO
 * modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] resetSeqCfg RESET sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetResetSeqConfig(XSPI_PrivateData* privateData, XSPI_ResetSeqConfig* resetSeqCfg);

/**
 * Sets ERASE SECTOR sequence configuration for Profile 1 in CDMA and
 * PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] eraseSecSeqCfg ERASE SECTOR sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetEraseSecConfig(XSPI_PrivateData* privateData, const XSPI_EraseSecSeqConfig* eraseSecSeqCfg);

/**
 * Gets ERASE SECTOR sequence configuration for Profile 1 in CDMA and
 * PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] eraseSecSeqCfg ERASE SECTOR sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetEraseSecConfig(XSPI_PrivateData* privateData, XSPI_EraseSecSeqConfig* eraseSecSeqCfg);

/**
 * Sets CHIP ERASE sequence configuration for Profile 1 in CDMA and
 * PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[in] chipEraseSeqCfg CHIP ERASE sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_SetChipEraseSeqConfig(XSPI_PrivateData* privateData, const XSPI_ChipEraseSeqConfig* chipEraseSeqCfg);

/**
 * Gets CHIP ERASE sequence configuration for Profile 1 in CDMA and
 * PIO modes
 * @param[in] privateData Pointer to driver private data object
 * @param[out] chipEraseSeqCfg CHIP ERASE sequence config
 * @return CDN_EOK On success
 * @return CDN_EINVAL For invalid pointer
 */
uint32_t XSPI_GetChipEraseSeqConfig(XSPI_PrivateData* privateData, XSPI_ChipEraseSeqConfig* chipEraseSeqCfg);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* XSPI_IF_H */
