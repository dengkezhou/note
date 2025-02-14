/* adapter_lock_internal.h
 *
 * Adapter concurrency (locking) management
 * Internal interface
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

#ifndef INCLUDE_GUARD_ADAPTER_LOCK_INTERNAL_H
#define INCLUDE_GUARD_ADAPTER_LOCK_INTERNAL_H


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // bool


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Internal critical section data structure
typedef struct
{
    // Generic lock pointer
    void * Lock_p;

    // True if the lock is taken
    volatile bool fLocked;

} Adapter_Lock_CS_Internal_t;


#endif // INCLUDE_GUARD_ADAPTER_LOCK_INTERNAL_H


/* end of file adapter_lock_internal.h */
