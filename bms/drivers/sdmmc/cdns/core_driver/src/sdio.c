/******************************************************************************
 * Copyright (C) 2014-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio.c
 * SDIO Host driver
 *****************************************************************************/

#include "cdn_stdint.h"
#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "csdd_if.h"
#include "csdd_obj_if.h"
#include "csdd_structs_if.h"
#include "csdd_sanity.h"
#include "sdio_host.h"
#include "sdio_memory_card.h"
#include "sdio_phy.h"
#include "sdio_card_general.h"
#include "sdio_request.h"
#include "sdio_cq.h"
#include "sdio_debug.h"
#include "sdio_utils.h"

#ifndef SDIO_CFG_HOST_VER
    #error "SDIO_CFG_HOST_VER should be defined explicitly"
#endif

#ifndef SDIO_SLOT_COUNT
    #error "SDIO_SLOT_COUNT should be defined explicitly"
#endif

#ifndef SDIO_CFG_ENABLE_IO
    #error "SDIO_CFG_ENABLE_IO should be defined explicitly"
#endif

#ifndef SDIO_CFG_ENABLE_MMC
   #error "SDIO_CFG_ENABLE_MMC should be defined explicitly"
#endif

#if (SDIO_CFG_HOST_VER >= 4) && (SDIO_SLOT_COUNT > 1)
    #error SD Host 4 has only one slot
#endif

static uint32_t ErrorTranslate(uint8_t sdioError)
{
    uint32_t result;

    switch (sdioError) {
    case SDIO_ERR_INVALID_PARAMETER:
    case EINVAL:
        result = EINVAL;
        break;
    case 0:
        result = 0;
        break;
    case SDIO_ERR_BUS_SPEED_UNSUPP:
    case SDIO_ERR_UNSUPPORTED_COMMAND:
    case SDIO_ERR_FUNCTION_UNSUPP:
    case SDIO_ERR_UNSUPORRTED_OPERATION:
    case ENOTSUP:
        result = ENOTSUP;
        break;
    default:
        result = EIO;
        break;
    }

    return (result);
}

uint32_t CSDD_MemoryCardGetSecCount(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t *sectorCount)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemoryCardGetSecCountSF(pD, sectorCount);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if ((pSlot->NeedAttach != 0U) || (pSlot->CardInserted == 0U)) {
                ret = EIO;
            } else if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_NONE) {
                ret = EIO;
            } else {
                ret = MemoryCard_GetSecCount(pSlot->pDevice, sectorCount);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_Probe(uintptr_t registerBase, CSDD_SysReq* req)
{
    uint32_t ret = CSDD_ProbeSF(req);

    if (ret == CDN_EOK) {
        req->pDataSize = (uint32_t)sizeof(CSDD_SDIO_Host);
        req->descSize = MAX_DESCR_BUFF_SIZE * SDIO_SLOT_COUNT;
#if (SDIO_CFG_HOST_VER >= 4)
        req->descSize += CQ_DESC_LIST_SIZE_WITH_ALIGN_MARGIN;
#endif
#if (SDIO_CFG_HOST_VER >= 6)
        // for command descriptor
        req->descSize += MAX_COMMAND_DESCR_BUFF_SIZE * SDIO_SLOT_COUNT;
        req->idDescSize = MAX_INTEGREATED_DESCR_BUFF_SIZE * SDIO_SLOT_COUNT;
#endif
    }

    return (ret);
}

uint32_t CSDD_Init(CSDD_SDIO_Host* pD, CSDD_Config *config, CSDD_Callbacks* callbacks)
{
    uint8_t i;
    CSDD_SDIO_Host *pSdioHost = pD;
    uintptr_t logAddrADMA;
    uintptr_t phyAddrADMA;
    uintptr_t logAddrID;
    uintptr_t phyAddrID;

    uint32_t ret = CSDD_InitSF(pD, config, callbacks);

    if (ret == CDN_EOK) {
        pSdioHost->RegOffset = (void*)(uintptr_t)config->regBase;
        pSdioHost->dma64BitEn = config->dma64BitEn;

        pSdioHost->pCardRemoved = callbacks->cardRemovedCallback;
        pSdioHost->pCardInserted = callbacks->cardInsertedCallback;
        pSdioHost->axiErrorCallback = callbacks->axiErrorCallback;
#if SDIO_CFG_ENABLE_MMC
	pSdioHost->pSetTuneVal = SDIOHost_MmcTune;
#if SDIO_CFG_HOST_VER > 4
	pSdioHost->pSetTuneVal = callbacks->setTuneValCallback;
#endif
#endif
        logAddrADMA = (uintptr_t)config->descLogAddress;
        phyAddrADMA = (uintptr_t)config->descPhyAddress;
	logAddrID = (uintptr_t)config->idDescLogAddress;
        phyAddrID = (uintptr_t)config->idDescPhyAddress;

        if ((logAddrADMA == 0U) || (phyAddrADMA == 0U)) {
            ret = EINVAL;
#if SDIO_CFG_HOST_VER >= 6
        } else if ((logAddrID == 0U) || (phyAddrID == 0U)) {
            ret = EINVAL;
#endif
	} else {
            for (i = 0; i < SDIO_SLOT_COUNT; i++) {
                const uintptr_t offset = (uintptr_t)i * MAX_DESCR_BUFF_SIZE;
                pSdioHost->Slots[i].DescriptorBuffer = (uint32_t*)(logAddrADMA + offset);
                pSdioHost->Slots[i].DescriptorDMAAddr = (uint32_t*)(phyAddrADMA + offset);
#if SDIO_CFG_HOST_VER >= 6
		const uintptr_t admaoffset = (uintptr_t)i * (MAX_DESCR_BUFF_SIZE + MAX_COMMAND_DESCR_BUFF_SIZE);
                pSdioHost->Slots[i].DescriptorBuffer = (uint32_t*)(logAddrADMA + admaoffset);
                pSdioHost->Slots[i].DescriptorDMAAddr = (uint32_t*)(phyAddrADMA + admaoffset);
                const uintptr_t IDoffset = (uintptr_t)i * MAX_INTEGREATED_DESCR_BUFF_SIZE;
                pSdioHost->Slots[i].IntegratedDescriptorBuffer = (uint32_t*)(logAddrID + IDoffset);
                pSdioHost->Slots[i].IntegratedDescriptorDMAAddr = (uint32_t*)(phyAddrID + IDoffset);
#endif
            }

            ret = ErrorTranslate(SDIOHost_HostInitialize(pSdioHost));
        }
    }

    return (ret);
}

uint32_t CSDD_GetRca(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint16_t* rca)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_GetRcaSF(pD, rca);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if ((pSlot->NeedAttach != 0U) || (pSlot->CardInserted == 0U)) {
                ret = EIO;
            } else if (pSlot->pDevice->deviceType == (uint8_t)CSDD_CARD_TYPE_NONE) {
                ret = EIO;
            } else {
                *rca = pSlot->pDevice->RCA;
            }
        }
    }

    return (ret);
}

