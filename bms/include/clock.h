#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <asm/io.h>
#include <stdbool.h>
#include <common.h>

#define CRYSTAL 24000
#define KHZ 1000

#ifndef SIM_CLK
#define SIM_CLK 20000000
#endif

#define FPGA_CLK 48000000

#define FPGA_GCLK1 48000000
#ifdef CONFIG_DRV_CODEC_ES8388
#define FPGA_GCLK2 24576000
#else
#define FPGA_GCLK2 24000000
#endif
#define FPGA_GCLK3 50000000
#define FPGA_GCLK4 48000000
#define FPGA_GCLK5 48000000
#define FPGA_GCLK6 125000000
#define FPGA_GCLK7 50000000
#define FPGA_GCLK8 100000000

#define FPGA_RTC_CLK FPGA_GCLK1 // rtc
#define FPGA_SAP_CLK FPGA_GCLK2 // sap system clk
#define FGPA_PAPB_CLK FPGA_GCLK3 // cpu apb
#define FGPA_BUS_CLK FPGA_GCLK4 // bus1 ~ bus6 clk
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
#define FGPA_SD_EXT_CLK 100000000 // sd extclk [40~80]MHZ
#else
#define FGPA_SD_EXT_CLK FPGA_GCLK7 // sd extclk [40~80]MHZ
#endif
#define FGPA_USB_APP_CLK FPGA_GCLK6 // usb app clk
#define FGPA_DDR_REF_CLK FPGA_GCLK8 // ddr
#define FGPA_CPU_CLK FPGA_GCLK5 // cpu core clk

#ifdef CONFIG_COMPILE_RTL
#define RTC_CLK 24000000
#else
#define RTC_CLK FPGA_GCLK1
#endif

#define PLL_RANGE 0x000
#define PLL_DIVR 0x004
#define PLL_DIVFI 0x008
#define PLL_DIVQ 0x00c
#define PLL_DIVFF 0x010
#define PLL_DIVQF 0x014
#define PLL_SSCFG 0x018
#define PLL_LDCFG 0x01c
#define PLL_ENABLE 0x20
#define PLL_SEL 0x24
#define PLL_LOCK 0x28

#define CLK_RANGE_OFFSET 0
#define CLK_RANGE_MASK (0x7 << CLK_RANGE_OFFSET)
#define CLK_BYPASS_OFFSET 4
#define CLK_BYPASS_MASK (1 << CLK_BYPASS_OFFSET)

#define CLK_DIVR_OFFSET 0
#define CLK_DIVR_MASK (0x3f << CLK_DIVR_OFFSET)

#define CLK_DIVFI_OFFSET 0
#define CLK_DIVFI_MASK (0x1ff << CLK_DIVFI_OFFSET)

#define CLK_DIVQ_OFFSET 0
#define CLK_DIVQ_MASK (0x1f << CLK_DIVQ_OFFSET)

#define CLK_DIVFF_OFFSET 0
#define CLK_DIVFF_MASK (0xffffff << CLK_DIVFF_OFFSET)

#define CLK_DIVQF_OFFSET 0
#define CLK_DIVQF_MASK (0x7 << CLK_DIVQF_OFFSET)

#define CLK_SSE_OFFSET 0
#define CLK_SSE_MASK (1 << CLK_SSE_OFFSET)
#define CLK_SSMD_OFFSET 1
#define CLK_SSMD_MASK (0x7 << CLK_SSMD_OFFSET)
#define CLK_SSMF_OFFSET 4
#define CLK_SSMF_MASK (0xf << CLK_SSMF_OFFSET)
#define CLK_SSDS_OFFSET 8
#define CLK_SSDS_MASK (1 << CLK_SSDS_OFFSET)

#define CLK_OUTE_OFFSET 0
#define CLK_OUTE_MASK (1 << CLK_OUTE_OFFSET)
#define CLK_PLOAD_OFFSET 1
#define CLK_PLOAD_MASK (1 << CLK_PLOAD_OFFSET)
#define CLK_NEWDIV_OFFSET 2
#define CLK_NEWDIV_MASK (1 << CLK_NEWDIV_OFFSET)

#define CLK_ENABLE_OFFSET 0
#define CLK_ENABLE_MASK (1 << CLK_ENABLE_OFFSET)

#define CLK_SEL_OFFSET 1
#define CLK_SEL_MASK (1 << CLK_SEL_OFFSET)

#define CLK_LOCK_OFFSET 0
#define CLK_LOCK_MASK (1 << CLK_LOCK_OFFSET)

#define DIV_CLKSRC 0x0
#define DIV_CLKRATIO 0x4
#define DIV_CLKNCO 0x8
#define DIV_CLKGATE 0xc

#define CLK_SRC_OFFSET 0
#define CLK_SRC_MASK (0x7 << CLK_SRC_OFFSET)
#define CLK_MODE_OFFSET 4
#define CLK_MODE_MASK (1 << CLK_MODE_OFFSET)

#define CLK_RATIO_OFFSET 0
#define CLK_RATIO_MASK (0x7f << CLK_RATIO_OFFSET)

#define CLK_NCO_OFFSET 0
#define CLK_NCO_MASK (0xff << CLK_NCO_OFFSET)

#define CLK_GATE_OFFSET 0
#define CLK_GATE_MASK (0x1 << CLK_GATE_OFFSET)

#define APB_CLKSRC 0x0
#define APB_CLKRATIO 0x4
#define APB_LOAD 0xc

#define CLK_LOAD_OFFSET 0
#define CLK_LOAD_MASK (1 << CLK_LOAD_OFFSET)

