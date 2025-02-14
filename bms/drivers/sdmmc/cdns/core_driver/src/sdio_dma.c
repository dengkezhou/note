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
 * sdio_dma.c
 * SD Host controller driver DMA module
 *****************************************************************************/

#include "sdio_dma.h"
#include "sdio_host.h"
#include "sdio_debug.h"
#include "sdio_utils.h"
#include "csdd_structs_if.h"


#ifndef SDIO_SDMA_SUPPORTED
    #error "SDIO_SDMA_SUPPORTED should be defined explicitly"
#endif

#ifndef SDIO_ADMA1_SUPPORTED
    #error "SDIO_ADMA1_SUPPORTED should be defined explicitly"
#endif

#ifndef SDIO_ADMA2_SUPPORTED
    #error "SDIO_ADMA2_SUPPORTED should be defined explicitly"
#endif

#ifndef SDIO_ADMA3_SUPPORTED
    #error "SDIO_ADMA2_SUPPORTED should be defined explicitly"
#endif

#if SDIO_ADMA3_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED
static uint8_t DMA_PrepareTransferADMA(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest,CSDD_CommandField* pCmd, uint8_t DMAMode,uint32_t *Descriptors, uint32_t *offset, uint32_t * ADMADescSize);

#define ADMA1_SIZE_OF_DESCRIPTOR        4U
#define ADMA2_SIZE_OF_DESCRIPTOR_32     8U
#define ADMA2_SIZE_OF_DESCRIPTOR_64     12U
#define ADMA2_SIZE_OF_DESCRIPTOR_64_HV4 16U

//------------------------------------------------------------------
// Macros for ADMA2 Length Mode
#define ADMA2_DESCRIPTOR_16_SHIFT   16U
#define ADMA2_DESCRIPTOR_16_MASK    0x0000FFFFU
#define ADMA2_DESCRIPTOR_10_SHIFT   10U
#define ADMA2_DESCRIPTOR_10_MASK    0x0000FFC0U
#define ADMA2_16LM_MAX_BUFSIZE      0x10000U
#define ADMA2_26LM_MAX_BUFSIZE      0x4000000U
//-------------------------------------------------------------------

/** ADMA1 Descriptor Fields */

/// Set address/length field
static inline uintptr_t ADMA1_DESCRIPTOR_ADDRESS_LENGHT(const uintptr_t val)
{
    return (val << 12);
}
/// No operation go to next descriptor on the list.
// ADMA1_DESCRIPTOR_TYPE_NOP   (0x0U << 4)
/// Set data page length and go to next descriptor on the list.
#define ADMA1_DESCRIPTOR_TYPE_SET   (0x1U << 4)
/// Transfer data from the pointed page and go to next descriptor on the list.
#define ADMA1_DESCRIPTOR_TYPE_TRAN  (0x2U << 4)
/// Go to the next descriptor list
// ADMA1_DESCRIPTOR_TYPE_LINK  (0x3U << 4)
/// the ADMA interrupt is generated
/// when the ADMA1 engine finishes processing the descriptor.
// ADMA1_DESCRIPTOR_INT        (0x1U << 2)
/// it signals termination of the transfer
/// and generates Transfer Complete Interrupt
/// when this transfer is completed
#define ADMA1_DESCRIPTOR_END        (0x1U << 1)
/// it indicates the valid descriptor on a list
#define ADMA1_DESCRIPTOR_VAL        (0x1U << 0)

/// Set address/length field
static inline uint32_t ADMA2_DESCRIPTOR_LENGTH(const CSDD_SDIO_Slot* pSlot,const uint32_t val)
{
    // data length for 16-bit Data Length Mode
    uint32_t data_length = ((uint32_t)(val & ADMA2_DESCRIPTOR_16_MASK) << ADMA2_DESCRIPTOR_16_SHIFT);
    uint32_t reg = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS15);
    if (pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP) {
        // data length for 26-bit Data Length Mode
        data_length = ((val << ADMA2_DESCRIPTOR_16_SHIFT) | ((val >> ADMA2_DESCRIPTOR_10_SHIFT) & ADMA2_DESCRIPTOR_10_MASK));
        // selects ADMA2 Length Mode as 26-bit.
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS15,(reg | SRS15_ADMA2LM_MASK));
    }

    return data_length;
}
/// No operation go to next descriptor on the list.
// ADMA2_DESCRIPTOR_TYPE_NOP   (0x0U << 4)
/// Transfer data from the pointed page and go to next descriptor on the list.
#define ADMA2_DESCRIPTOR_TYPE_TRAN  (0x2U << 4)
#define ADMA3_DESCRIPTOR_TYPE_TRAN  (0x7U << 3)
/// Go to the next descriptor list
// ADMA2_DESCRIPTOR_TYPE_LINK  (0x3U << 4)
/// the ADMA interrupt is generated
/// when the ADMA1 engine finishes processing the descriptor.
// ADMA2_DESCRIPTOR_INT        (0x1U << 2)
/// it signals termination of the transfer
/// and generates Transfer Complete Interrupt
/// when this transfer is completed
// ADMA2_DESCRIPTOR_END        (0x1U << 1)
/// it indicates the valid descriptor on a list
#define ADMA2_DESCRIPTOR_VAL        (0x1U << 0)
// Attribute indicate command descriptor for SD mode
#define ADMA3_SDCMDDESCRIPTOR_ACT   (0x1U << 3)

