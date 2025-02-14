/* eip202_global_level0.h
 *
 * EIP-202 HIA Global Control Level0 Internal interface
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

#ifndef EIP202_GLOBAL_LEVEL0_H_
#define EIP202_GLOBAL_LEVEL0_H_

#include <cae.h>

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip97_global.h"

// EIP-292 Global Control HW interface
#include "eip202_global_hw_interface.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // BIT definitions, bool, uint32_t

// Driver Framework Device API
#include "device_types.h"       // Device_Handle_t
#include "device_rw.h"          // Read32, Write32
#include "device_swap.h"        // Device_SwapEndian32

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
 * EIP202_Set_Slave_Byte_Order_Swap_Word32
 *
 * Helper function that can be used to swap words in the body of the
 * EIP202_Set_Slave_Byte_Order() functions as well as in the other
 * functions where words require byte swap before this can be done
 * by the Packet Engine Slave interface
  */
static inline void
EIP202_Set_Slave_Byte_Order_Swap_Word32(uint32_t* const Word32)
{
#ifndef EIP97_GLOBAL_DISABLE_HOST_SWAP_INIT

    uint32_t tmp = Device_SwapEndian32(*Word32);

    *Word32 = tmp;

#else
    IDENTIFIER_NOT_USED(Word32);
#endif // !EIP97_GLOBAL_DISABLE_HOST_SWAP_INIT
}


/*----------------------------------------------------------------------------
 * EIP202 Global Functions
 *
 */

/*----------------------------------------------------------------------------
 * EIP202_Read32
 *
 * This routine writes to a Register location in the EIP-202.
 */
static inline uint32_t
EIP202_Read32(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int Offset)
{
    return Device_Read32(dev, Device, Offset);
}


/*----------------------------------------------------------------------------
 * EIP202_Write32
 *
 * This routine writes to a Register location in the EIP-202.
 */
static inline void
EIP202_Write32(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint32_t Value)
{
    Device_Write32(dev, Device, Offset, Value);
}


static inline bool
EIP202_REV_SIGNATURE_MATCH(
        const uint32_t Rev)
{
    return (((uint16_t)Rev) == EIP202_SIGNATURE);
}


static inline void
EIP202_EIP_REV_RD(cae_device *dev,
        Device_Handle_t Device,
        uint8_t * const EipNumber,
        uint8_t * const ComplmtEipNumber,
        uint8_t * const HWPatchLevel,
        uint8_t * const MinHWRevision,
        uint8_t * const MajHWRevision)
{
    uint32_t RevRegVal;

    RevRegVal = EIP202_Read32(dev, Device, EIP202_G_REG_VERSION);

    *MajHWRevision     = (uint8_t)((RevRegVal >> 24) & MASK_4_BITS);
    *MinHWRevision     = (uint8_t)((RevRegVal >> 20) & MASK_4_BITS);
    *HWPatchLevel      = (uint8_t)((RevRegVal >> 16) & MASK_4_BITS);
    *ComplmtEipNumber  = (uint8_t)((RevRegVal >> 8)  & MASK_8_BITS);
    *EipNumber         = (uint8_t)((RevRegVal)       & MASK_8_BITS);
}


static inline void
EIP202_OPTIONS_RD(cae_device *dev,
        Device_Handle_t Device,
        uint8_t * const NofRings,
        uint8_t * const NofPes,
        bool * const fExpPlf,
        uint8_t * const CF_Size,
        uint8_t * const RF_Size,
        uint8_t * const HostIfc,
        uint8_t * const DMA_Len,
        uint8_t * const HDW,
        uint8_t * const TgtAlign,
        bool * const fAddr64)
{
    uint32_t RevRegVal;

    RevRegVal = EIP202_Read32(dev, Device, EIP202_G_REG_OPTIONS);

    *fAddr64   = ((RevRegVal & BIT_31) != 0);
    *TgtAlign  = (uint8_t)((RevRegVal >> 28) & MASK_3_BITS);
    *HDW       = (uint8_t)((RevRegVal >> 25) & MASK_3_BITS);
    *DMA_Len   = (uint8_t)((RevRegVal >> 20) & MASK_5_BITS);
    *HostIfc   = (uint8_t)((RevRegVal >> 16) & MASK_4_BITS);
    *RF_Size   = (uint8_t)((RevRegVal >> 12) & MASK_4_BITS);
    *CF_Size   = (uint8_t)((RevRegVal >> 8)  & MASK_4_BITS);
    *fExpPlf   = ((RevRegVal & BIT_7) != 0);
    *NofPes    = (uint8_t)((RevRegVal >> 4)  & MASK_3_BITS);
    *NofRings  = (uint8_t)((RevRegVal)       & MASK_4_BITS);
}


