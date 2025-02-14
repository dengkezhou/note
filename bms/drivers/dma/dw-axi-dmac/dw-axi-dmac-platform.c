// SPDX-License-Identifier:  GPL-2.0
// (C) 2017-2018 Synopsys, Inc. (www.synopsys.com)

/*
 * Synopsys DesignWare AXI DMA Controller driver.
 *
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 */

#include <linux/bitops.h>
#include <linux/err.h>
#include <linux/types.h>
#include <linux/list.h>
#include <common.h>
#include <irq.h>
#include <malloc.h>
#include <linux/dmaengine.h>
#include <linux/scatterlist.h>
#include <dma-ops.h>
#include <asm/io.h>
#include "dw-axi-dmac.h"
#include "../virt-dma.h"

/*
 * The set of bus widths supported by the DMA controller. DW AXI DMAC supports
 * master data bus width up to 512 bits (for both AXI master interfaces), but
 * it depends on IP block configurarion.
 */
#define AXI_DMA_BUSWIDTHS                                            \
	(DMA_SLAVE_BUSWIDTH_1_BYTE | DMA_SLAVE_BUSWIDTH_2_BYTES |    \
	 DMA_SLAVE_BUSWIDTH_4_BYTES | DMA_SLAVE_BUSWIDTH_8_BYTES |   \
	 DMA_SLAVE_BUSWIDTH_16_BYTES | DMA_SLAVE_BUSWIDTH_32_BYTES | \
	 DMA_SLAVE_BUSWIDTH_64_BYTES)

#if DEBUG_DMA
void com_reg_dump(int id, char *reg_str, u32 reg)
{
	u32 val = 0;
	if (id == 0)
		val = readl(ITCS_C_DMA0_BASE + reg);
	else if (id == 1)
		val = readl(ITCS_C_DMA1_BASE + reg);
	printf("--%s: 0x%x--\n", reg_str, val);
}

void cha_reg_dump(struct dma_chan *dchan, char *reg_str, u32 reg)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	u32 val;
	val = readl(chan->chan_regs + reg);
	printf("--%s: 0x%x--\n", reg_str, val);
}

void dma_reg_dump(int id, struct dma_chan *chan)
{
	com_reg_dump(id, "DMAC_ID", DMAC_ID);
	com_reg_dump(id, "DMAC_COMPVER", DMAC_COMPVER);
	com_reg_dump(id, "DMAC_CFG", DMAC_CFG);
	//com_reg_dump(id, "DMAC_CHEN_L", DMAC_CHEN_L);
	//com_reg_dump(id, "DMAC_CHEN_H", DMAC_CHEN_H);
	com_reg_dump(id, "DMAC_INTSTATUS", DMAC_INTSTATUS);
	com_reg_dump(id, "DMAC_COMMON_INTSTATUS_ENA",
		     DMAC_COMMON_INTSTATUS_ENA);
	com_reg_dump(id, "DMAC_COMMON_INTSIGNAL_ENA",
		     DMAC_COMMON_INTSIGNAL_ENA);
	com_reg_dump(id, "DMAC_COMMON_INTSTATUS", DMAC_COMMON_INTSTATUS);
	com_reg_dump(id, "DMAC_RESET", DMAC_RESET);

	cha_reg_dump(chan, "CH_SAR", CH_SAR);
	cha_reg_dump(chan, "CH_SAR + 4", CH_SAR + 4);
	cha_reg_dump(chan, "CH_DAR", CH_DAR);
	cha_reg_dump(chan, "CH_DAR + 4", CH_DAR + 4);
	cha_reg_dump(chan, "CH_BLOCK_TS", CH_BLOCK_TS);
	cha_reg_dump(chan, "CH_CTL_L", CH_CTL_L);
	cha_reg_dump(chan, "CH_CTL_H", CH_CTL_H);
	cha_reg_dump(chan, "CH_CFG_L", CH_CFG_L);
	cha_reg_dump(chan, "CH_CFG_H", CH_CFG_H);
	cha_reg_dump(chan, "CH_LLP", CH_LLP);
	cha_reg_dump(chan, "CH_LLP + 4", CH_LLP + 4);
	cha_reg_dump(chan, "CH_STATUS", CH_STATUS);
	//cha_reg_dump(chan, "CH_SWHSSRC", CH_SWHSSRC);
	//cha_reg_dump(chan, "CH_SWHSDST", CH_SWHSDST);
	//cha_reg_dump(chan, "CH_BLK_TFR_RESUMEREQ", CH_BLK_TFR_RESUMEREQ);
	cha_reg_dump(chan, "CH_AXI_ID", CH_AXI_ID);
	cha_reg_dump(chan, "CH_AXI_QOS", CH_AXI_QOS);
	cha_reg_dump(chan, "CH_SSTAT", CH_SSTAT);
	cha_reg_dump(chan, "CH_DSTAT", CH_DSTAT);
	cha_reg_dump(chan, "CH_SSTATAR", CH_SSTATAR);
	cha_reg_dump(chan, "CH_DSTATAR", CH_DSTATAR);
	cha_reg_dump(chan, "CH_INTSTATUS_ENA", CH_INTSTATUS_ENA);
	cha_reg_dump(chan, "CH_INTSTATUS", CH_INTSTATUS);
	cha_reg_dump(chan, "CH_INTSIGNAL_ENA", CH_INTSIGNAL_ENA);
	//cha_reg_dump(chan, "CH_INTCLEAR", CH_INTCLEAR);
}
#endif

struct dma_pool *dma_pool_create(const char *name, struct device *dev,
				 size_t size, size_t align, size_t boundary)
{
	struct dma_pool *retval;
	size_t allocation;

	if (align == 0)
		align = 1;
	else if (align & (align - 1))
		return NULL;

	if (size == 0)
		return NULL;
	else if (size < 4)
		size = 4;

	size = ALIGN(size, align);
	allocation = max_t(size_t, size, (PAGE_SIZE + align));

	if (!boundary)
		boundary = allocation;
	else if ((boundary < size) || (boundary & (boundary - 1)))
		return NULL;

	retval = kmalloc(sizeof(*retval), GFP_KERNEL);
	if (!retval)
		return retval;
	memset(retval, 0, sizeof(*retval));

	strncpy(retval->name, name, sizeof(retval->name));

	retval->dev = dev;

	INIT_LIST_HEAD(&retval->page_list);
	retval->size = size;
	retval->boundary = boundary;
	retval->allocation = allocation;

	INIT_LIST_HEAD(&retval->pools);
	list_add(&retval->pools, &dev->dma_pools);
	return retval;
}

static void pool_free_page(struct dma_pool *pool, struct dma_page *page)
{
#ifdef DMAPOOL_DEBUG
	memset(page->vaddr, POOL_POISON_FREED, pool->allocation);
#endif
	if (page->vaddr) {
		free(page->vaddr);
		page->vaddr = NULL;
	}
	list_del(&page->page_list);
	kfree(page);
}

/**
 * dma_pool_destroy - destroys a pool of dma memory blocks.
 * @pool: dma pool that will be destroyed
 * Context: !in_interrupt()
 *
 * Caller guarantees that no more memory from the pool is in use,
 * and that nothing will try to use the pool after this call.
 */
void dma_pool_destroy(struct dma_pool *pool)
{
	struct dma_page *page, *tmp;

	if (unlikely(!pool))
		return;

	list_del(&pool->pools);

	list_for_each_entry_safe(page, tmp, &pool->page_list, page_list) {
		if (is_page_busy(page)) {
			if (pool->dev)
				dev_err(pool->dev, "%s %s, %p busy\n", __func__,
					pool->name, page->vaddr);
			else
				dev_err("%s %s, %p busy\n", __func__,
					pool->name, page->vaddr);
			/* leak the still-in-use consistent memory */
			list_del(&page->page_list);
			kfree(page);
		} else
			pool_free_page(pool, page);
	}

	kfree(pool);
}

