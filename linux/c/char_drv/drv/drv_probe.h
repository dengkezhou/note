#ifndef DRV_PROBE_H
#define DRV_PROBE_H

#include <linux/cdev.h>                 /*cdev*/
#include <linux/device.h>       /*class device*/

#define DEVICE_NAME "char_dev"         /*device_create 会在/dev/目录下创建该设备文件*/
#define CLASS_NAME  "char_class_1"       /*class_create 会在/sys/class 目录下创建该类文件*/
#define P_MEM_SIZE   4096


#endif