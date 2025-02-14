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

#include "basetype.h"
#include "dwl_defs.h"
#include "dwl_syncobj_osfree.h"
#include "dwl.h"
#include "dwlthread.h"
#include "hantrodec_osfree.h"
#include "memalloc.h"
#include "deccfg.h"
#include "dec_log.h"
#include "vpufeature.h"

#ifdef MODEL_SIMULATION
#include "asic.h"
#endif

#ifdef _USE_VSI_STRING_
#include "vsi_string.h"
#else
#include <string.h>
#endif

/* macro for assertion, used only when _ASSERT_USED is defined */
#ifdef _ASSERT_USED
#ifndef ASSERT
#include <assert.h>
#define ASSERT(expr) assert(expr)
#endif
#else
#define ASSERT(expr)
#endif

#define NEXT_MULTIPLE(value, n) (((value) + (n) - 1) & ~((n) - 1))

extern int printf(const char *__restrict, ...);

/* the decoder device driver nod */
const char *dec_dev = DEC_MODULE_PATH;
/* the memalloc device driver nod */
const char *mem_dev = MEMALLOC_MODULE_PATH;


#ifdef _SYSTEM_MODEL_
#include "tb_cfg.h"
extern struct TBCfg tb_cfg;
extern u32 g_hw_ver;
extern u32 h264_high_support;

#include "asic.h"
void *g_sysmodel_core[MAX_ASIC_CORES];
#endif

#ifdef INTERNAL_TEST
#include "internal_test.h"
#endif

#define DWL_PJPEG_E         22  /* 1 bit */
#define DWL_REF_BUFF_E      20  /* 1 bit */

#define DWL_JPEG_EXT_E          31  /* 1 bit */
#define DWL_REF_BUFF_ILACE_E    30  /* 1 bit */
#define DWL_MPEG4_CUSTOM_E      29  /* 1 bit */
#define DWL_REF_BUFF_DOUBLE_E   28  /* 1 bit */

#define DWL_MVC_E           20  /* 2 bits */

#define DWL_DEC_TILED_L     17  /* 2 bits */
#define DWL_DEC_PIC_W_EXT   14  /* 2 bits */
#define DWL_EC_E            12  /* 2 bits */
#define DWL_STRIDE_E        11  /* 1 bit */
#define DWL_FIELD_DPB_E     10  /* 1 bit */
#define DWL_AVS_PLUS_E       6  /* 1 bit */
#define DWL_64BIT_ENV_E      5  /* 1 bit */

#define DWL_CFG_E           24  /* 4 bits */
#define DWL_PP_IN_TILED_L   14  /* 2 bits */

#define DWL_SORENSONSPARK_E 11  /* 1 bit */

#define DWL_H264_FUSE_E          31 /* 1 bit */
#define DWL_MPEG4_FUSE_E         30 /* 1 bit */
#define DWL_MPEG2_FUSE_E         29 /* 1 bit */
#define DWL_SORENSONSPARK_FUSE_E 28 /* 1 bit */
#define DWL_JPEG_FUSE_E          27 /* 1 bit */
#define DWL_VP6_FUSE_E           26 /* 1 bit */
#define DWL_VC1_FUSE_E           25 /* 1 bit */
#define DWL_PJPEG_FUSE_E         24 /* 1 bit */
#define DWL_CUSTOM_MPEG4_FUSE_E  23 /* 1 bit */
#define DWL_RV_FUSE_E            22 /* 1 bit */
#define DWL_VP7_FUSE_E           21 /* 1 bit */
#define DWL_VP8_FUSE_E           20 /* 1 bit */
#define DWL_AVS_FUSE_E           19 /* 1 bit */
#define DWL_MVC_FUSE_E           18 /* 1 bit */

#define DWL_DEC_MAX_1920_FUSE_E  15 /* 1 bit */
#define DWL_DEC_MAX_1280_FUSE_E  14 /* 1 bit */
#define DWL_DEC_MAX_720_FUSE_E   13 /* 1 bit */
#define DWL_DEC_MAX_352_FUSE_E   12 /* 1 bit */
#define DWL_REF_BUFF_FUSE_E       7 /* 1 bit */


#define DWL_PP_FUSE_E       31  /* 1 bit */
#define DWL_PP_DEINTERLACE_FUSE_E   30  /* 1 bit */
#define DWL_PP_ALPHA_BLEND_FUSE_E   29  /* 1 bit */
#define DWL_PP_MAX_4096_FUSE_E    16  /* 1 bit */
#define DWL_PP_MAX_1920_FUSE_E    15  /* 1 bit */
#define DWL_PP_MAX_1280_FUSE_E    14  /* 1 bit */
#define DWL_PP_MAX_720_FUSE_E   13  /* 1 bit */
#define DWL_PP_MAX_352_FUSE_E   12  /* 1 bit */

#ifdef _DWL_FAKE_HW_TIMEOUT
static void DWLFakeTimeout(u32 * status);
#endif

#define IS_PIPELINE_ENABLED(val)    ((val) & 0x02)

/* shadow HW registers */
u32 dwl_shadow_regs[MAX_ASIC_CORES][MAX_REG_COUNT] = {0};

/* shadow id/config registers */
u32 dwl_shadow_config_regs[MAX_ASIC_CORES][MAX_REG_COUNT] = {0};
u32 hw_enable[MAX_ASIC_CORES] = {0};

