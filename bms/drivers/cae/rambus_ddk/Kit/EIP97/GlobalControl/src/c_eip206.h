/* c_eip206.h
 *
 * Default configuration EIP-206 Driver Library
 *
 */

/*****************************************************************************
* Copyright (c) 2012-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef C_EIP206_H_
#define C_EIP206_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level configuration
#include "cs_eip206.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Processing Packet Engine n (n - number of the PE)
// Input Side
//#define EIP206_IN_DBUF_BASE           0xA0000
//#define EIP206_IN_TBUF_BASE           0xA0100

// Output Side
//#define EIP206_OUT_DBUF_BASE          0xA1C00
//#define EIP206_OUT_TBUF_BASE          0xA1D00

// PE Options and Version
//#define EIP206_ARC4_BASE              0xA1FEC
//#define EIP206_VER_BASE               0xA1FF8


#endif /* C_EIP206_H_ */


/* end of file c_eip206.h */
