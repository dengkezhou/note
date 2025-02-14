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
#include "isa-a64.h"
#include "jrx_base.h"
#include <stdint.h>

#define IR(_i, _c) static uint32_t _i = _c
IR(MOVZ, 0xd28);
IR(MOVN, 0x928);
IR(MOVK, 0xf28);

isa_a64_t *initIsaA64(int size, uint8_t *c, int *slots, uint8_t *d) {
  isa_a64_t *dev = initJrxBase(size, c, slots, d);

  dev->name = "aarch64";
  // x regs
  dev->M[rf] = 0; // arg0 -> p1
  dev->M[mm] = 1; // arg1 -> dataset
  dev->M[sc] = 2; // arg2
  dev->M[ic] = 3; // arg3
  // M[zero] = 4;
  dev->M[sp0]  = 5;
  dev->M[sp1]  = 6;
  dev->M[mxa]  = 7;
  dev->M[zero] = 8;
  dev->M[xtmp] = 9;
  dev->M[r0]   = 10;
  dev->M[r1]   = 11;
  dev->M[r2]   = 12;
  dev->M[r3]   = 13;
  dev->M[r4]   = 14;
  dev->M[r5]   = 15;
  dev->M[r6]   = 16;
  dev->M[r7]   = 17;
  for (int i = 18; i < 31; i++)
    dev->M[xpool + i - 18] = i;
  dev->M[sp] = 31;

  // v regs
  dev->M[e0]    = 0;
  dev->M[e1]    = 1;
  dev->M[e2]    = 2;
  dev->M[e3]    = 3;
  dev->M[f0]    = 4;
  dev->M[f1]    = 5;
  dev->M[f2]    = 6;
  dev->M[f3]    = 7;
  dev->M[a0]    = 8;
  dev->M[a1]    = 9;
  dev->M[a2]    = 10;
  dev->M[a3]    = 11;
  dev->M[vtmp]  = 12;
  dev->M[E_or]  = 13;
  dev->M[scale] = 14;
  dev->M[E_and] = 15;

  dev->ops = &isa_a64;
  return dev;
}

void exitIsaA64(isa_a64_t *dev) { exitJrxBase(dev); }

#define _U(dev, _op, _rd, _imm, _cy)                                           \
  ENC(dev, (_op) << 20 | dev->M[_rd] | (_imm) << 5, D1(_rd), 3, _cy)

#define _J(dev, _op, _rd, _imm, _cy)                                           \
  ENC(dev, (_op) << 20 | dev->M[_rd] | (_imm) << 5, -1, 3, _cy)

#define _I(dev, _op, _rd, _rn, _imm, _cy)                                      \
  ENC(dev, (_op) << 20 | dev->M[_rd] | dev->M[_rn] << 5 | (_imm) << 10,        \
      D1S1(_rd, _rn), 3, _cy)

#define _R(dev, _op, _f, _rd, _rn, _rm, _cy)                                   \
  ENC(dev,                                                                     \
      (_op) << 20 | dev->M[_rd] | dev->M[_rn] << 5 | _f << 10 |                \
          dev->M[_rm] << 16,                                                   \
      D1S2(_rd, _rn, _rm), 3, _cy)

#define _L(dev, _op, _rd, _rn, _offs, _cy)                                     \
  ENC(dev, (_op) << 20 | dev->M[_rd] | dev->M[_rn] << 5 | (_offs) << 10,       \
      D1S2(_rd, _rn, 0xfe), 4, _cy | 0xc0)

#define _S(dev, _op, _rd, _rn, _offs, _cy)                                     \
  ENC(dev, (_op) << 20 | dev->M[_rd] | dev->M[_rn] << 5 | (_offs) << 10,       \
      D1S2(0xfe, _rn, _rd), 5, _cy | 0xc0)

#define _LP(dev, _op, _rd, _rn, _rm, _offs, _cy)                               \
  ENC(dev,                                                                     \
      (_op) << 20 | dev->M[_rd] | dev->M[_rn] << 5 | dev->M[_rm] << 10 |       \
          (_offs) << 15,                                                       \
      D2S2(_rd, _rm, _rn, 0xfe), 4, _cy | 0xc0);

#define _SP(dev, _op, _rd, _rn, _rm, _offs, _cy)                               \
  ENC(dev,                                                                     \
      (_op) << 20 | dev->M[_rd] | dev->M[_rn] << 5 | dev->M[_rm] << 10 |       \
          (_offs) << 15,                                                       \
      D1S3(0xfe, _rm, _rn, _rd), 5, _cy | 0xc0);

