/******************************************************************************
 * Copyright (C) 2013-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio_sd4_host.h
 * Vendor specific registers definitions for SD Host 4 controller
 *****************************************************************************/

#ifndef SDIO_SD4_HOST_H
#define SDIO_SD4_HOST_H

#ifndef SDIO_CFG_HOST_VER
    #error "SDIO_CFG_HOST_VER should be defined explicitly"
#endif


//-----------------------------------------------------------------------------
/// @name Host Register Set Organization
//-----------------------------------------------------------------------------
//@{
/// general information register
#define SDIO_REG_HRS0       0x00U
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name General information register (HRS0) - masks
//-----------------------------------------------------------------------------
//@{
/** slot X is accesable */
static inline uint32_t HRS0_ACCESABLE_SLOT(uint32_t x)
{
    uint32_t result = 0U;
    const uint32_t shift = SD4HC__HRS__HRS00__SAV_SHIFT + x;
    if (shift < 32U) {
        result = (uint32_t)(1UL << shift);
    }
    return (result);
}
/// 4 slots are accesible in the SDIO host
#define HRS0_4_ACCESABLE_SLOTS      (0x1UL << 19)
/// 3 slots are accesible in the SDIO host
#define HRS0_3_ACCESABLE_SLOTS      (0x1UL << 18)
/// 2 slots are accesible in the SDIO host
#define HRS0_2_ACCESABLE_SLOTS      (0x1UL << 17)
/// 1 slots are accesible in the SDIO host
#define HRS0_1_ACCESABLE_SLOT       (0x1UL << 16)
/// Reset all internal registers including SRS RAM.
// The card detection unit is reset also.
#define HRS0_SOFTWARE_RESET         SD4HC__HRS__HRS00__SWR_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name DMA settings register (HRS2) - values
//-----------------------------------------------------------------------------
//@{
//  Burst Length                               SD4HC__HRS__HRS02__PBL_MASK
/// set 2048 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_2048    0xC
/// set 1024 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_1024    0xB
/// set 512 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_512     0xA
/// set 256 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_256     0x9
/// set 128 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_128     0x8
/// set 64 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_64      0x7
/// set 32 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_32      0x6
/// set 16 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_16      0x5
/// set 8 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_8       0x4
/// set 4 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_4       0x3
/// set 2 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_2       0x2
/// set 1 words as a maximum that can be transfered within one DMA transaction
#define HRS2_PROGRAMMABLE_BURST_LEN_1       0x1
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name PHY settings register (HRS4) - masks and macros
//-----------------------------------------------------------------------------
//@{
#define SD4HC__HRS__HRS04__UIS_WDATA_SHIFT 									  8U
#define SD4HC__HRS__HRS04__UIS_RDATA_MASK                            0x00FF0000U
#define SD4HC__HRS__HRS04__UIS_RDATA_SHIFT                                   16U
#define SD4HC__HRS__HRS04__UIS_ACK_MASK                              0x04000000U
#define SD4HC__HRS__HRS04__UIS_WR_MASK                               0x01000000U
#define SD4HC__HRS__HRS04__UIS_RD_MASK                               0x02000000U

/// PHY request acknowledge
#define HRS_PHY_ACKNOWLEDGE_REQUEST                     SD4HC__HRS__HRS04__UIS_ACK_MASK
/// make read request
#define HRS_PHY_READ_REQUEST                            SD4HC__HRS__HRS04__UIS_RD_MASK
/// make write request
#define HRS_PHY_WRITE_REQUEST                           SD4HC__HRS__HRS04__UIS_WR_MASK

/// set PHY register data
static inline uint32_t HRS_PHY_UIS_WDATA_SET(uint32_t wdata)
{
    return (wdata << SD4HC__HRS__HRS04__UIS_WDATA_SHIFT);

}
/// get PHY register data
static inline uint32_t HRS_PHY_UIS_RDATA_GET(uint32_t hrs04)
{
    return ((hrs04 & SD4HC__HRS__HRS04__UIS_RDATA_MASK) >> SD4HC__HRS__HRS04__UIS_RDATA_SHIFT);

 }

/// set PHY register address
static inline uint32_t HRS_PHY_UIS_ADDR_SET(uint32_t uisAddr)
{
    return (uisAddr);
}
//@}
//-----------------------------------------------------------------------------

/// @name AXI error response (HRS3) - masks and macros
//-----------------------------------------------------------------------------
//@{
#define HRS3_AER_ALL                                    (HRS3_AER_BS | \
                                                         HRS3_AER_BD | \
                                                         HRS3_AER_RS | \
                                                         HRS3_AER_RD)
