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
#include "isa-rv64g.h"
#include "jrx_base.h"
#include <stdint.h>

//#define RV_TRUE_V_ISA

#define RV(_i, _c) static uint32_t _i = _c
RV(VMV, 0x17);
RV(VFUNARY0, 0x12);
RV(VWXUNARY0, 0x10);
#ifdef RV_TRUE_V_ISA
RV(VAND, 0x9);
RV(VOR, 0xa);
RV(VXOR, 0xb);
RV(VFADD, 0x0);
RV(VFSUB, 0x2);
RV(VFMUL, 0x24);
RV(VFDIV, 0x20);
RV(VFUNARY1, 0x13);
RV(VRGATHER, 0xc);
#endif
RV(VSLIDE1DOWN, 0xf);
RV(VMVR, 0x27);


isa_rv64g_t *initIsaRV64g(int size, uint8_t *c, int *slots, uint8_t *d) {
  isa_rv64g_t *dev = initJrxBase(size, c, slots, d);

  dev->name = "rv64g";
  /* for init dataset */
  dev->M[ra]   = 1; // lr
  dev->M[ds0]  = 10;
  dev->M[ds1]  = 11;
  dev->M[ds2]  = 12;
  dev->M[ds3]  = 13;
  dev->M[ds4]  = 14;
  dev->M[ds5]  = 15;
  dev->M[ds6]  = 16;
  dev->M[ds7]  = 17;
  dev->M[ds8]  = 18;
  dev->M[ds9]  = 19;
  dev->M[ds10] = 20;
  dev->M[ds11] = 21;
  dev->M[ds12] = 22;
  dev->M[ds13] = 23;
  dev->M[ds14] = 24;
  /* for ds pool */
  dev->M[dspool + 0] = 28;
  dev->M[dspool + 1] = 29;
  dev->M[dspool + 2] = 30;
  dev->M[dspool + 3] = 31;

  // I regs
  dev->M[zero] = 0; // zero
  dev->M[mxa]  = 1; // lr
  dev->M[sp]   = 2;
  // M[mxa] = 3; // gp
  // M[mxa] = 4; // tp
  dev->M[sp0]        = 5;
  dev->M[sp1]        = 6;
  dev->M[xpool + 10] = 7;
  dev->M[xtmp]       = 8;
#ifndef RV_TRUE_V_ISA
  dev->M[E_and] = 9;
#endif
  dev->M[rf]        = 10; // arg0 -> p1
  dev->M[mm]        = 11; // arg1 -> dataset
  dev->M[sc]        = 12; // arg2
  dev->M[ic]        = 13; // arg3
  dev->M[r0]        = 14;
  dev->M[r1]        = 15;
  dev->M[r2]        = 16;
  dev->M[r3]        = 17;
  dev->M[r4]        = 18;
  dev->M[r5]        = 19;
  dev->M[r6]        = 20;
  dev->M[r7]        = 21;
  dev->M[xpool + 0] = 22;
  dev->M[xpool + 1] = 23;
  dev->M[xpool + 2] = 24;
  dev->M[xpool + 3] = 25;
  dev->M[xpool + 4] = 26;
  dev->M[xpool + 5] = 27;
  dev->M[xpool + 6] = 28;
  dev->M[xpool + 7] = 29;
  dev->M[xpool + 8] = 30;
  dev->M[xpool + 9] = 31;
#ifdef RV_TRUE_V_ISA
  dev->M[e0]        = 1;
  dev->M[e1]        = 2;
  dev->M[e2]        = 3;
  dev->M[e3]        = 4;
  dev->M[f0]        = 5;
  dev->M[f1]        = 6;
  dev->M[f2]        = 7;
  dev->M[f3]        = 8;
  dev->M[a0]        = 9;
  dev->M[a1]        = 10;
  dev->M[a2]        = 11;
  dev->M[a3]        = 12;
  dev->M[vtmp]      = 13;
  dev->M[E_or]      = 14;
  dev->M[scale]     = 15;
  dev->M[E_and]     = 16;
  dev->M[vpool + 0] = 17;
  dev->M[vpool + 1] = 18;
  dev->M[vpool + 2] = 19;
  dev->M[vpool + 3] = 20;
  dev->M[vpool + 4] = 21;
  dev->M[vpool + 5] = 22;
#else
  // F regs
  dev->M[e0]        = 0x0001;
  dev->M[e1]        = 0x0203;
  dev->M[e2]        = 0x0405;
  dev->M[e3]        = 0x0607;
  dev->M[f0]        = 0x0809;
  dev->M[f1]        = 0x0a0b;
  dev->M[f2]        = 0x0c0d;
  dev->M[f3]        = 0x0e0f;
  dev->M[a0]        = 0x1011;
  dev->M[a1]        = 0x1213;
  dev->M[a2]        = 0x1415;
  dev->M[a3]        = 0x1617;
  dev->M[vtmp]      = 0x1819;
  dev->M[E_or]      = 0x1a1b;
  dev->M[scale]     = 0x1c1d;
  dev->M[vpool + 0] = 0x1e;
  dev->M[vpool + 1] = 0x1f;
#endif
  dev->ops = &isa_rv64g;
  return dev;
}

