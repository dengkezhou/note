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
#ifndef XSPI_OBJ_IF_H
#define XSPI_OBJ_IF_H

#include "xspi_if.h"

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
typedef struct XSPI_OBJ_s
{
    /**
     * Gets the driver memory requirements to support specified
     * configuration
     * @param[in] config Driver/hardware configuration required.
     * @param[out] sysReq Returns the size of memory allocations required.
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*probe)(XSPI_Config* config, XSPI_SysReq* sysReq);

    /**
     * Initialize the driver as specified in the Config structure. Must
     * be called before all other access APIs.
     * @param[in] privateData Memory pointer to the uninitialized private data of the size specified by probe.
     * @param[in] config Specifies driver/hardware configuration.
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*init)(XSPI_PrivateData* privateData, const XSPI_Config* config);

    /**
     * Destructor for the driver
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*destroy)(XSPI_PrivateData* privateData);

    /**
     * "Start the XSPI driver, enabling interrupts.   This is called
     * after the client has successfully initialized the driver and
     * hooked   the driver's ISR (the isr member of this struct) to the
     * IRQ."
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*start)(XSPI_PrivateData* privateData);

    /**
     * Stops the XSPI driver by disabling interrupts.
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*stop)(XSPI_PrivateData* privateData);

    /**
     * "Driver ISR. Platform-specific code is responsible for ensuring
     * this gets called when the corresponding hardware's interrupt is
     * asserted. Registering the ISR should be done after calling init,
     * and before calling start. The driver's ISR will not attempt to
     * lock any locks, but will perform client callbacks. If the client
     * wishes to defer processing to non-interrupt time, it is
     * responsible for doing so. This function must not be called after
     * calling destroy and releasing private data memory."
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*isr)(XSPI_PrivateData* privateData);

    /**
     * Sets controller's work mode
     * @param[in] privateData Pointer to driver private data object
     * @param[in] workMode Controller work mode to be set
     * @return CDN_EOK On success
     * @return CDN_EINVAL If workMode is invalid
     * @return CDN_EBUSY When controller is busy
     */
    uint32_t (*setWorkMode)(XSPI_PrivateData* privateData, const XSPI_WorkMode workMode);

    /**
     * Gets controller's current work mode
     * @param[in] privateData Pointer to driver private data object
     * @param[out] workMode Controller work mode
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getWorkMode)(XSPI_PrivateData* privateData, XSPI_WorkMode* workMode);

    /**
     * Sets events to enable or disable corresponding interrupts
     * @param[in] privateData Pointer to driver private data object
     * @param[in] events Mask of Events to be enabled or disabled.
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setEventEnable)(XSPI_PrivateData* privateData, uint32_t events);

    /**
     * Gets enabled events
     * @param[in] privateData Pointer to driver private data object
     * @param[out] events Enabled events
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getEventEnable)(XSPI_PrivateData* privateData, uint32_t* events);

    /**
     * Sets callbacks for different events
     * @param[in] privateData Pointer to driver private data object
     * @param[in] callbacks Callback functions to register
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setCallbacks)(XSPI_PrivateData* privateData, const XSPI_Callbacks callbacks);

    /**
     * Gets registered callback functions
     * @param[in] privateData Pointer to driver private data object
     * @param[out] callbacks Returns registered callbacks
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getCallbacks)(const XSPI_PrivateData* privateData, XSPI_Callbacks* callbacks);

    /**
     * Sets write protection state for all devices
     * @param[in] privateData Pointer to driver private data object
     * @param[in] writeProtectEnabled Write protect state
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_EBUSY When controller is busy
     */
    uint32_t (*setWriteProtect)(XSPI_PrivateData* privateData, bool writeProtectEnabled);

    /**
     * Gets write protection state
     * @param[in] privateData Pointer to driver private data object
     * @param[out] writeProtectEnabled Write protect state
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getWriteProtect)(XSPI_PrivateData* privateData, bool* writeProtectEnabled);

    /**
     * Sets DMA configuration
     * @param[in] privateData Pointer to driver private data object
     * @param[in] dmaConfig DMA configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setDmaConfig)(XSPI_PrivateData* privateData, const XSPI_DmaConfig* dmaConfig);

    /**
     * Gets DMA configuration
     * @param[in] privateData Pointer to driver private data object
     * @param[out] dmaConfig DMA configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getDmaConfig)(XSPI_PrivateData* privateData, XSPI_DmaConfig* dmaConfig);

    /**
     * Sets SPI clock mode. Allowed to change for SDR transfers only.
     * @param[in] privateData Pointer to driver private data object
     * @param[in] spiClockMode SPI clock mode
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setSpiClockMode)(XSPI_PrivateData* privateData, XSPI_SpiClockMode spiClockMode);

    /**
     * Gets SPI clock mode
     * @param[in] privateData Pointer to driver private data object
     * @param[out] spiClockMode SPI clock mode
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getSpiClockMode)(XSPI_PrivateData* privateData, XSPI_SpiClockMode* spiClockMode);

    /**
     * Function gets the reset configuration currently set.
     * @param[in] privateData Pointer to driver private data object
     * @param[in] resetBankCfg Reset configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getResetConfig)(XSPI_PrivateData* privateData, XSPI_ResetDeviceConfig* resetBankCfg);

    /**
     * Function sets the reset configuration which is used to reset
     * memory banks.
     * @param[in] privateData Pointer to driver private data object
     * @param[in] resetBankCfg Reset configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setResetConfig)(XSPI_PrivateData* privateData, const XSPI_ResetDeviceConfig* resetBankCfg);

    /**
     * Asserts the software controlled hardware reset signal. Reset
     * configuration must be set before calling this function.
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_EBUSY When controller is busy
     */
    uint32_t (*assertReset)(XSPI_PrivateData* privateData);

    /**
     * Deasserts the software controlled hardware reset signal.
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_EBUSY When controller is busy
     */
    uint32_t (*deAssertReset)(XSPI_PrivateData* privateData);

    /**
     * Sets relative device selection and reset recovery delays
     * @param[in] privateData Pointer to driver private data object
     * @param[in] deviceRelativeDelays Device relative delays
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setDeviceRelativeDelays)(XSPI_PrivateData* privateData, const XSPI_DeviceRelativeDelays* deviceRelativeDelays);

    /**
     * Gets device relative delays
     * @param[in] privateData Pointer to driver private data object
     * @param[out] deviceRelativeDelays Device relative delays
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getDeviceRelativeDelays)(XSPI_PrivateData* privateData, XSPI_DeviceRelativeDelays* deviceRelativeDelays);

    /**
     * Sets global command parameters having common values for sequences
     * in CDMA, PIO and Direct work modes
     * @param[in] privateData Pointer to driver private data object
     * @param[in] globalCmdParameters Global command parameters
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setGlobalCmdParameters)(XSPI_PrivateData* privateData, const XSPI_GlobalCommandParameters* globalCmdParameters);

    /**
     * Gets global command parameters having common values for sequences
     * in CDMA, PIO and Direct work modes
     * @param[in] privateData Pointer to driver private data object
     * @param[out] globalCmdParameters Global command parameters
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getGlobalCmdParameters)(XSPI_PrivateData* privateData, XSPI_GlobalCommandParameters* globalCmdParameters);

    /**
     * Sets global command parameters for SPI NAND devices (Since R003)
     * @param[in] privateData Pointer to driver private data object
     * @param[in] spiNandCmdParams SPI NAND global command parameters
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*setSpiNandCmdParameters)(XSPI_PrivateData* privateData, const XSPI_SpiNandGlobCmdParams* spiNandCmdParams);

    /**
     * Gets global command parameters for SPI NAND devices (Since R003)
     * @param[in] privateData Pointer to driver private data object
     * @param[out] spiNandCmdParams SPI NAND global command parameters
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*getSpiNandCmdParameters)(XSPI_PrivateData* privateData, XSPI_SpiNandGlobCmdParams* spiNandCmdParams);

    /**
     * Sets XIP mode bits
     * @param[in] privateData Pointer to driver private data object
     * @param[in] xipModeBitsConfig XIP mode bits config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setXipModeBitsConfig)(XSPI_PrivateData* privateData, const XSPI_XipModeBitsConfig* xipModeBitsConfig);

    /**
     * Gets XIP mode bits
     * @param[in] privateData Pointer to driver private data object
     * @param[out] xipModeBitsConfig XIP mode bits config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getXipModeBitsConfig)(XSPI_PrivateData* privateData, XSPI_XipModeBitsConfig* xipModeBitsConfig);

    /**
     * Send command in Direct mode
     * @param[in] privateData Pointer to driver private data object
     * @param[in] directCmd Pointer to direct mode command structure
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*sendDirectCommand)(XSPI_PrivateData* privateData, const XSPI_DirectCmd* directCmd);

    /**
     * Checks busy status of Direct command generator module
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_EBUSY When controller is busy
     */
    uint32_t (*isDirectCmdEngBusy)(XSPI_PrivateData* privateData);

    /**
     * Sets direct work mode config
     * @param[in] privateData Pointer to driver private data object
     * @param[in] directModeConfig Pointer to direct mode config structure
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setDirectModeConfig)(XSPI_PrivateData* privateData, const XSPI_DirectModeConfig* directModeConfig);

    /**
     * Gets direct work mode config
     * @param[in] privateData Pointer to driver private data object
     * @param[out] directModeConfig Pointer to direct mode config structure
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getDirectModeConfig)(XSPI_PrivateData* privateData, XSPI_DirectModeConfig* directModeConfig);

    /**
     * Sets maximum number of xspi_clk cycles through CS# will be active
     * @param[in] privateData Pointer to driver private data object
     * @param[in] activeDevMaxCycles Active device max cycles (HyperRAM only)
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setP2ActiveDevMaxCycles)(XSPI_PrivateData* privateData, uint32_t activeDevMaxCycles);

    /**
     * Gets maximum number of xspi_clk cycles through CS# will be active
     * @param[in] privateData Pointer to driver private data object
     * @param[out] activeDevMaxCycles Active device max cycles (HyperRAM only)
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getP2ActiveDevMaxCycles)(XSPI_PrivateData* privateData, uint32_t* activeDevMaxCycles);

    /**
     * Sets PROGRAM sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[in] progSeqP1Cfg PROGRAM P1 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setProgramSeqP1Config)(XSPI_PrivateData* privateData, const XSPI_ProgramSeqP1Config* progSeqP1Cfg);

    /**
     * Gets PROGRAM sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[out] progSeqP1Cfg PROGRAM P1 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getProgramSeqP1Config)(XSPI_PrivateData* privateData, XSPI_ProgramSeqP1Config* progSeqP1Cfg);

    /**
     * Sets PROGRAM sequence configuration for Profile 2
     * @param[in] privateData Pointer to driver private data object
     * @param[in] progSeqP2Cfg PROGRAM P2 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setProgramSeqP2Config)(XSPI_PrivateData* privateData, const XSPI_ProgramSeqP2Config* progSeqP2Cfg);

    /**
     * Gets PROGRAM sequence configuration for Profile 2
     * @param[in] privateData Pointer to driver private data object
     * @param[out] progSeqP2Cfg PROGRAM P2 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getProgramSeqP2Config)(XSPI_PrivateData* privateData, XSPI_ProgramSeqP2Config* progSeqP2Cfg);

    /**
     * Sets READ sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[in] readSeqP1Cfg READ P1 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setReadSeqP1Config)(XSPI_PrivateData* privateData, const XSPI_ReadSeqP1Config* readSeqP1Cfg);

    /**
     * Gets READ sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[out] readSeqP1Cfg READ P1 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getReadSeqP1Config)(XSPI_PrivateData* privateData, XSPI_ReadSeqP1Config* readSeqP1Cfg);

    /**
     * Sets READ sequence configuration for Profile 2
     * @param[in] privateData Pointer to driver private data object
     * @param[in] readSeqP2Cfg READ P2 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setReadSeqP2Config)(XSPI_PrivateData* privateData, const XSPI_ReadSeqP2Config* readSeqP2Cfg);

    /**
     * Gets READ sequence configuration for Profile 2
     * @param[in] privateData Pointer to driver private data object
     * @param[out] readSeqP2Cfg READ P2 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getReadSeqP2Config)(XSPI_PrivateData* privateData, XSPI_ReadSeqP2Config* readSeqP2Cfg);

    /**
     * Sets Write Enable(WEL) sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[in] welSeqCfg WEL sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setWelSeqConfig)(XSPI_PrivateData* privateData, const XSPI_WelSeqConfig* welSeqCfg);

    /**
     * Gets Write Enable(WEL) sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[out] welSeqCfg WEL sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getWelSeqConfig)(XSPI_PrivateData* privateData, XSPI_WelSeqConfig* welSeqCfg);

    /**
     * Sets status checking sequence configuration common for Profile 1
     * and 2
     * @param[in] privateData Pointer to driver private data object
     * @param[in] commStatSeqConfig Common STAT sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setCommStatSeqConfig)(XSPI_PrivateData* privateData, const XSPI_CommStatSeqConfig* commStatSeqConfig);

    /**
     * Gets status checking sequence configuration common for Profile 1
     * and 2
     * @param[in] privateData Pointer to driver private data object
     * @param[out] commStatSeqConfig Common STAT sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getCommStatSeqConfig)(XSPI_PrivateData* privateData, XSPI_CommStatSeqConfig* commStatSeqConfig);

    /**
     * Sets status checking sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[in] statSeqP1Cfg STAT P1 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setStatSeqP1Config)(XSPI_PrivateData* privateData, const XSPI_StatSeqP1Config* statSeqP1Cfg);

    /**
     * Gets status checking sequence configuration for Profile 1
     * @param[in] privateData Pointer to driver private data object
     * @param[out] statSeqP1Cfg STAT P1 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getStatSeqP1Config)(XSPI_PrivateData* privateData, XSPI_StatSeqP1Config* statSeqP1Cfg);

    /**
     * Sets status checking sequence configuration for Profile 2
     * @param[in] privateData Pointer to driver private data object
     * @param[in] statSeqP2Cfg STAT P2 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setStatSeqP2Config)(XSPI_PrivateData* privateData, const XSPI_StatSeqP2Config* statSeqP2Cfg);

    /**
     * Gets status checking sequence configuration for Profile 2
     * @param[in] privateData Pointer to driver private data object
     * @param[out] statSeqP2Cfg STAT P2 sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getStatSeqP2Config)(XSPI_PrivateData* privateData, XSPI_StatSeqP2Config* statSeqP2Cfg);

    /**
     * Sets status sequence settings for NAND SPI devices (Since R003)
     * @param[in] privateData Pointer to driver private data object
     * @param[in] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*setStatSeqSpiNandConfig)(XSPI_PrivateData* privateData, const XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg);

    /**
     * Gets status sequence settings for NAND SPI devices (Since R003)
     * @param[in] privateData Pointer to driver private data object
     * @param[out] statSeqSpiNandCfg Status sequence settings for NAND SPI devices
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*getStatSeqSpiNandConfig)(XSPI_PrivateData* privateData, XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg);

    /**
     * Sends STIG command for execution
     * @param[in] privateData Pointer to driver private data object
     * @param[in,out] stigCommand Pointer to STIG command
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*sendStigCommand)(XSPI_PrivateData* privateData, XSPI_StigCommand* stigCommand);

    /**
     * Gets last command status (in STIG work mode)
     * @param[in] privateData Pointer to driver private data object
     * @param[out] stigCommand Stig command containing status information
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getStigStatus)(XSPI_PrivateData* privateData, XSPI_StigCommand* stigCommand);

    /**
     * Sets relative device selection delay applicable for JEDEC Reset
     * command (Since R003)
     * @param[in] privateData Pointer to driver private data object
     * @param[in] jedecRstTiming JEDEC RESET timing config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*setJedecResetTimingConfig)(XSPI_PrivateData* privateData, const XSPI_JedecResetTimingConfig* jedecRstTiming);

    /**
     * Gets relative device selection delay applicable for JEDEC Reset
     * command (Since R003)
     * @param[in] privateData Pointer to driver private data object
     * @param[out] jedecRstTiming JEDEC RESET timing config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*getJedecResetTimingConfig)(XSPI_PrivateData* privateData, XSPI_JedecResetTimingConfig* jedecRstTiming);

    /**
     * Sends JEDEC RESET command in STIG work mode
     * @param[in] privateData Pointer to driver piravte data object
     * @param[in] bankSelect Selected bank to which JEDEC RESET instruction should be sent
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     * @return CDN_ENOTSUP If controller version is below R003
     */
    uint32_t (*sendStigJedecReset)(XSPI_PrivateData* privateData, uint8_t bankSelect);

    /**
     * Sets continue processing on descriptor error state
     * @param[in] privateData Pointer to driver private data object
     * @param[in] procOnErrEnabled Continue processing on descriptor error
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setContinueProcOnDescError)(XSPI_PrivateData* privateData, bool procOnErrEnabled);

    /**
     * Gets continue processing on descriptor error state
     * @param[in] privateData Pointer to driver private data object
     * @param[out] procOnErrEnabled Continue processing on descriptor error
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getContinueProcOnDescError)(XSPI_PrivateData* privateData, bool* procOnErrEnabled);

    /**
     * Gets latest boot operation status
     * @param[in] privateData Pointer to driver private data object
     * @param[out] bootStatus Latest boot operation status
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getLatestBootStatus)(XSPI_PrivateData* privateData, XSPI_LatestBootStatus* bootStatus);

    /**
     * Sets device discovery config
     * @param[in] privateData Pointer to driver private data object
     * @param[in] deviceDiscoveryConfig Device discovery config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setDeviceDiscoveryConfig)(XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig);

    /**
     * Gets device discovery config
     * @param[in] privateData Pointer to driver private data object
     * @param[out] deviceDiscoveryConfig Device discovery config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getDeviceDiscoveryConfig)(XSPI_PrivateData* privateData, XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig);

    /**
     * Runs device discovery with current discovery settings
     * @param[in] privateData Pointer to driver private data object
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*runDeviceDiscovery)(XSPI_PrivateData* privateData);

    /**
     * Gets status of device discovery operation
     * @param[in] privateData Pointer to driver private data object
     * @param[out] deviceDiscoveryStatus Status of device discovery operation
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getDeviceDiscoveryStatus)(XSPI_PrivateData* privateData, XSPI_DeviceDiscoveryStatus* deviceDiscoveryStatus);

    /**
     * Sets the relative reset recovery delay with respect to generated
     * xSPI flash interface
     * @param[in] privateData Pointer to driver private data object
     * @param[in] resetRecovery Reset recovery delay
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setResetRecoveryDelay)(XSPI_PrivateData* privateData, uint32_t resetRecovery);

    /**
     * Gets the relative reset recovery delay with respect to generated
     * xSPI flash interface
     * @param[in] privateData Pointer to driver private data object
     * @param[out] resetRecovery Reset recovery delay
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getResetRecoveryDelay)(XSPI_PrivateData* privateData, uint32_t* resetRecovery);

    /**
     * Sets the polling configuration for controller to check device
     * status after issue of erase/write operation
     * @param[in] privateData Pointer to driver private data object
     * @param[in] pollingConfig Polling configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setPollingConfig)(XSPI_PrivateData* privateData, const XSPI_PollingConfig* pollingConfig);

    /**
     * Gets polling configuration for controller to check device status
     * @param[in] privateData Pointer to driver private data object
     * @param[out] pollingConfig Polling configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getPollingConfig)(XSPI_PrivateData* privateData, XSPI_PollingConfig* pollingConfig);

    /**
     * Sets HyperFlash offset config
     * @param[in] privateData Pointer to driver private data object
     * @param[in] hfOffsetCfg HyperFlash offset config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setHyperFlashOffsetConfig)(XSPI_PrivateData* privateData, const XSPI_HyperFlashOffsetConfig* hfOffsetCfg);

    /**
     * Gets HyperFlash offset config
     * @param[in] privateData Pointer to driver private data object
     * @param[out] hfOffsetCfg HyperFlash offset config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getHyperFlashOffsetConfig)(XSPI_PrivateData* privateData, XSPI_HyperFlashOffsetConfig* hfOffsetCfg);

    /**
     * Sets configuration of the resynchronization of slave DLL of PHY
     * @param[in] privateData Pointer to driver private data object
     * @param[in] phyConfig PHY configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setPhyConfig)(XSPI_PrivateData* privateData, const XSPI_PhyConfig* phyConfig);

    /**
     * Gets configuration of the resynchronization of slave DLL of PHY
     * @param[in] privateData Pointer to driver private data object
     * @param[out] phyConfig PHY configuration
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getPhyConfig)(XSPI_PrivateData* privateData, XSPI_PhyConfig* phyConfig);

    /**
     * Writes signal value to reset the DLLs of the PHY
     * @param[in] privateData Pointer to driver private data object
     * @param[in] dllReset DLL reset value
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*phyWriteDllReset)(XSPI_PrivateData* privateData, uint8_t dllReset);

    /**
     * Sends CDMA command for execution
     * @param[in] privateData Pointer to driver private data object
     * @param[in] thread Thread number
     * @param[in,out] cdmaCmd Pointer to CDMA command
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*sendCdmaCommand)(XSPI_PrivateData* privateData, uint8_t thread, XSPI_CdmaCommand* cdmaCmd);

    /**
     * Gets CDMA command status
     * @param[in] privateData Pointer to driver private data object
     * @param[in] thread Thread number
     * @param[in,out] cdmaCmd Pointer to CDMA command, contains status structure
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getCdmaCommandStatus)(XSPI_PrivateData* privateData, uint8_t thread, XSPI_CdmaCommand* cdmaCmd);

    /**
     * Sends multiple CDMA commands for execution by forming a chain
     * @param[in] privateData Pointer to driver private data object
     * @param[in,out] cdmaCmdChain Pointer to CDMA commands chain structure
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*sendCdmaCommandChain)(XSPI_PrivateData* privateData, XSPI_CdmaCommandChain* cdmaCmdChain);

    /**
     * Gets CDMA chain status
     * @param[in] privateData Pointer to driver private data object
     * @param[in,out] cdmaCmdChain Pointer to CDMA commands chain
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getCdmaChainStatus)(XSPI_PrivateData* privateData, XSPI_CdmaCommandChain* cdmaCmdChain);

    /**
     * Sends PIO command for execution
     * @param[in] privateData Pointer to driver private data object
     * @param[in] thread Thread number
     * @param[in,out] pioCmd Pointer to PIO command
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*sendPioCommand)(XSPI_PrivateData* privateData, uint8_t thread, XSPI_PioCommand* pioCmd);

    /**
     * Gets PIO command status
     * @param[in] privateData Pointer to driver private data object
     * @param[in] thread Thread number
     * @param[in,out] pioCmd Pointer to PIO command
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getPioCommandStatus)(XSPI_PrivateData* privateData, uint8_t thread, XSPI_PioCommand* pioCmd);

    /**
     * Gets the status of last command executed in ACMD mode (both for
     * CDMA and PIO modes) and STIG work mode
     * @param[in] privateData Pointer to driver private data object
     * @param[in] thread Thread number
     * @param[out] cmdStatus Pointer to command status structure
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getAcmdLastCmdStatus)(XSPI_PrivateData* privateData, uint8_t thread, XSPI_CommandStatusInfo* cmdStatus);

    /**
     * Sets RESET sequence configuration for Profile 1 in CDMA and PIO
     * modes
     * @param[in] privateData Pointer to driver private data object
     * @param[in] resetSeqCfg RESET sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setResetSeqConfig)(const XSPI_PrivateData* privateData, const XSPI_ResetSeqConfig* resetSeqCfg);

    /**
     * Gets RESET sequence configuration for Profile 1 in CDMA and PIO
     * modes
     * @param[in] privateData Pointer to driver private data object
     * @param[out] resetSeqCfg RESET sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getResetSeqConfig)(XSPI_PrivateData* privateData, XSPI_ResetSeqConfig* resetSeqCfg);

    /**
     * Sets ERASE SECTOR sequence configuration for Profile 1 in CDMA and
     * PIO modes
     * @param[in] privateData Pointer to driver private data object
     * @param[in] eraseSecSeqCfg ERASE SECTOR sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setEraseSecConfig)(XSPI_PrivateData* privateData, const XSPI_EraseSecSeqConfig* eraseSecSeqCfg);

    /**
     * Gets ERASE SECTOR sequence configuration for Profile 1 in CDMA and
     * PIO modes
     * @param[in] privateData Pointer to driver private data object
     * @param[out] eraseSecSeqCfg ERASE SECTOR sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getEraseSecConfig)(XSPI_PrivateData* privateData, XSPI_EraseSecSeqConfig* eraseSecSeqCfg);

    /**
     * Sets CHIP ERASE sequence configuration for Profile 1 in CDMA and
     * PIO modes
     * @param[in] privateData Pointer to driver private data object
     * @param[in] chipEraseSeqCfg CHIP ERASE sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*setChipEraseSeqConfig)(XSPI_PrivateData* privateData, const XSPI_ChipEraseSeqConfig* chipEraseSeqCfg);

    /**
     * Gets CHIP ERASE sequence configuration for Profile 1 in CDMA and
     * PIO modes
     * @param[in] privateData Pointer to driver private data object
     * @param[out] chipEraseSeqCfg CHIP ERASE sequence config
     * @return CDN_EOK On success
     * @return CDN_EINVAL For invalid pointer
     */
    uint32_t (*getChipEraseSeqConfig)(XSPI_PrivateData* privateData, XSPI_ChipEraseSeqConfig* chipEraseSeqCfg);

} XSPI_OBJ;
/* parasoft-end-suppress MISRA2012-DIR-4_8-4 */

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3666" */
/**
 * In order to access the XSPI APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return XSPI_OBJ* Driver Object Pointer
 */
extern XSPI_OBJ *XSPI_GetInstance(void);

/**
 *  @}
 */
/* parasoft-end-suppress METRICS-36-3 */


#endif	/* XSPI_OBJ_IF_H */