typedef struct {
    uint32_t numberOfDescriptors;
    uint32_t descSize;
} SD_DescriptorsParams;
//-----------------------------------------------------------------------------
static uint8_t DMA_FreeDecsriptors(CSDD_Request* pRequest)
{
    if (pRequest->admaDescriptorTable != NULL) {
        pRequest->admaDescriptorTable = NULL;
    }
    if (pRequest->IdDescriptorTable != NULL) {
        pRequest->IdDescriptorTable = NULL;
    }

    return SDIO_ERR_NO_ERROR;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#ifdef DEBUG
static void ADMADumpDescriptors(void *Descriptors, const uint32_t SizeOfDescriptors)
{
    uint32_t i;

    for (i = 0; i < (SizeOfDescriptors / 4U); i++) {
        vDbgMsg(DBG_GEN_MSG, DBG_FYI, "ADMADumpDescriptors 0x%08x: 0x%08x\n", ((uint32_t *)Descriptors + i), *((uint32_t *)Descriptors + i));
    }
}
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ADMACalcDescParams(const CSDD_SDIO_Slot* pSlot, const uint8_t ADMAType,
                                  const CSDD_SubBuffer *pSubBuffers, const uint32_t SubBuffersCount,
                                  SD_DescriptorsParams *descParams)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    uint32_t numberOfDescriptors = SubBuffersCount;
    uint32_t descSize = 0U;
    uint32_t i;

    if (ADMAType == (uint8_t)CSDD_ADMA1_MODE) {
        if ((pSubBuffers[0].size % 4096U) != 0U) {
            status = SDIO_ERR_INVALID_PARAMETER;
        } else {
            /// in ADMA1 mode all sub buffers must have the same size
            for (i = 0; i < SubBuffersCount; i++) {
                if ((pSubBuffers[i].size != pSubBuffers[0].size) || ((pSubBuffers[i].address % 4096U) != 0U)) {
                    status = SDIO_ERR_INVALID_PARAMETER;
                    break;
                }
            }

            numberOfDescriptors++;
            descSize = ADMA1_SIZE_OF_DESCRIPTOR;
        }
    }
    else if (ADMAType == (uint8_t)CSDD_ADMA2_MODE || (ADMAType == (uint8_t)CSDD_ADMA3_MODE)) {
        if (pSlot->SlotSettings.DMA64_En != 0U) {
            if (pSlot->SlotSettings.HostVer4_En != 0U) {
                descSize = ADMA2_SIZE_OF_DESCRIPTOR_64_HV4;
            }
            else {
                descSize = ADMA2_SIZE_OF_DESCRIPTOR_64;
            }
        }
        else {
            descSize =  ADMA2_SIZE_OF_DESCRIPTOR_32;
        }
    }
    else {
        status = SDIO_ERR_INVALID_PARAMETER;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        descParams->descSize = descSize;
        descParams->numberOfDescriptors = numberOfDescriptors;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void ADMA1FillDescriptors(const CSDD_SubBuffer* pSubBuffers, const uint32_t SubBuffersCount, const uint32_t NumberOfDescriptors, uint32_t* Descriptors){
    uint32_t i;

    // first descriptor sets the page size
    Descriptors[0] = CpuToLe32(
        ADMA1_DESCRIPTOR_TYPE_SET
        | (uint32_t)ADMA1_DESCRIPTOR_ADDRESS_LENGHT(pSubBuffers[0].size)
        | ADMA1_DESCRIPTOR_VAL);

    // next descriptors send prepared data
    for (i = 0; i < SubBuffersCount; i++) {
        Descriptors[i + 1U] =
            CpuToLe32(ADMA1_DESCRIPTOR_TYPE_TRAN
                      | (uint32_t)ADMA1_DESCRIPTOR_ADDRESS_LENGHT(pSubBuffers[i].address)
                      | ADMA1_DESCRIPTOR_VAL);
    }
    // last descriptor finishes transmission
    Descriptors[NumberOfDescriptors - 1U] |= CpuToLe32(ADMA1_DESCRIPTOR_END);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void ADMA2FillDescriptors(const CSDD_SDIO_Slot* pSlot, const CSDD_SubBuffer* pSubBuffers,
                                 const uint32_t NumberOfDescriptors, const uint32_t DescSize, uint32_t* Descriptors){
    uint32_t i;
    uint32_t j = 0;
    const CSDD_SDIO_SlotSettings* pSlotSettings = &pSlot->SlotSettings;
    // fill descriptors
    for (i = 0; i < NumberOfDescriptors; i++) {
        Descriptors[j] = CpuToLe32(
            ADMA2_DESCRIPTOR_TYPE_TRAN
            | ADMA2_DESCRIPTOR_LENGTH(pSlot, pSubBuffers[i].size)
            | ADMA2_DESCRIPTOR_VAL);
        j++;

        Descriptors[j] = CpuToLe32(((uint32_t)pSubBuffers[i].address & 0xFFFFFFFFU));
        j++;

        if (pSlotSettings->DMA64_En != 0U) {
            if (sizeof(uintptr_t) > 4U) {
                Descriptors[j] = CpuToLe32((uint32_t)((uint64_t)pSubBuffers[i].address >> 32));
            }
            else {
                Descriptors[j] = 0;
            }
            j++;
            if (pSlotSettings->HostVer4_En != 0U) {
                Descriptors[j] = 0;
                j++;
            }
        }
    }
    // last descriptor finishes transmission
    const uint32_t offset = (NumberOfDescriptors * (DescSize / 4U)) - (DescSize / 4U);
    Descriptors[offset]
        |= CpuToLe32(ADMA1_DESCRIPTOR_END);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static uint8_t ADMA3FillCommandDescriptors(const CSDD_CommandField* pCmd, uint32_t** ppDescriptor, uint16_t transfermode, uint32_t command)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t *Descriptors = *ppDescriptor;
    uint32_t i = 0;
    uint32_t endvalue = 0U;
    if (pCmd->requestFlags.dataPresent == 0U) {
        /*If command does not transfer a data, the last Command Descriptor has End flag set to 1, and ADMA3 leaps to the next
           Integrated Descriptor*/
        endvalue = ADMA1_DESCRIPTOR_END;
    }
    Descriptors[i] =  CpuToLe32(ADMA3_SDCMDDESCRIPTOR_ACT
                                | ADMA2_DESCRIPTOR_VAL);
    i++;
    Descriptors[i] = CpuToLe32((uint32_t)pCmd->blockCount);
    i++;
    Descriptors[i] =  CpuToLe32(ADMA3_SDCMDDESCRIPTOR_ACT
                                | ADMA2_DESCRIPTOR_VAL);
    i++;
    Descriptors[i] = CpuToLe32((uint32_t)(pCmd->blockLen & 0xFFFFU));
    i++;
    Descriptors[i] =   CpuToLe32(ADMA3_SDCMDDESCRIPTOR_ACT
                                 | ADMA2_DESCRIPTOR_VAL);
    i++;
    Descriptors[i] = CpuToLe32((uint32_t)(pCmd->argument));
    i++;
    Descriptors[i] = CpuToLe32(ADMA3_SDCMDDESCRIPTOR_ACT
                               | endvalue
                               | ADMA2_DESCRIPTOR_VAL);
    i++;
    Descriptors[i] = CpuToLe32((uint32_t)((uint32_t) command | (uint32_t)transfermode));
    *ppDescriptor = &Descriptors[i + 1];
    return (status);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static uint8_t ADMACreateCommandDescriptors(const CSDD_SDIO_Slot* pSlot, CSDD_CommandField* pCmd, uint8_t ADMAType, uint32_t** Descriptors)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint16_t transfermode;
    uint32_t commandReg;
    uint8_t BusyCheck = 0;
    if (pCmd->blockCount == 0 && pCmd->requestFlags.dataPresent != 0) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else if (pCmd->blockLen == 0 && pCmd->requestFlags.dataPresent != 0 ) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        // set AUTO CMD AUTO SELECT
        commandReg = SDIOHost_ExecCardCommand_ProcessRequestCheckRespType(pCmd->requestFlags.responseType, &BusyCheck);
        transfermode = (uint16_t)SRS3_DMA_ENABLE
                       | (uint16_t)SRS3_BLOCK_COUNT_ENABLE
                       | (uint16_t)SRS3_AUTO_CMD_AUTO_SELECT_ENABLE;
        if (pCmd->requestFlags.dataTransferDirection == CSDD_TRANSFER_READ) {
            transfermode |= (uint16_t)SRS3_TRANS_DIRECT_READ;
        }
        if (pCmd->blockCount > 1) {
            transfermode |= (uint16_t)SRS3_MULTI_BLOCK_SEL;
            transfermode |= (uint16_t)SRS3_AUTO_CMD_AUTO_SELECT_ENABLE;
        }
        if (pCmd->requestFlags.hwResponseCheck != 0U) {
            transfermode |= (uint16_t)SRS3_RESP_ERR_CHECK_EN;
            transfermode |= (uint16_t)SRS3_RESP_INTER_DISABLE;

            if (pCmd->requestFlags.responseType == CSDD_RESPONSE_R1) {
                transfermode |= (uint16_t)SRS3_RESPONSE_CHECK_TYPE_R1;
            }
            if (pCmd->requestFlags.responseType == CSDD_RESPONSE_R5) {
                transfermode |= (uint16_t)SRS3_RESPONSE_CHECK_TYPE_R5;
            }
        }
        if (pCmd->requestFlags.dataPresent != 0U) {
            commandReg |= (uint32_t)SRS3_DATA_PRESENT;
        }
        commandReg |= (uint32_t)((uint32_t)pCmd->command << 24U);
        status = ADMA3FillCommandDescriptors(pCmd,Descriptors,transfermode,commandReg);

    }
    return (status);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static uint8_t
ADMACreateIntegratedDescriptors(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest,
                                CSDD_CommandField* pCmd,uint8_t ADMAType,
                                uint32_t** CDDescriptors, uint32_t *ADMADescSize)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t offset;
    uint32_t *Descriptors;
    if (ADMAType != (uint8_t)CSDD_ADMA3_MODE) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        status = ADMACreateCommandDescriptors(pSlot, pCmd, ADMAType, CDDescriptors);
        if ((status == SDIO_ERR_NO_ERROR) && (pCmd->requestFlags.dataPresent != 0U)) {
            Descriptors = *CDDescriptors;
            status = DMA_PrepareTransferADMA(pSlot, pRequest, pCmd, ADMAType, *CDDescriptors, &offset, ADMADescSize);
        }

        if ((status == SDIO_ERR_NO_ERROR) && (pCmd->requestFlags.dataPresent != 0U)) {
            *CDDescriptors = &Descriptors[offset];
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ADMACreateDescriptors(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint8_t ADMAType,
                                     const CSDD_SubBuffer *pSubBuffers, uint32_t SubBuffersCount,
                                     uint32_t *Descriptors, uint32_t *next, uint32_t *ADMADescSize)
{
    SD_DescriptorsParams descriptorsParams;
    uint8_t status = ADMACalcDescParams(pSlot, ADMAType, pSubBuffers, SubBuffersCount, &descriptorsParams);
    if (status == SDIO_ERR_NO_ERROR) {
        const uint32_t NumberOfDescriptors = descriptorsParams.numberOfDescriptors;
        const uint32_t DescSize = descriptorsParams.descSize;
        const uint32_t RealDescSize = NumberOfDescriptors * DescSize;
        *ADMADescSize += RealDescSize;
        uint32_t maxBuf = (uint32_t)MAX_DESCR_BUFF_SIZE;
        if (pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP ) {
            maxBuf += (uint32_t)MAX_COMMAND_DESCR_BUFF_SIZE;
        }
        if (*ADMADescSize > maxBuf) {
            status = SDIO_ERR_TO_FEW_MEM;
        } else {

            if (ADMAType == (uint8_t)CSDD_ADMA1_MODE) {
                ADMA1FillDescriptors(pSubBuffers, SubBuffersCount, NumberOfDescriptors, Descriptors);
            }

            if (ADMAType == (uint8_t)CSDD_ADMA2_MODE) {
                ADMA2FillDescriptors(pSlot, pSubBuffers, NumberOfDescriptors, DescSize, Descriptors);
            }

            if (ADMAType == (uint8_t)CSDD_ADMA3_MODE) {
                ADMA2FillDescriptors(pSlot, pSubBuffers, NumberOfDescriptors, DescSize, Descriptors);
                uint32_t offset = (NumberOfDescriptors * (DescSize / 4U)) - (DescSize / 4U);
                *next = offset + 2U;
                pRequest->IdDescriptorTable = pSlot->IntegratedDescriptorDMAAddr;
            }

            pRequest->admaDescriptorTable = pSlot->DescriptorDMAAddr;

#ifdef DEBUG
            ADMADumpDescriptors(Descriptors, RealDescSize);
#endif
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
static uint8_t GetDMAAddr(CSDD_SDIO_Slot* pSlot, void **BufAddr, uint8_t DmaMode)
{
    uintptr_t address;
    if ((pSlot->SlotSettings.HostVer4_En == 0U) && (DmaMode == (uint8_t)CSDD_SDMA_MODE)) {
        address = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS00);
        *BufAddr = (void*)address;
    }
    else {
        address = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS22);
        *BufAddr = (void*)address;

        if ((pSlot->SlotSettings.DMA64_En != 0U) && (sizeof(uintptr_t) > 4U)) {
            uint64_t address64;
            uintptr_t HighAddr = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS23);
            address64 = address | ((uint64_t)HighAddr << 32);
            *BufAddr = (void*)(uintptr_t)address64;
        }
    }

    return 0;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t ValidateDMAAddrAlignment(const CSDD_SDIO_SlotSettings* pSlotSettings, const void *BufAddr)
{
    uint8_t status = SDIO_ERR_NO_ERROR;

    if (BufAddr == NULL) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        const uint32_t alignMask = ((pSlotSettings->DMA64_En != 0U) ? 0x7U : 0x3U);

        if (((uintptr_t)BufAddr & alignMask) != 0U) {
            // Address is not aligned to alignMask + 1
            status = SDIO_ERR_INVALID_PARAMETER;
        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t SetDMAAddr(CSDD_SDIO_Slot* pSlot, const void *BufAddr, uint8_t DmaMode)
{
    uint8_t status = ValidateDMAAddrAlignment(&pSlot->SlotSettings, BufAddr);

    if (status == SDIO_ERR_NO_ERROR) {
        if ((pSlot->SlotSettings.HostVer4_En == 0U) && (DmaMode == (uint8_t)CSDD_SDMA_MODE)) {
            if ((sizeof(uintptr_t) > 4U) && (((uint64_t)(uintptr_t)BufAddr >> 32) != 0U)) {
                // Address is bigger than 32 bit. DMA doesn't support 64 bit addresses
                status = SDIO_ERR_INVALID_PARAMETER;
            } else {
                // set system address register
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS00,
                              (uint32_t)(uintptr_t)BufAddr);
                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "DMA address 0x%08x\n", (uint32_t)(uintptr_t)BufAddr);
            }
        } else if (DmaMode == (uint8_t)CSDD_ADMA3_MODE) {
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS30, (uint32_t)(uintptr_t)BufAddr);
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "DMA_PrepareTransferADMA3", "DMA address low part = 0x%08x\n", (uint32_t)(uintptr_t)BufAddr);
            if (pSlot->SlotSettings.DMA64_En != 0U) {
                uint32_t HighAddr = 0;
                if (sizeof(uintptr_t) > 4U) {
                    HighAddr = (uint32_t)(((uint64_t)(uintptr_t)BufAddr) >> 32);
                }
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS31, HighAddr);
                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "SetDMAAddr", "DMA address high part = 0x%08x\n", HighAddr);
            } else if ((sizeof(uintptr_t) > 4U) && (((uint64_t)(uintptr_t)BufAddr >> 32) > 0U)) {
                // Address is bigger than 32 bit. DMA doesn't support 64 bit addresses
                status = SDIO_ERR_INVALID_PARAMETER;
            } else {
                // All 'if ... else if' constructs shall be terminated with an 'else' statement
                // (MISRA2012-RULE-15_7-3)
            }
        } else {
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS22, (uint32_t)(uintptr_t)BufAddr);
            vDbgMsg(DBG_GEN_MSG, DBG_FYI, "DMA address low part = 0x%08x\n", (uint32_t)(uintptr_t)BufAddr);

            if (pSlot->SlotSettings.DMA64_En != 0U) {
                uint32_t HighAddr = 0;

                if (sizeof(uintptr_t) > 4U) {
                    HighAddr = (uint32_t)(((uint64_t)(uintptr_t)BufAddr) >> 32);
                }
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS23, HighAddr);

                vDbgMsg(DBG_GEN_MSG, DBG_FYI, "DMA address high part = 0x%08x\n", HighAddr);
            } else if ((sizeof(uintptr_t) > 4U) && (((uint64_t)(uintptr_t)BufAddr >> 32) > 0U)) {
                // Address is bigger than 32 bit. DMA doesn't support 64 bit addresses
                status = SDIO_ERR_INVALID_PARAMETER;
            } else {
                // All 'if ... else if' constructs shall be terminated with an 'else' statement
                // (MISRA2012-RULE-15_7-3)
            }

        }
    }

    return (status);
}
//-----------------------------------------------------------------------------

