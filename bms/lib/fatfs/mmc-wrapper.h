#pragma once

#include <sdmmc.h>

#include "ff.h"

static inline int MMC_disk_status(int devn)
{
    return 0;
}

static inline int MMC_disk_initialize(int devn)
{
    return itcs_sdmmc_simple_init(CONFIG_FATFS_MMC_IF);
}

static inline int MMC_disk_read(int devn, BYTE *buff, LBA_t sector, UINT count)
{

    return itcs_sdmmc_read(CONFIG_FATFS_MMC_IF, sector, count << 9, buff);
}
