/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <arch.h>


	.macro	func_prologue
	stp	x29, x30, [sp, #-0x10]!
	mov	x29,sp
	.endm

	.macro	func_epilogue
	ldp	x29, x30, [sp], #0x10
	.endm


	.macro	dcache_line_size  reg, tmp
	mrs	\tmp, ctr_el0
	ubfx	\tmp, \tmp, #16, #4
	mov	\reg, #4
	lsl	\reg, \reg, \tmp
	.endm


	.macro	icache_line_size  reg, tmp
	mrs	\tmp, ctr_el0
	and	\tmp, \tmp, #0xf
	mov	\reg, #4
	lsl	\reg, \reg, \tmp
	.endm


	.macro	smc_check  label
	mrs	x0, esr_el3
	ubfx	x0, x0, #ESR_EC_SHIFT, #ESR_EC_LENGTH
	cmp	x0, #EC_AARCH64_SMC
	b.ne	$label
	.endm


	/*
	 * This macro verifies that the a given vector doesn't exceed the
	 * architectural limit of 32 instructions. This is meant to be placed
	 * immedately after the last instruction in the vector. It takes the
	 * vector entry as the parameter
	 */
	.macro check_vector_size since
	  .if (. - \since) > (32 * 4)
	    .error "Vector exceeds 32 instructions"
	  .endif
	.endm

	/*
	 * This macro is used to create a function label and place the
	 * code into a separate text section based on the function name
	 * to enable elimination of unused code during linking
	 */
	.macro func _name
	.section .text.\_name, "ax"
	.type \_name, %function
	\_name:
	.endm

	/*
	 * This macro declares an array of 1 or more stacks, properly
	 * aligned and in the requested section
	 */
#define STACK_ALIGN	6

	.macro declare_stack _name, _section, _size, _count
	.if ((\_size & ((1 << STACK_ALIGN) - 1)) <> 0)
	  .error "Stack size not correctly aligned"
	.endif
	.section    \_section, "aw", %nobits
	.align STACK_ALIGN
	\_name:
	.space ((\_count) * (\_size)), 0
	.endm

	/*
	 * This macro calculates the base address of an MP stack using the
	 * platform_get_core_pos() index, the name of the stack storage and
	 * the size of each stack
	 * In: X0 = MPIDR of CPU whose stack is wanted
	 * Out: X0 = physical address of stack base
	 * Clobber: X30, X1, X2
	 */
	.macro get_mp_stack _name, _size
	bl  platform_get_core_pos
	ldr x2, =(\_name + \_size)
	mov x1, #\_size
	madd x0, x0, x1, x2
	.endm

	/*
	 * This macro calculates the base address of an MP stack using the
	 * platform_get_core_pos() index, the name of the stack storage and
	 * the size of each stack
	 * In: X0 = MPIDR of CPU whose stack is wanted
	 * Out: X0 = physical address of stack base
	 * Clobber: X30, X1, X2
	 */
	.macro get_mp_stack_fixed  _name,_size
	bl  platform_get_core_pos
	ldr x1, =(\_name)
	mov x2, #\_size
	add x2, x1, x2
	mov x1, #\_size
	madd x0, x0, x1, x2
	.endm

	/*
	 * This macro calculates the base address of a UP stack using the
	 * name of the stack storage and the size of the stack
	 * Out: X0 = physical address of stack base
	 */
	.macro get_up_stack _name, _size
	ldr x0, =(\_name + \_size)
	.endm


/*
 * Stack pushing/popping (register pairs only). Equivalent to store decrement
 * before, load increment after.
 */
	.macro	push, xreg1, xreg2
	stp	\xreg1, \xreg2, [sp, #-16]!
	.endm

	.macro	pop, xreg1, xreg2
	ldp	\xreg1, \xreg2, [sp], #16
	.endm

lr 	.req x30
/*
 * Enable and disable interrupts.
 */
	.macro	disable_irq
	msr	daifset, #2
	.endm

	.macro	enable_irq
	msr	daifclr, #2
	.endm

	.macro  kernel_entry, el, regsize = 64                                      
    sub sp, sp, #S_FRAME_SIZE - S_LR    // room for LR, SP, SPSR, ELR           
    .if \regsize == 32                                                          
    mov w0, w0              // zero upper 32 bits of x0                         
    .endif                                                                      
    push    x28, x29                                                            
    push    x26, x27                                                            
    push    x24, x25                                                            
    push    x22, x23                                                            
    push    x20, x21                                                            
    push    x18, x19                                                            
    push    x16, x17                                                            
    push    x14, x15                                                            
    push    x12, x13                                                            
    push    x10, x11                                                            
    push    x8, x9                                                              
    push    x6, x7                                                              
    push    x4, x5                                                              
    push    x2, x3                                                              
    push    x0, x1                                                              
    .if \el == 0                                                                
    mrs x21, sp_el0                                                             
    .else                                                                       
    add x21, sp, #S_FRAME_SIZE                                                  
    .endif                                                                      
    mrs x22, elr_el1                                                            
    mrs x23, spsr_el1                                                           
    stp lr, x21, [sp, #S_LR]                                                    
    stp x22, x23, [sp, #S_PC]   

 /*                                                                          
     * Set syscallno to -1 by default (overridden later if real syscall).       
     */                                                                         
    .if \el == 0                                                                
    mvn x21, xzr                                                                
    str x21, [sp, #S_SYSCALLNO]                                                 
    .endif                                                                      
                                                                                
    /*                                                                          
     * Registers that may be useful after this macro is invoked:                
     *                                                                          
     * x21 - aborted SP                                                         
     * x22 - aborted PC                                                         
     * x23 - aborted PSTATE                                                     
    */                                                                          
    .endm                                                                       
                                                                                
    .macro  kernel_exit, el, ret = 0                                            
    ldp x21, x22, [sp, #S_PC]       // load ELR, SPSR                           
    .if \el == 0                                                                
    ldr x23, [sp, #S_SP]        // load return stack pointer                    
    .endif                                                                      
    .if \ret                                                                    
    ldr x1, [sp, #S_X1]         // preserve x0 (syscall return)                 
    add sp, sp, S_X2                                                            
    .else                                                                       
    pop x0, x1                                                                  
    .endif                                                                      
    pop x2, x3              // load the rest of the registers                   
    pop x4, x5                                                                  
    pop x6, x7                                                                  
    pop x8, x9                                                                  
    msr elr_el1, x21            // set up the return data                       
    msr spsr_el1, x22   

   .if \el == 0                                                                
    msr sp_el0, x23                                                             
    .endif                                                                      
    pop x10, x11                                                                
    pop x12, x13                                                                
    pop x14, x15                                                                
    pop x16, x17                                                                
    pop x18, x19                                                                
    pop x20, x21                                                                
    pop x22, x23                                                                
    pop x24, x25                                                                
    pop x26, x27                                                                
    pop x28, x29                                                                
    ldr lr, [sp], #S_FRAME_SIZE - S_LR  // load LR and restore SP               
    eret                    // return to kernel                                 
    .endm                                                                       

	.macro  el3_entry, el, regsize = 64                                      
    sub sp, sp, #S_FRAME_SIZE - S_LR    // room for LR, SP, SPSR, ELR           
    .if \regsize == 32                                                          
    mov w0, w0              // zero upper 32 bits of x0                         
    .endif                                                                      
    push    x28, x29                                                            
    push    x26, x27                                                            
    push    x24, x25                                                            
    push    x22, x23                                                            
    push    x20, x21                                                            
    push    x18, x19                                                            
    push    x16, x17                                                            
    push    x14, x15                                                            
    push    x12, x13                                                            
    push    x10, x11                                                            
    push    x8, x9                                                              
    push    x6, x7                                                              
    push    x4, x5                                                              
    push    x2, x3                                                              
    push    x0, x1                                                              
    .if \el == 0                                                                
    mrs x21, sp_el0                                                             
    .else                                                                       
    add x21, sp, #S_FRAME_SIZE                                                  
    .endif                                                                      
    mrs x22, elr_el3                                                            
    mrs x23, spsr_el3                                                           
    stp lr, x21, [sp, #S_LR]                                                    
    stp x22, x23, [sp, #S_PC]   

 	/*                                                                          
     * Set syscallno to -1 by default (overridden later if real syscall).       
     */                                                                         
    .if \el == 0                                                                
    mvn x21, xzr                                                                
    str x21, [sp, #S_SYSCALLNO]                                                 
    .endif                                                                      
                                                                                
    /*                                                                          
     * Registers that may be useful after this macro is invoked:                
     *                                                                          
     * x21 - aborted SP                                                         
     * x22 - aborted PC                                                         
     * x23 - aborted PSTATE                                                     
    */                                                                          
    .endm                                                                       
                                                                                
    .macro  el3_exit, el, ret = 0                                            
    ldp x21, x22, [sp, #S_PC]       // load ELR, SPSR                           
    .if \el == 0                                                                
    ldr x23, [sp, #S_SP]        // load return stack pointer                    
    .endif                                                                      
    .if \ret                                                                    
    ldr x1, [sp, #S_X1]         // preserve x0 (syscall return)                 
    add sp, sp, S_X2                                                            
    .else                                                                       
    pop x0, x1                                                                  
    .endif                                                                      
    pop x2, x3              // load the rest of the registers                   
    pop x4, x5                                                                  
    pop x6, x7                                                                  
    pop x8, x9                                                                  
    msr elr_el3, x21            // set up the return data                       
    msr spsr_el3, x22   

   .if \el == 0                                                                
    msr sp_el0, x23                                                             
    .endif                                                                      
    pop x10, x11                                                                
    pop x12, x13                                                                
    pop x14, x15                                                                
    pop x16, x17                                                                
    pop x18, x19                                                                
    pop x20, x21                                                                
    pop x22, x23                                                                
    pop x24, x25                                                                
    pop x26, x27                                                                
    pop x28, x29                                                                
    ldr lr, [sp], #S_FRAME_SIZE - S_LR  // load LR and restore SP               
    eret                    // return to kernel                                 
    .endm                                                                       

	/*
 	* Branch according to exception level
 	*/
	.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
	.endm
