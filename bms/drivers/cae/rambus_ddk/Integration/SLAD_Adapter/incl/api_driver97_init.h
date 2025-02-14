/* api_driver97_init.h
 *
 * Security-IP-97 Driver Initialization Interface
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

#ifndef DRIVER97_INIT_H_
#define DRIVER97_INIT_H_


/*----------------------------------------------------------------------------
 * Driver97_Init
 *
 * Initialize the driver. This function must be called before any other
 * driver API function can be called.
 *
 * Returns 0 for success and -1 for failure.
 */
int
Driver97_Init(cae_device *dev);

/*----------------------------------------------------------------------------
 * Driver97_Exit
 *
 * Initialize the driver. After this function is called no other driver API
 * function can be called except Driver97_Init().
 */
void
Driver97_Exit(cae_device *dev);


#endif /* DRIVER97_INIT_H_ */


/* end of file api_driver97_init.h */
