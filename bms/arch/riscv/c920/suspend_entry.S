/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2021 Western Digital Corporation or its affiliates.
 * Copyright (c) 2022 Ventana Micro Systems Inc.
 */

#include <asm/riscv/encoding.h>
#include <asm/riscv/csr.h>
#include <asm/arch-c920/base-map.h>

#ifdef CONFIG_32BIT
#define REG_L		lw
#define REG_S		sw
#define REGBYTES	4
#else
#define REG_L		ld
#define REG_S		sd
#define REGBYTES	8
#endif

	.text
	.altmacro
	.align 2
	.global __cpu_suspend_enter
	.option norelax

__cpu_suspend_enter:
	/* Save registers (except A0 and T0-T6) */
	REG_S	ra, (1 * REGBYTES)(a0)
	REG_S	sp, (2 * REGBYTES)(a0)
	REG_S	gp, (3 * REGBYTES)(a0)
	REG_S	tp, (4 * REGBYTES)(a0)
	REG_S	s0, (8 * REGBYTES)(a0)
	REG_S	s1, (9 * REGBYTES)(a0)
	REG_S	a1, (11 * REGBYTES)(a0)
	REG_S	a2, (12 * REGBYTES)(a0)
	REG_S	a3, (13 * REGBYTES)(a0)
	REG_S	a4, (14 * REGBYTES)(a0)
	REG_S	a5, (15 * REGBYTES)(a0)
	REG_S	a6, (16 * REGBYTES)(a0)
	REG_S	a7, (17 * REGBYTES)(a0)
	REG_S	s2, (18 * REGBYTES)(a0)
	REG_S	s3, (19 * REGBYTES)(a0)
	REG_S	s4, (20 * REGBYTES)(a0)
	REG_S	s5, (21 * REGBYTES)(a0)
	REG_S	s6, (22 * REGBYTES)(a0)
	REG_S	s7, (23 * REGBYTES)(a0)
	REG_S	s8, (24 * REGBYTES)(a0)
	REG_S	s9, (25 * REGBYTES)(a0)
	REG_S	s10, (26 * REGBYTES)(a0)
	REG_S	s11, (27 * REGBYTES)(a0)

	/* Save CSRs */
	csrr	t0, CSR_EPC
	REG_S	t0, (0 * REGBYTES)(a0)
	csrr	t0, CSR_STATUS
	REG_S	t0, (32 * REGBYTES)(a0)
	csrr	t0, CSR_TVAL
	REG_S	t0, (33 * REGBYTES)(a0)
	csrr	t0, CSR_CAUSE
	REG_S	t0, (34 * REGBYTES)(a0)

#ifdef CONFIG_CACHE
	jal itcs_dcache_flush
#endif

	li    t0, RTC_EVENTS
	li		t1, 1
	sb    t1, (t0)

	j     low_power

	/* Load the global pointer */
	.option push
	.option norelax
	.option pop
	.align 2
	.global __cpu_resume_enter
__cpu_resume_enter:
	/* Make A0 point to suspend context */
	//add	a0, a1, zero
	li    t0, RTC_CLRRESET
	li    t1, 0x2
	sb    t1, (t0)

  // get suspend context from rtcinfo
	li    t0, RTC_INFO16
	lbu   t1, 0 * 4(t0)
	slli  t2, t1, 8
	lbu   t1, 1 * 4(t0)
	xor   t2, t2, t1
	slli  t2, t2, 8
	lbu   t1, 2 * 4(t0)
	xor   t2, t2, t1
	slli  t2, t2, 8
	lbu   t1, 3 * 4(t0)
	xor   t2, t2, t1
	slli  t2, t2, 8
	lbu   t1, 4 * 4(t0)
	xor   t2, t2, t1
	slli  t2, t2, 8
	lbu   t1, 5 * 4(t0)
	xor   t2, t2, t1
	slli  t2, t2, 8
	lbu   t1, 6 * 4(t0)
	xor   t2, t2, t1
	slli  t2, t2, 8
	lbu   t1, 7 * 4(t0)
	xor   a0, t2, t1

	/* Restore CSRs */
	REG_L	t0, (0 * REGBYTES)(a0)
	csrw	CSR_EPC, t0
	REG_L	t0, (32 * REGBYTES)(a0)
	csrw	CSR_STATUS, t0
	REG_L	t0, (33 * REGBYTES)(a0)
	csrw	CSR_TVAL, t0
	REG_L	t0, (34 * REGBYTES)(a0)
	csrw	CSR_CAUSE, t0

	/* Restore registers (except A0 and T0-T6) */
  REG_L ra, (1 * REGBYTES)(a0)  
  REG_L sp, (2 * REGBYTES)(a0)  
  REG_L gp, (3 * REGBYTES)(a0)  
  REG_L tp, (4 * REGBYTES)(a0)  
  REG_L s0, (8 * REGBYTES)(a0)  
  REG_L s1, (9 * REGBYTES)(a0)  
  REG_L a1, (11 * REGBYTES)(a0) 
  REG_L a2, (12 * REGBYTES)(a0) 
  REG_L a3, (13 * REGBYTES)(a0) 
  REG_L a4, (14 * REGBYTES)(a0) 
  REG_L a5, (15 * REGBYTES)(a0) 
  REG_L a6, (16 * REGBYTES)(a0) 
  REG_L a7, (17 * REGBYTES)(a0) 
  REG_L s2, (18 * REGBYTES)(a0) 
  REG_L s3, (19 * REGBYTES)(a0) 
  REG_L s4, (20 * REGBYTES)(a0) 
  REG_L s5, (21 * REGBYTES)(a0) 
  REG_L s6, (22 * REGBYTES)(a0) 
  REG_L s7, (23 * REGBYTES)(a0) 
  REG_L s8, (24 * REGBYTES)(a0) 
  REG_L s9, (25 * REGBYTES)(a0) 
  REG_L s10, (26 * REGBYTES)(a0)
  REG_L s11, (27 * REGBYTES)(a0)

	/* Return zero value */
	add	a0, zero, zero

	/* Return to C code */
	ret
