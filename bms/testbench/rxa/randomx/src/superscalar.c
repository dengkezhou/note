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

#include "superscalar.h"
#include "blake2/endian.h"
#include "rxa_common.h"
#include "configuration.h"
#include "cvector.h"
#include "intrin_portable.h"
#include "program.h"
#include "reciprocal.h"


uint32_t SSP_getSize(SuperscalarProgram_t *ss) { return ss->size; }
void SSP_setSize(SuperscalarProgram_t *ss, uint32_t val) {
  ss->size = val;
}
int SSP_getAddressRegister(SuperscalarProgram_t *ss) {
  return ss->addrReg;
}
void SSP_setAddressRegister(SuperscalarProgram_t *ss, int val) {
  ss->addrReg = val;
}

Instruction_t *SSP_getInstruction(SuperscalarProgram_t *ss, int pc) {
  return &(ss->programBuffer[pc]);
}

void SSP_print(SuperscalarProgram_t *ss) {
  for (unsigned i = 0; i < ss->size; ++i) {
    printInstruction(SSP_getInstruction(ss, i));
  }
}

static bool isMultiplication(enum SuperscalarInstructionType type) {
  return type == SS_IMUL_R || type == SS_IMULH_R || type == SS_ISMULH_R ||
         type == SS_IMUL_RCP;
}

enum ExecutionPort_type {
  ExecutionPort_NULL,
  ExecutionPort_P0,
  ExecutionPort_P1,
  ExecutionPort_P5   = 4,
  ExecutionPort_P01  = (ExecutionPort_P0 | ExecutionPort_P1),
  ExecutionPort_P05  = (ExecutionPort_P0 | ExecutionPort_P5),
  ExecutionPort_P015 = (ExecutionPort_P0 | ExecutionPort_P1 | ExecutionPort_P5)
};

typedef struct MacroOp {
  char *name_;
  int size_;
  int latency_;
  int uop1_;
  int uop2_;
  bool dependent_;
} MacroOp_t;

const char *MacroOp_getName(MacroOp_t *op) { return op->name_; }
int MacroOp_getSize(MacroOp_t *op) { return op->size_; }
int MacroOp_getLatency(MacroOp_t *op) { return op->latency_; }
int MacroOp_getUop1(MacroOp_t *op) { return op->uop1_; }
int MacroOp_getUop2(MacroOp_t *op) { return op->uop2_; }
bool MacroOp_isSimple(MacroOp_t *op) { return op->uop2_ == ExecutionPort_NULL; }
bool MacroOp_isEliminated(MacroOp_t *op) {
  return op->uop1_ == ExecutionPort_NULL;
}
bool MacroOp_isDependent(MacroOp_t *op) { return op->dependent_; }

#define MacroOp(name, size, latency, uop1, uop2, dependent)                    \
  {                                                                            \
    .name_ = name, .size_ = size, .latency_ = latency, .uop1_ = uop1,          \
    .uop2_ = uop2, .dependent_ = dependent                                     \
  }

// Size: 3 bytes
MacroOp_t Sub_rr =
    MacroOp("sub r,r", 3, 1, ExecutionPort_P015, ExecutionPort_NULL, false);
MacroOp_t Xor_rr =
    MacroOp("xor r,r", 3, 1, ExecutionPort_P015, ExecutionPort_NULL, false);
MacroOp_t Imul_r =
    MacroOp("imul r", 3, 4, ExecutionPort_P1, ExecutionPort_P5, false);
MacroOp_t Mul_r =
    MacroOp("mul r", 3, 4, ExecutionPort_P1, ExecutionPort_P5, false);
MacroOp_t Mov_rr =
    MacroOp("mov r,r", 3, 0, ExecutionPort_NULL, ExecutionPort_NULL, false);

// Size: 4 bytes
MacroOp_t Lea_sib =
    MacroOp("lea r,r+r*s", 4, 1, ExecutionPort_P01, ExecutionPort_NULL, false);
MacroOp_t Imul_rr =
    MacroOp("imul r,r", 4, 3, ExecutionPort_P1, ExecutionPort_NULL, false);
MacroOp_t Ror_ri =
    MacroOp("ror r,i", 4, 1, ExecutionPort_P05, ExecutionPort_NULL, false);

// Size: 7 bytes (can be optionally padded with nop to 8 or 9 bytes)
MacroOp_t Add_ri =
    MacroOp("add r,i", 7, 1, ExecutionPort_P015, ExecutionPort_NULL, false);
MacroOp_t Xor_ri =
    MacroOp("xor r,i", 7, 1, ExecutionPort_P015, ExecutionPort_NULL, false);

// Size: 10 bytes
MacroOp_t Mov_ri64 = MacroOp("mov rax,i64", 10, 1, ExecutionPort_P015,
                             ExecutionPort_NULL, false);

MacroOp_t IMULH_R_ops_array[] = {
    MacroOp("mov r,r", 3, 0, ExecutionPort_NULL, ExecutionPort_NULL, false),
    MacroOp("mul r", 3, 4, ExecutionPort_P1, ExecutionPort_P5, false),
    MacroOp("mov r,r", 3, 0, ExecutionPort_NULL, ExecutionPort_NULL, false)};
