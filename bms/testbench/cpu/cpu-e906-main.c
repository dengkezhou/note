#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <hash.h>
#include <dhrystone/dhry.h>
#include <coremark/coremark.h>
#include <core_rv32.h>
#include <cache.h>
#include <asm/io.h>
#include <stdbool.h>
#include <pmu.h>
#include <sysmap.h>
#include <sysm.h>
#include <rand48.h>

#ifdef CONFIG_COMPILE_RTL
#define LOOP_CNT   2
#define CRC_LENGTH 0x800
#define CRC32_HASH 0x9f5edd58
#else
#define LOOP_CNT   20
#define CRC_LENGTH 0x8000
#define CRC32_HASH 0x217726b2
#endif

#define CPUBENCH

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

int test_crc(char op) {
  uint32_t tmp, len = CRC_LENGTH;
  uint8_t *buf;

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

#define L1ICACHE_SIZE 0x4000
#define L1DCACHE_SIZE 0x4000

void jump(unsigned long base) { asm volatile("jalr ra, %0;" ::"r"(base)); }

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

  sysmap_region_t regions[] = {
#ifdef CONFIG_TB_RUN_IRAM
    {0x14080000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x14100000, SYSMAP_SYSMAPCFG_B_Msk},
#else
    {0x0c000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x18000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
#endif
    {0x20000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x40000000, SYSMAP_SYSMAPCFG_SO_Msk},
    {0x40080000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x80000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0xc0000000, SYSMAP_SYSMAPCFG_SO_Msk},
    {0xfffff000, SYSMAP_SYSMAPCFG_SO_Msk}
  };

  for (int i = 0; i < MAX_REGIONS; i++) {
    if (i >= ARRAY_SIZE(regions))
      csi_sysmap_config_region(i, 0, 0);
    else
      csi_sysmap_config_region(i, regions[i].end, regions[i].attr);
  }

  buf = malloc(L1DCACHE_SIZE);
  // set one loop dcache
  for (i = 0; i < L1DCACHE_SIZE; i++)
    buf[i] = rand() % 0xff;
  l1dcwac = hpm_get_count(RISCV_PMU_L1DCWAC);
  l1dcwmc = hpm_get_count(RISCV_PMU_L1DCWMC);

  // set second loop dcache
  for (i = 0; i < L1DCACHE_SIZE; i++)
    buf[i] = rand() % 0xff;
  subl1dcwac = hpm_get_count(RISCV_PMU_L1DCWAC) - l1dcwac;
  subl1dcwmc = hpm_get_count(RISCV_PMU_L1DCWMC) - l1dcwmc;

  hitrate = subl1dcwac * 100 / (subl1dcwac + subl1dcwmc);
  free(buf);
  return ((hitrate > 90) ? 0 : -1);
}

/* retest pmp case must reset core */
int test_pmp(char op) {
  mpu_region_attr_t attr;
  attr.r = 1;
  attr.w = 1;
  attr.x = 1;
  attr.a = ADDRESS_MATCHING_TOR;
  attr.l = 1;
  csi_mpu_config_region(0, 0x40000000, REGION_SIZE_4KB, &attr, 1);
  csi_mpu_config_region(1, 0x70000000, REGION_SIZE_4KB, &attr, 1);
  attr.w = 0;
  csi_mpu_config_region(2, 0x80000000, REGION_SIZE_4KB, &attr, 1);

  *(unsigned long *)(0x70000000 - 4) = 1;
  printf("Test Physical Protect Memory Pass If show panic log next\n");
  *(unsigned long *)(0x70000000 + 4) = 2;
  return 0;
}

static sysmap_region_t regions[] = {
#ifdef CONFIG_TB_RUN_IRAM
    {0x14000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x14080000, SYSMAP_SYSMAPCFG_B_Msk},
#else
    {0x0c000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x18000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
#endif
    {0x20000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x40000000, SYSMAP_SYSMAPCFG_SO_Msk},
#ifdef CONFIG_TB_RUN_IRAM
    {0x41000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
#else
    {0x41000000, SYSMAP_SYSMAPCFG_SO_Msk},
#endif
    {0xc0000000, SYSMAP_SYSMAPCFG_SO_Msk},
    {0xfffff000, SYSMAP_SYSMAPCFG_SO_Msk}};

int test_sysmap(char op) {
  int ret;

  for (int i = 0; i < ARRAY_SIZE(regions); i++) {
    if (i >= MAX_REGIONS)
      break;

    csi_sysmap_config_region(i, regions[i].end, regions[i].attr);
  }

  /* run time same as icache disable */
  itcs_icache_enable();
  ret = cpu_test_case(test_crc, 0, true);
  itcs_icache_disable();

  return (ret < 0 ? ret : 0);
}

int test_idahb(char op) {
  itcs_sysm_set_ahb_range(SAP, IAHB, 0x0, IAHB_256MB);
  itcs_sysm_set_ahb_range(SAP, DAHB, 0x14000000, 0xc0000000);

  *(unsigned long *)(0xc000000) = 0x12345678;
  return 0;
}

int test_jtags(int argc, char *argv[]) {
	int mode = 0, en = 0;
	domain_t domain = CPU;
	
	printf("%s, %s\n", argv[0], argv[1]);
	printf("SAP state: 0x%x\n", itcs_sysm_get_state());
	if (!strcmp(argv[0], "switch"))
		mode = 1;
	else if (!strcmp(argv[0], "enable"))
		en = 1;
	printf("mode %d, en %d\n", mode, en);
	if (!strcmp(argv[1], "SAP"))
		domain = SAP;

	if (mode)
		itcs_sysm_switch_jtag(domain);
	else
		itcs_sysm_jtag_control(domain, en);

	printf("SAP state: 0x%x\n", itcs_sysm_get_state());
	return 0;
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

  if (!strncmp(argv[1], "icache_enable", 13)) {
    itcs_icache_enable();
    ret = cpu_test_case(test_crc, 0, true);
    itcs_icache_disable();
    printf("Test Icache Enable %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "icache_disable", 14)) {
    itcs_icache_disable();
    ret = cpu_test_case(test_crc, 0, true);
    printf("Test Icache Disable %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "icache_invalid", 14)) {
    itcs_icache_enable();
    ret = cpu_test_case(test_crc2, 0, true);
    if (ret < 0) {
      printf("Test Icache Invalid Failed\n");
      itcs_icache_disable();
      goto err;
    }
    itcs_icache_invalid();
    ret = cpu_test_case(test_crc, 0, false);
    ret *= 2;
    itcs_icache_disable();
    printf("Times:%ld\n", ret);
    printf("Test Icache Invalid %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "icache_full_scope", 14)) {
    itcs_icache_enable();
    hpm_init();
    ret = cpu_test_case(test_icache_full_scope, 0, false);
    hpm_deinit();
    itcs_icache_disable();
    printf("Test Icache Full Scope %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_enable", 13)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_crc, 0, true);
#ifndef CONFIG_CACHE_LITE
    itcs_dcache_disable();
#endif
    printf("Test Dcache Enable %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_disable", 14)) {
    itcs_dcache_disable();
    ret = cpu_test_case(test_crc, 0, true);
    printf("Test Dcache Disable %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_invalid", 14)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_crc2, 0, true);
    if (ret < 0) {
      itcs_dcache_disable();
      printf("Test Dcache Invalid Failed\n");
      goto err;
    }
    itcs_dcache_invalid();
    ret = cpu_test_case(test_crc, 0, false);
    ret *= 2;
    itcs_dcache_disable();
    printf("Total times:%ld\n", ret);
    printf("Test Dcache Invalid %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_clean", 12)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_crc2, 0, true);
    if (ret < 0) {
      itcs_dcache_disable();
      printf("Test Dcache Clean Failed\n");
      goto err;
    }
    itcs_dcache_clean();
    ret = cpu_test_case(test_crc, 0, false);
    ret *= 2;
    itcs_dcache_disable();
    printf("Total times:%lld\n", ret);
    printf("Test Dcache Clean %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_flush", 20)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_crc2, 0, true);
    if (ret < 0) {
      itcs_dcache_disable();
      printf("Test Dcache Flush Failed\n");
      goto err;
    }
    itcs_dcache_flush();
    ret = cpu_test_case(test_crc, 0, false);
    ret *= 2;
    itcs_dcache_disable();
    printf("Total times:%ld\n", ret);
    printf("Test Dcache Flush %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_full_scope", 14)) {
    itcs_dcache_enable();
    hpm_init();
    ret = cpu_test_case(test_dcache_full_scope, 0, false);
    hpm_deinit();
#ifndef CONFIG_CACHE_LITE
    itcs_dcache_disable();
#endif
    printf("Test Dcache Full Scope %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_range_flush", 26)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_dcache_range, 'n', true);
    if (ret < 0) {
      itcs_dcache_disable();
      printf("Test Dcache Flush Range Failed\n");
      goto err;
    }
    ret = cpu_test_case(test_dcache_range, 'f', true);
    itcs_dcache_disable();
    printf("Test Dcache Flush Range %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_range_clean", 18)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_dcache_range, 'n', true);
    if (ret < 0) {
      itcs_dcache_disable();
      printf("Test Dcache Clean Range Failed\n");
      goto err;
    }
    ret = cpu_test_case(test_dcache_range, 'c', true);
    itcs_dcache_disable();
    printf("Test Dcache Clean Range %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "dcache_range_invalid", 20)) {
    itcs_dcache_enable();
    ret = cpu_test_case(test_dcache_range, 'n', true);
    if (ret < 0) {
      itcs_dcache_disable();
      printf("Test Dcache Invalid Range Failed\n");
      goto err;
    }
    ret = cpu_test_case(test_dcache_range, 'i', true);
    itcs_dcache_disable();
    printf("Test Dcache Invalid Range %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "pmp", 20)) {
    ret = cpu_test_case(test_pmp, 0, false);
  } else if (!strncmp(argv[1], "sysmap", 20)) {
    ret = cpu_test_case(test_sysmap, 0, false);
    printf("Test SYSMAP %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "idahb", 20)) {
    ret = cpu_test_case(test_idahb, 0, false);
    printf("Test IAHB&DAHB %s\n", (ret < 0) ? "Failed" : "Pass");
  } else if (!strncmp(argv[1], "2-wire-jtag", 20)) {
    itcs_sysm_switch_jtag_mode(SAP, WIRE2_JTAGS);
  } else if (!strncmp(argv[1], "jtags", 20)) {
		test_jtags(argc - 2, &argv[2]);
	}
err:
  return ((ret >= 0) ? 0 : ret);
}

void cpu_init(void) { register_testbench("cpu", cpu_main, NULL); }

testbench_init(cpu_init);
