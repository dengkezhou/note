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
 * RISC-V ISA), and code that tailors the port to a specific RISC-V chip:
 *
 * + FreeRTOS\Source\portable\GCC\RISC-V-RV32\portASM.S contains the code that
 *   is common to all currently supported RISC-V chips.  There is only one
 *   portASM.S file because the same file is built for all RISC-V target chips.
 *
 * + Header files called freertos_risc_v_chip_specific_extensions.h contain the
 *   code that tailors the FreeRTOS kernel's RISC-V port to a specific RISC-V
 *   chip.  There are multiple freertos_risc_v_chip_specific_extensions.h files
 *   as there are multiple RISC-V chip implementations.
 *
 * !!!NOTE!!!
 * TAKE CARE TO INCLUDE THE CORRECT freertos_risc_v_chip_specific_extensions.h
 * HEADER FILE FOR THE CHIP IN USE.  This is done using the assembler's (not the
 * compiler's!) include path.  For example, if the chip in use includes a core
 * local interrupter (CLINT) and does not include any chip specific register
 * extensions then add the path below to the assembler's include path:
 * FreeRTOS\Source\portable\GCC\RISC-V-RV32\chip_specific_extensions\RV32I_CLINT_no_extensions
 *
 */

//#include <csi_config.h>
#ifndef __FREERTOS_RISC_V_EXTENSIONS_H__
#define __FREERTOS_RISC_V_EXTENSIONS_H__

#define portasmHAS_SIFIVE_CLINT 1
#define portasmHAS_MTIME 1
#define portasmADDITIONAL_CONTEXT_SIZE 0 /* Must be even number on 32-bit cores. */
#define portasmHANDLE_INTERRUPT Default_IRQHandler

.macro portasmSAVE_ADDITIONAL_REGISTERS
    /* save float registers */
#ifdef CONFIG_KERNEL_RUN_SMODE
    csrr    t0, sstatus
    li      t1, (0x1 << 13 | 0x1 << 9)
    li      t2, -1
    xor     t1, t1, t2
    and     t2, t1, t0
    csrw    sstatus, t2
#else
    csrr    t0, mstatus
    li      t1, (0x1 << 13 | 0x1 << 9)
    li      t2, -1
    xor     t1, t1, t2
    and     t2, t1, t0
    csrw    mstatus, t2
#endif
#if __riscv_flen == 64
    addi    sp, sp, -(128+128)

    li      t1, 3
    srli    t2, t0, 0xd
    and     t2, t2, t1
    bne     t2, t1, _jump_float_save

    fsd     f31, (0   * 2)(sp)
    fsd     f30, (4   * 2)(sp)
    fsd     f29, (8   * 2)(sp)
    fsd     f28, (12  * 2)(sp)
    fsd     f27, (16  * 2)(sp)
    fsd     f26, (20  * 2)(sp)
    fsd     f25, (24  * 2)(sp)
    fsd     f24, (28  * 2)(sp)
    fsd     f23, (32  * 2)(sp)
    fsd     f22, (36  * 2)(sp)
    fsd     f21, (40  * 2)(sp)
    fsd     f20, (44  * 2)(sp)
    fsd     f19, (48  * 2)(sp)
    fsd     f18, (52  * 2)(sp)
    fsd     f17, (56  * 2)(sp)
    fsd     f16, (60  * 2)(sp)
    fsd     f15, (64  * 2)(sp)
    fsd     f14, (68  * 2)(sp)
    fsd     f13, (72  * 2)(sp)
    fsd     f12, (76  * 2)(sp)
    fsd     f11, (80  * 2)(sp)
    fsd     f10, (84  * 2)(sp)
    fsd     f9,  (88  * 2)(sp)
    fsd     f8,  (92  * 2)(sp)
    fsd     f7,  (96  * 2)(sp)
    fsd     f6,  (100 * 2)(sp)
    fsd     f5,  (104 * 2)(sp)
    fsd     f4,  (108 * 2)(sp)
    fsd     f3,  (112 * 2)(sp)
    fsd     f2,  (116 * 2)(sp)
    fsd     f1,  (120 * 2)(sp)
    fsd     f0,  (124 * 2)(sp)
