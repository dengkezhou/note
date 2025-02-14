/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2004 - 2006 Intel Corporation. All rights reserved.
 */
#ifndef LINUX_DMAENGINE_H
#define LINUX_DMAENGINE_H

#include <linux/err.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/scatterlist.h>
#include <common.h>
#include <stdbool.h>

/**
 * typedef dma_cookie_t - an opaque DMA cookie
 *
 * if dma_cookie_t is >0 it's a DMA request cookie, <0 it's an error code
 */
typedef s32 dma_cookie_t;
#define DMA_MIN_COOKIE 1

static inline int dma_submit_error(dma_cookie_t cookie)
{
	return cookie < 0 ? cookie : 0;
}

/**
 * enum dma_status - DMA transaction status
 * @DMA_COMPLETE: transaction completed
 * @DMA_IN_PROGRESS: transaction not yet processed
 * @DMA_PAUSED: transaction is paused
 * @DMA_ERROR: transaction failed
 */
enum dma_status {
	DMA_COMPLETE,
	DMA_IN_PROGRESS,
	DMA_PAUSED,
	DMA_ERROR,
	DMA_OUT_OF_ORDER,
};

/**
 * enum dma_transfer_direction - dma transfer mode and direction indicator
 * @DMA_MEM_TO_MEM: Async/Memcpy mode
 * @DMA_MEM_TO_DEV: Slave mode & From Memory to Device
 * @DMA_DEV_TO_MEM: Slave mode & From Device to Memory
 * @DMA_DEV_TO_DEV: Slave mode & From Device to Device
 */
enum dma_transfer_direction {
	DMA_MEM_TO_MEM,
	DMA_MEM_TO_DEV,
	DMA_DEV_TO_MEM,
	DMA_DEV_TO_DEV,
	DMA_TRANS_NONE,
};

/**
 * struct dma_chan - devices supply DMA channels, clients use them
 * @device: ptr to the dma device who supplies this channel, always !%NULL
 * @slave: ptr to the device using this channel
 * @cookie: last cookie value returned to client
 * @completed_cookie: last completed cookie for this channel
 * @chan_id: channel ID for sysfs
 * @dev: class device for sysfs
 * @name: backlink name for sysfs
 * @dbg_client_name: slave name for debugfs in format:
 *	dev_name(requester's dev):channel name, for example: "2b00000.mcasp:tx"
 * @device_node: used to add this to the device chan list
 * @local: per-cpu pointer to a struct dma_chan_percpu
 * @client_count: how many clients are using this channel
 * @table_count: number of appearances in the mem-to-mem allocation table
 * @router: pointer to the DMA router structure
 * @route_data: channel specific data for the router
 * @private: private data for certain client-channel associations
 */
struct dma_chan {
	struct dma_device *device;
	char devname[16];

	struct list_head device_node;
	int client_count;
	dma_cookie_t cookie;
	dma_cookie_t completed_cookie;

	struct dma_async_tx_descriptor *desc;
	struct dma_info *info;
	void *private;
};

/**
 * enum dma_slave_buswidth - defines bus width of the DMA slave
 * device, source or target buses
 */
enum dma_slave_buswidth {
	DMA_SLAVE_BUSWIDTH_UNDEFINED = 0,
	DMA_SLAVE_BUSWIDTH_1_BYTE = 1,
	DMA_SLAVE_BUSWIDTH_2_BYTES = 2,
	DMA_SLAVE_BUSWIDTH_3_BYTES = 3,
	DMA_SLAVE_BUSWIDTH_4_BYTES = 4,
	DMA_SLAVE_BUSWIDTH_8_BYTES = 8,
	DMA_SLAVE_BUSWIDTH_16_BYTES = 16,
	DMA_SLAVE_BUSWIDTH_32_BYTES = 32,
	DMA_SLAVE_BUSWIDTH_64_BYTES = 64,
};

