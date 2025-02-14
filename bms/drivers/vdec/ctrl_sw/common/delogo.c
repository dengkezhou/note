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
#include "regdrv.h"
#include "commonconfig.h"
#include "sw_util.h"
#include "sw_debug.h"
#include "delogo.h"

#ifdef DELOGO_SUPPORT

/* check the delogo area is overlaped. */
u32 CheckDelogo(DelogoConfig *delogo_cfg, u32 luma_bit_depth, u32 chroma_bit_depth) {
  u32 luma_max_value = (1 << luma_bit_depth) - 1;
  u32 chroma_max_value = (1 << chroma_bit_depth) - 1;
  if (delogo_cfg[0].Y > luma_max_value || delogo_cfg[0].U > chroma_max_value ||
      delogo_cfg[0].V > chroma_max_value || delogo_cfg[1].Y > luma_max_value ||
      delogo_cfg[1].U > chroma_max_value || delogo_cfg[1].V > chroma_max_value)
    return 1;
  if (delogo_cfg[0].enabled && ((delogo_cfg[0].w > 512 || delogo_cfg[0].w < 8) ||
      (delogo_cfg[0].h > 256 || delogo_cfg[0].h < 4)))
    return 1;
  if (delogo_cfg[1].enabled && (delogo_cfg[1].w < 8 || delogo_cfg[1].h < 4))
    return 1;
  if (delogo_cfg[0].enabled && (delogo_cfg[0].x < 1 || delogo_cfg[0].y < 1))
    return 1;
  if (delogo_cfg[1].enabled && (delogo_cfg[1].x < 1 || delogo_cfg[1].y < 1))
    return 1;
  if (delogo_cfg[0].enabled && ((delogo_cfg[0].x & 0x1) || (delogo_cfg[0].y & 0x1) ||
      (delogo_cfg[0].w & 0x1) || (delogo_cfg[0].h & 0x1)))
    return 1;
  if (delogo_cfg[1].enabled && ((delogo_cfg[1].x & 0x1) || (delogo_cfg[1].y & 0x1) ||
      (delogo_cfg[1].w & 0x1) || (delogo_cfg[1].h & 0x1)))
    return 1;
  if ((delogo_cfg[0].x + delogo_cfg[0].w > delogo_cfg[1].x) &&
      (delogo_cfg[1].x + delogo_cfg[1].w > delogo_cfg[0].x) &&
      (delogo_cfg[0].y + delogo_cfg[0].h > delogo_cfg[1].y) &&
      (delogo_cfg[1].y + delogo_cfg[1].h > delogo_cfg[0].y))
    return 1;
  else
    return 0;
}

void DelogoSetRegs(u32 *pp_regs,
                   const struct DecHwFeatures *p_hw_feature,
                   DelogoConfig *delogo_cfg) {
}

#else

u32 CheckDelogo(DelogoConfig *delogo_cfg, u32 luma_bit_depth, u32 chroma_bit_depth) {
  return 0;
}
void DelogoSetRegs(u32 *pp_regs,
                   const struct DecHwFeatures *p_hw_feature,
                   DelogoConfig *delogo_cfg) {
}

#endif
