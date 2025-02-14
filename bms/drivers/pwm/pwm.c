/*
 ******************************************************************************
 * @file    pwm.c
 * @author  Intchains Firmware Team
 * @version V1.0.0
 * @date    2021
 * @brief   SPI module driver.
 *          This file provides firmware functions to manage the
 *          Pulse-Width Modulatio (PWM) peripheral
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 Intchains.
 * All rights reserved.
 ******************************************************************************
 */
#include <common.h>
#include <pads.h>
#include "pwm.h"

void pwm_int_enable(pwm_device_t *dev);
void pwm_int_disable(pwm_device_t *dev);
uint32_t pwm_int_get_status(pwm_device_t *dev);

/*************************************************************************
 * @brief : pwm interrupt handler.
 */
int pwm_irq_handler(int irq, void *args) {
  pwm_device_t *dev = (pwm_device_t *)args;

  /* get pwm status and clear */
  pwm_int_get_status(dev);

  if (dev->callback)
    dev->callback(dev, dev->callback_param);

  return 0;
}

/*************************************************************************
 * @brief : pwm channel param config
 * @param : channel: pwm channel select.
 *          init: initialization parameter.
 * @retval: pwm_device_t: device handle.
 */
pwm_device_t *itcs_pwm_config(domain_t sysmode, uint32_t channel,
                              pwm_init_t *init) {
  uint32_t lu32_HighClock;

  struct_PWM_t *CPWM_Device[] = {PWM0, PWM1, PWM2, PWM3,
                                 PWM4, PWM5, PWM6, PWM7};
  struct_PWM_t *SPWM_Device[] = {SPWM};
  struct_PWM_t *RPWM_Device[] = {RPWM};
  char *str[]                 = {"pwm0", "pwm1", "pwm2", "pwm3",
                 "pwm4", "pwm5", "pwm6", "pwm7"};
  pwm_device_t *dev;

  itcs_module_enable(sysmode, str[channel]);

  /* PWM int enable */
  itcs_module_set_pads(sysmode, FPGA_BIT_V_EMMC, str[channel]);
  // printf("sysmode is %d,channel name is %s\n",sysmode,str[channel]);
  dev = (pwm_device_t *)malloc(sizeof(pwm_device_t));
  if (!dev)
    return NULL;
  if (sysmode == 0 && channel <= 7)
    dev->pwm = CPWM_Device[channel];
  else if (sysmode == 1 && channel == 0)
    dev->pwm = SPWM_Device[channel];
  else if (sysmode == 2 && channel == 0){
    dev->pwm = RPWM_Device[channel];
    #if 1
    uint32_t tempreg = readl(ITCS_R_BASE + 0x204);
    printf("RCT pclk is enable! Tempreg is 0x%x\n",readl(ITCS_R_BASE + 0x204));
    tempreg |= 0x2;
    writel(tempreg, ITCS_R_BASE + 0x204);
    printf("RCT pclk is enable! Tempreg is 0x%x\n",readl(ITCS_R_BASE + 0x204));
    
    #endif
  }
    

  /* set period */
  dev->pwm->Period = init->period;
  /* calculate high clock */
  lu32_HighClock = init->period * init->duty * 10;
  lu32_HighClock /= 100;

  if (lu32_HighClock % 10 > 5)
    lu32_HighClock += 10;

  lu32_HighClock /= 10;

  dev->pwm->Hightime = lu32_HighClock;

  /* is enable interrupt */
  if (init->channel_int_enable == PWM_CHANNEL_INT_ENABLE) {
    if (sysmode == 0) {
      dev->irq = C_PWM0_IRQn + channel;
    } else if (sysmode == 1) {
      dev->irq = S_PWM0_IRQn;
    } else if (sysmode == 2) {
      dev->irq = RTC10_IRQn;
    }

    if (init->callback) {
      dev->callback       = init->callback;
      dev->callback_param = init->callback_param;
    }
    /* pwm int enable */
    dev->pwm->EnableINT = PWM_CHANNEL_INT_ENABLE;

    int ret = request_irq(dev->irq, pwm_irq_handler, str[channel], dev);

    if (ret < 0) {
      free(dev);
      return NULL;
    }
  }
  return dev;
}

/*************************************************************************
 * @brief : pwm period update
 * @param : dev: device handle.
 *          period: period clocks.
 * @retval: none.
 */
void itcs_pwm_period_update(pwm_device_t *dev, uint32_t period) {
  uint32_t lu32_HighClock;

  /* calculate duty */
  lu32_HighClock = (dev->pwm->Hightime * period) / dev->pwm->Period;

  /* set period */
  dev->pwm->Period   = period;
  dev->pwm->Hightime = lu32_HighClock;
}

/*************************************************************************
 * @brief : pwm duty update
 * @param : dev: device handle.
 *          period: period clocks.
 * @retval: none.
 */
void itcs_pwm_duty_update(pwm_device_t *dev, uint32_t duty) {
  uint32_t lu32_period;
  uint32_t lu32_HighClock;

  /* get period */
  lu32_period = dev->pwm->Period;
  /* calculate high clock */
  lu32_HighClock = lu32_period * duty * 10;
  lu32_HighClock /= 100;

  if (lu32_HighClock % 10 > 5)
    lu32_HighClock += 10;

  lu32_HighClock /= 10;

  dev->pwm->Hightime = lu32_HighClock;
}

/*************************************************************************
 * @brief : pwm channel output enable
 * @param : dev: device handle.
 * @retval: none
 */
void itcs_pwm_start( pwm_device_t *dev) { dev->pwm->Control = 0x1; }

/*************************************************************************
 * @brief : pwm channel output disable
 * @param : dev: device handle.
 * @retval: none
 */
void itcs_pwm_stop(pwm_device_t *dev) { dev->pwm->Control = 0x0; }

/*************************************************************************
 * @brief : pwm channel interrupt enable
 * @param : dev: device handle.
 * @retval: none
 */
void pwm_int_enable(pwm_device_t *dev) { dev->pwm->EnableINT = 1; }

/*************************************************************************
 * @brief : pwm channel interrupt disable
 * @param : dev: device handle.
 * @retval: none
 */
void pwm_int_disable(pwm_device_t *dev) { dev->pwm->DisableINT = 1; }

/*************************************************************************
 * @brief : pwm channel get interrupt status
 * @param : dev: device handle.
 * @retval: none
 */
uint32_t pwm_int_get_status(pwm_device_t *dev) { return dev->pwm->StatusINT; }

/*************************************************************************
 * @brief : itcs_pwm_deinit
 * @param : dev: device handle.
 * @retval: none
 */
void itcs_pwm_deinit(pwm_device_t *dev) {
  if (dev)
    free(dev);
}
