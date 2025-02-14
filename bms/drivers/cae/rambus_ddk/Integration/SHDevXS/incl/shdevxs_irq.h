/* shdevxs_irq.h
 *
 * Shared Device Access Interrupts.
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

#ifndef SHDEVXS_IRQ_H_
#define SHDEVXS_IRQ_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "shdevxs_irq.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Types Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
typedef void (*SHDevXS_InterruptHandler_t)(const int nIRQ,
                                           const unsigned int flags);

/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_Init
 *
 * Initialize the IRQ handling subsystem. Must be called from the Global Control
 * Driver once target accesses (along with endianness conversion) have been
 * enabled.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_IRQ_Init(void);

/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_UnInit
 *
 * Un-initialize the IRQ handling subsystem. Must be called from the
 * Global Control Driver before shutting off any communication with the device.
 *
 */
int
SHDevXS_IRQ_UnInit(void);

/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_Enable
 *
 * Enable the specified IRQ on the hardware.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_IRQ_Enable(const int nIRQ,
                   const unsigned int Flags);

/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_Disable
 *
 * Disable the specified IRQ on the hardware.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_IRQ_Disable(const int nIRQ,
                    const unsigned int Flags);


/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_Clear
 *
 * Clear the specified IRQ on the hardware.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_IRQ_Clear(const int nIRQ,
                   const unsigned int Flags);

/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_Enable
 *
 * Clear and enable the specified IRQ on the hardware.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_IRQ_ClearAndEnable(const int nIRQ,
                           const unsigned int Flags);



/*----------------------------------------------------------------------------
 * SHDevXS_IRQ_SetHandler
 *
 * Install the specified handler for the specified IRQ.
 * If the handle is NULL, remove the handler from the interrupt.
 *
 * Return 0 on success, -1 on failure.
 */
int
SHDevXS_IRQ_SetHandler(
        const int nIRQ,
        SHDevXS_InterruptHandler_t HandlerFunction);


#endif /* SHDEVXS_IRQ_H_ */


/* end of file shdevxs_irq.h */
