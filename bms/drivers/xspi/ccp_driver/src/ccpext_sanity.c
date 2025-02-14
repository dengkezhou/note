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
 * Extracted data
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
#include "ccpext_structs_if.h"
#include "ccpext_sanity.h"

/**
 * Function to validate struct PhyWrDeskewReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCPEXT_PhyWrDeskewRegSF(const CCPEXT_PhyWrDeskewReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->wrDq0DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq1DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq2DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq3DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq4DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq5DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq6DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wrDq7DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyRdDeskewReg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCPEXT_PhyRdDeskewRegSF(const CCPEXT_PhyRdDeskewReg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->rdDq0DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq1DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq2DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq3DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq4DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq5DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq6DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdDq7DeskwDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyWrDeskewPdCtrl0Dqx
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCPEXT_PhyWrDeskewPdCtrl0DqxSF(const CCPEXT_PhyWrDeskewPdCtrl0Dqx *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dq3SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq3EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq3SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq3PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq2SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq2EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq2SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq2PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq1SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq1EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq1SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq1PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyWrDeskewPdCtrl1Reg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCPEXT_PhyWrDeskewPdCtrl1RegSF(const CCPEXT_PhyWrDeskewPdCtrl1Reg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dq7SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq7EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq7SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq7PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq6SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq6EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq6SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq6PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq5SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq5EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq5SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq5PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq4SwDqPhaseBypass > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq4EnSwHalfCycle > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq4SwHalfCycleShift > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dq4PhaseDetectSel > (0x7U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyCtrlLowFreqSel
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCPEXT_PhyCtrlLowFreqSelSF(const CCPEXT_PhyCtrlLowFreqSel *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->lowFreqSel > (0x1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyWrRdDeskewCmdExt
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CCPEXT_PhyWrRdDeskewCmdExtSF(const CCPEXT_PhyWrRdDeskewCmdExt *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->wrCmdDeskewDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rdCmdDeskewDelay > (0xFU))
        {
            ret = CDN_EINVAL;
        }
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
uint32_t CCPEXT_SanityFunction1(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCPEXT_PhyWrDeskewPdCtrl0DqxSF(value) == CDN_EINVAL)
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
uint32_t CCPEXT_SanityFunction2(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl0Dqx* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (value == NULL)
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
uint32_t CCPEXT_SanityFunction3(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCPEXT_PhyWrDeskewRegSF(value) == CDN_EINVAL)
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
uint32_t CCPEXT_SanityFunction4(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (value == NULL)
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
uint32_t CCPEXT_SanityFunction5(const CCP_PrivateData* pD, const CCPEXT_PhyRdDeskewReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCPEXT_PhyRdDeskewRegSF(value) == CDN_EINVAL)
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
uint32_t CCPEXT_SanityFunction6(const CCP_PrivateData* pD, const CCPEXT_PhyRdDeskewReg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (value == NULL)
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
uint32_t CCPEXT_SanityFunction7(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl1Reg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCPEXT_PhyWrDeskewPdCtrl1RegSF(value) == CDN_EINVAL)
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
uint32_t CCPEXT_SanityFunction8(const CCP_PrivateData* pD, const CCPEXT_PhyWrDeskewPdCtrl1Reg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (value == NULL)
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
uint32_t CCPEXT_SanityFunction9(const CCP_PrivateData* pD, const CCPEXT_PhyCtrlLowFreqSel* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCPEXT_PhyCtrlLowFreqSelSF(value) == CDN_EINVAL)
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
uint32_t CCPEXT_SanityFunction10(const CCP_PrivateData* pD, const CCPEXT_PhyCtrlLowFreqSel* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (value == NULL)
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
uint32_t CCPEXT_SanityFunction11(const CCP_PrivateData* pD, const CCPEXT_PhyWrRdDeskewCmdExt* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CCPEXT_PhyWrRdDeskewCmdExtSF(value) == CDN_EINVAL)
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
uint32_t CCPEXT_SanityFunction12(const CCP_PrivateData* pD, const CCPEXT_PhyWrRdDeskewCmdExt* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (value == NULL)
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
