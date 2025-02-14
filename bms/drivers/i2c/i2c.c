// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * I2C bus driver for the Cadence I2C controller.
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.
 */

#include <common.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <linux/err.h>
#include <pads.h>
#include <i2c.h>

#define BIT(nr) (1 << nr)

#define I2C_SMBUS_BLOCK_MAX 32

#define BITS_PER_BYTE 8

/* Register offsets for the I2C device. */
#define CDNS_I2C_CR_OFFSET 0x00 /* Control Register, RW */
#define CDNS_I2C_SR_OFFSET 0x04 /* Status Register, RO */
#define CDNS_I2C_ADDR_OFFSET 0x08 /* I2C Address Register, RW */
#define CDNS_I2C_DATA_OFFSET 0x0C /* I2C Data Register, RW */
#define CDNS_I2C_ISR_OFFSET 0x10 /* IRQ Status Register, RW */
#define CDNS_I2C_XFER_SIZE_OFFSET 0x14 /* Transfer Size Register, RW */
#define CDNS_I2C_SLV_MON_PAUSE_OFFSET 0x18
#define CDNS_I2C_TIME_OUT_OFFSET 0x1C /* Time Out Register, RW */
#define CDNS_I2C_IMR_OFFSET 0x20 /* IRQ Mask Register, RO */
#define CDNS_I2C_IER_OFFSET 0x24 /* IRQ Enable Register, WO */
#define CDNS_I2C_IDR_OFFSET 0x28 /* IRQ Disable Register, WO */

/* Control Register Bit mask definitions */
#define CDNS_I2C_CR_SLVMON BIT(5)
#define CDNS_I2C_CR_HOLD BIT(4) /* Hold Bus bit */
#define CDNS_I2C_CR_ACK_EN BIT(3)
#define CDNS_I2C_CR_NEA BIT(2)
#define CDNS_I2C_CR_MS BIT(1)
/* Read or Write Master transfer 0 = Transmitter, 1 = Receiver */
#define CDNS_I2C_CR_RW BIT(0)
/* 1 = Auto init FIFO to zeroes */
#define CDNS_I2C_CR_CLR_FIFO BIT(6)
#define CDNS_I2C_CR_DIVA_SHIFT 14
#define CDNS_I2C_CR_DIVA_MASK (3 << CDNS_I2C_CR_DIVA_SHIFT)
#define CDNS_I2C_CR_DIVB_SHIFT 8
#define CDNS_I2C_CR_DIVB_MASK (0x3f << CDNS_I2C_CR_DIVB_SHIFT)

#define CDNS_I2C_CR_MASTER_EN_MASK \
	(CDNS_I2C_CR_NEA | CDNS_I2C_CR_ACK_EN | CDNS_I2C_CR_MS)

#define CDNS_I2C_CR_SLAVE_EN_MASK ~CDNS_I2C_CR_MASTER_EN_MASK

/* Status Register Bit mask definitions */
#define CDNS_I2C_SR_BA BIT(8)
#define CDNS_I2C_SR_TXDV BIT(6)
#define CDNS_I2C_SR_RXDV BIT(5)
#define CDNS_I2C_SR_RXRW BIT(3)

/*
 * I2C Address Register Bit mask definitions
 * Normal addressing mode uses [6:0] bits. Extended addressing mode uses [9:0]
 * bits. A write access to this register always initiates a transfer if the I2C
 * is in master mode.
 */
#define CDNS_I2C_ADDR_MASK 0x000003FF /* I2C Address Mask */

/*
 * I2C Interrupt Registers Bit mask definitions
 * All the four interrupt registers (Status/Mask/Enable/Disable) have the same
 * bit definitions.
 */
#define CDNS_I2C_IXR_ARB_LOST BIT(9)
#define CDNS_I2C_IXR_RX_UNF BIT(7)
#define CDNS_I2C_IXR_TX_OVF BIT(6)
#define CDNS_I2C_IXR_RX_OVF BIT(5)
#define CDNS_I2C_IXR_SLV_RDY BIT(4)
#define CDNS_I2C_IXR_TO BIT(3)
#define CDNS_I2C_IXR_NACK BIT(2)
#define CDNS_I2C_IXR_DATA BIT(1)
#define CDNS_I2C_IXR_COMP BIT(0)

#define CDNS_I2C_IXR_ALL_INTR_MASK                                           \
	(CDNS_I2C_IXR_ARB_LOST | CDNS_I2C_IXR_RX_UNF | CDNS_I2C_IXR_TX_OVF | \
	 CDNS_I2C_IXR_RX_OVF | CDNS_I2C_IXR_SLV_RDY | CDNS_I2C_IXR_TO |      \
	 CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_DATA | CDNS_I2C_IXR_COMP)

#define CDNS_I2C_IXR_ERR_INTR_MASK                                           \
	(CDNS_I2C_IXR_ARB_LOST | CDNS_I2C_IXR_RX_UNF | CDNS_I2C_IXR_TX_OVF | \
	 CDNS_I2C_IXR_RX_OVF | CDNS_I2C_IXR_NACK)

#define CDNS_I2C_ENABLED_INTR_MASK                                           \
	(CDNS_I2C_IXR_ARB_LOST | CDNS_I2C_IXR_RX_UNF | CDNS_I2C_IXR_TX_OVF | \
	 CDNS_I2C_IXR_RX_OVF | CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_DATA |       \
	 CDNS_I2C_IXR_COMP)

#define CDNS_I2C_IXR_SLAVE_INTR_MASK                                       \
	(CDNS_I2C_IXR_RX_UNF | CDNS_I2C_IXR_TX_OVF | CDNS_I2C_IXR_RX_OVF | \
	 CDNS_I2C_IXR_TO | CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_DATA |         \
	 CDNS_I2C_IXR_COMP)

/* ms */
#define CDNS_I2C_TIMEOUT 1000

#define CDNS_I2C_FIFO_DEPTH 16
/* FIFO depth at which the DATA interrupt occurs */
#define CDNS_I2C_DATA_INTR_DEPTH (CDNS_I2C_FIFO_DEPTH - 2)
#define CDNS_I2C_MAX_TRANSFER_SIZE 255
/* Transfer size in multiples of data interrupt depth */
#define CDNS_I2C_TRANSFER_SIZE (CDNS_I2C_MAX_TRANSFER_SIZE - 3)

#define CDNS_I2C_DIVA_MAX 4
#define CDNS_I2C_DIVB_MAX 64

#define CDNS_I2C_TIMEOUT_MAX 0xFF

#define CDNS_I2C_BROKEN_HOLD_BIT BIT(0)