enum dma_slave_burstlen {
	DMA_SLAVE_BURST_TRANS_LEN_1 = 1,
	DMA_SLAVE_BURST_TRANS_LEN_4 = 4,
	DMA_SLAVE_BURST_TRANS_LEN_8 = 8,
	DMA_SLAVE_BURST_TRANS_LEN_16 = 16,
	DMA_SLAVE_BURST_TRANS_LEN_32 = 32,
	DMA_SLAVE_BURST_TRANS_LEN_64 = 64,
	DMA_SLAVE_BURST_TRANS_LEN_128 = 128,
	DMA_SLAVE_BURST_TRANS_LEN_256 = 256,
	DMA_SLAVE_BURST_TRANS_LEN_512 = 512,
	DMA_SLAVE_BURST_TRANS_LEN_1024 = 1024
};

/**
 * struct dma_slave_config - dma slave channel runtime config
 * @direction: whether the data shall go in or out on this slave
 * channel, right now. DMA_MEM_TO_DEV and DMA_DEV_TO_MEM are
 * legal values. DEPRECATED, drivers should use the direction argument
 * to the device_prep_slave_sg and device_prep_dma_cyclic functions or
 * the dir field in the dma_interleaved_template structure.
 * @src_addr: this is the physical address where DMA slave data
 * should be read (RX), if the source is memory this argument is
 * ignored.
 * @dst_addr: this is the physical address where DMA slave data
 * should be written (TX), if the source is memory this argument
 * is ignored.
 * @src_addr_width: this is the width in bytes of the source (RX)
 * register where DMA data shall be read. If the source
 * is memory this may be ignored depending on architecture.
 * Legal values: 1, 2, 3, 4, 8, 16, 32, 64.
 * @dst_addr_width: same as src_addr_width but for destination
 * target (TX) mutatis mutandis.
 * @src_burstlen: the number of words (note: words, as in
 * units of the src_addr_width member, not bytes) that can be sent
 * in one burst to the device. Typically something like half the
 * FIFO depth on I/O peripherals so you don't overflow it. This
 * may or may not be applicable on memory sources.
 * @dst_burstlen: same as src_burstlen but for destination target
 * mutatis mutandis.
 * @device_fc: Flow Controller Settings. Only valid for slave channels. Fill
 * with 'true' if peripheral should be flow controller. Direction will be
 * selected at Runtime.
 *
 * This struct is passed in as configuration data to a DMA engine
 * in order to set up a certain channel for DMA transport at runtime.
 * The DMA device/engine has to provide support for an additional
 * callback in the dma_device structure, device_config and this struct
 * will then be passed in as an argument to the function.
 *
 * The rationale for adding configuration information to this struct is as
 * follows: if it is likely that more than one DMA slave controllers in
 * the world will support the configuration option, then make it generic.
 * If not: if it is fixed so that it be sent in static from the platform
 * data, then prefer to do that.
 */
struct dma_slave_config {
	enum dma_transfer_direction direction;
	phys_addr_t src_addr;
	phys_addr_t dst_addr;
	enum dma_slave_buswidth src_addr_width;
	enum dma_slave_buswidth dst_addr_width;
	enum dma_slave_burstlen src_burstlen;
	enum dma_slave_burstlen dst_burstlen;
	bool device_fc;
};

typedef void (*dma_async_tx_callback)(void *dma_async_param);

static inline const char *dma_chan_name(struct dma_chan *chan)
{
	return chan->devname;
}

enum dmaengine_tx_result {
	DMA_TRANS_NOERROR = 0, /* SUCCESS */
	DMA_TRANS_READ_FAILED, /* Source DMA read failed */
	DMA_TRANS_WRITE_FAILED, /* Destination DMA write failed */
	DMA_TRANS_ABORTED, /* Op never submitted / aborted */
};

struct dmaengine_result {
	enum dmaengine_tx_result result;
	u32 residue;
};

typedef void (*dma_async_tx_callback_result)(
	void *dma_async_param, const struct dmaengine_result *result);

enum dma_ctrl_flags {
	DMA_PREP_INTERRUPT = (1 << 0),
	DMA_CTRL_ACK = (1 << 1),
	DMA_PREP_PQ_DISABLE_P = (1 << 2),
	DMA_PREP_PQ_DISABLE_Q = (1 << 3),
	DMA_PREP_CONTINUE = (1 << 4),
	DMA_PREP_FENCE = (1 << 5),
	DMA_CTRL_REUSE = (1 << 6),
	DMA_PREP_CMD = (1 << 7),
	DMA_PREP_REPEAT = (1 << 8),
	DMA_PREP_LOAD_EOT = (1 << 9),
};

struct dma_async_tx_descriptor {
	dma_cookie_t cookie;
	enum dma_ctrl_flags flags; /* not a 'long' to pack with cookie */
	dma_addr_t phys;
	struct dma_chan *chan;
	dma_cookie_t (*tx_submit)(struct dma_async_tx_descriptor *tx);
	int (*desc_free)(struct dma_async_tx_descriptor *tx);
	dma_async_tx_callback callback;
	dma_async_tx_callback_result callback_result;
	void *callback_param;
};

/**
 * struct dma_tx_state - filled in to report the status of
 * a transfer.
 * @last: last completed DMA cookie
 * @used: last issued DMA cookie (i.e. the one in progress)
 * @residue: the remaining number of bytes left to transmit
 *	on the selected transfer for states DMA_IN_PROGRESS and
 *	DMA_PAUSED if this is implemented in the driver, else 0
 * @in_flight_bytes: amount of data in bytes cached by the DMA.
 */
struct dma_tx_state {
	dma_cookie_t last;
	dma_cookie_t used;
	u32 residue;
	u32 in_flight_bytes;
};

struct dma_device {
	char devname[16];
	struct list_head channels;
	struct list_head global_node;
	unsigned int chancnt;
	uint32_t src_addr_widths;
	uint32_t dst_addr_widths;
	uint32_t directions;

	struct device *dev;

	int (*device_alloc_chan_resources)(struct dma_chan *chan);
	void (*device_free_chan_resources)(struct dma_chan *chan);

	struct dma_async_tx_descriptor *(*device_prep_dma_memcpy)(
		struct dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		size_t len, unsigned long flags);
	struct dma_async_tx_descriptor *(*device_prep_dma_cyclic)(
		struct dma_chan *chan, dma_addr_t buf_addr, size_t buf_len,
		size_t period_len, enum dma_transfer_direction direction,
		unsigned long flags);
	struct dma_async_tx_descriptor *(*device_prep_slave_sg)(
		struct dma_chan *chan, struct scatterlist *sgl,
		unsigned int sg_len, enum dma_transfer_direction direction,
		unsigned long flags, void *context);
	int (*device_config)(struct dma_chan *chan,
			     struct dma_slave_config *config);
	void (*device_synchronize)(struct dma_chan *chan);
	enum dma_status (*device_tx_status)(struct dma_chan *chan,
					    dma_cookie_t cookie,
					    struct dma_tx_state *txstate);
	void (*device_issue_pending)(struct dma_chan *chan);
	int (*device_terminate_all)(struct dma_chan *chan);
	int (*device_pause)(struct dma_chan *chan);
	int (*device_resume)(struct dma_chan *chan);
};

static inline void
dmaengine_desc_clear_reuse(struct dma_async_tx_descriptor *tx)
{
	tx->flags &= ~DMA_CTRL_REUSE;
}

static inline bool dmaengine_desc_test_reuse(struct dma_async_tx_descriptor *tx)
{
	return (tx->flags & DMA_CTRL_REUSE) == DMA_CTRL_REUSE;
}

static inline void
dma_async_tx_descriptor_init(struct dma_async_tx_descriptor *tx,
			     struct dma_chan *chan)
{
	tx->chan = chan;
}

struct dmaengine_desc_callback {
	dma_async_tx_callback callback;
	dma_async_tx_callback_result callback_result;
	void *callback_param;
};

/**
 * dmaengine_desc_get_callback - get the passed in callback function
 * @tx: tx descriptor
 * @cb: temp struct to hold the callback info
 *
 * Fill the passed in cb struct with what's available in the passed in
 * tx descriptor struct
 * No locking is required.
 */
static inline void
dmaengine_desc_get_callback(struct dma_async_tx_descriptor *tx,
			    struct dmaengine_desc_callback *cb)
{
	cb->callback = tx->callback;
	cb->callback_result = tx->callback_result;
	cb->callback_param = tx->callback_param;
}

