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

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RISC-V RV32 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "core_rv64.h"

/* Standard includes. */
#include "string.h"

#ifdef configCLINT_BASE_ADDRESS
	#warning The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS dirctly in place of configCLINT_BASE_ADDRESS.  See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef configMTIME_BASE_ADDRESS
	#warning configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
#endif

#ifndef configMTIMECMP_BASE_ADDRESS
	#warning configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html
#endif

/* Let the user override the pre-loading of the initial LR with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger. */
#ifdef configTASK_RETURN_ADDRESS
	#define portTASK_RETURN_ADDRESS	configTASK_RETURN_ADDRESS
#else
	#define portTASK_RETURN_ADDRESS	prvTaskExitError
#endif

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
to use a statically allocated array as the interrupt stack.  Alternative leave
configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
linker variable names __freertos_irq_stack_top has the same value as the top
of the stack used by main.  Using the linker script method will repurpose the
stack that was used by main before the scheduler was started for use as the
interrupt stack after the scheduler has started. */
#ifdef configISR_STACK_SIZE_WORDS
	static __attribute__ ((aligned(16))) StackType_t xISRStack[ configISR_STACK_SIZE_WORDS ] = { 0 };
	const StackType_t xISRStackTop = ( StackType_t ) &( xISRStack[ configISR_STACK_SIZE_WORDS & ~portBYTE_ALIGNMENT_MASK ] );

	/* Don't use 0xa5 as the stack fill bytes as that is used by the kernerl for
	the task stacks, and so will legitimately appear in many positions within
	the ISR stack. */
	#define portISR_STACK_FILL_BYTE	0xee
#else
	extern const uint32_t __freertos_irq_stack_top[];
	const StackType_t xISRStackTop = ( StackType_t ) __freertos_irq_stack_top;
#endif

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
void vPortSetupTimerInterrupt( void ) __attribute__(( weak ));

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ullNextTime = 0ULL;
const uint64_t *pullNextTime = &ullNextTime;
const size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( configTICK_RATE_HZ ) ); /* Assumes increment won't go over 32-bits. */
uint32_t const ullMachineTimerCompareRegisterBase = configMTIMECMP_BASE_ADDRESS;
volatile uint64_t * pullMachineTimerCompareRegister = NULL;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 )
	#warning This path not tested, or even compiled yet.

	static const uint8_t ucExpectedStackBytes[] = {
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE };	\

	#define portCHECK_ISR_STACK() configASSERT( ( memcmp( ( void * ) xISRStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) == 0 ) )
#else
	/* Define the function away. */
	#define portCHECK_ISR_STACK()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

#if( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 )

	void vPortSetupTimerInterrupt( void )
	{
		printf("vPortSetupTimerInterruptjslfjlsjfd\n");
	//uint32_t ulCurrentTimeHigh, ulCurrentTimeLow;
	//volatile uint32_t * const pulTimeHigh = ( volatile uint32_t * const ) ( ( configMTIME_BASE_ADDRESS ) + 4UL ); /* 8-byte typer so high 32-bit word is 4 bytes up. */
	//volatile uint32_t * const pulTimeLow = ( volatile uint32_t * const ) ( configMTIME_BASE_ADDRESS );
	volatile uint32_t ulHartId;

		__asm volatile( "csrr %0, mhartid" : "=r"( ulHartId ) );
		pullMachineTimerCompareRegister  = ( volatile uint64_t * ) ( ullMachineTimerCompareRegisterBase + ( ulHartId * sizeof( uint64_t ) ) );
#if 0
		do
		{
			ulCurrentTimeHigh = *pulTimeHigh;
			ulCurrentTimeLow = *pulTimeLow;
		} while( ulCurrentTimeHigh != *pulTimeHigh );
#endif
		//ullNextTime = ( uint64_t ) ulCurrentTimeHigh;
		//ullNextTime <<= 32ULL; /* High 4-byte word is 32-bits up. */
		//ullNextTime |= ( uint64_t ) ulCurrentTimeLow;
		ullNextTime = __get_MTIME();
		ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
		*pullMachineTimerCompareRegister = ullNextTime;

		/* Prepare the time to use after the next tick interrupt. */
		ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
	}

#endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIME_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
portLONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to swtich task after enter critical area, we need know it
 * and implement task switch after exit critical area */
portLONG pendsvflag = 0;


