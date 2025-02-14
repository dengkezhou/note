/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     usb.c
 * @brief    cdns usb Driver
 * @version  V1.0
 * @date     06.23 2022
 * @name     usb
 *
 * @author   jason.liu
 *******************************************************************/

#include <common.h>
#include <asm/io.h>
#include <drd.h>
#include <pads.h>
#include "usb_ssp_drd_hw.h"

#define USB_DRD_CDNS_DID        0x0
#define USB_DRD_CDNS_RID        0x4
#define USB_DRD_CDNS_OTGCAPABILITY        0x8
#define USB_DRD_CDNS_OTGCMD     0x10
#define USB_DRD_CDNS_OTGSTS     0x14
#define USB_DRD_CDNS_OTGSTATE   0x18
#define USB_DRD_CDNS_OTGIEN     0x20

#define BIT(nr) (1 << nr)
/* OTGCMD - bitmasks */
/* "Request the bus for Device mode. */
#define OTGCMD_DEV_BUS_REQ		BIT(0)
/* Request the bus for Host mode */
#define OTGCMD_HOST_BUS_REQ		BIT(1)
/* Enable OTG mode. */
#define OTGCMD_OTG_EN			BIT(2)
/* Disable OTG mode */
#define OTGCMD_OTG_DIS			BIT(3)
/*"Configure OTG as A-Device. */
#define OTGCMD_A_DEV_EN			BIT(4)
/*"Configure OTG as A-Device. */
#define OTGCMD_A_DEV_DIS		BIT(5)
/* Drop the bus for Device mod	e. */
#define OTGCMD_DEV_BUS_DROP		BIT(8)
/* Drop the bus for Host mode*/
#define OTGCMD_HOST_BUS_DROP		BIT(9)
/* Power Down USBSS-DEV. */
#define OTGCMD_DEV_POWER_OFF		BIT(11)
/* Power Down CDNSXHCI. */
#define OTGCMD_HOST_POWER_OFF		BIT(12)

/* OTGIEN - bitmasks */
/* ID change interrupt enable */
#define OTGIEN_ID_CHANGE_INT		BIT(0)
/* Vbusvalid fall detected interrupt enable.*/
#define OTGIEN_VBUSVALID_RISE_INT	BIT(4)
/* Vbusvalid fall detected interrupt enable */
#define OTGIEN_VBUSVALID_FALL_INT	BIT(5)

/* OTGSTS - bitmasks */
/*
 * Current value of the ID pin. It is only valid when idpullup in
 *  OTGCTRL1_TYPE register is set to '1'.
 */
#define OTGSTS_ID_VALUE			BIT(0)
/* Current value of the vbus_valid */
#define OTGSTS_VBUS_VALID		BIT(1)
/* Current value of the b_sess_vld */
#define OTGSTS_SESSION_VALID		BIT(2)
/*Device mode is active*/
#define OTGSTS_DEV_ACTIVE		BIT(3)
/* Host mode is active. */
#define OTGSTS_HOST_ACTIVE		BIT(4)
/* OTG Controller not ready. */
#define OTGSTS_OTG_NRDY_MASK		BIT(11)
#define OTGSTS_OTG_NRDY(p)		((p) & OTGSTS_OTG_NRDY_MASK)
/*
 * Value of the strap pins.
 * 000 - no default configuration
 * 010 - Controller initiall configured as Host
 * 100 - Controller initially configured as Device
 */
#define OTGSTS_STRAP(p)			(((p) & GENMASK(14, 12)) >> 12)
#define OTGSTS_STRAP_NO_DEFAULT_CFG	0x00
#define OTGSTS_STRAP_HOST_OTG		0x01
#define OTGSTS_STRAP_HOST		0x02
#define OTGSTS_STRAP_GADGET		0x04
/* Host mode is turned on. */
#define OTGSTS_XHCI_READY		BIT(26)
/* "Device mode is turned on .*/
#define OTGSTS_DEV_READY		BIT(27)

/* OTGSTATE- bitmasks */
#define OTGSTATE_DEV_STATE_MASK		GENMASK(2, 0)
#define OTGSTATE_HOST_STATE_MASK	GENMASK(5, 3)
#define OTGSTATE_HOST_STATE_IDLE	0x0
#define OTGSTATE_HOST_STATE_VBUS_FALL	0x7
#define OTGSTATE_HOST_STATE(p)		(((p) & OTGSTATE_HOST_STATE_MASK) >> 3)

