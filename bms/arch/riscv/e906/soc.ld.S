OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH("riscv")

#include <generated/autoconf.h>

MEMORY
{
	/* brom 64KB */
	SRAM_DATA		: ORIGIN = 0x0c000000, LENGTH = 0x20000 /* 128KB */
	/* IROM 2MB */
#ifdef CONFIG_TB_RUN_IRAM
	MEM_TXT     : ORIGIN = 0x14000000, LENGTH = 0xa0000    /* 640KB */
	MEM_MALLOC  : ORIGIN = 0x140a0000, LENGTH = 0x60000    /* 384KB */
#else
	MEM_TXT   	: ORIGIN = 0x40000000, LENGTH = 0x80000    /* 512KB */
	MEM_DAT     : ORIGIN = 0x40080000, LENGTH = 0xf80000   /* 16MB-512KB */
	#ifdef CONFIG_CACHE_LITE
		MEM_MALLOC	: ORIGIN = 0x60000000, LENGTH = 0x8000000  /*128MB */
	#else
		MEM_MALLOC  : ORIGIN = 0x41000000, LENGTH = 0x8000000  /*128MB */
	#endif
#endif
}

REGION_ALIAS("REGION_TEXT",    MEM_TXT);
REGION_ALIAS("REGION_RODATA",  MEM_TXT);
#ifdef CONFIG_TB_RUN_IRAM
REGION_ALIAS("REGION_DATA",    MEM_TXT);
REGION_ALIAS("REGION_BSS",     MEM_TXT);
#else
REGION_ALIAS("REGION_DATA",    MEM_DAT);
REGION_ALIAS("REGION_BSS",     MEM_DAT);
#endif

ENTRY(Reset_Handler)
SECTIONS
{

	/*
	 * memory base(total 4K):
	 *    print memory: [0xf000, 0xf100] total: 256Bytes
	 *    rtl communication memory: [0xf100, 0xf200] total 256Bytes
	 *    rtl case memory: [0xf200, 0xf400] total: 512Bytes
	 *    rtl data memory: [0xf400, 0x10000] total: 3072Bytes
	 */
#ifdef CONFIG_COMPILE_RTL
	__lds_print = 0xd2f08800;
	__lds_print_size = 0x1;
#else
	__lds_print = ORIGIN(SRAM_DATA);
	__lds_print_size = 0x100;
#endif
	__lds_indicate = ORIGIN(SRAM_DATA) + 0x100;
	__lds_rtl_case = ORIGIN(SRAM_DATA) + 0x200;
	__lds_rtl_data = ORIGIN(SRAM_DATA) + 0x400;

	__lds_malloc_start = ORIGIN(MEM_MALLOC);
	__lds_malloc_end   = ORIGIN(MEM_MALLOC) + LENGTH(MEM_MALLOC);
	
	__lds_soc_base = ORIGIN(MEM_TXT);
	__lds_template = ORIGIN(MEM_TXT) + LENGTH(MEM_TXT) - 8;

	.text : {
		. = ALIGN(0x4) ;
		KEEP(*startup.o(*.text*))
			*(.text*)
	} > REGION_TEXT
	. = ALIGN(4);

	.rodata : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	} > REGION_RODATA

	.init_f : {
		__init_f_start = .;
		*(.init_f0)
			*(.init_f1)
			*(.init_f2)
	} > REGION_RODATA
	. = ALIGN(4);
	__init_f_end = .;
	
	__data_load__ = LOADADDR(.data);

	.data : {
		. = ALIGN(0x4) ;
		__data_start__ = . ;
		*(.data*)
		*(.sdata*)
			__global_pointer$ = .;
		__data_end__ = .;
		. = ALIGN(0x4) ;
	} > REGION_DATA

	.bss (NOLOAD): {
		. = ALIGN(0x4) ;
		__bss_start__ = .;
		*(.bss*)
		*(.sbss*)
			*(COMMON)
			__bss_end__ = .;
		. = ALIGN(0x4);
	} > REGION_BSS
}
