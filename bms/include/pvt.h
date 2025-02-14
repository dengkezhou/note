#ifndef __PVT_H__
#define __PVT_H__

#include <common.h>
#include <malloc.h>
#include <irq.h>

#define pvt_base 0xc2900000 // pvt base address in CPU

#define PVT_DEV_NUM 2

// define simpal function
#define GET_BIT(x, bit)   ((x & (1 << bit)) >> bit) /*  check bit if 1 or 0*/
#define DATA_OUT_VALUE(x) (((x) >> 16) & 0x3ff) /* 读取data_out的值bit[16:25]*/

// input information
#define VSAMPLE  (1UL << 8)
#define VSAMPLE0 (0 << 8)
#define PSAMPLE0 (1UL << 9)
#define PSAMPLE1 (1UL << 10)
#define TRIMG    (1UL << 16)
#define TRIMO    (1UL << 24)

#define DATA_VALID 0 //默认无效
#define ENA        (1UL << 0)

#define DEFAULT_TRIMG 5

// regs:CTL_TSVS is control reg and STA_TSVS is status reg;
#define CTL_TSVS0 0x00
#define STA_TSVS0 0x04
#define CTL_TSVS1 0x08
#define STA_TSVS1 0x12
#define CTL_TSVS2 0x16
#define STA_TSVS2 0x20
#define CTL_TSVS3 0x24
#define STA_TSVS3 0x28
#define CTL_TSVS4 0x32
#define STA_TSVS4 0x36
#define CTL_TSVS5 0x40
#define STA_TSVS5 0x44
#define CTL_TSVS6 0x52
#define STA_TSVS6 0x56
#define CTL_TSVS7 0x60

// 定义PVT模式的输入参数
typedef struct pvt_init_t {
  int mode;
  void (*callback)(void *dev, void *arg); //中断回调函数
  void *callback_param;
} pvt_init_t;

// pvt结构定义
typedef struct {
  //pvt_init_t *pvt;
  uint32_t mode;
  uint32_t base;
  uint32_t data_out;
  uint32_t channel_id;
  int irq;
  volatile uint32_t read_flag;
  void (*callback)(void *dev, void *arg);
  void *callback_param;
} pvt_device_t;

// pvt接口定义

pvt_device_t *itcs_pvt_init( uint32_t channel);
void itcs_pvt_mode_config(pvt_device_t *dev, uint32_t mode, uint32_t prmode);
void itcs_pvt_start(pvt_device_t *dev);
int itcs_pvt_get_status(pvt_device_t *dev);
uint32_t itcs_pvt_read(pvt_device_t *dev);
void itcs_pvt_stop(pvt_device_t *dev);
void itcs_pvt_deinit(pvt_device_t *dev);

#endif /* _PVT_H */
