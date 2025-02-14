#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <hash.h>
#include <dhrystone/dhry.h>
#include <coremark/coremark.h>
#include <mmu_table.h>
#include <core_rv64.h>
#include <cache.h>
#include <asm/io.h>
#include <stdbool.h>
#include <pmu.h>
#include <riscv_vector.h>
#include <sysm.h>
#include <sbi/sbi_ecall_interface.h>
#include <rand48.h>
#include <rtc-sysm.h>
#include <sysm.h>

#ifdef CONFIG_COMPILE_RTL
#define LOOP_CNT   2
#define CRC_LENGTH 0x800
#define CRC32_HASH 0x9f5edd58
#else
#define LOOP_CNT   20
#define CRC_LENGTH 0x80000
#define CRC32_HASH 0xd743a794
#endif

#define CPUBENCH

int test_crc(char op) {
  uint32_t tmp, len = CRC_LENGTH;
  uint8_t *buf = NULL;

  buf = malloc(len);
  if (buf == NULL)
    return -1;

  for (int i = 0; i < len; i++)
    buf[i] = i & 0xff;

  for (int i = 0; i < LOOP_CNT; i++) {
    lib_hash_init("crc32", len);
    lib_hash_data(buf, len);
    lib_hash_value(&tmp);
  }
  printf("CRC: 0x%x, ", tmp);
  free(buf);
  return ((tmp == CRC32_HASH) ? 0 : -1);
}

int test_crc2(char op) {
  if (!test_crc(0))
    return test_crc(0);
  else
    return -1;
}

int test_dcache_range(char op) {
  uint32_t i;
  uint8_t *buf;
  uint32_t len = CRC_LENGTH;

  buf = malloc(len);
  for (i = 0; i < len / 32; i++)
    buf[i * 32] = (uint8_t)i;

  if (op == 'f')
    itcs_dcache_flush_range(virt_to_phys(buf), len);
  else if (op == 'i')
    itcs_dcache_invalid_range(virt_to_phys(buf), len);
  else if (op == 'c')
    itcs_dcache_clean_range(virt_to_phys(buf), len);

  for (i = 0; i < len / 32; i++)
    buf[i * 32] = (uint8_t)i;
  free(buf);
  return 0;
}

/* malloc buf 32byte aligned, L1cache 16byte cacheline */
#define L1ICACHE_SIZE     0x8000
#define L1DCACHE_SIZE     0x8000
#define L2CACHE_SIZE      0x100000
#define L2CACHE_CACHELINE 64

inline void jump(unsigned long base) {
  asm volatile("jalr ra, %0;" ::"r"(base));
}

int test_icache_full_scope(char op) {
  uint16_t *buf;
  int i               = 0;
  unsigned long l1cac = 0, l1icmc = 0;
  unsigned long subl1cac = 0, subl1icmc = 0;
  int hitrate = 0;

  buf = (uint16_t *)malloc(L1ICACHE_SIZE);
  for (i = 0; i < L1ICACHE_SIZE / 2; i++)
    buf[i] = 0x0001;   // asm("nop");
  buf[i - 1] = 0x8082; // asm("ret");

  asm("sync.is");
  // run one loop in buf
  jump((unsigned long)buf);
  l1cac  = hpm_get_count(RISCV_PMU_L1ICAC);
  l1icmc = hpm_get_count(RISCV_PMU_L1ICMC);

  // run second loop in buf
  jump((unsigned long)buf);
  subl1cac  = hpm_get_count(RISCV_PMU_L1ICAC) - l1cac;
  subl1icmc = hpm_get_count(RISCV_PMU_L1ICMC) - l1icmc;
  hitrate   = subl1cac * 100 / (subl1cac + subl1icmc);
  free(buf);
  return ((hitrate > 90) ? 0 : -1);
}

int test_dcache_full_scope(char op) {
  uint8_t *buf;
  int i                 = 0;
  unsigned long l1dcwac = 0, l1dcwmc = 0;
  unsigned long subl1dcwac = 0, subl1dcwmc = 0;
  int hitrate = 0;

  buf = malloc(L1DCACHE_SIZE);
  // set one loop dcache
  for (i = 0; i < L1DCACHE_SIZE; i++)
    buf[i] = 0x01;
  l1dcwac = hpm_get_count(RISCV_PMU_L1DCWAC);
  l1dcwmc = hpm_get_count(RISCV_PMU_L1DCWMC);

  // set second loop dcache
  for (i = 0; i < L1DCACHE_SIZE; i++)
    buf[i] = 0x01;
  subl1dcwac = hpm_get_count(RISCV_PMU_L1DCWAC) - l1dcwac;
  subl1dcwmc = hpm_get_count(RISCV_PMU_L1DCWMC) - l1dcwmc;
  // printf("l1dcwac 0x%lx, l1dcwmc 0x%lx, subl1dcwac 0x%lx, subl1dcwmc
  // 0x%lx\n", l1dcwac, l1dcwmc, subl1dcwac, subl1dcwmc);
  hitrate = subl1dcwac * 100 / (subl1dcwac + subl1dcwmc);
  free(buf);
  return ((hitrate > 90) ? 0 : -1);
}

int test_l2cache_full_scope(char op) {
  uint8_t *buf;
  int i                = 0;
  int skip             = 0;
  unsigned long l2cwac = 0, l2cwmc = 0;
  unsigned long subl2cwac = 0, subl2cwmc = 0;
  int hitrate = 0;

  buf  = (uint8_t *)malloc(L2CACHE_SIZE + L2CACHE_CACHELINE);
  skip = (unsigned long)(buf + L2CACHE_CACHELINE - 1) / 64 * 64 -
         (unsigned long)buf;

  // set one loop L2cache
  for (i = skip; i < L2CACHE_SIZE; i++)
    buf[i] = rand() % 0xff;

  l2cwac = hpm_get_count(RISCV_PMU_L2CWAC);
  l2cwmc = hpm_get_count(RISCV_PMU_L2CWMC);

  // set second loop L2cache
  for (i = skip; i < L2CACHE_SIZE; i++)
    buf[i] = rand() % 0xff;

  subl2cwac = hpm_get_count(RISCV_PMU_L2CWAC) - l2cwac;
  subl2cwmc = hpm_get_count(RISCV_PMU_L2CWMC) - l2cwmc;
  // printf("l2cwac 0x%lx, l2cwmc 0x%lx, subl2cwac 0x%lx, subl2cwmc 0x%lx\n",
  // l2cwac, l2cwmc, subl2cwac, subl2cwmc);
  hitrate = subl2cwac * 100 / (subl2cwac + subl2cwmc);
  free(buf);
  return ((hitrate > 90) ? 0 : -1);
}

int test_pmp(char op) {
  itcs_send_ecall(SBI_CPU, SBI_EXT_PMP_CHANGE, 0, 0, 0);
  *(unsigned long *)(0x120000000 - 8) = 1;
  asm("sync.is");
  printf("Test Physical Protect Memory Pass If show panic log next\n");
  *(unsigned long *)(0x120000000 + 8) = 1;
  asm("sync.is");
  return 0;
}

int test_sysmap(char op) {
  int ret = 0;
  uint32_t val;

  if (itcs_sysm_identity() == CPU) {
    val = rtc_info_get(RSTCLR, 0);
    if (val != 1) {
      while (rtc_info_get(RSTCLR, 0) != 0x12)
        udelay(5);

      hang();
    } else {
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_ENABLE, 0, 0, 0);
      ret = test_crc(0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_DISABLE, 0, 0, 0);
    }
  } else {
    rtc_info_set(RSTCLR, 0, 0x12);
    // maybe cpu0 not in idle
    while (itcs_core_disable(CPU, 0) < 0)
      udelay(5);

    rtc_info_set(RSTCLR, 0, 0x1);
    itcs_core_enable(CPU, 0, ITCS_CDDR_ADDR, 0);
  }
  return ret;
}

int test_vector_isa(char op) {
  // compiler do not support now
  // asm("vsetivli zero, 2, e32, m1");
  asm("vsetvli x0, a0, e8,m1");
  return 0;
}

typedef int (*cpu_case_t)(char mode);

long cpu_test_case(cpu_case_t fn, char mode, bool dump) {
  unsigned long times;
  int ret;

  times = get_timer(0);
  ret   = fn(mode);
  times = get_timer(times);

  if (dump)
    printf("Time: %ld\n", times);

  return ((!ret) ? times : -1);
}

