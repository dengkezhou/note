/* lkm.h
 *
 * Linux Kernel Module (LKM) interface
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

#ifndef LKM_H_
#define LKM_H_


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"             // bool

// Driver Framework C Run-Time Library API
#include "clib.h"                   // memcmp

// Linux Kernel API
#include <linux/types.h>            // resource_size_t
//#include <linux/compiler.h>         // __iomem


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef struct
{
    // Driver name
    char * DriverName_p;

    // Run-time power management data,
    // pointer to struct dev_pm_ops containing device PM callbacks
    void * PM_p;

    // Implementation-specific initialization data, see implementation notes
    void * CustomInitData_p;

    // Identifier of the resource associated with the device controlled
    // by the device driver implemented in the LKM
    int ResId;

    // Resource size in bytes
    phys_addr_t ResByteCount;

    // Use Message Signaled Interrupts, true - use, false - do not use
    bool fUseMSI;

    // true - keep the device resource mapped after LKM initialization,
    // false - unmap the device resource mapped after LKM initialization
    bool fRetainMap;

} LKM_Init_t;


/*----------------------------------------------------------------------------
 * LKM_Init
 *
 * Initializes the kernel module and registers it as a device driver
 * in the kernel.
 *
 * Return value
 *      >=0 - success
 *      <0  - failure
 */
int LKM_Init(cae_device *dev, LKM_Init_t *const InitData_p);


/*-----------------------------------------------------------------------------
 * LKM_Uninit
 *
 * Uninitializes the kernel module registered with the LKM_Init() function.
 *
 * Return value
 *      None
 */
void LKM_Uninit(cae_device *dev);


/*-----------------------------------------------------------------------------
 * LKM_DeviceGeneric_Get
 *
 * Returns pointer to a generic Linux kernel struct device.
 *
 * Return value
 *      Pointer to struct device.
 */
void *
LKM_DeviceGeneric_Get(void);


/*-----------------------------------------------------------------------------
 * LKM_DeviceSpecific_Get
 *
 * Returns pointer to a specific Linux kernel struct device,
 * such as pci_dev for PCI, or platform_device for Platform.
 *
 * Return value
 *      Pointer to struct device.
 */
void *
LKM_DeviceSpecific_Get(void);


/*-----------------------------------------------------------------------------
 * LKM_PhysBaseAddr_Get
 *
 * Returns a pointer to a physical base address of the device memory mapped
 * IO space (physical resource address)
 *
 * Return value
 *      Pointer to a physical resource address of the device.
 */
void *
LKM_PhysBaseAddr_Get(cae_device *dev);


/*-----------------------------------------------------------------------------
 * LKM_MappedBaseAddr_Get
 *
 * Returns a pointer to a mapped to the kernel memory base address
 * of the device memory mapped IO space (mapped or virtual resource address)
 *
 * Return value
 *      Pointer to a mapped resource address of the device.
 */
void __iomem *
LKM_MappedBaseAddr_Get(cae_device *dev);


/* end of file lkm.h */


#endif /* LKM_H_ */
