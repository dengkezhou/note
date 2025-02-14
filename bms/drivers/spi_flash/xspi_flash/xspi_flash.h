#ifndef __XSPI_FLASH_H__
#define __XSPI_FLASH_H__

#include <common.h>
#include <xspi.h>
#include <spi_flash.h>
#include <spi_flash_common.h>

bool xspi_flash_device_discovery(XSPI_HandleTypeDef *handler, bool aut);
bool xspi_flash_boot(int port);
bool xspi_flash_enbale_device_discovery(XSPI_HandleTypeDef *handler,
                                        bool enable);
int xspi_nor_flash_xip(struct spi_flash_obj *obj);
bool xspi_write_image_to_flash(int port, uint8_t* head, uint64_t head_len, uint8_t* raw, uint64_t raw_len, uint32_t addr);
#endif //__XSPI_FLASH_H__