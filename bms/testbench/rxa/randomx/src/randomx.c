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

#include "randomx.h"
#include "argon2/argon2.h"
#include "blake2/blake2.h"
#include "dataset.h"
#include "intrin_portable.h"
#include "vm_compiled.h"
#include "vm_compiled_light.h"
#include "vm_interpreted.h"
#include "vm_interpreted_light.h"
#include <rxa_common.h>
#include <cpu.h>
#include <fenv.h>
#include <jrx_rxa.h>
#include <limits.h>
#include <virtual_machine.h>

randomx_flags randomx_get_flags() {
  randomx_flags flags =
      RANDOMX_HAVE_COMPILER ? RANDOMX_FLAG_JIT : RANDOMX_FLAG_DEFAULT;

  get_cpuinfo();
#ifdef RANDOMX_FORCE_SECURE
  if (flags == RANDOMX_FLAG_JIT) {
    flags |= RANDOMX_FLAG_SECURE;
  }
#endif
  if (HAVE_AES && hasAes()) {
    flags |= RANDOMX_FLAG_HARD_AES;
  }
  if (randomx_argon2_impl_avx2() != NULL && hasAvx2()) {
    flags |= RANDOMX_FLAG_ARGON2_AVX2;
  }
  if (randomx_argon2_impl_ssse3() != NULL && hasSsse3()) {
    flags |= RANDOMX_FLAG_ARGON2_SSSE3;
  }
  return flags;
}

randomx_cache_t *randomx_alloc_cache(void *data, randomx_flags flags) {
  randomx_cache_t *cache    = NULL;
  randomx_argon2_impl *impl = selectArgonImpl(flags);
  if (impl == NULL) {
    return cache;
  }

  cache            = allocMemory(AlignedAllocator, sizeof(randomx_cache_t), 64);
  cache->argonImpl = impl;
  switch ((int)(flags & (RANDOMX_FLAG_JIT | RANDOMX_FLAG_LARGE_PAGES))) {
  case RANDOMX_FLAG_DEFAULT:
    cache->allocatorMode = AlignedAllocator;
    cache->alignment     = CacheLineSize;
    cache->mc            = NULL;
    cache->initialize    = initCache;
    cache->datasetInit   = initDataset;
    cache->memory = (uint8_t *)allocMemory(cache->allocatorMode, CacheSize,
                                           cache->alignment);
    break;

  case RANDOMX_FLAG_JIT:
    cache->allocatorMode = AlignedAllocator;
    cache->alignment     = CacheLineSize;
    cache->mc            = (jrx_machine_t *)data;
    cache->initialize    = initCacheCompile;
    cache->datasetInit = cache->mc->jrx->getDatasetInitFunc(cache->mc->jrxDev);
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_RTL)
    cache->memory = (uint8_t *)FPGACACHEBASE;
#else
    cache->memory = (uint8_t *)allocMemory(cache->allocatorMode, CacheSize,
                                           cache->alignment);
#endif
    break;

  case RANDOMX_FLAG_LARGE_PAGES:
    cache->allocatorMode = LargePageAllocator;
    cache->mc            = NULL;
    cache->initialize    = initCache;
    cache->datasetInit   = initDataset;
    cache->memory = (uint8_t *)allocMemory(cache->allocatorMode, CacheSize,
                                           cache->alignment);
    break;

  case RANDOMX_FLAG_JIT | RANDOMX_FLAG_LARGE_PAGES:
    cache->allocatorMode = LargePageAllocator;
    cache->mc            = (jrx_machine_t *)data;
    cache->initialize  = initCacheCompile;
    cache->datasetInit = cache->mc->jrx->getDatasetInitFunc(cache->mc->jrxDev);
    cache->memory      = (uint8_t *)allocMemory(cache->allocatorMode, CacheSize,
                                           cache->alignment);
    break;

  default:
    UNREACHABLE;
    goto error;
  }
  return cache;
error:
  randomx_release_cache(cache);
  return NULL;
}

void randomx_init_cache(randomx_cache_t *cache, const void *key,
                        size_t keySize) {
  assert(cache != NULL);
  assert(keySize == 0 || key != NULL);
  if (strncmp(cache->cacheKey, key, keySize) ||
      !randomx_cache_isInitialized(cache)) {
#ifndef CONFIG_COMPILE_RTL
    cache->initialize(cache, key, keySize);
#endif
    strncpy(cache->cacheKey, key, keySize);
  }
}

