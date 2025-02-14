/******************************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 * This file contains Cadence Combo PHY Core Driver API implementation.
 *
 *****************************************************************************/

#include "cdn_errno.h"
#include "cps.h"
#include "cdn_log.h"
#ifndef CCP_MODE
#include "ccp_full_regs.h"
#include "ccpext_if.h"
#include "ccpext_structs_if.h"
#include "ccpext_sanity.h"
#else
#include "ccp_ls_regs.h"	
#endif
#include "ccp_if.h"
#include "ccp_structs_if.h"
#include "ccp_sanity.h"
#include "ccp_regs_macros.h"

#define  PHY_VERSION_REG  0x2070U


/* helper function to verify the HW version ID*/
static uint32_t checkMagicNumber(const CCP_PrivateData* pD) {
    uint32_t result = CDN_EOK;
    uint32_t reg_address = PHY_VERSION_REG;
    uint32_t magicNumber = (pD->cfg.readPhyReg(reg_address)) >> 16U;
    if (magicNumber != CCP_MAGIC_NUMBER) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Incorrect magic number! (read:0x%X, should be:0x%X)\n", magicNumber, CCP_MAGIC_NUMBER);
        result = CDN_EINVAL;
    } 
    return result;
}

/**
 * Get the driver's memory requirements to support the given
 * configuration.
 * @param[in] config driver/hardware configuration required
 * @param[out] memReq returns the size of memory allocations required
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CCP_Probe(const CCP_Config *config, CCP_SysReq *memReq)
{
    uint32_t status = CDN_EOK;

    /* check parameters */
    if (CCP_ProbeSF(config, memReq) != CDN_EOK)  {
        status = CDN_EINVAL;
    } else {
        memReq->privDataSize = (uint32_t) sizeof(CCP_PrivateData);
    }
    return status;
}

/**
 * Initialize the driver.
 * @param[in] pD 
 * @param[in] config specifies driver/hardware configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_Init(CCP_PrivateData* pD, const CCP_Config *config)
{
    uint32_t status = CDN_EOK;
	uint32_t regVal = 0U;

    /* check parameters */
    if (CCP_InitSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->cfg.readPhyReg = config->readPhyReg;
        pD->cfg.writePhyReg = config->writePhyReg;
        /* PHY registry access callback must be provided */
        if ((pD->cfg.readPhyReg == NULL) || (pD->cfg.writePhyReg == NULL)) {
            status = CDN_EINVAL;
        } else {
            status = checkMagicNumber(pD);
	    if(status == CDN_EOK) {
		uint32_t reg_address = offsetof(CCP_Regs, phy_features_reg);
		/* read register value */
		regVal = pD->cfg.readPhyReg(reg_address);
		uint8_t perBitDeskew = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, PER_BIT_DESKEW, regVal);
		uint8_t dfiClockRatio = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, DFI_CLOCK_RATIO, regVal);
#ifdef CCP_MODE
		// dfiClockRatio and perBitDeskew are zero for low speed 
		if((perBitDeskew != 0U) && (dfiClockRatio != 0U)) {
	 	    status = CDN_EINVAL;
		}
#else
		if((perBitDeskew == 0U) && (dfiClockRatio == 0U)) {
		    status = CDN_EINVAL;
		}
#endif
	    }
        }
    }
    return status;
}

