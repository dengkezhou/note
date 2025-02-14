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

#include "vm_compiled.h"
#include "rxa_common.h"
#include "jrx_base.h"
#include "jrx_core.h"
#include "stats-utils.h"

void CompiledVm_setDataset(void *vm, randomx_dataset_t *dataset) {
  CompiledVm_t *dev      = (CompiledVm_t *)vm;
  dev->vmbase.datasetPtr = dataset;
}

void CompiledVm_execute(CompiledVm_t *dev) {
	jrx_machine_t *mc = (jrx_machine_t *)(dev->vmbase.mc);
  memcpy(dev->vmbase.reg.f, dev->vmbase.config.eMask,
         sizeof(dev->vmbase.config.eMask));
  mc->jrx->getProgramFunc(mc->jrxDev)(
      &dev->vmbase.reg, &dev->vmbase.mem, dev->vmbase.scratchpad,
      RANDOMX_PROGRAM_ITERATIONS, mc->jrxDev);
}

void CompiledVm_run(void *vm, void *seed) {
  void *p;

  CompiledVm_t *dev = (CompiledVm_t *)vm;
	jrx_machine_t *mc = (jrx_machine_t *)(dev->vmbase.mc);
  vm_generateProgram(&dev->vmbase, seed);
  vm_initialize(&dev->vmbase);
  if (dev->secureJit) {
    mc->jrx->enableWriting(mc->jrxDev);
  }
  POKE(gen, "gen code (jit)");
  mc->jrx->generateProgram(mc->jrxDev, dev->vmbase.program,
                                &dev->vmbase.config);
  PEEK(gen);
  // perf_flush(2, "summary");
  if (dev->secureJit) {
    mc->jrx->enableExecution(mc->jrxDev);
  }
  dev->vmbase.mem.memory =
      dev->vmbase.datasetPtr->memory + dev->vmbase.datasetOffset;

  POKE(run, "run code (jit)");
  CompiledVm_execute(dev);
  if (dump_instr) {
    printf("\n\nround -%d ::: %s\n", dump_instr, "after 2048");
    for (int k = 0; k < 4; k++) {
      printf("r%d: %016zx  ", k * 2, dev->vmbase.reg.r[k * 2]);
      printf("r%d: %016zx  ", k * 2 + 1, dev->vmbase.reg.r[k * 2 + 1]);

      p = &dev->vmbase.reg.a[k];
      printf("a%d.lo: %016zx  ", k, *(uint64_t *)p);
      printf("a%d.hi: %016zx  ", k, *((uint64_t *)p + 1));

      p = &dev->vmbase.reg.f[k];
      printf("f%d.lo: %016zx  ", k, *(uint64_t *)p);
      printf("f%d.hi: %016zx  ", k, *((uint64_t *)p + 1));

      p = &dev->vmbase.reg.e[k];
      printf("e%d.lo: %016zx  ", k, *(uint64_t *)p);
      printf("e%d.hi: %016zx  ", k, *((uint64_t *)p + 1));
      printf("\n");
    }
  }

  PEEK(run);
}
extern bool rxaMode;
CompiledVm_t *initCompiledVm(jrx_machine_t *mc, bool secureJit, bool softAes,
                             int allocatorMode, int alignment) {
  CompiledVm_t *dev = NULL;

  dev = allocMemory(allocatorMode, sizeof(CompiledVm_t), alignment);
  if (!dev) {
    printf("CompiledVm_t alloc Memory Error\n");
    return NULL;
  }
  dev->softAes       = softAes;
  dev->allocatorMode = allocatorMode;
  dev->alignment     = alignment;
  dev->secureJit     = secureJit;

  initVmBase(&dev->vmbase, softAes, allocatorMode, alignment, mc);

	if (!secureJit)
    ((jrx_machine_t *)dev->vmbase.mc)->jrx->enableAll(
        ((jrx_machine_t *)dev->vmbase.mc)->jrxDev); // make JIT buffer both writable and executable

  return dev;
}

void exitCompileVm(void *vm) {
  CompiledVm_t *dev = (CompiledVm_t *)vm;
  exitVmBase(&dev->vmbase);
  freeMemory(dev->allocatorMode, dev, sizeof(CompiledVm_t));
}