uint32_t CSDD_Start(CSDD_SDIO_Host* pD)
{
    uint8_t i;
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_StartSF(pD);

    if (ret == CDN_EOK) {
#if (SDIO_CFG_HOST_VER >= 4)
        SDIOHost_AxiErrorIntSignalCfg(pSdioHost, 1);
#endif

        for (i = 0; i < pSdioHost->NumberOfSlots; i++) {
            (void)SDIOHost_InterruptConfig(&pSdioHost->Slots[i], 1);
        }
    }

    return (ret);
}

uint32_t CSDD_Stop(CSDD_SDIO_Host* pD)
{
    uint8_t i;
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_StopSF(pD);

    if (ret == CDN_EOK) {
#if (SDIO_CFG_HOST_VER >= 4)
        SDIOHost_AxiErrorIntSignalCfg(pSdioHost, 0);
#endif

        for (i = 0; i < pSdioHost->NumberOfSlots; i++) {
            (void)SDIOHost_InterruptConfig(&pSdioHost->Slots[i], 0);
        }
    }

    return (ret);
}

uint32_t CSDD_ExecCardCommand(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_Request* request)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ExecCardCommandSF(pD, request);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            SDIOHost_ExecCardCommand(pSlot, request);

            ret = ErrorTranslate(request->status);
        }
    }

    return (ret);
}

uint32_t CSDD_DeviceDetach(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_DeviceDetachSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIOHost_DeviceDetach(pSlot));
        }
    }

    return (ret);
}

uint32_t CSDD_DeviceAttach(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_DeviceAttachSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if (pSlot->NeedAttach == 0U) {
                ret = 0U;
            } else {
                ret = ErrorTranslate(SDIOHost_DeviceAttach(pSlot));
            }
        }
    }

    return (ret);
}

uint32_t CSDD_Abort(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t isSynchronous)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_AbortSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIOHost_Abort(pSlot, isSynchronous));
        }
    }

    return (ret);
}

uint32_t CSDD_StandBy(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t wakeupCondition)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_StandBySF(pD);

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

        ret = ErrorTranslate(SDIOHost_Standby(pSlot, wakeupCondition));
    }

    return (ret);
}

