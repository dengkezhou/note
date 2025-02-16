/*
 * (C) Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

#ifndef __COMMON_H_
#define __COMMON_H_ 1

#undef _LINUX_CONFIG_H
#define _LINUX_CONFIG_H 1 /* avoid reading Linux autoconf.h file	*/

#ifndef __ASSEMBLY__ /* put C only stuff in this section */

typedef unsigned char uchar;
typedef volatile unsigned long vu_long;
typedef volatile unsigned short vu_short;
typedef volatile unsigned char vu_char;
typedef enum { CPU, SAP, RTC } domain_t;
enum { CLUSTER0, CLUSTER1 };

#include <config.h>
#include <irerrno.h>
#include <linux/bitops.h>
#include <stdlib/stddef.h>
#include <stdlib/stdio.h>
#include <stdlib/sys/stdint.h>
#include <linux/string.h>
#include <stdarg.h>
#include <console.h>
#include <stdio.h>

//#include <iws100/all.h>

#include CONFIG_INTCHAINS_REGS_FILE
#include <generated/autoconf.h>

#ifdef CONFIG_RISCV_SMODE
#define __SMODE_SUPPORT
#endif

#ifdef CONFIG_RISCV
#ifdef CONFIG_64BIT
#include <core_rv64.h>
#include <csi_rv64_gcc.h>
#else
#include <core_rv32.h>
#include <csi_rv32_gcc.h>
#endif
#endif

//#include <part.h>
//#include <flash.h>

/*
 *testbench result
 * -1 : test Failed
 *  0 : auto test success
 *  1 : test over and result need  check  manually
 * */
#define TB_RET_SUCCESS 0
#define TB_RET_MANUAL  1
#define TB_RET_FAIL    -1

#define USE_INTLEAVE 1
#define USE_INTLEAVE_MASK (1<<6)

#ifdef DEBUG
#define debug(fmt, args...) printf(fmt, ##args)
#define debugX(level, fmt, args...)                                            \
  if (DEBUG >= level)                                                          \
    printf(fmt, ##args);
#else
#define debug(fmt, args...)
#define debugX(level, fmt, args...)
#endif /* DEBUG */
#if 1
#define panic(x...)                                                            \
  do {                                                                         \
    printf("@_@ panic:%d >_<\n", __LINE__);                                    \
    printf("%s\n", __FILE__);                                                  \
    printf(x);                                                                 \
    for (;;)                                                                   \
      ;                                                                        \
  } while (0)
#endif
#ifndef BUG
#define BUG()                                                                  \
  do {                                                                         \
    printf("BUG: failure at %s:%d/%s()!\n", __FILE__, __LINE__, __FUNCTION__); \
    panic("BUG!");                                                             \
  } while (0)
#define BUG_ON(condition)                                                      \
  do {                                                                         \
    if (unlikely((condition) != 0))                                            \
      BUG();                                                                   \
  } while (0)
#endif /* BUG */

#define cpu_relax() __asm__ __volatile__("" : : : "memory")

#define IS_ALIGNED(x, a) (((x) & ((typeof(x))(a)-1)) == 0)

#define dev_err(dev, format, ...)  printf(format, ##__VA_ARGS__)
#define dev_info(dev, format, ...) printf(format, ##__VA_ARGS__)
#define dev_dbg(dev, format, ...)  printf(format, ##__VA_ARGS__)
#define dev_vdbg(dev, format, ...) printf(format, ##__VA_ARGS__)
#define dev_warn(dev, format, ...) printf(format, ##__VA_ARGS__)

/**
 * upper_32_bits - return bits 32-63 of a number
 * @n: the number we're accessing
 *
 * A basic shift-right of a 64- or 32-bit quantity.  Use this to suppress
 * the "right shift count >= width of type" warning when that quantity is
 * 32-bits.
 */
#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))

/**
 * lower_32_bits - return bits 0-31 of a number
 * @n: the number we're accessing
 */
#define lower_32_bits(n) ((u32)((n)&0xffffffff))

typedef void(interrupt_handler_t)(void *);

/*
 * enable common handling for all TQM8xxL/M boards:
 * - CONFIG_TQM8xxM will be defined for all TQM8xxM boards
 * - CONFIG_TQM8xxL will be defined for all TQM8xxL _and_ TQM8xxM boards
 *                  and for the TQM885D board
 */
#if defined(CONFIG_TQM823M) || defined(CONFIG_TQM850M) ||                      \
    defined(CONFIG_TQM855M) || defined(CONFIG_TQM860M) ||                      \
    defined(CONFIG_TQM862M) || defined(CONFIG_TQM866M)
#ifndef CONFIG_TQM8xxM
#define CONFIG_TQM8xxM
#endif
#endif
#if defined(CONFIG_TQM823L) || defined(CONFIG_TQM850L) ||                      \
    defined(CONFIG_TQM855L) || defined(CONFIG_TQM860L) ||                      \
    defined(CONFIG_TQM862L) || defined(CONFIG_TQM8xxM) ||                      \
    defined(CONFIG_TQM885D)
#ifndef CONFIG_TQM8xxL
#define CONFIG_TQM8xxL
#endif
#endif

#ifndef CONFIG_SERIAL_MULTI

#if defined(CONFIG_8xx_CONS_SMC1) || defined(CONFIG_8xx_CONS_SMC2) ||          \
    defined(CONFIG_8xx_CONS_SCC1) || defined(CONFIG_8xx_CONS_SCC2) ||          \
    defined(CONFIG_8xx_CONS_SCC3) || defined(CONFIG_8xx_CONS_SCC4)

#define CONFIG_SERIAL_MULTI 1

#endif

#endif /* CONFIG_SERIAL_MULTI */

/*
 * General Purpose Utilities
 */

#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) > (y) ? (x) : (y))

#define MIN(x, y) min(x, y)
#define MAX(x, y) max(x, y)

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member)                                        \
  ({                                                                           \
    const typeof(((type *)0)->member) *__mptr = (ptr);                         \
    (type *)((char *)__mptr - offsetof(type, member));                         \
  })

/* add for iROM */
extern int init_timer(void);
extern void init_core(void);

/*
 * Function Prototypes
 */

#ifdef CONFIG_SERIAL_SOFTWARE_FIFO
void serial_buffered_init(void);
void serial_buffered_putc(const char);
void serial_buffered_puts(const char *);
int serial_buffered_getc(void);
int serial_buffered_tstc(void);
#endif /* CONFIG_SERIAL_SOFTWARE_FIFO */

void hang(void) __attribute__((noreturn));

/* */
phys_size_t initdram(int);
int display_options(void);
void print_size(phys_size_t, const char *);
int print_buffer(ulong addr, void *data, uint width, uint count, uint linelen);

/* common/main.c */
void main_loop(void);
int readline(const char *const prompt);
int readline_into_buffer(const char *const prompt, char *buffer);
int parse_line(char *, char *[]);
void init_cmd_timeout(void);
void reset_cmd_timeout(void);

/* lib_$(ARCH)/board.c */
void board_init_f(ulong) __attribute__((noreturn));
int checkboard(void);
int checkflash(void);
int checkdram(void);
int last_stage_init(void);
extern ulong monitor_flash_len;
int mac_read_from_eeprom(void);

/* common/flash.c */
void flash_perror(int);

/* common/cmd_source.c */
int source(ulong addr, const char *fit_uname);

extern ulong load_addr; /* Default Load Address */

/* common/cmd_doc.c */
void doc_probe(unsigned long physadr);

/* common/cmd_nvedit.c */
int env_init(void);
void env_relocate(void);
int envmatch(uchar *, int);
char *getenv(char *);
int getenv_r(char *name, char *buf, unsigned len);
int saveenv(void);
#ifdef CONFIG_PPC /* ARM version to be fixed! */
int inline setenv(char *, char *);
#else
int setenv(char *, char *);
#ifdef CONFIG_HAS_UID
void forceenv(char *, char *);
#endif
#endif /* CONFIG_PPC */
#ifdef CONFIG_ARM
#include <asm/mach-types.h>
#include <asm/setup.h>
#include <asm/u-boot-arm.h> /* ARM version to be fixed! */
#endif                      /* CONFIG_ARM */
#ifdef CONFIG_I386          /* x86 version to be fixed! */
#include <asm/u-boot-i386.h>
#endif /* CONFIG_I386 */

