/* c_device_generic.h
 *
 * This is the default configuration file for the generic Driver Framework
 * implementation.
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

// Top-level Hardware platform configuration
#include "cs_hwpal.h"

// Enables strict argument checking for input parameters
//#define HWPAL_STRICT_ARGS_CHECK

// choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT
#ifndef LOG_SEVERITY_MAX
//#define LOG_SEVERITY_MAX LOG_SEVERITY_INFO
#endif

#ifndef HWPAL_MAX_DEVICE_NAME_LENGTH
#error "HWPAL_MAX_DEVICE_NAME_LENGTH undefined"
#endif

// Some magic number for device data validation
//#define HWPAL_DEVICE_MAGIC   0xBABADEDAUL


/* end of file c_device_generic.h */
