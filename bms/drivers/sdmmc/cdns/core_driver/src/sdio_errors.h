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
 * sdio_errors.h
 * SD Host controller driver error code definitions.
 *****************************************************************************/

#ifndef SDIO_ERRORS_H
#define SDIO_ERRORS_H

/// There is no error during execute procedure
#define SDIO_ERR_NO_ERROR                   0x00U
/// Error Host base clock is zero
#define SDIO_ERR_BASE_CLK_IS_ZERO           0x01U
/// Error can't power supply
#define SDIO_ERR_NO_POWER_SUPPLY            0x02U
/// Error timeout
#define SDIO_ERR_TIMEOUT                    0x03U
/// Error during configuration - current limit error
#define SDIO_ERR_CURRENT_LIMIT_ERROR        0x04U
/// Error during transfer data - end bit error
#define SDIO_ERR_DATA_END_BIT_ERROR         0x05U
/// Error during transfer data - crc bit error
#define SDIO_ERR_DATA_CRC_ERROR             0x06U
/// Error during transfer data - timeout error
#define SDIO_ERR_DATA_TIMEOUT_ERROR         0x07U
/// Error during execute command - command index error
#define SDIO_ERR_COMMAND_INDEX_ERROR        0x08U
/// Error during execute command - command line conflict
#define SDIO_ERR_CMD_LINE_CONFLICT          0x09U
/// Error during execute command - timeout error
#define SDIO_ERR_COMMAND_TIMEOUT_ERROR      0x0AU
/// Error during execute command - end bit error
#define SDIO_ERR_COMMAND_END_BIT_ERROR      0x0BU
/// Error during execute command - CRC error
#define SDIO_ERR_COMMAND_CRC_ERROR          0x0CU
/// Card is in inactive state, it is unusable
#define SDIO_ERR_UNUSABLE_CARD              0x0DU
/// Wrong argument for SDIO card function
#define SDIO_ERR_PARAM_ERR                  0x0EU
/// Wrong SDIO function number error
#define SDIO_ERR_FUN_NUM_ERR                0x0FU
/// The CRC check for the previous command failed
#define SDIO_ERR_COM_CRC_ERR                0x10U
/// Illegal command error
#define SDIO_ERR_ILLEGAL_CMD                0x11U
/// An error in the sequence of erase commands occurred.
#define SDIO_ERR_ERASE_SEQUENCE_ERR         0x12U
/// A general or an unknown error occurred during the operation
#define SDIO_ERR_GENERAL                    0x13U
/// A misaligned address that did not match the block length was used in the command
#define SDIO_ERR_ADDRESS_ERR                0x14U
/// Can't switch device to bus speed mode because it is not supported either
/// by controller or by card
#define SDIO_ERR_BUS_SPEED_UNSUPP           0x15U
/// Command not inssued by auto CMD 12 error
/// CMD_wo_DAT is not executed due to an Auto CMD12 error (D04-D01)
/// in the Auto CMD12 error status register
#define SIO_ERR_AUTOCMD12_NOT_ISSUED        0x16U
/// Command index error occurs in response to a command
#define SIO_ERR_AUTOCMD12_INDEX_ERROR       0x17U
/// End bit of command response is 0
#define SIO_ERR_AUTOCMD12_END_BIT_ERROR     0x18U
/// Error CRC in the Auto CMD 12 command response
#define SIO_ERR_AUTOCMD12_CRC_ERROR         0x19U
/// No response is returned within 64 SDCLK cycles from the end bit of command
/// In this error occur then other error status bits are meaningless
#define SIO_ERR_AUTOCMD12_TIMEOUT           0x1AU
/// Host controller cannot issue Auto CMD12 to stop memory multiple
/// block data transfer due to some error.
#define SIO_ERR_AUTOCMD12_NOT_EXECUTED      0x1BU
/// Auto CMD12 error - CMD line conflict
#define SDIO_ERR_AUTOCMD12_LINE_CONFLICT    0x1CU
/// Touple not found in CIS register error
#define SDIO_ERR_TUPLE_NOT_FOUND            0x1DU
/// Software driver to service inserted card was not implemented
#define SDIO_ERR_DRIVER_NOT_IMPLEMENTED     0x1EU
/// Function malloc error
#define SDIO_ERR_MEM_ALLOC                  0x1FU
/// Error DAT line is busy, can't execute command
#define SDIO_ERR_DAT_LINE_BUSY              0x20U
/// Error CMD line is busy, can't execute command
#define SDIO_ERR_CMD_LINE_BUSY              0x21U
/// Internal card controller error
#define SDIO_ERR_CC_ERROR                   0x22U
/// Card internal ECC was applied but failure
#define SDIO_ERR_CARD_ECC                   0x23U
/// Sequence or password error has been detected in lock/unlock card command
#define SDIO_ERR_LOCK_UNLOCK_FAILED         0x24U
/// Host attempts to write to a protected block or to the temporary or permanent write protected card.
#define SDIO_ERR_WP_VIOLATION               0x25U
/// An invalid selection of write-blocks for erase occurred
#define SDIO_ERR_ERASE_PARAM                0x26U
/// The transferred block length is not allowed for this card, or the number
/// of transferred bytes does not match the block length
#define SDIO_ERR_BLOCK_LEN_ERROR            0x27U
/// The command's argument was out of the allowed range for this card
#define SDIO_ERR_OUT_OF_RANGE               0x28U
/// Unrecoverable error ocured
#define SDIO_ERR_NON_RECOVERABLE_ERROR      0x29U
/// An error occurred in CMD_wo_DAT, but not in the SD memory transfer.
#define SDIO_ERR_ACMD12_RECOVERABLE_A       0x2AU
/// An error occurred in CMD_wo_DAT, and also occurred in the SD memory transfer
#define SDIO_ERR_ACMD12_RECOVERABLE_B       0x2BU
/// An error did not occur in CMD_wo_DAT, but an error occurred in the SD memory transfer
#define SDIO_ERR_ACMD12_RECOVERABLE_C       0x2CU
/// CMD_wo_DAT was not issued, and an error occurred in the SD memory transfer
#define SDIO_ERR_ACMD12_RECOVERABLE_D       0x2DU
/// Card is card locked by the host
#define SDIO_ERR_CARD_IS_LOCKED             0x2EU
/// The card could not sustain data transfer in stream read mode
#define SDIO_ERR_UNDERRUN                   0x2FU
/// The card could not sustain data transfer in stream write mode
#define SDIO_ERR_OVERRUN                    0x30U
/// Problem with erase part of memory because it is protected
#define SDIO_ERR_WP_ERASE_SKIP              0x31U
/// Card didn't switch to the expected mode as requested by the SWITCH command
#define SDIO_ERR_SWITCH_ERROR               0x32U
/// Error authentication process
#define SDIO_ERR_AKE_SEQ_ERROR              0x33U
/// SLOT is busy can't execute a command
#define SDIO_ERR_SLOT_IS_BUSY               0x34U
// Error command is not supported by the card device
#define SDIO_ERR_UNSUPPORTED_COMMAND        0x35U
/// Device is null pointer
#define SDIO_ERR_DEV_NULL_POINTER           0x36U
/// ADMA error
#define SDIO_ERR_ADMA                       0x37U
/// unexepted DMA interrupt (probably wrong descriptor settings)
#define SDIO_ERR_DMA_UNEXCEPTED_INTERRUPT   0x38U
/// invalid function parameter
#define SDIO_ERR_INVALID_PARAMETER          0x39U
/// error trying write or erase locked card.
#define SDIO_ERR_CARD_WRITE_PROTECTED       0x3AU
/// error function is not supported (CMD6 command)
#define SDIO_ERR_FUNCTION_UNSUPP            0x3BU
/// to few memory for ADMA descriptors
#define SDIO_ERR_TO_FEW_MEM                 0x3CU
/// signal volatge switch procedure failed
#define SDIO_ERR_SWITCH_VOLTAGE_FAILED      0x3DU
/// Changing access mode funtion works only when 1.8V signaling level is active
#define SDIO_ERR_WRONG_SINGALING_LEVEL      0x3EU
/// operation is unsupported by the driver or core
#define SDIO_ERR_UNSUPORRTED_OPERATION      0x3FU
/// tuning operation failed
#define SDIO_ERR_TUNING_FAILED              0x40U
/// auto cmd23 function is not possible to use
/// SDMA can't be enabled and card must suports this command
#define SDIO_ERR_AUTO_CMD23_NOT_POSSIBLE    0x41U
/// Error appear during UHSII initialization
#define SDIO_ERR_UHSII_INITIALIZE_ERROR     0x42U
/// response error
#define SDIO_ERR_RESP_ERROR                 0x43U
/// device is uninitialized
#define SDIO_ERR_UNITIALIZED                0x44U
/// Header Error is detected in received packet
#define SDIO_ERR_HEADER_ERROR               0x45U
/// number of transfer retries reaches Retry Count
#define SDIO_ERR_RETRY_EXPIRED              0x47U
/// CRC Error is detected in received packet
#define SDIO_ERR_CRC_ERROR                  0x48U
/// Framing Error is detected in received packet
#define SDIO_ERR_FRAMING_ERROR              0x49U
/// Transaction ID (TID) Error is detected
#define SDIO_ERR_TID_ERROR                  0x4AU
/// received packed has the Unrecoverable Error
#define SDIO_ERR_UNRECOVERABLE_ERROR        0x4BU
/// received EBSY Packet has an error
#define SDIO_ERR_EBSY_ERROR                 0x4CU
/// RES Packet timeout occurs.
/// Host expects to receive RES packet but not received
/// in a specified timeout (5ms).
#define SDIO_ERR_TIMEOUT_FOR_CMD_RES        0x4DU
/// deadlock timeout occurs
#define SDIO_ERR_TIMEOUT_FOR_DEADLOCK       0x4EU
/// UHSII response error
#define SDIO_ERR_UHSII_RESPONSE_ERROR       0x4FU
/// The CMD is not permitted on the present condition or state
#define SDIO_ERR_RESPONSE_ECODE_COND        0x50U
/// At least one of arguments is improper in the CMD
#define SDIO_ERR_RESPONSE_ECODE_ARG         0x51U
/// General error detected
#define SDIO_ERR_RESPONSE_ECODE_GEN         0x52U
/// Card is not insterted to the slot
#define SDIO_ERR_CARD_IS_NOT_INSERTED       0x53U
/// Card is not attached (initialized)
#define SDIO_ERR_CARD_IS_NOT_ATTACHED       0x54U
/// Error appears durring abort
#define SDIO_ERR_ABORT_ERROR                0x55U
/// Could not set new value to EXT_CSD register
#define SDIO_ERR_SETTING_EXT_CSD_FAILED     0x57U
/// UHSII card not detected
/// SDIO_CFG_EXIT_WHEN_NO_UHSII option is set
#define SDIO_ERR_UHSII_CARD_NOT_DETECTED    0x58U
// MMC boot failed
#define SDIO_ERR_MMC_BOOT_ERROR             0x59U
// Recoverable error
#define SDIO_ERR_RECOVERABLE_ERROR  		0x60U
// Command Not Issued By Error
#define SIO_ERR_CMD_NOT_EXECUTED      		0x61U

/// Request is currently executing
#define SDIO_STATUS_PENDING                 0xFFU
/// Request was aborted
#define SDIO_STATUS_ABORTED                 0xFEU
/// Undefined error
#define SDIO_ERR_UNDEFINED                  0xEFU
/// Hardware problem error
#define SDIO_ERR_HARDWARE_PROBLEM           0xEEU
// Cant execute function
#define SDIO_ERR_CANT_EXECUTE               0xECU

const char * SDIO_Errors_GetText(uint8_t ErrorCode);

#endif
