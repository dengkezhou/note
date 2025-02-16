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

#include "virtual_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//#include <stdexcept.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#else
#ifdef __APPLE__
#include <mach/vm_statistics.h>
#endif
//#include <sys/mman.h>
//#include <sys/types.h>
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0 // MAP_ANON
#endif
#define PAGE_READONLY          0 // PROT_READ
#define PAGE_READWRITE         0 //(PROT_READ | PROT_WRITE)
#define PAGE_EXECUTE_READ      0 //(PROT_READ | PROT_EXEC)
#define PAGE_EXECUTE_READWRITE 0 //(PROT_READ | PROT_WRITE | PROT_EXEC)
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
void setPrivilege(const char *pszPrivilege, BOOL bEnable) {
  HANDLE hToken;
  TOKEN_PRIVILEGES tp;
  BOOL status;
  DWORD error;

  if (!OpenProcessToken(GetCurrentProcess(),
                        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
    printf("OpenProcessToken Error\n");
    exit(1);
  }

  if (!LookupPrivilegeValue(NULL, pszPrivilege, &tp.Privileges[0].Luid)) {
    printf("LookupPrivilegeValue Error\n");
    exit(1);
  }

  tp.PrivilegeCount = 1;

  if (bEnable)
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  else
    tp.Privileges[0].Attributes = 0;

  status =
      AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

  error = GetLastError();
  if (!status || (error != ERROR_SUCCESS)) {
    printf("AdjustTokenPrivileges Error\n");
    exit(1);
  }

  if (!CloseHandle(hToken)) {
    printf("CloseHandle Error\n");
    exit(1);
  }
}
#endif

void *allocMemoryPages(size_t bytes) {
  void *mem;
#if defined(_WIN32) || defined(__CYGWIN__)
  mem = VirtualAlloc(NULL, bytes, MEM_COMMIT, PAGE_READWRITE);
  if (mem == NULL) {
    printf("allocMemoryPages - VirtualAlloc Error\n");
    exit(1);
  }
#else
#if defined(__NetBSD__)
#define RESERVED_FLAGS PROT_MPROTECT(PROT_EXEC)
#else
#define RESERVED_FLAGS 0
#endif
#ifdef __APPLE__
#include <TargetConditionals.h>
#ifdef TARGET_OS_OSX
#define MEXTRA MAP_JIT
#else
#define MEXTRA 0
#endif
#else
#define MEXTRA 0
#endif
#if 0
  mem = mmap(NULL, bytes, PAGE_READWRITE | RESERVED_FLAGS,
             MAP_ANONYMOUS | MAP_PRIVATE | MEXTRA, -1, 0);
  if (mem == MAP_FAILED) {
    printf("allocMemoryPages - mmap failed\n");
    exit(1);
  }
#else
  mem = malloc(bytes);
#endif
#endif
  return mem;
}

static inline void pageProtect(void *ptr, size_t bytes, int rules) {
#if defined(_WIN32) || defined(__CYGWIN__)
  DWORD oldp;
  if (!VirtualProtect(ptr, bytes, (DWORD)rules, &oldp)) {
    printf("VirtualProtect Error\n");
    exit(1);
  }
#else
#if 0
  if (-1 == mprotect(ptr, bytes, rules)) {
    printf("mprotect failed\n");
    exit(1);
  }
#endif
#endif
}

void setPagesRW(void *ptr, size_t bytes) {
  pageProtect(ptr, bytes, PAGE_READWRITE);
}

void setPagesRX(void *ptr, size_t bytes) {
  pageProtect(ptr, bytes, PAGE_EXECUTE_READ);
}

void setPagesRWX(void *ptr, size_t bytes) {
  pageProtect(ptr, bytes, PAGE_EXECUTE_READWRITE);
}

void *allocLargePagesMemory(size_t bytes) {
  void *mem;
#if defined(_WIN32) || defined(__CYGWIN__)
  setPrivilege("SeLockMemoryPrivilege", 1);
  auto pageMinimum = GetLargePageMinimum();
  if (pageMinimum > 0)
    mem = VirtualAlloc(NULL, alignSize(bytes, pageMinimum),
                       MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES,
                       PAGE_READWRITE);
  else {
    printf("allocLargePagesMemory - Large pages are not supported\n");
    exit(1);
  }
  if (mem == NULL) {
    printf("allocLargePagesMemory - VirtualAlloc Error\n");
    exit(1);
  }
#else
#ifdef __APPLE__
  mem = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
             VM_FLAGS_SUPERPAGE_SIZE_2MB, 0);
#elif defined(__FreeBSD__)
  mem = mmap(NULL, bytes, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_ALIGNED_SUPER, -1, 0);
#elif defined(__OpenBSD__) || defined(__NetBSD__)
  mem = MAP_FAILED; // OpenBSD does not support huge pages
#else
#if 0
  mem = mmap(NULL, bytes, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_POPULATE, -1, 0);
#else
  mem = NULL;
#endif
#endif
#if 0
  if (mem == MAP_FAILED) {
    printf("allocLargePagesMemory - mmap failed\n");
    exit(1);
  }
#endif
#endif
  return mem;
}

void freePagedMemory(void *ptr, size_t bytes) {
#if defined(_WIN32) || defined(__CYGWIN__)
  VirtualFree(ptr, 0, MEM_RELEASE);
#else
  // munmap(ptr, bytes);
  if (ptr)
    free(ptr);
#endif
}
