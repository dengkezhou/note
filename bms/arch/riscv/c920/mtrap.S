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
#include <generated/autoconf.h>
#include <asm/riscv/encoding.h>

#ifdef CONFIG_32BIT
#define LREG		lw
#define SREG		sw
#define REGBYTES	4
#else
#define LREG		ld
#define SREG		sd
#define FLREG		fld
#define FSREG		fsd
#define REGBYTES	8
#endif

/* Enable interrupts when returning from the handler */
#define MSTATUS_PRV1 0x1880

	.text

	/* trap entry */
	.align 2
	.global mtrap_entry
mtrap_entry:
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
	
	addi sp, sp, -32 * REGBYTES
	FSREG ft0, 1 * REGBYTES(sp)
	FSREG ft1, 2 * REGBYTES(sp)
	FSREG ft2, 3 * REGBYTES(sp)
	FSREG ft3, 4 * REGBYTES(sp)
	FSREG ft4, 5 * REGBYTES(sp)
	FSREG ft5, 6 * REGBYTES(sp)
	FSREG ft6, 7 * REGBYTES(sp)
	FSREG ft6, 8 * REGBYTES(sp)
	FSREG ft7, 9 * REGBYTES(sp)
	FSREG fa0, 10 * REGBYTES(sp)
	FSREG fa1, 11 * REGBYTES(sp)
	FSREG fa3, 12 * REGBYTES(sp)
	FSREG fa4, 13 * REGBYTES(sp)
	FSREG fa5, 14 * REGBYTES(sp)
	FSREG fa6, 15 * REGBYTES(sp)
	FSREG fa7, 16 * REGBYTES(sp)
	FSREG ft8, 17 * REGBYTES(sp)
	FSREG ft9, 18 * REGBYTES(sp)
	FSREG ft10, 19 * REGBYTES(sp)
	FSREG ft11, 20 * REGBYTES(sp)

	csrr a0, mcause
	csrr a1, mepc
	csrr a2, mtval
	addi a3, sp, 32 * REGBYTES
	jal handle_trap
	csrw mepc, a0

	FLREG ft0, 1 * REGBYTES(sp)
	FLREG ft1, 2 * REGBYTES(sp)
	FLREG ft2, 3 * REGBYTES(sp)
	FLREG ft3, 4 * REGBYTES(sp)
	FLREG ft4, 5 * REGBYTES(sp)
	FLREG ft5, 6 * REGBYTES(sp)
	FLREG ft6, 7 * REGBYTES(sp)
	FLREG ft6, 8 * REGBYTES(sp)
	FLREG ft7, 9 * REGBYTES(sp)
	FLREG fa0, 10 * REGBYTES(sp)
	FLREG fa1, 11 * REGBYTES(sp)
	FLREG fa3, 12 * REGBYTES(sp)
	FLREG fa4, 13 * REGBYTES(sp)
	FLREG fa5, 14 * REGBYTES(sp)
	FLREG fa6, 15 * REGBYTES(sp)
	FLREG fa7, 16 * REGBYTES(sp)
	FLREG ft8, 17 * REGBYTES(sp)
	FLREG ft9, 18 * REGBYTES(sp)
	FLREG ft10, 19 * REGBYTES(sp)
	FLREG ft11, 20 * REGBYTES(sp)
	addi sp, sp, 32 * REGBYTES

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

	mret

#ifdef CONFIG_RISCV_SMODE
	/* trap entry */
	.align 2
	.global strap_entry
strap_entry:
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
	
	addi sp, sp, -32 * REGBYTES
	FSREG ft0, 1 * REGBYTES(sp)
	FSREG ft1, 2 * REGBYTES(sp)
	FSREG ft2, 3 * REGBYTES(sp)
	FSREG ft3, 4 * REGBYTES(sp)
	FSREG ft4, 5 * REGBYTES(sp)
	FSREG ft5, 6 * REGBYTES(sp)
	FSREG ft6, 7 * REGBYTES(sp)
	FSREG ft6, 8 * REGBYTES(sp)
	FSREG ft7, 9 * REGBYTES(sp)
	FSREG fa0, 10 * REGBYTES(sp)
	FSREG fa1, 11 * REGBYTES(sp)
	FSREG fa3, 12 * REGBYTES(sp)
	FSREG fa4, 13 * REGBYTES(sp)
	FSREG fa5, 14 * REGBYTES(sp)
	FSREG fa6, 15 * REGBYTES(sp)
	FSREG fa7, 16 * REGBYTES(sp)
	FSREG ft8, 17 * REGBYTES(sp)
	FSREG ft9, 18 * REGBYTES(sp)
	FSREG ft10, 19 * REGBYTES(sp)
	FSREG ft11, 20 * REGBYTES(sp)

	csrr a0, scause
	csrr a1, sepc
	csrr a2, stval
	addi a3, sp, 32 * REGBYTES
	jal handle_trap
	csrw sepc, a0

	FLREG ft0, 1 * REGBYTES(sp)
	FLREG ft1, 2 * REGBYTES(sp)
	FLREG ft2, 3 * REGBYTES(sp)
	FLREG ft3, 4 * REGBYTES(sp)
	FLREG ft4, 5 * REGBYTES(sp)
	FLREG ft5, 6 * REGBYTES(sp)
	FLREG ft6, 7 * REGBYTES(sp)
	FLREG ft6, 8 * REGBYTES(sp)
	FLREG ft7, 9 * REGBYTES(sp)
	FLREG fa0, 10 * REGBYTES(sp)
	FLREG fa1, 11 * REGBYTES(sp)
	FLREG fa3, 12 * REGBYTES(sp)
	FLREG fa4, 13 * REGBYTES(sp)
	FLREG fa5, 14 * REGBYTES(sp)
	FLREG fa6, 15 * REGBYTES(sp)
	FLREG fa7, 16 * REGBYTES(sp)
	FLREG ft8, 17 * REGBYTES(sp)
	FLREG ft9, 18 * REGBYTES(sp)
	FLREG ft10, 19 * REGBYTES(sp)
	FLREG ft11, 20 * REGBYTES(sp)
	addi sp, sp, 32 * REGBYTES

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
	sret
#endif
