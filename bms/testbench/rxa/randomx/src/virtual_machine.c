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

#include "virtual_machine.h"
#include "aes_hash.h"
#include "allocator.h"
#include "blake2/blake2.h"
#include "common.h"
#include "intrin_portable.h"
#include <string.h>
#include "rxa.h"
#include "jrx_core.h"
#include <jrx_rxa.h>
#include <asm/arch-c920/base-map.h>

randomx_vm_ops_t vm_ops = {.allocate       = vm_allocate,
                           .getFinalResult = vm_getFinalResult,
                           .hashAndFill    = vm_hashAndFill,
                           .setDataset     = vm_setDataset,
                           .setCache       = vm_setCache,
                           .initScratchpad = vm_initScratchpad,
                           .run            = NULL};

size_t alignSize(size_t pos, size_t align) {
  return ((pos - 1) / align + 1) * align;
}

RegisterFile_t *getRegisterFile(VmBase_t *dev) { return &dev->reg; }
const void *getScratchpad(VmBase_t *dev) { return dev->scratchpad; }
const Program_t *getProgram(VmBase_t *dev) { return dev->program; }
const uint8_t *getMemory(VmBase_t *dev) { return dev->mem.memory; }
void vm_setDataset(void *vm, randomx_dataset *dataset) {}

void vm_setCache(void *vm, randomx_cache *cache) {}

void resetRoundingMode(void) { rx_reset_float_state(); }

static inline uint64_t getSmallPositiveFloatBits(uint64_t entropy) {
  uint64_t exponent = entropy >> 59; // 0..31
  uint64_t mantissa = entropy & mantissaMask;
  exponent += exponentBias;
  exponent &= exponentMask;
  exponent <<= mantissaSize;
  return exponent | mantissa;
}

static inline uint64_t getStaticExponent(uint64_t entropy) {
  uint64_t exponent = constExponentBits;
  exponent |= (entropy >> (64 - staticExponentBits)) << dynamicExponentBits;
  exponent <<= mantissaSize;
  return exponent;
}

static inline uint64_t getFloatMask(uint64_t entropy) {
  uint64_t mask22bit = (1ULL << 22) - 1;
  return (entropy & mask22bit) | getStaticExponent(entropy);
}

void vm_initialize(VmBase_t *dev) {
  store64(&dev->reg.a[0].lo,
          getSmallPositiveFloatBits(getEntropy(dev->program, 0)));
  store64(&dev->reg.a[0].hi,
          getSmallPositiveFloatBits(getEntropy(dev->program, 1)));
  store64(&dev->reg.a[1].lo,
          getSmallPositiveFloatBits(getEntropy(dev->program, 2)));
  store64(&dev->reg.a[1].hi,
          getSmallPositiveFloatBits(getEntropy(dev->program, 3)));
  store64(&dev->reg.a[2].lo,
          getSmallPositiveFloatBits(getEntropy(dev->program, 4)));
  store64(&dev->reg.a[2].hi,
          getSmallPositiveFloatBits(getEntropy(dev->program, 5)));
  store64(&dev->reg.a[3].lo,
          getSmallPositiveFloatBits(getEntropy(dev->program, 6)));
  store64(&dev->reg.a[3].hi,
          getSmallPositiveFloatBits(getEntropy(dev->program, 7)));
  dev->mem.ma               = getEntropy(dev->program, 8) & CacheLineAlignMask;
  dev->mem.mx               = getEntropy(dev->program, 10);
  uint64_t addressRegisters = getEntropy(dev->program, 12);
  dev->config.readReg0      = 0 + (addressRegisters & 1);
  addressRegisters >>= 1;
  dev->config.readReg1 = 2 + (addressRegisters & 1);
  addressRegisters >>= 1;
  dev->config.readReg2 = 4 + (addressRegisters & 1);
  addressRegisters >>= 1;
  dev->config.readReg3 = 6 + (addressRegisters & 1);
  dev->datasetOffset =
      (getEntropy(dev->program, 13) % (DatasetExtraItems + 1)) * CacheLineSize;
  store64(&dev->config.eMask[0], getFloatMask(getEntropy(dev->program, 14)));
  store64(&dev->config.eMask[1], getFloatMask(getEntropy(dev->program, 15)));
}
extern bool rxaMode;
void vm_allocate(void *vm) {
  VmBase_t *dev = (VmBase_t *)vm;
	jrx_machine_t *mc = (jrx_machine_t *)dev->mc;
	jrx_rxa_t *rxa = (jrx_rxa_t *)mc->jrxDev;

  if (dev->datasetPtr == NULL) {
    printf("Cache/Dataset not set\n");
    return;
  }
  if (!dev->softAes) { // if hardware AES is not supported, it's better to fail
                       // now than to return a ticking bomb
    rx_vec_i128 tmp = rx_load_vec_i128((const rx_vec_i128 *)&dev->aesDummy);
    tmp             = rx_aesenc_vec_i128(tmp, tmp);
    rx_store_vec_i128((rx_vec_i128 *)&dev->aesDummy, tmp);
  }
  if (rxaMode)
    dev->scratchpad = (uint8_t *)(ITCS_RXA_DRAM_ADDR(rxa->id));
  else
    dev->scratchpad = (uint8_t *)allocMemory(dev->allocatorMode, ScratchpadSize,
                                             dev->alignment);
}

