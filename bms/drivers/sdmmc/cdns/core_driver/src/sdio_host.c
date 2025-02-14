/******************************************************************************
 * Copyright (C) 2013-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio_host.c
 * SD Host controller driver
 *****************************************************************************/
#include "sdio_host.h"
#include "sdio_config.h"
#include "sdio_errors.h"
#include "sdio_card_general.h"
#include "sdio_debug.h"
#include "sdio_types.h"
#include "sdio_dma.h"
#include "sdio_utils.h"
#include "sdio_request.h"
#include "sdio_cq.h"
#include "sdio_phy.h"
 
#include <sdmmc.h>

#ifndef SDIO_CFG_HOST_VER
    #error "SDIO_CFG_HOST_VER should be defined explicitly"
#endif

#ifndef SDIO_CFG_ENABLE_MMC
    #error "SDIO_CFG_ENABLE_MMC should be defined explicitly"
#endif

#ifndef SDIO_CFG_ENABLE_IO
    #error "SDIO_CFG_ENABLE_IO should be defined explicitly"
#endif

#ifndef ENABLE_CARD_INTERRUPT
    #error "ENABLE_CARD_INTERRUPT should be defined explicitly"
#endif

#ifndef SYTEM_CLK_KHZ
    #error "SYTEM_CLK_KHZ should be defined explicitly"
#endif

#ifndef DEBOUNCING_TIME
    #error "DEBOUNCING_TIME should be defined explicitly"
#endif

#ifndef SDIO_SDMA_SUPPORTED
    #error "SDIO_SDMA_SUPPORTED should be defined explicitly"
#endif

#ifndef SDIO_ADMA1_SUPPORTED
    #error "SDIO_ADMA1_SUPPORTED should be defined explicitly"
#endif

#ifndef SDIO_ADMA2_SUPPORTED
    #error "SDIO_ADMA2_SUPPORTED should be defined explicitly"
#endif

#ifndef SDIO_ADMA3_SUPPORTED
    #error "SDIO_ADMA3_SUPPORTED should be defined explicitly"
#endif

#ifndef CHANGE_DATA_ENDIANITY_NODMA
    #error "CHANGE_DATA_ENDIANITY_NODMA should be defined explicitly"
#endif

#ifndef SWAP_EXT_CSD
    #define SWAP_EXT_CSD 0
#endif

static const uint32_t Freq200MHzInKHz = 200000U;

static LIST_NODE SuppDevListArray[MAX_SUPPORTED_DEVICE_COUNT + 1U];
LIST_NODE *SuppDevList = &SuppDevListArray[0];

static uint8_t SDIOHost_GetResponse(CSDD_Request* pRequest, CSDD_SDIO_Slot* pSlot);
static void ConfigHostHighSpeedMode(CSDD_SDIO_Slot* pSlot, bool SetHighSpeed);
static uint8_t SDIOHost_SetBusWidth(CSDD_SDIO_Slot* pSlot, uint8_t BusType);
static void SDIOHost_ExecCardCmdFiniteNonAppNoTuning(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest);
static void SDIOHost_CheckBusyAbort(CSDD_SDIO_Host* pSdioHost, CSDD_Request* pRequest);
static void SDIOHost_CheckInterruptOnRecovery(CSDD_SDIO_Slot* pSlot, uint32_t status);
static void SDIOHost_ExecCardCommand_Set_Command_Flag(CSDD_SDIO_Slot* pSlot, uint32_t* commandInformation, CSDD_Request* pRequest,CSDD_Request* currentMainRequest);
static void SDIOHost_SubCommandStatusCheck(CSDD_SDIO_Slot* pSlot);
static uint8_t SDIOHost_EnableCMD23Ifsupported(CSDD_SDIO_Slot* pSlot);
static void SDIOHost_CheckRequestOnRecovery(CSDD_SDIO_Slot* pSlot, const CSDD_Request* pRequest);
static uint8_t SDIOHost_CheckErrorOnRecovery(CSDD_SDIO_Slot* pSlot);
static void SDIOHost_ErrorRecoveryExecuteCmd12(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint8_t doResetLines);
static void SDIOHost_ExecCardCommand_Set_Block_Count(CSDD_SDIO_Slot* pSlot,CSDD_Request* pRequest);

static void DumpRequest(const CSDD_Request *pRequest, uint8_t isError)
{

    if (isError != 0U) {

        if (pRequest->pCmd->requestFlags.dataTransferDirection != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Cmd=%d, Arg=0x%lX, BlockCount=%lu, BlockLen=%u\n",
                         pRequest->pCmd->command,
                         pRequest->pCmd->argument, pRequest->pCmd->blockCount,
                         pRequest->pCmd->blockLen);
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Cmd=%d, Arg=0x%lX\n",
                         pRequest->pCmd->command, pRequest->pCmd->argument);
        }
    }
    else {
        if ( pRequest->pCmd->requestFlags.dataTransferDirection != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Cmd=%d, Arg=0x%lX, BlockCount=%lu, BlockLen=%u\n",
                        pRequest->pCmd->command,
                        pRequest->pCmd->argument, pRequest->pCmd->blockCount,
                        pRequest->pCmd->blockLen);
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Cmd=%d, Arg=0x%lX\n",
                        pRequest->pCmd->command, pRequest->pCmd->argument);
        }

    }

}

//-----------------------------------------------------------------------------
uint8_t ResetLines(CSDD_SDIO_Slot* pSlot, uint8_t cmd, uint8_t dat)
{
    uint32_t tmp, mask = 0;
    uint8_t i, status = SDIO_ERR_NO_ERROR;

    if (cmd != 0U) {
        mask |= (uint32_t)SRS11_SOFT_RESET_CMD_LINE;
    }
    if (dat != 0U) {
        mask |= (uint32_t)SRS11_SOFT_RESET_DAT_LINE;
    }

    for (i = 0; i < SDIO_CFG_RESET_COUNT; i++) {
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS11);
        tmp |= mask;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS11, tmp);

        status = WaitForValue(&pSlot->RegOffset->SRS.SRS11,
                              mask, 0, COMMANDS_TIMEOUT);

        if (status != SDIO_ERR_NO_ERROR) {
            break;
        }
    }
    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t ResetHost(CSDD_SDIO_Host* pSdioHost)
{
    uint8_t i, status = SDIO_ERR_NO_ERROR;
    uint32_t tmp;

    for (i = 0; i < SDIO_CFG_RESET_COUNT; i++) {
        // reset controller for sure
        tmp = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS00);
        tmp |= (uint32_t)HRS0_SOFTWARE_RESET;
        CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS00, tmp);

        status = WaitForValue(&pSdioHost->RegOffset->HRS.HRS00,
                              (uint32_t)HRS0_SOFTWARE_RESET, 0, COMMANDS_TIMEOUT);
        if (status != SDIO_ERR_NO_ERROR) {

            break;
        }
    }
    return (status);
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_MMC
//-----------------------------------------------------------------------------


