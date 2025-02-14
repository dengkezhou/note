#include <common.h>
#include <initcall.h>
#include <asm/io.h>
#include <pads.h>
#include <malloc.h>
#include <rtc-sysm.h>
#include <pm.h>

struct pads_modules_bundle fpga_iolist[] = {
	{ "gmac0",  PADSRANGE(29, 44),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "gmac1",  PADSRANGE(45, 60),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "gmac2",  PADSRANGE(99, 114),  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "gmac3",  PADSRANGE(18, 33),   PADS_FUNC0, PADS_PULL_UP, SAP, 0, 4},

	{ "emmc0",  PADSRANGE(0, 13),    PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "sd1",    PADSRANGE(14, 22),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "sd2",    PADSRANGE(23, 28),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "Emmc-v18", 12,  PADS_FUNC2, PADS_PULL_UP, CPU, 0,},
	{ "sd1-v18",  14,  PADS_FUNC2, PADS_PULL_UP, CPU, 0,},
	{ "sd2-v18",  22,  PADS_FUNC2, PADS_PULL_UP, CPU, 0,},
	{ "sd2-cd",   22,  PADS_FUNC1, PADS_PULL_UP, CPU, 0,},

	{ "iis0",   PADSRANGE(33, 37),   PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "iis1",   PADSRANGE(38, 42),   PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "iis0",   PADSRANGE(84, 88),   PADS_FUNC0, PADS_PULL_UP, CPU, 1, 4},
	{ "iis1",   PADSRANGE(89, 93),   PADS_FUNC0, PADS_PULL_UP, CPU, 1, 4},
	{ "iis0",   PADSRANGE(49, 53),   PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "iis1",   PADSRANGE(54, 58),   PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "iis0",   PADSRANGE(115, 119), PADS_FUNC2, PADS_PULL_UP, CPU, 3, 4},
	{ "iis1",   PADSRANGE(120, 124), PADS_FUNC2, PADS_PULL_UP, CPU, 3, 4},
	{ "iis0",   33, PADS_FUNC1, PADS_PULL_UP, CPU, 4, 4},
	{ "iis0",   PADSRANGE(34, 37),   PADS_FUNC2, PADS_PULL_UP, CPU, 4, 4},
	{ "iis0",   49, PADS_FUNC1, PADS_PULL_UP, CPU, 5, 4},
	{ "iis0",   PADSRANGE(34, 37),   PADS_FUNC2, PADS_PULL_UP, CPU, 5, 4},

	{ "spi0",   PADSRANGE(4, 7),     PADS_FUNC0, PADS_PULL_UP, SAP, 0, 4},
	{ "spi1",   PADSRANGE(45, 48),   PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "spi1",   PADSRANGE(29, 32),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "spi1",   PADSRANGE(80, 83),   PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},
	{ "spi2",   PADSRANGE(51, 54),   PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "spi2",   PADSRANGE(35, 38),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "spi3",   PADSRANGE(55, 58),   PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "spi3",   PADSRANGE(39, 42),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "spi3",   PADSRANGE(23, 26),   PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},

	{ "qspi",   PADSRANGE(61, 67),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},

	{ "iic0",   PADSRANGE(0, 1),     PADS_FUNC0, PADS_PULL_UP, SAP, 0, 4},
	{ "iic1",   PADSRANGE(2, 3),     PADS_FUNC0, PADS_PULL_UP, SAP, 0, 4},
	{ "iic2",   PADSRANGE(68, 69),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "iic3",   PADSRANGE(70, 71),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "iic4",   PADSRANGE(72, 73),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "iic5",   PADSRANGE(74, 75),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "iic6",   PADSRANGE(111, 112), PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "iic7",   PADSRANGE(113, 114), PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "iic3",   PADSRANGE(63, 64),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "iic4",   PADSRANGE(107, 108), PADS_FUNC2, PADS_PULL_UP, CPU, 1, 4},
	{ "iic5",   PADSRANGE(109, 110), PADS_FUNC2, PADS_PULL_UP, CPU, 1, 4},

