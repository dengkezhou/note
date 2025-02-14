/**********************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
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
 * Cadence Combo PHY Core Driver
 **********************************************************************/

#include "ccp_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */

CCP_OBJ *CCP_GetInstance(void)
{
    static CCP_OBJ driver =
    {
        .probe = CCP_Probe,
        .init = CCP_Init,
        .setPhyDqTimingReg = CCP_SetPhyDqTimingReg,
        .getPhyDqTimingReg = CCP_GetPhyDqTimingReg,
        .setPhyDqsTimingReg = CCP_SetPhyDqsTimingReg,
        .getPhyDqsTimingReg = CCP_GetPhyDqsTimingReg,
        .setPhyGateLpbkCtrlReg = CCP_SetPhyGateLpbkCtrlReg,
        .getPhyGateLpbkCtrlReg = CCP_GetPhyGateLpbkCtrlReg,
        .setPhyDllMasterCtrlReg = CCP_SetPhyDllMasterCtrlReg,
        .getPhyDllMasterCtrlReg = CCP_GetPhyDllMasterCtrlReg,
        .setPhyDllSlaveCtrlReg = CCP_SetPhyDllSlaveCtrlReg,
        .getPhyDllSlaveCtrlReg = CCP_GetPhyDllSlaveCtrlReg,
        .setPhyIeTimingReg = CCP_SetPhyIeTimingReg,
        .getPhyIeTimingReg = CCP_GetPhyIeTimingReg,
        .getPhyObsReg0 = CCP_GetPhyObsReg0,
        .getPhyDllObsReg0 = CCP_GetPhyDllObsReg0,
        .getPhyDllObsReg1 = CCP_GetPhyDllObsReg1,
        .getPhyDllObsReg2 = CCP_GetPhyDllObsReg2,
        .setPhyStaticToggReg = CCP_SetPhyStaticToggReg,
        .getPhyStaticToggReg = CCP_GetPhyStaticToggReg,
        .setPhyWrRdDeskewCmd = CCP_SetPhyWrRdDeskewCmd,
        .getPhyWrRdDeskewCmd = CCP_GetPhyWrRdDeskewCmd,
        .setPhyWrDeskewPdCtrl0Dq0 = CCP_SetPhyWrDeskewPdCtrl0Dq0,
        .getPhyWrDeskewPdCtrl0Dq0 = CCP_GetPhyWrDeskewPdCtrl0Dq0,
        .setPhyCtrlMain = CCP_SetPhyCtrlMain,
        .getPhyCtrlMain = CCP_GetPhyCtrlMain,
        .setPhyTselReg = CCP_SetPhyTselReg,
        .getPhyTselReg = CCP_GetPhyTselReg,
        .setPhyGpioCtrl0 = CCP_SetPhyGpioCtrl0,
        .setPhyGpioCtrl1 = CCP_SetPhyGpioCtrl1,
        .getPhyGpioStatus0 = CCP_GetPhyGpioStatus0,
        .getPhyGpioStatus1 = CCP_GetPhyGpioStatus1,
        .waitForDllLock = CCP_WaitForDllLock,
        .getPhyFeaturesReg = CCP_GetPhyFeaturesReg,
    };

    return &driver;
}
