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
 * sdio_card_general.c
 * sdio/sd/emmc device card general functions
 *****************************************************************************/

#include "sdio_host.h"
#include "sdio_errors.h"
#include "sdio_card_general.h"
#include "sdio_debug.h"
#include "sdio_request.h"
#include "sdio_utils.h"
#include "csdd_structs_if.h"

#ifndef SDIO_CFG_ENABLE_MMC
    #error "SDIO_CFG_ENABLE_MMC should be defined explicitly"
#endif

#ifndef SDIO_CFG_ENABLE_IO
    #error "SDIO_CFG_ENABLE_IO should be defined explicitly"
#endif

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadSDStatus(CSDD_SDIO_Slot* pSlot, uint8_t Buffer[64])
{
    uint8_t Status;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        Status = SDIOHost_SelectCard(pSlot, pSlot->pDevice->RCA);

        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            CSDD_Request Request = {0};

            SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_ACMD13, .arg = 0,
                                                                          .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                        &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = 1, .blkLen = 64,
                                                                   .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ,
                                                                   .appCmd = 1U}));

            SDIOHost_ExecCardCommand(pSlot, &Request);
            SDIOHost_CheckBusy(Request.pSdioHost, &Request);

            Status = Request.status;
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ExecCMD55Command(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        uint32_t argument;
        if (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_NONE) {
            argument = ((uint32_t)pSlot->pDevice->RCA << 16);
        } else {
            argument = 0U;
        }

        CSDD_Request Request = {0};

        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD55, .arg = argument,
                                                            .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

        // execute CMD55 command
        SDIOHost_ExecCardCmdFiniteNonApp(pSlot, &Request);

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        status = Request.status;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ExecCMD23Command(CSDD_SDIO_Slot* pSlot, uint32_t BlockCount)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        CSDD_Request Request = {0};

        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD23, .arg = BlockCount,
                                                            .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

        // start data transfer
        SDIOHost_ExecCardCommand(pSlot, &Request);

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        status = Request.status;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ExecCMD12Command(CSDD_SDIO_Slot* pSlot, CSDD_ResponseType ResponseType)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        CSDD_Request Request = {0};

        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD12, .arg = 0,
                                                            .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = ResponseType, .hwRespCheck = 0}));

        // start data transfer
        SDIOHost_ExecCardCommand(pSlot, &Request);

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        status = Request.status;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ResetCard(CSDD_SDIO_Slot* pSlot)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        CSDD_Request Request = {0};
        CSDD_SDIO_Host *pSdioHost = pSlot->pSdioHost;

        if (pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
            SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD0, .arg = 0,
                                                                .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
        }
        else {
            SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD0, .arg = 0,
                                                                .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_NO_RESP, .hwRespCheck = 0}));
        }

        // execute CMD0 command
        SDIOHost_ExecCardCommand(pSlot, &Request);
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        status = Request.status;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static CSDD_ResponseType SDIOHost_CalcRespType(const CSDD_SDIO_Slot* pSlot, uint16_t rca)
{
    CSDD_ResponseType ResponseType = CSDD_RESPONSE_NO_RESP;

    if ((pSlot->pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U) {
        if (rca != 0U) {
            if (pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD) {
                ResponseType = CSDD_RESPONSE_R1B;
            }
        }
        else {
            ResponseType = CSDD_RESPONSE_NO_RESP;
        }
    }

#if SDIO_CFG_ENABLE_MMC
    if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
        ResponseType = CSDD_RESPONSE_R1;
    }
#endif

    return (ResponseType);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SelectCard(CSDD_SDIO_Slot* pSlot, uint16_t rca)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        // check if card is inserted and attached
        if (pSlot->CardInserted == 0U) {
            if (pSlot->NeedAttach != 0U) {
                status = SDIO_ERR_CARD_IS_NOT_ATTACHED;
            } else {
                status = SDIO_ERR_CARD_IS_NOT_INSERTED;
            }
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else if ((rca == pSlot->pDevice->RCA) && (pSlot->pDevice->IsSelected != 0U)) {
            status = SDIO_ERR_NO_ERROR;
        } else if ((rca == 0U) && (pSlot->pDevice->IsSelected == 0U)) {
            status = SDIO_ERR_NO_ERROR;
        } else {
            CSDD_Request Request = {0};
            CSDD_ResponseType ResponseType = SDIOHost_CalcRespType(pSlot, rca);

            SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD7, .arg = ((uint32_t)rca << 16),
                                                                .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                .respType = ResponseType, .hwRespCheck = 0}));

            // execute CMD7 command
            SDIOHost_ExecCardCommand(pSlot, &Request);
            SDIOHost_CheckBusy(Request.pSdioHost, &Request);

            if (Request.status == 0U) {
                if (rca != 0U) {
                    pSlot->pDevice->IsSelected = 1;
                } else {
                    pSlot->pDevice->IsSelected = 0;
                }
            }

            status = Request.status;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadCardStatus (CSDD_SDIO_Slot* pSlot, uint32_t *CardStatus)
{
    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_SDIO) {
        status = SDIO_ERR_UNSUPPORTED_COMMAND;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        CSDD_Request Request = {0};

        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD13, .arg = ((uint32_t)pSlot->pDevice->RCA << 16),
                                                            .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                            .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

        SDIOHost_ExecCardCommand(pSlot, &Request);
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        if (Request.response != NULL) {
            *CardStatus = Request.response[0];
        }

        status = Request.status;
    }

    return (status);
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_IO
//-----------------------------------------------------------------------------
uint8_t SDIOHost_AccessCCCR (CSDD_SDIO_Slot* pSlot, uint8_t TransferDirection,
                             void *Data, uint8_t DataSize, uint8_t RegisterAddress)
{
    CSDD_Request Request;
    char NumberOfBytes, i = 0;
    uint32_t tmp = 0;
    uint8_t Status;

    if (pSlot == NULL)
        return SDIO_ERR_INVALID_PARAMETER;


    Status = SDIOHost_SelectCard(pSlot, pSlot->pDevice->RCA);
    if (Status) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        return Status;
    }

    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD52, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R5, .hwRespCheck = 0}));

    // set numbers of bytes to transfer
    // and check if the Data parameter has appropriate size
    switch (RegisterAddress) {
    case CSDD_CCCR_CIS_POINTER:
        NumberOfBytes = 3;
        if (DataSize < 4U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            return SDIO_ERR_INVALID_PARAMETER;
        }
        break;
    case CSDD_CCCR_FN0_BLOCK_SIZE:
        if (DataSize < 2U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            return SDIO_ERR_INVALID_PARAMETER;
        }
        NumberOfBytes = 2;
        break;
    default:
        if (DataSize < 1U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            return SDIO_ERR_INVALID_PARAMETER;
        }
        NumberOfBytes = 1;
        break;
    }

    // read data from the CCCR register
    if (TransferDirection == 0) {
        for (i = 0; i < NumberOfBytes; i++) {
            // set address of register to read
            Request.argument = (uint32_t)(RegisterAddress + i) << 9
                               | (uint32_t)TransferDirection << 31;

            // execute command CMD52 to read data /from CCCR register
            SDIOHost_ExecCardCommand(pSlot, &Request);

            SDIOHost_CheckBusy(Request.pSdioHost, &Request);
            // check status
            if (Request.status) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
                return Request.status;
            }

            tmp |= (Request.response[0] & 0xFFU) << (i * 8U);
        }

        switch (RegisterAddress) {
        case CSDD_CCCR_CIS_POINTER:
            *((uint32_t*)Data) = (uint32_t)tmp;
            break;
        case CSDD_CCCR_FN0_BLOCK_SIZE:
            *((uint16_t*)Data) = (uint16_t)tmp;
            break;
        default:
            *((uint8_t*)Data) = (uint8_t)tmp;
            break;
        }
    }
    // write data to the CCCR register
    else {
        uint8_t *DataByte = Data;
        for (i = 0; i < NumberOfBytes; i++) {
            // set address of register to write
            Request.argument = (uint32_t)(RegisterAddress + i) << 9
                               | (uint32_t)TransferDirection << 31
                               | *DataByte++;

            // execute command CMD52 to write data to CCCR register
            SDIOHost_ExecCardCommand(pSlot, &Request);

            SDIOHost_CheckBusy(Request.pSdioHost, &Request);
            // check status
            if (Request.status) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
                return Request.status;
            }
        }
    }
    return SDIO_ERR_NO_ERROR;
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadSCR(CSDD_SDIO_Slot* pSlot)
{
    uint8_t Status;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        Status = SDIOHost_SelectCard(pSlot, pSlot->pDevice->RCA);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            CSDD_Request Request = {0};
            uint32_t Buffer[2];

            SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_ACMD51, .arg = 0,
                                                                          .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                        &((SD_CsddRequesParamsExt){.buf = (uint8_t*)Buffer, .blkCount = 1, .blkLen = 8,
                                                                   .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ,
                                                                   .appCmd = 1U}));
            SDIOHost_ExecCardCommand(pSlot, &Request);

            SDIOHost_CheckBusy(Request.pSdioHost, &Request);
            // check status
            if (Request.status != SDIO_ERR_NO_ERROR) {
                Status = Request.status;
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
            } else {
                // get more significant 32 bits from SCR register
                uint32_t SCR = Buffer[0];

                SCR = ((SCR & 0xFFU) << 24)
                      | ((SCR & 0xFF000000U) >> 24)
                      | ((SCR & 0xFF0000U) >> 8)
                      | ((SCR & 0xFF00U) << 8);

                DbgMsg(DBG_GEN_MSG, DBG_FYI, "SDIOHost_ReadSCR SCR(32-63) = %lX\n", SCR);

                pSlot->pDevice->SupportedBusWidths = (uint8_t)((SCR & SDCARD_REG_SCR_SBW_MASK) >> 16);
                pSlot->pDevice->SpecVersNumb = (uint8_t)((SCR & SDCARD_REG_SCR_SPEC_VER_MASK) >> 24);

                if ((pSlot->pDevice->SpecVersNumb == 2U)
                    && ((SCR & SDCARD_REG_SD_SPEC3_SUPPORT) != 0U)) {
                    pSlot->pDevice->SpecVersNumb = 3U;
                }

                pSlot->pDevice->CMD23Supported = (((SCR & SDCARD_REG_CMD23) != 0U) ? 1U : 0U);
                pSlot->pDevice->CMD20Supported = (((SCR & SDCARD_REG_CMD20) != 0U) ? 1U : 0U);

                Status = SDIO_ERR_NO_ERROR;
            }
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadRCA(CSDD_SDIO_Slot* pSlot)
{
    // RCA address for RCA cards for MMC cards
    static uint16_t RcaAddr = 0x1000;

    uint8_t status;

    if (pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        RcaAddr--;

        CSDD_Request Request = {0};

#if SDIO_CFG_ENABLE_MMC
        if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
            pSlot->pDevice->RCA = RcaAddr;
            SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD3, .arg = ((uint32_t)pSlot->pDevice->RCA << 16),
                                                                .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
        } else
#endif
        {
            SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD3, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                .respType = CSDD_RESPONSE_R6, .hwRespCheck = 0}));
        }

        // execute CMD3 command to get the card RCA
        SDIOHost_ExecCardCommand(pSlot, &Request);
        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        /* some memory models return error even if command executed properly */
        //    if (Request.status != SDIO_ERR_NO_ERROR)
        //        LOG_AND_EXIT(Request.status)

        if ((pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC) && (Request.response != NULL)) {
            //get RCA CMD 3
            pSlot->pDevice->RCA = (uint16_t)((Request.response[0] >> 16) & 0xFFFFU);
        }

        status = SDIO_ERR_NO_ERROR;
    }

    return (status);
}
//-----------------------------------------------------------------------------

