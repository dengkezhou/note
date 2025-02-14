/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * host_if.c
 * Cadence-USB-Device TI interface implementation
 *
 *
 *
 *****************************************************************************/
#include "host_if.h"
#include <irq.h>

static int get_desc_pending   = 0;
static CH9_UsbDeviceDescriptor dev_desc;
void sleepTb() {}
static int host_transfer_complete = 0;

int usb_host_irq_handler(int irq, void *args) {
  Host_profile *hprofile = (Host_profile *)args;
  USBSSP_Isr((USBSSP_DriverResourcesT *) hprofile->xhci_driver_resources);
  return 0;
}

static int register_IRQ(USB USBx, Host_profile *hprofile){
  int ret = 0;
  printf("register irq for USB%d\n", USBx);
  switch (USBx)
  {
  case USB0:
    ret = request_irq(C_USB0_CMB0_IRQn, usb_host_irq_handler, irq_name[0][2], (void *)hprofile);
    check_req_irq_ret(ret);
    break;
  case USB1:
    ret = request_irq(C_USB1_CMB0_IRQn, usb_host_irq_handler, irq_name[1][2], (void *)hprofile);
    check_req_irq_ret(ret);
    break;
  case USB2:
    ret = request_irq(C_USB2_CMB0_IRQn, usb_host_irq_handler, irq_name[2][2], (void *)hprofile);
    check_req_irq_ret(ret);
    break;
  case USB3:
    ret = request_irq(C_USB3_CMB0_IRQn, usb_host_irq_handler, irq_name[3][2], (void *)hprofile);
    check_req_irq_ret(ret);
    break;
  default:
    return -1;
    break;
  }
  
  return 0;  
}


static uint8_t getEpIndex(uint8_t epAddress) {

  uint8_t epNum = epAddress & 0x7F;

  // check if IN endpoint
  return (epNum * 2U + ((epAddress & 0x80U) ? 1U : 0U));
}

static void getDevDescComplete(USBSSP_DriverResourcesT *res, uint32_t status,
                               const USBSSP_RingElementT *eventPtr) {

  vDbgMsg(USBSSP_DBG_TEST, DBG_FYI, "getDescComplete status(%d) \n", status);
  if (status == CDN_EOK) {
      memcpy(&dev_desc, res->ep0Buff, sizeof(CH9_UsbDeviceDescriptor));
      printf("[ENUM STATE]: get desc done! data: \n");
      for(int i = 0; i <18; i++) {
        printf("%02x ", res->ep0Buff[i]);
      }
      printf("\n");
      get_desc_pending   = 0;
  }
}

static uint32_t waitUntilAddressState(USBSSP_DriverResourcesT const *res,
                                      uint32_t timeout) {
  uint32_t counter = timeout;
  uint32_t ret     = CDN_EOK;

  /* device must be connected on port */
  while (res->connected == 0U) {
    /* break loop when timeout value is 0 */
    if (counter == 0U) {
      ret = CDN_ETIMEDOUT;
      vDbgMsg(USBSSP_DBG_DRV, DBG_CRIT, "<%d> %s() timeout after %d\n",
              res->instanceNo, __func__, timeout);
      break;
    }
    counter--;
    CPS_DelayNs(1000);
  }

  if (ret == CDN_EOK) {
    counter = timeout;
    while (res->devAddress == 0U) {
      CPS_DelayNs(1000);
      /* break loop when timeout value is 0 */
      if (counter == 0U) {
        ret = CDN_ETIMEDOUT;
        vDbgMsg(USBSSP_DBG_DRV, DBG_CRIT, "<%d> %s() timeout after %d\n",
                res->instanceNo, __func__, timeout);
      } else if (res->connected ==
                 0U) { /* break loop when device is disconnected */
        ret = CDN_EIO;
      } else {
        counter--;
      }
      if (ret != CDN_EOK) {
        break;
      }
    }
  }

  return ret;
}

