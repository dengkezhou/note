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
 * Extracted data
 **********************************************************************/

#include "ccpext_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */

CCPEXT_OBJ *CCPEXT_GetInstance(void)
{
    static CCPEXT_OBJ driver =
    {
        .setPhyWrDeskewPdCtrl0Dqx = CCPEXT_SetPhyWrDeskewPdCtrl0Dqx,
        .getPhyWrDeskewPdCtrl0Dqx = CCPEXT_GetPhyWrDeskewPdCtrl0Dqx,
        .setPhyWrDeskewReg = CCPEXT_SetPhyWrDeskewReg,
        .getPhyWrDeskewReg = CCPEXT_GetPhyWrDeskewReg,
        .setPhyRdDeskewReg = CCPEXT_SetPhyRdDeskewReg,
        .getPhyRdDeskewReg = CCPEXT_GetPhyRdDeskewReg,
        .setPhyWrDeskewPdCtrl1Reg = CCPEXT_SetPhyWrDeskewPdCtrl1Reg,
        .getPhyWrDeskewPdCtrl1Reg = CCPEXT_GetPhyWrDeskewPdCtrl1Reg,
        .setPhyCtrlLowFreqSel = CCPEXT_SetPhyCtrlLowFreqSel,
        .getPhyCtrlLowFreqSel = CCPEXT_GetPhyCtrlLowFreqSel,
        .setPhyWrRdDeskewCmdExt = CCPEXT_SetPhyWrRdDeskewCmdExt,
        .getPhyWrRdDeskewCmdExt = CCPEXT_GetPhyWrRdDeskewCmdExt,
    };

    return &driver;
}
