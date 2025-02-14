/* adapter_alloc.h
 *
 * Linux kernel-space implementation of the Adapter buffer allocation
 * functionality.
 */

/*****************************************************************************
* Copyright (c) 2011-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef ADAPTER_ALLOC_H_
#define ADAPTER_ALLOC_H_

#include <malloc.h>
#include <linux/mtd/compat.h>

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Linux Kernel API
//#include <linux/kernel.h>
//#include <linux/slab.h>         // kmalloc, kfree
//#include <linux/hardirq.h>      // in_atomic


/*----------------------------------------------------------------------------
  Adapter_Alloc
*/
static inline void *
Adapter_Alloc(unsigned int size)
{
    if (size > 0) // Many callers do not check if requested size is non-zero
        // kmalloc() may return non-NULL for size=0
        return kmalloc(size, in_atomic() ? GFP_ATOMIC : GFP_KERNEL);
    else
        return NULL; // ... but only extreme optimists do not check the result!
}


/*----------------------------------------------------------------------------
  Adapter_Free
*/
static inline void
Adapter_Free(void *p)
{
    if (p != NULL)
    {
        kfree(p); // kfree() may take a NULL pointer but why bother
        p = NULL;
    }
}


#endif /* ADAPTER_ALLOC_H_ */


/* end of file adapter_alloc.h */