/**
 * setter for phyDqTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDqTimingReg(CCP_PrivateData *pD, const CCP_PhyDqTimingReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyDqTimingRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dq_timing_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_OE_END, regVal, value->dataSelectOeEnd);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_OE_START, regVal, value->dataSelectOeStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_TSEL_END, regVal, value->dataSelectTselEnd);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_TSEL_START, regVal, value->dataSelectTselStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, DATA_CLKPERIOD_DELAY, regVal, value->dataClkperiodDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, IO_MASK_START, regVal, value->ioMaskStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, IO_MASK_END, regVal, value->ioMaskEnd);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQ_TIMING_REG, IO_MASK_ALWAYS_ON, regVal, value->ioMaskAlwaysOn);
        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for phyDqTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDqTimingReg(const CCP_PrivateData *pD, CCP_PhyDqTimingReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDqTimingRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dq_timing_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->dataSelectOeEnd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_OE_END, regVal));
        value->dataSelectOeStart = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_OE_START, regVal));
        value->dataSelectTselEnd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_TSEL_END, regVal));
        value->dataSelectTselStart = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, DATA_SELECT_TSEL_START, regVal));
        value->dataClkperiodDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, DATA_CLKPERIOD_DELAY, regVal));
        value->ioMaskStart = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, IO_MASK_START, regVal));
        value->ioMaskEnd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, IO_MASK_END, regVal));
        value->ioMaskAlwaysOn = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQ_TIMING_REG, IO_MASK_ALWAYS_ON, regVal));
    }
    return status;
}

/**
 * setter for phyDqsTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDqsTimingReg(CCP_PrivateData *pD, const CCP_PhyDqsTimingReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyDqsTimingRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dqs_timing_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_OE_END, regVal, value->dqsSelectOeEnd);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_OE_START, regVal, value->dqsSelectOeStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_TSEL_END, regVal, value->dqsSelectTselEnd);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_TSEL_START, regVal, value->dqsSelectTselStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, PHONY_DQS_SEL, regVal, value->phonyDqsSel);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, USE_PHONY_DQS_CMD, regVal, value->usePhonyDqsCmd);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, USE_PHONY_DQS, regVal, value->usePhonyDqs);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, USE_LPBK_DQS, regVal, value->useLpbkDqs);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, USE_EXT_LPBK_DQS, regVal, value->useExtLpbkDqs);
        regVal = CPS_FLD_WRITE(CCP__PHY_DQS_TIMING_REG, DQS_CLKPERIOD_DELAY, regVal, value->dqsClkPeriodDelay);
        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for phyDqsTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDqsTimingReg(const CCP_PrivateData *pD, CCP_PhyDqsTimingReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDqsTimingRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dqs_timing_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->dqsSelectOeEnd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_OE_END, regVal));
        value->dqsSelectOeStart = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_OE_START, regVal));
        value->dqsSelectTselEnd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_TSEL_END, regVal));
        value->dqsSelectTselStart = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, DQS_SELECT_TSEL_START, regVal));
        value->usePhonyDqs = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, USE_PHONY_DQS, regVal));
        value->usePhonyDqsCmd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, USE_PHONY_DQS_CMD, regVal));
        value->phonyDqsSel = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, PHONY_DQS_SEL, regVal));
        value->useLpbkDqs = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, USE_LPBK_DQS, regVal));
        value->useExtLpbkDqs = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, USE_EXT_LPBK_DQS, regVal));
        value->dqsClkPeriodDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_DQS_TIMING_REG, DQS_CLKPERIOD_DELAY, regVal));
    }
    return status;
}

/* internal function */
static uint32_t setLpbkGateFields(const CCP_PhyGateLpbkCtrlReg* value, uint32_t regValue) {
    uint32_t regVal = regValue;

    /* set tie fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_ERR_CHECK_TIMING, regVal, value->lpbkErrCheckTiming);
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_FAIL_MUXSEL, regVal, value->lpbkFailMuxsel);
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_INTERNAL, regVal, value->lpbk_internal);
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_EN, regVal, value->lpbkEn);
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, GATE_CFG_ALWAYS_ON, regVal, value->gateCfgAlwaysOn);
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, GATE_CFG_CLOSE, regVal, value->gateCfgClose);
    regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, GATE_CFG, regVal, value->gateCfg);
    return regVal;
}



/**
 * setter for phyGateLpbkCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyGateLpbkCtrlReg(CCP_PrivateData *pD, const CCP_PhyGateLpbkCtrlReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyGateLpbkCtrlRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_gate_lpbk_ctrl_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, SYNC_METHOD, regVal, value->syncMethod);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, SW_DQS_PHASE_BYPASS, regVal, value->swDqsPhaseBypass);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, EN_SW_HALF_CYCLE, regVal, value->enSwHalfCycle);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, SW_HALF_CYCLE_SHIFT, regVal, value->swHalfCycleShift);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, PARAM_PHASE_DETECT_SEL_OE, regVal, value->paramPhaseDetectSelOe);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, RD_DEL_SEL, regVal, value->rdDelSel);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, RD_DEL_SEL_EMPTY, regVal, value->rdDelSelEmpty);
        regVal = CPS_FLD_WRITE(CCP__PHY_GATE_LPBK_CTRL_REG, LOOPBACK_CONTROL, regVal, value->loopbackControl);
        regVal = setLpbkGateFields(value, regVal);
        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/* internal function */
static void getLpbkGateFields(CCP_PhyGateLpbkCtrlReg *value, uint32_t regValue) {

    uint32_t regVal = regValue;

    /* extract fields values */
    value->lpbkErrCheckTiming = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_ERR_CHECK_TIMING, regVal);
    value->lpbkFailMuxsel = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_FAIL_MUXSEL, regVal);
    value->lpbk_internal = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_INTERNAL, regVal);
    value->lpbkEn = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, LPBK_EN, regVal);
    value->gateCfgAlwaysOn = (uint8_t) (CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, GATE_CFG_ALWAYS_ON, regVal));
    value->gateCfgClose = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, GATE_CFG_CLOSE, regVal);
    value->gateCfg = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, GATE_CFG, regVal);
}


