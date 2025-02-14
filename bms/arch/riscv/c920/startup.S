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
#include <asm/arch-c920/base-map.h>

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

		/* enable THEADISAEE */
		li  		t0, 0x400000
		csrs    mxstatus,t0
	
		/* enable fpu & vector */
		li      t0, 0x802200
		csrs    mstatus,t0

		/* enable unalign ucme-u, clintee-clint, MAEE, THEADISAEE */
		li      t0, 0x638000
		csrs    mxstatus,t0
#ifndef CONFIG_COMPILE_SIM	
		/* msmpr: muti-core snoop en */
		csrsi   msmpr, 0x1
#endif

    /* C920 will invalid all i-cache and d-cache automatically when reset */
    /* invalid all MMU TLB Entry */
    sfence.vma x0,x0

		/* disable mmu */
		csrw satp, zero

    la      a0, mtrap_entry
    csrw    mtvec, a0

#if ((CONFIG_CPU_E906F==1) || (CONFIG_CPU_E906D==1))|| (CONFIG_CPU_C920D==1)
    li      a0, 0x2000
    csrs    mstatus, a0
#endif

#if ((CONFIG_CPU_E906F==1) || (CONFIG_CPU_E906D==1))
    la      a0, __Vectors
    csrw    mtvt, a0
#endif

		/* invalid all memory for IBP,BTB,BHT, DCACHE,ICACHE? but need in fpga */
		li      t0, 0x70013
		csrs    mcor,t0

		/* enable BHT, BTB, IBP, RAS, WA */
		li      t0, 0x11fc
		csrs    mhcr,t0

		/* enable lbuf, way_pred, data_cache_prefetch, amr */
		li      t0, 0x6e30c
		csrs    mhint,t0

		/* mccr2 */
		li      t0, 0xe0000009
		csrs    mccr2,t0

		/* support pm */
		li			t0, RTC_RESETSTS
		ld      t1, (t0)
		andi 		t1, t1, 0x2
		bne			t1, zero, __cpu_resume_enter

		/* support smp core*/
		la      t0, g_top_irqstack
		li      t1, CONFIG_ARCH_INTERRUPTSTACK
		li      t2, CONFIG_NR_CPUS
		csrr    a0, mhartid
		bge     a0, t2, low_power
		mul     t1, t1, a0
		sub     sp, t0, t1
		bne     a0, zero, boot_slave

    /* Load data section */
#ifndef CONFIG_COMPILE_SIM
    la      a0, __data_load__
    la      a1, __data_start__
    la      a2, __data_end__
    beq     a0, a1, 2f
1:
    ld      t0, (a0)
    sd      t0, (a1)
    addi    a0, a0, 8
    addi    a1, a1, 8
    bltu    a1, a2, 1b
2:
#endif

#ifndef CONFIG_COMPILE_RTL
    /* Clear bss section */
    la      a0, __bss_start__
    la      a1, __bss_end__
    bgeu    a0, a1, 2f
1:
    sd      zero, (a0)
    addi    a0, a0, 8
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
	.globl boot_slave
boot_slave:
#ifndef CONFIG_COMPILE_RTL
  // clear sp memory
	li      t1, (CONFIG_ARCH_INTERRUPTSTACK/4)
	add  		t2, sp, zero
clrloop:
  sd      zero, 0(t2)
  addi    t2, t2, -8
  addi    t1, t1, -1
  bnez    t1, clrloop 
#endif

	/* rtcinfo0 flag for boot */
	li   t0, RTC_INFO0
	ld   t1, (t0)
	li   t2, 0x3b
	bne  t1, t2, low_power

	lbu  t1, 1 * 4(t0)
	slli t2, t1, 8
	lbu  t1, 2 * 4(t0)
	xor  t2, t2, t1
	slli t2, t2, 8
	lbu  t1, 3 * 4(t0)
	xor  t2, t2, t1
	slli t2, t2, 8
	lbu  t1, 4 * 4(t0)
	xor  t2, t2, t1
	slli t2, t2, 8
	lbu  t1, 5 * 4(t0)
	xor  t2, t2, t1
	slli t2, t2, 8
	lbu  t1, 6 * 4(t0)
	xor  t2, t2, t1
	slli t2, t2, 8
	lbu  t1, 7 * 4(t0)
	xor  t2, t2, t1
	slli t2, t2, 8
	lbu  t1, 8 * 4(t0)
	xor  t2, t2, t1

	slli t1, a0, 3
	add  t2, t2, t1
	li   t3, 1
	sd   t3, (t2)

	fence iorw, iorw
hold:
  ld   t1, (t2)
	beq  t1, t3, hold

	jalr zero, t1, 0
	 	
.section .text, "ax", %progbits
  .align 3
	.globl low_power
low_power:
	wfi
	j low_power


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
    .space CONFIG_ARCH_INTERRUPTSTACK * CONFIG_NR_CPUS
g_top_irqstack:
