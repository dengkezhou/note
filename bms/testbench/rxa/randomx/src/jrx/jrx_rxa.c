#include "jrx_rxa.h"
#include "isa-rxa.h"
#include "isa.h"
#include "program.h"
#include "reciprocal.h"
#include "rxa.h"
#include "superscalar.h"
#include "virtual_memory.h"
#include <bytecode_machine.h>
#include <jrx_core.h>
#include <stddef.h>
#include <common.h>
#include <asm/arch-c920/base-map.h>
#include <rand48.h>

#define JRX_SIZE_XPOOL (8 * GEN_REG_XPOOL)
#define JRX_SIZE_IMM   0x300
#define OFFSPREFETCH   JRX_SIZE_IMM
#define OFFSREGF       OFFSPREFETCH + 0x80
#define OFFSCODE       OFFSREGF + 0x180
#define JRX_SIZE_P0    (0x400 + OFFSCODE)
#define JRX_SIZE_P2    0x200
#define JRX_SIZE_P1    (JRX_SIZE_RXA - JRX_SIZE_P0 - JRX_SIZE_P2)
#define JRX_SIZE_RXA   0x3000
#define JRX_SIZE_P3    (0x4000 - JRX_SIZE_RXA)
#define OFFSDAG        0x0
#define JRX_SIZE       (JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2 + JRX_SIZE_P3)
#define OFFSSCRATCHPAD 0x200000 // need align with SCRATCHPAD

extern void rxaReset(jrx_base_t *base);
static size_t getCodeSize(void *jrx) { return 0; }

static void rxa_data_init(rxa_cfg_t *cfg) {
  if (!cfg)
    return;

  memset(cfg->e_or, 0, sizeof(cfg->e_or));
  cfg->e_and[0] = 0xffffffff;
  cfg->e_and[1] = 0x00ffffff;
  cfg->e_and[2] = 0xffffffff;
  cfg->e_and[3] = 0x00ffffff;
  memset(cfg->r, 0, sizeof(cfg->r));
  SET(cfg_cond_offs) = 8;
  SET(en_regf)       = true;
  SET(offs_prfc)     = OFFSPREFETCH;
  SET(offs_regf)     = OFFSREGF;
  SET(offs_code)     = OFFSCODE;
  SET(offs_spad)     = OFFSSCRATCHPAD;
  SET(offs_dag)      = OFFSDAG;
#if 1
	SET(dmamsk)        = RANDOMX_DATASET_BASE_SIZE-64;
#else
	SET(dmamsk)        = 2147483648UL - 64;
#endif
}

static void rxa_config(jrx_rxa_t *dev, int mode, void *data) {
  int regR0 = dr0;
  uint64_t value[2];

  if (!dev)
    return;

  switch (mode) {
  case RXA_CONFIG_R: {
    char cfg_r[4];
    ProgramConfiguration_t *pcfg = (ProgramConfiguration_t *)data;

    cfg_r[0] = regR0 + pcfg->readReg0;
    cfg_r[1] = regR0 + pcfg->readReg1;
    cfg_r[2] = regR0 + pcfg->readReg2;
    cfg_r[3] = regR0 + pcfg->readReg3;
    rxa_set_cfg_r(dev->drv, cfg_r);
  } break;
  case RXA_CONFIG_E_OR:
    rxa_set_cfg_e_or(dev->drv, (uint32_t *)data);
    break;
  case RXA_CONFIG_DATASET:
    rxa_set_dag_offs(dev->drv, *(unsigned long *)data);
    break;
  case RXA_CONFIG_XPOOL:
    rxa_set_xpool(dev->drv, (uint64_t *)data, dev->xlen);
    break;
	case RXA_CONFIG_SCALE:
		value[0] = 0x80f0000000000000;
		value[1] = 0x80f0000000000000;
		rxa_dbg_writeq(dev->drv, v29, value);
		break;
	case RXA_CONFIG_GREG_XPOOL:
		// load xpool
		for (int i = 0; i < (GEN_REG_XPOOL - RESV_TMP); i++)
			rxa_dbg_writeq(dev->drv, dxpool0 + GEN_REG_XPOOL - 1 - i, (uint64_t *)data + RESV_TMP + i);
		break;
  default:
    printf("RXA do not support this config: %d\n", mode);
    return;
  }
}

void rxa_callback(void *data) {
  jrx_rxa_t *dev = (jrx_rxa_t *)data;
#if 0
	rxa_dump(dev->drv);
	rxa_dump_inner_reg(dev->drv);
#endif
  dev->complete = true;
}

int step_avp = 0;
void exitJrxRxa(void *jrx);
extern int ilog2(int i);
int jrxNum               = 0;
void *initJrxRxa(int id) {
  jrx_rxa_t *dev = (jrx_rxa_t *)allocMemoryPages(sizeof(jrx_rxa_t));
  if (!dev) {
    printf("Jrx rxa malloc Error\n");
    return NULL;
  }
	dev->id = id;
  rxa_data_init(&dev->rdata);
  dev->drv = itcs_rxa_init(dev->id, &dev->rdata, rxa_callback, dev);
  if (!dev->drv) {
    printf("RXA driver init err\n");
    goto err0;
  }
  rxa_set_fetch_width(dev->drv, ilog2(param.fetch_width));
  jrxNum    = 0;
  dev->code     =  (uint8_t *)ITCS_RXA_IRAM_ADDR(dev->id);
  step_avp      = 0;
  dev->mode     = ISA_RXA;
  uint8_t *dlog = NULL;
  dev->p0       = initIsa(dev->mode, JRX_SIZE_P0, dev->code, dev->slots, dlog);
  dev->p1 = initIsa(dev->mode, JRX_SIZE_P1, dev->code + JRX_SIZE_P0, dev->slots,
                    dlog);
  dev->p2 = initIsa(dev->mode, JRX_SIZE_P2,
                    dev->code + JRX_SIZE_P0 + JRX_SIZE_P1, dev->slots, dlog);
  dev->p3 = initIsa(dev->mode, JRX_SIZE_P3,
                    dev->code + JRX_SIZE_P0 + JRX_SIZE_P1 + JRX_SIZE_P2,
                    dev->slots, dlog);
  cfg_literPool(dev->p0, dev);
  cfg_literPool(dev->p1, dev);
  cfg_literPool(dev->p2, dev);
  cfg_literPool(dev->p3, dev);
  // set default state
  dev->complete = false;
	
	if (!id) {
#if defined(__aarch64__) || defined(__riscv)
		dev->sjrx = get_jrx_by_name("baseDev");
#else
		dev->sjrx = get_jrx_by_name("x86Dev");
#endif
		if (!dev->sjrx) {
			printf("RXA get jrx for dataset err\n");
			goto err1;
		}
		dev->sjrxDev = dev->sjrx->init_jrx(0);
	} else
		dev->sjrx = NULL;

  printf("new RXA device: %d(%p)\n", JRX_SIZE, dev);
  return dev;

err1:
  itcs_rxa_exit(dev->drv);
err0:
  exitJrxRxa(dev);
  return NULL;
}

