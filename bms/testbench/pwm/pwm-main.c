/* pwm-main.c */
#include <command.h>
#include <common.h>
#include <malloc.h>
#include <testbench.h>
#include <asm/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pads.h>
#include <irq.h>
#include <pwm.h>
static pwm_device_t *pdevice;
static pwm_init_t init;
#ifdef CONFIG_COMPILE_RTL
#define T1MS (100)
#else
#define T1MS (1000 * 1)
#endif

void pwm_int_enable(pwm_device_t *dev);
void pwm_int_disable(pwm_device_t *dev);
uint32_t pwm_int_get_status(pwm_device_t *dev);

static uint32_t gu32_int_count;
static uint32_t gu32_int_flag = true;

void pwm_irq_callback(void *dev, void *args) {
  pwm_device_t *pwm_dev = (pwm_device_t *)dev;

  gu32_int_count++;

  printf("count %d\r\n", gu32_int_count);

  if (gu32_int_count > 10) {
    pwm_int_disable(pwm_dev);
    itcs_pwm_stop(pwm_dev);
    printf("pwm int status %08X\r\n", pwm_int_get_status(dev));

    gu32_int_count = 0;
    gu32_int_flag  = false;
  }
}
struct PWM_PRAM_t {
  uint32_t lu32_sysmode;
  uint32_t lu32_start;
  uint32_t lu32_period;
  uint32_t lu32_duty;
  uint32_t lu32_end;
  uint32_t mux_id;
};

static void pwm_output_control(uint32_t sysmode, uint32_t start, uint32_t end,
                               uint32_t period, uint32_t duty) {
  printf("pwm test case 1 start\r\n");
  if (end < start) {
    printf("Input channel range error!\n");
    return;
  }
  else{
    for (; start <= end; start++) {
      init.period             = period;
      init.duty               = duty;
      init.channel_int_enable = PWM_CHANNEL_INT_DISABLE;

      pdevice = itcs_pwm_config(sysmode, start, &init);
      itcs_pwm_start(pdevice);
      udelay(T1MS);
      //itcs_pwm_stop(pdevice);
    }
  }
  
  printf("pwm test case 1 Pass\r\n");
}

static void pwm_period_test(uint32_t sysmode, uint32_t start, uint32_t end,
                            uint32_t period, uint32_t duty) {
  printf("pwm test case 2 start\r\n");
  if (end < start) {
    printf("Input channel range error!\n");
    return;
  }
  else{
    for (; start <= end; start++) {
      init.period             = period;
      init.duty               = duty;
      init.channel_int_enable = PWM_CHANNEL_INT_DISABLE;

      pdevice = itcs_pwm_config(sysmode, start, &init);
      itcs_pwm_start(pdevice);
      udelay(T1MS);

      itcs_pwm_period_update(pdevice, init.period);
      udelay(T1MS);
      itcs_pwm_period_update(pdevice, init.period / 2);
      udelay(T1MS);
      itcs_pwm_period_update(pdevice, init.period / 3);
      udelay(T1MS);
      itcs_pwm_stop(pdevice);
    }
  }
  
  printf("pwm test case 2 Pass\r\n");
}
static void pwm_duty_test(uint32_t sysmode, uint32_t start, uint32_t end,
                          uint32_t period, uint32_t duty) {
  printf("pwm test case 3 start\r\n");
  if (end < start) {
    printf("Input channel range error!\n");
    return;
  }
  else{
    for (; start <= end; start++) {
      init.period             = period;
      init.duty               = duty;
      init.channel_int_enable = PWM_CHANNEL_INT_DISABLE;

      pdevice = itcs_pwm_config(sysmode, start, &init);
      itcs_pwm_start(pdevice);
      udelay(T1MS);

      itcs_pwm_duty_update(pdevice, duty);
      udelay(T1MS);
      itcs_pwm_duty_update(pdevice, 2 * duty);
      udelay(T1MS);
      itcs_pwm_duty_update(pdevice, 3 * duty);
      udelay(T1MS);
      itcs_pwm_stop(pdevice);
    }
  }
  
  printf("pwm test case 3 Pass\r\n");
}
static void pwm_IRQ_test(uint32_t sysmode, uint32_t start, int end) {
  printf("pwm test case 4 start\r\n");
#if 1
#ifdef CONFIG_COMPILE_RTL
  init.period = 24;
#else
  init.period = 50000;
#endif
#endif
  if (end < start) {
    printf("Input channel range error!\n");
    return;
  }
  else{
    for (; start <= end; start++) {
      init.duty               = 50;
      init.channel_int_enable = PWM_CHANNEL_INT_ENABLE;
      init.callback           = pwm_irq_callback;
      init.callback_param     = pdevice;
      pdevice                 = itcs_pwm_config(sysmode, start, &init);
      itcs_pwm_start(pdevice);
      while (gu32_int_flag) {
        udelay(10);
      }
      gu32_int_flag = true;
    }
  }
  

  printf("pwm test case 4 Pass\r\n");
}
static void pwm_set_mux(uint32_t channel, uint32_t mux_id){
  int channel_id[8];
  int fm = 0;
  for ( int i = 0; i < 4; i++)
  {
    channel_id[i] = 0;
  }
  switch (mux_id) {
  case 1:
    channel_id[4] = PWM4_MUX_1_PADS;
    channel_id[5] = PWM5_MUX_1_PADS;
    channel_id[6] = PWM6_MUX_1_PADS;
    channel_id[7] = PWM7_MUX_1_PADS;
    fm = PWM_MUX_1_FUNC;
    break;
  case 2:
    channel_id[4] = PWM4_MUX_2_PADS;
    channel_id[5] = PWM5_MUX_2_PADS;
    channel_id[6] = PWM6_MUX_2_PADS;
    channel_id[7] = PWM7_MUX_2_PADS;
    fm = PWM_MUX_2_FUNC;
    break;
  case 3:
    channel_id[4] = PWM4_MUX_3_PADS;
    channel_id[5] = PWM5_MUX_3_PADS;
    channel_id[6] = PWM6_MUX_3_PADS;
    channel_id[7] = PWM7_MUX_3_PADS;
    fm = PWM_MUX_3_FUNC;
    break;
  case 0:
    channel_id[4] = PWM4_MUX_0_PADS;
    channel_id[5]= PWM5_MUX_0_PADS;
    channel_id[6] = PWM6_MUX_0_PADS;
    channel_id[7] = PWM7_MUX_0_PADS;
    fm = PWM_MUX_0_FUNC;
    break;
  default:
    break;
  }
  
  itcs_pads_set_mode(CPU, channel_id[channel], PADS_MODE_OUT, 1);
  itcs_pads_set_mode(CPU, channel_id[channel], PADS_MODE_FUNC, fm);
  itcs_pads_set_pull(CPU, channel_id[channel], 1, PADS_PULL_UP);
}
static void pwm_mux_test(uint32_t sysmode, uint32_t start, uint32_t end, uint32_t period, uint32_t duty, uint32_t mux_id){
  printf("pwm test case 5 start\r\n");
  for (; start <= end; start++) {
      init.period             = period;
      init.duty               = duty;
      init.channel_int_enable = PWM_CHANNEL_INT_DISABLE;
      pdevice = itcs_pwm_config(sysmode, start, &init);
      pwm_set_mux(start, mux_id);
      itcs_pwm_start(pdevice);
      udelay(T1MS);
  }
  printf("pwm test case 5 Pass\r\n");
}

