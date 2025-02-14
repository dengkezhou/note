/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Memory Functions
 *
 * Copied from FADS ROM, Dan Malek (dmalek@jlc.net)
 */

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include <pads.h>
#include <rtc-sysm.h>
#include <rtc.h>
#include <sysm.h>
#include <asm/riscv/suspend.h>
#include <pm.h>
#include <rtl.h>
#include <cache.h>
#include <rand48.h>
#include <crc32.h>

#define RBMAGIC 0x12

#define RSVD_ZONE_START (0x80000000)

#define CCI_TEST_ZONE0 (0x120000000)
#define CCI_TEST_ZONE1 (0x120000000 + 0x1000)

#define CCI_TEST_DATA0 (0x55555555aaaaaaaa)
#define CCI_TEST_DATA1 (0xaaaaaaaa55555555)
#define CCI_TEST_DATA2 (0x1)

#define L1_TEST_ADDR (0x110000000)
#define L1DCACHE_SIZE 0x8000

#define LOOP_COUNT 1

enum {
	SYSM_SET_CLK = 'a',
	SYSM_GET_CLK,
	SYSM_SET_IOMODE,
	SYSM_SET_IOPULL,
	SYSM_SET_IOVALUE,
	SYSM_GET_IOSTATUS,
	SYSM_GPIO_TEST,
	SYSM_CLK_TEST,
	SYSM_DOMAIN_TEST,
	SYSM_GPIOINT_TEST,
	SYSM_RTCINFO_TEST,
	SYSM_SOFTPOWERDOWN_TEST,
	SYSM_SOFTRESET_TEST,
	SYSM_SUSPENDRESUME_TEST,
	SYSM_POWERUPCORE_TEST,
	SYSM_POWERDOWNCORE_TEST,
	SYSM_RTCIOFUNC_TEST,
	SYSM_BOOTM_TEST,
	SYSM_REMAPE906_TEST,
	SYSM_SHAREDDR_TEST,
	SYSM_SECURITY_TEST,
	SYSM_E906AHB_TEST,
	SYSM_RSVD_TEST,
	SYSM_CCI_CACHE_TEST,
	SYSM_CCI_UNCACHE_TEST,
	SYSM_CCI_FLUSH_TEST,
	SYSM_CCI_INVALID_TEST,
	SYSM_CCI_L1_TEST
};

typedef struct gpioint_test {
	int index;
	domain_t domain;
} gpioint_test_t;

typedef struct power_test {
	char *name;
	domain_t domain;
	unsigned long addr;
	int offset;
	uint32_t setval;
	uint32_t getval;
} power_test_t;

typedef struct security_mem {
	char *name;
	unsigned long addr;
	uint32_t set;
	uint32_t get;
	uint32_t secget;
} security_mem_t;

static char *dname[] = { "CPU", "SAP", "RTC" };

static gpioint_test_t stest;
static int gpioint_complete = 0;

#define MULTI_MAX_POWER_TEST 0
#define SINGLE_MAX_POWER_TEST 0
#ifdef CONFIG_CPU_CORES_TEST
static int core_num = 0;
static int core_testn = 0;
#endif

power_test_t pdevs[] = {
	{ "wdt", CPU, ITCS_C_WDT_BASE, 0, 0xabc123, 0x123 },
	{ "gpio", CPU, ITCS_C_GPIO_BASE, 0, 0x5678, 0x5678 },
	{ "ttc0", CPU, ITCS_C_TTC0_BASE, 0x24, 0x56789abc, 0x56789abc },
	{ "ttc1", CPU, ITCS_C_TTC1_BASE, 0x24, 0x56789abc, 0x56789abc },
	{ "spi1", CPU, ITCS_C_SPI1_BASE, 0x10, 0x5a, 0x5a },
	{ "spi2", CPU, ITCS_C_SPI2_BASE, 0x10, 0x5a, 0x5a },
	{ "spi3", CPU, ITCS_C_SPI3_BASE, 0x10, 0x5a, 0x5a },
	{ "iic2", CPU, ITCS_C_I2C2_BASE, 0x8, 0x3b, 0x3b },
	{ "iic3", CPU, ITCS_C_I2C3_BASE, 0x8, 0x3b, 0x3b },
	{ "iic4", CPU, ITCS_C_I2C4_BASE, 0x8, 0x3b, 0x3b },
	{ "iic5", CPU, ITCS_C_I2C5_BASE, 0x8, 0x3b, 0x3b },
	{ "uart2", CPU, ITCS_C_UART2_BASE, 0x1c, 0x12, 0x12 },
	{ "uart3", CPU, ITCS_C_UART3_BASE, 0x1c, 0x12, 0x12 },
	{ "uart4", CPU, ITCS_C_UART4_BASE, 0x1c, 0x12, 0x12 },
	{ "uart5", CPU, ITCS_C_UART5_BASE, 0x1c, 0x12, 0x12 },
	{ "uart6", CPU, ITCS_C_UART6_BASE, 0x1c, 0x12, 0x12 },
	{ "uart7", CPU, ITCS_C_UART7_BASE, 0x1c, 0x12, 0x12 },
	{ "uart8", CPU, ITCS_C_UART8_BASE, 0x1c, 0x12, 0x12 },
	{ "uart9", CPU, ITCS_C_UART9_BASE, 0x1c, 0x12, 0x12 },
	{ "uart10", CPU, ITCS_C_UART10_BASE, 0x1c, 0x12, 0x12 },
	{ "uart11", CPU, ITCS_C_UART11_BASE, 0x1c, 0x12, 0x12 },
	{ "mu", CPU, ITCS_C_MU_BASE, 0x8, 0x11223344, 0x11223344 },
	{ "iis0", CPU, ITCS_C_I2S0_BASE, 0x10, 0x15, 0x15 },
	{ "iis1", CPU, ITCS_C_I2S1_BASE, 0x10, 0x15, 0x15 },
	{ "pwm0", CPU, ITCS_C_PWM0_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm1", CPU, ITCS_C_PWM1_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm2", CPU, ITCS_C_PWM2_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm3", CPU, ITCS_C_PWM3_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm4", CPU, ITCS_C_PWM4_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm5", CPU, ITCS_C_PWM5_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm6", CPU, ITCS_C_PWM6_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "pwm7", CPU, ITCS_C_PWM7_BASE, 0x4, 0x55667788, 0x55667788 },
#if 0
	{"ddr", CPU, ITCS_C_MPU0_BASE, 0, 0, 0 },
	{"usb0", CPU, ITCS_C_USB0_BASE, 0, 0, 0 },
	{"usb1", CPU, ITCS_C_USB1_BASE, 0, 0, 0 },
	{"usb2", CPU, ITCS_C_USB2_BASE, 0, 0, 0 },
	{"usb3", CPU, ITCS_C_USB3_BASE, 0, 0, 0 },
	{"gmac0", CPU, ITCS_C_GMAC0_BASE, 0, 0, 0},
	{"gmac1", CPU, ITCS_C_GMAC1_BASE, 0, 0, 0},
	{"emmc0", CPU, ITCS_C_EMMC0_BASE, 0, 0, 0},
	{"ospi", CPU, ITCS_C_OSPI_BASE, 0, 0, 0},
	{"sd1", CPU, ITCS_C_SD1_BASE, 0, 0, 0},
	{"sd2", CPU, ITCS_C_SD2_BASE, 0, 0, 0},
	{"qspi", CPU, ITCS_C_QSPI_BASE, 0, 0, 0},
	{"cae", CPU, ITCS_C_CAE_BASE, 0, 0, 0},
	{"dma0", CPU, ITCS_C_DMA0_BASE, 0, 0, 0},
	{"dma1", CPU, ITCS_C_DMA1_BASE, 0, 0, 0},
	{"rxa0", CPU, ITCS_C_RXA0_BASE(0), 0, 0, 0},
	{"rxa1", CPU, ITCS_C_RXA1_BASE(0), 0, 0, 0},
	{"rxa2", CPU, ITCS_C_RXA2_BASE(0), 0, 0, 0},
	{"rxa3", CPU, ITCS_C_RXA3_BASE(0), 0, 0, 0},
#endif
	{ "wdt", SAP, ITCS_S_WDT_BASE, 0, 0xabc123, 0x123 },
	{ "gpio", SAP, ITCS_S_GPIO_BASE, 0, 0x5678, 0x5678 },
	{ "ttc", SAP, ITCS_S_TTC_BASE, 0x24, 0x56789abc, 0x56789abc },
	{ "spi0", SAP, ITCS_S_SPI0_BASE, 0x10, 0x5a, 0x5a },
	{ "iic0", SAP, ITCS_S_I2C0_BASE, 0x8, 0x3b, 0x3b },
	{ "iic1", SAP, ITCS_S_I2C1_BASE, 0x8, 0x3b, 0x3b },
#if !defined(CONFIG_COMPILE_FPGA) && !defined(CONFIG_COMPILE_ASIC)
	{ "uart0", SAP, ITCS_S_UART0_BASE, 0x1c, 0x12, 0x12 },
#endif
	{ "uart1", SAP, ITCS_S_UART1_BASE, 0x1c, 0x12, 0x12 },
	{ "mu", SAP, ITCS_S_MU_BASE, 0x8, 0x11223344, 0x11223344 },
	{ "pwm0", SAP, ITCS_S_PWM_BASE, 0x4, 0x55667788, 0x55667788 },
	{ "rtc", RTC, ITCS_R_RTC_BASE, 0x8, 0x1200, 0x1200 },
	{ "pwm0", RTC, ITCS_R_PWM_BASE, 0x4, 0x55667788, 0x55667788 },
	{ NULL }
};

