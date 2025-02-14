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
 * Layer interface for the Cadence USB device controller family
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

#ifndef CUSBD_SANITY_H
#define CUSBD_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "cusbd_if.h"

uint32_t CUSBD_CallbacksSF(const CUSBD_Callbacks *obj);
uint32_t CUSBD_ConfigSF(const CUSBD_Config *obj);
uint32_t CUSBD_DevSF(const CUSBD_Dev *obj);
uint32_t CUSBD_EpPrivateSF(const CUSBD_EpPrivate *obj);
uint32_t CUSBD_EpSF(const CUSBD_Ep *obj);
uint32_t CUSBD_PrivateDataSF(const CUSBD_PrivateData *obj);
uint32_t CUSBD_ReqSF(const CUSBD_Req *obj);

uint32_t CUSBD_SanityFunction1(const CUSBD_Config *config,
                               const CUSBD_SysReq *sysReqCusbd);
uint32_t CUSBD_SanityFunction2(const CUSBD_PrivateData *pD,
                               const CUSBD_Config *config,
                               const CUSBD_Callbacks *callbacks);
uint32_t CUSBD_SanityFunction3(const CUSBD_PrivateData *pD);
uint32_t CUSBD_SanityFunction7(const CUSBD_PrivateData *pD, const CUSBD_Ep *ep,
                               const uint8_t *desc);
uint32_t CUSBD_SanityFunction8(const CUSBD_PrivateData *pD, const CUSBD_Ep *ep);
uint32_t CUSBD_SanityFunction13(const CUSBD_PrivateData *pD, const CUSBD_Ep *ep,
                                const CUSBD_Req *req);
uint32_t CUSBD_SanityFunction15(const CUSBD_PrivateData *pD,
                                const CUSBD_Dev **dev);
uint32_t CUSBD_SanityFunction16(const CUSBD_PrivateData *pD,
                                const uint32_t *numOfFrame);
uint32_t CUSBD_SanityFunction19(const CUSBD_PrivateData *pD,
                                const CH9_ConfigParams *configParams);

#define CUSBD_ProbeSF             CUSBD_SanityFunction1
#define CUSBD_InitSF              CUSBD_SanityFunction2
#define CUSBD_DestroySF           CUSBD_SanityFunction3
#define CUSBD_StartSF             CUSBD_SanityFunction3
#define CUSBD_StopSF              CUSBD_SanityFunction3
#define CUSBD_IsrSF               CUSBD_SanityFunction3
#define CUSBD_EpEnableSF          CUSBD_SanityFunction7
#define CUSBD_EpDisableSF         CUSBD_SanityFunction8
#define CUSBD_EpSetHaltSF         CUSBD_SanityFunction8
#define CUSBD_EpSetWedgeSF        CUSBD_SanityFunction8
#define CUSBD_EpFifoStatusSF      CUSBD_SanityFunction8
#define CUSBD_EpFifoFlushSF       CUSBD_SanityFunction8
#define CUSBD_ReqQueueSF          CUSBD_SanityFunction13
#define CUSBD_ReqDequeueSF        CUSBD_SanityFunction13
#define CUSBD_GetDevInstanceSF    CUSBD_SanityFunction15
#define CUSBD_DGetFrameSF         CUSBD_SanityFunction16
#define CUSBD_DSetSelfpoweredSF   CUSBD_SanityFunction3
#define CUSBD_DClearSelfpoweredSF CUSBD_SanityFunction3
#define CUSBD_DGetConfigParamsSF  CUSBD_SanityFunction19

#endif /* CUSBD_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
