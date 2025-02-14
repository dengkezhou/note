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

#include "instruction.h"
#include "rxa_common.h"

void printInstruction(Instruction_t *ins) {
  printf("%s ", names[ins->opcode]);
  InstructionFormatter handler = engine[ins->opcode];
  (*handler)(ins);
}

void genAddressReg(Instruction_t *ins, int srcIndex) {
  printf("%s[r%d+%d]", Instruction_getModMem(ins) ? "L1" : "L2", srcIndex,
         (int32_t)Instruction_getImm32(ins));
}

void genAddressRegDst(Instruction_t *ins, int dstIndex) {
  if (Instruction_getModCond(ins) < StoreL3Condition)
    printf("%s", (Instruction_getModMem(ins) ? "L1" : "L2"));
  else
    printf("L3");
  printf("[r%d+%d]", dstIndex, (int32_t)Instruction_getImm32(ins));
}

void genAddressImm(Instruction_t *ins) {
  printf("L3[%ld]", (Instruction_getImm32(ins) & ScratchpadL3Mask));
}

uint32_t Instruction_getImm32(Instruction_t *ins) {
  return load32(&(ins->imm32));
}
void Instruction_setImm32(Instruction_t *ins, uint32_t val) {
  return store32(&(ins->imm32), val);
}
const char *Instruction_getName(Instruction_t *ins) {
  return names[ins->opcode];
}
int Instruction_getModMem(Instruction_t *ins) {
  return ins->mod % 4; // bits 0-1
}
int Instruction_getModShift(Instruction_t *ins) {
  return (ins->mod >> 2) % 4; // bits 2-3
}
int Instruction_getModCond(Instruction_t *ins) {
  return ins->mod >> 4; // bits 4-7
}
void Instruction_setMod(Instruction_t *ins, uint8_t val) {
  ins->mod = val;
}
void h_IADD_RS(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("r%d, r%d", dstIndex, srcIndex);
  if (dstIndex == RegisterNeedsDisplacement) {
    printf(", %d", (int32_t)Instruction_getImm32(ins));
  }
  printf(", SHFT %d\n", Instruction_getModShift(ins));
}

void h_IADD_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, ", dstIndex);
    genAddressReg(ins, srcIndex);
    printf("\n");
  } else {
    printf("r%d, ", dstIndex);
    genAddressImm(ins);
    printf("\n");
  }
}

void h_ISUB_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, r%d\n", dstIndex, srcIndex);
  } else {
    printf("r%d, %d\n", dstIndex, (int32_t)Instruction_getImm32(ins));
  }
}

void h_ISUB_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, ", dstIndex);
    genAddressReg(ins, srcIndex);
    printf("\n");
  } else {
    printf("r%d, ", dstIndex);
    genAddressImm(ins);
    printf("\n");
  }
}

void h_IMUL_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, r%d\n", dstIndex, srcIndex);
  } else {
    printf("r%d, %d\n", dstIndex, (int32_t)Instruction_getImm32(ins));
  }
}

void h_IMUL_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, ", dstIndex);
    genAddressReg(ins, srcIndex);
    printf("\n");
  } else {
    printf("r%d, ", dstIndex);
    genAddressImm(ins);
    printf("\n");
  }
}

void h_IMULH_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("r%d, r%d\n", dstIndex, srcIndex);
}

void h_IMULH_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, ", dstIndex);
    genAddressReg(ins, srcIndex);
    printf("\n");
  } else {
    printf("r%d, ", dstIndex);
    genAddressImm(ins);
    printf("\n");
  }
}

void h_ISMULH_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("r%d, r%d\n", dstIndex, srcIndex);
}

void h_ISMULH_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, ", dstIndex);
    genAddressReg(ins, srcIndex);
    printf("\n");
  } else {
    printf("r%d, ", dstIndex);
    genAddressImm(ins);
    printf("\n");
  }
}

void h_INEG_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  printf("r%d\n", dstIndex);
}

void h_IXOR_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, r%d\n", dstIndex, srcIndex);
  } else {
    printf("r%d, %d\n", dstIndex, (int32_t)Instruction_getImm32(ins));
  }
}

void h_IXOR_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, ", dstIndex);
    genAddressReg(ins, srcIndex);
    printf("\n");
  } else {
    printf("r%d, ", dstIndex);
    genAddressImm(ins);
    printf("\n");
  }
}

void h_IROR_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, r%d\n", dstIndex, srcIndex);
  } else {
    printf("r%d, %d\n", dstIndex, (Instruction_getImm32(ins) & 63));
  }
}

void h_IROL_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  if (dstIndex != srcIndex) {
    printf("r%d, r%d\n", dstIndex, srcIndex);
  } else {
    printf("r%d, %d\n", dstIndex, (Instruction_getImm32(ins) & 63));
  }
}

void h_IMUL_RCP(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  printf("r%d, %d\n", dstIndex, Instruction_getImm32(ins));
}

