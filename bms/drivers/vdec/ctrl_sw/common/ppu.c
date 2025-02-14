/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
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

#include "deccfg.h"
#include "ppu.h"
#include "regdrv.h"
#include "commonconfig.h"
#include "sw_util.h"
#include "sw_debug.h"
#include "dec_log.h"
#include "parselogmsg.h"
#include "memalloc.h"


#define PP_MAX_STRIDE 65536
#define DOWN_SCALE_SIZE(w, ds) (((w)/(ds)) & ~0x1)
#define TOFIX(d, q) ((u64)( (d) * ((u64)1<<(q)) ))
#define FDIVI(a, b) ((a)/(b))
#define ABS(a) (((a) < 0) ? -(a) : (a))
#define JPEG 3
#define COEFF_WIDTH 3


static const u32 coeff[6][5] = {{16384,22970,11700,5638,29032},
                                {19077,26149,13320,6419,33050},
                                {16384,25802,7670,3069,30402},
                                {19077,29372,8731,3494,34610},
                                {16384,24160,9361,2696,30825},
                                {19077,27504,10646,3069,35091}};


static double nResult(double x, double n) {
  return (n == 1) ? x : nResult(x, n - 1) * x / n;
}


static double my_sin(double x) {
  u32 i = 1;
  double result = 0, n = 0;
  while(ABS(n = nResult(x, 2 * i - 1)) > 1e-7) {
    result += (i%2 == 1) ? n : -n;
    i++;
  }
  return result;
}

static u32 stride_unit[] = {1, 2, 4, 8, 16, 3, 64};

static enum StrideUnit AdjustStrideUnit(u32 ystride, u32 cstride) {
  enum StrideUnit unit;
  for (unit = STRIDE_UNIT_1B; unit < STRIDE_UNIT_NOT_SUPPORTED; unit++) {
    if (ystride % stride_unit[unit] == 0 &&
        ystride/stride_unit[unit] < PP_MAX_STRIDE &&
        cstride % stride_unit[unit] == 0 &&
        cstride/stride_unit[unit] < PP_MAX_STRIDE) {
      break;
    }
  }
  return unit;
}

static void CalOutTableIndex(u32 table_in_index, u32 coeff_in_index, u32 filter_size,
                             u32* table_out_index, u32* coeff_out_index) {
#ifdef USE_COEFF_MIRROR
  if (table_in_index <= 16) {
    *table_out_index = table_in_index;
    *coeff_out_index = coeff_in_index;
  } else {
    *table_out_index = 32 - table_in_index;
    *coeff_out_index = filter_size - 1 - coeff_in_index;
  }
#else
  *table_out_index = table_in_index;
  *coeff_out_index = coeff_in_index;
#endif
}

static double getSplineCoeff(double a, double b, double c,
                             double d, double dist) {
  if (dist <= 1.0)
    return ((d * dist + c) * dist + b) * dist + a;
  else
    return getSplineCoeff(0.0, b + 2.0 * c + 3.0 * d,
                          c + 3.0 * d,
                          -b - 3.0 * c - 6.0 * d,
                          dist - 1.0);
}

static void CheckLanFilterSize(PpUnitIntConfig *ppu_cfg, u32 *x_flag, u32 *y_flag) {
  u32 j = 0;
  i32 xDstInSrc, yDstInSrc;
  i32 scale_ratio_x_inv, scale_ratio_y_inv;
  i32 start_pos[5] = {0, 0, 0, 0, 0};
  i32 end_pos[5] = {0, 0, 0, 0, 0};
  i32 pos, x_pos, y_pos;
  *x_flag = *y_flag = 0;
  /* horizontal*/
  scale_ratio_x_inv = FDIVI(TOFIX(ppu_cfg->crop.width, 16) + ppu_cfg->scale.width / 2, ppu_cfg->scale.width);
  if (scale_ratio_x_inv % 2) scale_ratio_x_inv++;
  if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
    xDstInSrc = scale_ratio_x_inv - 65536;
  } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
    xDstInSrc = 0;
  } else {
    xDstInSrc = scale_ratio_x_inv;
  }
  pos = xDstInSrc / 2 - scale_ratio_x_inv;
  x_pos = 0;
  if (ppu_cfg->crop.width > ppu_cfg->scale.width) {
    for (j = 0; j < ppu_cfg->scale.width; j++) {
      pos += scale_ratio_x_inv;
      x_pos = FLOOR(pos+32768);
      start_pos[j % 5] = x_pos - ppu_cfg->x_filter_size/2;
      end_pos[j % 5] = x_pos + ppu_cfg->x_filter_size/2;
      if ((j >= 4) && (start_pos[j % 5] < end_pos[(j + 1) % 5])) {
        *x_flag = 1;
        break;
      }
    }
  }
  //when filter_size = 8 * n + 1, HW performace will drop heavy, convert to 8 * n - 1
  if ((ppu_cfg->x_filter_size / 8) && (ppu_cfg->x_filter_size % 8) == 1)
    *x_flag = 1;
  /*vertical*/
  for (j = 0; j < 5; j++) {
    start_pos[j] = end_pos[j] = 0;
  }
  scale_ratio_y_inv = FDIVI(TOFIX(ppu_cfg->crop.height, 16) + ppu_cfg->scale.height / 2, ppu_cfg->scale.height);
  if (scale_ratio_y_inv % 2) scale_ratio_y_inv++;
  if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
    yDstInSrc = scale_ratio_y_inv - 65536;
  } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
    yDstInSrc = 0;
  } else {
    yDstInSrc = scale_ratio_y_inv;
  }
  pos = yDstInSrc / 2 - scale_ratio_y_inv;
  y_pos = 0;
  if (ppu_cfg->crop.height > ppu_cfg->scale.height) {
    for (j = 0; j<ppu_cfg->scale.height; j++) {
      pos += scale_ratio_y_inv;
      y_pos = FLOOR(pos+32768);
      start_pos[j % 5] = y_pos - ppu_cfg->y_filter_size/2;
      end_pos[j % 5] = y_pos + ppu_cfg->y_filter_size/2;
      if ((j >= 4) && (start_pos[j % 5] < end_pos[(j + 1) % 5])) {
        *y_flag = 1;
        break;
      }
    }
  }
  if ((ppu_cfg->y_filter_size / 8) && (ppu_cfg->y_filter_size % 8) == 1)
    *y_flag = 1;
}

void InitPpUnitBoundCoeff(const struct DecHwFeatures *hw_feature,
                                  u32 field_pic,
                                  PpUnitIntConfig *ppu_cfg) {
  u32 i = 0, j;
  i32 k;
  i32 yDstInSrc, scale_ratio_y_inv;
  i32 start_pos, end_pos, table_index;
  i32 pos, y_pos;
  u32 start_count, end_count;
  u32 out_index, coeff_index;
  i16 value;
  i16 *table_data;
  u32 shift = field_pic ? 2 : 1;
  u32 phase_repet_num = (1 << (4 - ppu_cfg->y_phase_num));
  i16 start_value[2]={0,0};
  i16 end_value[2]={0,0};
  i16 chroma_end_value[2]={0,0};
  u32 y_filter_stride;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
    if (i >= hw_feature->max_ppu_count)
      ppu_cfg->enabled = 0;
    if (!ppu_cfg->enabled) continue;
    if (ppu_cfg->lanczos_table.virtual_address) {
      table_data = (i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + Y_COEFF_OFFSET + 16;
      scale_ratio_y_inv = FDIVI(TOFIX(ppu_cfg->crop.height, 16) + ppu_cfg->scale.height / 2, ppu_cfg->scale.height);
      if (scale_ratio_y_inv % 2) scale_ratio_y_inv++;
      if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
        yDstInSrc = scale_ratio_y_inv - 65536;
      } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
        yDstInSrc = 0;
      } else {
        yDstInSrc = scale_ratio_y_inv;
      }
      pos = yDstInSrc / 2 - scale_ratio_y_inv;
      y_pos = 0;
      start_count = 0;
      end_count = 0;
      phase_repet_num = (1 << (4 - ppu_cfg->y_phase_num));
      if (ppu_cfg->crop.height > ppu_cfg->scale.height)
        y_filter_stride = NEXT_MULTIPLE((ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), 8);
      else
        y_filter_stride = 8;
      if (ppu_cfg->scale.height < ppu_cfg->crop.height) {
        for (j = 0; j< ppu_cfg->scale.height / shift; j++) {
          pos += scale_ratio_y_inv;
          y_pos = FLOOR(pos+32768);
          start_pos = y_pos - (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          end_pos = y_pos + (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          table_index = ((pos+32768 - MAKE_FIXED_UNI(y_pos)) >> (FIXED_BITS_UNI-TABLE_LENGTH));
          value = 0;
          if (start_pos < 0) {
            for (k = start_pos; k <= 0; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
            }
            start_value[start_count++] = value;
          } else {
            if (start_count < 2) {
              CalOutTableIndex(table_index, 0, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
              start_value[start_count++] = value;
            }
          }
          value = 0;
          if (end_pos >= ppu_cfg->crop.height / shift) {
            for (k = ppu_cfg->crop.height / shift - 1; k <= end_pos; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
            }
            end_value[end_count++] = value;
          }
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = start_value[j];
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = end_value[j];
        }
      }
      /*chroma*/
      if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
        yDstInSrc = scale_ratio_y_inv - 65536;
      } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
        yDstInSrc = 0;
      } else {
        yDstInSrc = scale_ratio_y_inv;
      }
      pos = yDstInSrc / 2 - scale_ratio_y_inv;
      y_pos = 0;
      end_count = 0;
      if (ppu_cfg->scale.height < ppu_cfg->crop.height) {
        for (j = 0; j<ppu_cfg->scale.height / 2 / shift; j++) {
          pos += scale_ratio_y_inv;
          y_pos = FLOOR(pos+32768);
          start_pos = y_pos - (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          end_pos = y_pos + (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          table_index = ((pos+32768 - MAKE_FIXED_UNI(y_pos)) >> (FIXED_BITS_UNI-TABLE_LENGTH));
          value = 0;
          if (end_pos >= ppu_cfg->crop.height / 2 / shift) {
            for (k = ppu_cfg->crop.height / 2 / shift - 1; k <= end_pos; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
            }
            chroma_end_value[end_count++] = value;
          }
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = chroma_end_value[j];
        }
      }
    }
#ifdef SUPPORT_DMA
    u32 n_cores = ppu_cfg->lanczos_table.size / LANCZOS_COEFF_BUFFER_SIZE / sizeof(i16);
    for (j = 0; j < n_cores; j++) {
      DWLDMATransData((addr_t)(ppu_cfg->lanczos_table.bus_address +
                               j * LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16)),
                      (void *)((u8 *)ppu_cfg->lanczos_table.virtual_address +
                               j * LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16)),
                      LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16), HOST_TO_DEVICE);
    }
#endif
  }
}

