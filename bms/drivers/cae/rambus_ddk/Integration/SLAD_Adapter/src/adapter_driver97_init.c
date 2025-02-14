/* adapter_driver97_init.c
 *
 * Adapter top level module, Security-IP-97 driver's entry point.
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
 * This module implements (provides) the following interface(s):
 */

#include <cae.h>

#include "api_driver97_init.h"    // Driver Init API


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default Adapter configuration
#include "cs_adapter.h"      // ADAPTER_DRIVER_NAME

// Adapter Initialization API
#include "adapter_init.h"   // Adapter_*
#include "adapter_global_init.h"

// Logging API
#include "log.h"            // LOG_INFO


/*----------------------------------------------------------------------------
 * Driver97_Init
 */
int
Driver97_Init(cae_device *dev)
{
    LOG_INFO("\n\t Driver97_Init \n");

    LOG_INFO("%s driver: initializing\n", ADAPTER_DRIVER_NAME);

    Adapter_Report_Build_Params();

    if (!Adapter_Init(dev))
    {
        return -1;
    }

    if (!Adapter_Global_Init(dev))
    {
        Adapter_UnInit(dev);
        return -1;
    }

    LOG_INFO("\n\t Driver97_Init done \n");

    return 0;   // success
}


/*----------------------------------------------------------------------------
 * Driver97_Exit
 */
void
Driver97_Exit(cae_device *dev)
{
    LOG_INFO("\n\t Driver97_Exit \n");

    LOG_INFO("%s driver: exit\n", ADAPTER_DRIVER_NAME);

    Adapter_Global_UnInit(dev);
    Adapter_UnInit(dev);

    LOG_INFO("\n\t Driver97_Exit done \n");
}

#include "adapter_driver97_init_ext.h"

/* end of file adapter_driver97_init.c */
