/* eip96_level0.h
 *
 * EIP-96 Packet Engine Level0 Internal interface
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

#ifndef EIP96_LEVEL0_H_
#define EIP96_LEVEL0_H_

#include <cae.h>

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // BIT definitions, bool, uint32_t

// EIP-96 Packet Engine HW interface
#include "eip96_hw_interface.h"

// Driver Framework Device API
#include "device_types.h"       // Device_Handle_t
#include "device_rw.h"          // Read32, Write32

extern uint32_t
Device_Read32(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int ByteOffset);
extern void
Device_Write32(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int ByteOffset,
        const uint32_t ValueIn);

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP96_Read32
 *
 * This routine writes to a Register location in the EIP-96.
 */
static inline uint32_t
EIP96_Read32(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int Offset)
{
    return Device_Read32(dev, Device, Offset);
}


/*----------------------------------------------------------------------------
 * EIP96_Write32
 *
 * This routine writes to a Register location in the EIP-96.
 */
static inline void
EIP96_Write32(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint32_t Value)
{
    Device_Write32(dev, Device, Offset, Value);
}


static inline void
EIP96_EIP_REV_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint8_t * const EipNumber,
        uint8_t * const ComplmtEipNumber,
        uint8_t * const HWPatchLevel,
        uint8_t * const MinHWRevision,
        uint8_t * const MajHWRevision)
{
    uint32_t RevRegVal;

    RevRegVal = EIP96_Read32(dev, Device, EIP96_REG_VERSION(PEnr));

    *MajHWRevision     = (uint8_t)((RevRegVal >> 24) & MASK_4_BITS);
    *MinHWRevision     = (uint8_t)((RevRegVal >> 20) & MASK_4_BITS);
    *HWPatchLevel      = (uint8_t)((RevRegVal >> 16) & MASK_4_BITS);
    *ComplmtEipNumber  = (uint8_t)((RevRegVal >> 8)  & MASK_8_BITS);;
    *EipNumber         = (uint8_t)((RevRegVal)       & MASK_8_BITS);
}


static inline void
EIP96_OPTIONS_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        bool * const fAES,
        bool * const fAESfb,
        bool * const fAESspeed,
        bool * const fDES,
        bool * const fDESfb,
        bool * const fDESspeed,
        uint8_t * const ARC4,
        bool * const fAES_XTS,
        bool * const fWireless,
        bool * const fMD5,
        bool * const fSHA1,
        bool * const fSHA1speed,
        bool * const fSHA224_256,
        bool * const fSHA384_512,
        bool * const fXCBC_MAC,
        bool * const fCBC_MACspeed,
        bool * const fCBC_MACkeylens,
        bool * const fGHASH)
{
    uint32_t RegVal;

    RegVal = EIP96_Read32(dev, Device, EIP96_REG_OPTIONS(PEnr));

    *fGHASH           = ((RegVal & BIT_30) != 0);
    *fCBC_MACkeylens  = ((RegVal & BIT_29) != 0);
    *fCBC_MACspeed    = ((RegVal & BIT_28) != 0);
    *fXCBC_MAC        = ((RegVal & BIT_27) != 0);
    *fSHA384_512      = ((RegVal & BIT_26) != 0);
    *fSHA224_256      = ((RegVal & BIT_25) != 0);
    *fSHA1speed       = ((RegVal & BIT_24) != 0);
    *fSHA1            = ((RegVal & BIT_23) != 0);
    *fMD5             = ((RegVal & BIT_22) != 0);
    *fWireless        = ((RegVal & BIT_21) != 0);
    *fAES_XTS         = ((RegVal & BIT_20) != 0);
    *ARC4             = (uint8_t)((RegVal >> 18) & MASK_2_BITS);
    *fDESspeed        = ((RegVal & BIT_17) != 0);
    *fDESfb           = ((RegVal & BIT_16) != 0);
    *fDES             = ((RegVal & BIT_15) != 0);
    *fAESspeed        = ((RegVal & BIT_14) != 0);
    *fAESfb           = ((RegVal & BIT_13) != 0);
    *fAES             = ((RegVal & BIT_12) != 0);
}


static inline void
EIP96_TOKEN_CTRL_STAT_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr)
{
    EIP96_Write32(dev, Device,
                  EIP96_REG_TOKEN_CTRL_STAT(PEnr),
                  EIP96_REG_TOKEN_CTRL_STAT_DEFAULT);
}


