#include <common.h>
#include <asm/riscv/csr.h>
#ifdef CONFIG_64BIT
#include <csi_rv64_gcc.h>
#else
#include <csi_rv32_gcc.h>
#endif
#include <pmu.h>

inline unsigned long hpm_get_count(int mode) {
	unsigned long v;	
  if (mode < RISCV_PMU_CYCLE || mode > RISCV_PMU_LSUSQDDC)
    return -1;
#ifdef CONFIG_RISCV_SMODE
	switch (mode) {
  case RISCV_PMU_CYCLE:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_CYCLE));
    break;
  case RISCV_PMU_TIME:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_TIME));
    break;
  case RISCV_PMU_INSTRET:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_INSTRET));
    break;
  case RISCV_PMU_L1ICAC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L1ICAC));
    break;
  case RISCV_PMU_L1ICMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L1ICMC));
    break;
  case RISCV_PMU_IUTLBMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_IUTLBMC));
    break;
  case RISCV_PMU_DUTLBMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_DUTLBMC));
    break;
  case RISCV_PMU_JTLBMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_JTLBMC));
    break;
  case RISCV_PMU_CBMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_CBMC));
    break;
  case RISCV_PMU_IBMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_IBMC));
    break;
  case RISCV_PMU_IBIC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_IBIC));
    break;
  case RISCV_PMU_LSUSFC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_LSUSFC));
    break;
  case RISCV_PMU_STC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_STC));
    break;
  case RISCV_PMU_L1DCRAC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L1DCRAC));
    break;
  case RISCV_PMU_L1DCRMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L1DCRMC));
    break;
  case RISCV_PMU_L1DCWAC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L1DCWAC));
    break;
  case RISCV_PMU_L1DCWMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L1DCWMC));
    break;
  case RISCV_PMU_L2CRAC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L2CRAC));
    break;
  case RISCV_PMU_L2CRMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L2CRMC));
    break;
  case RISCV_PMU_L2CWAC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L2CWAC));
    break;
  case RISCV_PMU_L2CWMC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_L2CWMC));
    break;
  case RISCV_PMU_RFLFC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_RFLFC));
    break;
  case RISCV_PMU_RFRLFC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_RFRLFC));
    break;
  case RISCV_PMU_RFIC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_RFIC));
    break;
  case RISCV_PMU_LSUC4SC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_LSUC4SC));
    break;
  case RISCV_PMU_LSUOSC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_LSUOSC));
    break;
  case RISCV_PMU_LSUSQDC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_LSUSQDC));
    break;
  case RISCV_PMU_LSUSQDDC:
    v = csr_read(CSR_SHPMCOUNTER(RISCV_PMU_LSUSQDDC));
    break;
  default:
    return -1;
  }
#else
  switch (mode) {
  case RISCV_PMU_CYCLE:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_CYCLE));
    break;
  case RISCV_PMU_TIME:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_TIME));
    break;
  case RISCV_PMU_INSTRET:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_INSTRET));
    break;
  case RISCV_PMU_L1ICAC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L1ICAC));
    break;
  case RISCV_PMU_L1ICMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L1ICMC));
    break;
  case RISCV_PMU_IUTLBMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_IUTLBMC));
    break;
  case RISCV_PMU_DUTLBMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_DUTLBMC));
    break;
  case RISCV_PMU_JTLBMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_JTLBMC));
    break;
  case RISCV_PMU_CBMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_CBMC));
    break;
  case RISCV_PMU_IBMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_IBMC));
    break;
  case RISCV_PMU_IBIC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_IBIC));
    break;
  case RISCV_PMU_LSUSFC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_LSUSFC));
    break;
  case RISCV_PMU_STC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_STC));
    break;
  case RISCV_PMU_L1DCRAC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L1DCRAC));
    break;
  case RISCV_PMU_L1DCRMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L1DCRMC));
    break;
  case RISCV_PMU_L1DCWAC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L1DCWAC));
    break;
  case RISCV_PMU_L1DCWMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L1DCWMC));
    break;
  case RISCV_PMU_L2CRAC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L2CRAC));
    break;
  case RISCV_PMU_L2CRMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L2CRMC));
    break;
  case RISCV_PMU_L2CWAC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L2CWAC));
    break;
  case RISCV_PMU_L2CWMC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_L2CWMC));
    break;
  case RISCV_PMU_RFLFC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_RFLFC));
    break;
  case RISCV_PMU_RFRLFC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_RFRLFC));
    break;
  case RISCV_PMU_RFIC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_RFIC));
    break;
  case RISCV_PMU_LSUC4SC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_LSUC4SC));
    break;
  case RISCV_PMU_LSUOSC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_LSUOSC));
    break;
  case RISCV_PMU_LSUSQDC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_LSUSQDC));
    break;
  case RISCV_PMU_LSUSQDDC:
    v = csr_read(CSR_MHPMCOUNTER(RISCV_PMU_LSUSQDDC));
    break;
  default:
    return -1;
  }
#endif
	return v;
}

