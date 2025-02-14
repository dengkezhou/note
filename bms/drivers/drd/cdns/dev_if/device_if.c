#include <device_if.h>
#include <irq.h>
#include <malloc.h>
static int usb_dev_write_complete_flg, usb_dev_read_complete_flg;
static CUSBD_Req ep0ReqAlloc, inReqAlloc, outReqAlloc;

//------------------- descriptor set--------------------------------------------
// device descriptor for SuperSpeed mode
static CH9_UsbDeviceDescriptor devSsDesc = {
    CH9_USB_DS_DEVICE,
    CH9_USB_DT_DEVICE,
    cpuToLe16(BCD_USB_SS),
    0,
    0,
    0,
    9,
    cpuToLe16(ID_VENDOR),
    cpuToLe16(ID_PRODUCT),
    cpuToLe16(BCD_DEVICE_SS),
    1,
    2,
    3,
    1
};

// device descriptor for HighSpeed mode
static CH9_UsbDeviceDescriptor devHsDesc = {
    CH9_USB_DS_DEVICE,
    CH9_USB_DT_DEVICE,
    cpuToLe16(BCD_USB_HS),
    0,
    0,
    0,
    64,
    cpuToLe16(ID_VENDOR),
    cpuToLe16(ID_PRODUCT),
    cpuToLe16(BCD_DEVICE_HS),
    1,
    2,
    3,
    1
};
//------------- Start of Super Speed configuration descriptors -----------------
// configuration descriptors for SuperSpeed mode
static CH9_UsbConfigurationDescriptor confSsDesc = {
    CH9_USB_DS_CONFIGURATION,
    CH9_USB_DT_CONFIGURATION,
    cpuToLe16(
    CH9_USB_DS_CONFIGURATION
    + CH9_USB_DS_INTERFACE
    + 2 * CH9_USB_DS_ENDPOINT
    + 2 * CH9_USB_DS_SS_USB_EP_COMPANION),
    1,
    1,
    0,
    CH9_USB_CONFIG_RESERVED | CH9_USB_CONFIG_SELF_POWERED,
    1
};
/*
//0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00,
static CH9_UsbInterfaceDescriptor interfaceDesc = {
    CH9_USB_DS_INTERFACE,
    CH9_USB_DT_INTERFACE,
    0,
    0,
    2,
    CH9_USB_CLASS_VENDOR,
    0,
    0,
    0
};
*/
//------------------- End of Super Speed configuration -------------------------

//------------- Start of High Speed configuration descriptors -----------------
// configuration descriptors for HighSpeed mode
static CH9_UsbConfigurationDescriptor confHsDesc = {
    CH9_USB_DS_CONFIGURATION,
    CH9_USB_DT_CONFIGURATION,
    cpuToLe16(
    CH9_USB_DS_CONFIGURATION
    + CH9_USB_DS_INTERFACE
    + 2 * CH9_USB_DS_ENDPOINT),
    1,
    1,
    0,
    CH9_USB_CONFIG_RESERVED | CH9_USB_CONFIG_SELF_POWERED,
    0
};


uint8_t epout_buf[1024];

int usb_dev_irq_handler(int irq, void *args) {
  Dev_profile *dprofile = (Dev_profile *)args;
  //printf("\n[USB DEV]: irq arrive\n");
  dprofile->drv->isr(&(dprofile->cusbdPrivData));
  return 0;
}

static void displayEndpointInfo(CUSBD_Ep * ep) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "-------Endpoint INFO------------- %c\n", ' ');
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "address: %02X\n", ep->address);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "epList: %08X\n", (uintptr_t) & ep->epList);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "name: %s\n", ep->name);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "ops: %c\n", ' ');

}

