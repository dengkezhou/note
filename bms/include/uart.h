#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include <irq.h>
#include <dma-ops.h>
//#define DEBUG_UART
#ifdef DEBUG_UART
#define DEBUG_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) 
#endif

typedef enum { UART0 = 0, UART1 = 1, UART2 = 2, UART3 = 3, UART4, UART5, UART6, UART7, UART8, UART9, UART10, UART11} UART;

#define IS_UART_HANDLER(HANDLER) ((HANDLER == NULL) ? 0 : 1)
#define IS_UART_ALL_PERIPH(PERIPH)                                             \
  (((PERIPH) == UART0) || ((PERIPH) == UART1) || ((PERIPH) == UART2) ||        \
   ((PERIPH) == UART3) || ((PERIPH) == UART4) || ((PERIPH) == UART5) ||        \
   ((PERIPH) == UART6) || ((PERIPH) == UART7) || ((PERIPH) == UART8) ||        \
   ((PERIPH) == UART9) || ((PERIPH) == UART10) || ((PERIPH) == UART11))

#define check_param(expr)                                                      \
  do{                                                                          \
    if( (expr) ? 0 : 1){                                                       \
        panic("uart check param failed!\n");                                   \
    }                                                                          \
  }while(0)

typedef enum { NONBLOCK = 0, BLOCK = 1 } BlockStatus;
typedef enum { RESET = 0, SET = 1 } BitStatus;

typedef enum { CDNS_UART = 0, DWC_UART = 1 } UART_TYPE;

struct uart_dma_st{
    #define UART_DMA_RX 0
    #define UART_DMA_TX 1
    struct dma_chan *chan[2];
	struct dma_prep_info prep_info[2];
	struct dma_slave_config cfg[2];
	struct dma_info info[2];
	dma_cookie_t cookie[2];
};

typedef struct {
  /*Specifies which uart type is used,CDNS or DWC*/
  UART_TYPE type;
  /*Specifies which uart is used*/
  UART UARTx;
  /*This member configures the UART communication baud rate.*/
  uint32_t UART_BaudRate;
  /*Specifies the number of data bits transmitted or received in a frame. */
  uint16_t UART_WordLength;
  /*Specifies the parity mode.*/
  uint16_t UART_Parity;
  /*Specifies the number of stop bits transmitted.*/
  uint16_t UART_StopBits;
  /*Specifies wether the hardware flow control mode is enabled or disabled.*/
  uint16_t UART_HardwareFlowControl;
  /*Specifies wether the UART mode or IrDA mode.*/
  uint16_t UART_Mode;

  /*Specifies wether the dma is used,only DWC uart type.*/
  uint8_t use_dma;
  /*Specifies wether the UART mode in normal/auto echo/local loopback, */
  uint16_t UART_ChannelMode;
  /*Specifies the access size.*/
  uint16_t UART_WSIZE;
  /*Specify ports to use uart func, is don`t have, use default in pads.c*/
  struct pads_modules_bundle* pads;
} UART_InitTypeDef;

typedef enum {
  UART_RCV_OK = 0,  /* uart receive ok            */
  UART_RCV_NONE,    /* uart receive none          */
  UART_RCV_ERR,     /* uart receive error         */
  UART_RESET,       /* uart isn't initialized     */
  UART_READY,       /* uart is ready              */
  UART_BUSY,        /* uart is busy with sth      */
  UART_BUSY_TX,     /* uart is busy with transmit */
  UART_BUSY_RX,     /* uart is busy with receive  */
  UART_TIMEOUT,     /* uart timeout               */
  UART_TX_COMPLETE, /* uart transmit complete.    */
  UART_RX_COMPLETE, /* uart receive  complete.    */
  UART_ERROR        /* uart error                 */
} UART_StatusTypeDef;

typedef enum {
  UART_ERROR_NONE = 0,
  UART_ERROR_BUSY,
  UART_ERROR_PE,           /* uart parity error              */
  UART_ERROR_FE,           /* uart framing error             */
  UART_ERROR_ROVRE,        /* uart receive overflow error    */
  UART_ERROR_BUF_TOO_SMALL /* uart receive buffer too small  */
} UART_ErrorTypeDef;

typedef struct UART_handle {
  /*common data structure*/
  UART_InitTypeDef UART_InitStruct; /* uart init structure            */
  uintptr_t uart_base_addr;         /* uart base address              */
  UART_ErrorTypeDef errorCode;      /* uart error code                */
  struct uart_dma_st dma;           /* uart dma struct                */

  /*only rx use*/
  uint8_t *rxBufPtr;           /* point to uart rx Buffer             */
  uint32_t rxBufSize;          /* uart receive buffer size            */
  uint32_t rxCount;            /* uart received bytes Counter         */
  uint32_t rxTriggerCount;     /* uart rx trigger Counter             */
  uint64_t rxTotal;            /* uart received total number          */
  BlockStatus isRxBlock;       /* uart block Receive                  */
  volatile UART_StatusTypeDef rxStatus; /* uart can receive only               */

  /*only tx use*/
  uint8_t *txBufPtr;           /* point to uart tx Buffer             */
  uint32_t txBufSize;          /* uart transfer buffer size           */
  uint32_t txCount;            /* uart transfered bytes counter       */
  uint32_t txTriggerCount;     /* uart tx trigger Counter             */
  uint64_t txTotal;            /* uart transfer total number          */
  BlockStatus isTxBlock;       /* uart block transmit                 */
  volatile UART_StatusTypeDef txStatus; /* uart can transmit only              */

  /*callback functions*/
  /* uart rx complete callback  */
  void (*rCCallback)(struct UART_handle *uartHandler);
  /* uart tx complete callback  */
  void (*tCCallback)(struct UART_handle *uartHandler);
  /* uart error callback        */
  void (*errCallback)(struct UART_handle *uartHandler);
} UART_HandleTypeDef;

UART_HandleTypeDef *itcs_uart_init(UART_InitTypeDef *init);
void itcs_uart_deinit(UART_HandleTypeDef *uartHandler);
int itcs_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data,
                       uint32_t size, BlockStatus isBlock);
int itcs_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data,
                      uint32_t size, BlockStatus isBlock);
int itcs_uart_is_completed(UART_HandleTypeDef *uartHandler, int tx_rx);

#endif /*__UART_H__*/
