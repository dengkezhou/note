#ifndef __ISA_RV64G_H__
#define __ISA_RV64G_H__

#include "jrx_base.h"

enum { RV_OPIVV, RV_OPFVV, RV_OPMVV, RV_OPIVI, RV_OPIVX, RV_OPFVF, RV_OPMVX };
enum {
  RV_SEW8,
  RV_SEW16,
  RV_SEW32,
  RV_SEW64,
  RV_SEW128,
};
enum {
  RV_LMUL_1,
  RV_LMUL_2,
  RV_LMUL_4,
  RV_LMUL_8,
  RV_LMUL_F8 = 5,
  RV_LMUL_F4,
  RV_LMUL_F2,
};
enum { RV_VMVR_1, RV_VMVR_2, RV_VMVR_4, RV_VMVR_8 };
enum { RV_LOAD, RV_STORE };

typedef jrx_base_t isa_rv64g_t;
extern instruction_ops_t isa_rv64g;

isa_rv64g_t *initIsaRV64g(int size, uint8_t *c, int *slots, uint8_t *d);
void exitIsaRV64g(isa_rv64g_t *dev);
#endif
