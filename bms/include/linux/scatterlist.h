/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SCATTERLIST_H
#define _LINUX_SCATTERLIST_H

#include <linux/string.h>
#include <linux/types.h>
#include <asm/io.h>

struct scatterlist {
	unsigned long page_link;
	unsigned int offset;
	unsigned int length;
	dma_addr_t dma_address;
#ifdef CONFIG_NEED_SG_DMA_LENGTH
	unsigned int dma_length;
#endif
};

/*
 * These macros should be used after a dma_map_sg call has been done
 * to get bus addresses of each of the SG entries and their lengths.
 * You should only work with the number of sg entries dma_map_sg
 * returns, or alternatively stop on the first sg_dma_len(sg) which
 * is 0.
 */
#define sg_dma_address(sg) ((sg)->dma_address)

#ifdef CONFIG_NEED_SG_DMA_LENGTH
#define sg_dma_len(sg) ((sg)->dma_length)
#else
#define sg_dma_len(sg) ((sg)->length)
#endif

struct sg_table {
	struct scatterlist *sgl; /* the list */
	unsigned int nents; /* number of mapped entries */
	unsigned int orig_nents; /* original size of list */
};

/*
 * Notes on SG table design.
 *
 * We use the unsigned long page_link field in the scatterlist struct to place
 * the page pointer AND encode information about the sg table as well. The two
 * lower bits are reserved for this information.
 *
 * If bit 0 is set, then the page_link contains a pointer to the next sg
 * table list. Otherwise the next entry is at sg + 1.
 *
 * If bit 1 is set, then this sg entry is the last element in a list.
 *
 * See sg_next().
 *
 */

#define SG_CHAIN 0x01UL
#define SG_END 0x02UL

/*
 * We overload the LSB of the page pointer to indicate whether it's
 * a valid sg entry, or whether it points to the start of a new scatterlist.
 * Those low bits are there for everyone! (thanks mason :-)
 */
#define sg_is_chain(sg) ((sg)->page_link & SG_CHAIN)
#define sg_is_last(sg) ((sg)->page_link & SG_END)
#define sg_chain_ptr(sg) \
	((struct scatterlist *)((sg)->page_link & ~(SG_CHAIN | SG_END)))

static inline struct scatterlist *sg_next(struct scatterlist *sg)
{
	if (sg_is_last(sg))
		return NULL;

	sg++;
	if (unlikely(sg_is_chain(sg)))
		sg = sg_chain_ptr(sg);

	return sg;
}

/*
 * Loop over each sg element, following the pointer to a new list if necessary
 */
#define for_each_sg(sglist, sg, nr, __i) \
	for (__i = 0, sg = (sglist); __i < (nr); __i++, sg = sg_next(sg))

static inline void sg_mark_end(struct scatterlist *sg)
{
	/*
   * Set termination bit, clear potential chain bit
   */
	sg->page_link |= SG_END;
	sg->page_link &= ~SG_CHAIN;
}

static inline void sg_init_marker(struct scatterlist *sgl, unsigned int nents)
{
	sg_mark_end(&sgl[nents - 1]);
}

static inline void sg_init_table(struct scatterlist *sgl, unsigned int nents)
{
	memset(sgl, 0, sizeof(*sgl) * nents);
	sg_init_marker(sgl, nents);
}
#endif /* _LINUX_SCATTERLIST_H */