void exitJrxRxa(void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;

  if (dev->sjrx)
    dev->sjrx->exit_jrx(dev->sjrxDev);

  exitIsa(dev->mode, dev->p0);
  exitIsa(dev->mode, dev->p1);
  exitIsa(dev->mode, dev->p2);
  exitIsa(dev->mode, dev->p3);

  itcs_rxa_exit(dev->drv);
  freePagedMemory(dev, sizeof(jrx_rxa_t));
}

static void enableAll(void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;

	if (dev->sjrx)
  	dev->sjrx->enableAll(dev->sjrxDev);
}

static void enableWriting(void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;

	if (dev->sjrx)
  	dev->sjrx->enableWriting(dev->sjrxDev);
}

static void enableExecution(void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;

	if (dev->sjrx)
  	dev->sjrx->enableExecution(dev->sjrxDev);
}

// private:
#define INS(x) if (instr->opcode < ceil_##x)
#if 1
#define MSG(x)
#else
#define MSG(x) printf("%d: %s\n", pc, #x)
#endif

static inline void load(void *dev, int x, int msrc, int imm, int msk) {
  // jrx_base_t *isa = (jrx_base_t *)dev;
  // rxaX_t *t0;
  if (msrc) {
    // t0 = rxaAllocX(isa, RXAI_REG32);
    imm &= msk - 1;
    // R_addi(dev, t0->xpoolId, msrc, imm);
    R_addi(dev, x, msrc, imm);
    // R_ld(dev, x, t0->xpoolId, log2(msk), 0);
    // R_ld(dev, x, t0->xpoolId, ((msk == RANDOMX_SCRATCHPAD_L1) ? 14 : 18), 0);
    R_ld(dev, x, x, ((msk == RANDOMX_SCRATCHPAD_L1) ? 14 : 18), 0);
    // rxaFreeX(isa, t0);
  } else {
    imm &= ScratchpadL3Mask;
    // R_ld(dev, x, dzero, log2(RANDOMX_SCRATCHPAD_L3), imm);
    R_ld(dev, x, dzero, 21, imm);
  }
}

static inline void loadvf(void *dev, int x, int msrc, int imm, int msk) {
  jrx_base_t *isa = (jrx_base_t *)dev;
  rxaX_t *t0      = rxaAllocX(isa, RXAI_REG32);

  imm &= msk - 1;
  // printf("enc ldvf, msrc=%d, imm=%d, msk=%d\n", msrc, imm, (msk - 1) &
  // ~7);
  R_addi(dev, t0->xpoolId, msrc, imm);

  // R_vld_w(dev, x, t0->xpoolId, log2(msk), 0);
  R_vld_w(dev, x, t0->xpoolId, ((msk == RANDOMX_SCRATCHPAD_L1) ? 14 : 18), 0);
  rxaFreeX(isa, t0);
}

// static cache_hit_t hit = {0};
extern InstructionGenerator RXAengine[256];
static void generateProgram(void *jrx, Program_t *prog,
                            ProgramConfiguration_t *pcfg) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;
  jrx_base_t *p0 = (jrx_base_t *)dev->p0;
  jrx_base_t *p1 = (jrx_base_t *)dev->p1;
  jrx_base_t *p2 = (jrx_base_t *)dev->p2;

  Jrx_set_stage(PROGRAM);
  dev->xpool_start = JRX_SIZE_IMM - 8;
  dev->xpool_end   = JRX_SIZE_IMM - JRX_SIZE_XPOOL;
  dev->literal_pos = dev->xpool_end - 8;
  dev->literal_end = 0;
  dev->xlen        = 0;

  // reset(p1);
  // ofo_reset((ofo_t *)p1->ofo);
  dev->pcfg = pcfg;

  // set cfg_r
  rxa_config(dev, RXA_CONFIG_R, pcfg);
  if (!locked(p0)) {
    reset(p0);
    ofo_reset((ofo_t *)p0->ofo);

    reset(p1);
    ofo_reset((ofo_t *)p1->ofo);
    iseek(p0, sizeof(RegisterFile_t) + sizeof(MemoryRegisters_t) + OFFSREGF);

    /* set scaler */
    ENC64(p0, 0x80f0000000000000);
    ENC64(p0, 0x80f0000000000000);
    /* set iterations */
    ENC64(p0, RANDOMX_PROGRAM_ITERATIONS);

    // seek to code offs
    iseek(p0, OFFSCODE);
#if 0
    // load xpool
    for (int i = RESV_TMP; i < GEN_REG_XPOOL; i++)
      R_ld(p0, dxpool0 + i, dzero, RXAI_OFFS_SRAM,
           JRX_SIZE_IMM - 8 - 8 * (i - RESV_TMP));
#endif
    // zero integer registers
    for (int i = 0; i < 8; i++)
      R_swap(p0, dr0 + i, dzero);

    // load ma, mx pointer & need`t to load dataset point
    R_ld(p0, dmxa, dzero, RXAI_OFFS_SRAM, 256 + OFFSREGF);

    // load reg.a
    R_vldp(p0, da0, da1, dzero, RXAI_OFFS_SRAM, 192 + OFFSREGF);
    R_vldp(p0, da2, da3, dzero, RXAI_OFFS_SRAM, 224 + OFFSREGF);

    // load scale mask
    //R_vld(p0, dscale, dzero, RXAI_OFFS_SRAM, 272 + OFFSREGF);

    R_ld(p0, dit, dzero, RXAI_OFFS_SRAM, 288 + OFFSREGF);

    R_mov(p0, dxtmp, dmxa);
    dev->loop_start = isaSize(p0);
    /* prefetch first 64bytes dataset */
    R_prfc(p0, dzero, dmxa, (1 << 2) | RXAI_RS_HI32, 0);

    // init sp0, sp1
    R_rxssp(p0, dsp0, dxtmp, dsp1);

    // 1. xor r0~r7 v2
    R_vldq_xor(p0, 2, dsp0, RXAI_OFFS_SPAD, 0);

    // 2. load reg.f
    R_vldq_w(p0, df0, dsp1, RXAI_OFFS_SPAD, 0);
    for (int i = 0; i < 4; i++)
      R_vcvt_d_w(p0, df0 + i, df0 + i, RXAI_WTOD_FTYPE);

    // 3. load reg.e
    R_vldq_w(p0, de0, dsp1, RXAI_OFFS_SPAD, 32);
    for (int i = 0; i < 4; i++)
      R_vcvt_d_w(p0, de0 + i, de0 + i, RXAI_WTOD_ETYPE);

    R_link(p0, p1, 0);
    lock(p0);

    R_end(p0);
  } else {
    iseek(p0, OFFSCODE);
    // memset(p1->code, 0, p1->size);
  }

  for (int i = dr0; i <= dr7; i++)
    p1->dst_change[i] = 0;

  POKE(gen256, "gen 256 12 code");
  // 4. exec 256 instructions
  for (int i = 0; i < getProgramSize(); ++i) {
    Instruction_t *instr = getPGInstruction(prog, i);
    RXAengine[instr->opcode](p1, instr, i);
  }
  R_link(p1, p2, 0);
  PEEK(gen256);
  R_end(p1);
  // printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n");
  // store_cache_hit(&hit, &tmphit);
  if (!locked(p2)) {
    reset(p2);

    ofo_reset((ofo_t *)p2->ofo);
    // 5. mx ^= r[readReg2] ^ r[readReg3];
    // 7. swap mx, ma
    R_rxsmxa(p2, dmxa);
    // prefetch
    // R_prfc(p2, zero, mxa, (1 << 2) | RXAI_RS_HI32, 0);
		R_wprfc(p2, 2);

    // 8. xor r0~7 with dataset
    // 9. store r0~7
    R_vldq_xor(p2, 2, dzero, 0, OFFSPREFETCH);
    R_vstq(p2, dsp1, 2, RXAI_OFFS_SPAD, 0);

    // 10. xor group F and group E registers
    for (int i = 0; i < 4; i++)
      R_vxor(p2, df0 + i, de0 + i, df0 + i);

    // 11. Store FP registers to scratchpad (spAddr0)
    R_vstq(p2, dsp0, df0, RXAI_OFFS_SPAD, 0);

    R_addi(p2, dit, dit, -1);

    R_mov(p2, dxtmp, dzero);
    // loop again
    // printf("offs %d, dev->loop_start %d, isaSize(p2) %d, JRX_SIZE_P1 %d\n",
    // offs, dev->loop_start, isaSize(p2), JRX_SIZE_P1);
    R_link(p2, p0, dev->loop_start / 4);
    R_end(p2);
    lock(p2);
  }
}

