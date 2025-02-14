#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <dma-ops.h>
#include <asm/io.h>
#include <getopt.h>
#include <cache.h>
#include <pads.h>
#ifdef CONFIG_MMU
#include <mmu_table.h>
#include <sysm.h>
#endif

#define CHANNEL_NUMS 2
#ifdef CONFIG_C920
#define SPEED_CHANNEL_NUMS 8
#define DMA_SPEED_BUFLEN (8192 * 2)
#endif

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
#define DMA_BUFLEN (8192 * 2)
#define DEVTODEV_DMA_BUFLEN (64 * 2)
#elif defined(CONFIG_COMPILE_RTL)
#define DMA_BUFLEN (16 * 2)
#define DEVTODEV_DMA_BUFLEN (16 * 2)
#endif

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
/* uart fifo depth is 64. */
#define UART_TRIG_LEVEL \
	(DMA_SLAVE_BURST_TRANS_LEN_32 * DMA_SLAVE_BUSWIDTH_1_BYTE)
#elif defined(CONFIG_COMPILE_RTL)
#define UART_TRIG_LEVEL \
	(DMA_SLAVE_BURST_TRANS_LEN_4 * DMA_SLAVE_BUSWIDTH_1_BYTE)
#endif

struct cb_param {
	void *prep_info;
	volatile unsigned int finished;
};

#define UART_CTRL (0x00000000UL)
#define UART_MODE (0x00000004UL)
#define UART_CISR (0x00000014UL)
#define UART_BRGR (0x00000018UL)
#define UART_RTOR (0x0000001CUL)
#define UART_RTR (0x00000020UL)
#define UART_MCR (0x00000024UL)
#define UART_CSR (0x0000002CUL)
#define UART_FIFO (0x00000030UL)
#define UART_TTR (0x00000044UL)
#define UART_IER (0x00000008UL)
#define UART_IDR (0x0000000CUL)
#define UART_IMR (0x00000010UL)

#define IxR_TIMEOUT_MASK ((uint16_t)0x0100) /* bit[8]: rx timeout error     */

#define CTRL_RXEN_MASK ((uint16_t)0x0004)
#define CTRL_RXDIS_MASK ((uint16_t)0x0008)
#define CTRL_TXEN_MASK ((uint16_t)0x0010)
#define CTRL_TXDIS_MASK ((uint16_t)0x0020)

#define MODE_CHRL_MASK ((uint16_t)0x0006)
#define MODE_PAR_MASK ((uint16_t)0x0038)
#define MODE_NBSTOP_MASK ((uint16_t)0x00C0)
#define MODE_CHMODE_MASK ((uint16_t)0x0300)
#define MODE_IRMODE_MASK ((uint16_t)0x0800)
#define MODE_WSIZE_MASK ((uint16_t)0x3000)
#define MCR_FCM_MASK ((uint16_t)0x0020)

#define UART_WordLength_8b ((uint16_t)0x0000)
#define UART_StopBits_1 ((uint16_t)0x0000)
#define UART_Parity_No ((uint16_t)0x0020)
#define UART_Mode_UART ((uint16_t)0x0000)
#define UART_WSIZE_1 ((uint16_t)0x1000)
#define UART_ChannelMode_Normal ((uint16_t)0x0000)
#define UART_ChannelMode_LocalLoop ((uint16_t)0x0200)
#define UART_HardwareFlowControl_None ((uint16_t)0x0000)

#define UART_SR_INTR_REMPTY 0x02
#define UART_SR_INTR_TFUL 0x10

typedef struct tty_dev {
	int id;
	unsigned long regbase;
} tty_dev_t;

static tty_dev_t ttydev_0;
static tty_dev_t ttydev_1;

#ifdef CONFIG_C920
volatile int dma_speed_test = 0;
unsigned long dma_start_time[SPEED_CHANNEL_NUMS] = { 0 };
unsigned long dma_stop_time[SPEED_CHANNEL_NUMS] = { 0 };
volatile int speed_start_index = 0;
volatile int speed_stop_index = 0;
#endif

