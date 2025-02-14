/* shdevxs_init.h
 *
 * Kernel suport Driver initialization API.
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

#ifndef SHDEVXS_INIT_H_
#define SHDEVXS_INIT_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "shdevxs_init.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Types Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * SHDevXS_Global_SetPrivileged
 *
 * This function is called once by the Global Control Driver to
 * tell the kernel support driver that it has privileged access
 * to the EIP hardware.
 *
 * API use order:
 *     This function must be called first by the Global Control Driver, before
 *     any other SHDevXS functions.
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_Global_SetPrivileged(
        void);


/*----------------------------------------------------------------------------
 * SHDevXS_Global_Init
 *
 * This function is called once by the Global Control Driver to
 * tell the kernel support driver that it has done basic initialization
 * of the hardware, so the Kernel Support Driver is now allowed to access
 * hardware.
 *
 * API use order:
 *     This function must be called once by the Global Control Driver, before
 *     any other SHDevXS functions. It can be called again after
 *     SHDevXS_HW_UnInit
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_Global_Init(
        void);


/*----------------------------------------------------------------------------
 * SHDevXS_Global_UnInit
 *
 * This function is called once by the Global Control Driver when it
 * exits. At that point, the Kernel Support Driver is no longer allowed to
 * access hardware and no other applications may do so.
 *
 * API use order:
 *     This function must be called once by the Global Control Driver, before
 *     it exits.
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_Global_UnInit(
        void);


/*----------------------------------------------------------------------------
 * SHDevXS_Test
 *
 * Function to test whether communication with the kernel support driver
 * is possible.
 *
 * Return Value
 *     0  Success
 *    0>  Failure, code is implementation-specific
 */
int
SHDevXS_Test(void);


#endif /* SHDEVXS_INIT_H_ */


/* end of file shdevxs_init.h */