static void InitPpUnitLanczosData(const struct DecHwFeatures *hw_feature,
                                  PpUnitIntConfig *ppu_cfg) {
  u32 i = 0, j, m;
  i32 k;
  i32 xDstInSrc, yDstInSrc;
  i32 scale_ratio_x_inv, scale_ratio_y_inv;
  i32 start_pos, end_pos, table_index;
  i32 pos, x_pos, y_pos;
  u32 start_count, end_count;
  u32 out_index, coeff_index;
  i32 total;
  i16 value;
  u32 shift_bit = hw_feature->pp_area_optimize ? 10 : 7;
  u32 least_coeff = (1 << shift_bit);
  u32 x_flag = 0;
  u32 y_flag = 0;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
    if (i >= hw_feature->max_ppu_count)
      ppu_cfg->enabled = 0;
    if (!ppu_cfg->enabled) continue;
    if (ppu_cfg->lanczos_table.virtual_address) {
      u32 x_filter_size, y_filter_size;
      u32 base_x_filter_size, base_y_filter_size;
      u32 x_filter_stride, y_filter_stride;
      u32 x_coeff_base, y_coeff_base;
      if (ppu_cfg->crop.width > ppu_cfg->scale.width) {
        if (ppu_cfg->pp_filter == PP_VSI_LINEAR) {
          x_filter_size = 2 * ((ppu_cfg->crop.width) / ppu_cfg->scale.width);
        } else if (ppu_cfg->pp_filter == PP_FAST_LINEAR) {
          x_filter_size = 2;
        } else if (ppu_cfg->pp_filter == PP_FAST_BICUBIC) {
          x_filter_size = 4;
        } else if (ppu_cfg->pp_filter == PP_LANCZOS || ppu_cfg->pp_filter == PP_BILINEAR ||
                 ppu_cfg->pp_filter == PP_BICUBIC || ppu_cfg->pp_filter == PP_SPLINE) {
          x_filter_size = (2 * ppu_cfg->x_filter_param * ppu_cfg->crop.width + ppu_cfg->scale.width - 1) / ppu_cfg->scale.width;
        } else if (ppu_cfg->pp_filter == PP_BOX) {
          x_filter_size = (ppu_cfg->x_filter_param * ppu_cfg->crop.width + ppu_cfg->scale.width - 1) / ppu_cfg->scale.width;
        } else { /*PP_NEAREST*/
          x_filter_size = 1;
        }
      } else if (ppu_cfg->crop.width < ppu_cfg->scale.width) {
        if (ppu_cfg->pp_filter == PP_FAST_LINEAR || ppu_cfg->pp_filter == PP_BILINEAR) {
          x_filter_size = 2;
        } else if (ppu_cfg->pp_filter == PP_FAST_BICUBIC || ppu_cfg->pp_filter == PP_BICUBIC) {
          x_filter_size = 4;
        } else if (ppu_cfg->pp_filter == PP_LANCZOS) {
          x_filter_size = (LAN_SIZE_HOR - 1);
        } else { /*PP_NEAREST*/
          x_filter_size = 1;
        }
      } else {
        x_filter_size = 0;
      }
      if (ppu_cfg->crop.height > ppu_cfg->scale.height) {
        if (ppu_cfg->pp_filter == PP_VSI_LINEAR) {
          y_filter_size = 2 * ((ppu_cfg->crop.height) / ppu_cfg->scale.height);
        } else if (ppu_cfg->pp_filter == PP_FAST_LINEAR) {
          y_filter_size = 2;
        } else if (ppu_cfg->pp_filter == PP_FAST_BICUBIC) {
          y_filter_size = 4;
        } else if (ppu_cfg->pp_filter == PP_LANCZOS || ppu_cfg->pp_filter == PP_BILINEAR ||
                 ppu_cfg->pp_filter == PP_BICUBIC || ppu_cfg->pp_filter == PP_SPLINE) {
          y_filter_size = (2 * ppu_cfg->y_filter_param * ppu_cfg->crop.height + ppu_cfg->scale.height - 1) / ppu_cfg->scale.height;
        } else if (ppu_cfg->pp_filter == PP_BOX) {
          y_filter_size = (ppu_cfg->y_filter_param * ppu_cfg->crop.height + ppu_cfg->scale.height - 1) / ppu_cfg->scale.height;
        } else { /*PP_NEAREST*/
          y_filter_size = 1;
        }
      } else if (ppu_cfg->crop.height < ppu_cfg->scale.height) {
        if (ppu_cfg->pp_filter == PP_FAST_LINEAR || ppu_cfg->pp_filter == PP_BILINEAR) {
          y_filter_size = 2;
        } else if (ppu_cfg->pp_filter == PP_FAST_BICUBIC || ppu_cfg->pp_filter == PP_BICUBIC) {
          y_filter_size = 4;
        } else if (ppu_cfg->pp_filter == PP_LANCZOS) {
          y_filter_size = (LAN_SIZE_VER - 1);
        } else { /*PP_NEAREST*/
          y_filter_size = 1;
        }
      } else {
        y_filter_size = 0;
      }
      if (ppu_cfg->crop.width != ppu_cfg->scale.width)
        x_filter_size = 1 + x_filter_size / 2 * 2;
      else
        x_filter_size = 0;
      if (ppu_cfg->crop.height != ppu_cfg->scale.height)
        y_filter_size = 1 + y_filter_size / 2 * 2;
      else
        y_filter_size = 0;
      if (x_filter_size > MIN(ppu_cfg->crop.width - 2, MAX_COEFF_SIZE_HOR_REAL))
        x_filter_size = MIN(ppu_cfg->crop.width - 2, MAX_COEFF_SIZE_HOR_REAL);
      if (y_filter_size > MIN(ppu_cfg->crop.height - 2, MAX_COEFF_SIZE_VER_REAL))
        y_filter_size = MIN(ppu_cfg->crop.height - 2, MAX_COEFF_SIZE_VER_REAL);

      if (ppu_cfg->crop.width > ppu_cfg->scale.width)
        base_x_filter_size =((LAN_SIZE_HOR - 1) * ppu_cfg->crop.width + ppu_cfg->scale.width - 1) / ppu_cfg->scale.width;
      else if (ppu_cfg->crop.width < ppu_cfg->scale.width)
        base_x_filter_size = (LAN_SIZE_HOR - 1);
      else
        base_x_filter_size = 0;
      if (ppu_cfg->crop.height > ppu_cfg->scale.height)
        base_y_filter_size = ((LAN_SIZE_VER - 1) * ppu_cfg->crop.height + ppu_cfg->scale.height - 1) / ppu_cfg->scale.height;
      else if (ppu_cfg->crop.height < ppu_cfg->scale.height)
        base_y_filter_size = (LAN_SIZE_VER - 1);
      else
        base_y_filter_size = 0;
      if (ppu_cfg->crop.width != ppu_cfg->scale.width)
        base_x_filter_size = 1 + base_x_filter_size / 2 * 2;
      else
        base_x_filter_size = 0;
      if (ppu_cfg->crop.height != ppu_cfg->scale.height)
        base_y_filter_size = 1 + base_y_filter_size / 2 * 2;
      else
        base_y_filter_size = 0;
      if (base_x_filter_size > MIN(ppu_cfg->crop.width - 2, MAX_COEFF_SIZE_HOR_REAL))
        base_x_filter_size = MIN(ppu_cfg->crop.width - 2, MAX_COEFF_SIZE_HOR_REAL);
      if (base_y_filter_size > MIN(ppu_cfg->crop.height - 2, MAX_COEFF_SIZE_VER_REAL))
        base_y_filter_size = MIN(ppu_cfg->crop.height - 2, MAX_COEFF_SIZE_VER_REAL);

#ifdef SUPPORT_FLEXIBLE_FILTER
      ppu_cfg->x_filter_size = x_filter_size;
      ppu_cfg->y_filter_size = y_filter_size;
      x_coeff_base = y_coeff_base = 0;
#else
      ppu_cfg->x_filter_size = base_x_filter_size;
      ppu_cfg->y_filter_size = base_y_filter_size;
      x_coeff_base = base_x_filter_size / 2 - x_filter_size / 2;
      y_coeff_base = base_y_filter_size / 2 - y_filter_size / 2;
#endif

      CheckLanFilterSize(ppu_cfg, &x_flag, &y_flag);
      if (x_flag)
        ppu_cfg->x_filter_offset = 2;
      else
        ppu_cfg->x_filter_offset = 0;
      if (y_flag)
        ppu_cfg->y_filter_offset = 2;
      else
        ppu_cfg->y_filter_offset = 0;

      if (ppu_cfg->crop.width > ppu_cfg->scale.width)
        x_filter_stride = NEXT_MULTIPLE((ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset), 8);
      else
        x_filter_stride = 8;
      if (ppu_cfg->crop.height > ppu_cfg->scale.height)
        y_filter_stride = NEXT_MULTIPLE((ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), 8);
      else
        y_filter_stride = 8;
      if (ppu_cfg->scale.width < ppu_cfg->crop.width) {
        if ((ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) <= 7)
          ppu_cfg->x_phase_num = 4;
        else if ((ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) > 7 &&
                 (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) <= 15)
          ppu_cfg->x_phase_num = 3;
        else if ((ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) > 15 &&
                 (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) <= 31)
          ppu_cfg->x_phase_num = 2;
        else if ((ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) > 31 &&
                 (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset) <= 63)
          ppu_cfg->x_phase_num = 1;
        else
          ppu_cfg->x_phase_num = 0;
      } else {
        ppu_cfg->x_phase_num = 4;
      }
      if (ppu_cfg->scale.height < ppu_cfg->crop.height) {
        if ((ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) <= 7)
          ppu_cfg->y_phase_num = 4;
        else if ((ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) > 7 &&
                 (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) <= 15)
          ppu_cfg->y_phase_num = 3;
        else if ((ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) > 15 &&
                 (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) <= 31)
          ppu_cfg->y_phase_num = 2;
        else if ((ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) > 31 &&
                 (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset) <= 63)
          ppu_cfg->y_phase_num = 1;
        else
          ppu_cfg->y_phase_num = 0;
      } else {
        ppu_cfg->y_phase_num = 4;
      }
      double ratio = 0;
      double distance = ppu_cfg->x_filter_param;
      i32 horizontal_weight[MAX_COEFF_SIZE_HOR] = {0};
      i32 vertical_weight[MAX_COEFF_SIZE_VER] = {0};
      i16 *table_data = (i16*)ppu_cfg->lanczos_table.virtual_address;
      if (ppu_cfg->scale.width != ppu_cfg->crop.width) {
        if (ppu_cfg->scale.width > ppu_cfg->crop.width)
          ratio = 1.0;
        else
          ratio = (double)ppu_cfg->scale.width / ppu_cfg->crop.width;
        for (k = 0; k < TABLE_SIZE; k++) {
          for (m = 0; m < x_filter_size; m++) {
            if (ppu_cfg->pp_filter == PP_NEAREST)
              horizontal_weight[m + x_coeff_base] = 65535;
            else if (ppu_cfg->pp_filter == PP_VSI_LINEAR) {
              if (((x_filter_size / 2) % 2) == 1) {
                if (m == (x_filter_size / 2 - (x_filter_size / 2 + 1) / 2) ||
                    m == (x_filter_size / 2 + (x_filter_size / 2 + 1) / 2)) {
                  horizontal_weight[m + x_coeff_base] = (65536 - (i32)((double)ppu_cfg->scale.width / ppu_cfg->crop.width * 65536)  * (x_filter_size / 2)) / 2;
                } else if ((m > (x_filter_size / 2 - (x_filter_size / 2 + 1) / 2)) &&
                           (m < (x_filter_size / 2 + (x_filter_size / 2 + 1) / 2))) {
                  horizontal_weight[m + x_coeff_base] = (i32)((double)ppu_cfg->scale.width / ppu_cfg->crop.width * 65536);
                } else {
                  horizontal_weight[m + x_coeff_base] = 0;
                }
              } else {
                if (m >= x_filter_size / 4 && m < 3 * x_filter_size / 4)
                  horizontal_weight[m + x_coeff_base] = (i32)((double)ppu_cfg->scale.width / ppu_cfg->crop.width * 65536);
                else if (m == 3 * x_filter_size / 4)
                  horizontal_weight[m + x_coeff_base] = 65536 - (i32)((double)ppu_cfg->scale.width / ppu_cfg->crop.width * 65536) * (x_filter_size / 2);
                else
                  horizontal_weight[m + x_coeff_base] = 0;
              }
            } else if (ppu_cfg->pp_filter == PP_FAST_LINEAR) {
              double value = (double)(m)-x_filter_size/2 - ((double)k - TABLE_SIZE/2)/TABLE_SIZE;
              if (value < 0)
                value *= -1.0;
              else
                value *= 1.0;
              double d = value;
              if (d >= 1)
                horizontal_weight[m + x_coeff_base] = 0;
              else
                horizontal_weight[m + x_coeff_base] = (i32)((1 - d) * 65536);
            } else if (ppu_cfg->pp_filter == PP_FAST_BICUBIC) {
              double value = (double)(m)-x_filter_size/2 - ((double)k - TABLE_SIZE/2)/TABLE_SIZE;
              if (value < 0)
                value *= -1.0;
              else
                value *= 1.0;
              double d = value;
              if (d >= 2)
                horizontal_weight[m + x_coeff_base] = 0;
              else if (d < 1)
                horizontal_weight[m + x_coeff_base] = (i32)((1.25 * d * d * d - 2.25 * d * d + 1) * 65536);
              else
                horizontal_weight[m + x_coeff_base] = (i32)((-0.75 * d * d * d + 3.75 * d * d - 6 * d + 3) * 65536);
            } else {
              double value = (double)(m)-x_filter_size/2 - ((double)k - TABLE_SIZE/2)/TABLE_SIZE;
              if (value < 0)
                value *= -1.0;
              else
                value *= 1.0;
              double d = value * ratio;
              if (ppu_cfg->pp_filter == PP_LANCZOS) {
                if (d==0) {
                  horizontal_weight[m + x_coeff_base] = 65535;
                } else if (d > distance || d < -distance) {
                  horizontal_weight[m + x_coeff_base] = 0;
                } else {
                  horizontal_weight[m + x_coeff_base]=
                  (i32)((distance*my_sin(PI*d)*my_sin(PI*d/distance)/(PI*PI*d*d))*65536);
                }
              } else if (ppu_cfg->pp_filter == PP_BILINEAR) {
                if (d >= 1)
                  horizontal_weight[m + x_coeff_base] = 0;
                else
                  horizontal_weight[m + x_coeff_base] = (i32)((1 - d) * 65536);
              } else if (ppu_cfg->pp_filter == PP_BICUBIC) {
                if (d >= 2)
                  horizontal_weight[m + x_coeff_base] = 0;
                else if (d < 1)
                  horizontal_weight[m + x_coeff_base] = (i32)((3 * d * d * d - 5 * d * d + 2) / 2 * 65536);
                else
                  horizontal_weight[m + x_coeff_base] = (i32)((5 * d * d - d * d * d - 8 * d + 4) / 2 * 65536);
              } else if (ppu_cfg->pp_filter == PP_SPLINE) {
                double p = -2.196152422706632;
                horizontal_weight[m + x_coeff_base] = (i32)(getSplineCoeff(1.0, 0.0, p, -p - 1.0, d) * 65536);
                if (m == 0 || m == x_filter_size - 1)
                  horizontal_weight[m + x_coeff_base] = 0;
              } else if (ppu_cfg->pp_filter == PP_BOX) {
                horizontal_weight[m + x_coeff_base] = (i32)(65536.0 / x_filter_size);
              } else {
                APITRACEERR("%s", "InitPpUnitLanczosData# ERROR: Not Supported\n");
              }
            }
          }
          total = 0;
          for (m = 0; m < ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset; m++) {
            total += horizontal_weight[m + ppu_cfg->x_filter_offset/2];
          }
          if (k % (1 << (4 - ppu_cfg->x_phase_num)) == 0) {
            i32 x_ratio[MAX_COEFF_SIZE_HOR] = {0};
            for (m = 0; m < ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset; m++) {
              i32 ratio = (i32) ((double)horizontal_weight[m + ppu_cfg->x_filter_offset/2] / total * 65536);
              u32 ratio_bac = (ratio >= 0) ? ratio : -ratio;
              if (ratio > 0)
                x_ratio[m] = (((ratio_bac >> shift_bit) + ((ratio_bac & (least_coeff / 2)) ? 1 : 0)) << shift_bit);
              else
                x_ratio[m] = -(i32)(((ratio_bac >> shift_bit) + ((ratio_bac & (least_coeff / 2)) ? 1 : 0)) << shift_bit);
            }
            total = 0;
            for (m = 0; m < ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset; m++) {
              total += x_ratio[m];
            }
            if (total < 65536) {
              for (m = 0; m < (65536 - total) / least_coeff; m++)
                x_ratio[ppu_cfg->x_filter_size/2 - ppu_cfg->x_filter_offset/2 - (65536 - total)/(2 * least_coeff) + m] += least_coeff;
            } else {
              for (m = 0; m < (total - 65536) / least_coeff; m++)
                x_ratio[ppu_cfg->x_filter_size/2 - ppu_cfg->x_filter_offset/2 - (total - 65536)/(2 * least_coeff) + m] -= least_coeff;
            }
            if (ppu_cfg->pp_filter != PP_NEAREST) {
              for (m = 0; m < ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset; m++) {
                if (x_ratio[m] == 65536) {
                  x_ratio[m] -= least_coeff;
                  x_ratio[m - 1] += least_coeff;
                }
              }
            }
            for (m = 0; m < ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset; m++) {
              *table_data++ = x_ratio[m]  >> shift_bit;
            }
            for (m = 0; m < x_filter_stride - (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset); m++) {
              *table_data++ = 0;
            }
          }
        }
      }
      distance = ppu_cfg->y_filter_param;
      table_data = (i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET;
      if (ppu_cfg->scale.height != ppu_cfg->crop.height) {
        if (ppu_cfg->scale.height > ppu_cfg->crop.height)
          ratio = 1.0;
        else
          ratio = (double)ppu_cfg->scale.height / ppu_cfg->crop.height;
        for (k = 0; k < TABLE_SIZE; k++) {
          for (m = 0; m < y_filter_size; m++) {
            if (ppu_cfg->pp_filter == PP_NEAREST)
              vertical_weight[m + y_coeff_base] = 65535;
            else if (ppu_cfg->pp_filter == PP_VSI_LINEAR) {
              if (((y_filter_size / 2) % 2) == 1) {
                if (m == (y_filter_size / 2 - (y_filter_size / 2 + 1) / 2) ||
                    m == (y_filter_size / 2 + (y_filter_size / 2 + 1) / 2)) {
                  vertical_weight[m + y_coeff_base] = (65536 - (i32)((double)ppu_cfg->scale.height / ppu_cfg->crop.height * 65536)  * (y_filter_size / 2)) / 2;
                } else if ((m > (y_filter_size / 2 - (y_filter_size / 2 + 1) / 2)) &&
                           (m < (y_filter_size / 2 + (y_filter_size / 2 + 1) / 2))) {
                  vertical_weight[m + y_coeff_base] = (i32)((double)ppu_cfg->scale.height / ppu_cfg->crop.height * 65536);
                } else {
                  vertical_weight[m + y_coeff_base] = 0;
                }
              } else {
                if (m >= y_filter_size / 4 && m < 3 * y_filter_size / 4)
                  vertical_weight[m + y_coeff_base] = (i32)((double)ppu_cfg->scale.height / ppu_cfg->crop.height * 65536);
                else if (m == 3 * y_filter_size / 4)
                  vertical_weight[m + y_coeff_base] = 65536 - (i32)((double)ppu_cfg->scale.height / ppu_cfg->crop.height * 65536) * (y_filter_size / 2);
                else
                  vertical_weight[m + y_coeff_base] = 0;
              }
            } else if (ppu_cfg->pp_filter == PP_FAST_LINEAR) {
              double value = (double)(m)-y_filter_size/2 - ((double)k - TABLE_SIZE/2)/TABLE_SIZE;
              if (value < 0)
                value *= -1.0;
              else
                value *= 1.0;
              double d = value;
              if (d >= 1)
                vertical_weight[m + y_coeff_base] = 0;
              else
                vertical_weight[m + y_coeff_base] = (i32)((1 - d) * 65536);
            } else if (ppu_cfg->pp_filter == PP_FAST_BICUBIC) {
              double value = (double)(m)-y_filter_size/2 - ((double)k - TABLE_SIZE/2)/TABLE_SIZE;
              if (value < 0)
                value *= -1.0;
              else
                value *= 1.0;
              double d = value;
              if (d >= 2)
                vertical_weight[m + y_coeff_base] = 0;
              else if (d < 1)
                vertical_weight[m + y_coeff_base] = (i32)((1.25 * d * d * d - 2.25 * d * d + 1) * 65536);
              else
                vertical_weight[m + y_coeff_base] = (i32)((-0.75 * d * d * d + 3.75 * d * d - 6 * d + 3) * 65536);
            } else {
              double value = (double)(m)-y_filter_size/2 - ((double)k - TABLE_SIZE/2)/TABLE_SIZE;
              if (value < 0)
                value *= -1.0;
              else
                value *= 1.0;
              double d = value * ratio;
              if (ppu_cfg->pp_filter == PP_LANCZOS) {
                if (d==0) {
                  vertical_weight[m + y_coeff_base] = 65535;
                } else if (d > distance || d < -distance) {
                  vertical_weight[m + y_coeff_base] = 0;
                } else {
                  vertical_weight[m + y_coeff_base]=
                  (i32)((distance*my_sin(PI*d)*my_sin(PI*d/distance)/(PI*PI*d*d))*65536);
                }
              } else if (ppu_cfg->pp_filter == PP_BILINEAR) {
                if (d >= 1)
                  vertical_weight[m + y_coeff_base] = 0;
                else
                  vertical_weight[m + y_coeff_base] = (i32)((1 - d) * 65536);
              } else if (ppu_cfg->pp_filter == PP_BICUBIC) {
                if (d >= 2)
                  vertical_weight[m + y_coeff_base] = 0;
                else if (d < 1)
                  vertical_weight[m + y_coeff_base] = (i32)((3 * d * d * d - 5 * d * d + 2) / 2 * 65536);
                else
                  vertical_weight[m + y_coeff_base] = (i32)((5 * d * d - d * d * d - 8 * d + 4) / 2 * 65536);
              } else if (ppu_cfg->pp_filter == PP_SPLINE) {
                double p = -2.196152422706632;
                vertical_weight[m + y_coeff_base] = (i32)(getSplineCoeff(1.0, 0.0, p, -p - 1.0, d) * 65536);
                if (m == 0 || m == y_filter_size - 1)
                  vertical_weight[m + y_coeff_base] = 0;
              } else if (ppu_cfg->pp_filter == PP_BOX) {
                vertical_weight[m + y_coeff_base] = (i32)(65536.0 / y_filter_size);
              } else {
                APITRACEERR("%s", "InitPpUnitLanczosData# ERROR: Not Supported\n");
              }
            }
          }
          total = 0;
          for (m = 0; m < ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset; m++) {
            total += vertical_weight[m + ppu_cfg->y_filter_offset/2];
          }
          if (k % (1 << (4 - ppu_cfg->y_phase_num)) == 0) {
            i32 y_ratio[MAX_COEFF_SIZE_HOR] = {0};
            for (m = 0; m < ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset; m++) {
              i32 ratio = (i32) ((double)vertical_weight[m + ppu_cfg->y_filter_offset/2] / total * 65536);
              u32 ratio_bac = (ratio >= 0) ? ratio : -ratio;
              if (ratio > 0)
                y_ratio[m] = (((ratio_bac >> shift_bit) + ((ratio_bac & (least_coeff / 2)) ? 1 : 0)) << shift_bit);
              else
                y_ratio[m] = -(i32)(((ratio_bac >> shift_bit) + ((ratio_bac & (least_coeff / 2)) ? 1 : 0)) << shift_bit);
            }
            total = 0;
            for (m = 0; m < ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset; m++) {
              total += y_ratio[m];
            }
            if (total < 65536) {
              for (m = 0; m < (65536 - total) / least_coeff; m++)
                y_ratio[ppu_cfg->y_filter_size/2 - ppu_cfg->y_filter_offset/2 - (65536 - total)/(2 * least_coeff) + m] += least_coeff;
            } else {
              for (m = 0; m < (total - 65536) / least_coeff; m++)
                y_ratio[ppu_cfg->y_filter_size/2 - ppu_cfg->y_filter_offset/2 - (total - 65536)/(2 * least_coeff) + m] -= least_coeff;
            }
            if (ppu_cfg->pp_filter != PP_NEAREST) {
              for (m = 0; m < ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset; m++) {
                if (y_ratio[m] == 65536) {
                  y_ratio[m] -= least_coeff;
                  y_ratio[m - 1] += least_coeff;
                }
              }
            }
            for (m = 0; m < ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset; m++) {
              *table_data++ = y_ratio[m] >> shift_bit;
            }
            for (m = 0; m < y_filter_stride - (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset); m++) {
              *table_data++ = 0;
            }
          }
        }
      }
      table_data = (i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + Y_COEFF_OFFSET;
      scale_ratio_x_inv = FDIVI(TOFIX(ppu_cfg->crop.width, 16) + ppu_cfg->scale.width / 2, ppu_cfg->scale.width);
      scale_ratio_y_inv = FDIVI(TOFIX(ppu_cfg->crop.height, 16) + ppu_cfg->scale.height / 2, ppu_cfg->scale.height);
      if (scale_ratio_x_inv % 2) scale_ratio_x_inv++;
      if (scale_ratio_y_inv % 2) scale_ratio_y_inv++;
      if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
        xDstInSrc = scale_ratio_x_inv - 65536;
      } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
        xDstInSrc = 0;
      } else {
        xDstInSrc = scale_ratio_x_inv;
      }
      pos = xDstInSrc / 2 - scale_ratio_x_inv;
      x_pos = 0;
      start_count = 0;
      end_count = 0;
      i16 start_value[2]={0,0};
      i16 end_value[2]={0,0};
      u32 phase_repet_num = (1 << (4 - ppu_cfg->x_phase_num));
      if (ppu_cfg->crop.width > ppu_cfg->scale.width) {
        for (j = 0; j < ppu_cfg->scale.width; j++) {
          pos += scale_ratio_x_inv;
          x_pos = FLOOR(pos+32768);
          start_pos = x_pos - (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset)/2;
          end_pos = x_pos + (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset)/2;
          table_index = ((pos+32768 - MAKE_FIXED_UNI(x_pos)) >> (FIXED_BITS_UNI-TABLE_LENGTH));
          value = 0;
          if (start_pos < 0) {
            for (k = start_pos; k <= 0; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + out_index / phase_repet_num * x_filter_stride + coeff_index);
            }
            start_value[start_count++] = value;
          } else {
            if (start_count < 2) {
              CalOutTableIndex(table_index, 0, (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + out_index / phase_repet_num * x_filter_stride + coeff_index);
              start_value[start_count++] = value;
            }
          }
          value = 0;
          if (end_pos >= ppu_cfg->crop.width) {
            for (k = ppu_cfg->crop.width - 1; k <= end_pos; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + out_index / phase_repet_num * x_filter_stride + coeff_index);
            }
            end_value[end_count++] = value;
          }
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = start_value[j];
          start_value[j] = 0;
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = end_value[j];
          end_value[j] = 0;
        }
      }
      /*chroma*/
      if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
        xDstInSrc = scale_ratio_x_inv - 65536;
      } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
        xDstInSrc = 0;
      } else {
        xDstInSrc = scale_ratio_x_inv;
      }
      pos = xDstInSrc / 2 - scale_ratio_x_inv;
      x_pos = 0;
      end_count = 0;
      i16 chroma_end_value[2]={0,0};
      if (ppu_cfg->crop.width > ppu_cfg->scale.width) {
        for (j = 0; j < ppu_cfg->scale.width / 2; j++) {
          pos += scale_ratio_x_inv;
          x_pos = FLOOR(pos+32768);
          start_pos = x_pos - (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset)/2;
          end_pos = x_pos + (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset)/2;
          table_index = ((pos+32768 - MAKE_FIXED_UNI(x_pos)) >> (FIXED_BITS_UNI-TABLE_LENGTH));
          value = 0;
          if (end_pos >= ppu_cfg->crop.width / 2) {
            for (k = ppu_cfg->crop.width / 2 - 1; k <= end_pos; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + out_index / phase_repet_num * x_filter_stride + coeff_index);
            }
            chroma_end_value[end_count++] = value;
          }
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = chroma_end_value[j];
          chroma_end_value[j] = 0;
        }
      }
      table_data = (i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + Y_COEFF_OFFSET + 16;
      if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
        yDstInSrc = scale_ratio_y_inv - 65536;
      } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
        yDstInSrc = 0;
      } else {
        yDstInSrc = scale_ratio_y_inv;
      }
      pos = yDstInSrc / 2 - scale_ratio_y_inv;
      y_pos = 0;
      start_count = 0;
      end_count = 0;
      phase_repet_num = (1 << (4 - ppu_cfg->y_phase_num));
      if (ppu_cfg->scale.height < ppu_cfg->crop.height) {
        for (j = 0; j<ppu_cfg->scale.height; j++) {
          pos += scale_ratio_y_inv;
          y_pos = FLOOR(pos+32768);
          start_pos = y_pos - (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          end_pos = y_pos + (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          table_index = ((pos+32768 - MAKE_FIXED_UNI(y_pos)) >> (FIXED_BITS_UNI-TABLE_LENGTH));
          value = 0;
          if (start_pos < 0) {
            for (k = start_pos; k <= 0; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
            }
            start_value[start_count++] = value;
          } else {
            if (start_count < 2) {
              CalOutTableIndex(table_index, 0, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value = *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
              start_value[start_count++] = value;
            }
          }
          value = 0;
          if (end_pos >= ppu_cfg->crop.height) {
            for (k = ppu_cfg->crop.height - 1; k <= end_pos; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
            }
            end_value[end_count++] = value;
          }
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = start_value[j];
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = end_value[j];
        }
      }
      /*chroma*/
      if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
        yDstInSrc = scale_ratio_y_inv - 65536;
      } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
        yDstInSrc = 0;
      } else {
        yDstInSrc = scale_ratio_y_inv;
      }
      pos = yDstInSrc / 2 - scale_ratio_y_inv;
      y_pos = 0;
      end_count = 0;
      if (ppu_cfg->scale.height < ppu_cfg->crop.height) {
        for (j = 0; j<ppu_cfg->scale.height / 2; j++) {
          pos += scale_ratio_y_inv;
          y_pos = FLOOR(pos+32768);
          start_pos = y_pos - (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          end_pos = y_pos + (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset)/2;
          table_index = ((pos+32768 - MAKE_FIXED_UNI(y_pos)) >> (FIXED_BITS_UNI-TABLE_LENGTH));
          value = 0;
          if (end_pos >= ppu_cfg->crop.height / 2) {
            for (k = ppu_cfg->crop.height / 2 - 1; k <= end_pos; k++) {
              CalOutTableIndex(table_index, k-start_pos, (ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset), &out_index, &coeff_index);
              value += *((i16*)ppu_cfg->lanczos_table.virtual_address + X_COEFF_OFFSET + out_index / phase_repet_num * y_filter_stride + coeff_index);
            }
            chroma_end_value[end_count++] = value;
          }
        }
        for (j = 0; j < 2; j++) {
          *table_data++ = chroma_end_value[j];
        }
      }
    }
#ifdef SUPPORT_DMA
    u32 n_cores = ppu_cfg->lanczos_table.size / LANCZOS_COEFF_BUFFER_SIZE / sizeof(i16);
    for (j = 0; j < n_cores; j++) {
      DWLDMATransData((addr_t)(ppu_cfg->lanczos_table.bus_address +
                               j * LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16)),
                      (void *)((u8 *)ppu_cfg->lanczos_table.virtual_address +
                               j * LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16)),
                      LANCZOS_COEFF_BUFFER_SIZE * sizeof(i16), HOST_TO_DEVICE); /* 512KB + tile_edge_size */
    }
#endif
  }
}

