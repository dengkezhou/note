/* adapter_ring_eip202.h
 *
 * Interface to EIP-202 ring-specific functionality.
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

#ifndef ADAPTER_RING_EIP202_H_
#define ADAPTER_RING_EIP202_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // bool


/*----------------------------------------------------------------------------
 * Adapter_Ring_EIP202_Configure
 *
 * This routine configures the Security-IP-202 ring-specific functionality
 * with parameters that are obtained via the Global Control
 * interface.
 *
 * HostDataWidth (input)
 *         Host interface data width:
 *              0 = 32 bits, 1 = 64 bits, 2 = 128 bits, 3 = 256 bits
 *
 * CF_Size (input)
 *         Command Descriptor FIFO size, the actual size is 2^CF_Size 32-bit
 *         words.
 *
 * RF_Size (input)
 *         Result Descriptor FIFO size, the actual size is 2^RF_Size 32-bit
 *         words.
 *
 * This function is re-entrant.
 */
void
Adapter_Ring_EIP202_Configure(cae_device *dev,
        const uint8_t HostDataWidth,
        const uint8_t CF_Size,
        const uint8_t RF_Size);


#endif /* ADAPTER_RING_EIP202_H_ */


/* end of file adapter_ring_eip202.h */
