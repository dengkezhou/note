/* umdevxs_chrdev.h
 *
 * Linux UMDevXS Driver Character Device Interfaces.
 */

/*****************************************************************************
* Copyright (c) 2015-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_UMDEVXS_CHRDEV_H
#define INCLUDE_GUARD_UMDEVXS_CHRDEV_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "umdevxs_cmd.h"        // UMDevXS_CmdRsp_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef int (* UMDevXS_HandleCmdFunction_t)(
        void * AppID,
        UMDevXS_CmdRsp_t * const CmdRsp_p);


/*----------------------------------------------------------------------------
 * UMDevXS_ChrDev_Init
 *
 * This routine hooks the character device.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code return by a kernel call
 */
int
UMDevXS_ChrDev_Init(void);


/*----------------------------------------------------------------------------
 * UMDevXS_ChrDev_UnInit
 *
 * This routine unhooks the character device.
 */
void
UMDevXS_ChrDev_UnInit(void);

/*----------------------------------------------------------------------------
 * UMDevXS_ChrDev_HandleCmdFunc_Set
 *
 * This routine installs the external handle function for commands.
 */
void
UMDevXS_ChrDev_HandleCmdFunc_Set
        (UMDevXS_HandleCmdFunction_t Func);


#endif /* INCLUDE_GUARD_UMDEVXS_CHRDEV_H */


/* end of file umdevxs_chrdev.h */
