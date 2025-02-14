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
 * sdio_host.h
 * SD Host controller driver
 *****************************************************************************/

#ifndef SDIO_HOST_H
#define SDIO_HOST_H

#include "sdio_types.h"
#include "sdio_config.h"
#include "sdio_errors.h"
#include "sdio_utils.h"
#include "cps_drv.h"
#include "sd4hc_regs.h"
#include "csdd_if.h"
#include "csdd_structs_if.h"
#include "cdn_log.h"

#ifndef SDIO_CFG_HOST_VER
    #error "SDIO_CFG_HOST_VER should be defined explicitly"
#endif

#if SDIO_CFG_HOST_VER == 3
#include "sdio_sd3_host.h"
#endif

#if SDIO_CFG_HOST_VER >= 4
#include "sdio_sd4_host.h"
#endif

#define IDLE() CPS_DelayNs(200U)

/// Choose SD bus mode SD or SPI ( currently only SD bus mode is supported )
#define HOST_BUS_MODE                       CSDD_BUS_MODE_SD

#define SDIO_HOST_VER_WTH_CCP 		    6U
//-----------------------------------------------------------------------------
/// @name Slot Register Set Organization
//-----------------------------------------------------------------------------
//@{
/// Host control settings #1 register
#define SDIO_REG_SRS11  0x2CU
/// Interrupt status register
#define SDIO_REG_SRS12  0x30U
/// Capabilities #1
#define SDIO_REG_SRS16  0x40U

//@}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// Card Status
#define SDIO_CARD_STATUS_MASK  0x00001E00UL
/// Trans state
#define SDIO_CARD_TRANS_STATE  0x00000800UL
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// @name Common Register (CRS63) - masks
//-----------------------------------------------------------------------------
//@{
static inline uint32_t CRS63_GET_SPEC_VERSION(const uint32_t val)
{
    return (((val >> 16) & 0xFFU) + 1U);
}

