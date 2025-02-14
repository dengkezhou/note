/***********************************************************************
 * copyright (C) 2014 Cadence Design Systems
 * All rights reserved.
 ***********************************************************************
 * @file           $RCSfile: $
 * @project        $Name:  $
 * @version        $Revision: $
 * @author         kswitala@cadence.com
 * @date           $Date: $
 * @desc           Clock generator functions
 ***********************************************************************/

#include "clk_generator.h"
#include "sw_hw_wrapper.h"

#if (USE_SIM == 1)

  void clkgen_change(uint32_t freq_kHz, uint8_t clk_sel ) {
    IOWR_32(CLKGEN_REG_PERIOD_C0 + (4*clk_sel), 1000000000  / freq_kHz);   // period in ps
  }

  void clkgen_enable(uint8_t enable_vect) {
    uint32_t _status;

    _status = IORD_32(CLKGEN_REG_CTRL);
    _status |= enable_vect;
    IOWR_32(CLKGEN_REG_CTRL, _status);
  }

  void clkgen_disable(uint8_t disable_vect) {
    uint32_t _status;

    _status = IORD_32(CLKGEN_REG_CTRL);
    _status &= ~(disable_vect);
    IOWR_32(CLKGEN_REG_CTRL, _status);
  }

  uint32_t clkgen_get(uint8_t clk_sel) {
    return IORD_32(CLKGEN_REG_PERIOD_C0 + (4*clk_sel)); // returns period in ps
  }

#else
  void clkgen_change(uint32_t freq_kHz, uint8_t clk_sel ) {
    /* Put your implementation of set clock frequency function */
  }

  void clkgen_enable(uint8_t enable_vect) {
    /* Put your implementation of clock enable function */
  }

  void clkgen_disable(uint8_t disable_vect) {
    /* Put your implementation of clock disable function */
  }

  uint32_t clkgen_get(uint8_t clk_sel) {
    /* Put your implementation of clock disable function */
  }
#endif