/**
 * getter for PhyGateLpbkCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyGateLpbkCtrlReg(const CCP_PrivateData *pD, CCP_PhyGateLpbkCtrlReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyGateLpbkCtrlRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_gate_lpbk_ctrl_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->syncMethod = (uint8_t) (CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, SYNC_METHOD, regVal));
        value->swDqsPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, SW_DQS_PHASE_BYPASS, regVal);
        value->enSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, EN_SW_HALF_CYCLE, regVal);
        value->swHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, SW_HALF_CYCLE_SHIFT, regVal);
        value->paramPhaseDetectSelOe = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, PARAM_PHASE_DETECT_SEL_OE, regVal);
        value->rdDelSel = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, RD_DEL_SEL, regVal);
        value->rdDelSelEmpty = (uint8_t) (CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, RD_DEL_SEL_EMPTY, regVal));
        value->loopbackControl = (uint8_t) CPS_FLD_READ(CCP__PHY_GATE_LPBK_CTRL_REG, LOOPBACK_CONTROL, regVal);
        getLpbkGateFields(value, regVal);
    }
    return status;
}

/**
 * setter for phyDllMasterCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDllMasterCtrlReg(CCP_PrivateData *pD, const CCP_PhyDllMasterCtrlReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyDllMasterCtrlRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_master_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_DLL_BYPASS_MODE, regVal, value->paramDllBypassMode);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_PHASE_DETECT_SEL, regVal, value->paramPhaseDetectSel);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_DLL_LOCK_NUM, regVal, value->paramDllLockNum);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_DLL_START_POINT, regVal, value->paramDllStartPoint);

        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyDllMasterCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllMasterCtrlReg(const CCP_PrivateData *pD, CCP_PhyDllMasterCtrlReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDllMasterCtrlRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_master_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        value->paramDllBypassMode = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_DLL_BYPASS_MODE, regVal);
        value->paramPhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_PHASE_DETECT_SEL, regVal);
        value->paramDllLockNum = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_DLL_LOCK_NUM, regVal);
        value->paramDllStartPoint = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_MASTER_CTRL_REG, PARAM_DLL_START_POINT, regVal);
    }
    return status;
}

/**
 * setter for phyDllSlaveCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyDllSlaveCtrlReg(CCP_PrivateData *pD, const CCP_PhyDllSlaveCtrlReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyDllSlaveCtrlRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_slave_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_SLAVE_CTRL_REG, READ_DQS_CMD_DELAY, regVal, value->readDqsCmdDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_SLAVE_CTRL_REG, CLK_WRDQS_DELAY, regVal, value->clkWrdqsDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_SLAVE_CTRL_REG, CLK_WR_DELAY, regVal, value->clkWrDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_DLL_SLAVE_CTRL_REG, READ_DQS_DELAY, regVal, value->readDqsDelay);
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyDllSlaveCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllSlaveCtrlReg(const CCP_PrivateData *pD, CCP_PhyDllSlaveCtrlReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDllSlaveCtrlRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_slave_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        value->readDqsCmdDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_SLAVE_CTRL_REG, READ_DQS_CMD_DELAY, regVal));
        value->clkWrdqsDelay = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_SLAVE_CTRL_REG, CLK_WRDQS_DELAY, regVal);
        value->clkWrDelay = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_SLAVE_CTRL_REG, CLK_WR_DELAY, regVal);
        value->readDqsDelay = (uint8_t) CPS_FLD_READ(CCP__PHY_DLL_SLAVE_CTRL_REG, READ_DQS_DELAY, regVal);
    }
    return status;
}

/**
 * setter for phyIeTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyIeTimingReg(CCP_PrivateData *pD, const CCP_PhyIeTimingReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyIeTimingRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_ie_timing_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/
        regVal = CPS_FLD_WRITE(CCP__PHY_IE_TIMING_REG, IE_ALWAYS_ON, regVal, value->ieAlwaysOn);
        regVal = CPS_FLD_WRITE(CCP__PHY_IE_TIMING_REG, DQ_IE_START, regVal, value->dqIeStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_IE_TIMING_REG, DQ_IE_STOP, regVal, value->dqIeStop);
        regVal = CPS_FLD_WRITE(CCP__PHY_IE_TIMING_REG, DQS_IE_START, regVal, value->dqsIeStart);
        regVal = CPS_FLD_WRITE(CCP__PHY_IE_TIMING_REG, DQS_IE_STOP, regVal, value->dqsIeStop);
        regVal = CPS_FLD_WRITE(CCP__PHY_IE_TIMING_REG, RDDATA_EN_IE_DLY, regVal, value->rddataEnIeDly);
        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyIeTimingReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyIeTimingReg(const CCP_PrivateData *pD, CCP_PhyIeTimingReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyIeTimingRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_ie_timing_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->ieAlwaysOn = (uint8_t) CPS_FLD_READ(CCP__PHY_IE_TIMING_REG, IE_ALWAYS_ON, regVal);
        value->dqIeStart = (uint8_t) CPS_FLD_READ(CCP__PHY_IE_TIMING_REG, DQ_IE_START, regVal);
        value->dqIeStop = (uint8_t) CPS_FLD_READ(CCP__PHY_IE_TIMING_REG, DQ_IE_STOP, regVal);
        value->dqsIeStart = (uint8_t) CPS_FLD_READ(CCP__PHY_IE_TIMING_REG, DQS_IE_START, regVal);
        value->dqsIeStop = (uint8_t) CPS_FLD_READ(CCP__PHY_IE_TIMING_REG, DQS_IE_STOP, regVal);
        value->rddataEnIeDly = (uint8_t) CPS_FLD_READ(CCP__PHY_IE_TIMING_REG, RDDATA_EN_IE_DLY, regVal);
    }
    return status;
}

/**
 * getter for phyObsReg0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyObsReg0(const CCP_PrivateData *pD, CCP_PhyObsReg0 *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyObsReg0SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_obs_reg_0);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->dqsCmdOverflow = (uint8_t) CPS_FLD_READ(CCP__PHY_OBS_REG_0, DQS_CMD_OVERFLOW, regVal);
        value->dqsCmdUnderrun = (uint8_t) CPS_FLD_READ(CCP__PHY_OBS_REG_0, DQS_CMD_UNDERRUN, regVal);
        value->dqsOverflow = (uint8_t) CPS_FLD_READ(CCP__PHY_OBS_REG_0, DQS_OVERFLOW, regVal);
        value->dqsUnderrun = (uint8_t) CPS_FLD_READ(CCP__PHY_OBS_REG_0, DQS_UNDERRUN, regVal);
        value->lpbkDqData = (uint16_t) CPS_FLD_READ(CCP__PHY_OBS_REG_0, LPBK_DQ_DATA, regVal);
        value->lpbkStatus = (uint8_t) CPS_FLD_READ(CCP__PHY_OBS_REG_0, LPBK_STATUS, regVal);
    }
    return status;
}

/**
 * getter for phyDllObsReg0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllObsReg0(const CCP_PrivateData *pD, CCP_PhyDllObsReg0 *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDllObsReg0SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_obs_reg_0);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->lockIncDbg = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, LOCK_INC_DBG, regVal));
        value->lockDecDbg = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, LOCK_DEC_DBG, regVal));
        value->dllLockValue = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, DLL_LOCK_VALUE, regVal));
        value->dllUnlockCount = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, DLL_UNLOCK_CNT, regVal));
        value->dllLockedMode = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, DLL_LOCKED_MODE, regVal));
        value->dllLock = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, DLL_LOCK, regVal));
    }
    return status;
}

/**
 * getter for phyDllObsReg1
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllObsReg1(const CCP_PrivateData *pD, CCP_PhyDllObsReg1 *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDllObsReg1SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_obs_reg_1);
        regVal = pD->cfg.readPhyReg(reg_address);
        value->decoderOutWr = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_1, DECODER_OUT_WR, regVal));
        value->decoderOutRdCmd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_1, DECODER_OUT_RD_CMD, regVal));
        value->decoderOutRd = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_1, DECODER_OUT_RD, regVal));
    }
    return status;
}

/**
 * getter for phyDllObsReg2
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyDllObsReg2(const CCP_PrivateData *pD, CCP_PhyDllObsReg2 *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyDllObsReg2SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_obs_reg_2);
        regVal = pD->cfg.readPhyReg(reg_address);
        value->decoderOutWrdqs = (uint8_t) (CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_2, DECODER_OUT_WRDQS, regVal));
    }
    return status;
}

/**
 * setter for phyStaticToggReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyStaticToggReg(CCP_PrivateData *pD, const CCP_PhyStaticToggReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyStaticToggRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_static_togg_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        regVal = CPS_FLD_WRITE(CCP__PHY_STATIC_TOGG_REG, READ_DQS_TOGG_ENABLE, regVal, value->readDqsToggEnable);
        regVal = CPS_FLD_WRITE(CCP__PHY_STATIC_TOGG_REG, STATIC_TOGG_ENABLE, regVal, value->staticToggEnable);
        regVal = CPS_FLD_WRITE(CCP__PHY_STATIC_TOGG_REG, STATIC_TOGG_GLOBAL_ENABLE, regVal, value->staticToggGlobalEnable);
        regVal = CPS_FLD_WRITE(CCP__PHY_STATIC_TOGG_REG, STATIC_TOG_CLK_DIV, regVal, value->staticTogClkDiv);
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyStaticToggReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyStaticToggReg(const CCP_PrivateData *pD, CCP_PhyStaticToggReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyStaticToggRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_static_togg_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        value->readDqsToggEnable = (uint8_t) CPS_FLD_READ(CCP__PHY_STATIC_TOGG_REG, READ_DQS_TOGG_ENABLE, regVal);
        value->staticToggEnable = (uint8_t) CPS_FLD_READ(CCP__PHY_STATIC_TOGG_REG, STATIC_TOGG_ENABLE, regVal);
        value->staticToggGlobalEnable = (uint8_t) CPS_FLD_READ(CCP__PHY_STATIC_TOGG_REG, STATIC_TOGG_GLOBAL_ENABLE, regVal);
        value->staticTogClkDiv = (uint16_t) CPS_FLD_READ(CCP__PHY_STATIC_TOGG_REG, STATIC_TOG_CLK_DIV, regVal);
    }
    return status;
}

/**
 * setter for PhyWrRdDeskewCmd
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyWrRdDeskewCmd(CCP_PrivateData *pD, const CCP_PhyWrRdDeskewCmd *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyWrRdDeskewCmdSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_rd_deskew_cmd_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/

        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_PHASE_DETECT_SEL, regVal, value->cmdPhaseDetectSel);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_SW_HALF_CYCLE_SHIFT, regVal, value->cmdSwHalfCycleShift);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_EN_SW_HALF_CYCLE, regVal, value->cmdEnSwHalfCycle);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_SW_DQ_PHASE_BYPASS, regVal, value->cmdSwDqPhaseBypass);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_CLKPERIOD_DELAY, regVal, value->cmdClkperiodDelay);

        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyWrRdDeskewCmd
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyWrRdDeskewCmd(const CCP_PrivateData *pD, CCP_PhyWrRdDeskewCmd *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyWrRdDeskewCmdSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_rd_deskew_cmd_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->cmdPhaseDetectSel = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_PHASE_DETECT_SEL, regVal));
        value->cmdSwHalfCycleShift = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_SW_HALF_CYCLE_SHIFT, regVal));
        value->cmdEnSwHalfCycle = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_EN_SW_HALF_CYCLE, regVal));
        value->cmdSwDqPhaseBypass = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_SW_DQ_PHASE_BYPASS, regVal));
        value->cmdClkperiodDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, CMD_CLKPERIOD_DELAY, regVal));
    }
    return status;
}

/**
 * setter for PhyWrDeskewPdCtrl0Reg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyWrDeskewPdCtrl0Dq0(CCP_PrivateData *pD, const CCP_PhyWrDeskewPdCtrl0Dq0 *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyWrDeskewPdCtrl0Dq0SF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_pd_ctrl_0_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
	regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_PHASE_DETECT_SEL, regVal, value->dq0PhaseDetectSel);
	regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_SW_HALF_CYCLE_SHIFT, regVal, value->dq0SwHalfCycleShift);
	regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_EN_SW_HALF_CYCLE, regVal, value->dq0EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_SW_DQ_PHASE_BYPASS, regVal, value->dq0SwDqPhaseBypass);
    
	pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyWrDeskewPdCtrl0RegDq0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyWrDeskewPdCtrl0Dq0(const CCP_PrivateData *pD, CCP_PhyWrDeskewPdCtrl0Dq0 *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyWrDeskewPdCtrl0Dq0SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_pd_ctrl_0_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
		
		 /* get DQ fields */
	value->dq0PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_PHASE_DETECT_SEL, regVal);
	value->dq0SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_SW_HALF_CYCLE_SHIFT, regVal);
	value->dq0EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_EN_SW_HALF_CYCLE, regVal);
	value->dq0SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ0_SW_DQ_PHASE_BYPASS, regVal);
    }
    return status;
}
/**
 * setter for phyCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyCtrlMain(CCP_PrivateData *pD, const CCP_PhyCtrlMain *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyCtrlMainSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);

        regVal = CPS_FLD_WRITE(CCP__PHY_CTRL_REG, SDR_DQS_VALUE, regVal, value->sdrDqsValue);
        regVal = CPS_FLD_WRITE(CCP__PHY_CTRL_REG, PHONY_DQS_TIMING, regVal, value->phonyDqsTiming);
        regVal = CPS_FLD_WRITE(CCP__PHY_CTRL_REG, CTRL_CLKPERIOD_DELAY, regVal, value->ctrlClkperiodDelay);
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyCtrlReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyCtrlMain(const CCP_PrivateData *pD, CCP_PhyCtrlMain *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0u;

    /* check parameters */
    if (CCP_GetPhyCtrlMainSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
		
        value->sdrDqsValue = (uint8_t) CPS_FLD_READ(CCP__PHY_CTRL_REG, SDR_DQS_VALUE, regVal);
        value->phonyDqsTiming = (uint8_t) CPS_FLD_READ(CCP__PHY_CTRL_REG, PHONY_DQS_TIMING, regVal);
        value->ctrlClkperiodDelay = (uint8_t) CPS_FLD_READ(CCP__PHY_CTRL_REG, CTRL_CLKPERIOD_DELAY, regVal);
    }
    return status;
}