#if 0
void InitFbcParams(PpUnitIntConfig *ppu_cfg, u32 db_filter, addr_t bus_address, u32 all_ppu) {
  u32 i;
  u32 ratio_w, ratio_h;
  u32 begin_offset = 0, hdr_size = 0;
  for (i = 0; i < (all_ppu ? DEC_MAX_PPU_COUNT : 1); i++, ppu_cfg++) {
    if (!ppu_cfg->enabled) continue;
    ppu_cfg->bus_address = bus_address;
    if (ppu_cfg->tiled_e && ppu_cfg->tile_mode) {
      ratio_w = ppu_cfg->crop.width / ppu_cfg->scale.width;
      ratio_h = ppu_cfg->crop.height / ppu_cfg->scale.height;
      ppu_cfg->vir_left = (ppu_cfg->crop.x / ratio_w) % 16;
      if (((ppu_cfg->vir_left + ppu_cfg->scale.width) % 16))
        ppu_cfg->vir_right = 16 - ((ppu_cfg->vir_left + ppu_cfg->scale.width) % 16);
      else
        ppu_cfg->vir_right = 0;
      if (db_filter) {
        if (ppu_cfg->crop.y <= 56) {
          if (((56 - ppu_cfg->crop.y) / ratio_h) % 16)
            ppu_cfg->vir_top = 16 - (((56 - ppu_cfg->crop.y) / ratio_h) % 16);
          else
            ppu_cfg->vir_top = 0;
          if (((ppu_cfg->vir_top + ppu_cfg->scale.height) % 16))
            ppu_cfg->vir_bottom = 16 - ((ppu_cfg->vir_top + ppu_cfg->scale.height) % 16);
          else
            ppu_cfg->vir_bottom = 0;
        } else {
          if (((64 - ((ppu_cfg->crop.y - 56) % 64)) / ratio_h) % 16)
            ppu_cfg->vir_top = 16 - (((64 - ((ppu_cfg->crop.y - 56) % 64)) / ratio_h) % 16);
          else
            ppu_cfg->vir_top = 0;
          if (((ppu_cfg->vir_top + ppu_cfg->scale.height) % 16))
            ppu_cfg->vir_bottom = 16 - ((ppu_cfg->vir_top + ppu_cfg->scale.height) % 16);
          else
            ppu_cfg->vir_bottom = 0;
        }
      } else {
        if (((64 - (ppu_cfg->crop.y % 64)) / ratio_h) % 16)
          ppu_cfg->vir_top = 16 - (((64 - (ppu_cfg->crop.y % 64)) / ratio_h) % 16);
        else
          ppu_cfg->vir_top = 0;
        if (((ppu_cfg->vir_top + ppu_cfg->scale.height) % 16))
          ppu_cfg->vir_bottom = 16 - ((ppu_cfg->vir_top + ppu_cfg->scale.height) % 16);
        else
          ppu_cfg->vir_bottom = 0;
      }
      if (ppu_cfg->tile_mode == TILED16x16) {
        begin_offset = ppu_cfg->hdr_offset;
#ifdef ASIC_TRACE_SUPPORT
        hdr_size = 0;
#else
        hdr_size = NEXT_MULTIPLE((ppu_cfg->vir_left + ppu_cfg->scale.width + ppu_cfg->vir_right) * (ppu_cfg->vir_top + ppu_cfg->scale.height + ppu_cfg->vir_bottom) / 16, 64);
#endif
        ppu_cfg->luma_offset = begin_offset + hdr_size;
        ppu_cfg->chroma_offset = ppu_cfg->luma_offset + NEXT_MULTIPLE((ppu_cfg->vir_left + ppu_cfg->scale.width + ppu_cfg->vir_right) *
                                 (ppu_cfg->vir_top + ppu_cfg->scale.height + ppu_cfg->vir_bottom) * (ppu_cfg->stream_pixel_width == 10 ? 2 : 1),
                                  ALIGN(ppu_cfg->align));
      }
    }
  }
}
#endif

void calSecondUpScaleRatio(const struct DecHwFeatures *hw_feature, PpUnitIntConfig *ppu_cfg, u32 interlace) {
  u32 i = 0;
  u32 found = 0;
  if (!hw_feature->pp_support_6x) {
    if (ppu_cfg->scale.width > 3 * ppu_cfg->crop.width) {
      for (i = 3 * ppu_cfg->crop.width; i > ppu_cfg->crop.width; i-=2) {
        if ((ppu_cfg->scale.width % i) == 0) {
          ppu_cfg->out_width = i;
          ppu_cfg->out_ratio_x = ppu_cfg->scale.width / i;
          found = 1;
          break;
        }
      }

      if (!found) {
        for (i = 3 * ppu_cfg->crop.width; i > ppu_cfg->crop.width; i-=2) {
          if ((ppu_cfg->scale.width / i) != (ppu_cfg->scale.width / (i - 2))) {
            ppu_cfg->out_width = i;
            ppu_cfg->out_ratio_x = ppu_cfg->scale.width / (i - 2);
            break;
          }
        }
      }
    } else {
      ppu_cfg->out_width = ppu_cfg->scale.width;
      ppu_cfg->out_ratio_x = 1;
    }
    found = 0;
    if (ppu_cfg->scale.height > 3 * ppu_cfg->crop.height) {
      for (i = 3 * ppu_cfg->crop.height; i > ppu_cfg->crop.height; i-=(interlace ? 4 : 2)) {
        if ((ppu_cfg->scale.height % i) == 0) {
          ppu_cfg->out_height = i;
          ppu_cfg->out_ratio_y = ppu_cfg->scale.height / i;
          found = 1;
          break;
        }
      }
      if (!found) {
        for (i = 3 * ppu_cfg->crop.height; i > ppu_cfg->crop.height; i-=(interlace ? 4 : 2)) {
          if ((ppu_cfg->scale.height / i) != (ppu_cfg->scale.height / (i - 2))) {
            ppu_cfg->out_height = i;
            ppu_cfg->out_ratio_y = ppu_cfg->scale.height / (i - (interlace ? 4 : 2));
            break;
          }
        }
      }
    } else {
      ppu_cfg->out_height =  ppu_cfg->scale.height;
      ppu_cfg->out_ratio_y = 1;
    }
  } else {
    ppu_cfg->out_width = ppu_cfg->scale.width;
    ppu_cfg->out_ratio_x = 1;
    ppu_cfg->out_height =  ppu_cfg->scale.height;
    ppu_cfg->out_ratio_y = 1;
  }
}
/* Print Out format */

char *PrintOutFormat(u16 i){
  switch(i){
    case PP_OUT_FMT_YUV420PACKED: return "PP_OUT_FMT_YUV420PACKED"; break;
    case PP_OUT_FMT_YUV420_P010: return "PP_OUT_FMT_YUV420_P010"; break;
    case PP_OUT_FMT_YUV420_BIGE: return "PP_OUT_FMT_YUV420_BIGE"; break;
    case PP_OUT_FMT_YUV420_8BIT: return "PP_OUT_FMT_YUV420_8BIT"; break;
    case PP_OUT_FMT_YUV400: return "PP_OUT_FMT_YUV400"; break;
    case PP_OUT_FMT_YUV400_P010: return "PP_OUT_FMT_YUV400_P010"; break;
    case PP_OUT_FMT_YUV400_8BIT: return "PP_OUT_FMT_YUV400_8BIT"; break;
    case PP_OUT_FMT_IYUVPACKED: return "PP_OUT_FMT_IYUVPACKED"; break;
    case PP_OUT_FMT_IYUV_P010: return "PP_OUT_FMT_IYUV_P010"; break;
    case PP_OUT_FMT_IYUV_8BIT: return "PP_OUT_FMT_IYUV_8BIT"; break;
    case PP_OUT_FMT_YUV420_10: return "PP_OUT_FMT_YUV420_10"; break;
    case PP_OUT_FMT_RGB: return "PP_OUT_FMT_RGB"; break;
    case PP_OUT_FMT_YUV422_10: return "PP_OUT_FMT_YUV422_10"; break;
    case PP_OUT_FMT_YUV422_8BIT: return "PP_OUT_FMT_YUV422_8BIT"; break;
    case PP_OUT_FMT_YUV422_P010: return " PP_OUT_FMT_YUV422_P010"; break;
    case PP_OUT_FMT_YUV422_P012: return "PP_OUT_FMT_YUV422_P012"; break;
    case PP_OUT_FMT_IYUV_422_8BIT: return "PP_OUT_FMT_IYUV_422_8BIT"; break;
    case PP_OUT_FMT_IYUV_422_P010: return "PP_OUT_FMT_IYUV_422_P010"; break;
    case PP_OUT_FMT_IYUV_422_P012: return "PP_OUT_FMT_IYUV_422_P012"; break;
    case PP_OUT_FMT_YUV422_YUYV: return "PP_OUT_FMT_YUV422_YUYV"; break;
    case PP_OUT_FMT_YUV422_UYVY: return "PP_OUT_FMT_YUV422_UYVY"; break;
    case PP_OUT_FMT_YUV400_P012: return "PP_OUT_FMT_YUV400_P012"; break;
    case PP_OUT_FMT_YUV420_P012: return "PP_OUT_FMT_YUV420_P012"; break;
    case PP_OUT_FMT_IYUV_420_P012: return "PP_OUT_FMT_IYUV_420_P012"; break;
    case PP_OUT_FMT_IYUV_444_8BIT: return "PP_OUT_FMT_IYUV_444_8BIT"; break;
    case PP_OUT_FMT_IYUV_444_P010: return "PP_OUT_FMT_IYUV_444_P010"; break;
    case PP_OUT_FMT_IYUV_444_P012: return "PP_OUT_FMT_IYUV_444_P012"; break;
    default: return "Illegal OutFormat";
  }

}

/* Print RGB format */
char *PrintRGBFormat(u16 i){
  return "1";

}
/* Print ppu_cfg */
int num_pp = 0, num_pp_bitmap;
int num_pp_flag = 0;
void PrintPpunitConfig(PpUnitIntConfig *ppu_cfg){
  u32 i;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++){
  if (ppu_cfg->enabled){
    num_pp = i+1;
    num_pp_bitmap |= (1 << i);
    num_pp_flag = 1;
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Enabled: %d\n",i, ppu_cfg->enabled);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Tiled_e: %d\n",i, ppu_cfg->tiled_e);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB: %d\n",i, ppu_cfg->rgb);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB Planar: %d\n",i, ppu_cfg->rgb_planar);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Cr first: %d\n",i, ppu_cfg->cr_first);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Luma offset: 0x%x, Luma size: %d\n",i, ppu_cfg->luma_offset, ppu_cfg->luma_size);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Chroma offset: 0x%x, Chroma size: %d\n",i, ppu_cfg->chroma_offset, ppu_cfg->chroma_size);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Hdr offset: 0x%x\n",i, ppu_cfg->hdr_offset);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Pixel Width: %d\n",i, ppu_cfg->pixel_width);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Stream Pixel Width: %d\n",i, ppu_cfg->stream_pixel_width);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Shaper Enabled: %d\n",i, ppu_cfg->shaper_enabled);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Shaper No Pad: %d\n",i, ppu_cfg->shaper_no_pad);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Dec400 Enabled: %d\n",i, ppu_cfg->dec400_enabled);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Planar: %d\n",i, ppu_cfg->planar);
    if (ppu_cfg->align == DEC_ALIGN_1B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 1B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_8B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 8B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_16B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 16B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_32B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 32B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_64B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 64B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_128B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 128B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_256B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 256B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_512B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 512B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_1024B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 1024B\n",i);
    if (ppu_cfg->align == DEC_ALIGN_2048B)
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Align: 2048B\n",i);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Tile coded image: %d\n",i, ppu_cfg->tile_coded_image);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Ystride: %d\n",i, ppu_cfg->ystride);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Cstride: %d\n",i, ppu_cfg->cstride);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# False_ystride: %d\n",i, ppu_cfg->false_ystride);
    APITRACEDEBUG("PpUnitCfg PPU[%d]# False_cstride: %d\n",i, ppu_cfg->false_cstride);
    if (ppu_cfg->crop.enabled){
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Crop# Enabled: %d\n",i, ppu_cfg->crop.enabled);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Crop# Setbyuser: %d\n",i, ppu_cfg->crop.set_by_user);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Crop# x: %d, y: %d, width: %d, height: %d\n",i, ppu_cfg->crop.x, ppu_cfg->crop.y, ppu_cfg->crop.width, ppu_cfg->crop.height);
    }

    if (ppu_cfg->crop2.enabled){
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Crop2# Enabled: %d\n",i, ppu_cfg->crop2.enabled);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Crop2# x: %d, y: %d, width: %d, height: %d\n",i, ppu_cfg->crop2.x, ppu_cfg->crop2.y, ppu_cfg->crop2.width, ppu_cfg->crop2.height);
    }

    if (ppu_cfg->scale.enabled) {
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale# Enabled: %d\n",i, ppu_cfg->scale.enabled);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale# Scale by ratio# x: %d\n",i, ppu_cfg->scale.scale_by_ratio);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale# Ratio x: %d\n",i, ppu_cfg->scale.ratio_x);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale# Ratio y: %d\n",i, ppu_cfg->scale.ratio_y);
      APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale# Width: %d, Height: %d\n",i, ppu_cfg->scale.width, ppu_cfg->scale.height);
    }

  APITRACEDEBUG("PpUnitCfg PPU[%d]# Monochrome: %d\n",i, ppu_cfg->monochrome);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out format: %s\n",i, PrintOutFormat(ppu_cfg->out_format));
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out P010: %d\n",i, ppu_cfg->out_p010);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out 1010: %d\n",i, ppu_cfg->out_1010);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out I010: %d\n",i, ppu_cfg->out_I010);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out L010: %d\n",i, ppu_cfg->out_L010);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out P012: %d\n",i, ppu_cfg->out_p012);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out I012: %d\n",i, ppu_cfg->out_I012);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out cut 8bits: %d\n",i, ppu_cfg->out_cut_8bits);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Video Range: %d\n",i, ppu_cfg->video_range);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Range max: %d\n",i, ppu_cfg->video_range);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB format: %s\n",i, PrintRGBFormat(ppu_cfg->rgb_format));
  APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB format: %s\n",i, PrintRGBFormat(ppu_cfg->rgb_format));
  if (ppu_cfg->rgb_stan == BT601)
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB conversion standard: %s\n",i, "BT601");
  if (ppu_cfg->rgb_stan == BT601_L)
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB conversion standard: %s\n",i, "BT601_L");
  if (ppu_cfg->rgb_stan == BT709)
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB conversion standard: %s\n",i, "BT709");
  if (ppu_cfg->rgb_stan == BT709_L)
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB conversion standard: %s\n",i, "BT709_L");
  if (ppu_cfg->rgb_stan == BT2020)
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB conversion standard: %s\n",i, "BT2020");
  if (ppu_cfg->rgb_stan == BT2020_L)
    APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB conversion standard: %s\n",i, "BT2020_L");
  APITRACEDEBUG("PpUnitCfg PPU[%d]# RGB alpha: %d\n",i, ppu_cfg->rgb_alpha);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# X filter size: %d, X filter offset\n",i, ppu_cfg->x_filter_size,ppu_cfg->x_filter_offset);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Y filter size: %d, Y filter offset\n",i, ppu_cfg->y_filter_size,ppu_cfg->y_filter_offset);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Outwidth: %d, Outheight\n",i, ppu_cfg->out_width,ppu_cfg->out_height);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out ratio x: %d, Out ratio y\n",i, ppu_cfg->out_ratio_x,ppu_cfg->out_ratio_y);
  switch(ppu_cfg->pp_filter){
    case PP_VSI_LINEAR: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_VSI_LINEAR"); break;
    case PP_LANCZOS: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_LANCZOS"); break;
    case PP_NEAREST: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_NEAREST"); break;
    case PP_BILINEAR: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_BILINEAR"); break;
    case PP_BICUBIC: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_BICUBIC"); break;
    case PP_SPLINE: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_SPLINE"); break;
    case PP_BOX: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_BOX"); break;
    case PP_FAST_LINEAR: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_FAST_LINEAR"); break;
    case PP_FAST_BICUBIC: APITRACEDEBUG("PpUnitCfg PPU[%d]# PP filter: %s\n",i, "PP_FAST_BICUBIC"); break;
    default:
      ASSERT(0);
      break;
  }
  APITRACEDEBUG("PpUnitCfg PPU[%d]# X filter param: %d\n",i, ppu_cfg->x_filter_param);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Y filter param: %d\n",i, ppu_cfg->y_filter_param);
  switch(ppu_cfg->tile_mode){
    case TILED4x4: APITRACEDEBUG("PpUnitCfg PPU[%d]# TIELD mode: %s\n",i, "TILED4x4"); break;
    case TILED8x8: APITRACEDEBUG("PpUnitCfg PPU[%d]# TIELD mode: %s\n",i, "TILED8x8"); break;
    case TILED16x16: APITRACEDEBUG("PpUnitCfg PPU[%d]# TIELD mode: %s\n",i, "TILED16x16"); break;
    case TILED128x2: APITRACEDEBUG("PpUnitCfg PPU[%d]# TIELD mode: %s\n",i, "TILED128x2"); break;
    case TILED64x64: APITRACEDEBUG("PpUnitCfg PPU[%d]# TIELD mode: %s\n",i, "TILED64x64"); break;
    case TILED32x8: APITRACEDEBUG("PpUnitCfg PPU[%d]# TIELD mode: %s\n",i, "TILED32x8"); break;
    default:
      ASSERT(0);
      break;
  }
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Vir left: %d\n",i, ppu_cfg->vir_left);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Vir right: %d\n",i, ppu_cfg->vir_right);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Vir top: %d\n",i, ppu_cfg->vir_top);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Vir bottom: %d\n",i, ppu_cfg->vir_bottom);
  switch(ppu_cfg->src_sel_mode){
    case DOWN_ROUND: APITRACEDEBUG("PpUnitCfg PPU[%d]# Center point select algorithm: %s\n",i, "DOWN_ROUND"); break;
    case NO_ROUND: APITRACEDEBUG("PpUnitCfg PPU[%d]# Center point select algorithm: %s\n",i, "NO_ROUND"); break;
    case UP_ROUND: APITRACEDEBUG("PpUnitCfg PPU[%d]# Center point select algorithm: %s\n",i, "UP_ROUND"); break;
    default:
      ASSERT(0);
      break;
  }
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Pad sel: %d\n",i, ppu_cfg->pad_sel);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Luma pad value: %d\n",i, ppu_cfg->pad_Y);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Cb pad value: %d\n",i, ppu_cfg->pad_U);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Cr pad value: %d\n",i, ppu_cfg->pad_V);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Sub x: %d\n",i, ppu_cfg->sub_x);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Sub y: %d\n",i, ppu_cfg->sub_y);
  switch(ppu_cfg->chroma_format){
    case PP_YUV400: APITRACEDEBUG("PpUnitCfg PPU[%d]# Chroma format: %s\n",i, "PP_YUV400"); break;
    case PP_YUV420: APITRACEDEBUG("PpUnitCfg PPU[%d]# Chroma format: %s\n",i, "PP_YUV420"); break;
    case PP_YUV422: APITRACEDEBUG("PpUnitCfg PPU[%d]# Chroma format: %s\n",i, "PP_YUV422"); break;
    case PP_YUV444: APITRACEDEBUG("PpUnitCfg PPU[%d]# Chroma format: %s\n",i, "PP_YUV444"); break;
    default:
      ASSERT(0);
      break;
  }
  APITRACEDEBUG("PpUnitCfg PPU[%d]# X phase num: %d\n",i, ppu_cfg->x_phase_num);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Y phase num: %d\n",i, ppu_cfg->y_phase_num);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# LC stride: %d\n",i, ppu_cfg->lc_stripe);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# Virtual address: 0x%x\n",i, ppu_cfg->lanczos_table.virtual_address);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# Bus address: 0x%x\n",i, ppu_cfg->lanczos_table.bus_address);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# Size: %d\n",i, ppu_cfg->lanczos_table.size);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# Logical: %d\n",i, ppu_cfg->lanczos_table.logical_size);
  switch(ppu_cfg->lanczos_table.mem_type){
    case DWL_MEM_TYPE_CPU: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_CPU"); break;
    case DWL_MEM_TYPE_SLICE: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_SLICE"); break;
    case DWL_MEM_TYPE_DPB: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_DPB"); break;
    case DWL_MEM_TYPE_VPU_WORKING: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_WORKING"); break;
    case DWL_MEM_TYPE_VPU_WORKING_SPECIAL: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_WORKING_SPECIAL"); break;

    case DWL_MEM_TYPE_VPU_ONLY: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_ONLY"); break;
    case DWL_MEM_TYPE_VPU_CPU: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_CPU"); break;
    case DWL_MEM_TYPE_DMA_DEVICE_ONLY: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_DEVICE_ONLY"); break;
    case DWL_MEM_TYPE_DMA_HOST_TO_DEVICE: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_HOST_TO_DEVICE"); break;
    case DWL_MEM_TYPE_DMA_DEVICE_TO_HOST: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_DEVICE_TO_HOST"); break;
    case DWL_MEM_TYPE_DMA_HOST_AND_DEVICE: APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_HOST_AND_DEVICE"); break;
    default:
      APITRACEDEBUG("PpUnitCfg PPU[%d]# lanczos_table# MEM type: %s\n",i, "Illegal type");
      break;

  }
  APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# Virtual address: 0x%x\n",i, ppu_cfg->fbc_tile.virtual_address);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# Bus address: 0x%x\n",i, ppu_cfg->fbc_tile.bus_address);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# Size: 0x%x\n",i, ppu_cfg->fbc_tile.size);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# Offset: 0x%x\n",i, ppu_cfg->fbc_tile_offset);

  switch(ppu_cfg->fbc_tile.mem_type){
    case DWL_MEM_TYPE_CPU: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_CPU"); break;
    case DWL_MEM_TYPE_SLICE: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_SLICE"); break;
    case DWL_MEM_TYPE_DPB: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_DPB"); break;
    case DWL_MEM_TYPE_VPU_WORKING: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_WORKING"); break;
    case DWL_MEM_TYPE_VPU_WORKING_SPECIAL: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_WORKING_SPECIAL"); break;

    case DWL_MEM_TYPE_VPU_ONLY: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_ONLY"); break;
    case DWL_MEM_TYPE_VPU_CPU: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_VPU_CPU"); break;
    case DWL_MEM_TYPE_DMA_DEVICE_ONLY: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_DEVICE_ONLY"); break;
    case DWL_MEM_TYPE_DMA_HOST_TO_DEVICE: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_HOST_TO_DEVICE"); break;
    case DWL_MEM_TYPE_DMA_DEVICE_TO_HOST: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_DEVICE_TO_HOST"); break;
    case DWL_MEM_TYPE_DMA_HOST_AND_DEVICE: APITRACEDEBUG("PpUnitCfg PPU[%d]# FBC tile# MEM type: %s\n",i, "DWL_MEM_TYPE_DMA_HOST_AND_DEVICE"); break;
    default:
      ASSERT(0);
      break;

  }
  u16 j;
  for (j = 0; j < MAX_ASIC_CORES; j++){
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Reorder buf bus[%d]: %d\n",i, j, ppu_cfg->reorder_buf_bus[j]);
  }
  for (j = 0; j < MAX_ASIC_CORES; j++){
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale buf bus[%d]: %d\n",i, j, ppu_cfg->scale_buf_bus[j]);
  }

  for (j = 0; j < MAX_ASIC_CORES; j++){
    APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale out buf bus[%d]: %d\n",i, j, ppu_cfg->scale_out_buf_bus[j]);
  }

  APITRACEDEBUG("PpUnitCfg PPU[%d]# Reorder size: %d\n",i, ppu_cfg->reorder_size);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale size: %d\n",i, ppu_cfg->scale_size);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Scale out size: %d\n",i, ppu_cfg->scale_out_size);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out YUYV: %d\n",i, ppu_cfg->out_yuyv);
  APITRACEDEBUG("PpUnitCfg PPU[%d]# Out UYVY: %d\n",i, ppu_cfg->out_uyvy);
  }
  }

}


