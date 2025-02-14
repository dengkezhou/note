/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_ECALL_H__
#define __SBI_ECALL_H__

#include <common.h>
#include <linux/list.h>
#include <asm/riscv/ptrace.h>

#define SBI_ECALL_VERSION_MAJOR		1
#define SBI_ECALL_VERSION_MINOR		0
#define SBI_OPENSBI_IMPID		1

struct sbi_trap_info {
	/** epc Trap program counter */
	unsigned long epc;
	/** cause Trap exception cause */
	unsigned long cause;
	/** tval Trap value */
	unsigned long tval;
	/** tval2 Trap value 2 */
	unsigned long tval2;
	/** tinst Trap instruction */
	unsigned long tinst;
	/** gva Guest virtual address in tval flag */
	unsigned long gva;
};

struct sbi_ecall_extension {
	struct list_head head;
	unsigned long extid_start;
	unsigned long extid_end;
	int (* probe)(unsigned long extid, unsigned long *out_val);
	int (* handle)(unsigned long extid, unsigned long funcid,
		       const struct pt_regs *regs,
		       unsigned long *out_val,
		       struct sbi_trap_info *out_trap);
};

u16 sbi_ecall_version_major(void);

u16 sbi_ecall_version_minor(void);

unsigned long sbi_ecall_get_impid(void);

void sbi_ecall_set_impid(unsigned long impid);

struct sbi_ecall_extension *sbi_ecall_find_extension(unsigned long extid);

int sbi_ecall_register_extension(struct sbi_ecall_extension *ext);

void sbi_ecall_unregister_extension(struct sbi_ecall_extension *ext);

int sbi_ecall_handler(struct pt_regs *regs);

void sbi_ecall_init(void);

#endif
