#include <common.h>
#include <initcall.h>
#include <asm/io.h>
#include <div64.h>
#include <pm.h>
#include "calpll.h"

clk_dev_t cpu_clks[] = {
    {"apll", 0xc2f08000, PLL, 0},     {"bpll", 0xc2f083c0, PLL, 1}, // bpll
    {"cpll", 0xc2f08340, PLL, 2},                                   // cpll
    {"dpll", 0xc2f08030, PLL, 0},     {"epll", 0xc2f08060, PLL, 0},
    {"vpll", 0xc2f08090, PLL, 0},     {"apb", 0xc2f080c0, APB, 0},
    {"bus1", 0xc2f080d0, DIV, 0},     {"bus2", 0xc2f080e0, DIV, 0},
    {"bus3", 0xc2f080f0, DIV, 0},     {"bus4", 0xc2f08100, DIV, 0},
    {"bus5", 0xc2f08110, DIV, 0},     {"bus6", 0xc2f08120, DIV, 0},
    {"ddr0", 0xc2f08130, DIV, 0},     {"ttc", 0xc2f08140, DIV, 0},
    {"spi", 0xc2f08150, DIV, 0},      {"uart", 0xc2f08160, DIV, 0},
    {"iis0", 0xc2f08170, DIV, 0},     {"iis1", 0xc2f08170, DIV, 0},
    {"mi2s0", 0xc2f08170, DIV, 0},    {"extern", 0xc2f08180, DIV, 0},
    {"reg bus", 0xc2f08190, DIV, 0},  {"emmc0", 0xc2f081a0, DIV, 0},
    {"ospi", 0xc2f081a0, DIV, 0},     {"sd1", 0xc2f081b0, DIV, 0},
    {"sd2", 0xc2f081c0, DIV, 0},      {"qspi", 0xc2f081d0, DIV, 0},
    {"usb3 ref", 0xc2f081e0, DIV, 0}, {"usb2 ref", 0xc2f081f0, DIV, 0},
    {"usb stb", 0xc2f08200, DIV, 0},  {"usb app", 0xc2f08210, DIV, 0},
    {"usb lpm", 0xc2f08220, DIV, 0},  {"gmac tsu", 0xc2f08230, DIV, 0},
    {"gmac gtx", 0xc2f08240, DIV, 0}, {"gmac ref", 0xc2f08250, DIV, 0},
    {"pvt", 0xc2f08260, DIV, 0},      {"vdec", 0xc2f08270, DIV, 1}, // Use bpll
    {"cae", 0xc2f08280, DIV, 0},      {"ddr1", 0xc2f082a0, DIV, 0},
    {"ids_etc", 0xc2f082b0, DIV, 0},  {"ids_eitf", 0xc2f082c0, DIV, 0},
    {"vip0", 0xc2f082d0, DIV, 2}, // Use cpll
    {"vip1", 0xc2f082e0, DIV, 2}, // Use cpll
    {"dmic", 0xc2f082f0, DIV, 0},     {"cpu", 0xc2f08380, CPUB, 0},
    {"cpub", 0xc2f08380, CPUB, 0},    {NULL}};

clk_dev_t sap_clk[] = {
    {"spll", 0xd2f08000, PLL, 0},
#ifndef CONFIG_COMPILE_ASIC
    {"spll-qf", 0xd2f08000, PLL, 0},
#endif
    {"apc", 0xd2f080c0, APB, 0},      {"apb", 0xd2f080d0, APB, 0},
    {"bus1", 0xd2f080e0, DIV, 0},     {"ttc", 0xd2f080f0, DIV, 0},
    {"spi", 0xd2f08100, DIV, 0},      {"uart", 0xd2f08110, DIV, 0},
    {"puf eng", 0xd2f08120, DIV, 0},  {"puf xtl", 0xd2f08130, DIV, 0},
    {"gmac tsu", 0xd2f08140, DIV, 0}, {"gmac gtx", 0xd2f08150, DIV, 0},
    {"gmac ref", 0xd2f08160, DIV, 0}, {NULL}};

/* specially for RTL */
static plldiv_t divlist[] = {
	{504000, 1, 4, 0, 104, 0, 2, false},
    {2004000, 1, 0, 1, 0x52, 0, 2, false},
    {1368000, 3, 0, 0, 0x71, 0, 0, false},
    {2496000, 0, 0, 0, 51, 0, 3, false},
    {1500000, 1, 1, 0, 124, 0, 2, false},
    {1440000, 0, 0, 0, 29, 0, 3, false },
    {2457600, 3, 0, 0, 203, 13421824, 0, false},
	{2376000, 1, 0, 0, 98, 0, 2, false},//BPLL
	{2424000, 3, 0, 0, 201, 0, 0, false},//EPLL
    {2112000, 0, 0, 0, 43, 0, 3, false},
    {2016000, 0, 0, 0, 41, 0, 3, false},
    {1327100, 3, 0, 0, 109, 9926528, 0, false},

	{ 0 },
};

static cpuratio_t cpuratio[] = {
	{ CPURATIO(1, 1, 4), 3, 0, 3, 2 },
	{ CPURATIO(1, 2, 4), 3, 5, 3, 0xc },
};

static cpuratio_t *get_cpuratio(int ratio)
{
	for (int i = 0; i < ARRAY_SIZE(cpuratio); i++) {
		if (cpuratio[i].ratio == ratio)
			return &cpuratio[i];
	}

	return NULL;
}

static cpuratio_t *get_cpuratio_by_reg(clk_dev_t *clk)
{
	for (int i = 0; i < ARRAY_SIZE(cpuratio); i++) {
		if (!memcmp(&(cpuratio[i].cpu_divlen),
			    (void *)(clk->addr + CPU_DIVLEN), 0x10))
			return &cpuratio[i];
	}

	return NULL;
}

static clk_dev_t *get_clk(domain_t sysmode, const char *name)
{
	clk_dev_t *clks = ((sysmode == CPU) ? cpu_clks : sap_clk);
	for (int i = 0; clks[i].name; i++)
		if (!strncmp(clks[i].name, name, 16))
			return &clks[i];

	return NULL;
}

char *cpu_clksource[] = { "apll", "dpll", "epll", "vpll", "mosc_clk", "bpll", "cpll", NULL };
char *sap_clksource[] = { "spll", "spll-qf", "rsvd", "rsvd", "mosc_clk", NULL };

static int get_clk_type(domain_t sysmode, const char *name)
{
	char **clksource = ((sysmode == CPU) ? cpu_clksource : sap_clksource);

	for (int i = 0; clksource[i]; i++)
		if (!strcmp(clksource[i], name)){
			if(strcmp(clksource[i],"cpll")==0){
				return 5;
			}
			return i;
		}


	return -1;
}

static int64_t get_parent_clock(domain_t sysmode, clk_dev_t *clk)
{
	clk_dev_t *parent_clk = NULL;
	int clksrc;
	char **clksource = ((sysmode == CPU) ? cpu_clksource : sap_clksource);

	if (!clk)
		return -1;

	clksrc = clk_readl(R(clk, DIV_CLKSRC), CLK_SRC_MASK, CLK_SRC_OFFSET);
	if (!strcmp(clksource[clksrc], "mosc_clk"))
		return (CRYSTAL * KHZ);

	if(clk->pll_type ==2)
		clksrc +=1;
		
	parent_clk = get_clk(sysmode, clksource[clksrc]);

	if (isPLL(parent_clk))
		return itcs_pll_get_clock(sysmode, clksource[clksrc]);
	else
		return -1;
}

static int is_clock_bypass(clk_dev_t *clk)
{
	if (!clk || !isPLL(clk))
		return 0;

	return (clk_readl(R(clk, PLL_RANGE), CLK_BYPASS_MASK,
			  CLK_BYPASS_OFFSET) ||
		!clk_readl(R(clk, PLL_SEL), CLK_SEL_MASK, CLK_SEL_OFFSET));
}

static int is_clock_enabled(clk_dev_t *clk)
{
	int en = 0;

	if (isPLL(clk)) {
		en = clk_readl(R(clk, PLL_ENABLE), CLK_ENABLE_MASK,
			       CLK_ENABLE_OFFSET);
		en = (en || is_clock_bypass(clk));
	} else if (isAPB(clk)) {
		en = 1;
	} else
		en = !clk_readl(R(clk, DIV_CLKGATE), CLK_GATE_MASK,
				CLK_GATE_OFFSET);

	return en;
}

static int get_pll_const_parameter(plldiv_t *div, int64_t clk)
{
	if (!div)
		return -1;

	for (int i = 0; divlist[i].clkrate; i++) {
		if (divlist[i].clkrate == clk) {
			/* memcpy is too slowly */
			// memcpy(div, &divlist[i], sizeof(plldiv_t));
			div->clkrate = divlist[i].clkrate;
			div->divr = divlist[i].divr;
			div->divq = divlist[i].divq;
			div->divqf = divlist[i].divqf;
			div->divfi = divlist[i].divfi;
			div->divff = divlist[i].divff;
			div->range = divlist[i].range;
			div->isqf = divlist[i].isqf;
			return 0;
		}
	}
	return -1;
}

static bool is_plloutF(const char *name)
{
	return (strstr(name, "-qf") ? true : false);
}

int64_t itcs_pll_set_clock(domain_t sysmode, const char *pll, int64_t freq,
			   bool fraction)
{
	clk_dev_t *clk = NULL;
	plldiv_t div;
	int ret;

	freq = lldiv(freq, KHZ);
	if (freq < PLL_OUTPUT_MIN || freq > PLL_OUTPUT_MAX)
		return -1;

	clk = get_clk(sysmode, pll);
	if (!clk || !isPLL(clk)) {
		printf("Clock(%s) can not found in clock list\n", pll);
		return -1;
	}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
	if (!strncmp(pll, "spll", 4) || !strncmp(pll, "spll-qf", 7))
		return FPGA_SAP_CLK / 24 * 60;
	else
		return FGPA_CPU_CLK;
#endif
	if (is_plloutF(pll)) {
		int64_t rate;

		div.clkrate = itcs_pll_get_clock(sysmode, pll);
		if (div.clkrate < 0)
			return -1;

		div.clkrate = lldiv(div.clkrate, KHZ);
		div.isqf = true;
		div.divqf = clk_readl(R(clk, PLL_DIVQF), CLK_DIVQF_MASK,
				      CLK_DIVQF_OFFSET);
		rate = div.clkrate * (div.divqf + 1);
		div.divqf = lldiv(rate + freq - 1, freq) - 1;

		if (div.divqf < 0 || div.divqf > 7) {
			printf("Clock(%s) can not be divided: 0x%x\n", pll,
			       div.divqf);
			return -1;
		}

		div.clkrate = rate / (div.divqf + 1);
	} else {
		if (get_pll_const_parameter(&div, freq) < 0) {
			ret = pll_cal_parameter(&div, freq, fraction);
			if (ret < 0)
				return -1;
		}
	}

	/* select reference clk */
	clk_writel(R(clk, PLL_SEL), CLK_SEL_MASK, CLK_SEL_OFFSET, 0);
	/* pll disable */
	clk_writel(R(clk, PLL_ENABLE), CLK_ENABLE_MASK, CLK_ENABLE_OFFSET,
		   DISABLE);
	/* pll load disbale */
	clk_writel(R(clk, PLL_LDCFG), CLK_PLOAD_MASK, CLK_PLOAD_OFFSET,
		   DISABLE);

	if (div.isqf)
		clk_writel(R(clk, PLL_DIVQF), CLK_DIVQF_MASK, CLK_DIVQF_OFFSET,
			   div.divqf);
	else {
		clk_writel(R(clk, PLL_RANGE), CLK_RANGE_MASK, CLK_RANGE_OFFSET,
			   div.range);
		clk_writel(R(clk, PLL_DIVR), CLK_DIVR_MASK, CLK_DIVR_OFFSET,
			   div.divr);
		clk_writel(R(clk, PLL_DIVQ), CLK_DIVQ_MASK, CLK_DIVQ_OFFSET,
			   div.divq);
		clk_writel(R(clk, PLL_DIVFI), CLK_DIVFI_MASK, CLK_DIVFI_OFFSET,
			   div.divfi);
		clk_writel(R(clk, PLL_DIVFF), CLK_DIVFF_MASK, CLK_DIVFF_OFFSET,
			   div.divff);
		clk_writel(R(clk, PLL_DIVQF), CLK_DIVQF_MASK, CLK_DIVQF_OFFSET,
			   div.divqf);
	}

	clk_writel(R(clk, PLL_LDCFG), CLK_PLOAD_MASK, CLK_PLOAD_OFFSET, ENABLE);

	clk_writel(R(clk, PLL_ENABLE), CLK_ENABLE_MASK, CLK_ENABLE_OFFSET,
		   ENABLE);

	/* wait n ms */
	for (int i = 0;
	     (i < 6666) &&
	     !clk_readl(R(clk, PLL_LOCK), CLK_LOCK_MASK, CLK_LOCK_OFFSET);
	     i++)
		;

	clk_writel(R(clk, PLL_SEL), CLK_SEL_MASK, CLK_SEL_OFFSET, 1);
	return div.clkrate * KHZ;
}