#ifdef CONFIG_TBH_I2C
extern unsigned int i2cx_multiplex_enable;
#else
static unsigned int i2cx_multiplex_enable = 0;
#endif

static int slv_rdy_flag = 0;

struct cdns_platform_data {
	u32 quirks;
};

static u32 cdns_i2c_readreg(void *membase, u32 offset)
{
	return readl((unsigned long)membase + offset);
}

static void cdns_i2c_writereg(void *membase, u32 offset, u32 val)
{
	writel(val, (unsigned long)membase + offset);
}

/**
 * cdns_i2c_clear_bus_hold - Clear bus hold bit
 * @id:	Pointer to driver data struct
 *
 * Helper to clear the controller's bus hold bit.
 */
static void cdns_i2c_clear_bus_hold(struct cdns_i2c *id)
{
	u32 reg = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
	if (reg & CDNS_I2C_CR_HOLD)
		cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
				  reg & ~CDNS_I2C_CR_HOLD);
}

static inline bool cdns_is_holdquirk(struct cdns_i2c *id, bool hold_wrkaround)
{
	return (hold_wrkaround &&
		(id->curr_recv_count == CDNS_I2C_FIFO_DEPTH + 1));
}

#if IS_ENABLED(CONFIG_I2C_SLAVE)
static void cdns_i2c_set_mode(i2c_mode mode, struct cdns_i2c *id)
{
	/* Disable all interrupts */
	cdns_i2c_writereg(id->membase, CDNS_I2C_IDR_OFFSET,
			  CDNS_I2C_IXR_ALL_INTR_MASK);

	/* Clear FIFO and transfer size */
	cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
			  CDNS_I2C_CR_CLR_FIFO);

	/* Update device mode and state */
	id->dev_mode = mode;
	id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;

	switch (mode) {
	case I2C_MASTER:
		/* Enable i2c master */
		cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
				  id->ctrl_reg_diva_divb |
					  CDNS_I2C_CR_MASTER_EN_MASK);
		/*
		 * This delay is needed to give the IP some time to switch to
		 * the master mode. With lower values(like 110 us) i2cdetect
		 * will not detect any slave and without this delay, the IP will
		 * trigger a timeout interrupt.
		 */
		udelay(125);
		break;
	case I2C_SLAVE:
		/* Enable i2c slave */
		cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
				  id->ctrl_reg_diva_divb &
					  CDNS_I2C_CR_SLAVE_EN_MASK);

		/* Setting slave address */
		cdns_i2c_writereg(id->membase, CDNS_I2C_ADDR_OFFSET,
				  id->slave->addr & CDNS_I2C_ADDR_MASK);

		/* Enable slave send/receive interrupts */
		cdns_i2c_writereg(id->membase, CDNS_I2C_IER_OFFSET,
				  CDNS_I2C_IXR_SLAVE_INTR_MASK);
		break;
	}
}

static void cdns_i2c_slave_rcv_data(struct cdns_i2c *id)
{
	u8 bytes;
	unsigned char data;
	/* Prepare backend for data reception */
	if (id->slave_state == CDNS_I2C_SLAVE_STATE_IDLE)
		id->slave_state = CDNS_I2C_SLAVE_STATE_RECV;

	/* Fetch number of bytes to receive */
	bytes = cdns_i2c_readreg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET);

	/* Read data and send to backend */
	while (bytes--) {
		data = cdns_i2c_readreg(id->membase, CDNS_I2C_DATA_OFFSET);
		*id->slave->slv_recv_buf++ = data;
		id->slave->slv_recv_count--;
	}
}

static void cdns_i2c_slave_send_data(struct cdns_i2c *id)
{
#if 0
	unsigned int avail_bytes = 0;
	unsigned int bytes_to_send = 0;
#endif
	/* Prepare backend for data transmission */
	if (id->slave_state == CDNS_I2C_SLAVE_STATE_IDLE)
		id->slave_state = CDNS_I2C_SLAVE_STATE_SEND;

	
        cdns_i2c_writereg(id->membase, CDNS_I2C_DATA_OFFSET, *(id->slave->slv_send_buf + id->slave->slv_curr_send_count));
	id->slave->slv_curr_send_count++;
	id->slave->slv_send_count--;
}

/**
 * cdns_i2c_slave_isr - Interrupt handler for the I2C device in slave role
 * @ptr:       Pointer to I2C device private data
 *
 * This function handles the data interrupt and transfer complete interrupt of
 * the I2C device in slave role.
 *
 * Return: IRQ_HANDLED always
 */
static int cdns_i2c_slave_isr(void *ptr)
{
	struct cdns_i2c *id = ptr;
	unsigned int isr_status, i2c_status;

	/* Fetch the interrupt status */
	isr_status = cdns_i2c_readreg(id->membase, CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(id->membase, CDNS_I2C_ISR_OFFSET, isr_status);

	/* Ignore masked interrupts */
	isr_status &= ~cdns_i2c_readreg(id->membase, CDNS_I2C_IMR_OFFSET);

	/* Fetch transfer mode (send/receive) */
	i2c_status = cdns_i2c_readreg(id->membase, CDNS_I2C_SR_OFFSET);

	/* Handle data send/receive */
	if (i2c_status & CDNS_I2C_SR_RXRW) {
		/* Send data to master */
		if (isr_status & CDNS_I2C_IXR_DATA)
			cdns_i2c_slave_send_data(id);

		if (isr_status & CDNS_I2C_IXR_COMP)
			id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
	} else {
		/* Receive data from master */
		if (isr_status & CDNS_I2C_IXR_DATA)
			cdns_i2c_slave_rcv_data(id);

		if (isr_status & CDNS_I2C_IXR_COMP) {
			cdns_i2c_slave_rcv_data(id);
			id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
		}
	}

	/* Master indicated xfer stop or fifo underflow/overflow */
	if (isr_status & (CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_RX_OVF |
			  CDNS_I2C_IXR_RX_UNF | CDNS_I2C_IXR_TX_OVF)) {
		id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
		cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
				  CDNS_I2C_CR_CLR_FIFO);
	}

	return 0;
}
#endif

/**
 * cdns_i2c_master_isr - Interrupt handler for the I2C device in master role
 * @ptr:       Pointer to I2C device private data
 *
 * This function handles the data interrupt, transfer complete interrupt and
 * the error interrupts of the I2C device in master role.
 *
 * Return: IRQ_HANDLED always
 */
static int cdns_i2c_master_isr(void *ptr)
{
	unsigned int isr_status, avail_bytes;
	unsigned int bytes_to_send;
	bool updatetx;
	struct cdns_i2c *id = ptr;
	/* Signal completion only after everything is updated */
	int done_flag = 0;
	unsigned int tmp_status;
	/* 1.5ms from 100khz and fifo depth 16, it is 10us * (8bit + 1ack) * 16 = 1440us */
	unsigned int timeout = 1500;

	isr_status = cdns_i2c_readreg(id->membase, CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(id->membase, CDNS_I2C_ISR_OFFSET, isr_status);
	id->err_status = 0;

	if (isr_status & CDNS_I2C_IXR_SLV_RDY) {
		slv_rdy_flag = 1;
		tmp_status = cdns_i2c_readreg(id->membase, CDNS_I2C_IMR_OFFSET);
		tmp_status |= CDNS_I2C_IXR_SLV_RDY;
		cdns_i2c_writereg(id->membase, CDNS_I2C_IDR_OFFSET, tmp_status);
		cdns_i2c_writereg(id->membase, CDNS_I2C_SLV_MON_PAUSE_OFFSET, 0);
		return 0;
	}

	/* Handling nack and arbitration lost interrupt */
	if (isr_status & (CDNS_I2C_IXR_NACK | CDNS_I2C_IXR_ARB_LOST))
		done_flag = 1;

	/*
	 * Check if transfer size register needs to be updated again for a
	 * large data receive operation.
	 */
	updatetx = id->recv_count > id->curr_recv_count;

	/* When receiving, handle data interrupt and completion interrupt */
	if (id->p_recv_buf && ((isr_status & CDNS_I2C_IXR_COMP) ||
			       (isr_status & CDNS_I2C_IXR_DATA))) {
		/* Read data if receive data valid is set */
		while (cdns_i2c_readreg(id->membase, CDNS_I2C_SR_OFFSET) &
		       CDNS_I2C_SR_RXDV) {
			if (id->recv_count > 0) {
				*(id->p_recv_buf)++ = cdns_i2c_readreg(
					id->membase, CDNS_I2C_DATA_OFFSET);
				id->recv_count--;
				id->curr_recv_count--;
				id->readed_cnt++;

				/*
				 * Clear hold bit that was set for FIFO control
				 * if RX data left is less than or equal to
				 * FIFO DEPTH unless repeated start is selected
				 */
				if (id->recv_count <= CDNS_I2C_FIFO_DEPTH &&
				    !id->bus_hold_flag)
					cdns_i2c_clear_bus_hold(id);

			} else {
#if DEBUG_I2C
				printf("xfer_size reg rollover. xfer aborted!\n");
#endif
				id->err_status |= CDNS_I2C_IXR_TO;
				break;
			}

			if (cdns_is_holdquirk(id, updatetx))
				break;
		}
		/*
		 * The controller sends NACK to the slave when transfer size
		 * register reaches zero without considering the HOLD bit.
		 * This workaround is implemented for large data transfers to
		 * maintain transfer size non-zero while performing a large
		 * receive operation.
		 */
		if (cdns_is_holdquirk(id, updatetx)) {
			/* wait while fifo is full until timeout */
			while (cdns_i2c_readreg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET) !=
			       (id->curr_recv_count - CDNS_I2C_FIFO_DEPTH)) {
				timeout--;
				udelay(1);
				if (timeout == 0)
					break;
			}
			/* only for inter-connect test between master recv and slave send */
			if (timeout == 0) {
				/* CDNS_I2C_XFER_SIZE_OFFSET reg definitely is CDNS_I2C_TRANSFER_SIZE */
				id->left_in_fifo = (CDNS_I2C_TRANSFER_SIZE - cdns_i2c_readreg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET) + id->left_in_fifo) - id->readed_cnt;
				id->readed_cnt = 0;

				if (((int)(id->recv_count) - id->left_in_fifo) >
				    CDNS_I2C_TRANSFER_SIZE) {
					cdns_i2c_writereg(id->membase,
							  CDNS_I2C_XFER_SIZE_OFFSET,
							  CDNS_I2C_TRANSFER_SIZE);
					id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE +
							      id->left_in_fifo;
				} else {
					cdns_i2c_writereg(
						id->membase, CDNS_I2C_XFER_SIZE_OFFSET,
						id->recv_count - id->left_in_fifo);
					id->curr_recv_count = id->recv_count;
				}
                        } else {
				id->readed_cnt = 0;
				/*
				 * Check number of bytes to be received against maximum
				 * transfer size and update register accordingly.
				 */
				if (((int)(id->recv_count) - CDNS_I2C_FIFO_DEPTH) >
					CDNS_I2C_TRANSFER_SIZE) {
					cdns_i2c_writereg(id->membase,
							  CDNS_I2C_XFER_SIZE_OFFSET,
							  CDNS_I2C_TRANSFER_SIZE);
					id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE +
							      CDNS_I2C_FIFO_DEPTH;
				} else {
					cdns_i2c_writereg(
						id->membase, CDNS_I2C_XFER_SIZE_OFFSET,
						id->recv_count - CDNS_I2C_FIFO_DEPTH);
					id->curr_recv_count = id->recv_count;
				}
			}
		}

		/* Clear hold (if not repeated start) and signal completion */
		if ((isr_status & CDNS_I2C_IXR_COMP) && !id->recv_count) {
			if (!id->bus_hold_flag)
				cdns_i2c_clear_bus_hold(id);
			done_flag = 1;
		}
	}

	/* When sending, handle transfer complete interrupt */
	if ((isr_status & CDNS_I2C_IXR_COMP) && !id->p_recv_buf) {
		/*
		 * If there is more data to be sent, calculate the
		 * space available in FIFO and fill with that many bytes.
		 */
		if (id->send_count) {
			avail_bytes =
				CDNS_I2C_FIFO_DEPTH -
				cdns_i2c_readreg(id->membase,
						 CDNS_I2C_XFER_SIZE_OFFSET);
			if (id->send_count > avail_bytes)
				bytes_to_send = avail_bytes;
			else
				bytes_to_send = id->send_count;

			while (bytes_to_send--) {
				cdns_i2c_writereg(id->membase,
						  CDNS_I2C_DATA_OFFSET,
						  (*(id->p_send_buf)++));
				id->send_count--;
			}
		} else {
			/*
			 * Signal the completion of transaction and
			 * clear the hold bus bit if there are no
			 * further messages to be processed.
			 */
			done_flag = 1;
		}
		if (!id->send_count && !id->bus_hold_flag)
			cdns_i2c_clear_bus_hold(id);
	}

	/* Update the status for errors */
	id->err_status |= isr_status & CDNS_I2C_IXR_ERR_INTR_MASK;

	if (done_flag)
		id->xfer_done = 1;

	return 0;
}

/**
 * cdns_i2c_isr - Interrupt handler for the I2C device
 * @irq:	irq number for the I2C device
 * @ptr:	void pointer to cdns_i2c structure
 *
 * This function passes the control to slave/master based on current role of
 * i2c controller.
 *
 * Return: IRQ_HANDLED always
 */
static int cdns_i2c_isr(int irq, void *ptr)
{
#if IS_ENABLED(CONFIG_I2C_SLAVE)
	struct cdns_i2c *id = ptr;

	if (id->dev_mode == I2C_SLAVE)
		return cdns_i2c_slave_isr(ptr);
#endif
	return cdns_i2c_master_isr(ptr);
}

/**
 * cdns_i2c_mrecv - Prepare and start a master receive operation
 * @id:		pointer to the i2c device structure
 */
static void cdns_i2c_mrecv(struct cdns_i2c *id)
{
	unsigned int ctrl_reg;
	unsigned int isr_status;
	bool hold_clear = false;

	u32 addr;

	id->p_recv_buf = id->p_msg->buf;
	id->recv_count = id->p_msg->len;

	/* Put the controller in master receive mode and clear the FIFO */
	ctrl_reg = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
	ctrl_reg |= CDNS_I2C_CR_RW | CDNS_I2C_CR_CLR_FIFO;

	/*
	 * Receive up to I2C_SMBUS_BLOCK_MAX data bytes, plus one message length
	 * byte, plus one checksum byte if PEC is enabled. p_msg->len will be 2 if
	 * PEC is enabled, otherwise 1.
	 */
	if (id->p_msg->flags & I2C_M_RECV_LEN)
		id->recv_count = I2C_SMBUS_BLOCK_MAX + id->p_msg->len;

	id->curr_recv_count = id->recv_count;

	/*
	 * Check for the message size against FIFO depth and set the
	 * 'hold bus' bit if it is greater than FIFO depth.
	 */
	if (id->recv_count > CDNS_I2C_FIFO_DEPTH)
		ctrl_reg |= CDNS_I2C_CR_HOLD;

	cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, ctrl_reg);

	/* Clear the interrupts in interrupt status register */
	isr_status = cdns_i2c_readreg(id->membase, CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(id->membase, CDNS_I2C_ISR_OFFSET, isr_status);

	/*
	 * The no. of bytes to receive is checked against the limit of
	 * max transfer size. Set transfer size register with no of bytes
	 * receive if it is less than transfer size and transfer size if
	 * it is more. Enable the interrupts.
	 */
	if (id->recv_count > CDNS_I2C_TRANSFER_SIZE) {
		cdns_i2c_writereg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET,
				  CDNS_I2C_TRANSFER_SIZE);
		id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE;
	} else {
		cdns_i2c_writereg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET,
				  id->recv_count);
	}

	/* Determine hold_clear based on number of bytes to receive and hold flag */
	if (!id->bus_hold_flag &&
	    ((id->p_msg->flags & I2C_M_RECV_LEN) != I2C_M_RECV_LEN) &&
	    (id->recv_count <= CDNS_I2C_FIFO_DEPTH)) {
		if (cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET) &
		    CDNS_I2C_CR_HOLD) {
			hold_clear = true;
		}
	}

	addr = id->p_msg->addr;
	addr &= CDNS_I2C_ADDR_MASK;

	if (hold_clear) {
		ctrl_reg = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET) &
			   ~CDNS_I2C_CR_HOLD;
		/*
		 * In case of Xilinx Zynq SOC, clear the HOLD bit before transfer size
		 * register reaches '0'. This is an IP bug which causes transfer size
		 * register overflow to 0xFF. To satisfy this timing requirement,
		 * disable the interrupts on current processor core between register
		 * writes to slave address register and control register.
		 */
		cdns_i2c_writereg(id->membase, CDNS_I2C_ADDR_OFFSET, addr);
		cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, ctrl_reg);
		/* Read it back to avoid bufferring and make sure write happens */
		cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
	} else {
		cdns_i2c_writereg(id->membase, CDNS_I2C_ADDR_OFFSET, addr);
	}

	cdns_i2c_writereg(id->membase, CDNS_I2C_IER_OFFSET,
			  CDNS_I2C_ENABLED_INTR_MASK);
}

/**
 * cdns_i2c_msend - Prepare and start a master send operation
 * @id:		pointer to the i2c device
 */
static void cdns_i2c_msend(struct cdns_i2c *id)
{
	unsigned int avail_bytes;
	unsigned int bytes_to_send;
	unsigned int ctrl_reg;
	unsigned int isr_status;

	id->p_recv_buf = NULL;
	id->p_send_buf = id->p_msg->buf;
	id->send_count = id->p_msg->len;

	/* Set the controller in Master transmit mode and clear the FIFO. */
	ctrl_reg = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
	ctrl_reg &= ~CDNS_I2C_CR_RW;
	ctrl_reg |= CDNS_I2C_CR_CLR_FIFO;

	/*
	 * Check for the message size against FIFO depth and set the
	 * 'hold bus' bit if it is greater than FIFO depth.
	 */
	if (id->send_count > CDNS_I2C_FIFO_DEPTH)
		ctrl_reg |= CDNS_I2C_CR_HOLD;
	cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, ctrl_reg);

	/* Clear the interrupts in interrupt status register. */
	isr_status = cdns_i2c_readreg(id->membase, CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(id->membase, CDNS_I2C_ISR_OFFSET, isr_status);

	/*
	 * Calculate the space available in FIFO. Check the message length
	 * against the space available, and fill the FIFO accordingly.
	 * Enable the interrupts.
	 */
	avail_bytes = CDNS_I2C_FIFO_DEPTH -
		      cdns_i2c_readreg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET);

	if (id->send_count > avail_bytes)
		bytes_to_send = avail_bytes;
	else
		bytes_to_send = id->send_count;

	while (bytes_to_send--) {
		cdns_i2c_writereg(id->membase, CDNS_I2C_DATA_OFFSET,
				  (*(id->p_send_buf)++));
		id->send_count--;
	}

	/*
	 * Clear the bus hold flag if there is no more data
	 * and if it is the last message.
	 */
	if (!id->bus_hold_flag && !id->send_count)
		cdns_i2c_clear_bus_hold(id);
	/* Set the slave address in address register - triggers operation. */
	cdns_i2c_writereg(id->membase, CDNS_I2C_ADDR_OFFSET,
			  id->p_msg->addr & CDNS_I2C_ADDR_MASK);

	cdns_i2c_writereg(id->membase, CDNS_I2C_IER_OFFSET,
			  CDNS_I2C_ENABLED_INTR_MASK);
}

