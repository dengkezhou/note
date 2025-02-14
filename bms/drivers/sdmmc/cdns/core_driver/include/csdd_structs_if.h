/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure, DRV-4932" */
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
#ifndef CSDD_STRUCTS_IF_H
#define CSDD_STRUCTS_IF_H

#include "cdn_stdtypes.h"
#include "csdd_if.h"

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
struct CSDD_SysReq_s
{
    /** private data size */
    uint32_t pDataSize;
    /** ADMA descriptors buffer size */
    uint32_t descSize;
    /** ADMA3 Integrated descriptors buffer size */
    uint32_t idDescSize;
};

/** Structure defining all configuration parameters applied on driver start-up */
struct CSDD_Config_s
{
    /** base address of CSDD registers */
    uintptr_t regBase;
    /** logical address of ADMA2descriptors */
    uint32_t* descLogAddress;
    /** physical address of ADMA2descriptors */
    void* descPhyAddress;
    /** logical address of ADMA3 integrated descriptors */
    uint32_t* idDescLogAddress;
    /** physical address of ADMA3 integrated descriptors */
    void* idDescPhyAddress;
    /** Enable DMA width 64bit */
    uint8_t dma64BitEn;
};

/** Structure describes a parameters of SD request */
struct CSDD_RequestFlags_s
{
    /** Type of command. */
    CSDD_CmdType commandType;
    /** This field specifies if request will transfer the data. 1 - data is present, 0 - no data */
    uint32_t dataPresent:1;
    /** Response type. */
    CSDD_ResponseType responseType;
    /** This variable specifies the data direction transfer */
    CSDD_TransferDirection dataTransferDirection;
    /** if the flag has a value of 1, then AutoCMD12 is enabled; value of 0 means otherwise (flag to be taken into consideration only in data transfer commands) */
    uint32_t autoCMD12Enable:1;
    /** 1 - enable Auto CMD23, 0 - disable Auto CMD23 */
    uint32_t autoCMD23Enable:1;
    /** 1 - use hardware response checking */
    uint32_t hwResponseCheck:1;
    /** 1 - APP_CMD application-specific command */
    uint32_t appCmd:1;
    /** 1 - means infinite transfer */
    uint32_t isInfinite:1;
};

/** Structure holds data transfer details */
struct CSDD_CommandField_s
{
    /** Argument of command to execute */
    uint32_t argument;
    /** Request flags */
    CSDD_RequestFlags requestFlags;
    /** Command to execute */
    uint8_t command;
    /** number of blocks to send or receive. Field to be taken into consideration only in data transfer commands */
    uint32_t blockCount;
    /** size of block data in bytes to send or receive; field to be taken into consideration only in data transfer commands */
    uint16_t blockLen;
    /** Number of sub-buffers */
    uint8_t subBuffersCount;
    /** data buffer or buffers for read/write data; field to be taken into consideration only in data transfer commands. If the SubBuffersCount parameter is 0 then it is just pointer to data. But if the SubBuffersCount is more than 0 then it is pointer to array of sub buffers. */
    void* pDataBuffer;
};

/** Structure describes a request which should be executed by host. */
struct CSDD_Request_s
{
    /** Response pointer (used in SD layer) */
    uint32_t* response;
    /** Buffer for command response */
    uint32_t responseTab[4];
    /** Current buffer position */
    void* pBufferPos;
    /** Number of bytes remaining in the transfer */
    uint32_t dataRemaining;
    /** Request status */
    volatile uint8_t status;
    /** ADMA descriptor table */
    uint32_t* admaDescriptorTable;
    /** ADMA3 integrated descriptor table */
    uint32_t* IdDescriptorTable;
    /** Pointer to SDIO host object */
    CSDD_SDIO_Host* pSdioHost;
    /** Internal field */
    uint8_t busyCheckFlags;
    /** Request type */
    uint8_t requestType;
    /** Size of response packet in bytes */
    uint8_t respSize;
    /** Response register */
    volatile uint32_t* respRegOffset;
    uint8_t infiniteStatus;
    /** slot index */
    uint8_t slotIndex;
    /** pointer to subcommand */
    CSDD_Request* subCommandRequest;
    /** Indicate request is executed as a subcommand or Main command */
    CSDD_CmdCat commandCategory;
    /** Number of command in a request. For noDMA, SDMA, ADMA1, ADMA2 must be 1 and for ADMA3 - 1 to CSDD_MAX_NUMBER_COMMAND */
    uint8_t cmdCount;
    /** Array to hold set of commands */
    CSDD_CommandField pCmd[CSDD_MAX_NUMBER_COMMAND];
};