static void pool_initialise_page(struct dma_pool *pool, struct dma_page *page,
				 unsigned int offset)
{
	unsigned int next_boundary = pool->boundary;

	do {
		unsigned int next = offset + pool->size;
		if (unlikely((next + pool->size) >= next_boundary)) {
			next = next_boundary;
			next_boundary += pool->boundary;
		}
		*(int *)(page->vaddr + offset) = next;
		offset = next;
	} while (offset < pool->allocation);
}

static struct dma_page *pool_alloc_page(struct dma_pool *pool, size_t align)
{
	struct dma_page *page;

	page = malloc(sizeof(*page));
	if (!page)
		return NULL;
	memset(page, 0, sizeof(*page));

	page->vaddr = malloc(pool->allocation);
	if (!page->vaddr) {
		printf("page->vaddr alloc failed\n");
		return NULL;
	}
	memset(page->vaddr, 0, pool->allocation);

	page->dma = (dma_addr_t)page->vaddr;

	if (page->vaddr) {
#ifdef DMAPOOL_DEBUG
		memset(page->vaddr, POOL_POISON_FREED, pool->allocation);
#endif
		if ((unsigned long)page->vaddr % align != 0)
			page->offset =
				align - (unsigned long)page->vaddr % align;
		else
			page->offset = 0;

		pool_initialise_page(pool, page, page->offset);
		page->in_use = 0;
	} else {
		kfree(page);
		page = NULL;
	}
	return page;
}

/**
 * dma_pool_alloc - get a block of consistent memory
 * @pool: dma pool that will produce the block
 * @mem_flags: GFP_* bitmask
 * @handle: pointer to dma address of block
 *
 * Return: the kernel virtual address of a currently unused block,
 * and reports its dma address through the handle.
 * If such a memory block can't be allocated, %NULL is returned.
 */
void *dma_pool_alloc(struct dma_pool *pool, dma_addr_t *handle, size_t align)
{
	struct dma_page *page;
	size_t offset;
	void *retval;

	list_for_each_entry(page, &pool->page_list, page_list) {
		if (page->offset < pool->allocation)
			goto ready;
	}

	page = pool_alloc_page(pool, align);
	if (!page)
		return NULL;

	list_add(&page->page_list, &pool->page_list);
ready:
	page->in_use++;
	offset = page->offset;
	page->offset = *(int *)(page->vaddr + offset);
	retval = offset + page->vaddr;
	*handle = offset + page->dma;
#ifdef DMAPOOL_DEBUG
	{
		int i;
		u8 *data = retval;
		/* page->offset is stored in first 4 bytes */
		for (i = sizeof(page->offset); i < pool->size; i++) {
			if (data[i] == POOL_POISON_FREED)
				continue;
			if (pool->dev)
				dev_err(pool->dev, "%s %s, %p (corrupted)\n",
					__func__, pool->name, retval);
			else
				pr_err("%s %s, %p (corrupted)\n", __func__,
				       pool->name, retval);

			/*
			 * Dump the first 4 bytes even if they are not
			 * POOL_POISON_FREED
			 */
			//print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1,
			//		data, pool->size, 1);
			break;
		}
	}
	if (!(mem_flags & __GFP_ZERO))
		memset(retval, POOL_POISON_ALLOCATED, pool->size);
#endif

	memset(retval, 0, pool->size);
	return retval;
}

static struct dma_page *pool_find_page(struct dma_pool *pool, dma_addr_t dma)
{
	struct dma_page *page;

	list_for_each_entry(page, &pool->page_list, page_list) {
		if (dma < page->dma)
			continue;
		if ((dma - page->dma) < pool->allocation)
			return page;
	}
	return NULL;
}

/**
 * dma_pool_free - put block back into dma pool
 * @pool: the dma pool holding the block
 * @vaddr: virtual address of block
 * @dma: dma address of block
 *
 * Caller promises neither device nor driver will again touch this block
 * unless it is first re-allocated.
 */
void dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma)
{
	struct dma_page *page;
	unsigned int offset;

	page = pool_find_page(pool, dma);
	if (!page) {
		if (pool->dev)
			dev_err(pool->dev, "%s %s, %p/%pad (bad dma)\n",
				__func__, pool->name, vaddr, &dma);
		else
			dev_err("%s %s, %p/%pad (bad dma)\n", __func__,
				pool->name, vaddr, &dma);
		return;
	}

	offset = vaddr - page->vaddr;
	memset(vaddr, 0, pool->size);
#ifdef DMAPOOL_DEBUG
	if ((dma - page->dma) != offset) {
		if (pool->dev)
			dev_err(pool->dev, "%s %s, %p (bad vaddr)/%pad\n",
				__func__, pool->name, vaddr, &dma);
		else
			dev_err("%s %s, %p (bad vaddr)/%pad\n", __func__,
				pool->name, vaddr, &dma);
		return;
	}
	{
		unsigned int chain = page->offset;
		while (chain < pool->allocation) {
			if (chain != offset) {
				chain = *(int *)(page->vaddr + chain);
				continue;
			}
			if (pool->dev)
				dev_err(pool->dev,
					"%s %s, dma %pad already free\n",
					__func__, pool->name, &dma);
			else
				dev_err("%s %s, dma %pad already free\n",
					__func__, pool->name, &dma);
			return;
		}
	}
	memset(vaddr, POOL_POISON_FREED, pool->size);
#endif

	page->in_use--;
	*(int *)vaddr = page->offset;
	page->offset = offset;
}

static inline void axi_dma_iowrite32(struct axi_dma_chip *chip, u32 reg,
				     u32 val)
{
	writel(val, chip->regs + reg);
}

static inline u32 axi_dma_ioread32(struct axi_dma_chip *chip, u32 reg)
{
	return readl(chip->regs + reg);
}

static inline void axi_chan_iowrite32(struct axi_dma_chan *chan, u32 reg,
				      u32 val)
{
	writel(val, chan->chan_regs + reg);
}

static inline u32 axi_chan_ioread32(struct axi_dma_chan *chan, u32 reg)
{
	return readl(chan->chan_regs + reg);
}

static inline void axi_chan_iowrite64(struct axi_dma_chan *chan, u32 reg,
				      u64 val)
{
	/*
	 * We split one 64 bit write for two 32 bit write as some HW doesn't
	 * support 64 bit access.
	 */
	writel(lower_32_bits(val), chan->chan_regs + reg);
	writel(upper_32_bits(val), chan->chan_regs + reg + 4);
}

static inline __u64 lo_hi_readq(const volatile void __iomem *addr)
{
	const volatile u32 __iomem *p = addr;
	u32 low, high;

	low = readl(p);
	high = readl(p + 1);

	return low + ((u64)high << 32);
}

static inline void axi_chan_config_write(struct axi_dma_chan *chan,
					 struct axi_dma_chan_config *config)
{
	u32 cfg_lo, cfg_hi;

	cfg_lo = (config->dst_multblk_type << CH_CFG_L_DST_MULTBLK_TYPE_POS |
		  config->src_multblk_type << CH_CFG_L_SRC_MULTBLK_TYPE_POS);

	cfg_hi = config->tt_fc << CH_CFG_H_TT_FC_POS |
		 config->hs_sel_src << CH_CFG_H_HS_SEL_SRC_POS |
		 config->hs_sel_dst << CH_CFG_H_HS_SEL_DST_POS |
		 config->src_per << CH_CFG_H_SRC_PER_POS |
		 config->dst_per << CH_CFG_H_DST_PER_POS |
		 config->prior << CH_CFG_H_PRIORITY_POS;

	axi_chan_iowrite32(chan, CH_CFG_L, cfg_lo);
	axi_chan_iowrite32(chan, CH_CFG_H, cfg_hi);
}

