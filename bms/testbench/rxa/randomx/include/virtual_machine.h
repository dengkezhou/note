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

#ifndef __VIRTUAL_MACHINE_H__
#define __VIRTUAL_MACHINE_H__

#include "rxa_common.h"
#include "program.h"
#include <intrin_portable.h>
#include <stdalign.h>
#include <stdint.h>


typedef struct VmBase {
  alignas(64) Program_t *program;
  alignas(64) RegisterFile_t reg;
  alignas(16) ProgramConfiguration_t config;
  alignas(16) volatile rx_vec_i128 aesDummy;
  MemoryRegisters_t mem;
  uint8_t *scratchpad;
  union {
    randomx_cache *cachePtr;
    randomx_dataset *datasetPtr;
  };
  uint64_t datasetOffset;
  char cacheKey[128];
  alignas(16) uint64_t tempHash[8];
  bool softAes;
  int allocatorMode;
  int alignment;
	void *mc;
} VmBase_t;

typedef struct randomx_vm_ops {
  void (*allocate)(void *vm);
  void (*getFinalResult)(void *vm, void *out, size_t outSize);
  void (*hashAndFill)(void *vm, void *out, size_t outSize,
                      uint64_t *fill_state);
  void (*setDataset)(void *vm, randomx_dataset *dataset);
  void (*setCache)(void *vm, randomx_cache *cache);
  void (*initScratchpad)(void *vm, void *seed);
  void (*run)(void *vm, void *seed);
} randomx_vm_ops_t;
extern randomx_vm_ops_t vm_ops;

typedef struct randomx_vm {
  void *dev;
  void (*exitDev)(void *);
  randomx_vm_ops_t *ops;
	void *mc;
} randomx_vm_t;

RegisterFile_t *getRegisterFile(VmBase_t *dev);
const void *getScratchpad(VmBase_t *dev);
const Program_t *getProgram(VmBase_t *dev);
const uint8_t *getMemory(VmBase_t *dev);

void resetRoundingMode(void);
void vm_initialize(VmBase_t *dev);
void vm_allocate(void *vm);
void vm_initScratchpad(void *vm, void *seed);
void vm_getFinalResult(void *vm, void *out, size_t outSize);
void vm_hashAndFill(void *vm, void *out, size_t outSize, uint64_t *fill_state);
void vm_generateProgram(VmBase_t *dev, void *seed);
void vm_setDataset(void *vm, randomx_dataset *dataset);

void vm_setCache(void *vm, randomx_cache *cache);
int initVmBase(VmBase_t *dev, bool softAes, int allocatorMode, int alignment, void *mc);
void exitVmBase(VmBase_t *dev);
#endif
