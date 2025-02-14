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

#include "csi_config.h"
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
    la      a0, trap_entry
    ori	    a0, a0, 3
    csrw    mtvec, a0

    la      sp, g_top_irqstack
    csrw    mscratch, sp

    /* Load data section */
#ifndef CONFIG_COMPILE_SIM
    la      a0, __data_load__
    la      a1, __data_start__
    la      a2, __data_end__
    bgeu    a0, a1, 2f
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b
2:
#endif

#ifndef CONFIG_COMPILE_RTL
    /* Clear bss section */
    la      a0, __bss_start__
    la      a1, __bss_end__
    bgeu    a0, a1, 2f
1:
    sw      zero, (a0)
    addi    a0, a0, 4
    bltu    a0, a1, 1b
2:
#endif

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