int64_t itcs_pll_get_clock(domain_t sysmode, const char *pll)
{
	clk_dev_t *clk = NULL;
	plldiv_t div;

	clk = get_clk(sysmode, pll);
	if (!clk || !isPLL(clk)) {
		printf("Clock(%s) can not found in clock list\n", pll);
		return -1;
	}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
	if (!strncmp(pll, "spll", 4) || !strncmp(pll, "spll-qf", 7))
		return FPGA_SAP_CLK / 24 * 60;
	else
		return FGPA_CPU_CLK;
#endif

	if (!is_clock_enabled(clk)) {
		printf("Clock(%s) is disabled\n", pll);
		return -1;
	}

	if (is_clock_bypass(clk))
		return (CRYSTAL * KHZ);

	/* check wether PLLOUTF or not */
	if (is_plloutF(pll))
		div.isqf = true;
	else
		div.isqf = false;

	div.divr = clk_readl(R(clk, PLL_DIVR), CLK_DIVR_MASK, CLK_DIVR_OFFSET);
	div.divq = clk_readl(R(clk, PLL_DIVQ), CLK_DIVQ_MASK, CLK_DIVQ_OFFSET);
	div.divqf =
		clk_readl(R(clk, PLL_DIVQF), CLK_DIVQF_MASK, CLK_DIVQF_OFFSET);
	div.divfi =
		clk_readl(R(clk, PLL_DIVFI), CLK_DIVFI_MASK, CLK_DIVFI_OFFSET);
	div.divff =
		clk_readl(R(clk, PLL_DIVFF), CLK_DIVFF_MASK, CLK_DIVFF_OFFSET);
	return ((int64_t)pll_get_actual_clock(&div) * KHZ);
}

static int64_t apb_set_clk(domain_t sysmode, clk_dev_t *clk, const char *pll,
			   int64_t need_freq)
{
	int64_t parent_clk;
	int div, type;

	if (pll) {
		parent_clk = itcs_pll_get_clock(sysmode, pll);
		if (parent_clk < 0) {
			printf("Get parent clk Err\n");
			return -1;
		}

		type = get_clk_type(sysmode, pll);
	} else
		parent_clk = get_parent_clock(sysmode, clk);

	div = lldiv(parent_clk + need_freq - 1, need_freq);
	if (div)
		div -= 1;

	clk_writel(R(clk, APB_LOAD), CLK_LOAD_MASK, CLK_LOAD_OFFSET, 0);

	if (pll)
		clk_writel(R(clk, APB_CLKSRC), CLK_SRC_MASK, CLK_SRC_OFFSET,
			   type);

	clk_writel(R(clk, APB_CLKRATIO), CLK_RATIO_MASK, CLK_RATIO_OFFSET, div);

	clk_writel(R(clk, APB_LOAD), CLK_LOAD_MASK, CLK_LOAD_OFFSET, 1);

	return lldiv(parent_clk, div + 1);
}