static void pwm_show_usage(void) {
  printf("Usage: pwm [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-m, --mode\t\tpwm system mode\n");
  printf("-c, --channel\t\tpwm channel select\n");
  printf("-i, --indexcase\t\tpwm test case index\n");
  printf("-p, --period\t\tpwm period\n");
  printf("-x, --mux\t\tpwm mux mode\n");
  printf("-d, --duty\t\tpwm duty\n");
}

static const char short_options[]         = " m:c:i:p:d:x:";
static const struct option long_options[] = {
    {"help", 0, 0, 'h'},
};

static int atoi(char *s) {
  int i, n = 0;

  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

int pwm_main(int argc, char *argv[]) {

  int lu32_index_case = 0;
  int option_index = 0, c, ret = 0;
  struct PWM_PRAM_t *pwm_pram_t = (struct PWM_PRAM_t *)malloc(sizeof(struct PWM_PRAM_t));;
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {

    case 'm': {
      pwm_pram_t->lu32_sysmode = atoi(optarg);
      ret                      = 1;
    } break;
    case 'c': {
      pwm_pram_t->lu32_start = atoi(optarg);
      pwm_pram_t->lu32_end   = atoi(argv[optind]);
      ret                    = 1;
    } break;

    case 'i': {
      lu32_index_case = atoi(optarg);
      ret             = 1;
    } break;

    case 'p': {
      pwm_pram_t->lu32_period = atoi(optarg);
      ret                     = 1;
    } break;

    case 'd': {
      pwm_pram_t->lu32_duty = atoi(optarg);
      ret                   = 1;
    } break;
    case 'x':{
      pwm_pram_t->mux_id = atoi(optarg);
      ret                = 1;
    } break;
    case 'h':
    default: {
      pwm_show_usage();
      ret = -1;
      goto err;
    } break;
    }
  }

  if (lu32_index_case != 0) {
    switch (lu32_index_case) {
      /* 输出开启关闭测试 */
    case 1:
      pwm_output_control(pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start,
                         pwm_pram_t->lu32_end, pwm_pram_t->lu32_period,
                         pwm_pram_t->lu32_duty);
      break;

    /* 频率周期测试 */
    case 2:
      pwm_period_test(pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start,
                      pwm_pram_t->lu32_end, pwm_pram_t->lu32_period,
                      pwm_pram_t->lu32_duty);
      break;

    /* 占空比测试 */
    case 3:
      pwm_duty_test(pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start,
                    pwm_pram_t->lu32_end, pwm_pram_t->lu32_period,
                    pwm_pram_t->lu32_duty);
      break;

    /* 中断测试 */
    case 4:
      pwm_IRQ_test(pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start,
                   pwm_pram_t->lu32_end);
      break;
    case 5:
      pwm_mux_test(pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start, 
                   pwm_pram_t->lu32_end,pwm_pram_t->lu32_period,
                    pwm_pram_t->lu32_duty,pwm_pram_t->mux_id);
      break;
    default:
      break;
    }
  } else {
    printf("pwm channel test. sysmode:%d, channel:%d, lu32_period:%d, "
           "lu32_duty:%d \r\n",
           pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start,
           pwm_pram_t->lu32_period, pwm_pram_t->lu32_duty);

    init.period             = pwm_pram_t->lu32_period;
    init.duty               = pwm_pram_t->lu32_duty;
    init.channel_int_enable = PWM_CHANNEL_INT_DISABLE;

    pdevice = itcs_pwm_config(pwm_pram_t->lu32_sysmode, pwm_pram_t->lu32_start,
                              &init);
    itcs_pwm_start(pdevice);
  }

  if (optind == 1) {
    pwm_show_usage();
    ret = -1;
    goto err;
  }

err:
  optind = 1;
  return ret;
}

void pwm_init(void) { register_testbench("pwm", pwm_main, NULL); }

testbench_init(pwm_init);