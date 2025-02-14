#include <spi-common.h>
#include <dma-ops.h>
#include <pads.h>
#include <stdio.h>
#include <common.h>

unsigned long spi_get_base_addr(SPI SPIx) {
  switch (SPIx) {
  case SPI0:
    return ITCS_S_SPI0_BASE;
    break;
  case SPI1:
    return ITCS_C_SPI1_BASE;
    break;
  case SPI2:
    return ITCS_C_SPI2_BASE;
    break;
  case SPI3:
    return ITCS_C_SPI3_BASE;
    break;
  default:
    return ITCS_S_SPI0_BASE;
    break;
  }
}

int spi_module_enable(SPI SPIx, bool enable) {
  char *module_name = NULL;
  domain_t domain = SAP;
  switch (SPIx) {
  case SPI0:
    module_name = "spi0";
    domain = SAP;
    break;
  case SPI1:
    module_name = "spi1";
    domain = CPU;
    break;
  case SPI2:
    module_name = "spi2";
    domain = CPU;
    break;
  case SPI3:
    module_name = "spi3";
    domain = CPU;
    break;
  }
  if (enable)
    itcs_module_enable(domain, module_name);
  else
    itcs_module_disable(domain, module_name);
  return 0;
}

int spi_module_set_pads(SPI SPIx) {
  domain_t domain = SAP;
  char *module_name = NULL;
  switch (SPIx) {
  case SPI0:
    domain = SAP;
    module_name = "spi0";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case SPI1:
    domain = CPU;
    module_name = "spi1";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case SPI2:
    domain = CPU;
    module_name = "spi2";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  case SPI3:
    domain = CPU;
    module_name = "spi3";
    itcs_module_set_pads_by_index(module_name, 0);
    break;
  }
  return 0;
}

int spi_get_dma_info(SPI SPIx, bool tx) {
  switch (SPIx) {
  case SPI0:
    if (tx)
      return DMAC1_SPI0_TX;
    else
      return DMAC1_SPI0_RX;
    break;
  case SPI1:
    if (tx)
      return DMAC0_SPI1_TX;
    else
      return DMAC0_SPI1_RX;
    break;
  case SPI2:
    if (tx)
      return DMAC0_SPI2_TX;
    else
      return DMAC0_SPI2_RX;
    break;
  case SPI3:
    if (tx)
      return DMAC0_SPI3_TX;
    else
      return DMAC0_SPI3_RX;
    break;
  }
  return 0;
}