uint8_t SDIOHost_MmcTune(const CSDD_SDIO_Host* pSdioHost, uint8_t value)
{
    uint32_t Hrs6;

    Hrs6 = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS06);
    Hrs6 &= ~(uint32_t)HRS6_EMMC_TUNE_VALUE_MASK;

    Hrs6 |= HRS6_EMMC_TUNE_SET_VALUE(value) | (uint32_t)HRS6_EMMC_TUNE_REQUEST;
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS06, Hrs6);

    return WaitForValue(&pSdioHost->RegOffset->HRS.HRS06,
                        (uint32_t)HRS6_EMMC_TUNE_REQUEST, 0, COMMANDS_TIMEOUT);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CheckMmcBusConfiguration(uint8_t BusWidth, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((BusWidth == (uint8_t)CSDD_BUS_WIDTH_1)
        && (AccessMode > CSDD_ACCESS_MODE_HS_SDR)) {
        status = SDIO_ERR_UNSUPORRTED_OPERATION;
    } else if ((BusWidth != (uint8_t)CSDD_BUS_WIDTH_8)
               && (AccessMode > CSDD_ACCESS_MODE_HS_200)) {
        status = SDIO_ERR_UNSUPORRTED_OPERATION;
    } else {
        // All 'if ... else if' constructs shall be terminated with an 'else' statement
        // (MISRA2012-RULE-15_7-3)
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcBuffSize(const uint8_t busWidth)
{
    uint8_t bufferSize = 0U;

    if ((uint8_t)CSDD_BUS_WIDTH_8 == busWidth) {
        bufferSize = 128U;
    }
    if ((uint8_t)CSDD_BUS_WIDTH_4 == busWidth) {
        bufferSize = 64U;
    }

    return (bufferSize);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static const uint32_t* CalcWritePattern(const uint8_t busWidth)
{
    static const uint32_t emmcPattern4b[64 / 4] = {
        0x00ff0fffU,
        0xccc3ccffU,
        0xffcc3cc3U,
        0xeffefffeU,
        0xddffdfffU,
        0xfbfffbffU,
        0xff7fffbfU,
        0xefbdf777U,
        0xf0fff0ffU,
        0x3cccfc0fU,
        0xcfcc33ccU,
        0xeeffefffU,
        0xfdfffdffU,
        0xffbfffdfU,
        0xfff7ffbbU,
        0xde7b7ff7U
    };

    static const uint32_t emmcPattern8b[128 / 4] = {
        0xff00ffffU,
        0x0000ffffU,
        0xccccffffU,
        0xcccc33ccU,
        0xcc3333ccU,
        0xffffccccU,
        0xffffeeffU,
        0xffeeeeffU,
        0xffddffffU,
        0xddddffffU,
        0xbbffffffU,
        0xbbffffffU,
        0xffffffbbU,
        0xffffff77U,
        0x77ff7777U,
        0xffeeddbbU,
        0x00ffffffU,
        0x00ffffffU,
        0xccffff00U,
        0xcc33ccccU,
        0x3333ccccU,
        0xffccccccU,
        0xffeeffffU,
        0xeeeeffffU,
        0xddffffffU,
        0xddffffffU,
        0xffffffddU,
        0xffffffbbU,
        0xffffbbbbU,
        0xffff77ffU,
        0xff7777ffU,
        0xeeddbb77U
    };

    const uint32_t* writePattern = NULL;

    if ((uint8_t)CSDD_BUS_WIDTH_8 == busWidth) {
        writePattern = (const uint32_t*)emmcPattern8b;
    }
    if ((uint8_t)CSDD_BUS_WIDTH_4 == busWidth) {
        writePattern = (const uint32_t*)emmcPattern4b;
    }

    return (writePattern);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcLongestValidDelayChainVal(const uint8_t* PatternOk)
{
    // looking for longest valid delay chain value (the best tuning value)
    uint8_t Pos = 0;
    uint8_t Length = 0;
    uint8_t CurrLength = 0;
    uint8_t i;
    for (i = 0; i < 40U; i++) {
        if (PatternOk[i] == 1U) {
            CurrLength++;
            if (CurrLength > Length) {
                Pos = i - Length;
                Length++;
            }
        }
        else {
            CurrLength = 0;
        }
    }
    Pos += (Length / 2U);

    return (Pos);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ExecuteTuningMmc(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    CSDD_Request Request = {0};
    uint32_t *ReadPattern = (uint32_t*)pSlot->AuxBuff;
    uint8_t i, j, PatternOk[40];

    uint8_t BufferSize = CalcBuffSize(pSlot->BusWidth);
    uint32_t const *WritePattern = CalcWritePattern(pSlot->BusWidth);

    SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD21, .arg = 0,
                                            .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 1}),
                                &((SD_CsddRequesParamsExt){.buf = ReadPattern, .blkCount = 1, .blkLen = BufferSize,
                                  .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ}));

    for (j = 0; j < 40U; j++) {

        if (pSlot->pSdioHost->pSetTuneVal != NULL) {
            status = pSlot->pSdioHost->pSetTuneVal(pSlot->pSdioHost,j);
        }
        else {
            status = SDIO_ERR_INVALID_PARAMETER;
            break;
        }
        for (i = 0; i < (BufferSize / 4U); i++) {
            ReadPattern[i] = 0;
        }

        // start data transfer
        SDIOHost_ExecCardCommand(pSlot, &Request);
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        if (Request.status == 0U) {
            // compare data with pattern
            PatternOk[j] = 1;
            for (i = 0; i < (BufferSize / 4U); i++) {
                if (WritePattern[i] != ReadPattern[i]) {
                    PatternOk[j] = 0;
                    break; // read pattern is not correct - exit loop
                }
            }
        }
        else {
            PatternOk[j] = 0;
        }
    }

    if(status == SDIO_ERR_NO_ERROR)
    {
        uint8_t Pos = CalcLongestValidDelayChainVal(PatternOk);
        // Delay value set to Pos

        if (pSlot->pSdioHost->pSetTuneVal != NULL) {
            status = pSlot->pSdioHost->pSetTuneVal(pSlot->pSdioHost,Pos);
        }

        // start data transfer
        SDIOHost_ExecCardCommand(pSlot, &Request);
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);
    }
    return status;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ChangeDeviceMmcBusModeInitWork(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode accessMode)
{
    uint8_t status = CheckMmcBusConfiguration(pSlot->BusWidth, accessMode);

    if (status == SDIO_ERR_NO_ERROR) {
        status = SDIOHost_SelectCard(pSlot, pSlot->pDevice->RCA);

        if (status == SDIO_ERR_NO_ERROR) {
            /// Read Extended CSD register from a card
            status = SDIOHost_ReadExCSD(pSlot, (uint8_t*)pSlot->AuxBuff);
#ifdef DBG_PRINT_EXT_CSD
            printf("ExCSD:\n");
            for (int i = 0; i < 512; i++) {
                if (i % 16 == 0)
                    printf("%03d: ", i);
                printf("%2x ", ((uint8_t*)pSlot->AuxBuff)[i]);
                if ( i % 16 == 15)
                    printf("\n");
            }
#endif
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcInitialArgBusWidth(uint8_t busWidth, uint8_t* argBusWidth)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    switch(busWidth) {
    case (uint8_t)CSDD_BUS_WIDTH_1:
        *argBusWidth = MMC_SWITCH_BUS_WIDTH_1;
        break;
    case (uint8_t)CSDD_BUS_WIDTH_4:
        *argBusWidth = MMC_SWITCH_BUS_WIDTH_4;
        break;
    case (uint8_t)CSDD_BUS_WIDTH_8:
        *argBusWidth = MMC_SWITCH_BUS_WIDTH_8;
        break;
    default:
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "argBusWidth =  %d\n",  *argBusWidth );
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Invalid busWidth %d\n", busWidth);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcBusWidthAndAccModeHsSdr(uint8_t mmcdeviceType, uint8_t* argBusWidth, uint32_t* argAccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((mmcdeviceType & MMC_EXCSD_DEV_HS_52MHZ) == 0U) {
        status = SDIO_ERR_FUNCTION_UNSUPP;
    } else {
        *argAccessMode = MMC_SWITCH_HIGH_SPEED;
        *argBusWidth &= ~MMC_SWITCH_BUS_WIDTH_DDR_MASK;
    }
    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcBusWidthAndAccModeHsDdr(uint8_t mmcdeviceType, uint8_t* argBusWidth, uint32_t* argAccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((mmcdeviceType & (MMC_EXCSD_DEV_HS_52MHZ
                          | MMC_EXCSD_DEV_HS_DDR_52MHZ_1_8_V_3_3_V
                          | MMC_EXCSD_DEV_HS_DDR_52MHZ_1_2_V)) == 0U) {
        status = SDIO_ERR_FUNCTION_UNSUPP;
    } else {
        *argAccessMode = MMC_SWITCH_HIGH_SPEED;
        *argBusWidth |= MMC_SWITCH_BUS_WIDTH_DDR_MASK;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcBusWidthAndAccModeHs200(uint8_t mmcdeviceType, uint8_t* argBusWidth, uint32_t* argAccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((mmcdeviceType & (MMC_EXCSD_DEV_HS_SDR_200MHZ_1_8_V
                          | MMC_EXCSD_DEV_HS_SDR_200MHZ_1_2_V)) == 0U) {
        status = SDIO_ERR_FUNCTION_UNSUPP;
    } else {
        *argAccessMode = MMC_SWITCH_HIGH_SPEED_200;
        *argBusWidth &= ~MMC_SWITCH_BUS_WIDTH_DDR_MASK;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcBusWidthAndAccModeHs400(uint8_t mmcdeviceType, uint8_t* argBusWidth, uint32_t* argAccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((mmcdeviceType & (MMC_EXCSD_DEV_HS_DDR_200MHZ_1_8_V
                          | MMC_EXCSD_DEV_HS_DDR_200MHZ_1_2_V)) == 0U) {
        status = SDIO_ERR_FUNCTION_UNSUPP;
    } else {
        *argAccessMode = MMC_SWITCH_HIGH_SPEED_400;
        *argBusWidth |= MMC_SWITCH_BUS_WIDTH_DDR_MASK;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcBusWidthAndAccModeHs400Es(uint8_t mmcdeviceType, uint8_t esSupported, uint8_t* argBusWidth, uint32_t* argAccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (esSupported == 0U) {
        status = SDIO_ERR_FUNCTION_UNSUPP;
    }else if ((mmcdeviceType & (MMC_EXCSD_DEV_HS_DDR_200MHZ_1_8_V
                                | MMC_EXCSD_DEV_HS_DDR_200MHZ_1_2_V)) == 0U) {
        status = SDIO_ERR_FUNCTION_UNSUPP;
    } else {
        *argAccessMode = MMC_SWITCH_HIGH_SPEED_400;
        *argBusWidth |= MMC_SWITCH_BUS_WIDTH_DDR_MASK | MMC_SWITCH_BUS_WIDTH_ES;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t CalcArgBusWidthAndArgAccessMode(CSDD_SpeedMode accessMode,
                                               uint8_t mmcdeviceType, uint8_t esSupported,
                                               uint8_t* argBusWidth, uint32_t* argAccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

#ifdef FORCE_MMC_TYPE
    mmcdeviceType = 0xff;
#endif

#ifdef FORCE_ES_SUPPORT
    esSupported = 1;
#endif

    switch(accessMode) {
    case CSDD_ACCESS_MODE_MMC_LEGACY:
        *argAccessMode = MMC_HIGH_SPEED_DISABLE;
        *argBusWidth &= ~MMC_SWITCH_BUS_WIDTH_DDR_MASK;
        break;

    case CSDD_ACCESS_MODE_HS_SDR:
        status = CalcBusWidthAndAccModeHsSdr(mmcdeviceType, argBusWidth, argAccessMode);
        break;

    case CSDD_ACCESS_MODE_HS_DDR:
        status = CalcBusWidthAndAccModeHsDdr(mmcdeviceType, argBusWidth, argAccessMode);
        break;

    case CSDD_ACCESS_MODE_HS_200:
        status = CalcBusWidthAndAccModeHs200(mmcdeviceType, argBusWidth, argAccessMode);
        break;

    case CSDD_ACCESS_MODE_HS_400:
        status = CalcBusWidthAndAccModeHs400(mmcdeviceType, argBusWidth, argAccessMode);
        break;

    case CSDD_ACCESS_MODE_HS_400_ES:
        status = CalcBusWidthAndAccModeHs400Es(mmcdeviceType, esSupported, argBusWidth, argAccessMode);
        break;
    default:
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }
    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ChangeDeviceMmcBusModeMmcSwitch(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode,
                                               uint32_t ArgAccessMode, uint8_t ArgBusWidth)
{
    uint8_t status;

    if (((ArgBusWidth & MMC_SWITCH_BUS_WIDTH_DDR_MASK) == 0U)
        || (AccessMode == CSDD_ACCESS_MODE_HS_400_ES)) {

        // change bus width to disable dual data rate option
        status = SDIOHost_MmcSwitch(pSlot, MMC_EXCSD_BUS_WIDTH, ArgBusWidth);

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_MmcSwitch(pSlot, MMC_EXCSD_HS_TIMING, (uint8_t)ArgAccessMode);
        }
    } else {
        status = SDIOHost_MmcSwitch(pSlot, MMC_EXCSD_HS_TIMING, (uint8_t)ArgAccessMode);

        if (status == SDIO_ERR_NO_ERROR) {
            // change bus width to enable dual data rate option
            status = SDIOHost_MmcSwitch(pSlot, MMC_EXCSD_BUS_WIDTH, ArgBusWidth);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ChangeDeviceMmcBusMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    // MMC card
    uint32_t ArgAccessMode;
    uint8_t MmcdeviceType, esSupported = 0;
    uint8_t ArgBusWidth;

    uint8_t status = ChangeDeviceMmcBusModeInitWork(pSlot, AccessMode);
#if (SWAP_EXT_CSD == 1)
    // get info about supported bus acces modes
    MmcdeviceType = GET_BYTE_FROM_BUFFER2(pSlot->AuxBuff, 512,
                                          MMC_EXCSD_DEVICE_TYPE);
    esSupported = GET_BYTE_FROM_BUFFER2(pSlot->AuxBuff, 512,
                                        MMC_EXCSD_ES_SUPPORTED);
#else
    const uint32_t* auxBuff = pSlot->AuxBuff;

    MmcdeviceType = GET_BYTE_FROM_BUFFER(auxBuff,
                                         MMC_EXCSD_DEVICE_TYPE);
    esSupported = GET_BYTE_FROM_BUFFER(auxBuff,
                                       MMC_EXCSD_ES_SUPPORTED);
#endif

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "MmcdeviceType %0x\n", MmcdeviceType);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "esSupported %0x\n", esSupported);

    status = CalcInitialArgBusWidth(pSlot->BusWidth, &ArgBusWidth);

    if (status == SDIO_ERR_NO_ERROR) {
        status = CalcArgBusWidthAndArgAccessMode(AccessMode, MmcdeviceType, esSupported,
                                                 &ArgBusWidth, &ArgAccessMode);
        if (status == SDIO_ERR_NO_ERROR) {
            status = ChangeDeviceMmcBusModeMmcSwitch(pSlot, AccessMode, ArgAccessMode, ArgBusWidth);
        }
    }
    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t HostSupportAccessMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);

    switch(AccessMode) {
    case CSDD_ACCESS_MODE_SDR12:
    case CSDD_ACCESS_MODE_SDR25:
        break;
    case CSDD_ACCESS_MODE_SDR50:
        if ((tmp & SRS17_SDR50_SUPPORTED) == 0U) {
            status = SDIO_ERR_UNSUPORRTED_OPERATION;
        }
        break;
    case CSDD_ACCESS_MODE_SDR104:
        if ((tmp & SRS17_SDR104_SUPPORTED) == 0U) {
            status = SDIO_ERR_UNSUPORRTED_OPERATION;
        }
        break;
    case CSDD_ACCESS_MODE_DDR50:
        if ((tmp & SRS17_DDR50_SUPPORTED) == 0U) {
            status = SDIO_ERR_UNSUPORRTED_OPERATION;
        }
        break;
    case CSDD_ACCESS_MODE_HS_400_ES:
        if (!pSlot->pSdioHost->hs400EsSupported) {
            status = SDIO_ERR_UNSUPORRTED_OPERATION;
        }
        break;
    default:
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#if SDIO_CFG_HOST_VER == 3
static uint8_t ChangeHostMmcBusMode_SD3(CSDD_SDIO_Slot* pSlot, uint8_t AccessMode)
{
    uint32_t Hrs0;
    uint32_t HostMmcAccessMode;
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;
    bool EnableHighSpeed = false;

    switch(AccessMode) {
    case (uint8_t)CSDD_ACCESS_MODE_MMC_LEGACY:
        EnableHighSpeed = true;
        HostMmcAccessMode = 0;
        break;
    case (uint8_t)CSDD_ACCESS_MODE_HS_SDR:
        EnableHighSpeed = true;
        HostMmcAccessMode = 0;
        break;
    case (uint8_t)CSDD_ACCESS_MODE_HS_DDR:
        EnableHighSpeed = true;
        HostMmcAccessMode = HRS0_DDR(pSlot->SlotNr);
        break;
    default:
        return SDIO_ERR_INVALID_PARAMETER;
    }

    Hrs0 = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS00);
    Hrs0 &= ~HRS0_DDR_MASK;
    Hrs0 |= HostMmcAccessMode;
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS00, Hrs0);

    ConfigHostHighSpeedMode(pSlot, EnableHighSpeed);

    return SDIO_ERR_NO_ERROR;
}
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ChangeHostMmcBusMode_SD4(const CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

#if SDIO_CFG_HOST_VER >= 4
    uint32_t Hrs6;
    uint32_t HostMmcAccessMode;
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;

    switch(AccessMode) {
    case CSDD_ACCESS_MODE_MMC_LEGACY:
        HostMmcAccessMode = HRS6_EMMC_MODE_LEGACY;
        break;
    case CSDD_ACCESS_MODE_HS_SDR:
        HostMmcAccessMode = HRS6_EMMC_MODE_SDR;
        break;
    case CSDD_ACCESS_MODE_HS_DDR:
        HostMmcAccessMode = HRS6_EMMC_MODE_DDR;
        break;
    case CSDD_ACCESS_MODE_HS_200:
        HostMmcAccessMode = HRS6_EMMC_MODE_HS200;
        break;
    case CSDD_ACCESS_MODE_HS_400:
        HostMmcAccessMode = HRS6_EMMC_MODE_HS400;
        break;
    case CSDD_ACCESS_MODE_HS_400_ES:
        HostMmcAccessMode = HRS6_EMMC_MODE_HS400_ES;
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        Hrs6 = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS06);
        Hrs6 &= ~HRS6_EMMC_MODE_MASK;
        Hrs6 |= HostMmcAccessMode;
        CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS06, Hrs6);
    }
#else
    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_UNSUPORRTED_OPERATION);
    status = SDIO_ERR_UNSUPORRTED_OPERATION;
#endif

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#if SDIO_CFG_HOST_VER == 3
static uint8_t ChangeHostMmcBusMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
#else
static uint8_t ChangeHostMmcBusMode(const CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
#endif
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pSlot->pSdioHost->SpecVersNumb > 3U) {
        (void)ChangeHostMmcBusMode_SD4(pSlot, AccessMode);
    }
    else {
#if SDIO_CFG_HOST_VER == 3
        (void)ChangeHostMmcBusMode_SD3(pSlot, AccessMode);
#else
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_UNSUPORRTED_OPERATION);
        status = SDIO_ERR_UNSUPORRTED_OPERATION;
#endif
    }
    return (status);
}
//-----------------------------------------------------------------------------

static uint8_t CalcArgBusWidth(uint8_t accessMode, uint8_t busWidth, uint8_t* pArgBusWidth)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    switch(accessMode) {
    case (uint8_t)CSDD_ACCESS_MODE_MMC_LEGACY:
    case (uint8_t)CSDD_ACCESS_MODE_HS_SDR:
    case (uint8_t)CSDD_ACCESS_MODE_HS_200:
        if (busWidth == (uint8_t)CSDD_BUS_WIDTH_4) {
            (*pArgBusWidth) = MMC_SWITCH_BUS_WIDTH_4;
        }
        if (busWidth == (uint8_t)CSDD_BUS_WIDTH_8) {
            (*pArgBusWidth) = MMC_SWITCH_BUS_WIDTH_8;
        }
        break;
    case (uint8_t)CSDD_ACCESS_MODE_HS_DDR:
        if (busWidth == (uint8_t)CSDD_BUS_WIDTH_4) {
            (*pArgBusWidth) = MMC_SWITCH_BUS_WIDTH_4_DDR;
        }
        if (busWidth == (uint8_t)CSDD_BUS_WIDTH_8) {
            (*pArgBusWidth) = MMC_SWITCH_BUS_WIDTH_8_DDR;
        }
        break;
    case (uint8_t)CSDD_ACCESS_MODE_HS_400:
        // busWidth should be equal to CSDD_BUS_WIDTH_8, but this condition is already in CheckMmcBusConfiguration() function.
        (*pArgBusWidth) = MMC_SWITCH_BUS_WIDTH_8_DDR;
        break;
    case (uint8_t)CSDD_ACCESS_MODE_HS_400_ES:
        (*pArgBusWidth) = MMC_SWITCH_BUS_WIDTH_8_DDR;
        (*pArgBusWidth) |= MMC_SWITCH_BUS_WIDTH_ES;
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    return (status);
}

//-----------------------------------------------------------------------------
static uint8_t ChangeDeviceMmcBusWidth(CSDD_SDIO_Slot* pSlot, uint8_t BusWidth)
{
    uint8_t ArgBusWidth = MMC_SWITCH_BUS_WIDTH_1;
    uint8_t status = CheckMmcBusConfiguration(BusWidth, (CSDD_SpeedMode)pSlot->AccessMode);

    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        status = CalcArgBusWidth(pSlot->AccessMode, BusWidth, &ArgBusWidth);

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_MmcSwitch(pSlot, MMC_EXCSD_BUS_WIDTH, ArgBusWidth);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
static uint8_t ChangeHostUhsiMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t tmp;
    uint32_t UhsMode;
    bool EnableHighSpeed = false;

    switch(AccessMode) {
    case CSDD_ACCESS_MODE_SDR12:
        UhsMode = SRS15_UHS_MODE_SDR12;
        break;
    case CSDD_ACCESS_MODE_SDR25:
        UhsMode = SRS15_UHS_MODE_SDR25;
        EnableHighSpeed = true;
        break;
    case CSDD_ACCESS_MODE_SDR50:
        UhsMode = SRS15_UHS_MODE_SDR50;
        EnableHighSpeed = true;
        break;
    case CSDD_ACCESS_MODE_SDR104:
        UhsMode = SRS15_UHS_MODE_SDR104;
        EnableHighSpeed = true;
        break;
    case CSDD_ACCESS_MODE_DDR50:
        UhsMode = SRS15_UHS_MODE_DDR50;
        EnableHighSpeed = true;
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        ConfigHostHighSpeedMode(pSlot, EnableHighSpeed);

        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
        tmp &= ~SRS15_UHS_MODE_MASK;
        tmp |= UhsMode;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, tmp);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void ConfigHostHighSpeedMode(CSDD_SDIO_Slot* pSlot, bool SetHighSpeed)
{
    uint32_t tmp;

    if (SetHighSpeed != 0) {
        // enable high-speed in the SDIO host controller
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);
        tmp |= SRS10_HIGH_SPEED_ENABLE;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, tmp);
    }
    else {
        // disable high-speed in the SDIO host controller
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);
        tmp &= ~SRS10_HIGH_SPEED_ENABLE;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, tmp);
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t Tuning(CSDD_SDIO_Slot* pSlot, uint8_t Reset)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t RepeatCount;
    uint32_t tmp;
    CSDD_Request Request = {0};

    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD19, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

    tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    if (Reset != 0U) {
        // Reset tuning circuit
        tmp &= ~SRS15_SAMPLING_CLOCK_SELECT;
    }
    // reset tuning unit
    tmp &= ~SRS15_SAMPLING_CLOCK_SELECT;
    // start of tuning
    tmp |= SRS15_EXECUTE_TUNING;

    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, tmp);

    RepeatCount = 40;
    while((tmp & SRS15_EXECUTE_TUNING) != 0U) {
        SDIOHost_ExecCardCmdFiniteNonAppNoTuning(pSlot, &Request);
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        // check status
        if (Request.status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
            status = Request.status;
        }

        if (((RepeatCount--) == 0U) || (status != SDIO_ERR_NO_ERROR)) {
            break;
        }

        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    }

    if ((status == SDIO_ERR_NO_ERROR) && ((tmp & SRS15_SAMPLING_CLOCK_SELECT) == 0U)) {
        status = SDIO_ERR_TUNING_FAILED;
    }

    // tuning completed
    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t IsTunningNeeded(CSDD_SDIO_Slot* pSlot, const CSDD_Request *pRequest)
{
    uint8_t result = 1U;
    uint32_t Timing;

    // if request is NULL
    // it means that tuning is executed not before command execution
    // but after access mode change
    if (pRequest != NULL) {
        // if the command is CMD19 that it means the re-tuning is just executing
        // if re-tuning is disabled it means it is not necessary
        if ((pRequest->pCmd->command == SDIO_CMD19) || (pSlot->RetuningEnabled == 0U)) {
            result = 0U;
        } else {
            uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
            if ((tmp & SRS12_RETUNING_EVENT) != 0U) {
                pSlot->RetuningRequest = 1;
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12_RETUNING_EVENT);
            }

            if (pRequest->pCmd->requestFlags.dataPresent != 0U) {
                pSlot->DataCount += (uint32_t)pRequest->pCmd->blockCount * pRequest->pCmd->blockLen;
            }

            RetuningGetTimer(&Timing, pSlot->SlotNr);
            // if host controller doesn't request tuning
            // and transfered data doesn't exceed 14MB
            // and re-tuning timer doesn't signal that tuning is needed
            // then we return without execution of tuning procedure
            if ((pSlot->RetuningRequest == 0U) && (pSlot->DataCount < 0xE00000U) && (Timing > 0U)) {
                result = 0U;
            }
        }
    }

    return (result);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ExecuteTuning(CSDD_SDIO_Slot* pSlot, uint8_t Reset, const CSDD_Request *pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (IsTunningNeeded(pSlot, pRequest) != 0U) {
        status = Tuning(pSlot, Reset);
        if (status != SDIO_ERR_NO_ERROR) {
            status = Tuning(pSlot, 1);
        }

        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {
            uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);
            uint32_t Timing = SRS17_GET_RETUNING_TIMER_COUNT(tmp);

            RetuningSetTimer(Timing, pSlot->SlotNr);
            pSlot->DataCount = 0;
            pSlot->RetuningRequest = 0;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t IsUhsiSupported(CSDD_SDIO_Slot* pSlot)
{
    uint8_t result = 1U;
    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->CRS.CRS63);

    if (CRS63_GET_SPEC_VERSION(tmp) < 2U) {
        result = 0U;
    } else {
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);

        if ((tmp & SRS16_VOLTAGE_1_8V_SUPPORT) == 0U) {
            result = 0U;
        } else {
            tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);

            uint32_t UhsiModes = (uint32_t)(SRS17_SDR50_SUPPORTED | SRS17_SDR104_SUPPORTED
                                            | SRS17_DDR50_SUPPORTED);

            if ((tmp & UhsiModes) == 0U) {
                result = 0U;
            }
        }
    }

    return (result);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#define SD_PMIC_ID 0
#define SD_PMIC_REGULATOR_NAME "aldo1"

#if !defined(CONFIG_COMPILE_ROM) && defined(CONFIG_COMPILE_ASIC) && defined(CONFIG_DRV_PMIC)

#include "pmic.h"


static uint8_t SDSupplyVoltage18v(uint32_t pmic_id, const char* name)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    struct regulator_dev *rdev;
    int ret;

    rdev = itcs_regulator_get(pmic_id, name);
    if (!rdev) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error get regulator, %d\n", SDIO_ERR_SWITCH_VOLTAGE_FAILED);
        status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
    } else {
        ret = itcs_regulator_is_enabled(rdev);
        if (ret < 0) {
            ret = itcs_regulator_enable(rdev);
            if (ret < 0) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error enable regulator, %d\n", SDIO_ERR_SWITCH_VOLTAGE_FAILED);
                status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
            }
        }

        ret = itcs_regulator_set_voltage(rdev, 1800000, 1800000);
        if (ret) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error set voltage, %d\n", SDIO_ERR_SWITCH_VOLTAGE_FAILED);
            status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
        }
    }

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Voltage set to %d uV\n", itcs_regulator_get_voltage(rdev));
    itcs_regulator_put(rdev);
    return status;
}

#else

#if defined(CONFIG_TBH_SDMMC) && !defined(CONFIG_DRV_PMIC)
#warning "PMIC driver is not available, SDIO voltage switching is not supported"
#endif

static uint8_t SDSupplyVoltage18v(uint32_t pmic_id, const char* name)
{
    return SDIO_ERR_NO_ERROR;
}

#endif
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t SwitchVoltageCardNot33(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    // SD clock disable
    SDIOHost_SupplySDCLK(pSlot, 0);

    // PMIC switch to 1.8V
    SDSupplyVoltage18v(SD_PMIC_ID, SD_PMIC_REGULATOR_NAME);

    // 1.8V signal enable
    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    tmp |= SRS15_18V_ENABLE;
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, tmp);

    // wait 5ms
#ifdef CONFIG_COMPILE_RTL
    udelay(300);
#else
    CPS_DelayNs(5000000U);
#endif

    // if 1.8V signal enable is cleared by host return with error
    tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    if ((tmp & SRS15_18V_ENABLE) == 0U) {
        // SDIO_ERR_SWITCH_VOLTAGE_FAILED
        status = 0xFFU;
    } else {
        // clock enable
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS11);
        tmp |= (uint32_t)SRS11_INT_CLOCK_ENABLE;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS11, tmp);
        status = WaitForValue(&pSlot->RegOffset->SRS.SRS11,
                              (uint32_t)SRS11_INT_CLOCK_STABLE, 1, COMMANDS_TIMEOUT);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {
            // supply clock
            SDIOHost_SupplySDCLK(pSlot, 1);

            // wait 1ms
            CPS_DelayNs(1000000U);

            pSlot->UhsiSelected = 1;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t SwitchVoltageCard33Wait(CSDD_SDIO_Slot* pSlot, const uint32_t DatLevel)
{
    uint8_t status;


    // PMIC switch to 1.8V
    SDSupplyVoltage18v(SD_PMIC_ID, SD_PMIC_REGULATOR_NAME);

    // 1.8V signal enable
    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    tmp |= SRS15_18V_ENABLE;
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, tmp);

    // wait 5ms
#ifdef CONFIG_COMPILE_RTL
    udelay(300);
#else
    CPS_DelayNs(5000000U);
#endif

    // if 1.8V signal enable is cleared by host return with error
    tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    if ((tmp & SRS15_18V_ENABLE) == 0U) {
        status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        // clock enable
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS11);
        tmp |= (uint32_t)SRS11_INT_CLOCK_ENABLE;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS11, tmp);
        status = WaitForValue(&pSlot->RegOffset->SRS.SRS11,
                              (uint32_t)SRS11_INT_CLOCK_STABLE, 1, COMMANDS_TIMEOUT);
        if (status == SDIO_ERR_NO_ERROR) {
            SDIOHost_SupplySDCLK(pSlot, 1);


            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Waiting 1ms started...\n", tmp);
#ifdef CONFIG_COMPILE_RTL
            udelay(200);
#else
            CPS_DelayNs(1000000U);
#endif
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Waiting 1ms ended...\n", tmp);

            // if dat line is not 1111b return error
            tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09);
            if ((tmp & DatLevel) != DatLevel) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "SRS.SRS09 0x%x\n", tmp);
                status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t SwitchVoltageCard33(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    const uint32_t DatLevel = (SRS9_DAT0_SIGNAL_LEVEL | SRS9_DAT1_SIGNAL_LEVEL
                                         | SRS9_DAT2_SIGNAL_LEVEL | SRS9_DAT3_SIGNAL_LEVEL);
    uint32_t tmp;

    // set bus with in the card
    SDIOHost_ExecCardCommand(pSlot, pRequest);
    SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
    if (pRequest->status != 0U) {
        status = pRequest->status;
    } else {
        // SD clock disable
        SDIOHost_SupplySDCLK(pSlot, 0);

        // if dat line is not 0000b return error
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09);
        if ((tmp & DatLevel) != 0U) {
            status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
        } else {
            status = SwitchVoltageCard33Wait(pSlot, DatLevel);
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t SignalVoltageSwitch(CSDD_SDIO_Slot* pSlot, uint8_t CardIs33)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Switch to 1,8V\n");

    if (CardIs33 == 0U) {
        status = SwitchVoltageCardNot33(pSlot);
    } else {
        CSDD_Request Request = {0};

        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD11, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                            .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

        status = SwitchVoltageCard33(pSlot, &Request);
        // check status

        if (status != SDIO_ERR_NO_ERROR) {
            // if error appears set SD bus power to 0
            (void)SDIOHost_SetPower(pSlot, 0);
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
        else {
            pSlot->UhsiSelected = 1;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint32_t SDIOHost_SetTimeout(CSDD_SDIO_Slot* pSlot, uint32_t timeoutValUs)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t temp, sdmclk_khz, sdmclk_Mhz, timeout_interval;
    uint8_t j;
    uint32_t sdmclk, timeoutVal;

    temp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);
    sdmclk_khz = SRS16_GET_TIMEOUT_CLK_FREQ(temp);

    if (((temp & SRS16_TIMEOUT_CLOCK_UNIT_MHZ) == 0U) && (timeoutValUs < 1000U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }
    else if (sdmclk_khz == 0U) {
        status = SDIO_ERR_BASE_CLK_IS_ZERO;
    } else {
        if ((temp & SRS16_TIMEOUT_CLOCK_UNIT_MHZ) != 0U) {
            sdmclk_khz *= 1000U;
        }
        sdmclk_Mhz = sdmclk_khz / 1000U;

        if (sdmclk_Mhz == 0U) {
            sdmclk = sdmclk_khz;
            timeoutVal = timeoutValUs / 1000U;
        }
        else {
            sdmclk = sdmclk_Mhz;
            timeoutVal = timeoutValUs;
        }

        // calculate Data Timeout Counter Value
        timeout_interval = 8192/*2 ^ 13*/;
        for(j = 0; j < 15U; j++) {
            //if  (timeoutVal < ((1 / sdmclk) * timeout_interval))
            if (timeoutVal < (timeout_interval / sdmclk)) {
                break;
            }
            timeout_interval *= 2U;
        }
        timeout_interval = (uint32_t)j << 16;

        temp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS11);
        temp &= (uint32_t)~SRS11_TIMEOUT_MASK;
        temp |= timeout_interval;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS11, temp);
    }

    return status;
}
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static LIST_NODE * GetNewListNode(LIST_NODE *ListHead)
{
    LIST_NODE *NewListNode = NULL;
    uint32_t i;

    for(i = 0; i < (MAX_SUPPORTED_DEVICE_COUNT + 1U); i++) {
        if(ListHead[i].Item == NULL) {
            NewListNode = &ListHead[i];
            break;
        }
    }
    return NewListNode;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void RemoveListNode(LIST_NODE *ListNode)
{
    ListNode->Next = NULL;
    ListNode->Item = NULL;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ChangeDeviceSdBusMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t CardAccessMode;

    // if SD specification is less than 1.1 CMD6 command is not supported
    if (pSlot->pDevice->SpecVersNumb == 0U) {
        status = SDIO_ERR_BUS_SPEED_UNSUPP;
    } else {
        switch(AccessMode) {
        case CSDD_ACCESS_MODE_SDR12:
            CardAccessMode = SDCARD_SWITCH_ACCESS_MODE_SDR12;
            break;
        case CSDD_ACCESS_MODE_SDR25:
            CardAccessMode = SDCARD_SWITCH_ACCESS_MODE_SDR25;
            break;
        case CSDD_ACCESS_MODE_SDR50:
            CardAccessMode = SDCARD_SWITCH_ACCESS_MODE_SDR50;
            break;
        case CSDD_ACCESS_MODE_SDR104:
            CardAccessMode = SDCARD_SWITCH_ACCESS_MODE_SDR104;
            break;
        case CSDD_ACCESS_MODE_DDR50:
            CardAccessMode = SDCARD_SWITCH_ACCESS_MODE_DDR50;
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
            break;
        }
        if (status == SDIO_ERR_NO_ERROR) {
            // execute CMD6 command to change card access mode
            status = SDIOHost_SwitchFunction(pSlot, CardAccessMode,
                                             SDCARD_SWITCH_GROUP_NR_1);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_IO
//-----------------------------------------------------------------------------
static uint8_t ChangeDeviceIoBusMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status, HighSpeedReg, UhsiSupport;

    // get high speed register from a card
    status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_READ, &HighSpeedReg,
                                 sizeof(HighSpeedReg), CSDD_CCCR_HIGH_SPEED);
    if (status) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        return status;
    }

    // clear all access mode settings
    HighSpeedReg &= ~SDIO_CCCR_13_BSS_MASK;

    if (AccessMode > CSDD_ACCESS_MODE_SDR25) {
        status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_READ, &UhsiSupport,
                                     sizeof(UhsiSupport),
                                     CSDD_CCCR_UHSI_SUPPORT);
        if (status) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            return status;
        }
    }

    switch(AccessMode) {
    case CSDD_ACCESS_MODE_SDR12:
        break;
    case CSDD_ACCESS_MODE_SDR25:
        // check if card supports SDR25 mode (high speed)
        if ((HighSpeedReg & SDIO_CCCR_13_SHS) == 0U) {
            return SDIO_ERR_BUS_SPEED_UNSUPP;
        }
        HighSpeedReg |= SDIO_CCCR_13_EHS;
        break;
    case CSDD_ACCESS_MODE_SDR50:
        // check if card supports SDR50 access mode
        if ((UhsiSupport & SDIO_CCCR_14_SSDR50) == 0U) {
            return SDIO_ERR_BUS_SPEED_UNSUPP;
        }
        HighSpeedReg |= SDIO_CCCR_13_BSS_SDR50;
        break;
    case CSDD_ACCESS_MODE_SDR104:
        // check if card supports SDR104 access mode
        if (!(UhsiSupport & SDIO_CCCR_14_SSDR104) == 0U) {
            return SDIO_ERR_BUS_SPEED_UNSUPP;
        }
        HighSpeedReg |= SDIO_CCCR_13_BSS_SDR104;
        break;
    case CSDD_ACCESS_MODE_DDR50:
        // check if card supports DDR50 access mode
        if (!(UhsiSupport & SDIO_CCCR_14_SDDR50) == 0U) {
            return SDIO_ERR_BUS_SPEED_UNSUPP;
        }
        HighSpeedReg |= SDIO_CCCR_13_BSS_DDR50;
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        return SDIO_ERR_INVALID_PARAMETER;
    }

    // apply access bus mode to sdio card
    return SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_WRITE, &HighSpeedReg,
                               sizeof(HighSpeedReg),
                               CSDD_CCCR_HIGH_SPEED);
}
//-----------------------------------------------------------------------------
#endif