static int64_t cpu_set_clk(domain_t sysmode, clk_dev_t *clk, const char *pll,
			   int64_t ratio)
{
	cpuratio_t *cpu = NULL;
	int type = 0;

	if (!clk)
		return -1;

	cpu = get_cpuratio(ratio);
	if (!cpu) {
		printf("Get CPU Ratio Err: 0x%lx\n", ratio);
		return -1;
	}

	if (pll) {
		type = get_clk_type(sysmode, pll);
		if (type > 1) {
			printf("Do not support this parent(support apll or dpll): %s\n",
			       pll);
			return -1;
		}
	}

	if (ratio == CPURATIO(1, 2, 4))
		clk_writel(R(clk, CPU_LOAD), 0x3, CPU_LOAD_OFFSET, DISABLE);
	else
		clk_writel(R(clk, CPU_LOAD), CPU_LOAD_MASK, CPU_LOAD_OFFSET, DISABLE);

	if (pll)
		/* set div parent */
		clk_writel(R(clk, CPU_SRCSEL), CPU_SRCSEL_MASK,
			   CPU_SRCSEL_OFFSET, type);

	/* If APLL:CPU CLK = 1:1, must use bypass mode */
	if (GetCPURatio(cpu->ratio) == 1)
		clk_writel(R(clk, CPU_SRCSEL), CPU_DIVEN_MASK, CPU_DIVEN_OFFSET,
			   0);
	else
		clk_writel(R(clk, CPU_SRCSEL), CPU_DIVEN_MASK, CPU_DIVEN_OFFSET,
			   1);

	clk_writel(R(clk, CPU_DIVLEN), CPU_DIVLEN_MASK, CPU_DIVLEN_OFFSET,
		   cpu->cpu_divlen);
	clk_writel(R(clk, CPU_CLKSEQ), CPU_CLKSEQ0_MASK, CPU_CLKSEQ0_OFFSET,
		   cpu->cpu_clkseq);
	clk_writel(R(clk, CPUB_CLKSEQ), CPU_CLKSEQ1_MASK, CPU_CLKSEQ1_OFFSET,
		   cpu->cpub_clkseq);
	clk_writel(R(clk, CPUB_CLKENSEQ), CPU_CLKENSEQ_MASK,
		   CPU_CLKENSEQ_OFFSET, cpu->cpub_clkenseq);

	if (ratio == CPURATIO(1, 2, 4))
		clk_writel(R(clk, CPU_LOAD), 0x3, CPU_LOAD_OFFSET, 0x3);
	else
		clk_writel(R(clk, CPU_LOAD), CPU_LOAD_MASK, CPU_LOAD_OFFSET, ENABLE);

	return ratio;
}

static int64_t cpu_get_clk(domain_t sysmode, clk_dev_t *clk)
{
	cpuratio_t *cpu;
	int iscpub = 0, bypass = 0;
	int64_t parent_clk;
	int type;

	if (!strcmp(clk->name, "cpub"))
		iscpub = 1;

	type = clk_readl(R(clk, CPU_SRCSEL), CPU_SRCSEL_MASK,
			 CPU_SRCSEL_OFFSET);
	parent_clk = itcs_pll_get_clock(sysmode, cpu_clksource[type]);
	if (parent_clk < 0)
		return -1;

	if (!iscpub) {
		bypass = !clk_readl(R(clk, CPU_SRCSEL), CPU_DIVEN_MASK,
				    CPU_DIVEN_OFFSET);
		if (bypass)
			return parent_clk;
	}

	cpu = get_cpuratio_by_reg(clk);
	if (!cpu) {
		printf("Wrong configuration in CPU&CPUB\n");
		return -1;
	}

	return (iscpub ? (parent_clk / GetCPUBRatio(cpu->ratio)) :
			       (parent_clk / GetCPURatio(cpu->ratio)));
}

