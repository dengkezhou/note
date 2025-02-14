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
 * sdio_sd4_host.c
 * Vendor specific registers definitions for SD Host 4 controller
 *****************************************************************************/

#include "sdio_host.h"
#include "csdd_structs_if.h"

#ifndef SDIO_CFG_HOST_VER
    #error "SDIO_CFG_HOST_VER should be defined explicitly"
#endif

#if SDIO_CFG_HOST_VER >= 4

#include "sdio_sd4_host.h"

void SDIOHost_AxiErrorInit(CSDD_SDIO_Host *pSdioHost)
{
    uint32_t reg;
    reg = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS03);
    reg |= HRS3_SET_INT_STATUS_EN(HRS3_AER_ALL);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS03, reg);
}

void SDIOHost_AxiErrorIntSignalCfg(CSDD_SDIO_Host *pSdioHost, uint8_t enable)
{
    uint32_t reg;
    reg = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS03);
    if (enable != 0U) {
        reg |= HRS3_SET_INT_SIGNAL_EN(HRS3_AER_ALL);
    } else {
        reg &= ~HRS3_SET_INT_SIGNAL_EN(HRS3_AER_ALL);
    }
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS03, reg);
}

void SDIOHost_AxiErrorGetStatus(CSDD_SDIO_Host *pSdioHost, uint8_t* status)
{
    uint32_t reg;
    reg = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS03);
    *status = (uint8_t)HRS3_GET_INT_STATUS(reg);
}

void SDIOHost_AxiErrorClearStatus(CSDD_SDIO_Host *pSdioHost, uint8_t status)
{
    uint32_t reg;
    reg = CPS_REG_READ(&pSdioHost->RegOffset->HRS.HRS03);
    reg &= ~HRS3_SET_INT_STATUS(HRS3_AER_ALL);
    reg |= HRS3_SET_INT_STATUS(status);
    CPS_REG_WRITE(&pSdioHost->RegOffset->HRS.HRS03, reg);
}

#endif