	{ "uart0",  PADSRANGE(9, 10),    PADS_FUNC0, PADS_PULL_UP, SAP, 0, 4},
	{ "uart1",  PADSRANGE(11, 12),   PADS_FUNC0, PADS_PULL_UP, SAP, 0, 4},
	{ "uart2",  PADSRANGE(89, 92),   PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart2",  PADSRANGE(61, 62),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart2",  PADSRANGE(68, 71),   PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},
	{ "uart3",  PADSRANGE(85, 88),   PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart3",  PADSRANGE(14, 15),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart3",  PADSRANGE(72, 75),   PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},
	{ "uart3",  PADSRANGE(80, 83),   PADS_FUNC2, PADS_PULL_UP, CPU, 4, 4},
	{ "uart4",  PADSRANGE(115, 116), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart4",  PADSRANGE(99, 100),  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart4",  PADSRANGE(23, 24),   PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "uart5",  PADSRANGE(117, 118), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart5",  PADSRANGE(101, 102), PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart5",  PADSRANGE(25, 26),   PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "uart6",  PADSRANGE(119, 120), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart6",  PADSRANGE(103, 104), PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart6",  PADSRANGE(27, 28),   PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "uart7",  PADSRANGE(121, 122), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart7",  PADSRANGE(94, 95),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart7",  PADSRANGE(105, 106), PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},
	{ "uart8",  PADSRANGE(123, 124), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart8",  PADSRANGE(96, 97),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart8",  PADSRANGE(107, 108), PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},
	{ "uart9",  PADSRANGE(125, 126), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart9",  PADSRANGE(109, 110), PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart10", PADSRANGE(127, 128), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart10", PADSRANGE(111, 112), PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "uart11", PADSRANGE(113, 114), PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "uart11", PADSRANGE(78, 79),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},

	{ "jtag",   PADSRANGE(94, 98),   PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "jtag",   PADSRANGE(16, 20),   PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "jtag",   PADSRANGE(13, 17),   PADS_FUNC0, PADS_PULL_UP, SAP, 2, 4},

	{ "ids",    PADSRANGE(115, 142), PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},

	{ "mi2s0",  PADSRANGE(129,141),  PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},

	{ "ospi",	PADSRANGE(0, 13),    PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},

	{ "pwm0",    76,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm1",    77,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm2",    78,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm3",    79,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm4",    80,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm5",    81,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm6",    82,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm7",    83,  PADS_FUNC0, PADS_PULL_UP, CPU, 0, 4},
	{ "pwm0",    8,   PADS_FUNC0, PADS_PULL_UP, SAP, 1, 4},
	{ "pwm0",    65,  PADS_FUNC1, PADS_PULL_UP, CPU, 2, 4},
	{ "pwm1",    66,  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "pwm4",    12,  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "pwm5",    13,  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "pwm6",    27,  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "pwm7",    28,  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "pwm4",    29,  PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "pwm5",    30,  PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "pwm6",    31,  PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "pwm7",    32,  PADS_FUNC2, PADS_PULL_UP, CPU, 2, 4},
	{ "pwm4",    45,  PADS_FUNC2, PADS_PULL_UP, CPU, 3, 4},
	{ "pwm5",    46,  PADS_FUNC2, PADS_PULL_UP, CPU, 3, 4},
	{ "pwm6",    47,  PADS_FUNC2, PADS_PULL_UP, CPU, 3, 4},
	{ "pwm7",    48,  PADS_FUNC2, PADS_PULL_UP, CPU, 3, 4},

	{ "dmic0_0", 99,  PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic0_1", 100, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic1_0", 105, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic1_1", 101, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic2_0", 104, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic2_1", 102, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic3_0", 103, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "dmic3_1", 106, PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},

	{ "pwonslp", 2,   RTC_MUX1, PADS_PULL_UP, RTC, 0, 4},
	{ "pwm0",    5,   RTC_MUX1, PADS_PULL_UP, RTC, 0, 4},
	{ "rtcclk",  5,   RTC_MUX2, PADS_PULL_UP, RTC, 0, 4},

	{ "ext-clk",  		34,  PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "ext-clk",  		50,  PADS_FUNC1, PADS_PULL_UP, CPU, 1, 4},
	{ "usb0-drivevbus", 84,  PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "usb1-drivevbus", 93,  PADS_FUNC1, PADS_PULL_UP, CPU, 0, 4},
	{ "usb2-drivevbus", 88,  PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},
	{ "usb3-drivevbus", 92,  PADS_FUNC2, PADS_PULL_UP, CPU, 0, 4},

	{ NULL },
};

struct pads_modules_bundle fpga_rgmii_iolist[] = {
	/* codec&rgmii&usb2 */
	{ "gmac0", PADSRANGE(29, 44), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "gmac1", PADSRANGE(45, 60), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "gmac2", PADSRANGE(99, 114), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "gmac3", PADSRANGE(18, 33), PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "iis0", PADSRANGE(84, 88), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ NULL },
};

struct pads_modules_bundle fpga_emmc_iolist[] = {
	/* emmc */
	{ "emmc0", PADSRANGE(0, 13), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "sd1", PADSRANGE(14, 22), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "sd2", PADSRANGE(23, 28), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "iis0", PADSRANGE(33, 37), PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "iis1", PADSRANGE(38, 42), PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "spi0", PADSRANGE(4, 7), PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "spi1", PADSRANGE(45, 48), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "spi2", PADSRANGE(51, 54), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "spi3", PADSRANGE(55, 58), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "qspi", PADSRANGE(61, 67), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "iic0", PADSRANGE(0, 1), PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "iic1", PADSRANGE(2, 3), PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "iic2", PADSRANGE(68, 69), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "iic3", PADSRANGE(70, 71), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "iic4", PADSRANGE(72, 73), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "iic5", PADSRANGE(74, 75), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "iic6", PADSRANGE(111, 112), PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "iic7", PADSRANGE(113, 114), PADS_FUNC2, PADS_PULL_UP, CPU },	
	{ "pwm0", 76, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm1", 77, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm2", 78, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm3", 79, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm4", 80, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm5", 81, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm6", 82, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm7", 83, PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwm0", 8, PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "uart0", PADSRANGE(9, 10), PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "uart1", PADSRANGE(11, 12), PADS_FUNC0, PADS_PULL_UP, SAP },
	{ "uart2", PADSRANGE(89, 92), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart3", PADSRANGE(85, 88), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart4", PADSRANGE(115, 116), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart5", PADSRANGE(117, 118), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart6", PADSRANGE(119, 120), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart7", PADSRANGE(121, 122), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart8", PADSRANGE(123, 124), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart9", PADSRANGE(125, 126), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart10", PADSRANGE(127, 128), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "uart11", PADSRANGE(113, 114), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "jtag", PADSRANGE(94, 98), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "ids", PADSRANGE(115, 142), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ "pwonslp", 2, RTC_MUX1, PADS_PULL_UP, RTC },
	{ "pwm0", 5, RTC_MUX1, PADS_PULL_UP, RTC },
	{ "rtcclk", 5, RTC_MUX2, PADS_PULL_UP, RTC },
	{ "mi2s0", PADSRANGE(129,141), PADS_FUNC1, PADS_PULL_UP, CPU },
	{ "dmic0_0", 99, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic0_1", 100, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic1_0", 105, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic1_1", 101, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic2_0", 104, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic2_1", 102, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic3_0", 103, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ "dmic3_1", 106, PADS_FUNC2, PADS_PULL_UP, CPU },
	{ NULL },
};

struct pads_modules_bundle fpga_ospi_iolist[] = {
	/* ospi */
	{ "ospi", PADSRANGE(0, 13), PADS_FUNC0, PADS_PULL_UP, CPU },
	{ NULL },
};

struct pads_modules_bundle *bundle_list[FPGA_BIT_V_MAX] = { fpga_rgmii_iolist,
							    fpga_emmc_iolist,
							    fpga_ospi_iolist };

int is_gpio_mode(domain_t sysmode, int index)
{
	int mux;

	mux = pads_readl(PADS_CONFIG_IO(sysmode, index), PADS_MUXMODE_MASK,
			 PADS_MUXMODE_OFFSET);
	return (GPIO_MODE == mux);
}

int itcs_pads_get_mode(domain_t sysmode, uint32_t index)
{
	if (is_rtc(sysmode))
		return rtc_get_mode(index);

	if (!is_gpio_mode(sysmode, index))
		return PADS_MODE_FUNC;

	return pads_readl(GPIO_IOCTRL(sysmode, index), GPIO_DIRECTION_MASK,
			  GPIO_DIRECTION_OFFSET);
}

/*high must every bit represent output mode high/low level*/
int itcs_pads_set_mode(domain_t sysmode, int range, int mode, uint32_t value)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	uint32_t temp;
	int i = 0;

	if (is_rtc(sysmode))
		return rtc_set_mode(range, mode, value);

	if (!end)
		end = start;

	/* invalid range */
	if (end < start) {
		printf("Range Err\n");
		return -1;
	}

	for (i = start; i <= end; i++) {
		switch (mode) {
		case PADS_MODE_FUNC:
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				    PADS_MUXMODE_MASK, PADS_MUXMODE_OFFSET,
				    value);
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				    PADS_INPUTEN_MASK, PADS_INPUTEN_OFFSET,
				    ENABLE);
			break;
		case PADS_MODE_IN:
			/* set func1 mode*/
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				    PADS_MUXMODE_MASK, PADS_MUXMODE_OFFSET,
				    GPIO_MODE);
			/* set input enable */
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				    PADS_INPUTEN_MASK, PADS_INPUTEN_OFFSET,
				    ENABLE);

			temp = (ENABLE << GPIO_INPUTEN_OFFSET) | PADS_MODE_IN;
			pads_writel(GPIO_IOCTRL(sysmode, i), GPIO_INOUT_MASK,
				    GPIO_INOUT_OFFSET, temp);
			break;
		case PADS_MODE_OUT:
			/* set func1 mode*/
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				    PADS_MUXMODE_MASK, PADS_MUXMODE_OFFSET,
				    GPIO_MODE);
			/* set input disable */
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				    PADS_INPUTEN_MASK, PADS_INPUTEN_OFFSET,
				    DISABLE);

			temp = (DISABLE << GPIO_INPUTEN_OFFSET) |
			       ((value & 0x1) << GPIO_OUPUTVAL_OFFSET) |
			       PADS_MODE_OUT;
			/* set output enable */
			pads_writel(GPIO_IOCTRL(sysmode, i), GPIO_INOUT_MASK,
				    GPIO_INOUT_OFFSET, temp);
			break;
		default:
			printf("unknown pads mode %d\n", mode);
			return -1;
		}
	}
	return 0;
}

