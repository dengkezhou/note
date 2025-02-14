#ifndef __DWC_UART_H__
#define __DWC_UART_H__

#include <stdint.h>
#include <uart.h>

#define DWC_UART0_BASE ITCS_DUART0_BASE
#define DWC_UART1_BASE ITCS_DUART1_BASE
#define DWC_UART2_BASE ITCS_DUART2_BASE
#define DWC_UART3_BASE ITCS_DUART3_BASE

/* <! UART Register Offset */
#define DWC_REG_RBR_OFFSET (0x00000000UL) // Receive Buffer Register
#define DWC_REG_THR_OFFSET (0x00000000UL) // Transmit Holding Register
#define DWC_REG_DLL_OFFSET (0x00000000UL) // Divisor Latch Low
#define DWC_REG_DLH_OFFSET (0x00000004UL) // Divisor Latch High
#define DWC_REG_IER_OFFSET (0x00000004UL) // Interrupt Enable Register
#define DWC_REG_FCR_OFFSET (0x00000008UL) // FIFO  Control Register
#define DWC_REG_IIR_OFFSET (0x00000008UL) // Interrupt Identification Register
#define DWC_REG_LCR_OFFSET (0x0000000CUL) // Line  Control Register
#define DWC_REG_MCR_OFFSET (0x00000010UL) // Modem Control Register
#define DWC_REG_LSR_OFFSET (0x00000014UL) // Line Status Register
#define DWC_REG_MSR_OFFSET (0x00000018UL) // Modem Status Register
#define DWC_REG_SCR_OFFSET (0x0000001CUL) // Scratchpad Register
#define DWC_REG_FAR_OFFSET (0x00000070UL) // FIFO Access Register
#define DWC_REG_TFR_OFFSET (0x00000074UL) // Transmit FIFO Read
#define DWC_REG_RFW_OFFSET (0x00000078UL) // Receive FIFO Write
#define DWC_REG_USR_OFFSET (0x0000007CUL) // UART Status register
#define DWC_REG_TFL_OFFSET (0x00000080UL) // Transmit FIFO Level
#define DWC_REG_RFL_OFFSET (0x00000084UL) // Receive FIFO Level
/* UART Register Offset !> */

/* <! REGISTER BITS MASK FOR ACCORDING FUNCTIONS */
#define DWC_MASK_IER_ERBFI (0x00000001UL) // Received Data Available Interrupt.
#define DWC_MASK_IER_ETBEI (0x00000002UL) // Transmit Holding Register Empty
                                          // Int.
#define DWC_MASK_IER_ELSI   (0x00000004UL) // Receiver Line Status Interrupt
#define DWC_MASK_IER_EDSSI  (0x00000008UL) // Enable Modem Status Interrupt
#define DWC_MASK_IER_ELCOLR (0x00000010UL) //
#define DWC_MASK_IER_PTIME  (0x00000080UL) // Programmable THRE Interrupt Mode

#define DWC_MASK_IIR_IID    (0x0000000FUL) // Interrupt ID
#define DWC_MASK_IIR_FIFOSE (0x000000C0UL) // FIFOs Enabled

#define DWC_MASK_LSR_DR   (0x00000001UL) // Data Ready, receice fifo byte num != 0
#define DWC_MASK_LSR_OE   (0x00000002UL) // Overrun Error Bit,read clear
#define DWC_MASK_LSR_PE   (0x00000004UL) // Parity Error Bit,read clear
#define DWC_MASK_LSR_FE   (0x00000008UL) // Framing Error Bit,read clear
#define DWC_MASK_LSR_BI   (0x00000010UL) // Break Interrupt Bit,read clear
#define DWC_MASK_LSR_THRE (0x00000020UL) // Transmit Holding Register Empty bit
#define DWC_MASK_LSR_TEMT (0x00000040UL) // Transmitter Empty bit
#define DWC_MASK_LSR_RFE  (0x00000080UL) // Receiver FIFO Error bit

#define DWC_MASK_LCR_DLS  (0x00000003UL) // Data Length Select
#define DWC_MASK_LCR_STOP (0x00000004UL) // Stop Bits
#define DWC_MASK_LCR_PEN  (0x00000008UL) // Parity Enable
#define DWC_MASK_LCR_EPS  (0x00000010UL) // Even Parity Select
#define DWC_MASK_LCR_SP   (0x00000020UL) // Stick Parity
#define DWC_MASK_LCR_BC   (0x00000040UL) // Break Control Bit
#define DWC_MASK_LCR_DLAB (0x00000080UL) // Divisor Latch Access Bit

