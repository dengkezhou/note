/*
Copyright (c) 2018-2019, tevador <tevador@gmail.com>

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

#ifndef __JRX_X86_H__
#define __JRX_X86_H__

#include "rxa_common.h"
#include <cvector.h>
#include <instruction.h>
#include <jrx_base.h>
#include <program.h>
#include <stdint.h>
#include <string.h>
#include <superscalar_program.h>

typedef void (*InstructionGeneratorX86)(void *jrx, Instruction_t *, int);

typedef struct jrx_x86 {
  jrx_data_t data;
  cvector instructionOffsets;
  int registerUsage[RegistersCount];
  uint8_t *code;
  int32_t codePos;
} jrx_x86_t;

static ProgramFunc *getProgramFunc(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  return (ProgramFunc *)dev->code;
}
static DatasetInitFunc *getDatasetInitFunc(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  return (DatasetInitFunc *)dev->code;
}
static uint8_t *getCode(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  return dev->code;
}
extern InstructionGeneratorX86 X86Engine[256];

void generateProgramPrologue(void *, Program_t *, ProgramConfiguration_t *);
void generateProgramEpilogue(void *, Program_t *, ProgramConfiguration_t *);
void genAddressReg(void *, Instruction_t *, bool);
void genAddressRegDst(void *, Instruction_t *);
void genAddressImm(void *, Instruction_t *);
void genSIB(void *jrx, int scale, int index, int base);

void generateCode(void *, Instruction_t *, int);
void generateSuperscalarCode(void *, Instruction_t *, cvector);

static void emitByte(void *jrx, uint8_t val) {
  jrx_x86_t *dev          = (jrx_x86_t *)jrx;
  dev->code[dev->codePos] = val;
  dev->codePos++;
}

static void emit32(void *jrx, uint32_t val) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  memcpy(dev->code + dev->codePos, &val, sizeof(val));
  dev->codePos += sizeof(val);
}

static void emit64(void *jrx, uint64_t val) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  memcpy(dev->code + dev->codePos, &val, sizeof(val));
  dev->codePos += sizeof(val);
}

static void emit(void *jrx, const uint8_t *src, size_t count) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  memcpy(dev->code + dev->codePos, src, count);
  dev->codePos += count;
}

void h_IADD_RS(void *jrx, Instruction_t *, int);
void h_IADD_M(void *jrx, Instruction_t *, int);
void h_ISUB_R(void *jrx, Instruction_t *, int);
void h_ISUB_M(void *jrx, Instruction_t *, int);
void h_IMUL_R(void *jrx, Instruction_t *, int);
void h_IMUL_M(void *jrx, Instruction_t *, int);
void h_IMULH_R(void *jrx, Instruction_t *, int);
void h_IMULH_M(void *jrx, Instruction_t *, int);
void h_ISMULH_R(void *jrx, Instruction_t *, int);
void h_ISMULH_M(void *jrx, Instruction_t *, int);
void h_IMUL_RCP(void *jrx, Instruction_t *, int);
void h_INEG_R(void *jrx, Instruction_t *, int);
void h_IXOR_R(void *jrx, Instruction_t *, int);
void h_IXOR_M(void *jrx, Instruction_t *, int);
void h_IROR_R(void *jrx, Instruction_t *, int);
void h_IROL_R(void *jrx, Instruction_t *, int);
void h_ISWAP_R(void *jrx, Instruction_t *, int);
void h_FSWAP_R(void *jrx, Instruction_t *, int);
void h_FADD_R(void *jrx, Instruction_t *, int);
void h_FADD_M(void *jrx, Instruction_t *, int);
void h_FSUB_R(void *jrx, Instruction_t *, int);
void h_FSUB_M(void *jrx, Instruction_t *, int);
void h_FSCAL_R(void *jrx, Instruction_t *, int);
void h_FMUL_R(void *jrx, Instruction_t *, int);
void h_FDIV_M(void *jrx, Instruction_t *, int);
void h_FSQRT_R(void *jrx, Instruction_t *, int);
void h_CBRANCH(void *jrx, Instruction_t *, int);
void h_CFROUND(void *jrx, Instruction_t *, int);
void h_ISTORE(void *jrx, Instruction_t *, int);
void h_NOP(void *jrx, Instruction_t *, int);

#endif