static inline uint32_t CRS63_GET_VENDOR_VERSION(const uint32_t val)
{
    return ((val >> 24) & 0xFFU);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Block count and size register (SFR1) - masks
//-----------------------------------------------------------------------------
//@{
/// Block count for current transfer mask
#define SRS1_BLOCK_COUNT            SD4HC__SRS__SRS01__BCCT_MASK
/// DMA buffer size 4kB
#define SRS1_DMA_BUFF_SIZE_4KB      0x00000000UL
/// DMA buffer size 8kB
#define SRS1_DMA_BUFF_SIZE_8KB      0x00001000UL
/// DMA buffer size 16kB
#define SRS1_DMA_BUFF_SIZE_16KB     0x00002000UL
/// DMA buffer size 32kB
#define SRS1_DMA_BUFF_SIZE_32KB     0x00003000UL
/// DMA buffer size 64kB
#define SRS1_DMA_BUFF_SIZE_64KB     0x00004000UL
/// DMA buffer size 128kB
#define SRS1_DMA_BUFF_SIZE_128KB    0x00005000UL
/// DMA buffer size 265kB
#define SRS1_DMA_BUFF_SIZE_256KB    0x00006000UL
/// DMA buffer size 512kB
#define SRS1_DMA_BUFF_SIZE_512KB    0x00007000UL
/// DMA buffer size mask
#define SRS1_DMA_BUFF_SIZE_MASK     SD4HC__SRS__SRS01__SDMABB_MASK
/// Transfer block size mask
#define SRS1_BLOCK_SIZE             SD4HC__SRS__SRS01__TBS_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Transfer mode and command information register (SFR3) - masks
//-----------------------------------------------------------------------------
//@{
//command type                      SD4HC__SRS__SRS03__CT_MASK
/// Abort CMD12, CMD52 for writing "I/O Abort" in CCCR
#define SRS3_ABORT_CMD              (0x3UL << 22)
/// Resume CMD52 for writing "Function Select" in CCCR
#define SRS3_RESUME_CMD             (0x2UL << 22)
///Suspend CMD52 for writing "Bus Suspend" in CCCR
#define SRS3_SUSPEND_CMD            (0x1UL << 22)
/// data is present and will be transferred using the DAT line
#define SRS3_DATA_PRESENT           SD4HC__SRS__SRS03__DPS_MASK
/// index check enable
#define SRS3_INDEX_CHECK_EN         SD4HC__SRS__SRS03__CICE_MASK
/// response CRC check enable
#define SRS3_CRC_CHECK_EN           SD4HC__SRS__SRS03__CRCCE_MASK
//  Sub Command Flag - This bit is added from Version 4.10 to distinguish a main command or sub command.
#define SRS3_SUB_CMD_FLAG		SD4HC__SRS__SRS03__SCF_MASK;
/// response type                   SD4HC__SRS__SRS03__RTS_MASK
/// response type - no response
#define SRS3_NO_RESPONSE            (0x0UL << 16)
/// response type - response length 136
#define SRS3_RESP_LENGTH_136        (0x1UL << 16)
/// response type - response length 48
#define SRS3_RESP_LENGTH_48         (0x2UL << 16)
/// response type - response length 48 and check Busy after response
#define SRS3_RESP_LENGTH_48B        (0x3UL << 16)
/// RID - Response Interrupt Disable
/// When set to 1, the Command Complete Interrupt (SRS12.CC)
/// will be disabled
#define SRS3_RESP_INTER_DISABLE     SD4HC__SRS__SRS03__RID_MASK
/// RECE - Response Error Check Enable.
/// When set 1, the host will look after R1/R5 responses.
#define SRS3_RESP_ERR_CHECK_EN      SD4HC__SRS__SRS03__RECE_MASK
/// Response type                   SD4HC__SRS__SRS03__RECT_MASK
/// Response type R1 for the response content checker
#define SRS3_RESPONSE_CHECK_TYPE_R1 (0x0UL << 6)
/// Response type R5 for the response content checker
#define SRS3_RESPONSE_CHECK_TYPE_R5 (0x1UL << 6)
/// multi block DAT line data transfers
#define SRS3_MULTI_BLOCK_SEL        SD4HC__SRS__SRS03__MSBS_MASK
//Data Transfer Direction Select    SD4HC__SRS__SRS03__DTDS_MASK
/// data transfer direction - write
#define SRS3_TRANS_DIRECT_WRITE     (0x0UL << 4)
/// data transfer direction - read
#define SRS3_TRANS_DIRECT_READ      (0x1UL << 4)
//Auto CMD Enable                   SD4HC__SRS__SRS03__ACE_MASK
/// Auto CMD23 enable
#define SRS3_AUTOCMD23_ENABLE       (0x2UL << 2)
/// Auto CMD12 enable
#define SRS3_AUTOCMD12_ENABLE       (0x1UL << 2)
/// Auto CMD Auto Select
#define SRS3_AUTO_CMD_AUTO_SELECT_ENABLE	(0x3UL << 2)
/// Block count enable
#define SRS3_BLOCK_COUNT_ENABLE     SD4HC__SRS__SRS03__BCE_MASK
/// DMA enable
#define SRS3_DMA_ENABLE             SD4HC__SRS__SRS03__DMAE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Present state register masks (SFR9) - masks
//-----------------------------------------------------------------------------
//@{
/// Command Not Issued By Error
#define SRS9_CMD_NOT_ISSUED			SD4HC__SRS__SRS09__CNIBE_MASK
/// CMD line signal level
#define SRS9_CMD_SIGNAL_LEVEL       SD4HC__SRS__SRS09__CMDSL_MASK
// DAT[3:0] Line Signal Level       SD4HC__SRS__SRS09__DATSL1_MASK
/// DAT3 signal level
#define SRS9_DAT3_SIGNAL_LEVEL      ((uint32_t)(0x1UL << 23))
/// DAT2 signal level
#define SRS9_DAT2_SIGNAL_LEVEL      ((uint32_t)(0x1UL << 22))
/// DAT1 signal level
#define SRS9_DAT1_SIGNAL_LEVEL      ((uint32_t)(0x1UL << 21))
/// DAT0 signal level
#define SRS9_DAT0_SIGNAL_LEVEL      ((uint32_t)(0x1UL << 20))
/// Write protect switch pin level
#define SRS9_WP_SWITCH_LEVEL        SD4HC__SRS__SRS09__WPSL_MASK
/// Card detect pin level
#define SRS9_CARD_DETECT_LEVEL      SD4HC__SRS__SRS09__CDSL_MASK
/// Card state stable
#define SRS9_CARD_STATE_STABLE      SD4HC__SRS__SRS09__CSS_MASK
/// Card inserted
#define SRS9_CARD_INSERTED          SD4HC__SRS__SRS09__CI_MASK
/// Buffer read enable
#define SRS9_BUFF_READ_EN           SD4HC__SRS__SRS09__BRE_MASK
/// Buffer write enable
#define SRS9_BUFF_WRITE_EN          SD4HC__SRS__SRS09__BWE_MASK
/// Read transfer active
#define SRS9_READ_TRANS_ACTIVE      SD4HC__SRS__SRS09__RTA_MASK
/// Write transfer active
#define SRS9_WRITE_TRANS_ACTIVE     SD4HC__SRS__SRS09__WTA_MASK
//  DAT[7:4] Line Signal Level      SD4HC__SRS__SRS09__DATSL2_MASK
/** DAT7 Line Signal Level l (SD Mode only) */
#define SRS9_WRITE_DAT7_PIN_LEVEL   ((uint32_t)(0x1UL << 7))
/** DAT6 Line Signal Level l (SD Mode only) */
#define SRS9_WRITE_DAT6_PIN_LEVEL   ((uint32_t)(0x1UL << 6))
/** DAT5 Line Signal Level l (SD Mode only) */
#define SRS9_WRITE_DAT5_PIN_LEVEL   ((uint32_t)(0x1UL << 5))
/** DAT4 Line Signal Level l (SD Mode only) */
#define SRS9_WRITE_DAT4_PIN_LEVEL   ((uint32_t)(0x1UL << 4))
/// The signal will be used by the SD driver to rerun the
/// DAT line active
#define SRS9_DAT_LINE_ACTIVE        SD4HC__SRS__SRS09__DLA_MASK
/// Command Inhibit (DAT)
#define SRS9_CMD_INHIBIT_DAT        SD4HC__SRS__SRS09__CIDAT_MASK
/// Command Inhibit (CMD)
#define SRS9_CMD_INHIBIT_CMD        SD4HC__SRS__SRS09__CICMD_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @anchor Voltages
/// @name Host control settings #0 (SFR10) - masks
//-----------------------------------------------------------------------------
//@{
/// Wakeup event enable on SD card removal
#define SRS10_WAKEUP_EVENT_CARD_REM_ENABLE  SD4HC__SRS__SRS10__WORM_MASK
/// Wakeup event enable on SD card inserted
#define SRS10_WAKEUP_EVENT_CARD_INS_ENABLE  SD4HC__SRS__SRS10__WOIS_MASK
/// Wakeup event enable on SD card interrupt
#define SRS10_WAKEUP_EVENT_CARD_INT_ENABLE  SD4HC__SRS__SRS10__WOIQ_MASK
/// Continue request
#define SRS10_CONTINUE_REQUEST              SD4HC__SRS__SRS10__CREQ_MASK
/// Stop at block gap request
#define SRS10_STOP_AT_BLOCK_GAP             SD4HC__SRS__SRS10__SBGR_MASK
// SD Bus Voltage Select for VDD2           SD4HC__SRS__SRS10__BVS2_MASK
/** SD Bus Voltage Select mask */
#define SRS10_VOLT_VDD2_MASK                ((uint32_t)(0x7UL << 13))
// SD Bus Voltage Select                    SD4HC__SRS__SRS10__BVS_MASK
/// SD bus voltage - 3.3V
#define SRS10_SET_3_3V_BUS_VOLTAGE          ((uint32_t)(0x7UL << 9))
/// SD bus voltage - 3.0V
#define SRS10_SET_3_0V_BUS_VOLTAGE          ((uint32_t)(0x6UL << 9))
/// SD bus voltage - 1.8V
#define SRS10_SET_1_8V_BUS_VOLTAGE          ((uint32_t)(0x5UL << 9))
/// SD bus voltage mask
#define SRS10_BUS_VOLTAGE_MASK              ((uint32_t)(0x7UL << 9))
/// SD bus power. The SD device is powered.
#define SRS10_SD_BUS_POWER                  SD4HC__SRS__SRS10__BP_MASK
/// Card Detect Signal Selection
#define SRS10_CDSS                          SD4HC__SRS__SRS10__CDSS_MASK
/// Card Detect Test Level
#define SRS10_CARD_DETECT_TEST              SD4HC__SRS__SRS10__CDTL_MASK
/// Extended Data Transfer Width
#define SRS10_EXTENDED_DATA_TRANSFER_WIDTH  SD4HC__SRS__SRS10__EDTW_MASK
// DMA Select                               SD4HC__SRS__SRS10__DMASEL_MASK
/// select SDMA mode
#define SRS10_DMA_SELECT_SDMA               ((uint32_t)(0x0UL << 3))
/// select ADMA1 mode
#define SRS10_DMA_SELECT_ADMA1              ((uint32_t)(0x1UL << 3))
/// select ADMA2 mode
#define SRS10_DMA_SELECT_ADMA2              ((uint32_t)(0x2UL << 3))
/// DMA mode selection mask
#define SRS10_DMA_SELECT_MASK               ((uint32_t)(0x3UL << 3))
/// High speed enable.
#define SRS10_HIGH_SPEED_ENABLE             SD4HC__SRS__SRS10__HSE_MASK
/// Set 4 bit data transfer width
#define SRS10_DATA_WIDTH_4BIT               SD4HC__SRS__SRS10__DTW_MASK
/// Turning on the LED.
#define SRS10_TURN_ON_LED                   SD4HC__SRS__SRS10__LEDC_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Host control settings #1 (SFR11) - masks
//-----------------------------------------------------------------------------
//{@
/// Software reset for DAT line
#define SRS11_SOFT_RESET_DAT_LINE           SD4HC__SRS__SRS11__SRDAT_MASK
/// Software reset for CMD line
#define SRS11_SOFT_RESET_CMD_LINE           SD4HC__SRS__SRS11__SRCMD_MASK
/// Software reset for all. Restart entrie controller except the card detection circuit.
#define SRS11_SOFT_RESET_ALL                SD4HC__SRS__SRS11__SRFA_MASK

// Data Timeout Counter Value               SD4HC__SRS__SRS11__DTCV_MASK
/// Data timeout TMCLK x 2 raised to the 27-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_27      (0xEUL << 16)
/// Data timeout TMCLK x 2 raised to the 26-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_26      (0xDUL << 16)
/// Data timeout TMCLK x 2 raised to the 25-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_25      (0xCUL << 16)
/// Data timeout TMCLK x 2 raised to the 24-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_24      (0xBUL << 16)
/// Data timeout TMCLK x 2 raised to the 23-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_23      (0xAUL << 16)
/// Data timeout TMCLK x 2 raised to the 22-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_22      (0x9UL << 16)
/// Data timeout TMCLK x 2 raised to the 21-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_21      (0x8UL << 16)
/// Data timeout TMCLK x 2 raised to the 20-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_20      (0x7UL << 16)
/// Data timeout TMCLK x 2 raised to the 19-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_19      (0x6UL << 16)
/// Data timeout TMCLK x 2 raised to the 18-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_18      (0x5UL << 16)
/// Data timeout TMCLK x 2 raised to the 17-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_17      (0x4UL << 16)
/// Data timeout TMCLK x 2 raised to the 16-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_16      (0x3UL << 16)
/// Data timeout TMCLK x 2 raised to the 15-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_15      (0x2UL << 16)
/// Data timeout TMCLK x 2 raised to the 14-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_14      (0x1UL << 16)
/// Data timeout TMCLK x 2 raised to the 13-th power
#define SRS11_TIMEOUT_TMCLK_X_2_PWR_13      (0x0UL << 16)
/// Data timeout mask
#define SRS11_TIMEOUT_MASK                  (0xFUL << 16)

// SDCLK Frequency Select (lower part)      SD4HC__SRS__SRS11__SDCFSL_MASK
// SDCFSH SDCLK Frequency Select (higher part) SD4HC__SRS__SRS11__SDCFSH_MASK
/// SDCLK Frequency select. Divide base clock by 256.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_256     (128UL << 8)
/// SDCLK Frequency select. Divide base clock by 128.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_128     (64UL << 8)
/// SDCLK Frequency select. Divide base clock by 64.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_64      (32UL << 8)
/// SDCLK Frequency select. Divide base clock by 32.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_32      (16UL << 8)
/// SDCLK Frequency select. Divide base clock by 16.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_16      (8UL << 8)
/// SDCLK Frequency select. Divide base clock by 8.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_8       (4UL << 8)
/// SDCLK Frequency select. Divide base clock by 4.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_4       (2UL << 8)
/// SDCLK Frequency select. Divide base clock by 2.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_2       (1UL << 8)
/// SDCLK Frequency select. Divide base clock by 1.
#define SRS11_SEL_FREQ_BASE_CLK_DIV_1       (0UL << 8)
/// SDCLK Frequency mask
#define SRS11_SEL_FREQ_BASE_MASK            (SD4HC__SRS__SRS11__SDCFSL_MASK | SD4HC__SRS__SRS11__SDCFSH_MASK)
/// Clock Generator Select
//The SDCLK Frequency Divider method can be selected by this field
#define SRS11_CLOCK_GENERATOR_SELECT        (0x1UL << 5)
/// SD clock enable
#define SRS11_SD_CLOCK_ENABLE               SD4HC__SRS__SRS11__SDCE_MASK
/// Internal clock stable
#define SRS11_INT_CLOCK_STABLE              SD4HC__SRS__SRS11__ICS_MASK
/// internal clock enable
#define SRS11_INT_CLOCK_ENABLE              SD4HC__SRS__SRS11__ICE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Interrupt status register (SFR12) - masks
//-----------------------------------------------------------------------------
//@{
/** ERSP - Response Error (SD Mode only) */
#define SRS12_RESPONSE_ERROR        SD4HC__SRS__SRS12__ERSP_MASK
/// Tuning error
#define SRS12_TUNING_ERROR          ((uint32_t)(0x1UL << 26))  // SD4HC__SRS__SRS12__RSVD_1_MASK
/// ADMA error
#define SRS12_ADMA_ERROR            SD4HC__SRS__SRS12__EADMA_MASK
/// Auto CMD (CMD12 or CMD23) error
#define SRS12_AUTO_CMD_ERROR        SD4HC__SRS__SRS12__EAC_MASK
/// Current limit error host controller is not supplying power to SD card due some failure.
#define SRS12_CURRENT_LIMIT_ERROR   SD4HC__SRS__SRS12__ECL_MASK
/// Data end bit error
#define SRS12_DATA_END_BIT_ERROR    SD4HC__SRS__SRS12__EDEB_MASK
/// Data CRC error
#define SRS12_DATA_CRC_ERROR        SD4HC__SRS__SRS12__EDCRC_MASK
/// Data timeout error
#define SRS12_DATA_TIMEOUT_ERROR    SD4HC__SRS__SRS12__EDT_MASK
/// Command index error. Index error occurs in the command response.
#define SRS12_COMMAND_INDEX_ERROR   SD4HC__SRS__SRS12__ECI_MASK
/// Command end bit error
#define SRS12_COMMAND_END_BIT_ERROR SD4HC__SRS__SRS12__ECEB_MASK
/// Command CRC error
#define SRS12_COMMAND_CRC_ERROR     SD4HC__SRS__SRS12__ECCRC_MASK
/// Command timeout error
#define SRS12_COMMAND_TIMEOUT_ERROR SD4HC__SRS__SRS12__ECT_MASK
/// Error interrupt
#define SRS12_ERROR_INTERRUPT       SD4HC__SRS__SRS12__EINT_MASK
/// Command Queuing - interrupt
#define SRS12_CMD_QUEUING_INT       SD4HC__SRS__SRS12__CQINT_MASK
/// Re-Tuning Event
#define SRS12_RETUNING_EVENT        ((uint32_t)(0x1UL << 12))
/// Interrupt on line C
#define SRS12_INTERRUPT_ON_LINE_C   ((uint32_t)(0x1UL << 11))
/// Interrupt on line B
#define SRS12_INTERRUPT_ON_LINE_B   ((uint32_t)(0x1UL << 10))
/// Interrupt on line A
#define SRS12_INTERRUPT_ON_LINE_A   ((uint32_t)(0x1UL << 9))
// Card interrupt
#define SRS12_CARD_INTERRUPT        SD4HC__SRS__SRS12__CINT_MASK
/// Card removal
#define SRS12_CARD_REMOVAL          SD4HC__SRS__SRS12__CR_MASK
/// Card insertion
#define SRS12_CARD_INSERTION        SD4HC__SRS__SRS12__CIN_MASK
/// Buffer read ready. Host is ready to read the buffer.
#define SRS12_BUFFER_READ_READY     SD4HC__SRS__SRS12__BRR_MASK
/// Buffer write ready. Host is ready for writing data to the buffer.
#define SRS12_BUFFER_WRITE_READY    SD4HC__SRS__SRS12__BWR_MASK
/// DMA interrupt
#define SRS12_DMA_INTERRUPT         SD4HC__SRS__SRS12__DMAINT_MASK
/// Block gap event
#define SRS12_BLOCK_GAP_EVENT       SD4HC__SRS__SRS12__BGE_MASK
/// Transfer complete
#define SRS12_TRANSFER_COMPLETE     SD4HC__SRS__SRS12__TC_MASK
/// Command complete
#define SRS12_COMMAND_COMPLETE      SD4HC__SRS__SRS12__CC_MASK
/// normal interrupt status mask
#define SRS12_NORMAL_STAUS_MASK     ((uint32_t)(0xFFFFUL))
#define SRS12_ERROR_STATUS_MASK     ((uint32_t)(0xFFFF0000UL))
#define SRS12_ERROR_CMD_LINE        (SRS12_COMMAND_TIMEOUT_ERROR \
                                     | SRS12_COMMAND_CRC_ERROR \
                                     | SRS12_COMMAND_END_BIT_ERROR \
                                     | SRS12_COMMAND_INDEX_ERROR)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Interrupt status enable register (SFR13) - masks
