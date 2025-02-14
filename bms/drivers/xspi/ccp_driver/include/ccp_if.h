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
 * Cadence Combo PHY Core Driver
 **********************************************************************/

#ifndef CCP_IF_H
#define CCP_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */

#include "cdn_stdtypes.h"
#include "cdn_inttypes.h"
#include "ccp_ls_regs.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** Magic number value */
#define	CCP_MAGIC_NUMBER 0x6182U

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
typedef struct CCP_SysReq_s CCP_SysReq;
typedef struct CCP_Config_s CCP_Config;
typedef struct CCP_PrivateData_s CCP_PrivateData;
typedef struct CCP_PhyDqTimingReg_s CCP_PhyDqTimingReg;
typedef struct CCP_PhyDqsTimingReg_s CCP_PhyDqsTimingReg;
typedef struct CCP_PhyGateLpbkCtrlReg_s CCP_PhyGateLpbkCtrlReg;
typedef struct CCP_PhyDllMasterCtrlReg_s CCP_PhyDllMasterCtrlReg;
typedef struct CCP_PhyDllSlaveCtrlReg_s CCP_PhyDllSlaveCtrlReg;
typedef struct CCP_PhyIeTimingReg_s CCP_PhyIeTimingReg;
typedef struct CCP_PhyObsReg0_s CCP_PhyObsReg0;
typedef struct CCP_PhyDllObsReg0_s CCP_PhyDllObsReg0;
typedef struct CCP_PhyDllObsReg1_s CCP_PhyDllObsReg1;
typedef struct CCP_PhyDllObsReg2_s CCP_PhyDllObsReg2;
typedef struct CCP_PhyStaticToggReg_s CCP_PhyStaticToggReg;
typedef struct CCP_PhyWrDeskewReg_s CCP_PhyWrDeskewReg;
typedef struct CCP_PhyRdDeskewReg_s CCP_PhyRdDeskewReg;
typedef struct CCP_PhyWrRdDeskewCmd_s CCP_PhyWrRdDeskewCmd;
typedef struct CCP_PhyWrDeskewPdCtrl0Dq0_s CCP_PhyWrDeskewPdCtrl0Dq0;
typedef struct CCP_PhyFeaturesReg_s CCP_PhyFeaturesReg;
typedef struct CCP_PhyCtrlMain_s CCP_PhyCtrlMain;
typedef struct CCP_PhyTselReg_s CCP_PhyTselReg;


/**********************************************************************
 * Callbacks
 **********************************************************************/
/** Reads the requested PHY register value. */
typedef uint32_t (*CCP_ReadPhyReg)(uint32_t address);

/** Write the requested PHY register with the value. */
typedef void (*CCP_WritePhyReg)(uint32_t address, uint32_t value);

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
 * "Get the driver memory requirements to support the given
 * configuration."
 * @param[in] config "Driver/hardware configuration required."
 * @param[out] memReq "Returns the size of memory allocations required."
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CCP_Probe(const CCP_Config* config, CCP_SysReq* memReq);

