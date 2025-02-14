#include <stdio.h>
#include <asm/io.h>
#include <irq.h>
#include <common.h>
#include <pads.h>

#ifdef CONFIG_COMPILE_SIM
static uint32_t reg_base = CSKY_UART_BASE;
#else
static uint32_t reg_base = ITCS_DUART0_BASE;
#endif

#define DUART_RBR 0x00
#define DUART_THR 0x00
#define DUART_DLL 0x00
#define DUART_DLH 0x04
#define DUART_FCR 0x08
#define DUART_LCR 0x0c
#define DUART_LSR 0x14

// console
int console_puts(const char *str) {
  while (*str) {
    console_putc(*str);
    str++;
  }
  return 0;
}

int console_getc(void) {
  // check rx ready
  while (!(readl(reg_base + DUART_LSR) & 0x1))
    ;
  return readl(reg_base + DUART_RBR) & 0xff;
}

int console_putc(const char c) {
  // check fifo empty
  while (!(readl(reg_base + DUART_LSR) & 0x20))
    ;
  writel(c, reg_base + DUART_THR);
  return c;
}

int console_tstc(void) { return 0; }

void set_baudrate(int baudrate) {
  int clk = itcs_module_get_clock(CPU, "apb");
  int divisor;
  uint32_t value;

  divisor = DIV_ROUND(clk, 16 * baudrate);

  value = readl(reg_base + DUART_LCR);
  value |= (1 << 7);
  writel(value, reg_base + DUART_LCR);

  writel(divisor & 0xff, reg_base + DUART_DLL);
  writel(divisor >> 8, reg_base + DUART_DLH);

  value = readl(reg_base + DUART_LCR);
  value &= ~(1 << 7);
  writel(value, reg_base + DUART_LCR);
}

void console_init(int tty) {
  char name[16] = {0};

  reg_base += (tty * 0x1000);
  sprintf(name, "uart%d", tty);
  itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, name);

  set_baudrate(115200);

  // 8bit noparity 1stop
  writel(0x3, reg_base + DUART_LCR);
}

int init_serial(void) {
  console_init(0);
  return 0;
}
