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

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10, DRV-4789" */
/* parasoft-begin-suppress METRIC.CC-3 "Follow the Cyclomatic Complexity limit of 30, DRV-4417" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions, DRV-3823" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4, DRV-4790" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement, DRV-4926" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit, DRV-4139" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#ifndef XSPI_SANITY_H
#define XSPI_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "xspi_if.h"

uint32_t XSPI_ChipEraseSeqConfigSF(const XSPI_ChipEraseSeqConfig *obj);
uint32_t XSPI_CommStatSeqConfigSF(const XSPI_CommStatSeqConfig *obj);
uint32_t XSPI_ConfigSF(const XSPI_Config *obj);
uint32_t XSPI_CtrlFeaturesInfoSF(const XSPI_CtrlFeaturesInfo *obj);
uint32_t XSPI_DevDiscParamsP1SF(const XSPI_DevDiscParamsP1 *obj);
uint32_t XSPI_DeviceDiscoveryConfigSF(const XSPI_DeviceDiscoveryConfig *obj);
uint32_t XSPI_DeviceRelativeDelaysSF(const XSPI_DeviceRelativeDelays *obj);
uint32_t XSPI_DirectCmdSF(const XSPI_DirectCmd *obj);
uint32_t XSPI_DirectModeConfigSF(const XSPI_DirectModeConfig *obj);
uint32_t XSPI_DmaConfigSF(const XSPI_DmaConfig *obj);
uint32_t XSPI_EraseSecSeqConfigSF(const XSPI_EraseSecSeqConfig *obj);
uint32_t XSPI_GlobalCommandParametersSF(const XSPI_GlobalCommandParameters *obj);
uint32_t XSPI_HyperFlashOffsetConfigSF(const XSPI_HyperFlashOffsetConfig *obj);
uint32_t XSPI_JedecResetTimingConfigSF(const XSPI_JedecResetTimingConfig *obj);
uint32_t XSPI_PhyConfigSF(const XSPI_PhyConfig *obj);
uint32_t XSPI_PollingConfigSF(const XSPI_PollingConfig *obj);
uint32_t XSPI_PrivateDataSF(const XSPI_PrivateData *obj);
uint32_t XSPI_ProgramSeqP1ConfigSF(const XSPI_ProgramSeqP1Config *obj);
uint32_t XSPI_ProgramSeqP2ConfigSF(const XSPI_ProgramSeqP2Config *obj);
uint32_t XSPI_ReadSeqP1ConfigSF(const XSPI_ReadSeqP1Config *obj);
uint32_t XSPI_ReadSeqP2ConfigSF(const XSPI_ReadSeqP2Config *obj);
uint32_t XSPI_ResetDeviceConfigSF(const XSPI_ResetDeviceConfig *obj);
uint32_t XSPI_ResetSeqConfigSF(const XSPI_ResetSeqConfig *obj);
uint32_t XSPI_SeqAddressPhaseSF(const XSPI_SeqAddressPhase *obj);
uint32_t XSPI_SeqCommandPhaseSF(const XSPI_SeqCommandPhase *obj);
uint32_t XSPI_SeqDataPhaseSF(const XSPI_SeqDataPhase *obj);
uint32_t XSPI_SpiNandGlobCmdParamsSF(const XSPI_SpiNandGlobCmdParams *obj);
uint32_t XSPI_StatSeqP1ConfigSF(const XSPI_StatSeqP1Config *obj);
uint32_t XSPI_StatSeqP2ConfigSF(const XSPI_StatSeqP2Config *obj);
uint32_t XSPI_StatSeqSpiNandConfigSF(const XSPI_StatSeqSpiNandConfig *obj);
uint32_t XSPI_WelSeqConfigSF(const XSPI_WelSeqConfig *obj);
uint32_t XSPI_XipModeBitsConfigSF(const XSPI_XipModeBitsConfig *obj);

uint32_t XSPI_SanityFunction1(const XSPI_Config* config, const XSPI_SysReq* sysReq);
uint32_t XSPI_SanityFunction2(const XSPI_PrivateData* privateData, const XSPI_Config* config);
uint32_t XSPI_SanityFunction3(const XSPI_PrivateData* privateData);
uint32_t XSPI_SanityFunction7(const XSPI_PrivateData* privateData, const XSPI_WorkMode workMode);
uint32_t XSPI_SanityFunction8(const XSPI_PrivateData* privateData, const XSPI_WorkMode* workMode);
uint32_t XSPI_SanityFunction10(const XSPI_PrivateData* privateData, const uint32_t* events);
uint32_t XSPI_SanityFunction12(const XSPI_PrivateData* privateData, const XSPI_Callbacks* callbacks);
uint32_t XSPI_SanityFunction14(const XSPI_PrivateData* privateData, const bool* writeProtectEnabled);
uint32_t XSPI_SanityFunction15(const XSPI_PrivateData* privateData, const XSPI_DmaConfig* dmaConfig);
uint32_t XSPI_SanityFunction16(const XSPI_PrivateData* privateData, const XSPI_DmaConfig* dmaConfig);
uint32_t XSPI_SanityFunction17(const XSPI_PrivateData* privateData, const XSPI_SpiClockMode spiClockMode);
uint32_t XSPI_SanityFunction18(const XSPI_PrivateData* privateData, const XSPI_SpiClockMode* spiClockMode);
uint32_t XSPI_SanityFunction19(const XSPI_PrivateData* privateData, const XSPI_ResetDeviceConfig* resetBankCfg);
uint32_t XSPI_SanityFunction23(const XSPI_PrivateData* privateData, const XSPI_DeviceRelativeDelays* deviceRelativeDelays);
uint32_t XSPI_SanityFunction24(const XSPI_PrivateData* privateData, const XSPI_DeviceRelativeDelays* deviceRelativeDelays);
uint32_t XSPI_SanityFunction25(const XSPI_PrivateData* privateData, const XSPI_GlobalCommandParameters* globalCmdParameters);
uint32_t XSPI_SanityFunction26(const XSPI_PrivateData* privateData, const XSPI_GlobalCommandParameters* globalCmdParameters);
uint32_t XSPI_SanityFunction27(const XSPI_PrivateData* privateData, const XSPI_SpiNandGlobCmdParams* spiNandCmdParams);
uint32_t XSPI_SanityFunction28(const XSPI_PrivateData* privateData, const XSPI_SpiNandGlobCmdParams* spiNandCmdParams);
uint32_t XSPI_SanityFunction29(const XSPI_PrivateData* privateData, const XSPI_XipModeBitsConfig* xipModeBitsConfig);
uint32_t XSPI_SanityFunction30(const XSPI_PrivateData* privateData, const XSPI_XipModeBitsConfig* xipModeBitsConfig);
uint32_t XSPI_SanityFunction31(const XSPI_PrivateData* privateData, const XSPI_DirectCmd* directCmd);
uint32_t XSPI_SanityFunction33(const XSPI_PrivateData* privateData, const XSPI_DirectModeConfig* directModeConfig);
uint32_t XSPI_SanityFunction34(const XSPI_PrivateData* privateData, const XSPI_DirectModeConfig* directModeConfig);
uint32_t XSPI_SanityFunction37(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP1Config* progSeqP1Cfg);
uint32_t XSPI_SanityFunction38(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP1Config* progSeqP1Cfg);
uint32_t XSPI_SanityFunction39(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP2Config* progSeqP2Cfg);
uint32_t XSPI_SanityFunction40(const XSPI_PrivateData* privateData, const XSPI_ProgramSeqP2Config* progSeqP2Cfg);
uint32_t XSPI_SanityFunction41(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP1Config* readSeqP1Cfg);
uint32_t XSPI_SanityFunction42(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP1Config* readSeqP1Cfg);
uint32_t XSPI_SanityFunction43(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP2Config* readSeqP2Cfg);
uint32_t XSPI_SanityFunction44(const XSPI_PrivateData* privateData, const XSPI_ReadSeqP2Config* readSeqP2Cfg);
uint32_t XSPI_SanityFunction45(const XSPI_PrivateData* privateData, const XSPI_WelSeqConfig* welSeqCfg);
uint32_t XSPI_SanityFunction46(const XSPI_PrivateData* privateData, const XSPI_WelSeqConfig* welSeqCfg);
uint32_t XSPI_SanityFunction47(const XSPI_PrivateData* privateData, const XSPI_CommStatSeqConfig* commStatSeqConfig);
uint32_t XSPI_SanityFunction48(const XSPI_PrivateData* privateData, const XSPI_CommStatSeqConfig* commStatSeqConfig);
uint32_t XSPI_SanityFunction49(const XSPI_PrivateData* privateData, const XSPI_StatSeqP1Config* statSeqP1Cfg);
uint32_t XSPI_SanityFunction50(const XSPI_PrivateData* privateData, const XSPI_StatSeqP1Config* statSeqP1Cfg);
uint32_t XSPI_SanityFunction51(const XSPI_PrivateData* privateData, const XSPI_StatSeqP2Config* statSeqP2Cfg);
uint32_t XSPI_SanityFunction52(const XSPI_PrivateData* privateData, const XSPI_StatSeqP2Config* statSeqP2Cfg);
uint32_t XSPI_SanityFunction53(const XSPI_PrivateData* privateData, const XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg);
uint32_t XSPI_SanityFunction54(const XSPI_PrivateData* privateData, const XSPI_StatSeqSpiNandConfig* statSeqSpiNandCfg);
uint32_t XSPI_SanityFunction55(const XSPI_PrivateData* privateData, const XSPI_StigCommand* stigCommand);
uint32_t XSPI_SanityFunction56(const XSPI_PrivateData* privateData, const XSPI_StigCommand* stigCommand);
uint32_t XSPI_SanityFunction57(const XSPI_PrivateData* privateData, const XSPI_JedecResetTimingConfig* jedecRstTiming);
uint32_t XSPI_SanityFunction58(const XSPI_PrivateData* privateData, const XSPI_JedecResetTimingConfig* jedecRstTiming);
uint32_t XSPI_SanityFunction62(const XSPI_PrivateData* privateData, const XSPI_LatestBootStatus* bootStatus);
uint32_t XSPI_SanityFunction63(const XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig);
uint32_t XSPI_SanityFunction64(const XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryConfig* deviceDiscoveryConfig);
uint32_t XSPI_SanityFunction66(const XSPI_PrivateData* privateData, const XSPI_DeviceDiscoveryStatus* deviceDiscoveryStatus);
uint32_t XSPI_SanityFunction69(const XSPI_PrivateData* privateData, const XSPI_PollingConfig* pollingConfig);
uint32_t XSPI_SanityFunction70(const XSPI_PrivateData* privateData, const XSPI_PollingConfig* pollingConfig);
uint32_t XSPI_SanityFunction71(const XSPI_PrivateData* privateData, const XSPI_HyperFlashOffsetConfig* hfOffsetCfg);
uint32_t XSPI_SanityFunction72(const XSPI_PrivateData* privateData, const XSPI_HyperFlashOffsetConfig* hfOffsetCfg);
uint32_t XSPI_SanityFunction73(const XSPI_PrivateData* privateData, const XSPI_PhyConfig* phyConfig);
uint32_t XSPI_SanityFunction74(const XSPI_PrivateData* privateData, const XSPI_PhyConfig* phyConfig);
uint32_t XSPI_SanityFunction75(const XSPI_PrivateData* privateData, const uint8_t dllReset);
uint32_t XSPI_SanityFunction76(const XSPI_PrivateData* privateData, const XSPI_CdmaCommand* cdmaCmd);
uint32_t XSPI_SanityFunction78(const XSPI_PrivateData* privateData, const XSPI_CdmaCommandChain* cdmaCmdChain);
uint32_t XSPI_SanityFunction80(const XSPI_PrivateData* privateData, const XSPI_PioCommand* pioCmd);
uint32_t XSPI_SanityFunction82(const XSPI_PrivateData* privateData, const XSPI_CommandStatusInfo* cmdStatus);
uint32_t XSPI_SanityFunction83(const XSPI_PrivateData* privateData, const XSPI_ResetSeqConfig* resetSeqCfg);
uint32_t XSPI_SanityFunction84(const XSPI_PrivateData* privateData, const XSPI_ResetSeqConfig* resetSeqCfg);
uint32_t XSPI_SanityFunction85(const XSPI_PrivateData* privateData, const XSPI_EraseSecSeqConfig* eraseSecSeqCfg);
uint32_t XSPI_SanityFunction86(const XSPI_PrivateData* privateData, const XSPI_EraseSecSeqConfig* eraseSecSeqCfg);
uint32_t XSPI_SanityFunction87(const XSPI_PrivateData* privateData, const XSPI_ChipEraseSeqConfig* chipEraseSeqCfg);
uint32_t XSPI_SanityFunction88(const XSPI_PrivateData* privateData, const XSPI_ChipEraseSeqConfig* chipEraseSeqCfg);

#define	XSPI_ProbeSF XSPI_SanityFunction1
#define	XSPI_InitSF XSPI_SanityFunction2
#define	XSPI_DestroySF XSPI_SanityFunction3
#define	XSPI_StartSF XSPI_SanityFunction3
#define	XSPI_StopSF XSPI_SanityFunction3
#define	XSPI_IsrSF XSPI_SanityFunction3
#define	XSPI_SetWorkModeSF XSPI_SanityFunction7
#define	XSPI_GetWorkModeSF XSPI_SanityFunction8
#define	XSPI_SetEventEnableSF XSPI_SanityFunction3
#define	XSPI_GetEventEnableSF XSPI_SanityFunction10
#define	XSPI_SetCallbacksSF XSPI_SanityFunction3
#define	XSPI_GetCallbacksSF XSPI_SanityFunction12
#define	XSPI_SetWriteProtectSF XSPI_SanityFunction3
#define	XSPI_GetWriteProtectSF XSPI_SanityFunction14
#define	XSPI_SetDmaConfigSF XSPI_SanityFunction15
#define	XSPI_GetDmaConfigSF XSPI_SanityFunction16
#define	XSPI_SetSpiClockModeSF XSPI_SanityFunction17
#define	XSPI_GetSpiClockModeSF XSPI_SanityFunction18
#define	XSPI_GetResetConfigSF XSPI_SanityFunction19
#define	XSPI_SetResetConfigSF XSPI_SanityFunction19
#define	XSPI_AssertResetSF XSPI_SanityFunction3
#define	XSPI_DeAssertResetSF XSPI_SanityFunction3
#define	XSPI_SetDeviceRelativeDelaysSF XSPI_SanityFunction23
#define	XSPI_GetDeviceRelativeDelaysSF XSPI_SanityFunction24
#define	XSPI_SetGlobalCmdParametersSF XSPI_SanityFunction25
#define	XSPI_GetGlobalCmdParametersSF XSPI_SanityFunction26
#define	XSPI_SetSpiNandCmdParametersSF XSPI_SanityFunction27
#define	XSPI_GetSpiNandCmdParametersSF XSPI_SanityFunction28
#define	XSPI_SetXipModeBitsConfigSF XSPI_SanityFunction29
#define	XSPI_GetXipModeBitsConfigSF XSPI_SanityFunction30
#define	XSPI_SendDirectCommandSF XSPI_SanityFunction31
#define	XSPI_IsDirectCmdEngBusySF XSPI_SanityFunction3
#define	XSPI_SetDirectModeConfigSF XSPI_SanityFunction33
#define	XSPI_GetDirectModeConfigSF XSPI_SanityFunction34
#define	XSPI_SetP2ActiveDevMaxCyclesSF XSPI_SanityFunction3
#define	XSPI_GetP2ActiveDevMaxCyclesSF XSPI_SanityFunction10
#define	XSPI_SetProgramSeqP1ConfigSF XSPI_SanityFunction37
#define	XSPI_GetProgramSeqP1ConfigSF XSPI_SanityFunction38
#define	XSPI_SetProgramSeqP2ConfigSF XSPI_SanityFunction39
#define	XSPI_GetProgramSeqP2ConfigSF XSPI_SanityFunction40
#define	XSPI_SetReadSeqP1ConfigSF XSPI_SanityFunction41
#define	XSPI_GetReadSeqP1ConfigSF XSPI_SanityFunction42
#define	XSPI_SetReadSeqP2ConfigSF XSPI_SanityFunction43
#define	XSPI_GetReadSeqP2ConfigSF XSPI_SanityFunction44
#define	XSPI_SetWelSeqConfigSF XSPI_SanityFunction45
#define	XSPI_GetWelSeqConfigSF XSPI_SanityFunction46
#define	XSPI_SetCommStatSeqConfigSF XSPI_SanityFunction47
#define	XSPI_GetCommStatSeqConfigSF XSPI_SanityFunction48
#define	XSPI_SetStatSeqP1ConfigSF XSPI_SanityFunction49
#define	XSPI_GetStatSeqP1ConfigSF XSPI_SanityFunction50
#define	XSPI_SetStatSeqP2ConfigSF XSPI_SanityFunction51
#define	XSPI_GetStatSeqP2ConfigSF XSPI_SanityFunction52
#define	XSPI_SetStatSeqSpiNandConfigSF XSPI_SanityFunction53
#define	XSPI_GetStatSeqSpiNandConfigSF XSPI_SanityFunction54
#define	XSPI_SendStigCommandSF XSPI_SanityFunction55
#define	XSPI_GetStigStatusSF XSPI_SanityFunction56
#define	XSPI_SetJedecResetTimingConfSF XSPI_SanityFunction57
#define	XSPI_GetJedecResetTimingConfSF XSPI_SanityFunction58
#define	XSPI_SendStigJedecResetSF XSPI_SanityFunction3
#define	XSPI_SetContinueProcOnDescErSF XSPI_SanityFunction3
#define	XSPI_GetContinueProcOnDescErSF XSPI_SanityFunction14
#define	XSPI_GetLatestBootStatusSF XSPI_SanityFunction62
#define	XSPI_SetDeviceDiscoveryConfiSF XSPI_SanityFunction63
#define	XSPI_GetDeviceDiscoveryConfiSF XSPI_SanityFunction64
#define	XSPI_RunDeviceDiscoverySF XSPI_SanityFunction3
#define	XSPI_GetDeviceDiscoveryStatuSF XSPI_SanityFunction66
#define	XSPI_SetResetRecoveryDelaySF XSPI_SanityFunction3
#define	XSPI_GetResetRecoveryDelaySF XSPI_SanityFunction10
#define	XSPI_SetPollingConfigSF XSPI_SanityFunction69
#define	XSPI_GetPollingConfigSF XSPI_SanityFunction70
#define	XSPI_SetHyperFlashOffsetConfSF XSPI_SanityFunction71
#define	XSPI_GetHyperFlashOffsetConfSF XSPI_SanityFunction72
#define	XSPI_SetPhyConfigSF XSPI_SanityFunction73
#define	XSPI_GetPhyConfigSF XSPI_SanityFunction74
#define	XSPI_PhyWriteDllResetSF XSPI_SanityFunction75
#define	XSPI_SendCdmaCommandSF XSPI_SanityFunction76
#define	XSPI_GetCdmaCommandStatusSF XSPI_SanityFunction76
#define	XSPI_SendCdmaCommandChainSF XSPI_SanityFunction78
#define	XSPI_GetCdmaChainStatusSF XSPI_SanityFunction78
#define	XSPI_SendPioCommandSF XSPI_SanityFunction80
#define	XSPI_GetPioCommandStatusSF XSPI_SanityFunction80
#define	XSPI_GetAcmdLastCmdStatusSF XSPI_SanityFunction82
#define	XSPI_SetResetSeqConfigSF XSPI_SanityFunction83
#define	XSPI_GetResetSeqConfigSF XSPI_SanityFunction84
#define	XSPI_SetEraseSecConfigSF XSPI_SanityFunction85
#define	XSPI_GetEraseSecConfigSF XSPI_SanityFunction86
#define	XSPI_SetChipEraseSeqConfigSF XSPI_SanityFunction87
#define	XSPI_GetChipEraseSeqConfigSF XSPI_SanityFunction88


#endif	/* XSPI_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
