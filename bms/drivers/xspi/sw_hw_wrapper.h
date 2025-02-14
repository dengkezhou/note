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

#ifndef _SW_HW_WRAPPER_H_
#define _SW_HW_WRAPPER_H_

#include <stdint.h>

void sd_delay(unsigned long wait_cnt);

extern long unsigned int SYS_CLK_FREQ_MHz;
#define USE_SIM   0
#define USE_MMAP  0
#define USE_TIMER 0
#define CDNS_OSPI 0

#if (USE_SIM == 1)
// program related defines
#include <stdio.h>
#define xil_printf               printf
#define cpu_enable_interrupts()  ;
#define cpu_disable_interrupts() ;

void IOWR_32(unsigned int addr, unsigned int val);
unsigned int IORD_32(unsigned int addr);

void *sv_malloc(uint32_t size);
void sv_free(void *buff);

int set_mem(uint64_t addr, uint8_t val);
int read_mem(uint64_t addr);

void sd_printf(const char *format, ...);
char inbyte();

extern int sv_axi_read(int _a1, unsigned int *_a2);
extern int sv_wait(int _a1);
extern int sv_axi_write(int _a1, int _a2);

extern int sv_add_protect_area(uint64_t _a1, int _a2);
extern int sv_remove_protect_area(uint64_t _a1);

extern int sv_stdio_write_str(const char *str);

#define XPAR_TMRCTR_0_BASEADDR  0x72000000
#define XPAR_TMRCTR_0_DEVICE_ID 0

#else
#define SYS_CLK_FREQ_MHz 100

// C FUNCTIONS/DEFINES
//#include <xparameters.h>
//#define INTC_0_BASE XPAR_INTC_0_BASEADDR
//#define sd_printf(fmt, ...) printf("[XSPI] "fmt, ##__VA_ARGS__)
#define sd_printf        printf
//#define cpu_enable_interrupts microblaze_enable_interrupts
//#define cpu_disable_interrupts microblaze_disable_interrupts

//#define sv_malloc malloc
//#define sv_free free
#define sv_malloc        soc_malloc
void sv_free(void *buff);

#define IOWR_32(register_address, data)                                        \
  (*((volatile unsigned int *)(register_address))) = data

#define IORD_32(register_address)                                              \
  (*((volatile unsigned int *)(register_address)))

void sd_delay(unsigned long wait_cnt);
#endif

#endif // _SW_HW_WRAPPER_H_
