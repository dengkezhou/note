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
 * Layer interface for the Cadence DMA controller
 **********************************************************************/

#include "cusbdma_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per
 * statement, DRV-4926" */

CUSBDMA_OBJ *CUSBDMA_GetInstance(void) {
  static CUSBDMA_OBJ driver = {
      .probe                   = CUSBDMA_Probe,
      .init                    = CUSBDMA_Init,
      .destroy                 = CUSBDMA_Destroy,
      .channelAlloc            = CUSBDMA_ChannelAlloc,
      .channelReset            = CUSBDMA_ChannelReset,
      .channelRelease          = CUSBDMA_ChannelRelease,
      .channelProgram          = CUSBDMA_ChannelProgram,
      .channelTrigger          = CUSBDMA_ChannelTrigger,
      .channelUpdateState      = CUSBDMA_ChannelUpdateState,
      .channelSetMaxPktSz      = CUSBDMA_ChannelSetMaxPktSz,
      .channelHandleStall      = CUSBDMA_ChannelHandleStall,
      .channelFreeHeadTrbChain = CUSBDMA_ChannelFreeHeadTrbChain,
  };

  return &driver;
}