/**
 * setter for phyTselReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyTselReg(CCP_PrivateData *pD, const CCP_PhyTselReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCP_SetPhyTselRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_tsel_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        regVal = CPS_FLD_WRITE(CCP__PHY_TSEL_REG, TSEL_OFF_VALUE_DATA, regVal, value->tselOffValueData);
        regVal = CPS_FLD_WRITE(CCP__PHY_TSEL_REG, TSEL_OFF_VALUE_DQS, regVal, value->tselOffValueDqs);
        regVal = CPS_FLD_WRITE(CCP__PHY_TSEL_REG, TSEL_RD_VALUE_DATA, regVal, value->tselRdValueData);
        regVal = CPS_FLD_WRITE(CCP__PHY_TSEL_REG, TSEL_RD_VALUE_DQS, regVal, value->tselRdValueDqs);
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyTselReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyTselReg(const CCP_PrivateData *pD, CCP_PhyTselReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyTselRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_tsel_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        value->tselOffValueData = (uint8_t) CPS_FLD_READ(CCP__PHY_TSEL_REG, TSEL_OFF_VALUE_DATA, regVal);
        value->tselOffValueDqs = (uint8_t) CPS_FLD_READ(CCP__PHY_TSEL_REG, TSEL_OFF_VALUE_DQS, regVal);
        value->tselRdValueData = (uint8_t) CPS_FLD_READ(CCP__PHY_TSEL_REG, TSEL_RD_VALUE_DATA, regVal);
        value->tselRdValueDqs = (uint8_t) CPS_FLD_READ(CCP__PHY_TSEL_REG, TSEL_RD_VALUE_DQS, regVal);
    }
    return status;
}

/**
 * setter for PhyGpioCtrl0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyGpioCtrl0(const CCP_PrivateData *pD, uint32_t value) {
    uint32_t status = CDN_EOK;

    /* check parameters */
    if ((CCP_SetPhyGpioCtrl0SF(pD) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_gpio_ctrl_0);
        pD->cfg.writePhyReg(reg_address, value);
    }
    return status;
}