void exitIsaRV64g(isa_rv64g_t *dev) { exitJrxBase(dev); }

#define Type_U(dev, _op, _rd, _imm, _cy)                                       \
  ENC(dev, _op | dev->M[_rd] << 7 | (_imm >> 12) << 12, D1(_rd), 3, _cy)

#define Type_I(dev, _op, _f, _rd, _rs, _imm, _cy)                              \
  ENC(dev,                                                                     \
      _op | dev->M[_rd] << 7 | _f << 12 | dev->M[_rs] << 15 | (_imm) << 20,    \
      D1S1(_rd, _rs), 3, _cy)

#define Type_L(dev, _op, _f, _rd, _rs, _offs, _cy)                             \
  ENC(dev,                                                                     \
      _op | dev->M[_rd] << 7 | _f << 12 | dev->M[_rs] << 15 | (_offs) << 20,   \
      D1S2(_rd, _rs, 0xfe), 4, _cy)

#define Type_S(dev, _op, _f, _rs1, _rs2, _offs, _cy)                           \
  do {                                                                         \
    ENC(dev,                                                                   \
        _op | (_offs & 0x1f) << 7 | _f << 12 | dev->M[_rs1] << 15 |            \
            dev->M[_rs2] << 20 | (_offs >> 5) << 25,                           \
        D1S2(0xfe, _rs1, _rs2), 5, _cy);                                       \
  } while (0)

#define Type_R(dev, _op, _f, _f7, _rd, _rs1, _rs2, _cy)                        \
  ENC(dev,                                                                     \
      _op | dev->M[_rd] << 7 | _f << 12 | dev->M[_rs1] << 15 |                 \
          dev->M[_rs2] << 20 | _f7 << 25,                                      \
      D1S2(_rd, _rs1, _rs2), 3, _cy)

#define Type_B(dev, _op, _f, _rs1, _rs2, _offs, _cy)                           \
  do {                                                                         \
    int offs_4_1_11  = ((_offs & ~1) | !!(_offs & (1 << 11))) & 0x1f;          \
    int offs_12_10_5 = ((_offs >> 5) & 0x3f) | ((_offs >> 31) << 6);           \
    ENC(dev,                                                                   \
        _op | offs_4_1_11 << 7 | _f << 12 | dev->M[_rs1] << 15 |               \
            dev->M[_rs2] << 20 | offs_12_10_5 << 25,                           \
        -1, 3, _cy);                                                           \
  } while (0)

#define Type_J(dev, _op, _rd, _offs, _cy)                                      \
  do {                                                                         \
    _offs = CUT(_offs, 12, 8, 0) | CUT(_offs, 11, 1, 8) |                      \
            CUT(_offs, 1, 10, 9) | (_offs < 0) << 19;                          \
    ENC(dev, _op | dev->M[_rd] << 7 | _offs << 12, -1, 3, _cy);                \
  } while (0)

void li(void *isa, int rd1, int imm);
void li64(void *isa, int rd1, int64_t imm);
void mov(void *isa, int rd, int rs);
void prefetch(void *isa, int rs);
void ld(void *isa, int rd, int rs1, int offs);
void sd(void *isa, int rs1, int rs2, int offs);
void ldp(void *isa, int rd1, int rd2, int rs1, int offs);
void sdp(void *isa, int rs1, int rs2, int t, int offs);
void andi(void *isa, int rd1, int rs1, int imm);
void nop(void *isa);
void lsri(void *isa, int rd1, int rs1, int imm);
void lsli(void *isa, int rd1, int rs1, int imm);
void xor_(void *isa, int rd1, int rs1, int rs2);
void xorw(void *isa, int rd1, int rs1, int rs2);
void and_(void *isa, int rd1, int rs1, int rs2);
void or_(void *isa, int rd1, int rs1, int rs2);
void ror(void *isa, int rd1, int rs1, int rs2);
void rori(void *isa, int rd1, int rs1, int imm);
void roli(void *isa, int rd1, int rs1, int imm);
void add(void *isa, int rd1, int rs1, int rs2);
void addi(void *isa, int rd1, int rs1, int imm);
void sub(void *isa, int rd1, int rs1, int rs2);
void mul(void *isa, int rd1, int rs1, int rs2);
void mulh_(void *isa, int rd1, int rs1, int rs2);
void mulhu(void *isa, int rd1, int rs1, int rs2);
void vsetivli(void *isa, int rd1, int uimm, int zimm);
void vls_ustride(void *isa, int mode, int vd1, int rs1, int width, int nf,
                 int mop, int vm, int umop);
void vle(void *isa, int width, int vd1, int rs1, int offset, int vm);
void vse(void *isa, int width, int vd1, int rs1, int offset, int vm);
void dumpVx(void *isa, int rd1, int width);
void dumpVregs(void *isa);
void vmv(void *isa, int mode, int rd, int rs1, int imm);
void vmvxs(void *isa, int mode, int rd, int imm, int rs2);
void vmvvi(void *isa, int mode, int rd, int imm, int rs2);
void vmvr(void *isa, int mode, int rd, int imm, int rs2);
void vslide1down(void *isa, int mode, int rd, int rs1, int rs2);
void vfwcvt(void *isa, int mode, int rd, int imm, int rs2);
void _vld(void *isa, int width, int rd1, int rs1, int offs);
void vld(void *isa, int rd1, int rs1, int offs);
void vldp(void *isa, int rd1, int rd2, int rs1, int offs);
void vldpw(void *isa, int rd1, int rs1, int offs);
void vsdp(void *isa, int rd1, int rd2, int rs1, int offs);
void vbitmask(void *isa, int rd, int imm, int w, int sl, int n);
void vand(void *isa, int rd1, int rs1, int rs2);
void vor(void *isa, int rd1, int rs1, int rs2);
void vfswap(void *isa, int rd1);
void vfadd(void *isa, int rd1, int rs1, int rs2);
void vfsub(void *isa, int rd1, int rs1, int rs2);
void vfxor(void *isa, int rd1, int rs1, int rs2);
void vfmul(void *isa, int rd1, int rs1, int rs2);
void vfdiv(void *isa, int rd1, int rs1, int rs2);
void vfsqrt(void *isa, int rd1, int rs1);
void sfrm(void *isa, int rs1);
void brk(void *isa);
void b(void *isa, int offs);
void blt(void *isa, int rs1, int rs2, int offs);
void beq(void *isa, int rs1, int rs2, int offs);
void auipc(void *isa, int rd1, int offs);
void entry(void *isa);
void exit_(void *isa);
static void lsr(void *isa, int rd1, int rs1, int rs2);
static void lsl(void *isa, int rd1, int rs1, int rs2);
static void subi(void *isa, int rd1, int rs1, int imm);
static void xori(void *isa, int rd1, int rs1, int imm);
static void fld(void *isa, int rd1, int rs1, int offs);
static void fsd(void *isa, int rs1, int rs2, int offs);
static void bitmask(void *isa, int rd, int imm, int w, int sl, int n);

void li(void *isa, int rd1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int u            = imm < 0 ? ~imm : imm;

  if (!(u >> 11))
    addi(dev, rd1, zero, imm);
  else {

    // LUI -- hi 20bits
    Type_U(dev, 0x37, rd1, imm, 1);

    if (!(imm & (1 << 11))) {
      // ORI
      Type_I(dev, 0x13, 6, rd1, rd1, imm, 1);
    } else {

      int t0 = allocX(dev);
      // ORI
      Type_I(dev, 0x13, 6, t0, zero, imm, 1);

      lsli(dev, t0, t0, 52);
      lsri(dev, t0, t0, 52);
      or_(dev, rd1, rd1, t0);
      freeX(dev, t0);
    }
  }
}

void li64(void *isa, int rd1, int64_t imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int64_t u        = imm < 0 ? ~imm : imm;

  if (!(u >> 32))
    li(dev, rd1, u);
  else {
    int t0 = allocX(dev);
    int t1 = allocX(dev);
    li(dev, t0, imm >> 31);
    lsli(dev, t0, t0, 31);
    li(dev, t1, imm & 0x7fffffff);
    or_(dev, rd1, t0, t1);
    freeX(dev, t0);
    freeX(dev, t1);
  }
}

void mov(void *isa, int rd, int rs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  addi(dev, rd, rs, 0);
}

// load & store
void prefetch(void *isa, int rs) {}
void ld(void *isa, int rd, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_L(dev, 3, 3, rd, rs1, offs, 3);
}
void sd(void *isa, int rs1, int rs2, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_S(dev, 0x23, 3, rs1, rs2, offs, 3);
}
void ldp(void *isa, int rd1, int rd2, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  ld(dev, rd1, rs1, offs);
  ld(dev, rd2, rs1, offs + 8);
}
void sdp(void *isa, int rs1, int rs2, int t, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  sd(dev, t, rs1, offs);
  sd(dev, t, rs2, offs + 8);
}

// bits
void andi(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int u            = imm < 0 ? ~imm : imm;
  if (!(u >> 11))
    Type_I(dev, 0x13, 7, rd1, rs1, imm, 1);
  else {
    int t = allocX(dev);
    li(dev, t, imm);
    and_(dev, rd1, rs1, t);
    freeX(dev, t);
  }
}

