#ifndef __ISA_RXA_H__
#define __ISA_RXA_H__

#include "jrx_base.h"
#include "rxa.h"
#include <program.h>

#define MAX_ISA 512

#define GEN_REG_XPOOL 18
#define DEV_REG_XPOOL 32
#define TOT_REG_XPOOL (GEN_REG_XPOOL + DEV_REG_XPOOL)

enum {
  RXA_LSU,
	RXA_ALU,
  RXA_VAU,
  RXA_VDV,
  RXA_VMU,
  RXA_VSQ,
  RXA_RXU,
  RXA_NONE,
  RXA_CIPHER,
  RXA_UNIT_MAX
};

enum {
  RXA_NORMAL = (1 << 0),
  RXA_VREG   = (1 << 1),
  RXA_XREG   = (1 << 2),
  RXA_MEM    = (1 << 3),
  RXA_FRM    = (1 << 4),
  RXA_JMP    = (1 << 5),
};

enum { RXA_GEN_REG_XPOOL, RXA_DEV_REG_XPOOL, RXA_TEMP_XPOOL };

enum {
	INTEGER,
	FLOAT,
	FIXED,
};

typedef struct isa_con {
  int op;
  char *name;
  int unit;
	int type;
} isa_con_t;

#define ISACON(_name, _unit, _type)                                    \
  [RXA_ISA_##_name] = {                                                        \
      .op     = RXA_ISA_##_name,                                               \
      .name   = #_name,                                                        \
      .unit   = _unit,                                                         \
		  .type   = _type,                                                         \
  }

typedef struct isa {
  uint32_t code;
  int16_t nid;
  int16_t step;
  int8_t fstepEnd;
  isa_con_t *con;
  struct isa *srcDep[2];
} isa_t;

typedef struct ofo_flag {
  uint8_t unit[RXA_MAX];
  uint8_t len[FIXED + 1];
	uint16_t isa_id[8];
  uint8_t mask[32];
} ofo_flag_t;

typedef struct param {
  int mask_steps;
  int fetch_width;
  int valid_width;
  int unit[RXA_UNIT_MAX];
} param_t;

typedef struct ofo {
  // isa input
  isa_t isa[MAX_ISA];
  int len;
  // unit flags
  ofo_flag_t uflags[MAX_ISA];
  int latest_step;
  // for dep
  isa_t dfdep[jmp + 1];
  isa_t *rdep[jmp + 1];
  // for jump
  uint16_t jumpId[64];
  int jlen;
  // finish
  bool finish;
} ofo_t;

#define getOP(code) (code & 0x7f)
#define getRD(code) ((code >> 7) & 0x1f)
#define getRS(code) ((code >> 12) & 0x1f)
#define getP0(code) ((code >> 17) & 0x1f)
#define getP1(code) ((code >> 22) & 0x3ff)

//#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define Check(x)      (op == x)
#define Max(a, b)     ((a > b) ? a : b)
#define Min(a, b)     ((a < b) ? a : b)
#define M(x)          dev->M[x]
#define O(x)          ofo->x
#define I(x)          isa->x
#define P(x)          param.x
#define F(x)          flags->x
#define N(x)          con->x
#define IsVreg(x)     ((x >= a0) ? (dev->M[x] + v0) : dev->M[x])
#define IsV(x)        (x >= a0)

extern param_t param;

typedef jrx_base_t isa_rxa_t;

isa_rxa_t *initIsaRxa(int size, uint8_t *c, int *slots, uint8_t *d);
void exitIsaRxa(isa_rxa_t *dev);

void R_ld(void *isa, int rd, int rs, int mask, int offs);
void R_st(void *isa, int rd, int rs, int mask, int offs);
void R_vld(void *isa, int rd, int rs, int mask, int offs);
void R_vldp(void *isa, int rd, int rd1, int rs, int mask, int offs);
void R_vldq_xor(void *isa, int rd, int rs, int mask, int offs);
void R_vstq(void *isa, int rd, int rs, int mask, int offs);
void R_vld_w(void *isa, int rd, int rs, int mask, int offs);
void R_vldq_w(void *isa, int rd, int rs, int mask, int offs);
void R_prfc(void *isa, int rd, int rs, int mask, int offs);
void R_wprfc(void *isa, int rs);
void R_xor(void *isa, int rd, int rs, int flh);
void R_ror(void *isa, int rd, int rs, int shift);
void R_rori(void *isa, int rd, int shift);
void R_swap(void *isa, int rd, int rs);
void R_addsl(void *isa, int rd, int rs, int flh, int shift);
void R_addi(void *isa, int rd, int rs, int imm);
void R_add(void *isa, int rd, int rs, int flh, int rs2);
void R_sub(void *isa, int rd, int rs, int flh, int rs2);
void R_mul(void *isa, int rd, int rs, int flh, int rs2);
void R_mulh(void *isa, int rd, int rs, int rs2);
void R_mulhu(void *isa, int rd, int rs, int rs2);
void R_mov(void *isa, int rd, int rs);
void R_vxor(void *isa, int rd, int rs, int rs2);
void R_vswap(void *isa, int rd);
void R_vadd_d(void *isa, int rd, int rs, int rs2);
void R_vsub_d(void *isa, int rd, int rs, int rs2);
void R_vmul_d(void *isa, int rd, int rs, int rs2);
void R_vdiv_d(void *isa, int rd, int rs, int rs2);
void R_vsqrt_d(void *isa, int rd, int rs);
void R_vcvt_d_w(void *isa, int rd, int rs, int e);
void R_rxsfrm(void *isa, int rs, int imm);
void R_rxssp(void *isa, int rd1, int rs, int rd2);
void R_rxsmxa(void *isa, int rd);
void R_rxb(void *isa, int rd, int rs, int sl, int offs);
void R_brk(void *isa);
void R_bgt(void *isa, int rd, int rs, int flh, int offs);
void R_end(void *isa);
void R_nop(void *isa);
void R_li(void *isa, int rd, int imm);
void R_neg(void *isa, int rd);
void R_link(isa_rxa_t *base, isa_rxa_t *isa, int offs);
void R_rxblk2b(void *isa, int index);
void R_rxaes1rx4(void *isa, int index, int mode);
void R_rxaes4rx4(void *isa, int index);

//#define OUT_OF_ORDER  1
#ifdef OUT_OF_ORDER
#define isaSize(base)		codeSize(base)
#else
#define isaSize(base)		((ofo_t *)base->ofo)->len * 4
#endif

void cfg_literPool(void *isa, void *pdata);
int set_literalPool(void *isa, int dst, uint64_t data);
void dump_isa(isa_rxa_t *dev);

ofo_t *ofo_init(void);
void ofo_exit(ofo_t *ofo);
void ofo_reset(ofo_t *ofo);

rxaX_t *rxaAllocX(jrx_base_t *base, int mode);
rxaX_t *rxaResvX(jrx_base_t *base, int mode, int prio);
void set_resvLiteralPool(void *isa, rxaX_t *dev, int size, uint64_t data);

#define FLH(x)                                                                 \
  ((x->type == RXA_DEV_REG_XPOOL) ? (x->xslot | (1 << 2)) : x->xslot)
#endif

#define rxaFreeX(base, dev) \
do { \
	if (dev->type == RXA_TEMP_XPOOL) \
		dev->xslot = -1; \
} while (0)
