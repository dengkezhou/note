#include <common.h>
#include <malloc.h>
#include <linux/scatterlist.h>
#include <dma-ops.h>
#include <dw-axi-dmac.h>

static LIST_HEAD(dma_device_list);

static struct dma_chan *dma_chan_get(struct dma_device *dev)
{
	struct dma_chan *chan = NULL;
	bool found = false;

	list_for_each_entry(chan, &dev->channels, device_node) {
		if (!chan->client_count) {
			chan->client_count++;
			found = true;
			break;
		}
	}
	if (!found)
		return NULL;

	return chan;
}

static void dma_chan_put(struct dma_chan *chan)
{
	chan->client_count = 0;
}

static void set_axi_chan_name(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	sprintf(dchan->devname, "channel %d", chan->id);
}

struct dma_chan *itcs_dma_request_channel(struct dma_info *info)
{
	struct dma_chan *chan = NULL;
	struct dma_device *device, *_d;
	int ret;

	list_for_each_entry_safe(device, _d, &dma_device_list, global_node) {
		if (strcmp(device->devname, info->devname))
			continue;

		chan = dma_chan_get(device);
		if (chan)
			break;
	}
	if (!chan)
		return NULL;

	set_axi_chan_name(chan);

	ret = chan->device->device_alloc_chan_resources(chan);
	if (ret < 0) {
		dma_chan_put(chan);
		return NULL;
	}

	dw_axi_dma_chan_set_hw_handshake_num(chan, info->src_hw_handshake_num,
					     info->dst_hw_handshake_num);
	return chan;
}

void itcs_dma_release_channel(struct dma_chan *chan)
{
	if (!chan || !chan->device)
		return;

	dma_chan_put(chan);
	return chan->device->device_free_chan_resources(chan);
}

dma_cookie_t itcs_dma_prepare(struct dma_chan *chan, struct dma_prep_info *info)
{
	struct dma_async_tx_descriptor *desc;

	if (!chan || !chan->device)
		return -1;

	if (info->direction == DMA_MEM_TO_MEM) {
		desc = chan->device->device_prep_dma_memcpy(chan, info->dst,
							    info->src,
							    info->len,
							    DMA_PREP_INTERRUPT);
	} else {
		if (info->mode == DMA_SLAVE) {
			struct scatterlist sg;
			sg_init_table(&sg, 1);
			sg_dma_address(&sg) =
				(info->direction == DMA_MEM_TO_DEV ||
				 info->direction == DMA_DEV_TO_DEV) ?
					      info->src :
					      info->dst;
			sg_dma_len(&sg) = info->len;

			desc = chan->device->device_prep_slave_sg(
				chan, &sg, 1, info->direction,
				DMA_PREP_INTERRUPT, NULL);
		} else {
			desc = chan->device->device_prep_dma_cyclic(
				chan,
				(info->direction == DMA_MEM_TO_DEV ||
				 info->direction == DMA_DEV_TO_DEV) ?
					      info->src :
					      info->dst,
				info->len, info->period_len, info->direction,
				DMA_PREP_INTERRUPT);
		}
	}
	if (!desc)
		return -1;

	if (info->callback) {
		desc->callback = info->callback;
		desc->callback_param = info->callback_param;
	}

	return desc->tx_submit(desc);
}

int itcs_dma_slave_config(struct dma_chan *chan, struct dma_slave_config *cfg)
{
	if (!chan || !chan->device)
		return -1;

	return chan->device->device_config(chan, cfg);
}

enum dma_status itcs_dma_transfer_completed(struct dma_chan *chan,
					    dma_cookie_t cookie,
					    struct dma_tx_state *txstate)
{
	if (!chan || !chan->device)
		return -1;

	return chan->device->device_tx_status(chan, chan->cookie, txstate);
}

int itcs_dma_start(struct dma_chan *chan)
{
	if (!chan || !chan->device)
		return -1;

	chan->device->device_issue_pending(chan);
	return 0;
}

int itcs_dma_stop(struct dma_chan *chan)
{
	if (!chan || !chan->device)
		return -1;

	return chan->device->device_terminate_all(chan);
}

void itcs_dma_register(struct dma_device *dev)
{
	list_add_tail(&dev->global_node, &dma_device_list);
}
