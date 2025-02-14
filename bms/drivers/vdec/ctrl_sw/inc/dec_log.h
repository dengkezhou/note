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
------------------------------------------------------------------------------*/

/**********************************************************
* INCLUDES
**********************************************************/
#ifndef _DEC_LOG_H
#define _DEC_LOG_H

/**********************************************************
* INCLUDES
**********************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

extern int printf(const char *__restrict, ...);

/**
 * \defgroup api_logmsg Log and Message Utility API
 *
 * @{
 */

/** Types of control for log */
enum {
  VCDEC_LOG_OUTPUT = 0, /**< For ENV to control output device */
  VCDEC_LOG_LEVEL = 1,  /**< For ENV to control output level */
  VCDEC_LOG_TRACE = 2, /**< For ENV to control trace information for prompt and debug */
};

/** Values of ENV "VCDEC_LOG_OUTPUT" */
typedef enum _vcdec_log_output {
  LOG_STDOUT = 0,    /**< All log output to stdout. */
  LOG_ONE_FILE = 1,  /**< All log use one log file.
                      * \n Trace file name is "vcdec_trace_p${pid}.log".
                      * \n Check file name is "vcdec_check_p${pid}.log". */
  LOG_BY_THREAD = 2, /**< Each thread of each instance has its own log file.
                      * \n Log file name is "vcdec_trace_p${pid}t${tid}.log". */
  LOG_STDERR = 3,    /**< All log output to stderr. */
  LOG_COUNT = 4      /**< Number of output device option. */
} vcdec_log_output;

/** Types of log message */
enum {
  STREAM_TRACE_FILE = 0, /**< Trace output is used for prompt and debug */
  STREAM_COUNT = 1
};

/** Category for VCDEC_LOG_TRACE ENV
 * The correspoing bit defined in ENV VCDEC_LOG_TRACE to indicate what kinds of log should be output for debug. */
enum {
  VCDEC_LOG_TRACE_CONFIG = 0,  /**< Output full command line and tb.cfg and feature_list; */
  VCDEC_LOG_TRACE_API = 1,  /**< Dump API call, replace "-DHEVCDEC_TRACE" */
  VCDEC_LOG_TRACE_STREAM = 2, /**< Dump stream parsing information */
  VCDEC_LOG_TRACE_DWL = 3,  /**< Dump DWL, replace "-D_DWL_DEBUG" */
  VCDEC_LOG_TRACE_MEM = 4,  /**< Dump memory usage, replace "MEMORY_USAGE_TRACE" */
  VCDEC_LOG_TRACE_DPB = 5, /**< replace "DPB_LOCK_TRACE"; */
  VCDEC_LOG_TRACE_REGS = 6, /**< Dump registers, replace "#ifndef DWL_DISABLE_REG_PRINTS" */
  VCDEC_LOG_TRACE_VCMD = 7, /**< Dump vcmd instruction; */
  VCDEC_LOG_TRACE_IRQ = 8,  /**<dump IRQ status; */
  VCDEC_LOG_TRACE_PERF = 9, /**< Performance information. */
  VCDEC_LOG_TRACE_COUNT = 10 /**< Number of trace option. */
};

/** Define the level defined in VCDEC_LOG_LEVEL. The message defined smaller than the level will
 * be output */
typedef enum _vcdec_log_level {
  VCDEC_LOG_QUIET = 0, /**< "quiet": no output; */
  VCDEC_LOG_ERROR = 1, /**< "error": error happens; */
  VCDEC_LOG_INFO = 2,  /**< "info": provide some information; */
  VCDEC_LOG_DEBUG = 3, /**< "debug": provide debug information; */
  VCDEC_LOG_ALL = 4,   /**< "": every thing; */
  VCDEC_LOG_COUNT = 5
} vcdec_log_level;

/** \brief Record the setting read from ENV */
typedef struct _log_env_setting {
  vcdec_log_output out_dir;
  vcdec_log_level out_level;
  unsigned int k_trace_map;
} log_env_setting;

/** Initialize the log message system
 *
 * all parameter get as this order:
 *              1. command line
 *              2. environment setting
 *              3. default value.
 * \param [in] to control log message output device.
 *              follow type definition of "vcdec_log_output"
 * \param [in] to control log message output level, from "QUIET(0)" to "ALL(6)"
 *              follow type definition of "vcdec_log_level"
 * \param [in] to control log message output trace information for prompt and debug. [63]=b`0111111
 *              0 = dump API call.
 *              1 = dump registers.
 *              2 = dump EWL.
 *              3 = dump memory usage.
 *              4 = dump Rate Control Status
 *              5 = output full command line
 *              6 = output performance information
 *
 * \param [in] to control log message output check information for test only. [1]=b`00001
 *              0 = output recon YUV data.
 *              1 = output quality PSNR/SSIM for each frame.
 *              2 = output VBV information for checking RC.
 *              3 = output RC information for RC profiling.
 *              4 = output features for coverage
 */
int VCDecLogInit(unsigned int out_dir, unsigned int out_level,
                 unsigned int trace_map);