/*pattern must every bit represent output mode high/low level*/
int itcs_pads_set_pull(domain_t sysmode, int range, int en, uint32_t pattern)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	int i = 0;

	if (is_rtc(sysmode))
		return rtc_set_pull(range, en, pattern);

	if (!end)
		end = start;

	/* invalid range */
	if (end < start) {
		printf("Range Err\n");
		return -1;
	}

	for (i = start; i <= end; i++) {
		if (!en)
		{
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				PADS_PULLEN_MASK, PADS_PULLEN_OFFSET,
				DISABLE);
			continue;
		}

		switch (pattern) {
		case PADS_PULL_UP:
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				PADS_PULLEN_MASK, PADS_PULLEN_OFFSET,
				ENABLE);
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				PADS_PULLSELECTOR_MASK, PADS_PULLSELECTOR_OFFSET,
				PADS_SELECTOR_PULLUP);
			break;

		case PADS_PULL_DOWN:
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				PADS_PULLEN_MASK, PADS_PULLEN_OFFSET,
				ENABLE);
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				PADS_PULLSELECTOR_MASK, PADS_PULLSELECTOR_OFFSET,
				PADS_SELECTOR_PULLDOWN);
			break;

		case PADS_PULL_NO:
			pads_writel(PADS_CONFIG_IO(sysmode, i),
				PADS_PULLEN_MASK, PADS_PULLEN_OFFSET,
				DISABLE);
			break;

		default:
			printf("Set Pull Pattern Err: %d\n", pattern);
			return -1;
		}
	}
	return 0;
}

