# UART相关公共接口说明

## 头文件

```c
#include <uart.h>
```
## 重要数据结构说明
* UART_InitTypeDef
```c
typedef struct {
  /*Specifies which uart type is used,CDNS or DWC*/
  UART_TYPE type; 
  /*Specifies which uart is used*/
  UART UARTx;                       
  /*This member configures the UART communication baud rate.*/
  uint16_t UART_BaudRate;
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
} UART_InitTypeDef;
```


## 接口说明

* 串口模式初始化

	**初始化的时候确定使用DWC或CDNS串口，如果DWC串口使用DMA方式传输则初始化init结构体下的dma结构体，若init->dma == NULL则使用中断方式传输数据**
	
  初始化内容：	
	
	* 选择使用DWC或CDNS uart
	* 启用或不启用DMA（仅针对DWC uart）
	* 选择UART0~UART3
	* IrDA/UART(RS232)/RS485模式
	* 数据位（5/6/7/8/9）、校验位、停止位（1/1.5/2）
	* FIFO访问宽度（仅针对CDNS uart）
	* 硬件流控设置
	```c 
	UART_HandleTypeDef* itcs_uart_init(UART_InitTypeDef* init);	
	```
	|参数/返回值|说明|
	|--|--|
	|init|初始化结构体，定义及相关变量解释见上文重要数据结构说明|
	|返回值|串口句柄|
	
* 串口模式去初始化

	关闭接收和发送器，释放和重新复位相关数据结构
	```c 
	void itcs_uart_deinit(UART_HandleTypeDef *uartHandler);
	```
	|参数/返回值|说明|
	|--|--|
	|uartHandler|串口句柄|
	|返回值|-|

* 串口发送数据

	**函数内部根据uartHandler->type选择调用CDNS或DWC相关的数据发送函数，根据uartHandler->dma是否为空判断使用中断方式还是DMA方式进行发送**

  ```c 
  int itcs_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data, uint32_t size, uint8_t isBlock);
  ```
	|参数/返回值|说明|
	|--|--|
	|uartHandler|串口句柄|
	|data|要发送的数据的buffer地址|
	|size|要发送的数据的字节数|
	|isBlock|是否阻塞发送|
	|返回值|发送的字节数|
	
* 串口接收数据

	**函数内部根据uartHandler->type选择调用CDNS或DWC相关的数据接收函数，根据uartHandler->dma是否为空判断使用中断方式还是DMA方式进行接收**
  
  ```c 
  int itcs_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data, uint32_t size, uint8_t isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|uartHandler|串口句柄|
	|data|要接收数据存放的buffer地址|
	|size|数据存放buffer的尺寸|
	|isBlock|是否阻塞接收|
	|返回值|接收的字节数|

* 串口接收或发送是否完成

  ```c 
  int itcs_uart_is_completed(UART_HandleTypeDef *uartHandler, uint8_t rx_tx);
	```
	|参数/返回值|说明|
	|--|--|
	|uartHandler|串口句柄|
	|rx_tx|传入UART_RX_COMPLETE或UART_TX_COMPLETE|
	|返回值|1:完成 0:其他|

## 示例代码
* **cdns uart示例**
```c 
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <uart.h>
#include <cdns_uart.h>

#define SUCCESS 1
#define FAILURE 0

 
#define INIT_PARAM                                                        \
    {CDNS_UART,                                                           \
    UART0,                                                                \
    (uint16_t)115200,                                                     \
    CDNS_UART_WordLength_8b,                                              \
    CDNS_UART_Parity_No,                                                  \
    CDNS_UART_StopBits_1,                                                 \
    CDNS_UART_HardwareFlowControl_None,                                   \
    CDNS_UART_Mode_UART,                                                  \
    0,                                                                    \
    CDNS_UART_ChannelMode_Normal,                                         \
    CDNS_UART_WSIZE_1,                                                    \
    }                                                                                  

int uart_main(int argc, char *argv[]) {
  UART_InitTypeDef init_a = INIT_PARAM;
  UART_InitTypeDef init_b = INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UARTx = UART0;
  init_b.UARTx = UART1;
  UART_HandleTypeDef* huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef* huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  while (1) {
    // uart b received
    if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
        // The data are consistent,send data back.
        memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
        itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
      } else {
        return FAILURE;
      }
    }
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        itcs_uart_deinit(huart_a);
        itcs_uart_deinit(huart_b);
        return SUCCESS;
      } else {
        return FAILURE;
      }
    }
  }
}
```

* **dwc uart示例**
```c 
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <uart.h>
#include <dwc_uart.h>


#define SUCCESS 1
#define FAILURE 0

#ifdef CONFIG_COMPILE_RTL
#define UART_BUF_MAX_SIZE 32
#else
#define UART_BUF_MAX_SIZE 1024
#endif

#define INIT_PARAM                                             \
  {                                                                        \
    DWC_UART, UART0, (uint16_t)115200, DWC_UART_WordLength_8b,             \
    DWC_UART_Parity_No, DWC_UART_StopBits_1,                               \
    DWC_UART_HardwareFlowControl_None, DWC_UART_Mode_UART, 0, 0, 0         \
  }

int uart_main() {
  UART_InitTypeDef init_a = INIT_PARAM;
  UART_InitTypeDef init_b = INIT_PARAM;
  uint8_t uart_a_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_a_tx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_rx_buffer[UART_BUF_MAX_SIZE];
  uint8_t uart_b_tx_buffer[UART_BUF_MAX_SIZE];
  init_a.UARTx = UART0;
  init_b.UARTx = UART1;

  UART_HandleTypeDef *huart_a = itcs_uart_init(&init_a);
  UART_HandleTypeDef *huart_b = itcs_uart_init(&init_b);

  itcs_uart_receive(huart_a, uart_a_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  itcs_uart_receive(huart_b, uart_b_rx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);

  for (int i = 0; i < UART_BUF_MAX_SIZE; i++) {
    uart_a_tx_buffer[i] = i;
  }
  itcs_uart_transmit(huart_a, uart_a_tx_buffer, UART_BUF_MAX_SIZE, NONBLOCK);
  while (1) {
    // uart b received
    if (itcs_uart_is_completed(huart_b, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->txBufPtr, huart_b->rxBufPtr, huart_a->txCount)) {
        // The data are consistent,send data back.
        memcpy(uart_b_tx_buffer, huart_b->rxBufPtr, huart_a->txCount);
        itcs_uart_transmit(huart_b, uart_b_tx_buffer, UART_BUF_MAX_SIZE,
                           NONBLOCK);
      } else {
        return FAILURE;
      }
    }
    if (itcs_uart_is_completed(huart_a, UART_RX_COMPLETE)) {
      if (!memcmp(huart_a->rxBufPtr, huart_b->txBufPtr, huart_b->txCount)) {
        return SUCCESS;
      } else {
        return FAILURE;
      }
    }
  }
}

```