#ifdef CONFIG_AUTO_COMPLETE
int env_complete(char *var, int maxv, char *cmdv[], int maxsz, char *buf);
#endif
int get_env_id(void);

void pci_init(void);
void pci_init_board(void);
void pciinfo(int, int);

#if defined(CONFIG_PCI) && (defined(CONFIG_4xx) && !defined(CONFIG_AP1000))
int pci_pre_init(struct pci_controller *);
int is_pci_host(struct pci_controller *);
#endif

#if defined(CONFIG_PCI) && (defined(CONFIG_440) || defined(CONFIG_405EX))
#if defined(CONFIG_SYS_PCI_TARGET_INIT)
void pci_target_init(struct pci_controller *);
#endif
#if defined(CONFIG_SYS_PCI_MASTER_INIT)
void pci_master_init(struct pci_controller *);
#endif
#if defined(CONFIG_440SPE) || defined(CONFIG_460EX) ||                         \
    defined(CONFIG_460GT) || defined(CONFIG_405EX)
void pcie_setup_hoses(int busno);
#endif
#endif

int misc_init_f(void);
int misc_init_r(void);

/* common/exports.c */
void jumptable_init(void);

/* common/kallsysm.c */
const char *symbol_lookup(unsigned long addr, unsigned long *caddr);

/* api/api.c */
void api_init(void);

/* common/memsize.c */
long get_ram_size(volatile long *, long);

/* $(BOARD)/$(BOARD).c */
void reset_phy(void);
void fdc_hw_init(void);

/* $(BOARD)/eeprom.c */
void eeprom_init(void);
#ifndef CONFIG_SPI
int eeprom_probe(unsigned dev_addr, unsigned offset);
#endif
int eeprom_read(unsigned dev_addr, unsigned offset, uchar *buffer,
                unsigned cnt);
int eeprom_write(unsigned dev_addr, unsigned offset, uchar *buffer,
                 unsigned cnt);
#ifdef CONFIG_LWMON
extern uchar pic_read(uchar reg);
extern void pic_write(uchar reg, uchar val);
#endif

/*
 * Set this up regardless of board
 * type, to prevent errors.
 */
#if defined(CONFIG_SPI) || !defined(CONFIG_SYS_I2C_EEPROM_ADDR)
#define CONFIG_SYS_DEF_EEPROM_ADDR 0
#else
#define CONFIG_SYS_DEF_EEPROM_ADDR CONFIG_SYS_I2C_EEPROM_ADDR
#endif /* CONFIG_SPI || !defined(CONFIG_SYS_I2C_EEPROM_ADDR) */

#if defined(CONFIG_SPI)
extern void spi_init_f(void);
extern void spi_init_r(void);
extern ssize_t spi_read(uchar *, int, uchar *, int);
extern ssize_t spi_write(uchar *, int, uchar *, int);
#endif

#ifdef CONFIG_RPXCLASSIC
void rpxclassic_init(void);
#endif

void rpxlite_init(void);

#ifdef CONFIG_MBX
/* $(BOARD)/mbx8xx.c */
void mbx_init(void);
void board_serial_init(void);
void board_ether_init(void);
#endif

#ifdef CONFIG_HERMES
/* $(BOARD)/hermes.c */
void hermes_start_lxt980(int speed);
#endif

#ifdef CONFIG_EVB64260
void evb64260_init(void);
void debug_led(int, int);
void display_mem_map(void);
void perform_soft_reset(void);
#endif

/* $(BOARD)/$(BOARD).c */
int board_early_init_f(void);
int board_late_init(void);
int board_postclk_init(void); /* after clocks/timebase, before env/serial */
int board_early_init_r(void);
void board_poweroff(void);

#if defined(CONFIG_SYS_DRAM_TEST)
int testdram(void);
#endif /* CONFIG_SYS_DRAM_TEST */