static inline void axi_dma_disable(struct axi_dma_chip *chip)
{
	u32 val;

	val = axi_dma_ioread32(chip, DMAC_CFG);
	val &= ~DMAC_EN_MASK;
	axi_dma_iowrite32(chip, DMAC_CFG, val);
}

static inline void axi_dma_enable(struct axi_dma_chip *chip)
{
	u32 val;

	val = axi_dma_ioread32(chip, DMAC_CFG);
	val |= DMAC_EN_MASK;
	axi_dma_iowrite32(chip, DMAC_CFG, val);
}

static inline void axi_dma_irq_disable(struct axi_dma_chip *chip)
{
	u32 val;

	val = axi_dma_ioread32(chip, DMAC_CFG);
	val &= ~INT_EN_MASK;
	axi_dma_iowrite32(chip, DMAC_CFG, val);
}

static inline void axi_dma_irq_enable(struct axi_dma_chip *chip)
{
	u32 val;

	val = axi_dma_ioread32(chip, DMAC_CFG);
	val |= INT_EN_MASK;
	axi_dma_iowrite32(chip, DMAC_CFG, val);
}

static inline void axi_chan_irq_disable(struct axi_dma_chan *chan, u32 irq_mask)
{
	u32 val;

	if (likely(irq_mask == DWAXIDMAC_IRQ_ALL)) {
		axi_chan_iowrite32(chan, CH_INTSTATUS_ENA, DWAXIDMAC_IRQ_NONE);
	} else {
		val = axi_chan_ioread32(chan, CH_INTSTATUS_ENA);
		val &= ~irq_mask;
		axi_chan_iowrite32(chan, CH_INTSTATUS_ENA, val);
	}
}

static inline void axi_chan_irq_set(struct axi_dma_chan *chan, u32 irq_mask)
{
	axi_chan_iowrite32(chan, CH_INTSTATUS_ENA, irq_mask);
}

static inline void axi_chan_irq_sig_set(struct axi_dma_chan *chan, u32 irq_mask)
{
	axi_chan_iowrite32(chan, CH_INTSIGNAL_ENA, irq_mask);
}

static inline void axi_chan_irq_clear(struct axi_dma_chan *chan, u32 irq_mask)
{
	axi_chan_iowrite32(chan, CH_INTCLEAR, irq_mask);
}

static inline u32 axi_chan_irq_read(struct axi_dma_chan *chan)
{
	return axi_chan_ioread32(chan, CH_INTSTATUS);
}

static inline void axi_chan_disable(struct axi_dma_chan *chan)
{
	u32 val;

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);
	val &= ~(BIT(chan->id) << DMAC_CHAN_EN_SHIFT);
	val |= BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
	axi_dma_iowrite32(chan->chip, DMAC_CHEN, val);
}

static inline void axi_chan_enable(struct axi_dma_chan *chan)
{
	u32 val;

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);
	val |= BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
	       BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
	axi_dma_iowrite32(chan->chip, DMAC_CHEN, val);
}

static inline bool axi_chan_is_hw_enable(struct axi_dma_chan *chan)
{
	u32 val;

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);

	return !!(val & (BIT(chan->id) << DMAC_CHAN_EN_SHIFT));
}

static void axi_dma_hw_init(struct axi_dma_chip *chip)
{
	u32 i;

	for (i = 0; i < chip->dw->hdata->nr_channels; i++) {
		axi_chan_irq_disable(&chip->dw->chan[i], DWAXIDMAC_IRQ_ALL);
		axi_chan_disable(&chip->dw->chan[i]);
	}
}

static u32 axi_chan_get_xfer_width(struct axi_dma_chan *chan, dma_addr_t src,
				   dma_addr_t dst, size_t len)
{
	u32 max_width = chan->chip->dw->hdata->m_data_width;

	return __ffs(src | dst | len | BIT(max_width));
}

static inline const char *axi_chan_name(struct axi_dma_chan *chan)
{
	return dma_chan_name(&chan->vc.chan);
}

static struct axi_dma_desc *axi_desc_alloc(u32 num)
{
	struct axi_dma_desc *desc;

	desc = kzalloc(sizeof(*desc), GFP_NOWAIT);
	if (!desc)
		return NULL;
	memset(desc, 0, sizeof(*desc));

	desc->hw_desc =
		(struct axi_dma_hw_desc *)malloc(num * sizeof(*desc->hw_desc));
	if (!desc->hw_desc) {
		kfree(desc);
		return NULL;
	}
	memset(desc->hw_desc, 0, num * sizeof(*desc->hw_desc));
	return desc;
}

//#if defined(CONFIG_CACHE_LITE)
//static dma_addr_t last_lli = DMA_UNCACHEABLE_LLI;
//#endif

static struct axi_dma_lli *axi_desc_get(struct axi_dma_chan *chan,
					dma_addr_t *addr)
{
	struct axi_dma_lli *lli;
//#if !defined(CONFIG_CACHE_LITE)
	dma_addr_t phys;
//#endif

	/* here we need to be aligned to a 64 byte boundary. */
//#if defined(CONFIG_CACHE_LITE)
//	lli = (struct axi_dma_lli *)last_lli;
//	last_lli = (dma_addr_t)lli + 64;
///#else
	lli = dma_pool_alloc(chan->desc_pool, &phys, 64);
//#endif
	if (unlikely(!lli)) {
		dev_err(chan2dev(chan),
			"%s: not enough descriptors available\n",
			axi_chan_name(chan));
		return NULL;
	}

	atomic_inc(&chan->descs_allocated);
//#if defined(CONFIG_CACHE_LITE)
//	*addr = (dma_addr_t)lli;
//#else
	*addr = phys;
//#endif

	return lli;
}

static void axi_desc_put(struct axi_dma_desc *desc)
{
	struct axi_dma_chan *chan = desc->chan;
	int count = atomic_read(&chan->descs_allocated);
//#if !defined(CONFIG_CACHE_LITE)
	struct axi_dma_hw_desc *hw_desc;
//#endif
	int descs_put;

	for (descs_put = 0; descs_put < count; descs_put++) {
//#if !defined(CONFIG_CACHE_LITE)
		hw_desc = &desc->hw_desc[descs_put];
		dma_pool_free(chan->desc_pool, hw_desc->lli, hw_desc->llp);
//#endif
	}

	kfree(desc->hw_desc);
	kfree(desc);
	atomic_sub(descs_put, &chan->descs_allocated);
#if DEBUG_DMA
	dev_vdbg(chan2dev(chan), "%s: %d descs put, %d still allocated\n",
		 axi_chan_name(chan), descs_put,
		 atomic_read(&chan->descs_allocated));
#endif
}

static void vchan_desc_put(struct virt_dma_desc *vdesc)
{
	axi_desc_put(vd_to_axi_desc(vdesc));
}

static enum dma_status dma_chan_tx_status(struct dma_chan *dchan,
					  dma_cookie_t cookie,
					  struct dma_tx_state *txstate)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	struct virt_dma_desc *vdesc;
	enum dma_status status;
	u32 completed_length;
	u32 completed_blocks;
	size_t bytes = 0;
	u32 length;
	u32 len;

	status = dma_cookie_status(dchan, cookie, txstate);
	if (status == DMA_COMPLETE || !txstate)
		return status;

	// spin_lock_irqsave(&chan->vc.lock, flags);

	vdesc = vchan_find_desc(&chan->vc, cookie);
	if (vdesc) {
		length = vd_to_axi_desc(vdesc)->length;
		completed_blocks = vd_to_axi_desc(vdesc)->completed_blocks;
		len = vd_to_axi_desc(vdesc)->hw_desc[0].len;
		completed_length = completed_blocks * len;
		bytes = length - completed_length;
	}

	// spin_unlock_irqrestore(&chan->vc.lock, flags);
	dma_set_residue(txstate, bytes);
	return status;
}

