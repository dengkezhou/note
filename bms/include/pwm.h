/*
 ******************************************************************************
 * @file    pwm.h
 * @author  Intchains Firmware Team
 * @version V1.0.0
 * @date    2021
 * @brief   Header file of PWM HAL module.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 Intchains.
 * All rights reserved.
 ******************************************************************************
 */
#ifndef __DRIVER_PWM_H__
#define __DRIVER_PWM_H__

#include <common.h>
#include <malloc.h>
#include <irq.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_CLK_ENA (ITCS_R_BASE + 0x204)


/** @addtogroup PWM_Registers_Section
 * @{
 */
/* ################################ Register Section Start
 * ################################ */

/* -----------------------------------------------*/
/*                   PWM Register                 */
/* -----------------------------------------------*/
typedef struct {
  volatile uint32_t Control;    /* Offset 0x00 */
  volatile uint32_t Period;     /* Offset 0x04 */
  volatile uint32_t Hightime;   /* Offset 0x08 */
  volatile uint32_t ModuleID;   /* Offset 0x0C */
  volatile uint32_t EnableINT;  /* Offset 0x10 */
  volatile uint32_t DisableINT; /* Offset 0x14 */
  volatile uint32_t ValueINT;   /* Offset 0x18 */
  volatile uint32_t StatusINT;  /* Offset 0x1C */
} struct_PWM_t;

#define PWM0 ((struct_PWM_t *)ITCS_C_PWM0_BASE)
#define PWM1 ((struct_PWM_t *)ITCS_C_PWM1_BASE)
#define PWM2 ((struct_PWM_t *)ITCS_C_PWM2_BASE)
#define PWM3 ((struct_PWM_t *)ITCS_C_PWM3_BASE)
#define PWM4 ((struct_PWM_t *)ITCS_C_PWM4_BASE)
#define PWM5 ((struct_PWM_t *)ITCS_C_PWM5_BASE)
#define PWM6 ((struct_PWM_t *)ITCS_C_PWM6_BASE)
#define PWM7 ((struct_PWM_t *)ITCS_C_PWM7_BASE)
#define SPWM ((struct_PWM_t *)ITCS_S_PWM_BASE) /*----------sap PWM----------*/
#define RPWM ((struct_PWM_t *)ITCS_R_PWM_BASE) /*----------rtc PWM----------*/

/* ################################ Register Section END
 * ################################## */
/**
 * @}
 */

/** @addtogroup PWM_Initialization_Config_Section
 * @{
 */
/* ################################ Initialization��Config Section Start
 * ################################ */

#define PWM_CHANNEL_INT_DISABLE (0)
#define PWM_CHANNEL_INT_ENABLE  (1)

/*
 * @brief PWM device Structure definition
 */
typedef struct {
  struct_PWM_t *pwm;
  int irq;
  void (*callback)(void *dev, void *arg);
  void *callback_param;
} pwm_device_t;

/*
 * @brief PWM Init Structure definition
 */
typedef struct {
  uint32_t
      period; /*!< Specifies the number of period clocks.
                   This parameter can be a value 0x00000000 ~ 0xFFFFFFFF. */

  uint32_t duty; /*!< Specifies the number of duty.
                      This parameter can be a value 0% ~ 100%. */

  uint32_t channel_int_enable; /*!< pwm channel interrupt enable/disable. */

  void (*callback)(void *dev, void *arg);
  void *callback_param;

} pwm_init_t;

/* ################################ Initialization/Config Section END
 * ################################## */
/**
 * @}
 */

/*mux pin*/
#define PWM4_MUX_0_PADS 80
#define PWM5_MUX_0_PADS 81
#define PWM6_MUX_0_PADS 82
#define PWM7_MUX_0_PADS 83
#define PWM_MUX_0_FUNC PADS_FUNC0

#define PWM4_MUX_1_PADS 12
#define PWM5_MUX_1_PADS 13
#define PWM6_MUX_1_PADS 27
#define PWM7_MUX_1_PADS 28
#define PWM_MUX_1_FUNC PADS_FUNC1

#define PWM4_MUX_2_PADS 29
#define PWM5_MUX_2_PADS 30
#define PWM6_MUX_2_PADS 31
#define PWM7_MUX_2_PADS 32
#define PWM_MUX_2_FUNC PADS_FUNC2

#define PWM4_MUX_3_PADS 45
#define PWM5_MUX_3_PADS 46
#define PWM6_MUX_3_PADS 47
#define PWM7_MUX_3_PADS 48
#define PWM_MUX_3_FUNC PADS_FUNC2
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* itcs_pwm_config */
pwm_device_t *itcs_pwm_config(domain_t sysmode, uint32_t channel,
                              pwm_init_t *init);

/* itcs_pwm_period_update */
/* itcs_pwm_duty_update */
void itcs_pwm_period_update(pwm_device_t *dev, uint32_t period);
void itcs_pwm_duty_update(pwm_device_t *dev, uint32_t duty);

/* itcs_pwm_start */
/* itcs_pwm_stop */
void itcs_pwm_start(pwm_device_t *dev);
void itcs_pwm_stop(pwm_device_t *dev);

/* itcs_pwm_deinit */
void itcs_pwm_deinit(pwm_device_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __DRIVER_PWM_H__ */