static uint8_t SDIOHost_ProcessReadCID(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_CidRegister* CID)
{
    uint8_t Status;

    CSDD_Request Request = {0};

    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD2, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R2, .hwRespCheck = 0}));

    // execute CMD command to get the card CID register
    SDIOHost_ExecCardCommand(pSlot, &Request);

    SDIOHost_CheckBusy(Request.pSdioHost, &Request);
    // check status
    if (Request.status != SDIO_ERR_NO_ERROR) {
        Status = Request.status;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else {
        uint8_t i;

        CID->manufacturerId = (uint8_t)((Request.response[3] >> 16) & 0xFFU);
        CID->oemApplicationId = (uint16_t)(Request.response[3] & 0xFFFFU);

        CID->productName[0] = (uint8_t)((Request.response[1] >> 24) & 0xFFU);
        for (i = 0U; i < 4U; i++) {
            uint8_t nameElement = 0U;
            const uint8_t shift = i * 8U;
            if (shift < 32U) {
                nameElement = (uint8_t)((Request.response[2] >> shift) & 0xFFU);
            }
            CID->productName[i + 1U] = nameElement;
        }

        CID->productRevision = (uint8_t)((Request.response[1] >> 16) & 0xFFU);

        CID->productSn = ((Request.response[0] >> 16) & 0xFFFFU)
                         | ((Request.response[1] & 0xFFFFU) << 16);

        CID->manufacturingDate = (uint16_t)((Request.response[0]) & 0xFFFU);

        Status = SDIO_ERR_NO_ERROR;
    }

    return (Status);
}

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadCID(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_CidRegister* CID)
{
    uint8_t Status;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        Status = SDIOHost_SelectCard(pSlot, 0);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            Status = SDIOHost_ProcessReadCID(pSlot, CID);
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_IO
//-----------------------------------------------------------------------------
uint8_t SDIOHost_GetTupleFromCIS(CSDD_SDIO_Slot* pSlot, uint32_t TupleAddress,
                                 uint8_t TupleCode, uint8_t *Buffer, uint8_t BufferSize)
{
    CSDD_Request Request;
    uint8_t i = 0;
    uint8_t NextTupleOffset;

    if (pSlot == NULL)
        return SDIO_ERR_INVALID_PARAMETER;


    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD52, .arg = (TupleAddress << 9), .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R5, .hwRespCheck = 0}));

    while(1) {
        uint8_t ReadTupleCode;
        // Read tuple code name
        SDIOHost_ExecCardCommand(pSlot, &Request);

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);
        // Check status
        if (Request.status) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
            return Request.status;
        }

        if ((Request.response[0] & 0xFFU) == (uint8_t)CSDD_TUPLE_CISTPL_END) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_TUPLE_NOT_FOUND);
            return (SDIO_ERR_TUPLE_NOT_FOUND);
        }
        ReadTupleCode = Request.response[0] & 0xFFU;

        TupleAddress++;
        Request.argument = TupleAddress << 9;
        // Read link to next tuple
        SDIOHost_ExecCardCommand(pSlot, &Request);

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);
        // Check status
        if (Request.status) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
            return Request.status;
        }

        if ((Request.response[0] & 0xFFU) == (uint8_t)CSDD_TUPLE_CISTPL_END) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_TUPLE_NOT_FOUND);
            return SDIO_ERR_TUPLE_NOT_FOUND;
        }

        // save size of tuple body
        NextTupleOffset = Request.response[0] & 0xFFU;
        TupleAddress++;

        if (ReadTupleCode == TupleCode) {
            if (BufferSize < NextTupleOffset) {
                // to small buffer for data
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
                return SDIO_ERR_INVALID_PARAMETER;
            }

            for (i = 0; i < NextTupleOffset; i++) {
                Request.argument = (TupleAddress + i) << 9;
                // Read tuple body
                SDIOHost_ExecCardCommand(pSlot, &Request);

                SDIOHost_CheckBusy(Request.pSdioHost, &Request);
                // Check status
                if (Request.status) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
                    return Request.status;
                }

                Buffer[i] = Request.response[0] & 0xFFU;
            }
            break;
        }
        else {
            TupleAddress += NextTupleOffset;
            Request.argument = TupleAddress << 9;
        }
    }
    return SDIO_ERR_NO_ERROR;
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
static void SDIOHost_ProcessReadCSDFillBuf(uint32_t* Buffer,
                                           const uint8_t* TmpBuffer, const CSDD_Request* Request,
                                           uint8_t hostBusMode)
{
    int32_t i;
    if (hostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
        for (i = 0; i < 4; i++) {
            Buffer[i] = TmpBuffer[ i * 0 ]
                        | ((uint32_t)TmpBuffer[ i * 1 ] << 8)
                        | ((uint32_t)TmpBuffer[ i * 2 ] << 16)
                        | ((uint32_t)TmpBuffer[ i * 3 ] << 24);
        }
    } else {
        for (i = 0; i < 4; i++) {
            Buffer[i] = Request->response[i];
        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessReadCSD(CSDD_SDIO_Slot* pSlot, uint32_t* Buffer)
{
    uint8_t Status;
    uint8_t* TmpBuffer = (uint8_t*)pSlot->AuxBuff;
    CSDD_SDIO_Host* pSdioHost = pSlot->pSdioHost;
    CSDD_Request Request = {0};

    if (pSdioHost->HostBusMode == (uint8_t)CSDD_BUS_MODE_SPI) {
        SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD9,
                                                                      .arg = ((uint32_t)pSlot->pDevice->RCA << 16),
                                                                      .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                    &((SD_CsddRequesParamsExt){.buf = TmpBuffer, .blkCount = 1, .blkLen = 512,
                                                               .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ}));
    }
    else {
        SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD9, .arg = ((uint32_t)pSlot->pDevice->RCA << 16),
                                                            .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R2, .hwRespCheck = 0}));
    }

    // execute command to get CSD register content
    SDIOHost_ExecCardCommand(pSlot, &Request);

    SDIOHost_CheckBusy(Request.pSdioHost, &Request);
    // check status
    if (Request.status != SDIO_ERR_NO_ERROR) {
        Status = Request.status;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else {

        SDIOHost_ProcessReadCSDFillBuf(Buffer, TmpBuffer, &Request, pSdioHost->HostBusMode);

        Status = SDIO_ERR_NO_ERROR;
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadCSD(CSDD_SDIO_Slot* pSlot, uint32_t *Buffer)
{
    uint8_t Status;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        //deselect card read CSD command has to be exetuce in standby state
        Status = SDIOHost_SelectCard(pSlot, 0);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            Status = SDIOHost_ProcessReadCSD(pSlot, Buffer);
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_ReadExCSD(CSDD_SDIO_Slot* pSlot, uint8_t *Buffer)
{
    uint8_t Status;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        //select card read ExCSD command has to be exetuce in transfer state
        Status = SDIOHost_SelectCard(pSlot, pSlot->pDevice->RCA);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            CSDD_Request Request = {0};

            const uint8_t accessMode = pSlot->AccessMode;
            if ((accessMode != (uint8_t)CSDD_ACCESS_MODE_HS_DDR)
                && (accessMode != (uint8_t)CSDD_ACCESS_MODE_HS_400)
                && (accessMode != (uint8_t)CSDD_ACCESS_MODE_HS_400_ES)) {
                /* in DDR mode block length is automatically 512*/
                SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD16, .arg = 512,
                                                                    .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
                SDIOHost_ExecCardCommand(pSlot, &Request);
                SDIOHost_CheckBusy(Request.pSdioHost, &Request);
            }

            SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD8, .arg = 0, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                          .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                        &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = 1, .blkLen = 512,
                                                                   .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ}));

            // execute command to get CSD register content
            SDIOHost_ExecCardCommand(pSlot, &Request);

            SDIOHost_CheckBusy(Request.pSdioHost, &Request);
            // check status
            if (Request.status != SDIO_ERR_NO_ERROR) {
                Status = Request.status;
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
            } else {
                Status = SDIO_ERR_NO_ERROR;
            }
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ExecCMD6Command(CSDD_SDIO_Slot* pSlot, uint32_t argument,
                                        uint8_t *Buffer,
                                        uint8_t FunctionNr, uint8_t GroupNr)
{
    uint8_t status;

    if (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_SDMEM) {
        // this function can be executed only on SD cards
        status = SDIO_ERR_UNSUPPORTED_COMMAND;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        CSDD_Request Request = {0};

        SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD6, .arg = argument,
                                                                      .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                    &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = 1, .blkLen = 64,
                                                               .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ}));

        uint32_t Timeout = COMMANDS_TIMEOUT;
        bool doContinue = true;
        do {
            SDIOHost_ExecCardCommand(pSlot, &Request);
            SDIOHost_CheckBusy(Request.pSdioHost, &Request);
            if (Request.status != SDIO_ERR_NO_ERROR) {
                doContinue = false;
                status = Request.status;
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                break;
            }

            // check data structure version
            // if it is 1 then checking the busy status is possible
            if (SDCARD_SWITCH_FUNC_GET_DATA_STRUCT_VER(Buffer) == 1U) {
                // if function is busy continue loop
                // wait until function will be ready
                if (SDCARD_SWICH_FUNC_GET_BUSY_STAT(Buffer, GroupNr, FunctionNr) == 0U) {
                    doContinue = false;
                }
            } else {
                doContinue = false;
            }

        } while((--Timeout != 0U) && doContinue);

        if (Timeout == 0U) {
            status = SDIO_ERR_TIMEOUT;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {
            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_MMC
//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcSwitch(CSDD_SDIO_Slot* pSlot, uint8_t ArgIndex, uint8_t ArgValue)
{
    CSDD_Request Request = {0};
    uint32_t argument = (uint32_t)MMC_CMD6_ARG_MODE_WRITE_BYTE
                        | MMC_CMD6_ARG_INDEX(ArgIndex)
                        | MMC_CMD6_ARG_VALUE(ArgValue);
    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD6, .arg = argument, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1B, .hwRespCheck = 0}));

    // set bus width in the CSD register of MMC card
    SDIOHost_ExecCardCommand(pSlot, &Request);

    SDIOHost_CheckBusy(Request.pSdioHost, &Request);

    return Request.status;
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
static uint8_t SDIOHost_ProcessSwitchFunction(CSDD_SDIO_Slot* pSlot, uint8_t FunctionNr, uint8_t GroupNr)
{
    uint8_t Status;
    uint8_t* TmpBuffer = (uint8_t*)pSlot->AuxBuff;
    uint32_t argument;
    uint32_t argumentBase = 0U;

    const uint32_t shift = (((uint32_t)GroupNr - 1U) * 4U);
    if (shift < 32U) {
        argumentBase = (uint32_t)(0xFFFFFFU & ~(0xFU << shift))
                       | ((uint32_t)FunctionNr << shift);
    }

    argument = argumentBase | (uint32_t)SDCARD_SWITCH_FUNC_MODE_CHECK;
    // first check if function is supported
    Status = SDIOHost_ExecCMD6Command(pSlot, argument, TmpBuffer, FunctionNr, GroupNr);
    if (Status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else if (SDCARD_SWICH_FUNC_GET_STAT_CODE(TmpBuffer, GroupNr) == 0xFU) {
        // if status code for function is 0xF
        // then function is not supported by a card
        DbgMsg(DBG_GEN_MSG, DBG_CRIT, "Function %d in Group %d is not supported\n",
                FunctionNr, GroupNr);
        Status = SDIO_ERR_FUNCTION_UNSUPP;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else {

        argument = argumentBase | (uint32_t)SDCARD_SWITCH_FUNC_MODE_SWITCH;
        // execute command to switch function
        Status = SDIOHost_ExecCMD6Command(pSlot, argument, TmpBuffer, FunctionNr, GroupNr);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else if (SDCARD_SWICH_FUNC_GET_STAT_CODE(TmpBuffer, GroupNr) != FunctionNr) {
            // Status indicates the same function number as specified in the argument,
            // which means Supported function successful function change.
            Status = SDIO_ERR_SWITCH_ERROR;
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            Status = SDIO_ERR_NO_ERROR;
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SwitchFunction(CSDD_SDIO_Slot* pSlot, uint8_t FunctionNr,
                                uint8_t GroupNr)
{
    uint8_t Status;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_SDMEM) {
        // this function can be executed only on SD cards
        Status = SDIO_ERR_UNSUPPORTED_COMMAND;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else {

        DbgMsg(DBG_GEN_MSG, DBG_FYI, "FunctionNr %d, GroupNr %d\n", FunctionNr, GroupNr);

        Status = SDIOHost_ProcessSwitchFunction(pSlot, FunctionNr, GroupNr);
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SDCardUhsiSupported(CSDD_SDIO_Slot* pSlot, uint8_t *UhsiSupported)
{
    uint8_t Status = SDIO_ERR_NO_ERROR;
    const uint8_t GroupNr = 1;
    uint8_t FunctionNr = SDCARD_SWITCH_ACCESS_MODE_SDR50;
    uint8_t *TmpBuffer;

    if (pSlot == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else
    {
        *UhsiSupported = 0;

        if (pSlot->pDevice->SpecVersNumb >= 1U) {

            uint32_t argument = 0U;
            const uint32_t shift = ((GroupNr - 1U) * 4U);
            if (shift < 32U) {
                argument = (uint32_t)(0xFFFFFFU & ~(0xFU << shift))
                           | ((uint32_t)FunctionNr << shift)
                           | (uint32_t)SDCARD_SWITCH_FUNC_MODE_CHECK;
            }

            TmpBuffer = (uint8_t*)pSlot->AuxBuff;

            // first check if function is supported
            Status = SDIOHost_ExecCMD6Command(pSlot, argument, TmpBuffer,
                                              FunctionNr, GroupNr);
            if (Status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
            } else {
                // if status code for function is 0xF
                // then function is not supported by a card
                if (SDCARD_SWICH_FUNC_GET_STAT_CODE(TmpBuffer, GroupNr) == 0xFU) {
                    *UhsiSupported = 0;
                }
                else if (SDCARD_SWICH_FUNC_GET_STAT_CODE(TmpBuffer, GroupNr) == FunctionNr) {
                    *UhsiSupported = 1;
                } else {
                    // All 'if ... else if' constructs shall be terminated with an 'else' statement
                    // (MISRA2012-RULE-15_7-3)
                }
            }
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SDCardSetCurrentLimit(CSDD_SDIO_Slot*              pSlot,
                                       CSDD_DriverCurrentLimit CurrentLimit)
{
    uint8_t status = SDIO_ERR_UNSUPORRTED_OPERATION;
    if ((uint8_t)CurrentLimit > (uint8_t)CSDD_SDCARD_SWITCH_CURRENT_LIMIT_800) {
        status = SDIO_ERR_INVALID_PARAMETER;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        switch(pSlot->pDevice->deviceType) {
        case (uint8_t)CSDD_CARD_TYPE_SDMEM:
            status =  SDIOHost_SwitchFunction(pSlot, (uint8_t)CurrentLimit,
                                              SDCARD_SWITCH_GROUP_NR_4);
            break;
        default:
            //
            break;
        }
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_SDCardSetDrvStrength(CSDD_SDIO_Slot* pSlot,
                                         CSDD_DriverStrengthType DriverStrength)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t cardDriverStrength;

    switch(DriverStrength) {
    case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_A:
        cardDriverStrength = SDCARD_SWITCH_DRIVER_STRENGTH_A_TYPE;
        break;
    case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_B:
        cardDriverStrength = SDCARD_SWITCH_DRIVER_STRENGTH_B_TYPE;
        break;
    case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_C:
        cardDriverStrength = SDCARD_SWITCH_DRIVER_STRENGTH_C_TYPE;
        break;
    case CSDD_SWITCH_DRIVER_STRENGTH_TYPE_D:
        cardDriverStrength = SDCARD_SWITCH_DRIVER_STRENGTH_D_TYPE;
        break;
    default:
        status = SDIO_ERR_INVALID_PARAMETER;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        switch(pSlot->pDevice->deviceType) {
        case (uint8_t)CSDD_CARD_TYPE_SDMEM:
            status = SDIOHost_SwitchFunction(pSlot, cardDriverStrength,
                                             SDCARD_SWITCH_GROUP_NR_3);
            break;
        default:
            status = SDIO_ERR_UNSUPORRTED_OPERATION;
            break;
        }

        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcSetExtCsd(CSDD_SDIO_Slot* pSlot, uint8_t ByteNr,
                              uint8_t NewValue, uint8_t Mask)
{
    uint8_t* TmpBuffer = (uint8_t*)pSlot->AuxBuff;

    // Read Extended CSD register from a card
    uint8_t Status = SDIOHost_ReadExCSD(pSlot, TmpBuffer);
    if (Status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else {

        // get byte for EXT_CSD register
        uint8_t ByteNew = (GET_BYTE_FROM_BUFFER(TmpBuffer, ByteNr) & ~Mask) | NewValue;

        // set new value to CSD register
        Status = SDIOHost_MmcSwitch(pSlot, ByteNr, ByteNew);
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {

            // Read Extended CSD register from a card
            Status = SDIOHost_ReadExCSD(pSlot, TmpBuffer);
            if (Status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
            } else {

                uint8_t ByteOld = GET_BYTE_FROM_BUFFER(TmpBuffer, ByteNr);

                if (ByteNew != ByteOld) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "%s",
                                 "Written and read byte of EXT_CSD are different\n");
                    Status = SDIO_ERR_SETTING_EXT_CSD_FAILED;
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
                }
            }
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

static uint8_t SDIOHost_PartitionToPartConfig(CSDD_ParitionAccess partition, uint8_t* partConfig)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t partCfg;

    switch(partition) {
    case CSDD_EMMC_ACCCESS_BOOT_NONE:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_NONE;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_1:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_BP_1;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_2:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_BP_1;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_1:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_GP_1;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_2:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_GP_2;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_3:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_GP_3;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_GENERAL_PURP_4:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_GP_4;
        break;
    case CSDD_EMMC_ACCCESS_BOOT_RPMB:
        partCfg = MMC_EXCSD_BOOTPART_ACCESS_RPMB;
        break;
    default:
        status = SDIO_ERR_INVALID_PARAMETER;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        *partConfig = partCfg;
    }

    return (status);
}

//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcSetPartAccess(CSDD_SDIO_Slot* pSlot, CSDD_ParitionAccess Partition)
{

    uint8_t PartConfig;

    uint8_t Status = SDIOHost_PartitionToPartConfig(Partition, &PartConfig);

    if (Status == SDIO_ERR_NO_ERROR) {
        Status = SDIOHost_MmcSetExtCsd(pSlot, MMC_EXCSD_BOOT_PART_CONFIG,
                                       PartConfig, MMC_EXCSD_BOOTPART_ACCESS_MASK);

        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcSetBootAck(CSDD_SDIO_Slot* pSlot, bool enableBootAck)
{
    /* TODO create separate function */
    return SDIOHost_MmcSetExtCsd(pSlot, MMC_EXCSD_BOOT_PART_CONFIG,
                                 enableBootAck,
                                 MMC_EXCSD_BOOTPART_CFG_BOOT_ACK);

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcSetBootPartition(CSDD_SDIO_Slot* pSlot, CSDD_ParitionBoot Partition)
{
    uint8_t Status = SDIO_ERR_NO_ERROR;
    uint8_t PartConfig;

    switch(Partition) {
    case CSDD_EMMC_BOOT_NONE:
        PartConfig = MMC_EXCSD_BOOTPART_CFG_BOOT_DISABLE;
        break;
    case CSDD_EMMC_BOOT_1:
        PartConfig = MMC_EXCSD_BOOTPART_CFG_BOOT1_EN;
        break;
    case CSDD_EMMC_BOOT_2:
        PartConfig = MMC_EXCSD_BOOTPART_CFG_BOOT2_EN;
        break;
    case CSDD_EMMC_BOOT_USER:
        PartConfig = MMC_EXCSD_BOOTPART_CFG_BOOTUSR_EN;
        break;
    default:
        Status = SDIO_ERR_INVALID_PARAMETER;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        break;
    }

    if (Status == SDIO_ERR_NO_ERROR) {
        Status = SDIOHost_MmcSetExtCsd(pSlot, MMC_EXCSD_BOOT_PART_CONFIG,
                                       PartConfig, MMC_EXCSD_BOOTPART_CFG_BOOT_EN_MASK);

        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        }
    }

    return (Status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcExecuteBoot(CSDD_SDIO_Slot* pSlot, void *Buffer, uint32_t BufSize)
{
    uint8_t status;

    CSDD_Request Request = {0};

    //first reset CMD0 with 0xF0F0F0F0 to go to pre-boot state
    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD0, .arg = 0xF0F0F0F0U, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_NO_RESP, .hwRespCheck = 0}));
    SDIOHost_ExecCardCommand(pSlot, &Request);
    SDIOHost_CheckBusy(Request.pSdioHost, &Request);
    if (Request.status != SDIO_ERR_NO_ERROR) {
        status = Request.status;
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        //next execute CMD0 with 0xFFFFFFA to go to boot and read boot data
        SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD0, .arg = 0xFFFFFFFAU, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                                      .respType = CSDD_RESPONSE_NO_RESP, .hwRespCheck = 1}),
                                    &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = BufSize / 512U, .blkLen = 512,
                                                               .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_READ}));
        SDIOHost_ExecCardCommand( pSlot, &Request );

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);

        status = Request.status;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t SDIOHost_MmcGetPartitionBootSize(CSDD_SDIO_Slot* pSlot, uint32_t *BootSize)
{
    uint8_t Status;

    /// Read Extended CSD register from a card
    Status = SDIOHost_ReadExCSD(pSlot, (uint8_t*)pSlot->AuxBuff);
    if (Status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    } else {

        // get info boot partition size
        *BootSize = GET_BYTE_FROM_BUFFER(pSlot->AuxBuff,
                                         MMC_EXCSD_BOOT_SIZE_MULTI);

        *BootSize = MMC_EXCSD_BOOT_SIZE_MULTI_GET_SIZE(*BootSize);
    }

    return (Status);
}
//-----------------------------------------------------------------------------