/** structure contains info about one buffer. Used to transfer group of buffers */
struct CSDD_SubBuffer_s
{
    /** Address of sub buffer */
    uintptr_t address;
    /** Size in bytes of sub buffer */
    uint32_t size;
};

/** Structure contains information that will be used to recognize type of supported devices */
struct CSDD_DeviceInfo_s
{
    /** Manufacturer code read from SDIO card CIS registers */
    uint16_t manufacturerCode;
    /** Manufacturer information(Part Number and/or Revision) read from SDIO card CIS register */
    uint16_t manufacturerInformation;
    /** Type of device (SDIO card, SD/MMC memory card or combo card) */
    uint8_t deviceType;
    /** Function pointer which should point to interrupt function which handle SDIO card interrupt */
    CSDD_CardInterruptHandlerCallback pCardInterruptHandler;
    /** Function pointer which should point to function which initialize the card device */
    CSDD_CardInitializeCallback pCardInitialize;
    /** Function pointer which should point to function which de-initialize the card device */
    CSDD_CardDeinitializeCallback pCardDeinitialize;
};

struct CSDD_PhyDelaySettings_s
{
    /** PHY delay for SD High speed */
    uint8_t highSpeed;
    /** PHY delay for SD default speed */
    uint8_t defaultSpeed;
    /** PHY delay for SDR12 mode */
    uint8_t uhsiSdr12;
    /** PHY delay for SDR25 mode */
    uint8_t uhsiSdr25;
    /** PHY delay for SDR50 mode */
    uint8_t uhsiSdr50;
    /** PHY delay for DDR50 mode */
    uint8_t uhsiDdr50;
    /** PHY delay for eMMC legacy mode */
    uint8_t mmcLegacy;
    /** PHY delay for eMMC High speed SDR mode */
    uint8_t mmcSdr;
    /** PHY delay for eMMC High speed DDR mode */
    uint8_t mmcDdr;
    /** PHY delay for eMMC High speed HS400 mode */
    uint8_t mmcHs400;
};

struct CSDD_MemoryCardInfo_s
{
    /** block size */
    uint16_t blockSize;
    /** card command classes */
    uint16_t commandClasses;
    /** device size in MB */
    uint32_t deviceSizeMB;
    /** Defines whether partial block sizes can be used in block read commands. */
    bool partialReadAllowed;
    /** Defines whether partial block sizes can be used in block write commands. */
    bool partialWriteAlloed;
    /**  Defines if the data block to be written by one command can be  spread over more than one physical block of the memory device. */
    bool writeBlkMisalign;
    /**  Defines if the data block to be read by one command can be  spread over more than one physical block of the memory device. */
    bool readBlkMisalign;
    /** The size of an erasable sector. The content of this register is a 7-bit binary coded value, defining the number of write blocks */
    uint16_t sectorSize;
    /** The EraseBlkEn defines the granularity of the unit size of the data to be erased. */
    bool eraseBlkEn;
    /** The maximum read data block length */
    uint8_t readBlkLen;
    /** The maximum write data block length */
    uint8_t writeBlkLen;
};

struct CSDD_DeviceState_s
{
    /** is card physical located in slot */
    uint8_t inserted;
    /** is card properly detected and initialized */
    uint8_t attached;
    /** device type */
    CSDD_CardType deviceType;
    /** is Ultra High Speed I mode supported */
    uint8_t uhsSupported;
};

/** Command queuing initial configuration. */
struct CSDD_CQInitConfig_s
{
    /** Send Status Command Block Counter. if 0 then the CQE does not send CMD13 during data transfer. The value is 1, 2, or N means, the CQE sends CMD13 is transferred during last, one before last, or (N-1) before last block, respectively */
    uint8_t sendStatBlckCount;
    /** time interval of polling device status (CMD13) when controller is idle */
    uint16_t sendStatIdleTimer;
};

