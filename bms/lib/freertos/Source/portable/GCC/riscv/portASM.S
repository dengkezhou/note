/*
 * FreeRTOS Kernel V10.3.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*
 * The FreeRTOS kernel's RISC-V port is split between the the code that is
 * common across all currently supported RISC-V chips (implementations of the
 * RISC-V ISA), and code which tailors the port to a specific RISC-V chip:
 *
 * + The code that is common to all RISC-V chips is implemented in
 *   FreeRTOS\Source\portable\GCC\RISC-V-RV32\portASM.S.  There is only one
 *   portASM.S file because the same file is used no matter which RISC-V chip is
 *   in use.
 *
 * + The code that tailors the kernel's RISC-V port to a specific RISC-V
 *   chip is implemented in freertos_risc_v_chip_specific_extensions.h.  There
 *   is one freertos_risc_v_chip_specific_extensions.h that can be used with any
 *   RISC-V chip that both includes a standard CLINT and does not add to the
 *   base set of RISC-V registers.  There are additional
 *   freertos_risc_v_chip_specific_extensions.h files for RISC-V implementations
 *   that do not include a standard CLINT or do add to the base set of RISC-V
 *   registers.
 *
 * CARE MUST BE TAKEN TO INCLDUE THE CORRECT
 * freertos_risc_v_chip_specific_extensions.h HEADER FILE FOR THE CHIP
 * IN USE.  To include the correct freertos_risc_v_chip_specific_extensions.h
 * header file ensure the path to the correct header file is in the assembler's
 * include path.
 *
 * This freertos_risc_v_chip_specific_extensions.h is for use on RISC-V chips
 * that include a standard CLINT and do not add to the base set of RISC-V
 * registers.
 *
 */
#if __riscv_xlen == 64
	#define portWORD_SIZE 8
	#define store_x sd
	#define load_x ld
#elif __riscv_xlen == 32
	#define store_x sw
	#define load_x lw
	#define portWORD_SIZE 4
#else
	#error Assembler did not define __riscv_xlen
#endif

#include "freertos_risc_v_chip_specific_extensions.h"

/* Check the freertos_risc_v_chip_specific_extensions.h and/or command line
definitions. */
#if defined( portasmHAS_CLINT ) && defined( portasmHAS_MTIME )
	#error The portasmHAS_CLINT constant has been deprecated.  Please replace it with portasmHAS_MTIME.  portasmHAS_CLINT and portasmHAS_MTIME cannot both be defined at once.  See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifdef portasmHAS_CLINT
	#warning The portasmHAS_CLINT constant has been deprecated.  Please replace it with portasmHAS_MTIME and portasmHAS_SIFIVE_CLINT.  For now portasmHAS_MTIME and portasmHAS_SIFIVE_CLINT are derived from portasmHAS_CLINT.  See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
	#define portasmHAS_MTIME portasmHAS_CLINT
	#define portasmHAS_SIFIVE_CLINT portasmHAS_CLINT
#endif

#ifndef portasmHAS_MTIME
	#error freertos_risc_v_chip_specific_extensions.h must define portasmHAS_MTIME to either 1 (MTIME clock present) or 0 (MTIME clock not present).  See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef portasmHANDLE_INTERRUPT
	#error portasmHANDLE_INTERRUPT must be defined to the function to be called to handle external/peripheral interrupts.  portasmHANDLE_INTERRUPT can be defined on the assembler command line or in the appropriate freertos_risc_v_chip_specific_extensions.h header file.  https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef portasmHAS_SIFIVE_CLINT
	#define portasmHAS_SIFIVE_CLINT 0
#endif

/* Only the standard core registers are stored by default.  Any additional
registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
specific version of freertos_risc_v_chip_specific_extensions.h.  See the notes
at the top of this file. */
#define portCONTEXT_SIZE ( 30 * portWORD_SIZE )

.global xPortStartFirstTask
.global freertos_risc_v_trap_handler
.global Mtspend_Handler
.global Stspend_Handler
.global pxPortInitialiseStack
.extern pxCurrentTCB
.extern ulPortTrapHandler
.extern vTaskSwitchContext
.extern xTaskIncrementTick
.extern Timer_IRQHandler
.extern pullMachineTimerCompareRegister
.extern pullNextTime
.extern uxTimerIncrementsForOneTick /* size_t type so 32-bit on 32-bit core and 64-bits on 64-bit core. */
.extern xISRStackTop
.extern portasmHANDLE_INTERRUPT