static inline void
EIP202_OPTIONS2_RD(
        Device_Handle_t Device,
        uint8_t * const NofLA_Ifs,
        uint8_t * const NofIN_Ifs,
        uint8_t * const NofAXI_WrChs,
        uint8_t * const NofAXI_RdClusters,
        uint8_t * const NofAXI_RdCPC)
{
    // Not supported for this HW configuration, return zero values.
    IDENTIFIER_NOT_USED(Device);
    *NofLA_Ifs = 0;
    *NofIN_Ifs = 0;
    *NofAXI_WrChs = 0;
    *NofAXI_RdClusters = 0;
    *NofAXI_RdCPC = 0;
}


static inline void
EIP202_MST_CTRL_BUS_BURST_SIZE_GET(cae_device *dev,
        Device_Handle_t Device,
        uint8_t * const BusBurstSize)
{
    uint32_t RegVal;

    RegVal = EIP202_Read32(dev, Device, EIP202_G_REG_MST_CTRL);

    *BusBurstSize  = (uint8_t)((RegVal >> 4  ) & MASK_4_BITS);
}


static inline void
EIP202_MST_CTRL_BUS_BURST_SIZE_UPDATE(cae_device *dev,
        Device_Handle_t Device,
        const uint8_t BusBurstSize,
        const uint8_t RxBusBurstSize)
{
    uint32_t RegVal;

    // Preserve other settings
    RegVal = EIP202_Read32(dev, Device, EIP202_G_REG_MST_CTRL);

    RegVal &= ~MASK_8_BITS;

    RegVal |= (uint32_t)((((uint32_t)BusBurstSize)   & MASK_4_BITS) << 4);
    RegVal |= (uint32_t)((((uint32_t)RxBusBurstSize) & MASK_4_BITS));

    EIP202_Write32(dev, Device, EIP202_G_REG_MST_CTRL, RegVal);
}


static inline void
EIP202_MST_CTRL_BUS_TIMEOUT_UPDATE(cae_device *dev,
        Device_Handle_t Device,
        const uint8_t Timeout)
{
    uint32_t RegVal;

    // Preserve other settings
    RegVal = EIP202_Read32(dev, Device, EIP202_G_REG_MST_CTRL);

    RegVal &= ~(MASK_6_BITS << 26);

    RegVal |= (uint32_t)((((uint32_t)Timeout) & MASK_6_BITS) << 26);

    EIP202_Write32(dev, Device, EIP202_G_REG_MST_CTRL, RegVal);
}


static inline void
EIP202_MST_CTRL_BYTE_SWAP_UPDATE(cae_device *dev,
        const Device_Handle_t Device,
        const bool fByteSwap)
{
    uint32_t SlaveCfg;

    SlaveCfg = EIP202_Read32(dev, Device, EIP202_G_REG_MST_CTRL);

    // Swap the bytes for the Host endianness format (must be Big Endian)
    EIP202_Set_Slave_Byte_Order_Swap_Word32(&SlaveCfg);

    // Enable the Slave Endian Byte Swap in HW
    SlaveCfg &= ~(BIT_25 | BIT_24);
    SlaveCfg |= (fByteSwap ? BIT_24 : BIT_25);

    // Swap the bytes back for the Device endianness format (Little Endian)
    EIP202_Set_Slave_Byte_Order_Swap_Word32(&SlaveCfg);

    // Set byte order in the EIP202_G_REG_MST_CTRL register
    EIP202_Write32(dev, Device, EIP202_G_REG_MST_CTRL, SlaveCfg);
}