/**
 * cdns_i2c_master_reset - Reset the interface
 * @adap:	pointer to the i2c adapter driver instance
 *
 * This function cleanup the fifos, clear the hold bit and status
 * and disable the interrupts.
 */
static void cdns_i2c_master_reset(struct cdns_i2c_adapter *adap)
{
	struct cdns_i2c *id = adap->algo_data;
	u32 regval;

	/* Disable the interrupts */
	cdns_i2c_writereg(id->membase, CDNS_I2C_IDR_OFFSET,
			  CDNS_I2C_IXR_ALL_INTR_MASK);
	/* Clear the hold bit and fifos */
	regval = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
	regval &= ~CDNS_I2C_CR_HOLD;
	regval |= CDNS_I2C_CR_CLR_FIFO;
	cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, regval);
	/* Update the transfercount register to zero */
	cdns_i2c_writereg(id->membase, CDNS_I2C_XFER_SIZE_OFFSET, 0);
	/* Clear the interrupt status register */
	regval = cdns_i2c_readreg(id->membase, CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(id->membase, CDNS_I2C_ISR_OFFSET, regval);
	/* Clear the status register */
	regval = cdns_i2c_readreg(id->membase, CDNS_I2C_SR_OFFSET);
	cdns_i2c_writereg(id->membase, CDNS_I2C_SR_OFFSET, regval);
}

static int cdns_i2c_process_msg(struct cdns_i2c *id, struct cdns_i2c_msg *msg,
				struct cdns_i2c_adapter *adap)
{
	unsigned long time_left, msg_timeout;
	u32 reg;

	id->p_msg = msg;
	id->err_status = 0;
	id->xfer_done = 0;

	/* Check for the TEN Bit mode on each msg */
	reg = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
	if (msg->flags & I2C_M_TEN) {
		if (reg & CDNS_I2C_CR_NEA)
			cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
					  reg & ~CDNS_I2C_CR_NEA);
	} else {
		if (!(reg & CDNS_I2C_CR_NEA))
			cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET,
					  reg | CDNS_I2C_CR_NEA);
	}

	/* Check for the R/W flag on each msg */
	if (msg->flags & I2C_M_RD)
		cdns_i2c_mrecv(id);
	else
		cdns_i2c_msend(id);

	/* msg_timeout unit: ms. */
	/* Minimal time to execute this message */
	msg_timeout = (1000 * msg->len * BITS_PER_BYTE) / id->i2c_clk;
	/* Plus some wiggle room */
	msg_timeout += 500;


	if (msg_timeout < adap->timeout)
		msg_timeout = adap->timeout;

	//msg_timeout *= 1000;

	time_left = msg_timeout;
	/* Wait for the signal of completion */
	while (!id->xfer_done && msg_timeout--) {
		udelay(10);
		time_left = msg_timeout;
	}
	if (time_left == 0) {
		cdns_i2c_master_reset(adap);
#if DEBUG_I2C
		printf("timeout waiting on completion\n");
#endif
		return -ETIMEDOUT;
	}

	cdns_i2c_writereg(id->membase, CDNS_I2C_IDR_OFFSET,
			  CDNS_I2C_IXR_ALL_INTR_MASK);

	/* If it is bus arbitration error, try again */
	if (id->err_status & CDNS_I2C_IXR_ARB_LOST)
		return -EAGAIN;

	if (msg->flags & I2C_M_RECV_LEN)
		msg->len +=
			min_t(unsigned int, msg->buf[0], I2C_SMBUS_BLOCK_MAX);

	return 0;
}

/**
 * cdns_i2c_master_xfer - The main i2c transfer function
 * @adap:	pointer to the i2c adapter driver instance
 * @msgs:	pointer to the i2c message structure
 * @num:	the number of messages to transfer
 *
 * Initiates the send/recv activity based on the transfer message received.
 *
 * Return: number of msgs processed on success, negative error otherwise
 */
static int cdns_i2c_master_xfer(struct cdns_i2c_adapter *adap,
				struct cdns_i2c_msg *msgs, int num)
{
	int ret = 0, count;
	u32 reg;
	struct cdns_i2c *id = adap->algo_data;
	bool hold_quirk;
#if IS_ENABLED(CONFIG_I2C_SLAVE)
	bool change_role = false;
#endif

#if IS_ENABLED(CONFIG_I2C_SLAVE)
	/* Check i2c operating mode and switch if possible */
	if (id->dev_mode == I2C_SLAVE) {
		if (id->slave_state != CDNS_I2C_SLAVE_STATE_IDLE)
			return -EAGAIN;

		/* Set mode to master */
		cdns_i2c_set_mode(I2C_MASTER, id);

		/* Mark flag to change role once xfer is completed */
		change_role = true;
	}
#endif

	/* Check if the bus is free */
	if (cdns_i2c_readreg(id->membase, CDNS_I2C_SR_OFFSET) &
	    CDNS_I2C_SR_BA) {
		ret = -EAGAIN;
		goto out;
	}

	hold_quirk = !!(id->quirks & CDNS_I2C_BROKEN_HOLD_BIT);
	/*
	 * Set the flag to one when multiple messages are to be
	 * processed with a repeated start.
	 */
	if (num > 1) {
		/*
		 * This controller does not give completion interrupt after a
		 * master receive message if HOLD bit is set (repeated start),
		 * resulting in SW timeout. Hence, if a receive message is
		 * followed by any other message, an error is returned
		 * indicating that this sequence is not supported.
		 */
		for (count = 0; (count < num - 1 && hold_quirk); count++) {
			if (msgs[count].flags & I2C_M_RD) {
#if DEBUG_I2C
				printf("Can't do repeated start after a receive message\n");
#endif
				ret = -EOPNOTSUPP;
				goto out;
			}
		}
		id->bus_hold_flag = 1;
		reg = cdns_i2c_readreg(id->membase, CDNS_I2C_CR_OFFSET);
		reg |= CDNS_I2C_CR_HOLD;
		cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, reg);
	} else {
		id->bus_hold_flag = 0;
	}

	/* Process the msg one by one */
	for (count = 0; count < num; count++, msgs++) {
		if (count == (num - 1))
			id->bus_hold_flag = 0;

		ret = cdns_i2c_process_msg(id, msgs, adap);
		if (ret)
			goto out;

		/* Report the other error interrupts to application */
		if (id->err_status) {
			cdns_i2c_master_reset(adap);

			if (id->err_status & CDNS_I2C_IXR_NACK) {
				ret = -ENXIO;
				goto out;
			}
			ret = -EIO;
			goto out;
		}
	}
	ret = num;
