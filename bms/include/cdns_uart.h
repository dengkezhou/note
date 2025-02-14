#ifndef __CDNS_UART_H__
#define __CDNS_UART_H__

#include <stdint.h>
#include <irq.h>
#include <uart.h>

#define CDNS_UART0_BASE ITCS_S_UART0_BASE
#define CDNS_UART1_BASE ITCS_S_UART1_BASE
#define CDNS_UART2_BASE ITCS_C_UART2_BASE
#define CDNS_UART3_BASE ITCS_C_UART3_BASE
#define CDNS_UART4_BASE ITCS_C_UART4_BASE
#define CDNS_UART5_BASE ITCS_C_UART5_BASE
#define CDNS_UART6_BASE ITCS_C_UART6_BASE
#define CDNS_UART7_BASE ITCS_C_UART7_BASE
#define CDNS_UART8_BASE ITCS_C_UART8_BASE
#define CDNS_UART9_BASE ITCS_C_UART9_BASE
#define CDNS_UART10_BASE ITCS_C_UART10_BASE
#define CDNS_UART11_BASE ITCS_C_UART11_BASE

#define REG_CTRL_OFFSET  (0x00000000UL) // control register
#define REG_MODE_OFFSET  (0x00000004UL) // mode register
#define REG_IER_OFFSET   (0x00000008UL) // interrupt enable register(WO).
#define REG_IDR_OFFSET   (0x0000000CUL) // interrupt disable register(WO).
#define REG_IMR_OFFSET   (0x00000010UL) // interrupt mask register(RO).
#define REG_CISR_OFFSET  (0x00000014UL) // channel interrupt status register
#define REG_BRGR_OFFSET  (0x00000018UL) // baud rate generator register
#define REG_RTOR_OFFSET  (0x0000001CUL) // receiver timeout register
#define REG_RTR_OFFSET   (0x00000020UL) // receiver FIFO trigger level register
#define REG_MCR_OFFSET   (0x00000024UL) // modem control register
#define REG_MSR_OFFSET   (0x00000028UL) // modem status register
#define REG_CSR_OFFSET   (0x0000002CUL) // channel status register
#define REG_FIFO_OFFSET  (0x00000030UL) // receive or transmit FIFO
#define REG_BDIVR_OFFSET (0x00000034UL) // baud rate driver register
#define REG_FCDR_OFFSET  (0x00000038UL) // flow control delay register
#define REG_RPWR_OFFSET  (0x0000003CUL) // IR minimum received pulse width
#define REG_TPWR_OFFSET  (0x00000040UL) // IR transmit pulse register
#define REG_TTR_OFFSET   (0x00000044UL) // transmitter FIFO trigger level register
#define REG_RBSR_OFFSET  (0x00000048UL) // rx FIFO byte status register

#define IxR_RTRIG_MASK   ((uint16_t)0x0001) /* bit[0]: rx FIFO trigger.     */
#define IxR_REMPTY_MASK  ((uint16_t)0x0002) /* bit[1]: rx FIFO empty.       */
#define IxR_RFUL_MASK    ((uint16_t)0x0004) /* bit[2]: rx FIFO full.        */
#define IxR_TEMPTY_MASK  ((uint16_t)0x0008) /* bit[3]: tx FIFO empty.       */
#define IxR_TFUL_MASK    ((uint16_t)0x0010) /* bit[4]: tx FIFO full.        */
#define IxR_ROVR_MASK    ((uint16_t)0x0020) /* bit[5]: rx overflow error    */
#define IxR_FRAME_MASK   ((uint16_t)0x0040) /* bit[6]: rx framing error.    */
#define IxR_PARE_MASK    ((uint16_t)0x0080) /* bit[7]: rx parity error.     */
#define IxR_TIMEOUT_MASK ((uint16_t)0x0100) /* bit[8]: rx timeout error     */
#define IxR_DMSI_MASK    ((uint16_t)0x0200) /* bit[9]: delta modem status   */
#define IxR_TTRIG_MASK   ((uint16_t)0x0400) /* bit[10]: tx FIFO trigger     */
#define IxR_TNFUL_MASK   ((uint16_t)0x0800) /* bit[11]: tx FIFO nearly full */
#define IxR_TOVR_MASK    ((uint16_t)0x1000) /* bit[12]: tx FIFO overflow    */
#define IxR_RBRK_MASK    ((uint16_t)0x2000) /* bit[13]: rx break detect.    */

/* bit[0]: reset receiver,auto clear.| @value 1:enable */
#define CTRL_RXRES_MASK ((uint16_t)0x0001)
/* bit[1]: reset transmitter,auto clear.| @value 1:enable */
#define CTRL_TXRES_MASK ((uint16_t)0x0002)
/* bit[2]: receive enable.  | @value 1:enable*/
#define CTRL_RXEN_MASK ((uint16_t)0x0004)
/* bit[3]: receive disable. | @value 1:enable*/
#define CTRL_RXDIS_MASK ((uint16_t)0x0008)
/* bit[4]: transmit enable. | @value 1:enable*/
#define CTRL_TXEN_MASK ((uint16_t)0x0010)
/* bit[5]: transmit disable.| @value 1:enable*/
#define CTRL_TXDIS_MASK ((uint16_t)0x0020)
/* bit[6]: restart receiver timeout counter,auto clear. @value 1:enable*/
#define CTRL_RSTTO_MASK ((uint16_t)0x0040)
/* bit[7]: start transmitter break. | @value 1:enable*/
#define CTRL_STTBRK_MASK ((uint16_t)0x0040)
/* bit[8]: stop  transmitter break. | @value 1:enable*/
#define CTRL_STPBRK_MASK ((uint16_t)0x0040)