/*----------------------------------------------------------------------------
 * EIP202 DFE Thread Functions
 *
 */

static inline void
EIP202_DFE_CFG_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr)
{
    IDENTIFIER_NOT_USED(PEnr);
    EIP202_Write32(dev, Device,
                   EIP202_DFE_REG_CFG(PEnr),
                   EIP202_DFE_REG_CFG_DEFAULT);
}


static inline void
EIP202_DFE_CFG_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint8_t MinDataSize,
        const uint8_t DataCacheCtrl,
        const uint8_t MaxDataSize,
        const uint8_t MinCtrlSize,
        const uint8_t CtrlCacheCtrl,
        const uint8_t MaxCtrlSize,
        const bool fAdvThreshMode,
        const bool fAggressive)
{
    uint32_t RegVal = EIP202_DFE_REG_CFG_DEFAULT;

    IDENTIFIER_NOT_USED(PEnr);

    if(fAggressive)
        RegVal |= BIT_31;

    if(fAdvThreshMode)
        RegVal |= BIT_29;

    RegVal |= (uint32_t)((((uint32_t)MaxCtrlSize)   & MASK_4_BITS) << 24);
    RegVal |= (uint32_t)((((uint32_t)CtrlCacheCtrl) & MASK_3_BITS) << 20);
    RegVal |= (uint32_t)((((uint32_t)MinCtrlSize)   & MASK_4_BITS) << 16);
    RegVal |= (uint32_t)((((uint32_t)MaxDataSize)   & MASK_4_BITS) << 8);
    RegVal |= (uint32_t)((((uint32_t)DataCacheCtrl) & MASK_3_BITS) << 4);
    RegVal |= (uint32_t)((((uint32_t)MinDataSize)   & MASK_4_BITS));

    EIP202_Write32(dev, Device, EIP202_DFE_REG_CFG(PEnr), RegVal);
}


static inline void
EIP202_DFE_TRD_CTRL_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr)
{
    EIP202_Write32(dev, Device,
                   EIP202_DFE_TRD_REG_CTRL(PEnr),
                   EIP202_DFE_TRD_REG_CTRL_DEFAULT);
}


static inline void
EIP202_DFE_TRD_CTRL_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint16_t RingPEmap,
        const bool fEnable,
        const bool fReset)
{
    uint32_t RegVal = EIP202_DFE_TRD_REG_CTRL_DEFAULT;

    if(RingPEmap > 0)
        RegVal |= (((uint32_t)RingPEmap) & MASK_15_BITS);

    if(fEnable)
        RegVal |= BIT_30;

    if(fReset)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DFE_TRD_REG_CTRL(PEnr), RegVal);
}


static inline void
EIP202_DFE_TRD_CTRL_UPDATE(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PEnr,
        const uint16_t RingPEmap,
        const bool fEnable,
        const bool fReset)
{
    uint32_t RegVal;

    // Preserve other settings
    RegVal = EIP202_Read32(dev, Device, EIP202_DFE_TRD_REG_CTRL(PEnr));

    RegVal &= (~MASK_15_BITS);
    RegVal |= (((uint32_t)RingPEmap) & MASK_15_BITS);

    if(fEnable)
        RegVal |= BIT_30;
    else
        RegVal &= (~BIT_30);

    if(fReset)
        RegVal |= BIT_31;
    else
        RegVal &= (~BIT_31);

    EIP202_Write32(dev, Device, EIP202_DFE_TRD_REG_CTRL(PEnr), RegVal);
}


