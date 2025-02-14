/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     sdmmc-main.c
 * @brief    sdmmc testBench
 * @version  V1.0
 * @date     06.15 2022

 * @name     sdmmc-main
 * author    jason.liu
 ******************************************************************************/

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>
#include <sdio_dfi.h>
#include <sdmmc.h>

#ifdef CONFIG_COMPILE_RTL
#define CARD_MODEL_SD   0x1
#define CARD_MODEL_EMMC 0x2
#define CARD_MODEL_SDIO 0x8
#endif

static unsigned char *writeBuffer;
static unsigned char *readBuffer;
static CSDD_Config *config;
static CSDD_OBJ *sdHostDriver;
static CSDD_SDIO_Host *sdHost;
static CSDD_Callbacks *cb;

static SDMMC_Handler *handler;

const static SDMMC_InitTypeDef default_init = {
  .slot_num = 0,
  .mod_index = 0,
  .bus_width = CSDD_BUS_WIDTH_1,
  .dma_mode = CSDD_SDMA_MODE,
  .access_mode = CSDD_ACCESS_MODE_MMC_LEGACY,
  .freq_khz = 25000,
};

static SDMMC_InitTypeDef init;
static uint32_t force_3v3 = 0;

static const char *access_mode_str[] = {
  "SDR12",          /** 0U : access mode - SDR12 default (CLK: max 25MHz, DT: max 12MB/s) */
  "SDR25",          /** 1U : access mode - SDR25 default (CLK: max 50MHz, DT: max 25MB/s) */
  "SDR50",          /** 2U : access mode - SDR50 default (CLK: max 100MHz, DT: max 50MB/s) */
  "SDR104",         /** 3U : access mode - SDR104 default (CLK: max 208MHz, DT: max 104MB/s) */
  "DDR50",          /** 4U : access mode - DDR50 default (CLK: max 50MHz, DT: max 50MB/s) */
  "Invalid",        /** 5U : Invalid mode string */
  "Legacy",         /** 6U : MMC access mode - legacy mode (CLK: max 26MHz, DT: max 26MB/s) */
  "High Speed SDR", /** 7U : MMC access mode - high speed SDR mode (CLK: max 26MHz, DT: max 26MB/s) */
  "High Speed DDR", /** 8U : MMC access mode - high speed DDR mode (CLK: max 52MHz, DT: max 104MB/s) */
  "HS200",          /** 9U : MMC access mode - HS200 mode (CLK: max 200MHz, DT: max 200MB/s) */
  "HS400",          /** 10U: MMC access mode - HS400 mode (CLK: max 200MHz, DT: max 400MB/s) */
  "HS400 ES",       /** 11 : MMC access mode - HS400 using Enhanced Strobe (CLK: max 200MHz, DT: max 400MB/s) */
};

static void test_result(uint8_t status, char *name)
{
  if (!name)
    printf("Test %s, %s mode, %s, %dbit@%dM, %s\n",
        init.mod_index == 0 ? "eMMC" : init.mod_index == 1 ? "SD" : "SDIO",
        init.access_mode >= ARRAY_SIZE(access_mode_str) ? "Invalid" : access_mode_str[init.access_mode],
        init.dma_mode == CSDD_NONEDMA_MODE ? "PIO" : "DMA",
        init.bus_width,
        init.freq_khz / 1000,
        status ? "Failed" : "Pass"
      );
  else
    printf("Test %s, %s, %s\n",
        init.mod_index == 0 ? "eMMC" : init.mod_index == 1 ? "SD" : "SDIO",
        name,
        status ? "Failed" : "Pass"
      );
}

static void Fillbuf(void *buf, uint32_t size)
{
    uint32_t tmp = size / 4;

    for (uint32_t i = 0, j = 0; i < tmp; i++, j += 4)
      *((uint32_t *)buf + i) =
            (((j + 0) & 0xff) << 0)
          | (((j + 1) & 0xff) << 8)
          | (((j + 2) & 0xff) << 16)
          | (((j + 3) & 0xff) << 24);

    tmp = size % 4;
    for (uint8_t i = 0; i < tmp; i++)
      *((uint8_t *)buf + i) = i & 0xff;
}

static uint8_t ReinitHostAndDevice(void)
{
    uint8_t status;

    printf("Reinitialize SD Host and device\n");

    /* reset host */
    status = sdHostDriver->resetHost(sdHost);
    CHECK_STATUS(status);

    /* Initialize host */
    status = sdHostDriver->init(sdHost, config, cb);
    CHECK_STATUS(status);

    status = dfiInit();
    CHECK_STATUS(status);

    if (sdHost->hostCtrlVer == 4) {
        status = sdHostDriver->writePhySet(sdHost, 0,
                                           CSDD_PHY_DELAY_DLL_HS_SDCLK, 5);
        if (status) {
            printf("Error cannot set phy configuration\n");
            return status;
        }
    }

    //sdHostDriver->start(sdHost);

    sdHostDriver->memoryCardLoadDriver(sdHost);

    status = sdHostDriver->checkSlots(sdHost);
    CHECK_STATUS(status);

    return 0;
}

static uint8_t WriteReadCompare(uint8_t slotIndex, uint32_t sectorNumber,
                         uint32_t DataSize)
{
    uint8_t status;

    printf("\tWrite data to memory sector number:%d, data size:%d\n",
             sectorNumber, DataSize);
    
    Fillbuf(writeBuffer, DataSize);

    status = sdHostDriver->memoryCardDataTransfer(sdHost, slotIndex,
                                                  sectorNumber, writeBuffer,
                                                  DataSize,
                                                  CSDD_TRANSFER_WRITE);
    CHECK_STATUS(status);

    printf("\tData write operation succeed\n");

    memset(readBuffer, 0xa5, DataSize);

    printf("\tRead data from memory sector number:%d, data size:%d\n",
             sectorNumber, DataSize);

    status = sdHostDriver->memoryCardDataTransfer(sdHost, slotIndex,
                                                  sectorNumber, readBuffer,
                                                  DataSize,
                                                  CSDD_TRANSFER_READ);

    CHECK_STATUS(status);
    printf("\tData read operation succeed\n");

    status = memcmp(writeBuffer, readBuffer, DataSize);
    if (status) {
        printf("\tError written data and read data are different\n\n");
    }
    else{
        printf("\tWritten data and read data are identically\n\n");
    }
    return status;
}

static uint8_t DMATest(uint32_t sectorNumber)
{
    uint8_t status, size;
    uint8_t slotIndex = handler->init.slot_num;
    uint8_t DmaMode = handler->init.dma_mode;
    size = sizeof(DmaMode);

    /* change DMA mode */
    status = sdHostDriver->configure(sdHost, slotIndex,
                                      CSDD_CONFIG_SET_DMA_MODE,
                                      &DmaMode, &size);
    if (status) {
        printf("\tSetting DMA mode to %d failed\n\n", DmaMode);
    }
    printf("\tSetting DMA mode to %d succeed\n", DmaMode);

    status = WriteReadCompare(slotIndex, sectorNumber, 1024);
    CHECK_STATUS(status);

    sectorNumber += 4;

    return 0;
}

