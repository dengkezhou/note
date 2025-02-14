#include <common.h>
#include <rxa.h>
#include <irq.h>
#include <malloc.h>
#include <asm/io.h>

#define rxa_err(x, ...) printf(x, ##__VA_ARGS__)
#define rxa_dbg(x, ...) printf(x, ##__VA_ARGS__)
#define rxa_info(x, ...)

int isExist(rxa_device_t *dev) {
  char ver[5]  = {0};
  uint32_t val = rxa_readl(RXA(ver), RXA_VERSION_MASK, RXA_VERSION_OFFSET);

  snprintf(ver, 5, "%s", (char *)&val);
  return strncmp(ver, RXA_VER, sizeof(RXA_VER));
}

void rxa_dump(rxa_device_t *dev) {
#define dbg(_off) rxa_dbg("%s 0x%x\n", #_off, readl(RXA(_off)))
  dbg(ver);
  dbg(cfg);
  dbg(ctrl);
  dbg(cfg_r);
  dbg(cfg_cond_offs);
  dbg(cfg_e_and_l.l);
  dbg(cfg_e_and_l.h);
  dbg(cfg_e_and_h.l);
  dbg(cfg_e_and_h.h);
  dbg(cfg_e_or_l.l);
  dbg(cfg_e_or_l.h);
  dbg(cfg_e_or_h.l);
  dbg(cfg_e_or_h.h);
  dbg(offs_prfc);
  dbg(offs_regf);
  dbg(offs_code); //
  dbg(offs_spad);
  dbg(offs_dag);
  dbg(int_msk);
  dbg(int_status); //
  dbg(dbg_pc);
}

void rxa_dump_inner_reg(rxa_device_t *dev) {
	uint64_t val[2];
	for (int i = 0; i < 32; i++) {
		rxa_dbg_readq(dev, i, val);
		printf("x%d: 0x%016lx ", i, val[0]);
		if (!((i + 1) % 8))
			printf("\n");
	}

	for (int i = v16; i < 64; i++) {
		rxa_dbg_readq(dev, i, val);
		printf("v%d: [0x%016lx, 0x%016lx] ", (i - v0), val[0], val[1]);
		if (!((i - v16 + 1) % 2))
			printf("\n");
	}
}

uint64_t rxa_readq(unsigned long addr, uint64_t mask, int offset) {
  return ((readq(addr) & mask) >> offset);
}

void rxa_writeq(unsigned long addr, uint64_t mask, int offset, uint64_t val) {
  uint64_t tmp;

  tmp = readq(addr);
  tmp &= ~mask;
  tmp |= ((val << offset) & mask);
  writeq(tmp, addr);
}

void rxa_dbg_writeq(rxa_device_t *dev, int reg, uint64_t *val) {
  if (!limits(x0, v31))
    return;

  if (limits(x0, x31)) {
    rxa_writeq(RXA(dbg_greg[reg]), RXA_64DATA_MASK, RXA_64DATA_OFFSET, val[0]);
  }

  if (limits(v0, v31)) {
    rxa_writeq(RXA(dbg_greg[(reg - v0) * 2]), RXA_64DATA_MASK,
               RXA_64DATA_OFFSET, val[0]);
    rxa_writeq(RXA(dbg_greg[(reg - v0) * 2 + 1]), RXA_64DATA_MASK,
               RXA_64DATA_OFFSET, val[1]);
  }
}

void rxa_dbg_readq(rxa_device_t *dev, int reg, uint64_t *val) {
  if (!limits(x0, v31))
    return;

  if (limits(x0, x31) && val)
    val[0] = rxa_readq(RXA(dbg_greg[reg]), RXA_64DATA_MASK, RXA_64DATA_OFFSET);

  if (limits(v0, v31) && val) {
    val[0] = rxa_readq(RXA(dbg_greg[(reg - v0) * 2]), RXA_64DATA_MASK,
                       RXA_64DATA_OFFSET);
    val[1] = rxa_readq(RXA(dbg_greg[(reg - v0) * 2 + 1]), RXA_64DATA_MASK,
                       RXA_64DATA_OFFSET);
  }
}

void rxa_resetRoundingMode(rxa_device_t *dev) { /* TODO */
	rxa_writel(RXA(fprc), RXA_FLOAT_MASK, RXA_FLOAT_OFFSET, 0);	
}