static av_unused void PrintIrqType(u32 is_pp, u32 core_id, u32 status) {
  if(is_pp) {
    printf("PP[%d] IRQ %s\n", core_id,
           status & PP_IRQ_RDY ? "READY" : "BUS ERROR");
  } else {
    if(status & DEC_IRQ_ABORT)
      printf("DEC[%d] IRQ ABORT\n", core_id);
    else if (status & DEC_IRQ_RDY)
      printf("DEC[%d] IRQ READY\n", core_id);
    else if (status & DEC_IRQ_BUS)
      printf("DEC[%d] IRQ BUS ERROR\n", core_id);
    else if (status & DEC_IRQ_BUFFER)
      printf("DEC[%d] IRQ BUFFER\n", core_id);
    else if (status & DEC_IRQ_ASO)
      printf("DEC[%d] IRQ ASO\n", core_id);
    else if (status & DEC_IRQ_ERROR)
      printf("DEC[%d] IRQ STREAM ERROR\n", core_id);
    else if (status & DEC_IRQ_SLICE)
      printf("DEC[%d] IRQ SLICE\n", core_id);
    else if (status & DEC_IRQ_TIMEOUT)
      printf("DEC[%d] IRQ TIMEOUT\n", core_id);
    else if (status & DEC_IRQ_LAST_SLICE_INT)
      printf("DEC[%d] IRQ LAST_SLICE_INT\n", core_id);
    else if (status & DEC_IRQ_NO_SLICE_INT)
      printf("DEC[%d] IRQ NO_SLICE_INT\n", core_id);
    else if (status & DEC_IRQ_EXT_TIMEOUT)
      printf("DEC[%d] IRQ EXT_TIMEOUT\n", core_id);
    else
      printf("DEC[%d] IRQ UNKNOWN 0x%08x\n", core_id, status);
  }
}

/*------------------------------------------------------------------------------*/
int __init hantrodec_init(void);
int g1_sim_open(const char* name, int flag) {
#ifndef __BARE_METAL__
  if(!strcmp(name, DEC_MODULE_PATH))
#endif
  {
    hantrodec_init();
  }
  return 1;
}

void g1_sim_close(int fd) {
}

long g1_sim_ioctl(/*struct file * */ int filp, unsigned int cmd, unsigned long arg) {
  return hantrodec_ioctl(filp, cmd, arg);
}

/*------------------------------------------------------------------------------
    Function name   : DWLMapRegisters
    Description     :

    Return type     : u32 - the HW ID
------------------------------------------------------------------------------*/
static av_unused u32 *DWLMapRegisters(int mem_dev, unsigned long base,
                            unsigned int reg_size, u32 write) {
  u32* io;

  io = (u32*)base;

  return io;
}

void DWLUnmapRegisters(const void *io, unsigned int reg_size) {
}

/*------------------------------------------------------------------------------
    Function name   : DWLReadAsicCoreCount
    Description     : Return the number of hardware cores available
------------------------------------------------------------------------------*/
u32 DWLReadAsicCoreCount() {
  int fd_dec;
  unsigned int cores = 0;

  /* open driver */
  fd_dec = open(DEC_MODULE_PATH, O_RDONLY);
  if (fd_dec == -1) {
    DWL_DEBUG("failed to open %s\n", DEC_MODULE_PATH);
    return 0;
  }

  /* ask module for cores */
  if (ioctl(fd_dec, HANTRODEC_IOC_MC_CORES, &cores) == -1) {
    DWL_DEBUG("ioctl failed\n","");
    cores = 0;
  }

  if (fd_dec != -1)
    close(fd_dec);

  return (u32)cores;
}

/*------------------------------------------------------------------------------
    Function name   : DWLReadAsicID
    Description     : Read the HW ID. Does not need a DWL instance to run

    Return type     : u32 - the HW ID
------------------------------------------------------------------------------*/
u32 DWLReadAsicID(enum DWLClientType client_type) {

#ifdef _SYSTEM_MODEL_
  u32 build = 0;

  /* Set HW info from TB config */
  g_hw_ver = g_hw_ver ? g_hw_ver : 19001;
  build = g_hw_id;

  build = ( build/1000)     *0x1000 +
          ((build/100)%10) *0x100 +
          ((build/10)%10)  *0x10 +
          ((build)%10)     *0x1;

  switch (g_hw_ver) {
  case 8190:
    return 0x81900000 + build;
  case 9170:
    return 0x91700000 + build;
  case 9190:
    return 0x91900000 + build;
  case 10000:
    return 0x67310000 + build;  /* G1 */
  case 10001:
    return 0x67320000 + build;  /* G2 */
  default:
    return 0x90010000 + build;  /* VC9000D */
  }
#else
  u32 *io = MAP_FAILED, id = ~0;
  int fd_dec = -1, fd = 0;
  unsigned long base = 0;
  unsigned int reg_size = 0;

  DWL_DEBUG("\n");

  /* id from shadow regs */
  if(dwl_shadow_config_regs[0][0] != 0x00000000)
    return (u32)dwl_shadow_config_regs[0][0];

  fd = open("/dev/mem", O_RDONLY);
  if(fd == -1) {
    DWL_DEBUG("failed to open /dev/mem\n");
    goto end;
  }

  fd_dec = open(DEC_MODULE_PATH, O_RDONLY);
  if(fd_dec == -1) {
    DWL_DEBUG("failed to open %s\n", DEC_MODULE_PATH);
    goto end;
  }

  /* ask module for base */
  if(ioctl(fd_dec, HANTRODEC_IOCGHWOFFSET, &base) == -1) {
    DWL_DEBUG("ioctl failed\n");
    goto end;
  }

  /* ask module for reg size */
  if(ioctl(fd_dec, HANTRODEC_IOCGHWIOSIZE, &reg_size) == -1) {
    DWL_DEBUG("ioctl failed\n");
    goto end;
  }

  io = DWLMapRegisters(fd, base, reg_size, 0);

  if(io == MAP_FAILED) {
    DWL_DEBUG("failed to mmap regs.");
    goto end;
  }

  /* to shadow regs */
  id = dwl_shadow_config_regs[0][0] = io[0];

  DWLUnmapRegisters(io, reg_size);

end:
  if(fd != -1)
    close(fd);
  if(fd_dec != -1)
    close(fd_dec);

  return id;
#endif
}

