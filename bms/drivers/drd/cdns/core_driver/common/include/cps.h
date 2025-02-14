/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * cps_v3.h
 * Interface for Cadence Platform Services (CPS), version 3
 *
 * This is the "hardware abstraction layer" upon which all drivers are built.
 * It must be implemented for each platform.
 ******************************************************************************
 */
#ifndef CPS_V3_H
#define CPS_V3_H

#ifdef ERROR_INJECTION
#include "cps_ei.h"
#else

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cdn_stdtypes.h"
#include <cache.h>

static inline uint32_t CPS_ReadReg32(volatile uint32_t* address) {
    return *address;
}

/* see cps.h */
static inline void CPS_WriteReg32(volatile uint32_t* address, uint32_t value) {
    *address = value;
}

/* see cps.h */
static inline uint8_t CPS_UncachedRead8(volatile uint8_t* address) {
    return *address;
}

/* see cps.h */
static inline uint16_t CPS_UncachedRead16(volatile uint16_t* address) {
    return *address;
}

/* see cps.h */
static inline uint32_t CPS_UncachedRead32(volatile uint32_t* address) {
    return *address;
}

/* see cps.h */
static inline uint64_t CPS_UncachedRead64(volatile uint64_t* address) {
    return *address;
}

/* see cps.h */
static inline uint64_t CPS_ReadReg64(volatile uint64_t* address) {
    return *address;
}

/* see cps.h */
static inline void CPS_UncachedWrite8(volatile uint8_t* address, uint8_t value) {
    *address = value;
}

/* see cps.h */
static inline void CPS_UncachedWrite16(volatile uint16_t* address, uint16_t value) {
    *address = value;
}

/* see cps.h */
static inline void CPS_UncachedWrite32(volatile uint32_t* address, uint32_t value) {
    *address = value;
}

/* see cps.h */
static inline void CPS_UncachedWrite64(volatile uint64_t* address, uint64_t value) {
    *address = value;
}

/* see cps.h */
static inline void CPS_WriteReg64(volatile uint64_t* address, uint64_t value) {
    *address = value;
}

/* see cps.h */
static inline void CPS_WritePhysAddress32(volatile uint32_t* location, uint32_t addrValue) {
    *location = addrValue;
}

/* see cps.h */
static inline void CPS_BufferCopy(volatile uint8_t *dst, volatile const uint8_t *src, uint32_t size) {
    memcpy((void*)dst, (void*)src, size);
}

/* Since this is a bare-metal system, with no MMU in place, we expect that there will be no cache enabled */

static inline void CPS_CacheInvalidate(void* address, size_t size, uintptr_t devInfo) {
#ifdef TENSILICA
    xthal_dcache_region_invalidate(address, size);
#endif
    itcs_dcache_flush_range((phys_addr_t)address, (unsigned long)size);
    return;
}

static inline void CPS_CacheFlush(void* address, size_t size, uintptr_t devInfo) {
#ifdef TENSILICA
    xthal_dcache_region_writeback(address, size);
#endif
    itcs_dcache_flush_range((phys_addr_t)address, (unsigned long)size);
    return;
}

/* see cps.h */
static inline void CPS_DelayNs(uint32_t ns)
{
    //nsdelay(ns);
    udelay(ns/1000);
    return;
}

/* see cps.h */
static inline void CPS_MemoryBarrier(void) {

}

/* see cps.h */
static inline void CPS_MemoryBarrierWrite(void) {

}

/* see cps.h */
static inline void CPS_MemoryBarrierRead(void) {

}

#endif /* ERROR_INJECTION */

#endif /* multiple inclusion protection */