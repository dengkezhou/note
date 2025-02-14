/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
--         Copyright (c) 2011-2014, Google Inc. All rights reserved.          --
--         Copyright (c) 2007-2010, Hantro OY. All rights reserved.           --
--                                                                            --
-- This software is confidential and proprietary and may be used only as      --
--   expressly authorized by VeriSilicon in a written licensing agreement.    --
--                                                                            --
--         This entire notice must be reproduced on all copies                --
--                       and may not be removed.                              --
--                                                                            --
--------------------------------------------------------------------------------
-- Redistribution and use in source and binary forms, with or without         --
-- modification, are permitted provided that the following conditions are met:--
--   * Redistributions of source code must retain the above copyright notice, --
--       this list of conditions and the following disclaimer.                --
--   * Redistributions in binary form must reproduce the above copyright      --
--       notice, this list of conditions and the following disclaimer in the  --
--       documentation and/or other materials provided with the distribution. --
--   * Neither the names of Google nor the names of its contributors may be   --
--       used to endorse or promote products derived from this software       --
--       without specific prior written permission.                           --
--------------------------------------------------------------------------------
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"--
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  --
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE --
-- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  --
-- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        --
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       --
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   --
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    --
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    --
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE --
-- POSSIBILITY OF SUCH DAMAGE.                                                --
--------------------------------------------------------------------------------
--                Description : printf log info to ***.log                    --
------------------------------------------------------------------------------*/


/**********************************************************
* INCLUDES
**********************************************************/
#include <stdarg.h>
#ifdef VCD_LOGMSG
#include "dec_log.h"
#include "dwl.h"

#ifdef WIN32
#define GETPID() _getpid()
#else
#define GETPID() getpid()
#endif

/**********************************************************
* TYPES
**********************************************************/

/**********************************************************
* MACROS
**********************************************************/
#define VPU_MAX_DEBUG_BUFFER_LEN 1024 * 10
#define FILE_MAX_SIZE (1024 * 1024)
#define BUF_SIZE 1024
#define HSWREG(n) ((n)*4)

static FILE *log_output[STREAM_COUNT] = {0};
static char log_out_filename[256] = {0};
static log_env_setting env_log = {LOG_STDOUT, VCDEC_LOG_ERROR, 0x02};

static unsigned int vcdec_log_trace_bitmap[] = {
  1 << VCDEC_LOG_TRACE_CONFIG, 1 << VCDEC_LOG_TRACE_API,
  1 << VCDEC_LOG_TRACE_STREAM, 1 << VCDEC_LOG_TRACE_DWL,
  1 << VCDEC_LOG_TRACE_MEM, 1 << VCDEC_LOG_TRACE_DPB,
  1 << VCDEC_LOG_TRACE_REGS, 1 << VCDEC_LOG_TRACE_VCMD,
  1 << VCDEC_LOG_TRACE_IRQ, 1 << VCDEC_LOG_TRACE_PERF
};
static char *log_trace_str[] = {"config", "api", "stream", "dwl", "mem", "dpb", "regs", "vcmd", "irq", "perf"};

static pthread_mutex_t log_mutex;

/*
void getNameByPid(pid_t pid, char *task_name) {
  char proc_pid_path[BUF_SIZE];
  char buf[BUF_SIZE];

  sprintf(proc_pid_path, "/proc/%d/status", pid);
  FILE *fp = fopen(proc_pid_path, "r");
  if (NULL != fp) {
    if (fgets(buf, BUF_SIZE - 1, fp) == NULL) {
      fclose(fp);
    }
    fclose(fp);
    sscanf(buf, "%s", task_name);
  }
}
*/

// rainbow fprint
#ifdef VCD_LOGMSG
static void _rainbow_fprint(FILE *stream, vcdec_log_level log_level, char *str_content) {
  switch (log_level) {
    case VCDEC_LOG_ERROR:
      fprintf(stream, "%s", str_content);
      break;
    case VCDEC_LOG_INFO:
      fprintf(stream, "%s", str_content);
      break;
    default:
      fprintf(stream, "%s", str_content);
      break;
  }
}

static char *CetTimeStamp(char *timestamp) {
  struct timeval tv;
  if (gettimeofday(&tv, NULL) == 0) {
    sprintf(timestamp, "%04d.%06d", (unsigned int)tv.tv_sec & 0xffff,
            (unsigned int)tv.tv_usec);
  }
  return timestamp;
}
#endif

