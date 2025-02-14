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
#include <linux/types.h>
#include "bytecode_machine.h"
#include "reciprocal.h"
#include <math.h>
#include <intrin_portable.h>

bytecode_machine_t *initBytecodeMachine(void) {
  bytecode_machine_t *dev = NULL;

  dev = aligned_allocMemory(sizeof(bytecode_machine_t), 64);
  if (!dev) {
    printf("Bytecode_Machine alloc mem Error\n");
    return NULL;
  }
  return dev;
}

void exitBytecodeMachine(bytecode_machine_t *dev) {
  aligned_freeMemory(dev, sizeof(bytecode_machine_t));
}

void beginCompilation(bytecode_machine_t *dev, NativeRegisterFile_t *regFile) {
  for (unsigned i = 0; i < RegistersCount; ++i) {
    dev->registerUsage[i] = -1;
  }
}

void compileInstruction(RANDOMX_GEN_ARGS)
#ifdef RANDOMX_GEN_TABLE
{
  auto generator = genTable[instr.opcode];
  (this->*generator)(instr, i, ibc);
}
#else
    ;
#endif

void compileProgram(bytecode_machine_t *dev, Program_t *program,
                    InstructionByteCode_t *bytecode,
                    NativeRegisterFile_t *regFile) {
  beginCompilation(dev, regFile);
  for (unsigned i = 0; i < RANDOMX_PROGRAM_SIZE; ++i) {
    Instruction_t *instr       = &program->programBuffer[i];
    InstructionByteCode_t *ibc = &bytecode[i];

    compileInstruction(dev, instr, i, ibc, regFile);
  }
}

InsStats inss = {0};
void executeBytecode(bytecode_machine_t *dev, InstructionByteCode_t *bytecode,
                     uint8_t *scratchpad, ProgramConfiguration_t *config,
                     Program_t *program) {
  int i = 0;

  for (int pc = 0; pc < RANDOMX_PROGRAM_SIZE; ++pc) {
    InstructionByteCode_t *ibc = &bytecode[pc];
    Instruction_t *instr       = &program->programBuffer[pc];

    // printf("exec pc %d\n", pc);
    if (op_info[(int)ibc->type].mem & 1)
      POKC(cache_read);
    else if (op_info[(int)ibc->type].mem & 2)
      POKC(cache_write);

    struct opdesc q = {0}, *p = &q;
    // set dst
    if (ibc->type <= ISWAP_R)
      p->dst = (instr->dst & 7) | 0x10;
    else if (ibc->type <= FSWAP_R) {
      p->dst = (instr->dst & 7);
      p->dst |= p->dst < 4 ? 0xf0 : 0xe0;
    } else if (ibc->type <= FSCAL_R)
      p->dst = (instr->dst & 3) | 0xf0;
    else if (ibc->type <= FSQRT_R)
      p->dst = (instr->dst & 3) | 0xe0;

    // set src
    if (ibc->type <= ISWAP_R) {
      if (ibc->isrc == &dev->zero || ibc->isrc == &ibc->imm)
        // no reg depended
        p->src = 0;
      else
        p->src = (instr->src & 7) | 0x10;
    } else if (ibc->type == FADD_M || ibc->type == FSUB_M ||
               ibc->type == FDIV_M)
      p->src = (instr->src & 7) | 0x10;
    else
      p->src = 0;

    // set op
    p->op = (int)ibc->type;

    int issue = 0;
    for (int j = 0; j < i; j++) {
      if (p->src == inss.op[j].dst || p->dst == inss.op[j].dst ||
          ibc->type == CBRANCH || (i > 0 && inss.op[i - 1].op == (int)ISTORE)) {
        issue = 1;
        break;
      }
    }

    if (i >= INS_ISSUE || issue) {
      // printf("issue %d\n", i);
      POKC(issue_instruction);
      i = 0;
    }

    inss.op[i].src = p->src;
    inss.op[i].dst = p->dst;
    inss.op[i].op  = p->op;
    i++;

    // if(dump_instr)
    // 	printf("> %03x: %-7s (%02x)  %d, %d, #0x%08x (m=%d, s=%d, c=%d)\n",
    // 		pc, op_info[(int)ibc->type].name, instr.opcode, instr.dst & 7,
    // 		instr.src & 7, instr.imm32, instr.getModMem(),
    // instr.getModShift(), 		instr.getModCond());
    executeInstruction(ibc, &pc, scratchpad, config);
    // if(dump_instr) {
    // 	if (op_info[(int)ibc->type].mem & 2)
    // 		printf("  - m: %016lx @ %08x\n", *(uint64_t *)(scratchpad +
    // ((*ibc->idst + ibc->imm) & ibc->memMask)),
    // 		 ((*ibc->idst + ibc->imm) & ibc->memMask));
    // 	else
    // 		printf("  - i: %016lx, f: %016lx %016lx\n", *ibc->idst,
    // *(uint64_t
    // *)ibc->fdst,
    // 		*((uint64_t *)ibc->fdst + 1));
    // }

    cmpRegs(instr->opcode, 0, st_ic, st_nreg);
  }
}

