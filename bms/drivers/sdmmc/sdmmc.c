/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     sdmmc.c
 * @brief    cdns sdmmc Driver
 * @version  V1.0
 * @date     06.13 2022
 * @name     sdmmc
 *
 * @author   jason.liu
 *******************************************************************/
#include <malloc.h>
#include <irq.h>
#include <pads.h>
#include <sdio_dfi.h>

#include <csdd_obj_if.h>
#include <csdd_structs_if.h>
#include <sdmmc.h>
#include <cdn_errno.h>


static CSDD_Config *config;
static CSDD_Callbacks *cb;
static CSDD_SysReq *sysReq;

CSDD_OBJ *sdHostDriver;
CSDD_SDIO_Host *sdHost;

static void combo_reg_config(void)
{
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x00, 0x00000001); // SDHC
    CPS_WriteReg32((void *)(ITCS_C_EMMC0_COMBO_BASE + 0x20), 0x5F6A3C8A); // SRS16
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x24, 0x88000077); // SRS17
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x28, 0x20202020); // SRS18
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x2c, 0x00000020); // SRS19
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x30, 0x000400FA); // SRS24
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x34, 0x00040002); // SRS25
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x38, 0x00010002); // SRS26
    // CPS_WriteReg32(ITCS_C_EMMC0_COMBO_BASE + 0x3c, 0x00020000); // SRS27
    CPS_WriteReg32((void *)(ITCS_C_EMMC0_COMBO_BASE + 0x10), 0x00000001); // SD_DET Bypass
}

static int sdmmc_module_init(uint8_t index)
{
  char * module_name = NULL;

  switch(index){
    case 0:
        module_name = "emmc0";
        break;
    case 1:
        module_name = "sd1";
        break;
    case 2:
        module_name = "sd2";
        break;
    default:
        return -1;
  }

  writel((0xffff), (0xC5f00000+index*0x400+0x4 )); // clkgate en
  writel((0x3), (0xC5f00000+index*0x400+0xc ));    // bus en
  writel((0x1), (0xC5f00000+index*0x400+0x18));    // io in en
  combo_reg_config();
  itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, module_name);
  itcs_module_set_clock(CPU, module_name, NULL, FGPA_SD_EXT_CLK, 0);

  writel((0x0), (0xC5f00000+index*0x400+0x0 ));    // reset release

  printf("sdmmc freq: %d\n", (int)itcs_module_get_clock(CPU, module_name));
  return 0;
}

static int sdmmc_irq_handler(int irq, void *args) {
  bool handled;

  CSDD_OBJ *sdHostDrv = (CSDD_OBJ *)args;
  sdHostDrv->isr(sdHost, &handled);
  return 0;
}

static int sdmmc_register_irq(uint8_t index, CSDD_OBJ *sdHostDrv){
  unsigned int irq;
  char *s;

  switch (index) {
  case 0:
    irq = C_EMMC0_IRQn;
    s = "emmc0_irq";
    break;
  case 1:
    irq = C_SD1_IRQn;
    s = "sd1_irq";
    break;
  case 2:
    irq = C_SD2_IRQn;
    s = "sd2_irq";
    break;
  default:
    return -1;
  }
  return request_irq(irq, sdmmc_irq_handler, s, sdHostDrv);  
}

static uint8_t setTuneVal(const CSDD_SDIO_Host* pd, uint8_t tune_val)
{
    return dfihs200Init(tune_val);
}