/* $(CPU)/start.S */
#if defined(CONFIG_5xx) || defined(CONFIG_8xx)
uint get_immr(uint);
#endif
uint get_pir(void);
#if defined(CONFIG_MPC5xxx)
uint get_svr(void);
#endif
uint get_pvr(void);
uint get_svr(void);
uint rd_ic_cst(void);
void wr_ic_cst(uint);
void wr_ic_adr(uint);
uint rd_dc_cst(void);
void wr_dc_cst(uint);
void wr_dc_adr(uint);
void align_chk_enable(void);
void align_chk_disable(void);
void smp_enable(void);
void smp_disable(void);
int smp_status(void);

int icache_status(void);
void icache_enable(void);
void icache_disable(void);
void icache_invalid(void);
int dcache_status(void);
void dcache_enable(void);
void dcache_disable(void);
void dcache_enable_all(void);
void dcache_disable_all(void);

void dcache_clean(void);
void dcache_invalid(void);
void dcache_flush_range(uint64_t *start, unsigned long size);
void dcache_clean_range(uint64_t *start, unsigned long size);
void dcache_invalid_range(uint64_t *start, unsigned long size);
void l1_l2_inv_range(unsigned start, unsigned size);
void l1_l2_invalid_all(void);
void l1_l2_clean_range(unsigned start, unsigned size);
void l1_l2_clean_all(void);
void cache_flush_all(void);
ulong get_endaddr(void);
void trap_init(ulong);
#if defined(CONFIG_4xx) || defined(CONFIG_MPC5xxx) ||                          \
    defined(CONFIG_74xx_7xx) || defined(CONFIG_74x) || defined(CONFIG_75x) ||  \
    defined(CONFIG_74xx) || defined(CONFIG_MPC8220) ||                         \
    defined(CONFIG_MPC85xx) || defined(CONFIG_MPC86xx) ||                      \
    defined(CONFIG_MPC83xx)
unsigned char in8(unsigned int);
void out8(unsigned int, unsigned char);
unsigned short in16(unsigned int);
unsigned short in16r(unsigned int);
void out16(unsigned int, unsigned short value);
void out16r(unsigned int, unsigned short value);
unsigned long in32(unsigned int);
unsigned long in32r(unsigned int);
void out32(unsigned int, unsigned long value);
void out32r(unsigned int, unsigned long value);
void ppcDcbf(unsigned long value);
void ppcDcbi(unsigned long value);
void ppcSync(void);
void ppcDcbz(unsigned long value);
#endif
#if defined(CONFIG_MICROBLAZE)
unsigned short in16(unsigned int);
void out16(unsigned int, unsigned short value);
#endif

#if defined(CONFIG_MPC83xx)
void ppcDWload(unsigned int *addr, unsigned int *ret);
void ppcDWstore(unsigned int *addr, unsigned int *value);
#endif

/* $(CPU)/cpu.c */
int checkcpu(void);
int checkicache(void);
int checkdcache(void);
void upmconfig(unsigned int, unsigned int *, unsigned int);
ulong get_tbclk(void);
void reset_cpu(ulong addr);
#if defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP)
void ft_cpu_setup(void *blob);
#ifdef CONFIG_PCI
void ft_pci_setup(void *blob);
#endif
#endif

/* $(CPU)/speed.c */
int get_clocks(void);
int get_clocks_866(void);
int sdram_adjust_866(void);
int adjust_sdram_tbs_8xx(void);
#if defined(CONFIG_8260)
int prt_8260_clks(void);
#elif defined(CONFIG_MPC5xxx)
int prt_mpc5xxx_clks(void);
#endif
#if defined(CONFIG_MPC512X)
int prt_mpc512xxx_clks(void);
#endif
#if defined(CONFIG_MPC8220)
int prt_mpc8220_clks(void);
#endif
#ifdef CONFIG_4xx
ulong get_OPB_freq(void);
ulong get_PCI_freq(void);
#endif
ulong get_PCLK(void);
#if defined(CONFIG_S3C2400) || defined(CONFIG_S3C2410) ||                      \
    defined(CONFIG_LH7A40X) || defined(CONFIG_S3C6400)