/* get pads pull status, return value:
 * PADS_PULL_UP, PADS_PULL_DOWN, PADS_PULL_NO
 */
int itcs_pads_get_pull(domain_t sysmode, int index)
{
	int value;

	if (is_rtc(sysmode))
		return rtc_get_pull(index);

	value = pads_readl(PADS_CONFIG_IO(sysmode, index), PADS_PULLEN_MASK,
		       PADS_PULLEN_OFFSET);
	if (!value)
		return PADS_PULL_NO;

	value = pads_readl(PADS_CONFIG_IO(sysmode, index),
			    PADS_PULLSELECTOR_MASK, PADS_PULLSELECTOR_OFFSET);
	if (value == PADS_SELECTOR_PULLDOWN)
		return PADS_PULL_DOWN;
	else
		return PADS_PULL_UP;
}

/*high must every bit represent output mode high/low level*/
int itcs_pads_set_value(domain_t sysmode, int range, uint32_t high)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	int i = 0;

	if (is_rtc(sysmode))
		return rtc_set_value(range, high);

	if (!end)
		end = start;

	/* invalid range */
	if (end < start)
		return -1;

	for (i = start; i <= end; i++) {
		if (itcs_pads_get_mode(sysmode, i) != PADS_MODE_OUT)
			continue;

		pads_writel(GPIO_IOCTRL(sysmode, i), GPIO_OUPUTVAL_MASK,
			    GPIO_OUPUTVAL_OFFSET, high);
	}
	return 0;
}