#if SDIO_ADMA1_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA3_SUPPORTED
static CSDD_SubBuffer SubBuffers[SDIO_CFG_SDIO_SUB_BUFFERS_COUNT];
#endif

#if SDIO_ADMA2_SUPPORTED || SDIO_ADMA1_SUPPORTED || SDIO_SDMA_SUPPORTED
//-----------------------------------------------------------------------------

static uint8_t DMA_PrepareSubBuffers(CSDD_SDIO_Slot* pSlot, const CSDD_CommandField* pCmd, uint32_t* pNumBuffers)
{
    // 32-bit block count * block len( Max 2048)
    uint64_t DataSize = pCmd->blockCount * pCmd->blockLen;
    // max data length 2^16 or 2^26
    uint32_t SubBufSize = (uint32_t)ADMA2_16LM_MAX_BUFSIZE;
    uint32_t i = 0;
    uint8_t status = SDIO_ERR_NO_ERROR;
    if (pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP) {
        SubBufSize = (uint32_t)ADMA2_26LM_MAX_BUFSIZE;
    }
    if (DataSize >= SubBufSize) {
        uint32_t CurrentSubsize = SubBufSize;
        uint32_t Size = DataSize;
        uintptr_t BufAddress = (uintptr_t)pCmd->pDataBuffer;
        while (Size > 0U) {
            if (i >= SDIO_CFG_SDIO_SUB_BUFFERS_COUNT) {
                // There is not enough buffer count to create descriptors.
                // You need to increase SDIO_CFG_SDIO_SUB_BUFFERS_COUNT parameter
                status = SDIO_ERR_INVALID_PARAMETER;
                break;
            }

            if (Size < CurrentSubsize) {
                CurrentSubsize = Size;
            }
            SubBuffers[i].address = BufAddress;
            SubBuffers[i].size = CurrentSubsize;

            Size -= CurrentSubsize;
            BufAddress += CurrentSubsize;
            i++;
        }
    }
    else {
        SubBuffers[0].size = DataSize;
        SubBuffers[0].address = (uintptr_t)pCmd->pDataBuffer;
        i = 1;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        *pNumBuffers = i;
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t DMA_PrepareTransferSDMA(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint8_t DMAMode)
{
    uint8_t status;

    if (pRequest->pCmd->subBuffersCount != 0U) {
        status = SDIO_ERR_INVALID_PARAMETER;
    } else {
        // SDMA mode selected
        status = SetDMAAddr(pSlot, pRequest->pCmd->pDataBuffer, DMAMode);

        uint32_t Tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);
        Tmp = (Tmp & (~SRS10_DMA_SELECT_MASK));
        CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10, Tmp | SRS10_DMA_SELECT_SDMA);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#if SDIO_ADMA1_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA3_SUPPORTED
static uint8_t DMA_PrepareTransferADMA(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest,
                                       CSDD_CommandField* pCmd,
                                       uint8_t DMAMode,uint32_t *Descriptors,
                                       uint32_t *offset, uint32_t * ADMADescSize)
{
    uint8_t status;
    uint32_t Buffers = 0U;

    // if user prepared sub-buffers then create descriptors
    if (pCmd->subBuffersCount != 0U) {
        status = ADMACreateDescriptors(pSlot, pRequest, DMAMode, pCmd->pDataBuffer,
                                       pCmd->subBuffersCount, Descriptors, offset, ADMADescSize);
    }
    else {
        status = DMA_PrepareSubBuffers(pSlot, pCmd, &Buffers);
    }

    if (Buffers > 0) {
        status = ADMACreateDescriptors(pSlot, pRequest, DMAMode,
                                       &SubBuffers[0], Buffers, Descriptors, offset, ADMADescSize);
    }

    if (status == SDIO_ERR_NO_ERROR) {
        CPS_CacheFlush((void*)pRequest->admaDescriptorTable, MAX_DESCR_BUFF_SIZE, 0);

        // set address to DMA engine
        if (DMAMode != CSDD_ADMA3_MODE) {
            status = SetDMAAddr(pSlot, pRequest->admaDescriptorTable, DMAMode);
        }
        if (status == SDIO_ERR_NO_ERROR) {
            uint32_t Tmp = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS10);
            Tmp = (Tmp & (~SRS10_DMA_SELECT_MASK));
            if (DMAMode == (uint8_t)CSDD_ADMA1_MODE) {
                // ADMA1 mode selected
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10,
                              Tmp | SRS10_DMA_SELECT_ADMA1);
            } else {
                // ADMA2 mode (ADMA3 is not supported or disabled) selected
                uint32_t dmaselect = SRS10_DMA_SELECT_ADMA2;
#if SDIO_ADMA3_SUPPORTED
                dmaselect = SRS10_DMA_SELECT_MASK;
#endif
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS10,
                              Tmp | dmaselect);

            }
        }
    }

    return (status);
}
static uint8_t ADMA3CalcIDDescsize(const CSDD_SDIO_Slot* pSlot)
{
    uint32_t idDescSize;
    if (pSlot->SlotSettings.DMA64_En != 0U) {
        idDescSize = ADMA2_SIZE_OF_DESCRIPTOR_64_HV4;
    } else {
        idDescSize =  ADMA2_SIZE_OF_DESCRIPTOR_32;
    }
    return idDescSize;
}
uint8_t DMA_PrepareTransferADMA3(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint8_t DMAMode, uint8_t count) {
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t *IntegratedDescriptors = pSlot->IntegratedDescriptorBuffer;
    uint32_t *CDDescriptors = pSlot->DescriptorBuffer;
    uint32_t ADMADescSize = (ADMA2_SIZE_OF_DESCRIPTOR_32 * 4U * count);
    uint32_t *CDDescriptorsAddr;
    uint32_t endvalue = 0;
    uint32_t i = 0, j = 0;
    const uint32_t RealIdDescSize = count * ADMA3CalcIDDescsize(pSlot);
    if (RealIdDescSize > MAX_INTEGREATED_DESCR_BUFF_SIZE) {
        status = SDIO_ERR_TO_FEW_MEM;
    } else if (count > CSDD_MAX_NUMBER_COMMAND) {
        status = SDIO_ERR_OUT_OF_RANGE;
    } else {
        for (i = 0; i < count; i++) {
            CDDescriptorsAddr = CDDescriptors;
            // create integrated descriptor
            status =  ADMACreateIntegratedDescriptors(pSlot, pRequest, &pRequest->pCmd[i], DMAMode, &CDDescriptors, &ADMADescSize );
            if (status != SDIO_ERR_NO_ERROR) {
                break;
            }
            if (i == (count - 1U)) {
                endvalue = ADMA1_DESCRIPTOR_END;
            }

            IntegratedDescriptors[j] = CpuToLe32(
                ADMA3_DESCRIPTOR_TYPE_TRAN
                | ADMA2_DESCRIPTOR_VAL
                | endvalue);
            j++;
            IntegratedDescriptors[j] = CpuToLe32(((uint32_t)(uintptr_t)CDDescriptorsAddr & 0xFFFFFFFFU));
            j++;

            if (pSlot->SlotSettings.DMA64_En != 0U) {
                if (sizeof(uintptr_t) > 4U) {
                    IntegratedDescriptors[j] = CpuToLe32((uint32_t)((uint64_t)(uintptr_t)CDDescriptorsAddr >> 32));
                }
                else {
                    IntegratedDescriptors[j] = 0;
                }
                j++;
                IntegratedDescriptors[j] = 0;
                j++;
            }
            CPS_CacheFlush((void*)pRequest->IdDescriptorTable, MAX_DESCR_BUFF_SIZE, 0);
        }
        // set DMA descriptor address
        if (status == SDIO_ERR_NO_ERROR ) {
            status = SetDMAAddr(pSlot, pRequest->IdDescriptorTable, DMAMode);
        }

    }

    return (status);
}
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t DMA_PrepareTransfer(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint8_t DMAMode = DMA_SpecifyTransmissionMode(pSlot, pRequest);
    uint32_t offset = 0U;
    uint32_t descSize = 0U;

    switch (DMAMode) {
    case (uint8_t)CSDD_SDMA_MODE:
        status = DMA_PrepareTransferSDMA(pSlot, pRequest, DMAMode);
        break;
    case (uint8_t)CSDD_ADMA1_MODE:
    case (uint8_t)CSDD_ADMA2_MODE:
#if SDIO_ADMA1_SUPPORTED || SDIO_ADMA2_SUPPORTED
        status = DMA_PrepareTransferADMA(pSlot, pRequest, pRequest->pCmd, DMAMode, pSlot->DescriptorBuffer, &offset, &descSize);
        break;
#endif
#if SDIO_ADMA3_SUPPORTED
    case (uint8_t)CSDD_ADMA3_MODE:
        status = DMA_PrepareTransferADMA3(pSlot, pRequest,DMAMode, pRequest->cmdCount);
#endif
        break;
    default:
        status = SDIO_ERR_INVALID_PARAMETER;
        break;
    }

    if (status == SDIO_ERR_NO_ERROR) {
        uint32_t DataSize = pRequest->pCmd->blockCount * pRequest->pCmd->blockLen;
        CPS_CacheFlush((void*)pRequest->pCmd->pDataBuffer, DataSize, 0);
    }

    return (status);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
inline static bool DMA_NeedDescriptorsFreed(const uint32_t Status, const uint8_t DMAMode)
{
    return ((((Status & SRS12_TRANSFER_COMPLETE) != 0U)
             || ((Status & SRS12_ERROR_INTERRUPT) != 0U)
             || ((Status & SRS12_CARD_REMOVAL) != 0U)
             || ((Status & SRS12_CARD_INSERTION) != 0U))
            && ((DMAMode == (uint8_t)CSDD_ADMA1_MODE) || (DMAMode == (uint8_t)CSDD_ADMA2_MODE)));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t DMA_HandleInterrupt(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint32_t Status)
{
    uint8_t retStatus = SDIO_ERR_NO_ERROR;
    uint8_t DMAMode = DMA_SpecifyTransmissionMode(pSlot, pRequest);

    if (pRequest->pCmd->requestFlags.dataPresent != 0U) {
        if (((Status & SRS12_DMA_INTERRUPT) != 0U)
            && (DMAMode == (uint8_t)CSDD_SDMA_MODE)) {
            // DMA interrupt
            if (pSlot->pCurrentRequest->pBufferPos == NULL) {
                // DMA_HandleInterrupt. pBufferPos pointer points to NULL
                retStatus = SDIO_ERR_PARAM_ERR;
            } else {
                // clear DMA status
                CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12_DMA_INTERRUPT);

                (void)GetDMAAddr(pSlot, &pRequest->pBufferPos, DMAMode);
                // set system address register (transfer will be resumed)
                retStatus = SetDMAAddr(pSlot, pRequest->pBufferPos, DMAMode);
            }
        } else if (((Status & SRS12_DMA_INTERRUPT) != 0U)
                   && ((DMAMode == (uint8_t)CSDD_ADMA1_MODE) || (DMAMode == (uint8_t)CSDD_ADMA2_MODE) || (DMAMode == (uint8_t)CSDD_ADMA3_MODE))) {
            retStatus = SDIO_ERR_DMA_UNEXCEPTED_INTERRUPT;
        }
#if SDIO_ADMA1_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA3_SUPPORTED
        else if (DMA_NeedDescriptorsFreed(Status, DMAMode)) {
            (void)DMA_FreeDecsriptors(pRequest);
        }
#endif
        else {
            // All 'if ... else if' constructs shall be terminated with an 'else' statement
            // (MISRA2012-RULE-15_7-3)
        }
    }

    return (retStatus);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static uint8_t DMA_FinishTransferSDMA(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t retStatus = SDIO_ERR_NO_ERROR;
    uint32_t SRS12;

    uint8_t Tmp = 1U;
    while (Tmp != 0U) {
        // wait for transfer complete
        pRequest->status = WaitForValue(&pSlot->RegOffset->SRS.SRS12,
                                        (SRS12_TRANSFER_COMPLETE
                                         | SRS12_ERROR_INTERRUPT
                                         | SRS12_DMA_INTERRUPT),
                                        1, COMMANDS_TIMEOUT);
        if (pRequest->status != 0U) {
            pSlot->pCurrentRequest = NULL;
            // Timeout occurs during waiting for finish DMA transfer
            retStatus = pRequest->status;
            break;
        }

        SRS12 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12);
        // check transmission status
        switch ( SRS12 & (SRS12_TRANSFER_COMPLETE | SRS12_ERROR_INTERRUPT
                          | SRS12_DMA_INTERRUPT)) {
        case SRS12_TRANSFER_COMPLETE:
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12_TRANSFER_COMPLETE);
            retStatus = SDIO_ERR_NO_ERROR;
            Tmp = 0U;
            break;
        case SRS12_ERROR_INTERRUPT:
            pRequest->status = SDIOHost_CheckError(pSlot);
            retStatus = pRequest->status;
            Tmp = 0U;
            break;
        case SRS12_DMA_INTERRUPT:
            // clear DMA status
            pRequest->status = DMA_HandleInterrupt(pSlot, pRequest, SRS12);
            if (pRequest->status != 0U) {
                retStatus = pRequest->status;
                Tmp = 0U;
            }
            break;
        default:
            //
            break;
        }
    }

    return (retStatus);
}
//-----------------------------------------------------------------------------

