#ifndef __XSPI_NOR_FLASH_H__
#define __XSPI_NOR_FLASH_H__

#include <common.h>
#include <xspi.h>
#include <spi_flash_common.h>

extern struct xspi_flash_operations f_ops_xspi_nor;
extern struct xspi_flash_operations f_ops_mxic_nor;
extern struct xspi_flash_operations f_ops_gd_nor;

#endif //__XSPI_NOR_FLASH_H__