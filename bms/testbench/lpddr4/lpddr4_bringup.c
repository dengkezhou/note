
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <uart.h>
#include <cdns_uart.h>
#include <asm/io.h>
#include <getopt.h>
#include <pads.h>
#include <cache.h>
#include <pads.h>
#include <lpddr4.h>

#define WRITE_CMD (0xa5a5a5a5)
#define READ_CMD (0x5a5a5a5a)

struct uart_command {
	unsigned int cmd;
	unsigned int memAddress;
	unsigned int memValue;
};

#define COMMUNICATE_LEN (sizeof(struct uart_command))

#define R_UART_CR 0x00
#define UART_CR_RX_RST 0x01
#define UART_CR_TX_RST 0x02
#define UART_CR_RX_ENABLE 0x04
#define UART_CR_RX_DISABLE 0x08
#define UART_CR_TX_ENABLE 0x10
#define UART_CR_TX_DISABLE 0x20

#define R_UART_MR 0x04
#define UART_MR_NO_PARITY 0x20

#define R_UART_BRGR 0x18
#define R_UART_RTRIG 0x20
#define R_UART_SR 0x2C
#define UART_SR_INTR_RTRIG 0x01
#define UART_SR_INTR_REMPTY 0x02
#define UART_SR_INTR_TEMPTY 0x08
#define UART_SR_INTR_TFUL 0x10

#define R_UART_TTRIG 0x44

#define R_UART_TX 0x30
#define R_UART_RX 0x30

static uint32_t reg_base;

extern int memtester_test(int argc, char **argv);
extern void lpddr4_pi_training(int port, int is_lpddr4x, int freq);

static int lpddr4_uart_read(unsigned char *buf, int len)
{
	int least = len;

	while (least) {
		if (readl(reg_base + R_UART_SR) & UART_SR_INTR_REMPTY) {
			continue;
		}

		*(buf++) = readl(reg_base + R_UART_RX) & 0xff;
		least--;
	}
	return len;
}

static int lpddr4_uart_write(unsigned char *buf, int len)
{
	int least = len;

	while (least) {
		if (readl(reg_base + R_UART_SR) & UART_SR_INTR_TFUL) {
			continue;
		}
		writel(buf[len - least], reg_base + R_UART_RX);
		least--;
	}
	return len;
}

static void lpddr4_set_baudrate(int baudrate)
{
	int clk = itcs_module_get_clock(SAP, "uart");
	int divisor;

	divisor = DIV_ROUND(clk, 16 * baudrate);

	writel(divisor & 0xffff, reg_base + R_UART_BRGR);
}

static void lpddr4_uart_reset(void)
{
	writel(0x3, reg_base + R_UART_CR);
	while ((readl(reg_base + R_UART_CR) & 0x3))
		;
}

static void lpddr4_uart_init(int tty, int baud)
{
	char name[16] = { 0 };
	domain_t domain;
	if (tty < 2) {
		reg_base = ITCS_S_UART0_BASE + (tty * 0x1000);
		domain = SAP;
	} else {
		reg_base = ITCS_C_UART2_BASE + ((tty - 2) * 0x1000);
		domain = CPU;
	}

	sprintf(name, "uart%d", tty);

	itcs_module_enable(domain, name);
	itcs_module_set_pads_by_index(name, 0);

	/* reset path */
	lpddr4_uart_reset();
	/* clock from apb, 8bit data, no parity, 1stop, 1 byte read&write width
   */
	writel(((0x4 << 3) | (0x1 << 12)), reg_base + R_UART_MR);
	lpddr4_set_baudrate(baud);

	writel(0x3, reg_base + R_UART_RTRIG);
	writel(0x3, reg_base + R_UART_TTRIG);

	writel((UART_CR_RX_ENABLE | UART_CR_TX_ENABLE), reg_base + R_UART_CR);
}

static void lpddr4_clksrc_select(int port, uint32_t sel)
{
	unsigned int reg_val = 0;

	if (port == 0) {
		reg_val = (readl(0xc2f08000 + 0x130) & (~0xf)) | (sel);
		writel(reg_val, 0xc2f08000 + 0x130);
	} else {
		reg_val = (readl(0xc2f08000 + 0x2a0) & (~0xf)) | (sel);
		writel(reg_val, 0xc2f08000 + 0x2a0);
	}
}

int lpddr4_bringup_test(int num)
{
	struct uart_command rx_buf;
	struct uart_command tx_buf;
	int ret = 0;
	int params_cnt = 5;
	char *params_0[5] = { "memtester", "-p", "0x100000000", "100M", "1" };
	char *params_1[5] = { "memtester", "-p", "0x500000000", "100M", "1" };

	if (num == DDRAPP_TEST_MPU0 || num == DDRAPP_TEST_MPU1) {
		if (num == DDRAPP_TEST_MPU0) {
			itcs_module_enable(CPU, "ddr");
			/* close clk gate. */
			writel(0xffff, 0xc2f0813c);
			/* from dpll, boot freq 50MHZ. */
			writel(29, 0xc2f08000 + 0xc0 + 0x74); // 29 + 1,30 divi的值
			lpddr4_clksrc_select(0, 1); // 0:apll, 1:dpll, 2:epll, 3:vpll, 4:mosc
			/* reopen clk gate. */
			writel(0x0000, 0xc2f0813c);
			/* release mpu port access for asic. */
			writel(0, 0xc30f0000 + 0x28);
		} else {
			itcs_module_enable(CPU, "ddr1");
			/* close clk gate. */
			writel(0xffff, 0xc2f082ac);
			/* from dpll, boot freq 50MHZ. */
			writel(29, 0xc2f08000 + 0x2a4); // 29 + 1,30 divi的值
			lpddr4_clksrc_select(1, 1); // 0:apll, 1:dpll, 2:epll, 3:vpll, 4:mosc
			/* reopen clk gate. */
			writel(0x0000, 0xc2f082ac);
			/* release mpu port access for asic. */
			writel(0, 0xc31f0000 + 0x28);
		}

		lpddr4_uart_init(1, 115200);
		while (1) {
			memset(&rx_buf, 0, COMMUNICATE_LEN);
			lpddr4_uart_read((unsigned char *)&rx_buf, COMMUNICATE_LEN);
			if (rx_buf.cmd == WRITE_CMD) {
				writel(rx_buf.memValue, rx_buf.memAddress);
				printf("W: 0x%08x, 0x%08x\n", rx_buf.memAddress, rx_buf.memValue);
			} else if (rx_buf.cmd == READ_CMD) {
				tx_buf.cmd = READ_CMD;
				tx_buf.memAddress = rx_buf.memAddress;
				tx_buf.memValue = readl(rx_buf.memAddress);
				lpddr4_uart_write((unsigned char *)&tx_buf, COMMUNICATE_LEN);
				printf("R: 0x%08x, 0x%08x\n", tx_buf.memAddress,
				       tx_buf.memValue);
			} else {
				printf("Unknown command: 0x%x\n", rx_buf.cmd);
				ret = -1;
				goto err;
			}
		}
	} else if (num == LPDDR4_MEMTESTER_TEST_MPU0 || num == LPDDR4_MEMTESTER_TEST_MPU1) {
		if (num == LPDDR4_MEMTESTER_TEST_MPU0) {
			/* mpu0 lpddr4 init, 2133MHz */
			lpddr4_pi_training(0, 1, 2133);
			memtester_test(params_cnt, params_0);
		} else {
			/* mpu1 lpddr4 init, 2133MHz */
			lpddr4_pi_training(1, 1, 2133);
			memtester_test(params_cnt, params_1);
		}
		
	}
err:
	return ret;
}
