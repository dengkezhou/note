# DMA相关接口说明:

## 头文件

```c
#include <dma-ops.h>
```

## 接口说明

* DMA初始化

```c
int itcs_dma_init(int id)
```

dma初始化。  
参数/返回值列表:
|参数名|参数说明|
|--|--|
|int id|初始化第几路dma(可选值[0,1])<br>DMA0路(spi1, spi2, spi3, cuart2, cuart3, i2s0, i2s1)<br>DMA1路(spi0, cuart0, cuart1)|

|返回值|返回值说明|
|--|--|
|0|初始化成功|
|负值|初始化失败|

* 查询DMA是否初始化
  
```c
bool itcs_is_dma_inited(int id)
```

查询DMA是否初始化。  
参数/返回值列表:
|参数名|参数说明|
|--|--|
|int id|查询第几路dma(可选值[0,1])是否初始化|

|返回值|返回值说明|
|--|--|
|true|DMA已经初始化|
|false|DMA未初始化|

* DMA传输通道申请
  
```c
struct dma_chan *itcs_dma_request_channel(struct dma_info *info)
```

申请DMA通道。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_info *info|申请DMA通道需要的参数|

|返回值|返回值说明|
|--|--|
|struct dma_chan *|申请成功|
|NULL|申请失败|  

结构体说明：

1. struct dma_info

|结构体参数|必填|参数说明|
|--|--|--|
|char *devname|是|dma名(可选dma0或dma1)|
|int src_hw_handshake_num|否|数据从MEM搬运到MEM不需要填，其他都需要。具体如下所示：<br>enum DMAC0_HW_HANDSHAKE {<br>&nbsp;&nbsp;DMAC0_SPI1_TX,<br>&nbsp;&nbsp;DMAC0_SPI1_RX,<br>&nbsp;&nbsp;DMAC0_SPI2_TX,<br>&nbsp;&nbsp;DMAC0_SPI2_RX,<br>&nbsp;&nbsp;DMAC0_SPI3_TX,<br>&nbsp;&nbsp;DMAC0_SPI3_RX,<br>&nbsp;&nbsp;DMAC0_CUART2_TX,<br>&nbsp;&nbsp;DMAC0_CUART2_RX,<br>&nbsp;&nbsp;DMAC0_CUART3_TX,<br/>&nbsp;&nbsp;DMAC0_CUART3_RX,<br/>&nbsp;&nbsp;DMAC0_IIS0_TX,<br/>&nbsp;&nbsp;DMAC0_IIS0_RX,<br/>&nbsp;&nbsp;DMAC0_IIS1_TX,<br/>&nbsp;&nbsp;DMAC0_IIS1_RX<br/>};<br>enum DMAC1_HW_HANDSHAKE {<br>&nbsp;&nbsp;DMAC1_SPI0_TX,<br>&nbsp;&nbsp;DMAC1_SPI0_RX,<br>&nbsp;&nbsp;DMAC1_CUART0_TX,<br>&nbsp;&nbsp;DMAC1_CUART0_RX,<br>&nbsp;&nbsp;DMAC1_CUART1_TX,<br>&nbsp;&nbsp;DMAC1_CUART1_RX,<br>};<br />|
|int dst_hw_handshake_num|否|同src_hw_handshake_num|

* DMA传输通道释放
  
```c
void itcs_dma_release_channel(struct dma_chan *chan)
```

释放DMA通道。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_chan *|dma驱动句柄，itcs_dma_request_channel所得|


* DMA传输描述符准备
  
```c
dma_cookie_t itcs_dma_prepare(struct dma_chan *chan, struct dma_prep_info *info)
```

准备DMA传输描述符。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_chan *|dma驱动句柄，itcs_dma_request_channel所得|
|struct dma_prep_info *|dma传输参数|

|返回值|返回值说明|
|--|--|
|其他|准备成功，建议保留返回值，后续可以用来查询任务完成情况|
|负值|准备失败|

结构体说明：

1. struct dma_prep_info

|结构体参数|必填|参数说明|
|--|--|--|
|enum dma_transaction_type mode|是|传输模式:<br/> DMA_SLAVE: 单次传输模式，传输完成后停止<br/> DMA_CYCLIC: 循环传输模式，除非用户停止，否则dma将一致循环传输|
|enum dma_transfer_direction direction|是|dma传输方向:<br/> DMA_MEM_TO_MEM: dma从源内存地址搬运数据到目的内存地址<br/> DMA_MEM_TO_DEV: dma从源内存地址搬运数据到外设地址<br/> DMA_DEV_TO_MEM: dma从外设地址搬运数据到目的源内存地址<br /> DMA_DEV_TO_DEV: dma从外设地址搬运数据到目的外设地址|
|dma_addr_t src|否|dma传输源地址(在DMA_MEM_TO_MEM, DMA_MEM_TO_DEV，DMA_DEV_TO_DEV的情况下必填)|
|dma_addr_t dst|否|dma传输目标地址(在DMA_MEM_TO_MEM, DMA_DEV_TO_MEM的情况下必填)|
|unsigned long period_len|否|dma单次描述符传输长度，DMA_CYCLIC模式专用|
|unsigned long len|是|dma传输长度|
|void (*callback)(void *arg)|否|回调函数，dma完成传输后调用，异步通知完成机制|
|void *callback_param|否|回调函数回传的参数|