void rxa_start(rxa_device_t *dev) {
  rxa_writel(RXA(ctrl), RXA_START_MASK, RXA_START_OFFSET, 1);
}

void rxa_stop(rxa_device_t *dev) {
  rxa_writel(RXA(ctrl), RXA_STOP_MASK, RXA_STOP_OFFSET, 1);
}

int rxa_set_break(rxa_device_t *dev, int mode, uint32_t addr) {
  if (mode < RXAI_BREAK_POINT0 || mode > RXAI_BREAK_POINT4)
    return -1;

  rxa_writel(RXA(dbg_brk[mode]), RXA_CFG_MASK, RXA_CFG_OFFSET, addr);
  return 0;
}

void rxa_set_stepmode(rxa_device_t *dev, int mode, int num) {
	if (mode == RXAI_STEP)
  	rxa_writel(RXA(cfg), RXA_EXECMODE_MASK, RXA_EXECMODE_OFFSET, num);
	else
		rxa_writel(RXA(cfg), RXA_EXECMODE_MASK, RXA_EXECMODE_OFFSET, 0);
}

void rxa_set_fetch_width(rxa_device_t *dev, int width) {
  rxa_writel(RXA(cfg), RXA_FETCHWIDTH_MASK, RXA_FETCHWIDTH_OFFSET, width);
}

void rxa_set_cfg_r(rxa_device_t *dev, char *cfgr) {
  for (int i = 0; i < 4; i++)
    rxa_writel(RXA(cfg_r), RXA_CFG_R_MASK(i), RXA_CFG_R_OFFSET(i), cfgr[i]);
}

void rxa_set_cond_offs(rxa_device_t *dev, uint32_t offs) {
  rxa_writel(RXA(cfg_cond_offs), RXA_CFG_MASK, RXA_CFG_OFFSET, offs);
}

void rxa_set_cfg_e_and(rxa_device_t *dev, uint32_t *e_and) {
  rxa_writel(RXA(cfg_e_and_l.l), RXA_CFG_MASK, RXA_CFG_OFFSET, e_and[0]);
  rxa_writel(RXA(cfg_e_and_l.h), RXA_CFG_MASK, RXA_CFG_OFFSET, e_and[1]);
  rxa_writel(RXA(cfg_e_and_h.l), RXA_CFG_MASK, RXA_CFG_OFFSET, e_and[2]);
  rxa_writel(RXA(cfg_e_and_h.h), RXA_CFG_MASK, RXA_CFG_OFFSET, e_and[3]);
}

void rxa_set_xpool(rxa_device_t *dev, uint64_t *data, int size) {
  for (int i = 0; i < size; i++)
    rxa_writeq(RXA(xpool[i]), RXA_64DATA_MASK, RXA_64DATA_OFFSET, data[i]);
}

void rxa_set_cfg_e_or(rxa_device_t *dev, uint32_t *e_or) {
  rxa_writel(RXA(cfg_e_or_l.l), RXA_CFG_MASK, RXA_CFG_OFFSET, e_or[0]);
  rxa_writel(RXA(cfg_e_or_l.h), RXA_CFG_MASK, RXA_CFG_OFFSET, e_or[1]);
  rxa_writel(RXA(cfg_e_or_h.l), RXA_CFG_MASK, RXA_CFG_OFFSET, e_or[2]);
  rxa_writel(RXA(cfg_e_or_h.h), RXA_CFG_MASK, RXA_CFG_OFFSET, e_or[3]);
}

void rxa_set_prefetch_offs(rxa_device_t *dev, uint32_t offs) {
  rxa_writel(RXA(offs_prfc), RXA_IDRAM_MASK, RXA_IDRAM_OFFSET, offs);
}

void rxa_set_regf(rxa_device_t *dev, int en, uint32_t offs) {
  if (en)
    rxa_writel(RXA(offs_regf), RXA_IDRAM_MASK, RXA_IDRAM_OFFSET, offs);

  rxa_writel(RXA(offs_regf), RXA_OUTPUTEN_MASK, RXA_OUTPUTEN_OFFSET, en);
}

int rxa_wait_regf_ready(rxa_device_t *dev) {
	return !rxa_readl(RXA(offs_regf), RXA_OUTPUTEN_MASK, RXA_OUTPUTEN_OFFSET);
}

