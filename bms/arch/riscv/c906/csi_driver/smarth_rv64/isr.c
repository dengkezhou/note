/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     isr.c
 * @brief    source file for the interrupt server route
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <drv_common.h>
#include <csi_config.h>
#include "soc.h"
#ifndef CONFIG_KERNEL_NONE
//#include <csi_kernel.h>
#endif

#ifndef CONFIG_SYSTICK_HZ
#define CONFIG_SYSTICK_HZ 100
#endif

extern void ck_usart_irqhandler(int32_t idx);
extern void dw_timer_irqhandler(int32_t idx);
extern void dw_gpio_irqhandler(int32_t idx);
extern void systick_handler(void);
extern void xPortSysTickHandler(void);
extern void OSTimeTick(void);

#define ATTRIBUTE_ISR

#define readl(addr)                                                            \
  ({                                                                           \
    unsigned int __v = (*(volatile unsigned int *)(addr));                     \
    __v;                                                                       \
  })

#ifndef CONFIG_KERNEL_NONE
#define CSI_INTRPT_ENTER() 0 // csi_kernel_intrpt_enter()
#define CSI_INTRPT_EXIT()  0 // csi_kernel_intrpt_exit()
#else
#define CSI_INTRPT_ENTER()
#define CSI_INTRPT_EXIT()
#endif

ATTRIBUTE_ISR void CORET_IRQHandler(void) {
#ifndef CONFIG_KERNEL_FREERTOS
  CSI_INTRPT_ENTER();
#endif

  csi_coret_config(drv_get_sys_freq() / CONFIG_SYSTICK_HZ, 0x0);

#if defined(CONFIG_KERNEL_RHINO)
  systick_handler();
#elif defined(CONFIG_KERNEL_FREERTOS)
  xPortSysTickHandler();
#elif defined(CONFIG_KERNEL_UCOS)
  OSTimeTick();
#endif

#ifndef CONFIG_KERNEL_FREERTOS
  CSI_INTRPT_EXIT();
#endif
}

ATTRIBUTE_ISR void USART_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  ck_usart_irqhandler(0);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM0_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_timer_irqhandler(0);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM1_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_timer_irqhandler(1);
  CSI_INTRPT_EXIT();
}
ATTRIBUTE_ISR void TIM2_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_timer_irqhandler(2);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM3_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_timer_irqhandler(3);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO0_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(0);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO1_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(1);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO2_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(2);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO3_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(3);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO4_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(4);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO5_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(5);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO6_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(6);
  CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO7_IRQHandler(void) {
  CSI_INTRPT_ENTER();
  dw_gpio_irqhandler(7);
  CSI_INTRPT_EXIT();
}
