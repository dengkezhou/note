/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     cdns-uart-main.c
 * @brief    cdns uart testBench
 * @version  V1.0
 * @date     04.16 2022

 * @name     cdns-uart-main
 * @author   jason.liu
 ******************************************************************************/

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

#define SUCCESS 1
#define FAILURE 0

static void uart_show_usage(void) {
  printf("Usage: uart [OPTION]...\n\n");
  printf("-h, \t\tcommand help.\n");
  printf("-n1,\t\tnormal 1 byte test.\n");
  printf("-n2,\t\tnormal 2 byte test.\n");
  printf("-ae,\t\tauto echo test.\n");
  printf("-ll,\t\tloacl loopback test.\n");
  printf("-ir,\t\tIrDA test.\n");
  printf("-fl,\t\tflow control test.\n");
  printf("-in,\t\tinteraction test.\n");
  printf("-first,\t\tfirst uart select, 0~3.\n");
  printf("-second,\t\tsecond uart select, 0~3.\n");
  printf("-port,\t\tport select, 0/1/2/3.\n");
}

#ifdef CONFIG_COMPILE_RTL
#define UART_BUF_MAX_SIZE 32
#else
#define UART_BUF_MAX_SIZE 64
#endif

typedef enum {
  CASE_UNDEFINED = 0,
  NORMAL_1_BYTE,
  NORMAL_2_BYTE,
  NORMAL_4_BYTE,
  AUTO_ECHO,
  LOCAL_LOOPBACK,
  FLOW_CTRL,
  INTERACTION,
  IRDA,
  DMA_TEST,
  FUNC_TEST
} CASE;


struct pads_modules_bundle rtl_uart2_func_test_iolist[] = {
    {"uart2-func1-cpads-68-71", PADSRANGE(68, 71), PADS_FUNC1, PADS_PULL_UP,
     CPU},
    {NULL},
};

struct pads_modules_bundle rtl_uart3_func_test_iolist[] = {
    // 14-15 only tx and rx 
    {"uart3-func1-cpads-72-75", PADSRANGE(72, 75), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart3-func1-cpads-88-92", PADSRANGE(88, 92), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart3-func2-cpads-80-83", PADSRANGE(80, 83), PADS_FUNC2, PADS_PULL_UP, CPU},
    {NULL},
};

struct pads_modules_bundle rtl_uart4_func_test_iolist[] = {
    {"uart4-func1-cpads-115-116", PADSRANGE(115, 116), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart4-func2-cpads-23-24", PADSRANGE(23, 24), PADS_FUNC2, PADS_PULL_UP, CPU},
    {NULL},
};

struct pads_modules_bundle rtl_uart5_func_test_iolist[] = {
    {"uart5-func1-cpads-117-118", PADSRANGE(117, 118), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart5-func2-cpads-25-26", PADSRANGE(25, 26), PADS_FUNC2, PADS_PULL_UP, CPU},
    {NULL},
};

struct pads_modules_bundle rtl_uart6_func_test_iolist[] = {
    {"uart6-func1-cpads-119-120", PADSRANGE(119, 120), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart6-func2-cpads-27-28", PADSRANGE(27, 28), PADS_FUNC2, PADS_PULL_UP, CPU},
    {NULL},
};
struct pads_modules_bundle rtl_uart7_func_test_iolist[] = {
    {"uart7-func1-cpads-121-122", PADSRANGE(121, 122), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart7-func1-cpads-94-95", PADSRANGE(94, 95), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};
struct pads_modules_bundle rtl_uart8_func_test_iolist[] = {
    {"uart8-func1-cpads-123-124", PADSRANGE(123, 124), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"uart8-func1-cpads-96-97", PADSRANGE(96, 97), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};
struct pads_modules_bundle rtl_uart9_func_test_iolist[] = {
    {"uart9-func1-cpads-125-126", PADSRANGE(125, 126), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};
struct pads_modules_bundle rtl_uart10_func_test_iolist[] = {
    {"uart10-func1-cpads-111-112", PADSRANGE(111, 112), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};
struct pads_modules_bundle rtl_uart11_func_test_iolist[] = {
    {"uart11-func1-cpads-78-79", PADSRANGE(78, 79), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};
static int normal_1_byte_test(int first_uart, int second_uart) {
  int comp_a = 0,comp_b = 0;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);
  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = CDNS_DEFAULT_INIT_PARAM;

