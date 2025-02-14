/**********************************************************************
 * Copyright (C) 2014-2023 Cadence Design Systems, Inc.
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
 * Cadence Core Driver for the Cadence Ethernet MAC (EMAC) core. This
 * header file lists the API providing a HAL (hardware abstraction
 * layer) interface for the EMAC core, GEM_GXL  part no. IP7014
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

#ifndef CEDI_SANITY_H
#define CEDI_SANITY_H

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "cedi_if.h"

uint32_t CEDI_1588TimerValSF(const CEDI_1588TimerVal *obj);
uint32_t CEDI_AnAdvPageSF(const CEDI_AnAdvPage *obj);
uint32_t CEDI_AnNextPageSF(const CEDI_AnNextPage *obj);
uint32_t CEDI_AxiBuffCfgSF(const CEDI_AxiBuffCfg *obj);
uint32_t CEDI_AxiHostArbitrationCfgSF(const CEDI_AxiHostArbitrationCfg *obj);
uint32_t CEDI_AxiQosConfigSF(const CEDI_AxiQosConfig *obj);
uint32_t CEDI_BuffAddrSF(const CEDI_BuffAddr *obj);
uint32_t CEDI_CallbacksSF(const CEDI_Callbacks *obj);
uint32_t CEDI_ConfigSF(const CEDI_Config *obj);
uint32_t CEDI_EnstTimeConfigSF(const CEDI_EnstTimeConfig *obj);
uint32_t CEDI_FrameEliminationConfigSF(const CEDI_FrameEliminationConfig *obj);
uint32_t CEDI_FrameEliminationTagConfSF(const CEDI_FrameEliminationTagConfig *obj);
uint32_t CEDI_LockupConfigSF(const CEDI_LockupConfig *obj);
uint32_t CEDI_MacAddressSF(const CEDI_MacAddress *obj);
uint32_t CEDI_Pcs25gCfgSF(const CEDI_Pcs25gCfg *obj);
uint32_t CEDI_PreemptionConfigSF(const CEDI_PreemptionConfig *obj);
uint32_t CEDI_PrivateDataSF(const CEDI_PrivateData *obj);
uint32_t CEDI_QTxBufParamsSF(const CEDI_qTxBufParams *obj);
uint32_t CEDI_QueueSegAllocSF(const CEDI_QueueSegAlloc *obj);
uint32_t CEDI_RxQFlushConfigSF(const CEDI_RxQFlushConfig *obj);
uint32_t CEDI_T1ScreenSF(const CEDI_T1Screen *obj);
uint32_t CEDI_T2CompareSF(const CEDI_T2Compare *obj);
uint32_t CEDI_T2ScreenSF(const CEDI_T2Screen *obj);
uint32_t CEDI_TestPatternSeedSF(const CEDI_TestPatternSeed *obj);
uint32_t CEDI_TimerIncrementSF(const CEDI_TimerIncrement *obj);
uint32_t CEDI_TsuTimerValSF(const CEDI_TsuTimerVal *obj);
uint32_t CEDI_Type2ScreenerRateLimitSF(const CEDI_Type2ScreenerRateLimit *obj);
uint32_t CEDI_WakeOnLanRegSF(const CEDI_WakeOnLanReg *obj);
uint32_t CEDI_WatermarkLvlSF(const CEDI_WatermarkLvl *obj);

uint32_t CEDI_SanityFunction1(const CEDI_Config* config, const CEDI_SysReq* memReq);
uint32_t CEDI_SanityFunction2(const CEDI_PrivateData* pD, const CEDI_Config* config, const CEDI_Callbacks* callbacks);
uint32_t CEDI_SanityFunction3(const CEDI_PrivateData* pD);
uint32_t CEDI_SanityFunction7(const CEDI_PrivateData* pD, const uint8_t enable);
uint32_t CEDI_SanityFunction8(const CEDI_PrivateData* pD, const uint32_t* event);
uint32_t CEDI_SanityFunction9(const CEDI_PrivateData* pD, const uint8_t txIntDelay, const uint8_t rxIntDelay);
uint32_t CEDI_SanityFunction10(const CEDI_PrivateData* pD, const uint8_t* txIntDelay, const uint8_t* rxIntDelay);
uint32_t CEDI_SanityFunction13(const CEDI_PrivateData* pD, const CEDI_IfSpeed speedSel);
uint32_t CEDI_SanityFunction14(const CEDI_PrivateData* pD, const CEDI_IfSpeed* speedSel);
uint32_t CEDI_SanityFunction16(const CEDI_PrivateData* pD, const uint8_t* enable);
uint32_t CEDI_SanityFunction17(const CEDI_PrivateData* pD, const uint16_t length);
uint32_t CEDI_SanityFunction18(const CEDI_PrivateData* pD, const uint16_t* length);
uint32_t CEDI_SanityFunction23(const CEDI_PrivateData* pD, const uint8_t offset);
uint32_t CEDI_SanityFunction25(const CEDI_PrivateData* pD, const uint8_t bufferSizeMultiple64Bytes);
uint32_t CEDI_SanityFunction27(const CEDI_PrivateData* pD, const CEDI_BurstLen burstLength);
uint32_t CEDI_SanityFunction28(const CEDI_PrivateData* pD, const CEDI_BurstLen burstLenth);
uint32_t CEDI_SanityFunction38(const CEDI_PrivateData* pD, const uint32_t* watermark, const uint8_t* enable);
uint32_t CEDI_SanityFunction41(const CEDI_PrivateData* pD, const uint8_t enableBit, const uint8_t bitValues);
uint32_t CEDI_SanityFunction51(const CEDI_PrivateData* pD, const CEDI_PreCrcCover txCrcPreCover, const CEDI_PreCrcCover rxCrcPreCover);
uint32_t CEDI_SanityFunction52(const CEDI_PrivateData* pD, const CEDI_PreCrcCover* txCrcPreCover, const CEDI_PreCrcCover* rxCrcPreCover);
uint32_t CEDI_SanityFunction53(const CEDI_PrivateData* pD, const uint32_t* cap);
uint32_t CEDI_SanityFunction54(const CEDI_PrivateData* pD, const uint8_t mode);
uint32_t CEDI_SanityFunction56(const CEDI_PrivateData* pD, const CEDI_FrameSize* maxTxSize);
uint32_t CEDI_SanityFunction57(const CEDI_PrivateData* pD, const CEDI_BuffAddr* bufAdd, const uint32_t length);
uint32_t CEDI_SanityFunction58(const CEDI_PrivateData* pD, const CEDI_qTxBufParams* params);
uint32_t CEDI_SanityFunction59(const CEDI_PrivateData* pD, const CEDI_qTxBufParams* params);
uint32_t CEDI_SanityFunction61(const CEDI_PrivateData* pD, const CEDI_TxDescData* descData);
uint32_t CEDI_SanityFunction62(const CEDI_PrivateData* pD, const CEDI_TxDescStat* txDStat);
uint32_t CEDI_SanityFunction74(const CEDI_PrivateData* pD, const CEDI_TxStatus* txStatus);
uint32_t CEDI_SanityFunction75(const CEDI_PrivateData* pD, const CEDI_TxQStatus* txQstatus);
uint32_t CEDI_SanityFunction76(const CEDI_PrivateData* pD, const uint32_t resetStatus);
uint32_t CEDI_SanityFunction77(const CEDI_PrivateData* pD, const uint32_t resetStatus);
uint32_t CEDI_SanityFunction80(const CEDI_PrivateData* pD, const uint8_t qSel, const uint8_t* enable, const uint32_t* idleSlope);
uint32_t CEDI_SanityFunction81(const CEDI_PrivateData* pD, const uint8_t enable, const uint8_t multiplier, const uint8_t divisor);
uint32_t CEDI_SanityFunction82(const CEDI_PrivateData* pD, const uint8_t* enable, const uint8_t* multiplier, const uint8_t* divisor);
uint32_t CEDI_SanityFunction83(const CEDI_PrivateData* pD, const CEDI_MinIpg minIpg);
uint32_t CEDI_SanityFunction85(const CEDI_PrivateData* pD, const bool* enable);
uint32_t CEDI_SanityFunction87(const CEDI_PrivateData* pD, const CEDI_BuffAddr* buf, const uint8_t init);
uint32_t CEDI_SanityFunction90(const CEDI_PrivateData* pD, const CEDI_BuffAddr* buf, const uint8_t init, const CEDI_RxDescData* descData);
uint32_t CEDI_SanityFunction91(const CEDI_PrivateData* pD, const CEDI_RxDescStat* rxDStat);
uint32_t CEDI_SanityFunction97(const CEDI_PrivateData* pD, const CEDI_BuffAddr* buf);
uint32_t CEDI_SanityFunction99(const CEDI_PrivateData* pD, const CEDI_RxStatus* status);
uint32_t CEDI_SanityFunction100(const CEDI_PrivateData* pD, const CEDI_RxQStatus* rxQstatus);
uint32_t CEDI_SanityFunction101(const CEDI_PrivateData* pD, const uint32_t resetStatus);
uint32_t CEDI_SanityFunction102(const CEDI_PrivateData* pD, const uint32_t resetStatus);
uint32_t CEDI_SanityFunction110(const CEDI_PrivateData* pD, const CEDI_MacAddress* addr, const uint8_t specFilterType, const uint8_t byteMask);
uint32_t CEDI_SanityFunction111(const CEDI_PrivateData* pD, const CEDI_MacAddress* addr, const uint8_t* specFilterType, const uint8_t* byteMask);
uint32_t CEDI_SanityFunction112(const CEDI_PrivateData* pD, const CEDI_MacAddress* mask);
uint32_t CEDI_SanityFunction113(const CEDI_PrivateData* pD, const CEDI_MacAddress* mask);
uint32_t CEDI_SanityFunction115(const CEDI_PrivateData* pD, const uint8_t matchSel, const uint16_t typeId, const uint8_t enable);
uint32_t CEDI_SanityFunction116(const CEDI_PrivateData* pD, const uint8_t matchSel, const uint16_t* typeId, const uint8_t* enable);
uint32_t CEDI_SanityFunction127(const CEDI_PrivateData* pD, const uint8_t enable, const uint16_t vlanType);
uint32_t CEDI_SanityFunction128(const CEDI_PrivateData* pD, const uint8_t* enable, const uint16_t* vlanType);
uint32_t CEDI_SanityFunction131(const CEDI_PrivateData* pD, const uint32_t hAddrTop, const uint32_t hAddrBot);
uint32_t CEDI_SanityFunction132(const CEDI_PrivateData* pD, const uint32_t* hAddrTop, const uint32_t* hAddrBot);
uint32_t CEDI_SanityFunction135(const CEDI_PrivateData* pD, const CEDI_NumScreeners* regNums);
uint32_t CEDI_SanityFunction136(const CEDI_PrivateData* pD, const CEDI_T1Screen* regVals);
uint32_t CEDI_SanityFunction137(const CEDI_PrivateData* pD, const CEDI_T1Screen* regVals);
uint32_t CEDI_SanityFunction138(const CEDI_PrivateData* pD, const CEDI_T2Screen* regVals);
uint32_t CEDI_SanityFunction139(const CEDI_PrivateData* pD, const CEDI_T2Screen* regVals);
uint32_t CEDI_SanityFunction140(const CEDI_PrivateData* pD, const uint16_t eTypeVal);
uint32_t CEDI_SanityFunction141(const CEDI_PrivateData* pD, const uint16_t* eTypeVal);
uint32_t CEDI_SanityFunction142(const CEDI_PrivateData* pD, const CEDI_T2Compare* regVals);
uint32_t CEDI_SanityFunction143(const CEDI_PrivateData* pD, const CEDI_T2Compare* regVals);
uint32_t CEDI_SanityFunction149(const CEDI_PrivateData* pD, const uint16_t value, const uint8_t qpriority);
uint32_t CEDI_SanityFunction150(const CEDI_PrivateData* pD, const uint16_t* value, const uint8_t qpriority);
uint32_t CEDI_SanityFunction162(const CEDI_PrivateData* pD, const uint32_t rxAddr);
uint32_t CEDI_SanityFunction166(const CEDI_PrivateData* pD, const CEDI_1588TimerVal* timeVal);
uint32_t CEDI_SanityFunction167(const CEDI_PrivateData* pD, const CEDI_1588TimerVal* timeVal);
uint32_t CEDI_SanityFunction168(const CEDI_PrivateData* pD, const int32_t nSecAdjust);
uint32_t CEDI_SanityFunction169(const CEDI_PrivateData* pD, const CEDI_TimerIncrement* incSettings);
uint32_t CEDI_SanityFunction170(const CEDI_PrivateData* pD, const CEDI_TimerIncrement* incSettings);
uint32_t CEDI_SanityFunction171(const CEDI_PrivateData* pD, const CEDI_TsuTimerVal* timeVal);
uint32_t CEDI_SanityFunction172(const CEDI_PrivateData* pD, const CEDI_TsuTimerVal* timeVal);
uint32_t CEDI_SanityFunction182(const CEDI_PrivateData* pD, const CEDI_TxTsMode txMode, const CEDI_RxTsMode rxMode);
uint32_t CEDI_SanityFunction183(const CEDI_PrivateData* pD, const CEDI_TxTsMode* txMode, const CEDI_RxTsMode* rxMode);
uint32_t CEDI_SanityFunction188(const CEDI_PrivateData* pD, const CEDI_AnAdvPage* advDat);
uint32_t CEDI_SanityFunction195(const CEDI_PrivateData* pD, const CEDI_AnAdvPage* advDat);
uint32_t CEDI_SanityFunction196(const CEDI_PrivateData* pD, const CEDI_LpAbilityPage* lpAbl);
uint32_t CEDI_SanityFunction198(const CEDI_PrivateData* pD, const CEDI_AnNextPage* npDat);
uint32_t CEDI_SanityFunction199(const CEDI_PrivateData* pD, const CEDI_AnNextPage* npDat);
uint32_t CEDI_SanityFunction200(const CEDI_PrivateData* pD, const CEDI_LpNextPage* npDat);
uint32_t CEDI_SanityFunction204(const CEDI_PrivateData* pD, const uint8_t flags, const uint8_t phyAddr, const uint8_t devReg);
uint32_t CEDI_SanityFunction213(const CEDI_PrivateData* pD, const CEDI_WakeOnLanReg* regVals);
uint32_t CEDI_SanityFunction214(const CEDI_PrivateData* pD, const CEDI_WakeOnLanReg* regVals);
uint32_t CEDI_SanityFunction217(const CEDI_PrivateData* pD, const CEDI_LpiStats* lpiStats);
uint32_t CEDI_SanityFunction218(const CEDI_PrivateData* pD, const CEDI_DesignCfg* hwCfg);
uint32_t CEDI_SanityFunction234(const CEDI_PrivateData* pD, const uint32_t offs, const uint32_t* data);
uint32_t CEDI_SanityFunction235(const CEDI_PrivateData* pD, const uint32_t offs);
uint32_t CEDI_SanityFunction236(const CEDI_PrivateData* pD, const uint8_t numQueues);
uint32_t CEDI_SanityFunction238(const CEDI_PrivateData* pD, const uint8_t numQueues);
uint32_t CEDI_SanityFunction240(const CEDI_PrivateData* pD, const CEDI_QueueSegAlloc* queueSegAlloc);
uint32_t CEDI_SanityFunction241(const CEDI_PrivateData* pD, const CEDI_TxSchedType schedType);
uint32_t CEDI_SanityFunction242(const CEDI_PrivateData* pD, const CEDI_TxSchedType* schedType);
uint32_t CEDI_SanityFunction249(const CEDI_PrivateData* pD, const CEDI_EnstTimeConfig* enstTimeConfig);
uint32_t CEDI_SanityFunction250(const CEDI_PrivateData* pD, const CEDI_EnstTimeConfig* enstTimeConfig);
uint32_t CEDI_SanityFunction252(const CEDI_PrivateData* pD, const uint8_t* enable);
uint32_t CEDI_SanityFunction262(const CEDI_PrivateData* pD, const CEDI_LinkFaultIndication* linkFault);
uint32_t CEDI_SanityFunction263(const CEDI_PrivateData* pD, const CEDI_RedundancyTagSize tagSize);
uint32_t CEDI_SanityFunction264(const CEDI_PrivateData* pD, const CEDI_RedundancyTagSize* tagSize);
uint32_t CEDI_SanityFunction265(const CEDI_PrivateData* pD, const uint8_t queueNum, const uint8_t enable);
uint32_t CEDI_SanityFunction266(const CEDI_PrivateData* pD, const uint8_t queueNum, const uint8_t* enable);
uint32_t CEDI_SanityFunction269(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_FrameEliminationConfig* fec);
uint32_t CEDI_SanityFunction270(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_FrameEliminationConfig* fec);
uint32_t CEDI_SanityFunction271(const CEDI_PrivateData* pD, const CEDI_FrameEliminationTagConfig* fetc);
uint32_t CEDI_SanityFunction272(const CEDI_PrivateData* pD, const CEDI_FrameEliminationTagConfig* fetc);
uint32_t CEDI_SanityFunction274(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_FrameEliminationStats* stats);
uint32_t CEDI_SanityFunction275(const CEDI_PrivateData* pD, const CEDI_PrivateData** emacPrivateData);
uint32_t CEDI_SanityFunction277(const CEDI_PrivateData* pD, const CEDI_MacType* macType);
uint32_t CEDI_SanityFunction278(const CEDI_PrivateData* pD, const CEDI_PreemptionConfig* preCfg);
uint32_t CEDI_SanityFunction279(const CEDI_PrivateData* pD, const CEDI_PreemptionConfig* preCfg);
uint32_t CEDI_SanityFunction283(const CEDI_PrivateData* pD, const CEDI_MmslStats* mmslStats);
uint32_t CEDI_SanityFunction284(const CEDI_PrivateData* pD, const CEDI_MmslStatus* mmslStatus);
uint32_t CEDI_SanityFunction285(const CEDI_PrivateData* pD, const CEDI_LockupConfig* lockupCfg);
uint32_t CEDI_SanityFunction286(const CEDI_PrivateData* pD, const CEDI_LockupConfig* lockupCfg);
uint32_t CEDI_SanityFunction291(const CEDI_PrivateData* pD, const CEDI_RxQFlushConfig* rxQFlushConfig);
uint32_t CEDI_SanityFunction292(const CEDI_PrivateData* pD, const CEDI_RxQFlushConfig* rxQFlushConfig);
uint32_t CEDI_SanityFunction294(const CEDI_PrivateData* pD, const CEDI_Type2ScreenerRateLimit* rateLimit);
uint32_t CEDI_SanityFunction295(const CEDI_PrivateData* pD, const CEDI_Type2ScreenerRateLimit* rateLimit);
uint32_t CEDI_SanityFunction297(const CEDI_PrivateData* pD, const uint16_t rxHighWatermark, const uint16_t rxLowWatermark);
uint32_t CEDI_SanityFunction298(const CEDI_PrivateData* pD, const uint16_t* rxHighWatermark, const uint16_t* rxLowWatermark);
uint32_t CEDI_SanityFunction299(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_AxiQosConfig* axiQosConfig);
uint32_t CEDI_SanityFunction300(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_AxiQosConfig* axiQosConfig);
uint32_t CEDI_SanityFunction301(const CEDI_PrivateData* pD, const CEDI_AsfInfo* asfInfo);
uint32_t CEDI_SanityFunction302(const CEDI_PrivateData* pD, const CEDI_WatermarkLvl* watermarkLvl);
uint32_t CEDI_SanityFunction303(const CEDI_PrivateData* pD, const CEDI_WatermarkLvl* watermarkLvl);
uint32_t CEDI_SanityFunction306(const CEDI_PrivateData* pD, const CEDI_AxiHostArbitrationCfg* axiCfg);
uint32_t CEDI_SanityFunction307(const CEDI_PrivateData* pD, const CEDI_AxiHostArbitrationCfg* axiCfg);
uint32_t CEDI_SanityFunction308(const CEDI_PrivateData* pD, const CEDI_AxiChannelType axiChannel, const CEDI_AxiBuffCfg* axiBuffCfg);
uint32_t CEDI_SanityFunction309(const CEDI_PrivateData* pD, const CEDI_AxiChannelType axiChannel, const CEDI_AxiBuffCfg* axiBuffCfg);
uint32_t CEDI_SanityFunction314(const CEDI_PrivateData* pD, const CEDI_SerdesRate serDes);
uint32_t CEDI_SanityFunction315(const CEDI_PrivateData* pD, const CEDI_SerdesRate* serDes);
uint32_t CEDI_SanityFunction318(const CEDI_PrivateData* pD, const CEDI_Pcs25gOperationMode opMode);
uint32_t CEDI_SanityFunction319(const CEDI_PrivateData* pD, const CEDI_Pcs25gOperationMode* opMode);
uint32_t CEDI_SanityFunction320(const CEDI_PrivateData* pD, const CEDI_TestPatternMode patternMode);
uint32_t CEDI_SanityFunction321(const CEDI_PrivateData* pD, const CEDI_TestPatternMode* patternMode);
uint32_t CEDI_SanityFunction324(const CEDI_PrivateData* pD, const CEDI_Pcs25gStatus* pcsStatus);
uint32_t CEDI_SanityFunction325(const CEDI_PrivateData* pD, const CEDI_TestSeedReg testSeedReg, const CEDI_TestPatternSeed* testPatternSeed);
uint32_t CEDI_SanityFunction326(const CEDI_PrivateData* pD, const CEDI_TestSeedReg testSeedReg, const CEDI_TestPatternSeed* testPatternSeed);
uint32_t CEDI_SanityFunction331(const CEDI_PrivateData* pD, const CEDI_FecError* fecError);
uint32_t CEDI_SanityFunction346(const CEDI_PrivateData* pD, const CEDI_Pcs25gCfg* pcsCfg);

#define	CEDI_ProbeSF CEDI_SanityFunction1
#define	CEDI_InitSF CEDI_SanityFunction2
#define	CEDI_DestroySF CEDI_SanityFunction3
#define	CEDI_StartSF CEDI_SanityFunction3
#define	CEDI_StopSF CEDI_SanityFunction3
#define	CEDI_IsrSF CEDI_SanityFunction3
#define	CEDI_SetEventEnableSF CEDI_SanityFunction7
#define	CEDI_GetEventEnableSF CEDI_SanityFunction8
#define	CEDI_SetIntrptModerateSF CEDI_SanityFunction9
#define	CEDI_GetIntrptModerateSF CEDI_SanityFunction10
#define	CEDI_SetIntrptModerateThreshSF CEDI_SanityFunction9
#define	CEDI_GetIntrptModerateThreshSF CEDI_SanityFunction10
#define	CEDI_SetIfSpeedSF CEDI_SanityFunction13
#define	CEDI_GetIfSpeedSF CEDI_SanityFunction14
#define	CEDI_SetJumboFramesRxSF CEDI_SanityFunction7
#define	CEDI_GetJumboFramesRxSF CEDI_SanityFunction16
#define	CEDI_SetJumboFrameRxMaxLenSF CEDI_SanityFunction17
#define	CEDI_GetJumboFrameRxMaxLenSF CEDI_SanityFunction18
#define	CEDI_SetUniDirEnableSF CEDI_SanityFunction7
#define	CEDI_GetUniDirEnableSF CEDI_SanityFunction16
#define	CEDI_SetTxChecksumOffloadSF CEDI_SanityFunction7
#define	CEDI_GetTxChecksumOffloadSF CEDI_SanityFunction16
#define	CEDI_SetRxBufOffsetSF CEDI_SanityFunction23
#define	CEDI_GetRxBufOffsetSF CEDI_SanityFunction16
#define	CEDI_SetRxQBufferSizeSF CEDI_SanityFunction25
#define	CEDI_GetRxQBufferSizeSF CEDI_SanityFunction3
#define	CEDI_SetRxQBurstLengthSF CEDI_SanityFunction27
#define	CEDI_GetRxQBurstLengthSF CEDI_SanityFunction28
#define	CEDI_SetTxQBurstLengthSF CEDI_SanityFunction27
#define	CEDI_GetTxQBurstLengthSF CEDI_SanityFunction28
#define	CEDI_Set1536ByteFramesRxSF CEDI_SanityFunction7
#define	CEDI_Get1536ByteFramesRxSF CEDI_SanityFunction16
#define	CEDI_SetRxChecksumOffloadSF CEDI_SanityFunction7
#define	CEDI_GetRxChecksumOffloadSF CEDI_SanityFunction16
#define	CEDI_SetFcsRemoveSF CEDI_SanityFunction7
#define	CEDI_GetFcsRemoveSF CEDI_SanityFunction16
#define	CEDI_SetTxPartialStFwdSF CEDI_SanityFunction7
#define	CEDI_GetTxPartialStFwdSF CEDI_SanityFunction38
#define	CEDI_SetRxPartialStFwdSF CEDI_SanityFunction7
#define	CEDI_GetRxPartialStFwdSF CEDI_SanityFunction38
#define	CEDI_SetRxDmaDataAddrMaskSF CEDI_SanityFunction41
#define	CEDI_GetRxDmaDataAddrMaskSF CEDI_SanityFunction10
#define	CEDI_SetRxBadPreambleSF CEDI_SanityFunction7
#define	CEDI_GetRxBadPreambleSF CEDI_SanityFunction16
#define	CEDI_SetFullDuplexSF CEDI_SanityFunction7
#define	CEDI_GetFullDuplexSF CEDI_SanityFunction16
#define	CEDI_SetIgnoreFcsRxSF CEDI_SanityFunction7
#define	CEDI_GetIgnoreFcsRxSF CEDI_SanityFunction16
#define	CEDI_SetRxHalfDuplexInTxSF CEDI_SanityFunction7
#define	CEDI_GetRxHalfDuplexInTxSF CEDI_SanityFunction16
#define	CEDI_SetPreambleCrcCoverSF CEDI_SanityFunction51
#define	CEDI_GetPreambleCrcCoverSF CEDI_SanityFunction52
#define	CEDI_GetIfCapabilitiesSF CEDI_SanityFunction53
#define	CEDI_SetLoopbackSF CEDI_SanityFunction54
#define	CEDI_GetLoopbackSF CEDI_SanityFunction16
#define	CEDI_CalcMaxTxFrameSizeSF CEDI_SanityFunction56
#define	CEDI_QueueTxBufSF CEDI_SanityFunction57
#define	CEDI_QTxBufSF CEDI_SanityFunction58
#define	CEDI_DeQTxBufSF CEDI_SanityFunction59
#define	CEDI_TxDescFreeSF CEDI_SanityFunction18
#define	CEDI_FreeTxDescSF CEDI_SanityFunction61
#define	CEDI_GetTxDescStatSF CEDI_SanityFunction62
#define	CEDI_GetTxDescSizeSF CEDI_SanityFunction8
#define	CEDI_GetTxQDescSizeSF CEDI_SanityFunction8
#define	CEDI_ResetTxQSF CEDI_SanityFunction3
#define	CEDI_StartTxSF CEDI_SanityFunction3
#define	CEDI_StartQTxSF CEDI_SanityFunction3
#define	CEDI_StopTxSF CEDI_SanityFunction3
#define	CEDI_StopQTxSF CEDI_SanityFunction3
#define	CEDI_AbortTxSF CEDI_SanityFunction3
#define	CEDI_TransmittingSF CEDI_SanityFunction3
#define	CEDI_EnableTxSF CEDI_SanityFunction3
#define	CEDI_GetTxEnabledSF CEDI_SanityFunction3
#define	CEDI_GetTxStatusSF CEDI_SanityFunction74
#define	CEDI_GetQTxStatusSF CEDI_SanityFunction75
#define	CEDI_ClearTxStatusSF CEDI_SanityFunction76
#define	CEDI_ClearQTxStatusSF CEDI_SanityFunction77
#define	CEDI_EnableCbsSF CEDI_SanityFunction7
#define	CEDI_DisableCbsSF CEDI_SanityFunction7
#define	CEDI_GetCbsQSettingSF CEDI_SanityFunction80
#define	CEDI_SetIpgStretchSF CEDI_SanityFunction81
#define	CEDI_GetIpgStretchSF CEDI_SanityFunction82
#define	CEDI_SetMinIpgSF CEDI_SanityFunction83
#define	CEDI_SetTxDeferSF CEDI_SanityFunction3
#define	CEDI_GetTxDeferSF CEDI_SanityFunction85
#define	CEDI_CalcMaxRxFrameSizeSF CEDI_SanityFunction8
#define	CEDI_AddRxBufSF CEDI_SanityFunction87
#define	CEDI_NumRxBufsSF CEDI_SanityFunction18
#define	CEDI_NumRxUsedSF CEDI_SanityFunction3
#define	CEDI_ReadRxBufSF CEDI_SanityFunction90
#define	CEDI_GetRxDescStatSF CEDI_SanityFunction91
#define	CEDI_GetRxDescSizeSF CEDI_SanityFunction8
#define	CEDI_GetRxQDescSizeSF CEDI_SanityFunction8
#define	CEDI_RxEnabledSF CEDI_SanityFunction3
#define	CEDI_EnableRxSF CEDI_SanityFunction3
#define	CEDI_DisableRxSF CEDI_SanityFunction3
#define	CEDI_RemoveRxBufSF CEDI_SanityFunction97
#define	CEDI_ResetRxQSF CEDI_SanityFunction7
#define	CEDI_GetRxStatusSF CEDI_SanityFunction99
#define	CEDI_GetQRxStatusSF CEDI_SanityFunction100
#define	CEDI_ClearRxStatusSF CEDI_SanityFunction101
#define	CEDI_ClearQRxStatusSF CEDI_SanityFunction102
#define	CEDI_SetHdrDataSplitSF CEDI_SanityFunction7
#define	CEDI_GetHdrDataSplitSF CEDI_SanityFunction16
#define	CEDI_SetQHdrDataSplitSF CEDI_SanityFunction3
#define	CEDI_GetQHdrDataSplitSF CEDI_SanityFunction85
#define	CEDI_SetRscEnableSF CEDI_SanityFunction7
#define	CEDI_GetRscEnableSF CEDI_SanityFunction16
#define	CEDI_SetRscClearMaskSF CEDI_SanityFunction7
#define	CEDI_SetSpecificAddrSF CEDI_SanityFunction110
#define	CEDI_GetSpecificAddrSF CEDI_SanityFunction111
#define	CEDI_SetSpecificAddr1MaskSF CEDI_SanityFunction112
#define	CEDI_GetSpecificAddr1MaskSF CEDI_SanityFunction113
#define	CEDI_DisableSpecAddrSF CEDI_SanityFunction3
#define	CEDI_SetTypeIdMatchSF CEDI_SanityFunction115
#define	CEDI_GetTypeIdMatchSF CEDI_SanityFunction116
#define	CEDI_SetUnicastEnableSF CEDI_SanityFunction7
#define	CEDI_GetUnicastEnableSF CEDI_SanityFunction16
#define	CEDI_SetMulticastEnableSF CEDI_SanityFunction7
#define	CEDI_GetMulticastEnableSF CEDI_SanityFunction16
#define	CEDI_SetNoBroadcastSF CEDI_SanityFunction7
#define	CEDI_GetNoBroadcastSF CEDI_SanityFunction16
#define	CEDI_SetSendBroadcastToAllQsSF CEDI_SanityFunction3
#define	CEDI_GetSendBroadcastToAllQsSF CEDI_SanityFunction85
#define	CEDI_SetVlanOnlySF CEDI_SanityFunction7
#define	CEDI_GetVlanOnlySF CEDI_SanityFunction16
#define	CEDI_SetStackedVlanRegSF CEDI_SanityFunction127
#define	CEDI_GetStackedVlanRegSF CEDI_SanityFunction128
#define	CEDI_SetCopyAllFramesSF CEDI_SanityFunction7
#define	CEDI_GetCopyAllFramesSF CEDI_SanityFunction16
#define	CEDI_SetHashAddrSF CEDI_SanityFunction131
#define	CEDI_GetHashAddrSF CEDI_SanityFunction132
#define	CEDI_SetLenErrDiscardSF CEDI_SanityFunction7
#define	CEDI_GetLenErrDiscardSF CEDI_SanityFunction16
#define	CEDI_GetNumScreenRegsSF CEDI_SanityFunction135
#define	CEDI_SetType1ScreenRegSF CEDI_SanityFunction136
#define	CEDI_GetType1ScreenRegSF CEDI_SanityFunction137
#define	CEDI_SetType2ScreenRegSF CEDI_SanityFunction138
#define	CEDI_GetType2ScreenRegSF CEDI_SanityFunction139
#define	CEDI_SetType2EthertypeRegSF CEDI_SanityFunction140
#define	CEDI_GetType2EthertypeRegSF CEDI_SanityFunction141
#define	CEDI_SetType2CompareRegSF CEDI_SanityFunction142
#define	CEDI_GetType2CompareRegSF CEDI_SanityFunction143
#define	CEDI_SetPauseEnableSF CEDI_SanityFunction7
#define	CEDI_GetPauseEnableSF CEDI_SanityFunction16
#define	CEDI_TxPauseFrameSF CEDI_SanityFunction3
#define	CEDI_TxZeroQPauseSF CEDI_SanityFunction3
#define	CEDI_GetRxPauseQuantumSF CEDI_SanityFunction18
#define	CEDI_SetTxPauseQuantumSF CEDI_SanityFunction149
#define	CEDI_GetTxPauseQuantumSF CEDI_SanityFunction150
#define	CEDI_SetCopyPauseDisableSF CEDI_SanityFunction7
#define	CEDI_GetCopyPauseDisableSF CEDI_SanityFunction16
#define	CEDI_SetPfcPriorityBasedPausSF CEDI_SanityFunction7
#define	CEDI_GetPfcPriorityBasedPausSF CEDI_SanityFunction16
#define	CEDI_TxPfcPriorityBasedPauseSF CEDI_SanityFunction3
#define	CEDI_SetTxPfcPauseFrameFieldSF CEDI_SanityFunction3
#define	CEDI_GetTxPfcPauseFrameFieldSF CEDI_SanityFunction10
#define	CEDI_SetEnableMultiPfcPauseQSF CEDI_SanityFunction7
#define	CEDI_GetEnableMultiPfcPauseQSF CEDI_SanityFunction16
#define	CEDI_SetUnicastPtpDetectSF CEDI_SanityFunction7
#define	CEDI_GetUnicastPtpDetectSF CEDI_SanityFunction16
#define	CEDI_SetPtpRxUnicastIpAddrSF CEDI_SanityFunction162
#define	CEDI_GetPtpRxUnicastIpAddrSF CEDI_SanityFunction8
#define	CEDI_SetPtpTxUnicastIpAddrSF CEDI_SanityFunction162
#define	CEDI_GetPtpTxUnicastIpAddrSF CEDI_SanityFunction8
#define	CEDI_Set1588TimerSF CEDI_SanityFunction166
#define	CEDI_Get1588TimerSF CEDI_SanityFunction167
#define	CEDI_Adjust1588TimerSF CEDI_SanityFunction168
#define	CEDI_Set1588TimerIncSF CEDI_SanityFunction169
#define	CEDI_Get1588TimerIncSF CEDI_SanityFunction170
#define	CEDI_SetTsuTimerCompValSF CEDI_SanityFunction171
#define	CEDI_GetTsuTimerCompValSF CEDI_SanityFunction172
#define	CEDI_GetPtpFrameTxTimeSF CEDI_SanityFunction167
#define	CEDI_GetPtpFrameRxTimeSF CEDI_SanityFunction167
#define	CEDI_GetPtpPeerFrameTxTimeSF CEDI_SanityFunction167
#define	CEDI_GetPtpPeerFrameRxTimeSF CEDI_SanityFunction167
#define	CEDI_Get1588SyncStrobeTimeSF CEDI_SanityFunction167
#define	CEDI_SetExtTsuPortEnableSF CEDI_SanityFunction7
#define	CEDI_GetExtTsuPortEnableSF CEDI_SanityFunction16
#define	CEDI_Set1588OneStepTxSyncEnaSF CEDI_SanityFunction7
#define	CEDI_Get1588OneStepTxSyncEnaSF CEDI_SanityFunction16
#define	CEDI_SetDescTimeStampModeSF CEDI_SanityFunction182
#define	CEDI_GetDescTimeStampModeSF CEDI_SanityFunction183
#define	CEDI_SetStoreRxTimeStampSF CEDI_SanityFunction7
#define	CEDI_GetStoreRxTimeStampSF CEDI_SanityFunction16
#define	CEDI_ResetPcsSF CEDI_SanityFunction3
#define	CEDI_GetPcsReadySF CEDI_SanityFunction16
#define	CEDI_StartAutoNegotiationSF CEDI_SanityFunction188
#define	CEDI_SetAutoNegEnableSF CEDI_SanityFunction7
#define	CEDI_GetAutoNegEnableSF CEDI_SanityFunction16
#define	CEDI_GetLinkStatusSF CEDI_SanityFunction16
#define	CEDI_GetAnRemoteFaultSF CEDI_SanityFunction16
#define	CEDI_GetAnCompleteSF CEDI_SanityFunction16
#define	CEDI_SetAnAdvPageSF CEDI_SanityFunction188
#define	CEDI_GetAnAdvPageSF CEDI_SanityFunction195
#define	CEDI_GetLpAbilityPageSF CEDI_SanityFunction196
#define	CEDI_GetPageRxSF CEDI_SanityFunction3
#define	CEDI_SetNextPageTxSF CEDI_SanityFunction198
#define	CEDI_GetNextPageTxSF CEDI_SanityFunction199
#define	CEDI_GetLpNextPageSF CEDI_SanityFunction200
#define	CEDI_GetPhyIdSF CEDI_SanityFunction8
#define	CEDI_SetMdioEnableSF CEDI_SanityFunction7
#define	CEDI_GetMdioEnableSF CEDI_SanityFunction3
#define	CEDI_PhyStartMdioWriteSF CEDI_SanityFunction204
#define	CEDI_PhyStartMdioReadSF CEDI_SanityFunction204
#define	CEDI_GetMdioReadDataSF CEDI_SanityFunction18
#define	CEDI_GetMdioIdleSF CEDI_SanityFunction3
#define	CEDI_ReadStatsSF CEDI_SanityFunction3
#define	CEDI_ClearStatsSF CEDI_SanityFunction3
#define	CEDI_TakeSnapshotSF CEDI_SanityFunction3
#define	CEDI_SetReadSnapshotSF CEDI_SanityFunction7
#define	CEDI_GetReadSnapshotSF CEDI_SanityFunction16
#define	CEDI_SetWakeOnLanRegSF CEDI_SanityFunction213
#define	CEDI_GetWakeOnLanRegSF CEDI_SanityFunction214
#define	CEDI_SetLpiTxEnableSF CEDI_SanityFunction7
#define	CEDI_GetLpiTxEnableSF CEDI_SanityFunction16
#define	CEDI_GetLpiStatsSF CEDI_SanityFunction217
#define	CEDI_GetDesignConfigSF CEDI_SanityFunction218
#define	CEDI_SetWriteStatsEnableSF CEDI_SanityFunction7
#define	CEDI_GetWriteStatsEnableSF CEDI_SanityFunction16
#define	CEDI_IncStatsRegsSF CEDI_SanityFunction3
#define	CEDI_SetRxBackPressureSF CEDI_SanityFunction7
#define	CEDI_GetRxBackPressureSF CEDI_SanityFunction16
#define	CEDI_SetCollisionTestSF CEDI_SanityFunction7
#define	CEDI_GetCollisionTestSF CEDI_SanityFunction16
#define	CEDI_SetRetryTestSF CEDI_SanityFunction7
#define	CEDI_GetRetryTestSF CEDI_SanityFunction16
#define	CEDI_WriteUserOutputsSF CEDI_SanityFunction3
#define	CEDI_ReadUserOutputsSF CEDI_SanityFunction18
#define	CEDI_SetUserOutPinSF CEDI_SanityFunction7
#define	CEDI_ReadUserInputsSF CEDI_SanityFunction18
#define	CEDI_GetUserInPinSF CEDI_SanityFunction16
#define	CEDI_GetMdioInStateSF CEDI_SanityFunction16
#define	CEDI_ReadRegSF CEDI_SanityFunction234
#define	CEDI_WriteRegSF CEDI_SanityFunction235
#define	CEDI_SetTxQueueNumSF CEDI_SanityFunction236
#define	CEDI_GetTxQueueNumSF CEDI_SanityFunction16
#define	CEDI_SetRxQueueNumSF CEDI_SanityFunction238
#define	CEDI_GetRxQueueNumSF CEDI_SanityFunction16
#define	CEDI_SetTxQueueSegAllocSF CEDI_SanityFunction240
#define	CEDI_SetTxQueueSchedulerSF CEDI_SanityFunction241
#define	CEDI_GetTxQueueSchedulerSF CEDI_SanityFunction242
#define	CEDI_SetRateLimitSF CEDI_SanityFunction3
#define	CEDI_GetRateLimitSF CEDI_SanityFunction16
#define	CEDI_SetDwrrWeightingSF CEDI_SanityFunction3
#define	CEDI_SetEtsBandAllocSF CEDI_SanityFunction3
#define	CEDI_GetDwrrWeightingSF CEDI_SanityFunction16
#define	CEDI_GetEtsBandAllocSF CEDI_SanityFunction16
#define	CEDI_SetEnstTimeConfigSF CEDI_SanityFunction249
#define	CEDI_GetEnstTimeConfigSF CEDI_SanityFunction250
#define	CEDI_SetEnstEnableSF CEDI_SanityFunction7
#define	CEDI_GetEnstEnableSF CEDI_SanityFunction252
#define	CEDI_GetEnstSupportedSF CEDI_SanityFunction252
#define	CEDI_SetReportingBadFCSSF CEDI_SanityFunction7
#define	CEDI_GetReportingBadFCSSF CEDI_SanityFunction252
#define	CEDI_SetPtpSingleStepSF CEDI_SanityFunction7
#define	CEDI_GetPtpSingleStepSF CEDI_SanityFunction252
#define	CEDI_SetMiiOnRgmiiSF CEDI_SanityFunction7
#define	CEDI_GetMiiOnRgmiiSF CEDI_SanityFunction16
#define	CEDI_SetCbsIdleSlopeSF CEDI_SanityFunction3
#define	CEDI_GetCbsIdleSlopeSF CEDI_SanityFunction8
#define	CEDI_GetLinkFaultIndicationSF CEDI_SanityFunction262
#define	CEDI_SetFrameEliminationTagSSF CEDI_SanityFunction263
#define	CEDI_GetFrameEliminationTagSSF CEDI_SanityFunction264
#define	CEDI_SetFrameEliminationEnabSF CEDI_SanityFunction265
#define	CEDI_GetFrameEliminationEnabSF CEDI_SanityFunction266
#define	CEDI_SetFrameEliminationSeqRSF CEDI_SanityFunction265
#define	CEDI_GetFrameEliminationSeqRSF CEDI_SanityFunction266
#define	CEDI_SetFrameEliminationConfSF CEDI_SanityFunction269
#define	CEDI_GetFrameEliminationConfSF CEDI_SanityFunction270
#define	CEDI_SetFrameEliminationTagCSF CEDI_SanityFunction271
#define	CEDI_GetFrameEliminationTagCSF CEDI_SanityFunction272
#define	CEDI_SetFrameEliminationTimoSF CEDI_SanityFunction3
#define	CEDI_GetFrameEliminationStatSF CEDI_SanityFunction274
#define	CEDI_GetEmacSF CEDI_SanityFunction275
#define	CEDI_GetPmacSF CEDI_SanityFunction275
#define	CEDI_GetMacTypeSF CEDI_SanityFunction277
#define	CEDI_SetPreemptionConfigSF CEDI_SanityFunction278
#define	CEDI_GetPreemptionConfigSF CEDI_SanityFunction279
#define	CEDI_PreemptionRestartVerifiSF CEDI_SanityFunction3
#define	CEDI_SetMmslEventEnableSF CEDI_SanityFunction7
#define	CEDI_GetMmslEventEnableSF CEDI_SanityFunction8
#define	CEDI_ReadMmslStatsSF CEDI_SanityFunction283
#define	CEDI_ReadMmslStatusSF CEDI_SanityFunction284
#define	CEDI_SetLockupConfigSF CEDI_SanityFunction285
#define	CEDI_GetLockupConfigSF CEDI_SanityFunction286
#define	CEDI_SetType1ScreenRegDropEnSF CEDI_SanityFunction7
#define	CEDI_GetType1ScreenRegDropEnSF CEDI_SanityFunction16
#define	CEDI_SetType2ScreenRegDropEnSF CEDI_SanityFunction7
#define	CEDI_GetType2ScreenRegDropEnSF CEDI_SanityFunction16
#define	CEDI_SetRxQFlushConfigSF CEDI_SanityFunction291
#define	CEDI_GetRxQFlushConfigSF CEDI_SanityFunction292
#define	CEDI_GetRxDmaFlushedPacketsCSF CEDI_SanityFunction18
#define	CEDI_SetType2ScreenerRateLimSF CEDI_SanityFunction294
#define	CEDI_GetType2ScreenerRateLimSF CEDI_SanityFunction295
#define	CEDI_GetRxType2RateLimitTrigSF CEDI_SanityFunction18
#define	CEDI_SetRxWatermarkSF CEDI_SanityFunction297
#define	CEDI_GetRxWatermarkSF CEDI_SanityFunction298
#define	CEDI_SetAxiQosConfigSF CEDI_SanityFunction299
#define	CEDI_GetAxiQosConfigSF CEDI_SanityFunction300
#define	CEDI_GetAsfInfoSF CEDI_SanityFunction301
#define	CEDI_SetRxThresholdControlSF CEDI_SanityFunction302
#define	CEDI_GetRxThresholdControlSF CEDI_SanityFunction303
#define	CEDI_SetTxThresholdControlSF CEDI_SanityFunction302
#define	CEDI_GetTxThresholdControlSF CEDI_SanityFunction303
#define	CEDI_SetAxiArbitrationCfgSF CEDI_SanityFunction306
#define	CEDI_GetAxiArbitrationCfgSF CEDI_SanityFunction307
#define	CEDI_SetAxiReqNumSF CEDI_SanityFunction308
#define	CEDI_GetAxiReqNumSF CEDI_SanityFunction309
#define	CEDI_SetPreambleConversionSF CEDI_SanityFunction3
#define	CEDI_GetPreambleConversionSF CEDI_SanityFunction85
#define	CEDI_SetDeferOnLinkIntEnableSF CEDI_SanityFunction3
#define	CEDI_GetDeferOnLinkIntEnableSF CEDI_SanityFunction85
#define	CEDI_SetPcs25gSerdesRateSF CEDI_SanityFunction314
#define	CEDI_GetPcs25gSerdesRateSF CEDI_SanityFunction315
#define	CEDI_SetPcs25gFecEnableSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gFecEnableSF CEDI_SanityFunction85
#define	CEDI_SetPcs25gOperationModeSF CEDI_SanityFunction318
#define	CEDI_GetPcs25gOperationModeSF CEDI_SanityFunction319
#define	CEDI_SetPcs25gRxTestPatternMSF CEDI_SanityFunction320
#define	CEDI_GetPcs25gRxTestPatternMSF CEDI_SanityFunction321
#define	CEDI_SetPcs25gTxTestPatternMSF CEDI_SanityFunction320
#define	CEDI_GetPcs25gTxTestPatternMSF CEDI_SanityFunction321
#define	CEDI_GetPcs25gStatusSF CEDI_SanityFunction324
#define	CEDI_SetPcs25gTxTestPatternSSF CEDI_SanityFunction325
#define	CEDI_GetPcs25gTxTestPatternSSF CEDI_SanityFunction326
#define	CEDI_GetPcs25gRxDecoderErrCoSF CEDI_SanityFunction16
#define	CEDI_GetPcs25gTestPatternErrSF CEDI_SanityFunction18
#define	CEDI_GetPcs25gPrbsErrorCountSF CEDI_SanityFunction18
#define	CEDI_GetPcs25gBitErrorCountSF CEDI_SanityFunction8
#define	CEDI_GetPcs25gFecErrorCountSF CEDI_SanityFunction331
#define	CEDI_SetPcs25gEventEnableSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gEventEnableSF CEDI_SanityFunction8
#define	CEDI_SetPcs25gTxScrBypassEnaSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gTxScrBypassEnaSF CEDI_SanityFunction85
#define	CEDI_SetPcs25gRxDescrBypassESF CEDI_SanityFunction3
#define	CEDI_GetPcs25gRxDescrBypassESF CEDI_SanityFunction85
#define	CEDI_SetPcs25gFecErrIndEnablSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gFecErrIndEnablSF CEDI_SanityFunction85
#define	CEDI_SetPcs25gTxDatapathEnabSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gTxDatapathEnabSF CEDI_SanityFunction85
#define	CEDI_SetPcs25gRxDatapathEnabSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gRxDatapathEnabSF CEDI_SanityFunction85
#define	CEDI_SetPcs25gEnableSF CEDI_SanityFunction3
#define	CEDI_GetPcs25gEnableSF CEDI_SanityFunction85
#define	CEDI_Pcs25gSetupSF CEDI_SanityFunction346
#define	CEDI_CheckPcs25gSyncSF CEDI_SanityFunction3


#endif	/* CEDI_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
