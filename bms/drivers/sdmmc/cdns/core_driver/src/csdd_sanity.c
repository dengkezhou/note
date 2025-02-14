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

#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "csdd_structs_if.h"
#include "csdd_sanity.h"

/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_ConfigSF(const CSDD_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct Request
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_RequestSF(const CSDD_Request *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->commandCategory != CSDD_CMD_CAT_MAIN) &&
            (obj->commandCategory != CSDD_CMD_CAT_SUB) &&
            (obj->commandCategory != CSDD_CMD_CAT_NORMAL)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyDelaySettings
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_PhyDelaySettingsSF(const CSDD_PhyDelaySettings *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct CQInitConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CQInitConfigSF(const CSDD_CQInitConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct CQRequest
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CQRequestSF(const CSDD_CQRequest *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->transferDirection != CSDD_TRANSFER_READ) &&
            (obj->transferDirection != CSDD_TRANSFER_WRITE)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_FINISHED) &&
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_ATTACHED) &&
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_PENDING) &&
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_FAILED)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct CQDcmdRequest
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CQDcmdRequestSF(const CSDD_CQDcmdRequest *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->responseType != CSDD_RESPONSE_NO_RESP) &&
            (obj->responseType != CSDD_RESPONSE_R1) &&
            (obj->responseType != CSDD_RESPONSE_R1B) &&
            (obj->responseType != CSDD_RESPONSE_R2) &&
            (obj->responseType != CSDD_RESPONSE_R3) &&
            (obj->responseType != CSDD_RESPONSE_R4) &&
            (obj->responseType != CSDD_RESPONSE_R5) &&
            (obj->responseType != CSDD_RESPONSE_R5B) &&
            (obj->responseType != CSDD_RESPONSE_R6) &&
            (obj->responseType != CSDD_RESPONSE_R7)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_FINISHED) &&
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_ATTACHED) &&
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_PENDING) &&
            (obj->cQReqStat != CSDD_CQ_REQ_STAT_FAILED)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct CQIntCoalescingCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CQIntCoalescingCfgSF(const CSDD_CQIntCoalescingCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct SDIO_Host
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_SDIOHostSF(const CSDD_SDIO_Host *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_Slots;

        for (idx_Slots = 0; idx_Slots < SDIO_SLOT_COUNT; idx_Slots++)
        {
            if (CSDD_SDIOSlotSF(&obj->Slots[idx_Slots]) == CDN_EINVAL)
            {
                ret = CDN_EINVAL;
            }
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
uint32_t CSDD_CallbacksSF(const CSDD_Callbacks *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct CPhyConfigIoDelay
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CPhyConfigIoDelaySF(const CSDD_CPhyConfigIoDelay *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct CPhyConfigLvsi
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CPhyConfigLvsiSF(const CSDD_CPhyConfigLvsi *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct CPhyConfigDfiRd
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CPhyConfigDfiRdSF(const CSDD_CPhyConfigDfiRd *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct CPhyConfigOutputDelay
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_CPhyConfigOutputDelaySF(const CSDD_CPhyConfigOutputDelay *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct SDIO_Slot
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSDD_SDIOSlotSF(const CSDD_SDIO_Slot *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->dmaModeSelected != CSDD_SDMA_MODE) &&
            (obj->dmaModeSelected != CSDD_ADMA1_MODE) &&
            (obj->dmaModeSelected != CSDD_ADMA2_MODE) &&
            (obj->dmaModeSelected != CSDD_ADMA3_MODE) &&
            (obj->dmaModeSelected != CSDD_AUTO_MODE) &&
            (obj->dmaModeSelected != CSDD_NONEDMA_MODE)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->CQDescSize != CSDD_CQ_TASK_DESC_SIZE_64BIT) &&
            (obj->CQDescSize != CSDD_CQ_TASK_DESC_SIZE_128BIT)
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
 * @param[out] req
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction1(const CSDD_SysReq* req)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (req == NULL)
    {
        ret = CDN_EINVAL;
    }


    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD private data
 * @param[in] config startup configuration
 * @param[in] callbacks pointer to callbacks functions
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction2(const CSDD_SDIO_Host* pD, const CSDD_Config* config, const CSDD_Callbacks* callbacks)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CallbacksSF(callbacks) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction3(const CSDD_SDIO_Host* pD)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD private data
 * @param[in] request request to execute
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction5(const CSDD_SDIO_Host* pD, const CSDD_Request* request)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_RequestSF(request) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] cmd it describes what should be configured
 * @param[in] data buffer with configuration data
 * @param[in] sizeOfData size of data buffer in bytes
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction10(const CSDD_SDIO_Host* pD, const CSDD_ConfigCmd cmd, const void* data, const uint8_t* sizeOfData)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (data == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (sizeOfData == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (cmd != CSDD_CONFIG_SET_CLK) &&
        (cmd != CSDD_CONFIG_SET_BUS_WIDTH) &&
        (cmd != CSDD_CONFIG_SET_DAT_TIMEOUT) &&
        (cmd != CSDD_CONFIG_DISABLE_SIGNAL_INTERRUPT) &&
        (cmd != CSDD_CONFIG_RESTORE_SIGNAL_INTERRUPT) &&
        (cmd != CSDD_CONFIG_SET_DMA_MODE)
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
 * @param[in] pD private data
 * @param[in] handled informs if interrupt occurred
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction11(const CSDD_SDIO_Host* pD, const bool* handled)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (handled == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] accessMode access mode to set
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction15(const CSDD_SDIO_Host* pD, const CSDD_SpeedMode accessMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (accessMode != CSDD_ACCESS_MODE_SDR12) &&
        (accessMode != CSDD_ACCESS_MODE_SDR25) &&
        (accessMode != CSDD_ACCESS_MODE_SDR50) &&
        (accessMode != CSDD_ACCESS_MODE_SDR104) &&
        (accessMode != CSDD_ACCESS_MODE_DDR50) &&
        (accessMode != CSDD_ACCESS_MODE_MMC_LEGACY) &&
        (accessMode != CSDD_ACCESS_MODE_HS_SDR) &&
        (accessMode != CSDD_ACCESS_MODE_HS_DDR) &&
        (accessMode != CSDD_ACCESS_MODE_HS_200) &&
        (accessMode != CSDD_ACCESS_MODE_HS_400) &&
        (accessMode != CSDD_ACCESS_MODE_HS_400_ES)
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
 * @param[in] pD private data
 * @param[in] driverStrength new driver strength
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction19(const CSDD_SDIO_Host* pD, const CSDD_DriverStrengthType driverStrength)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (driverStrength != CSDD_SWITCH_DRIVER_STRENGTH_TYPE_A) &&
        (driverStrength != CSDD_SWITCH_DRIVER_STRENGTH_TYPE_B) &&
        (driverStrength != CSDD_SWITCH_DRIVER_STRENGTH_TYPE_C) &&
        (driverStrength != CSDD_SWITCH_DRIVER_STRENGTH_TYPE_D)
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
 * @param[in] pD private data
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] direction
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction21(const CSDD_SDIO_Host* pD, const void* buffer, const CSDD_TransferDirection direction)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buffer == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (direction != CSDD_TRANSFER_READ) &&
        (direction != CSDD_TRANSFER_WRITE)
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
 * @param[in] pD private data
 * @param[in] cmd this parameter defines what operation will be executed
 * @param[in] data buffer with data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction23(const CSDD_SDIO_Host* pD, const CSDD_MmcConfigCmd cmd, const uint8_t* data)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (data == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (cmd != CSDD_MMC_CARD_CONF_CARD_LOCK) &&
        (cmd != CSDD_MMC_CARD_CONF_CARD_UNLOCK) &&
        (cmd != CSDD_MMC_CARD_CONF_SET_PASSWORD) &&
        (cmd != CSDD_MMC_CARD_CONF_RESET_PASSWORD)
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
 * @param[in] pD private data
 * @param[in] direction parameter defines transfer direction
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction28(const CSDD_SDIO_Host* pD, const CSDD_TransferDirection direction)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (direction != CSDD_TRANSFER_READ) &&
        (direction != CSDD_TRANSFER_WRITE)
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
 * @param[in] pD private data
 * @param[in,out] buffer buffer with data to be written or to save data that was read
 * @param[in] direction parameter defines transfer direction
 * @param[out] request current executing request
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction29(const CSDD_SDIO_Host* pD, const void* buffer, const CSDD_TransferDirection direction, const void** request)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buffer == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (request == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (direction != CSDD_TRANSFER_READ) &&
        (direction != CSDD_TRANSFER_WRITE)
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
 * @param[in] pD private data
 * @param[in] phyDelaySet PHY delay settings
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction31(const CSDD_SDIO_Host* pD, const CSDD_PhyDelaySettings* phyDelaySet)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_PhyDelaySettingsSF(phyDelaySet) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] phyDelayType it defines which PHY delay should be written
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction33(const CSDD_SDIO_Host* pD, const CSDD_PhyDelay phyDelayType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (phyDelayType != CSDD_PHY_DELAY_INPUT_HIGH_SPEED) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_DEFAULT_SPEED) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_SDR12) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_SDR25) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_SDR50) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_DDR50) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_MMC_LEGACY) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_MMC_SDR) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_MMC_DDR) &&
        (phyDelayType != CSDD_PHY_DELAY_DLL_SDCLK) &&
        (phyDelayType != CSDD_PHY_DELAY_DLL_HS_SDCLK) &&
        (phyDelayType != CSDD_PHY_DELAY_DLL_DAT_STROBE)
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
 * @param[in] pD private data
 * @param[in] phyDelayType it defines which PHY delay should be read:
 * @param[in] delayVal read value of selected PHY delay
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction34(const CSDD_SDIO_Host* pD, const CSDD_PhyDelay phyDelayType, const uint8_t* delayVal)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (delayVal == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (phyDelayType != CSDD_PHY_DELAY_INPUT_HIGH_SPEED) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_DEFAULT_SPEED) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_SDR12) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_SDR25) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_SDR50) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_DDR50) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_MMC_LEGACY) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_MMC_SDR) &&
        (phyDelayType != CSDD_PHY_DELAY_INPUT_MMC_DDR) &&
        (phyDelayType != CSDD_PHY_DELAY_DLL_SDCLK) &&
        (phyDelayType != CSDD_PHY_DELAY_DLL_HS_SDCLK) &&
        (phyDelayType != CSDD_PHY_DELAY_DLL_DAT_STROBE)
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
 * @param[in] pD private data
 * @param[out] cardStatus pointer to memory where read card status shall be written
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction35(const CSDD_SDIO_Host* pD, const uint32_t* cardStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cardStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] transferDirection parameter defines transfer direction
 * @param[in,out] data pointer to write/read data buffer
 * @param[in] registerAddress
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction39(const CSDD_SDIO_Host* pD, const CSDD_TransferDirection transferDirection, const void* data, const CSDD_CccrRegAddr registerAddress)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (data == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (transferDirection != CSDD_TRANSFER_READ) &&
        (transferDirection != CSDD_TRANSFER_WRITE)
    )
    {
        ret = CDN_EINVAL;
    }
    else if (
        (registerAddress != CSDD_CCCR_CCCR_SDIO_REV) &&
        (registerAddress != CSDD_CCCR_SD_SPEC_REV) &&
        (registerAddress != CSDD_CCCR_IO_ENABLE) &&
        (registerAddress != CSDD_CCCR_IO_READY) &&
        (registerAddress != CSDD_CCCR_INT_ENABLE) &&
        (registerAddress != CSDD_CCCR_INT_PENDING) &&
        (registerAddress != CSDD_CCCR_ABORT) &&
        (registerAddress != CSDD_CCCR_BUS_CONTROL) &&
        (registerAddress != CSDD_CCCR_CARD_CAPABILITY) &&
        (registerAddress != CSDD_CCCR_CIS_POINTER) &&
        (registerAddress != CSDD_CCCR_BUS_SUSPENDED) &&
        (registerAddress != CSDD_CCCR_FUNCTION_SELECT) &&
        (registerAddress != CSDD_CCCR_EXEC_FLAGS) &&
        (registerAddress != CSDD_CCCR_READY_FLAGS) &&
        (registerAddress != CSDD_CCCR_FN0_BLOCK_SIZE) &&
        (registerAddress != CSDD_CCCR_POWER_CONTROL) &&
        (registerAddress != CSDD_CCCR_HIGH_SPEED) &&
        (registerAddress != CSDD_CCCR_UHSI_SUPPORT) &&
        (registerAddress != CSDD_CCCR_DRIVER_STRENGTH) &&
        (registerAddress != CSDD_CCCR_INT_EXT)
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
 * @param[in] pD private data
 * @param[out] buffer
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction41(const CSDD_SDIO_Host* pD, const uint8_t* buffer)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buffer == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] tupleCode code name of tuple
 * @param[out] buffer buffer for read tuple
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction42(const CSDD_SDIO_Host* pD, const CSDD_TupleCode tupleCode, const void* buffer)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buffer == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (tupleCode != CSDD_TUPLE_CISTPL_NULL) &&
        (tupleCode != CSDD_TUPLE_CISTPL_CHECKSUM) &&
        (tupleCode != CSDD_TUPLE_CISTPL_VERS_1) &&
        (tupleCode != CSDD_TUPLE_CISTPL_ALTSTR) &&
        (tupleCode != CSDD_TUPLE_CISTPL_MANFID) &&
        (tupleCode != CSDD_TUPLE_CISTPL_FUNCID) &&
        (tupleCode != CSDD_TUPLE_CISTPL_SDIO_STD) &&
        (tupleCode != CSDD_TUPLE_CISTPL_SDIO_EXT) &&
        (tupleCode != CSDD_TUPLE_CISTPL_END)
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
 * @param[in] pD private data
 * @param[in] currentLimit
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction45(const CSDD_SDIO_Host* pD, const CSDD_DriverCurrentLimit currentLimit)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (currentLimit != CSDD_SDCARD_SWITCH_CURRENT_LIMIT_200) &&
        (currentLimit != CSDD_SDCARD_SWITCH_CURRENT_LIMIT_400) &&
        (currentLimit != CSDD_SDCARD_SWITCH_CURRENT_LIMIT_600) &&
        (currentLimit != CSDD_SDCARD_SWITCH_CURRENT_LIMIT_800)
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
 * @param[in] pD private data
 * @param[in] partition partition to be active to boot
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction48(const CSDD_SDIO_Host* pD, const CSDD_ParitionBoot partition)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (partition != CSDD_EMMC_BOOT_NONE) &&
        (partition != CSDD_EMMC_BOOT_1) &&
        (partition != CSDD_EMMC_BOOT_2) &&
        (partition != CSDD_EMMC_BOOT_USER)
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
 * @param[in] pD private data
 * @param[in] partition partition to be active to access
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction49(const CSDD_SDIO_Host* pD, const CSDD_ParitionAccess partition)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (partition != CSDD_EMMC_ACCCESS_BOOT_NONE) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_1) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_2) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_1) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_2) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_3) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_4) &&
        (partition != CSDD_EMMC_ACCCESS_BOOT_RPMB)
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
 * @param[in] pD private data
 * @param[out] buffer buffer for read
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction51(const CSDD_SDIO_Host* pD, const void* buffer)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (buffer == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] interfaceType interface type
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction53(const CSDD_SDIO_Host* pD, const CSDD_InterfaceType* interfaceType)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (interfaceType == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] deviceState device state and info
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction54(const CSDD_SDIO_Host* pD, const CSDD_DeviceState* deviceState)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (deviceState == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] drvData driver data
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction57(const CSDD_SDIO_Host* pD, const void** drvData)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (drvData == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] rca RCA address
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction60(const CSDD_SDIO_Host* pD, const uint16_t* rca)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (rca == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] cqConfig Initial configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction61(const CSDD_SDIO_Host* pD, const CSDD_CQInitConfig* cqConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CQInitConfigSF(cqConfig) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] cqConfig current command queue configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction63(const CSDD_SDIO_Host* pD, const CSDD_CQInitConfig* cqConfig)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cqConfig == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] request a request to be attached
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction66(const CSDD_SDIO_Host* pD, const CSDD_CQRequest* request)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CQRequestSF(request) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] request a direct request to be executed
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction67(const CSDD_SDIO_Host* pD, const CSDD_CQDcmdRequest* request)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CQDcmdRequestSF(request) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[int] config new interrupt coalescing configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction70(const CSDD_SDIO_Host* pD, const CSDD_CQIntCoalescingCfg* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CQIntCoalescingCfgSF(config) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] config current interrupt coalescing configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction71(const CSDD_SDIO_Host* pD, const CSDD_CQIntCoalescingCfg* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] ioDelay configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction82(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigIoDelay* ioDelay)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CPhyConfigIoDelaySF(ioDelay) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] ioDelay configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction83(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigIoDelay* ioDelay)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (ioDelay == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] lvsi configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction84(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigLvsi* lvsi)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CPhyConfigLvsiSF(lvsi) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] lvsi configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction85(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigLvsi* lvsi)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (lvsi == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] dfiRd configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction86(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigDfiRd* dfiRd)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CPhyConfigDfiRdSF(dfiRd) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] dfiRd configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction87(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigDfiRd* dfiRd)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (dfiRd == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[in] outputDelay configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction88(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigOutputDelay* outputDelay)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_CPhyConfigOutputDelaySF(outputDelay) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] outputDelay configuration
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction89(const CSDD_SDIO_Host* pD, const CSDD_CPhyConfigOutputDelay* outputDelay)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (outputDelay == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
 * @param[in] pD private data
 * @param[out] extendedWrMode
 * @param[out] extendedRdMode
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSDD_SanityFunction92(const CSDD_SDIO_Host* pD, const bool* extendedWrMode, const bool* extendedRdMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (extendedWrMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (extendedRdMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSDD_SDIOHostSF(pD) == CDN_EINVAL)
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
