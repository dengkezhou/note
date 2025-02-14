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

#include "jrx_x86.h"
#include "jrx_x86_static.h"
#include "program.h"
#include "reciprocal.h"
#include "superscalar.h"
#include "virtual_memory.h"
#include <jrx_core.h>
#include <limits.h>
#include <string.h>

#define MaxRandomXInstrCodeSize  32 // FDIV_M requires up to 32 bytes of x86 code
#define MaxSuperscalarInstrSize  14   // IMUL_RCP requires 14 bytes of x86 code
#define SuperscalarProgramHeader 128  // overhead per superscalar program
#define CodeAlign                4096 // align code size to a multiple of 4 KiB
#define ReserveCodeSize          CodeAlign // function prologue/epilogue + reserve

size_t RandomXCodeSize;
size_t SuperscalarSize;

uint32_t CodeSize;

int32_t superScalarHashOffset;

const uint8_t *codePrologue    = (uint8_t *)&randomx_program_prologue;
const uint8_t *codeLoopBegin   = (uint8_t *)&randomx_program_loop_begin;
const uint8_t *codeLoopLoad    = (uint8_t *)&randomx_program_loop_load;
const uint8_t *codeProgamStart = (uint8_t *)&randomx_program_start;
const uint8_t *codeReadDataset = (uint8_t *)&randomx_program_read_dataset;
const uint8_t *codeReadDatasetLightSshInit =
    (uint8_t *)&randomx_program_read_dataset_sshash_init;
const uint8_t *codeReadDatasetLightSshFin =
    (uint8_t *)&randomx_program_read_dataset_sshash_fin;
const uint8_t *codeDatasetInit = (uint8_t *)&randomx_dataset_init;
const uint8_t *codeLoopStore   = (uint8_t *)&randomx_program_loop_store;
const uint8_t *codeLoopEnd     = (uint8_t *)&randomx_program_loop_end;
const uint8_t *codeEpilogue    = (uint8_t *)&randomx_program_epilogue;
const uint8_t *codeProgramEnd  = (uint8_t *)&randomx_program_end;
const uint8_t *codeShhLoad     = (uint8_t *)&randomx_sshash_load;
const uint8_t *codeShhPrefetch = (uint8_t *)&randomx_sshash_prefetch;
const uint8_t *codeShhEnd      = (uint8_t *)&randomx_sshash_end;
const uint8_t *codeShhInit     = (uint8_t *)&randomx_sshash_init;

#define prologueSize    (codeLoopBegin - codePrologue)
#define loopLoadSize    (codeProgamStart - codeLoopLoad)
#define readDatasetSize (codeReadDatasetLightSshInit - codeReadDataset)
#define readDatasetLightInitSize                                               \
  (codeReadDatasetLightSshFin - codeReadDatasetLightSshInit)
#define readDatasetLightFinSize (codeLoopStore - codeReadDatasetLightSshFin)
#define loopStoreSize           (codeLoopEnd - codeLoopStore)
#define datasetInitSize         (codeEpilogue - codeDatasetInit)
#define epilogueSize            (codeShhLoad - codeEpilogue)
#define codeSshLoadSize         (codeShhPrefetch - codeShhLoad)
#define codeSshPrefetchSize     (codeShhEnd - codeShhPrefetch)
#define codeSshInitSize         (codeProgramEnd - codeShhInit)

int32_t epilogueOffset;

void initParameter(void) {
  RandomXCodeSize = alignSize(ReserveCodeSize + MaxRandomXInstrCodeSize *
                                                    RANDOMX_PROGRAM_SIZE,
                              CodeAlign);
  SuperscalarSize = alignSize(
      ReserveCodeSize + (SuperscalarProgramHeader +
                         MaxSuperscalarInstrSize * SuperscalarMaxSize) *
                            RANDOMX_CACHE_ACCESSES,
      CodeAlign);
  CodeSize              = RandomXCodeSize + SuperscalarSize;
  superScalarHashOffset = RandomXCodeSize;
  epilogueOffset        = (CodeSize - epilogueSize);
}

static const uint8_t REX_ADD_RR[]             = {0x4d, 0x03};
static const uint8_t REX_ADD_RM[]             = {0x4c, 0x03};
static const uint8_t REX_SUB_RR[]             = {0x4d, 0x2b};
static const uint8_t REX_SUB_RM[]             = {0x4c, 0x2b};
static const uint8_t REX_MOV_RR[]             = {0x41, 0x8b};
static const uint8_t REX_MOV_RR64[]           = {0x49, 0x8b};
static const uint8_t REX_MOV_R64R[]           = {0x4c, 0x8b};
static const uint8_t REX_IMUL_RR[]            = {0x4d, 0x0f, 0xaf};
static const uint8_t REX_IMUL_RRI[]           = {0x4d, 0x69};
static const uint8_t REX_IMUL_RM[]            = {0x4c, 0x0f, 0xaf};
static const uint8_t REX_MUL_R[]              = {0x49, 0xf7};
static const uint8_t REX_MUL_M[]              = {0x48, 0xf7};
static const uint8_t REX_81[]                 = {0x49, 0x81};
static const uint8_t AND_EAX_I                = 0x25;
static const uint8_t MOV_EAX_I                = 0xb8;
static const uint8_t MOV_RAX_I[]              = {0x48, 0xb8};
static const uint8_t MOV_RCX_I[]              = {0x48, 0xb9};
static const uint8_t REX_LEA[]                = {0x4f, 0x8d};
static const uint8_t REX_MUL_MEM[]            = {0x48, 0xf7, 0x24, 0x0e};
static const uint8_t REX_IMUL_MEM[]           = {0x48, 0xf7, 0x2c, 0x0e};
static const uint8_t REX_SHR_RAX[]            = {0x48, 0xc1, 0xe8};
static const uint8_t RAX_ADD_SBB_1[]          = {0x48, 0x83, 0xC0, 0x01,
                                        0x48, 0x83, 0xD8, 0x00};
static const uint8_t MUL_RCX[]                = {0x48, 0xf7, 0xe1};
static const uint8_t REX_SHR_RDX[]            = {0x48, 0xc1, 0xea};
static const uint8_t REX_SH[]                 = {0x49, 0xc1};
static const uint8_t MOV_RCX_RAX_SAR_RCX_63[] = {0x48, 0x89, 0xc1, 0x48,
                                                 0xc1, 0xf9, 0x3f};
static const uint8_t AND_ECX_I[]              = {0x81, 0xe1};
static const uint8_t ADD_RAX_RCX[]            = {0x48, 0x01, 0xC8};
static const uint8_t SAR_RAX_I8[]             = {0x48, 0xC1, 0xF8};
static const uint8_t NEG_RAX[]                = {0x48, 0xF7, 0xD8};
static const uint8_t ADD_R_RAX[]              = {0x4C, 0x03};
static const uint8_t XOR_EAX_EAX[]            = {0x33, 0xC0};
static const uint8_t ADD_RDX_R[]              = {0x4c, 0x01};
static const uint8_t SUB_RDX_R[]              = {0x4c, 0x29};
static const uint8_t SAR_RDX_I8[]             = {0x48, 0xC1, 0xFA};
static const uint8_t TEST_RDX_RDX[]           = {0x48, 0x85, 0xD2};
static const uint8_t SETS_AL_ADD_RDX_RAX[]    = {0x0F, 0x98, 0xC0,
                                              0x48, 0x03, 0xD0};
static const uint8_t REX_NEG[]                = {0x49, 0xF7};
static const uint8_t REX_XOR_RR[]             = {0x4D, 0x33};
static const uint8_t REX_XOR_RI[]             = {0x49, 0x81};
static const uint8_t REX_XOR_RM[]             = {0x4c, 0x33};
static const uint8_t REX_ROT_CL[]             = {0x49, 0xd3};
static const uint8_t REX_ROT_I8[]             = {0x49, 0xc1};
static const uint8_t SHUFPD[]                 = {0x66, 0x0f, 0xc6};
static const uint8_t REX_ADDPD[]              = {0x66, 0x41, 0x0f, 0x58};
static const uint8_t REX_CVTDQ2PD_XMM12[]     = {0xf3, 0x44, 0x0f,
                                             0xe6, 0x24, 0x06};
static const uint8_t REX_SUBPD[]              = {0x66, 0x41, 0x0f, 0x5c};
static const uint8_t REX_XORPS[]              = {0x41, 0x0f, 0x57};
static const uint8_t REX_MULPD[]              = {0x66, 0x41, 0x0f, 0x59};
static const uint8_t REX_MAXPD[]              = {0x66, 0x41, 0x0f, 0x5f};
static const uint8_t REX_DIVPD[]              = {0x66, 0x41, 0x0f, 0x5e};
static const uint8_t SQRTPD[]                 = {0x66, 0x0f, 0x51};
static const uint8_t AND_OR_MOV_LDMXCSR[] = {0x25, 0x00, 0x60, 0x00, 0x00, 0x0D,
                                             0xC0, 0x9F, 0x00, 0x00, 0x50, 0x0F,
                                             0xAE, 0x14, 0x24, 0x58};
static const uint8_t ROL_RAX[]            = {0x48, 0xc1, 0xc0};
static const uint8_t XOR_ECX_ECX[]        = {0x33, 0xC9};
static const uint8_t REX_CMP_R32I[]       = {0x41, 0x81};
static const uint8_t REX_CMP_M32I[]       = {0x81, 0x3c, 0x06};
static const uint8_t MOVAPD[]             = {0x66, 0x0f, 0x29};
static const uint8_t REX_MOV_MR[]         = {0x4c, 0x89};
static const uint8_t REX_XOR_EAX[]        = {0x41, 0x33};
static const uint8_t SUB_EBX[]            = {0x83, 0xEB, 0x01};
static const uint8_t JNZ[]                = {0x0f, 0x85};
static const uint8_t JMP                  = 0xe9;
static const uint8_t REX_XOR_RAX_R64[]    = {0x49, 0x33};
static const uint8_t REX_XCHG[]           = {0x4d, 0x87};
static const uint8_t REX_ANDPS_XMM12[]    = {0x45, 0x0F, 0x54, 0xE5,
                                          0x45, 0x0F, 0x56, 0xE6};
static const uint8_t REX_PADD[]           = {0x66, 0x44, 0x0f};
static const uint8_t PADD_OPCODES[]       = {0xfc, 0xfd, 0xfe, 0xd4};
static const uint8_t CALL                 = 0xe8;
static const uint8_t REX_ADD_I[]          = {0x49, 0x81};
static const uint8_t REX_TEST[]           = {0x49, 0xF7};
static const uint8_t JZ[]                 = {0x0f, 0x84};
static const uint8_t RET                  = 0xc3;
static const uint8_t LEA_32[]             = {0x41, 0x8d};
static const uint8_t MOVNTI[]             = {0x4c, 0x0f, 0xc3};
static const uint8_t ADD_EBX_I[]          = {0x81, 0xc3};

static const uint8_t NOP1[] = {0x90};
static const uint8_t NOP2[] = {0x66, 0x90};
static const uint8_t NOP3[] = {0x66, 0x66, 0x90};
static const uint8_t NOP4[] = {0x0F, 0x1F, 0x40, 0x00};
static const uint8_t NOP5[] = {0x0F, 0x1F, 0x44, 0x00, 0x00};
static const uint8_t NOP6[] = {0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00};
static const uint8_t NOP7[] = {0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00};
static const uint8_t NOP8[] = {0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00};
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

static const uint8_t *NOPX[] = {NOP1, NOP2, NOP3, NOP4, NOP5, NOP6, NOP7, NOP8};

static size_t getCodeSize(void *jrx) { return CodeSize; }

void *initJrxX86(int id) {
  initParameter();
  jrx_x86_t *dev = (jrx_x86_t *)allocMemoryPages(sizeof(jrx_x86_t));
  if (!dev) {
    printf("Jrx malloc Error\n");
    exit(1);
  }

  dev->code = (uint8_t *)allocMemoryPages(CodeSize);
  memcpy(dev->code, codePrologue, prologueSize);
  memcpy(dev->code + epilogueOffset, codeEpilogue, epilogueSize);

  dev->instructionOffsets = cvector_create(sizeof(int32_t));
  printf("X86 device\n");
  return dev;
}

void exitJrxX86(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;

  cvector_destroy(dev->instructionOffsets);
  freePagedMemory(dev->code, CodeSize);
  freePagedMemory(dev, sizeof(jrx_x86_t));
}

static void enableAll(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  setPagesRWX(dev->code, CodeSize);
}

static void enableWriting(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  setPagesRW(dev->code, CodeSize);
}

static void enableExecution(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  setPagesRX(dev->code, CodeSize);
}

static void generateProgram(void *jrx, Program_t *prog,
                            ProgramConfiguration_t *pcfg) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;

  memcpy(dev->code, codePrologue, prologueSize);
  memcpy(dev->code + epilogueOffset, codeEpilogue, epilogueSize);

  generateProgramPrologue(jrx, prog, pcfg);
  memcpy(dev->code + dev->codePos, codeReadDataset, readDatasetSize);
  dev->codePos += readDatasetSize;
  generateProgramEpilogue(jrx, prog, pcfg);
}

static void generateProgramLight(void *jrx, Program_t *prog,
                                 ProgramConfiguration_t *pcfg,
                                 uint32_t datasetOffset) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  generateProgramPrologue(jrx, prog, pcfg);
  emit(jrx, codeReadDatasetLightSshInit, readDatasetLightInitSize);
  emit(jrx, ADD_EBX_I, ARRAY_SIZE(ADD_EBX_I));
  emit32(jrx, datasetOffset / CacheLineSize);
  emitByte(jrx, CALL);
  emit32(jrx, superScalarHashOffset - (dev->codePos + 4));
  emit(jrx, codeReadDatasetLightSshFin, readDatasetLightFinSize);
  generateProgramEpilogue(jrx, prog, pcfg);
}

static void generateSuperscalarHash(void *jrx, SuperscalarProgram_t *programs,
                                    cvector reciprocalCache) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  memcpy(dev->code + superScalarHashOffset, codeShhInit, codeSshInitSize);
  dev->codePos = superScalarHashOffset + codeSshInitSize;

  for (unsigned j = 0; j < RANDOMX_CACHE_ACCESSES; ++j) {
    SuperscalarProgram_t *prog = &programs[j];
    for (unsigned i = 0; i < SSP_getSize(prog); ++i) {
      Instruction_t *instr = SSP_getInstruction(prog, i);
      generateSuperscalarCode(jrx, instr, reciprocalCache);
    }
    emit(jrx, codeShhLoad, codeSshLoadSize);
    if (j < RANDOMX_CACHE_ACCESSES - 1) {
      emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
      emitByte(jrx, 0xd8 + SSP_getAddressRegister(prog));
      emit(jrx, codeShhPrefetch, codeSshPrefetchSize);
#ifdef RANDOMX_ALIGN
      int align = (dev->codePos % 16);
      while (align != 0) {
        int nopSize = 16 - align;
        if (nopSize > 8)
          nopSize = 8;
        emit(jrx, NOPX[nopSize - 1], nopSize);
        align = (dev->codePos % 16);
      }
#endif
    }
  }
  emitByte(jrx, RET);
}

static void generateDatasetInitCode(void *jrx) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  memcpy(dev->code, codeDatasetInit, datasetInitSize);
}

void generateProgramPrologue(void *jrx, Program_t *prog,
                             ProgramConfiguration_t *pcfg) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  cvector_clear(dev->instructionOffsets);
  for (unsigned i = 0; i < RegistersCount; ++i) {
    dev->registerUsage[i] = -1;
  }

  dev->codePos = prologueSize;
  memcpy(dev->code + dev->codePos - 48, pcfg->eMask, sizeof(pcfg->eMask));
  memcpy(dev->code + dev->codePos, codeLoopLoad, loopLoadSize);
  dev->codePos += loopLoadSize;
  for (unsigned i = 0; i < getProgramSize(); ++i) {
    Instruction_t *instr = getPGInstruction(prog, i);
    instr->src %= RegistersCount;
    instr->dst %= RegistersCount;
    generateCode(jrx, instr, i);
  }
  emit(jrx, REX_MOV_RR, ARRAY_SIZE(REX_MOV_RR));
  emitByte(jrx, 0xc0 + pcfg->readReg2);
  emit(jrx, REX_XOR_EAX, ARRAY_SIZE(REX_XOR_EAX));
  emitByte(jrx, 0xc0 + pcfg->readReg3);
}

void generateProgramEpilogue(void *jrx, Program_t *prog,
                             ProgramConfiguration_t *pcfg) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
  emitByte(jrx, 0xc0 + pcfg->readReg0);
  emit(jrx, REX_XOR_RAX_R64, ARRAY_SIZE(REX_XOR_RAX_R64));
  emitByte(jrx, 0xc0 + pcfg->readReg1);
  emit(jrx, (const uint8_t *)&randomx_prefetch_scratchpad,
       ((uint8_t *)&randomx_prefetch_scratchpad_end) -
           ((uint8_t *)&randomx_prefetch_scratchpad));
  memcpy(dev->code + dev->codePos, codeLoopStore, loopStoreSize);
  dev->codePos += loopStoreSize;
  emit(jrx, SUB_EBX, ARRAY_SIZE(SUB_EBX));
  emit(jrx, JNZ, ARRAY_SIZE(JNZ));
  emit32(jrx, prologueSize - dev->codePos - 4);
  emitByte(jrx, JMP);
  emit32(jrx, epilogueOffset - dev->codePos - 4);
}

void generateCode(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  cvector_pushback(dev->instructionOffsets, &dev->codePos);
  InstructionGeneratorX86 generator = X86Engine[instr->opcode];
  generator(jrx, instr, i);
}

void generateSuperscalarCode(void *jrx, Instruction_t *instr,
                             cvector reciprocalCache) {
  switch ((enum SuperscalarInstructionType)instr->opcode) {
  case SS_ISUB_R:
    emit(jrx, REX_SUB_RR, ARRAY_SIZE(REX_SUB_RR));
    emitByte(jrx, 0xc0 + 8 * instr->dst + instr->src);
    break;
  case SS_IXOR_R:
    emit(jrx, REX_XOR_RR, ARRAY_SIZE(REX_XOR_RR));
    emitByte(jrx, 0xc0 + 8 * instr->dst + instr->src);
    break;
  case SS_IADD_RS:
    emit(jrx, REX_LEA, ARRAY_SIZE(REX_LEA));
    emitByte(jrx, 0x04 + 8 * instr->dst);
    genSIB(jrx, Instruction_getModShift(instr), instr->src, instr->dst);
    break;
  case SS_IMUL_R:
    emit(jrx, REX_IMUL_RR, ARRAY_SIZE(REX_IMUL_RR));
    emitByte(jrx, 0xc0 + 8 * instr->dst + instr->src);
    break;
  case SS_IROR_C:
    emit(jrx, REX_ROT_I8, ARRAY_SIZE(REX_ROT_I8));
    emitByte(jrx, 0xc8 + instr->dst);
    emitByte(jrx, Instruction_getImm32(instr) & 63);
    break;
  case SS_IADD_C7:
    emit(jrx, REX_81, ARRAY_SIZE(REX_81));
    emitByte(jrx, 0xc0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
    break;
  case SS_IXOR_C7:
    emit(jrx, REX_XOR_RI, ARRAY_SIZE(REX_XOR_RI));
    emitByte(jrx, 0xf0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
    break;
  case SS_IADD_C8:
    emit(jrx, REX_81, ARRAY_SIZE(REX_81));
    emitByte(jrx, 0xc0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
#ifdef RANDOMX_ALIGN
    emit(jrx, NOP1, ARRAY_SIZE(NOP1));
#endif
    break;
  case SS_IXOR_C8:
    emit(jrx, REX_XOR_RI, ARRAY_SIZE(REX_XOR_RI));
    emitByte(jrx, 0xf0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
#ifdef RANDOMX_ALIGN
    emit(jrx, NOP1, ARRAY_SIZE(NOP1));
#endif
    break;
  case SS_IADD_C9:
    emit(jrx, REX_81, ARRAY_SIZE(REX_81));
    emitByte(jrx, 0xc0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
#ifdef RANDOMX_ALIGN
    emit(jrx, NOP2, ARRAY_SIZE(NOP2));
#endif
    break;
  case SS_IXOR_C9:
    emit(jrx, REX_XOR_RI, ARRAY_SIZE(REX_XOR_RI));
    emitByte(jrx, 0xf0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
#ifdef RANDOMX_ALIGN
    emit(jrx, NOP2, ARRAY_SIZE(NOP2));
#endif
    break;
  case SS_IMULH_R:
    emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
    emitByte(jrx, 0xc0 + instr->dst);
    emit(jrx, REX_MUL_R, ARRAY_SIZE(REX_MUL_R));
    emitByte(jrx, 0xe0 + instr->src);
    emit(jrx, REX_MOV_R64R, ARRAY_SIZE(REX_MOV_R64R));
    emitByte(jrx, 0xc2 + 8 * instr->dst);
    break;
  case SS_ISMULH_R:
    emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
    emitByte(jrx, 0xc0 + instr->dst);
    emit(jrx, REX_MUL_R, ARRAY_SIZE(REX_MUL_R));
    emitByte(jrx, 0xe8 + instr->src);
    emit(jrx, REX_MOV_R64R, ARRAY_SIZE(REX_MOV_R64R));
    emitByte(jrx, 0xc2 + 8 * instr->dst);
    break;
  case SS_IMUL_RCP:
    emit(jrx, MOV_RAX_I, ARRAY_SIZE(MOV_RAX_I));
    emit64(jrx, *(uint64_t *)cvector_get_val(reciprocalCache,
                                             Instruction_getImm32(instr)));
    emit(jrx, REX_IMUL_RM, ARRAY_SIZE(REX_IMUL_RM));
    emitByte(jrx, 0xc0 + 8 * instr->dst);
    break;
  default:
    UNREACHABLE;
  }
}

void genAddressReg(void *jrx, Instruction_t *instr, bool rax) {
  emit(jrx, LEA_32, ARRAY_SIZE(LEA_32));
  emitByte(jrx, 0x80 + instr->src + (rax ? 0 : 8));
  if (instr->src == RegisterNeedsSib) {
    emitByte(jrx, 0x24);
  }
  emit32(jrx, Instruction_getImm32(instr));
  if (rax)
    emitByte(jrx, AND_EAX_I);
  else
    emit(jrx, AND_ECX_I, ARRAY_SIZE(AND_ECX_I));
  emit32(jrx,
         Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
}

void genAddressRegDst(void *jrx, Instruction_t *instr) {
  emit(jrx, LEA_32, ARRAY_SIZE(LEA_32));
  emitByte(jrx, 0x80 + instr->dst);
  if (instr->dst == RegisterNeedsSib) {
    emitByte(jrx, 0x24);
  }
  emit32(jrx, Instruction_getImm32(instr));
  emitByte(jrx, AND_EAX_I);
  if (Instruction_getModCond(instr) < StoreL3Condition) {
    emit32(jrx,
           Instruction_getModMem(instr) ? ScratchpadL1Mask : ScratchpadL2Mask);
  } else {
    emit32(jrx, ScratchpadL3Mask);
  }
}

void genAddressImm(void *jrx, Instruction_t *instr) {
  emit32(jrx, Instruction_getImm32(instr) & ScratchpadL3Mask);
}

void h_IADD_RS(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  emit(jrx, REX_LEA, ARRAY_SIZE(REX_LEA));
  if (instr->dst == RegisterNeedsDisplacement)
    emitByte(jrx, 0xac);
  else
    emitByte(jrx, 0x04 + 8 * instr->dst);
  genSIB(jrx, Instruction_getModShift(instr), instr->src, instr->dst);
  if (instr->dst == RegisterNeedsDisplacement)
    emit32(jrx, Instruction_getImm32(instr));
}

void h_IADD_M(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    genAddressReg(jrx, instr, true);
    emit(jrx, REX_ADD_RM, ARRAY_SIZE(REX_ADD_RM));
    emitByte(jrx, 0x04 + 8 * instr->dst);
    emitByte(jrx, 0x06);
  } else {
    emit(jrx, REX_ADD_RM, ARRAY_SIZE(REX_ADD_RM));
    emitByte(jrx, 0x86 + 8 * instr->dst);
    genAddressImm(jrx, instr);
  }
}

void genSIB(void *jrx, int scale, int index, int base) {
  emitByte(jrx, (scale << 6) | (index << 3) | base);
}

void h_ISUB_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    emit(jrx, REX_SUB_RR, ARRAY_SIZE(REX_SUB_RR));
    emitByte(jrx, 0xc0 + 8 * instr->dst + instr->src);
  } else {
    emit(jrx, REX_81, ARRAY_SIZE(REX_81));
    emitByte(jrx, 0xe8 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
  }
}

void h_ISUB_M(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    genAddressReg(jrx, instr, true);
    emit(jrx, REX_SUB_RM, ARRAY_SIZE(REX_SUB_RM));
    emitByte(jrx, 0x04 + 8 * instr->dst);
    emitByte(jrx, 0x06);
  } else {
    emit(jrx, REX_SUB_RM, ARRAY_SIZE(REX_SUB_RM));
    emitByte(jrx, 0x86 + 8 * instr->dst);
    genAddressImm(jrx, instr);
  }
}

void h_IMUL_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    emit(jrx, REX_IMUL_RR, ARRAY_SIZE(REX_IMUL_RR));
    emitByte(jrx, 0xc0 + 8 * instr->dst + instr->src);
  } else {
    emit(jrx, REX_IMUL_RRI, ARRAY_SIZE(REX_IMUL_RRI));
    emitByte(jrx, 0xc0 + 9 * instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
  }
}

void h_IMUL_M(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    genAddressReg(jrx, instr, true);
    emit(jrx, REX_IMUL_RM, ARRAY_SIZE(REX_IMUL_RM));
    emitByte(jrx, 0x04 + 8 * instr->dst);
    emitByte(jrx, 0x06);
  } else {
    emit(jrx, REX_IMUL_RM, ARRAY_SIZE(REX_IMUL_RM));
    emitByte(jrx, 0x86 + 8 * instr->dst);
    genAddressImm(jrx, instr);
  }
}

void h_IMULH_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
  emitByte(jrx, 0xc0 + instr->dst);
  emit(jrx, REX_MUL_R, ARRAY_SIZE(REX_MUL_R));
  emitByte(jrx, 0xe0 + instr->src);
  emit(jrx, REX_MOV_R64R, ARRAY_SIZE(REX_MOV_R64R));
  emitByte(jrx, 0xc2 + 8 * instr->dst);
}

void h_IMULH_M(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    genAddressReg(jrx, instr, false);
    emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
    emitByte(jrx, 0xc0 + instr->dst);
    emit(jrx, REX_MUL_MEM, ARRAY_SIZE(REX_MUL_MEM));
  } else {
    emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
    emitByte(jrx, 0xc0 + instr->dst);
    emit(jrx, REX_MUL_M, ARRAY_SIZE(REX_MUL_M));
    emitByte(jrx, 0xa6);
    genAddressImm(jrx, instr);
  }
  emit(jrx, REX_MOV_R64R, ARRAY_SIZE(REX_MOV_R64R));
  emitByte(jrx, 0xc2 + 8 * instr->dst);
}

void h_ISMULH_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
  emitByte(jrx, 0xc0 + instr->dst);
  emit(jrx, REX_MUL_R, ARRAY_SIZE(REX_MUL_R));
  emitByte(jrx, 0xe8 + instr->src);
  emit(jrx, REX_MOV_R64R, ARRAY_SIZE(REX_MOV_R64R));
  emitByte(jrx, 0xc2 + 8 * instr->dst);
}

void h_ISMULH_M(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    genAddressReg(jrx, instr, false);
    emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
    emitByte(jrx, 0xc0 + instr->dst);
    emit(jrx, REX_IMUL_MEM, ARRAY_SIZE(REX_IMUL_MEM));
  } else {
    emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
    emitByte(jrx, 0xc0 + instr->dst);
    emit(jrx, REX_MUL_M, ARRAY_SIZE(REX_MUL_M));
    emitByte(jrx, 0xae);
    genAddressImm(jrx, instr);
  }
  emit(jrx, REX_MOV_R64R, ARRAY_SIZE(REX_MOV_R64R));
  emitByte(jrx, 0xc2 + 8 * instr->dst);
}

void h_IMUL_RCP(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev   = (jrx_x86_t *)jrx;
  uint64_t divisor = Instruction_getImm32(instr);
  if (!isZeroOrPowerOf2(divisor)) {
    dev->registerUsage[instr->dst] = i;
    emit(jrx, MOV_RAX_I, ARRAY_SIZE(MOV_RAX_I));
    emit64(jrx, randomx_reciprocal_fast(divisor));
    emit(jrx, REX_IMUL_RM, ARRAY_SIZE(REX_IMUL_RM));
    emitByte(jrx, 0xc0 + 8 * instr->dst);
  }
}

void h_INEG_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  emit(jrx, REX_NEG, ARRAY_SIZE(REX_NEG));
  emitByte(jrx, 0xd8 + instr->dst);
}

void h_IXOR_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    emit(jrx, REX_XOR_RR, ARRAY_SIZE(REX_XOR_RR));
    emitByte(jrx, 0xc0 + 8 * instr->dst + instr->src);
  } else {
    emit(jrx, REX_XOR_RI, ARRAY_SIZE(REX_XOR_RI));
    emitByte(jrx, 0xf0 + instr->dst);
    emit32(jrx, Instruction_getImm32(instr));
  }
}

void h_IXOR_M(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    genAddressReg(jrx, instr, true);
    emit(jrx, REX_XOR_RM, ARRAY_SIZE(REX_XOR_RM));
    emitByte(jrx, 0x04 + 8 * instr->dst);
    emitByte(jrx, 0x06);
  } else {
    emit(jrx, REX_XOR_RM, ARRAY_SIZE(REX_XOR_RM));
    emitByte(jrx, 0x86 + 8 * instr->dst);
    genAddressImm(jrx, instr);
  }
}

void h_IROR_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    emit(jrx, REX_MOV_RR, ARRAY_SIZE(REX_MOV_RR));
    emitByte(jrx, 0xc8 + instr->src);
    emit(jrx, REX_ROT_CL, ARRAY_SIZE(REX_ROT_CL));
    emitByte(jrx, 0xc8 + instr->dst);
  } else {
    emit(jrx, REX_ROT_I8, ARRAY_SIZE(REX_ROT_I8));
    emitByte(jrx, 0xc8 + instr->dst);
    emitByte(jrx, Instruction_getImm32(instr) & 63);
  }
}

void h_IROL_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev                 = (jrx_x86_t *)jrx;
  dev->registerUsage[instr->dst] = i;
  if (instr->src != instr->dst) {
    emit(jrx, REX_MOV_RR, ARRAY_SIZE(REX_MOV_RR));
    emitByte(jrx, 0xc8 + instr->src);
    emit(jrx, REX_ROT_CL, ARRAY_SIZE(REX_ROT_CL));
    emitByte(jrx, 0xc0 + instr->dst);
  } else {
    emit(jrx, REX_ROT_I8, ARRAY_SIZE(REX_ROT_I8));
    emitByte(jrx, 0xc0 + instr->dst);
    emitByte(jrx, Instruction_getImm32(instr) & 63);
  }
}

void h_ISWAP_R(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  if (instr->src != instr->dst) {
    dev->registerUsage[instr->dst] = i;
    dev->registerUsage[instr->src] = i;
    emit(jrx, REX_XCHG, ARRAY_SIZE(REX_XCHG));
    emitByte(jrx, 0xc0 + instr->src + 8 * instr->dst);
  }
}

void h_FSWAP_R(void *jrx, Instruction_t *instr, int i) {
  emit(jrx, SHUFPD, ARRAY_SIZE(SHUFPD));
  emitByte(jrx, 0xc0 + 9 * instr->dst);
  emitByte(jrx, 1);
}

void h_FADD_R(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  instr->src %= RegisterCountFlt;
  emit(jrx, REX_ADDPD, ARRAY_SIZE(REX_ADDPD));
  emitByte(jrx, 0xc0 + instr->src + 8 * instr->dst);
}

void h_FADD_M(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  genAddressReg(jrx, instr, true);
  emit(jrx, REX_CVTDQ2PD_XMM12, ARRAY_SIZE(REX_CVTDQ2PD_XMM12));
  emit(jrx, REX_ADDPD, ARRAY_SIZE(REX_ADDPD));
  emitByte(jrx, 0xc4 + 8 * instr->dst);
}

