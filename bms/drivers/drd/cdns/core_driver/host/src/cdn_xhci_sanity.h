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
 * XHCI driver for both host and device mode header file
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

#ifndef CDN_XHCI_SANITY_H
#define CDN_XHCI_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "cdn_xhci_if.h"

uint32_t USBSSP_DriverContextTSF(const USBSSP_DriverContextT *obj);
uint32_t USBSSP_DriverResourcesTSF(const USBSSP_DriverResourcesT *obj);
uint32_t USBSSP_ForceHdrParamsSF(const USBSSP_ForceHdrParams *obj);
uint32_t USBSSP_XferBufferDescSF(const USBSSP_XferBufferDesc *obj);
uint32_t USBSSP_XhciResourcesTSF(const USBSSP_XhciResourcesT *obj);

uint32_t USBSSP_SanityFunction1(const USBSSP_DriverResourcesT *res,
                                const uint8_t epIndex);
uint32_t USBSSP_SanityFunction2(const USBSSP_DriverResourcesT *res,
                                const uint8_t epIndex,
                                const USBSSP_XferBufferDesc *bufferDesc);
uint32_t USBSSP_SanityFunction3(const USBSSP_DriverResourcesT *res,
                                const uint8_t endpoint);
uint32_t USBSSP_SanityFunction5(const USBSSP_DriverResourcesT *res);
uint32_t USBSSP_SanityFunction7(const USBSSP_DriverResourcesT *res,
                                const USBSSP_XhciResourcesT *memRes);
uint32_t USBSSP_SanityFunction15(const USBSSP_DriverResourcesT *res,
                                 const CH9_UsbSetup *setup);
uint32_t USBSSP_SanityFunction20(const USBSSP_DriverResourcesT *res,
                                 const uint8_t *desc);
uint32_t USBSSP_SanityFunction22(const USBSSP_DriverResourcesT *res,
                                 const uint32_t *index);
uint32_t USBSSP_SanityFunction23(const USBSSP_DriverResourcesT *res,
                                 const USBSSP_ExtraFlagsEnumT flags);
uint32_t USBSSP_SanityFunction28(const USBSSP_DriverResourcesT *res,
                                 const USBSSP_ForceHdrParams *trbDwords);
uint32_t USBSSP_SanityFunction31(const USBSSP_DriverResourcesT *res,
                                 const USBSSP_PortControlRegIdx portRegIdx);
uint32_t USBSSP_SanityFunction32(const USBSSP_DriverResourcesT *res,
                                 const USBSSP_PortControlRegIdx portRegIdx,
                                 const uint32_t *regValue);
uint32_t USBSSP_SanityFunction33(const USBSSP_DriverResourcesT *res,
                                 const USBSSP_DriverContextT *drvContext);

#define USBSSP_TransferDataSF          USBSSP_SanityFunction1
#define USBSSP_TransferVectorDataSF    USBSSP_SanityFunction2
#define USBSSP_StopEndpointSF          USBSSP_SanityFunction3
#define USBSSP_ResetEndpointSF         USBSSP_SanityFunction3
#define USBSSP_ResetDeviceSF           USBSSP_SanityFunction5
#define USBSSP_IsrSF                   USBSSP_SanityFunction5
#define USBSSP_SetMemResSF             USBSSP_SanityFunction7
#define USBSSP_InitSF                  USBSSP_SanityFunction5
#define USBSSP_GetDescriptorSF         USBSSP_SanityFunction5
#define USBSSP_SetAddressSF            USBSSP_SanityFunction5
#define USBSSP_ResetRootHubPortSF      USBSSP_SanityFunction5
#define USBSSP_IssueGenericCommandSF   USBSSP_SanityFunction5
#define USBSSP_EndpointSetFeatureSF    USBSSP_SanityFunction1
#define USBSSP_SetConfigurationSF      USBSSP_SanityFunction5
#define USBSSP_NBControlTransferSF     USBSSP_SanityFunction15
#define USBSSP_NoOpTestSF              USBSSP_SanityFunction5
#define USBSSP_EnableSlotSF            USBSSP_SanityFunction5
#define USBSSP_DisableSlotSF           USBSSP_SanityFunction5
#define USBSSP_EnableEndpointSF        USBSSP_SanityFunction20
#define USBSSP_DisableEndpointSF       USBSSP_SanityFunction5
#define USBSSP_GetMicroFrameIndexSF    USBSSP_SanityFunction22
#define USBSSP_SetEndpointExtraFlagSF  USBSSP_SanityFunction23
#define USBSSP_CleanEndpointExtraFlaSF USBSSP_SanityFunction23
#define USBSSP_GetEndpointExtraFlagSF  USBSSP_SanityFunction20
#define USBSSP_SetFrameIDSF            USBSSP_SanityFunction5
#define USBSSP_AddEventDataTRBSF       USBSSP_SanityFunction5
#define USBSSP_ForceHeaderSF           USBSSP_SanityFunction28
#define USBSSP_SetPortOverrideRegSF    USBSSP_SanityFunction5
#define USBSSP_GetPortOverrideRegSF    USBSSP_SanityFunction22
#define USBSSP_SetPortControlRegSF     USBSSP_SanityFunction31
#define USBSSP_GetPortControlRegSF     USBSSP_SanityFunction32
#define USBSSP_SaveStateSF             USBSSP_SanityFunction33
#define USBSSP_RestoreStateSF          USBSSP_SanityFunction33
#define USBSSP_GetPortConnectedSF      USBSSP_SanityFunction20
#define USBSSP_GetDevAddressStateSF    USBSSP_SanityFunction20

#endif /* CDN_XHCI_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
