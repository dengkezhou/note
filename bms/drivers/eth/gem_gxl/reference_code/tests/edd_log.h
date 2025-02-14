/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#ifndef INCLUDE_EDD_LOG_H
#define INCLUDE_EDD_LOG_H

#ifdef __KERNEL__
#include <linux/string.h>
#else
#ifdef KDEBUG
#error ###### Should be compiling in kernel driver, not as user app
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#include "cdn_log.h"
#include "test_harness_log.h"
#include "cedi_priv.h"
#include "cps.h"

// shortcut macros for logging to DBG_GEN_MSG module using vDbgMsg
// empty strings added to avoid empty __VA_ARGS__ in vDbgMsg macro
#define log_dbg( lvl, ...)   vDbgMsg( DBG_GEN_MSG, lvl, __VA_ARGS__, "");
#define log_dbg_fyi( ...)   vDbgMsg( DBG_GEN_MSG, DBG_FYI, __VA_ARGS__, "");
#define log_dbg_warn( ...)   vDbgMsg( DBG_GEN_MSG, DBG_WARN, __VA_ARGS__, "");
#define log_dbg_crit( ...)   vDbgMsg( DBG_GEN_MSG, DBG_CRIT, __VA_ARGS__, "");
#define log_dbg_hiverb( ...)   vDbgMsg( DBG_GEN_MSG, DBG_HIVERB, __VA_ARGS__, "");

// shortcut macros for logging to DBG_GEN_MSG module using cDbgMsg (like normal printf)
#define log_simple( lvl, ...)   cDbgMsg( DBG_GEN_MSG, lvl, __VA_ARGS__, "");
#define log_simple_fyi( ...)   cDbgMsg( DBG_GEN_MSG, DBG_FYI, __VA_ARGS__, "");
#define log_simple_warn( ...)   cDbgMsg( DBG_GEN_MSG, DBG_WARN, __VA_ARGS__, "");
#define log_simple_crit( ...)   cDbgMsg( DBG_GEN_MSG, DBG_CRIT, __VA_ARGS__, "");
#define log_simple_hiverb( ...)   cDbgMsg( DBG_GEN_MSG, DBG_HIVERB, __VA_ARGS__, "");

void printTxDescList(const CEDI_PrivateData *pD, uint8_t qNum);
void printRxDescList(const CEDI_PrivateData *pD, uint8_t qNum);
void printNetControlReg(const CEDI_PrivateData *pD);
void printDesignCfg(const CEDI_PrivateData *pD);
void printNetConfigReg(const CEDI_PrivateData *pD);
void printNetStatusReg(const CEDI_PrivateData *pD);
void printDmaConfigReg(const CEDI_PrivateData *pD);
void printTxStatus(uint8_t emacObj);
void printRxVAddrList(CEDI_PrivateData *pD, uint8_t qNum);
void printStatsCopy(const CEDI_PrivateData *pD);
void printRxStatus(uint8_t emacObj);

#endif // INCLUDE_EDD_LOG_H
