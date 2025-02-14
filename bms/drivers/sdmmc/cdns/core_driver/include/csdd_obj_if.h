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
#ifndef CSDD_OBJ_IF_H
#define CSDD_OBJ_IF_H

#include "csdd_if.h"

/** @defgroup DriverObject Driver API Object
 *  API listing for the driver. The API is contained in the object as
 *  function pointers in the object structure. As the actual functions
 *  resides in the Driver Object, the client software must first use the
 *  global GetInstance function to obtain the Driver Object Pointer.
 *  The actual APIs then can be invoked using obj->(api_name)() syntax.
 *  These functions are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/

/* parasoft-begin-suppress MISRA2012-DIR-4_8-4 "Consider hiding the implementation of the structure, DRV-4932" */
typedef struct CSDD_OBJ_s
{
    /**
     * @param[in] registerBase base address of controller registers
     * @param[out] req
     * @return 0 on success
     * @return ENOTSUP if configuration cannot be supported due to driver/hardware constraints
     */
    uint32_t (*probe)(uintptr_t registerBase, CSDD_SysReq* req);

    /**
     * Function initializes all objects. It must be called as the first
     * function before calling other driver functions
     * @param[in] pD private data
     * @param[in] config startup configuration
     * @param[in] callbacks pointer to callbacks functions
     * @return 0 on success or error code otherwise
     */
    uint32_t (*init)(CSDD_SDIO_Host* pD, CSDD_Config* config, CSDD_Callbacks* callbacks);

    /**
     * Enable signaling interrupts
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*start)(CSDD_SDIO_Host* pD);

    /**
     * Disable signaling interrupts
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*stop)(CSDD_SDIO_Host* pD);

    /**
     * Function executes a request which is given as the request
     * parameter
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] request request to execute
     * @return 0 on success or error code otherwise
     */
    uint32_t (*execCardCommand)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_Request* request);

    /**
     * Function detaches card, meaning that all information about card is
     * removed in this function
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @return 0 on success or error code otherwise
     */
    uint32_t (*deviceDetach)(CSDD_SDIO_Host* pD, uint8_t slotIndex);

    /**
     * Function initializes a newly inserted card, gathers information
     * about it, and searches for card driver
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @return 0 on success or error code otherwise
     */
    uint32_t (*deviceAttach)(CSDD_SDIO_Host* pD, uint8_t slotIndex);

    /**
     * function aborts data transfer
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] isSynchronous abort type: synchronous or asynchronous
     * @return 0 on success or error code otherwise
     */
    uint32_t (*abort)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t isSynchronous);

    /**
     * sets slot of SD host controller to standby mode and waits for
     * wakeup condition; in standby mode the clock is disabled
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] wakeupCondition conditions of wakeup from standby mode
     * @return 0 on success or error code otherwise
     */
    uint32_t (*standBy)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t wakeupCondition);

    /**
     * configures the SD Host controller
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] cmd it describes what should be configured
     * @param[in] data buffer with configuration data
     * @param[in] sizeOfData size of data buffer in bytes
     * @return 0 on success or error code otherwise
     */
    uint32_t (*configure)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ConfigCmd cmd, void* data, uint8_t* sizeOfData);

    /**
     * interrupt handler function, it should be called to handle SD host
     * interrupts
     * @param[in] pD private data
     * @param[in] handled informs if interrupt occurred
     */
    void (*isr)(CSDD_SDIO_Host* pD, bool* handled);

    /**
     * switches a card and host to work either in high speed mode or in
     * normal mode
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] setHighSpeed defines if high speed mode will be enabled SetHighSpeed = 1) or disabled (SetHighSpeed = 0)
     * @return 0 on success or error code otherwise
     */
    uint32_t (*configureHighSpeed)(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool setHighSpeed);

    /**
     * checks slots states; depending on the slots status, calls
     * deviceAttach or deviceDettach, or does nothing if slot state
     * remains unchanged
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*checkSlots)(CSDD_SDIO_Host* pD);

    /**
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] status
     */
    void (*checkInterrupt)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t status);

    /**
     * Function configures card access mode
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] accessMode access mode to set
     * @return 0 on success or error code otherwise
     */
    uint32_t (*configureAccessMode)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_SpeedMode accessMode);

    /**
     * function executes tuning operation on a card but only if it is
     * needed
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @return 0 on success or error code otherwise
     */
    uint32_t (*tuning)(CSDD_SDIO_Host* pD, uint8_t slotIndex);

    /**
     * function executes tuning operation on a card but only if it is
     * needed
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] progClkMode parameter defines if programmable clock mode should be enabled. 1  programmable clock mode will be enabled; 0  10-bit divider clock mode is enabled
     * @return 0 on success or error code otherwise
     */
    uint32_t (*clockGeneratorSelect)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t progClkMode);

    /**
     * Function enables or disables preset value switching
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] enable enable/disable preset value switching
     * @return 0 on success or error code otherwise
     */
    uint32_t (*presetValueSwitch)(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool enable);

    /**
     * function configures driver strength of a card and the slot
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] driverStrength new driver strength
     * @return 0 on success or error code otherwise
     */
    uint32_t (*configureDriverStrength)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverStrengthType driverStrength);

    /**
     * Function loads driver for the card
     * @param[in] pD private data
     */
    void (*memoryCardLoadDriver)(CSDD_SDIO_Host* pD);

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
    uint32_t (*memoryCardDataTransfer)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction);

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
    uint32_t (*memoryCardDataTransfer2)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction, uint32_t subBufferCount);

    /**
     * function executes configuration commands on memory card
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] cmd this parameter defines what operation will be executed
     * @param[in] data buffer with data
     * @param[in] size size of data in bytes
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memoryCardConfigure)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_MmcConfigCmd cmd, uint8_t* data, uint8_t size);

    /**
     * Function erases block or blocks specified by startBlockAddress and
     * blockCount parameteres.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] startBlockAddress address of the first block to be erased
     * @param[in] blockCount number of blocks to be erased.
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memoryCardDataErase)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t startBlockAddress, uint32_t blockCount);

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
    uint32_t (*memCardPartialDataXfer)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction);

    /**
     * Function transfers data in infinite mode to/from memory card.
     * Function operates on 512 data blocks. Data transfer can be
     * continiued by memCardInfXferContinue. Trnasmission must be
     * finished by memCardInfXferFinish
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] address address in card memory to/from which data will be transferred; address in blocks (512 bytes)
     * @param[in,out] buffer buffer with data to be written or to save data that was read
     * @param[in] size size of buffer in bytes
     * @param[in] direction parameter defines transfer direction
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memCardInfXferStart)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction);

    /**
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in,out] buffer buffer with data to be written or to save data that was read
     * @param[in] size size of buffer in bytes
     * @param[in] direction parameter defines transfer direction
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memCardInfXferContinue)(CSDD_SDIO_Host* pD, uint8_t slotIndex, void* buffer, uint32_t size, CSDD_TransferDirection direction);

    /**
     * Function finishes data transfer in infinite mode
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] direction parameter defines transfer direction
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memCardInfXferFinish)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_TransferDirection direction);

    /**
     * Function transfers data to/from memory card. Function operates on
     * 512 data blocks. Function does not wait for operation finish.
     * Therefore it returns pointer to current request. User using
     * MemoryCard_FinishXferNonBlock function and request pointer can
     * wait until operation finish and get the status of operation.
     * Function needs AUTO_CMD option enabled
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] address address in card memory to/from which data will be transferred; address in blocks (512 bytes)
     * @param[in,out] buffer buffer with data to be written or to save data that was read
     * @param[in] size size of buffer in bytes
     * @param[in] direction parameter defines transfer direction
     * @param[out] request current executing request
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memCardDataXferNonBlock)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction, void** request);

    /**
     * Function waits until request finish and returns status of request
     * execution
     * @param[in] pD private data
     * @param[in] pRequest request to wait for
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memCardFinishXferNonBlock)(CSDD_SDIO_Host* pD, CSDD_Request* pRequest);

    /**
     * Function sets delay line in UHS-I PHY hardware module. Function
     * works for SD Host 3 Function is obsolete writePhySet function
     * should be used to configure PHY delays.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] phyDelaySet PHY delay settings
     * @return 0 on success or error code otherwise
     */
    uint32_t (*phySettingsSd3)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelaySettings* phyDelaySet);

    /**
     * Function sets delay line in UHS-I PHY hardware module. Function
     * works for SD Host 4. Function is obsolete writePhySet function
     * should be used to configure PHY delays.
     * @param[in] pD private data
     * @param[in] phyDelaySet PHY delay settings
     * @return 0 on success or error code otherwise
     */
    uint32_t (*phySettingsSd4)(CSDD_SDIO_Host* pD, CSDD_PhyDelaySettings* phyDelaySet);

    /**
     * Function configures one PHY delay line in UHS-I PHY hardware
     * module.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] phyDelayType it defines which PHY delay should be written
     * @param[in] delayVal value to be written to selected PHY delay
     * @return 0 on success or error code otherwise
     */
    uint32_t (*writePhySet)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelay phyDelayType, uint8_t delayVal);

    /**
     * Function configures one PHY delay line in UHS-I PHY hardware
     * module.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] phyDelayType it defines which PHY delay should be read:
     * @param[in] delayVal read value of selected PHY delay
     * @return 0 on success or error code otherwise
     */
    uint32_t (*readPhySet)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelay phyDelayType, uint8_t* delayVal);

    /**
     * reads card status. Function returns error if command executing
     * error appears or card error bits are set
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] cardStatus pointer to memory where read card status shall be written
     * @return 0 on success or error code otherwise
     */
    uint32_t (*readCardStatus)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* cardStatus);

    /**
     * selects or deselects a card; if RCA parameter is 0, then card will
     * be deselected, otherwise,a card of the RCA value will be selected
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] rca card address in selecting card case or 0 in deselecting card case
     * @return 0 on success or error code otherwise
     */
    uint32_t (*selectCard)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint16_t rca);

    /**
     * resets a card using CMD0 command
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @return 0 on success or error code otherwise
     */
    uint32_t (*resetCard)(CSDD_SDIO_Host* pD, uint8_t slotIndex);

    /**
     * executes CMD55 command
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @return 0 on success or error code otherwise
     */
    uint32_t (*execCmd55Command)(CSDD_SDIO_Host* pD, uint8_t slotIndex);

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
    uint32_t (*accessCccr)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_TransferDirection transferDirection, void* data, uint8_t size, CSDD_CccrRegAddr registerAddress);

    /**
     * reads CSD register of the card
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] buffer content of CSD register 16 bytes
     * @return 0 on success or error code otherwise
     */
    uint32_t (*readCsd)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t buffer[4]);

    /**
     * function reads Extended CSD register from the card
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] buffer
     * @return 0 on success or error code otherwise
     */
    uint32_t (*readExCsd)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t* buffer);

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
    uint32_t (*getTupleFromCis)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t tupleAddress, CSDD_TupleCode tupleCode, void* buffer, uint8_t bufferSize);

    /**
     * function reads SD card status
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] buffer card status
     * @return 0 on success or error code otherwise
     */
    uint32_t (*readSdStatus)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t buffer[64]);

    /**
     * Function configures driver strength of a card
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] driverStrength new driver strength value
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setDriverStrength)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverStrengthType driverStrength);

    /**
     * Function sets a card current limit.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] currentLimit
     * @return 0 on success or error code otherwise
     */
    uint32_t (*execSetCurrentLimit)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverCurrentLimit currentLimit);

    /**
     * Function executes mmc switch command to modify EXT_CSD register.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] argIndex index of EXT_CSD register field to be modified
     * @param[in] argValue new value to be set
     * @return 0 on success or error code otherwise
     */
    uint32_t (*mmcSwitch)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t argIndex, uint8_t argValue);

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
    uint32_t (*mmcSetExtCsd)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t byteNr, uint8_t newValue, uint8_t mask);

    /**
     * Function sets active partition to boot operation.
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] partition partition to be active to boot
     * @return 0 on success or error code otherwise
     */
    uint32_t (*mmcSetBootPartition)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ParitionBoot partition);

    /**
     * Function sets active partition to access
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] partition partition to be active to access
     * @return 0 on success or error code otherwise
     */
    uint32_t (*mmcSetPartAccess)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ParitionAccess partition);

    /**
     * Function sets active partition to access
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] enableBootAck enable/disable eMMC boot ACK
     * @return 0 on success or error code otherwise
     */
    uint32_t (*mmcSetBootAck)(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool enableBootAck);

    /**
     * Function executes boot operation. It reads data from active boot
     * partition to the buffer
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] buffer buffer for read
     * @param[in] size buffer size in bytes
     * @return 0 on success or error code otherwise
     */
    uint32_t (*mmcExecuteBoot)(CSDD_SDIO_Host* pD, uint8_t slotIndex, void* buffer, uint32_t size);

    /**
     * Function gets boot partition size
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] bootSize size of boot partition
     * @return 0 on success or error code otherwise
     */
    uint32_t (*mmcGetParitionBootSize)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* bootSize);

    /**
     * function gets current device interface type (SD legacy)
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] interfaceType interface type
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getInterfaceType)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_InterfaceType* interfaceType);

    /**
     * function gets current device state/info
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] deviceState device state and info
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getDeviceState)(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DeviceState* deviceState);

    /**
     * Function gets sectors count
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] sectorCount sector count
     * @return 0 on success or error code otherwise
     */
    uint32_t (*memoryCardGetSecCount)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* sectorCount);

    /**
     * Function used to save pointer to driver data
     * @param[in] pD private data
     * @param[in] drvData driver data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setDriverData)(CSDD_SDIO_Host* pD, void* drvData);

    /**
     * Function used get pointer to driver data saved by setDriverData
     * function
     * @param[in] pD private data
     * @param[out] drvData driver data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getDriverData)(CSDD_SDIO_Host* pD, const void** drvData);

    /**
     * Function makes very simple host initialization just enables clock
     * and supply the power. Function is useful for emmc boot operation
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[in] clk clock frequency in hertz
     * @return 0 on success or error code otherwise
     */
    uint32_t (*simpleInit)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t clk);

    /**
     * Function resets SD Host controller
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*resetHost)(CSDD_SDIO_Host* pD);

    /**
     * Function gets RCA address of conneted device
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] rca RCA address
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getRca)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint16_t* rca);

    /**
     * Function enables command queuing and set initialize configuration
     * @param[in] pD private data
     * @param[in] cqConfig Initial configuration.
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQEnable)(CSDD_SDIO_Host* pD, CSDD_CQInitConfig* cqConfig);

    /**
     * Function disables command queuing
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQDisable)(CSDD_SDIO_Host* pD);

    /**
     * Function get command queuing initial configuration passed in in
     * cQEnable function
     * @param[in] pD private data
     * @param[out] cqConfig current command queue configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQGetInitConfig)(CSDD_SDIO_Host* pD, CSDD_CQInitConfig* cqConfig);

    /**
     * Function searches and gets unused task ID
     * @param[in] pD private data
     * @param[out] taskId unused task ID
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQGetUnusedTaskId)(CSDD_SDIO_Host* pD, uint8_t* taskId);

    /**
     * Function starts task execution. Task must be attached before by
     * cQAttachRequest function
     * @param[in] pD private data
     * @param[in] taskId task ID which shall be executed
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQStartExecuteTask)(CSDD_SDIO_Host* pD, uint8_t taskId);

    /**
     * Function attaches new request to a task. Function create new
     * descriptors. Function cannot be used to attach direct requests.
     * Execution of request is not started by this function.
     * @param[in] pD private data
     * @param[in] request a request to be attached
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQAttachRequest)(CSDD_SDIO_Host* pD, CSDD_CQRequest* request);

    /**
     * Function attaches new request to the direct task. Function create
     * new descriptors. Function start of execution direct task. Function
     * can be only to direct requests.
     * @param[in] pD private data
     * @param[in] request a direct request to be executed
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQExecuteDcmdRequest)(CSDD_SDIO_Host* pD, CSDD_CQDcmdRequest* request);

    /**
     * Function gets current configuration of command queuing direct
     * command
     * @param[in] pD private data
     * @param[out] enable it informs if direct command is enabled or disabled
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQGetDirectCmdConfig)(CSDD_SDIO_Host* pD, uint8_t* enable);

    /**
     * Function sets new configuration of command queuing direct command
     * @param[in] pD private data
     * @param[out] enable if it is then direct command will be enabled, if it is 0 then direct command will be disabled
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQSetDirectCmdConfig)(CSDD_SDIO_Host* pD, uint8_t enable);

    /**
     * Function sets new configuration of command queuing interrupt
     * coalescing
     * @param[in] pD private data
     * @param[int] config new interrupt coalescing configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQSetIntCoalescingConfig)(CSDD_SDIO_Host* pD, CSDD_CQIntCoalescingCfg* config);

    /**
     * Function gets current configuration of command queuing interrupt
     * coalescing
     * @param[in] pD private data
     * @param[out] config current interrupt coalescing configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQGetIntCoalescingConfig)(CSDD_SDIO_Host* pD, CSDD_CQIntCoalescingCfg* config);

    /**
     * Function gets current configuration of command queuing interrupt
     * coalescing
     * @param[in] pD private data
     * @param[out] clockFreqKHz interrupt coalescing timeout base clock frequency in KHz. It can be usefull to calculate interrupt coalescing timeout value
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQGetIntCoalescingTimeoutBase)(CSDD_SDIO_Host* pD, uint32_t* clockFreqKHz);

    /**
     * Function starts tasks execution. Tasks must be attached before by
     * cQAttachRequest function
     * @param[in] pD private data
     * @param[in] taskIds task IDs OR'd combination of bit-flags selecting the tasks to be executed. Bit 0 - task ID 0, bit 1 task ID 1 ...
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQStartExecuteTasks)(CSDD_SDIO_Host* pD, uint32_t taskIds);

    /**
     * Function put command queueing to halt state or exit from halt
     * state. Behaviour depends on set parameter.
     * @param[in] pD private data
     * @param[in] set 1 - enter to halt state, 0 - exit from halt state
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQHalt)(CSDD_SDIO_Host* pD, uint8_t set);

    /**
     * Function dicards one task
     * @param[in] pD private data
     * @param[in] taskId task ID to discard
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQTaskDiscard)(CSDD_SDIO_Host* pD, uint8_t taskId);

    /**
     * Function dicards all tasks
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQAllTasksDiscard)(CSDD_SDIO_Host* pD);

    /**
     * Function resets interrupt coalescing timer and counter
     * @param[in] pD private data
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQResetIntCoalCounters)(CSDD_SDIO_Host* pD);

    /**
     * Function writes error mask for command response.
     * @param[in] pD private data
     * @param[in] errorMask bit mask informs CQ engine which bits should be treated as error in command response
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQSetResponseErrorMask)(CSDD_SDIO_Host* pD, uint32_t errorMask);

    /**
     * Function reads error mask for command response.
     * @param[in] pD private data
     * @param[out] errorMask bit mask informs CQ engine which bits should be treated as error in command response
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cQGetResponseErrorMask)(CSDD_SDIO_Host* pD, uint32_t* errorMask);

    /**
     * Function reads base clock
     * @param[in] pD private data
     * @param[in] slotIndex slot index
     * @param[out] frequencyKHz base clock
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getBaseClk)(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* frequencyKHz);

    /**
     * Function waits until request finish and returns status of request
     * execution
     * @param[in] pD private data
     * @param[in] pRequest request to wait for
     * @return 0 on success or error code otherwise
     */
    uint32_t (*waitForRequest)(CSDD_SDIO_Host* pD, CSDD_Request* pRequest);

    /**
     * @param[in] pD private data
     * @param[in] ioDelay configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setCPhyConfigIoDelay)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigIoDelay* ioDelay);

    /**
     * @param[in] pD private data
     * @param[out] ioDelay configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getCPhyConfigIoDelay)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigIoDelay* ioDelay);

    /**
     * @param[in] pD private data
     * @param[in] lvsi configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setCPhyConfigLvsi)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigLvsi* lvsi);

    /**
     * @param[in] pD private data
     * @param[out] lvsi configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getCPhyConfigLvsi)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigLvsi* lvsi);

    /**
     * @param[in] pD private data
     * @param[in] dfiRd configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setCPhyConfigDfiRd)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigDfiRd* dfiRd);

    /**
     * @param[in] pD private data
     * @param[out] dfiRd configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getCPhyConfigDfiRd)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigDfiRd* dfiRd);

    /**
     * @param[in] pD private data
     * @param[in] outputDelay configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setCPhyConfigOutputDelay)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigOutputDelay* outputDelay);

    /**
     * @param[in] pD private data
     * @param[out] outputDelay configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getCPhyConfigOutputDelay)(CSDD_SDIO_Host* pD, CSDD_CPhyConfigOutputDelay* outputDelay);

    /**
     * @param[in] pD private data
     * @param[in] doReset enable/disable reset
     * @return 0 on success or error code otherwise
     */
    uint32_t (*cPhyDllReset)(CSDD_SDIO_Host* pD, bool doReset);

    /**
     * @param[in] pD private data
     * @param[in] extendedWrMode
     * @param[in] extendedRdMode
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setCPhyExtMode)(CSDD_SDIO_Host* pD, bool extendedWrMode, bool extendedRdMode);

    /**
     * @param[in] pD private data
     * @param[out] extendedWrMode
     * @param[out] extendedRdMode
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getCPhyExtMode)(CSDD_SDIO_Host* pD, bool* extendedWrMode, bool* extendedRdMode);

    /**
     * @param[in] pD private data
     * @param[in] sdclkAdj configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*setCPhySdclkAdj)(CSDD_SDIO_Host* pD, uint8_t sdclkAdj);

    /**
     * @param[in] pD private data
     * @param[out] sdclkAdj configuration
     * @return 0 on success or error code otherwise
     */
    uint32_t (*getCPhySdclkAdj)(CSDD_SDIO_Host* pD, uint8_t* sdclkAdj);

} CSDD_OBJ;
/* parasoft-end-suppress MISRA2012-DIR-4_8-4 */

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3666" */
/**
 * In order to access the CSDD APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CSDD_OBJ* Driver Object Pointer
 */
extern CSDD_OBJ *CSDD_GetInstance(void);

/**
 *  @}
 */
/* parasoft-end-suppress METRICS-36-3 */


#endif	/* CSDD_OBJ_IF_H */