MacroOp_t ISMULH_R_ops_array[] = {
    MacroOp("mov r,r", 3, 0, ExecutionPort_NULL, ExecutionPort_NULL, false),
    MacroOp("imul r", 3, 4, ExecutionPort_P1, ExecutionPort_P5, false),
    MacroOp("mov r,r", 3, 0, ExecutionPort_NULL, ExecutionPort_NULL, false)};
MacroOp_t IMUL_RCP_ops_array[] = {
    MacroOp("mov rax,i64", 10, 1, ExecutionPort_P015, ExecutionPort_NULL,
            false),
    MacroOp("imul r,r", 4, 3, ExecutionPort_P1, ExecutionPort_NULL, true)};

typedef struct SuperscalarInstructionInfo {
  const char *name_;
  enum SuperscalarInstructionType type_;
  MacroOp_t *ops_;
  int opslen_;
  int latency_;
  int resultOp_;
  int dstOp_;
  int srcOp_;
} SuperscalarInstructionInfo_t;

static int MacroOp_getTotalLatency(MacroOp_t *ops, int len);

const char *SII_getName(SuperscalarInstructionInfo_t *info) {
  return info->name_;
}
int SII_getSize(SuperscalarInstructionInfo_t *info) { return info->opslen_; }
bool SII_isSimple(SuperscalarInstructionInfo_t *info) {
  return SII_getSize(info) == 1;
}
int SII_getLatency(SuperscalarInstructionInfo_t *info) {
  if (info->latency_ < 0)
    info->latency_ = MacroOp_getTotalLatency(info->ops_, info->opslen_);

  return info->latency_;
}
MacroOp_t *SII_getOp(SuperscalarInstructionInfo_t *info, int index) {
  return &info->ops_[index];
}
enum SuperscalarInstructionType
SII_getType(SuperscalarInstructionInfo_t *info) {
  return info->type_;
}
int SII_getResultOp(SuperscalarInstructionInfo_t *info) {
  return info->resultOp_;
}
int SII_getDstOp(SuperscalarInstructionInfo_t *info) { return info->dstOp_; }
int SII_getSrcOp(SuperscalarInstructionInfo_t *info) { return info->srcOp_; }

int MacroOp_getTotalLatency(MacroOp_t *ops, int len) {
  int latency_ = 0;

  if (!len)
    return 0;

  for (int i = 0; i < len; i++) {
    latency_ += MacroOp_getLatency(&ops[i]);
  }
  return latency_;
}

#define SuperscalarInstructionInfo(name, type, ops, opslen, resultOp, dstOp,   \
                                   srcOp)                                      \
  {                                                                            \
    .name_ = name, .type_ = type, .ops_ = ops, .opslen_ = opslen,              \
    .latency_ = -1, .resultOp_ = resultOp, .dstOp_ = dstOp, .srcOp_ = srcOp    \
  }

SuperscalarInstructionInfo_t SII_ISUB_R =
    SuperscalarInstructionInfo("ISUB_R", SS_ISUB_R, &Sub_rr, 1, 0, 0, 0);
SuperscalarInstructionInfo_t SII_IXOR_R =
    SuperscalarInstructionInfo("IXOR_R", SS_IXOR_R, &Xor_rr, 1, 0, 0, 0);
SuperscalarInstructionInfo_t SII_IADD_RS =
    SuperscalarInstructionInfo("IADD_RS", SS_IADD_RS, &Lea_sib, 1, 0, 0, 0);
SuperscalarInstructionInfo_t SII_IMUL_R =
    SuperscalarInstructionInfo("IMUL_R", SS_IMUL_R, &Imul_rr, 1, 0, 0, 0);
SuperscalarInstructionInfo_t SII_IROR_C =
    SuperscalarInstructionInfo("IROR_C", SS_IROR_C, &Ror_ri, 1, 0, 0, -1);

SuperscalarInstructionInfo_t SII_IADD_C7 =
    SuperscalarInstructionInfo("IADD_C7", SS_IADD_C7, &Add_ri, 1, 0, 0, -1);
SuperscalarInstructionInfo_t SII_IXOR_C7 =
    SuperscalarInstructionInfo("IXOR_C7", SS_IXOR_C7, &Xor_ri, 1, 0, 0, -1);
SuperscalarInstructionInfo_t SII_IADD_C8 =
    SuperscalarInstructionInfo("IADD_C8", SS_IADD_C8, &Add_ri, 1, 0, 0, -1);
SuperscalarInstructionInfo_t SII_IXOR_C8 =
    SuperscalarInstructionInfo("IXOR_C8", SS_IXOR_C8, &Xor_ri, 1, 0, 0, -1);
SuperscalarInstructionInfo_t SII_IADD_C9 =
    SuperscalarInstructionInfo("IADD_C9", SS_IADD_C9, &Add_ri, 1, 0, 0, -1);
SuperscalarInstructionInfo_t SII_IXOR_C9 =
    SuperscalarInstructionInfo("IXOR_C9", SS_IXOR_C9, &Xor_ri, 1, 0, 0, -1);

SuperscalarInstructionInfo_t SII_IMULH_R = SuperscalarInstructionInfo(
    "IMULH_R", SS_IMULH_R, IMULH_R_ops_array, 3, 1, 0, 1);
SuperscalarInstructionInfo_t SII_ISMULH_R = SuperscalarInstructionInfo(
    "ISMULH_R", SS_ISMULH_R, ISMULH_R_ops_array, 3, 1, 0, 1);
SuperscalarInstructionInfo_t SII_IMUL_RCP = SuperscalarInstructionInfo(
    "IMUL_RCP", SS_IMUL_RCP, IMUL_RCP_ops_array, 2, 1, 1, -1);

SuperscalarInstructionInfo_t SII_NOP =
    SuperscalarInstructionInfo("NOP", SS_INVALID, NULL, 0, 0, 0, 0);

// these are some of the options how to split a 16-byte window into 3 or 4 x86
// instructions. RandomX uses instructions with a native size of 3 (sub, xor,
// mul, mov), 4 (lea, mul), 7 (xor, add immediate) or 10 bytes (mov 64-bit
// immediate). Slots with sizes of 8 or 9 bytes need to be padded with a nop
// instruction.
typedef struct DecoderBuffer {
  char *name_;
  int index_;
  int *counts_;
  int opsCount_;
} DecoderBuffer_t;

#define DecoderBuffer(name, index, counts, opsCount)                           \
  { .name_ = name, .index_ = index, .counts_ = counts, .opsCount_ = opsCount }

int buffer0[] = {4, 8, 4};
int buffer1[] = {7, 3, 3, 3};
int buffer2[] = {3, 7, 3, 3};
int buffer3[] = {4, 9, 3};
int buffer4[] = {4, 4, 4, 4};
int buffer5[] = {3, 3, 10};

int *DecoderBuffer_getCounts(DecoderBuffer_t *buffer) {
  return buffer->counts_;
}
int DecoderBuffer_getSize(DecoderBuffer_t *buffer) { return buffer->opsCount_; }
int DecoderBuffer_getIndex(DecoderBuffer_t *buffer) { return buffer->index_; }
char *DecoderBuffer_getName(DecoderBuffer_t *buffer) { return buffer->name_; }

DecoderBuffer_t decodeBuffer484  = DecoderBuffer("4,8,4", 0, buffer0, 3);
DecoderBuffer_t decodeBuffer7333 = DecoderBuffer("7,3,3,3", 1, buffer1, 4);
DecoderBuffer_t decodeBuffer3733 = DecoderBuffer("3,7,3,3", 2, buffer2, 4);
DecoderBuffer_t decodeBuffer493  = DecoderBuffer("4,9,3", 3, buffer3, 3);
DecoderBuffer_t decodeBuffer4444 = DecoderBuffer("4,4,4,4", 4, buffer4, 4);
DecoderBuffer_t decodeBuffer3310 = DecoderBuffer("3,3,10", 5, buffer5, 3);
DecoderBuffer_t decodeDefault    = DecoderBuffer(NULL, -1, NULL, 0);

DecoderBuffer_t *decodeBuffers[4] = {
    &decodeBuffer484,
    &decodeBuffer7333,
    &decodeBuffer3733,
    &decodeBuffer493,
};

DecoderBuffer_t *DecoderBuffer_fetchNextDefault(Blake2Generator_t *gen) {
  return decodeBuffers[Blake2Generator_getByte(gen) & 3];
}

DecoderBuffer_t *
DecoderBuffer_fetchNext(enum SuperscalarInstructionType instrType, int cycle,
                        int mulCount, Blake2Generator_t *gen) {
  // If the current RandomX instruction is "IMULH", the next fetch configuration
  // must be 3-3-10 because the full 128-bit multiplication instruction is 3
  // bytes long and decodes to 2 uOPs on Intel CPUs. Intel CPUs can decode at
  // most 4 uOPs per cycle, so this requires a 2-1-1 configuration for a total of
  // 3 macro ops.
  if (instrType == SS_IMULH_R || instrType == SS_ISMULH_R)
    return &decodeBuffer3310;

  // To make sure that the multiplication port is saturated, a 4-4-4-4
  // configuration is generated if the number of multiplications is lower than
  // the number of cycles.
  if (mulCount < cycle + 1)
    return &decodeBuffer4444;

  // If the current RandomX instruction is "IMUL_RCP", the next buffer must
  // begin with a 4-byte slot for multiplication.
  if (instrType == SS_IMUL_RCP)
    return (Blake2Generator_getByte(gen) & 1) ? &decodeBuffer484
                                              : &decodeBuffer493;

  // Default: select a random fetch configuration.
  return DecoderBuffer_fetchNextDefault(gen);
}

SuperscalarInstructionInfo_t *slot_3[]  = {&SII_ISUB_R, &SII_IXOR_R};
SuperscalarInstructionInfo_t *slot_3L[] = {&SII_ISUB_R, &SII_IXOR_R,
                                           &SII_IMULH_R, &SII_ISMULH_R};
SuperscalarInstructionInfo_t *slot_4[]  = {&SII_IROR_C, &SII_IADD_RS};
SuperscalarInstructionInfo_t *slot_7[]  = {&SII_IXOR_C7, &SII_IADD_C7};
SuperscalarInstructionInfo_t *slot_8[]  = {&SII_IXOR_C8, &SII_IADD_C8};
SuperscalarInstructionInfo_t *slot_9[]  = {&SII_IXOR_C9, &SII_IADD_C9};
SuperscalarInstructionInfo_t *slot_10   = &SII_IMUL_RCP;

static bool selectRegister(cvector availableRegisters, Blake2Generator_t *gen,
                           int *reg) {
  int index;

  if (cvector_length(availableRegisters) == 0)
    return false;

  if (cvector_length(availableRegisters) > 1) {
    index = Blake2Generator_getUInt32(gen) % cvector_length(availableRegisters);
  } else {
    index = 0;
  }
  cvector_val_at(availableRegisters, index, reg);
  return true;
}

typedef struct RegisterInfo {
  int latency;
  enum SuperscalarInstructionType lastOpGroup;
  int lastOpPar;
  int value;
} RegisterInfo_t;

void init_registerInfos(RegisterInfo_t *info, int num) {
  for (int i = 0; i < num; i++) {
    info[i].latency     = 0;
    info[i].lastOpGroup = SS_INVALID;
    info[i].lastOpPar   = -1;
    info[i].value       = 0;
  }
}

typedef struct SuperscalarInstruction {
  SuperscalarInstructionInfo_t *info_;
  int src_;
  int dst_;
  int mod_;
  uint32_t imm32_;
  enum SuperscalarInstructionType opGroup_;
  int opGroupPar_;
  bool canReuse_;
  bool groupParIsSource_;
} SuperscalarInstruction_t;

enum SuperscalarInstructionType SSI_getType(SuperscalarInstruction_t *ssInstr) {
  return SII_getType(ssInstr->info_);
}
int SSI_getSource(SuperscalarInstruction_t *ssInstr) { return ssInstr->src_; }
int SSI_getDestination(SuperscalarInstruction_t *ssInstr) {
  return ssInstr->dst_;
}
enum SuperscalarInstructionType
SSI_getGroup(SuperscalarInstruction_t *ssInstr) {
  return ssInstr->opGroup_;
}
int SSI_getGroupPar(SuperscalarInstruction_t *ssInstr) {
  return ssInstr->opGroupPar_;
}

SuperscalarInstructionInfo_t *SSI_getInfo(SuperscalarInstruction_t *ssInstr) {
  return ssInstr->info_;
}

void SSI_init(SuperscalarInstruction_t *ssInstr,
              SuperscalarInstructionInfo_t *info) {
  ssInstr->src_              = -1;
  ssInstr->dst_              = -1;
  ssInstr->canReuse_         = false;
  ssInstr->groupParIsSource_ = false;
  ssInstr->info_             = info;
}

void SSI_reset(SuperscalarInstruction_t *ssInstr) {
  ssInstr->src_ = ssInstr->dst_ = -1;
  ssInstr->canReuse_ = ssInstr->groupParIsSource_ = false;
}
//"SuperscalarInstruction" consists of one or more macro-ops
void SSI_toInstr(
    SuperscalarInstruction_t *ssInstr,
    Instruction_t *instr) { // translate to a RandomX instruction format
  instr->opcode = SSI_getType(ssInstr);
  instr->dst    = ssInstr->dst_;
  instr->src    = ssInstr->src_ >= 0 ? ssInstr->src_ : ssInstr->dst_;
  Instruction_setMod(instr, ssInstr->mod_);
  Instruction_setImm32(instr, ssInstr->imm32_);
}

void SSI_create(SuperscalarInstruction_t *ssInstr,
                SuperscalarInstructionInfo_t *info, Blake2Generator_t *gen);

void SSI_createForSlot(SuperscalarInstruction_t *ssInstr,
                       Blake2Generator_t *gen, int slotSize, int fetchType,
                       bool isLast, bool isFirst) {
  switch (slotSize) {
  case 3:
    // if this is the last slot, we can also select "IMULH" instructions
    if (isLast) {
      SSI_create(ssInstr, slot_3L[Blake2Generator_getByte(gen) & 3], gen);
    } else {
      SSI_create(ssInstr, slot_3[Blake2Generator_getByte(gen) & 1], gen);
    }
    break;
  case 4:
    // if this is the 4-4-4-4 buffer, issue multiplications as the first 3
    // instructions
    if (fetchType == 4 && !isLast) {
      SSI_create(ssInstr, &SII_IMUL_R, gen);
    } else {
      SSI_create(ssInstr, slot_4[Blake2Generator_getByte(gen) & 1], gen);
    }
    break;
  case 7:
    SSI_create(ssInstr, slot_7[Blake2Generator_getByte(gen) & 1], gen);
    break;
  case 8:
    SSI_create(ssInstr, slot_8[Blake2Generator_getByte(gen) & 1], gen);
    break;
  case 9:
    SSI_create(ssInstr, slot_9[Blake2Generator_getByte(gen) & 1], gen);
    break;
  case 10:
    SSI_create(ssInstr, slot_10, gen);
    break;
  default:
    UNREACHABLE;
  }
}

void SSI_create(SuperscalarInstruction_t *ssInstr,
                SuperscalarInstructionInfo_t *info, Blake2Generator_t *gen) {
  ssInstr->info_ = info;
  SSI_reset(ssInstr);
  switch (SSI_getType(ssInstr)) {
  case SS_ISUB_R: {
    ssInstr->mod_              = 0;
    ssInstr->imm32_            = 0;
    ssInstr->opGroup_          = SS_IADD_RS;
    ssInstr->groupParIsSource_ = true;
  } break;

  case SS_IXOR_R: {
    ssInstr->mod_              = 0;
    ssInstr->imm32_            = 0;
    ssInstr->opGroup_          = SS_IXOR_R;
    ssInstr->groupParIsSource_ = true;
  } break;

  case SS_IADD_RS: {
    ssInstr->mod_              = Blake2Generator_getByte(gen);
    ssInstr->imm32_            = 0;
    ssInstr->opGroup_          = SS_IADD_RS;
    ssInstr->groupParIsSource_ = true;
  } break;

  case SS_IMUL_R: {
    ssInstr->mod_              = 0;
    ssInstr->imm32_            = 0;
    ssInstr->opGroup_          = SS_IMUL_R;
    ssInstr->groupParIsSource_ = true;
  } break;

  case SS_IROR_C: {
    ssInstr->mod_ = 0;
    do {
      ssInstr->imm32_ = Blake2Generator_getByte(gen) & 63;
    } while (ssInstr->imm32_ == 0);
    ssInstr->opGroup_    = SS_IROR_C;
    ssInstr->opGroupPar_ = -1;
  } break;

  case SS_IADD_C7:
  case SS_IADD_C8:
  case SS_IADD_C9: {
    ssInstr->mod_        = 0;
    ssInstr->imm32_      = Blake2Generator_getUInt32(gen);
    ssInstr->opGroup_    = SS_IADD_C7;
    ssInstr->opGroupPar_ = -1;
  } break;

  case SS_IXOR_C7:
  case SS_IXOR_C8:
  case SS_IXOR_C9: {
    ssInstr->mod_        = 0;
    ssInstr->imm32_      = Blake2Generator_getUInt32(gen);
    ssInstr->opGroup_    = SS_IXOR_C7;
    ssInstr->opGroupPar_ = -1;
  } break;

  case SS_IMULH_R: {
    ssInstr->canReuse_   = true;
    ssInstr->mod_        = 0;
    ssInstr->imm32_      = 0;
    ssInstr->opGroup_    = SS_IMULH_R;
    ssInstr->opGroupPar_ = Blake2Generator_getUInt32(gen);
  } break;

  case SS_ISMULH_R: {
    ssInstr->canReuse_   = true;
    ssInstr->mod_        = 0;
    ssInstr->imm32_      = 0;
    ssInstr->opGroup_    = SS_ISMULH_R;
    ssInstr->opGroupPar_ = Blake2Generator_getUInt32(gen);
  } break;

  case SS_IMUL_RCP: {
    ssInstr->mod_ = 0;
    do {
      ssInstr->imm32_ = Blake2Generator_getUInt32(gen);
    } while (isZeroOrPowerOf2(ssInstr->imm32_));
    ssInstr->opGroup_    = SS_IMUL_RCP;
    ssInstr->opGroupPar_ = -1;
  } break;

  default:
    break;
  }
}

bool SSI_selectDestination(SuperscalarInstruction_t *ssInstr, int cycle,
                           bool allowChainedMul, RegisterInfo_t *registers,
                           Blake2Generator_t *gen) {
  /*if (allowChainedMultiplication && opGroup_ == SS_IMUL_R)
          std::cout << "Selecting destination with chained MUL enabled" <<
     std::endl;*/
  cvector availableRegisters = cvector_create(sizeof(int));
  bool ret;
  // Conditions for the destination register:
  // * value must be ready at the required cycle
  // * cannot be the same as the source register unless the instruction allows
  // it
  //   - this avoids optimizable instructions such as "xor r, r" or "sub r, r"
  // * register cannot be multiplied twice in a row unless allowChainedMul is
  // true
  //   - this avoids accumulation of trailing zeroes in registers due to
  //   excessive multiplication
  //   - allowChainedMul is set to true if an attempt to find source/destination
  //   registers failed (this is quite rare, but prevents a catastrophic failure
  //   of the generator)
  // * either the last instruction applied to the register or its source must be
  // different than this instruction
  //   - this avoids optimizable instruction sequences such as "xor r1, r2; xor
  //   r1, r2" or "ror r, C1; ror r, C2" or "add r, C1; add r, C2"
  // * register r5 cannot be the destination of the IADD_RS instruction
  // (limitation of the x86 lea instruction)
  for (unsigned i = 0; i < 8; ++i) {
    if (registers[i].latency <= cycle &&
        (ssInstr->canReuse_ || i != ssInstr->src_) &&
        (allowChainedMul || ssInstr->opGroup_ != SS_IMUL_R ||
         registers[i].lastOpGroup != SS_IMUL_R) &&
        (registers[i].lastOpGroup != ssInstr->opGroup_ ||
         registers[i].lastOpPar != ssInstr->opGroupPar_) &&
        (SSI_getType(ssInstr) != SS_IADD_RS || i != RegisterNeedsDisplacement))
      cvector_pushback(availableRegisters, &i);
  }
  ret = selectRegister(availableRegisters, gen, &ssInstr->dst_);
  cvector_destroy(availableRegisters);
  return ret;
}

bool SSI_selectSource(SuperscalarInstruction_t *ssInstr, int cycle,
                      RegisterInfo_t *registers, Blake2Generator_t *gen) {
  cvector availableRegisters = cvector_create(sizeof(int));
  int index0, index1;
  // all registers that are ready at the cycle
  for (unsigned i = 0; i < 8; ++i) {
    if (registers[i].latency <= cycle)
      cvector_pushback(availableRegisters, &i);
  }
  // if there are only 2 available registers for IADD_RS and one of them is r5,
  // select it as the source because it cannot be the destination
  if (cvector_length(availableRegisters) == 2 &&
      SSI_getType(ssInstr) == SS_IADD_RS) {
    cvector_val_at(availableRegisters, 0, &index0);
    cvector_val_at(availableRegisters, 1, &index1);
    if (index0 == RegisterNeedsDisplacement ||
        index1 == RegisterNeedsDisplacement) {
      ssInstr->opGroupPar_ = ssInstr->src_ = RegisterNeedsDisplacement;
      cvector_destroy(availableRegisters);
      return true;
    }
  }
  if (selectRegister(availableRegisters, gen, &ssInstr->src_)) {
    if (ssInstr->groupParIsSource_)
      ssInstr->opGroupPar_ = ssInstr->src_;
    cvector_destroy(availableRegisters);
    return true;
  }
  cvector_destroy(availableRegisters);
  return false;
}

int CYCLE_MAP_SIZE      = RANDOMX_SUPERSCALAR_LATENCY + 4;
int LOOK_FORWARD_CYCLES = 4;
int MAX_THROWAWAY_COUNT = 256;

static int scheduleUop(bool commit, enum ExecutionPort_type uop,
                       enum ExecutionPort_type (*portBusy)[3], int cycle) {
  // The scheduling here is done optimistically by checking port availability in
  // order P5 -> P0 -> P1 to not overload port P1 (multiplication) by
  // instructions that can go to any port.
  for (; cycle < CYCLE_MAP_SIZE; ++cycle) {
    if ((uop & ExecutionPort_P5) != 0 && !portBusy[cycle][2]) {
      if (commit) {
        if (trace)
          printf("; P5 at cycle %d\n", cycle);
        portBusy[cycle][2] = uop;
      }
      return cycle;
    }
    if ((uop & ExecutionPort_P0) != 0 && !portBusy[cycle][0]) {
      if (commit) {
        if (trace)
          printf("; P0 at cycle %d\n", cycle);
        portBusy[cycle][0] = uop;
      }
      return cycle;
    }
    if ((uop & ExecutionPort_P1) != 0 && !portBusy[cycle][1]) {
      if (commit) {
        if (trace)
          printf("; P1 at cycle %d\n", cycle);
        portBusy[cycle][1] = uop;
      }
      return cycle;
    }
  }
  return -1;
}

static int scheduleMop(bool commit, MacroOp_t *mop,
                       enum ExecutionPort_type (*portBusy)[3], int cycle,
                       int depCycle) {
  // if this macro-op depends on the previous one, increase the starting cycle
  // if needed this handles an explicit dependency chain in IMUL_RCP
  if (MacroOp_isDependent(mop)) {
    cycle = max(cycle, depCycle);
  }
  // move instructions are eliminated and don't need an execution unit
  if (MacroOp_isEliminated(mop)) {
    if (commit)
      if (trace)
        printf("; (eliminated)\n");
    return cycle;
  } else if (MacroOp_isSimple(mop)) {
    // this macro-op has only one uOP
    return scheduleUop(commit, MacroOp_getUop1(mop), portBusy, cycle);
  } else {
    // macro-ops with 2 uOPs are scheduled conservatively by requiring both uOPs
    // to execute in the same cycle
    for (; cycle < CYCLE_MAP_SIZE; ++cycle) {

      int cycle1 = scheduleUop(false, MacroOp_getUop1(mop), portBusy, cycle);
      int cycle2 = scheduleUop(false, MacroOp_getUop2(mop), portBusy, cycle);

      if (cycle1 >= 0 && cycle1 == cycle2) {
        if (commit) {
          scheduleUop(true, MacroOp_getUop1(mop), portBusy, cycle1);
          scheduleUop(true, MacroOp_getUop2(mop), portBusy, cycle2);
        }
        return cycle1;
      }
    }
  }

  return -1;
}

void generateSuperscalar(SuperscalarProgram_t *prog, Blake2Generator_t *gen) {

  enum ExecutionPort_type portBusy[CYCLE_MAP_SIZE][3];
  memset(portBusy, 0, sizeof(portBusy));
  RegisterInfo_t registers[8];

  DecoderBuffer_t *decodeBuffer = &decodeDefault;
  SuperscalarInstruction_t currentInstruction;
  int macroOpIndex    = 0;
  int codeSize        = 0;
  int macroOpCount    = 0;
  int cycle           = 0;
  int depCycle        = 0;
  int retireCycle     = 0;
  bool portsSaturated = false;
  int programSize     = 0;
  int mulCount        = 0;
  int decodeCycle;
  int throwAwayCount = 0;

  init_registerInfos(registers, 8);
  SSI_init(&currentInstruction, &SII_NOP);
  // decode instructions for RANDOMX_SUPERSCALAR_LATENCY cycles or until an
  // execution port is saturated. Each decode cycle decodes 16 bytes of x86 code.
  // Since a decode cycle produces on average 3.45 macro-ops and there are only
  // 3 ALU ports, execution ports are always saturated first. The cycle limit is
  // present only to guarantee loop termination. Program size is limited to
  // SuperscalarMaxSize instructions.
  for (decodeCycle = 0; decodeCycle < RANDOMX_SUPERSCALAR_LATENCY &&
                        !portsSaturated && programSize < SuperscalarMaxSize;
       ++decodeCycle) {

    // select a decode configuration
    decodeBuffer = DecoderBuffer_fetchNext(SSI_getType(&currentInstruction),
                                           decodeCycle, mulCount, gen);
    if (trace)
      printf("; ------------- fetch cycle %d (%s)\n", cycle,
             DecoderBuffer_getName(decodeBuffer));

    int bufferIndex = 0;

    // fill all instruction slots in the current decode buffer
    while (bufferIndex < DecoderBuffer_getSize(decodeBuffer)) {
      int topCycle = cycle;

      // if we have issued all macro-ops for the current RandomX instruction,
      // create a new instruction
      if (macroOpIndex >= SII_getSize(SSI_getInfo(&currentInstruction))) {
        if (portsSaturated || programSize >= SuperscalarMaxSize)
          break;
        // select an instruction so that the first macro-op fits into the
        // current slot
        SSI_createForSlot(&currentInstruction, gen,
                          DecoderBuffer_getCounts(decodeBuffer)[bufferIndex],
                          DecoderBuffer_getIndex(decodeBuffer),
                          DecoderBuffer_getSize(decodeBuffer) ==
                              bufferIndex + 1,
                          bufferIndex == 0);
        macroOpIndex = 0;
        if (trace)
          printf("; %s\n", SII_getName(SSI_getInfo(&currentInstruction)));
      }
      MacroOp_t *mop =
          SII_getOp(SSI_getInfo(&currentInstruction), macroOpIndex);
      if (trace)
        printf("%s ", MacroOp_getName(mop));

      // calculate the earliest cycle when this macro-op (all of its uOPs) can
      // be scheduled for execution
      int scheduleCycle = scheduleMop(false, mop, portBusy, cycle, depCycle);
      if (scheduleCycle < 0) {
        if (trace)
          printf("Unable to map operation '%s' to execution port (cycle %d)\n",
                 MacroOp_getName(mop), cycle);
        //__debugbreak();
        portsSaturated = true;
        break;
      }

      // find a source register (if applicable) that will be ready when this
      // instruction executes
      if (macroOpIndex == SII_getSrcOp(SSI_getInfo(&currentInstruction))) {
        int forward;
        // if no suitable operand is ready, look up to LOOK_FORWARD_CYCLES
        // forward
        for (forward = 0; forward < LOOK_FORWARD_CYCLES &&
                          !SSI_selectSource(&currentInstruction, scheduleCycle,
                                            registers, gen);
             ++forward) {
          if (trace)
            printf("; src STALL at cycle %d\n", cycle);
          ++scheduleCycle;
          ++cycle;
        }
        // if no register was found, throw the instruction away and try another
        // one
        if (forward == LOOK_FORWARD_CYCLES) {
          if (throwAwayCount < MAX_THROWAWAY_COUNT) {
            throwAwayCount++;
            macroOpIndex = SII_getSize(SSI_getInfo(&currentInstruction));
            if (trace)
              printf("; THROW away %s\n",
                     SII_getName(SSI_getInfo(&currentInstruction)));
            // cycle = topCycle;
            continue;
          }
          // abort this decode buffer
          if (trace)
            printf("Aborting at cycle %d with decode buffer %s - source "
                   "registers not available for operation %s\n",
                   cycle, DecoderBuffer_getName(decodeBuffer),
                   SII_getName(SSI_getInfo(&currentInstruction)));
          SSI_init(&currentInstruction, &SII_NOP);
          break;
        }
        if (trace)
          printf("; src = r%d\n", SSI_getSource(&currentInstruction));
      }
      // find a destination register that will be ready when this instruction
      // executes
      if (macroOpIndex == SII_getDstOp(SSI_getInfo(&currentInstruction))) {
        int forward;
        for (forward = 0;
             forward < LOOK_FORWARD_CYCLES &&
             !SSI_selectDestination(&currentInstruction, scheduleCycle,
                                    throwAwayCount > 0, registers, gen);
             ++forward) {
          if (trace)
            printf("; dst STALL at cycle %d\n", cycle);
          ++scheduleCycle;
          ++cycle;
        }
        if (forward == LOOK_FORWARD_CYCLES) { // throw instruction away
          if (throwAwayCount < MAX_THROWAWAY_COUNT) {
            throwAwayCount++;
            macroOpIndex = SII_getSize(SSI_getInfo(&currentInstruction));
            if (trace)
              printf("; THROW away %s\n",
                     SII_getName(SSI_getInfo(&currentInstruction)));
            // cycle = topCycle;
            continue;
          }
          // abort this decode buffer
          if (trace)
            printf("Aborting at cycle %d with decode buffer %s - destination "
                   "registers not available\n",
                   cycle, DecoderBuffer_getName(decodeBuffer));
          SSI_init(&currentInstruction, &SII_NOP);
          break;
        }
        if (trace)
          printf("; dst = r%d\n", SSI_getDestination(&currentInstruction));
      }
      throwAwayCount = 0;

      // recalculate when the instruction can be scheduled for execution based
      // on operand availability
      scheduleCycle =
          scheduleMop(true, mop, portBusy, scheduleCycle, scheduleCycle);

      if (scheduleCycle < 0) {
        if (trace)
          printf("Unable to map operation '%s' to execution port (cycle %d)\n",
                 MacroOp_getName(mop), scheduleCycle);
        portsSaturated = true;
        break;
      }

      // calculate when the result will be ready
      depCycle = scheduleCycle + MacroOp_getLatency(mop);

      // if this instruction writes the result, modify register information
      //  RegisterInfo.latency - which cycle the register will be ready
      //  RegisterInfo.lastOpGroup - the last operation that was applied to the
      //  register RegisterInfo.lastOpPar - the last operation source value (-1
      //  = constant, 0-7 = register)
      if (macroOpIndex == SII_getResultOp(SSI_getInfo(&currentInstruction))) {
        int dst            = SSI_getDestination(&currentInstruction);
        RegisterInfo_t *ri = &registers[dst];
        retireCycle        = depCycle;
        ri->latency        = retireCycle;
        ri->lastOpGroup    = SSI_getGroup(&currentInstruction);
        ri->lastOpPar      = SSI_getGroupPar(&currentInstruction);
        if (trace)
          printf("; RETIRED at cycle %d\n", retireCycle);
      }
      codeSize += MacroOp_getSize(mop);
      bufferIndex++;
      macroOpIndex++;
      macroOpCount++;

      // terminating condition
      if (scheduleCycle >= RANDOMX_SUPERSCALAR_LATENCY) {
        portsSaturated = true;
      }
      cycle = topCycle;

      // when all macro-ops of the current instruction have been issued, add the
      // instruction into the program
      if (macroOpIndex >= SII_getSize(SSI_getInfo(&currentInstruction))) {
        SSI_toInstr(&currentInstruction,
                    SSP_getInstruction(prog, programSize++));
        mulCount += isMultiplication(SSI_getType(&currentInstruction));
      }
    }
    ++cycle;
  }

  double ipc = (macroOpCount / (double)retireCycle);

  memset(prog->asicLatencies, 0, sizeof(prog->asicLatencies));

  // Calculate ASIC latency:
  // Assumes 1 cycle latency for all operations and unlimited parallelization.
  for (int i = 0; i < programSize; ++i) {
    Instruction_t *instr = SSP_getInstruction(prog, i);
    int latDst           = prog->asicLatencies[instr->dst] + 1;
    int latSrc =
        instr->dst != instr->src ? prog->asicLatencies[instr->src] + 1 : 0;
    prog->asicLatencies[instr->dst] = max(latDst, latSrc);
  }

  // address register is the register with the highest ASIC latency
  int asicLatencyMax = 0;
  int addressReg     = 0;
  for (int i = 0; i < 8; ++i) {
    if (prog->asicLatencies[i] > asicLatencyMax) {
      asicLatencyMax = prog->asicLatencies[i];
      addressReg     = i;
    }
    prog->cpuLatencies[i] = registers[i].latency;
  }

  SSP_setSize(prog, programSize);
  SSP_setAddressRegister(prog, addressReg);

  prog->cpuLatency   = retireCycle;
  prog->asicLatency  = asicLatencyMax;
  prog->codeSize     = codeSize;
  prog->macroOps     = macroOpCount;
  prog->decodeCycles = decodeCycle;
  prog->ipc          = ipc;
  prog->mulCount     = mulCount;
}

void executeSuperscalar(int_reg_t *r, SuperscalarProgram_t *prog,
                        cvector reciprocals) {
  uint64_t value;
  for (unsigned j = 0; j < SSP_getSize(prog); ++j) {
    Instruction_t *instr = SSP_getInstruction(prog, j);
    switch ((enum SuperscalarInstructionType)instr->opcode) {
    case SS_ISUB_R:
      r[instr->dst] -= r[instr->src];
      break;
    case SS_IXOR_R:
      r[instr->dst] ^= r[instr->src];
      break;
    case SS_IADD_RS:
      r[instr->dst] += r[instr->src] << Instruction_getModShift(instr);
      break;
    case SS_IMUL_R:
      r[instr->dst] *= r[instr->src];
      break;
    case SS_IROR_C:
      r[instr->dst] = rotr(r[instr->dst], Instruction_getImm32(instr));
      break;
    case SS_IADD_C7:
    case SS_IADD_C8:
    case SS_IADD_C9:
      r[instr->dst] += signExtend2sCompl(Instruction_getImm32(instr));
      break;
    case SS_IXOR_C7:
    case SS_IXOR_C8:
    case SS_IXOR_C9:
      r[instr->dst] ^= signExtend2sCompl(Instruction_getImm32(instr));
      break;
    case SS_IMULH_R:
      r[instr->dst] = mulh(r[instr->dst], r[instr->src]);
      break;
    case SS_ISMULH_R:
      r[instr->dst] = smulh(r[instr->dst], r[instr->src]);
      break;
    case SS_IMUL_RCP:
      if (reciprocals != NULL) {
        cvector_val_at(reciprocals, Instruction_getImm32(instr), &value);
        r[instr->dst] *= value;
      } else
        r[instr->dst] *= randomx_reciprocal(Instruction_getImm32(instr));
      break;
    default:
      UNREACHABLE;
    }
  }
}
