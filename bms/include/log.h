/*
 * log message define
 * log level :
 * 			info
 * 			debug
 * 			warning
 * 			error
 *only log the level large than LOG_LEVEL
 *modify the LOG_LEVEL to deside the the log message type
 *
 *
 */

#ifndef __CASE_LOG_H__
#define __CASE_LOG_H__

#include <common.h>
#define LOG_STR(str) str

// system log level define
#define SYS_LOG_LEVEL 0

// standard level define
#define LOG_LEVEL_VER  0
#define LOG_LEVEL_DBG  1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERR  4

#define LOG_HANDLER(str...) (printf)(str)

#define LOG_VER(str...)                                                        \
  if (LOG_LEVEL_VER >= SYS_LOG_LEVEL) {                                        \
    LOG_HANDLER("VER ->%s :%d:%s -->", __FILE__, __LINE__, __func__);          \
    LOG_HANDLER(str);                                                          \
    LOG_HANDLER("\r\n");                                                       \
  }
#define LOG_DBG(str...)                                                        \
  if (LOG_LEVEL_DBG >= SYS_LOG_LEVEL) {                                        \
    LOG_HANDLER("DBG ->%s :%d:%s -->", __FILE__, __LINE__, __func__);          \
    LOG_HANDLER(str);                                                          \
    LOG_HANDLER("\r\n");                                                       \
  }
#define LOG_INFO(str...)                                                       \
  if (LOG_LEVEL_INFO >= SYS_LOG_LEVEL) {                                       \
    LOG_HANDLER("INFO ->%s :%d:%s -->", __FILE__, __LINE__, __func__);         \
    LOG_HANDLER(str);                                                          \
    LOG_HANDLER("\r\n");                                                       \
  }
#define LOG_WARN(str...)                                                       \
  if (LOG_LEVEL_WARN >= SYS_LOG_LEVEL) {                                       \
    LOG_HANDLER("WARN ->%s :%d:%s -->", __FILE__, __LINE__, __func__);         \
    LOG_HANDLER(str);                                                          \
    LOG_HANDLER("\r\n");                                                       \
  }
#define LOG_ERR(str...)                                                        \
  if (LOG_LEVEL_ERR >= SYS_LOG_LEVEL) {                                        \
    LOG_HANDLER("ERR ->%s :%d:%s -->", __FILE__, __LINE__, __func__);          \
    LOG_HANDLER(str);                                                          \
    LOG_HANDLER("\r\n");                                                       \
  }

#endif