/*thie can get input&output gpio status*/
int itcs_pads_get_value(domain_t sysmode, int index, int *mode)
{
	int value = -1;

	if (is_rtc(sysmode))
		return rtc_get_value(index, mode);

	*mode = itcs_pads_get_mode(sysmode, index);
	switch (*mode) {
	case PADS_MODE_FUNC:
		break;
	case PADS_MODE_IN:
	case PADS_MODE_OUT:
		value = pads_readl(GPIO_IOSTS(sysmode, index),
				   GPIO_INPUTVAL_MASK, GPIO_INPUTVAL_OFFSET);
		break;
	default:
		printf("Mode Err: %d\n", mode);
		return -1;
	}

	return value;
}

int itcs_pads_set_drselector(domain_t sysmode, int range, uint32_t ds)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	int i = 0;

	if (is_rtc(sysmode))
		return 0;

	if (!end)
		end = start;

	/* invalid range */
	if (end < start)
		return -1;

	for (i = start; i <= end; i++) {
		pads_writel(PADS_CONFIG_IO(sysmode, i), PADS_DRSELECTOR_MASK,
			    PADS_DRSELECTOR_OFFSET, ds);
	}
	return 0;
}

int itcs_pads_get_drselector(domain_t sysmode, int index)
{
	int value;

	if (is_rtc(sysmode))
		return 0;

	value =	pads_readl(PADS_CONFIG_IO(sysmode, index), PADS_DRSELECTOR_MASK,
			    PADS_DRSELECTOR_OFFSET);

	return value;
}

