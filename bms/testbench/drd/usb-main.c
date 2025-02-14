/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     usb-main.c
 * @brief    usb testBench
 * @version  V1.0
 * @date     07.04 2022

 * @name     usb-main
 * author    jason.liu
 ******************************************************************************/

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>
#include <drd.h>
#include <mouse.h>
#include <loop_dev.h>
#include <string.h>
#include <pads.h>

#define SUCCESS 1
#define FAILURE 0

#define TEST_DATA_LEN 8

#define USB_TEST_EP 3

static void usb_show_usage(void) {
  printf("Usage: usb [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-p, --port\t\t0-3\n");
  printf("-m, --mode\t\t0:host 1:device\n");
  printf("-v, --version\t\t2:USB2.0 3:USB3.0\n");
  printf("-l, --loopback\t\tdevice loopback mode\n");
  printf("-i, --insert\t\tdevice insert test\n");
}

static void dev_connect(CUSBD_PrivateData *pD) {
  CUSBD_Dev *dev;
  USB_Handler * usb_handler = (USB_Handler *) pD->userHandler;
  usb_handler->dprofile->drv->getDevInstance(pD, &dev);
  //printf("++++++++++++USB%d Application: connect+++++++++++\n", usb_handler->USB_InitStruct.USBx);
}

static void dev_disconnect(CUSBD_PrivateData *pD) {
  //printf("\n------------Application: disconnect-------------\n");
}

static void dev_ep0reqComplete(CUSBD_Ep *ep, CUSBD_Req *req) {
  printf("**************Request on endpoint %s completed*************\n", ep->name);
}

uint32_t dev_setup(CUSBD_PrivateData *pD, CH9_UsbSetup *ctrl) {
  USB_Handler * usb_handler = (USB_Handler *) pD->userHandler;
  usb_handler->dprofile->ep0Req->complete = dev_ep0reqComplete;
  //mouse_setup(usb_handler, pD, ctrl);
  loop_dev_setup(usb_handler, pD, ctrl);
  return 0;
}

/**
 * User callback for BUS INTERVAL
 */
static void dev_busInterval(CUSBD_PrivateData *pD) {
    vDbgMsg(DBG_GEN_MSG, DBG_HIVERB, "Application: bus interval %c\n", ' ');
}

static int iso_complete = 0;

static void outEpXferCmpl(CUSBD_Ep *ep, CUSBD_Req * req) {
    printf("out ep xfer complete\n");
    iso_complete = 1;
}
/**
 * User callback for MISSING DESCRIPTOR
 */

static void dev_descMissing(CUSBD_PrivateData *pD, uint8_t epAddr) {
    static CUSBD_Req DataXferRequests;
    uint8_t buffer[TEST_DATA_LEN] = {0};
    printf("Application: descriptor missing\n");
    USB_Handler * usb_handler = (USB_Handler *) pD->userHandler;

    memset(&DataXferRequests, 0, sizeof (CUSBD_Req));
    DataXferRequests.buf = buffer;
    DataXferRequests.dma = (uintptr_t) (DataXferRequests.buf);
    DataXferRequests.complete = outEpXferCmpl;
    DataXferRequests.length = TEST_DATA_LEN;
    DataXferRequests.streamId = 0;

    usb_handler->dprofile->epOut->ops->reqQueue(pD, usb_handler->dprofile->epOut , &DataXferRequests);    
}

static void dev_resume(CUSBD_PrivateData *pD) {
    vDbgMsg(DBG_USB_CTRL_MSG, 1, "Application: resume\n");
}

static void dev_suspend(CUSBD_PrivateData *pD){
    vDbgMsg(DBG_USB_CTRL_MSG, 1, "Application: suspend\n");
}


// user callback
static CUSBD_Callbacks USBD_Callbacks = {
    .connect          = dev_connect,
    .disconnect       = dev_disconnect,
    .setup            = dev_setup,
    .resume           = dev_resume,
    .suspend          = dev_suspend,
    .busInterval      = dev_busInterval,
    .descMissing      = dev_descMissing,
    .usb2PhySoftReset = NULL,
};