uint32_t CSDD_Configure(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ConfigCmd cmd, void* data, uint8_t* sizeOfData)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ConfigureSF(pD, cmd, data, sizeOfData);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIOHost_Configure(pSlot, cmd, data, sizeOfData));
        }
    }

    return (ret);
}

void CSDD_Isr(CSDD_SDIO_Host* pD, bool* handled)
{
    uint32_t ret = CSDD_IsrSF(pD, handled);

    if (ret == CDN_EOK) {
        SDIOHost_InterruptHandler(pD, (uint8_t*)handled);
    }
}

uint32_t CSDD_ConfigureHighSpeed(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool setHighSpeed)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ConfigureHighSpeedSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if (pSlot->InterfaceType != (uint8_t)CSDD_INTERFACE_TYPE_SD) {
                ret = EOPNOTSUPP;
            } else {
                ret = ErrorTranslate(SDIOHost_ConfigureHighSpeed(pSlot, setHighSpeed));
            }
        }
    }

    return (ret);
}

uint32_t CSDD_CheckSlots(CSDD_SDIO_Host* pD)
{
    uint32_t ret = CSDD_CheckSlotsSF(pD);

    if (ret == CDN_EOK) {
        ret = SDIOHost_CheckSlots(pD);
    }

    return (ret);
}

void CSDD_CheckInterrupt(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t status)
{
    CSDD_SDIO_Host *pSdioHost = pD;
    CSDD_SDIO_Slot *pSlot;

    uint32_t ret = CSDD_CheckInterruptSF(pD);

    if ((ret == CDN_EOK) && (slotIndex < pSdioHost->NumberOfSlots)) {
        pSlot = &pSdioHost->Slots[slotIndex];

        SDIOHost_CheckInterrupt(pSlot, status);
    }
}

uint32_t CSDD_ConfigureAccessMode(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_SpeedMode accessMode)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ConfigureAccessModeSF(pD, accessMode);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if (pSlot->InterfaceType != (uint8_t)CSDD_INTERFACE_TYPE_SD) {
                ret = EOPNOTSUPP;
            } else {
                ret = ErrorTranslate(SDIOHost_ConfigureAccessMode(pSlot, accessMode));
            }
        }
    }

    return (ret);
}

uint32_t CSDD_Tuning(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_TuningSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots ) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if (pSlot->InterfaceType != (uint8_t)CSDD_INTERFACE_TYPE_SD) {
                ret = EOPNOTSUPP;
            } else {
                ret = ErrorTranslate(SDIOHost_Tuning(pSlot));
            }
        }
    }

    return (ret);
}

uint32_t CSDD_ClockGeneratorSelect(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t progClkMode)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ClockGeneratorSelectSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIOHost_ClockGeneratorSelect(pSlot, progClkMode));
        }
    }

    return (ret);
}

uint32_t CSDD_PresetValueSwitch(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool enable)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_PresetValueSwitchSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            SDIOHost_PresetValueSwitch(pSlot, enable);
        }
    }

    return (ret);
}

uint32_t CSDD_ConfigureDriverStrength(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverStrengthType driverStrength)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ConfigureDriverStrengthSF(pD, driverStrength);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIOHost_ConfigureDrvStrength(pSlot, driverStrength));
        }
    }

    return (ret);
}

void CSDD_MemoryCardLoadDriver(CSDD_SDIO_Host* pD)
{
    uint32_t ret = CSDD_MemoryCardLoadDriverSF(pD);

    if (ret == CDN_EOK) {
        MemoryCard_LoadDriver();
    }
}

uint32_t CSDD_MemoryCardDataTransfer(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address,
                                            void* buffer, uint32_t size, CSDD_TransferDirection direction)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemoryCardDataTransferSF(pD, buffer, direction);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        }
        //if (address + SDIO_MemoryCardGetSecCount
        else if (size != 0U) {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_DataXfer2(pSlot->pDevice, address, buffer, size, direction, 0));
        } else {
            // All 'if ... else if' constructs shall be terminated with an 'else' statement
            // (MISRA2012-RULE-15_7-3)
        }
    }

    return (ret);
}

uint32_t CSDD_MemoryCardDataTransfer2(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer,
                                             uint32_t size, CSDD_TransferDirection direction, uint32_t subBufferCount)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemoryCardDataTransfer2SF(pD, buffer, direction);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else if (size != 0U) {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_DataXfer2(pSlot->pDevice, address, buffer, size, direction, subBufferCount));
        } else {
            // All 'if ... else if' constructs shall be terminated with an 'else' statement
            // (MISRA2012-RULE-15_7-3)
        }
    }

    return (ret);
}

