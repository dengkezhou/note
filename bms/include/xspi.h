#ifndef __XSPI_H__
#define __XSPI_H__

#include <cdn_stdint.h>
#include <cdn_errno.h>
#include <cdn_log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xspi_if.h>
#include <xspi_structs_if.h>
#include <xspi_obj_if.h>
#include <cps.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef CONFIG_COMPILE_RTL
#define DEBUG_XSPI
#endif

#ifdef DEBUG_XSPI
#define DEBUG_XSPI_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_XSPI_LOG(format, ...)
#endif

typedef enum { OSPI = 0, QSPI = 1 } XSPI_e;

typedef struct {
  XSPI_e XSPIx;
  uint32_t ClockMode;
  int line_num;
  int flash_type;
#define SPI_NOR_FLASH  0
#define SPI_NAND_FLASH 1
#define HYPER_RAM      2
#define HYPER_FLASH    3
  bool dev_discovery;
  bool ddr;

  // unit of size is byte
  uint32_t flash_size;
  uint32_t block_size;
  uint32_t sector_size;
  uint32_t page_size;
} XSPI_InitTypeDef;

typedef struct XSPI_handle {
  XSPI_InitTypeDef init;
  XSPI_PrivateData *pD;
  XSPI_OBJ *drv;
  // the callback functions passed to driver (must be provided by a user)
  XSPI_Callbacks cb;
  uint32_t reg_base;
  uint8_t work_mode;
#define CDNS_XSPI_MODE_DIRECT    0
#define CDNS_XSPI_MODE_STIG      1
#define CDNS_XSPI_MODE_ACMD_PIO  2
#define CDNS_XSPI_MODE_ACMD_CMDA 3
  bool cpu_access;
} XSPI_HandleTypeDef;

XSPI_HandleTypeDef *itcs_xspi_init(XSPI_InitTypeDef *init);
int cdns_xspi_send_acmd_pio_command(XSPI_HandleTypeDef *xspi_handler,
                                    XSPI_PioCommand *cmd);
int cdns_xspi_send_acmd_cdma_command(XSPI_HandleTypeDef *xspi_handler,
                                     XSPI_CdmaCommand *cmd);
int cdns_xspi_send_direct_command(XSPI_HandleTypeDef *xspi_handler,
                                  XSPI_DirectCmd *cmd);
int cdns_xspi_send_stig_command(XSPI_HandleTypeDef *xspi_handler,
                                XSPI_StigCommand *cmd);

#endif /*__XSPI_H__*/
