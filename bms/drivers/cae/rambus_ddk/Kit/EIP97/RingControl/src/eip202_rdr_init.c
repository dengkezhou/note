/* eip202_rdr_init.c
 *
 * EIP-202 Ring Control Driver Library
 * RDR Init/Reset API implementation
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
*****************************************************************************/

#include <cae.h>

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "eip202_rdr.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip202_ring.h"

// EIP-202 Ring Control Driver Library Types API
#include "eip202_ring_types.h"          // EIP202_Ring_* types

// EIP-202 Ring Control Driver Library Internal interfaces
#include "eip202_ring_internal.h"
#include "eip202_rdr_level0.h"          // EIP-202 Level 0 macros
#include "eip202_rdr_fsm.h"             // RDR State machine
#include "eip202_rdr_dscr.h"            // RingHelper callbacks
#include "eip202_rd_format.h"           // EIP-202 Result Descriptor

// RingHelper API
#include "ringhelper.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"                // IDENTIFIER_NOT_USED, bool, uint32_t

// Driver Framework Device API
#include "device_types.h"              // Device_Handle_t

// Driver Framework DMA Resource API
#include "dmares_types.h"         // types of the DMA resource API
#include "dmares_rw.h"            // read/write of the DMA resource API.

// Driver Framework C Run-Time Library API
#include "clib.h"

// Standard IOToken API
#include "iotoken.h"                   // IOToken_InWordCount_Get()


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP202Lib_Detect
 *
 * Checks the presence of EIP-202 HIA hardware. Returns true when found.
 */
static bool
EIP202Lib_RDR_Detect(cae_device *dev,
        const Device_Handle_t Device)
{
    uint32_t Value;

    // read-write test one of the registers

    // Set MASK_31_BITS bits of the EIP202_RDR_RING_BASE_ADDR_LO register
    EIP202_RDR_Write32(dev, Device,
                       EIP202_RDR_RING_BASE_ADDR_LO,
                       MASK_31_BITS );

    Value = EIP202_RDR_Read32(dev, Device, EIP202_RDR_RING_BASE_ADDR_LO);
    if ((Value & MASK_31_BITS) != MASK_31_BITS)
        return false;

    // Clear MASK_31_BITS bits of the EIP202_RDR_RING_BASE_ADDR_LO register
    EIP202_RDR_Write32(dev, Device, EIP202_RDR_RING_BASE_ADDR_LO, 0);
    Value = EIP202_RDR_Read32(dev, Device, EIP202_RDR_RING_BASE_ADDR_LO);
    if ((Value & MASK_31_BITS) != 0)
       return false;

    return true;
}


/*----------------------------------------------------------------------------
 * EIP202Lib_RDR_ClearAllDescriptors
 *
 * Clear all descriptors
 */
static inline void
EIP202Lib_RDR_ClearAllDescriptors(cae_device *dev,
        DMAResource_Handle_t Handle,
        const uint32_t DescriptorSpacingWordCount,
        const uint32_t DescriptorSizeWordCount,
        const uint32_t NumberOfDescriptors)
{
    unsigned int i, j;

    for(i = 0; i < NumberOfDescriptors; i++)
        for(j = 0; j < DescriptorSizeWordCount; j++)
            DMAResource_Write32(dev, Handle, i * DescriptorSpacingWordCount + j, 0);
}


/*----------------------------------------------------------------------------
 * EIP202_RDR_Init
 *
 */
