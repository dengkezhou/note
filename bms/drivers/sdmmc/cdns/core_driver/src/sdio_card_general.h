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
 * sdio_card_general.h
 * sdio/sd/emmc device general functions
 *****************************************************************************/

#ifndef SDIO_CARD_GENERAL_H
#define SDIO_CARD_GENERAL_H

#include "sdio_utils.h"
#ifndef SDIO_CFG_ENABLE_IO
    #error "SDIO_CFG_ENABLE_IO should be defined explicitly"
#endif

//---------------------------------------------------------------------------
/// @name Commands definitions
//---------------------------------------------------------------------------
//@{
/// Reset SD card, go to idle state
#define SDIO_CMD0    0U
/// Asks the card, in idle state, to send its Operating Conditions Register contents in the response on the SDIO_CMD line.
#define SDIO_CMD1    1U
/// Asks the card to send its CID number on the SDIO_CMD line
#define SDIO_CMD2    2U
/// Assigns relative address to the card
#define SDIO_CMD3    3U
/// Programs the DSR of the card
#define SDIO_CMD4    4U
/// It is used to inquire about the voltage range needed by the I/O card
#define SDIO_CMD5    5U
/// Switch function command it is used to switch or expand memory card functions
#define SDIO_CMD6    6U
/// Command toggles a card between the stand-by and transfer states or between the programming and disconnect states.
#define SDIO_CMD7    7U
/// Sends SD Memory Card interface condition, which includes host supply voltage information and asks the card whether card supports voltage.
#define SDIO_CMD8    8U
/// Addressed card sends its card-specific data (CSD) on the SDIO_CMD line.
#define SDIO_CMD9    9U
/// Addressed card sends its card identification (CID) on SDIO_CMD the line.
#define SDIO_CMD10   10U
/// Reads data stream from the card, starting at the given address, until a STOP_TRANSMISSION follows. (MMC card only)
#define SDIO_CMD11   11U
/// Forces the card to stop transmission
#define SDIO_CMD12   12U
/// Addressed card sends its status register.
#define SDIO_CMD13   13U
/// A host reads the reversed bus testing data pattern from a card. (MMC card only)
#define SDIO_CMD14   14U
/// Sets the card to inactive state
#define SDIO_CMD15   15U
/// Setss the block length of the SD/SDIO card
#define SDIO_CMD16   16U
/// Reads a block of the size selected by the SET_BLOCKLEN command.
#define SDIO_CMD17   17U
/// Continuously transfers data blocks from card to host until interrupted by a stop command,
#define SDIO_CMD18   18U
/// A host sends the bus test data pattern to a card. (MMC card only)
#define SDIO_CMD19   19U
///  Writes a data stream from the host, starting at the given address, until a STOP_TRANSMISSION follows. (MMC card only)
#define SDIO_CMD20   20U
///  send tuning block (MMC card only)
#define SDIO_CMD21   21U
/// Defines the number of blocks which are going to be transferred in the immediately succeeding multiple block read or write command.(MMC card only)
#define SDIO_CMD23   23U
/// Writes a block of the size selected by the SET_BLOCKLEN command.
#define SDIO_CMD24   24U
/// Continuously writes blocks of data until a STOP_TRANSMISSION follows or the requested number of block received.
#define SDIO_CMD25   25U
/// Programming of the programmable bits of the CSD.
#define SDIO_CMD27   27U
/// If the card has write protection features, this command sets the write protection bit of the addressed group.
#define SDIO_CMD28   28U
/// If the card provides write protection features, this command clears the write protection bit of the addressed group.
#define SDIO_CMD29   29U
/// Ask the card to send the status of the write protection. (If card support write protection)
#define SDIO_CMD30   30U
/// Sets the address of the first write block to be erased.
#define SDIO_CMD32   32U
/// Sets the address of the last write block of the continuous range to be erased.
#define SDIO_CMD33   33U
/// Sets the address of the first write block to be erased for MMC device
#define SDIO_CMD35   35U
/// Sets the address of the last write block of the continuous range to be erased for MMC device
#define SDIO_CMD36   36U
/// Erases all previously selected write blocks.
#define SDIO_CMD38   38U
/// Used to set/reset the password or lock/unlock the card. The size of the data block is set by the SET_BLOCK_LEN command.
#define SDIO_CMD42   42U
/// Access a single register within the total 128K of register space
#define SDIO_CMD52   52U
/// Extended access a single register within the total 128K of register space
#define SDIO_CMD53   53U
/// Commmand informs that the next command is an application specific command rather than a standard command
#define SDIO_CMD55   55U
/// Used either to transfer a data block to the card or to get a data block from the card for general purpose/application specific commands.
#define SDIO_CMD56   56U
/// Read OCR register in SPI mode
#define SDIO_CMD58   58U
/// Turns the CRC option on or off in SPI mode
#define SDIO_CMD59   59U
/// Set the data bus width.
#define SDIO_ACMD6   6U
/// Read SD card status
#define SDIO_ACMD13  13U
/// Command is used to get the number of the written (without errors) write blocks. Responds with 32bit+CRC data block.
#define SDIO_ACMD22  22U
/// Set the number of write blocks to be preerased before writing
#define SDIO_ACMD23  23U
/// Sends host capacity support information (HCS) and asks the accessed card
/// to send its operating condition register (OCR) content in the response on the CMD line.
#define SDIO_ACMD41  41U
/// Connect[1]/Disconnect[0] the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card.
#define SDIO_ACMD42  42U
/// Reads the SD Configuration Register (SCR).
#define SDIO_ACMD51  51U
/// EMMC Command queueing task management
#define SDIO_CMD48   48U
//}@
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name OCR register bits defnitions of SD memory cards
//---------------------------------------------------------------------------
//{@
#define SDCARD_REG_OCR_2_7_2_8  (1UL << 15)
#define SDCARD_REG_OCR_2_8_2_9  (1UL << 16)
#define SDCARD_REG_OCR_2_9_3_0  (1UL << 17)
#define SDCARD_REG_OCR_3_0_3_1  (1UL << 18)
#define SDCARD_REG_OCR_3_1_3_2  (1UL << 19)
#define SDCARD_REG_OCR_3_2_3_3  (1UL << 20)
#define SDCARD_REG_OCR_3_3_3_4  (1UL << 21)
#define SDCARD_REG_OCR_3_4_3_5  (1UL << 22)
#define SDCARD_REG_OCR_3_5_3_6  (1UL << 23)
/// Switching to 1.8V request
#define SDCARD_REG_OCR_S18R     (1UL << 24)
/// Switching to 1.8V accepted
#define SDCARD_REG_OCR_S18A     (1UL << 24)
/// SDXC power controll (0 - power saving, 1 - maximum performance)
/// (this bit is not aviable in the SDIO cards)
#define SDCARD_REG_OCR_XPC      (1UL << 28)
/// card capacity status (this bit is not aviable in the SDIO cards)
#define SDCARD_REG_OCR_CCS      (1UL << 30)
/// card power up busy status (this is not aviable in the SDIO cards)
#define SDCARD_REG_OCR_READY    (1UL << 31)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name SCR register bits defnitions and slot masks
//---------------------------------------------------------------------------
//@{

