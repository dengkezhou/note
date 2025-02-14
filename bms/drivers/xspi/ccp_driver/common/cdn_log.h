/******************************************************************************
 *
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * cdn_log.h
 * System wide debug log messaging framework
 *****************************************************************************/

#ifndef INCLUDE_CDN_LOG_H

#define INCLUDE_CDN_LOG_H

#include "cdn_assert.h"
#include "cdn_inttypes.h"
#include <stdarg.h>
#include <stdio.h>

#define DEBUG 1
#ifdef DEBUG
 #if DEBUG
  #define CFP_DBG_MSG 1
 #endif
#endif

/**
 * Modules definitions
 */
#define CLIENT_MSG         0x01000000

#define DBG_GEN_MSG        0xFFFFFFFF

/**
 * Log level:
 * DBG_CRIT - critical
 * DBG_WARN - warning
 * DBG_FYI - fyi
 * DBG_HIVERB - highly verbose
 * DBG_INFLOOP - infinite loop debug
 */
#define DBG_CRIT 0
#define DBG_WARN 5
#define DBG_FYI 10
#define DBG_HIVERB 100
#define DBG_INFLOOP 200

/* module mask: */
#ifdef _HAVE_DBG_LOG_INT_
uint32_t g_dbg_enable_log  = 0;
#else
extern uint32_t g_dbg_enable_log;
#endif

/* level, counter, state: */
#ifdef _HAVE_DBG_LOG_INT_
uint32_t g_dbg_log_lvl = DBG_CRIT;
uint32_t g_dbg_log_cnt = 0;
uint32_t g_dbg_state = 0;
#else
extern uint32_t g_dbg_log_lvl;
extern uint32_t g_dbg_log_cnt;
extern uint32_t g_dbg_state;
#endif

#ifdef DEBUG
static inline void DbgPrint(const char *fmt, ...)
{
    printf("XSPI-DEBUG:");
    char buf[1024] = {0};
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    printf("%s", buf);
}
#define vDbgMsg(log_lvl, module, msg, ...)    DbgPrint( msg, ##__VA_ARGS__)
#define cvDbgMsg(log_lvl, module, msg, ...)   DbgPrint( msg, ##__VA_ARGS__)
#define evDbgMsg(log_lvl, module, msg, ...)   { DbgPrint( msg, ##__VA_ARGS__); assert(0); }

#else

#define vDbgMsg(log_lvl, module, msg, ...)    
#define cvDbgMsg(log_lvl, module, msg, ...)  
#define evDbgMsg(log_lvl, module, msg, ...)   
#endif




#define DbgMsgSetLvl( x ) (g_dbg_log_lvl = (x))
#define DbgMsgEnableModule( x ) (g_dbg_enable_log |= (x) )
#define DbgMsgDisableModule( x ) (g_dbg_enable_log &= ~( (uint32_t) (x) ))
#define DbgMsgClearAll( _x ) ( g_dbg_enable_log = (_x) )

#define SetDbgState( _x ) (g_dbg_state = (_x) )
#define GetDbgState       (g_dbg_state)

// parasoft-end-suppress MISRA2012-RULE-8_6-2
// parasoft-end-suppress MISRA2012-DIR-4_4-4

#endif // INCLUDE_CDN_LOG_H
