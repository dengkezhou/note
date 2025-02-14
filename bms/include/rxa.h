#ifndef __RXA_DRIVER_H__
#define __RXA_DRIVER_H__

#define RXA_ISA_NOP       0x00
#define RXA_ISA_LD        0x01
#define RXA_ISA_ST        0x02
#define RXA_ISA_VSTQ      0x03
#define RXA_ISA_VLD       0x04
#define RXA_ISA_VLDQ_XOR  0x05
#define RXA_ISA_VLD_W     0x06
#define RXA_ISA_VLDQ_W    0x07
#define RXA_ISA_PRFC      0x08
#define RXA_ISA_WPRFC     0x09
#define RXA_ISA_XOR       0x10
#define RXA_ISA_ROR       0x11
#define RXA_ISA_RORI      0x12
#define RXA_ISA_SWAP      0x13
#define RXA_ISA_ADDSL     0x14
#define RXA_ISA_ADDI      0x15
#define RXA_ISA_NEG       0x16
#define RXA_ISA_ADD       0x18
#define RXA_ISA_SUB       0x19
#define RXA_ISA_MUL       0x1a
#define RXA_ISA_MULH      0x1b
#define RXA_ISA_MULHU     0x1c
#define RXA_ISA_VADD_D    0x20
#define RXA_ISA_VSUB_D    0x21
#define RXA_ISA_VMUL_D    0x22
#define RXA_ISA_VDIV_D    0x23
#define RXA_ISA_VXOR      0x24
#define RXA_ISA_VSWAP     0x28
#define RXA_ISA_VSQRT_D   0x29
#define RXA_ISA_VCVT_D_W  0x2a
#define RXA_ISA_RXSFRM    0x30
#define RXA_ISA_RXSSP     0x31
#define RXA_ISA_RXSMXA    0x32
#define RXA_ISA_RXB       0x33
#define RXA_ISA_BGT       0x34
#define RXA_ISA_BRK       0x35
#define RXA_ISA_RXBLK2B   0x36
#define RXA_ISA_RXAES1RX4 0x37
#define RXA_ISA_RXAES1RX4_HASH  RXA_ISA_RXAES1RX4
#define RXA_ISA_RXAES1RX4_MUTI  RXA_ISA_RXAES1RX4
#define RXA_ISA_RXAES4RX4 0x38
#define RXA_ISA_BRGT      (RXA_ISA_END - 1) // fake instruction
#define RXA_ISA_END       0x7f
#define RXA_ISA_MAX       RXA_ISA_END + 1

#define RXA_VER            "V010"
#define RXA_MAX            32
#define RXA_PER_GROUP      6
#define RXA_PER_RESV_GROUP 8
#ifdef CONFIG_COMPILE_SIM
#define RXA_IRQ(idx) 0
#else
#define RXA_IRQ(idx)                                                           \
  (C_RXAG0IDX0_IRQn + idx / RXA_PER_GROUP * RXA_PER_RESV_GROUP +               \
   idx % RXA_PER_GROUP)
#endif
#define ENABLE  1
#define DISABLE 0

#define RXA_PICK_SIZE        10
#define RXA_INT_DONE         (1 << 0)
#define RXA_INT_PAUSED       (1 << 1)
#define RXA_INT_STEP				 (1 << 2)
#define RXA_INT_ILLEAGLE     (1 << 3)
#define RXA_INT_DATA_ABORT   (1 << 4)
#define RXA_INT_ILLEAGLE_CFG (1 << 5)
#define RXA_INT_ALL                                                            \
  (RXA_INT_DONE | RXA_INT_PAUSED | RXA_INT_ILLEAGLE | RXA_INT_DATA_ABORT |     \
   RXA_INT_ILLEAGLE_CFG | RXA_INT_STEP)
#define RXA_INT_NONE 0

#define RXA_CFG_OUTPUT_REGF (1 << 3)
#define RXA_CFG_EXEC_MODE   (1 << 2)
#define RXA_CFG_FETCH_WIDTH (3)