/**
 * setter for PhyGpioCtrl1
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_SetPhyGpioCtrl1(const CCP_PrivateData *pD, uint32_t value) {
    uint32_t status = CDN_EOK;

    /* check parameters */
    if ((CCP_SetPhyGpioCtrl1SF(pD) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_gpio_ctrl_1);
        pD->cfg.writePhyReg(reg_address, value);
    }
    return status;
}

/**
 * getter for PhyGpioStatus0
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyGpioStatus0(const CCP_PrivateData *pD, uint32_t *value) {
    uint32_t status = CDN_EOK;

    /* check parameters */
    if (CCP_GetPhyGpioStatus0SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_gpio_status_0);
        *value = pD->cfg.readPhyReg(reg_address);
    }
    return status;
}

/**
 * getter for PhyGpioStatus1
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyGpioStatus1(const CCP_PrivateData *pD, uint32_t *value) {
    uint32_t status = CDN_EOK;

    /* check parameters */
    if (CCP_GetPhyGpioStatus1SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_gpio_status_1);
        *value = pD->cfg.readPhyReg(reg_address);
    }
    return status;
}
/* internal function */
static void getPhyFeaturesFields(CCP_PhyFeaturesReg *value, uint32_t regValue) {

    uint32_t regVal = regValue;

    /* extract fields values */
    value->aging = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, AGING, regVal);
    value->dllTapNum = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, DLL_TAP_NUM, regVal);
    value->bankNum = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, BANK_NUM, regVal);
    value->sdEmmc = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, SD_EMMC, regVal);
    value->xspi = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, XSPI, regVal);
    value->sdr16Bit = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, SDR_16BIT, regVal);
    value->onfi41 = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, ONFI_41, regVal);
    value->onfi40 = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, ONFI_40, regVal);
}