  init_a.UARTx = (UART)first_uart;
  init_b.UARTx = (UART)second_uart;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);
  // printf("%d, uart%d,1 csr value=%x, \n",__LINE__,
  // huart_a->UART_InitStruct.UARTx, readl(huart_a->uart_base_addr+
  // REG_CSR_OFFSET));
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));
  while (1) {
    // uart b received
    if(comp_a){
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("uart a->b done \n");
          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1; 
        }else {
          printf("Test Uart Normal 1byte Failed, uart%d -> uart%d failed!\n",
                first_uart, second_uart);
          return FAILURE;
        }
      } 
    }
    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart Normal 1byte Failed, uart%d -> uart%d failed!\n",
                second_uart, first_uart);
          printf("uart0 tx[%d]:", huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart1 rx[%d]:", huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart1 tx[%d]:", huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart0 rx[%d]:", huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");
          return FAILURE;
        }
      }
    }
    udelay(1);
  }
}

static int normal_2_byte_test(int first_uart, int second_uart) {
  int comp_a = 0,comp_b = 0;

  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);

  
  UART_InitTypeDef init_a                     = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b                     = CDNS_DEFAULT_INIT_PARAM;
  init_a.UART_WSIZE                           = CDNS_UART_WSIZE_2;
  init_b.UART_WSIZE                           = CDNS_UART_WSIZE_2;

  init_a.UARTx = (UART)first_uart;
  init_b.UARTx = (UART)second_uart;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));
  while (1) {
    if(comp_a){
      // uart b received
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("uart a->b done \n");
          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1;
        } else {
          printf("Test Uart Normal 2byte Failed, uart%d -> uart%d failed!\n",
                first_uart, second_uart);
          return FAILURE;
        }
      }
    }
    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart Normal 2byte Failed, uart%d -> uart%d failed!\n",
                second_uart, first_uart);
          printf("uart0 tx[%d]:", huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart1 rx[%d]:", huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart1 tx[%d]:", huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart0 rx[%d]:", huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");

        return FAILURE;
      }
    }
    udelay(1);
    }
  }
}

static int normal_4_byte_test(int first_uart, int second_uart) {
  int comp_a = 0,comp_b = 0;
 
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);

  UART_InitTypeDef init_a                     = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b                     = CDNS_DEFAULT_INIT_PARAM;
  init_a.UART_WSIZE                           = CDNS_UART_WSIZE_4;
  init_b.UART_WSIZE                           = CDNS_UART_WSIZE_4;

  init_a.UARTx = (UART)first_uart;
  init_b.UARTx = (UART)second_uart;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));
  while (1) {
    if(comp_a){
      // uart b received
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("uart a->b done\n ");
          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1;
        } else {
          printf("Test Uart Normal 4byte Failed, uart%d -> uart%d failed!\n",
                first_uart, second_uart);
          return FAILURE;
        }
      }
    }
    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart Normal 4byte Failed, uart%d -> uart%d failed!\n",
                second_uart, first_uart);
          printf("uart0 tx[%d]:", huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart1 rx[%d]:", huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart1 tx[%d]:", huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart0 rx[%d]:", huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");
          return FAILURE;
        }
      }
    }
    udelay(1);
  }
}

// auto_echo_test testing process
/*
  1.enable the auto echo mode of uart1.
  2.start none block receive function of uart0 and uart1.
  3.uart0 transmits data
  4.uart1 compares received data with transmitted by uart0.
  5.uart0 compares received autoecho data from uart1 with transmitted before.
*/
static int auto_echo_test(int ae_uart, int normal_uart) {
  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = CDNS_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UART_ChannelMode = CDNS_UART_ChannelMode_AutoEcho;
  init_b.UART_ChannelMode = CDNS_UART_ChannelMode_Normal;

  init_a.UARTx = (UART)ae_uart;
  init_b.UARTx = (UART)normal_uart;
  printf("uart_a_rx_addr = %p, uart_b_rx_addr = %p\n", uart_a_rx_buffer,
         uart_b_rx_buffer);
  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_b_tx_buffer[i] = i;
  }

  itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);

  while (1) {
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE) &&
        itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (memcmp(huart_a->rxBufPtr, huart_b->rxBufPtr, huart_b->txCount) ||
          memcmp(huart_b->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        return FAILURE;
      } else {
        return SUCCESS;
      }
    }
  }
}

// local_loopback_test testing process
/*
  1.enable the local loopback mode of uart0.
  2.start none block receive function of uart0.
  3.uart0 transmits data
  4.uart0 compares received data with transmitted before.
*/
static int local_loopback_test(int uart) {
  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UART_ChannelMode = CDNS_UART_ChannelMode_LocalLoop;
  init_a.UARTx = uart;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);

  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  while (1) {
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (memcmp(huart_a->rxBufPtr, huart_a->txBufPtr, huart_a->txCount)) {
        return FAILURE;
      } else {
        return SUCCESS;
      }
    }
  }
}

// irda_test testing process
/*
  1.enable the irda mode of uart0.
  2.start none block receive function of uart0.
  3.uart0 transmits data
  4.uart0 compares received data with transmitted before.
*/
static int irda_test(int first_uart, int second_uart) {
  int comp_a = 0,comp_b = 0;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);

  UART_InitTypeDef init_a                     = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b                     = CDNS_DEFAULT_INIT_PARAM;
  init_a.UART_Mode                            = CDNS_UART_Mode_IrDA;
  init_b.UART_Mode                            = CDNS_UART_Mode_IrDA;
  init_a.UARTx                                = (UART)first_uart;
  init_b.UARTx                                = (UART)second_uart;

  uint32_t val = 0;
  if (first_uart > 1) {
    val = 1 << (first_uart - 2);
    if (second_uart > 1) {
      val |= 1 << (second_uart - 2);
      writel(val, (0XC2F01400 + 0x24)); // C_SYSM_UART
    } else {
      writel(val, 0XC2F01400 + 0x24);              // C_SYSM_UART
      writel(1 << second_uart, 0XD2F01400 + 0x24); // S_SYSM_UART
    }
  } else {
    val = 1 << first_uart;
    if (second_uart <= 1) {
      val |= 1 << second_uart;
      writel(val, 0XD2F01400 + 0x24); // S_SYSM_UART
    } else {
      writel(1 << (first_uart - 2), 0XD2F01400 + 0x24); // S_SYSM_UART
      writel(val, 0XC2F01400 + 0x24);                   // C_SYSM_UART
    }
  }
  
  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;
  uart_a_tx_buffer[0]                     = IRDA_BOF;
  uart_a_tx_buffer[UART_BUF_MAX_SIZE - 1] = IRDA_EOF;

  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));
  while (1) {
    if(comp_a){
      // uart b received
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("uart a->b done \n");
          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1;
        } else {
          printf("Test Uart IrDA Failed, uart%d -> uart%d failed!\n", first_uart,
                second_uart);
          printf("uart%d tx[%d]:", huart_a->UART_InitStruct.UARTx,
                huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart%d rx[%d]:", huart_b->UART_InitStruct.UARTx,
                huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\n");
          return FAILURE;
        }
      }
    }
    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart IrDA Failed, uart%d -> uart%d failed!\n", second_uart,
                first_uart);
          printf("uart%d tx[%d]:", huart_a->UART_InitStruct.UARTx,
                huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart%d rx[%d]:", huart_b->UART_InitStruct.UARTx,
                huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart%d tx[%d]:", huart_b->UART_InitStruct.UARTx,
                huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart%d rx[%d]:", huart_a->UART_InitStruct.UARTx,
                huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");

          return FAILURE;
        }
      }
      udelay(1);
    }
  }
}