/// CMD20 (speed class controll) command is supported by card
#define SDCARD_REG_CMD20                (1UL << 0)
/// CMD23 (set block count) command is supported by card
#define SDCARD_REG_CMD23                (1UL << 1)
static inline uint32_t SDCARD_REG_GET_EXT_SECURITY(uint32_t x)
{
    return ((x >> 11) & 0xFU);
}
///
#define SDCARD_REG_SD_SPEC3_SUPPORT     (1UL << 15)

/// SD supported bus width 1 bit
#define SDCARD_REG_SCR_SBW_1BIT         (1UL << 16)
/// SD supported bus width 4 bit
#define SDCARD_REG_SCR_SBW_4BIT         (4UL << 16)
/// SD bus width mask
#define SDCARD_REG_SCR_SBW_MASK         0x000F0000UL
/// SD security mask
#define SDCARD_REG_SCR_SEC_MASK         0x00700000UL
/// SD security - no security
#define SDCARD_REG_SCR_SEC_NO           0x00000000UL
/// SD security version 1.01
#define SDCARD_REG_SCR_SEC_VER_101      0x00200000UL
/// SD security version 2.00
#define SDCARD_REG_SCR_SEC_VER_200      0x00300000UL
/// Data state after erase is 1
#define SDCARD_REG_SCR_DSAE_1           0x00800000UL
/// Physical Layer Specification Version supported by the card mask.
#define SDCARD_REG_SCR_SPEC_MAS         0x0F000000UL
/// Physical Layer Specification Version 1.00 - 1.01
#define SDCARD_REG_SCR_SPEC_VER_100     0x00000000UL
/// Physical Layer Specification Version 1.10
#define SDCARD_REG_SCR_SPEC_VER_110     0x01000000UL
/// Physical Layer Specification Version 2.00
#define SDCARD_REG_SCR_SPEC_VER_200     0x02000000UL
/// Physical Layer Specification mask
#define SDCARD_REG_SCR_SPEC_VER_MASK    0x0F000000UL
/// SCR structure mask
#define SDCARD_REG_SCR_STRUCTURE_MASK   0xF0000000UL
/// SCR version 1.0
#define SDCARD_REG_SCR_VER_10           0x00000000UL
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Response R4 bit definitions
//---------------------------------------------------------------------------
//@{
/// card ready bit
#define SDCARD_R4_CARD_READY        (1UL << 31)
/// memory present bit
#define SDCARD_R4_MEMORY_PRESENT    (1UL << 27)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Command masks
//---------------------------------------------------------------------------
//@{
/// host hight capacity support -
#define SDCARD_ACMD41_HCS   (1UL << 30)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Response SPI R1 for SD memory cards bits defnitions
//---------------------------------------------------------------------------
//@{
/// The card is in idle state and running the initializing process.
#define SDCARD_RESP_R1_IDLE                 0x01U
/// An erase sequence was cleared before executing because an out of erase sequence command was received.
#define SDCARD_RESP_R1_ERASE_RESET          0x02U
/// An illegal command code was detected.
#define SDCARD_RESP_R1_ILLEGAL_CMD_ERR      0x04U
/// The CRC check of the last command failed.
#define SDCARD_RESP_R1_COM_CRC_ERR          0x08U
/// An error in the sequence of erase commands occurred.
#define SDCARD_RESP_R1_ERASE_SEQUENCE_ERR   0x10U
/// A misaligned address that did not match the block length was used in the command.
#define SDCARD_RESP_R1_ADDRESS_ERR          0x20U
/// The command's argument (e.g. address, block length) was outside the allowed
#define SDCARD_RESP_R1_PARAM_ERR            0x40U
/// All errors mask
#define SDCARD_RESP_R1_ALL_ERRORS           (SDCARD_RESP_R1_ILLEGAL_CMD_ERR \
                                             | SDCARD_RESP_R1_COM_CRC_ERR \
                                             | SDCARD_RESP_R1_ERASE_SEQUENCE_ERR \
                                             | SDCARD_RESP_R1_ADDRESS_ERR \
                                             | SDCARD_RESP_R1_PARAM_ERR)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Response SPI modified R1 for SDIO cards bit defnitions,
// These bits are a part of the R5 response in SPI mode as also
//---------------------------------------------------------------------------
//@{
/// The card is in idle state and running the initializing process.
#define SDCARD_RESP_MOD_R1_IDLE                 0x01U
/// An illegal command code was detected.
#define SDCARD_RESP_MOD_R1_ILLEGAL_CMD_ERR      0x04U
/// The CRC check of the last command failed.
#define SDCARD_RESP_MOD_R1_COM_CRC_ERR          0x08U
///  Function number error
#define SDCARD_RESP_MOD_R1_FUN_NUMB_ERR         0x10U
/// A misaligned address that did not match the block length was used in the command.
#define SDCARD_RESP_MOD_R1_PARAM_ERR            0x40U
/// All errors mask
#define SDCARD_RESP_MOD_R1_ALL_ERRORS       (SDCARD_RESP_MOD_R1_ILLEGAL_CMD_ERR \
                                             | SDCARD_RESP_MOD_R1_COM_CRC_ERR \
                                             | SDCARD_RESP_MOD_R1_FUN_NUMB_ERR \
                                             | SDCARD_RESP_MOD_R1_PARAM_ERR)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name R5 response flags bit definitions
//---------------------------------------------------------------------------
//@{
/// The command's argument was out of the allowed range for this card.
#define SDCARD_R5_FLAGS_OUT_OF_RANGE_ERR    0x0100U
/// An invalid function number was requested
#define SDCARD_R5_FLAGS_FUNC_NUMB_ERR       0x0200U
/// A general or an unknown error occurred during the operation
#define SDCARD_R5_FLAGS_GENERAL_ERR         0x0800U
/// IO current state - disabled
#define SDCARD_R5_FLAGS_STATE_DIS           0x0000U
/// IO current state - DAT line is free
#define SDCARD_R5_FLAGS_STATE_CMD           0x1000U
/// IO current state -  Command executing with data transfer using DAT[0] or DAT[3:0] lines
#define SDCARD_R5_FLAGS_STATE_TRN           0x2000U
/// Command not legal for the card state
#define SDCARD_R5_FLAGS_ILLEGAL_CMD_ERR     0x4000U
/// The CRC check for the previous command failed
#define SDCARD_R5_FLAGS_COM_CRC_ERR         0x8000U
/// All flags mask
#define SDCARD_R5_FLAGS_ALL                 0xFF00U
// All error flags mask
#define SDCARD_R5_FLAGS_ALL_ERROR           (SDCARD_R5_FLAGS_OUT_OF_RANGE_ERR \
                                             | SDCARD_R5_FLAGS_FUNC_NUMB_ERR \
                                             | SDCARD_R5_FLAGS_GENERAL_ERR \
                                             | SDCARD_R5_FLAGS_ILLEGAL_CMD_ERR \
                                             | SDCARD_R5_FLAGS_ILLEGAL_CMD_ERR)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Bus interface control register bit definitions
//---------------------------------------------------------------------------
//@{
/// Data 4 bit bus width
#define SDCARD_BIS_BUS_WIDTH_4BIT   0x02U
/// Data 1 bit bus width
#define SDCARD_BIS_BUS_WIDTH_1BIT   0x00U
/// Connect[0]/Disconnect[1] the 10K-90K ohm pull-up resistor on CD/DAT[3]
/// (pin 1) of card.
#define SDCARD_BIS_CD_DISABLE       0x80
/// Support contiunous SPI interrupt (irrespective of the state the CS line)
#define SDCARD_BIS_SCSI             0x40
/// Enable contiunous SPI interrupt (irrespective of the state the CS line)
#define SDCARD_BIS_ECSI             0x20
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Card capability register bit definitions
//---------------------------------------------------------------------------
//@{
/// Card supports direct commands during data trnsfer. (only in SD mode)
#define SDCARD_CCR_SDC  0x01U
/// Card supports multiblock
#define SDCARD_CCR_SMB  0x02U
/// Card supports read wait
#define SDCARD_CCR_SRW  0x04U
/// Card supports Suspend/Resume
#define SDCARD_CCR_SBS  0x08U
/// Card supports interrupt between blocks of data in 4-bit SD mode.
#define SDCARD_CCR_S4MI 0x10U
/// Enable interrupt between blocks of data in 4-bit SD mode.
#define SDCARD_CCR_E4MI 0x20U
/// Card is a low-speed card
#define SDCARD_CCR_LSC  0x40U
/// 4 bit support for Low-Speed cards
#define SDCARD_CCR_4BLS 0x80U
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Bus suspend register bit definitions
//---------------------------------------------------------------------------
//@{
/// Bus status. Currently addressed function is transferring dara on the DAT line.
#define SDCARD_BS_BS    0x01U
/// Bus release request/status. This bit is used to request that the addressed function to suspend operation.
#define SDCARD_BS_BR    0x02U
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Power control register bit definitions
//---------------------------------------------------------------------------
//@{
/// Support master power control.
#define SDCARD_PC_SMPC  0x01U
/// Enable master power control.
#define SDCARD_PC_EMPC  0x02U
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Bus speed register bit definitions
//---------------------------------------------------------------------------
//@{
/// Support high speed.
#define SDIO_CCCR_13_SHS          0x01U
/// Enable high speed.
#define SDIO_CCCR_13_EHS          0x02U

#define SDIO_CCCR_13_BSS_MASK     (0x7U << 1)
#define SDIO_CCCR_13_BSS_SDR12    (0x0U << 1)
#define SDIO_CCCR_13_BSS_SDR25    (0x1U << 1)
#define SDIO_CCCR_13_BSS_SDR50    (0x2U << 1)
#define SDIO_CCCR_13_BSS_SDR104   (0x3U << 1)
#define SDIO_CCCR_13_BSS_DDR50    (0x4U << 1)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name USH-I suport bits register 0x14
//---------------------------------------------------------------------------
//@{
#define SDIO_CCCR_14_SSDR50       (0x1U << 0)
#define SDIO_CCCR_14_SSDR104      (0x1U << 1)
#define SDIO_CCCR_14_SDDR50       (0x1U << 2)
//@}
//---------------------------------------------------------------------------

static inline uint8_t GET_BYTE_FROM_BUFFER(const void* buffer, uintptr_t byteNr)
{
    return ((uint8_t)GetByte((*(uint32_t*)((uintptr_t)buffer + (byteNr & ~3UL))), (byteNr & 3UL)));
}
static inline uint8_t GET_BYTE_FROM_BUFFER2(const void* buffer, uintptr_t bufferSize, uintptr_t byteNr)
{
    return (GET_BYTE_FROM_BUFFER(buffer, bufferSize - 1U - byteNr));
}

//---------------------------------------------------------------------------
/// @name SD card function register bits, masks and macros definitions
//---------------------------------------------------------------------------
//@{
/// Check function mode - is used to query if the card supports a specific function or functions.
#define SDCARD_SWITCH_FUNC_MODE_SWITCH          (0x1UL << 31)
/// Set function mode  - is used to switch the functionality of the card.
#define SDCARD_SWITCH_FUNC_MODE_CHECK           (0x0UL << 31)

/// Card access mode - SDR12 default
#define SDCARD_SWITCH_ACCESS_MODE_SDR12         0x0U
/// Card access mode - SDR25 highspeed
#define SDCARD_SWITCH_ACCESS_MODE_SDR25         0x1U
/// Card access mode - SDR50
#define SDCARD_SWITCH_ACCESS_MODE_SDR50         0x2U
/// Card access mode - SDR104
#define SDCARD_SWITCH_ACCESS_MODE_SDR104        0x3U
/// Card access mode - DDR50
#define SDCARD_SWITCH_ACCESS_MODE_DDR50         0x4U

/// Card command system - default
#define SDCARD_SWITCH_CMD_SYSTEM_DEFAULT        0x0U
/// Card command system - eCommerce command set
#define SDCARD_SWITCH_CMD_SYSTEM_E_COMMERCE     0x1U
/// Card command system - OTP
#define SDCARD_SWITCH_CMD_SYSTEM_OTP            0x3U
/// Card command system - ASSD
#define SDCARD_SWITCH_CMD_SYSTEM_ASSD           0x4U
/// Card command system - vendor specific command set
#define SDCARD_SWITCH_CMD_SYSTEM_NR_VENDOR      0xEU

/// Card driver strength - Type B default
#define SDCARD_SWITCH_DRIVER_STRENGTH_B_TYPE    0x0U
/// Card driver strength - Type A
#define SDCARD_SWITCH_DRIVER_STRENGTH_A_TYPE    0x1U
/// Card driver strength - Type C
#define SDCARD_SWITCH_DRIVER_STRENGTH_C_TYPE    0x2U
/// Card driver strength - Type D
#define SDCARD_SWITCH_DRIVER_STRENGTH_D_TYPE    0x3U

