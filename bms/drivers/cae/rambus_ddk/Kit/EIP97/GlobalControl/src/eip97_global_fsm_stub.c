/* eip97_global_fsm_stub.c
 *
 * EIP-97 Global Control Driver Library API State Machine Internal Interface
 * stub implementation
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "eip97_global_fsm.h"

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"                // IDENTIFIER_NOT_USED

// EIP-97 Driver Library Types API
#include "eip97_global_types.h"        // EIP97_Global_* types

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * EIP97_Global_State_Set
 *
 */
EIP97_Global_Error_t
EIP97_Global_State_Set(
        EIP97_Global_State_t * const CurrentState,
        const EIP97_Global_State_t NewState)
{
    IDENTIFIER_NOT_USED(CurrentState);
    IDENTIFIER_NOT_USED((bool)NewState);

    return EIP97_GLOBAL_NO_ERROR;
}


/* end of file eip97_global_fsm_stub.c */