StackType_t *pxPortInitialiseStack( StackType_t * pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    StackType_t *stk  = NULL;
    register int *gp asm("x3");
    uint64_t temp = (uint64_t)pxTopOfStack;
#ifdef CONFIG_KERNEL_RUN_SMODE
    uint64_t status = ((uint64_t)__get_SSTATUS() & (~0x19ff)) | 0x120;
#else
    uint64_t status = ((uint64_t)__get_MSTATUS() & (~0x19ff)) | 0x1880;
#endif

    temp &= 0xFFFFFFFFFFFFFFF8UL;
    stk = (StackType_t *)temp;

    *(--stk)  = (uint64_t)0x3131313131313131L;       /* X31         */
    *(--stk)  = (uint64_t)0x3030303030303030L;       /* X30         */
    *(--stk)  = (uint64_t)0x2929292929292929L;       /* X29         */
    *(--stk)  = (uint64_t)0x2828282828282828L;       /* X28         */
    *(--stk)  = (uint64_t)0x2727272727272727L;       /* X27         */
    *(--stk)  = (uint64_t)0x2626262626262626L;       /* X26         */
    *(--stk)  = (uint64_t)0x2525252525252525L;       /* X25         */
    *(--stk)  = (uint64_t)0x2424242424242424L;       /* X24         */
    *(--stk)  = (uint64_t)0x2323232323232323L;       /* X23         */
    *(--stk)  = (uint64_t)0x2222222222222222L;       /* X22         */
    *(--stk)  = (uint64_t)0x2121212121212121L;       /* X21         */
    *(--stk)  = (uint64_t)0x2020202020202020L;       /* X20         */
    *(--stk)  = (uint64_t)0x1919191919191919L;       /* X19         */
    *(--stk)  = (uint64_t)0x1818181818181818L;       /* X18         */
    *(--stk)  = (uint64_t)0x1717171717171717L;       /* X17         */
    *(--stk)  = (uint64_t)0x1616161616161616L;       /* X16         */
    *(--stk)  = (uint64_t)0x1515151515151515L;       /* X15         */
    *(--stk)  = (uint64_t)0x1414141414141414L;       /* X14         */
    *(--stk)  = (uint64_t)0x1313131313131313L;       /* X13         */
    *(--stk)  = (uint64_t)0x1212121212121212L;       /* X12         */
    *(--stk)  = (uint64_t)0x1111111111111111L;       /* X11         */
    *(--stk)  = (uint64_t)pvParameters;      /* X10         */
    *(--stk)  = (uint64_t)0x0909090909090909L;       /* X9          */
    *(--stk)  = (uint64_t)0x0808080808080808L;       /* X8          */
    *(--stk)  = (uint64_t)0x0707070707070707L;       /* X7          */
    *(--stk)  = (uint64_t)0x0606060606060606L;       /* X6          */
    *(--stk)  = (uint64_t)0x0505050505050505L;       /* X5          */
    *(--stk)  = (uint64_t)0x0404040404040404L;       /* X4          */
    *(--stk)  = (uint64_t)gp;                /* X3          */
    *(--stk)  = (uint64_t)0xFFFFFFFFFFFFFFFEL;       /* X1          */

#if __riscv_flen == 64
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F31         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F30         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F29         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F28         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F27         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F26         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F25         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F24         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F23         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F22         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F21         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F20         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F19         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F18         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F17         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F16         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F15         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F14         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F13         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F12         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F11         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F10         */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F9          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F8          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F7          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F6          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F5          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F4          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F3          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F2          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F1          */
    *(--stk)  = (uint64_t)0x1234567812345678L;       /* F0          */
#endif
#if CONFIG_CPU_C908V == 1
#if CONFIG_RISCV_VECTOR_LEN == 128
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v31         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v30         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v29         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v28         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v27         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v26         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v25         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v24         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v23         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v22         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v21         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v20         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v19         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v18         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v17         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v16         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v15         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v14         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v13         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v12         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v11         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v10         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v9          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v8          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v7          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v6          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v5          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v4          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v3          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v2          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v1          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;       /* v0          */
#endif
#if CONFIG_RISCV_VECTOR_LEN == 256
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v31         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v30         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v29         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v28         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v27         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v26         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v25         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v24         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v23         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v22         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v21         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v20         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v19         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v18         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v17         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v16         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v15         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v14         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v13         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v12         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v11         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v10         */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v9          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v8          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v7          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v6          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v5          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v4          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v3          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v2          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v1          */
    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;    *(--stk)  = (uint64_t)0x1234567812345678L;   *(--stk)  = (uint64_t)0x1234567812345678L;   /* v0          */
#endif
#endif
    *(--stk)  = (uint64_t)status;       /* mstatus     */
    *(--stk)  = (uint64_t)pxCode;                    /* Entry Point */

    return stk;
}