int hpm_set_count(int mode, unsigned long value) {
  if (mode < RISCV_PMU_CYCLE || mode > RISCV_PMU_LSUSQDDC)
    return -1;

  switch (mode) {
  case RISCV_PMU_CYCLE:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_CYCLE), value);
    break;
  case RISCV_PMU_TIME:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_TIME), value);
    break;
  case RISCV_PMU_INSTRET:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_INSTRET), value);
    break;
  case RISCV_PMU_L1ICAC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L1ICAC), value);
    break;
  case RISCV_PMU_L1ICMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L1ICMC), value);
    break;
  case RISCV_PMU_IUTLBMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_IUTLBMC), value);
    break;
  case RISCV_PMU_DUTLBMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_DUTLBMC), value);
    break;
  case RISCV_PMU_JTLBMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_JTLBMC), value);
    break;
  case RISCV_PMU_CBMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_CBMC), value);
    break;
  case RISCV_PMU_IBMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_IBMC), value);
    break;
  case RISCV_PMU_IBIC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_IBIC), value);
    break;
  case RISCV_PMU_LSUSFC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_LSUSFC), value);
    break;
  case RISCV_PMU_STC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_STC), value);
    break;
  case RISCV_PMU_L1DCRAC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L1DCRAC), value);
    break;
  case RISCV_PMU_L1DCRMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L1DCRMC), value);
    break;
  case RISCV_PMU_L1DCWAC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L1DCWAC), value);
    break;
  case RISCV_PMU_L1DCWMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L1DCWMC), value);
    break;
  case RISCV_PMU_L2CRAC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L2CRAC), value);
    break;
  case RISCV_PMU_L2CRMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L2CRMC), value);
    break;
  case RISCV_PMU_L2CWAC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L2CWAC), value);
    break;
  case RISCV_PMU_L2CWMC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_L2CWMC), value);
    break;
  case RISCV_PMU_RFLFC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_RFLFC), value);
    break;
  case RISCV_PMU_RFRLFC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_RFRLFC), value);
    break;
  case RISCV_PMU_RFIC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_RFIC), value);
    break;
  case RISCV_PMU_LSUC4SC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_LSUC4SC), value);
    break;
  case RISCV_PMU_LSUOSC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_LSUOSC), value);
    break;
  case RISCV_PMU_LSUSQDC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_LSUSQDC), value);
    break;
  case RISCV_PMU_LSUSQDDC:
    csr_write(CSR_MHPMCOUNTER(RISCV_PMU_LSUSQDDC), value);
    break;
  default:
    return -1;
  }
  return 0;
}

int hpm_set_event(int mode, uint64_t value) {
  if (mode < RISCV_PMU_L1ICAC || mode > RISCV_PMU_LSUSQDDC)
    return -1;

  switch (mode) {
  case RISCV_PMU_L1ICAC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L1ICAC), value);
    break;
  case RISCV_PMU_L1ICMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L1ICMC), value);
    break;
  case RISCV_PMU_IUTLBMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_IUTLBMC), value);
    break;
  case RISCV_PMU_DUTLBMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_DUTLBMC), value);
    break;
  case RISCV_PMU_JTLBMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_JTLBMC), value);
    break;
  case RISCV_PMU_CBMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_CBMC), value);
    break;
  case RISCV_PMU_IBMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_IBMC), value);
    break;
  case RISCV_PMU_IBIC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_IBIC), value);
    break;
  case RISCV_PMU_LSUSFC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_LSUSFC), value);
    break;
  case RISCV_PMU_STC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_STC), value);
    break;
  case RISCV_PMU_L1DCRAC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L1DCRAC), value);
    break;
  case RISCV_PMU_L1DCRMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L1DCRMC), value);
    break;
  case RISCV_PMU_L1DCWAC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L1DCWAC), value);
    break;
  case RISCV_PMU_L1DCWMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L1DCWMC), value);
    break;
  case RISCV_PMU_L2CRAC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L2CRAC), value);
    break;
  case RISCV_PMU_L2CRMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L2CRMC), value);
    break;
  case RISCV_PMU_L2CWAC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L2CWAC), value);
    break;
  case RISCV_PMU_L2CWMC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_L2CWMC), value);
    break;
  case RISCV_PMU_RFLFC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_RFLFC), value);
    break;
  case RISCV_PMU_RFRLFC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_RFRLFC), value);
    break;
  case RISCV_PMU_RFIC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_RFIC), value);
    break;
  case RISCV_PMU_LSUC4SC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_LSUC4SC), value);
    break;
  case RISCV_PMU_LSUOSC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_LSUOSC), value);
    break;
  case RISCV_PMU_LSUSQDC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_LSUSQDC), value);
    break;
  case RISCV_PMU_LSUSQDDC:
    csr_write(CSR_MHPMEVENT(RISCV_PMU_LSUSQDDC), value);
    break;
  default:
    return -1;
  }
  return 0;
}

void hpm_init(void) {
  int i;

  __disable_hpm();

  for (i = RISCV_PMU_CYCLE; i <= RISCV_PMU_LSUSQDDC; i++) {
    // enable hpmevent
    if (i >= RISCV_PMU_L1ICAC)
      hpm_set_event(i, i - RISCV_PMU_L1ICAC + 1);

		// init hpmcountn zero, mcycle, minstret
    if (i != RISCV_PMU_TIME)
      hpm_set_count(i, 0);
  }

  __enable_hpm();
}

void hpm_deinit(void) { __disable_hpm(); }
