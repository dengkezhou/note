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
 * sdio_config.h
 * SD Host controller driver configuration
 *****************************************************************************/

#ifndef SDIO_CONFIG_H
#define SDIO_CONFIG_H

// Macros used only in preprocessor directives
//
/// SDMA support for SDIO host driver
#define SDIO_SDMA_SUPPORTED                 1
/// ADMA1 support for SDIO host driver
#define SDIO_ADMA1_SUPPORTED                0
/// ADMA2 support for SDIO host driver
#define SDIO_ADMA2_SUPPORTED                1
/// ADMA3 support for SDIO host driver from host ver6.
#define SDIO_ADMA3_SUPPORTED                1
/// procedure to handle card interrupt
#define ENABLE_CARD_INTERRUPT               0
/// change data endianity during read - dma disabled
#define CHANGE_DATA_ENDIANITY_NODMA         1
/// it enables support for IO cards
/// (it should be disabled it was not tested yet)
#define SDIO_CFG_ENABLE_IO                  0
///  disable or enable support for MMC devices
#define SDIO_CFG_ENABLE_MMC                 1
/// Version of SD Host controller
#ifndef SDIO_CFG_HOST_VER
#   define SDIO_CFG_HOST_VER                6
#endif

#ifdef CONFIG_COMPILE_RTL
// #define SKIP_SD_TRY
// #define NO_REQ_S18R
// #define DBG_PRINT_EXT_CSD
#define FORCE_MMC_TYPE
#define FORCE_ES_SUPPORT
#endif

// Macros used as constants
/// Set debouncing period
#define DEBOUNCING_TIME                     0x300000UL
/// Commands timeout is a iteration count after which timeout error will be report
/// if a command will not execute (mainly using in WaitForValue function)
#define COMMANDS_TIMEOUT                    3000U
// system clock in Hz
#define SYTEM_CLK_KHZ                       (FGPA_SD_EXT_CLK / 1000U)
/// buffer size for ADMA2 descriptors
#define MAX_DESCR_BUFF_SIZE                 (1024U * 50U)
/// buffer size for ADMA 3 command descriptors
#define MAX_COMMAND_DESCR_BUFF_SIZE         (1024U * 50U)
/// buffer size for ADMA 3 integrated descriptors
#define MAX_INTEGREATED_DESCR_BUFF_SIZE     (1024U * 50U)
/// hardware slots count
#define SDIO_SLOT_COUNT                     1U
/// maximum supported device(SDIO device drivers) count.
/// Default it is 2 SD and MMC.
#define MAX_SUPPORTED_DEVICE_COUNT          2U
/// option defines if memory card driver should use auto CMD or not.
/// 1 - use auto CMD
/// 0 - don't use auto CMD
#define USE_AUTO_CMD                        0
/// delay in microseconds after power enable
#define POWER_UP_DELAY_US                   2000U
/// number of temporary sub-buffers, used by to split data
/// bigger than 64KB for smaller parts. Split is made by ADMA module.
#define SDIO_CFG_SDIO_SUB_BUFFERS_COUNT     4000U
/// Configuration of how many times each reset operation shall be executed
#define SDIO_CFG_RESET_COUNT                2U
#endif
