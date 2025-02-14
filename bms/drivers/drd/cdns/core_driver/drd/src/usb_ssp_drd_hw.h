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

#ifndef USB_SSP_DRD_HW_H
#define USB_SSP_DRD_HW_H

#include "usb_ssp_drd_regs.h"
#include "usb_ssp_drd_if.h"
#include "usb_ssp_drd_structs_if.h"

uint32_t readDID(USB_SspDrdRegs *regsBase);
uint32_t readRID(USB_SspDrdRegs *regsBase);
USB_SSP_DRD_Mode readStrapMode(USB_SspDrdRegs *regsBase);
bool checkIfControllerIsReady(USB_SspDrdRegs *regsBase);
void readIdVbus(USB_SspDrdRegs *regsBase, uint32_t *idVal, uint32_t *vBus);
void enableAllInterrupts(USB_SspDrdRegs *regsBase);
void clearAllInterrupts(USB_SspDrdRegs *regsBase);
uint32_t readInterruptVector(USB_SspDrdRegs *regsBase);
USB_SSP_DRD_Mode readDrdMode(USB_SspDrdRegs *regsBase);
uint32_t enableIdPullup(USB_SspDrdRegs *regsBase);
void enableHwAHost(USB_SspDrdRegs *regsBase);
void enableBPeripheral(USB_SspDrdRegs *regsBase);
void disableHostDevice(USB_SspDrdRegs *regsBase);
void enableFastSim(USB_SspDrdRegs *regsBase);
void switchOtg2ToPeripheral(USB_SspDrdRegs *regsBase);

#endif /* USB_SSP_DRD_HW_H */