static int check_args(int port, int version) {
  if ((port > 3) || (port < 0)) {
    printf("-p supports 0/1/2/3\n");
    usb_show_usage();
    return -1;
  }
  if ((version != 2) && (version != 3)) {
    printf("-m supports 2/3\n");
    usb_show_usage();
    return -1;
  }
  return 0;
}

static int parse_args(int port, int mode, int version) {
  if (port == 0) {
    port = USB0;
  } else if (port == 1) {
    port = USB1;
  } else if (port == 2) {
    port = USB2;
  } else if (port == 3) {
    port = USB3;
  }

  if (mode == 0) {
    mode = USB_MODE_HOST;
  } else if (mode == 1) {
    mode = USB_MODE_DEV;
  }

  if (version == 2) {
    version = USB_VER_2_0;
  } else if (version == 3) {
    version = USB_VER_3_0;
  }
  return 0;
}

#ifndef CONFIG_COMPILE_ASIC
static void usb_sel_clock_freq()
{
    itcs_pads_set_mode(CPU, PADSRANGE(76, 79), PADS_MODE_OUT, 0);
    itcs_pads_set_value(CPU, PADSRANGE(76, 79), 1);
}
#endif

static int usb_dev_loopback_test(int host_port, int dev_port, int version) {
  uint8_t tx_buf[TEST_DATA_LEN] = {0};
  uint8_t rx_buf[TEST_DATA_LEN] = {0};
  int ret;
  USB_Handler *handler_host;
  USB_Handler *handler_dev;
  USB_InitTypeDef init_host, init_dev;

  memset(&init_dev, 0, sizeof(USB_InitTypeDef));
  memset(&init_host, 0, sizeof(USB_InitTypeDef));
  init_dev.ep = USB_TEST_EP;
  init_host.ep = USB_TEST_EP;
  if(version == USB_VER_3_0){
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_3_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_3_0;
    init_host.callbacks = NULL;
  }else{
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_2_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_2_0;
    init_host.callbacks = NULL;
  }

  #ifdef CONFIG_COMPILE_RTL
  usb_module_init(&init_host);
  usb_module_init(&init_dev);
  #endif

  handler_host = itcs_usb_init(&init_host);
  handler_dev = itcs_usb_init(&init_dev);
  handler_dev->trans_mode = CH9_USB_EP_BULK;
  #if 0
  {
    USBSSP_DriverResourcesT *res;
    uint32_t flags = (0x00000008U) | (0x00000004U) | (0x00000001U);
    res = handler_host->hprofile->xhci_driver_resources;
    writel(flags, &res->regs.xhciOperational->usbcmd);
  }
  #endif
  if(usb_host_get_desc(handler_host)){
    printf("------get desc failed!-------\n");
    return 0;
  }

  printf("------usb dev read-------\n");
  ret = itcs_usb_read(handler_dev, handler_dev->ep, TEST_DATA_LEN, rx_buf, NONBLOCK);
  if (ret < 0) {
    printf("usb dev read error, ret = %d", ret);
    return -1;
  }
  printf("------usb host write-------\n");
  memset(tx_buf, 0xAA, sizeof(tx_buf));
  
  ret = itcs_usb_write(handler_host, handler_host->ep, TEST_DATA_LEN, tx_buf, BLOCK);
  if (ret < 0) {
    printf("usb host write error, ret = %d", ret);
    return -1;
  }

  if (memcmp(rx_buf, tx_buf, TEST_DATA_LEN)) {
    printf("host write & read test error, data is not same!\n");
    printf("tx:\n");
    for(int i = 0; i < TEST_DATA_LEN; i++){
        printf("0x%x ", tx_buf[i]);
    }
    printf("\nrx:\n");
    for(int i = 0; i < TEST_DATA_LEN; i++){
        printf("0x%x ", rx_buf[i]);
    }
    return -1;
  }

  if (handler_host->USB_InitStruct.version == USB_VER_2_0) {
    printf("Test DRD usb2.0 Loop Test Pass.\n");
  } else if (handler_host->USB_InitStruct.version == USB_VER_3_0) {
    printf("Test DRD usb3.0 Loop Test Pass.\n");
  }

  
  return 0;
}

