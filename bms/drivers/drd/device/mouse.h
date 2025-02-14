#ifndef __USB_DEVICE_MOUSE_H__
#define __USB_DEVICE_MOUSE_H__

#ifndef HID_CFG_H
#define HID_CFG_H

#include "cusb_ch9_if.h"
#include "cusb_ch9_structs_if.h"
#include "cusbd_if.h"
#include "drd.h"
#include "device_if.h"






uint8_t hid_devcfg_setEpMode(uint8_t epMode);

void hid_devcfg_setMaxSpeed(CH9_UsbSpeed maxSpeed);

CH9_UsbSpeed hid_devcfg_updateSpeed(CH9_UsbSpeed devSpeed);

CH9_UsbConfigurationDescriptor *hid_devcfg_getConfigDesc(CH9_UsbSpeed devSpeed);

CH9_UsbDeviceDescriptor *hid_devcfg_getDeviceDesc(CH9_UsbSpeed devSpeed);

char* hid_dev_getLanguageDesc();
char* hid_dev_getVendorDesc();

char* hid_dev_getProductDesc();

char* hid_dev_getSerialDesc();

CH9_UsbDeviceQualifierDescriptor* hid_dev_getQualifierDesc();

int hid_dev_getOtgDesc(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed);
int hid_dev_getHidDesc(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed);
int hid_dev_getHidIntDesc(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed);

int hid_dev_getSpeedConfiguration(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed);

int hid_dev_getOtherSpeedCfg(uint8_t* ep0Buffer, CH9_UsbSpeed devSpeed);
int hid_dev_getConfiguration(uint8_t* ep0Buffer, CH9_UsbSpeed devSpeed);

int hid_dev_getBOSDesc(uint8_t* ep0Buffer, CH9_UsbSpeed maxSpeed);

int hid_dev_getEpDesc(uint8_t* buffer, uint8_t epAddress);

uint8_t hid_dev_getInEpAddress();

uint8_t hid_dev_getOutEpAddress();

uint8_t hid_dev_getXferMode();
uint32_t mouse_setup(USB_Handler *usb_handler,CUSBD_PrivateData *pD, CH9_UsbSetup *ctrl);
#endif

#endif //__USB_DEVICE_MOUSE_H__
