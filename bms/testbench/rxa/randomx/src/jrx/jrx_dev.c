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

#include <stdint.h>

#include "bytecode_machine.h"
#include "rxa_common.h"
#include "isa.h"
#include "jrx_base.h"
#include "jrx_core.h"
#include "jrx_dev.h"
#include "program.h"
#include "virtual_memory.h"
#include <superscalar.h>

#define JRX_SIZE_P0 0x800
#define JRX_SIZE_P1 0x2000
#define JRX_SIZE_P2 0x800
#define JRX_SIZE_P3 0x1000 // for LITERALPOOL
#define JRX_SIZE_P4 0x200
#define JRX_SIZE_P5 0x10000
#define JRX_SIZE_P6 0x200
#define JRX_SIZE                                                               \
  (JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 + JRX_SIZE_P3 + JRX_SIZE_P4 +       \
   JRX_SIZE_P5 + JRX_SIZE_P6)

void dumpReg(void *dev, uint8_t opcode, int indicator);
void encode(jrx_dev_t *dev, Instruction_t *instr, int pc);

void *initJrx(int id) {
  jrx_dev_t *dev = (jrx_dev_t *)allocMemoryPages(sizeof(jrx_dev_t));
  if (!dev) {
    printf("Jrx dev malloc Error\n");
    return NULL;
  }

  memset(dev, 0, sizeof(jrx_dev_t));
#if defined(__aarch64__)
  // #if 1
  dev->mode = ISA_A64;
#elif defined(__riscv)
  dev->mode = ISA_RV64G;
#else
  dev->mode = ISA_A64;
#endif
  dev->code     = (uint8_t *)allocMemoryPages(JRX_SIZE);
  uint8_t *dlog = NULL;
  dev->p0       = initIsa(dev->mode, JRX_SIZE_P0, dev->code, dev->slots, dlog);
  dev->p1 = initIsa(dev->mode, JRX_SIZE_P1, dev->code + JRX_SIZE_P0, dev->slots,
                    dlog ? dlog + 2 * JRX_SIZE_P0 : dlog);
  dev->p2 =
      initIsa(dev->mode, JRX_SIZE_P2, dev->code + JRX_SIZE_P0 + JRX_SIZE_P1,
              dev->slots, dlog ? dlog + 2 * (JRX_SIZE_P0 + JRX_SIZE_P1) : dlog);
  dev->p3 = initIsa(
      dev->mode, JRX_SIZE_P3,
      dev->code + JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2, dev->slots,
      dlog ? dlog + 2 * (JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2) : dlog);
  dev->p4 = initIsa(
      dev->mode, JRX_SIZE_P4,
      dev->code + JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 + JRX_SIZE_P3,
      dev->slots,
      dlog ? dlog + 2 * (JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 + JRX_SIZE_P3)
           : dlog);
  dev->p5 = initIsa(dev->mode, JRX_SIZE_P5,
                    dev->code + JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 +
                        JRX_SIZE_P3 + JRX_SIZE_P4,
                    dev->slots,
                    dlog ? dlog + 2 * (JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 +
                                       JRX_SIZE_P3 + JRX_SIZE_P4)
                         : dlog);
  dev->p6 = initIsa(dev->mode, JRX_SIZE_P6,
                    dev->code + JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 +
                        JRX_SIZE_P3 + JRX_SIZE_P4 + JRX_SIZE_P5,
                    dev->slots,
                    dlog ? dlog + 2 * (JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 +
                                       JRX_SIZE_P3 + JRX_SIZE_P4 + JRX_SIZE_P5)
                         : dlog);

  printf("JRX using %s: %p\n", ((jrx_base_t *)(dev->p0))->name, dev->code);
  return dev;
}

void exitJrx(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
  exitIsa(dev->mode, dev->p0);
  exitIsa(dev->mode, dev->p1);
  exitIsa(dev->mode, dev->p2);
  exitIsa(dev->mode, dev->p3);
  exitIsa(dev->mode, dev->p4);
  exitIsa(dev->mode, dev->p5);
  exitIsa(dev->mode, dev->p6);
  freePagedMemory(dev->code, JRX_SIZE);
  freePagedMemory(dev, sizeof(jrx_dev_t));
}

