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

#include "usb_ssp_drd_if.h"
#include "usb_ssp_drd_structs_if.h"

#include "usb_ssp_drd_hw.h"
#include "usb_ssp_drd_regs.h"

/* Function for transitioning from B Peripheral to A Host. */
static uint32_t
transitionFromBPeripheralToAIdl(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Check if callback for disabling device is set. */
  if (NULL == privData->callbacks.disableDev) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: disableDev callback is not set\n",
           __func__);
    status = CDN_EPROTO;
  } else {
    /* Disable device by calling a callback. Callback should use a
       device driver. */
    status = privData->callbacks.disableDev(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: disableDev callback failed\n",
             __func__);
    } else {
      /* Disable host and device in hardware. */
      disableHostDevice(privData->regsBase);
      /* Change state to A Host. */
      status = transitionToAIdle(privData);
      if (CDN_EOK != status) {
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
      }
    }
  }
  return status;
}

/* Function for transitioning from B Peripheral to B Idle. */
static uint32_t
transitionFromBPeripheralToBIdl(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Change the state of FSM */
  status = transitionToBIdle(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  }
  return status;
}

/* Function for transitioning from B Peripheral to Host. */
static uint32_t
transitionFromBPeripheralToHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Check if callback for disabling device is set. */
  if (NULL == privData->callbacks.disableDev) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: disableDev callback is not set\n",
           __func__);
    status = CDN_EPROTO;
  } else {
    /* Disable Device by calling a callback. Callback should use a
       device driver. */
    status = privData->callbacks.disableDev(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: disableHost callback failed\n",
             __func__);
    } else {
      /* Disable host and device in hardware. */
      disableHostDevice(privData->regsBase);
      /* Transition to host. */
      status = transitionToHost(privData);
      if (CDN_EOK != status) {
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
      }
    }
  }
  return status;
}

/* Function for transitioning to the B Peripheral state. */
uint32_t transitionToBPeripheral(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);

  /* Set default event handlers. */
  setDefaultEvent(privData);
  /* Set only a subset of event handlers supported by the B
     Peripheral state. */
  privData->state.isr            = interruptDevEvent;
  privData->state.idDownVBusDown = transitionFromBPeripheralToAIdl;
  privData->state.idDownVBusUp   = transitionFromBPeripheralToAIdl;
  privData->state.idUpVBusDown   = transitionFromBPeripheralToBIdl;
  privData->state.enableHost     = transitionFromBPeripheralToHost;

  /* Check if callback for enabling device is set. */
  if (NULL == privData->callbacks.enableDev) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: enableDev callback is not set\n",
           __func__);
    status = CDN_EPROTO;
  } else {
    /* Enable peripheral mode in hardware. */
    enableBPeripheral(privData->regsBase);
    /* Call callback for enabling device mode. Callback should use a
       device driver. */
    status = privData->callbacks.enableDev(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: enableDev callback failed\n",
             __func__);
    }
  }
  return status;
}