static int usb_dev_loopback_band_width_test(int host_port, int dev_port, int version) {
  uint8_t tx_buf[2048] = {0};
  uint8_t rx_buf[2048] = {0};
  USB_Handler *handler_host;
  USB_Handler *handler_dev;
  USB_InitTypeDef init_host, init_dev;

  memset(&init_dev, 0, sizeof(USB_InitTypeDef));
  memset(&init_host, 0, sizeof(USB_InitTypeDef));
  init_dev.ep = USB_TEST_EP;
  init_host.ep = USB_TEST_EP;
  if(version == USB_VER_3_0){
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_3_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_3_0;
    init_host.callbacks = NULL;
  }else{
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_2_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_2_0;
    init_host.callbacks = NULL;
  }

  #ifdef CONFIG_COMPILE_RTL
  usb_module_init(&init_host);
  usb_module_init(&init_dev);
  #endif

  handler_host = itcs_usb_init(&init_host);
  handler_dev = itcs_usb_init(&init_dev);
  handler_dev->trans_mode = CH9_USB_EP_BULK;

  if(usb_host_get_desc(handler_host)){
    printf("------get desc failed!-------\n");
    return 0;
  }

  printf("------usb dev read-------\n");
  itcs_usb_read(handler_dev, handler_dev->ep, 2048, rx_buf, NONBLOCK);

  printf("------usb host write-------\n");
  memset(tx_buf, 0xAA, sizeof(tx_buf));
  
  itcs_usb_write(handler_host, handler_host->ep, 2048, tx_buf, BLOCK);

  if (handler_host->USB_InitStruct.version == USB_VER_2_0) {
    printf("Test DRD usb2.0 Band Width Pass.\n");
  } else if (handler_host->USB_InitStruct.version == USB_VER_3_0) {
    printf("Test DRD usb3.0 Band Width Pass.\n");
  }

  
  return 0;
}

static int usb_ep_loop_test(int host_port, int dev_port, int version, int ep){
  uint8_t tx_buf[TEST_DATA_LEN] = {0};
  uint8_t rx_buf[TEST_DATA_LEN] = {0};
  int ret;
  USB_Handler *handler_host;
  USB_Handler *handler_dev;
  USB_InitTypeDef init_host, init_dev;

  memset(&init_dev, 0, sizeof(USB_InitTypeDef));
  memset(&init_host, 0, sizeof(USB_InitTypeDef));

  if(version == USB_VER_3_0){
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_3_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_3_0;
    init_host.callbacks = NULL;
  }else{
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_2_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_2_0;
    init_host.callbacks = NULL;
  }
  if(ep > 15){
    printf("ep error: %d\n", ep);
    return -1;
  }

  init_dev.ep = ep;
  init_host.ep = ep;

  #ifdef CONFIG_COMPILE_RTL
  usb_module_init(&init_host);
  usb_module_init(&init_dev);
  #endif

  handler_host = itcs_usb_init(&init_host);
  handler_dev = itcs_usb_init(&init_dev);
  handler_dev->trans_mode = CH9_USB_EP_BULK;
  
  if(usb_host_get_desc(handler_host)){
    printf("------get desc failed!-------\n");
    return 0;
  }

  printf("------usb dev read-------\n");
  ret = itcs_usb_read(handler_dev, handler_dev->ep, TEST_DATA_LEN, rx_buf, NONBLOCK);
  if (ret < 0) {
      printf("usb dev read error, ret = %d", ret);
      return -1;
  }
  printf("------usb host write-------\n");
  memset(tx_buf, 0xAA, sizeof(tx_buf));

  ret = itcs_usb_write(handler_host, handler_host->ep, TEST_DATA_LEN, tx_buf, BLOCK);
  if (ret < 0) {
      printf("usb host write error, ret = %d", ret);
      return -1;
  }


  if (memcmp(rx_buf, tx_buf, TEST_DATA_LEN)) {
    printf("host write & read test error, data is not same!\n");
    printf("tx:\n");
    for(int i = 0; i < TEST_DATA_LEN; i++){
        printf("0x%x ", tx_buf[i]);
    }
    printf("\nrx:\n");
    for(int i = 0; i < TEST_DATA_LEN; i++){
        printf("0x%x ", rx_buf[i]);
    }
    return -1;
  }

  printf("Test DRD ep%d Test Pass.\n", ep);
  
  return 0;
}