static void uart_enable(tty_dev_t *dev)
{
	unsigned int reg;
	reg = readl(dev->regbase + UART_CTRL);
	/* rx */
	reg |= CTRL_RXEN_MASK;
	reg &= ~CTRL_RXDIS_MASK;
	/* tx */
	reg |= CTRL_TXEN_MASK;
	reg &= ~CTRL_TXDIS_MASK;
	writel(reg, dev->regbase + UART_CTRL);
	reg = readl(dev->regbase + UART_CTRL);
}

static void uart_disable(tty_dev_t *dev)
{
	unsigned int reg;
	reg = readl(dev->regbase + UART_CTRL);
	/* rx */
	reg &= ~CTRL_RXEN_MASK;
	reg |= CTRL_RXDIS_MASK;
	/* tx */
	reg &= ~CTRL_TXEN_MASK;
	reg |= CTRL_TXDIS_MASK;
	writel(reg, dev->regbase + UART_CTRL);
	reg = readl(dev->regbase + UART_CTRL);
}

static void uart_reset(tty_dev_t *dev)
{
	/* sw reset */
	writel(0x3, dev->regbase + UART_CTRL);
	while ((readl(dev->regbase + UART_CTRL) & 0x3))
		;
}

static void uart_mode_set(tty_dev_t *dev, unsigned int mode)
{
	unsigned int reg;
	reg = readl(dev->regbase + UART_MODE);
	reg &= ~MODE_CHRL_MASK;
	reg |= (unsigned int)UART_WordLength_8b;
	reg &= ~MODE_PAR_MASK;
	reg |= (unsigned int)UART_Parity_No;
	reg &= ~MODE_NBSTOP_MASK;
	reg |= (unsigned int)UART_StopBits_1;
	reg &= ~MODE_IRMODE_MASK;
	reg |= (unsigned int)UART_Mode_UART;
	reg &= ~MODE_CHMODE_MASK;
	reg |= mode;
	reg &= ~MODE_WSIZE_MASK;
	reg |= (unsigned int)UART_WSIZE_1;
	writel(reg, dev->regbase + UART_MODE);
}

static void uart_flow_ctr_set(tty_dev_t *dev)
{
	unsigned int reg;
	/* enable hardware flow control */
	reg = readl(dev->regbase + UART_MCR);
	reg &= ~MCR_FCM_MASK;
	reg |= (unsigned int)UART_HardwareFlowControl_None;
	writel(reg, dev->regbase + UART_MCR);
}

static void uart_set_baud(tty_dev_t *dev, int domain, int baudrate)
{
	int divisor;
	int clk = itcs_module_get_clock(domain, "uart");
	divisor = DIV_ROUND(clk, 16 * baudrate);
	writel(divisor & 0xffff, dev->regbase + UART_BRGR);
}

static void uart_set_timeout(tty_dev_t *dev)
{
	/*Uart rx timeout value*/
	writel(0xff, dev->regbase + UART_RTOR);
}

static void uart_set_trig_level(tty_dev_t *dev)
{
	writel(UART_TRIG_LEVEL, dev->regbase + UART_RTR);
	writel(UART_TRIG_LEVEL, dev->regbase + UART_TTR);
}

static int uart_read(tty_dev_t *dev, char *buf, int len)
{
	int least = len;

	while (least) {
		if (readl(dev->regbase + UART_CSR) & UART_SR_INTR_REMPTY) {
			continue;
		}

		*(buf++) = readl(dev->regbase + UART_FIFO) & 0xff;
		least--;
	}
	return len;
}

static int uart_write(tty_dev_t *dev, char *buf, int len)
{
	int least = len;

	while (least) {
		if (readl(dev->regbase + UART_CSR) & UART_SR_INTR_TFUL) {
			continue;
		}
		writel(buf[len - least], dev->regbase + UART_FIFO);
		least--;
	}
	return len;
}

