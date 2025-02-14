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

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "cedi_sanity.h"
#include "cedi_priv.h"
#include "cedi_structs_if.h"

/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_ConfigSF(const CEDI_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->dmaAddrBusWidth != CEDI_DMA_ADDR_BUS_WIDTH_32) &&
            (obj->dmaAddrBusWidth != CEDI_DMA_ADDR_BUS_WIDTH_64)
        )
        {
            ret = CDN_EINVAL;
        }
        if ((obj->dmaEndianism & ~(
                    CEDI_END_SWAP_DESC |
                    CEDI_END_SWAP_DATA
                )) != 0)
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->dmaBusWidth != CEDI_DMA_BUS_WIDTH_32) &&
            (obj->dmaBusWidth != CEDI_DMA_BUS_WIDTH_64) &&
            (obj->dmaBusWidth != CEDI_DMA_BUS_WIDTH_128)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->rxPktBufSize > (3))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->dmaDataBurstLen != CEDI_DMA_DBUR_LEN_1) &&
            (obj->dmaDataBurstLen != CEDI_DMA_DBUR_LEN_4) &&
            (obj->dmaDataBurstLen != CEDI_DMA_DBUR_LEN_8) &&
            (obj->dmaDataBurstLen != CEDI_DMA_DBUR_LEN_16) &&
            (obj->dmaDataBurstLen != CEDI_DMA_DBUR_LEN_256)
        )
        {
            ret = CDN_EINVAL;
        }
        if ((obj->dmaCfgFlags & ~(
                    CEDI_CFG_DMA_DISC_RXP |
                    CEDI_CFG_DMA_FRCE_RX_BRST |
                    CEDI_CFG_DMA_FRCE_TX_BRST
                )) != 0)
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_8) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_16) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_32) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_48) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_64) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_96) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_128) &&
            (obj->mdcPclkDiv != CEDI_MDC_DIV_BY_224)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->ifTypeSel != CEDI_IFSP_MII) &&
            (obj->ifTypeSel != CEDI_IFSP_GMII) &&
            (obj->ifTypeSel != CEDI_IFSP_RGMII) &&
            (obj->ifTypeSel != CEDI_IFSP_SGMII) &&
            (obj->ifTypeSel != CEDI_IFSP_BASE_X) &&
            (obj->ifTypeSel != CEDI_IFSP_XGMII) &&
            (obj->ifTypeSel != CEDI_IFSP_USXGMII)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->ifSpeedSel != CEDI_SPEED_10M) &&
            (obj->ifSpeedSel != CEDI_SPEED_100M) &&
            (obj->ifSpeedSel != CEDI_SPEED_1000M) &&
            (obj->ifSpeedSel != CEDI_SPEED_2500M) &&
            (obj->ifSpeedSel != CEDI_SPEED_5G) &&
            (obj->ifSpeedSel != CEDI_SPEED_10G) &&
            (obj->ifSpeedSel != CEDI_SPEED_25G)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->rxBufOffset > (CEDI_RX_MAX_BUFFER_OFFSET))
        {
            ret = CDN_EINVAL;
        }
        if ((obj->chkSumOffEn & ~(
                    CEDI_CFG_CHK_OFF_TX |
                    CEDI_CFG_CHK_OFF_RX
                )) != 0)
        {
            ret = CDN_EINVAL;
        }
        if (obj->rx1536ByteEn > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rxJumboFrEn > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enRxBadPreamble > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ignoreIpgRxEr > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->storeUdpTcpOffset > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enExtTsuPort > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->aw2bMaxPipeline < (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ar2rMaxPipeline < (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->pfcMultiQuantum > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->incExpressTraffic > (1))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->preInCrcTx != CEDI_PRE_CRC_NO_COVER) &&
            (obj->preInCrcTx != CEDI_PRE_CRC_7MS_COVER) &&
            (obj->preInCrcTx != CEDI_PRE_CRC_ALL8_COVER) &&
            (obj->preInCrcTx != CEDI_PRE_CRC_4MS_COVER)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->preInCrcRx != CEDI_PRE_CRC_NO_COVER) &&
            (obj->preInCrcRx != CEDI_PRE_CRC_7MS_COVER) &&
            (obj->preInCrcRx != CEDI_PRE_CRC_ALL8_COVER) &&
            (obj->preInCrcRx != CEDI_PRE_CRC_4MS_COVER)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct Pcs25gCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_Pcs25gCfgSF(const CEDI_Pcs25gCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->serdesRate != CEDI_SERDES_RATE_5G) &&
            (obj->serdesRate != CEDI_SERDES_RATE_10G) &&
            (obj->serdesRate != CEDI_SERDES_RATE_25G)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct AxiHostArbitrationCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_AxiHostArbitrationCfgSF(const CEDI_AxiHostArbitrationCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->axiWriterArbiter != CEDI_AW_ROUND_ROBIN) &&
            (obj->axiWriterArbiter != CEDI_AW_TXDSC_RXDSC_RXDATA) &&
            (obj->axiWriterArbiter != CEDI_AW_TXDSC_RXDATA_RXDSC) &&
            (obj->axiWriterArbiter != CEDI_AW_RXDSC_TXDSC_RXDATA) &&
            (obj->axiWriterArbiter != CEDI_AW_RXDSC_RXDATA_TXDSC) &&
            (obj->axiWriterArbiter != CEDI_AW_RXDATA_TXDSC_RXDSC) &&
            (obj->axiWriterArbiter != CEDI_AW_RXDATA_RXDSC_TXDSC)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->axiReadArbiter != CEDI_AR_ROUND_ROBIN) &&
            (obj->axiReadArbiter != CEDI_AR_RXDSC_TXDATA_TXDSC) &&
            (obj->axiReadArbiter != CEDI_AR_RXDSC_TXDSC_TXDATA) &&
            (obj->axiReadArbiter != CEDI_AR_TXDATA_RXDSC_TXDSC) &&
            (obj->axiReadArbiter != CEDI_AR_TXDATA_TXDSC_RXDSC) &&
            (obj->axiReadArbiter != CEDI_AR_TXDSC_RXDSC_TXDATA) &&
            (obj->axiReadArbiter != CEDI_AR_TXDSC_TXDATA_RXDSC)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct WatermarkLvl
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_WatermarkLvlSF(const CEDI_WatermarkLvl *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->low != CEDI_WATERMARK_LEVEL_1) &&
            (obj->low != CEDI_WATERMARK_LEVEL_2) &&
            (obj->low != CEDI_WATERMARK_LEVEL_4) &&
            (obj->low != CEDI_WATERMARK_LEVEL_8) &&
            (obj->low != CEDI_WATERMARK_LEVEL_16)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->high != CEDI_WATERMARK_LEVEL_1) &&
            (obj->high != CEDI_WATERMARK_LEVEL_2) &&
            (obj->high != CEDI_WATERMARK_LEVEL_4) &&
            (obj->high != CEDI_WATERMARK_LEVEL_8) &&
            (obj->high != CEDI_WATERMARK_LEVEL_16)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct AxiBuffCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_AxiBuffCfgSF(const CEDI_AxiBuffCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct TestPatternSeed
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_TestPatternSeedSF(const CEDI_TestPatternSeed *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->seedUpper > (67108863))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct BuffAddr
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_BuffAddrSF(const CEDI_BuffAddr *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct qTxBufParams
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_QTxBufParamsSF(const CEDI_qTxBufParams *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->queueNum > (CEDI_MAX_TX_QUEUES-1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct MacAddress
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_MacAddressSF(const CEDI_MacAddress *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct T1Screen
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_T1ScreenSF(const CEDI_T1Screen *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->udpEnable > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dstcEnable > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct T2Screen
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_T2ScreenSF(const CEDI_T2Screen *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->vlanEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->vlanPriority > (7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->eTypeEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ethTypeIndex > (7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->compAEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->compAIndex > (CEDI_COMPARE_MAX_INDEX))
        {
            ret = CDN_EINVAL;
        }
        if (obj->compBEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->compBIndex > (CEDI_COMPARE_MAX_INDEX))
        {
            ret = CDN_EINVAL;
        }
        if (obj->compCEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->compCIndex > (CEDI_COMPARE_MAX_INDEX))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct T2Compare
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_T2CompareSF(const CEDI_T2Compare *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->offsetVal > (63))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->offsetPosition != CEDI_T2COMP_OFF_SOF) &&
            (obj->offsetPosition != CEDI_T2COMP_OFF_ETYPE) &&
            (obj->offsetPosition != CEDI_T2COMP_OFF_IPHDR) &&
            (obj->offsetPosition != CEDI_T2COMP_OFF_TCPUDP) &&
            (obj->offsetPosition != CEDI_T2COMP_OFF_VID_C_TAG) &&
            (obj->offsetPosition != CEDI_T2COMP_OFF_VID_S_TAG)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->disableMask > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct 1588TimerVal
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_1588TimerValSF(const CEDI_1588TimerVal *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->nanosecs > (1073741823))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct TsuTimerVal
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_TsuTimerValSF(const CEDI_TsuTimerVal *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->nanosecs > (4194303))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct TimerIncrement
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_TimerIncrementSF(const CEDI_TimerIncrement *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct AnAdvPage
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_AnAdvPageSF(const CEDI_AnAdvPage *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->fullDuplex > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->halfDuplex > (1))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->pauseCap != CEDI_AN_PAUSE_CAP_NONE) &&
            (obj->pauseCap != CEDI_AN_PAUSE_CAP_SYM) &&
            (obj->pauseCap != CEDI_AN_PAUSE_CAP_ASYM) &&
            (obj->pauseCap != CEDI_AN_PAUSE_CAP_BOTH)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->remFlt != CEDI_AN_REM_FLT_NONE) &&
            (obj->remFlt != CEDI_AN_REM_FLT_LNK_FAIL) &&
            (obj->remFlt != CEDI_AN_REM_FLT_OFFLINE) &&
            (obj->remFlt != CEDI_AN_REM_FLT_AN_ERR)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->nextPage > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct AnNextPage
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_AnNextPageSF(const CEDI_AnNextPage *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->message > (0x7ff))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ack2 > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->msgPage > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->np > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct WakeOnLanReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_WakeOnLanRegSF(const CEDI_WakeOnLanReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->magPktEn > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->arpEn > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->specAd1En > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->multiHashEn > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct EnstTimeConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_EnstTimeConfigSF(const CEDI_EnstTimeConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->startTimeS > (3))
        {
            ret = CDN_EINVAL;
        }
        if (obj->startTimeNs > (0x3FFFFFFF))
        {
            ret = CDN_EINVAL;
        }
        if (obj->onTime > (0x1FFFF))
        {
            ret = CDN_EINVAL;
        }
        if (obj->offTime > (0x1FFFF))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct Callbacks
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_CallbacksSF(const CEDI_Callbacks *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct QueueSegAlloc
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_QueueSegAllocSF(const CEDI_QueueSegAlloc *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct FrameEliminationConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_FrameEliminationConfigSF(const CEDI_FrameEliminationConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->enVectAlg > (1))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->seqNumIdentification != CEDI_SEQ_NUM_IDEN_OFFSET) &&
            (obj->seqNumIdentification != CEDI_SEQ_NUM_IDEN_TAG)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->offsetValue > (511))
        {
            ret = CDN_EINVAL;
        }
        if (obj->smemberStream1 > (15))
        {
            ret = CDN_EINVAL;
        }
        if (obj->smemberStream2 > (15))
        {
            ret = CDN_EINVAL;
        }
        if (obj->seqNumLength > (16))
        {
            ret = CDN_EINVAL;
        }
        if (obj->seqRecWindow > (63))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct FrameEliminationTagConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_FrameEliminationTagConfSF(const CEDI_FrameEliminationTagConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->enStripRedTag > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PreemptionConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_PreemptionConfigSF(const CEDI_PreemptionConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->routeRxToPmac > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enPreeption > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enVerify > (1))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->addFragSize != CEDI_FRAG_SIZE_64) &&
            (obj->addFragSize != CEDI_FRAG_SIZE_128) &&
            (obj->addFragSize != CEDI_FRAG_SIZE_192) &&
            (obj->addFragSize != CEDI_FRAG_SIZE_256)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct LockupConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_LockupConfigSF(const CEDI_LockupConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dmaLockupTime > (2047))
        {
            ret = CDN_EINVAL;
        }
        if (obj->txLockupTime > (2047))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enLockupRecovery > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enRxMacLockupMon > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enRxDmaLockupMon > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enTxMacLockupMon > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enTxDmaLockupMon > (1))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct RxQFlushConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_RxQFlushConfigSF(const CEDI_RxQFlushConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dropAllFrames > (1))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dropOnRsrcErr > (1))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->rxQFlushMode != CEDI_FLUSH_MODE_OFF) &&
            (obj->rxQFlushMode != CEDI_FLUSH_MODE_LIMIT_NUM_BYTES) &&
            (obj->rxQFlushMode != CEDI_FLUSH_MODE_LIMIT_FRAME_SIZE)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct Type2ScreenerRateLimit
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_Type2ScreenerRateLimitSF(const CEDI_Type2ScreenerRateLimit *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct AxiQosConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_AxiQosConfigSF(const CEDI_AxiQosConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->descriptorQos > (15))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataQos > (15))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PrivateData
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CEDI_PrivateDataSF(const CEDI_PrivateData *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (CEDI_ConfigSF(&obj->cfg) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (CEDI_1588TimerValSF(&obj->ptpTime) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->macType != CEDI_MAC_TYPE_EMAC) &&
            (obj->macType != CEDI_MAC_TYPE_PMAC) &&
            (obj->macType != CEDI_MAC_TYPE_MAC)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] config driver/hardware configuration required
 * @param[out] memReq returns the size of memory allocations required
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction1(const CEDI_Config* config, const CEDI_SysReq* memReq)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (memReq == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[out] pD driver state info specific to this instance
 * @param[in,out] config specifies driver/hardware configuration
 * @param[in] callbacks client-supplied callback functions
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction2(const CEDI_PrivateData* pD, const CEDI_Config* config, const CEDI_Callbacks* callbacks)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_CallbacksSF(callbacks) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver state info specific to this instance
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction3(const CEDI_PrivateData* pD)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enable the events, if =0 then disable
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction7(const CEDI_PrivateData* pD, const uint8_t enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (enable > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] event returned enabled events
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction8(const CEDI_PrivateData* pD, const uint32_t* event)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (event == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txIntDelay Interrupt delay to apply to Tx frame complete
 * @param[in] rxIntDelay Interrupt delay to apply to Rx frame complete
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction9(const CEDI_PrivateData* pD, const uint8_t txIntDelay, const uint8_t rxIntDelay)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txIntDelay Interrupt delay to apply to Tx frame complete
 * @param[out] rxIntDelay Interrupt delay to apply to Rx frame complete
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction10(const CEDI_PrivateData* pD, const uint8_t* txIntDelay, const uint8_t* rxIntDelay)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (txIntDelay == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (rxIntDelay == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] speedSel a CEDI_IfSpeed enum indicating Tx/Rx speed
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction13(const CEDI_PrivateData* pD, const CEDI_IfSpeed speedSel)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (speedSel != CEDI_SPEED_10M) &&
        (speedSel != CEDI_SPEED_100M) &&
        (speedSel != CEDI_SPEED_1000M) &&
        (speedSel != CEDI_SPEED_2500M) &&
        (speedSel != CEDI_SPEED_5G) &&
        (speedSel != CEDI_SPEED_10G) &&
        (speedSel != CEDI_SPEED_25G)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] speedSel returns CEDI_IfSpeed enum indicating Tx/Rx speed "
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction14(const CEDI_PrivateData* pD, const CEDI_IfSpeed* speedSel)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (speedSel == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable equal 1 if jumbo frames accept enabled; equal 0 if disabled.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction16(const CEDI_PrivateData* pD, const uint8_t* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] length max. length to receive, in bytes.  Maximum is 16383
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction17(const CEDI_PrivateData* pD, const uint16_t length)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (length > (16383))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] length returns max. length to receive, in bytes
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction18(const CEDI_PrivateData* pD, const uint16_t* length)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (length == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] offset offset to use, range 0 to 3 bytes
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction23(const CEDI_PrivateData* pD, const uint8_t offset)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (offset > (3))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] bufferSizeMultiple64Bytes The size of buffer (in multiples of 64 bytes) to use in main system memory
 *    when writing received data.
 *    Possible values are 1 to 255 which gives 64 to 16320 bytes.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction25(const CEDI_PrivateData* pD, const uint8_t bufferSizeMultiple64Bytes)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (bufferSizeMultiple64Bytes < (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] burstLength burst length to use for given queue
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction27(const CEDI_PrivateData* pD, const CEDI_BurstLen burstLength)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (burstLength != CEDI_BURST_LEN_1) &&
        (burstLength != CEDI_BURST_LEN_2) &&
        (burstLength != CEDI_BURST_LEN_4) &&
        (burstLength != CEDI_BURST_LEN_8) &&
        (burstLength != CEDI_BURST_LEN_16) &&
        (burstLength != CEDI_BURST_LEN_32) &&
        (burstLength != CEDI_BURST_LEN_64) &&
        (burstLength != CEDI_BURST_LEN_128) &&
        (burstLength != CEDI_BURST_LEN_256)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] burstLenth burst length to use for given queue
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction28(const CEDI_PrivateData* pD, const CEDI_BurstLen burstLenth)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] watermark returns value to control data forwarding if partial store and forward Tx mode enabled
 * @param[out] enable =1 if partial store and forward Tx mode enabled
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction38(const CEDI_PrivateData* pD, const uint32_t* watermark, const uint8_t* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (watermark == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enableBit 4-bit field selecting bits to force value on
 * @param[in] bitValues 4-bit field specifying values to force address bits 31:28 to, if corresponding bit in enableBit is set to 1
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction41(const CEDI_PrivateData* pD, const uint8_t enableBit, const uint8_t bitValues)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (enableBit > (0xf))
    {
        ret = CDN_EINVAL;
    }
    else if (bitValues > (0xf))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txCrcPreCover preamble Crc coverage for Tx
 * @param[in] rxCrcPreCover preamble Crc coverage for Rx
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction51(const CEDI_PrivateData* pD, const CEDI_PreCrcCover txCrcPreCover, const CEDI_PreCrcCover rxCrcPreCover)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (txCrcPreCover != CEDI_PRE_CRC_NO_COVER) &&
        (txCrcPreCover != CEDI_PRE_CRC_7MS_COVER) &&
        (txCrcPreCover != CEDI_PRE_CRC_ALL8_COVER) &&
        (txCrcPreCover != CEDI_PRE_CRC_4MS_COVER)
    )
    {
        ret = CDN_EINVAL;
    }
    else if (
        (rxCrcPreCover != CEDI_PRE_CRC_NO_COVER) &&
        (rxCrcPreCover != CEDI_PRE_CRC_7MS_COVER) &&
        (rxCrcPreCover != CEDI_PRE_CRC_ALL8_COVER) &&
        (rxCrcPreCover != CEDI_PRE_CRC_4MS_COVER)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txCrcPreCover preamble Crc coverage for Tx
 * @param[in] rxCrcPreCover preamble Crc coverage for Rx
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction52(const CEDI_PrivateData* pD, const CEDI_PreCrcCover* txCrcPreCover, const CEDI_PreCrcCover* rxCrcPreCover)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (txCrcPreCover == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (rxCrcPreCover == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (*txCrcPreCover != CEDI_PRE_CRC_NO_COVER) &&
        (*txCrcPreCover != CEDI_PRE_CRC_7MS_COVER) &&
        (*txCrcPreCover != CEDI_PRE_CRC_ALL8_COVER) &&
        (*txCrcPreCover != CEDI_PRE_CRC_4MS_COVER)
    )
    {
        ret = CDN_EINVAL;
    }
    else if (
        (*rxCrcPreCover != CEDI_PRE_CRC_NO_COVER) &&
        (*rxCrcPreCover != CEDI_PRE_CRC_7MS_COVER) &&
        (*rxCrcPreCover != CEDI_PRE_CRC_ALL8_COVER) &&
        (*rxCrcPreCover != CEDI_PRE_CRC_4MS_COVER)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] cap pointer for returning supported capabilities, OR combination of CEDI_CAP_XXX flags
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction53(const CEDI_PrivateData* pD, const uint32_t* cap)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cap == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] mode enum selecting mode enable/disable. =CEDI_SERDES_LOOPBACK: select loopback mode in PHY transceiver, if available; =CEDI_LOCAL_LOOPBACK: select internal loopback mode. Tx and Rx should be disabled when enabling or disabling this mode. Only available if int_loopback defined; =CEDI_NO_LOOPBACK: disable loopback mode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction54(const CEDI_PrivateData* pD, const uint8_t mode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (mode != CEDI_NO_LOOPBACK) &&
        (mode != CEDI_LOCAL_LOOPBACK) &&
        (mode != CEDI_SERDES_LOOPBACK)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] maxTxSize pointer for returning array of sizes for queues
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction56(const CEDI_PrivateData* pD, const CEDI_FrameSize* maxTxSize)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (maxTxSize == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] bufAdd pointer to address of buffer
 * @param[in] length length of data in buffer
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction57(const CEDI_PrivateData* pD, const CEDI_BuffAddr* bufAdd, const uint32_t length)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_BuffAddrSF(bufAdd) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((length < (1)) || (length > (CEDI_TXD_LMASK)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] params pointer to struct for all parameters required by the function
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction58(const CEDI_PrivateData* pD, const CEDI_qTxBufParams* params)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_QTxBufParamsSF(params) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in,out] params pointer to struct for parameters to be returned. Not all fields are used - queueNum must be specified, and bufAdd and length are returned
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction59(const CEDI_PrivateData* pD, const CEDI_qTxBufParams* params)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (params == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] descData pointer for returning status & descriptor data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction61(const CEDI_PrivateData* pD, const CEDI_TxDescData* descData)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (descData == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txDStat - pointer to bit-field struct for decoded status fields
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction62(const CEDI_PrivateData* pD, const CEDI_TxDescStat* txDStat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (txDStat == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txStatus pointer to struct with fields for each flag
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction74(const CEDI_PrivateData* pD, const CEDI_TxStatus* txStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (txStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txQstatus pointer to struct with fields for each flag
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction75(const CEDI_PrivateData* pD, const CEDI_TxQStatus* txQstatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (txQstatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] resetStatus OR'd combination of CEDI_TXS_ bit-flags
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction76(const CEDI_PrivateData* pD, const uint32_t resetStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((resetStatus & ~(
                  CEDI_TXS_USED_READ |
                  CEDI_TXS_COLLISION |
                  CEDI_TXS_RETRY_EXC |
                  CEDI_TXS_FRAME_ERR |
                  CEDI_TXS_TX_COMPLETE |
                  CEDI_TXS_UNDERRUN |
                  CEDI_TXS_LATE_COLL |
                  CEDI_TXS_HRESP_ERR
              )) != 0)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] resetStatus OR'd combination of CEDI_TXSQ_ bit-flags
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction77(const CEDI_PrivateData* pD, const uint32_t resetStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((resetStatus & ~(
                  CEDI_TXSQ_TX_COMPLETE |
                  CEDI_TXSQ_USED_BIT_READ |
                  CEDI_TXSQ_BUFF_EX_MID
              )) != 0)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selects next-highest priority queue (queue B)
 * @param[out] enable returns: 1 if CBS enabled for the specified queue 0 if not enabled
 * @param[out] idleSlope pointer for returning the idleSlope value for selected queue.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction80(const CEDI_PrivateData* pD, const uint8_t qSel, const uint8_t* enable, const uint32_t* idleSlope)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (idleSlope == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (qSel > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 then enable IPG stretch, if =0 then disable
 * @param[in] multiplier multiplying factor applied to previous Tx frame length.  Ignored if enable equal 0.
 * @param[in] divisor after multiplying previous frame length, divide by (divisor+1) - if result>96 bits,
 *    this is used for the Tx IPG. Ignored if enable equal 0.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction81(const CEDI_PrivateData* pD, const uint8_t enable, const uint8_t multiplier, const uint8_t divisor)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (enable > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning enabled state: returns 1 if IPG stretch enabled, 0 if disabled.
 * @param[out] multiplier pointer for returning IPG multiplying factor
 * @param[out] divisor pointer for returning IPG divisor
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction82(const CEDI_PrivateData* pD, const uint8_t* enable, const uint8_t* multiplier, const uint8_t* divisor)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (multiplier == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (divisor == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] minIpg Minimum Inter Packet Gap
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction83(const CEDI_PrivateData* pD, const CEDI_MinIpg minIpg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (minIpg != CEDI_MINIMUM_IPG_12) &&
        (minIpg != CEDI_MINIMUM_IPG_24) &&
        (minIpg != CEDI_MINIMUM_IPG_32) &&
        (minIpg != CEDI_MINIMUM_IPG_CUSTOM)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable Returns true if txDefer is enabled
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction85(const CEDI_PrivateData* pD, const bool* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] buf pointer to address of buffer. Checked for word-alignment in 64/128-bit width cases.
 * @param[in] init if >0 then initialise the buffer data to all zeros
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction87(const CEDI_PrivateData* pD, const CEDI_BuffAddr* buf, const uint8_t init)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_BuffAddrSF(buf) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (init > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in,out] buf pointer to address of memory for new buffer to add to Rx descriptor queue; if data is available the buffer addresses for this are returned in buf, else if no data available then the new buffer can be re-used. Physical address of buffer is checked for word-alignment in 64/128-bit width cases.
 * @param[in] init if >0 then initialise the (new) buffer data to all zeros. Ignored if no data available.
 * @param[out] descData pointer for returning status & descriptor data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction90(const CEDI_PrivateData* pD, const CEDI_BuffAddr* buf, const uint8_t init, const CEDI_RxDescData* descData)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buf == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (descData == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (init > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] rxDStat pointer to bit-field struct for decoded status fields
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction91(const CEDI_PrivateData* pD, const CEDI_RxDescStat* rxDStat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (rxDStat == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] buf pointer to struct for returning virtual and physical addresses of buffer.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction97(const CEDI_PrivateData* pD, const CEDI_BuffAddr* buf)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buf == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] status pointer to struct with fields for each flag
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction99(const CEDI_PrivateData* pD, const CEDI_RxStatus* status)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (status == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] rxQstatus pointer to struct with fields for each flag
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction100(const CEDI_PrivateData* pD, const CEDI_RxQStatus* rxQstatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (rxQstatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] resetStatus OR'd combination of CEDI_RXS_ bit-flags
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction101(const CEDI_PrivateData* pD, const uint32_t resetStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((resetStatus & ~(
                  CEDI_RXS_NO_BUFF |
                  CEDI_RXS_FRAME_RX |
                  CEDI_RXS_OVERRUN |
                  CEDI_RXS_HRESP_ERR
              )) != 0)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] resetStatus OR'd combination of CEDI_RXSQ_ bit-flags
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction102(const CEDI_PrivateData* pD, const uint32_t resetStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((resetStatus & ~(
                  CEDI_RXSQ_FRAME_RX |
                  CEDI_RXSQ_USED_BIT_READ
              )) != 0)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] addr pointer to the 6-byte MAC address value to write
 * @param[in] specFilterType flag specifying whether to use MAC source or destination address to be compared for filtering. Source filter when =1.
 * @param[in] byteMask Bits masking out bytes of specific address from comparison.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction110(const CEDI_PrivateData* pD, const CEDI_MacAddress* addr, const uint8_t specFilterType, const uint8_t byteMask)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_MacAddressSF(addr) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (specFilterType > (1))
    {
        ret = CDN_EINVAL;
    }
    else if (byteMask > (0x3F))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] addr pointer to a 6-byte MAC address struct for returning the address value
 * @param[out] specFilterType flag specifying whether to use MAC source or destination address to be
 *    compared for filtering. =1 for source address
 * @param[out] byteMask "Bits masking out bytes of specific address from comparison.  When high,
 *    the associated address byte will be ignored. e.g. LSB of byteMask=1
 *    implies first byte received should not be compared."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction111(const CEDI_PrivateData* pD, const CEDI_MacAddress* addr, const uint8_t* specFilterType, const uint8_t* byteMask)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (addr == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (specFilterType == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (byteMask == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] mask pointer to the address mask value to write
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction112(const CEDI_PrivateData* pD, const CEDI_MacAddress* mask)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_MacAddressSF(mask) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mask pointer to a 6-byte MAC address struct for returning the mask value
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction113(const CEDI_PrivateData* pD, const CEDI_MacAddress* mask)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (mask == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] matchSel number of TypeID Match register, range 1 - 4
 * @param[in] typeId the Type ID match value to write ignored if enable equal 0
 * @param[in] enable if =1 enables the type matching for this ID, if =0 then disables type matching for this ID
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction115(const CEDI_PrivateData* pD, const uint8_t matchSel, const uint16_t typeId, const uint8_t enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((matchSel < (1)) || (matchSel > (4)))
    {
        ret = CDN_EINVAL;
    }
    else if (enable > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] matchSel number of TypeID Match register, range 1 - 4
 * @param[out] typeId pointer for returning the Type ID match value read ignored if disabled
 * @param[out] enable "pointer for returning enabled status: equal 1 if typeId matching is
 *    enabled for this register, equal 0 if disabled"
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction116(const CEDI_PrivateData* pD, const uint8_t matchSel, const uint16_t* typeId, const uint8_t* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (typeId == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((matchSel < (1)) || (matchSel > (4)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enable if =1 enables stacked VLAN processing, if =0 disables it
 * @param[in] vlanType sets user defined VLAN type for matching first VLAN tag. Ignored if enable equal 0.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction127(const CEDI_PrivateData* pD, const uint8_t enable, const uint16_t vlanType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (enable > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable pointer for returning Enabled field equal 1 if enabled equal 0 if disabled.
 * @param[out] vlanType pointer for returning VLAN type field
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction128(const CEDI_PrivateData* pD, const uint8_t* enable, const uint16_t* vlanType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (vlanType == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] hAddrTop most significant 32 bits of hash register
 * @param[in] hAddrBot least significant 32 bits of hash register
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction131(const CEDI_PrivateData* pD, const uint32_t hAddrTop, const uint32_t hAddrBot)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] hAddrTop pointer for returning most significant 32 bits of hash register
 * @param[out] hAddrBot pointer for returning least significant 32 bits of hash register
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction132(const CEDI_PrivateData* pD, const uint32_t* hAddrTop, const uint32_t* hAddrBot)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (hAddrTop == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (hAddrBot == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regNums points to a CEDI_NumScreeners struct for returning the numbers of registers
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction135(const CEDI_PrivateData* pD, const CEDI_NumScreeners* regNums)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (regNums == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regVals points to a CEDI_T1Screen struct with the match parameters to be written
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction136(const CEDI_PrivateData* pD, const CEDI_T1Screen* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_T1ScreenSF(regVals) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regVals points to a CEDI_T1Screen struct for returning the match parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction137(const CEDI_PrivateData* pD, const CEDI_T1Screen* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (regVals == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regVals points to a CEDI_T2Screen struct with the match parameters to be written
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction138(const CEDI_PrivateData* pD, const CEDI_T2Screen* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_T2ScreenSF(regVals) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regVals points to a CEDI_T2Screen struct for returning the match parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction139(const CEDI_PrivateData* pD, const CEDI_T2Screen* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (regVals == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] eTypeVal Ethertype compare value to write
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction140(const CEDI_PrivateData* pD, const uint16_t eTypeVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] eTypeVal pointer for returning the Ethertype compare value
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction141(const CEDI_PrivateData* pD, const uint16_t* eTypeVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (eTypeVal == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regVals points to a CEDI_T2Compare struct with the compare parameters to be written
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction142(const CEDI_PrivateData* pD, const CEDI_T2Compare* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_T2CompareSF(regVals) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regVals points to a CEDI_T2Compare struct for returning the compare parameters
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction143(const CEDI_PrivateData* pD, const CEDI_T2Compare* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (regVals == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] value transmit pause quantum value
 * @param[in] qpriority quantum priority, the priority for the pause quantum
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction149(const CEDI_PrivateData* pD, const uint16_t value, const uint8_t qpriority)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (qpriority > (CEDI_QUANTA_PRIORITY_MAX-1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] value returns transmit pause quantum value
 * @param[in] qpriority quantum priority,the priority for the pause quantum
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction150(const CEDI_PrivateData* pD, const uint16_t* value, const uint8_t qpriority)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (qpriority > (CEDI_QUANTA_PRIORITY_MAX-1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] rxAddr IP destination address
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction162(const CEDI_PrivateData* pD, const uint32_t rxAddr)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] timeVal pointer to CEDI_1588TimerVal struct with values to write to timer registers
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction166(const CEDI_PrivateData* pD, const CEDI_1588TimerVal* timeVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_1588TimerValSF(timeVal) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_1588TimerVal struct for returning timer registers contents
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction167(const CEDI_PrivateData* pD, const CEDI_1588TimerVal* timeVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (timeVal == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] nSecAdjust nanoseconds to adjust timer by: - if =1, enable time stamp storing, else disable (restore normal operation)
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction168(const CEDI_PrivateData* pD, const int32_t nSecAdjust)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((nSecAdjust < (-0x3FFFFFFF)) || (nSecAdjust > (0x3FFFFFFF)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] incSettings pointer to CEDI_TimerIncrement struct for defining how much to increment the timer each clock cycle
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction169(const CEDI_PrivateData* pD, const CEDI_TimerIncrement* incSettings)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_TimerIncrementSF(incSettings) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] incSettings pointer to a CEDI_TimerIncrement struct for returning how the timer increment values
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction170(const CEDI_PrivateData* pD, const CEDI_TimerIncrement* incSettings)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (incSettings == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] timeVal pointer to CEDI_TsuTimerVal struct with values to write to comparison registers
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction171(const CEDI_PrivateData* pD, const CEDI_TsuTimerVal* timeVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_TsuTimerValSF(timeVal) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] timeVal pointer to a CEDI_TsuTimerVal struct for returning comparison registers settings
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction172(const CEDI_PrivateData* pD, const CEDI_TsuTimerVal* timeVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (timeVal == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] txMode TX Descriptor timestamp insertion mode
 * @param[in] rxMode RX Descriptor timestamp insertion mode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction182(const CEDI_PrivateData* pD, const CEDI_TxTsMode txMode, const CEDI_RxTsMode rxMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (txMode != CEDI_TX_TS_DISABLED) &&
        (txMode != CEDI_TX_TS_PTP_EVENT_ONLY) &&
        (txMode != CEDI_TX_TS_PTP_ALL) &&
        (txMode != CEDI_TX_TS_ALL)
    )
    {
        ret = CDN_EINVAL;
    }
    else if (
        (rxMode != CEDI_RX_TS_DISABLED) &&
        (rxMode != CEDI_RX_TS_PTP_EVENT_ONLY) &&
        (rxMode != CEDI_RX_TS_PTP_ALL) &&
        (rxMode != CEDI_RX_TS_ALL)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] txMode TX Descriptor timestamp insertion mode
 * @param[out] rxMode RX Descriptor timestamp insertion mode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction183(const CEDI_PrivateData* pD, const CEDI_TxTsMode* txMode, const CEDI_RxTsMode* rxMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (txMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (rxMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] advDat pointer to CEDI_AnAdvPage struct for setting the advertised abilities register
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction188(const CEDI_PrivateData* pD, const CEDI_AnAdvPage* advDat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_AnAdvPageSF(advDat) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] advDat - pointer for returning the advertisement register data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction195(const CEDI_PrivateData* pD, const CEDI_AnAdvPage* advDat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (advDat == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] lpAbl pointer for returning the link partner ability data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction196(const CEDI_PrivateData* pD, const CEDI_LpAbilityPage* lpAbl)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (lpAbl == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] npDat - pointer to struct containing next page data to transmit
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction198(const CEDI_PrivateData* pD, const CEDI_AnNextPage* npDat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_AnNextPageSF(npDat) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] npDat - pointer to struct for returning next page register data.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction199(const CEDI_PrivateData* pD, const CEDI_AnNextPage* npDat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (npDat == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] npDat - pointer to CEDI_LpNextPage struct for returning link partner next page data.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction200(const CEDI_PrivateData* pD, const CEDI_LpNextPage* npDat)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (npDat == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] flags Combination of 2 bit-flags: if CEDI_MDIO_FLG_CLAUSE_45 present, specifies
 *    clause 45 PHY (else clause 22),
 *    if CEDI_MDIO_FLG_SET_ADDR present, specifies a set address operation (else
 *    do a write operation) - if not clause 45, this will be ignored.
 * @param[in] phyAddr PHY address
 * @param[in] devReg device type (clause 45) or register address (clause 22) - enum CEDI_MdioDevType
 *    is available to specify the device type
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction204(const CEDI_PrivateData* pD, const uint8_t flags, const uint8_t phyAddr, const uint8_t devReg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((flags & ~(
                  CEDI_MDIO_FLG_CLAUSE_45 |
                  CEDI_MDIO_FLG_SET_ADDR |
                  CEDI_MDIO_FLG_INC_ADDR
              )) != 0)
    {
        ret = CDN_EINVAL;
    }
    else if (phyAddr > (0x1F))
    {
        ret = CDN_EINVAL;
    }
    else if (devReg > (0x1F))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] regVals pointer to CEDI_WakeOnLanReg struct for register values to set
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction213(const CEDI_PrivateData* pD, const CEDI_WakeOnLanReg* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_WakeOnLanRegSF(regVals) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] regVals pointer to CEDI_WakeOnLanReg struct for returning WOL register contents
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction214(const CEDI_PrivateData* pD, const CEDI_WakeOnLanReg* regVals)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (regVals == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] lpiStats pointer to a CEDI_LpiStats struct for returning the LPI statistics.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction217(const CEDI_PrivateData* pD, const CEDI_LpiStats* lpiStats)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (lpiStats == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] hwCfg pointer to struct for receiving configuration data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction218(const CEDI_PrivateData* pD, const CEDI_DesignCfg* hwCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (hwCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] offs address offset to register
 * @param[out] data pointer for returning data read
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction234(const CEDI_PrivateData* pD, const uint32_t offs, const uint32_t* data)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (data == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (offs > (sizeof(struct emac_regs)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] offs address offset to register
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction235(const CEDI_PrivateData* pD, const uint32_t offs)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (offs > (sizeof(struct emac_regs)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] numQueues number of TX priority queues
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction236(const CEDI_PrivateData* pD, const uint8_t numQueues)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((numQueues < (1)) || (numQueues > (CEDI_MAX_TX_QUEUES)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] numQueues Number of RX priority queues. At least one queue must be enabled.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction238(const CEDI_PrivateData* pD, const uint8_t numQueues)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if ((numQueues < (1)) || (numQueues > (CEDI_MAX_RX_QUEUES)))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueSegAlloc new configuration of segment allocation
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction240(const CEDI_PrivateData* pD, const CEDI_QueueSegAlloc* queueSegAlloc)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_QueueSegAllocSF(queueSegAlloc) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] schedType new scheduler type
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction241(const CEDI_PrivateData* pD, const CEDI_TxSchedType schedType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (schedType != CEDI_TX_SCHED_TYPE_FIXED) &&
        (schedType != CEDI_TX_SCHED_TYPE_CBS) &&
        (schedType != CEDI_TX_SCHED_TYPE_DWRR) &&
        (schedType != CEDI_TX_SCHED_TYPE_ETS)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] schedType returned scheduler type
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction242(const CEDI_PrivateData* pD, const CEDI_TxSchedType* schedType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (schedType == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] enstTimeConfig new timing configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction249(const CEDI_PrivateData* pD, const CEDI_EnstTimeConfig* enstTimeConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_EnstTimeConfigSF(enstTimeConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enstTimeConfig new timing configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction250(const CEDI_PrivateData* pD, const CEDI_EnstTimeConfig* enstTimeConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enstTimeConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] enable if 1 then ENST is enabled, if 0 then ENST is disabled
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction252(const CEDI_PrivateData* pD, const uint8_t* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] linkFault pointer to read link fault status
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction262(const CEDI_PrivateData* pD, const CEDI_LinkFaultIndication* linkFault)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (linkFault == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] tagSize tag size 4 or 6 as enum
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction263(const CEDI_PrivateData* pD, const CEDI_RedundancyTagSize tagSize)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (tagSize != CEDI_REDUNDANCY_TAG_SIZE_4) &&
        (tagSize != CEDI_REDUNDANCY_TAG_SIZE_6)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] tagSize pointer to read current tag size
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction264(const CEDI_PrivateData* pD, const CEDI_RedundancyTagSize* tagSize)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (tagSize == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to enable disable  elimination frames
 * @param[in] enable if 1 then enable frame elimination, if 0 disable it.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction265(const CEDI_PrivateData* pD, const uint8_t queueNum, const uint8_t enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_RX_QUEUES))
    {
        ret = CDN_EINVAL;
    }
    else if (enable > (1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to check elimination frames
 * @param[out] enable if 1 then frame elimination is enabled, if 0 it is disabled
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction266(const CEDI_PrivateData* pD, const uint8_t queueNum, const uint8_t* enable)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (enable == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_RX_QUEUES))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to configure elimination frames feature
 * @param[in] fec configuration of frame elimination
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction269(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_FrameEliminationConfig* fec)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_RX_QUEUES))
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_FrameEliminationConfigSF(fec) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get frame elimination configuration
 * @param[out] fec configuration of frame elimination
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction270(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_FrameEliminationConfig* fec)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (fec == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_RX_QUEUES))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] fetc tag configuration of frame elimination
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction271(const CEDI_PrivateData* pD, const CEDI_FrameEliminationTagConfig* fetc)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_FrameEliminationTagConfSF(fetc) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] fetc tag configuration of frame elimination
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction272(const CEDI_PrivateData* pD, const CEDI_FrameEliminationTagConfig* fetc)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (fetc == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum priority queue to get statistics of FRER
 * @param[out] stats Frame elimination statistcs
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction274(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_FrameEliminationStats* stats)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (stats == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_RX_QUEUES))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] emacPrivateData express MAC private data object
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction275(const CEDI_PrivateData* pD, const CEDI_PrivateData** emacPrivateData)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (emacPrivateData == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] macType type of MAC private data object
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction277(const CEDI_PrivateData* pD, const CEDI_MacType* macType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (macType == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] preCfg configuration of preemption
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction278(const CEDI_PrivateData* pD, const CEDI_PreemptionConfig* preCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PreemptionConfigSF(preCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] preCfg read configuration of preemption
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction279(const CEDI_PrivateData* pD, const CEDI_PreemptionConfig* preCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (preCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mmslStats mmsl statistics
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction283(const CEDI_PrivateData* pD, const CEDI_MmslStats* mmslStats)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (mmslStats == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] mmslStatus mmsl status
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction284(const CEDI_PrivateData* pD, const CEDI_MmslStatus* mmslStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (mmslStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[in] lockupCfg lockup detection and recovery configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction285(const CEDI_PrivateData* pD, const CEDI_LockupConfig* lockupCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_LockupConfigSF(lockupCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance
 * @param[out] lockupCfg lockup detection and recovery configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction286(const CEDI_PrivateData* pD, const CEDI_LockupConfig* lockupCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (lockupCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] rxQFlushConfig Rx queue flush configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction291(const CEDI_PrivateData* pD, const CEDI_RxQFlushConfig* rxQFlushConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_RxQFlushConfigSF(rxQFlushConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[out] rxQFlushConfig Rx queue flush configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction292(const CEDI_PrivateData* pD, const CEDI_RxQFlushConfig* rxQFlushConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (rxQFlushConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] rateLimit Configuration of rate limiting for given screening register.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction294(const CEDI_PrivateData* pD, const CEDI_Type2ScreenerRateLimit* rateLimit)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_Type2ScreenerRateLimitSF(rateLimit) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[out] rateLimit Configuration of rate limiting for given screening register.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction295(const CEDI_PrivateData* pD, const CEDI_Type2ScreenerRateLimit* rateLimit)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (rateLimit == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] rxHighWatermark If not set to zero and receive SRAM fill level exceeds this value, a pause frame is transmitted.
 * @param[in] rxLowWatermark If not set to zero and receive SRAM fill level falls below this value, a zero-length pause frame is transmitted.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction297(const CEDI_PrivateData* pD, const uint16_t rxHighWatermark, const uint16_t rxLowWatermark)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[out] rxHighWatermark If not set to zero and receive SRAM fill level exceeds this value, a pause frame is transmitted.
 * @param[out] rxLowWatermark If not set to zero and receive SRAM fill level falls below this value, a zero-length pause frame is transmitted.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction298(const CEDI_PrivateData* pD, const uint16_t* rxHighWatermark, const uint16_t* rxLowWatermark)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (rxHighWatermark == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (rxLowWatermark == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] queueNum number of Tx queue
 * @param[in] axiQosConfig conifiguration of AXI QoS to set
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction299(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_AxiQosConfig* axiQosConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_TX_QUEUES-1))
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_AxiQosConfigSF(axiQosConfig) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD driver private state info specific to this instance.
 * @param[in] queueNum number of Tx queue
 * @param[out] axiQosConfig read conifiguration of AXI QoS
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction300(const CEDI_PrivateData* pD, const uint8_t queueNum, const CEDI_AxiQosConfig* axiQosConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (axiQosConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (queueNum > (CEDI_MAX_TX_QUEUES-1))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Specific driver's Private Data structure
 * @param[out] asfInfo returns information about ASF module. It informs if ASF is included to GEM,
 *    how many instances of ASF are included and what are the register base offsets if any.
 *    ASF module has own Core Driver which does not connected with GEM Core Driver.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction301(const CEDI_PrivateData* pD, const CEDI_AsfInfo* asfInfo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (asfInfo == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] watermarkLvl Pointer to struct with watermark levels (both: high and low)
 *    for queue.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction302(const CEDI_PrivateData* pD, const CEDI_WatermarkLvl* watermarkLvl)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_WatermarkLvlSF(watermarkLvl) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] watermarkLvl Pointer to struct with watermark levels (both: high and low)
 *    for queue.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction303(const CEDI_PrivateData* pD, const CEDI_WatermarkLvl* watermarkLvl)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (watermarkLvl == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] axiCfg Pointer to struct with axi configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction306(const CEDI_PrivateData* pD, const CEDI_AxiHostArbitrationCfg* axiCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_AxiHostArbitrationCfgSF(axiCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] axiCfg Pointer to axi configuration struct.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction307(const CEDI_PrivateData* pD, const CEDI_AxiHostArbitrationCfg* axiCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (axiCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] axiChannel AXI channel type
 * @param[in] axiBuffCfg Pointer to struct with AXI outstanding transaction buffer configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction308(const CEDI_PrivateData* pD, const CEDI_AxiChannelType axiChannel, const CEDI_AxiBuffCfg* axiBuffCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (axiChannel != CEDI_AXI_CHANNEL_READ) &&
        (axiChannel != CEDI_AXI_CHANNEL_WRITE)
    )
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_AxiBuffCfgSF(axiBuffCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] axiChannel AXI channel type
 * @param[out] axiBuffCfg Pointer to AXI outstanding transaction buffer configuration struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction309(const CEDI_PrivateData* pD, const CEDI_AxiChannelType axiChannel, const CEDI_AxiBuffCfg* axiBuffCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (axiBuffCfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (axiChannel != CEDI_AXI_CHANNEL_READ) &&
        (axiChannel != CEDI_AXI_CHANNEL_WRITE)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] serDes Value of SerDes rate
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction314(const CEDI_PrivateData* pD, const CEDI_SerdesRate serDes)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (serDes != CEDI_SERDES_RATE_5G) &&
        (serDes != CEDI_SERDES_RATE_10G) &&
        (serDes != CEDI_SERDES_RATE_25G)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] serDes Value of SerDes rate
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction315(const CEDI_PrivateData* pD, const CEDI_SerdesRate* serDes)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (serDes == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] opMode Operation mode for PCS25G
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction318(const CEDI_PrivateData* pD, const CEDI_Pcs25gOperationMode opMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (opMode != CEDI_TEST_PATTERN_MODE) &&
        (opMode != CEDI_MII_LOOPBACK_MODE) &&
        (opMode != CEDI_SCRAMBLER_LOOPBACK_MODE)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] opMode Operation mode for PCS25G
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction319(const CEDI_PrivateData* pD, const CEDI_Pcs25gOperationMode* opMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (opMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] patternMode Test pattern for PCS25G
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction320(const CEDI_PrivateData* pD, const CEDI_TestPatternMode patternMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (patternMode != CEDI_NORMAL_OPERATION) &&
        (patternMode != CEDI_SCRAMBLED_LOCAL_FAULT) &&
        (patternMode != CEDI_SCRAMBLED_IDLE) &&
        (patternMode != CEDI_SCRAMBLED_ZERO) &&
        (patternMode != CEDI_PRBS_9) &&
        (patternMode != CEDI_PRBS_31) &&
        (patternMode != CEDI_SQUARE_WAVE)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] patternMode Test pattern for PCS25G
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction321(const CEDI_PrivateData* pD, const CEDI_TestPatternMode* patternMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (patternMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] pcsStatus Status of PCS25G
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction324(const CEDI_PrivateData* pD, const CEDI_Pcs25gStatus* pcsStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pcsStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] testSeedReg Describes where (A or B) test pattern we be wrote
 * @param[in] testPatternSeed Struct with test pattern values
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction325(const CEDI_PrivateData* pD, const CEDI_TestSeedReg testSeedReg, const CEDI_TestPatternSeed* testPatternSeed)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (testSeedReg != CEDI_TEST_SEED_A) &&
        (testSeedReg != CEDI_TEST_SEED_B)
    )
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_TestPatternSeedSF(testPatternSeed) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] testSeedReg Describes from where (A or B) test pattern will be read
 * @param[out] testPatternSeed Struct to save test pattern values
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction326(const CEDI_PrivateData* pD, const CEDI_TestSeedReg testSeedReg, const CEDI_TestPatternSeed* testPatternSeed)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (testPatternSeed == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (testSeedReg != CEDI_TEST_SEED_A) &&
        (testSeedReg != CEDI_TEST_SEED_B)
    )
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[out] fecError Pointer to struct to save FEC error count
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction331(const CEDI_PrivateData* pD, const CEDI_FecError* fecError)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (fecError == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance
 * @param[in] pcsCfg Pointer to structure with PCS25G configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CEDI_SanityFunction346(const CEDI_PrivateData* pD, const CEDI_Pcs25gCfg* pcsCfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CEDI_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CEDI_Pcs25gCfgSF(pcsCfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRIC.CC-3 */
/* parasoft-end-suppress METRICS-18-3 */