/* HW Build ID is for feature list query */
/* For G1/G2, HwBuildId is reg0; otherwise it's reg309. */
static u32 DWLReadHwBuildID(enum DWLClientType client_type) {
#ifdef _SYSTEM_MODEL_
  g_hw_ver = g_hw_ver ? g_hw_ver : 19001;

  if (g_hw_ver == 10000 || g_hw_ver == 10001)
    return DWLReadAsicID(client_type);
  else
    return g_hw_build_id;
#else
  u32 *io = MAP_FAILED, id = ~0;
  int fd_dec = -1, fd = 0;
  unsigned long base = 0;
  unsigned int reg_size = 0;

  DWL_DEBUG("\n");

  /* id from shadow regs */
  if(dwl_shadow_config_regs[0][0] != 0x00000000)
    return (u32)dwl_shadow_config_regs[0][0];

  fd = open("/dev/mem", O_RDONLY);
  if(fd == -1) {
    DWL_DEBUG("failed to open /dev/mem\n");
    goto end;
  }

  fd_dec = open(DEC_MODULE_PATH, O_RDONLY);
  if(fd_dec == -1) {
    DWL_DEBUG("failed to open %s\n", DEC_MODULE_PATH);
    goto end;
  }

  /* ask module for base */
  if(ioctl(fd_dec, HANTRODEC_IOCGHWOFFSET, &base) == -1) {
    DWL_DEBUG("ioctl failed\n");
    goto end;
  }

  /* ask module for reg size */
  if(ioctl(fd_dec, HANTRODEC_IOCGHWIOSIZE, &reg_size) == -1) {
    DWL_DEBUG("ioctl failed\n");
    goto end;
  }

  io = DWLMapRegisters(fd, base, reg_size, 0);

  if(io == MAP_FAILED) {
    DWL_DEBUG("failed to mmap regs.");
    goto end;
  }

  /* to shadow regs */
  id = dwl_shadow_config_regs[0][309] = io[309];

  DWLUnmapRegisters(io, reg_size);

end:
  if(fd != -1)
    close(fd);
  if(fd_dec != -1)
    close(fd_dec);

  return id;
#endif
}

u32 DWLReadCoreHwBuildID(u32 core_id) {
#ifdef _SYSTEM_MODEL_
  return g_hw_build_id;
#else
  u32 *io = MAP_FAILED, id = ~0;
  int fd_dec = -1, fd = 0;
  unsigned long base = 0;
  unsigned int reg_size = 0;

  DWL_DEBUG("\n");

  /* id from shadow regs */
  if(dwl_shadow_config_regs[0][0] != 0x00000000)
    return (u32)dwl_shadow_config_regs[0][0];

  fd = open("/dev/mem", O_RDONLY);
  if(fd == -1) {
    DWL_DEBUG("failed to open /dev/mem\n");
    goto end;
  }

  fd_dec = open(DEC_MODULE_PATH, O_RDONLY);
  if(fd_dec == -1) {
    DWL_DEBUG("failed to open %s\n", DEC_MODULE_PATH);
    goto end;
  }

  /* ask module for base */
  if(ioctl(fd_dec, HANTRODEC_IOCGHWOFFSET, &base) == -1) {
    DWL_DEBUG("ioctl failed\n");
    goto end;
  }

  /* ask module for reg size */
  if(ioctl(fd_dec, HANTRODEC_IOCGHWIOSIZE, &reg_size) == -1) {
    DWL_DEBUG("ioctl failed\n");
    goto end;
  }

  io = DWLMapRegisters(fd, base, reg_size, 0);

  if(io == MAP_FAILED) {
    DWL_DEBUG("failed to mmap regs.");
    goto end;
  }

  /* to shadow regs */
  id = dwl_shadow_config_regs[0][309] = io[309];

  DWLUnmapRegisters(io, reg_size);

end:
  if(fd != -1)
    close(fd);
  if(fd_dec != -1)
    close(fd_dec);

  return id;
#endif
}

u32 DWLGetReleaseHwFeaturesByClientType(enum DWLClientType client_type, const void **p_hw_feature)
{
  ASSERT(p_hw_feature);
  const struct DecHwFeatures **hw_feature = (const struct DecHwFeatures **)p_hw_feature;

  u32 hw_build_id = DWLReadHwBuildID(client_type);

  GetReleaseHwFeaturesByID(hw_build_id, hw_feature);

  return 0;
}

/*------------------------------------------------------------------------------
    Function name   : DWLMallocRefFrm
    Description     : Allocate a frame buffer (contiguous linear RAM memory)

    Return type     : i32 - 0 for success or a negative error code

    Argument        : const void * instance - DWL instance
    Argument        : u32 size - size in bytes of the requested memory
    Argument        : void *info - place where the allocated memory buffer
                        parameters are returned
------------------------------------------------------------------------------*/
enum DWLRet DWLMallocRefFrm(const void *instance, u32 size, struct DWLLinearMem * info) {

  MEMTRACE_I("DWLMallocRefFrm\t%8d bytes\n", size);

  return DWLMallocLinear(instance, size, info);

}

/*------------------------------------------------------------------------------
    Function name   : DWLFreeRefFrm
    Description     : Release a frame buffer previously allocated with
                        DWLMallocRefFrm.

    Return type     : void

    Argument        : const void * instance - DWL instance
    Argument        : void *info - frame buffer memory information
------------------------------------------------------------------------------*/
void DWLFreeRefFrm(const void *instance, struct DWLLinearMem * info) {
  DWLFreeLinear(instance, info);
}

/*------------------------------------------------------------------------------
    Function name   : DWLMallocLinear
    Description     : Allocate a contiguous, linear RAM  memory buffer

    Return type     : i32 - 0 for success or a negative error code

    Argument        : const void * instance - DWL instance
    Argument        : u32 size - size in bytes of the requested memory
    Argument        : void *info - place where the allocated memory buffer
                        parameters are returned
------------------------------------------------------------------------------*/
enum DWLRet DWLMallocLinear(const void *instance, u32 size, struct DWLLinearMem * info) {
  av_unused struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;

  /* allocate device bus_address */
  info->logical_size = size;
  size = NEXT_MULTIPLE(size, DEC_X170_BUS_ADDR_ALIGNMENT);
  info->size = size;
  info->bus_address = (addr_t)(u32 *)aligned_malloc(DEC_X170_BUS_ADDR_ALIGNMENT, size);
  MEMTRACE_I("DWLMallocLinear: %8d\n", size);
  if(info->bus_address == 0) return DWL_ERROR;

/* DMA : allocate host virtual_address */
#ifdef SUPPORT_DMA
  u32 dma_mem_type = info->mem_type & 0xFF00;
  if (dma_mem_type == DWL_MEM_TYPE_DMA_HOST_TO_DEVICE ||
      dma_mem_type == DWL_MEM_TYPE_DMA_DEVICE_TO_HOST ||
      dma_mem_type == DWL_MEM_TYPE_DMA_HOST_AND_DEVICE) {
      MEMTRACE_I("DWLMallocLinear(DMA): %8d\n", size);
    info->virtual_address = (u32 *)aligned_malloc(DEC_X170_BUS_ADDR_ALIGNMENT, size);
    if (info->virtual_address == NULL) return DWL_ERROR;
  } else {
    info->virtual_address = (u32 *)info->bus_address;
  }
#else
  info->virtual_address = (u32 *)info->bus_address;
#endif
  return DWL_OK;
}