int64_t itcs_module_set_clock(domain_t sysmode, const char *module,
			      const char *pll, int64_t freq, bool nco)
{
	clk_dev_t *clk = NULL;
	int64_t clkrate;
	int div = 0;
	int type = 0;

	if (!strncmp(module, "rtc", 3))
		return RTC_CLK;

	clk = get_clk(sysmode, module);
	if (!clk || isPLL(clk)) {
		printf("Clock(%s) can not found in clock list\n", module);
		return -1;
	}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
	if (sysmode == SAP) {
		if (!strncmp(module, "apb", 3))
			return FPGA_SAP_CLK / 24 * 50;
		else
			return FPGA_SAP_CLK;
	} else {
		if (!strncmp(module, "bus", 3))
			return FGPA_BUS_CLK;
		else if (!strncmp(module, "apb", 3) ||
			 !strncmp(module, "reg bus", 7))
			return FGPA_PAPB_CLK;
		else if (!strncmp(module, "sd1", 3) ||
			 !strncmp(module, "sd2", 3) ||
			 !strncmp(module, "emmc0", 5) ||
			 !strncmp(module, "qspi", 4))
			return FGPA_SD_EXT_CLK;
		else if (!strncmp(module, "usb", 3))
			return FGPA_USB_APP_CLK;
		else if (!strncmp(module, "ddr0", 4) || !strncmp(module, "ddr1", 4))
			return FGPA_DDR_REF_CLK;
		else
			return FPGA_SAP_CLK;
	}
#endif

	if (isAPB(clk))
		return apb_set_clk(sysmode, clk, pll, freq);
	else if (isCPU(clk))
		return cpu_set_clk(sysmode, clk, pll, freq);

	clk_writel(R(clk, DIV_CLKGATE), CLK_GATE_MASK, CLK_GATE_OFFSET, 1);

	if (pll)
		clkrate = itcs_pll_get_clock(sysmode, pll);
	else
		clkrate = get_parent_clock(sysmode, clk);
	if (clkrate < 0) {
		printf("Get parent clock Err: %ld\n", clkrate);
		return -1;
	}

	if (pll) {
		type = get_clk_type(sysmode, pll);
		clk_writel(R(clk, DIV_CLKSRC), CLK_SRC_MASK, CLK_SRC_OFFSET,
			   type);
	}

	if (nco) {
		div = lldiv(lldiv(clkrate, KHZ) + lldiv(freq, KHZ) * 256 - 1,
			    lldiv(clkrate, KHZ));
		clk_writel(R(clk, DIV_CLKNCO), CLK_NCO_MASK, CLK_NCO_OFFSET,
			   div);
		clk_writel(R(clk, DIV_CLKSRC), CLK_MODE_MASK, CLK_MODE_OFFSET,
			   1);
	} else {
		div = lldiv(clkrate + freq - 1, freq);
		if (div)
			div -= 1;

		clk_writel(R(clk, DIV_CLKRATIO), CLK_RATIO_MASK,
			   CLK_RATIO_OFFSET, div);
		clk_writel(R(clk, DIV_CLKSRC), CLK_MODE_MASK, CLK_MODE_OFFSET,
			   0);
	}

	clk_writel(R(clk, DIV_CLKGATE), CLK_GATE_MASK, CLK_GATE_OFFSET, 0);
	return (nco ? (lldiv(clkrate, 0x100) * div) : lldiv(clkrate, div + 1));
}

int64_t itcs_module_get_clock(domain_t sysmode, const char *module)
{
	clk_dev_t *clk = NULL;
	int64_t clkrate;
	int nco = 0, div;

	if (!strncmp(module, "rtc", 3))
		return RTC_CLK;

	clk = get_clk(sysmode, module);
	if (!clk || isPLL(clk)) {
		printf("Clock(%s) can not found in clock list\n", module);
		return -1;
	}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
	if (sysmode == SAP) {
		if (!strncmp(module, "apb", 3))
			return FPGA_SAP_CLK / 24 * 50;
		else
			return FPGA_SAP_CLK;
	} else {
		if (!strncmp(module, "bus", 3))
			return FGPA_BUS_CLK;
		else if (!strncmp(module, "apb", 3) ||
			 !strncmp(module, "reg bus", 7))
			return FGPA_PAPB_CLK;
		else if (!strncmp(module, "sd1", 3) ||
			 !strncmp(module, "sd2", 3) ||
			 !strncmp(module, "emmc0", 5) ||
			 !strncmp(module, "qspi", 4))
			return FGPA_SD_EXT_CLK;
		else if (!strncmp(module, "usb", 3))
			return FGPA_USB_APP_CLK;
		else if (!strncmp(module, "ddr0", 4) || !strncmp(module, "ddr1", 4))
			return FGPA_DDR_REF_CLK;
		else
			return FPGA_SAP_CLK;
	}
#endif
	if (isCPU(clk))
		return cpu_get_clk(sysmode, clk);

	clkrate = get_parent_clock(sysmode, clk);
	if (clkrate < 0) {
		printf("Get parent clock Err\n");
		return -1;
	}

	if (!is_clock_enabled(clk)) {
		printf("Clock(%s) is disabled\n", module);
		return -1;
	}

	if (!isAPB(clk))
		nco = clk_readl(R(clk, DIV_CLKSRC), CLK_MODE_MASK,
				CLK_MODE_OFFSET);

	if (nco)
		div = clk_readl(R(clk, DIV_CLKNCO), CLK_NCO_MASK,
				CLK_NCO_OFFSET);
	else
		div = clk_readl(R(clk, DIV_CLKRATIO), CLK_RATIO_MASK,
				CLK_RATIO_OFFSET);
	return (nco ? lldiv(clkrate, 0x100) * div : lldiv(clkrate, div + 1));
}