#define RXA(_offs)   ((unsigned long)(&dev->regs->_offs))
#define limits(a, b) (reg >= a && reg <= b)
#define lo(x)        (x & 0xffffffff)
#define hi(x)        lo(x >> 32)

enum {
  RXA_BLAKE2B,
  RXA_AES1RX4,
  RXA_AES1RX4_HASH,
  RXA_AES1RX4_MUTI,
  RXA_AES4RX4,
};

enum {
  x0,
  x1,
  x2,
  x3,
  x4,
  x5,
  x6,
  x7,
  x8,
  x9,
  x10,
  x11,
  x12,
  x13,
  x14,
  x15,
  x16,
  x17,
  x18,
  x19,
  x20,
  x21,
  x22,
  x23,
  x24,
  x25,
  x26,
  x27,
  x28,
  x29,
  x30,
  x31,
  v0,
  v1,
  v2,
  v3,
  v4,
  v5,
  v6,
  v7,
  v8,
  v9,
  v10,
  v11,
  v12,
  v13,
  v14,
  v15,
  v16,
  v17,
  v18,
  v19,
  v20,
  v21,
  v22,
  v23,
  v24,
  v25,
  v26,
  v27,
  v28,
  v29,
  v30,
  v31,
  frm,
  mem,
  prfc,
  jmp
};

#define G(x) ((x > x31) ? x - v0 : x)
#define RXAC(_op, _rd, _rs, _p0, _p1)                                          \
  do {                                                                         \
    printf("%p: RXAC 0x%x\n", code,                                            \
           _op | (G(_rd) << 7) | (G(_rs) << 12) | (_p0 << 17) | (_p1 << 22));  \
    *code++ =                                                                  \
        _op | (G(_rd) << 7) | (G(_rs) << 12) | (_p0 << 17) | (_p1 << 22);      \
  } while (0)

enum {
  RXAI_NORMAL,
  RXAI_STEP,
};

enum {
  RXAI_OFFS_SRAM = 0,
  RXAI_OFFS_SPAD = 21, // log20x1000
  RXAI_OFFS_DDR  = 31, // log2Dataset
};

enum {
  RXAI_ISA_FETCH_WIDTH1,
  RXAI_ISA_FETCH_WIDTH2,
  RXAI_ISA_FETCH_WIDTH4,
  RXAI_ISA_FETCH_WIDTH8,
};

enum {
  RXAI_BREAK_POINT0,
  RXAI_BREAK_POINT1,
  RXAI_BREAK_POINT2,
  RXAI_BREAK_POINT3,
  RXAI_BREAK_POINT4,
};

enum { RXAI_R_RIGHT, RXAI_R_LEFT };

enum { RXAI_RS_FULL, RXAI_RS_LO32, RXAI_RS_HI32, RXAI_RS_XPOOL };

enum { RXAI_WTOD_FTYPE, RXAI_WTOD_ETYPE };

#define RXA_VERSION_OFFSET 0
#define RXA_VERSION_MASK   (0xffffffff << RXA_VERSION_OFFSET)

#define RXA_OUTPUTEN_OFFSET  16
#define RXA_OUTPUTEN_MASK     (1 << RXA_OUTPUTEN_OFFSET)
#define RXA_EXECMODE_OFFSET   2
#define RXA_EXECMODE_MASK     (0x3fffffff << RXA_EXECMODE_OFFSET)
#define RXA_FETCHWIDTH_OFFSET 0
#define RXA_FETCHWIDTH_MASK   (0x3 << RXA_FETCHWIDTH_OFFSET)

#define RXA_STOP_OFFSET   2
#define RXA_STOP_MASK     (1 << RXA_STOP_OFFSET)
#define RXA_STATUS_OFFSET 1
#define RXA_STATUS_MASK   (1 << RXA_STATUS_OFFSET)
#define RXA_START_OFFSET  0
#define RXA_START_MASK    (1 << RXA_START_OFFSET)

