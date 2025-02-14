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

/* Original code from Argon2 reference source code package used under CC0
 * Licence https://github.com/P-H-C/phc-winner-argon2 Copyright 2015 Daniel
 * Dinu, Dmitry Khovratovich, Jean-Philippe Aumasson, and Samuel Neves
 */
#include <linux/types.h>
#include <assert.h>
#include <string.h>

#include "argon2/argon2.h"
#include "argon2/argon2_core.h"
#include "blake2/endian.h"
#include "blake2_generator.h"
#include "rxa_common.h"
#include "cvector.h"
#include "dataset.h"
#include "intrin_portable.h"
#include "jrx_core.h"
#include "reciprocal.h"
#include "superscalar.h"
#include "virtual_memory.h"

int randomx_cache_isInitialized(randomx_cache_t *cache) {
  return SSP_getSize(&cache->programs[0]) != 0;
}

void deallocDataset(int mode, size_t alignment,
                           randomx_dataset *dataset) {
  if (dataset->memory != NULL)
    freeMemory(mode, dataset->memory, DatasetSize);
}

void deallocCache(int mode, size_t alignment, randomx_cache_t *cache) {
  if (cache->memory != NULL)
    freeMemory(mode, cache->memory, CacheSize);
}

extern bool fastCache;
void initCache(randomx_cache_t *cache, const void *key, size_t keySize) {
  uint32_t memory_blocks, segment_length;
  argon2_instance_t instance;
  argon2_context context;

  if (fastCache) {
    for (int i = 0; i < (256 << 17); i++)
      *(uint64_t *)(cache->memory + i * 8) = i;
    // memset(cache->memory, 0, 256 << 20);
    return;
  }

  context.out          = NULL;
  context.outlen       = 0;
  context.pwd          = CONST_CAST(uint8_t *) key;
  context.pwdlen       = (uint32_t)keySize;
  context.salt         = CONST_CAST(uint8_t *) RANDOMX_ARGON_SALT;
  context.saltlen      = (uint32_t)ArgonSaltSize;
  context.secret       = NULL;
  context.secretlen    = 0;
  context.ad           = NULL;
  context.adlen        = 0;
  context.t_cost       = RANDOMX_ARGON_ITERATIONS;
  context.m_cost       = RANDOMX_ARGON_MEMORY;
  context.lanes        = RANDOMX_ARGON_LANES;
  context.threads      = 1;
  context.allocate_cbk = NULL;
  context.free_cbk     = NULL;
  context.flags        = ARGON2_DEFAULT_FLAGS;
  context.version      = ARGON2_VERSION_NUMBER;

  int inputsValid = randomx_argon2_validate_inputs(&context);
  assert(inputsValid == ARGON2_OK);

  /* 2. Align memory size */
  /* Minimum memory_blocks = 8L blocks, where L is the number of lanes */
  memory_blocks = context.m_cost;

  segment_length = memory_blocks / (context.lanes * ARGON2_SYNC_POINTS);

  instance.version        = context.version;
  instance.memory         = NULL;
  instance.passes         = context.t_cost;
  instance.memory_blocks  = memory_blocks;
  instance.segment_length = segment_length;
  instance.lane_length    = segment_length * ARGON2_SYNC_POINTS;
  instance.lanes          = context.lanes;
  instance.threads        = context.threads;
  instance.type           = Argon2_d;
  instance.memory         = (block *)cache->memory;
  instance.impl           = cache->argonImpl;

  if (instance.threads > instance.lanes) {
    instance.threads = instance.lanes;
  }

  /* 3. Initialization: Hashing inputs, allocating memory, filling first
   * blocks
   */
  randomx_argon2_initialize(&instance, &context);

  randomx_argon2_fill_memory_blocks(&instance);

  cache->reciprocalCache = cvector_create(sizeof(uint64_t));
  Blake2Generator_t *gen = initBlake2Generator();
  Blake2Generator_seed_init(gen, key, keySize, 0);
  for (int i = 0; i < RANDOMX_CACHE_ACCESSES; ++i) {
    generateSuperscalar(&cache->programs[i], gen);
    for (unsigned j = 0; j < SSP_getSize(&cache->programs[i]); ++j) {
      Instruction_t *instr = SSP_getInstruction(&cache->programs[i], j);
      if (instr->opcode == SS_IMUL_RCP) {
        uint64_t rcp = randomx_reciprocal(Instruction_getImm32(instr));
        Instruction_setImm32(instr, cvector_length(cache->reciprocalCache));
        cvector_pushback(cache->reciprocalCache, &rcp);
      }
    }
  }
  exitBlake2Generator(gen);
}

void initCacheCompile(randomx_cache_t *cache, const void *key, size_t keySize) {
  initCache(cache, key, keySize);
	if (fastCache)
		return;
  cache->mc->jrx->enableWriting(cache->mc->jrxDev);
  cache->mc->jrx->generateSuperscalarHash(cache->mc->jrxDev, cache->programs,
                                          cache->reciprocalCache);
  cache->mc->jrx->generateDatasetInitCode(cache->mc->jrxDev);
  cache->mc->jrx->enableExecution(cache->mc->jrxDev);
}

uint64_t superscalarMul0 = 6364136223846793005ULL;
uint64_t superscalarAdd1 = 9298411001130361340ULL;
uint64_t superscalarAdd2 = 12065312585734608966ULL;
uint64_t superscalarAdd3 = 9306329213124626780ULL;
uint64_t superscalarAdd4 = 5281919268842080866ULL;
uint64_t superscalarAdd5 = 10536153434571861004ULL;
uint64_t superscalarAdd6 = 3398623926847679864ULL;
uint64_t superscalarAdd7 = 9549104520008361294ULL;

static inline uint8_t *getMixBlock(uint64_t registerValue, uint8_t *memory) {
  uint32_t mask = CacheSize / CacheLineSize - 1;
  return memory + (registerValue & mask) * CacheLineSize;
}

void initDatasetItem(randomx_cache_t *cache, uint8_t *out,
                     uint64_t itemNumber) {
  int_reg_t rl[8];
  uint8_t *mixBlock;
  uint64_t registerValue = itemNumber;
  rl[0]                  = (itemNumber + 1) * superscalarMul0;
  rl[1]                  = rl[0] ^ superscalarAdd1;
  rl[2]                  = rl[0] ^ superscalarAdd2;
  rl[3]                  = rl[0] ^ superscalarAdd3;
  rl[4]                  = rl[0] ^ superscalarAdd4;
  rl[5]                  = rl[0] ^ superscalarAdd5;
  rl[6]                  = rl[0] ^ superscalarAdd6;
  rl[7]                  = rl[0] ^ superscalarAdd7;
  for (unsigned i = 0; i < RANDOMX_CACHE_ACCESSES; ++i) {
    mixBlock = getMixBlock(registerValue, cache->memory);
    rx_prefetch_nta(mixBlock);
    SuperscalarProgram_t *prog = &cache->programs[i];

    executeSuperscalar(rl, prog, cache->reciprocalCache);

    for (unsigned q = 0; q < 8; ++q)
      rl[q] ^= load64_native(mixBlock + 8 * q);

    registerValue = rl[SSP_getAddressRegister(prog)];
  }

  memcpy(out, &rl, CacheLineSize);
}

void initDataset(randomx_cache_t *cache, uint8_t *dataset, uint32_t startItem,
                 uint32_t endItem) {
  for (uint32_t itemNumber = startItem; itemNumber < endItem;
       ++itemNumber, dataset += CacheLineSize)
    initDatasetItem(cache, dataset, itemNumber);
}