static void uart_enable_timeout_dma_req(bool enable)
{
	unsigned long cpu_uart_timeout_en_addr = 0xc2f01400 + 0x28;
	unsigned long sap_uart_timeout_en_addr = 0xd2f01400 + 0x28;
	unsigned int tmp_val = 0;
	if (enable == 1) {
		tmp_val = readl(cpu_uart_timeout_en_addr);
		tmp_val |= 0x1 << 1;
		tmp_val |= 0x1 << 0;
		writel(tmp_val, cpu_uart_timeout_en_addr);

		tmp_val = readl(sap_uart_timeout_en_addr);
		tmp_val |= 0x1 << 1;
		tmp_val |= 0x1 << 0;
		writel(tmp_val, sap_uart_timeout_en_addr);
	} else {
		tmp_val = readl(cpu_uart_timeout_en_addr);
		tmp_val &= ~(0x1 << 1);
		tmp_val &= ~(0x1 << 0);
		writel(tmp_val, cpu_uart_timeout_en_addr);

		tmp_val = readl(sap_uart_timeout_en_addr);
		tmp_val &= ~(0x1 << 1);
		tmp_val &= ~(0x1 << 0);
		writel(tmp_val, sap_uart_timeout_en_addr);
	}
}

static void uart_module_set(tty_dev_t *dev, int domain, unsigned long reg_base,
			    int id)
{
	char name[16] = { 0 };

	dev->regbase = reg_base;
	dev->id = id;
	sprintf(name, "uart%d", dev->id);
	itcs_module_enable(domain, name);
	//itcs_module_set_pads(domain, FPGA_BIT_V_EMMC, name);
	if(dev->id == 1)
		itcs_module_set_pads_by_index(name, 0);
	else
		itcs_module_set_pads_by_index(name, 2);
	//itcs_module_set_clock(domain, "uart", NULL, 24000000, false);

	uart_enable_timeout_dma_req(0);
}

static void uart_start(tty_dev_t *dev)
{
	uart_enable(dev);
}

static tty_dev_t *uart_init(tty_dev_t *dev, int domain, unsigned long reg_base,
			    int id, unsigned int mode)
{
	uart_module_set(dev, domain, reg_base, id);

	uart_disable(dev);
	uart_reset(dev);
	uart_mode_set(dev, mode);
	uart_flow_ctr_set(dev);
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	uart_set_baud(dev, domain, 115200);
#elif defined(CONFIG_COMPILE_RTL)
	uart_set_baud(dev, domain, 921600);
#endif
	uart_set_timeout(dev);
	uart_set_trig_level(dev);
	return dev;
}

static void dmatest_memcpy_callback(void *param)
{
	struct cb_param *cbp = (struct cb_param *)param;
	cbp->finished = 1;
#ifdef CONFIG_C920
	if (dma_speed_test) {
		dma_stop_time[speed_stop_index] = get_timer_us(0);
		speed_stop_index++;
	}
#endif
}

struct dma_chan *dma_prepare(struct cb_param *cbp,
			     struct dma_prep_info *prep_info,
			     struct dma_info *info, int len)
{
	struct dma_chan *chan = NULL;
	unsigned char *mem = NULL;
	dma_cookie_t cookie;

	chan = itcs_dma_request_channel(info);
	if (!chan)
		return NULL;

//#if defined(CONFIG_CACHE_LITE)
//	mem = (unsigned char *)DMA_UNCACHEABLE_MEM;
//#else
	mem = malloc(len);
//#endif
	if (!mem)
		return NULL;

	memset(mem, 0xac, len / 2);
	memset(mem + len / 2, 0xdb, len / 2);

	prep_info->direction = DMA_MEM_TO_MEM;
	prep_info->mode = DMA_SLAVE;
	prep_info->src = virt_to_phys(mem);
	prep_info->dst = virt_to_phys(mem + len / 2);
	prep_info->len = len / 2;
	prep_info->callback = dmatest_memcpy_callback;
	prep_info->callback_param = cbp;

	cbp->prep_info = prep_info;

	cookie = itcs_dma_prepare(chan, prep_info);
	if (cookie < 0)
		return NULL;

	return chan;
}

static void dma_start(struct dma_chan *chan)
{
	itcs_dma_start(chan);
}

static void dma_finish(struct dma_chan *chan, struct dma_prep_info *prep_info)
{
	free(phys_to_virt(prep_info->src));
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
}

static int dmatest_memcpy(void)
{
	struct dma_chan *chan = NULL;
	struct dma_prep_info prep_info;
	struct dma_info info = {
		.devname = "dma0",
	};
	unsigned char *mem = NULL;
	dma_cookie_t cookie;
	int ret = 0;

	printf("test len: %d\n", DMA_BUFLEN / 2);

	chan = itcs_dma_request_channel(&info);
	if (!chan)
		return -1;

//#if defined(CONFIG_CACHE_LITE)
//	mem = (unsigned char *)DMA_UNCACHEABLE_MEM;
//#else
	mem = malloc(DMA_BUFLEN);
//#endif
	if (!mem)
		return -1;

	memset(mem, 0xac, DMA_BUFLEN / 2);
	memset(mem + DMA_BUFLEN / 2, 0xdb, DMA_BUFLEN / 2);

	prep_info.direction = DMA_MEM_TO_MEM;
	prep_info.mode = DMA_SLAVE;
	prep_info.src = virt_to_phys(mem);
	prep_info.dst = virt_to_phys(mem + DMA_BUFLEN / 2);
	prep_info.len = DMA_BUFLEN / 2;
	prep_info.callback = NULL;
	cookie = itcs_dma_prepare(chan, &prep_info);
	if (cookie < 0)
		return -1;

	itcs_dcache_flush();
	itcs_dma_start(chan);
	while (1) {
		ret = itcs_dma_transfer_completed(chan, cookie, NULL);
		if (ret != DMA_IN_PROGRESS)
			break;

		udelay(100);
	}

	itcs_dcache_invalid();
	if (ret == DMA_COMPLETE &&
	    !memcmp((char *)phys_to_virt(prep_info.src),
		    (char *)phys_to_virt(prep_info.dst), prep_info.len)) {
		printf("Test DMA MemToMem Pass\n");
		ret = 0;
	} else {
		printf("Test DMA MemToMem Failed\n");
		ret = -1;
	}

//#if !defined(CONFIG_CACHE_LITE)
	free(mem);
//#endif
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
	return ret;
}

static int dmatest_multimemcpy(void)
{
	struct cb_param cbp[2];
	struct dma_prep_info *prep_info = NULL;
	struct dma_prep_info prep_info_0;
	struct dma_prep_info prep_info_1;
	struct dma_chan *chan_0 = NULL;
	struct dma_chan *chan_1 = NULL;
	struct dma_info info = {
		.devname = "dma0",
	};
	int i = 0;
	int ret = 0;

	printf("test len: %d\n", DMA_BUFLEN / 2);

	for (i = 0; i < 2; i++)
		memset(&cbp[i], 0, sizeof(cbp[i]));

	chan_0 = dma_prepare(&cbp[0], &prep_info_0, &info, DMA_BUFLEN);
	chan_1 = dma_prepare(&cbp[1], &prep_info_1, &info, DMA_BUFLEN);
	itcs_dcache_flush();
	dma_start(chan_0);
	dma_start(chan_1);

	while (1) {
		for (i = 0; i < CHANNEL_NUMS; i++) {
			if (cbp[i].finished == 1) {
				if (i == CHANNEL_NUMS - 1)
					goto done;
				else
					continue;
			} else {
				break;
			}
		}
		udelay(10);
	}
done:
	for (i = 0; i < CHANNEL_NUMS; i++) {
		prep_info = (struct dma_prep_info *)cbp[i].prep_info;
		itcs_dcache_invalid();
		if (memcmp((char *)phys_to_virt(prep_info->src),
			   (char *)phys_to_virt(prep_info->dst),
			   prep_info->len)) {
			printf("Test DMA Multi-MemToMem Failed\n");
			ret = -1;
			goto err_exit;
		} else {
			continue;
		}
	}

	printf("Test DMA Multi-MemToMem Pass\n");
	ret = 0;
err_exit:
	dma_finish(chan_1, &prep_info_1);
	dma_finish(chan_0, &prep_info_0);
	return ret;
}

