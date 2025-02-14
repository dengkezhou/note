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
 * sdio_phy.c
 * SD Host controller driver - PHY module
 *****************************************************************************/

#include "sdio_phy.h"
#include "sdio_host.h"
#include "sdio_utils.h"
#include "sdio_debug.h"
#include "cdn_errno.h"
#include "csdd_structs_if.h"

#ifndef SDIO_CFG_HOST_VER
#   error "SDIO_CFG_HOST_VER should be defined explicitly"
#endif

// --------------------------------------------------------------------------------------
static uint8_t GetPhyAddr(CSDD_PhyDelay phyDelayType, uint8_t *phySetAddr)
{
    uint8_t ret = EINVAL;
    size_t i;

    for (i = 0; i < (sizeof(phyDelayAddr) / sizeof(phyDelayAddr[0])); i++) {
        if (phyDelayAddr[i].phyDelayType == phyDelayType) {
            *phySetAddr = phyDelayAddr[i].address;
            ret = SDIO_ERR_NO_ERROR;
            break;
        }
    }
    if (ret != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Delay %d not found\n",
                     phyDelayAddr);

    }

    return ret;
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
static uint8_t GetPhyRegAddr(const CSDD_SDIO_Host* pSdioHost, uint8_t slotIndex, volatile uint32_t** regOffset)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

#if SDIO_CFG_HOST_VER == 3
    if (pSdioHost->SpecVersNumb > 4U) {
        status = CDN_ENOTSUP;
    } else {
        *regOffset = pSdioHost->RegOffset + SDIO_REG_HRS44 + (slotIndex * 4UL);
    }
#endif
#if SDIO_CFG_HOST_VER >= 4
    if (pSdioHost->SpecVersNumb < 4U) {
        status = CDN_ENOTSUP;
    } else {
        *regOffset = &pSdioHost->RegOffset->HRS.HRS04;
    }
#endif

    return (status);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