void *getScratchpadAddress(InstructionByteCode_t *ibc, uint8_t *scratchpad) {
  uint32_t addr = (*ibc->isrc + ibc->imm) & ibc->memMask;
  return scratchpad + addr;
}

rx_vec_f128 maskRegisterExponentMantissa(ProgramConfiguration_t *config,
                                         rx_vec_f128 x) {
  const rx_vec_f128 xmantissaMask =
      rx_set_vec_f128(dynamicMantissaMask, dynamicMantissaMask);
  const rx_vec_f128 xexponentMask =
      rx_load_vec_f128((const double *)config->eMask);
  x = rx_and_vec_f128(x, xmantissaMask);
  x = rx_or_vec_f128(x, xexponentMask);
  return x;
}

void exe_IADD_RS(RANDOMX_EXE_ARGS) {
  *ibc->idst += (*ibc->isrc << ibc->shift) + ibc->imm;
}

void exe_IADD_M(RANDOMX_EXE_ARGS) {
  *ibc->idst += load64(getScratchpadAddress(ibc, scratchpad));
}

void exe_ISUB_R(RANDOMX_EXE_ARGS) { *ibc->idst -= *ibc->isrc; }

void exe_ISUB_M(RANDOMX_EXE_ARGS) {
  *ibc->idst -= load64(getScratchpadAddress(ibc, scratchpad));
}

void exe_IMUL_R(RANDOMX_EXE_ARGS) { *ibc->idst *= *ibc->isrc; }

void exe_IMUL_M(RANDOMX_EXE_ARGS) {
  *ibc->idst *= load64(getScratchpadAddress(ibc, scratchpad));
}

void exe_IMULH_R(RANDOMX_EXE_ARGS) {
  *ibc->idst = mulh(*ibc->idst, *ibc->isrc);
}

void exe_IMULH_M(RANDOMX_EXE_ARGS) {
  *ibc->idst = mulh(*ibc->idst, load64(getScratchpadAddress(ibc, scratchpad)));
}

void exe_ISMULH_R(RANDOMX_EXE_ARGS) {
  *ibc->idst = smulh(unsigned64ToSigned2sCompl(*ibc->idst),
                     unsigned64ToSigned2sCompl(*ibc->isrc));
}

void exe_ISMULH_M(RANDOMX_EXE_ARGS) {
  *ibc->idst = smulh(
      unsigned64ToSigned2sCompl(*ibc->idst),
      unsigned64ToSigned2sCompl(load64(getScratchpadAddress(ibc, scratchpad))));
}

void exe_INEG_R(RANDOMX_EXE_ARGS) {
  *ibc->idst = ~(*ibc->idst) + 1; // two's complement negative
}

void exe_IXOR_R(RANDOMX_EXE_ARGS) { *ibc->idst ^= *ibc->isrc; }

void exe_IXOR_M(RANDOMX_EXE_ARGS) {
  *ibc->idst ^= load64(getScratchpadAddress(ibc, scratchpad));
}

void exe_IROR_R(RANDOMX_EXE_ARGS) {
  *ibc->idst = rotr(*ibc->idst, *ibc->isrc & 63);
}

void exe_IROL_R(RANDOMX_EXE_ARGS) {
  *ibc->idst = rotl(*ibc->idst, *ibc->isrc & 63);
}

void exe_ISWAP_R(RANDOMX_EXE_ARGS) {
  int_reg_t temp          = *ibc->isrc;
  *(int_reg_t *)ibc->isrc = *ibc->idst;
  *ibc->idst              = temp;
}

void exe_FSWAP_R(RANDOMX_EXE_ARGS) {
  *ibc->fdst = rx_swap_vec_f128(*ibc->fdst);
}

