/* api_driver97_pec_init.h
 *
 * Security-IP-97 Driver Initialization or PEC only Interface
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

#ifndef API_DRIVER97_PEC_INIT_H_
#define API_DRIVER97_PEC_INIT_H_


/*----------------------------------------------------------------------------
 * Driver97_PEC_Init
 *
 * Initialize the driver. This function must be called before any other
 * driver API function can be called.
 *
 * Returns 0 for success and -1 for failure.
 */
int
Driver97_PEC_Init(void);

/*----------------------------------------------------------------------------
 * Driver97_PEC_Exit
 *
 * Initialize the driver. After this function is called no other driver API
 * function can be called except Driver97_Init().
 */
void
Driver97_PEC_Exit(void);


#endif /* API_DRIVER97_PEC_INIT_H_ */


/* end of file api_driver97_pec_init.h */
