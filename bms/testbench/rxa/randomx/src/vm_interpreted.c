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

#include "vm_interpreted.h"
#include "dataset.h"
#include "intrin_portable.h"
#include "reciprocal.h"
#include "stats-utils.h"
#include "vm_interpreted_light.h"

void vm_interpreted_setDataset(void *vm, randomx_dataset *dataset) {
  InterpretedVm_t *dev   = (InterpretedVm_t *)vm;
  dev->vmbase.datasetPtr = dataset;
  dev->vmbase.mem.memory = dataset->memory;
}

void dumpreg(InterpretedVm_t *dev, NativeRegisterFile_t *nreg,
             const char *phase) {
  // return ;
  if (dump_instr) {
    printf("\n\nround -%d ::: %s\n", dump_instr, phase);
    for (int k = 0; k < 4; k++) {
      printf("r%d: %016zx  ", k * 2, nreg->r[k * 2]);
      printf("r%d: %016zx  ", k * 2 + 1, nreg->r[k * 2 + 1]);

      printf("a%d.lo: %016zx  ", k, *(uint64_t *)&nreg->a[k]);
      printf("a%d.hi: %016zx  ", k, *((uint64_t *)&nreg->a[k] + 1));

      printf("f%d.lo: %016zx  ", k, *(uint64_t *)&nreg->f[k]);
      printf("f%d.hi: %016zx  ", k, *((uint64_t *)&nreg->f[k] + 1));

      printf("e%d.lo: %016zx  ", k, *(uint64_t *)&nreg->e[k]);
      printf("e%d.hi: %016zx  ", k, *((uint64_t *)&nreg->e[k] + 1));
      printf("\n");
    }
  }
}

static void vm_interpreted_datasetRead(void *vm, uint64_t address,
                                       int_reg_t *r) {
  InterpretedVm_t *dev  = (InterpretedVm_t *)vm;
  uint64_t *datasetLine = (uint64_t *)(dev->vmbase.mem.memory + address);
  POKC(dag_read8);
  for (int i = 0; i < RegistersCount; ++i)
    r[i] ^= datasetLine[i];
}

static void vm_interpreted_datasetPrefetch(void *vm, uint64_t address) {
#if 0
  InterpretedVm_t *dev = (InterpretedVm_t *)vm;
	//rx_prefetch_nta is a null function
  rx_prefetch_nta(dev->vmbase.mem.memory + address);
#endif
}

void swap(uint32_t *a, uint32_t *b) {
  int temp;

  temp = *b;
  *b   = *a;
  *a   = temp;
}

void execute(InterpretedVm_t *dev) {

  NativeRegisterFile_t nreg;

  for (unsigned i = 0; i < RegisterCountFlt; ++i) {
    nreg.a[i] = rx_load_vec_f128(&dev->vmbase.reg.a[i].lo);
  }

  for (unsigned i = 0; i < 8; i++)
    nreg.r[i] = 0;

  POKE(pvx, "gen code (interpret)");
  compileProgram(dev->bm, dev->vmbase.program, dev->bytecode, &nreg);
  PEEK(pvx);

  uint32_t spAddr0 = dev->vmbase.mem.mx;
  uint32_t spAddr1 = dev->vmbase.mem.ma;

  progN++;
  for (unsigned ic = 0; ic < RANDOMX_PROGRAM_ITERATIONS; ++ic) {

    // dumpreg(dev, &nreg, "before mixing");

    uint64_t spMix = nreg.r[dev->vmbase.config.readReg0] ^
                     nreg.r[dev->vmbase.config.readReg1];
    spAddr0 ^= spMix;
    spAddr0 &= ScratchpadL3Mask64;
    spAddr1 ^= spMix >> 32;
    spAddr1 &= ScratchpadL3Mask64;
#if 0
		 if(dump_instr)
		 	printf("%d.%d spMix=%016zx, sp0=%08x sp1=%08x\n",
		 	dev->vmbase.config.readReg0, dev->vmbase.config.readReg1,
		 	 spMix, spAddr0, spAddr1);
#endif
    for (unsigned i = 0; i < RegistersCount; ++i)
      nreg.r[i] ^= load64(dev->vmbase.scratchpad + spAddr0 + 8 * i);

    for (unsigned i = 0; i < RegisterCountFlt; ++i)
      nreg.f[i] =
          rx_cvt_packed_int_vec_f128(dev->vmbase.scratchpad + spAddr1 + 8 * i);

    for (unsigned i = 0; i < RegisterCountFlt; ++i)
      nreg.e[i] = maskRegisterExponentMantissa(
          &dev->vmbase.config,
          rx_cvt_packed_int_vec_f128(dev->vmbase.scratchpad + spAddr1 +
                                     8 * (RegisterCountFlt + i)));

    // cmpRegs(0, 0xbe, 2048 - ic, (uint64_t *)&nreg);
    // dumpreg(dev, &nreg, "before 256");

    POKE(pvx1, "run code (interpret)");

    st_ic   = 2048 - ic;
    st_nreg = (uint64_t *)&nreg;

    executeBytecode(dev->bm, dev->bytecode, dev->vmbase.scratchpad,
                    &dev->vmbase.config, dev->vmbase.program);
    PEEK(pvx1);

    // dumpreg(dev, &nreg, "after 256");

    dev->vmbase.mem.mx ^= nreg.r[dev->vmbase.config.readReg2] ^
                          nreg.r[dev->vmbase.config.readReg3];
    dev->vmbase.mem.mx &= CacheLineAlignMask;
#if 0
		 if(dump_instr) 
		 printf("new  ma=%08x, mx=%08x %d %d, %016zx\n", dev->vmbase.mem.ma, dev->vmbase.mem.mx,dev->vmbase.config.readReg2, dev->vmbase.config.readReg3,
		   nreg.r[dev->vmbase.config.readReg2] ^ nreg.r[dev->vmbase.config.readReg3]);
#endif
    dev->ops.datasetPrefetch(dev,
                             dev->vmbase.datasetOffset + dev->vmbase.mem.mx);
    dev->ops.datasetRead(dev, dev->vmbase.datasetOffset + dev->vmbase.mem.ma,
                         nreg.r);

    // cmpRegs(mem.ma, 0x1d, 2048 - ic, (uint64_t *)&nreg);

    swap(&dev->vmbase.mem.mx, &dev->vmbase.mem.ma);

    for (unsigned i = 0; i < RegistersCount; ++i)
      store64(dev->vmbase.scratchpad + spAddr1 + 8 * i, nreg.r[i]);

    for (unsigned i = 0; i < RegisterCountFlt; ++i)
      nreg.f[i] = rx_xor_vec_f128(nreg.f[i], nreg.e[i]);

    // dumpreg(dev, &nreg, "post process");

    for (unsigned i = 0; i < RegisterCountFlt; ++i)
      rx_store_vec_f128((double *)(dev->vmbase.scratchpad + spAddr0 + 16 * i),
                        nreg.f[i]);

    // cmpRegs(0, 0xae, 2048 - ic, (uint64_t *)&nreg);
    // dumpreg(dev, &nreg, "end of for");

    spAddr0 = 0;
    spAddr1 = 0;
    if (dump_instr)
      dump_instr--;
  }

  // dumpreg(dev, &nreg, "after 2048");

  for (unsigned i = 0; i < RegistersCount; ++i)
    store64(&dev->vmbase.reg.r[i], nreg.r[i]);

  for (unsigned i = 0; i < RegisterCountFlt; ++i)
    rx_store_vec_f128(&dev->vmbase.reg.f[i].lo, nreg.f[i]);

  for (unsigned i = 0; i < RegisterCountFlt; ++i)
    rx_store_vec_f128(&dev->vmbase.reg.e[i].lo, nreg.e[i]);
}

void vm_interpreted_run(void *vm, void *seed) {
  InterpretedVm_t *dev = (InterpretedVm_t *)vm;
  vm_generateProgram(&dev->vmbase, seed);
  vm_initialize(&dev->vmbase);
  execute(dev);

  PEOO();
}

InterpretedVm_t *initInterpretedVm(bool softAes, int allocatorMode,
                                   int alignment) {
  InterpretedVm_t *dev = NULL;

  dev = allocMemory(allocatorMode, sizeof(InterpretedVm_t), alignment);
  if (!dev) {
    printf("InterpretedVm alloc Memory Error\n");
    return NULL;
  }
  dev->softAes             = softAes;
  dev->allocatorMode       = allocatorMode;
  dev->alignment           = alignment;
  dev->ops.datasetRead     = vm_interpreted_datasetRead;
  dev->ops.datasetPrefetch = vm_interpreted_datasetPrefetch;
  initVmBase(&dev->vmbase, softAes, allocatorMode, alignment, NULL);
  dev->bm = initBytecodeMachine();
  return dev;
}

void exitInterpretedVm(void *vm) {
  InterpretedVm_t *dev = (InterpretedVm_t *)vm;
  exitVmBase(&dev->vmbase);
  exitBytecodeMachine(dev->bm);
  freeMemory(dev->allocatorMode, dev, sizeof(InterpretedVm_t));
}
