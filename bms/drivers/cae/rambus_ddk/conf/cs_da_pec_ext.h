/* cs_da_pec_ext.h
 *
 * Demo Application Top-level Configuration, FPGA extensions
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


// this file is included by da_pec.c.c to get configuration switches

// Enable multiple packet test
#define DA_PEC_MULTIPLE_PKT_TEST

// Packet get retries
#define DA_PEC_PKT_GET_RETRY_COUNT     500

// Packet get wait timeout (in milliseconds)
#define DA_PEC_PKT_GET_TIMEOUT_MS      2


/* end of file cs_da_pec_ext.h */