#if SDIO_CFG_HOST_VER >= 4
//-----------------------------------------------------------------------------
static void SDIOHost_InterruptHandlerAxiError(CSDD_SDIO_Host *pSdioHost)
{
    uint8_t status;

    SDIOHost_AxiErrorGetStatus(pSdioHost, &status);

    if (status != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Fatal Error! AXI error detected.\n");
        if (pSdioHost->axiErrorCallback != NULL) {
            pSdioHost->axiErrorCallback(pSdioHost, status);
        }
        SDIOHost_AxiErrorClearStatus(pSdioHost, status);
    }
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
void SDIOHost_InterruptHandler(CSDD_SDIO_Host *pSdioHost, uint8_t *Handled)
{
    // check which slot is the source of interrupt
    uint8_t i;

    *Handled = 0;

#if SDIO_CFG_HOST_VER >= 4
    SDIOHost_InterruptHandlerAxiError(pSdioHost);
#endif

    for (i = 0; i < pSdioHost->NumberOfSlots; i++) {
        uint32_t IntSignal = 1;

        /* if interrupts are enabled then check which slot signals interrupt
         * if interrupts are disabled then check interrupt register because
         * function is also in pooloing mode used when interrupts are disabled
         * */
        if ((pSdioHost->intEn != 0U) && (i < SDIO_SLOT_COUNT)) {
            IntSignal = (CPS_REG_READ(&pSdioHost->RegOffset->CRS.CRS63) >> i) & 1U;
        }

        if (IntSignal != 0U) {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[i];

            uint32_t regStatus = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
            while (regStatus != 0U) {
                uint32_t intToClear;
                *Handled = 1;
                /* The CC and TC are to be used only when CQ is disabled or halted */
                if ((pSlot->CQEnabled != 0U) && (pSlot->CQHalted == 0U)) {
                    regStatus &= ~(SRS12_COMMAND_COMPLETE | SRS12_TRANSFER_COMPLETE);
                }
                intToClear =  regStatus
                             & (SRS12_NORMAL_STAUS_MASK & ~SRS12_CMD_QUEUING_INT);
                // clear occurred normal status interrupts apart from CQ interrupt
                if (intToClear != 0U) {
                    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, intToClear);
                }
                SDIOHost_CheckInterrupt(pSlot, regStatus);

                regStatus = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
            }
        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_MmcBootStatus(const CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = 0;
    uint32_t hrs36;
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;

    status = WaitForValue(&pSdioHost->RegOffset->HRS.HRS36,
                          (uint32_t)HRS36_BOOT_ACT, 0, COMMANDS_TIMEOUT);

    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Timeout boot is active to long. Error %d\n", SDIO_ERR_MMC_BOOT_ERROR);
        status = SDIO_ERR_MMC_BOOT_ERROR;
    } else {
        hrs36 = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS36);
        if ((hrs36 & HRS36_BOOT_ERROR) != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Boot failed. Error %d\n", SDIO_ERR_MMC_BOOT_ERROR);
            status = SDIO_ERR_MMC_BOOT_ERROR;
        }
    }
    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SlotInitialize(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_Host* pSdioHost)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    const uint32_t data_timeout_ms = 500; //500ms

    const uint32_t SRS13 = (uint32_t)(SRS13_TUNING_ERROR_STAT_EN
                                      | SRS13_ADMA_ERROR_STAT_EN
                                      | SRS13_AUTO_CMD12_ERR_STAT_EN
                                      | SRS13_CURRENT_LIMIT_ERR_STAT_EN
                                      | SRS13_DATA_END_BIT_ERR_STAT_EN
                                      | SRS13_DATA_CRC_ERR_STAT_EN
                                      | SRS13_DATA_TIMEOUT_ERR_STAT_EN
                                      | SRS13_COMMAND_INDEX_ERR_STAT_EN
                                      | SRS13_COMMAND_END_BIT_ERR_STAT_EN
                                      | SRS13_COMMAND_CRC_ERR_STAT_EN
                                      | SRS13_COMMAND_TIMEOUT_ERR_STAT_EN
                                      | SRS13_RETUNING_EVENT_STAT_EN
                                      | SRS13_INTERRUPT_ON_LINE_A_STAT_EN
                                      | SRS13_INTERRUPT_ON_LINE_B_STAT_EN
                                      | SRS13_INTERRUPT_ON_LINE_C_STAT_EN
#if ENABLE_CARD_INTERRUPT
                                      | SRS13_CARD_INTERRUPT_STAT_EN
#endif
                                      | SRS13_CARD_REMOVAL_STAT_EN
                                      | SRS13_CARD_INERTION_STAT_EN
                                      | SRS13_BUF_READ_READY_STAT_EN
                                      | SRS13_BUF_WRITE_READY_STAT_EN
                                      | SRS13_DMA_INTERRUPT_STAT_EN
                                      | SRS13_BLOCK_GAP_EVENT_STAT_EN
                                      | SRS13_TRANSFER_COMPLETE_STAT_EN
                                      | SRS13_COMMAND_COMPLETE_STAT_EN
                                      | SRS13_RESPONSE_ERROR_STAT_EN
                                      | SRS13_CMD_QUEUING_STAT_EN);

    const uint32_t SRS14 = 0U;

    pSlot->UhsiSelected = 0;
    pSlot->CardInserted = 0;
    pSlot->NeedAttach = 0;
    pSlot->pSdioHost = pSdioHost;
    pSlot->RetuningEnabled = 0;
    pSlot->RetuningRequest = 0;
    pSlot->DataCount = 0;
    pSlot->DmaMode = (uint8_t)CSDD_AUTO_MODE;
    pSlot->pDevice = &pSlot->Devices[0];
    pSlot->SlotSettings.DMA64_En = 0;
    pSlot->SlotSettings.HostVer4_En = 0;
    pSlot->dmaModeSelected = CSDD_AUTO_MODE;

    if (SDIOHost_MmcBootStatus(pSlot) != SDIO_ERR_NO_ERROR) {
        status = SDIO_ERR_MMC_BOOT_ERROR;
    } else {
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, 0xFFFFFFFFU);

        DataSet(&pSlot->Devices, 0,
                (uint32_t)sizeof(pSlot->Devices[0]) * CSDD_MAX_DEV_PER_SLOT);
        pSlot->pCurrentRequest = NULL;
        pSlot->DMABufferBoundary = (uint32_t)SRS1_DMA_BUFF_SIZE_512KB;
        pSlot->AbortRequest = 0;
        pSlot->ProgClockMode = 0;
        uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
        if (pSdioHost->dma64BitEn) {
            uint32_t cap = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);
            uint32_t A64VS = SRS16_64BIT_SUPPORT_V4;
            if(pSdioHost->hostCtrlVer < 6U){
                A64VS = SRS16_64BIT_SUPPORT;
            }
            if ((cap & A64VS) == 0U) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "DMA 64 bit is not supported\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
                return SDIO_ERR_INVALID_PARAMETER;

            }
            pSlot->SlotSettings.DMA64_En = 1;
            reg |= SRS15_64_BIT_ADDRESSING;
            pSlot->SlotSettings.HostVer4_En = 1;
            reg |= SRS15_HOST_4_ENABLE;
        }
        if(pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP) {
            pSlot->SlotSettings.HostVer4_En = 1;
            reg |= SRS15_HOST_4_ENABLE;
        }
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, reg);
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS13, SRS13);
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, SRS14);

        (void)SDIOHost_SetTimeout(pSlot, data_timeout_ms * 1000U);

        if (status == SDIO_ERR_NO_ERROR) {
            (void)SDIOHost_SetPower(pSlot, 0);
            (void)SDIOHost_CQ_Init(pSlot);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_HostInitSlots(CSDD_SDIO_Host* pSdioHost)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    const uint32_t HRS0 = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS00);
    uint8_t i;

    pSdioHost->NumberOfSlots = 0;
    for (i = 0; i < SDIO_SLOT_COUNT; i++) {
        if ((HRS0 & HRS0_ACCESABLE_SLOT(i)) != 0U) {
            pSdioHost->Slots[i].RegOffset = pSdioHost->RegOffset;

            pSdioHost->Slots[i].SlotNr = i;

            pSdioHost->NumberOfSlots++;
        }
    }

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Found %d slots \n",
                (uint16_t)pSdioHost->NumberOfSlots);

    // NumberOfSlots can't be 0
    if (pSdioHost->NumberOfSlots == 0U) {
        status = SDIO_ERR_HARDWARE_PROBLEM;
    } else {

        for (i = 0; i < (MAX_SUPPORTED_DEVICE_COUNT + 1U); i++) {
            SuppDevListArray[i].Item = NULL;
            SuppDevListArray[i].Next = NULL;
        }
        SuppDevList->Item = (CSDD_DeviceInfo*)(uint32_t)0xFFFFFFFFUL;

        for (i = 0; i < pSdioHost->NumberOfSlots; i++) {
            status = SDIOHost_SlotInitialize(&pSdioHost->Slots[i], pSdioHost);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                break;
            }
        }

        if (status == SDIO_ERR_NO_ERROR) {
            CPS_DelayNs(2000000U);
            SDIOHost_AxiErrorInit(pSdioHost);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_HostInitialize(CSDD_SDIO_Host* pSdioHost)
{
    uint32_t tmp;
    uint8_t status;
    uint32_t ctrlRev;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Start host initializing... \n");
    pSdioHost->HostBusMode = (uint8_t)CSDD_BUS_MODE_SD;

    tmp = CPS_REG_READ(&pSdioHost->RegOffset->CRS.CRS63);
    pSdioHost->SpecVersNumb = (uint8_t)CRS63_GET_SPEC_VERSION(tmp);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Specification Version Number %d \n",
                (uint16_t)pSdioHost->SpecVersNumb );

    tmp = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS31);
    ctrlRev = CPS_FLD_READ(SD4HC__HRS__HRS31, HOSTCTRLVER, tmp);
    pSdioHost->cqSupported = true;
    pSdioHost->hs400EsSupported = true;
    if (ctrlRev > 0U){
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SD Host controller revision %x \n", ctrlRev);
#if SDIO_CFG_HOST_VER > 4
        pSdioHost->hostCtrlVer = HRS31_GET_MAJOR(ctrlRev);
        pSdioHost->HostFixVer = (uint8_t)CPS_FLD_READ(SD4HC__HRS__HRS31, HOSTFIXVER, tmp);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SD Host controller fix revision %x \n", pSdioHost->HostFixVer);
#else
        pSdioHost->hostCtrlVer = SDIO_CFG_HOST_VER;
#endif
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SD Host controller revision %x \n", pSdioHost->hostCtrlVer);
        tmp = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS30);
        if (CPS_FLD_READ(SD4HC__HRS__HRS30, CQSUP, tmp) == 0U) {
            pSdioHost->cqSupported = false;
        }

        if (CPS_FLD_READ(SD4HC__HRS__HRS30, HS400ESSUP, tmp) == 0U) {
            pSdioHost->hs400EsSupported = false;
        }
    }

    // reset controller
    status = ResetHost(pSdioHost);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

#if DEBOUNCING_TIME > 0xFFFFFF
#   error WRONG VALUE OF DEBOUNCING TIME IN CONFIG.H FILE
#endif
        CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS01, (uint32_t)DEBOUNCING_TIME);

        if ((pSdioHost->SpecVersNumb  < 4U) && (pSdioHost->dma64BitEn != 0U)) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "DMA 64 bit is not supported\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        } else {
            status = SDIOHost_HostInitSlots(pSdioHost);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------

static uint8_t ResponseToErrorSD(uint32_t Error)
{
    uint8_t result;

    switch (Error) {
    case SDCARD_RESP_R1_ILLEGAL_CMD_ERR:
        result = SDIO_ERR_ILLEGAL_CMD;
        break;
    case SDCARD_RESP_R1_COM_CRC_ERR:
        result = SDIO_ERR_COM_CRC_ERR;
        break;
    case SDCARD_RESP_R1_ERASE_SEQUENCE_ERR:
        result = SDIO_ERR_ERASE_SEQUENCE_ERR;
        break;
    case SDCARD_RESP_R1_ADDRESS_ERR:
        result = SDIO_ERR_ADDRESS_ERR;
        break;
    case SDCARD_RESP_R1_PARAM_ERR:
        result = SDIO_ERR_PARAM_ERR;
        break;
    default:
        result = SDIO_ERR_NO_ERROR;
        break;
    }

    return (result);
}

//------------------------------------------------------------------------------
#if SDIO_CFG_ENABLE_IO
static uint8_t ResponseToErrorSDIO(uint32_t Error)
{
    switch (Error) {
    case SDCARD_RESP_MOD_R1_ILLEGAL_CMD_ERR:
        return SDIO_ERR_ILLEGAL_CMD;
    case SDCARD_RESP_MOD_R1_COM_CRC_ERR:
        return SDIO_ERR_COM_CRC_ERR;
    case SDCARD_RESP_MOD_R1_FUN_NUMB_ERR:
        return SDIO_ERR_FUN_NUM_ERR;
    case SDCARD_RESP_MOD_R1_PARAM_ERR:
        return SDIO_ERR_PARAM_ERR;
    }

    return SDIO_ERR_NO_ERROR;
}
#endif
//------------------------------------------------------------------------------

static uint8_t ResponseToErrorR5(uint32_t Error)
{
    uint8_t result;

    switch(Error) {
    case SDCARD_R5_FLAGS_OUT_OF_RANGE_ERR:
        result = SDIO_ERR_PARAM_ERR;
        break;
    case SDCARD_R5_FLAGS_FUNC_NUMB_ERR:
        result = SDIO_ERR_FUN_NUM_ERR;
        break;
    case SDCARD_R5_FLAGS_GENERAL_ERR:
        result = SDIO_ERR_GENERAL;
        break;
    case SDCARD_R5_FLAGS_ILLEGAL_CMD_ERR:
        result = SDIO_ERR_ILLEGAL_CMD;
        break;
    case SDCARD_R5_FLAGS_COM_CRC_ERR:
        result = SDIO_ERR_COM_CRC_ERR;
        break;
    default:
        result = SDIO_ERR_NO_ERROR;
        break;
    }

    return (result);
}

//------------------------------------------------------------------------------

static uint8_t ResponseToErrorR6(uint32_t Error)
{
    uint8_t result;

    switch(Error) {
    case SDCARD_R6_STATUS_ERROR:
        result = SDIO_ERR_GENERAL;
        break;
    case SDCARD_R6_STATUS_ILLEGAL_COMMAND:
        result = SDIO_ERR_ILLEGAL_CMD;
        break;
    case SDCARD_R6_STATUS_COM_CRC_ERROR:
        result = SDIO_ERR_COM_CRC_ERR;
        break;
    default:
        result = SDIO_ERR_NO_ERROR;
        break;
    }

    return (result);
}

//------------------------------------------------------------------------------

static uint8_t ResponseToErrorR1(uint32_t Error)
{
    uint8_t result;

    switch(Error) {
    case CARD_STATUS_OUT_OF_RANGE:
        result = SDIO_ERR_OUT_OF_RANGE;
        break;
    case CARD_STATUS_ADDRESS_ERROR:
        result = SDIO_ERR_ADDRESS_ERR;
        break;
    case CARD_STATUS_BLOCK_LEN_ERROR:
        result = SDIO_ERR_BLOCK_LEN_ERROR;
        break;
    case CARD_STATUS_ERASE_SEQ_ERROR:
        result = SDIO_ERR_ERASE_SEQUENCE_ERR;
        break;
    case CARD_STATUS_ERASE_PARAM:
        result = SDIO_ERR_PARAM_ERR;
        break;
    case CARD_STATUS_WP_VIOLATION:
        result = SDIO_ERR_CARD_IS_LOCKED;
        break;
    case CARD_STATUS_LOCK_UNLOCK_FAILED:
        result = SDIO_ERR_LOCK_UNLOCK_FAILED;
        break;
    case CARD_STATUS_COM_CRC_ERROR:
        result = SDIO_ERR_COM_CRC_ERR;
        break;
    case CARD_STATUS_ILLEGAL_COMMAND:
        result = SDIO_ERR_ILLEGAL_CMD;
        break;
    case CARD_STATUS_CARD_ECC_FAILED:
        result = SDIO_ERR_CARD_ECC;
        break;
    case CARD_STATUS_CC_ERROR:
        result = SDIO_ERR_CC_ERROR;
        break;
    case CARD_STATUS_ERROR:
        result = SDIO_ERR_GENERAL;
        break;
    case CARD_STATUS_UNDERRUN:
        result = SDIO_ERR_UNDERRUN;
        break;
    case CARD_STATUS_OVERRUN:
        result = SDIO_ERR_OVERRUN;
        break;
    case CARD_STATUS_WP_ERASE_SKIP:
        result = SDIO_ERR_WP_ERASE_SKIP;
        break;
    case CARD_STATUS_SWITCH_ERROR:
        result = SDIO_ERR_SWITCH_ERROR;
        break;
    case CARD_SATUS_AKE_SEQ_ERROR:
        result = SDIO_ERR_AKE_SEQ_ERROR;
        break;
    default:
        result = SDIO_ERR_NO_ERROR;
        break;
    }

    return (result);
}

//------------------------------------------------------------------------------

uint8_t CheckResponseError(const uint32_t *Response, uint8_t ResponseType,
                           const CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t R1;
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;

    // check a response errors - SPI bus mode
    if (pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
        switch(ResponseType) {
        case (uint8_t)CSDD_RESPONSE_R4:
        case (uint8_t)CSDD_RESPONSE_R3:
        case (uint8_t)CSDD_RESPONSE_R7:
            R1 = Response[1];
            break;
        default:
            R1 = Response[0];
            break;
        }

        // SD memory card response error
        if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_SDMEM) {
            if ((R1 & SDCARD_RESP_R1_ALL_ERRORS) != 0U) {
                status = ResponseToErrorSD(R1 & SDCARD_RESP_R1_ALL_ERRORS);
            }
        } else {
#if SDIO_CFG_ENABLE_IO
            if (pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
                // SDIO card response error
                status = ResponseToErrorSDIO(R1 & SDCARD_RESP_R1_ALL_ERRORS);
            }
#endif
        }
    }
    // check a response errors - SD bus mode
    else {
        // in SD bus mode, only responses R5 and R6 have information about errors
        switch (ResponseType) {
        case (uint8_t)CSDD_RESPONSE_R5:
            status = ResponseToErrorR5(Response[0] & SDCARD_R5_FLAGS_ALL_ERROR);
            break;
        case (uint8_t)CSDD_RESPONSE_R6:
            status = ResponseToErrorR6(Response[0] & SDCARD_R6_STATUS_MASK);
            break;
        case (uint8_t)CSDD_RESPONSE_R1:
            status = ResponseToErrorR1(Response[0] & (uint32_t)CARD_STATUS_ALL_ERRORS_MASK);
            break;
        default:
            // SDIO_ERR_NO_ERROR
            break;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static void CalcRespSize(CSDD_Request* pRequest, const CSDD_SDIO_Slot* pSlot)
{
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;
    if (pSdioHost->HostBusMode != (uint8_t)CSDD_BUS_MODE_SPI) {
        // check how long in bytes is response field
        // and how many registers is needed to read
        switch (pRequest->pCmd->requestFlags.responseType) {
        case CSDD_RESPONSE_R2:
            pRequest->respSize = 16;
            break;
        case CSDD_RESPONSE_NO_RESP:
            pRequest->respSize = 0;
            break;
        default:
            pRequest->respSize = 4;
            break;
        }
    } else {
        pRequest->respSize = 4;
    }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t SDIOHost_FillResponseTab(CSDD_Request* pRequest, const CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t i;

    pRequest->responseTab[1] = 0;
    pRequest->responseTab[2] = 0;
    pRequest->responseTab[3] = 0;

    for (i = 0; i < (pRequest->respSize / 4U); i++) {
        volatile uint32_t* offset = &pRequest->respRegOffset[i];
        pRequest->responseTab[i]
            = CPS_REG_READ(offset);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "R[%d] = 0x%lX\n",
                    (uint16_t)i, pRequest->responseTab[i]);
    }

    if (pSlot->pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
        switch (pRequest->pCmd->requestFlags.responseType) {
        case CSDD_RESPONSE_R4:
        case CSDD_RESPONSE_R3:
        case CSDD_RESPONSE_R7:
        {
            volatile uint32_t* offset = &pRequest->respRegOffset[1U];
            pRequest->responseTab[1]
                = CPS_REG_READ(offset) & 0xFFU;
            break;
        }
        case CSDD_RESPONSE_R1:
        case CSDD_RESPONSE_R1B:
        case CSDD_RESPONSE_R5:
        case CSDD_RESPONSE_R2:
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER); // wrong response type
            status = SDIO_ERR_INVALID_PARAMETER;
            break;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static uint8_t SDIOHost_GetResponse(CSDD_Request* pRequest, CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pRequest->respSize != 0U) {
        status = SDIOHost_FillResponseTab(pRequest, pSlot);

        if (status == SDIO_ERR_NO_ERROR) {

            switch (pSlot->InterfaceType) {
            case (uint8_t)CSDD_INTERFACE_TYPE_SD:
                pRequest->response = &pRequest->responseTab[0];
                break;
            default:
                status = SDIO_ERR_UNITIALIZED;
                break;
            }

            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {
                // if RCA is not 0 it means that device is initialized
                // so and we can check response error after any commands
                if (pSlot->pDevice->RCA != 0U) {
                    status = CheckResponseError(pRequest->response,
                                                (uint8_t)pRequest->pCmd->requestFlags.responseType, pSlot);
                }
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void SDIOHost_SupplySDCLK(CSDD_SDIO_Slot* pSlot, uint8_t Enable)
{
    uint32_t Temp;

    Temp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS11);
    if (Enable != 0U) {
        Temp |= (uint32_t)SRS11_SD_CLOCK_ENABLE;
    } else {
        Temp &= ~(uint32_t)SRS11_SD_CLOCK_ENABLE;
    }
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS11, Temp);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
uint8_t SDIOHost_GetBaseClk(CSDD_SDIO_Slot* pSlot, uint32_t *frequencyKHz)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t temp;

    //read base clock frequency for SD clock in kilo herz
    temp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);
    *frequencyKHz = SRS16_GET_BASE_CLK_FREQ_MHZ(temp) * 1000U;

    // if (*frequencyKHz == 0U) {
#if !SYTEM_CLK_KHZ
        status = SDIO_ERR_BASE_CLK_IS_ZERO;
#else
        *frequencyKHz = SYTEM_CLK_KHZ;
#endif
    // }

    return (status);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static inline bool SDIOHost_IsMaxDivider(uint32_t FrequencyKHz, uint32_t BaseCLKkHz, uint32_t i)
{
    return (((BaseCLKkHz / i) < FrequencyKHz)
            || (((BaseCLKkHz / i) == FrequencyKHz) && ((BaseCLKkHz % i) == 0U)));
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static void CalclProgrammableClockMode(CSDD_SDIO_Slot* pSlot, uint32_t FrequencyKHz, uint32_t BaseCLKkHz,
                                       uint32_t* pSrs11Reg, uint32_t* pSetFreqKhz)
{
    uint32_t i;
    uint32_t Temp2 = 0, M = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);
    M = SRS17_GET_CLOCK_MULTIPLIER(M);
    for (i = 1; i < 1024U; i++) {
        if (((BaseCLKkHz * M) / i) <= FrequencyKHz) {
            break;
        }
    }
    if (i > 1U) {
        Temp2 = (i << 8);
        i--;
    }
    // Set SDCLK Frequency Select and Internal Clock Enable
    *pSrs11Reg |= (Temp2 & 0xFF00U) | ((Temp2 & 0x30000U) >> 10)
                  | (uint32_t)SRS11_INT_CLOCK_ENABLE;
    *pSrs11Reg |= (uint32_t)SRS11_CLOCK_GENERATOR_SELECT;
    *pSetFreqKhz = (BaseCLKkHz * M) / i;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static void CalcSrs11RegAndSetFreqKhz(CSDD_SDIO_Slot* pSlot, uint32_t FrequencyKHz, uint32_t BaseCLKkHz,
                                      uint32_t* pSrs11Reg, uint32_t* SetFrequencyKHz)
{
    uint32_t i = 0U;
    uint32_t setFreqKhz = 0U;
    // read current value of SRS11 register
    uint32_t Temp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS11);
    // clear old frequency base settings
    Temp &= ~(uint32_t)SRS11_SEL_FREQ_BASE_MASK;

    const uint32_t CRS63 = CPS_REG_READ(&pSlot->pSdioHost->RegOffset->CRS.CRS63);
    if (CRS63_GET_SPEC_VERSION(CRS63) < 2U) { // 8-bit Divider Clock Mode
        for (i = 1; i < 256U; i = 2U * i) {
            if (SDIOHost_IsMaxDivider(FrequencyKHz, BaseCLKkHz, i)) {
                break;
            }
        }
        // Set SDCLK Frequency Select and Internal Clock Enable
        Temp |= (uint32_t)(((i / 2UL) << 8) | SRS11_INT_CLOCK_ENABLE);

        setFreqKhz = BaseCLKkHz / i;
    }
    else {
        if (pSlot->ProgClockMode == 0U) { // 10-bit Divider Clock Mode
            uint32_t Temp2;
            for (i = 1; i < 2046U; i++) {
                if (SDIOHost_IsMaxDivider(FrequencyKHz, BaseCLKkHz, i))
                {
                    break;
                }
            }
            Temp2 = ((i / 2U) << 8);
            // Set SDCLK Frequency Select and Internal Clock Enable
            Temp |= (Temp2 & 0xFF00U) | ((Temp2 & 0x30000U) >> 10)
                    | (uint32_t)SRS11_INT_CLOCK_ENABLE;
            Temp &= ~(uint32_t)SRS11_CLOCK_GENERATOR_SELECT;
            setFreqKhz = BaseCLKkHz / i;
        }
        else { // Programmable Clock Mode
            CalclProgrammableClockMode(pSlot, FrequencyKHz, BaseCLKkHz, &Temp, &setFreqKhz);
        }
    }

    *pSrs11Reg = Temp;
    *SetFrequencyKHz = setFreqKhz;

    if (pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP) {
        if (pSlot->ProgClockMode == 0U){
            // i == 1 means that clock is not diveded sdclk == sdmclk
            bool extendedMode = (i != 1U);
            SDIO_CPhy_SetExtMode(pSlot->pSdioHost, extendedMode, extendedMode);
        }

        /* put PHY to reset */
        SDIO_CPhy_DLLReset(pSlot->pSdioHost, true);
    }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
uint8_t SDIOHost_ChangeSDCLK(CSDD_SDIO_Slot* pSlot, uint32_t *FrequencyKHz)
{
    uint32_t BaseCLKkHz;
    uint32_t Srs11;
    uint8_t status;
    uint32_t SetFrequencyKHz;

    // set SD clock off
    SDIOHost_SupplySDCLK(pSlot, 0);

    status = SDIOHost_GetBaseClk(pSlot, &BaseCLKkHz);

#if !SYTEM_CLK_KHZ
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else
#endif
    {
        CalcSrs11RegAndSetFreqKhz(pSlot, *FrequencyKHz, BaseCLKkHz, &Srs11, &SetFrequencyKHz);

        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS11, Srs11);

        // wait for clock stable is 1
        status = WaitForValue(&pSlot->RegOffset->SRS.SRS11,
                              (uint32_t)SRS11_INT_CLOCK_STABLE, 1, COMMANDS_TIMEOUT);
        if (status == SDIO_ERR_NO_ERROR) {
            // write to FrequencyKHz the real value of set frequency
            *FrequencyKHz = SetFrequencyKHz;
        }
    }

    return (status);
}

//------------------------------------------------------------------------------
static uint8_t SDIOHost_SetSDCLK(CSDD_SDIO_Slot* pSlot, uint32_t *FrequencyKHz)
{
    uint8_t status;

    status = SDIOHost_ChangeSDCLK(pSlot, FrequencyKHz);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        if(pSlot->pSdioHost->hostCtrlVer >= 6U) {
            status = SDIO_CPhy_DLLReset(pSlot->pSdioHost, false);
        }
        SDIOHost_SupplySDCLK(pSlot, 1);
    }
    return (status);
}
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SetPower(CSDD_SDIO_Slot* pSlot, uint32_t Voltage)
{
    uint32_t Temp, SRS16;
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ( pSlot == NULL ) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        // disable SD bus power
        Temp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);
        Temp &= ~SRS10_SD_BUS_POWER;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, Temp);

        //clear current voltage settings
        Temp &= ~SRS10_BUS_VOLTAGE_MASK;

        SRS16 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);

        // if Voltage == 0
        // disable bus power
        // power is disabled so do nothing, return no error

        if (Voltage != 0U) {
            switch (Voltage) {
            case SRS10_SET_3_3V_BUS_VOLTAGE:
                if ((SRS16 & SRS16_VOLTAGE_3_3V_SUPPORT) == 0U) {
                    status = SDIO_ERR_INVALID_PARAMETER;
                    break;
                }
                // set new voltage value
                Temp |= (SRS10_SET_3_3V_BUS_VOLTAGE | SRS10_SD_BUS_POWER);
                break;
            case SRS10_SET_3_0V_BUS_VOLTAGE:
                if ((SRS16 & SRS16_VOLTAGE_3_0V_SUPPORT) == 0U) {
                    status = SDIO_ERR_INVALID_PARAMETER;
                    break;
                }
                // set new voltage value
                Temp |= (SRS10_SET_3_0V_BUS_VOLTAGE | SRS10_SD_BUS_POWER);
                break;
            case SRS10_SET_1_8V_BUS_VOLTAGE:
                if ((SRS16 & SRS16_VOLTAGE_1_8V_SUPPORT) == 0U) {
                    status = SDIO_ERR_INVALID_PARAMETER;
                    break;
                }
                // set new voltage value
                Temp |= (SRS10_SET_1_8V_BUS_VOLTAGE | SRS10_SD_BUS_POWER);
                break;
            default:
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
                status = SDIO_ERR_INVALID_PARAMETER;
                break;
            }

            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s",
                             "Can't set given voltage. It is not supported by the host\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, Temp);

                CPS_DelayNs(POWER_UP_DELAY_US * 1000U);
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SetSlotBusWidth(CSDD_SDIO_Slot* pSlot, uint8_t BusType)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t SRS10 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);

    // set bus width in the host
    switch(BusType) {
    case (uint8_t)CSDD_BUS_WIDTH_1:
        SRS10 &= ~SRS10_DATA_WIDTH_4BIT;
        SRS10 &= ~SRS10_EXTENDED_DATA_TRANSFER_WIDTH;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, SRS10);
        break;
    case (uint8_t)CSDD_BUS_WIDTH_4:
        SRS10 |= SRS10_DATA_WIDTH_4BIT;
        SRS10 &= ~SRS10_EXTENDED_DATA_TRANSFER_WIDTH;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, SRS10);
        break;
    case (uint8_t)CSDD_BUS_WIDTH_8:
        SRS10 |= SRS10_EXTENDED_DATA_TRANSFER_WIDTH;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, SRS10);
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_SetBusWidthCheckPreconditions(const CSDD_SDIO_Slot* pSlot, uint8_t BusType)
{
    uint8_t status;

    // it is no possibility to change bus width in SPI mode
    if (pSlot->pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
        status = SDIO_ERR_CANT_EXECUTE;
    }
    // if bus mode is not supported by card return error
    else if ((pSlot->pDevice->SupportedBusWidths & BusType) == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Card doesn't support this bus type\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }
    else if ((BusType != (uint8_t)CSDD_BUS_WIDTH_1) && (BusType != (uint8_t)CSDD_BUS_WIDTH_4)
             && (BusType != (uint8_t)CSDD_BUS_WIDTH_8)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }
    else if ((pSlot->UhsiSelected != 0U) && (BusType == (uint8_t)CSDD_BUS_WIDTH_1)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "for UHS-I modes only 4-bits bus mode is supported\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }
    else
    {
        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_SetBusWidthSdMemCardOnly(CSDD_SDIO_Slot* pSlot, uint8_t BusType)
{
    CSDD_Request Request = {0};

    SDIO_REQ_INIT_ACMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_ACMD6, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                         .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

    if (BusType == (uint8_t)CSDD_BUS_WIDTH_1) {
        Request.pCmd->argument = 0; // 1 bit bus width
    } else {
        Request.pCmd->argument = 2; // 4 bit bus width
    }

    // set bus with in the card
    SDIOHost_ExecCardCommand(pSlot, &Request);

    SDIOHost_CheckBusy(Request.pSdioHost, &Request);

    return (Request.status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#if SDIO_CFG_ENABLE_IO
static uint8_t SDIOHost_SetBusWidthChange(CSDD_SDIO_Slot* pSlot, uint8_t BusType, uint32_t* pHostIntStat, uint8_t* pCardIntStat)
#else
static uint8_t SDIOHost_SetBusWidthChange(CSDD_SDIO_Slot* pSlot, uint8_t BusType, uint32_t* pHostIntStat)
#endif
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    // dissable host normal interrupts for masking  incorrect interrupts
    // that may occur while changing the bus width.
    *pHostIntStat = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS13);
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS13,
                 *pHostIntStat & ~(uint32_t)SRS13_CARD_INTERRUPT_STAT_EN);

    // if it is a combo or SDIO card then disable card interrupts
    if ((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) != 0U) {
#if SDIO_CFG_ENABLE_IO
        uint8_t tmp;
        // read status of the card interrupt register
        status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_READ, pCardIntStat,
                                     sizeof(*pCardIntStat), CSDD_CCCR_INT_ENABLE);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            return status;
        }

        // clear interrupt enable master bit
        if ((*pCardIntStat & 0xFEU) != 0U) {
            tmp = *pCardIntStat & 0xFEU;

            // disable all card interrupts
            status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_WRITE, &tmp,
                                         sizeof(tmp), CSDD_CCCR_INT_ENABLE);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                return status;
            }
        }

        // read bus interface control
        status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_READ, &tmp,
                                     sizeof(tmp), CSDD_CCCR_BUS_CONTROL);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            return status;

        }

        if (BusType == (uint8_t)CSDD_BUS_WIDTH_1) {
            tmp = (tmp & 0xFCU) | SDCARD_BIS_BUS_WIDTH_1BIT;
        }
        else {
            tmp = (tmp & 0xFCU) | SDCARD_BIS_BUS_WIDTH_4BIT;
        }

        // set bus width in the SDIO card
        status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_WRITE, &tmp,
                                     sizeof(tmp), CSDD_CCCR_BUS_CONTROL);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            return status;

        }
