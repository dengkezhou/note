#ifndef __PL011_H__
#define __PL011_H__

#define UART_DEBUG
#ifdef UART_DEBUG
#define uart_dbg(fmt...) printf(fmt)
#else
#define uart_dbg(...)                                                          \
  do {                                                                         \
  } while (0)
#endif
#define uart_err(fmt...) printf(fmt)

#define DMA_BUFFER_SIZE     4096
#define POLL_UART_SIZE      (102400)
#define UART_DEFAUTL_FRAMES (102400)
#ifdef CONFIG_COMPILE_FPGA
#define IRQ_THRESHOLD 18
#else
#define IRQ_THRESHOLD 18
#endif

#define UART_DMATX_PERI_ID 18
#define UART_DMARX_PERI_ID 19

enum UART_TTY {
  PL011_UART0,
  PL011_UART1,
  PL011_UART2,
  PL011_UART3,
};

enum uart_block {
  NO_BLOCK,
  BLOCKED,
};

enum TTY_TYPE {
  TTY_READ,
  TTY_WRITE,
};

enum word_length {
  PL011_5BIT,
  PL011_6BIT,
  PL011_7BIT,
  PL011_8BIT,
};

enum parity_mode {
  PL011_PARITY_ODD,
  PL011_PARITY_EVEN,
  PL011_PARITY_NO,
};

enum fifo_level {
  FIFO_FULL_1_8,
  FIFO_FULL_1_4,
  FIFO_FULL_1_2,
  FIFO_FULL_3_4,
  FIFO_FULL_7_8,
};

struct uart_flowctrl {
  int cts_enable;
  int rts_enable;
};

struct uart_fifo {
  enum fifo_level recv;
  enum fifo_level trans;
};

struct uart_termios {
  enum word_length length;
  int fifo_enable;
  int stop_enable;
  enum parity_mode parity;
  int break_enable;
};

struct pkt_data {
  char *data;
  int pkt_len;
  int read;
};

typedef struct pkt_data *packet_t;

struct uart_dev {
  char name[16];
  int num;
  uint32_t reg_addr;
  packet_t tx_pkt;
  packet_t rx_pkt;

  /* for dma mode */
  int dma_enable;
  struct dma_chan *chantx;
  struct dma_chan *chanrx;
  char *tx_buf;
  char *rx_buf;
};

extern int tty_write(struct uart_dev *dev, uint8_t *buf, int len, int block);
extern int tty_read(struct uart_dev *dev, uint8_t *buf, int len, int block);
extern struct uart_dev *uart_init(int num);
extern void uart_exit(struct uart_dev *dev);
extern int uart_open(struct uart_dev *dev);
extern void uart_close(struct uart_dev *dev);
extern void uart_enable(struct uart_dev *dev, int flags);
extern void uart_ctrl_ctsrts(struct uart_dev *dev, int flags);
extern void uart_ctrl_loopback(struct uart_dev *dev, int flags);
extern void uart_dma_init(struct uart_dev *dev);
extern void uart_dma_exit(struct uart_dev *dev);
extern void uart_test_sir_loopback(struct uart_dev *dev, int flags);
extern void uart_irda_enable(struct uart_dev *dev, int flags);
extern void uart_set_clk(struct uart_dev *dev, int baudrate);
extern void uart_irda_lp_enable(struct uart_dev *dev, int flags);
extern void uart_lp_count(struct uart_dev *dev, int count);
extern void uart_wait_parapare(struct uart_dev *dev);
/* internal interface */
extern void uart_set_dma_mode(struct uart_dev *dev, int flags);
extern void uart_ctrl_enable(struct uart_dev *dev, int flags);
extern int uart_set_termios(struct uart_dev *dev, struct uart_termios *termios);
extern void uart_recv_ctrl_enable(struct uart_dev *dev, int flags);
extern void uart_trans_ctrl_enable(struct uart_dev *dev, int flags);
extern void uart_prepare(struct uart_dev *dev, int flags, uint8_t *buf,
                         int len);
extern int uart_callback(struct uart_dev *dev, int flags);
extern int uart_dma_rx_callback(void *data);
extern int uart_dma_tx_callback(void *data);
#endif
