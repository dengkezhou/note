#include <common.h>
#include <asm/io.h>

struct module_power modules[] = {
	{ "wdt", 0xc2f00000, CPU, RESET_ALL },
	{ "gpio", 0xc2f00400, CPU, RESET_ALL },
	{ "ttc0", 0xc2f00800, CPU, RESET_CHAN(0) },
	{ "ttc1", 0xc2f00800, CPU, RESET_CHAN(1) },
	{ "spi1", 0xc2f00c00, CPU, RESET_CHAN(0) | RESET_CHAN(1) },
	{ "spi2", 0xc2f00c00, CPU, RESET_CHAN(2) | RESET_CHAN(3) },
	{ "spi3", 0xc2f00c00, CPU, RESET_CHAN(4) | RESET_CHAN(5) },
	{ "iic2", 0xc2f01000, CPU, RESET_CHAN(0) },
	{ "iic3", 0xc2f01000, CPU, RESET_CHAN(1) },
	{ "iic4", 0xc2f01000, CPU, RESET_CHAN(2) },
	{ "iic5", 0xc2f01000, CPU, RESET_CHAN(3) },
	{ "iic6", 0xc2f01000, CPU, RESET_CHAN(4) },
	{ "iic7", 0xc2f01000, CPU, RESET_CHAN(5) },	
	{ "uart2", 0xc2f01400, CPU, RESET_CHAN(0) | RESET_CHAN(1) },
	{ "uart3", 0xc2f01400, CPU, RESET_CHAN(2) | RESET_CHAN(3) },
	{ "uart4", 0xc2f01400, CPU, RESET_CHAN(4) | RESET_CHAN(5) },
	{ "uart5", 0xc2f01400, CPU, RESET_CHAN(6) | RESET_CHAN(7) },
	{ "uart6", 0xc2f01400, CPU, RESET_CHAN(8) | RESET_CHAN(9) },
	{ "uart7", 0xc2f01400, CPU, RESET_CHAN(10) | RESET_CHAN(11) },
	{ "uart8", 0xc2f01400, CPU, RESET_CHAN(12) | RESET_CHAN(13) },
	{ "uart9", 0xc2f01400, CPU, RESET_CHAN(14) | RESET_CHAN(15) },
	{ "uart10", 0xc2f01400, CPU, RESET_CHAN(16) | RESET_CHAN(17) },
	{ "uart11", 0xc2f01400, CPU, RESET_CHAN(18) | RESET_CHAN(19) },
	{ "mu", 0xc2f01800, CPU, RESET_ALL },
	{ "iis0", 0xc2f01c00, CPU, RESET_CHAN(0) | RESET_CHAN(2) },
	{ "iis1", 0xc2f01c00, CPU, RESET_CHAN(1) | RESET_CHAN(3) },
	{ "pwm0", 0xc2f02000, CPU, RESET_CHAN(0) },
	{ "pwm1", 0xc2f02000, CPU, RESET_CHAN(1) },
	{ "pwm2", 0xc2f02000, CPU, RESET_CHAN(2) },
	{ "pwm3", 0xc2f02000, CPU, RESET_CHAN(3) },
	{ "pwm4", 0xc2f02000, CPU, RESET_CHAN(4) },
	{ "pwm5", 0xc2f02000, CPU, RESET_CHAN(5) },
	{ "pwm6", 0xc2f02000, CPU, RESET_CHAN(6) },
	{ "pwm7", 0xc2f02000, CPU, RESET_CHAN(7) },
	{ "pvt", 0xc2f02400, CPU, RESET_ALL },
	{ "ddr", 0xc30f0000, CPU, RESET_ALL },
	{ "ddr1", 0xc31f0000, CPU, RESET_ALL },
	{ "usb0", 0xc4f00000, CPU, RESET_ALL },
	{ "usb1", 0xc4f00400, CPU, RESET_ALL },
	{ "usb2", 0xc4f00800, CPU, RESET_ALL },
	{ "usb3", 0xc4f00c00, CPU, RESET_ALL },
	{ "gmac0", 0xc4f01000, CPU, RESET_ALL },
	{ "gmac1", 0xc4f01400, CPU, RESET_ALL },
	{ "gmac2", 0xc4f01800, CPU, RESET_ALL },
	{ "emmc0", 0xc5f00000, CPU, RESET_ALL },
	{ "ospi", 0xc5f00000, CPU, RESET_ALL },
	{ "sd1", 0xc5f00400, CPU, RESET_ALL },
	{ "sd2", 0xc5f00800, CPU, RESET_ALL },
	{ "qspi", 0xc5f00c00, CPU, RESET_ALL },
	{ "cae", 0xc5f01000, CPU, RESET_ALL },
	{ "dma0", 0xc5f01400, CPU, RESET_ALL },
	{ "dma1", 0xc5f01800, CPU, RESET_ALL },
	{ "vdec", 0xc6f00000, CPU, RESET_ALL },
	{ "pp", 0xc6f00400, CPU, RESET_ALL },
	{ "npu", 0xc7f00000, CPU, RESET_ALL },
	{ "venc0", 0xc9f00000, CPU, RESET_ALL },
	{ "venc1", 0xc9f00400, CPU, RESET_ALL },
	{ "ids", 0xc9f00800, CPU, RESET_ALL },
	{ "pufcc", 0xd0f00000, SAP, RESET_ALL },
	{ "gmac3", 0xd0f00400, SAP, RESET_ALL },
	{ "wdt", 0xd2f00000, SAP, RESET_ALL },
	{ "gpio", 0xd2f00400, SAP, RESET_ALL },
	{ "ttc", 0xd2f00800, SAP, RESET_ALL },
	{ "spi0", 0xd2f00c00, SAP, RESET_ALL },
	{ "iic0", 0xd2f01000, SAP, RESET_CHAN(0) },
	{ "iic1", 0xd2f01000, SAP, RESET_CHAN(1) },
	{ "uart0", 0xd2f01400, SAP, RESET_CHAN(0) | RESET_CHAN(1) },
	{ "uart1", 0xd2f01400, SAP, RESET_CHAN(2) | RESET_CHAN(3) },
	{ "mu", 0xd2f01800, SAP, RESET_ALL },
	{ "pwm0", 0xd2f02000, SAP, RESET_ALL },
	{ "rtc", 0xd2e00200, RTC, RESET_CHAN(0) },
	{ "pwm0", 0xd2e00200, RTC, RESET_CHAN(1) },
	{ "mi2s0", 0xc2f02800, CPU, RESET_ALL },
	{ "dmic0", 0xc2f02c00, CPU, RESET_CHAN(0) | RESET_CHAN(1) },
	{ "dmic1", 0xc2f02c00, CPU, RESET_CHAN(2) | RESET_CHAN(3) },
	{ "dmic2", 0xc2f02c00, CPU, RESET_CHAN(4) | RESET_CHAN(5) },
	{ "dmic3", 0xc2f02c00, CPU, RESET_CHAN(6) | RESET_CHAN(7) }
};

