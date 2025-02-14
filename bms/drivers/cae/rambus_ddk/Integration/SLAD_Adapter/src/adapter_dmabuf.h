/* adapter_dmabuf.h
 *
 * Adapter DMABuf internal interface
 */

/*****************************************************************************
* Copyright (c) 2010-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef ADAPTER_DMABUF_H_
#define ADAPTER_DMABUF_H_

#include <cae.h>

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"            // bool

// Driver Framework DMAResource API
#include "dmares_types.h"          // DMAResource_Handle_t

// DMABuf API
#include "api_dmabuf.h"            // DMABuf_Handle_t


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ADAPTER_DMABUF_ALIGNMENT_INVALID       -1


/*----------------------------------------------------------------------------
 * Function name
 *
 */

DMAResource_Handle_t
Adapter_DMABuf_Handle2DMAResourceHandle(
        DMABuf_Handle_t Handle);


DMABuf_Handle_t
Adapter_DMAResource_Handle2DMABufHandle(
        DMAResource_Handle_t Handle);


void *
Adapter_DMAResource_HostAddr(cae_device *dev,
        DMAResource_Handle_t Handle);


bool
Adapter_DMAResource_IsSubRangeOf(cae_device *dev,
        const DMAResource_Handle_t Handle1,
        const DMAResource_Handle_t Handle2);


bool
Adapter_DMAResource_IsForeignAllocated(cae_device *dev,
        DMAResource_Handle_t Handle);


void
Adapter_DMAResource_Alignment_Set(
        const int Alignment);


int
Adapter_DMAResource_Alignment_Get(void);


#endif /* ADAPTER_DMABUF_H_ */


/* end of file adapter_dmabuf.h */
