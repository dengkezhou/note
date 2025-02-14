#ifndef __JRX_BASE_H__
#define __JRX_BASE_H__

#include <stdint.h>
#include <stdio.h>

#define RESV_TMP 6
enum RR {
  // 0~31 is reserved and should be mapped to x0~x31
  xpool = 0x30, // for rxa xpool
  vpool = 0x70,
  rf    = 0x80, // arg0 (reg file) -> p1
  mm,           // arg1 (ma, mx, dataset) -> ds
  sc,           // arg2 (scratchpad)
  ic,           // arg3
  sp,
  xtmp, // tmp
  zero,
  sp2,

  // reg.a
  a0 = 0xd0,
  a1,
  a2,
  a3,
  vtmp, // vector tmp
  scale,

  // rx tmp
  mxa = 0xa0,
  sp0,
  sp1,
  E_and,
  E_or,
  it,

  // reg.r
  r0 = 0xb0,
  r1,
  r2,
  r3,
  r4,
  r5,
  r6,
  r7,

  // reg.f/e
  e0 = 0xe0,
  e1,
  e2,
  e3,
  f0 = 0xf0,
  f1,
  f2,
  f3,

  ra,
  ds0 =
      0x100, // output value (calculated dataset item) arg0 -> pointer to cache
  ds1,       // arg1 -> pointer to dataset memory at startItem
  ds2,       // arg2 -> start item
  ds3,       // arg3 -> end item
  ds4,
  ds5,
  ds6,
  ds7,
  ds8,            // pointer to cache memory
  ds9,            // pointer to output
  ds10,           // registerValue
  ds11,           // mixBlock
  ds12,           // temporary
  ds13,           // temporary
  ds14,           // temporary
  dspool = 0x120, // ds pool
};

enum { DATASET, PROGRAM };