void h_ISWAP_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("r%d, r%d\n", dstIndex, srcIndex);
}

void h_FSWAP_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  char reg         = (dstIndex >= RegisterCountFlt) ? 'e' : 'f';
  dstIndex %= RegisterCountFlt;
  printf("%c%d\n", reg, dstIndex);
}

void h_FADD_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  uint8_t srcIndex = ins->src % RegisterCountFlt;
  printf("f%d, a%d\n", dstIndex, srcIndex);
}

void h_FADD_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("f%d, ", dstIndex);
  genAddressReg(ins, srcIndex);
  printf("\n");
}

void h_FSUB_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  uint8_t srcIndex = ins->src % RegisterCountFlt;
  printf("f%d, a%d\n", dstIndex, srcIndex);
}

void h_FSUB_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("f%d, ", dstIndex);
  genAddressReg(ins, srcIndex);
  printf("\n");
}

void h_FSCAL_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  printf("f%d\n", dstIndex);
}

void h_FMUL_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  uint8_t srcIndex = ins->src % RegisterCountFlt;
  printf("e%d, a%d\n", dstIndex, srcIndex);
}

void h_FDIV_M(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("e%d, ", dstIndex);
  genAddressReg(ins, srcIndex);
  printf("\n");
}

void h_FSQRT_R(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegisterCountFlt;
  printf("e%d\n", dstIndex);
}

void h_CFROUND(Instruction_t *ins) {
  uint8_t srcIndex = ins->src % RegistersCount;
  printf("r%d, %d\n", srcIndex, (Instruction_getImm32(ins) & 63));
}

void h_CBRANCH(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  //uint8_t srcIndex = ins->src % RegistersCount;
  printf("r%d, %d, COND %d\n", dstIndex, (int32_t)Instruction_getImm32(ins),
         (int)(Instruction_getModCond(ins)));
}

void h_ISTORE(Instruction_t *ins) {
  uint8_t dstIndex = ins->dst % RegistersCount;
  uint8_t srcIndex = ins->src % RegistersCount;
  genAddressRegDst(ins, dstIndex);
  printf(", r%d\n", srcIndex);
}

void h_NOP(Instruction_t *ins) { printf("\n"); }

#include "instruction_weights.h"
#define INST_NAME(x)   REPN(#x, WT(x))
#define INST_HANDLE(x) REPN(&h_##x, WT(x))

char *names[256] = {
    INST_NAME(IADD_RS) INST_NAME(IADD_M) INST_NAME(ISUB_R) INST_NAME(ISUB_M)
        INST_NAME(IMUL_R) INST_NAME(IMUL_M) INST_NAME(IMULH_R)
            INST_NAME(IMULH_M) INST_NAME(ISMULH_R) INST_NAME(ISMULH_M)
                INST_NAME(IMUL_RCP) INST_NAME(INEG_R) INST_NAME(IXOR_R)
                    INST_NAME(IXOR_M) INST_NAME(IROR_R) INST_NAME(IROL_R)
                        INST_NAME(ISWAP_R) INST_NAME(FSWAP_R) INST_NAME(FADD_R)
                            INST_NAME(FADD_M) INST_NAME(FSUB_R)
                                INST_NAME(FSUB_M) INST_NAME(FSCAL_R)
                                    INST_NAME(FMUL_R) INST_NAME(FDIV_M)
                                        INST_NAME(FSQRT_R) INST_NAME(CBRANCH)
                                            INST_NAME(CFROUND) INST_NAME(ISTORE)
                                                INST_NAME(NOP)};

InstructionFormatter engine[256] = {
    INST_HANDLE(IADD_RS) INST_HANDLE(IADD_M) INST_HANDLE(ISUB_R) INST_HANDLE(
        ISUB_M) INST_HANDLE(IMUL_R) INST_HANDLE(IMUL_M) INST_HANDLE(IMULH_R)
        INST_HANDLE(IMULH_M) INST_HANDLE(ISMULH_R) INST_HANDLE(ISMULH_M)
            INST_HANDLE(IMUL_RCP) INST_HANDLE(INEG_R) INST_HANDLE(IXOR_R)
                INST_HANDLE(IXOR_M) INST_HANDLE(IROR_R) INST_HANDLE(IROL_R)
                    INST_HANDLE(ISWAP_R) INST_HANDLE(FSWAP_R) INST_HANDLE(
                        FADD_R) INST_HANDLE(FADD_M) INST_HANDLE(FSUB_R)
                        INST_HANDLE(FSUB_M) INST_HANDLE(FSCAL_R)
                            INST_HANDLE(FMUL_R) INST_HANDLE(FDIV_M)
                                INST_HANDLE(FSQRT_R) INST_HANDLE(CBRANCH)
                                    INST_HANDLE(CFROUND) INST_HANDLE(ISTORE)
                                        INST_HANDLE(NOP)};