void generateProgram(void *jrx, Program_t *program,
                     ProgramConfiguration_t *config) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
  jrx_base_t *p0 = (jrx_base_t *)dev->p0;
  jrx_base_t *p1 = (jrx_base_t *)dev->p1;
  jrx_base_t *p2 = (jrx_base_t *)dev->p2;

  Jrx_set_stage(PROGRAM);
  progN++;
  dev->literal_pos = JRX_SIZE_P0 - 8;
  for (int i = r0; i <= r7; i++)
    dev->dst_change[i] = 0;

  reset(p0);
  reset(p1);
  reset(p2);

  if (locked(p0)) {
    iseek(p0, dev->loop_start);
    p0->ops->xor_(dev->p0, dev->loop_start_t0, config->readReg0 + r0,
                  config->readReg1 + r0);
    iseek(p0, dev->load_start);
  } else {

    p0->ops->entry(dev->p0);

    // zero integer registers
    for (int i = 0; i < 8; i++)
      p0->ops->mov(dev->p0, r0 + i, zero);

    // load ma, mx and dataset pointer
    p0->ops->ldp(dev->p0, mxa, mm, mm, 0);

    // load reg.a
    p0->ops->vldp(dev->p0, a0, a1, rf, 192);
    p0->ops->vldp(dev->p0, a2, a3, rf, 224);

    // load E 'and' mask
    p0->ops->vbitmask(dev->p0, E_and, 0, 8, 56, 1);

    // load E 'or' mask
    p0->ops->vld(dev->p0, E_or, rf, 64);

    // load scale mask 0x80f0000000000000
    p0->ops->vbitmask(dev->p0, scale, 0x80f, 12, 52, 0);

    // save rf
    p0->ops->sd(dev->p0, sp, rf, -16);

    p0->ops->auipc(dev->p0, rf, -codeSize(p0)); // store p0->code to rf

    // init sp0, sp1
    int t0 = allocX(p0);
    p0->ops->mov(dev->p0, xtmp, mxa);

    dev->loop_start    = codeSize(p0);
    dev->loop_start_t0 = t0;
    p0->ops->xor_(dev->p0, t0, config->readReg0 + r0, config->readReg1 + r0);
    p0->ops->xor_(dev->p0, xtmp, xtmp, t0);

    p0->ops->li(dev->p0, t0, ScratchpadL3Mask64);
    p0->ops->and_(dev->p0, sp0, xtmp, t0);
    p0->ops->lsri(dev->p0, sp1, xtmp, 32);
    p0->ops->and_(dev->p0, sp1, sp1, t0);
    p0->ops->add(dev->p0, sp0, sp0, sc);
    p0->ops->add(dev->p0, sp1, sp1, sc);

    // 1. xor r0~r7
    for (int i = 0; i < 8; i += 2) {
      p0->ops->ldp(dev->p0, xtmp, t0, sp0, i * 8);
      p0->ops->xor_(dev->p0, r0 + i, r0 + i, xtmp);
      p0->ops->xor_(dev->p0, r0 + i + 1, r0 + i + 1, t0);
    }
    freeX(p0, t0);

    // 2. load reg.f
    for (int i = 0; i < 4; i++) {
      int f = f0 + i;
      p0->ops->vldpw(dev->p0, f, sp1, i * 8);
    }

    // 3. load reg.e
    for (int i = 0; i < 4; i++) {
      int f = e0 + i;
      p0->ops->vldpw(dev->p0, f, sp1, 32 + i * 8);

      p0->ops->vand(dev->p0, f, f, E_and);
      p0->ops->vor(dev->p0, f, f, E_or);
    }
    lock(p0);

    dev->load_start = codeSize(p0);
  }

  dumpReg(p1, 0, 0xbe);

  // 4. exec 256 instructions
  for (int i = 0; i < getProgramSize(); ++i)
    encode(dev, getPGInstruction(program, i), i);

  link_(p0, p1);

  // 5. mx ^= r[readReg2] ^ r[readReg3];
  p1->ops->xor_(dev->p1, xtmp, config->readReg2 + r0, config->readReg3 + r0);

  // !! p1 ends here the rest is p2
  link_(p1, p2);

  if (!locked(p2)) {

    p2->ops->xorw(dev->p2, mxa, mxa, xtmp);

    // 6. prefetch 64Bytes from xtmp
    if (p2->ops->hasPrefetch()) {
      p2->ops->andi(dev->p2, xtmp, mxa, CacheLineAlignMask);
      p2->ops->add(dev->p2, xtmp, xtmp, mm);

      p2->ops->prefetch(dev->p2, xtmp);
    }

    // 7. swap mx, ma
    p2->ops->rori(dev->p2, mxa, mxa, 32);

    // 8. xor r0~7 with dataset
    // 9. store r0~7
    p2->ops->andi(dev->p2, xtmp, mxa, CacheLineAlignMask);

    p2->ops->add(dev->p2, xtmp, xtmp, mm);
    // dumpReg(p1, 0, 0x1d);

    int t0 = allocX(p2), t1 = allocX(p2);
    for (int i = 0; i < 8; i += 2) {
      p2->ops->ldp(dev->p2, t0, t1, xtmp, i * 8);
      p2->ops->xor_(dev->p2, r0 + i, r0 + i, t0);
      p2->ops->xor_(dev->p2, r0 + i + 1, r0 + i + 1, t1);
      p2->ops->sdp(dev->p2, r0 + i, r0 + i + 1, sp1, i * 8);
    }
    freeX(p2, t0);
    freeX(p2, t1);

    // 10. xor group F and group E registers
    for (int i = 0; i < 4; i++)
      p2->ops->vfxor(dev->p2, f0 + i, f0 + i, e0 + i);

    dumpReg(p1, 0, 0xae);

    // 11. Store FP registers to scratchpad (spAddr0)
    p2->ops->vsdp(dev->p2, f0, f1, sp0, 0);
    p2->ops->vsdp(dev->p2, f2, f3, sp0, 32);

    p2->ops->addi(dev->p2, ic, ic, -1);

    // here xtmp is used as spMix
    p2->ops->mov(dev->p2, xtmp, zero);

    // loop again
    int offs = dev->loop_start - codeSize(p2) - JRX_SIZE_P0 - JRX_SIZE_P1;
    // printf("j0 %p ==> %p (%p)\n", p1->codeSize() + p1->code,
    //        loop_start + p0->code, p1->codeSize() + offs + p1->code);
    printf("loop ins: %d\n",
           (codeSize(p2) + codeSize(p1) + codeSize(p0) - dev->loop_start) / 4);
    p2->ops->blt(dev->p2, zero, ic, offs);

    dev->loop_end = codeSize(p2);

    // clear battle ground and return
    p2->ops->ld(dev->p2, rf, sp, -16);

    // store reg.r
    for (int i = 0; i < 8; i += 2) {
      int r = r0 + i;
      p2->ops->sdp(dev->p2, r, r + 1, rf, i * 8);
    }

    // store reg.f & reg.e
    p2->ops->vsdp(dev->p2, f0, f1, rf, 64);
    p2->ops->vsdp(dev->p2, f2, f3, rf, 96);
    p2->ops->vsdp(dev->p2, e0, e1, rf, 128);
    p2->ops->vsdp(dev->p2, e2, e3, rf, 160);

    p2->ops->exit(dev->p2);

    link_(p2, p0); // this is useless
    lock(p2);
  }

  if (p0->dlog) {
    printf("\np0:\n");
    analyze(p0->dlog + dev->loop_start * 2, JRX_SIZE_P0 * 2, 1);
    printf("\np1:\n");
    analyze(p1->dlog, JRX_SIZE_P1 * 2, 0);
    printf("\np2:\n");
    analyze(p2->dlog, dev->loop_end * 2, 0);

    printf("\np0-re:\n");
    reorder(p0->dlog + dev->loop_start * 2, JRX_SIZE_P0 * 2);
    printf("\np1-re:\n");
    reorder(p1->dlog, JRX_SIZE_P1 * 2);
    printf("\np2-re:\n");
    reorder(p2->dlog, dev->loop_end * 2);
  }

  // printf("compile done! p0->size=%d ins, p1->size=%d ins\n",
  //        p0->codeSize() / 4, p1->codeSize() / 4);
}

