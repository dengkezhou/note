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

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10, DRV-4789" */
/* parasoft-begin-suppress METRIC.CC-3 "Follow the Cyclomatic Complexity limit of 30, DRV-4417" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4, DRV-4790" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit, DRV-4139" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#ifndef CCPEXT_SANITY_H
#define CCPEXT_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "ccpext_if.h"

uint32_t CCPEXT_PhyCtrlLowFreqSelSF(const CCPEXT_PhyCtrlLowFreqSel *obj);
uint32_t CCPEXT_PhyRdDeskewRegSF(const CCPEXT_PhyRdDeskewReg *obj);
uint32_t CCPEXT_PhyWrDeskewPdCtrl0DqxSF(const CCPEXT_PhyWrDeskewPdCtrl0Dqx *obj);
uint32_t CCPEXT_PhyWrDeskewPdCtrl1RegSF(const CCPEXT_PhyWrDeskewPdCtrl1Reg *obj);
uint32_t CCPEXT_PhyWrDeskewRegSF(const CCPEXT_PhyWrDeskewReg *obj);
uint32_t CCPEXT_PhyWrRdDeskewCmdExtSF(const CCPEXT_PhyWrRdDeskewCmdExt *obj);

uint32_t CCPEXT_SanityFunction1(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value);
uint32_t CCPEXT_SanityFunction2(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value);
uint32_t CCPEXT_SanityFunction3(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewReg* value);
uint32_t CCPEXT_SanityFunction4(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewReg* value);
uint32_t CCPEXT_SanityFunction5(const CCP_PrivateData* pD, const CCPEXT_PhyRdDeskewReg* value);
uint32_t CCPEXT_SanityFunction6(const CCP_PrivateData* pD, const CCPEXT_PhyRdDeskewReg* value);
uint32_t CCPEXT_SanityFunction7(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl1Reg* value);
uint32_t CCPEXT_SanityFunction8(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl1Reg* value);
uint32_t CCPEXT_SanityFunction9(const CCP_PrivateData* pD, const CCPEXT_PhyCtrlLowFreqSel* value);
uint32_t CCPEXT_SanityFunction10(const CCP_PrivateData* pD, const CCPEXT_PhyCtrlLowFreqSel* value);
uint32_t CCPEXT_SanityFunction11(const CCP_PrivateData* pD, const CCPEXT_PhyWrRdDeskewCmdExt* value);
uint32_t CCPEXT_SanityFunction12(const CCP_PrivateData* pD, const CCPEXT_PhyWrRdDeskewCmdExt* value);

#define	CCPEXT_SetPhyWrDeskewPdCtrl0SF CCPEXT_SanityFunction1
#define	CCPEXT_GetPhyWrDeskewPdCtrl0SF CCPEXT_SanityFunction2
#define	CCPEXT_SetPhyWrDeskewRegSF CCPEXT_SanityFunction3
#define	CCPEXT_GetPhyWrDeskewRegSF CCPEXT_SanityFunction4
#define	CCPEXT_SetPhyRdDeskewRegSF CCPEXT_SanityFunction5
#define	CCPEXT_GetPhyRdDeskewRegSF CCPEXT_SanityFunction6
#define	CCPEXT_SetPhyWrDeskewPdCtrl1SF CCPEXT_SanityFunction7
#define	CCPEXT_GetPhyWrDeskewPdCtrl1SF CCPEXT_SanityFunction8
#define	CCPEXT_SetPhyCtrlLowFreqSelSF CCPEXT_SanityFunction9
#define	CCPEXT_GetPhyCtrlLowFreqSelSF CCPEXT_SanityFunction10
#define	CCPEXT_SetPhyWrRdDeskewCmdExSF CCPEXT_SanityFunction11
#define	CCPEXT_GetPhyWrRdDeskewCmdExSF CCPEXT_SanityFunction12


#endif	/* CCPEXT_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