void exe_FADD_R(RANDOMX_EXE_ARGS) {
  *ibc->fdst = rx_add_vec_f128(*ibc->fdst, *ibc->fsrc);
}

void exe_FADD_M(RANDOMX_EXE_ARGS) {
  rx_vec_f128 fsrc =
      rx_cvt_packed_int_vec_f128(getScratchpadAddress(ibc, scratchpad));
  *ibc->fdst = rx_add_vec_f128(*ibc->fdst, fsrc);
}

void exe_FSUB_R(RANDOMX_EXE_ARGS) {
  *ibc->fdst = rx_sub_vec_f128(*ibc->fdst, *ibc->fsrc);
}

void exe_FSUB_M(RANDOMX_EXE_ARGS) {
  rx_vec_f128 fsrc =
      rx_cvt_packed_int_vec_f128(getScratchpadAddress(ibc, scratchpad));
  *ibc->fdst = rx_sub_vec_f128(*ibc->fdst, fsrc);
}

void exe_FSCAL_R(RANDOMX_EXE_ARGS) {
  const rx_vec_f128 mask = rx_set1_vec_f128(0x80F0000000000000);
  *ibc->fdst             = rx_xor_vec_f128(*ibc->fdst, mask);
}

void exe_FMUL_R(RANDOMX_EXE_ARGS) {
  *ibc->fdst = rx_mul_vec_f128(*ibc->fdst, *ibc->fsrc);
}

void exe_FDIV_M(RANDOMX_EXE_ARGS) {
  rx_vec_f128 fsrc = maskRegisterExponentMantissa(
      config,
      rx_cvt_packed_int_vec_f128(getScratchpadAddress(ibc, scratchpad)));
  *ibc->fdst = rx_div_vec_f128(*ibc->fdst, fsrc);
}

void exe_FSQRT_R(RANDOMX_EXE_ARGS) {
  *ibc->fdst = rx_sqrt_vec_f128(*ibc->fdst);
}

void exe_CBRANCH(RANDOMX_EXE_ARGS) {
  *ibc->idst += ibc->imm;
  if ((*ibc->idst & ibc->memMask) == 0) {
    *pc = ibc->target;
    if (dump_instr)
      printf("** branch took %d\n", *pc);
  }
}

void exe_CFROUND(RANDOMX_EXE_ARGS) {
  rx_set_rounding_mode(rotr(*ibc->isrc, ibc->imm) % 4);
}

void exe_ISTORE(RANDOMX_EXE_ARGS) {
  store64(scratchpad + ((*ibc->idst + ibc->imm) & ibc->memMask), *ibc->isrc);
}
#define INSTR_CASE(x)                                                          \
  case x:                                                                      \
    exe_##x(ibc, pc, scratchpad, config);                                      \
    break;

void executeInstruction(RANDOMX_EXE_ARGS) {
  switch (ibc->type) {
    INSTR_CASE(IADD_RS)
    INSTR_CASE(IADD_M)
    INSTR_CASE(ISUB_R)
    INSTR_CASE(ISUB_M)
    INSTR_CASE(IMUL_R)
    INSTR_CASE(IMUL_M)
    INSTR_CASE(IMULH_R)
    INSTR_CASE(IMULH_M)
    INSTR_CASE(ISMULH_R)
    INSTR_CASE(ISMULH_M)
    INSTR_CASE(INEG_R)
    INSTR_CASE(IXOR_R)
    INSTR_CASE(IXOR_M)
    INSTR_CASE(IROR_R)
    INSTR_CASE(IROL_R)
    INSTR_CASE(ISWAP_R)
    INSTR_CASE(FSWAP_R)
    INSTR_CASE(FADD_R)
    INSTR_CASE(FADD_M)
    INSTR_CASE(FSUB_R)
    INSTR_CASE(FSUB_M)
    INSTR_CASE(FSCAL_R)
    INSTR_CASE(FMUL_R)
    INSTR_CASE(FDIV_M)
    INSTR_CASE(FSQRT_R)
    INSTR_CASE(CBRANCH)
    INSTR_CASE(CFROUND)
    INSTR_CASE(ISTORE)

  case NOP:
    break;

  case IMUL_RCP: // executed as IMUL_R
  default:
    UNREACHABLE;
  }
}