static unsigned long magic_addr = RTC_INFO(RSTUNCLR, 9);

/* pufcc security mode will be test in pufcc case */
static security_mem_t smem[3] = {
	{ "sram", ITCS_SRAM_ADDR, 0x12345678, 0x12345678, 0x0 },
	{ "e906core", ITCS_S_SAP_BASE + SYSM_S_BMU_IAHBL, 0xffffffff, 0xfc00000,
	  0x0 },
	{ NULL },
};

#ifdef CONFIG_C920

#ifdef CONFIG_COMPILE_ASIC
#define RTC_INFO_CORES        RSTUNCLR
#define RTC_INFO_CORES_OFFSET 0x0

#ifdef CONFIG_CPU_CORES_TEST
#define RTC_INFO_CORES_OFFSET_1 0x4
#define RTC_INFO_CORES_OFFSET_2 0x8
#endif

static void poweron_set_cores(int val) {
  rtc_info_set(RTC_INFO_CORES, RTC_INFO_CORES_OFFSET, val);
}
static int poweron_get_cores() {
  return rtc_info_get(RTC_INFO_CORES, RTC_INFO_CORES_OFFSET);
}

extern void irq_env_enable(void);
extern void init_system(void);
extern void max_power(void);
extern int pmic_vol_set(int pmic_id, char *name, int voltage);
extern int pmic_vol_get(int pmic_id, char *name, int *voltage);
extern int pmic_cur_get(int pmic_id, char *name, int *cur);
int core_test(int core_num, int core_testn){
  unsigned long pllrates[] ={1080000000, 1440000000, 1560000000, 1680000000, 1740000000, 1800000000, 1860000000, 1920000000};
  int vols[] = {650, 720, 800, 850, 900, 950, 1000, 1050};
	char *pll = "apll";
	char *pmic = "page0";
	printf("core test\n");
  	while (1) {
		int voltage = 0, cur = 0; 
		//int vols[] = {650, 720, 800, 850, 900, 950, 1000, 1050};
		//char *pll = "apll";
		//char *pmic = "page0";
    //unsigned long pllrates[] ={1140000000, 1500000000, 1560000000, 1680000000, 1740000000, 1800000000, 1860000000, 1920000000};
		//unsigned long pllrate = 1020000000;
		int num;

		num = core_testn;
		// 0.65, 0.72, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05
		// 1G ~ 2G step 60M

		itcs_pll_set_clock(CPU, pll, pllrates[num], 0);
		pmic_vol_set(1, pmic, vols[num]);
		pmic_vol_get(1, pmic, &voltage);
		printf("\n\n\n");
		printf("voltage %s: %d mv\n", pmic, voltage);
		if(abs(voltage - vols[num]) > 10){
			printf("voltage set error, need %d mv\n", vols[num]);
			panic("panic\n");
		}
		printf("\n\n\n");
		for (int i = 0;;i++) {
      		//printf("num = %d, pllrates = %#llu\n", num, pllrates[num]);
			printf("**************start next freq[%ld] test**************\n",pllrates[num] + 60000000 * i);
			itcs_pll_set_clock(CPU, pll, pllrates[num] + 60000000 * i, 0);
			printf("**************%s: %ld**************\n", pll, itcs_pll_get_clock(CPU, pll));
			printf("**************Core: %d Running**************\n", __get_MHARTID());
			extern void benchmark_dhry_main(void);
			benchmark_dhry_main();
			pmic_vol_get(1, pmic, &voltage);
			printf("\n\n\n");
			printf("voltage %s: %d mv\n", pmic, voltage);
			printf("**************freq[%ld] test**************\n",pllrates[num] + 60000000 * i);
			printf("**************Core: %d Pass**************\n", __get_MHARTID());
			printf("\n\n\n\n\n");
		}
		pmic_cur_get(1, pmic, &cur);
		printf("**************cur vol=%d**************\n", cur);
	}
}

#else
static int poweron_cores = 0;
static void poweron_set_cores(int val) { poweron_cores = val; }
static int  poweron_get_cores() { return poweron_cores;}
#endif

static rtc_device_t *rtcdev;

static volatile int is_flush_test = 1;

static volatile unsigned int crc_save = 0;

extern void irq_env_enable(void);
extern void init_system(void);
#endif

extern void clear_getopt_data(void);
extern clk_dev_t cpu_clks[];
extern clk_dev_t sap_clk[];
extern dev_pm_t pm_plic;

static int get_domain(char *name)
{
	if (!strcmp(name, "CPU"))
		return CPU;
	else if (!strcmp(name, "SAP"))
		return SAP;
	else if (!strcmp(name, "RTC"))
		return RTC;

	return -1;
}

static void sysm_set_rbflags(int flags)
{
	writel(flags, magic_addr);
#ifdef CONFIG_C920
	asm("sync.is");
#endif
#ifdef CONFIG_CACHE
	itcs_dcache_flush();
#endif
}

static uint32_t sysm_get_rbflags(void)
{
	return (readl(magic_addr));
}

static bool sysm_check_rbflags(void)
{
	return (readl(magic_addr) == RBMAGIC);
}

#ifdef CONFIG_C920
static void sysm_set_cci_flag(int flags)
{
	writel(flags, magic_addr);
	asm("sync.is");
}

static uint32_t sysm_check_cci_flag(void)
{
	return (readl(magic_addr) == RBMAGIC);
}

static void corejump(void)
{
	int cores;
	// disable mask
	itcs_mask_core_debug(CPU, __get_MHARTID(), 0);

	init_system();
	irq_env_enable();
	printf("Core: %d PowerUP\n", __get_MHARTID());
#ifdef CONFIG_C920
	asm("sync.is");
#endif

	cores = poweron_get_cores();
	cores++;
	poweron_set_cores(cores);

#ifdef CONFIG_C920
	asm("sync.is");
#endif

	if(cores == 1)
	{
			printf("=====cpu 1 run benchmark");
			extern void benchmark_dhry_main(void);
			benchmark_dhry_main();
			printf("=====cpu 1 run benchmark, over");
	}

#if MULTI_MAX_POWER_TEST
	while (1) {
		max_power();
	}
#endif

#ifdef CONFIG_CPU_CORES_TEST
  int core_second = rtc_info_get(RTC_INFO_CORES, RTC_INFO_CORES_OFFSET_1);
  int test_second = rtc_info_get(RTC_INFO_CORES, RTC_INFO_CORES_OFFSET_2);
  printf("second = %d\n", core_second);
  if(core_second == __get_MHARTID()){
    core_test(core_second, test_second);
  }
  #endif
	hang();
}

static void cci_core_jump(void)
{
	int i = 0;
	unsigned long test_zone_0 = CCI_TEST_ZONE0;
	unsigned long test_zone_1 = CCI_TEST_ZONE1;
	volatile int flag = 1;

	itcs_mask_core_debug(CPU, __get_MHARTID(), 0);

	init_system();
	irq_env_enable();

#ifdef CONFIG_C920
	asm("sync.is");
#endif
#ifdef CONFIG_C920
	asm("csrci msmpr, 0x1");
#endif

	while (sysm_check_cci_flag())
		udelay(5);

	for (i = 0; i < 1024; i++) {
		flag = ((readl((test_zone_0 + i * 4)) & i) != i) ? 1 : 0;
		if (flag)
			printf("CCI core %d test Failed\n", __get_MHARTID());
	}
	if (flag == 0)
		printf("CCI core %d cache coherency test Pass\n", __get_MHARTID());

	for (i = 0; i < 1024; i++)
		writel(i, (test_zone_1 + i * 4));
	sysm_set_cci_flag(RBMAGIC);

	hang();
}

