/* adapter_lock_ext.h
 *
 * Adapter concurrency (locking) management
 * extensions for Linux kernel-space
 *
 */

/*****************************************************************************
* Copyright (c) 2013-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_ADAPTER_LOCK_EXT_H
#define INCLUDE_GUARD_ADAPTER_LOCK_EXT_H

#include <lib/spinlock.h>

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Linux Kernel API
//#include <linux/spinlock.h>     // spinlock_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ADAPTER_LOCK_DEFINE(Lock)   //DEFINE_SPINLOCK(Lock)

/* Lock structure, so it can be part of another structure or array */
typedef spinlock_t Adapter_Lock_Struct_t;

/* Initializer for elements of Adapter_Lock_Struct_t */
#define ADAPTER_LOCK_INITIALIZER __SPIN_LOCK_UNLOCKED(adapter)

#endif // INCLUDE_GUARD_ADAPTER_LOCK_EXT_H


/* end of file adapter_lock_ext.h */