#define RXA_CFG_R_OFFSET(n) (0x8 * n)
#define RXA_CFG_R_MASK(n)   (0xff << RXA_CFG_R_OFFSET(n))

#define RXA_CFG_OFFSET 0
#define RXA_CFG_MASK   (0xffffffff << RXA_CFG_OFFSET)

#define RXA_IDRAM_OFFSET 0
#define RXA_IDRAM_MASK   (0x3fffff << RXA_IDRAM_OFFSET)

#define RXA_DDRH_OFFSET 0
#define RXA_DDRH_MASK   (0x7 << RXA_DDRH_OFFSET)
#define RXA_DDRL_OFFSET 0
#define RXA_DDRL_MASK   (0xffffffff << RXA_DDRL_OFFSET)

#define RXA_PBUFCLR_START_OFFSET	 16
#define RXA_PBUFCLR_START_MASK		 (0xffff << RXA_PBUFCLR_START_OFFSET)
#define RXA_PBUFCLR_LEN_OFFSET		 0
#define RXA_PBUFCLR_LEN_MASK			 (0xffff << RXA_PBUFCLR_LEN_OFFSET)

#define RXA_INT_DONE_OFFSET      0
#define RXA_INT_DONE_MASK        (1 << RXA_INTEXCEDONE_OFFSET)
#define RXA_INT_PAUSE_OFFSET     1
#define RXA_INT_PAUSE_MASK       (1 << RXA_INTPAUSE_OFFSET)
#define RXA_INT_ILLINS_OFFSET    2
#define RXA_INT_ILLINS_MASK      (1 << RXA_INTILLINS_OFFSET)
#define RXA_INT_DATAABORT_OFFSET 3
#define RXA_INT_DATAABORT_MASK   (1 << RXA_INT_DATAABORT_OFFSET)
#define RXA_INT_ILLCFG_OFFSET    4
#define RXA_INT_ILLCFG_MASK      (1 << RXA_INT_ILLCFG_OFFSET)
#define RXA_INT_OTHER_OFFSET     5
#define RXA_INT_OTHER_MASK       (1 << 5)

#define RXA_DATA_OFFSET 0
#define RXA_DATA_MASK   (0xffffffff << 0)

#define RXA_FLOAT_OFFSET		0
#define RXA_FLOAT_MASK	(0x3 << RXA_FLOAT_OFFSET)

#define RXA_64DATA_OFFSET 0
#define RXA_64DATA_MASK   (0xffffffffffffffffUL << RXA_64DATA_OFFSET)

#define rxa_readl  nbits_readl
#define rxa_writel nbits_writel

typedef struct rxa64 {
  uint32_t h;
  uint32_t l;
} rxa64_t;

typedef struct rxa_regs {
  uint32_t ver;
  uint32_t cfg;
  uint32_t ctrl;
  uint32_t cfg_r;
  uint32_t cfg_cond_offs;
  rxa64_t cfg_e_and_l;
  rxa64_t cfg_e_and_h;
  rxa64_t cfg_e_or_l;
  rxa64_t cfg_e_or_h;
  uint32_t offs_prfc;
  uint32_t offs_regf;
  uint32_t offs_code; //
  uint32_t offs_spad;
  rxa64_t offs_dag;
  rxa64_t offs_decr;
  uint32_t int_msk;
  uint32_t int_status; //
  uint32_t fprc;       // float point round mode
  uint64_t xpool[32];
  uint32_t dbg_pc;
  uint32_t dbg_cycles;
  uint32_t dbg_brk[5];
  uint32_t pbuf_clr; //
  uint64_t dbg_greg[60];
	uint64_t dmamsk;
} rxa_regs_t;