static void write_desc_llp(struct axi_dma_hw_desc *desc, dma_addr_t adr)
{
//#if (defined(CONFIG_E906) && defined(CONFIG_TB_RUN_DDR)) || defined(CONFIG_CACHE_LITE)
//	unsigned long long llp_addr = adr;
//	llp_addr = llp_addr - E906_DMA_MAP_ADDR1 + E906_DMA_MAP_ADDR2;
//	desc->lli->llp = cpu_to_le64(llp_addr);
//#else
	desc->lli->llp = cpu_to_le64(adr);
//#endif
}

static void write_chan_llp(struct axi_dma_chan *chan, dma_addr_t adr)
{
//#if (defined(CONFIG_E906) && defined(CONFIG_TB_RUN_DDR)) || defined(CONFIG_CACHE_LITE)
//	unsigned long long llp_addr = adr;
//	llp_addr = llp_addr - E906_DMA_MAP_ADDR1 + E906_DMA_MAP_ADDR2;
//	axi_chan_iowrite64(chan, CH_LLP, llp_addr);
//#else
	axi_chan_iowrite64(chan, CH_LLP, adr);
//#endif
}

#ifdef CONFIG_C920
extern volatile int dma_speed_test;
extern volatile int dma_speed_test;
extern unsigned long dma_start_time[8];
extern unsigned long dma_stop_time[8];
extern volatile int speed_start_index;
#endif

/* Called in chan locked context */
static void axi_chan_block_xfer_start(struct axi_dma_chan *chan,
				      struct axi_dma_desc *first)
{
	u32 priority = chan->chip->dw->hdata->priority[chan->id];
	struct axi_dma_chan_config config = {};
	u32 irq_mask;
	u8 lms = 0; /* Select AXI0 master for LLI fetching */

	if (unlikely(axi_chan_is_hw_enable(chan))) {
		dev_err(chan2dev(chan), "%s is non-idle!\n",
			axi_chan_name(chan));

		return;
	}

	axi_dma_enable(chan->chip);

	config.dst_multblk_type = DWAXIDMAC_MBLK_TYPE_LL;
	config.src_multblk_type = DWAXIDMAC_MBLK_TYPE_LL;
	config.tt_fc = DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC;
	config.prior = priority;
	config.hs_sel_dst = DWAXIDMAC_HS_SEL_HW;
	config.hs_sel_src = DWAXIDMAC_HS_SEL_HW;
	switch (chan->direction) {
	case DMA_MEM_TO_DEV:
		config.tt_fc = chan->config.device_fc ?
					     DWAXIDMAC_TT_FC_MEM_TO_PER_DST :
					     DWAXIDMAC_TT_FC_MEM_TO_PER_DMAC;
		config.dst_per = chan->dst_hw_handshake_num;
		break;
	case DMA_DEV_TO_MEM:
		config.tt_fc = chan->config.device_fc ?
					     DWAXIDMAC_TT_FC_PER_TO_MEM_SRC :
					     DWAXIDMAC_TT_FC_PER_TO_MEM_DMAC;
		config.src_per = chan->src_hw_handshake_num;
		break;
	case DMA_DEV_TO_DEV:
		config.tt_fc = chan->config.device_fc ?
					     DWAXIDMAC_TT_FC_PER_TO_PER_SRC :
					     DWAXIDMAC_TT_FC_PER_TO_PER_DMAC;
		config.src_per = chan->src_hw_handshake_num;
		config.dst_per = chan->dst_hw_handshake_num;
		break;
	default:
		break;
	}
	axi_chan_config_write(chan, &config);

	write_chan_llp(chan, first->hw_desc[0].llp | lms);

	irq_mask = DWAXIDMAC_IRQ_DMA_TRF | DWAXIDMAC_IRQ_ALL_ERR;
	axi_chan_irq_sig_set(chan, irq_mask);
	/* Generate 'suspend' status but don't generate interrupt */
	irq_mask |= DWAXIDMAC_IRQ_SUSPENDED;
	axi_chan_irq_set(chan, irq_mask);
#ifdef CONFIG_C920
	if (dma_speed_test)
		dma_start_time[speed_start_index] = get_timer_us(0);
#endif
	axi_chan_enable(chan);
}

static void axi_chan_start_first_queued(struct axi_dma_chan *chan)
{
	struct axi_dma_desc *desc;
	struct virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd)
		return;

	desc = vd_to_axi_desc(vd);
#if DEBUG_DMA
	dev_vdbg(chan2dev(chan), "%s: started %u\n", axi_chan_name(chan),
		 vd->tx.cookie);
#endif
	axi_chan_block_xfer_start(chan, desc);
}

static void dma_chan_issue_pending(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	if (vchan_issue_pending(&chan->vc))
		axi_chan_start_first_queued(chan);
}

static void dw_axi_dma_synchronize(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	vchan_synchronize(&chan->vc);
}

static int dma_chan_alloc_chan_resources(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSERT: channel is idle */
	if (axi_chan_is_hw_enable(chan)) {
		dev_err(chan2dev(chan), "%s is non-idle!\n",
			axi_chan_name(chan));
		return -EBUSY;
	}

	/* LLI address must be aligned to a 64-byte boundary */
	chan->desc_pool = dma_pool_create(dchan->devname, chan->chip->dev,
					  sizeof(struct axi_dma_lli), 64, 0);
	if (!chan->desc_pool) {
		dev_err(chan2dev(chan), "No memory for descriptors\n");
		return -ENOMEM;
	}
	dev_vdbg(dchan2dev(dchan), "%s: allocating\n", axi_chan_name(chan));

	return 0;
}

static void dma_chan_free_chan_resources(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSERT: channel is idle */
	if (axi_chan_is_hw_enable(chan))
		dev_err(dchan2dev(dchan), "%s is non-idle!\n",
			axi_chan_name(chan));

	axi_chan_disable(chan);
	axi_chan_irq_disable(chan, DWAXIDMAC_IRQ_ALL);

	vchan_free_chan_resources(&chan->vc);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = NULL;
	dev_vdbg(dchan2dev(dchan),
		 "%s: free resources, descriptor still allocated: %u\n",
		 axi_chan_name(chan), atomic_read(&chan->descs_allocated));
}

/*
 * If DW_axi_dmac sees CHx_CTL.ShadowReg_Or_LLI_Last bit of the fetched LLI
 * as 1, it understands that the current block is the final block in the
 * transfer and completes the DMA transfer operation at the end of current
 * block transfer.
 */
static void set_desc_last(struct axi_dma_hw_desc *desc)
{
	u32 val;

	val = le32_to_cpu(desc->lli->ctl_hi);
	val |= CH_CTL_H_LLI_LAST;
	desc->lli->ctl_hi = cpu_to_le32(val);
}

static void write_desc_sar(struct axi_dma_hw_desc *desc, dma_addr_t adr,
			   enum dma_transfer_direction direction)
{
//#if (defined(CONFIG_E906) && defined(CONFIG_TB_RUN_DDR)) || defined(CONFIG_CACHE_LITE)
//	unsigned long long sar_addr = adr;
//	if (direction == DMA_MEM_TO_MEM || direction == DMA_MEM_TO_DEV)
//		sar_addr = sar_addr - E906_DMA_MAP_ADDR1 + E906_DMA_MAP_ADDR2;
//
//	desc->lli->sar = cpu_to_le64(sar_addr);
//#else
	desc->lli->sar = cpu_to_le64(adr);
//#endif
}

static void write_desc_dar(struct axi_dma_hw_desc *desc, dma_addr_t adr,
			   enum dma_transfer_direction direction)
{
//#if (defined(CONFIG_E906) && defined(CONFIG_TB_RUN_DDR)) || defined(CONFIG_CACHE_LITE)
//	unsigned long long dar_addr = adr;
//	if (direction == DMA_MEM_TO_MEM || direction == DMA_DEV_TO_MEM)
//		dar_addr = dar_addr - E906_DMA_MAP_ADDR1 + E906_DMA_MAP_ADDR2;
//
//	desc->lli->dar = cpu_to_le64(dar_addr);
//#else
	desc->lli->dar = cpu_to_le64(adr);
//#endif
}

