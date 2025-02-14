/* shdevxs_prng.h
 *
 * API to access EIP-96 Pseudo Random Number Generator.
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

#ifndef SHDEVXS_PRNG_H_
#define SHDEVXS_PRNG_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "shdevxs_prng.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Types Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
// EIP-96 PRNG Re-seed data
typedef struct
{
    // Seed value low 32-bit word
    uint32_t SeedLo;

    // Seed value high 32-bit word
    uint32_t SeedHi;

    // Key register 0 value low 32-bit word
    uint32_t Key0Lo;

    // Key register 0 value high 32-bit word
    uint32_t Key0Hi;

    // Key register 1 value low 32-bit word
    uint32_t Key1Lo;

    // Key register 1 value high 32-bit word
    uint32_t Key1Hi;

    // Seed value low 32-bit word
    uint32_t LFSRLo;

    // Seed value high 32-bit word
    uint32_t LFSRHi;
} SHDevXS_PRNG_Reseed_t;

/*----------------------------------------------------------------------------
 * SHDevXS_PRNG_Ressed
 *
 * Reseed the internal PRNG of the EIP-96 to obtain predicatble IV's in
 * known answer tests.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_PRNG_Reseed(
        SHDevXS_PRNG_Reseed_t * const Reseed_p);



#endif /* SHDEVXS_PRNG_H_ */


/* end of file shdevxs_prng.h */
