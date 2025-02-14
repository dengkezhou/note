/* device_platform.h
 *
 * Driver Framework platform-specific interface,
 * Linux user-space UMDevXS.
 */

/*****************************************************************************
* Copyright (c) 2017-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef DEVICE_PLATFORM_H_
#define DEVICE_PLATFORM_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"             // uint32_t

// Linux kernel API
//#include <linux/compiler.h>         // __iomem
//#include <linux/pci.h>              // pci_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Internal global device administration data
typedef struct
{
    // Device data
    //struct pci_dev * PCI_Device_p;
    uint32_t *PCI_Device_p;

    // Physical base address of the device resource (MMIO space)
    void * PhysBaseAddr;

    // Mapped (virtual) address of the device resource (MMIO space)
    uint32_t * MappedBaseAddr_p;

} Device_Platform_Global_t;

// Internal device administration data
typedef struct
{
    unsigned int Reserved; // not used

} Device_Platform_t;


/*----------------------------------------------------------------------------
 * Local variables
 */


#endif // DEVICE_PLATFORM_H_


/* end of file device_platform.h */

