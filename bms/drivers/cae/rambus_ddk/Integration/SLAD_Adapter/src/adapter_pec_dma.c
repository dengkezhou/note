/* adapter_pec_dma.c
 *
 * Packet Engine Control (PEC) API Implementation
 * using DMA mode.
 */

/*****************************************************************************
* Copyright (c) 2011-2020 by Rambus, Inc. and/or its subsidiaries.
* All rights reserved. Unauthorized use (including, without limitation,
* distribution and copying) is strictly prohibited. All use requires,
* and is subject to, explicit written authorization and nondisclosure
* Rambus, Inc. and/or its subsidiaries
*
* For more information or support, please go to our online support system at
* https://sipsupport.rambus.com.
* In case you do not have an account for this system, please send an e-mail
* to sipsupport@rambus.com.
******************************************************************************/

#include <common.h>
#include <cae.h>

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_pec.h"            // PEC_* (the API we implement here)


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default Adapter PEC configuration
#include "c_adapter_pec.h"

// DMABuf API
#include "api_dmabuf.h"         // DMABuf_*

// Adapter DMABuf internal API
#include "adapter_dmabuf.h"

// Adapter PEC device API
#include "adapter_pecdev_dma.h" // Adapter_PECDev_*

// Adapter Locking internal API
#include "adapter_lock.h"       // Adapter_Lock_*

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
#include "api_pec_sg.h"         // PEC_SG_* (the API we implement here)
#endif

// Runtime Power Management Device Macros API
#include "rpm_device_macros.h"  // RPM_*

// Logging API
#include "log.h"

// Driver Framework DMAResource API
#include "dmares_types.h"       // DMAResource_Handle_t
#include "dmares_mgmt.h"        // DMAResource management functions
#include "dmares_rw.h"          // DMAResource buffer access.
#include "dmares_addr.h"        // DMAResource addr translation functions.
#include "dmares_buf.h"         // DMAResource buffer allocations

// Driver Framework C Run-Time Library API
#include "clib.h"               // memcpy, memset

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // bool, uint32_t


#ifndef ADAPTER_PE_MODE_DHM
/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * Local variables
 */

extern PEC_Status_t
Adapter_PECDev_Init(cae_device *dev,
        const unsigned int InterfaceId,
        const PEC_InitBlock_t * const InitBlock_p);
extern PEC_Status_t
Adapter_PECDev_UnInit(cae_device *dev,
        const unsigned int InterfaceId);
extern void
Adapter_PECDev_Enable_ResultIRQ(cae_device *dev,
        const unsigned int InterfaceId);
extern void
Adapter_PECDev_Enable_ResultIRQ(cae_device *dev,
        const unsigned int InterfaceId);
extern void
Adapter_PECDev_Enable_CommandIRQ(cae_device *dev,
        const unsigned int InterfaceId);
extern void
Adapter_PECDev_Disable_ResultIRQ(cae_device *dev,
        const unsigned int InterfaceId);
extern void
Adapter_PECDev_Disable_CommandIRQ(cae_device *dev,
        const unsigned int InterfaceId);

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
/*----------------------------------------------------------------------------
 * AdapterPEC_InterruptHandlerResultNotify
 *
 * This function is the interrupt handler for the PEC interrupt
 * sources that indicate the arrival of a a result descriptor..There
 * may be several interrupt sources.
 *
 * This function is used to invoke the PEC result notification callback.
 */

#if CAE_DDK_INFO_DUMP
static void rdr_hw_descr_info_dump(cae_device *dev)
{
	unsigned long cae_base = dev->LKM_Admin.PhysBaseAddr;
	unsigned long rdr0_ring_base = readl(cae_base + 0x800);
	int i = 0;

	printf("----rdr0 ring dump: 0x%lx----\n", rdr0_ring_base);
	for (i = 0; i < 2; i++)
		printf("0x%08x\n", readl(rdr0_ring_base + i * 4));
}
#endif

static void
AdapterPEC_InterruptHandlerResultNotify(void *c_dev,
        const int nIRQ,
        const unsigned int flags)
{
    unsigned int InterfaceId = Adapter_PECDev_IRQToInferfaceId(nIRQ);
    cae_device *dev = (cae_device *)c_dev;

    IDENTIFIER_NOT_USED(flags);

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
    {
        LOG_CRIT("AdapterPEC_InterruptHandlerResultNotify"
                 "InterfaceId out of range\n");
        return;
    }

    Adapter_PECDev_Disable_ResultIRQ(dev, InterfaceId);

    LOG_INFO("AdapterPEC_InterruptHandlerResultNotify: Enter\n");

    if (dev->PEC_Notify[InterfaceId].ResultNotifyCB_p != NULL)
    {
        PEC_NotifyFunction_t CBFunc_p;
	void *args = dev->PEC_Notify[InterfaceId].result_notify_args;

        // Keep the callback on stack to allow registration
        // of another result notify request from callback
        CBFunc_p = dev->PEC_Notify[InterfaceId].ResultNotifyCB_p;

       dev->PEC_Notify[InterfaceId].ResultNotifyCB_p = NULL;
       dev->PEC_Notify[InterfaceId].ResultsCount = 0;
       dev->PEC_Notify[InterfaceId].result_notify_args = NULL;

        LOG_INFO(
            "AdapterPEC_InterruptHandlerResultNotify: "
            "Invoking PEC result notify callback for interface %d\n",
            InterfaceId);

#if CAE_DDK_INFO_DUMP
	rdr_hw_descr_info_dump(dev);
#endif

        CBFunc_p(args);
    }
}


/*----------------------------------------------------------------------------
 * AdapterPEC_InterruptHandlerCommandNotify
 *
 * This function is the interrupt handler for the PEC interrupt sources.that
 * indicate that there is again freee space for new command descriptors.
 *
 * This function is used to invoke the PEC command notification callback.
 */
static void
AdapterPEC_InterruptHandlerCommandNotify(void *c_dev,
        const int nIRQ,
        const unsigned int flags)
{
    unsigned int InterfaceId = Adapter_PECDev_IRQToInferfaceId(nIRQ);
    cae_device *dev = (cae_device *)c_dev;

    IDENTIFIER_NOT_USED(flags);

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
    {
        LOG_CRIT("AdapterPEC_InterruptHandlerCommandNotify"
                 "InterfaceId out of range\n");
        return;
    }

    Adapter_PECDev_Disable_CommandIRQ(dev, InterfaceId);

    LOG_INFO("AdapterPEC_InterruptHandlerCommandNotify: Enter\n");

    if (dev->PEC_Notify[InterfaceId].CommandNotifyCB_p != NULL)
    {
        PEC_NotifyFunction_t CBFunc_p;
	void *args = dev->PEC_Notify[InterfaceId].command_notify_args;

        // Keep the callback on stack to allow registration
        // of another command notify request from callback
        CBFunc_p = dev->PEC_Notify[InterfaceId].CommandNotifyCB_p;

        dev->PEC_Notify[InterfaceId].CommandNotifyCB_p = NULL;
        dev->PEC_Notify[InterfaceId].CommandsCount = 0;
	dev->PEC_Notify[InterfaceId].command_notify_args = NULL;

        LOG_INFO(
            "AdapterPEC_InterruptHandlerCommandNotify: "
            "Invoking PEC command notify callback interface=%d\n",
            InterfaceId);

        CBFunc_p(args);
    }
}
#endif /* ADAPTER_PEC_INTERRUPTS_ENABLE */


/*----------------------------------------------------------------------------
 * Adapter_MakeCommandNotify_CallBack
 */
