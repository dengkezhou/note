#ifndef __CLK_H__
#define __CLK_H__

//Formula for PLLOUT (Integer mode)
//PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
//Where DIVF_VAL = 1 + DIVFI
//Example:
//    RANGE[2:0] = 110
//    DIVFI[8:0] = 000001110
//    DIVF_VAL = 1 + 14 = 15
//    REF = 300 (MHz)
//    DIVR[5:0] = 000010, so DIVR_VAL=3
//    DIVQ[4:0] = 00001, so DIVQ_VAL=4
//    PLLOUT = 300 / 3 * (4) * 15 / 4 = 1500 (MHz)
//    VCO range from 1200 ~ 6000 MHz
//
//Formula for PLLOUT (Fractional mode)
//PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
//Where DIVF_VAL = 1 + DIVFI + (DIVFF/2 24 )
//Example:
//    RANGE[2:0] = 000
//    DIVFI[8:0] = 001010101
//    DIVFF[23:0] = 100000011110110011010110
//    DIVF_VAL = 1 + 85 + (8514774/2 24 ) = 1 + 85 + 0. 50752 = 86.50752
//    REF = 156.25 (MHz)
//    DIVR[5:0] = 011000, so DIVR_VAL=25
//    DIVQ[4:0] = 10101, so DIVQ_VAL=44
//    PLLOUT = 156.25 / 25 * (4) * 86.50752 / 44 = 49.152 (MHz)

///////////////////////////////////////////////////////////
//CPU subsystem CLKGEN
#define MLCLKG_BASE         CLKGEN_BASE + 0xC0

#define CLKGEN_ARANGE       (CLKGEN_BASE + 0x00)
#define CLKGEN_ADIVR        (CLKGEN_BASE + 0x04)
#define CLKGEN_ADIVFI       (CLKGEN_BASE + 0x08)
#define CLKGEN_ADIVQ        (CLKGEN_BASE + 0x0C)
#define CLKGEN_ADIVFF       (CLKGEN_BASE + 0x10)
#define CLKGEN_ADIVQF       (CLKGEN_BASE + 0x14)
#define CLKGEN_ASSCFG       (CLKGEN_BASE + 0x18)
#define CLKGEN_ALDCFG       (CLKGEN_BASE + 0x1C)
#define CLKGEN_AEN          (CLKGEN_BASE + 0x20)
#define CLKGEN_ASEL         (CLKGEN_BASE + 0x24)
#define CLKGEN_ALOCK        (CLKGEN_BASE + 0x28)

#define CLKGEN_DRANGE       (CLKGEN_BASE + 0x30)
#define CLKGEN_DDIVR        (CLKGEN_BASE + 0x34)
#define CLKGEN_DDIVFI       (CLKGEN_BASE + 0x38)
#define CLKGEN_DDIVQ        (CLKGEN_BASE + 0x3C)
#define CLKGEN_DDIVFF       (CLKGEN_BASE + 0x40)
#define CLKGEN_DDIVQF       (CLKGEN_BASE + 0x44)
#define CLKGEN_DSSCFG       (CLKGEN_BASE + 0x48)
#define CLKGEN_DLDCFG       (CLKGEN_BASE + 0x4C)
#define CLKGEN_DEN          (CLKGEN_BASE + 0x50)
#define CLKGEN_DSEL         (CLKGEN_BASE + 0x54)
#define CLKGEN_DLOCK        (CLKGEN_BASE + 0x58)

#define CLKGEN_ERANGE       (CLKGEN_BASE + 0x60)
#define CLKGEN_EDIVR        (CLKGEN_BASE + 0x64)
#define CLKGEN_EDIVFI       (CLKGEN_BASE + 0x68)
#define CLKGEN_EDIVQ        (CLKGEN_BASE + 0x6C)
#define CLKGEN_EDIVFF       (CLKGEN_BASE + 0x70)
#define CLKGEN_EDIVQF       (CLKGEN_BASE + 0x74)
#define CLKGEN_ESSCFG       (CLKGEN_BASE + 0x78)
#define CLKGEN_ELDCFG       (CLKGEN_BASE + 0x7C)
#define CLKGEN_EEN          (CLKGEN_BASE + 0x80)
#define CLKGEN_ESEL         (CLKGEN_BASE + 0x84)
#define CLKGEN_ELOCK        (CLKGEN_BASE + 0x88)