// flow_control_test testing process
/*
  1.connect tx&rx of uart0 to rx&tx of uart1 by electric wire
  2.enable the flow control of uart0 and uart1.
  3.start none block receive function of uart0 and uart1.
  4.uart0 transmits data
  5.uart1 transmits received data back to uart0
  6.uart0 compares received data with transmitted before.
*/
static int flow_control_test(int first_uart, int second_uart) {
  int comp_a = 0,comp_b = 0;
  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = CDNS_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);

  init_a.UART_HardwareFlowControl = CDNS_UART_HardwareFlowControl_Auto;
  init_b.UART_HardwareFlowControl = CDNS_UART_HardwareFlowControl_Auto;

  init_a.UARTx = (UART)first_uart;
  init_b.UARTx = (UART)second_uart;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  while (1) {
    // uart b received
    if(comp_a){
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("a->b done.\n");
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          comp_a = 0;
          comp_b = 1;  
                       
        } else {
          printf("Test Uart Flow Control Failed, uart%d -> uart%d failed!\n",
                first_uart, second_uart);
          return FAILURE;
        }
      }
    }

    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart Flow Control Failed, uart%d -> uart%d failed!\n",
                second_uart, first_uart);
          return FAILURE;
        }
      }
    }
    udelay(1);
  }
}

// interaction_test testing process
/*
  1.connect tx&rx of uart0 to rx&tx of PC by electric wire
  2.set uart0 to normal 1byte mode.
  3.uart0 start none block receive and then send data to pc.
  4.PC receive data then transmit these data to uart0.
  5.uart0 compare received data with transmitted data.
*/
static int interaction_test(int uart) {
  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UARTx = uart;


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
/*
static int easy_test(int uart) {
  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  uint8_t uart_a_rx_buffer[2] ;
  uint8_t uart_a_tx_buffer[2] = {0xaa, 0xaa};
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

  while (1) {
      itcs_uart_transmit(huart_a, uart_a_tx_buffer, 1, BLOCK);
      udelay(1000 * 1000);
  }
  return 0;
}
*/

static int dma_test(int first_uart, int second_uart) {
  int comp_a = 0,comp_b = 0;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);

  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = CDNS_DEFAULT_INIT_PARAM;

  init_a.UARTx   = (UART)first_uart;
  init_b.UARTx   = (UART)second_uart;
  init_a.use_dma = 1;
  init_b.use_dma = 1;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;

  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));

  while (1) {
    if(comp_a){
      // uart b received
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        itcs_dcache_invalid_range((unsigned long)huart_b->rxBufPtr,UART_BUF_MAX_SIZE);
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("uart a->b done\n");
          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1;
        } else {
          printf("Test Uart DMA Failed, uart%d -> uart%d failed!\n", first_uart,
                second_uart);
          return FAILURE;
        }
      }
    }

    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        itcs_dcache_invalid_range((unsigned long)huart_a->rxBufPtr,UART_BUF_MAX_SIZE);
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart DMA Failed, uart%d -> uart%d failed!\n", second_uart,
                first_uart);
          printf("uart%d tx[%d]:", huart_a->UART_InitStruct.UARTx,huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart%d rx[%d]:", huart_b->UART_InitStruct.UARTx, huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart%d tx[%d]:", huart_b->UART_InitStruct.UARTx, huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart%d rx[%d]:", huart_a->UART_InitStruct.UARTx, huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");
          return FAILURE;
        }
      }
    }
    udelay(1);
  }
}


