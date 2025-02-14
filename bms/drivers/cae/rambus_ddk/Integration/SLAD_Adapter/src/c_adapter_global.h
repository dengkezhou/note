/* c_adapter_global.h
 *
 * Default Adapter Global configuration
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

#ifndef INCLUDE_GUARD_C_ADAPTER_GLOBAL_H
#define INCLUDE_GUARD_C_ADAPTER_GLOBAL_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include "cs_adapter.h"

#ifndef ADAPTER_GLOBAL_DRIVER_NAME
#define ADAPTER_GLOBAL_DRIVER_NAME     "Security-IP"
#endif

#ifndef ADAPTER_GLOBAL_LICENSE
#define ADAPTER_GLOBAL_LICENSE         "Proprietary"
#endif

#ifndef ADAPTER_GLOBAL_PRNG_SEED
// 8 words to seed the PRNG to provide IVs, input to
#define ADAPTER_GLOBAL_PRNG_SEED {0x48c24cfd, 0x6c07f742, \
                                  0xaee75681, 0x0f27c239, \
                                  0x79947198, 0xe2991275, \
                                  0x21ac3c7c, 0xd008c4b4}
#endif

#ifndef ADAPTER_GLOBAL_DEVICE_NAME
#define ADAPTER_GLOBAL_DEVICE_NAME           "EIP197_GLOBAL"
#endif // ADAPTER_GLOBAL_DEVICE_NAME

#ifndef ADAPTER_GLOBAL_RESET_MAX_RETRIES
#define ADAPTER_GLOBAL_RESET_MAX_RETRIES      1000
#endif // ADAPTER_GLOBAL_RESET_MAX_RETRIES

#ifndef ADAPTER_GLOBAL_EIP97_NOF_PES
#define ADAPTER_GLOBAL_EIP97_NOF_PES          1
#endif

#ifndef ADAPTER_GLOBAL_EIP97_RINGMASK
#define ADAPTER_GLOBAL_EIP97_RINGMASK         0x0001
#endif

#ifndef ADAPTER_GLOBAL_EIP97_PRIOMASK
#define ADAPTER_GLOBAL_EIP97_PRIOMASK         0
#endif

// Enables PCI device support
//#define ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

// Enables board control device support
//#define ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE

// Enables board reset via the board control device
//#define ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE


#endif /* Include Guard */


/* end of file c_adapter_global.h */
