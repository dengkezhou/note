/* rpm_device_macros.h
 *
 * Runtime Power Management (RPM) Device Macros API
 *
 */

/*****************************************************************************
* Copyright (c) 2015-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_RPM_DEVICE_MACROS_H
#define INCLUDE_GUARD_RPM_DEVICE_MACROS_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"     // false, IDENTIFIER_NOT_USED


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define RPM_SUCCESS     0   // No error

#define RPM_DEVICE_CAPABILITIES_STR_MACRO     "RPM stubbed"


/*----------------------------------------------------------------------------
 * RPM_DEVICE_INIT_START_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_DEVICE_INIT_START_MACRO(DevId, SuspendFunc, ResumeFunc) RPM_SUCCESS

/*----------------------------------------------------------------------------
 * RPM_DEVICE_INIT_STOP_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_DEVICE_INIT_STOP_MACRO(DevId) RPM_SUCCESS


/*----------------------------------------------------------------------------
 * RPM_DEVICE_UNINIT_START_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_DEVICE_UNINIT_START_MACRO(DevId, fResume) RPM_SUCCESS


/*----------------------------------------------------------------------------
 * RPM_DEVICE_UNINIT_STOP_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_DEVICE_UNINIT_STOP_MACRO(DevId) RPM_SUCCESS


/*----------------------------------------------------------------------------
 * RPM_DEVICE_IO_START_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_DEVICE_IO_START_MACRO(DevId, flag) RPM_SUCCESS


/*----------------------------------------------------------------------------
 * RPM_DEVICE_IO_STOP_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_DEVICE_IO_STOP_MACRO(DevId, flag) RPM_SUCCESS


#endif /* INCLUDE_GUARD_RPM_DEVICE_MACROS_H */


/* rpm_device_macros.h */
