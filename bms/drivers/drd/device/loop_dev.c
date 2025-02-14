#include "loop_dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "byteorder.h"
#include "cdn_log.h"
#include "cdn_errno.h"

static CH9_UsbDeviceDescriptor loop_dev_devdesc = {
    .bLength = CH9_USB_DS_DEVICE,
    .bDescriptorType = CH9_USB_DT_DEVICE,
    .bcdUSB = cpuToLe16(0x0200),
    .bDeviceClass = 0,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = cpuToLe16(0x0559),
    .idProduct = cpuToLe16(0x1003),
    .bcdDevice = cpuToLe16(0x0200),
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1
};

static CH9_UsbConfigurationDescriptor loop_dev_confdesc = {
    .bLength = CH9_USB_DS_CONFIGURATION,        //1
    .bDescriptorType = CH9_USB_DT_CONFIGURATION,//1
    .wTotalLength = CH9_USB_DS_CONFIGURATION+CH9_USB_DS_INTERFACE+CH9_USB_DS_ENDPOINT,//2
    .bNumInterfaces = 0x01,//1
    .bConfigurationValue = 0x01,//1
    .iConfiguration = 0x00,//1
    .bmAttributes = CH9_USB_CONFIG_RESERVED|CH9_USB_CONFIG_SELF_POWERED,//1
    .bMaxPower = 0x80//1
};

static CH9_UsbInterfaceDescriptor loop_dev_ifacedesc = {
    .bLength = CH9_USB_DS_INTERFACE,        //1
    .bDescriptorType = CH9_USB_DT_INTERFACE,//1
    .bInterfaceNumber = 0x00,
    .bAlternateSetting = 0x00,
    .bNumEndpoints = 1,
    .bInterfaceClass = 0x08,
    .bInterfaceSubClass = 0x06,
    .bInterfaceProtocol = 0x50,
    .iInterface = 0x00
};

static CH9_UsbEndpointDescriptor loop_dev_ep_desc = {
    .bLength = CH9_USB_DS_ENDPOINT,
    .bDescriptorType = CH9_USB_DT_ENDPOINT,
    .bEndpointAddress = 0x1,
    .bmAttributes = CH9_USB_EP_BULK,
    .wMaxPacketSize = cpuToLe16(64),
    .bInterval = 1
};

static CH9_UsbSSEndpointCompanionDescriptor loop_dev_ep_companion_desc = {
  .bLength = CH9_USB_DS_SS_USB_EP_COMPANION,
  .bDescriptorType = CH9_USB_DT_SS_USB_EP_COMPANION,
  .bMaxBurst = 15,
  .bmAttributes = 0,
  .wBytesPerInterval = 0
};

static void configureDev(USB_Handler *usb_handler, CUSBD_PrivateData *pD) {
    //static uint8_t configValue = 0;
    static uint8_t epDescBuffer[64];    
    CUSBD_Ep * ep;
    LIST_ListHead *list;
    CUSBD_Dev * dev;
    CUSBD_OBJ *drv = usb_handler->dprofile->drv;
    drv->getDevInstance(pD, &dev);
    
    
    for (list = dev->epList.next; list != &dev->epList; list = list->next) {
        ep = (CUSBD_Ep *) list;
        if(ep->address == usb_handler->ep){
            printf("-------ep 0x%x enable------\n", ep->address);
            memmove(epDescBuffer, &loop_dev_ep_desc, CH9_USB_DS_ENDPOINT);
            ep->ops->epEnable(pD, ep, epDescBuffer);
            break;
        }
    }
    
    dev->state = CH9_USB_STATE_CONFIGURED; 
   
}


static void unConfigureDev(USB_Handler *usb_handler, CUSBD_PrivateData *pD) {
    CUSBD_Dev * dev;
    CUSBD_Ep * ep;
    LIST_ListHead *list;

    CUSBD_OBJ *drv = usb_handler->dprofile->drv;
    drv->getDevInstance(pD, &dev);
    printf("*************unconfig device*************\n");
    for (list = dev->epList.next; list != &dev->epList; list = list->next) {
        ep = (CUSBD_Ep *) list;
        ep->ops->epDisable(pD, ep);
    }  
    
    dev->state = CH9_USB_STATE_ADDRESS;
      
}

