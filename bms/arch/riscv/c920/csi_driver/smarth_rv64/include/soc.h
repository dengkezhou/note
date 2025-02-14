/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/**************************************************************************/ /**
                                                                              * @file     soc.h
                                                                              * @brief    CSI Core Peripheral Access Layer Header File for
                                                                              *           CSKYSOC Device Series
                                                                              * @version  V1.0
                                                                              * @date     02. June 2017
                                                                              ******************************************************************************/

#ifndef _SOC_H_
#define _SOC_H_

#include <stdint.h>
#include <riscv/csi_core.h>
#include <sys_freq.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IHS_VALUE
#define IHS_VALUE (20000000)
#endif

#ifndef EHS_VALUE
#define EHS_VALUE (20000000)
#endif

/* ================================================================================
 */
/* ================       Device Specific Peripheral Section ================
 */
/* ================================================================================
 */

#define CONFIG_TIMER_NUM    4
#define CONFIG_USART_NUM    1
#define CONFIG_GPIO_NUM     8
#define CONFIG_GPIO_PIN_NUM 8

#include <common.h>
/* ================================================================================
 */
/* ================             Peripheral declaration ================ */
/* ================================================================================
 */
#define CSKY_UART ((CSKY_UART_TypeDef *)CSKY_UART_BASE)

#ifdef __cplusplus
}
#endif

#endif /* _SOC_H_ */