#include <asm/arch-c920/base-map.h>

/********************************************************************
 * Functions: vPortYield
 *
 ********************************************************************/
.global vPortYield
.type   vPortYield, %function
vPortYield:
#ifdef CONFIG_KERNEL_RUN_SMODE
    li      t0, (PLIC_BASE + 0x400c000)
#else
    li      t0, (PLIC_BASE + 0x4000000)
#endif
    li      t2, 0x1    
    sw      t2, 0(t0)
#if ((CONFIG_CPU_TYPE == __cputype_c908v) || (CONFIG_CPU_TYPE == __cputype_c908v))
    fence   iorw, iorw
#endif

__loop:
    lw      t2, 0(t0)
    seqz    t1, t2
#ifdef CONFIG_KERNEL_RUN_SMODE
    csrr    t2, sip
    andi    t2, t2, 0x2
#else
    csrr    t2, mip
    andi    t2, t2, 0x8
#endif
    snez    t3, t2
    add     t2, t3, t1
    beqz    t2, __loop

    ret

.align 8
.func
Mtspend_Handler:
Stspend_Handler:
    addi    sp, sp, -(120+120)
    sd      x1,  (0  +0  )(sp)
    sd      x3,  (4  +4  )(sp)
    sd      x4,  (8  +8  )(sp)
    sd      x5,  (12 +12 )(sp)
    sd      x6,  (16 +16 )(sp)
    sd      x7,  (20 +20 )(sp)
    sd      x8,  (24 +24 )(sp)
    sd      x9,  (28 +28 )(sp)
    sd      x10, (32 +32 )(sp)
    sd      x11, (36 +36 )(sp)
    sd      x12, (40 +40 )(sp)
    sd      x13, (44 +44 )(sp)
    sd      x14, (48 +48 )(sp)
    sd      x15, (52 +52 )(sp)
    sd      x16, (56 +56 )(sp)
    sd      x17, (60 +60 )(sp)
    sd      x18, (64 +64 )(sp)
    sd      x19, (68 +68 )(sp)
    sd      x20, (72 +72 )(sp)
    sd      x21, (76 +76 )(sp)
    sd      x22, (80 +80 )(sp)
    sd      x23, (84 +84 )(sp)
    sd      x24, (88 +88 )(sp)
    sd      x25, (92 +92 )(sp)
    sd      x26, (96 +96 )(sp)
    sd      x27, (100+100)(sp)
    sd      x28, (104+104)(sp)
    sd      x29, (108+108)(sp)
    sd      x30, (112+112)(sp)
    sd      x31, (116+116)(sp)

    portasmSAVE_ADDITIONAL_REGISTERS

    addi    sp, sp, -(8 + 8)
#ifdef CONFIG_KERNEL_RUN_SMODE
    csrr    t0, sepc
    sd      t0, (0 + 0)(sp)
    csrr    t0, sstatus
    sd      t0, (4 + 4)(sp)
#else
    csrr    t0, mepc
    sd      t0, (0 + 0)(sp)
    csrr    t0, mstatus
    sd      t0, (4 + 4)(sp)
#endif

    la      a1, pxCurrentTCB
    ld      a1, (a1)
    sd      sp, (a1)

    jal     vTaskSwitchContext

    la      a1, pxCurrentTCB
    ld      a1, (a1)
    ld      sp, (a1)

#ifdef CONFIG_KERNEL_RUN_SMODE
    li      t0, (PLIC_BASE + 0x400c000)
#else
    li      t0, (PLIC_BASE + 0x4000000)
#endif
    li      t2, 0x0    
    sw      t2, 0(t0)
#if ((CONFIG_CPU_TYPE == __cputype_c908v) || (CONFIG_CPU_TYPE == __cputype_c908v))
    fence   iorw, iorw
#endif

#ifdef CONFIG_KERNEL_RUN_SMODE
    ld      t0, (0 + 0)(sp)
    csrw    sepc, t0

    ld      t0, (4 + 4)(sp)
    csrw    sstatus, t0
#else
    ld      t0, (0 + 0)(sp)
    csrw    mepc, t0

    ld      t0, (4 + 4)(sp)
    csrw    mstatus, t0