/**
 * "Initialize the driver. Must be called before all other access
 * APIs. The init function will retain the default value in the
 * hardware."
 * @param[in] pD "Memory pointer to the uninitialized private data of the size specified by probe."
 * @param[in] config "Specifies driver/hardware configuration."
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_Init(CCP_PrivateData* pD, const CCP_Config* config);

/**
 * setter for phyDqTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDqTimingReg(CCP_PrivateData* pD, const CCP_PhyDqTimingReg* value);

/**
 * getter for phyDqTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDqTimingReg(const CCP_PrivateData* pD, CCP_PhyDqTimingReg* value);

/**
 * setter for phyDqsTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDqsTimingReg(CCP_PrivateData* pD, const CCP_PhyDqsTimingReg* value);

/**
 * getter for phyDqsTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDqsTimingReg(const CCP_PrivateData* pD, CCP_PhyDqsTimingReg* value);

/**
 * setter for phyGateLpbkCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyGateLpbkCtrlReg(CCP_PrivateData* pD, const CCP_PhyGateLpbkCtrlReg* value);

/**
 * getter for PhyGateLpbkCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyGateLpbkCtrlReg(const CCP_PrivateData* pD, CCP_PhyGateLpbkCtrlReg* value);

/**
 * setter for phyDllMasterCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDllMasterCtrlReg(CCP_PrivateData* pD, const CCP_PhyDllMasterCtrlReg* value);

/**
 * getter for PhyDllMasterCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllMasterCtrlReg(const CCP_PrivateData* pD, CCP_PhyDllMasterCtrlReg* value);

/**
 * setter for phyDllSlaveCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDllSlaveCtrlReg(CCP_PrivateData* pD, const CCP_PhyDllSlaveCtrlReg* value);

/**
 * getter for PhyDllSlaveCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllSlaveCtrlReg(const CCP_PrivateData* pD, CCP_PhyDllSlaveCtrlReg* value);

/**
 * setter for phyIeTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyIeTimingReg(CCP_PrivateData* pD, const CCP_PhyIeTimingReg* value);

/**
 * getter for PhyIeTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyIeTimingReg(const CCP_PrivateData* pD, CCP_PhyIeTimingReg* value);

/**
 * getter for phyObsReg0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyObsReg0(const CCP_PrivateData* pD, CCP_PhyObsReg0* value);

/**
 * getter for phyDllObsReg0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllObsReg0(const CCP_PrivateData* pD, CCP_PhyDllObsReg0* value);

/**
 * getter for phyDllObsReg1
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllObsReg1(const CCP_PrivateData* pD, CCP_PhyDllObsReg1* value);

/**
 * getter for phyDllObsReg2
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllObsReg2(const CCP_PrivateData* pD, CCP_PhyDllObsReg2* value);

/**
 * setter for phyStaticToggReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyStaticToggReg(CCP_PrivateData* pD, const CCP_PhyStaticToggReg* value);

/**
 * getter for PhyStaticToggReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyStaticToggReg(const CCP_PrivateData* pD, CCP_PhyStaticToggReg* value);

/**
 * setter for PhyWrRdDeskewCmd
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyWrRdDeskewCmd(CCP_PrivateData* pD, const CCP_PhyWrRdDeskewCmd* value);

/**
 * getter for PhyWrRdDeskewCmd
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyWrRdDeskewCmd(const CCP_PrivateData* pD, CCP_PhyWrRdDeskewCmd* value);

/**
 * setter for PhyWrDeskewPdCtrl0Dq0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyWrDeskewPdCtrl0Dq0(CCP_PrivateData* pD, const CCP_PhyWrDeskewPdCtrl0Dq0* value);

/**
 * getter for PhyWrDeskewPdCtrl0Dq0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyWrDeskewPdCtrl0Dq0(const CCP_PrivateData* pD, CCP_PhyWrDeskewPdCtrl0Dq0* value);

/**
 * setter for phyCtrlMain
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyCtrlMain(CCP_PrivateData* pD, const CCP_PhyCtrlMain* value);

/**
 * getter for PhyCtrlMain
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyCtrlMain(const CCP_PrivateData* pD, CCP_PhyCtrlMain* value);

/**
 * setter for phyTselReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyTselReg(CCP_PrivateData* pD, const CCP_PhyTselReg* value);

/**
 * getter for PhyTselReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyTselReg(const CCP_PrivateData* pD, CCP_PhyTselReg* value);

/**
 * setter for PhyGpioCtrl0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input value
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyGpioCtrl0(const CCP_PrivateData* pD, uint32_t value);

/**
 * setter for PhyGpioCtrl1
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input value
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyGpioCtrl1(const CCP_PrivateData* pD, uint32_t value);

/**
 * getter for PhyGpioStatus0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyGpioStatus0(const CCP_PrivateData* pD, uint32_t* value);

/**
 * getter for PhyGpioStatus1
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyGpioStatus1(const CCP_PrivateData* pD, uint32_t* value);

/**
 * Waits until Phy DLL locked bit is set.
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] locked PHY DLL lock status
 * @param[in] delayNs Delay in nanoseconds
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_WaitForDllLock(const CCP_PrivateData* pD, uint32_t* locked, uint32_t delayNs);

/**
 * getter for PhyFeaturesReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyFeaturesReg(const CCP_PrivateData* pD, CCP_PhyFeaturesReg* value);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* CCP_IF_H */
