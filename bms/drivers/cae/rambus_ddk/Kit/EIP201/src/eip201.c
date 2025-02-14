/* eip201_sl.c
 *
 * Driver Library for the Security-IP-EIP-201 Advanced Interrupt Controller.
 */

/*****************************************************************************
* Copyright (c) 2007-2020 by Rambus, Inc. and/or its subsidiaries.
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

// Top-level Interrupt controller configuration
#include "c_eip201.h"           // configuration

// Driver Framework Basic Defs API
#include "basic_defs.h"         // uint32_t, inline, etc.

// Interrupt controller API
#include "eip201.h"             // the API we will implement

// Driver Framework Device API
#include "device_rw.h"          // Device_Read32/Write32

// create a constant where all unused interrupts are '1'
#if (EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS < 32)
#define EIP201_NOTUSEDIRQ_MASK (uint32_t) \
                    (~((1 << EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS)-1))
#else
#define EIP201_NOTUSEDIRQ_MASK 0
#endif

#ifdef EIP201_STRICT_ARGS
#define EIP201_CHECK_IF_IRQ_SUPPORTED(_irqs) \
        if (_irqs & EIP201_NOTUSEDIRQ_MASK) \
            return EIP201_STATUS_UNSUPPORTED_IRQ;
#else
#define EIP201_CHECK_IF_IRQ_SUPPORTED(_irqs)
#endif /* EIP201_STRICT_ARGS */


/*----------------------------------------------------------------------------
 *  EIP201 registers
 */
enum
{
    EIP201_REGISTER_OFFSET_POL_CTRL     = EIP201_LO_REG_BASE+0,
    EIP201_REGISTER_OFFSET_TYPE_CTRL    = EIP201_LO_REG_BASE+4,
    EIP201_REGISTER_OFFSET_ENABLE_CTRL  = EIP201_LO_REG_BASE+8,
    EIP201_REGISTER_OFFSET_RAW_STAT     = EIP201_HI_REG_BASE+12,
    EIP201_REGISTER_OFFSET_ENABLE_SET   = EIP201_LO_REG_BASE+12,
    EIP201_REGISTER_OFFSET_ENABLED_STAT = EIP201_HI_REG_BASE+16,
    EIP201_REGISTER_OFFSET_ACK          = EIP201_LO_REG_BASE+16,
    EIP201_REGISTER_OFFSET_ENABLE_CLR   = EIP201_LO_REG_BASE+20,
    EIP201_REGISTER_OFFSET_OPTIONS      = EIP201_HI_REG_BASE+24,
    EIP201_REGISTER_OFFSET_VERSION      = EIP201_HI_REG_BASE+28
};

// this implementation supports only the EIP-201 HW1.1 and HW1.2
// 0xC9  = 201
// 0x39  = binary inverse of 0xC9
#define EIP201_SIGNATURE      0x36C9
#define EIP201_SIGNATURE_MASK 0xffff

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
 * EIP201_Read32
 *
 * This routine reads from a Register location in the EIP201, applying
 * endianness swapping when required (depending on configuration).
 */
static inline uint32_t
EIP201_Read32(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int Offset)
{
    return Device_Read32(dev, Device, Offset);
}


/*----------------------------------------------------------------------------
 * EIP201_Write32
 *
 * This routine writes to a Register location in the EIP201, applying
 * endianness swapping when required (depending on configuration).
 */
static inline void
EIP201_Write32(cae_device *dev,
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint32_t Value)
{
    Device_Write32(dev, Device, Offset, Value);
}


/*----------------------------------------------------------------------------
 * EIP201_Config_Change
 */
#ifndef EIP201_REMOVE_CONFIG_CHANGE
EIP201_Status_t
EIP201_Config_Change(cae_device *dev,
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources,
        const EIP201_Config_t Config)
{
    uint32_t Value;
    uint32_t NewPol = 0;
    uint32_t NewType = 0;
    EIP201_CHECK_IF_IRQ_SUPPORTED(Sources);

    /*
        EIP201_CONFIG_ACTIVE_LOW,       // Type=0, Pol=0
        EIP201_CONFIG_ACTIVE_HIGH,      // Type=0, Pol=1
        EIP201_CONFIG_FALLING_EDGE,     // Type=1, Pol=0
        EIP201_CONFIG_RISING_EDGE       // Type=1, Pol=1
    */

    // do we want Type=1?
    if (Config == EIP201_CONFIG_FALLING_EDGE ||
        Config == EIP201_CONFIG_RISING_EDGE)
    {
        NewType = Sources;
    }

    // do we want Pol=1?
    if (Config == EIP201_CONFIG_ACTIVE_HIGH ||
        Config == EIP201_CONFIG_RISING_EDGE)
    {
        NewPol = Sources;
    }

    if (Sources)
    {
        // modify polarity register
        Value = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_POL_CTRL);
        Value &= ~Sources;
        Value |= NewPol;
        EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_POL_CTRL, Value);

        // modify type register
        Value = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_TYPE_CTRL);
        Value &= ~Sources;
        Value |= NewType;
        EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_TYPE_CTRL, Value);
    }

    return EIP201_STATUS_SUCCESS;
}
#endif /* EIP201_REMOVE_CONFIG_CHANGE */