//-----------------------------------------------------------------------------
//@{
/** ERSP_SE - Response Error Status Enable */
#define SRS13_RESPONSE_ERROR_STAT_EN        SD4HC__SRS__SRS13__ERSP_SE_MASK
/// Tuning error status enable
#define SRS13_TUNING_ERROR_STAT_EN          (0x1UL << 26)  // SD4HC__SRS__SRS13__RSVD_2_MASK
/// ADMA error status enable
#define SRS13_ADMA_ERROR_STAT_EN            SD4HC__SRS__SRS13__EADMA_SE_MASK
/// Auto CMD12 error status enable
#define SRS13_AUTO_CMD12_ERR_STAT_EN        SD4HC__SRS__SRS13__EAC_SE_MASK
/// Current limit error status enable
#define SRS13_CURRENT_LIMIT_ERR_STAT_EN     SD4HC__SRS__SRS13__ECL_SE_MASK
/// Data end bit error status enable
#define SRS13_DATA_END_BIT_ERR_STAT_EN      SD4HC__SRS__SRS13__EDEB_SE_MASK
/// Data CRC error status enable
#define SRS13_DATA_CRC_ERR_STAT_EN          SD4HC__SRS__SRS13__EDCRC_SE_MASK
/// Data timeout error status enable
#define SRS13_DATA_TIMEOUT_ERR_STAT_EN      SD4HC__SRS__SRS13__EDT_SE_MASK
/// Command index error status enable
#define SRS13_COMMAND_INDEX_ERR_STAT_EN     SD4HC__SRS__SRS13__ECI_SE_MASK
/// Command end bit error status enable
#define SRS13_COMMAND_END_BIT_ERR_STAT_EN   SD4HC__SRS__SRS13__ECEB_SE_MASK
/// Command CRC error status enable
#define SRS13_COMMAND_CRC_ERR_STAT_EN       SD4HC__SRS__SRS13__ECCRC_SE_MASK
/// Command timeout error status enable
#define SRS13_COMMAND_TIMEOUT_ERR_STAT_EN   SD4HC__SRS__SRS13__ECT_SE_MASK
/// Command Queuing Status Enable
#define SRS13_CMD_QUEUING_STAT_EN           SD4HC__SRS__SRS13__CQINT_SE_MASK