/**
 * getter for PhyFeaturesReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_GetPhyFeaturesReg(const CCP_PrivateData *pD, CCP_PhyFeaturesReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCP_GetPhyFeaturesRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_features_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->asfSup = (uint8_t) (CPS_FLD_READ(CCP__PHY_FEATURES_REG, ASF_SUP, regVal));
        value->pllSup = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, PLL_SUP, regVal);
        value->jtagSup = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, JTAG_SUP, regVal);
        value->extLpbkDqs = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, EXT_LPBK_DQS, regVal);
        value->regIntf = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, REG_INTF, regVal);
        value->perBitDeskew = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, PER_BIT_DESKEW, regVal);
        value->dfiClockRatio = (uint8_t) CPS_FLD_READ(CCP__PHY_FEATURES_REG, DFI_CLOCK_RATIO, regVal);
        getPhyFeaturesFields(value, regVal);
    }
    return status;
}
/**
 * Waits until Phy DLL locked bit is set.
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] locked PHY DLL lock status
 * @param[in] delayNs Delay in nanoseconds
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCP_WaitForDllLock(const CCP_PrivateData *pD, uint32_t *locked, uint32_t delayNs) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;
    uint32_t delay = delayNs;

    /* check parameters */
    if (CCP_WaitForDllLockSF(pD, locked) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_dll_obs_reg_0);
        regVal = pD->cfg.readPhyReg(reg_address);
        *locked = CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, DLL_LOCK, regVal);

        /* Waiting for PHY Dll lock bit if necessary */
        while ((*locked == 0U) && (delay > 0U)) {
            CPS_DelayNs(1U);
            delay--;
            regVal = pD->cfg.readPhyReg(reg_address);
            *locked = CPS_FLD_READ(CCP__PHY_DLL_OBS_REG_0, DLL_LOCK, regVal);
        }
    }
    return status;
}
#ifndef CCP_MODE
/**
 * setter for PhyWrRdDeskewCmdExt
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrRdDeskewCmdExt(CCP_PrivateData *pD, const CCPEXT_PhyWrRdDeskewCmdExt *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCPEXT_SetPhyWrRdDeskewCmdExSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_rd_deskew_cmd_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, WR_CMD_DESKEW_DELAY, regVal, value->wrCmdDeskewDelay);

        regVal = CPS_FLD_WRITE(CCP__PHY_WR_RD_DESKEW_CMD_REG, RD_CMD_DESKEW_DELAY, regVal, value->rdCmdDeskewDelay);

        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyWrRdDeskewCmdExt
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrRdDeskewCmdExt(const CCP_PrivateData *pD, CCPEXT_PhyWrRdDeskewCmdExt *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCPEXT_GetPhyWrRdDeskewCmdExSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_rd_deskew_cmd_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */

        value->wrCmdDeskewDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, WR_CMD_DESKEW_DELAY, regVal));
        value->rdCmdDeskewDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_RD_DESKEW_CMD_REG, RD_CMD_DESKEW_DELAY, regVal));

    }
    return status;
}
/* internal function */
static uint32_t setCtrl0Dq1(const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value, uint32_t regValue) {
    uint32_t regVal = regValue;

	/* set DQ1 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_PHASE_DETECT_SEL, regVal, value->dq1PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_SW_HALF_CYCLE_SHIFT, regVal, value->dq1SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_EN_SW_HALF_CYCLE, regVal, value->dq1EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_SW_DQ_PHASE_BYPASS, regVal, value->dq1SwDqPhaseBypass);
    
    return regVal;
}
/* internal function */
static uint32_t setCtrl0Dq2Dq3(const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value, uint32_t regValue) {
    uint32_t regVal = regValue;

    /* set DQ2 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_PHASE_DETECT_SEL, regVal, value->dq2PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_SW_HALF_CYCLE_SHIFT, regVal, value->dq2SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_EN_SW_HALF_CYCLE, regVal, value->dq2EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_SW_DQ_PHASE_BYPASS, regVal, value->dq2SwDqPhaseBypass);

    /* set DQ3 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_PHASE_DETECT_SEL, regVal, value->dq3PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_SW_HALF_CYCLE_SHIFT, regVal, value->dq3SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_EN_SW_HALF_CYCLE, regVal, value->dq3EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_SW_DQ_PHASE_BYPASS, regVal, value->dq3SwDqPhaseBypass);

    return regVal;
}
/**
 * setter for PhyWrDeskewPdCtrl0Reg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrDeskewPdCtrl0Dqx(CCP_PrivateData *pD, const CCPEXT_PhyWrDeskewPdCtrl0Dqx *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCPEXT_SetPhyWrDeskewPdCtrl0SF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_pd_ctrl_0_reg);
        regVal = pD->cfg.readPhyReg(reg_address);

	regVal = setCtrl0Dq1(value, regVal);
    regVal = setCtrl0Dq2Dq3(value, regVal);
    pD->cfg.writePhyReg(reg_address, regVal);
	
    }
    return status;
}

/* internal function */
static void getCtrl0Dq1(CCPEXT_PhyWrDeskewPdCtrl0Dqx *value, uint32_t regValue) {

    uint32_t regVal = regValue;

    /* get DQ1 fields */
    value->dq1PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_PHASE_DETECT_SEL, regVal);
    value->dq1SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq1EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_EN_SW_HALF_CYCLE, regVal);
    value->dq1SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ1_SW_DQ_PHASE_BYPASS, regVal);
}