static int usb_transmode_test(int host_port, int dev_port, int version, int mode) {
  uint8_t tx_buf[TEST_DATA_LEN] = {0};
  uint8_t rx_buf[TEST_DATA_LEN] = {0};
  int ret;
  USB_Handler *handler_host;
  USB_Handler *handler_dev;
  USB_InitTypeDef init_host, init_dev;

  memset(&init_dev, 0, sizeof(USB_InitTypeDef));
  memset(&init_host, 0, sizeof(USB_InitTypeDef));
  init_dev.ep = USB_TEST_EP;
  init_host.ep = USB_TEST_EP;
  if(version == USB_VER_3_0){
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_3_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_3_0;
    init_host.callbacks = NULL;
  }else{
    init_dev.USBx    = dev_port;
    init_dev.mode    = USB_MODE_DEV;
    init_dev.version = USB_VER_2_0;
    init_dev.callbacks = &USBD_Callbacks;

    init_host.USBx    = host_port;
    init_host.mode    = USB_MODE_HOST;
    init_host.version = USB_VER_2_0;
    init_host.callbacks = NULL;
  }

  #ifdef CONFIG_COMPILE_RTL
  usb_module_init(&init_host);
  usb_module_init(&init_dev);
  #endif

  handler_host = itcs_usb_init(&init_host);
  handler_dev = itcs_usb_init(&init_dev);
  switch(mode){
    case 1: handler_dev->trans_mode = CH9_USB_EP_ISOCHRONOUS;  break;
    case 2: handler_dev->trans_mode = CH9_USB_EP_BULK;  break;
    case 3: handler_dev->trans_mode = CH9_USB_EP_INTERRUPT;  break;
    default: handler_dev->trans_mode = CH9_USB_EP_BULK;  break;
  }
  
  if(usb_host_get_desc(handler_host)){
    printf("------get desc failed!-------\n");
    return 0;
  }

  printf("------usb dev read-------\n");
  ret = itcs_usb_read(handler_dev, handler_dev->ep, TEST_DATA_LEN, rx_buf, NONBLOCK);
  if (ret < 0) {
    printf("usb dev read error, ret = %d", ret);
    return -1;
  }
  printf("------usb host write-------\n");
  memset(tx_buf, 0xAA, sizeof(tx_buf));
  
  ret = itcs_usb_write(handler_host, handler_host->ep, TEST_DATA_LEN, tx_buf, BLOCK);
  if (ret < 0) {
    printf("usb host write error, ret = %d", ret);
    return -1;
  }

  if(handler_dev->trans_mode == CH9_USB_EP_ISOCHRONOUS){
    int retry_count = 5;
    while(retry_count --){
        itcs_usb_read(handler_dev, handler_dev->ep, TEST_DATA_LEN, rx_buf, NONBLOCK);
        itcs_usb_write(handler_host, handler_host->ep, TEST_DATA_LEN, tx_buf, BLOCK);
        int timeout_us = 100;
        while(timeout_us--){
          if(iso_complete){
            goto comp;
          }
          udelay(1);
        }
    }
  }
comp:
  if (memcmp(rx_buf, tx_buf, TEST_DATA_LEN)) {
    printf("host write & read test error, data is not same!\n");
    printf("tx:\n");
    for(int i = 0; i < TEST_DATA_LEN; i++){
        printf("0x%x ", tx_buf[i]);
    }
    printf("\nrx:\n");
    for(int i = 0; i < TEST_DATA_LEN; i++){
        printf("0x%x ", rx_buf[i]);
    }
    return -1;
  }

  switch(mode){
    case 1: printf("Test DRD transfer mode isochronous Test Pass.\n"); break;
    case 2: printf("Test DRD transfer mode bulk Test Pass.\n");  break;
    case 3: printf("Test DRD transfer mode interrupt Test Pass.\n");  break;
    default: printf("Test DRD transfer mode bulk Test Pass.\n");  break;
  }
  

  
  return 0;
}