/*----------------------------------------------------------------------------
 * EIP201_Config_Read
 */
#ifndef EIP201_REMOVE_CONFIG_READ

static const EIP201_Config_t EIP201_Setting2Config[4] =
{
    EIP201_CONFIG_ACTIVE_LOW,       // Type=0, Pol=0
    EIP201_CONFIG_ACTIVE_HIGH,      // Type=0, Pol=1
    EIP201_CONFIG_FALLING_EDGE,     // Type=1, Pol=0
    EIP201_CONFIG_RISING_EDGE       // Type=1, Pol=1
};

EIP201_Config_t
EIP201_Config_Read(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    uint32_t Value;
    unsigned char Setting = 0;

    Value = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_TYPE_CTRL);
    if (Value & Source)
    {
        // Type=1, thus edge
        Setting += 2;
    }

    Value = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_POL_CTRL);
    if (Value & Source)
    {
        // Pol=1, this rising edge or active high
        Setting++;
    }

    return EIP201_Setting2Config[Setting];
}
#endif /* EIP201_REMOVE_CONFIG_READ */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_EnableSource
 *
 * See header file for function specifications.
 */
#ifndef EIP201_REMOVE_SOURCEMASK_ENABLESOURCE
EIP201_Status_t
EIP201_SourceMask_EnableSource(cae_device *dev,
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources)
{
    EIP201_CHECK_IF_IRQ_SUPPORTED(Sources);

    EIP201_Write32(dev, 
            Device,
            EIP201_REGISTER_OFFSET_ENABLE_SET,
            Sources);

    return EIP201_STATUS_SUCCESS;
}
#endif /* EIP201_REMOVE_SOURCEMASK_ENABLESOURCE */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_DisableSource
 */
#ifndef EIP201_REMOVE_SOURCEMASK_DISABLESOURCE
EIP201_Status_t
EIP201_SourceMask_DisableSource(cae_device *dev,
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources)
{
    EIP201_Write32(dev, 
            Device,
            EIP201_REGISTER_OFFSET_ENABLE_CLR,
            Sources);

    return EIP201_STATUS_SUCCESS;
}
#endif /* EIP201_REMOVE_SOURCEMASK_DISABLESOURCE */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_SourceIsEnabled
 */
#ifndef EIP201_REMOVE_SOURCEMASK_SOURCEISENABLED
bool
EIP201_SourceMask_SourceIsEnabled(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    uint32_t SourceMasks;

    SourceMasks = EIP201_Read32(dev, 
                        Device,
                        EIP201_REGISTER_OFFSET_ENABLE_CTRL);

    if (SourceMasks & Source)
        return true;

    return false;
}
#endif /* EIP201_REMOVE_SOURCEMASK_SOURCEISENABLED */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_ReadAll
 */
#ifndef EIP201_REMOVE_SOURCEMASK_READALL
EIP201_SourceBitmap_t
EIP201_SourceMask_ReadAll(
        Device_Handle_t Device)
{
    return EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_ENABLE_CTRL);
}
#endif /* EIP201_REMOVE_SOURCEMASK_READALL */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_IsEnabledSourcePending
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_ISENABLEDSOURCEPENDING
bool
EIP201_SourceStatus_IsEnabledSourcePending(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    uint32_t Statuses;

    Statuses = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_ENABLED_STAT);

    if (Statuses & Source)
        return true;

    return false;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_ISENABLEDSOURCEPENDING */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_IsRawSourcePending
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_ISRAWSOURCEPENDING
bool
EIP201_SourceStatus_IsRawSourcePending(cae_device *dev,
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    uint32_t Statuses;

    Statuses = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_RAW_STAT);

    if (Statuses & Source)
        return true;

    return false;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_ISRAWSOURCEPENDING */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_ReadAllEnabled
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_READALLENABLED
EIP201_SourceBitmap_t
EIP201_SourceStatus_ReadAllEnabled(cae_device *dev,
        Device_Handle_t Device)
{
    return EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_ENABLED_STAT);
}
#endif /* EIP201_REMOVE_SOURCESTATUS_READALLENABLED */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_ReadAllRaw
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_READALLRAW
EIP201_SourceBitmap_t
EIP201_SourceStatus_ReadAllRaw(cae_device *dev,
        Device_Handle_t Device)
{
    return EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_RAW_STAT);
}
#endif /* EIP201_REMOVE_SOURCESTATUS_READALLRAW */


