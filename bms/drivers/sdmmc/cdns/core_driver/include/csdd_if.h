/**********************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.05.b3ee589
 *          Do not edit it manually.
 **********************************************************************
 * SD Host driver
 **********************************************************************/

#ifndef CSDD_IF_H
#define CSDD_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */

#include "cdn_stdint.h"
#include "cdn_stdtypes.h"
#include "sdio_config.h"
#include "sd4hc_regs.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** CommandField structure maximum array size */
#define	CSDD_MAX_NUMBER_COMMAND 10U

/** Max devices per one slot */
#define	CSDD_MAX_DEV_PER_SLOT 1U

#define	CSDD_CQ_REQUEST_PTR CSDD_CQRequest*

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
 * Type defines
 **********************************************************************/

typedef struct MEMORY_CARD_INFO_s CSDD_MEMORY_CARD_INFO;
typedef struct MEMORY_CARD_INFO_s* CSDD_PMEMORY_CARD_INFO;

/**********************************************************************
 * Forward declarations
 **********************************************************************/
typedef struct CSDD_SysReq_s CSDD_SysReq;
typedef struct CSDD_Config_s CSDD_Config;
typedef struct CSDD_RequestFlags_s CSDD_RequestFlags;
typedef struct CSDD_CommandField_s CSDD_CommandField;
typedef struct CSDD_Request_s CSDD_Request;
typedef struct CSDD_SubBuffer_s CSDD_SubBuffer;
typedef struct CSDD_DeviceInfo_s CSDD_DeviceInfo;
typedef struct CSDD_PhyDelaySettings_s CSDD_PhyDelaySettings;
typedef struct CSDD_MemoryCardInfo_s CSDD_MemoryCardInfo;
typedef struct CSDD_DeviceState_s CSDD_DeviceState;
typedef struct CSDD_CQInitConfig_s CSDD_CQInitConfig;
typedef struct CSDD_CQRequestData_s CSDD_CQRequestData;
typedef struct CSDD_CQRequest_s CSDD_CQRequest;
typedef struct CSDD_CQDcmdRequest_s CSDD_CQDcmdRequest;
typedef struct CSDD_CQIntCoalescingCfg_s CSDD_CQIntCoalescingCfg;
typedef struct CSDD_SDIO_SlotSettings_s CSDD_SDIO_SlotSettings;
typedef struct CSDD_SDIO_CidRegister_s CSDD_SDIO_CidRegister;
typedef struct CSDD_SDIO_Device_s CSDD_SDIO_Device;
typedef struct CSDD_SDIO_Slot_s CSDD_SDIO_Slot;
typedef struct CSDD_SDIO_Host_s CSDD_SDIO_Host;
typedef struct CSDD_Callbacks_s CSDD_Callbacks;
typedef struct CSDD_CPhyConfigIoDelay_s CSDD_CPhyConfigIoDelay;
typedef struct CSDD_CPhyConfigLvsi_s CSDD_CPhyConfigLvsi;
typedef struct CSDD_CPhyConfigDfiRd_s CSDD_CPhyConfigDfiRd;
typedef struct CSDD_CPhyConfigOutputDelay_s CSDD_CPhyConfigOutputDelay;


/**********************************************************************
 * Enumerations
 **********************************************************************/
/** CCCR card control registers definitions */
typedef enum
{
    /** CCCR version number and SDIO specification version number register */
    CSDD_CCCR_CCCR_SDIO_REV = 0U,
    /** SD version number register */
    CSDD_CCCR_SD_SPEC_REV = 1U,
    /** IO enable function register */
    CSDD_CCCR_IO_ENABLE = 2U,
    /** IO ready function register */
    CSDD_CCCR_IO_READY = 3U,
    /** interrupt enable register */
    CSDD_CCCR_INT_ENABLE = 4U,
    /** interrupt pending register */
    CSDD_CCCR_INT_PENDING = 5U,
    /** IO Abort register. It used to stop a function transfer. */
    CSDD_CCCR_ABORT = 6U,
    /** Bus interface control register */
    CSDD_CCCR_BUS_CONTROL = 7U,
    /** Card capability register */
    CSDD_CCCR_CARD_CAPABILITY = 8U,
    /** Pointer to card's common Card Information Structure (CIS) */
    CSDD_CCCR_CIS_POINTER = 9U,
    /** Bus suspend register */
    CSDD_CCCR_BUS_SUSPENDED = 12U,
    /** Function select register */
    CSDD_CCCR_FUNCTION_SELECT = 13U,
    /** Exec flags register. The bits of this register are used by the host to determine the current execution status of all functions (1-7) and memory (0). */
    CSDD_CCCR_EXEC_FLAGS = 14U,
    /** Ready flags register. The bits of this register tell the host the read or write busy status for functions (1-7) and memory (0). */
    CSDD_CCCR_READY_FLAGS = 15U,
    /** I/O block size for Function 0 */
    CSDD_CCCR_FN0_BLOCK_SIZE = 16U,
    /** Power control register */
    CSDD_CCCR_POWER_CONTROL = 18U,
    /** Bus speed select */
    CSDD_CCCR_HIGH_SPEED = 19U,
    /** UHS-I support info */
    CSDD_CCCR_UHSI_SUPPORT = 20U,
    /** Driver Strength */
    CSDD_CCCR_DRIVER_STRENGTH = 21U,
    /** Interrupt extension */
    CSDD_CCCR_INT_EXT = 22U
} CSDD_CccrRegAddr;

