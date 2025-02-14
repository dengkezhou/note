/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * M-mode Trap Handler Code for RISC-V Core
 *
 * Copyright (c) 2017 Microsemi Corporation.
 * Copyright (c) 2017 Padmarao Begari <Padmarao.Begari@microsemi.com>
 *
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 *
 * Copyright (C) 2018, Bin Meng <bmeng.cn@gmail.com>
 */

#include <asm/riscv/encoding.h>
#include <generated/autoconf.h>

#ifdef CONFIG_32BIT
#define LREG		lw
#define SREG		sw
#define FLREG		flw
#define FSREG		fsw
#define REGBYTES	4
#define FREGBYTES	8
#else
#define LREG		ld
#define SREG		sd
#define FLREG		fld
#define FSREG		fsd
#define REGBYTES	8
#define FREGBYTES 8
#endif

/* Enable interrupts when returning from the handler */
#define MSTATUS_PRV1 0x1880

	.text

	/* trap entry */
	.align 6
	.global trap_entry
trap_entry:
	# disable mie
	csrc    mstatus, 8

	addi sp, sp, -32 * REGBYTES
	SREG x1,   1 * REGBYTES(sp)
	SREG x2,   2 * REGBYTES(sp)
	SREG x3,   3 * REGBYTES(sp)
	SREG x4,   4 * REGBYTES(sp)
	SREG x5,   5 * REGBYTES(sp)
	SREG x6,   6 * REGBYTES(sp)
	SREG x7,   7 * REGBYTES(sp)
	SREG x8,   8 * REGBYTES(sp)
	SREG x9,   9 * REGBYTES(sp)
	SREG x10, 10 * REGBYTES(sp)
	SREG x11, 11 * REGBYTES(sp)
	SREG x12, 12 * REGBYTES(sp)
	SREG x13, 13 * REGBYTES(sp)
	SREG x14, 14 * REGBYTES(sp)
	SREG x15, 15 * REGBYTES(sp)
	SREG x16, 16 * REGBYTES(sp)
	SREG x17, 17 * REGBYTES(sp)
	SREG x18, 18 * REGBYTES(sp)
	SREG x19, 19 * REGBYTES(sp)
	SREG x20, 20 * REGBYTES(sp)
	SREG x21, 21 * REGBYTES(sp)
	SREG x22, 22 * REGBYTES(sp)
	SREG x23, 23 * REGBYTES(sp)
	SREG x24, 24 * REGBYTES(sp)
	SREG x25, 25 * REGBYTES(sp)
	SREG x26, 26 * REGBYTES(sp)
	SREG x27, 27 * REGBYTES(sp)
	SREG x28, 28 * REGBYTES(sp)
	SREG x29, 29 * REGBYTES(sp)
	SREG x30, 30 * REGBYTES(sp)
	SREG x31, 31 * REGBYTES(sp)
	
	addi sp, sp, -32 * FREGBYTES
	FSREG ft0, 1 * FREGBYTES(sp)
	FSREG ft1, 2 * FREGBYTES(sp)
	FSREG ft2, 3 * FREGBYTES(sp)
	FSREG ft3, 4 * FREGBYTES(sp)
	FSREG ft4, 5 * FREGBYTES(sp)
	FSREG ft5, 6 * FREGBYTES(sp)
	FSREG ft6, 7 * FREGBYTES(sp)
	FSREG ft6, 8 * FREGBYTES(sp)
	FSREG ft7, 9 * FREGBYTES(sp)
	FSREG fa0, 10 * FREGBYTES(sp)
	FSREG fa1, 11 * FREGBYTES(sp)
	FSREG fa3, 12 * FREGBYTES(sp)
	FSREG fa4, 13 * FREGBYTES(sp)
	FSREG fa5, 14 * FREGBYTES(sp)
	FSREG fa6, 15 * FREGBYTES(sp)
	FSREG fa7, 16 * FREGBYTES(sp)
	FSREG ft8, 17 * FREGBYTES(sp)
	FSREG ft9, 18 * FREGBYTES(sp)
	FSREG ft10, 19 * FREGBYTES(sp)
	FSREG ft11, 20 * FREGBYTES(sp)

	csrr a0, MODE_PREFIX(cause)
	csrr a1, MODE_PREFIX(epc)
	csrr a2, MODE_PREFIX(tval)
	addi a3, sp, 32 * FREGBYTES
	jal handle_trap
	csrw MODE_PREFIX(epc), a0

	FLREG ft0, 1 * FREGBYTES(sp)
	FLREG ft1, 2 * FREGBYTES(sp)
	FLREG ft2, 3 * FREGBYTES(sp)
	FLREG ft3, 4 * FREGBYTES(sp)
	FLREG ft4, 5 * FREGBYTES(sp)
	FLREG ft5, 6 * FREGBYTES(sp)
	FLREG ft6, 7 * FREGBYTES(sp)
	FLREG ft6, 8 * FREGBYTES(sp)
	FLREG ft7, 9 * FREGBYTES(sp)
	FLREG fa0, 10 * FREGBYTES(sp)
	FLREG fa1, 11 * FREGBYTES(sp)
	FLREG fa3, 12 * FREGBYTES(sp)
	FLREG fa4, 13 * FREGBYTES(sp)
	FLREG fa5, 14 * FREGBYTES(sp)
	FLREG fa6, 15 * FREGBYTES(sp)
	FLREG fa7, 16 * FREGBYTES(sp)
	FLREG ft8, 17 * FREGBYTES(sp)
	FLREG ft9, 18 * FREGBYTES(sp)
	FLREG ft10, 19 * FREGBYTES(sp)
	FLREG ft11, 20 * FREGBYTES(sp)
	addi sp, sp, 32 * FREGBYTES

	LREG x1,   1 * REGBYTES(sp)
	LREG x3,   3 * REGBYTES(sp)
	LREG x4,   4 * REGBYTES(sp)
	LREG x5,   5 * REGBYTES(sp)
	LREG x6,   6 * REGBYTES(sp)
	LREG x7,   7 * REGBYTES(sp)
	LREG x8,   8 * REGBYTES(sp)
	LREG x9,   9 * REGBYTES(sp)
	LREG x10, 10 * REGBYTES(sp)
	LREG x11, 11 * REGBYTES(sp)
	LREG x12, 12 * REGBYTES(sp)
	LREG x13, 13 * REGBYTES(sp)
	LREG x14, 14 * REGBYTES(sp)
	LREG x15, 15 * REGBYTES(sp)
	LREG x16, 16 * REGBYTES(sp)
	LREG x17, 17 * REGBYTES(sp)
	LREG x18, 18 * REGBYTES(sp)
	LREG x19, 19 * REGBYTES(sp)
	LREG x20, 20 * REGBYTES(sp)
	LREG x21, 21 * REGBYTES(sp)
	LREG x22, 22 * REGBYTES(sp)
	LREG x23, 23 * REGBYTES(sp)
	LREG x24, 24 * REGBYTES(sp)
	LREG x25, 25 * REGBYTES(sp)
	LREG x26, 26 * REGBYTES(sp)
	LREG x27, 27 * REGBYTES(sp)
	LREG x28, 28 * REGBYTES(sp)
	LREG x29, 29 * REGBYTES(sp)
	LREG x30, 30 * REGBYTES(sp)
	LREG x31, 31 * REGBYTES(sp)
	LREG x2,   2 * REGBYTES(sp)
	addi sp, sp, 32 * REGBYTES
	# enable mie
	addi sp, sp, -1 * REGBYTES
	SREG t0,   0(sp)
	li      t0, MSTATUS_PRV1
	csrs    mstatus, t0
	LREG t0,   0(sp)
	addi sp, sp, 1 * REGBYTES
	MODE_PREFIX(ret)