/* bit[0]: clock source select.
  @value 0: uart_clock
  @value 1: uart_clock/8
*/
#define MODE_CLKS_MASK ((uint16_t)0x0001)
/* bit[2:1]: character length select.
  @value 11: 6 bits
  @value 10: 7 bits
  @value 0x: 8 bits
*/
#define MODE_CHRL_MASK ((uint16_t)0x0006)
/* bit[5:3]: parity type select.
  @value 000: even parity
  @value 001: odd parity
  @value 010: forced to 0 parity
  @value 011: forced to 1 parity
  @value 1xx: no parity
*/
#define MODE_PAR_MASK ((uint16_t)0x0038)
/* bit[7:6]: number of stop bits.
  @value 00: 1 stop bit
  @value 01: 1.5 stop bits
  @value 10: 2 stop bits
  @value 11: reserved value
*/
#define MODE_NBSTOP_MASK ((uint16_t)0x00C0)
/* bit[9:8]: channel mode.
  @value 00: normal mode
  @value 01: automatic echo mode
  @value 10: local loopback mode
  @value 11: remote loopback mode
*/
#define MODE_CHMODE_MASK ((uint16_t)0x0300)
/* bit[10]: external uart clock source select.
  @value 0: APB clock
  @value 1: a user-defined clock
*/
#define MODE_UCLKEN_MASK ((uint16_t)0x0400)
/* bit[11]: enable IrDA mode.
  @value 1:IrDA mode
  @value 0:UART mode
*/
#define MODE_IRMODE_MASK ((uint16_t)0x0800)
/* bit[13:12]: FIFO access size.
  @value 00: 1/2 bytes access according to bytesel 1/0
  @value 01: 1 byte access
  @value 10: 2 bytes access
  @value 11: 4 bytes access
*/
#define MODE_WSIZE_MASK ((uint16_t)0x3000)

/* bit[15:0]: baud rate clock divisor.
  @value 0: disables baud_sample
  @value 1: clock divisor bypass(baud_sample = sel_clk)
  @value 2-65535: clock divisor(baud_sample = sel_clk/CD)
*/
#define BRGR_CD_MASK ((uint16_t)0xffff)
/* bit[15:0]: receiver timeout value.
  @value 0: disables receiver timeout counter
  @value 1-255:receiver timeout in number of baud_tx_rate periods = 4*RTO
*/
#define RTOR_RTO_MASK ((uint16_t)0xffff)
/* bit[5]: flow control mode.
  @value 0: disable automatic flow control mode
  @value 1: enable automatic flow control mode
*/
#define MCR_FCM_MASK ((uint16_t)0x0020)
#define MCR_RTS_MASK ((uint16_t)0x0002) /* bit[1]: request to send */
#define MCR_DTR_MASK ((uint16_t)0x0001) /* bit[0]: data terminal ready */

#define IRDA_BOF 0xc0
#define IRDA_EOF 0xc1

/* UART_InitStruct parameter value range */
#define CDNS_UART_WordLength_6b            ((uint16_t)0x0006)
#define CDNS_UART_WordLength_7b            ((uint16_t)0x0004)
#define CDNS_UART_WordLength_8b            ((uint16_t)0x0000)
#define CDNS_UART_StopBits_1               ((uint16_t)0x0000)
#define CDNS_UART_StopBits_1_5             ((uint16_t)0x0040)
#define CDNS_UART_StopBits_2               ((uint16_t)0x0080)
#define CDNS_UART_Parity_No                ((uint16_t)0x0020)
#define CDNS_UART_Parity_Even              ((uint16_t)0x0000)
#define CDNS_UART_Parity_Odd               ((uint16_t)0x0008)
#define CDNS_UART_Parity_Space             ((uint16_t)0x0010)
#define CDNS_UART_Parity_Mark              ((uint16_t)0x0018)
#define CDNS_UART_Mode_UART                ((uint16_t)0x0000)
#define CDNS_UART_Mode_IrDA                ((uint16_t)0x0800)
#define CDNS_UART_WSIZE_1                  ((uint16_t)0x1000)
#define CDNS_UART_WSIZE_2                  ((uint16_t)0x2000)
#define CDNS_UART_WSIZE_4                  ((uint16_t)0x3000)
#define CDNS_UART_WSIZE_BY_BYTESEL         ((uint16_t)0x0000)
#define CDNS_UART_ChannelMode_Normal       ((uint16_t)0x0000)
#define CDNS_UART_ChannelMode_AutoEcho     ((uint16_t)0x0100)
#define CDNS_UART_ChannelMode_LocalLoop    ((uint16_t)0x0200)
#define CDNS_UART_ChannelMode_RemoteLoop   ((uint16_t)0x0300)
#define CDNS_UART_HardwareFlowControl_None ((uint16_t)0x0000)
#define CDNS_UART_HardwareFlowControl_Auto ((uint16_t)0x0020)

