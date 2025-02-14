/*
 * (C) Copyright 2003
 * Texas Instruments <www.ti.com>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002-2004
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2004
 * Philippe Robin, ARM Ltd. <philippe.robin@arm.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

void bad_mode(void) {
  panic("Resetting CPU ...\n");
  while (1)
    ;
}

void __show_regs(void *regs) {
#if 0  
	int i;

	printf("CPU: %d    %s  (%s %.*s)\n",
		raw_smp_processor_id(), print_tainted(),
		init_utsname()->release,
		(int)strcspn(init_utsname()->version, " "),
		init_utsname()->version);
	print_symbol("PC is at %s\n", instruction_pointer(regs));
	print_symbol("LR is at %s\n", regs->regs[30]);
	printf("pc : [<%016llx>] lr : [<%016llx>] pstate: %08llx\n",
	       regs->pc, regs->regs[30], regs->pstate);
	printf("sp : %016llx\n", regs->sp);
	for (i = 29; i >= 0; i--) {
		printf("x%-2d: %016llx ", i, regs->regs[i]);
		if (i % 2 == 0)
			printf("\n");
	}
	printf("\n");
#endif
}

void show_regs(void *regs) {
#if 0
	printf("\n");
	printf("Pid: %d, comm: %20s\n", task_pid_nr(current), current->comm);
	__show_regs(regs);
#endif
}

void do_undefined_instruction(void *pt_regs) {
  printf("undefined instruction\n");
  show_regs(pt_regs);
  bad_mode();
}

void do_software_interrupt(void *pt_regs) {
  printf("software interrupt\n");
  show_regs(pt_regs);
  bad_mode();
}

void do_prefetch_abort(void *pt_regs) {
  printf("prefetch abort\n");
  show_regs(pt_regs);
  bad_mode();
}

void do_data_abort(void *pt_regs) {
  printf("data abort\n");
  show_regs(pt_regs);
  bad_mode();
}

void do_not_used(void *pt_regs) {
  printf("not used\n");
  show_regs(pt_regs);
  bad_mode();
}

void do_fiq(void *pt_regs) {
  printf("fast interrupt request\n");
  show_regs(pt_regs);
  bad_mode();
}