#endif
    }
    // SD memory card only
    else if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_SDMEM) {
        status = SDIOHost_SetBusWidthSdMemCardOnly(pSlot, BusType);
        // check status
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }
#if SDIO_CFG_ENABLE_MMC
    else if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
        status = ChangeDeviceMmcBusWidth(pSlot, BusType);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }
#endif
    else {
        // All 'if ... else if' constructs shall be terminated with an 'else' statement
        // (MISRA2012-RULE-15_7-3)
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessSetBusWidth(CSDD_SDIO_Slot* pSlot, uint8_t BusType)
{
    uint8_t status;
    uint32_t HostIntStat;
#if SDIO_CFG_ENABLE_IO
    uint8_t CardIntStat;
#endif

#if SDIO_CFG_ENABLE_IO
    status = SDIOHost_SetBusWidthChange(pSlot, BusType, &HostIntStat, &CardIntStat);
#else
    status = SDIOHost_SetBusWidthChange(pSlot, BusType, &HostIntStat);
#endif

    if (status == SDIO_ERR_NO_ERROR) {
        status = SetSlotBusWidth(pSlot, BusType);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

#if SDIO_CFG_ENABLE_IO
            if (pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
                // check if the interrupts was enabled before
                if ((CardIntStat & 0xFEU) != 0U) {
                    // resume card interrupts state
                    status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_WRITE,
                                                 &CardIntStat, sizeof(CardIntStat),
                                                 CSDD_CCCR_INT_ENABLE);
                }
            }

            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else

#endif
            {
                // restore host normal interrupts
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS13, HostIntStat);

                pSlot->BusWidth = BusType;
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_SetBusWidth(CSDD_SDIO_Slot* pSlot, uint8_t BusType)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    // check  if we need to realy change the bus width
    if (pSlot->BusWidth != BusType) {

        status = SDIOHost_SetBusWidthCheckPreconditions(pSlot, BusType);

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_ProcessSetBusWidth(pSlot, BusType);
        }
    } else {
        // All 'if ... else if' constructs shall be terminated with an 'else' statement
        // (MISRA2012-RULE-15_7-3)
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHOST_MatchVoltage(CSDD_SDIO_Slot* pSlot, uint32_t OCR,
                                     uint32_t *CardVoltage,
                                     uint32_t *ControllerVoltage)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    uint32_t cardVolt = 0;
    uint32_t controllerVolt = 0;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        /// host voltage capabilities
        uint32_t HostCapabilities = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);

        bool voltage33vSupported = ((HostCapabilities & SRS16_VOLTAGE_3_3V_SUPPORT) != 0U);
        bool voltage30vSupported = ((HostCapabilities & SRS16_VOLTAGE_3_0V_SUPPORT) != 0U);

        uint32_t set33Volatage = SRS10_SET_3_3V_BUS_VOLTAGE;
        uint32_t set30Volatage = SRS10_SET_3_0V_BUS_VOLTAGE;

        // check the voltage capabilities of the SDIO host controller and a card
        // to set appropriate voltage
        if (voltage33vSupported && ((OCR & SDCARD_REG_OCR_3_3_3_4) != 0U)) {
            cardVolt = (uint32_t)SDCARD_REG_OCR_3_3_3_4;
            controllerVolt = set33Volatage;
        } else if (voltage33vSupported && ((OCR & SDCARD_REG_OCR_3_2_3_3) != 0U)) {
            cardVolt = (uint32_t)SDCARD_REG_OCR_3_2_3_3;
            controllerVolt = set33Volatage;
        } else if (voltage30vSupported && ((OCR & SDCARD_REG_OCR_3_0_3_1) != 0U)) {
            cardVolt = (uint32_t)SDCARD_REG_OCR_3_0_3_1;
            controllerVolt = set30Volatage;
        } else if (voltage30vSupported && ((OCR & SDCARD_REG_OCR_2_9_3_0) != 0U)) {
            cardVolt = (uint32_t)SDCARD_REG_OCR_2_9_3_0;
            controllerVolt = set30Volatage;
        } else {
            // All 'if ... else if' constructs shall be terminated with an 'else' statement
            // (MISRA2012-RULE-15_7-3)
        }
    }

    *CardVoltage = cardVolt;
    *ControllerVoltage = controllerVolt;

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_MMC
static uint8_t SDIOHost_MmcDeviceIdentification(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t status;
    CSDD_SDIO_Host *pSdioHost = pSlot->pSdioHost;
    CSDD_SDIO_Device* pDevice = pSlot->pDevice;

    status = SDIOHost_ResetCard(pSlot);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Reset card failed\n");
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        if (pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
            SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD1, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
        } else {
            SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD1, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                .respType = CSDD_RESPONSE_R3, .hwRespCheck = 0}));
        }

        // execute CMD1 command
        SDIOHost_ExecCardCommand(pSlot, pRequest);

        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
        switch (pRequest->status) {
        case SDIO_ERR_COMMAND_TIMEOUT_ERROR:
            // it is not MMC card
            break;
        case SDIO_ERR_NO_ERROR:
            pDevice->deviceType = (uint8_t)CSDD_CARD_TYPE_MMC;
            pSlot->AccessMode = (uint8_t)CSDD_ACCESS_MODE_MMC_LEGACY;
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", pRequest->status);
            status = pRequest->status;
            break;
        }
    }

    return (status);
}
#endif

//-----------------------------------------------------------------------------
static void SDIOHost_CheckdeviceTypePrepareRequest(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    DataSet(pRequest, 0, (uint32_t)sizeof(*pRequest));
    SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD8, .arg = (uint32_t)(1UL << 8), .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R7, .hwRespCheck = 0}));

    SDIOHost_ExecCardCommand(pSlot, pRequest);

    SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);

    SDIO_REQ_INIT_ACMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_ACMD41, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                         .respType = CSDD_RESPONSE_R3, .hwRespCheck = 0}));

    if (pSlot->pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
        pRequest->pCmd->requestFlags.responseType = CSDD_RESPONSE_R1;
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_CheckdeviceTypeCheckResponse(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_Device* pDevice, CSDD_Request* pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    do {
        // if no response on ACMD41 command then check
        // CMD1 command response
        if (pRequest->status == SDIO_ERR_COMMAND_TIMEOUT_ERROR) {
#if SDIO_CFG_ENABLE_MMC
            status = SDIOHost_MmcDeviceIdentification(pSlot, pRequest);
            if ((status != SDIO_ERR_NO_ERROR) || (pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC)) {
                break;
            }
#endif
        } else if (pRequest->status == SDIO_ERR_NO_ERROR) {
            pDevice->deviceType = (uint8_t)CSDD_CARD_TYPE_SDMEM;
        } else {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", pRequest->status);
            status = pRequest->status;
        }

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_ResetCard(pSlot);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Reset card failed\n");
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {
#if SDIO_CFG_ENABLE_IO
                SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD5, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                    .respType = CSDD_RESPONSE_R4, .hwRespCheck = 0}));
                SDIOHost_ExecCardCommand(pSlot, pRequest);

                SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
                switch (pRequest->status) {
                case SDIO_ERR_COMMAND_TIMEOUT_ERROR:
                    break;
                case SDIO_ERR_NO_ERROR:
                    // it can be a SDIO device or combo device
                    pDevice->deviceType |= (uint8_t)CSDD_CARD_TYPE_SDIO;
                    break;
                default:
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", pRequest->status);
                    return pRequest->status;
                }
#endif
            }
        }
    } while(0);

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_CheckdeviceType(CSDD_SDIO_Slot* pSlot)
{
    CSDD_Request Request = {0};
    uint8_t status;
    CSDD_SDIO_Device* pDevice = pSlot->pDevice;
    pDevice->deviceType = (uint8_t)CSDD_CARD_TYPE_NONE;
#ifdef CONFIG_COMPILE_RTL
    if ((uintptr_t)pSlot->RegOffset == (uintptr_t)ITCS_C_EMMC0_BASE) {
        Request.status = SDIO_ERR_COMMAND_TIMEOUT_ERROR;
    } else
#endif
    {
        SDIOHost_CheckdeviceTypePrepareRequest(pSlot, &Request);
        // execute ACMD41 command
        SDIOHost_ExecCardCommand(pSlot, &Request);
        // check status
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);
    }

    status = SDIOHost_CheckdeviceTypeCheckResponse(pSlot, pDevice, &Request);
    if (pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_NONE) {
        status = SDIO_ERR_UNUSABLE_CARD;
    } else if (status == SDIO_ERR_NO_ERROR) {
        pDevice->pSlot = pSlot;
        pDevice->IsSelected = 0;
        pDevice->RCA = 0;
        pSlot->BusWidth = 1;
        status = SDIOHost_ResetCard(pSlot);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Reset card failed\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    } else {
        // All 'if ... else if' constructs shall be terminated with an 'else' statement
        // (MISRA2012-RULE-15_7-3)
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_CmdDatLineErrorRecovery(CSDD_SDIO_Slot* pSlot, uint32_t IntStatus)
{
    uint8_t Error = SDIO_ERR_NO_ERROR;

    // CMD Line error occurs
    if ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12)
         & (SRS12_COMMAND_TIMEOUT_ERROR | SRS12_COMMAND_CRC_ERROR
            | SRS12_COMMAND_END_BIT_ERROR | SRS12_COMMAND_INDEX_ERROR | SRS12_RESPONSE_ERROR)) != 0U) {
        // reset CMD line
        Error = ResetLines(pSlot, 1, 0);
        if (Error != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error - Can't reset CMD Line\n");
            // restore interrupt settings
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
        }
    }

    if (Error == SDIO_ERR_NO_ERROR) {
        // DAT Line error occurs
        if (((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12)
              & (SRS12_DATA_END_BIT_ERROR | SRS12_DATA_CRC_ERROR
                 | SRS12_DATA_TIMEOUT_ERROR)) != 0U)
            || ((pSlot->pCurrentRequest != NULL) && (pSlot->pCurrentRequest->pCmd->requestFlags.dataPresent != 0U))) {

            // reset DAT line
            Error = ResetLines(pSlot, 0, 1);
            if (Error != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error - Can't reset DAT Line\n");
                // restore interrupt settings
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
            }
        }
    }

    return (Error);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_FinishErrorInterruptRecovery(CSDD_SDIO_Slot* pSlot, uint32_t IntStatus)
{
    // reset command and data line
    uint8_t Error = ResetLines(pSlot, 1, 1);

    if (Error != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error - Can't reset CMD and DAT Line\n");
    } else {

        // wait for more than 40us
        CPS_DelayNs(45000U);

        // check DAT Line
        if ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09) &
             (SRS9_DAT0_SIGNAL_LEVEL | SRS9_DAT1_SIGNAL_LEVEL
              | SRS9_DAT2_SIGNAL_LEVEL | SRS9_DAT3_SIGNAL_LEVEL)) == 0U) {
            Error = SDIO_ERR_NON_RECOVERABLE_ERROR;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Unrecoverable Error\n");
        }

        // restore interrupt signal settings
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
    }

    return (Error);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_CalcPcmd(CSDD_SDIO_Slot* pSlot, uint32_t SRS15, uint32_t IntStatus,
                                 uint8_t* PCMD)
{
    uint8_t Error = SDIO_ERR_NO_ERROR;
    uint8_t localPcmd;

    if ((SRS15 & SRS15_AUTO_CMD12_NOT_EXECUTED) != 0U) {
        localPcmd = 1;
    } else {
        localPcmd = 0;

        // reset CMD line
        Error = ResetLines(pSlot, 1, 0);
        if (Error != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error - Can't reset CMD Line\n");
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
        }
    }

    if (Error == SDIO_ERR_NO_ERROR) {
        *PCMD = localPcmd;
    }

    return (Error);
}

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_FinishAutoCmd12ErrorRecovery(CSDD_SDIO_Slot* pSlot, uint32_t SRS15, uint32_t IntStatus,
                                                     uint8_t requestStatus, uint8_t PCMD)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    switch (requestStatus) {
    // Unrecoverable Error
    case SDIO_ERR_COMMAND_CRC_ERROR:
    case SDIO_ERR_COMMAND_END_BIT_ERROR:
    case SDIO_ERR_COMMAND_TIMEOUT_ERROR:
    case SDIO_ERR_CMD_LINE_CONFLICT:
    case SDIO_ERR_COMMAND_INDEX_ERROR:
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Unreconverable Error\n");
        (void)ResetLines(pSlot, 1, 1);
        status = SDIO_ERR_NON_RECOVERABLE_ERROR;
        break;
    // No error
    case SDIO_ERR_NO_ERROR:
        if (PCMD == 1U) {
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
            (void)ResetLines(pSlot, 1, 1);
            status = SDIO_ERR_ACMD12_RECOVERABLE_A;
        }
        break;
    default:
        //
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {

        if (PCMD == 1U) {
            status = SDIO_ERR_ACMD12_RECOVERABLE_B;
        } else {
            if ((SRS15 & SRS15_CMD_NOT_ISSUED_ERR) != 0U) {
                status = SDIO_ERR_ACMD12_RECOVERABLE_D;
            } else {
                status = SDIO_ERR_ACMD12_RECOVERABLE_C;
            }
        }

        // reset command and data line
        uint8_t Error = ResetLines(pSlot, 1, 1);

        if (Error != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error - Can't reset CMD and DAT Line\n");
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
            status = Error;
        } else {
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, IntStatus);
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status); // B or C or D
        }
    }

    return (status);
}

//-----------------------------------------------------------------------------

static void SDIOHost_CheckRequestOnRecovery(CSDD_SDIO_Slot* pSlot, const CSDD_Request* pRequest)
{
    while (pRequest->status == SDIO_STATUS_PENDING) {
        uint32_t regStatus = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
        // clear occurred normal status interrupts
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, regStatus
                     & SRS12_NORMAL_STAUS_MASK);
        SDIOHost_CheckInterruptOnRecovery(pSlot, regStatus);
    }
}

static void SDIOHost_ErrorRecoveryExecuteCmd12(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint8_t doResetLines)
{
    SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD12, .arg = 0, .cmdType = CSDD_CMD_TYPE_ABORT,
                                                        .respType = CSDD_RESPONSE_R1B, .hwRespCheck = 0}));

    if (doResetLines != 0U) {
        (void)ResetLines(pSlot, 1, 0);
    }

    // execute CMD12 command to abort command
    SDIOHost_ExecCardCmdFiniteNonAppNoTuning(pSlot, pRequest);
}
//-----------------------------------------------------------------------------

static
uint8_t SDIOHost_ErrorRecovery(CSDD_SDIO_Slot* pSlot, uint32_t SRS12, uint32_t SRS15)
{
    uint8_t Error = SDIO_ERR_NO_ERROR;

    uint32_t IntStatus, tmp;
    CSDD_Request Request, *pAbortingRequest;

    IntStatus = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS14);
    // disable all errors interrupt signal, and command complete interrupt signal
    tmp = IntStatus & (uint32_t)(~(SRS14_COMMAND_COMPLETE_SIG_EN
                                   | SRS14_TRANSFER_COMPLETE_SIG_EN
                                   | SRS14_COMMAND_TIMEOUT_ERR_SIG_EN
                                   | SRS14_COMMAND_CRC_ERR_SIG_EN
                                   | SRS14_COMMAND_END_BIT_ERR_SIG_EN
                                   | SRS14_COMMAND_INDEX_ERR_SIG_EN
                                   | SRS14_DATA_TIMEOUT_ERR_SIG_EN
                                   | SRS14_DATA_CRC_ERR_SIG_EN
                                   | SRS14_DATA_END_BIT_ERR_SIG_EN
                                   | SRS14_CURRENT_LIMIT_ERR_SIG_EN
                                   | SRS14_AUTO_CMD12_ERR_SIG_EN));
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, tmp);

    if ((SRS12 & SRS12_AUTO_CMD_ERROR) == 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Attempt Error Interrupt Recovery\n");

        Error = SDIOHost_CmdDatLineErrorRecovery(pSlot, IntStatus);

        if(Error == SDIO_ERR_NO_ERROR) {

            // save pointer of current request
            pAbortingRequest = pSlot->pCurrentRequest;

            //clear error interrupt
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12);

            SDIOHost_ErrorRecoveryExecuteCmd12(pSlot, &Request, 0);

            // interrupts are disabled on the begin of this function
            // so we have to check status register here because it will not be
            // checked neither in SDIOHost_ExecCardCommand function
            // nor SDIOHost_CheckInterrupt function
            SDIOHost_CheckRequestOnRecovery(pSlot, &Request);

            // restore pointer to the request
            pSlot->pCurrentRequest = pAbortingRequest;

            Error = SDIOHost_FinishErrorInterruptRecovery(pSlot, IntStatus);
        }

    } // Error Interrupt Recovery
    else {
        uint8_t PCMD;

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Attempt Auto CMD12 Error Recovery\n");

        Error = SDIOHost_CalcPcmd(pSlot, SRS15, IntStatus, &PCMD);

        if (Error == SDIO_ERR_NO_ERROR) {

            SDIOHost_ErrorRecoveryExecuteCmd12(pSlot, &Request, 1);

            SDIOHost_CheckRequestOnRecovery(pSlot, &Request);

            Error = SDIOHost_FinishAutoCmd12ErrorRecovery(pSlot, SRS15, IntStatus,
                                                          Request.status, PCMD);
        }
    } // AUTO CMD12 Error Recovery

    return (Error);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static inline bool SDIOHost_IsSdmemOrMmc(uint8_t deviceType) {
    return (deviceType == (uint8_t)CSDD_CARD_TYPE_SDMEM)
           || (deviceType == (uint8_t)CSDD_CARD_TYPE_MMC);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_LookingForDriverFinalize(const CSDD_DeviceInfo *DevInfo, const LIST_NODE *Iterator, CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;

    if (DevInfo == NULL) {
        status = SDIO_ERR_DRIVER_NOT_IMPLEMENTED;
    } else if ((Iterator == NULL) || (DevInfo->pCardInitialize == NULL)) {
        status = SDIO_ERR_DRIVER_NOT_IMPLEMENTED;
    } else {
        status = DevInfo->pCardInitialize(pSlot->pSdioHost, pSlot->SlotNr);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_AssignDeviceInfoToDevice(const CSDD_DeviceInfo *DevInfo, CSDD_SDIO_Device* pDevice)
{
    pDevice->pCardInterruptHandler = DevInfo->pCardInterruptHandler;
    pDevice->pCardDeinitialize = DevInfo->pCardDeinitialize;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_LookingForDriver(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;
    CSDD_SDIO_Device* pDevice = pSlot->pDevice;
    CSDD_DeviceInfo *DevInfo = NULL;

    if (SuppDevList->Next == NULL) {
        status = SDIO_ERR_DRIVER_NOT_IMPLEMENTED;
    } else {

        LIST_NODE* Iterator = SuppDevList->Next;

        // Check if drivers implemented

        // For SDIO devices or combo devices read the CIS register
        if ((pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) != 0U) {
#if SDIO_CFG_ENABLE_IO
            uint16_t ManufacturerCode, ManufacturerInformation;
            uint8_t Buffer[4];

            /// Get CIS pointer
            status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_READ,
                                         &pDevice->CommonCISAddress,
                                         sizeof(pDevice->CommonCISAddress),
                                         CSDD_CCCR_CIS_POINTER);
            if (status) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                return status;
            }

            // Get manufacturer ID and manufacturer informations
            SDIOHost_GetTupleFromCIS(pSlot, pDevice->CommonCISAddress,
                                     CSDD_TUPLE_CISTPL_MANFID, Buffer, sizeof(Buffer));

            ManufacturerCode = Buffer[0] | ((uint16_t)Buffer[1] << 8);
            ManufacturerInformation = Buffer[2] | ((uint16_t)Buffer[3] << 8);

            // search device
            while(Iterator != NULL) {
                DevInfo = Iterator->Item;
                if ((DevInfo->manufacturerCode == ManufacturerCode)
                    && (DevInfo->manufacturerInformation
                        == ManufacturerInformation)) {
                    SDIOHost_AssignDeviceInfoToDevice(DevInfo, pDevice);
                    break;
                }
                Iterator = Iterator->Next;
            }
#endif
        } else if (SDIOHost_IsSdmemOrMmc(pDevice->deviceType)) {

            while(Iterator != NULL) {
                DevInfo = Iterator->Item;
                if (SDIOHost_IsSdmemOrMmc(DevInfo->deviceType)) {
                    SDIOHost_AssignDeviceInfoToDevice(DevInfo, pDevice);
                    break;
                }
                Iterator = Iterator->Next;
            }
        } else {
            // All 'if ... else if' constructs shall be terminated with an 'else' statement
            // (MISRA2012-RULE-15_7-3)
        }

        status = SDIOHost_LookingForDriverFinalize(DevInfo, Iterator, pSlot);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint32_t CalcDataToCopy(const CSDD_Request* pRequest)
{
    uint32_t ToCopy;

    if (pRequest->dataRemaining < (pRequest->pCmd->blockLen) ){
        ToCopy = pRequest->dataRemaining;
    } else {
        ToCopy = pRequest->pCmd->blockLen;
    }

    return (ToCopy);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void ProcessTransferDataBufferRead(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint32_t ToCopy = CalcDataToCopy(pRequest);

    pRequest->dataRemaining -= ToCopy;

    while(ToCopy > 0U) {
#if CHANGE_DATA_ENDIANITY_NODMA
        pRequest->pBufferPos = &((uint32_t*)pRequest->pBufferPos)[1];
        ToCopy -= 4U;
        ((uint32_t*)pRequest->pBufferPos)[-1]
            = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS08);
#else
        uint32_t data = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS08);
        uint8_t byte_count = 4;
        while(ToCopy && byte_count) {
            *((uint8_t*)pRequest->pBufferPos) = data & 0xFF;
            data >>= 8;
            byte_count--;
            ToCopy--;
            pRequest->pBufferPos = (uint8_t*)pRequest->pBufferPos + 1;
        }
#endif
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void ProcessTransferDataBufferWrite(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint32_t ToCopy = CalcDataToCopy(pRequest);

    pRequest->dataRemaining -= ToCopy;

    while(ToCopy > 0U) {
#if CHANGE_DATA_ENDIANITY_NODMA
        pRequest->pBufferPos = &((uint32_t*)pRequest->pBufferPos)[1];
        ToCopy -= 4U;
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS08,
                     ((uint32_t*)pRequest->pBufferPos)[-1]);
#else
        uint32_t Data = 0;
        uint8_t ByteCount = 0;
        while(ToCopy && (ByteCount < 4)) {
            Data |= (uint32_t)*((uint8_t*)pRequest->pBufferPos) << (8 * ByteCount);
            ByteCount++;
            ToCopy--;
            pRequest->pBufferPos = (uint8_t*)pRequest->pBufferPos + 1;
        }
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS08, CPUToLE32(Data));
#endif
    }

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void TransferDataBuffer(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    if (pRequest == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error! pRequest is null\n");
    } else if ((pRequest->dataRemaining & 3U) != 0U) {
        pRequest->status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        if (pRequest->pCmd->requestFlags.dataTransferDirection == CSDD_TRANSFER_READ) {
            ProcessTransferDataBufferRead(pSlot, pRequest);
        }
        else {
            ProcessTransferDataBufferWrite(pSlot, pRequest);
        }
    }
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_IO
//-----------------------------------------------------------------------------
static uint8_t GetIoCardOCR(CSDD_SDIO_Slot* pSlot, uint32_t *OCR)
{
    CSDD_Request Request;
    *OCR = 0;

    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD5, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R4, .hwRespCheck = 0}));

    // execute CMD5 command to check a card OCR register
    SDIOHost_ExecCardCommand(pSlot, &Request);
    SDIOHost_CheckBusy(Request.pSdioHost, &Request);

    if (Request.status != SDIO_ERR_COMMAND_TIMEOUT_ERROR) {
        // OCR is valid and number of I/O functions are more than 1
        if ((Request.status == SDIO_ERR_NO_ERROR)
            && (((Request.response[0] >> 28) & 0x7U) != 0U)) {

            *OCR = Request.response[0];
        }
    }
    return SDIO_ERR_NO_ERROR;
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
static uint8_t GetMemCardOCR(CSDD_SDIO_Slot* pSlot, uint32_t *OCR)
{
    CSDD_Request Request = {0};
    CSDD_SDIO_Host *pSdioHost = pSlot->pSdioHost;
    *OCR = 0;

    if (((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U)
        || (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC)) {

        // prepare request
        if ((pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI)
            || (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC)) {

            uint8_t command = (pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) ? SDIO_CMD58 : SDIO_CMD1;

            SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = command, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                .respType = CSDD_RESPONSE_R3, .hwRespCheck = 0}));
        } else {
            SDIO_REQ_INIT_ACMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_ACMD41, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                 .respType = CSDD_RESPONSE_R3, .hwRespCheck = 0}));
        }

        // execute command to check a card OCR register
        SDIOHost_ExecCardCommand(pSlot, &Request);

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);
        if ((Request.status == SDIO_ERR_NO_ERROR) && (Request.response != NULL)) {
            *OCR = Request.response[0];
        }
    }
    return SDIO_ERR_NO_ERROR;
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_IO
//-----------------------------------------------------------------------------
static uint8_t SetIoCardVoltage(CSDD_SDIO_Slot* pSlot, uint32_t Voltage, uint8_t S18R,
                                uint8_t *S18A)
{
    CSDD_Request Request;

    // get OCR register from SDIO or combo card
    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD5, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R4, .hwRespCheck = 0}));
    *S18A = 0;

    // execute CMD5 command to check a card OCR register
    SDIOHost_ExecCardCommand(pSlot, &Request);

    SDIOHost_CheckBusy(Request.pSdioHost, &Request);
    if (Request.status != SDIO_ERR_COMMAND_TIMEOUT_ERROR) {
        volatile uint32_t Delay;
        // OCR is valid and number of I/O functions are more than 1
        if ((Request.status == SDIO_ERR_NO_ERROR)
            && ((Request.response[0] >> 28) & 0x7U)) {
            Request.argument = Voltage;
            if (S18R) {
                Request.argument |= SDCARD_REG_OCR_S18R;
            }

            Delay = 10000U;

            do {
                // execute CMD5 command with setting the supply voltage as argument
                SDIOHost_ExecCardCommand(pSlot, &Request);

                SDIOHost_CheckBusy(Request.pSdioHost, &Request);
                // if no response from card it is unusable return error code
                if (Request.status != SDIO_ERR_NO_ERROR) {
                    Delay = 0;
                }
                // wait until card will be ready
            } while (((Request.response[0] & SDCARD_R4_CARD_READY) == 0U) && (--Delay));

            if (Delay == 0) {
                return SDIO_ERR_UNUSABLE_CARD;
            }
        }
    }

    if ((Request.response[0] & SDCARD_REG_OCR_S18A) != 0U) {
        *S18A = 1;
    }
    return SDIO_ERR_NO_ERROR;
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
static uint32_t SetMemCardVoltageCalcArgument(uint32_t Voltage, uint8_t F8, uint8_t S18R, uint8_t XPC)
{
    uint32_t argument = Voltage;
    // if card sent response on CMD8 command
    // set host high capacity flag to 1
    if (F8 != 0U) {
        argument |= (uint32_t)SDCARD_ACMD41_HCS;
    }

    if (S18R != 0U) {
        argument |= (uint32_t)SDCARD_REG_OCR_S18R;
    }

    if (XPC != 0U) {
        argument |= (uint32_t)SDCARD_REG_OCR_XPC;
    }

    return (argument);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SetMemCardVoltageWaitForCard(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    bool cardReady;
    uint32_t Delay = 10000U;
    do {
        // execute ACMD41 or CMD1 command with setting the supply voltage as argument
        SDIOHost_ExecCardCommand(pSlot, pRequest);
        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);

        if (pRequest->status != SDIO_ERR_NO_ERROR) {
            status  = SDIO_ERR_UNUSABLE_CARD;
            break;
        }

        cardReady = ((pRequest->response[0] & SDCARD_REG_OCR_READY) != 0U);
        Delay -= 1U;
        // if no response from card it is unusable return error code
    } while ((!cardReady) && (Delay != 0U)); // wait until card will be ready

    if ((Delay == 0U) && (status == SDIO_ERR_NO_ERROR)) { // card is busy to much time
        status = SDIO_ERR_UNUSABLE_CARD;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SetMemCardVoltageSetCCS(const CSDD_SDIO_Slot* pSlot, const CSDD_Request* pRequest, uint8_t *CCS)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U) {
        // check CCS card flag
        if ((pRequest->response[0] & SDCARD_REG_OCR_CCS) != 0U) {
            *CCS = 1;
        } else {
            *CCS = 0;
        }
    }
#if SDIO_CFG_ENABLE_MMC
    else if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
        if ((pRequest->response[0] & MMC_REG_OCR_SECTOR_MODE) != 0U) {
            *CCS = 1;
        } else {
            *CCS = 0;
        }
    }
#endif
    else {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SetMemCardVoltage(CSDD_SDIO_Slot* pSlot, uint32_t Voltage, uint8_t F8,
                                 uint8_t *CCS, uint8_t S18R, uint8_t XPC, uint8_t *S18A)
{
    CSDD_Request Request = {0};

    *S18A = 0;

    if ((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U) {

        uint32_t argument = SetMemCardVoltageCalcArgument(Voltage, F8, S18R, XPC);

        SDIO_REQ_INIT_ACMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_ACMD41, .arg = argument, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                             .respType = CSDD_RESPONSE_R3, .hwRespCheck = 0}));
    }
#if SDIO_CFG_ENABLE_MMC
    else { // MMC card
        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD1, .arg = Voltage, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                            .respType = CSDD_RESPONSE_R3, .hwRespCheck = 0}));
        Request.pCmd->argument |= (uint32_t)MMC_REG_OCR_SECTOR_MODE;
    }
#endif

    uint8_t status = SetMemCardVoltageWaitForCard(pSlot, &Request);

    if (status == SDIO_ERR_NO_ERROR) {

        status = SetMemCardVoltageSetCCS(pSlot, &Request, CCS);

        if (status == SDIO_ERR_NO_ERROR) {
            if ((Request.response[0] & SDCARD_REG_OCR_S18A) != 0U) {
                *S18A = 1;
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_AddItem(LIST_NODE *ListHead, CSDD_DeviceInfo* Item)
{
    uint8_t status;

    if (ListHead == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (Item == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        LIST_NODE* Iterator = ListHead;

        while(Iterator->Next != NULL) {
            Iterator = Iterator->Next;
        }

        //Iterator->Next = malloc(sizeof(LIST_NODE))
        Iterator->Next = GetNewListNode(ListHead);

        if (Iterator->Next == NULL) {
            status = SDIO_ERR_MEM_ALLOC;
        } else {

            Iterator->Next->Item = Item;
            Iterator->Next->Next = NULL;

            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_RemoveItemPrecond(const LIST_NODE *ListHead, const CSDD_DeviceInfo* Item)
{
    uint8_t status;
    if ((ListHead == NULL) || (Item == NULL)) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (ListHead->Next == NULL) {
        // list is empty, can't remove anything
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_RemoveItem(LIST_NODE *ListHead, const CSDD_DeviceInfo* Item)
{
    uint8_t status = SDIOHost_RemoveItemPrecond(ListHead, Item);

    if (status == SDIO_ERR_NO_ERROR) {

        LIST_NODE* Iterator = ListHead;
        LIST_NODE *Previous = NULL;

        // find element to remove to change pointers values
        while(Iterator->Next != NULL) {
            Previous = Iterator;
            Iterator = Iterator->Next;
            if (Iterator->Item == Item) {
                break;
            }
        }

        // given pointer to node to remove is not exists on the list
        if (Iterator->Item != Item) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        } else if (Previous != NULL) {
            Previous->Next = Iterator->Next;
            //free(Iterator)
            RemoveListNode(Iterator);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
CSDD_SDIO_Device* SDIOHost_GetDeviceFromSlot(CSDD_SDIO_Host* pSdioHost, uint8_t SlotNumber)
{
    CSDD_SDIO_Device* result;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SlotNumber = %d\n", SlotNumber);
    if (SlotNumber > pSdioHost->NumberOfSlots) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "Given slot number is %d but max slot number is %d\n",
                     SlotNumber, pSdioHost->NumberOfSlots);
        result = NULL;
    } else {
        result = &pSdioHost->Slots[SlotNumber].Devices[0];
    }

    return (result);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_CheckSlotsCardInserted(CSDD_SDIO_Slot* pSlot, uint8_t initStatus, uint8_t i)
{
    uint8_t status = initStatus;
    uint8_t localStatus;
    // if card is inserted to SD socked but it is unattached
    // attach the card
    if (((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09)
          & SRS9_CARD_INSERTED) != 0U) && (pSlot->CardInserted == 0U)) {
        // attach new
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Card is inserted in slot %d\n", i);
        localStatus = SDIOHost_DeviceAttach(pSlot);
        if (localStatus != SDIO_ERR_NO_ERROR) {
            status = localStatus;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error during device attach slot %d\n", i);
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    } else if (((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09)
                 & SRS9_CARD_INSERTED) == 0U) && (pSlot->CardInserted == 1U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "There is no card in slot %d\n", i);

        localStatus = SDIOHost_DeviceDetach(pSlot);

        if (localStatus != SDIO_ERR_NO_ERROR) {
            status = localStatus;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Device detach failed. Error %d\n", status);
        }
    } else {
        // All 'if ... else if' constructs shall be terminated with an 'else' statement
        // (MISRA2012-RULE-15_7-3)
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_CheckSlots(CSDD_SDIO_Host* pSdioHost)
{
    uint8_t i;
    uint8_t status = SDIO_ERR_NO_ERROR;
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "...\n");
    for (i = 0; i < pSdioHost->NumberOfSlots; i++) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[i];
        uint8_t localStatus = WaitForValue(&pSlot->RegOffset->SRS.SRS09,
                                           SRS9_CARD_STATE_STABLE, 1, COMMANDS_TIMEOUT);
        if (localStatus != SDIO_ERR_NO_ERROR) {
            // if card stable is not set it means that something is wrong
            vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                        "Warning - card state is unstable in slot %d\n", i);
            if (pSlot->CardInserted == 1U) {
                localStatus = SDIOHost_DeviceDetach(pSlot);
                if (localStatus != SDIO_ERR_NO_ERROR) {
                    status = localStatus;
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Device detach failed. Error %d\n", status);
                    break;
                }
            }
            continue;
        }
        status = SDIOHost_CheckSlotsCardInserted(pSlot, status, i);
    }

    return (status);
}
//-----------------------------------------------------------------------------

static uint8_t SDIOHost_CalcIntToClear(uint32_t SRS12, uint32_t SRS15, uint32_t* IntToClear)
{
    uint8_t Error = SDIO_ERR_UNDEFINED;

    uint32_t localIntToClear = SRS12_ERROR_INTERRUPT;

    if ((SRS12 & SRS12_AUTO_CMD_ERROR) != 0U) {
        if ((SRS15 & SRS15_CMD_NOT_ISSUED_ERR) != 0U) {
            Error = SIO_ERR_AUTOCMD12_NOT_ISSUED;
        }
        else if ((SRS15 & SRS15_AUTO_CMD12_INDEX_ERR) != 0U) {
            Error = SIO_ERR_AUTOCMD12_INDEX_ERROR;
        }
        else if ((SRS15 & SRS15_AUTO_CMD12_END_BIT_ERR) != 0U) {
            Error = SIO_ERR_AUTOCMD12_END_BIT_ERROR;
        }
        else if ((SRS15 & SRS15_AUTO_CMD12_CRC_ERR) != 0U) {
            if ((SRS15 & SRS15_AUTO_CMD12_TIMEOUT_ERR) != 0U) {
                Error = SDIO_ERR_AUTOCMD12_LINE_CONFLICT;
            } else {
                Error = SIO_ERR_AUTOCMD12_CRC_ERROR;
            }
        }
        else if ((SRS15 & SRS15_AUTO_CMD12_TIMEOUT_ERR) != 0U) {
            Error = SIO_ERR_AUTOCMD12_TIMEOUT;
        }
        else if ((SRS15 & SRS15_AUTO_CMD12_NOT_EXECUTED) != 0U) {
            Error = SIO_ERR_AUTOCMD12_NOT_EXECUTED;
        }
        else {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
        }
        localIntToClear |= SRS12_AUTO_CMD_ERROR;
    }

    else if ((SRS12 & SRS12_RESPONSE_ERROR) != 0U) {
        Error = SDIO_ERR_RESP_ERROR;
    }

    else if ((SRS12 & SRS12_TUNING_ERROR) != 0U) {
        localIntToClear |= SRS12_TUNING_ERROR;
        Error = SDIO_ERR_TUNING_FAILED;
    }

    else if ((SRS12 & SRS12_CURRENT_LIMIT_ERROR) != 0U) {
        localIntToClear |= SRS12_CURRENT_LIMIT_ERROR;
        Error = SDIO_ERR_CURRENT_LIMIT_ERROR;
    }
    else if ((SRS12 & SRS12_DATA_END_BIT_ERROR) != 0U) {
        localIntToClear |= SRS12_DATA_END_BIT_ERROR;
        Error = SDIO_ERR_DATA_END_BIT_ERROR;
    }
    else if ((SRS12 & SRS12_DATA_CRC_ERROR) != 0U) {
        localIntToClear |= SRS12_DATA_CRC_ERROR;
        Error = SDIO_ERR_DATA_CRC_ERROR;
    }
   else if ((SRS12 & SRS12_DATA_TIMEOUT_ERROR) != 0U) {
        localIntToClear |= SRS12_DATA_TIMEOUT_ERROR;
        Error = SDIO_ERR_DATA_TIMEOUT_ERROR;
    }
    else if ((SRS12 & SRS12_COMMAND_INDEX_ERROR) != 0U) {
        localIntToClear |= SRS12_COMMAND_INDEX_ERROR;
        Error = SDIO_ERR_COMMAND_INDEX_ERROR;
    }
    else if ((SRS12 & SRS12_COMMAND_END_BIT_ERROR) != 0U) {
        localIntToClear |= SRS12_COMMAND_END_BIT_ERROR;
        Error = SDIO_ERR_COMMAND_END_BIT_ERROR;
    }
    else if ((SRS12 & SRS12_COMMAND_CRC_ERROR) != 0U) {
        if ((SRS12 & SRS12_COMMAND_TIMEOUT_ERROR) != 0U) {
            localIntToClear |= (SRS12_COMMAND_CRC_ERROR | SRS12_COMMAND_TIMEOUT_ERROR);
            Error = SDIO_ERR_CMD_LINE_CONFLICT;
        }
        else {
            localIntToClear |= SRS12_COMMAND_CRC_ERROR;
            Error = SDIO_ERR_COMMAND_CRC_ERROR;
        }
    }
    else if ((SRS12 & SRS12_COMMAND_TIMEOUT_ERROR) != 0U) {
        localIntToClear |= SRS12_COMMAND_TIMEOUT_ERROR;
        Error = SDIO_ERR_COMMAND_TIMEOUT_ERROR;
    }
#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
    else if ((SRS12 & SRS12_ADMA_ERROR) != 0U) {
        localIntToClear |= SRS12_ADMA_ERROR;
        Error = SDIO_ERR_ADMA;
    }
#endif
    else {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    *IntToClear = localIntToClear;

    return (Error);
}

//-----------------------------------------------------------------------------
uint8_t SDIOHost_CheckError(CSDD_SDIO_Slot* pSlot)
{
    uint32_t SRS12, SRS15;
    uint8_t Error;
    // number of interrupt to clear
    uint32_t IntToClear;

    if (pSlot == NULL) {
        Error = SDIO_ERR_INVALID_PARAMETER;
    } else {

        SRS12 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
        SRS15 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SRS12=%8lx\n", SRS12);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SRS15=%8lx\n", SRS15);

        Error = SDIOHost_CalcIntToClear(SRS12, SRS15, &IntToClear);
        uint8_t RecorveryStatus = SDIO_ERR_NO_ERROR;

        // if tuning error appear the error recovery is not need
        if (/*(pSlot->CardInserted) &&*/ (pSlot->ErrorRecorvering == 0U) &&
                                         (Error != SDIO_ERR_TUNING_FAILED)) {

            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                         "E%d %s", (uint16_t)Error, SDIO_Errors_GetText(Error));

            pSlot->ErrorRecorvering = 1;
            RecorveryStatus = SDIOHost_ErrorRecovery(pSlot, SRS12, SRS15);
            pSlot->ErrorRecorvering = 0;
            if (RecorveryStatus != SDIO_ERR_NO_ERROR) {
                Error = RecorveryStatus;
            }
        }

        if (RecorveryStatus == SDIO_ERR_NO_ERROR) {
            // clear error interrupts
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, IntToClear);
        }
    }

    return (Error);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_CheckErrorOnRecovery(CSDD_SDIO_Slot* pSlot)
{
    uint32_t SRS12, SRS15;
    uint8_t Error;
    // number of interrupt to clear
    uint32_t IntToClear;

    if (pSlot == NULL) {
        Error = SDIO_ERR_INVALID_PARAMETER;
    } else {

        SRS12 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
        SRS15 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SRS12=%8lx\n", SRS12);
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SRS15=%8lx\n", SRS15);

        Error = SDIOHost_CalcIntToClear(SRS12, SRS15, &IntToClear);

        // clear error interrupts
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, IntToClear);
    }

    return (Error);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_InterruptCommandComplete(CSDD_SDIO_Slot* pSlot, CSDD_Request* pCurrentRequest)
{
    uint8_t LocalStatus;
    uint8_t returnStatus = 0U;

    vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Command complete interrupt\n");

    pCurrentRequest->busyCheckFlags |= (uint8_t)SRS12_COMMAND_COMPLETE;
    // get response data
    LocalStatus = SDIOHost_GetResponse(pCurrentRequest, pSlot);
    if (LocalStatus != SDIO_ERR_NO_ERROR) {
        (void)ResetLines(pSlot, 1, 1);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Response error - %d\n", LocalStatus);
        pCurrentRequest->status = LocalStatus;
        returnStatus = 1U;
    } else {
        // if request doesn't need to transfer data
        // the transaction is finish

        if ( (pCurrentRequest->pCmd->requestFlags.dataPresent == 1U)
             || (pCurrentRequest->pCmd->requestFlags.responseType == CSDD_RESPONSE_R1B)
             || (pCurrentRequest->pCmd->requestFlags.responseType == CSDD_RESPONSE_R5B)) {

            if (((uint32_t)(pCurrentRequest->busyCheckFlags)
                 & (SRS12_COMMAND_COMPLETE | SRS12_TRANSFER_COMPLETE)) ==
                (SRS12_COMMAND_COMPLETE | SRS12_TRANSFER_COMPLETE)) {
                pCurrentRequest->status = SDIO_ERR_NO_ERROR;
                pSlot->pCurrentRequest = NULL;
                returnStatus = 1U;
            }
        }
        else {
            pCurrentRequest->status = SDIO_ERR_NO_ERROR;
            pSlot->pCurrentRequest = NULL;
            returnStatus = 1;
        }
    }

    return (returnStatus);
}



static uint8_t SDIOHost_InterruptBufferReadReady(CSDD_SDIO_Slot* pSlot, CSDD_Request* pCurrentRequest)
{
    uint8_t status;

    vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Buffer read ready interrupt\n");

    // in cmd19 command - (tuning command)
    // we wait only for buffer read ready interrupt
    if (pCurrentRequest->pCmd->command == SDIO_CMD19) {
        pCurrentRequest->status = SDIO_ERR_NO_ERROR;
        pSlot->pCurrentRequest = NULL;
        status = 1U;
    }
    else if ((pSlot->pCurrentRequest == NULL) || (pCurrentRequest->pBufferPos == NULL)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "pBufferPos pointer points to NULL\n");
        status = 1U;
    } else if ((pCurrentRequest->pCmd->requestFlags.isInfinite != 0U)
               && (pCurrentRequest->dataRemaining == 0U)) {
        pCurrentRequest->status = SDIO_ERR_NO_ERROR;
        pSlot->pCurrentRequest = NULL;
        status = 1U;
    } else {

        // read buffer is ready and transmission direction is read
        // transfer data from SDIO card
        if (pCurrentRequest->pCmd->requestFlags.dataTransferDirection
            == CSDD_TRANSFER_READ) {
            TransferDataBuffer(pSlot, pSlot->pCurrentRequest);
        }
        status = 0U;
    }

    return (status);
}

static uint8_t SDIOHost_InterruptBufferWriteReady(CSDD_SDIO_Slot* pSlot, CSDD_Request* pCurrentRequest)
{
    uint8_t status;
    vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Buffer write ready interrupt\n");

    if ((pSlot->pCurrentRequest == NULL) || (pCurrentRequest->pBufferPos == NULL)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "pBufferPos pointer points to NULL\n");
        status = 1U;
    } else if ((pCurrentRequest->pCmd->requestFlags.isInfinite != 0U)
               && (pCurrentRequest->dataRemaining == 0U)) {
        pCurrentRequest->status = SDIO_ERR_NO_ERROR;
        pSlot->pCurrentRequest = NULL;
        status = 1U;
    } else {

        if (pCurrentRequest->pCmd->requestFlags.dataTransferDirection
            == CSDD_TRANSFER_WRITE) {
            // write buffer is ready and transmission direction is write
            // transfer data to SDIO card
            TransferDataBuffer(pSlot, pSlot->pCurrentRequest);
        }
        status = 0U;
    }

    return (status);
}

static uint8_t SDIOHost_InterruptTransferComplete(CSDD_SDIO_Slot* pSlot, CSDD_Request* pCurrentRequest, uint32_t status)
{
    uint32_t tmp;

    do {

#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
        (void)DMA_HandleInterrupt(pSlot, pSlot->pCurrentRequest, status);
#endif
        vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Transfer complete interrupt\n");
        pCurrentRequest->busyCheckFlags |= (uint8_t)SRS12_TRANSFER_COMPLETE;

        if ((status & SRS12_BLOCK_GAP_EVENT) != 0U) {
            if (pSlot->AbortRequest != 0U) {
                pSlot->AbortRequest = 0;
                break;
            }
            // continue request
            tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, tmp | SRS10_CONTINUE_REQUEST);
        }
        if (((uint32_t)(pCurrentRequest->busyCheckFlags)
             & (SRS12_COMMAND_COMPLETE | SRS12_TRANSFER_COMPLETE)) ==
            (SRS12_COMMAND_COMPLETE | SRS12_TRANSFER_COMPLETE)) {

            if(pSlot->pCurrentRequest->commandCategory != CSDD_CMD_CAT_NORMAL) {
                if(pSlot->pCurrentRequest->subCommandRequest->status == SDIO_STATUS_PENDING) {
                   pSlot->pCurrentRequest->subCommandRequest->status = SDIO_ERR_NO_ERROR;
                }
            }
            pCurrentRequest->status = SDIO_ERR_NO_ERROR;
            pSlot->pCurrentRequest = NULL;
        }
    } while (0);

    return 1;
}



static void SDIOHost_ProcessCheckInterruptRemovalInsertion(CSDD_SDIO_Slot* pSlot, uint32_t status, uint8_t Stat)
{
    // check the previous and current state of slot
    if ((pSlot->CardInserted == 1U)
        && (((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09)
              & SRS9_CARD_INSERTED) == 0U) || (Stat != 0U))) {

#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
        if (pSlot->pCurrentRequest != NULL) {
            (void)DMA_HandleInterrupt(pSlot, pSlot->pCurrentRequest, status);
        }
#endif

        uint8_t localStat = SDIOHost_DeviceDetach(pSlot);
        if (localStat != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Device detaching failed\n");
        }
        if (pSlot->pSdioHost->pCardRemoved != NULL) {
            pSlot->pSdioHost->pCardRemoved(pSlot->pSdioHost, pSlot->SlotNr);
        }

    }
    else if ((pSlot->CardInserted == 0U)
             && ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09)
                  & SRS9_CARD_INSERTED) != 0U)) {
        pSlot->NeedAttach = 1;
        if (pSlot->pSdioHost->pCardInserted != NULL) {
            pSlot->pSdioHost->pCardInserted(pSlot->pSdioHost, pSlot->SlotNr);
        }
    }
    else {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Problem with the card insertion/removal\n");
        (void)SDIOHost_DeviceDetach(pSlot);

    }
}

