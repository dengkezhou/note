#include "spi_flash.h"
#include "xspi_flash.h"
#include <malloc.h>
#include "spi_nand_flash.h"
#include "spi_nor_flash.h"
#include "xspi_nand_flash.h"
#include "xspi_nor_flash.h"
#include "xspi_hyper_flash.h"
#include "xspi_hyper_ram.h"

struct spi_flash_bind {
  const char *compatible;
  struct spi_flash_operations  *f_ops;
};

struct spi_flash_bind spi_flash_table[] = {
    {"spi_nand", &f_ops_spi_nand},
    {"spi_nor", &f_ops_spi_nor},
    {NULL},
};

static struct spi_flash_operations *match_spi_flash_ops(const char *name) {
  for (int i = 0; spi_flash_table[i].compatible != NULL; i++) {
    if (!strncmp(spi_flash_table[i].compatible, name, 32)) {
      printf("match_spi_flash_ops: %s\n", name);
      return spi_flash_table[i].f_ops;
    }
  }
  return NULL;
}

#if defined(CONFIG_DRV_XSPI)

struct xspi_flash_bind {
  const char *compatible;
  struct xspi_flash_operations  *f_ops;
};

struct xspi_flash_bind xspi_flash_table[] = {
    {"xspi_nor", &f_ops_xspi_nor},
    {"mxic_nor", &f_ops_mxic_nor},
    {"gd_nor", &f_ops_gd_nor},
    {"xspi_nand", &f_ops_xspi_nand},
    {"xspi_hyper_flash", &f_ops_xspi_hyper_flash},
    {"xspi_hyper_ram", &f_ops_xspi_hyper_ram},
    {NULL},
};

static struct xspi_flash_operations *match_xspi_flash_ops(const char *name) {
  for (int i = 0; xspi_flash_table[i].compatible != NULL; i++) {
    if (!strncmp(xspi_flash_table[i].compatible, name, 32)) {
      printf("match_xspi_flash_ops: %s\n", name);
      return xspi_flash_table[i].f_ops;
    }
  }
  return NULL;
}
#endif 

struct spi_flash_obj *itcs_spi_flash_init(struct spi_flash_init_s *init) {
  struct spi_flash_obj *obj = NULL;
  obj = (struct spi_flash_obj *)malloc(sizeof(struct spi_flash_obj));
  if (obj == NULL) {
    printf("malloc memory for struct spi_flash_obj failed!\n");
    return NULL;
  }
  memset(obj, 0, sizeof(struct spi_flash_obj));

  obj->spi_flash_init = *init;
  obj->is_xspi        = init->is_xspi;

  if (init->is_xspi) {
#if defined(CONFIG_DRV_XSPI)
    XSPI_InitTypeDef xspi_init;
    xspi_init.XSPIx      = init->spi_instance;
    xspi_init.flash_type = init->flash_type;
    if ((init->mode == 0) || (init->mode == 1))
      xspi_init.ClockMode = 0;
    else
      xspi_init.ClockMode = 1;

    if(init->spi_instance == QSPI) {
        obj->base = ITCS_C_QSPI_BASE;
    }else{
        obj->base = ITCS_C_OSPI_BASE;
    }

    xspi_init.line_num      = init->line_num;
    xspi_init.dev_discovery = init->dev_discovery;
    xspi_init.ddr = init->ddr;

    obj->xf_ops = match_xspi_flash_ops(init->compatible_name);
    if (obj->xf_ops == NULL) {
      if (init->flash_type == SPI_NOR_FLASH) {
        obj->xf_ops = &f_ops_xspi_nor;
        printf("flash compatible unmatch, using general nor flash ops\n");
      } else if (init->flash_type == SPI_NAND_FLASH) {
        obj->xf_ops = &f_ops_xspi_nand;
        printf("flash compatible unmatch, using general nand flash ops\n");
      } else if (init->flash_type == HYPER_RAM) {
        obj->xf_ops = &f_ops_xspi_hyper_ram;
        printf("flash compatible unmatch, using general hyper ram ops\n");
      } else if (init->flash_type == HYPER_FLASH) {
        obj->xf_ops = &f_ops_xspi_hyper_flash;
        printf("flash compatible unmatch, using general hyper flash ops\n");
      }
    }

    obj->xhandler = obj->xf_ops->init(&xspi_init);
    return obj;
#endif // CONFIG_DRV_XSPI

  } else {
    SPI_InitTypeDef spi_init;
    if ((init->mode & 0x02)) {
      spi_init.CLKPolarity = SPI_POLARITY_HIGH;
    } else {
      spi_init.CLKPolarity = SPI_POLARITY_LOW;
    }
    if ((init->mode & 0x01)) {
      spi_init.CLKPhase = SPI_PHASE_2EDGE;
    } else {
      spi_init.CLKPhase = SPI_PHASE_1EDGE;
    }

    spi_init.cs_mode  = init->cs_mode;
    spi_init.cs_pin   = init->cs_pin;
    spi_init.dataSize = init->dataSize;
    spi_init.freq_hz  = init->freq_hz;
    spi_init.SPIx     = init->spi_instance;
    spi_init.type     = init->ip_type;
    spi_init.mode     = SPI_MODE_MASTER;
    spi_init.pads     = NULL;
    spi_init.enable_dma = false;
    spi_init.enable_ddr = false;

    obj->f_ops = match_spi_flash_ops(init->compatible_name);
    if (obj->f_ops == NULL) {
      if (init->flash_type == SPI_NOR_FLASH) {
        obj->f_ops = &f_ops_spi_nor;
      } else if (init->flash_type == SPI_NAND_FLASH) {
        obj->f_ops = &f_ops_spi_nand;
      }
    }

    obj->spihandler = obj->f_ops->init(&spi_init);
    return obj;
  }

