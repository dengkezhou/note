#include <common.h>
#include <asm/riscv/ptrace.h>
#include <asm/riscv/encoding.h>
#include <irq.h>
#include <sbi/sbi_ecall.h>


#if defined(CONFIG_PLIC) || defined(CONFIG_CLIC)

/**
 * instr_len() - get instruction length
 *
 * @i:    low 16 bits of the instruction
 * Return:  number of u16 in instruction
 */
static int instr_len(u16 i) {
  if ((i & 0x03) != 0x03)
    return 1;
  /* Instructions with more than 32 bits are not yet specified */
  return 2;
}

/**
 * show_code() - display code leading to exception
 *
 * @epc:  program counter
 */
static void show_code(ulong epc) {
  u16 *pos = (u16 *)(epc & ~1UL);
  int i, len = instr_len(*pos);

  printf("\nCode: ");
  for (i = -8; i; ++i)
    printf("%04x ", pos[i]);
  printf("(");
  for (i = 0; i < len; ++i)
    printf("%04x%s", pos[i], i + 1 == len ? ")\n" : " ");
}

static void show_regs(struct pt_regs *regs) {
  printf("\nSP:  " REG_FMT " GP:  " REG_FMT " TP:  " REG_FMT "\n", regs->sp,
         regs->gp, regs->tp);
  printf("T0:  " REG_FMT " T1:  " REG_FMT " T2:  " REG_FMT "\n", regs->t0,
         regs->t1, regs->t2);
  printf("S0:  " REG_FMT " S1:  " REG_FMT " A0:  " REG_FMT "\n", regs->s0,
         regs->s1, regs->a0);
  printf("A1:  " REG_FMT " A2:  " REG_FMT " A3:  " REG_FMT "\n", regs->a1,
         regs->a2, regs->a3);
  printf("A4:  " REG_FMT " A5:  " REG_FMT " A6:  " REG_FMT "\n", regs->a4,
         regs->a5, regs->a6);
  printf("A7:  " REG_FMT " S2:  " REG_FMT " S3:  " REG_FMT "\n", regs->a7,
         regs->s2, regs->s3);
  printf("S4:  " REG_FMT " S5:  " REG_FMT " S6:  " REG_FMT "\n", regs->s4,
         regs->s5, regs->s6);
  printf("S7:  " REG_FMT " S8:  " REG_FMT " S9:  " REG_FMT "\n", regs->s7,
         regs->s8, regs->s9);
  printf("S10: " REG_FMT " S11: " REG_FMT " T3:  " REG_FMT "\n", regs->s10,
         regs->s11, regs->t3);
  printf("T4:  " REG_FMT " T5:  " REG_FMT " T6:  " REG_FMT "\n", regs->t4,
         regs->t5, regs->t6);
}

static void enter_trap(unsigned long code, unsigned long epc,
                       unsigned long tval, struct pt_regs *regs) {
  static const char *const exception_code[] = {
      "Reserved",
      "Instruction access fault",
      "Illegal instruction",
      "Breakpoint",
      "Load address misaligned",
      "Load access fault",
      "Store/AMO address misaligned",
      "Store/AMO access fault",
      "Environment call from U-mode",
      "Environment call from S-mode",
      "Reserved",
      "Environment call from M-mode",
      "Instruction page fault",
      "Load page fault",
      "Reserved",
      "Store/AMO page fault",
  };

  if (code < ARRAY_SIZE(exception_code))
    printf("Unhandled exception: %s\n", exception_code[code]);
  else
    printf("Unhandled exception code: 0x%lx\n", code);

  printf("EPC: 0x%016lx RA: 0x%016lx TVAL: 0x%016lx\n", epc, regs->ra, tval);

  show_regs(regs);
  show_code(epc);

  for (;;)
    ;
}

#endif

#if defined(CONFIG_PLIC)
unsigned long handle_trap(unsigned long cause, unsigned long epc,
                          unsigned long tval, struct pt_regs *regs) {
  unsigned long is_irq, irq;

  is_irq     = (cause & MCAUSE_INT);
  irq        = (cause & ~MCAUSE_INT);
  regs->sepc = epc;

  if (is_irq) {
    switch (irq) {
    case IRQ_M_EXT:
    case IRQ_S_EXT:
      external_interrupt(regs); /* handle external interrupt */
      break;
    case IRQ_M_TIMER:
    case IRQ_S_TIMER:
      coret_interrupt(regs); /* handle timer interrupt */
      break;
    case IRQ_M_SOFT:
    case IRQ_S_SOFT:
      soft_interrupt(regs);
      break;
    default:
      enter_trap(cause, epc, tval, regs);
      break;
    };
  } else {
#ifdef CONFIG_LIB_SBI
    if (irq == CAUSE_USER_ECALL || irq == CAUSE_SUPERVISOR_ECALL ||
        irq == CAUSE_MACHINE_ECALL)
      sbi_ecall_handler(regs);
    else
#endif
      enter_trap(cause, epc, tval, regs);
  }

  return regs->sepc;
}
#elif defined(CONFIG_CLIC)
__attribute__((weak)) void nmi_interrupt(void *regs) {}

unsigned long handle_trap(unsigned long cause, unsigned long epc,
                          unsigned long tval, struct pt_regs *regs) {
  unsigned long is_irq, irq;

  is_irq = (cause & MCAUSE_INT);
  irq    = (cause & ~MCAUSE_INT);
  irq &= 0xfff;

  // printf("handle_trap: 0x%lx\n", cause);

  if (is_irq) {
    switch (irq) {
    case IRQ_M_TIMER:
#ifdef CONFIG_RISCV_SMODE
    case IRQ_S_TIMER:
#endif
    case IRQ_M_SOFT:
#ifdef CONFIG_RISCV_SMODE
    case IRQ_S_SOFT:
#endif
      external_interrupt(regs);
      break;
    default:
      if (irq >= 16 || irq == 11)
        external_interrupt(regs);
      break;
    };
  } else {
    if (irq == 24)
      nmi_interrupt(regs);
    else
      enter_trap(cause, epc, tval, regs);
  }

  return epc;
}
#else
unsigned long handle_trap(unsigned long cause, unsigned long epc,
                          unsigned long tval, struct pt_regs *regs) { return 0; }
#endif

__attribute__((weak)) void external_interrupt(void *regs) { asm_do_IRQ(regs); }

__attribute__((weak)) void coret_interrupt(void *regs) {}

__attribute__((weak)) void soft_interrupt(void *regs) {}
