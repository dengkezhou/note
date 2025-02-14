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

#ifndef REGDRV_H
#define REGDRV_H

#include "basetype.h"
#include "assert.h"

#define DEC_HW_ALIGN_MASK 0x0F
#define DEC_IRQ_DISABLE 0x10
#define DEC_ABORT 0x20

#define DEC_HW_IRQ_ABORT 0x01
#define DEC_HW_IRQ_RDY 0x02
#define DEC_HW_IRQ_BUS 0x04
#define DEC_HW_IRQ_BUFFER 0x08
#define DEC_HW_IRQ_ASO 0x10
#define DEC_HW_IRQ_ERROR 0x20
#define DEC_HW_IRQ_SLICE 0x40
#define DEC_HW_IRQ_TIMEOUT 0x80
#define DEC_HW_IRQ_EXT_TIMEOUT 0x400
#define DEC_HW_IRQ_SCAN_RDY 0x4000

/* dec mode */
#define DEC_MODE_H264      0
#define DEC_MODE_MPEG4     1
#define DEC_MODE_H263      2
#define DEC_MODE_JPEG      3
#define DEC_MODE_VC1       4
#define DEC_MODE_MPEG2     5
#define DEC_MODE_MPEG1     6
#define DEC_MODE_VP6       7
#define DEC_MODE_RV        8
#define DEC_MODE_VP7       9
#define DEC_MODE_VP8       10
#define DEC_MODE_AVS       11
#define DEC_MODE_HEVC      12
#define DEC_MODE_VP9       13
#define DEC_MODE_H264_H10P 15
#define DEC_MODE_AVS2      16
#define DEC_MODE_AV1       17
#define DEC_MODE_VVC       18

#define PP_REG_START                60

enum HwIfName {
  /* include script-generated part */
#include "8170enum.h"
  HWIF_DEC_IRQ_STAT,
  HWIF_LAST_REG,

  /* aliases */
  HWIF_MPEG4_DC_BASE_LSB = HWIF_I4X4_OR_DC_BASE_LSB,
  HWIF_MPEG4_DC_BASE_MSB = HWIF_I4X4_OR_DC_BASE_MSB,
  HWIF_INTRA_4X4_BASE_LSB = HWIF_I4X4_OR_DC_BASE_LSB,
  HWIF_INTRA_4X4_BASE_MSB = HWIF_I4X4_OR_DC_BASE_MSB,
  HWIF_DEC_ERROR_CODE = HWIF_ERROR_INFO, /* for vc8000d av1 */
  /* VP6 */
  HWIF_VP6HWGOLDEN_BASE_LSB = HWIF_REFER4_BASE_LSB,
  HWIF_VP6HWGOLDEN_BASE_MSB = HWIF_REFER4_BASE_MSB,
  HWIF_VP6HWPART1_BASE_LSB = HWIF_REFER13_BASE_LSB,
  HWIF_VP6HWPART1_BASE_MSB = HWIF_REFER13_BASE_MSB,
  HWIF_VP6HWPART2_BASE_LSB = HWIF_RLC_VLC_BASE_LSB,
  HWIF_VP6HWPART2_BASE_MSB = HWIF_RLC_VLC_BASE_MSB,
  HWIF_VP6HWPROBTBL_BASE_LSB = HWIF_QTABLE_BASE_LSB,
  HWIF_VP6HWPROBTBL_BASE_MSB = HWIF_QTABLE_BASE_MSB,
  /* progressive JPEG */
  HWIF_PJPEG_COEFF_BUF_LSB = HWIF_DIR_MV_BASE_LSB,
  HWIF_PJPEG_COEFF_BUF_MSB = HWIF_DIR_MV_BASE_MSB,

