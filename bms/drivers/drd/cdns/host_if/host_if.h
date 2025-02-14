/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * host_if.h
 * Cadence-USB-Device TI interface header file
 *
 *
 *
 *****************************************************************************/

#ifndef _HOST_IF_H_
#define _HOST_IF_H_

#include <string.h>
#include <stdint.h>
#include "cdn_xhci_if.h"
#include "dev_host_if.h"
#include "cusb_ch9_structs_if.h"
#include "cusb_ch9_if.h"
#include "trb.h"
#include "cdn_log.h"
#include "stdlib.h"

#define USB_HOST_REGS_OFFSET 0x10000

#if !(defined USBSSP_DEFAULT_TIMEOUT)
#define USBSSP_DEFAULT_TIMEOUT 1000000U
#endif

typedef struct {
  USBSSP_DriverResourcesT *xhci_driver_resources;
  uintptr_t ssp_hw_cores_base;
  CH9_UsbDeviceDescriptor * dev_desc;
} Host_profile;

Host_profile *usb_host_init(USB_InitTypeDef *init);
uint32_t usb_host_get_dev_desc(Host_profile *hprofile,
                               CH9_UsbDeviceDescriptor *DevDesc,
                               int retry_times);
USB_TRANSFER_STATUS
get_usb_host_transfer_status(USBSSP_DriverResourcesT *ssp_ref,
                             uint8_t uEndPoint);
uint32_t usb_host_write(USBSSP_DriverResourcesT *ssp_ref, uint8_t uEndPoint,
                        uint8_t *puData, uint32_t uSize, uint8_t isBlock);
uint32_t usb_host_read(USBSSP_DriverResourcesT *ssp_ref, uint8_t uEndPoint,
                       uint8_t *puData, uint32_t uSize, uint8_t isBlock);

#endif // _HOST_IF_H_