// SD4HC__SRS__SRS13__RSVD_0_MASK          0x00003E00U
/// Re-Tuning Event status enable
#define SRS13_RETUNING_EVENT_STAT_EN        (0x1UL << 12)
///Interrupt on line C status enable
#define SRS13_INTERRUPT_ON_LINE_C_STAT_EN   (0x1UL << 11)
/// Interrupt on line B status enable
#define SRS13_INTERRUPT_ON_LINE_B_STAT_EN   (0x1UL << 10)
/// Interrupt on line A status enable
#define SRS13_INTERRUPT_ON_LINE_A_STAT_EN   (0x1UL << 9)
/// Card interrupt status enable
#define SRS13_CARD_INTERRUPT_STAT_EN        SD4HC__SRS__SRS13__CINT_SE_MASK
/// Card removal status enable
#define SRS13_CARD_REMOVAL_STAT_EN          SD4HC__SRS__SRS13__CR_SE_MASK
/// Card insertion status enable
#define SRS13_CARD_INERTION_STAT_EN         SD4HC__SRS__SRS13__CIN_SE_MASK
/// Buffer read ready status enable
#define SRS13_BUF_READ_READY_STAT_EN        SD4HC__SRS__SRS13__BRR_SE_MASK
/// Buffer write ready status enable
#define SRS13_BUF_WRITE_READY_STAT_EN       SD4HC__SRS__SRS13__BWR_SE_MASK
/// DMA interrupt status enable
#define SRS13_DMA_INTERRUPT_STAT_EN         SD4HC__SRS__SRS13__DMAINT_SE_MASK
/// Block gap event status enable
#define SRS13_BLOCK_GAP_EVENT_STAT_EN       SD4HC__SRS__SRS13__BGE_SE_MASK
/// Transfer complete status enable
#define SRS13_TRANSFER_COMPLETE_STAT_EN     SD4HC__SRS__SRS13__TC_SE_MASK
/// Command complete status enable
#define SRS13_COMMAND_COMPLETE_STAT_EN      SD4HC__SRS__SRS13__CC_SE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Interrupt signal enable register (SFR14) - masks
//-----------------------------------------------------------------------------
//{@
/// Response error interrupt signdla enable
#define SRS14_RESPONSE_ERROR_SIG_EN         SD4HC__SRS__SRS14__ERSP_IE_MASK
/// Tuning error signal enable
#define SRS14_TUNING_ERROR_SIG_EN           (0x1UL << 26)  // SD4HC__SRS__SRS14__RSVD_2_MASK
/// ADMA error signal enable
#define SRS14_ADMA_ERROR_SIG_EN             SD4HC__SRS__SRS14__EADMA_IE_MASK
/// Auto CMD12 error signal enable
#define SRS14_AUTO_CMD12_ERR_SIG_EN         SD4HC__SRS__SRS14__EAC_IE_MASK
/// Current limit error signal enable
#define SRS14_CURRENT_LIMIT_ERR_SIG_EN      SD4HC__SRS__SRS14__ECL_IE_MASK
/// Data end bit error signal enable
#define SRS14_DATA_END_BIT_ERR_SIG_EN       SD4HC__SRS__SRS14__EDEB_IE_MASK
/// Data CRC error signal enable
#define SRS14_DATA_CRC_ERR_SIG_EN           SD4HC__SRS__SRS14__EDCRC_IE_MASK
/// Data timeout error signal enable
#define SRS14_DATA_TIMEOUT_ERR_SIG_EN       SD4HC__SRS__SRS14__EDT_IE_MASK
/// Command index error signal enable
#define SRS14_COMMAND_INDEX_ERR_SIG_EN      SD4HC__SRS__SRS14__ECI_IE_MASK
/// Command end bit error signal enable
#define SRS14_COMMAND_END_BIT_ERR_SIG_EN    SD4HC__SRS__SRS14__ECEB_IE_MASK
/// Command CRC error signal enable
#define SRS14_COMMAND_CRC_ERR_SIG_EN        SD4HC__SRS__SRS14__ECCRC_IE_MASK
/// Command timeout error signal enable
#define SRS14_COMMAND_TIMEOUT_ERR_SIG_EN    SD4HC__SRS__SRS14__ECT_IE_MASK
/// Command Queuing - interrupt enable
#define SRS14_CMD_QUEUING_SIG_EN            SD4HC__SRS__SRS14__CQINT_IE_MASK
// SD4HC__SRS__SRS14__RSVD_0_MASK           0x00003E00U
/// Re-Tuning Event signal enable
#define SRS14_RETUNING_EVENT_SIG_EN         (0x1UL << 12)
///Interrupt on line C signal enable
#define SRS14_INTERRUPT_ON_LINE_C_SIG_EN    (0x1UL << 11)
/// Interrupt on line B signal enable
#define SRS14_INTERRUPT_ON_LINE_B_SIG_EN    (0x1UL << 10)
/// Interrupt on line A signal enable
#define SRS14_INTERRUPT_ON_LINE_A_SIG_EN    (0x1UL << 9)
// Card interrupt signal enable
#define SRS14_CARD_INTERRUPT_SIG_EN         SD4HC__SRS__SRS14__CINT_IE_MASK
/// Card removal signal enable
#define SRS14_CARD_REMOVAL_SIG_EN           SD4HC__SRS__SRS14__CR_IE_MASK
/// Card insertion signal enable
#define SRS14_CARD_INERTION_SIG_EN          SD4HC__SRS__SRS14__CIN_IE_MASK
/// Buffer read ready signal enable
#define SRS14_BUFFER_READ_READY_SIG_EN      SD4HC__SRS__SRS14__BRR_IE_MASK
/// Buffer write ready signal enable
#define SRS14_BUFFER_WRITE_READY_SIG_EN     SD4HC__SRS__SRS14__BWR_IE_MASK
/// DMA interrupt signal enable
#define SRS14_DMA_INTERRUPT_SIG_EN          SD4HC__SRS__SRS14__DMAINT_IE_MASK
/// Block gap event signal enable
#define SRS14_BLOCK_GAP_EVENT_SIG_EN        SD4HC__SRS__SRS14__BGE_IE_MASK
/// Transfer complete signal enable
#define SRS14_TRANSFER_COMPLETE_SIG_EN      SD4HC__SRS__SRS14__TC_IE_MASK
/// Command complete signal enable
#define SRS14_COMMAND_COMPLETE_SIG_EN       SD4HC__SRS__SRS14__CC_IE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name AutoCMD12 Error Status Register/Host Control Register (SFR15) - masks
//-----------------------------------------------------------------------------
//@{
/// Preset Value Enable
#define SRS15_PRESET_VALUE_ENABLE       SD4HC__SRS__SRS15__PVE_MASK
/// Asynchronous Interrupt Enable
#define SRS15_ASYNCHRONOUS_INT_EN       ((uint32_t)(0x1UL << 30))  // SD4HC__SRS__SRS15__RSVD_3_MASK
/// 64-bit Addressing Specifies the addressing mode for DMA ending.
#define SRS15_64_BIT_ADDRESSING         SD4HC__SRS__SRS15__A64B_MASK
/// Host Version 4.00 Enable
/// Selects backward (SD Host 3.00 Version) compatibility mode
/// or SD Host 4.00 Version mode
#define SRS15_HOST_4_ENABLE             SD4HC__SRS__SRS15__HV4E_MASK
// CMD23E - CMD23 Enable
#define SRS15_CMD23_ENABLE				0x08000000U
// ADMA2LM - ADMA2 Length Mode
#define SRS15_ADMA2LM_MASK				0x04000000U
/// Sampling Clock Select
#define SRS15_SAMPLING_CLOCK_SELECT     SD4HC__SRS__SRS15__SCS_MASK
/// Execute Tuning
#define SRS15_EXECUTE_TUNING            SD4HC__SRS__SRS15__EXTNG_MASK
// SD4HC__SRS__SRS15__DSS_MASK          0x00300000U
/// Driver Strength Select mask
#define SRS15_DRIVER_TYPE_MASK          ((uint32_t)(0x3UL << 20))
/// Driver Strength Select type D
#define SRS15_DRIVER_TYPE_D             ((uint32_t)(0x3UL << 20))
/// Driver Strength Select type C
#define SRS15_DRIVER_TYPE_C             ((uint32_t)(0x2UL << 20))
/// Driver Strength Select type A
#define SRS15_DRIVER_TYPE_A             ((uint32_t)(0x1UL << 20))
/// Driver Strength Select type B
#define SRS15_DRIVER_TYPE_B             ((uint32_t)(0x0UL << 20))
/// This bit is to switch I/O signaling voltage level on
/// the SD interface between 3.3V and 1.8V
#define SRS15_18V_ENABLE                SD4HC__SRS__SRS15__V18SE_MASK
// SD4HC__SRS__SRS15__UMS_MASK          0x00070000U
/// UHS mode select mask
#define SRS15_UHS_MODE_MASK             ((uint32_t)(0x7UL << 16))
/// DDR50 mode select
#define SRS15_UHS_MODE_DDR50            ((uint32_t)(0x4UL << 16))
/// SDR104 mode select
#define SRS15_UHS_MODE_SDR104           ((uint32_t)(0x3UL << 16))
/// SDR50 mode select
#define SRS15_UHS_MODE_SDR50            ((uint32_t)(0x2UL << 16))
/// SDR25 mode select
#define SRS15_UHS_MODE_SDR25            ((uint32_t)(0x1UL << 16))
/// SDR12 mode select
#define SRS15_UHS_MODE_SDR12            ((uint32_t)(0x0UL << 16))
/// Command not issued bu auto CMD12 error
#define SRS15_CMD_NOT_ISSUED_ERR        SD4HC__SRS__SRS15__CNIACE_MASK
/// Auto CMD12 index error
#define SRS15_AUTO_CMD12_INDEX_ERR      SD4HC__SRS__SRS15__ACIE_MASK
/// Auto CMD12 end bit error
#define SRS15_AUTO_CMD12_END_BIT_ERR    SD4HC__SRS__SRS15__ACEBE_MASK
/// Auto CMD12 CRC error
#define SRS15_AUTO_CMD12_CRC_ERR        SD4HC__SRS__SRS15__ACCE_MASK
/// Auto CMD12 timeout error
#define SRS15_AUTO_CMD12_TIMEOUT_ERR    SD4HC__SRS__SRS15__ACTE_MASK
/// Autp CMD12 not executed
#define SRS15_AUTO_CMD12_NOT_EXECUTED   SD4HC__SRS__SRS15__ACNE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Capabilities register  #1 (SFR16) - masks
//-----------------------------------------------------------------------------
//@{
//A64B - 64-bit Addressing Mask
#define SD4HC__SRS__SRS16__A64S_MASK        0x10000000U
// Slot Type                                SD4HC__SRS__SRS16__SLT_MASK
/// Slot Type - Shared Bus Slot
#define SRS16_SLOT_TYPE_SHARED_BUS          (0x2UL << 30)
/// Slot Type - Embedded Slot for One Device
#define SRS16_SLOT_TYPE_EMBEDDED_ONE_DEV    (0x1UL << 30)
/// Slot Type - Removable Card Slot
#define SRS16_SLOT_TYPE_REMOVABLE_CARD      (0x0UL << 30)
/// Asynchronous Interrupt Support
#define SRS16_ASYNCH_INT_SUPPORT            SD4HC__SRS__SRS16__AIS_MASK
/// 64-bit System Bus Support
#define SRS16_64BIT_SUPPORT                 SD4HC__SRS__SRS16__A64S_MASK
/// 64-bit System Addressing Support for V4
#define SRS16_64BIT_SUPPORT_V4              SD4HC__SRS__SRS16__A64SV4_MASK
/// Voltage 1.8V is supported
#define SRS16_VOLTAGE_1_8V_SUPPORT          SD4HC__SRS__SRS16__VS18_MASK
/// Voltage 3.0V is supported
#define SRS16_VOLTAGE_3_0V_SUPPORT          SD4HC__SRS__SRS16__VS30_MASK
/// Voltage 3.3V is supported
#define SRS16_VOLTAGE_3_3V_SUPPORT          SD4HC__SRS__SRS16__VS33_MASK
/// Suspend and resume functionality are supported
#define SRS16_RESUME_SUPPORT                SD4HC__SRS__SRS16__SRS_MASK
/// Host controller is capable of using SDMA
#define SRS16_DMA_SUPPORT                   SD4HC__SRS__SRS16__DMAS_MASK
/// Host controller and the host system support High Speed mode.
#define SRS16_HIGH_SPEED_SUPPORT            SD4HC__SRS__SRS16__HSS_MASK
/// Host controller is capable of using ADMA1
#define SRS16_ADMA1_SUPPORT                 SD4HC__SRS__SRS16__ADMA1S_MASK
/// Host controller is capable of using ADMA2
#define SRS16_ADMA2_SUPPORT                 SD4HC__SRS__SRS16__ADMA2S_MASK
/// 8-bit Embedded Device Support
#define SRS16_8_BIT_EMB_DEV_SUPP            SD4HC__SRS__SRS16__EDS8_MASK
// Max Block Length                         SD4HC__SRS__SRS16__MBL_MASK
/// 512 is the maximum block size that can be written
/// to the buffer in the Host Controller.
#define SRS16_MAX_BLOCK_LENGTH_512          (0x0UL << 16)
/// 1024 is the maximum block size that can be written
/// to the buffer in the Host Controller.
#define SRS16_MAX_BLOCK_LENGTH_1024         (0x1UL << 16)
/// 2048 is the maximum block size that can be written to
/// the buffer in the Host Controller.
#define SRS16_MAX_BLOCK_LENGTH_2048         (0x2UL << 16)
/// timeout unit clock is MHz
#define SRS16_TIMEOUT_CLOCK_UNIT_MHZ        SD4HC__SRS__SRS16__TCU_MASK
/// this function can be used to get base clock frequency for SD clock,
/// from a value which was read from the SRS16 register
static inline uint32_t SRS16_GET_BASE_CLK_FREQ_MHZ(const uint32_t val)
{
    return ((val & SD4HC__SRS__SRS16__BCSDCLK_MASK) >> SD4HC__SRS__SRS16__BCSDCLK_SHIFT);
}
/// this function can be used to get timeout clock frequency
/// from a value which was read from the SRS16 register
static inline uint32_t SRS16_GET_TIMEOUT_CLK_FREQ(const uint32_t val)
{
    return (val & SD4HC__SRS__SRS16__TCF_MASK);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Capabilities Register #2 Fields  (SRS17) - masks
//-----------------------------------------------------------------------------
//@{
/// VDD2 Supported
#define SRS17_VDD2_ENABLED                  SD4HC__SRS__SRS17__VDD2S_MASK
/// VDD2 Supported
#define SRS17_ADMA3_SUPPORT                 SD4HC__SRS__SRS17__ADMA3SUP_MASK
/// Macro gets value of clock multiplier
static inline uint32_t SRS17_GET_CLOCK_MULTIPLIER(const uint32_t val)
{
    return ((val & SD4HC__SRS__SRS17__CLKMPR_MASK) >> SD4HC__SRS__SRS17__CLKMPR_SHIFT);
}
// Re-Tuning Modes                          SD4HC__SRS__SRS17__RTNGM_MASK
/// Re-Tuning Modes - mode 3
#define SRS17_RETUNING_MODE_3               (0x2UL << 14)
/// Re-Tuning Modes - mode 2
#define SRS17_RETUNING_MODE_2               (0x1UL << 14)
/// Re-Tuning Modes - mode 1
#define SRS17_RETUNING_MODE_1               (0x0UL << 14)
///  tuning operation is necessary in SDR50 mode
#define SRS17_USE_TUNING_SDR50              SD4HC__SRS__SRS17__UTSM50_MASK
/// It gest value of timer Count for Re-Tuning,
static inline uint32_t SRS17_GET_RETUNING_TIMER_COUNT(const uint32_t val)
{
    // (1 << (((val >> 8) & 0xF) - 1))
    uint32_t result = 0x80000000U; // 1 << -1

    uint32_t shift = ((val & SD4HC__SRS__SRS17__RTNGCNT_MASK) >> SD4HC__SRS__SRS17__RTNGCNT_SHIFT);
    if (shift > 0U) {
        shift -= 1U;
        result = (((uint32_t)1U) << shift);
    }

    return (result);
}
/// 1.8V Line Driver Type D Supported
#define SRS17_1_8V_DRIVER_TYPE_D_SUPPORTED  SD4HC__SRS__SRS17__DRVD_MASK
/// 1.8V Line Driver Type C Supported
#define SRS17_1_8V_DRIVER_TYPE_C_SUPPORTED  SD4HC__SRS__SRS17__DRVC_MASK
/// 1.8V Line Driver Type A Supported
#define SRS17_1_8V_DRIVER_TYPE_A_SUPPORTED  SD4HC__SRS__SRS17__DRVA_MASK
/// UHS-II Supported
#define SRS17_UHSII_SUPPORTED               SD4HC__SRS__SRS17__UHSII_MASK
/// DDR50 Supported
#define SRS17_DDR50_SUPPORTED               SD4HC__SRS__SRS17__DDR50_MASK
/// SDR104 Supported
#define SRS17_SDR104_SUPPORTED              SD4HC__SRS__SRS17__SDR104_MASK
/// SDR50 Supported
#define SRS17_SDR50_SUPPORTED               SD4HC__SRS__SRS17__SDR50_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Capabilities Register #3 register (SRS18) - masks
//-----------------------------------------------------------------------------
//@{
/// function gets maximum current in mA for 1.8V
static inline uint32_t SRS18_GET_MAX_CURRENT_1_8V(const uint32_t val)
{
    return (((val & SD4HC__SRS__SRS18__MC18_MASK) >> SD4HC__SRS__SRS18__MC18_SHIFT) * 4U);
}
/// function gets maximum current in mA for 3.0V
static inline uint32_t SRS18_GET_MAX_CURRENT_3_0V(const uint32_t val)
{
    return (((val & SD4HC__SRS__SRS18__MC30_MASK) >> SD4HC__SRS__SRS18__MC30_SHIFT) * 4U);
}
/// function gets maximum current in mA for 3.3V
static inline uint32_t SRS18_GET_MAX_CURRENT_3_3V(const uint32_t val)
{
    return (((val & SD4HC__SRS__SRS18__MC33_MASK) >> SD4HC__SRS__SRS18__MC33_SHIFT) * 4U);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Event Trigger Register  (SRS20) - masks
//-----------------------------------------------------------------------------
//@{
#define SRS20_FORCE_RESPONSE_ERROR              SD4HC__SRS__SRS20__ERESP_FE_MASK
/// Force tuning error event
#define SRS20_FORCE_TUNING_ERROR                SD4HC__SRS__SRS20__ETUNE_FE_MASK
/// Force ADMA Error Event
#define SRS20_FORCE_ADMA_ERROR                  SD4HC__SRS__SRS20__EADMA_FE_MASK
/// Force Auto CMD12 Error Event.
#define SRS20_FORCE_AUTO_CMD12_ERROR            SD4HC__SRS__SRS20__EAC_FE_MASK
/// Force Current Limit Error Event.
#define SRS20_FORCE_CURRENT_LIMIT_ERROR         SD4HC__SRS__SRS20__ECL_FE_MASK
/// Force Data End Bit Error Event
#define SRS20_FORCE_DATA_END_BIT_ERROR          SD4HC__SRS__SRS20__EDEB_FE_MASK
/// Force Data CRC Error Event.
#define SRS20_FORCE_DATA_CRC_ERROR              SD4HC__SRS__SRS20__EDCRC_FE_MASK
/// Force Data Timeout Error Event.
#define SRS20_FORCE_DATA_TIMEOUT_ERROR          SD4HC__SRS__SRS20__EDT_FE_MASK
/// Force Command Index Error Event.
#define SRS20_FORCE_COMMAND_INDEX_ERROR         SD4HC__SRS__SRS20__ECI_FE_MASK
/// Force Command End Bit Error Event.
#define SRS20_FORCE_COMMAND_END_BIT_ERROR       SD4HC__SRS__SRS20__ECEB_FE_MASK
/// Force Command CRC Error Event
#define SRS20_FORCE_COMMAND_CRC_ERROR           SD4HC__SRS__SRS20__ECCRC_FE_MASK
/// Force Command Timeout Error Event.
#define SRS20_FORCE_COMMAND_TIMEOUT_ERROR       SD4HC__SRS__SRS20__ECT_FE_MASK
/// Force Command Not Issued By Auto CMD12 Error Event
#define SRS20_FORCE_CMD_NOT_ISSUED              SD4HC__SRS__SRS20__CNIACE_FE_MASK
/// Force Auto CMD12 Index Error Event.
#define SRS20_FORCE_AUTO_CMD12_INDEX_ERROR      SD4HC__SRS__SRS20__ACIE_FE_MASK
/// Force Auto CMD12 End Bit Error Event.
#define SRS20_FORCE_AUTO_CMD12_END_BIT_ERROR    SD4HC__SRS__SRS20__ACEBE_FE_MASK
/// Force Auto CMD12 CRC Error Event
#define SRS20_FORCE_AUTO_CMD12_CRC_ERROR        SD4HC__SRS__SRS20__ACCE_FE_MASK
/// Force Auto CMD12 Timeout Error Event.
#define SRS20_FORCE_AUTO_CMD12_TIMEOUT_ERROR    SD4HC__SRS__SRS20__ACTE_FE_MASK
/// Force Auto CMD12 Not Executed Event
#define SRS20_FORCE_AUTO_CMD12_NOT_EXECUTED     SD4HC__SRS__SRS20__ACNE_FE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name ADMA Error Status Register (SRS21)
//-----------------------------------------------------------------------------
//@{
/// ADMA Length Mismatch Error
#define SRS21_ADMA_ERR_LENGTH_MISMATCH                SD4HC__SRS__SRS21__EADMAL_MASK
/// ADMA state mask
#define SRS21_ADMA_ERR_STATE_MASK                     SD4HC__SRS__SRS21__EADMAS_MASK
/// ADMA machine Stopped
#define SRS21_ADMA_ERR_STATE_STOP                     (0x0UL << 0)
/// ADMA Fetching descriptor
#define SRS21_ADMA_ERR_STATE_FDS                      (0x1UL << 0)
/// ADMA machine Transfer data
#define SRS21_ADMA_ERR_STATE_TRF                      (0x3UL << 0)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name Capabilities Register #4 register (SRS19) - masks
//-----------------------------------------------------------------------------
//@{
/// macro gets maximum current in mA for 1.8V VDD2
static inline uint32_t SRS19_GET_MAX_CURRENT_1_8V_VDD2(const uint32_t val)
{
    return ((val & SD4HC__SRS__SRS19__MC18V2_MASK) * 4U);
}
//@}


//-----------------------------------------------------------------------------
/// Command Queuing Version Register (CQRS00)- macros
//-----------------------------------------------------------------------------
//@{
//
inline static uint32_t CQRS00_GET_EMMC_MAJOR_VERSION(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS00__CQVN1_MASK) >> SD4HC__CQRS__CQRS00__CQVN1_SHIFT);
}
inline static uint32_t CQRS00_GET_EMMC_MINOR_VERSION(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS00__CQVN2_MASK) >> SD4HC__CQRS__CQRS00__CQVN2_SHIFT);
}
inline static uint32_t CQRS00_GET_EMMC_VERSION_SUFFIX(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS00__CQVN3_MASK) >> SD4HC__CQRS__CQRS00__CQVN3_SHIFT);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Capabilities Register (CQRS01)- macros and masks
//-----------------------------------------------------------------------------
//@{
/// Get Internal Timer Clock Frequency Multiplier
inline static uint32_t CQRS01_GET_ITCFMUL(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS01__ITCFMUL_MASK) >> SD4HC__CQRS__CQRS01__ITCFMUL_SHIFT);
}

