#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <pvt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pvt_callback(void *dev, void *data);

int PVT_IRQn[PVT_DEV_NUM]  = {C_PVT0_IRQn, C_PVT1_IRQn};
char *pvt_irq[PVT_DEV_NUM] = {"pvt0", "pvt1"};

static int pvt_irq_handle(int irq, void *args) {
  pvt_device_t *dev = (pvt_device_t *)args;
  uint32_t tempreg  = 0;

  tempreg = readl(dev->base + 0x4);
  uint32_t data_valid  = GET_BIT(tempreg, 0);
  if(data_valid == 1)  dev->read_flag = 1;


  tempreg = readl(dev->base);
  //writel(tempreg & (~ENA), dev->base);
  tempreg = readl(pvt_base + 0x64);
  tempreg&=~(1<<(dev->channel_id));
  writel(tempreg, pvt_base + 0x64);
  
  if (dev->callback)
    dev->callback(dev, dev->callback_param);

  return 0;
}

pvt_device_t *itcs_pvt_init( uint32_t channel) {
  
  int ret;
  itcs_module_enable(CPU, "pvt");

  pvt_device_t *pdev = (pvt_device_t *)malloc(sizeof(pvt_device_t));
  if (!pdev)
    return NULL;

  pdev->base       = pvt_base + 0x8 * channel;
  pdev->channel_id = channel;
  pdev->mode       = 0;
  pdev->callback   = pvt_callback;
  pdev->irq = PVT_IRQn[channel];

  ret = request_irq(pdev->irq, pvt_irq_handle, pvt_irq[channel], pdev);
  if (ret < 0) {
    free(pdev);
    return NULL;
  }

  return pdev;
}


extern int trimg;
extern int trimo;

void itcs_pvt_mode_config(pvt_device_t *dev, uint32_t mode, uint32_t prmode){
  uint32_t tempreg   = 0;

  pvt_device_t *pdev = dev;
  pdev->data_out     = 0;
  pdev->read_flag    = 0;

  //中断使能寄存器
  tempreg = readl(pvt_base + 0x64);
  tempreg |= 1 << pdev->channel_id;
  writel(tempreg, pvt_base + 0x64); 

  pdev->mode = mode;
  tempreg    = readl(pdev->base);
  switch (mode)
  {
  case 0:
    tempreg = (trimg << 16 | VSAMPLE0 | trimo << 24);
    break;
  case 1:
    tempreg = (trimg << 16 | VSAMPLE | trimo << 24);
    break;
  case 2:{
    switch (prmode)
    {
    case 0:
      tempreg = (trimg << 16 | PSAMPLE0 | trimo << 24);
      break;
    case 1:
      tempreg = (trimg << 16 | PSAMPLE1 | trimo << 24);
      break;
    case 2:
      tempreg = (trimg << 16 | PSAMPLE1 |PSAMPLE0 | trimo << 24);
      break;
    default:
      break;
    }
  }
    break;
  default:
    break;
  }
  writel(tempreg, pdev->base);
}

uint32_t itcs_pvt_read(pvt_device_t *dev) {
  //本函数实现用户读取pvt的data_out[9:0]值的功能
  uint32_t tempreg = 0, temp = 0;
  pvt_device_t *pdev = dev;
  // tempreg            = readl(pdev->base + 0x4);
  // writel( reg&(~(1<<(dev->channel_id))), pvt_base + 0x64);
  temp    = readl(pdev->base);
  tempreg = readl(pdev->base + 0x4);
  writel(temp & (~ENA), pdev->base);
  return DATA_OUT_VALUE(tempreg);
}

void itcs_pvt_start(pvt_device_t *dev) { // channel
  uint32_t tempreg = readl(dev->base);
  uint32_t reg = readl(pvt_base + 0x64);
  writel( tempreg| ENA, dev->base);
  writel( reg|(1<<(dev->channel_id)), pvt_base + 0x64);
}

int itcs_pvt_get_status(pvt_device_t *dev){
  return dev->read_flag;
}


void itcs_pvt_deinit(pvt_device_t *dev) {
  if (dev)
    free(dev);
}

void itcs_pvt_stop(pvt_device_t *dev) { 
  uint32_t tempreg = readl(dev->base);
  writel(tempreg&(~ENA) , dev->base); 
}