static void transferComplete(USBSSP_DriverResourcesT *arg, uint32_t status,
                             const USBSSP_RingElementT *eventPtr) {
  vDbgMsg(USBSSP_DBG_EXTERNAL_STACK, DBG_FYI,
          "Transfer complete on endpoint: %d\n", arg->lastEpIntIndex);
  vDbgMsg(USBSSP_DBG_EXTERNAL_STACK, DBG_FYI, "Completion Code: %d\n",
          arg->ep[arg->lastEpIntIndex].completionCode);
  host_transfer_complete = 1;
}

Host_profile *usb_host_init(USB_InitTypeDef *init) {
  int ret;
  Host_profile *hprofile = (Host_profile *)malloc(sizeof(Host_profile));
  if (hprofile == NULL) {
    printf("malloc memory for hprofile failed!\n");
    return NULL;
  }

  memset(hprofile, 0, sizeof(Host_profile));

  hprofile->xhci_driver_resources =
      (USBSSP_DriverResourcesT *)malloc(sizeof(USBSSP_DriverResourcesT));

  memset(hprofile->xhci_driver_resources, 0, sizeof(USBSSP_DriverResourcesT));

  switch (init->USBx) {
  case USB0:
    hprofile->ssp_hw_cores_base = ITCS_C_USB0_BASE + USB_HOST_REGS_OFFSET;
    break;
  case USB1:
    hprofile->ssp_hw_cores_base = ITCS_C_USB1_BASE + USB_HOST_REGS_OFFSET;
    break;
  case USB2:
    hprofile->ssp_hw_cores_base = ITCS_C_USB2_BASE + USB_HOST_REGS_OFFSET;
    break;
  case USB3:
    hprofile->ssp_hw_cores_base = ITCS_C_USB3_BASE + USB_HOST_REGS_OFFSET;
    break;
  default:
    goto err;
    break;
  }
  
  if(register_IRQ(init->USBx, hprofile)){
    goto err;
  }
  udelay(1000);
  //- USB_HOST_REGS_OFFSET
  hprofile->xhci_driver_resources->ipIdVerRegs.didRegPtr = hprofile->ssp_hw_cores_base - USB_HOST_REGS_OFFSET + 0x0; // add by jason
  hprofile->xhci_driver_resources->ipIdVerRegs.ridRegPtr = hprofile->ssp_hw_cores_base - USB_HOST_REGS_OFFSET + 0x4; // add by jason

  vDbgMsg(USBSSP_DBG_EXTERNAL_STACK, DBG_FYI,
          "Initialising driver for instanceNumber: %0d, base address 0x%08x\n",
          init->USBx, hprofile->ssp_hw_cores_base);
  ret = USBSSP_Init(hprofile->xhci_driver_resources, hprofile->ssp_hw_cores_base);

  if(ret){
    printf("USBSSP_Init failed, ret:%d\n", ret);
    goto err;
  }
  
  printf("Successfully initialised driver for instanceNumber: %0d, base address 0x%08x\n",init->USBx, hprofile->ssp_hw_cores_base);
  return hprofile;

err:
  usb_check_free(hprofile->xhci_driver_resources);
  usb_check_free(hprofile);
  return NULL;
}

static uint32_t waitforGetDescComplete() {

  uint32_t ret     = CDN_EOK;
  uint32_t counter = USBSSP_DEFAULT_TIMEOUT;

  while ((get_desc_pending > 0) && (--counter > 0U)) {
    CPS_DelayNs(1000);
  }

  if (get_desc_pending > 0) {
    ret = CDN_ETIMEDOUT;
  }
  if (get_desc_pending < 0) {
    ret = CDN_EPERM;
  }

  return ret;
}