typedef struct rxa_cfg {
  // randomx parameters
  uint32_t e_and[4];
  uint32_t e_or[4];
  char r[4];
  uint32_t cfg_cond_offs;
  bool en_regf;
  int exec_mode;
  int fetch_width;
  // sram & ddr addr
  uint32_t offs_prfc;
  uint32_t offs_regf;
  uint32_t offs_code;
  uint32_t offs_spad;
  unsigned long offs_dag;
  unsigned long offs_decr;
	unsigned long dmamsk;
} rxa_cfg_t;
#define SET(_offs) cfg->_offs

typedef struct rxa_mem {
  void *sram;
  void *dram;
  void *ddr;
} rxa_mem_t;

typedef struct rxa_device {
  char devname[16];
  int idx;
  rxa_mem_t mem;
  rxa_regs_t *regs;
  rxa_cfg_t *cfg;
  void (*callback)(void *data);
  void *privdata;
} rxa_device_t;

typedef struct case_cmd {
  char *name;
  int type;
  int param;
  bool started;
  int result;
  rxa_device_t *dev;
} case_cmd_t;

#pragma pack(4)
typedef struct rxa_cipher_decr {
  int crypto_type;
  uint32_t keyaddrl;
  uint32_t keyaddrh;
  uint32_t keylen;
  uint32_t stateaddrl;
  uint32_t stateaddrh;
  uint32_t statelen;
  uint32_t inaddrl;
  uint32_t inaddrh;
  uint32_t inlen;
  uint32_t outaddrl;
  uint32_t outaddrh;
  uint32_t outlen;
  uint32_t privaddrl;
  uint32_t privaddrh;
  uint32_t privlen;
  uint32_t next_decrl;
  uint32_t next_decrh;
} rxa_cipher_decr_t;
#pragma pack()

rxa_device_t *itcs_rxa_init(int idx, rxa_cfg_t *cfg,
                            void (*callback)(void *privdata), void *privdata);
void rxa_set_privdata(rxa_device_t *dev, void *privdata);
void itcs_rxa_exit(rxa_device_t *dev);
void rxa_start(rxa_device_t *dev);
void rxa_stop(rxa_device_t *dev);
void rxa_set_stepmode(rxa_device_t *dev, int mode, int num);
void rxa_dbg_writeq(rxa_device_t *dev, int reg, uint64_t *val);
void rxa_dbg_readq(rxa_device_t *dev, int reg, uint64_t *val);
void rxa_dump(rxa_device_t *dev);
void rxa_dump_inner_reg(rxa_device_t *dev);
void rxa_set_cfg_e_or(rxa_device_t *dev, uint32_t *e_or);
void rxa_set_cfg_r(rxa_device_t *dev, char *cfgr);
void rxa_set_dag_offs(rxa_device_t *dev, unsigned long offs);
void rxa_resetRoundingMode(rxa_device_t *dev);
void rxa_set_fetch_width(rxa_device_t *dev, int width);
void rxa_set_xpool(rxa_device_t *dev, uint64_t *data, int size);
void rxa_set_cipher_offs(rxa_device_t *dev, unsigned long offs);
void rxa_set_code_offs(rxa_device_t *dev, uint32_t offs);
int rxa_set_break(rxa_device_t *dev, int mode, uint32_t addr);
uint32_t rxa_get_code_offs(rxa_device_t *dev);
int rxa_wait_regf_ready(rxa_device_t *dev);
void rxa_set_regf(rxa_device_t *dev, int en, uint32_t offs);
void rxa_memset(rxa_device_t *dev, uint32_t offs, int len);

inline void *rxa_get_code(rxa_device_t *dev) {
  return (void *)(dev->mem.sram + dev->cfg->offs_code);
}

inline void *rxa_get_sram(rxa_device_t *dev) { return (void *)(dev->mem.sram); }

inline void *rxa_get_spad(rxa_device_t *dev) { return (void *)(dev->mem.dram); }

inline void *rxa_get_ddr(rxa_device_t *dev) {
  return (void *)(dev->cfg->offs_dag);
}

inline void *rxa_get_prfc(rxa_device_t *dev) {
  return (void *)(dev->mem.sram + dev->cfg->offs_prfc);
}
#endif