static int dmatest_memtodev(int dma_id)
{
	struct dma_chan *chan = NULL;
	struct dma_prep_info prep_info;
	struct dma_slave_config cfg;
	struct dma_info info = {
		.devname = "dma0",
		.dst_hw_handshake_num = DMAC0_CUART3_TX,
	};
	char *mem = NULL;
	dma_cookie_t cookie;
	tty_dev_t *dev = &ttydev_0;
	int ret;

	if (dma_id == 1) {
		info.devname = "dma1";
		info.dst_hw_handshake_num = DMAC1_CUART1_TX;
	}

	printf("test len: %d\n", DMA_BUFLEN / 2);

	chan = itcs_dma_request_channel(&info);
	if (!chan)
		return -1;

//#if defined(CONFIG_CACHE_LITE)
//	mem = (char *)DMA_UNCACHEABLE_MEM;
//#else
	mem = malloc(DMA_BUFLEN);
//#endif
	if (!mem)
		return -1;

	memset(mem, 0xa5, DMA_BUFLEN / 2);
	memset(mem + DMA_BUFLEN / 2, 0x0, DMA_BUFLEN / 2);

	if (dma_id == 1)
		uart_init(dev, SAP, ITCS_S_UART1_BASE, 1,
			  UART_ChannelMode_LocalLoop);
	else if (dma_id == 0)
		uart_init(dev, CPU, ITCS_C_UART3_BASE, 3,
			  UART_ChannelMode_LocalLoop);

	uart_start(dev);

	cfg.direction = DMA_MEM_TO_DEV;
	cfg.src_addr = virt_to_phys(mem);
	cfg.dst_addr = dev->regbase + UART_FIFO;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
#elif defined(CONFIG_COMPILE_RTL)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_4;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_4;
#endif
	cfg.device_fc = 0;
	ret = itcs_dma_slave_config(chan, &cfg);
	if (ret < 0)
		return -1;

	prep_info.direction = DMA_MEM_TO_DEV;
	prep_info.mode = DMA_SLAVE;
	prep_info.src = virt_to_phys(mem);
	prep_info.len = DMA_BUFLEN / 2;
	prep_info.callback = NULL;
	cookie = itcs_dma_prepare(chan, &prep_info);
	if (cookie < 0)
		return -1;

	itcs_dcache_flush();
	itcs_dma_start(chan);

	uart_read(dev, mem + DMA_BUFLEN / 2, DMA_BUFLEN / 2);

	while (1) {
		ret = itcs_dma_transfer_completed(chan, cookie, NULL);
		if (ret != DMA_IN_PROGRESS)
			break;

		udelay(100);
	}
	if (ret == DMA_COMPLETE &&
	    !memcmp((char *)phys_to_virt(prep_info.src), mem + DMA_BUFLEN / 2,
		    prep_info.len)) {
		printf("Test DMA MemtoDev %s Pass\n", info.devname);
		ret = 0;
	} else {
		printf("Test DMA MemtoDev %s Failed\n", info.devname);
		ret = -1;
	}

//#if !defined(CONFIG_CACHE_LITE)
	free(mem);
//#endif
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
	return ret;
}

