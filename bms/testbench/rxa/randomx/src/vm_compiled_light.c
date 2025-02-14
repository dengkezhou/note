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

#include "vm_compiled_light.h"
#include "rxa_common.h"

void CompiledLightVm_setDataset(void *vm, randomx_dataset *dataset) {}

void CompiledLightVm_setCache(void *vm, randomx_cache_t *cache) {
  CompiledLightVm_t *dev = (CompiledLightVm_t *)vm;
	jrx_machine_t *mc = (jrx_machine_t *)(dev->vmbase.mc);

  dev->vmbase.cachePtr   = cache;
  dev->vmbase.mem.memory = cache->memory;
  if (dev->secureJit) {
    mc->jrx->enableWriting(mc->jrxDev);
  }
  mc->jrx->generateSuperscalarHash(mc->jrxDev, cache->programs,
                                        cache->reciprocalCache);
  if (dev->secureJit) {
    mc->jrx->enableExecution(mc->jrxDev);
  }
}

void CompiledLightVm_run(void *vm, void *seed) {
  CompiledLightVm_t *dev = (CompiledLightVm_t *)vm;
	jrx_machine_t *mc = (jrx_machine_t *)(dev->vmbase.mc);

  vm_generateProgram(&dev->vmbase, seed);
  vm_initialize(&dev->vmbase);
  if (dev->secureJit) {
    mc->jrx->enableWriting(mc->jrxDev);
  }
  mc->jrx->generateProgramLight(mc->jrxDev, dev->vmbase.program,
                                     &dev->vmbase.config,
                                     dev->vmbase.datasetOffset);
  if (dev->secureJit) {
    mc->jrx->enableExecution(mc->jrxDev);
  }
  CompiledVm_execute(dev);
}

CompiledLightVm_t *initCompiledLightVm(jrx_machine_t *mc, bool secureJit,
                                       bool softAes, int allocatorMode,
                                       int alignment) {
  return (CompiledLightVm_t *)initCompiledVm(mc, secureJit, softAes,
                                             allocatorMode, alignment);
}

void exitCompileLightVm(void *vm) {
  CompiledLightVm_t *dev = (CompiledLightVm_t *)vm;
  exitCompileVm((CompiledVm_t *)dev);
}