static bool SDIOHost_CheckInterruptRemovalInsertion(CSDD_SDIO_Slot* pSlot, uint32_t status)
{
    bool interruptProcessed = false;

    if (((status & SRS12_CARD_REMOVAL) != 0U) || ((status & SRS12_CARD_INSERTION) != 0U)) {

        // clear card insertion and removal interrupt
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12,
                     (SRS12_CARD_REMOVAL | SRS12_CARD_INSERTION));

        if ((status & SRS12_CARD_INSERTION) != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Card insertion interrupt\n");
        }
        else {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Card removal interrupt\n");
        }

        uint8_t localStat = WaitForValue(&pSlot->RegOffset->SRS.SRS09,
                                         SRS9_CARD_STATE_STABLE, 1, COMMANDS_TIMEOUT);

        if (localStat != 0U) {
            // if card stable is not set it means that something is wrong
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Waring - card state is unstable\n");
        }

        SDIOHost_ProcessCheckInterruptRemovalInsertion(pSlot, status, localStat);

        interruptProcessed = true;
    }

    return (interruptProcessed);
}

static bool SDIOHost_CheckInterruptError(CSDD_SDIO_Slot* pSlot, uint32_t status, CSDD_Request* pCurrentRequest)
{
    bool interruptProcessed = false;
    uint8_t ret;
    if (pCurrentRequest == NULL) {
        if ((status & SRS12_ERROR_INTERRUPT) != 0U) {
            (void)SDIOHost_CheckError(pSlot);
        }

        interruptProcessed = true;
    }

    if (!interruptProcessed) {
        // check the source of the interrupt
        if ((status & SRS12_ERROR_INTERRUPT) != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Error interrupt\n");
#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
            // call this function to handle ADMA error
            (void)DMA_HandleInterrupt(pSlot, pCurrentRequest, status);
#endif
            // Reset subCommandStatus
            pSlot->subCommandStatus = 0;
            if(pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP ) {
                SDIOHost_SubCommandStatusCheck(pSlot);
            }
            DumpRequest(pCurrentRequest, 1);
            ret = SDIOHost_CheckError(pSlot);
            if(pCurrentRequest->commandCategory != CSDD_CMD_CAT_NORMAL) {
                if(pSlot->subCommandStatus != 0U) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "error is due to subcommand!\n");
                    pCurrentRequest->subCommandRequest->status = ret;
                    if(pCurrentRequest->status == SDIO_STATUS_PENDING) {
                        pCurrentRequest->status =  SDIO_ERR_GENERAL;
                    }
                    interruptProcessed = true;

                } else {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "error is due to main command!\n");
                    pCurrentRequest->status = ret;
                    if(pCurrentRequest->subCommandRequest->status == SDIO_STATUS_PENDING) {
                        pCurrentRequest->subCommandRequest->status = SDIO_ERR_NO_ERROR;
                    }
                    interruptProcessed = true;
                }
            } else {
                pCurrentRequest->status = ret;
                interruptProcessed = true;
            }
        }
    }

    return (interruptProcessed);
}


static bool SDIOHost_CheckInterruptErrorOnRecovery(CSDD_SDIO_Slot* pSlot, uint32_t status, CSDD_Request* pCurrentRequest)
{
    bool interruptProcessed = false;

    if (pCurrentRequest == NULL) {
        if ((status & SRS12_ERROR_INTERRUPT) != 0U) {
            (void)SDIOHost_CheckErrorOnRecovery(pSlot);
        }

        interruptProcessed = true;
    }

    if (!interruptProcessed) {
        // check the source of the interrupt
        if ((status & SRS12_ERROR_INTERRUPT) != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Error interrupt\n");
#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
            // call this function to handle ADMA error
            (void)DMA_HandleInterrupt(pSlot, pCurrentRequest, status);
#endif
            DumpRequest(pCurrentRequest, 1);
            pCurrentRequest->status = SDIOHost_CheckErrorOnRecovery(pSlot);

            interruptProcessed = true;
        }
    }

    return (interruptProcessed);
}

static uint8_t SDIOHost_CheckInterruptNonCardNonDma(CSDD_SDIO_Slot* pSlot, uint32_t status, CSDD_Request* pCurrentRequest)
{
    uint8_t LocalStatus = 0U;

    if ((status & SRS12_COMMAND_COMPLETE) != 0U) {
        LocalStatus = SDIOHost_InterruptCommandComplete(pSlot, pCurrentRequest);
    }

    if (LocalStatus == 0U) {

        if ((status & SRS12_BUFFER_READ_READY) != 0U) {
            LocalStatus = SDIOHost_InterruptBufferReadReady(pSlot, pCurrentRequest);
        }

        if (LocalStatus == 0U) {

            if ((status & SRS12_BUFFER_WRITE_READY) != 0U) {
                LocalStatus = SDIOHost_InterruptBufferWriteReady(pSlot, pCurrentRequest);
            }

            if (LocalStatus == 0U) {

                if ((status & SRS12_TRANSFER_COMPLETE) != 0U) {
                    LocalStatus = SDIOHost_InterruptTransferComplete(pSlot, pCurrentRequest, status);
                }
            }
        }
    }

    return (LocalStatus);
}

static void SDIOHost_CheckInterruptNonError(CSDD_SDIO_Slot* pSlot, uint32_t status, CSDD_Request* pCurrentRequest)
{
    uint8_t LocalStatus = SDIOHost_CheckInterruptNonCardNonDma(pSlot, status, pCurrentRequest);

    if (LocalStatus == 0U) {

#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
        if ((status & SRS12_DMA_INTERRUPT) != 0U) {
            (void)DMA_HandleInterrupt(pSlot, pSlot->pCurrentRequest, status);
        }
#endif

        if ((status & SRS12_CARD_INTERRUPT) != 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "%s", "Card interrupt\n");
            // clear card interrupt interrupt
            if ((pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_NONE)
                && (pSlot->pDevice->pCardInterruptHandler != NULL)) {
                pCurrentRequest->status = pSlot->pDevice->pCardInterruptHandler(pSlot->pSdioHost, pSlot->SlotNr);

            }
            else {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s",
                             "Card interrupt is signaled but pCardInterruptHandler is NULL\n");
            }
        }
    }
}

void SDIOHost_CheckInterrupt(CSDD_SDIO_Slot* pSlot, uint32_t status)
{
    CSDD_Request* pCurrentRequest;

    if (pSlot == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error! pSlot is null\n");
    } else {

        vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "SRS12 %x\n", status);

        bool interruptProcessed = SDIOHost_CheckInterruptRemovalInsertion(pSlot, status);

        if (!interruptProcessed) {
            if ((pSlot->CQEnabled != 0U) && (pSlot->CQHalted == 0U)) {
                if ((status & (SRS12_ERROR_INTERRUPT | SRS12_CMD_QUEUING_INT)) != 0U) {
                    SDIOHost_CQ_CheckInterrupt(pSlot);
                }
                interruptProcessed = true;
            }

            if (!interruptProcessed) {
                pCurrentRequest = pSlot->pCurrentRequest;

                interruptProcessed = SDIOHost_CheckInterruptError(pSlot, status, pCurrentRequest);

                if (!interruptProcessed) {
                    SDIOHost_CheckInterruptNonError(pSlot, status, pCurrentRequest);
                }
            }
        }
    }
}

