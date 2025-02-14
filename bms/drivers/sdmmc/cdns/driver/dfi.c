/******************************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 * Combo PHY configuration functions
 *****************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "sdio_dfi.h"
#include "csdd_if.h"
#include "csdd_structs_if.h"
#include "dfi.h"

static CSDD_SDIO_Host *sdHost;

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
#define FPGA_PHY      1   //
#else
#define FPGA_PHY      0
#endif

#define SD_REG_HRS4  (&sdHost->RegOffset->HRS.HRS04)
#define SD_REG_HRS5  (&sdHost->RegOffset->HRS.HRS05)
#define SD_REG_HRS7  (&sdHost->RegOffset->HRS.HRS07)
#define SD_REG_HRS9  (&sdHost->RegOffset->HRS.HRS09)
#define SD_REG_HRS10 (&sdHost->RegOffset->HRS.HRS10)
#define SD_REG_HRS16 (&sdHost->RegOffset->HRS.HRS16)


static uint32_t dfiConfigure(void)
{
    if (sdHost->hostCtrlVer < 6) {
        return 0;
    }

    return CSDD_CPhyDllReset(sdHost, true);
}

static uint32_t dfiRelease(void)
{
    if (sdHost->hostCtrlVer < 6) {
        return 0;
    }

    return CSDD_CPhyDllReset(sdHost, false);
}


static uint32_t readPhyReg(uint32_t address)
{
    CPS_REG_WRITE(SD_REG_HRS4, address);
    return CPS_REG_READ(SD_REG_HRS5);
}

static void writePhyReg(uint32_t address, uint32_t value)
{
    CPS_REG_WRITE(SD_REG_HRS4, address);
    CPS_REG_WRITE(SD_REG_HRS5, value);
}

uint32_t dfiInitDriver(CSDD_SDIO_Host *pD)
{
    sdHost = pD;
    return sdHost ? CDN_EOK : CDN_EINVAL;
}

uint32_t dfiInit(void) 
{
    uint32_t status = CDN_EOK;

    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (1 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                (0 << READ_DQS_CMD_DELAY)
                | (0 << CLK_WRDQS_DELAY)
                | (0 <<  CLK_WR_DELAY)
                | (0 << READ_DQS_DELAY)
                );
    CPS_REG_WRITE(SD_REG_HRS4, PHY_DLL_CTRL_REG);
    temp = CPS_REG_READ(SD_REG_HRS5);
    temp &= ~(0x3f << 4); // phony_dqs_timing=0
    CPS_REG_WRITE(SD_REG_HRS5, temp);
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (1 << 3)
                | (1 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
                | (1 << 16));
    CPS_REG_WRITE(SD_REG_HRS16,
                (0 << 28)
                | (0 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (1 << 8)
                | (0 << 4)
                | (1 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                (9 << 16)
                | (0 << 0));

    return status;
}

uint32_t dfisdr104Init(void) {
    uint32_t status = CDN_EOK;
    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (0 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                (111 << READ_DQS_CMD_DELAY)
                | (77 << CLK_WRDQS_DELAY)
                | (77 <<  CLK_WR_DELAY)
                | (111 << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (1 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (0 << 3)
                | (0 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
                | (8 << 16));
    CPS_REG_WRITE(SD_REG_HRS16,
                (0 << 28)
                | (0 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (1 << 8)
                | (0 << 4)
                | (1 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                (9 << 16)
                | (0 << 0));
    return status;
}

uint32_t dfisdr50Init(void)
{
    uint32_t status = CDN_EOK;

    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                    (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                    (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                                & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (1 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                    (0 << READ_DQS_CMD_DELAY)
                | (0 << CLK_WRDQS_DELAY)
                | (0 <<  CLK_WR_DELAY)
                | (0 << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp  
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (1 << 3)
                | (1 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
                | (5 << 16));
    CPS_REG_WRITE(SD_REG_HRS16,
                    (0 << 28)
                | (0 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (0 << 8)
                | (0 << 4)
                | (0 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                    (8 << 16)
                | (0 << 0));
    return status;
}

uint32_t dfisdrInit(void)
{
    uint32_t status = CDN_EOK;

    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                    (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                    (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                                & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (1 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                    (0 << READ_DQS_CMD_DELAY)
                | (0 << CLK_WRDQS_DELAY)
                | (0 <<  CLK_WR_DELAY)
                | (0 << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (1 << 3)
                | (1 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
                | (2 << 16));
    CPS_REG_WRITE(SD_REG_HRS16,
                    (0 << 28)
                | (0 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (1 << 8)
                | (0 << 4)
                | (1 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                    (9 << 16)
                | (0 << 0));

    return status;
}

uint32_t dfiddrInit(void)
{
    uint32_t status = CDN_EOK;
    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (1 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                (0 << READ_DQS_CMD_DELAY)
                | (0 << CLK_WRDQS_DELAY)
                | (0 <<  CLK_WR_DELAY)
                | (0 << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (1 << 3)
                | (1 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
    #if (FPGA_PHY == 0)
                | (2 << 16)
    #else
                | (3 << 16)
    #endif
                );
    CPS_REG_WRITE(SD_REG_HRS16,
                (1 << 28)
                | (1 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (0 << 8)
                | (0 << 4)
                | (1 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                (8 << 16)
                | (0 << 0));

    return status;
}

uint32_t dfiddr50Init(void)
{
    uint32_t status = CDN_EOK;
    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (1 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                (0 << READ_DQS_CMD_DELAY)
                | (0 << CLK_WRDQS_DELAY)
                | (0 <<  CLK_WR_DELAY)
                | (0 << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (1 << 3)
                | (1 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
    #if (FPGA_PHY == 0)
                | (2 << 16)
    #else
                | (3 << 16)
    #endif
                );
    CPS_REG_WRITE(SD_REG_HRS16,
                (1 << 28)
                | (1 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (0 << 8)
                | (0 << 4)
                | (0 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                (8 << 16)
                | (0 << 0));

    return status;
}

uint32_t dfihs200Init(uint32_t tune_val)
{
    uint32_t status = CDN_EOK;
    volatile uint32_t _tune_val;

    _tune_val = 0xff & ((tune_val<<8)/40); // N * 256 / 40 
    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (1 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (0 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                (_tune_val << READ_DQS_CMD_DELAY)
                | (77 << CLK_WRDQS_DELAY)
                | (77 <<  CLK_WR_DELAY)
                | (_tune_val << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (0 << 3)
                | (0 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
                | (8 << 16));
    CPS_REG_WRITE(SD_REG_HRS16,
                (0 << 28)
                | (0 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (1 << 8)
                | (0 << 4)
                | (1 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                (9 << 16)
                | (0 << 0));
    return status;
}

uint32_t dfihs400Init(void)
{
    uint32_t status = CDN_EOK;
    uint32_t temp;
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    temp = CPS_REG_READ(SD_REG_HRS5) & 0xFF000000;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5, 
                (0 << EXT_LPBK_DQS) 
                | (1 << LPBK_DQS) 
                | (0 << PHONY_DQS) 
                | (1 << PHONY_DQS_CMD)); 

    CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
                | (0 << SW_HALF_CYCLE_SHIFT)
                | (52 << RD_DEL_SEL)
    #if (FPGA_PHY == 0)
                | (1 << UNDERRUN_SUPPRESS)
    #endif
                | (1 << GATE_CFG_ALWAYS_ON)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
                | (0 << DLL_BYPASS_MODE)
                | (2 << 20)
                | (4 <<  DLL_START_POINT)
                );
    CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
    CPS_REG_WRITE(SD_REG_HRS5,
                temp
                | (77 << CLK_WRDQS_DELAY)
                | (75 <<  CLK_WR_DELAY)
                | (64 << READ_DQS_DELAY)
                );
    dfiRelease();
    temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
    writePhyReg(PHY_DQ_TIMING_REG, temp
    #if (FPGA_PHY == 0)
                | (0 << 31)
                | (0 << 27)
                | (0 << 24)
                | (1 << 0)
    #else
                | (0 << 31)
                | (1 << 27)
                | (0 << 24)
                | (2 << 0)
    #endif
                );
    temp=CPS_REG_READ(SD_REG_HRS9);
    temp&=0xFFFE7FF3;
    CPS_REG_WRITE(SD_REG_HRS9,temp
                | (1 << 16)
                | (1 << 15)
                | (0 << 3)
                | (0 << 2));
    temp=CPS_REG_READ(SD_REG_HRS10);
    temp&=0xFFF0FFFF;
    CPS_REG_WRITE(SD_REG_HRS10,temp
    #if (FPGA_PHY == 0)
                | (8 << 16)
    #else
                | (9 << 16)
    #endif
    );
    CPS_REG_WRITE(SD_REG_HRS16,
                (1 << 28)
                | (1 << 24)
                | (0 << 20)
                | (0 << 16)
                | (0 << 12)
                | (0 << 8)
                | (0 << 4)
                | (1 << 0));
    CPS_REG_WRITE(SD_REG_HRS7,
                (8 << 16)
                | (0 << 0));
    return status;
}

uint32_t dfihs400esInit(void)
{
    uint32_t status = CDN_EOK;
    uint32_t temp;
    dfiConfigure();
    CPS_REG_WRITE(SD_REG_HRS4,
                PHY_DQS_TIMING_REG); // select phy_dqs_timing_reg - enable phony
                                     // dqs for card init.
    CPS_REG_WRITE(SD_REG_HRS5,
#if (FPGA_PHY == 0)
                (0 << EXT_LPBK_DQS)
#else
                (1 << EXT_LPBK_DQS)
#endif
                    | (1 << LPBK_DQS) | (0 << PHONY_DQS) |
                    (0 << PHONY_DQS_CMD)); 

  CPS_REG_WRITE(SD_REG_HRS4, PHY_GATE_LPBK_CTRL_REG);
  CPS_REG_WRITE(SD_REG_HRS5, 
                (1 << SYNC_METHOD)
              | (0 << SW_HALF_CYCLE_SHIFT)
              | (52 << RD_DEL_SEL)
#if (FPGA_PHY == 0)
              | (1 << UNDERRUN_SUPPRESS)
#endif
              | (1 << GATE_CFG_ALWAYS_ON)
              );
  CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_MASTER_CTRL_REG);
  CPS_REG_WRITE(SD_REG_HRS5, (CPS_REG_READ(SD_REG_HRS5)
                            & ~((0x1<<23) | (0x7<<20) | (0xff<<0)))
              | (0 << DLL_BYPASS_MODE)
              | (2 << 20)
              | (4 <<  DLL_START_POINT)
              );
  CPS_REG_WRITE(SD_REG_HRS4,PHY_DLL_SLAVE_CTRL_REG);
  CPS_REG_WRITE(SD_REG_HRS5,
                (111 << READ_DQS_CMD_DELAY)
              | (77 << CLK_WRDQS_DELAY)
              | (75 <<  CLK_WR_DELAY)
              | (111 << READ_DQS_DELAY)
              );
  dfiRelease();
  temp = readPhyReg(PHY_DQ_TIMING_REG) & 0x00FFFFF8;
  writePhyReg(PHY_DQ_TIMING_REG, temp
#if (FPGA_PHY == 0)
              | (0 << 31)
              | (0 << 27)
              | (0 << 24)
              | (1 << 0)
#else
              | (0 << 31)
              | (1 << 27)
              | (0 << 24)
              | (2 << 0)
#endif
              );
  temp=CPS_REG_READ(SD_REG_HRS9);
  temp&=0xFFFE7FF3;
  CPS_REG_WRITE(SD_REG_HRS9,temp
              | (1 << 16)
              | (1 << 15)
              | (0 << 3)
              | (0 << 2));
  temp=CPS_REG_READ(SD_REG_HRS10);
  temp&=0xFFF0FFFF;
  CPS_REG_WRITE(SD_REG_HRS10,temp
#if (FPGA_PHY == 0)
              | (8 << 16)
#else
              | (9 << 16)
#endif
  );
  CPS_REG_WRITE(SD_REG_HRS16,
                (1 << 28)
              | (1 << 24)
              | (0 << 20)
              | (0 << 16)
              | (0 << 12)
              | (0 << 8)
              | (0 << 4)
              | (1 << 0));
  CPS_REG_WRITE(SD_REG_HRS7,
                (8 << 16)
              | (0 << 0));
    return status;
}