#define SDCARD_SWITCH_GROUP_NR_1    1U
#define SDCARD_SWITCH_GROUP_NR_2    2U
#define SDCARD_SWITCH_GROUP_NR_3    3U
#define SDCARD_SWITCH_GROUP_NR_4    4U
#define SDCARD_SWITCH_GROUP_NR_5    5U
#define SDCARD_SWITCH_GROUP_NR_6    6U

/// Macro gets function busy status from the switch function status data structure
/// Macro returns 1 if function is busy 0 otherwise
static inline uint8_t SDCARD_SWICH_FUNC_GET_BUSY_STAT(const uint8_t* val, uint8_t groupNum, uint8_t funcNum)
{
    uint32_t busyStatus = 0U;

    if (funcNum < 32U) {
        const uintptr_t offset = (groupNum - 1UL) * 2UL;

        busyStatus = (((uint32_t)GET_BYTE_FROM_BUFFER2(val, 64UL, 34UL - offset)
                       | (uint32_t)GET_BYTE_FROM_BUFFER2(val, 64UL, 35UL - offset)) << 8)
                     & (uint32_t)(1UL << funcNum);
    }

    return ((busyStatus != 0U) ? 1U : 0U);
}
/// Macro gets function status code from the switch function status data structure
static inline uint8_t SDCARD_SWICH_FUNC_GET_STAT_CODE(const uint8_t* val, uint8_t groupNum)
{
    uint8_t result = 0U;
    const uint8_t shift = ((groupNum - 1U) % 2U) * 4U;

    const uintptr_t offset = 47UL + ((groupNum - 1UL) / 2UL);
    /* parasoft-begin-suppress MISRA2012-RULE-12_2-2 "Shifting operation should be checked, DRV-5093" */
    result = (GET_BYTE_FROM_BUFFER2(val, 64UL, offset) >> shift) & 0xFU;
    /* parasoft-end-suppress MISRA2012-RULE-12_2-2 */

    return (result);
}

/// Macro returns 1 if given function is supported by the card
static inline uint8_t SDCARD_SWITCH_FUNC_IS_FUNC_SUPPORTED(const uint8_t* val, uint8_t groupNum, uint8_t funcNum)
{
    uint32_t supportStatus = 0U;

    if (funcNum < 32U) {
        const uintptr_t offset = (groupNum - 1UL) * 2UL;

        supportStatus = (((uint32_t)GET_BYTE_FROM_BUFFER2(val, 64UL, 50UL - offset)
                          | (uint32_t)(GET_BYTE_FROM_BUFFER2(val, 64UL, 51UL - offset))) << 8)
                        & (uint32_t)(1UL << funcNum);
    }

    return ((supportStatus != 0U) ? 1U : 0U);
}

/// Macro gets version number of data structure
static inline uint8_t SDCARD_SWITCH_FUNC_GET_DATA_STRUCT_VER(const uint8_t* val)
{
    return GET_BYTE_FROM_BUFFER2(val, 64UL, 46UL);
}

//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Card status bits and masks definitions for cards (SD SDIO MMC)
//---------------------------------------------------------------------------
//@{
/// Error authentication process
#define CARD_SATUS_AKE_SEQ_ERROR          (0x1UL << 3)
/// The card will expect ACMD, or an indication that the command has been interpreted as ACMD
#define CARD_SATUS_APP_CMD                (0x1UL << 5)
/// Card didn't switch to the expected mode as requested by the SWITCH command
#define CARD_STATUS_SWITCH_ERROR          (0x1UL << 7)
/// Corresponds to buffer empty signaling on the bus - buffer is ready
#define CARD_SATUS_READY_FOR_DATA         (0x1UL << 8)
/// The state of the card when receiving the command. Below are definded all 9 satuses.
#define CARD_STATUS_CS_MASK               (0xFUL << 9)
/// Current status card is in Idle State
#define CARD_STATUS_CS_IDLE               (0x0UL << 9)
/// Current status card is in Ready State
#define CARD_STATUS_CS_READY              (0x1UL << 9)
/// Current status card is Identification State
#define CARD_STATUS_CS_IDENT              (0x2UL << 9)
/// Current status card is in Stand-by State
#define CARD_STATUS_CS_STBY               (0x3UL << 9)
/// Current status card is in Transfer State
#define CARD_STATUS_CS_TRAN               (0x4UL << 9)
/// Current status card is in Sending-data State
#define CARD_STATUS_CS_DATA               (0x5UL << 9)
/// Current status card is in Receive-data State
#define CARD_STATUS_CS_RCV                (0x6UL << 9)
/// Current status card is in Programming State
#define CARD_STATUS_CS_PRG                (0x7UL << 9)
/// Current status card is in Disconnect State
#define CARD_STATUS_CS_DIS                (0x8UL << 9)
/// An erase sequence was cleared before executing because an out of erase sequence command was received
#define CARD_STATUS_ERASE_RESET           (0x1UL << 13)
/// The command has been executed without using the internal ECC.
#define CARD_STATUS_CARD_ECC_DISABLED     (0x1UL << 14)
/// Problem with erase part of memory because it is protected
#define CARD_STATUS_WP_ERASE_SKIP         (0x1UL << 15)
/// Can be either one of the following errors:
/// - The read only section of the CSD does not match the card content.
/// - An attempt to reverse the copy (set as original) or permanent WP (unprotected) bits was made.
#define CARD_STATUS_CSD_OVERWRITE         (0x1UL << 16)
/// The card could not sustain data programming in stream write mode
#define CARD_STATUS_OVERRUN               (0x1UL << 17)
/// The card could not sustain data transfer in stream read mode
#define CARD_STATUS_UNDERRUN              (0x1UL << 18)
/// A general or an unknown error occurred during the operation.
#define CARD_STATUS_ERROR                 (0x1UL << 19)
/// Internal card controller error
#define CARD_STATUS_CC_ERROR              (0x1UL << 20)
/// Card internal ECC was applied but failure failed to correct the data.
#define CARD_STATUS_CARD_ECC_FAILED       (0x1UL << 21)
/// Command not legal for the card state
#define CARD_STATUS_ILLEGAL_COMMAND       (0x1UL << 22)
/// The CRC check of the previous error command failed.
#define CARD_STATUS_COM_CRC_ERROR         (0x1UL << 23)
/// Set when a sequence or password error has been detected in lock/unlock card command.
#define CARD_STATUS_LOCK_UNLOCK_FAILED    (0x1UL << 24)
/// When set, signals that the card is card locked by the host
#define CARD_STATUS_CARD_IS_LOCKED        (0x1UL << 25)
/// Set when the host attempts to write to a protected block or to the temporary or permanent write protected card.
#define CARD_STATUS_WP_VIOLATION          (0x1UL << 26)
/// An invalid selection of write-blocks for erase occurred.
#define CARD_STATUS_ERASE_PARAM           (0x1UL << 27)
/// An error in the sequence of erase error commands occurred.
#define CARD_STATUS_ERASE_SEQ_ERROR       (0x1UL << 28)
/// The transferred block length is not allowed for this card, or the number
/// of transferred bytes does not match the block length.
#define CARD_STATUS_BLOCK_LEN_ERROR       (0x1UL << 29)
/// A misaligned address which did not match the block length was used in the command.
#define CARD_STATUS_ADDRESS_ERROR         (0x1UL << 30)
/// The command's argument was out of the allowed range for this card.
#define CARD_STATUS_OUT_OF_RANGE          (0x1UL << 31)