out:
#if IS_ENABLED(CONFIG_I2C_SLAVE)
	/* Switch i2c mode to slave */
	if (change_role)
		cdns_i2c_set_mode(I2C_SLAVE, id);
#endif
	return ret;
}

#if IS_ENABLED(CONFIG_I2C_SLAVE)
static int cdns_reg_slave(struct cdns_i2c_client *slave)
{
	struct cdns_i2c *id =
		container_of(slave->adapter, struct cdns_i2c, adap);

	if (!id->slave)
		return -EBUSY;

	if (slave->flags & I2C_CLIENT_TEN)
		return -EAFNOSUPPORT;

	/* Enable I2C slave */
	cdns_i2c_set_mode(I2C_SLAVE, id);

	return 0;
}

static int cdns_unreg_slave(struct cdns_i2c_client *slave)
{
	struct cdns_i2c *id =
		container_of(slave->adapter, struct cdns_i2c, adap);

	/* Enable I2C master */
	cdns_i2c_set_mode(I2C_MASTER, id);

	return 0;
}
#endif

/**
 * cdns_i2c_calc_divs - Calculate clock dividers
 * @f:		I2C clock frequency
 * @input_clk:	Input clock frequency
 * @a:		First divider (return value)
 * @b:		Second divider (return value)
 *
 * f is used as input and output variable. As input it is used as target I2C
 * frequency. On function exit f holds the actually resulting I2C frequency.
 *
 * Return: 0 on success, negative errno otherwise.
 */
static int cdns_i2c_calc_divs(unsigned long *f, unsigned long input_clk,
			      unsigned int *a, unsigned int *b)
{
	unsigned long fscl = *f, best_fscl = *f, actual_fscl, temp;
	unsigned int div_a, div_b, calc_div_a = 0, calc_div_b = 0;
	unsigned int last_error, current_error;

	/* calculate (divisor_a+1) x (divisor_b+1) */
	temp = input_clk / (22 * fscl);

	/*
	 * If the calculated value is negative or 0, the fscl input is out of
	 * range. Return error.
	 */
	if (!temp || (temp > (CDNS_I2C_DIVA_MAX * CDNS_I2C_DIVB_MAX)))
		return -EINVAL;

	last_error = -1;
	for (div_a = 0; div_a < CDNS_I2C_DIVA_MAX; div_a++) {
		div_b = DIV_ROUND_UP(input_clk, 22 * fscl * (div_a + 1));

		if ((div_b < 1) || (div_b > CDNS_I2C_DIVB_MAX))
			continue;
		div_b--;

		actual_fscl = input_clk / (22 * (div_a + 1) * (div_b + 1));

		if (actual_fscl > fscl)
			continue;

		current_error = ((actual_fscl > fscl) ? (actual_fscl - fscl) :
							      (fscl - actual_fscl));

		if (last_error > current_error) {
			calc_div_a = div_a;
			calc_div_b = div_b;
			best_fscl = actual_fscl;
			last_error = current_error;
		}
	}

	*a = calc_div_a;
	*b = calc_div_b;
	*f = best_fscl;

	return 0;
}

/**
 * cdns_i2c_setclk - This function sets the serial clock rate for the I2C device
 * @clk_in:	I2C clock input frequency in Hz
 * @id:		Pointer to the I2C device structure
 *
 * The device must be idle rather than busy transferring data before setting
 * these device options.
 * The data rate is set by values in the control register.
 * The formula for determining the correct register values is
 *	Fscl = Fpclk/(22 x (divisor_a+1) x (divisor_b+1))
 * See the hardware data sheet for a full explanation of setting the serial
 * clock rate. The clock can not be faster than the input clock divide by 22.
 * The two most common clock rates are 100KHz and 400KHz.
 *
 * Return: 0 on success, negative error otherwise
 */
static int cdns_i2c_setclk(unsigned long clk_in, struct cdns_i2c *id)
{
	unsigned int div_a, div_b;
	unsigned int ctrl_reg;
	int ret = 0;
	unsigned long fscl = id->i2c_clk;

	ret = cdns_i2c_calc_divs(&fscl, clk_in, &div_a, &div_b);
	if (ret)
		return ret;

	ctrl_reg = id->ctrl_reg;
	ctrl_reg &= ~(CDNS_I2C_CR_DIVA_MASK | CDNS_I2C_CR_DIVB_MASK);
	ctrl_reg |= ((div_a << CDNS_I2C_CR_DIVA_SHIFT) |
		     (div_b << CDNS_I2C_CR_DIVB_SHIFT));
	id->ctrl_reg = ctrl_reg;
	cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, ctrl_reg);
#if IS_ENABLED(CONFIG_I2C_SLAVE)
	id->ctrl_reg_diva_divb =
		ctrl_reg & (CDNS_I2C_CR_DIVA_MASK | CDNS_I2C_CR_DIVB_MASK);
#endif
	return 0;
}

/**
 * cdns_i2c_init -  Controller initialisation
 * @id:		Device private data structure
 *
 * Initialise the i2c controller.
 *
 */
static void cdns_i2c_init(struct cdns_i2c *id)
{
	cdns_i2c_writereg(id->membase, CDNS_I2C_CR_OFFSET, id->ctrl_reg);
	/*
	 * Cadence I2C controller has a bug wherein it generates
	 * invalid read transaction after HW timeout in master receiver mode.
	 * HW timeout is not used by this driver and the interrupt is disabled.
	 * But the feature itself cannot be disabled. Hence maximum value
	 * is written to this register to reduce the chances of error.
	 */
	cdns_i2c_writereg(id->membase, CDNS_I2C_TIME_OUT_OFFSET,
			  CDNS_I2C_TIMEOUT_MAX);
}

/**
 * itcs_i2c_init - Platform registration call
 * @pdev:	Handle to the platform device structure
 *
 * This function does all the memory allocation and registration for the i2c
 * device. User can modify the address mode to 10 bit address mode using the
 * ioctl call with option I2C_TENBIT.
 *
 * Return: 0 on success, negative error otherwise
 */