static int register_IRQ(USB USBx, Dev_profile *dprofile){
  int ret = 0;
  switch (USBx)
  {
  case USB0:
      ret = request_irq(C_USB0_CMB1_IRQn, usb_dev_irq_handler, irq_name[0][3], (void *)dprofile);
      check_req_irq_ret(ret);
    break;
  case USB1:
      ret = request_irq(C_USB1_CMB1_IRQn, usb_dev_irq_handler, irq_name[1][3], (void *)dprofile);
      check_req_irq_ret(ret);
    break;
  case USB2:
      ret = request_irq(C_USB2_CMB1_IRQn, usb_dev_irq_handler, irq_name[2][3], (void *)dprofile);
      check_req_irq_ret(ret);
    break;
  case USB3:
      ret = request_irq(C_USB3_CMB1_IRQn, usb_dev_irq_handler, irq_name[3][3], (void *)dprofile);
      check_req_irq_ret(ret);
    break;
  default:
    return -1;
    break;
  }
  
  return 0;  
}

CH9_UsbConfigurationDescriptor *cusbdss_devcfg_getConfigDesc(CH9_UsbSpeed devSpeed) {
    CH9_UsbConfigurationDescriptor *configDesc = NULL;

    // select descriptors according to actual speed
    switch (devSpeed) {
        case CH9_USB_SPEED_FULL:
            configDesc = &confHsDesc;
            break;
        case CH9_USB_SPEED_HIGH:
            configDesc = &confHsDesc;
            break;
        case CH9_USB_SPEED_SUPER:
            configDesc = &confSsDesc;
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, 1, "Unknown speed %d: \n", devSpeed);
            break;
    }
    return configDesc;
}

CH9_UsbDeviceDescriptor *cusbdss_devcfg_getDeviceDesc(CH9_UsbSpeed devSpeed) {
    CH9_UsbDeviceDescriptor * devDesc = NULL;
    // select descriptors according to actual speed
    switch (devSpeed) {
        case CH9_USB_SPEED_FULL:
            devDesc = &devHsDesc;
            break;
        case CH9_USB_SPEED_HIGH:
            devDesc = &devHsDesc;
            break;
        case CH9_USB_SPEED_SUPER:
            devDesc = &devSsDesc;
            break;
        default:
            vDbgMsg(DBG_GEN_MSG, 1, "Unknown speed %d: \n", devSpeed);
            break;
    }
    return devDesc;
}

static void devWriteComplete(CUSBD_Ep *ep, CUSBD_Req *req) {
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "Request on endpoint %s completed\n", ep->name);
  usb_dev_write_complete_flg = 1;
}

static void devReadComplete(CUSBD_Ep *ep, CUSBD_Req *req) {
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "Request on endpoint %s completed\n", ep->name);
  usb_dev_read_complete_flg = 1;
}

static unsigned long getPhysicalAddress(volatile void *virtualAddr) {
  unsigned long phyAddress = 0;
  phyAddress          = (unsigned long)virtualAddr;
  return phyAddress;
}

void clearMem(volatile uint8_t *memPtr, uint8_t val, int size) {
  memset((void *)memPtr, 0, size);
  #if 0
  int idx = 0;
  while (idx < size) {
    memPtr[idx++] = val;
  }
  return;
  #endif
}

uint32_t allocateMemory(Dev_profile *dprofile) {
  int ret = 0;
  int idx;

  dprofile->deviceRegisters = malloc(REGISTER_BUFFER_SIZE);
  if (dprofile->deviceRegisters == NULL) {
    ret = -1;
    printf("Error in obtaining deviceRegisters memory \n");
    goto allocateMemory_exit;
  }
  clearMem((volatile uint8_t *)dprofile->deviceRegisters, 0,
           REGISTER_BUFFER_SIZE);

  dprofile->trbMem = malloc(DMA_ALLOC_SIZE);
  if (dprofile->trbMem == NULL) {
    ret = -1;
    printf("Error in obtaining TRB memory \n");
    goto allocateMemory_exit;
  }
  clearMem((volatile uint8_t *)dprofile->trbMem, 0, DMA_ALLOC_SIZE);
  dprofile->trbMemPhyAddr = getPhysicalAddress(dprofile->trbMem);
  printf("Mapped (%d) bytes at: 0x%lx\n", DMA_ALLOC_SIZE,
         (unsigned long)dprofile->trbMem);

  for (idx = 0; idx < DMA_BUFFER_COUNT; idx++) {
    dprofile->dmaMem[idx] = malloc(DMA_ALLOC_SIZE);
    if (dprofile->dmaMem[idx] == NULL) {
      ret = -1;
      printf("Error in obtaining dmaMem[%d] memory \n", idx);
      goto allocateMemory_exit;
    }
    clearMem((volatile uint8_t *)dprofile->dmaMem[idx], 0, DMA_ALLOC_SIZE);
    dprofile->dmaMemPhyAddr[idx] = getPhysicalAddress(dprofile->dmaMem[idx]);
  }

  for (idx = 0; idx < 15; idx++) {
    dprofile->auxMem[idx] = malloc(DMA_ALLOC_SIZE);
    if (dprofile->auxMem[idx] == NULL) {
      ret = -1;
      printf("Error in obtaining auxMem[%d] memory \n", idx);
      goto allocateMemory_exit;
    }
    clearMem((volatile uint8_t *)dprofile->auxMem[idx], 0, DMA_ALLOC_SIZE);
    dprofile->auxMemPhyAddr[idx] = getPhysicalAddress(dprofile->auxMem[idx]);
  }
allocateMemory_exit:
  return ret;
}