static void generateProgramLight(void *jrx, Program_t *prog,
                                 ProgramConfiguration_t *pcfg,
                                 uint32_t datasetOffset) {}

static void generateSuperscalarHash(void *jrx, SuperscalarProgram_t *programs,
                                    cvector reciprocalCache) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;
  dev->sjrx->generateSuperscalarHash(dev->sjrxDev, programs, reciprocalCache);
}

static void generateDatasetInitCode(void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;
  dev->sjrx->generateDatasetInitCode(dev->sjrxDev);
}

static void rxa_handle(RegisterFile_t *regf, MemoryRegisters_t *mem,
                       uint8_t *scratchpad, uint64_t its, void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;
  uint64_t datasetOffs = mem->memory - (uint8_t *)rxa_get_ddr(dev->drv);
	jrx_base_t *p1       = (jrx_base_t *)dev->p1;
  // set regf and mem
  memcpy(dev->code + OFFSREGF, regf, sizeof(RegisterFile_t));
  memcpy(dev->code + sizeof(RegisterFile_t) + OFFSREGF, mem,
         sizeof(MemoryRegisters_t));

#if 0
	printf("Start rxa vm scratchpad: \n");
	for (int i = 0; i < (0x200000 / 8); i++) {
		printf("0x%016lx ", *((uint64_t *)scratchpad + i));
		if (!((i + 1) % 8))
			printf("\n");
	}
	printf("\n");
#endif
  // set e_or
  rxa_config(dev, RXA_CONFIG_E_OR, regf->f);
  rxa_config(dev, RXA_CONFIG_DATASET, &datasetOffs);
  rxa_config(dev, RXA_CONFIG_XPOOL, dev->xpool);
  rxa_config(dev, RXA_CONFIG_SCALE, NULL);
  rxa_config(dev, RXA_CONFIG_GREG_XPOOL, dev->code + dev->xpool_end);
#if 0
	printf("16K memory: %p, 0x%lx\n", dev->code, *(uint64_t *)(dev->code + 0x300));
	for (int i = 0; i < (0x4000 / 4); i++) {
		printf("0x%08x ", *((uint32_t *)dev->code + i));
		if (!((i + 1) % 8))
			printf("\n");
	}
#endif
	//rxa_set_stepmode(dev->drv, RXAI_STEP, 1);
  rxa_start(dev->drv);
  for (;;) {
    if (dev->complete) {
      dev->complete = false;
			ofo_reset((ofo_t *)p1->ofo);
			rxaReset(p1);
      break;
    }
    udelay(1);
  }

	rxa_set_regf(dev->drv, 1, OFFSREGF);
	while (!rxa_wait_regf_ready(dev->drv))
		udelay(1);

  memcpy(regf, dev->code + OFFSREGF, sizeof(RegisterFile_t));

	rxa_memset(dev->drv, JRX_SIZE_P0, JRX_SIZE_P1 - 0x20);
#if 1
	printf("RegisterFile_t\n");
	for (int i = 0; i < (256 / 4); i++) {
		printf("0x%08x ", *((uint32_t *)regf + i));
		if (!((i + 1) % 8))
			printf("\n");
	}
#endif
#if 0
	printf("\nFinish rxa vm scratchpad: \n");
	for (int i = 0; i < (0x200000 / 8); i++) {
		printf("0x%016lx ", *((uint64_t *)scratchpad + i));
		if (!((i + 1) % 8))
			printf("\n");
	}
#endif
}