static int MmcBootTest(uint32_t sectorNumber)
{
    uint8_t status;
    uint32_t dataSize = 512;
    uint32_t bootSize;
    CSDD_DeviceState deviceState;
    uint8_t slotIndex = handler->init.slot_num;

    sdHostDriver->getDeviceState(sdHost, slotIndex, &deviceState);

    if (deviceState.deviceType != CSDD_CARD_TYPE_MMC) {
        printf("Test is not supported for devices different than MMC\n");
        return -1;
    }

    memset(readBuffer, 0xa5, dataSize);
    Fillbuf(writeBuffer, dataSize);

    status = sdHostDriver->mmcGetParitionBootSize(sdHost, slotIndex, &bootSize);
    CHECK_STATUS(status);

    printf("Boot partition Size = %d KB\n", bootSize >> 10);

    if (!bootSize){
        printf("boot is not supported\n");
        return -1;
    }
    if (dataSize > bootSize)
        dataSize = bootSize;

    /* select access to partition boot 1 */
    status = sdHostDriver->mmcSetPartAccess(sdHost, slotIndex,
                                            CSDD_EMMC_ACCCESS_BOOT_1);
    CHECK_STATUS(status);

    /* program data to active partition */
    status = sdHostDriver->memoryCardDataTransfer(sdHost, slotIndex, 0,
                                                   writeBuffer,
                                                   dataSize, CSDD_TRANSFER_WRITE);
    CHECK_STATUS(status);

    /* select boot partition to boot operation 1 */
    status = sdHostDriver->mmcSetBootPartition(sdHost, slotIndex,
                                                CSDD_EMMC_BOOT_1);
    CHECK_STATUS(status);

    /* disable boot ACK (it cannot be properly handled in SW boot) */
    status = sdHostDriver->mmcSetBootAck(sdHost, slotIndex, false);
    CHECK_STATUS(status);

    /* detach device */
    status = sdHostDriver->deviceDetach(sdHost, slotIndex);
    CHECK_STATUS(status);
    printf("Device detached\n");

    /* reset host */
    status = sdHostDriver->resetHost(sdHost);
    CHECK_STATUS(status);
    printf("host reresed\n");

    /* Initialize host */
    status = sdHostDriver->init(sdHost, config, cb);
    CHECK_STATUS(status);
    printf("Host initialized\n");

    if (sdHost->hostCtrlVer >= 6) {
        status = dfiInit();
        CHECK_STATUS(status);
    }

    /* start interrupts */
    sdHostDriver->start(sdHost);

    /* short Initialization one slot (just enable clock and power supply) */
    status = sdHostDriver->simpleInit(sdHost, slotIndex, 400);
    CHECK_STATUS(status);

    /* execute eMMC boot to read data from boot partition */
    status = sdHostDriver->mmcExecuteBoot(sdHost, slotIndex, readBuffer,
                                          dataSize);
    printf("readBuffer %x\n", readBuffer[0]);
    CHECK_STATUS(status);

    /* compare written and read data */
    status = memcmp(writeBuffer, readBuffer, dataSize);
    CHECK_STATUS(status);

    return status;
}

