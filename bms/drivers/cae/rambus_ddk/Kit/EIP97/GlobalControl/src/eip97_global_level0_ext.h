/* eip97_global_level0_ext.h
 *
 * EIP-97 Global Control Level0 Internal interface extensions
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

#ifndef EIP97_GLOBAL_LEVEL0_EXT_H_
#define EIP97_GLOBAL_LEVEL0_EXT_H_


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // BIT definitions, bool, uint32_t

// Driver Framework Device API
#include "device_types.h"       // Device_Handle_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */

static inline void
EIP97_OPTIONS_RD(cae_device *dev,
        Device_Handle_t Device,
        uint8_t * const NofPes,
        uint8_t * const InTbufSize,
        uint8_t * const InDbufSize,
        uint8_t * const OutTbufSize,
        uint8_t * const OutDbufSize,
        bool * const fCentralPRNG,
        bool * const fTG,
        bool * const fTRC)
{
    uint32_t RevRegVal;

    RevRegVal = EIP97_Read32(dev, Device, EIP97_REG_OPTIONS);

    *fTRC         = ((RevRegVal & BIT_31) != 0);
    *fTG          = ((RevRegVal & BIT_27) != 0);
    *fCentralPRNG = ((RevRegVal & BIT_26) != 0);
    *OutDbufSize  = (uint8_t)((RevRegVal >> 16) & MASK_4_BITS);
    *OutTbufSize  = (uint8_t)((RevRegVal >> 13) & MASK_3_BITS) + 3;
    *InDbufSize   = (uint8_t)((RevRegVal >> 9)  & MASK_4_BITS);
    *InTbufSize   = (uint8_t)((RevRegVal >> 6)  & MASK_3_BITS) + 3;
    *NofPes       = (uint8_t)((RevRegVal)       & MASK_5_BITS);
}


#endif /* EIP97_GLOBAL_LEVEL0_EXT_H_ */


/* end of file eip97_global_level0_ext.h */