#ifdef CONFIG_KERNEL_RUN_SMODE
BaseType_t xPortStartScheduler( void )
{
	ulCriticalNesting = 0UL;
extern void xPortStartFirstTask( void );

	#if( configASSERT_DEFINED == 1 )
	{
		volatile uint32_t mtvec = 0;

		/* Check the least significant two bits of mtvec are 00 - indicating
		single vector mode. */
		__asm volatile( "csrr %0, stvec" : "=r"( mtvec ) );
		configASSERT( ( mtvec & 0x03UL ) == 0 );

		/* Check alignment of the interrupt stack - which is the same as the
		stack that was being used by main() prior to the scheduler being
		started. */
		configASSERT( ( xISRStackTop & portBYTE_ALIGNMENT_MASK ) == 0 );

		#ifdef configISR_STACK_SIZE_WORDS
		{
			memset( ( void * ) xISRStack, portISR_STACK_FILL_BYTE, sizeof( xISRStack ) );
		}
		#endif	 /* configISR_STACK_SIZE_WORDS */
	}
	#endif /* configASSERT_DEFINED */

	/* If there is a CLINT then it is ok to use the default implementation
	in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
	configure whichever clock is to be used to generate the tick interrupt. */
	//vPortSetupTimerInterrupt();

	#if( ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) )
	{
		/* Enable mtime and external interrupts.  1<<7 for timer interrupt, 1<<11
		for external interrupt.  _RB_ What happens here when mtime is not present as
		with pulpino? */
		__asm volatile( "csrs sie, %0" :: "r"(0x220) );
	}
	#else
	{
		/* Enable external interrupts. */
		__asm volatile( "csrs sie, %0" :: "r"(0X200) );
	}
	#endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

	xPortStartFirstTask();

	/* Should not get here as after calling xPortStartFirstTask() only tasks
	should be executing. */
	return pdFAIL;
}
#else
BaseType_t xPortStartScheduler( void )
{
	ulCriticalNesting = 0UL;
extern void xPortStartFirstTask( void );

	#if( configASSERT_DEFINED == 1 )
	{
		volatile uint32_t mtvec = 0;

		/* Check the least significant two bits of mtvec are 00 - indicating
		single vector mode. */
		__asm volatile( "csrr %0, mtvec" : "=r"( mtvec ) );
		configASSERT( ( mtvec & 0x03UL ) == 0 );

		/* Check alignment of the interrupt stack - which is the same as the
		stack that was being used by main() prior to the scheduler being
		started. */
		configASSERT( ( xISRStackTop & portBYTE_ALIGNMENT_MASK ) == 0 );

		#ifdef configISR_STACK_SIZE_WORDS
		{
			memset( ( void * ) xISRStack, portISR_STACK_FILL_BYTE, sizeof( xISRStack ) );
		}
		#endif	 /* configISR_STACK_SIZE_WORDS */
	}
	#endif /* configASSERT_DEFINED */

	/* If there is a CLINT then it is ok to use the default implementation
	in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
	configure whichever clock is to be used to generate the tick interrupt. */
	//vPortSetupTimerInterrupt();

	#if( ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) )
	{
		/* Enable mtime and external interrupts.  1<<7 for timer interrupt, 1<<11
		for external interrupt.  _RB_ What happens here when mtime is not present as
		with pulpino? */
		__asm volatile( "csrs mie, %0" :: "r"(0x880) );
	}
	#else
	{
		/* Enable external interrupts. */
		__asm volatile( "csrs mie, %0" :: "r"(0x800) );
	}
	#endif /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

	xPortStartFirstTask();

	/* Should not get here as after calling xPortStartFirstTask() only tasks
	should be executing. */
	return pdFAIL;
}
#endif
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* Not implemented. */
	for( ;; );
}

void vTaskEnterCritical( void )
{
    portDISABLE_INTERRUPTS();
    ulCriticalNesting ++;
}

void vTaskExitCritical( void )
{
    if (ulCriticalNesting == 0) {
        while(1);
    }

    ulCriticalNesting --;
    if (ulCriticalNesting == 0)
    {
        portENABLE_INTERRUPTS();

        if (pendsvflag)
        {
            pendsvflag = 0;
            portYIELD();
        }
    }
}

#if configUSE_PREEMPTION == 0
void xPortSysTickHandler( void )
{
    portLONG ulDummy;

    ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
    xTaskIncrementTick();
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulDummy );
}

#else
void xPortSysTickHandler( void )
{
    portLONG ulDummy;

    ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        if (xTaskIncrementTick() != pdFALSE)
        {
            portYIELD_FROM_ISR(pdTRUE);
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulDummy );
}
#endif

void vPortYieldHandler( void )
{
    uint32_t ulSavedInterruptMask;

    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();

    vTaskSwitchContext();

    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}

__attribute__((weak)) void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
    for(;;);
}

__attribute__((weak)) void vApplicationMallocFailedHook( void )
{
    for(;;);
}