void randomx_release_cache(randomx_cache_t *cache) {
  assert(cache != NULL);
#if !defined(CONFIG_COMPILE_FPGA) || !defined(CONFIG_COMPILE_RTL)
  if (cache->memory != NULL) {
    freeMemory(cache->allocatorMode, cache->memory, CacheSize);
  }
#endif
  freeMemory(AlignedAllocator, cache, sizeof(randomx_cache_t));
}

randomx_dataset_t *randomx_alloc_dataset(randomx_cache_t *cache,
                                         randomx_flags flags) {
  assert(cache != NULL);
  // fail on 32-bit systems if DatasetSize is >= 4 GiB
  if (DatasetSize > 0xffffffff) {
    return NULL;
  }

  randomx_dataset_t *dataset = NULL;

  dataset     = allocMemory(AlignedAllocator, sizeof(randomx_dataset_t), 64);
  dataset->mc = cache->mc;

  if (flags & RANDOMX_FLAG_LARGE_PAGES) {
    dataset->allocatorMode = LargePageAllocator;
    if (rxaMode) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_RTL)
      dataset->memory = (uint8_t *)FPGADATASETBASE;
			memset(dataset->memory, 0, DatasetSize);
#else
      dataset->memory =
          (uint8_t *)rxa_get_ddr(((jrx_rxa_t *)cache->mc->jrxDev)->drv);
#endif
		} else
      dataset->memory = (uint8_t *)allocMemory(
          dataset->allocatorMode, DatasetSize + dump_regs_mem + 128,
          dataset->alignment);
  } else {
    dataset->allocatorMode = AlignedAllocator;
    dataset->alignment     = CacheLineSize;
    if (rxaMode) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_RTL)
      dataset->memory = (uint8_t *)FPGADATASETBASE;
#ifndef CONFIG_COMPILE_RTL
			/* template */
			for (uint32_t i = 0; i < 0x82000000; i+=8) {
				if (((unsigned long)(dataset->memory + i)) >= 0x200000000) {
					printf("dataset->memory %p, i %x, %p\n", dataset->memory, i, dataset->memory + i);
					break;
				}
				*(uint64_t *)(dataset->memory + i) = 0;
			}
#endif
#else
      dataset->memory =
          (uint8_t *)rxa_get_ddr(((jrx_rxa_t *)cache->mc->jrxDev)->drv);
#endif
		} else
      dataset->memory = (uint8_t *)allocMemory(
          dataset->allocatorMode, DatasetSize + dump_regs_mem + 128,
          dataset->alignment);
  }

  if (dataset->memory == NULL) {
    randomx_release_dataset(dataset);
    dataset = NULL;
  }

  return dataset;
}

unsigned long DatasetItemCount = DatasetSize / RANDOMX_DATASET_ITEM_SIZE;

unsigned long randomx_dataset_item_count() { return DatasetItemCount; }