static int func_test_rw(int first_uart, struct pads_modules_bundle* first_pads,
                         int second_uart, struct pads_modules_bundle* second_pads){
  int comp_a = 0,comp_b = 0;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);


  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = CDNS_DEFAULT_INIT_PARAM;

  init_a.UARTx = (UART)first_uart;
  init_b.UARTx = (UART)second_uart;
  if(first_pads){
    init_a.pads = first_pads;
  }
  if(second_pads){
    init_b.pads = second_pads;
  }

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));
  while (1) {
    if(comp_a){
      // uart b received
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("uart a->b done\n");
          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1;
        } else {
          printf("Test Uart Function Mode Failed, uart%d -> uart%d failed!\n",
                first_uart, second_uart);
          return FAILURE;
        }
      }
    }
    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart Function Mode Failed, uart%d -> uart%d failed!\n",
                second_uart, first_uart);
          printf("uart0 tx[%d]:", huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart1 rx[%d]:", huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart1 tx[%d]:", huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart0 rx[%d]:", huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");
          return FAILURE;
        }
      }
    }
    udelay(1);
  }

}

static int func_test_flow_control(int first_uart, struct pads_modules_bundle* first_pads,
                         int second_uart, struct pads_modules_bundle* second_pads){
  int comp_a = 0,comp_b = 0;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE] = {0};
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE] = {0};
  printf("uart_a rx addr = 0%p\n", uart_a_rx_buffer);
  printf("uart_a tx addr = 0%p\n", uart_a_tx_buffer);
  printf("uart_b rx addr = 0%p\n", uart_b_rx_buffer);
  printf("uart_b tx addr = 0%p\n", uart_b_tx_buffer);


  UART_InitTypeDef init_a = CDNS_DEFAULT_INIT_PARAM;
  UART_InitTypeDef init_b = CDNS_DEFAULT_INIT_PARAM;
  init_a.UART_HardwareFlowControl = CDNS_UART_HardwareFlowControl_Auto;
  init_b.UART_HardwareFlowControl = CDNS_UART_HardwareFlowControl_Auto;

  init_a.UARTx = (UART)first_uart;
  init_b.UARTx = (UART)second_uart;
  if(first_pads){
    init_a.pads = first_pads;
  }
  if(second_pads){
    init_b.pads = second_pads;
  }

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  comp_a = 1;

  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
  DEBUG_LOG("uart%d transmit done!\n", (int)(huart_a->UART_InitStruct.UARTx));
  while (1) {
    if(comp_a){
      // uart b received
      if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
          // The data are consistent,send data back.
          memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
          printf("a->b done.\n");

          itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE,
                            NONBLOCK);
          DEBUG_LOG("uart%d receive success, transmit start!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, BLOCK);
          DEBUG_LOG("uart%d transmit done!\n",
                    (int)(huart_b->UART_InitStruct.UARTx));
          comp_a = 0;
          comp_b = 1;
   
        } else {
          printf("Test Uart Function Mode with Flow Control Failed, uart%d -> uart%d failed!\n",
                first_uart, second_uart);
          return FAILURE;
        }
      }
    }
    if(comp_b){
      if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
        if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
          return SUCCESS;
        } else {
          printf("Test Uart Function Mode with Flow Control Failed, uart%d -> uart%d failed!\n",
                second_uart, first_uart);
          printf("uart0 tx[%d]:", huart_a->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->txBufPtr + i));
          }
          printf("\nuart1 rx[%d]:", huart_b->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->rxBufPtr + i));
          }
          printf("\nuart1 tx[%d]:", huart_b->txCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_b->txBufPtr + i));
          }
          printf("\nuart0 rx[%d]:", huart_a->rxCount);
          for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
            printf("%d ", *(huart_a->rxBufPtr + i));
          }
          printf("\n");
          return FAILURE;
        }
      }
    }
    udelay(1);
  }

}

