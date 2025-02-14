/* Copyright(C)infoTM For Working
 * All right reserved
 *
 */
/**
 * @file para.h
 * @brief
 * @author Bright.Jiang bright.jiang@infotmic.com.cn  godvmxi@126.com
 * @version 0.1
 * @date 2014-07-11
 */

#ifndef __BMS_PARA_H__
#define __BMS_PARA_H__

#include <common.h>
#include <stdio.h>
#include <malloc.h>
#include <semihost.h>

#define MAX_CFG_SIZE           2048
#define MIN_LINE_SIZE          14
#define MAX_LINE_SIZE          256 //??
#define MAX_VALUE_NUM_PER_LINE 10  // per line can contain the number of value
#define MAX_PARA_VALUE_NUM     16
#define MAX_CHAR_PARA_LEN      128
typedef enum {
  char_p = '0', // str point
  i8_p   = '1', // int8_t    dat
  i16_p  = '2', // int16_t   dat
  i32_p  = '3', // int32_t   dat
  i64_p  = '4', // int32_t   dat
  u8_p   = '5', // uint8_t   dat
  u16_p  = '6', // uint16_t  dat
  u32_p  = '7', // uint32_t  dat
  u64_p  = '8'  // uint32_t  dat
} para_type_t;
typedef struct {
  int8_t name[MAX_CHAR_PARA_LEN];
  para_type_t type;
  int32_t number;
  void *point;
} para_struct_t;

/**
 * @brief load_para_from_cfg_file   load cfg data from cfg file
 *
 * @param filename   cfg file name
 * @param list
 * @param para_num
 *
 * @return
 */
int32_t load_para_from_cfg_file(int8_t *filename, para_struct_t *list,
                                int32_t para_num);

#endif