int itcs_sdmmc_init(SDMMC_Handler **pphandler, SDMMC_InitTypeDef *init)
{
    uintptr_t regBase;
    uint8_t status;
    int ret;

    SDMMC_Handler *sdmmc_handler = NULL;

    printf("Start sdmmc init...\n");

    if (!init || !pphandler)
        return -1;

    if (*pphandler)
        goto skip_init;

    if (init->mod_index == 0)
        regBase = ITCS_C_EMMC0_BASE;
    else if(init->mod_index == 1)
        regBase = ITCS_C_SD1_BASE;
    else
        regBase = ITCS_C_SD2_BASE;

    ret = sdmmc_module_init(init->mod_index);
    if (ret < 0)
        return -1;

    sysReq = calloc(1, sizeof(*sysReq));
    config = calloc(1, sizeof(*config));
    cb = calloc(1, sizeof(*cb));

    sdHostDriver = CSDD_GetInstance();
    sdHostDriver->probe(regBase, sysReq);
    sdHost = calloc(1, sysReq->pDataSize);
    if (!sdHost)
        return -1;

    config->descLogAddress = (uint32_t*)malloc(sysReq->descSize);
    config->idDescLogAddress = (uint32_t*)malloc(sysReq->idDescSize);
    config->descPhyAddress = config->descLogAddress;
    config->idDescPhyAddress = config->idDescLogAddress;
    config->regBase = regBase;

    if (sizeof(void *) > 4) {
        config->dma64BitEn = 1;
    } else {
        config->dma64BitEn = 0;
    }

    cb->setTuneValCallback = &setTuneVal;

    status = sdHostDriver->init(sdHost, config, cb);
    if (status)
        goto err;

    /* Combo PHY Driver init and config PHY*/
    if (sdHost->hostCtrlVer >= 6) {
        if (dfiInitDriver(sdHost))
            goto err;
        else if (dfiInit())
            goto err;
    }

    /* load memory card driver, it is necessary to use this driver */
    sdHostDriver->memoryCardLoadDriver(sdHost);

    sdmmc_handler = malloc(sizeof(*sdmmc_handler));
    if (!sdmmc_handler)
        goto err;
    
    *pphandler = sdmmc_handler;

    sdmmc_handler->sdHostDriver = sdHostDriver;
    sdmmc_handler->sdHost = sdHost;
    sdmmc_handler->config = config;
    sdmmc_handler->cb = cb;
    sdmmc_handler->sysReq = sysReq;

skip_init:
	memcpy(&(*pphandler)->init, init, sizeof(*init));

    if (init->withInt) {
        sdmmc_register_irq(init->mod_index, sdHostDriver);
        sdHostDriver->start(sdHost);
    } else {
        sdHostDriver->stop(sdHost);
    }
    return 0;

err:
    if (!config->idDescLogAddress)
        free(config->idDescLogAddress);
    if (!config->descLogAddress)
        free(config->descLogAddress);
    if (!sdHost)
        free(sdHost);
    return -1;
}

struct mmc_config {
    CSDD_Config *config;
    CSDD_Callbacks *cb;
    CSDD_SysReq *sysReq;
    CSDD_OBJ *sdHostDriver;
    CSDD_SDIO_Host *sdHost;
    bool initialized;
};

static struct mmc_config mmc_config[3];