static uint8_t DMA_FinishTransferADMA(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t retStatus = SDIO_ERR_NO_ERROR;

    // wait for transfer complete
    pRequest->status = WaitForValue(&pSlot->RegOffset->SRS.SRS12,
                                    (SRS12_TRANSFER_COMPLETE | SRS12_ERROR_INTERRUPT
                                     | SRS12_DMA_INTERRUPT), 1, COMMANDS_TIMEOUT);

    if (pRequest->status != 0U) {
        pSlot->pCurrentRequest = NULL;
        // DMA_FinishTransfer. Timeout occurs during waiting for finish DMA transfer
        retStatus = pRequest->status;
    } else {
        // check transmission status
        switch (CPS_REG_READ(&pSlot->RegOffset->SRS.SRS12) &
                (SRS12_TRANSFER_COMPLETE | SRS12_ERROR_INTERRUPT | SRS12_DMA_INTERRUPT)) {
        case SRS12_TRANSFER_COMPLETE:
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12_TRANSFER_COMPLETE);
#if SDIO_ADMA1_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA3_SUPPORTED
            (void)DMA_FreeDecsriptors(pRequest);
#endif
            break;
        case SRS12_ERROR_INTERRUPT:
            pRequest->status = SDIOHost_CheckError(pSlot);
#if SDIO_ADMA1_SUPPORTED || SDIO_ADMA2_SUPPORTED || SDIO_ADMA3_SUPPORTED
            (void)DMA_FreeDecsriptors(pRequest);
#endif
            retStatus = pRequest->status;
            break;
        case SRS12_DMA_INTERRUPT:
            // clear DMA status
            CPS_REG_WRITE(&pSlot->RegOffset->SRS.SRS12, SRS12_DMA_INTERRUPT);
            retStatus = SDIO_ERR_DMA_UNEXCEPTED_INTERRUPT;
            break;
        default:
            //
            break;
        }
    }

    return (retStatus);
}