_jump_float_save:
#endif
#if CONFIG_CPU_C908V == 1
#if CONFIG_RISCV_VECTOR_LEN == 128
    li      t1, 3
    srli    t2, t0, 0x9
    and     t2, t2, t1
    addi    sp, sp, -(128*4)
    bne     t2, t1, _jump_vector_save
    addi    sp, sp, (128*3)
    vs8r.v  v24, (sp)
    addi    sp, sp, -128
    vs8r.v  v16, (sp)
    addi    sp, sp, -128
    vs8r.v  v8, (sp)
    addi    sp, sp, -128
    vs8r.v  v0, (sp)

_jump_vector_save:
#endif
#if CONFIG_RISCV_VECTOR_LEN == 256
    li      t1, 3
    srli    t2, t0, 0x9
    and     t2, t2, t1
    addi    sp, sp, -(256*4)
    bne     t2, t1, _jump_vector_save
    addi    sp, sp, (256*3)
    vs8r.v  v24, (sp)
    addi    sp, sp, -256
    vs8r.v  v16, (sp)
    addi    sp, sp, -256
    vs8r.v  v8, (sp)
    addi    sp, sp, -256
    vs8r.v  v0, (sp)

_jump_vector_save:
#endif
#endif

#if CONFIG_CPU_C920V == 1
    /* save vector registers */
#if CONFIG_RISCV_VECTOR_LEN == 128
    li      t1, 3
    srli    t2, t0, 0x9
    and     t2, t2, t1
    bne     t2, t1, _jump_vector_save

    addi    sp, sp, -16
    vs1r.v  v31, (sp)
    addi    sp, sp, -16
    vs1r.v  v30, (sp)
    addi    sp, sp, -16
    vs1r.v  v29, (sp)
    addi    sp, sp, -16
    vs1r.v  v28, (sp)
    addi    sp, sp, -16
    vs1r.v  v27, (sp)
    addi    sp, sp, -16
    vs1r.v  v26, (sp)
    addi    sp, sp, -16
    vs1r.v  v25, (sp)
    addi    sp, sp, -16
    vs1r.v  v24, (sp)
    addi    sp, sp, -16
    vs1r.v  v23, (sp)
    addi    sp, sp, -16
    vs1r.v  v22, (sp)
    addi    sp, sp, -16
    vs1r.v  v21, (sp)
    addi    sp, sp, -16
    vs1r.v  v20, (sp)
    addi    sp, sp, -16
    vs1r.v  v19, (sp)
    addi    sp, sp, -16
    vs1r.v  v18, (sp)
    addi    sp, sp, -16
    vs1r.v  v17, (sp)
    addi    sp, sp, -16
    vs1r.v  v16, (sp)
    addi    sp, sp, -16
    vs1r.v  v15, (sp)
    addi    sp, sp, -16
    vs1r.v  v14, (sp)
    addi    sp, sp, -16
    vs1r.v  v13, (sp)
    addi    sp, sp, -16
    vs1r.v  v12, (sp)
    addi    sp, sp, -16
    vs1r.v  v11, (sp)
    addi    sp, sp, -16
    vs1r.v  v10, (sp)
    addi    sp, sp, -16
    vs1r.v  v9,  (sp)
    addi    sp, sp, -16
    vs1r.v  v8,  (sp)
    addi    sp, sp, -16
    vs1r.v  v7,  (sp)
    addi    sp, sp, -16
    vs1r.v  v6,  (sp)
    addi    sp, sp, -16
    vs1r.v  v5,  (sp)
    addi    sp, sp, -16
    vs1r.v  v4,  (sp)
    addi    sp, sp, -16
    vs1r.v  v3,  (sp)
    addi    sp, sp, -16
    vs1r.v  v2,  (sp)
    addi    sp, sp, -16
    vs1r.v  v1,  (sp)
    addi    sp, sp, -16
    vs1r.v  v0,  (sp)