/* internal function */
static void getCtrl0Dq2Dq3(CCPEXT_PhyWrDeskewPdCtrl0Dqx *value, uint32_t regValue) {

    uint32_t regVal = regValue;

    /* get DQ2 fields */
    value->dq2PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_PHASE_DETECT_SEL, regVal);
    value->dq2SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq2EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_EN_SW_HALF_CYCLE, regVal);
    value->dq2SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ2_SW_DQ_PHASE_BYPASS, regVal);

    /* get DQ3 fields */
    value->dq3PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_PHASE_DETECT_SEL, regVal);
    value->dq3SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq3EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_EN_SW_HALF_CYCLE, regVal);
    value->dq3SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_0_REG, DQ3_SW_DQ_PHASE_BYPASS, regVal);
}

/**
 * getter for PhyWrDeskewPdCtrl0RegDqx
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrDeskewPdCtrl0Dqx(const CCP_PrivateData *pD, CCPEXT_PhyWrDeskewPdCtrl0Dqx *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCPEXT_GetPhyWrDeskewPdCtrl0SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_pd_ctrl_0_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
		
        getCtrl0Dq1(value, regVal);
        getCtrl0Dq2Dq3(value, regVal);

    }
    return status;
}
/**
 * setter for PhyWrDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrDeskewReg(CCP_PrivateData *pD, const CCPEXT_PhyWrDeskewReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCPEXT_SetPhyWrDeskewRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* preparing new value*/
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ0_DESKEW_DELAY, regVal, value->wrDq0DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ1_DESKEW_DELAY, regVal, value->wrDq1DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ2_DESKEW_DELAY, regVal, value->wrDq2DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ3_DESKEW_DELAY, regVal, value->wrDq3DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ4_DESKEW_DELAY, regVal, value->wrDq4DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ5_DESKEW_DELAY, regVal, value->wrDq5DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ6_DESKEW_DELAY, regVal, value->wrDq6DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_REG, WR_DQ7_DESKEW_DELAY, regVal, value->wrDq7DeskwDelay);
        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyWrDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrDeskewReg(const CCP_PrivateData *pD, CCPEXT_PhyWrDeskewReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCPEXT_GetPhyWrDeskewRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->wrDq0DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ0_DESKEW_DELAY, regVal));
        value->wrDq1DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ1_DESKEW_DELAY, regVal));
        value->wrDq2DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ2_DESKEW_DELAY, regVal));
        value->wrDq3DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ3_DESKEW_DELAY, regVal));
        value->wrDq4DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ4_DESKEW_DELAY, regVal));
        value->wrDq5DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ5_DESKEW_DELAY, regVal));
        value->wrDq6DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ6_DESKEW_DELAY, regVal));
        value->wrDq7DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_WR_DESKEW_REG, WR_DQ7_DESKEW_DELAY, regVal));
    }
    return status;
}

/**
 * setter for PhyRdDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyRdDeskewReg(CCP_PrivateData *pD, const CCPEXT_PhyRdDeskewReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCPEXT_SetPhyRdDeskewRegSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_rd_deskew_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ0_DESKEW_DELAY, regVal, value->rdDq0DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ1_DESKEW_DELAY, regVal, value->rdDq1DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ2_DESKEW_DELAY, regVal, value->rdDq2DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ3_DESKEW_DELAY, regVal, value->rdDq3DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ4_DESKEW_DELAY, regVal, value->rdDq4DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ5_DESKEW_DELAY, regVal, value->rdDq5DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ6_DESKEW_DELAY, regVal, value->rdDq6DeskwDelay);
        regVal = CPS_FLD_WRITE(CCP__PHY_RD_DESKEW_REG, RD_DQ7_DESKEW_DELAY, regVal, value->rdDq7DeskwDelay);
        /* write register value */
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/**
 * getter for PhyRdDeskewReg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyRdDeskewReg(const CCP_PrivateData *pD, CCPEXT_PhyRdDeskewReg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCPEXT_GetPhyRdDeskewRegSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_rd_deskew_reg);
        /* read register value */
        regVal = pD->cfg.readPhyReg(reg_address);
        /* extract fields values */
        value->rdDq0DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ0_DESKEW_DELAY, regVal));
        value->rdDq1DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ1_DESKEW_DELAY, regVal));
        value->rdDq2DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ2_DESKEW_DELAY, regVal));
        value->rdDq3DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ3_DESKEW_DELAY, regVal));
        value->rdDq4DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ4_DESKEW_DELAY, regVal));
        value->rdDq5DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ5_DESKEW_DELAY, regVal));
        value->rdDq6DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ6_DESKEW_DELAY, regVal));
        value->rdDq7DeskwDelay = (uint8_t) (CPS_FLD_READ(CCP__PHY_RD_DESKEW_REG, RD_DQ7_DESKEW_DELAY, regVal));
    }

    return status;
}

