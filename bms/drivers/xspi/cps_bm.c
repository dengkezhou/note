/******************************************************************************
 * Copyright (C) 2014-2018 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * cps_bm.c
 *
 * Sample implementation of Cadence Platform Services for a bare-metal
 * system
 ******************************************************************************
 */
#ifdef __BARE_METAL__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cps.h"

/* see cps.h */
uint32_t CPS_ReadReg32(volatile uint32_t *address) { return *address; }

/* see cps.h */
void CPS_WriteReg32(volatile uint32_t *address, uint32_t value) {
  *address = value;
}

/* see cps.h */
uint8_t CPS_UncachedRead8(volatile uint8_t *address) { return *address; }

/* see cps.h */
uint16_t CPS_UncachedRead16(volatile uint16_t *address) { return *address; }

/* see cps.h */
uint32_t CPS_UncachedRead32(volatile uint32_t *address) { return *address; }

/* see cps.h */
uint64_t CPS_UncachedRead64(volatile uint64_t *address) { return *address; }

/* see cps.h */
extern uint64_t CPS_ReadReg64(volatile uint64_t *address) { return *address; }

/* see cps.h */
void CPS_UncachedWrite8(volatile uint8_t *address, uint8_t value) {
  *address = value;
}

/* see cps.h */
void CPS_UncachedWrite16(volatile uint16_t *address, uint16_t value) {
  *address = value;
}

/* see cps.h */
void CPS_UncachedWrite32(volatile uint32_t *address, uint32_t value) {
  *address = value;
}

/* see cps.h */
void CPS_UncachedWrite64(volatile uint64_t *address, uint64_t value) {
  *address = value;
}

/* see cps.h */
extern void CPS_WriteReg64(volatile uint64_t *address, uint64_t value) {
  *address = value;
}

/* see cps.h */
void CPS_WritePhysAddress32(volatile uint32_t *location, uint32_t addrValue) {
  *location = addrValue;
}

/* see cps.h */
void CPS_BufferCopy(volatile uint8_t *dst, volatile const uint8_t *src,
                    uint32_t size) {
  memcpy((void *)dst, (void *)src, size);
}

/* Since this is a bare-metal system, with no MMU in place, we expect that there
 * will be no cache enabled */

void CPS_CacheInvalidate(void *address, size_t size, uintptr_t devInfo) {
#ifdef TENSILICA
  xthal_dcache_region_invalidate(address, size);
#endif
  return;
}

void CPS_CacheFlush(void *address, size_t size, uintptr_t devInfo) {
#ifdef TENSILICA
  xthal_dcache_region_writeback(address, size);
#endif
  return;
}

/* see cps.h */
void CPS_DelayNs(uint32_t ns) { return; }

/* see cps.h */
void CPS_MemoryBarrier(void) {}

/* see cps.h */
void CPS_MemoryBarrierWrite(void) {}

/* see cps.h */
void CPS_MemoryBarrierRead(void) {}

#endif /* __BARE_METAL__ */