void UpdatePpUnitStride(PpUnitIntConfig *ppu_cfg) {
  u32 ystride = 0, cstride = 0, pp_width = 0;
  if (ppu_cfg->crop2.enabled)
      pp_width = ppu_cfg->crop2.width;
    else
      pp_width = ppu_cfg->scale.width;

  if (ppu_cfg->tiled_e && !ppu_cfg->tile_mode) {
    /* tile4x4 */
    pp_width = NEXT_MULTIPLE(pp_width, 4);
    ystride = NEXT_MULTIPLE(4 * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    cstride = NEXT_MULTIPLE(4 * (ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
  } else if (ppu_cfg->out_yuyv || ppu_cfg->out_uyvy) {
    ystride = cstride = NEXT_MULTIPLE(2 * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
  } else if (ppu_cfg->out_1010) {
    pp_width = ((pp_width + 2) / 3) * 3;
    ystride = NEXT_MULTIPLE(4 * pp_width / 3, ALIGN(ppu_cfg->align));
    cstride = NEXT_MULTIPLE(4 * (ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width / 3, ALIGN(ppu_cfg->align));
  } else if (ppu_cfg->tile_mode) {
    if (ppu_cfg->tile_mode == TILED16x16) {
      pp_width = NEXT_MULTIPLE(pp_width, 16);
      ystride = cstride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width * 24, ALIGN(ppu_cfg->align) * 8) / 8;
    } else if (ppu_cfg->tile_mode == TILED64x64) {
      /* TILED64x64 only support this RGB formats. */
      if (ppu_cfg->rgb_format == PP_OUT_ABGR888 || ppu_cfg->rgb_format == PP_OUT_ARGB888 ||
          ppu_cfg->rgb_format == PP_OUT_A2B10G10R10 || ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 ||
          ppu_cfg->rgb_format == PP_OUT_XBGR888 || ppu_cfg->rgb_format == PP_OUT_XRGB888) {
        // pp_width *= 4;
        // ystride = cstride = pp_width;
        pp_width = NEXT_MULTIPLE(pp_width, 64);
        ystride = cstride = NEXT_MULTIPLE(pp_width * 64 * 4, ALIGN(ppu_cfg->align)) ;
      }
    } else {
      pp_width = NEXT_MULTIPLE(pp_width, 256);
      ystride = cstride = NEXT_MULTIPLE(2 * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    }
  } else if (ppu_cfg->rgb) {
    if (ppu_cfg->rgb_format == PP_OUT_RGB888 || ppu_cfg->rgb_format == PP_OUT_BGR888 ||
        ppu_cfg->rgb_format == PP_OUT_R16G16B16 || ppu_cfg->rgb_format == PP_OUT_B16G16R16) {
      pp_width *= 3;
      ystride = cstride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    } else if (ppu_cfg->rgb_format == PP_OUT_ARGB888 || ppu_cfg->rgb_format == PP_OUT_ABGR888 ||
                ppu_cfg->rgb_format == PP_OUT_RGBA888 || ppu_cfg->rgb_format == PP_OUT_BGRA888 ||
                ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 || ppu_cfg->rgb_format == PP_OUT_A2B10G10R10 ||
                ppu_cfg->rgb_format == PP_OUT_R10G10B10A2 || ppu_cfg->rgb_format == PP_OUT_B10G10R10A2 ||
                ppu_cfg->rgb_format == PP_OUT_XRGB888 || ppu_cfg->rgb_format == PP_OUT_XBGR888) {
      pp_width *= 4;

      ystride = cstride = NEXT_MULTIPLE(pp_width * 8, ALIGN(ppu_cfg->align) * 8) / 8;

    }
  } else if (ppu_cfg->rgb_planar) {
    ystride = cstride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
  } else {
    ystride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    if (ppu_cfg->planar)
      cstride = NEXT_MULTIPLE((ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width / 2 * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    else
      cstride = NEXT_MULTIPLE((ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
  }
  if (ppu_cfg->ystride == 0) {

    ppu_cfg->ystride = ystride;
    ppu_cfg->false_ystride = 1;
  } else {
    if (ppu_cfg->false_ystride) {
      ppu_cfg->ystride = ystride;
    }
  }
  if (ppu_cfg->cstride == 0) {
    ppu_cfg->cstride = cstride;
    ppu_cfg->false_cstride = 1;
  } else {
    if (ppu_cfg->false_cstride) {
      ppu_cfg->cstride = cstride;
    }
  }
}

/* To be moved to a comomn source file for all formats. */
u32 CheckPpUnitConfig(const struct DecHwFeatures *hw_feature,
                            u32 in_width,
                            u32 in_height,
                            u32 interlace,
                            u32 pixel_width,
                            u32 chroma_format,
                            PpUnitIntConfig *ppu_cfg) {
  u32 i = 0;
  u32 pp_width, ystride = 0, cstride = 0;
  PpUnitIntConfig *ppu_cfg_temp = ppu_cfg;
  PrintPpunitConfig(ppu_cfg_temp);
  u32 crop_align = (1 << hw_feature->crop_step_rshift) - 1;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
    if (i >= hw_feature->max_ppu_count && ppu_cfg->enabled) {
      APITRACEERR("The count(%d) of PPU exceeded the max PPU count.\n", i);
      return 1;
      // ppu_cfg->enabled = 0;
    }

    if (!ppu_cfg->enabled) continue;

    if (in_width == 0 && in_height == 0)
      return 0;

    if (!hw_feature->pp_planar_support[i] && ppu_cfg->planar) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PLANAR output is not supuported.\n", i);
      return 1;
    }

    if (!hw_feature->fmt_tile_support[i] && ppu_cfg->tiled_e && !ppu_cfg->tile_mode) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: TILE4x4 output is not supuported.\n", i);
      return 1;
    }

    if (!hw_feature->fmt_supertile_support[i] && ppu_cfg->tile_mode == TILED64x64) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Super_tile output is not supuported.\n", i);
      return 1;
    }

    if (!hw_feature->pp_yuv420_101010_support && ppu_cfg->out_1010) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: 101010 output is not supuported.\n", i);
      return 1;
    }

    if (!hw_feature->fmt_p010_support &&
        (ppu_cfg->out_p010 || ppu_cfg->out_I010 || ppu_cfg->out_L010)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: P010 output is not supuported.\n", i);
      return 1;
    }
    if (!hw_feature->second_crop_support && ppu_cfg->crop2.enabled) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Second crop  is not supuported.\n", i);
      return 1;
    }

#if 0
    if (!hw_feature->fmt_rgb_support[i] && (ppu_cfg->rgb || ppu_cfg->rgb_planar)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: RGB is not supported.\n", i);
      return 1;
    }
#endif
    if (ppu_cfg->planar && ppu_cfg->monochrome) {
      ppu_cfg->planar = 0;
    }
    if (!ppu_cfg->crop.width || !ppu_cfg->crop.height) {
      ppu_cfg->crop.enabled = 0;
    }
    if (!ppu_cfg->crop.enabled) {
      ppu_cfg->crop.x = ppu_cfg->crop.y = 0;
      ppu_cfg->crop.width = in_width;
      ppu_cfg->crop.height = in_height;
      ppu_cfg->crop.set_by_user = 0;
      ppu_cfg->crop.enabled = 1;
    }

    if (!ppu_cfg->scale.width || !ppu_cfg->scale.height) {
      ppu_cfg->scale.enabled = 0;
    }

    /* reset PP0 scaling w/h when enable '-d' and tb.cfg*/
    if (ppu_cfg->scale.ratio_x && ppu_cfg->scale.ratio_y &&
        !ppu_cfg->scale.width && !ppu_cfg->scale.height) {
      ppu_cfg->scale.width = DOWN_SCALE_SIZE(ppu_cfg->crop.width, ppu_cfg->scale.ratio_x);
      ppu_cfg->scale.height = DOWN_SCALE_SIZE(ppu_cfg->crop.height, ppu_cfg->scale.ratio_y);
      /* To resolve last 'if' which sets ppu_cfg->scale.enabled as 0 */
      ppu_cfg->scale.enabled = 1;
    }

    if (!ppu_cfg->scale.enabled) {
      ppu_cfg->scale.width = ppu_cfg->crop.width;
      ppu_cfg->scale.height = ppu_cfg->crop.height;
      ppu_cfg->scale.ratio_x = 1;
      ppu_cfg->scale.ratio_y = 1;
      ppu_cfg->scale.scale_by_ratio = 1;
      ppu_cfg->scale.enabled = 1;
    }

    if (ppu_cfg->planar && pixel_width != 8 &&
        !(ppu_cfg->out_cut_8bits | ppu_cfg->out_p010 | ppu_cfg->out_I010 | ppu_cfg->out_L010)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: When 10bit stream outputs planar, must open one of cut_8_bit/P010/I010/L010.\n", i);
      return 1;
    }

    if (!ppu_cfg->tiled_e && ppu_cfg->tile_mode == TILED64x64) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: When output format is TILED64x64, must enable tiled flag.\n", i);
      return 1;
    }

    if (ppu_cfg->tiled_e && pixel_width != 8 && ppu_cfg->tile_mode && ppu_cfg->tile_mode != TILED64x64 &&
        !(ppu_cfg->out_p010 | ppu_cfg->out_I010 | ppu_cfg->out_L010)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: When 10bit stream outputs in tile mode(except TILED64x64), must open one of P010/I010/L010.\n", i);
      return 1;
    }

    //PP1 can support upsample
    if (chroma_format < ppu_cfg->chroma_format && i != 1) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PP only support downsample.\n", i);
      return 1;
    }

    if ((ppu_cfg->out_yuyv || ppu_cfg->out_uyvy) && (!((ppu_cfg->sub_x == 2) && (ppu_cfg->sub_y == 1)))) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: only 422 support YUYV and UYVY format.\n", i);
      return 1;
    }
    if ((ppu_cfg->out_yuyv || ppu_cfg->out_uyvy) && (pixel_width != 8)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: only 8bit support YUYV and UYVY format.\n", i);
      return 1;
    }
    if (ppu_cfg->chroma_format >= PP_CHROMA_422 && ppu_cfg->monochrome) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: 444/422 output conflict luma only.\n", i);
      return 1;
    }
    if (ppu_cfg->chroma_format >= PP_CHROMA_422 && (ppu_cfg->rgb || ppu_cfg->rgb_planar)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: yuv output and rgb output can not both enabled\n", i);
      return 1;
    }
    if (ppu_cfg->chroma_format == PP_CHROMA_444 && !ppu_cfg->planar) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: 444 only support planar output\n", i);
      return 1;
    }
    if (ppu_cfg->chroma_format == PP_CHROMA_422 && ppu_cfg->planar) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: 422 can not support planar output\n", i);
      return 1;
    }
    if (ppu_cfg->chroma_format == PP_CHROMA_422 && ppu_cfg->tiled_e) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: 422 can not support tiled output\n", i);
      return 1;
    }
#if 0
    if (ppu_cfg->tile_mode && (ppu_cfg->tile_mode != TILED128x2))
      InitFbcParams(ppu_cfg, 0, 0, 0);
#endif
    if (ppu_cfg->crop2.enabled)
      pp_width = ppu_cfg->crop2.width;
    else
      pp_width = ppu_cfg->scale.width;
    if (ppu_cfg->tiled_e && !ppu_cfg->tile_mode) {
      pp_width = NEXT_MULTIPLE(pp_width, 4);
      ystride = NEXT_MULTIPLE(4 * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
      cstride = NEXT_MULTIPLE(4 * (ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    } else if (ppu_cfg->out_yuyv || ppu_cfg->out_uyvy) {
      ystride = cstride = NEXT_MULTIPLE(2 * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    } else if (ppu_cfg->out_1010) {
      pp_width = ((pp_width + 2) / 3) * 3;
      ystride = NEXT_MULTIPLE(4 * pp_width / 3, ALIGN(ppu_cfg->align));
      cstride = NEXT_MULTIPLE(4 * (ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width / 3, ALIGN(ppu_cfg->align));
    } else if (ppu_cfg->tile_mode) {
      if (ppu_cfg->tile_mode == TILED16x16) {
        pp_width = NEXT_MULTIPLE(pp_width, 16);
        ystride = cstride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width * 24, ALIGN(ppu_cfg->align) * 8) / 8;
      } else if (ppu_cfg->tile_mode == TILED64x64) {
        /* TILED64x64 only support this RGB formats. */
        if (ppu_cfg->rgb_format == PP_OUT_ABGR888 || ppu_cfg->rgb_format == PP_OUT_ARGB888 ||
            ppu_cfg->rgb_format == PP_OUT_A2B10G10R10 || ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 ||
            ppu_cfg->rgb_format == PP_OUT_XBGR888 || ppu_cfg->rgb_format == PP_OUT_XRGB888) {
          // pp_width *= 4;
          // ystride = cstride = pp_width;
          pp_width = NEXT_MULTIPLE(pp_width, 64);
          ystride = cstride = NEXT_MULTIPLE(pp_width * 64 * 4, ALIGN(ppu_cfg->align)) ;
        }
      } else {
        pp_width = NEXT_MULTIPLE(pp_width, 256);
        ystride = cstride = NEXT_MULTIPLE(2 * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
      }
    } else if (ppu_cfg->rgb) {
      if (ppu_cfg->rgb_format == PP_OUT_RGB888 || ppu_cfg->rgb_format == PP_OUT_BGR888 ||
          ppu_cfg->rgb_format == PP_OUT_R16G16B16 || ppu_cfg->rgb_format == PP_OUT_B16G16R16) {
        pp_width *= 3;
        ystride = cstride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
      } else if (ppu_cfg->rgb_format == PP_OUT_ARGB888 || ppu_cfg->rgb_format == PP_OUT_ABGR888 ||
                 ppu_cfg->rgb_format == PP_OUT_RGBA888 || ppu_cfg->rgb_format == PP_OUT_BGRA888 ||
                 ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 || ppu_cfg->rgb_format == PP_OUT_A2B10G10R10 ||
                 ppu_cfg->rgb_format == PP_OUT_R10G10B10A2 || ppu_cfg->rgb_format == PP_OUT_B10G10R10A2 ||
                 ppu_cfg->rgb_format == PP_OUT_XRGB888 || ppu_cfg->rgb_format == PP_OUT_XBGR888) {
        pp_width *= 4;

        ystride = cstride = NEXT_MULTIPLE(pp_width * 8, ALIGN(ppu_cfg->align) * 8) / 8;
      }
    } else if (ppu_cfg->rgb_planar) {
      ystride = cstride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    } else {
      ystride = NEXT_MULTIPLE(pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
      if (ppu_cfg->planar)
        cstride = NEXT_MULTIPLE((ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width / 2 * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
      else
        cstride = NEXT_MULTIPLE((ppu_cfg->sub_x == 1 ? 2 : 1) * pp_width * ppu_cfg->pixel_width, ALIGN(ppu_cfg->align) * 8) / 8;
    }
    if (ppu_cfg->ystride == 0) {
#if 0
      if ((ppu_cfg->tiled_e && !ppu_cfg->tile_mode && ((ystride >> hw_feature->pp_tiled_stride_shift) >= PP_MAX_STRIDE)) ||
          (ppu_cfg->tile_mode && ((ystride >> hw_feature->pp_tiled_stride_shift) >= PP_MAX_STRIDE)) ||
          (!ppu_cfg->tile_mode && !ppu_cfg->tiled_e && (ystride >= PP_MAX_STRIDE))) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Too large Y stride.\n", i);
        return 1;
      }
#endif

      ppu_cfg->ystride = ystride;
      ppu_cfg->false_ystride = 1;
    } else {
      if (ppu_cfg->false_ystride) {
        ppu_cfg->ystride = ystride;
      } else {
        if (ppu_cfg->ystride < ystride) {
          return 1;
        }
      }
    }
    if (ppu_cfg->cstride == 0) {
#if 0
      if ((ppu_cfg->tiled_e && !ppu_cfg->tile_mode && ((cstride >> hw_feature->pp_tiled_stride_shift) >= PP_MAX_STRIDE)) ||
          (ppu_cfg->tile_mode && ((cstride >> hw_feature->pp_tiled_stride_shift) >= PP_MAX_STRIDE)) ||
          (!ppu_cfg->tile_mode && !ppu_cfg->tiled_e && (cstride >= PP_MAX_STRIDE))) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Too large C stride.\n", i);
        return 1;
      }
#endif
      ppu_cfg->cstride = cstride;
      ppu_cfg->false_cstride = 1;
    } else {
      if (ppu_cfg->false_cstride) {
        ppu_cfg->cstride = cstride;
      } else {
        if (ppu_cfg->cstride < cstride)
          return 1;
      }
    }

    /* Validate the stride */
    enum StrideUnit unit;
    unit = AdjustStrideUnit(ppu_cfg->ystride, ppu_cfg->cstride);
    if (unit == STRIDE_UNIT_NOT_SUPPORTED) {
      APITRACEERR("%s", "CheckPpUnitConfig# Stride not supported.\n");
      return 1;
    }
    ppu_cfg->unit = unit;

    if (pixel_width > 8 && ppu_cfg->dec400_enabled && !ppu_cfg->out_p010 && !ppu_cfg->out_cut_8bits) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: please open p010 when enables dec400 and output 10bit formats.\n", i);
      return 1;
    }
    if (pixel_width < 12 && (ppu_cfg->out_p012 || ppu_cfg->out_I012)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: 12bit output is not supported for less 12 bit stream.\n", i);
      return 1;
    }
#if 0
    if (pixel_width == 12 && !ppu_cfg->out_p012 && !ppu_cfg->out_I012) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: pp 12bit input only can output 16bit.\n", i);
      return 1;
    }
#endif
    if ((ppu_cfg->rgb || ppu_cfg->rgb_planar)) {
      if (ppu_cfg->stream_pixel_width == 8 &&
         (ppu_cfg->rgb_format == PP_OUT_R16G16B16 ||
          ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 ||
          ppu_cfg->rgb_format == PP_OUT_A2B10G10R10 ||
          ppu_cfg->rgb_format == PP_OUT_R10G10B10A2 ||
          ppu_cfg->rgb_format == PP_OUT_B10G10R10A2 ||
          ppu_cfg->rgb_format == PP_OUT_B16G16R16)) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal RGB parameters.\n", i);
        return 1;
      }
    }
    if (ppu_cfg->rgb_planar) {
      if (ppu_cfg->rgb_format == PP_OUT_ARGB888 || ppu_cfg->rgb_format == PP_OUT_ABGR888 ||
          ppu_cfg->rgb_format == PP_OUT_RGBA888 || ppu_cfg->rgb_format == PP_OUT_BGRA888 ||
          ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 || ppu_cfg->rgb_format == PP_OUT_A2B10G10R10 ||
          ppu_cfg->rgb_format == PP_OUT_R10G10B10A2 || ppu_cfg->rgb_format == PP_OUT_B10G10R10A2 ||
          ppu_cfg->rgb_format == PP_OUT_XRGB888 || ppu_cfg->rgb_format == PP_OUT_XBGR888) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal RGB parameters.\n", i);
        return 1;
      }
    }
    if ((ppu_cfg->crop.x & crop_align) ||
        (ppu_cfg->crop.y & crop_align) ||
        (ppu_cfg->crop.width & crop_align) ||
        (ppu_cfg->crop.height & crop_align) ||
	(ppu_cfg->crop.x > PP_CROP_MAX_X) ||
        (ppu_cfg->crop.y > PP_CROP_MAX_Y) ||
        (ppu_cfg->crop.width  < PP_CROP_MIN_WIDTH && ppu_cfg->crop.width != in_width) ||
        (ppu_cfg->crop.height < PP_CROP_MIN_HEIGHT && ppu_cfg->crop.height != in_height) ||
        (ppu_cfg->crop.x + ppu_cfg->crop.width > in_width) ||
        (ppu_cfg->crop.y + ppu_cfg->crop.height > in_height)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal cropping parameters.\n", i);
      return 1;
    }
    if ((ppu_cfg->crop2.x & crop_align) ||
        (ppu_cfg->crop2.y & crop_align) ||
        (ppu_cfg->crop2.width & crop_align) ||
        (ppu_cfg->crop2.height & crop_align) ||
        (ppu_cfg->crop2.x + ppu_cfg->crop2.width > ppu_cfg->scale.width) ||
        (ppu_cfg->crop2.y + ppu_cfg->crop2.height > ppu_cfg->scale.height) ||
        (ppu_cfg->crop2.enabled && ((ppu_cfg->crop2.width < 48) || (ppu_cfg->scale.height < 48)))) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal cropping parameters.\n", i);
      return 1;
    }
    /* If cropping output greater thatn SCALE_IN_MAX size, no scaling. */
    if (ppu_cfg->crop.width  <= hw_feature->max_pp_out_pic_width[i] &&
        ppu_cfg->crop.height <= hw_feature->max_pp_out_pic_height[i]) {
      if (!ppu_cfg->scale.width || !ppu_cfg->scale.height ||
          (!hw_feature->uscale_support[i] &&
           (ppu_cfg->scale.width > ppu_cfg->crop.width ||
            ppu_cfg->scale.height > ppu_cfg->crop.height)) ||
          (!hw_feature->dscale_support[i] &&
           (ppu_cfg->scale.width < ppu_cfg->crop.width ||
            ppu_cfg->scale.height < ppu_cfg->crop.height)) ||
          ((ppu_cfg->scale.width  > MIN(hw_feature->max_pp_out_pic_width[i],  (hw_feature->pp_support_6x ? 6 : 3) * ppu_cfg->crop.width))) ||
          ((ppu_cfg->scale.height > MIN(hw_feature->max_pp_out_pic_height[i], (hw_feature->pp_support_6x ? 6 : 3) * ppu_cfg->crop.height))) ||
          (ppu_cfg->scale.width  & 1) ||
          (ppu_cfg->scale.height & (interlace ? 3 : 1)) /*||
          (ppu_cfg->scale.width  > ppu_cfg->crop.width &&
           ppu_cfg->scale.height < ppu_cfg->crop.height) ||
          (ppu_cfg->scale.width  < ppu_cfg->crop.width &&
           ppu_cfg->scale.height > ppu_cfg->crop.height)*/) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal scaling output parameters.\n", i);
        return 1;
      }
    } else {
      if ((((ppu_cfg->crop.width != ppu_cfg->scale.width) || (ppu_cfg->crop.height != ppu_cfg->scale.height)) &&
          ((ppu_cfg->scale.width  > MIN(hw_feature->max_pp_out_pic_width[i],  (hw_feature->pp_support_6x ? 6 : 3) * ppu_cfg->crop.width)) ||
          (ppu_cfg->scale.height > MIN(hw_feature->max_pp_out_pic_height[i], (hw_feature->pp_support_6x ? 6 : 3) * ppu_cfg->crop.height)))) ||
          (ppu_cfg->scale.width  & 1) ||
          (ppu_cfg->scale.height & (interlace ? 3 : 1))) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal scaling output parameters.\n", i);
        return 1;
      }
    }

    if ((ppu_cfg->scale.width && ppu_cfg->scale.width < 48) || (ppu_cfg->scale.height && ppu_cfg->scale.height < 48)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal scaling output parameters, scale output width and height must be more than 48.\n", i);
      return 1;
    }

