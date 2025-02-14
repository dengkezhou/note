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

#ifdef CONFIG_COMPILE_RTL
#define loop_cnt 2
#else
#define loop_cnt 20
#endif

#define CPUBENCH
#define CRC32_HASH 0xb1c3dc4a

int test_crc(char op) {
  uint32_t tmp, len;
  uint8_t *buf;
#ifdef CONFIG_COMPILE_RTL
  len = 0x800;
#else
  len = 0x800000;
#endif
  buf = malloc(len);
  if (buf == NULL)
    return -1;

  for (int i = 0; i < len; i++)
    buf[i] = i & 0xff;

  for (int i = 0; i < loop_cnt; i++) {
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


int test_pmp(char op) {
  mpu_region_attr_t attr;
  volatile uint32_t *a, *b;

  a = (uint32_t *)(0x20020000 - 4);
  b = (uint32_t *)(0x20020000 + 4);

  *a = *b = 0x1234;

  attr.r = 1;
  attr.w = 1;
  attr.x = 1;
  attr.l = 0;
  attr.a = ADDRESS_MATCHING_NAPOT;

  csi_mpu_config_region(0, 0x20000000, REGION_SIZE_128KB, attr, true);

  attr.w = 0;
  csi_mpu_config_region(1, 0x20020000, REGION_SIZE_128KB, attr, true);

  *a = *b = 0x5678;

  printf("region 0(rw): %s, &a=%p, *a=%#x\n", *a == 0x5678 ? "PASS" : "FAILED", a, *a);
  printf("region 1(r):  %s, &b=%p, *b=%#x\n", *b == 0x5678 ? "FAILED" : "PASS", b, *b);

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
  } else if (!strncmp(argv[1], "pmp", 20)) {
    ret = cpu_test_case(test_pmp, 0, false);
    printf("Test Physical Protect Memory %s\n", (ret < 0) ? "Failed" : "Pass");
  }
err:
  return ((ret >= 0) ? 0 : ret);
}

void cpu_init(void) { register_testbench("cpu", cpu_main, NULL); }

testbench_init(cpu_init);
