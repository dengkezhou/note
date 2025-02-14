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

#include "cusbd_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per
 * statement, DRV-4926" */

CUSBD_OBJ *CUSBD_GetInstance(void) {
  static CUSBD_OBJ driver = {
      .probe             = CUSBD_Probe,
      .init              = CUSBD_Init,
      .destroy           = CUSBD_Destroy,
      .start             = CUSBD_Start,
      .stop              = CUSBD_Stop,
      .isr               = CUSBD_Isr,
      .epEnable          = CUSBD_EpEnable,
      .epDisable         = CUSBD_EpDisable,
      .epSetHalt         = CUSBD_EpSetHalt,
      .epSetWedge        = CUSBD_EpSetWedge,
      .epFifoStatus      = CUSBD_EpFifoStatus,
      .epFifoFlush       = CUSBD_EpFifoFlush,
      .reqQueue          = CUSBD_ReqQueue,
      .reqDequeue        = CUSBD_ReqDequeue,
      .getDevInstance    = CUSBD_GetDevInstance,
      .dGetFrame         = CUSBD_DGetFrame,
      .dSetSelfpowered   = CUSBD_DSetSelfpowered,
      .dClearSelfpowered = CUSBD_DClearSelfpowered,
      .dGetConfigParams  = CUSBD_DGetConfigParams,
  };

  return &driver;
}