/** Tuple names definitions of SDIO card */
typedef enum
{
    /** NULL tuple */
    CSDD_TUPLE_CISTPL_NULL = 0U,
    /** Checksum control */
    CSDD_TUPLE_CISTPL_CHECKSUM = 16U,
    /** Level 1 version/product information */
    CSDD_TUPLE_CISTPL_VERS_1 = 21U,
    /** Alternate language string tuple */
    CSDD_TUPLE_CISTPL_ALTSTR = 22U,
    /** Manufacturer identification string tuple */
    CSDD_TUPLE_CISTPL_MANFID = 32U,
    /** Function identification tuple */
    CSDD_TUPLE_CISTPL_FUNCID = 33U,
    /** Additional information for functions built to support application specifications for standard SDIO functions. */
    CSDD_TUPLE_CISTPL_SDIO_STD = 145U,
    /** Reserved for future use with SDIO devices */
    CSDD_TUPLE_CISTPL_SDIO_EXT = 146U,
    /** The End-of-chain Tuple */
    CSDD_TUPLE_CISTPL_END = 255U
} CSDD_TupleCode;

typedef enum
{
    /** normal command */
    CSDD_CMD_TYPE_NORMAL = 0U,
    /** suspend command */
    CSDD_CMD_TYPE_SUSPEND = 1U,
    /** resume command */
    CSDD_CMD_TYPE_RESUME = 2U,
    /** abort command */
    CSDD_CMD_TYPE_ABORT = 3U,
    /** abort command in UHS-II native protocol */
    CSDD_CMD_TYPE_TRANS_ABORT = 4U,
    /** go into dormant state command (UHS-II command type) */
    CSDD_CMD_TYPE_GO_DORMANT = 5U
} CSDD_CmdType;

/** Command can be be MainCommand or SubCommand depending on the DAT line Busy during command execution */
typedef enum
{
    /** Command is called as Main command if it contains a subcommand */
    CSDD_CMD_CAT_MAIN = 0U,
    /** Command is called as Sub command if it comes under a command  */
    CSDD_CMD_CAT_SUB = 1U,
    /** Normal Command */
    CSDD_CMD_CAT_NORMAL = 2U
} CSDD_CmdCat;

typedef enum
{
    CSDD_RESPONSE_NO_RESP = 0U,
    CSDD_RESPONSE_R1 = 1U,
    CSDD_RESPONSE_R1B = 2U,
    CSDD_RESPONSE_R2 = 3U,
    CSDD_RESPONSE_R3 = 4U,
    CSDD_RESPONSE_R4 = 5U,
    CSDD_RESPONSE_R5 = 6U,
    CSDD_RESPONSE_R5B = 7U,
    CSDD_RESPONSE_R6 = 8U,
    CSDD_RESPONSE_R7 = 9U
} CSDD_ResponseType;

typedef enum
{
    CSDD_CARD_TYPE_NONE = 0U,
    CSDD_CARD_TYPE_SDIO = 1U,
    CSDD_CARD_TYPE_SDMEM = 2U,
    CSDD_CARD_TYPE_COMBO = 3U,
    CSDD_CARD_TYPE_MMC = 4U
} CSDD_CardType;

typedef enum
{
    CSDD_CAPACITY_NORMAL = 1U,
    CSDD_CAPACITY_HIGH = 2U
} CSDD_Capacity;

typedef enum
{
    CSDD_BUS_WIDTH_1 = 1U,
    CSDD_BUS_WIDTH_4 = 4U,
    CSDD_BUS_WIDTH_8 = 8U,
    CSDD_BUS_WIDTH_4_DDR = 5U,
    CSDD_BUS_WIDTH_8_DDR = 6U
} CSDD_BusWidth;

typedef enum
{
    CSDD_BUS_MODE_SPI = 1U,
    CSDD_BUS_MODE_SD = 2U
} CSDD_BusMode;

typedef enum
{
    CSDD_INTERFACE_TYPE_SD = 1U,
    CSDD_INTERFACE_TYPE_UNKNOWN = 2U
} CSDD_InterfaceType;

typedef enum
{
    /** SD layer request type (SD) */
    CSDD_REQUEST_TYPE_SD = 1U
} CSDD_RequestType;

typedef enum
{
    /** set host clock frequency */
    CSDD_CONFIG_SET_CLK = 1U,
    /** set host bus width */
    CSDD_CONFIG_SET_BUS_WIDTH = 2U,
    /** set timeout on DAT line. Argument is timeout in microseconds */
    CSDD_CONFIG_SET_DAT_TIMEOUT = 3U,
    /** disable signal interrupts */
    CSDD_CONFIG_DISABLE_SIGNAL_INTERRUPT = 4U,
    /** restore signal interrupts */
    CSDD_CONFIG_RESTORE_SIGNAL_INTERRUPT = 5U,
    /** set DMA mode */
    CSDD_CONFIG_SET_DMA_MODE = 6U
} CSDD_ConfigCmd;

typedef enum
{
    CSDD_TRANSFER_READ = 1U,
    CSDD_TRANSFER_WRITE = 0U
} CSDD_TransferDirection;

typedef enum
{
    /** access mode - SDR12 default (CLK: max 25MHz, DT: max 12MB/s) */
    CSDD_ACCESS_MODE_SDR12 = 0U,
    /** access mode - SDR15 default (CLK: max 50MHz, DT: max 25MB/s) */
    CSDD_ACCESS_MODE_SDR25 = 1U,
    /** access mode - SDR50 default (CLK: max 100MHz, DT: max 50MB/s) */
    CSDD_ACCESS_MODE_SDR50 = 2U,
    /** access mode - SDR104 default (CLK: max 208MHz, DT: max 104MB/s) */
    CSDD_ACCESS_MODE_SDR104 = 3U,
    /** access mode - DDR50 default (CLK: max 50MHz, DT: max 50MB/s) */
    CSDD_ACCESS_MODE_DDR50 = 4U,
    /** MMC access mode - legacy mode (CLK: max 26MHz, DT: max 26MB/s) */
    CSDD_ACCESS_MODE_MMC_LEGACY = 6U,
    /** MMC access mode - high speed SDR mode (CLK: max 26MHz, DT: max 26MB/s) */
    CSDD_ACCESS_MODE_HS_SDR = 7U,
    /** MMC access mode - high speed DDR mode (CLK: max 52MHz, DT: max 104MB/s) */
    CSDD_ACCESS_MODE_HS_DDR = 8U,
    /** MMC access mode - HS200 mode (CLK: max 200MHz, DT: max 200MB/s) */
    CSDD_ACCESS_MODE_HS_200 = 9U,
    /** MMC access mode - HS400 mode (CLK: max 200MHz, DT: max 400MB/s) */
    CSDD_ACCESS_MODE_HS_400 = 10U,
    /** MMC access mode - HS400 using Enhanced Strobe (CLK: max 200MHz, DT: max 400MB/s) */
    CSDD_ACCESS_MODE_HS_400_ES = 11U
} CSDD_SpeedMode;

typedef enum
{
    /** Standard DMA mode */
    CSDD_SDMA_MODE = 0U,
    /** Advanced DMA Mode Version 1 */
    CSDD_ADMA1_MODE = 1U,
    /** Advanced DMA Mode Version 2 */
    CSDD_ADMA2_MODE = 2U,
    /** Advanced DMA Mode Version 3 */
    CSDD_ADMA3_MODE = 3U,
    /** DMA mode is selected automatically */
    CSDD_AUTO_MODE = 4U,
    /** DMA is disabled */
    CSDD_NONEDMA_MODE = 255U
} CSDD_DmaMode;

/** Partition name to set access */
typedef enum
{
    /** none partition */
    CSDD_EMMC_ACCCESS_BOOT_NONE = 0U,
    /** boot partition 1 */
    CSDD_EMMC_ACCCESS_BOOT_1 = 1U,
    /** boot partition 2 */
    CSDD_EMMC_ACCCESS_BOOT_2 = 2U,
    /** general purpose partition 1 */
    CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_1 = 3U,
    /** general purpose partition 2 */
    CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_2 = 4U,
    /** general purpose partition 3 */
    CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_3 = 5U,
    /** general purpose partition 4 */
    CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_4 = 6U,
    /** Replay-protected memory-block partition */
    CSDD_EMMC_ACCCESS_BOOT_RPMB = 7U
} CSDD_ParitionAccess;

/** Partition to boot */
typedef enum
{
    /** none partition */
    CSDD_EMMC_BOOT_NONE = 0U,
    /** set boot partition 1 for boot */
    CSDD_EMMC_BOOT_1 = 1U,
    /** set boot partition 2 for boot */
    CSDD_EMMC_BOOT_2 = 2U,
    /** set user partition for boot */
    CSDD_EMMC_BOOT_USER = 3U
} CSDD_ParitionBoot;

/** Partition to boot */
typedef enum
{
    /** Lock device */
    CSDD_MMC_CARD_CONF_CARD_LOCK = 4U,
    /** Unlock device */
    CSDD_MMC_CARD_CONF_CARD_UNLOCK = 0U,
    /** Set device password */
    CSDD_MMC_CARD_CONF_SET_PASSWORD = 1U,
    /** Reset device password */
    CSDD_MMC_CARD_CONF_RESET_PASSWORD = 2U
} CSDD_MmcConfigCmd;

/** Driver strength type */
typedef enum
{
    /** Device driver strength A */
    CSDD_SWITCH_DRIVER_STRENGTH_TYPE_A = 1U,
    /** Device driver strength B */
    CSDD_SWITCH_DRIVER_STRENGTH_TYPE_B = 2U,
    /** Device driver strength C */
    CSDD_SWITCH_DRIVER_STRENGTH_TYPE_C = 3U,
    /** Device driver strength D */
    CSDD_SWITCH_DRIVER_STRENGTH_TYPE_D = 4U
} CSDD_DriverStrengthType;

/** SD card driver current limit */
typedef enum
{
    /** Card driver current limit - 200mA default */
    CSDD_SDCARD_SWITCH_CURRENT_LIMIT_200 = 0U,
    /** Card driver current limit - 400mA */
    CSDD_SDCARD_SWITCH_CURRENT_LIMIT_400 = 1U,
    /** Card driver current limit - 600mA */
    CSDD_SDCARD_SWITCH_CURRENT_LIMIT_600 = 2U,
    /** Card driver current limit - 800mA */
    CSDD_SDCARD_SWITCH_CURRENT_LIMIT_800 = 3U
} CSDD_DriverCurrentLimit;

/** Command queuing task descriptor size */
typedef enum
{
    /** Task descriptor size 64 bit */
    CSDD_CQ_TASK_DESC_SIZE_64BIT = 0U,
    /** Task descriptor size 128 bit */
    CSDD_CQ_TASK_DESC_SIZE_128BIT = 1U
} CSDD_EmmcCmdqTaskDescSize;

/** Command queuing request status */
typedef enum
{
    /** Task executed without errors */
    CSDD_CQ_REQ_STAT_FINISHED = 0U,
    /** Task is ready to execute */
    CSDD_CQ_REQ_STAT_ATTACHED = 1U,
    /** Task is currently executed */
    CSDD_CQ_REQ_STAT_PENDING = 2U,
    /** Task execution failed */
    CSDD_CQ_REQ_STAT_FAILED = 3U
} CSDD_CQReqStat;

/** PHY configuration delay type */
typedef enum
{
    /** delay in the input path for High Speed work mode */
    CSDD_PHY_DELAY_INPUT_HIGH_SPEED = 0U,
    /** delay in the input path for Default Speed work mode */
    CSDD_PHY_DELAY_INPUT_DEFAULT_SPEED = 1U,
    /** delay in the input path for SDR12 work mode */
    CSDD_PHY_DELAY_INPUT_SDR12 = 2U,
    /** delay in the input path for SDR25 work mode */
    CSDD_PHY_DELAY_INPUT_SDR25 = 3U,
    /** delay in the input path for SDR50 work mode */
    CSDD_PHY_DELAY_INPUT_SDR50 = 4U,
    /** delay in the input path for DDR50 work mode */
    CSDD_PHY_DELAY_INPUT_DDR50 = 5U,
    /** delay in the input path for eMMC legacy work mode */
    CSDD_PHY_DELAY_INPUT_MMC_LEGACY = 6U,
    /** delay in the input path for eMMC SDR work mode */
    CSDD_PHY_DELAY_INPUT_MMC_SDR = 7U,
    /** delay in the input path for eMMC DDR work mode */
    CSDD_PHY_DELAY_INPUT_MMC_DDR = 8U,
    /** Value of the delay introduced on the sdclk output for all modes except HS200, HS400 and HS400_ES */
    CSDD_PHY_DELAY_DLL_SDCLK = 11U,
    /** Value of the delay introduced on the sdclk output for HS200, HS400 and HS400_ES speed mode */
    CSDD_PHY_DELAY_DLL_HS_SDCLK = 12U,
    /** Value of the delay introduced on the dat_strobe input used in HS400 / HS400_ES speed mode. */
    CSDD_PHY_DELAY_DLL_DAT_STROBE = 13U
} CSDD_PhyDelay;

/**********************************************************************
 * Callbacks
 **********************************************************************/
typedef void (*CSDD_CardInsertedCallback)(void* pd, uint8_t slotIndex);

typedef void (*CSDD_CardRemovedCallback)(void* pd, uint8_t slotIndex);

typedef uint8_t (*CSDD_CardInterruptHandlerCallback)(void* pd, uint8_t slotIndex);

typedef uint8_t (*CSDD_CardInitializeCallback)(CSDD_SDIO_Host* pd, uint8_t slotIndex);

typedef uint8_t (*CSDD_CardDeinitializeCallback)(CSDD_SDIO_Host* pd, uint8_t slotIndex);

typedef void (*CSDD_AxiErrorCallback)(void* pd, uint8_t axiError);

typedef uint8_t (*CSDD_SetTuneValCallback)(const CSDD_SDIO_Host* pd, uint8_t tune_val);

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
 * @param[in] registerBase base address of controller registers
 * @param[out] req
 * @return 0 on success
 * @return ENOTSUP if configuration cannot be supported due to driver/hardware constraints
 */
uint32_t CSDD_Probe(uintptr_t registerBase, CSDD_SysReq* req);

/**
 * Function initializes all objects. It must be called as the first
 * function before calling other driver functions
 * @param[in] pD private data
 * @param[in] config startup configuration
 * @param[in] callbacks pointer to callbacks functions
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_Init(CSDD_SDIO_Host* pD, CSDD_Config* config, CSDD_Callbacks* callbacks);

/**
 * Enable signaling interrupts
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_Start(CSDD_SDIO_Host* pD);

/**
 * Disable signaling interrupts
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_Stop(CSDD_SDIO_Host* pD);

/**
 * Function executes a request which is given as the request parameter
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] request request to execute
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ExecCardCommand(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_Request* request);

/**
 * Function detaches card, meaning that all information about card is
 * removed in this function
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_DeviceDetach(CSDD_SDIO_Host* pD, uint8_t slotIndex);

/**
 * Function initializes a newly inserted card, gathers information
 * about it, and searches for card driver
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_DeviceAttach(CSDD_SDIO_Host* pD, uint8_t slotIndex);

/**
 * function aborts data transfer
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] isSynchronous abort type: synchronous or asynchronous
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_Abort(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t isSynchronous);

/**
 * sets slot of SD host controller to standby mode and waits for
 * wakeup condition; in standby mode the clock is disabled
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] wakeupCondition conditions of wakeup from standby mode
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_StandBy(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t wakeupCondition);

/**
 * configures the SD Host controller
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] cmd it describes what should be configured
 * @param[in] data buffer with configuration data
 * @param[in] sizeOfData size of data buffer in bytes
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_Configure(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ConfigCmd cmd, void* data, uint8_t* sizeOfData);

/**
 * interrupt handler function, it should be called to handle SD host
 * interrupts
 * @param[in] pD private data
 * @param[in] handled informs if interrupt occurred
 */
void CSDD_Isr(CSDD_SDIO_Host* pD, bool* handled);

/**
 * switches a card and host to work either in high speed mode or in
 * normal mode
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] setHighSpeed defines if high speed mode will be enabled SetHighSpeed = 1) or disabled (SetHighSpeed = 0)
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ConfigureHighSpeed(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool setHighSpeed);

/**
 * checks slots states; depending on the slots status, calls
 * deviceAttach or deviceDettach, or does nothing if slot state
 * remains unchanged
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CheckSlots(CSDD_SDIO_Host* pD);

/**
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] status
 */
void CSDD_CheckInterrupt(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t status);

/**
 * Function configures card access mode
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] accessMode access mode to set
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ConfigureAccessMode(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_SpeedMode accessMode);

/**
 * function executes tuning operation on a card but only if it is
 * needed
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_Tuning(CSDD_SDIO_Host* pD, uint8_t slotIndex);

/**
 * function executes tuning operation on a card but only if it is
 * needed
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] progClkMode parameter defines if programmable clock mode should be enabled. 1  programmable clock mode will be enabled; 0  10-bit divider clock mode is enabled
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ClockGeneratorSelect(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t progClkMode);

/**
 * Function enables or disables preset value switching
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] enable enable/disable preset value switching
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_PresetValueSwitch(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool enable);

/**
 * function configures driver strength of a card and the slot
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] driverStrength new driver strength
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ConfigureDriverStrength(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverStrengthType driverStrength);

/**
 * Function loads driver for the card
 * @param[in] pD private data
 */
void CSDD_MemoryCardLoadDriver(CSDD_SDIO_Host* pD);

