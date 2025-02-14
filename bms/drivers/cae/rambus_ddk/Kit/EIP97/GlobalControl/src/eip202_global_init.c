/* eip202_global_init.c
 *
 * EIP-202 Global Control Driver Library
 * Initialization Module
 */

/*****************************************************************************
* Copyright (c) 2016-2020 by Rambus, Inc. and/or its subsidiaries.
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

#include "eip202_global_init.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip97_global.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"             // uint32_t

// Driver Framework C Run-time Library API
#include "clib.h"                   // ZEROINIT

// Driver Framework Device API
#include "device_types.h"           // Device_Handle_t

#include "eip202_global_level0.h"   // EIP-202 Level 0 macros


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP202_Global_Detect
 *
 * Checks the presence of EIP-202 HIA hardware. Returns true when found.
 */
bool
EIP202_Global_Detect(cae_device *dev,
        const Device_Handle_t Device)
{
    uint32_t Value;

    Value = EIP202_Read32(dev, Device, EIP202_G_REG_VERSION);
    if (!EIP202_REV_SIGNATURE_MATCH( Value ))
        return false;

    // read-write test one of the registers

    // Set MASK_4_BITS bits of the EIP202_DFE_REG_PRIO_0 register
    EIP202_DFE_PRIO_0_VALUE32_WR(dev, Device, 0x8F8F);
    Value = EIP202_DFE_PRIO_0_VALUE32_RD(dev, Device);
    if ((Value & MASK_4_BITS) != MASK_4_BITS)
        return false;

    // Clear MASK_4_BITS bits of the EIP202_DFE_REG_PRIO_0 register
    EIP202_DFE_PRIO_0_VALUE32_WR(dev, Device, 0);
    Value = EIP202_DFE_PRIO_0_VALUE32_RD(dev, Device);
    if ((Value & MASK_4_BITS) != 0)
       return false;

    return true;
}




/*----------------------------------------------------------------------------
 * EIP202_Global_HWRevision_Get
 */
void
EIP202_Global_HWRevision_Get(cae_device *dev,
        const Device_Handle_t Device,
        EIP202_Capabilities_t * const Capabilities_p)
{
    EIP202_EIP_REV_RD(dev, Device,
                      &Capabilities_p->EipNumber,
                      &Capabilities_p->ComplmtEipNumber,
                      &Capabilities_p->HWPatchLevel,
                      &Capabilities_p->MinHWRevision,
                      &Capabilities_p->MajHWRevision);

    EIP202_OPTIONS_RD(dev, Device,
                      &Capabilities_p->NofRings,
                      &Capabilities_p->NofPes,
                      &Capabilities_p->fExpPlf,
                      &Capabilities_p->CF_Size,
                      &Capabilities_p->RF_Size,
                      &Capabilities_p->HostIfc,
                      &Capabilities_p->DMA_Len,
                      &Capabilities_p->HDW,
                      &Capabilities_p->TgtAlign,
                      &Capabilities_p->fAddr64);

    EIP202_OPTIONS2_RD(Device,
                       &Capabilities_p->NofLA_Ifs,
                       &Capabilities_p->NofIN_Ifs,
                       &Capabilities_p->NofAXI_WrChs,
                       &Capabilities_p->NofAXI_RdClusters,
                       &Capabilities_p->NofAXI_RdCPC);
}


/*----------------------------------------------------------------------------
 * EIP202_Global_Endianness_Slave_Configure
 */
bool
EIP202_Global_Endianness_Slave_Configure(cae_device *dev,
        const Device_Handle_t Device)
{
#ifdef EIP97_GLOBAL_ENABLE_SWAP_REG_DATA
    uint32_t Value;

    // Read and check the revision register
    Value = EIP202_Read32(dev, Device, EIP202_G_REG_VERSION);
    if (!EIP202_REV_SIGNATURE_MATCH( Value ))
    {
        // No match, try to enable the Slave interface byte swap
        // Must be done via EIP-202 HIA Global
        EIP202_MST_CTRL_BYTE_SWAP_UPDATE(Device, true);

        // Read and check the revision register again
        Value = EIP202_Read32(dev, Device, EIP202_G_REG_VERSION);
        if (!EIP202_REV_SIGNATURE_MATCH( Value ))
            // Bail out if still not OK
            return false;
    }

    return true;
#else
    IDENTIFIER_NOT_USED(Device);
    return true;
#endif // EIP97_GLOBAL_ENABLE_SWAP_REG_DATA
}