int itcs_module_set_pads(domain_t sysmode, int bitmode, const char *name)
{
	struct pads_modules_bundle *list = NULL;
	int i;

	if (bitmode < FPGA_BIT_V_RGMII || bitmode > FPGA_BIT_V_MAX)
		return -1;

	if (sysmode < CPU && sysmode > RTC)
		return -1;

	list = bundle_list[bitmode];
	for (i = 0; list[i].name != NULL; i++) {
		if (!strncmp(list[i].name, name, 32) &&
		    list[i].sysmode == sysmode) {
			itcs_pads_set_mode(sysmode, list[i].id, PADS_MODE_FUNC,
					   list[i].fm);
			//itcs_pads_set_pull(sysmode, list[i].id, 1, list[i].pt);
		}
	}

	return 0;
}

int itcs_module_set_pads_by_index(const char *name, uint32_t index)
{
	int i;
	int found = 0;

	struct pads_modules_bundle *list = fpga_iolist;
	for (i = 0; list[i].name != NULL; i++)
	{
		if (!strncmp(list[i].name, name, 32) &&
		    list[i].index == index)
		{
			found = 1;
			itcs_pads_set_mode(list[i].sysmode, list[i].id, PADS_MODE_FUNC,
					   list[i].fm);
			//itcs_pads_set_pull(list[i].sysmode, list[i].id, 1, list[i].pt);
			itcs_pads_set_drselector(list[i].sysmode, list[i].id, list[i].drselector);
		}
	}

	if (!found)
	{
		printf("itcs_modules_set_pads_by_index not find, name = %s, index = %d\n",
			name, index);
		return -1;
	}



	return 0;
}

static gpio_bank_t *cpu_gpio_banks = NULL;
static gpio_bank_t *sap_gpio_banks = NULL;

static gpio_bank_t *get_bank(domain_t sysmode, int index)
{
	gpio_bank_t *bank = (sysmode == CPU) ? cpu_gpio_banks : sap_gpio_banks;

	if (is_rtc(sysmode))
		return NULL;

	return &(bank[index / BANK_NUM]);
}

static gpio_single_t *get_gpio(gpio_bank_t *bank, int index)
{
	return (bank ? &(bank->gpios[index % BANK_NUM]) : NULL);
}

void gpio_irq_mask(domain_t sysmode, int index)
{
	if (is_rtc(sysmode))
		return;

	gpio_irq_disable(sysmode, index);
	pads_writel(GPIO_IOCTRL(sysmode, index), GPIO_INTMASK_MASK,
		    GPIO_INTMASK_OFFSET, 1);
}

void gpio_irq_unmask(domain_t sysmode, int index)
{
	if (is_rtc(sysmode))
		return;

	pads_writel(GPIO_IOCTRL(sysmode, index), GPIO_INTMASK_MASK,
		    GPIO_INTMASK_OFFSET, 0);
	gpio_irq_enable(sysmode, index);
}

static void gpio_irq_eoi(domain_t sysmode, int index)
{
	if (is_rtc(sysmode))
		return rtc_irq_eoi(index);

	pads_writel(GPIO_IOSTS(sysmode, index), GPIO_RAWINTS_MASK,
		    GPIO_RAWINTS_OFFSET, 1);
}

void gpio_irq_enable(domain_t sysmode, int index)
{
	if (is_rtc(sysmode))
		return rtc_irq_enable(index);

	pads_writel(GPIO_IOCTRL(sysmode, index), GPIO_INTEN_MASK,
		    GPIO_INTEN_OFFSET, 1);
}

void gpio_irq_disable(domain_t sysmode, int index)
{
	if (is_rtc(sysmode))
		return rtc_irq_disable(index);

	pads_writel(GPIO_IOCTRL(sysmode, index), GPIO_INTEN_MASK,
		    GPIO_INTEN_OFFSET, 0);
}