static int dmatest_devtomem(int dma_id)
{
	struct dma_chan *chan = NULL;
	struct dma_prep_info prep_info;
	struct dma_slave_config cfg;
	struct dma_info info = {
		.devname = "dma0",
		.src_hw_handshake_num = DMAC0_CUART3_RX,
	};
	char *mem = NULL;
	dma_cookie_t cookie;
	tty_dev_t *dev = &ttydev_0;
	int ret;

	if (dma_id == 1) {
		info.devname = "dma1";
		info.src_hw_handshake_num = DMAC1_CUART1_RX;
	}

	printf("test len: %d\n", DMA_BUFLEN / 2);

	chan = itcs_dma_request_channel(&info);
	if (!chan)
		return -1;

//#if defined(CONFIG_CACHE_LITE)
//	mem = (char *)DMA_UNCACHEABLE_MEM;
//#else
	mem = malloc(DMA_BUFLEN);
//#endif
	if (!mem)
		return -1;

	memset(mem, 0x0, DMA_BUFLEN / 2);
	memset(mem + DMA_BUFLEN / 2, 0xa5, DMA_BUFLEN / 2);

	if (dma_id == 1)
		uart_init(dev, SAP, ITCS_S_UART1_BASE, 1,
			  UART_ChannelMode_LocalLoop);
	else if (dma_id == 0)
		uart_init(dev, CPU, ITCS_C_UART3_BASE, 3,
			  UART_ChannelMode_LocalLoop);

	cfg.direction = DMA_DEV_TO_MEM;
	cfg.src_addr = dev->regbase + UART_FIFO;
	cfg.dst_addr = virt_to_phys(mem);
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
#elif defined(CONFIG_COMPILE_RTL)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_4;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_4;
#endif
	cfg.device_fc = 0;
	ret = itcs_dma_slave_config(chan, &cfg);
	if (ret < 0)
		return -1;

	prep_info.direction = DMA_DEV_TO_MEM;
	prep_info.mode = DMA_SLAVE;
	prep_info.dst = virt_to_phys(mem);
	prep_info.len = DMA_BUFLEN / 2;
	prep_info.callback = NULL;
	cookie = itcs_dma_prepare(chan, &prep_info);
	if (cookie < 0)
		return -1;

	itcs_dcache_flush();
	itcs_dma_start(chan);

	uart_start(dev);
	uart_write(dev, mem + DMA_BUFLEN / 2, DMA_BUFLEN / 2);

	while (1) {
		ret = itcs_dma_transfer_completed(chan, cookie, NULL);
		if (ret != DMA_IN_PROGRESS)
			break;

		udelay(100);
	}

	itcs_dcache_flush();
	if (ret == DMA_COMPLETE &&
	    !memcmp((char *)phys_to_virt(prep_info.dst), mem + DMA_BUFLEN / 2,
		    prep_info.len)) {
		printf("Test DMA DevtoMem %s Pass\n", info.devname);
		ret = 0;
	} else {
		printf("Test DMA DevtoMem %s Failed\n", info.devname);
		ret = -1;
	}

//#if !defined(CONFIG_CACHE_LITE)
	free(mem);
//#endif
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
	return ret;
}