module_power_t *get_module(const char *module, domain_t mode)
{
	int len = ARRAY_SIZE(modules);

	for (int i = 0; i < len; i++)
		if (!strncmp(modules[i].name, module, strlen(module)) &&
		    (modules[i].mode == mode))
			return &modules[i];

	return NULL;
}

int itcs_module_reset(domain_t mode, const char *module)
{
	module_power_t *dev = NULL;
	uint32_t tmp;

	dev = get_module(module, mode);
	if (!dev) {
		printf("Domain(%d) module %s can not find in list\n", mode,
		       module);
		return -1;
	}

	tmp = pwr_readl(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET);
	pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET,
		   (tmp | dev->id));
	udelay(10);
	pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET,
		   (tmp & (~dev->id)));
	return 0;
}

int itcs_module_enable(domain_t mode, const char *module)
{
	module_power_t *dev = NULL;
	uint32_t tmp;

	dev = get_module(module, mode);
	if (!dev) {
		printf("Domain(%d) module %s can not find in list\n", mode,
		       module);
		return -1;
	}

	if (mode == RTC) {
		if (!strcmp(module, "pwm0") || !strcmp(module, "rtc")) {
			tmp = pwr_readl(R(dev, PWR_RSTC), PWR_RSTC_MASK,
					PWR_RSTC_OFFSET);
			pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK,
				   PWR_RSTC_OFFSET, (tmp | dev->id));
			pwr_writel(R(dev, PWR_CLKEN), PWR_CLKEN_MASK,
				   PWR_CLKEN_OFFSET, RESET_ALL);
			pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK,
				   PWR_RSTC_OFFSET, (tmp & (~dev->id)));
		}
		return 0;
	}
	tmp = pwr_readl(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET);
	/* asset reset */
	pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET,
		   (tmp | dev->id));
	/* power up */
	pwr_writel(R(dev, PWR_PWRC), PWR_REQ_MASK, PWR_REQ_OFFSET, 1);
	while (!pwr_readl(R(dev, PWR_PWRC), PWR_ACK_MASK, PWR_ACK_OFFSET))
		;
	pwr_writel(R(dev, PWR_PWRC), PWR_ISO_MASK, PWR_ISO_OFFSET, 1);
	/* clkgate en */
	pwr_writel(R(dev, PWR_CLKEN), PWR_CLKEN_MASK, PWR_CLKEN_OFFSET,
		   RESET_ALL);
	/* bus en */
	pwr_writel(R(dev, PWR_BUSC), PWR_BUSEN_MASK, PWR_BUSEN_OFFSET, 0x3);
	/* input en */
	pwr_writel(R(dev, PWR_IOC), PWR_IOC_MASK, PWR_IOC_OFFSET, 1);

	if (pwr_readl(R(dev, PWR_BUSC), PWR_BUSEN_MASK, PWR_BUSEN_OFFSET) !=
	    0x3)
		printf("Apb Read/Write Err\n");

	/* release reset */
	pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET,
		   (tmp & (~dev->id)));
	return 0;
}