EIP202_Ring_Error_t
EIP202_RDR_Init(cae_device *dev,
        EIP202_Ring_IOArea_t * IOArea_p,
        const Device_Handle_t Device,
        const EIP202_RDR_Settings_t * const RDRSettings_p)
{
    EIP202_Ring_Error_t rv;
    volatile EIP202_RDR_True_IOArea_t * const TrueIOArea_p = RDRIOAREA(IOArea_p);

    EIP202_RING_CHECK_POINTER(IOArea_p);

    // Initialize the IO Area
    TrueIOArea_p->Device = Device;
    TrueIOArea_p->State = (unsigned int)EIP202_RDR_STATE_UNINITIALIZED;

    // Check if the CPU integer size is enough to store 32-bit value
    if(sizeof(unsigned int) < sizeof(uint32_t))
        return EIP202_RING_UNSUPPORTED_FEATURE_ERROR;

    // Detect presence of EIP-202 CDR hardware
    if(!EIP202Lib_RDR_Detect(dev, Device))
        return EIP202_RING_UNSUPPORTED_FEATURE_ERROR;

    // Extension of 32-bit pointers to 64-bit addresses not supported.
    if(RDRSettings_p->Params.DMA_AddressMode == EIP202_RING_64BIT_DMA_EXT_ADDR)
        return EIP202_RING_UNSUPPORTED_FEATURE_ERROR;

    if(RDRSettings_p->Params.DscrOffsWordCount == 0 ||
       RDRSettings_p->Params.DscrOffsWordCount <
       RDRSettings_p->Params.DscrSizeWordCount)
        return EIP202_RING_ARGUMENT_ERROR;

    // Ring size cannot be smaller than one descriptor size or
    // larger than 4194303 (16MB / 4 - 1), in 32-bit words
    if(RDRSettings_p->Params.RingSizeWordCount <
       RDRSettings_p->Params.DscrOffsWordCount ||
       RDRSettings_p->Params.RingSizeWordCount > 4194303)
        return EIP202_RING_ARGUMENT_ERROR;

    if(RDRSettings_p->Params.DscrSizeWordCount >
             EIP202_RD_CTRL_DATA_MAX_WORD_COUNT + IOToken_OutWordCount_Get())
        return EIP202_RING_ARGUMENT_ERROR;

    if(RDRSettings_p->Params.DscrFetchSizeWordCount %
                            RDRSettings_p->Params.DscrOffsWordCount)
        return EIP202_RING_ARGUMENT_ERROR;

    if( RDRSettings_p->Params.IntThresholdDscrCount *
            RDRSettings_p->Params.DscrOffsWordCount >
                      RDRSettings_p->Params.RingSizeWordCount )
        return EIP202_RING_ARGUMENT_ERROR;

    // Configure the Ring Helper
    TrueIOArea_p->RingHelperCallbacks.WriteFunc_p = &EIP202_RDR_WriteCB;
    TrueIOArea_p->RingHelperCallbacks.ReadFunc_p = &EIP202_RDR_ReadCB;
    TrueIOArea_p->RingHelperCallbacks.StatusFunc_p = &EIP202_RDR_StatusCB;
    TrueIOArea_p->RingHelperCallbacks.CallbackParam1_p = IOArea_p;
    TrueIOArea_p->RingHelperCallbacks.CallbackParam2 = 0;
    TrueIOArea_p->RingHandle = RDRSettings_p->Params.RingDMA_Handle;
    TrueIOArea_p->DescOffsWordCount = RDRSettings_p->Params.DscrOffsWordCount;
    TrueIOArea_p->RingSizeWordCount = RDRSettings_p->Params.RingSizeWordCount;
    TrueIOArea_p->PacketFound = false;

    // Initialize one RingHelper instance for one RDR instance
    if( RingHelper_Init(
         (volatile RingHelper_t*)&TrueIOArea_p->RingHelper,
         (volatile RingHelper_CallbackInterface_t*)&TrueIOArea_p->RingHelperCallbacks,
         false, // One RDR as combined rings
         (unsigned int)(RDRSettings_p->Params.RingSizeWordCount /
             RDRSettings_p->Params.DscrOffsWordCount),
         (unsigned int)(RDRSettings_p->Params.RingSizeWordCount /
             RDRSettings_p->Params.DscrOffsWordCount)) < 0)
        return EIP202_RING_ARGUMENT_ERROR;

    // Transit to a new state
    rv = EIP202_RDR_State_Set((volatile EIP202_RDR_State_t*)&TrueIOArea_p->State,
                             EIP202_RDR_STATE_INITIALIZED);
    if(rv != EIP202_RING_NO_ERROR)
        return EIP202_RING_ILLEGAL_IN_STATE;

    // Prepare the RDR DMA buffer
    // Initialize all descriptors with zero for RDR
    EIP202Lib_RDR_ClearAllDescriptors(dev,
            TrueIOArea_p->RingHandle,
            RDRSettings_p->Params.DscrOffsWordCount,
            RDRSettings_p->Params.DscrSizeWordCount,
            RDRSettings_p->Params.RingSizeWordCount /
                 RDRSettings_p->Params.DscrOffsWordCount);

    // Call PreDMA to make sure engine sees it
    DMAResource_PreDMA(dev, TrueIOArea_p->RingHandle,
                       0,
                       (unsigned int)(TrueIOArea_p->RingSizeWordCount*4));

    EIP202_RDR_RING_BASE_ADDR_LO_WR(dev,
                       Device,
                       RDRSettings_p->Params.RingDMA_Address.Addr);

    EIP202_RDR_RING_BASE_ADDR_HI_WR(dev,
                       Device,
                       RDRSettings_p->Params.RingDMA_Address.UpperAddr);

    EIP202_RDR_RING_SIZE_WR(dev,
                       Device,
                       RDRSettings_p->Params.RingSizeWordCount);

    EIP202_RDR_DESC_SIZE_WR(dev,
                       Device,
                       RDRSettings_p->Params.DscrSizeWordCount,
                       RDRSettings_p->Params.DscrOffsWordCount,
                       RDRSettings_p->Params.DMA_AddressMode == EIP202_RING_64BIT_DMA_DSCR_PTR);

    EIP202_RDR_CFG_WR(dev, Device,
                      RDRSettings_p->Params.DscrFetchSizeWordCount,
                      RDRSettings_p->Params.DscrThresholdWordCount,
                      true, // Propagate Buffer and Descriptor Overflow
                            // interrupts to the RDR interrupt output
#ifdef EIP202_RDR_OWNERSHIP_WORD_ENABLE
                      true);  // Ownership write mode
#else
                      false); // Normal mode, no ownership words are written
