/* adapter_init.c
 *
 * Adapter module responsible for adapter initialization tasks.
 *
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

#include <cae.h>

#include "adapter_init.h"

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include "cs_adapter.h"

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
#include "adapter_interrupts.h" // Adapter_Interrupts_Init,
                                // Adapter_Interrupts_UnInit
#endif

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
#include "adapter_pciconfig.h"  // PCICONFIG_*
#endif

// Logging API
#include "log.h"            // LOG_*

// Driver Framework Device API
#include "device_mgmt.h"    // Device_Initialize, Device_UnInitialize
#include "device_rw.h"      // Device_Read32, Device_Write32

// Driver Framework DMAResource API
#include "dmares_mgmt.h"    // DMAResource_Init, DMAResource_UnInit

// Driver Framework Basic Definitions API
#include "basic_defs.h"     // bool, true, false


/*----------------------------------------------------------------------------
 * Local variables
 */

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
static Device_Handle_t Adapter_Device_PCIConfigSpace;
#endif

extern bool
Adapter_Interrupts_Init(cae_device *dev,
        const int nIRQ);
extern void
Adapter_Interrupts_UnInit(cae_device *dev, const int nIRQ);
extern void
Device_Write32(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int ByteOffset,
        const uint32_t ValueIn);
extern uint32_t
Device_Read32(cae_device *dev,
        const Device_Handle_t Device,
        const unsigned int ByteOffset);

/*----------------------------------------------------------------------------
 * Adapter_Init
 *
 * Return Value
 *     true   Success
 *     false  Failure (fatal!)
 */
bool
Adapter_Init(cae_device *dev)
{
    dev->Device_IRQ = -1;

    if (dev->Adapter_IsInitialized != false)
    {
        LOG_WARN("Adapter_Init: Already initialized\n");
        return true;
    }

    // trigger first-time initialization of the adapter
    if (Device_Initialize(dev, &dev->Device_IRQ) < 0)
        return false;

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
    Adapter_Device_PCIConfigSpace = Device_Find(dev, "PCI_CONFIG_SPACE");
    if (Adapter_Device_PCIConfigSpace == NULL)
    {
        LOG_CRIT("Adapter_Init: Failed to locate PCI_CONFIG_SPACE\n");
        return false;
    }
#endif // ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
    dev->Adapter_Device_BOARDCTRL = Device_Find(dev, "BOARD_CTRL");
    if (dev->Adapter_Device_BOARDCTRL == NULL)
    {
        LOG_CRIT("Adapter_Init: Failed to locate BOARD_CTRL\n");
        return false;
    }
#endif // ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE

    if (!DMAResource_Init(dev))
    {
        Device_UnInitialize(dev);
        return false;
    }

    // PCI specific functionality
#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
    {
        uint32_t Value;
        int VendorID, DeviceID;

        Value = Device_Read32(dev, 
                    Adapter_Device_PCIConfigSpace,
                    PCICONFIG_REG_ID);

        VendorID = PCICONFIG_ID_EXTRACT_VENDOR(Value);
        DeviceID = PCICONFIG_ID_EXTRACT_DEVICE(Value);

        IDENTIFIER_NOT_USED(VendorID);
        IDENTIFIER_NOT_USED(DeviceID);

        LOG_INFO(
            "Adapter_Init: "
            "PCI device: "
            "Vendor=0x%X, "
            "Device=0x%X\n",
            VendorID,
            DeviceID);
    }

    // initialize the PCI device
    // command and status register - Writing value 0x146 to this register
    // is recommended before accessing Security-IP-97 FPGA
    {
        uint32_t Value;

        Value = PCICONFIG_STATCMD_MEMORYACCESS_ENABLE +
                PCICONFIG_STATCMD_BUSMASTER_ENABLE +
                PCICONFIG_STATCMD_PARITYERR_ENABLE +
                PCICONFIG_STATCMD_SYSTEMERR_ENABLE;

        Device_Write32(dev,
                Adapter_Device_PCIConfigSpace,
                PCICONFIG_REG_STATCMD,
                Value);
    }

    // Setting cache line size
    // maintain all other bits (set by BIOS or OS)
    {
        uint32_t OldValue, Value;

        Value = Device_Read32(dev, 
                    Adapter_Device_PCIConfigSpace,
                    PCICONFIG_REG_CONFIG);
        OldValue = Value;

        IDENTIFIER_NOT_USED(OldValue);

        Value = PCICONFIG_CONFIG_UPDATE_CACHELINESIZE(
                    Value,
                    ADAPTER_PCICONFIG_CACHELINESIZE);

#ifdef ADAPTER_PCICONFIG_MASTERLATENCYTIMER
        Value = PCICONFIG_CONFIG_UPDATE_MASTERLATENCYTIMER(
                    Value,
                    ADAPTER_PCICONFIG_MASTERLATENCYTIMER);
#endif

        Device_Write32(dev,
                Adapter_Device_PCIConfigSpace,
                PCICONFIG_REG_CONFIG,
                Value);

        LOG_INFO(
            "Adapter_Init: "
            "Changed PCI_Config[0x0c] "
            "from 0x%08x "
            "to 0x%08x\n",
            OldValue,
            Value);
    }
#endif // ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

    // FPGA board specific functionality
#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
    {
#ifdef ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
        // Perform HW Reset for the EIP-97 FPGA board
        Device_Write32(dev, dev->Adapter_Device_BOARDCTRL, 0x0, 0);
        Device_Write32(dev, dev->Adapter_Device_BOARDCTRL, 0x0, 1);
        Device_Write32(dev, dev->Adapter_Device_BOARDCTRL, 0x0, 0);
#endif // ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
    }
#endif // ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
    if (!Adapter_Interrupts_Init(dev, dev->Device_IRQ))
    {
        LOG_CRIT("Adapter_Init: Adapter_Interrupts_Init failed\n");

        DMAResource_UnInit(dev);

        Device_UnInitialize(dev);

        return false;
    }
#endif

    dev->Adapter_IsInitialized = true;

    return true;    // success
}


