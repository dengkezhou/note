/* umdevxs_ofdev.h
 *
 * Exported OpenFirmware (OF) Device API of the UMDexXS driver.
 */

/*****************************************************************************
* Copyright (c) 2014-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_UMDEVXS_OFDEV_H
#define INCLUDE_GUARD_UMDEVXS_OFDEV_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Linux Kernel API
#include <linux/of_platform.h>      // of_*,


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * UMDevXS_OFDev_GetDevice
 *
 * Obtain a reference to the OF device structure and the mapped address
 * of the OF device registered by this driver.
 *
 * DeviceID (input)
 *   Selection of a specific (sub)-device.
 *
 * Device_pp (output)
 *   Reference to the struct platform_device of the registered OF device.
 *
 * MappedBaseAddr_pp (output)
 *   Base address of the memory-mapped I/O.
 *
 * Return 0 on success.
 */
int
UMDevXS_OFDev_GetDevice(
              unsigned int DeviceID,
              struct platform_device ** OF_Device_pp,
              void __iomem ** MappedBaseAddr_pp);


#endif /* INCLUDE_GUARD_UMDEVXS_OFDEV_H */


/* umdevxs_ofdev.h */
