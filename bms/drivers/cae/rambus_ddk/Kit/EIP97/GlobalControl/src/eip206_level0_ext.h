/* eip206_level0_ext.h
 *
 * EIP-206 Processing Engine Level0 Internal interface extensions
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

#ifndef EIP206_LEVEL0_EXT_H_
#define EIP206_LEVEL0_EXT_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // IDENTIFIER_NOT_USED, bool

// Driver Framework Device API
#include "device_types.h"       // Device_Handle_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


static inline void
EIP206_ARC4_SIZE_WR(
        Device_Handle_t Device,
        const unsigned int PEnr,
        const bool fLarge)
{
    IDENTIFIER_NOT_USED(Device);
    IDENTIFIER_NOT_USED(PEnr);
    IDENTIFIER_NOT_USED(fLarge);

    return; // Not supported on this engine, stub implementation
}


#endif /* EIP206_LEVEL0_EXT_H_ */


/* end of file eip206_level0_ext.h */
