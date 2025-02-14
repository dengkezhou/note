/* cs_eip96_ext.h
 *
 * Top-level EIP-96 Driver Library configuration extensions
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

#ifndef CS_EIP96_EXT_H_
#define CS_EIP96_EXT_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Read/Write register constants

/*****************************************************************************
 * Byte offsets of the EIP-96 Packet Engine registers
 *****************************************************************************/

// Processing Packet Engine n (n - number of the DSE thread)
#define EIP96_CONF_BASE                    0x11000

// EIP-96 PRNG
#define EIP96_PRNG_BASE                    0x11040

// EIP-96 Options and Version
#define EIP96_VER_BASE                     0x113F8


#endif /* CS_EIP96_EXT_H_ */


/* end of file cs_eip96_ext.h */
