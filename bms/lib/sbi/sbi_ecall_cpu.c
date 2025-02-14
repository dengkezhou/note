/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 *   Atish Patra <atish.patra@wdc.com>
 */

#include <sbi/sbi_error.h>
#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <cache.h>
#include <common.h>
#include <pmu.h>

static int sbi_ecall_cpu_handler(unsigned long extid, unsigned long funcid,
                                 const struct pt_regs *regs,
                                 unsigned long *out_val,
                                 struct sbi_trap_info *out_trap) {
  int ret = 0;
  switch (funcid) {
  case SBI_EXT_ICACHE_ENABLE:
    csi_icache_enable();
    break;
  case SBI_EXT_ICACHE_DISABLE:
    csi_icache_disable();
    break;
  case SBI_EXT_DCACHE_ENABLE:
    csi_icache_enable();
    csi_dcache_enable();
    break;
  case SBI_EXT_DCACHE_DISABLE:
    itcs_dcache_clean();
    csi_dcache_disable();
    csi_icache_disable();
    // for invalid l2cache
    itcs_l2cache_invalid();
    break;
  case SBI_EXT_PMU_ENABLE:
#ifdef CONFIG_TBH_CPU
    hpm_init();
#endif
    break;
  case SBI_EXT_PMU_DISABLE:
#ifdef CONFIG_TBH_CPU
    hpm_deinit();
#endif
    break;
  case SBI_EXT_PMP_CHANGE: {
    mpu_region_attr_t attr;

    attr.r = 1;
    attr.w = 1;
    attr.x = 1;
    attr.a = ADDRESS_MATCHING_TOR;
    attr.l = 0;
    csi_mpu_config_region(7, 0x120000000, REGION_SIZE_4KB, &attr, 1);
    attr.w = 0;
    csi_mpu_config_region(8, 0x140000000, REGION_SIZE_4KB, &attr, 1);
  }break;
  
  case SBI_EXT_ICACHE_INVALID:
    csi_icache_invalid();
  break;

  default:
    return SBI_ENOTSUPP;
  }

  return ret;
}

struct sbi_ecall_extension ecall_cpu = {
    .extid_start = SBI_CPU,
    .extid_end   = SBI_CPU,
    .handle      = sbi_ecall_cpu_handler,
};