/*------------------------------------------------------------------------------
    Function name   : DWLFreeLinear
    Description     : Release a linera memory buffer, previously allocated with
                        DWLMallocLinear.

    Return type     : void

    Argument        : const void * instance - DWL instance
    Argument        : void *info - linear buffer memory information
------------------------------------------------------------------------------*/
void DWLFreeLinear(const void *instance, struct DWLLinearMem * info) {
  av_unused struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;

  ASSERT(dec_dwl != NULL);
  ASSERT(info != NULL);

  MEMTRACE_I("DWLFreeLinear: %8d\n", info->size);
  if(info->bus_address != 0)
    aligned_free((u32 *)info->bus_address);

/* DMA */
#ifdef SUPPORT_DMA
  u32 dma_mem_type = info->mem_type & 0xFF00;
  if (dma_mem_type == DWL_MEM_TYPE_DMA_HOST_TO_DEVICE ||
      dma_mem_type == DWL_MEM_TYPE_DMA_DEVICE_TO_HOST ||
      dma_mem_type == DWL_MEM_TYPE_DMA_HOST_AND_DEVICE) {
      MEMTRACE_I("DWLFreeLinear(DMA): %8d\n", info->size);
    if (info->virtual_address != NULL) {
      aligned_free(info->virtual_address);
    }
  } else {
    /* do nothing. */
  }
#endif

  info->bus_address = 0;
  info->virtual_address = NULL;
  info->size = 0;
  info->logical_size = 0;

}

/*------------------------------------------------------------------------------
    Function name   : DWLWriteReg
    Description     : Write a value to a hardware IO register

    Return type     : void

    Argument        : const void * instance - DWL instance
    Argument        : u32 offset - byte offset of the register to be written
    Argument        : u32 value - value to be written out
------------------------------------------------------------------------------*/

void DWLWriteReg(const void *instance, i32 core_id, u32 offset, u32 value) {
  av_unused struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;

  REGTRACE_I("core[%d] swreg[%d] at offset 0x%02X = %08X\n",
            core_id, offset/4, offset, value);

  offset = offset / 4;

  ASSERT(dec_dwl != NULL);
  ASSERT(offset < MAX_REG_COUNT * 4);
  ASSERT(core_id < (i32)dec_dwl->num_cores);


  dwl_shadow_regs[core_id][offset] = value;

#ifdef INTERNAL_TEST
  InternalTestDumpWriteSwReg(core_id, offset, value, dwl_shadow_regs[core_id]);
#endif
}

/**
 * Writes num 32-bit value to a specified hardware register.
 * All registers are written at once at the beginning of frame decoding.
 * \ingroup common_group
 * \param [in]     instance                  Pointer to a DWL instance.
 * \param [in]     core_id                   Core ID of the hardware resource to release.
 * \param [in]     offset                    Register offset is relative to the hardware ID register (#0) in byte.
 * \param [in]     from                      Source Register address.
 * \param [in]     num_regs                  The number of Registers should be Written.
 * \param [in]     print_flag                Whether print regs info.
 */
void DWLWriteRegs(const void *instance, i32 core_id, u32 offset, u32* from, u32 num_regs, u32 print_flag)
{
  (void)print_flag;
  for (u32 i = 0; i < num_regs; i++)
    DWLWriteReg(instance, core_id, offset + i, from[i]);
}

/*------------------------------------------------------------------------------
    Function name   : DWLReadReg
    Description     : Read the value of a hardware IO register

    Return type     : u32 - the value stored in the register

    Argument        : const void * instance - DWL instance
    Argument        : u32 offset - byte offset of the register to be read
------------------------------------------------------------------------------*/
u32 DWLReadReg(const void *instance, i32 core_id, u32 offset) {
  av_unused struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;
  u32 val;

  ASSERT(dec_dwl != NULL);
  ASSERT(offset < MAX_REG_COUNT * 4);
  ASSERT(core_id < (i32)dec_dwl->num_cores);

  offset = offset / 4;

  val = dwl_shadow_regs[core_id][offset];

  DWL_DEBUG("core[%d] swreg[%d] at offset 0x%02X = %08X\n",
            core_id, offset, offset * 4, val);

#ifdef INTERNAL_TEST
  InternalTestDumpReadSwReg(core_id, offset, val, dwl_shadow_regs[core_id]);
#endif

  return val;
}

/**
  * Reads num 32-bit value from a specified hardware register.
  * The status register is read after every macroblock decoding by software.
  * \ingroup common_group
  * \param [in]     instance                  Pointer to a DWL instance.
  * \param [in]     core_id                   Core ID of the hardware resource to release.
  * \param [in]     offset                    The first Register offset is relative to the hardware ID register (#0) in byte.
  * \param [in]     dest                      The destination Register address.
  * \param [in]     num                       The number of Registers should be copied.
------------------------------------------------------------------------------*/
void DWLReadRegs(const void *instance, i32 core_id, u32 offset, u32* dest, u32 num)
{
  for (u32 i = 0; i < num; i++)
    dest[i] = DWLReadReg(instance, core_id, offset + i);
}

/*------------------------------------------------------------------------------
    Function name   : DWLWriteRegToHw
    Description     : Write a value to a hardware IO register
    Return type     : void
    Argument        : const void * instance - DWL instance
    Argument        : u32 offset - byte offset of the register to be written
    Argument        : u32 value - value to be written out
------------------------------------------------------------------------------*/
void DWLWriteRegToHw(const void *instance, i32 core_id, u32 offset, u32 value)
{
    DWLWriteReg(instance, core_id, offset, value);
}

