/* api_global_driver97_init.h
 *
 * Security-IP-97 Global Control Driver Initialization Interface
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

#ifndef DRIVER97_GLOBAL_INIT_H_
#define DRIVER97_GLOBAL_INIT_H_


/*----------------------------------------------------------------------------
 * Driver97_Global_Init
 *
 * Initialize the global control driver. This function must be called before
 * any other driver API function can be called.
 *
 * Returns 0 for success and -1 for failure.
 */
int
Driver97_Global_Init(void);


/*----------------------------------------------------------------------------
 * Driver97_Global_Exit
 *
 * Uninitialize the global control driver. After this function is called
 * no other driver API function can be called except Driver97_Global_Init().
 */
void
Driver97_Global_Exit(void);


#endif /* DRIVER97_GLOBAL_INIT_H_ */


/* end of file api_driver97_init.h */