static ProgramFunc *getProgramFunc(void *jrx) {

  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;
#ifdef __GNUC__
  __builtin___clear_cache((char *)(dev->code), (char *)(dev->code + JRX_SIZE));
#endif
  return (ProgramFunc *)rxa_handle;
}
//#define DECR_DBG
#ifdef DECR_DBG
enum { CRYPTO_KEY, CRYPTO_STATE, CRYPTO_IN, CRYPTO_OUT, CRYPTO_PRIV };

static unsigned long cvtADDR(int id, uint32_t addr) {
	if (addr >= 0x200000)
		return ITCS_RXA_DRAM_ADDR(id) + addr - 0x200000;
	else
		return ITCS_RXA_IRAM_ADDR(id) + addr;
}

static void dump_crypto(int id, rxa_cipher_decr_t *decr, char *str, int mode) {
	printf("\n%s\n", str);
	switch (mode)	{
		case CRYPTO_KEY:
			printf("addr 0x%lx, id %d, addr 0x%x\n", cvtADDR(id, decr->keyaddrl), id, decr->keyaddrl);
			for (int i = 0; i < decr->keylen/8; i++) {
				printf("0x%08lx ", *((uint64_t *)cvtADDR(id, decr->keyaddrl) + i));
				if (!((i + 1) % 8))
					printf("\n");
				if (i > 16)
				  break;
			}
			break;
		case CRYPTO_STATE:
			printf("addr 0x%lx, id %d, addr 0x%x\n", cvtADDR(id, decr->stateaddrl), id, decr->stateaddrl);
			for (int i = 0; i < decr->statelen/8; i++) {
				printf("0x%08lx ", *((uint64_t *)cvtADDR(id, decr->stateaddrl) + i));
				if (!((i + 1) % 8))
					printf("\n");

				if (i > 16)
				  break;
			}
			break;
		case CRYPTO_IN:
			{
				printf("addr 0x%lx, id %d, addr 0x%x\n", cvtADDR(id, decr->inaddrl), id, decr->inaddrl);
				for (int i = 0; i < decr->inlen/8; i++) {
					printf("0x%08lx ", *((uint64_t *)cvtADDR(id, decr->inaddrl) + i));
					if (!((i + 1) % 8))
						printf("\n");

					if (i > 16)
						break;
				}
			}
			break;
		case CRYPTO_OUT:
			printf("addr 0x%lx, id %d, addr 0x%x\n", cvtADDR(id, decr->outaddrl), id, decr->outaddrl);
			for (int i = 0; i < decr->outlen/8; i++) {
				printf("0x%08lx ", *((uint64_t *)cvtADDR(id, decr->outaddrl) + i));
				if (!((i + 1) % 8))
					printf("\n");

				if (i > 16)
					break;
			}
			printf("CRYPTO_OUT\n");
			break;
		case CRYPTO_PRIV:
			printf("addr 0x%lx, id %d, addr 0x%x\n", cvtADDR(id, decr->privaddrl), id, decr->privaddrl);
			for (int i = 0; i < decr->privlen/8; i++) {
				printf("0x%08lx ", *((uint64_t *)cvtADDR(id, decr->privaddrl) + i));
				if (!((i + 1) % 8))
					printf("\n");

				if (i > 16)
				  break;
			}
			break;
	}
}
#endif

#define OFFSCIPHERDECR (0x80)
#define OFFSCIPHERIN   (0x100)
#define OFFSCIPHEROUT  (0x600)
#define OFFSCIPHER4R4  (0x700)  

#define isPbuf(addr) ((addr >= ITCS_RXA_IRAM_ADDR(0)) && (addr <= ITCS_RXA_IRAM_ADDR(27)))
#define isScratchpad(addr) ((addr >= ITCS_RXA_DRAM_ADDR(0)) && (addr <= ITCS_RXA_DRAM_ADDR(27)))

static int setRXAaddr(uint8_t *buf, const uint8_t *in, int len) {
	unsigned long addr = (unsigned long)buf;
	memcpy(buf, in, len);

	if (isPbuf(addr))
		return (addr & (JRX_SIZE - 1));

	return -1;
}

