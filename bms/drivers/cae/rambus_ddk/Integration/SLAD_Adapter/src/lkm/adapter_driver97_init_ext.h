/* adapter_driver97_init_ext.h
 *
 * Linux kernel specific Adapter extensions
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


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include "cs_adapter.h"

// Linux Kernel API
//#include <linux/init.h>     // module_init, module_exit
//#include <linux/module.h>   // EXPORT_SYMBOL


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_dmabuf.h"     // DMABuf API


//MODULE_LICENSE(ADAPTER_LICENSE);

//module_init(Driver97_Init);
//module_exit(Driver97_Exit);
//
//EXPORT_SYMBOL(DMABuf_NULLHandle);
//EXPORT_SYMBOL(DMABuf_Handle_IsSame);
//EXPORT_SYMBOL(DMABuf_Alloc);
//EXPORT_SYMBOL(DMABuf_Register);
//EXPORT_SYMBOL(DMABuf_Release);


// PEC API LKM implementation extensions
#include "adapter_pec_lkm_ext.h"


/* end of file adapter_driver97_init_ext.h */
