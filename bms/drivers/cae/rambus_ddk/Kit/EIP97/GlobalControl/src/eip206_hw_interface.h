/* eip206_hw_interface.h
 *
 * EIP-206 Processing Engine HW interface
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

#ifndef EIP206_HW_INTERFACE_H_
#define EIP206_HW_INTERFACE_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include "c_eip206.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // uint16_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Read/Write register constants

/*****************************************************************************
 * Byte offsets of the EIP-206 Processing Engine registers
 *****************************************************************************/
// Processing Engine EIP number (0xCE) and complement (0x31)
#define EIP206_SIGNATURE              ((uint16_t)0x31CE)

#define EIP206_REG_OFFS               4
#define EIP206_REG_MAP_SIZE           8192

// Processing Packet Engine n (n - number of the PE)
// Input Side
#define EIP206_IN_REG_DBUF_TRESH(n)   ((EIP206_REG_MAP_SIZE * n) + \
                                       ((EIP206_IN_DBUF_BASE) + \
                                        (0x00 * EIP206_REG_OFFS)))

#define EIP206_IN_REG_TBUF_TRESH(n)   ((EIP206_REG_MAP_SIZE * n) + \
                                       ((EIP206_IN_TBUF_BASE) + \
                                        (0x00 * EIP206_REG_OFFS)))

// Output Side
#define EIP206_OUT_REG_DBUF_TRESH(n)  ((EIP206_REG_MAP_SIZE * n) + \
                                       ((EIP206_OUT_DBUF_BASE) + \
                                        (0x00 * EIP206_REG_OFFS)))

#define EIP206_OUT_REG_TBUF_TRESH(n)  ((EIP206_REG_MAP_SIZE * n) + \
                                       ((EIP206_OUT_TBUF_BASE) + \
                                        (0x00 * EIP206_REG_OFFS)))

// PE Options and Version
#define EIP206_REG_OPTIONS(n)         ((EIP206_REG_MAP_SIZE * n) + \
                                       ((EIP206_VER_BASE) + \
                                        (0x00 * EIP206_REG_OFFS)))
#define EIP206_REG_VERSION(n)         ((EIP206_REG_MAP_SIZE * n) + \
                                       ((EIP206_VER_BASE) + \
                                        (0x01 * EIP206_REG_OFFS)))

// Default EIP206_IN_REG_DBUF_TRESH register value
#define EIP206_IN_REG_DBUF_TRESH_DEFAULT        0x00000000

// Default EIP206_IN_REG_TBUF_TRESH register value
#define EIP206_IN_REG_TBUF_TRESH_DEFAULT        0x00000000

// Default EIP206_OUT_REG_DBUF_TRESH register value
#define EIP206_OUT_REG_DBUF_TRESH_DEFAULT       0x00000000

// Default EIP206_OUT_REG_TBUF_TRESH register value
#define EIP206_OUT_REG_TBUF_TRESH_DEFAULT       0x00000000


#endif /* EIP206_HW_INTERFACE_H_ */


/* end of file eip206_hw_interface.h */
