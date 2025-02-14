/* cs_eip202_global_ext.h
 *
 * Top-level EIP-202 Driver Library Global Control configuration extensions
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

#ifndef CS_EIP202_GLOBAL_EXT_H_
#define CS_EIP202_GLOBAL_EXT_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Read/Write register constants

/*****************************************************************************
 * Byte offsets of the EIP-202 HIA registers
 *****************************************************************************/

// HIA DFE all threads
#define EIP202_DFE_BASE           0x0F000

// HIA DFE thread n (n - number of the DFE thread)
#define EIP202_DFE_TRD_BASE       0x0F200

// HIA DSE all threads
#define EIP202_DSE_BASE           0x0F400

// HIA DSE thread n (n - number of the DSE thread)
#define EIP202_DSE_TRD_BASE       0x0F600

// HIA Global
#define EIP202_G_BASE             0x0FFF4


#endif /* CS_EIP202_GLOBAL_EXT_H_ */


/* end of file cs_eip202_global_ext.h */