uint32_t CSDD_MemoryCardConfigure(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_MmcConfigCmd cmd, uint8_t* data, uint8_t size)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemoryCardConfigureSF(pD, cmd, data);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC) {
                ret = ENOTSUP;
            } else {
                ret = ErrorTranslate(MemoryCard_Configure(pSlot->pDevice, cmd, data, size));
            }
        }
    }

    return (ret);
}

uint32_t CSDD_MemoryCardDataErase(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t startBlockAddress, uint32_t blockCount)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemoryCardDataEraseSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_DataErase(pSlot->pDevice, startBlockAddress, blockCount));
        }
    }

    return (ret);
}

uint32_t CSDD_MemCardPartialDataXfer(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemCardPartialDataXferSF(pD, buffer, direction);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_PartialDataTransfer(pSlot->pDevice, address, buffer, size, direction));
        }
    }

    return (ret);
}

uint32_t CSDD_MemCardInfXferStart(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t address, void* buffer, uint32_t size, CSDD_TransferDirection direction)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemCardInfXferStartSF(pD, buffer, direction);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_InfXferStart(pSlot->pDevice, address, buffer, size, direction));
        }
    }

    return (ret);
}

uint32_t CSDD_MemCardInfXferContinue(CSDD_SDIO_Host* pD, uint8_t slotIndex, void* buffer, uint32_t size, CSDD_TransferDirection direction)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemCardInfXferContinueSF(pD, buffer, direction);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_InfXferContinue(pSlot->pDevice, buffer, size, direction));
        }
    }

    return (ret);
}

uint32_t CSDD_MemCardInfXferFinish(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_TransferDirection direction)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemCardInfXferFinishSF(pD, direction);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(MemoryCard_InfDataXferFinish(pSlot->pDevice, direction));
        }
    }

    return (ret);
}

uint32_t CSDD_MemCardDataXferNonBlock(CSDD_SDIO_Host* pD, uint8_t slotIndex,
                                               uint32_t address, void* buffer, uint32_t size,
                                               CSDD_TransferDirection direction, void** request)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MemCardDataXferNonBlockSF(pD, (const void*)buffer, direction, (const void**)request);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(MemoryCard_DataXferNonBlock(pSlot->pDevice, address, buffer, size, direction, request));
        }
    }

    return (ret);
}

uint32_t CSDD_MemCardFinishXferNonBlock(CSDD_SDIO_Host* pD, CSDD_Request* pRequest)
{
    uint32_t ret = CSDD_MemCardFinishXferNonBloSF(pD, pRequest);

    if (ret == CDN_EOK) {
        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);

        ret = ErrorTranslate(pRequest->status);
    }

    return (ret);
}

uint32_t CSDD_WaitForRequest(CSDD_SDIO_Host* pD, CSDD_Request* pRequest)
{
    uint32_t ret = CSDD_WaitForRequestSF(pD, pRequest);

    if (ret == CDN_EOK) {
        SDIOHost_CheckBusy(pRequest->pSdioHost, pRequest);

        ret = ErrorTranslate(pRequest->status);
    }

    return (ret);
}

uint32_t CSDD_PhySettingsSd3(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_PhyDelaySettings* phyDelaySet)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_PhySettingsSd3SF(pD, phyDelaySet);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIO_Phy_PhySettings_SDv3(pSlot, phyDelaySet));
        }
    }

    return (ret);
}

uint32_t CSDD_PhySettingsSd4(CSDD_SDIO_Host* pD, CSDD_PhyDelaySettings* phyDelaySet)
{
    uint32_t ret = CSDD_PhySettingsSd4SF(pD, phyDelaySet);

    if (ret == CDN_EOK) {
        ret = ErrorTranslate(SDIO_Phy_PhySettings_SDv4(pD, phyDelaySet));
    }

    return (ret);
}

uint32_t CSDD_ReadPhySet(CSDD_SDIO_Host* pD, uint8_t slotIndex,
                                CSDD_PhyDelay phyDelayType, uint8_t *delayVal)
{
    uint32_t ret = CSDD_ReadPhySetSF(pD, phyDelayType, delayVal);

    if (ret == CDN_EOK) {
        ret = ErrorTranslate(SDIO_ReadPhySet(pD, slotIndex, phyDelayType, delayVal));
    }

    return (ret);
}

uint32_t CSDD_WritePhySet(CSDD_SDIO_Host* pD, uint8_t slotIndex,
                                 CSDD_PhyDelay phyDelayType, uint8_t delayVal)
{
    uint32_t ret = CSDD_WritePhySetSF(pD, phyDelayType);

    if (ret == CDN_EOK) {
        ret = ErrorTranslate(SDIO_WritePhySet(pD, slotIndex, phyDelayType, delayVal));
    }

    return (ret);
}

