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

#ifndef FSM_STATE_DEV_H
#define FSM_STATE_DEV_H

#include "fsm_usb.h"

#include "usb_ssp_drd_regs.h"

#include "usb_ssp_drd_if.h"
#include "usb_ssp_drd_structs_if.h"

uint32_t interruptDevEvent(USB_SSP_DRD_PrivData *privData);
uint32_t transitionToDev(USB_SSP_DRD_PrivData *privData);

#endif /* FSM_STATE_DEV_H */