/** Request describing single task */
struct CSDD_CQRequestData_s
{
    /** physical address of data buffer */
    uintptr_t buffPhyAddr;
    /** Size of buffer in bytes */
    uint32_t bufferSize;
};

/** Data transfer request */
struct CSDD_CQRequest_s
{
    /** Number of blocks to be read/written */
    uint16_t blockCount;
    /** Data block address */
    uint32_t blockAddress;
    /** task ID - it must be unused */
    uint8_t taskId;
    /** it define one data buffer with data */
    CSDD_CQRequestData* buffers;
    /** number of buffers with data */
    uint8_t numberOfBuffers;
    /** context ID */
    uint8_t contextId;
    /** Data transfer direction */
    CSDD_TransferDirection transferDirection;
    /** Enable disable high priority */
    uint32_t highPriorityEn:1;
    /** Enable queue barrier */
    uint32_t queueBarrierEn:1;
    /** When 1 data shall be forcefully programmed to nonvolatile storage instead of volatile cache while cache is turned */
    uint32_t forceProgEn:1;
    /** Enable tag request */
    uint32_t tagRequestEn:1;
    /** If 1 Interrupt will be generated when interrupt coalescing conditions have been met. If 0 then interrupt will be generated when task is finished. */
    uint32_t intCoalEn:1;
    /** Enable reliable write */
    uint32_t reliableWriteEn:1;
    /** pointer to virtual memory area where descriptors can be hold. Virtual address. It is necessary if there is more than one data buffer is used. */
    uint32_t* descDataBuffer;
    /** address of physical memory area where descriptors can be hold. It is necessary if there is more than one data buffer is used. */
    uintptr_t descDataPhyAddr;
    /** size of memory area where descriptors can be hold. It is used by driver to verify if there is enough space to all transfer descriptors. It is necessary if there is more than one data buffer is used. */
    uintptr_t descDataSize;
    /** Request status. Only driver can modify it. */
    CSDD_CQReqStat cQReqStat;
};

/** Direct command request used to execute eMMC command by their index and argument. It is not used to data transfer */
struct CSDD_CQDcmdRequest_s
{
    /** The index of the command to be sent to device */
    uint8_t cmdIdx;
    /** response expected to be received from the device */
    CSDD_ResponseType responseType;
    /** argument of the command to be sent to the device */
    uint32_t argument;
    /** Enable queue barrier */
    uint32_t queueBarrierEn:1;
    /** 1 - command may be sent to device during data activity or busy, 0 - command may not be sent to device during data activity or busy */
    uint32_t cmdTiming:1;
    /** command response get from device after command execution */
    uint32_t response;
    /** Request status. Only driver can modify it. */
    CSDD_CQReqStat cQReqStat;
};

/** Command queuing interrupt coalescing configuration */
struct CSDD_CQIntCoalescingCfg_s
{
    /**  enable/disable Interrupt coalescing 1 - enable, 0 - disable */
    uint8_t enable;
    /** counter threshold number of tasks completions which are required in order to generate an interrupt */
    uint8_t threshold;
    /** timeout value */
    uint8_t timeout;
};

struct CSDD_SDIO_SlotSettings_s
{
    /** DMA 64 bit enabled */
    uint32_t DMA64_En:1;
    /** Host version 4 enabled */
    uint32_t HostVer4_En:1;
};

/** Structure defines CID register fields */
struct CSDD_SDIO_CidRegister_s
{
    /** An 8-bit binary number that identifies the card manufacturer */
    uint8_t manufacturerId;
    /** A 2-character ASCII string that identifies the card OEM and/or the card contents */
    uint16_t oemApplicationId;
    /** Product name is a string, 5-character ASCII string */
    uint8_t productName[5];
    /** The product revision is composed of two Binary Coded Decimal (BCD) digits */
    uint8_t productRevision;
    /** Product serial number */
    uint32_t productSn;
    /** Manufacturing date (year and month) */
    uint16_t manufacturingDate;
};