static void li(void *isa, int rd1, int imm);
static void mov(void *isa, int rd, int rs);
static void prefetch(void *isa, int rn);
static void ld(void *isa, int rd, int rn, int offs);
static void sd(void *isa, int rd, int rn, int offs);
static void ldp(void *isa, int rd1, int rd2, int rn, int offs);
static void sdp(void *isa, int rn, int rm, int t, int offs);
static void andi(void *isa, int rd1, int rn, int imm);
static void lsri(void *isa, int rd1, int rn, int imm);
static void lsli(void *isa, int rd1, int rn, int imm);
static void xor_(void *isa, int rd1, int rn, int rm);
static void xorw(void *isa, int rd1, int rn, int rm);
static void and_(void *isa, int rd1, int rn, int rm);
static void or_(void *isa, int rd1, int rn, int rm);
static void ror(void *isa, int rd1, int rn, int rm);
static void rol(void *isa, int rd1, int rn, int rm);
static void rori(void *isa, int rd1, int rn, int imm);
static void roli(void *isa, int rd1, int rn, int imm);
static void add(void *isa, int rd1, int rn, int rm);
static void addi(void *isa, int rd1, int rn, int imm);
static void sub(void *isa, int rd1, int rn, int rm);
static void mul(void *isa, int rd1, int rn, int rm);
//static void mulh(void *isa, int rd1, int rn, int rm);
static void mulhu(void *isa, int rd1, int rn, int rm);
static void vldpw(void *isa, int vd1, int rn, int offs);
static void vld(void *isa, int vd1, int rn, int offs);
static void vldp(void *isa, int vd1, int vd2, int rn, int offs);
static void vsdp(void *isa, int vs1, int vs2, int rd1, int offs);
static void vbitmask(void *isa, int vd, int imm, int w, int sl, int n);
static void vand(void *isa, int vd1, int vs1, int vs2);
static void vor(void *isa, int vd1, int vs1, int vs2);
static void vfswap(void *isa, int vd);
static void vfadd(void *isa, int vd1, int vs1, int vs2);
static void vfsub(void *isa, int vd1, int vs1, int vs2);
static void vfxor(void *isa, int vd1, int vs1, int vs2);
static void vfmul(void *isa, int vd1, int vs1, int vs2);
static void vfdiv(void *isa, int vd1, int vs1, int vs2);
static void vfsqrt(void *isa, int vd1, int vs1);
static void sfrm(void *isa, int rn);
static void brk(void *isa);
static void b(void *isa, int offs);
static void blt(void *isa, int rn, int rm, int offs);
static void beq(void *isa, int rn, int rm, int offs);
static void auipc(void *isa, int rd1, int offs);

static void li(void *isa, int rd1, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;

  if (!(imm >> 16))
    _U(dev, MOVZ, rd1, imm, 1);
  else {
    if (imm < 0)
      // movn tmp_reg, ~imm32 (16 high bits)
      _U(dev, MOVN | 2, rd1, ~imm >> 16, 1);
    else
      // movz tmp_reg, imm32 (16 high bits)
      _U(dev, MOVZ | 2, rd1, imm >> 16, 1);

    // movk tmp_reg, imm32 (16 low bits)
    _U(dev, MOVK, rd1, imm & 0xffff, 1);
  }
}

static void mov(void *isa, int rd, int rs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  if (dev->M[rd] != dev->M[rs])
    or_(isa, rd, rs, zero);
}

// load & store
static int hasPrefetch() { return 1; }
static void prefetch(void *isa, int rn) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // PRFM
  _I(dev, 0xf98, 2, rn, 0, 1);
}
static void ld(void *isa, int rd, int rn, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;

  if (offs >= 0)
    _L(dev, 0xf94, rd, rn, offs >> 3, 2); // LDR unsigned
  else {
    int t0 = allocX(dev);
    li(dev, t0, offs >> 3);
    _R(dev, 0xf86, 0x1e, rd, rn, t0, 2); // LDR reg
    freeX(dev, t0);
  }
}
static void sd(void *isa, int rd, int rn, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;

  if (offs >= 0)
    _S(dev, 0xf90, rn, rd, offs >> 3, 1); // STR
  else {
    int t0 = allocX(dev);
    li(dev, t0, offs >> 3);
    _R(dev, 0xf82, 0x1e, rn, rd, t0, 1); // LDR reg
    freeX(dev, t0);
  }
}
static void ldp(void *isa, int rd1, int rd2, int rn, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _LP(dev, 0xa94, rd1, rn, rd2, offs >> 3, 2);
}
static void sdp(void *isa, int rn, int rm, int t, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _SP(dev, 0xa90, rn, t, rm, offs >> 3, 1);
}

// bits
static void andi(void *isa, int rd1, int rn, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // FIXME
  int t = allocX(dev);
  li(dev, t, imm);
  and_(dev, rd1, rn, t);
  freeX(dev, t);
}

