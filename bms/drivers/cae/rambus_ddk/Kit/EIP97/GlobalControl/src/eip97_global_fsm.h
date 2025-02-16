/* eip97_global_fsm.h
 *
 * EIP-97 Global Control Driver Library API State Machine Internal Interface
 *
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

#ifndef EIP97_GLOBAL_FSM_H_
#define EIP97_GLOBAL_FSM_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "eip97_global_types.h"            // EIP97_Global_Error_t

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// EIP-97 Global Control Driver Library API States
typedef enum
{
    EIP97_GLOBAL_STATE_UNKNOWN = 1,
    EIP97_GLOBAL_STATE_SW_RESET_START,
    EIP97_GLOBAL_STATE_SW_RESET_DONE,
    EIP97_GLOBAL_STATE_HW_RESET_DONE,
    EIP97_GLOBAL_STATE_INITIALIZED,
    EIP97_GLOBAL_STATE_ENABLED,
    EIP97_GLOBAL_STATE_FATAL_ERROR
} EIP97_Global_State_t;


/*----------------------------------------------------------------------------
 * EIP97_Global_State_Set
 *
 * This function check whether the transition from the "CurrentState" to the
 * "NewState" is allowed and if yes changes the former to the latter.
 *
  * Return value
 *     EIP97_GLOBAL_NO_ERROR : operation is completed
 *     EIP97_GLOBAL_ILLEGAL_IN_STATE : state transition is not allowed
 */
EIP97_Global_Error_t
EIP97_Global_State_Set(
        volatile EIP97_Global_State_t * const CurrentState,
        const EIP97_Global_State_t NewState);


#endif /* EIP97_GLOBAL_FSM_H_ */


/* end of file eip97_global_fsm.h */
