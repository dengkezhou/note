#ifndef __SPI_H__
#define __SPI_H__

#include <spi-common.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct SPI_handle {
  /*common data structure*/
  SPI_InitTypeDef SPI_InitStruct; /* SPI init structure  */
  void *spi_profile;
} SPI_HandleTypeDef;

void itcs_spi_chip_select(SPI_HandleTypeDef *spiHandler, int voltage);
SPI_HandleTypeDef *itcs_spi_init(SPI_InitTypeDef *init);
void itcs_spi_deinit(SPI_HandleTypeDef *spiHandler);
int itcs_spi_receive(SPI_HandleTypeDef *spiHandler, uint8_t *data,
                     uint32_t size, bool isBlock);
int itcs_spi_transmit(SPI_HandleTypeDef *spiHandler, uint8_t *data,
                      uint32_t size, bool isBlock);
int itcs_spi_transmit_receive(SPI_HandleTypeDef *spiHandler, uint8_t *tx_data,
                              uint8_t *rx_data, uint32_t size, bool isBlock);
int itcs_spi_get_transfer_status(SPI_HandleTypeDef *spiHandler, bool tx);

#endif /*__SPI_H__*/