/*----------------------------------------------------------------------------
 * EIP201Lib_Detect
 *
 *  Detect the presence of EIP201 hardware.
 */
#ifndef EIP201_REMOVE_INITIALIZE
static bool
EIP201Lib_Detect(cae_device *dev,
        Device_Handle_t Device)
{
    uint32_t Value;

    Value = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_VERSION);
    Value &= EIP201_SIGNATURE_MASK;
    if ( Value != EIP201_SIGNATURE)
        return false;

    // Prevent interrupts going of by disabling them
    EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_ENABLE_CTRL, 0);

    // Get the number of interrupt sources
    Value = EIP201_Read32(dev, Device, EIP201_REGISTER_OFFSET_OPTIONS);
    // lowest 6 bits contain the number of inputs, which should be between 1-32
    Value &= MASK_6_BITS;
    if (Value == 0 || Value > 32)
        return false;

    return true;
}
#endif /* EIP201_REMOVE_INITIALIZE */


/*----------------------------------------------------------------------------
 * EIP201_Initialize API
 *
 *  See header file for function specification.
 */
#ifndef EIP201_REMOVE_INITIALIZE
EIP201_Status_t
EIP201_Initialize(cae_device *dev,
        Device_Handle_t Device,
        const EIP201_SourceSettings_t * SettingsArray_p,
        const unsigned int SettingsCount)
{
    EIP201_SourceBitmap_t ActiveLowSources = 0;
    EIP201_SourceBitmap_t ActiveHighSources = 0;
    EIP201_SourceBitmap_t FallingEdgeSources = 0;
    EIP201_SourceBitmap_t RisingEdgeSources = 0;
    EIP201_SourceBitmap_t EnabledSources = 0;

    // check presence of EIP201 hardware
    if (!EIP201Lib_Detect(dev, Device))
        return EIP201_STATUS_UNSUPPORTED_HARDWARE_VERSION;

    // disable all interrupts and set initial configuration
    EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_ENABLE_CTRL, 0);
    EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_POL_CTRL, 0);
    EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_TYPE_CTRL, 0);

    // process the setting, if provided
    if (SettingsArray_p != NULL)
    {
        unsigned int i;

        for (i = 0; i < SettingsCount; i++)
        {
            // check
            const EIP201_Source_t Source = SettingsArray_p[i].Source;
            EIP201_CHECK_IF_IRQ_SUPPORTED(Source);

            // determine polarity
            switch(SettingsArray_p[i].Config)
            {
                case EIP201_CONFIG_ACTIVE_LOW:
                    ActiveLowSources |= Source;
                    break;

                case EIP201_CONFIG_ACTIVE_HIGH:
                    ActiveHighSources |= Source;
                    break;

                case EIP201_CONFIG_FALLING_EDGE:
                    FallingEdgeSources |= Source;
                    break;

                case EIP201_CONFIG_RISING_EDGE:
                    RisingEdgeSources |= Source;
                    break;

                default:
                    // invalid parameter
                    break;
            } // switch

            // determine enabled mask
            if (SettingsArray_p[i].fEnable)
                EnabledSources |= Source;
        } // for
    }

    // program source configuration
    EIP201_Config_Change(dev, 
            Device,
            ActiveLowSources,
            EIP201_CONFIG_ACTIVE_LOW);

    EIP201_Config_Change(dev, 
            Device,
            ActiveHighSources,
            EIP201_CONFIG_ACTIVE_HIGH);

    EIP201_Config_Change(dev, 
            Device,
            FallingEdgeSources,
            EIP201_CONFIG_FALLING_EDGE);

    EIP201_Config_Change(dev, 
            Device,
            RisingEdgeSources,
            EIP201_CONFIG_RISING_EDGE);

    // the configuration change could have triggered the edge-detection logic
    // so acknowledge all edge-based interrupts immediately
    {
        const uint32_t Value = FallingEdgeSources | RisingEdgeSources;
        EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_ACK, Value);
    }

    // set mask (enable required interrupts)
    EIP201_SourceMask_EnableSource(dev, Device, EnabledSources);

    return EIP201_STATUS_SUCCESS;
}
#endif /* EIP201_REMOVE_INITIALIZE */


/*----------------------------------------------------------------------------
 * EIP201_Acknowledge
 *
 * See header file for function specification.
 */
#ifndef EIP201_REMOVE_ACKNOWLEDGE
EIP201_Status_t
EIP201_Acknowledge(cae_device *dev,
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources)
{
    EIP201_CHECK_IF_IRQ_SUPPORTED(Sources);

    EIP201_Write32(dev, Device, EIP201_REGISTER_OFFSET_ACK, Sources);

    return EIP201_STATUS_SUCCESS;
}
#endif /* EIP201_REMOVE_ACKNOWLEDGE */

/* end of file eip201_sl.c */