static void lsri(void *isa, int rd1, int rn, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  imm &= 0x3f;
  if (!imm)
    return mov(dev, rd1, rn);
  _I(dev, 0xd34, rd1, rn, imm << 6 | 0x3f, 1);
}
static void lsli(void *isa, int rd1, int rn, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  imm            = 64 - (imm & 0x3f);
  if (!imm)
    return mov(dev, rd1, rn);
  _I(dev, 0xd34, rd1, rn, imm << 6 | (imm - 1), 1);
}
static void xor_(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0xca0, 0, rd1, rn, rm, 1);
}
static void xorw(void *isa, int rd1, int rn,
                 int rm) { // lo32 xor, hi32 remain unchanged
  isa_a64_t *dev = (isa_a64_t *)isa;
  int t0         = allocX(dev);
  lsli(dev, t0, rm, 32);
  lsri(dev, t0, t0, 32);
  xor_(dev, rd1, rn, t0);
  // _R(0x4a0, 0, rd1, rn, rm, 1);
  freeX(dev, t0);
}
static void and_(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0x8a0, 0, rd1, rn, rm, 1);
}
static void or_(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0xaa0, 0, rd1, rn, rm, 1);
}
static void ror(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0x9ac, 0xb, rd1, rn, rm, 1);
}
static void rol(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  int t0         = allocX(dev);
  sub(dev, t0, zero, rm);
  ror(dev, rd1, rn, t0);
  freeX(dev, t0);
}
static void rori(void *isa, int rd1, int rn, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  imm &= 0x3f;
  if (!imm)
    return mov(dev, rd1, rn);
  // ROR i
  _R(dev, 0x93c, imm, rd1, rn, rn, 1);
}
static void roli(void *isa, int rd1, int rn, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  imm            = 64 - (imm & 0x3f);
  rori(dev, rd1, rn, imm);
}

// integer funcs
static void add(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0x8b0, 0, rd1, rn, rm, 1);
}
static void addi(void *isa, int rd1, int rn, int imm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  uint32_t u = imm < 0 ? -imm : imm, lo = u & 0xfff, hi = u >> 12;
  if (!(u >> 24)) {
    if (lo)
      _I(dev, 0x910 | ((imm < 0) << 10), rd1, rn, lo, 1); // add/sub lo
    if (hi)
      _I(dev, 0x914 | ((imm < 0) << 10), rd1, lo ? rd1 : rn, hi,
         1); // add/sub hi
  } else {
    int t = allocX(dev);
    li(dev, t, imm);
    add(dev, rd1, rn, t);
    freeX(dev, t);
  }
}
static void sub(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0xcb0, 0, rd1, rn, rm, 1);
}
static void mul(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0x9b0, 0x1f, rd1, rn, rm, 3);
}
static void mulh_(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0x9b4, 0x1f, rd1, rn, rm, 3);
}
static void mulhu(void *isa, int rd1, int rn, int rm) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0x9bc, 0x1f, rd1, rn, rm, 3);
}

// vector funcs
static void vldpw(void *isa, int vd1, int rn, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  int t0 = allocX(dev), t1 = allocX(dev);

  // ldpsw tmp_reg, tmp_reg + 1, [tmp_reg]
  _LP(dev, 0x694, t0, rn, t1, offs >> 2, 1);

  // ins vd[0], vd[1] <== t0, t1  x10_0000_0111
  _I(dev, 0x4e0, vd1, t0, 0x207, 1);
  _I(dev, 0x4e1, vd1, t1, 0x207, 1);

  // scvtf
  _I(dev, 0x4e6, vd1, vd1, 0x76, 1);

  freeX(dev, t0);
  freeX(dev, t1);
}

static void vld(void *isa, int vd1, int rn, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // LDR
  _L(dev, 0x3dc, vd1, rn, offs >> 4, 2);
}

static void vldp(void *isa, int vd1, int vd2, int rn, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // LDP
  _LP(dev, 0xad4, vd1, rn, vd2, offs >> 4, 4);
}

static void vsdp(void *isa, int vs1, int vs2, int rd1, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // STP
  _SP(dev, 0xad0, vs1, rd1, vs2, offs >> 4, 2);
}

static void vbitmask(void *isa, int vd, int imm, int w, int sl, int n) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  uint64_t u     = (n ? ~imm : imm) & ((1 << w) - 1);

  int t0 = allocX(dev);

  if (sl >= 48)
    _U(dev, n ? 0x92e : 0xd2e, t0, u << (sl - 48), 1);
  else
    ASSERT(NULL == "can not form bitmask");

  // ins vd[0], vd[1] <== t0, t1
  _I(dev, 0x4e0, vd, t0, 0x81c >> 2, 1);
  _I(dev, 0x4e1, vd, t0, 0x81c >> 2, 1);
  freeX(dev, t0);
}