void rxa_set_code_offs(rxa_device_t *dev, uint32_t offs) {
  rxa_writel(RXA(offs_code), RXA_IDRAM_MASK, RXA_IDRAM_OFFSET, offs);
}

uint32_t rxa_get_code_offs(rxa_device_t *dev) {
  return rxa_readl(RXA(offs_code), RXA_IDRAM_MASK, RXA_IDRAM_OFFSET);
}

void rxa_set_spad_offs(rxa_device_t *dev, uint32_t offs) {
  rxa_writel(RXA(offs_spad), RXA_IDRAM_MASK, RXA_IDRAM_OFFSET, offs);
}

void rxa_set_dag_offs(rxa_device_t *dev, unsigned long offs) {
  rxa_writel(RXA(offs_dag.h), RXA_DDRH_MASK, RXA_DDRH_OFFSET, hi(offs));
  rxa_writel(RXA(offs_dag.l), RXA_DDRL_MASK, RXA_DDRL_OFFSET, lo(offs));
}

void rxa_set_cipher_offs(rxa_device_t *dev, unsigned long offs) {
  rxa_writel(RXA(offs_decr.h), RXA_DDRH_MASK, RXA_DDRH_OFFSET, hi(offs));
  rxa_writel(RXA(offs_decr.l), RXA_DDRL_MASK, RXA_DDRL_OFFSET, lo(offs));
}

void rxa_set_brk(rxa_device_t *dev, int id, uint32_t brk) {
  rxa_writel(RXA(dbg_brk[id]), RXA_CFG_MASK, RXA_CFG_OFFSET, brk);
}

void rxa_set_dmamsk(rxa_device_t *dev, uint64_t dmamsk) {
	rxa_writeq(RXA(dmamsk), RXA_64DATA_MASK, RXA_64DATA_OFFSET, dmamsk);
}

static void rxa_core_init(rxa_device_t *dev) {
  rxa_cfg_t *cfg = dev->cfg;

  if (!cfg)
    return;

  rxa_set_cfg_e_and(dev, SET(e_and));
  rxa_set_cfg_e_or(dev, SET(e_or));
  rxa_set_cfg_r(dev, SET(r));
  // enable output regfile
  //rxa_set_regf(dev, SET(en_regf), SET(offs_regf));
  // set cond offs
  rxa_set_cond_offs(dev, SET(cfg_cond_offs));

  // these are offsets to the start of SRAM
  rxa_set_prefetch_offs(dev, SET(offs_prfc));
  rxa_set_code_offs(dev, SET(offs_code));
  rxa_set_spad_offs(dev, SET(offs_spad));

  // DAG will be read from the start address of DDR
  rxa_set_dag_offs(dev, SET(offs_dag));

	rxa_set_dmamsk(dev, SET(dmamsk));

  for (int i = 0; i < 5; i++)
    rxa_set_brk(dev, i, 0xffffffff);

	//rxa_set_regf(dev, 1, 0x380);
}

void rxa_irq_mask(rxa_device_t *dev, uint32_t mask) {
  rxa_writel(RXA(int_msk), RXA_CFG_MASK, RXA_CFG_OFFSET, mask);
}

void rxa_set_privdata(rxa_device_t *dev, void *privdata) {
  dev->privdata = privdata;
}

void rxa_memset(rxa_device_t *dev, uint32_t offs, int len) {
	rxa_writel(RXA(pbuf_clr), RXA_PBUFCLR_START_MASK, RXA_PBUFCLR_START_OFFSET, offs);
	rxa_writel(RXA(pbuf_clr), RXA_PBUFCLR_LEN_MASK, RXA_PBUFCLR_LEN_OFFSET, len);
	while (rxa_readl(RXA(pbuf_clr), RXA_PBUFCLR_LEN_MASK, RXA_PBUFCLR_LEN_OFFSET));
}

