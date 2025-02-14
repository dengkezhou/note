/**








**/

#ifndef __IMAPX_PLATFORM_H__
#define __IMAPX_PLATFORM_H__

//
// platform setting, general in project file.
//
#if defined(_IMAPX_XILINX_)
#define _MEM_START  0x40000000
#define _MEM_LENGTH 0x4000000 // 64MB

#define _MMALLOC_FOR_MODULE 0
#elif defined(_IMAPX_DINI_) || defined(_IMAPX_HAPS_) || defined(_IMAPX_S2C_)
#define _MEM_START  0x40000000
#define _MEM_LENGTH 0x40000000 // 1GB

#define _MMALLOC_FOR_MODULE 1
#endif

//
// ADDRESS SPACE ASSINGMENT.
//
#define _PROGRAM_BASE                                                          \
  0x40000000 // [0x40000000]-<16MB>-[0x41000000], include RW, ZI, BSS, RO areas.
#define _HEAP_BASE      0x41000000 // [0x41000000]-<8MB>-[0x41800000]
#define _SVC_STACK_TOP  0x41fffff0 // [0x41800000]-<8MB>-[0x41fffff0]
#define _USR_STACK_TOP  0x420ffff0 // [0x42000000]-<1MB>-[0x420ffff0]
#define _UND_STACK_TOP  0x421ffff0 // [0x42100000]-<1MB>-[0x421ffff0]
#define _ABT_STACK_TOP  0x422ffff0 // [0x42200000]-<1MB>-[0x422ffff0]
#define _FIQ_STACK_TOP  0x424ffff0 // [0x42300000]-<2MB>-[0x424ffff0]
#define _IRQ_STACK_TOP  0x428ffff0 // [0x42500000]-<4MB>-[0x428ffff0]
#define _ISR_TABLE_BASE 0x42900000 // [0x42900000]-<1MB>-[0x42a00000]

#define _MMALLOC_BASE 0x42a00000 // [0x42a00000]-<22MB>-[0x44000000]
#define _MMALLOC_LEN  0x1600000

#define pISR_RESET    *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x0)
#define PISR_UNDEF    *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x4)
#define pISR_SWI      *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x8)
#define pISR_PABORT   *(volatile unsigned int *)(_ISR_TABLE_BASE + 0xc)
#define pISR_DABORT   *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x10)
#define pISR_RESERVED *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x14)
#define pISR_IRQ      *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x18)
#define pISR_FIQ      *(volatile unsigned int *)(_ISR_TABLE_BASE + 0x1c)

#endif // __IMAPX_PLATFORM_H__