#if 0
    if ((ppu_cfg->crop.width > JPEG_PP_SCALE_IN_MAX_WIDTH || ppu_cfg->crop.height > JPEG_PP_SCALE_IN_MAX_HEIGHT) &&
        (ppu_cfg->scale.width != ppu_cfg->crop.width || ppu_cfg->scale.height != ppu_cfg->crop.height)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal scaling output parameters.\n", i);
      return 1;
    }
#endif
    if (((ppu_cfg->scale.width  > ppu_cfg->crop.width) || (ppu_cfg->scale.height > ppu_cfg->crop.height)) &&
       ((ppu_cfg->pp_filter == PP_VSI_LINEAR) || (ppu_cfg->pp_filter == PP_SPLINE) || (ppu_cfg->pp_filter == PP_BOX))) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Illegal filter type, the filter type can not support upscale.\n", i);
      return 1;
    }

    if (((FDIVI(TOFIX(ppu_cfg->crop.width, 16) + ppu_cfg->scale.width  / 2, ppu_cfg->scale.width)) >= TOFIX(1, 23)) ||
        ((FDIVI(TOFIX(ppu_cfg->crop.height, 16) + ppu_cfg->scale.height  / 2, ppu_cfg->scale.height)) >= TOFIX(1, 23))) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: too large DS ratio due to max supported ratio is 128.\n", i);
      return 1;
    }
    if (ppu_cfg->tile_mode == TILED16x16) {
      if ((ppu_cfg->crop.x & 7) || (ppu_cfg->crop.width & 7) ||
         (ppu_cfg->crop.y & 7) || (ppu_cfg->crop.height & 7)) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC cropping must align to 8. size must align to 8.\n", i);
        return 1;
      }
      #if 0
      if ((ppu_cfg->scale.width != ppu_cfg->crop.width) || (ppu_cfg->scale.height != ppu_cfg->crop.height)) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC TILED16x16 only support no scale.\n", i);
        return 1;
      }
      #endif
      if (ppu_cfg->crop2.enabled) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC TILED16x16 not support second crop.\n", i);
        return 1;
      }
      if (ppu_cfg->scale.width > 8192) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC TILED16x16 max resolution is 8K.\n", i);
        return 1;
      }
    }
    if (ppu_cfg->tile_mode == TILED64x64) {
      if (!ppu_cfg->rgb ||
          !(ppu_cfg->rgb_format == PP_OUT_ARGB888 || ppu_cfg->rgb_format == PP_OUT_ABGR888 ||
            ppu_cfg->rgb_format == PP_OUT_XRGB888 || ppu_cfg->rgb_format == PP_OUT_XBGR888 ||
            ppu_cfg->rgb_format == PP_OUT_A2R10G10B10 || ppu_cfg->rgb_format == PP_OUT_A2B10G10R10)) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: TILED64x64 only support ARGB888 or ABGR888 or XRGB888 or XBGR888 or A2R10G10B10 or A2B10G10R10.\n", i);
        return 1;
      }
      if (!(((ppu_cfg->scale.width == ppu_cfg->crop.width) || (ppu_cfg->scale.width == ppu_cfg->crop.width / 2)) &&
            ((ppu_cfg->scale.height == ppu_cfg->crop.height) || (ppu_cfg->scale.height == ppu_cfg->crop.height / 2)))) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: TILED64x64 only support no scale or 2:1 scale.\n", i);
        return 1;
      }
      ppu_cfg->shaper_enabled = 0;
    }
#if 0
    if (ppu_cfg->tiled_e && (ppu_cfg->tile_mode != TILED128x2)) {
      if ((ppu_cfg->crop.x & 3) || (ppu_cfg->crop.width & 3) ||
          (ppu_cfg->crop.y & 3) || (ppu_cfg->crop.height & 3)) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC cropping must align to 4.\n", i);
        return 1;
      }
      if ((ppu_cfg->tile_mode == TILED16x16) &&
          ((ppu_cfg->scale.width != ppu_cfg->crop.width) || (ppu_cfg->scale.height != ppu_cfg->crop.height))) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC TILED16x16 only support no scale.\n", i);
        return 1;
      }
      if ((ppu_cfg->tile_mode == TILED8x8) &&
          (!(((ppu_cfg->scale.width == ppu_cfg->crop.width) || (ppu_cfg->scale.width == ppu_cfg->crop.width / 2)) &&
            ((ppu_cfg->scale.height == ppu_cfg->crop.height) || (ppu_cfg->scale.height == ppu_cfg->crop.height / 2))))) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC TILED8x8 only support no scale or 2:1 scale.\n", i);
        return 1;
      }
      if (ppu_cfg->tile_mode && !hw_feature->fbc_support) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: FBC not support.\n", i);
        return 1;
      }
    }
#endif
    if (ppu_cfg->tiled_e && !ppu_cfg->tile_mode && ppu_cfg->planar) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PLANAR is not supported with TILED4x4 output.\n", i);
      return 1;
    }
    if ((ppu_cfg->tile_mode == TILED128x2) && (ppu_cfg->scale.height & 3)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: TILED128x2, height must align to 4.\n", i);
      return 1;
    }
    if (ppu_cfg->tiled_e && !ppu_cfg->tile_mode && ppu_cfg->scale.width > hw_feature->max_pp_out_pic_width[i]) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: HW limit: TILED4x4 output size can't be bigger than PP max size.\n", i);
      return 1;
    }
#if 0
    if (ppu_cfg->tiled_e && (ppu_cfg->scale.height%16) != 0) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PP height must be 16 alignment with TILED4x4 output.\n", i);
      return 1;
    }
#endif
    if (ppu_cfg->pp_comp && (!hw_feature->fbc_comp_support[i])) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Don't support enable PFC compression.\n", i);
      return 1;
    }
    if (ppu_cfg->pp_comp && !(ppu_cfg->tile_mode == TILED16x16 || ppu_cfg->tile_mode == TILED32x8)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: When enable PFC compression, must set '--tiled-mode' as one of TILED16x16/TILED32x8.\n", i);
      return 1;
    }
    if (ppu_cfg->pp_comp && (ppu_cfg->tile_mode == TILED16x16 || ppu_cfg->tile_mode == TILED32x8)) {
      if ((ppu_cfg->crop.x & 7) || (ppu_cfg->crop.width & 7) ||
         (ppu_cfg->crop.y & 7) || (ppu_cfg->crop.height & 7)) {
        APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PFC compression cropping must align to 8. size must align to 8.\n", i);
        return 1;
      }
    }
    if (((ppu_cfg->scale.width != ppu_cfg->crop.width) ||
        (ppu_cfg->scale.height != ppu_cfg->crop.height)) &&
        hw_feature->fbc_support && hw_feature->fbc_comp_support[i]) {
      if (((FDIVI(TOFIX(ppu_cfg->crop.width, 16) + ppu_cfg->scale.width / 2, ppu_cfg->scale.width)) != 0x20000) ||
          ((FDIVI(TOFIX(ppu_cfg->crop.height, 16) + ppu_cfg->scale.height / 2, ppu_cfg->scale.height)) != 0x20000)) {
        if ((ppu_cfg->crop.width % 4) || (ppu_cfg->crop.height % 4)) {
          APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Channel that support both PFC and PFC compression, crop size must align to 4.\n", i);
        } else {
          APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Channel that support both PFC and PFC compression, only support 1:1 and 1:2 dscale ratio.\n", i);
        }
        return 1;
      }
    }
    if (ppu_cfg->pp_comp && (ppu_cfg->out_format == PP_OUT_FMT_YUV400 || ppu_cfg->out_format == PP_OUT_FMT_YUV400_P010 ||
        ppu_cfg->out_format == PP_OUT_FMT_YUV400_8BIT || ppu_cfg->out_format == PP_OUT_FMT_YUV400_P012)) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PFC compression not support monochrome output format.\n", i);
      return 1;
    }
    if (hw_feature->fbc_support && hw_feature->fbc_comp_support[i] && ppu_cfg->src_sel_mode != DOWN_ROUND) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: Channel that support both PFC and PFC compression, only support DOWN_ROUND mode for src_sel.\n", i);
      return 1;
    }
    if (ppu_cfg->pp_comp && ppu_cfg->crop2.enabled) {
      APITRACEERR("CheckPpUnitConfig# Illegal param[PP %d]: PFC compression not support crop2.\n", i);
      return 1;
    }
    if (!hw_feature->pp_support_6x && (ppu_cfg->scale.width > ppu_cfg->crop.width*3 ||
        ppu_cfg->scale.height > ppu_cfg->crop.height*3)) {
      ppu_cfg->shaper_enabled = 0;
    }
  }
  InitPpUnitLanczosData(hw_feature, ppu_cfg_temp);
  return 0; //return DEC_OK;
}

void PPSetOneChannelRegs(u32 *pp_regs,
               const struct DecHwFeatures *p_hw_feature,
               PpUnitIntConfig *ppu_cfg,
               addr_t ppu_out_bus_addr,
               u32 mono_chrome,
               u32 bottom_field_flag,
               u32 channel_id) {
  u32 i = channel_id;
  u32 ppb_mode = DEC_DPB_FRAME;
  u32 ppw, ppw_c;
  u32 pp_field_offset = 0;
  u32 pp_field_offset_ch = 0;
#ifndef MODEL_SIMULATION
  const struct DecHwFeatures *hw_feature = p_hw_feature;
#endif
  /* pp common registers*/
  if (ppu_cfg->rgb || ppu_cfg->rgb_planar) {
    SetDecRegister(pp_regs, HWIF_PPX_COLOR_COEFFA2_U, coeff[ppu_cfg->rgb_stan][0]);
    SetDecRegister(pp_regs, HWIF_PPX_COLOR_COEFFA1_U, coeff[ppu_cfg->rgb_stan][0]);
    SetDecRegister(pp_regs, HWIF_PPX_COLOR_COEFFB_U, coeff[ppu_cfg->rgb_stan][1]);
    SetDecRegister(pp_regs, HWIF_PPX_COLOR_COEFFC_U, coeff[ppu_cfg->rgb_stan][2]);
    SetDecRegister(pp_regs, HWIF_PPX_COLOR_COEFFD_U, coeff[ppu_cfg->rgb_stan][3]);
    SetDecRegister(pp_regs, HWIF_PPX_COLOR_COEFFE_U, coeff[ppu_cfg->rgb_stan][4]);
    SetDecRegister(pp_regs, HWIF_YCBCR_RANGE_U, ppu_cfg->video_range);
    SetDecRegister(pp_regs, HWIF_RGB_RANGE_MAX_U, ppu_cfg->range_max);
    SetDecRegister(pp_regs, HWIF_RGB_RANGE_MIN_U, ppu_cfg->range_min);
  }
  SET_ADDR_REG(pp_regs, HWIF_PP_REORDER_TILE_WR_BASE_U, ppu_cfg->reorder_buf_bus[0]);

  SetPpuRegister(pp_regs, HWIF_PPX_CR_FIRST, i, ppu_cfg->cr_first);
  SetPpuRegister(pp_regs, HWIF_PPX_OUT_TILE_E_U, i, ppu_cfg->tiled_e);
  SetPpuRegister(pp_regs, HWIF_PPX_OUT_FORMAT_U, i, ppu_cfg->out_format);
  if (ppu_cfg->rgb_planar)
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_RGB_FMT_U, i, (ppu_cfg->rgb_format + RGB_PLANAR_DIFF));
  else
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_RGB_FMT_U, i, ppu_cfg->rgb_format);
  SetPpuRegister(pp_regs, HWIF_PPX_RGB_PLANAR_U, i, ppu_cfg->rgb_planar);
  SetPpuRegister(pp_regs, HWIF_PPX_OUT_ALPHA_U, i, ppu_cfg->rgb_alpha);
  SetPpuRegister(pp_regs, HWIF_PPX_PAD_SEL_U, i, ppu_cfg->pad_sel);
  SetPpuRegister(pp_regs, HWIF_PPX_SRC_SEL_MODE_U, i, ppu_cfg->src_sel_mode);
  SetPpuRegister(pp_regs, HWIF_PPX_PADY_U, i, ppu_cfg->pad_Y);
  SetPpuRegister(pp_regs, HWIF_PPX_PADU_U, i, ppu_cfg->pad_U);
  SetPpuRegister(pp_regs, HWIF_PPX_PADV_U, i, ppu_cfg->pad_V);
  SetPpuRegister(pp_regs, HWIF_PPX_SHAPER_DIS_U, i, !ppu_cfg->shaper_enabled);
  SetPpuRegister(pp_regs, HWIF_PPX_SHAPER_PAD_E_U, i, !ppu_cfg->shaper_no_pad);
  SetPpuRegister(pp_regs, HWIF_PPX_X_PHASE_NUM_U, i, (ppu_cfg->x_phase_num + 1));
  SetPpuRegister(pp_regs, HWIF_PPX_Y_PHASE_NUM_U, i, (ppu_cfg->y_phase_num + 1));
  SetPpuRegister(pp_regs, HWIF_PPX_OUT_P010_FMT_U, i, (ppu_cfg->out_L010 ? 2 :
                                                    ((ppu_cfg->out_I010 || ppu_cfg->out_I012) ? 1 : 0)));
  SetPpuRegister(pp_regs, HWIF_PPX_LINE_CNT_STRIPE_U, i, ppu_cfg->lc_stripe);
  SetPpuRegister(pp_regs, HWIF_PPX_LINE_CNT_E_U, i, ppu_cfg->lc_stripe > 0);

  {
    /* flexible scale ratio */
    if ((ppu_cfg->scale.width  > ppu_cfg->crop.width) || (ppu_cfg->scale.height > ppu_cfg->crop.height))
      calSecondUpScaleRatio(p_hw_feature, ppu_cfg, GetDecRegister(pp_regs, HWIF_PIC_FIELDMODE_E));
    u32 in_width = ppu_cfg->crop.width;
    u32 in_height = ppu_cfg->crop.height;
    u32 out_width = ppu_cfg->scale.width;
    u32 out_height = ppu_cfg->scale.height;
    u32 out_ratio_x = 1;
    u32 out_ratio_y = 1;
    if ((in_width < out_width) || (in_height < out_height)) {
      out_width = ppu_cfg->out_width;
      out_height = ppu_cfg->out_height;
      out_ratio_x = ppu_cfg->out_ratio_x;
      out_ratio_y = ppu_cfg->out_ratio_y;
    }
    ppw = ppu_cfg->ystride;
    ppw_c = ppu_cfg->cstride;
    SetPpuRegister(pp_regs, HWIF_PPX_CROP_STARTX_U, i,
                    ppu_cfg->crop.x >> p_hw_feature->crop_step_rshift);
    SetPpuRegister(pp_regs, HWIF_PPX_CROP_STARTY_U, i,
                    ppu_cfg->crop.y >> p_hw_feature->crop_step_rshift);
    SetPpuRegister(pp_regs, HWIF_PPX_IN_WIDTH_U, i,
                    ppu_cfg->crop.width >> p_hw_feature->crop_step_rshift);
    SetPpuRegister(pp_regs, HWIF_PPX_IN_HEIGHT_U, i,
                    ppu_cfg->crop.height >> p_hw_feature->crop_step_rshift);

    if (ppu_cfg->crop2.enabled) {
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_STARTX_U, i,
                      ppu_cfg->crop2.x >> p_hw_feature->crop_step_rshift);
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_STARTY_U, i,
                      ppu_cfg->crop2.y >> p_hw_feature->crop_step_rshift);
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_OUT_WIDTH_U, i,
                      ppu_cfg->crop2.width >> p_hw_feature->crop_step_rshift);
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_OUT_HEIGHT_U, i,
                      ppu_cfg->crop2.height >> p_hw_feature->crop_step_rshift);
    } else {
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_STARTX_U, i, 0);
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_STARTY_U, i, 0);
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_OUT_WIDTH_U, i,
                      ppu_cfg->scale.width >> p_hw_feature->crop_step_rshift);
      SetPpuRegister(pp_regs, HWIF_PPX_CROP2_OUT_HEIGHT_U, i,
                      ppu_cfg->scale.height >> p_hw_feature->crop_step_rshift);
    }

    SetPpuRegister(pp_regs, HWIF_PPX_OUT_WIDTH_U, i,
                    ppu_cfg->scale.width);
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_HEIGHT_U, i,
                    ppu_cfg->scale.height);

    if(in_width < out_width) {
      /* upscale */
      u32 W, inv_w;

      SetPpuRegister(pp_regs, HWIF_PPX_HOR_SCALE_MODE_U, i, 1);

      W = FDIVI(TOFIX(out_width, 32), (TOFIX(in_width, 16) + out_width / 2));
      inv_w = FDIVI(TOFIX(in_width, 16) + out_width / 2, out_width);
      if (inv_w % 2) inv_w++;

      SetPpuRegister(pp_regs, HWIF_PPX_WSCALE_RATIO_U, i, W);
      SetPpuRegister(pp_regs, HWIF_PPX_WSCALE_INVRA_U, i, inv_w);
      SetPpuRegister(pp_regs, HWIF_PPX_DUP_HOR_U, i,  out_ratio_x);
    } else if(in_width > out_width) {
      /* downscale */
      u32 W, inv_w;

      SetPpuRegister(pp_regs, HWIF_PPX_HOR_SCALE_MODE_U, i, 2);

      W = FDIVI(TOFIX(out_width, 32), (TOFIX(in_width, 16) + out_width / 2));
      inv_w = FDIVI(TOFIX(in_width, 16) + out_width / 2, out_width);
      if (inv_w % 2) inv_w++;

      SetPpuRegister(pp_regs, HWIF_PPX_WSCALE_RATIO_U, i, W);
      SetPpuRegister(pp_regs, HWIF_PPX_WSCALE_INVRA_U, i, inv_w);
    } else {
      SetPpuRegister(pp_regs, HWIF_PPX_HOR_SCALE_MODE_U, i, 0);
      SetPpuRegister(pp_regs, HWIF_PPX_WSCALE_RATIO_U, i, 0);
      SetPpuRegister(pp_regs, HWIF_PPX_DUP_HOR_U, i, 1);
    }

    if(in_height < out_height) {
      /* upscale */
      u32 H, inv_h;

      SetPpuRegister(pp_regs, HWIF_PPX_VER_SCALE_MODE_U, i, 1);

      H = FDIVI(TOFIX(out_height, 32), (TOFIX(in_height, 16) + out_height / 2));
      inv_h = FDIVI(TOFIX(in_height, 16) + out_height / 2, out_height);
      if (inv_h % 2) inv_h++;

      SetPpuRegister(pp_regs, HWIF_PPX_HSCALE_RATIO_U, i, H);
      SetPpuRegister(pp_regs, HWIF_PPX_HSCALE_INVRA_U, i, inv_h);
      SetPpuRegister(pp_regs, HWIF_PPX_DUP_VER_U, i, out_ratio_y);
    } else if(in_height > out_height) {
      /* downscale */
      u32 H, inv_h;

      SetPpuRegister(pp_regs, HWIF_PPX_VER_SCALE_MODE_U, i, 2);

      H = FDIVI(TOFIX(out_height, 32), (TOFIX(in_height, 16) + out_height / 2));
      inv_h = FDIVI(TOFIX(in_height, 16) + out_height / 2, out_height);
      if (inv_h % 2) inv_h++;

      SetPpuRegister(pp_regs, HWIF_PPX_HSCALE_RATIO_U, i, H);
      SetPpuRegister(pp_regs, HWIF_PPX_HSCALE_INVRA_U, i, inv_h);
    } else {
      SetPpuRegister(pp_regs, HWIF_PPX_VER_SCALE_MODE_U, i, 0);
      SetPpuRegister(pp_regs, HWIF_PPX_HSCALE_INVRA_U, i, 0);
      SetPpuRegister(pp_regs, HWIF_PPX_DUP_VER_U, i, 1);
    }
  }
  if (ppu_cfg->tiled_e && ppu_cfg->tile_mode) {
    SetPpuRegister(pp_regs, HWIF_PPX_TILE_SIZE_U, i, ppu_cfg->tile_mode);
    /*
    SetPpuRegister(pp_regs, VIRTUAL_LEFT_U, i, ppu_cfg->vir_left);
    SetPpuRegister(pp_regs, VIRTUAL_RIGHT_U, i, ppu_cfg->vir_right);
    SetPpuRegister(pp_regs, VIRTUAL_TOP_U, i, ppu_cfg->vir_top);
    SetPpuRegister(pp_regs, VIRTUAL_BOTTOM_U, i, ppu_cfg->vir_bottom);
    SET_PP_ADDR_REG2(pp_regs,
                      PP_FBC_TILE_BASE_U_LSB,
                      PP_FBC_TILE_BASE_U_MSB,
                      i,
                      ppu_cfg->fbc_tile.bus_address + ppu_cfg->fbc_tile_offset);
    */
    //TODO(min): FBC to be supported.
  }
  if (ppu_cfg->pp_comp && (ppu_cfg->tile_mode == TILED16x16 || ppu_cfg->tile_mode == TILED32x8)) {
    SetPpuRegister(pp_regs, HWIF_PPX_COMP_E_U, i, ppu_cfg->pp_comp);
  }
  else {
    SetPpuRegister(pp_regs, HWIF_PPX_COMP_E_U, i, 0);
  }
  if(bottom_field_flag &&
      ppb_mode == DEC_DPB_FRAME) {
    pp_field_offset = ppw;
    pp_field_offset_ch = ppw_c;
  }
  SET_PP_ADDR_REG2(pp_regs,
                  HWIF_PPX_LANCZOS_TBL_BASE_U_LSB,
                  HWIF_PPX_LANCZOS_TBL_BASE_U_MSB,
                  i,
                  ppu_cfg->lanczos_table.bus_address);
  if(p_hw_feature->fbc_comp_support[i] && ((ppu_cfg->crop.width >> 1) == ppu_cfg->scale.width) && ((ppu_cfg->crop.height >> 1) == ppu_cfg->scale.height)) {
    /*width and height downscale 1/2: set 7 filter weight factors*/
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF0_U, i, (i8)*ppu_cfg->lanczos_table.virtual_address); /*low 16 bit*/
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF1_U, i, (i8)(*(ppu_cfg->lanczos_table.virtual_address) >> 16)); /*high 16 bit*/
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF2_U, i, (i8)*(ppu_cfg->lanczos_table.virtual_address + 1));
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF3_U, i, (i8)(*(ppu_cfg->lanczos_table.virtual_address + 1) >> 16));
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF4_U, i, (i8)*(ppu_cfg->lanczos_table.virtual_address + 2));
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF5_U, i, (i8)(*(ppu_cfg->lanczos_table.virtual_address + 2) >> 16));
    SetPpuRegister(pp_regs, HWIF_PPX_DS_COEFF6_U, i, (i8)*(ppu_cfg->lanczos_table.virtual_address + 3));
  }
  SET_PP_ADDR_REG2(pp_regs,
                  HWIF_PPX_SCALE_COLBUF_WR_BASE_U_LSB,
                  HWIF_PPX_SCALE_COLBUF_WR_BASE_U_MSB,
                  i,
                  ppu_cfg->scale_buf_bus[0]);
  SetPpuRegister(pp_regs, HWIF_PPX_Y_FILTER_SIZE_U, i, ppu_cfg->y_filter_size - ppu_cfg->y_filter_offset);
  SetPpuRegister(pp_regs, HWIF_PPX_X_FILTER_SIZE_U, i, ppu_cfg->x_filter_size - ppu_cfg->x_filter_offset);

