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
 * USB 3.0 specification USB 2.0 specification And others Specification
 * defined by USB organization  Because of when this file was creating
 * USB 3.1 specification was the latest published so it mostly based
 * on this specification. USB 3.1 specification does not contains all
 * descriptors and definitions included in older specification so
 * cusb_ch9_if.h file also refers to other specification defined by
 * USB organization.
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

#ifndef CUSB_CH9_SANITY_H
#define CUSB_CH9_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "cusb_ch9_if.h"

uint32_t CH9_ConfigParamsSF(const CH9_ConfigParams *obj);
uint32_t
CH9_Usb20ExtensionDescriptorSF(const CH9_Usb20ExtensionDescriptor *obj);
uint32_t CH9_UsbBosDescriptorSF(const CH9_UsbBosDescriptor *obj);
uint32_t CH9_UsbCapabilityDescriptorSF(const CH9_UsbCapabilityDescriptor *obj);
uint32_t
CH9_UsbConfigurationDescriptSF(const CH9_UsbConfigurationDescriptor *obj);
uint32_t
CH9_UsbContainerIdDescriptorSF(const CH9_UsbContainerIdDescriptor *obj);
uint32_t CH9_UsbDeviceDescriptorSF(const CH9_UsbDeviceDescriptor *obj);
uint32_t
CH9_UsbDeviceQualifierDescriSF(const CH9_UsbDeviceQualifierDescriptor *obj);
uint32_t CH9_UsbEndpointDescriptorSF(const CH9_UsbEndpointDescriptor *obj);
uint32_t CH9_UsbHeaderDescriptorSF(const CH9_UsbHeaderDescriptor *obj);
uint32_t CH9_UsbInterfaceAssociationDSF(
    const CH9_UsbInterfaceAssociationDescriptor *obj);
uint32_t CH9_UsbInterfaceDescriptorSF(const CH9_UsbInterfaceDescriptor *obj);
uint32_t CH9_UsbOtgDescriptorSF(const CH9_UsbOtgDescriptor *obj);
uint32_t CH9_UsbOtherSpeedConfiguratiSF(
    const CH9_UsbOtherSpeedConfigurationDescriptor *obj);
uint32_t
CH9_UsbPTMCapabilityDescriptSF(const CH9_UsbPTMCapabilityDescriptor *obj);
uint32_t CH9_UsbPlatformDescriptorSF(const CH9_UsbPlatformDescriptor *obj);
uint32_t
CH9_UsbSSDeviceCapabilityDesSF(const CH9_UsbSSDeviceCapabilityDescriptor *obj);
uint32_t
CH9_UsbSSEndpointCompanionDeSF(const CH9_UsbSSEndpointCompanionDescriptor *obj);
uint32_t CH9_UsbSSPlusDescriptorSF(const CH9_UsbSSPlusDescriptor *obj);
uint32_t CH9_UsbSSPlusIsocEndpointComSF(
    const CH9_UsbSSPlusIsocEndpointCompanionDescriptor *obj);
uint32_t CH9_UsbSetupSF(const CH9_UsbSetup *obj);
uint32_t CH9_UsbStringDescriptorSF(const CH9_UsbStringDescriptor *obj);

#endif /* CUSB_CH9_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
