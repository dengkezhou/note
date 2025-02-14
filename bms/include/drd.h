#ifndef __DRD_H__
#define __DRD_H__

#include <host_if.h>
#include <device_if.h>
#include "dev_host_if.h"

typedef struct {
  USB_InitTypeDef USB_InitStruct;
  Host_profile *hprofile;
  Dev_profile *dprofile;
  uint8_t ep;
  uint8_t trans_mode;
} USB_Handler;

int usb_module_init(USB_InitTypeDef *init);
int usb_host_get_desc(USB_Handler *handler);
USB_Handler *itcs_usb_init(USB_InitTypeDef *init);
void itcs_usb_deinit(USB_Handler *handler);
int itcs_usb_read(USB_Handler *handler, uint8_t ep, uint32_t size, uint8_t *buf,
                  uint8_t isBlock);
int itcs_usb_write(USB_Handler *handler, uint8_t ep, uint32_t size,
                   uint8_t *buf, uint8_t isBlock);
USB_TRANSFER_STATUS itcs_get_usb_transfer_status(USB_Handler *handler,
                                                 uint8_t ep);
int itcs_usb_set_mode(USB_Handler *handler, uint8_t mode, uint8_t ver);
#endif //__DRD_H__