#define CQRS01_ITCFMUL_1KHZ                 0
#define CQRS01_ITCFMUL_10KHZ                1
#define CQRS01_ITCFMUL_100KHZ               2
#define CQRS01_ITCFMUL_1MHZ                 3
#define CQRS01_ITCFMUL_10MHZ                4

/// Get Internal Timer Clock Frequency Value
inline static uint32_t CQRS01_GET_ITCFVAL(const uint32_t rv)
{
    return  (rv & 0x3FU);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Configuration (CQRS02)- masks
//-----------------------------------------------------------------------------
//@{
/// Direct Command (DCMD) Enable
#define CQRS02_DIRECT_CMD_ENABLE            SD4HC__CQRS__CQRS02__CQDCE_MASK
/// Task Descriptor Size 128 bits
#define CQRS02_TASK_DESCRIPTOR_SIZE_128     (1UL << 8)
/// Task Descriptor Size 64 bits
#define CQRS02_TASK_DESCRIPTOR_SIZE_64      (0UL << 8)
/// Task Descriptor Size mask
#define CQRS02_TASK_DESCRIPTOR_SIZE_MASK    SD4HC__CQRS__CQRS02__CQTDS_MASK
/// Command Queuing Enable
#define CQRS02_COMMAND_QUEUING_ENABLE       SD4HC__CQRS__CQRS02__CQE_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Control (CQRS03)- masks
//-----------------------------------------------------------------------------
//@{
#define CQRS03_CLEAR_ALL_TASKS              SD4HC__CQRS__CQRS03__CQCAT_MASK
#define CQRS03_HALT                         SD4HC__CQRS__CQRS03__CQHLT_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Interrupt Status (CQRS04)- masks
//-----------------------------------------------------------------------------
//@{
/// Task cleared interrupt
#define CQRS04_TASK_CLEARED_INT             SD4HC__CQRS__CQRS04__CQTCL_MASK
/// Response Error Detected Interrupt
#define CQRS04_RESP_ERR_INT                 SD4HC__CQRS__CQRS04__CQREDI_MASK
/// Task Complete Interrupt
#define CQRS04_TASK_COMPLETE_INT            SD4HC__CQRS__CQRS04__CQTCC_MASK
/// Halt Complete Interrupt
#define CQRS04_HALT_COMPLETE_INT            SD4HC__CQRS__CQRS04__CQHAC_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Interrupt Status Enable (CQRS05)- masks
//-----------------------------------------------------------------------------
//@{
/// Task cleared status enable
#define CQRS05_TASK_CLEARED_STAT_EN         SD4HC__CQRS__CQRS05__CQTCLST_MASK
/// Response Error Detected status enable
#define CQRS05_RESP_ERR_STAT_EN             SD4HC__CQRS__CQRS05__CQREDST_MASK
/// Task Complete status enable
#define CQRS05_TASK_COMPLETE_STAT_EN        SD4HC__CQRS__CQRS05__CQTCCST_MASK
/// Halt Complete status enable
#define CQRS05_HALT_COMPLETE_STAT_EN        SD4HC__CQRS__CQRS05__CQHACST_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Interrupt Signal Enable (CQRS06)- masks
//-----------------------------------------------------------------------------
//@{
/// Task cleared interrupt signal enable
#define CQRS06_TASK_CLEARED_INT_SIG_EN      SD4HC__CQRS__CQRS06__CQTCLSI_MASK
/// Response Error Detected Interrupt signal enable
#define CQRS06_RESP_ERR_INT_SIG_EN          SD4HC__CQRS__CQRS06__CQREDSI_MASK
/// Task Complete Interrupt signal enable
#define CQRS06_TASK_COMPLETE_INT_SIG_EN     SD4HC__CQRS__CQRS06__CQTCCSI_MASK
/// Halt Complete Interrupt signal enable
#define CQRS06_HALT_COMPLETE_INT_SIG_EN     SD4HC__CQRS__CQRS06__CQHACSI_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Interrupt Coalescing (CQRS07)- masks and macros
//-----------------------------------------------------------------------------
//@{
#define CQRS07_INT_COAL_ENABLE                  SD4HC__CQRS__CQRS07__CQICED_MASK
/// Interrupt Coalescing Status Bit
#define CQRS07_INT_COAL_STATUS_BIT              SD4HC__CQRS__CQRS07__CQICSB_MASK
/// Counter and Timer Reset(ICCTR)
#define CQRS07_INT_COAL_COUNTER_TIMER_RESET     SD4HC__CQRS__CQRS07__CQICCTR_MASK
/// Interrupt Coalescing Counter Threshold Write Enable
#define CQRS07_INT_COAL_COUNT_THRESHOLD_WE      SD4HC__CQRS__CQRS07__CQICCTHWEN_MASK
/// Interrupt Coalescing Counter Threshold
inline static uint32_t CQRS07_SET_INT_COAL_COUNT_THRESHOLD(const uint32_t val)
{
    return  ((val & 0x1FU) << SD4HC__CQRS__CQRS07__CQICCTH_SHIFT);
}
inline static uint32_t CQRS07_GET_INT_COAL_COUNT_THRESHOLD(const uint32_t reg)
{
    return ((reg & SD4HC__CQRS__CQRS07__CQICCTH_MASK) >> SD4HC__CQRS__CQRS07__CQICCTH_SHIFT);
}
#define CQRS07_INT_COAL_COUNT_THRESHOLD_MASK    SD4HC__CQRS__CQRS07__CQICCTH_MASK
/// Interrupt Coalescing Timeout Value write enable mask
#define CQRS07_INT_COAL_TIMEOUT_WE              SD4HC__CQRS__CQRS07__CQICTOVALEN_MASK
/// Interrupt Coalescing Timeout Value
inline static uint32_t CQRS07_SET_INT_COAL_TIMEOUT_VAL(const uint32_t val)
{
    return  (val & SD4HC__CQRS__CQRS07__CQICTOVAL_MASK);
}
inline static uint32_t CQRS07_GET_INT_COAL_TIMEOUT_VAL(const uint32_t reg)
{
    return  (reg & SD4HC__CQRS__CQRS07__CQICTOVAL_MASK);
}
#define CQRS07_INT_COAL_TIMEOUT_VAL_MASK        SD4HC__CQRS__CQRS07__CQICTOVAL_MASK
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Task Doorbell (CQRS10)- macro
//-----------------------------------------------------------------------------
//@{
inline static uint32_t CQRS10_SET_TASK_DORBELL(const uint32_t taskId)
{
    uint32_t result = 0U;

    const uint32_t shift = (taskId & 0xFFU);
    if (shift < 32U) {
        result = ((uint32_t)1U << shift);
    }

    return  (result);
}
inline static uint32_t CQRS10_GET_TASK_DORBELL(const uint32_t rv, const uint32_t taskId)
{
    uint32_t result = 0U;

    if (taskId < 32U) {
        result = ((rv >> taskId) & 0x1U);
    }

    return (result);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Queuing Task Notification (CQRS11)- macros
//-----------------------------------------------------------------------------
//@{
/// Task Completion Notification
inline static uint32_t CQRS11_SET_TASK_COMPL(const uint32_t taskId)
{
    uint32_t result = 0U;

    const uint32_t shift = (taskId & 0xFFU);
    if (shift < 32U) {
        result = ((uint32_t)1U << shift);
    }

    return (result);
}
/// Task Completion Notification
inline static uint32_t CQRS11_GET_TASK_COMPL(const uint32_t rv, const uint32_t taskId)
{
    uint32_t result = 0U;

    const uint32_t shift = (taskId & 0xFFU);
    if (shift < 32U) {
        result = ((rv >> shift) & 1U);
    }

    return (result);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Device Pending Tasks (CQRS13)- macro
//-----------------------------------------------------------------------------
//@{
/// Get gending task status
inline static uint32_t CQRS13_GET_TASK_PEND(const uint32_t rv, const uint32_t taskId)
{
    uint32_t result = 0U;

    const uint32_t shift = (taskId & 0xFFU);
    if (shift < 32U) {
        result = ((rv >> shift) & 1U);
    }

    return (result);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Task Clear (CQRS14)- macros
//-----------------------------------------------------------------------------
//@{
/// Set Command Queuing Task Clear #TASK_ID
inline static uint32_t CQRS14_SET_TASK_CLEAR(const uint32_t taskId)
{
    uint32_t result = 0U;

    const uint32_t shift = (taskId & 0xFFU);
    if (shift < 32U) {
        result = ((uint32_t)1U << shift);
    }

    return (result);
}
/// Get Command Queuing Task Clear #TASK_ID
inline static uint32_t CQRS14_GET_TASK_CLEAR(const uint32_t rv, const uint32_t taskId)
{
    uint32_t result = 0U;

    const uint32_t shift = (taskId & 0xFFU);
    if (shift < 32U) {
        result = ((rv >> shift) & 1U);
    }

    return (result);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Send Status Configuration 1 (CQRS16)- macros
//-----------------------------------------------------------------------------
//@{
///  Send Status Command Block Counter (CBC)
inline static uint32_t CQRS16_SET_CMD_BLOCK_COUNTER(const uint32_t val)
{
    return  ((val & 0xFU) << SD4HC__CQRS__CQRS16__CQSSCBC_SHIFT);
}
inline static uint32_t CQRS16_GET_CMD_BLOCK_COUNTER(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS16__CQSSCBC_MASK) >> SD4HC__CQRS__CQRS16__CQSSCBC_SHIFT);
}
/// Send Status Command Idle Timer (CIT)
inline static uint32_t CQRS16_SET_CMD_IDLE_TIMER(const uint32_t val)
{
    return  (val & SD4HC__CQRS__CQRS16__CQSSCIT_MASK);
}
inline static uint32_t CQRS16_GET_CMD_IDLE_TIMER(const uint32_t rv)
{
    return (rv & SD4HC__CQRS__CQRS16__CQSSCIT_MASK);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Send Status Configuration 2 (CQRS17)- macro
//-----------------------------------------------------------------------------
//@{
/// Send Queue Status RCA
inline static uint32_t CQRS17_SET_RCA(const uint32_t rca)
{
    return (rca & SD4HC__CQRS__CQRS17__CQSQSR_MASK);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Task Error Information (CQRS21)- macros
//-----------------------------------------------------------------------------
//@{
/// Data Transfer Error Fields Valid
#define CQRS21_DT_ERR_FIELDS_RVID          SD4HC__CQRS__CQRS21__CQDTEFV_MASK
/// Get Data Transfer Error Task ID
inline static uint32_t CQRS21_GET_DT_ERR_TASK_ID(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS21__CQDTETID_MASK) >> SD4HC__CQRS__CQRS21__CQDTETID_SHIFT);
}
/// Get - Data Transfer Error Command Index
inline static uint32_t CQRS21_GET_DT_ERR_CMD_IDX(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS21__CQDTECI_MASK) >> SD4HC__CQRS__CQRS21__CQDTECI_SHIFT);
}
/// Response Mode Error Fields Valid
#define CQRS21_RM_ERR_FIELDS_RVID          SD4HC__CQRS__CQRS21__CQRMEFV_MASK
/// Get Response Mode Error Task ID
inline static uint32_t CQRS21_GET_RM_ERR_TASK_ID(const uint32_t rv)
{
    return ((rv & SD4HC__CQRS__CQRS21__CQRMETID_MASK) >> SD4HC__CQRS__CQRS21__CQRMETID_SHIFT);
}
/// Get Response Mode Error Command Index
inline static uint32_t CQRS21_GET_RM_ERR_CMD_IDX(const uint32_t rv)
{
    return  (rv & SD4HC__CQRS__CQRS21__CQRMECI_MASK);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Command Response Index (CQRS22)- macros
//-----------------------------------------------------------------------------
//@{
inline static uint32_t CQRS22_GET_LAST_CMD_IDX(const uint32_t rv)
{
    return  (rv & SD4HC__CQRS__CQRS22__CQLCRI_MASK);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @anchor WakeupCondition
/// @name Wakeup condition definition
//-----------------------------------------------------------------------------
//@{
/// Wake up host when card is instert
#define SDIOHOST_WAKEUP_COND_CARD_INS       0x1U
/// Wake up host when card is remove
#define SDIOHOST_WAKEUP_COND_CARD_REM       0x2U
/// Wake up host when card interrupt occur
#define SDIOHOST_WAKEUP_COND_CARD_INT       0x4U
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name CCCR transfer direction definitions
//-----------------------------------------------------------------------------
//@{
/// Read data from CCCR register
#define SDIOHOST_CCCR_READ  0
/// Write data to CCCR register
#define SDIOHOST_CCCR_WRITE 1
//@}
//-----------------------------------------------------------------------------

/// Maximum size of response in bytes
#define MAX_CARD_RESPONSE_BYTES 120

#if 0
inline static bool IS_CARD_WRITE_PROTECT(const CSDD_SDIO_Slot* pSlot) {
    return ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09) & SRS9_WP_SWITCH_LEVEL) == 0U);
}
#else
inline static bool IS_CARD_WRITE_PROTECT(const CSDD_SDIO_Slot* pSlot) {
    return ((CPS_REG_READ(&pSlot->RegOffset->SRS.SRS09) & SRS9_WP_SWITCH_LEVEL) != 0U);
}
#endif

