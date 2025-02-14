/* shdevxs_cmd.h
 *
 * Opcodes (additional to those used by UMDevXS drive) for SHDevXS.
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

#ifndef SHDEVXS_CMD_H_
#define SHDEVXS_CMD_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include "umdevxs_cmd.h"


enum {
    UMDEVXS_OPCODE_SHDEVXS_GLOBAL_INIT = UMDEVXS_OPCODE_LAST,
    UMDEVXS_OPCODE_SHDEVXS_GLOBAL_UNINIT,
    UMDEVXS_OPCODE_SHDEVXS_TEST,
    UMDEVXS_OPCODE_SHDEVXS_DMAPOOL_INIT,
    UMDEVXS_OPCODE_SHDEVXS_DMAPOOL_UNINIT,
    UMDEVXS_OPCODE_SHDEVXS_DMAPOOL_GETBASE,
    UMDEVXS_OPCODE_SHDEVXS_RC_TRC_INVALIDATE,
    UMDEVXS_OPCODE_SHDEVXS_RC_ARC4RC_INVALIDATE,
    UMDEVXS_OPCODE_SHDEVXS_RC_LOCK,
    UMDEVXS_OPCODE_SHDEVXS_RC_FREE,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_INIT,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_UNINIT,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_ENABLE,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_DISABLE,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_CLEAR,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_CLEARANDENABLE,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_SETHANDLER,
    UMDEVXS_OPCODE_SHDEVXS_IRQ_WAIT,
    UMDEVXS_OPCODE_SHDEVXS_PRNG_RESEED,
};

#endif /* SHDEVXS_CMD_H_ */

/* shdevxs_cmd.h */
