#ifndef __JRX_H__
#define __JRX_H__

#include "isa.h"

typedef struct jrx_dev {
  jrx_data_t data;
  int literal_pos;
  int loop_start;
  int loop_start_t0;
  int load_start;
  int loop_end;
  int prefetch_start;
  uint8_t *code;
  int dst_change[256];
  int slots[576];
  int mode;
  void *p0, *p1, *p2, *p3, *p4, *p5, *p6;
} jrx_dev_t;
#endif