void nop(void *isa) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  addi(dev, zero, zero, 0);
}

void lsri(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_I(dev, 0x13, 5, rd1, rs1, imm, 1);
}
void lsli(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_I(dev, 0x13, 1, rd1, rs1, imm, 1);
}
void xor_(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 4, 0, rd1, rs1, rs2, 1);
}
void xorw(void *isa, int rd1, int rs1,
          int rs2) { // lo32 xor, hi32 remain unchanged
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int t            = allocX(dev);
  mov(dev, t, rs2);
  lsli(dev, t, t, 32);
  lsri(dev, t, t, 32);
  xor_(dev, rd1, rs1, t);
  freeX(dev, t);
}
void and_(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 7, 0, rd1, rs1, rs2, 1);
}
void or_(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 6, 0, rd1, rs1, rs2, 1);
}
void ror(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_ISA_B
  // ROR
  Type_R(dev, 0x33, 5, 0x30, rd1, rs1, rs2, 1);
#else
  int t0 = allocX(dev), t1 = allocX(dev);
  andi(dev, t0, rs2, 0x3f);
  lsr(dev, t1, rs1, t0);
  sub(dev, t0, zero, t0);
  andi(dev, t0, t0, 0x3f);
  lsl(dev, t0, rs1, t0);
  or_(dev, rd1, t1, t0);
  freeX(dev, t0);
  freeX(dev, t1);
#endif
}
void rol(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_ISA_B
  // ROL
  Type_R(dev, 0x33, 1, 0x30, rd1, rs1, rs2, 1);
#else
  int t0 = allocX(dev), t1 = allocX(dev);
  andi(dev, t0, rs2, 0x3f);
  lsl(dev, t1, rs1, t0);
  sub(dev, t0, zero, t0);
  andi(dev, t0, t0, 0x3f);
  lsr(dev, t0, rs1, t0);
  or_(dev, rd1, t1, t0);
  freeX(dev, t0);
  freeX(dev, t1);
#endif
}
void rori(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  imm &= 0x3f;

  if (!imm)
    return mov(dev, rd1, rs1);

#ifdef RV_ISA_B
  // RORI
  Type_I(dev, 0x13, 5, rd1, rs1, imm | 0x600, 1);
#else
  int t0 = allocX(dev);
  lsri(dev, t0, rs1, imm);
  lsli(dev, rd1, rs1, 64 - imm);
  or_(dev, rd1, rd1, t0);
  freeX(dev, t0);
#endif
}
void roli(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  imm &= 0x3f;
  imm = 64 - imm;
  rori(dev, rd1, rs1, imm);
}

// integer funcs
void add(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 0, 0, rd1, rs1, rs2, 1);
}
void addi(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int u            = imm < 0 ? ~imm : imm;

  if (!(u >> 11))
    Type_I(dev, 0x13, 0, rd1, rs1, imm, 1);
  else {
    int t = allocX(dev);
    li(dev, t, imm);
    add(dev, rd1, rs1, t);
    freeX(dev, t);
  }
}
void sub(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 0, 0x20, rd1, rs1, rs2, 1);
}
void mul(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 0, 1, rd1, rs1, rs2, 3);
}
void mulh_(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 1, 1, rd1, rs1, rs2, 3);
}
void mulhu(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 3, 1, rd1, rs1, rs2, 3);
}

// vector funcs
#define V2R(dev, r1) int r1##_0 = dev->M[r1] & 0xff, r1##_1 = dev->M[r1] >> 8
#define V2R2(dev, r1, r2)                                                      \
  V2R(dev, r1);                                                                \
  V2R(dev, r2)
#define V2R3(dev, r1, r2, r3)                                                  \
  V2R2(dev, r1, r2);                                                           \
  V2R(dev, r3)

#define Type_I_RII(dev, _op, _f, _rd, _zimm, _imm, _cy)                        \
  ENC(dev, _op | dev->M[_rd] << 7 | _f << 12 | _zimm << 15 | (_imm) << 20,     \
      D1(_rd), 3, _cy)

#define Type_R_RIR(dev, _op, _f, _f7, _rd, _imm, _rs2, _cy)                    \
  ENC(dev,                                                                     \
      _op | dev->M[_rd] << 7 | _f << 12 | _imm << 15 | dev->M[_rs2] << 20 |    \
          _f7 << 25,                                                           \
      D1S1(_rd, _rs2), 3, _cy)

#define Type_R_RRI(dev, _op, _f, _f7, _rd, _rs1, _imm, _cy)                    \
  ENC(dev,                                                                     \
      _op | dev->M[_rd] << 7 | _f << 12 | dev->M[_rs1] << 15 | _imm << 20 |    \
          _f7 << 25,                                                           \
      D1S1(_rd, _rs1), 3, _cy)

