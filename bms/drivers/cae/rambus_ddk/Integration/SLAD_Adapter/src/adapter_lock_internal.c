/* adapter_lock_internal.c
 *
 * Adapter concurrency (locking) management
 * Generic implementation
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

// Adapter locking API
#include "adapter_lock.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // bool

// Adapter Lock Internal API
#include "adapter_lock_internal.h"

#define TEST_SIZEOF(type, size) \
    extern int must_bigger[1 - 2*((int)(sizeof(type) > size))]

// Check the size of the data structures
TEST_SIZEOF(Adapter_Lock_CS_Internal_t, sizeof(Adapter_Lock_CS_t));


/*----------------------------------------------------------------------------
 * Adapter_Lock_NULL
 *
 */
const Adapter_Lock_t Adapter_Lock_NULL = NULL;


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Set
 */
void
Adapter_Lock_CS_Set(
        Adapter_Lock_CS_t * const CS_p,
        Adapter_Lock_t Lock)
{
    Adapter_Lock_CS_Internal_t * CS_Internal_p =
                                 (Adapter_Lock_CS_Internal_t*)CS_p;

    if (CS_Internal_p)
    {
        // Lock cannot be set while the critical section is entered
        if (CS_Internal_p->fLocked == false)
            CS_Internal_p->Lock_p = Lock;
    }
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Get
 */
Adapter_Lock_t
Adapter_Lock_CS_Get(
        Adapter_Lock_CS_t * const CS_p)
{
    Adapter_Lock_CS_Internal_t * CS_Internal_p =
                                 (Adapter_Lock_CS_Internal_t*)CS_p;

    if (CS_Internal_p)
        return CS_Internal_p->Lock_p;
    else
        return Adapter_Lock_NULL;
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Enter
 */
bool
Adapter_Lock_CS_Enter(
        Adapter_Lock_CS_t * const CS_p)
{
    unsigned long Flags;
    Adapter_Lock_CS_Internal_t * CS_Internal_p =
                                (Adapter_Lock_CS_Internal_t*)CS_p;

    if (CS_Internal_p == NULL)
        return false;
    // Enter critical section
    Adapter_Lock_Acquire(CS_Internal_p->Lock_p, &Flags);
    // Check if critical section is already entered
    if (CS_Internal_p->fLocked)
    {
        Adapter_Lock_Release(CS_Internal_p->Lock_p, &Flags);
        return false; // CS already entered
    }
    else
        CS_Internal_p->fLocked = true; // success
    // Leave critical section
    Adapter_Lock_Release(CS_Internal_p->Lock_p, &Flags);

    return true;
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_CS_Leave
 */
void
Adapter_Lock_CS_Leave(
        Adapter_Lock_CS_t * const CS_p)
{
    Adapter_Lock_CS_Internal_t * CS_Internal_p =
                                (Adapter_Lock_CS_Internal_t*)CS_p;

    if (CS_Internal_p)
        CS_Internal_p->fLocked = false;
}


/* end of file adapter_lock_internal.c */
