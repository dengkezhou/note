// SPDX-License-Identifier: GPL-2.0-only
/*
 * Virtual DMA channel support for DMAengine
 *
 * Copyright (C) 2012 Russell King
 */
#include "virt-dma.h"

static struct virt_dma_desc *to_virt_desc(struct dma_async_tx_descriptor *tx)
{
	return container_of(tx, struct virt_dma_desc, tx);
}

dma_cookie_t vchan_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct virt_dma_chan *vc = to_virt_chan(tx->chan);
	struct virt_dma_desc *vd = to_virt_desc(tx);
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(tx);

	list_move_tail(&vd->node, &vc->desc_submitted);

	dev_dbg(vc->chan.device->dev, "vchan %p: txd %p[%x]: submitted\n", vc,
		vd, cookie);

	return cookie;
}

/**
 * vchan_tx_desc_free - free a reusable descriptor
 * @tx: the transfer
 *
 * This function frees a previously allocated reusable descriptor. The only
 * other way is to clear the DMA_CTRL_REUSE flag and submit one last time the
 * transfer.
 *
 * Returns 0 upon success
 */
int vchan_tx_desc_free(struct dma_async_tx_descriptor *tx)
{
	struct virt_dma_chan *vc = to_virt_chan(tx->chan);
	struct virt_dma_desc *vd = to_virt_desc(tx);

	list_del(&vd->node);

	dev_dbg(vc->chan.device->dev, "vchan %p: txd %p[%x]: freeing\n", vc, vd,
		vd->tx.cookie);
	vc->desc_free(vd);
	return 0;
}

struct virt_dma_desc *vchan_find_desc(struct virt_dma_chan *vc,
				      dma_cookie_t cookie)
{
	struct virt_dma_desc *vd;

	list_for_each_entry(vd, &vc->desc_issued, node)
		if (vd->tx.cookie == cookie)
			return vd;

	return NULL;
}

/*
 * This tasklet handles the completion of a DMA descriptor by
 * calling its callback and freeing it.
 */
void vchan_complete(struct tasklet_struct *t)
{
	struct virt_dma_chan *vc = from_tasklet(vc, t, task);
	struct virt_dma_desc *vd, *_vd;
	struct dmaengine_desc_callback cb;
	LIST_HEAD(head);

	list_splice_tail_init(&vc->desc_completed, &head);
	vd = vc->cyclic;
	if (vd) {
		vc->cyclic = NULL;
		dmaengine_desc_get_callback(&vd->tx, &cb);
	} else {
		memset(&cb, 0, sizeof(cb));
	}

	dmaengine_desc_callback_invoke(&cb, &vd->tx_result);

	list_for_each_entry_safe(vd, _vd, &head, node) {
		dmaengine_desc_get_callback(&vd->tx, &cb);
		list_del(&vd->node);
		dmaengine_desc_callback_invoke(&cb, &vd->tx_result);
		vchan_vdesc_fini(vd);
	}
}

void vchan_dma_desc_free_list(struct virt_dma_chan *vc, struct list_head *head)
{
	struct virt_dma_desc *vd, *_vd;

	list_for_each_entry_safe(vd, _vd, head, node) {
		list_del(&vd->node);
		vchan_vdesc_fini(vd);
	}
}

void vchan_init(struct virt_dma_chan *vc, struct dma_device *dmadev)
{
	dma_cookie_init(&vc->chan);

	vc->chan.client_count = 0;

	INIT_LIST_HEAD(&vc->desc_allocated);
	INIT_LIST_HEAD(&vc->desc_submitted);
	INIT_LIST_HEAD(&vc->desc_issued);
	INIT_LIST_HEAD(&vc->desc_completed);
	INIT_LIST_HEAD(&vc->desc_terminated);

	vc->task.callback = vchan_complete;

	vc->chan.device = dmadev;
	list_add_tail(&vc->chan.device_node, &dmadev->channels);
}
