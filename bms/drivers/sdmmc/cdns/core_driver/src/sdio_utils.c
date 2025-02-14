/******************************************************************************
 * Copyright (C) 2013-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio_utils.c
 * Auxiliary driver functions
 *****************************************************************************/

#include "sdio_utils.h"
#include "sdio_errors.h"
#include "sdio_host.h"

/*****************************************************************************/
void DataSet(void *Destination, uint8_t Value, size_t SizeArg)
{
    size_t Size = SizeArg;
    size_t i;

    if ((Size & 3U) != 0U) {
        uint8_t *Dst = Destination;

        for (i = 0; i < Size; i++) {
            Dst[i] = Value;
        }
    }
    else {
        uint32_t *Dst = Destination;
        uint32_t val32 = ((uint32_t)Value << 24) | ((uint32_t)Value << 16)
                         | ((uint32_t)Value << 8) | Value;

        Size = Size >> 2;

        for (i = 0; i < Size; i++) {
            Dst[i] = val32;
        }
    }
}
/*****************************************************************************/

/******************************************************************************/
uint8_t WaitForValue(volatile uint32_t* Address, uint32_t Mask, uint8_t IsSet,
                     uint32_t TimeUs)
{
    uint8_t status = SDIO_ERR_NO_ERROR;
    uint32_t TimeNs = TimeUs * 1000 + 100;

    if (IsSet == 0U) {
        // wait until bit/bits will clear
        while (((CPS_REG_READ(Address) & Mask) != 0U)) {
            CPS_DelayNs(100);
            if (TimeNs < 100) {
                status = SDIO_ERR_TIMEOUT;
                break;
            }
            TimeNs -= 100;

        }
    } else {
        // wait until a bit/bits will set
        while (((CPS_REG_READ(Address) & Mask) == 0U)) {
            CPS_DelayNs(100);
            if (TimeNs < 100) {
                status = SDIO_ERR_TIMEOUT;
                break;
            }
            TimeNs -= 100;
        }
    }
    return (status);
}
/******************************************************************************/


static uint32_t Timer[SDIO_SLOT_COUNT];
/******************************************************************************/
void RetuningSetTimer(uint32_t Seconds, uint8_t TimerNumber)
{
    Timer[TimerNumber] = Seconds;
}
/******************************************************************************/

/******************************************************************************/
void RetuningGetTimer(uint32_t *Seconds, uint8_t TimerNumber)
{
    if (Timer[TimerNumber] > 0U) {
        Timer[TimerNumber]--;
    }
    *Seconds = Timer[TimerNumber];
}
/******************************************************************************/

uint32_t swap32(uint32_t data)
{
    return ((data & 0xFF000000U) >> 24) |
           ((data & 0x00FF0000U) >> 8) |
           ((data & 0x0000FF00U) << 8) |
           ((data & 0x000000FFU) << 24);
}

uint16_t swap16(uint16_t data)
{
    return ((data & 0xFF00U) >> 8)  |
           ((data & 0x00FFU) << 8);
}