void compileInstruction(RANDOMX_GEN_ARGS) {
  int opcode = instr->opcode;

  if (opcode < ceil_IADD_RS) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IADD_RS;
    ibc->idst   = &nreg->r[dst];
    if (dst != RegisterNeedsDisplacement) {
      ibc->isrc  = &nreg->r[src];
      ibc->shift = Instruction_getModShift(instr);
      ibc->imm   = 0;
    } else {
      ibc->isrc  = &nreg->r[src];
      ibc->shift = Instruction_getModShift(instr);
      ibc->imm   = signExtend2sCompl(Instruction_getImm32(instr));
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IADD_M) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IADD_M;
    ibc->idst   = &nreg->r[dst];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    } else {
      ibc->isrc    = &dev->zero;
      ibc->memMask = ScratchpadL3Mask;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_ISUB_R) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = ISUB_R;
    ibc->idst   = &nreg->r[dst];
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
    } else {
      ibc->imm  = signExtend2sCompl(Instruction_getImm32(instr));
      ibc->isrc = &ibc->imm;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_ISUB_M) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = ISUB_M;
    ibc->idst   = &nreg->r[dst];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    } else {
      ibc->isrc    = &dev->zero;
      ibc->memMask = ScratchpadL3Mask;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IMUL_R) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IMUL_R;
    ibc->idst   = &nreg->r[dst];
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
    } else {
      ibc->imm  = signExtend2sCompl(Instruction_getImm32(instr));
      ibc->isrc = &ibc->imm;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IMUL_M) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IMUL_M;
    ibc->idst   = &nreg->r[dst];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    } else {
      ibc->isrc    = &dev->zero;
      ibc->memMask = ScratchpadL3Mask;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IMULH_R) {
    uint8_t dst             = instr->dst % RegistersCount;
    uint8_t src             = instr->src % RegistersCount;
    ibc->type               = IMULH_R;
    ibc->idst               = &nreg->r[dst];
    ibc->isrc               = &nreg->r[src];
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IMULH_M) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IMULH_M;
    ibc->idst   = &nreg->r[dst];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    } else {
      ibc->isrc    = &dev->zero;
      ibc->memMask = ScratchpadL3Mask;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_ISMULH_R) {
    uint8_t dst             = instr->dst % RegistersCount;
    uint8_t src             = instr->src % RegistersCount;
    ibc->type               = ISMULH_R;
    ibc->idst               = &nreg->r[dst];
    ibc->isrc               = &nreg->r[src];
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_ISMULH_M) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = ISMULH_M;
    ibc->idst   = &nreg->r[dst];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    } else {
      ibc->isrc    = &dev->zero;
      ibc->memMask = ScratchpadL3Mask;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IMUL_RCP) {
    uint64_t divisor = Instruction_getImm32(instr);
    if (!isZeroOrPowerOf2(divisor)) {
      uint8_t dst             = instr->dst % RegistersCount;
      ibc->type               = IMUL_R;
      ibc->idst               = &nreg->r[dst];
      ibc->imm                = randomx_reciprocal(divisor);
      ibc->isrc               = &ibc->imm;
      dev->registerUsage[dst] = i;
    } else {
      ibc->type = NOP;
    }
    return;
  }

  if (opcode < ceil_INEG_R) {
    uint8_t dst             = instr->dst % RegistersCount;
    ibc->type               = INEG_R;
    ibc->idst               = &nreg->r[dst];
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IXOR_R) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IXOR_R;
    ibc->idst   = &nreg->r[dst];
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
    } else {
      ibc->imm  = signExtend2sCompl(Instruction_getImm32(instr));
      ibc->isrc = &ibc->imm;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IXOR_M) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IXOR_M;
    ibc->idst   = &nreg->r[dst];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    } else {
      ibc->isrc    = &dev->zero;
      ibc->memMask = ScratchpadL3Mask;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IROR_R) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IROR_R;
    ibc->idst   = &nreg->r[dst];
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
    } else {
      ibc->imm  = Instruction_getImm32(instr);
      ibc->isrc = &ibc->imm;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_IROL_R) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = IROL_R;
    ibc->idst   = &nreg->r[dst];
    if (src != dst) {
      ibc->isrc = &nreg->r[src];
    } else {
      ibc->imm  = Instruction_getImm32(instr);
      ibc->isrc = &ibc->imm;
    }
    dev->registerUsage[dst] = i;
    return;
  }

  if (opcode < ceil_ISWAP_R) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    if (src != dst) {
      ibc->idst               = &nreg->r[dst];
      ibc->isrc               = &nreg->r[src];
      ibc->type               = ISWAP_R;
      dev->registerUsage[dst] = i;
      dev->registerUsage[src] = i;
    } else {
      ibc->type = NOP;
    }
    return;
  }

  if (opcode < ceil_FSWAP_R) {
    uint8_t dst = instr->dst % RegistersCount;
    ibc->type   = FSWAP_R;
    if (dst < RegisterCountFlt)
      ibc->fdst = &nreg->f[dst];
    else
      ibc->fdst = &nreg->e[dst - RegisterCountFlt];
    return;
  }

  if (opcode < ceil_FADD_R) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    uint8_t src = instr->src % RegisterCountFlt;
    ibc->type   = FADD_R;
    ibc->fdst   = &nreg->f[dst];
    ibc->fsrc   = &nreg->a[src];
    return;
  }

  if (opcode < ceil_FADD_M) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = FADD_M;
    ibc->fdst   = &nreg->f[dst];
    ibc->isrc   = &nreg->r[src];
    ibc->memMask =
        (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    ibc->imm = signExtend2sCompl(Instruction_getImm32(instr));
    return;
  }

  if (opcode < ceil_FSUB_R) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    uint8_t src = instr->src % RegisterCountFlt;
    ibc->type   = FSUB_R;
    ibc->fdst   = &nreg->f[dst];
    ibc->fsrc   = &nreg->a[src];
    return;
  }

  if (opcode < ceil_FSUB_M) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = FSUB_M;
    ibc->fdst   = &nreg->f[dst];
    ibc->isrc   = &nreg->r[src];
    ibc->memMask =
        (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    ibc->imm = signExtend2sCompl(Instruction_getImm32(instr));
    return;
  }

  if (opcode < ceil_FSCAL_R) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    ibc->fdst   = &nreg->f[dst];
    ibc->type   = FSCAL_R;
    return;
  }

  if (opcode < ceil_FMUL_R) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    uint8_t src = instr->src % RegisterCountFlt;
    ibc->type   = FMUL_R;
    ibc->fdst   = &nreg->e[dst];
    ibc->fsrc   = &nreg->a[src];
    return;
  }

  if (opcode < ceil_FDIV_M) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = FDIV_M;
    ibc->fdst   = &nreg->e[dst];
    ibc->isrc   = &nreg->r[src];
    ibc->memMask =
        (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    ibc->imm = signExtend2sCompl(Instruction_getImm32(instr));
    return;
  }

  if (opcode < ceil_FSQRT_R) {
    uint8_t dst = instr->dst % RegisterCountFlt;
    ibc->type   = FSQRT_R;
    ibc->fdst   = &nreg->e[dst];
    return;
  }

  if (opcode < ceil_CBRANCH) {
    ibc->type = CBRANCH;
    // jump condition
    int creg    = instr->dst % RegistersCount;
    ibc->idst   = &nreg->r[creg];
    ibc->target = dev->registerUsage[creg];
    int shift   = Instruction_getModCond(instr) + ConditionOffset;
    ibc->imm = signExtend2sCompl(Instruction_getImm32(instr)) | (1ULL << shift);
    if (ConditionOffset > 0 ||
        shift > 0) // clear the bit below the condition mask - this limits the
                   // number of successive jumps to 2
      ibc->imm &= ~(1ULL << (shift - 1));
    ibc->memMask = ConditionMask << shift;
    // mark all registers as used
    for (unsigned j = 0; j < RegistersCount; ++j) {
      dev->registerUsage[j] = i;
    }
    return;
  }

  if (opcode < ceil_CFROUND) {
    uint8_t src = instr->src % RegistersCount;
    ibc->isrc   = &nreg->r[src];
    ibc->type   = CFROUND;
    ibc->imm    = Instruction_getImm32(instr) & 63;
    return;
  }

  if (opcode < ceil_ISTORE) {
    uint8_t dst = instr->dst % RegistersCount;
    uint8_t src = instr->src % RegistersCount;
    ibc->type   = ISTORE;
    ibc->idst   = &nreg->r[dst];
    ibc->isrc   = &nreg->r[src];
    ibc->imm    = signExtend2sCompl(Instruction_getImm32(instr));
    if (Instruction_getModCond(instr) < StoreL3Condition)
      ibc->memMask =
          (Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
    else
      ibc->memMask = ScratchpadL3Mask;
    return;
  }

  if (opcode < ceil_NOP) {
    ibc->type = NOP;
    return;
  }

  UNREACHABLE;
}