static int dmatest_devtodev(int dma_id)
{
	struct dma_chan *chan = NULL;
	struct dma_prep_info prep_info;
	struct dma_slave_config cfg;
	struct dma_info info = {
		.devname = "dma0",
		.src_hw_handshake_num = DMAC0_CUART3_RX,
		.dst_hw_handshake_num = DMAC0_CUART3_TX,
	};
	char *mem = NULL;
	dma_cookie_t cookie;
	tty_dev_t *dev_0 = &ttydev_0;
	tty_dev_t *dev_1 = &ttydev_1;
	int ret;

	if (dma_id == 1) {
		info.devname = "dma1";
		info.src_hw_handshake_num = DMAC1_CUART1_RX;
		info.dst_hw_handshake_num = DMAC1_CUART1_TX;
	}

	printf("test len: %d\n", DEVTODEV_DMA_BUFLEN / 2);

	chan = itcs_dma_request_channel(&info);
	if (!chan)
		return -1;

	mem = malloc(DEVTODEV_DMA_BUFLEN);
	if (!mem)
		return -1;

	memset(mem, 0xac, DEVTODEV_DMA_BUFLEN / 2);
	memset(mem + DEVTODEV_DMA_BUFLEN / 2, 0x0, DEVTODEV_DMA_BUFLEN / 2);

	uart_init(dev_0, SAP, ITCS_S_UART1_BASE, 1, UART_ChannelMode_Normal);
	uart_init(dev_1, CPU, ITCS_C_UART3_BASE, 3, UART_ChannelMode_Normal);
	cfg.direction = DMA_DEV_TO_DEV;
	if (dma_id == 1) {
		cfg.src_addr = dev_0->regbase + UART_FIFO;
		cfg.dst_addr = dev_0->regbase + UART_FIFO;
	} else if (dma_id == 0) {
		cfg.src_addr = dev_1->regbase + UART_FIFO;
		cfg.dst_addr = dev_1->regbase + UART_FIFO;
	}
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
#elif defined(CONFIG_COMPILE_RTL)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_4;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_4;
#endif
	cfg.device_fc = 0;
	ret = itcs_dma_slave_config(chan, &cfg);
	if (ret < 0)
		return -1;

	prep_info.direction = DMA_DEV_TO_DEV;
	prep_info.mode = DMA_SLAVE;
	if (dma_id == 1)
		prep_info.src = dev_0->regbase + UART_FIFO;
	else if (dma_id == 0)
		prep_info.src = dev_1->regbase + UART_FIFO;

	prep_info.len = DEVTODEV_DMA_BUFLEN / 2;
	prep_info.callback = NULL;
	cookie = itcs_dma_prepare(chan, &prep_info);
	if (cookie < 0)
		return -1;

	itcs_dcache_flush();

	uart_start(dev_0);
	uart_start(dev_1);
	if (dma_id == 1)
		uart_write(dev_1, mem, DEVTODEV_DMA_BUFLEN / 2);
	else if (dma_id == 0)
		uart_write(dev_0, mem, DEVTODEV_DMA_BUFLEN / 2);

	itcs_dma_start(chan);

	while (1) {
		ret = itcs_dma_transfer_completed(chan, cookie, NULL);
		if (ret != DMA_IN_PROGRESS)
			break;

		udelay(100);
	}

	if (dma_id == 1)
		uart_read(dev_1, mem + DEVTODEV_DMA_BUFLEN / 2,
			  DEVTODEV_DMA_BUFLEN / 2);
	else if (dma_id == 0)
		uart_read(dev_0, mem + DEVTODEV_DMA_BUFLEN / 2,
			  DEVTODEV_DMA_BUFLEN / 2);

	if (ret == DMA_COMPLETE && !memcmp(mem, mem + DEVTODEV_DMA_BUFLEN / 2,
					   DEVTODEV_DMA_BUFLEN / 2)) {
		printf("Test DMA DevtoDev %s Pass\n", info.devname);
		ret = 0;
	} else {
		printf("Test DMA DevtoDev %s Failed\n", info.devname);
		ret = -1;
	}

	free(mem);
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
	return ret;
}

#ifdef CONFIG_C920
static int dmatest_speed(void)
{
	struct cb_param cbp[SPEED_CHANNEL_NUMS];
	struct dma_prep_info *prep_info = NULL;
	struct dma_prep_info tmp_prep_info[SPEED_CHANNEL_NUMS];
	struct dma_chan *chan[SPEED_CHANNEL_NUMS];
	struct dma_info info = {
		.devname = "dma0",
	};
	int i = 0;
	int ret = 0;
	unsigned long used_time[SPEED_CHANNEL_NUMS] = { 0 };
	unsigned long total_time = 0;

	printf("speed test len: %d\n", DMA_SPEED_BUFLEN / 2);
	dma_speed_test = 1;

	for (i = 0; i < SPEED_CHANNEL_NUMS; i++) {
		memset(&cbp[i], 0, sizeof(cbp[i]));
		chan[i] = dma_prepare(&cbp[i], &tmp_prep_info[i], &info, DMA_SPEED_BUFLEN);
	}
	itcs_dcache_flush();
	for (i = 0; i < SPEED_CHANNEL_NUMS; i++) {
		dma_start(chan[i]);
		speed_start_index++;
	}

	while (1) {
		for (i = 0; i < SPEED_CHANNEL_NUMS; i++) {
			if (cbp[i].finished == 1) {
				if (i == SPEED_CHANNEL_NUMS - 1)
					goto done;
				else
					continue;
			} else {
				break;
			}
		}
		udelay(10);
	}
done:
	for (i = 0; i < SPEED_CHANNEL_NUMS; i++) {
		used_time[i] = dma_stop_time[i] - dma_start_time[i];
		printf("chan %d, time: %ldus, speed: %ldKbytes/s\n", i, used_time[i], (unsigned long)DMA_SPEED_BUFLEN / 2 * 1000000 / used_time[i] / 1024);
		total_time += used_time[i];
	}
	printf("8x total, time: %ldus, speed: %ldKbytes/s\n", total_time, (unsigned long)DMA_SPEED_BUFLEN / 2 * SPEED_CHANNEL_NUMS * 1000000 / total_time / 1024);

	for (i = 0; i < SPEED_CHANNEL_NUMS; i++) {
		prep_info = (struct dma_prep_info *)cbp[i].prep_info;
		itcs_dcache_invalid();
		if (memcmp((char *)phys_to_virt(prep_info->src),
			   (char *)phys_to_virt(prep_info->dst),
			   prep_info->len)) {
			printf("Test DMA %dx speed MemToMem Failed\n", SPEED_CHANNEL_NUMS);
			ret = -1;
			goto err_exit;
		} else {
			continue;
		}
	}

	printf("Test DMA %dx speed MemToMem Pass\n", SPEED_CHANNEL_NUMS);
	ret = 0;
err_exit:
	for (i = SPEED_CHANNEL_NUMS - 1; i >= 0; i--)
		dma_finish(chan[i], &tmp_prep_info[i]);

	return ret;
}
#endif

