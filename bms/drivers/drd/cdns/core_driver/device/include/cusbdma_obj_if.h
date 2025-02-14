/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.05.b3ee589
 *          Do not edit it manually.
 **********************************************************************
 * Layer interface for the Cadence DMA controller
 **********************************************************************/
#ifndef CUSBDMA_OBJ_IF_H
#define CUSBDMA_OBJ_IF_H

#include "cusbdma_if.h"

/** @defgroup DriverObject Driver API Object
 *  API listing for the driver. The API is contained in the object as
 *  function pointers in the object structure. As the actual functions
 *  resides in the Driver Object, the client software must first use the
 *  global GetInstance function to obtain the Driver Object Pointer.
 *  The actual APIs then can be invoked using obj->(api_name)() syntax.
 *  These functions are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/

/* parasoft-begin-suppress MISRA2012-DIR-4_8-4 "Consider hiding the
 * implementation of the structure, DRV-4932" */
typedef struct CUSBDMA_OBJ_s {
  /**
   * Obtain the private memory size required by the driver.
   * @param[in] config driver/hardware configuration required
   * @param[out] sysReq sysReq returns the size of memory allocations required
   * @return CDN_EOK on success
   * @return CDN_EINVAL if function parameters are not valid
   * @return CDN_ENOTSUP if configuration cannot be supported due to
   * driver/hardware constraints
   */
  uint32_t (*probe)(const CUSBDMA_Config *config, CUSBDMA_SysReq *sysReq);

  /**
   * Initialize the driver instance and state, configure the USB device
   * as specified in the 'config' settings, initialize locks used by
   * the driver.
   * @param[in] pD driver state info specific to this instance
   * @param[in] config specifies driver/hardware configuration
   * @return CDN_EOK on success
   * @return CDN_EINVAL if function parameters are not valid
   * @return CDN_ENOTSUP if configuration cannot be supported due to
   * driver/hardware constraints
   * @return CDN_EIO if driver encountered an error accessing hardware
   * @return CDN_ENOENT insufficient locks were available (i.e. something
   * allocated locks between probe and init)
   */
  uint32_t (*init)(CUSBDMA_DmaController *pD, const CUSBDMA_Config *config);

  /**
   * Destroy the driver (automatically performs a stop).
   * @param[in] pD driver state info specific to this instance
   */
  uint32_t (*destroy)(CUSBDMA_DmaController *pD);

  /**
   * Allocation the DMA channel
   * @param[in] pD driver state info specific to this instance
   * @param[out] channelPtr address of channel pointer
   * @param[in] channelParams Channel parameters
   */
  uint32_t (*channelAlloc)(CUSBDMA_DmaController *pD,
                           CUSBDMA_DmaChannel **channelPtr,
                           CUSBDMA_ChannelParams *channelParams);

  /**
   * Reset the DMA channel
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel channel pointer to DMA channel
   * @return CDN_EOK on success
   * @return CDN_EINVAL if function parameters are not valid
   * @return CDN_EPERM if the DMA is active and channel cannot be reset
   */
  uint32_t (*channelReset)(CUSBDMA_DmaController *pD,
                           CUSBDMA_DmaChannel *channel);

  /**
   * Release the DMA channel
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel channel pointer to DMA channel
   * @return CDN_EOK on success
   * @return CDN_EINVAL if function parameters are not valid
   */
  uint32_t (*channelRelease)(CUSBDMA_DmaController *pD,
                             CUSBDMA_DmaChannel *channel);

  /**
   * Prepares transfer and starts it.
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel channel pointer to DMA channel for which transfer will
   * be started
   * @param[in] params transfer parameters container
   * @return CDN_EOK on success
   * @return CDN_EINVAL if function parameters are not valid
   * @return CDN_ENOMEM if DMA channel has no free memory for TRB
   */
  uint32_t (*channelProgram)(CUSBDMA_DmaController *pD,
                             CUSBDMA_DmaChannel *channel,
                             const CUSBDMA_DmaTransferParam *params);

  /**
   * Triggers DMA transfer for given DMA channel if TRBs are queued
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel pointer to DMA channel which needs to be triggered
   * @return CDN_EOK on successful trigger or if the DMA is already active
   * @return CDN_EINVAL if function parameters are not valid
   * @return CDN_ENOTSUP if TRBs are not queued
   */
  uint32_t (*channelTrigger)(CUSBDMA_DmaController *pD,
                             CUSBDMA_DmaChannel *channel);

  /**
   * Updates the data transfer status of a channel
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel pointer to DMA channel whose state needs to be updated
   * @return CDN_EOK on successful trigger or if the DMA is already active
   * @return CDN_EINVAL if function parameters are not valid
   */
  uint32_t (*channelUpdateState)(CUSBDMA_DmaController *pD,
                                 CUSBDMA_DmaChannel *channel);

  /**
   * Updates the max packet size for a channel
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel pointer to DMA channel whose state needs to be updated
   * @param[in] maxPacketSize Value of max packet size
   * @return CDN_EOK on successful successful update of max packet size
   * @return CDN_EINVAL if function parameters are not valid
   */
  uint32_t (*channelSetMaxPktSz)(CUSBDMA_DmaController *pD,
                                 CUSBDMA_DmaChannel *channel,
                                 uint16_t maxPacketSize);

  /**
   * Set or Clear channel stall
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel pointer to DMA channel whose stall state is handled
   * @param[in] value Clear stall if 0, else set stall
   * @param[in] timeout Timeout for waiting for flush operation while stalling
   * @return CDN_EOK on successful trigger or if the DMA is already active
   * @return CDN_EINVAL if function parameters are not valid
   */
  uint32_t (*channelHandleStall)(CUSBDMA_DmaController *pD,
                                 CUSBDMA_DmaChannel *channel, uint32_t value,
                                 uint32_t timeout);

  /**
   * Free the head(oldest) TRB chain descriptor for this channel.
   * @param[in] pD driver state info specific to this instance
   * @param[in] channel pointer to DMA channel whose descriptor needs to be
   * freed
   * @return CDN_EOK on success
   * @return CDN_EINVAL if function parameters are not valid
   */
  uint32_t (*channelFreeHeadTrbChain)(const CUSBDMA_DmaController *pD,
                                      CUSBDMA_DmaChannel *channel);

} CUSBDMA_OBJ;
/* parasoft-end-suppress MISRA2012-DIR-4_8-4 */

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from
 * more than 5 different functions, DRV-3666" */
/**
 * In order to access the CUSBDMA APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CUSBDMA_OBJ* Driver Object Pointer
 */
extern CUSBDMA_OBJ *CUSBDMA_GetInstance(void);

/**
 *  @}
 */
/* parasoft-end-suppress METRICS-36-3 */

#endif /* CUSBDMA_OBJ_IF_H */
