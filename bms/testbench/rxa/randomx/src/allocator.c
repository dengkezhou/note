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
#include "allocator.h"
#include "rxa_common.h"
#include "intrin_portable.h"
#include "virtual_memory.h"
#include <malloc.h>

void *aligned_allocMemory(size_t count, size_t alignment) {
  void *mem = malloc(count); // rx_aligned_alloc(count, alignment);
  if (mem == NULL) {
    printf("alloc mem error %d\n", count);
    return NULL;
  }
  return mem;
}

void aligned_freeMemory(void *ptr, size_t count) {
  // rx_aligned_free(ptr);
  if (ptr)
    free(ptr);
}

void *largePage_allocMemory(size_t count) {
  return allocLargePagesMemory(count);
}

void largePage_freeMemory(void *ptr, size_t count) {
  freePagedMemory(ptr, count);
};

void *allocMemory(int mode, size_t size, size_t alignment) {
  if (mode == AlignedAllocator) {
    return aligned_allocMemory(size, alignment);
  } else
    return largePage_allocMemory(size);
}

void freeMemory(int mode, void *buf, size_t size) {
  if (mode == AlignedAllocator)
    aligned_freeMemory(buf, size);
  else
    largePage_freeMemory(buf, size);
}