/**
 * dmaengine_desc_callback_invoke - call the callback function in cb struct
 * @cb: temp struct that is holding the callback info
 * @result: transaction result
 *
 * Call the callback function provided in the cb struct with the parameter
 * in the cb struct.
 * Locking is dependent on the driver.
 */
static inline void
dmaengine_desc_callback_invoke(struct dmaengine_desc_callback *cb,
			       const struct dmaengine_result *result)
{
	struct dmaengine_result dummy_result = { .result = DMA_TRANS_NOERROR,
						 .residue = 0 };

	if (cb->callback_result) {
		if (!result)
			result = &dummy_result;
		cb->callback_result(cb->callback_param, result);
	} else if (cb->callback) {
		cb->callback(cb->callback_param);
	}
}

/**
 * dma_async_is_complete - test a cookie against chan state
 * @cookie: transaction identifier to test status of
 * @last_complete: last know completed transaction
 * @last_used: last cookie value handed out
 *
 * dma_async_is_complete() is used in dma_async_is_tx_complete()
 * the test logic is separated for lightweight testing of multiple cookies
 */
static inline enum dma_status dma_async_is_complete(dma_cookie_t cookie,
						    dma_cookie_t last_complete,
						    dma_cookie_t last_used)
{
	if (last_complete <= last_used) {
		if ((cookie <= last_complete) || (cookie > last_used))
			return DMA_COMPLETE;
	} else {
		if ((cookie <= last_complete) && (cookie > last_used))
			return DMA_COMPLETE;
	}
	return DMA_IN_PROGRESS;
}

/**
 * dma_cookie_init - initialize the cookies for a DMA channel
 * @chan: dma channel to initialize
 */
static inline void dma_cookie_init(struct dma_chan *chan)
{
	chan->cookie = DMA_MIN_COOKIE;
	chan->completed_cookie = DMA_MIN_COOKIE;
}

/**
 * dma_cookie_assign - assign a DMA engine cookie to the descriptor
 * @tx: descriptor needing cookie
 *
 * Assign a unique non-zero per-channel cookie to the descriptor.
 * Note: caller is expected to hold a lock to prevent concurrency.
 */
static inline dma_cookie_t dma_cookie_assign(struct dma_async_tx_descriptor *tx)
{
	struct dma_chan *chan = tx->chan;
	dma_cookie_t cookie;

	cookie = chan->cookie + 1;
	if (cookie < DMA_MIN_COOKIE)
		cookie = DMA_MIN_COOKIE;
	tx->cookie = chan->cookie = cookie;

	return cookie;
}

/**
 * dma_cookie_complete - complete a descriptor
 * @tx: descriptor to complete
 *
 * Mark this descriptor complete by updating the channels completed
 * cookie marker.  Zero the descriptors cookie to prevent accidental
 * repeated completions.
 *
 * Note: caller is expected to hold a lock to prevent concurrency.
 */
static inline void dma_cookie_complete(struct dma_async_tx_descriptor *tx)
{
	tx->chan->completed_cookie = tx->cookie;
	tx->cookie = 0;
}

/**
 * dma_cookie_status - report cookie status
 * @chan: dma channel
 * @cookie: cookie we are interested in
 * @state: dma_tx_state structure to return last/used cookies
 *
 * Report the status of the cookie, filling in the state structure if
 * non-NULL.  No locking is required.
 */
static inline enum dma_status dma_cookie_status(struct dma_chan *chan,
						dma_cookie_t cookie,
						struct dma_tx_state *state)
{
	dma_cookie_t used, complete;

	used = chan->cookie;
	complete = chan->completed_cookie;
	// barrier();
	if (state) {
		state->last = complete;
		state->used = used;
		state->residue = 0;
		state->in_flight_bytes = 0;
	}
	return dma_async_is_complete(cookie, complete, used);
}

static inline void dma_set_residue(struct dma_tx_state *state, u32 residue)
{
	if (state)
		state->residue = residue;
}

#endif /* DMAENGINE_H */