static void SDIOHost_CheckInterruptOnRecovery(CSDD_SDIO_Slot* pSlot, uint32_t status)
{
    CSDD_Request* pCurrentRequest;

    vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "SRS12 %x\n", status);

    bool interruptProcessed = SDIOHost_CheckInterruptRemovalInsertion(pSlot, status);

    if (!interruptProcessed) {
        if ((pSlot->CQEnabled != 0U) && (pSlot->CQHalted == 0U)) {
            if ((status & (SRS12_ERROR_INTERRUPT | SRS12_CMD_QUEUING_INT)) != 0U) {
                SDIOHost_CQ_CheckInterrupt(pSlot);
            }
            interruptProcessed = true;
        }

        if (!interruptProcessed) {
            pCurrentRequest = pSlot->pCurrentRequest;

            interruptProcessed = SDIOHost_CheckInterruptErrorOnRecovery(pSlot, status, pCurrentRequest);

            if (!interruptProcessed) {
                SDIOHost_CheckInterruptNonError(pSlot, status, pCurrentRequest);
            }
        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ExecCardCommand_Precond(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = 1U;
    uint8_t subCommandflag = 0U;
    uint8_t responseflag = 0U;

    if (pSlot == NULL) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Error! pSlot is null\n");
        doContinue = 0U;
    } else {

        DumpRequest(pRequest, 0);
        if((pRequest->pCmd->requestFlags.responseType == CSDD_RESPONSE_R1B) || (pRequest->pCmd->requestFlags.responseType == CSDD_RESPONSE_R5B)) {
            responseflag = 1U;
        }
        if(pSlot->pSdioHost->hostCtrlVer >= 6U) {
            // Request may be a subcommand
            if((pRequest->pCmd->requestFlags.dataPresent == 0U) && (responseflag == 0U)) {
                // enabled subcommand flag
                subCommandflag = 1U;
            }
        }

#if SDIO_CFG_ENABLE_IO
        if(pSlot->pDevice->deviceType == CSDD_CARD_TYPE_SDIO ) {
            /* TODO: Fix this. ‘CSDD_SDIO_Device’ has no member named ‘SDC’
               if(pSlot->pDevice->SDC != 0) {

               }
             */
        }
#endif
        if (pRequest->pCmd->requestFlags.commandType != CSDD_CMD_TYPE_ABORT) {
            if (pSlot->pCurrentRequest != NULL) {
                /* In ADMA3 sub commands can be send only when ADMA3 engine stopped*/
                if((pSlot->pCurrentRequest->status == SDIO_STATUS_PENDING) && ((pSlot->dmaModeSelected == CSDD_ADMA3_MODE) || (subCommandflag == 0))) {
                    DumpRequest(pRequest, 1);
                    pRequest->status = SDIO_ERR_SLOT_IS_BUSY;
                    doContinue = 0U;
                } else {
                    // Reset to default mode
                    pSlot->dmaModeSelected = CSDD_AUTO_MODE;
                }
            }
        }

    }

    return (doContinue);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

static bool SDIOHost_ExecCardCommand_ProcessRequestDataPresentMultiBlock(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest,
                                                                         uint8_t TransmissionMode, uint32_t* commandInformation)
{
    bool doContinue = true;

    uint32_t command_information = (uint32_t)SRS3_MULTI_BLOCK_SEL;

    if (pRequest->pCmd->requestFlags.isInfinite == 0U) {
        command_information |= (uint32_t)SRS3_BLOCK_COUNT_ENABLE;

        if (pRequest->pCmd->requestFlags.autoCMD12Enable != 0U) {
            command_information |= (uint32_t)SRS3_AUTOCMD12_ENABLE;

        }

        if (pRequest->pCmd->requestFlags.autoCMD23Enable != 0U) {
            if ((TransmissionMode == (uint8_t)CSDD_SDMA_MODE)
                || (pSlot->pDevice->CMD23Supported == 0U)) {
                pRequest->status = SDIO_ERR_AUTO_CMD23_NOT_POSSIBLE;
                DumpRequest(pRequest, 1);
                pSlot->pCurrentRequest = NULL;
                doContinue = false;;
            } else {
                command_information |= (uint32_t)SRS3_AUTOCMD23_ENABLE;
                uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
                if((reg & SRS15_CMD23_ENABLE)!= 0U) {    // for version > 4.10, Auto CMD Auto Select used
                    command_information |= (uint32_t)SRS3_AUTO_CMD_AUTO_SELECT_ENABLE;
                }
                // block count form auto CMD23 command
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS00,
                              pRequest->pCmd->blockCount);
            }
        }
    }

    *commandInformation |= command_information;

    return (doContinue);
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ExecCardCommand_Set_Block_Count(CSDD_SDIO_Slot* pSlot,CSDD_Request* pRequest)
{
    uint32_t tmp;
    uint32_t block_count = pRequest->pCmd->blockCount;
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    tmp = CPS_FLD_READ(SD4HC__SRS__SRS15,HV4E, reg);
    if( (tmp == 1U) && (pSlot->pSdioHost->hostCtrlVer >= 6U)){
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS00,
                                block_count);
        block_count = 0U;
    }
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS01, pRequest->pCmd->blockLen
                    | (((uint32_t)block_count) << 16)
                    | pSlot->DMABufferBoundary);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static bool SDIOHost_ExecCardCommand_ProcessRequestDataPresent(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint32_t* commandInformation)
{
    uint32_t command_information = 0U;
    bool doContinue = true;
    pRequest->pBufferPos = pRequest->pCmd->pDataBuffer;
    pRequest->dataRemaining = (uint32_t)pRequest->pCmd->blockCount * pRequest->pCmd->blockLen;
    uint8_t TransmissionMode = DMA_SpecifyTransmissionMode(pSlot, pRequest);

#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
    if (TransmissionMode == (uint8_t)CSDD_ADMA3_MODE) {
        // hardware will check
        pRequest->busyCheckFlags |= (uint8_t)SRS12_COMMAND_COMPLETE;
        doContinue = false;
    }
    if (TransmissionMode != (uint8_t)CSDD_NONEDMA_MODE) {
        uint8_t status = DMA_PrepareTransfer(pSlot, pRequest);
        if (status != SDIO_ERR_NO_ERROR) {
            pRequest->status = status;
            DumpRequest(pRequest, 1);
            pSlot->pCurrentRequest = NULL;
            doContinue = false;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            // set DMA enable flag and DMA boundary at 512kB
            command_information |= (uint32_t)SRS3_DMA_ENABLE;
        }
    }
#endif

    if (doContinue) {
        // set block size and block
        SDIOHost_ExecCardCommand_Set_Block_Count(pSlot, pRequest);
        // set data preset bit
        command_information |= (uint32_t)SRS3_DATA_PRESENT;

        if (pRequest->pCmd->blockCount > 1U) {
            doContinue = SDIOHost_ExecCardCommand_ProcessRequestDataPresentMultiBlock(pSlot, pRequest,
                                                                                      TransmissionMode, &command_information);
        }

        if (doContinue) {
            if (pRequest->pCmd->requestFlags.dataTransferDirection == CSDD_TRANSFER_READ) {
                command_information |= (uint32_t)SRS3_TRANS_DIRECT_READ;
            }

            if (pRequest->pCmd->requestFlags.hwResponseCheck != 0U) {
                command_information |= (uint32_t)SRS3_RESP_ERR_CHECK_EN;
                command_information |= (uint32_t)SRS3_RESP_INTER_DISABLE;

                if (pRequest->pCmd->requestFlags.responseType == CSDD_RESPONSE_R1) {
                    command_information |= (uint32_t)SRS3_RESPONSE_CHECK_TYPE_R1;
                }
                if (pRequest->pCmd->requestFlags.responseType == CSDD_RESPONSE_R5) {
                    command_information |= (uint32_t)SRS3_RESPONSE_CHECK_TYPE_R5;
                }
            }
        }
    }

    *commandInformation |= command_information;

    return (doContinue);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint32_t SDIOHost_ExecCardCommand_ProcessRequestCheckRespType(CSDD_ResponseType responseType, uint8_t* BusyCheck)
{
    uint32_t command_information;

    // check response type
    switch (responseType) {
    default:
    case CSDD_RESPONSE_NO_RESP:
        command_information = (uint32_t)SRS3_NO_RESPONSE;
        break;
    case CSDD_RESPONSE_R2:
        command_information = (uint32_t)(SRS3_RESP_LENGTH_136
                                         | SRS3_CRC_CHECK_EN);
        break;
    case CSDD_RESPONSE_R3:
    case CSDD_RESPONSE_R4:
        command_information = (uint32_t)SRS3_RESP_LENGTH_48;
        break;
    case CSDD_RESPONSE_R1:
    case CSDD_RESPONSE_R5:
    case CSDD_RESPONSE_R6:
    case CSDD_RESPONSE_R7:
        command_information = (uint32_t)(SRS3_RESP_LENGTH_48
                                         | SRS3_CRC_CHECK_EN
                                         | SRS3_INDEX_CHECK_EN);
        break;
    case CSDD_RESPONSE_R1B:
    case CSDD_RESPONSE_R5B:
        command_information = (uint32_t)(SRS3_RESP_LENGTH_48B
                                         | SRS3_CRC_CHECK_EN
                                         | SRS3_INDEX_CHECK_EN);
        *BusyCheck = 1;
        break;
    }

    return (command_information);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static bool SDIOHost_IsDatLineBusy(CSDD_SDIO_Slot* pSlot, const CSDD_Request* pRequest, uint8_t BusyCheck)
{
    return ((( pRequest->pCmd->requestFlags.dataTransferDirection != 0U)
             || ((BusyCheck != 0U) && (pRequest->pCmd->command != SDIO_CMD12)
                 && (pRequest->pCmd->command != SDIO_CMD52))) // check if data line is not busy
            && (WaitForValue(&pSlot->RegOffset->SRS.SRS09,
                             SRS9_CMD_INHIBIT_CMD | SRS9_CMD_INHIBIT_DAT,
                             0, COMMANDS_TIMEOUT) != 0U));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ExecCardCommand_Set_Command_Flag(CSDD_SDIO_Slot* pSlot, uint32_t* commandInformation, CSDD_Request* pRequest,CSDD_Request* currentMainRequest)
{
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09);
    // If data transfer is in progress, and sub command issuing is required, set Sub Command Flag
    if(CPS_FLD_READ(SD4HC__SRS__SRS09,CIDAT, reg) != 0U){
        // set Sub Command Flag
        *commandInformation |= SRS3_SUB_CMD_FLAG;
        pRequest->commandCategory = CSDD_CMD_CAT_SUB;
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Sub command flag set\n");
        if(currentMainRequest != NULL) {
            currentMainRequest->commandCategory = CSDD_CMD_CAT_MAIN;
            currentMainRequest->subCommandRequest = pRequest;
            pSlot->pCurrentRequest = currentMainRequest;
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "Main command\n");
            DumpRequest(pSlot->pCurrentRequest, 0);
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "sub command\n");
            DumpRequest(currentMainRequest->subCommandRequest, 0);
        }
    }
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ExecCardCommand_ProcessRequest(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t BusyCheck = 0;
    bool doContinue = true;
    CSDD_Request *currentMainRequest = NULL;
    pRequest->busyCheckFlags = 0;
    if(pSlot->pCurrentRequest !=  NULL) {
        currentMainRequest = pSlot->pCurrentRequest;
    }
    // set current request
    pSlot->pCurrentRequest = pRequest;

    uint32_t command_information = SDIOHost_ExecCardCommand_ProcessRequestCheckRespType(pRequest->pCmd->requestFlags.responseType, &BusyCheck);

    // check if command line is not busy
    if (WaitForValue(&pSlot->RegOffset->SRS.SRS09, SRS9_CMD_INHIBIT_CMD, 0,
                     COMMANDS_TIMEOUT) != 0U) {
        pRequest->status = SDIO_ERR_CMD_LINE_BUSY;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Command line is busy can't execute command\n");
        DumpRequest(pRequest, 1);
        pSlot->pCurrentRequest = NULL;
    } else if (SDIOHost_IsDatLineBusy(pSlot, pRequest, BusyCheck)) {

        pRequest->status = SDIO_ERR_DAT_LINE_BUSY;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "DAT line is busy can't execute command\n");
        DumpRequest(pRequest, 1);
        pSlot->pCurrentRequest = NULL;
    } else {

        // clear all status interrupts except:
        // current limit error, card interrupt, card removal, card insertion
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, ~(SRS12_CURRENT_LIMIT_ERROR
                                                            | SRS12_CARD_INTERRUPT
                                                            | SRS12_CARD_REMOVAL
                                                            | SRS12_CARD_INSERTION));

        pRequest->respRegOffset = &pSlot->RegOffset->SRS.SRS04;
        CalcRespSize(pRequest, pSlot);
        if (pRequest->pCmd->requestFlags.hwResponseCheck != 0U) {
            pRequest->busyCheckFlags |= (uint8_t)SRS12_COMMAND_COMPLETE;
        }
        if (pRequest->pCmd->requestFlags.dataPresent != 0U) {
            doContinue = SDIOHost_ExecCardCommand_ProcessRequestDataPresent(pSlot, pRequest, &command_information);
        }
        if (doContinue) {
            // tuning command
            if (pRequest->pCmd->command == SDIO_CMD19) {
                // set data preset bit
                command_information |= (uint32_t)(SRS3_DATA_PRESENT | SRS3_TRANS_DIRECT_READ);
                // set block size and block
                pRequest->pCmd->blockLen = 64;
                // set block size and block
                SDIOHost_ExecCardCommand_Set_Block_Count(pSlot, pRequest);
            }

            //write argument
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS02, pRequest->pCmd->argument);

            command_information |= ((uint32_t)pRequest->pCmd->requestFlags.commandType << 22);

            //set sub command flag, if required
            if(pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP ) {
                    SDIOHost_ExecCardCommand_Set_Command_Flag(pSlot,&command_information,pRequest,currentMainRequest);
            }
            // execute command
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS03,
                         command_information | ((uint32_t)(pRequest->pCmd->command) << 24));
        }
    }
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ExecCardCommand_Impl(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = SDIOHost_ExecCardCommand_Precond(pSlot, pRequest);

    if (doContinue != 0U) {

        pRequest->status = SDIO_STATUS_PENDING;

        pRequest->busyCheckFlags = 0;
        // execute tuning
        (void)ExecuteTuning(pSlot, 0, pRequest);

        SDIOHost_ExecCardCommand_ProcessRequest(pSlot, pRequest);
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ExecCardCommand_NoTuning(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = SDIOHost_ExecCardCommand_Precond(pSlot, pRequest);

    if (doContinue != 0U) {

        pRequest->status = SDIO_STATUS_PENDING;

        SDIOHost_ExecCardCommand_ProcessRequest(pSlot, pRequest);
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ExecCardCommandPreconds(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = 1U;

    if ((pSlot->CQEnabled != 0U) && (pSlot->CQHalted == 0U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "This function is not supported if command queuing is enabled\n");
        pRequest->status = SDIO_ERR_UNSUPORRTED_OPERATION;
        doContinue = 0U;
    } else if ((pRequest->pCmd->requestFlags.isInfinite != 0U)
               && (pRequest->infiniteStatus == SDIOHOST_REQUEST_ISTATUS_NEXT)) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Continue infinite transfer"
                                                "BlockCount=%lu, BlockLen=%u\n", pRequest->pCmd->blockCount,
                    pRequest->pCmd->blockLen);

        pRequest->status = SDIO_STATUS_PENDING;
        pRequest->pBufferPos = pRequest->pCmd->pDataBuffer;
        pRequest->dataRemaining = (uint32_t)pRequest->pCmd->blockCount
                                  * pRequest->pCmd->blockLen;
        pSlot->pCurrentRequest = pRequest;

        TransferDataBuffer(pSlot, pRequest);
        doContinue = 0U;
    } else {
        pRequest->pSdioHost = pSlot->pSdioHost;
        pRequest->slotIndex = pSlot->SlotNr;
        pRequest->busyCheckFlags = 0;
    }

    return (doContinue);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void SDIOHost_ExecCardCommand(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = SDIOHost_ExecCardCommandPreconds(pSlot, pRequest);

    if (doContinue != 0U) {
        if (pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD) {
            if (pRequest->pCmd->requestFlags.appCmd != 0U) {
                    pRequest->status = SDIOHost_ExecCMD55Command(pSlot);
                    if (pRequest->status != SDIO_ERR_NO_ERROR) {
                            doContinue = 0U;
                    }
            }
            if (doContinue != 0U) {
                    SDIOHost_ExecCardCommand_Impl(pSlot, pRequest);
            }
        }

    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ExecCardCmdFiniteNonAppPreconds(const CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = 1U;

    if ((pRequest->pCmd->requestFlags.appCmd != 0U) || (pRequest->pCmd->requestFlags.isInfinite != 0U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "This function works only with finite not app CMD\n");
        doContinue = 0U;
    } else if ((pSlot->CQEnabled != 0U) && (pSlot->CQHalted == 0U)) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "This function is not supported if command queuing is enabled\n");
        pRequest->status = SDIO_ERR_UNSUPORRTED_OPERATION;
        doContinue = 0U;
    } else {
        pRequest->pSdioHost = pSlot->pSdioHost;
        pRequest->slotIndex = pSlot->SlotNr;
        pRequest->busyCheckFlags = 0;
    }

    return (doContinue);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Function not calling Tuning, to avoid redundancy. Used to call ABORT type commands
static void SDIOHost_ExecCardCmdFiniteNonAppNoTuning(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = SDIOHost_ExecCardCmdFiniteNonAppPreconds(pSlot, pRequest);

    if (doContinue != 0U) {
        if (pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD) {

            SDIOHost_ExecCardCommand_NoTuning(pSlot, pRequest);

        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void SDIOHost_ExecCardCmdFiniteNonApp(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t doContinue = SDIOHost_ExecCardCmdFiniteNonAppPreconds(pSlot, pRequest);

    if (doContinue != 0U) {

        if (pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD) {

            SDIOHost_ExecCardCommand_Impl(pSlot, pRequest);

        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

static uint8_t SDIOHost_CheckHighCapacityMemory(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint8_t* pFlagF8)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    // check if card supports High Capacity Memory.
    if ((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U) {
        // prepare request VHS voltage 2.7-3.6V
        SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD8, .arg = (uint32_t)(1UL << 8), .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                            .respType = CSDD_RESPONSE_R7, .hwRespCheck = 0}));
        SDIOHost_ExecCardCommand(pSlot, pRequest);

        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
        switch (pRequest->status) {
        case SDIO_ERR_COMMAND_TIMEOUT_ERROR:
            *pFlagF8 = 0;
            break;
        case SDIO_ERR_NO_ERROR:
            *pFlagF8 = 1;
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", pRequest->status);
            status = pRequest->status;
            break;
        }
    }

    return (status);
}

static uint8_t SDIOHost_ReadCCCR(CSDD_SDIO_Slot* pSlot)
{
#if SDIO_CFG_ENABLE_IO
    uint8_t status;

    // for SDIO or combo cards read CCCR to get information about supported bus widths
    if (pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
        uint8_t CardCapability;

        // read bus card capabilities
        status = SDIOHost_AccessCCCR(pSlot, SDIOHOST_CCCR_READ,
                                     &CardCapability, sizeof(CardCapability),
                                     CSDD_CCCR_CARD_CAPABILITY);
        if (status) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            return status;
        }

        if ((CardCapability & SDCARD_CCR_LSC) != 0
            && ((CardCapability & SDCARD_CCR_4BLS)) == 0) {
            pSlot->pDevice->SupportedBusWidths = CSDD_BUS_WIDTH_1;
        }
        else {
            pSlot->pDevice->SupportedBusWidths = (uint8_t)(CSDD_BUS_WIDTH_1
                                                 | CSDD_BUS_WIDTH_4);
        }
    }
#endif
    return 0;
}

// for SD memory only card get information about card from SCR register
static uint8_t SDIOHost_GetSCRRegister(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_SDMEM) {
        status = SDIOHost_ReadSCR(pSlot);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    return (status);
}

//set voltage for memory card
static uint8_t SDIOHost_SetVoltage(CSDD_SDIO_Slot* pSlot, uint8_t* pS18A, uint8_t S18R, uint8_t* pCCS, uint8_t XPC, uint8_t FlagF8, uint32_t CardVoltage)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    //set voltage for memory card
    if (((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U)
        || (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC)) {

        status = SetMemCardVoltage(pSlot, CardVoltage, FlagF8, pCCS, S18R, XPC,
                                   pS18A);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            // set device capacity info relay on CCS flag from card OCR register
            if (*pCCS != 0U) {
                pSlot->pDevice->DeviceCapacity = (uint8_t)CSDD_CAPACITY_HIGH;
            } else {
                pSlot->pDevice->DeviceCapacity = (uint8_t)CSDD_CAPACITY_NORMAL;
            }
        }
    }

    if (status == SDIO_ERR_NO_ERROR) {
        if (*pS18A != 0U) {
            pSlot->pDevice->UhsiSupported = 1;
            status = SignalVoltageSwitch(pSlot, 1);
            if (status != SDIO_ERR_NO_ERROR) {
                status = SDIO_ERR_SWITCH_VOLTAGE_FAILED;
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_SwitchVoltageIfSupported(CSDD_SDIO_Slot* pSlot, uint8_t S18A, uint8_t S18R)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if ((S18A == 0U) && (S18R != 0U)) {
        status = SDIOHost_SDCardUhsiSupported(pSlot, &pSlot->pDevice->UhsiSupported);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            if (pSlot->pDevice->UhsiSupported != 0U) {
                status = SignalVoltageSwitch(pSlot, 0);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }
        }
    }
    return (status);
}

static uint8_t SDIOHost_DeviceAttachProcess1(CSDD_SDIO_Slot* pSlot, uint32_t CurrentControllerVoltage)
{
    uint8_t status;

    // set 1 bit bus mode
    (void)SetSlotBusWidth(pSlot, (uint8_t)CSDD_BUS_WIDTH_1);
#ifdef CONFIG_COMPILE_RTL
    uint32_t FrequencyKHz = 4000;
#else
    uint32_t FrequencyKHz = 400;
#endif
    pSlot->InterfaceType = (uint8_t)CSDD_INTERFACE_TYPE_SD;

    // enable bus power
    status = SDIOHost_SetPower(pSlot, CurrentControllerVoltage);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        return status;

    }
    // SD clock supply before Issue a SD command
    // clock frequency is set to 400kHz
    status = SDIOHost_SetSDCLK(pSlot, &FrequencyKHz);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        return status;

    }
    CPS_DelayNs(800000U);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Set host clock frequency to %ldKHz \n", FrequencyKHz);

    if (status == SDIO_ERR_NO_ERROR) {
        status = SDIOHost_ResetCard(pSlot);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Reset card failed. Error %d\n", status);
        } else {
            if (pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD)
            {
                // function checks the type of card device
                // it can be MMC, SD memory or SDIO
                status = SDIOHost_CheckdeviceType(pSlot);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }

            if ((status == SDIO_ERR_NO_ERROR) && (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_NONE)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Can't identify card type\n");
                status = SDIO_ERR_DEV_NULL_POINTER;
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_DeviceAttachProcess6(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pSlot->UhsiSelected != 0U) {
        // Now card and controller works in UHS-I mode
        // for UHS-I modes only 4-bits bus mode is supported
        pSlot->pDevice->SupportedBusWidths |= (uint8_t)CSDD_BUS_WIDTH_4;
        status = SDIOHost_SelectCard(pSlot, pSlot->pDevice->RCA);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {
            status = SDIOHost_SetBusWidth(pSlot, (uint8_t)CSDD_BUS_WIDTH_4);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }
    }

    if (status == SDIO_ERR_NO_ERROR) {
        // for SD memory only card get information about card from SCR register
        status = SDIOHost_GetSCRRegister(pSlot);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            status = SDIOHost_ReadCCCR(pSlot);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {

                status = SDIOHost_LookingForDriver(pSlot);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Card initialization failed. Error %d\n", status);
                }
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_DeviceAttachProcess5(CSDD_SDIO_Slot* pSlot, uint8_t S18A, uint8_t S18R,
                                            CSDD_Request* pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_SDIO) {
        SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = SDIO_CMD2, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                            .respType = CSDD_RESPONSE_R2, .hwRespCheck = 0}));

        // execute CMD2 command
        SDIOHost_ExecCardCommand(pSlot, pRequest);

        // check status
        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
        if (pRequest->status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", pRequest->status);
            status = pRequest->status;
        }
    }

    if (status == SDIO_ERR_NO_ERROR) {

        status = SDIOHost_ReadRCA(pSlot);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            pSlot->CardInserted = 1;
            pSlot->NeedAttach = 0;

            status = SDIOHost_SwitchVoltageIfSupported(pSlot, S18A, S18R);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {
                status = SDIOHost_DeviceAttachProcess6(pSlot);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                } else {
                    status = SDIOHost_EnableCMD23Ifsupported(pSlot);
                }
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_MatchCardAndControllerVoltageSettings(CSDD_SDIO_Slot* pSlot, uint32_t OCR, uint32_t* pCardVoltage, uint32_t CurrentControllerVoltage)
{
    uint8_t status;
    uint32_t NewControllerVoltage = CurrentControllerVoltage;

    // match card voltage and controller voltage settings
    status = SDIOHOST_MatchVoltage(pSlot, OCR, pCardVoltage,
                                   &NewControllerVoltage);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        if (NewControllerVoltage != CurrentControllerVoltage) {
            // change controller voltage
            status = SDIOHost_SetPower(pSlot, NewControllerVoltage);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_ResetCard(pSlot);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_DeviceAttachProcess4(CSDD_SDIO_Slot* pSlot, uint32_t* pCardVoltage, uint32_t CurrentControllerVoltage)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    uint32_t OcrIo = 0xFFFFFFU, OcrMem = 0xFFFFFFU;

#if SDIO_CFG_ENABLE_IO
    // get OCR register from IO card
    if (pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
        status = GetIoCardOCR(pSlot, &OcrIo);
        if (status) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    if (status == SDIO_ERR_NO_ERROR)
#endif
    {
        // get OCR register from memory card
        if (((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U)
            || (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC)) {

            status = GetMemCardOCR(pSlot, &OcrMem);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_MatchCardAndControllerVoltageSettings(pSlot,
                        (OcrMem & OcrIo), pCardVoltage, CurrentControllerVoltage);
        }
    }

    return (status);
}

static uint8_t SDIOHost_DeviceAttachProcess3(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint32_t CurrentControllerVoltage, uint8_t* FlagF8, uint32_t* pCardVoltage)
{
    uint8_t status = SDIOHost_CheckHighCapacityMemory(pSlot, pRequest, FlagF8);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        status = SDIOHost_DeviceAttachProcess4(pSlot, pCardVoltage, CurrentControllerVoltage);

        if (status == SDIO_ERR_NO_ERROR) {

            status = SDIOHost_CheckHighCapacityMemory(pSlot, pRequest, FlagF8);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }
    }

    return (status);
}

static uint8_t SDIOHost_DeviceAttachProcess2(CSDD_SDIO_Slot* pSlot, uint32_t CurrentControllerVoltage)
{
    CSDD_Request Request = {0};

    uint32_t CardVoltage;
    uint8_t S18A = 0, S18R = 0, FlagF8 = 0, CCS;

    if (pSlot->Force3v3)
        S18R = 0;
    else
        S18R = (IsUhsiSupported(pSlot) != 0U) ? 1U : 0U;

    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS18);
    const uint32_t MaxCurrent_3_3V = SRS18_GET_MAX_CURRENT_3_3V(tmp);
    const uint32_t MaxCurrent_1_8V = SRS18_GET_MAX_CURRENT_1_8V(tmp);

    /// flag used for SDXC cards
    /// if card is initialized with XPC=1
    /// then it is operating less than 150mA
    const uint8_t XPC = ((MaxCurrent_1_8V >= 150U) && (MaxCurrent_3_3V >= 150U))
                        ? 1U : 0U;

    uint8_t status = SDIOHost_DeviceAttachProcess3(pSlot, &Request, CurrentControllerVoltage, &FlagF8, &CardVoltage);

    if (status == SDIO_ERR_NO_ERROR) {

#if SDIO_CFG_ENABLE_IO
        // set voltage for SDIO card
        if (pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
            status = SetIoCardVoltage(pSlot, CardVoltage, S18R, &S18A);
            if (status) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }

        if (status == SDIO_ERR_NO_ERROR)
#endif
        {
            status = SDIOHost_SetVoltage(pSlot, &S18A, S18R, &CCS, XPC, FlagF8, CardVoltage);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {
                status = SDIOHost_DeviceAttachProcess5(pSlot, S18A, S18R, &Request);
            }
        }
    }

    return(status);
}

uint8_t SDIOHost_DeviceAttach(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;
    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        const uint32_t CurrentControllerVoltage = SRS10_SET_3_3V_BUS_VOLTAGE;
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "...\n");

        status = SDIOHost_DeviceAttachProcess1(pSlot, CurrentControllerVoltage);
        if (status == SDIO_ERR_NO_ERROR) {

            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Inserted card type is %d \n",
                        pSlot->pDevice->deviceType);
            status = SDIOHost_DeviceAttachProcess2(pSlot, CurrentControllerVoltage);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_DeviceDetach(CSDD_SDIO_Slot* pSlot)
{
    uint8_t Error;

    if (pSlot == NULL) {
        Error = SDIO_ERR_INVALID_PARAMETER;
    } else {

        if (pSlot->pCurrentRequest != NULL) {
            pSlot->pCurrentRequest->status = SDIO_STATUS_ABORTED;
        }

        // reset CMD line and DAT lines
        Error = ResetLines(pSlot, 1, 1);

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "...\n");

        pSlot->CardInserted = 0;
        pSlot->NeedAttach = 0;

        if ((pSlot->pDevice != NULL) && (pSlot->pDevice->pCardDeinitialize != NULL)) {
            uint8_t status = pSlot->pDevice->pCardDeinitialize(pSlot->pSdioHost, pSlot->SlotNr);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Card de-initialize function returns error\n");
            }
        }

        DataSet(&pSlot->Devices, 0, sizeof(pSlot->Devices[0]) * CSDD_MAX_DEV_PER_SLOT);

        pSlot->pCurrentRequest = NULL;
        pSlot->RetuningEnabled = 0;
        pSlot->RetuningRequest = 0;
        pSlot->DataCount = 0;
    }

    return (Error);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_SetDmaMode(CSDD_SDIO_Slot* pSlot, uint8_t mode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t SRS17 = 0;
    uint32_t SRS16 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);
    if(pSlot->pSdioHost->hostCtrlVer >= 6) {
        SRS17 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);
    }

    switch(mode) {
    case (uint8_t)CSDD_SDMA_MODE:
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "set SDMA mode\n");

#if SDIO_SDMA_SUPPORTED
        if ((SRS16 & SRS16_DMA_SUPPORT) == 0U)
#endif
        {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        }
        break;
    case (uint8_t)CSDD_ADMA1_MODE:
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "set ADMA1 mode\n");

#if !SDIO_ADMA1_SUPPORTED
        if ((SRS16 & SRS16_ADMA1_SUPPORT) != 0U)
#endif
        {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        }
        break;
    case (uint8_t)CSDD_ADMA2_MODE:
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "set ADMA2 mode\n");

#if SDIO_ADMA2_SUPPORTED
        if ((SRS16 & SRS16_ADMA2_SUPPORT) == 0U)
#endif
        {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        }
        break;
    case (uint8_t)CSDD_ADMA3_MODE:
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "set ADMA3 mode\n");
        if ((SRS17 & SRS17_ADMA3_SUPPORT) == 0U)
        {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "ADMA3 mode not supported\n");
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        }
        break;
    case (uint8_t)CSDD_NONEDMA_MODE:
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "set NO DMA mode\n");
        break;
    case (uint8_t)CSDD_AUTO_MODE:
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s", "set AUTO select mode\n");
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        pSlot->DmaMode = mode;
    }

    return status;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ConfigureSetClk(CSDD_SDIO_Slot* pSlot,
                                        void *Data,  uint8_t dataSize)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (dataSize == sizeof(uint32_t)) {
        uint32_t* Data32 = Data;

        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "Cmd = CSDD_CONFIG_SET_CLK, FrequencyKHz = %ld\n",
                    *Data32);
        status = SDIOHost_SetSDCLK(pSlot, Data32);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                         "Set host CLK to %d failed\n",
                         *Data32);
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }
    else {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "SizeOfData should be %d but is %d\n",
                     sizeof(uint32_t), dataSize);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ConfigureSetBusWidth(CSDD_SDIO_Slot* pSlot,
                                             void *Data,  uint8_t dataSize)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (dataSize == sizeof(uint8_t)) {
        uint8_t* Data8 = Data;

        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
                    "Cmd = CSDD_CONFIG_SET_BUS_WIDTH, BusWidth = %d\n",
                    *Data8);
        status = SDIOHost_SetBusWidth(pSlot, *Data8);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Set bus width to %d failed\n",
                         *Data8);
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }
    else {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                     "SizeOfData should be %d but is %d\n",
                     sizeof(uint8_t), dataSize);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ConfigureSetDatTimeout(CSDD_SDIO_Slot* pSlot,
                                               void *Data,  uint8_t dataSize)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (dataSize == sizeof(uint32_t)) {
        uint32_t* Data32 = Data;

        vDbgMsg(DBG_GEN_MSG, DBG_FYI,
            "Cmd = CSDD_CONFIG_SET_DAT_TIMEOUT, BusWidth = %ld\n",
            *Data32);
        (void)SDIOHost_SetTimeout(pSlot, *Data32);
    }
    else {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "SizeOfData should be 4 but is %d\n",
                     dataSize);
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_Configure(CSDD_SDIO_Slot* pSlot, CSDD_ConfigCmd Cmd,
                           void *Data, const uint8_t *SizeOfData)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    const uint8_t dataSize = *SizeOfData;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        switch(Cmd) {
        case CSDD_CONFIG_SET_CLK:
            status = SDIOHost_ConfigureSetClk(pSlot, Data,  dataSize);
            break;
        case CSDD_CONFIG_SET_BUS_WIDTH:
            status = SDIOHost_ConfigureSetBusWidth(pSlot, Data, dataSize);
            break;
        case CSDD_CONFIG_SET_DAT_TIMEOUT:
            status = SDIOHost_ConfigureSetDatTimeout(pSlot, Data, dataSize);
            break;
        case CSDD_CONFIG_DISABLE_SIGNAL_INTERRUPT:
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s",
                        "Cmd = CSDD_CONFIG_DISABLE_SIGNAL_INTERRUPT\n");
            pSlot->IntSettings = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS14);
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, 0);
            break;
        case CSDD_CONFIG_RESTORE_SIGNAL_INTERRUPT:
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s",
                        "Cmd = CSDD_CONFIG_RESTORE_SIGNAL_INTERRUPT\n");
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, pSlot->IntSettings);
            break;
        case CSDD_CONFIG_SET_DMA_MODE:
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "%s",
                        "Cmd = SDIOHOST_SET_DMA_MODE\n");
            status = SDIOHost_SetDmaMode(pSlot, *(uint8_t *)Data);
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Cmd %d is not recognized\n", Cmd);
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
            break;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ProcessAbortErrorRecovery(CSDD_SDIO_Slot* pSlot)
{
    uint32_t SRS12, SRS15;
    // error occurs
    // call error recovery function
    // (this function is not automatically called only for abort command)
    SRS12 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
    SRS15 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SRS12=%8x\n", SRS12);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SRS15=%8x\n", SRS15);
    uint8_t LocalStatus = SDIOHost_ErrorRecovery(pSlot, SRS12, SRS15);
    if(LocalStatus != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT,
                "SDIOHost_ErrorRecovery function failed - Error%d, %s \n",
                LocalStatus, SDIO_Errors_GetText(LocalStatus));
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessAbort(CSDD_SDIO_Slot* pSlot)
{
    CSDD_Request Request = {0};

    // save pointer of current request
    CSDD_Request* pAbortingRequest = pSlot->pCurrentRequest;

    // reset command and data line
    uint8_t status = ResetLines(pSlot, 1, 1);
    if (status != SDIO_ERR_NO_ERROR) {
        if (pAbortingRequest != NULL) {
            pAbortingRequest->status = SDIO_ERR_ABORT_ERROR;
        }

        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Abort Error\n");
        status = SDIO_ERR_ABORT_ERROR;
    } else {

        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD12, .arg = 0, .cmdType = CSDD_CMD_TYPE_ABORT,
                                                            .respType = CSDD_RESPONSE_R1B, .hwRespCheck = 0}));
        // execute CMD12 command to abort data transmission
        SDIOHost_ExecCardCmdFiniteNonAppNoTuning(pSlot, &Request);

        SDIOHost_CheckBusyAbort(Request.pSdioHost, &Request);
        if (Request.status != SDIO_ERR_NO_ERROR) {
            SDIOHost_ProcessAbortErrorRecovery(pSlot);

            if (pAbortingRequest != NULL) {
                pAbortingRequest->status = SDIO_ERR_ABORT_ERROR;
            }
            status = SDIO_ERR_ABORT_ERROR;
        } else {

            // reset command and data line
            status = ResetLines(pSlot, 1, 1);
            if (status != SDIO_ERR_NO_ERROR) {
                if (pAbortingRequest != NULL) {
                    pAbortingRequest->status = SDIO_ERR_ABORT_ERROR;
                }
                status = SDIO_ERR_ABORT_ERROR;
            } else {

                // set status of aborting request to SDIO_STATUS_ABORTED
                if (pAbortingRequest != NULL) {
                    pAbortingRequest->status = SDIO_STATUS_ABORTED;
                }
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_Abort(CSDD_SDIO_Slot* pSlot, uint8_t IsSynchronous)
{
    uint8_t status;

    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "IsSynchronous=%d\n", IsSynchronous);

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);

        // in synchronous mode
        if (IsSynchronous != 0U) {
            // set AbortRequest flag to 1 to current slot
            pSlot->AbortRequest = 1;
            // set stop at block gap
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, tmp | SRS10_STOP_AT_BLOCK_GAP);
            // the AbortRequest flag will be cleared if transfer complete interrupt occurs
            while(CPS_UncachedRead8(&pSlot->AbortRequest) != 0U) {}
        }

        status = SDIOHost_ProcessAbort(pSlot);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ProcessStandby(CSDD_SDIO_Slot* pSlot, uint8_t WakeupCondition)
{
    uint8_t OldBusType = pSlot->BusWidth;
    uint32_t WakeupInts = 0;

    // stop SD clock
    SDIOHost_SupplySDCLK(pSlot, 0);

    // clear normal interrupt status
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, 0x1FF);

    // disable normal interrupt signal and save old settings
    uint32_t OldIntteruptSettings = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS14);
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, OldIntteruptSettings & 0x1FFU);

    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);

    if ((WakeupCondition & SDIOHOST_WAKEUP_COND_CARD_INT) != 0U) {
        tmp |= SRS10_WAKEUP_EVENT_CARD_INT_ENABLE;
        WakeupInts |= SRS12_CARD_INTERRUPT;
    }
    if ((WakeupCondition & SDIOHOST_WAKEUP_COND_CARD_INS) != 0U) {
        tmp |= SRS10_WAKEUP_EVENT_CARD_INS_ENABLE;
        WakeupInts |= SRS12_CARD_INSERTION;
    }
    if ((WakeupCondition & SDIOHOST_WAKEUP_COND_CARD_REM) != 0U) {
        tmp |= SRS10_WAKEUP_EVENT_CARD_REM_ENABLE;
        WakeupInts |= SRS12_CARD_REMOVAL;
    }

    // setup the wakeup conditions
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, tmp);

    // wait for wakeup event
    while((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12) & WakeupInts) == 0U) {;}

    tmp &= ~(SRS10_WAKEUP_EVENT_CARD_INT_ENABLE
            | SRS10_WAKEUP_EVENT_CARD_INS_ENABLE
            | SRS10_WAKEUP_EVENT_CARD_REM_ENABLE);

    // clear all wakeup conditions
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, tmp);

    // Supply SD clock
    SDIOHost_SupplySDCLK(pSlot, 1);

    // if SD bus width was changed then restore old settings
    if (OldBusType != pSlot->BusWidth) {
        (void)SetSlotBusWidth(pSlot, OldBusType);
        pSlot->BusWidth = OldBusType;
    }

    // restore old interrupt signal settings
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, OldIntteruptSettings);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_Standby(CSDD_SDIO_Slot* pSlot, uint8_t WakeupCondition)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "WakeupCondition=%d", WakeupCondition);

        // if one of resume condition is occur of the card interrupt
        // then the bus width has to be 1
        if (((WakeupCondition & SDIOHOST_WAKEUP_COND_CARD_INT) != 0U)
            && (pSlot->BusWidth != (uint8_t)CSDD_BUS_WIDTH_1)) {

            (void)SetSlotBusWidth(pSlot, (uint8_t)CSDD_BUS_WIDTH_1);
            pSlot->BusWidth = (uint8_t)CSDD_BUS_WIDTH_1;
        }

        SDIOHost_ProcessStandby(pSlot, WakeupCondition);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static bool SDIOHost_ConfigureHighSpeedMmc(CSDD_SDIO_Slot* pSlot, bool SetHighSpeed,
                                           CSDD_SpeedMode* AccessMode, uint8_t* status)
{
    bool doContinue = true;

    CSDD_Request Request = {0};

    uint32_t argument = (uint32_t)MMC_CMD6_ARG_MODE_WRITE_BYTE
                        | MMC_CMD6_ARG_INDEX(MMC_EXCSD_HS_TIMING)
                        | MMC_CMD6_ARG_VALUE((uint8_t)SetHighSpeed);

    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD6, .arg = argument, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1B, .hwRespCheck = 0}));

    // set high speed mode in the CSD register of MMC card
    SDIOHost_ExecCardCommand(pSlot, &Request);

    SDIOHost_CheckBusy(Request.pSdioHost, &Request);

    uint8_t localStatus;
    // check status
    if (Request.status != SDIO_ERR_NO_ERROR) {
        localStatus = Request.status;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", localStatus);
        doContinue = false;
        *status = localStatus;
    } else {
        *AccessMode = CSDD_ACCESS_MODE_HS_SDR;
        localStatus = ChangeHostMmcBusMode(pSlot, *AccessMode);
        *status = localStatus;
        if (localStatus != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", localStatus);
            doContinue = false;
        }
    }

    return (doContinue);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_ConfigureHighSpeedVerifyCardType(uint8_t deviceType, uint8_t* status)
{
    // if it is neither sd memory card nor sdio card then return error
    switch (deviceType) {
    case (uint8_t)CSDD_CARD_TYPE_SDMEM:
#if SDIO_CFG_ENABLE_MMC
    case (uint8_t)CSDD_CARD_TYPE_MMC:
#endif
    case (uint8_t)CSDD_CARD_TYPE_COMBO:
#if SDIO_CFG_ENABLE_IO
    case CSDD_CARD_TYPE_SDIO:
#endif
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        *status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ConfigureHighSpeed(CSDD_SDIO_Slot* pSlot, bool SetHighSpeed)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    bool doContinue = true;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        const uint8_t deviceType = pSlot->pDevice->deviceType;

        CSDD_SpeedMode AccessMode = (SetHighSpeed != 0U)
                             ? CSDD_ACCESS_MODE_SDR25
                             : CSDD_ACCESS_MODE_SDR12;

        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SetHighSpeed=%d", SetHighSpeed);

        // check if high speed is supported by host
        //if (CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16) & SFR16_HIGH_SPEED_SUPPORT)
        //    return SDIO_ERR_BUS_SPEED_UNSUPP

        if ((deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U) {
            status = ChangeDeviceSdBusMode(pSlot, AccessMode);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                doContinue = false;
            } else {
                ConfigHostHighSpeedMode(pSlot, SetHighSpeed);
            }
        }

        if (doContinue) {
#if SDIO_CFG_ENABLE_IO
            if (deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
                status = ChangeDeviceIoBusMode(pSlot, AccessMode);
                if (status == SDIO_ERR_NO_ERROR) {
                    ConfigHostHighSpeedMode(pSlot, SetHighSpeed);
                }
            }
#endif

#if SDIO_CFG_ENABLE_MMC
            if (deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
                // MMC card
                doContinue = SDIOHost_ConfigureHighSpeedMmc(pSlot, SetHighSpeed,
                                                            &AccessMode, &status);
            }
#endif

            if (doContinue) {
                SDIOHost_ConfigureHighSpeedVerifyCardType(deviceType, &status);

                if (status == SDIO_ERR_NO_ERROR) {
                    pSlot->AccessMode = (uint8_t)AccessMode;
                } else {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ConfigureAccessMode33vNonMmc(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status;

    switch(AccessMode) {
    case CSDD_ACCESS_MODE_SDR12:
        status = SDIOHost_ConfigureHighSpeed(pSlot, 0);
        break;
    case CSDD_ACCESS_MODE_SDR25:
        status = SDIOHost_ConfigureHighSpeed(pSlot, 1);
        break;
    default:
        status = SDIO_ERR_WRONG_SINGALING_LEVEL;
        break;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessConfigureAccessModeHs400(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = ChangeDeviceMmcBusMode(pSlot, CSDD_ACCESS_MODE_HS_200);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        status = ChangeHostMmcBusMode(pSlot, CSDD_ACCESS_MODE_HS_200);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            pSlot->AccessMode = (uint8_t)CSDD_ACCESS_MODE_HS_400;

            uint32_t FrequencyKHz = Freq200MHzInKHz;
            status = SDIOHost_SetSDCLK(pSlot, &FrequencyKHz);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {

                status = ExecuteTuningMmc(pSlot);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_FinishConfigureAccessMode18vOrMmc(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = ChangeDeviceMmcBusMode(pSlot, AccessMode);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        status = ChangeHostMmcBusMode(pSlot, AccessMode);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    if (status == SDIO_ERR_NO_ERROR) {
        if (AccessMode == CSDD_ACCESS_MODE_HS_200) {
            uint32_t FrequencyKHz = Freq200MHzInKHz;

            status = SDIOHost_SetSDCLK(pSlot, &FrequencyKHz);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {

                status = ExecuteTuningMmc(pSlot);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessConfigureAccessCheckDevType(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode, uint8_t deviceType)
{
    uint8_t status;

    // if it is neither sd memory card nor sdio card then return error
    switch (deviceType) {
    case (uint8_t)CSDD_CARD_TYPE_SDMEM:
    case (uint8_t)CSDD_CARD_TYPE_SDIO:
    case (uint8_t)CSDD_CARD_TYPE_COMBO:
    case (uint8_t)CSDD_CARD_TYPE_MMC:
        pSlot->AccessMode = (uint8_t)AccessMode;
        status = SDIO_ERR_NO_ERROR;
        break;
    default:
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#if 0
static uint8_t SDIOHost_ProcessConfigureAccessModeHs400Es(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;

    uint32_t FrequencyKHz = 400;
    uint32_t cardStatus;

    ChangeDeviceMmcBusMode(pSlot, CSDD_ACCESS_MODE_HS_SDR);

    status = ChangeHostMmcBusMode(pSlot, CSDD_ACCESS_MODE_HS_SDR);
    if (status) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        return status;

    }

    status = SDIOHost_SetSDCLK(pSlot, &FrequencyKHz);
    if (status) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        return status;

    }

    status = SDIOHost_ReadCardStatus(pSlot, &cardStatus);
    if (status) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        return status;

    }

    return (status);
}
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessConfigureAccessMode18vOrMmc(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    const uint8_t deviceType = pSlot->pDevice->deviceType;

#if SDIO_CFG_ENABLE_IO
    if (deviceType & (uint8_t)CSDD_CARD_TYPE_SDIO) {
        // change sdio card access bus mode settings
        status = ChangeDeviceIoBusMode(pSlot, AccessMode);

        if (status == SDIO_ERR_NO_ERROR) {
            status = ChangeHostUhsiMode(pSlot, AccessMode);
            if (status) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                return status;
            }
        }
    }
#endif

#if SDIO_CFG_ENABLE_MMC
    if (deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
        // change sdio card access bus mode settings

#if 0
        if (AccessMode == CSDD_ACCESS_MODE_HS_400_ES) {
            status = SDIOHost_ProcessConfigureAccessModeHs400Es(pSlot);
            if (status) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                return status;
            }
        }
#endif

        if (AccessMode == CSDD_ACCESS_MODE_HS_400) {
            status = SDIOHost_ProcessConfigureAccessModeHs400(pSlot);
        }

        if (status == SDIO_ERR_NO_ERROR) {
            status = SDIOHost_FinishConfigureAccessMode18vOrMmc(pSlot, AccessMode);
        }
    }
#endif

    if (status == SDIO_ERR_NO_ERROR) {
        status = SDIOHost_ProcessConfigureAccessCheckDevType(pSlot, AccessMode, deviceType);
    }

    return(status);

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ConfigureAccessMode18vOrMmc(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    bool doContinue = true;

    // if host signal is 1.8V then we can use UHS-I modes
    if ((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U) {

        status = HostSupportAccessMode(pSlot, AccessMode);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            doContinue = false;
        } else {

            //change device settings
            status = ChangeDeviceSdBusMode(pSlot, AccessMode);
            if (status == SDIO_ERR_NO_ERROR) {
                // change host settings
                status = ChangeHostUhsiMode(pSlot, AccessMode);
                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                    doContinue = false;
                }
            }
            else {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                doContinue = false;
            }
        }
    }

    if (doContinue) {
        status = SDIOHost_ProcessConfigureAccessMode18vOrMmc(pSlot, AccessMode);
    }

    return(status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ConfigureAccessMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode)
{
    uint8_t status;

    if (AccessMode <= CSDD_ACCESS_MODE_HS_400_ES) {
        uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
        // if host signal is 3,3V then we can use either
        // default mode or high speed mode
        if (((tmp & SRS15_18V_ENABLE) == 0U)
            && (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
            status = SDIOHost_ConfigureAccessMode33vNonMmc(pSlot, AccessMode);
        } else {
            status = SDIOHost_ConfigureAccessMode18vOrMmc(pSlot, AccessMode);
        }
    } else {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    }

    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_Tuning(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t tmp;

    pSlot->RetuningEnabled = 0;
    // check if tuning is needed in selected access mode
    // if it is needed set RetuningEnabled flag
    switch (pSlot->AccessMode) {
    case (uint8_t)CSDD_ACCESS_MODE_SDR104:
        pSlot->RetuningEnabled = 1;
        status = ExecuteTuning(pSlot, 1, NULL);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
        break;
    case (uint8_t)CSDD_ACCESS_MODE_SDR50:
        tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);
        if ((tmp & SRS17_USE_TUNING_SDR50) != 0U) {
            pSlot->RetuningEnabled = 1;
            status = ExecuteTuning(pSlot, 1, NULL);
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            }
        }
        break;
    default:
        //
        break;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void SDIOHost_PresetValueSwitch(CSDD_SDIO_Slot* pSlot, bool Enable)
{
    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);

    if (Enable != 0U) {
        tmp |= SRS15_PRESET_VALUE_ENABLE;
    } else {
        tmp &= ~SRS15_PRESET_VALUE_ENABLE;
    }

    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, tmp);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ClockGeneratorSelect(CSDD_SDIO_Slot* pSlot, uint8_t ProgClkMode)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t tmp;

    if (ProgClkMode != pSlot->ProgClockMode) {
        if (ProgClkMode != 0U) {
            tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);
            // if Clock Multiplier is 0 that means Programmable Clock Mode
            // is not supported
            if (SRS17_GET_CLOCK_MULTIPLIER(tmp) == 0U) {
                status = SDIO_ERR_UNSUPORRTED_OPERATION;
            }
        }

        if (status == SDIO_ERR_NO_ERROR) {
            pSlot->ProgClockMode = ProgClkMode;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ConfigureDrvStrength(CSDD_SDIO_Slot* pSlot,
                                         CSDD_DriverStrengthType DriverStrength)
{
    uint8_t status = SDIOHost_SDCardSetDrvStrength(pSlot, DriverStrength);

    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        uint32_t SRS15 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);

        SRS15 &= ~SRS15_DRIVER_TYPE_MASK;

        switch(DriverStrength) {
        case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_A:
            SRS15 |= SRS15_DRIVER_TYPE_A;
            break;
        case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_B:
            SRS15 |= SRS15_DRIVER_TYPE_B;
            break;
        case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_C:
            SRS15 |= SRS15_DRIVER_TYPE_C;
            break;
        case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_D:
            SRS15 |= SRS15_DRIVER_TYPE_D;
            break;
        default:
            //
            break;
        }

        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, SRS15);

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_InterruptConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable)
{
    uint32_t SRS14 = 0;

    pSlot->pSdioHost->intEn = enable;
    if (enable != 0U) {
        SRS14 |= (uint32_t)(SRS14_TUNING_ERROR_SIG_EN
                            | SRS14_ADMA_ERROR_SIG_EN
                            | SRS14_AUTO_CMD12_ERR_SIG_EN
                            | SRS14_CURRENT_LIMIT_ERR_SIG_EN
                            | SRS14_DATA_END_BIT_ERR_SIG_EN
                            | SRS14_DATA_CRC_ERR_SIG_EN
                            | SRS14_DATA_TIMEOUT_ERR_SIG_EN
                            | SRS14_COMMAND_INDEX_ERR_SIG_EN
                            | SRS14_COMMAND_END_BIT_ERR_SIG_EN
                            | SRS14_COMMAND_CRC_ERR_SIG_EN
                            | SRS14_COMMAND_TIMEOUT_ERR_SIG_EN
#   if ENABLE_CARD_INTERRUPT
                            | SRS14_CARD_INTERRUPT_SIG_EN
#   endif
                            | SRS14_CARD_REMOVAL_SIG_EN
                            | SRS14_CARD_INERTION_SIG_EN
                            | SRS14_BUFFER_READ_READY_SIG_EN
                            | SRS14_BUFFER_WRITE_READY_SIG_EN
                            | SRS14_DMA_INTERRUPT_SIG_EN
                            | SRS14_BLOCK_GAP_EVENT_SIG_EN
                            | SRS14_TRANSFER_COMPLETE_SIG_EN
                            | SRS14_COMMAND_COMPLETE_SIG_EN
                            | SRS14_RESPONSE_ERROR_SIG_EN
                            | SRS14_CMD_QUEUING_SIG_EN);
    }

    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS14, SRS14);

    (void)SDIOHost_CQ_InterruptConfig(pSlot, enable);

    return 0;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void SDIOHost_CheckBusy(CSDD_SDIO_Host* pSdioHost, CSDD_Request* pRequest)
{
    uint32_t TimeNs = COMMANDS_TIMEOUT * 1000 + 100;

    while(pRequest->status == SDIO_STATUS_PENDING) {
        /*if interrupts are disabled then we need to call
         *  interrupt handler manually - polling mode*/
        if (pSdioHost->intEn == 0U) {
            uint8_t handled;
            SDIOHost_InterruptHandler(pSdioHost, &handled);
        }

        if (TimeNs < 100) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Driver timeout error!\n");
            if (pRequest->pCmd->requestFlags.commandType != CSDD_CMD_TYPE_ABORT) {
                (void)SDIOHost_Abort(&pSdioHost->Slots[pRequest->slotIndex], 0);
            }
            pRequest->status = SDIO_ERR_TIMEOUT;
        }
        CPS_DelayNs(100U);
        TimeNs -= 100;
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_CheckBusyAbort(CSDD_SDIO_Host* pSdioHost, CSDD_Request* pRequest)
{
    uint32_t TimeNs = COMMANDS_TIMEOUT * 1000 + 100;

    if (pRequest->pCmd->requestFlags.commandType != CSDD_CMD_TYPE_ABORT) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "should be used only with ABORT command!\n");
    }
    while(pRequest->status == SDIO_STATUS_PENDING) {
        /*if interrupts are disabled then we need to call
         *  interrupt handler manually - polling mode*/
        if (pSdioHost->intEn == 0U) {
            uint8_t handled;
            SDIOHost_InterruptHandler(pSdioHost, &handled);
        }
        // check if given Time is not exceeded
        if (TimeNs < 100) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s", "Driver timeout error!\n");
            pRequest->status = SDIO_ERR_TIMEOUT;
        }
        CPS_DelayNs(100U);
        TimeNs -= 100;
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void SDIOHost_SubCommandStatusCheck(CSDD_SDIO_Slot* pSlot)
{
    uint32_t SRS09 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09);
    pSlot->subCommandStatus = (uint8_t)(CPS_FLD_READ(SD4HC__SRS__SRS09,SCMDS,SRS09) & 0xFFU);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static uint8_t SDIOHost_EnableCMD23Ifsupported(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    // SRS15.CMD23E bit added from spec ver4.10. Host Driver set this bit to 1 if Card supports CMD23.
    if((pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP) && (pSlot->pDevice->CMD23Supported != 0U)){
        tmp |= SRS15_CMD23_ENABLE;
    }
    CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15, tmp);

    return status;
}
//-----------------------------------------------------------------------------




