/* cs_eip206_ext.h
 *
 * Top-level EIP-206 Driver Library configuration extensions
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

#ifndef CS_EIP206_EXT_H_
#define CS_EIP206_EXT_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Read/Write register constants

/*****************************************************************************
 * Byte offsets of the EIP-206 Processing Engine registers
 *****************************************************************************/

// Processing Packet Engine n (n - number of the PE)
// Input Side
#define EIP206_IN_DBUF_BASE           0x10000
#define EIP206_IN_TBUF_BASE           0x10100

// Output Side
#define EIP206_OUT_DBUF_BASE          0x11C00
#define EIP206_OUT_TBUF_BASE          0x11D00

// PE Options and Version
#define EIP206_VER_BASE               0x11FF8


#endif /* CS_EIP206_EXT_H_ */


/* end of file cs_eip206_ext.h */
