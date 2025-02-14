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

#ifndef __VM_INTERPRETED_H__
#define __VM_INTERPRETED_H__

#include "allocator.h"
#include "bytecode_machine.h"
#include "rxa_common.h"
#include "intrin_portable.h"
#include "virtual_machine.h"

typedef struct InterpretedVm_ops {
  void (*datasetRead)(void *vm, uint64_t address, int_reg_t *r);
  void (*datasetPrefetch)(void *vm, uint64_t address);
} InterpretedVm_ops_t;

typedef struct InterpretedVm {
  VmBase_t vmbase;
  InstructionByteCode_t bytecode[RANDOMX_PROGRAM_SIZE];
  bytecode_machine_t *bm;
  InterpretedVm_ops_t ops;
  bool softAes;
  int allocatorMode;
  int alignment;
} InterpretedVm_t;

InterpretedVm_t *initInterpretedVm(bool softAes, int allocatorMode,
                                   int alignment);
void exitInterpretedVm(void *vm);
void vm_interpreted_run(void *vm, void *seed);
void vm_interpreted_setDataset(void *vm, randomx_dataset *dataset);

#endif