int cipherUpdate(void *jrx, int crypto_mode, const uint8_t *in, int inlen,
                 uint8_t *out, int outlen, void *priv) {
  jrx_rxa_t *dev          = (jrx_rxa_t *)jrx;
  jrx_base_t *p           = (jrx_base_t *)dev->p3;
  rxa_cipher_decr_t *decr = (rxa_cipher_decr_t *)(p->code + OFFSCIPHERDECR);
	uint8_t *code = p->code;
	int offs = OFFSCIPHERIN;
  uint32_t temp;
	bool spd = isScratchpad((unsigned long)out) ? true : false;
  uint32_t aes1rstate[]   = {0xd7983aad, 0xcc82db47, 0x9fa856de, 0x92b52c0d,
                           0xace78057, 0xf59e125a, 0x15c7b798, 0x338d996e,
                           0xe8a07ce4, 0x5079506b, 0xae62c7d0, 0x6a770017,
                           0x7e994948, 0x79a10005, 0x07ad828d, 0x630a240c};
  uint32_t aes1rxkey[]    = {0x06890201, 0x90dc56bf, 0x8b24949f, 0xf6fa8389,
                          0xed18f99b, 0xee1043c6, 0x51f4e03c, 0x61b263d1};
  uint32_t aes1rkey[]     = {0xb4f44917, 0xdbb5552b, 0x62716609, 0x6daca553,
                         0x0da1dc4e, 0x1725d378, 0x846a710d, 0x6d7caf07,
                         0x3e20e345, 0xf4c0794f, 0x9f947ec6, 0x3f1262f1,
                         0x49169154, 0x16314c88, 0xb1ba317c, 0x6aef8135};
  uint32_t aes1rmutikey[] = {
      0xb4f44917, 0xdbb5552b, 0x62716609, 0x6daca553, 0x0da1dc4e, 0x1725d378,
      0x846a710d, 0x6d7caf07, 0x3e20e345, 0xf4c0794f, 0x9f947ec6, 0x3f1262f1,
      0x49169154, 0x16314c88, 0xb1ba317c, 0x6aef8135, 0x06890201, 0x90dc56bf,
      0x8b24949f, 0xf6fa8389, 0xed18f99b, 0xee1043c6, 0x51f4e03c, 0x61b263d1};
  uint32_t aes4rkey[] = {
      0x99e5d23f, 0x2f546d2b, 0xd1833ddb, 0x6421aadd, 0xa5dfcde5, 0x06f79d53,
      0xb6913f55, 0xb20e3450, 0x171c02bf, 0x0aa4679f, 0x515e7baf, 0x5c3ed904,
      0xd8ded291, 0xcd673785, 0xe78f5d08, 0x85623763, 0x229effb4, 0x3d518b6d,
      0xe3d6a7a6, 0xb5826f73, 0xb272b7d2, 0xe9024d4e, 0x9c10b3d9, 0xc7566bf3,
      0xf63befa7, 0x2ba9660a, 0xf765a38b, 0xf273c9e7, 0xc0b0762d, 0x0c06d1fd,
      0x915839de, 0x7a7cd609};

  reset(p);
  ofo_reset((ofo_t *)p->ofo);
	
	memset(decr, 0, sizeof(rxa_cipher_decr_t));
  /* Common settings */
  decr->crypto_type = crypto_mode;
  decr->keylen      = 0;
  if (crypto_mode == RXA_AES1RX4_MUTI) {
		decr->inlen     = 64;
		decr->inaddrl   = setRXAaddr(code + offs, priv, decr->inlen);
		offs += decr->inlen;

    decr->privaddrl = 0x200000; // set in dram
    decr->privlen   = inlen;
		/* scratchpad for a special purpose, do not need memcpy */
		//memcpy(rxa_get_spad(dev->drv), in, decr->privlen); 
	} else if (crypto_mode == RXA_AES1RX4_HASH) {
		decr->inaddrl = 0x200000;
		decr->inlen = inlen;
		/* scratchpad for a special purpose，do not need memcpy */
		//memcpy(rxa_get_spad(dev->drv), in, decr->inlen);
  } else {
		decr->inlen     = inlen;
		decr->inaddrl   = setRXAaddr(code + offs, in, decr->inlen);
		offs += decr->inlen;

    decr->privaddrl = (unsigned long)priv;
    decr->privlen   = 0;
  }
	decr->outaddrl   = spd ? 0x200000 : (JRX_SIZE_RXA + OFFSCIPHEROUT);
  decr->outlen     = outlen;
  decr->next_decrl = 0;

  switch (crypto_mode) {
  case RXA_BLAKE2B:
    R_rxblk2b(p, 0);
    break;
  case RXA_AES1RX4:
		decr->keylen   = sizeof(aes1rkey);
		decr->keyaddrl = setRXAaddr(code + offs, (uint8_t *)aes1rkey, decr->keylen);
		offs += decr->keylen;
    R_rxaes1rx4(p, 0, 0);
    break;
  case RXA_AES1RX4_HASH:
		decr->keylen     = sizeof(aes1rxkey);
    decr->keyaddrl   = setRXAaddr(code + offs, (uint8_t *)aes1rxkey, decr->keylen);
		offs += decr->keylen;
		
		decr->statelen   = sizeof(aes1rstate);
    decr->stateaddrl = setRXAaddr(code + offs, (uint8_t *)aes1rstate, decr->statelen);
		offs += decr->statelen;

    R_rxaes1rx4(p, 0, 1);
    break;
  case RXA_AES1RX4_MUTI:
		decr->keylen     = sizeof(aes1rmutikey);
    decr->keyaddrl   = setRXAaddr(code + offs, (uint8_t *)aes1rmutikey, decr->keylen);
		offs += decr->keylen;
		
		decr->statelen   = sizeof(aes1rstate);
    decr->stateaddrl = setRXAaddr(code + offs, (uint8_t *)aes1rstate, decr->statelen);
		offs += decr->statelen;

    R_rxaes1rx4(p, 0, 2);
    break;
  case RXA_AES4RX4:
		decr->keylen   = sizeof(aes4rkey);
    decr->keyaddrl = setRXAaddr(code + offs, (uint8_t *)aes4rkey, decr->keylen);
		offs += decr->keylen;
		decr->outaddrl   = spd ? 0x200000 : (JRX_SIZE_RXA + OFFSCIPHER4R4);

    R_rxaes4rx4(p, 0);
    break;
  default:
    printf("Not support this cipher mode: %d\n", crypto_mode);
    return -1;
  }

  rxa_set_cipher_offs(dev->drv, OFFSCIPHERDECR + JRX_SIZE_RXA);
  // set cmd
  R_end(p);
  temp = rxa_get_code_offs(dev->drv);
  rxa_set_code_offs(dev->drv, JRX_SIZE_RXA);
  rxa_start(dev->drv);
  for (;;) {
    if (dev->complete) {
      dev->complete = false;
      break;
    }
    udelay(1);
  }
  rxa_set_code_offs(dev->drv, temp);

#ifdef DECR_DBG
	printf("decr:\n");
	printf("crypto_type: %d\n", decr->crypto_type);
	printf("keyaddr: 0x%08lx, len 0x%x\n", decr->keyaddrl, decr->keylen);
	printf("stateaddr: 0x%08lx, len 0x%x\n", decr->stateaddrl, decr->statelen);
	printf("inaddr: 0x%08lx, len 0x%x\n", decr->inaddrl, decr->inlen);
	printf("outaddr: 0x%08lx, len 0x%x\n", decr->outaddrl, decr->outlen);
	printf("privaddr: 0x%08lx, len 0x%x\n", decr->privaddrl, decr->privlen);
	printf("next_decr: 0x%08lx\n", decr->next_decrl);
	switch(crypto_mode) {
		case RXA_BLAKE2B:
			printf("RXA_BLAKE2B:\n");
			dump_crypto(dev->id, decr, "input", CRYPTO_IN);
			dump_crypto(dev->id, decr, "output", CRYPTO_OUT);
			break;
		case RXA_AES4RX4:
			printf("RXA_AES4RX4:\n");
			dump_crypto(dev->id, decr, "key", CRYPTO_KEY);
			dump_crypto(dev->id, decr, "input", CRYPTO_IN);  
			dump_crypto(dev->id, decr, "output", CRYPTO_OUT);
			break;
		case RXA_AES1RX4_MUTI:
			printf("RXA_AES1RX4_MUTI\n");
			dump_crypto(dev->id, decr, "state", CRYPTO_STATE);
			dump_crypto(dev->id, decr, "key", CRYPTO_KEY);
			dump_crypto(dev->id, decr, "input 2M", CRYPTO_IN);  
			dump_crypto(dev->id, decr, "input", CRYPTO_PRIV);
			dump_crypto(dev->id, decr, "output hash", CRYPTO_OUT);
			break;
		case RXA_AES1RX4_HASH:
			printf("RXA_AES1RX4_HASH\n");
			dump_crypto(dev->id, decr, "state", CRYPTO_STATE);
			dump_crypto(dev->id, decr, "key", CRYPTO_KEY);
			dump_crypto(dev->id, decr, "input", CRYPTO_IN);  
			dump_crypto(dev->id, decr, "output hash", CRYPTO_OUT);
			break;
		case RXA_AES1RX4:
			printf("RXA_AES1RX4:\n");
			dump_crypto(dev->id, decr, "key", CRYPTO_KEY);
			dump_crypto(dev->id, decr, "input", CRYPTO_IN);  
			dump_crypto(dev->id, decr, "output 2M", CRYPTO_OUT);
			break;
	}
#endif
	if (crypto_mode == RXA_AES1RX4) {
		if (decr->inlen == -1)
			while (1);
		memcpy((void *)in, code + OFFSCIPHERIN, decr->inlen);
		//printf("in: %p, code + OFFSCIPHERIN %p, decr->inlen %d\n", in, code + OFFSCIPHERIN, decr->inlen);
	} else if (crypto_mode == RXA_AES1RX4_MUTI) {
		if (decr->inlen == -1)
			while (1);
		memcpy((void *)priv, code + OFFSCIPHERIN, decr->inlen);
		//printf("priv: %p, code + OFFSCIPHERIN %p, decr->inlen %d\n", priv, code + OFFSCIPHERIN, decr->inlen);
	}

	if (!spd && (crypto_mode != RXA_AES4RX4)) {
		if (decr->outlen == -1)
			while (1);
		
		memcpy(out, p->code + OFFSCIPHEROUT, decr->outlen);
		//printf("out: %p, p->code + OFFSCIPHEROUT %p, decr->outlen %d\n", out, p->code + OFFSCIPHEROUT, decr->outlen);
	}
	return 0;
}