#if 0
  if (ppu_cfg->tiled_e) {
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_Y_STRIDE, i, (ppw >> p_hw_feature->pp_tiled_stride_shift));
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_C_STRIDE, i, (ppw_c >> p_hw_feature->pp_tiled_stride_shift));
  } else {
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_Y_STRIDE, i, ppw);
    SetPpuRegister(pp_regs, HWIF_PPX_OUT_C_STRIDE, i, ppw_c);
  }
#else
  SetPpuRegister(pp_regs, HWIF_PPX_OUT_Y_STRIDE, i, ppw / stride_unit[ppu_cfg->unit]);
  SetPpuRegister(pp_regs, HWIF_PPX_OUT_C_STRIDE, i, ppw_c / stride_unit[ppu_cfg->unit]);
  SetPpuRegister(pp_regs, HWIF_PPX_STRIDE_UNIT, i, ppu_cfg->unit);
#endif

  if (!ppu_cfg->rgb_planar) {

    if (i == 0 && ppu_cfg->pp_comp && (ppu_cfg->tile_mode == TILED16x16 || ppu_cfg->tile_mode == TILED32x8)) {
      SET_PP_ADDR_REG2(pp_regs,
                  HWIF_PPX_OUT_LU_BASE_U_LSB,
                  HWIF_PPX_OUT_LU_BASE_U_MSB,
                  0,
                  ppu_out_bus_addr + ppu_cfg->header_offset + pp_field_offset);
      SET_PP_ADDR_REG2(pp_regs,
                  HWIF_PPX_OUT_CH_BASE_U_LSB,
                  HWIF_PPX_OUT_CH_BASE_U_MSB,
                  0,
                  ppu_out_bus_addr + ppu_cfg->payload_offset + pp_field_offset_ch);
    }
    else {
      SET_PP_ADDR_REG2(pp_regs,
                  HWIF_PPX_OUT_LU_BASE_U_LSB,
                  HWIF_PPX_OUT_LU_BASE_U_MSB,
                  i,
                  ppu_out_bus_addr + ppu_cfg->luma_offset + pp_field_offset);
    SET_PP_ADDR_REG2(pp_regs,
                  HWIF_PPX_OUT_CH_BASE_U_LSB,
                  HWIF_PPX_OUT_CH_BASE_U_MSB,
                  i,
                  ppu_out_bus_addr + ppu_cfg->chroma_offset + pp_field_offset_ch);
    }

      u32 pp_height = ppu_cfg->crop2.enabled ? ppu_cfg->crop2.height : ppu_cfg->scale.height;
      if (ppu_cfg->planar) {
        SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_B_BASE_U_LSB,
                    HWIF_PPX_OUT_B_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->chroma_offset + pp_field_offset_ch +
                    ppu_cfg->cstride * pp_height / ppu_cfg->sub_y);
      } else {
        SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_B_BASE_U_LSB,
                    HWIF_PPX_OUT_B_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->chroma_offset + pp_field_offset_ch);
      }
  } else {
    u32 offset = NEXT_MULTIPLE(ppw * ppu_cfg->scale.height, PLANE_ALIGNMENT);
    if (ppu_cfg->crop2.enabled)
      offset = NEXT_MULTIPLE(ppw * ppu_cfg->crop2.height, PLANE_ALIGNMENT);
    if (IS_BGR_FORMAT(ppu_cfg->rgb_format)) {
      SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_B_BASE_U_LSB,
                    HWIF_PPX_OUT_B_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->luma_offset + pp_field_offset);
      SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_G_BASE_U_LSB,
                    HWIF_PPX_OUT_G_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->luma_offset + offset + pp_field_offset);
      SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_R_BASE_U_LSB,
                    HWIF_PPX_OUT_R_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->luma_offset + 2 * offset + pp_field_offset);
    } else {
      SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_R_BASE_U_LSB,
                    HWIF_PPX_OUT_R_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->luma_offset + pp_field_offset);
      SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_G_BASE_U_LSB,
                    HWIF_PPX_OUT_G_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->luma_offset + offset + pp_field_offset);
      SET_PP_ADDR_REG2(pp_regs,
                    HWIF_PPX_OUT_B_BASE_U_LSB,
                    HWIF_PPX_OUT_B_BASE_U_MSB,
                    i,
                    ppu_out_bus_addr + ppu_cfg->luma_offset + 2 * offset + pp_field_offset);
    }
  }
}



/*------------------------------------------------------------------------------
    Function name :
    Description   :

    Return type   : None
    Argument      : DecAsicBuffers_t * p_asic_buff
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------

    Function: PPSetRegs

        Functional description:
            Set registers based on pp configurations.

        Input:
            pp_regs     register array base pointer (swreg0)
            p_hw_feature  hw feature struct pointer
            ppu_out_bus_addr  base address of pp buffer
            mono_chrome   whether input picture is mono-chrome
            bottom_field_flag set 1 if current is the bottom field of a picture,
                              otherwise (top field or frame) 0
            align       alignment setting

        Output:

        Returns:

------------------------------------------------------------------------------*/
void PPSetRegs(u32 *pp_regs,
               const struct DecHwFeatures *p_hw_feature,
               PpUnitIntConfig *ppu_cfg,
               addr_t ppu_out_bus_addr,
               u32 mono_chrome,
               u32 bottom_field_flag) {
  u32 i;
  u32 pp_enabled = 0;
  /* registers for each pp unit */
  if (p_hw_feature->max_ppu_count > 0) {

    for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
      pp_enabled |= ppu_cfg->enabled << i;

      if (!ppu_cfg->enabled) continue;
      PPSetOneChannelRegs(pp_regs, p_hw_feature,
                            ppu_cfg,
                            ppu_out_bus_addr,
                            mono_chrome, bottom_field_flag, i);
    }
    SetDecRegister(pp_regs, HWIF_PP_OUT_E_U, pp_enabled);
  }
  /* Set default value 1 for input format in pipeline mode. */
  /* For standalone pp, remember to overwrite it to correct value after PPSetRegs. */
  SetDecRegister(pp_regs, HWIF_PP_IN_FORMAT_U, 1);
}

void PPSetFbcRegs(u32 *pp_regs,
                   const struct DecHwFeatures *p_hw_feature,
                   PpUnitIntConfig *ppu_cfg,
                   u32 tile_enable) {
  u32 i;
  /* registers for each pp unit */
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
    if (!ppu_cfg->enabled) continue;
    if (ppu_cfg->tile_mode == TILED128x2) {
      if (tile_enable) {
        SetPpuRegister(pp_regs, HWIF_PPX_OUT_TILE_E_U, i, 0);
        SetPpuRegister(pp_regs, HWIF_PPX_TILE_SIZE_U, i, 0);
      } else {
        SetPpuRegister(pp_regs, HWIF_PPX_OUT_TILE_E_U, i, ppu_cfg->tiled_e);
        SetPpuRegister(pp_regs, HWIF_PPX_TILE_SIZE_U, i, ppu_cfg->tile_mode);
      }
      SetPpuRegister(pp_regs, HWIF_PPX_OUT_Y_STRIDE, i, ppu_cfg->ystride / stride_unit[ppu_cfg->unit]);
      SetPpuRegister(pp_regs, HWIF_PPX_OUT_C_STRIDE, i, ppu_cfg->cstride / stride_unit[ppu_cfg->unit]);
      SetPpuRegister(pp_regs, HWIF_PPX_STRIDE_UNIT, i, ppu_cfg->unit);
    }
  }
}

u32 PPGetLancozsColumnBufferSize(PpUnitIntConfig *ppu_cfg,
                                 u32 pic_height,
                                 u32 pixel_width,
                                 u32 num_tile_cols) {
  u32 pp_reorder_size = NEXT_MULTIPLE(pic_height, 16) * pixel_width * 36;
  u32 pp_scale_size = LANCZOS_TILE_EDGE_SIZE * sizeof(i32);
  u32 pp_scale_out_size = 0;
  u32 size = 0;
  /* pp reorder col buffer: only one */
  size += pp_reorder_size * num_tile_cols;
  for (u32 i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    ppu_cfg[i].reorder_size = pp_reorder_size;
    ppu_cfg[i].scale_size = pp_scale_size;
    if (ppu_cfg[i].enabled) {
      /* pp scale col buffer: each pp channel */
      size += pp_scale_size * num_tile_cols;
      /*pp scale out col buffer: each pp channel */
      switch (ppu_cfg[i].tile_mode) {
        case TILED16x16:
          if (ppu_cfg[i].pp_comp) {
            /*support max_pic_height: 8K,"* (8192 + 8192 / 2)": luma + chroma, '*2': if can't write done in HW */
            pp_scale_out_size = 3 * LANCZOS_TILE_PPOUT_SIZE;
          } else {
            pp_scale_out_size = 3 * LANCZOS_TILE_PPOUT_SIZE;
          }
          break;
        case TILED64x64:
          /* 8(column) x 8192(max height) x 4(r g b occupies 32bits) x 2(prevent overwrite) : for 8x8 bolck */
          pp_scale_out_size = 4 * LANCZOS_TILE_PPOUT_SIZE;
          break;
        default:
          if (ppu_cfg[i].pp_comp) {
            /*support max_pic_height: 8K,"* (8192 + 8192 / 2)": luma + chroma, '*2': if can't write done in HW */
            pp_scale_out_size = 6 * LANCZOS_TILE_PPOUT_SIZE;
          } else {
            pp_scale_out_size = 1 * LANCZOS_TILE_PPOUT_SIZE;
          }
          break;
      }
      ppu_cfg[i].scale_out_size = pp_scale_out_size;
      size += pp_scale_out_size * num_tile_cols;
    }
  }
  return size;
}

void PPSetLancozsScaleRegs(u32 *pp_regs,
                           const struct DecHwFeatures *p_hw_feature,
                           PpUnitIntConfig *ppu_cfg,
                           u32 core_id) {
  u32 i;
  u32 reorder_set = 0;
  const struct DecHwFeatures *hw_feature = p_hw_feature;

  if (hw_feature->max_ppu_count > 0) {
    for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
      if (!ppu_cfg->enabled) continue;
      if (!reorder_set) {
        SET_ADDR_REG(pp_regs, HWIF_PP_REORDER_TILE_WR_BASE_U, ppu_cfg->reorder_buf_bus[core_id]);
        SET_ADDR_REG(pp_regs, HWIF_PP_REORDER_TILE_RD_BASE_U, ppu_cfg->reorder_buf_bus[core_id]);
        reorder_set = 1;
      }
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_COLBUF_WR_BASE_U_LSB,
                      HWIF_PPX_SCALE_COLBUF_WR_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_buf_bus[core_id]);
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_COLBUF_RD_BASE_U_LSB,
                      HWIF_PPX_SCALE_COLBUF_RD_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_buf_bus[core_id]);
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_OUT_COLBUF_WR_BASE_U_LSB,
                      HWIF_PPX_SCALE_OUT_COLBUF_WR_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_out_buf_bus[core_id]);
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_OUT_COLBUF_RD_BASE_U_LSB,
                      HWIF_PPX_SCALE_OUT_COLBUF_RD_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_out_buf_bus[core_id]);
    }
  }
}

void PPSetLancozsMutiCoreScaleRegs(u32 *pp_regs,
                                   const struct DecHwFeatures *p_hw_feature,
                                   PpUnitIntConfig *ppu_cfg, u32 tile_id) {
  u32 i;
  u32 reorder_set = 0;
  u32 tile_id_wr = 0;
  u32 tile_id_rd = 0;
  const struct DecHwFeatures *hw_feature = p_hw_feature;

  if (hw_feature->max_ppu_count) {
    for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
      if (!ppu_cfg->enabled) continue;
      tile_id_wr = tile_id;
      tile_id_rd = tile_id == 0 ? 0 : (tile_id - 1);
      if (!reorder_set) {
        SET_ADDR_REG(pp_regs, HWIF_PP_REORDER_TILE_WR_BASE_U, ppu_cfg->reorder_buf_bus[0] + tile_id_wr * ppu_cfg->reorder_size);
        SET_ADDR_REG(pp_regs, HWIF_PP_REORDER_TILE_RD_BASE_U, ppu_cfg->reorder_buf_bus[0] + tile_id_rd * ppu_cfg->reorder_size);
        reorder_set = 1;
      }
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_COLBUF_WR_BASE_U_LSB,
                      HWIF_PPX_SCALE_COLBUF_WR_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_buf_bus[0] + tile_id_wr * ppu_cfg->scale_size);
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_COLBUF_RD_BASE_U_LSB,
                      HWIF_PPX_SCALE_COLBUF_RD_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_buf_bus[0] + tile_id_rd * ppu_cfg->scale_size);
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_OUT_COLBUF_WR_BASE_U_LSB,
                      HWIF_PPX_SCALE_OUT_COLBUF_WR_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_out_buf_bus[0] + tile_id_wr * ppu_cfg->scale_out_size);
      SET_PP_ADDR_REG2(pp_regs,
                      HWIF_PPX_SCALE_OUT_COLBUF_RD_BASE_U_LSB,
                      HWIF_PPX_SCALE_OUT_COLBUF_RD_BASE_U_MSB,
                      i,
                      ppu_cfg->scale_out_buf_bus[0] + tile_id_rd * ppu_cfg->scale_out_size);
    }
  }
}

u32 PPCheckMutiCoreSupport(PpUnitIntConfig *ppu_cfg, u32 filter_bypass, u32 sb_size, u32 tile_cols, u8* tile_col_mem) {
  u32 i, j;
  u32 start_tile = 0;
  i32 xDstInSrc;
  i32 scale_ratio_x_inv;
  i32 pos, x_pos;
  u16 xRow[8320] = {0};//8192+128 = 8320
  u32 index = 0;
  u32 last_index = 0;
  u32 first_flag = 1;
  if (ppu_cfg->scale.width >= ppu_cfg->crop.width)
    return 1;
  if (ppu_cfg->pixel_width != 10 && !ppu_cfg->tiled_e)
    return 1;
  u32 *tile_size_start = (u32*)DWLmalloc((tile_cols - 1) * sizeof(u32));
  if (tile_size_start == NULL)
  	return 0;
  u32 *tile_size_end = (u32*)DWLmalloc((tile_cols - 1) * sizeof(u32));
  if (tile_size_end == NULL) {
	free(tile_size_start);
	return 0;
  }
  for (i = 0; i < tile_cols - 1; i++) {
    tile_size_start[i] = (tile_col_mem[i] << sb_size) / 2 - (i == 0 ? 0 : filter_bypass ? 0 : 8);
    tile_size_end[i] = (tile_col_mem[i + 1] << sb_size) / 2 - ((i + 1) == 0 ? 0 : filter_bypass ? 0 : 8);
  }
  for (i = 0; i < tile_cols - 1; i++) {
    if ((ppu_cfg->crop.x / 2 >= tile_size_start[i]) && (ppu_cfg->crop.x / 2 < tile_size_end[i])) {
      start_tile = i + 1;
      break;
    }
  }
  /* x_pos*/
  for (i = 0; i < 8320; i++)
    xRow[i] = 0;
  scale_ratio_x_inv = FDIVI(TOFIX(ppu_cfg->crop.width, 16) + ppu_cfg->scale.width / 2, ppu_cfg->scale.width);
  if (scale_ratio_x_inv % 2) scale_ratio_x_inv++;
  if (ppu_cfg->src_sel_mode == DOWN_ROUND) {
    xDstInSrc = scale_ratio_x_inv - 65536;
  } else if (ppu_cfg->src_sel_mode == NO_ROUND) {
    xDstInSrc = 0;
  } else {
    xDstInSrc = scale_ratio_x_inv;
  }
  pos = xDstInSrc / 2 - scale_ratio_x_inv;
  x_pos = 0;
  for (i = 0; i < ppu_cfg->scale.width; i++) {
    pos += scale_ratio_x_inv;
    x_pos = FLOOR(pos+32768);
    index = x_pos + ppu_cfg->x_filter_size/2;
    if (index == last_index) {
      if (first_flag) {
        first_flag = 0;
        xRow[index] = 0;
      } else {
        xRow[index]++;
      }
      last_index = index;
    } else {
      for (j = last_index + 1; j < index; j++)
        xRow[j] = xRow[last_index];
      if (first_flag) {
        first_flag = 0;
        xRow[index] = 0;
      } else {
        xRow[index] = xRow[last_index] + 1;
      }
      last_index = index;
    }
  }
  for (i = start_tile; i < tile_cols - 1; i++) {
    if (xRow[tile_size_start[i]] == xRow[tile_size_end[i]]) {
      free(tile_size_start);
      free(tile_size_end);
      return 0;
    }
  }
  free(tile_size_start);
  free(tile_size_end);;
  return 1;
}