/*
  uart0&uart1 only 1 function port, already tested in other cases.
  uart2 has 1 function mode isn`t tested.
  uart3 has 3 function mode isn`t tested.
  this case inplement by read&write between uart2-func1-68-71 and uart3-func1-14-15.

*/
static int func_test(int test_port){
    int fail = 0;
    switch (test_port)
    {
    case 0:
      if(func_test_rw(1, NULL, 3, &rtl_uart3_func_test_iolist[0])){
            printf("Test %s Function Mode Pass.\n", rtl_uart3_func_test_iolist[0].name);
        }else{
            fail++;
        }
      break;
    case 1:
      if(func_test_flow_control(2, &rtl_uart2_func_test_iolist[0] , 3, &rtl_uart3_func_test_iolist[1])){
            printf("Test %s %s Function Mode Pass.\n",rtl_uart2_func_test_iolist[0].name, rtl_uart3_func_test_iolist[1].name);
        }else{
            fail++;
        }
        break;
    case 2:
      if(func_test_flow_control(2, NULL , 3, &rtl_uart3_func_test_iolist[2])){
            printf("Test %s Function Mode Pass.\n", rtl_uart3_func_test_iolist[2].name);
        }else{
            fail++;
        }
        break;
    case 3:
      if (func_test_rw(4,&rtl_uart4_func_test_iolist[0],5,&rtl_uart5_func_test_iolist[0]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart4_func_test_iolist[0].name, rtl_uart5_func_test_iolist[0].name);
      }else{
          fail++;
      }
      break;
    case 4:
      if (func_test_rw(6,&rtl_uart6_func_test_iolist[0],7,&rtl_uart7_func_test_iolist[0]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart6_func_test_iolist[0].name, rtl_uart7_func_test_iolist[0].name);
      }else{
          fail++;
      }
    case 5:
      if (func_test_rw(8,&rtl_uart8_func_test_iolist[0],9,&rtl_uart9_func_test_iolist[0]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart8_func_test_iolist[0].name, rtl_uart9_func_test_iolist[0].name);
      }else{
          fail++;
      }
      break;
    case 6:
      if (func_test_rw(10,&rtl_uart10_func_test_iolist[0],11,&rtl_uart11_func_test_iolist[0]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart10_func_test_iolist[0].name, rtl_uart11_func_test_iolist[0].name);
      }else{
          fail++;
      }
      break;
    case 7:
      if (func_test_rw(4,&rtl_uart4_func_test_iolist[1],5,&rtl_uart5_func_test_iolist[1]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart4_func_test_iolist[1].name, rtl_uart5_func_test_iolist[1].name);
      }else{
          fail++;
      }
      break;
    case 8:
      if (func_test_rw(6,&rtl_uart6_func_test_iolist[1],7,&rtl_uart7_func_test_iolist[1]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart6_func_test_iolist[1].name, rtl_uart7_func_test_iolist[1].name);
      }else{
          fail++;
      }
      break;
    case 9:
      if (func_test_rw(8,&rtl_uart8_func_test_iolist[1],7,&rtl_uart7_func_test_iolist[1]))
      {
            printf("Test %s %s Function Mode Pass.\n",rtl_uart8_func_test_iolist[1].name, rtl_uart7_func_test_iolist[1].name);
      }else{
          fail++;
      }
      break;
    default:
      break;
    }
    
    if(fail){
        return FAILURE;
    }
    return SUCCESS;
}

