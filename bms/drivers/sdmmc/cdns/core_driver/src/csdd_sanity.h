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

#ifndef CSDD_SANITY_H
#define CSDD_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "csdd_if.h"

uint32_t CSDD_CPhyConfigDfiRdSF(const CSDD_CPhyConfigDfiRd *obj);
uint32_t CSDD_CPhyConfigIoDelaySF(const CSDD_CPhyConfigIoDelay *obj);
uint32_t CSDD_CPhyConfigLvsiSF(const CSDD_CPhyConfigLvsi *obj);
uint32_t CSDD_CPhyConfigOutputDelaySF(const CSDD_CPhyConfigOutputDelay *obj);
uint32_t CSDD_CQDcmdRequestSF(const CSDD_CQDcmdRequest *obj);
uint32_t CSDD_CQInitConfigSF(const CSDD_CQInitConfig *obj);
uint32_t CSDD_CQIntCoalescingCfgSF(const CSDD_CQIntCoalescingCfg *obj);
uint32_t CSDD_CQRequestSF(const CSDD_CQRequest *obj);
uint32_t CSDD_CallbacksSF(const CSDD_Callbacks *obj);
uint32_t CSDD_ConfigSF(const CSDD_Config *obj);
uint32_t CSDD_PhyDelaySettingsSF(const CSDD_PhyDelaySettings *obj);
uint32_t CSDD_RequestSF(const CSDD_Request *obj);
uint32_t CSDD_SDIOHostSF(const CSDD_SDIO_Host *obj);
uint32_t CSDD_SDIOSlotSF(const CSDD_SDIO_Slot *obj);

uint32_t CSDD_SanityFunction1(const CSDD_SysReq* req);
uint32_t CSDD_SanityFunction2(const CSDD_SDIO_Host* pD, const CSDD_Config* config, const CSDD_Callbacks* callbacks);
uint32_t CSDD_SanityFunction3(const CSDD_SDIO_Host* pD);
uint32_t CSDD_SanityFunction5(const CSDD_SDIO_Host* pD, const CSDD_Request* request);
uint32_t CSDD_SanityFunction10(const CSDD_SDIO_Host* pD, const CSDD_ConfigCmd cmd, const void* data, const uint8_t* sizeOfData);
uint32_t CSDD_SanityFunction11(const CSDD_SDIO_Host* pD, const bool* handled);
uint32_t CSDD_SanityFunction15(const CSDD_SDIO_Host* pD, const CSDD_SpeedMode accessMode);
uint32_t CSDD_SanityFunction19(const CSDD_SDIO_Host* pD, const CSDD_DriverStrengthType driverStrength);
uint32_t CSDD_SanityFunction21(const CSDD_SDIO_Host* pD, const void* buffer, const CSDD_TransferDirection direction);
uint32_t CSDD_SanityFunction23(const CSDD_SDIO_Host* pD, const CSDD_MmcConfigCmd cmd, const uint8_t* data);
uint32_t CSDD_SanityFunction28(const CSDD_SDIO_Host* pD, const CSDD_TransferDirection direction);
uint32_t CSDD_SanityFunction29(const CSDD_SDIO_Host* pD, const void* buffer, const CSDD_TransferDirection direction, const void** request);
uint32_t CSDD_SanityFunction31(const CSDD_SDIO_Host* pD, const CSDD_PhyDelaySettings* phyDelaySet);
uint32_t CSDD_SanityFunction33(const CSDD_SDIO_Host* pD, const CSDD_PhyDelay phyDelayType);
uint32_t CSDD_SanityFunction34(const CSDD_SDIO_Host* pD, const CSDD_PhyDelay phyDelayType, const uint8_t* delayVal);
uint32_t CSDD_SanityFunction35(const CSDD_SDIO_Host* pD, const uint32_t* cardStatus);
uint32_t CSDD_SanityFunction39(const CSDD_SDIO_Host* pD, const CSDD_TransferDirection transferDirection, const void* data, const CSDD_CccrRegAddr registerAddress);
uint32_t CSDD_SanityFunction41(const CSDD_SDIO_Host* pD, const uint8_t* buffer);
uint32_t CSDD_SanityFunction42(const CSDD_SDIO_Host* pD, const CSDD_TupleCode tupleCode, const void* buffer);
uint32_t CSDD_SanityFunction45(const CSDD_SDIO_Host* pD, const CSDD_DriverCurrentLimit currentLimit);
uint32_t CSDD_SanityFunction48(const CSDD_SDIO_Host* pD, const CSDD_ParitionBoot partition);
uint32_t CSDD_SanityFunction49(const CSDD_SDIO_Host* pD, const CSDD_ParitionAccess partition);
uint32_t CSDD_SanityFunction51(const CSDD_SDIO_Host* pD, const void* buffer);
uint32_t CSDD_SanityFunction53(const CSDD_SDIO_Host* pD, const CSDD_InterfaceType* interfaceType);
uint32_t CSDD_SanityFunction54(const CSDD_SDIO_Host* pD, const CSDD_DeviceState* deviceState);
uint32_t CSDD_SanityFunction57(const CSDD_SDIO_Host* pD, const void** drvData);
uint32_t CSDD_SanityFunction60(const CSDD_SDIO_Host* pD, const uint16_t* rca);
uint32_t CSDD_SanityFunction61(const CSDD_SDIO_Host* pD, const CSDD_CQInitConfig* cqConfig);
uint32_t CSDD_SanityFunction63(const CSDD_SDIO_Host* pD, const CSDD_CQInitConfig* cqConfig);
uint32_t CSDD_SanityFunction66(const CSDD_SDIO_Host* pD, const CSDD_CQRequest* request);
uint32_t CSDD_SanityFunction67(const CSDD_SDIO_Host* pD, const CSDD_CQDcmdRequest* request);
uint32_t CSDD_SanityFunction70(const CSDD_SDIO_Host* pD, const CSDD_CQIntCoalescingCfg* config);
uint32_t CSDD_SanityFunction71(const CSDD_SDIO_Host* pD, const CSDD_CQIntCoalescingCfg* config);
uint32_t CSDD_SanityFunction82(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigIoDelay* ioDelay);
uint32_t CSDD_SanityFunction83(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigIoDelay* ioDelay);
uint32_t CSDD_SanityFunction84(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigLvsi* lvsi);
uint32_t CSDD_SanityFunction85(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigLvsi* lvsi);
uint32_t CSDD_SanityFunction86(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigDfiRd* dfiRd);
uint32_t CSDD_SanityFunction87(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigDfiRd* dfiRd);
uint32_t CSDD_SanityFunction88(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigOutputDelay* outputDelay);
uint32_t CSDD_SanityFunction89(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigOutputDelay* outputDelay);
uint32_t CSDD_SanityFunction92(const CSDD_SDIO_Host* pD, const bool* extendedWrMode, const bool* extendedRdMode);