#define IS_CDNS_UART_WORD_LENGTH(LENGTH)                                       \
  (((LENGTH) == CDNS_UART_WordLength_6b) ||                                    \
   ((LENGTH) == CDNS_UART_WordLength_7b) ||                                    \
   ((LENGTH) == CDNS_UART_WordLength_8b))

#define IS_CDNS_UART_STOPBITS(STOPBITS)                                        \
  (((STOPBITS) == CDNS_UART_StopBits_1) ||                                     \
   ((STOPBITS) == CDNS_UART_StopBits_1_5) ||                                   \
   ((STOPBITS) == CDNS_UART_StopBits_2))

#define IS_CDNS_UART_PARITY(PARITY)                                            \
  (((PARITY) == CDNS_UART_Parity_No) || ((PARITY) == CDNS_UART_Parity_Even) || \
   ((PARITY) == CDNS_UART_Parity_Odd) ||                                       \
   ((PARITY) == CDNS_UART_Parity_Space) ||                                     \
   ((PARITY) == CDNS_UART_Parity_Mark))

#define CDNS_UART_Mode_UART ((uint16_t)0x0000)
#define CDNS_UART_Mode_IrDA ((uint16_t)0x0800)

#define IS_CDNS_UART_MODE(MODE)                                                \
  (((MODE) == CDNS_UART_Mode_UART) || ((MODE) == CDNS_UART_Mode_IrDA))

#define IS_CDNS_UART_WSIZE(WSIZE)                                              \
  (((WSIZE) == CDNS_UART_WSIZE_1) || ((WSIZE) == CDNS_UART_WSIZE_2) ||         \
   ((WSIZE) == CDNS_UART_WSIZE_4) || ((WSIZE) == CDNS_UART_WSIZE_BY_BYTESEL))

#define IS_CDNS_UART_ChannelMode(ChannelMode)                                  \
  (((ChannelMode) == CDNS_UART_ChannelMode_Normal) ||                          \
   ((ChannelMode) == CDNS_UART_ChannelMode_AutoEcho) ||                        \
   ((ChannelMode) == CDNS_UART_ChannelMode_LocalLoop) ||                       \
   ((ChannelMode) == CDNS_UART_ChannelMode_RemoteLoop))

#define IS_CDNS_UART_HARDWARE_FLOW_CONTROL(CONTROL)                            \
  (((CONTROL) == CDNS_UART_HardwareFlowControl_None) ||                        \
   ((CONTROL) == CDNS_UART_HardwareFlowControl_Auto))

#define IS_CDNS_UART_DATA_WSIZE_32(DATA) ((DATA) <= 0xFFFFFFFF)
#define IS_CDNS_UART_DATA_WSIZE_16(DATA) ((DATA) <= 0xFFFF)
#define IS_CDNS_UART_DATA_WSIZE_08(DATA) ((DATA) <= 0xFF)

// this value must be recalculate
#define CDNS_MAX_BAUDRATE 4000000
#define IS_CDNS_UART_BAUDRATE(BAUDRATE)                                        \
  (((BAUDRATE) > 0) && ((BAUDRATE) < CDNS_MAX_BAUDRATE))
#define BAUD_BDIVR_BDIV_DEFAULT (0x0F)
#define BAUD_BRGR_CD_MAX        (0XFFFF)

#if CONFIG_COMPILE_RTL

#define CDNS_DEFAULT_INIT_PARAM                                                \
  {                                                                            \
        CDNS_UART, UART1, (uint32_t)3000000, CDNS_UART_WordLength_8b,          \
        CDNS_UART_Parity_No, CDNS_UART_StopBits_1,                             \
        CDNS_UART_HardwareFlowControl_None, CDNS_UART_Mode_UART, 0,            \
        CDNS_UART_ChannelMode_Normal, CDNS_UART_WSIZE_1, NULL                  \
  }

#else

#define CDNS_DEFAULT_INIT_PARAM                                                \
  {                                                                            \
        CDNS_UART, UART1, (uint32_t)921600, CDNS_UART_WordLength_8b,           \
        CDNS_UART_Parity_No, CDNS_UART_StopBits_1,                             \
        CDNS_UART_HardwareFlowControl_None, CDNS_UART_Mode_UART, 0,            \
        CDNS_UART_ChannelMode_Normal, CDNS_UART_WSIZE_1, NULL                  \
  }

#endif
UART_HandleTypeDef *cdns_uart_init(UART_InitTypeDef *init);
void cdns_uart_deinit(UART_HandleTypeDef *uartHandler);
int cdns_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data,
                       uint32_t size, BlockStatus isBlock);
int cdns_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data,
                      uint32_t size, BlockStatus isBlock);
int cdns_uart_is_completed(UART_HandleTypeDef *uartHandler, int tx_rx);

#endif /*__CDNS_UART_H__*/