i2c_dev_t *itcs_i2c_init(i2c_chan index, i2c_mode mode, i2c_addr_mode addr_mode,
			 int devaddr, i2c_speed_mode speed)
{
	static struct cdns_i2c i2c_id[16] = {0};
	struct cdns_i2c *id;
	char i2c_name[8] = { 0 };
	int ret;

#if 0
	id = malloc(sizeof(*id));
	if (!id)
		return NULL;
#else
	id = &i2c_id[index];
	if (id->slave != NULL)
		return id;
#endif

	memset(id, 0, sizeof(struct cdns_i2c));

	id->slave = malloc(sizeof(struct cdns_i2c_client));
	if (!id->slave)
		return NULL;
	memset(id->slave, 0, sizeof(struct cdns_i2c_client));

	sprintf(i2c_name, "iic%d", index);
	if (index == 0 || index == 1) {
		itcs_module_enable(SAP, i2c_name);
		id->input_clk = itcs_module_get_clock(SAP, "apb");
		//itcs_module_set_clock(SAP, "apb", NULL, 12000000, false);
		//id->input_clk = 12000000;
		itcs_module_set_pads(SAP, FPGA_BIT_V_EMMC, i2c_name);
	} else if (index == 2 || index == 3 || index == 4 || index == 5 || index == 6 || index == 7) {
		itcs_module_enable(CPU, i2c_name);
		//itcs_module_set_clock(CPU, "apb", NULL, 12000000, false);
		//id->input_clk = 12000000;
		id->input_clk = itcs_module_get_clock(CPU, "apb");
		if (index == 3 && i2cx_multiplex_enable) {
			itcs_pads_set_mode(CPU, PADSRANGE(63, 64), PADS_MODE_FUNC, PADS_FUNC1);
			itcs_pads_set_pull(CPU, PADSRANGE(63, 64), 1, PADS_PULL_UP);
		}else if(index == 4 && i2cx_multiplex_enable){
			itcs_pads_set_mode(CPU, PADSRANGE(107, 108), PADS_MODE_FUNC, PADS_FUNC2);
			itcs_pads_set_pull(CPU, PADSRANGE(107, 108), 1, PADS_PULL_UP);
		}else if(index == 5 && i2cx_multiplex_enable){
			itcs_pads_set_mode(CPU, PADSRANGE(109, 110), PADS_MODE_FUNC, PADS_FUNC2);
			itcs_pads_set_pull(CPU, PADSRANGE(109, 110), 1, PADS_PULL_UP);
		}else {
			itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, i2c_name);
		}
	}

	if (addr_mode == ADDR_7BITS)
		id->addr_mode = ADDR_7BITS;
	else if (addr_mode == ADDR_10BITS)
		id->addr_mode = ADDR_10BITS;

	id->quirks = CDNS_I2C_BROKEN_HOLD_BIT;

	switch (index) {
	case 0:
		id->membase = (void *)ITCS_S_I2C0_BASE;
		id->irq = S_IIC0_IRQn;
		break;
	case 1:
		id->membase = (void *)ITCS_S_I2C1_BASE;
		id->irq = S_IIC1_IRQn;
		break;
	case 2:
		id->membase = (void *)ITCS_C_I2C2_BASE;
		id->irq = C_IIC2_IRQn;
		break;
	case 3:
		id->membase = (void *)ITCS_C_I2C3_BASE;
		id->irq = C_IIC3_IRQn;
		break;
	case 4:
		id->membase = (void *)ITCS_C_I2C4_BASE;
		id->irq = C_IIC4_IRQn;
		break;
	case 5:
		id->membase = (void *)ITCS_C_I2C5_BASE;
		id->irq = C_IIC5_IRQn;
		break;
	case 6:
		id->membase = (void *)ITCS_C_I2C6_BASE;
		id->irq = C_IIC6_IRQn;
		break;
	case 7:
		id->membase = (void *)ITCS_C_I2C7_BASE;
		id->irq = C_IIC7_IRQn;
		break;
	default:
		id->membase = NULL;
		id->irq = -1;
		printf("don't support i2c%d!\n", index);
		break;
	}
	if (IS_ERR(id->membase) || id->irq < 0)
		goto err;

	id->adap.timeout = CDNS_I2C_TIMEOUT;
	id->adap.algo_data = id;
	id->xfer_done = 0;
	snprintf(id->adap.name, sizeof(id->adap.name), "Cadence I2C at %08lx",
		 (unsigned long)id->membase);

	id->i2c_clk = speed;
#ifdef CONFIG_COMPILE_FPGA
	if (id->i2c_clk > I2C_MAX_FAST_MODE_PLUS_FREQ)
		id->i2c_clk = I2C_MAX_STANDARD_MODE_FREQ;
#endif

#if IS_ENABLED(CONFIG_I2C_SLAVE)
	/* Set initial mode to master */
	id->dev_mode = I2C_MASTER;
	id->slave_state = CDNS_I2C_SLAVE_STATE_IDLE;
#endif
	id->ctrl_reg = CDNS_I2C_CR_ACK_EN | CDNS_I2C_CR_NEA | CDNS_I2C_CR_MS;

	ret = cdns_i2c_setclk(id->input_clk, id);
	if (ret) {
		printf("invalid SCL clock: %u Hz\n", id->i2c_clk);
		ret = -EINVAL;
		goto err;
	}

	if (index == I2C_CHAN0)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic0", id);
	else if (index == I2C_CHAN1)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic1", id);
	else if (index == I2C_CHAN2)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic2", id);
	else if (index == I2C_CHAN3)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic3", id);
	else if (index == I2C_CHAN4)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic4", id);
	else if (index == I2C_CHAN5)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic5", id);
	else if (index == I2C_CHAN6)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic6", id);
	else if (index == I2C_CHAN7)
		ret = request_irq(id->irq, cdns_i2c_isr, "iic7", id);
	if (ret) {
		printf("cannot get irq %d\n", id->irq);
		goto err;
	}
	cdns_i2c_init(id);

	printf("%s: %u kHz mmio %08lx irq %d as %s\n", i2c_name,
	       id->i2c_clk / 1000, (unsigned long)id->membase, id->irq,
	       mode == I2C_MASTER ? "master" : "slave");
	//itcs_set_irq_priority(id->irq, IRQ_PRIORITY_0);
	if (mode == I2C_SLAVE) {
		id->slave->addr = devaddr;
		id->slave->adapter = &id->adap;
		ret = cdns_reg_slave(id->slave);
		//itcs_set_irq_priority(id->irq, IRQ_PRIORITY_1);
		if (ret < 0) {
			printf("%s cannot register as slave\n", i2c_name);
			goto err;
		}
	}

	return id;

err:
	free(id->slave);
	free(id);
	return NULL;
}

