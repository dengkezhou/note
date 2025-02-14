/* dmares_addr.h
 *
 * Driver Framework, DMAResource API, Address Translation functions
 * Translates an {address + domain} to an address in a requested domain.
 *
 * The document "Driver Framework Porting Guide" contains the detailed
 * specification of this API. The information contained in this header file
 * is for reference only.
 */

/*****************************************************************************
* Copyright (c) 2007-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_DMARES_ADDR_H
#define INCLUDE_GUARD_DMARES_ADDR_H

#include "dmares_types.h"       // DMAResource_AddrDomain/AddrPair/Handle_t

/*----------------------------------------------------------------------------
 * DMAResource_Translate
 *
 * Attempts to provide an address for a DMA Resource that can be used in the
 * requested address domain. Typically used to get the address that can be
 * used by a device to perform DMA.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_Alloc, DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * DestDomain (input)
 *     The requested domain to translate the address to.
 *     Please check the implementation notes for supported domains.
 *
 * PairOut_p (output)
 *     Pointer to the memory location when the converted address plus domain
 *     will be written.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation dependent)
 */
int
DMAResource_Translate(cae_device *dev,
        const DMAResource_Handle_t Handle,
        const DMAResource_AddrDomain_t DestDomain,
        DMAResource_AddrPair_t * const PairOut_p);


/*----------------------------------------------------------------------------
 * DMAResource_AddPair
 *
 * This function can be used to register another address pair known to the
 * caller for a DMA Resource.
 * The information will be stored in the DMA Resource Record and can be used
 * by DMAResource_Translate.
 * Typically used when an external DMA-safe buffer allocator returns two
 * addresses (for example virtual and physical).
 * Note: How many address pairs are supported is implementation specific.
 *
 * Handle (input)
 *     The handle to the DMA Resource record that was returned by
 *     DMAResource_CheckAndRegister or DMAResource_Attach.
 *
 * Pair (input)
 *     Address pair (address + domain) to be associated with the DMA Resource.
 *
 * Return Values
 *     0    Success
 *     <0   Error code (implementation dependent)
 */
int
DMAResource_AddPair(cae_device *dev,
        const DMAResource_Handle_t Handle,
        const DMAResource_AddrPair_t Pair);


#endif /* Include Guard */

/* end of file dmares_addr.h */
