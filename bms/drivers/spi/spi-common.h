#ifndef __COMMON_SPI_H__
#define __COMMON_SPI_H__

#include <stdbool.h>
#include <stdint.h>

//#define DEBUG_SPI

#ifdef DEBUG_SPI
#define DEBUG_SPI_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_SPI_LOG(format, ...)
#endif

#define SPI0_MODULE_NAME "spi0"
#define SPI1_MODULE_NAME "spi1"
#define SPI2_MODULE_NAME "spi2"
#define SPI3_MODULE_NAME "spi3"

#define spi_check_free(ptr)                                                    \
  do {                                                                         \
    if (ptr) {                                                                 \
      free(ptr);                                                               \
      ptr = NULL;                                                              \
    }                                                                          \
  } while (0)

typedef enum { SPI0 = 0, SPI1, SPI2, SPI3 } SPI;

enum spi_type {
  SSI_MOTO_SPI     = 0,
  SSI_TI_SSP       = 0x10,
  SSI_NS_MICROWIRE = 0x20,
};

enum spi_tmode { SSI_TR = 0, SSI_TO, SSI_RO, SSI_EEPROM };

typedef enum {
  SPI_STA_RESET = 0x00U, /* SPI isn't initialized     */
  SPI_STA_READY,         /* SPI is ready              */
  SPI_STA_BUSY,          /* SPI is busy with sth      */
  SPI_STA_BUSY_TX,       /* SPI is busy with transmit */
  SPI_STA_BUSY_RX,       /* SPI is busy with receive  */
  SPI_STA_BUSY_TX_RX,
  SPI_STA_TIMEOUT,     /* SPI timeout               */
  SPI_STA_TX_COMPLETE, /* SPI transmit complete.    */
  SPI_STA_RX_COMPLETE, /* SPI receive  complete.    */
  SPI_STA_ERROR,       /* SPI error                 */
  SPI_STA_ABORT,       /* SPI abort                 */
} SPI_StatusTypeDef;

typedef enum {
  SPI_ERROR_NONE  = 0x00, /* SPI no error              */
  SPI_ERROR_MODF  = 0x01, /* SPI MODF error            */
  SPI_ERROR_CRC   = 0x02, /* SPI CRC error             */
  SPI_ERROR_OVR   = 0x03, /* SPI OVR error             */
  SPI_ERROR_DMA   = 0x04, /* SPI DMA error             */
  SPI_ERROR_ABORT = 0x05, /* SPI in abort              */
  SPI_ERROR_PARAM = 0x06, /* SPI param error           */
} SPI_ErrorTypeDef;

typedef enum {
  HAL_OK      = 0x00U,
  HAL_ERROR   = 0x01U,
  HAL_BUSY    = 0x02U,
  HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef struct {
  /* Specifies which SPI is used. */
  SPI SPIx;

  /* Specifies which SPI type is used. */
  uint8_t type;
#define SPI_TYPE_DWC_SSI 1
#define SPI_TYPE_ARM_SSP 2

  /* Specifies whether enable dma transfer */
  bool enable_dma;
  bool enable_ddr;

  /* Specifies the SPI operating mode. */
  uint32_t mode;
#define SPI_MODE_SLAVE  0
#define SPI_MODE_MASTER 1

  /* Specifies the SPI data size. */
  uint32_t dataSize;
#define SPI_DATASIZE_8BIT  0x7
#define SPI_DATASIZE_16BIT 0xf

  /* Specifies the serial clock steady state. */
  uint32_t CLKPolarity;
#define SPI_POLARITY_LOW  0x00
#define SPI_POLARITY_HIGH 0x80

  /* Specifies the clock active edge for the bit capture. */
  uint32_t CLKPhase;
#define SPI_PHASE_1EDGE 0x00
#define SPI_PHASE_2EDGE 0x40

  /* Specifies the bus frequency in hz. */
  uint32_t freq_hz;

  /* Specifies whether enable the software NSS. */
  int cs_mode; /* chip select mode */
#define HW_SPI_CS_MODE 1
#define GPIO_CS_MODE   2
  int cs_pin; /* chip select pin number */
  /*Specifies ports to use spi func, is don`t have, use default in pads.c*/
  struct pads_modules_bundle* pads;

} SPI_InitTypeDef;

unsigned long spi_get_base_addr(SPI SPIx);
int spi_module_enable(SPI SPIx, bool enable);
int spi_module_set_pads(SPI SPIx);
int spi_get_dma_info(SPI SPIx, bool tx);
#endif //__COMMON_SPI_H__