/*----------------------------------------------------------------------------
 * EIP202_Global_Init
 */
void
EIP202_Global_Init(cae_device *dev,
        const Device_Handle_t Device,
        unsigned int NofPE,
        unsigned int NofLA,
        uint8_t ipbuf_min,
        uint8_t ipbuf_max,
        uint8_t itbuf_min,
        uint8_t itbuf_max,
        uint8_t opbuf_min,
        uint8_t opbuf_max)
{
    unsigned int i;
    uint8_t BufferCtrl;
    // Configure EIP-202 HIA Global
    EIP202_MST_CTRL_BUS_BURST_SIZE_UPDATE(dev, Device,
                                          EIP97_GLOBAL_BUS_BURST_SIZE,
                                          EIP97_GLOBAL_RX_BUS_BURST_SIZE);
    EIP202_MST_CTRL_BUS_TIMEOUT_UPDATE(dev, Device,
                                       EIP97_GLOBAL_TIMEOUT_VALUE);
    if (NofLA)
        // User-configured value
        BufferCtrl = EIP97_GLOBAL_DSE_BUFFER_CTRL;
    else
        // Default register reset value
        BufferCtrl = (uint8_t)EIP202_DSE_BUFFER_CTRL;

    for (i = 0; i < NofPE; i++)
    {
        // Configure EIP-202 HIA DFE Global
        EIP202_DFE_CFG_WR(dev, Device,
                          i,
                          ipbuf_min,
                          EIP97_GLOBAL_DFE_DATA_CACHE_CTRL,
                          ipbuf_max,
                          itbuf_min,
                          EIP97_GLOBAL_DFE_CTRL_CACHE_CTRL,
                          itbuf_max,
                          (EIP97_GLOBAL_DFE_ADV_THRESH_MODE_FLAG == 1),
                          (EIP97_GLOBAL_DFE_AGGRESSIVE_DMA_FLAG == 1));

        // Configure EIP-202 HIA DSE Global
        EIP202_DSE_CFG_WR(dev, Device,
                          i,
                          opbuf_min,
                          EIP97_GLOBAL_DSE_DATA_CACHE_CTRL,
                          opbuf_max,
                          BufferCtrl,
                          (EIP97_GLOBAL_DSE_ENABLE_SINGLE_WR_FLAG == 1),
                          (EIP97_GLOBAL_DSE_AGGRESSIVE_DMA_FLAG == 1));

    }
}


/*----------------------------------------------------------------------------
 * EIP202_Global_Reset
 */
bool
EIP202_Global_Reset(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int NofPE)
{
    unsigned int i;

    // Restore the EIP-202 default configuration
    // Resets DFE thread and clears ring assignment
    for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
        EIP202_DFE_TRD_CTRL_WR(dev, Device, i, 0, false, true);

    // HIA DFE defaults
    for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
        EIP202_DFE_CFG_DEFAULT_WR(dev, Device, i);

    EIP202_DFE_PRIO_0_DEFAULT_WR(dev, Device);
    EIP202_DFE_PRIO_1_DEFAULT_WR(dev, Device);
    EIP202_DFE_PRIO_2_DEFAULT_WR(dev, Device);
    EIP202_DFE_PRIO_3_DEFAULT_WR(dev, Device);


    // Resets DSE thread and clears ring assignment
    for (i = 0; i < NofPE; i++)
        EIP202_DSE_TRD_CTRL_WR(dev, Device, i, 0, false, true);

    // HIA DSE defaults
    for (i = 0; i < NofPE; i++)
        EIP202_DSE_CFG_DEFAULT_WR(dev, Device, i);


    EIP202_DSE_PRIO_0_DEFAULT_WR(dev, Device);
    EIP202_DSE_PRIO_1_DEFAULT_WR(dev, Device);
    EIP202_DSE_PRIO_2_DEFAULT_WR(dev, Device);
    EIP202_DSE_PRIO_3_DEFAULT_WR(dev, Device);

    return true;
}


