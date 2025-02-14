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

#include "usb_ssp_drd_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per
 * statement, DRV-4926" */

USB_SSP_DRD_OBJ *USB_SSP_DRD_GetInstance(void) {
  static USB_SSP_DRD_OBJ driver = {
      .Probe              = USB_SSP_DRD_Probe,
      .Init               = USB_SSP_DRD_Init,
      .Isr                = USB_SSP_DRD_Isr,
      .Start              = USB_SSP_DRD_Start,
      .Stop               = USB_SSP_DRD_Stop,
      .Destroy            = USB_SSP_DRD_Destroy,
      .CheckIfReady       = USB_SSP_DRD_CheckIfReady,
      .CheckStrapMode     = USB_SSP_DRD_CheckStrapMode,
      .CheckOperationMode = USB_SSP_DRD_CheckOperationMode,
      .SetOperationMode   = USB_SSP_DRD_SetOperationMode,
      .CheckIrq           = USB_SSP_DRD_CheckIrq,
      .ProcessIrq         = USB_SSP_DRD_ProcessIrq,
  };

  return &driver;
}