uint32_t CSDD_ReadCardStatus(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* cardStatus)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ReadCardStatusSF(pD, cardStatus);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(SDIOHost_ReadCardStatus(pSlot, cardStatus));
        }
    }

    return (ret);
}

uint32_t CSDD_SelectCard(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint16_t rca)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_SelectCardSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(SDIOHost_SelectCard(pSlot, rca));
        }
    }

    return (ret);
}

uint32_t CSDD_ResetCard(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ResetCardSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            const uint8_t status = SDIOHost_ResetCard(pSlot);
            if (status != 0U) {
                ret = ErrorTranslate(status);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_ExecCmd55Command(CSDD_SDIO_Host* pD, uint8_t slotIndex)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ExecCmd55CommandSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(SDIOHost_ExecCMD55Command(pSlot));
        }
    }

    return (ret);
}

uint32_t CSDD_AccessCccr(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_TransferDirection transferDirection, void* data, uint8_t size, CSDD_CccrRegAddr registerAddress)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_AccessCccrSF(pD, transferDirection, data, registerAddress);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            ret = ENOTSUP;

#if SDIO_CFG_ENABLE_IO
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_SDIO)) {
                ret = ENOTSUP;
            } else {
                ret = ErrorTranslate(SDIOHost_AccessCCCR(pSlot, transferDirection, data, size, registerAddress));
            }

#endif
        }
    }

    return (ret);
}

uint32_t CSDD_ReadCsd(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* buffer)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ReadCsdSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(SDIOHost_ReadCSD(pSlot, buffer));
        }
    }

    return (ret);
}

uint32_t CSDD_ReadExCsd(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t* buffer)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ReadExCsdSF(pD, buffer);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                const uint8_t status = SDIOHost_ReadExCSD(pSlot, buffer);
                if (status != 0U) {
                    ret = ErrorTranslate(status);
                }
            }
        }
    }

    return (ret);
}

uint32_t CSDD_GetTupleFromCis(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t tupleAddress, CSDD_TupleCode tupleCode, void* buffer, uint8_t bufferSize)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_GetTupleFromCisSF(pD, tupleCode, buffer);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            ret = ENOTSUP;

#if SDIO_CFG_ENABLE_IO
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_SDIO)) {
                ret = ENOTSUP;
            } else {
                ret = ErrorTranslate(SDIOHost_GetTupleFromCIS(pSlot, tupleAddress, tupleCode, buffer, bufferSize));
            }
#endif
        }
    }

    return (ret);
}

uint32_t CSDD_ReadSdStatus(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t buffer[64])
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ReadSdStatusSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(SDIOHost_ReadSDStatus(pSlot, buffer));
        }
    }

    return (ret);
}

uint32_t CSDD_SetDriverStrength(CSDD_SDIO_Host* pD, uint8_t slotIndex,
                                       CSDD_DriverStrengthType driverStrength)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_SetDriverStrengthSF(pD, driverStrength);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = ErrorTranslate(SDIOHost_SDCardSetDrvStrength(pSlot, driverStrength));
        }
    }

    return (ret);
}

uint32_t CSDD_ExecSetCurrentLimit(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DriverCurrentLimit currentLimit)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_ExecSetCurrentLimitSF(pD, currentLimit);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = ErrorTranslate(SDIOHost_SDCardSetCurrentLimit(pSlot, currentLimit));
        }
    }

    return (ret);
}

uint32_t CSDD_MmcSwitch(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t argIndex, uint8_t argValue)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcSwitchSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                ret = SDIOHost_MmcSwitch(pSlot, argIndex, argValue);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_MmcSetExtCsd(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint8_t byteNr, uint8_t newValue, uint8_t mask)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcSetExtCsdSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                ret = SDIOHost_MmcSetExtCsd(pSlot, byteNr, newValue, mask);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_MmcSetBootPartition(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ParitionBoot partition)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcSetBootPartitionSF(pD, partition);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                ret = SDIOHost_MmcSetBootPartition(pSlot, partition);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_MmcSetBootAck(CSDD_SDIO_Host* pD, uint8_t slotIndex, bool enableBootAck)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcSetBootAckSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                ret = SDIOHost_MmcSetBootAck(pSlot, enableBootAck);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_MmcSetPartAccess(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_ParitionAccess partition)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcSetPartAccessSF(pD, partition);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                ret = SDIOHost_MmcSetPartAccess(pSlot, partition);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_MmcExecuteBoot(CSDD_SDIO_Host* pD, uint8_t slotIndex, void* buffer, uint32_t size)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcExecuteBootSF(pD, buffer);
    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            /* it is special function it can be called when device is not attached
             * so we cannot verify whether it is eMMC */

            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = SDIOHost_MmcExecuteBoot(pSlot, buffer, size);
        }
    }

    return (ret);
}