#endif

    // Disable Processed Descriptor threshold interrupt,
    // Disable Timeout interrupt and stop timeout counter for
    // reducing power consumption
    EIP202_RDR_THRESH_WR(dev,
                       Device,
                       TrueIOArea_p->RingSizeWordCount,
                       0,  // Set descriptor processing mode
                       0); // Disable timeout

    EIP202_RDR_DMA_CFG_WR(dev,
                       Device,
                       (uint8_t)RDRSettings_p->Params.ByteSwap_Descriptor_Mask,
                       (uint8_t)RDRSettings_p->Params.ByteSwap_Packet_Mask,

                       // Bufferability control for DMA writes of
                       EIP202_RING_RD_RES_BUF,  // result token
                       EIP202_RING_RD_CTRL_BUF, // descriptor control words
                       EIP202_RING_RD_OWN_BUF,  // ownership words

                       EIP202_RING_RD_WR_CACHE_CTRL, // Write cache type control
                       EIP202_RING_RD_RD_CACHE_CTRL, // Read cache type control
                       EIP202_RING_RD_PROT_VALUE,
                       EIP202_RING_DATA_PROT_VALUE,
                       EIP202_RDR_PAD_TO_OFFSET); // Result descriptor padding

    return EIP202_RING_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP202_RDR_Reset
 *
 */
EIP202_Ring_Error_t
EIP202_RDR_Reset(cae_device *dev,
        EIP202_Ring_IOArea_t * const IOArea_p,
        const Device_Handle_t Device)
{
    EIP202_Ring_Error_t rv;
    volatile EIP202_RDR_True_IOArea_t * const TrueIOArea_p = RDRIOAREA(IOArea_p);

    EIP202_RING_CHECK_POINTER(IOArea_p);

    // Initialize the IO Area
    memset((void*)IOArea_p, 0, sizeof(*TrueIOArea_p));
    TrueIOArea_p->Device = Device;
    TrueIOArea_p->State = (unsigned int)EIP202_RDR_STATE_UNKNOWN;

    // Transit to a new state
    rv = EIP202_RDR_State_Set((volatile EIP202_RDR_State_t*)&TrueIOArea_p->State,
                             EIP202_RDR_STATE_UNINITIALIZED);
    if(rv != EIP202_RING_NO_ERROR)
        return EIP202_RING_ILLEGAL_IN_STATE;

    // Clear RDR count
    EIP202_RDR_PREP_COUNT_WR(dev, Device, 0, true);
    EIP202_RDR_PROC_COUNT_WR(dev, Device, 0, 0, true);

    // Re-init RDR
    EIP202_RDR_PREP_PNTR_DEFAULT_WR(dev, Device);
    EIP202_RDR_PROC_PNTR_DEFAULT_WR(dev, Device);

    // Restore default register values
    EIP202_RDR_RING_BASE_ADDR_LO_DEFAULT_WR(dev, Device);
    EIP202_RDR_RING_BASE_ADDR_HI_DEFAULT_WR(dev, Device);
    EIP202_RDR_RING_SIZE_DEFAULT_WR(dev, Device);
    EIP202_RDR_DESC_SIZE_DEFAULT_WR(dev, Device);
    EIP202_RDR_CFG_DEFAULT_WR(dev, Device);
    EIP202_RDR_DMA_CFG_DEFAULT_WR(dev, Device);
    EIP202_RDR_THRESH_DEFAULT_WR(dev, Device);

    // Clear and disable all RDR interrupts
    EIP202_RDR_STAT_CLEAR_ALL_IRQ_WR(dev, Device);

    return EIP202_RING_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP202_RDR_Dump
 *
 */
void
EIP202_RDR_Dump(
        EIP202_Ring_IOArea_t * const IOArea_p,
        EIP202_RingAdmin_t * const RingAdmin_p)
{
    EIP202_RDR_True_IOArea_t * const TrueIOArea_p =
                            (EIP202_RDR_True_IOArea_t * const)IOArea_p;

    if(!TrueIOArea_p)
        return;

    if(!RingAdmin_p)
        return;

    RingAdmin_p->IN_Size           = TrueIOArea_p->RingHelper.IN_Size;
    RingAdmin_p->IN_Tail           = TrueIOArea_p->RingHelper.IN_Tail;
    RingAdmin_p->OUT_Size          = TrueIOArea_p->RingHelper.OUT_Size;
    RingAdmin_p->OUT_Head          = TrueIOArea_p->RingHelper.OUT_Head;

    RingAdmin_p->fSeparate         = TrueIOArea_p->RingHelper.fSeparate;

    RingAdmin_p->DescOffsWordCount = TrueIOArea_p->DescOffsWordCount;
    RingAdmin_p->RingSizeWordCount = TrueIOArea_p->RingSizeWordCount;
}


/* end of file eip202_rdr_init.c */
