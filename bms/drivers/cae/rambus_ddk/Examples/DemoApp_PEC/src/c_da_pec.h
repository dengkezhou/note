/* c_da_pec.h
 *
 * Default Demo Application Configuration
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

#include "cs_da_pec.h"

// this file is included by da_pec.c to get configuration switches

// log level for the entire adapter (for now)
// choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT
#ifndef LOG_SEVERITY_MAX
//#define LOG_SEVERITY_MAX                    LOG_SEVERITY_INFO
#endif

#ifndef DA_PEC_LICENSE
#define DA_PEC_LICENSE                      "Proprietary"
#endif

#ifndef DA_PEC_BANK_PACKET
#define DA_PEC_BANK_PACKET                  0
#endif

#ifndef DA_PEC_BANK_TOKEN
#define DA_PEC_BANK_TOKEN                   0
#endif

#ifndef DA_PEC_BANK_SA
#define DA_PEC_BANK_SA                      0
#endif

#ifndef DA_PEC_MIN_SA_BYTE_COUNT
#define DA_PEC_MIN_SA_BYTE_COUNT 256
#endif

// Define this to enable Wireless tests.
//#define DA_PEC_USE_WIRELESS

// Define this to enable SHA3 tests.
//#define DA_PEC_USE_SHA3

// enable gather-usage for AES-GCM
//#define DA_PEC_GATHER

// Enables multiple packet test
//#define DA_PEC_MULTIPLE_PKT_TEST

// Default DMA buffer allocation alignment (4 - 4 bytes)
#ifndef DA_PEC_DMA_ALIGNMENT_BYTE_COUNT
#define DA_PEC_DMA_ALIGNMENT_BYTE_COUNT                4
#endif

// Packet get retries
#ifndef DA_PEC_PKT_GET_RETRY_COUNT
#define DA_PEC_PKT_GET_RETRY_COUNT          10
#endif // DA_PEC_PKT_GET_RETRY_COUNT

// Packet get wait timeout (in milliseconds)
#ifndef DA_PEC_PKT_GET_TIMEOUT_MS
#define DA_PEC_PKT_GET_TIMEOUT_MS           10
#endif // DA_PEC_PKT_GET_RETRY_COUNT

// Enable Extended IOToken API implementation for Server with ICE and OCE
//#define DA_PEC_IOTOKEN_EXT_SRV_ICEOCE

// Enable Extended IOToken API implementation for Server with ICE
//#define DA_PEC_IOTOKEN_EXT_SRV_ICE

// Enable Extended IOToken API implementation for Mobile with ICE
//#define DA_PEC_IOTOKEN_EXT_MOB_ICE


/* end of file c_da_pec.h */
