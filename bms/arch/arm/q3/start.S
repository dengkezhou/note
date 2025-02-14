
/* InfoTM iMAPx5360 start up code
    warits.wang Thu Sep 1, 2011
    ivan.zhuang Tue July 22, 2014*/
#include <asm_macros.S>
// # include <config.h>
// # include CONFIG_IMAPX_REGS_FILE
.globl _start
_start:     
#if 0

    /*set little endian
	mrs	x0, sctlr_el3
	bic	x0, x0, #(1<<25)
	msr	sctlr_el3, x0
	isb*/

    /*enable smp in midr_el1*/
    mrs x0, midr_el1
    lsr x0, x0, #0x4 /*part num ,implemention defined*/
    and x0, x0, #0xfff 
    cmp x0, #0xd07 /*a57*/
    b.eq    _set_smp_en
    cmp x0, #0xd03 /*a53*/
    b.ne    _set_smp_end
_set_smp_en:
    mrs x0, S3_1_C15_C2_1
    orr x0, x0, #(1<<6) /*enable smp bit in cpuectlr_el1*/
    msr S3_1_C15_C2_1, x0
    isb
_set_smp_end:  
#endif
    /*setup exception vector base address*/
    # ldr x0, =vector_base
    msr vbar_el3, x0
    
    /*set lower level to non-secure*/
    mrs x0, scr_el3
    orr x0, x0, #0x1 
    msr scr_el3, x0
    
    /*Disable trap to el3 when access cpacr_el1 from el1 or  cptr_el2 from el2,   
       still maybe trapped at el2. Disable trap to el3 when access trace functionality 
       from any excpt lvl  ,  still maybe trapped at el2 or el1. Disable trap to el3 when
       access registers associated with Float point and Adv SIMD , still maybe traoped 
       at el2 or el1*/
	msr	cptr_el3, xzr

    /*enable i cache*/
	mrs	x0, sctlr_el3
	orr	x0, x0, #(1<<12)
	msr	sctlr_el3, x0
	isb
	
	/* the mask ROM code should have PLL and others stable*/
	bl core_init_crit

	mrs	x0, mpidr_el1
    and x0, x0, #(0xff|(0xff<<8)) /*core id and cluster id*/
    cmp x0, #0
    b.ne boot_slave              /*boot slave , slave cpu will  hold cold until active by kernel*/

	/*initial stack before call c routine*/
	ldr x0, =__lds_stack_el3
	mov sp, x0

    /*master core initial and start  _main*/
    /*initial bss*/
#ifdef CONFIG_COMPILE_RTL
    /*needn't to be initialized when rtl simulation because of rtl module's behavior*/
#else
	ldr	x0, =__bss_start
	ldr	x1, =__bss_size
	# bl	zeromem16
#endif
#if 0
	/*No necessary  when data is allocated in ram*/
    /*initial data*/
	ldr	x0, =__data_start
	ldr	x1, =__data_load
	ldr	x2, =__data_len
	bl	memcpy16    
#endif 	
	bl main

panic:
	b  panic

core_init_crit:
	/*reset status mmu disabled, i/d cached disabled, 
	should invalid tlb or cache now?*/
	#if 0
	/*wait for confirm ,wdt initial*/
	mov x1, #0
	ldr w1, =0 #TIMER_WATCHDOG_ADDR
	ldr w0, =0x12345678
	str w0, [x1, #0x34]
	ldr w0, =0x87654321
	str w0, [x1, #0x34]
	#endif
	ret	

boot_slave:
	/*switch slave cpu to el2 than switch to el1*/
    # bl armv8_switch_to_el2   
    # bl armv8_switch_to_el1
	# bl platform_get_core_pos /*get core id, x0=core id*/

	/*cold_hold*/
	/*hold current core, w0 is reserved for core index*/
    # ldr x3,=RTC_INFO0
    ldr w1, [x3]
    mov w2, #0x3b
	cmp w1, w2
	# bne low_power

	/*load alternate entry*/
    mov x1, #0
	ldr w1, [x3, #0xc]
	lsl w2, w1, #8
	ldr w1, [x3, #0x8]
	orr w2, w2, w1
	lsl w2, w2, #8
	ldr w1, [x3, #0x4]
	orr w2, w2, w1
	lsl w1, w2, #8

	lsl w2, w0, #2
	add w1, w2, w1
	mov w2, #1
	str w2, [x1]

	/*have some doubt about sy? wait for confirm*/
	dsb sy
	
	mov x0, #0
hold_l:
	ldr w0, [x1]
	cmp w0, #1
	beq hold_l
	
	/*jump to the re-directed address*/
	br x0

low_power:
	wfi	        /* put core into WFI mode*/
	b .			/* never reach    */

