/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************/

#include <cdn_inttypes.h>
#include <cdn_log.h>

#include "fsm_usb.h"
#include "fsm_state_a_idle.h"
#include "fsm_state_host.h"
#include "fsm_state_a_host.h"
#include "fsm_state_dev.h"
#include "fsm_state_b_idle.h"
#include "fsm_state_b_peripheral.h"

#include "usb_ssp_drd_hw.h"
#include "usb_ssp_drd_regs.h"

#include <cdn_errno.h>
#include <cdn_inttypes.h>

#include "usb_ssp_drd_if.h"
#include "usb_ssp_drd_structs_if.h"

/* Function for transitioning from AIdle to Host. */
static uint32_t transitionFromAIdleToHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Transition to Host. */
  status = transitionToHost(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from AIdle to Dev. */
static uint32_t transitionFromAIdleToDev(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Transition to Device. */
  status = transitionToDev(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from AIdle to A Host. */
static uint32_t transitionFromAIdleToAHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Transition to A Host. */
  status = transitionToAHost(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from AIdle to B Peripheral. */
static uint32_t transitionFromAIdleToBPerip(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Transition to B Peripheral. */
  status = transitionToBPeripheral(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from AIdle to B Idle. */
static uint32_t transitionFromAIdleToBIdle(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Transition to B Idle. */
  status = transitionToBIdle(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning to the AIdle state. */
uint32_t transitionToAIdle(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Set default event handlers. */
  setDefaultEvent(privData);
  /* Set only a subset of event handlers supported by the AIdle
     state. */
  privData->state.enableHost   = transitionFromAIdleToHost;
  privData->state.enableDev    = transitionFromAIdleToDev;
  privData->state.idDownVBusUp = transitionFromAIdleToAHost;
  privData->state.idUpVBusDown = transitionFromAIdleToBIdle;
  privData->state.idUpVBusUp   = transitionFromAIdleToBPerip;
  /* Enable pullup of ID pin line. */
  status = enableIdPullup(privData->regsBase);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}