/* OTGREFCLK - bitmasks */
#define OTGREFCLK_STB_CLK_SWITCH_EN	BIT(31)

/* OVERRIDE - bitmasks */
#define OVERRIDE_IDPULLUP		BIT(0)
/* Only for CDNS3_CONTROLLER_V0 version */
#define OVERRIDE_IDPULLUP_V0		BIT(24)



#ifndef CONFIG_COMPILE_FPGA
static void rtl_usb_phy_init(uint32_t base){
    // *******Writing PLL0 Registers for VCO Frequency Setting*******
#if 1
    writel(0x0190, base+0x40000+0x090*4); 
    writel(0x0000, base+0x40000+0x091*4); 
    writel(0x0002, base+0x40000+0x092*4); 
    writel(0x010b, base+0x40000+0x093*4); 
    writel(0x0002, base+0x40000+0x1a0*4); 
    writel(0x0318, base+0x40000+0x088*4); 
    writel(0x0019, base+0x40000+0x0022*4);
    writel(0x0032, base+0x40000+0x002a*4);
    writel(0x00d1, base+0x40000+0x002c*4);
    writel(0x0032, base+0x40000+0x0032*4);
    writel(0x00d1, base+0x40000+0x0034*4);
    writel(0x007d, base+0x40000+0x0064*4);
    writel(0x007d, base+0x40000+0x0065*4);
    writel(0x0019, base+0x40000+0x0074*4);
    writel(0x001e, base+0x40000+0x0104*4);
    writel(0x0006, base+0x40000+0x0105*4);
    writel(0x001e, base+0x40000+0x010c*4);
    writel(0x0006, base+0x40000+0x010d*4);
    writel(0x02ee, base+0x40000+0x0114*4);
    writel(0x0006, base+0x40000+0x0115*4);
    writel(0x0002, base+0x40000+0x0124*4);
    writel(0x0002, base+0x40000+0x0125*4);
    writel(0x000e, base+0x40000+0x0126*4);
    writel(0x012b, base+0x40000+0x0128*4);
    writel(0x0509, base+0x40000+0x01a4*4);
    writel(0x0f00, base+0x40000+0x01a5*4);
    writel(0x0f08, base+0x40000+0x01a6*4);
    writel(0x0004, base+0x40000+0x0094*4);
    writel(0x00fa, base+0x40000+0x0084*4);
    writel(0x0004, base+0x40000+0x0085*4);
    writel(0x00fa, base+0x40000+0x00c4*4);
    writel(0x0004, base+0x40000+0x00c5*4);
    writel(0x0317, base+0x40000+0x0086*4);
    writel(0x8600, base+0x40000+0x01a1*4);
    writel(0x8200, base+0x40000+0x0041*4);
    writel(0x8200, base+0x40000+0x0047*4);
#endif

    writel(0x00000000, base+0x40000+0x00030038);
    writel(0x00008600, base+0x40000+0x00000684);
    writel(0x00000000, base+0x40000+0x00010398);
    writel(0x00000001, base+0x40000+0x0001039c);
    writel(0x00000041, base+0x40000+0x00010394);
    writel(0x00000a0a, base+0x40000+0x00030080);
    writel(0x00001000, base+0x40000+0x00030088);
    writel(0x00000010, base+0x40000+0x0003008c);
    writel(0x00000004, base+0x40000+0x00000208);
    writel(0x00008200, base+0x40000+0x00000104);
    writel(0x00008200, base+0x40000+0x0000011c);
    writel(0x00003400, base+0x40000+0x00000784);
    writel(0x000002fb, base+0x40000+0x00010400);
    writel(0x000006ab, base+0x40000+0x00010404);
    writel(0x000006aa, base+0x40000+0x00010408);
    writel(0x000006aa, base+0x40000+0x0001040c);
    writel(0x00000d1d, base+0x40000+0x00020000);
    writel(0x00000d1d, base+0x40000+0x00020004);
    writel(0x00000d00, base+0x40000+0x00020008);
    writel(0x00000500, base+0x40000+0x0002000c);
    writel(0x00000014, base+0x40000+0x00010134);
    writel(0x0000000a, base+0x40000+0x0001012c);
    writel(0x00000010, base+0x40000+0x0001013c);
    writel(0x00000013, base+0x40000+0x00020240);
    writel(0x00000000, base+0x40000+0x00020420);
    writel(0x00000c02, base+0x40000+0x00020524);
    writel(0x00000330, base+0x40000+0x000205dc);
    writel(0x00000300, base+0x40000+0x000205e0);
    writel(0x00000003, base+0x40000+0x000103ac);
    writel(0x00001002, base+0x40000+0x000207a0);
    writel(0x000000f9, base+0x40000+0x00020794);
    writel(0x00000c01, base+0x40000+0x00020788);
    writel(0x00000002, base+0x40000+0x0002078c);
    writel(0x00000000, base+0x40000+0x000207d4);
    writel(0x00000031, base+0x40000+0x000207d0);
    writel(0x0000018c, base+0x40000+0x00020200);
    writel(0x00000003, base+0x40000+0x00020208);
    writel(0x00000002, base+0x40000+0x0003003c);
}
#endif //CONFIG_COMPILE_RTL

