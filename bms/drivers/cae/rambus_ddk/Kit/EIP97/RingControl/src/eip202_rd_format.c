/* eip202_rd_format.c
 *
 * EIP-202 Ring Control Driver Library
 * Result Descriptor Internal interface
 *
 * This module contains the EIP-202 Result Descriptor specific functionality
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "eip202_rd_format.h"

// Descriptor I/O Driver Library API implementation
#include "eip202_rdr.h"                 // EIP202_ARM_CommandDescriptor_t


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip202_ring.h"

// EIP-202 Ring Control Driver Library Internal interfaces
#include "eip202_ring_internal.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"                // bool, uint32_t, uint8_t

// Driver Framework DMA Resource API
#include "dmares_types.h"              // DMAResource_Handle_t
#include "dmares_rw.h"                 // DMAResource_Write/Read

// Standard IOToken API
#include "iotoken.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP202_RD_Make_ControlWord
 */
uint32_t
EIP202_RD_Make_ControlWord(
        const uint8_t ExpectedResultWordCount,
        const uint32_t PrepSegmentByteCount,
        const bool fFirstSegment,
        const bool fLastSegment)
{
    uint32_t Value = 0;

    if(fFirstSegment)
        Value |= BIT_23;

    if(fLastSegment)
        Value |= BIT_22;

    Value |= ((((uint32_t)ExpectedResultWordCount) & MASK_8_BITS) << 24);
    Value |= ((((uint32_t)PrepSegmentByteCount)    & MASK_20_BITS));

    return Value;
}


/*----------------------------------------------------------------------------
 * EIP202_Prepared_Write
 */
void
EIP202_Prepared_Write(cae_device *dev,
        DMAResource_Handle_t Handle,
        const unsigned int WordOffset,
        const EIP202_ARM_PreparedDescriptor_t * const Descr_p)
{
#ifdef EIP202_64BIT_DEVICE
    // Write Control Word
    DMAResource_Write32(dev, Handle, WordOffset, Descr_p->PrepControlWord);

    // Do not support lengths greater than 20 bit.
    DMAResource_Write32(dev, Handle, WordOffset + 1, 0);

    // Write Destination Packet Data address
    DMAResource_Write32(dev, Handle, WordOffset + 2, Descr_p->DstPacketAddr.Addr);
    DMAResource_Write32(dev, Handle, WordOffset + 3, Descr_p->DstPacketAddr.UpperAddr);

#else
    // Write Control Word
    DMAResource_Write32(dev, Handle, WordOffset, Descr_p->PrepControlWord);

    // Write Destination Packet Data address
    DMAResource_Write32(dev, Handle, WordOffset + 1, Descr_p->DstPacketAddr.Addr);
#endif

    return;
}


/*----------------------------------------------------------------------------
 * EIP202_ReadDescriptor
 */
void
EIP202_ReadDescriptor(cae_device *dev,
        EIP202_ARM_ResultDescriptor_t * const Descr_p,
        const DMAResource_Handle_t Handle,
        const unsigned int WordOffset,
        const unsigned int DscrOffsWordCount,
        bool * const fLastSegment,
        bool * const fFirstSegment)
{
    unsigned int OutTokenWordOffset;

#ifdef EIP202_64BIT_DEVICE
    // Word 0 - Control Word
    Descr_p->ProcControlWord = DMAResource_Read32(dev, Handle, WordOffset);

    // Word 1 - extended length, not read.

    // Word 2 & 3 - Destination Packet Data Buffer Address
    Descr_p->DstPacketAddr.Addr = DMAResource_Read32(dev, Handle, WordOffset + 2);
    Descr_p->DstPacketAddr.UpperAddr = DMAResource_Read32(dev, Handle, WordOffset + 3);

    OutTokenWordOffset = WordOffset + 4;
#else // EIP202_64BIT_DEVICE
    // Word 0 - Control Word
    Descr_p->ProcControlWord = DMAResource_Read32(dev, Handle, WordOffset);

    // Word 1 - Destination Packet Data Buffer Address
    Descr_p->DstPacketAddr.Addr = DMAResource_Read32(dev, Handle, WordOffset + 1);

    OutTokenWordOffset = WordOffset + 2;
#endif // !EIP202_64BIT_DEVICE

    if (Descr_p->Token_p == NULL)
    {
        *fLastSegment   = false;
        *fFirstSegment  = false;
        return; // Fatal error
    }

    // Read token data
    {
        unsigned int i;

#ifdef EIP202_RING_ANTI_DMA_RACE_CONDITION_CDS
        for (i = 0; i < IOToken_OutWordCount_Get(); i++)
            if (i != (unsigned int)IOToken_OutMarkOffset_Get())
                Descr_p->Token_p[i] = DMAResource_Read32(dev, 
                                          Handle,
                                          OutTokenWordOffset + i);
#else
        for (i = 0; i < IOToken_OutWordCount_Get(); i++)
            Descr_p->Token_p[i] = DMAResource_Read32(dev, 
                                    Handle,
                                    OutTokenWordOffset + i);
#endif
    }

    // Check if this descriptor is for the last segment
    if((Descr_p->ProcControlWord & BIT_22) != 0)
        *fLastSegment = true; // Processed packet
    else
        *fLastSegment = false;

    // Check if this descriptor is for the first segment
    if((Descr_p->ProcControlWord & BIT_23) != 0)
        *fFirstSegment = true; // New packet descriptor chain detected
    else
        *fFirstSegment = false;

    IDENTIFIER_NOT_USED(DscrOffsWordCount);

    return;
}


