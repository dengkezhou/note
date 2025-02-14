/* dmares_record.h
 *
 * Driver Framework, DMAResource Record Definition (example)
 *
 * This file is an customizable declaration of the DMAResource_Record_t type
 * as part DMA Resource API.
 * Do not include this file directly; include dmares_types.h instead.
 *
 * The document "Driver Framework Porting Guide" contains the detailed
 * specification of this API. The information contained in this header file
 * is for reference only.
 */

/*****************************************************************************
* Copyright (c) 2008-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_DMARES_TYPES_H
#error "Please include dmares_types.h instead of dmares_record.h"
#endif

/*----------------------------------------------------------------------------
 * Address Domains
 *
 * This is a list of domains that are supported by the implementation.
 * The domain describes the applicability of the address.
 */
enum
{
    DMARES_DOMAIN_DEVICE_CM,
    DMARES_DOMAIN_DEVICE_PE,
    DMARES_DOMAIN_DEVICE_PKA,
    DMARES_DOMAIN_PHYSICAL,
    DMARES_DOMAIN_BUS,
    DMARES_DOMAIN_INTERHOST,
    DMARES_DOMAIN_USER,
    DMARES_DOMAIN_KERNEL,
    DMARES_DOMAIN_DRIVER,
    DMARES_DOMAIN_APPLICATION,
    DMARES_DOMAIN_UNKNOWN
};

#define DMARES_ADDRPAIRS_CAPACITY 4

typedef struct
{
    uint32_t Magic;     // signature used to validate handles

    struct
    {
        // for freeing the buffer
        void * AllocatedAddr_p;
        unsigned int AllocatedSize;     // in bytes

        char AllocatorRef;
    } alloc;

    DMAResource_Properties_t Props;

    // list of applicable addresses for this resource
    DMAResource_AddrPair_t AddPairs[DMARES_ADDRPAIRS_CAPACITY];

    struct
    {
        // aligned start-address, data starts here
        void * HostAddr_p;
    } host;

    struct
    {
        // used by Read32/Write32[Array]
        bool fSwapEndianness;
    } swap;

} DMAResource_Record_t;


/* end of file dmares_record.h */
