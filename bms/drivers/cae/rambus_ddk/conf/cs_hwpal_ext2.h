/* cs_hwpal_ext2.h
 *
 * Security-IP-97 hardware specific configuration parameters
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

#ifndef CS_HWPAL_EXT2_H_
#define CS_HWPAL_EXT2_H_


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Enables DMA resources banks so that different memory regions can be used
// for DMA buffer allocation
#ifdef DRIVER_DMARESOURCE_BANKS_ENABLE
#define HWPAL_DMARESOURCE_BANKS_ENABLE
#endif // DRIVER_DMARESOURCE_BANKS_ENABLE

#ifdef HWPAL_DMARESOURCE_BANKS_ENABLE
// Definition of DMA banks, one dynamic and 1 static
//                                  Bank   Static   Blocks   Block size
#define HWPAL_DMARESOURCE_BANKS                                          \
        HWPAL_DMARESOURCE_BANK_ADD (0,       0,       0,          0),    \
        HWPAL_DMARESOURCE_BANK_ADD (1,       1,                          \
                                    DRIVER_TRANSFORM_RECORD_COUNT,       \
                                    DRIVER_TRANSFORM_RECORD_BYTE_COUNT)
#endif // HWPAL_DMARESOURCE_BANKS_ENABLE


#endif /* CS_HWPAL_EXT2_H_ */


/* end of file cs_hwpal_ext2.h */
