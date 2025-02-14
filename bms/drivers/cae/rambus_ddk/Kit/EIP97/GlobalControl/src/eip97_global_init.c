/* eip97_global_init.c
 *
 * EIP-97 Global Control Driver Library
 * Initialization Module
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

#include "eip97_global_init.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip97_global.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"             // uint32_t

// Driver Framework C Run-time Library API
#include "clib.h"                       // ZEROINIT

// Driver Framework Device API
#include "device_types.h"           // Device_Handle_t

// EIP-97 Global Control Driver Library Internal interfaces
#include "eip97_global_internal.h"
#include "eip97_global_level0.h"       // EIP-97 Level 0 macros
#include "eip202_global_init.h"        // EIP-202 Initialization code
#include "eip206_level0.h"             // EIP-206 Level 0 macros
#include "eip96_level0.h"              // EIP-96 Level 0 macros
#include "eip97_global_fsm.h"          // State machine


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Maximum number of Packet Engines that should be used
// Driver Library will check the maximum number supported run-time
#ifndef EIP97_GLOBAL_MAX_NOF_PE_TO_USE
#error "EIP97_GLOBAL_MAX_NOF_PE_TO_USE is not defined"
#endif

// Number of Ring interfaces
// Maximum number of Ring interfaces that should be used
// Driver Library will check the maximum number supported run-time
#ifndef EIP97_GLOBAL_MAX_NOF_RING_TO_USE
#error "EIP97_GLOBAL_MAX_NOF_RING_TO_USE is not defined"
#endif


/*----------------------------------------------------------------------------
 * Local variables
 */



/*----------------------------------------------------------------------------
 * EIP206Lib_Detect
 *
 * Checks the presence of EIP-206 PE hardware. Returns true when found.
 */
static bool
EIP206Lib_Detect(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PEnr)
{
    uint32_t Value;

    // No revision register for this HW version

    // read-write test one of the registers

    // Set MASK_8_BITS bits of the EIP206_OUT_REG_DBUF_TRESH register
    EIP206_Write32(dev, Device,
                   EIP206_OUT_REG_DBUF_TRESH(PEnr),
                   MASK_8_BITS);
    Value = EIP206_Read32(dev, Device,
                          EIP206_OUT_REG_DBUF_TRESH(PEnr));
    if ((Value & MASK_8_BITS) != MASK_8_BITS)
        return false;

    // Clear MASK_8_BITS bits of the EIP206_OUT_REG_DBUF_TRESH(PEnr) register
    EIP206_Write32(dev, Device, EIP206_OUT_REG_DBUF_TRESH(PEnr), 0);
    Value = EIP206_Read32(dev, Device, EIP206_OUT_REG_DBUF_TRESH(PEnr));
    if ((Value & MASK_8_BITS) != 0)
       return false;

    return true;
}


/*----------------------------------------------------------------------------
 * EIP96Lib_Detect
 *
 * Checks the presence of EIP-96 Engine hardware. Returns true when found.
 */
static bool
EIP96Lib_Detect(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PEnr)
{
    uint32_t Value, DefaultValue;
    bool fSuccess = true;

    // No revision register for this HW version

    // Save the default register value
    DefaultValue = EIP96_Read32(dev, Device,
                                EIP96_REG_CONTEXT_CTRL(PEnr));

    // read-write test one of the registers

    // Set MASK_6_BITS bits of the EIP96_REG_CONTEXT_CTRL register
    EIP96_Write32(dev, Device,
                  EIP96_REG_CONTEXT_CTRL(PEnr),
                  MASK_6_BITS );
    Value = EIP96_Read32(dev, Device, EIP96_REG_CONTEXT_CTRL(PEnr));
    if ((Value & MASK_6_BITS) != MASK_6_BITS)
        fSuccess = false;

    if( fSuccess )
    {
        // Clear MASK_6_BITS bits of the EIP96_REG_CONTEXT_CTRL register
        EIP96_Write32(dev, Device, EIP96_REG_CONTEXT_CTRL(PEnr), 0);
        Value = EIP96_Read32(dev, Device, EIP96_REG_CONTEXT_CTRL(PEnr));
        if ((Value & MASK_6_BITS) != 0)
            fSuccess = false;
    }

    // Restore the default register value
    EIP96_Write32(dev, Device,
            EIP96_REG_CONTEXT_CTRL(PEnr),
                  DefaultValue );
    return fSuccess;
}


/*----------------------------------------------------------------------------
 * EIP97Lib_Detect
 *
 * Checks the presence of EIP-97 Engine hardware. Returns true when found.
 */