_jump_vector_save:
#endif
#if CONFIG_RISCV_VECTOR_LEN == 256
    li      t1, 3
    srli    t2, t0, 0x9
    and     t2, t2, t1
    bne     t2, t1, _jump_vector_save

    addi    sp, sp, -32
    vs1r.v  v31, (sp)
    addi    sp, sp, -32
    vs1r.v  v30, (sp)
    addi    sp, sp, -32
    vs1r.v  v29, (sp)
    addi    sp, sp, -32
    vs1r.v  v28, (sp)
    addi    sp, sp, -32
    vs1r.v  v27, (sp)
    addi    sp, sp, -32
    vs1r.v  v26, (sp)
    addi    sp, sp, -32
    vs1r.v  v25, (sp)
    addi    sp, sp, -32
    vs1r.v  v24, (sp)
    addi    sp, sp, -32
    vs1r.v  v23, (sp)
    addi    sp, sp, -32
    vs1r.v  v22, (sp)
    addi    sp, sp, -32
    vs1r.v  v21, (sp)
    addi    sp, sp, -32
    vs1r.v  v20, (sp)
    addi    sp, sp, -32
    vs1r.v  v19, (sp)
    addi    sp, sp, -32
    vs1r.v  v18, (sp)
    addi    sp, sp, -32
    vs1r.v  v17, (sp)
    addi    sp, sp, -32
    vs1r.v  v16, (sp)
    addi    sp, sp, -32
    vs1r.v  v15, (sp)
    addi    sp, sp, -32
    vs1r.v  v14, (sp)
    addi    sp, sp, -32
    vs1r.v  v13, (sp)
    addi    sp, sp, -32
    vs1r.v  v12, (sp)
    addi    sp, sp, -32
    vs1r.v  v11, (sp)
    addi    sp, sp, -32
    vs1r.v  v10, (sp)
    addi    sp, sp, -32
    vs1r.v  v9,  (sp)
    addi    sp, sp, -32
    vs1r.v  v8,  (sp)
    addi    sp, sp, -32
    vs1r.v  v7,  (sp)
    addi    sp, sp, -32
    vs1r.v  v6,  (sp)
    addi    sp, sp, -32
    vs1r.v  v5,  (sp)
    addi    sp, sp, -32
    vs1r.v  v4,  (sp)
    addi    sp, sp, -32
    vs1r.v  v3,  (sp)
    addi    sp, sp, -32
    vs1r.v  v2,  (sp)
    addi    sp, sp, -32
    vs1r.v  v1,  (sp)
    addi    sp, sp, -32
    vs1r.v  v0,  (sp)

_jump_vector_save:
#endif
#endif
    .endm

.macro portasmRESTORE_ADDITIONAL_REGISTERS
    /* restore float registers */
#if CONFIG_CPU_C920V == 1
#if CONFIG_RISCV_VECTOR_LEN == 128
    vl1r.v  v31,(sp)
    addi    sp, sp, 16
    vl1r.v  v30,(sp)
    addi    sp, sp, 16
    vl1r.v  v29,(sp)
    addi    sp, sp, 16
    vl1r.v  v28,(sp)
    addi    sp, sp, 16
    vl1r.v  v27,(sp)
    addi    sp, sp, 16
    vl1r.v  v26,(sp)
    addi    sp, sp, 16
    vl1r.v  v25,(sp)
    addi    sp, sp, 16
    vl1r.v  v24,(sp)
    addi    sp, sp, 16
    vl1r.v  v23,(sp)
    addi    sp, sp, 16
    vl1r.v  v22,(sp)
    addi    sp, sp, 16
    vl1r.v  v21,(sp)
    addi    sp, sp, 16
    vl1r.v  v20,(sp)
    addi    sp, sp, 16
    vl1r.v  v19,(sp)
    addi    sp, sp, 16
    vl1r.v  v18,(sp)
    addi    sp, sp, 16
    vl1r.v  v17,(sp)
    addi    sp, sp, 16
    vl1r.v  v16,(sp)
    addi    sp, sp, 16
    vl1r.v  v15,(sp)
    addi    sp, sp, 16
    vl1r.v  v14,(sp)
    addi    sp, sp, 16
    vl1r.v  v13,(sp)
    addi    sp, sp, 16
    vl1r.v  v12,(sp)
    addi    sp, sp, 16
    vl1r.v  v11,(sp)
    addi    sp, sp, 16
    vl1r.v  v10,(sp)
    addi    sp, sp, 16
    vl1r.v  v9, (sp)
    addi    sp, sp, 16
    vl1r.v  v8, (sp)
    addi    sp, sp, 16
    vl1r.v  v7, (sp)
    addi    sp, sp, 16
    vl1r.v  v6, (sp)
    addi    sp, sp, 16
    vl1r.v  v5, (sp)
    addi    sp, sp, 16
    vl1r.v  v4, (sp)
    addi    sp, sp, 16
    vl1r.v  v3, (sp)
    addi    sp, sp, 16
    vl1r.v  v2, (sp)
    addi    sp, sp, 16
    vl1r.v  v1, (sp)
    addi    sp, sp, 16
    vl1r.v  v0, (sp)
    addi    sp, sp, 16
