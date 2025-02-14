/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */


/******************************************************************************
 * @file     dw_timer.c
 * @brief    CSI Source File for timer Driver
 * @version  V1.0
 * @date     02. June 2017
 * @vendor   csky
 * @name     dw-timer
 * @ip_id    0x111000010
 * @model    timer
 * @tag      DRV_DW_TIMER_TAG
 ******************************************************************************/

#include <csi_core.h>
#include <timer.h>
#include <irq.h>
#include "dw_timer.h"

#define TIMER_NULL_PARAM_CHK(para)

typedef struct {
    uint8_t idx;
    uint32_t base;
    uint32_t irq;
    timer_event_cb_t cb_event;
    uint32_t timeout;                  ///< the set time (us)
    uint32_t timeout_flag;
} dw_timer_priv_t;

static dw_timer_priv_t timer_instance[CONFIG_TIMER_NUM] = {
    {
        .idx = 0,
        .base = CSKY_TIMER0_BASE,
        .irq = TIM0_IRQn,
    },
    {
        .idx = 1,
        .base = CSKY_TIMER1_BASE,
        .irq = TIM1_IRQn,
    },
    {
        .idx = 2,
        .base = CSKY_TIMER2_BASE,
        .irq = TIM2_IRQn,
    },
    {
        .idx = 3,
        .base = CSKY_TIMER3_BASE,
        .irq = TIM3_IRQn,
    },    
};

static int64_t dw_timer_freq(int32_t idx)
{
#if defined(CONFIG_COMPILE_SIM) && defined(CONFIG_E902)
    return itcs_pll_get_clock(CPU, "apll");
#else
#   error "Not support yet!"
#endif
}
/**
  \brief      Make all the timers in the idle state.
  \param[in]  pointer to timer register base
*/
static void timer_deactive_control(dw_timer_reg_t *addr)
{
    /* stop the corresponding timer */
    addr->TxControl &= ~DW_TIMER_TXCONTROL_ENABLE;
    /* Disable interrupt. */
    addr->TxControl |= DW_TIMER_TXCONTROL_INTMASK;
}

static int dw_timer_irqhandler(int idx, void *arg)
{
    dw_timer_priv_t *timer_priv = (dw_timer_priv_t *)arg;
    timer_priv->timeout_flag = 1;

    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    addr->TxEOI;

    if (timer_priv->cb_event) {
        timer_priv->cb_event(timer_priv);
    }

    return 0;
}

/**
  \brief       Initialize TIMER Interface. 1. Initializes the resources needed for the TIMER interface 2.registers event callback function
  \param[in]   idx  instance timer index
  \param[in]   cb_event  Pointer to \ref timer_event_cb_t
  \return      pointer to timer instance
*/
timer_handle_t csi_timer_initialize(int32_t idx, timer_event_cb_t cb_event)
{
    char irq_name[16] = {0};
    if (idx < 0 || idx >= CONFIG_TIMER_NUM) {
        return NULL;
    }

    dw_timer_priv_t *timer_priv = &timer_instance[idx];
    if (timer_priv->idx != idx) {
        return NULL;
    }

    snprintf(irq_name, 16, "timer%d", timer_priv->idx);
    request_irq(timer_priv->irq, dw_timer_irqhandler, irq_name, timer_priv);

    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    timer_deactive_control(addr);
    timer_priv->cb_event = cb_event;
    timer_priv->timeout = DW_TIMER_INIT_DEFAULT_VALUE;

    return (timer_handle_t)timer_priv;
}

/**
  \brief       De-initialize TIMER Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_uninitialize(timer_handle_t handle)
{
    TIMER_NULL_PARAM_CHK(handle);

    dw_timer_priv_t *timer_priv = (dw_timer_priv_t *)handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    timer_deactive_control(addr);
    timer_priv->cb_event = NULL;

    return 0;
}

/**
  \brief       config timer mode.
  \param[in]   handle timer handle to operate.
  \param[in]   mode      \ref timer_mode_e
  \return      error code
*/
int32_t csi_timer_config(timer_handle_t handle, uint32_t mode)
{
    TIMER_NULL_PARAM_CHK(handle);

    dw_timer_priv_t *timer_priv = handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    switch (mode) {
        case 0:
            addr->TxControl &= ~DW_TIMER_TXCONTROL_MODE;
            break;

        case 1:
            addr->TxControl |= DW_TIMER_TXCONTROL_MODE;
            break;

        default:
            return -1;
    }

    addr->TxControl |= (DW_TIMER_TXCONTROL_TRIGGER);

    return 0;
}

/**
  \brief       Set timer.
  \param[in]   instance  timer instance to operate.
  \param[in]   timeout the timeout value in microseconds(us).
  \return      error code
*/
int32_t csi_timer_set_timeout(timer_handle_t handle, uint32_t timeout)
{
    TIMER_NULL_PARAM_CHK(handle);

    dw_timer_priv_t *timer_priv = handle;
    timer_priv->timeout = timeout;
    return 0;
}

