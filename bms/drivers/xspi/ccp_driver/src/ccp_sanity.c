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
 * Cadence Combo PHY Core Driver
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
#include "ccp_ls_regs.h"
#include "ccp_structs_if.h"
#include "ccp_sanity.h"

/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_ConfigSF(const CCP_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
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
uint32_t CCP_PrivateDataSF(const CCP_PrivateData *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct PhyDqTimingReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyDqTimingRegSF(const CCP_PhyDqTimingReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->ioMaskAlwaysOn > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ioMaskEnd > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ioMaskStart > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataSelectTselStart > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataSelectTselEnd > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataSelectOeStart > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataSelectOeEnd > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyDqsTimingReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyDqsTimingRegSF(const CCP_PhyDqsTimingReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dqsClkPeriodDelay > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->useExtLpbkDqs > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->useLpbkDqs > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->usePhonyDqs > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->usePhonyDqsCmd > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->phonyDqsSel > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsSelectTselStart > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsSelectTselEnd > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsSelectOeStart > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsSelectOeEnd > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyGateLpbkCtrlReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyGateLpbkCtrlRegSF(const CCP_PhyGateLpbkCtrlReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->syncMethod > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->swDqsPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->swHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->paramPhaseDetectSelOe > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDelSel > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDelSelEmpty > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpbkErrCheckTiming > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpbkFailMuxsel > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->loopbackControl > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpbk_internal > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpbkEn > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->gateCfgAlwaysOn > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->gateCfgClose > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->gateCfg > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyDllMasterCtrlReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyDllMasterCtrlRegSF(const CCP_PhyDllMasterCtrlReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->paramDllBypassMode > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->paramPhaseDetectSel > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->paramDllLockNum > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyDllSlaveCtrlReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyDllSlaveCtrlRegSF(const CCP_PhyDllSlaveCtrlReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct PhyIeTimingReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyIeTimingRegSF(const CCP_PhyIeTimingReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->ieAlwaysOn > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqIeStart > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqIeStop > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsIeStart > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dqsIeStop > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rddataEnIeDly > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyStaticToggReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyStaticToggRegSF(const CCP_PhyStaticToggReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->readDqsToggEnable > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->staticToggEnable > (0x1FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->staticToggGlobalEnable > (0x1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyWrRdDeskewCmd
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyWrRdDeskewCmdSF(const CCP_PhyWrRdDeskewCmd *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->cmdClkperiodDelay > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->cmdSwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->cmdEnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->cmdSwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->cmdPhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyWrDeskewPdCtrl0Dq0
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyWrDeskewPdCtrl0Dq0SF(const CCP_PhyWrDeskewPdCtrl0Dq0 *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dq0SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq0EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq0SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq0PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyCtrlMain
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyCtrlMainSF(const CCP_PhyCtrlMain *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->sdrDqsValue > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->phonyDqsTiming > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ctrlClkperiodDelay > (0x1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyTselReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCP_PhyTselRegSF(const CCP_PhyTselReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->tselOffValueData > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->tselRdValueData > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->tselOffValueDqs > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->tselRdValueDqs > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] config "Driver/hardware configuration required."
 * @param[out] memReq "Returns the size of memory allocations required."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction1(const CCP_Config* config, const CCP_SysReq* memReq)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (memReq == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_ConfigSF(config) == CDN_EINVAL)
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
 * @param[in] pD "Memory pointer to the uninitialized private data of the size specified by probe."
 * @param[in] config "Specifies driver/hardware configuration."
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction2(const CCP_PrivateData* pD, const CCP_Config* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_ConfigSF(config) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction3(const CCP_PrivateData* pD, const CCP_PhyDqTimingReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyDqTimingRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction4(const CCP_PrivateData* pD, const CCP_PhyDqTimingReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction5(const CCP_PrivateData* pD, const CCP_PhyDqsTimingReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyDqsTimingRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction6(const CCP_PrivateData* pD, const CCP_PhyDqsTimingReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction7(const CCP_PrivateData* pD, const CCP_PhyGateLpbkCtrlReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyGateLpbkCtrlRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction8(const CCP_PrivateData* pD, const CCP_PhyGateLpbkCtrlReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction9(const CCP_PrivateData* pD, const CCP_PhyDllMasterCtrlReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyDllMasterCtrlRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction10(const CCP_PrivateData* pD, const CCP_PhyDllMasterCtrlReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction11(const CCP_PrivateData* pD, const CCP_PhyDllSlaveCtrlReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyDllSlaveCtrlRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction12(const CCP_PrivateData* pD, const CCP_PhyDllSlaveCtrlReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction13(const CCP_PrivateData* pD, const CCP_PhyIeTimingReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyIeTimingRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction14(const CCP_PrivateData* pD, const CCP_PhyIeTimingReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction15(const CCP_PrivateData* pD, const CCP_PhyObsReg0* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction16(const CCP_PrivateData* pD, const CCP_PhyDllObsReg0* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction17(const CCP_PrivateData* pD, const CCP_PhyDllObsReg1* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction18(const CCP_PrivateData* pD, const CCP_PhyDllObsReg2* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction19(const CCP_PrivateData* pD, const CCP_PhyStaticToggReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyStaticToggRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction20(const CCP_PrivateData* pD, const CCP_PhyStaticToggReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction21(const CCP_PrivateData* pD, const CCP_PhyWrRdDeskewCmd* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyWrRdDeskewCmdSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction22(const CCP_PrivateData* pD, const CCP_PhyWrRdDeskewCmd* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction23(const CCP_PrivateData* pD, const CCP_PhyWrDeskewPdCtrl0Dq0* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyWrDeskewPdCtrl0Dq0SF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction24(const CCP_PrivateData* pD, const CCP_PhyWrDeskewPdCtrl0Dq0* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction25(const CCP_PrivateData* pD, const CCP_PhyCtrlMain* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyCtrlMainSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction26(const CCP_PrivateData* pD, const CCP_PhyCtrlMain* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction27(const CCP_PrivateData* pD, const CCP_PhyTselReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PhyTselRegSF(value) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction28(const CCP_PrivateData* pD, const CCP_PhyTselReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction29(const CCP_PrivateData* pD)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction31(const CCP_PrivateData* pD, const uint32_t* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CCP_SanityFunction34(const CCP_PrivateData* pD, const CCP_PhyFeaturesReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCP_PrivateDataSF(pD) == CDN_EINVAL)
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
