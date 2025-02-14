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

#ifndef FSM_USB_H
#define FSM_USB_H

#include "usb_ssp_drd_if.h"
#include "usb_ssp_drd_regs.h"

/**
 *  \brief Function sets default transition functions in a state.
 *
 *  This function is supposed to be called upon entering new
 *  state. This function will set every event handler of a state to
 *  default.
 *
 *  \param privData Pointer to driver's private data object.
 *  \return void
 */
void setDefaultEvent(USB_SSP_DRD_PrivData *privData);

/**
 *  \brief Function triggers FSM events based on values of ID pin and
 *  VBUS.
 *
 *  \param privData Pointer to driver's private data object.
 *  \return CDN_EOK if function succeed
 *  \return negative vale if function failed.
 */
uint32_t processIdVbus(USB_SSP_DRD_PrivData *privData);

/**
 *  \brief Function starts FSM.
 *
 *  Function checks if FSM can be initialized and starts FSM.
 *
 *  \param privData Pointer to driver's private data object.
 *  \return CDN_EOK if function succeed
 *  \return negative vale if function failed.
 */
uint32_t startFsm(USB_SSP_DRD_PrivData *privData);

#endif /* FSM_USB_H */