static void cci_flush_invalid_jump(void)
{
	unsigned long test_zone = CCI_TEST_ZONE0;
	unsigned long test_data = CCI_TEST_DATA1;

	itcs_mask_core_debug(CPU, __get_MHARTID(), 0);

	init_system();
	irq_env_enable();

#ifdef CONFIG_C920
	asm("sync.is");
#endif
#ifdef CONFIG_C920
	asm("csrci msmpr, 0x1");
#endif

	*(unsigned long *)test_zone = test_data;
	sysm_set_cci_flag(RBMAGIC);

	while (sysm_check_cci_flag())
		udelay(5);

	if (is_flush_test) {
		if (*(unsigned long *)test_zone == CCI_TEST_DATA0)
			printf("CCI flush_range core %d Pass\n", __get_MHARTID());
		else
			printf("CCI flush_range core %d Failed\n", __get_MHARTID());
#ifdef CONFIG_CACHE
		itcs_dcache_flush_range(test_zone, 8);
#endif
		sysm_set_cci_flag(RBMAGIC);
	} else {
		if (*(unsigned long *)test_zone == CCI_TEST_DATA2)
			printf("CCI invalid_range phase 0 core %d Pass\n", __get_MHARTID());
		else
			printf("CCI invalid_range phase 0 core %d Failed\n", __get_MHARTID());
#ifdef CONFIG_CACHE
		itcs_dcache_invalid_range(test_zone, 8);
#endif
		if (*(unsigned long *)test_zone == CCI_TEST_DATA2)
			printf("CCI invalid_range phase 1 core %d Pass\n", __get_MHARTID());
		else
			printf("CCI invalid_range phase 1 core %d Failed\n", __get_MHARTID());
		sysm_set_cci_flag(RBMAGIC);
	}

	hang();
}

static void cci_l1_jump(void)
{
	int loop_cnt = LOOP_COUNT;
	int tmp_loop_cnt = 0;
	int i = 0;
	unsigned int crc_val = 0;
	int len = L1DCACHE_SIZE;
	unsigned char *tmp_ptr = (unsigned char *)L1_TEST_ADDR;
	int pass = 0;

	itcs_mask_core_debug(CPU, __get_MHARTID(), 0);

	init_system();
	irq_env_enable();

#ifdef CONFIG_C920
	asm("sync.is");
#endif
	printf("Core %d rand len: 0x%x", __get_MHARTID(), len);
	while (tmp_loop_cnt < loop_cnt) {
		while (!sysm_check_cci_flag())
			udelay(5);

		itcs_icache_invalid();
		itcs_dcache_invalid_range((phys_addr_t)tmp_ptr, len);

		crc_val = lib_crc32_le(0, tmp_ptr, len);
		if (crc_val != crc_save) {
			printf("Core %d loop count %d failed, 0x%x, 0x%x\n", __get_MHARTID(), tmp_loop_cnt, crc_val, crc_save);
			pass = -1;
			goto err;
		}
		tmp_loop_cnt++;

		for (i = 0; i < len; i++)
			tmp_ptr[i] = rand() % 0xff;

		crc_val = lib_crc32_le(0, tmp_ptr, len);

		itcs_dcache_flush_range((phys_addr_t)tmp_ptr, len);
		crc_save = crc_val;
		sysm_set_cci_flag(0);
	}
err:
	if (pass == 0)
		printf("CCI core %d Pass\n", __get_MHARTID());
	else
		printf("CCI core %d Failed\n", __get_MHARTID());

	udelay(5);
	sysm_set_cci_flag(RBMAGIC);
#ifdef CONFIG_C920
	asm("csrci msmpr, 0x1");
#endif
	
	hang();
}
#endif

#if 0
int sysm_handle_clk(int mode, int argc, char **argv)
{
	int domain = get_domain(argv[0]);
	char *clkname = argv[1];
	bool pll = false;
	int clkrate;
	int ret;

	if (strstr(clkname, "pll"))
		pll = true;

	if (domain < 0) {
		printf("Do not support this domain: %s\n", argv[0]);
		return -1;
	}

	if (mode == SYSM_SET_CLK) {
		clkrate = simple_strtol(argv[2], NULL, 10) * KHZ;

		if (pll)
			ret = itcs_pll_set_clock(domain, clkname, clkrate,
						 false);
		else
			ret = itcs_module_set_clock(domain, clkname, NULL,
						    clkrate, false);

		if (ret > 0)
			printf("Set clk(%s) to %d Mhz, actully %d Mhz\n",
			       clkname, clkrate / KHZ, ret / KHZ);
		else
			printf("Set clk(%s) Err\n", clkname);
	} else {
		if (pll)
			ret = itcs_pll_get_clock(domain, clkname);
		else
			ret = itcs_module_get_clock(domain, clkname);

		if (ret > 0)
			printf("Get clk(%s): %d Mhz\n", clkname, ret / KHZ);
		else
			printf("Get clk(%s) Err\n", clkname);
	}
	return ret;
}
#endif

int sysm_handle_io(int mode, int argc, char **argv)
{
	int domain = get_domain(argv[0]);
	const char *iomode[3] = { "In", "Out", "Func" };
	const char *iopull[3] = { "UP", "Down", "No" };
	int index;
	int ret = 0;

	index = simple_strtol(argv[1], NULL, 10);
	switch (mode) {
	case SYSM_SET_IOMODE: {
		int mode = simple_strtol(argv[2], NULL, 10);
		int value = 0;

		if (mode != PADS_MODE_IN)
			value = simple_strtol(argv[3], NULL, 10);

		ret = itcs_pads_set_mode(domain, index, mode, value);
		if (ret < 0)
			printf("Set(%d) IO Mode Err\n", index);
		else
			printf("Set(%d) IO Mode: %s\n", index, iomode[mode]);
	} break;
	case SYSM_SET_IOPULL: {
		int en = simple_strtol(argv[2], NULL, 10);
		int pull = simple_strtol(argv[3], NULL, 10);

		ret = itcs_pads_set_pull(domain, index, en,
					 (en ? PADS_PULL_NO : pull));
		if (ret < 0)
			printf("Set(%d) IO Pull Err\n", index);
		else
			printf("Set(%d) IO Pull: %s(%s)\n", index, iopull[pull],
			       en ? "enable" : "disable");
	} break;
	case SYSM_SET_IOVALUE: {
		int value = simple_strtol(argv[2], NULL, 10);

		ret = itcs_pads_set_value(domain, index, value);
		if (ret < 0)
			printf("Set(%d) IO Value Err\n", index);
		else
			printf("Set(%d) IO Value: %s\n", index,
			       value ? "high" : "low");
	} break;
	case SYSM_GET_IOSTATUS: {
		int mode, value;
		int pull = itcs_pads_get_pull(domain, index);

		value = itcs_pads_get_value(domain, index, &mode);

		printf("IO Status:\n");
		printf("IO Mode: %s\n", iomode[mode]);
		printf("IO Pull: %s\n", iopull[pull]);
		if (mode != PADS_MODE_FUNC)
			printf("IO Value: %s\n", value ? "high" : "low");
	} break;
	default:
		return -1;
	}
	return ret;
}

static void sysm_gpio_read_delay(domain_t domain, int index)
{
#ifdef CONFIG_COMPILE_RTL
	if (domain == RTC && index == RTCGP3)
		udelay(10);
#endif
}

static int sysm_domain_gpio_test(domain_t domain, int start, int end)
{
	int mode, val;

	for (int i = start; i < end; i += 2) {
		itcs_pads_set_mode(domain, i + 1, PADS_MODE_IN, 0);
		itcs_pads_set_mode(domain, i, PADS_MODE_OUT, 0);

		sysm_gpio_read_delay(domain, i + 1);
		val = itcs_pads_get_value(domain, i + 1, &mode);
		if (val || mode != PADS_MODE_IN) {
			printf("Pads out %d in %d Err: %d\n", i, i + 1, val);
			return -1;
		}

		itcs_pads_set_value(domain, i, 1);

		sysm_gpio_read_delay(domain, i + 1);
		val = itcs_pads_get_value(domain, i + 1, &mode);
		if (!val || mode != PADS_MODE_IN) {
			printf("Pads out %d in %d Err: %d\n", i, i + 1, val);
			return -1;
		}

		itcs_pads_set_mode(domain, i, PADS_MODE_IN, 0);
		itcs_pads_set_mode(domain, i + 1, PADS_MODE_OUT, 0);

		sysm_gpio_read_delay(domain, i);
		val = itcs_pads_get_value(domain, i, &mode);
		if (val || mode != PADS_MODE_IN) {
			printf("Pads out %d in %d Err: %d\n", i + 1, i, val);
			return -1;
		}

		itcs_pads_set_value(domain, i + 1, 1);

		sysm_gpio_read_delay(domain, i);
		val = itcs_pads_get_value(domain, i, &mode);
		if (!val || mode != PADS_MODE_IN) {
			printf("Pads out %d in %d Err: %d\n", i + 1, i, val);
			return -1;
		}
	}
	return 0;
}