#define CLKGEN_VRANGE       (CLKGEN_BASE + 0x90)
#define CLKGEN_VDIVR        (CLKGEN_BASE + 0x94)
#define CLKGEN_VDIVFI       (CLKGEN_BASE + 0x98)
#define CLKGEN_VDIVQ        (CLKGEN_BASE + 0x9C)
#define CLKGEN_VDIVFF       (CLKGEN_BASE + 0xA0)
#define CLKGEN_VDIVQF       (CLKGEN_BASE + 0xA4)
#define CLKGEN_VSSCFG       (CLKGEN_BASE + 0xA8)
#define CLKGEN_VLDCFG       (CLKGEN_BASE + 0xAC)
#define CLKGEN_VEN          (CLKGEN_BASE + 0xB0)
#define CLKGEN_VSEL         (CLKGEN_BASE + 0xB4)
#define CLKGEN_VLOCK        (CLKGEN_BASE + 0xB8)

#define CPUC_LOADEN         (CLKGEN_BASE + 0x380)
#define CPUC_SRCCFG         (CLKGEN_BASE + 0x384)
#define CPUC_CLKCYC         (CLKGEN_BASE + 0x388)
#define CPUC_CLKSEQ         (CLKGEN_BASE + 0x38C)
#define CPUC_BUSSEQ         (CLKGEN_BASE + 0x390)
#define CPUC_BUSEN          (CLKGEN_BASE + 0x394)

//#define CLKG_WSRC   (io, val )  (void) MA_OUTW(MLCLKG_BASE+0x0+(uint32_t)io*0x10, (uint32_t) val)
//#define CLKG_WRATIO (io, val )  (void) MA_OUTW(MLCLKG_BASE+0x4+(uint32_t)io*0x10, (uint32_t) val)
//#define CLKG_WNCO   (io, val )  (void) MA_OUTW(MLCLKG_BASE+0x8+(uint32_t)io*0x10, (uint32_t) val)
//#define CLKG_WCFG   (io, val )  (void) MA_OUTW(MLCLKG_BASE+0xC+(uint32_t)io*0x10, (uint32_t) val)

///////////////////////////////////////////////////////////
//SAP subsystem CLKGEN
#define SMLCLKG_BASE        SCLKGEN_BASE + 0xC0

#define SCLKGEN_ARANGE      (SCLKGEN_BASE + 0x00)
#define SCLKGEN_ADIVR       (SCLKGEN_BASE + 0x04)
#define SCLKGEN_ADIVFI      (SCLKGEN_BASE + 0x08)
#define SCLKGEN_ADIVQ       (SCLKGEN_BASE + 0x0C)
#define SCLKGEN_ADIVFF      (SCLKGEN_BASE + 0x10)
#define SCLKGEN_ADIVQF      (SCLKGEN_BASE + 0x14)
#define SCLKGEN_ASSCFG      (SCLKGEN_BASE + 0x18)
#define SCLKGEN_ALDCFG      (SCLKGEN_BASE + 0x1C)
#define SCLKGEN_AEN         (SCLKGEN_BASE + 0x20)
#define SCLKGEN_ASEL        (SCLKGEN_BASE + 0x24)
#define SCLKGEN_ALOCK       (SCLKGEN_BASE + 0x28)


//#define SCLKG_WSRC   (io, val )  (void) MA_OUTW(SMLCLKG_BASE+0x0+(uint32_t)io*0x10, (uint32_t) val)
//#define SCLKG_WRATIO (io, val )  (void) MA_OUTW(SMLCLKG_BASE+0x4+(uint32_t)io*0x10, (uint32_t) val)
//#define SCLKG_WNCO   (io, val )  (void) MA_OUTW(SMLCLKG_BASE+0x8+(uint32_t)io*0x10, (uint32_t) val)
//#define SCLKG_WCFG   (io, val )  (void) MA_OUTW(SMLCLKG_BASE+0xC+(uint32_t)io*0x10, (uint32_t) val)


#endif

