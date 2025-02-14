/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

 /******************************************************************************
 * @file     startup.S
 * @brief    startup file. Should use with
 *           GCC for CSKY Embedded Processors
 * @version  V1.0
 * @date     29. July 2019
 ******************************************************************************/

#include <csi_config.h>
#include <generated/autoconf.h>

.section .text
    .align  2
_start:
    .text
    .align  2
    .globl  Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    /* disable ie and clear all interrupts */
    csrw    mie, zero
    csrw    mip, zero

    /* C920 will invalid all i-cache and d-cache automatically when reset */
    /* invalid all MMU TLB Entry */
    sfence.vma x0,x0

    la      a0, trap_entry
    csrw    mtvec, a0

#if ((CONFIG_CPU_E906F==1) || (CONFIG_CPU_E906D==1))|| (CONFIG_CPU_C920D==1)
    li      a0, 0x2000
    csrs    mstatus, a0
#endif

#if ((CONFIG_CPU_E906F==1) || (CONFIG_CPU_E906D==1))
    la      a0, __Vectors
    csrw    mtvt, a0
#endif

    la      sp, g_top_irqstack

    /* Load data section */
#ifndef CONFIG_COMPILE_SIM
    la      a0, __erodata
    la      a1, __data_start__
    la      a2, __data_end__
    bgeu    a1, a2, 2f
1:
    ld      t0, (a0)
    sd      t0, (a1)
    addi    a0, a0, 8
    addi    a1, a1, 8
    bltu    a1, a2, 1b
2:
#endif

    /* Clear bss section */
    la      a0, __bss_start__
    la      a1, __bss_end__
    bgeu    a0, a1, 2f
1:
    sd      zero, (a0)
    addi    a0, a0, 8
    bltu    a0, a1, 1b
2:

#ifndef __NO_SYSTEM_INIT
#    jal     SystemInit
#endif

#ifndef __NO_BOARD_INIT
#jal     board_init
#endif

    jal     main

    .size   Reset_Handler, . - Reset_Handler

__exit:
    j      __exit

.section .bss
    .align  3
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_irqstack:
