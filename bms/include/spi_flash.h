#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#include "xspi.h"
#include "spi.h"
#include <spi_flash_common.h>

struct spi_flash_init_s {
  bool is_xspi;
  uint8_t ip_type;
  char *compatible_name;
  uint16_t spi_instance;
  uint32_t dataSize;
  int mode; // pol pha 00 01 10 11
  int freq_hz;
  int cs_mode; /* chip select mode */
#define HW_SPI_CS_MODE 1
#define GPIO_CS_MODE   2
  int cs_pin; /* chip select pin number */
  int line_num;
  int flash_type;
#define SPI_NOR_FLASH  0
#define SPI_NAND_FLASH 1
#define HYPER_RAM      2
#define HYPER_FLASH    3
#define SPI_WINBOND_NAND_FLASH 4
  bool dev_discovery;
  bool ddr;
};

struct spi_flash_obj {
  uint32_t base;
  bool is_xspi;
  struct spi_flash_init_s spi_flash_init;
  struct spi_flash_operations *f_ops;
  struct xspi_flash_operations *xf_ops;
  SPI_HandleTypeDef *spihandler;
  XSPI_HandleTypeDef *xhandler;
};

struct spi_flash_obj *itcs_spi_flash_init(struct spi_flash_init_s *init);
uint32_t itcs_spi_flash_read(struct spi_flash_obj *obj, uint8_t *pBuffer,
                             uint32_t addr, uint32_t byte_num);
uint32_t itcs_spi_flash_write(struct spi_flash_obj *obj, uint8_t *pBuffer,
                              uint32_t addr, uint32_t byte_num);
bool itcs_spi_flash_erase(struct spi_flash_obj *obj, SPI_FLASH_ERASE_TYPE type,
                          uint32_t addr);
uint32_t itcs_spi_flash_get_alignment(struct spi_flash_obj *obj);
bool itcs_spi_flash_write_protect(struct spi_flash_obj *obj, bool enable);

void itcs_spi_flash_reset(struct spi_flash_obj *obj);
#endif //__SPI_FLASH_H__