//-----------------------------------------------------------------------------
uint8_t DMA_FinishTransfer(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t retStatus = SDIO_ERR_NO_ERROR;

    uint8_t DMAMode = DMA_SpecifyTransmissionMode(pSlot, pRequest);

    if (DMAMode == (uint8_t)CSDD_SDMA_MODE) {
        retStatus = DMA_FinishTransferSDMA(pSlot, pRequest);
    } else if ((DMAMode == (uint8_t)CSDD_ADMA1_MODE) || (DMAMode == (uint8_t)CSDD_ADMA2_MODE)) {
        retStatus = DMA_FinishTransferADMA(pSlot, pRequest);
    } else {
        // All 'if ... else if' constructs shall be terminated with an 'else' statement
        // (MISRA2012-RULE-15_7-3)
    }

    return (retStatus);
}
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
uint8_t DMA_SpecifyTransmissionMode(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest)
{
    uint8_t Mode = (uint8_t)CSDD_NONEDMA_MODE; // MANUAL
    uint32_t SRS16 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS16);
    uint32_t SRS17 = CPS_REG_READ(&pSlot->RegOffset->SRS.SRS17);

    if (pRequest == NULL) {
        Mode = SDIO_ERR_INVALID_PARAMETER;
    } else if (pRequest->pCmd->requestFlags.isInfinite != 0U) {
        Mode = (uint8_t)CSDD_NONEDMA_MODE;
    } else if (pSlot->DmaMode != (uint8_t)CSDD_AUTO_MODE) {
        Mode = pSlot->DmaMode;
    } else {
#if SDIO_SDMA_SUPPORTED
        if ((SRS16 & SRS16_DMA_SUPPORT) != 0U) {
            if ((pRequest->pCmd->blockLen > 32U) != 0U) {
                Mode = (uint8_t)CSDD_SDMA_MODE; // SDMA
            }
        }
#endif
#if SDIO_ADMA1_SUPPORTED
        if (SRS16 & SRS16_ADMA1_SUPPORT) {
            if (((pRequest->pCmd->blockLen % 4096U) == 0U)
                && (((uint32_t)pRequest->pCmd->pDataBuffer % 4096U) == 0U)) {
                Mode = (uint8_t)CSDD_ADMA1_MODE; // ADMA1
            }
        }
#endif
#if SDIO_ADMA2_SUPPORTED
        if ((SRS16 & SRS16_ADMA2_SUPPORT) != 0U) {
            if (pRequest->pCmd->blockCount > 1U) {
                Mode = (uint8_t)CSDD_ADMA2_MODE; // AMDA2
            }
        }
#endif
        if ((pSlot->pSdioHost->hostCtrlVer >= 6) && (SRS17 & SRS17_ADMA3_SUPPORT) != 0U) {
            if (pRequest->pCmd->blockCount > 1U) {
                Mode = (uint8_t)CSDD_ADMA3_MODE; // AMDA3
            }
        }

        const uint32_t alignMask = ((pSlot->SlotSettings.DMA64_En != 0U) ? 0x7U : 0x3U);

        if (((uintptr_t)pRequest->pCmd->pDataBuffer & alignMask) != 0U) {
            Mode = (uint8_t)CSDD_NONEDMA_MODE;
        }
    }
    pSlot->dmaModeSelected = (CSDD_DmaMode)Mode;
    return (Mode);
}
//-----------------------------------------------------------------------------
