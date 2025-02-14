#ifndef __USB_DEVICE_IF_H__
#define __USB_DEVICE_IF_H__

#include "cusb_ch9_if.h"
#include "cusb_ch9_structs_if.h"
#include "cusbd_if.h"
#include "cusbd_structs_if.h"
#include "cusbdma_if.h"
#include "cusbdma_structs_if.h"
#include "cusbd_obj_if.h"
#include "byteorder.h"
#include "cdn_log.h"
#include "cdn_errno.h"
#include "cps.h"
#include "dev_host_if.h"

#define USB_DEV_REGS_OFFSET 0x20000

#define REGISTER_BUFFER_SIZE   (4 * 1024)
#define DMA_ALLOC_SIZE         (4 * 1024)
#define DATA_XFER_BUFFER_COUNT 15
#define DMA_BUFFER_COUNT       (DATA_XFER_BUFFER_COUNT + 1)
#define DBG_USB_CTRL_MSG       0x00000002

#define DEV_EP_IN      0x81
#define DEV_EP_OUT     0x01
#define DEV_INT_EP_IN  0x82
#define DEV_INT_EP_OUT 0x02
#define DEV_ISO_EP_IN  0x82
#define DEV_ISO_EP_OUT 0x02

//-------------- definitions used during configuration -------------------------
#define BCD_USB_SS    0x0320 // 3.00 version USB
#define BCD_USB_HS    0x0200 // 2.00
#define ID_VENDOR     0x0559 // Cadence  VID
#define ID_PRODUCT    0x1003 // example hid product
#define BCD_DEVICE_HS 0x0200 // 2.00
#define BCD_DEVICE_SS 0x0010 // 0.1
#define BCD_USB_HS_ONLY 0x0201  // 2.01  /*Only HS with BOS descriptor*/

#define USB_MANUFACTURER_STRING         "CADENCE"
#define USB_PRODUCT_STRING              "Hid example device"
#define USB_SERIAL_NUMBER_STRING        "100000000000" // should 12 chars long
#define MOUSE_EP_ADDRES_IN 0x01
//------------------------------------------------------------------------------

typedef struct {
  uintptr_t regBase;
  uint8_t dmultEnabled;
  uint8_t forcedUsbMode;

  /* TRB buffers for each endpoint */
  CUSBDMA_MemResources (*epMemRes)[32];

  /* buffer used by the device to get setup packet from host */
  uint8_t *setupBuffer;
  uintptr_t setupBufferPhyAddr;

  /* EP0 buffer for sending descriptors */
  uint8_t *ep0Buffer;
  uintptr_t ep0BufferPhyAddr;

  /* Data transfer buffer */
  uint8_t *dataXferBuffer[DATA_XFER_BUFFER_COUNT];
  uintptr_t dataXferBufferPhyAddr[DATA_XFER_BUFFER_COUNT];
  uint32_t dataXferBufferSize;

  /* data buffer */
  uint8_t *dataBuffer;
  uintptr_t dataBufferPhyAddr;
  uint32_t dataBufferSize;

  /* auxilliary buffer*/
  uint8_t *auxBuffer[15];
  uintptr_t auxBufferPhyAddr[15];
  uint32_t auxBufferSize;
} CUSBDSS_App_Config;

typedef struct {
  CUSBD_OBJ *drv; // driver interface pointer pointer
  CUSBD_PrivateData cusbdPrivData;
  uintptr_t regBase;
  CUSBD_Config config;
  CUSBDSS_App_Config appConfig;
  CUSBDMA_MemResources epMemRes[32];
  void *deviceRegisters;

  volatile void *trbMem;
  uint64_t trbMemPhyAddr;
  volatile void *dmaMem[DMA_BUFFER_COUNT];
  uint64_t dmaMemPhyAddr[DMA_BUFFER_COUNT];
  volatile void *auxMem[15];
  uint64_t auxMemPhyAddr[15];

  uint8_t cusbdss_epCfgMode;
  CUSBD_Req CmdReq;
  CUSBD_Req *ep0Req;
  CUSBD_Req *inReq;
  CUSBD_Req *outReq;
  CUSBD_Ep *epIn;
  CUSBD_Ep *epOut;
  uint8_t *ep0Buff;
  uintptr_t ep0BufferPhyAddr;
} Dev_profile;
CH9_UsbConfigurationDescriptor *
cusbdss_devcfg_getConfigDesc(CH9_UsbSpeed devSpeed);
CH9_UsbDeviceDescriptor *cusbdss_devcfg_getDeviceDesc(CH9_UsbSpeed devSpeed);
uint8_t cusbdss_dev_getInEpAddress(Dev_profile *dprofile);
uint8_t cusbdss_dev_getOutEpAddress(Dev_profile *dprofile);
Dev_profile *usb_dev_init(USB_InitTypeDef *init);
USB_TRANSFER_STATUS get_usb_device_transfer_status(CUSBD_Req *req);
uint32_t usb_device_read(CUSBD_PrivateData *pD, CUSBD_Req *req, CUSBD_Ep *ep,
                         uint8_t *puData, uint32_t uSize, uint8_t isBlock);
uint32_t usb_device_write(CUSBD_PrivateData *pD, CUSBD_Req *req, CUSBD_Ep *ep,
                          uint8_t *puData, uint32_t uSize, uint8_t isBlock);

#endif /*__USB_DEVICE_IF_H__*/