#ifndef __USB_DEV_HOST_IF_H__
#define __USB_DEV_HOST_IF_H__

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "cusbd_if.h"


__attribute__((unused)) static const char * irq_name[4][6] = {
  {"usb0_cmb0", "usb0_cmb1", "usb0_host_req0",  "usb0_dev_irqs0", "usb0_otg",  "usb0_phy", },
  {"usb1_cmb0", "usb1_cmb1", "usb1_host_req0",  "usb1_dev_irqs0", "usb1_otg",  "usb1_phy", },
  {"usb2_cmb0", "usb2_cmb1", "usb2_host_req0",  "usb2_dev_irqs0", "usb2_otg",  "usb2_phy", },
  {"usb3_cmb0", "usb3_cmb1", "usb3_host_req0",  "usb3_dev_irqs0", "usb3_otg",  "usb3_phy", }
};

#define check_req_irq_ret(ret)\
  do{\
    if (ret) {\
      return ret;\
    }\
  }while(0)


#define NONBLOCK 0U
#define BLOCK    1U

#define USB_MODE_HOST 0
#define USB_MODE_DEV  1
#define USB_VER_2_0   2
#define USB_VER_3_0   3
#define USB_TX        0
#define USB_RX        1

#define usb_check_free(ptr)                                                    \
  do {                                                                         \
    if (ptr) {                                                                 \
      free(ptr);                                                               \
      ptr = NULL;                                                              \
    }                                                                          \
  } while (0)

typedef enum { USB0 = 0, USB1, USB2, USB3 } USB;

typedef enum {
  TRANSFERING       = 0,
  TRANSFER_COMPLETE = 1,
  TRANSFER_ERROR    = 2
} USB_TRANSFER_STATUS;

typedef struct {
  USB USBx;
  uint8_t mode;    /* USB mode, USB_MODE_HOST 或 USB_MODE_DEV  */
  uint8_t version; /* USB Version, USB_VER_2_0 或  USB_VER_3_0 */
  CUSBD_Callbacks *callbacks; /* if usb device, must fill in. */
  uint8_t ep;
} USB_InitTypeDef;

#endif /*__USB_DEV_HOST_IF_H__*/