int rxaCipherUpdate(void *dev, int crypto_mode, void *in, int inlen, void *out, int outlen,
                    void *priv) {
	jrx_machine_t *mc = (jrx_machine_t *)dev;
  return cipherUpdate(mc->jrxDev, crypto_mode, in, inlen, out, outlen, priv);
}

rxa_device_t *getRXADevice(void *dev) {
	jrx_machine_t *mc = (jrx_machine_t *)dev;
	jrx_rxa_t *rxadev = (jrx_rxa_t *)mc->jrxDev;

	return rxadev->drv;
}

static DatasetInitFunc *getDatasetInitFunc(void *jrx) {
  jrx_rxa_t *dev = (jrx_rxa_t *)jrx;

	return dev->sjrx ? dev->sjrx->getDatasetInitFunc(dev->sjrxDev) : NULL;
}
#define LOAD_XTMP
void r_IADD_RS(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;
  int sl  = Instruction_getModShift(instr);
  int imm = Instruction_getImm32(instr);
  MSG(IADD_RS);
  R_addsl(p1, dst, src, RXAI_RS_FULL, sl);
  if (dst == dr5)
    R_addi(p1, dst, dst, imm);
  p1->dst_change[dst] = isaSize(p1);
}

void r_IADD_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src  = (instr->src & 0x7) + dr0;
  int dst  = (instr->dst & 0x7) + dr0;
  int msrc = src == dst ? 0 : src;
  int msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;
  MSG(IADD_M);
#ifdef LOAD_XTMP
  t0 = rxaAllocX(p1, RXAI_REG32);
  load(p1, t0->xpoolId, msrc, imm, msk);
  R_addsl(p1, dst, t0->xpoolId, FLH(t0), 0);
  rxaFreeX(p1, t0);
#else
  load(p1, dxtmp, msrc, imm, msk);
  R_addsl(p1, dst, dxtmp, RXAI_RS_FULL, 0);
#endif
  p1->dst_change[dst] = isaSize(p1);
}

void r_ISUB_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;
  int imm = Instruction_getImm32(instr);
  MSG(ISUB_R);
  if (src == dst)
    R_addi(p1, dst, dst, -imm);
  else
    R_sub(p1, dst, src, RXAI_RS_FULL, dst);

  p1->dst_change[dst] = isaSize(p1);
}

void r_ISUB_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src  = (instr->src & 0x7) + dr0;
  int dst  = (instr->dst & 0x7) + dr0;
  int msrc = src == dst ? 0 : src;
  int msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(ISUB_M);
#ifdef LOAD_XTMP
  t0 = rxaAllocX(p1, RXAI_REG32);
  load(p1, t0->xpoolId, msrc, imm, msk);
  R_sub(p1, dst, t0->xpoolId, FLH(t0), dst);
  rxaFreeX(p1, t0);
#else
  load(p1, dxtmp, msrc, imm, msk);
  R_sub(p1, dst, dxtmp, RXAI_RS_FULL, dst);
#endif
  p1->dst_change[dst] = isaSize(p1);
}

void r_IMUL_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src    = (instr->src & 0x7) + dr0;
  int dst    = (instr->dst & 0x7) + dr0;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(IMUL_R);
  if (src == dst) {
    t0 = rxaResvX(p1, RXAI_REG32, RXA_DEV_REG_XPOOL);
    if (t0)
      set_resvLiteralPool(p1, t0, t0->mode, imm);
    else {
      t0 = rxaAllocX(p1, RXAI_REG32);
      R_li(p1, t0->xpoolId, imm);
    }
    R_mul(p1, dst, t0->xpoolId, FLH(t0), dst);
    rxaFreeX(p1, t0);
  } else
    R_mul(p1, dst, src, RXAI_RS_FULL, dst);

  p1->dst_change[dst] = isaSize(p1);
}

void r_IMUL_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src  = (instr->src & 0x7) + dr0;
  int dst  = (instr->dst & 0x7) + dr0;
  int msrc = src == dst ? 0 : src;
  int msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(IMUL_M);
#ifdef LOAD_XTMP
  t0 = rxaAllocX(p1, RXAI_REG32);
  load(p1, t0->xpoolId, msrc, imm, msk);
  R_mul(p1, dst, t0->xpoolId, FLH(t0), dst);
  rxaFreeX(p1, t0);
#else
  load(p1, dxtmp, msrc, imm, msk);
  R_mul(p1, dst, dxtmp, RXAI_RS_FULL, dst);
