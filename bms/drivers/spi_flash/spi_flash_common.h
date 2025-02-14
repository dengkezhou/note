#ifndef __SPI_FLASH_COMMON_H__
#define __SPI_FLASH_COMMON_H__

#include "spi.h"
#include "xspi.h"

#define BYTES_PER_XSPI_DMA_OP 8 

typedef enum {
  SPI_FLASH_ERASE_SECTOR = 0,
  SPI_FLASH_ERASE_BLOCK,
  SPI_FLASH_ERASE_FULL_CHIP
} SPI_FLASH_ERASE_TYPE;

struct spi_flash_operations {
  SPI_HandleTypeDef *(*init)(SPI_InitTypeDef *);
  uint32_t (*read)(SPI_HandleTypeDef *, uint8_t *, uint32_t, uint32_t);
  uint32_t (*write)(SPI_HandleTypeDef *, uint8_t *, uint32_t, uint32_t);
  bool (*erase)(SPI_HandleTypeDef *, SPI_FLASH_ERASE_TYPE, uint32_t);
  uint32_t (*get_alignment)(SPI_HandleTypeDef *);
  bool (*write_protect)(SPI_HandleTypeDef *, bool);
  void (*reset)(SPI_HandleTypeDef *);
};

struct xspi_flash_operations {
  XSPI_HandleTypeDef *(*init)(XSPI_InitTypeDef *);
  uint32_t (*read)(XSPI_HandleTypeDef *, uint8_t *, uint32_t, uint32_t);
  uint32_t (*write)(XSPI_HandleTypeDef *, uint8_t *, uint32_t, uint32_t);
  bool (*erase)(XSPI_HandleTypeDef *, SPI_FLASH_ERASE_TYPE, uint32_t);
  uint32_t (*get_alignment)(XSPI_HandleTypeDef *);
  bool (*write_protect)(XSPI_HandleTypeDef *, bool);
  void (*reset)(XSPI_HandleTypeDef *);
};

struct spi_transfer {
  uint8_t cmd[4];
  uint8_t *tx_data;
  uint8_t *rx_data;
  uint32_t cmd_size;
  uint32_t data_size;
};

#endif //__SPI_FLASH_COMMON_H__