/*------------------------------------------------------------------------------
    Function name   : DWLReadRegFromHW
    Description     : Read the value of a hardware IO register
    Return type     : u32 - the value stored in the register
    Argument        : const void * instance - DWL instance
    Argument        : u32 offset - byte offset of the register to be read
------------------------------------------------------------------------------*/
u32 DWLReadRegFromHw(const void *instance, i32 core_id, u32 offset)
{
    return DWLReadReg(instance, core_id, offset);
}

/*------------------------------------------------------------------------------
    Function name   : DWLEnableHW
    Description     : Enable hw by writing to register
    Return type     : void
    Argument        : const void * instance - DWL instance
    Argument        : u32 offset - byte offset of the register to be written
    Argument        : u32 value - value to be written out
------------------------------------------------------------------------------*/
void DWLEnableHw(const void *instance, i32 core_id, u32 offset, u32 value) {
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;
  struct core_desc core;
  int ioctl_req = 0;

  ASSERT(dec_dwl);

  pthread_mutex_lock(&dec_dwl->shadow_mutex[core_id]);
  ioctl_req = HANTRODEC_IOCS_DEC_PUSH_REG;

  DWLWriteReg(dec_dwl, core_id, offset, value);

  DWL_DEBUG("%s %d enabled by previous DWLWriteReg\n",
            dec_dwl->client_type == DWL_CLIENT_TYPE_PP ? "PP" : "DEC",
            core_id);

  core.id = core_id;
  core.regs = dwl_shadow_regs[core_id];
  core.size = dec_dwl->reg_size.size;

  if(ioctl(dec_dwl->fd, ioctl_req, &core)) {
    DWL_DEBUG("ioctl HANTRODEC_IOCS_*_PUSH_REG failed\n", "");
    ASSERT(0);
  }
  hw_enable[core_id] = 1;

  dec_dwl->core_usage_counts[core_id]++;

  pthread_mutex_unlock(&dec_dwl->shadow_mutex[core_id]);
#ifdef _SYSTEM_MODEL_
  AsicHwCoreRun(g_sysmodel_core[core_id]);
#endif
}

/*------------------------------------------------------------------------------
    Function name   : DWLDisableHW
    Description     : Disable hw by writing to register
    Return type     : void
    Argument        : const void * instance - DWL instance
    Argument        : u32 offset - byte offset of the register to be written
    Argument        : u32 value - value to be written out
------------------------------------------------------------------------------*/
void DWLDisableHw(const void *instance, i32 core_id, u32 offset, u32 value) {
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;
  struct core_desc core;
  int ioctl_req = 0;

  ASSERT(dec_dwl);

  ioctl_req = HANTRODEC_IOCS_DEC_PUSH_REG;

  DWLWriteReg(dec_dwl, core_id, offset, value);

  DWL_DEBUG("%s %d disabled by previous DWLWriteReg\n", "DEC", core_id);

  core.id = core_id;
  core.regs = dwl_shadow_regs[core_id];
  core.size = dec_dwl->reg_size.size;

  if (ioctl(dec_dwl->fd, ioctl_req, &core)) {
    DWL_DEBUG("ioctl HANTRODEC_IOCS_*_PUSH_REG failed\n", "");
    ASSERT(0);
  }
}

/*------------------------------------------------------------------------------
    Function name   : DWLWaitHwReady
    Description     : Wait until hardware has stopped running.
                      Used for synchronizing software runs with the hardware.
                      The wait could succed, timeout, or fail with an error.

    Return type     : i32 - one of the values DWL_HW_WAIT_OK
                                              DWL_HW_WAIT_TIMEOUT
                                              DWL_HW_WAIT_ERROR

    Argument        : const void * instance - DWL instance
------------------------------------------------------------------------------*/
enum DWLRet DWLWaitHwReady(const void *instance, i32 core_id, u32 timeout) {
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;
  struct core_desc core;
  int ioctl_req = 0;
  i32 ret = DWL_HW_WAIT_OK;

  UNUSED(timeout);

#ifndef DWL_USE_DEC_IRQ
  int max_wait_time = 10000; /* 10s in ms */
#endif

  ASSERT(dec_dwl);

  DWL_DEBUG("%s %d\n", "DEC", core_id);

  core.id = core_id;
  core.regs = dwl_shadow_regs[core_id];
  core.size = dec_dwl->reg_size.size;

#ifdef DWL_USE_DEC_IRQ
#if 0
    ioctl_req = HANTRODEC_IOCX_DEC_WAIT;

    if (ioctl(dec_dwl->fd, ioctl_req, &core)) {
      DWL_DEBUG("ioctl HANTRODEC_IOCG_*_WAIT failed\n");
      ret = DWL_HW_WAIT_ERROR;
    }
#else
    sem_wait(dec_dwl->sync_params->sc_dec_rdy_sem + core_id);
#endif
#else /* Polling */

  ret = DWL_HW_WAIT_TIMEOUT;

  ioctl_req = (int)HANTRODEC_IOCS_DEC_READ_REG;
  core.reg_id = 1;

  do {
    u32 irq_stats;
    const unsigned int usec = 1000; /* 1 ms polling interval */

    /* Just read swreg[1] to check hw status */
    pthread_mutex_lock(&dec_dwl->shadow_mutex[core_id]);

    if (ioctl(dec_dwl->fd, ioctl_req, &core)) {
      pthread_mutex_unlock(&dec_dwl->shadow_mutex[core_id]);
      DWL_DEBUG("ioctl HANTRODEC_IOCS_*_PULL_REG failed\n", "");
      ret = DWL_HW_WAIT_ERROR;
      break;
    }

    irq_stats = dwl_shadow_regs[core_id][HANTRO_IRQ_STAT_DEC];
    pthread_mutex_unlock(&dec_dwl->shadow_mutex[core_id]);
    irq_stats = (irq_stats >> 11) & 0x1FFF;

    if(irq_stats != 0) {
      hw_enable[core_id] = 0;
#ifdef PERFORMANCE_TEST
      ActivityTraceStopDec(&dec_dwl->activity);
      hw_time_use = dec_dwl->activity.active_time / 100;
#endif
      ret = DWL_HW_WAIT_OK;
      ioctl_req = (int)HANTRODEC_IOCS_DEC_PULL_REG;
      pthread_mutex_lock(&dec_dwl->shadow_mutex[core_id]);

      if (ioctl(dec_dwl->fd, ioctl_req, &core)) {
        pthread_mutex_unlock(&dec_dwl->shadow_mutex[core_id]);
        DWL_DEBUG("%s", "ioctl HANTRODEC_IOCS_*_PULL_REG failed\n");
        ret = DWL_HW_WAIT_ERROR;
        break;
      }
      pthread_mutex_unlock(&(dec_dwl->shadow_mutex[core_id]));
      break;
    }

    usleep(usec);

    max_wait_time--;
  } while (max_wait_time > 0);

#endif

#ifdef _DWL_DEBUG
  {
    u32 irq_stats = dwl_shadow_regs[core_id][HANTRO_IRQ_STAT_DEC];

    PrintIrqType(dec_dwl->client_type == DWL_CLIENT_TYPE_PP ? 1 : 0, core_id, irq_stats);
  }
#endif

