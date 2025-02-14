/* eip202_cdr_fsm.h
 *
 * EIP-202 Ring Control Driver Library API State Machine Internal Interface
 * for Command Descriptor Ring (CDR)
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

#ifndef EIP202_CDR_FSM_H_
#define EIP202_CDR_FSM_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "eip202_ring_types.h"            // EIP202_Ring_Error_t

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// EIP-202 Ring Control Driver Library API States
typedef enum
{
    EIP202_CDR_STATE_UNKNOWN = 1,
    EIP202_CDR_STATE_UNINITIALIZED,
    EIP202_CDR_STATE_INITIALIZED,
    EIP202_CDR_STATE_FREE,
    EIP202_CDR_STATE_FULL,
    EIP202_CDR_STATE_FATAL_ERROR
} EIP202_CDR_State_t;


/*----------------------------------------------------------------------------
 * EIP202_CDR_State_Set
 *
 * This function check whether the transition from the "CurrentState" to the
 * "NewState" is allowed and if yes changes the former to the latter.
 *
  * Return value
 *     EIP202_RING_NO_ERROR : operation is completed
 *     EIP202_RING_ILLEGAL_IN_STATE : state transition is not allowed
 */
EIP202_Ring_Error_t
EIP202_CDR_State_Set(
        volatile EIP202_CDR_State_t * const CurrentState,
        const EIP202_CDR_State_t NewState);


#endif /* EIP202_CDR_FSM_H_ */


/* end of file eip202_cdr_fsm.h */