  /* MVC */
  HWIF_INTER_VIEW_BASE_LSB = HWIF_REFER15_BASE_LSB,
  HWIF_INTER_VIEW_BASE_MSB = HWIF_REFER15_BASE_MSB,
  HWIF_INTER_VIEW_CBASE_LSB = HWIF_REFER15_CBASE_LSB,
  HWIF_INTER_VIEW_CBASE_MSB = HWIF_REFER15_CBASE_MSB,
  HWIF_INTER_VIEW_DBASE_LSB = HWIF_REFER15_DBASE_LSB,
  HWIF_INTER_VIEW_DBASE_MSB = HWIF_REFER15_DBASE_MSB,
  HWIF_INTER_VIEW_TYBASE_LSB = HWIF_REFER15_TYBASE_LSB,
  HWIF_INTER_VIEW_TYBASE_MSB = HWIF_REFER15_TYBASE_MSB,
  HWIF_INTER_VIEW_TCBASE_LSB = HWIF_REFER15_TCBASE_LSB,
  HWIF_INTER_VIEW_TCBASE_MSB = HWIF_REFER15_TCBASE_MSB,

  /* PP */
  /* Make sure to update HWIF_PPX_END to the last register of PP unit when there
     is any updating to PP unit register definition. */
  HWIF_PPX_START = HWIF_PPX_OUT_SWAP_U,
  HWIF_PPX_END = HWIF_PPX_CROP2_OUT_HEIGHT_U,

  /* stream length info for ddr_low_latency model */
  HWIF_LG_STREAM_STATUS_BASE_LSB = HWIF_STREAM_STATUS_BASE_LSB,
  HWIF_LG_STREAM_STATUS_BASE_MSB = HWIF_STREAM_STATUS_BASE_MSB
};

/* { SWREG, BITS, POSITION, WRITABLE } */
extern u32 hw_dec_reg_spec[HWIF_LAST_REG + 1][4];

/*------------------------------------------------------------------------------
    Data types
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Function prototypes
------------------------------------------------------------------------------*/

void SetDecRegister(u32* reg_base, u32 id, u32 value);
u32 GetDecRegister(const u32* reg_base, u32 id);
void FlushDecRegisters(const void* dwl, i32 core_id, u32* regs, u32 ppu_count);
void RefreshDecRegisters(const void* dwl, i32 core_id, u32* regs, u32 ppu_count);
void SetPpuRegister(u32 *pp_reg_base, u32 id, int ppu_index, u32 value);
u32 GetPpuRegister(const u32 *pp_reg_base, u32 id, int ppu_index);

#if 0
/* For legacy release compatible */
#define SET_G1_DEC_REGISTER(reg_base, id, value) do { \
  if ((reg_base)[0] >> 16 == 0x6731)  \
    SetDecRegister((reg_base), id##_G1, (value)); \
  else \
    SetDecRegister((reg_base), id, (value));  \
  } while (0)

#define SET_G2_DEC_REGISTER(reg_base, id, value) do { \
  if ((reg_base)[0] >> 16 == 0x6732)  \
    SetDecRegister((reg_base), id##_G2, (value)); \
  else \
    SetDecRegister((reg_base), id, (value));  \
  } while (0)
#endif

