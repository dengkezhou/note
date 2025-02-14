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
 * SD Host driver
 **********************************************************************/

#include "csdd_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */

CSDD_OBJ *CSDD_GetInstance(void)
{
    static CSDD_OBJ driver =
    {
        .probe = CSDD_Probe,
        .init = CSDD_Init,
        .start = CSDD_Start,
        .stop = CSDD_Stop,
        .execCardCommand = CSDD_ExecCardCommand,
        .deviceDetach = CSDD_DeviceDetach,
        .deviceAttach = CSDD_DeviceAttach,
        .abort = CSDD_Abort,
        .standBy = CSDD_StandBy,
        .configure = CSDD_Configure,
        .isr = CSDD_Isr,
        .configureHighSpeed = CSDD_ConfigureHighSpeed,
        .checkSlots = CSDD_CheckSlots,
        .checkInterrupt = CSDD_CheckInterrupt,
        .configureAccessMode = CSDD_ConfigureAccessMode,
        .tuning = CSDD_Tuning,
        .clockGeneratorSelect = CSDD_ClockGeneratorSelect,
        .presetValueSwitch = CSDD_PresetValueSwitch,
        .configureDriverStrength = CSDD_ConfigureDriverStrength,
        .memoryCardLoadDriver = CSDD_MemoryCardLoadDriver,
        .memoryCardDataTransfer = CSDD_MemoryCardDataTransfer,
        .memoryCardDataTransfer2 = CSDD_MemoryCardDataTransfer2,
        .memoryCardConfigure = CSDD_MemoryCardConfigure,
        .memoryCardDataErase = CSDD_MemoryCardDataErase,
        .memCardPartialDataXfer = CSDD_MemCardPartialDataXfer,
        .memCardInfXferStart = CSDD_MemCardInfXferStart,
        .memCardInfXferContinue = CSDD_MemCardInfXferContinue,
        .memCardInfXferFinish = CSDD_MemCardInfXferFinish,
        .memCardDataXferNonBlock = CSDD_MemCardDataXferNonBlock,
        .memCardFinishXferNonBlock = CSDD_MemCardFinishXferNonBlock,
        .phySettingsSd3 = CSDD_PhySettingsSd3,
        .phySettingsSd4 = CSDD_PhySettingsSd4,
        .writePhySet = CSDD_WritePhySet,
        .readPhySet = CSDD_ReadPhySet,
        .readCardStatus = CSDD_ReadCardStatus,
        .selectCard = CSDD_SelectCard,
        .resetCard = CSDD_ResetCard,
        .execCmd55Command = CSDD_ExecCmd55Command,
        .accessCccr = CSDD_AccessCccr,
        .readCsd = CSDD_ReadCsd,
        .readExCsd = CSDD_ReadExCsd,
        .getTupleFromCis = CSDD_GetTupleFromCis,
        .readSdStatus = CSDD_ReadSdStatus,
        .setDriverStrength = CSDD_SetDriverStrength,
        .execSetCurrentLimit = CSDD_ExecSetCurrentLimit,
        .mmcSwitch = CSDD_MmcSwitch,
        .mmcSetExtCsd = CSDD_MmcSetExtCsd,
        .mmcSetBootPartition = CSDD_MmcSetBootPartition,
        .mmcSetPartAccess = CSDD_MmcSetPartAccess,
        .mmcSetBootAck = CSDD_MmcSetBootAck,
        .mmcExecuteBoot = CSDD_MmcExecuteBoot,
        .mmcGetParitionBootSize = CSDD_MmcGetParitionBootSize,
        .getInterfaceType = CSDD_GetInterfaceType,
        .getDeviceState = CSDD_GetDeviceState,
        .memoryCardGetSecCount = CSDD_MemoryCardGetSecCount,
        .setDriverData = CSDD_SetDriverData,
        .getDriverData = CSDD_GetDriverData,
        .simpleInit = CSDD_SimpleInit,
        .resetHost = CSDD_ResetHost,
        .getRca = CSDD_GetRca,
        .cQEnable = CSDD_CQEnable,
        .cQDisable = CSDD_CQDisable,
        .cQGetInitConfig = CSDD_CQGetInitConfig,
        .cQGetUnusedTaskId = CSDD_CQGetUnusedTaskId,
        .cQStartExecuteTask = CSDD_CQStartExecuteTask,
        .cQAttachRequest = CSDD_CQAttachRequest,
        .cQExecuteDcmdRequest = CSDD_CQExecuteDcmdRequest,
        .cQGetDirectCmdConfig = CSDD_CQGetDirectCmdConfig,
        .cQSetDirectCmdConfig = CSDD_CQSetDirectCmdConfig,
        .cQSetIntCoalescingConfig = CSDD_CQSetIntCoalescingConfig,
        .cQGetIntCoalescingConfig = CSDD_CQGetIntCoalescingConfig,
        .cQGetIntCoalescingTimeoutBase = CSDD_CQGetIntCoalescingTimeoutBase,
        .cQStartExecuteTasks = CSDD_CQStartExecuteTasks,
        .cQHalt = CSDD_CQHalt,
        .cQTaskDiscard = CSDD_CQTaskDiscard,
        .cQAllTasksDiscard = CSDD_CQAllTasksDiscard,
        .cQResetIntCoalCounters = CSDD_CQResetIntCoalCounters,
        .cQSetResponseErrorMask = CSDD_CQSetResponseErrorMask,
        .cQGetResponseErrorMask = CSDD_CQGetResponseErrorMask,
        .getBaseClk = CSDD_GetBaseClk,
        .waitForRequest = CSDD_WaitForRequest,
        .setCPhyConfigIoDelay = CSDD_SetCPhyConfigIoDelay,
        .getCPhyConfigIoDelay = CSDD_GetCPhyConfigIoDelay,
        .setCPhyConfigLvsi = CSDD_SetCPhyConfigLvsi,
        .getCPhyConfigLvsi = CSDD_GetCPhyConfigLvsi,
        .setCPhyConfigDfiRd = CSDD_SetCPhyConfigDfiRd,
        .getCPhyConfigDfiRd = CSDD_GetCPhyConfigDfiRd,
        .setCPhyConfigOutputDelay = CSDD_SetCPhyConfigOutputDelay,
        .getCPhyConfigOutputDelay = CSDD_GetCPhyConfigOutputDelay,
        .cPhyDllReset = CSDD_CPhyDllReset,
        .setCPhyExtMode = CSDD_SetCPhyExtMode,
        .getCPhyExtMode = CSDD_GetCPhyExtMode,
        .setCPhySdclkAdj = CSDD_SetCPhySdclkAdj,
        .getCPhySdclkAdj = CSDD_GetCPhySdclkAdj,
    };

    return &driver;
}
