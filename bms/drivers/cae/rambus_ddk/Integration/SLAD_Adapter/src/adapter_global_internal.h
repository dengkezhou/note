/* adapter_global_internal.h
 *
 * Internal interface between parts of the Global Control adapter.
 */

/*****************************************************************************
* Copyright (c) 2014-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_ADAPTER_GLOBAL_INTERNAL_H
#define INCLUDE_GUARD_ADAPTER_GLOBAL_INTERNAL_H

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Adapter_Global_Interfaces_Get
 *
 * Read the number of available packet interfaces.
 *
 * NofRings_p (output)
 *    Number of available ring pairs.
 * NofLAInterfaces_p (output)
 *    Number of available Look-Aside FIFO interfaces.
 * NofInlineInterfaces_p (output)
 *    Number of available Inline interfaces.
 *
 * If all returned values are zero, the device has not been initialized.
 * This is considered an error.
 */
void
Adapter_Global_Interfaces_Get(
    unsigned int * const NofRings_p,
    unsigned int * const NofLAInterfaces_p,
    unsigned int * const NofInlineInterfaces_p);


#endif /* Include Guard */


/* end of file adapter_global_internal.h */