static inline void
Adapter_MakeCommandNotify_CallBack(cae_device *dev, unsigned int InterfaceId)
{
    unsigned int PacketSlotsEmptyCount;

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return;

    if (dev->PEC_Notify[InterfaceId].CommandNotifyCB_p != NULL)
    {
        PacketSlotsEmptyCount = Adapter_PECDev_GetFreeSpace(dev, InterfaceId);

        if (dev->PEC_Notify[InterfaceId].CommandsCount <= PacketSlotsEmptyCount)
        {
            PEC_NotifyFunction_t CBFunc_p;
	    void *args = dev->PEC_Notify[InterfaceId].command_notify_args;

            // Keep the callback on stack to allow registeration
            // of another result notify request from callback
            CBFunc_p = dev->PEC_Notify[InterfaceId].CommandNotifyCB_p;

            dev->PEC_Notify[InterfaceId].CommandNotifyCB_p = NULL;
            dev->PEC_Notify[InterfaceId].CommandsCount = 0;

            LOG_INFO(
                "PEC_Packet_Get: "
                "Invoking command notify callback\n");

            CBFunc_p(args);
        }
    }
}


/*----------------------------------------------------------------------------
 * Adapter_PECResgisterSA_BounceIfRequired
 *
 * Returns false in case of error.
 * Allocate a bounce buffer and copy the data in case this if required.
 */
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
static bool
Adapter_PECRegisterSA_BounceIfRequired(cae_device *dev,
        DMAResource_Handle_t *DMAHandle_p)
{
    DMAResource_Handle_t DMAHandle = *DMAHandle_p;
    DMAResource_Record_t * Rec_p;
    DMAResource_AddrPair_t BounceHostAddr;
    void * HostAddr;
    int dmares;

    // skip null handles
    if (!DMAResource_IsValidHandle(dev, DMAHandle))
        return true;    // no error

    Rec_p = DMAResource_Handle2RecordPtr(dev, DMAHandle);


    // skip proper buffers
    if (!Adapter_DMAResource_IsForeignAllocated(dev, DMAHandle))
    {
        Rec_p->bounce.Bounce_Handle = NULL;
        return true;    // no error
    }

    {
        DMAResource_Properties_t BounceProperties;

        // used as uint32_t array
        BounceProperties.Alignment  = Adapter_DMAResource_Alignment_Get();
        BounceProperties.Bank       = ADAPTER_PEC_BANK_SA;
        BounceProperties.fCached    = false;
        BounceProperties.Size       = Rec_p->Props.Size;

        HostAddr = Adapter_DMAResource_HostAddr(dev, DMAHandle);

        dmares = DMAResource_Alloc(dev,
                     BounceProperties,
                     &BounceHostAddr,
                     &Rec_p->bounce.Bounce_Handle);

        // bounce buffer handle is stored in the DMA Resource Record
        // of the original buffer, which links the two
        // this will be used when freeing the buffer
        // but also when the SA is referenced in packet put

        if (dmares != 0)
        {
            LOG_CRIT(
                "PEC_SA_Register: "
                "Failed to alloc bounce buffer (error %d)\n",
                dmares);
            return false;   // error!
        }
        LOG_INFO(
            "PEC_SA_Register: "
            "Bouncing SA: %p to %p\n",
            DMAHandle,
            Rec_p->bounce.Bounce_Handle);
#ifdef ADAPTER_PEC_ARMRING_ENABLE_SWAP
        DMAResource_SwapEndianness_Set(dev, Rec_p->bounce.Bounce_Handle, true);
#endif

    }

    // copy the data to the bounce buffer
    memcpy(
        BounceHostAddr.Address_p,
        HostAddr,
        Rec_p->Props.Size);

    *DMAHandle_p = Rec_p->bounce.Bounce_Handle;
    return true;        // no error
}
#endif /* ADAPTER_PEC_REMOVE_BOUNCEBUFFERS */


/*----------------------------------------------------------------------------
 * Adapter_FIFO_Put
 *
 * Put packet information into the side channel FIFO
 */
static bool
Adapter_FIFO_Put(AdapterPEC_SideChannelFIFO_t *FIFO,
                 void *User_p,
                 DMABuf_Handle_t SrcPkt_Handle,
                 DMABuf_Handle_t DstPkt_Handle,
                 DMABuf_Handle_t Token_Handle,
                 unsigned int Bypass_WordCount)
{
    int WriteIndex = FIFO->WriteIndex;
    int ReadIndex = FIFO->ReadIndex;
    if (WriteIndex == ReadIndex - 1 ||
        (ReadIndex == 0 && WriteIndex == FIFO->Size - 1))
    {
        LOG_CRIT("Side channel FIFO full\n");
        return false;
    }
    FIFO->Records[WriteIndex].User_p = User_p;
    FIFO->Records[WriteIndex].SrcPkt_Handle = SrcPkt_Handle;
    FIFO->Records[WriteIndex].DstPkt_Handle = DstPkt_Handle;

    FIFO->Records[WriteIndex].Token_Handle = Token_Handle;
    if (!DMABuf_Handle_IsSame(&Token_Handle, &DMABuf_NULLHandle))
    {
        FIFO->Records[WriteIndex].Bypass_WordCount = Bypass_WordCount;
    }

    WriteIndex += 1;
    if (WriteIndex == FIFO->Size)
        WriteIndex = 0;
    FIFO->WriteIndex = WriteIndex;
    return true;
}


/*----------------------------------------------------------------------------
 * Adapter_FIFO_Get
 *
 * Get and remove the oldest entry from the side channel FIFO.
 */
static bool
Adapter_FIFO_Get(AdapterPEC_SideChannelFIFO_t *FIFO,
                 void **User_p,
                 DMABuf_Handle_t *SrcPkt_Handle_p,
                 DMABuf_Handle_t *DstPkt_Handle_p,
                 DMABuf_Handle_t *Token_Handle_p,
                 unsigned int *Bypass_WordCount_p)
{
    int WriteIndex = FIFO->WriteIndex;
    int ReadIndex = FIFO->ReadIndex;
    if (WriteIndex == ReadIndex)
    {
        LOG_CRIT("Trying to read from empty FIFO\n");
        return false;
    }
    *User_p = FIFO->Records[ReadIndex].User_p;
    *SrcPkt_Handle_p = FIFO->Records[ReadIndex].SrcPkt_Handle;
    *DstPkt_Handle_p = FIFO->Records[ReadIndex].DstPkt_Handle;

    *Token_Handle_p = FIFO->Records[ReadIndex].Token_Handle;
    if (!DMABuf_Handle_IsSame(Token_Handle_p, &DMABuf_NULLHandle))
        *Bypass_WordCount_p = FIFO->Records[ReadIndex].Bypass_WordCount;

    ReadIndex += 1;
    if (ReadIndex == FIFO->Size)
        ReadIndex = 0;
    FIFO->ReadIndex = ReadIndex;
    return true;
}


/*----------------------------------------------------------------------------
 * Adapter_FIFO_Withdraw
 *
 * Withdraw the most recently added record from the side channel FIFO.
 */
static void
Adapter_FIFO_Withdraw(
        AdapterPEC_SideChannelFIFO_t *FIFO)
{
    int WriteIndex = FIFO->WriteIndex;
    if (WriteIndex == FIFO->ReadIndex)
    {
        LOG_CRIT("Adapter_FIFO_Withdraw: FIFO is empty\n");
    }
    if (WriteIndex == 0)
        WriteIndex = FIFO->Size - 1;
    else
        WriteIndex -= 1;
    FIFO->WriteIndex = WriteIndex;
}


/* Adapter_Packet_Prepare
 *
 * In case of bounce buffers, allocate bounce buffers for the packet and
 * the packet token.
 * Copy source packet and token into the bounce buffers.
 * Perform PreDMA on all packet buffers (source, destination and token).
 */