/**
  \brief       Start timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/

int32_t csi_timer_start(timer_handle_t handle)
{
    TIMER_NULL_PARAM_CHK(handle);

    dw_timer_priv_t *timer_priv = handle;

    timer_priv->timeout_flag = 0;

    uint32_t min_us = dw_timer_freq(timer_priv->idx) / 1000000;
    uint32_t load;

    if (((timer_priv->timeout * dw_timer_freq(timer_priv->idx)) / 1000000) > 0xffffffff) {
        return -1;
    }

    if (min_us) {
        load = (uint32_t)(timer_priv->timeout * min_us);
    } else {
        load = (uint32_t)(((uint64_t)(timer_priv->timeout) * dw_timer_freq(timer_priv->idx)) / 1000000);
    }

    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    if (timer_priv->timeout == 0) {
        addr->TxLoadCount = 0xffffffff;                           /* load time(us) */
    } else {
        if ((addr->TxControl | 0x2) == 0x2) {
            addr->TxLoadCount = 0xffffffff;                           /* load time(us) */
        } else {
            addr->TxLoadCount = load;                           /* load time(us) */
        }
    }

    addr->TxControl &= ~DW_TIMER_TXCONTROL_ENABLE;      /* disable the timer */
    addr->TxControl |= DW_TIMER_TXCONTROL_ENABLE;       /* enable the corresponding timer */
    addr->TxControl &= ~DW_TIMER_TXCONTROL_INTMASK;     /* enable interrupt */

    /* avoid timer bug on yunvoice soc */
#ifdef CONFIG_CHIP_YUNVOICE

    if (addr->TxCurrentValue > addr->TxLoadCount) {
        addr->TxControl &= ~DW_TIMER_TXCONTROL_ENABLE;      /* disable the timer */
        addr->TxControl |= DW_TIMER_TXCONTROL_ENABLE;       /* enable the corresponding timer */
        addr->TxControl &= ~DW_TIMER_TXCONTROL_INTMASK;     /* enable interrupt */
    }

#endif

    return 0;
}

/**
  \brief       Stop timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_stop(timer_handle_t handle)
{
    TIMER_NULL_PARAM_CHK(handle);

    dw_timer_priv_t *timer_priv = handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    addr->TxControl |= DW_TIMER_TXCONTROL_INTMASK;      /* enable interrupt */
    addr->TxControl &= ~DW_TIMER_TXCONTROL_ENABLE;      /* disable the timer */

    return 0;
}

/**
  \brief       suspend timer.
  \param[in]   instance  timer instance to operate.
  \return      error code
*/
int32_t csi_timer_suspend(timer_handle_t handle)
{
    TIMER_NULL_PARAM_CHK(handle);

    return -1;
}

/**
  \brief       resume timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_resume(timer_handle_t handle)
{
    TIMER_NULL_PARAM_CHK(handle);

    dw_timer_priv_t *timer_priv = handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    addr->TxControl &= ~DW_TIMER_TXCONTROL_ENABLE;      /* stop the corresponding timer */
    addr->TxControl &= DW_TIMER_TXCONTROL_ENABLE;       /* restart the corresponding timer */

    return 0;
}

/**
  \brief       get timer current value
  \param[in]   handle timer handle to operate.
  \param[out]   value     timer current value
  \return      error code
*/
int32_t csi_timer_get_current_value(timer_handle_t handle, uint32_t *value)
{
    TIMER_NULL_PARAM_CHK(handle);
    TIMER_NULL_PARAM_CHK(value);

    dw_timer_priv_t *timer_priv = handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    *value = addr->TxCurrentValue;
    return 0;
}

/**
  \brief       Get TIMER status.
  \param[in]   handle timer handle to operate.
  \return      TIMER status \ref timer_status_t
*/
timer_status_t csi_timer_get_status(timer_handle_t handle)
{
    timer_status_t timer_status = {0};

    if (handle == NULL) {
        return timer_status;
    }

    dw_timer_priv_t *timer_priv = handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    if (addr->TxControl & DW_TIMER_TXCONTROL_ENABLE) {
        timer_status.active = 1;
    }

    if (timer_priv->timeout_flag == 1) {
        timer_status.timeout = 1;
    }

    return timer_status;
}

/**
  \brief       get timer reload value
  \param[in]   handle timer handle to operate.
  \param[out]   value    timer reload value
  \return      error code
*/
int32_t csi_timer_get_load_value(timer_handle_t handle, uint32_t *value)
{
    TIMER_NULL_PARAM_CHK(handle);
    TIMER_NULL_PARAM_CHK(value);

    dw_timer_priv_t *timer_priv = handle;
    dw_timer_reg_t *addr = (dw_timer_reg_t *)(timer_priv->base);

    *value = addr->TxLoadCount;
    return 0;
}