/*----------------------------------------------------------------------------
 * EIP202_Global_Reset_IsDone
 */
bool
EIP202_Global_Reset_IsDone(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PEnr)
{
    uint8_t RingId;

    // Check for completion of all DMA transfers
    EIP202_DFE_TRD_STAT_RINGID_RD(dev, Device, PEnr, &RingId);
    if(RingId == EIP202_DFE_TRD_REG_STAT_IDLE)
    {
        EIP202_DSE_TRD_STAT_RINGID_RD(dev, Device, PEnr, &RingId);
        if(RingId == EIP202_DFE_TRD_REG_STAT_IDLE)
        {
            // Take DFE thread out of reset
            EIP202_DFE_TRD_CTRL_DEFAULT_WR(dev, Device, PEnr);

            // Take DSE thread out of reset
            EIP202_DSE_TRD_CTRL_DEFAULT_WR(dev, Device, PEnr);

            // Do not restore the EIP-202 Master Control default configuration
            // so this will not change the endianness conversion configuration
            // for the Slave interface
        }
        return true;
    }
    else
    {
        return false;
    }
}


/*----------------------------------------------------------------------------
 * EIP202_Global_Configure
 */
void
EIP202_Global_Configure(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PE_Number,
        const EIP202_Global_Ring_PE_Map_t * const RingPEMap_p)
{
    // Disable EIP-202 HIA DFE thread(s)
    EIP202_DFE_TRD_CTRL_WR(dev, Device,
                           PE_Number,   // Thread Nr
                           0,
                           false,       // Disable thread
                           false);      // Do not reset thread

    // Disable EIP-202 HIA DSE thread(s)
    EIP202_DSE_TRD_CTRL_WR(dev, Device,
                           PE_Number,   // Thread Nr
                           0,
                           false,       // Disable thread
                           false);      // Do not reset thread

    // Configure DFE ring priorities
    EIP202_DFE_PRIO_0_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_0) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_1) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_2) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_3) == 0 ? false : true);

    EIP202_DFE_PRIO_1_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_4) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_5) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_6) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_7) == 0 ? false : true);

    EIP202_DFE_PRIO_2_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_8) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_9) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_10) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_11) == 0 ? false : true);

    EIP202_DFE_PRIO_3_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_12) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_13) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_14) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_15) == 0 ? false : true);

    // Configure DSE ring priorities
    EIP202_DSE_PRIO_0_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_0) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_1) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_2) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_3) == 0 ? false : true);

    EIP202_DSE_PRIO_1_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_4) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_5) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_6) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_7) == 0 ? false : true);

    EIP202_DSE_PRIO_2_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_8) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_9) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_10) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_11) == 0 ? false : true);

    EIP202_DSE_PRIO_3_WR(dev,
            Device,
            (RingPEMap_p->RingPrio_Mask & BIT_12) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_13) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_14) == 0 ? false : true,
            (RingPEMap_p->RingPrio_Mask & BIT_15) == 0 ? false : true);


    {
        // Assign Rings to this DFE thread
        // Enable EIP-202 HIA DFE thread(s)
        EIP202_DFE_TRD_CTRL_WR(dev, Device,
                               PE_Number,   // Thread Nr
                               RingPEMap_p->RingPE_Mask,  // Rings to assign
                               true,        // Enable thread
                               false);      // Do not reset thread

        // Assign Rings to this DSE thread
        // Enable EIP-202 HIA DSE thread(s)
        EIP202_DSE_TRD_CTRL_WR(dev, Device,
                               PE_Number,   // Thread Nr
                               RingPEMap_p->RingPE_Mask,   // Rings to assign
                               true,        // Enable thread
                               false);      // Do not reset thread
    }
}

/* end of file eip202_global_init.c */
