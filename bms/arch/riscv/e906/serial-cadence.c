#include <stdio.h>
#include <asm/io.h>
#include <irq.h>
#include <common.h>
#include <pads.h>

static uint32_t reg_base = ITCS_S_UART0_BASE;

#define R_UART_CR          0x00
#define UART_CR_RX_RST     0x01
#define UART_CR_TX_RST     0x02
#define UART_CR_RX_ENABLE  0x04
#define UART_CR_RX_DISABLE 0x08
#define UART_CR_TX_ENABLE  0x10
#define UART_CR_TX_DISABLE 0x20

#define R_UART_MR         0x04
#define UART_MR_NO_PARITY 0x20

#define R_UART_BRGR         0x18
#define R_UART_RTRIG        0x20
#define R_UART_SR           0x2C
#define UART_SR_INTR_RTRIG  0x01
#define UART_SR_INTR_REMPTY 0x02
#define UART_SR_INTR_TEMPTY 0x08
#define UART_SR_INTR_TFUL   0x10

#define R_UART_TTRIG 0x44

#define R_UART_TX 0x30
#define R_UART_RX 0x30

// console
int console_puts(const char *str) {
  while (*str) {
    if (*str == 10)
      console_putc(13);
    console_putc(*str);
    str++;
  }
  return 0;
}

int console_getc(void) {
  // check rx ready
  while ((readl(reg_base + R_UART_SR) & UART_SR_INTR_REMPTY))
    ;
  return readl(reg_base + R_UART_RX) & 0xff;
}

int console_putc(const char c) {
  // check fifo empty
  while ((readl(reg_base + R_UART_SR) & UART_SR_INTR_TFUL))
    ;
  writel(c, reg_base + R_UART_TX);
  return c;
}

int console_tstc(void) { 
	while (!(readl(reg_base + R_UART_SR) & UART_SR_INTR_TEMPTY))
		;
	return 0;
}

void set_baudrate(int baudrate) {
  int clk = itcs_module_get_clock(SAP, "uart");
  int divisor;

  divisor = DIV_ROUND(clk, 16 * baudrate);

  writel(divisor & 0xffff, reg_base + R_UART_BRGR);
}

void console_reset(void) {
  writel(0x3, reg_base + R_UART_CR);
  while ((readl(reg_base + R_UART_CR) & 0x3))
    ;
}

void console_init(int tty) {
  char name[16] = {0};
  domain_t domain;
  if(tty < 2){
    reg_base =  ITCS_S_UART0_BASE + (tty * 0x1000);
    domain = SAP;
  }else{
    reg_base =  ITCS_C_UART2_BASE + ((tty-2) * 0x1000);
    domain = CPU;
  }

  sprintf(name, "uart%d", tty);

  itcs_module_enable(domain, name);
  itcs_module_set_pads(domain, FPGA_BIT_V_EMMC, name);

  /* reset path */
  console_reset();
  /* clock from apb, 8bit data, no parity, 1stop, 1 byte read&write width
   */
  writel(((0x4 << 3) | (0x1 << 12)), reg_base + R_UART_MR);
  set_baudrate(115200);

  writel(0x3, reg_base + R_UART_RTRIG);
  writel(0x3, reg_base + R_UART_TTRIG);

  writel((UART_CR_RX_ENABLE | UART_CR_TX_ENABLE), reg_base + R_UART_CR);
}

int init_serial(void) {
  console_init(0);
  return 0;
}
