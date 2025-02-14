/* dmares_record.h
 *
 * Driver Framework, DMAResource Record Definition
 *
 * The document "Driver Framework Porting Guide" contains the detailed
 * specification of this API. The information contained in this header file
 * is for reference only.
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

#ifndef INCLUDE_GUARD_DMARES_REC_H
#define INCLUDE_GUARD_DMARES_REC_H


#include "cs_adapter.h"     // enable switches for conditional fields
#include "basic_defs.h"     // uint8_t, uint32_t

/*----------------------------------------------------------------------------
 * AddrTrans_Domain_t
 *
 * This is a list of domains that can be supported by the implementation.
 * Can be used with variables of the DMAResource_AddrDomain_t type
 *
 */
typedef enum
{
    DMARES_DOMAIN_UNKNOWN = 0,
    DMARES_DOMAIN_HOST,
    DMARES_DOMAIN_HOST_UNALIGNED,
    DMARES_DOMAIN_BUS
} AddrTrans_Domain_t;


// Maximum number of address/domain pairs stored per DMA resource.
#define DMARES_ADDRPAIRS_CAPACITY 3

typedef struct
{
    uint32_t Magic;     // signature used to validate handles

    // DMA resource properties: Size, Alignment, Bank & fCached
    DMAResource_Properties_t Props;

    // Storage for upto N address/domain pairs.
    DMAResource_AddrPair_t AddrPairs[DMARES_ADDRPAIRS_CAPACITY];

    // if true, 32-bit words are swapped when transferred to/from
    // the DMA resource
    bool fSwapEndianness;

    // this implementation supports the following allocator references:
    // 'A' -> this DMA resource has been obtained through DMAResource_Alloc
    // 'R' -> this DMA resource has been obtained through
    //        DMAResource_CheckAndRegister using Linux DMA API
    // 'k' -> this DMA resource has been obtained through
    //        DMAResource_CheckAndRegister using Linux kmalloc() allocator
    // 'N' -> used to register buffers that do not need to be DMA-safe
    // 'T' -> this DMA resource has been obtained through DMAResource_Attach
    char AllocatorRef;

    // maximum data amount that can be stored in bytes, e.g. allocated size
    unsigned int BufferSize;

#ifndef ADAPTER_REMOVE_BOUNCEBUFFERS
    struct
    {
        // bounce buffer for DMAResource_CheckAndRegister'ed buffers
        // note: used only when concurrency is impossible
        //       (PE source packets allow concurrency!!)
        DMAResource_Handle_t Bounce_Handle;
    } bounce;
#endif

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
    struct
    {
        // for secure detection of PEC_SGList handles
        bool IsSGList;
    } sg;
#endif

    bool fIsNewSA;

#ifndef ADAPTER_USE_LARGE_TRANSFORM_DISABLE
    bool fIsLargeTransform;
#endif

    // Implementation-specific DMA resource context
    void * Context_p;

    // Type of DMA bank
    unsigned int BankType;

} DMAResource_Record_t;

#define DMARES_RECORD_MAGIC 0xde42b5e7


#endif // INCLUDE_GUARD_DMARES_REC_H


/* end of file dmares_record.h */