static int check_init_param(USB_InitTypeDef *init) {
  if (init == NULL) {
    printf("init should not be NULL.\n");
    return -1;
  }

  if ((init->USBx > USB3) || (init->USBx < USB0)) {
    printf("USBx should be USB0/1/2/3\n");
    return -1;
  }

  if ((init->mode != USB_MODE_HOST) && (init->mode != USB_MODE_DEV)) {
    printf("mode should be USB_MODE_HOST or USB_MODE_DEV\n");
    return -1;
  }

  if ((init->version != USB_VER_2_0) && (init->version != USB_VER_3_0)) {
    printf("version should be USB_VER_2_0 or USB_VER_23_0\n");
    return -1;
  }

  return 0;
}

static uint32_t usb_get_base(USB_InitTypeDef *init){
  switch (init->USBx) {
  case USB0:
    return ITCS_C_USB0_BASE;
    break;
  case USB1:
    return ITCS_C_USB1_BASE;
    break;
  case USB2:
    return ITCS_C_USB2_BASE;
    break;
  case USB3:
    return ITCS_C_USB3_BASE;
    break;
  default:
  return 0;
    break;
  }
}



int usb_module_init(USB_InitTypeDef *init)
{
  uint32_t phy_base = ITCS_C_USB0_BASE;
  int ret = 0;
  char * module_name = NULL;
  //int freq = 125000000;
  switch(init->USBx){
    case USB0: module_name = "usb0"; 
        phy_base = ITCS_C_USB0_BASE;
      break;
    case USB1: module_name = "usb1"; 
        phy_base = ITCS_C_USB1_BASE;
      break;
    case USB2: module_name = "usb2"; 
        phy_base = ITCS_C_USB2_BASE;
      break;
    case USB3: module_name = "usb3"; 
        phy_base = ITCS_C_USB3_BASE;
      break;
  }

  printf("usb module enable process...\r\n");
  ret = itcs_module_enable(CPU, module_name);
  if(ret){
    printf("usb module enable process failed\r\n");
    return ret;
  }
  printf("usb module enabled\r\n");
  printf("phy base:0x%x\r\n",phy_base);
  #ifndef CONFIG_COMPILE_FPGA
  rtl_usb_phy_init(phy_base);
  #endif

  return 0;
}


static int usb_drd_init_to_host_or_device(USB_InitTypeDef *init){
  uint32_t tmp_reg = 0;
  uint32_t reg_base = usb_get_base(init);
  /* 1.switch drd mode to host or dev */
  if(init->mode == USB_MODE_HOST){
    tmp_reg |= OTGCMD_HOST_BUS_REQ;
    tmp_reg |= OTGCMD_OTG_DIS;
    writel(tmp_reg, reg_base + USB_DRD_CDNS_OTGCMD);
  }else{
    tmp_reg |= OTGCMD_DEV_BUS_REQ;
    tmp_reg |= OTGCMD_OTG_DIS;
    writel(tmp_reg, reg_base + USB_DRD_CDNS_OTGCMD);
  }

  return 0;
}


int usb_host_get_desc(USB_Handler *handler){
    return usb_host_get_dev_desc(handler->hprofile, handler->hprofile->dev_desc, 0xffffffff);
}