#ifdef VCD_LOGMSG
int VCDecLogInit(unsigned int out_dir, unsigned int out_level, unsigned int trace_map) {
  FILE *fp1;
  static int init_done_flag = -1;

  if (1 == init_done_flag) {
    return 0;
  }

  env_log.out_dir = (vcdec_log_output)out_dir;
  env_log.out_level = (vcdec_log_level)out_level;
  env_log.k_trace_map = trace_map;

  if ((LOG_ONE_FILE == env_log.out_dir) && (VCDEC_LOG_QUIET != env_log.out_level)) {
    sprintf(log_out_filename, "vcdec_trace_p%d.log", GETPID());
    fp1 = fopen(log_out_filename, "wt");
    if ((fp1 == NULL)) {
      printf("Fail to open LOG file! [%s:%d] \n", __FILE__, __LINE__);
      return -1;
    }
    log_output[STREAM_TRACE_FILE] = fp1;
  }
  pthread_mutex_init(&log_mutex, NULL);
  init_done_flag = 1;

  return 0;
}
#else
int VCDecLogInit(unsigned int out_dir, unsigned int out_level, unsigned int trace_map) {
  return 0;
}
#endif

#ifdef VCD_LOGMSG
int VCDecLogDestory(void)
{
  if ((LOG_ONE_FILE == env_log.out_dir) &&
  (VCDEC_LOG_QUIET != env_log.out_level)) {
    fclose(log_output[STREAM_TRACE_FILE]);
  }
  pthread_mutex_destroy(&log_mutex);

  return 1;
}
#else
int VCDecLogDestory(void) {
  return 1;
}
#endif

void VCDecTraceMsg(void *inst, vcdec_log_level level,
                   unsigned int log_trace_level, int prefix, const char *fmt,...)
{
  char arg_buffer[VPU_MAX_DEBUG_BUFFER_LEN - 128 - 6 - 18] = {0};  //6 for log_trace_str[i] and 18 for pointer inst
  char msg_buffer[VPU_MAX_DEBUG_BUFFER_LEN] = {0};
  char time_stamp_buffer[128] = {0};
  va_list arg;
  FILE *fLog;

  //do nothing if env "VCDEC_LOG_LEVEL" not match
  if (level > env_log.out_level) {
    return;
  }
  // do nothing if env "VCDEC_LOG_TRACE" not match
  if ((env_log.k_trace_map & vcdec_log_trace_bitmap[log_trace_level]) == 0) {
    return;
  }
  va_start(arg, fmt);
  vsnprintf(arg_buffer, VPU_MAX_DEBUG_BUFFER_LEN - 128 - 6 - 18, fmt, arg);
  va_end(arg);
  // add time stamp
  CetTimeStamp(time_stamp_buffer);
  if (prefix == 1) {
    if (inst == NULL){
    sprintf(msg_buffer, "[%s] [%s] %s", time_stamp_buffer, log_trace_str[log_trace_level], arg_buffer);
    } else{
    sprintf(msg_buffer, "[%s] %s[%p] %s", time_stamp_buffer, log_trace_str[log_trace_level], (inst), arg_buffer);
    }
  }
  else
    sprintf(msg_buffer, "%s", arg_buffer);


  if ((LOG_ONE_FILE == env_log.out_dir) &&
      (VCDEC_LOG_QUIET != env_log.out_level)) {
    pthread_mutex_lock(&log_mutex);
    fprintf(log_output[STREAM_TRACE_FILE], "%s", msg_buffer);
    pthread_mutex_unlock(&log_mutex);
    fflush(log_output[STREAM_TRACE_FILE]);
  } else if (LOG_BY_THREAD == env_log.out_dir) {
    //combine the log filename
    sprintf(log_out_filename, "vcdec_trace_p%d_t%lu.log", GETPID(),
    pthread_self());
    fLog = fopen(log_out_filename, "at+");
	if (fLog == NULL) return;
    fprintf(fLog, "%s", msg_buffer);
    fflush(fLog);
    fclose(fLog);
  } else if (LOG_STDOUT == env_log.out_dir) {
    _rainbow_fprint(stdout, level, msg_buffer);
    fflush(stdout);
  } else {
    _rainbow_fprint(stderr, level, msg_buffer);
  }

} /* VCDecTraceMsg() */
#endif