uint32_t loop_dev_setup(USB_Handler *usb_handler, CUSBD_PrivateData *pD, CH9_UsbSetup *ctrl) {
  CUSBD_Dev *dev;
  int length = 0;  
  CH9_UsbDeviceDescriptor *devDesc;
  CH9_UsbConfigurationDescriptor *configDesc;
  //uint8_t outEpAddress = cusbdss_dev_getOutEpAddress(usb_handler->dprofile);
  //uint8_t inEpAddress = cusbdss_dev_getInEpAddress(usb_handler->dprofile);
  //vDbgMsg(DBG_USB_CTRL_MSG, 1, "######################## setup ################\n");
  ctrl->wIndex  = le16ToCpu(ctrl->wIndex);
  ctrl->wLength = le16ToCpu(ctrl->wLength);
  ctrl->wValue  = le16ToCpu(ctrl->wValue);

  usb_handler->dprofile->drv->getDevInstance(pD, &dev);
  
  devDesc    = &loop_dev_devdesc;
  configDesc = &loop_dev_confdesc;

  //printf("Speed %d: \n", dev->speed);
  //printf("bRequest: %02X\n", ctrl->bRequest);
  //printf("bRequestType: %02X\n", ctrl->bmRequestType);
  //printf("wIndex: %04X\n", ctrl->wIndex);
  //printf("wValue: %04X\n", ctrl->wValue);
  //printf("wLength: %04X\n", ctrl->wLength);


  usb_handler->dprofile->ep0Req->buf = usb_handler->dprofile->ep0Buff;
  usb_handler->dprofile->ep0Req->dma = (uintptr_t) (usb_handler->dprofile->ep0Buff);
  
  switch (ctrl->bRequest) {
  case CH9_USB_REQ_GET_DESCRIPTOR:{
          if( (ctrl->wValue >> 8) == CH9_USB_DT_DEVICE){
              printf("request CH9_USB_DT_DEVICE descriptor!\n");
              length = CH9_USB_DS_DEVICE;
              memmove(usb_handler->dprofile->ep0Buff, devDesc, 18);
              break;
          }else if( (ctrl->wValue >> 8) == CH9_USB_DT_CONFIGURATION){ 
              printf("request CH9_USB_DT_CONFIGURATION descriptor!\n");
              uint8_t conf_desc[64];
              loop_dev_ep_desc.bEndpointAddress = usb_handler->ep;
              loop_dev_ep_desc.bmAttributes = usb_handler->trans_mode;
              if(usb_handler->trans_mode == CH9_USB_EP_BULK){
                loop_dev_ep_desc.bInterval = 0;
                loop_dev_ep_desc.wMaxPacketSize = 512;
              }else if(usb_handler->trans_mode == CH9_USB_EP_ISOCHRONOUS){
                #ifdef CONFIG_COMPILE_RTL
                loop_dev_ep_desc.bInterval = 1;
                #else
                loop_dev_ep_desc.bInterval = 0xFF;
                #endif
                loop_dev_ep_desc.wMaxPacketSize = 512;
              }

              if(dev->speed <= 3){
                memcpy(conf_desc, &loop_dev_confdesc, CH9_USB_DS_CONFIGURATION);
                memcpy(&conf_desc[CH9_USB_DS_CONFIGURATION], &loop_dev_ifacedesc, CH9_USB_DS_INTERFACE);    
                memcpy(&conf_desc[CH9_USB_DS_CONFIGURATION + CH9_USB_DS_INTERFACE], &loop_dev_ep_desc, CH9_USB_DS_ENDPOINT);                       
                length = CH9_USB_DS_CONFIGURATION + CH9_USB_DS_INTERFACE + CH9_USB_DS_ENDPOINT;
              }else{
                loop_dev_confdesc.wTotalLength = CH9_USB_DS_CONFIGURATION+CH9_USB_DS_INTERFACE+CH9_USB_DS_ENDPOINT + CH9_USB_DS_SS_USB_EP_COMPANION;
                memcpy(conf_desc, &loop_dev_confdesc, CH9_USB_DS_CONFIGURATION);
                memcpy(&conf_desc[CH9_USB_DS_CONFIGURATION], &loop_dev_ifacedesc, CH9_USB_DS_INTERFACE);    
                memcpy(&conf_desc[CH9_USB_DS_CONFIGURATION + CH9_USB_DS_INTERFACE], &loop_dev_ep_desc, CH9_USB_DS_ENDPOINT);      
                memcpy(&conf_desc[CH9_USB_DS_CONFIGURATION + CH9_USB_DS_INTERFACE + CH9_USB_DS_ENDPOINT], &loop_dev_ep_companion_desc, CH9_USB_DS_SS_USB_EP_COMPANION);                    
                length = CH9_USB_DS_CONFIGURATION + CH9_USB_DS_INTERFACE + CH9_USB_DS_ENDPOINT + CH9_USB_DS_SS_USB_EP_COMPANION;
              }
              memmove(usb_handler->dprofile->ep0Buff, conf_desc, length);
              break;
          }
      }
  case CH9_USB_REQ_SET_CONFIGURATION:{
      printf("request set configuration!\n");
      if (ctrl->wValue == 0) {
          // un-configure device
          printf("[LOOP_DEV]: unconfigure device\n");
          unConfigureDev(usb_handler, pD);
          return 0;
      }else {
          // configure device
          printf("[LOOP_DEV]: configure device\n");
          configureDev(usb_handler, pD);  
          if (configDesc->bmAttributes & CH9_USB_CONFIG_SELF_POWERED) {
            if (usb_handler->dprofile->drv->dSetSelfpowered) {
                    usb_handler->dprofile->drv->dSetSelfpowered(pD);
                }
            } else {
                if (usb_handler->dprofile->drv->dClearSelfpowered) {
                    usb_handler->dprofile->drv->dSetSelfpowered(pD);
                }
            }
          }
  }
  
  }

  if (length > 0) {
      usb_handler->dprofile->ep0Req->length = ctrl->wLength < length ? ctrl->wLength : length;
      dev->ep0->ops->reqQueue(pD, dev->ep0, usb_handler->dprofile->ep0Req);
  }

  return 0;
}