static inline void
EIP202_DFE_TRD_STAT_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint16_t * const CDFIFOWordCount,
        uint8_t * const CDRId,
        uint16_t * const DMAByteCount,
        bool * const fTokenDMABusy,
        bool * const fDataDMABusy,
        bool * const fDMAError)
{
    uint32_t RegVal;

    RegVal = EIP202_Read32(dev, Device, EIP202_DFE_TRD_REG_STAT(PEnr));

    *fDMAError         = ((RegVal & BIT_31) != 0);
    *fDataDMABusy      = ((RegVal & BIT_29) != 0);
    *fTokenDMABusy     = ((RegVal & BIT_28) != 0);
    *DMAByteCount      = (uint16_t)((RegVal >> 16) & MASK_12_BITS);
    *CDRId             =  (uint8_t)((RegVal >> 12) & MASK_4_BITS);
    *CDFIFOWordCount   = (uint16_t)((RegVal)       & MASK_12_BITS);
}


static inline void
EIP202_DFE_TRD_STAT_RINGID_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint8_t * const CDRId)
{
    uint32_t RegVal;

    RegVal = EIP202_Read32(dev, Device, EIP202_DFE_TRD_REG_STAT(PEnr));

    *CDRId  = (uint8_t)((RegVal >> 12) & MASK_4_BITS);
}


static inline void
EIP202_DFE_PRIO_0_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR0High,
        const bool fCDR1High,
        const bool fCDR2High,
        const bool fCDR3High)
{
    uint32_t RegVal = EIP202_DFE_REG_PRIO_0_DEFAULT;

    if(fCDR0High)
        RegVal |= BIT_7;

    if(fCDR1High)
        RegVal |= BIT_15;

    if(fCDR2High)
        RegVal |= BIT_23;

    if(fCDR3High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DFE_REG_PRIO_0, RegVal);
}


static inline void
EIP202_DFE_PRIO_1_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR4High,
        const bool fCDR5High,
        const bool fCDR6High,
        const bool fCDR7High)
{
    uint32_t RegVal = EIP202_DFE_REG_PRIO_1_DEFAULT;

    if(fCDR4High)
        RegVal |= BIT_7;

    if(fCDR5High)
        RegVal |= BIT_15;

    if(fCDR6High)
        RegVal |= BIT_23;

    if(fCDR7High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DFE_REG_PRIO_1, RegVal);
}


static inline void
EIP202_DFE_PRIO_2_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR8High,
        const bool fCDR9High,
        const bool fCDR10High,
        const bool fCDR11High)
{
    uint32_t RegVal = EIP202_DFE_REG_PRIO_2_DEFAULT;

    if(fCDR8High)
        RegVal |= BIT_7;

    if(fCDR9High)
        RegVal |= BIT_15;

    if(fCDR10High)
        RegVal |= BIT_23;

    if(fCDR11High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DFE_REG_PRIO_2, RegVal);
}


static inline void
EIP202_DFE_PRIO_3_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR12High,
        const bool fCDR13High,
        const bool fCDR14High,
        const bool fCDR15High)
{
    uint32_t RegVal = EIP202_DFE_REG_PRIO_3_DEFAULT;

    if(fCDR12High)
        RegVal |= BIT_7;

    if(fCDR13High)
        RegVal |= BIT_15;

    if(fCDR14High)
        RegVal |= BIT_23;

    if(fCDR15High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DFE_REG_PRIO_3, RegVal);
}


static inline void
EIP202_DFE_PRIO_0_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DFE_REG_PRIO_0,
                   EIP202_DFE_REG_PRIO_0_DEFAULT);
}


static inline void
EIP202_DFE_PRIO_0_VALUE32_WR(cae_device *dev,
        Device_Handle_t Device,
        const uint32_t Value)
{
    EIP202_Write32(dev, Device, EIP202_DFE_REG_PRIO_0, Value);
}


static inline uint32_t
EIP202_DFE_PRIO_0_VALUE32_RD(cae_device *dev,
        Device_Handle_t Device)
{
    return EIP202_Read32(dev, Device, EIP202_DFE_REG_PRIO_0);
}


static inline void
EIP202_DFE_PRIO_1_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DFE_REG_PRIO_1,
                   EIP202_DFE_REG_PRIO_1_DEFAULT);
}


static inline void
EIP202_DFE_PRIO_2_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DFE_REG_PRIO_2,
                   EIP202_DFE_REG_PRIO_2_DEFAULT);
}