int cpu_main(int argc, char *argv[]) {
  long ret = 0;

  if (argc < 2) {
    printf("cpu command to test functions.\n");
    return -1;
  }
  printf("Test %s \n", argv[1]);
#ifdef CPUBENCH
  if (!strncmp(argv[1], "dhry", 4)) {
    benchmark_dhry_main();
  } else if (!strncmp(argv[1], "coremark", 8)) {
    coremark_main(argc - 1, &argv[1]);
  }
#endif

  if (!strncmp(argv[1], "vector-isa", 10)) {
    ret = cpu_test_case(test_vector_isa, 0, false);
    printf("Test Vector ISA %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "sysmap", 6)) {
    ret = cpu_test_case(test_sysmap, 0, true);
    printf("Test Sysmap %s\n", (ret < 0) ? "Failed" : "Pass");
  } else {
    itcs_sysm_switch_bram(CPU, L2CACHE_MODE);

    #ifdef CONFIG_MMU
    if (!is_cfg_mmu()) {
      configure_mmu();
      mmu_enable();
    }
    #endif

    #ifndef CONFIG_RISCV_SMODE
      for(int i = 0; i < 3; i++) {
        printf("please select supervisor mode in menuconfig!!!\n");
      }
    #endif

    #ifndef CONFIG_LIB_SBI
      for(int i = 0; i < 3; i++) {
        printf("please select lib_sbi in menuconfig!!!\n");
      }
    #endif


    if (!strncmp(argv[1], "icache_enable", 13)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc, 0, true);
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_DISABLE, 0, 0, 0);
      printf("Test Icache Enable %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "icache_disable", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_DISABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc, 0, true);
      printf("Test Icache Disable %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "icache_invalid", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc2, 0, true);
      if (ret < 0) {
        printf("Test Icache Invalid Failed\n");
        itcs_icache_disable();
        goto err;
      }
      csi_icache_invalid();
      //itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_INVALID, 0, 0, 0);
      ret = cpu_test_case(test_crc, 0, false);
      ret *= 2;
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_DISABLE, 0, 0, 0);
      printf("Times:%ld\n", ret);
      printf("Test Icache Invalid %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "icache_full_scope", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_ENABLE, 0, 0, 0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_PMU_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_icache_full_scope, 0, false);
      itcs_send_ecall(SBI_CPU, SBI_EXT_PMU_DISABLE, 0, 0, 0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_ICACHE_DISABLE, 0, 0, 0);
      printf("Test Icache Full Scope %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_enable", 13)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc, 0, true);
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Test Dcache Enable %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_disable", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc, 0, true);
      printf("Test Dcache Disable %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_invalid", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc2, 0, true);
      if (ret < 0) {
        itcs_dcache_disable();
        printf("Test Dcache Invalid Failed\n");
        goto err;
      }
      itcs_dcache_invalid();
      ret = cpu_test_case(test_crc, 0, false);
      ret *= 2;
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Total times:%ld\n", ret);
      printf("Test Dcache Invalid %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_clean", 12)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc2, 0, true);
      if (ret < 0) {
        itcs_dcache_disable();
        printf("Test Dcache Clean Failed\n");
        goto err;
      }
      itcs_dcache_clean();
      ret = cpu_test_case(test_crc, 0, false);
      ret *= 2;
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Total times:%ld\n", ret);
      printf("Test Dcache Clean %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_flush", 20)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_crc2, 0, true);
      if (ret < 0) {
        itcs_dcache_disable();
        printf("Test Dcache Flush Failed\n");
        goto err;
      }
      itcs_dcache_flush();
      ret = cpu_test_case(test_crc, 0, false);
      ret *= 2;
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Total times:%ld\n", ret);
      printf("Test Dcache Flush %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_full_scope", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_PMU_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_dcache_full_scope, 0, false);
      itcs_send_ecall(SBI_CPU, SBI_EXT_PMU_DISABLE, 0, 0, 0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Test Dcache Full Scope %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "l2cache_full_scope", 14)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_PMU_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_l2cache_full_scope, 0, false);
      itcs_send_ecall(SBI_CPU, SBI_EXT_PMU_DISABLE, 0, 0, 0);
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Test L2cache Full Scope %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_range_flush", 26)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_dcache_range, 'n', true);
      if (ret < 0) {
        itcs_dcache_disable();
        printf("Test Dcache Flush Range Failed\n");
        goto err;
      }
      ret = cpu_test_case(test_dcache_range, 'f', true);
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Test Dcache Flush Range %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_range_clean", 18)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_dcache_range, 'n', true);
      if (ret < 0) {
        itcs_dcache_disable();
        printf("Test Dcache Clean Range Failed\n");
        goto err;
      }
      ret = cpu_test_case(test_dcache_range, 'c', true);
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Test Dcache Clean Range %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "dcache_range_invalid", 20)) {
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_ENABLE, 0, 0, 0);
      ret = cpu_test_case(test_dcache_range, 'n', true);
      if (ret < 0) {
        itcs_dcache_disable();
        printf("Test Dcache Invalid Range Failed\n");
        goto err;
      }
      ret = cpu_test_case(test_dcache_range, 'i', true);
      itcs_send_ecall(SBI_CPU, SBI_EXT_DCACHE_DISABLE, 0, 0, 0);
      printf("Test Dcache Invalid Range %s\n", (ret < 0) ? "Failed" : "Pass");
    } else if (!strncmp(argv[1], "pmp", 20)) {
      ret = cpu_test_case(test_pmp, 0, false);
    }
  }
err:
  return ((ret >= 0) ? 0 : ret);
}

void cpu_init(void) { register_testbench("cpu", cpu_main, NULL); }

testbench_init(cpu_init);