/** Print the message according to log level and trace category. trace log is used
 * for information prompt and debug.
 *
 * \param [in] inst The instance the calling belong to.
 * \param [in] level Show the important of the message, from "FATAL(1)" to "DEBUG(5)"
 * \param [in] log_trace_level The bit mask to indicate which category of the information
 *             shall be printed when corresponding bit is 1.
 * \param [in] fmt The format same as "printf"
 * \retunr None.
 */
void VCDecTraceMsg(void *inst, vcdec_log_level level,
                   unsigned int log_trace_level, int prefix, const char *fmt, ...);

/** Print the message according to log level and check category. check log is used for testing
 *  only.
 *
 * \param [in] inst  The instance the calling belong to.
 * \param [in] level  Show the important of the message, from "FATAL(1)" to "DEBUG(5)"
 * \param [in] log_check_level The bit mask to indicate which category of the information
 *             shall be output to check file when corresponding bit is 1.
 * \param [in] fmt The format same as "printf"
 * \retunr None.
 */

/** Release related resouce used in logging messges */
int VCDecLogDestory(void);

#ifdef VCD_LOGMSG
/* Tracing macro */
#define APITRACEERR(fmt, ...)                                           \
  VCDecTraceMsg(NULL, VCDEC_LOG_ERROR, VCDEC_LOG_TRACE_API, 1, fmt,##__VA_ARGS__);
#define APITRACEDEBUG(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_DEBUG, VCDEC_LOG_TRACE_API, 1, fmt,##__VA_ARGS__)
#define APITRACEDEBUG_NP(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_DEBUG, VCDEC_LOG_TRACE_API, 0, fmt,##__VA_ARGS__)
#define APITRACE(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_API, 1, fmt,##__VA_ARGS__)

#define STREAMTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_STREAM, 1, fmt,##__VA_ARGS__)
#define STREAMTRACE_D(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_DEBUG, VCDEC_LOG_TRACE_STREAM, 1, fmt,##__VA_ARGS__)
/* Only output the content without the prefix*/
#define STREAMTRACE_D_NP(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_DEBUG, VCDEC_LOG_TRACE_STREAM, 0, fmt,##__VA_ARGS__)
#define STREAMTRACE_E(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_ERROR, VCDEC_LOG_TRACE_STREAM, 1, fmt,##__VA_ARGS__)
#define CONFIGTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_CONFIG, 1, fmt,##__VA_ARGS__)

#define CONFIGTRACE_E(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_ERROR, VCDEC_LOG_TRACE_CONFIG, 1, fmt,##__VA_ARGS__)

#define DPB_TRACE(fmt, ...)                              \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_DPB, 1, fmt,##__VA_ARGS__)
#define DPB_TRACE_NP(fmt, ...)                              \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_DPB, 0, fmt,##__VA_ARGS__)
#define HLS_CHECK(fmt, ...)                                           \
  VCDecTraceMsg(NULL, VCDEC_LOG_ERROR, VCDEC_LOG_TRACE_API, 1, fmt,##__VA_ARGS__);
#define DTRACE_E(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_ERROR, VCDEC_LOG_TRACE_DWL, 1, fmt,##__VA_ARGS__)
#define DTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_DWL, 1, fmt,##__VA_ARGS__)
#define DTRACE_D(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_DEBUG, VCDEC_LOG_TRACE_DWL, 1, fmt,##__VA_ARGS__)

/* dump registers --replace #ifndef DWL_DISABLE_REG_PRINTS */
#define REGTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_REGS, 1, fmt,##__VA_ARGS__)

/* dump memory usage --replace macro MEMORY_USAGE_TRACE */
#define MEMTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_MEM, 1, fmt,##__VA_ARGS__)

/* dump IRQ status */
#define IRQTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_IRQ, 1, fmt, ##__VA_ARGS__)
/* print VCMD instruction */
#define VCMDTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_VCMD, 1, fmt, ##__VA_ARGS__)

#define PERFTRACE_I(fmt, ...) \
  VCDecTraceMsg(NULL, VCDEC_LOG_INFO, VCDEC_LOG_TRACE_PERF, 1, fmt, ##__VA_ARGS__)

#else
#define VCDecLogInit()
#define VCDecTraceMsg()
#define VCDecLogDestory()
#define APITRACEERR(...) printf(__VA_ARGS__)
#define APITRACE(...)
#define APITRACEDEBUG(...)
#define APITRACEDEBUG_NP(...)
#define CONFIGTRACE_I(...)
#define CONFIGTRACE_E(...)
#define STREAMTRACE_I(...)
#define STREAMTRACE_E(...)
#define STREAMTRACE_D(...)
#define STREAMTRACE_D_NP(...)
#define DPB_TRACE_NP(...)


#define DPB_TRACE(...)
#define HLS_CHECK(...)
#define DTRACE_E(...) printf(__VA_ARGS__)
#define DTRACE_I(...)
#define DTRACE_D(...)
#define REGTRACE_I(...)
#define IRQTRACE_I(...)
#define MEMTRACE_I(...)
#define VCMDTRACE_I(...)
#define PERFTRACE_I(...)
#endif

/** @} */

#if defined(__cplusplus)
}
#endif

#endif /* _DEC_LOG_H */