u32 CalcOnePpUnitFBCHeaderPayloadSize(PpUnitIntConfig *ppu_cfg, u32 header) {
  u32 width_in_block = 0, height_in_block = 0;
  u32 block_payload_size = 0;
  u32 header_size = 0, payload_size = 0;
  u32 pp_width = ppu_cfg->crop2.enabled ? ppu_cfg->crop2.width : ppu_cfg->scale.width;
  u32 pp_height = ppu_cfg->crop2.enabled ? ppu_cfg->crop2.height : ppu_cfg->scale.height;
  if (ppu_cfg->tile_mode == TILED16x16) {
    width_in_block = NEXT_MULTIPLE(pp_width, 16) >> 4;
    height_in_block = NEXT_MULTIPLE(pp_height, 16) >> 4;
  }
  else if (ppu_cfg->tile_mode == TILED32x8) {
    width_in_block = NEXT_MULTIPLE(pp_width, 32) >> 5;
    height_in_block = NEXT_MULTIPLE(pp_height, 8) >> 3;
  }
  if (ppu_cfg->pixel_width == 8)
    block_payload_size = 384;
  else
    block_payload_size = 512;
  header_size = NEXT_MULTIPLE(width_in_block * 16 * height_in_block, 128);
  payload_size = NEXT_MULTIPLE(block_payload_size * width_in_block *height_in_block, 128);
  if (header)
    return header_size;
  else
    return payload_size;
}

u32 CalcOnePpUnitLumaSize(PpUnitIntConfig *ppu_cfg) {
  u32 pp_height = 0, pp_stride = 0, luma_size = 0;
  if (ppu_cfg->tiled_e && !ppu_cfg->tile_mode)
    pp_height = NEXT_MULTIPLE(ppu_cfg->scale.height, 4) / 4;
  else {
    if (ppu_cfg->crop2.enabled)
      pp_height = ppu_cfg->crop2.height;
    else
      pp_height = ppu_cfg->scale.height;
  }
  pp_stride = ppu_cfg->ystride;
  if (ppu_cfg->tile_mode) {
    if (ppu_cfg->tile_mode == TILED16x16) {
      luma_size = pp_stride * (NEXT_MULTIPLE(ppu_cfg->scale.height, 16) / 16);
    } else if (ppu_cfg->tile_mode == TILED64x64) {
      luma_size = pp_stride * (NEXT_MULTIPLE(ppu_cfg->scale.height, 64) / 64);
    } else {
      luma_size = pp_stride * ppu_cfg->scale.height;
    }
  } else if (ppu_cfg->rgb) {
    luma_size = NEXT_MULTIPLE(pp_stride * pp_height, PLANE_ALIGNMENT);
  } else if (ppu_cfg->rgb_planar) {
    luma_size = 3 * NEXT_MULTIPLE(pp_stride * pp_height, PLANE_ALIGNMENT);
  } else
    luma_size = pp_stride * pp_height;

  return luma_size;
}

u32 CalcOnePpUnitChromaSize(PpUnitIntConfig *ppu_cfg, u32 mono_chrome) {
  u32 pp_height = 0, pp_stride = 0, chroma_size = 0;

  if (!ppu_cfg->monochrome && !mono_chrome && !ppu_cfg->rgb &&
      !ppu_cfg->rgb_planar && !ppu_cfg->out_yuyv && !ppu_cfg->out_uyvy &&
      (ppu_cfg->tile_mode != TILED16x16)) {
    if (ppu_cfg->tiled_e && !ppu_cfg->tile_mode) {
      pp_height = NEXT_MULTIPLE(ppu_cfg->scale.height/ppu_cfg->sub_y, 4) / 4;
    } else if (ppu_cfg->crop2.enabled) {
      if (ppu_cfg->planar)
        pp_height = ppu_cfg->crop2.height * (ppu_cfg->sub_y == 1 ? 2 : 1);
      else
        pp_height = ppu_cfg->crop2.height / ppu_cfg->sub_y;
    } else {
      if (ppu_cfg->planar)
        pp_height = ppu_cfg->scale.height * (ppu_cfg->sub_y == 1 ? 2 : 1);
      else
        pp_height = ppu_cfg->scale.height / ppu_cfg->sub_y;
    }
    pp_stride = ppu_cfg->cstride;
    if (ppu_cfg->tile_mode) {
      chroma_size = ppu_cfg->cstride * ppu_cfg->scale.height / 2;
    } else {
      chroma_size = pp_stride * pp_height;
    }
  }
  return chroma_size;
}

u32 CalcOnePpUnitDec400TblSize(PpUnitIntConfig *ppu_cfg, u32 luma_size, u32 chroma_size) {
  u32 dec400_table_size = 0;
#ifdef SUPPORT_DEC400
    if(ppu_cfg->dec400_enabled){
      //luma
      ppu_cfg->dec400_luma_table.logical_size = NEXT_MULTIPLE((luma_size / 256 * 4 + 7) / 8, 16);
      /*always align DEC400_TBL_ALIGN_FACTOR bytes for luma/chroma table to avoid table pading data covers previous data,
      and uv start address align*/
      ppu_cfg->dec400_luma_table.size = NEXT_MULTIPLE(ppu_cfg->dec400_luma_table.logical_size, DEC400_TBL_ALIGN_FACTOR);
      dec400_table_size += ppu_cfg->dec400_luma_table.size;

      //chroma
      ppu_cfg->dec400_chroma_table.logical_size = NEXT_MULTIPLE((chroma_size / 256 * 4 + 7) / 8, 16);
      /*always align DEC400_TBL_ALIGN_FACTOR bytes for luma/chroma table to avoid table pading data covers previous data,
        and uv start address align*/
      ppu_cfg->dec400_chroma_table.size = NEXT_MULTIPLE(ppu_cfg->dec400_chroma_table.logical_size, DEC400_TBL_ALIGN_FACTOR);
      dec400_table_size += ppu_cfg->dec400_chroma_table.size;
    }
#endif
  return dec400_table_size;
}

/* when having dec400, one PP buffer layout is like following
  | luma compressed data | luma table | chroma compressed data | chroma table |
  |--------------------->32 bytes align---------------------------------------|
  |----------------------------------->256 bytes align------------------------|
  |------------------------------------------------------------>32 bytes align|
*/

u32 CalcPpUnitBufferSize(PpUnitIntConfig *ppu_cfg, u32 mono_chrome) {
  u32 i = 0;
  u32 luma_size = 0,chroma_size = 0;
  u32 ext_buffer_size = 0, dec400_table_size = 0;
  u32 header_size = 0, payload_size = 0;
  for (i = 0; i < DEC_MAX_PPU_COUNT; i++, ppu_cfg++) {
    if (!ppu_cfg->enabled) continue;
    //only pp0 support embedded FBC core
    if (i == 0 && ppu_cfg->pp_comp && (ppu_cfg->tile_mode == TILED16x16 || ppu_cfg->tile_mode == TILED32x8)) {
      header_size = CalcOnePpUnitFBCHeaderPayloadSize(ppu_cfg, 1);
      payload_size = CalcOnePpUnitFBCHeaderPayloadSize(ppu_cfg, 0);
      ppu_cfg->header_offset = ext_buffer_size;
      ppu_cfg->payload_offset = ext_buffer_size + header_size;
    }

    luma_size = CalcOnePpUnitLumaSize(ppu_cfg);
    ppu_cfg->hdr_offset = ext_buffer_size + dec400_table_size;
    //buf_off_set_by_user only used in heif format
    if (!ppu_cfg->buf_off_set_by_user) {
      ppu_cfg->luma_offset = ext_buffer_size + dec400_table_size;
      ppu_cfg->chroma_offset = ext_buffer_size + luma_size + dec400_table_size;
    }
    ppu_cfg->luma_size = luma_size;

    chroma_size = CalcOnePpUnitChromaSize(ppu_cfg, mono_chrome);
    ppu_cfg->chroma_size = chroma_size;

    dec400_table_size += CalcOnePpUnitDec400TblSize(ppu_cfg, luma_size, chroma_size);
#ifdef SUPPORT_DEC400
    ppu_cfg->chroma_offset += ppu_cfg->dec400_luma_table.size;
#endif

    //only pp0 support embedded FBC core
    if (i == 0 && ppu_cfg->pp_comp && (ppu_cfg->tile_mode == TILED16x16 || ppu_cfg->tile_mode == TILED32x8)) {
      ext_buffer_size += MAX(NEXT_MULTIPLE(header_size + payload_size, 16), NEXT_MULTIPLE(luma_size + chroma_size, 16));
    }
    else {
      ext_buffer_size += NEXT_MULTIPLE(luma_size + chroma_size, 16);
    }
  }
  return (ext_buffer_size + dec400_table_size);
}

#ifdef SUPPORT_DEC400
void PpFillDec400TblInfo(PpUnitIntConfig *ppu_cfg,
                         const u32 *pp_start_vir_addr,
                         addr_t pp_start_bus_addr,
                         struct DWLLinearMem *luma_tbl,
                         struct DWLLinearMem *chroma_tbl) {

  addr_t dec400_table_luma_offset = 0;
  addr_t dec400_table_chroma_offset = 0;
  /* dec400_luma_table is put into the end region of luma data,
     dec400_chroma_table is put about the end region of chroma data, */
  dec400_table_luma_offset = ppu_cfg->luma_offset + ppu_cfg->luma_size;
  dec400_table_chroma_offset = ppu_cfg->chroma_offset + ppu_cfg->chroma_size;
  luma_tbl->virtual_address = (u32*)((addr_t)pp_start_vir_addr + dec400_table_luma_offset);
  luma_tbl->bus_address = pp_start_bus_addr + dec400_table_luma_offset;
  luma_tbl->logical_size = ppu_cfg->dec400_luma_table.logical_size;;
  luma_tbl->size = ppu_cfg->dec400_luma_table.size;
  if (!ppu_cfg->monochrome) {
    chroma_tbl->virtual_address = (u32*)((addr_t)pp_start_vir_addr + dec400_table_chroma_offset);
    chroma_tbl->bus_address = pp_start_bus_addr + dec400_table_chroma_offset;
    chroma_tbl->logical_size = ppu_cfg->dec400_chroma_table.logical_size;
    chroma_tbl->size = ppu_cfg->dec400_chroma_table.size;
  }
}
#endif

void PpUnitSetIntConfig(PpUnitIntConfig *ppu_int_cfg,
                        PpUnitConfig *ppu_ext_cfg,
                        u32 pixel_width, u32 frame_only,
                        u32 mono_chrome) {
  u32 i;
  u32 chroma_format = 0;
  if (ppu_int_cfg == NULL || ppu_ext_cfg == NULL)
    return;

  for (i = 0; i < DEC_MAX_PPU_COUNT; i++) {
    ppu_int_cfg->enabled = ppu_ext_cfg->enabled;
    if (!ppu_int_cfg->enabled) {
      ppu_ext_cfg++;
      ppu_int_cfg++;
      continue;
    }
    ppu_int_cfg->tiled_e = ppu_ext_cfg->tiled_e;
    ppu_int_cfg->rgb = ppu_ext_cfg->rgb;
    ppu_int_cfg->rgb_planar = ppu_ext_cfg->rgb_planar;
    ppu_int_cfg->cr_first = ppu_ext_cfg->cr_first;
    ppu_int_cfg->shaper_enabled = ppu_ext_cfg->shaper_enabled;
    ppu_int_cfg->shaper_no_pad = ppu_ext_cfg->shaper_no_pad;
    ppu_int_cfg->dec400_enabled = ppu_ext_cfg->dec400_enabled;
    ppu_int_cfg->crop.enabled = ppu_ext_cfg->crop.enabled;
    ppu_int_cfg->crop.set_by_user = ppu_ext_cfg->crop.set_by_user;
    ppu_int_cfg->crop.x = ppu_ext_cfg->crop.x;
    ppu_int_cfg->crop.y = ppu_ext_cfg->crop.y;
    ppu_int_cfg->crop.width = ppu_ext_cfg->crop.width;
    ppu_int_cfg->crop.height = ppu_ext_cfg->crop.height;
    ppu_int_cfg->crop2.enabled = ppu_ext_cfg->crop2.enabled;
    ppu_int_cfg->crop2.x = ppu_ext_cfg->crop2.x;
    ppu_int_cfg->crop2.y = ppu_ext_cfg->crop2.y;
    ppu_int_cfg->crop2.width = ppu_ext_cfg->crop2.width;
    ppu_int_cfg->crop2.height = ppu_ext_cfg->crop2.height;
    ppu_int_cfg->scale.enabled = ppu_ext_cfg->scale.enabled;
    ppu_int_cfg->scale.scale_by_ratio = ppu_ext_cfg->scale.scale_by_ratio;
    ppu_int_cfg->scale.ratio_x = ppu_ext_cfg->scale.ratio_x;
    ppu_int_cfg->scale.ratio_y = ppu_ext_cfg->scale.ratio_y;
    ppu_int_cfg->scale.width = ppu_ext_cfg->scale.width;
    ppu_int_cfg->scale.height = ppu_ext_cfg->scale.height;
    ppu_int_cfg->monochrome = ppu_ext_cfg->monochrome;
    ppu_int_cfg->out_p010 = ppu_ext_cfg->out_p010;
    ppu_int_cfg->out_I010 = ppu_ext_cfg->out_I010;
    ppu_int_cfg->out_L010 = ppu_ext_cfg->out_L010;
    ppu_int_cfg->out_1010 = ppu_ext_cfg->out_1010;
    ppu_int_cfg->out_p012 = ppu_ext_cfg->out_p012;
    ppu_int_cfg->out_I012 = ppu_ext_cfg->out_I012;
    ppu_int_cfg->out_uyvy = ppu_ext_cfg->out_uyvy;
    ppu_int_cfg->out_yuyv = ppu_ext_cfg->out_yuyv;
    ppu_int_cfg->out_cut_8bits = ppu_ext_cfg->out_cut_8bits;
    ppu_int_cfg->planar = ppu_ext_cfg->planar;
    ppu_int_cfg->align = ppu_ext_cfg->align;
    ppu_int_cfg->align_h = ppu_ext_cfg->align_h;
    ppu_int_cfg->ystride = ppu_ext_cfg->ystride;
    ppu_int_cfg->cstride = ppu_ext_cfg->cstride;
    ppu_int_cfg->video_range = ppu_ext_cfg->video_range;
    ppu_int_cfg->tile_mode = ppu_ext_cfg->tile_mode;
    ppu_int_cfg->pp_comp = ppu_ext_cfg->pp_comp;
    ppu_int_cfg->pad_sel = ppu_ext_cfg->pad_sel;
    ppu_int_cfg->src_sel_mode = ppu_ext_cfg->src_sel_mode;
    ppu_int_cfg->pad_Y = ppu_ext_cfg->pad_Y;
    ppu_int_cfg->pad_U = ppu_ext_cfg->pad_U;
    ppu_int_cfg->pad_V = ppu_ext_cfg->pad_V;
    ppu_int_cfg->lc_stripe = ppu_ext_cfg->lc_stripe;
    if (ppu_ext_cfg->buf_off_set_by_user) {
      ppu_int_cfg->luma_offset = ppu_ext_cfg->luma_offset;
      ppu_int_cfg->chroma_offset = ppu_ext_cfg->chroma_offset;
    }
    ppu_int_cfg->buf_off_set_by_user = ppu_ext_cfg->buf_off_set_by_user;
    ppu_int_cfg->out1to1 = ppu_ext_cfg->out1to1;
    if (mono_chrome)
      ppu_int_cfg->chroma_format = chroma_format = 0;
    else
      ppu_int_cfg->chroma_format = chroma_format = ppu_ext_cfg->chroma_format;
    if (ppu_int_cfg->out_uyvy || ppu_int_cfg->out_yuyv)
      ppu_int_cfg->cr_first = 0;
    if (ppu_ext_cfg->rgb || ppu_ext_cfg->rgb_planar) {
      ppu_int_cfg->cr_first = 0;
      switch (ppu_ext_cfg->rgb_format) {
      case DEC_OUT_FRM_RGB888:
        ppu_int_cfg->rgb_format = ppu_ext_cfg->rgb_planar ? PP_OUT_RGB888 : PP_OUT_BGR888;
        break;
      case DEC_OUT_FRM_BGR888:
          ppu_int_cfg->rgb_format = ppu_ext_cfg->rgb_planar ? PP_OUT_BGR888 : PP_OUT_RGB888;
        break;
      case DEC_OUT_FRM_R16G16B16:
        ppu_int_cfg->rgb_format = ppu_ext_cfg->rgb_planar ? PP_OUT_R16G16B16 : PP_OUT_B16G16R16;
        break;
      case DEC_OUT_FRM_B16G16R16:
        ppu_int_cfg->rgb_format = ppu_ext_cfg->rgb_planar ? PP_OUT_B16G16R16 : PP_OUT_R16G16B16;
        break;
      case DEC_OUT_FRM_ABGR888:
        ppu_int_cfg->rgb_format = PP_OUT_ABGR888;
        break;
      case DEC_OUT_FRM_ARGB888:
        ppu_int_cfg->rgb_format = PP_OUT_ARGB888;
        break;
      case DEC_OUT_FRM_A2B10G10R10:
        ppu_int_cfg->rgb_format = PP_OUT_A2B10G10R10;
        break;
      case DEC_OUT_FRM_A2R10G10B10:
        ppu_int_cfg->rgb_format = PP_OUT_A2R10G10B10;
        break;
      case DEC_OUT_FRM_XBGR888:
        ppu_int_cfg->rgb_format = PP_OUT_XBGR888;
        break;
      case DEC_OUT_FRM_XRGB888:
        ppu_int_cfg->rgb_format = PP_OUT_XRGB888;
        break;
      case DEC_OUT_FRM_BGRA888:
        ppu_int_cfg->rgb_format = PP_OUT_BGRA888;
        break;
      case DEC_OUT_FRM_RGBA888:
        ppu_int_cfg->rgb_format = PP_OUT_RGBA888;
        break;
      case DEC_OUT_FRM_B10G10R10A2:
        ppu_int_cfg->rgb_format = PP_OUT_B10G10R10A2;
        break;
      case DEC_OUT_FRM_R10G10B10A2:
        ppu_int_cfg->rgb_format = PP_OUT_R10G10B10A2;
        break;
      default:
        ASSERT(0);
        break;
      }
      ppu_int_cfg->rgb_stan = ppu_ext_cfg->rgb_stan;
      ppu_int_cfg->rgb_alpha = ppu_ext_cfg->rgb_alpha;
      if (ppu_ext_cfg->video_range) {
        if (pixel_width == 8) {
          ppu_int_cfg->range_max = 255;
          ppu_int_cfg->range_min = 0;
        } else {
          ppu_int_cfg->range_max = 1023;
          ppu_int_cfg->range_min = 0;
        }
      } else {
        if (pixel_width == 8) {
          ppu_int_cfg->range_max = 235;
          ppu_int_cfg->range_min = 16;
        } else {
          ppu_int_cfg->range_max = 940;
          ppu_int_cfg->range_min = 64;
        }
      }
    }
    switch (ppu_ext_cfg->pp_filter) {
    case VSI_LINEAR:
      ppu_int_cfg->pp_filter = PP_VSI_LINEAR;
      break;
    case LANCZOS:
      ppu_int_cfg->pp_filter = PP_LANCZOS;
      ppu_int_cfg->x_filter_param = ppu_ext_cfg->x_filter_param;
      ppu_int_cfg->y_filter_param = ppu_ext_cfg->y_filter_param;
      break;
    case NEAREST:
      ppu_int_cfg->pp_filter = PP_NEAREST;
      break;
    case BI_LINEAR:
      ppu_int_cfg->pp_filter = PP_BILINEAR;
      ppu_int_cfg->x_filter_param = 1;
      ppu_int_cfg->y_filter_param = 1;
      break;
    case BICUBIC:
      ppu_int_cfg->pp_filter = PP_BICUBIC;
      ppu_int_cfg->x_filter_param = 2;
      ppu_int_cfg->y_filter_param = 2;
      break;
    case SPLINE:
      ppu_int_cfg->pp_filter = PP_SPLINE;
      ppu_int_cfg->x_filter_param = 2;
      ppu_int_cfg->y_filter_param = 2;
      break;
    case BOX:
      ppu_int_cfg->pp_filter = PP_BOX;
      ppu_int_cfg->x_filter_param = 1;
      ppu_int_cfg->y_filter_param = 1;
      break;
    case FAST_LINEAR:
      ppu_int_cfg->pp_filter = FAST_LINEAR;
      break;
    case FAST_BICUBIC:
      ppu_int_cfg->pp_filter = FAST_BICUBIC;
      break;
    default:
      ASSERT(0);
      break;
    }
    if (chroma_format == PP_CHROMA_420 || chroma_format == PP_CHROMA_400) {
      ppu_int_cfg->sub_x = ppu_int_cfg->sub_y = 2;
    } else if (chroma_format == PP_CHROMA_422) {
      ppu_int_cfg->sub_x = 2;
      ppu_int_cfg->sub_y = 1;
    } else {
      ppu_int_cfg->sub_x = ppu_int_cfg->sub_y = 1;
    }
#if 0
    if (ppu_ext_cfg->tiled_e && pixel_width > 8) {
      if (!ppu_int_cfg->out_p010 &&
          !ppu_int_cfg->out_I010 &&
          !ppu_int_cfg->out_L010) {
        ppu_int_cfg->out_p010 = 1;  /* P010 by default for tile output of 10-bit cases */
      }
      ppu_int_cfg->out_cut_8bits = 0;
    }
#endif
    if (pixel_width == 8 || ppu_int_cfg->rgb || ppu_int_cfg->rgb_planar) {
      ppu_int_cfg->out_cut_8bits = 0;
      ppu_int_cfg->out_p010 = 0;
      ppu_int_cfg->out_1010 = 0;
      ppu_int_cfg->out_I010 = 0;
      ppu_int_cfg->out_L010 = 0;
      ppu_int_cfg->out_p012 = 0;
      ppu_int_cfg->out_I012 = 0;
    }
    if (ppu_int_cfg->out_cut_8bits) {
      ppu_int_cfg->out_p010 = 0;
      ppu_int_cfg->out_1010 = 0;
      ppu_int_cfg->out_I010 = 0;
      ppu_int_cfg->out_L010 = 0;
      ppu_int_cfg->out_p012 = 0;
      ppu_int_cfg->out_I012 = 0;
    }
    if (!IS_PLANAR_RGB(ppu_int_cfg->rgb_format)) {
      ppu_int_cfg->rgb_planar = 0;
    }
    if ((ppu_int_cfg->sub_x == 1) && (ppu_int_cfg->sub_y == 1) && !ppu_int_cfg->planar) {
      ppu_int_cfg->planar = 1;
    }
    if (ppu_int_cfg->rgb || ppu_int_cfg->rgb_planar) {
      ppu_int_cfg->out_format = PP_OUT_FMT_RGB;
    } else if (ppu_int_cfg->out_yuyv) {
      ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_YUYV;
    } else if (ppu_int_cfg->out_uyvy) {
      ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_UYVY;
    } else if (ppu_int_cfg->monochrome || mono_chrome) {
      if (ppu_int_cfg->out_p010 || ppu_int_cfg->out_I010 || ppu_int_cfg->out_L010)
        ppu_int_cfg->out_format = PP_OUT_FMT_YUV400_P010;
      else if (ppu_int_cfg->out_p012 || ppu_int_cfg->out_I012)
        ppu_int_cfg->out_format = PP_OUT_FMT_YUV400_P012;
      else if (ppu_int_cfg->out_cut_8bits)
        ppu_int_cfg->out_format = PP_OUT_FMT_YUV400_8BIT;
      else
        ppu_int_cfg->out_format = PP_OUT_FMT_YUV400;
      ppu_int_cfg->monochrome = 1;
    } else if (ppu_int_cfg->planar) {
      if (ppu_int_cfg->out_p010 || ppu_int_cfg->out_I010 || ppu_int_cfg->out_L010) {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_P010;
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_422_P010;
        else
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_444_P010;
      } else if (ppu_int_cfg->out_p012 || ppu_int_cfg->out_I012) {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_420_P012;
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_422_P012;
        else
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_444_P012;
      } else if (ppu_int_cfg->out_cut_8bits) {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_8BIT;
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_422_8BIT;
        else
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_444_8BIT;
      } else {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUVPACKED; /*422 and 444 not defined packed mode*/
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_422_8BIT;
        else
          ppu_int_cfg->out_format = PP_OUT_FMT_IYUV_444_8BIT;
      }
    } else if (ppu_int_cfg->out_1010) {
      if (chroma_format == PP_CHROMA_420)
        ppu_int_cfg->out_format = PP_OUT_FMT_YUV420_10;
      else if (chroma_format == PP_CHROMA_422)
        ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_10;
    } else {
      //444 only support planar
      if (ppu_int_cfg->out_p010 || ppu_int_cfg->out_I010 || ppu_int_cfg->out_L010) {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV420_P010;
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_P010;
      } else if (ppu_int_cfg->out_cut_8bits) {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV420_8BIT;
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_8BIT;
      } else if (ppu_int_cfg->out_p012 || ppu_int_cfg->out_I012) {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV420_P012;
        else if (chroma_format == PP_CHROMA_422)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_P012;
      } else {
        if (chroma_format == PP_CHROMA_420)
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV420PACKED; /*422 and 444 not defined packed mode*/
        else if (chroma_format == PP_CHROMA_422) {
          ppu_int_cfg->out_format = PP_OUT_FMT_YUV422_8BIT;
          ppu_int_cfg->out_cut_8bits = 1;
        }
      }
    }
    if (!frame_only)
      ppu_int_cfg->tiled_e = 0;
    ppu_int_cfg->pixel_width = (ppu_int_cfg->out_cut_8bits || ((ppu_int_cfg->rgb || ppu_int_cfg->rgb_planar) &&
                                (IS_4PLAN_FORMAT(ppu_int_cfg->rgb_format) || IS_8BITS_FORMAT(ppu_int_cfg->rgb_format))) ||
                                pixel_width == 8) ? 8 :
                               ((ppu_int_cfg->out_p010 || ppu_int_cfg->out_I010 || ppu_int_cfg->out_L010 ||
                                 ppu_int_cfg->out_p012 || ppu_int_cfg->out_I012 ||
                                ((ppu_int_cfg->rgb || ppu_int_cfg->rgb_planar) && IS_16BITS_FORMAT(ppu_int_cfg->rgb_format))) ? 16 : pixel_width);
    ppu_int_cfg->stream_pixel_width = pixel_width;
    ppu_ext_cfg++;
    ppu_int_cfg++;
  }
}