static bool
EIP97Lib_Detect(
        const Device_Handle_t Device)
{
#ifdef EIP97_GLOBAL_VERSION_CHECK_ENABLE
    uint32_t Value;

    // read and check the revision register
    Value = EIP97_Read32(Device, EIP97_REG_VERSION);
    if (!EIP97_REV_SIGNATURE_MATCH( Value ))
        return false;
#else
    IDENTIFIER_NOT_USED(Device);
#endif // EIP97_GLOBAL_VERSION_CHECK_ENABLE

    return true;
}


/*----------------------------------------------------------------------------
 * EIP202Lib_HWRevision_Get
 */
static void
EIP202Lib_HWRevision_Get(cae_device *dev,
        const Device_Handle_t Device,
        EIP202_Options_t * const Options_p,
        EIP202_Options2_t * const Options2_p,
        EIP_Version_t * const Version_p)
{
    EIP202_Capabilities_t EIP202_Capabilities;
    EIP202_Global_HWRevision_Get(dev, Device, &EIP202_Capabilities);

    Version_p->EipNumber = EIP202_Capabilities.EipNumber;
    Version_p->ComplmtEipNumber = EIP202_Capabilities.ComplmtEipNumber;
    Version_p->HWPatchLevel = EIP202_Capabilities.HWPatchLevel;
    Version_p->MinHWRevision = EIP202_Capabilities.MinHWRevision;
    Version_p->MajHWRevision = EIP202_Capabilities.MajHWRevision;

    Options_p->NofRings = EIP202_Capabilities.NofRings;
    Options_p->NofPes = EIP202_Capabilities.NofPes;
    Options_p->fExpPlf = EIP202_Capabilities.fExpPlf;
    Options_p->CF_Size = EIP202_Capabilities.CF_Size;
    Options_p->RF_Size = EIP202_Capabilities.RF_Size;
    Options_p->HostIfc = EIP202_Capabilities.HostIfc;
    Options_p->DMA_Len = EIP202_Capabilities.DMA_Len;
    Options_p->HDW = EIP202_Capabilities.HDW;
    Options_p->TgtAlign = EIP202_Capabilities.TgtAlign;
    Options_p->fAddr64 = EIP202_Capabilities.fAddr64;

    Options2_p->NofLA_Ifs = EIP202_Capabilities.NofLA_Ifs;
    Options2_p->NofIN_Ifs = EIP202_Capabilities.NofIN_Ifs;
    Options2_p->NofAXI_WrChs = EIP202_Capabilities.NofAXI_WrChs;
    Options2_p->NofAXI_RdClusters = EIP202_Capabilities.NofAXI_RdClusters;
    Options2_p->NofAXI_RdCPC = EIP202_Capabilities.NofAXI_RdCPC;

}


/*----------------------------------------------------------------------------
 * EIP96Lib_HWRevision_Get
 */
static void
EIP96Lib_HWRevision_Get(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int PEnr,
        EIP96_Options_t * const Options_p,
        EIP_Version_t * const Version_p)
{
    EIP96_EIP_REV_RD(dev, Device,
                     PEnr,
                     &Version_p->EipNumber,
                     &Version_p->ComplmtEipNumber,
                     &Version_p->HWPatchLevel,
                     &Version_p->MinHWRevision,
                     &Version_p->MajHWRevision);

    EIP96_OPTIONS_RD(dev, Device,
                     PEnr,
                     &Options_p->fAES,
                     &Options_p->fAESfb,
                     &Options_p->fAESspeed,
                     &Options_p->fDES,
                     &Options_p->fDESfb,
                     &Options_p->fDESspeed,
                     &Options_p->ARC4,
                     &Options_p->fAES_XTS,
                     &Options_p->fWireless,
                     &Options_p->fMD5,
                     &Options_p->fSHA1,
                     &Options_p->fSHA1speed,
                     &Options_p->fSHA224_256,
                     &Options_p->fSHA384_512,
                     &Options_p->fXCBC_MAC,
                     &Options_p->fCBC_MACspeed,
                     &Options_p->fCBC_MACkeylens,
                     &Options_p->fGHASH);
}


/*----------------------------------------------------------------------------
 * EIP97Lib_HWRevision_Get
 */