static int sysm_gpio_test(int argc, char **argv)
{
	int domain = get_domain(argv[0]);
	int start = simple_strtol(argv[1], NULL, 10);
	int end = simple_strtol(argv[2], NULL, 10);

	if (end <= start)
		return -1;

	if (sysm_domain_gpio_test(domain, start, end) < 0) {
		printf("Test SYSM %s GPIO Input&OutPut Failed\n", argv[0]);
		return -1;
	}

	printf("Test SYSM %s GPIO Input&OutPut Pass\n", argv[0]);
	return 0;
}

static int gpio_irqhandler(int irq, void *args)
{
	gpioint_test_t *gtest = (gpioint_test_t *)args;

	//printf("gtest->index %d, gtest->domain %d\n", gtest->index, gtest->domain);
	if (gtest->index == stest.index && gtest->domain == stest.domain) {
		printf("gpio %d get irq\n", gtest->index);
		gpioint_complete = 1;
	} else {
		printf("%s(%s) gpio%d(%d) generate irq, but Err\n",
		       dname[gtest->domain], dname[stest.domain], gtest->index,
		       stest.index);
		gpioint_complete = -1;
	}

	gpio_irq_disable(gtest->domain, gtest->index);
	return 0;
}

static int sysm_single_gpioint_test(domain_t domain, int output, int gpioidx)
{
	int flags = (domain == RTC) ? IRQ_TYPE_LEVEL_HIGH :
					    IRQ_TYPE_EDGE_RISING;
	int ret;

	stest.domain = domain;
	gpioint_complete = 0;

	itcs_pads_set_mode(domain, gpioidx, PADS_MODE_IN, 0);
	itcs_pads_set_mode(domain, output, PADS_MODE_OUT, 0);

	stest.index = gpioidx;
	ret = gpio_request_irq(domain, stest.index, gpio_irqhandler, flags,
			       NULL, &stest);
	if (ret < 0)
		return -1;

	sysm_gpio_read_delay(domain, stest.index);
	itcs_pads_set_mode(domain, output, PADS_MODE_OUT, 1);
	while (1) {
		if (gpioint_complete < 0)
			return -1;
		else if (gpioint_complete > 0) {
			printf("%s gpio%d pass\n", dname[stest.domain],
			       stest.index);
			break;
		}

		udelay(5);
	}
	return 0;
}

static int sysm_gpioint_test(int argc, char **argv)
{
	int domain = get_domain(argv[0]);
	int start = simple_strtol(argv[1], NULL, 10);
	int end = simple_strtol(argv[2], NULL, 10);
	int ret;

	if (end <= start)
		return -1;

	for (int i = start; i < end; i += 2) {
		ret = sysm_single_gpioint_test(domain, i, i + 1);
		if (ret < 0)
			break;

		ret = sysm_single_gpioint_test(domain, i + 1, i);
		if (ret < 0)
			break;
	}

	printf("Test SYSM %s GPIO IRQ %s\n", argv[0],
	       ((ret < 0) ? "Failed" : "Pass"));
	return ret;
}

static int sysm_domain_clk_test(domain_t domain, clk_dev_t *dev,
				uint64_t cpurate)
{
	uint64_t rate;
	uint64_t cmprate;

	for (int i = 0; dev[i].name; i++) {
		if (dev[i].clkmode == PLL) {
#if defined(CONFIG_COMPILE_ASIC) && (defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
			if (!strcmp("vpll", dev[i].name))
				continue;
#endif
			if (!strcmp("spll", dev[i].name))
				cpurate = itcs_pll_get_clock(domain, dev[i].name);
			itcs_pll_set_clock(domain, dev[i].name, cpurate, false);
			rate = itcs_pll_get_clock(domain, dev[i].name);
			if (rate != cpurate) {
				printf("Get %s pll clk err: %lld(%lld)\n",
				       dev[i].name, rate, cpurate);
				return -1;
			}
		} else {
			if (dev[i].clkmode == CPUB) {
				itcs_module_set_clock(domain, dev[i].name, NULL,
						      CPURATIO(1, 2, 4), false);
				rate = itcs_module_get_clock(domain,
							     dev[i].name);
				if (!strcmp(dev[i].name, "cpub"))
					cmprate = cpurate / 4;
				else
					cmprate = cpurate / 2;

				if (rate != cmprate) {
					printf("Get %s clk err: %lld(%lld)\n",
					       dev[i].name, rate, cmprate);
					return -1;
				}
				continue;
			}

			if (!strcmp("ddr0", dev[i].name) || !strcmp("ddr1", dev[i].name))
				continue;

			if (!strcmp(dev[i].name, "usb3 ref") ||
			    !strcmp(dev[i].name, "usb2 ref") ||
			    !strcmp(dev[i].name, "usb stb") ||
			    !strcmp(dev[i].name, "usb lpm") ||
			    !strcmp(dev[i].name, "pvt") ||
			    !strcmp(dev[i].name, "puf eng") ||
			    !strcmp(dev[i].name, "puf xtl"))
				cmprate = 12000000;
			else
				cmprate = cpurate / 8;

			if (domain == SAP && (!strcmp("apb", dev[i].name) || !strcmp("apc", dev[i].name)))
				cmprate = itcs_module_get_clock(domain, dev[i].name);

			if (domain == SAP && !strcmp("uart", dev[i].name))
				continue;
			itcs_module_set_clock(domain, dev[i].name, NULL,
					      cmprate, false);
			rate = itcs_module_get_clock(domain, dev[i].name);
			if (rate != cmprate) {
				printf("Get %s clk err: %lld(%lld)\n",
				       dev[i].name, rate, cmprate);
				return -1;
			}
			if (dev[i].clkmode != APB)
				itcs_module_disable_clock(domain, dev[i].name);
		}
	}

	return 0;
}

static int sysm_clk_test(void)
{
	int ret;

	ret = sysm_domain_clk_test(CPU, cpu_clks, 1584000000);
	if (ret < 0) {
		printf("Test SYSM CPU PLL & Module Clock Failed\n");
		return -1;
	}
	ret = sysm_domain_clk_test(SAP, sap_clk, 480000000);
	if (ret < 0) {
		printf("Test SYSM SAP PLL & Module Clock Failed\n");
		return -1;
	}
	printf("Test SYSM PLL & Module Clock Pass\n");
	return 0;
}

static int sysm_domain_test(void)
{
	uint32_t tmp;

	for (int i = 0; pdevs[i].name; i++) {
		//printf("%s module: %s \n", dname[pdevs[i].domain], pdevs[i].name);
		itcs_module_enable(pdevs[i].domain, pdevs[i].name);
		writel(pdevs[i].setval, pdevs[i].addr + pdevs[i].offset);
		tmp = readl(pdevs[i].addr + pdevs[i].offset);
		if (tmp != pdevs[i].getval) {
			printf("SYSM %s Enable Err: 0x%x(0x%x)\n",
			       pdevs[i].name, tmp, pdevs[i].getval);
			return -1;
		}
		// wdt do not have reset func
		if (strcmp(pdevs[i].name, "wdt")) {
			// for not keep rtc
			if (!strcmp(pdevs[i].name, "rtc"))
				writel(0, pdevs[i].addr + 0x30);

			itcs_module_reset(pdevs[i].domain, pdevs[i].name);
			tmp = readl(pdevs[i].addr + pdevs[i].offset);
			if (tmp) {
				printf("SYSM %s Reset Err: 0x%x\n",
				       pdevs[i].name, tmp);
				return -1;
			}
		}

		itcs_module_disable(pdevs[i].domain, pdevs[i].name);
		if (!strcmp(pdevs[i].name, "wdt"))
			writel(0xabc000, pdevs[i].addr + pdevs[i].offset);
		else
			writel(pdevs[i].setval,
			       pdevs[i].addr + pdevs[i].offset);
		tmp = readl(pdevs[i].addr + pdevs[i].offset);
		if (tmp) {
			printf("SYSM %s Disable Err: 0x%x\n", pdevs[i].name,
			       tmp);
			return -1;
		}
	}
	printf("Test SYSM Domain Pass\n");
	return 0;
}

#ifdef CONFIG_COMPILE_RTL
static void sysm_simualte_hardreset(domain_t domain, int index)
{
	itcs_pads_set_mode(domain, index, PADS_MODE_OUT, 0);
	udelay(5);
	itcs_pads_set_value(domain, index, 1);
}
#endif