#define Type_I_IRI(dev, _op, _f, _rd, _rs, _imm, _cy)                          \
  ENC(dev, _op | _rd << 7 | _f << 12 | dev->M[_rs] << 15 | (_imm) << 20,       \
      D1S1(_rd, _rs), 3, _cy)

void vsetivli(void *isa, int rd1, int uimm, int zimm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_I_RII(dev, 0x57, 7, rd1, uimm, (0x3 << 10) | (zimm & 0x3ff), 1);
}

void vsetvli(void *isa, int rd1, int rs1, int zimm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_I_RII(dev, 0x57, 7, rd1, dev->M[rs1], (zimm & 0x7ff), 1);
}

void vls_ustride(void *isa, int mode, int vd1, int rs1, int width, int nf,
                 int mop, int vm, int umop) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int wmode;

  if (width == 8)
    wmode = 0;
  else {
    wmode = 5;
    while (width != 16) {
      width >>= 1;
      wmode++;
    }
  }

  Type_I(dev, ((mode == RV_LOAD) ? 0x7 : 0x27), (wmode & 0x7), vd1, rs1,
         (((nf << 9) | ((wmode >> 3) & 0x1) << 8) | ((mop & 0x3) << 6) |
          (vm << 5) | (umop & 0x1f)),
         (2 + nf));
}

void vle(void *isa, int width, int vd1, int rs1, int offset, int vm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int t0           = allocX(dev);
  addi(dev, t0, rs1, offset);
  vls_ustride(dev, RV_LOAD, vd1, t0, width, 0, 0, vm, 0);
  freeX(dev, t0);
}

void vse(void *isa, int width, int vd1, int rs1, int offset, int vm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int t0           = allocX(dev);
  addi(dev, t0, rs1, offset);
  vls_ustride(dev, RV_STORE, vd1, t0, width, 0, 0, vm, 0);
  freeX(dev, t0);
}

uint8_t dumpMem[10240];
int dumpMemOffs = 0;
void dumpVx(void *isa, int rd1, int width) {
#ifdef RV_TRUE_V_ISA
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int t0 = allocX(dev);
  li64(dev, t0, (int64_t)dumpMem);
  vse(dev, width, rd1, t0, dumpMemOffs, 1);
  dumpMemOffs += 16;
  freeX(dev, t0);
#endif
}

void dumpVregs(void *isa) {
#ifdef RV_TRUE_V_ISA
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int t0 = allocX(dev);
  int t1 = allocX(dev);
  int i;
  printf("dumpVx: 0x%lx\n", (int64_t)dumpMem);
  li64(dev, t0, (int64_t)dumpMem);
  for (i = 0; i < 32; i++) {
    addi(dev, t1, t0, dumpMemOffs);
    // for 64bit width
    Type_I_IRI(dev, 0x27, (7 & 0x7), i, t1,
               (((0 << 9) | ((7 >> 3) & 0x1) << 8) | ((0 & 0x3) << 6) |
                (1 << 5) | (0 & 0x1f)),
               (2 + 0));
    dumpMemOffs += 16;
  }
  freeX(dev, t1);
  freeX(dev, t0);
#endif
}

void vmv(void *isa, int mode, int rd, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R_RRI(dev, 0x57, mode, ((VMV << 1) | 1), rd, rs1, imm, 3);
}

void vmvxs(void *isa, int mode, int rd, int imm, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R_RIR(dev, 0x57, mode, ((VWXUNARY0 << 1) | 1), rd, imm, rs2, 3);
}

void vmvvi(void *isa, int mode, int rd, int imm, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R_RIR(dev, 0x57, mode, ((VMV << 1) | 1), rd, imm, rs2, 3);
}

void vmvr(void *isa, int mode, int rd, int imm, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R_RIR(dev, 0x57, mode, ((VMVR << 1) | 1), rd, imm, rs2, 3);
}

void vslide1down(void *isa, int mode, int rd, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x57, mode, ((VSLIDE1DOWN << 1) | 1), rd, rs1, rs2, 3);
}

void vfwcvt(void *isa, int mode, int rd, int imm, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R_RIR(dev, 0x57, mode, ((VFUNARY0 << 1) | 1), rd, imm, rs2, 3);
}

void _vld(void *isa, int width, int rd1, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  vle(dev, width, rd1, rs1, offs, 1);
#else
  V2R(dev, rd1);

  fld(dev, rd1_0, rs1, offs);
  fld(dev, rd1_1, rs1, offs + 8);
#endif
}

void vld(void *isa, int rd1, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  _vld(dev, 64, rd1, rs1, offs);
}

void vldp(void *isa, int rd1, int rd2, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  // vsetivli zero, 2, e64, m1
  //vsetivli(dev, zero, 2, RV_SEW64 << 3);
	int t0 = allocV(dev);
	li(dev, t0, 2);
	vsetvli(dev, zero, t0, RV_SEW64 << 2);
	freeV(dev, t0);
#endif
  _vld(dev, 64, rd1, rs1, offs);
  _vld(dev, 64, rd2, rs1, offs + 16);
}

