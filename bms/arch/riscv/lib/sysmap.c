#include <common.h>
#include <core_rv32.h>
#include <sysmap.h>

// set e906 ddr 512M for SO from 0x6000000
sysmap_region_t regions[] = {
#ifdef CONFIG_TB_RUN_IRAM
    {0x140a0000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x14100000, SYSMAP_SYSMAPCFG_B_Msk},
    {0x14240000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
#else
    {0x0c000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x18000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
#endif
    {0x40000000, SYSMAP_SYSMAPCFG_SO_Msk},
    {0x40080000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
    {0x80000000, SYSMAP_SYSMAPCFG_B_Msk},
    {0xc0000000, SYSMAP_SYSMAPCFG_SO_Msk},
    {0xfffff000, SYSMAP_SYSMAPCFG_SO_Msk}};

void systemmap_config(void) {
  for (int i = 0; i < ARRAY_SIZE(regions); i++) {
    if (i >= MAX_REGIONS)
      break;

    csi_sysmap_config_region(i, regions[i].end, regions[i].attr);
  }
}
