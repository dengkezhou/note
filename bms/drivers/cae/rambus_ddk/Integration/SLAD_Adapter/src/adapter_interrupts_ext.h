/* adapter_interrupts_ext.h
 *
 * Host hardware specific extensions for the Adapter Interrupts interface
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

#ifndef ADAPTER_INTERRUPTS_EXT_H_
#define ADAPTER_INTERRUPTS_EXT_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Adapter EIP-202 Default configuration
#include "c_adapter_eip202.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ADAPTER_EIP202_ADD_IRQ(_name,_phy,_aicname,_tasklet,_pol)  \
    _name

// Adapter logical EIP-(1)97 interrupts
enum
{
    ADAPTER_EIP202_IRQS
};

#undef ADAPTER_EIP202_ADD_IRQ

#endif /* ADAPTER_INTERRUPTS_EXT_H_ */

/* end of file adapter_interrupts_ext.h */