int itcs_module_disable(domain_t mode, const char *module)
{
	module_power_t *dev = NULL;
	uint32_t tmp;

	dev = get_module(module, mode);
	if (!dev) {
		printf("Domain(%d) module %s can not find in list\n", mode,
		       module);
		return -1;
	}

	if (mode == RTC) {
		if (!strcmp(module, "pwm0") || !strcmp(module, "rtc")) {
			tmp = pwr_readl(R(dev, PWR_RSTC), PWR_RSTC_MASK,
					PWR_RSTC_OFFSET);
			pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK,
				   PWR_RSTC_OFFSET, (tmp | dev->id));
			pwr_writel(R(dev, PWR_CLKEN), PWR_CLKEN_MASK,
				   PWR_CLKEN_OFFSET, 0);
		}
		return 0;
	}
	tmp = pwr_readl(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET);
	tmp |= dev->id;
	/* asset reset */
	pwr_writel(R(dev, PWR_RSTC), PWR_RSTC_MASK, PWR_RSTC_OFFSET, tmp);
	if (tmp == RESET_ALL) {
		/* input disable */
		pwr_writel(R(dev, PWR_IOC), PWR_IOC_MASK, PWR_IOC_OFFSET, 0);
		/* bus disable */
		pwr_writel(R(dev, PWR_BUSC), PWR_BUSEN_MASK, PWR_BUSEN_OFFSET,
			   0x0);
		/* clkgate disable */
		pwr_writel(R(dev, PWR_CLKEN), PWR_CLKEN_MASK, PWR_CLKEN_OFFSET,
			   0x0);
		/* power down */
		pwr_writel(R(dev, PWR_PWRC), PWR_ALL_MASK, PWR_ALL_OFFSET, 0);
	}
	return 0;
}