static PEC_Status_t
Adapter_Packet_Prepare(cae_device *dev,
        const PEC_CommandDescriptor_t *Cmd_p)
{
    DMAResource_Handle_t SrcPkt_Handle, DstPkt_Handle, Token_Handle;
#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    unsigned int ParticleCount;
    unsigned int i;
    DMABuf_Handle_t ParticleHandle;
    DMAResource_Handle_t DMARes_Handle;
    uint8_t * DummyPtr;
    unsigned int ParticleSize;
#endif

    SrcPkt_Handle =
        Adapter_DMABuf_Handle2DMAResourceHandle(Cmd_p->SrcPkt_Handle);
    DstPkt_Handle =
        Adapter_DMABuf_Handle2DMAResourceHandle(Cmd_p->DstPkt_Handle);
    Token_Handle = Adapter_DMABuf_Handle2DMAResourceHandle(Cmd_p->Token_Handle);

    if (!DMAResource_IsValidHandle(dev, SrcPkt_Handle) &&
        !DMAResource_IsValidHandle(dev, DstPkt_Handle))
        return PEC_STATUS_OK; // For record invalidation in the Record Cache
    else if (!DMAResource_IsValidHandle(dev, SrcPkt_Handle) ||
        !DMAResource_IsValidHandle(dev, DstPkt_Handle))
    {
        LOG_CRIT("PEC_Packet_Put: invalid source or destination handle\n");
        return PEC_ERROR_BAD_PARAMETER;
    }

    // Token handle
    if (DMAResource_IsValidHandle(dev, Token_Handle))
    {
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
        DMAResource_Record_t * Rec_p =
            DMAResource_Handle2RecordPtr(dev, Token_Handle);
        if (Adapter_DMAResource_IsForeignAllocated(dev, Token_Handle))
        {
            // Bounce buffer required.
            DMAResource_AddrPair_t BounceHostAddr;
            void * HostAddr;
            int dmares;
            DMAResource_Properties_t BounceProperties;

            // used as uint32_t array
            BounceProperties.Alignment  = Adapter_DMAResource_Alignment_Get();
            BounceProperties.Bank       = ADAPTER_PEC_BANK_TOKEN;
            BounceProperties.fCached    = false;
            BounceProperties.Size       = Rec_p->Props.Size;

            HostAddr = Adapter_DMAResource_HostAddr(dev, Token_Handle);

            dmares = DMAResource_Alloc(dev,
                BounceProperties,
                &BounceHostAddr,
                &Rec_p->bounce.Bounce_Handle);

            // bounce buffer handle is stored in the DMA Resource Record
            // of the original buffer, which links the two
            // this will be used when freeing the buffer
            // but also when obtaining the bus address.

            if (dmares != 0)
            {
                LOG_CRIT(
                    "PEC_Packet_Put: "
                    "Failed to alloc bounce buffer (error %d)\n",
                dmares);
                return PEC_ERROR_INTERNAL;   // error!
            }

            LOG_INFO(
                "PEC_Packet_Putr: "
                "Bouncing Token: %p to %p\n",
                Token_Handle,
                Rec_p->bounce.Bounce_Handle);

            // copy the data to the bounce buffer
            memcpy(
                BounceHostAddr.Address_p,
                HostAddr,
                Rec_p->Props.Size);

            Token_Handle = Rec_p->bounce.Bounce_Handle;
        }
        else
        {
            Rec_p->bounce.Bounce_Handle = NULL;
        }
#endif // !ADAPTER_PEC_REMOVE_BOUNCEBUFFERS

#ifdef ADAPTER_PEC_ARMRING_ENABLE_SWAP
        // Convert token data to packet engine endianness format
        DMAResource_SwapEndianness_Set(dev, Token_Handle, true);

        DMAResource_Write32Array(
            Token_Handle,
            0,
            Cmd_p->Token_WordCount,
            Adapter_DMAResource_HostAddr(dev, Token_Handle));
#endif // ADAPTER_PEC_ARMRING_ENABLE_SWAP

        DMAResource_PreDMA(dev, Token_Handle, 0, 0);
    }

    // Source packet handle
#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    PEC_SGList_GetCapacity(Cmd_p->SrcPkt_Handle, &ParticleCount);

    if (ParticleCount > 0)
    {
        for (i=0; i<ParticleCount; i++)
        {
            PEC_SGList_Read(Cmd_p->SrcPkt_Handle,
                            i,
                            &ParticleHandle,
                            &ParticleSize,
                            &DummyPtr);
            DMARes_Handle =
                Adapter_DMABuf_Handle2DMAResourceHandle(ParticleHandle);
            DMAResource_PreDMA(dev, DMARes_Handle, 0, 0);
        }
    }
    else
#endif
    { // Not a gather packet,
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
        DMAResource_Record_t * Rec_p =
            DMAResource_Handle2RecordPtr(dev, SrcPkt_Handle);
        DMAResource_Record_t * Dst_Rec_p =
            DMAResource_Handle2RecordPtr(dev, DstPkt_Handle);
        if (Adapter_DMAResource_IsForeignAllocated(dev, SrcPkt_Handle) ||
            Adapter_DMAResource_IsForeignAllocated(dev, DstPkt_Handle))
        {
            // Bounce buffer required. Use a single bounce buffer for
            // both the source and the destination packet.
            DMAResource_AddrPair_t BounceHostAddr;
            void * HostAddr;
            int dmares;
            DMAResource_Properties_t BounceProperties;

            // used as uint32_t array
            BounceProperties.Alignment  = Adapter_DMAResource_Alignment_Get();
            BounceProperties.Bank       = ADAPTER_PEC_BANK_PACKET;
            BounceProperties.fCached    = false;
            BounceProperties.Size       = MAX(Rec_p->Props.Size,
                                              Dst_Rec_p->Props.Size);

            HostAddr = Adapter_DMAResource_HostAddr(dev, SrcPkt_Handle);

            dmares = DMAResource_Alloc(dev,
                BounceProperties,
                &BounceHostAddr,
                &Rec_p->bounce.Bounce_Handle);

            // bounce buffer handle is stored in the DMA Resource Record
            // of the original buffer, which links the two
            // this will be used when freeing the buffer
            // but also when obtaining the bus address.

            if (dmares != 0)
            {
                LOG_CRIT(
                    "PEC_Packet_Put: "
                    "Failed to alloc bounce buffer (error %d)\n",
                dmares);
                return PEC_ERROR_INTERNAL;   // error!
            }
            LOG_INFO(
                "PEC_Packet_Putr: "
                "Bouncing Packet: %p to %p\n",
                SrcPkt_Handle,
                Rec_p->bounce.Bounce_Handle);


            // copy the data to the bounce buffer
            memcpy(
                BounceHostAddr.Address_p,
                HostAddr,
                Rec_p->Props.Size);

            DstPkt_Handle = SrcPkt_Handle = Rec_p->bounce.Bounce_Handle;

            Dst_Rec_p->bounce.Bounce_Handle = Rec_p->bounce.Bounce_Handle;
        }
        else
        {
            Rec_p->bounce.Bounce_Handle = NULL;
            Dst_Rec_p->bounce.Bounce_Handle = NULL;
        }
#endif
        DMAResource_PreDMA(dev, SrcPkt_Handle, 0, 0);
    }
    // Destination packet handle
#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    PEC_SGList_GetCapacity(Cmd_p->DstPkt_Handle, &ParticleCount);

    if (ParticleCount > 0)
    {
        for (i=0; i<ParticleCount; i++)
        {
            PEC_SGList_Read(Cmd_p->DstPkt_Handle,
                            i,
                            &ParticleHandle,
                            &ParticleSize,
                            &DummyPtr);
            DMARes_Handle =
                Adapter_DMABuf_Handle2DMAResourceHandle(ParticleHandle);
            DMAResource_PreDMA(dev, DMARes_Handle, 0, 0);
        }
    }
    else
#endif
    if (SrcPkt_Handle != DstPkt_Handle)
    {
        // Only if source and destination are distinct.
        // When bounce buffers were used, these are not distinct.
        DMAResource_PreDMA(dev, DstPkt_Handle, 0, 0);
    }
    return PEC_STATUS_OK;
}


