/* cs_driver_ext2.h
 *
 * Top-level Product EIP-97 hardware specific Configuration Settings.
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

#ifndef INCLUDE_GUARD_CS_DRIVER_EXT2_H
#define INCLUDE_GUARD_CS_DRIVER_EXT2_H


// Enables DMA banks
#ifdef DRIVER_64BIT_DEVICE
//#define DRIVER_DMARESOURCE_BANKS_ENABLE
#endif

#ifdef DRIVER_DMARESOURCE_BANKS_ENABLE
// DMA bank to use for SA bouncing by the PEC API implementation
#define DRIVER_PEC_BANK_SA                             1 // Static bank

// Maximum number of SA or transform records the driver can allocate
#define DRIVER_TRANSFORM_RECORD_COUNT           DRIVER_PEC_MAX_SAS

// Transform record size
#define DRIVER_TRANSFORM_RECORD_BYTE_COUNT      640

// Each static bank for DMA resources must have 2 lists
#define DRIVER_LIST_MAX_NOF_INSTANCES           2

// Not used, but required for the Adapter PCL config params compile-time check
#define DRIVER_LIST_PCL_OFFSET                  DRIVER_LIST_MAX_NOF_INSTANCES
#else
// Not used, but required for the Adapter PCL config params compile-time check
#define DRIVER_LIST_PCL_OFFSET                  0
#endif // DRIVER_DMARESOURCE_BANKS_ENABLE


#endif /* Include Guard */


/* end of file cs_driver_ext2.h */
