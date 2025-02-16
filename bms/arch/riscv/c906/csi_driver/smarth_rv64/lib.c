/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     lib.c
 * @brief    source file for the lib
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <csi_config.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "soc.h"
#include "csi_core.h" //for test
#include "drv_usart.h"

extern uint64_t csi_coret_get_load(void);
extern uint64_t csi_coret_get_value(void);
extern uint32_t csi_coret_get_valueh(void);

extern int32_t csi_usart_putchar(usart_handle_t handle, uint8_t ch);
extern int32_t csi_usart_getchar(usart_handle_t handle, uint8_t *ch);

static void _mdelay(void) {
  unsigned long long start, cur, delta;
  uint32_t startl = csi_coret_get_value();
  uint32_t starth = csi_coret_get_valueh();
  uint32_t curl, curh;
  uint32_t cnt = (drv_get_sys_freq() / 1000);
  start        = ((unsigned long long)starth << 32) | startl;

  while (1) {
    curl  = csi_coret_get_value();
    curh  = csi_coret_get_valueh();
    cur   = ((unsigned long long)curh << 32) | curl;
    delta = cur - start;

    if (delta >= cnt) {
      return;
    }
  }
}

void mdelay(uint32_t ms) {
  if (ms == 0) {
    return;
  }

  while (ms--) {
    _mdelay();
  }
}
