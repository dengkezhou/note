/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.06.f48696b
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core driver for eXpanded Serial Peripheral Interface
 **********************************************************************/

#include "xspi_obj_if.h"

/* parasoft suppress item METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */

XSPI_OBJ *XSPI_GetInstance(void)
{
    static XSPI_OBJ driver =
    {
        .probe = XSPI_Probe,
        .init = XSPI_Init,
        .destroy = XSPI_Destroy,
        .start = XSPI_Start,
        .stop = XSPI_Stop,
        .isr = XSPI_Isr,
        .setWorkMode = XSPI_SetWorkMode,
        .getWorkMode = XSPI_GetWorkMode,
        .setEventEnable = XSPI_SetEventEnable,
        .getEventEnable = XSPI_GetEventEnable,
        .setCallbacks = XSPI_SetCallbacks,
        .getCallbacks = XSPI_GetCallbacks,
        .setWriteProtect = XSPI_SetWriteProtect,
        .getWriteProtect = XSPI_GetWriteProtect,
        .setDmaConfig = XSPI_SetDmaConfig,
        .getDmaConfig = XSPI_GetDmaConfig,
        .setSpiClockMode = XSPI_SetSpiClockMode,
        .getSpiClockMode = XSPI_GetSpiClockMode,
        .getResetConfig = XSPI_GetResetConfig,
        .setResetConfig = XSPI_SetResetConfig,
        .assertReset = XSPI_AssertReset,
        .deAssertReset = XSPI_DeAssertReset,
        .setDeviceRelativeDelays = XSPI_SetDeviceRelativeDelays,
        .getDeviceRelativeDelays = XSPI_GetDeviceRelativeDelays,
        .setGlobalCmdParameters = XSPI_SetGlobalCmdParameters,
        .getGlobalCmdParameters = XSPI_GetGlobalCmdParameters,
        .setSpiNandCmdParameters = XSPI_SetSpiNandCmdParameters,
        .getSpiNandCmdParameters = XSPI_GetSpiNandCmdParameters,
        .setXipModeBitsConfig = XSPI_SetXipModeBitsConfig,
        .getXipModeBitsConfig = XSPI_GetXipModeBitsConfig,
        .sendDirectCommand = XSPI_SendDirectCommand,
        .isDirectCmdEngBusy = XSPI_IsDirectCmdEngBusy,
        .setDirectModeConfig = XSPI_SetDirectModeConfig,
        .getDirectModeConfig = XSPI_GetDirectModeConfig,
        .setP2ActiveDevMaxCycles = XSPI_SetP2ActiveDevMaxCycles,
        .getP2ActiveDevMaxCycles = XSPI_GetP2ActiveDevMaxCycles,
        .setProgramSeqP1Config = XSPI_SetProgramSeqP1Config,
        .getProgramSeqP1Config = XSPI_GetProgramSeqP1Config,
        .setProgramSeqP2Config = XSPI_SetProgramSeqP2Config,
        .getProgramSeqP2Config = XSPI_GetProgramSeqP2Config,
        .setReadSeqP1Config = XSPI_SetReadSeqP1Config,
        .getReadSeqP1Config = XSPI_GetReadSeqP1Config,
        .setReadSeqP2Config = XSPI_SetReadSeqP2Config,
        .getReadSeqP2Config = XSPI_GetReadSeqP2Config,
        .setWelSeqConfig = XSPI_SetWelSeqConfig,
        .getWelSeqConfig = XSPI_GetWelSeqConfig,
        .setCommStatSeqConfig = XSPI_SetCommStatSeqConfig,
        .getCommStatSeqConfig = XSPI_GetCommStatSeqConfig,
        .setStatSeqP1Config = XSPI_SetStatSeqP1Config,
        .getStatSeqP1Config = XSPI_GetStatSeqP1Config,
        .setStatSeqP2Config = XSPI_SetStatSeqP2Config,
        .getStatSeqP2Config = XSPI_GetStatSeqP2Config,
        .setStatSeqSpiNandConfig = XSPI_SetStatSeqSpiNandConfig,
        .getStatSeqSpiNandConfig = XSPI_GetStatSeqSpiNandConfig,
        .sendStigCommand = XSPI_SendStigCommand,
        .getStigStatus = XSPI_GetStigStatus,
        .setJedecResetTimingConfig = XSPI_SetJedecResetTimingConfig,
        .getJedecResetTimingConfig = XSPI_GetJedecResetTimingConfig,
        .sendStigJedecReset = XSPI_SendStigJedecReset,
        .setContinueProcOnDescError = XSPI_SetContinueProcOnDescError,
        .getContinueProcOnDescError = XSPI_GetContinueProcOnDescError,
        .getLatestBootStatus = XSPI_GetLatestBootStatus,
        .setDeviceDiscoveryConfig = XSPI_SetDeviceDiscoveryConfig,
        .getDeviceDiscoveryConfig = XSPI_GetDeviceDiscoveryConfig,
        .runDeviceDiscovery = XSPI_RunDeviceDiscovery,
        .getDeviceDiscoveryStatus = XSPI_GetDeviceDiscoveryStatus,
        .setResetRecoveryDelay = XSPI_SetResetRecoveryDelay,
        .getResetRecoveryDelay = XSPI_GetResetRecoveryDelay,
        .setPollingConfig = XSPI_SetPollingConfig,
        .getPollingConfig = XSPI_GetPollingConfig,
        .setHyperFlashOffsetConfig = XSPI_SetHyperFlashOffsetConfig,
        .getHyperFlashOffsetConfig = XSPI_GetHyperFlashOffsetConfig,
        .setPhyConfig = XSPI_SetPhyConfig,
        .getPhyConfig = XSPI_GetPhyConfig,
        .phyWriteDllReset = XSPI_PhyWriteDllReset,
        .sendCdmaCommand = XSPI_SendCdmaCommand,
        .getCdmaCommandStatus = XSPI_GetCdmaCommandStatus,
        .sendCdmaCommandChain = XSPI_SendCdmaCommandChain,
        .getCdmaChainStatus = XSPI_GetCdmaChainStatus,
        .sendPioCommand = XSPI_SendPioCommand,
        .getPioCommandStatus = XSPI_GetPioCommandStatus,
        .getAcmdLastCmdStatus = XSPI_GetAcmdLastCmdStatus,
        .setResetSeqConfig = XSPI_SetResetSeqConfig,
        .getResetSeqConfig = XSPI_GetResetSeqConfig,
        .setEraseSecConfig = XSPI_SetEraseSecConfig,
        .getEraseSecConfig = XSPI_GetEraseSecConfig,
        .setChipEraseSeqConfig = XSPI_SetChipEraseSeqConfig,
        .getChipEraseSeqConfig = XSPI_GetChipEraseSeqConfig,
    };

    return &driver;
}
