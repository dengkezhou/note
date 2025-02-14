/* adapter_lock.c
 *
 * Adapter concurrency (locking) management
 * Linux kernel-space implementation
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
#include "basic_defs.h"         // IDENTIFIER_NOT_USED

// Adapter Lock Internal API
#include "adapter_lock_internal.h"

// Adapter Memory Allocation API
#include "adapter_alloc.h"

// Logging API
//#undef LOG_SEVERITY_MAX
//#define LOG_SEVERITY_MAX    LOG_SEVERITY_WARN
#include "log.h"

// Linux Kernel API
//#include <linux/spinlock.h>     // spinlock_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Adapter_Lock_Alloc
 */
Adapter_Lock_t
Adapter_Lock_Alloc(void)
{
    spinlock_t * Lock_p;

    size_t LockSize=sizeof(spinlock_t);
    if (LockSize==0)
        LockSize=4;

    Lock_p = Adapter_Alloc(LockSize);
    if (Lock_p == NULL)
        return Adapter_Lock_NULL;

    //Log_FormattedMessage("%s: Lock = spinlock\n", __func__);

   // spin_lock_init(Lock_p);

    return Lock_p;
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_Free
 */
void
Adapter_Lock_Free(Adapter_Lock_t Lock)
{
    Adapter_Free((void*)Lock);
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_Acquire
 */
void
Adapter_Lock_Acquire(
        Adapter_Lock_t Lock,
        unsigned long * Flags)
{
    //spin_lock_irqsave((spinlock_t *)Lock, *Flags);
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_Release
 */
void
Adapter_Lock_Release(
        Adapter_Lock_t Lock,
        unsigned long * Flags)
{
    //spin_unlock_irqrestore((spinlock_t *)Lock, *Flags);
}


/* end of file adapter_lock.c */