#define superscalarMul0        6364136223846793005ULL
#define superscalarAdd1        9298411001130361340ULL
#define superscalarAdd2        12065312585734608966ULL
#define superscalarAdd3        9306329213124626780ULL
#define superscalarAdd4        5281919268842080866ULL
#define superscalarAdd5        10536153434571861004ULL
#define superscalarAdd6        3398623926847679864ULL
#define superscalarAdd7        9549104520008361294ULL
#define superscalarConstantLen 64

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    do {                                                                       \
      printf("%s not fullfilled\n", #x);                                       \
      for (;;)                                                                 \
        ;                                                                      \
  } while (0)

#define D1(d1)               ((d1 << 16) | 0xff00ffff)
#define D1S1(d1, s1)         ((d1 << 16) | (s1) | 0xff00ff00)
#define D1S2(d1, s1, s2)     ((d1 << 16) | (s1) | (s2 << 8) | 0xff000000)
#define D2S2(d1, d2, s1, s2) ((d1 << 16) | (d1 << 24) | (s1) | (s2 << 8))
#define D1S3                 D2S2

typedef struct instruction_ops {
  // op list
  void (*li)(void *isa, int rd1, int imm);
  void (*mov)(void *isa, int rd, int rs);

  // load & store
  int (*hasPrefetch)(void);
  void (*prefetch)(void *isa, int rs1);
  void (*ld)(void *isa, int rd, int rs1, int offs);
  void (*sd)(void *isa, int rs1, int rs2, int offs);
  void (*ldp)(void *isa, int rd1, int rd2, int rs1, int offs);
  void (*sdp)(void *isa, int rs1, int rs2, int t, int offs);

  // bits
  void (*andi)(void *isa, int rd1, int rs1, int imm);
  void (*lsri)(void *isa, int rd1, int rs1, int imm);
  void (*lsli)(void *isa, int rd1, int rs1, int imm);
  void (*xor_)(void *isa, int rd1, int rs1, int rs2);
  void (*xorw)(void *isa, int rd1, int rs1, int rs2);
  // lo32 xor, hi32 remain unchanged
  void (*and_)(void *isa, int rd1, int rs1, int rs2);
  void (*or_)(void *isa, int rd1, int rs1, int rs2);
  void (*ror)(void *isa, int rd1, int rs1, int rs2);
  void (*rol)(void *isa, int rd1, int rs1, int rs2);
  void (*rori)(void *isa, int rd1, int rs1, int imm);
  void (*roli)(void *isa, int rd1, int rs1, int imm);

  // integer funcs
  void (*add)(void *isa, int rd1, int rs1, int rs2);
  void (*addi)(void *isa, int rd1, int rs1, int imm);
  void (*sub)(void *isa, int rd1, int rs1, int rs2);
  void (*mul)(void *isa, int rd1, int rs1, int rs2);
  void (*mulh)(void *isa, int rd1, int rs1, int rs2);
  void (*mulhu)(void *isa, int rd1, int rs1, int rs2);

  // vector double float funcs
  void (*vldpw)(void *isa, int rd1, int rs1, int offs);
  void (*vld)(void *isa, int rd1, int rs1, int offs);
  void (*vldp)(void *isa, int rd1, int rd2, int rs1, int offs);
  void (*vsdp)(void *isa, int rs1, int rs2, int rd1, int offs);
  void (*vbitmask)(void *isa, int rd, int imm, int w, int sl, int n);
  void (*vand)(void *isa, int rd1, int rs1, int rs2);
  void (*vor)(void *isa, int rd1, int rs1, int rs2);
  void (*vfswap)(void *isa, int rd1);
  void (*vfadd)(void *isa, int rd1, int rs1, int rs2);
  void (*vfsub)(void *isa, int rd1, int rs1, int rs2);
  void (*vfxor)(void *isa, int rd1, int rs1, int rs2);
  void (*vfmul)(void *isa, int rd1, int rs1, int rs2);
  void (*vfdiv)(void *isa, int rd1, int rs1, int rs2);
  void (*vfsqrt)(void *isa, int rd1, int rs1);

  // 00 even, 01 -, 02 +, 03 zeros
  void (*sfrm)(void *isa, int rs1);

  // control
  void (*brk)(void *isa);
  void (*b)(void *isa, int offs);
  void (*blt)(void *isa, int rs1, int rs2, int offs);
  void (*beq)(void *isa, int rs1, int rs2, int offs);
  void (*bne)(void *isa, int rs1, int rs2, int offs);

  void (*auipc)(void *isa, int rd1, int offs);
  void (*ret)(void *isa);
  void (*entry)(void *isa);
  void (*exit)(void *isa);
  void (*nop)(void *isa);
} instruction_ops_t;

enum {
  RXAI_REG64,
  RXAI_REG32,
};

typedef struct rxaX {
  int mode;
  int type;
  int xpoolId;
  int xslot;
} rxaX_t;

typedef struct jrx_base {
  char *name;
  uint8_t *code;
  uint8_t *dlog;
  int pos;
  int lastP;
  int lastdevregpool;
  int lastgenregpool;
  int size;
  int *xslot;
  int *vslot;
  int *M;
  int _lock;
  instruction_ops_t *ops;
  void *pdata;
  rxaX_t *rslot;
  void *ofo;
  int id;
  int dst_change[256];
} jrx_base_t;

typedef struct jrx_data {
  void *data;
} jrx_data_t;

#define O_Pos(w, x, y) (w * x + y) * 4

#define OENC(dev, w, x, y, c)                                                  \
  do {                                                                         \
    jrx_base_t *base_ = (jrx_base_t *)dev;                                     \
    *(uint32_t *)(base_->code + base_->pos + O_Pos(w, x, y)) = (c);            \
  } while (0)

#define OGET(dev, w, x, y) *(uint32_t *)(dev->code + dev->pos + O_Pos(w, x, y))

#define ENC(dev, c, dep, stg, _cy)                                             \
  do {                                                                         \
    jrx_base_t *base_                       = (jrx_base_t *)dev;               \
    *(uint32_t *)(base_->code + base_->pos) = (c);                             \
    if (base_->dlog)                                                           \
      *(uint64_t *)(base_->dlog + base_->pos * 2) =                            \
          ((uint64_t)(dep) << 16) | (stg << 8) | _cy;                          \
    base_->pos += 4;                                                           \
  } while (0)

#define ENC64(dev, dat)                                                        \
  do {                                                                         \
    jrx_base_t *base_                       = (jrx_base_t *)dev;               \
    *(uint64_t *)(base_->code + base_->pos) = (dat);                           \
    base_->pos += 8;                                                           \
  } while (0)

#define CUT(x, a, n, b) ((((x) >> a) & ((1 << n) - 1)) << b)

jrx_base_t *initJrxBase(int sz, uint8_t *c, int *slots, uint8_t *d);
void exitJrxBase(jrx_base_t *dev);
void reset(jrx_base_t *base);
void iseek(jrx_base_t *base, int offs);
int locked(jrx_base_t *base);
void lock(jrx_base_t *base);
int codeSize(jrx_base_t *base);
int allocX(jrx_base_t *base);
int resvX(jrx_base_t *base);
void freeX(jrx_base_t *base, int x);
int allocV(jrx_base_t *base);
void freeV(jrx_base_t *base, int x);
void link_(jrx_base_t *base, jrx_base_t *isa);
void printIns(uint64_t ins);
void reorder(uint8_t *c2, int end);
void analyze(uint8_t *c2, int end, int reset);
void Jrx_set_stage(int stage);
int Jrx_get_stage(void);
#endif
