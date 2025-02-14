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
#include <linux/types.h>
#include "blake2_generator.h"
#include "allocator.h"
#include "blake2/blake2.h"
#include "blake2/endian.h"
#include "stats-utils.h"
#include <stddef.h>

static int maxSeedSize = 60;

Blake2Generator_t *initBlake2Generator(void) {
  Blake2Generator_t *dev = NULL;

  dev = allocMemory(AlignedAllocator, sizeof(Blake2Generator_t), 32);
  if (!dev) {
    printf("Blake2Generator alloc Memory Error\n");
    return NULL;
  }
  return dev;
}

void exitBlake2Generator(Blake2Generator_t *dev) {
  freeMemory(AlignedAllocator, dev, sizeof(Blake2Generator_t));
}

void checkData(Blake2Generator_t *dev, const size_t bytesNeeded) {
  if (dev->dataIndex + bytesNeeded > sizeof(dev->data)) {
    blake2b(dev->data, sizeof(dev->data), dev->data, sizeof(dev->data), NULL,
            0);
    dev->dataIndex = 0;
  }
}

void Blake2Generator_seed_init(Blake2Generator_t *dev, const void *seed,
                               size_t seedSize, int nonce) {
  dev->dataIndex = sizeof(dev->data);
  memset(dev->data, 0, sizeof(dev->data));
  memcpy(dev->data, seed, seedSize > maxSeedSize ? maxSeedSize : seedSize);
  store32(&dev->data[maxSeedSize], nonce);
}

uint8_t Blake2Generator_getByte(Blake2Generator_t *dev) {
  checkData(dev, 1);
  return dev->data[dev->dataIndex++];
}

uint32_t Blake2Generator_getUInt32(Blake2Generator_t *dev) {
  checkData(dev, 4);
  int ret = load32(&(dev->data[dev->dataIndex]));
  dev->dataIndex += 4;
  return ret;
}