void initAppConfig(Dev_profile *dprofile) {
  int idx;
  int trbBufferSize = DMA_ALLOC_SIZE / 32;

  memset(&dprofile->appConfig, 0, sizeof(CUSBDSS_App_Config));

  /* dummy register base */
  dprofile->appConfig.regBase       = (uintptr_t)dprofile->deviceRegisters;
  dprofile->appConfig.forcedUsbMode = 3U;

  for (idx = 0; idx < 32; idx++) {
    dprofile->epMemRes[idx].trbAddr =
        (CUSBDMA_DmaTrb *)(((uint8_t *)dprofile->trbMem) +
                           (trbBufferSize * idx));
    dprofile->epMemRes[idx].trbBufferSize = trbBufferSize;
    dprofile->epMemRes[idx].trbDmaAddr =
        dprofile->trbMemPhyAddr + (trbBufferSize * idx);
    /*
    printf("[initAppConfig %d]: epMemRes[%d]: trbAddr(0x%lx) trbDmaAddr(%lx)\n",
           __LINE__, idx, (unsigned long)dprofile->epMemRes[idx].trbAddr,
           (unsigned long)dprofile->epMemRes[idx].trbDmaAddr);
    */
  }

  dprofile->appConfig.setupBuffer        = (uint8_t *)dprofile->dmaMem[0];
  dprofile->appConfig.setupBufferPhyAddr = dprofile->dmaMemPhyAddr[0];
  /*
  printf("[initAppConfig %d]: setupBuffer(0x%lx) setupBufferPhyAddr(%lx)\n",
         __LINE__, (unsigned long)dprofile->appConfig.setupBuffer,
         (unsigned long)dprofile->appConfig.setupBufferPhyAddr);
  */
  dprofile->appConfig.ep0Buffer = ((uint8_t *)dprofile->dmaMem[0]) + 2048;
  dprofile->appConfig.ep0BufferPhyAddr = dprofile->dmaMemPhyAddr[0] + 2048;

  for (idx = 0; idx < 15; idx++) {
    dprofile->appConfig.auxBuffer[idx] = (uint8_t *)dprofile->auxMem[idx];
    dprofile->appConfig.auxBufferPhyAddr[idx] =
        (uintptr_t)dprofile->auxMemPhyAddr[idx];
    dprofile->appConfig.auxBufferSize = 1024;
  }

  dprofile->appConfig.epMemRes = &dprofile->epMemRes;
  return;
}