static int cur_cycle = 0, max_cycle = 0, min_cycle = 0, avr_cycle = 0;
static int sum_cycle = 0, loop = 0;
int rxa_irq_handler(int irqno, void *buf) {
  rxa_device_t *dev = (rxa_device_t *)buf;
  uint32_t st       = rxa_readl(RXA(int_status), RXA_CFG_MASK, RXA_CFG_OFFSET);
  //rxa_dbg("irq %d triggered, status=%x\n", irqno, st);
#if 0
  if (st & RXA_INT_ILLEAGLE) {
    rxa_err("Illeagel\n");
    goto clr;
  }
#endif
  if (st & RXA_INT_DATA_ABORT) {
    rxa_err("Data Abort\n");
    goto clr;
  }

  if (st & RXA_INT_ILLEAGLE_CFG) {
    rxa_err("Illeagel Config\n");
    goto clr;
  }

  if (st & RXA_INT_DONE) {
    // finished, do nothing
    rxa_info("Work Done\n");
    cur_cycle = readl(RXA(dbg_cycles));
    writel(0, RXA(dbg_cycles));
		// except a1r4, a4r4 and blk2b
    if (cur_cycle > 100) {
      loop++;
      sum_cycle += cur_cycle;
      avr_cycle = sum_cycle / loop;

      if (!max_cycle)
        max_cycle = cur_cycle;

      if (!min_cycle)
        min_cycle = cur_cycle;

      if (cur_cycle > max_cycle)
        max_cycle = cur_cycle;

      if (cur_cycle < min_cycle)
        min_cycle = cur_cycle;
#if 0
      printf("nonces: %d, cur: %d, max: %d, min: %d, avr: %d\n", (loop - 1) / 8,
             cur_cycle, max_cycle, min_cycle, avr_cycle);
#endif
    }

    if (dev->callback)
      dev->callback(dev->privdata);
  } else if (st & RXA_INT_PAUSED) {
    // pause
    // writel(1, RXA(dbg_ctrl));
    rxa_dbg("Pause Mode\n");
		rxa_dbg("Run Enter %d: \n", (readl(RXA(dbg_pc)) - 0x500) / (8 * 4));
		rxa_dump_inner_reg(dev);
#if 0
		if (dev->callback)
  		dev->callback(dev->privdata);
#endif
  } else if (st & RXA_INT_STEP) {
		rxa_dbg("Run Enter %d: \n", (readl(RXA(dbg_pc)) - 0x500) / (8 * 4));
		rxa_dump_inner_reg(dev);
		//rxa_start(dev);
#if 0
		if (dev->callback)
  		dev->callback(dev->privdata);
#endif
	}

clr:
  rxa_writel(RXA(int_status), RXA_CFG_MASK, RXA_CFG_OFFSET, 0);
	if ((st & RXA_INT_STEP) && !(st & RXA_INT_DONE) && !(st & RXA_INT_PAUSED))
		*((uint32_t *)0xc6000008) = 1;
  return 0;
}

rxa_device_t *itcs_rxa_init(int idx, rxa_cfg_t *cfg,
                            void (*callback)(void *privdata), void *privdata) {
  rxa_device_t *dev;
  char name[16] = {0};
  int ret;

  if (idx > RXA_MAX || idx < 0)
    return NULL;

  dev = malloc(sizeof(rxa_device_t));
  if (!dev) {
    rxa_err("RXA Malloc Err\n");
    return NULL;
  }
  dev->idx      = idx;
  dev->callback = callback;
  dev->regs     = (rxa_regs_t *)ITCS_C_RXA_BASE(idx);
  dev->cfg      = cfg;
  sprintf(dev->devname, "rxa%d", dev->idx);
  dev->privdata = privdata;

  dev->mem.sram = (void *)ITCS_RXA_IRAM_ADDR(idx);
  dev->mem.dram = (void *)ITCS_RXA_DRAM_ADDR(idx);
  dev->mem.ddr  = (void *)ITCS_CDDR_ADDR;

	sprintf(name, "rxa%d", idx);
	itcs_module_enable(CPU, name);
	if (isExist(dev)) {
		rxa_err("Bad RXA value\n");
		goto exit;
	}

  rxa_core_init(dev);
	
  rxa_irq_mask(dev, RXA_INT_STEP | RXA_INT_PAUSED | RXA_INT_DONE);
  ret = request_irq(RXA_IRQ(idx), rxa_irq_handler, "rxa", dev);
  if (ret < 0) {
    ret = replace_irq(RXA_IRQ(idx), rxa_irq_handler, "rxa", dev);
    if (ret < 0) {
      printf("Request watchdog irq Err\n");
      goto exit;
    }
  }

  return dev;

exit:
  if (dev)
    free(dev);

  return NULL;
}

void itcs_rxa_exit(rxa_device_t *dev) {
  if (dev)
    free(dev);
}