static void set_desc_src_master(struct axi_dma_hw_desc *desc)
{
	u32 val;

	/* Select AXI0 for source master */
	val = le32_to_cpu(desc->lli->ctl_lo);
	val &= ~CH_CTL_L_SRC_MAST;
	desc->lli->ctl_lo = cpu_to_le32(val);
}

static void set_desc_dest_master(struct axi_dma_hw_desc *hw_desc,
				 struct axi_dma_desc *desc)
{
	u32 val;

	/* Select AXI1 for source master if available */
	val = le32_to_cpu(hw_desc->lli->ctl_lo);
	if (desc->chan->chip->dw->hdata->nr_masters > 1)
		val |= CH_CTL_L_DST_MAST;
	else
		val &= ~CH_CTL_L_DST_MAST;

	hw_desc->lli->ctl_lo = cpu_to_le32(val);
}

static int get_burst_len(enum dma_slave_burstlen burst_len)
{
	int val;
	switch (burst_len) {
	case DMA_SLAVE_BURST_TRANS_LEN_1:
		val = DWAXIDMAC_BURST_TRANS_LEN_1;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_4:
		val = DWAXIDMAC_BURST_TRANS_LEN_4;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_8:
		val = DWAXIDMAC_BURST_TRANS_LEN_8;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_16:
		val = DWAXIDMAC_BURST_TRANS_LEN_16;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_32:
		val = DWAXIDMAC_BURST_TRANS_LEN_32;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_64:
		val = DWAXIDMAC_BURST_TRANS_LEN_64;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_128:
		val = DWAXIDMAC_BURST_TRANS_LEN_128;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_256:
		val = DWAXIDMAC_BURST_TRANS_LEN_256;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_512:
		val = DWAXIDMAC_BURST_TRANS_LEN_512;
		break;
	case DMA_SLAVE_BURST_TRANS_LEN_1024:
		val = DWAXIDMAC_BURST_TRANS_LEN_1024;
		break;
	default:
		val = DWAXIDMAC_BURST_TRANS_LEN_4;
		printf("Unsupported burst length, please re-selected!\n");
		break;
	}
	return val;
}

static int dw_axi_dma_set_hw_desc(struct axi_dma_chan *chan,
				  struct axi_dma_hw_desc *hw_desc,
				  dma_addr_t mem_addr, size_t len)
{
	unsigned int data_width = BIT(chan->chip->dw->hdata->m_data_width);
	unsigned int reg_width, src_dev_reg_width, dst_dev_reg_width;
	unsigned int mem_width;
	dma_addr_t src_device_addr = 0, dst_device_addr = 0;
	size_t axi_block_ts;
	size_t block_ts;
	u32 ctllo, ctlhi;
	u32 burst_len;

	axi_block_ts = chan->chip->dw->hdata->block_size[chan->id];

	mem_width = __ffs(data_width | mem_addr | len);
	if (mem_width > DWAXIDMAC_TRANS_WIDTH_32)
		mem_width = DWAXIDMAC_TRANS_WIDTH_32;

	if (chan->direction != DMA_DEV_TO_DEV) {
		if (!IS_ALIGNED(mem_addr, 4)) {
			dev_err(chan->chip->dev, "invalid buffer alignment\n");
			return -EINVAL;
		}
	}

	switch (chan->direction) {
	case DMA_MEM_TO_DEV:
		reg_width = __ffs(chan->config.dst_addr_width);
		dst_device_addr = chan->config.dst_addr;
		ctllo = reg_width << CH_CTL_L_DST_WIDTH_POS |
			mem_width << CH_CTL_L_SRC_WIDTH_POS |
			DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_DST_INC_POS |
			DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_SRC_INC_POS;
		block_ts = len >> mem_width;
		break;
	case DMA_DEV_TO_MEM:
		reg_width = __ffs(chan->config.src_addr_width);
		src_device_addr = chan->config.src_addr;
		ctllo = reg_width << CH_CTL_L_SRC_WIDTH_POS |
			mem_width << CH_CTL_L_DST_WIDTH_POS |
			DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_DST_INC_POS |
			DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_SRC_INC_POS;
		block_ts = len >> reg_width;
		break;
	case DMA_DEV_TO_DEV:
		src_dev_reg_width = __ffs(chan->config.src_addr_width);
		dst_dev_reg_width = __ffs(chan->config.dst_addr_width);
		src_device_addr = chan->config.src_addr;
		dst_device_addr = chan->config.dst_addr;
		ctllo = src_dev_reg_width << CH_CTL_L_SRC_WIDTH_POS |
			dst_dev_reg_width << CH_CTL_L_DST_WIDTH_POS |
			DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_DST_INC_POS |
			DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_SRC_INC_POS;
		block_ts = len >> src_dev_reg_width;
		break;
	default:
		return -EINVAL;
	}

	if (block_ts > axi_block_ts) {
		printf("error! block_ts: %d greater than axi_block_ts: %d!\n",
		       block_ts, axi_block_ts);
		return -EINVAL;
	}

	hw_desc->lli = axi_desc_get(chan, &hw_desc->llp);
	if (unlikely(!hw_desc->lli))
		return -ENOMEM;

	ctlhi = CH_CTL_H_LLI_VALID;

	if (chan->chip->dw->hdata->restrict_axi_burst_len) {
		burst_len = chan->chip->dw->hdata->axi_rw_burst_len;
		ctlhi |= CH_CTL_H_ARLEN_EN | CH_CTL_H_AWLEN_EN |
			 burst_len << CH_CTL_H_ARLEN_POS |
			 burst_len << CH_CTL_H_AWLEN_POS;
	}

	hw_desc->lli->ctl_hi = cpu_to_le32(ctlhi);

	if (chan->direction == DMA_MEM_TO_DEV) {
		write_desc_sar(hw_desc, mem_addr, chan->direction);
		write_desc_dar(hw_desc, dst_device_addr, chan->direction);
	} else if (chan->direction == DMA_DEV_TO_MEM) {
		write_desc_sar(hw_desc, src_device_addr, chan->direction);
		write_desc_dar(hw_desc, mem_addr, chan->direction);
	} else if (chan->direction == DMA_DEV_TO_DEV) {
		write_desc_sar(hw_desc, src_device_addr, chan->direction);
		write_desc_dar(hw_desc, dst_device_addr, chan->direction);
	}

	hw_desc->lli->block_ts_lo = cpu_to_le32(block_ts - 1);

	ctllo |= get_burst_len(chan->config.dst_burstlen)
			 << CH_CTL_L_DST_MSIZE_POS |
		 get_burst_len(chan->config.src_burstlen)
			 << CH_CTL_L_SRC_MSIZE_POS;
	hw_desc->lli->ctl_lo = cpu_to_le32(ctllo);

	set_desc_src_master(hw_desc);

	hw_desc->len = len;
	return 0;
}

static size_t calculate_block_len(struct axi_dma_chan *chan,
				  dma_addr_t dma_addr, size_t buf_len,
				  enum dma_transfer_direction direction)
{
	u32 data_width, reg_width, mem_width;
	size_t axi_block_ts, block_len;

	axi_block_ts = chan->chip->dw->hdata->block_size[chan->id];

	switch (direction) {
	case DMA_MEM_TO_DEV:
		data_width = BIT(chan->chip->dw->hdata->m_data_width);
		mem_width = __ffs(data_width | dma_addr | buf_len);
		if (mem_width > DWAXIDMAC_TRANS_WIDTH_32)
			mem_width = DWAXIDMAC_TRANS_WIDTH_32;

		block_len = axi_block_ts << mem_width;
		break;
	case DMA_DEV_TO_MEM:
		reg_width = __ffs(chan->config.src_addr_width);
		block_len = axi_block_ts << reg_width;
		break;
	case DMA_DEV_TO_DEV:
		reg_width = __ffs(chan->config.src_addr_width);
		block_len = axi_block_ts << reg_width;
		break;
	default:
		block_len = 0;
	}