void vldpw(void *isa, int rd1, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#if 0
  int t0 = allocV(dev);
	int t1 = allocV(dev);
  // vsetivli zero, 2, e32, m1
	li(dev, t1, 2);
  //vsetivli(dev, zero, 2, RV_SEW32 << 3 | RV_LMUL_F2);
	vsetvli(dev, zero, t1, RV_SEW32 << 2);
  _vld(dev, 32, t0, rs1, offs);
  vfwcvt(dev, RV_OPFVV, rd1, 0xb, t0);
  //vsetivli(dev, zero, 2, RV_SEW64 << 3);
	vsetvli(dev, zero, t1, RV_SEW64 << 2);
	freeV(dev, t1);
  freeV(dev, t0);
#else
  int t0 = allocX(dev);
  V2R(dev, rd1);

  // LW, FCVT_D_W
  ld(dev, t0, rs1, offs);
  Type_I(dev, 0x53, 7, rd1_0, t0, 0xd20, 2);
  lsri(dev, t0, t0, 32);
  Type_I(dev, 0x53, 7, rd1_1, t0, 0xd20, 2);

  freeX(dev, t0);
#endif
}

void vsdp(void *isa, int rd1, int rd2, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  vse(dev, 64, rd1, rs1, offs, 1);
  vse(dev, 64, rd2, rs1, offs + 16, 1);
#else
  V2R2(dev, rd1, rd2);

  fsd(dev, rs1, rd1_0, offs);
  fsd(dev, rs1, rd1_1, offs + 8);
  fsd(dev, rs1, rd2_0, offs + 16);
  fsd(dev, rs1, rd2_1, offs + 24);
#endif
}

void vbitmask(void *isa, int rd, int imm, int w, int sl, int n) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifndef RV_TRUE_V_ISA
  V2R(dev, rd);

  if (dev->M[rd] < 0xff)
    return bitmask(dev, rd, imm, w, sl, n);
#endif

  int t0 = allocX(dev);
  li(dev, t0, n ? ~imm : imm);
  lsli(dev, t0, t0, sl);
  if (n)
    xori(dev, t0, t0, -1);

#ifdef RV_TRUE_V_ISA
  vmv(dev, RV_OPIVX, rd, t0, 0);
#else
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd_0, t0, 0xf20, 6);
  Type_I(dev, 0x53, 0, rd_1, t0, 0xf20, 6);
#endif
  freeX(dev, t0);
}

void vand(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  // vand
  Type_R(dev, 0x57, RV_OPIVV, ((VAND << 1) | 1), rd1, rs1, rs2, 3);
#else
  V2R2(dev, rd1, rs1);

  int t0 = allocX(dev);
  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rs1_0, 0xe20, 1);
  and_(dev, t0, t0, rs2);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_0, t0, 0xf20, 6);

  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rs1_1, 0xe20, 1);
  and_(dev, t0, t0, rs2);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_1, t0, 0xf20, 6);

  freeX(dev, t0);
#endif
}

void vor(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R(dev, 0x57, RV_OPIVV, ((VOR << 1) | 1), rd1, rs1, rs2, 3);
#else
  V2R3(dev, rd1, rs1, rs2);

  int t0 = allocX(dev), t1 = allocX(dev);
  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rs1_0, 0xe20, 1);
  Type_I(dev, 0x53, 0, t1, rs2_0, 0xe20, 1);
  or_(dev, t0, t0, t1);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_0, t0, 0xf20, 6);

  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rs1_1, 0xe20, 1);
  Type_I(dev, 0x53, 0, t1, rs2_1, 0xe20, 1);
  or_(dev, t0, t0, t1);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_1, t0, 0xf20, 6);

  freeX(dev, t0);
  freeX(dev, t1);
#endif
}

void vfswap(void *isa, int rd1) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  int t0 = allocV(dev);
  int x0 = allocX(dev);

  // vmv.x.s x0, rd1
  vmvxs(dev, RV_OPMVV, x0, 0, rd1);
  // vslide1down.vx t0, rd1, x0
  vslide1down(dev, RV_OPMVX, t0, x0, rd1);
  // vmv1r.v rd1, t0
  vmvr(dev, RV_OPIVI, rd1, RV_VMVR_1, t0);
  freeX(dev, x0);
  freeV(dev, t0);
#else
  V2R(dev, rd1);

  int t0 = allocX(dev);

  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rd1_0, 0xe20, 1);
  // FSGNJ.D
  Type_R(dev, 0x53, 0, 0x11, rd1_0, rd1_1, rd1_1, 2);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_1, t0, 0xf20, 6);

  freeX(dev, t0);