#ifndef MODEL_SIMULATION
/* G1&G2 */
#define SET_ADDR_REG(reg_base, REGBASE, addr) do {\
    SetDecRegister((reg_base), REGBASE##_LSB, (u32)(addr));  \
    if (hw_feature->addr64_support) { \
      if(sizeof(addr_t) == 4) \
        SetDecRegister((reg_base), REGBASE##_MSB, 0); \
      else \
        SetDecRegister((reg_base), REGBASE##_MSB, (u32)((u64)(addr) >> 32)); \
    } else { \
      if(sizeof(addr_t) == 8) \
        ASSERT(((u32)((u64)(addr) >> 32)) == 0); \
    } \
  } while (0)

/* for both G1&G2 */
#define SET_ADDR_REG2(reg_base, lsb, msb, addr) do {\
    SetDecRegister((reg_base), (lsb), (u32)(addr));  \
    if (hw_feature->addr64_support) { \
      SetDecRegister((reg_base), (msb), (u32)((u64)(addr) >> 32)); \
    } else { \
      ASSERT((u32)((u64)(addr) >> 32) == 0); \
      SetDecRegister((reg_base), (msb), 0); \
    } \
  } while (0)

/* only used in cmodel */
#define SET_ADDR_REG3(reg_base, REGBASE, addr, addr64_support) do {\
    SetDecRegister((reg_base), REGBASE##_LSB, (u32)(addr));  \
    if (addr64_support) { \
      if(sizeof(addr_t) == 4) \
        SetDecRegister((reg_base), REGBASE##_MSB, 0); \
      else \
        SetDecRegister((reg_base), REGBASE##_MSB, (u32)((u64)(addr) >> 32)); \
    } else { \
      if(sizeof(addr_t) == 8) \
        ASSERT(((u32)((u64)(addr) >> 32)) == 0); \
    } \
  } while (0)

#define SET_PP_ADDR_REG(reg_base, REGBASE, addr) do {\
    SetDecRegister((reg_base), REGBASE, (u32)(addr));  \
    if (hw_feature->addr64_support) { \
      SetDecRegister((reg_base), REGBASE##_MSB, (u32)((u64)(addr) >> 32)); \
    } else { \
      assert((u32)((u64)(addr) >> 32) == 0); \
    } \
  } while (0)

#define SET_PP_ADDR_REG2(reg_base, lsb, msb, i, addr) do {\
    SetPpuRegister((reg_base), (lsb), (i), (u32)(addr));  \
    if (hw_feature->addr64_support) { \
      SetPpuRegister((reg_base), (msb), (i), (u32)((u64)(addr) >> 32)); \
    } else { \
      assert((u32)((u64)(addr) >> 32) == 0); \
      SetPpuRegister((reg_base), (msb), (i), 0); \
    } \
  } while (0)

#define SET_ADDR64_REG(reg_base, REGBASE, addr) do {\
    SetDecRegister((reg_base), REGBASE##_LSB, (u32)(addr));  \
    if (hw_feature->addr64_support) { \
      SetDecRegister((reg_base), REGBASE##_MSB, (u32)((addr_t)(addr) >> 32)); \
    } else { \
      assert((u32)((addr_t)(addr) >> 32) == 0); \
      SetDecRegister((reg_base), REGBASE##_MSB, 0); \
    } \
  } while (0)

#else
#ifdef VDK_STRICT_TEST
#define ENCRYP_CODE (0xbeef)
#else
#define ENCRYP_CODE (0)
#endif
/* MODEL simulation: always set both MSB/LSB base registers. */
#define SET_ADDR_REG(reg_base, REGBASE, addr) do {\
    assert((((u64)addr) & 0xf) == 0);  \
    SetDecRegister((reg_base), REGBASE##_LSB, (u32)(addr));  \
    if (sizeof(addr_t) == 4) {\
      SetDecRegister((reg_base), REGBASE##_MSB, 0); \
    } else {\
      if ((addr) != 0) {\
        SetDecRegister((reg_base), REGBASE##_MSB, (u32)((u64)(addr) >> 32) ^ ENCRYP_CODE); \
      } else {\
        SetDecRegister((reg_base), REGBASE##_MSB, 0); \
      } \
    } \
  } while (0)

/* for both G1&G2 */
#define SET_ADDR_REG2(reg_base, lsb, msb, addr) do {\
    assert((((u64)addr) & 0xf) == 0);  \
    SetDecRegister((reg_base), (lsb), (u32)(addr));  \
    if (sizeof(addr_t) == 4) {\
      SetDecRegister((reg_base), (msb), 0); \
    } else { \
      if ((addr) != 0) {\
        SetDecRegister((reg_base), (msb), (u32)((u64)(addr) >> 32) ^ ENCRYP_CODE); \
      } else {\
        SetDecRegister((reg_base), (msb), 0); \
      } \
    } \
  } while (0)

/* only used in cmodel */
#define SET_ADDR_REG3(reg_base, REGBASE, addr, addr64_support) do {\
    SetDecRegister((reg_base), REGBASE##_LSB, (u32)(addr));  \
    if (sizeof(addr_t) == 4) \
      SetDecRegister((reg_base), REGBASE##_MSB, 0); \
    else \
      SetDecRegister((reg_base), REGBASE##_MSB, (u32)((u64)(addr) >> 32)); \
  } while (0)

#define SET_PP_ADDR_REG(reg_base, REGBASE, addr) do {\
    SetDecRegister((reg_base), REGBASE, (u32)(addr));  \
    if (sizeof(addr_t) == 4) { \
      SetDecRegister((reg_base), REGBASE##_MSB, 0); \
    } else { \
      if ((addr) != 0) {\
        SetDecRegister((reg_base), REGBASE##_MSB, (u32)((u64)(addr) >> 32) ^ ENCRYP_CODE); \
      } else {\
        SetDecRegister((reg_base), REGBASE##_MSB, 0); \
      } \
    } \
  } while (0)

#define SET_PP_ADDR_REG2(reg_base, lsb, msb, i, addr) do {\
    SetPpuRegister((reg_base), (lsb), (i), (u32)(addr));  \
    if (sizeof(addr_t) == 4) { \
      SetPpuRegister((reg_base), (msb), (i), 0); \
    } else { \
      if ((addr) != 0) {\
        SetPpuRegister((reg_base), (msb), (i), (u32)((u64)(addr) >> 32) ^ ENCRYP_CODE); \
      } else {\
        SetPpuRegister((reg_base), (msb), (i), 0); \
      } \
    } \
  } while (0)

#define SET_ADDR64_REG(reg_base, REGBASE, addr) do {\
    SetDecRegister((reg_base), REGBASE##_LSB, (u32)(addr));  \
    if (sizeof(addr_t) == 4) { \
      SetDecRegister((reg_base), REGBASE##_MSB, 0); \
    } else { \
      if ((addr) != 0) {\
        SetDecRegister((reg_base), REGBASE##_MSB, (u32)((addr_t)(addr) >> 32) ^ ENCRYP_CODE); \
      } else {\
        SetDecRegister((reg_base), REGBASE##_MSB, 0); \
      } \
    } \
  } while (0)

#endif

#define GET_ADDR_REG(reg_base, REGBASE)  \
    (sizeof(addr_t) == 8 ? \
    (((addr_t)GetDecRegister((reg_base), REGBASE##_LSB)) |  \
    (((addr_t)GetDecRegister((reg_base), REGBASE##_MSB)) << 32)) \
    :(GetDecRegister((reg_base), REGBASE##_LSB)))

#define GET_ADDR_REG2(reg_base, lsb, msb)  \
    (sizeof(addr_t) == 8 ? \
    (((addr_t)GetDecRegister((reg_base), (lsb))) |  \
    (((addr_t)GetDecRegister((reg_base), (msb))) << 32)) \
    : (GetDecRegister((reg_base), (lsb))))

#define GET_PP_ADDR_REG(reg_base, REGBASE)  \
    (sizeof(addr_t) == 8 ? \
    (((addr_t)GetPpRegister((reg_base), REGBASE)) |  \
    (((addr_t)GetPpRegister((reg_base), REGBASE##_MSB)) << 32)) \
    : (GetDecRegister((reg_base), REGBASE)))

#define GET_PP_ADDR64_REG(reg_base, REGBASE, i)  \
      (sizeof(addr_t) == 8 ? \
      (((addr_t)GetPpuRegister((reg_base), REGBASE##_LSB, (i))) |  \
      (((addr_t)GetPpuRegister((reg_base), REGBASE##_MSB, (i))) << 32)) \
      :(GetPpuRegister((reg_base), REGBASE##_LSB, (i))))

#define GET_PP_ADDR_REG2(reg_base, lsb, msb, i)  \
    (sizeof(addr_t) == 8 ? \
    (((addr_t)GetPpuRegister((reg_base), (lsb), (i))) |  \
    (((addr_t)GetPpuRegister((reg_base), (msb), (i))) << 32)) \
    :(GetPpuRegister((reg_base), (lsb), (i))))


#define GET_ADDR64_REG(reg_base, REGBASE)  \
  (sizeof(addr_t) == 8 ? \
  (((addr_t)GetDecRegister((reg_base), REGBASE##_LSB)) |  \
  (((addr_t)GetDecRegister((reg_base), REGBASE##_MSB)) << 32)) \
  :(GetDecRegister((reg_base), REGBASE##_LSB)))


#endif /* #ifndef REGDRV_H */
