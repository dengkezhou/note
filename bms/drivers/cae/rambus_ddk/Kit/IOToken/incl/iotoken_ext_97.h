/* iotoken_ext_97.h
 *
 * IOToken API for Extended Server
 *
 * All the functions in this API are re-entrant for different tokens.
 * All the functions in this API can be used concurrently for different tokens.
 *
 */

/*****************************************************************************
* Copyright (c) 2018-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef IOTOKEN_EXT_97_H_
#define IOTOKEN_EXT_97_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Standard IOToken API
#include "iotoken.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define IOTOKEN_MAX_BYPASS_WORD_COUNT 0

// Length of the EIP-197 Server extended command token (in 32-bit words)
// Note: Based on 64-bit Context (SA) address only!
#define IOTOKEN_IN_WORD_COUNT        (4 + IOTOKEN_MAX_BYPASS_WORD_COUNT)

// Length of the EIP-197 Server extended result token (in 32-bit words)
#define IOTOKEN_OUT_WORD_COUNT       (4 + IOTOKEN_MAX_BYPASS_WORD_COUNT)

#define IOTOKEN_FLOW_TYPE            0

// Input Token descriptor extension
typedef int
IOToken_Input_Dscr_Ext_t;

// Output Token descriptor extension
typedef int
IOToken_Output_Dscr_Ext_t;


/* end of file iotoken_ext_97.h */


#endif /* IOTOKEN_EXT_97_H_ */
