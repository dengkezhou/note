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

	addi sp, sp, -16 * REGBYTES
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

	csrr a0, MODE_PREFIX(cause)
	csrr a1, MODE_PREFIX(epc)
	csrr a2, MODE_PREFIX(tval)
	addi a3, sp, 32 * FREGBYTES
	jal handle_trap
	csrw MODE_PREFIX(epc), a0

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
	LREG x2,   2 * REGBYTES(sp)
	addi sp, sp, 16 * REGBYTES
	# enable mie
	addi sp, sp, -1 * REGBYTES
	SREG t0,   0(sp)
	li      t0, MSTATUS_PRV1
	csrs    mstatus, t0
	LREG t0,   0(sp)
	addi sp, sp, 1 * REGBYTES
	MODE_PREFIX(ret)
