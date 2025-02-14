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

#ifndef __DATASET_H__
#define __DATASET_H__

#include "allocator.h"
#include "argon2/argon2.h"
#include "rxa_common.h"
#include "cvector.h"
#include "jrx_core.h"
#include "superscalar_program.h"
#include <stdint.h>

/* Global scope for C binding */
typedef struct randomx_dataset {
  uint8_t *memory;
  int allocatorMode;
  int alignment;
  jrx_machine_t *mc;
} randomx_dataset_t;

/* Global scope for C binding */
typedef struct randomx_cache {
  uint8_t *memory;
  int allocatorMode;
  int alignment;
  jrx_machine_t *mc;
  CacheInitializeFunc *initialize;
  DatasetInitFunc *datasetInit;
  SuperscalarProgram_t programs[RANDOMX_CACHE_ACCESSES];
  cvector reciprocalCache;
  char cacheKey[128];
  randomx_argon2_impl *argonImpl;
} randomx_cache_t;

int randomx_cache_isInitialized(randomx_cache_t *cache);

// the following assert fails when compiling Debug in Visual Studio (JIT mode
// will crash in Debug)
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) && defined(_DEBUG)
#define TO_STR(x) #x
#define STR(x)    TO_STR(x)
#pragma message(__FILE__ "(" STR(                                              \
    __LINE__) ") warning: check std::is_standard_layout<randomx_cache>() is disabled for Debug configuration. JIT mode will crash.")
#undef STR
#undef TO_STR
#else
#endif

void deallocDataset(int mode, size_t alignment,
                           randomx_dataset *dataset);
void deallocCache(int mode, size_t alignment, randomx_cache *cache);

void initCache(randomx_cache_t *, const void *, size_t);
void initCacheCompile(randomx_cache_t *, const void *, size_t);
void initDatasetItem(randomx_cache_t *cache, uint8_t *out,
                     uint64_t blockNumber);
void initDataset(randomx_cache_t *cache, uint8_t *dataset, uint32_t startBlock,
                 uint32_t endBlock);

static inline randomx_argon2_impl *selectArgonImpl(randomx_flags flags) {
  if (flags & RANDOMX_FLAG_ARGON2_AVX2) {
    return randomx_argon2_impl_avx2();
  }
  if (flags & RANDOMX_FLAG_ARGON2_SSSE3) {
    return randomx_argon2_impl_ssse3();
  }
  return &randomx_argon2_fill_segment_ref;
}
#endif
