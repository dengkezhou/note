/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     duart-main.c
 * @brief    dwc uart testBench
 * @version  V1.0
 * @date     04.16 2022

 * @name     duart-main
 * @author   jason.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <uart.h>
#include <dwc_uart.h>

#if 0
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


int test_console_getc(void) {
  // check rx ready
  while (!(readl(reg_base + DUART_LSR) & 0x1))
    ;
  return readl(reg_base + DUART_RBR) & 0xff;
}

int test_console_putc(const char c) {
  // check fifo empty
  while (!(readl(reg_base + DUART_LSR) & 0x20))
    ;
  writel(c, reg_base + DUART_THR);
  return c;
}




void test_set_baudrate(int baudrate) {
  int clk = itcs_module_get_clock("cpu-pclk");
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

void test_console_init(int tty) {
  char name[16] = {0};

  reg_base += (tty * 0x1000);
  sprintf(name, "uart%d", tty);
  itcs_module_set_pads(FPGA_BIT_V_EMMC, name);
  itcs_module_set_clock("uart-clk",24000000);
  test_set_baudrate(115200);

  // 8bit noparity 1stop
  writel(0x3, reg_base + DUART_LCR);
}

int test_init_serial(void) {
  test_console_init(2);
  return 0;
}

int duart_main(int argc, char *argv[]) {
  test_init_serial();
  while(1){
    char c = (char) test_console_getc();
    test_console_putc(c);
  }
}

void duart_init(void) { register_testbench("duart", duart_main, NULL); }

testbench_init(duart_init);

#endif

#if 1
#define SUCCESS 1
#define FAILURE 0

static void uart_show_usage(void) {
  printf("Usage: duart [OPTION]...\n\n");
  printf("-h, \t\tcommand help.\n");
  printf("-rf,\t\tRS232 & FIFO test.\n");
  printf("-ir,\t\tIrDA test.\n");
  printf("-dm,\t\tdma test.\n");
  printf("-fl,\t\tflow control test.\n");
  printf("-in,\t\tinteraction test.\n");
  printf("-group,\t\tgroup select, 1/2.\n");
  printf("-port,\t\tport select, 0/1/2/3.\n");
}

#ifdef CONFIG_COMPILE_RTL
#define UART_BUF_MAX_SIZE 32
#else
#define UART_BUF_MAX_SIZE 32
#endif

typedef enum {
  CASE_UNDEFINED = 0,
  RS232,
  IRDA,
  DMA,
  FLOW_CTRL,
  INTERACTION
} CASE;

static int easy_test() {
  UART_InitTypeDef init;
  UART_HandleTypeDef *huart;
  uint8_t buffer[32];
  init.UARTx                    = UART2;
  init.type                     = DWC_UART;
  init.UART_BaudRate            = (uint32_t)115200;
  init.UART_WordLength          = DWC_UART_WordLength_8b;
  init.UART_Parity              = DWC_UART_Parity_No;
  init.UART_StopBits            = DWC_UART_StopBits_1;
  init.UART_HardwareFlowControl = DWC_UART_HardwareFlowControl_None;
  init.UART_Mode                = DWC_UART_Mode_UART;
  init.use_dma                  = 0;

  for (uint8_t i = 0; i < 32; i++) {
    buffer[i] = i;
  }

  huart = itcs_uart_init(&init);
  printf("duart easy test\n");
  int num = 0;
  while (1) {
    num = itcs_uart_receive(huart, buffer, 32, BLOCK);
    printf("duart received done, num = %d\n", num);
    printf("read: ");
    for(int i = 0; i<32; i++){
        printf("0x%x ",buffer[i]);
    }
    printf("\n");
    itcs_uart_transmit(huart, buffer, num, BLOCK);
    printf("duart transmit done.\n");
  }
  return 0;
}

static int rs232_fifo_test(int group) {
  UART_InitTypeDef init_a = DWC_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = DWC_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  if (group == 1) {
    init_a.UARTx = UART0;
    init_b.UARTx = UART1;
  } else {
    init_a.UARTx = UART2;
    init_b.UARTx = UART3;
  }
  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  while (1) {
    // uart b received
    if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
        // The data are consistent,send data back.
        memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
        itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
        itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE,
                           BLOCK);
      } else {
        if (group == 1) {
          printf("Test Uart RS232 Failed, uart0 -> uart1 failed!\n");
        } else {
          printf("Test Uart RS232 Failed, uart2 -> uart3 failed!\n");
        }
        return FAILURE;
      }
    }
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        return SUCCESS;
      } else {
        if (group == 1) {
          printf("Test Uart RS232 Failed, uart1 -> uart0 failed!\n");
        } else {
          printf("Test Uart RS232 Failed, uart3 -> uart2 failed!\n");
        }
        return FAILURE;
      }
    }
  }
}

static int dma_test(int group) {
  UART_InitTypeDef init_a = DWC_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = DWC_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.use_dma = DWC_USED_DMA;
  init_b.use_dma = DWC_USED_DMA;
  if (group == 1) {
    init_a.UARTx = UART0;
    init_b.UARTx = UART1;
  } else {
    init_a.UARTx = UART2;
    init_b.UARTx = UART3;
  }
  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  while (1) {
    // uart b received
    if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
        // The data are consistent,send data back.
        memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
        itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE,
                           NONBLOCK);
      } else {
        if (group == 1) {
          printf("Test Uart DMA Failed, uart0 -> uart1 failed!\n");
        } else {
          printf("Test Uart DMA Failed, uart2 -> uart3 failed!\n");
        }
        return FAILURE;
      }
    }
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        return SUCCESS;
      } else {
        if (group == 1) {
          printf("Test Uart DMA Failed, uart1 -> uart0 failed!\n");
        } else {
          printf("Test Uart DMA Failed, uart3 -> uart2 failed!\n");
        }
        return FAILURE;
      }
    }
  }
}

