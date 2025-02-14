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

#ifndef CCP_SANITY_H
#define CCP_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "ccp_if.h"

uint32_t CCP_ConfigSF(const CCP_Config *obj);
uint32_t CCP_PhyCtrlMainSF(const CCP_PhyCtrlMain *obj);
uint32_t CCP_PhyDllMasterCtrlRegSF(const CCP_PhyDllMasterCtrlReg *obj);
uint32_t CCP_PhyDllSlaveCtrlRegSF(const CCP_PhyDllSlaveCtrlReg *obj);
uint32_t CCP_PhyDqTimingRegSF(const CCP_PhyDqTimingReg *obj);
uint32_t CCP_PhyDqsTimingRegSF(const CCP_PhyDqsTimingReg *obj);
uint32_t CCP_PhyGateLpbkCtrlRegSF(const CCP_PhyGateLpbkCtrlReg *obj);
uint32_t CCP_PhyIeTimingRegSF(const CCP_PhyIeTimingReg *obj);
uint32_t CCP_PhyStaticToggRegSF(const CCP_PhyStaticToggReg *obj);
uint32_t CCP_PhyTselRegSF(const CCP_PhyTselReg *obj);
uint32_t CCP_PhyWrDeskewPdCtrl0Dq0SF(const CCP_PhyWrDeskewPdCtrl0Dq0 *obj);
uint32_t CCP_PhyWrRdDeskewCmdSF(const CCP_PhyWrRdDeskewCmd *obj);
uint32_t CCP_PrivateDataSF(const CCP_PrivateData *obj);

uint32_t CCP_SanityFunction1(const CCP_Config* config, const CCP_SysReq* memReq);
uint32_t CCP_SanityFunction2(const CCP_PrivateData* pD, const CCP_Config* config);
uint32_t CCP_SanityFunction3(const CCP_PrivateData* pD, const CCP_PhyDqTimingReg* value);
uint32_t CCP_SanityFunction4(const CCP_PrivateData* pD, const CCP_PhyDqTimingReg* value);
uint32_t CCP_SanityFunction5(const CCP_PrivateData* pD, const CCP_PhyDqsTimingReg* value);
uint32_t CCP_SanityFunction6(const CCP_PrivateData* pD, const CCP_PhyDqsTimingReg* value);
uint32_t CCP_SanityFunction7(const CCP_PrivateData* pD, const CCP_PhyGateLpbkCtrlReg* value);
uint32_t CCP_SanityFunction8(const CCP_PrivateData* pD, const CCP_PhyGateLpbkCtrlReg* value);
uint32_t CCP_SanityFunction9(const CCP_PrivateData* pD, const CCP_PhyDllMasterCtrlReg* value);
uint32_t CCP_SanityFunction10(const CCP_PrivateData* pD, const CCP_PhyDllMasterCtrlReg* value);
uint32_t CCP_SanityFunction11(const CCP_PrivateData* pD, const CCP_PhyDllSlaveCtrlReg* value);
uint32_t CCP_SanityFunction12(const CCP_PrivateData* pD, const CCP_PhyDllSlaveCtrlReg* value);
uint32_t CCP_SanityFunction13(const CCP_PrivateData* pD, const CCP_PhyIeTimingReg* value);
uint32_t CCP_SanityFunction14(const CCP_PrivateData* pD, const CCP_PhyIeTimingReg* value);
uint32_t CCP_SanityFunction15(const CCP_PrivateData* pD, const CCP_PhyObsReg0* value);
uint32_t CCP_SanityFunction16(const CCP_PrivateData* pD, const CCP_PhyDllObsReg0* value);
uint32_t CCP_SanityFunction17(const CCP_PrivateData* pD, const CCP_PhyDllObsReg1* value);
uint32_t CCP_SanityFunction18(const CCP_PrivateData* pD, const CCP_PhyDllObsReg2* value);
uint32_t CCP_SanityFunction19(const CCP_PrivateData* pD, const CCP_PhyStaticToggReg* value);
uint32_t CCP_SanityFunction20(const CCP_PrivateData* pD, const CCP_PhyStaticToggReg* value);
uint32_t CCP_SanityFunction21(const CCP_PrivateData* pD, const CCP_PhyWrRdDeskewCmd* value);
uint32_t CCP_SanityFunction22(const CCP_PrivateData* pD, const CCP_PhyWrRdDeskewCmd* value);
uint32_t CCP_SanityFunction23(const CCP_PrivateData* pD, const CCP_PhyWrDeskewPdCtrl0Dq0* value);
uint32_t CCP_SanityFunction24(const CCP_PrivateData* pD, const CCP_PhyWrDeskewPdCtrl0Dq0* value);
uint32_t CCP_SanityFunction25(const CCP_PrivateData* pD, const CCP_PhyCtrlMain* value);
uint32_t CCP_SanityFunction26(const CCP_PrivateData* pD, const CCP_PhyCtrlMain* value);
uint32_t CCP_SanityFunction27(const CCP_PrivateData* pD, const CCP_PhyTselReg* value);
uint32_t CCP_SanityFunction28(const CCP_PrivateData* pD, const CCP_PhyTselReg* value);
uint32_t CCP_SanityFunction29(const CCP_PrivateData* pD);
uint32_t CCP_SanityFunction31(const CCP_PrivateData* pD, const uint32_t* value);
uint32_t CCP_SanityFunction34(const CCP_PrivateData* pD, const CCP_PhyFeaturesReg* value);