// AXI ERROR Response B channel: SLVERR
#define HRS3_AER_BS                                     3U
/// AER_BD - AXI ERROR Response B channel
#define HRS3_AER_BD                                     2U
/// AXI ERROR Response R channel
#define HRS3_AER_RS                                     1U
/// AXI ERROR Response R channel
#define HRS3_AER_RD                                     0U
// macro sets interrupt signal enable
static inline uint32_t HRS3_SET_INT_SIGNAL_EN(uint32_t val)
{
    return ((val & 0xFU) << 16);
}
// macro sets interrupt status enable
static inline uint32_t HRS3_SET_INT_STATUS_EN(uint32_t val)
{
    return ((val & 0xFU) << 8);
}
// macro set interrupt status
static inline uint32_t HRS3_SET_INT_STATUS(uint32_t val)
{
    return ((val & 0xFU) << 0);
}
// macro set interrupt status
static inline uint32_t HRS3_GET_INT_STATUS(uint32_t val)
{
    return (val & 0xFU);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name PHY Delay Value Registers addressing
//-----------------------------------------------------------------------------
//@{
/// PHY register addresses using
#define UIS_ADDR_HIGH_SPEED                 0x00
#define UIS_ADDR_DEFAULT_SPEED              0x01
#define UIS_ADDR_UHSI_SDR12                 0x02
#define UIS_ADDR_UHSI_SDR25                 0x03
#define UIS_ADDR_UHSI_SDR50                 0x04
#define UIS_ADDR_UHSI_DDR50                 0x05
#define UIS_ADDR_MMC_LEGACY                 0x06
#define UIS_ADDR_MMC_SDR                    0x07
#define UIS_ADDR_MMC_DDR                    0x08
#define UIS_ADDR_SDCLK                      0x0B
#define UIS_ADDR_HS_SDCLK                   0x0C
#define UIS_ADDR_DAT_STROBE                 0x0D
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name (HRS6) - masks and macros
//-----------------------------------------------------------------------------
//@{
#define HRS6_EMMC_MODE_MASK             SD4HC__HRS__HRS06__EMM_MASK
#define HRS6_EMMC_MODE_SDCARD           (0x0U << 0)
#define HRS6_EMMC_MODE_SDR              (0x2U << 0)
#define HRS6_EMMC_MODE_DDR              (0x3U << 0)
#define HRS6_EMMC_MODE_HS200            (0x4U << 0)
#define HRS6_EMMC_MODE_HS400            (0x5U << 0)
#define HRS6_EMMC_MODE_HS400_ES         (0x6U << 0)
#define HRS6_EMMC_MODE_LEGACY           (0x7U << 0)

#define HRS6_EMMC_TUNE_VALUE_MASK       (0x3FuL << 8)
#define HRS6_EMMC_TUNE_SET_VALUE(val)   ((uint32_t)(val) << 8)
#define HRS6_EMMC_TUNE_REQUEST          (1uL << 15)

//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name (HRS9) - masks and macros
//-----------------------------------------------------------------------------
//@{
#define HRS09_PHY_INT_COMPLETE SD4HC__HRS__HRS09__PHY_INIT_COMPLETE_MASK

//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name (HRS31) - masks and macros
//-----------------------------------------------------------------------------
//@{
static inline uint8_t HRS31_GET_MAJOR(uint32_t val)
{
	return (uint8_t)((val >> 8U) & 0xFU);
}

//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name (HRS36) - masks and macros
//-----------------------------------------------------------------------------
//@{
#define HRS36_BOOT_ERROR_DATA_END_BIT   SD4HC__HRS__HRS36__BOOT_EDE_MASK
#define HRS36_BOOT_ERROR_DATA_CRC       SD4HC__HRS__HRS36__BOOT_EDC_MASK
#define HRS36_BOOT_ERROR_DATA_TIMEOUT   SD4HC__HRS__HRS36__BOOT_EDT_MASK
#define HRS36_BOOT_ERROR_INVALID_ACK    SD4HC__HRS__HRS36__BOOT_EAT_MASK
#define HRS36_BOOT_ERROR_ACK_TIMEOUT    SD4HC__HRS__HRS36__BOOT_EAT_MASK
#define HRS36_BOOT_ACT                  SD4HC__HRS__HRS36__BOOT_ACT_MASK

#define HRS36_BOOT_ERROR \
    (HRS36_BOOT_ERROR_DATA_END_BIT \
     | HRS36_BOOT_ERROR_DATA_CRC \
     | HRS36_BOOT_ERROR_DATA_TIMEOUT \
     | HRS36_BOOT_ERROR_INVALID_ACK \
    )
//@}
//-----------------------------------------------------------------------------

struct PhyDelayAddresses {
    uint8_t address;
    CSDD_PhyDelay phyDelayType;
};

static const struct PhyDelayAddresses phyDelayAddr[] = {
    { UIS_ADDR_DEFAULT_SPEED, CSDD_PHY_DELAY_INPUT_DEFAULT_SPEED},
    { UIS_ADDR_HIGH_SPEED, CSDD_PHY_DELAY_INPUT_HIGH_SPEED},
    { UIS_ADDR_UHSI_SDR12, CSDD_PHY_DELAY_INPUT_SDR12},
    { UIS_ADDR_UHSI_SDR25, CSDD_PHY_DELAY_INPUT_SDR25},
    { UIS_ADDR_UHSI_SDR50, CSDD_PHY_DELAY_INPUT_SDR50},
    { UIS_ADDR_UHSI_DDR50, CSDD_PHY_DELAY_INPUT_DDR50},
    { UIS_ADDR_MMC_LEGACY, CSDD_PHY_DELAY_INPUT_MMC_LEGACY},
    { UIS_ADDR_MMC_SDR, CSDD_PHY_DELAY_INPUT_MMC_SDR},
    { UIS_ADDR_MMC_DDR, CSDD_PHY_DELAY_INPUT_MMC_DDR},
    { UIS_ADDR_SDCLK, CSDD_PHY_DELAY_DLL_SDCLK},
    { UIS_ADDR_HS_SDCLK, CSDD_PHY_DELAY_DLL_HS_SDCLK},
    { UIS_ADDR_DAT_STROBE, CSDD_PHY_DELAY_DLL_DAT_STROBE},
};

void SDIOHost_AxiErrorInit(CSDD_SDIO_Host *pSdioHost);
void SDIOHost_AxiErrorIntSignalCfg(CSDD_SDIO_Host *pSdioHost, uint8_t enable);
void SDIOHost_AxiErrorGetStatus(CSDD_SDIO_Host *pSdioHost, uint8_t* status);
void SDIOHost_AxiErrorClearStatus(CSDD_SDIO_Host *pSdioHost, uint8_t status);

#endif