#define	CSDD_ProbeSF CSDD_SanityFunction1
#define	CSDD_InitSF CSDD_SanityFunction2
#define	CSDD_StartSF CSDD_SanityFunction3
#define	CSDD_StopSF CSDD_SanityFunction3
#define	CSDD_ExecCardCommandSF CSDD_SanityFunction5
#define	CSDD_DeviceDetachSF CSDD_SanityFunction3
#define	CSDD_DeviceAttachSF CSDD_SanityFunction3
#define	CSDD_AbortSF CSDD_SanityFunction3
#define	CSDD_StandBySF CSDD_SanityFunction3
#define	CSDD_ConfigureSF CSDD_SanityFunction10
#define	CSDD_IsrSF CSDD_SanityFunction11
#define	CSDD_ConfigureHighSpeedSF CSDD_SanityFunction3
#define	CSDD_CheckSlotsSF CSDD_SanityFunction3
#define	CSDD_CheckInterruptSF CSDD_SanityFunction3
#define	CSDD_ConfigureAccessModeSF CSDD_SanityFunction15
#define	CSDD_TuningSF CSDD_SanityFunction3
#define	CSDD_ClockGeneratorSelectSF CSDD_SanityFunction3
#define	CSDD_PresetValueSwitchSF CSDD_SanityFunction3
#define	CSDD_ConfigureDriverStrengthSF CSDD_SanityFunction19
#define	CSDD_MemoryCardLoadDriverSF CSDD_SanityFunction3
#define	CSDD_MemoryCardDataTransferSF CSDD_SanityFunction21
#define	CSDD_MemoryCardDataTransfer2SF CSDD_SanityFunction21
#define	CSDD_MemoryCardConfigureSF CSDD_SanityFunction23
#define	CSDD_MemoryCardDataEraseSF CSDD_SanityFunction3
#define	CSDD_MemCardPartialDataXferSF CSDD_SanityFunction21
#define	CSDD_MemCardInfXferStartSF CSDD_SanityFunction21
#define	CSDD_MemCardInfXferContinueSF CSDD_SanityFunction21
#define	CSDD_MemCardInfXferFinishSF CSDD_SanityFunction28
#define	CSDD_MemCardDataXferNonBlockSF CSDD_SanityFunction29
#define	CSDD_MemCardFinishXferNonBloSF CSDD_SanityFunction5
#define	CSDD_PhySettingsSd3SF CSDD_SanityFunction31
#define	CSDD_PhySettingsSd4SF CSDD_SanityFunction31
#define	CSDD_WritePhySetSF CSDD_SanityFunction33
#define	CSDD_ReadPhySetSF CSDD_SanityFunction34
#define	CSDD_ReadCardStatusSF CSDD_SanityFunction35
#define	CSDD_SelectCardSF CSDD_SanityFunction3
#define	CSDD_ResetCardSF CSDD_SanityFunction3
#define	CSDD_ExecCmd55CommandSF CSDD_SanityFunction3
#define	CSDD_AccessCccrSF CSDD_SanityFunction39
#define	CSDD_ReadCsdSF CSDD_SanityFunction3
#define	CSDD_ReadExCsdSF CSDD_SanityFunction41
#define	CSDD_GetTupleFromCisSF CSDD_SanityFunction42
#define	CSDD_ReadSdStatusSF CSDD_SanityFunction3
#define	CSDD_SetDriverStrengthSF CSDD_SanityFunction19
#define	CSDD_ExecSetCurrentLimitSF CSDD_SanityFunction45
#define	CSDD_MmcSwitchSF CSDD_SanityFunction3
#define	CSDD_MmcSetExtCsdSF CSDD_SanityFunction3
#define	CSDD_MmcSetBootPartitionSF CSDD_SanityFunction48
#define	CSDD_MmcSetPartAccessSF CSDD_SanityFunction49
#define	CSDD_MmcSetBootAckSF CSDD_SanityFunction3
#define	CSDD_MmcExecuteBootSF CSDD_SanityFunction51
#define	CSDD_MmcGetParitionBootSizeSF CSDD_SanityFunction35
#define	CSDD_GetInterfaceTypeSF CSDD_SanityFunction53
#define	CSDD_GetDeviceStateSF CSDD_SanityFunction54
#define	CSDD_MemoryCardGetSecCountSF CSDD_SanityFunction35
#define	CSDD_SetDriverDataSF CSDD_SanityFunction51
#define	CSDD_GetDriverDataSF CSDD_SanityFunction57
#define	CSDD_SimpleInitSF CSDD_SanityFunction3
#define	CSDD_ResetHostSF CSDD_SanityFunction3
#define	CSDD_GetRcaSF CSDD_SanityFunction60
#define	CSDD_CQEnableSF CSDD_SanityFunction61
#define	CSDD_CQDisableSF CSDD_SanityFunction3
#define	CSDD_CQGetInitConfigSF CSDD_SanityFunction63
#define	CSDD_CQGetUnusedTaskIdSF CSDD_SanityFunction41
#define	CSDD_CQStartExecuteTaskSF CSDD_SanityFunction3
#define	CSDD_CQAttachRequestSF CSDD_SanityFunction66
#define	CSDD_CQExecuteDcmdRequestSF CSDD_SanityFunction67
#define	CSDD_CQGetDirectCmdConfigSF CSDD_SanityFunction41
#define	CSDD_CQSetDirectCmdConfigSF CSDD_SanityFunction3
#define	CSDD_CQSetIntCoalescingConfiSF CSDD_SanityFunction70
#define	CSDD_CQGetIntCoalescingConfiSF CSDD_SanityFunction71
#define	CSDD_CQGetIntCoalescingTimeoSF CSDD_SanityFunction35
#define	CSDD_CQStartExecuteTasksSF CSDD_SanityFunction3
#define	CSDD_CQHaltSF CSDD_SanityFunction3
#define	CSDD_CQTaskDiscardSF CSDD_SanityFunction3
#define	CSDD_CQAllTasksDiscardSF CSDD_SanityFunction3
#define	CSDD_CQResetIntCoalCountersSF CSDD_SanityFunction3
#define	CSDD_CQSetResponseErrorMaskSF CSDD_SanityFunction3
#define	CSDD_CQGetResponseErrorMaskSF CSDD_SanityFunction35
#define	CSDD_GetBaseClkSF CSDD_SanityFunction35
#define	CSDD_WaitForRequestSF CSDD_SanityFunction5
#define	CSDD_SetCPhyConfigIoDelaySF CSDD_SanityFunction82
#define	CSDD_GetCPhyConfigIoDelaySF CSDD_SanityFunction83
#define	CSDD_SetCPhyConfigLvsiSF CSDD_SanityFunction84
#define	CSDD_GetCPhyConfigLvsiSF CSDD_SanityFunction85
#define	CSDD_SetCPhyConfigDfiRdSF CSDD_SanityFunction86
#define	CSDD_GetCPhyConfigDfiRdSF CSDD_SanityFunction87
#define	CSDD_SetCPhyConfigOutputDelaSF CSDD_SanityFunction88
#define	CSDD_GetCPhyConfigOutputDelaSF CSDD_SanityFunction89
#define	CSDD_CPhyDllResetSF CSDD_SanityFunction3
#define	CSDD_SetCPhyExtModeSF CSDD_SanityFunction3
#define	CSDD_GetCPhyExtModeSF CSDD_SanityFunction92
#define	CSDD_SetCPhySdclkAdjSF CSDD_SanityFunction3
#define	CSDD_GetCPhySdclkAdjSF CSDD_SanityFunction41


#endif	/* CSDD_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
