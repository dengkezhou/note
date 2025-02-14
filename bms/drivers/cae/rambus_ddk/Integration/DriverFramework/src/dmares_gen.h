/* dmares_gen.h
 *
 * Declare functions exported by "dmares_gen.c" that implements large parts
 * of the DMAResource API. The exported functions are to be used by module(s)
 * that implement the remaining parts of the DMAResource API.
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

#ifndef DMARES_GEN_H_
#define DMARES_GEN_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // bool

// Driver Framework DMAResource Types API
#include "dmares_types.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * DMAResourceLib_IsSaneInput
 */
bool
DMAResourceLib_IsSaneInput(
        const DMAResource_AddrPair_t * AddrPair_p,
        const char * const AllocatorRef_p,
        const DMAResource_Properties_t * Props_p);


/*----------------------------------------------------------------------------
 * DMAResourceLib_AlignForSize
 */
unsigned int
DMAResourceLib_AlignForSize(
        const unsigned int ByteCount,
        const unsigned int AlignTo);


/*----------------------------------------------------------------------------
 * DMAResourceLib_AlignForAddress
 */
unsigned int
DMAResourceLib_AlignForAddress(
        const unsigned int ByteCount,
        const unsigned int AlignTo);


/*----------------------------------------------------------------------------
 * DMAResourceLib_LookupDomain
 */
DMAResource_AddrPair_t *
DMAResourceLib_LookupDomain(
        const DMAResource_Record_t * Rec_p,
        const DMAResource_AddrDomain_t Domain);


#endif // DMARES_GEN_H_


/* end of file dmares_gen.h */