static inline void
EIP96_TOKEN_CTRL_STAT_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint8_t * const ActiveTokenCount,
        bool * const fTokenLocationAvailable,
        bool * const fResultTokenAvailable,
        bool * const fTokenReadActive,
        bool * const fContextCacheActive,
        bool * const fContextFetch,
        bool * const fResultContext,
        bool * const fProcessingHeld,
        bool * const fBusy)
{
    uint32_t RegVal;

    RegVal = EIP96_Read32(dev, Device, EIP96_REG_TOKEN_CTRL_STAT(PEnr));

    *fBusy                   = ((RegVal & BIT_15) != 0);
    *fProcessingHeld         = ((RegVal & BIT_14) != 0);
    *fResultContext          = ((RegVal & BIT_7) != 0);
    *fContextFetch           = ((RegVal & BIT_6) != 0);
    *fContextCacheActive     = ((RegVal & BIT_5) != 0);
    *fTokenReadActive        = ((RegVal & BIT_4) != 0);
    *fResultTokenAvailable   = ((RegVal & BIT_3) != 0);
    *fTokenLocationAvailable = ((RegVal & BIT_2) != 0);
    *ActiveTokenCount        = (uint8_t)((RegVal) & MASK_2_BITS);
}


static inline void
EIP96_TOKEN_CTRL_STAT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const bool fOptimalContextUpdate,
        const bool fCTNoTokenWait,
        const bool fAbsoluteARC4,
        const bool fAllowReuseCached,
        const bool fAllowPostponedReuse,
        const bool fZeroLengthResult,
        const bool fTimeoutCounterEnable,
        const bool fExtendedErrorEnable)
{
    uint32_t RegVal = EIP96_REG_TOKEN_CTRL_STAT_DEFAULT;

    if(fOptimalContextUpdate)
        RegVal |= BIT_16;

    if(fCTNoTokenWait)
        RegVal |= BIT_17;

    if(fAbsoluteARC4)
        RegVal |= BIT_18;

    if(fAllowReuseCached)
        RegVal |= BIT_19;

    if(fAllowPostponedReuse)
        RegVal |= BIT_20;

    if(fZeroLengthResult)
        RegVal |= BIT_21;

    if(fTimeoutCounterEnable)
        RegVal |= BIT_22;

    if(fExtendedErrorEnable)
        RegVal |= BIT_30;

    EIP96_Write32(dev, Device, EIP96_REG_TOKEN_CTRL_STAT(PEnr), RegVal);
}


static inline void
EIP96_TOKEN_CTRL2_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const bool fAdvFifoMode,
        const bool fPrepOvsChkDis,
        const bool fFetchOvsChkDis)
{
    uint32_t RegVal = 0;

    if (fAdvFifoMode)
        RegVal |= BIT_0;

    if (fPrepOvsChkDis)
        RegVal |= BIT_1;

    if (fFetchOvsChkDis)
        RegVal |= BIT_2;

    EIP96_Write32(dev, Device, EIP96_REG_TOKEN_CTRL2(PEnr), RegVal);
}


static inline void
EIP96_CONTEXT_STAT_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint16_t * const Error,
        uint8_t * const AvailableTokenCount,
        bool * const fActiveContext,
        bool * const fNextContext,
        bool * const fResultContext,
        bool * const fErrorRecovery)
{
    uint32_t RegVal;

    RegVal = EIP96_Read32(dev, Device, EIP96_REG_CONTEXT_STAT(PEnr));

    *fErrorRecovery          = ((RegVal & BIT_21) != 0);
    *fResultContext          = ((RegVal & BIT_20) != 0);
    *fNextContext            = ((RegVal & BIT_19) != 0);
    *fActiveContext          = ((RegVal & BIT_18) != 0);
    *AvailableTokenCount     = (uint16_t)((RegVal >> 16) & MASK_2_BITS);
    *Error                   = (uint16_t)((RegVal)       & MASK_16_BITS);
}


static inline void
EIP96_CONTEXT_CTRL_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint8_t ContextSize,
        bool fAddressMode,
        bool fControlMode)
{
    uint32_t RegVal = 0;

    if (fAddressMode)
        RegVal |= BIT_8;

    if (fControlMode)
        RegVal |= BIT_9;

    RegVal |= ContextSize & MASK_8_BITS;

    Device_Write32(dev, Device,EIP96_REG_CONTEXT_CTRL(PEnr), RegVal);
}