* DMA传输参数设置
  
```c
int itcs_dma_slave_config(struct dma_chan *chan, struct dma_slave_config *cfg)
```

设置DMA传输参数(DMA_MEM_TO_MEM模式下不需要调用)。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_chan *|dma驱动句柄，itcs_dma_request_channel所得|
|struct dma_slave_config *|dma传输参数|

|返回值|返回值说明|
|--|--|
|0|设置成功|
|负值|设置失败|

结构体说明：

1. struct dma_slave_config

|结构体参数|必填|参数说明|
|--|--|--|
|enum dma_transfer_direction direction|是|dma传输方向:<br/> DMA_MEM_TO_MEM: dma从源内存地址搬运数据到目的内存地址<br/> DMA_MEM_TO_DEV: dma从源内存地址搬运数据到外设地址<br/> DMA_DEV_TO_MEM: dma从外设地址搬运数据到目的源内存地址<br />DMA_DEV_TO_DEV: dma从外设地址搬运数据到目的外设地址|
|dma_addr_t src_addr|否|dma传输源地址(在DMA_DEV_TO_MEM，DMA_DEV_TO_DEV的情况下必填)|
|dma_addr_t dst_addr|否|dma传输目的地址(在DMA_MEM_TO_DEV，DMA_DEV_TO_DEV的情况下必填)|
|enum dma_slave_buswidth src_addr_width|是|dma传输源地址位宽(目前可选DMA_SLAVE_BUSWIDTH_1_BYTE, DMA_SLAVE_BUSWIDTH_2_BYTE, DMA_SLAVE_BUSWIDTH_4_BYTE, DMA_SLAVE_BUSWIDTH_8_BYTE)|
|enum dma_slave_buswidth dst_addr_width|是|dma传输目的地址位宽（可选值同enum dma_slave_buswidth src_addr_width）|
|enum dma_slave_burstlen src_burstlen|是|dma传输源burst长度(可选DMA_SLAVE_BURST_TRANS_LEN_1,<br />DMA_SLAVE_BURST_TRANS_LEN_4,<br />DMA_SLAVE_BURST_TRANS_LEN_8,<br />DMA_SLAVE_BURST_TRANS_LEN_16,<br />DMA_SLAVE_BURST_TRANS_LEN_32,<br />DMA_SLAVE_BURST_TRANS_LEN_64,<br />DMA_SLAVE_BURST_TRANS_LEN_128,<br />DMA_SLAVE_BURST_TRANS_LEN_256,<br />DMA_SLAVE_BURST_TRANS_LEN_512,<br />DMA_SLAVE_BURST_TRANS_LEN_1024)|
|enum dma_slave_burstlen dst_burstlen|是|dma传输目的burst长度（可选值同enum dma_slave_burstlen src_burstlen）|
|bool device_fc|是|指定谁为流控, false时，指定dmac为流控，否则则是具体外设。目前只支持dmac作为流控|

* DMA传输开启
  
```c
int itcs_dma_start(struct dma_chan *chan)
```

开启DMA传输。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_chan *|dma驱动句柄，itcs_dma_request_channel所得|

|返回值|返回值说明|
|--|--|
|0|开启成功|
|负值|开启失败|


* DMA传输停止
  
```c
int itcs_dma_stop(struct dma_chan *chan)
```

关闭DMA传输。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_chan *|dma驱动句柄，itcs_dma_request_channel所得|

|返回值|返回值说明|
|--|--|
|0|关闭成功|
|负值|关闭失败|

* 查询dma通道对某任务的完成情况
  
```c
enum dma_status itcs_dma_transfer_completed(struct dma_chan *chan, dma_cookie_t cookie, struct dma_tx_state *txstate)
```

查询dma通道对某任务的完成情况。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|struct dma_chan *|dma驱动句柄，itcs_dma_request_channel所得|
|cookie|所查询任务的标签，调用itcs_dma_prepare获得|
|struct dma_tx_state *txstate|dma当前传输状态|

|返回值|返回值说明|
|--|--|
|enum dma_status|获得传输状态值：<br/> DMA_COMPLETE: 传输完成<br/>DMA_IN_PROGRESS: 传输进行中<br/>DMA_PAUSED: 传输暂停<br/>DMA_ERROR: 传输错误|

结构体说明：

1. struct dma_tx_state

|结构体参数|必填|参数说明|
|--|--|--|
|dma_cookie_t last|否|最近完成任务的标签|
|dma_cookie_t used|否|正在进行的任务的标签|
|u32 residue|否|还剩下需要传输的字节数|
|u32 in_flight_bytes|否|被cache在dma控制器里的数据|

## 示例代码