void generateProgramLight(void *jrx, Program_t *program,
                          ProgramConfiguration_t *config,
                          uint32_t datasetOffset) {}
ProgramFunc *getProgramFunc(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
#ifdef __GNUC__
  __builtin___clear_cache((char *)(dev->code), (char *)(dev->code + JRX_SIZE));
#endif
  return (ProgramFunc *)(dev->code);
}

void generateSuperscalarHash(void *jrx, SuperscalarProgram_t *programs,
                             cvector reciprocalCache) {
  jrx_dev_t *dev                = (jrx_dev_t *)jrx;
  jrx_base_t *p3                = (jrx_base_t *)dev->p3;
  jrx_base_t *p4                = (jrx_base_t *)dev->p4;
  jrx_base_t *p5                = (jrx_base_t *)dev->p5;
  jrx_base_t *p6                = (jrx_base_t *)dev->p6;
  int i                         = 0, spi;
  uint32_t superscaclarConstant = 0;
  int literalPool_cur = 0, literalPool_end = 0;
  static uint32_t main_loop;

  Jrx_set_stage(DATASET);

  /* reset p3, p4, p5, p6 */
  reset(p3);
  reset(p4);
  reset(p5);
  reset(p6);

  if (!locked(p3)) {
    /* for superscalar constant */
    ENC64(dev->p3, superscalarMul0);
    ENC64(dev->p3, superscalarAdd1);
    ENC64(dev->p3, superscalarAdd2);
    ENC64(dev->p3, superscalarAdd3);
    ENC64(dev->p3, superscalarAdd4);
    ENC64(dev->p3, superscalarAdd5);
    ENC64(dev->p3, superscalarAdd6);
    ENC64(dev->p3, superscalarAdd7);
    literalPool_cur = codeSize(p3);
    literalPool_end = literalPool_cur;
    lock(p3);
  } else {
    iseek(p3, superscalarConstantLen);
    literalPool_cur = superscalarConstantLen;
    literalPool_end = literalPool_cur;
  }

  if (!locked(p4)) {
    /* Save ra (return address) */
    p4->ops->addi(dev->p4, sp, sp, -16);
    p4->ops->sd(dev->p4, sp, ra, 0);
    /* Load pointer to cache memory */
    p4->ops->ld(dev->p4, ds0, ds0, 0);

    main_loop = codeSize(p4);
    /* calc dataset item */
    p4->ops->addi(dev->p4, sp, sp, -120);
    spi = 0;
    // stp x0, x1, [sp]
    for (i = 0; i < 7; i++) {
      p4->ops->sd(dev->p4, sp, ds0 + 2 * i, spi);
      p4->ops->sd(dev->p4, sp, ds1 + 2 * i, spi + 8);
      spi += 16;
    }
    p4->ops->sd(dev->p4, sp, ds14, spi);
    p4->ops->auipc(dev->p4, ds14, -(codeSize(p4) + JRX_SIZE_P3));

    p4->ops->ld(dev->p4, ds12, ds14, superscaclarConstant);
    superscaclarConstant += 8;
    p4->ops->mov(dev->p4, ds8, ds0);
    p4->ops->mov(dev->p4, ds9, ds1);
    p4->ops->mov(dev->p4, ds10, ds2);

    // rl[0] = (itemNumber + 1) * superscalarMul0;
    p4->ops->addi(dev->p4, ds2, ds2, 1);
    p4->ops->mul(dev->p4, ds0, ds2, ds12);
    for (i = 0; i < 7; i++) {
      // rl[1] = rl[0] ^ superscalarAdd1;
      p4->ops->ld(dev->p4, ds12, ds14, superscaclarConstant);
      superscaclarConstant += 8;
      p4->ops->xor_(dev->p4, ds1 + i, ds0, ds12);
    }
    lock(p4);
  }

  link_(p4, p5);
  for (i = 0; i < RANDOMX_CACHE_ACCESSES; i++) {
    /* Actual mask will be inserted by JIT compiler */
    // and x11, x10, CacheSize / CacheLineSize - 1
    p5->ops->andi(dev->p5, ds11, ds10, CacheSize / CacheLineSize - 1);
    p5->ops->lsli(dev->p5, ds11, ds11, 6);
    p5->ops->add(dev->p5, ds11, ds8, ds11);
    if (p5->ops->hasPrefetch()) {
      p5->ops->prefetch(dev->p5, ds11);
    }

    SuperscalarProgram_t *prog = &programs[i];
    size_t progSize            = SSP_getSize(prog);
    // Fill in literal pool
    for (int j = 0; j < progSize; ++j) {
      Instruction_t *instr = SSP_getInstruction(prog, j);
      if (instr->opcode == SS_IMUL_RCP) {
        ENC64(dev->p3, *(uint64_t *)cvector_get_val(
                           reciprocalCache, Instruction_getImm32(instr)));
        literalPool_end += 8;
        if (literalPool_end > JRX_SIZE_P3) {
          printf("Literal pool have no space\n");
          return;
        }
      }
    }

    for (int j = 0; j < progSize; ++j) {
      Instruction_t *instr = SSP_getInstruction(prog, j);
      uint32_t src         = ds0 + instr->src;
      uint32_t dst         = ds0 + instr->dst;
      uint32_t imm         = Instruction_getImm32(instr);
      int sl               = Instruction_getModShift(instr);
      int xtemp            = ds12;

      switch ((enum SuperscalarInstructionType)instr->opcode) {
      case SS_ISUB_R:
        p5->ops->sub(dev->p5, dst, dst, src);
        break;
      case SS_IXOR_R:
        p5->ops->xor_(dev->p5, dst, dst, src);
        break;
      case SS_IADD_RS:
        p5->ops->lsli(dev->p5, xtemp, src, sl);
        p5->ops->add(dev->p5, dst, dst, xtemp);
        break;
      case SS_IMUL_R:
        p5->ops->mul(dev->p5, dst, dst, src);
        break;
      case SS_IROR_C:
        p5->ops->rori(dev->p5, dst, dst, imm & 63);
        break;
      case SS_IADD_C7:
      case SS_IADD_C8:
      case SS_IADD_C9:
        p5->ops->addi(dev->p5, dst, dst, imm);
        break;
      case SS_IXOR_C7:
      case SS_IXOR_C8:
      case SS_IXOR_C9:
        p5->ops->li(dev->p5, xtemp, imm);
        p5->ops->xor_(dev->p5, dst, dst, xtemp);
        break;
      case SS_IMULH_R:
        p5->ops->mulhu(dev->p5, dst, dst, src);
        break;
      case SS_ISMULH_R:
        p5->ops->mulh(dev->p5, dst, dst, src);
        break;
      case SS_IMUL_RCP: {
        if (literalPool_cur > literalPool_end) {
          printf("No data in literal pool\n");
          return;
        }
        p5->ops->ld(dev->p5, xtemp, ds14, literalPool_cur);
        literalPool_cur += 8;
        p5->ops->mul(dev->p5, dst, dst, xtemp);
      } break;
      default:
        break;
      }
    }
    // Generated SuperScalar hash program goes here
    /* item mix */
    for (int j = 0; j < 4; j++) {
      p5->ops->ldp(dev->p5, ds12, ds13, ds11, 16 * j);
      p5->ops->xor_(dev->p5, ds0 + 2 * j, ds0 + 2 * j, ds12);
      p5->ops->xor_(dev->p5, ds1 + 2 * j, ds1 + 2 * j, ds13);
    }
    /* TODO update registerValue */
    p5->ops->mov(dev->p5, ds10, ds0 + SSP_getAddressRegister(prog));
  }

  link_(p5, p6);

  if (!locked(p6)) {
    for (i = 0; i < 4; i++) {
      p6->ops->sd(dev->p6, ds9, ds0 + 2 * i, 16 * i);
      p6->ops->sd(dev->p6, ds9, ds1 + 2 * i, 8 + 16 * i);
    }

    for (i = 0; i < 7; i++)
      p6->ops->ldp(dev->p6, ds0 + 2 * i, ds1 + 2 * i, sp, 16 * i);
    p6->ops->ld(dev->p6, ds14, sp, 16 * i);
    p6->ops->addi(dev->p6, sp, sp, 120);

    /* TODO ret */
    p6->ops->addi(dev->p6, ds1, ds1, 64);
    p6->ops->addi(dev->p6, ds2, ds2, 1);
    int offs = main_loop - JRX_SIZE_P4 - JRX_SIZE_P5 - codeSize(p6);
    p6->ops->bne(dev->p6, ds2, ds3, offs);
    /* Restore ra (return address) */
    p6->ops->ld(dev->p6, ra, sp, 0);
    p6->ops->addi(dev->p6, sp, sp, 16);
    p6->ops->ret(dev->p6);
    lock(p6);
  }

  // printf("SuperscalarHash(p3: 0x%x, p4: 0x%x, p5: 0x%x, p6: 0x%x)\n",
  // codeSize(p3), codeSize(p4), codeSize(p5), codeSize(p6));
}

