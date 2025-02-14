#ifndef __ISA_H__
#define __ISA_H__

#include <isa-a64.h>
#include <isa-rv64g.h>
#include <isa-rxa.h>

enum { ISA_A64, ISA_RV64G, ISA_RXA };

void *initIsa(int mode, int size, uint8_t *c, int *slots, uint8_t *d);
void exitIsa(int mode, void *data);
#endif