#define	CCP_ProbeSF CCP_SanityFunction1
#define	CCP_InitSF CCP_SanityFunction2
#define	CCP_SetPhyDqTimingRegSF CCP_SanityFunction3
#define	CCP_GetPhyDqTimingRegSF CCP_SanityFunction4
#define	CCP_SetPhyDqsTimingRegSF CCP_SanityFunction5
#define	CCP_GetPhyDqsTimingRegSF CCP_SanityFunction6
#define	CCP_SetPhyGateLpbkCtrlRegSF CCP_SanityFunction7
#define	CCP_GetPhyGateLpbkCtrlRegSF CCP_SanityFunction8
#define	CCP_SetPhyDllMasterCtrlRegSF CCP_SanityFunction9
#define	CCP_GetPhyDllMasterCtrlRegSF CCP_SanityFunction10
#define	CCP_SetPhyDllSlaveCtrlRegSF CCP_SanityFunction11
#define	CCP_GetPhyDllSlaveCtrlRegSF CCP_SanityFunction12
#define	CCP_SetPhyIeTimingRegSF CCP_SanityFunction13
#define	CCP_GetPhyIeTimingRegSF CCP_SanityFunction14
#define	CCP_GetPhyObsReg0SF CCP_SanityFunction15
#define	CCP_GetPhyDllObsReg0SF CCP_SanityFunction16
#define	CCP_GetPhyDllObsReg1SF CCP_SanityFunction17
#define	CCP_GetPhyDllObsReg2SF CCP_SanityFunction18
#define	CCP_SetPhyStaticToggRegSF CCP_SanityFunction19
#define	CCP_GetPhyStaticToggRegSF CCP_SanityFunction20
#define	CCP_SetPhyWrRdDeskewCmdSF CCP_SanityFunction21
#define	CCP_GetPhyWrRdDeskewCmdSF CCP_SanityFunction22
#define	CCP_SetPhyWrDeskewPdCtrl0Dq0SF CCP_SanityFunction23
#define	CCP_GetPhyWrDeskewPdCtrl0Dq0SF CCP_SanityFunction24
#define	CCP_SetPhyCtrlMainSF CCP_SanityFunction25
#define	CCP_GetPhyCtrlMainSF CCP_SanityFunction26
#define	CCP_SetPhyTselRegSF CCP_SanityFunction27
#define	CCP_GetPhyTselRegSF CCP_SanityFunction28
#define	CCP_SetPhyGpioCtrl0SF CCP_SanityFunction29
#define	CCP_SetPhyGpioCtrl1SF CCP_SanityFunction29
#define	CCP_GetPhyGpioStatus0SF CCP_SanityFunction31
#define	CCP_GetPhyGpioStatus1SF CCP_SanityFunction31
#define	CCP_WaitForDllLockSF CCP_SanityFunction31
#define	CCP_GetPhyFeaturesRegSF CCP_SanityFunction34


#endif	/* CCP_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