int cuart_main(int argc, char *argv[]) {
  int ret;
  CASE test_case;
  int test_first_uart = 0, test_second_uart = 0, test_port = 1;

  if (strncmp(argv[1], "-n1", 3) == 0) {
    test_case = NORMAL_1_BYTE;
  } else if (strncmp(argv[1], "-n2", 3) == 0) {
    test_case = NORMAL_2_BYTE;
  } else if (strncmp(argv[1], "-n4", 3) == 0) {
    test_case = NORMAL_4_BYTE;
  } else if (strncmp(argv[1], "-ae", 3) == 0) {
    test_case = AUTO_ECHO;
  } else if (strncmp(argv[1], "-ll", 3) == 0) {
    test_case = LOCAL_LOOPBACK;
  } else if (strncmp(argv[1], "-ir", 3) == 0) {
    test_case = IRDA;
  } else if (strncmp(argv[1], "-fl", 3) == 0) {
    test_case = FLOW_CTRL;
  } else if (strncmp(argv[1], "-in", 3) == 0) {
    test_case = INTERACTION;
  } else if (strncmp(argv[1], "-dm", 3) == 0) {
    test_case = DMA_TEST;
  } else if (strncmp(argv[1], "-fc", 3) == 0) {
    test_case = FUNC_TEST;
  } else {
    test_case = CASE_UNDEFINED;
  }

  if (strncmp(argv[2], "-first", 6) == 0) {
    if (argc < 6) {
      uart_show_usage();
      ret = -1;
      goto err;
    }
    test_first_uart = simple_strtoul(argv[3], NULL, 10);

    if (strncmp(argv[4], "-second", 7) == 0) {
      test_second_uart = simple_strtoul(argv[5], NULL, 10);
    }

  } else if (strncmp(argv[2], "-port", 5) == 0) {
    test_port = simple_strtoul(argv[3], NULL, 10);
  }
  switch (test_case) {
  case NORMAL_1_BYTE:
    printf("Uart Normal 1 byte Testing......\n");
    if (normal_1_byte_test(test_first_uart, test_second_uart)) {
      printf("Test Uart Normal 1byte Pass.\n");
      return 0;
    }
    printf("Test Uart Normal 1byte failed.\n");
    break;
  case NORMAL_2_BYTE:
    printf("Uart Normal 2 byte Testing......\n");
    if (normal_2_byte_test(test_first_uart, test_second_uart)) {
      printf("Test Uart Normal 2byte Pass.\n");
      return 0;
    }
    break;
  case NORMAL_4_BYTE:
    printf("Uart Normal 4 byte Testing......\n");
    if (normal_4_byte_test(test_first_uart, test_second_uart)) {
      printf("Test Uart Normal 4byte Pass.\n");
      return 0;
    }
    break;
  case AUTO_ECHO:
    printf("Uart Auto Echo Testing......\n");
    if (auto_echo_test(test_first_uart, test_second_uart)) {
      printf("Test Uart Automatic Echo Pass.\n");
      return 0;
    } else {
      printf("Test Uart Automatic Echo Failed.\n");
    }

    break;
  case LOCAL_LOOPBACK:
    printf("Uart Local Loopback Testing......\n");
    if (local_loopback_test(test_port)) {
      printf("Test Uart Local Loopback Pass.\n");
      return 0;
    }
    break;
  case IRDA:
    printf("Uart IrDA Testing......\n");
    if (irda_test(test_first_uart, test_second_uart)) {
      printf("Test Uart IrDA Pass.\n");
      return 0;
    }
    break;
  case FLOW_CTRL:
    printf("Uart Flow Control Testing......\n");
    if (flow_control_test(test_first_uart, test_second_uart)) {
      printf("Test Uart Flowctrl Pass.\n");
      return 0;
    }
    break;
  case INTERACTION:
    printf("Uart Interaction Testing......\n");
    if (interaction_test(test_port)) {
      printf("Test Uart Interaction Pass.\n");
      return 0;
    }
    break;
  case DMA_TEST:
    printf("Uart DMA Testing......\n");
    if (dma_test(test_first_uart, test_second_uart)) {
      printf("Test Uart DMA Pass.\n");
      return 0;
    }
    break;
  case FUNC_TEST:
    printf("Uart Function Mode Testing......\n");
    if (func_test(test_port)) {
      printf("Test Function Mode Pass.\n");
      return 0;
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

void cuart_init(void) { register_testbench("cuart", cuart_main, NULL); }

testbench_init(cuart_init);