/*----------------------------------------------------------------------------
 * EIP202_ClearDescriptor
 */
void
EIP202_ClearDescriptor(cae_device *dev,
        EIP202_ARM_ResultDescriptor_t * const Descr_p,
        const DMAResource_Handle_t Handle,
        const unsigned int WordOffset,
        const unsigned int DscrWordCount)
{
    IDENTIFIER_NOT_USED(Descr_p);

#if defined(EIP202_RDR_OWNERSHIP_WORD_ENABLE)

    DMAResource_Write32(dev, Handle, WordOffset + DscrWordCount - 1, 0);

#elif defined(EIP202_RING_ANTI_DMA_RACE_CONDITION_CDS)

    IDENTIFIER_NOT_USED(DscrWordCount);

    DMAResource_Write32(dev, Handle,
                        WordOffset + EIP202_RD_CTRL_DATA_MAX_WORD_COUNT +
                                                 IOToken_OutMarkOffset_Get(),
                        0);
#else
    IDENTIFIER_NOT_USED(Handle);
    IDENTIFIER_NOT_USED(WordOffset);
    IDENTIFIER_NOT_USED(DscrWordCount);
#endif // !EIP202_RDR_OWNERSHIP_WORD_ENABLE
}


/*----------------------------------------------------------------------------
 * EIP202_RD_Read_ControlWord
 */
void
EIP202_RD_Read_ControlWord(
        const uint32_t ControlWord,
        uint32_t * TokenData_p,
        EIP202_RDR_Result_Control_t * const RDControl_p,
        EIP202_RDR_Result_Token_t * const ResToken_p)
{
    RDControl_p->ProcSegmentByteCount =  (ControlWord        & MASK_20_BITS);
    RDControl_p->ProcResultWordCount  = ((ControlWord >> 24) & MASK_8_BITS);

    // Fill in EIP202_RDR_Result_Control_t
    if((ControlWord & BIT_20) != 0)
        RDControl_p->fDscrOverflow = true;
    else
        RDControl_p->fDscrOverflow = false;

    if((ControlWord & BIT_21) != 0)
        RDControl_p->fBufferOverflow = true;
    else
        RDControl_p->fBufferOverflow = false;

    if((ControlWord & BIT_22) != 0)
        RDControl_p->fLastSegment = true;
    else
        RDControl_p->fLastSegment = false;

    if((ControlWord & BIT_23) != 0)
        RDControl_p->fFirstSegment = true;
    else
        RDControl_p->fFirstSegment = false;

    IDENTIFIER_NOT_USED(TokenData_p);
    IDENTIFIER_NOT_USED(ResToken_p);
}


/*----------------------------------------------------------------------------
 * EIP202_RD_Read_BypassData
 */
void
EIP202_RD_Read_BypassData(
        const uint32_t * BypassData_p,
        const uint8_t BypassWordCount,
        EIP202_RDR_BypassData_t * const BD_p)
{
    if (BypassWordCount == 1)
    {
        BD_p->Fail.ErrorFlags = BypassData_p[0] & MASK_2_BITS;
    }
    else if (BypassWordCount == 2)
    {
        BD_p->Pass.TOS_TC           = BypassData_p[0] & MASK_8_BITS;
        BD_p->Pass.fDF              = ((BypassData_p[0] & BIT_8) != 0);
        BD_p->Pass.NextHeaderOffset = (BypassData_p[0] >> 8) & MASK_16_BITS;
        BD_p->Pass.HdrProcCtxRef    = BypassData_p[1];
    }
    else
    {
        IDENTIFIER_NOT_USED(BypassData_p);
        IDENTIFIER_NOT_USED(BypassWordCount);
        IDENTIFIER_NOT_USED(BD_p);
    }
}


/* end of file eip202_rd_format.c */