USB_Handler *itcs_usb_init(USB_InitTypeDef *init) {
  USB_Handler *handler = NULL;

  if (check_init_param(init)) {
    return NULL;
  }
  #ifndef CONFIG_COMPILE_RTL
  if(usb_module_init(init)){
    return NULL;
  }
  #endif
  usb_drd_init_to_host_or_device(init);

  handler = (USB_Handler *)malloc(sizeof(USB_Handler));

  if (handler == NULL) {
    printf("malloc memory for USB_Handler failed!\n");
    return NULL;
  }

  memset(handler, 0, sizeof(USB_Handler));
  
  memcpy(&handler->USB_InitStruct, init, sizeof(USB_InitTypeDef));
  
  printf("usb init process.\r\n");
  handler->ep = init->ep;
  // USB host initialization
  if (init->mode == USB_MODE_HOST) {
    printf("usb host init process.\r\n");
    handler->hprofile = usb_host_init(init);
    if (handler->hprofile == NULL) {
      printf("usb host initilize failed!\n");
      goto err;
    }
    printf("usb host init done.\r\n");
  } else if (init->mode == USB_MODE_DEV) { // USB device initialization
    printf("usb device init process.\r\n");
    handler->dprofile = usb_dev_init(init);
    if (handler->dprofile == NULL) {
      printf("usb device initilize failed!\n");
      goto err;
    }
    handler->dprofile->cusbdPrivData.userHandler = (void *)handler;
    printf("usb device init done.\r\n");
  }
  
  printf("usb init process done.\r\n");
  return handler;

err:
  usb_check_free(handler->hprofile);
  usb_check_free(handler->dprofile);
  usb_check_free(handler);
  printf("itcs_usb_init error return\r\n");
  return NULL;
}

void itcs_usb_deinit(USB_Handler *handler) {
  usb_check_free(handler->hprofile);
  usb_check_free(handler->dprofile);
  usb_check_free(handler);
  return;
}

int itcs_usb_read(USB_Handler *handler, uint8_t ep, uint32_t size, uint8_t *buf,
                  uint8_t isBlock) {
  int ret = 0;
  if (handler->USB_InitStruct.mode == USB_MODE_HOST) {
    /*
    if(handler->hprofile->dev_desc == NULL){
      ret = usb_host_get_dev_desc(handler->hprofile, handler->hprofile->dev_desc,
                                3);
      if (ret) {
        return ret;
      }
    }
    */
    ret = usb_host_read(handler->hprofile->xhci_driver_resources, ep, buf, size,
                        isBlock);
  } else {
    ret = usb_device_read(&handler->dprofile->cusbdPrivData,
                          handler->dprofile->outReq, handler->dprofile->epOut,
                          buf, size, isBlock);
  }
  return ret;
}

int itcs_usb_write(USB_Handler *handler, uint8_t ep, uint32_t size,
                   uint8_t *buf, uint8_t isBlock) {
  int ret = 0;
  if (handler->USB_InitStruct.mode == USB_MODE_HOST) {
    ret = usb_host_write(handler->hprofile->xhci_driver_resources, ep, buf,
                         size, isBlock);
  } else {
    ret = usb_device_write(&handler->dprofile->cusbdPrivData,
                           handler->dprofile->outReq, handler->dprofile->epOut,
                           buf, size, isBlock);
  }
  return ret;
}

USB_TRANSFER_STATUS itcs_get_usb_transfer_status(USB_Handler *handler,
                                                 uint8_t ep) {
  USB_TRANSFER_STATUS status;
  if (handler->USB_InitStruct.mode == USB_MODE_HOST) {
    status = get_usb_host_transfer_status(
        handler->hprofile->xhci_driver_resources, ep);

  } else {
    if (ep == 0) {
      status = get_usb_device_transfer_status(handler->dprofile->ep0Req);
    } else if (ep <= 15) {
      status = get_usb_device_transfer_status(handler->dprofile->inReq);
    } else {
      status = get_usb_device_transfer_status(handler->dprofile->outReq);
    }
  }
  return status;
}

int itcs_usb_set_mode(USB_Handler *handler, uint8_t mode, uint8_t ver) {
  // dp sth
  return 0;
}