static inline void
EIP202_DFE_PRIO_3_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DFE_REG_PRIO_3,
                   EIP202_DFE_REG_PRIO_3_DEFAULT);
}


/*----------------------------------------------------------------------------
 * EIP202 DSE Thread Functions
 *
 */

static inline void
EIP202_DSE_CFG_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr)
{
    IDENTIFIER_NOT_USED(PEnr);
    EIP202_Write32(dev, Device,
                   EIP202_DSE_REG_CFG(PEnr),
                   EIP202_DSE_REG_CFG_DEFAULT);
}


static inline void
EIP202_DSE_CFG_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint8_t MinDataSize,
        const uint8_t DataCacheCtrl,
        const uint8_t MaxDataSize,
        const uint8_t BufferCtrl,
        const bool fEnableSingleWr,
        const bool fAggressive)
{
    uint32_t RegVal = EIP202_DSE_REG_CFG_DEFAULT;

    IDENTIFIER_NOT_USED(PEnr);

    RegVal &= (~BIT_31);
    if(fAggressive)
        RegVal |= BIT_31;

    if(fEnableSingleWr)
        RegVal |= BIT_29;

    RegVal &= (uint32_t)(~(MASK_2_BITS << 14)); // Clear BufferCtrl field
    RegVal |= (uint32_t)((((uint32_t)BufferCtrl)    & MASK_2_BITS) << 14);
    RegVal |= (uint32_t)((((uint32_t)MaxDataSize)   & MASK_4_BITS) << 8);
    RegVal |= (uint32_t)((((uint32_t)DataCacheCtrl) & MASK_3_BITS) << 4);
    RegVal |= (uint32_t)((((uint32_t)MinDataSize)   & MASK_4_BITS));

    EIP202_Write32(dev, Device, EIP202_DSE_REG_CFG(PEnr), RegVal);
}


static inline void
EIP202_DSE_TRD_CTRL_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr)
{
    EIP202_Write32(dev, Device,
                   EIP202_DSE_TRD_REG_CTRL(PEnr),
                   EIP202_DSE_TRD_REG_CTRL_DEFAULT);
}


static inline void
EIP202_DSE_TRD_CTRL_WR(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        const uint16_t RingPEmap,
        const bool fEnable,
        const bool fReset)
{
    uint32_t RegVal = EIP202_DSE_TRD_REG_CTRL_DEFAULT;

    if(RingPEmap > 0)
        RegVal |= (((uint32_t)RingPEmap) & MASK_15_BITS);

    if(fEnable)
        RegVal |= BIT_30;

    if(fReset)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DSE_TRD_REG_CTRL(PEnr), RegVal);
}


static inline void
EIP202_DSE_TRD_CTRL_UPDATE(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PEnr,
        const uint16_t RingPEmap,
        const bool fEnable,
        const bool fReset)
{
    uint32_t RegVal;

    // Preserve other settings
    RegVal = EIP202_Read32(dev, Device, EIP202_DSE_TRD_REG_CTRL(PEnr));

    RegVal &= (~MASK_15_BITS);
    RegVal |= (((uint32_t)RingPEmap) & MASK_15_BITS);

    if(fEnable)
        RegVal |= BIT_30;
    else
        RegVal &= (~BIT_30);

    if(fReset)
        RegVal |= BIT_31;
    else
        RegVal &= (~BIT_31);

    EIP202_Write32(dev, Device, EIP202_DSE_TRD_REG_CTRL(PEnr), RegVal);
}


static inline void
EIP202_DSE_TRD_STAT_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint16_t * const RDFIFOWordCount,
        uint8_t * const RDRId,
        uint16_t * const DMAByteCount,
        bool * const fDataFlushBusy,
        bool * const fDataDMABusy,
        bool * const fDMAError)
{
    uint32_t RegVal;

    RegVal = EIP202_Read32(dev, Device, EIP202_DSE_TRD_REG_STAT(PEnr));

    *fDMAError         = ((RegVal & BIT_31) != 0);
    *fDataDMABusy      = ((RegVal & BIT_29) != 0);
    *fDataFlushBusy    = ((RegVal & BIT_28) != 0);
    *DMAByteCount      = (uint16_t)((RegVal >> 16) & MASK_12_BITS);
    *RDRId             =  (uint8_t)((RegVal >> 12) & MASK_4_BITS);
    *RDFIFOWordCount   = (uint16_t)((RegVal)       & MASK_12_BITS);
}