/// All errors mask definition
#define CARD_STATUS_ALL_ERRORS_MASK (   CARD_STATUS_OUT_OF_RANGE        \
                                        | CARD_STATUS_ADDRESS_ERROR       \
                                        | CARD_STATUS_BLOCK_LEN_ERROR     \
                                        | CARD_STATUS_ERASE_SEQ_ERROR     \
                                        | CARD_STATUS_ERASE_PARAM         \
                                        | CARD_STATUS_WP_VIOLATION        \
                                        | CARD_STATUS_LOCK_UNLOCK_FAILED  \
                                        | CARD_STATUS_COM_CRC_ERROR       \
                                        | CARD_STATUS_ILLEGAL_COMMAND     \
                                        | CARD_STATUS_CARD_ECC_FAILED     \
                                        | CARD_STATUS_CC_ERROR            \
                                        | CARD_STATUS_ERROR               \
                                        | CARD_STATUS_UNDERRUN            \
                                        | CARD_STATUS_OVERRUN             \
                                        | CARD_STATUS_WP_ERASE_SKIP       \
                                        | CARD_STATUS_SWITCH_ERROR        \
                                        | CARD_SATUS_AKE_SEQ_ERROR )
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Response R6 argument field bit and masks definitions for SD memory card
//---------------------------------------------------------------------------
//@{
//---------------------------
// SD memory only definitions
//---------------------------
/// error authentication process
#define SDCARD_R6_SDMEM_STATUS_AKE_SEQ_ERROR        (0x1UL << 3)
///The card will expect ACMD, or an indication that the command has been interpreted as ACMD
#define SDCARD_R6_SDMEM_STATUS_APP_CMD              (0x1UL << 5)
/// Corresponds to buffer empty signaling on the bus - buffer is ready
#define SDCARD_R6_SDMEM_STATUS_READY_FOR_DATA       (0x1UL << 8)
/// The state of the card when receiving the command. Below are definded all 9 satuses.
#define SDCARD_R6_SDMEM_STATUS_CURRENT_STATUS_MASK  (0xFU << 9)
/// Current status card is in Idle State
#define SDCARD_R6_SDMEM_STATUS_CS_IDLE              (0x0U << 9)
/// Current status card is in Ready State
#define SDCARD_R6_SDMEM_STATUS_CS_READY             (0x1UL << 9)
/// Current status card is Identification State
#define SDCARD_R6_SDMEM_STATUS_CS_IDENT             (0x2U << 9)
/// Current status card is in Stand-by State
#define SDCARD_R6_SDMEM_STATUS_CS_STBY              (0x3U << 9)
/// Current status card is in Transfer State
#define SDCARD_R6_SDMEM_STATUS_CS_TRAN              (0x4U << 9)
/// Current status card is in Sending-data State
#define SDCARD_R6_SDMEM_STATUS_CS_DATA              (0x5U << 9)
/// Current status card is in Receive-data State
#define SDCARD_R6_SDMEM_STATUS_CS_RCV               (0x6U << 9)
/// Current status card is in Programming State
#define SDCARD_R6_SDMEM_STATUS_CS_PRG               (0x7U << 9)
/// Current status card is in Disconnect State
#define SDCARD_R6_SDMEM_STATUS_CS_DIS               (0x8U << 9)
/// Status field from SD memory card response R6
#define SDCARD_SDMEM_STATUS_MASK                    0xFFFFU
//---------------------------

//---------------------------
// Common SDIO and SD memory definitions
//---------------------------
/// A general or an unknown error C occurred during the operation.
#define SDCARD_R6_STATUS_ERROR                 (0x1UL << 13)
/// Command not legal for the card state
#define SDCARD_R6_STATUS_ILLEGAL_COMMAND       (0x1UL << 14)
/// The CRC check of the previous error command failed.
#define SDCARD_R6_STATUS_COM_CRC_ERROR         (0x1UL << 15)
/// Both SDIO and SD memory status mask part
#define SDCARD_R6_STATUS_MASK                   0xE000U
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Access modes of MMC card switch function
//---------------------------------------------------------------------------
//@{
///
/// The command set is changed according to the Cmd Set field of the argument
#define MMC_CMD6_ARG_MODE_COMMAND_SET (0x0UL << 24)
/// The bits in the pointed byte are set, according to the '1' bits in the Value field
#define MMC_CMD6_ARG_MODE_SET_BITS    (0x1UL << 24)
/// bits in the pointed byte are cleared, according to the '1' bits in the Value field
#define MMC_CMD6_ARG_MODE_CLEAR_BITS  (0x2UL << 24)
/// The Value field is written into the pointed byte
#define MMC_CMD6_ARG_MODE_WRITE_BYTE  (0x3UL << 24)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name MMC switch high speed timing values
//---------------------------------------------------------------------------
//@{
/// Standard speed
#define MMC_HIGH_SPEED_DISABLE      0U
/// High speed enabled
#define MMC_SWITCH_HIGH_SPEED       1U
/// High speed 200
#define MMC_SWITCH_HIGH_SPEED_200   2U
/// High speed 400
#define MMC_SWITCH_HIGH_SPEED_400   3U
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name MMC switch bus width values and masks
//---------------------------------------------------------------------------
//@{
/// enhanced strobe
#define MMC_SWITCH_BUS_WIDTH_ES         (1U << 7)
/// dual data rate mask
#define MMC_SWITCH_BUS_WIDTH_DDR_MASK   4U
/// 8 bit data bus
#define MMC_SWITCH_BUS_WIDTH_8      2U
/// 4 bit data bus
#define MMC_SWITCH_BUS_WIDTH_4      1U
/// 1 bit data bus
#define MMC_SWITCH_BUS_WIDTH_1      0U
/// 4 bit data bus (dual data rate)
#define MMC_SWITCH_BUS_WIDTH_4_DDR  (MMC_SWITCH_BUS_WIDTH_4 \
                                     | MMC_SWITCH_BUS_WIDTH_DDR_MASK)
