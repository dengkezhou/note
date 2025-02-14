/* cs_ringhelper.h
 *
 * Ring Helper Configuration File
 */

/*****************************************************************************
* Copyright (c) 2010-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_CS_RINGHELPER_H
#define INCLUDE_GUARD_CS_RINGHELPER_H

#include "cs_driver.h"

// when enabled, all function call parameters are sanity-checked
// comment-out to disable this code
#ifndef DRIVER_PERFORMANCE
#define RINGHELPER_STRICT_ARGS
#endif

// the following switch removes support for the Status Callback Function
//#define RINGHELPER_REMOVE_STATUSFUNC

// the following switch removes support for separate rings
// use when only overlapping rings are used
//#define RINGHELPER_REMOVE_SEPARATE_RING_SUPPORT


#endif /* Include Guard */


/* end of file cs_ringhelper.h */
