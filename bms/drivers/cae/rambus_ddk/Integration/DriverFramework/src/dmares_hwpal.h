/* dmares_hwpal.h
 *
 * HW and OS abstraction API
 * for the Driver Framework DMAResource API implementation
 *
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

#ifndef DMARES_HWPAL_H_
#define DMARES_HWPAL_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // uint32_t, NULL, inline, bool

// Driver Framework DMAResource Types API
#include "dmares_types.h"

// Driver Framework C Library abstraction API
#include "clib.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Dynamic flag cannot be mixed with any other HWPAL_DMARESOURCE_BANK_* flags
#define HWPAL_DMARESOURCE_BANK_DYNAMIC                  0

// Maximum number of supported dynamic DMA banks
#define HWPAL_DMARESOURCE_MAX_NOF_BANKS                 30

// Static flags can be mixed with each other for the same bank
#define HWPAL_DMARESOURCE_BANK_STATIC                   (HWPAL_DMARESOURCE_MAX_NOF_BANKS + 1)
#define HWPAL_DMARESOURCE_BANK_STATIC_FIXED_ADDR        (HWPAL_DMARESOURCE_MAX_NOF_BANKS + 3)

#define HWPAL_DMARESOURCE_BANK_STATIC_LAST              HWPAL_DMARESOURCE_BANK_STATIC_FIXED_ADDR


// Internal DMAResource_Properties_t extension
typedef struct
{
    void * Addr;
    unsigned int BankType;
} HWPAL_DMAResource_Properties_Ext_t;


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MaxAlignment_Get
 */
unsigned int
HWPAL_DMAResource_MaxAlignment_Get(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_DCache_Alignment_Get
 */
unsigned int
HWPAL_DMAResource_DCache_Alignment_Get(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MemAlloc
 */
void *
HWPAL_DMAResource_MemAlloc(
        size_t ByteCount);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MemFree
 */
void
HWPAL_DMAResource_MemFree(
        void * Buf_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Alloc
 */
void *
HWPAL_DMAResource_Lock_Alloc(void);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Free
 */
void
HWPAL_DMAResource_Lock_Free(void * Lock_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Acquire
 */
void
HWPAL_DMAResource_Lock_Acquire(
        void * Lock_p,
        unsigned long * Flags);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Release
 */
void
HWPAL_DMAResource_Lock_Release(
        void * Lock_p,
        unsigned long * Flags);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Alloc
 */
int
HWPAL_DMAResource_Alloc(cae_device *dev,
        const DMAResource_Properties_t RequestedProperties,
        const HWPAL_DMAResource_Properties_Ext_t RequestedPropertiesExt,
        DMAResource_AddrPair_t * const AddrPair_p,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Release
 */
int
HWPAL_DMAResource_Release(cae_device *dev,
        const DMAResource_Handle_t Handle);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Init
 */
bool
HWPAL_DMAResource_Init(cae_device *dev);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_UnInit
 */
void
HWPAL_DMAResource_UnInit(cae_device *dev);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_CheckAndRegister
 */
int
HWPAL_DMAResource_CheckAndRegister(cae_device *dev,
        const DMAResource_Properties_t RequestedProperties,
        const DMAResource_AddrPair_t AddrPair,
        const char AllocatorRef,
        DMAResource_Handle_t * const Handle_p);


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Record_Update
 */
int
HWPAL_DMAResource_Record_Update(
        const int Identifier,
        DMAResource_Record_t * const Rec_p);


#endif // DMARES_HWPAL_H_


/* end of file dmares_hwpal.h */
