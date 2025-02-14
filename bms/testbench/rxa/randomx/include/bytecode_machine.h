/*
Copyright (c) 2019, tevador <tevador@gmail.com>

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

#ifndef __BYTECODE_MACHINE_H__
#define __BYTECODE_MACHINE_H__

#include "rxa_common.h"
#include "instruction.h"
#include "intrin_portable.h"
#include "program.h"
#include "stats-utils.h"
#include <math.h>

// register file in machine byte order
typedef struct NativeRegisterFile {
  int_reg_t r[RegistersCount];
  rx_vec_f128 f[RegisterCountFlt];
  rx_vec_f128 e[RegisterCountFlt];
  rx_vec_f128 a[RegisterCountFlt];
} NativeRegisterFile_t;

typedef struct InstructionByteCode {
  union {
    int_reg_t *idst;
    rx_vec_f128 *fdst;
  };
  union {
    const int_reg_t *isrc;
    const rx_vec_f128 *fsrc;
  };
  union {
    uint64_t imm;
    int64_t simm;
  };
  enum InstructionType type;
  union {
    int16_t target;
    uint16_t shift;
  };
  uint32_t memMask;
} InstructionByteCode_t;

#define OPCODE_CEIL_DECLARE(curr, prev)                                        \
  ceil_##curr = ceil_##prev + RANDOMX_FREQ_##curr

enum {
  ceil_NULL = 0,
  OPCODE_CEIL_DECLARE(IADD_RS, NULL),
  OPCODE_CEIL_DECLARE(IADD_M, IADD_RS),
  OPCODE_CEIL_DECLARE(ISUB_R, IADD_M),
  OPCODE_CEIL_DECLARE(ISUB_M, ISUB_R),
  OPCODE_CEIL_DECLARE(IMUL_R, ISUB_M),
  OPCODE_CEIL_DECLARE(IMUL_M, IMUL_R),
  OPCODE_CEIL_DECLARE(IMULH_R, IMUL_M),
  OPCODE_CEIL_DECLARE(IMULH_M, IMULH_R),
  OPCODE_CEIL_DECLARE(ISMULH_R, IMULH_M),
  OPCODE_CEIL_DECLARE(ISMULH_M, ISMULH_R),
  OPCODE_CEIL_DECLARE(IMUL_RCP, ISMULH_M),
  OPCODE_CEIL_DECLARE(INEG_R, IMUL_RCP),
  OPCODE_CEIL_DECLARE(IXOR_R, INEG_R),
  OPCODE_CEIL_DECLARE(IXOR_M, IXOR_R),
  OPCODE_CEIL_DECLARE(IROR_R, IXOR_M),
  OPCODE_CEIL_DECLARE(IROL_R, IROR_R),
  OPCODE_CEIL_DECLARE(ISWAP_R, IROL_R),
  OPCODE_CEIL_DECLARE(FSWAP_R, ISWAP_R),
  OPCODE_CEIL_DECLARE(FADD_R, FSWAP_R),
  OPCODE_CEIL_DECLARE(FADD_M, FADD_R),
  OPCODE_CEIL_DECLARE(FSUB_R, FADD_M),
  OPCODE_CEIL_DECLARE(FSUB_M, FSUB_R),
  OPCODE_CEIL_DECLARE(FSCAL_R, FSUB_M),
  OPCODE_CEIL_DECLARE(FMUL_R, FSCAL_R),
  OPCODE_CEIL_DECLARE(FDIV_M, FMUL_R),
  OPCODE_CEIL_DECLARE(FSQRT_R, FDIV_M),
  OPCODE_CEIL_DECLARE(CBRANCH, FSQRT_R),
  OPCODE_CEIL_DECLARE(CFROUND, CBRANCH),
  OPCODE_CEIL_DECLARE(ISTORE, CFROUND),
  OPCODE_CEIL_DECLARE(NOP, ISTORE),
};

#undef OPCODE_CEIL_DECLARE

typedef struct bytecode_machine {
  int_reg_t zero;
  int registerUsage[RegistersCount];
} bytecode_machine_t;

#define RANDOMX_EXE_ARGS                                                       \
  InstructionByteCode_t *ibc, int *pc, uint8_t *scratchpad,                    \
      ProgramConfiguration_t *config
#define RANDOMX_GEN_ARGS                                                       \
  bytecode_machine_t *dev, Instruction_t *instr, int i,                        \
      InstructionByteCode_t *ibc, NativeRegisterFile_t *nreg

typedef void (*InstructionGenBytecode)(RANDOMX_GEN_ARGS);
void executeInstruction(RANDOMX_EXE_ARGS);

bytecode_machine_t *initBytecodeMachine(void);
void exitBytecodeMachine(bytecode_machine_t *dev);
void beginCompilation(bytecode_machine_t *dev, NativeRegisterFile_t *regFile);
void compileInstruction(RANDOMX_GEN_ARGS);
void compileProgram(bytecode_machine_t *dev, Program_t *program,
                           InstructionByteCode_t *bytecode,
                           NativeRegisterFile_t *regFile);
void executeBytecode(bytecode_machine_t *dev,
                            InstructionByteCode_t *bytecode,
                            uint8_t *scratchpad, ProgramConfiguration_t *config,
                            Program_t *program);
void *getScratchpadAddress(InstructionByteCode_t *ibc,
                                  uint8_t *scratchpad);
rx_vec_f128 maskRegisterExponentMantissa(ProgramConfiguration_t *config,
                                                rx_vec_f128 x);
void exe_IADD_RS(RANDOMX_EXE_ARGS);
void exe_IADD_M(RANDOMX_EXE_ARGS);
void exe_ISUB_R(RANDOMX_EXE_ARGS);
void exe_ISUB_M(RANDOMX_EXE_ARGS);
void exe_IMUL_R(RANDOMX_EXE_ARGS);
void exe_IMUL_M(RANDOMX_EXE_ARGS);
void exe_IMULH_R(RANDOMX_EXE_ARGS);
void exe_IMULH_M(RANDOMX_EXE_ARGS);
void exe_ISMULH_R(RANDOMX_EXE_ARGS);
void exe_ISMULH_M(RANDOMX_EXE_ARGS);
void exe_INEG_R(RANDOMX_EXE_ARGS);
void exe_IXOR_R(RANDOMX_EXE_ARGS);
void exe_IXOR_M(RANDOMX_EXE_ARGS);
void exe_IROR_R(RANDOMX_EXE_ARGS);
void exe_IROL_R(RANDOMX_EXE_ARGS);
void exe_ISWAP_R(RANDOMX_EXE_ARGS);
void exe_FSWAP_R(RANDOMX_EXE_ARGS);
void exe_FADD_R(RANDOMX_EXE_ARGS);
void exe_FADD_M(RANDOMX_EXE_ARGS);
void exe_FSUB_R(RANDOMX_EXE_ARGS);
void exe_FSUB_M(RANDOMX_EXE_ARGS);
void exe_FSCAL_R(RANDOMX_EXE_ARGS);
void exe_FMUL_R(RANDOMX_EXE_ARGS);
void exe_FDIV_M(RANDOMX_EXE_ARGS);
void exe_FSQRT_R(RANDOMX_EXE_ARGS);
void exe_CBRANCH(RANDOMX_EXE_ARGS);
void exe_CFROUND(RANDOMX_EXE_ARGS);
void exe_ISTORE(RANDOMX_EXE_ARGS);

#ifdef RANDOMX_GEN_TABLE
static InstructionGenBytecode genTable[256];

void gen_IADD_RS(RANDOMX_GEN_ARGS);
void gen_IADD_M(RANDOMX_GEN_ARGS);
void gen_ISUB_R(RANDOMX_GEN_ARGS);
void gen_ISUB_M(RANDOMX_GEN_ARGS);
void gen_IMUL_R(RANDOMX_GEN_ARGS);
void gen_IMUL_M(RANDOMX_GEN_ARGS);
void gen_IMULH_R(RANDOMX_GEN_ARGS);
void gen_IMULH_M(RANDOMX_GEN_ARGS);
void gen_ISMULH_R(RANDOMX_GEN_ARGS);
void gen_ISMULH_M(RANDOMX_GEN_ARGS);
void gen_IMUL_RCP(RANDOMX_GEN_ARGS);
void gen_INEG_R(RANDOMX_GEN_ARGS);
void gen_IXOR_R(RANDOMX_GEN_ARGS);
void gen_IXOR_M(RANDOMX_GEN_ARGS);
void gen_IROR_R(RANDOMX_GEN_ARGS);
void gen_IROL_R(RANDOMX_GEN_ARGS);
void gen_ISWAP_R(RANDOMX_GEN_ARGS);
void gen_FSWAP_R(RANDOMX_GEN_ARGS);
void gen_FADD_R(RANDOMX_GEN_ARGS);
void gen_FADD_M(RANDOMX_GEN_ARGS);
void gen_FSUB_R(RANDOMX_GEN_ARGS);
void gen_FSUB_M(RANDOMX_GEN_ARGS);
void gen_FSCAL_R(RANDOMX_GEN_ARGS);
void gen_FMUL_R(RANDOMX_GEN_ARGS);
void gen_FDIV_M(RANDOMX_GEN_ARGS);
void gen_FSQRT_R(RANDOMX_GEN_ARGS);
void gen_CBRANCH(RANDOMX_GEN_ARGS);
void gen_CFROUND(RANDOMX_GEN_ARGS);
void gen_ISTORE(RANDOMX_GEN_ARGS);
void gen_NOP(RANDOMX_GEN_ARGS);
#endif

#endif