static inline void
EIP202_DSE_TRD_STAT_RINGID_RD(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int PEnr,
        uint8_t * const CDRId)
{
    uint32_t RegVal;

    RegVal = EIP202_Read32(dev, Device, EIP202_DSE_TRD_REG_STAT(PEnr));

    *CDRId = (uint8_t)((RegVal >> 12) & MASK_4_BITS);
}


static inline void
EIP202_DSE_PRIO_0_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DSE_REG_PRIO_0,
                   EIP202_DSE_REG_PRIO_0_DEFAULT);
}


static inline void
EIP202_DSE_PRIO_1_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DSE_REG_PRIO_1,
                   EIP202_DSE_REG_PRIO_1_DEFAULT);
}


static inline void
EIP202_DSE_PRIO_2_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DSE_REG_PRIO_2,
                   EIP202_DSE_REG_PRIO_2_DEFAULT);
}


static inline void
EIP202_DSE_PRIO_3_DEFAULT_WR(cae_device *dev,
        Device_Handle_t Device)
{
    EIP202_Write32(dev, Device,
                   EIP202_DSE_REG_PRIO_3,
                   EIP202_DSE_REG_PRIO_3_DEFAULT);
}


static inline void
EIP202_DSE_PRIO_0_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR0High,
        const bool fCDR1High,
        const bool fCDR2High,
        const bool fCDR3High)
{
    uint32_t RegVal = EIP202_DSE_REG_PRIO_0_DEFAULT;

    if(fCDR0High)
        RegVal |= BIT_7;

    if(fCDR1High)
        RegVal |= BIT_15;

    if(fCDR2High)
        RegVal |= BIT_23;

    if(fCDR3High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DSE_REG_PRIO_0, RegVal);
}


static inline void
EIP202_DSE_PRIO_1_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR4High,
        const bool fCDR5High,
        const bool fCDR6High,
        const bool fCDR7High)
{
    uint32_t RegVal = EIP202_DSE_REG_PRIO_1_DEFAULT;

    if(fCDR4High)
        RegVal |= BIT_7;

    if(fCDR5High)
        RegVal |= BIT_15;

    if(fCDR6High)
        RegVal |= BIT_23;

    if(fCDR7High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DSE_REG_PRIO_1, RegVal);
}


static inline void
EIP202_DSE_PRIO_2_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR8High,
        const bool fCDR9High,
        const bool fCDR10High,
        const bool fCDR11High)
{
    uint32_t RegVal = EIP202_DSE_REG_PRIO_2_DEFAULT;

    if(fCDR8High)
        RegVal |= BIT_7;

    if(fCDR9High)
        RegVal |= BIT_15;

    if(fCDR10High)
        RegVal |= BIT_23;

    if(fCDR11High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DSE_REG_PRIO_2, RegVal);
}


static inline void
EIP202_DSE_PRIO_3_WR(cae_device *dev,
        Device_Handle_t Device,
        const bool fCDR12High,
        const bool fCDR13High,
        const bool fCDR14High,
        const bool fCDR15High)
{
    uint32_t RegVal = EIP202_DSE_REG_PRIO_3_DEFAULT;

    if(fCDR12High)
        RegVal |= BIT_7;

    if(fCDR13High)
        RegVal |= BIT_15;

    if(fCDR14High)
        RegVal |= BIT_23;

    if(fCDR15High)
        RegVal |= BIT_31;

    EIP202_Write32(dev, Device, EIP202_DSE_REG_PRIO_3, RegVal);
}


#endif /* EIP202_GLOBAL_LEVEL0_H_ */


/* end of file eip202_global_level0.h */
