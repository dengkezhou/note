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

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "blake2/endian.h"
#include <stdint.h>

typedef struct Instruction {
  uint8_t opcode;
  uint8_t dst;
  uint8_t src;
  uint8_t mod;
  uint32_t imm32;
} Instruction_t;

typedef void (*InstructionFormatter)(Instruction_t *);

extern char *names[256];
extern InstructionFormatter engine[256];

enum InstructionType {
  IADD_RS  = 0,
  IADD_M   = 1,
  ISUB_R   = 2,
  ISUB_M   = 3,
  IMUL_R   = 4,
  IMUL_M   = 5,
  IMULH_R  = 6,
  IMULH_M  = 7,
  ISMULH_R = 8,
  ISMULH_M = 9,
  IMUL_RCP = 10,
  INEG_R   = 11,
  IXOR_R   = 12,
  IXOR_M   = 13,
  IROR_R   = 14,
  IROL_R   = 15,
  ISWAP_R  = 16,
  FSWAP_R  = 17,
  FADD_R   = 18,
  FADD_M   = 19,
  FSUB_R   = 20,
  FSUB_M   = 21,
  FSCAL_R  = 22,
  FMUL_R   = 23,
  FDIV_M   = 24,
  FSQRT_R  = 25,
  CBRANCH  = 26,
  CFROUND  = 27,
  ISTORE   = 28,
  NOP      = 29,
};

uint32_t Instruction_getImm32(Instruction_t *ins);
void Instruction_setImm32(Instruction_t *ins, uint32_t val);
const char *Instruction_getName(Instruction_t *ins);
int Instruction_getModMem(Instruction_t *ins);
int Instruction_getModShift(Instruction_t *ins);
int Instruction_getModCond(Instruction_t *ins);
void Instruction_setMod(Instruction_t *ins, uint8_t val);
void printInstruction(Instruction_t *ins);
#endif
