#ifndef _INIT_PARAMS_H_
#define _INIT_PARAMS_H_

#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <common.h>

#define SYS_CLK_START_FREQ_kHZ  200000
#define XSPI_CLK_START_FREQ_kHZ 50000
#define INIT_RB_VALID_TIME      0x00000000

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
#define INIT_PHY_DQ_TIMING_REG      0x80000101
#define INIT_PHY_DQS_TIMING_REG     0x00300404
#define INIT_PHY_GATE_LPBK_CTRL_REG 0x00180030
#define INIT_PHY_DLL_SLAVE_CTRL_REG 0x0000357f
#define INIT_PHY_DLL_MASTER_CTRL_REG    0x00800004 // phy reg 0x200c, asic only
#else
#define INIT_PHY_DQ_TIMING_REG      0x80000102 // phy reg 0x2000
#define INIT_PHY_DQS_TIMING_REG     0x00300404 // phy reg 0x2004
#define INIT_PHY_GATE_LPBK_CTRL_REG 0x00200030 // phy reg 0x2008
#define INIT_PHY_DLL_SLAVE_CTRL_REG 0x00003f3f // phy reg 0x2010
#define INIT_PHY_DLL_MASTER_CTRL_REG    0x0030004a // phy reg 0x200c, asic only
#endif


#define INIT_DQS_LAST_DATA_DROP_EN      0
#define INIT_SDR_EDGE_ACTIVE            0
#define INIT_WP_ENABLE                  0
#define INIT_RST_DQ3_ENABLE             0
#define INIT_SW_CTRLED_HW_RST_OPTION    0
#define DISCOVERY_INHIBIT               1
#define DISCOVERY_NUM_LINES             0
#define DISCOVERY_BANK                  0
#define DISCOVERY_CMD_TYPE              0
#define DISCOVERY_EXTOP_EN              0
#define DISCOVERY_EXTOP_VAL             0
#define DISCOVERY_DUMMY_CNT             0
#define DISCOVERY_ABNUM                 0
#define DISCOVERY_SEQ_CRC_EN            0
#define DISCOVERY_SEQ_CRC_VARIANT       0
#define DISCOVERY_SEQ_CRC_OE            0
#define DISCOVERY_SEQ_CRC_CHUNK_SIZE    0
#define DISCOVERY_SEQ_CRC_UAL_CHUNK_EN  0
#define DISCOVERY_SEQ_CRC_UAL_CHUNK_CHK 0
#define BOOT_EN                         0

#define sd_printf                       printf
#define sv_malloc                       malloc
#define sv_free                         free
#define IOWR_32(register_address, data) writel(data, register_address)
#define IORD_32(register_address)       readl(register_address)
#define sd_delay                        udelay

#define QSPI_SDMA_BASE 0x38000000 // b2m3 axi slave addr
#define OSPI_SDMA_BASE 0x30000000 // b2m0 axi slave addr

#define OSPI_REG_BASE 0xC5000000
#define QSPI_REG_BASE 0xC5300000

// GPIO READ
#define OSPI_TB_GPIO_SEL_REG                     (OSPI_REG_BASE + 0x8000)
#define OSPI_TB_GPIO_PHY_EXT_REG                 (OSPI_REG_BASE + 0x8008)
#define OSPI_TB_GPIO_BOOT_REG                    (OSPI_REG_BASE + 0x80a0)
#define OSPI_TB_GPIO_DISCOVERY_REG               (OSPI_REG_BASE + 0x80a4)
#define OSPI_TB_GPIO_INIT_RB_REG                 (OSPI_REG_BASE + 0x80a8)
#define OSPI_TB_GPIO_INIT_PHY_DQ_REG             (OSPI_REG_BASE + 0x80ac)
#define OSPI_TB_GPIO_INIT_PHY_DQS_REG            (OSPI_REG_BASE + 0x80b0)
#define OSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG      (OSPI_REG_BASE + 0x80b4)
#define OSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG     (OSPI_REG_BASE + 0x80b8)
#define OSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG      (OSPI_REG_BASE + 0x80bc)
#define OSPI_TB_GPIO_INIT_REG                    (OSPI_REG_BASE + 0x80c0)
#define OSPI_TB_GPIO_CTRL_REG                    (OSPI_REG_BASE + 0x80c4)


#define QSPI_TB_GPIO_BOOT_REG                    (QSPI_REG_BASE + 0x8000)
#define QSPI_TB_GPIO_DISCOVERY_REG               (QSPI_REG_BASE + 0x8004)
#define QSPI_TB_GPIO_INIT_RB_REG                 (QSPI_REG_BASE + 0x8008)
#define QSPI_TB_GPIO_INIT_PHY_DQ_REG             (QSPI_REG_BASE + 0x800c)
#define QSPI_TB_GPIO_INIT_PHY_DQS_REG            (QSPI_REG_BASE + 0x8010)
#define QSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG      (QSPI_REG_BASE + 0x8014)
#define QSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG     (QSPI_REG_BASE + 0x8018)
#define QSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG      (QSPI_REG_BASE + 0x801c)
#define QSPI_TB_GPIO_INIT_REG                    (QSPI_REG_BASE + 0x8020)
#define QSPI_TB_GPIO_CTRL_REG                    (QSPI_REG_BASE + 0x8024)

#define TB_GPIO_INIT_COMP                   8    /* XSPI OUTPUT: init_comp */
#define TB_GPIO_INIT_FAIL                   12   /* XSPI OUTPUT: init_fail */
#define TB_GPIO_CTRL_BUSY                   0    /* XSPI OUTPUT: ctrl_busy */
#define TB_GPIO_BOOT_EN                     0    /* XSPI INPUT: boot_en */
#define TB_GPIO_BOOT_COMP                   4    /* XSPI OUTPUT: boot_comp */
#define TB_GPIO_BOOT_ERROR                  8    /* XSPI OUTPUT: boot_error */
#define TB_GPIO_PHY_EXT_COMP                12   /* XSPI OUTPUT: dfi comp */


#define OSPI_R_CMD_STATUS_PTR (OSPI_REG_BASE + 0x0040)
#define QSPI_R_CMD_STATUS_PTR (QSPI_REG_BASE + 0x0040)

#define F_THRD_STATUS_SEL     0

#define OSPI_R_CMD_STATUS (OSPI_REG_BASE + 0x0044)
#define QSPI_R_CMD_STATUS (QSPI_REG_BASE + 0x0044)
#define F_CMD_STATUS      0

#define OSPI_R_CTRL_STATUS (OSPI_REG_BASE + 0x0100)
#define QSPI_R_CTRL_STATUS (QSPI_REG_BASE + 0x0100)

#define F_INIT_COMP        16
#define F_INIT_FAIL        8
#define F_CTRL_BUSY        7
#define F_DISCOVERY_BUSY   6
#define F_GCMD_ENG_MC_BUSY 4
#define F_GCMD_ENG_BUSY    3
#define F_ACMD_ENG_BUSY    2
#define F_MDMA_BUSY        1
#define F_SDMA_BUSY        0

int cdns_xspi_before_driver_init(int port);
#endif /* _INIT_PARAMS_H_ */