static int sysm_rtcinfo_test(int argc, char **argv)
{
	int rbmode = !strcmp(argv[0], "poweron_reset");
	int io = 2, mode;

#ifdef CONFIG_COMPILE_ASIC
	io = 68;
	/* default high, need to pull low. */
	itcs_pads_set_mode(CPU, PADSRANGE(io, io), PADS_MODE_IN, 0);
	if (itcs_pads_get_value(CPU, io, &mode)) {
#else
	// CPU GPIO2 as flags for whether reset or not
	itcs_pads_set_mode(CPU, io, PADS_MODE_IN, 0);
	if (itcs_pads_get_value(CPU, io, &mode)) {
#endif
		for (int i = 0; i < RINFO_RSTCLR_SUM; i++)
			if (rtc_info_get(RSTCLR, i) != 0) {
				printf("RTCINFO(CLR) Err %d: 0x%x\n", i,
				       rtc_info_get(RSTCLR, i));
				return -1;
			}

		for (int i = 0; i < RINFO_RSTUNCLR_SUM; i++)
			if (rtc_info_get(RSTUNCLR, i) !=
			    (rbmode ? 0 : (i + 1))) {
				printf("RTCINFO(UNCLR) Err %d: 0x%x\n", i,
				       rtc_info_get(RSTUNCLR, i));
				return -1;
			}

		printf("Test SYSM RTCINFO Pass\n");
		return 0;
	} else {
#ifdef CONFIG_COMPILE_RTL
		int domain = get_domain(argv[1]);
		int index = simple_strtol(argv[2], NULL, 10);
#endif
		for (int i = 0; i < RINFO_RSTCLR_SUM; i++)
			rtc_info_set(RSTCLR, i, i + 1);

		for (int i = 0; i < RINFO_RSTUNCLR_SUM; i++)
			rtc_info_set(RSTUNCLR, i, i + 1);

#ifdef CONFIG_COMPILE_RTL
		/* reload image in ddr */
		rtl_move_stage(RTL_RELOAD);

		sysm_simualte_hardreset(domain, index);
		/* Can not run in here*/
		for (;;)
			;
#endif
	}

	return 0;
}

static int sysm_power_test(int mode)
{
	int event = (mode == SYSM_SOFTPOWERDOWN_TEST) ? RTC_SHUTDOWN :
							      RTC_SOFTRESET;

	if (sysm_check_rbflags()) {
		sysm_set_rbflags(0);

		if (mode == SYSM_SOFTPOWERDOWN_TEST)
			printf("Test SYSM ShutDown Pass\n");
		else
			printf("Test SYSM SoftReset %s\n",
			       is_soft_reset() ? "Pass" : "Failed");
		return 0;
	}

	sysm_set_rbflags(RBMAGIC);
#ifdef CONFIG_COMPILE_RTL
	rtl_move_stage(RTL_RELOAD);
	udelay(5);
#endif
	rtc_set_event(event);
	/* Can not run in here*/
	hang();
	return -1;
}
#ifdef CONFIG_C920
const char *resume_events[RESUME_EVENT_MAX] = {
	"GP0",	"GP1",	"GP2",	"GP3",	"RTC-ALARM", "GP4",  "GP5", "EGP0",
	"EGP1", "EGP2", "EGP3", "EGP4", "EGP5",	     "EGP6", "EGP7"
};

static int get_resume_event(char *name)
{
	if (!name)
		return -1;

	for (int i = 0; i < RESUME_EVENT_MAX; i++)
		if (!strcmp(name, resume_events[i]))
			return i;

	return -1;
}

static int resume_gpio_irqhandler(int irq, void *args)
{
	// printf("%s\n", __func__);
	return 0;
}

static void rtc_alarm_callback(void *arg, int status)
{
	// printf("%s: status 0x%x\n", __func__, status);
	if (status & RTC_ALRM_TRIG) {
		itcs_rtc_event_set_irq_enable(rtcdev, RTC_ALRM_TRIG, false);
		itcs_rtc_deinit(rtcdev);
	}
}

static int rtc_alarm(void)
{
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = rtc_alarm_callback,
	};
	rtc_time_t time0, time1;
	int ret = -1;

	rtcdev = itcs_rtc_init(&sets);
	if (!rtcdev)
		return ret;

		/* alarm doesn't support year setting, here we set it as 2022. */
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	itcs_rtc_init_time(&time1, 2022, 7, 21, 12, 7, 25, 0);
#elif defined(CONFIG_COMPILE_RTL)
	itcs_rtc_init_time(&time1, 2022, 7, 21, 12, 7, 22, 0);
#endif
	itcs_rtc_set_alarm(rtcdev, &time1);

	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 21, 0);
	itcs_rtc_set_time(rtcdev, &time0);

	return 0;
}

static int sysm_suspendresume_test(int argc, char **argv)
{
	struct suspend_context *context =
		(struct suspend_context *)(ITCS_DBGRAM_ADDR);
	int sevent = get_resume_event(argv[0]);
	int irqflags = IRQ_TYPE_LEVEL_LOW;
	int index = 0;
	int ret = -1;

	if (sevent < 0)
		return -1;

	if (argc == 2) {
		irqflags = simple_strtol(argv[1], NULL, 10);
		irqflags =
			(irqflags ? IRQ_TYPE_LEVEL_HIGH : IRQ_TYPE_LEVEL_LOW);
	}

	// irq suspend first currently
	if (sevent != 4) {
		pm_plic.ops.suspend(NULL);

		index = ((sevent < 5) ? sevent : sevent - 1);
		itcs_pads_set_mode(RTC, index, PADS_MODE_IN, 0);
		ret = gpio_request_irq(RTC, index, resume_gpio_irqhandler,
				       irqflags, NULL, NULL);
		if (ret < 0)
			return ret;
	} else {
		/* TODO */
		ret = rtc_alarm();
		if (ret < 0)
			return ret;

		pm_plic.ops.suspend(NULL);
	}

	rtc_set_resume_source(sevent, true);
	// set context addr to rtcinfo
	for (int i = 0; i < sizeof(unsigned long); i++) {
		rtc_info_set(RSTUNCLR, i,
			     (((unsigned long)context) >> (64 - 8 - 8 * i)) &
				     0xff);
	}
	// enter suspend flow
	// device suspend
	itcs_pm_run_suspend();
#ifdef CONFIG_CACHE
	itcs_dcache_flush();
	itcs_icache_disable();
	itcs_dcache_disable();
	itcs_l2cache_invalid();
#endif
	asm("sync.is");
	// save general register
	__cpu_suspend_enter(context);
#ifdef CONFIG_CACHE
	itcs_icache_enable();
	itcs_dcache_enable();
#endif
	// rtc enter suspend
	// itcs_platform_pm_enter();
	// resume device;
	itcs_pm_run_resume();

	pm_plic.ops.resume(NULL);

	if (sevent != 4)
		printf("Test SYSM %s-%s WakeUP Pass\n", argv[0],
		       ((irqflags == IRQ_TYPE_LEVEL_HIGH) ? "High" : "Low"));
	else
		printf("Test SYSM %s WakeUP Pass\n", argv[0]);
	return ret;
}

static int sysm_powercore_test(int mode, int argc, char **argv)
{
#if !defined(CONFIG_TB_RUN_DDR) && !defined(CONFIG_TB_RUN_DDR1)
	extern uint32_t __lds_soc_base[];
	unsigned long soc_base = (unsigned long)__lds_soc_base;
#endif
	unsigned long jmpaddr[NR_CPUS] = { 0 };
	int endCore = simple_strtol(argv[0], NULL, 10);
	int nCores = ((itcs_sysm_identity() == CPU) ? (endCore - 1) : endCore);
	int cores;

	#ifdef CONFIG_CPU_CORES_TEST
	core_num = simple_strtol(argv[1], NULL, 10);
	core_testn = simple_strtol(argv[2], NULL, 10);

	rtc_info_set(RTC_INFO_CORES, RTC_INFO_CORES_OFFSET_1, core_num);
	rtc_info_set(RTC_INFO_CORES, RTC_INFO_CORES_OFFSET_2, core_testn);

		//int vols[] = {650, 720, 800, 850, 900, 950, 1000, 1050};
		//char *pmic = "page0";

		//extern int pmic_vol_set(int pmic_id, char *name, int voltage);
		//pmic_vol_set(1, pmic, vols[core_testn]);
	
	if(core_num == 0){
		printf("core_numii = %d\n", core_num);
		core_test(core_num, core_testn);
	}
	#endif

#if MULTI_MAX_POWER_TEST
	printf("Core 0 is starting max power test\n");
	while (1) {
		max_power();
	}
#endif

#if SINGLE_MAX_POWER_TEST
	printf("Single core power test is starting and it never ends.\n");
	while (1) {
		max_power();
	}
#endif

	poweron_set_cores(0);
	endCore = min(endCore, NR_CPUS);
	printf("----endcore = %d, nCores = %d\n", endCore, nCores);

	if (mode == SYSM_POWERUPCORE_TEST) {
		for (int i = 0; i < endCore; i++) {
			if ((itcs_sysm_identity() == CPU) && !i)
				continue;

			rtc_info_set(RSTCLR, 0, 0x3b);
			for (int j = 0; j < sizeof(unsigned long); j++) {
				rtc_info_set(RSTCLR, j + 1,
					     ((unsigned long)(&jmpaddr[0]) >>
					      (64 - 8 - 8 * j)) &
						     0xff);
			}
#ifdef CONFIG_TB_RUN_DDR
			itcs_core_enable(CPU, i, ITCS_CDDR_ADDR, 0);
#elif defined(CONFIG_TB_RUN_DDR1)
			itcs_core_enable(CPU, i, ITCS_CDDR_END, 0);
#else
			itcs_core_enable(CPU, i, soc_base, 0);
#endif
			// wait core i powerup
			while (jmpaddr[i] != 1)
				udelay(5);

			jmpaddr[i] = (unsigned long)corejump;

#if 1
			udelay(1000);
			itcs_hwmon_print_one_info(0, 10);
			return 0;
#endif

			// ensure write jmpaddr to memory
#ifdef CONFIG_C920
			asm("sync.is");
#endif
		}

		do {
			cores = poweron_get_cores();
			udelay(5);
		}while (cores < nCores);

		printf("Test SYSM CoreUP Pass\n");
	} else {
		for (int i = 0; i < endCore; i++) {
			if ((itcs_sysm_identity() == CPU) && !i)
				continue;

			itcs_core_disable(CPU, i);
		}
		printf("Test SYSM CoreDown Pass\n");
	}
	return 0;
}
#endif

