# USB相关公共接口说明

## 头文件

```c
#include <drd.h>
```

## 接口说明

* USB初始化
	```c 
	USB_Handler *itcs_usb_init(USB_InitTypeDef *init);
	```
	|参数/返回值|说明|
	|--|--|
	|init| 初始化结构体|
	|返回值|返回值说明|
	|NULL|初始化失败|
	|!NULL|初始化成功，返回USB句柄|


	结构体说明:<br>
	1.USB_InitTypeDef

	|结构体参数|必填|参数说明|
	|--|--|--|
	|usb_mode|是|USB运行模式,取值范围:<br>USB_MODE_HOST<br>USB_MODE_DEV|
	|USBx|是|USB控制器接口，取值范围:<br>USB0<br>USB1<br>USB2<br>USB3|
	|version|是|USB协议版本，取值范围:<br>USB_VER_2_0<br>USB_VER_3_0|
	|callbacks|见说明|当usb_mode为USB_MODE_DEV时为必填，否则填NULL|

	2.CUSBD_Callbacks 
	|结构体参数|必填|参数说明|
	|--|--|--|
	|disconnect|是|设备从USB总线上断开的回调|
	|connect|是|设备连接上USB总线的回调|
	|setup|是|设备收到令牌包的回调|
	|suspend|否|设备被挂起的回调|
	|resume|否|设备从挂起中恢复的回调|
	|businterval|否|接收到ITP（Isochronous Timestamp Packet）的回调|
	|descMissing|否|设备描述符缺失的回调|
	|usb2PhySoftReset|否|设备软件复位的回调|


* USB去初始化
	```c 
	void itcs_usb_deinit(USB_Handler *handler);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| USB句柄|
	|返回值|-|		

* USB读
	```c 
	int itcs_usb_read(USB_Handler *handler, uint8_t ep, uint32_t size, uint8_t *buf，uint8_t isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| USB句柄|
	|ep| 端点号|
	|size| 读取的字节数|
	|buf| 读取后存放数据的buffer地址|
	|返回值|返回值说明|
	|非0|读取失败，并返回错误码|
	|0|读取成功或非阻塞返回|	

* USB写
	```c 
	int itcs_usb_write(USB_Handler *handler, uint8_t ep, uint32_t size,uint8_t *buf, uint8_t isBlock);	
	```
	|参数/返回值|说明|
	|--|--|
	|handler| USB句柄|
	|ep| 端点号|
	|size| 写入的字节数|
	|buf| 要写入sdmmc数据的buffer地址|
	|返回值|返回值说明|
	|非0|写入失败，并返回错误码|
	|0|写入成功或非阻塞返回|

* 获取USB传输状态
	```c 
	USB_TRANSFER_STATUS itcs_get_usb_transfer_status(USB_Handler *handler,uint8_t ep);	
	```
	|参数/返回值|说明|
	|--|--|
	|handler| USB句柄|
	|ep| 端点号|
	|返回值|返回值说明|
	|TRANSFERING|数据正在传输，还未完成|
	|TRANSFER_COMPLETE|数据传输完成|
	|TRANSFER_ERROR|数据传输发生错误|

* 切换USB模式
	```c 
	int itcs_usb_set_mode(USB_Handler *handler, uint8_t mode, uint8_t ver);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| USB句柄|
	|mode| USB模式，取值范围:<br>USB_MODE_HOST<br>USB_MODE_DEV|
	|ver| USB版本，取值范围:<br>USB_VER_2_0<br>USB_VER_3_0|
	|返回值|返回值说明|
	|非零|切换失败，并返回错误码|
	|0|切换成功|

## 示例代码

* HOST

```c 
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>
#include <drd.h>

#define SUCCESS 1
#define FAILURE 0

#define USB_HOST_EP_OUT 16
#define USB_HOST_EP_IN  2

#define USB_DEV_EP_OUT 16
#define USB_DEV_EP_IN  2
static uint8_t read_buf[32];
static uint8_t write_buf[32];


static int fillin_init_param(USB_InitTypeDef *init) {
  init->USBx    = USB0;
  init->mode    = USB_MODE_HOST;
  init->version = USB_VER_2_0;
  init->callbacks = NULL;
  return 0;
}

static int usb_host_wr_test(USB_Handler *handler) {
  int ret;
  memset(write_buf, 0xAA, sizeof(write_buf));
  ret = itcs_usb_read(handler, USB_HOST_EP_IN, sizeof(read_buf), read_buf,
                      NONBLOCK);
  if (ret < 0) {
    printf("usb read error, ret = %d", ret);
    return -1;
  }

  ret = itcs_usb_write(handler, USB_HOST_EP_OUT, sizeof(write_buf), write_buf,
                       NONBLOCK);
  if (ret < 0) {
    printf("usb write error, ret = %d", ret);
    return -1;
  }

  // Waiting for tx complete.
  while (itcs_get_usb_transfer_status(handler, USB_TX) == TRANSFERING)
    ;
  // Waiting for rx complete.
  while (itcs_get_usb_transfer_status(handler, USB_RX) == TRANSFERING)
    ;

  if (memcmp(read_buf, write_buf, sizeof(read_buf))) {
    printf("host write & read test error, data is not same!\n");
  }

  if (handler->USB_InitStruct.version == USB_VER_2_0) {
    printf("Test DRD usb2.0 Host Mode Pass.\n");
  } else if (handler->USB_InitStruct.version == USB_VER_3_0) {
    printf("Test DRD usb3.0 Host Mode Pass.\n");
  }
  return 0;
}

int main(){
	USB_InitTypeDef init;
  	USB_Handler *handle;
	fillin_init_param(&init);
	handle      = itcs_usb_init(&init);
	usb_host_wr_test(handle);
	return 0;
}

```

* DEVICE

```c
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>
#include <drd.h>

#define SUCCESS 1
#define FAILURE 0

#define USB_HOST_EP_OUT 16
#define USB_HOST_EP_IN  2

#define USB_DEV_EP_OUT 16
#define USB_DEV_EP_IN  2
static uint8_t read_buf[32];
static uint8_t write_buf[32];

static void connect(CUSBD_PrivateData *pD) {
  CUSBD_Dev *dev;
  usb_handler->dprofile->drv->getDevInstance(pD, &dev);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "Application: connect at %d speed\n",
          dev->speed);
}