static void
EIP97Lib_HWRevision_Get(cae_device *dev,
        const Device_Handle_t Device,
        EIP97_Options_t * const Options_p,
        EIP_Version_t * const Version_p)
{
    EIP97_EIP_REV_RD(dev, Device,
                     &Version_p->EipNumber,
                     &Version_p->ComplmtEipNumber,
                     &Version_p->HWPatchLevel,
                     &Version_p->MinHWRevision,
                     &Version_p->MajHWRevision);

    EIP97_OPTIONS_RD(dev, Device,
                     &Options_p->NofPes,
                     &Options_p->in_tbuf_size,
                     &Options_p->in_dbuf_size,
                     &Options_p->out_tbuf_size,
                     &Options_p->out_dbuf_size,
                     &Options_p->central_prng,
                     &Options_p->tg,
                     &Options_p->trc);
}


/*----------------------------------------------------------------------------
 * EIP97Lib_Reset_IsDone
 */
static EIP97_Global_Error_t
EIP97Lib_Reset_IsDone(cae_device *dev,
        const Device_Handle_t Device,
        volatile uint32_t * State_p,
        const unsigned int PEnr)
{
    bool fResetDone = EIP202_Global_Reset_IsDone(dev, Device, PEnr);

    if(fResetDone)
    {
        // Transit to a new state
#ifdef EIP97_GLOBAL_DEBUG_FSM
        {
            EIP97_Global_Error_t rv;

            rv = EIP97_Global_State_Set((volatile EIP97_Global_State_t*)State_p,
                                        EIP97_GLOBAL_STATE_SW_RESET_DONE);
            if(rv != EIP97_GLOBAL_NO_ERROR)
                return EIP97_GLOBAL_ILLEGAL_IN_STATE;
        }
#endif // EIP97_GLOBAL_DEBUG_FSM
    }
    else
    {
#ifdef EIP97_GLOBAL_DEBUG_FSM
        {
            EIP97_Global_Error_t rv;

            // SW Reset is ongoing, retry later
            rv = EIP97_Global_State_Set((volatile EIP97_Global_State_t*)State_p,
                                        EIP97_GLOBAL_STATE_SW_RESET_START);
            if(rv != EIP97_GLOBAL_NO_ERROR)
                return EIP97_GLOBAL_ILLEGAL_IN_STATE;
        }
#endif // EIP97_GLOBAL_DEBUG_FSM

        return EIP97_GLOBAL_BUSY_RETRY_LATER;
    }

    return EIP97_GLOBAL_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP97_Global_Init
 */
EIP97_Global_Error_t
EIP97_Global_Init(cae_device *dev,
        EIP97_Global_IOArea_t * const IOArea_p,
        const Device_Handle_t Device)
{
    unsigned int i;
    EIP97_Global_Capabilities_t Capabilities;
    volatile EIP97_True_IOArea_t * const TrueIOArea_p = IOAREA(IOArea_p);

    ZEROINIT(Capabilities);

    EIP97_GLOBAL_CHECK_POINTER(IOArea_p);

    // Attempt to initialize slave byte swapping.
    if (!EIP202_Global_Endianness_Slave_Configure(dev, Device))
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;

    // Detect presence of the EIP-97 HW hardware
    if (!EIP202_Global_Detect(dev, Device) ||
        !EIP206Lib_Detect(dev, Device, PE_DEFAULT_NR) ||
        !EIP96Lib_Detect(dev, Device, PE_DEFAULT_NR) ||
        !EIP97Lib_Detect(Device))
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;

    // Initialize the IO Area
    TrueIOArea_p->Device = Device;
    // Can also be EIP97_GLOBAL_STATE_HW_RESET_DONE
    TrueIOArea_p->State = (uint32_t)EIP97_GLOBAL_STATE_SW_RESET_DONE;

    EIP97Lib_HWRevision_Get(dev, Device,
                            &Capabilities.EIP97_Options,
                            &Capabilities.EIP97_Version);

    EIP202Lib_HWRevision_Get(dev, Device,
                             &Capabilities.EIP202_Options,
                             &Capabilities.EIP202_Options2,
                             &Capabilities.EIP202_Version);

    EIP96Lib_HWRevision_Get(dev, Device,
                            PE_DEFAULT_NR,
                            &Capabilities.EIP96_Options,
                            &Capabilities.EIP96_Version);

    // Check actual configuration HW against capabilities
    // Number of configured PE's
    if(Capabilities.EIP202_Options.NofPes < EIP97_GLOBAL_MAX_NOF_PE_TO_USE)
        return false;

    // Number of configure ring interfaces
    if(Capabilities.EIP202_Options.NofRings < EIP97_GLOBAL_MAX_NOF_RING_TO_USE)
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;

#if EIP97_GLOBAL_MAX_NOF_LAFIFO_TO_USE>0
    // Number of configured Look-aside FIFO interfaces
    if(Capabilities.EIP202_Options2.NofLA_Ifs <
                        EIP97_GLOBAL_MAX_NOF_LAFIFO_TO_USE)
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;
#endif
#if EIP97_GLOBAL_MAX_NOF_INFIFO_TO_USE
    // Number of configured Inline FIFO interfaces
    if(Capabilities.EIP202_Options2.NofIN_Ifs <
                       EIP97_GLOBAL_MAX_NOF_INFIFO_TO_USE)
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;
#endif

#ifdef EIP97_GLOBAL_DEBUG_FSM
        {
            EIP97_Global_Error_t rv;

            // Transit to a new state
            rv = EIP97_Global_State_Set(
                    (volatile EIP97_Global_State_t*)&TrueIOArea_p->State,
                    EIP97_GLOBAL_STATE_INITIALIZED);
            if(rv != EIP97_GLOBAL_NO_ERROR)
                return EIP97_GLOBAL_ILLEGAL_IN_STATE;
        }
#endif // EIP97_GLOBAL_DEBUG_FSM

    // Configure Endianness Conversion method for master (DMA) interface
    for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
        EIP97_MST_CTRL_WR(dev, Device,
                          i,
                          EIP97_GLOBAL_RD_CACHE_VALUE,
                          EIP97_GLOBAL_WR_CACHE_VALUE,
                          EIP97_GLOBAL_BYTE_SWAP_METHOD,
                          EIP97_GLOBAL_SUPPORT_PROTECT_VALUE);
    {
        uint8_t ipbuf_max, ipbuf_min,
                itbuf_max, itbuf_min,
                opbuf_max, opbuf_min;

#ifdef EIP97_GLOBAL_THRESH_CONFIG_AUTO
        // Calculate the EIP-202 and EIP-206 Global Control thresholds
        uint8_t dmalen;

        // Convert to powers of byte counts from powers of 32-bit word counts
        ipbuf_max = Capabilities.EIP97_Options.in_dbuf_size + 2;
        itbuf_max = Capabilities.EIP97_Options.in_tbuf_size + 2;
        opbuf_max = Capabilities.EIP97_Options.out_dbuf_size + 2;

        // EIP-96 token cannot be larger than 2^7 bytes
        if( itbuf_max > EIP97_GLOBAL_MAX_TOKEN_SIZE )
            itbuf_max = EIP97_GLOBAL_MAX_TOKEN_SIZE;

        // DMA_Len is power of byte count
        if (Capabilities.EIP202_Options.DMA_Len >= 1)
            dmalen = Capabilities.EIP202_Options.DMA_Len - 1;
        else
            dmalen = Capabilities.EIP202_Options.DMA_Len;

        ipbuf_max = MIN(ipbuf_max, dmalen);
        itbuf_max = MIN(itbuf_max, dmalen);
        opbuf_max = MIN(opbuf_max, dmalen);

        ipbuf_min = ipbuf_max - 1;
        itbuf_min = itbuf_max - 1;
        opbuf_min = opbuf_max - 1;
#else
        // Use configured statically
        // the EIP-202 and EIP-206 Global Control thresholds
        ipbuf_min = EIP97_GLOBAL_DFE_MIN_DATA_XFER_SIZE;
        ipbuf_max = EIP97_GLOBAL_DFE_MAX_DATA_XFER_SIZE;

        itbuf_min = EIP97_GLOBAL_DFE_MIN_TOKEN_XFER_SIZE;
        itbuf_max = EIP97_GLOBAL_DFE_MAX_TOKEN_XFER_SIZE;

        opbuf_min = EIP97_GLOBAL_DSE_MIN_DATA_XFER_SIZE;
        opbuf_max = EIP97_GLOBAL_DSE_MAX_DATA_XFER_SIZE;
#endif


        EIP202_Global_Init(dev, Device,
                           EIP97_GLOBAL_MAX_NOF_PE_TO_USE,
                           Capabilities.EIP202_Options2.NofLA_Ifs,
                           ipbuf_min,
                           ipbuf_max,
                           itbuf_min,
                           itbuf_max,
                           opbuf_min,
                           opbuf_max);
        for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
        {

            // Configure EIP-206 Processing Engine
            EIP206_IN_DBUF_THRESH_WR(dev,
                            Device,
                            i,
                            0,
                            ipbuf_min,
                            ipbuf_max); // ... or use 0xF for maximum, autoconf

            EIP206_IN_TBUF_THRESH_WR(dev,
                            Device,
                            i,
                            14,
                            itbuf_min,
                            itbuf_max); // ... or use 0xF for maximum, autoconf

            EIP206_OUT_DBUF_THRESH_WR(dev,
                            Device,
                            i,
                            opbuf_min,
                            opbuf_max); // ... or use 0xF for maximum, autoconf

            // Configure EIP-96 Packet Engine
            EIP96_TOKEN_CTRL_STAT_WR(dev,
                    Device,
                    i,
                    true, /* optimal context update */
                    false, /* CT No token wait */
                    false, /* Absulute ARC4 pointer */
                    false, /* Allow reuse cached context */
                    false, /* Allow postponed reuse */
                    false, /* Zero length result */
                    (EIP97_GLOBAL_EIP96_TIMEOUT_CNTR_FLAG == 0) ? false : true,
                    (EIP97_GLOBAL_EIP96_EXTENDED_ERRORS_ENABLE == 0) ? false : true
                    );
            EIP96_TOKEN_CTRL2_WR(dev,
                    Device,
                    i,
                    true,
                    true,
                    false);
            EIP96_OUT_BUF_CTRL_WR(dev,
                    Device,
                    i,
                    EIP97_GLOBAL_EIP96_PE_HOLD_OUTPUT_DATA,
                    (EIP97_GLOBAL_EIP96_BLOCK_UPDATE_APPEND == 0) ? false : true,
                    (EIP97_GLOBAL_EIP96_LEN_DELTA_ENABLE == 0) ? false : true);
            EIP96_CONTEXT_CTRL_WR(dev,
                Device,
                i,
                0x3e,
                false,
                true);
            EIP96_CTX_NUM32_THR_WR(dev,
                Device,
                i,
                EIP97_GLOBAL_EIP96_NUM32_THR);
            EIP96_CTX_NUM64_THR_L_WR(dev,
                Device,
                i,
                EIP97_GLOBAL_EIP96_NUM64_THR_L);
            EIP96_CTX_NUM64_THR_H_WR(dev,
                Device,
                i,
                EIP97_GLOBAL_EIP96_NUM64_THR_H);
        } // for

    } // EIP-202 HIA Global is configured

    return EIP97_GLOBAL_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP97_Global_Reset
 */
EIP97_Global_Error_t
EIP97_Global_Reset(cae_device *dev,
        EIP97_Global_IOArea_t * const IOArea_p,
        const Device_Handle_t Device)
{
    volatile EIP97_True_IOArea_t * const TrueIOArea_p = IOAREA(IOArea_p);
    unsigned int i;

    EIP97_GLOBAL_CHECK_POINTER(IOArea_p);

    // Attempt to initialize slave byte swapping.
    if (!EIP202_Global_Endianness_Slave_Configure(dev, Device))
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;

    // Initialize the IO Area
    TrueIOArea_p->Device = Device;
    // Assume this function is called in the Unknown state but
    // this may not always be true
    TrueIOArea_p->State = (uint32_t)EIP97_GLOBAL_STATE_UNKNOWN;

    if (!EIP202_Global_Reset(dev, Device, EIP97_GLOBAL_MAX_NOF_PE_TO_USE))
        return EIP97_GLOBAL_UNSUPPORTED_FEATURE_ERROR;

    for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
    {
        // Restore the EIP-206 default configuration
        EIP206_IN_DBUF_THRESH_DEFAULT_WR(dev, Device, i);
        EIP206_IN_TBUF_THRESH_DEFAULT_WR(dev, Device, i);
        EIP206_OUT_DBUF_THRESH_DEFAULT_WR(dev, Device, i);
        EIP206_OUT_TBUF_THRESH_DEFAULT_WR(dev, Device, i);

        // Restore the EIP-96 default configuration
        EIP96_TOKEN_CTRL_STAT_DEFAULT_WR(dev, Device, i);
    }

    // Check if Global SW Reset is done
    for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
    {
        EIP97_Global_Error_t EIP97_Rc;

        EIP97_Rc =
            EIP97Lib_Reset_IsDone(dev, Device, &TrueIOArea_p->State, i);

        if (EIP97_Rc != EIP97_GLOBAL_NO_ERROR)
            return EIP97_Rc;
    }

    return EIP97_GLOBAL_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP97_Global_Reset_IsDone
 */
EIP97_Global_Error_t
EIP97_Global_Reset_IsDone(cae_device *dev,
        EIP97_Global_IOArea_t * const IOArea_p)
{
    Device_Handle_t Device;
    volatile EIP97_True_IOArea_t * const TrueIOArea_p = IOAREA(IOArea_p);
    unsigned int i;

    EIP97_GLOBAL_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    // Check if Global SW Reset is done
    for (i = 0; i < EIP97_GLOBAL_MAX_NOF_PE_TO_USE; i++)
    {
        EIP97_Global_Error_t EIP97_Rc;

        EIP97_Rc =
            EIP97Lib_Reset_IsDone(dev, Device, &TrueIOArea_p->State, i);

        if (EIP97_Rc != EIP97_GLOBAL_NO_ERROR)
            return EIP97_Rc;
    }

    return EIP97_GLOBAL_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP97_Global_HWRevision_Get
 */
EIP97_Global_Error_t
EIP97_Global_HWRevision_Get(cae_device *dev,
        EIP97_Global_IOArea_t * const IOArea_p,
        EIP97_Global_Capabilities_t * const Capabilities_p)
{
    Device_Handle_t Device;
    volatile EIP97_True_IOArea_t * const TrueIOArea_p = IOAREA(IOArea_p);

    EIP97_GLOBAL_CHECK_POINTER(IOArea_p);
    EIP97_GLOBAL_CHECK_POINTER(Capabilities_p);

    Device = TrueIOArea_p->Device;

    EIP202Lib_HWRevision_Get(dev, Device,
                             &Capabilities_p->EIP202_Options,
                             &Capabilities_p->EIP202_Options2,
                             &Capabilities_p->EIP202_Version);

    EIP96Lib_HWRevision_Get(dev, Device,
                            PE_DEFAULT_NR,
                            &Capabilities_p->EIP96_Options,
                            &Capabilities_p->EIP96_Version);

    EIP97Lib_HWRevision_Get(dev, Device,
                            &Capabilities_p->EIP97_Options,
                            &Capabilities_p->EIP97_Version);

    return EIP97_GLOBAL_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP97_Global_Configure
 */
EIP97_Global_Error_t
EIP97_Global_Configure(cae_device *dev,
        EIP97_Global_IOArea_t * const IOArea_p,
        const unsigned int PE_Number,
        const EIP97_Global_Ring_PE_Map_t * const RingPEMap_p)
{
    Device_Handle_t Device;
    volatile EIP97_True_IOArea_t * const TrueIOArea_p = IOAREA(IOArea_p);
    EIP202_Global_Ring_PE_Map_t EIP202RingPEMap;

    EIP97_GLOBAL_CHECK_POINTER(IOArea_p);
    EIP97_GLOBAL_CHECK_POINTER(RingPEMap_p);

    if(PE_Number >= EIP97_GLOBAL_MAX_NOF_PE_TO_USE)
        return EIP97_GLOBAL_ARGUMENT_ERROR;

    Device = TrueIOArea_p->Device;

    // Figure out which rings must be assigned to
    // DFE and DSE threads for PE_Number
    EIP202RingPEMap.RingPE_Mask = (uint16_t)(RingPEMap_p->RingPE_Mask &
                                 ((1 << EIP97_GLOBAL_MAX_NOF_RING_TO_USE)-1));
    EIP202RingPEMap.RingPrio_Mask = RingPEMap_p->RingPrio_Mask;
    EIP202RingPEMap.RingSlots0 = RingPEMap_p->RingSlots0;
    EIP202RingPEMap.RingSlots1 = RingPEMap_p->RingSlots1;

#ifdef EIP97_GLOBAL_DEBUG_FSM
    {
        EIP97_Global_Error_t rv;
        EIP97_Global_State_t NewState;

        // Transit to a new state
        if(EIP202RingPEMap.RingPE_Mask != 0)
            NewState = EIP97_GLOBAL_STATE_ENABLED;
        else
            // Engines without rings not allowed!
            NewState = EIP97_GLOBAL_STATE_INITIALIZED;

        rv = EIP97_Global_State_Set(
                (volatile EIP97_Global_State_t*)&TrueIOArea_p->State, NewState);
        if(rv != EIP97_GLOBAL_NO_ERROR)
            return EIP97_GLOBAL_ILLEGAL_IN_STATE;
    }
#endif // EIP97_GLOBAL_DEBUG_FSM

    EIP202_Global_Configure(dev, Device, PE_Number, &EIP202RingPEMap);

    return EIP97_GLOBAL_NO_ERROR;
}


/* end of file eip97_global_init.c */