static uint8_t WritePhySet(const CSDD_SDIO_Host* pSdioHost,volatile uint32_t* RegOffset, uint8_t PhySetAddr, uint8_t PhySetVal)
{
    uint32_t PhyCfg;
    uint8_t Stat = SDIO_ERR_UNSUPORRTED_OPERATION;

    if (pSdioHost->hostCtrlVer < SDIO_HOST_VER_WTH_CCP) {

        // wait for acknowledge
        Stat = WaitForValue(RegOffset,
                            (uint32_t)HRS_PHY_ACKNOWLEDGE_REQUEST, 0, COMMANDS_TIMEOUT);
        if (Stat != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
        } else {

            //set data and address
            PhyCfg = HRS_PHY_UIS_ADDR_SET(PhySetAddr) | HRS_PHY_UIS_WDATA_SET(PhySetVal);
            CPS_REG_WRITE(RegOffset, PhyCfg);

            //send write request
            PhyCfg |= (uint32_t)HRS_PHY_WRITE_REQUEST;
            CPS_REG_WRITE(RegOffset, PhyCfg);

            // wait for acknowledge
            Stat = WaitForValue(RegOffset, (uint32_t)HRS_PHY_ACKNOWLEDGE_REQUEST, 1, COMMANDS_TIMEOUT);
            if (Stat != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
            } else {

                PhyCfg &= ~(uint32_t)HRS_PHY_WRITE_REQUEST;
                //clear write request
                CPS_REG_WRITE(RegOffset, PhyCfg);
                CPS_REG_WRITE(RegOffset, 0x0);
            }
        }
    }
    return (Stat);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
static uint8_t ReadPhySet(const CSDD_SDIO_Host* pSdioHost,volatile uint32_t* RegOffset, uint8_t PhySetAddr, uint8_t *PhySetVal)
{
    uint32_t PhyCfg;
    uint8_t Stat = SDIO_ERR_UNSUPORRTED_OPERATION;
    if (pSdioHost->hostCtrlVer < SDIO_HOST_VER_WTH_CCP) {
        // wait for acknowledge
        Stat = WaitForValue(RegOffset,
                            (uint32_t)HRS_PHY_ACKNOWLEDGE_REQUEST, 0, COMMANDS_TIMEOUT);
        if (Stat != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
        } else {

            //set address
            PhyCfg = HRS_PHY_UIS_ADDR_SET(PhySetAddr);
            CPS_REG_WRITE(RegOffset, PhyCfg);

            //send read request
            PhyCfg |= (uint32_t)HRS_PHY_READ_REQUEST;
            CPS_REG_WRITE(RegOffset, PhyCfg);

            // wait for acknowledge
            Stat = WaitForValue(RegOffset,
                                (uint32_t)HRS_PHY_ACKNOWLEDGE_REQUEST, 1, COMMANDS_TIMEOUT);
            if (Stat != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
            } else {

                PhyCfg = CPS_REG_READ(RegOffset);
                *PhySetVal = (uint8_t)HRS_PHY_UIS_RDATA_GET(PhyCfg);

                //clear request
                CPS_REG_WRITE(RegOffset, 0x00);
            }
        }
    }
    return (Stat);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
static uint8_t SDIO_Phy_PhySettings(const CSDD_SDIO_Host* pSdioHost,volatile uint32_t* RegOffset,
                                    const CSDD_PhyDelaySettings *PhyDelaySet)
{
    uint8_t Stat = SDIO_ERR_NO_ERROR;
    uint8_t PhySet;
    uint8_t i;

    const uint8_t addrAndVal[9][2] = {
        [0] = {UIS_ADDR_DEFAULT_SPEED,  PhyDelaySet->defaultSpeed},
        [1] = {UIS_ADDR_HIGH_SPEED,     PhyDelaySet->highSpeed},
        [2] = {UIS_ADDR_UHSI_SDR12,     PhyDelaySet->uhsiSdr12},
        [3] = {UIS_ADDR_UHSI_SDR25,     PhyDelaySet->uhsiSdr25},
        [4] = {UIS_ADDR_UHSI_SDR50,     PhyDelaySet->uhsiSdr50},
        [5] = {UIS_ADDR_UHSI_DDR50,     PhyDelaySet->uhsiDdr50},
        [6] = {UIS_ADDR_MMC_LEGACY,     PhyDelaySet->mmcLegacy},
        [7] = {UIS_ADDR_MMC_SDR,        PhyDelaySet->mmcSdr},
        [8] = {UIS_ADDR_MMC_DDR,        PhyDelaySet->mmcDdr}
    };

    for (i = 0; i < 9U; ++i) {
        Stat = WritePhySet(pSdioHost,RegOffset, addrAndVal[i][0], addrAndVal[i][1]);
        if (Stat != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
            break;
        }
    }

    if (Stat == SDIO_ERR_NO_ERROR) {
#ifdef UIS_ADDR_MMC_HS400
        Stat = WritePhySet(pSdioHost,RegOffset, UIS_ADDR_MMC_HS400, PhyDelaySet->mmcHs400);
        if (Stat) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
        } else
#endif
        {
            bool doBreak = false;
            for (i = 0; i < 9U; ++i) {
                Stat = ReadPhySet(pSdioHost,RegOffset, addrAndVal[i][0], &PhySet);
                if (Stat != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Stat);
                    doBreak = true;
                } else if (PhySet != addrAndVal[i][1]) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_HARDWARE_PROBLEM);
                    doBreak = true;
                } else {
                    continue;
                }

                if (doBreak) {
                    break;
                }
            }
        }
    }

    return (Stat);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
uint8_t SDIO_ReadPhySet(const CSDD_SDIO_Host* pSdioHost, uint8_t slotIndex, CSDD_PhyDelay delayType,
                        uint8_t *delayVal)
{
    volatile uint32_t* regOffset;
    uint8_t phySetAddr;
    uint8_t status;

    status = GetPhyAddr(delayType, &phySetAddr);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        status = GetPhyRegAddr(pSdioHost, slotIndex, &regOffset);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            status = ReadPhySet(pSdioHost,regOffset, phySetAddr, delayVal);
        }
    }

    return (status);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
uint8_t SDIO_WritePhySet(const CSDD_SDIO_Host* pSdioHost, uint8_t slotIndex, CSDD_PhyDelay delayType,
                         uint8_t delayVal)
{
    volatile uint32_t* regOffset;
    uint8_t phySetAddr;
    uint8_t status;

    status = GetPhyAddr(delayType, &phySetAddr);
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        status = GetPhyRegAddr(pSdioHost, slotIndex, &regOffset);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            status = WritePhySet(pSdioHost,regOffset, phySetAddr, delayVal);
        }
    }

    return (status);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
uint8_t SDIO_Phy_PhySettings_SDv4(const CSDD_SDIO_Host*             pSdioHost,
                                  const CSDD_PhyDelaySettings *PhyDelaySet)
{
    uint8_t status;
    if (pSdioHost->SpecVersNumb < 4U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        status = SDIO_Phy_PhySettings(pSdioHost,&pSdioHost->RegOffset->HRS.HRS04, PhyDelaySet);
    }

    return (status);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
uint8_t SDIO_Phy_PhySettings_SDv3(const CSDD_SDIO_Slot*             pSlot,
                                  const CSDD_PhyDelaySettings *PhyDelaySet)
{
    uint8_t status;
#if SDIO_CFG_HOST_VER == 3
    uint32_t RegOffset;
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;

    if (pSdioHost->SpecVersNumb > 3) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        RegOffset = (pSlot->SlotNr * 4) + SDIO_REG_HRS44 + pSdioHost->RegOffset;

        status = SDIO_Phy_PhySettings(pSdioHost,RegOffset, PhyDelaySet);
    }
#else
    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_UNSUPORRTED_OPERATION);
    status = SDIO_ERR_UNSUPORRTED_OPERATION;
#endif

    return (status);
}

uint32_t SDIO_CPhy_DLLReset(CSDD_SDIO_Host* pSdioHost, bool doReset)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);

    if (doReset) {
        regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, PHY_SW_RESET, regVal, 0);
    } else {
        regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, PHY_SW_RESET, regVal, 1);
    }

    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS09, regVal);

    /* if reset is released then wait until PHY init is completed */
    if (!doReset) {
        status = WaitForValue(&pSdioHost->RegOffset->HRS.HRS09,
                              HRS09_PHY_INT_COMPLETE, 1, COMMANDS_TIMEOUT);
    }

    return status;
}

void SDIO_CPhy_SetCPhyConfigIoDelay(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigIoDelay* ioDelay)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS07);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS07, RW_COMPENSATE, regVal, ioDelay->rwCompensate);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS07, IDELAY_VAL, regVal, ioDelay->idelayVal);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS07, regVal);
}

void SDIO_CPhy_GetCPhyConfigIoDelay(CSDD_SDIO_Host* pSdioHost,
                                    CSDD_CPhyConfigIoDelay* ioDelay)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS07);
    ioDelay->rwCompensate = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS07, RW_COMPENSATE, regVal));
    ioDelay->idelayVal = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS07, IDELAY_VAL, regVal));
}

void SDIO_CPhy_SetConfigLvsi(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigLvsi* lvsi)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, LVSI_TCKSEL, regVal, lvsi->lvsiTcksel);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, LVSI_CNT, regVal, lvsi->lvsiCnt);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS09, regVal);
}

void SDIO_CPhy_GetConfigLvsi(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigLvsi* lvsi)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);
    lvsi->lvsiTcksel = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS09, LVSI_TCKSEL, regVal));
    lvsi->lvsiCnt = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS09, LVSI_CNT, regVal));
}

void SDIO_CPhy_SetConfigDfiRd(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigDfiRd* dfiRd)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, RDCMD_EN, regVal, dfiRd->rdcmdEn);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, RDDATA_EN, regVal, dfiRd->rddataEn);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS09, regVal);

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS10);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS10, RDDATA_SWAP, regVal, dfiRd->rddataSwap);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS10, regVal);
}