/// List of supported SDIO devices.
/// If once create a driver for a SDIO device then should add this device
/// to the list. First element is a head and it's item is always NULL
extern LIST_NODE *SuppDevList;

/*****************************************************************************/
/*!
 * @fn          void SDIOHost_ExecCardCommand( CSDD_SDIO_Slot* pSlot,
 *                                           CSDD_Request* pRequest )
 * @brief       Function executes request given as a parameter.
 *              All commands should be executeby using this function.
 * @param       pSlot Slot on which request shall be executed
 * @param       pRequest Request to execute.
 */
/*****************************************************************************/
void SDIOHost_ExecCardCommand( CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest );

void SDIOHost_ExecCardCmdFiniteNonApp(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest);

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_DeviceAttach( CSDD_SDIO_Slot* pSlot )
 * @brief       Function initializes new inserted card and
 *              gathers informations about it.
 * @param       pSlot Slot in which card was inserted.
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_DeviceAttach( CSDD_SDIO_Slot* pSlot );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_DeviceDetach( CSDD_SDIO_Slot* pSlot )
 * @brief       Function detaches card.
 * @param       pSlot Slot from which card was removed.
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_DeviceDetach( CSDD_SDIO_Slot* pSlot );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_HostInitialize(CSDD_SDIO_Host* pSdioHost)
 * @brief       Function initializes the SDIO host.
 *              It Creates slot structures.
 *              One structure per each one hardware slot.
 *              This function has to be called as a first function
 *              before call other functions.
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_HostInitialize(CSDD_SDIO_Host* pSdioHost);

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_Abort( CSDD_SDIO_Slot* pSlot,
 *                                   uint8_t IsSynchronous )
 * @brief       Function aborts transfer.
 * @param       pSlot Slot on which transfer shall be aborted.
 * @param       IsSynchronous This parameter defines abort type:
 *              synchronous or asynchronous
 * @remarks     Function shouldn't be used in recorvery error procedure
 *              it shlud be used only to abort data transmission
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_Abort( CSDD_SDIO_Slot* pSlot, uint8_t IsSynchronous );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_Standby( CSDD_SDIO_Slot* pSlot,
 *                                     uint8_t WakeupCondition )
 * @brief       Function sets slot of SDIO controller to standby mode,
 *              and waits for wakeup condition. In standby mode clock
 *              is disable.
 * @param       pSlot Slot which we want set to standby mode
 * @param       WakeupCondition Codnditions of wakeup
 *              from standby mode. It is logical sum of conditions.
 *              All of them are defined here @ref WakeupCondition.
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_Standby( CSDD_SDIO_Slot* pSlot, uint8_t WakeupCondition );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_Configure( CSDD_SDIO_Slot* pSlot,
 *                                       CSDD_ConfigCmd Cmd,
 *                                       void *Data,
 *                                       const uint8_t *SizeOfData )
 * @brief       Function changes configuration of a slot.
 * @param       pSlot Slot which we want to configure
 * @param       Cmd This paramater defines what configuration
 *                  shall be changed see  @ref HostConfigureCmd
 *                  to check aviable commands
 * @param       Data Pointer to configuration data
 * @param       SizeOfData Size of Data parameter
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_Configure( CSDD_SDIO_Slot* pSlot, CSDD_ConfigCmd Cmd,
                            void *Data, const uint8_t *SizeOfData );

