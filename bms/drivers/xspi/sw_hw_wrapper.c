/***********************************************************************
 * copyright (C) 2013 Cadence Design Systems
 * All rights reserved.
 ***********************************************************************
 * @file           $RCSfile: $
 * @project        $Name:  $
 * @version        $Revision: $
 * @author         kswitala@cadence.com
 * @date           $Date: $
 ***********************************************************************/

#include "sw_hw_wrapper.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//------------------------------------------------------
#if (USE_SIM == 1)
#include <stdarg.h>
#include <sys/mman.h>

#if (USE_MMAP == 1)
struct memory_pointers {
  void *ptr;
  uint32_t size;
  uint8_t active;
} mem_ptr_arr[100]; // MEMORY_POINTERS;

#endif

unsigned long SYS_CLK_FREQ_MHz = 100;

// VERILOG TASKS
void IOWR_32(unsigned int addr, unsigned int val) { sv_axi_write(addr, val); }

unsigned int IORD_32(unsigned int addr) {
  unsigned int _result;
  sv_axi_read(addr, &_result);
  return _result;
}

// --- used only if memory is located inside C env ---
int set_mem(uint64_t addr, uint8_t val) { // for 64b pointers
  // long _tmp = addr;
  // printf(" !! addr = 0x%lx, val=%d \r\n", addr, val);
  *((unsigned char *)(uintptr_t)addr) = val;
  return 0;
}

int read_mem(uint64_t addr) { // for 64b pointers
  return *((unsigned char *)(uintptr_t)addr);
}

// --- additional functions
void sd_delay(unsigned long wait_cnt) {
  sv_wait(1 + (wait_cnt * SYS_CLK_FREQ_MHz /
               5)); // delay value is divided by 5 to decrease simulation time
}

void sd_printf(const char *format, ...) {
  char _buffer[512];
  va_list _args;

  va_start(_args, format);
  vsprintf(_buffer, format, _args);
  va_end(_args);

#if 0
    // send data byte by byte - like in serial port
    int _i;
    for (_i=0; _i<strlen(_buffer); _i++)
      IOWR_32(0x74000000, _buffer[_i]);

#else
  // send whole buffer at once
  sv_stdio_write_str(_buffer);
#endif

  printf("%s", _buffer);
}

char inbyte() { return IORD_32(0x74000000); }

// --- memory protect mechanism ---
void *sv_malloc(uint32_t size) {
  void *_buff;

#if (USE_MMAP == 1)
  int i;
  _buff = mmap(0, size, PROT_READ | PROT_WRITE,
               MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
  for (i = 0; i < 100; i++) {
    if (mem_ptr_arr[i].active != 1)
      break;
  }

  mem_ptr_arr[i].ptr    = _buff;
  mem_ptr_arr[i].size   = size;
  mem_ptr_arr[i].active = 1;
#else
  _buff = malloc(size);
#endif

  // sd_printf("MALLOC: 0x%lx\r\n", _buff);

  sv_add_protect_area((uint64_t)(uintptr_t)_buff, size);
  return _buff;
}

void sv_free(void *buff) {
  sv_remove_protect_area((uint64_t)(uintptr_t)buff);
  // sd_printf("FREE: 0x%x\r\n", buff);

#if (USE_MMAP == 1)
  int i;
  for (i = 0; i < 100; i++) {
    if ((mem_ptr_arr[i].ptr == buff) && (mem_ptr_arr[i].active == 1)) {
      munmap(buff, mem_ptr_arr[i].size);
      mem_ptr_arr[i].active = 0;
      sd_printf("FREE: ptr=0x%lx, size=%d\r\n", mem_ptr_arr[i].ptr,
                mem_ptr_arr[i].size);
      break;
    }
  }
#else
  free(buff);
#endif
}

#else
// static uint32_t  malloc_base_addr = 0x141e0000; //bram addr, should be wr/rd
// mem address but not overlap with cpu __kernel_stack
//
// void* sv_malloc (uint32_t size){
//    void* _buff = malloc_base_addr;
//    sd_printf("current malloc_base_addr 0x%0x with size 0x%0x\n", _buff,
//    size);
//
//    if(size & 0xf){
//        malloc_base_addr = malloc_base_addr + (size & 0xfffffff0) + 0x10;
//    }
//    else{
//        malloc_base_addr = malloc_base_addr + size;
//    }
//    return _buff;
//}

void sv_free(void *buff) {}

// C FUNCTIONS
void sd_delay(unsigned long wait_cnt) {
  volatile unsigned long _i;
  // for (_i=0; _i<(wait_cnt*SYS_CLK_FREQ_MHz); _i++);
  for (_i = 0; _i < (wait_cnt); _i++)
    ;
  // for(_i=0; _i<wait_cnt; _i++)  printf(".");
}

#endif
