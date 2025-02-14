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
 * Extracted data
 **********************************************************************/

#ifndef CCPEXT_IF_H
#define CCPEXT_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */

#include "cdn_stdtypes.h"
#include "cdn_inttypes.h"
#include "ccp_if.h"

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
typedef struct CCPEXT_PhyWrDeskewReg_s CCPEXT_PhyWrDeskewReg;
typedef struct CCPEXT_PhyRdDeskewReg_s CCPEXT_PhyRdDeskewReg;
typedef struct CCPEXT_PhyWrDeskewPdCtrl0Dqx_s CCPEXT_PhyWrDeskewPdCtrl0Dqx;
typedef struct CCPEXT_PhyWrDeskewPdCtrl1Reg_s CCPEXT_PhyWrDeskewPdCtrl1Reg;
typedef struct CCPEXT_PhyCtrlLowFreqSel_s CCPEXT_PhyCtrlLowFreqSel;
typedef struct CCPEXT_PhyWrRdDeskewCmdExt_s CCPEXT_PhyWrRdDeskewCmdExt;


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
 * setter for PhyWrDeskewPdCtrl0Dqx
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrDeskewPdCtrl0Dqx(CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value);

/**
 * getter for PhyWrDeskewPdCtrl0Dqx
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrDeskewPdCtrl0Dqx(const CCP_PrivateData* pD, CCPEXT_PhyWrDeskewPdCtrl0Dqx* value);

/**
 * setter for PhyWrDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrDeskewReg(CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewReg* value);

/**
 * getter for PhyWrDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrDeskewReg(const CCP_PrivateData* pD, CCPEXT_PhyWrDeskewReg* value);

/**
 * setter for PhyRdDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyRdDeskewReg(CCP_PrivateData* pD, const CCPEXT_PhyRdDeskewReg* value);

/**
 * getter for PhyRdDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyRdDeskewReg(const CCP_PrivateData* pD, CCPEXT_PhyRdDeskewReg* value);

/**
 * setter for PhyWrDeskewPdCtrl1Reg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrDeskewPdCtrl1Reg(CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl1Reg* value);

/**
 * getter for PhyWrDeskewPdCtrl1Reg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrDeskewPdCtrl1Reg(const CCP_PrivateData* pD, CCPEXT_PhyWrDeskewPdCtrl1Reg* value);

/**
 * setter for PhyCtrlLowFreqSel
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyCtrlLowFreqSel(CCP_PrivateData* pD, const CCPEXT_PhyCtrlLowFreqSel* value);

/**
 * getter for PhyCtrlLowFreqSel
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyCtrlLowFreqSel(const CCP_PrivateData* pD, CCPEXT_PhyCtrlLowFreqSel* value);

/**
 * setter for PhyWrRdDeskewCmdExt
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrRdDeskewCmdExt(CCP_PrivateData* pD, const CCPEXT_PhyWrRdDeskewCmdExt* value);

/**
 * getter for PhyWrRdDeskewCmdExt
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrRdDeskewCmdExt(const CCP_PrivateData* pD, CCPEXT_PhyWrRdDeskewCmdExt* value);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* CCPEXT_IF_H */