void generateDatasetInitCode(void *jrx) {}

DatasetInitFunc *getDatasetInitFunc(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
#ifdef __GNUC__
  __builtin___clear_cache((char *)(dev->code), (char *)(dev->code + JRX_SIZE));
#endif
  return (DatasetInitFunc *)(dev->code + JRX_SIZE_P0 + JRX_SIZE_P1 +
                             JRX_SIZE_P2 + JRX_SIZE_P3);
}

size_t getCodeSize(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
  return codeSize((jrx_base_t *)dev->p0) + codeSize((jrx_base_t *)dev->p1) +
         codeSize((jrx_base_t *)dev->p2);
}
void enableWriting(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
  setPagesRW(dev->code, JRX_SIZE);
}
void enableExecution(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
  setPagesRX(dev->code, JRX_SIZE);
}
void enableAll(void *jrx) {
  jrx_dev_t *dev = (jrx_dev_t *)jrx;
  setPagesRWX(dev->code, JRX_SIZE);
}

// private:
#define INS(x) if (instr->opcode < ceil_##x)
#if 1
#define MSG(x)                                                                 \
  do {                                                                         \
  } while (0)
#else
#define MSG(x) printf("%s: %02x <= %02x\n", #x, dst, src)
#endif

void dumpReg(void *dev, uint8_t opcode, int indicator) {
  jrx_base_t *isa = (jrx_base_t *)dev;
  static int id   = 0;

  if (!dump_regs_mem)
    return;
  int t0 = allocX(isa), moffs = allocX(isa), sp2 = allocX(isa), offs = 0;

  isa->ops->addi(dev, sp2, mm, DatasetSize);

  isa->ops->ld(dev, moffs, sp2, 0);

  isa->ops->add(dev, sp2, sp2, moffs);

  isa->ops->li(dev, t0, id++);
  isa->ops->sd(dev, sp2, t0, 0);

  isa->ops->li(dev, t0, indicator);
  isa->ops->sd(dev, sp2, t0, 8);

  isa->ops->li(dev, t0, opcode);
  isa->ops->sdp(dev, t0, ic, sp2, 16);

  isa->ops->sd(dev, sp2, mxa, 32);
  isa->ops->sdp(dev, r0, r1, sp2, 48);
  offs += 64;

  if (dump_regs_full) {
    for (int i = 0; i < 8; i += 2)
      isa->ops->sdp(dev, r0 + i, r0 + i + 1, sp2, offs + i * 8);
    offs += 64;

    for (int i = 0; i < 4; i += 2)
      isa->ops->vsdp(dev, f0 + i, f0 + i + 1, sp2, offs + i * 16);
    offs += 64;

    for (int i = 0; i < 4; i += 2)
      isa->ops->vsdp(dev, e0 + i, e0 + i + 1, sp2, offs + i * 16);
    offs += 64;
  }

  // only log for 10M
  isa->ops->li(dev, t0, dump_regs_mem);
  isa->ops->blt(dev, t0, moffs, 8);
  isa->ops->addi(dev, moffs, moffs, offs);

  isa->ops->addi(dev, sp2, mm, DatasetSize);
  isa->ops->sd(dev, sp2, moffs, 0);

  freeX(isa, t0);
  freeX(isa, moffs);
  freeX(isa, sp2);
}