#endif
}

void vfadd(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R(dev, 0x57, RV_OPFVV, ((VFADD << 1) | 1), rd1, rs2, rs1, 3);
#else
  V2R3(dev, rd1, rs1, rs2);

  // FADD.D
  Type_R(dev, 0x53, 7, 1, rd1_0, rs1_0, rs2_0, 7);
  Type_R(dev, 0x53, 7, 1, rd1_1, rs1_1, rs2_1, 7);
#endif
}

void vfsub(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R(dev, 0x57, RV_OPFVV, ((VFSUB << 1) | 1), rd1, rs2, rs1, 3);
#else
  V2R3(dev, rd1, rs1, rs2);

  // FSUB.D
  Type_R(dev, 0x53, 7, 5, rd1_0, rs1_0, rs2_0, 7);
  Type_R(dev, 0x53, 7, 5, rd1_1, rs1_1, rs2_1, 7);
#endif
}

void vfxor(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R(dev, 0x57, RV_OPIVV, ((VXOR << 1) | 1), rd1, rs2, rs1, 3);
#else
  V2R3(dev, rd1, rs1, rs2);

  int t0 = allocX(dev), t1 = allocX(dev);
  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rs1_0, 0xe20, 1);
  Type_I(dev, 0x53, 0, t1, rs2_0, 0xe20, 1);
  xor_(dev, t0, t0, t1);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_0, t0, 0xf20, 6);

  // FMV.X.D
  Type_I(dev, 0x53, 0, t0, rs1_1, 0xe20, 1);
  Type_I(dev, 0x53, 0, t1, rs2_1, 0xe20, 1);
  xor_(dev, t0, t0, t1);
  // FMV.D.X
  Type_I(dev, 0x53, 0, rd1_1, t0, 0xf20, 6);

  freeX(dev, t0);
  freeX(dev, t1);
#endif
}

void vfmul(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R(dev, 0x57, RV_OPFVV, ((VFMUL << 1) | 1), rd1, rs2, rs1, 3);
#else
  V2R3(dev, rd1, rs1, rs2);

  // FMUL.D
  Type_R(dev, 0x53, 7, 9, rd1_0, rs1_0, rs2_0, 7);
  Type_R(dev, 0x53, 7, 9, rd1_1, rs1_1, rs2_1, 7);
#endif
}

void vfdiv(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R(dev, 0x57, RV_OPFVV, ((VFDIV << 1) | 1), rd1, rs2, rs1, 11);
  // dumpVx(rd1);
#else
  V2R3(dev, rd1, rs1, rs2);

  // FDIV.D
  Type_R(dev, 0x53, 7, 13, rd1_0, rs1_0, rs2_0, 35); // 9 ~ 58
  Type_R(dev, 0x53, 7, 13, rd1_1, rs1_1, rs2_1, 35);
#endif
}

void vfsqrt(void *isa, int rd1, int rs1) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
#ifdef RV_TRUE_V_ISA
  Type_R_RIR(dev, 0x57, RV_OPFVV, ((VFUNARY1 << 1) | 1), rd1, 0, rs1, 10);
#else
  V2R2(dev, rd1, rs1);

  // FSQRT.D
  Type_R(dev, 0x53, 7, 0x2d, rd1_0, rs1_0, 0, 35); // 9 ~ 57
  Type_R(dev, 0x53, 7, 0x2d, rd1_1, rs1_1, 0, 35);
#endif
}

// 00 even, 01 -, 02 +, 03 zeros
void sfrm(void *isa, int rs1) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int t0 = allocX(dev), t1 = allocX(dev);

  li(dev, t1, 0x78);
  andi(dev, t0, rs1, 3);
  lsli(dev, t0, t0, 1);
  lsr(dev, t1, t1, t0);
  andi(dev, t1, t1, 3);

  // CSRRW
  Type_I(dev, 0x73, 1, zero, t1, 2, 1);
  freeX(dev, t0);
  freeX(dev, t1);
}

// control
void brk(void *isa) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  return;
  Type_I(dev, 0x73, 0, 0, 0, 1, 0);
}

void b(void *isa, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  // JAL
  Type_J(dev, 0x6f, zero, offs, 1);
}

void blt(void *isa, int rs1, int rs2, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int u            = offs < 0 ? ~offs : offs;

  if (!(u >> 12))
    // BLT
    Type_B(dev, 0x63, 4, rs1, rs2, offs, 1);

  else {
    // BGE
    Type_B(dev, 0x63, 5, rs1, rs2, 8, 1);
    b(dev, offs - 4);
  }
}

void beq(void *isa, int rs1, int rs2, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int u            = offs < 0 ? ~offs : offs;
  if (!(u >> 12))
    // BEQ
    Type_B(dev, 0x63, 0, rs1, rs2, offs, 1);
  else {
    // BNE
    Type_B(dev, 0x63, 1, rs1, rs2, 8, 1);
    b(dev, offs - 4);
  }
}

