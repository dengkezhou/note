#ifndef __IIC_H__
#define __IIC_H__

#define DEBUG_I2C 1

#define I2C_MAX_STANDARD_MODE_FREQ 100000
#define I2C_MAX_FAST_MODE_FREQ 400000
#define I2C_MAX_FAST_MODE_PLUS_FREQ 1000000

#define I2C_M_RD 0x0001 /* guaranteed to be 0x0001! */
#define I2C_M_TEN 0x0010 /* use only if I2C_FUNC_10BIT_ADDR */
#define I2C_M_DMA_SAFE 0x0200 /* use only in kernel space */
#define I2C_M_RECV_LEN 0x0400 /* use only if I2C_FUNC_SMBUS_READ_BLOCK_DATA */
#define I2C_M_NO_RD_ACK 0x0800 /* use only if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK 0x1000 /* use only if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR 0x2000 /* use only if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NOSTART 0x4000 /* use only if I2C_FUNC_NOSTART */
#define I2C_M_STOP 0x8000 /* use only if I2C_FUNC_PROTOCOL_MANGLING */

#define CDNS_I2C_WRITE 0
#define CDNS_I2C_READ I2C_M_RD
#define CDNS_I2C_M_TEN I2C_M_TEN

#define SLV_MON_PAUSE_MAX ((1 << 4) - 1 - 1)

typedef enum cdns_i2c_chan {
	I2C_CHAN0,
	I2C_CHAN1,
	I2C_CHAN2,
	I2C_CHAN3,
	I2C_CHAN4,
	I2C_CHAN5,
	I2C_CHAN6,
	I2C_CHAN7
} i2c_chan;

#define IS_ENABLED defined
#define CONFIG_I2C_SLAVE

#if IS_ENABLED(CONFIG_I2C_SLAVE)
/**
 * enum cdns_i2c_mode - I2C Controller current operating mode
 *
 * @I2C_SLAVE:       I2C controller operating in slave mode
 * @I2C_MASTER:      I2C Controller operating in master mode
 */
typedef enum cdns_i2c_mode { I2C_SLAVE, I2C_MASTER } i2c_mode;

/**
 * enum cdns_i2c_slave_state - Slave state when I2C is operating in slave mode
 *
 * @CDNS_I2C_SLAVE_STATE_IDLE: I2C slave idle
 * @CDNS_I2C_SLAVE_STATE_SEND: I2C slave sending data to master
 * @CDNS_I2C_SLAVE_STATE_RECV: I2C slave receiving data from master
 */
enum cdns_i2c_slave_state {
	CDNS_I2C_SLAVE_STATE_IDLE,
	CDNS_I2C_SLAVE_STATE_SEND,
	CDNS_I2C_SLAVE_STATE_RECV,
};
#endif

typedef enum cdns_i2c_speed_mode {
	NORMAL = I2C_MAX_STANDARD_MODE_FREQ,
	FAST = I2C_MAX_FAST_MODE_FREQ,
	FAST_PLUS = I2C_MAX_FAST_MODE_PLUS_FREQ,
	I2C_RTL_SPEED = 4000000
} i2c_speed_mode;

typedef enum cdns_i2c_addr_mode { ADDR_7BITS, ADDR_10BITS } i2c_addr_mode;

struct cdns_i2c_adapter {
	char name[64];
	int timeout;
	void *algo_data;
};

typedef struct cdns_i2c_msg {
	__u16 addr;
	__u16 flags;
	__u32 len;
	__u8 *buf;
} i2c_msg_t;

struct cdns_i2c_client {
	unsigned short flags; /* div., see below              */
#define I2C_CLIENT_PEC 0x04 /* Use Packet Error Checking */
#define I2C_CLIENT_TEN 0x10 /* we have a ten bit chip address */
	/* Must equal I2C_M_TEN below */
#define I2C_CLIENT_SLAVE 0x20 /* we are the slave */
#define I2C_CLIENT_HOST_NOTIFY 0x40 /* We want to use I2C host notify */
#define I2C_CLIENT_WAKE 0x80 /* for board_info; true iff can wake */
#define I2C_CLIENT_SCCB 0x9000 /* Use Omnivision SCCB protocol */
	/* Must match I2C_M_STOP|IGNORE_NAK */
	unsigned short addr;
	struct cdns_i2c_adapter *adapter;
	unsigned char *slv_recv_buf;
	unsigned char *slv_send_buf;
	unsigned int slv_send_count;
	unsigned int slv_curr_send_count;
	unsigned int slv_recv_count;
};

/**
 * struct cdns_i2c - I2C device private data structure
 *
 * @membase:		Base address of the I2C device
 * @adap:		I2C adapter instance
 * @p_msg:		Message pointer
 * @err_status:		Error status in Interrupt Status Register
 * @xfer_done:		Transfer complete status
 * @p_send_buf:		Pointer to transmit buffer
 * @p_recv_buf:		Pointer to receive buffer
 * @send_count:		Number of bytes still expected to send
 * @recv_count:		Number of bytes still expected to receive
 * @curr_recv_count:	Number of bytes to be received in current transfer
 * @irq:		IRQ number
 * @input_clk:		Input clock to I2C controller
 * @i2c_clk:		Maximum I2C clock speed
 * @bus_hold_flag:	Flag used in repeated start for clearing HOLD bit
 * @clk:		Pointer to struct clk
 * @quirks:		flag for broken hold bit usage in r1p10
 * @ctrl_reg:		Cached value of the control register.
 * @ctrl_reg_diva_divb: value of fields DIV_A and DIV_B from CR register
 * @slave:		Registered slave instance.
 * @dev_mode:		I2C operating role(master/slave).
 * @slave_state:	I2C Slave state(idle/read/write).
 */
typedef struct cdns_i2c {
	void *membase;
	struct cdns_i2c_adapter adap;
	struct cdns_i2c_msg *p_msg;
	int err_status;
	unsigned int xfer_done;
	unsigned char *p_send_buf;
	unsigned char *p_recv_buf;
	unsigned int send_count;
	unsigned int recv_count;
	unsigned int curr_recv_count;
	unsigned int left_in_fifo;
	unsigned int readed_cnt;
	i2c_msg_t inter_connect_msg;
	i2c_addr_mode addr_mode;
	int irq;
	unsigned long input_clk;
	unsigned int i2c_clk;
	unsigned int bus_hold_flag;
	u32 quirks;
	u32 ctrl_reg;
#if IS_ENABLED(CONFIG_I2C_SLAVE)
	u16 ctrl_reg_diva_divb;
	struct cdns_i2c_client *slave;
	enum cdns_i2c_mode dev_mode;
	enum cdns_i2c_slave_state slave_state;
#endif
} i2c_dev_t;

i2c_dev_t *itcs_i2c_init(i2c_chan index, i2c_mode mode, i2c_addr_mode addr_mode, int devaddr, i2c_speed_mode speed);
int itcs_i2c_transfer(i2c_dev_t *dev, i2c_msg_t *msg, int num);
int itcs_i2c_write(i2c_dev_t *dev, int devaddr, unsigned char *buf, int len, bool blocked);
int itcs_i2c_read(i2c_dev_t *dev, int devaddr, unsigned char *buf, int len, bool blocked);
int itcs_i2c_is_completed(i2c_dev_t *dev);
int itcs_i2c_slv_mon_is_rdy(i2c_dev_t *dev);
int itcs_i2c_slv_mon_config(i2c_dev_t *dev, int devaddr, int interval);
void itcs_i2c_exit(i2c_dev_t *dev);

#endif
