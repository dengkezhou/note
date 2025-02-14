#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <common.h>

#ifdef CONFIG_COMPILE_SIM
typedef enum IRQn {
  User_Software_IRQn    = 0,
  Supervisor_Software_IRQn = 1,
  Machine_Software_IRQn = 3,
  User_Timer_IRQn       = 4, /* User timer interrupt */
  Supervisor_Timer_IRQn = 5,
  CORET_IRQn            = 7,
  Machine_External_IRQn = 11,
  UART_IRQn             = 16, /* uart Interrupt */
  TIM0_IRQn             = 18, /* timer0 Interrupt */
  TIM1_IRQn             = 19, /* timer1 Interrupt */
  TIM2_IRQn             = 20, /* timer2 Interrupt */
  TIM3_IRQn             = 21, /* timer3 Interrupt */
  GPIO0_IRQn            = 22, /* gpio0 Interrupt */
  GPIO1_IRQn            = 23, /* gpio1 Interrupt */
  GPIO2_IRQn            = 24, /* gpio2 Interrupt */
  GPIO3_IRQn            = 25, /* gpio3 Interrupt */
  GPIO4_IRQn            = 26, /* gpio4 Interrupt */
  GPIO5_IRQn            = 27, /* gpio5 Interrupt */
  GPIO6_IRQn            = 28, /* gpio6 Interrupt */
  GPIO7_IRQn            = 29, /* gpio7 Interrupt */
  STIM0_IRQn            = 30, /* stimer0 Interrupt */
  STIM1_IRQn            = 31, /* stimer1 Interrupt */
  STIM2_IRQn            = 32, /* stimer2 Interrupt */
  STIM3_IRQn            = 33, /* stimer3 Interrupt */
  PAD_IRQn              = 34, /* pad Interrupt */
  MAX_IRQn,

} IRQn_Type;
#else

#error Not support yet!

#endif

#endif
