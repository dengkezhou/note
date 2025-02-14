/***********************************************************************
 * copyright (C) 2014 Cadence Design Systems
 * All rights reserved.
 ***********************************************************************
 * @file           $RCSfile: $
 * @project        $Name:  $
 * @version        $Revision: $
 * @author         kswitala@cadence.com
 * @date           $Date: $
 * @desc           Clock generator header file
 ***********************************************************************/

#ifndef _PERF_CLK_GEN_H_
  #define _PERF_CLK_GEN_H_
  #include <common.h>
  #include <stdint.h>

  #define CLKGEN_BASEADDR  0x70000000

  #define CLKGEN_REG_CTRL       (CLKGEN_BASEADDR + 0x00)
  #define CLKGEN_REG_PERIOD_C0  (CLKGEN_BASEADDR + 0x10)
  #define CLKGEN_REG_PERIOD_C1  (CLKGEN_BASEADDR + 0x14)
  #define CLKGEN_REG_PERIOD_C2  (CLKGEN_BASEADDR + 0x18)
  #define CLKGEN_REG_PERIOD_C3  (CLKGEN_BASEADDR + 0x1C)

  void clkgen_change(uint32_t freq_kHz, uint8_t clk_sel );
  void clkgen_enable(uint8_t enable_vect);
  void clkgen_disable(uint8_t disable_vect);
  uint32_t clkgen_get(uint8_t clk_sel);

#endif /* _PERF_CLK_GEN_H_ */