/** Structure contains information about inserted card and functions to handle them */
struct CSDD_SDIO_Device_s
{
    /** Type of device. Types of devices are defined here @ref Devices */
    uint8_t deviceType;
    /** Card capacity information. Types of device capacities are define here @ref Capacities */
    uint8_t DeviceCapacity;
    /** Relative card address or NODE ID */
    uint16_t RCA;
    /** Specification Version Number */
    uint8_t SpecVersNumb;
    /** Card device supported bus width. They are defined here @ref BusWidths. This parameter is logic sum of all supported bus widths */
    uint8_t SupportedBusWidths;
    /** Address of card's common Card Information Structure (CIS) */
    uint32_t CommonCISAddress;
    /** This variable defines if the card is selected or unselected */
    uint8_t IsSelected;
    /** Function pointer which should point to interrupt function which hanle card interrupt */
    CSDD_CardInterruptHandlerCallback pCardInterruptHandler;
    /** Function pointer which should point to  function which deinitialize the card device */
    CSDD_CardDeinitializeCallback pCardDeinitialize;
    /** Private driver data */
    CSDD_PMEMORY_CARD_INFO CardDriverData;
    /** Slot in which card is inserted */
    CSDD_SDIO_Slot* pSlot;
    /** Flag is set if UHS-I mode is supported by the device */
    uint8_t UhsiSupported;
    /** Flag is set if CMD23 commad is supported by the device */
    uint8_t CMD23Supported;
    /** Flag is set if CMD20 commad is supported by the device */
    uint8_t CMD20Supported;
    /** command queuing depth */
    uint8_t cQDepth;
};

/** Structure contains information a SDIO Host slot */
struct CSDD_SDIO_Slot_s
{
    /** start address of the slot registers */
    SD4HC_Regs* RegOffset;
    /** Size of buffer in the system memory which is used by DMA module */
    uint32_t DMABufferBoundary;
    /** Current selected device */
    CSDD_SDIO_Device* pDevice;
    /** These structure describes SD devices connected to the host */
    CSDD_SDIO_Device Devices[CSDD_MAX_DEV_PER_SLOT];
    /** Current set bus width. The bus widths are defined here @ref BusWidths */
    uint8_t BusWidth;
    /** Pointer to current executing SD request */
    CSDD_Request* pCurrentRequest;
    uint8_t subCommandStatus;
    /** 1 - card is inserted, 0 - there is no card in slot */
    uint32_t CardInserted:1;
    /** voltage is switched, host and sd card work in UHSI mode */
    uint32_t UhsiSelected:1;
    /** force use 3.3v voltage*/
    uint32_t Force3v3:1;
    /** Abort current transaction */
    uint8_t AbortRequest;
    /** Settings of signaling the interrupts */
    uint32_t IntSettings;
    /** Flag is set if error recovering is already executing */
    uint8_t ErrorRecorvering;
    /** pointer to the sdio host object */
    CSDD_SDIO_Host* pSdioHost;
    /** slot number */
    uint8_t SlotNr;
    /** pointer to logical address of descriptor buffer */
    uint32_t* DescriptorBuffer;
    /** pointer to physical address of descriptor buffer */
    uint32_t* DescriptorDMAAddr;
    /** pointer to logical address of ADMA3 integrated descriptor buffer */
    uint32_t* IntegratedDescriptorBuffer;
    /** pointer to physical address of ADMA3 integrated descriptor buffer */
    uint32_t* IntegratedDescriptorDMAAddr;
    /** If this flag is set then programmable clock mode is enabled, if it is 0 then 10-bit divider clock mode is enabled */
    uint32_t ProgClockMode:1;
    /** flag informs if re-tuning is currently enabled */
    uint32_t RetuningEnabled:1;
    /** fields keep info about current card access mode (UHS-I) */
    uint8_t AccessMode;
    /** flags informs if host requests for re-tuning */
    uint32_t RetuningRequest:1;
    /** data count in bytes which are transfered since last re-tuning procedure */
    uint32_t DataCount;
    /** DMA mode */
    uint8_t DmaMode;
    /** extra buffer used for read data during initialization (256 = 512/2) */
    uint32_t AuxBuff[256];
    /**  Interface type can be: - CSDD_INTERFACE_TYPE_SD */
    uint8_t InterfaceType;
    /** other slot settings */
    CSDD_SDIO_SlotSettings SlotSettings;
    /** indicate the current DMA mode */
    CSDD_DmaMode dmaModeSelected;
    /** flag is set when card is in slot but it is not attached by the driver */
    uint32_t NeedAttach:1;
    /** CQ: it informs if DCMD mode is enabled. In DCMD mode the pointer CQCurrentReq[31] is always NULL */
    uint32_t CQDcmdEnabled:1;
    /** is command queuing enabled */
    uint32_t CQEnabled:1;
    /** is command queuing halted */
    uint32_t CQHalted:1;
    /** is interrupt coalescing enabled */
    uint32_t CQIntCoalescingEn:1;
    /** pointer to logical address of task descriptor buffer */
    uint32_t* CQDescriptorBuffer;
    /** pointer to physical address of task descriptor buffer */
    uintptr_t CQDescriptorDmaAddr;
    /** pointer to current request of each normal (not DCMD) task */
    CSDD_CQ_REQUEST_PTR CQCurrentReq[32];
    /** used only if DCMD mode is enabled */
    CSDD_CQDcmdRequest* CQCurrentDcmdReq;
    /** task/transfer descriptor size in bytes */
    CSDD_EmmcCmdqTaskDescSize CQDescSize;
};