void vm_getFinalResult(void *vm, void *out, size_t outSize) {
  VmBase_t *dev = (VmBase_t *)vm;
  if (rxaMode) {
		rxaCipherUpdate(dev->mc, RXA_AES1RX4_HASH, dev->scratchpad, ScratchpadSize, &dev->reg.a, -1, NULL);
		rxaCipherUpdate(dev->mc, RXA_BLAKE2B, &dev->reg, sizeof(RegisterFile_t), out, outSize, NULL);
	} else {
    hashAes1Rx4(dev->softAes, dev->scratchpad, ScratchpadSize, &dev->reg.a);
    blake2b(out, outSize, &dev->reg, sizeof(RegisterFile_t), NULL, 0);
  }
}

void vm_hashAndFill(void *vm, void *out, size_t outSize, uint64_t *fill_state) {
  VmBase_t *dev = (VmBase_t *)vm;
  if (rxaMode) {
		rxaCipherUpdate(dev->mc, RXA_AES1RX4_MUTI, (void *)getScratchpad(dev), ScratchpadSize, &dev->reg.a, 64, fill_state);
		rxaCipherUpdate(dev->mc, RXA_BLAKE2B, &dev->reg, sizeof(RegisterFile_t), out, outSize, NULL);
	} else {
    hashAndFillAes1Rx4(dev->softAes, (void *)getScratchpad(dev), ScratchpadSize,
                       &dev->reg.a, fill_state);
    blake2b(out, outSize, &dev->reg, sizeof(RegisterFile_t), NULL, 0);
  }
}

void vm_initScratchpad(void *vm, void *seed) {
  VmBase_t *dev = (VmBase_t *)vm;
  if (rxaMode)
		rxaCipherUpdate(dev->mc, RXA_AES1RX4, seed, 64, dev->scratchpad, ScratchpadSize, NULL);
	else
#ifndef CONFIG_COMPILE_RTL
    fillAes1Rx4(dev->softAes, seed, ScratchpadSize, dev->scratchpad);
#else
    ;
#endif
}

void vm_generateProgram(VmBase_t *dev, void *seed) {
  if (rxaMode)
		rxaCipherUpdate(dev->mc, RXA_AES4RX4, seed, 64, dev->program, sizeof(Program_t), NULL);
	else
    fillAes4Rx4(dev->softAes, seed, sizeof(Program_t), dev->program);
}

int initVmBase(VmBase_t *dev, bool softAes, int allocatorMode, int alignment, void *mc) {
	jrx_machine_t *devmc = (jrx_machine_t *)mc;
	jrx_rxa_t *rxa = (jrx_rxa_t *)devmc->jrxDev;

  dev->softAes       = softAes;
  dev->allocatorMode = allocatorMode;
  dev->alignment     = alignment;
	dev->mc = mc;
	
	if (rxaMode)
		dev->program = (Program_t *)(ITCS_RXA_IRAM_ADDR(rxa->id) + 0x3700); //  OFFSCIPHER4R4
	else
  	dev->program = initProgram();
  return 0;
}

void exitVmBase(VmBase_t *dev) {
	if (!rxaMode)
  	exitProgram(dev->program);
  if (dev->scratchpad && !rxaMode)
    freeMemory(dev->allocatorMode, dev->scratchpad, ScratchpadSize);
}
