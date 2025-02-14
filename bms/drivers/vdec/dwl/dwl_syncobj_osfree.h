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
#ifndef _DWL_SYNCOBJ_OSFREE_H_
#define _DWL_SYNCOBJ_OSFREE_H_

#include "basetype.h"
#include "dwl_defs.h"
#include "dwl.h"
#include "ppu.h"
#include "dwlthread.h"
#include "memalloc.h"
#include "deccfg.h"
#include <assert.h>
#include <string.h>
#include "hantrodec_osfree.h"

#ifdef MODEL_SIMULATION
#define _SYSTEM_MODEL_
#endif

#ifndef DEC_MODULE_PATH
#define DEC_MODULE_PATH         "/tmp/dev/hantrodec"
#endif

#ifndef MEMALLOC_MODULE_PATH
#define MEMALLOC_MODULE_PATH    "/tmp/dev/memalloc"
#endif

#define HANTROPP_REG_START       0xF0
#define HANTRODEC_REG_START      0x4

#define HANTROPP_FUSE_CFG         99
#define HANTRODEC_FUSE_CFG        57

#define DWL_DECODER_INT ((DWLReadReg(dec_dwl, HANTRODEC_REG_START) >> 11) & 0xFFU)
#define DWL_PP_INT      ((DWLReadReg(dec_dwl, HANTROPP_REG_START) >> 11) & 0xFFU)

#define DEC_IRQ_ABORT          (1 << 11)
#define DEC_IRQ_RDY            (1 << 12)
#define DEC_IRQ_BUS            (1 << 13)
#define DEC_IRQ_BUFFER         (1 << 14)
#define DEC_IRQ_ASO            (1 << 15)
#define DEC_IRQ_ERROR          (1 << 16)
#define DEC_IRQ_SLICE          (1 << 17)
#define DEC_IRQ_TIMEOUT        (1 << 18)
#define DEC_IRQ_LAST_SLICE_INT (1 << 19)
#define DEC_IRQ_NO_SLICE_INT   (1 << 20)
#define DEC_IRQ_EXT_TIMEOUT    (1 << 21)

#define PP_IRQ_RDY             (1 << 12)
#define PP_IRQ_BUS             (1 << 13)

#define DWL_HW_ENABLE_BIT       0x000001    /* 0th bit */

#ifdef _DWL_HW_PERFORMANCE
/* signal that decoder/pp is enabled */
void DwlDecoderEnable(void);
void DwlPpEnable(void);
#endif

struct MCListenerThreadParams {
  int fd;
  int b_stopped;
  unsigned int n_dec_cores;
  sem_t sc_dec_rdy_sem[MAX_ASIC_CORES];
  DWLIRQCallbackFn *callback[MAX_ASIC_CORES];
  void *callback_arg[MAX_ASIC_CORES];
};

/* wrapper information */
struct HANTRODWL {
  u32 client_type;
  int fd;                  /* decoder device file */
  int fd_mem;              /* /dev/mem for mapping */
  int fd_memalloc;         /* linear memory allocator */
  u32 num_cores;
  struct regsize_desc reg_size;         /* IO mem size */
  struct regsize_desc dec400_reg_size;
  addr_t free_lin_mem;     /* Start address of free linear memory */
  addr_t free_ref_frm_mem; /* Start address of free reference frame memory */
  int semid;
//  struct mc_listener_thread_params_ *sync_params;
  u32 b_ppreserved;
  pthread_mutex_t shadow_mutex[MAX_ASIC_CORES];
  PpUnitIntConfig ppu_cfg[MAX_ASIC_CORES][DEC_MAX_PPU_COUNT];
  u32 tile_id[MAX_ASIC_CORES];
  u32 num_tiles[MAX_ASIC_CORES];
  u64 buf_size[MAX_ASIC_CORES];
  u64 tb_buff[MAX_ASIC_CORES];
  u32 pjpeg_coeff_buffer_size[MAX_ASIC_CORES];
  u32 *core_reg_base[MAX_ASIC_CORES];  /* registers base address */
  /* counters for core usage statistics */
  u32 core_usage_counts[MAX_ASIC_CORES];

  struct DecHwFeatures *hw_features; /* did a storage for current hw_features */
  u32 hwcfg_id_mask; /* it and hwcfg_id used to judge if the hw_features matches the client_type */
  u32 hwcfg_id;
};

i32 DWLWaitPpHwReady(const void *instance, i32 core_id, u32 timeout);
i32 DWLWaitDecHwReady(const void *instance, i32 core_id, u32 timeout);
void DWLUnmapRegisters(const void *io, unsigned int reg_size);

int g1_sim_open(const char* name, int flag);
void g1_sim_close(int fd);
long g1_sim_ioctl(/*struct file * */ int filp, unsigned int cmd, unsigned long arg);

#endif /* _DWL_SYNCOBJ_OSFREE_H_ */