void h_FSUB_R(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  instr->src %= RegisterCountFlt;
  emit(jrx, REX_SUBPD, ARRAY_SIZE(REX_SUBPD));
  emitByte(jrx, 0xc0 + instr->src + 8 * instr->dst);
}

void h_FSUB_M(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  genAddressReg(jrx, instr, true);
  emit(jrx, REX_CVTDQ2PD_XMM12, ARRAY_SIZE(REX_CVTDQ2PD_XMM12));
  emit(jrx, REX_SUBPD, ARRAY_SIZE(REX_SUBPD));
  emitByte(jrx, 0xc4 + 8 * instr->dst);
}

void h_FSCAL_R(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  emit(jrx, REX_XORPS, ARRAY_SIZE(REX_XORPS));
  emitByte(jrx, 0xc7 + 8 * instr->dst);
}

void h_FMUL_R(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  instr->src %= RegisterCountFlt;
  emit(jrx, REX_MULPD, ARRAY_SIZE(REX_MULPD));
  emitByte(jrx, 0xe0 + instr->src + 8 * instr->dst);
}

void h_FDIV_M(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  genAddressReg(jrx, instr, true);
  emit(jrx, REX_CVTDQ2PD_XMM12, ARRAY_SIZE(REX_CVTDQ2PD_XMM12));
  emit(jrx, REX_ANDPS_XMM12, ARRAY_SIZE(REX_ANDPS_XMM12));
  emit(jrx, REX_DIVPD, ARRAY_SIZE(REX_DIVPD));
  emitByte(jrx, 0xe4 + 8 * instr->dst);
}

void h_FSQRT_R(void *jrx, Instruction_t *instr, int i) {
  instr->dst %= RegisterCountFlt;
  emit(jrx, SQRTPD, ARRAY_SIZE(SQRTPD));
  emitByte(jrx, 0xe4 + 9 * instr->dst);
}

void h_CFROUND(void *jrx, Instruction_t *instr, int i) {
  emit(jrx, REX_MOV_RR64, ARRAY_SIZE(REX_MOV_RR64));
  emitByte(jrx, 0xc0 + instr->src);
  int rotate = (13 - (Instruction_getImm32(instr) & 63)) & 63;
  if (rotate != 0) {
    emit(jrx, ROL_RAX, ARRAY_SIZE(ROL_RAX));
    emitByte(jrx, rotate);
  }
  emit(jrx, AND_OR_MOV_LDMXCSR, ARRAY_SIZE(AND_OR_MOV_LDMXCSR));
}

void h_CBRANCH(void *jrx, Instruction_t *instr, int i) {
  jrx_x86_t *dev = (jrx_x86_t *)jrx;
  int reg        = instr->dst;
  int target     = dev->registerUsage[reg] + 1;
  emit(jrx, REX_ADD_I, ARRAY_SIZE(REX_ADD_I));
  emitByte(jrx, 0xc0 + reg);
  int shift    = Instruction_getModCond(instr) + ConditionOffset;
  uint32_t imm = Instruction_getImm32(instr) | (1UL << shift);
  if (ConditionOffset > 0 || shift > 0)
    imm &= ~(1UL << (shift - 1));
  emit32(jrx, imm);
  emit(jrx, REX_TEST, ARRAY_SIZE(REX_TEST));
  emitByte(jrx, 0xc0 + reg);
  emit32(jrx, ConditionMask << shift);
  emit(jrx, JZ, ARRAY_SIZE(JZ));
  emit32(jrx, *(int32_t *)cvector_get_val(dev->instructionOffsets, target) -
                  (dev->codePos + 4));
  // mark all registers as used
  for (unsigned j = 0; j < RegistersCount; ++j) {
    dev->registerUsage[j] = i;
  }
}

void h_ISTORE(void *jrx, Instruction_t *instr, int i) {
  genAddressRegDst(jrx, instr);
  emit(jrx, REX_MOV_MR, ARRAY_SIZE(REX_MOV_MR));
  emitByte(jrx, 0x04 + 8 * instr->src);
  emitByte(jrx, 0x06);
}

void h_NOP(void *jrx, Instruction_t *instr, int i) {
  emit(jrx, NOP1, ARRAY_SIZE(NOP1));
}

#include "instruction_weights.h"
#define INST_HANDLE(x) REPN(h_##x, WT(x))

InstructionGeneratorX86 X86Engine[256] = {
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

jrx_t x86Dev = {
    .name                    = "x86Dev",
    .init_jrx                = initJrxX86,
    .exit_jrx                = exitJrxX86,
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
JRX_REGISTER(x86Dev)
