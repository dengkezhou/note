#include <common.h>
#ifdef CONFIG_64BIT
#include <core_rv64.h>
#else
#include <core_rv32.h>
#endif
#include <cache.h>
#include <sbi/sbi_ecall_interface.h>
#include <sysm.h>

#ifdef CONFIG_ICACHE
int itcs_icache_status(void) {
  uint64_t cache;
#ifdef CONFIG_RISCV_SMODE
  cache = __get_SHCR();
#else
  cache = __get_MHCR();
#endif
  return cache & 0x1;
}

void itcs_icache_enable(void) {
  if (!itcs_icache_status())
#ifdef CONFIG_RISCV_SMODE
    itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_ENABLE, 0, 0, 0);
#else
    csi_icache_enable();
#endif
}

void itcs_icache_disable(void) {
  if (itcs_icache_status())
#ifdef CONFIG_RISCV_SMODE
    itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_DISABLE, 0, 0, 0);
#else
    csi_icache_disable();
#endif
}

void itcs_icache_invalid(void) {
#ifndef CONFIG_CACHE_LITE
  if (itcs_icache_status())
    csi_icache_invalid();

#ifdef CONFIG_L2CACHE
  //itcs_l2cache_invalid();
#endif
#endif
}
#endif

#ifdef CONFIG_DCACHE
int itcs_dcache_status(void) {
  uint64_t cache;
#ifdef CONFIG_RISCV_SMODE
  cache = __get_SHCR();
#else
  cache = __get_MHCR();
#endif
  return cache & (0x1 << 1);
}

void itcs_dcache_enable(void) {
  if (!itcs_dcache_status())
#ifdef CONFIG_RISCV_SMODE
    itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
#else
    csi_dcache_enable();
#endif
}

void itcs_dcache_disable(void) {
  if (itcs_dcache_status())
#ifdef CONFIG_RISCV_SMODE
    itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
#else
    csi_dcache_disable();
#endif
}

void itcs_dcache_clean(void) {
#ifndef CONFIG_CACHE_LITE
  if (itcs_dcache_status())
    csi_dcache_clean();

#ifdef CONFIG_L2CACHE
  itcs_l2cache_clean();
#endif
#endif
}

void itcs_dcache_invalid(void) {
#ifndef CONFIG_CACHE_LITE
  if (itcs_dcache_status())
    csi_dcache_invalid();

#ifdef CONFIG_L2CACHE
  itcs_l2cache_invalid();
#endif
#endif
}

void itcs_dcache_flush(void) {
#ifndef CONFIG_CACHE_LITE
  if (itcs_dcache_status())
    csi_dcache_clean_invalid();

#ifdef CONFIG_L2CACHE
  itcs_l2cache_flush();
#endif
#endif
}

#ifdef CONFIG_L2CACHE
void itcs_l2cache_invalid(void) { 
#if 0
	csi_l2cache_invalid(); 
#endif
}

void itcs_l2cache_clean(void) { 
#if 0
	csi_l2cache_clean(); 
#endif
}

void itcs_l2cache_flush(void) { 
#if 0
	csi_l2cache_clean_invalid(); 
#else
	uint32_t l2cache = readl(ITCS_C_CPU_CLUSTER0_BASE + 0x50);
	writel(l2cache | 0x1, ITCS_C_CPU_CLUSTER0_BASE + 0x50);
	while (!(readl(ITCS_C_CPU_CLUSTER0_BASE + 0x50) & (0x1 << 4)));
	writel(l2cache & (~0x1), ITCS_C_CPU_CLUSTER0_BASE + 0x50);
#endif
}
#endif

void itcs_dcache_flush_range(phys_addr_t start, unsigned long size) {
#ifndef CONFIG_CACHE_LITE
  csi_dcache_clean_invalid_range(start, size);
#endif
}

void itcs_dcache_clean_range(phys_addr_t start, unsigned long size) {
#ifndef CONFIG_CACHE_LITE
  csi_dcache_clean_range(start, size);
#endif
}

void itcs_dcache_invalid_range(phys_addr_t start, unsigned long size) {
#ifndef CONFIG_CACHE_LITE
  csi_dcache_invalid_range(start, size);
#endif
}

#endif