/// 8 bit data bus (dual data rate)
#define MMC_SWITCH_BUS_WIDTH_8_DDR  (MMC_SWITCH_BUS_WIDTH_8 \
                                     | MMC_SWITCH_BUS_WIDTH_DDR_MASK)
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name MMC card extended CSD byte index definitions
//---------------------------------------------------------------------------
//@{
/// CMD Queuing Support
#define MMC_EXCSD_CQ_SUPPORT              308U
/// CMD Queuing Depth
#define MMC_EXCSD_CQ_DEPTH                307U
/// Boot information (supported transmission modes)
#define MMC_EXCSD_BOOT_INFO               228U
/// Boot partition size
#define MMC_EXCSD_BOOT_SIZE_MULTI         226U
/// I/O Driver Strength
#define MMC_EXCSD_I_O_DRIVER_STRENGTH     197U
/// Device type
#define MMC_EXCSD_DEVICE_TYPE             196U
/// MMC card power class
#define MMC_EXCSD_POWER_CLASS             187U
/// High speed interface timing
#define MMC_EXCSD_HS_TIMING               185U
///field informs whether device supports Enhanced Strobe
#define MMC_EXCSD_ES_SUPPORTED            184U
/// Bus width mode
#define MMC_EXCSD_BUS_WIDTH               183U
/// Partition configuration
#define MMC_EXCSD_BOOT_PART_CONFIG        179U
/// Boot config protection
#define MMC_EXCSD_BOOT_CONFIG_PROT        178U
/// Boot bus Conditions
#define MMC_EXCSD_BOOT_BUS_COND           177U
/// Command Queue Mode Enable
#define MMC_EXCSD_CQ_MODE_EN              15U
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name MMC card extended CSD device type masks
//---------------------------------------------------------------------------
//@{
/// High-Speed at 26MHz
#define MMC_EXCSD_DEV_HS_26MHZ            (1U << 0)
/// High-Speed at 52MHz
#define MMC_EXCSD_DEV_HS_52MHZ            (1U << 1)
/// High-speed DDR at 52 MHz, 1.8V or 3V I/O
#define MMC_EXCSD_DEV_HS_DDR_52MHZ_1_8_V_3_3_V    (1U << 2)
/// High-speed DDR at 52 MHz, 1.2V I/O
#define MMC_EXCSD_DEV_HS_DDR_52MHZ_1_2_V      (1U << 3)
/// High-speed HS200 SDR at 200 MHz, 1.8V I/O
#define MMC_EXCSD_DEV_HS_SDR_200MHZ_1_8_V     (1U << 4)
/// High-speed HS200 SDR at 200 MHz, 1.2V I/O
#define MMC_EXCSD_DEV_HS_SDR_200MHZ_1_2_V     (1U << 5)
/// High-speed HS400 DDR at 200 MHz, 1.8V I/O
#define MMC_EXCSD_DEV_HS_DDR_200MHZ_1_8_V     (1U << 6)
/// High-speed HS400 DDR at 200 MHz, 1.2V I/O
#define MMC_EXCSD_DEV_HS_DDR_200MHZ_1_2_V     (1U << 7)
//@}
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name MMC card extended CSD boot information masks
//-----------------------------------------------------------------------------
//@{
/// Device supports high speed timing during boot.
#define MMC_EXCSD_BOOT_INFO_HS_BOOT_MODE      (1U << 2)
/// Device supports dual data rate during boot.
#define MMC_EXCSD_BOOT_INFO_DDR_BOOT_MODE     (1U << 1)
/// Device supports alternative boot method.
#define MMC_EXCSD_BOOT_INFO_ALT_BOOT_MODE     (1U << 0)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name MMC card extended CSD boot partition size macro
//-----------------------------------------------------------------------------
//@{
/// macro calculates boot partition size base on MMC_EXCSD_BOOT_SIZE
static inline uint32_t MMC_EXCSD_BOOT_SIZE_MULTI_GET_SIZE(uint32_t bootSizeMult)
{
    return (bootSizeMult * 128U * 1024U);
}
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name MMC card extended CSD boot partition configuration masks
//-----------------------------------------------------------------------------
//@{
/// select partitions no access to boot partition (default)
#define MMC_EXCSD_BOOTPART_ACCESS_NONE    (0U << 0)
/// select partitions to access to R/W boot partition 1
#define MMC_EXCSD_BOOTPART_ACCESS_BP_1    (1U << 0)
/// select partitions to access to R/W boot partition 2
#define MMC_EXCSD_BOOTPART_ACCESS_BP_2    (2U << 0)
///R/W Replay Protected Memory Block (RPMB)
#define MMC_EXCSD_BOOTPART_ACCESS_RPMB    (3U << 0)
/// select partitions to access to to General Purpose partition 1
#define MMC_EXCSD_BOOTPART_ACCESS_GP_1    (4U << 0)
/// select partitions to access to to General Purpose partition 2
#define MMC_EXCSD_BOOTPART_ACCESS_GP_2    (5U << 0)
/// select partitions to access to to General Purpose partition 3
#define MMC_EXCSD_BOOTPART_ACCESS_GP_3    (6U << 0)
/// select partitions to access to to General Purpose partition 4
#define MMC_EXCSD_BOOTPART_ACCESS_GP_4    (7U << 0)
/// select partitions to access mask
#define MMC_EXCSD_BOOTPART_ACCESS_MASK    (7U << 0)

/// Device not boot enabled (default)
#define MMC_EXCSD_BOOTPART_CFG_BOOT_DISABLE   (0U << 3)
/// Boot partition 1 enabled for boot
#define MMC_EXCSD_BOOTPART_CFG_BOOT1_EN       (1U << 3)
/// Boot partition 2 enabled for boot
#define MMC_EXCSD_BOOTPART_CFG_BOOT2_EN       (2U << 3)
/// User area enabled for boot
#define MMC_EXCSD_BOOTPART_CFG_BOOTUSR_EN     (7U << 3)
/// boot partition selection mask
#define MMC_EXCSD_BOOTPART_CFG_BOOT_EN_MASK   (7U << 3)

///Boot acknowledge sent during boot operation Bit
#define MMC_EXCSD_BOOTPART_CFG_BOOT_ACK       (1U << 6)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name MMC card extended CSD boot partition configuration masks
//-----------------------------------------------------------------------------
//@{
/// disable the change of boot configuration
#define MMC_EXCSD_BOOTCFG_PROT_BOOT_PROT_EN   (1U << 0)
/// Permanently disable the change of boot configuration
#define MMC_EXCSD_BOOTCFG_PROT_PERM_PROT_EN   (1U << 4)
//@}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @name MMC card extended CSD bus conditions masks
//-----------------------------------------------------------------------------
//@{

/// Use single data rate + backward compatible timings in boot operation (default)
#define MMC_EXCSD_BOOTBUS_BOOT_MODE_SDR     (0U << 3)
/// Use single data rate + High Speed timings in boot operation mode
#define MMC_EXCSD_BOOTBUS_BOOT_MODE_SDR_HS  (1U << 3)
/// Use dual data rate in boot operation
#define MMC_EXCSD_BOOTBUS_BOOT_MODE_DDR     (2U << 3)
///  boot operation mode mask
#define MMC_EXCSD_BOOTBUS_BOOT_MODE_MASK    (3U << 3)