static int sysm_rtciofunc_test(int argc, char **argv)
{
	/* poweronsleep would be sure in suspend&resume case */
	if (!strcmp(argv[0], "rtcclk")) {
		itcs_module_set_pads(RTC, FPGA_BIT_V_EMMC, argv[0]);
#ifdef CONFIG_COMPILE_RTL
		// wait for outputing rtcclk
		udelay(50);
#endif
		printf("Test SYSM RTCCLK Pass\n");
	} else {
		printf("Cmd Err: %s\n", argv[0]);
		return -1;
	}
	return 0;
}

/* frank.lin uses 0x8 & 0x9 bootm mode as test mode. */
static int sysm_bootm_test(int argc, char **argv)
{
	bool security = false;
	int ret = 0;

	if (argc > 0)
		security = !strcmp(argv[0], "security");

	itcs_sysm_set_security(security);
	printf("Boot mode: %d\n", itcs_sysm_get_boot_mode(itcs_sysm_identity()));
	printf("Test SYSM Bootm%s %s\n", (security ? "(Security)" : ""),
	       (!ret ? "Pass" : "Failed"));
	return ret;
}

static int sysm_remape906_test(void)
{
	if (itcs_sysm_identity() == CPU) {
		/* map ddr 0x140000000 to 0x40000000. */
		writel(1, 0xc2f087f8);
		/* 0x40000000 remap to 0 */
		itcs_sysm_remap(SAP, ITCS_SDDR_ADDR);

#ifdef CONFIG_COMPILE_RTL
		rtl_move_stage(RTL_RELOAD_SRAM);
#endif
		sysm_set_rbflags(RBMAGIC);

		while (sysm_check_rbflags())
			udelay(5);

		printf("Test SYSM REMAP E906 Pass\n");
	} else {
		while (!sysm_check_rbflags())
			udelay(5);

		sysm_set_rbflags(0);
		/* wait c920 print finished. */
		udelay(30);
	}
	return 0;
}

static int sysm_shareddr_test(int argc, char **argv)
{
	int ddrsize = simple_strtol(argv[0], NULL, 10);
	int ret = -1, i;

	if (itcs_sysm_identity() == CPU) {
		for (int i = 0; i < ddrsize; i++)
			writel(0x11111111 * (i + 1),
			       0x101000000 + i * 0x40000000);
		
#ifdef CONFIG_C920
		asm("sync.is");
#endif
		sysm_set_rbflags(RBMAGIC);
		while (sysm_check_rbflags())
			udelay(5);

		ret = sysm_get_rbflags();
		printf("Test SYSM ShareDDR %s\n", (ret ? "Failed" : "Pass"));
		return (!ret ? 0 : -1);
	} else {
		while (!sysm_check_rbflags())
			udelay(5);

		for (i = 0; i < ddrsize; i++) {
			/* remap ddr */
			writel(i, 0xc2f087f8);
			/* wait ddr remap ready */
			while (readl(0xc2f087f8) != i)
				udelay(1);

			if ((0x11111111 * (i + 1)) != readl(0x41000000)) {
				sysm_set_rbflags(1);
				break;
			}
		}

		if (i == ddrsize)
			sysm_set_rbflags(0);

		return 0;
	}
}

static int sysm_security_test(void)
{
	bool security = false;
	uint32_t val, tmp;
	int ret = 0;

secmode:
	for (int i = 0; smem[i].name; i++) {
		if (smem[i].set != 0xffffffff)
			writel(smem[i].set, smem[i].addr);

		if (itcs_sysm_identity() == CPU)
			val = (security ? smem[i].secget : smem[i].get);
		else
			val = smem[i].get;
		tmp = readl(smem[i].addr);
		if (val != tmp) {
			printf("Test %s Err: (0x%x, 0x%x)\n", smem[i].name, val,
			       tmp);
			ret = -1;
			break;
		}
	}

	if (!ret && !security) {
		security = true;
		itcs_sysm_set_security(security);
#ifdef CONFIG_C920
		asm("sync.is");
#endif
		goto secmode;
	}

	printf("Test SYSM Security %s\n", (!ret ? "Pass" : "Failed"));
	return ret;
}

int sysm_e906ahb_test(void)
{
	if (itcs_sysm_identity() == CPU) {
		itcs_core_disable(SAP, 0);
		itcs_sysm_set_ahb_range(SAP, IAHB, 0x40000000, 0xc00);
		itcs_sysm_set_ahb_range(SAP, DAHB, 0x4000000, 0x3ff00000);
		sysm_set_rbflags(RBMAGIC);
		/* remap 0x140000000 to 0x40000000 */
		writel(1, 0xc2f087f8);
		itcs_core_enable(SAP, 0, ITCS_SDDR_ADDR, 0);
		while (sysm_check_rbflags())
			udelay(5);
		printf("Test SYSM AHB E906 Pass\n");
	} else {
		while (!sysm_check_rbflags())
			udelay(5);

		sysm_set_rbflags(0);
	}

	return 0;
}

#ifdef CONFIG_C920
static int sysm_rsvd_test(void)
{
	unsigned int i = 0;

	for (i = 0; i < 128; i++) {
		writel(i, (RSVD_ZONE_START + i * 4));
#ifdef CONFIG_CACHE
		itcs_dcache_flush_range((RSVD_ZONE_START + i * 4), 4);
#endif
		asm("sync.is");
		readl((RSVD_ZONE_START + i * 4));
	}
	printf("Reserved zone read and write test Pass\n");
	return 0;
}

static int sysm_cci_rw_test(void)
{
	unsigned long jmpaddr[8] = { 0 };
	unsigned int i = 0;
	unsigned long test_zone_0 = CCI_TEST_ZONE0;
	unsigned long test_zone_1 = CCI_TEST_ZONE1;
	volatile int flag = 1;

	rtc_info_set(RSTCLR, 0, 0x3b);
	for (int j = 0; j < sizeof(unsigned long); j++) {
		rtc_info_set(RSTCLR, j + 1,
			     ((unsigned long)(&jmpaddr[0]) >>
			      (64 - 8 - 8 * j)) &
				     0xff);
	}

	for (i = 0; i < 1024; i++)
		writel(i, (test_zone_0 + i * 4));
	sysm_set_cci_flag(0);

#ifdef CONFIG_TB_RUN_DDR
	itcs_core_enable(CPU, CORE_4, ITCS_CDDR_ADDR, 0);
#elif defined(CONFIG_TB_RUN_DDR1)
	itcs_core_enable(CPU, CORE_4, ITCS_CDDR_END, 0);
#endif
	while (jmpaddr[CORE_4] != 1)
		udelay(5);

	jmpaddr[CORE_4] = (unsigned long)cci_core_jump;
#ifdef CONFIG_C920
	asm("sync.is");
#endif

	while (!sysm_check_cci_flag())
		udelay(5);

	for (i = 0; i < 1024; i++) {
		flag = ((readl((test_zone_1 + i * 4)) & i) != i) ? 1 : 0;
		if (flag)
			printf("CCI core %d test Failed\n", __get_MHARTID());
	}
	if (flag == 0)
		printf("CCI core %d cache coherency test Pass\n", __get_MHARTID());
	return 0;
}

