#ifndef __USB_DEVICE_LOOP_H__
#define __USB_DEVICE_LOOP_H__

#include "cusb_ch9_if.h"
#include "cusb_ch9_structs_if.h"
#include "cusbd_if.h"
#include "drd.h"
#include "device_if.h"


uint32_t loop_dev_setup(USB_Handler *usb_handler,CUSBD_PrivateData *pD, CH9_UsbSetup *ctrl);


#endif //__USB_DEVICE_LOOP_H__
