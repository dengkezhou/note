#ifndef _IROM_CONFGI_H_
#define _IROM_CONFGI_H_

#include <generated/autoconf.h>

#define CONFIG_FPGA_TALS
/* boards
#define CONFIG_FPGA_HAPS
#define CONFIG_FPGA_TALS
*/
#if defined(CONFIG_C920)
#define CONFIG_INTCHAINS_REGS_FILE <asm/arch-c920/intchains-regs.h>
#elif defined(CONFIG_E906)
#define CONFIG_INTCHAINS_REGS_FILE <asm/arch-e906/intchains-regs.h>
#elif defined(CONFIG_E902)
#define CONFIG_INTCHAINS_REGS_FILE <asm/arch-e902/intchains-regs.h>
#endif

#if defined(CONFIG_FPGA_HAPS)
#define UART_CLK 40000000
#define SD_CLK   40000000
#define USB_CLK  48000000
#define APB_CLK  20000000
#define AXI_CLK  20000000
#elif defined(CONFIG_FPGA_TALS)
#define UART_CLK 40000000 // 20000000
#define SD_CLK   40000000
#define USB_CLK  48000000
#define APB_CLK  20000000
#define AXI_CLK  20000000
#endif

#define CONFIG_SYS_PROMPT "tb:/$ " /* Monitor Command Prompt */

#define CONFIG_SYS_64BIT_VSPRINTF /* needed for nand_util.c */
#define CONFIG_SYS_64BIT_STRTOUL
#define CONFIG_SYS_LONGHELP      /* undef to save memory	      */
#define CONFIG_SYS_CBSIZE    256 /* Console I/O Buffer Size    */
#define CONFIG_SYS_PBSIZE    384 /* Print Buffer Size          */
#define CONFIG_SYS_MAXARGS   16  /* max number of command args */
#define CONFIG_DOS_PARTITION 1

#endif /* _IROM_CONFGI_H_ */