/*****************************************************************************/
/*!
 * @fn      void SDIOHost_InterruptHandler( CSDD_SDIO_Host *pSdioHost )
 * @param   pSdioHost SDIO Host object
 * @param   Handled flag informs if interrupt ocurred
 * @brief   Interrupt handler function, calls always when
 *              interrupt SDIO host controller occurs
 */
/*****************************************************************************/
void SDIOHost_InterruptHandler( CSDD_SDIO_Host *pSdioHost, uint8_t *Handled);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ConfigureHighSpeed( CSDD_SDIO_Slot* pSlot,
 *                                           bool SetHighSpeed )
 * @brief   Function switches a card to high speed mode or to normal mode
 * @param   pSlot Slot in which card is present
 * @param   SetHighSpeed This parameter defines if high speed mode
 *                          should be enabled ( SetHighSpeed = 1 )
 *                          or disbled ( SetHighSpeed = 0 )
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ConfigureHighSpeed( CSDD_SDIO_Slot* pSlot, bool SetHighSpeed );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_AddItem( LIST_NODE *ListHead,
 *                                     CSDD_DeviceInfo* Item)
 *
 * @brief       Function adds new element to the ListHead list
 * @param       ListHead Pointer to head of list to which
 *                  new element shall be added
 * @param       Item Pointer to object which shall be added to the list
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_AddItem( LIST_NODE *ListHead, CSDD_DeviceInfo* Item);

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_RemoveItem( LIST_NODE *ListHead,
 *                                        const CSDD_DeviceInfo* Item )
 *
 * @brief       Function remove one item from list
 * @param       ListHead pointer to head of list
 *                  from which item shall be removed
 * @param       Item Pointer to item which we want to remove
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_RemoveItem( LIST_NODE *ListHead, const CSDD_DeviceInfo* Item );

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_CheckSlots(CSDD_SDIO_Host* pSdioHost)
 *
 * @brief   Function check all slots state and if it is needed
 *              attaches new devices or detaches devices which are
 *              removed.
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_CheckSlots(CSDD_SDIO_Host* pSdioHost);

