/* shdevxs_rc.h
 *
 * Shared Device Access Record Cache API
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

#ifndef SHDEVXS_RC_H_
#define SHDEVXS_RC_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "shdevxs_rc.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Types Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * SHDevXS_TRC_Record_Invalidate
 *
 * This function invalidates the transform record in the TRC.
 *
 * ByteOffset (input)
 *     Record byte offset in the Transform Record Cache.
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_TRC_Record_Invalidate(
        const uint32_t ByteOffset);


/*----------------------------------------------------------------------------
 * SHDevXS_ARC4RC_Record_Invalidate
 *
 * This function invalidates the ARC4 state record in the ARC4RC.
 *
 * ByteOffset (input)
 *     Record byte offset in the ARC4 Record Cache.
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_ARC4RC_Record_Invalidate(
        const uint32_t ByteOffset);


/*----------------------------------------------------------------------------
 * SHDevXS_RC_Lock
 *
 * This function locks the TRC for mutually exclusive use.
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_RC_Lock(void);


/*----------------------------------------------------------------------------
 * SHDevXS_RC_Free
 *
 * This function frees the TRC from the mutually exclusive use.
 *
 * Return Value
 *     None
 */
void
SHDevXS_RC_Free(void);


/*----------------------------------------------------------------------------
 * SHDevXS_RC_Record_Dummy_Addr_Get
 *
 * This function returns the dummy record address.
 *
 * Return Value
 *     Record Cache record dummy (NULL) address.
 */
unsigned int
SHDevXS_RC_Record_Dummy_Addr_Get(void);


#endif /* SHDEVXS_RC_H_ */


/* end of file shdevxs_rc.h */
