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
 * Cadence Core Driver for USB SSP DRD
 **********************************************************************/
#ifndef USB_SSP_DRD_OBJ_IF_H
#define USB_SSP_DRD_OBJ_IF_H

#include "usb_ssp_drd_if.h"

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
typedef struct USB_SSP_DRD_OBJ_s {
  /**
   * Returns the memory requirements for a driver instance.
   * @param[out] sysReq Returns the memory requirements for given configuration.
   * @return CDN_EOK On success.
   * @return CDN_EINVAL If config contains invalid values or not supported.
   */
  uint32_t (*Probe)(USB_SSP_DRD_SysReq *sysReq);

  /**
   * Instantiates the USB_SSP_DRD Core Driver, given the required
   * blocks of memory (this includes initializing the instance and the
   * underlying hardware). If a client configuration is required
   * (likely to always be true), it is passed in also. Returns an
   * instance pointer, which the client must maintain and pass to all
   * other driver functions. (except probe).
   * @param[in] privData Pointer to driver's private data object.
   * @param[in] config Specifies driver/hardware configuration.
   * @param[in] callbacks Event Handlers and Callbacks.
   * @return CDN_EOK On success
   * @return CDN_EINVAL If illegal/inconsistent values in 'config' doesn't
   * support feature(s) required by 'config' parameters.
   * @return CDN_EIO if operation failed
   */
  uint32_t (*Init)(USB_SSP_DRD_PrivData *privData,
                   const USB_SSP_DRD_Config *config,
                   const USB_SSP_DRD_Callbacks *callbacks);

  /**
   * USB_SSP_DRD Core Driver's ISR. Platform-specific code is
   * responsible for ensuring this gets called when the corresponding
   * hardware's interrupt is asserted. Registering the ISR should be
   * done after calling init, and before calling start. The driver's
   * ISR will not attempt to lock any locks, but will perform client
   * callbacks. If the client wishes to defer processing to non-
   * interrupt time, it is responsible for doing so. This function must
   * not be called after calling destroy and releasing private data
   * memory.
   * @param[in] privData Pointer to driver's private data object filled by init.
   * @return CDN_EOK on success
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*Isr)(USB_SSP_DRD_PrivData *privData);

  /**
   * Start the USB_SSP_DRD driver, enabling interrupts. This is called
   * after the client has successfully initialized the driver and
   * hooked the driver's ISR (the isr member of this struct) to the
   * IRQ.
   * @param[in] privData Pointer to driver's private data object.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*Start)(USB_SSP_DRD_PrivData *privData);

  /**
   * The client may call this to disable the hardware (disabling its
   * IRQ at the source and disconnecting it if applicable). Also, a
   * best-effort is made to cancel any pending transactions.
   * @param[in] privData Pointer to driver's private data object.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*Stop)(const USB_SSP_DRD_PrivData *privData);

  /**
   * This performs an automatic stop and then de-initializes the
   * driver. The client may not make further requests on this instance.
   * @param[in] privData Pointer to driver's private data object.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*Destroy)(const USB_SSP_DRD_PrivData *privData);

  /**
   * Checks if controller is ready.
   * @param[in] privData Pointer to driver's private data object.
   * @param[out] isReady Will tell if controller is ready.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*CheckIfReady)(USB_SSP_DRD_PrivData *privData, bool *isReady);

  /**
   * Checks strap mode of controller.
   * @param[in] privData Pointer to driver's private data object.
   * @param[out] strapMode Will tell how controller is strapped.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*CheckStrapMode)(USB_SSP_DRD_PrivData *privData,
                             USB_SSP_DRD_Mode *strapMode);

  /**
   * Checks current operation mode of controller.
   * @param[in] privData Pointer to driver's private data object.
   * @param[out] operationMode Will tell operation mode of controller.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*CheckOperationMode)(const USB_SSP_DRD_PrivData *privData,
                                 USB_SSP_DRD_Mode *operationMode);

  /**
   * Sets operation mode of controller.
   * @param[in] privData Pointer to driver's private data object.
   * @param[in] operationMode Mode of operation that should be set for
   * controller.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*SetOperationMode)(USB_SSP_DRD_PrivData *privData,
                               const USB_SSP_DRD_Mode operationMode);

  /**
   * Checks if there is an unhndled interrupt pending.
   * @param[in] privData Pointer to driver's private data object.
   * @param[out] interruptVect Interrupt Vector value.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*CheckIrq)(const USB_SSP_DRD_PrivData *privData,
                       uint32_t *interruptVect);

  /**
   * This function will process an interrupt that is pending.
   * @param[in] privData Pointer to driver's private data object.
   * @return CDN_EOK on success
   * @return CDN_EIO if operation failed
   * @return CDN_EINVAL if input parameters are invalid
   */
  uint32_t (*ProcessIrq)(USB_SSP_DRD_PrivData *privData);

} USB_SSP_DRD_OBJ;
/* parasoft-end-suppress MISRA2012-DIR-4_8-4 */

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from
 * more than 5 different functions, DRV-3666" */
/**
 * In order to access the USB_SSP_DRD APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return USB_SSP_DRD_OBJ* Driver Object Pointer
 */
extern USB_SSP_DRD_OBJ *USB_SSP_DRD_GetInstance(void);

/**
 *  @}
 */
/* parasoft-end-suppress METRICS-36-3 */

#endif /* USB_SSP_DRD_OBJ_IF_H */