```c
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
#endif

#ifdef CONFIG_COMPILE_FPGA
#define DMA_BUFLEN (8192 * 2)
#define DEVTODEV_DMA_BUFLEN (64 * 2)
#elif defined(CONFIG_COMPILE_RTL)
#define DMA_BUFLEN (16 * 2)
#define DEVTODEV_DMA_BUFLEN (16 * 2)
#endif

#ifdef CONFIG_COMPILE_FPGA
/* uart fifo depth is 64. */
#define UART_TRIG_LEVEL (DMA_SLAVE_BURST_TRANS_LEN_32 * DMA_SLAVE_BUSWIDTH_1_BYTE)
#elif defined(CONFIG_COMPILE_RTL)
#define UART_TRIG_LEVEL (DMA_SLAVE_BURST_TRANS_LEN_4 * DMA_SLAVE_BUSWIDTH_1_BYTE)
#endif

#define UART_CTRL  (0x00000000UL)
#define UART_MODE  (0x00000004UL)
#define UART_CISR  (0x00000014UL)
#define UART_BRGR  (0x00000018UL)
#define UART_RTOR  (0x0000001CUL)
#define UART_RTR   (0x00000020UL)
#define UART_MCR   (0x00000024UL)
#define UART_CSR   (0x0000002CUL)
#define UART_FIFO  (0x00000030UL)
#define UART_TTR   (0x00000044UL)
#define UART_IER   (0x00000008UL)
#define UART_IDR   (0x0000000CUL)
#define UART_IMR   (0x00000010UL)

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

#define UART_WordLength_8b		((uint16_t)0x0000)
#define UART_StopBits_1			((uint16_t)0x0000)
#define UART_Parity_No			((uint16_t)0x0020)
#define UART_Mode_UART			((uint16_t)0x0000)
#define UART_WSIZE_1			((uint16_t)0x1000)
#define UART_ChannelMode_Normal		((uint16_t)0x0000)
#define UART_ChannelMode_LocalLoop	((uint16_t)0x0200)
#define UART_HardwareFlowControl_None	((uint16_t)0x0000)

#define UART_SR_INTR_REMPTY 0x02
#define UART_SR_INTR_TFUL   0x10

typedef struct tty_dev {
	int id;
	unsigned long regbase;
} tty_dev_t;

static tty_dev_t ttydev_0;

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
	while ((readl(dev->regbase + UART_CTRL) & 0x3));
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

static void uart_set_baud(tty_dev_t *dev, int baudrate)
{
	int divisor;
	int clk = itcs_module_get_clock(CPU, "uart");
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

static void uart_module_set(tty_dev_t *dev, int domain, unsigned long reg_base, int id)
{
	char name[16] = {0};

	dev->regbase = reg_base;
	dev->id = id;
	sprintf(name, "uart%d", dev->id);
	itcs_module_enable(domain, name);
	itcs_module_set_pads(domain, FPGA_BIT_V_EMMC, name);
	itcs_module_set_clock(domain, "uart", NULL, 24000000, false);

	uart_enable_timeout_dma_req(0);
}

static void uart_start(tty_dev_t *dev)
{
	uart_enable(dev);
}

static tty_dev_t *uart_init(tty_dev_t *dev, int domain, unsigned long reg_base, int id, unsigned int mode)
{
	uart_module_set(dev, domain, reg_base, id);

	uart_disable(dev);
	uart_reset(dev);
	uart_mode_set(dev, mode);
	uart_flow_ctr_set(dev);
#ifdef CONFIG_COMPILE_FPGA
	uart_set_baud(dev, 115200);
#elif defined(CONFIG_COMPILE_RTL)
	uart_set_baud(dev, 921600);
#endif
	uart_set_timeout(dev);
	uart_set_trig_level(dev);
	return dev;
}

static int dmatest_memtodev(void)
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

	chan = itcs_dma_request_channel(&info);
	if (!chan)
		return -1;

	mem = malloc(DMA_BUFLEN);
	if (!mem)
		return -1;

	memset(mem, 0xa5, DMA_BUFLEN / 2);
	memset(mem + DMA_BUFLEN / 2, 0x0, DMA_BUFLEN / 2);

	uart_init(dev, CPU, ITCS_C_UART3_BASE, 3, UART_ChannelMode_LocalLoop);
	uart_start(dev);

	cfg.direction = DMA_MEM_TO_DEV;
	cfg.src_addr = virt_to_phys(mem);
	cfg.dst_addr = dev->regbase + UART_FIFO;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_32;
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
		printf("Test DMA MemtoDev Pass\n");
		ret = 0;
	} else {
		printf("Test DMA MemtoDev Failed\n");
		ret = -1;
	}

	free(mem);
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
	return ret;
}

int main(int argc, char **argv)
{
  if (!itcs_is_dma_inited(0)) {
    itcs_dma_init(0);
  }
#ifdef CONFIG_MMU
  if (!is_cfg_mmu())
    configure_mmu();
#endif
#ifdef CONFIG_CACHE
  itcs_icache_enable();
  itcs_dcache_enable();
#endif
    
  dmatest_memtodev();
  return 0;
}

```