	return block_len;
}

static struct dma_async_tx_descriptor *
dw_axi_dma_chan_prep_cyclic(struct dma_chan *dchan, dma_addr_t dma_addr,
			    size_t buf_len, size_t period_len,
			    enum dma_transfer_direction direction,
			    unsigned long flags)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	struct axi_dma_hw_desc *hw_desc = NULL;
	struct axi_dma_desc *desc = NULL;
	dma_addr_t src_addr = dma_addr;
	u32 num_periods, num_segments;
	size_t axi_block_len;
	u32 total_segments;
	u32 segment_len;
	unsigned int i;
	int status;
	u64 llp = 0;
	u8 lms = 0; /* Select AXI0 master for LLI fetching */

	num_periods = buf_len / period_len;

	axi_block_len = calculate_block_len(chan, dma_addr, buf_len, direction);
	if (axi_block_len == 0)
		return NULL;

	num_segments = DIV_ROUND_UP(period_len, axi_block_len);
	segment_len = DIV_ROUND_UP(period_len, num_segments);

	total_segments = num_periods * num_segments;

	desc = axi_desc_alloc(total_segments);
	if (unlikely(!desc))
		goto err_desc_get;

	chan->direction = direction;
	desc->chan = chan;
	chan->cyclic = true;
	desc->length = 0;
	desc->period_len = period_len;

	for (i = 0; i < total_segments; i++) {
		hw_desc = &desc->hw_desc[i];
		status = dw_axi_dma_set_hw_desc(chan, hw_desc, src_addr,
						segment_len);
		if (status < 0)
			goto err_desc_get;

		desc->length += hw_desc->len;
		/* Set end-of-link to the linked descriptor, so that cyclic
		 * callback function can be triggered during interrupt.
		 */
		set_desc_last(hw_desc);

		src_addr += segment_len;
	}

	llp = desc->hw_desc[0].llp;

	/* Managed transfer list */
	do {
		hw_desc = &desc->hw_desc[--total_segments];
		write_desc_llp(hw_desc, llp | lms);
		llp = hw_desc->llp;
	} while (total_segments);

	return vchan_tx_prep(&chan->vc, &desc->vd, flags);

err_desc_get:
	if (desc)
		axi_desc_put(desc);

	return NULL;
}

static struct dma_async_tx_descriptor *
dw_axi_dma_chan_prep_slave_sg(struct dma_chan *dchan, struct scatterlist *sgl,
			      unsigned int sg_len,
			      enum dma_transfer_direction direction,
			      unsigned long flags, void *context)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	struct axi_dma_hw_desc *hw_desc = NULL;
	struct axi_dma_desc *desc = NULL;
	u32 num_segments, segment_len;
	unsigned int loop = 0;
	struct scatterlist *sg;
	size_t axi_block_len;
	u32 len, num_sgs = 0;
	unsigned int i;
	dma_addr_t mem;
	int status;
	u64 llp = 0;
	u8 lms = 0; /* Select AXI0 master for LLI fetching */

	if (unlikely(!is_slave_direction(direction) || !sg_len))
		return NULL;

	mem = sg_dma_address(sgl);
	len = sg_dma_len(sgl);

	axi_block_len = calculate_block_len(chan, mem, len, direction);
	if (axi_block_len == 0)
		return NULL;

	for_each_sg(sgl, sg, sg_len, i)
		num_sgs += DIV_ROUND_UP(sg_dma_len(sg), axi_block_len);

	desc = axi_desc_alloc(num_sgs);
	if (unlikely(!desc))
		goto err_desc_get;

	desc->chan = chan;
	desc->length = 0;
	chan->direction = direction;

	for_each_sg(sgl, sg, sg_len, i) {
		mem = sg_dma_address(sg);
		len = sg_dma_len(sg);
		num_segments = DIV_ROUND_UP(sg_dma_len(sg), axi_block_len);
		segment_len = axi_block_len;
		do {
			hw_desc = &desc->hw_desc[loop++];
			if (num_segments == 1)
				status = dw_axi_dma_set_hw_desc(chan, hw_desc,
								mem, len);
			else
				status = dw_axi_dma_set_hw_desc(
					chan, hw_desc, mem, segment_len);
			if (status < 0)
				goto err_desc_get;

			desc->length += hw_desc->len;
			if (num_segments > 1) {
				len -= segment_len;
				mem += segment_len;
			}
		} while (--num_segments);
	}

	/* Set end-of-link to the last link descriptor of list */
	set_desc_last(&desc->hw_desc[num_sgs - 1]);

	/* Managed transfer list */
	do {
		hw_desc = &desc->hw_desc[--num_sgs];
		write_desc_llp(hw_desc, llp | lms);
		llp = hw_desc->llp;
	} while (num_sgs);

	return vchan_tx_prep(&chan->vc, &desc->vd, flags);

err_desc_get:
	if (desc)
		axi_desc_put(desc);

	return NULL;
}

static struct dma_async_tx_descriptor *
dma_chan_prep_dma_memcpy(struct dma_chan *dchan, dma_addr_t dst_adr,
			 dma_addr_t src_adr, size_t len, unsigned long flags)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	size_t block_ts, max_block_ts, xfer_len;
	struct axi_dma_hw_desc *hw_desc = NULL;
	struct axi_dma_desc *desc = NULL;
	u32 xfer_width, reg, num;
	u64 llp = 0;
	u8 lms = 0; /* Select AXI0 master for LLI fetching */

#if DEBUG_DMA
	dev_dbg(chan2dev(chan),
		"%s: memcpy: src: %pad dst: %pad length: %zd flags: %#lx",
		axi_chan_name(chan), &src_adr, &dst_adr, len, flags);
#endif

	max_block_ts = chan->chip->dw->hdata->block_size[chan->id];
	xfer_width = axi_chan_get_xfer_width(chan, src_adr, dst_adr, len);
	num = DIV_ROUND_UP(len, max_block_ts << xfer_width);
	desc = axi_desc_alloc(num);
	if (unlikely(!desc))
		goto err_desc_get;

	desc->chan = chan;
	num = 0;
	desc->length = 0;
	while (len) {
		xfer_len = len;
		hw_desc = &desc->hw_desc[num];
		/*
		 * Take care for the alignment.
		 * Actually source and destination widths can be different, but
		 * make them same to be simpler.
		 */
		xfer_width = axi_chan_get_xfer_width(chan, src_adr, dst_adr,
						     xfer_len);
		/*
		 * block_ts indicates the total number of data of width
		 * to be transferred in a DMA block transfer.
		 * BLOCK_TS register should be set to block_ts - 1
		 */
		block_ts = xfer_len >> xfer_width;
		if (block_ts > max_block_ts) {
			block_ts = max_block_ts;
			xfer_len = max_block_ts << xfer_width;
		}

		hw_desc->lli = axi_desc_get(chan, &hw_desc->llp);
		if (unlikely(!hw_desc->lli))
			goto err_desc_get;

		write_desc_sar(hw_desc, src_adr, chan->direction);
		write_desc_dar(hw_desc, dst_adr, chan->direction);
		hw_desc->lli->block_ts_lo = cpu_to_le32(block_ts - 1);

		reg = CH_CTL_H_LLI_VALID;
		if (chan->chip->dw->hdata->restrict_axi_burst_len) {
			u32 burst_len = chan->chip->dw->hdata->axi_rw_burst_len;

			reg |= (CH_CTL_H_ARLEN_EN |
				burst_len << CH_CTL_H_ARLEN_POS |
				CH_CTL_H_AWLEN_EN |
				burst_len << CH_CTL_H_AWLEN_POS);
		}
		hw_desc->lli->ctl_hi = cpu_to_le32(reg);
		reg = (DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_DST_MSIZE_POS |
		       DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_SRC_MSIZE_POS |
		       xfer_width << CH_CTL_L_DST_WIDTH_POS |
		       xfer_width << CH_CTL_L_SRC_WIDTH_POS |
		       DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_DST_INC_POS |
		       DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_SRC_INC_POS);
		hw_desc->lli->ctl_lo = cpu_to_le32(reg);

		set_desc_src_master(hw_desc);
		set_desc_dest_master(hw_desc, desc);

		hw_desc->len = xfer_len;
		desc->length += hw_desc->len;
		/* update the length and addresses for the next loop cycle */
		len -= xfer_len;
		dst_adr += xfer_len;
		src_adr += xfer_len;
		num++;
	}

	/* Set end-of-link to the last link descriptor of list */
	set_desc_last(&desc->hw_desc[num - 1]);
	/* Managed transfer list */
	do {
		//llp = hw_desc->llp;
		hw_desc = &desc->hw_desc[--num];
		write_desc_llp(hw_desc, llp | lms);
		llp = hw_desc->llp;
	} while (num);

	return vchan_tx_prep(&chan->vc, &desc->vd, flags);