void randomx_init_dataset(randomx_dataset_t *dataset, randomx_cache_t *cache,
                          unsigned long startItem, unsigned long itemCount) {
  assert(dataset != NULL);
  assert(cache != NULL);
  assert(startItem < DatasetItemCount && itemCount <= DatasetItemCount);
  assert(startItem + itemCount <= DatasetItemCount);
 // printf("memory %p, startItem 0x%lx, endItem 0x%lx\n", dataset->memory +
  // startItem * CacheLineSize, startItem, startItem + itemCount);
  cache->datasetInit(cache, dataset->memory + startItem * CacheLineSize,
                     startItem, startItem + itemCount);
#if 0
	FILE *fd = fopen("/mnt/hgfs/Downloads/dataset", "w+");
#if 0
	for (int i = 0; i <= startItem + itemCount; i++) {
		uint64_t *temp = (uint64_t *)(dataset->memory + i * CacheLineSize);

		fprintf(fd, "0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx\n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);
	}
#endif
	printf("start fwrite\n");
	fwrite(dataset->memory, 1, DatasetSize, fd);
	printf("finish\n");
	fclose (fd);
	exit(0);
#endif
}

void *randomx_get_dataset_memory(randomx_dataset_t *dataset) {
  assert(dataset != NULL);
  return dataset->memory;
}

void randomx_release_dataset(randomx_dataset_t *dataset) {
  assert(dataset != NULL);
#if !defined(CONFIG_COMPILE_FPGA) || !defined(CONFIG_COMPILE_RTL)
  if (!rxaMode)
    freeMemory(dataset->allocatorMode, dataset->memory,
               DatasetSize + dump_regs_mem + 128);
#endif
  freeMemory(AlignedAllocator, dataset, sizeof(randomx_dataset_t));
}

randomx_vm_t *randomx_create_vm(void *mc, randomx_flags flags, randomx_cache_t *cache,
                                randomx_dataset_t *dataset) {
  assert(cache != NULL || (flags & RANDOMX_FLAG_FULL_MEM));
  assert(cache == NULL || randomx_cache_isInitialized(cache));
  assert(dataset != NULL || !(flags & RANDOMX_FLAG_FULL_MEM));

  randomx_vm_t *vm = allocMemory(AlignedAllocator, sizeof(randomx_vm_t), 4);
	if (!vm)
		return NULL;
	
	vm->mc = mc;
  switch ((int)(flags & (RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_JIT |
                         RANDOMX_FLAG_HARD_AES | RANDOMX_FLAG_LARGE_PAGES))) {
  case RANDOMX_FLAG_DEFAULT: {
    InterpretedLightVm_t *dev =
        initInterpretedLightVm(true, AlignedAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = InterpretedLightVm_setDataset;
    vm_ops.setCache   = InterpretedLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM: {
    InterpretedVm_t *dev =
        initInterpretedVm(true, AlignedAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = vm_interpreted_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedVm;
  } break;

  case RANDOMX_FLAG_JIT: {
    CompiledLightVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledLightVm((jrx_machine_t *)mc, true, true, AlignedAllocator,
                                CacheLineSize);
    } else {
      dev = initCompiledLightVm((jrx_machine_t *)mc, false, true, AlignedAllocator,
                                CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledLightVm_run;
    vm_ops.setDataset = CompiledLightVm_setDataset;
    vm_ops.setCache   = CompiledLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_JIT: {
    CompiledVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledVm((jrx_machine_t *)mc, true, true, AlignedAllocator,
                           CacheLineSize);
    } else {
      dev = initCompiledVm((jrx_machine_t *)mc, false, true, AlignedAllocator,
                           CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledVm_run;
    vm_ops.setDataset = CompiledVm_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileVm;
  } break;

  case RANDOMX_FLAG_HARD_AES: {
    InterpretedLightVm_t *dev =
        initInterpretedLightVm(false, AlignedAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = InterpretedLightVm_setDataset;
    vm_ops.setCache   = InterpretedLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_HARD_AES: {
    InterpretedVm_t *dev =
        initInterpretedVm(false, AlignedAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = vm_interpreted_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedVm;
  } break;

  case RANDOMX_FLAG_JIT | RANDOMX_FLAG_HARD_AES: {
    CompiledLightVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledLightVm((jrx_machine_t *)mc, true, false, AlignedAllocator,
                                CacheLineSize);
    } else {
      dev = initCompiledLightVm((jrx_machine_t *)mc, false, false, AlignedAllocator,
                                CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledLightVm_run;
    vm_ops.setDataset = CompiledLightVm_setDataset;
    vm_ops.setCache   = CompiledLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_JIT | RANDOMX_FLAG_HARD_AES: {
    CompiledVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledVm((jrx_machine_t *)mc, true, false, AlignedAllocator,
                           CacheLineSize);
    } else {
      dev = initCompiledVm((jrx_machine_t *)mc, false, false, AlignedAllocator,
                           CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledVm_run;
    vm_ops.setDataset = CompiledVm_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileVm;
  } break;

  case RANDOMX_FLAG_LARGE_PAGES: {
    InterpretedLightVm_t *dev =
        initInterpretedLightVm(true, LargePageAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = InterpretedLightVm_setDataset;
    vm_ops.setCache   = InterpretedLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_LARGE_PAGES: {
    InterpretedVm_t *dev =
        initInterpretedVm(true, LargePageAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = vm_interpreted_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedVm;
  } break;

  case RANDOMX_FLAG_JIT | RANDOMX_FLAG_LARGE_PAGES: {
    CompiledLightVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledLightVm((jrx_machine_t *)mc, true, true, AlignedAllocator,
                                CacheLineSize);
    } else {
      dev = initCompiledLightVm((jrx_machine_t *)mc, false, true, AlignedAllocator,
                                CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledLightVm_run;
    vm_ops.setDataset = CompiledLightVm_setDataset;
    vm_ops.setCache   = CompiledLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_JIT | RANDOMX_FLAG_LARGE_PAGES: {
    CompiledVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledVm((jrx_machine_t *)mc, true, true, LargePageAllocator,
                           CacheLineSize);
    } else {
      dev = initCompiledVm((jrx_machine_t *)mc, false, true, LargePageAllocator,
                           CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledVm_run;
    vm_ops.setDataset = CompiledVm_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileVm;
  } break;

  case RANDOMX_FLAG_HARD_AES | RANDOMX_FLAG_LARGE_PAGES: {
    InterpretedLightVm_t *dev =
        initInterpretedLightVm(false, LargePageAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = InterpretedLightVm_setDataset;
    vm_ops.setCache   = InterpretedLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_HARD_AES |
      RANDOMX_FLAG_LARGE_PAGES: {
    InterpretedVm_t *dev =
        initInterpretedVm(false, LargePageAllocator, CacheLineSize);
    vm->dev           = dev;
    vm_ops.run        = vm_interpreted_run;
    vm_ops.setDataset = vm_interpreted_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitInterpretedVm;
  } break;

  case RANDOMX_FLAG_JIT | RANDOMX_FLAG_HARD_AES | RANDOMX_FLAG_LARGE_PAGES: {
    CompiledLightVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledLightVm((jrx_machine_t *)mc, true, false, AlignedAllocator,
                                CacheLineSize);
    } else {
      dev = initCompiledLightVm((jrx_machine_t *)mc, false, false, AlignedAllocator,
                                CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledLightVm_run;
    vm_ops.setDataset = CompiledLightVm_setDataset;
    vm_ops.setCache   = CompiledLightVm_setCache;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileLightVm;
  } break;

  case RANDOMX_FLAG_FULL_MEM | RANDOMX_FLAG_JIT | RANDOMX_FLAG_HARD_AES | RANDOMX_FLAG_LARGE_PAGES: {
    CompiledVm_t *dev = NULL;
    if (flags & RANDOMX_FLAG_SECURE) {
      dev = initCompiledVm((jrx_machine_t *)mc, true, false, LargePageAllocator,
                           CacheLineSize);
    } else {
      dev = initCompiledVm((jrx_machine_t *)mc, false, false, LargePageAllocator,
                           CacheLineSize);
    }
    vm->dev           = dev;
    vm_ops.run        = CompiledVm_run;
    vm_ops.setDataset = CompiledVm_setDataset;
    vm->ops           = &vm_ops;
    vm->exitDev       = exitCompileVm;
  } break;

  default:
    UNREACHABLE;
  }

  if (cache != NULL) {
    vm->ops->setCache(vm->dev, cache);
    strcpy(((VmBase_t *)(vm->dev))->cacheKey, cache->cacheKey);
  }

  if (dataset != NULL)
    vm->ops->setDataset(vm->dev, dataset);

  vm->ops->allocate(vm->dev);

  return vm;
}

void randomx_vm_t_set_cache(randomx_vm_t *machine, randomx_cache_t *cache) {
  assert(machine != NULL);
  assert(cache != NULL && randomx_cache_isInitialized(cache));
  VmBase_t *vm = (VmBase_t *)machine->dev;
  if (strncmp(vm->cacheKey, cache->cacheKey, strlen(cache->cacheKey)) ||
      getMemory(vm) != cache->memory) {
    machine->ops->setCache(machine->dev, cache);
    strcpy(vm->cacheKey, cache->cacheKey);
  }
}

void randomx_vm_t_set_dataset(randomx_vm_t *machine,
                              randomx_dataset_t *dataset) {
  assert(machine != NULL);
  assert(dataset != NULL);
  machine->ops->setDataset(machine->dev, dataset);
}

void randomx_destroy_vm(randomx_vm_t *machine) {
  assert(machine != NULL);
  machine->exitDev(machine->dev);
  freeMemory(AlignedAllocator, machine, sizeof(randomx_vm_t));
}
#define CIPHER_HARDWARE 1
void randomx_calculate_hash(randomx_vm_t *machine, void *input,
                            size_t inputSize, void *output) {
  assert(machine != NULL);
  assert(inputSize == 0 || input != NULL);
  assert(output != NULL);
  // fenv_t fpstate;
  // fegetenv(&fpstate);
  alignas(16) uint64_t tempHash[8];
  int blakeResult;

  if (rxaMode)
    rxa_resetRoundingMode(getRXADevice(machine->mc));
  else
    resetRoundingMode();

  if (rxaMode)
    blakeResult = rxaCipherUpdate(machine->mc, RXA_BLAKE2B, input, inputSize, tempHash,
                                  sizeof(tempHash), NULL);
  else
    blakeResult =
        blake2b(tempHash, sizeof(tempHash), input, inputSize, NULL, 0);

  VmBase_t *vm = (VmBase_t *)machine->dev;
  assert(blakeResult == 0);
  machine->ops->initScratchpad(machine->dev, &tempHash);
  resetRoundingMode();
  for (int chain = 0; chain < RANDOMX_PROGRAM_COUNT - 1; ++chain) {
    machine->ops->run(machine->dev, &tempHash);
    if (rxaMode)
      blakeResult = rxaCipherUpdate(machine->mc, RXA_BLAKE2B, getRegisterFile(vm),
                                    sizeof(RegisterFile_t), tempHash,
                                    sizeof(tempHash), NULL);
    else
      blakeResult = blake2b(tempHash, sizeof(tempHash), getRegisterFile(vm),
                            sizeof(RegisterFile_t), NULL, 0);
    assert(blakeResult == 0);
  }
  machine->ops->run(machine->dev, &tempHash);
  machine->ops->getFinalResult(machine->dev, output, RANDOMX_HASH_SIZE);
  // fesetenv(&fpstate);
}

void randomx_calculate_hash_first(randomx_vm_t *machine, void *input,
                                  size_t inputSize) {
  VmBase_t *vm = (VmBase_t *)machine->dev;
  if (rxaMode)
		rxaCipherUpdate(machine->mc, RXA_BLAKE2B, input, inputSize, vm->tempHash, sizeof(vm->tempHash), NULL);
	else
    blake2b(vm->tempHash, sizeof(vm->tempHash), input, inputSize, NULL, 0);
  machine->ops->initScratchpad(machine->dev, vm->tempHash);
}
extern int step_avp;
void randomx_calculate_hash_next(randomx_vm_t *machine, void *nextInput,
                                 size_t nextInputSize, void *output) {
  VmBase_t *vm = (VmBase_t *)machine->dev;
  if (rxaMode)
    rxa_resetRoundingMode(getRXADevice(machine->mc));
  else
    resetRoundingMode();
  for (uint32_t chain = 0; chain < RANDOMX_PROGRAM_COUNT - 1; ++chain) {
    machine->ops->run(machine->dev, vm->tempHash);
    if (rxaMode)
			rxaCipherUpdate(machine->mc, RXA_BLAKE2B, getRegisterFile(vm), sizeof(RegisterFile_t), vm->tempHash, sizeof(vm->tempHash), NULL);
		else
      blake2b(vm->tempHash, sizeof(vm->tempHash), getRegisterFile(vm),
              sizeof(RegisterFile_t), NULL, 0);
  }
  machine->ops->run(machine->dev, vm->tempHash);
  // Finish current hash and fill the scratchpad for the next hash at the same
  // time
  if (rxaMode)
		rxaCipherUpdate(machine->mc, RXA_BLAKE2B, nextInput, nextInputSize, vm->tempHash, sizeof(vm->tempHash), NULL);
	else
    blake2b(vm->tempHash, sizeof(vm->tempHash), nextInput, nextInputSize, NULL,
            0);
  // get_cache_hit_rate(&thit);
  //printf("Avp step: %d\n", step_avp);
  machine->ops->hashAndFill(machine->dev, output, RANDOMX_HASH_SIZE,
                            vm->tempHash);
}

void randomx_calculate_hash_last(randomx_vm_t *machine, void *output) {
  VmBase_t *vm = (VmBase_t *)machine->dev;
  resetRoundingMode();
  for (int chain = 0; chain < RANDOMX_PROGRAM_COUNT - 1; ++chain) {
    machine->ops->run(machine->dev, vm->tempHash);

    if (rxaMode)
      rxaCipherUpdate(machine->mc, RXA_BLAKE2B, getRegisterFile(vm), sizeof(RegisterFile_t),
                      vm->tempHash, sizeof(vm->tempHash), NULL);
    else
      blake2b(vm->tempHash, sizeof(vm->tempHash), getRegisterFile(vm),
              sizeof(RegisterFile_t), NULL, 0);
  }
  machine->ops->run(machine->dev, vm->tempHash);
  machine->ops->getFinalResult(machine->dev, output, RANDOMX_HASH_SIZE);
}