void bne(void *isa, int rs1, int rs2, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int u            = offs < 0 ? ~offs : offs;
  if (!(u >> 12))
    Type_B(dev, 0x63, 1, rs1, rs2, offs, 1);
  else {
    Type_B(dev, 0x63, 0, rs1, rs2, 8, 1);
    b(dev, offs - 4);
  }
}

void auipc(void *isa, int rd1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_U(dev, 0x17, rd1, 0, 1);
  addi(dev, rd1, rd1, offs);
}

void entry(void *isa) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int spi          = 0;

  subi(dev, sp, sp, 300);

  sd(dev, sp, 1, spi);
  sd(dev, sp, 2, spi + 8);
  sd(dev, sp, 8, spi + 16);
  sd(dev, sp, 9, spi + 24);

  spi += 32;
  for (int i = 18; i <= 27; i++) {
    sd(dev, sp, i, spi);
#ifndef RV_TRUE_V_ISA
    fsd(dev, sp, i, spi + 8);
    spi += 16;
#else
    spi += 8;
#endif
  }
#ifndef RV_TRUE_V_ISA
  fsd(dev, sp, 8, spi);
  fsd(dev, sp, 9, spi + 8);
#endif
}

void ret(void *isa) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  // jalr x0, x1, 0
  Type_U(dev, 0x8067, 0, 0, 1);
}

void exit_(void *isa) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  int spi          = 0;

  ld(dev, 1, sp, spi);
  ld(dev, 2, sp, spi + 8);
  ld(dev, 8, sp, spi + 16);
  ld(dev, 9, sp, spi + 24);

  spi += 32;
  for (int i = 18; i <= 27; i++) {
    ld(dev, i, sp, spi);
#ifndef RV_TRUE_V_ISA
    fld(dev, i, sp, spi + 8);
    spi += 16;
#else
    spi += 8;
#endif
  }
#ifndef RV_TRUE_V_ISA
  fld(dev, 8, sp, spi);
  fld(dev, 9, sp, spi + 8);
#endif

  addi(dev, sp, sp, 300);

  // JALR
  Type_U(dev, 0x8067, 0, 0, 1);
}

static void lsr(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 5, 0, rd1, rs1, rs2, 1);
}
static void lsl(void *isa, int rd1, int rs1, int rs2) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_R(dev, 0x33, 1, 0, rd1, rs1, rs2, 1);
}
static void subi(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  addi(dev, rd1, rs1, -imm);
}
static void xori(void *isa, int rd1, int rs1, int imm) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_I(dev, 0x13, 4, rd1, rs1, imm, 1);
}
static void fld(void *isa, int rd1, int rs1, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_L(dev, 7, 3, rd1, rs1, offs, 2);
}
static void fsd(void *isa, int rs1, int rs2, int offs) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  Type_S(dev, 0x27, 3, rs1, rs2, offs, 4);
}
static void bitmask(void *isa, int rd, int imm, int w, int sl, int n) {
  isa_rv64g_t *dev = (isa_rv64g_t *)isa;
  li(dev, rd, n ? ~imm : imm);
  lsli(dev, rd, rd, sl);
  if (n)
    xori(dev, rd, rd, -1);
}

static int hasPrefetch() { return 0; }

instruction_ops_t isa_rv64g = {
    .li          = li,
    .mov         = mov,
    .prefetch    = prefetch,
    .ld          = ld,
    .sd          = sd,
    .ldp         = ldp,
    .sdp         = sdp,
    .andi        = andi,
    .lsri        = lsri,
    .lsli        = lsli,
    .xor_        = xor_,
    .xorw        = xorw,
    .and_        = and_,
    .or_         = or_,
    .ror         = ror,
    .rol         = rol,
    .rori        = rori,
    .roli        = roli,
    .add         = add,
    .addi        = addi,
    .sub         = sub,
    .mul         = mul,
    .mulh        = mulh_,
    .mulhu       = mulhu,
    .vldpw       = vldpw,
    .vld         = vld,
    .vldp        = vldp,
    .vsdp        = vsdp,
    .vbitmask    = vbitmask,
    .vand        = vand,
    .vor         = vor,
    .vfswap      = vfswap,
    .vfadd       = vfadd,
    .vfsub       = vfsub,
    .vfxor       = vfxor,
    .vfmul       = vfmul,
    .vfdiv       = vfdiv,
    .vfsqrt      = vfsqrt,
    .sfrm        = sfrm,
    .brk         = brk,
    .b           = b,
    .blt         = blt,
    .beq         = beq,
    .bne         = bne,
    .auipc       = auipc,
    .ret         = ret,
    .entry       = entry,
    .exit        = exit_,
    .nop         = nop,
    .hasPrefetch = hasPrefetch,
};