err_desc_get:
	if (desc)
		axi_desc_put(desc);
	return NULL;
}

void dw_axi_dma_chan_set_hw_handshake_num(struct dma_chan *dchan,
					  int src_hw_handshake_num,
					  int dst_hw_handshake_num)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	chan->src_hw_handshake_num = src_hw_handshake_num;
	chan->dst_hw_handshake_num = dst_hw_handshake_num;
}

static int dw_axi_dma_chan_slave_config(struct dma_chan *dchan,
					struct dma_slave_config *config)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	memcpy(&chan->config, config, sizeof(*config));

	return 0;
}

static void axi_chan_dump_lli(struct axi_dma_chan *chan,
			      struct axi_dma_hw_desc *desc)
{
	if (!desc->lli) {
		dev_err(dchan2dev(&chan->vc.chan), "NULL LLI\n");
		return;
	}

	dev_err(dchan2dev(&chan->vc.chan),
		"SAR: 0x%llx DAR: 0x%llx LLP: 0x%llx BTS 0x%x CTL: 0x%x:%08x",
		le64_to_cpu(desc->lli->sar), le64_to_cpu(desc->lli->dar),
		le64_to_cpu(desc->lli->llp),
		le32_to_cpu(desc->lli->block_ts_lo),
		le32_to_cpu(desc->lli->ctl_hi), le32_to_cpu(desc->lli->ctl_lo));
}

static void axi_chan_list_dump_lli(struct axi_dma_chan *chan,
				   struct axi_dma_desc *desc_head)
{
	int count = atomic_read(&chan->descs_allocated);
	int i;

	for (i = 0; i < count; i++)
		axi_chan_dump_lli(chan, &desc_head->hw_desc[i]);
}

static void axi_chan_handle_err(struct axi_dma_chan *chan, u32 status)
{
	struct virt_dma_desc *vd;

	// spin_lock_irqsave(&chan->vc.lock, flags);

	axi_chan_disable(chan);

	/* The bad descriptor currently is in the head of vc list */
	vd = vchan_next_desc(&chan->vc);
	if (!vd) {
		dev_err(chan2dev(chan), "BUG: %s, IRQ with no descriptors\n",
			axi_chan_name(chan));
		goto out;
	}
	/* Remove the completed descriptor from issued list */
	list_del(&vd->node);

	/* WARN about bad descriptor */
	dev_err(chan2dev(chan),
		"Bad descriptor submitted for %s, cookie: %d, irq: 0x%08x\n",
		axi_chan_name(chan), vd->tx.cookie, status);
	axi_chan_list_dump_lli(chan, vd_to_axi_desc(vd));

	vchan_cookie_complete(vd);

	/* Try to restart the controller */
	axi_chan_start_first_queued(chan);

out:
	return;
}

static void axi_chan_block_xfer_complete(struct axi_dma_chan *chan)
{
	int count = atomic_read(&chan->descs_allocated);
	struct axi_dma_hw_desc *hw_desc;
	struct axi_dma_desc *desc;
	struct virt_dma_desc *vd;
	u64 llp;
	int i;

	// spin_lock_irqsave(&chan->vc.lock, flags);
	if (unlikely(axi_chan_is_hw_enable(chan))) {
		dev_err(chan2dev(chan),
			"BUG: %s caught DWAXIDMAC_IRQ_DMA_TRF, but channel not idle!\n",
			axi_chan_name(chan));
		axi_chan_disable(chan);
	}

	/* The completed descriptor currently is in the head of vc list */
	vd = vchan_next_desc(&chan->vc);
	if (!vd) {
		dev_err(chan2dev(chan), "BUG: %s, IRQ with no descriptors\n",
			axi_chan_name(chan));
		goto out;
	}

	if (chan->cyclic) {
		desc = vd_to_axi_desc(vd);
		if (desc) {
			llp = lo_hi_readq(chan->chan_regs + CH_LLP);
			for (i = 0; i < count; i++) {
				hw_desc = &desc->hw_desc[i];
				if (hw_desc->llp == llp) {
					axi_chan_irq_clear(
						chan, hw_desc->lli->status_lo);
					hw_desc->lli->ctl_hi |=
						CH_CTL_H_LLI_VALID;
					desc->completed_blocks = i;

					if (((hw_desc->len * (i + 1)) %
					     desc->period_len) == 0)
						vchan_cyclic_callback(vd);
					break;
				}
			}

			axi_chan_enable(chan);
		}
	} else {
		/* Remove the completed descriptor from issued list before completing */
		list_del(&vd->node);
		vchan_cookie_complete(vd);
		/* Submit queued descriptors after processing the completed ones */
		axi_chan_start_first_queued(chan);
	}

out:
	return;
}

/* gclk3 should be 48MHz for dw dma in pc player pro software or else no interrupt generated. */
static int dw_axi_dma_interrupt(int irq, void *dev_id)
{
	struct axi_dma_chip *chip = dev_id;
	struct dw_axi_dma *dw = chip->dw;
	struct axi_dma_chan *chan;
	u32 status, i;

	/* Disable DMAC inerrupts. We'll enable them after processing chanels */
	axi_dma_irq_disable(chip);

	/* Poll, clear and process every chanel interrupt status */
	for (i = 0; i < dw->hdata->nr_channels; i++) {
		chan = &dw->chan[i];
		status = axi_chan_irq_read(chan);
		axi_chan_irq_clear(chan, status);
#if DEBUG_DMA
		dev_vdbg(chip->dev, "%s %u IRQ status: 0x%08x\n",
			 axi_chan_name(chan), i, status);
#endif
		if (status & DWAXIDMAC_IRQ_ALL_ERR)
			axi_chan_handle_err(chan, status);
		else if (status & DWAXIDMAC_IRQ_DMA_TRF)
			axi_chan_block_xfer_complete(chan);
	}

	/* Re-enable interrupts */
	axi_dma_irq_enable(chip);
	return 0;
}

#define readl_poll_timeout_atomic(addr, val, cond, delay_us, timeout_us) \
	({                                                               \
		u64 __timeout_us = (timeout_us);                         \
		unsigned long __delay_us = (delay_us);                   \
		unsigned long base = get_timer(0);                       \
		for (;;) {                                               \
			val = readl(addr);                               \
			if (cond)                                        \
				break;                                   \
			if (__timeout_us &&                              \
			    (get_timer(base) > __timeout_us)) {          \
				val = readl(addr);                       \
				break;                                   \
			}                                                \
			if (__delay_us)                                  \
				udelay(__delay_us);                      \
		}                                                        \
		(cond) ? 0 : -ETIMEDOUT;                                 \
	})

