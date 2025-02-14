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
 * sdio_memory_card.c
 * SD Host controller driver - Memory card driver
 *****************************************************************************/

#include "sdio_host.h"
#include "sdio_card_general.h"
#include "sdio_errors.h"
#include "sdio_memory_card.h"
#include "sdio_debug.h"
#include "sdio_dma.h"
#include "sdio_request.h"
#include "sdio_utils.h"
#include "csdd_structs_if.h"

#ifndef SDIO_CFG_ENABLE_MMC
    #error "SDIO_CFG_ENABLE_MMC should be defined explicitly"
#endif

static uint8_t MemoryCard_Initialize(CSDD_SDIO_Host* pD, uint8_t slotIndex);
static uint8_t MemoryCard_Deinitialize(CSDD_SDIO_Host* pD, uint8_t slotIndex);

struct MemCards_s {
    CSDD_MEMORY_CARD_INFO Card;
    uint8_t Used;
};

static struct MemCards_s MemCards[CSDD_MAX_DEV_PER_SLOT * SDIO_SLOT_COUNT];

static CSDD_MEMORY_CARD_INFO *GetUnusedCard(void)
{
    CSDD_MEMORY_CARD_INFO* result = NULL;

    uint32_t i;
    for(i = 0; i < SDIO_SLOT_COUNT; i++) {
        if (MemCards[i].Used == 0U) {
            MemCards[i].Used = 1U;
            result = &MemCards[i].Card;
            break;
        }
    }
    return (result);
}

static void FreeCard(const CSDD_MEMORY_CARD_INFO *pCard)
{
    uint32_t i;
    for(i = 0; i < SDIO_SLOT_COUNT; i++) {
        if (&MemCards[i].Card == pCard) {
            MemCards[i].Used = 0U;
        }
    }
}

static CSDD_Request gRequest;