static int irda_test(int group) {
  UART_InitTypeDef init_a = DWC_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = DWC_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UART_Mode = DWC_UART_Mode_IrDA;
  init_b.UART_Mode = DWC_UART_Mode_IrDA;
  if (group == 1) {
    init_a.UARTx = UART0;
    init_a.UARTx = UART1;
  } else {
    init_a.UARTx = UART2;
    init_b.UARTx = UART3;
  }
  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  while (1) {
    // uart b received
    if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
        // The data are consistent,send data back.
        memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
        itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
        itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE,
                           BLOCK);
      } else {
        if (group == 1) {
          printf("Test Uart IrDA Failed, uart0 -> uart1 failed!\n");
        } else {
          printf("Test Uart IrDA Failed, uart2 -> uart3 failed!\n");
        }
        return FAILURE;
      }
    }
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        return SUCCESS;
      } else {
        if (group == 1) {
          printf("Test Uart IrDA Failed, uart1 -> uart0 failed!\n");
        } else {
          printf("Test Uart IrDA Failed, uart3 -> uart2 failed!\n");
        }
        return FAILURE;
      }
    }
  }
}

static int flow_control_test(int group) {
  UART_InitTypeDef init_a = DWC_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = DWC_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UART_HardwareFlowControl = DWC_UART_HardwareFlowControl_Auto;
  init_b.UART_HardwareFlowControl = DWC_UART_HardwareFlowControl_Auto;
  if (group == 1) {
    init_a.UARTx = UART0;
    init_a.UARTx = UART1;
  } else {
    init_a.UARTx = UART2;
    init_b.UARTx = UART3;
  }
  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  while (1) {
    // uart b received
    if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
        // The data are consistent,send data back.
        memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
        itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
        itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE,
                           BLOCK);
      } else {
        if (group == 1) {
          printf("Test Uart Flow Control Failed, uart0 -> uart1 failed!\n");
        } else {
          printf("Test Uart Flow Control Failed, uart2 -> uart3 failed!\n");
        }
        return FAILURE;
      }
    }
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        return SUCCESS;
      } else {
        if (group == 1) {
          printf("Test Uart Flow Control Failed, uart1 -> uart0 failed!\n");
        } else {
          printf("Test Uart Flow Control Failed, uart3 -> uart2 failed!\n");
        }
        return FAILURE;
      }
    }
  }
}

static int interaction_test(int uart) {
  UART_InitTypeDef init_a = DWC_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  switch (uart) {
  case 0:
    init_a.UARTx = UART0;
    break;
  case 1:
    init_a.UARTx = UART1;
    break;
  case 2:
    init_a.UARTx = UART2;
    break;
  case 3:
    init_a.UARTx = UART3;
    break;
  }

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  while (1) {
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      memcpy(uart_a_tx_buffer, uart_a_rx_buffer, huart_a->rxCount);
      itcs_uart_transmit(huart_a, uart_a_tx_buffer, huart_a->rxCount, BLOCK);
      return SUCCESS;
    }
  }
}

int duart_main(int argc, char *argv[]) {
  int ret;
  CASE test_case;
  int test_group = 2, test_port = 1;
  /*
  if (strncmp(argv[1], "-rf", 3) == 0) {
    test_case = RS232;
  } else if (strncmp(argv[1], "-ir", 3) == 0) {
    test_case = IRDA;
  } else if (strncmp(argv[1], "-dm", 3) == 0) {
    test_case = DMA;
  } else if (strncmp(argv[1], "-fl", 3) == 0) {
    test_case = FLOW_CTRL;
  } else if (strncmp(argv[1], "-in", 3) == 0) {
    test_case = INTERACTION;
  } else {
    test_case = CASE_UNDEFINED;
    uart_show_usage();
    return -1;
  }

  if (strncmp(argv[2], "-group", 6) == 0) {
    test_group = simple_strtoul(argv[3], NULL, 10);
  } else if (strncmp(argv[2], "-port", 5) == 0) {
    test_port = simple_strtoul(argv[3], NULL, 10);
  } else {
    printf("cmd error, group or port error.\n");
    return -1;
  }
  */
  easy_test();
  return 0;

  switch (test_case) {
  case RS232:
    printf("Uart RS232 Testing......\n");
    if (rs232_fifo_test(test_group)) {
      printf("Test Uart RS232 Pass.\n");
    }
    break;
  case IRDA:
    printf("Uart IrDA Testing......\n");
    if (irda_test(test_group)) {
      printf("Test Uart IrDA Pass.\n");
    }
    break;
  case DMA:
    printf("Uart DMA Testing......\n");
    if (dma_test(test_group)) {
      printf("Test Uart DMA Pass.\n");
    }
    break;
  case FLOW_CTRL:
    printf("Uart Flow Control Testing......\n");
    if (flow_control_test(test_group)) {
      printf("Test Uart Flow Control Pass.\n");
    }
    break;
  case INTERACTION:
    printf("Uart Interaction Testing......\n");
    if (interaction_test(test_port)) {
      printf("Test Uart Interaction Pass.\n");
    }
    break;
  default:
    uart_show_usage();
    ret = -1;
    goto err;
  }
err:
  return ret;
}

void duart_init(void) { register_testbench("duart", duart_main, NULL); }

testbench_init(duart_init);
#endif