#endif
    addi    sp, sp, (8 + 8)

    portasmRESTORE_ADDITIONAL_REGISTERS

    ld     x31, (116+116)(sp)
    ld     x30, (112+112)(sp)
    ld     x29, (108+108)(sp)
    ld     x28, (104+104)(sp)
    ld     x27, (100+100)(sp)
    ld     x26, (96 +96 )(sp)
    ld     x25, (92 +92 )(sp)
    ld     x24, (88 +88 )(sp)
    ld     x23, (84 +84 )(sp)
    ld     x22, (80 +80 )(sp)
    ld     x21, (76 +76 )(sp)
    ld     x20, (72 +72 )(sp)
    ld     x19, (68 +68 )(sp)
    ld     x18, (64 +64 )(sp)
    ld     x17, (60 +60 )(sp)
    ld     x16, (56 +56 )(sp)
    ld     x15, (52 +52 )(sp)
    ld     x14, (48 +48 )(sp)
    ld     x13, (44 +44 )(sp)
    ld     x12, (40 +40 )(sp)
    ld     x11, (36 +36 )(sp)
    ld     x10, (32 +32 )(sp)
    ld     x9,  (28 +28 )(sp)
    ld     x8,  (24 +24 )(sp)
    ld     x7,  (20 +20 )(sp)
    ld     x6,  (16 +16 )(sp)
    ld     x5,  (12 +12 )(sp)
    ld     x4,  (8  +8  )(sp)
    ld     x3,  (4  +4  )(sp)
    ld     x1,  (0  +0  )(sp)

    addi    sp, sp, (120+120)
#ifdef CONFIG_KERNEL_RUN_SMODE
    sret
#else
		addi   sp, sp, -(4+4)
	  sd     x5, (sp)
	  li     x5, 0xfffffffffffffffe
		beq    x5, x1, initSP
		ld     x5, (sp)
	  addi   sp, sp, (4 + 4)
    ret
initSP:
    ld     x5, (sp)
	  addi   sp, sp, (4 + 4)
    mret
#endif
    .endfunc


.align 8
.func
xPortStartFirstTask:

#if( portasmHAS_SIFIVE_CLINT != 0 )
	/* If there is a clint then interrupts can branch directly to the FreeRTOS
	trap handler.  Otherwise the interrupt controller will need to be configured
	outside of this file. */
//	la t0, freertos_risc_v_trap_handler
//	csrw mtvec, t0
#endif /* portasmHAS_CLILNT */

    la      a0, pxCurrentTCB
    ld      a0, (a0)
    ld      sp, (a0)

#ifdef CONFIG_KERNEL_RUN_SMODE
    ld      t0, (0 + 0)(sp)
    csrw    sepc, t0

    ld      t0, (4 + 4)(sp)
    csrw    sstatus, t0
#else
    ld      t0, (0 + 0)(sp)
    csrw    mepc, t0

    ld      t0, (4 + 4)(sp)
    csrw    mstatus, t0
#endif
    addi    sp, sp, (8 + 8)

#if CONFIG_CPU_C908V == 1
#if CONFIG_RISCV_VECTOR_LEN == 128
    vl8r.v  v0, (sp)
    addi    sp, sp, 128
    vl8r.v  v8, (sp)
    addi    sp, sp, 128
    vl8r.v  v16, (sp)
    addi    sp, sp, 128
    vl8r.v  v24, (sp)
    addi    sp, sp, 128
#endif
#if CONFIG_RISCV_VECTOR_LEN == 256
    vl8r.v  v0, (sp)
    addi    sp, sp, 256
    vl8r.v  v8, (sp)
    addi    sp, sp, 256
    vl8r.v  v16, (sp)
    addi    sp, sp, 256
    vl8r.v  v24, (sp)
    addi    sp, sp, 256
#endif
#endif