#define DWC_MASK_MCR_AFCE (0x00000020UL) // Auto Flow Control Enable
#define DWC_MASK_MCR_SIRE (0x00000040UL) // Sir Mode Enable
/* REGISTER BITS MASK FOR ACCORDING FUNCTIONS !>*/

/* <! UART_InitStruct parameter value range */
#define DWC_UART_WordLength_5b ((uint16_t)0x0000)
#define DWC_UART_WordLength_6b ((uint16_t)0x0001)
#define DWC_UART_WordLength_7b ((uint16_t)0x0002)
#define DWC_UART_WordLength_8b ((uint16_t)0x0003)

#define DWC_UART_StopBits_1   ((uint16_t)0x0000)
#define DWC_UART_StopBits_1_5 ((uint16_t)0x0004)
#define DWC_UART_StopBits_2   ((uint16_t)0x0004)

#define DWC_UART_Parity_No    ((uint16_t)0x0000)
#define DWC_UART_Parity_Odd   ((uint16_t)0x0008)
#define DWC_UART_Parity_Even  ((uint16_t)0x0018)
#define DWC_UART_Parity_Space ((uint16_t)0x0038)
#define DWC_UART_Parity_Mark  ((uint16_t)0x0028)

#define DWC_UART_Mode_UART ((uint16_t)0x0000)
#define DWC_UART_Mode_IrDA ((uint16_t)0x0040)

#define DWC_UART_HardwareFlowControl_None ((uint16_t)0x0000)
#define DWC_UART_HardwareFlowControl_Auto ((uint16_t)0x0020)
/* UART_InitStruct parameter value range !> */

#define IS_DWC_UART_WORD_LENGTH(LENGTH)                                        \
  (((LENGTH) == DWC_UART_WordLength_5b) ||                                     \
   ((LENGTH) == DWC_UART_WordLength_6b) ||                                     \
   ((LENGTH) == DWC_UART_WordLength_7b) ||                                     \
   ((LENGTH) == DWC_UART_WordLength_8b))

#define IS_DWC_UART_STOPBITS(STOPBITS)                                         \
  (((STOPBITS) == DWC_UART_StopBits_1) ||                                      \
   ((STOPBITS) == DWC_UART_StopBits_1_5) ||                                    \
   ((STOPBITS) == DWC_UART_StopBits_2))

#define IS_DWC_UART_PARITY(PARITY)                                             \
  (((PARITY) == DWC_UART_Parity_No) || ((PARITY) == DWC_UART_Parity_Even) ||   \
   ((PARITY) == DWC_UART_Parity_Odd) || ((PARITY) == DWC_UART_Parity_Space) || \
   ((PARITY) == DWC_UART_Parity_Mark))

#define IS_DWC_UART_MODE(MODE)                                                 \
  (((MODE) == DWC_UART_Mode_UART) || ((MODE) == DWC_UART_Mode_IrDA))

#define IS_DWC_UART_HARDWARE_FLOW_CONTROL(CONTROL)                             \
  (((CONTROL) == DWC_UART_HardwareFlowControl_None) ||                         \
   ((CONTROL) == DWC_UART_HardwareFlowControl_Auto))

#define DWC_MAX_BAUDRATE 0x00100000
#define IS_DWC_UART_BAUDRATE(BAUDRATE)                                         \
  (((BAUDRATE) > 0) && ((BAUDRATE) < DWC_MAX_BAUDRATE))

#define DWC_USED_DMA     1
#define DWC_NOT_USED_DMA 0

#define DWC_DEFAULT_INIT_PARAM                                                 \
  {                                                                            \
    DWC_UART, UART0, (uint16_t)115200, DWC_UART_WordLength_8b,                 \
        DWC_UART_Parity_No, DWC_UART_StopBits_1,                               \
        DWC_UART_HardwareFlowControl_None, DWC_UART_Mode_UART, 0, 0, 0         \
  }

typedef enum {
  MODEM_STATUS = 0x0,
  NO_INTERRUPT_PENDING,
  THR_EMPTY,
  RECEIVED_DATA_AVALIABLE = 0x4,
  RECEIVER_LINE_STATUS    = 0x6,
  BUSY_DETECT,
  CHARACTER_TIMEOUT = 0x0c
} InterruptID;

UART_HandleTypeDef *dwc_uart_init(UART_InitTypeDef *init);
void dwc_uart_deinit(UART_HandleTypeDef *uartHandler);
int dwc_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data,
                      uint32_t size, BlockStatus isBlock);
int dwc_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data,
                     uint32_t size, BlockStatus isBlock);
int dwc_uart_is_completed(UART_HandleTypeDef *uartHandler, int tx_rx);

#endif /*__DWC_UART_H__*/