/* Adapter_Packet_Finalize
 *
 * Perform PostDMA on all DMA buffers (source, destination and token).
 * Copy the destination packet from the bounce buffer into the final location.
 * Deallocate any bounce buffers (packet and token).
 */
static PEC_Status_t
Adapter_Packet_Finalize(cae_device *dev,
        DMABuf_Handle_t DMABuf_SrcPkt_Handle,
        DMABuf_Handle_t DMABuf_DstPkt_Handle,
        DMABuf_Handle_t DMABuf_Token_Handle)
{
    DMAResource_Handle_t SrcPkt_Handle, DstPkt_Handle, Token_Handle;

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    unsigned int ParticleCount;
    unsigned int i;
    DMABuf_Handle_t ParticleHandle;
    DMAResource_Handle_t DMARes_Handle;
    uint8_t * DummyPtr;
    unsigned int ParticleSize;
#endif

    SrcPkt_Handle =
        Adapter_DMABuf_Handle2DMAResourceHandle(DMABuf_SrcPkt_Handle);
    DstPkt_Handle =
        Adapter_DMABuf_Handle2DMAResourceHandle(DMABuf_DstPkt_Handle);

    if (!DMAResource_IsValidHandle(dev, SrcPkt_Handle) &&
        !DMAResource_IsValidHandle(dev, DstPkt_Handle))
        return PEC_STATUS_OK; // For record invalidation in the Record Cache

    Token_Handle = Adapter_DMABuf_Handle2DMAResourceHandle(DMABuf_Token_Handle);

    // Token Handle.
    if (DMAResource_IsValidHandle(dev, Token_Handle))
    {
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
        DMAResource_Record_t * Rec_p =
            DMAResource_Handle2RecordPtr(dev, Token_Handle);
        if (Rec_p->bounce.Bounce_Handle != NULL)
        {
            // Post DMA and release the bounce buffer.
            DMAResource_PostDMA(dev, Rec_p->bounce.Bounce_Handle, 0, 0);
            DMAResource_Release(dev, Rec_p->bounce.Bounce_Handle);
        }
        else
#endif
        {
            DMAResource_PostDMA(dev, Token_Handle, 0, 0);
        }
    }
    // Destination packet handle

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    PEC_SGList_GetCapacity(DMABuf_DstPkt_Handle, &ParticleCount);

    if (ParticleCount > 0)
    {
        for (i=0; i<ParticleCount; i++)
        {
            PEC_SGList_Read(DMABuf_DstPkt_Handle,
                            i,
                            &ParticleHandle,
                            &ParticleSize,
                            &DummyPtr);
            DMARes_Handle =
                Adapter_DMABuf_Handle2DMAResourceHandle(ParticleHandle);
            DMAResource_PostDMA(dev, DMARes_Handle, 0, 0);
        }
    }
    else
#endif
    {
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
        DMAResource_Record_t * Rec_p =
            DMAResource_Handle2RecordPtr(dev, DstPkt_Handle);
        void * HostAddr = Adapter_DMAResource_HostAddr(dev, DstPkt_Handle);
        if (Rec_p->bounce.Bounce_Handle != NULL)
        {
            void * BounceHostAddr =
                Adapter_DMAResource_HostAddr(dev, Rec_p->bounce.Bounce_Handle);
            // Post DMA, copy and release the bounce buffer.
            DMAResource_PostDMA(dev, Rec_p->bounce.Bounce_Handle, 0, 0);

            memcpy( HostAddr, BounceHostAddr, Rec_p->Props.Size);

            DMAResource_Release(dev, Rec_p->bounce.Bounce_Handle);
            SrcPkt_Handle = DstPkt_Handle;
        }
        else
#endif
        {
            DMAResource_PostDMA(dev, DstPkt_Handle, 0, 0);
        }

    }
    // Source packet handle
#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    PEC_SGList_GetCapacity(DMABuf_SrcPkt_Handle, &ParticleCount);

    if (ParticleCount > 0)
    {
        for (i=0; i<ParticleCount; i++)
        {
            PEC_SGList_Read(DMABuf_SrcPkt_Handle,
                            i,
                            &ParticleHandle,
                            &ParticleSize,
                            &DummyPtr);
            DMARes_Handle =
                Adapter_DMABuf_Handle2DMAResourceHandle(ParticleHandle);
            DMAResource_PostDMA(dev, DMARes_Handle, 0, 0);
        }
    }
    else
#endif
    if (SrcPkt_Handle != DstPkt_Handle)
    {
        // Only if source and destination are distinct.
        // When bounce buffers were used, these are not distinct.
        DMAResource_PostDMA(dev, SrcPkt_Handle, 0, 0);
    }

    return PEC_STATUS_OK;
}


#ifdef ADAPTER_PEC_RPM_EIP202_DEVICE0_ID
/*----------------------------------------------------------------------------
 * AdapterPEC_Resume
 */
static int
AdapterPEC_Resume(cae_device *dev, void * p)
{
    int InterfaceId = *(int *)p;

    if (InterfaceId < 0 || InterfaceId < ADAPTER_PEC_RPM_EIP202_DEVICE0_ID)
        return -3; // error

    InterfaceId -= ADAPTER_PEC_RPM_EIP202_DEVICE0_ID;

    return Adapter_PECDev_Resume(dev, InterfaceId);
}


/*----------------------------------------------------------------------------
 * AdapterPEC_Suspend
 */
static int
AdapterPEC_Suspend(cae_device *dev, void * p)
{
    int InterfaceId = *(int *)p;

    if (InterfaceId < 0 || InterfaceId < ADAPTER_PEC_RPM_EIP202_DEVICE0_ID)
        return -3; // error

    InterfaceId -= ADAPTER_PEC_RPM_EIP202_DEVICE0_ID;

    return Adapter_PECDev_Suspend(dev, InterfaceId);
}
#endif


/*----------------------------------------------------------------------------
 * PEC_Capabilities_Get
 */
PEC_Status_t
PEC_Capabilities_Get(
        PEC_Capabilities_t * const Capabilities_p)
{
    return Adapter_PECDev_Capabilities_Get(Capabilities_p);
}


/*----------------------------------------------------------------------------
 * PEC_Init
 */
