#ifndef _IROM_CDBG_H_
#define _IROM_CDBG_H_

struct cdbg_cfg_dram {
  uint32_t paras;
};

struct cdbg_cfg_clks {
  uint16_t apll;
  uint16_t dpll;
  uint16_t epll;
  uint16_t vpll;
  uint8_t cpu_clk[8];
  uint8_t axi_clk[8];
  uint8_t apb_clk[8];
  uint8_t axi_cpu[8];
  uint8_t apb_cpu[8];
  uint8_t apb_axi[8];
  int cpu_pll;
  int div_len;
};

enum cdbg_nand_timing {
  NF_tREA = 0,
  NF_tREH,
  NF_tCLS,
  NF_tCLH,
  NF_tWH,
  NF_tWP,
  NF_tRP,
  NF_tDS,
  NF_tCAD,
  NF_tDQSCK,
  /*NF_tCAD = NF_tRPRE, NF_tDQSCK = NF_tDQSRE*/
};

#define CDBG_NAND_ID_COUNT 8
struct cdbg_cfg_nand {
  uint32_t magic;

  uint8_t name[24];
  uint8_t id[CDBG_NAND_ID_COUNT];
  uint8_t timing[12];

  uint16_t pagesize;
  uint16_t blockpages; /* pages per block */
  uint16_t blockcount; /* blocks per device */
  uint16_t bad0;       /* first bad block mark */
  uint16_t bad1;       /* second bad block mark */

  uint16_t sysinfosize;
  uint16_t rnbtimeout; /* ms */
  uint16_t
      syncdelay; /* percent of a peroid [7:0] , phy cycle time (ns) [15:8]*/
  uint16_t syncread;

  uint16_t polynomial;
  uint32_t seed[4];

  /* [1:  0]: interface: 0: legacy, 1: ONFI sync, 2: toggle
   * [3:  2]: bus width: 0: 8-bit, 1: 16-bit
   * [6:  4]: cycle
   * [    7]: randomizer
   * [15: 8]: main ECC bits
   * [23:16]: spare ECC bits
   */
  uint32_t parameter;
  uint32_t resv0;
  uint32_t resv1;
  uint32_t resv2;
};

#define CDBG_NF_PARAMETER(a, b, c, d, e, f)                                    \
  (a | (b << 2) | (c << 4) | (d << 7) | (e << 8) | (f << 16))

#define CDBG_NF_INTERFACE(x)  (x & 0x3)
#define CDBG_NF_BUSW(x)       ((x >> 2) & 0x3)
#define CDBG_NF_CYCLE(x)      ((x >> 4) & 0x7)
#define CDBG_NF_RANDOMIZER(x) ((x >> 7) & 1)
#define CDBG_NF_MLEVEL(x)                                                      \
  ({                                                                           \
    int __t = (x >> 8) & 0xff;                                                 \
    (__t >= 80)                                                                \
        ? 12                                                                   \
        : (__t >= 72)                                                          \
              ? 11                                                             \
              : (__t >= 64)                                                    \
                    ? 10                                                       \
                    : (__t >= 60)                                              \
                          ? 9                                                  \
                          : (__t >= 56)                                        \
                                ? 8                                            \
                                : (__t >= 48)                                  \
                                      ? 7                                      \
                                      : (__t >= 40)                            \
                                            ? 6                                \
                                            : (__t >= 32)                      \
                                                  ? 5                          \
                                                  : (__t >= 24)                \
                                                        ? 4                    \
                                                        : (__t >= 16)          \
                                                              ? 3              \
                                                              : (__t >= 8)     \
                                                                    ? 2        \
                                                                    : (__t >=  \
                                                                       4)      \
                                                                          ? 1  \
                                                                          : 0; \
  })
#define CDBG_NF_SLEVEL(x) ((((x >> 16) & 0xff) >= 8) ? 1 : 0)
#define CDBG_NF_ECCEN(x)  !!((x >> 8) & 0xffff)

struct cdbg_cfg_table {
  /* magic */
  uint32_t magic;
  uint32_t length;
  uint32_t dcrc;
  uint32_t hcrc;
  int clksen;
  int dramen;
  int nanden;
  int nandcount;
  int spibytes;
  int iomux;    /* IO MUX mode */
  int blinfo;   /* new 16-bit bootloader info to reconfig boot devices */
  int bldevice; /* boot loader device, -1 means following the config boot loader
                 */
  int resv[4];
  uint32_t bloffset; /* boot loader offset in that device */
  uint32_t clks_offset;
  uint32_t dram_offset;
  uint32_t nand_offset;
};

#define IR_CFG_TLB_MAGIC 0x69780800

extern void cdbg_jump(void *address, int para);
extern int cdbg_do_config(void *table, int c);
extern int cdbg_config_status(uint32_t *stat);
extern void cdbg_shell(void);
extern int cdbg_dram_enabled(void);
extern int cdbg_is_wakeup(void);
extern void cdbg_restore_os(void);
extern void cdbg_log_toggle(int en);
extern void cdbg_boot_redirect(int *id, loff_t *offs);
extern int cdbg_config_isi(void *data);

extern int cdbg_verify_burn(void);
extern void cdbg_verify_burn_enable(int en, const uint8_t *key);
extern uint8_t *cdbg_verify_burn_key(void);

extern uint8_t __irom_ver[];

#define addr_is_dram(x) (((uint32_t)x) >= DRAM_BASE_PA)

#define CDBG_MAGIC_NAND    0xdfbda458
#define CDBG_MAGIC_NANDSUB 0xaca4570e
#define CDBG_MAGIC_SPI     0x4a82467c

#endif /* _IROM_CDBG_H_ */
