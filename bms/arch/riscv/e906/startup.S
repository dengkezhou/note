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
    li      ra, 0
    call    _reset_regs

	  /* disable ie and clear all interrupts */
		csrw    mie, zero
		csrw    mip, zero
	
		# enable fpu
		li      t0, 0x2000
		csrs    mstatus, t0

    # set cache config and disable icache&dcache
		li      t0, 0x103c
		csrw    mhcr, t0

    la      a0, trap_entry
    ori	    a0, a0, 3
    csrw    mtvec, a0

    la      sp, g_top_irqstack
    csrw    mscratch, sp

    /* Load data section */
#if !defined(CONFIG_COMPILE_SIM)
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

.section .text, "ax", %progbits
	.align 3
	.globl _reset_regs
_reset_regs:
	/* flush the instruction cache */
	fence.i
	/* Reset all registers except ra, a0, a1, a2, gp */
	li sp, 0
#li gp, 0
	li tp, 0
	li t0, 0
	li t1, 0
	li t2, 0
	li s0, 0
	li s1, 0
	li a3, 0
	li a4, 0
	li a5, 0
	li a6, 0
	li a7, 0
	li s2, 0
	li s3, 0
	li s4, 0
	li s5, 0
	li s6, 0
	li s7, 0
	li s8, 0
	li s9, 0
	li s10, 0
	li s11, 0
	li t3, 0
	li t4, 0
	li t5, 0
	li t6, 0
	csrw mscratch, 0
	
	li  t1, 0x6000
	csrs  mstatus, t1
	fmv.s.x f0, zero
	fmv.s.x f1, zero
	fmv.s.x f2, zero
	fmv.s.x f3, zero
	fmv.s.x f4, zero
	fmv.s.x f5, zero
	fmv.s.x f6, zero
	fmv.s.x f7, zero
	fmv.s.x f8, zero
	fmv.s.x f9, zero
	fmv.s.x f10, zero
	fmv.s.x f11, zero
	fmv.s.x f12, zero
	fmv.s.x f13, zero
	fmv.s.x f14, zero
	fmv.s.x f15, zero
	fmv.s.x f16, zero
	fmv.s.x f17, zero
	fmv.s.x f18, zero
	fmv.s.x f19, zero
	fmv.s.x f20, zero
	fmv.s.x f21, zero
	fmv.s.x f22, zero
	fmv.s.x f23, zero
	fmv.s.x f24, zero
	fmv.s.x f25, zero
	fmv.s.x f26, zero
	fmv.s.x f27, zero
	fmv.s.x f28, zero
	fmv.s.x f29, zero
	fmv.s.x f30, zero
	fmv.s.x f31, zero
	csrw  fcsr, 0

	ret

__exit:
    j      __exit

.section .bss

    .align  3
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_irqstack:
