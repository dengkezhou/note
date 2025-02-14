/* umdevxs_interrupt.h
 *
 * Exported API for interrupt of the UMDexXS/UMPCI driver.
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

#ifndef INCLUDE_GUARD_UMDEVXS_INTERRUPT_H
#define INCLUDE_GUARD_UMDEVXS_INTERRUPT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
//#include <linux/interrupt.h>

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * UMDevXS_Interrupt_Request
 *
 * Request an IRQ handler to be registered for the IRQ of the device managed
 * by this driver. It temporarily unregisters the driver's own IRQ handler.
 * Unregister any handler if a null pointer is passed and restore the driver's
 * own handler
 *
 * Handler_p (input)
 *    Pointer to the interrupt (top half) handler to be registered for the
 *    device. If NULL is passed, restore the driver's own handler.
 *
 * Index (input)
 *    Index of the interrupt for which a handler should be registered.
 *    0 for the first interrupt, 1 for the second, etc.
 *
 * Return: OS IRQ number on success (nonnegative).
 *         -1 on failure.
 */
int
UMDevXS_Interrupt_Request(irq_handler_t Handler_p, int Index);


#endif /* INCLUDE_GUARD_UMDEVXS_INTERRUPT_H */

/* umdevxs_interrupt.h */
