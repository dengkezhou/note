OUTPUT_FORMAT("elf64-littleriscv")
OUTPUT_ARCH("riscv")

#include <generated/autoconf.h>

MEMORY
{
	/* brom 64KB */
	BROM_TXT    : ORIGIN = 0x00000000, LENGTH = 0x10000
	LD_MALLOC   : ORIGIN = 0x00010000, LENGTH = 0x0f000
	RTL_DATA   : ORIGIN = 0x0c000000, LENGTH = 0x1000
}

REGION_ALIAS("REGION_TEXT",    BROM_TXT);
REGION_ALIAS("REGION_RODATA",  BROM_TXT);
REGION_ALIAS("REGION_DATA",    BROM_TXT);
REGION_ALIAS("REGION_BSS",     BROM_TXT);

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
	__lds_print = 0x3fffff0;
	__lds_print_size = 1;
#else
	__lds_print = ORIGIN(RTL_DATA);
	__lds_print_size = 0x100;
#endif
	__lds_indicate = ORIGIN(RTL_DATA) + 0x100;
	__lds_rtl_case = ORIGIN(RTL_DATA) + 0x200;
	__lds_rtl_data = ORIGIN(RTL_DATA) + 0x400;

	__lds_malloc_start = ORIGIN(LD_MALLOC);
	__lds_malloc_end   = ORIGIN(LD_MALLOC) + LENGTH(LD_MALLOC);

	__lds_soc_base = ORIGIN(BROM_TXT);
	__lds_template = ORIGIN(BROM_TXT) + LENGTH(BROM_TXT) - 8;

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
			__global_pointer$ = .;
		__data_end__ = .;
		. = ALIGN(0x4) ;
	} > REGION_DATA AT > REGION_RODATA

	.bss (NOLOAD): {
		. = ALIGN(0x4) ;
		__bss_start__ = .;
		*(.bss*)
			*(COMMON)
			__bss_end__ = .;
		. = ALIGN(0x4);
	} > REGION_BSS AT > REGION_RODATA
}