void SDIO_CPhy_GetConfigDfiRd(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigDfiRd* dfiRd)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);
    dfiRd->rdcmdEn = (CPS_FLD_READ(SD4HC__HRS__HRS09, RDCMD_EN, regVal));
    dfiRd->rddataEn = (CPS_FLD_READ(SD4HC__HRS__HRS09, RDDATA_EN, regVal));

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS10);
    dfiRd->rddataSwap = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS10, RDDATA_SWAP, regVal));
}

void SDIO_CPhy_SetConfigOutputDelay(CSDD_SDIO_Host* pSdioHost,
                                    CSDD_CPhyConfigOutputDelay* outputDelay)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS16);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRDATA1_SDCLK_DLY, regVal, outputDelay->wrdata1SdclkDly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRDATA0_SDCLK_DLY, regVal, outputDelay->wrdata0SdclkDly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRCMD1_SDCLK_DLY, regVal, outputDelay->wrcmd1SdclkDly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRCMD0_SDCLK_DLY, regVal, outputDelay->wrcmd0SdclkDly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRDATA1_DLY, regVal, outputDelay->wrdata1Dly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRDATA0_DLY, regVal, outputDelay->wrdata0Dly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRCMD1_DLY, regVal, outputDelay->wrcmd1Dly);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS16, WRCMD0_DLY, regVal, outputDelay->wrcmd0Dly);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS16, regVal);
}


void SDIO_CPhy_GetConfigOutputDelay(CSDD_SDIO_Host* pSdioHost,
                                    CSDD_CPhyConfigOutputDelay* outputDelay)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS16);
    outputDelay->wrdata1SdclkDly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRDATA1_SDCLK_DLY, regVal));
    outputDelay->wrdata0SdclkDly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRDATA0_SDCLK_DLY, regVal));
    outputDelay->wrcmd1SdclkDly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRCMD1_SDCLK_DLY, regVal));
    outputDelay->wrcmd0SdclkDly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRCMD0_SDCLK_DLY, regVal));
    outputDelay->wrdata1Dly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRDATA1_DLY, regVal));
    outputDelay->wrdata0Dly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRDATA0_DLY, regVal));
    outputDelay->wrcmd1Dly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRCMD1_DLY, regVal));
    outputDelay->wrcmd0Dly = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS16, WRCMD0_DLY, regVal));
}

void SDIO_CPhy_SetExtMode(CSDD_SDIO_Host* pSdioHost, bool extendedWrMode,
                          bool extendedRdMode)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);
    if (extendedRdMode) {
        regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, EXTENDED_RD_MODE, regVal, 1);
    } else {
        regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, EXTENDED_RD_MODE, regVal, 0);
    }

    if (extendedWrMode) {
        regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, EXTENDED_WR_MODE, regVal, 1);
    } else {
        regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS09, EXTENDED_WR_MODE, regVal, 0);
    }

    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS09, regVal);
}

void SDIO_CPhy_GetExtMode(CSDD_SDIO_Host* pSdioHost, bool* extendedWrMode,
                          bool* extendedRdMode)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS09);
    *extendedRdMode = ((CPS_FLD_READ(SD4HC__HRS__HRS09, EXTENDED_RD_MODE, regVal)) == 1);
    *extendedWrMode = ((CPS_FLD_READ(SD4HC__HRS__HRS09, EXTENDED_WR_MODE, regVal)) == 1);

}

void SDIO_CPhy_SetSdclkAdj(CSDD_SDIO_Host* pSdioHost, uint8_t sdclkAdj)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS10);
    regVal = CPS_FLD_WRITE(SD4HC__HRS__HRS10, HCSDCLKADJ, regVal, sdclkAdj);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS10, regVal);

}

void SDIO_CPhy_GetSdclkAdj(CSDD_SDIO_Host* pSdioHost, uint8_t* sdclkAdj)
{
    uint32_t regVal;

    regVal = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS10);
    *sdclkAdj = (uint8_t)(CPS_FLD_READ(SD4HC__HRS__HRS10, HCSDCLKADJ, regVal));
}