//------------------------------------------------------------------------------------------
void MemoryCard_LoadDriver(void)
{
    static CSDD_DeviceInfo SD_Card = {
        .manufacturerCode = 0,
        .manufacturerInformation = 0,
        .deviceType = (uint8_t)CSDD_CARD_TYPE_SDMEM,
        .pCardInterruptHandler = NULL,
        .pCardInitialize = MemoryCard_Initialize,
        .pCardDeinitialize = MemoryCard_Deinitialize,
    };

    static CSDD_DeviceInfo MMC_Card = {
        .manufacturerCode = 0,
        .manufacturerInformation = 0,
        .deviceType = (uint8_t)CSDD_CARD_TYPE_MMC,
        .pCardInterruptHandler = NULL,
        .pCardInitialize = MemoryCard_Initialize,
        .pCardDeinitialize = MemoryCard_Deinitialize,
    };

    uint32_t i;
    for(i = 0; i < SDIO_SLOT_COUNT; i++) {
        MemCards[i].Used = 0;
    }

    // add supported by driver devices to list
    (void)SDIOHost_AddItem( SuppDevList, &SD_Card );
    (void)SDIOHost_AddItem( SuppDevList, &MMC_Card );
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
/* parasoft-begin-suppress MISRA2012-RULE-12_2-2 "Shifting operation should be checked, DRV-5093" */
static uint8_t MemoryCard_CalcDeviceSizeMB(CSDD_SDIO_Device* pDevice, uint8_t CSDStructVer,
                                           const uint32_t Buffer_CSD[4], uint32_t* deviceSizeMB)
{
    uint8_t Status = SDIO_ERR_NO_ERROR;
    uint32_t CSize, CSizeMult, ReadBlLen, Mult, BlockNR, BlockLen;

    uint8_t* Buffer_ExCSD = (uint8_t*)pDevice->pSlot->AuxBuff;
// work around for device size
    if ( pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC ) {
        CSize = ( ( Buffer_CSD[2] & 0x3U ) << 10  ) | ( Buffer_CSD[1] >> 22 );
        if ( CSize == 0xFFFU ) {
            // memory capacity over 2GB

            /// Read Extended CSD register from a card
            Status = SDIOHost_ReadExCSD( pDevice->pSlot, Buffer_ExCSD );
            if (Status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
            } else {
                const uint32_t devSizePart215 = (uint32_t)Buffer_ExCSD[215] << (13 /*24 - 11*/);
                const uint32_t devSizePart214 = (uint32_t)Buffer_ExCSD[214] << (5 /*16 - 11*/);
                const uint32_t devSizePart213 = (uint32_t)Buffer_ExCSD[213] >> (3 /*11 -  8*/);

                *deviceSizeMB = devSizePart215 | devSizePart214 | devSizePart213;
            }

        } else {
            CSizeMult = ( Buffer_CSD[1] >> 7 ) & 0x7U;
            Mult = (uint32_t)1U << (CSizeMult + 2U);
            ReadBlLen = ( Buffer_CSD[2] >> 8 ) & 0xFU;
            BlockLen = (uint32_t)1U << ReadBlLen;
            BlockNR =  ( CSize + 1U ) * Mult;

            *deviceSizeMB = (uint32_t)(BlockNR * BlockLen) / (uint32_t)(1024UL * 1024UL);
        }
    } else {
        // SD card structure version 2
        if ( CSDStructVer == 1U ) {
            CSize = ( Buffer_CSD[2] >> 16 ) & 0xFFFFU;
            CSize |= ((Buffer_CSD[1] & 0x3FU) << 16);
            /*((CSize + 1) * 512 * 1024) / (1024 * 1024)*/
            *deviceSizeMB = (CSize + 1U) / 2U;
        } else {
            //FIXME: In case of CSDStructVer != 1U, This function returns SDIO_ERR_NO_ERROR
            //without setting deviceSizeMB.
        }
    }

    return (Status);
}
/* parasoft-end-suppress MISRA2012-RULE-12_2-2 */
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_GetCSD( CSDD_SDIO_Device* pDevice )
{
    CSDD_MEMORY_CARD_INFO* pCard;
    uint32_t Buffer[4];
    uint8_t CSDStructVer;
    uint8_t Status;
    uint32_t deviceSizeMB = 0;

    if ((pDevice->pSlot == NULL)
        || (pDevice->CardDriverData == NULL)) {

        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        pCard = pDevice->CardDriverData;

        /// Read CSD register from a card
        Status = SDIOHost_ReadCSD( pDevice->pSlot, Buffer );
        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {

            CSDStructVer = (uint8_t)( Buffer[3] >> 22 ) & 0x3U;
            pCard->commandClasses = (uint16_t)(Buffer[2] >> 12 ) & 0xFFFU;
            pCard->PartialReadAllowed = (uint8_t)( Buffer[2] >> 7 ) & 0x1U;
            pCard->PartialWriteAllowed = (uint8_t)( Buffer[0] >> 13 ) & 0x1U;
            pCard->WriteBlkMisalign = (uint8_t)( Buffer[2] >> 6 ) & 0x1U;
            pCard->ReadBlkMisalign = (uint8_t)( Buffer[2] >> 5 ) & 0x1U;
            pCard->EraseBlkEn = (uint8_t)( Buffer[1] >> 6 ) & 0x1U;

            if ( (pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U ) {
                pCard->SectorSize = (uint16_t)( ( ( Buffer[1] & 0x3FU ) << 1  ) | ( Buffer[0] >> 31 ) ) + 1U;
            }

            Status = MemoryCard_CalcDeviceSizeMB(pDevice, CSDStructVer,
                                                 Buffer, &deviceSizeMB);

            if (Status == SDIO_ERR_NO_ERROR) {
                pCard->DeviceSizeMB = deviceSizeMB;

                if (pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
                    pDevice->SpecVersNumb = (uint8_t)( Buffer[3] >> 18 ) & 0xFU;
                }

                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Card CSD register - %08x %08x %08x %08x\n",
                            Buffer[0], Buffer[1], Buffer[2], Buffer[3]);

                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Card size equals %ldMB\n", pCard->DeviceSizeMB);

                // all cards support this block size
                pCard->BlockSize = 512;
            }
        }
    }

    return (Status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_GetSecCount(const CSDD_SDIO_Device* pDevice, uint32_t *sectorCount)
{
    CSDD_MEMORY_CARD_INFO *pCard;
    pCard = pDevice->CardDriverData;

    *sectorCount = pCard->DeviceSizeMB * 2U * 1024U;

    return 0;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_ProcessInitialize(CSDD_SDIO_Device* pDevice, CSDD_MEMORY_CARD_INFO* pCard)
{
    uint8_t i;
    CSDD_Request Request = {0};

    if (pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) {
        if (pDevice->SpecVersNumb < 4U) {
            pDevice->SupportedBusWidths = (uint8_t)CSDD_BUS_WIDTH_1;
        } else {
            pDevice->SupportedBusWidths = (uint8_t)((uint8_t)CSDD_BUS_WIDTH_1
                                          | (uint8_t)CSDD_BUS_WIDTH_4
                                          | (uint8_t)CSDD_BUS_WIDTH_8);
        }
    }

    (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );
    // set block length in the card
    uint16_t argument = 0U;
    for (i = 9U; i < 13U; i++) {
        if (i < 32U) {
            argument = (uint16_t)1U << i;
        }
        if (argument == pCard->BlockSize) {
            break;
        }
    }

    SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD16, .arg = argument, .cmdType = CSDD_CMD_TYPE_NORMAL,
                                                        .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));
    // In High Capacity card and in
    // Normal Capacity card with partial block read allowed in CSD.
    // CMD16 command will effective only for LOCK_UNLOCK command.
    SDIOHost_ExecCardCommand( pDevice->pSlot, &Request );
    SDIOHost_CheckBusy(Request.pSdioHost, &Request);

    uint8_t status = Request.status;
    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {
        pDevice->CardDriverData = pCard;
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_Initialize(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    uint8_t Status;
    CSDD_MEMORY_CARD_INFO *pCard;
    CSDD_SDIO_Device* pDevice;
    CSDD_SDIO_Host* pSdioHost = pD;

    if (pSdioHost == NULL) {
        Status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        pDevice = pSdioHost->Slots[slotIndex].pDevice;

        if ( pDevice == NULL ) {
            Status = SDIO_ERR_DEV_NULL_POINTER;
        } else {

            pCard = GetUnusedCard();
            if ( pCard == NULL ) {
                Status = SDIO_ERR_MEM_ALLOC;
            } else {

                pDevice->CardDriverData = pCard;

                Status = MemoryCard_GetCSD (pDevice);
                if (Status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
                } else {

                    Status = MemoryCard_ProcessInitialize(pDevice, pCard);
                }
            }
        }
    }

    return (Status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_Deinitialize(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    uint8_t status;
    CSDD_SDIO_Device* pDevice;
    CSDD_SDIO_Host* pSdioHost = pD;

    if (pSdioHost == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        pDevice = pSdioHost->Slots[slotIndex].pDevice;

        if ( pDevice == NULL ) {
            status = SDIO_ERR_DEV_NULL_POINTER;
        } else {

            FreeCard(pDevice->CardDriverData);

            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_SetBlockLength(CSDD_SDIO_Device* pDevice, uint32_t BlockLength)
{
    uint8_t status;
    CSDD_Request Request = {0};
    CSDD_MEMORY_CARD_INFO* pCard;

    if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        if (pDevice->pSlot->AccessMode == (uint8_t)CSDD_ACCESS_MODE_HS_DDR) {
            if (BlockLength == 512U) {
                status = SDIO_ERR_NO_ERROR;
            } else{
                /* in DDR mode CMD16 command is illegal */
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
                status = SDIO_ERR_INVALID_PARAMETER;
            }
        } else {

            pCard = pDevice->CardDriverData;

            if (pCard == NULL) {
                status = SDIO_ERR_INVALID_PARAMETER;
            } else {

                (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

                SDIO_REQ_INIT_CMD(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD16, .arg = BlockLength,
                                                                    .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}));

                // start data transfer
                SDIOHost_ExecCardCommand( pDevice->pSlot, &Request );

                SDIOHost_CheckBusy(Request.pSdioHost, &Request);

                status = Request.status;

                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
                } else {
                    pCard->BlockSize = (uint16_t)BlockLength;
                }
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_PartialDataTransferCheckPrecondCard(const CSDD_SDIO_Device* pDevice, uint32_t Address,
                                                              uint32_t BufferSize, CSDD_TransferDirection TransferDirection)
{
    uint8_t status;
    CSDD_MEMORY_CARD_INFO* pCard = pDevice->CardDriverData;

    if (TransferDirection == CSDD_TRANSFER_WRITE) { //write
        // if write partial is not allowed then finish with error
        if (pCard->PartialWriteAllowed == 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        }
        // if write block misalign is not allowed then crossing physical block boundaries is invalid
        else if ((pCard->WriteBlkMisalign == 0U)
                 && ((Address / 512U) != (((Address + BufferSize) - 1U) / 512U))) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        } else {
            status = SDIO_ERR_NO_ERROR;
        }

    } else { // read
        // if read partial is not allowed then finish with error
        if (pCard->PartialReadAllowed == 0U) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        }
        // if write block misalign is not allowed then crossing physical block boundaries is invalid.
        else if ((pCard->ReadBlkMisalign == 0U)
                 && ((Address / 512U) != (((Address + BufferSize) - 1U) / 512U))) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
            status = SDIO_ERR_INVALID_PARAMETER;
        } else {
            status = SDIO_ERR_NO_ERROR;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static inline bool IsWriteToWriteProtectedSd(const CSDD_SDIO_Device* pDevice, CSDD_TransferDirection TransferDirection)
{
    return (((pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U)
            && (TransferDirection == CSDD_TRANSFER_WRITE)
            && (IS_CARD_WRITE_PROTECT(pDevice->pSlot)));
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_PartialDataTransferCheckPrecond(const CSDD_SDIO_Device* pDevice, uint32_t Address,
                                                          uint32_t BufferSize, CSDD_TransferDirection TransferDirection, bool* transferNeeded)
{
    uint8_t status;
    bool isTransferNeeded = true;

    if ( pDevice == NULL ) {
        status = SDIO_ERR_DEV_NULL_POINTER;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->CardDriverData == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (BufferSize > 512U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (BufferSize == 0U) {
        status = SDIO_ERR_NO_ERROR;
        isTransferNeeded = false;
    } else if ((BufferSize % 4U) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if ( pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_HIGH ) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_UNSUPORRTED_OPERATION);
        status = SDIO_ERR_UNSUPORRTED_OPERATION;
    } else if (IsWriteToWriteProtectedSd(pDevice, TransferDirection)) {
        status = SDIO_ERR_CARD_WRITE_PROTECTED;
    } else {

        status = MemoryCard_PartialDataTransferCheckPrecondCard(pDevice, Address,
                                                                BufferSize, TransferDirection);
    }

    *transferNeeded = isTransferNeeded;
    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_PartialDataTransfer(CSDD_SDIO_Device* pDevice, uint32_t Address,
                                       void* Buffer, uint32_t BufferSize,
                                       CSDD_TransferDirection TransferDirection)
{
    bool isTransferNeeded;
    uint8_t status = MemoryCard_PartialDataTransferCheckPrecond(pDevice, Address,
                                                                BufferSize, TransferDirection,
                                                                &isTransferNeeded);

    if ((status == SDIO_ERR_NO_ERROR) && isTransferNeeded) {

        CSDD_MEMORY_CARD_INFO* pCard = pDevice->CardDriverData;

        if (BufferSize != pCard->BlockSize) {
            status = MemoryCard_SetBlockLength(pDevice, BufferSize);
        }

        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {
            CSDD_Request Request = {0};

            (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

            const uint8_t command = (TransferDirection == CSDD_TRANSFER_WRITE) ? SDIO_CMD24 : SDIO_CMD17;
            SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = command, .arg = Address,
                                                                          .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                        &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = 1, .blkLen = (uint16_t)BufferSize,
                                                                   .auto12 = 0, .auto23 = 0, .dir = TransferDirection}));

            // start data transfer
            SDIOHost_ExecCardCommand( pDevice->pSlot, &Request );

            SDIOHost_CheckBusy(Request.pSdioHost, &Request);

            status = Request.status;
            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Request.status);
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_FinishXferNonBlock(CSDD_Request* pRequest)
{
    SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);

    return (pRequest->status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_DataXferNonBlockCheckPrecond(const CSDD_SDIO_Device* pDevice, uint32_t BufferSize,
                                                           CSDD_TransferDirection TransferDirection, bool* transferNeeded)
{
    uint8_t status;
    bool isTranserNeeded = true;

    if (BufferSize == 0U) {
        status = SDIO_ERR_NO_ERROR;
        isTranserNeeded = false;
    } else if ( pDevice == NULL ) {
        status = SDIO_ERR_DEV_NULL_POINTER;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->CardDriverData == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if ((BufferSize % 512U) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if ((!USE_AUTO_CMD) && (pDevice->pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD)) {
        status = SDIO_ERR_CANT_EXECUTE;
    } else if (IsWriteToWriteProtectedSd(pDevice, TransferDirection)) {
        status = SDIO_ERR_CARD_WRITE_PROTECTED;
    } else {
        status = SDIO_ERR_NO_ERROR;
    }

    *transferNeeded = isTranserNeeded;
    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_DataXferCalcCommand(uint32_t BlockCount, CSDD_TransferDirection TransferDirection)
{
    uint8_t Command;

    if (BlockCount == 1U) {
        // single block transfer
        Command = (TransferDirection == CSDD_TRANSFER_WRITE) ? SDIO_CMD24 : SDIO_CMD17;
    } else {
        // multiple block transfer
        Command = (TransferDirection == CSDD_TRANSFER_WRITE) ? SDIO_CMD25 : SDIO_CMD18;
    }

    return (Command);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_SetBlockLengthTo512(CSDD_SDIO_Device* pDevice, const CSDD_MEMORY_CARD_INFO* pCard)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (pCard->BlockSize != 512U) {
        status = MemoryCard_SetBlockLength(pDevice, 512U);
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_ProcessDataTransferNonBlock(CSDD_SDIO_Device* pDevice, uint32_t Address,
                                                      void* Buffer, uint32_t BufferSize, CSDD_TransferDirection TransferDirection,
                                                      const CSDD_MEMORY_CARD_INFO* pCard, void **Request)
{
    uint8_t Status = SDIO_ERR_NO_ERROR;
    uint8_t TransMode;
    uint32_t BlockCount, argument;
    uint16_t BlockLen;
    uint8_t autoCMD12Enable = 0;
    uint8_t autoCMD23Enable = 0;
    uint8_t Command;

    (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

    if (pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_NORMAL) {
        BlockLen = pCard->BlockSize;
        // Data address is in byte units in a Standard Capacity SD memory card and MMC memory card
        argument = Address * 512U;
    } else if (pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_HIGH) {
        BlockLen = 512U;
        argument = Address;
    } else {
        Status = SDIO_ERR_INVALID_PARAMETER;
    }

    if (Status == SDIO_ERR_NO_ERROR) {

        BlockCount = ((BufferSize - 1U) / pCard->BlockSize) + 1U;

        Command = MemoryCard_DataXferCalcCommand(BlockCount, TransferDirection);

        if (BlockCount > 1U) { // multiple block transfer
            if (pDevice->CMD23Supported != 0U) {
                // block count and block length are necessary to
                // specify data transmission mode type
                gRequest.pCmd->blockCount = BlockCount;
                gRequest.pCmd->blockLen = BlockLen;
                gRequest.pCmd->requestFlags.isInfinite = 0;
                TransMode = DMA_SpecifyTransmissionMode(pDevice->pSlot, &gRequest);
                if ((TransMode != (uint8_t)CSDD_SDMA_MODE) /*&& USE_AUTO_CMD*/) {
                    // if card supports CMD23, and auto command should be used and
                    // transmission mode is not SDMA then use auto CMD23
                    autoCMD23Enable = 1U;
                } else {
                    // if card supports CMD23, and auto CMD23 command can't be used
                    // then execute CMD23 manually
                    Status = SDIOHost_ExecCMD23Command(pDevice->pSlot, BlockCount);
                }
            } else {
                /*if (USE_AUTO_CMD)*/
                autoCMD12Enable = 1U;
            }
        }

        if (Status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
        } else {
            *Request = &gRequest;
            SDIO_REQ_INIT_CMD_WITH_DATA(&gRequest, &((SD_CsddRequesParams){.cmd = Command, .arg = argument,
                                                                           .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                        &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = BlockCount, .blkLen = BlockLen,
                                                                   .auto12 = autoCMD12Enable, .auto23 = autoCMD23Enable, .dir = TransferDirection}));
            // start data transfer
            SDIOHost_ExecCardCommand( pDevice->pSlot, &gRequest );

        }
    }

    return (Status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_DataXferNonBlock(CSDD_SDIO_Device* pDevice, uint32_t Address,
                                        void* Buffer, uint32_t BufferSize, CSDD_TransferDirection TransferDirection,
                                        void **Request)
{
    CSDD_MEMORY_CARD_INFO* pCard;
    bool isTransferNeeded;
    uint8_t Status;

    Status = MemoryCard_DataXferNonBlockCheckPrecond(pDevice, BufferSize,
                                                         TransferDirection, &isTransferNeeded);

    if ((Status == SDIO_ERR_NO_ERROR) && isTransferNeeded) {

        pCard = pDevice->CardDriverData;

        Status = MemoryCard_SetBlockLengthTo512(pDevice, pCard);

        if (Status == SDIO_ERR_NO_ERROR) {

            Status = MemoryCard_ProcessDataTransferNonBlock(pDevice, Address,
                                                            Buffer, BufferSize, TransferDirection,
                                                            pCard, Request);
        }
    }

    return (Status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_DataXfer(CSDD_SDIO_Device* pDevice, uint32_t Address,
                                uint8_t *Buffer, uint32_t BufferSize, CSDD_TransferDirection TransferDirection)
{
    return MemoryCard_DataXfer2(pDevice, Address, Buffer, BufferSize, TransferDirection, 0);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_DataXfer2CheckPrecond(const CSDD_SDIO_Device* pDevice,
                                                    uint32_t BufferSize, CSDD_TransferDirection TransferDirection,
                                                    uint32_t SubBufferCount, bool* transferNeeded)
{
    uint8_t status;
    bool isTransferNeeded = true;

    if ((BufferSize % 512U) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if ( pDevice == NULL ) {
        status = SDIO_ERR_DEV_NULL_POINTER;
    } else if ((BufferSize == 0U) && (SubBufferCount == 0U)) {
        status = SDIO_ERR_NO_ERROR;
        isTransferNeeded = false;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->CardDriverData == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (IsWriteToWriteProtectedSd(pDevice, TransferDirection)) {
        status = SDIO_ERR_CARD_WRITE_PROTECTED;
    } else {
        status = SDIO_ERR_NO_ERROR;
    }

    *transferNeeded = isTransferNeeded;
    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static void MemoryCard_ProcessDataTransfer2CalcArgAndBlockLen(const CSDD_SDIO_Device* pDevice, uint32_t Address, const CSDD_MEMORY_CARD_INFO* pCard, uint32_t* argument, uint16_t* blockLength)
{
    uint32_t arg;
    uint16_t blockLen;

    if (pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_HIGH) {
        blockLen = 512U;
        arg = Address;
    } else {
        blockLen = pCard->BlockSize;
        // Data address is in byte units in a Standard Capacity SD memory card and MMC memory card
        arg = Address * 512U;
    }

    *blockLength = blockLen;
    *argument = arg;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_ProcessDataTransfer2ExecCardCommand(CSDD_SDIO_Device* pDevice, CSDD_TransferDirection TransferDirection,
                                                              CSDD_Request* pRequest,
                                                              const SD_CsddRequesParams* params,
                                                              const SD_CsddRequesParamsExt* paramsExt)
{
    uint8_t status;

    SDIO_REQ_INIT_CMD_WITH_DATA(pRequest, params,
                                paramsExt);

    // start data transfer
    SDIOHost_ExecCardCommand( pDevice->pSlot, pRequest );
    SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);
    status = pRequest->status;

    if (status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
    } else {

        if ( pRequest->pCmd->blockCount > 1U ) {
            if ((pDevice->CMD23Supported == 0U) && (!USE_AUTO_CMD) && (pDevice->pSlot->dmaModeSelected != CSDD_ADMA3_MODE)
                && (pDevice->pSlot->InterfaceType == (uint8_t)CSDD_INTERFACE_TYPE_SD)) {

                if ((pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) && (TransferDirection == CSDD_TRANSFER_READ)) {
                    (void)SDIOHost_ExecCMD12Command(pDevice->pSlot, CSDD_RESPONSE_R1);
                } else {
                    (void)SDIOHost_ExecCMD12Command(pDevice->pSlot, CSDD_RESPONSE_R1B);
                }
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_ProcessDataTransfer2( CSDD_SDIO_Device* pDevice, uint32_t Address,
                                                void* Buffer, uint32_t BufferSize, CSDD_TransferDirection TransferDirection,
                                                uint32_t SubBufferCount, const CSDD_MEMORY_CARD_INFO* pCard)
{
    CSDD_Request Request = {0};
    uint8_t Status = SDIO_ERR_NO_ERROR;
    uint8_t TransMode;
    uint32_t BlockCount = 0, argument;
    uint16_t BlockLen;
    uint8_t autoCMD12Enable = 0;
    uint8_t autoCMD23Enable = 0;
    uint8_t Command;

    (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

    MemoryCard_ProcessDataTransfer2CalcArgAndBlockLen(pDevice, Address, pCard, &argument, &BlockLen);

    if (BufferSize != 0U) {
        BlockCount = ((BufferSize - 1U) / pCard->BlockSize) + 1U;
    }

    Command = MemoryCard_DataXferCalcCommand(BlockCount, TransferDirection);

    if (BlockCount > 1U) {

        if (pDevice->CMD23Supported != 0U) {
            // block count and block length are necessary to
            // specify data transmission mode type
            Request.pCmd->blockCount = BlockCount;
            Request.pCmd->blockLen = BlockLen;
            Request.pCmd->requestFlags.isInfinite = 0;
            TransMode = DMA_SpecifyTransmissionMode(pDevice->pSlot, &Request);
            if ((TransMode != (uint8_t)CSDD_SDMA_MODE) && USE_AUTO_CMD) {
                // if card supports CMD23, and auto command should be used and
                // transmission mode is not SDMA then use auto CMD23
                autoCMD23Enable = 1;
            } else {
                // if card supports CMD23, and auto CMD23 command can't be used
                // then execute CMD23 manually
                Status = SDIOHost_ExecCMD23Command(pDevice->pSlot, BlockCount);
                if (Status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
                }
            }
        }
        else {
            autoCMD12Enable = USE_AUTO_CMD;
        }
    }

    if (Status == SDIO_ERR_NO_ERROR) {

        Status = MemoryCard_ProcessDataTransfer2ExecCardCommand(pDevice, TransferDirection,
                                                                &Request,
                                                                &((SD_CsddRequesParams){.cmd = Command, .arg = argument,
                                                                                        .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 1}),
                                                                &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = BlockCount, .blkLen = BlockLen,
                                                                                           .auto12 = autoCMD12Enable, .auto23 = autoCMD23Enable, .dir = TransferDirection,
                                                                                           .subBuffersCount = (uint8_t)SubBufferCount}));

    }

    return (Status);
}

//------------------------------------------------------------------------------------------

// Address is in block (512 Byte) units
//------------------------------------------------------------------------------------------
uint8_t MemoryCard_DataXfer2( CSDD_SDIO_Device* pDevice, uint32_t Address,
                                  void *Buffer, uint32_t BufferSize, CSDD_TransferDirection TransferDirection,
                                  uint32_t SubBufferCount )
{
    CSDD_MEMORY_CARD_INFO* pCard;
    uint8_t Status;
    bool isTransferNeeded;

    Status = MemoryCard_DataXfer2CheckPrecond(pDevice,
                                                  BufferSize, TransferDirection,
                                                  SubBufferCount, &isTransferNeeded);

    if ((Status == SDIO_ERR_NO_ERROR) && isTransferNeeded) {

        pCard = pDevice->CardDriverData;

        Status = MemoryCard_SetBlockLengthTo512(pDevice, pCard);

        if (Status == SDIO_ERR_NO_ERROR) {

            Status = MemoryCard_ProcessDataTransfer2(pDevice, Address,
                                                     Buffer, BufferSize, TransferDirection,
                                                     SubBufferCount, pCard);
        }
    }

    return (Status);
}
//------------------------------------------------------------------------------------------

// Address is in block (512 Byte) units
//------------------------------------------------------------------------------------------
uint8_t MemoryCard_InfXferStart(CSDD_SDIO_Device* pDevice, uint32_t Address, void* Buffer,
                                         uint32_t BufferSize, CSDD_TransferDirection TransferDirection)
{
    uint8_t status;
    CSDD_MEMORY_CARD_INFO* pCard;
    uint32_t BlockCount, argument;
    uint16_t BlockLen;
    uint8_t Command;

    if ((BufferSize % 512U) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice == NULL) {
        status = SDIO_ERR_DEV_NULL_POINTER;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->CardDriverData == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (IsWriteToWriteProtectedSd(pDevice, TransferDirection)) {
        status = SDIO_ERR_CARD_WRITE_PROTECTED;
    } else {

        pCard = pDevice->CardDriverData;

        status = MemoryCard_SetBlockLengthTo512(pDevice, pCard);

        if (status == SDIO_ERR_NO_ERROR) {

            (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

            if (pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_HIGH) {
                BlockLen = 512U;
                argument = Address;
            }
            else {
                BlockLen = pCard->BlockSize;
                // Data address is in byte units in a Standard Capacity SD memory card and MMC memory card
                argument = Address * 512U;
            }

            BlockCount = ((BufferSize - 1U) / pCard->BlockSize) + 1U;

            // multiple block transfer
            Command = (TransferDirection == CSDD_TRANSFER_WRITE) ? SDIO_CMD25 : SDIO_CMD18;

            SDIO_REQ_INIT_CMD_DATA_INF_S(&gRequest, &((SD_CsddRequesParams){.cmd = Command, .arg = argument,
                                                                            .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                              &((SD_CsddRequesParamsExt){.buf = Buffer, .blkCount = BlockCount, .blkLen = BlockLen,
                                                                         .dir = TransferDirection}));

            // start data transfer
            SDIOHost_ExecCardCommand(pDevice->pSlot, &gRequest);

            SDIOHost_CheckBusy(gRequest.pSdioHost, &gRequest);

            status = gRequest.status;
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_InfXferContinue(CSDD_SDIO_Device* pDevice,
                                            void* Buffer, uint32_t BufferSize,
                                            CSDD_TransferDirection TransferDirection)
{
    uint8_t status;
    CSDD_MEMORY_CARD_INFO* pCard;
    uint32_t BlockCount;
    uint16_t BlockLen;

    if ((BufferSize % 512U) != 0U) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice == NULL) {
        status = SDIO_ERR_DEV_NULL_POINTER;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->CardDriverData == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (IsWriteToWriteProtectedSd(pDevice, TransferDirection)) {
        status = SDIO_ERR_CARD_WRITE_PROTECTED;
    } else {

        pCard = pDevice->CardDriverData;

        if (pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_HIGH) {
            BlockLen = 512U;
        } else {
            // Data address is in byte units in a Standard Capacity SD memory card and MMC memory card
            BlockLen = pCard->BlockSize;
        }

        BlockCount = ((BufferSize - 1U) / pCard->BlockSize) + 1U;

        SDIO_REQ_INIT_CMD_DATA_INF_N(&gRequest, Buffer, BlockCount,
                                    BlockLen, TransferDirection);

        // start data transfer
        SDIOHost_ExecCardCommand( pDevice->pSlot, &gRequest );
        SDIOHost_CheckBusy(gRequest.pSdioHost, &gRequest);

        status = gRequest.status;
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_InfDataXferFinish(CSDD_SDIO_Device* pDevice, CSDD_TransferDirection TransferDirection)
{
    uint8_t Status;

    // wait for data transfer finish (user can change this value)
    if (TransferDirection == CSDD_TRANSFER_WRITE) {
        CPS_DelayNs(300000U);
    }

    Status = SDIOHost_Abort(pDevice->pSlot, 0);

    if (Status != SDIO_ERR_NO_ERROR) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", Status);
    }

    return (Status);;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_DataEraseCheckPrecond(const CSDD_SDIO_Device* pDevice, uint32_t blockCountVal, bool* ereaseNeeded)
{
    bool isEreaseNeeded = true;
    uint8_t status;

    if (blockCountVal == 0U) {
        status = SDIO_ERR_NO_ERROR;
        isEreaseNeeded = false;
    } else if (pDevice == NULL) {
        status = SDIO_ERR_DEV_NULL_POINTER;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (((pDevice->deviceType & (uint8_t)CSDD_CARD_TYPE_SDMEM) != 0U)
               && (IS_CARD_WRITE_PROTECT(pDevice->pSlot))) {
        status = SDIO_ERR_CARD_WRITE_PROTECTED;
    } else {
        status = SDIO_ERR_NO_ERROR;
    }

    *ereaseNeeded = isEreaseNeeded;
    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_DataEraseExecCmd(CSDD_SDIO_Device* pDevice, CSDD_Request* pRequest,
                                           uint8_t command, uint32_t argument, CSDD_ResponseType responseType)
{
    SDIO_REQ_INIT_CMD(pRequest, &((SD_CsddRequesParams){.cmd = command, .arg = argument,
                                                        .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = responseType, .hwRespCheck = 0}));

    SDIOHost_ExecCardCommand(pDevice->pSlot, pRequest);
    SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);

    return pRequest->status;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_DataErase(CSDD_SDIO_Device* pDevice, uint32_t StartBlockAddress, uint32_t BlockCount)
{
    bool isEreaseNeeded;
    uint32_t blockCountVal = BlockCount;
    uint32_t startBlockAddressVal = StartBlockAddress;

    uint8_t status = MemoryCard_DataEraseCheckPrecond(pDevice, blockCountVal, &isEreaseNeeded);

    if ((status == SDIO_ERR_NO_ERROR) && isEreaseNeeded) {
        uint8_t command;
        CSDD_Request Request = {0};

        blockCountVal--;

        (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

        if ( pDevice->DeviceCapacity == (uint8_t)CSDD_CAPACITY_NORMAL ) {
            // Data address is in byte units
            // in a Standard Capacity SD memory card and MMC memory card
            startBlockAddressVal = startBlockAddressVal * 512U;
            blockCountVal = blockCountVal * 512U;
        }

        // Sets the address of the first write block to be erased.
        command = (pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) ? SDIO_CMD35 : SDIO_CMD32;

        status = MemoryCard_DataEraseExecCmd(pDevice, &Request,
                                             command, startBlockAddressVal, CSDD_RESPONSE_R1);

        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        } else {

            command = (pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_MMC) ? SDIO_CMD36 : SDIO_CMD33;

            // Sets the address of the last write block
            // of the continuous range to be erased.
            status = MemoryCard_DataEraseExecCmd(pDevice, &Request,
                                                 command, startBlockAddressVal + blockCountVal, CSDD_RESPONSE_R1);

            if (status != SDIO_ERR_NO_ERROR) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
            } else {

                // Erases all previously selected write blocks.
                status = MemoryCard_DataEraseExecCmd(pDevice, &Request,
                                                     SDIO_CMD38, 0, CSDD_RESPONSE_R1B);

                if (status != SDIO_ERR_NO_ERROR) {
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
                }
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

#if SDIO_CFG_ENABLE_MMC
//------------------------------------------------------------------------------------------
static uint8_t MemoryCard_ConfigureExecCmd(CSDD_SDIO_Device* pDevice, CSDD_MmcConfigCmd Cmd,
                                           const uint8_t* Data, uint8_t SizeOfData, CSDD_MEMORY_CARD_INFO* pCard)
{
    static uint8_t cfgBuffer[512];

    uint8_t status;
    CSDD_Request Request = {0};
    uint32_t i;

    if ( SizeOfData > 16U ) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        SDIO_REQ_INIT_CMD_WITH_DATA(&Request, &((SD_CsddRequesParams){.cmd = SDIO_CMD42, .arg = 0,
                                                                      .cmdType = CSDD_CMD_TYPE_NORMAL, .respType = CSDD_RESPONSE_R1, .hwRespCheck = 0}),
                                    &((SD_CsddRequesParamsExt){.buf = cfgBuffer, .blkCount = 1, .blkLen = pCard->BlockSize,
                                                               .auto12 = 0, .auto23 = 0, .dir = CSDD_TRANSFER_WRITE}));

        // set type of operation
        cfgBuffer[0] = (uint8_t)Cmd;
        // set size of password or passwords
        cfgBuffer[1] = SizeOfData;

        // copy password/passwords
        for ( i = 0; i < SizeOfData; i++ ) {
            cfgBuffer[i + 2U] = ((const uint8_t*)Data)[i];
        }

        for ( i = (uint32_t)2U + SizeOfData; i < pCard->BlockSize; i++) {
            cfgBuffer[i] = 0;
        }

        SDIOHost_ExecCardCommand( pDevice->pSlot, &Request );

        SDIOHost_CheckBusy(Request.pSdioHost, &Request);
        // check status
        status = Request.status;
        if (status != SDIO_ERR_NO_ERROR) {
            vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", status);
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
uint8_t MemoryCard_Configure(CSDD_SDIO_Device* pDevice, CSDD_MmcConfigCmd Cmd,
                             const uint8_t* Data, uint8_t SizeOfData)
{
    uint8_t status;

    if (pDevice == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->pSlot == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pDevice->CardDriverData == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {

        CSDD_MEMORY_CARD_INFO* pCard = pDevice->CardDriverData;

        (void)SDIOHost_SelectCard( pDevice->pSlot, pDevice->RCA );

        status = MemoryCard_SetBlockLengthTo512(pDevice, pCard);

        if (status == SDIO_ERR_NO_ERROR) {

            if ((SizeOfData < 1U) || (SizeOfData > 16U)) {
                vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
                status = SDIO_ERR_INVALID_PARAMETER;
            } else {

                switch( Cmd ) {
                case CSDD_MMC_CARD_CONF_SET_PASSWORD:
                case CSDD_MMC_CARD_CONF_RESET_PASSWORD:
                case CSDD_MMC_CARD_CONF_CARD_LOCK:
                case CSDD_MMC_CARD_CONF_CARD_UNLOCK:
                    status = MemoryCard_ConfigureExecCmd(pDevice, Cmd,
                                                         Data, SizeOfData, pCard);
                    break;
                default:
                    // wrong command value
                    vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Error %d\n", SDIO_ERR_INVALID_PARAMETER);
                    status = SDIO_ERR_INVALID_PARAMETER;
                    break;
                }
            }
        }
    }

    return (status);
}
//------------------------------------------------------------------------------------------
#endif