uint32_t CSDD_MmcGetParitionBootSize(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t* bootSize)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_MmcGetParitionBootSizeSF(pD, bootSize);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            if ((pSlot->pDevice == NULL) || (pSlot->pDevice->deviceType != (uint8_t)CSDD_CARD_TYPE_MMC)) {
                ret = ENOTSUP;
            } else {
                ret = SDIOHost_MmcGetPartitionBootSize(pSlot, bootSize);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_GetInterfaceType(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_InterfaceType* interfaceType)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_GetInterfaceTypeSF(pD, interfaceType);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            *interfaceType = (CSDD_InterfaceType)pSlot->InterfaceType;
        }
    }

    return (ret);
}

uint32_t CSDD_GetDeviceState(CSDD_SDIO_Host* pD, uint8_t slotIndex, CSDD_DeviceState* deviceState)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_GetDeviceStateSF(pD, deviceState);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            deviceState->deviceType = (CSDD_CardType)pSlot->pDevice->deviceType;
            deviceState->inserted = pSlot->CardInserted;
            deviceState->attached = (((pSlot->NeedAttach == 0U) && (pSlot->CardInserted != 0U)) ? 1U : 0U);
            deviceState->uhsSupported = pSlot->pDevice->UhsiSupported;
        }
    }

    return (ret);
}

uint32_t CSDD_SetDriverData(CSDD_SDIO_Host* pD, void *drvData)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_SetDriverDataSF(pD, drvData);

    if (ret == CDN_EOK) {
        pSdioHost->drvData = drvData;
    }

    return (ret);
}

uint32_t CSDD_GetDriverData(CSDD_SDIO_Host* pD, const void **drvData)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_GetDriverDataSF(pD, drvData);

    if (ret == CDN_EOK) {
        *drvData = pSdioHost->drvData;
    }

    return (ret);
}

uint32_t CSDD_SimpleInit(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t clk)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_SimpleInitSF(pD);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];
            ret = SDIOHost_ChangeSDCLK(pSlot, &clk);

            if((pSlot->pSdioHost->hostCtrlVer >= SDIO_HOST_VER_WTH_CCP) && (ret == CDN_EOK)) {
                ret = SDIO_CPhy_DLLReset(pSlot->pSdioHost, false);
            }

            if (ret == CDN_EOK) {
                // set VDD1
                ret = SDIOHost_SetPower(pSlot, SRS10_SET_3_3V_BUS_VOLTAGE);
            }

            if (ret == CDN_EOK) {
                // Set SD clock enable
                SDIOHost_SupplySDCLK(pSlot, 1);

                pSlot->InterfaceType = (uint8_t)CSDD_INTERFACE_TYPE_SD;

                CPS_DelayNs(800000U);
            }
        }
    }

    return (ret);
}

uint32_t CSDD_ResetHost(CSDD_SDIO_Host* pD)
{
    uint32_t ret = CSDD_ResetHostSF(pD);

    if (ret == CDN_EOK) {
        ret = ErrorTranslate(ResetHost(pD));
    }

    return (ret);
}

uint32_t CSDD_CQEnable(CSDD_SDIO_Host* pD, CSDD_CQInitConfig *cqConfig)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQEnableSF(pD, cqConfig);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_Enable(pSlot, cqConfig);
    }

    return (ret);
}

uint32_t CSDD_CQDisable(CSDD_SDIO_Host* pD)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQDisableSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_Disable(pSlot);
    }

    return (ret);
}

uint32_t CSDD_CQGetInitConfig(CSDD_SDIO_Host* pD, CSDD_CQInitConfig *cqConfig)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQGetInitConfigSF(pD, cqConfig);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_GetInitConfig(pSlot, cqConfig);
    }

    return (ret);
}

uint32_t CSDD_CQGetUnusedTaskId(CSDD_SDIO_Host* pD, uint8_t *taskId)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQGetUnusedTaskIdSF(pD, taskId);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_GetUnusedTaskId(pSlot, taskId);
    }

    return (ret);
}
uint32_t CSDD_CQStartExecuteTask(CSDD_SDIO_Host* pD, uint8_t taskId)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQStartExecuteTaskSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_StartExecuteTask(pSlot, taskId);
    }

    return (ret);
}
uint32_t CSDD_CQAttachRequest(CSDD_SDIO_Host* pD, CSDD_CQRequest *request)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQAttachRequestSF(pD, request);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_AttachRequest(pSlot, request);
    }

    return (ret);
}
uint32_t CSDD_CQExecuteDcmdRequest(CSDD_SDIO_Host* pD, CSDD_CQDcmdRequest *request)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQExecuteDcmdRequestSF(pD, request);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_ExecuteDcmdRequest(pSlot, request);
    }

    return (ret);
}

