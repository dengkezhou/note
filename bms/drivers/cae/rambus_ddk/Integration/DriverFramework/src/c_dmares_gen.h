/* c_dmares_gen.h
 *
 * Default configuration for generic Driver Framework DMAResource API
 * implementation.
 *
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

#ifndef C_DMARES_GEN_H_
#define C_DMARES_GEN_H_


/*----------------------------------------------------------------
 * get configuration settings from product config file
 */
#include "cs_hwpal.h"

// choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT
#ifndef LOG_SEVERITY_MAX
//#define LOG_SEVERITY_MAX LOG_SEVERITY_INFO
#endif

#ifdef HWPAL_DMARESOURCE_BANKS_ENABLE
#ifndef HWPAL_DMARESOURCE_BANKS
#error "Expected HWPAL_DMARESOURCE_BANKS defined by cs_hwpal.h"
#endif
#endif // HWPAL_DMARESOURCE_BANKS_ENABLE

// Enable use of UMDevXS device
#ifdef HWPAL_USE_UMDEVXS_DEVICE
#define HWPAL_DMARESOURCE_USE_UMDEVXS_DEVICE
#endif // HWPAL_USE_UMDEVXS_DEVICE

/*----------------------------------------------------------------
 * Other configuration parameters that can be set in a top level
 * configuration
 */

// Enables DMA resources banks so that different memory regions can be used
// for DMA buffer allocation
//#define HWPAL_DMARESOURCE_BANKS_ENABLE

#ifndef HWPAL_DMARESOURCE_DMA_ALIGNMENT_BYTE_COUNT
#ifdef HWPAL_DMARESOURCE_64BIT
// Default 8 bytes (64 bits) address alignment
#define HWPAL_DMARESOURCE_DMA_ALIGNMENT_BYTE_COUNT      8
#else
// Default 4 bytes (32 bits) address alignment
#define HWPAL_DMARESOURCE_DMA_ALIGNMENT_BYTE_COUNT      4
#endif
#endif

// When defined enables strict argument checking
//#define HWPAL_DMARESOURCE_STRICT_ARGS_CHECKS


#endif // C_DMARES_GEN_H_


/* end of file c_dmares_gen.h */