#if __riscv_flen == 64
    fld      f31, (0  +0  )(sp)
    fld      f30, (4  +4  )(sp)
    fld      f29, (8  +8  )(sp)
    fld      f28, (12 +12 )(sp)
    fld      f27, (16 +16 )(sp)
    fld      f26, (20 +20 )(sp)
    fld      f25, (24 +24 )(sp)
    fld      f24, (28 +28 )(sp)
    fld      f23, (32 +32 )(sp)
    fld      f22, (36 +36 )(sp)
    fld      f21, (40 +40 )(sp)
    fld      f20, (44 +44 )(sp)
    fld      f19, (48 +48 )(sp)
    fld      f18, (52 +52 )(sp)
    fld      f17, (56 +56 )(sp)
    fld      f16, (60 +60 )(sp)
    fld      f15, (64 +64 )(sp)
    fld      f14, (68 +68 )(sp)
    fld      f13, (72 +72 )(sp)
    fld      f12, (76 +76 )(sp)
    fld      f11, (80 +80 )(sp)
    fld      f10, (84 +84 )(sp)
    fld      f9,  (88 +88 )(sp)
    fld      f8,  (92 +92 )(sp)
    fld      f7,  (96 +96 )(sp)
    fld      f6,  (100+100)(sp)
    fld      f5,  (104+104)(sp)
    fld      f4,  (108+108)(sp)
    fld      f3,  (112+112)(sp)
    fld      f2,  (116+116)(sp)
    fld      f1,  (120+120)(sp)
    fld      f0,  (124+124)(sp)

    addi    sp, sp, (128+128)
#endif

    ld      x31, (116+116)(sp)
    ld      x30, (112+112)(sp)
    ld      x29, (108+108)(sp)
    ld      x28, (104+104)(sp)
    ld      x27, (100+100)(sp)
    ld      x26, (96 +96 )(sp)
    ld      x25, (92 +92 )(sp)
    ld      x24, (88 +88 )(sp)
    ld      x23, (84 +84 )(sp)
    ld      x22, (80 +80 )(sp)
    ld      x21, (76 +76 )(sp)
    ld      x20, (72 +72 )(sp)
    ld      x19, (68 +68 )(sp)
    ld      x18, (64 +64 )(sp)
    ld      x17, (60 +60 )(sp)
    ld      x16, (56 +56 )(sp)
    ld      x15, (52 +52 )(sp)
    ld      x14, (48 +48 )(sp)
    ld      x13, (44 +44 )(sp)
    ld      x12, (40 +40 )(sp)
    ld      x11, (36 +36 )(sp)
    ld      x10, (32 +32 )(sp)
    ld      x9,  (28 +28 )(sp)
    ld      x8,  (24 +24 )(sp)
    ld      x7,  (20 +20 )(sp)
    ld      x6,  (16 +16 )(sp)
    ld      x5,  (12 +12 )(sp)
    ld      x4,  (8  +8  )(sp)
    ld      x3,  (4  +4  )(sp)
    ld      x1,  (0  +0  )(sp)

    addi    sp, sp, (120+120)

#ifdef CONFIG_KERNEL_RUN_SMODE
    sret
#else
    mret
#endif
	.endfunc
/*-----------------------------------------------------------*/

/*
 * Unlike other ports pxPortInitialiseStack() is written in assembly code as it
 * needs access to the portasmADDITIONAL_CONTEXT_SIZE constant.  The prototype
 * for the function is as per the other ports:
 * StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
 *
 * As per the standard RISC-V ABI pxTopcOfStack is passed in in a0, pxCode in
 * a1, and pvParameters in a2.  The new top of stack is passed out in a0.
 *
 * RISC-V maps registers to ABI names as follows (X1 to X31 integer registers
 * for the 'I' profile, X1 to X15 for the 'E' profile, currently I assumed).
 *
 * Register		ABI Name	Description						Saver
 * x0			zero		Hard-wired zero					-
 * x1			ra			Return address					Caller
 * x2			sp			Stack pointer					Callee
 * x3			gp			Global pointer					-
 * x4			tp			Thread pointer					-
 * x5-7			t0-2		Temporaries						Caller
 * x8			s0/fp		Saved register/Frame pointer	Callee
 * x9			s1			Saved register					Callee
 * x10-11		a0-1		Function Arguments/return values Caller
 * x12-17		a2-7		Function arguments				Caller
 * x18-27		s2-11		Saved registers					Callee
 * x28-31		t3-6		Temporaries						Caller
 *
 * The RISC-V context is saved t FreeRTOS tasks in the following stack frame,
 * where the global and thread pointers are currently assumed to be constant so
 * are not saved:
 *
 * mstatus
 * x31
 * x30
 * x29
 * x28
 * x27
 * x26
 * x25
 * x24
 * x23
 * x22
 * x21
 * x20
 * x19
 * x18
 * x17
 * x16
 * x15
 * x14
 * x13
 * x12
 * x11
 * pvParameters
 * x9
 * x8
 * x7
 * x6
 * x5
 * portTASK_RETURN_ADDRESS
 * [chip specific registers go here]
 * pxCode
 */

/*-----------------------------------------------------------*/