void load(void *dev, int x, int msrc, int imm, int msk) {
  jrx_base_t *isa = (jrx_base_t *)dev;
  if (msrc) {
    imm &= msk - 1;
    isa->ops->addi(dev, x, msrc, imm);
    isa->ops->andi(dev, x, x, (msk - 1) & ~7);
    isa->ops->add(dev, x, x, sc);
  } else {
    imm &= ScratchpadL3Mask;
    isa->ops->addi(dev, x, sc, imm);
  }
  isa->ops->ld(dev, x, x, 0);
}

void loadvf(void *dev, int x, int msrc, int imm, int msk) {
  jrx_base_t *isa = (jrx_base_t *)dev;
  int t0          = allocX(isa);

  imm &= msk - 1;
  // printf("enc ldvf, msrc=%d, imm=%d, msk=%d\n", msrc, imm, (msk - 1) &
  // ~7);
  isa->ops->addi(dev, t0, msrc, imm);
  isa->ops->andi(dev, t0, t0, (msk - 1) & ~7);
  isa->ops->add(dev, t0, t0, sc);

  isa->ops->vldpw(dev, x, t0, 0);
  freeX(isa, t0);
}

void getReg(Instruction_t *instr, int *src, int *dst, int *dm) {
  *src = instr->src & 7;
  *dst = instr->dst & 7;
  *dm  = 0;

  INS(ISWAP_R) {
    *src += r0;
    *dst += r0;
    INS(ISMULH_M) *dm = 1;
    else INS(IMUL_RCP) {
    }
    else INS(IROL_R) *dm  = 1;
    else INS(ISWAP_R) *dm = 3;
  }
  else INS(FSWAP_R) {
    if (*dst > 3)
      *dst = (*dst - 4) + e0;
    else
      *dst += f0;
  }
  else INS(FSQRT_R) {
    *dst &= 3;

    INS(FSCAL_R) {
      *dst += f0;

      INS(FADD_R) {
        *src &= 3;
        *src += a0;
      }
      else INS(FADD_M) *src += r0;
      else INS(FSUB_R) {
        *src &= 3;
        *src += a0;
      }
      else *src += r0;
    }
    else INS(FSQRT_R) {
      *dst += e0;

      INS(FMUL_R) {
        *src &= 3;
        *src += a0;
      }
      else INS(FDIV_M) *src += r0;
    }
  }
  else {
    *src += r0;
    *dst += r0;
  }
}