int itcs_sdmmc_simple_init(int moduleIndex)
{
    uintptr_t regBase;
    int ret;
    uint32_t status;
    CSDD_SpeedMode speedMode;
    uint8_t busWidth;
    uint32_t freqKHz;

    struct mmc_config *cfg;

    if (mmc_config[moduleIndex].initialized)
        return 0;

    switch (moduleIndex) {
    case 0:
        regBase = ITCS_C_EMMC0_BASE;
        busWidth = 1;
        freqKHz = 10000;
        speedMode = CSDD_ACCESS_MODE_MMC_LEGACY;
        break;
    case 1:
        regBase = ITCS_C_SD1_BASE;
        busWidth = 4;
        freqKHz = 25000;
        speedMode = CSDD_ACCESS_MODE_SDR12;
        break;
    default:
        return -1;
    }

    ret = sdmmc_module_init(moduleIndex);
    if (ret < 0)
        return -1;

    memset(&mmc_config[moduleIndex], 0, sizeof(mmc_config[moduleIndex]));
    cfg = &mmc_config[moduleIndex];

    cfg->sysReq = cfg->sysReq ?: calloc(1, sizeof(*cfg->sysReq));
    cfg->config = cfg->config ?: calloc(1, sizeof(*cfg->config));
    cfg->cb = cfg->cb ?: calloc(1, sizeof(*cfg->cb));

    cfg->sdHostDriver = CSDD_GetInstance();
    cfg->sdHostDriver->probe(regBase, cfg->sysReq);

    cfg->sdHost = cfg->sdHost ?: calloc(1, cfg->sysReq->pDataSize);

    cfg->config->descLogAddress = cfg->config->descLogAddress ?: malloc(cfg->sysReq->descSize);
    cfg->config->idDescLogAddress = cfg->config->idDescLogAddress ?: malloc(cfg->sysReq->idDescSize);
    cfg->config->descPhyAddress = cfg->config->descLogAddress;
    cfg->config->idDescPhyAddress = cfg->config->idDescLogAddress;
    cfg->config->regBase = regBase;
    cfg->config->dma64BitEn = sizeof(void *) > 4 ? 1 : 0;

    cfg->sdHostDriver->init(cfg->sdHost, cfg->config, cfg->cb);

    dfiInitDriver(cfg->sdHost);
    dfiInit();

    cfg->sdHostDriver->memoryCardLoadDriver(cfg->sdHost);
    cfg->sdHostDriver->stop(cfg->sdHost);

    if (moduleIndex == 1)
        cfg->sdHost->Slots[0].Force3v3 = 1;

    status = cfg->sdHostDriver->checkSlots(cfg->sdHost);
    CHECK_STATUS(status);

    CSDD_DeviceState deviceState;
    cfg->sdHostDriver->getDeviceState(cfg->sdHost, 0, &deviceState);
    if (!deviceState.inserted) {
        printf("There is no card in slot\n");
        return -1;
    }

    uint8_t size;

    size = sizeof(busWidth);
    status = cfg->sdHostDriver->configure(cfg->sdHost, 0,
                                     CSDD_CONFIG_SET_BUS_WIDTH,
                                     &busWidth, &size);
    CHECK_STATUS(status);

    status = cfg->sdHostDriver->configureAccessMode(cfg->sdHost, 0,
                                                speedMode);
    CHECK_STATUS(status);

    size = sizeof(freqKHz);
    status = cfg->sdHostDriver->configure(cfg->sdHost, 0,
                                      CSDD_CONFIG_SET_CLK, &freqKHz, &size);
    CHECK_STATUS(status);

    cfg->initialized = true;
    return 0;
}

void itcs_sdmmc_deinit(SDMMC_Handler *handler)
{
    sdHostDriver = NULL;
    CHECK_FREE(sdHost);
}

int itcs_sdmmc_read(int devn, uint64_t addr, size_t size, void *buf)
{
    struct mmc_config *cfg = &mmc_config[devn];
    return cfg->sdHostDriver->memoryCardDataTransfer(cfg->sdHost, 0,
            addr, buf, size, CSDD_TRANSFER_READ);
}

int itcs_sdmmc_write(int devn, uint64_t addr, size_t size, void* buf)
{
    struct mmc_config *cfg = &mmc_config[devn];
    return cfg->sdHostDriver->memoryCardDataTransfer(cfg->sdHost, 0,
            addr, buf, size, CSDD_TRANSFER_WRITE);
}

int itcs_sdmmc_erase(int devn, uint64_t addr, size_t size)
{
    uint8_t status;
    struct mmc_config *cfg = &mmc_config[devn];

    if(addr % 512){
        printf("address aglined error,must be divided evenly by 512.");
        return 0;
    }
    if(size % 512){
        printf("size aglined error,must be divided evenly by 512.");
        return 0;
    }
    status = cfg->sdHostDriver->memoryCardDataErase(cfg->sdHost, 0, addr, size);
    if (status)
        return size;

    return 0;
}

int itcs_sdmmc_get_block_len(void)
{
    uint8_t status;
    //[83:80] 4bits means READ_BL_LEN
    //block length = 2 ^ (READ_BL_LEN)
    uint32_t csd_buffer[4];
    uint8_t tmp;

    status = sdHostDriver->readCsd(sdHost, 0, csd_buffer);
    if (status)
        return -1;

    tmp = ((uint8_t) (csd_buffer[2] >> 16)) & 0x0f;
    return 1 << tmp;
}
