/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     pvt-main.c
 * @brief    process voltage temperature
 * @version  V1.0
 * @date     05.12 2023
 * @name     pvt-main
 * author    Sineidin.Shen
 ******************************************************************************/
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
#include <i2c.h>
#include <pmic.h>

static int complete = 0;
// static pvt_init_t init;
static void pvt_show_usage(void) {
  printf("Usage: pvt [OPTION]...\n\n");
  printf("-h, --help\t\t command help\n");
  printf("-p, --process_mode\t\t process mode\n");
  printf("-m, --mode\t\t pvt test mode\n");
  printf("-i, --index\t\t pvt case index\n");
}
static int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

void pvt_callback(void *dev, void *data) {
  complete = 1;
  // printf("pvt callback react\n");
}

double pvt_calculate_temp(uint32_t x) {
  double temp;
  const double a4 = -1.8439E-11;
  const double a3 = 8.0705e-08;
  const double a2 = -1.8501e-04;
  const double a1 = 3.2843e-01;
  const double a0 = -4.8690e+01;

  temp = a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
  return temp;
}

double pvt_calculate_vlt(uint32_t x) {
  double vlt;
  const double a1 = 7.1917e-04;
  const double a0 = 4.1485e-01;
  vlt             = a1 * x + a0;
  return vlt;
}

#ifdef CONFIG_DRV_PMIC
static int pvt_pmic_set_cpu_vlt(int vlt)
{
  int ret, tmp;
  static struct regulator_dev *pmic = NULL;

  vlt *= 1000;

  if (pmic == NULL)
  {
    pmic = itcs_regulator_get(0, "dcdc2");
    if (pmic == NULL)
    {
      printf("pvt get pmic failed\n");
      return -1;
    }
  }

  ret = itcs_regulator_enable(pmic);
  if (ret) {
    printf("pvt pmic enable failed, ret = %d\n", ret);
    return ret;
  }

  tmp = itcs_regulator_get_voltage(pmic);
  printf("pvt pmic get vlt = %d\n", tmp);

  itcs_regulator_set_voltage(pmic, vlt, vlt);

  tmp = itcs_regulator_get_voltage(pmic);
  printf("pvt pmic get vlt = %d\n", tmp);

  //itcs_regulator_put(pmic);

  return 0;
}
#else
static int pvt_pmic_set_cpu_vlt(int vlt) {return 0;}
#endif

void pvt_temperature_test(pvt_device_t *dev, uint32_t pvt_case,
                          uint32_t process_mode) {
  uint32_t data_valid = 0;
  uint32_t data_out   = 0;
  double temp;

  complete = 0;
  itcs_pvt_mode_config(dev, pvt_case, process_mode);
  itcs_pvt_start(dev);
  while (1) {
    data_valid = itcs_pvt_get_status(dev);
    if (data_valid)
      break;
    udelay(1);
  }
  if (data_valid == 1) {
    data_out = itcs_pvt_read(dev);
    temp     = pvt_calculate_temp(data_out);
    //printf("temp data_out = %d, temp * 100 = %d\n",data_out, (int)(temp * 100));
    printf("%d ", (int)(temp * 100));
  }

  itcs_pvt_stop(dev);
}

void pvt_voltage_test(pvt_device_t *dev, uint32_t pvt_case,
                      uint32_t process_mode) {
  uint32_t data_out   = 0;
  uint32_t data_valid = 0;
  double vlt;
  complete = 0;

  itcs_pvt_mode_config(dev, pvt_case, process_mode);
  itcs_pvt_start(dev);
  while (1) {
    data_valid = itcs_pvt_get_status(dev);
    if (data_valid)
      break;
    udelay(1);
  }
  if (data_valid == 1) {
    data_out = itcs_pvt_read(dev);
    vlt      = pvt_calculate_vlt(data_out);
    printf("vlt data_out = %d, vlt * 1000 = %d\n",data_out, (int)(vlt * 1000));
  }

  itcs_pvt_stop(dev);
}