#endif
#if CONFIG_RISCV_VECTOR_LEN == 256
    vl1r.v  v31,(sp)
    addi    sp, sp, 32
    vl1r.v  v30,(sp)
    addi    sp, sp, 32
    vl1r.v  v29,(sp)
    addi    sp, sp, 32
    vl1r.v  v28,(sp)
    addi    sp, sp, 32
    vl1r.v  v27,(sp)
    addi    sp, sp, 32
    vl1r.v  v26,(sp)
    addi    sp, sp, 32
    vl1r.v  v25,(sp)
    addi    sp, sp, 32
    vl1r.v  v24,(sp)
    addi    sp, sp, 32
    vl1r.v  v23,(sp)
    addi    sp, sp, 32
    vl1r.v  v22,(sp)
    addi    sp, sp, 32
    vl1r.v  v21,(sp)
    addi    sp, sp, 32
    vl1r.v  v20,(sp)
    addi    sp, sp, 32
    vl1r.v  v19,(sp)
    addi    sp, sp, 32
    vl1r.v  v18,(sp)
    addi    sp, sp, 32
    vl1r.v  v17,(sp)
    addi    sp, sp, 32
    vl1r.v  v16,(sp)
    addi    sp, sp, 32
    vl1r.v  v15,(sp)
    addi    sp, sp, 32
    vl1r.v  v14,(sp)
    addi    sp, sp, 32
    vl1r.v  v13,(sp)
    addi    sp, sp, 32
    vl1r.v  v12,(sp)
    addi    sp, sp, 32
    vl1r.v  v11,(sp)
    addi    sp, sp, 32
    vl1r.v  v10,(sp)
    addi    sp, sp, 32
    vl1r.v  v9, (sp)
    addi    sp, sp, 32
    vl1r.v  v8, (sp)
    addi    sp, sp, 32
    vl1r.v  v7, (sp)
    addi    sp, sp, 32
    vl1r.v  v6, (sp)
    addi    sp, sp, 32
    vl1r.v  v5, (sp)
    addi    sp, sp, 32
    vl1r.v  v4, (sp)
    addi    sp, sp, 32
    vl1r.v  v3, (sp)
    addi    sp, sp, 32
    vl1r.v  v2, (sp)
    addi    sp, sp, 32
    vl1r.v  v1, (sp)
    addi    sp, sp, 32
    vl1r.v  v0, (sp)
    addi    sp, sp, 32
#endif
#endif

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
    fld     f31,( 0 + 0 )(sp)
    fld     f30,( 4 + 4 )(sp)
    fld     f29,( 8 + 8 )(sp)
    fld     f28,( 12+ 12)(sp)
    fld     f27,( 16+ 16)(sp)
    fld     f26,( 20+ 20)(sp)
    fld     f25,( 24+ 24)(sp)
    fld     f24,( 28+ 28)(sp)
    fld     f23,( 32+ 32)(sp)
    fld     f22,( 36+ 36)(sp)
    fld     f21,( 40+ 40)(sp)
    fld     f20,( 44+ 44)(sp)
    fld     f19,( 48+ 48)(sp)
    fld     f18,( 52+ 52)(sp)
    fld     f17,( 56+ 56)(sp)
    fld     f16,( 60+ 60)(sp)
    fld     f15,( 64+ 64)(sp)
    fld     f14,( 68+ 68)(sp)
    fld     f13,( 72+ 72)(sp)
    fld     f12,( 76+ 76)(sp)
    fld     f11,( 80+ 80)(sp)
    fld     f10,( 84+ 84)(sp)
    fld     f9, ( 88+ 88)(sp)
    fld     f8, ( 92+ 92)(sp)
    fld     f7, ( 96+ 96)(sp)
    fld     f6, (100+100)(sp)
    fld     f5, (104+104)(sp)
    fld     f4, (108+108)(sp)
    fld     f3, (112+112)(sp)
    fld     f2, (116+116)(sp)
    fld     f1, (120+120)(sp)
    fld     f0, (124+124)(sp)
    addi    sp, sp, (128+128)
#endif

    .endm

#endif /* __FREERTOS_RISC_V_EXTENSIONS_H__ */