uint32_t CSDD_CQGetDirectCmdConfig(CSDD_SDIO_Host* pD, uint8_t *enable)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQGetDirectCmdConfigSF(pD, enable);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_GetDirectCmdConfig(pSlot, enable);
    }

    return (ret);
}
uint32_t CSDD_CQSetDirectCmdConfig(CSDD_SDIO_Host* pD, uint8_t enable)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQSetDirectCmdConfigSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_SetDirectCmdConfig(pSlot, enable);
    }

    return (ret);
}

uint32_t CSDD_CQSetIntCoalescingConfig(CSDD_SDIO_Host* pD, CSDD_CQIntCoalescingCfg *config)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQSetIntCoalescingConfiSF(pD, config);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_SetIntCoalescingCfg(pSlot, config);
    }

    return (ret);
}

uint32_t CSDD_CQGetIntCoalescingConfig(CSDD_SDIO_Host* pD, CSDD_CQIntCoalescingCfg *config)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQGetIntCoalescingConfiSF(pD, config);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_GetIntCoalescingCfg(pSlot, config);
    }

    return (ret);
}

uint32_t CSDD_CQGetIntCoalescingTimeoutBase(CSDD_SDIO_Host* pD, uint32_t *clockFreqKHz)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQGetIntCoalescingTimeoSF(pD, clockFreqKHz);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_GetIntCoalescingTimeoutBase(pSlot, clockFreqKHz);
    }

    return (ret);
}

uint32_t CSDD_CQStartExecuteTasks(CSDD_SDIO_Host* pD, uint32_t taskIds)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQStartExecuteTasksSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_StartExecuteTasks(pSlot, taskIds);
    }

    return (ret);
}

uint32_t CSDD_CQHalt(CSDD_SDIO_Host* pD, uint8_t set)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQHaltSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_Halt(pSlot, set);
    }

    return (ret);
}

uint32_t CSDD_CQTaskDiscard(CSDD_SDIO_Host* pD, uint8_t taskId)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQTaskDiscardSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_TaskDiscard(pSlot, taskId);
    }

    return (ret);
}

uint32_t CSDD_CQAllTasksDiscard(CSDD_SDIO_Host* pD)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQAllTasksDiscardSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_AllTasksDiscard(pSlot);
    }

    return (ret);
}

uint32_t CSDD_CQResetIntCoalCounters(CSDD_SDIO_Host* pD)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQResetIntCoalCountersSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_ResetIntCoalCounters(pSlot);
    }

    return (ret);
}

uint32_t CSDD_CQSetResponseErrorMask(CSDD_SDIO_Host* pD, uint32_t errorMask)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQSetResponseErrorMaskSF(pD);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_SetResponseErrMask(pSlot, errorMask);
    }

    return (ret);
}

uint32_t CSDD_CQGetResponseErrorMask(CSDD_SDIO_Host* pD, uint32_t *errorMask)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_CQGetResponseErrorMaskSF(pD, errorMask);

    if (ret == CDN_EOK) {
        if (!pSdioHost->cqSupported) {
            ret = ENOTSUP;
        }
    }

    if (ret == CDN_EOK) {
        CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[0];

        ret = SDIOHost_CQ_GetResponseErrMask(pSlot, errorMask);
    }

    return (ret);
}

uint32_t CSDD_GetBaseClk(CSDD_SDIO_Host* pD, uint8_t slotIndex, uint32_t *frequencyKHz)
{
    CSDD_SDIO_Host *pSdioHost = pD;

    uint32_t ret = CSDD_GetBaseClkSF(pD, frequencyKHz);

    if (ret == CDN_EOK) {
        if (slotIndex >= pSdioHost->NumberOfSlots) {
            ret = EINVAL;
        } else {
            CSDD_SDIO_Slot* pSlot = &pSdioHost->Slots[slotIndex];

            ret = SDIOHost_GetBaseClk(pSlot, frequencyKHz);
        }
    }

    return (ret);
}

static inline uint32_t CheckSdhcVersion(CSDD_SDIO_Host* pSdioHost, uint8_t version)
{
    uint32_t status = CDN_EOK;

    if (pSdioHost->hostCtrlVer < version) {
        vDbgMsg(DBG_GEN_MSG, DBG_CRIT, "Host version %d is smaller than expected %d\n",
                pSdioHost->hostCtrlVer, version);
        status = CDN_ENOTSUP;
    }
    return status;
}


uint32_t CSDD_SetCPhyConfigIoDelay(CSDD_SDIO_Host* pD, CSDD_CPhyConfigIoDelay* ioDelay)
{
    uint32_t ret = CSDD_SetCPhyConfigIoDelaySF(pD, ioDelay);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_SetCPhyConfigIoDelay(pD, ioDelay);
    }

    return ret;
}

uint32_t CSDD_GetCPhyConfigIoDelay(CSDD_SDIO_Host* pD, CSDD_CPhyConfigIoDelay* ioDelay)
{
    uint32_t ret = CSDD_GetCPhyConfigIoDelaySF(pD, ioDelay);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_GetCPhyConfigIoDelay(pD, ioDelay);
    }

    return ret;
}

uint32_t CSDD_SetCPhyConfigLvsi(CSDD_SDIO_Host* pD, CSDD_CPhyConfigLvsi* lvsi)
{
    uint32_t ret = CSDD_SetCPhyConfigLvsiSF(pD, lvsi);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_SetConfigLvsi(pD, lvsi);
    }

    return ret;
}

uint32_t CSDD_GetCPhyConfigLvsi(CSDD_SDIO_Host* pD, CSDD_CPhyConfigLvsi* lvsi)
{
    uint32_t ret = CSDD_GetCPhyConfigLvsiSF(pD, lvsi);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_GetConfigLvsi(pD, lvsi);
    }

    return ret;
}

uint32_t CSDD_SetCPhyConfigDfiRd(CSDD_SDIO_Host* pD, CSDD_CPhyConfigDfiRd* dfiRd)
{
    uint32_t ret = CSDD_SetCPhyConfigDfiRdSF(pD, dfiRd);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_SetConfigDfiRd(pD, dfiRd);
    }

    return ret;
}

uint32_t CSDD_GetCPhyConfigDfiRd(CSDD_SDIO_Host* pD, CSDD_CPhyConfigDfiRd* dfiRd)
{
    uint32_t ret = CSDD_GetCPhyConfigDfiRdSF(pD, dfiRd);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_GetConfigDfiRd(pD, dfiRd);
    }

    return ret;
}

uint32_t CSDD_SetCPhyConfigOutputDelay(CSDD_SDIO_Host* pD,
                                       CSDD_CPhyConfigOutputDelay* outputDelay)
{
    uint32_t ret = CSDD_SetCPhyConfigOutputDelaSF(pD, outputDelay);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_SetConfigOutputDelay(pD, outputDelay);
    }

    return ret;
}

uint32_t CSDD_GetCPhyConfigOutputDelay(CSDD_SDIO_Host* pD,
                                       CSDD_CPhyConfigOutputDelay* outputDelay)
{
    uint32_t ret = CSDD_GetCPhyConfigOutputDelaSF(pD, outputDelay);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_GetConfigOutputDelay(pD, outputDelay);
    }

    return ret;
}

uint32_t CSDD_CPhyDllReset(CSDD_SDIO_Host* pD, bool doReset)
{
    uint32_t ret = CSDD_CPhyDllResetSF(pD);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        ret = SDIO_CPhy_DLLReset(pD, doReset);
    }

    return ret;
}

uint32_t CSDD_SetCPhyExtMode(CSDD_SDIO_Host* pD, bool extendedWrMode,
                             bool extendedRdMode)
{
    uint32_t ret = CSDD_SetCPhyExtModeSF(pD);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_SetExtMode(pD, extendedWrMode, extendedRdMode);
    }

    return ret;
}

uint32_t CSDD_GetCPhyExtMode(CSDD_SDIO_Host* pD, bool* extendedWrMode,
                             bool* extendedRdMode)
{
    uint32_t ret = CSDD_GetCPhyExtModeSF(pD, extendedWrMode, extendedRdMode);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_GetExtMode(pD, extendedWrMode, extendedRdMode);
    }

    return ret;
}

uint32_t CSDD_SetCPhySdclkAdj(CSDD_SDIO_Host* pD, uint8_t sdclkAdj)
{
    uint32_t ret = CSDD_SetCPhySdclkAdjSF(pD);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_SetSdclkAdj(pD, sdclkAdj);
    }

    return ret;
}

uint32_t CSDD_GetCPhySdclkAdj(CSDD_SDIO_Host* pD, uint8_t* sdclkAdj)
{
    uint32_t ret = CSDD_GetCPhySdclkAdjSF(pD, sdclkAdj);

    if (ret == CDN_EOK) {
        ret = CheckSdhcVersion(pD, SDIO_HOST_VER_WTH_CCP);
    }

    if (ret == CDN_EOK) {
        SDIO_CPhy_GetSdclkAdj(pD, sdclkAdj);
    }

    return ret;
}