static inline void
EIP96_OUT_TRANS_CTRL_STAT_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint8_t * const AvailableWord32Count,
        uint8_t * const MinTransferWordCount,
        uint8_t * const MaxTransferWordCount,
        uint8_t * const TransferSizeMask)
{
    uint32_t RegVal;

    RegVal = EIP96_Read32(dev, Device, EIP96_REG_OUT_TRANS_CTRL_STAT(PEnr));

    *TransferSizeMask      = (uint8_t)((RegVal >> 24) & MASK_8_BITS);
    *MaxTransferWordCount  = (uint8_t)((RegVal >> 16) & MASK_8_BITS);
    *MinTransferWordCount  = (uint8_t)((RegVal >> 8)  & MASK_8_BITS);
    *AvailableWord32Count  = (uint8_t)((RegVal)       & MASK_8_BITS);
}


static inline void
EIP96_OUT_BUF_CTRL_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint8_t HoldOutputData,
        const bool fBlockUpdateAppend,
        const bool fLenDeltaEnable)
{
    uint32_t RegVal = EIP96_REG_OUT_BUF_CTRL_DEFAULT;

    if (fBlockUpdateAppend)
        RegVal |= BIT_31;

    if (fLenDeltaEnable)
        RegVal |= BIT_30;

    RegVal |= (uint32_t)((((uint32_t)HoldOutputData) & MASK_5_BITS) << 3);

    EIP96_Write32(dev, Device, EIP96_REG_OUT_BUF_CTRL(PEnr), RegVal);
}

static inline void
EIP96_CTX_NUM32_THR_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Threshold)
{
    EIP96_Write32(dev, Device,
                  EIP96_REG_CTX_NUM32_THR(PEnr),
                  Threshold);
}

static inline void
EIP96_CTX_NUM64_THR_L_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Threshold_L)
{
    EIP96_Write32(dev, Device,
                  EIP96_REG_CTX_NUM64_THR_L(PEnr),
                  Threshold_L);
}

static inline void
EIP96_CTX_NUM64_THR_H_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Threshold_H)
{
    EIP96_Write32(dev, Device,
                  EIP96_REG_CTX_NUM64_THR_H(PEnr),
                  Threshold_H);
}


static inline void
EIP96_PRNG_CTRL_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr)
{
    EIP96_Write32(dev, Device,
                  EIP96_REG_PRNG_CTRL(PEnr),
                  EIP96_REG_PRNG_CTRL_DEFAULT);
}


static inline void
EIP96_PRNG_CTRL_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const bool fEnable,
        const bool fAutoMode)
{
    uint32_t RegVal = EIP96_REG_PRNG_CTRL_DEFAULT;

    if(fEnable)
        RegVal |= BIT_0;

    if(fAutoMode)
        RegVal |= BIT_1;

    EIP96_Write32(dev, Device, EIP96_REG_PRNG_CTRL(PEnr), RegVal);
}


static inline void
EIP96_PRNG_STAT_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        bool * const fBusy,
        bool * const fResultReady)
{
    uint32_t RegVal;

    RegVal = EIP96_Read32(dev, Device, EIP96_REG_PRNG_STAT(PEnr));

    *fResultReady  = ((RegVal & BIT_1) != 0);
    *fBusy         = ((RegVal & BIT_0) != 0);
}


static inline void
EIP96_PRNG_SEED_L_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t SeedLo)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_SEED_L(PEnr), SeedLo);
}


static inline void
EIP96_PRNG_SEED_H_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t SeedHi)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_SEED_H(PEnr), SeedHi);
}


static inline void
EIP96_PRNG_KEY_0_L_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Key0Lo)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_KEY_0_L(PEnr), Key0Lo);
}


static inline void
EIP96_PRNG_KEY_0_H_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Key0Hi)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_KEY_0_H(PEnr), Key0Hi);
}


static inline void
EIP96_PRNG_KEY_1_L_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Key1Lo)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_KEY_1_L(PEnr), Key1Lo);
}


static inline void
EIP96_PRNG_KEY_1_H_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t Key1Hi)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_KEY_1_H(PEnr), Key1Hi);
}


static inline void
EIP96_PRNG_LFSR_L_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t LFSRLo)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_LFSR_L(PEnr), LFSRLo);
}


static inline void
EIP96_PRNG_LFSR_H_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint32_t LFSRHi)
{
    EIP96_Write32(dev, Device, EIP96_REG_PRNG_LFSR_H(PEnr), LFSRHi);
}


#endif /* EIP96_LEVEL0_H_ */


/* end of file eip96_level0.h */