PEC_Status_t
PEC_Init(cae_device *dev,
        const unsigned int InterfaceId,
        const PEC_InitBlock_t * const InitBlock_p)
{
    LOG_INFO("\n\t PEC_Init \n");

    if (!InitBlock_p)
        return PEC_ERROR_BAD_PARAMETER;

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return PEC_ERROR_BAD_PARAMETER;

    Adapter_Lock_CS_Set(&dev->AdapterPEC_InitCS, &dev->AdapterPEC_InitLock);

    if (!Adapter_Lock_CS_Enter(&dev->AdapterPEC_InitCS))
        return PEC_STATUS_BUSY;

    // ensure we init only once
    if (dev->PEC_IsInitialized[InterfaceId])
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_STATUS_OK;
    }

    // Allocate the Put lock
    dev->AdapterPEC_PutLock[InterfaceId] = Adapter_Lock_Alloc();
    if (dev->AdapterPEC_PutLock[InterfaceId] == NULL)
    {
        LOG_CRIT("PEC_Init: PutLock allocation failed\n");
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_ERROR_INTERNAL;
    }
    Adapter_Lock_CS_Set(&dev->AdapterPEC_PutCS[InterfaceId],
                         dev->AdapterPEC_PutLock[InterfaceId]);

    // Allocate the Get lock
    dev->AdapterPEC_GetLock[InterfaceId] = Adapter_Lock_Alloc();
    if (dev->AdapterPEC_GetLock[InterfaceId] == NULL)
    {
        LOG_CRIT("PEC_Init: GetLock allocation failed\n");
        Adapter_Lock_Free(dev->AdapterPEC_PutLock[InterfaceId]);
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_ERROR_INTERNAL;
    }
    Adapter_Lock_CS_Set(&dev->AdapterPEC_GetCS[InterfaceId],
                         dev->AdapterPEC_GetLock[InterfaceId]);

    ZEROINIT(dev->PEC_Notify[InterfaceId]);

    if (RPM_DEVICE_INIT_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
                                    AdapterPEC_Suspend,
                                    AdapterPEC_Resume) != RPM_SUCCESS)
        return PEC_ERROR_INTERNAL;

    // Init the device
    if (Adapter_PECDev_Init(dev, InterfaceId, InitBlock_p) != PEC_STATUS_OK)
    {
        (void)RPM_DEVICE_INIT_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId);
        LOG_CRIT("PEC_Init: Adapter_PECDev_Init failed\n");
        Adapter_Lock_Free(dev->AdapterPEC_PutLock[InterfaceId]);
        Adapter_Lock_Free(dev->AdapterPEC_GetLock[InterfaceId]);
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_ERROR_INTERNAL;
    }

    (void)RPM_DEVICE_INIT_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId);

    dev->Adapter_SideChannelFIFO[InterfaceId].Size =
        sizeof(dev->Adapter_SideChannelFIFO[InterfaceId].Records) /
        sizeof(dev->Adapter_SideChannelFIFO[InterfaceId].Records[0]);
    dev->Adapter_SideChannelFIFO[InterfaceId].WriteIndex = 0;
    dev->Adapter_SideChannelFIFO[InterfaceId].ReadIndex = 0;

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
    // enable the descriptor done interrupt
    LOG_INFO("PEC_Init: Registering interrupt handler\n");

    Adapter_PECDev_SetResultHandler(dev,
            InterfaceId,
            AdapterPEC_InterruptHandlerResultNotify);

    Adapter_PECDev_SetCommandHandler(dev,
            InterfaceId,
            AdapterPEC_InterruptHandlerCommandNotify);
#endif /* ADAPTER_PEC_INTERRUPTS_ENABLE */

    dev->PEC_IsInitialized[InterfaceId] = true;

    LOG_INFO("\n\t PEC_Init done \n");

    Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_UnInit
 */
PEC_Status_t
PEC_UnInit(cae_device *dev,
        const unsigned int InterfaceId)
{
    LOG_INFO("\n\t PEC_UnInit \n");

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return PEC_ERROR_BAD_PARAMETER;

    Adapter_Lock_CS_Set(&dev->AdapterPEC_InitCS, &dev->AdapterPEC_InitLock);

    if (!Adapter_Lock_CS_Enter(&dev->AdapterPEC_InitCS))
        return PEC_STATUS_BUSY;

    // ensure we uninit only once
    if (!dev->PEC_IsInitialized[InterfaceId])
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_STATUS_OK;
    }

    if (!Adapter_Lock_CS_Enter(&dev->AdapterPEC_PutCS[InterfaceId]))
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_STATUS_BUSY;
    }

    if (!Adapter_Lock_CS_Enter(&dev->AdapterPEC_GetCS[InterfaceId]))
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_PutCS[InterfaceId]);
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_STATUS_BUSY;
    }

    if (RPM_DEVICE_UNINIT_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
                                true) != RPM_SUCCESS)
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_PutCS[InterfaceId]);
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);
        return PEC_ERROR_INTERNAL;
    }

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
    Adapter_PECDev_Disable_ResultIRQ(dev, InterfaceId);
    Adapter_PECDev_Disable_CommandIRQ(dev, InterfaceId);
#endif

    Adapter_PECDev_UnInit(dev, InterfaceId);

    dev->PEC_IsInitialized[InterfaceId] = false;

    (void)RPM_DEVICE_UNINIT_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId);

    Adapter_Lock_CS_Leave(&dev->AdapterPEC_GetCS[InterfaceId]);
    Adapter_Lock_CS_Leave(&dev->AdapterPEC_PutCS[InterfaceId]);

    // Free Get lock
    Adapter_Lock_Free(Adapter_Lock_CS_Get(&dev->AdapterPEC_GetCS[InterfaceId]));
    Adapter_Lock_CS_Set(&dev->AdapterPEC_GetCS[InterfaceId], Adapter_Lock_NULL);

    // Free Put lock
    Adapter_Lock_Free(Adapter_Lock_CS_Get(&dev->AdapterPEC_PutCS[InterfaceId]));
    Adapter_Lock_CS_Set(&dev->AdapterPEC_PutCS[InterfaceId], Adapter_Lock_NULL);

    LOG_INFO("\n\t PEC_UnInit done \n");

    Adapter_Lock_CS_Leave(&dev->AdapterPEC_InitCS);

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_SA_Register
 */