/*****************************************************************************/
/*!
 * \def     CHECK_BUSY( Status )
 * \brief   Marco waits until Status is pending and examines
 *              DSR buffer to check if there is a interrupt in it
 *              to service and if it is then macro calls
 *              the SDIOHost_CheckInterrupt procedure.
 *              Marco do nothing if interrupt support is disbled
 *              in the configuration file.
 * \param       Status parameter which is checking in while loop
 */
/*****************************************************************************/

#ifndef IDLE
#   define IDLE()
#endif

/*****************************************************************************/
/*!
 * @fn          void SDIOHost_CheckInterrupt( CSDD_SDIO_Slot* pSlot,
 *                                            uint32_t status )
 *
 * @brief       Function checks one interrupt source
 *                  and on a base of a SlotStatus
 *                  (read from SRS12 register)
 *                  executes proper operations
 * @param       pSlot on which interrupt occured
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
void SDIOHost_CheckInterrupt( CSDD_SDIO_Slot* pSlot, uint32_t status );

/*****************************************************************************/
/*!
 * @fn      CSDD_SDIO_Device* SDIOHost_GetDeviceFromSlot(CSDD_SDIO_Host* pSdioHost,
 *                                                      uint8_t SlotNumber )
 *
 * @brief   Function check the SlotNumber and if it is smaller than
 *              number of all slots then return handle to card device.
 *              If card is not inserted or unatached then card device
 *              will be null device.
 *
 * @param   SlotNumber It is a slot number from which we want to get
 *              a device handle. It can be 0.. slots count. Slots
 *              count depend on SDIO host controller implementation.
 * @return  Function returns handle to the device from slot
 *              which number is given as SlotNumber parameter.
 *              If slot number is to big then function returns pointer
 *              to null device.
 */
/*****************************************************************************/
CSDD_SDIO_Device* SDIOHost_GetDeviceFromSlot(CSDD_SDIO_Host* pSdioHost,
                                        uint8_t    SlotNumber );
/*****************************************************************************/
/*!
 * @fn      static uint8_t SDIOHost_CheckError(CSDD_SDIO_Slot* pSlot)
 *
 * @brief   Function checks what error occurs.
 * @param   pSlot Slot in which error is checking
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_CheckError(CSDD_SDIO_Slot* pSlot);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ConfigureAccessMode(CSDD_SDIO_Slot* pSlot,
 *                                                CSDD_SpeedMode AccessMode)
 *
 * @brief   Function configures card access mode (UHS-I mode)
 * @param   AccessMode access mode to set
 * @param   pSlot slot object to change its configurations
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ConfigureAccessMode(CSDD_SDIO_Slot* pSlot, CSDD_SpeedMode AccessMode);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_Tuning(CSDD_SDIO_Slot* pSlot)
 *
 * @brief   Function executes tuning operation on a card if it is needed
 * @param   pSlot slot object execute tuning on
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_Tuning(CSDD_SDIO_Slot* pSlot);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ClockGeneratorSelect(CSDD_SDIO_Slot* pSlot,
 *                                              uint8_t ProgClkMode)
 *
 * @brief   Function enables or disables clock mode with multiplayer
 * @param   pSlot slot object to change its configurations
 * @param   ProgClkMode parameter defines if programmable clock mode should
 *              be enabled.
 *              1 - programmable clock mode will be enabled
 *              0 - 10-bit divider clock mode is enabled
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ClockGeneratorSelect(CSDD_SDIO_Slot* pSlot, uint8_t ProgClkMode);

/*****************************************************************************/
/*!
 * @fn      void SDIOHost_PresetValueSwitch(CSDD_SDIO_Slot* pSlot, bool Enable)
 *
 * @brief   Function enables or disables preset value switching
 * @param   pSlot slot object to change its configurations
 * @param   Enable parameter defines enable or disable
 *              preset value switching
 *              1 - enable preset value switching
 *              0 - disable preset value switching
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
void SDIOHost_PresetValueSwitch(CSDD_SDIO_Slot* pSlot, bool Enable);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ConfigureDrvStrength(CSDD_SDIO_Slot* pSlot,
 *                                                   CSDD_DriverStrengthType DriverStrength)
 *
 * @brief   Function configures driver strength of a card and the slot
 * @param   pSlot slot object to change its configurations
 * @param   DriverStrength value of new driver strength
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ConfigureDrvStrength(CSDD_SDIO_Slot* pSlot, CSDD_DriverStrengthType DriverStrength);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ChangeSDCLK(CSDD_SDIO_Slot* pSlot, uint32_t *FrequencyKHz)
 *
 * @brief   Function configures SD clock with new frequency. But clock is not
 *              enabled. To enable clock SDIOHost_SupplySDCLK must be called.
 * @param   pSlot slot object to change its configurations
 * @param   FrequencyKHz frequency to set. Also set frequency is returned by
 *              function.
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ChangeSDCLK(CSDD_SDIO_Slot* pSlot, uint32_t *FrequencyKHz);

/*****************************************************************************/
/*!
 * @fn      void SDIOHost_SupplySDCLK(CSDD_SDIO_Slot* pSlot, uint8_t Enable)
 *
 * @brief   Function enables or disables clock
 *              depending on the Enable parameter
 * @param   pSlot slot object to change its configurations
 * @param   Enable - if it is 1 enable clock, if 0 disable clock
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
void SDIOHost_SupplySDCLK(CSDD_SDIO_Slot* pSlot, uint8_t Enable);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_SetPower (CSDD_SDIO_Slot* pSlot, uint32_t Voltage)
 *
 * @brief   Function changes host slot power settings
 * @param   pSlot slot to change configuration
 * @param   Voltage new voltage settings
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_SetPower (CSDD_SDIO_Slot* pSlot, uint32_t Voltage);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_SlotInitialize(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_Host* pSdioHost)
 *
 * @brief   Function initilaizes one slot.
 * @param   pSlot slot to initialize
 * @param   pSdioHost host which contains the slot
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_SlotInitialize(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_Host* pSdioHost);

/*****************************************************************************/
/*!
 * @fn      uint8_t ResetHost(CSDD_SDIO_Host* pSdioHost)
 *
 * @brief   Function executes hard reset on the host controller.
 * @param   pSdioHost host on which operation shall be executed
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t ResetHost(CSDD_SDIO_Host* pSdioHost);

uint8_t SDIOHost_InterruptConfig(CSDD_SDIO_Slot* pSlot, uint8_t enable);

uint8_t ResetLines(CSDD_SDIO_Slot* pSlot, uint8_t cmd, uint8_t dat);

uint8_t CheckResponseError(const uint32_t *Response, uint8_t ResponseType,
                           const CSDD_SDIO_Slot* pSlot);

void SDIOHost_CheckBusy(CSDD_SDIO_Host* pSdioHost, CSDD_Request* pRequest);

uint8_t SDIOHost_GetBaseClk(CSDD_SDIO_Slot* pSlot, uint32_t *frequencyKHz);

uint8_t SDIOHost_MmcTune(const CSDD_SDIO_Host* pSdioHost, uint8_t value);
uint32_t SDIOHost_ExecCardCommand_ProcessRequestCheckRespType(CSDD_ResponseType responseType, uint8_t* BusyCheck);

#endif