static void dmatest_show_usage(void)
{
	printf("Usage: dmatest [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("--memtomem\t\tdma transfer from mem to mem\n");
	printf("--memtodev\t\tdma transfer from mem to dev\n");
	printf("--devtomem\t\tdma transfer from dev to mem\n");
	printf("--devtodev\t\tdma transfer from dev to dev\n");
	printf("--multi-memtomem\t\tmulti dma transfer from mem to mem\n");
#ifdef CONFIG_C920
	printf("--speed\t\t8x dma transfer from mem to mem for speed test\n");
#endif
}

int dmatest_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "h";
#ifdef CONFIG_C920
	static const struct option long_options[] = {
		{ "memtomem", 0, 0, 1 },
		{ "memtodev", 1, 0, 2 },
		{ "devtomem", 1, 0, 3 },
		{ "devtodev", 1, 0, 4 },
		{ "multi-memtomem", 0, 0, 5 },
		{ "speed", 0, 0, 6 },
		{ "help", 0, 0, 'h' },
		{ 0, 0, 0, 0 },
	};
#else
	static const struct option long_options[] = {
		{ "memtomem", 0, 0, 1 },
		{ "memtodev", 1, 0, 2 },
		{ "devtomem", 1, 0, 3 },
		{ "devtodev", 1, 0, 4 },
		{ "multi-memtomem", 0, 0, 5 },
		{ "help", 0, 0, 'h' },
		{ 0, 0, 0, 0 },
	};
#endif

	if (!itcs_is_dma_inited(0))
		itcs_dma_init(0);

	if (!itcs_is_dma_inited(1))
		itcs_dma_init(1);

#if defined(CONFIG_CACHE)
	itcs_icache_enable();
	itcs_dcache_enable();
#endif

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		case 1:
			ret = dmatest_memcpy();
			break;
		case 2:
			if (!strcmp(optarg, "dma0"))
				ret = dmatest_memtodev(0);
			else if (!strcmp(optarg, "dma1"))
				ret = dmatest_memtodev(1);
			break;
		case 3:
			if (!strcmp(optarg, "dma0"))
				ret = dmatest_devtomem(0);
			else if (!strcmp(optarg, "dma1"))
				ret = dmatest_devtomem(1);
			break;
		case 4:
			if (!strcmp(optarg, "dma0"))
				ret = dmatest_devtodev(0);
			else if (!strcmp(optarg, "dma1"))
				ret = dmatest_devtodev(1);
			break;
		case 5:
			ret = dmatest_multimemcpy();
			break;
#ifdef CONFIG_C920
		case 6:
			ret = dmatest_speed();
			break;
#endif
		case 'h':
		default:
			dmatest_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (optind == 1) {
		dmatest_show_usage();
		ret = -1;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

void dmatest_init(void)
{
	register_testbench("dma", dmatest_main, NULL);
}

testbench_init(dmatest_init);