PEC_Status_t
PEC_SA_Register(cae_device *dev,
        const unsigned int InterfaceId,
        DMABuf_Handle_t SA_Handle1,
        DMABuf_Handle_t SA_Handle2,
        DMABuf_Handle_t SA_Handle3)
{
    DMAResource_Handle_t DMAHandle1, DMAHandle2, DMAHandle3;
    PEC_Status_t res;

    LOG_INFO("\n\t PEC_SA_Register \n");

    IDENTIFIER_NOT_USED(InterfaceId);

    DMAHandle1 = Adapter_DMABuf_Handle2DMAResourceHandle(SA_Handle1);
    DMAHandle2 = Adapter_DMABuf_Handle2DMAResourceHandle(SA_Handle2);
    DMAHandle3 = Adapter_DMABuf_Handle2DMAResourceHandle(SA_Handle3);

    // The SA, State Record and ARC4 State Record are arrays of uint32_t.
    // The caller provides them in host-native format.
    // This function converts them to device-native format
    // using DMAResource and in-place operations.

    // Endianness conversion for the 1st SA memory block (Main SA Record)
#ifdef ADAPTER_PEC_ARMRING_ENABLE_SWAP
    {
        DMAResource_Record_t * const Rec_p =
            DMAResource_Handle2RecordPtr(dev, DMAHandle1);

        if (Rec_p == NULL)
            return PEC_ERROR_INTERNAL;

        DMAResource_SwapEndianness_Set(dev, DMAHandle1, true);

        DMAResource_Write32Array(
            DMAHandle1,
            0,
            Rec_p->Props.Size / 4,
            Adapter_DMAResource_HostAddr(dev, DMAHandle1));
    }

    // Endianness conversion for the 2nd SA memory block (State Record)
    if (DMAHandle2 != NULL)
    {
        DMAResource_Record_t * const Rec_p =
            DMAResource_Handle2RecordPtr(dev, DMAHandle2);

        if (Rec_p == NULL)
            return PEC_ERROR_INTERNAL;

        // The 2nd SA memory block can never be a subset of
        // the 1st SA memory block so it is safe to perform
        // the endianness conversion
        DMAResource_SwapEndianness_Set(dev, DMAHandle2, true);

        DMAResource_Write32Array(
            DMAHandle2,
            0,
            Rec_p->Props.Size / 4,
            Adapter_DMAResource_HostAddr(dev, DMAHandle2));
    }

    // Endianness conversion for the 3d SA memory block (ARC4 State Record)
    if (DMAHandle3 != NULL)
    {
        DMAResource_Record_t * const Rec_p =
            DMAResource_Handle2RecordPtr(dev, DMAHandle3);

        if (Rec_p == NULL)
            return PEC_ERROR_INTERNAL;

        // The 3d SA memory block can never be a subset of
        // the 2nd SA memory block.

        // Check if the 3d SA memory block is not a subset of the 1st one
        if (!Adapter_DMAResource_IsSubRangeOf(dev, DMAHandle3, DMAHandle1))
        {
            // The 3d SA memory block is a separate buffer and does not
            // overlap with the 1st SA memory block,
            // so the endianness conversion must be done
            DMAResource_SwapEndianness_Set(dev, DMAHandle3, true);

            DMAResource_Write32Array(
                    DMAHandle3,
                    0,
                    Rec_p->Props.Size / 4,
                    Adapter_DMAResource_HostAddr(dev, DMAHandle3));
        }
    }
#endif // ADAPTER_PEC_ARMRING_ENABLE_SWAP

#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
    // Bounce the SA buffers if required
    // Check if the 3d SA memory block is not a subset of the 1st one
    if (DMAHandle3 != NULL &&
        !Adapter_DMAResource_IsSubRangeOf(dev, DMAHandle3, DMAHandle1))
    {
        if (!Adapter_PECRegisterSA_BounceIfRequired(dev, &DMAHandle3))
            return PEC_ERROR_INTERNAL;
    }

    if (!Adapter_PECRegisterSA_BounceIfRequired(dev, &DMAHandle1))
        return PEC_ERROR_INTERNAL;

    if (!Adapter_PECRegisterSA_BounceIfRequired(dev, &DMAHandle2))
        return PEC_ERROR_INTERNAL;
#endif

    res = Adapter_PECDev_SA_Prepare(dev, SA_Handle1, SA_Handle2, SA_Handle3);
    if (res != PEC_STATUS_OK)
    {
        LOG_WARN(
            "PEC_SA_Register: "
            "Adapter_PECDev_PrepareSA returned %d\n",
            res);
        return PEC_ERROR_INTERNAL;
    }

    // now use DMAResource to ensure the engine
    // can read the memory blocks using DMA
    DMAResource_PreDMA(dev, DMAHandle1, 0, 0);     // 0,0 = "entire buffer"

    if (DMAHandle2 != NULL)
        DMAResource_PreDMA(dev, DMAHandle2, 0, 0);

    // Check if the 3d SA memory block is not a subset of the 1st one
    if (DMAHandle3 != NULL &&
        !Adapter_DMAResource_IsSubRangeOf(dev, DMAHandle3, DMAHandle1))
        DMAResource_PreDMA(dev, DMAHandle3, 0, 0);

    LOG_INFO("\n\t PEC_SA_Register done \n");

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_SA_UnRegister
 */
PEC_Status_t
PEC_SA_UnRegister(cae_device *dev,
        const unsigned int InterfaceId,
        DMABuf_Handle_t SA_Handle1,
        DMABuf_Handle_t SA_Handle2,
        DMABuf_Handle_t SA_Handle3)
{
    DMAResource_Handle_t SA_Handle[3];
    PEC_Status_t res;
    int i, MaxHandles;

    LOG_INFO("\n\t PEC_SA_UnRegister \n");

    IDENTIFIER_NOT_USED(InterfaceId);

    res = Adapter_PECDev_SA_Remove(SA_Handle1, SA_Handle2, SA_Handle3);
    if (res != PEC_STATUS_OK)
    {
        LOG_CRIT(
            "PEC_SA_UnRegister: "
            "Adapter_PECDev_SA_Remove returned %d\n",
            res);
        return PEC_ERROR_INTERNAL;
    }

    SA_Handle[0] = Adapter_DMABuf_Handle2DMAResourceHandle(SA_Handle1);
    SA_Handle[1] = Adapter_DMABuf_Handle2DMAResourceHandle(SA_Handle2);
    SA_Handle[2] = Adapter_DMABuf_Handle2DMAResourceHandle(SA_Handle3);

    // Check if the 3d SA memory block is not a subset of the 1st one
    if (SA_Handle[0] != NULL &&
        SA_Handle[2] != NULL &&
        Adapter_DMAResource_IsSubRangeOf(dev, SA_Handle[2], SA_Handle[0]))
        MaxHandles = 2;
    else
        MaxHandles = 3;

    for (i = 0; i < MaxHandles; i++)
    {
        if (DMAResource_IsValidHandle(dev, SA_Handle[i]))
        {
            DMAResource_Handle_t DMAHandle = SA_Handle[i];
            void *HostAddr;
            DMAResource_Record_t * Rec_p =
                DMAResource_Handle2RecordPtr(dev, DMAHandle);

            // Check if a bounce buffer is in use
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
            void * OrigHostAddr;
            DMAResource_Record_t * HostRec_p = Rec_p;

            OrigHostAddr = Adapter_DMAResource_HostAddr(dev, DMAHandle);

            if (Adapter_DMAResource_IsForeignAllocated(dev, SA_Handle[i]))
            {
                // Get bounce buffer handle and its record
                DMAHandle = HostRec_p->bounce.Bounce_Handle;
                Rec_p = DMAResource_Handle2RecordPtr(dev, DMAHandle);
            }
#endif /* ADAPTER_PEC_REMOVE_BOUNCEBUFFERS */

            HostAddr = Adapter_DMAResource_HostAddr(dev, DMAHandle);
            // ensure we look at valid engine-written data
            // 0,0 = "entire buffer"
            DMAResource_PostDMA(dev, DMAHandle, 0, 0);

            // convert to host format
            if (Rec_p != NULL)
                DMAResource_Read32Array(dev,
                    DMAHandle,
                    0,
                    Rec_p->Props.Size / 4,
                    HostAddr);

            // copy from bounce buffer to original buffer
#ifndef ADAPTER_PEC_REMOVE_BOUNCEBUFFERS
            if (Adapter_DMAResource_IsForeignAllocated(dev, SA_Handle[i]) &&
                HostRec_p != NULL)
            {
                // copy the data from bounce to original buffer
                memcpy(
                    OrigHostAddr,
                    HostAddr,
                    HostRec_p->Props.Size);

                // free the bounce handle
                DMAResource_Release(dev, HostRec_p->bounce.Bounce_Handle);
                HostRec_p->bounce.Bounce_Handle = NULL;
            }
#endif /* ADAPTER_PEC_REMOVE_BOUNCEBUFFERS */
        } // if handle valid
    } // for

    LOG_INFO("\n\t PEC_SA_UnRegister done\n");

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_Packet_Put
 */
PEC_Status_t
PEC_Packet_Put(cae_device *dev,
        const unsigned int InterfaceId,
        const PEC_CommandDescriptor_t * Commands_p,
        const unsigned int CommandsCount,
        unsigned int * const PutCount_p)
{
    unsigned int CmdLp;
    unsigned int PktCnt;
    unsigned int CmdDescriptorCount;
    PEC_Status_t res = 0, res2, PEC_Rc = PEC_STATUS_OK;
    unsigned int FreeSlots;

    //LOG_INFO("\n\t PEC_Packet_Put \n");

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return PEC_ERROR_BAD_PARAMETER;

#ifdef ADAPTER_PEC_STRICT_ARGS
    if (Commands_p == NULL ||
        CommandsCount == 0 ||
        PutCount_p == NULL)
    {
        return PEC_ERROR_BAD_PARAMETER;
    }
#endif

    // initialize the output parameters
    *PutCount_p = 0;

#ifdef ADAPTER_PEC_STRICT_ARGS
    // validate the descriptors
    // (error out before bounce buffer allocation)
    for (CmdLp = 0; CmdLp < CommandsCount; CmdLp++)
        if (Commands_p[CmdLp].Bypass_WordCount > 255)
            return PEC_ERROR_BAD_PARAMETER;
#endif /* ADAPTER_PEC_STRICT_ARGS */

    if (!Adapter_Lock_CS_Enter(&dev->AdapterPEC_PutCS[InterfaceId]))
        return PEC_STATUS_BUSY;

    if (!dev->PEC_IsInitialized[InterfaceId])
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_PutCS[InterfaceId]);
        return PEC_ERROR_BAD_USE_ORDER;
    }

    CmdDescriptorCount = MIN(ADAPTER_PEC_MAX_LOGICDESCR, CommandsCount);
    FreeSlots = 0;
    CmdLp = 0;
    while (CmdLp < CmdDescriptorCount)
    {
        unsigned int j;
        unsigned int count;
        unsigned int NonSGPackets;

#ifndef ADAPTER_PEC_ENABLE_SCATTERGATHER
        NonSGPackets = CmdDescriptorCount - CmdLp;
        // All remaining packets are non-SG.
#else
        unsigned int GatherParticles;
        unsigned int ScatterParticles;
        unsigned int i;

        for (i = CmdLp; i < CmdDescriptorCount; i++)
        {
            PEC_SGList_GetCapacity(Commands_p[i].SrcPkt_Handle,
                                   &GatherParticles);
            PEC_SGList_GetCapacity(Commands_p[i].DstPkt_Handle,
                               &ScatterParticles);
            if ( GatherParticles > 0 || ScatterParticles > 0)
                break;
        }
        NonSGPackets = i - CmdLp;

        if (NonSGPackets == 0)
        {
            bool fSuccess;

            if (RPM_DEVICE_IO_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                                   InterfaceId,
                                          RPM_FLAG_SYNC) != RPM_SUCCESS)
            {
                PEC_Rc = PEC_ERROR_INTERNAL;
                break;
            }

            // First packet found is scatter gather.
            fSuccess = Adapter_PECDev_TestSG(InterfaceId,
                                             GatherParticles,
                                             ScatterParticles);

            (void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                           InterfaceId,
                                           RPM_FLAG_ASYNC);

            if (!fSuccess)
            {
                PEC_Rc = PEC_ERROR_INTERNAL;
                break;
            }

            // Process a single SG packet in this iteration.
            FreeSlots = 1;
        }
        else
#endif
        if (FreeSlots == 0)
        {
            if (RPM_DEVICE_IO_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                                   InterfaceId,
                                          RPM_FLAG_SYNC) != RPM_SUCCESS)
            {
                PEC_Rc = PEC_ERROR_INTERNAL;
                break;
            }

            // Allow all non-SG packets to be processed in this iteration,
            // but limited by the number of free slots in the ring(s).
            FreeSlots = Adapter_PECDev_GetFreeSpace(dev, InterfaceId);

            (void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                           InterfaceId,
                                           RPM_FLAG_ASYNC);

            if (FreeSlots > NonSGPackets)
                FreeSlots = NonSGPackets;

            if (FreeSlots == 0)
                break;
        }

        for (PktCnt=0; PktCnt<FreeSlots; PktCnt++)
        {
            res = Adapter_Packet_Prepare(dev, Commands_p + CmdLp + PktCnt);
            if (res != PEC_STATUS_OK)
            {
                LOG_CRIT("%s: Adapter_Packet_Prepare error %d\n", __func__, res);
                PEC_Rc = res;
                break;
            }

            Adapter_FIFO_Put(&(dev->Adapter_SideChannelFIFO[InterfaceId]),
                             Commands_p[CmdLp+PktCnt].User_p,
                             Commands_p[CmdLp+PktCnt].SrcPkt_Handle,
                             Commands_p[CmdLp+PktCnt].DstPkt_Handle,
                             Commands_p[CmdLp+PktCnt].Token_Handle,
                             Commands_p[CmdLp+PktCnt].Bypass_WordCount);
        }

        // RPM_Device_IO_Start() must be called for each successfully submitted
        // packet
        for (j = 0; j < PktCnt; j++)
        {
            // Skipped error checking to reduce code complexity
            (void)RPM_DEVICE_IO_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                                InterfaceId,
                                            RPM_FLAG_SYNC);
        }

        res2 = Adapter_PECDev_Packet_Put(dev, InterfaceId,
                                         Commands_p + CmdLp,
                                         PktCnt,
                                         &count);
        if (res2 != PEC_STATUS_OK)
        {
            LOG_CRIT("%s: Adapter_PECDev_Packet_Put error %d\n", __func__, res2);
            PEC_Rc = res2;
        }

        FreeSlots -= count;
        *PutCount_p += count;

        if (count <  PktCnt)
        {
            LOG_WARN("PEC_Packet_Put: withdrawing %d prepared packets\n",
                     PktCnt - count);

            for (j = count; j < PktCnt; j++)
            {
                Adapter_FIFO_Withdraw(&(dev->Adapter_SideChannelFIFO[InterfaceId]));
                Adapter_Packet_Finalize(dev, Commands_p[CmdLp + j].SrcPkt_Handle,
                                        Commands_p[CmdLp + j].DstPkt_Handle,
                                        Commands_p[CmdLp + j].Token_Handle);

                // RPM_DEVICE_IO_STOP_MACRO() must be called here for packets
                // which could not be successfully submitted,
                // for example because device queue was full
                (void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                               InterfaceId,
                                               RPM_FLAG_ASYNC);
            }
            break;
        }

        CmdLp += count;

        if (res != PEC_STATUS_OK || res2 != PEC_STATUS_OK)
        {
            PEC_Rc = PEC_ERROR_INTERNAL;
            break;
        }
    } // while

    //LOG_INFO("\n\t PEC_Packet_Put done \n");

    Adapter_Lock_CS_Leave(&dev->AdapterPEC_PutCS[InterfaceId]);

    return PEC_Rc;
}


