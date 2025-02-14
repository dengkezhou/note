#ifndef __PMU_H__
#define __PMU_H__

#define RISCV_PMU_CYCLE   0
#define RISCV_PMU_TIME    1
#define RISCV_PMU_INSTRET 2
#define RISCV_PMU_L1ICAC  3 /* ICache Access */
#define RISCV_PMU_L1ICMC  4 /* ICache Miss */
#define RISCV_PMU_IUTLBMC 5 /* I-UTLB Miss */
#define RISCV_PMU_DUTLBMC 6 /* D-UTLB Miss */
#define RISCV_PMU_JTLBMC  7 /* JTLB Miss Counter */

#define RISCV_PMU_CBMC   8  /* Cond-br-mispredict */
#define RISCV_PMU_IBMC   10 /* Indirect Branch Mispredict */
#define RISCV_PMU_IBIC   11 /* Indirect Branch Instruction */
#define RISCV_PMU_LSUSFC 12 /* LSU Spec Fail */
#define RISCV_PMU_STC    13 /* Store Instruction */

#define RISCV_PMU_L1DCRAC 14 /* L1 DCache Read Access */
#define RISCV_PMU_L1DCRMC 15 /* L1 DCache Read Miss */
#define RISCV_PMU_L1DCWAC 16 /* L1 DCache Write Access */
#define RISCV_PMU_L1DCWMC 17 /* L1 DCache Write Miss */

#define RISCV_PMU_L2CRAC 18 /* L2 Cache Read Access */
#define RISCV_PMU_L2CRMC 19 /* L2 Cache Read Miss */
#define RISCV_PMU_L2CWAC 20 /* L2 Cache Write Access */
#define RISCV_PMU_L2CWMC 21 /* L2 Cache Write Miss */

#define RISCV_PMU_RFLFC  22 /* RF Launch Fail */
#define RISCV_PMU_RFRLFC 23 /* RF Reg Launch Fail */
#define RISCV_PMU_RFIC   24 /* RF Instruction */

#define RISCV_PMU_LSUC4SC  25 /* LSU Cross 4K Stall */
#define RISCV_PMU_LSUOSC   26 /* LSU Other Stall */
#define RISCV_PMU_LSUSQDC  27 /* LSU SQ Discard */
#define RISCV_PMU_LSUSQDDC 28 /* LSU SQ Data Discard */

#define CSR_MCYCLE         0xb00
#define CSR_MTIME          0xb01
#define CSR_MINSTRET       0xb02
#define CSR_MHPMCOUNTER(n) (0xb00 + n)
#define CSR_SHPMCOUNTER(n) (0xc00 + n)
#define CSR_MHPMCOUNTER3   0xb03
#define CSR_MHPMCOUNTER4   0xb04
#define CSR_MHPMCOUNTER5   0xb05
#define CSR_MHPMCOUNTER6   0xb06
#define CSR_MHPMCOUNTER7   0xb07
#define CSR_MHPMCOUNTER8   0xb08
#define CSR_MHPMCOUNTER9   0xb09
#define CSR_MHPMCOUNTER10  0xb0a
#define CSR_MHPMCOUNTER11  0xb0b
#define CSR_MHPMCOUNTER12  0xb0c
#define CSR_MHPMCOUNTER13  0xb0d
#define CSR_MHPMCOUNTER14  0xb0e
#define CSR_MHPMCOUNTER15  0xb0f
#define CSR_MHPMCOUNTER16  0xb10
#define CSR_MHPMCOUNTER17  0xb11
#define CSR_MHPMCOUNTER18  0xb12
#define CSR_MHPMCOUNTER19  0xb13
#define CSR_MHPMCOUNTER20  0xb14
#define CSR_MHPMCOUNTER21  0xb15
#define CSR_MHPMCOUNTER22  0xb16
#define CSR_MHPMCOUNTER23  0xb17
#define CSR_MHPMCOUNTER24  0xb18
#define CSR_MHPMCOUNTER25  0xb19
#define CSR_MHPMCOUNTER26  0xb1a
#define CSR_MHPMCOUNTER27  0xb1b
#define CSR_MHPMCOUNTER28  0xb1c
#define CSR_MHPMCOUNTER29  0xb1d
#define CSR_MHPMCOUNTER30  0xb1e
#define CSR_MHPMCOUNTER31  0xb1f
#define CSR_MHPMEVENT(n)   (0x320 + n)
#define CSR_MHPMEVENT3     0x323
#define CSR_MHPMEVENT4     0x324
#define CSR_MHPMEVENT5     0x325
#define CSR_MHPMEVENT6     0x326
#define CSR_MHPMEVENT7     0x327
#define CSR_MHPMEVENT8     0x328
#define CSR_MHPMEVENT9     0x329
#define CSR_MHPMEVENT10    0x32a
#define CSR_MHPMEVENT11    0x32b
#define CSR_MHPMEVENT12    0x32c
#define CSR_MHPMEVENT13    0x32d
#define CSR_MHPMEVENT14    0x32e
#define CSR_MHPMEVENT15    0x32f
#define CSR_MHPMEVENT16    0x330
#define CSR_MHPMEVENT17    0x331
#define CSR_MHPMEVENT18    0x332
#define CSR_MHPMEVENT19    0x333
#define CSR_MHPMEVENT20    0x334
#define CSR_MHPMEVENT21    0x335
#define CSR_MHPMEVENT22    0x336
#define CSR_MHPMEVENT23    0x337
#define CSR_MHPMEVENT24    0x338
#define CSR_MHPMEVENT25    0x339
#define CSR_MHPMEVENT26    0x33a
#define CSR_MHPMEVENT27    0x33b
#define CSR_MHPMEVENT28    0x33c
#define CSR_MHPMEVENT29    0x33d
#define CSR_MHPMEVENT30    0x33e
#define CSR_MHPMEVENT31    0x33f

enum {
	M_MODE,
	S_MODE,
	U_MODE
};

void hpm_init(void);
unsigned long hpm_get_count(int mode);
int hpm_set_count(int mode, unsigned long value);
void hpm_deinit(void);

#endif