/** Structure contains information about inserted card and functions to handle them */
struct CSDD_SDIO_Host_s
{
    /** start address of the host registers */
    SD4HC_Regs* RegOffset;
    /** slots array which belong to the host */
    CSDD_SDIO_Slot Slots[SDIO_SLOT_COUNT];
    /** host bus mode (SPI SD, in the current version only SD is supported) */
    uint8_t HostBusMode;
    /** The host's slots count */
    uint8_t NumberOfSlots;
    /** Specification Version Number */
    uint8_t SpecVersNumb;
    /** callback called when card removed interrupt occurs */
    CSDD_CardRemovedCallback pCardRemoved;
    /** callback called when card inserted interrupt occurs */
    CSDD_CardInsertedCallback pCardInserted;
    /** function pointer which point to function which handle mmc tunning */
    CSDD_SetTuneValCallback pSetTuneVal;
    /** callback called when AXI error occurs */
    CSDD_AxiErrorCallback axiErrorCallback;
    /** pointer to user driver data */
    void* drvData;
    /** interrupts enabled */
    uint32_t intEn:1;
    /** DMA 64 bit enable */
    uint32_t dma64BitEn:1;
    /** emmc command queueing is supported */
    bool cqSupported;
    /** HS 400ES supported */
    bool hs400EsSupported;
    /** Host Controller Version */
    uint16_t hostCtrlVer;
    /** Fix Version Number : Number of the fix related to the Host Controller Version. */
    uint8_t HostFixVer;
};

/**
 * Function pointers to event notification callbacks issued
 * by driver functions when interrupt occurs.
 * Each call passes the drivers privateData pointer and slotIndex for instance
 * identification if necessary.
*/
struct CSDD_Callbacks_s
{
    CSDD_CardInsertedCallback cardInsertedCallback;
    CSDD_CardRemovedCallback cardRemovedCallback;
    CSDD_AxiErrorCallback axiErrorCallback;
    CSDD_SetTuneValCallback setTuneValCallback;
};

/** Controls the IO delay related timings - Combo PHY */
struct CSDD_CPhyConfigIoDelay_s
{
    uint8_t rwCompensate;
    uint8_t idelayVal;
};

/** Controls LVSI related timings - Combo PHY */
struct CSDD_CPhyConfigLvsi_s
{
    uint8_t lvsiCnt;
    uint8_t lvsiTcksel;
};

/** Controls rddata and rdcmd parameters - Combo PHY */
struct CSDD_CPhyConfigDfiRd_s
{
    uint8_t rddataSwap;
    uint8_t rddataEn;
    uint8_t rdcmdEn;
};

/** Controls CMD DAT output delay related timings - Combo PHY */
struct CSDD_CPhyConfigOutputDelay_s
{
    uint8_t wrdata1SdclkDly;
    uint8_t wrdata0SdclkDly;
    uint8_t wrcmd1SdclkDly;
    uint8_t wrcmd0SdclkDly;
    uint8_t wrdata1Dly;
    uint8_t wrdata0Dly;
    uint8_t wrcmd1Dly;
    uint8_t wrcmd0Dly;
};

/**
 *  @}
 */

#endif	/* CSDD_STRUCTS_IF_H */
