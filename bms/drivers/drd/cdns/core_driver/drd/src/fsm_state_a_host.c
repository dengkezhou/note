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

#include "usb_ssp_drd_hw.h"
#include "usb_ssp_drd_regs.h"

#if !(defined USB_SSP_DRD_VBUS_FALL_DELAY)
#define USB_SSP_DRD_VBUS_FALL_DELAY 11000000U
#endif

/* Function for disabling a host mode of operation. */
static uint32_t disableAHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status          = CDN_EOK;
  USB_SSP_DRD_Mode drdMode = USB_SSP_DRD_HOST;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);
  /* Check if callback for disabling host is set. */
  if (NULL == privData->callbacks.disableHost) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: disableHost callback is not set\n",
           __func__);
    status = CDN_EPROTO;
  } else {
    /* Disable host by calling a callback. Callback should use a
       host driver. */
    status = privData->callbacks.disableHost(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: disableHost callback failed\n",
             __func__);
    } else {
      /* Disable host and device in hardware. */
      disableHostDevice(privData->regsBase);

      DbgMsg(DBG_GEN_MSG, DBG_FYI,
             "%s, Will wait 11 ms for controller to timeout waiting for VBUS "
             "to fall.\n",
             __func__);
      /* Wait for VBUS to fall. */
      CPS_DelayNs(USB_SSP_DRD_VBUS_FALL_DELAY);

      /* Read mode of operation for later checking. */
      drdMode = readDrdMode(privData->regsBase);
      DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s, drdMode: %d\n", __func__, drdMode);

      /* Check if mode of operation is DRD. */
      if (USB_SSP_DRD_DRD != drdMode) {
        /* Mode of operation is not DRD. Retrun an error. */
        status = CDN_EPROTO;
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
      }
    }
  }

  return status;
}

/* Function for transitioning from A Host to A Idle. */
static uint32_t transitionFromAHostToAIdle(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);

  /* Disable host. */
  status = disableAHost(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  } else {
    /* Call function that transitions to the A Idle state. */
    status = transitionToAIdle(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
    }
  }

  return status;
}

/* Function for transitioning from A Host to B Idle. */
static uint32_t transitionFromAHostToBIdle(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);

  /* Disable host. */
  status = disableAHost(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  } else {
    /* Call function that transitions to B Idle state. */
    status = transitionToBIdle(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
    }
  }

  return status;
}

/* Function for transitioning from A Host to Device. */
static uint32_t transitionFromAHostToDev(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);

  /* Disable host. */
  status = disableAHost(privData);
  if (CDN_EOK != status) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
  } else {
    /* Disable host and device in hardware. */
    disableHostDevice(privData->regsBase);
    /* Call function that transitions to the device state. */
    status = transitionToDev(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s\n", __func__);
    }
  }

  return status;
}

/* Function for transitioning to the A Host state. */
uint32_t transitionToAHost(USB_SSP_DRD_PrivData *privData) {
  uint32_t status = CDN_EOK;
  DbgMsg(DBG_GEN_MSG, DBG_FYI, "%s\n", __func__);

  /* Set default event handlers. */
  setDefaultEvent(privData);
  /* Set only a subset of event handlers supported by the A Host
     state. */
  privData->state.isr            = interruptHostEvent;
  privData->state.idDownVBusDown = transitionFromAHostToAIdle;
  privData->state.idUpVBusDown   = transitionFromAHostToBIdle;
  privData->state.idUpVBusUp     = transitionFromAHostToBIdle;
  privData->state.enableDev      = transitionFromAHostToDev;
  /* Check if callback for enabling host is set. */
  if (NULL == privData->callbacks.enableHost) {
    DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: enableHost callback is not set\n",
           __func__);
    status = CDN_EPROTO;
  } else {
    /* Enable the A Host mode in hardware. */
    enableHwAHost(privData->regsBase);
    /* Call callback for enabling host mode. Callback should use a
       host driver.*/
    status = privData->callbacks.enableHost(privData);
    if (CDN_EOK != status) {
      DbgMsg(DBG_GEN_MSG, DBG_CRIT, "ERROR %s: enableHost callback failed\n",
             __func__);
    }
  }
  return status;
}