static void vand(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // AND v
  _R(dev, 0x4e2, 7, vd1, vs1, vs2, 1 | 0x80);
}

static void vor(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // OR v
  _R(dev, 0x4ea, 7, vd1, vs1, vs2, 1 | 0x80);
}

static void vfswap(void *isa, int vd) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  int t0         = allocX(dev);

  // MOV t0 <== vd[0]
  _I(dev, 0x4e0, t0, vd, 0x20f, 1);

  // MOV vd[0] <== vd[1] 01000_0_1000_1
  _I(dev, 0x6e0, vd, vd, 0x211, 1 | 0x80);

  // MOV vd[1] <== t0  11000_000111
  _I(dev, 0x4e0, vd, t0, 0x607, 1);

  freeX(dev, t0);
}

static void vfadd(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // ADD v
  _R(dev, 0x4e6, 0x35, vd1, vs1, vs2, 7 | 0x80);
}

static void vfsub(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // SUB v
  _R(dev, 0x4ee, 0x35, vd1, vs1, vs2, 7 | 0x80);
}

static void vfxor(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // XOR v
  _R(dev, 0x6e2, 7, vd1, vs1, vs2, 1 | 0x80);
}

static void vfmul(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // FMUL v
  _R(dev, 0x6e6, 0x37, vd1, vs1, vs2, 7 | 0x80);
}

static void vfdiv(void *isa, int vd1, int vs1, int vs2) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // FMUL v
  _R(dev, 0x6e6, 0x3f, vd1, vs1, vs2, 35 | 0x80);
}

static void vfsqrt(void *isa, int vd1, int vs1) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // FSQRT v
  _I(dev, 0x6ee, vd1, vs1, 0x1f8 >> 2, 35 | 0x80);
}

// 00 even, 01 -, 02 +, 03 zeros
static void sfrm(void *isa, int rn) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  int t0         = allocX(dev);

  li(dev, t0, 0);
  _I(dev, 0xb35, t0, rn, 0x201, 1); // BFI, 40, 2, from rn
  _I(dev, 0xdac, t0, t0, 0, 1);     // RBIT
  _U(dev, 0xd51, t0, 0x5a20, 1);    // MSR FPCR

  freeX(dev, t0);
}

// control
static void brk(void *isa) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  return;
  _U(dev, 0xd42, 0, 0, 0);
}

static void b(void *isa, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  // JAL
  ENC(dev, 0x14000000 | CUT(offs, 2, 26, 0), -1, 3, 1);
}

static void blt(void *isa, int rn, int rm, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0xeb2, 0x18, 31, rn, rm, 1);
  _J(dev, 0x540, 0xb, CUT(offs - 4, 2, 19, 0), 1);
}

static void beq(void *isa, int rn, int rm, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _R(dev, 0xeb2, 0x18, 31, rn, rm, 1);
  _J(dev, 0x540, 0, CUT(offs - 4, 2, 19, 0), 1);
}

static void auipc(void *isa, int rd1, int offs) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  _U(dev, 0x100, rd1, CUT(offs, 2, 19, 0), 1);
}

static void entry(void *isa) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  int spi        = 16;

  brk(dev);

  addi(dev, sp, sp, -256);

  sd(dev, sp, 8, 0);
  sd(dev, sp, 30, 8);
  for (int i = 16; i < 29; i += 2, spi += 16)
    sdp(dev, i, i + 1, sp, spi);

  vsdp(dev, 8, 9, sp, spi);
  vsdp(dev, 10, 11, sp, spi + 32);
  vsdp(dev, 12, 13, sp, spi + 64);
  vsdp(dev, 14, 15, sp, spi + 96);

  li(dev, zero, 0);
}

static void exit_(void *isa) {
  isa_a64_t *dev = (isa_a64_t *)isa;
  int spi        = 16;

  ld(dev, 8, sp, 0);
  ld(dev, 30, sp, 8);
  for (int i = 16; i < 29; i += 2, spi += 16)
    ldp(dev, i, i + 1, sp, spi);

  vld(dev, 8, sp, spi);
  vld(dev, 9, sp, spi + 16);
  vldp(dev, 10, 11, sp, spi + 32);
  vldp(dev, 12, 13, sp, spi + 64);
  vldp(dev, 14, 15, sp, spi + 96);

  addi(dev, sp, sp, 256);

  // JALR
  _U(dev, 0xd65, 0, 0x781e, 1);
}

instruction_ops_t isa_a64 = {
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
    .auipc       = auipc,
    .entry       = entry,
    .exit        = exit_,
    .hasPrefetch = hasPrefetch,
};
