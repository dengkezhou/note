/*
Copyright (c) 2018-2019, tevador <tevador@gmail.com>
Copyright (c) 2019, SChernykh    <https://github.com/SChernykh>
Copyright (c) 2021, antiwinter    <https://github.com/antiwinter>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the copyright holder nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "isa-rxa.h"
#include "jrx_base.h"
#include "jrx_rxa.h"
#include <stdint.h>
#include <stdlib.h>

#define NEW_JUMPMODE

isa_rxa_t *initIsaRxa(int size, uint8_t *c, int *slots, uint8_t *d) {
  isa_rxa_t *dev = initJrxBase(size, c, slots, d);

  dev->name = "rxa";

  // I regs
  dev->M[zero] = 0; // zero
  dev->M[sp0]  = 1;
  dev->M[sp1]  = 2;
  dev->M[mxa]  = 3; // lr
  dev->M[r0]   = 4;
  dev->M[r1]   = 5;
  dev->M[r2]   = 6;
  dev->M[r3]   = 7;
  dev->M[r4]   = 8;
  dev->M[r5]   = 9;
  dev->M[r6]   = 10;
  dev->M[r7]   = 11;
  dev->M[it]   = 12;
  dev->M[xtmp] = 13;
  // gen reg xpool
  for (int i = 0; i < GEN_REG_XPOOL; i++)
    dev->M[xpool + i] = 14 + i;

  // rxa dev reg xpool
  for (int i = 0; i < DEV_REG_XPOOL; i++)
    dev->M[xpool + GEN_REG_XPOOL + i] = i;

  dev->M[f0]    = 16;
  dev->M[f1]    = 17;
  dev->M[f2]    = 18;
  dev->M[f3]    = 19;
  dev->M[e0]    = 20;
  dev->M[e1]    = 21;
  dev->M[e2]    = 22;
  dev->M[e3]    = 23;
  dev->M[a0]    = 24;
  dev->M[a1]    = 25;
  dev->M[a2]    = 26;
  dev->M[a3]    = 27;
  dev->M[vtmp]  = 28;
  dev->M[scale] = 29;

  dev->ofo = ofo_init();
  return dev;
}

void exitIsaRxa(isa_rxa_t *dev) {
  ofo_exit((ofo_t *)dev->ofo);
  exitJrxBase(dev);
}

static inline rxaX_t *_rxaAllocX(jrx_base_t *base, int mode, int resv,
                                 int prio) {
  rxaX_t *dev = NULL;

  if (prio == RXA_DEV_REG_XPOOL) {
    for (; base->lastdevregpool < TOT_REG_XPOOL; base->lastdevregpool++) {
      dev = &base->rslot[base->lastdevregpool];
      if (dev->xslot < 0 ||
          (mode == RXAI_REG32 && dev->xslot == RXAI_RS_LO32)) {
        dev->xpoolId = base->lastdevregpool - GEN_REG_XPOOL;
        dev->type    = RXA_DEV_REG_XPOOL;
        goto release;
      }
    }
  }

  int i;

  if (resv) {
    for (i = base->lastgenregpool; i < GEN_REG_XPOOL; i++) {
      dev = &base->rslot[i];
      if (dev->xslot < 0 ||
          (mode == RXAI_REG32 && dev->xslot == RXAI_RS_LO32)) {
        base->lastgenregpool = i;

        dev->xpoolId = i + dxpool0;
        dev->type    = RXA_GEN_REG_XPOOL;
        goto release;
      }
    }
  } else {
    i   = base->lastP;
    dev = &base->rslot[i];
    if (dev->xslot < 0) {
      base->lastP = i + 1;
      if (base->lastP == RESV_TMP)
        base->lastP = 0;

      dev->xpoolId = i + dxpool0;
      dev->type    = RXA_TEMP_XPOOL;
      goto release;
    }
  }

  if (!resv) {
    printf("cannot alloc rxa tmp X reg\n");
    for (;;)
      ;
  }

  return NULL;

release:
  dev->mode  = resv ? mode : RXAI_REG64;
  dev->xslot = (dev->mode == RXAI_REG64)
                   ? RXAI_RS_FULL
                   : ((dev->xslot < 0) ? RXAI_RS_LO32 : RXAI_RS_HI32);
  return dev;
}

rxaX_t *rxaAllocX(jrx_base_t *base, int mode) {
  return _rxaAllocX(base, mode, 0, RXA_GEN_REG_XPOOL);
}

rxaX_t *rxaResvX(jrx_base_t *base, int mode, int prio) {
  return _rxaAllocX(base, mode, 1, prio);
}

#define Remit32(dev, data)                                                     \
  do {                                                                         \
    int index, offs = (rxa->xslot == RXAI_RS_LO32) ? 0 : 4;                    \
    uint8_t *base;                                                             \
    if (rxa->type == RXA_DEV_REG_XPOOL) {                                      \
      index     = rxa->xpoolId;                                                \
      base      = (uint8_t *)(dev->xpool + index);                             \
      dev->xlen = index + 1;                                                   \
    } else {                                                                   \
      index = rxa->xpoolId - dxpool0 - RESV_TMP;                               \
      base  = (dev->code + dev->xpool_start - 8 * index);                      \
    }                                                                          \
    *(uint32_t *)(base + offs) = (uint32_t)data;                               \
  } while (0)

#define Remit64(dev, data)                                                     \
  do {                                                                         \
    int index;                                                                 \
    uint8_t *base;                                                             \
    if (rxa->type == RXA_DEV_REG_XPOOL) {                                      \
      index     = rxa->xpoolId;                                                \
      base      = (uint8_t *)(dev->xpool + index);                             \
      dev->xlen = index + 1;                                                   \
    } else {                                                                   \
      index = rxa->xpoolId - dxpool0 - RESV_TMP;                               \
      base  = (dev->code + dev->xpool_start - 8 * index);                      \
    }                                                                          \
    *(uint64_t *)base = (uint64_t)data;                                        \
  } while (0)

void set_resvLiteralPool(void *isa, rxaX_t *rxa, int size, uint64_t data) {
  isa_rxa_t *dev      = (isa_rxa_t *)isa;
  jrx_rxa_t *platform = (jrx_rxa_t *)dev->pdata;

  if (rxa->type == RXA_TEMP_XPOOL)
    return;

  switch (size) {
  case RXAI_REG32:
    Remit32(platform, data);
    break;
  case RXAI_REG64:
    Remit64(platform, data);
    break;
  default:
    printf("Resv literal pool size Error\n");
    for (;;)
      ;
  }
}

#if OUT_OF_ORDER
param_t param = {
    .mask_steps  = 9,
    .fetch_width = 1,
    .valid_width = 1,
    .unit        = {1, 1, 1, 1, 2, 4, 1, 1, 1, 1, 8,
             8}, // .lsu .imu .vau .vdv .vcv .alu .vbu .vmu .vsq .rxu .none
};

#define CODE(dev, _op, _rd, _rs, _p0, _p1, _cy)                                \
  do {                                                                         \
    ENC(dev, (_op | (_rd << 7) | (_rs << 12) | (_p0 << 17) | (_p1 << 22)),     \
        D1S1(_rd, _rs), 3, _cy);                                               \
  } while (0)

void ofo_reset(ofo_t *ofo) {}

ofo_t *ofo_init(void) { return NULL; }

void ofo_exit(ofo_t *ofo) {}
#else

param_t param = {
    .mask_steps  = 9,
    .fetch_width = 8,
    .valid_width = 6,
    .unit        = {1, 6, 3, 1, 1, 1, 6, 6,
             6}, // .lsu .alu .vau .vdv .vmu .vsq .rxu .none, cipher
};

isa_con_t cons[RXA_ISA_MAX] = {
    ISACON(LD, RXA_LSU, INTEGER),
    ISACON(ST, RXA_LSU, INTEGER),
    ISACON(VLD, RXA_LSU, FLOAT),
    ISACON(VLDQ_XOR, RXA_LSU, FLOAT),
    ISACON(VSTQ, RXA_LSU, FLOAT),
    ISACON(VLD_W, RXA_LSU, FLOAT),
    ISACON(VLDQ_W, RXA_LSU, FLOAT),
    ISACON(PRFC, RXA_LSU, INTEGER),
    ISACON(XOR, RXA_ALU, INTEGER),
    ISACON(ROR, RXA_ALU, INTEGER),
    ISACON(RORI, RXA_ALU, INTEGER),
    ISACON(SWAP, RXA_VSQ, FLOAT),
    ISACON(ADDSL, RXA_ALU, INTEGER),
    ISACON(ADDI, RXA_ALU, INTEGER),
    ISACON(SUB, RXA_ALU, INTEGER),
    ISACON(NEG, RXA_ALU, INTEGER),
    ISACON(MUL, RXA_ALU, INTEGER),
    ISACON(MULH, RXA_ALU, INTEGER),
    ISACON(MULHU, RXA_ALU, INTEGER),
    ISACON(VXOR, RXA_VAU, FLOAT),
    ISACON(VSWAP, RXA_VAU, FLOAT),
    ISACON(VADD_D, RXA_VAU, FLOAT),
    ISACON(VSUB_D, RXA_VAU, FLOAT),
    ISACON(VMUL_D, RXA_VMU, FLOAT),
    ISACON(VDIV_D, RXA_VDV, FLOAT),
    ISACON(VSQRT_D, RXA_VSQ, FLOAT),
    ISACON(VCVT_D_W, RXA_VAU, FLOAT),
    ISACON(RXSFRM, RXA_RXU, INTEGER),
    ISACON(RXSSP, RXA_VSQ, FLOAT),
    ISACON(RXSMXA, RXA_RXU, INTEGER),
    ISACON(RXB, RXA_RXU, INTEGER),
    ISACON(BGT, RXA_NONE, INTEGER),
    ISACON(BRK, RXA_RXU, INTEGER),
    ISACON(END, RXA_NONE, INTEGER),
    ISACON(NOP, RXA_NONE, INTEGER),
    ISACON(ADD, RXA_ALU, INTEGER),
    ISACON(BRGT, RXA_NONE, INTEGER),
    ISACON(RXBLK2B, RXA_CIPHER, INTEGER),
    ISACON(RXAES1RX4, RXA_CIPHER, INTEGER),
    ISACON(RXAES4RX4, RXA_CIPHER, INTEGER),
    ISACON(WPRFC, RXA_LSU, INTEGER),
};

static inline bool isStore(int op) {
  return Check(RXA_ISA_ST) || Check(RXA_ISA_VSTQ);
}

static inline bool isLoad(int op) {
  return Check(RXA_ISA_LD) || Check(RXA_ISA_VLD) || Check(RXA_ISA_VLDQ_XOR) ||
         Check(RXA_ISA_VLD_W) || Check(RXA_ISA_VLDQ_W);
}

static inline bool isFloat(int op) {
  return Check(RXA_ISA_VLD_W) || Check(RXA_ISA_VLDQ_W) ||
         Check(RXA_ISA_VADD_D) || Check(RXA_ISA_VSUB_D) ||
         Check(RXA_ISA_VMUL_D) || Check(RXA_ISA_VDIV_D) ||
         Check(RXA_ISA_VSQRT_D) || Check(RXA_ISA_VCVT_D_W);
}

static inline bool isNodst(int op) {
  return !isStore(op) && !Check(RXA_ISA_RXSFRM);
}

static inline bool isMultiR(int op) {
  return Check(RXA_ISA_VSTQ) || Check(RXA_ISA_VLDQ_W) ||
         Check(RXA_ISA_VLDQ_XOR);
}

static inline bool is2Src(int op) {
  return Check(RXA_ISA_SUB) || Check(RXA_ISA_MUL) || Check(RXA_ISA_MULH) ||
         Check(RXA_ISA_MULHU) || Check(RXA_ISA_VXOR) || Check(RXA_ISA_VADD_D) ||
         Check(RXA_ISA_VSUB_D) || Check(RXA_ISA_VMUL_D) ||
         Check(RXA_ISA_VDIV_D) || Check(RXA_ISA_ADD);
}

static inline bool isflh(int op) {
  return Check(RXA_ISA_PRFC) || Check(RXA_ISA_XOR) || Check(RXA_ISA_ADDSL) ||
         Check(RXA_ISA_ADD) || Check(RXA_ISA_SUB) || Check(RXA_ISA_MUL) ||
         Check(RXA_ISA_BGT);
}

static inline void update_rdep(ofo_t *ofo, int r, bool out) {
  isa_t *isa  = O(isa) + O(len) - 1;
  isa_t *rdep = O(rdep[r]);

  if (!ofo)
    return;

  if (rdep && r != x0) {
    if (r != jmp) {
      if (out) {
        if (rdep->srcDep[1]) {
          I(step) = Max(I(step), rdep->srcDep[0]->step);
          I(step) = Max(I(step), rdep->srcDep[1]->step);
        } else if (rdep->srcDep[0]) {
          I(step) = Max(I(step), rdep->srcDep[0]->step);
        }
      } else {
        if (!rdep->srcDep[0])
          rdep->srcDep[0] = isa;
        else if (!rdep->srcDep[1])
          rdep->srcDep[1] = isa;
        else {
          int choose = (rdep->srcDep[1]->step > rdep->srcDep[0]->step) ? 0 : 1;
          rdep->srcDep[choose] = isa;
        }
      }
    }
    I(step) = Max(I(step), rdep->step);
  }

  if (out)
    O(rdep[r]) = isa;
}

static inline int get_msk_number(ofo_t *ofo, int from, int to) {
  int number = 0;
  int m      = Max(from, to);
  int n      = Min(from, to);

  for (int i = 0; i < O(jlen); i++) {
    if (O(jumpId[i]) >= n) {
      if (O(jumpId[i]) < m)
        number++;
      else
        return number;
    }
  }
  return number;
}

static inline void vbitmsk(uint8_t *buf, int num, uint8_t val) {
  int cap = 8 / P(fetch_width);
  int msk = (1 << P(fetch_width)) - 1;

  if (num % cap)
    buf[num / cap] |= (val & msk) << (num % cap);
  else
    buf[num / cap] = (val & msk);
}

int get_MemoryStep(isa_rxa_t *isaF, isa_rxa_t *isaT) {
  int m        = Max(isaF->id, isaT->id);
  int n        = Min(isaF->id, isaT->id);
  int memory   = 0;
  jrx_rxa_t *p = (jrx_rxa_t *)isaF->pdata;

  for (int i = n; i < m; i++) {
    isa_rxa_t *dev = (isa_rxa_t *)(*(&(p->p0) + i - 1));
    memory += (dev->size - dev->pos);
  }

  return memory / (4 * P(fetch_width));
}

static inline int inject_mask(uint8_t *mask, isa_rxa_t *isaF, int from,
                              isa_rxa_t *isaT, int to) {
  ofo_t *ofoF = (ofo_t *)isaF->ofo, *ofoT = (ofo_t *)isaT->ofo;
  isa_t *fi = ofoF->isa + from, *ti = ofoT->isa + to;
  ofo_flag_t *tf;
  int fstep = fi->step + 1, tstep = ti->step - P(mask_steps), cstep;
  int tskip = 0, found = 0;
  int offs, j, i;

  if (tstep < 0)
    tstep = 0;

  i = mask[0];
  if (to) {
    for (j = 0; j <= 2 * P(mask_steps); j++) {
      cstep = tstep + j;
      if (cstep > ofoT->latest_step)
        break;

      tf = ofoT->uflags + cstep;

      uint8_t msk = 0;
      if (tf->isa_id[tf->len[INTEGER] - 1] >= ti->nid) {
        for (int j = 0; j < tf->len[INTEGER]; j++) {
          if (tf->isa_id[j] >= ti->nid) {
            msk   = 0x100 - (1 << j);
            found = 1;
            break;
          }
        }
      } else if (cstep >= fstep) {
        found = 1;
        msk   = 0x100 - (1 << tf->len[INTEGER]);
      }

      if (!found)
        tskip++;
      else
        mask[RXA_PICK_SIZE + 1 + j - tskip] = msk;
    }
    mask[RXA_PICK_SIZE] = j - tskip;
  } else
    mask[RXA_PICK_SIZE] = 0;

  if (isaF->id == isaT->id)
    offs = (tstep + tskip) - (fstep + i) -
           get_msk_number(ofoF, fstep + i, tstep + tskip);
  else if (isaF->id < isaT->id) {
    offs = (tstep + tskip) - (fstep + i) - get_msk_number(ofoF, 0, fstep + i) +
           get_MemoryStep(isaF, isaT);
  } else {
    offs = (tstep + tskip) + get_msk_number(ofoT, 0, tstep + tskip) -
           get_MemoryStep(isaF, isaT) - (fstep + i) -
           get_msk_number(ofoF, 0, fstep + i);
  }
  return offs;
}

void fill_in_code(isa_rxa_t *dev) {
  ofo_t *ofo = (ofo_t *)dev->ofo;
  int jump   = 0;
  uint32_t op;
  isa_t *isa = NULL;
  int j;

  for (int i = 0; i <= O(latest_step); i++) {
    ofo_flag_t *flags = O(uflags) + i;
    for (j = 0; j < F(len[INTEGER]); j++) {
      isa = O(isa) + F(isa_id[j]);
      // show_isa(isa->code);
      OENC(dev, P(fetch_width), (I(step) + jump), j, I(code));
    }

    op = getOP(I(code));
    if (P(fetch_width) > 1 &&
        (Check(RXA_ISA_RXB) || Check(RXA_ISA_BGT) || Check(RXA_ISA_BRGT))) {
      int rd = getRD(I(code)), rs = getRS(I(code)), p0 = getP0(I(code)),
          p1 = getP1(I(code));

      jump++;
      if (Check(RXA_ISA_RXB)) {
        int to   = (p1 & (1 << 9)) ? (p1 | 0xfffffe00) : p1;
        int offs = inject_mask(F(mask), dev, I(nid), dev, I(nid) + to + 1);
        I(code)  = op | rd << 7 | rs << 12 | p0 << 17 |
                  ((offs & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)) << 22;
      } else if (Check(RXA_ISA_BRGT)) {
        jrx_rxa_t *p = (jrx_rxa_t *)dev->pdata;
        int offs     = inject_mask(F(mask), dev, I(nid),
                               (isa_rxa_t *)(*(&(p->p0) + p0 - 1)), p1);
        I(code)      = RXA_ISA_BGT | rd << 7 | rs << 12 | ((offs & 0x7) << 19) |
                  (((offs >> 3) & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)) << 22;
      } else if (Check(RXA_ISA_BGT)) {
        int to = (p1 << 3) | (p0 >> 2);
        if (to & (1 << 12))
          to = (to & 0xfff) | (0xfffff << 12);
        int offs = inject_mask(F(mask), dev, I(nid), dev, I(nid) + to + 1);
        I(code)  = op | rd << 7 | rs << 12 | (p0 & 0x3) << 17 |
                  ((offs & 0x7) << 19) |
                  (((offs >> 3) & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)) << 22;
      }
      OENC(dev, P(fetch_width), (I(step) + jump - 1), j - 1, I(code));
      // set mask
      for (int h = 0; h < P(fetch_width); h++)
        OENC(dev, P(fetch_width), (i + jump), h, *((uint32_t *)F(mask) + h));
    }
  }
}
#ifdef __RXACODE__
static inline void CODE(isa_rxa_t *dev, uint32_t op, uint32_t rd, uint32_t rs,
                        uint32_t p0, uint32_t p1, uint32_t cy) {
  jrx_rxa_t *p                 = (jrx_rxa_t *)dev->pdata;
  ofo_t *ofo                   = (ofo_t *)dev->ofo;
  ProgramConfiguration_t *pcfg = p->pcfg;
  isa_t *isa                   = NULL;
  ofo_flag_t *flags            = NULL;
  int u, i;
  isa_con_t *con = &cons[op];

  if (O(finish))
    return;

  if (con->op != op) {
    printf("Unsupport this isa: 0x%x\n", op);
    return;
  }

  if (O(len) > MAX_ISA) {
    printf("Greater than Max Isa(%d)\n", MAX_ISA);
    return;
  }

  isa = O(isa) + O(len++);
  if (is2Src(op))
    I(code) = op | M(rd) << 7 | M(rs) << 12 | p0 << 17 | M(p1) << 22;
  else
    I(code) = op | M(rd) << 7 | M(rs) << 12 | p0 << 17 | p1 << 22;
  I(nid)       = O(len) - 1;
  I(step)      = -1;
  I(con)       = con;
  I(srcDep[0]) = NULL;
  I(srcDep[1]) = NULL;

  if (Check(RXA_ISA_END)) {
    I(step)   = O(latest_step) + 1;
    O(finish) = true;
    goto outStep;
  }

  update_rdep(ofo, jmp, false);
  // dep src
  if (isflh(op) && (p0 & (1 << 2))) {
    if (is2Src(op))
      update_rdep(ofo, IsVreg(p1), false);
  } else if (Check(RXA_ISA_RXSSP)) {
    update_rdep(ofo, M(rs), true);
    update_rdep(ofo, p0, false);
    update_rdep(ofo, M(r0) + pcfg->readReg0, false);
    update_rdep(ofo, M(r0) + pcfg->readReg1, false);
  } else if (Check(RXA_ISA_RXSMXA)) {
    update_rdep(ofo, IsVreg(rs), false);
    update_rdep(ofo, M(r0) + pcfg->readReg2, false);
    update_rdep(ofo, M(r0) + pcfg->readReg3, false);
  } else if (Check(RXA_ISA_SWAP)) {
    update_rdep(ofo, M(rs), false);
    update_rdep(ofo, M(rd), false);
    update_rdep(ofo, M(rs), true);
  } else if (Check(RXA_ISA_VSWAP)) {
    update_rdep(ofo, IsVreg(rd), false);
  } else if (is2Src(op)) {
    update_rdep(ofo, IsVreg(rs), false);
    update_rdep(ofo, IsVreg(p1), false);
  } else if (!Check(RXA_ISA_RORI))
    update_rdep(ofo, IsVreg(rs), false);

  // dep dst
  if (isMultiR(op)) {
    uint32_t r = Check(RXA_ISA_VSTQ) ? rs : rd;
    int num    = IsV(r) ? 4 : 8;
    for (i = 0; i < num; i++)
      update_rdep(ofo, (IsV(r) ? IsVreg(r) + i : 2 * IsVreg(r) + i),
                  isNodst(op));
  } else
    update_rdep(ofo, IsVreg(rd), isNodst(op));

  // dep mem
  if (isStore(op))
    update_rdep(ofo, mem, true);
  else if (isLoad(op))
    update_rdep(ofo, mem, false);

  // dep frm
  if (isFloat(op)) {
    update_rdep(ofo, frm, false);
  } else if (Check(RXA_ISA_RXSFRM))
    update_rdep(ofo, frm, true);

  if (Check(RXA_ISA_RXB) || Check(RXA_ISA_BGT) || Check(RXA_ISA_BRGT))
    update_rdep(ofo, jmp, true);

  I(step) += 1;

  if ((O(latest_step) - I(step)) > P(mask_steps))
    I(step) = O(latest_step) - P(mask_steps);

outStep:
  u = N(unit);
  while (1) {
    flags = O(uflags) + I(step);
    if (F(unit[u]) < P(unit[u]) && F(len) <= (P(fetch_width) - 1)) {
      F(isa_id[F(len)]) = I(nid);
      F(len++);
      F(unit[u]++);
      break;
    } else
      I(step++);
  }
  // show_isa(I(code));
  // printf("Out-of-order: %d, %d, true %d, In-order: %d\n", I(step), (F(len) -
  // 1), (I(step) + O(jlen)), I(nid));
  O(latest_step) = Max(I(step), O(latest_step));

  if (Check(RXA_ISA_RXB) || Check(RXA_ISA_BGT) || Check(RXA_ISA_BRGT)) {
    O(jumpId[O(jlen)]) = I(step);
    O(jlen)++;
    I(fstepEnd) = O(latest_step) - I(step);

    F(mask[0])    = I(fstepEnd);
    uint8_t *mask = &(F(mask[1]));
    // set pick
    for (int m = 0; m < I(fstepEnd); m++) {
      flags = O(uflags) + I(step) + 1 + m;
      vbitmsk(mask, m, (1 << F(len)) - 1);
    }
  }

  if (O(finish))
    fill_in_code(dev);
}
#endif

void ofo_reset(ofo_t *ofo) {
  memset(ofo->uflags, 0, (ofo->latest_step + 1) * sizeof(ofo_flag_t));
  ofo->len         = 0;
  ofo->latest_step = 0;
  ofo->finish      = false;
  ofo->jlen        = 0;

  for (int i = 0; i < (jmp + 1); i++) {
    ofo->rdep[i]            = &ofo->dfdep[i];
    ofo->rdep[i]->step      = -1;
    ofo->rdep[i]->srcDep[0] = NULL;
    ofo->rdep[i]->srcDep[1] = NULL;
  }
}

ofo_t *ofo_init(void) {
  ofo_t *ofo = (ofo_t *)malloc(sizeof(ofo_t));
  if (!ofo)
    return NULL;

  memset(ofo, 0, sizeof(ofo_t));
  for (int i = 0; i < (jmp + 1); i++) {
    ofo->rdep[i]       = &ofo->dfdep[i];
    ofo->rdep[i]->step = -1;
  }

  return ofo;
}

void ofo_exit(ofo_t *ofo) {
  if (ofo)
    free(ofo);
}
#endif

void cfg_literPool(void *isa, void *pdata) {
  isa_rxa_t *dev = (isa_rxa_t *)isa;

  dev->pdata = pdata;
}

int set_literalPool(void *isa, int dst, uint64_t data) {
  isa_rxa_t *dev = (isa_rxa_t *)isa;
  jrx_rxa_t *platform;

  if (!dev)
    return -1;

  platform = (jrx_rxa_t *)dev->pdata;
  if ((platform->literal_pos - 8) < platform->literal_end) {
    printf("LiteralPool do not enough\n");
    return -1;
  }

  *(uint64_t *)(platform->code + platform->literal_pos) = data;
  R_ld(isa, dst, dzero, 0, platform->literal_pos);
  platform->literal_pos -= 8;
  return 0;
}

#ifdef __RXACODE__
#define rxa_code_init(mode)
#define rxa_code_pre(_code)
#define rxa_code_last()
#else
#define rxa_code_init(mode)                                                    \
  ofo_t *ofo        = (ofo_t *)dev->ofo;                                       \
  isa_t *isa        = NULL;                                                    \
  ofo_flag_t *flags = NULL;                                                    \
  isa_con_t *con    = &cons[mode];                                             \
  int u;

#define rxa_code_pre(_code)                                                    \
  do {                                                                         \
    isa          = O(isa) + O(len++);                                          \
    I(nid)       = O(len) - 1;                                                 \
    I(step)      = -1;                                                         \
    I(code)      = _code;                                                      \
    I(con)       = con;                                                        \
    I(srcDep[0]) = NULL;                                                       \
    I(srcDep[1]) = NULL;                                                       \
  } while (0)

#define rxa_code_last()                                                        \
  do {                                                                         \
    I(step) += 1;                                                              \
    if ((O(latest_step) - I(step)) > P(mask_steps))                            \
      I(step) = O(latest_step) - P(mask_steps);                                \
                                                                               \
    u = N(unit);                                                               \
    while (1) {                                                                \
      flags = O(uflags) + I(step);                                             \
      if (F(unit[u]) < P(unit[u])) {                                           \
        switch (N(type)) {                                                     \
        case INTEGER:                                                          \
          if (F(len[INTEGER]) < P(valid_width)) {                              \
            F(isa_id[F(len[INTEGER])]) = I(nid);                               \
            F(len[INTEGER]++);                                                 \
            F(unit[u]++);                                                      \
            goto out;                                                          \
          } else                                                               \
            goto nextStep;                                                     \
          break;                                                               \
        case FLOAT:                                                            \
          if (F(len[FLOAT]) < 3 && F(len[INTEGER]) < P(valid_width)) {         \
            F(isa_id[F(len[INTEGER])]) = I(nid);                               \
            F(len[INTEGER]++);                                                 \
            F(len[FLOAT]++);                                                   \
            F(unit[u]++);                                                      \
            goto out;                                                          \
          } else                                                               \
            goto nextStep;                                                     \
        }                                                                      \
      }                                                                        \
    nextStep:                                                                  \
      I(step++);                                                               \
    }                                                                          \
  out:                                                                         \
    O(latest_step) = Max(I(step), O(latest_step));                             \
  } while (0)
#endif

inline void R_ld(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
  rxaX_t *t0     = NULL;
  rxa_code_init(RXA_ISA_LD)

      if (offs >> 13) {
    if (rs == dzero) {
      t0 = rxaResvX(dev, RXAI_REG64, RXA_GEN_REG_XPOOL);
      if (t0)
        set_resvLiteralPool(dev, t0, t0->mode, offs);
    }
    if (!t0) {
      t0 = rxaAllocX(dev, RXAI_REG32);
      R_addi(dev, t0->xpoolId, rs, offs);
    }
#ifdef __RXACODE__
    CODE(dev, RXA_ISA_LD, rd, t0->xpoolId, mask, 0, 3);
#else
    rxa_code_pre(RXA_ISA_LD | rd << 7 | t0->xpoolId << 12 | mask << 17);

    update_rdep(ofo, jmp, false);
    update_rdep(ofo, rd, true);
    update_rdep(ofo, mem, false);
    update_rdep(ofo, t0->xpoolId, false);
#endif
    rxaFreeX(dev, t0);
  }
  else {
#ifdef __RXACODE__
    CODE(dev, RXA_ISA_LD, rd, rs, mask, (offs >> 3), 3);
#else
    rxa_code_pre(RXA_ISA_LD | rd << 7 | rs << 12 | mask << 17 |
                 (offs >> 3) << 22);

    update_rdep(ofo, jmp, false);
    update_rdep(ofo, rd, true);
    update_rdep(ofo, mem, false);
    update_rdep(ofo, rs, false);
#endif
  }
  rxa_code_last();
}

inline void R_st(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_ST, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_ST)

      rxa_code_pre(RXA_ISA_ST | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, false);
  update_rdep(ofo, rd, false);
  update_rdep(ofo, mem, true);

  rxa_code_last();
#endif
}

void R_vld(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VLD, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_VLD)

      rxa_code_pre(RXA_ISA_VLD | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, mem, false);

  rxa_code_last();
#endif
}

void R_vldp(void *isa, int rd, int rd1, int rs, int mask, int offs) {
  R_vld(isa, rd, rs, mask, offs);
  R_vld(isa, rd1, rs, mask, offs + 16);
}

void R_vldq_xor(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VLDQ_XOR, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_VLDQ_XOR)

      rxa_code_pre(RXA_ISA_VLDQ_XOR | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, false);
  bool isV = (rd >= df0);
  int num  = isV ? 4 : 8;

  for (int i = 0; i < num; i++)
    update_rdep(ofo, (isV ? rd + v0 + i : 2 * rd + i), true);

  update_rdep(ofo, mem, false);

  rxa_code_last();
#endif
}

void R_vstq(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VSTQ, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_VSTQ)

      rxa_code_pre(RXA_ISA_VSTQ | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rd, false);
  bool isV = (rs >= df0);
  int num  = isV ? 4 : 8;
  for (int i = 0; i < num; i++)
    update_rdep(ofo, (isV ? rs + v0 + i : 2 * rs + i), false);

  update_rdep(ofo, mem, true);

  rxa_code_last();
#endif
}

void R_vld_w(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VLD_W, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_VLD_W)

      rxa_code_pre(RXA_ISA_VLD_W | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, mem, false);

  rxa_code_last();
#endif
}

void R_vldq_w(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VLDQ_W, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_VLDQ_W)

      rxa_code_pre(RXA_ISA_VLDQ_W | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, false);

  bool isV = (rd >= df0);
  int num  = isV ? 4 : 8;
  for (int i = 0; i < num; i++)
    update_rdep(ofo, (isV ? rd + v0 + i : 2 * rd + i), true);

  update_rdep(ofo, mem, false);

  rxa_code_last();
#endif
}

void R_prfc(void *code, int rd, int rs, int mask, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_PRFC, rd, rs, mask, (offs >> 3), 3);
#else
  rxa_code_init(RXA_ISA_PRFC)

      rxa_code_pre(RXA_ISA_PRFC | rd << 7 | rs << 12 | mask << 17 |
                   (offs >> 3) << 22);

  if (!(mask & (1 << 2)))
    update_rdep(ofo, rs, false);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rd, false);

  rxa_code_last();
#endif
}

void R_wprfc(void *code, int rs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_WPRFC, dzero, dzero, 0, 0, 1);
#else
  rxa_code_init(RXA_ISA_WPRFC)

      rxa_code_pre(RXA_ISA_WPRFC);

  update_rdep(ofo, rs, false);
  update_rdep(ofo, jmp, false);
  rxa_code_last();
#endif
}

void R_xor(void *code, int rd, int rs, int flh) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_XOR, rd, rs, flh, 0, 3);
#else
  rxa_code_init(RXA_ISA_XOR)

      rxa_code_pre(RXA_ISA_XOR | rd << 7 | rs << 12 | flh << 17);

  update_rdep(ofo, jmp, false);
  if (!(flh & (1 << 2)))
    update_rdep(ofo, rs, false);

  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_ror(void *code, int rd, int rs, int mode) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_ROR, rd, rs, mode, 0, 3);
#else
  rxa_code_init(RXA_ISA_ROR)

      rxa_code_pre(RXA_ISA_ROR | rd << 7 | rs << 12 | mode << 17);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_rori(void *code, int rd, int shift) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RORI, rd, 0, 0, shift, 3);
#else
  rxa_code_init(RXA_ISA_RORI)

      rxa_code_pre(RXA_ISA_RORI | rd << 7 | shift << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_swap(void *code, int rd, int rs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_SWAP, rd, rs, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_SWAP)

      rxa_code_pre(RXA_ISA_SWAP | rd << 7 | rs << 12);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, true);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_addsl(void *code, int rd, int rs, int flh, int shift) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_ADDSL, rd, rs, flh, shift, 3);
#else
  rxa_code_init(RXA_ISA_ADDSL)

      rxa_code_pre(RXA_ISA_ADDSL | rd << 7 | rs << 12 | flh << 17 |
                   shift << 22);

  update_rdep(ofo, jmp, false);
  if (!(flh & (1 << 2)))
    update_rdep(ofo, rs, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_add(void *code, int rd, int rs, int flh, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_ADD, rd, rs, flh, rs2, 3);
#else
  rxa_code_init(RXA_ISA_ADD)

      rxa_code_pre(RXA_ISA_ADD | rd << 7 | rs << 12 | flh << 17 | rs2 << 22);

  update_rdep(ofo, jmp, false);
  if (flh & (1 << 2))
    update_rdep(ofo, rs2, false);
  else {
    update_rdep(ofo, rs, false);
    update_rdep(ofo, rs2, false);
  }
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

static inline void _R_addi(void *code, int rd, int rs, int imm) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#if 0
  int c          = imm < 0 ? ~imm : imm;

  if (c >> 14) {
    printf("The immediate value of Addi must in [0, 14]\n");
    return;
  }
#endif
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_ADDI, rd, rs, (imm & 0x1f), ((imm >> 5) & 0x3ff), 3);
#else
  rxa_code_init(RXA_ISA_ADDI)

      rxa_code_pre(RXA_ISA_ADDI | rd << 7 | rs << 12 | (imm & 0x1f) << 17 |
                   ((imm >> 5) & 0x3ff) << 22);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rs, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_addi(void *isa, int rd, int rs, int imm) {
  isa_rxa_t *dev = (isa_rxa_t *)isa;
  int u          = imm < 0 ? ~imm : imm;
  rxaX_t *t0;

  if (!(u >> 14))
    _R_addi(isa, rd, rs, imm);
  else {
    t0 = rxaResvX(dev, RXAI_REG32, RXA_DEV_REG_XPOOL);
    if (t0)
      set_resvLiteralPool(isa, t0, t0->mode, imm);
    else {
      t0 = rxaAllocX(dev, RXAI_REG64);
      if (set_literalPool(isa, t0->xpoolId, imm) < 0) {
        printf("Config literPool first\n");
        return;
      }
    }
    if (rd == rs)
      R_addsl(isa, rd, t0->xpoolId, FLH(t0), 0);
    else
      R_add(isa, rd, t0->xpoolId, FLH(t0), rs);
    rxaFreeX(dev, t0);
  }
}

void R_li(void *isa, int rd, int imm) {
  int u = imm < 0 ? ~imm : imm;

  if (!(u >> 14))
    _R_addi(isa, rd, dzero, imm);
  else {
    if (set_literalPool(isa, rd, imm) < 0) {
      printf("Config literPool first\n");
      return;
    }
  }
}

void R_neg(void *code, int rd) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_NEG, rd, 0, 0, 0, 1);
#else
  rxa_code_init(RXA_ISA_NEG)

      rxa_code_pre(RXA_ISA_NEG | rd << 7);

  update_rdep(ofo, jmp, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_mov(void *isa, int rd, int rs) { R_addi(isa, rd, rs, 0); }

void R_sub(void *code, int rd, int rs, int flh, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_SUB, rd, rs, flh, rs2, 3);
#else
  rxa_code_init(RXA_ISA_SUB)

      rxa_code_pre(RXA_ISA_SUB | rd << 7 | rs << 12 | flh << 17 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  if (flh & (1 << 2))
    update_rdep(ofo, rs2, false);
  else {
    update_rdep(ofo, rs, false);
    update_rdep(ofo, rs2, false);
  }
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_mul(void *code, int rd, int rs, int flh, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_MUL, rd, rs, flh, rs2, 3);
#else
  rxa_code_init(RXA_ISA_MUL)

      rxa_code_pre(RXA_ISA_MUL | rd << 7 | rs << 12 | flh << 17 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  if (flh & (1 << 2))
    update_rdep(ofo, rs2, false);
  else {
    update_rdep(ofo, rs, false);
    update_rdep(ofo, rs2, false);
  }
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_mulh(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_MULH, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_MULH)

      rxa_code_pre(RXA_ISA_MULH | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs, false);
  update_rdep(ofo, rs2, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_mulhu(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_MULHU, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_MULHU)

      rxa_code_pre(RXA_ISA_MULHU | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs, false);
  update_rdep(ofo, rs2, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_vxor(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VXOR, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_VXOR)

      rxa_code_pre(RXA_ISA_VXOR | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rs2 + v0, false);
  update_rdep(ofo, rd + v0, true);

  rxa_code_last();
#endif
}

void R_vswap(void *code, int rd) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VSWAP, rd, 0, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_VSWAP)

      rxa_code_pre(RXA_ISA_VSWAP | rd << 7);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rd + v0, true);

  rxa_code_last();
#endif
}

void R_vadd_d(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VADD_D, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_VADD_D)

      rxa_code_pre(RXA_ISA_VADD_D | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rs2 + v0, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, frm, false);

  rxa_code_last();
#endif
}

void R_vsub_d(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VSUB_D, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_VSUB_D)

      rxa_code_pre(RXA_ISA_VSUB_D | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rs2 + v0, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, frm, false);

  rxa_code_last();
#endif
}

void R_vmul_d(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VMUL_D, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_VMUL_D)

      rxa_code_pre(RXA_ISA_VMUL_D | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rs2 + v0, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, frm, false);

  rxa_code_last();
#endif
}

void R_vdiv_d(void *code, int rd, int rs, int rs2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VDIV_D, rd, rs, 0, rs2, 3);
#else
  rxa_code_init(RXA_ISA_VDIV_D)

      rxa_code_pre(RXA_ISA_VDIV_D | rd << 7 | rs << 12 | rs2 << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rs2 + v0, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, frm, false);

  rxa_code_last();
#endif
}

void R_vsqrt_d(void *code, int rd, int rs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VSQRT_D, rd, rs, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_VSQRT_D)

      rxa_code_pre(RXA_ISA_VSQRT_D | rd << 7 | rs << 12);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, frm, false);

  rxa_code_last();
#endif
}

void R_vcvt_d_w(void *code, int rd, int rs, int e) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_VCVT_D_W, rd, rs, e, 0, 3);
#else
  rxa_code_init(RXA_ISA_VCVT_D_W)

      rxa_code_pre(RXA_ISA_VCVT_D_W | rd << 7 | rs << 12 | e << 17);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs + v0, false);
  update_rdep(ofo, rd + v0, true);
  update_rdep(ofo, frm, false);

  rxa_code_last();
#endif
}

void R_rxsfrm(void *code, int rs, int imm) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXSFRM, 0, rs, 0, imm, 3);
#else
  rxa_code_init(RXA_ISA_RXSFRM)

      rxa_code_pre(RXA_ISA_RXSFRM | rs << 12 | imm << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs, false);
  update_rdep(ofo, frm, true);

  rxa_code_last();
#endif
}

void R_rxssp(void *code, int rd1, int rs, int rd2) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXSSP, rd1, rs, rd2, 0, 3);
#else
  rxa_code_init(RXA_ISA_RXSSP) jrx_rxa_t *p = (jrx_rxa_t *)dev->pdata;
  ProgramConfiguration_t *pcfg              = p->pcfg;

  rxa_code_pre(RXA_ISA_RXSSP | rd1 << 7 | rs << 12 | rd2 << 17);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs, true);
  update_rdep(ofo, rd2, true);
  update_rdep(ofo, dr0 + pcfg->readReg0, false);
  update_rdep(ofo, dr0 + pcfg->readReg1, false);
  update_rdep(ofo, rd1, true);

  rxa_code_last();
#endif
}

void R_rxsmxa(void *code, int rd) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXSMXA, rd, 0, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_RXSMXA) jrx_rxa_t *p = (jrx_rxa_t *)dev->pdata;
  ProgramConfiguration_t *pcfg               = p->pcfg;

  rxa_code_pre(RXA_ISA_RXSMXA | rd << 7);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, dr0 + pcfg->readReg2, false);
  update_rdep(ofo, dr0 + pcfg->readReg3, false);
  update_rdep(ofo, rd, true);

  rxa_code_last();
#endif
}

void R_rxb(void *code, int rd, int rs, int sl, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
  offs >>= 2;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXB, rd, rs, sl,
       ((offs & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)), 3);
#else
  rxa_code_init(RXA_ISA_RXB)

      rxa_code_pre(RXA_ISA_RXB | rd << 7 | rs << 12 | sl << 17 |
                   (((offs & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)) << 22));

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, rs, false);
  update_rdep(ofo, rd, true);

  update_rdep(ofo, jmp, true);

  rxa_code_last();

  O(jumpId[O(jlen)]) = I(step);
  O(jlen)++;
  I(fstepEnd)   = O(latest_step) - I(step);
  F(mask[0])    = I(fstepEnd);
  uint8_t *mask = &(F(mask[1]));
  // set pick
  for (int m = 0; m < I(fstepEnd); m++) {
    flags   = O(uflags) + I(step) + 1 + m;
    mask[m] = (1 << F(len[INTEGER])) - 1;
  }
#endif
}
void R_brk(void *code) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_BRK, 0, 0, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_BRK)

      rxa_code_pre(RXA_ISA_BRK);

  update_rdep(ofo, jmp, false);

  rxa_code_last();
#endif
}

void R_bgt(void *code, int rd, int rs, int flh, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
  offs >>= 2;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_BGT, rd, rs, (flh | ((offs & 0x7) << 2)),
       (((offs >> 3) & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)), 3);
#else
  rxa_code_init(RXA_ISA_BGT) int p0 = flh | ((offs & 0x7) << 2);

  rxa_code_pre(RXA_ISA_BGT | rd << 7 | rs << 12 | p0 << 17 |
               (((offs >> 3) & 0x1ff) | ((offs < 0) ? (1 << 9) : 0)) << 22);

  update_rdep(ofo, jmp, false);

  if (p0 & (1 << 2))
    update_rdep(ofo, rs, false);

  update_rdep(ofo, jmp, true);

  rxa_code_last();

  O(jumpId[O(jlen)]) = I(step);
  O(jlen)++;
  I(fstepEnd)   = O(latest_step) - I(step);
  F(mask[0])    = I(fstepEnd);
  uint8_t *mask = &(F(mask[1]));
  // set pick
  for (int m = 0; m < I(fstepEnd); m++) {
    flags   = O(uflags) + I(step) + 1 + m;
    mask[m] = (1 << F(len[INTEGER])) - 1;
  }
#endif
}
extern int step_avp;
void R_end(void *code) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_END, 0, 0, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_END)

      rxa_code_pre(RXA_ISA_END);

  I(step) = O(latest_step);

  rxa_code_last();
  fill_in_code(dev);
  step_avp += I(step);
#if 0
	if (dev->id < 4) {
		printf("instruction %d\n", dev->id);
		for (int i = 0; i < dev->size/4; i++) {
			printf("0x%016x ", *((uint32_t *)dev->code + i));
			if (!((i + 1) % 8))
				printf("\n");
		}
	}
#endif
#endif
}

void R_nop(void *code) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_NOP, 0, 0, 0, 0, 3);
#else
  rxa_code_init(RXA_ISA_NOP)

      rxa_code_pre(RXA_ISA_NOP);

  update_rdep(ofo, jmp, false);

  rxa_code_last();
#endif
}

void R_link(isa_rxa_t *base, isa_rxa_t *to, int offs) {
  isa_rxa_t *dev = (isa_rxa_t *)base;
  // int offset;

#ifdef __RXACODE__
#if 0
  CODE(dev, RXA_ISA_BRGT, dit, dzero, to->id, offs, 3);
#else
  // printf("isa->code %p, base->code %p, isaSize(dev) %d, offs %d\n",
  // isa->code, base->code, isaSize(dev), offs);
  offset = ((to->code - (base->code + isaSize(dev)) - 4) >> 2) + offs;
  // printf("offset %x\n", offset);
  CODE(dev, RXA_ISA_BGT, dit, dzero, ((offset & 0x7) << 2),
       (((offset >> 3) & 0x1ff) | ((offset < 0) ? (1 << 9) : 0)), 3);
#endif
#else
  rxa_code_init(RXA_ISA_BRGT)

      rxa_code_pre(RXA_ISA_BRGT | dit << 7 | to->id << 17 | offs << 22);

  update_rdep(ofo, jmp, false);

  update_rdep(ofo, dit, true);
  update_rdep(ofo, jmp, true);

  rxa_code_last();

  O(jumpId[O(jlen)]) = I(step);
  O(jlen)++;
  I(fstepEnd)   = O(latest_step) - I(step);
  F(mask[0])    = I(fstepEnd);
  uint8_t *mask = &(F(mask[1]));
  // set pick
  for (int m = 0; m < I(fstepEnd); m++) {
    flags   = O(uflags) + I(step) + 1 + m;
    mask[m] = (1 << F(len[INTEGER])) - 1;
  }
#endif
}

void R_rxblk2b(void *code, int index) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXBLK2B, 0, 0, index, 0, 1);
#else
  rxa_code_init(RXA_ISA_RXBLK2B)

      rxa_code_pre(RXA_ISA_RXBLK2B | index << 17);

  update_rdep(ofo, jmp, false);

  rxa_code_last();
#endif
}

void R_rxaes1rx4(void *code, int index, int mode) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXAES1RX4, 0, 0, index, mode, 1);
#else
  rxa_code_init(RXA_ISA_RXAES1RX4)

      rxa_code_pre(RXA_ISA_RXAES1RX4 | index << 17 | mode << 22);

  update_rdep(ofo, jmp, false);

  rxa_code_last();
#endif
}

void R_rxaes4rx4(void *code, int index) {
  isa_rxa_t *dev = (isa_rxa_t *)code;
#ifdef __RXACODE__
  CODE(dev, RXA_ISA_RXAES4RX4, 0, 0, index, 0, 1);
#else
  rxa_code_init(RXA_ISA_RXAES4RX4)

      rxa_code_pre(RXA_ISA_RXAES4RX4 | index << 17);

  update_rdep(ofo, jmp, false);

  rxa_code_last();
#endif
}
