/* adapter_sleep.c
 *
 * Linux kernel specific Adapter module
 * responsible for adapter-wide time management.
 */

/*****************************************************************************
* Copyright (c) 2008-2020 by Rambus, Inc. and/or its subsidiaries.
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

#include <common.h>

// Adapter Sleep API
#include "adapter_sleep.h"

// Driver Framework Basic Defs API
#include "basic_defs.h"

// Linux Kernel API
//#include <linux/delay.h>        // msleep, no-busy-waiting implementation


/*----------------------------------------------------------------------------
 * Adapter_SleepMS
 */
void
Adapter_SleepMS(
        const unsigned int Duration_ms)
{
    udelay(Duration_ms * 1000);
}


/* end of file adapter_sleep.c */
