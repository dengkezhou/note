/* rpm_kernel_macros.h
 *
 * Runtime Power Management (RPM) Kernel Macros API
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

#ifndef INCLUDE_GUARD_RPM_KERNEL_MACROS_H
#define INCLUDE_GUARD_RPM_KERNEL_MACROS_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Forward declarations
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define RPM_SUCCESS     0   // No error

#define RPM_OPS_INIT

#define RPM_OPS_PM      NULL


/*----------------------------------------------------------------------------
 * RPM_INIT_MACRO
 *
 * Expands into a single line expression
 */
#define RPM_INIT_MACRO(data)    RPM_SUCCESS


/*----------------------------------------------------------------------------
 * RPM_Uninit
 *
 * Expands into a single line expression
 */
#define RPM_UNINIT_MACRO()    RPM_SUCCESS


#endif /* INCLUDE_GUARD_RPM_KERNEL_MACROS_H */


/* rpm_kernel_macros.h */
