/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     spi.c
 * @brief    spi Driver
 * @version  V1.0
 * @date     07.26 2022
 * @name     spi
 *
 * @author   jason.liu
 *******************************************************************/

#include <spi.h>
#include "arm-spi.h"
#include <malloc.h>

static int check_init_param(SPI_InitTypeDef *init) {
  if (init == NULL) {
    printf("init should not be NULL.\n");
    return -1;
  }

  return 0;
}

void itcs_spi_chip_select(SPI_HandleTypeDef *spiHandler, int voltage) {
  if (spiHandler->SPI_InitStruct.type == SPI_TYPE_ARM_SSP) {
    arm_spi_chipselect((struct arm_spi_profile *)(spiHandler->spi_profile),
                       voltage);
  }
}

SPI_HandleTypeDef *itcs_spi_init(SPI_InitTypeDef *init) {
  SPI_HandleTypeDef *handler = NULL;

  if (check_init_param(init)) {
    return NULL;
  }

  handler = (SPI_HandleTypeDef *)malloc(sizeof(SPI_HandleTypeDef));
  if (handler == NULL) {
    printf("malloc memory for SPI_HandleTypeDef failed!\n");
    return NULL;
  }
  memset(handler, 0, sizeof(SPI_HandleTypeDef));
  handler->SPI_InitStruct = *init;

  if (handler->SPI_InitStruct.type == SPI_TYPE_ARM_SSP) {
    handler->spi_profile = arm_spi_init(init);
  }

  if (handler->spi_profile == NULL) {
    printf("spi initilize failed!\n");
    goto err;
  }

  return handler;

err:
  spi_check_free(handler->spi_profile);
  spi_check_free(handler);
  return NULL;
}

void itcs_spi_deinit(SPI_HandleTypeDef *spiHandler) {
  if (spiHandler->SPI_InitStruct.type == SPI_TYPE_ARM_SSP) {
    arm_spi_deinit((struct arm_spi_profile *)(spiHandler->spi_profile));
  }

  spi_check_free(spiHandler);
}

int itcs_spi_receive(SPI_HandleTypeDef *spiHandler, uint8_t *data,
                     uint32_t size, bool isBlock) {
  int ret = 0;
  if (spiHandler->SPI_InitStruct.type == SPI_TYPE_ARM_SSP) {
    ret = arm_spi_receive((struct arm_spi_profile *)(spiHandler->spi_profile),
                          data, size, isBlock);
  }
  return ret;
}

int itcs_spi_transmit(SPI_HandleTypeDef *spiHandler, uint8_t *data,
                      uint32_t size, bool isBlock) {
  int ret = 0;
  if (spiHandler->SPI_InitStruct.type == SPI_TYPE_ARM_SSP) {
    ret = arm_spi_transmit((struct arm_spi_profile *)(spiHandler->spi_profile),
                           data, size, isBlock);
  }
  return ret;
}

int itcs_spi_transmit_receive(SPI_HandleTypeDef *spiHandler, uint8_t *tx_data,
                              uint8_t *rx_data, uint32_t size, bool isBlock) {
  int ret = 0;
  if (spiHandler->SPI_InitStruct.type == SPI_TYPE_ARM_SSP) {
    ret = arm_spi_transmit_receive(
        (struct arm_spi_profile *)(spiHandler->spi_profile), tx_data, rx_data,
        size, isBlock);
  }
  return ret;
}

int itcs_spi_get_transfer_status(SPI_HandleTypeDef *spiHandler, bool tx) {
  switch (spiHandler->SPI_InitStruct.type) {
  case SPI_TYPE_ARM_SSP: {
    struct arm_spi_profile *profile;
    profile = (struct arm_spi_profile *)(spiHandler->spi_profile);
    return arm_spi_get_transfer_status(profile, tx);
    break;
  }
  default:
    break;
  }

  return -1;
}