void itcs_module_disable_clock(domain_t sysmode, const char *module)
{
	clk_dev_t *clk = NULL;

	clk = get_clk(sysmode, module);
	if (!clk || isPLL(clk) || isCPU(clk)) {
		printf("Clock(%s) can not found in clock list\n", module);
		return;
	}

	/* TODO disable clock output */
	clk_writel(R(clk, DIV_CLKGATE), CLK_GATE_MASK, CLK_GATE_OFFSET, 1);
}

void itcs_module_enable_clock(domain_t sysmode, const char *module)
{
	clk_dev_t *clk = NULL;

	clk = get_clk(sysmode, module);
	if (!clk || isPLL(clk) || isCPU(clk)) {
		printf("Clock(%s) can not found in clock list\n", module);
		return;
	}

	/* TODO enable clock output */
	clk_writel(R(clk, DIV_CLKGATE), CLK_GATE_MASK, CLK_GATE_OFFSET, 0);
}

typedef struct suspend_clk {
	clk_dev_t *dev;
	int64_t rate;
	domain_t mode;
	char *clksource;
	bool fraction;
} suspend_clk_t;

static suspend_clk_t saveClk[64];
int clk_pm_suspend(void *privdata)
{
	int num = 0;
	for (int i = 0; cpu_clks[i].name; i++) {
#ifdef CONFIG_COMPILE_RTL
		if (!isPLL((&cpu_clks[i])))
			break;

		if (!strcmp(cpu_clks[i].name, "apll") ||
		    !strcmp(cpu_clks[i].name, "vpll"))
			continue;
#endif

		saveClk[num].dev = &cpu_clks[i];
		saveClk[num].mode = CPU;
		if (isPLL(saveClk[num].dev)) {
			saveClk[num].rate = itcs_pll_get_clock(
				saveClk[num].mode, saveClk[num].dev->name);
			saveClk[num].fraction =
				(clk_readl(R(saveClk[num].dev, PLL_DIVFF),
					   CLK_DIVFF_MASK,
					   CLK_DIVFF_OFFSET) != 0);
		} else {
			saveClk[num].rate = itcs_module_get_clock(
				saveClk[num].mode, saveClk[num].dev->name);
			saveClk[num].clksource = cpu_clksource[clk_readl(
				R(saveClk[num].dev, DIV_CLKSRC), CLK_SRC_MASK,
				CLK_SRC_OFFSET)];
		}

		num++;
	}

	for (int i = 0; sap_clk[i].name; i++) {
#ifdef CONFIG_COMPILE_RTL
		break;
#endif
		saveClk[num].dev = &sap_clk[i];
		saveClk[num].mode = SAP;
		if (isPLL(saveClk[num].dev)) {
			saveClk[num].rate = itcs_pll_get_clock(
				saveClk[num].mode, saveClk[num].dev->name);
			saveClk[num].fraction =
				(clk_readl(R(saveClk[num].dev, PLL_DIVFF),
					   CLK_DIVFF_MASK,
					   CLK_DIVFF_OFFSET) != 0);
		} else {
			saveClk[num].rate = itcs_module_get_clock(
				saveClk[num].mode, saveClk[num].dev->name);
			saveClk[num].clksource = sap_clksource[clk_readl(
				R(saveClk[num].dev, DIV_CLKSRC), CLK_SRC_MASK,
				CLK_SRC_OFFSET)];
		}

		num++;
	}

	saveClk[num].dev = NULL;
	return 0;
}

int clk_pm_resume(void *privdata)
{
	for (int i = 0; saveClk[i].dev; i++) {
		// printf("mode %d: , name %s, rate %d ", saveClk[i].mode,
		// saveClk[i].dev->name, saveClk[i].rate);
		if (isPLL(saveClk[i].dev)) {
			itcs_pll_set_clock(saveClk[i].mode,
					   saveClk[i].dev->name,
					   saveClk[i].rate,
					   saveClk[i].fraction);
		} else {
			itcs_module_set_clock(saveClk[i].mode,
					      saveClk[i].dev->name,
					      saveClk[i].clksource,
					      saveClk[i].rate, false);
		}
	}
	return 0;
}

SIMPLE_PM_OPS(clk, clk_pm_suspend, clk_pm_resume, NULL);

void clk_init(void)
{
	itcs_register_pm(&pm_clk);
}
module_init(clk_init);