static void disconnect(CUSBD_PrivateData *pD) {
  printf("\nApplication: disconnect\n");
}

static void ep0reqComplete(CUSBD_Ep *ep, CUSBD_Req *req) {
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "Request on endpoint %s completed\n", ep->name);
}

static uint32_t setup(CUSBD_PrivateData *pD, CH9_UsbSetup *ctrl) {

  CUSBD_Dev *dev;
  // int length = 0;

  CH9_UsbConfigurationDescriptor *configDesc;
  CH9_UsbDeviceDescriptor *devDesc;
  // uint8_t outEpAddress = cusbdss_dev_getOutEpAddress(usb_handler->dprofile);
  // uint8_t inEpAddress = cusbdss_dev_getInEpAddress(usb_handler->dprofile);

  ctrl->wIndex  = le16ToCpu(ctrl->wIndex);
  ctrl->wLength = le16ToCpu(ctrl->wLength);
  ctrl->wValue  = le16ToCpu(ctrl->wValue);

  usb_handler->dprofile->drv->getDevInstance(pD, &dev);

  configDesc = cusbdss_devcfg_getConfigDesc(dev->speed);
  devDesc    = cusbdss_devcfg_getDeviceDesc(dev->speed);

  if ((configDesc == NULL) || (devDesc == NULL)) {
    return CDN_EINVAL;
  }

  vDbgMsg(DBG_USB_CTRL_MSG, 1, "Speed %d: \n", dev->speed);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "bRequest: %02X\n", ctrl->bRequest);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "bRequestType: %02X\n", ctrl->bmRequestType);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "wIndex: %04X\n", ctrl->wIndex);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "wValue: %04X\n", ctrl->wValue);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "wLength: %04X\n", ctrl->wLength);

  usb_handler->dprofile->ep0Req->buf = usb_handler->dprofile->ep0Buff;
  usb_handler->dprofile->ep0Req->dma =
      (uintptr_t)usb_handler->dprofile->ep0BufferPhyAddr;
  usb_handler->dprofile->ep0Req->complete = ep0reqComplete;
  switch (ctrl->bmRequestType & CH9_USB_REQ_TYPE_MASK) {
  case CH9_USB_REQ_TYPE_STANDARD:
    switch (ctrl->bRequest) {
    case CH9_USB_REQ_GET_DESCRIPTOR:
      break;
    case CH9_USB_REQ_SET_CONFIGURATION:
      break;
    case CH9_USB_REQ_GET_CONFIGURATION:
      break;
    case CH9_USB_REQ_SET_INTERFACE:
      break;
    case CH9_USB_REQ_GET_INTERFACE:
      break;
    case CH9_USB_REQ_GET_STATUS:
      break;
    default:
      printf("request does not support!\n");
      return -1;
      break;
    }
    break;
  case CH9_USB_REQ_TYPE_CLASS:
    return -1;
    break;
  }

  return 0;
}

// user callback
static CUSBD_Callbacks USBD_Callbacks = {
    .connect          = connect,
    .disconnect       = disconnect,
    .setup            = setup,
    .resume           = NULL,
    .suspend          = NULL,
    .busInterval      = NULL,
    .descMissing      = NULL,
    .usb2PhySoftReset = NULL,
};

static int fillin_init_param(USB_InitTypeDef *init) {
  init->USBx    = USB1;
  init->mode    = USB_MODE_DEV;
  init->version = USB_VER_2_0;
  init->callbacks = &USBD_Callbacks;
  return 0;
}

static int usb_dev_loopback_test(USB_Handler *handler) {
  int ret;
  if (handler->USB_InitStruct.version != USB_VER_3_0) {
    printf("only usb3.0 have loopback case.\n");
    return -1;
  }
  memset(write_buf, 0xAA, sizeof(write_buf));
  
  ret = itcs_usb_read(handler, USB_HOST_EP_IN, sizeof(read_buf), read_buf,
                      NONBLOCK);
  if (ret < 0) {
    printf("usb read error, ret = %d", ret);
    return -1;
  }

  ret = itcs_usb_write(handler, USB_HOST_EP_OUT, sizeof(write_buf), write_buf,
                       NONBLOCK);
  if (ret < 0) {
    printf("usb write error, ret = %d", ret);
    return -1;
  }

  // Waiting for tx complete.
  while (itcs_get_usb_transfer_status(handler, USB_TX) == TRANSFERING)
    ;
  // Waiting for rx complete.
  while (itcs_get_usb_transfer_status(handler, USB_RX) == TRANSFERING)
    ;

  if (memcmp(read_buf, write_buf, sizeof(read_buf))) {
    printf("host write & read test error, data is not same!\n");
  }

  printf("Test DRD usb3.0 Loopback Mode Pass.\n");
  return 0;
}

int main(){
	USB_InitTypeDef init;
  	USB_Handler *handle;
	fillin_init_param(&init);
	handle      = itcs_usb_init(&init);
	usb_handler = handle;
	usb_dev_loopback_test(handle);
	return 0;
}

```