  printf("spi or xspi does not enabled.\n");
  free(obj);
  return NULL;
}

uint32_t itcs_spi_flash_read(struct spi_flash_obj *obj, uint8_t *pBuffer,
                             uint32_t addr, uint32_t byte_num) {

  if (obj->is_xspi) {
#ifdef CONFIG_DRV_XSPI
    return obj->xf_ops->read(obj->xhandler, pBuffer, addr, byte_num);
#endif
  } else {
#ifdef CONFIG_DRV_SPI
    return obj->f_ops->read(obj->spihandler, pBuffer, addr, byte_num);
#endif
  }
  return 0;
}

uint32_t itcs_spi_flash_write(struct spi_flash_obj *obj, uint8_t *pBuffer,
                              uint32_t addr, uint32_t byte_num) {

  if (obj->is_xspi) {
#ifdef CONFIG_DRV_XSPI
    itcs_spi_flash_write_protect(obj, false);
    return obj->xf_ops->write(obj->xhandler, pBuffer, addr, byte_num);
#endif
  } else {
#ifdef CONFIG_DRV_SPI
    itcs_spi_flash_write_protect(obj, false);
    return obj->f_ops->write(obj->spihandler, pBuffer, addr, byte_num);
#endif
  }
  return 0;
}

bool itcs_spi_flash_erase(struct spi_flash_obj *obj, SPI_FLASH_ERASE_TYPE type,
                          uint32_t addr) {

  if (obj->is_xspi) {
#ifdef CONFIG_DRV_XSPI
    itcs_spi_flash_write_protect(obj, false);
    return obj->xf_ops->erase(obj->xhandler, type, addr);
#endif
  } else {
#ifdef CONFIG_DRV_SPI
    itcs_spi_flash_write_protect(obj, false);
    return obj->f_ops->erase(obj->spihandler, type, addr);
#endif
  }

  return true;
}

uint32_t itcs_spi_flash_get_alignment(struct spi_flash_obj *obj) {

  if (obj->is_xspi) {
#ifdef CONFIG_DRV_XSPI
    return obj->xf_ops->get_alignment(obj->xhandler);
#endif
  } else {
#ifdef CONFIG_DRV_SPI
    return obj->f_ops->get_alignment(obj->spihandler);
#endif
  }
  return 0;
}

bool itcs_spi_flash_write_protect(struct spi_flash_obj *obj, bool enable) {

  if (obj->is_xspi) {
#ifdef CONFIG_DRV_XSPI
    return obj->xf_ops->write_protect(obj->xhandler, enable);
#endif
  } else {
#ifdef CONFIG_DRV_SPI
    return obj->f_ops->write_protect(obj->spihandler, enable);
#endif
  }
  return true;
}

void itcs_spi_flash_reset(struct spi_flash_obj *obj) {
  if (obj->is_xspi) {
#ifdef CONFIG_DRV_XSPI
    return obj->xf_ops->reset(obj->xhandler);
#endif
  } else {
#ifdef CONFIG_DRV_SPI
    return obj->f_ops->reset(obj->spihandler);
#endif
  }
}