static int sysm_cci_flush_invalid_test(void)
{
	unsigned long jmpaddr[8] = { 0 };
	unsigned long test_zone = CCI_TEST_ZONE0;
	unsigned long test_data = CCI_TEST_DATA0;

	rtc_info_set(RSTCLR, 0, 0x3b);
	for (int j = 0; j < sizeof(unsigned long); j++) {
		rtc_info_set(RSTCLR, j + 1,
			     ((unsigned long)(&jmpaddr[0]) >>
			      (64 - 8 - 8 * j)) &
				     0xff);
	}
	*(unsigned long *)test_zone = CCI_TEST_DATA2;
	itcs_dcache_flush_range(test_zone, 8);
	sysm_set_cci_flag(0);

#ifdef CONFIG_TB_RUN_DDR
	itcs_core_enable(CPU, CORE_4, ITCS_CDDR_ADDR, 0);
#elif defined(CONFIG_TB_RUN_DDR1)
	itcs_core_enable(CPU, CORE_4, ITCS_CDDR_END, 0);
#endif
	while (jmpaddr[CORE_4] != 1)
		udelay(5);

	jmpaddr[CORE_4] = (unsigned long)cci_flush_invalid_jump;
#ifdef CONFIG_C920
	asm("sync.is");
#endif

	while (!sysm_check_cci_flag())
		udelay(5);

	*(unsigned long *)test_zone = test_data;
#ifdef CONFIG_CACHE
	if (is_flush_test)
		itcs_dcache_flush_range(test_zone, 8);
	else
		itcs_dcache_invalid_range(test_zone, 8);
#endif

	sysm_set_cci_flag(0);
	while (!sysm_check_cci_flag())
		udelay(5);

	if (is_flush_test) {
		if (*(unsigned long *)test_zone == CCI_TEST_DATA0)
			printf("CCI flush_range core %d Pass\n", __get_MHARTID());
		else
			printf("CCI flush_range core %d Failed\n", __get_MHARTID());
	}
	return 0;
}

static int sysm_cci_l1_test(void)
{
	unsigned long jmpaddr[8] = { 0 };
	unsigned char *ptr = NULL;
	unsigned int crc_val = 0;
	unsigned int tmp_crc_val = 0;
	int len = L1DCACHE_SIZE;
	int loop_cnt = LOOP_COUNT;
	int tmp_loop_cnt = 0;
	int i;
	int ret = 0;

	rtc_info_set(RSTCLR, 0, 0x3b);
	for (int j = 0; j < sizeof(unsigned long); j++) {
		rtc_info_set(RSTCLR, j + 1,
			     ((unsigned long)(&jmpaddr[0]) >>
			      (64 - 8 - 8 * j)) &
				     0xff);
	}

	sysm_set_cci_flag(0);
#ifdef CONFIG_TB_RUN_DDR
	itcs_core_enable(CPU, CORE_4, ITCS_CDDR_ADDR, 0);
#elif defined(CONFIG_TB_RUN_DDR1)
	itcs_core_enable(CPU, CORE_4, ITCS_CDDR_END, 0);
#endif
	while (jmpaddr[CORE_4] != 1)
		udelay(5);

	jmpaddr[CORE_4] = (unsigned long)cci_l1_jump;
#ifdef CONFIG_C920
	asm("sync.is");
#endif
	ptr = (unsigned char *)L1_TEST_ADDR;
	printf("Core %d rand len: 0x%x", __get_MHARTID(), len);
	while (tmp_loop_cnt < loop_cnt) {
		for (i = 0; i < len; i++)
			ptr[i] = rand() % 0xff;

		crc_val = lib_crc32_le(0, ptr, len);

		itcs_dcache_flush_range((phys_addr_t)ptr, len);
		crc_save = crc_val;
		sysm_set_cci_flag(RBMAGIC);

		while (sysm_check_cci_flag())
			udelay(5);

		itcs_icache_invalid();
		itcs_dcache_invalid_range((phys_addr_t)ptr, len);
		tmp_crc_val = lib_crc32_le(0, ptr, len);
		if (tmp_crc_val != crc_save) {
			printf("Core %d loop count %d failed, 0x%x, 0x%x\n", __get_MHARTID(), tmp_loop_cnt, tmp_crc_val, crc_save);
			ret = -1;
			goto err;
		}
		tmp_loop_cnt++;
	}
err:
	while (!sysm_check_cci_flag())
		udelay(5);
	if (ret == 0)
		printf("CCI core %d Pass\n", __get_MHARTID());
	else
		printf("CCI core %d Failed\n", __get_MHARTID());
	return 0;
}
#endif