static int gpio_set_type(domain_t sysmode, int index, int type)
{
	int mode;

	if (is_rtc(sysmode))
		return rtc_set_type(index, type);

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		mode = GPIO_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		mode = GPIO_EDGE_FALLING;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		mode = GPIO_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		mode = GPIO_LEVEL_LOW;
		break;
	default:
		printf("Do not suuport this IRQ Flags: %d\n", type);
		return -1;
	}
	pads_writel(GPIO_IOCTRL(sysmode, index), GPIO_INTMODE_MASK,
		    GPIO_INTMODE_OFFSET, mode);
	return 0;
}

static int gpio_general_handle_irq(int irq, void *args)
{
	gpio_bank_t *bank = (gpio_bank_t *)args;
	gpio_single_t *gpios = bank->gpios;
	uint32_t status;

	status = pads_readl(GPIO_MSKINTS(bank->sysmode, BANK_NUM * bank->id),
			    GPIO_MSK_MASK, GPIO_MSK_OFFSET);

	for (int i = 0; i < BANK_NUM; i++) {
		if (status & (1 << i)) {
			if (gpios[i].inited && gpios[i].handler)
				gpios[i].handler(irq, gpios[i].private_data);

			gpio_irq_eoi(bank->sysmode, bank->id * BANK_NUM + i);
		}
	}
	return 0;
}

int gpio_to_irq(domain_t sysmode, int index)
{
	gpio_bank_t *bank = get_bank(sysmode, index);

	if (is_rtc(sysmode))
		return rtc_to_irq(index);

	return bank->irq;
}

int gpio_request_irq(domain_t sysmode, int index, irq_handler_t handler,
		     int flags, const char *name, void *dev)
{
	gpio_bank_t *bank = get_bank(sysmode, index);
	gpio_single_t *gpios = get_gpio(bank, index);

	if (is_rtc(sysmode))
		return rtc_request_irq(index, handler, flags, name, dev);

	if (gpios->inited) {
		printf("GPIO%d request IRQ failed, name(%s) already exists\n",
		       index, name);
		return -1;
	}

	if (gpio_set_type(sysmode, index, flags) < 0)
		return -1;

	gpios->handler = handler;
	gpios->name = name;
	gpios->private_data = dev;
	gpios->inited = true;
	gpio_irq_unmask(sysmode, index);

	if (!bank->requested) {
		printf("bank->name %s, bank->irq %d\n", bank->name, bank->irq);
		request_irq(bank->irq, gpio_general_handle_irq, bank->name,
			    bank);
		bank->requested = true;
	}

	return 0;
}

int gpio_replace_irq(domain_t sysmode, int index, irq_handler_t handler,
		     int flags, const char *name, void *dev)
{
	gpio_bank_t *bank = get_bank(sysmode, index);
	gpio_single_t *gpios = get_gpio(bank, index);

	if (is_rtc(sysmode))
		return rtc_replace_irq(index, handler, flags, name, dev);

	gpio_irq_mask(sysmode, index);
	if (gpio_set_type(sysmode, index, flags) < 0) {
		gpio_irq_unmask(sysmode, index);
		return -1;
	}

	gpios->handler = handler;
	gpios->name = name;
	gpios->private_data = dev;
	gpios->inited = true;

	gpio_irq_unmask(sysmode, index);
	return 0;
}

static gpio_bank_t *gpio_init_bank(domain_t sysmode, int irq, int ngpio)
{
	gpio_bank_t *bank;
	int num = div_up(ngpio, BANK_NUM);

	bank = malloc(sizeof(gpio_bank_t) * num);
	if (!bank) {
		printf("GPIO IRQ Malloc Err\n");
		return NULL;
	}

	for (int i = 0; i < num; i++) {
		bank[i].irq = irq + i;
		bank[i].id = i;
		sprintf(bank[i].name, "%s bank%d",
			((sysmode == CPU) ? "CPU" : "SAP"), bank[i].id);

		bank[i].requested = false;
		bank[i].sysmode = sysmode;

#ifndef CONFIG_COMPILE_RTL
		memset(bank[i].gpios, 0, sizeof(gpio_single_t) * BANK_NUM);
#endif
	}

	return bank;
}