  DWL_DEBUG("%s %d done\n", "DEC", core_id);

  return ret;
}

/*------------------------------------------------------------------------------
    Function name   : DWLmalloc
    Description     : Allocate a memory block. Same functionality as
                      the ANSI C malloc()

    Return type     : void pointer to the allocated space, or NULL if there
                      is insufficient memory available

    Argument        : u32 n - Bytes to allocate
------------------------------------------------------------------------------*/
void *DWLmalloc(size_t n) {
  MEMTRACE_I("DWLmalloc\t%8d bytes\n", n);
  return malloc(n);
}

/*------------------------------------------------------------------------------
    Function name   : DWLfree
    Description     : Deallocates or frees a memory block. Same functionality as
                      the ANSI C free()

    Return type     : void

    Argument        : void *p - Previously allocated memory block to be freed
------------------------------------------------------------------------------*/
void DWLfree(void *p) {
  if(p != NULL)
    free(p);
}

/*------------------------------------------------------------------------------
    Function name   : DWLcalloc
    Description     : Allocates an array in memory with elements initialized
                      to 0. Same functionality as the ANSI C calloc()

    Return type     : void pointer to the allocated space, or NULL if there
                      is insufficient memory available

}
    Argument        : u32 n - Number of elements
    Argument        : u32 s - Length in bytes of each element.
------------------------------------------------------------------------------*/
void *DWLcalloc(size_t n, size_t s) {
  MEMTRACE_I("DWLcalloc\t%8d bytes\n", n * s);
  return calloc(n, s);
}

/*------------------------------------------------------------------------------
    Function name   : DWLmemcpy
    Description     : Copies characters between buffers. Same functionality as
                      the ANSI C memcpy()

    Return type     : The value of destination d

    Argument        : void *d - Destination buffer
    Argument        : const void *s - Buffer to copy from
    Argument        : u32 n - Number of bytes to copy
------------------------------------------------------------------------------*/
void *DWLmemcpy(void *d, const void *s, size_t n) {
  return memcpy(d, s, n);
}

/*------------------------------------------------------------------------------
    Function name   : DWLmemset
    Description     : Sets buffers to a specified character. Same functionality
                      as the ANSI C memset()

    Return type     : The value of destination d

    Argument        : void *d - Pointer to destination
    Argument        : i32 c - Character to set
    Argument        : u32 n - Number of characters
------------------------------------------------------------------------------*/
void *DWLmemset(void *d, i32 c, size_t n) {
  return memset(d, (int) c, n);
}

/*------------------------------------------------------------------------------
    Function name   : DWLInit
    Description     : Initialize a DWL instance

    Return type     : const void * - pointer to a DWL instance

    Argument        : void * param - not in use, application passes NULL
------------------------------------------------------------------------------*/
#ifdef _SYSTEM_MODEL_
u32 dwl_instance_num = 0;
#endif

const void *DWLInit(struct DWLInitParam * param) {
  struct HANTRODWL *dec_dwl;

  dec_dwl = (struct HANTRODWL *) DWLcalloc(1, sizeof(struct HANTRODWL));

  DWL_DEBUG("INITIALIZE\n", "");

  if(dec_dwl == NULL) {
    DWL_DEBUG("failed to alloc struct HANTRODWL struct\n", "");
    return NULL;
  }

  dec_dwl->client_type = param->client_type;
  dec_dwl->fd = -1;
  dec_dwl->fd_mem = -1;
  dec_dwl->fd_memalloc = -1;

  /* open the device */
  dec_dwl->fd = open(dec_dev, O_RDWR);
  if(dec_dwl->fd == -1) {
    DWL_DEBUG("failed to open '%s'\n", dec_dev);
    goto err;
  }

  /* Linear memories not needed in pp */
  if(dec_dwl->client_type != DWL_CLIENT_TYPE_PP) {
    /* open memalloc for linear memory allocation */
    dec_dwl->fd_memalloc = open(mem_dev, O_RDWR | O_SYNC);

    if(dec_dwl->fd_memalloc == -1) {
      DWL_DEBUG("failed to open: %s\n", mem_dev);
      goto err;
    }
  }

  dec_dwl->fd_mem = open("/dev/mem", O_RDWR | O_SYNC);

  if(dec_dwl->fd_mem == -1) {
    DWL_DEBUG("failed to open: %s\n", "/dev/mem");
    goto err;
  }

  switch (dec_dwl->client_type) {
  case DWL_CLIENT_TYPE_H264_DEC:
  case DWL_CLIENT_TYPE_MPEG4_DEC:
  case DWL_CLIENT_TYPE_JPEG_DEC:
  case DWL_CLIENT_TYPE_VC1_DEC:
  case DWL_CLIENT_TYPE_MPEG2_DEC:
  case DWL_CLIENT_TYPE_VP6_DEC:
  case DWL_CLIENT_TYPE_VP8_DEC:
  case DWL_CLIENT_TYPE_RV_DEC:
  case DWL_CLIENT_TYPE_AVS_DEC:
  case DWL_CLIENT_TYPE_PP: {
    break;
  }
  default: {
    DWL_DEBUG("Unknown client type no. %d\n", dec_dwl->client_type);
    goto err;
  }
  }

  if(ioctl(dec_dwl->fd, HANTRODEC_IOC_MC_CORES,  &dec_dwl->num_cores) == -1) {
    DWL_DEBUG("ioctl HANTRODEC_IOC_MC_CORES failed\n", "");
    goto err;
  }

  if(ioctl(dec_dwl->fd, HANTRODEC_IOCGHWIOSIZE, &dec_dwl->reg_size.size) == -1) {
    DWL_DEBUG("ioctl HANTRODEC_IOCGHWIOSIZE failed\n", "");
    goto err;
  }

  DWL_DEBUG("SUCCESS\n", "");

#ifdef _SYSTEM_MODEL_
  dwl_instance_num++;
#endif

  return dec_dwl;

err:

  DWL_DEBUG("FAILED\n", "");

  DWLRelease(dec_dwl);

  return NULL;
}