/*----------------------------------------------------------------------------
 * PEC_Packet_Get
 */
PEC_Status_t
PEC_Packet_Get(cae_device *dev,
        const unsigned int InterfaceId,
        PEC_ResultDescriptor_t * Results_p,
        const unsigned int ResultsLimit,
        unsigned int * const GetCount_p)
{
    LOG_INFO("\n\t PEC_Packet_Get \n");

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return PEC_ERROR_BAD_PARAMETER;

#ifdef ADAPTER_PEC_STRICT_ARGS
    if (Results_p == NULL ||
        GetCount_p == NULL ||
        ResultsLimit == 0)
    {
        return PEC_ERROR_BAD_PARAMETER;
    }
#endif

    // initialize the output parameter
    *GetCount_p = 0;

    if (!Adapter_Lock_CS_Enter(&dev->AdapterPEC_GetCS[InterfaceId]))
        return PEC_STATUS_BUSY;

    if (!dev->PEC_IsInitialized[InterfaceId])
    {
        Adapter_Lock_CS_Leave(&dev->AdapterPEC_GetCS[InterfaceId]);
        return PEC_ERROR_BAD_USE_ORDER;
    }

    // read descriptors from PEC device
    {
        PEC_Status_t res;
        unsigned int ResLp;
        unsigned int Limit = MIN(ResultsLimit, ADAPTER_PEC_MAX_LOGICDESCR);
        unsigned int count;
        DMABuf_Handle_t Token_Handle = DMABuf_NULLHandle;

        res=Adapter_PECDev_Packet_Get(dev, InterfaceId,
                                      Results_p,
                                      Limit,
                                      &count);
        if (res != PEC_STATUS_OK)
        {
            LOG_CRIT("PEC_Packet_Get() returned error: %d\n", res);
            Adapter_Lock_CS_Leave(&dev->AdapterPEC_GetCS[InterfaceId]);
            return res;
        }

        for (ResLp = 0; ResLp < count; ResLp++)
        {
            // To help CommandNotifyCB
            if (ResLp == count-1)
                Adapter_MakeCommandNotify_CallBack(dev, InterfaceId);

            (void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID +
                                                        InterfaceId,
                                           RPM_FLAG_ASYNC);

            Adapter_FIFO_Get(&(dev->Adapter_SideChannelFIFO[InterfaceId]),
                             &(Results_p[ResLp].User_p),
                             &(Results_p[ResLp].SrcPkt_Handle),
                             &(Results_p[ResLp].DstPkt_Handle),
                             &Token_Handle,
                             &(Results_p[ResLp].Bypass_WordCount));

            Adapter_Packet_Finalize(dev, Results_p[ResLp].SrcPkt_Handle,
                                    Results_p[ResLp].DstPkt_Handle,
                                    Token_Handle);

            if (!DMABuf_Handle_IsSame(&Results_p[ResLp].DstPkt_Handle,
                                      &DMABuf_NULLHandle))
            {
                Results_p[ResLp].DstPkt_p =
                        Adapter_DMAResource_HostAddr(dev, 
                                Adapter_DMABuf_Handle2DMAResourceHandle(
                                            Results_p[ResLp].DstPkt_Handle));
            }
            else
                Results_p[ResLp].DstPkt_p = NULL;
            *GetCount_p += 1;
        } // for
    }

    LOG_INFO("\n\t PEC_Packet_Get done \n");

    Adapter_Lock_CS_Leave(&dev->AdapterPEC_GetCS[InterfaceId]);

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_CD_Control_Write
 *
 * Write the Control1 and Control2 engine-specific fields in the
 * Command Descriptor The other fields (such as SrcPkt_ByteCount and
 * Bypass_WordCount must have been filled in already.
 *
 * Command_p (input, output)
 *     Command descriptor whose Control1 and Control2 fields must be filled in.
 *
 * PacketParams_p (input)
 *     Per-packet parameters.
 *
 * This function is not implemented for all engine types.
 */
PEC_Status_t
PEC_CD_Control_Write(
    PEC_CommandDescriptor_t *Command_p,
    const PEC_PacketParams_t *PacketParams_p)
{
    return Adapter_PECDev_CD_Control_Write(Command_p, PacketParams_p);
}


/*----------------------------------------------------------------------------
 * PEC_RD_Status_Read
 */
PEC_Status_t
PEC_RD_Status_Read(
        const PEC_ResultDescriptor_t * const Result_p,
        PEC_ResultStatus_t * const ResultStatus_p)
{
    return Adapter_PECDev_RD_Status_Read(Result_p, ResultStatus_p);
}


/*----------------------------------------------------------------------------
 * PEC_CommandNotify_Request
 */
PEC_Status_t
PEC_CommandNotify_Request(cae_device *dev,
        const unsigned int InterfaceId,
        PEC_NotifyFunction_t CBFunc_p,
	void *args,
        const unsigned int CommandsCount)
{
    unsigned int PacketSlotsEmptyCount;

    LOG_INFO("\n\t PEC_CommandNotify_Request \n");

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return PEC_ERROR_BAD_PARAMETER;

    if (CBFunc_p == NULL || args == NULL ||
        CommandsCount == 0 ||
        CommandsCount > ADAPTER_PEC_MAX_PACKETS)
    {
        return PEC_ERROR_BAD_PARAMETER;
    }

    if (!dev->PEC_IsInitialized[InterfaceId])
        return PEC_ERROR_BAD_USE_ORDER;

    if (RPM_DEVICE_IO_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
                                  RPM_FLAG_SYNC) != RPM_SUCCESS)
        return PEC_ERROR_INTERNAL;

    PacketSlotsEmptyCount = Adapter_PECDev_GetFreeSpace(dev, InterfaceId);

    (void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
                                   RPM_FLAG_ASYNC);

    if (CommandsCount <= PacketSlotsEmptyCount)
    {
        LOG_INFO(
            "PEC_CommandNotify_Request: "
            "Invoking command notify callback immediately\n");

        CBFunc_p(args);
    }
    else
    {
        dev->PEC_Notify[InterfaceId].CommandsCount = CommandsCount;
        dev->PEC_Notify[InterfaceId].CommandNotifyCB_p = CBFunc_p;
	dev->PEC_Notify[InterfaceId].command_notify_args = args;

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
        if (RPM_DEVICE_IO_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
                                      RPM_FLAG_SYNC) != RPM_SUCCESS)
            return PEC_ERROR_INTERNAL;

        /* Note that space for new commands may have become available before
         * the call to PEC_CommandNotify_Request and the associated interrupt
         * may already be pending. In this case the interrupt will occur
         * immediately.
         */
        Adapter_PECDev_Enable_CommandIRQ(dev, InterfaceId);

        (void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
                                       RPM_FLAG_ASYNC);
#endif /* ADAPTER_PEC_INTERRUPTS_ENABLE */
    }

    LOG_INFO("\n\t PEC_CommandNotify_Request done \n");

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_ResultNotify_Request
 */
PEC_Status_t
PEC_ResultNotify_Request(cae_device *dev,
        const unsigned int InterfaceId,
        PEC_NotifyFunction_t CBFunc_p,
	void *args,
        const unsigned int ResultsCount)
{
    LOG_INFO("\n\t PEC_ResultNotify_Request \n");

    if (InterfaceId >= ADAPTER_PEC_DEVICE_COUNT)
        return PEC_ERROR_BAD_PARAMETER;

    if (CBFunc_p == NULL || args == NULL ||
        ResultsCount == 0 ||
        ResultsCount > ADAPTER_PEC_MAX_PACKETS)
    {
        return PEC_ERROR_BAD_PARAMETER;
    }

    if (!dev->PEC_IsInitialized[InterfaceId])
        return PEC_ERROR_BAD_USE_ORDER;

    // install it
    dev->PEC_Notify[InterfaceId].ResultsCount = ResultsCount;
    dev->PEC_Notify[InterfaceId].ResultNotifyCB_p = CBFunc_p;
    dev->PEC_Notify[InterfaceId].result_notify_args = args;

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
    //if (RPM_DEVICE_IO_START_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
    //                              RPM_FLAG_SYNC) != RPM_SUCCESS)
    //    return PEC_ERROR_INTERNAL;

    /* Note that results may have become available before the call
       to PEC_ResultNotify_Request and the associated interrupts may already
       be pending. In this case the interrupt will occur immediately.
     */
    Adapter_PECDev_Enable_ResultIRQ(dev, InterfaceId);

    //(void)RPM_DEVICE_IO_STOP_MACRO(ADAPTER_PEC_RPM_EIP202_DEVICE0_ID + InterfaceId,
    //                               RPM_FLAG_ASYNC);
#endif /* ADAPTER_PEC_INTERRUPTS_ENABLE */

    LOG_INFO("\n\t PEC_ResultNotify_Request done\n");

    return PEC_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * PEC_Put_Dump
 */
void
PEC_Put_Dump(cae_device *dev,
        const unsigned int InterfaceId,
        const unsigned int FirstSlotId,
        const unsigned int LastSlotId,
        const bool fDumpRDRAdmin,
        const bool fDumpRDRCache)
{
    Adapter_PECDev_Put_Dump(dev, InterfaceId,
                            FirstSlotId,
                            LastSlotId,
                            fDumpRDRAdmin,
                            fDumpRDRCache);
}


/*----------------------------------------------------------------------------
 * PEC_Get_Dump
 */
void
PEC_Get_Dump(cae_device *dev,
        const unsigned int InterfaceId,
        const unsigned int FirstSlotId,
        const unsigned int LastSlotId,
        const bool fDumpRDRAdmin,
        const bool fDumpRDRCache)
{
    Adapter_PECDev_Get_Dump(dev, InterfaceId,
                            FirstSlotId,
                            LastSlotId,
                            fDumpRDRAdmin,
                            fDumpRDRCache);
}


#endif /* ADAPTER_PE_MODE_DHM */


/* end of file adapter_pec_dma.c */
