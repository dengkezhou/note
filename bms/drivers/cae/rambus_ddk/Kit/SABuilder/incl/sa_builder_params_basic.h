/* sa_builder_params_basic.h
 *
 * Basic crypto and hash specific extension to the SABuilder_Params_t type.
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


#ifndef SA_BUILDER_PARAMS_BASIC_H_
#define SA_BUILDER_PARAMS_BASIC_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "sa_builder_params.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/* Flag bits for the BasicFlags field. Combine any values using a
   bitwise or.
 */
#define SAB_BASIC_FLAG_EXTRACT_ICV   BIT_0 /* Extract and verify ICV from packet*/
#define SAB_BASIC_FLAG_ENCRYPT_AFTER_HASH BIT_1
/* Encrypt the hashed data (default is hashing the encrypted data). */

/* Extension record for SAParams_t. Protocol_Extension_p must point
   to this structure when the Basic crypto/hash protocol is used.

   SABuilder_Iinit_Basic() will fill all fields in this structure  with
   sensible defaults.
 */
typedef struct
{
    uint32_t BasicFlags;
    uint32_t DigestBlockCount;
    uint32_t ICVByteCount; /* Length of ICV in bytes. */
    uint32_t  fresh;      /* 32-bit 'fresh' value for wireless authentication
                             algorithms. */
    uint8_t bearer;       /* 5-bit 'bearer' value for wireless algorithms. */
    uint8_t direction;   /* 1-bit 'direction' value for wireless algorithms. */
} SABuilder_Params_Basic_t;


#endif /* SA_BUILDER_PARAMS_BASIC_H_ */


/* end of file sa_builder_params_basic.h */