/*------------------------------------------------------------------------------
    Function name   : DWLRelease
    Description     : Release a DWl instance

    Return type     : i32 - 0 for success or a negative error code

    Argument        : const void * instance - instance to be released
------------------------------------------------------------------------------*/
enum DWLRet DWLRelease(const void *instance) {
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;

  ASSERT(dec_dwl != NULL);

  if(dec_dwl->fd_mem != -1)
    close(dec_dwl->fd_mem);

  if(dec_dwl->fd != -1) {
    extern int hantrodec_release(/*struct inode * */ int *inode, /*struct file * */ int filp);
#ifdef _SYSTEM_MODEL_
    dwl_instance_num--;
    if(dwl_instance_num == 0)
#endif
      hantrodec_release(NULL, dec_dwl->fd);
    close(dec_dwl->fd);
  }

  /* linear memory allocator */
  if(dec_dwl->fd_memalloc != -1)
    close(dec_dwl->fd_memalloc);

  free(dec_dwl);

  DWL_DEBUG("SUCCESS\n", "");

  return (DWL_OK);
}

/* HW locking */

/*------------------------------------------------------------------------------
    Function name   : DWLReserveHwPipe
    Description     :
    Return type     : i32
    Argument        : const void *instance
    Argument        : i32 *core_id - ID of the reserved HW core
------------------------------------------------------------------------------*/
i32 DWLReserveHwPipe(const void *instance, struct DWLReqInfo *info, i32 *core_id) {
  i32 ret;
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;

  ASSERT(dec_dwl != NULL);
  ASSERT(dec_dwl->client_type != DWL_CLIENT_TYPE_PP);

  DWL_DEBUG("Start\n", "");

  /* reserve decoder */
  *core_id = ioctl(dec_dwl->fd, HANTRODEC_IOCH_DEC_RESERVE,
                   dec_dwl->client_type);

  if (*core_id != 0) {
    return DWL_ERROR;
  }

  /* reserve PP */
  ret = ioctl(dec_dwl->fd, HANTRODEC_IOCQ_PP_RESERVE, 0);

  /* for pipeline we expect same core for both dec and PP */
  if (ret != *core_id) {
    /* release the decoder */
    ioctl(dec_dwl->fd, HANTRODEC_IOCT_DEC_RELEASE, core_id);
    return DWL_ERROR;
  }

  dec_dwl->b_ppreserved = 1;

  DWL_DEBUG("Reserved DEC+PP core %d\n", *core_id);

  return DWL_OK;
}

/*------------------------------------------------------------------------------
    Function name   : DWLReserveHw
    Description     :
    Return type     : i32
    Argument        : const void *instance
    Argument        : i32 *core_id - ID of the reserved HW core
------------------------------------------------------------------------------*/
enum DWLRet DWLReserveHw(const void *instance, struct DWLReqInfo *info, i32 *core_id) {
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;
  int is_pp;

  ASSERT(dec_dwl != NULL);

  is_pp = dec_dwl->client_type == DWL_CLIENT_TYPE_PP ? 1 : 0;

  DWL_DEBUG(" %s\n", is_pp ? "PP" : "DEC");

  if (is_pp) {
    *core_id = ioctl(dec_dwl->fd, HANTRODEC_IOCQ_PP_RESERVE, 0);

    /* PP is single core so we expect a zero return value */
    if (*core_id != 0) {
      return DWL_ERROR;
    }
  } else {
    *core_id = ioctl(dec_dwl->fd, HANTRODEC_IOCH_DEC_RESERVE,
                     dec_dwl->client_type);
  }

  /* negative value signals an error */
  if (*core_id < 0) {
    DWL_DEBUG("ioctl HANTRODEC_IOCS_%s_RESERVE failed\n",
              is_pp ? "PP" : "DEC");
    return DWL_ERROR;
  }

  DWL_DEBUG("Reserved %s core %d\n", is_pp ? "PP" : "DEC", *core_id);

  return DWL_OK;
}

/*------------------------------------------------------------------------------
    Function name   : DWLReleaseHw
    Description     :
    Return type     : void
    Argument        : const void *instance
------------------------------------------------------------------------------*/
enum DWLRet DWLReleaseHw(const void *instance, i32 core_id) {
  struct HANTRODWL *dec_dwl = (struct HANTRODWL *) instance;
  int is_pp;

  ASSERT((u32)core_id < dec_dwl->num_cores);
  ASSERT(dec_dwl != NULL);

  is_pp = dec_dwl->client_type == DWL_CLIENT_TYPE_PP ? 1 : 0;

  if ((u32) core_id >= dec_dwl->num_cores)
    return 0;

  DWL_DEBUG(" %s core %d\n", is_pp ? "PP" : "DEC", core_id);

  if (is_pp) {
    ASSERT(core_id == 0);

    ioctl(dec_dwl->fd, HANTRODEC_IOCT_PP_RELEASE, core_id);
  } else {
    if (dec_dwl->b_ppreserved) {
      /* decoder has reserved PP also => release it */
      DWL_DEBUG("DEC released PP core %d\n", core_id);

      dec_dwl->b_ppreserved = 0;

      ASSERT(core_id == 0);

      ioctl(dec_dwl->fd, HANTRODEC_IOCT_PP_RELEASE, core_id);
    }

    ioctl(dec_dwl->fd, HANTRODEC_IOCT_DEC_RELEASE, core_id);
  }
  return 0;
}