/// Retain BOOT_BUS_WIDTH and BOOT_MODE values after boot operation.
#define MMC_EXCSD_BOOTBUS_RETAIN_COND       (1U << 2)

/// x1 (sdr) or x4 (ddr) bus width in boot operation mode (default)
#define MMC_EXCSD_BOOTBUS__WIDTH_1       (0U << 0)
/// x4 (sdr/ddr) bus width in boot operation mode
#define MMC_EXCSD_BOOTBUS_WIDTH_4       (1U << 0)
/// x8 (sdr/ddr) bus width in boot operation mode
#define MMC_EXCSD_BOOTBUS_WIDTH_8       (2U << 0)
/// bus width in boot operation mode mask
#define MMC_EXCSD_BOOTBUS_WIDTH_MASK    (3U << 0)
//@}
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name Auxilary macros which can be used to prepare argument to CMD6 command for MMC cards
//---------------------------------------------------------------------------
//@{
/// Set access field in CMD6 command argument
static inline uint32_t MMC_CMD6_ARG_VALUE(uint32_t ArgValue)
{
    return ((uint32_t)ArgValue << 8);
}
/// Set index field in CMD6 command argument
static inline uint32_t MMC_CMD6_ARG_INDEX(uint32_t ArgIndex)
{
    return ((uint32_t)ArgIndex << 16);
}
//@}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// @name MMC card OCR register - mode definitions
//---------------------------------------------------------------------------
//@{
/// MMC card access mode - sector mode
#define MMC_REG_OCR_SECTOR_MODE (0x2UL << 29 )
/// MMC card access mode - byte mode
#define MMC_REG_OCR_BYTE_MODE   (0x0UL << 29 )
//@}
//---------------------------------------------------------------------------

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_ReadCardStatus ( CSDD_SDIO_Slot* pSlot,
 *                                             uint32_t *CardStatus )
 *
 * @brief       Function reads card status from a memory card
 *                  to the CardStatus.
 * @param       pSlot Slot on which read status command
 *                  shall be executed
 * @param       CardStatus pointer to memory where read card
 *                  status shall be written
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadCardStatus ( CSDD_SDIO_Slot* pSlot, uint32_t *CardStatus );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_SelectCard( CSDD_SDIO_Slot* pSlot,
 *                                        uint16_t RCA )
 *
 * @brief       Function select or deselect a card. If RCA is 0
 *                  then card will be deselect otherwise it
 *                  will be select (if real card RCA
 *                  equals RCA parameter)
 * @param       pSlot Slot on which select card status
 *                  shall be executed
 * @param       rca RCA address card in selecting card case
 *                  or 0 in deselecting card case
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_SelectCard( CSDD_SDIO_Slot* pSlot, uint16_t rca );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_ResetCard( CSDD_SDIO_Slot* pSlot )
 *
 * @brief       Function resets a card using CMD0 command
 * @param       pSlot Slot on which reset command shall be executed
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_ResetCard( CSDD_SDIO_Slot* pSlot );

/*****************************************************************************/
/*!
 * @fn          uint8_t SDIOHost_ExecCMD55Command( CSDD_SDIO_Slot* pSlot )
 *
 * @brief       Function executes CMD55 command
 * @param       pSlot Slot on which CMD55 command shall be executed
 * @return      Function returns 0 if everything is ok
 *                  otherwise returns error number
 *
 */
/*****************************************************************************/
uint8_t SDIOHost_ExecCMD55Command( CSDD_SDIO_Slot* pSlot );

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_AccessCCCR ( CSDD_SDIO_Slot* pSlot,
 *                                     uint8_t TransferDirection,
                                       void *Data,
                                       uint8_t DataSize,
                                       uint8_t RegisterAddress )
 * @brief   Function writes or reads the CCCR card registers.
 *              the CCCR is present in SDIO or combo cards only
 * @param   pSlot The slot from which we want to read/write data
 * @param   TransferDirection 0 means read, 1 means write
 * @param   Data Pointer to data buffer
 * @param   DataSize Size of data buffer
 * @param   RegisterAddress The address of register to which
 *              we want to access. The definitions of registers are
 *              here @ref CCCR
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
#if SDIO_CFG_ENABLE_IO
uint8_t SDIOHost_AccessCCCR ( CSDD_SDIO_Slot* pSlot, uint8_t TransferDirection,
                              void *Data, uint8_t DataSize, uint8_t RegisterAddress);
#endif

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ReadSCR( CSDD_SDIO_Slot* pSlot )
 * @brief   Function reads SCR register and store
 *              read informations in the device structure variables.
 *              SCR register is present only in memory or combo cards
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadSCR( CSDD_SDIO_Slot* pSlot );

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ReadCID(CSDD_SDIO_Slot* pSlot,
 *                                   CSDD_SDIO_CidRegister* CID)
 * @brief   Function reads CID register of the card and store
 *              read informations CID parameter.
 *              CID register is present only in memory or combo cards
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @param   CID Structure which represents CID registers
 *              Read data are stored in this structure
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadCID(CSDD_SDIO_Slot* pSlot, CSDD_SDIO_CidRegister* CID);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ReadRCA( CSDD_SDIO_Slot* pSlot )
 * @brief   Function reads RCA register of the card and store
 *              read informations in the device structure variables.
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadRCA( CSDD_SDIO_Slot* pSlot );

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ReadCSD(CSDD_SDIO_Slot* pSlot, uint32_t Buffer[4] )
 * @brief   Function reads CSD register from the card to Buffer.
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @param   Buffer Buffer for read data
 * @return	Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadCSD(CSDD_SDIO_Slot* pSlot, uint32_t Buffer[4] );

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ReadExCSD(CSDD_SDIO_Slot* pSlot, uint32_t Buffer[512] )
 * @brief   Function reads Extended CSD register from the card to Buffer.
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @param   Buffer Buffer for read data
 * @return	Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadExCSD(CSDD_SDIO_Slot* pSlot, uint8_t Buffer[512] );

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_GetTupleFromCIS( CSDD_SDIO_Slot* pSlot,
                                           uint32_t TupleAddress, uint8_t TupleCode,
                                           uint8_t *Buffer, uint8_t BufferSize )

 * @brief   Function reads a tuple from the CIS card register to Buffer.
 *              CIS register is present only in SDIO or combo cards
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @param   TupleAddress Start address of the CIS register,
 * @param   TupleCode Code name of tuple. There all bus widths defined
 *              here @ref TupleDefinitions.
 * @param   Buffer Buffer on read data
 * @param   BufferSize Size of Buffer in bytes
 * @return	Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
