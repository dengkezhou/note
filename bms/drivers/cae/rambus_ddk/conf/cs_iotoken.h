/* cs_iotoken.h
 *
 * Top-level configuration file
 */

/*****************************************************************************
* Copyright (c) 2016-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef CS_IOTOKEN_H_
#define CS_IOTOKEN_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#ifdef DRIVER_64BIT_DEVICE
#define IOTOKEN_64BIT_DEVICE
#endif

// Enable strict argument checking (input parameters)
#define IOTOKEN_STRICT_ARGS

// Number of 32-bit words passed from Input to Output Token
// without modifications
//#define IOTOKEN_BYPASS_WORD_COUNT        4


/* end of file cs_iotoken.h */


#endif /* CS_IOTOKEN_H_ */
