/*
 * (C) Copyright 2009
 * Ilya Yanok, Emcraft Systems Ltd, <yanok@emcraft.com>
 *
 * Copyright (C) 2005-2007 Samsung Electronics
 * Kyungin Park <kyugnmin.park@samsung.com>
 *
 * Copyright (c) 2004 Texas Instruments
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
MEMORY
{
	LDS_OUT    : ORIGIN = 0x42000000, LENGTH = 64M
	LDS_TXT : ORIGIN = 0x44000000, LENGTH = 48M

	/* 16M for code stack */
	LDS_STACK  : ORIGIN = 0x47000000, LENGTH = 16M

	/* malloc */
	LDS_MALLOC : ORIGIN = 0x48000000, LENGTH = 256M
	LDS_RESV : ORIGIN = 0x58000000, LENGTH = 512M

	/* reserve 128M for RTL/FPGA data and output */ 
	LDS_DAT    : ORIGIN = 0x78000000, LENGTH = 64M

}

SECTIONS
{
        /* lds memory base */
	__lds_rtl_case     = ORIGIN(LDS_DAT) + 0x1000;
	__lds_rtl_data     = ORIGIN(LDS_DAT) + 0x100000;
	__lds_indicate     = ORIGIN(LDS_OUT);
	__lds_print        = ORIGIN(LDS_OUT) + 0x1000;
	__lds_print_size   = 0x800000;
	__lds_fb           = ORIGIN(LDS_RESV) + 0x1000000;
	__lds_malloc_start = ORIGIN(LDS_MALLOC);
	__lds_malloc_end   = ORIGIN(LDS_MALLOC) + LENGTH(LDS_MALLOC);
	
	/*stacks*/
	__lds_stack_el3 = ORIGIN(LDS_STACK) + LENGTH(LDS_STACK) -0x20;

	.text : {
		*start.o(.text*)
		*(.text)
	} > LDS_TXT
	. = ALIGN(4);
	
	.vectors : {
		*(.vectors);
	} > LDS_TXT
	. = ALIGN(4);

	.rodata : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	} > LDS_TXT
	. = ALIGN(4);

	.init_f : {
		__init_f_start = .;
		*(.init_f0)
		*(.init_f1)
		*(.init_f2)
	} > LDS_TXT
	. = ALIGN(4);
	__init_f_end = .;

    . = ALIGN(4);
    .mmtest : { 
        __mmtest_start = .;
        *(.mmtest)
        . = ALIGN(4);
        __mmtest_end = .;
	} > LDS_TXT

	. = ALIGN(4);

	xlat_table (NOLOAD) : {
        *(xlat_table)
   	} > LDS_TXT 

	.data : {
		__data_start = .;
		*(.data)
		__data_end = .;
		. = ALIGN(4);
	} > LDS_TXT
	. = ALIGN(4);

	.bss (NOLOAD) : {
		__bss_start = .;
		*(.bss)
		*(COMMON)
		 __bss_end = .;
	} > LDS_TXT
	. = ALIGN(4);

	__data_load = LOADADDR(.data);
	__data_len = SIZEOF(.data);
	__bss_size = SIZEOF(.bss);


}