#if SDIO_CFG_ENABLE_IO
uint8_t SDIOHost_GetTupleFromCIS( CSDD_SDIO_Slot* pSlot,
                                  uint32_t   TupleAddress,
                                  uint8_t    TupleCode,
                                  uint8_t *  Buffer,
                                  uint8_t    BufferSize );
#endif

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_SwitchFunction(CSDD_SDIO_Slot* pSlot, uint8_t FunctionNr,
 *                                      uint8_t GroupNr)
 *
 * @brief   Function switches memory card functions.
 *              It supports six function groups,
 *              and each function group supports
 *              sixteen branches (functions).
 * @param   pSlot Slot in which is the card which register
 *              we want to read
 * @param   FunctionNr function number to switch (0 - 14),
 * @param   GroupNr group number to switch (1 - 6)
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_SwitchFunction(CSDD_SDIO_Slot* pSlot, uint8_t FunctionNr,
                                uint8_t GroupNr);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ExecCMD23Command(CSDD_SDIO_Slot* pSlot, uint32_t BlockCount)
 *
 * @brief   Function executes CMD23 command on the card.
 *              Command specifies block count for CMD18 CMD25.
 * @param   pSlot Slot on which command will be executed
 * @param   BlockCount argument of CMD23 command
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ExecCMD23Command(CSDD_SDIO_Slot* pSlot, uint32_t BlockCount);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ExecCMD12Command(CSDD_SDIO_Slot* pSlot, CSDD_ResponseType ResponseType)
 *
 * @brief   Function executes CMD12 command on the card. Command forces card
 *              to stop transmission.
 * @param   pSlot Slot on which command will be executed
 * @param   ResponseType type of response.
 *              Parameter depends on transmission direction.
 *              CSDD_RESPONSE_R1B - to stop write transmission.
 *              CSDD_RESPONSE_R1 - to stop read transmission.
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ExecCMD12Command(CSDD_SDIO_Slot* pSlot, CSDD_ResponseType ResponseType);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_ReadSDStatus(CSDD_SDIO_Slot* pSlot, uint8_t Buffer[64])
 *
 * @brief   Function reads SD card status
 * @param   pSlot Slot on which command will be executed
 * @param   Buffer read status
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_ReadSDStatus(CSDD_SDIO_Slot* pSlot, uint8_t Buffer[64]);

/*****************************************************************************/
/*!
 * @fn      SDIOHost_SDCardUhsiSupported(CSDD_SDIO_Slot* pSlot, uint8_t *UhsiSupported)
 *
 * @brief   Function checks if card supports UHS-I modes
 * @param   pSlot Slot on which command will be executed
 * @param   UhsiSupported parameter returns info if UHS-I
 *              mode is supported by the card
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_SDCardUhsiSupported(CSDD_SDIO_Slot* pSlot, uint8_t *UhsiSupported);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_SDCardSetDrvStrength(CSDD_SDIO_Slot* pSlot,
 *                                                CSDD_DriverStrengthType DriverStrength
 *
 * @brief   Function configures driver strength of a card
 * @param   pSlot Slot with card to change configuration
 * @param   DriverStrength new driver strength parameter
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_SDCardSetDrvStrength(CSDD_SDIO_Slot*              pSlot,
                                         CSDD_DriverStrengthType DriverStrength);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_SDCardSetCurrentLimit(CSDD_SDIO_Slot* pSlot,
 *                                              CSDD_DriverCurrentLimit CurrentLimit)
 *
 * @brief   Function sets a card current limit
 * @param   pSlot Slot with card to change configuration
 * @param   CurrentLimit new current limit
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_SDCardSetCurrentLimit(CSDD_SDIO_Slot* pSlot, CSDD_DriverCurrentLimit CurrentLimit);

/*****************************************************************************/
/*!
 * @fn      SDIOHost_MmcSwitch(CSDD_SDIO_Slot* pSlot, uint8_t ArgIndex, uint8_t ArgValue)
 *
 * @brief   Function modifies the EXT_CSD register.
 * @param   pSlot Slot on which command will be executed
 * @param   ArgIndex index of EXT_CSD register field to be modified
 * @param   ArgValue new value to be set
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_MmcSwitch(CSDD_SDIO_Slot* pSlot, uint8_t ArgIndex, uint8_t ArgValue);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_MmcSetExtCsd(CSDD_SDIO_Slot* pSlot, uint8_t ByteNr,
 *                          uint8_t NewValue, uint8_t Mask)
 *
 * @brief   Function modifies a part of EXT_CSD register. Function reads byte
 *              pointer by ByteNr parameter next masks using ~Mask, and at the
 *              end function makes "or" operation with NewValue. Such value
 *              is written to the EXT_CSD register.
 * @param   pSlot Slot on which command will be executed
 * @param   ByteNr index of EXT_CSD register field to be modified
 * @param   Mask shows which part of byte is used
 * @param   NewValue new value to be "or"
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_MmcSetExtCsd(CSDD_SDIO_Slot* pSlot, uint8_t ByteNr,
                              uint8_t NewValue, uint8_t Mask);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_MmcSetBootPartition(CSDD_SDIO_Slot* pSlot, CSDD_ParitionBoot Partition)
 *
 * @brief   Function sets active partition to boot operation.
 * @param   pSlot Slot on which command will be executed
 * @param   Partition partition to boot
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_MmcSetBootPartition(CSDD_SDIO_Slot* pSlot, CSDD_ParitionBoot Partition);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_MmcSetPartAccess(CSDD_SDIO_Slot* pSlot, CSDD_ParitionAccess Partition)
 *
 * @brief   Function sets active partition to access
 * @param   pSlot Slot on which command will be executed
 * @param   Partition partition to access
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_MmcSetPartAccess(CSDD_SDIO_Slot* pSlot, CSDD_ParitionAccess Partition);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_MmcExecuteBoot(CSDD_SDIO_Slot* pSlot, void *Buffer,
 *                                      uint32_t BufSize)
 *
 * @brief   Function executes boot operation. It reads data from active boot
 *              partition to the Buffer.
 * @param   pSlot Slot on which command will be executed
 * @param   Buffer boot data is placed there
 * @param   BufSize buffer size in bytes
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_MmcExecuteBoot(CSDD_SDIO_Slot* pSlot, void *Buffer, uint32_t BufSize);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIOHost_MmcGetPartitionBootSize(CSDD_SDIO_Slot* pSlot, uint32_t *BootSize)
 *
 * @brief   Function gets boot partition size.
 * @param   pSlot Slot on which command will be executed
 * @param   BootSize of boot partition in bytes
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIOHost_MmcGetPartitionBootSize(CSDD_SDIO_Slot* pSlot, uint32_t *BootSize);

uint8_t SDIOHost_MmcSetBootAck(CSDD_SDIO_Slot* pSlot, bool enableBootAck);
#endif