static uint8_t MmchighSpeedTest(uint32_t sectorNumber)
{
    uint8_t status;
    uint32_t clockFreqsKHz = handler->init.freq_khz;
    uint8_t cardMode = handler->init.access_mode;
    unsigned char busWidth = handler->init.bus_width;
    unsigned char size;
    uint32_t freq = 400;
    uint8_t slotIndex = handler->init.slot_num;
    CSDD_DeviceState deviceState;

    if (force_3v3) {
      sdHost->Slots[0].Force3v3 = 1;
      access_mode_str[CSDD_ACCESS_MODE_SDR12] = "Default Speed";
      access_mode_str[CSDD_ACCESS_MODE_SDR25] = "High Speed";
    }

    status = sdHostDriver->checkSlots(sdHost);
    CHECK_STATUS(status);

    sdHostDriver->getDeviceState(sdHost, slotIndex, &deviceState);
    if (!deviceState.inserted) {
        printf("There is no eMMC in slot\n");
        return -1;
    }

    size = sizeof(busWidth);
    status = sdHostDriver->configure(sdHost, slotIndex,
                                     CSDD_CONFIG_SET_BUS_WIDTH,
                                     &busWidth, &size);
    CHECK_STATUS(status);

    if (cardMode == CSDD_ACCESS_MODE_HS_400_ES) {
        status = ReinitHostAndDevice();
        CHECK_STATUS(status);

        size = sizeof(busWidth);
        status = sdHostDriver->configure(sdHost, slotIndex,
                                          CSDD_CONFIG_SET_BUS_WIDTH,
                                          &busWidth, &size);
        CHECK_STATUS(status);
    }

    /* set card mode */
    printf("\tChange access mode to %s \n", access_mode_str[handler->init.access_mode]);
    status = sdHostDriver->configureAccessMode(sdHost, slotIndex,
                                                cardMode);
    CHECK_STATUS(status);

    switch (cardMode) {
    case CSDD_ACCESS_MODE_SDR50:
      dfisdr50Init();
      break;
    case CSDD_ACCESS_MODE_SDR104:
      dfisdr104Init();
      break;
    case CSDD_ACCESS_MODE_HS_SDR:
      dfisdrInit();
      break;
    case CSDD_ACCESS_MODE_DDR50:
      dfiddr50Init();
      break;
    case CSDD_ACCESS_MODE_HS_DDR:
      dfiddrInit();
      break;
    case CSDD_ACCESS_MODE_HS_200:
      dfihs200Init(111);
      break;
    case CSDD_ACCESS_MODE_HS_400:
      dfihs400Init();
      break;
    case CSDD_ACCESS_MODE_HS_400_ES:
      dfihs400esInit();
      break;
    case CSDD_ACCESS_MODE_SDR12:
    case CSDD_ACCESS_MODE_SDR25:
    case CSDD_ACCESS_MODE_MMC_LEGACY:
    default:
      break;
    }

    /* set new clock frequency */
    freq = clockFreqsKHz;
    size = sizeof(freq);
    status = sdHostDriver->configure(sdHost, slotIndex,
                                      CSDD_CONFIG_SET_CLK, &freq, &size);
    CHECK_STATUS(status);
    printf("\tChange clock frequency to %dKHz \n", freq);

    status = WriteReadCompare(slotIndex, sectorNumber, 1024);
    CHECK_STATUS(status);
    return 0;
}

static int sdmmc_irq_handler(int irq, void *args) {
  uint8_t *p = (uint8_t *)args;
  uintptr_t base = 0XC5104200;
  uint32_t SRS12 = 0;

  SRS12 = readl((void *)(base + 0x30));
  writel(SRS12, (void *)(base + 0x30));

  if (SRS12 & (1U << 6)) {
    printf("Card was inserted\n");
    *p |= 1U << 0;
  } else if (SRS12 & (1U << 7)) {
    printf("Card was removed\n");
    *p |= 1U << 1;
  }

  return 0;
}

#ifdef CONFIG_COMPILE_RTL

extern int __lds_print[];
static int soc_cmd(int cmd)
{
  volatile int *addr_ptr = (int *)__lds_print;
  *addr_ptr = cmd;
  // asm("sync.is");
  return 0;
}

static void sv_cmd_cfg(uint32_t cfg_data){
    uint32_t  _data = cfg_data << 16 | 0xa53c;
    printf("%s %s Card\n", cfg_data ? "Insert" : "Remove",
        init.mod_index == 0 ? "eMMC" :
        init.mod_index == 1 ? "SD" : "SDIO");
    soc_cmd(_data);
}
#endif

static int SDInsertionRemovalTest(void)
{
  uint32_t SRS14 = (1U << 7) | (1U << 6);
  volatile uint8_t card_status = 0; // Bit0: inserted, Bit1: removed;
  uintptr_t base = 0XC5104200;

  writel(SRS14, (void *)(base + 0x38));
  request_irq(C_SD1_IRQn, sdmmc_irq_handler, "sdmmc_irq_handler", (void *)&card_status);

  printf("Waiting for SD insert/remove...\n");

#if CONFIG_COMPILE_RTL && SD_DUMMY_INS_RM
  uint32_t SRS10 = 0;

  printf("Start dummy SD remove...\n");
  SRS10 = 0x80;
  writel(SRS10, (void *)(base + 0x28));
  while (!(card_status & (1U << 1)));

  printf("Start dummy SD insert...\n");
  SRS10 = 0xc0;
  writel(SRS10, (void *)(base + 0x28));
  while (!(card_status & (1U << 0)));

  return (card_status & 0x3) != 0x3;
#elif CONFIG_COMPILE_RTL
    sv_cmd_cfg(0x0);
    while (!(card_status & (1U << 1)));

    sv_cmd_cfg(CARD_MODEL_SD);
    while (!(card_status & (1U << 0)));

    return (card_status & 0x3) != 0x3;
#else
  while ((card_status & 0x3) != 0x3);
  return 0;
#endif
}

