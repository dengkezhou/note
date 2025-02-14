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
 * sdio_request.h
 * SD Host controller driver - Request creator module
 *****************************************************************************/

#ifndef SDIO_REQUEST_H
#define SDIO_REQUEST_H

#include "sdio_types.h"

#define SDIOHOST_REQUEST_ISTATUS_FIRST      0U
#define SDIOHOST_REQUEST_ISTATUS_NEXT       1U

typedef struct {
    uint8_t cmd;
    uint32_t arg;
    CSDD_CmdType cmdType;
    CSDD_ResponseType respType;
    uint8_t hwRespCheck;
} SD_CsddRequesParams;

typedef struct {
    void* buf;
    uint32_t blkCount;
    uint16_t blkLen;
    uint8_t auto12;
    uint8_t auto23;
    CSDD_TransferDirection dir;
    uint8_t appCmd;
    uint8_t subBuffersCount;
} SD_CsddRequesParamsExt;

typedef struct {
    void* buf;
    uint32_t blkCount;
    uint16_t blkLen;
    CSDD_TransferDirection dir;
    uint8_t subBuffersCount;
} SD_CsddRequesParamsADMA3Ext;

void SDIO_REQ_INIT_CMD(CSDD_Request* req, const SD_CsddRequesParams* params);

void SDIO_REQ_INIT_ACMD(CSDD_Request* req, const SD_CsddRequesParams* params);

void SDIO_REQ_INIT_CMD_WITH_DATA(CSDD_Request* req, const SD_CsddRequesParams* params,
                                 const SD_CsddRequesParamsExt* paramsExt);

void SDIO_REQ_INIT_CMD_DATA_INF_S(CSDD_Request* req, const SD_CsddRequesParams* params,
                                       const SD_CsddRequesParamsExt* paramsExt);

void SDIO_REQ_INIT_CMD_DATA_INF_N(CSDD_Request* req, void* buf,
                                       uint32_t blk_count,  uint16_t blk_len,
                                       CSDD_TransferDirection dir);
void SDIO_REQ_INIT_CMD_DATA_MULTI(CSDD_Request* req, uint8_t cmdCount);

#endif
