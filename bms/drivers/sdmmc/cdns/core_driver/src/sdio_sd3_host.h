/*******************************************************************
* copyright (C) 2014-2019 Cadence Design Systems, Inc.
* All rights reserved worldwide.
*******************************************************************
* sdio_sd3_host.h
* Vendor specific registers definitions for SD Host 3 controller
*******************************************************************/

#ifndef SDIO_SD3_HOST_H
#define SDIO_SD3_HOST_H

//-----------------------------------------------------------------------------
/// @name Host Register Set Organization
//-----------------------------------------------------------------------------
/// general information register
#define SDIO_REG_HRS0       0x00
/// initialization setting register
#define SDIO_REG_HRS1       0x04
/// DMA setting register
#define SDIO_REG_HRS2       0x08
/// HWInit SRS16 configuration for slot #0
#define SDIO_REG_HRS4       0x10
/// HWInit SRS17 configuration for slot #0
#define SDIO_REG_HRS5       0x14
/// HWInit SRS18 configuration for slot #0
#define SDIO_REG_HRS6       0x18
/// HWInit SRS16 configuration for slot #1
#define SDIO_REG_HRS8       0x20
/// HWInit SRS17 configuration for slot #1
#define SDIO_REG_HRS9       0x24
/// HWInit SRS18 configuration for slot #1
#define SDIO_REG_HRS10      0x28
/// HWInit SRS16 configuration for slot #2
#define SDIO_REG_HRS12      0x30
/// HWInit SRS17 configuration for slot #2
#define SDIO_REG_HRS13      0x34
/// HWInit SRS18 configuration for slot #2
#define SDIO_REG_HRS14      0x38
/// HWInit SRS16 configuration for slot #3
#define SDIO_REG_HRS16      0x40
/// HWInit SRS17 configuration for slot #3
#define SDIO_REG_HRS17      0x44
/// HWInit SRS18 configuration for slot #3
#define SDIO_REG_HRS18      0x48
/// CPRM information/settings register
#define SDIO_REG_HRS20      0x50
/// CPRM CBC settings register
#define SDIO_REG_HRS21      0x54
/// HWInit SRS24 preset for slot #0
#define SDIO_REG_HRS24      0x60
/// HWInit SRS25 preset for slot #0
#define SDIO_REG_HRS25      0x64
/// HWInit SRS26 preset for slot #0
#define SDIO_REG_HRS26      0x68
/// HWInit SRS27 preset for slot #0
#define SDIO_REG_HRS27      0x6C
/// HWInit SRS24 preset for slot #1
#define SDIO_REG_HRS28      0x70
/// HWInit SRS25 preset for slot #1
#define SDIO_REG_HRS29      0x74
/// HWInit SRS26 preset for slot #1
#define SDIO_REG_HRS30      0x78
/// HWInit SRS27 preset for slot #1
#define SDIO_REG_HRS31      0x7C
/// HWInit SRS24 preset for slot #2
#define SDIO_REG_HRS32      0x80
/// HWInit SRS25 preset for slot #2
#define SDIO_REG_HRS33      0x84
/// HWInit SRS26 preset for slot #2
#define SDIO_REG_HRS34      0x88
/// HWInit SRS27 preset for slot #2
#define SDIO_REG_HRS35      0x8C
/// HWInit SRS24 preset for slot #3
#define SDIO_REG_HRS36      0x90
/// HWInit SRS25 preset for slot #3
#define SDIO_REG_HRS37      0x94
/// HWInit SRS26 preset for slot #3
#define SDIO_REG_HRS38      0x98
/// HWInit SRS27 preset for slot #3
#define SDIO_REG_HRS39      0x9C
///HWInit SRS56 preset for slot #0
#define SDIO_REG_HRS40      0xA0
///HWInit SRS56 preset for slot #1
#define SDIO_REG_HRS41      0xA4
///HWInit SRS56 preset for slot #2
#define SDIO_REG_HRS42      0xA8
///HWInit SRS56 preset for slot #3
#define SDIO_REG_HRS43      0xAC
/// UHS-I PHY Settings for slot #0
#define SDIO_REG_HRS44      0xB0
/// UHS-I PHY Settings for slot #1
#define SDIO_REG_HRS45      0xB4
/// UHS-I PHY Settings for slot #2
#define SDIO_REG_HRS46      0xB8
/// UHS-I PHY Settings for slot #3
#define SDIO_REG_HRS47      0xBC
/// UHS-I PHY BIST Control/Status for slot #0
#define SDIO_REG_HRS48      0xC0
/// UHS-I PHY BIST Control/Status for slot #1
#define SDIO_REG_HRS49      0xC4
/// UHS-I PHY BIST Control/Status for slot #2
#define SDIO_REG_HRS50      0xC8
/// UHS-I PHY BIST Control/Status for slot #3
#define SDIO_REG_HRS51      0xCC
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name General information register (HRS0) - masks
//-----------------------------------------------------------------------------
//@{
/// DDR mode mask
#define HRS0_DDR_MASK               (0xFUL << 28)
/// Set DDR mode for specific slot
#define HRS0_DDR(SlotNr)            (1UL << (28U + SlotNr))
/** slot X is accesable */
#define HRS0_ACCESABLE_SLOT(X)      (1UL << (16U + X))
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
#define HRS0_SOFTWARE_RESET         (1UL << 0)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name PHY settings register (HRS44 - HRS47) - masks and macros
//-----------------------------------------------------------------------------
//@{
/// PHY request acknowledge
#define HRS_PHY_ACKNOWLEDGE_REQUEST                (1UL << 26)
/// make read request
#define HRS_PHY_READ_REQUEST                       (1UL << 25)
/// make write request
#define HRS_PHY_WRITE_REQUEST                      (1UL << 24)
/// set PHY register data
#define HRS_PHY_UIS_WDATA_SET(WDATA)               ((uint32_t)WDATA << 8)
/// get PHY register data
#define HRS_PHY_UIS_RDATA_GET(HRS04)               ((HRS04 >> 16) & 0xFF)
/// set PHY register address
#define HRS_PHY_UIS_ADDR_SET(UIS_ADDR)             (UIS_ADDR)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name PHY Delay Value Registers addressing
//-----------------------------------------------------------------------------
//@{
/// PHY register addresses using
#define UIS_ADDR_DEFAULT_SPEED              0x00
#define UIS_ADDR_HIGH_SPEED                 0x01
#define UIS_ADDR_UHSI_SDR12                 0x02
#define UIS_ADDR_UHSI_SDR25                 0x03
#define UIS_ADDR_UHSI_SDR50                 0x04
#define UIS_ADDR_UHSI_DDR50                 0x06
#define UIS_ADDR_MMC_LEGACY                 0x07
#define UIS_ADDR_MMC_SDR                    0x08
#define UIS_ADDR_MMC_DDR                    0x09
//@}
//-----------------------------------------------------------------------------

#define SDIOHost_AxiErrorInit(HOST)
#define SDIOHost_AxiErrorIntSignalCfg(HOST, EN)
#define SDIOHost_AxiErrorGetStatus(HOST, STAT)
#define SDIOHost_AxiErrorClearStatus(HOST, BITS)

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
    { UIS_ADDR_UHSI_DDR50, CSDD_PHY_DELAY_INPUT_SDR50},
    { UIS_ADDR_MMC_LEGACY, CSDD_PHY_DELAY_INPUT_MMC_LEGACY},
    { UIS_ADDR_MMC_SDR, CSDD_PHY_DELAY_INPUT_MMC_SDR},
    { UIS_ADDR_MMC_DDR, CSDD_PHY_DELAY_INPUT_MMC_DDR},
};

#endif
