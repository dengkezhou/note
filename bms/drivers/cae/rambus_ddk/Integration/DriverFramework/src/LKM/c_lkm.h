/* c_lkm.h
 *
 * Configuration Handling for the LKM implementation.
 * A build-level configuration file is included and sanity-checked.
 * Do not edit this file. Edit cs_lkm.h instead.
 */

/*****************************************************************************
* Copyright (c) 2010-2020 by Rambus, Inc. and/or its subsidiaries.
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

/*----------------------------------------------------------------
 * get configuration settings from product config file
 */

// Top-level Hardware platform configuration
#include "cs_lkm.h"


// Enables strict argument checking for input parameters
//#define LKM_STRICT_ARGS_CHECK

// choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT
#ifndef LKM_LOG_SEVERITY
#define LKM_LOG_SEVERITY LOG_SEVERITY_INFO
#endif

/* LKM_DEVICE_ID
 *
 * PCI device identification required for implementation of Device API
 */
//#define LKM_DEVICE_ID             0x6018

/* LKM_VENDOR_ID
 *
 * PCI device vendor identification required for implementation of Device API
 */
//#define LKM_VENDOR_ID             0x10EE

/* LKM_LOG_PREFIX
 *
 * Logging prefix that precedes each trace line in log
 */
#ifndef LKM_LOG_PREFIX
#define LKM_LOG_PREFIX                  ""
#endif

/* LKM_PLATFORM_DEVICE_NAME
 *
 * Platform-specific device name that can be used for looking up
 * device properties
 */
//#define LKM_PLATFORM_DEVICE_NAME      "Unknown"

/* LKM_PLATFORM_IRQ_COUNT
 *
 * Platform-specific number of the IRQ's that will be used by the device.
 *
 */
#ifndef LKM_PLATFORM_IRQ_COUNT
#define LKM_PLATFORM_IRQ_COUNT          1
#endif

/* LKM_PLATFORM_IRQ_IDX
 *
 * Platform-specific index of the IRQ that will be used.
 *
 */
#ifndef LKM_PLATFORM_IRQ_IDX
#define LKM_PLATFORM_IRQ_IDX            0
#endif


/* end of file c_lkm.h */