static int dma_chan_terminate_all(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	u32 chan_active = BIT(chan->id) << DMAC_CHAN_EN_SHIFT;
	u32 val;
	int ret;
	LIST_HEAD(head);

	axi_chan_disable(chan);

	ret = readl_poll_timeout_atomic(chan->chip->regs + DMAC_CHEN, val,
					!(val & chan_active), 1000, 10000);
	if (ret == -ETIMEDOUT)
		dev_warn(dchan2dev(dchan), "%s failed to stop\n",
			 axi_chan_name(chan));

	// spin_lock_irqsave(&chan->vc.lock, flags);

	vchan_get_all_descriptors(&chan->vc, &head);

	chan->cyclic = false;
	// spin_unlock_irqrestore(&chan->vc.lock, flags);

	vchan_dma_desc_free_list(&chan->vc, &head);
	dev_vdbg(dchan2dev(dchan), "terminated: %s\n", axi_chan_name(chan));
	return 0;
}

static int dma_chan_pause(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	unsigned int timeout = 20; /* timeout iterations */
	u32 val;

	// spin_lock_irqsave(&chan->vc.lock, flags);

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);
	val |= BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT |
	       BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT;
	axi_dma_iowrite32(chan->chip, DMAC_CHEN, val);

	do {
		if (axi_chan_irq_read(chan) & DWAXIDMAC_IRQ_SUSPENDED)
			break;

		udelay(2);
	} while (--timeout);

	axi_chan_irq_clear(chan, DWAXIDMAC_IRQ_SUSPENDED);

	chan->is_paused = true;

	// spin_unlock_irqrestore(&chan->vc.lock, flags);

	return timeout ? 0 : -EAGAIN;
}

/* Called in chan locked context */
static inline void axi_chan_resume(struct axi_dma_chan *chan)
{
	u32 val;

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);
	val &= ~(BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT);
	val |= (BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT);
	axi_dma_iowrite32(chan->chip, DMAC_CHEN, val);

	chan->is_paused = false;
}

static int dma_chan_resume(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	// spin_lock_irqsave(&chan->vc.lock, flags);

	if (chan->is_paused)
		axi_chan_resume(chan);

	// spin_unlock_irqrestore(&chan->vc.lock, flags);

	return 0;
}

static int axi_dma_resume(struct axi_dma_chip *chip)
{
	axi_dma_enable(chip);
	axi_dma_irq_enable(chip);
	return 0;
}

static int parse_device_properties(struct axi_dma_chip *chip)
{
	int i;

	chip->dw->hdata->nr_channels = 8;
	chip->dw->hdata->nr_masters = 1;
	chip->dw->hdata->m_data_width = 3;

	/* max block size is equal to 2^22. all 22 bits. */
	for (i = 0; i < chip->dw->hdata->nr_channels; i++)
		chip->dw->hdata->block_size[i] = 4096; //4096 * 2;

	/* Priority value must be programmed within [0:nr_channels-1] range */
	for (i = 0; i < chip->dw->hdata->nr_channels; i++)
		chip->dw->hdata->priority[i] = 7;

	/* axi-max-burst-len is optional property */
	chip->dw->hdata->restrict_axi_burst_len = true;
	/* dmax_chx_max_amba_burst_length = 16 */
	chip->dw->hdata->axi_rw_burst_len = 16;
	return 0;
}

bool dma_inited[2] = { false, false };

bool itcs_is_dma_inited(int id)
{
	return dma_inited[id];
}

static struct device g_device;

int itcs_dma_init(int id)
{
	struct axi_dma_chip *chip;
	struct dw_axi_dma *dw;
	struct dw_axi_dma_hcfg *hdata;
	u32 i;
	int ret;

	if (id == 0)
		itcs_module_enable(CPU, "dma0");
	else if (id == 1)
		itcs_module_enable(CPU, "dma1");

	if (itcs_is_dma_inited(id))
		return 0;

	chip = (struct axi_dma_chip *)malloc(sizeof(*chip));
	if (!chip)
		return -ENOMEM;
	dw = (struct dw_axi_dma *)malloc(sizeof(*dw));
	if (!dw)
		return -ENOMEM;
	hdata = (struct dw_axi_dma_hcfg *)malloc(sizeof(*hdata));
	if (!hdata)
		return -ENOMEM;

	memset(chip, 0, sizeof(*chip));
	memset(dw, 0, sizeof(*dw));
	memset(hdata, 0, sizeof(*hdata));

	chip->dw = dw;

	INIT_LIST_HEAD(&g_device.dma_pools);
	chip->dev = &g_device;

	chip->dw->hdata = hdata;
	chip->irq = !id ? C_DMA0_IRQn : C_DMA1_IRQn;
	chip->regs = (void *)(!id ? ITCS_C_DMA0_BASE : ITCS_C_DMA1_BASE);
	chip->apb_regs = NULL;
	ret = parse_device_properties(chip);
	if (ret)
		return ret;

	dw->chan = (struct axi_dma_chan *)malloc(hdata->nr_channels *
						 sizeof(*(dw->chan)));
	if (!dw->chan)
		return -ENOMEM;

	memset(dw->chan, 0, hdata->nr_channels * sizeof(*(dw->chan)));

	ret = request_irq(chip->irq, dw_axi_dma_interrupt,
			  (!id ? "dma0" : "dma1"), chip);
	if (ret < 0)
		return ret;

	INIT_LIST_HEAD(&dw->dma.channels);
	for (i = 0; i < hdata->nr_channels; i++) {
		struct axi_dma_chan *chan = &dw->chan[i];
		chan->chip = chip;
		chan->id = i;
		chan->chan_regs =
			chip->regs + COMMON_REG_LEN + i * CHAN_REG_LEN;
		atomic_set(&chan->descs_allocated, 0);
		chan->vc.desc_free = vchan_desc_put;
		vchan_init(&chan->vc, &dw->dma);
	}

	/* DMA capabilities */
	sprintf(dw->dma.devname, "dma%d", id);
	dw->dma.chancnt = hdata->nr_channels;
	dw->dma.src_addr_widths = AXI_DMA_BUSWIDTHS;
	dw->dma.dst_addr_widths = AXI_DMA_BUSWIDTHS;
	dw->dma.directions = BIT(DMA_MEM_TO_MEM);
	dw->dma.directions |= BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM) |
			      BIT(DMA_DEV_TO_DEV);

	dw->dma.dev = chip->dev;
	dw->dma.device_tx_status = dma_chan_tx_status;
	dw->dma.device_issue_pending = dma_chan_issue_pending;
	dw->dma.device_terminate_all = dma_chan_terminate_all;
	dw->dma.device_pause = dma_chan_pause;
	dw->dma.device_resume = dma_chan_resume;

	dw->dma.device_alloc_chan_resources = dma_chan_alloc_chan_resources;
	dw->dma.device_free_chan_resources = dma_chan_free_chan_resources;

	dw->dma.device_prep_dma_memcpy = dma_chan_prep_dma_memcpy;
	dw->dma.device_synchronize = dw_axi_dma_synchronize;
	dw->dma.device_config = dw_axi_dma_chan_slave_config;
	dw->dma.device_prep_slave_sg = dw_axi_dma_chan_prep_slave_sg;
	dw->dma.device_prep_dma_cyclic = dw_axi_dma_chan_prep_cyclic;

	ret = axi_dma_resume(chip);
	if (ret < 0)
		goto err_pm_disable;

	axi_dma_hw_init(chip);

	itcs_dma_register(&dw->dma);
	dev_info(chip->dev, "DesignWare AXI DMA Controller, %d channels\n",
		 dw->hdata->nr_channels);

	dma_inited[id] = true;
	return 0;

err_pm_disable:
	return ret;
}