Dev_profile *usb_dev_init(USB_InitTypeDef *init) {
  int i;
  uint32_t res;
  CUSBD_SysReq sysReqCusbd;
  CUSBD_OBJ *drv        = NULL;
  CUSBD_Dev *dev        = NULL;
  CUSBD_PrivateData *pD = NULL;
  LIST_ListHead *list;
  
  Dev_profile *dprofile = (Dev_profile *)malloc(sizeof(Dev_profile));
  if (dprofile == NULL) {
    printf("malloc memory for dprofile failed!\n");
    return NULL;
  }

  memset(dprofile, 0, sizeof(Dev_profile));

  switch (init->USBx) {
  case USB0:
    dprofile->regBase = ITCS_C_USB0_BASE;
    break;
  case USB1:
    dprofile->regBase = ITCS_C_USB1_BASE;
    break;
  case USB2:
    dprofile->regBase = ITCS_C_USB2_BASE;
    break;
  case USB3:
    dprofile->regBase = ITCS_C_USB3_BASE;
    break;
  default:
    goto error;
    break;
  }
  
  pD = &dprofile->cusbdPrivData;
  
  printf("alloc memory for cusbd...\n");
  res = allocateMemory(dprofile);
  if (res) {
    printf("alloc memory for cusbd failed.\n");
    goto error;
  }
  printf("alloc memory for cusbd successfully\n");
  dprofile->ep0Req = &ep0ReqAlloc;
  dprofile->inReq  = &inReqAlloc;
  dprofile->outReq = &outReqAlloc;
  
  printf("initAppConfig\n");
  initAppConfig(dprofile);
  printf("initAppConfig done\n");

  // buffer address?
  dprofile->ep0Buff = dprofile->appConfig.ep0Buffer;

  memset(&dprofile->config, 0, sizeof(CUSBD_Config));

  dprofile->config.regBase           = dprofile->regBase + USB_DEV_REGS_OFFSET;
  dprofile->config.epMemRes          = &dprofile->epMemRes;
  dprofile->config.dmaInterfaceWidth = CUSBD_DMA_64_WIDTH;
  dprofile->config.dmultEnabled      = dprofile->appConfig.dmultEnabled;
  dprofile->config.forcedUsbMode     = dprofile->appConfig.forcedUsbMode;
  dprofile->config.setupPacket =
      (CH9_UsbSetup *)(void *)dprofile->appConfig.setupBuffer;
  dprofile->config.setupPacketDma = dprofile->appConfig.setupBufferPhyAddr;

  for (i = 0; i < 15; i++) {
    dprofile->config.epOutAuxBufferCfg[i].bufferAddr =
        dprofile->appConfig.auxBuffer[i];
    dprofile->config.epOutAuxBufferCfg[i].bufferSize =
        dprofile->appConfig.auxBufferSize;
  }

  for (i = 0; i < 15; i++) {
    dprofile->config.epIN[i].bufferingValue  = 0;
    dprofile->config.epOUT[i].bufferingValue = 0;
  }
  
  printf("alloc hw buffer for ep %d\n", init->ep);
  dprofile->config.epIN[init->ep - 1].bufferingValue  = 2;
  dprofile->config.epOUT[init->ep - 1].bufferingValue = 2;

  /*
  for (i = 0; i < 3; i++) {
    dprofile->config.epIN[i].bufferingValue  = 2;
    dprofile->config.epOUT[i].bufferingValue = 2;
  }
  
  
  for (i = 3; i < 15; i++) {
    dprofile->config.epIN[i].bufferingValue  = 0;
    dprofile->config.epOUT[i].bufferingValue = 0;
  }
  */
  printf("cusbd get instance\n");
  dprofile->drv = CUSBD_GetInstance(); // get driver handle
  printf("cusbd get instance done\n");
  drv           = dprofile->drv;
  
  printf("cusbd probe\n");
  dprofile->config.didRegPtr = dprofile->regBase + 0x0; // add by jason
  dprofile->config.ridRegPtr = dprofile->regBase + 0x4; // add by jason
  
  if(init->version == USB_VER_2_0){
    dprofile->config.forcedUsbMode = 2;
  }else{
    dprofile->config.forcedUsbMode = 0;
  }

  res = drv->probe(&(dprofile->config), &sysReqCusbd);
  if (res != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Probe Failed : Error: (0x%X)\n", res);
    goto error;
  }
  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "cusbd probe done, device memory requirement: %ld bytes\n",
          sysReqCusbd.privDataSize);

  /* clear memory for private data */
  memset(pD, 0, (size_t)(sysReqCusbd.privDataSize));

  memcpy(&(pD->config), &(dprofile->config), sizeof(dprofile->config));

  vDbgMsg(DBG_GEN_MSG, 1, "Initializing driver\n", 0);
  if (init->callbacks != NULL) {
    printf("cusbd init\n");
    res = drv->init(pD, &(dprofile->config), init->callbacks);
    if(res){
        printf("cusbd init failed, res = %d\n",res);
        goto error;
    }
    printf("cusbd init done\n");
  } else {
    printf("USB device controler, callbacks must be filled.\n");
    goto error;
  }
  if (res != 0) {
    goto error;
  }
  vDbgMsg(DBG_GEN_MSG, 1, "Initializing OK! %s\n", " ");

  // checking device and endpoints parameters correctness
  // get CUSBD device instance exposed as Linux gadget device
  printf("cusbd get dev instance\n");
  drv->getDevInstance(pD, &dev);
  printf("cusbd get dev instance done\n");
  // displayDeviceInfo(dev);

  // allocate request for ep0
  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "EP%d\n", 0);
  dprofile->ep0Req = &(dprofile->CmdReq);

  /*Change descriptor for maxSpeed == HS only Device*/
  /*For USB2.0 we have to modified wTotalLength of BOS descriptor*/
  // cusbdss_devcfg_setMaxSpeed(dev->maxSpeed);
  if(register_IRQ(init->USBx, dprofile)){
    goto error;
  }
  
  for (list = dev->epList.next; list != &dev->epList; list = list->next) {
    CUSBD_Ep *ep = (CUSBD_Ep *)list;
    if (ep->address == init->ep) {
      displayEndpointInfo(ep);
      dprofile->epOut = ep;
      dprofile->outReq->buf      = epout_buf;
      dprofile->outReq->dma      = (uintptr_t)epout_buf;
      break;
    }
  }

  printf("cusbd drv start\n");
  drv->start(pD);
  printf("cusbd drv start done\n");


  return dprofile;