#define CPU_LOAD 0x0
#define CPU_SRCSEL 0x4
#define CPU_DIVLEN 0x8
#define CPU_CLKSEQ 0xc
#define CPUB_CLKSEQ 0x10
#define CPUB_CLKENSEQ 0x14

#define CPU_LOAD_OFFSET 0
#define CPU_LOAD_MASK (0x1 << CPU_LOAD_OFFSET)

#define CPU_DIVEN_OFFSET 0
#define CPU_DIVEN_MASK (0x1 << CPU_DIVEN_OFFSET)
#define CPU_SRCSEL_OFFSET 1
#define CPU_SRCSEL_MASK (0x1 << CPU_SRCSEL_OFFSET)

#define CPU_DIVLEN_OFFSET 0
#define CPU_DIVLEN_MASK (0x1f << CPU_DIVLEN_OFFSET)

#define CPU_CLKSEQ0_OFFSET 0
#define CPU_CLKSEQ0_MASK (0xffffffff << CPU_CLKSEQ0_OFFSET)

#define CPU_CLKSEQ1_OFFSET 0
#define CPU_CLKSEQ1_MASK (0xffffffff << CPU_CLKSEQ1_OFFSET)

#define CPU_CLKENSEQ_OFFSET 0
#define CPU_CLKENSEQ_MASK (0xffffffff << CPU_CLKENSEQ_OFFSET)

#define PLL_OUTPUT_MAX 3000000
#define PLL_OUTPUT_MIN 20000
#define PLL_VCO_MAX 6000000
#define PLL_VCO_MIN 1200000
#define PLL_OUTPUTF_MAX 6000000
#define PLL_OUTPUTF_MIN 171000
#define PLL_PFD_INT_MAX 200000
#define PLL_PFD_INT_MIN 10000
#define PLL_PFD_FAC_MAX 7500
#define PLL_PFD_FAC_MIN 5000

enum { PLL, DIV, APB, CPUB };

enum { DIVR, DIVQ, DIVQF };

enum { CENTER_SPREAD, DOWN_SPREAD };

#define PARA_RANGE(min, max) (min | (max << 16))
#define GetRangeMin(range) (range & 0xffff)
#define GetRangeMax(range) ((range >> 16) & 0xffff)

#define ENABLE 1
#define DISABLE 0

#define CPURATIO(a, b, c) \
	(((a & 0xff) << 16) | ((b & 0xff) << 8) | ((c & 0xff) << 0))
#define GetCPUBRatio(n) (n & 0xff)
#define GetCPURatio(n) ((n >> 8) & 0xff)
#define GetPllRatio(n) ((n >> 16) & 0xff)

typedef struct cpuratio {
	int ratio;
	uint32_t cpu_divlen;
	uint32_t cpu_clkseq;
	uint32_t cpub_clkseq;
	uint32_t cpub_clkenseq;
} cpuratio_t;

typedef struct plldiv {
	int64_t clkrate;
	int divr;
	int divq;
	int divqf;
	int divfi;
	int divff;
	int range;
	bool isqf;
} plldiv_t;

typedef struct clk_dev {
	const char *name;
	unsigned long addr;
	int clkmode;
	int pll_type;//0: normal 1: bpll 2:cpll
} clk_dev_t;

#define isPLL(dev) (dev->clkmode == PLL)
#define isAPB(dev) (dev->clkmode == APB)
#define isCPU(dev) (dev->clkmode == CPUB)

#define clk_readl nbits_readl
#define clk_writel nbits_writel

#ifdef CONFIG_DRV_SYSM
extern int64_t itcs_pll_set_clock(domain_t sysmode, const char *pll,
				  int64_t freq, bool fraction);
extern int64_t itcs_pll_get_clock(domain_t sysmode, const char *pll);
extern int64_t itcs_module_set_clock(domain_t sysmode, const char *module,
				     const char *pll, int64_t freq, bool nco);
extern int64_t itcs_module_get_clock(domain_t sysmode, const char *module);
extern void itcs_module_disable_clock(domain_t sysmode, const char *module);
extern void itcs_module_enable_clock(domain_t sysmode, const char *module);

#elif defined(CONFIG_COMPILE_SIM)

static inline int64_t itcs_pll_set_clock(domain_t sysmode, const char *pll,
					 int64_t freq, bool fraction)
{
	return 0;
}

static inline int64_t itcs_pll_get_clock(domain_t sysmode, const char *pll)
{
	return SIM_CLK;
}

static inline int64_t itcs_module_set_clock(domain_t sysmode,
					    const char *module, const char *pll,
					    int64_t freq, bool nco)
{
	return 0;
}

static inline int64_t itcs_module_get_clock(domain_t sysmode,
					    const char *module)
{
	return SIM_CLK;
}

static inline void itcs_module_disable_clock(domain_t sysmode,
					     const char *module)
{
}

static inline void itcs_module_enable_clock(domain_t sysmode,
					    const char *module)
{
}
#else /* CONFIG_DRV_SYSM */
static inline int64_t itcs_pll_set_clock(domain_t sysmode, const char *pll,
					 int64_t freq, bool fraction)
{
	return -1;
}

static inline int64_t itcs_pll_get_clock(domain_t sysmode, const char *pll)
{
	return -1;
}

static inline int64_t itcs_module_set_clock(domain_t sysmode,
					    const char *module, const char *pll,
					    int64_t freq, bool nco)
{
	return -1;
}

static inline int64_t itcs_module_get_clock(domain_t sysmode,
					    const char *module)
{
	return -1;
}

static inline void itcs_module_disable_clock(domain_t sysmode,
					     const char *module)
{
}

static inline void itcs_module_enable_clock(domain_t sysmode,
					    const char *module)
{
}

#endif /* CONFIG_DRV_SYSM */

#endif
