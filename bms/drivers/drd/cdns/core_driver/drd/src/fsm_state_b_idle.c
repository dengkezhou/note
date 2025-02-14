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
#include "fsm_state_host.h"
#include "fsm_state_dev.h"
#include "fsm_state_a_idle.h"
#include "fsm_state_a_host.h"
#include "fsm_state_b_idle.h"
#include "fsm_state_b_peripheral.h"

#include "usb_ssp_drd_if.h"
#include "usb_ssp_drd_structs_if.h"

/* Function for transitioning from B Idle to Host state. */
static uint32_t transitionFromBIdleToHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Call function that transitions to Host state. */
  status = transitionToHost(privData);
  if (CDN_EOK != status) {
    /* Check if Host state was enabled. */
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from B Idle to Device state. */
static uint32_t transitionFromBIdleToDev(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Call function that transitions to Device state. */
  status = transitionToDev(privData);
  if (CDN_EOK != status) {
    /* Check if Device state was enabled. */
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from B Idle to A Idle state. */
static uint32_t transitionFromBIdleToAIdle(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Call function that transitions to A Host state. */
  status = transitionToAIdle(privData);
  if (CDN_EOK != status) {
    /* Check if A Idle state was enabled. */
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from B Idle to A Host state. */
static uint32_t transitionFromBIdleToAHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Call function that transitions to A Host state. */
  status = transitionToAHost(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from B Idle to B Peripheral state. */
static uint32_t
transitionFromBIdleToBPeriphera(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Call function that transitions to B Peripheral state. */
  status = transitionToBPeripheral(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Funtction for transitioning to the B Idle state. */
uint32_t transitionToBIdle(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Set default event handlers. */
  setDefaultEvent(privData);
  /* Set only a subset of event handlers supported by the B Idle
     state. */
  privData->state.enableHost     = transitionFromBIdleToHost;
  privData->state.enableDev      = transitionFromBIdleToDev;
  privData->state.idDownVBusDown = transitionFromBIdleToAIdle;
  privData->state.idDownVBusUp   = transitionFromBIdleToAHost;
  privData->state.idUpVBusUp     = transitionFromBIdleToBPeriphera;
  /* Check if callback for enabling device in B Idle mode. */
  if (NULL == privData->callbacks.enableBIdleDev) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT,
           "ERROR %s: enableBIdleDev callback is not set\n", __func__);
    status = CDN_EPROTO;
  } else {
    /* Call callback for enabling device in B Idle mode. Callback
       should use device driver. */
    status = privData->callbacks.enableBIdleDev(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT,
             "ERROR %s: enableBIdleDev callback failed\n", __func__);
    }
  }
  return status;
}