error:
  usb_check_free(dprofile);
  return NULL;
}

USB_TRANSFER_STATUS get_usb_device_transfer_status(CUSBD_Req *req) {
  if (req->status == CDN_EOK) {
    return TRANSFER_COMPLETE;
  } else {
    return TRANSFER_ERROR;
  }
}

uint32_t usb_dev_read_queue_request(CUSBD_PrivateData *pD, CUSBD_Req *req,
                                    CUSBD_Ep *ep, uint8_t *puData,
                                    uint32_t uSize) {
  uint32_t status = CDN_EOK;

  req->buf      = puData;
  req->dma      = (uintptr_t)puData;
  req->complete = devReadComplete;
  req->length   = uSize;
  req->streamId = 0;

  status = ep->ops->reqQueue(pD, ep, req);
  return status;
}

uint32_t usb_dev_write_queue_request(CUSBD_PrivateData *pD, CUSBD_Req *req,
                                     CUSBD_Ep *ep, uint8_t *puData,
                                     uint32_t uSize) {
  uint32_t status = CDN_EOK;

  req->buf      = puData;
  req->dma      = (uintptr_t)puData;
  req->complete = devWriteComplete;
  req->length   = uSize;
  req->streamId = 0;

  status = ep->ops->reqQueue(pD, ep, req);
  return status;
}

uint32_t usb_device_read(CUSBD_PrivateData *pD, CUSBD_Req *req, CUSBD_Ep *ep,
                         uint8_t *puData, uint32_t uSize, uint8_t isBlock) {
  uint32_t result = 0;

  result = usb_dev_read_queue_request(pD, req, ep, puData, uSize);
  if (result) {
    return result;
  }
  if (isBlock == 1) {
    while (1) {
      if (usb_dev_read_complete_flg) {
        usb_dev_read_complete_flg = 0;
        break;
      }
    }
  }
  return result;
}

uint32_t usb_device_write(CUSBD_PrivateData *pD, CUSBD_Req *req, CUSBD_Ep *ep,
                          uint8_t *puData, uint32_t uSize, uint8_t isBlock) {
  uint32_t result = 0;

  result = usb_dev_write_queue_request(pD, req, ep, puData, uSize);
  if (result) {
    return result;
  }
  if (isBlock == 1) {
    while (1) {
      if (usb_dev_write_complete_flg) {
        usb_dev_write_complete_flg = 0;
        break;
      }
    }
  }
  return result;
}