ulong get_FCLK(void);
ulong get_HCLK(void);
ulong get_UCLK(void);
#endif
#if defined(CONFIG_LH7A40X)
ulong get_PLLCLK(void);
#endif
#if defined CONFIG_INCA_IP
uint incaip_get_cpuclk(void);
#endif
#if defined(CONFIG_IMX)
ulong get_systemPLLCLK(void);
ulong get_FCLK(void);
ulong get_HCLK(void);
ulong get_BCLK(void);
ulong get_PERCLK1(void);
ulong get_PERCLK2(void);
ulong get_PERCLK3(void);
#endif
ulong get_bus_freq(ulong);

#if defined(CONFIG_MPC85xx)
typedef MPC85xx_SYS_INFO sys_info_t;
void get_sys_info(sys_info_t *);
ulong get_ddr_freq(ulong);
#endif
#if defined(CONFIG_MPC86xx)
typedef MPC86xx_SYS_INFO sys_info_t;
void get_sys_info(sys_info_t *);
#endif

#if defined(CONFIG_4xx) || defined(CONFIG_IOP480)
#if defined(CONFIG_440)
#if defined(CONFIG_440SPE)
unsigned long determine_sysper(void);
unsigned long determine_pci_clock_per(void);
#endif
#endif
typedef PPC4xx_SYS_INFO sys_info_t;
int ppc440spe_revB(void);
void get_sys_info(sys_info_t *);
#endif

/* $(CPU)/cpu_init.c */
#if defined(CONFIG_8xx) || defined(CONFIG_8260)
void cpu_init_f(volatile immap_t *immr);
#endif
#if defined(CONFIG_4xx) || defined(CONFIG_MPC85xx) ||                          \
    defined(CONFIG_MCF52x2) || defined(CONFIG_MPC86xx)
void cpu_init_f(void);
#endif

int cpu_init_r(void);
#if defined(CONFIG_8260)
int prt_8260_rsr(void);
#elif defined(CONFIG_MPC83xx)
int prt_83xx_rsr(void);
#endif

/* $(CPU)/interrupts.c */
int interrupt_init(void);
void coret_interrupt(void *);
void external_interrupt(void *);
void soft_interrupt(void *regs);
void irq_install_handler(int, interrupt_handler_t *, void *);
void irq_free_handler(int);
void reset_timer(void);
unsigned long get_timer(ulong base);
unsigned long get_timer_us(ulong base);
void set_timer(ulong t);
void enable_interrupts(void);
int disable_interrupts(void);
#define if_timeout(_cd, _to)                                                   \
  for (int __t = get_timer(0); get_timer(__t) < _to;)                          \
    if (_cd)                                                                   \
      break;                                                                   \
  if (get_timer(__t) > _to)

/* $(CPU)/.../commproc.c */
int dpram_init(void);
uint dpram_base(void);
uint dpram_base_align(uint align);
uint dpram_alloc(uint size);
uint dpram_alloc_align(uint size, uint align);
void post_word_store(ulong);
ulong post_word_load(void);
void bootcount_store(ulong);
ulong bootcount_load(void);
#define BOOTCOUNT_MAGIC 0xB001C041

/* $(CPU)/.../<eth> */
void mii_init(void);

/* $(CPU)/.../lcd.c */
ulong lcd_setmem(ulong);

/* $(CPU)/.../vfd.c */
ulong vfd_setmem(ulong);

/* $(CPU)/.../video.c */
ulong video_setmem(ulong);

/* lib_$(ARCH)/cache.c */
void flush_cache(unsigned long, unsigned long);
void inv_cache(unsigned long, unsigned long);
void clean_cache(unsigned long, unsigned long);
void flush_dcache_range(unsigned long start, unsigned long stop);
void dcache_flush(void);
void invalidate_dcache_range(unsigned long start, unsigned long stop);

#include <clock.h>
#include <domain.h>
//#include <pads.h>

/* lib_$(ARCH)/ticks.S */
unsigned long long get_ticks(void);
void wait_ticks(unsigned long);

/* lib_$(ARCH)/time.c */
void udelay(unsigned long);
void nsdelay(unsigned long);
ulong usec2ticks(unsigned long usec);
ulong ticks2usec(unsigned long ticks);
int init_timebase(void);

