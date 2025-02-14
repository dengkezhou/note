/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
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
 * Cadence Core Driver for USB SSP DRD
 **********************************************************************/

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit
 * of 10, DRV-4789" */
/* parasoft-begin-suppress METRIC.CC-3 "Follow the Cyclomatic Complexity limit
 * of 30, DRV-4417" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from
 * more than 5 different functions, DRV-3823" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function
 * should not be higher than 4, DRV-4790" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per
 * statement, DRV-4926" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not
 * be defined with external linkage if they are referenced in only one
 * translation unit, DRV-4139" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong
 * parameter value(s).
 */

#ifndef USB_SSP_DRD_SANITY_H
#define USB_SSP_DRD_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "usb_ssp_drd_if.h"

uint32_t USB_SSP_DRD_CallbacksSF(const USB_SSP_DRD_Callbacks *obj);
uint32_t USB_SSP_DRD_ConfigSF(const USB_SSP_DRD_Config *obj);
uint32_t USB_SSP_DRD_PrivDataSF(const USB_SSP_DRD_PrivData *obj);

uint32_t USB_SSP_DRD_SanityFunction1(const USB_SSP_DRD_SysReq *sysReq);
uint32_t USB_SSP_DRD_SanityFunction2(const USB_SSP_DRD_PrivData *privData,
                                     const USB_SSP_DRD_Config *config,
                                     const USB_SSP_DRD_Callbacks *callbacks);
uint32_t USB_SSP_DRD_SanityFunction3(const USB_SSP_DRD_PrivData *privData);
uint32_t USB_SSP_DRD_SanityFunction7(const USB_SSP_DRD_PrivData *privData,
                                     const bool *isReady);
uint32_t USB_SSP_DRD_SanityFunction8(const USB_SSP_DRD_PrivData *privData,
                                     const USB_SSP_DRD_Mode *strapMode);
uint32_t USB_SSP_DRD_SanityFunction10(const USB_SSP_DRD_PrivData *privData,
                                      const USB_SSP_DRD_Mode operationMode);
uint32_t USB_SSP_DRD_SanityFunction11(const USB_SSP_DRD_PrivData *privData,
                                      const uint32_t *interruptVect);

#define USB_SSP_DRD_ProbeSF            USB_SSP_DRD_SanityFunction1
#define USB_SSP_DRD_InitSF             USB_SSP_DRD_SanityFunction2
#define USB_SSP_DRD_IsrSF              USB_SSP_DRD_SanityFunction3
#define USB_SSP_DRD_StartSF            USB_SSP_DRD_SanityFunction3
#define USB_SSP_DRD_StopSF             USB_SSP_DRD_SanityFunction3
#define USB_SSP_DRD_DestroySF          USB_SSP_DRD_SanityFunction3
#define USB_SSP_DRD_CheckIfReadySF     USB_SSP_DRD_SanityFunction7
#define USB_SSP_DRD_CheckStrapModeSF   USB_SSP_DRD_SanityFunction8
#define USB_SSP_DRD_CheckOperationMoSF USB_SSP_DRD_SanityFunction8
#define USB_SSP_DRD_SetOperationModeSF USB_SSP_DRD_SanityFunction10
#define USB_SSP_DRD_CheckIrqSF         USB_SSP_DRD_SanityFunction11
#define USB_SSP_DRD_ProcessIrqSF       USB_SSP_DRD_SanityFunction3

#endif /* USB_SSP_DRD_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