enum DecPictureFormat TransUnitConfig2Format(PpUnitIntConfig *ppu_int_cfg) {
  enum DecPictureFormat output_format = DEC_OUT_FRM_TILED_4X4;

  if (ppu_int_cfg->dec400_enabled) {
    /* DEC400 */
    if (ppu_int_cfg->monochrome) {
      if (ppu_int_cfg->tiled_e)
        output_format = DEC_OUT_FRM_DEC400_400TILE;
      else if (ppu_int_cfg->planar)
        output_format = DEC_OUT_FRM_DEC400_400P;
      else
        output_format = DEC_OUT_FRM_DEC400_400SP;
    } else {
      if (ppu_int_cfg->tiled_e)
        output_format = DEC_OUT_FRM_DEC400_420TILE;
      else if (ppu_int_cfg->planar)
        output_format = DEC_OUT_FRM_DEC400_420P;
      else
        output_format = DEC_OUT_FRM_DEC400_420SP;
    }
  } else if (ppu_int_cfg->tiled_e && ppu_int_cfg->tile_mode) {
    /* FBC style */
    if (ppu_int_cfg->tile_mode == TILED8x8)
      output_format = DEC_OUT_FRM_TILED_8X8;
    else if (ppu_int_cfg->tile_mode == TILED16x16 && !ppu_int_cfg->pp_comp) {
      if (ppu_int_cfg->pixel_width != 8)
        output_format = DEC_OUT_FRM_TILED_16X16_P010;
      else
        output_format = DEC_OUT_FRM_TILED_16X16;
    } else if (ppu_int_cfg->tile_mode == TILED16x16 && ppu_int_cfg->pp_comp) {
      if (ppu_int_cfg->pixel_width != 8)
        output_format = DEC_OUT_FRM_TILED_16X16_P010_COMP;
      else
        output_format = DEC_OUT_FRM_TILED_16X16_COMP;
    } else if (ppu_int_cfg->tile_mode == TILED32x8 && ppu_int_cfg->pp_comp) {
      if (ppu_int_cfg->pixel_width != 8)
        output_format = DEC_OUT_FRM_TILED_32X8_P010_COMP;
      else
        output_format = DEC_OUT_FRM_TILED_32X8_COMP;
    } else if (ppu_int_cfg->tile_mode == TILED128x2) {
      if (!ppu_int_cfg->tile_coded_image) {
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->monochrome)
            output_format = DEC_OUT_FRM_YUV400TILE_128X2_P010;
          else
            output_format = DEC_OUT_FRM_YUV420TILE_128X2_P010;
        } else {
          if (ppu_int_cfg->monochrome)
            output_format = DEC_OUT_FRM_YUV400TILE_128X2;
          else
            output_format = DEC_OUT_FRM_YUV420TILE_128X2;
        }
      } else {
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->monochrome)
            output_format = DEC_OUT_FRM_YUV400_P010;
          else
            output_format = DEC_OUT_FRM_YUV420SP_P010;
        } else {
          if (ppu_int_cfg->monochrome)
            output_format = DEC_OUT_FRM_YUV400;
          else
            output_format = DEC_OUT_FRM_YUV420SP;
        }
      }
    } else if (ppu_int_cfg->tile_mode == TILED64x64) {
      switch (ppu_int_cfg->rgb_format) {
      case PP_OUT_ABGR888:
        output_format = DEC_OUT_FRM_ABGR888_TILED64X64;
        break;
      case PP_OUT_ARGB888:
        output_format = DEC_OUT_FRM_ARGB888_TILED64X64;
        break;
      case PP_OUT_A2B10G10R10:
        output_format = DEC_OUT_FRM_A2B10G10R10_TILED64X64;
        break;
      case PP_OUT_A2R10G10B10:
        output_format = DEC_OUT_FRM_A2R10G10B10_TILED64X64;
        break;
      case PP_OUT_XBGR888:
        output_format = DEC_OUT_FRM_XBGR888_TILED64X64;
        break;
      case PP_OUT_XRGB888:
        output_format = DEC_OUT_FRM_XRGB888_TILED64X64;
        break;
      default:
        ASSERT(0);
        break;
      }
    }
  } else if (ppu_int_cfg->rgb || ppu_int_cfg->rgb_planar) {
    /* RGB */
    switch (ppu_int_cfg->rgb_format) {
    case PP_OUT_RGB888: /* sw_ppx_out_rgb_fmt == 0 */
      if (ppu_int_cfg->rgb_planar)
        output_format = DEC_OUT_FRM_RGB888_P;
      else
        output_format = DEC_OUT_FRM_BGR888;
      break;
    case PP_OUT_BGR888: /* sw_ppx_out_rgb_fmt == 1 */
      if (ppu_int_cfg->rgb_planar)
        output_format = DEC_OUT_FRM_BGR888_P;
      else
        output_format = DEC_OUT_FRM_RGB888;
      break;
    case PP_OUT_R16G16B16: /* sw_ppx_out_rgb_fmt == 2 */
      if (ppu_int_cfg->rgb_planar)
        output_format = DEC_OUT_FRM_R16G16B16_P;
      else
        output_format = DEC_OUT_FRM_B16G16R16;
      break;
    case PP_OUT_B16G16R16: /* sw_ppx_out_rgb_fmt == 3 */
      if (ppu_int_cfg->rgb_planar)
        output_format = DEC_OUT_FRM_B16G16R16_P;
      else
        output_format = DEC_OUT_FRM_R16G16B16;
      break;
    case PP_OUT_ABGR888: /* sw_ppx_out_rgb_fmt == 4 */
        output_format = DEC_OUT_FRM_ABGR888;
      break;
    case PP_OUT_ARGB888: /* sw_ppx_out_rgb_fmt == 5 */
        output_format = DEC_OUT_FRM_ARGB888;
      break;
    case PP_OUT_A2B10G10R10: /* sw_ppx_out_rgb_fmt == 6 */
        output_format = DEC_OUT_FRM_A2B10G10R10;
      break;
    case PP_OUT_A2R10G10B10: /* sw_ppx_out_rgb_fmt == 7 */
        output_format = DEC_OUT_FRM_A2R10G10B10;
      break;
    case PP_OUT_XBGR888: /* sw_ppx_out_rgb_fmt == 8 */
        output_format = DEC_OUT_FRM_XBGR888;
      break;
    case PP_OUT_XRGB888: /* sw_ppx_out_rgb_fmt == 9 */
        output_format = DEC_OUT_FRM_XRGB888;
      break;
    case PP_OUT_BGRA888: /* sw_ppx_out_rgb_fmt == 14 */
        output_format = DEC_OUT_FRM_BGRA888;
      break;
    case PP_OUT_RGBA888: /* sw_ppx_out_rgb_fmt == 15 */
        output_format = DEC_OUT_FRM_RGBA888;
      break;
    case PP_OUT_B10G10R10A2: /* sw_ppx_out_rgb_fmt == 16 */
        output_format = DEC_OUT_FRM_B10G10R10A2;
      break;
    case PP_OUT_R10G10B10A2: /* sw_ppx_out_rgb_fmt == 17 */
        output_format = DEC_OUT_FRM_R10G10B10A2;
      break;
    default:
      ASSERT(0);
      break;
    }
  } else if (ppu_int_cfg->out_yuyv) {
    output_format = DEC_OUT_FRM_YUV422_YUYV;
  } else if (ppu_int_cfg->out_uyvy) {
    output_format = DEC_OUT_FRM_YUV422_UYVY;
  } else { /* YUV */
    if (ppu_int_cfg->monochrome) { /* YUV400 */
      if (ppu_int_cfg->tiled_e) {
        output_format = DEC_OUT_FRM_YUV400TILE;
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->out_cut_8bits)
            output_format = DEC_OUT_FRM_YUV400TILE;
          else if (ppu_int_cfg->out_p010)
            output_format = DEC_OUT_FRM_YUV400TILE_P010;
          else if (ppu_int_cfg->out_I010)
            output_format = DEC_OUT_FRM_YUV400TILE_I010;
          else if (ppu_int_cfg->out_L010)
            output_format = DEC_OUT_FRM_YUV400TILE_L010;
          else if (ppu_int_cfg->out_p012)
            output_format = DEC_OUT_FRM_YUV400TILE_P012;
          else if (ppu_int_cfg->out_I012)
            output_format = DEC_OUT_FRM_YUV400TILE_I012;
          else
            output_format = DEC_OUT_FRM_YUV400TILE_PACK10;
        }
      } else {
        output_format = DEC_OUT_FRM_YUV400;
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->out_cut_8bits) {
            output_format = DEC_OUT_FRM_YUV400;
          } else if(ppu_int_cfg->out_p010) {
            output_format = DEC_OUT_FRM_YUV400_P010;
          } else if (ppu_int_cfg->out_I010) {
            output_format = DEC_OUT_FRM_YUV400_I010;
          } else if (ppu_int_cfg->out_L010) {
            output_format = DEC_OUT_FRM_YUV400_L010;
          } else if(ppu_int_cfg->out_p012) {
            output_format = DEC_OUT_FRM_YUV400_P012;
          } else if (ppu_int_cfg->out_I012) {
            output_format = DEC_OUT_FRM_YUV400_I012;
          } else {
            if (ppu_int_cfg->pixel_width == 10)
              output_format = DEC_OUT_FRM_YUV400_PACK10;
            else
              output_format = DEC_OUT_FRM_YUV400_PACK12;
          }
        }
      }
    } else {
      /* YUV420 */
      u32 cr_first = ppu_int_cfg->cr_first;
      if (ppu_int_cfg->tiled_e) {
        output_format = cr_first ? DEC_OUT_FRM_NV21TILE : DEC_OUT_FRM_YUV420TILE;
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->out_cut_8bits)
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE : DEC_OUT_FRM_YUV420TILE;
          else if (ppu_int_cfg->out_p010)
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE_P010 : DEC_OUT_FRM_YUV420TILE_P010;
          else if (ppu_int_cfg->out_I010)
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE_I010 : DEC_OUT_FRM_YUV420TILE_I010;
          else if (ppu_int_cfg->out_L010)
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE_L010 : DEC_OUT_FRM_YUV420TILE_L010;
          else if (ppu_int_cfg->out_p012)
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE_P012 : DEC_OUT_FRM_YUV420TILE_P012;
          else if (ppu_int_cfg->out_I012)
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE_I012 : DEC_OUT_FRM_YUV420TILE_I012;
          else
            output_format = cr_first ? DEC_OUT_FRM_NV21TILE_PACK10 : DEC_OUT_FRM_YUV420TILE_PACK10;
        }
      } else if (ppu_int_cfg->planar) {
        if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
          output_format = cr_first ? DEC_OUT_FRM_NV21P : DEC_OUT_FRM_YUV420P;
        else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
          output_format = cr_first ? DEC_OUT_FRM_422_NV21P : DEC_OUT_FRM_YUV422P;
        else
          output_format = cr_first ? DEC_OUT_FRM_444_NV21P : DEC_OUT_FRM_YUV444P;
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->out_cut_8bits) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P : DEC_OUT_FRM_YUV420P;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21P : DEC_OUT_FRM_YUV422P;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21P : DEC_OUT_FRM_YUV444P;
          } else if (ppu_int_cfg->out_p010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P_P010 : DEC_OUT_FRM_YUV420P_P010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21P_P010 : DEC_OUT_FRM_YUV422P_P010;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21P_P010 : DEC_OUT_FRM_YUV444P_P010;
          } else if (ppu_int_cfg->out_I010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P_I010 : DEC_OUT_FRM_YUV420P_I010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21P_I010 : DEC_OUT_FRM_YUV422P_I010;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21P_I010 : DEC_OUT_FRM_YUV444P_I010;
          } else if (ppu_int_cfg->out_L010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P_L010 : DEC_OUT_FRM_YUV420P_L010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21P_L010 : DEC_OUT_FRM_YUV422P_L010;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21P_L010 : DEC_OUT_FRM_YUV444P_L010;
           } else if (ppu_int_cfg->out_1010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P_1010 : DEC_OUT_FRM_YUV420P_1010;
            //422.444 not support planar 1010.
          } else if (ppu_int_cfg->out_p012) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P_P012 : DEC_OUT_FRM_YUV420P_P012;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21P_P012 : DEC_OUT_FRM_YUV422P_P012;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21P_P012 : DEC_OUT_FRM_YUV444P_P012;
          } else if (ppu_int_cfg->out_I012) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21P_I012 : DEC_OUT_FRM_YUV420P_I012;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21P_I012 : DEC_OUT_FRM_YUV422P_I012;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21P_I012 : DEC_OUT_FRM_YUV444P_I012;
          } else {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420) {
              if (ppu_int_cfg->pixel_width == 10)
                output_format = cr_first ? DEC_OUT_FRM_NV21P_PACK10 : DEC_OUT_FRM_YUV420P_PACK10;
              else
                output_format = cr_first ? DEC_OUT_FRM_NV21P_PACK12 : DEC_OUT_FRM_YUV420P_PACK12;
            } else if (ppu_int_cfg->chroma_format == PP_CHROMA_422) {
              if (ppu_int_cfg->pixel_width == 10)
                output_format = cr_first ? DEC_OUT_FRM_422_NV21P_PACK10 : DEC_OUT_FRM_YUV422P_PACK10;
              else
                output_format = cr_first ? DEC_OUT_FRM_422_NV21P_PACK12 : DEC_OUT_FRM_YUV422P_PACK12;
            } else {
              if (ppu_int_cfg->pixel_width == 10)
                output_format = cr_first ? DEC_OUT_FRM_444_NV21P_PACK10 : DEC_OUT_FRM_YUV444P_PACK10;
              else
                output_format = cr_first ? DEC_OUT_FRM_444_NV21P_PACK12 : DEC_OUT_FRM_YUV444P_PACK12;
            }
          }
        }
      } else { /* semi-planar */
        if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
          output_format = cr_first ? DEC_OUT_FRM_NV21SP : DEC_OUT_FRM_YUV420SP;
        else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
          output_format = cr_first ? DEC_OUT_FRM_422_NV21SP : DEC_OUT_FRM_YUV422SP;
        else
          output_format = cr_first ? DEC_OUT_FRM_444_NV21SP : DEC_OUT_FRM_YUV444SP;
        if (ppu_int_cfg->pixel_width != 8) {
          if (ppu_int_cfg->out_cut_8bits) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP : DEC_OUT_FRM_YUV420SP;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP : DEC_OUT_FRM_YUV422SP;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21SP : DEC_OUT_FRM_YUV444SP;
          } else if (ppu_int_cfg->out_p010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP_P010 : DEC_OUT_FRM_YUV420SP_P010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_P010 : DEC_OUT_FRM_YUV422SP_P010;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_P010 : DEC_OUT_FRM_YUV444SP_P010;
          } else if (ppu_int_cfg->out_I010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP_I010 : DEC_OUT_FRM_YUV420SP_I010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_I010 : DEC_OUT_FRM_YUV422SP_I010;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_I010 : DEC_OUT_FRM_YUV444SP_I010;
          } else if (ppu_int_cfg->out_L010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP_L010 : DEC_OUT_FRM_YUV420SP_L010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_L010 : DEC_OUT_FRM_YUV422SP_L010;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_L010 : DEC_OUT_FRM_YUV444SP_L010;
          } else if (ppu_int_cfg->out_1010) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP_1010 : DEC_OUT_FRM_YUV420SP_1010;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_1010 : DEC_OUT_FRM_YUV422SP_1010;
          } else if (ppu_int_cfg->out_p012) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP_P012 : DEC_OUT_FRM_YUV420SP_P012;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_P012 : DEC_OUT_FRM_YUV422SP_P012;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_P012 : DEC_OUT_FRM_YUV444SP_P012;
          } else if (ppu_int_cfg->out_I012) {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420)
              output_format = cr_first ? DEC_OUT_FRM_NV21SP_I012 : DEC_OUT_FRM_YUV420SP_I012;
            else if (ppu_int_cfg->chroma_format == PP_CHROMA_422)
              output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_I012 : DEC_OUT_FRM_YUV422SP_I012;
            else
              output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_I012 : DEC_OUT_FRM_YUV444SP_I012;
          } else {
            if (ppu_int_cfg->chroma_format == PP_CHROMA_420) {
              if (ppu_int_cfg->pixel_width == 10)
                output_format = cr_first ? DEC_OUT_FRM_NV21SP_PACK10 : DEC_OUT_FRM_YUV420SP_PACK10;
              else
                output_format = cr_first ? DEC_OUT_FRM_NV21SP_PACK12 : DEC_OUT_FRM_YUV420SP_PACK12;
            } else if (ppu_int_cfg->chroma_format == PP_CHROMA_422) {
              if (ppu_int_cfg->pixel_width == 10)
                output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_PACK10 : DEC_OUT_FRM_YUV422SP_PACK10;
              else
                output_format = cr_first ? DEC_OUT_FRM_422_NV21SP_PACK12 : DEC_OUT_FRM_YUV422SP_PACK12;
            } else {
              if (ppu_int_cfg->pixel_width == 10)
                output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_PACK10 : DEC_OUT_FRM_YUV444SP_PACK10;
              else
                output_format = cr_first ? DEC_OUT_FRM_444_NV21SP_PACK12 : DEC_OUT_FRM_YUV444SP_PACK12;
            }
          }
        }
      }
    }
  }
  return (output_format);
}