/* internal function */
static uint32_t setCtrl1Dq4Dq5(const CCPEXT_PhyWrDeskewPdCtrl1Reg* value, uint32_t regValue) {
    uint32_t regVal = regValue;

    /* set DQ4 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_PHASE_DETECT_SEL, regVal, value->dq4PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_SW_HALF_CYCLE_SHIFT, regVal, value->dq4SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_EN_SW_HALF_CYCLE, regVal, value->dq4EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_SW_DQ_PHASE_BYPASS, regVal, value->dq4SwDqPhaseBypass);

    /* set DQ5 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_PHASE_DETECT_SEL, regVal, value->dq5PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_SW_HALF_CYCLE_SHIFT, regVal, value->dq5SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_EN_SW_HALF_CYCLE, regVal, value->dq5EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_SW_DQ_PHASE_BYPASS, regVal, value->dq5SwDqPhaseBypass);

    return regVal;
}

/* internal function */
static uint32_t setCtrl1Dq6Dq7(const CCPEXT_PhyWrDeskewPdCtrl1Reg* value, uint32_t regValue) {
    uint32_t regVal = regValue;

    /* set DQ6 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_PHASE_DETECT_SEL, regVal, value->dq6PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_SW_HALF_CYCLE_SHIFT, regVal, value->dq6SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_EN_SW_HALF_CYCLE, regVal, value->dq6EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_SW_DQ_PHASE_BYPASS, regVal, value->dq6SwDqPhaseBypass);

    /* set DQ7 fields */
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_PHASE_DETECT_SEL, regVal, value->dq7PhaseDetectSel);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_SW_HALF_CYCLE_SHIFT, regVal, value->dq7SwHalfCycleShift);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_EN_SW_HALF_CYCLE, regVal, value->dq7EnSwHalfCycle);
    regVal = CPS_FLD_WRITE(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_SW_DQ_PHASE_BYPASS, regVal, value->dq7SwDqPhaseBypass);
    return regVal;
}

/**
 * setter for PhyWrDeskewPdCtrl1Reg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyWrDeskewPdCtrl1Reg(CCP_PrivateData *pD, const CCPEXT_PhyWrDeskewPdCtrl1Reg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCPEXT_SetPhyWrDeskewPdCtrl1SF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_pd_ctrl_1_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        regVal = setCtrl1Dq4Dq5(value, regVal);
        regVal = setCtrl1Dq6Dq7(value, regVal);
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

/* internal function */
static void getCtrl1Dq4Dq5(CCPEXT_PhyWrDeskewPdCtrl1Reg *value, uint32_t regValue) {

    uint32_t regVal = regValue;

    /* get DQ4 fields */
    value->dq4PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_PHASE_DETECT_SEL, regVal);
    value->dq4SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq4EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_EN_SW_HALF_CYCLE, regVal);
    value->dq4SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ4_SW_DQ_PHASE_BYPASS, regVal);

    /* get DQ5 fields */
    value->dq5PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_PHASE_DETECT_SEL, regVal);
    value->dq5SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq5EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_EN_SW_HALF_CYCLE, regVal);
    value->dq5SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ5_SW_DQ_PHASE_BYPASS, regVal);
}

/* internal function */
static void getCtrl1Dq6Dq7(CCPEXT_PhyWrDeskewPdCtrl1Reg *value, uint32_t regValue) {

    uint32_t regVal = regValue;

    /* get DQ6 fields */
    value->dq6PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_PHASE_DETECT_SEL, regVal);
    value->dq6SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq6EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_EN_SW_HALF_CYCLE, regVal);
    value->dq6SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ6_SW_DQ_PHASE_BYPASS, regVal);

    /* set DQ7 fields */
    value->dq7PhaseDetectSel = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_PHASE_DETECT_SEL, regVal);
    value->dq7SwHalfCycleShift = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_SW_HALF_CYCLE_SHIFT, regVal);
    value->dq7EnSwHalfCycle = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_EN_SW_HALF_CYCLE, regVal);
    value->dq7SwDqPhaseBypass = (uint8_t) CPS_FLD_READ(CCP__PHY_WR_DESKEW_PD_CTRL_1_REG, DQ7_SW_DQ_PHASE_BYPASS, regVal);

}
/**
 * getter for PhyWrDeskewPdCtrl1Reg
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyWrDeskewPdCtrl1Reg(const CCP_PrivateData *pD, CCPEXT_PhyWrDeskewPdCtrl1Reg *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCPEXT_GetPhyWrDeskewPdCtrl1SF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_wr_deskew_pd_ctrl_1_reg);
        regVal = pD->cfg.readPhyReg(reg_address);
        getCtrl1Dq4Dq5(value, regVal);
        getCtrl1Dq6Dq7(value, regVal);
    }
    return status;
}
/**
 * getter for LowFreqSel
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_GetPhyCtrlLowFreqSel(const CCP_PrivateData *pD, CCPEXT_PhyCtrlLowFreqSel *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check parameters */
    if (CCPEXT_GetPhyCtrlLowFreqSelSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);

        value->lowFreqSel = (uint8_t) (CPS_FLD_READ(CCP__PHY_CTRL_REG, LOW_FREQ_SEL, regVal));

    }
    return status;
}
/**
 * setter for LowFreqSel
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CCPEXT_SetPhyCtrlLowFreqSel(CCP_PrivateData *pD, const CCPEXT_PhyCtrlLowFreqSel *value) {
    uint32_t status = CDN_EOK;
    uint32_t regVal = 0U;

    /* check parameters */
    if ((CCPEXT_SetPhyCtrlLowFreqSelSF(pD, value) != CDN_EOK)) {
        status = CDN_EINVAL;
    } else {
        uint32_t reg_address = offsetof(CCP_Regs, phy_ctrl_reg);
        regVal = pD->cfg.readPhyReg(reg_address);

        regVal = CPS_FLD_WRITE(CCP__PHY_CTRL_REG, LOW_FREQ_SEL, regVal, value->lowFreqSel);
		
        pD->cfg.writePhyReg(reg_address, regVal);
    }
    return status;
}

#endif