uint32_t usb_host_get_dev_desc(Host_profile *hprofile,
                               CH9_UsbDeviceDescriptor *DevDesc,
                               int retry_times) {
  uint32_t result;
  USBSSP_DriverResourcesT *ssp_ref = hprofile->xhci_driver_resources;

xhci_enumerate_dev:
  printf("wait until address state...");
  result = waitUntilAddressState(ssp_ref, USBSSP_DEFAULT_TIMEOUT);
  if(result != 0) {
    printf("\nsending address state...");
    USBSSP_SetAddress(ssp_ref);
    result = waitUntilAddressState(ssp_ref, USBSSP_DEFAULT_TIMEOUT);
    if (result != 0) {
        printf("failed!\n");
        return result;
    }
  }
  printf("ok\n");
  printf("\n[ ENUM STAGE ]: get device descriptor \n");
  get_desc_pending   = 1;
  result = USBSSP_GetDescriptor(ssp_ref, CH9_USB_DT_DEVICE, getDevDescComplete);
  if (result == CDN_EIO) goto xhci_enumerate_dev;
  else if (result != 0) return result;
  result = waitforGetDescComplete();
  if (result != CDN_EOK) return result;

  printf("\n[ ENUM STAGE ]: get confuguration descriptor \n");
  get_desc_pending   = 1;
  result = USBSSP_GetDescriptor(ssp_ref, CH9_USB_DT_CONFIGURATION, getDevDescComplete);
  if (result == CDN_EIO) goto xhci_enumerate_dev;
  else if (result != 0) return result;
  result = waitforGetDescComplete();
  if (result != CDN_EOK) return result;
  
  printf("\n[ ENUM STAGE ]: set confuguration  \n");
  result = USBSSP_SetConfiguration(ssp_ref, 1);
  if (result == CDN_EIO) goto xhci_enumerate_dev;
  else if (result != CDN_EOK) return result;

  return 0;
}

USB_TRANSFER_STATUS
get_usb_host_transfer_status(USBSSP_DriverResourcesT *ssp_ref,
                             uint8_t uEndPoint) {
  uint32_t result   = 0;
  uint8_t epAddress = uEndPoint;
  uint8_t epIndex   = getEpIndex(epAddress);
  if (ssp_ref->ep[epIndex].isRunningFlag) {
    return TRANSFERING;
  }
  result = ssp_ref->ep[epIndex].completionCode;
  if (result == USBSSP_TRB_COMPLETE_SUCCESS) {
    return TRANSFER_COMPLETE;
  } else {
    return TRANSFER_ERROR;
  }
}

uint32_t usb_host_write(USBSSP_DriverResourcesT *ssp_ref, uint8_t uEndPoint,
                        uint8_t *puData, uint32_t uSize, uint8_t isBlock) {

  uint32_t result   = 0;
  uint8_t epAddress = uEndPoint;
  uint8_t epIndex   = getEpIndex(epAddress);

  vDbgMsg(USBSSP_DBG_EXTERNAL_STACK, DBG_FYI,
          "uEndPoint: %d, puData: %p, uSize: %ld\n", uEndPoint, puData, uSize); 
  host_transfer_complete = 0;
  result = USBSSP_TransferData(ssp_ref, epIndex, (uintptr_t)puData, uSize,
                               transferComplete);
  if (isBlock == 1) {
    while(1){
        udelay(10);
        if(host_transfer_complete){
            host_transfer_complete = 0;
            return 0;
        }
    }
    result = 0;
  }
  return result;
}

uint32_t usb_host_read(USBSSP_DriverResourcesT *ssp_ref, uint8_t uEndPoint,
                       uint8_t *puData, uint32_t uSize, uint8_t isBlock) {

  uint32_t result   = 0;
  uint8_t epAddress = uEndPoint | 0x80;
  uint8_t epIndex   = getEpIndex(epAddress);

  vDbgMsg(USBSSP_DBG_EXTERNAL_STACK, DBG_FYI,
          "uEndPoint: %d, puData: %p, uSize: %ld\n", uEndPoint, puData, uSize);
  result = USBSSP_TransferData(ssp_ref, epIndex, (uintptr_t)puData, uSize,
                               transferComplete);
  if (isBlock == 1) {
    while (ssp_ref->ep[epIndex].isRunningFlag) {
      sleepTb();
    }
    result = ssp_ref->ep[epIndex].completionCode;
    if (result == USBSSP_TRB_COMPLETE_SUCCESS)
      result = uSize;
  }
  return result;
}