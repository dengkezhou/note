/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     uart.c
 * @brief    uart Driver
 * @version  V1.0
 * @date     04.15 2022
 * @name     uart
 *
 * @author   jason.liu
 *******************************************************************/

#include <common.h>
#include <asm/io.h>
#include <uart.h>
#include <cdns_uart.h>
#include <dwc_uart.h>
#include <pads.h>

#ifdef CONFIG_DRV_UART
#define CONFIG_CDNS_UART
#endif

static domain_t cdns_uart_get_domain(UART UARTx) {
  if (UARTx <= UART1) {
    return SAP;
  } else if (UARTx <= UART11){
    return CPU;
  } else {
    printf("uart instance number error.\n");
    return 0;
  }
}

static int uart_module_init(UART_InitTypeDef *init) {
  int ret;
  char *module_name = NULL;
  domain_t domain;
  // char * clk_name = NULL;
  // int freq = 12000000;
  switch (init->UARTx) {
  case UART0:
    module_name = "uart0"; // clk_name = "uart0-clk";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case UART1:
    module_name = "uart1"; // clk_name = "uart1-clk";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case UART2:
    module_name = "uart2"; // clk_name = "uart2-clk";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case UART3:
    module_name = "uart3"; // clk_name = "uart3-clk";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case UART4:
    module_name = "uart4"; // clk_name = "uart4-clk";
    itcs_module_set_pads_by_index(module_name, 1);
    break;
  case UART5:
    module_name = "uart5"; // clk_name = "uart5-clk";
    itcs_module_set_pads_by_index(module_name, 1);
    break;
  case UART6:
    module_name = "uart6"; // clk_name = "uart6-clk";
    itcs_module_set_pads_by_index(module_name, 1);
    break;
  case UART7:
    module_name = "uart7"; // clk_name = "uart7-clk";
    itcs_module_set_pads_by_index(module_name, 2);
    break;
  case UART8:
    module_name = "uart8"; // clk_name = "uart8-clk";
    itcs_module_set_pads_by_index(module_name, 2);
    break;
  case UART9:
    module_name = "uart9"; // clk_name = "uart9-clk";
    itcs_module_set_pads_by_index(module_name, 1);
    break;
  case UART10:
    module_name = "uart10"; // clk_name = "uart10-clk";
    itcs_module_set_pads_by_index(module_name, 1);
    break;
  case UART11:
    module_name = "uart11"; // clk_name = "uart11-clk";
    itcs_module_set_pads_by_index(module_name, 0);
    break;  
  default:
    printf("should not be here.\n");
    return -1;
  }

  domain = cdns_uart_get_domain(init->UARTx);

  ret = itcs_module_enable(domain, module_name);
  if (ret) {
    return ret;
  }

  return 0;
}

UART_HandleTypeDef *itcs_uart_init(UART_InitTypeDef *init) {
  if (uart_module_init(init)) {
    printf("uart_module_init failed!\n");
    return NULL;
  }

#ifdef CONFIG_CDNS_UART
  if (init->type == CDNS_UART) {
    return cdns_uart_init(init);
  }
#endif

#ifdef CONFIG_DWC_UART
  if (init->type == DWC_UART) {
    return dwc_uart_init(init);
  }
#endif
  printf("uart type error.\n");
  return NULL;
}

void itcs_uart_deinit(UART_HandleTypeDef *uartHandler) {
#ifdef CONFIG_CDNS_UART
  if (uartHandler->UART_InitStruct.type != CDNS_UART) {
    printf("uart type error!");
    return;
  }
  cdns_uart_deinit(uartHandler);
#endif

#ifdef CONFIG_DWC_UART
  if (uartHandler->UART_InitStruct.type != DWC_UART) {
    printf("uart type error!");
    return;
  }
  dwc_uart_deinit(uartHandler);
#endif
  return;
}

int itcs_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data,
                       uint32_t size, BlockStatus isBlock) {
#ifdef CONFIG_CDNS_UART
  if (uartHandler->UART_InitStruct.type == CDNS_UART) {
    return cdns_uart_transmit(uartHandler, data, size, isBlock);
  }
#endif

#ifdef CONFIG_DWC_UART
  if (uartHandler->UART_InitStruct.type == DWC_UART) {
    return dwc_uart_transmit(uartHandler, data, size, isBlock);
  }
#endif
  return 0;
}

int itcs_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data,
                      uint32_t size, BlockStatus isBlock) {
  while (!((readl(uartHandler->uart_base_addr + 0x2c) & 0x02))) {
    readl(uartHandler->uart_base_addr + 0x30);
  }
#ifdef CONFIG_CDNS_UART
  if (uartHandler->UART_InitStruct.type == CDNS_UART) {
    return cdns_uart_receive(uartHandler, data, size, isBlock);
  }
#endif

#ifdef CONFIG_DWC_UART
  if (uartHandler->UART_InitStruct.type == DWC_UART) {
    return dwc_uart_receive(uartHandler, data, size, isBlock);
  }
#endif
  return 0;
}

int itcs_uart_is_completed(UART_HandleTypeDef *uartHandler, int tx_rx) {
#ifdef CONFIG_CDNS_UART
  if (uartHandler->UART_InitStruct.type == CDNS_UART) {
    return cdns_uart_is_completed(uartHandler, tx_rx);
  }
#endif

#ifdef CONFIG_DWC_UART
  if (uartHandler->UART_InitStruct.type == DWC_UART) {
    return dwc_uart_is_completed(uartHandler, tx_rx);
  }
#endif
  return 0;
}