#endif
  p1->dst_change[dst] = isaSize(p1);
}

void r_IMULH_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;

  MSG(IMULH_R);
  R_mulhu(p1, dst, src, dst);

  p1->dst_change[dst] = isaSize(p1);
}

void r_IMULH_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src  = (instr->src & 0x7) + dr0;
  int dst  = (instr->dst & 0x7) + dr0;
  int msrc = src == dst ? 0 : src;
  int msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(IMULH_M);
#ifdef LOAD_XTMP
  t0 = rxaAllocX(p1, RXAI_REG32);
  load(p1, t0->xpoolId, msrc, imm, msk);
  R_mulhu(p1, dst, t0->xpoolId, dst);
  rxaFreeX(p1, t0);
#else
  load(p1, dxtmp, msrc, imm, msk);
  R_mulhu(p1, dst, dxtmp, dst);
#endif
  p1->dst_change[dst] = isaSize(p1);
}

void r_ISMULH_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;

  MSG(ISMULH_R);
  R_mulh(p1, dst, src, dst);

  p1->dst_change[dst] = isaSize(p1);
}

void r_ISMULH_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src  = (instr->src & 0x7) + dr0;
  int dst  = (instr->dst & 0x7) + dr0;
  int msrc = src == dst ? 0 : src;
  int msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(ISMULH_M);
#ifdef LOAD_XTMP
  t0 = rxaAllocX(p1, RXAI_REG32);
  load(p1, t0->xpoolId, msrc, imm, msk);
  R_mulh(p1, dst, t0->xpoolId, dst);
  rxaFreeX(p1, t0);
#else
  load(p1, dxtmp, msrc, imm, msk);
  R_mulh(p1, dst, dxtmp, dst);
#endif
  p1->dst_change[dst] = isaSize(p1);
}

void r_IMUL_RCP(jrx_base_t *p1, Instruction_t *instr, int pc) {
  rxaX_t *t0  = NULL;
  int dst     = (instr->dst & 0x7) + dr0;
  int imm     = Instruction_getImm32(instr);
  uint64_t N  = 1ull << 63;
  uint64_t dv = (uint64_t)(uint32_t)imm;

  MSG(IMUL_RCP);
  // bool allocF = false;
  if (isZeroOrPowerOf2(dv))
    return;

  uint64_t s = 64 - __builtin_clzll(dv), q = N / dv, r = N % dv;
  uint64_t val = (q << s) + ((r << s) / dv);
  t0           = rxaResvX(p1, RXAI_REG64, RXA_DEV_REG_XPOOL);
  if (t0)
    set_resvLiteralPool(p1, t0, t0->mode, val);
  else {
    t0 = rxaAllocX(p1, RXAI_REG64);
    set_literalPool(p1, t0->xpoolId, val);
  }
  R_mul(p1, dst, t0->xpoolId, FLH(t0), dst);
  rxaFreeX(p1, t0);

  p1->dst_change[dst] = isaSize(p1);
}

void r_INEG_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x7) + dr0;
  MSG(INEG_R);
  R_neg(p1, dst);

  p1->dst_change[dst] = isaSize(p1);
}

void r_IXOR_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src    = (instr->src & 0x7) + dr0;
  int dst    = (instr->dst & 0x7) + dr0;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(IXOR_R);
  if (src == dst) {
    t0 = rxaResvX(p1, RXAI_REG32, RXA_DEV_REG_XPOOL);
    if (t0)
      set_resvLiteralPool(p1, t0, t0->mode, imm);
    else {
      t0 = rxaAllocX(p1, RXAI_REG32);
      R_li(p1, t0->xpoolId, imm);
    }
    R_xor(p1, dst, t0->xpoolId, FLH(t0));
    rxaFreeX(p1, t0);
  } else
    R_xor(p1, dst, src, RXAI_RS_FULL);

  p1->dst_change[dst] = isaSize(p1);
}

void r_IXOR_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src  = (instr->src & 0x7) + dr0;
  int dst  = (instr->dst & 0x7) + dr0;
  int msrc = src == dst ? 0 : src;
  int msk  = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(IXOR_M);
#ifdef LOAD_XTMP
  t0 = rxaAllocX(p1, RXAI_REG32);
  load(p1, t0->xpoolId, msrc, imm, msk);
  R_xor(p1, dst, t0->xpoolId, FLH(t0));
  rxaFreeX(p1, t0);
#else
  load(p1, dxtmp, msrc, imm, msk);
  R_xor(p1, dst, dxtmp, RXAI_RS_FULL);
#endif
  p1->dst_change[dst] = isaSize(p1);
}

void r_IROR_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;
  int imm = Instruction_getImm32(instr);

  MSG(IROR_R);
  if (src == dst) {
    R_rori(p1, dst, imm & 0x3f);
  } else
    R_ror(p1, dst, src, RXAI_R_RIGHT);

  p1->dst_change[dst] = isaSize(p1);
}

void r_IROL_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;
  int imm = Instruction_getImm32(instr);

  MSG(IROL_R);
  if (src == dst) {
    R_rori(p1, dst, 64 - (imm & 0x3f));
  } else
    R_ror(p1, dst, src, RXAI_R_LEFT);

  p1->dst_change[dst] = isaSize(p1);
}

void r_ISWAP_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x7) + dr0;

  MSG(ISWAP_R);
  if (src == dst)
    return;

  R_swap(p1, dst, src);

  p1->dst_change[dst] = isaSize(p1);
  p1->dst_change[src] = isaSize(p1);
}

void r_FSWAP_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x7);

  MSG(FSWAP_R);
  if (dst > 3)
    dst = (dst - 4) + de0;
  else
    dst += df0;

  R_vswap(p1, dst);
}

void r_FADD_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x3) + da0;
  int dst = (instr->dst & 0x3) + df0;

  MSG(FADD_R);
  R_vadd_d(p1, dst, src, dst);
}

void r_FADD_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x3) + df0;
  // int msrc = src == dst ? 0 : src;
  int msk = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm = Instruction_getImm32(instr);
  MSG(FADD_M);
  loadvf(p1, dvtmp, src, imm, msk);
  R_vcvt_d_w(p1, dvtmp, dvtmp, RXAI_WTOD_FTYPE);
  R_vadd_d(p1, dst, dvtmp, dst);
}

void r_FSUB_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x3) + da0;
  int dst = (instr->dst & 0x3) + df0;
  MSG(FSUB_R);
  R_vsub_d(p1, dst, src, dst);
}