typedef struct suspend_pad {
	domain_t mode;
	uint32_t iom;
	uint32_t debc;
	uint8_t ioctl;
} suspend_pad_t;

#ifndef CONFIG_COMPILE_RTL
static suspend_pad_t savePad[CPU_GPIO_MAX + SAP_GPIO_MAX + 2];
#endif
int gpio_pm_suspend(void *privdata)
{
#ifndef CONFIG_COMPILE_RTL
	int max = CPU_GPIO_MAX + SAP_GPIO_MAX + 2;
	int id;
	printf("%s\n", __func__);
	for (int i = 0; i < max; i++) {
		id = i;
		if (i > CPU_GPIO_MAX) {
			savePad[i].mode = SAP;
			id = i - CPU_GPIO_MAX - 1;
		} else
			savePad[i].mode = CPU;

		// printf("%d: PADS_CONFIG_IO %lx, GPIO_IOCTRL %lx, GPIO_DEBC %lx\n", id,
		// PADS_CONFIG_IO(savePad[i].mode, id), GPIO_IOCTRL(savePad[i].mode, id),
		// GPIO_DEBC(savePad[i].mode));
		savePad[i].iom = readl(PADS_CONFIG_IO(savePad[i].mode, id));
		savePad[i].ioctl = readb(GPIO_IOCTRL(savePad[i].mode, id));
		if (!id)
			savePad[i].debc = readl(GPIO_DEBC(savePad[i].mode));
	}
#endif
	return 0;
}

int gpio_pm_resume(void *privdata)
{
#ifndef CONFIG_COMPILE_RTL
	int max = CPU_GPIO_MAX + SAP_GPIO_MAX + 2;
	int id;

	printf("%s\n", __func__);
	for (int i = 0; i < max; i++) {
		id = i;
		if (i > CPU_GPIO_MAX)
			id = i - CPU_GPIO_MAX - 1;

		// printf("%d: PADS_CONFIG_IO %lx, GPIO_IOCTRL %lx, GPIO_DEBC %lx\n", id,
		// PADS_CONFIG_IO(savePad[i].mode, id), GPIO_IOCTRL(savePad[i].mode, id),
		// GPIO_DEBC(savePad[i].mode));
		writel(savePad[i].iom, PADS_CONFIG_IO(savePad[i].mode, id));
		if (!id)
			writeb(savePad[i].debc, GPIO_DEBC(savePad[i].mode));
		writel(savePad[i].ioctl, GPIO_IOCTRL(savePad[i].mode, id));
	}
#endif
	return 0;
}

SIMPLE_PM_OPS(gpio, gpio_pm_suspend, gpio_pm_resume, NULL);

void gpio_irq_init(void)
{
	cpu_gpio_banks = gpio_init_bank(CPU, C_GPIO0_IRQn, CPU_GPIO_MAX);
	if (!cpu_gpio_banks) {
		printf("CPU GPIO Err\n");
		return;
	}

	sap_gpio_banks = gpio_init_bank(SAP, S_GPIO0_IRQn, SAP_GPIO_MAX);
	if (!sap_gpio_banks) {
		printf("SAP GPIO Err\n");
		return;
	}

	itcs_register_pm(&pm_gpio);
}

void gpio_irq_exit(void)
{
	if (cpu_gpio_banks)
		free(cpu_gpio_banks);

	if (sap_gpio_banks)
		free(sap_gpio_banks);
}

static void gpio_init(void)
{
	itcs_module_enable(CPU, "gpio");
	itcs_module_enable(SAP, "gpio");

	gpio_irq_init();
}

module_init(gpio_init);
