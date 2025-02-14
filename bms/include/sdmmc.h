#ifndef __SDMMC_H__
#define __SDMMC_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <csdd_obj_if.h>
#include <csdd_structs_if.h>

#define CHECK_FREE(ptr)                                                        \
  if (ptr) {                                                                   \
    free(ptr);                                                                 \
    ptr = NULL;                                                                \
  }

#define CHECK_STATUS(status)\
    if (status){\
        printf("%s:%d - error 0x%x \n", __func__, __LINE__, status);\
	      return status;\
    }

typedef struct {
  uint8_t slot_num;           /* Specifies the slot number */
  uint8_t mod_index;          /* Specifies the module number */
  uint8_t access_mode;        /* Specifies the access mode */
  uint8_t bus_width;          /* Specifies the bus width. */
  uint32_t freq_khz;          /* Specifies the frequency. */
  uint8_t dma_mode;           /* Specifies dma mode */
  uint8_t withInt;            /* Specifies if use interrupt */
} SDMMC_InitTypeDef;

typedef struct CSDD_OBJ_s CSDD_OBJ;

typedef struct {
  SDMMC_InitTypeDef init; /* init structure(user)           */
  CSDD_OBJ *sdHostDriver;
  CSDD_SDIO_Host *sdHost;
  CSDD_Config *config;
  CSDD_Callbacks *cb;
  CSDD_SysReq *sysReq;
  uint8_t uhsSupported;
} SDMMC_Handler;

int itcs_sdmmc_init(SDMMC_Handler **pphandler, SDMMC_InitTypeDef *init);
void itcs_sdmmc_deinit(SDMMC_Handler *handler);
int itcs_sdmmc_read(int devn, uint64_t addr, size_t size, void *buf);
int itcs_sdmmc_write(int devn, uint64_t addr, size_t size, void *buf);
int itcs_sdmmc_erase(int devn, uint64_t addr, size_t size);
int itcs_sdmmc_get_block_len(void);
int itcs_sdmmc_simple_init(int devn);

#endif /*__SDMMC_H__*/