static uint32_t atoi(char *s) {
  uint32_t n = 0;
  for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

static void sdmmc_show_usage(void) {
  printf("Usage: sdmmc [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-p, --port\t\t0:mmc 1:sd1 2:sd2\n");
  printf("-a, --accessmode\t\taccess mode\n");
  printf("-d, --dma\t\tif use dma,should be 1\n");
  printf("-w, --buswidth\t\tbus width should be 1 or 4 or 8(mmc)\n");
  printf("-q, --quit\t\tcard plug-in or plug-out test\n");
  printf("-f, --freq\t\tclock speed\n");
  printf("-t, --type\t\ttest type\n");
}



int sdmmc_main(int argc, char *argv[]) {
  int c, grp = 0;
  uint32_t sector = 128U << (20 - 9);
  uint8_t status;
  char *grp_name;

  if (argc < 2) {
    sdmmc_show_usage();
    return -1;
  }

  memcpy(&init, &default_init, sizeof(default_init));
  force_3v3 = 0;

  while((c = getopt(argc, argv, "p:a:d:w:q:o:f:g:sr:vi")) != -1) {
    switch (c) {
    case 'p':
      init.mod_index = atoi(optarg);
      break;
    case 'a':
      init.access_mode = atoi(optarg);
      break;
    case 'd':
      init.dma_mode = atoi(optarg);
      break;
    case 'w':
      init.bus_width = atoi(optarg);
      break;
    case 'f':
      init.freq_khz = atoi(optarg);
      break;
    case 'g':
      grp = atoi(optarg);
      break;
    case 'r':
      sector = atoi(optarg);
      break;
    case 's':
      itcs_sdmmc_simple_init(1);
      goto exit;
    case 'v':
      force_3v3 = 1;
      break;
    case 'i':
      init.withInt = 1;
      break;
    case 'h':
    default:
      sdmmc_show_usage();
      goto exit;
    }
  }

#ifdef CONFIG_COMPILE_RTL
  if (init.mod_index == 0)
    sv_cmd_cfg(CARD_MODEL_EMMC);
  else
    sv_cmd_cfg(CARD_MODEL_SD);
#endif

  /* Initialize sdmmc.*/
  itcs_sdmmc_init(&handler, &init);
  if (handler == NULL) {
    printf("sdmmc initialize failed!\n");
    return -1;
  }

  writeBuffer = writeBuffer ?: malloc(1024);
  readBuffer = readBuffer ?: malloc(1024);
  config = handler->config;
  sdHostDriver = handler->sdHostDriver;
  sdHost = handler->sdHost;
  cb = handler->cb;

  switch (grp) {
  case 5:
    status = MmchighSpeedTest(sector);
    grp_name = NULL;
    break;
  case 3:
    status = DMATest(sector);
    grp_name = NULL;
    break;
  case 4:
    status = MmcBootTest(sector);
    grp_name = "MMC Boot Test";
    break;

  case 6:
    status = SDInsertionRemovalTest();
    grp_name = "SD Insertion/Removal Test";
    break;
  default:
    printf("Invalid test group\n");
    sdmmc_show_usage();
    goto exit;
  }

  test_result(status, grp_name);

#ifdef CONFIG_COMPILE_RTL
    sv_cmd_cfg(0x0);
#endif

exit:
  optind = 1;
  return 0;
}

static void sdmmc_init(void) { register_testbench("sdmmc", sdmmc_main, NULL); }

testbench_init(sdmmc_init);
