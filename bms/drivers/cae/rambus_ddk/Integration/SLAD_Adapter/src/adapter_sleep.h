/* adapter_sleep.h
 *
 * Data types and Interfaces
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

#ifndef INCLUDE_GUARD_ADAPTER_SLEEP_H
#define INCLUDE_GUARD_ADAPTER_SLEEP_H

// Driver Framework Basic Defs API
#include "basic_defs.h"

/*----------------------------------------------------------------------------
 *                           Adapter time management
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 * Adapter_SleepMS
 *
 * This function will sleep the calling context for at most the requested
 * amount of time (milliseconds) and then returns.
 *
 */
void
Adapter_SleepMS(
        const unsigned int Duration_ms);

#endif /* Include Guard */

/* end of file adapter_sleep.h */
