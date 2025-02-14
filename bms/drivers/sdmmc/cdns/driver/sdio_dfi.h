/******************************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 * Combo PHY configuration functions
 *****************************************************************************/

#ifndef DFI_H
#define DFI_H

#include "cdn_errno.h"
#include <csdd_if.h>

uint32_t dfiInitDriver(CSDD_SDIO_Host *pD);
uint32_t dfiInit(void);
uint32_t dfisdr104Init(void);
uint32_t dfisdr50Init(void);
uint32_t dfisdrInit(void);
uint32_t dfiddrInit(void);
uint32_t dfiddr50Init(void);
uint32_t dfihs200Init(uint32_t tune_val);
uint32_t dfihs400Init(void);
uint32_t dfihs400esInit(void);

#endif
