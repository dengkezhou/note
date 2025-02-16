/* eip97_global_fsm.c
 *
 * EIP-97 Global Control Driver Library API State Machine Internal Interface
 * implementation
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

// EIP-97 Driver Library Types API
#include "eip97_global_types.h"        // EIP97_Global_* types


/*----------------------------------------------------------------------------
 * EIP97_Global_State_Set
 *
 */
EIP97_Global_Error_t
EIP97_Global_State_Set(
        volatile EIP97_Global_State_t * const CurrentState,
        const EIP97_Global_State_t NewState)
{
    switch(*CurrentState)
    {
        case EIP97_GLOBAL_STATE_UNKNOWN:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_SW_RESET_START:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_SW_RESET_DONE:
                    *CurrentState = NewState;
                    break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

         case EIP97_GLOBAL_STATE_HW_RESET_DONE:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_INITIALIZED:
                   *CurrentState = NewState;
                   break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

        case EIP97_GLOBAL_STATE_SW_RESET_START:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_SW_RESET_DONE:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_SW_RESET_START:
                    *CurrentState = NewState;
                    break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

        case EIP97_GLOBAL_STATE_SW_RESET_DONE:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_SW_RESET_DONE:
                case EIP97_GLOBAL_STATE_INITIALIZED:
                    *CurrentState = NewState;
                    break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

        case EIP97_GLOBAL_STATE_INITIALIZED:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_ENABLED:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_SW_RESET_DONE:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_INITIALIZED:
                    *CurrentState = NewState;
                    break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

        case EIP97_GLOBAL_STATE_ENABLED:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_SW_RESET_START:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_SW_RESET_DONE:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_FATAL_ERROR:
                    break;
                case EIP97_GLOBAL_STATE_ENABLED:
                    break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

        case EIP97_GLOBAL_STATE_FATAL_ERROR:
            switch(NewState)
            {
                case EIP97_GLOBAL_STATE_SW_RESET_START:
                    *CurrentState = NewState;
                    break;
                case EIP97_GLOBAL_STATE_SW_RESET_DONE:
                    *CurrentState = NewState;
                    break;
                default:
                    return EIP97_GLOBAL_ILLEGAL_IN_STATE;
            }
            break;

        default:
            return EIP97_GLOBAL_ILLEGAL_IN_STATE;
    }

    return EIP97_GLOBAL_NO_ERROR;
}


/* end of file eip97_global_fsm.c */