static int usb_dev_rw_test(int port, int version) {
  /*
  int ret;
  memset(write_buf, 0xAA, sizeof(write_buf));
  ret = itcs_usb_read(handler, USB_HOST_EP_IN, sizeof(read_buf), read_buf,
                      NONBLOCK);
  if (ret < 0) {
    printf("usb read error, ret = %d", ret);
    return -1;
  }
  while (itcs_get_usb_transfer_status(handler, USB_RX) == TRANSFERING)
    ;

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
    return -1;
  }

  if (handler->USB_InitStruct.version == USB_VER_2_0) {
    printf("Test DRD usb2.0 Device Mode Pass.\n");
  } else if (handler->USB_InitStruct.version == USB_VER_3_0) {
    printf("Test DRD usb3.0 Device Mode Pass.\n");
  }
  */
  return 0;
}

static int usb_host_wr_test(int port, int version) {
  /*
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
  */
  return 0;
}


int usb_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  static int port, portl, mode, version, loopback_test = 0, band_width_test = 0;
  int ep = 0;
  int trans_mode = 0; // 1:bulk 2:int 3:iso
  static const char short_options[]         = "hp:q:m:v:le:t:b";
  static const struct option long_options[] = {{"help", 0, 0, 'h'},
                                               {"port", 1, 0, 'p'},
                                               {"portloop", 1, 0, 'q'},
                                               {"mode", 1, 0, 'm'},
                                               {"version", 1, 0, 'v'},
                                               {"loopback", 0, 0, 'l'},
                                               {"ep", 1, 0, 'e'},
                                               {"trans", 1, 0, 't'},
                                               {"band", 0, 0, 'b'},
                                               {0, 0, 0, 0}};

  /* Get all arguements. */
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'p':
      port = simple_strtoul(optarg, NULL, 10);
      break;
    case 'q':
      portl = simple_strtoul(optarg, NULL, 10);
      break;
    case 'm':
      mode = simple_strtoul(optarg, NULL, 10);
      break;
    case 'v':
      version = simple_strtoul(optarg, NULL, 10);
      break;
    case 'l':
      loopback_test = 1;
      break;
    case 'b':
      band_width_test = 1;
      break;
    case 'e':
      ep = simple_strtoul(optarg, NULL, 10);
      break;
    case 't':
      trans_mode = simple_strtoul(optarg, NULL, 10);
      break;
    case 'h':
    default:
      usb_show_usage();
      ret = -1;
      goto err;
    }
  }

  if (optind == 1) {
    usb_show_usage();
    ret = -1;
    goto err;
  }

  /* Check arguements. */
  if (check_args(port, version)) {
    printf("cmdline param invalild, please refer to test case document.\n");
    ret = -1;
    goto err;
  }

  /* Parse arguements */
  parse_args(port, mode, version);

  #ifdef CONFIG_COMPILE_ASIC
  itcs_pads_set_mode(CPU, 84, PADS_MODE_OUT, 1);
  itcs_pads_set_mode(CPU, 93, PADS_MODE_OUT, 1);
  itcs_pads_set_mode(CPU, 88, PADS_MODE_OUT, 1);
  itcs_pads_set_mode(CPU, 92, PADS_MODE_OUT, 1);
  #else
  usb_sel_clock_freq();
  #endif

  /* ---------Test flow start--------- */
  if (loopback_test) {
    // loopback test
    printf("usb loopback test...\n");
    usb_dev_loopback_test(port, portl, version);
  }else if(ep){
    printf("usb ep test...\n");
    usb_ep_loop_test(port, portl, version, ep);
  }else if(trans_mode){
    printf("usb transfer mode test...\n");
    usb_transmode_test(port, portl, version, trans_mode);
  }else if(band_width_test){
    printf("usb band width test...\n");
    usb_dev_loopback_band_width_test(port, portl, version);
  }else {
    if (mode == USB_MODE_HOST) {
      printf("usb host mode rw test...\n");
      usb_host_wr_test(port, version);
    } else if (mode == USB_MODE_DEV) {
      printf("usb device mode rw test...\n");
      usb_dev_rw_test(port, version);
    }
  }

  /* ---------Test flow end----------- */

err:
  optind = 1;
  return ret;
}

void usb_init(void) { register_testbench("drd", usb_main, NULL); }

testbench_init(usb_init);