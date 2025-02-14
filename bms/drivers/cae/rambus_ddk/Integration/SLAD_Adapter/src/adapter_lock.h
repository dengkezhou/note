/* adapter_lock.h
 *
 * Adapter concurrency (locking) management
 *
 * Adapter_Lock functions usage examples
 *
 * Example 1:
 *
 * static Adapter_Lock_t Lock;
 * static unsigned long Flags;
 *
 * Adapter_Lock_Alloc(Lock);
 * Adapter_Lock_Acquire(Lock, &Flags);
 * ...
 * Adapter_Lock_Release(Lock, &Flags);
 * Adapter_Lock_Free(Lock);
 *
 * Example 2:
 *
 * static ADAPTER_LOCK_DEFINE(Lock_p);
 * static unsigned long Flags;
 *
 * Adapter_Lock_Acquire(Lock_p, &Flags);
 * ...
 * Adapter_Lock_Release(Lock_p, &Flags);
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

#ifndef INCLUDE_GUARD_ADAPTER_LOCK_H
#define INCLUDE_GUARD_ADAPTER_LOCK_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // bool


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Lock, use Adapter_Lock_NULL to set to a known uninitialized value
typedef void * Adapter_Lock_t;

// Critical section
typedef struct
{
    volatile void * p [2]; // Place holder

} Adapter_Lock_CS_t;


/*----------------------------------------------------------------------------
 * Adapter_Lock_t
 *
 * This handle can be assigned to a variable of type Adapter_Lock_t.
 *
 */
extern const Adapter_Lock_t Adapter_Lock_NULL;


/*----------------------------------------------------------------------------
 * Adapter_Lock_Alloc
 */
Adapter_Lock_t
Adapter_Lock_Alloc(void);


/*----------------------------------------------------------------------------
 * Adapter_Lock_Free
 */
void
Adapter_Lock_Free(
        Adapter_Lock_t Lock);


/*----------------------------------------------------------------------------
 * Adapter_Lock_Acquire
 *
 * Acquire the lock.
 *
 * Lock (input):
 *      Lock to acquire
 *
 * Flags (input):
 *      Pointer to memory location where implementation-specific flags
 *      can be stored.
 *
 * Return value:
 *     none
 */
void
Adapter_Lock_Acquire(
        Adapter_Lock_t Lock,
        unsigned long * Flags);


/*----------------------------------------------------------------------------
 * Adapter_Lock_Release
 *
 * Release the lock previously acquired via Adapter_Lock_Acquire().
 *
 * Lock (input):
 *      Lock to be released
 *
 * Flags (input):
 *      Pointer to memory location where flags were stored by
 *      the corresponding Adapter_Lock_Acquire() call.
 *
 * Return value:
 *     none
 */
void
Adapter_Lock_Release(
        Adapter_Lock_t Lock,
        unsigned long * Flags);


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Set
 *
 * Set the lock for the critical section.
 *
 * Note: This function must be called prior to calling Adapter_Lock_CS_Enter()
 *       or Adapter_Lock_CS_Leave() functions.
 *       The lock cannot be changes while the critical section is entered.
 *
 * CS_p (output):
 *      Critical section where the Lock data must be set.
 *
 * Lock (input):
 *      Pointer to a lock instantiated by the ADAPTER_LOCK_DEFINE macro or
 *      allocated by Adapter_Lock_Alloc() function
 *
 * Return value:
 *     none
 */
void
Adapter_Lock_CS_Set(
        Adapter_Lock_CS_t * const CS_p,
        Adapter_Lock_t Lock);


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Get
 *
 * Get the lock for the critical section.
 *
 * CS_p (input):
 *      Critical section for which the Lock object must be obtained.
 *
 * Return value:
 *     Lock
 */
Adapter_Lock_t
Adapter_Lock_CS_Get(
        Adapter_Lock_CS_t * const CS_p);


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Enter
 *
 * Enter critical section
 *
 * Return code:
 *     true - section entered
 *     false - section not entered, another context is already executing it
 */
bool
Adapter_Lock_CS_Enter(
        Adapter_Lock_CS_t * const CS_p);


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Leave
 *
 * Leave critical section
 *
 * Return value:
 *     none
 */
void
Adapter_Lock_CS_Leave(
        Adapter_Lock_CS_t * const CS_p);


// Adapter Locking API extensions
#include "adapter_lock_ext.h"           // ADAPTER_LOCK_DEFINE


#endif // INCLUDE_GUARD_ADAPTER_LOCK_H


/* end of file adapter_lock.h */