/*----------------------------------------------------------------------------
 * Adapter_UnInit
 */
void
Adapter_UnInit(cae_device *dev)
{
    if (!dev->Adapter_IsInitialized)
    {
        LOG_WARN("Adapter_UnInit: Adapter is not initialized\n");
        return;
    }

    dev->Adapter_IsInitialized = false;

    DMAResource_UnInit(dev);

#ifdef ADAPTER_PEC_INTERRUPTS_ENABLE
    Adapter_Interrupts_UnInit(dev, dev->Device_IRQ);
#endif

    Device_UnInitialize(dev);
}


/*----------------------------------------------------------------------------
 * Adapter_Report_Build_Params
 */
void
Adapter_Report_Build_Params(void)
{
#ifdef LOG_INFO_ENABLED
    int dummy;

    // This function is dependent on config file cs_adapter.h.
    // Please update this when Config file for Adapter is changed.
    Log_FormattedMessage("Adapter build configuration:\n");

#define REPORT_SET(_X) \
    Log_FormattedMessage("\t" #_X "\n")

#define REPORT_STR(_X) \
    Log_FormattedMessage("\t" #_X ": %s\n", _X)

#define REPORT_INT(_X) \
    dummy = _X; Log_FormattedMessage("\t" #_X ": %d\n", _X)

#define REPORT_HEX32(_X) \
    dummy = _X; Log_FormattedMessage("\t" #_X ": 0x%08X\n", _X)

#define REPORT_EQ(_X, _Y) \
    dummy = (_X + _Y); Log_FormattedMessage("\t" #_X " == " #_Y "\n")

#define REPORT_EXPL(_X, _Y) \
    Log_FormattedMessage("\t" #_X _Y "\n")

    // Adapter PEC
#ifdef ADAPTER_PEC_DBG
    REPORT_SET(ADAPTER_PEC_DBG);
#endif

#ifdef ADAPTER_PEC_STRICT_ARGS
    REPORT_SET(ADAPTER_PEC_STRICT_ARGS);
#endif

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    REPORT_SET(ADAPTER_PEC_ENABLE_SCATTERGATHER);
#endif

#ifdef ADAPTER_PEC_SEPARATE_RINGS
    REPORT_SET(ADAPTER_PEC_SEPARATE_RINGS);
#else
    REPORT_EXPL(ADAPTER_PEC_SEPARATE_RINGS, " is NOT set => Overlapping");
#endif

#ifdef ADAPTER_PEC_ARMRING_ENABLE_SWAP
    REPORT_SET(ADAPTER_PEC_ARMRING_ENABLE_SWAP);
#endif

    REPORT_INT(ADAPTER_PEC_DEVICE_COUNT);
    REPORT_INT(ADAPTER_PEC_MAX_PACKETS);
    REPORT_INT(ADAPTER_MAX_PECLOGICDESCR);
    REPORT_INT(ADAPTER_PEC_MAX_SAS);
    REPORT_INT(ADAPTER_DESCRIPTORDONETIMEOUT);
    REPORT_INT(ADAPTER_DESCRIPTORDONECOUNT);

#ifdef ADAPTER_REMOVE_BOUNCEBUFFERS
    REPORT_EXPL(ADAPTER_REMOVE_BOUNCEBUFFERS, " is SET => Bounce DISABLED");
#else
    REPORT_EXPL(ADAPTER_REMOVE_BOUNCEBUFFERS, " is NOT set => Bounce ENABLED");
#endif

#ifdef ADAPTER_EIP202_INTERRUPTS_ENABLE
    REPORT_EXPL(ADAPTER_EIP202_INTERRUPTS_ENABLE,
            " is SET => Interrupts ENABLED");
#else
    REPORT_EXPL(ADAPTER_EIP202_INTERRUPTS_ENABLE,
            " is NOT set => Interrupts DISABLED");
#endif

#ifdef ADAPTER_64BIT_HOST
    REPORT_EXPL(ADAPTER_64BIT_HOST,
                " is SET => addresses are 64-bit");
#else
    REPORT_EXPL(ADAPTER_64BIT_HOST,
                " is NOT set => addresses are 32-bit");
#endif

#ifdef ADAPTER_64BIT_DEVICE
    REPORT_EXPL(ADAPTER_64BIT_DEVICE,
                " is SET => full 64-bit DMA addresses usable");
#else
    REPORT_EXPL(ADAPTER_64BIT_DEVICE,
                " is NOT set => DMA addresses must be below 4GB");
#endif

#ifdef ADAPTER_DMARESOURCE_BANKS_ENABLE
    REPORT_SET(ADAPTER_DMARESOURCE_BANKS_ENABLE);
#endif

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
    REPORT_SET(ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE);
#endif

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
    REPORT_SET(ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE);
#endif

    // Log
    Log_FormattedMessage("Logging:\n");

#if (LOG_SEVERITY_MAX == LOG_SEVERITY_INFO)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_INFO);
#elif (LOG_SEVERITY_MAX == LOG_SEVERITY_WARNING)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_WARNING);
#elif (LOG_SEVERITY_MAX == LOG_SEVERITY_CRITICAL)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_CRITICAL);
#else
    REPORT_EXPL(LOG_SEVERITY_MAX, " - Unknown (not info/warn/crit)");
#endif

    // Adapter other
    Log_FormattedMessage("Other:\n");
    REPORT_STR(ADAPTER_DRIVER_NAME);
    REPORT_STR(ADAPTER_LICENSE);
    REPORT_HEX32(ADAPTER_INTERRUPTS_TRACEFILTER);

    IDENTIFIER_NOT_USED(dummy);

#endif //LOG_INFO_ENABLED
}


/* end of file adapter_init.c */