/**
 * Function transfers data to/from memory card, function operates on
 * blocks (512 bytes);
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] address address in card memory to/from which data will be transferred; address in blocks (512 bytes)
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] size size of buffer in bytes, Buffer size should be divisible by 512
 * @param[in] direction
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemoryCardDataTransfer(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction);

/**
 * Function transfers data to/from memory card, function operates on
 * blocks (512 bytes)
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] address memory card address to/from which data will be transferred; address in blocks (512 bytes);
 * @param[in,out] buffer buffer (or buffers when SubBufferCount > 0) with data to be written or to save data that was read
 * @param[in] size BufferSize size of buffer in bytes
 * @param[in] direction parameter defines data transfer direction
 * @param[in] subBufferCount If it is bigger than 0 it means that Buffer is pointer to CSDD_SubBuffer array where are defined buffers with data to transfer and data sizes of each buffer
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemoryCardDataTransfer2(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction, uint32_t subBufferCount);

/**
 * function executes configuration commands on memory card
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] cmd this parameter defines what operation will be executed
 * @param[in] data buffer with data
 * @param[in] size size of data in bytes
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemoryCardConfigure(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_MmcConfigCmd cmd, uint8_t* data, uint8_t size);

/**
 * Function erases block or blocks specified by startBlockAddress and
 * blockCount parameteres.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] startBlockAddress address of the first block to be erased
 * @param[in] blockCount number of blocks to be erased.
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemoryCardDataErase(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t startBlockAddress, uint32_t blockCount);

/**
 * Function transfers data to/from memory card (byte oriented)
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] address address in card memory to/from which data will be transferred; address in bytes
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] size size of buffer in bytes
 * @param[in] direction size of buffer in bytes
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemCardPartialDataXfer(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction);

/**
 * Function transfers data in infinite mode to/from memory card.
 * Function operates on 512 data blocks. Data transfer can be
 * continiued by memCardInfXferContinue. Trnasmission must be finished
 * by memCardInfXferFinish
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] address address in card memory to/from which data will be transferred; address in blocks (512 bytes)
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] size size of buffer in bytes
 * @param[in] direction parameter defines transfer direction
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemCardInfXferStart(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction);

/**
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] size size of buffer in bytes
 * @param[in] direction parameter defines transfer direction
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemCardInfXferContinue(CSDD_SDIO_Host* pD, uint8_t slotIndex, void* buffer, uint32_t size, CSDD_TransferDirection direction);

/**
 * Function finishes data transfer in infinite mode
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] direction parameter defines transfer direction
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemCardInfXferFinish(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_TransferDirection direction);

/**
 * Function transfers data to/from memory card. Function operates on
 * 512 data blocks. Function does not wait for operation finish.
 * Therefore it returns pointer to current request. User using
 * MemoryCard_FinishXferNonBlock function and request pointer can wait
 * until operation finish and get the status of operation. Function
 * needs AUTO_CMD option enabled
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] address address in card memory to/from which data will be transferred; address in blocks (512 bytes)
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] size size of buffer in bytes
 * @param[in] direction parameter defines transfer direction
 * @param[out] request current executing request
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemCardDataXferNonBlock(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction, void** request);

/**
 * Function waits until request finish and returns status of request
 * execution
 * @param[in] pD private data
 * @param[in] pRequest request to wait for
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemCardFinishXferNonBlock(CSDD_SDIO_Host* pD, CSDD_Request* pRequest);

/**
 * Function sets delay line in UHS-I PHY hardware module. Function
 * works for SD Host 3 Function is obsolete writePhySet function
 * should be used to configure PHY delays.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] phyDelaySet PHY delay settings
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_PhySettingsSd3(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelaySettings* phyDelaySet);

/**
 * Function sets delay line in UHS-I PHY hardware module. Function
 * works for SD Host 4. Function is obsolete writePhySet function
 * should be used to configure PHY delays.
 * @param[in] pD private data
 * @param[in] phyDelaySet PHY delay settings
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_PhySettingsSd4(CSDD_SDIO_Host* pD, CSDD_PhyDelaySettings* phyDelaySet);

/**
 * Function configures one PHY delay line in UHS-I PHY hardware
 * module.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] phyDelayType it defines which PHY delay should be written
 * @param[in] delayVal value to be written to selected PHY delay
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_WritePhySet(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelay phyDelayType, uint8_t delayVal);

/**
 * Function configures one PHY delay line in UHS-I PHY hardware
 * module.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] phyDelayType it defines which PHY delay should be read:
 * @param[in] delayVal read value of selected PHY delay
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ReadPhySet(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelay phyDelayType, uint8_t* delayVal);

/**
 * reads card status. Function returns error if command executing
 * error appears or card error bits are set
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] cardStatus pointer to memory where read card status shall be written
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ReadCardStatus(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* cardStatus);

/**
 * selects or deselects a card; if RCA parameter is 0, then card will
 * be deselected, otherwise,a card of the RCA value will be selected
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] rca card address in selecting card case or 0 in deselecting card case
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SelectCard(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint16_t rca);

/**
 * resets a card using CMD0 command
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ResetCard(CSDD_SDIO_Host* pD, uint8_t slotIndex);

/**
 * executes CMD55 command
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ExecCmd55Command(CSDD_SDIO_Host* pD, uint8_t slotIndex);

/**
 * writes or reads the CCCR card registers; the CCCR is present in
 * SDIO or combo cards only
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] transferDirection parameter defines transfer direction
 * @param[in,out] data pointer to write/read data buffer
 * @param[in] size size of Data buffer in bytes
 * @param[in] registerAddress
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_AccessCccr(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_TransferDirection transferDirection, void* data, uint8_t size, CSDD_CccrRegAddr registerAddress);

/**
 * reads CSD register of the card
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] buffer content of CSD register 16 bytes
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ReadCsd(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t buffer[4]);

/**
 * function reads Extended CSD register from the card
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] buffer
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ReadExCsd(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t* buffer);

/**
 * function reads tuple from the CIS card register to buffer; CIS
 * register is present only in SDIO or combo cards;
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] tupleAddress start address of the CIS register
 * @param[in] tupleCode code name of tuple
 * @param[out] buffer buffer for read tuple
 * @param[in] bufferSize size of buffer in bytes
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetTupleFromCis(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t tupleAddress, CSDD_TupleCode tupleCode, void* buffer, uint8_t bufferSize);

/**
 * function reads SD card status
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] buffer card status
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ReadSdStatus(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t buffer[64]);

/**
 * Function configures driver strength of a card
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] driverStrength new driver strength value
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetDriverStrength(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverStrengthType driverStrength);

/**
 * Function sets a card current limit.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] currentLimit
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ExecSetCurrentLimit(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverCurrentLimit currentLimit);

/**
 * Function executes mmc switch command to modify EXT_CSD register.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] argIndex index of EXT_CSD register field to be modified
 * @param[in] argValue new value to be set
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcSwitch(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t argIndex, uint8_t argValue);

/**
 * Function reads byte pointed by byteNr parameter. Next it masks the
 * value using ~mask, at the end function makes "or" operation with
 * newValue. Such value is written to the EXT_CSD register
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] byteNr index of EXT_CSD register field to be modified
 * @param[in] newValue new value to be "or"
 * @param[in] mask mask showing which part of byte should be masked
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcSetExtCsd(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t byteNr, uint8_t newValue, uint8_t mask);

/**
 * Function sets active partition to boot operation.
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] partition partition to be active to boot
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcSetBootPartition(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ParitionBoot partition);

/**
 * Function sets active partition to access
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] partition partition to be active to access
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcSetPartAccess(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ParitionAccess partition);

/**
 * Function sets active partition to access
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] enableBootAck enable/disable eMMC boot ACK
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcSetBootAck(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool enableBootAck);

/**
 * Function executes boot operation. It reads data from active boot
 * partition to the buffer
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] buffer buffer for read
 * @param[in] size buffer size in bytes
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcExecuteBoot(CSDD_SDIO_Host* pD, uint8_t slotIndex, void* buffer, uint32_t size);

/**
 * Function gets boot partition size
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] bootSize size of boot partition
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MmcGetParitionBootSize(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* bootSize);

/**
 * function gets current device interface type (SD legacy)
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] interfaceType interface type
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetInterfaceType(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_InterfaceType* interfaceType);

/**
 * function gets current device state/info
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] deviceState device state and info
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetDeviceState(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DeviceState* deviceState);

/**
 * Function gets sectors count
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] sectorCount sector count
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_MemoryCardGetSecCount(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* sectorCount);

/**
 * Function used to save pointer to driver data
 * @param[in] pD private data
 * @param[in] drvData driver data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetDriverData(CSDD_SDIO_Host* pD, void* drvData);

/**
 * Function used get pointer to driver data saved by setDriverData
 * function
 * @param[in] pD private data
 * @param[out] drvData driver data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetDriverData(CSDD_SDIO_Host* pD, const void** drvData);

/**
 * Function makes very simple host initialization just enables clock
 * and supply the power. Function is useful for emmc boot operation
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[in] clk clock frequency in hertz
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SimpleInit(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t clk);

/**
 * Function resets SD Host controller
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_ResetHost(CSDD_SDIO_Host* pD);

/**
 * Function gets RCA address of conneted device
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] rca RCA address
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetRca(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint16_t* rca);

/**
 * Function enables command queuing and set initialize configuration
 * @param[in] pD private data
 * @param[in] cqConfig Initial configuration.
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQEnable(CSDD_SDIO_Host* pD, CSDD_CQInitConfig* cqConfig);

/**
 * Function disables command queuing
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQDisable(CSDD_SDIO_Host* pD);

/**
 * Function get command queuing initial configuration passed in in
 * cQEnable function
 * @param[in] pD private data
 * @param[out] cqConfig current command queue configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQGetInitConfig(CSDD_SDIO_Host* pD, CSDD_CQInitConfig* cqConfig);

/**
 * Function searches and gets unused task ID
 * @param[in] pD private data
 * @param[out] taskId unused task ID
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQGetUnusedTaskId(CSDD_SDIO_Host* pD, uint8_t* taskId);

/**
 * Function starts task execution. Task must be attached before by
 * cQAttachRequest function
 * @param[in] pD private data
 * @param[in] taskId task ID which shall be executed
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQStartExecuteTask(CSDD_SDIO_Host* pD, uint8_t taskId);

/**
 * Function attaches new request to a task. Function create new
 * descriptors. Function cannot be used to attach direct requests.
 * Execution of request is not started by this function.
 * @param[in] pD private data
 * @param[in] request a request to be attached
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQAttachRequest(CSDD_SDIO_Host* pD, CSDD_CQRequest* request);

/**
 * Function attaches new request to the direct task. Function create
 * new descriptors. Function start of execution direct task. Function
 * can be only to direct requests.
 * @param[in] pD private data
 * @param[in] request a direct request to be executed
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQExecuteDcmdRequest(CSDD_SDIO_Host* pD, CSDD_CQDcmdRequest* request);

/**
 * Function gets current configuration of command queuing direct
 * command
 * @param[in] pD private data
 * @param[out] enable it informs if direct command is enabled or disabled
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQGetDirectCmdConfig(CSDD_SDIO_Host* pD, uint8_t* enable);

/**
 * Function sets new configuration of command queuing direct command
 * @param[in] pD private data
 * @param[out] enable if it is then direct command will be enabled, if it is 0 then direct command will be disabled
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQSetDirectCmdConfig(CSDD_SDIO_Host* pD, uint8_t enable);

/**
 * Function sets new configuration of command queuing interrupt
 * coalescing
 * @param[in] pD private data
 * @param[int] config new interrupt coalescing configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQSetIntCoalescingConfig(CSDD_SDIO_Host* pD, CSDD_CQIntCoalescingCfg* config);

/**
 * Function gets current configuration of command queuing interrupt
 * coalescing
 * @param[in] pD private data
 * @param[out] config current interrupt coalescing configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQGetIntCoalescingConfig(CSDD_SDIO_Host* pD, CSDD_CQIntCoalescingCfg* config);

/**
 * Function gets current configuration of command queuing interrupt
 * coalescing
 * @param[in] pD private data
 * @param[out] clockFreqKHz interrupt coalescing timeout base clock frequency in KHz. It can be usefull to calculate interrupt coalescing timeout value
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQGetIntCoalescingTimeoutBase(CSDD_SDIO_Host* pD, uint32_t* clockFreqKHz);

/**
 * Function starts tasks execution. Tasks must be attached before by
 * cQAttachRequest function
 * @param[in] pD private data
 * @param[in] taskIds task IDs OR'd combination of bit-flags selecting the tasks to be executed. Bit 0 - task ID 0, bit 1 task ID 1 ...
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQStartExecuteTasks(CSDD_SDIO_Host* pD, uint32_t taskIds);

/**
 * Function put command queueing to halt state or exit from halt
 * state. Behaviour depends on set parameter.
 * @param[in] pD private data
 * @param[in] set 1 - enter to halt state, 0 - exit from halt state
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQHalt(CSDD_SDIO_Host* pD, uint8_t set);

/**
 * Function dicards one task
 * @param[in] pD private data
 * @param[in] taskId task ID to discard
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQTaskDiscard(CSDD_SDIO_Host* pD, uint8_t taskId);

/**
 * Function dicards all tasks
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQAllTasksDiscard(CSDD_SDIO_Host* pD);

/**
 * Function resets interrupt coalescing timer and counter
 * @param[in] pD private data
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQResetIntCoalCounters(CSDD_SDIO_Host* pD);

/**
 * Function writes error mask for command response.
 * @param[in] pD private data
 * @param[in] errorMask bit mask informs CQ engine which bits should be treated as error in command response
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQSetResponseErrorMask(CSDD_SDIO_Host* pD, uint32_t errorMask);

/**
 * Function reads error mask for command response.
 * @param[in] pD private data
 * @param[out] errorMask bit mask informs CQ engine which bits should be treated as error in command response
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CQGetResponseErrorMask(CSDD_SDIO_Host* pD, uint32_t* errorMask);

/**
 * Function reads base clock
 * @param[in] pD private data
 * @param[in] slotIndex slot index
 * @param[out] frequencyKHz base clock
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetBaseClk(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* frequencyKHz);

/**
 * Function waits until request finish and returns status of request
 * execution
 * @param[in] pD private data
 * @param[in] pRequest request to wait for
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_WaitForRequest(CSDD_SDIO_Host* pD, CSDD_Request* pRequest);

/**
 * @param[in] pD private data
 * @param[in] ioDelay configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetCPhyConfigIoDelay(CSDD_SDIO_Host* pD, CSDD_CPhyConfigIoDelay* ioDelay);

/**
 * @param[in] pD private data
 * @param[out] ioDelay configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetCPhyConfigIoDelay(CSDD_SDIO_Host* pD, CSDD_CPhyConfigIoDelay* ioDelay);

/**
 * @param[in] pD private data
 * @param[in] lvsi configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetCPhyConfigLvsi(CSDD_SDIO_Host* pD, CSDD_CPhyConfigLvsi* lvsi);

/**
 * @param[in] pD private data
 * @param[out] lvsi configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetCPhyConfigLvsi(CSDD_SDIO_Host* pD, CSDD_CPhyConfigLvsi* lvsi);

/**
 * @param[in] pD private data
 * @param[in] dfiRd configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetCPhyConfigDfiRd(CSDD_SDIO_Host* pD, CSDD_CPhyConfigDfiRd* dfiRd);

/**
 * @param[in] pD private data
 * @param[out] dfiRd configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetCPhyConfigDfiRd(CSDD_SDIO_Host* pD, CSDD_CPhyConfigDfiRd* dfiRd);

/**
 * @param[in] pD private data
 * @param[in] outputDelay configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetCPhyConfigOutputDelay(CSDD_SDIO_Host* pD, CSDD_CPhyConfigOutputDelay* outputDelay);

/**
 * @param[in] pD private data
 * @param[out] outputDelay configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetCPhyConfigOutputDelay(CSDD_SDIO_Host* pD, CSDD_CPhyConfigOutputDelay* outputDelay);

/**
 * @param[in] pD private data
 * @param[in] doReset enable/disable reset
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_CPhyDllReset(CSDD_SDIO_Host* pD, bool doReset);

/**
 * @param[in] pD private data
 * @param[in] extendedWrMode
 * @param[in] extendedRdMode
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetCPhyExtMode(CSDD_SDIO_Host* pD, bool extendedWrMode, bool extendedRdMode);

/**
 * @param[in] pD private data
 * @param[out] extendedWrMode
 * @param[out] extendedRdMode
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetCPhyExtMode(CSDD_SDIO_Host* pD, bool* extendedWrMode, bool* extendedRdMode);

/**
 * @param[in] pD private data
 * @param[in] sdclkAdj configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_SetCPhySdclkAdj(CSDD_SDIO_Host* pD, uint8_t sdclkAdj);

/**
 * @param[in] pD private data
 * @param[out] sdclkAdj configuration
 * @return 0 on success or error code otherwise
 */
uint32_t CSDD_GetCPhySdclkAdj(CSDD_SDIO_Host* pD, uint8_t* sdclkAdj);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* CSDD_IF_H */
