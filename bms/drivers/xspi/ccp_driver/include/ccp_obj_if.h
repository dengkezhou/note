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
#ifndef CCP_OBJ_IF_H
#define CCP_OBJ_IF_H

#include "ccp_if.h"

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
typedef struct CCP_OBJ_s
{
    /**
     * "Get the driver memory requirements to support the given
     * configuration."
     * @param[in] config "Driver/hardware configuration required."
     * @param[out] memReq "Returns the size of memory allocations required."
     * @return CDN_EOK on success
     * @return CDN_EINVAL for invalid pointer
     */
    uint32_t (*probe)(const CCP_Config* config, CCP_SysReq* memReq);

    /**
     * "Initialize the driver. Must be called before all other access
     * APIs. The init function will retain the default value in the
     * hardware."
     * @param[in] pD "Memory pointer to the uninitialized private data of the size specified by probe."
     * @param[in] config "Specifies driver/hardware configuration."
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*init)(CCP_PrivateData* pD, const CCP_Config* config);

    /**
     * setter for phyDqTimingReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyDqTimingReg)(CCP_PrivateData* pD, const CCP_PhyDqTimingReg* value);

    /**
     * getter for phyDqTimingReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDqTimingReg)(const CCP_PrivateData* pD, CCP_PhyDqTimingReg* value);

    /**
     * setter for phyDqsTimingReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyDqsTimingReg)(CCP_PrivateData* pD, const CCP_PhyDqsTimingReg* value);

    /**
     * getter for phyDqsTimingReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDqsTimingReg)(const CCP_PrivateData* pD, CCP_PhyDqsTimingReg* value);

    /**
     * setter for phyGateLpbkCtrlReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyGateLpbkCtrlReg)(CCP_PrivateData* pD, const CCP_PhyGateLpbkCtrlReg* value);

    /**
     * getter for PhyGateLpbkCtrlReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyGateLpbkCtrlReg)(const CCP_PrivateData* pD, CCP_PhyGateLpbkCtrlReg* value);

    /**
     * setter for phyDllMasterCtrlReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyDllMasterCtrlReg)(CCP_PrivateData* pD, const CCP_PhyDllMasterCtrlReg* value);

    /**
     * getter for PhyDllMasterCtrlReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDllMasterCtrlReg)(const CCP_PrivateData* pD, CCP_PhyDllMasterCtrlReg* value);

    /**
     * setter for phyDllSlaveCtrlReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyDllSlaveCtrlReg)(CCP_PrivateData* pD, const CCP_PhyDllSlaveCtrlReg* value);

    /**
     * getter for PhyDllSlaveCtrlReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDllSlaveCtrlReg)(const CCP_PrivateData* pD, CCP_PhyDllSlaveCtrlReg* value);

    /**
     * setter for phyIeTimingReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyIeTimingReg)(CCP_PrivateData* pD, const CCP_PhyIeTimingReg* value);

    /**
     * getter for PhyIeTimingReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyIeTimingReg)(const CCP_PrivateData* pD, CCP_PhyIeTimingReg* value);

    /**
     * getter for phyObsReg0
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyObsReg0)(const CCP_PrivateData* pD, CCP_PhyObsReg0* value);

    /**
     * getter for phyDllObsReg0
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDllObsReg0)(const CCP_PrivateData* pD, CCP_PhyDllObsReg0* value);

    /**
     * getter for phyDllObsReg1
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDllObsReg1)(const CCP_PrivateData* pD, CCP_PhyDllObsReg1* value);

    /**
     * getter for phyDllObsReg2
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyDllObsReg2)(const CCP_PrivateData* pD, CCP_PhyDllObsReg2* value);

    /**
     * setter for phyStaticToggReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyStaticToggReg)(CCP_PrivateData* pD, const CCP_PhyStaticToggReg* value);

    /**
     * getter for PhyStaticToggReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyStaticToggReg)(const CCP_PrivateData* pD, CCP_PhyStaticToggReg* value);

    /**
     * setter for PhyWrRdDeskewCmd
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyWrRdDeskewCmd)(CCP_PrivateData* pD, const CCP_PhyWrRdDeskewCmd* value);

    /**
     * getter for PhyWrRdDeskewCmd
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyWrRdDeskewCmd)(const CCP_PrivateData* pD, CCP_PhyWrRdDeskewCmd* value);

    /**
     * setter for PhyWrDeskewPdCtrl0Dq0
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyWrDeskewPdCtrl0Dq0)(CCP_PrivateData* pD, const CCP_PhyWrDeskewPdCtrl0Dq0* value);

    /**
     * getter for PhyWrDeskewPdCtrl0Dq0
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyWrDeskewPdCtrl0Dq0)(const CCP_PrivateData* pD, CCP_PhyWrDeskewPdCtrl0Dq0* value);

    /**
     * setter for phyCtrlMain
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyCtrlMain)(CCP_PrivateData* pD, const CCP_PhyCtrlMain* value);

    /**
     * getter for PhyCtrlMain
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyCtrlMain)(const CCP_PrivateData* pD, CCP_PhyCtrlMain* value);

    /**
     * setter for phyTselReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyTselReg)(CCP_PrivateData* pD, const CCP_PhyTselReg* value);

    /**
     * getter for PhyTselReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyTselReg)(const CCP_PrivateData* pD, CCP_PhyTselReg* value);

    /**
     * setter for PhyGpioCtrl0
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input value
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyGpioCtrl0)(const CCP_PrivateData* pD, uint32_t value);

    /**
     * setter for PhyGpioCtrl1
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input value
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*setPhyGpioCtrl1)(const CCP_PrivateData* pD, uint32_t value);

    /**
     * getter for PhyGpioStatus0
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyGpioStatus0)(const CCP_PrivateData* pD, uint32_t* value);

    /**
     * getter for PhyGpioStatus1
     * @param[in] pD Pointer to the private data initialized by init
     * @param[in] value input struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyGpioStatus1)(const CCP_PrivateData* pD, uint32_t* value);

    /**
     * Waits until Phy DLL locked bit is set.
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] locked PHY DLL lock status
     * @param[in] delayNs Delay in nanoseconds
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*waitForDllLock)(const CCP_PrivateData* pD, uint32_t* locked, uint32_t delayNs);

    /**
     * getter for PhyFeaturesReg
     * @param[in] pD Pointer to the private data initialized by init
     * @param[out] value output struct
     * @return CDN_EOK on success
     * @return CDN_EINVAL if any pointer parameters are NULL
     */
    uint32_t (*getPhyFeaturesReg)(const CCP_PrivateData* pD, CCP_PhyFeaturesReg* value);

} CCP_OBJ;
/* parasoft-end-suppress MISRA2012-DIR-4_8-4 */

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3666" */
/**
 * In order to access the CCP APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CCP_OBJ* Driver Object Pointer
 */
extern CCP_OBJ *CCP_GetInstance(void);

/**
 *  @}
 */
/* parasoft-end-suppress METRICS-36-3 */


#endif	/* CCP_OBJ_IF_H */