void encode(jrx_dev_t *dev, Instruction_t *instr, int pc) {
  jrx_base_t *p0 = (jrx_base_t *)dev->p0;
  jrx_base_t *p1 = (jrx_base_t *)dev->p1;
  int src, dst, msrc, t0, dm;
  int imm = Instruction_getImm32(instr), sl = Instruction_getModShift(instr),
      cond = Instruction_getModCond(instr),
      msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;

  getReg(instr, &src, &dst, &dm);
  msrc = src == dst ? 0 : src;

  INS(IADD_RS) {
    MSG(IADD_RS);

    if (sl) {
      p1->ops->lsli(dev->p1, xtmp, src, sl);
      p1->ops->add(dev->p1, dst, dst, xtmp);
    } else
      p1->ops->add(dev->p1, dst, dst, src);

    if (dst == r5)
      p1->ops->addi(dev->p1, dst, dst, imm);
  }

  else INS(IADD_M) {
    MSG(IADD_M);
    load(dev->p1, xtmp, msrc, imm, msk);
    p1->ops->add(dev->p1, dst, dst, xtmp);
  }

  else INS(ISUB_R) {
    MSG(ISUB_R);
    if (src == dst)
      p1->ops->addi(dev->p1, dst, dst, -imm);
    else
      p1->ops->sub(dev->p1, dst, dst, src);
  }

  else INS(ISUB_M) {
    MSG(ISUB_M);
    load(dev->p1, xtmp, msrc, imm, msk);
    p1->ops->sub(dev->p1, dst, dst, xtmp);
  }

  else INS(IMUL_R) {
    MSG(IMUL_R);
    if (src == dst) {
      p1->ops->li(dev->p1, xtmp, imm);
      p1->ops->mul(dev->p1, dst, dst, xtmp);
    } else
      p1->ops->mul(dev->p1, dst, dst, src);
  }

  else INS(IMUL_M) {
    MSG(IMUL_M);
    load(dev->p1, xtmp, msrc, imm, msk);
    p1->ops->mul(dev->p1, dst, dst, xtmp);
  }

  else INS(IMULH_R) {
    MSG(IMULH_R);
    p1->ops->mulhu(dev->p1, dst, dst, src);
  }

  else INS(IMULH_M) {
    MSG(IMULH_M);
    load(dev->p1, xtmp, msrc, imm, msk);
    p1->ops->mulhu(dev->p1, dst, dst, xtmp);
  }

  else INS(ISMULH_R) {
    MSG(ISMULH_R);
    p1->ops->mulh(dev->p1, dst, dst, src);
  }

  else INS(ISMULH_M) {
    MSG(ISMULH_M);
    load(dev->p1, xtmp, msrc, imm, msk);
    p1->ops->mulh(dev->p1, dst, dst, xtmp);
  }

  else INS(IMUL_RCP) {
    MSG(IMUL_RCP);
    uint64_t N  = 1ull << 63;
    uint64_t dv = (uint64_t)(uint32_t)imm;

    if (isZeroOrPowerOf2(dv))
      goto out;
    uint64_t s = 64 - __builtin_clzll(dv), q = N / dv, r = N % dv;

    // printf("writing to %p %d\n", code, literal_pos);
    *(uint64_t *)(dev->code + dev->literal_pos) = (q << s) + ((r << s) / dv);
    // printf("done\n");

    t0 = resvX(p0);
    if (t0) {
      p0->ops->ld(dev->p0, t0, rf, dev->literal_pos);
      // printf("encode RCP %016llx @ %x to %02x\n",
      //        (q << s) + ((r << s) / dv), literal_pos, t0);
    } else {
      t0 = xtmp;
      p1->ops->ld(dev->p1, xtmp, rf, dev->literal_pos);
    }
    dev->literal_pos -= 8;

    p1->ops->mul(dev->p1, dst, dst, t0);
    dm = 1;
  }

  else INS(INEG_R) {
    MSG(INEG_R);
    p1->ops->sub(dev->p1, dst, zero, dst);
  }

  else INS(IXOR_R) {
    MSG(IXOR_R);
    if (src == dst) {
      p1->ops->li(dev->p1, xtmp, imm);
      p1->ops->xor_(dev->p1, dst, dst, xtmp);
    } else
      p1->ops->xor_(dev->p1, dst, dst, src);
  }

  else INS(IXOR_M) {
    MSG(IXOR_M);
    load(dev->p1, xtmp, msrc, imm, msk);
    p1->ops->xor_(dev->p1, dst, dst, xtmp);
  }

  else INS(IROR_R) {
    MSG(IROR_R);
    if (src == dst) {
      p1->ops->rori(dev->p1, dst, dst, imm & 0x3f);
    } else
      p1->ops->ror(dev->p1, dst, dst, src);
  }

  else INS(IROL_R) {
    MSG(IROL_R);
    if (src == dst) {
      p1->ops->roli(dev->p1, dst, dst, imm & 0x3f);
    } else
      p1->ops->rol(dev->p1, dst, dst, src);
  }

  else INS(ISWAP_R) {
    MSG(ISWAP_R);
    if (src == dst) {
      dm = 0;
      goto out;
    }

    p1->ops->mov(dev->p1, xtmp, dst);
    p1->ops->mov(dev->p1, dst, src);
    p1->ops->mov(dev->p1, src, xtmp);
  }

  // float
  else INS(FSWAP_R) {
    MSG(FSWAP_R);
    p1->ops->vfswap(dev->p1, dst);
  }

  else INS(FADD_R) {
    MSG(FADD_R);
    p1->ops->vfadd(dev->p1, dst, dst, src);
  }

  else INS(FADD_M) {
    MSG(FADD_M);
    loadvf(dev->p1, vtmp, msrc, imm, msk);
    p1->ops->vfadd(dev->p1, dst, dst, vtmp);
  }

  else INS(FSUB_R) {
    MSG(FSUB_R);
    p1->ops->vfsub(dev->p1, dst, dst, src);
  }

  else INS(FSUB_M) {
    MSG(FSUB_M);
    loadvf(dev->p1, vtmp, msrc, imm, msk);
    p1->ops->vfsub(dev->p1, dst, dst, vtmp);
  }

  else INS(FSCAL_R) {
    MSG(FSCAL_R);
    p1->ops->vfxor(dev->p1, dst, dst, scale);
  }

  else INS(FMUL_R) {
    MSG(FMUL_R);
    p1->ops->vfmul(dev->p1, dst, dst, src);
  }

  else INS(FDIV_M) {
    MSG(FDIV_M);
    loadvf(dev->p1, vtmp, msrc, imm, msk);
    p1->ops->vand(dev->p1, vtmp, vtmp, E_and);
    p1->ops->vor(dev->p1, vtmp, vtmp, E_or);
    p1->ops->vfdiv(dev->p1, dst, dst, vtmp);
  }

  else INS(FSQRT_R) {
    MSG(FSQRT_R);
    p1->ops->vfsqrt(dev->p1, dst, dst);
  }

  // control
  else INS(CBRANCH) {
    MSG(CBRANCH);
    sl = cond + ConditionOffset;
    imm |= (1U << sl);
    imm &= ~(1U << (sl - 1));

    p1->ops->addi(dev->p1, dst, dst, imm);
    p1->ops->lsri(dev->p1, xtmp, dst, sl);
    p1->ops->andi(dev->p1, xtmp, xtmp, 0xff);

    dumpReg(dev->p1, instr->opcode, 0);

    int offs = dev->dst_change[dst] - codeSize(p1);
    // printf("j %p ==> %p (%p)\n", p1->codeSize() + p1->code,
    //        dst_change[dst] + p1->code, p1->codeSize() + offs + p1->code);
    p1->ops->beq(dev->p1, xtmp, zero, offs);

    for (int k = 0; k < 8; ++k)
      dev->dst_change[r0 + k] = codeSize(p1);
    return;
    // printf("%d b\n", offs);
  }

  else INS(CFROUND) {
    MSG(CFROUND);
    p1->ops->rori(dev->p1, xtmp, src, imm & 63);
    p1->ops->sfrm(dev->p1, xtmp);
  }

  else {
    MSG(ISTORE);
    msk = cond < StoreL3Condition ? msk : RANDOMX_SCRATCHPAD_L3;
    msk -= 1;

    p1->ops->addi(dev->p1, xtmp, dst, imm & msk);
    p1->ops->andi(dev->p1, xtmp, xtmp, msk & ~7);
    p1->ops->add(dev->p1, xtmp, xtmp, sc);
    p1->ops->sd(dev->p1, xtmp, src, 0);
  }

out:
  dumpReg(dev->p1, instr->opcode, 0);

  if (dm)
    dev->dst_change[dst] = codeSize(p1);
  if (dm & 2)
    dev->dst_change[src] = codeSize(p1);
}

jrx_t baseDev = {
    .name                    = "baseDev",
    .init_jrx                = initJrx,
    .exit_jrx                = exitJrx,
    .generateProgram         = generateProgram,
    .generateProgramLight    = generateProgramLight,
    .generateSuperscalarHash = generateSuperscalarHash,
    .generateDatasetInitCode = generateDatasetInitCode,
    .getProgramFunc          = getProgramFunc,
    .getDatasetInitFunc      = getDatasetInitFunc,
    .getCode                 = NULL,
    .getCodeSize             = getCodeSize,
    .enableWriting           = enableWriting,
    .enableExecution         = enableExecution,
    .enableAll               = enableAll,
};
JRX_REGISTER(baseDev)