/**
 * itcs_i2c_deinit - Unregister the device after releasing the resources
 * @pdev:	Handle to the platform device structure
 *
 * This function frees all the resources allocated to the device.
 *
 * Return: 0 always
 */
void itcs_i2c_exit(i2c_dev_t *dev)
{
	if (dev->dev_mode == I2C_SLAVE)
		cdns_unreg_slave(dev->slave);

	if (dev) {
		if (dev->slave) {
			free(dev->slave);
			dev->slave = NULL;
		}
                free(dev);
		dev = NULL;
        }
}

int itcs_i2c_slv_mon_is_rdy(i2c_dev_t *dev)
{
	int ret = 0;
	unsigned int val;
	if (slv_rdy_flag) {
		slv_rdy_flag = 0;
		val = cdns_i2c_readreg(dev->membase, CDNS_I2C_CR_OFFSET);
		if (!(val & CDNS_I2C_CR_SLVMON))
			ret = 1;
	}
	return ret;
}

int itcs_i2c_slv_mon_config(i2c_dev_t *dev, int devaddr, int interval)
{
	unsigned int ctrl_reg;
	unsigned int isr_status;

	if (interval > SLV_MON_PAUSE_MAX) {
		printf("interval must less than %d\n", SLV_MON_PAUSE_MAX);
		return -1;
	}

	slv_rdy_flag = 0;

	/* Set the controller in Master transmit mode and clear the FIFO. */
	ctrl_reg = cdns_i2c_readreg(dev->membase, CDNS_I2C_CR_OFFSET);
	ctrl_reg &= ~CDNS_I2C_CR_RW;
	ctrl_reg |= CDNS_I2C_CR_CLR_FIFO;
	ctrl_reg |= CDNS_I2C_CR_SLVMON;
	cdns_i2c_writereg(dev->membase, CDNS_I2C_CR_OFFSET, ctrl_reg);

	/* Clear the interrupts in interrupt status register. */
	isr_status = cdns_i2c_readreg(dev->membase, CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(dev->membase, CDNS_I2C_ISR_OFFSET, isr_status);

	cdns_i2c_writereg(dev->membase, CDNS_I2C_SLV_MON_PAUSE_OFFSET, interval + 1);
	/* Set the slave address in address register - triggers operation. */
	cdns_i2c_writereg(dev->membase, CDNS_I2C_ADDR_OFFSET, devaddr & CDNS_I2C_ADDR_MASK);
	cdns_i2c_writereg(dev->membase, CDNS_I2C_IER_OFFSET, CDNS_I2C_IXR_SLV_RDY);
	return 0;
}

int itcs_i2c_is_completed(i2c_dev_t *dev)
{
	int count = 1;

	if (!dev)
		return -1;

	if (dev->dev_mode == I2C_SLAVE) {
		count = dev->slave->slv_send_buf != NULL ?
				      dev->slave->slv_send_count :
				      dev->slave->slv_recv_count;
	} else if (dev->dev_mode == I2C_MASTER) {
		count = dev->p_send_buf != NULL ? dev->send_count :
							dev->recv_count;
	}
	return count == 0 ? 1 : 0;
}

static int wait_for_blocking(i2c_dev_t *dev, bool blocked)
{
	int ret;
	while (blocked) {
		ret = itcs_i2c_is_completed(dev);
		if (ret < 0 || dev->err_status & CDNS_I2C_IXR_ARB_LOST ||
		    dev->err_status & CDNS_I2C_IXR_RX_UNF ||
		    dev->err_status & CDNS_I2C_IXR_TX_OVF ||
		    dev->err_status & CDNS_I2C_IXR_RX_OVF ||
		    dev->err_status & CDNS_I2C_IXR_NACK) {
			writel(CDNS_I2C_IXR_ALL_INTR_MASK,
			       dev->membase + CDNS_I2C_IDR_OFFSET);

			printf("i2c failed, ret = %d, errno = 0x%x\n", ret,dev->err_status);
			return -1;
		} else if (ret) {
			break;
		}
		udelay(1);
	}
	return 0;
}

int itcs_i2c_read(i2c_dev_t *dev, int devaddr, unsigned char *buf, int len, bool blocked)
{
	dev->inter_connect_msg.addr = devaddr;
	if (dev->addr_mode == ADDR_7BITS)
		dev->inter_connect_msg.flags = CDNS_I2C_READ;
	else if (dev->addr_mode == ADDR_10BITS)
		dev->inter_connect_msg.flags = CDNS_I2C_READ | CDNS_I2C_M_TEN;
	dev->inter_connect_msg.buf = buf;
	dev->inter_connect_msg.len = len;

	if (dev->dev_mode == I2C_SLAVE) {
		dev->slave->slv_recv_buf = dev->inter_connect_msg.buf;
		dev->slave->slv_recv_count = dev->inter_connect_msg.len;
	} else if (dev->dev_mode == I2C_MASTER) {
		cdns_i2c_master_xfer(&dev->adap, &dev->inter_connect_msg, 1);
	}
	return wait_for_blocking(dev, blocked);
}

int itcs_i2c_write(i2c_dev_t *dev, int devaddr, unsigned char *buf, int len, bool blocked)
{
	dev->inter_connect_msg.addr = devaddr;
	if (dev->addr_mode == ADDR_7BITS)
		dev->inter_connect_msg.flags = CDNS_I2C_WRITE;
	else if (dev->addr_mode == ADDR_10BITS)
		dev->inter_connect_msg.flags = CDNS_I2C_WRITE | CDNS_I2C_M_TEN;
	dev->inter_connect_msg.buf = buf;
	dev->inter_connect_msg.len = len;

	if (dev->dev_mode == I2C_SLAVE) {
		dev->slave->slv_send_buf = dev->inter_connect_msg.buf;
		dev->slave->slv_send_count = dev->inter_connect_msg.len;
		dev->slave->slv_curr_send_count = 0;
	} else if (dev->dev_mode == I2C_MASTER) {
		cdns_i2c_master_xfer(&dev->adap, &dev->inter_connect_msg, 1);
	}
	return wait_for_blocking(dev, blocked);
}

int itcs_i2c_transfer(i2c_dev_t *dev, i2c_msg_t *msg, int num)
{
	int ret = 0;
	if (dev->dev_mode == I2C_SLAVE) {
		printf("please use read and write api interface!\n");
		ret = -1;
	} else if (dev->dev_mode == I2C_MASTER) {
		cdns_i2c_master_xfer(&dev->adap, msg, num);
		ret = wait_for_blocking(dev, 1);
	}
	return ret;
}
