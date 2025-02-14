/* cs_da_pec.h
 *
 * Demo Application Top-level Configuration
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

#ifndef CS_DA_PEC_H_
#define CS_DA_PEC_H_

/*----------------------------------------------------------------------------
* This module uses (requires) the following interface(s):
 */


// Platform-specific conf parameters
#include "cs_da_pec_ext.h"

// Engine-specific conf parameters
#include "cs_da_pec_ext2.h"

// Define this to enable Wireless tests.
//#define DA_PEC_USE_WIRELESS
// Define this to enable SHA3 tests.
//#define DA_PEC_USE_SHA3

// log level for the entire adapter (for now)
// choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT
//#define LOG_SEVERITY_MAX  LOG_SEVERITY_INFO

#define DA_PEC_LICENSE "Proprietary"

// enable gather-usage for AES-GCM
//#define DA_PEC_GATHER


#endif // CS_DA_PEC_H_


/* end of file cs_da_pec.h */