void DWLSetIRQCallback(const void *instance, i32 core_id,
                       DWLIRQCallbackFn *callback_fn, void* arg) {
  /* not in use with single core only control code */
  UNUSED(instance);
  UNUSED(core_id);
  UNUSED(callback_fn);
  UNUSED(arg);

  //ASSERT(0);
}



/*------------------------------------------------------------------------------
    Function name   : DWLFakeTimeout
    Description     : Testing help function that changes HW stream errors info
                        HW timeouts. You can check how the SW behaves or not.
    Return type     : void
    Argument        : void
------------------------------------------------------------------------------*/

#ifdef _DWL_FAKE_HW_TIMEOUT
void DWLFakeTimeout(u32 * status) {

  if((*status) & DEC_IRQ_ERROR) {
    *status &= ~DEC_IRQ_ERROR;
    *status |= DEC_IRQ_TIMEOUT;
    printf("\nDwl: Change stream error to hw timeout\n");
  }
}
#endif

/*------------------------------------------------------------------------------
    Function name   : DWLReadPpConfigure
    Description     : Read the pp configure
    Return type     : void
    Argument        : const void * instance - DWL instance
    Argument        : PpUnitIntConfig *ppu_cfg
------------------------------------------------------------------------------*/
void DWLReadPpConfigure(const void *instance, u32 core_id, void *ppu_cfg, u32 pjpeg_coeff_buffer_size)
{
    struct HANTRODWL *dec_dwl = (struct HANTRODWL *)instance;
    if (dec_dwl->client_type == DWL_CLIENT_TYPE_JPEG_DEC) {
      dec_dwl->pjpeg_coeff_buffer_size[core_id] = pjpeg_coeff_buffer_size;
    }
    DWLmemcpy(dec_dwl->ppu_cfg[core_id], ppu_cfg, DEC_MAX_PPU_COUNT*sizeof(PpUnitIntConfig));
}

void DWLReadMcRefBuffer(const void *instance, u32 core_id, u64 buf_size, u32 dpb_size) {
    struct HANTRODWL *dec_dwl = (struct HANTRODWL *)instance;
    dec_dwl->buf_size[core_id] = buf_size;
    UNUSED(dpb_size);
}

enum DWLRet DWLReserveCmdBuf(const void *instance, struct DWLReqInfo *info, u32 *cmd_buf_id) {
  UNUSED(instance);
  UNUSED(info);
  UNUSED(cmd_buf_id);
  return 0;
}

enum DWLRet DWLFlushRegister(const void *instance, u32 cmd_buf_id, u32 *dec_regs, u32 *mc_fresh_regs, u32 mc_buf_id, const void *owner)
{
  UNUSED(instance);
  UNUSED(cmd_buf_id);
  UNUSED(dec_regs);
  UNUSED(mc_fresh_regs);
  UNUSED(mc_buf_id);
  UNUSED(owner);
  return 0;
}

enum DWLRet DWLRefreshRegister(const void *instance, u32 cmd_buf_id, u32 *dec_regs)
{
  UNUSED(instance);
  UNUSED(cmd_buf_id);
  UNUSED(dec_regs);
  return 0;
}

void DWLCmdPushSliceRegs(const void *instance, u32 cmd_buf_id, u32 *regs) {
  UNUSED(instance);
  UNUSED(cmd_buf_id);
  UNUSED(regs);
}

enum DWLRet DWLVcmdMCRefreshStatusRegs(const void *instance, u32 *dec_regs, u32 cmdbuf_id)
{
  UNUSED(instance);
  UNUSED(dec_regs);
  UNUSED(cmdbuf_id);
  return 0;
}

i32 DWLGetVcmdMCVirtualCoreId(const void *instance, u32 cmdbuf_id)
{
  UNUSED(instance);
  UNUSED(cmdbuf_id);
  return 0;
}

/* Reserve one valid command buffer. */
enum DWLRet DWLEnableCmdBuf(const void *instance, u32 cmd_buf_id) {
  UNUSED(instance);
  UNUSED(cmd_buf_id);
  return 0;
}

/* Wait cmd buffer ready. Used only in single core decoding. */
enum DWLRet DWLWaitCmdBufReady(const void *instance, u16 cmd_buf_id) {
  UNUSED(instance);
  UNUSED(cmd_buf_id);
  return 0;
}

/* Reserve one valid command buffer. */
enum DWLRet DWLReleaseCmdBuf(const void *instance, u32 cmd_buf_id) {
  UNUSED(instance);
  UNUSED(cmd_buf_id);
  return 0;
}

enum DWLRet DWLWaitCmdbufsDone(const void *instance, const void *owner) {
  UNUSED(instance);
  UNUSED(owner);
  return 0;
}

u32 DWLVcmdIsUsed(void) {
  return 0;
}

/**@brief DMA data transfer between host memory and device memory. \n
 * function will copy the data from host memory to device memory
 *  after SW process the data in that host memory and
 *  copy the data from device memory to host memory
 *  after HW process the data in that device memory.
 * @param[in,out]    device_bus_addr             device memory address
 * @param[in,out]    host_virtual_addr           host memory address
 * @param[in]        length                      copy data length(byte)
 * @param[in]        dir                         DMA transfer direction
 *                                               -HOST_TO_DEVICE
 *                                               -DEVICE_TO_HOST
*/
void DWLDMATransData(addr_t device_bus_addr, void *host_virtual_addr,
                     u32 length, enum DWLDMADirection dir) {

  if (device_bus_addr == 0 || host_virtual_addr == NULL)
    return;

  if ((u8 *)device_bus_addr == (u8 *)host_virtual_addr)
    return;

  if (length <= 0 || (dir != HOST_TO_DEVICE && dir != DEVICE_TO_HOST))
    return;

  /* Customer implement their own DMA data transfer function here. */
  if (dir == HOST_TO_DEVICE) {
    DWLmemcpy((u8 *)device_bus_addr, (u8 *)host_virtual_addr, length);
  } else if (dir == DEVICE_TO_HOST) {
    DWLmemcpy((u8 *)host_virtual_addr, (u8 *)device_bus_addr, length);
  }

}

#ifdef ASIC_TRACE_SUPPORT
void DWLSetSimMc(const void *instance) {
  return;
}
#endif
