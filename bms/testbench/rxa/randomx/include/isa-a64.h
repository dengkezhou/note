#ifndef __ISA_A64_H__
#define __ISA_A64_H__

#include "jrx_base.h"

typedef jrx_base_t isa_a64_t;
extern instruction_ops_t isa_a64;

isa_a64_t *initIsaA64(int size, uint8_t *c, int *slots, uint8_t *d);
void exitIsaA64(isa_a64_t *dev);
#endif