/* lib_generic/vsprintf.c */
ulong simple_strtoul(const char *cp, char **endp, unsigned int base);
#ifdef CONFIG_SYS_64BIT_VSPRINTF
unsigned long long simple_strtoull(const char *cp, char **endp,
                                   unsigned int base);
#endif
long simple_strtol(const char *cp, char **endp, unsigned int base);
int sprintf(char *buf, const char *fmt, ...)
    __attribute__((format(__printf__, 2, 3)));
int vsprintf(char *buf, const char *fmt, va_list args);

/* lib_generic/strmhz.c */
char *strmhz(char *buf, long hz);

/* lib_generic/crc32.c */
uint32_t lib_crc32(uint32_t, const unsigned char *, uint);
uint32_t lib_crc32_wd(uint32_t, const unsigned char *, uint, uint);
uint32_t lib_crc32_no_comp(uint32_t, const unsigned char *, uint);

/* common/console.c */
int init_serial(void);

int console_init_f(void); /* Before relocation; uses the serial  stuff	*/
int console_init_r(void); /* After  relocation; uses the console stuff	*/
int console_assign(int file, char *devname); /* Assign the console	*/
int ctrlc(void);
int had_ctrlc(void);    /* have we had a Control-C since last clear? */
void clear_ctrlc(void); /* clear the Control-C condition */
int disable_ctrlc(int); /* 1 to disable, 0 to enable Control-C detect */
void soc_dump(uint64_t src_addr, uint32_t size);
/*
 * STDIO based functions (can always be used)
 */
/* serial stuff */
void serial_printf(const char *fmt, ...)
    __attribute__((format(__printf__, 1, 2)));
/* stdin */
int getc(void);
int tstc(void);
char *gets_s(char *s, int len);

/* stdout */
void putc(const char c);
void puts(const char *s);
void puts_enable(int);
void vprintf(const char *fmt, va_list args);

#ifdef NO_PRINTF
#define printf(x...)
#endif

/* stderr */
#define eputc(c)              fputc(stderr, c)
#define eputs(s)              fputs(stderr, s)
#define eprintf(fmt, args...) fprintf(stderr, fmt, ##args)

/*
 * FILE based functions (can only be used AFTER relocation!)
 */
#ifndef __STD_IO_FILE__
#define __STD_IO_FILE__
#define stdin     0
#define stdout    1
#define stderr    2
#define MAX_FILES 3
#endif
#if 0
void	fprintf(int file, const char *fmt, ...)
		__attribute__ ((format (__printf__, 2, 3)));
void	fputs(int file, const char *s);
void	fputc(int file, const char c);
#endif
int ftstc(int file);
int fgetc(int file);

/*
 * CONSOLE multiplexing.
 */
#ifdef CONFIG_CONSOLE_MUX
#include <iomux.h>
#endif

int pcmcia_init(void);

#ifdef CONFIG_STATUS_LED
#include <status_led.h>
#endif
/*
 * Board-specific Platform code can reimplement show_boot_progress () if needed
 */
void show_boot_progress(int val);

/* Multicore arch functions */
#ifdef CONFIG_MP
int cpu_status(int nr);
int cpu_reset(int nr);
int cpu_release(int nr, int argc, char *argv[]);
#endif

#endif /* __ASSEMBLY__ */

/* Put only stuff here that the assembler can digest */

#ifdef CONFIG_POST
#define CONFIG_HAS_POST
#endif

#ifdef CONFIG_INIT_CRITICAL
#error CONFIG_INIT_CRITICAL is deprecated!
#error Read section CONFIG_SKIP_LOWLEVEL_INIT in README.
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define ROUND(a, b)        (((a) + (b)) & ~((b)-1))
#define DIV_ROUND(n, d)    (((n) + ((d) / 2)) / (d))
#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))
#define roundup(x, y)      ((((x) + ((y)-1)) / (y)) * (y))

#define __ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))

#define memset2(p, n, c) memset(p, c, n)
void dsb(void);

#define NR_CPUS CONFIG_NR_CPUS
#endif /* __COMMON_H_ */