static void sysm_show_usage(void)
{
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	printf("Usage: sysm [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("--set-clk\t\tset clk rate(param: domain(CPU, SAP, RTC), clkname, "
	       "clkrate(Mhz)): sysm "
	       "--set-clk CPU apll 1000\n");
	printf("--get-clk\t\tget clk rate(Mhz): sysm --get-clk CPU apll\n");
	printf("--set-iomode\t\tset io mode(param: domain, index, iomode(0: out, 1: "
	       "in, 2: "
	       "func), value): sysm --set-iomode CPU 10 0 0\n");
	printf("--set-iopull\t\tset io pull(param: domain, en/dis, pull(0: up, 1: "
	       "down, 2: no)): sysm --set-iopull CPUD 10 1 0\n");
	printf("--set-iovalue\t\tset io value(param: domain, index, value(0: low, 1: "
	       "high)): "
	       "sysm --set-iovalue CPU 10 0\n");
	printf("--get-iostatus\t\tget io status(param: domain, index): sysm "
	       "--get-iostatus CPU "
	       "10\n");
	printf("--gpio-test\t\ttest gpio(param: domain, startio, endio): "
	       "sysm --gpio-test CPU 0 98\n");
	printf("--clk-test\t\ttest clk: sysm --clk-test\n");
	printf("--domain-test\t\ttest domain: sysm --domain-test\n");
	printf("--gpioint-test\t\ttest gpio interrupt(param: domain, startio, endio):"
	       "sysm --gpioint-test CPU 0 98\n");
	printf("--rtcinfo-test\t\ttest rtcinfo(param: mode, domain, gpio): "
	       "sysm --rtcinfo-test poweron_reset CPU 0\n");
	printf("--softpowerdown-test\ttest soft power down: sysm "
	       "--softpowerdown-test\n");
	printf("--softreset-test\ttest soft reset: sysm --softreset-test\n");
	printf("--suspendresume-test\ttest suspend&resume(param: gpio, pullup or "
	       "pulldown): "
	       "sysm --suspendresume-test GP0 0\n");
	printf("--powerupcore-test\tpower up c920 core(param: core number): sysm "
	       "--powerupcore-test 4\n");
	printf("--powerdowncore-test\tpower down c920 core(param: core number): sysm "
	       "--powerdowncore-test 4\n");
	printf("--bootm-test\t\ttest read bootm(param: domain, startio, endio, "
	       "maxbootm): sysm --bootm-test 6 9 15\n");
	printf("--remap-e906-test\ttest remap e906: sysm --remap-e906-test\n");
	printf("--ddr-share-test\ttest e906 ddr share: sysm --ddr-share-test\n");
	printf("--security-test\t\ttest security: sysm --security-test\n");
	printf("--rtciofunc-test\touput rtcclk: sysm --rtciofunc-test rtcclk\n");
	printf("--ahb-e906-test\t\ttest e906 ahb: sysm --ahb-e906-test\n");
#endif
}

int sysm_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "abcdefghijklmnopqrstuvwxyz";
	static const struct option long_options[] = {
		{ "set-clk", 0, 0, SYSM_SET_CLK },
		{ "get-clk", 0, 0, SYSM_GET_CLK },
		{ "set-iomode", 0, 0, SYSM_SET_IOMODE },
		{ "set-iopull", 0, 0, SYSM_SET_IOPULL },
		{ "set-iovalue", 0, 0, SYSM_SET_IOVALUE },
		{ "get-iostatus", 0, 0, SYSM_GET_IOSTATUS },
		{ "gpio-test", 0, 0, SYSM_GPIO_TEST },
		{ "clk-test", 0, 0, SYSM_CLK_TEST },
		{ "domain-test", 0, 0, SYSM_DOMAIN_TEST },
		{ "gpioint-test", 0, 0, SYSM_GPIOINT_TEST },
		{ "rtcinfo-test", 0, 0, SYSM_RTCINFO_TEST },
		{ "softpowerdown-test", 0, 0, SYSM_SOFTPOWERDOWN_TEST },
		{ "softreset-test", 0, 0, SYSM_SOFTRESET_TEST },
		{ "suspendresume-test", 0, 0, SYSM_SUSPENDRESUME_TEST },
		{ "powerupcore-test", 0, 0, SYSM_POWERUPCORE_TEST },
		{ "powerdowncore-test", 0, 0, SYSM_POWERDOWNCORE_TEST },
		{ "rtciofunc-test", 0, 0, SYSM_RTCIOFUNC_TEST },
		{ "bootm-test", 0, 0, SYSM_BOOTM_TEST },
		{ "remap-e906-test", 0, 0, SYSM_REMAPE906_TEST },
		{ "ddr-share-test", 0, 0, SYSM_SHAREDDR_TEST },
		{ "security-test", 0, 0, SYSM_SECURITY_TEST },
		{ "ahb-e906-test", 0, 0, SYSM_E906AHB_TEST },
		{ "rsvd_test", 0, 0, SYSM_RSVD_TEST },
		{ "cci_cache_test", 0, 0, SYSM_CCI_CACHE_TEST },
		{ "cci_uncache_test", 0, 0, SYSM_CCI_UNCACHE_TEST },
		{ "cci_flush_test", 0, 0, SYSM_CCI_FLUSH_TEST },
		{ "cci_invalid_test", 0, 0, SYSM_CCI_INVALID_TEST },
		{ "cci_l1_test", 0, 0, SYSM_CCI_L1_TEST },
		{ 0, 0, 0, 0 },
	};
	optind = 1;

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		case SYSM_SET_CLK:
		case SYSM_GET_CLK:
#if 0
			ret = sysm_handle_clk(c, argc - optind, &argv[optind]);
#endif
			break;
		case SYSM_SET_IOMODE:
		case SYSM_SET_IOPULL:
		case SYSM_SET_IOVALUE:
		case SYSM_GET_IOSTATUS:
#if 0
			ret = sysm_handle_io(c, argc - optind, &argv[optind]);
#endif
			break;
		case SYSM_GPIO_TEST:
			ret = sysm_gpio_test(argc - optind, &argv[optind]);
			break;
		case SYSM_CLK_TEST:
			ret = sysm_clk_test();
			break;
		case SYSM_DOMAIN_TEST:
			ret = sysm_domain_test();
			break;
		case SYSM_GPIOINT_TEST:
			ret = sysm_gpioint_test(argc - optind, &argv[optind]);
			break;
		case SYSM_RTCINFO_TEST:
			ret = sysm_rtcinfo_test(argc - optind, &argv[optind]);
			break;
		case SYSM_SOFTPOWERDOWN_TEST:
		case SYSM_SOFTRESET_TEST:
			ret = sysm_power_test(c);
			break;
		case SYSM_SUSPENDRESUME_TEST:
#ifdef CONFIG_C920
			ret = sysm_suspendresume_test(argc - optind,
						      &argv[optind]);
#endif
			break;
		case SYSM_POWERUPCORE_TEST:
		case SYSM_POWERDOWNCORE_TEST:
#ifdef CONFIG_C920
			ret = sysm_powercore_test(c, argc - optind,
						  &argv[optind]);
#endif
			break;
		case SYSM_RTCIOFUNC_TEST:
			ret = sysm_rtciofunc_test(argc - optind, &argv[optind]);
			break;
		case SYSM_BOOTM_TEST:
			ret = sysm_bootm_test(argc - optind, &argv[optind]);
			break;
		case SYSM_REMAPE906_TEST:
			ret = sysm_remape906_test();
			break;
		case SYSM_SHAREDDR_TEST:
			ret = sysm_shareddr_test(argc - optind, &argv[optind]);
			break;
		case SYSM_SECURITY_TEST:
			ret = sysm_security_test();
			break;
		case SYSM_E906AHB_TEST:
			ret = sysm_e906ahb_test();
			break;
		case SYSM_RSVD_TEST:
#ifdef CONFIG_C920
			ret = sysm_rsvd_test();
#endif
			break;
		case SYSM_CCI_CACHE_TEST:
		case SYSM_CCI_UNCACHE_TEST:
#ifdef CONFIG_C920
			ret = sysm_cci_rw_test();
#endif
			break;
		case SYSM_CCI_FLUSH_TEST:
#ifdef CONFIG_C920
			is_flush_test = 1;
			ret = sysm_cci_flush_invalid_test();
#endif
			break;
		case SYSM_CCI_INVALID_TEST:
#ifdef CONFIG_C920
			is_flush_test = 0;
			ret = sysm_cci_flush_invalid_test();
#endif
			break;
		case SYSM_CCI_L1_TEST:
#ifdef CONFIG_C920
			ret = sysm_cci_l1_test();
#endif
			break;
		default:
			sysm_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (optind == 1) {
		sysm_show_usage();
		ret = -1;
		goto err;
	}

err:
	clear_getopt_data();
	optind = 1;
	return ret;

	return 0;
}



static void gpio_show_usage(void) {
	printf("Usage: gpio [OPTION]...\n\n");
	printf("-h \t\t\t Command help\n");
	printf("-s <n>\t\t\t Pin start\n");
	printf("-e <n>\t\t\t Pin end\n");
	printf("-v <0|1>   \t\t Set gpio high or low, pull up or pull down\n");
	printf("-m <0|1>   \t\t Test gpio input output\n");
	printf("-d <0|1|2> \t\t Set gpio domain at CPU|SAP|RTC\n");
	printf("-x \t\t\t Test start pin gpio func with end pin\n");
}
static int atoi(char *s) {
	int i;
	int n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
		n = 10 * n + (s[i] - '0');
	}
	return n;
}

static void sysm_gpio_get_test(int domain, int output_pin, int input_pin)
{
	int value, i;
	int test_value[2] = {0, 1};
	int mode;

	itcs_pads_set_mode(domain, input_pin, PADS_MODE_IN, 0);

	for(i = 0; i < 2; ++i)
	{
		value = !test_value[i];

		if (value == 0)
			itcs_pads_set_pull(domain, input_pin, 1, PADS_PULL_DOWN);
		else
			itcs_pads_set_pull(domain, input_pin, +1, PADS_PULL_UP);

		itcs_pads_set_mode(domain, output_pin, PADS_MODE_OUT, test_value[i]);
		udelay(1);

		value = itcs_pads_get_value(domain, input_pin, &mode);
		if (value != test_value[i] || mode != PADS_MODE_IN)
			printf("error : ");
		else
			printf("sucess: ");

		printf("output %d intput %d get value: %d\n",output_pin, input_pin, value);
	}
}

static int sysm_single_gpio_test(int domain, int test_pin, int pin)
{
	sysm_gpio_get_test(domain, test_pin, pin);
	sysm_gpio_get_test(domain, pin, test_pin);
	sysm_single_gpioint_test(domain, pin, test_pin);
	return 0;
}

static int gpio_main(int argc, char *argv[]) {
	int c, option_index = 0;
	int start, end, value, mode, domain;
	int i, tmp;
	int test_start_pin_func = 0;

	static const char short_options[] = "s:e:v:m:d:x";
	static const struct option long_options[] = {
		{ 0, 0, 0, 0 },
	};

	start = end = value = mode = domain = 0;

	while ((c = getopt_long(argc, argv, short_options, long_options,
		&option_index)) != -1) {
		switch (c) {
		case 's':
			start = atoi(optarg);
			break;

		case 'e':
			end = atoi(optarg);
			break;

		case 'v':
			value = atoi(optarg);
			break;

		case 'm':
			mode = atoi(optarg);
			break;

		case 'd':
			domain = atoi(optarg);
			break;     

		case 'x':
			test_start_pin_func = 1;
			break;     

		case 'h':
		default:
			gpio_show_usage();
			goto exit;
		}
	}

	if (test_start_pin_func)
	{
		sysm_single_gpio_test(domain, start, end);
		goto exit;
	}

	if (end == 0)
		end = start;

	switch (mode) {
	case 0: /*gpio in*/
		for (i = start; i <= end; ++i)
		{
			itcs_pads_set_mode(domain, i, PADS_MODE_IN, 0);
			if (value == 0)
				itcs_pads_set_pull(domain, i, 1, PADS_PULL_DOWN);
			else
				itcs_pads_set_pull(domain, i, 1, PADS_PULL_UP);

			tmp = itcs_pads_get_value(domain, i, &mode);
			printf("domain %d gpio %d read value = %d\n", domain, i, tmp);
		}
		break;

	case 1: /* gpio out */
		itcs_pads_set_mode(domain, PADSRANGE(start, end), PADS_MODE_OUT, value);
		break;

	default:
		printf("no such mode = %d\n", mode);
		break;
	}

exit:
	optind = 1;
	return 0;
}

void sysm_init(void)
{
	register_testbench("sysm", sysm_main, NULL);
}

testbench_init(sysm_init);

void gpio_test_init(void)
{
	register_testbench("gpio", gpio_main, NULL);
}

testbench_init(gpio_test_init);