void pvt_process_test(pvt_device_t *dev, uint32_t pvt_case,
                      uint32_t process_mode) {
  uint32_t data_out   = 0;
  uint32_t data_valid = 0;

  itcs_pvt_mode_config(dev, pvt_case, process_mode);
  itcs_pvt_start(dev);
  while (1) {
    data_valid = itcs_pvt_get_status(dev);
    if (data_valid)
      break;
    udelay(1);
  }
  if (data_valid == 1) {
    data_out = itcs_pvt_read(dev);
    printf("process data_out = 0x%x\n", data_out);
  }

  itcs_pvt_stop(dev);
}

void pvt_mc_temp_test()
{
  int i;
  static pvt_device_t *p_dev[PVT_DEV_NUM] = {NULL};

  for (i = 0; i < PVT_DEV_NUM; ++i)
  {
      if (p_dev[i] == NULL)
      {
        p_dev[i] = itcs_pvt_init(i);
        if (p_dev[i] == NULL)
        {
          printf("pvt init failed, i = %d\n", i);
          return;
        }
      }
      printf("channel %d: ", i);
      pvt_temperature_test(p_dev[i], 0, 0);
  }

  printf("\n");
}


int trimg = 0xf;
int trimo = 0; 

int pvt_main(int argc, char *argv[]) {
  uint32_t c, ret = 0;
  int option_index = 0;
  int pvt_case     = -1;
  int process_mode = 0;
  int vlt = 0;
  int i;

  int loop, delay;

  static int init = 0;
  static pvt_device_t *p_dev[PVT_DEV_NUM];

  static char *const short_options    = "m:c:p:v:g:o:l:d:";
  static struct option long_options[] = {
      {"help", 0, 0, 'h'},
      {"mode", 0, 0, 'm'},
      {"channel", 0, 0, 'c'},
      {"set vlt", 0, 0, 'v'},
      {0, 0, 0, 0},
  };

  /*  get all argument. */
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'p': {
      process_mode = atoi(optarg);
      break;
    }
    case 'm': {
      pvt_case = atoi(optarg);
      break;
    }

    case 'v':
      vlt = atoi(optarg);
    break;

    case 'g':
      trimg = atoi(optarg);
    break;

    case 'o':
      trimo = atoi(optarg);
    break;

    case 'l':
      loop = atoi(optarg);
    break;

    case 'd':
      delay = atoi(optarg); // 100ms
    break;

    case 'h':
    default:
      pvt_show_usage();
      ret = -1;
      goto err;
    }
  }

  if (optind == 1) {
    pvt_show_usage();
    ret = -1;
    goto err;
  }

  if (vlt)
  {
    pvt_pmic_set_cpu_vlt(vlt);
  }

  if (!init)
  {
    for (i = 0; i < PVT_DEV_NUM; ++i)
    {
        p_dev[i] = itcs_pvt_init(i);
        if (p_dev[i] == NULL)
        {
          printf("pvt init failed, i = %d\n", i);
          goto err;
        }
    }

    init = 1;
  }

  if (pvt_case <=-1)
  {
    pvt_show_usage();
    goto err;
  }

  printf("---delay = %d, trimg = %d, trimo = %d\n", delay, trimg, trimo);

  while(loop --)
  {
    printf("loop = %d: ", loop);
  for (i = 0; i < PVT_DEV_NUM; ++i)
  {
      switch (pvt_case) {
        /*温度模式测试*/
      case 0:
        pvt_temperature_test(p_dev[i], pvt_case, process_mode);
        //printf("PVT Temperature channel %d Test Pass\n", i);
        break;
        /*电压模式测试*/
      case 1:
        pvt_voltage_test(p_dev[i], pvt_case, process_mode);
        printf("PVT Voltage channel %d Test Pass\n", i);
        break;
        /*工艺模式测试*/
      case 2:
        pvt_process_test(p_dev[i], pvt_case, process_mode);
        printf("PVT Process channeld %d Test Pass\n", i);
        break;
      default:
        printf("PVT Test may be KeyIn Error!\n");
        break;
      }
  }

    printf("\n");
    udelay(delay * 1000 * 100);
  }

err:
  optind = 1;
  return ret;
}

void pvt_init(void) { register_testbench("pvt", pvt_main, NULL); }

testbench_init(pvt_init);
