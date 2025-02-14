/* umdevxs_pcidev.h
 *
 * Exported PCIDev API of the UMDexXS/UMPCI driver.
 */

/*****************************************************************************
* Copyright (c) 2012-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_UMDEVXS_PCIDEV_H
#define INCLUDE_GUARD_UMDEVXS_PCIDEV_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
//#include <linux/pci.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */



/*----------------------------------------------------------------------------
 * UMDevXS_PCIDev_Get
 *
 * Obtain a reference to the PCI device structure and the mapped address
 * of the first BAR of the PCI device registered by this driver.
 *
 * DeviceID (input)
 *   Selection of a specific (sub)-device.
 * Device_p (output)
 *   Reference to the struct pci_dev of the registered PCI device.
 * MappedBaseAddr_p (output)
 *   Base address of the memory-mapped I/O.
 *
 * Return 0 on success.
 */
int
UMDevXS_PCIDev_Get(
              unsigned int DeviceID,
              unsigned int ** Device_pp,
              void ** MappedBaseAddr_pp);


#endif /* INCLUDE_GUARD_UMDEVXS_PCIDEV_H */


/* umdevxs_pcidev.h */