void r_FSUB_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int dst = (instr->dst & 0x3) + df0;
  // int msrc = src == dst ? 0 : src;
  int msk = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm = Instruction_getImm32(instr);
  MSG(FSUB_M);
  loadvf(p1, dvtmp, src, imm, msk);
  R_vcvt_d_w(p1, dvtmp, dvtmp, RXAI_WTOD_FTYPE);
  R_vsub_d(p1, dst, dvtmp, dst);
}

void r_FSCAL_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x3) + df0;
  MSG(FSCAL_R);
  R_vxor(p1, dst, dscale, dst);
}

void r_FMUL_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x3) + de0;
  int src = (instr->src & 0x3) + da0;
  MSG(FMUL_R);
  R_vmul_d(p1, dst, src, dst);
}

void r_FDIV_M(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x3) + de0;
  int src = (instr->src & 0x7) + dr0;
  // int msrc = src == dst ? 0 : src;
  int msk = Instruction_getModMem(instr) ? RANDOMX_SCRATCHPAD_L1
                                         : RANDOMX_SCRATCHPAD_L2;
  int imm = Instruction_getImm32(instr);
  MSG(FDIV_M);
  loadvf(p1, dvtmp, src, imm, msk);
  R_vcvt_d_w(p1, dvtmp, dvtmp, RXAI_WTOD_ETYPE);
  R_vdiv_d(p1, dst, dvtmp, dst);
}

void r_FSQRT_R(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x3) + de0;
  MSG(FSQRT_R);
  R_vsqrt_d(p1, dst, dst);
}

void r_CBRANCH(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst = (instr->dst & 0x7) + dr0;
  int sl = Instruction_getModShift(instr), cond = Instruction_getModCond(instr),
      imm    = Instruction_getImm32(instr);
  rxaX_t *t0 = NULL;

  MSG(CBRANCH);
  sl = cond + ConditionOffset;
  imm |= (1U << sl);
  imm &= ~(1U << (sl - 1));

  // dumpReg(p1, instr->opcode, 0);
  // printf("j %p ==> %p (%p)\n", p1->isaSize() + p1->code,
  //        dst_change[dst] + p1->code, p1->isaSize() + offs + p1->code);
  t0 = rxaResvX(p1, RXAI_REG32, RXA_GEN_REG_XPOOL);
  if (t0)
    set_resvLiteralPool(p1, t0, t0->mode, imm);
  else {
    t0 = rxaAllocX(p1, RXAI_REG32);
    R_li(p1, t0->xpoolId, imm);
  }

  int offs = p1->dst_change[dst] - isaSize(p1) - 4;
  R_rxb(p1, dst, t0->xpoolId,
        (cond << 1) | ((t0->mode == RXAI_REG32) ? FLH(t0) - 1 : 0), offs);
  rxaFreeX(p1, t0);
  for (int k = 0; k < 8; ++k)
    p1->dst_change[dr0 + k] = isaSize(p1);
}

void r_CFROUND(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int src = (instr->src & 0x7) + dr0;
  int imm = Instruction_getImm32(instr);

  MSG(CFROUND);
  R_rxsfrm(p1, src, imm & 63);
}

void r_ISTORE(jrx_base_t *p1, Instruction_t *instr, int pc) {
  int dst  = (instr->dst & 0x7) + dr0;
  int src  = (instr->src & 0x7) + dr0;
  int cond = Instruction_getModCond(instr), imm = Instruction_getImm32(instr);
  int msk = Instruction_getModMem(instr)
                ? 14
                : 18; // RANDOMX_SCRATCHPAD_L1 : RANDOMX_SCRATCHPAD_L2;
  rxaX_t *t0 = NULL;

  MSG(ISTORE);
  msk = cond < StoreL3Condition ? msk : 21; // RANDOMX_SCRATCHPAD_L3;
  t0  = rxaAllocX(p1, RXAI_REG32);
  R_addi(p1, t0->xpoolId, dst, imm);
  R_st(p1, t0->xpoolId, src, msk, 0);
  rxaFreeX(p1, t0);
}

void r_NOP(jrx_base_t *p1, Instruction_t *instr, int pc) {}

#include "instruction_weights.h"
#define INST_HANDLE(x) REPN(r_##x, WT(x))

InstructionGenerator RXAengine[256] = {
    INST_HANDLE(IADD_RS) INST_HANDLE(IADD_M) INST_HANDLE(ISUB_R) INST_HANDLE(
        ISUB_M) INST_HANDLE(IMUL_R) INST_HANDLE(IMUL_M) INST_HANDLE(IMULH_R)
        INST_HANDLE(IMULH_M) INST_HANDLE(ISMULH_R) INST_HANDLE(ISMULH_M)
            INST_HANDLE(IMUL_RCP) INST_HANDLE(INEG_R) INST_HANDLE(IXOR_R)
                INST_HANDLE(IXOR_M) INST_HANDLE(IROR_R) INST_HANDLE(IROL_R)
                    INST_HANDLE(ISWAP_R) INST_HANDLE(FSWAP_R) INST_HANDLE(
                        FADD_R) INST_HANDLE(FADD_M) INST_HANDLE(FSUB_R)
                        INST_HANDLE(FSUB_M) INST_HANDLE(FSCAL_R)
                            INST_HANDLE(FMUL_R) INST_HANDLE(FDIV_M)
                                INST_HANDLE(FSQRT_R) INST_HANDLE(CBRANCH)
                                    INST_HANDLE(CFROUND) INST_HANDLE(ISTORE)
                                        INST_HANDLE(NOP)};

jrx_t rxaDev = {
    .name                    = "rxaDev",
    .init_jrx                = initJrxRxa,
    .exit_jrx                = exitJrxRxa,
    .generateProgram         = generateProgram,
    .generateProgramLight    = generateProgramLight,
    .generateSuperscalarHash = generateSuperscalarHash,
    .generateDatasetInitCode = generateDatasetInitCode,
    .getProgramFunc          = getProgramFunc,
    .getDatasetInitFunc      = getDatasetInitFunc,
    .getCode                 = NULL,
    .getCodeSize             = getCodeSize,
    .cipherUpdate            = cipherUpdate,
    .enableWriting           = enableWriting,
    .enableExecution         = enableExecution,
    .enableAll               = enableAll,
};
JRX_REGISTER(rxaDev)
