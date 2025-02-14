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

#include "h264hwd_cfg.h"
#include "h264hwd_dpb.h"
#include "h264hwd_slice_header.h"
#include "h264hwd_image.h"
#include "h264hwd_util.h"
#include "basetype.h"
#include "dwl.h"
#include "h264hwd_storage.h"
#include "dec_log.h"
#include "errorhandling.h"

/*------------------------------------------------------------------------------
    2. External compiler flags
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
    3. Module defines
------------------------------------------------------------------------------*/

/* Function style implementation for IS_REFERENCE() macro to fix compiler
 * warnings */
static u32 IsReference( const dpbPicture_t *a) {
    return a->status[0] && a->status[0] != EMPTY &&
           a->status[1] && a->status[1] != EMPTY;
}

static u32 IsReferenceField( const dpbPicture_t *a) {
  return (a->status[0] != UNUSED && a->status[0] != EMPTY) ||
         (a->status[1] != UNUSED && a->status[1] != EMPTY);
}

static u32 IsExisting(const dpbPicture_t *a, const u32 f) {
  if(f < FRAME) {
    return  (a->status[f] > NON_EXISTING) &&
            (a->status[f] != EMPTY);
  } else {
    return (a->status[0] > NON_EXISTING) &&
           (a->status[0] != EMPTY) &&
           (a->status[1] > NON_EXISTING) &&
           (a->status[1] != EMPTY);
  }
}

static u32 IsShortTerm(const dpbPicture_t *a, const u32 f) {
  if((f < FRAME)) {
    return (a->status[f] == NON_EXISTING || a->status[f] == SHORT_TERM);
  } else {
    return (a->status[0] == NON_EXISTING || a->status[0] == SHORT_TERM) &&
           (a->status[1] == NON_EXISTING || a->status[1] == SHORT_TERM);
  }
}

static u32 IsShortTermField(const dpbPicture_t *a) {
  return (a->status[0] == NON_EXISTING || a->status[0] == SHORT_TERM) ||
         (a->status[1] == NON_EXISTING || a->status[1] == SHORT_TERM);
}

static u32 IsLongTerm(const dpbPicture_t *a, const u32 f) {
  if(f < FRAME) {
    return a->status[f] == LONG_TERM;
  } else {
    return a->status[0] == LONG_TERM && a->status[1] == LONG_TERM;
  }
}

static u32 IsLongTermField(const dpbPicture_t *a) {
  return (a->status[0] == LONG_TERM) || (a->status[1] == LONG_TERM);
}

static u32 IsUnused(const dpbPicture_t *a, const u32 f) {
  if(f < FRAME) {
    return (a->status[f] == UNUSED);
  } else {
    return (a->status[0] == UNUSED) && (a->status[1] == UNUSED);
  }
}

static void SetStatus(dpbPicture_t *pic,const dpbPictureStatus_e s,
                      const u32 f) {
  if (f < FRAME) {
    pic->status[f] = s;
  } else {
    pic->status[0] = pic->status[1] = s;
  }
}

static void SetPoc(dpbPicture_t *pic, const i32 *poc, const u32 f) {
  if (f < FRAME) {
    pic->pic_order_cnt[f] = poc[f];
  } else {
    pic->pic_order_cnt[0] = poc[0];
    pic->pic_order_cnt[1] = poc[1];
  }
}

static i32 GetPoc(dpbPicture_t *pic) {
  i32 poc0 = (pic->status[0] == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt[0]);
  i32 poc1 = (pic->status[1] == EMPTY ? 0x7FFFFFFF : pic->pic_order_cnt[1]);
  return MIN(poc0,poc1);
}

#define IS_REFERENCE(a,f)       IsReference(&(a))
#define IS_EXISTING(a,f)        IsExisting(&(a),f)
#define IS_REFERENCE_F(a)       IsReferenceField(&(a))
#define IS_SHORT_TERM(a,f)      IsShortTerm(&(a),f)
#define IS_SHORT_TERM_F(a)      IsShortTermField(&(a))
#define IS_LONG_TERM(a,f)       IsLongTerm(&(a),f)
#define IS_LONG_TERM_F(a)       IsLongTermField(&(a))
#define IS_UNUSED(a,f)          IsUnused(&(a),f)
#define SET_STATUS(pic,s,f)     SetStatus(&(pic),s,f)
#define SET_POC(pic,poc,f)      SetPoc(&(pic),poc,f)
#define GET_POC(pic)            GetPoc(&(pic))

#define MAX_NUM_REF_IDX_L0_ACTIVE 16

#define MEM_STAT_DPB 0x1
#define MEM_STAT_OUT 0x2
#define INVALID_MEM_IDX 0xFF

static void DpbBufFree(dpbStorage_t *dpb, u32 i);

#define DISPLAY_SMOOTHING (dpb->tot_buffers > dpb->dpb_size + 1)
typedef i32 (*ComparePicturesCallBack)(const void *ptr1,
                                             const void *ptr2, i32 curr_poc);
/*------------------------------------------------------------------------------
    4. Local function prototypes
------------------------------------------------------------------------------*/

static i32 ComparePictures(const void *ptr1, const void *ptr2, i32 zero);
static i32 ComparePicturesB(const void *ptr1, const void *ptr2, i32 curr_poc);

static i32 CompareFields(const void *ptr1, const void *ptr2);
static i32 CompareFieldsB(const void *ptr1, const void *ptr2, i32 curr_poc);

static u32 Mmcop1(dpbStorage_t * dpb, u32 curr_pic_num, u32 difference_of_pic_nums,
                  u32 pic_struct);

static u32 Mmcop2(dpbStorage_t * dpb, u32 long_term_pic_num, u32 pic_struct);

static u32 Mmcop3(dpbStorage_t * dpb, u32 curr_pic_num, u32 difference_of_pic_nums,
                  u32 long_term_frame_idx, u32 pic_struct);

static u32 Mmcop4(dpbStorage_t * dpb, u32 max_long_term_frame_idx);

static u32 Mmcop5(dpbStorage_t * dpb);

static u32 Mmcop6(dpbStorage_t * dpb, u32 frame_num, i32 * pic_order_cnt,
                  u32 long_term_frame_idx, u32 pic_struct);

static u32 SlidingWindowRefPicMarking(dpbStorage_t * dpb);

static i32 FindDpbPic(dpbStorage_t * dpb, i32 pic_num, u32 is_short_term,
                      u32 field);

static /*@null@ */ dpbPicture_t *FindSmallestPicOrderCnt(dpbStorage_t * dpb);

static u32 OutputPicture(dpbStorage_t * dpb);

static dpbPicture_t *FindSmallestDpbTime(dpbStorage_t * dpb);

/*------------------------------------------------------------------------------

    Function: ComparePictures

        Functional description:
            Function to compare dpb pictures, used by the qsort() function.
            Order of the pictures after sorting shall be as follows:
                1) short term reference pictures starting with the largest
                   pic_num
                2) long term reference pictures starting with the smallest
                   long_term_pic_num
                3) pictures unused for reference but needed for display
                4) other pictures

        Returns:
            -1      pic 1 is greater than pic 2
             0      equal from comparison point of view
             1      pic 2 is greater then pic 1

------------------------------------------------------------------------------*/

i32 ComparePictures(const void *ptr1, const void *ptr2, i32 zero) {

  /* Variables */

  const dpbPicture_t *pic1, *pic2;

  /* Code */

  ASSERT(ptr1);
  ASSERT(ptr2);

  (void)zero;

  pic1 = (dpbPicture_t *) ptr1;
  pic2 = (dpbPicture_t *) ptr2;

  /* both are non-reference pictures, check if needed for display */
  if(!IS_REFERENCE(*pic1, FRAME) && !IS_REFERENCE(*pic2, FRAME)) {
    if(pic1->to_be_displayed && !pic2->to_be_displayed)
      return (-1);
    else if(!pic1->to_be_displayed && pic2->to_be_displayed)
      return (1);
    else
      return (0);
  }
  /* only pic 1 needed for reference -> greater */
  else if(!IS_REFERENCE(*pic2, FRAME))
    return (-1);
  /* only pic 2 needed for reference -> greater */
  else if(!IS_REFERENCE(*pic1, FRAME))
    return (1);
  /* both are short term reference pictures -> check pic_num */
  else if(IS_SHORT_TERM(*pic1, FRAME) && IS_SHORT_TERM(*pic2, FRAME)) {
    if(pic1->pic_num > pic2->pic_num)
      return (-1);
    else if(pic1->pic_num < pic2->pic_num)
      return (1);
    else
      return (0);
  }
  /* only pic 1 is short term -> greater */
  else if(IS_SHORT_TERM(*pic1, FRAME))
    return (-1);
  /* only pic 2 is short term -> greater */
  else if(IS_SHORT_TERM(*pic2, FRAME))
    return (1);
  /* both are long term reference pictures -> check pic_num (contains the
   * long_term_pic_num */
  else {
    if(pic1->pic_num > pic2->pic_num)
      return (1);
    else if(pic1->pic_num < pic2->pic_num)
      return (-1);
    else
      return (0);
  }
}

i32 CompareFields(const void *ptr1, const void *ptr2) {

  /* Variables */

  dpbPicture_t *pic1, *pic2;

  /* Code */

  ASSERT(ptr1);
  ASSERT(ptr2);

  pic1 = (dpbPicture_t *) ptr1;
  pic2 = (dpbPicture_t *) ptr2;

  /* both are non-reference pictures, check if needed for display */
  if(!IS_REFERENCE_F(*pic1) && !IS_REFERENCE_F(*pic2))
    return (0);
  /* only pic 1 needed for reference -> greater */
  else if(!IS_REFERENCE_F(*pic2))
    return (-1);
  /* only pic 2 needed for reference -> greater */
  else if(!IS_REFERENCE_F(*pic1))
    return (1);
  /* both are short term reference pictures -> check pic_num */
  else if(IS_SHORT_TERM_F(*pic1) && IS_SHORT_TERM_F(*pic2)) {
    if(pic1->pic_num > pic2->pic_num)
      return (-1);
    else if(pic1->pic_num < pic2->pic_num)
      return (1);
    else
      return (0);
  }
  /* only pic 1 is short term -> greater */
  else if(IS_SHORT_TERM_F(*pic1))
    return (-1);
  /* only pic 2 is short term -> greater */
  else if(IS_SHORT_TERM_F(*pic2))
    return (1);
  /* both are long term reference pictures -> check pic_num (contains the
   * long_term_pic_num */
  else {
    if(pic1->pic_num > pic2->pic_num)
      return (1);
    else if(pic1->pic_num < pic2->pic_num)
      return (-1);
    else
      return (0);
  }
}

/*------------------------------------------------------------------------------

    Function: ComparePicturesB

        Functional description:
            Function to compare dpb pictures, used by the qsort() function.
            Order of the pictures after sorting shall be as follows:
                1) short term reference pictures with POC less than current POC
                   in descending order
                2) short term reference pictures with POC greater than current
                   POC in ascending order
                3) long term reference pictures starting with the smallest
                   long_term_pic_num

        Returns:
            -1      pic 1 is greater than pic 2
             0      equal from comparison point of view
             1      pic 2 is greater then pic 1

------------------------------------------------------------------------------*/

i32 ComparePicturesB(const void *ptr1, const void *ptr2, i32 curr_poc) {

  /* Variables */

  dpbPicture_t *pic1, *pic2;
  i32 poc1, poc2;

  /* Code */

  ASSERT(ptr1);
  ASSERT(ptr2);

  pic1 = (dpbPicture_t *) ptr1;
  pic2 = (dpbPicture_t *) ptr2;

  /* both are non-reference pictures */
  if(!IS_REFERENCE(*pic1, FRAME) && !IS_REFERENCE(*pic2, FRAME))
    return (0);
  /* only pic 1 needed for reference -> greater */
  else if(!IS_REFERENCE(*pic2, FRAME))
    return (-1);
  /* only pic 2 needed for reference -> greater */
  else if(!IS_REFERENCE(*pic1, FRAME))
    return (1);
  /* both are short term reference pictures -> check pic_order_cnt */
  else if(IS_SHORT_TERM(*pic1, FRAME) && IS_SHORT_TERM(*pic2, FRAME)) {
    poc1 = MIN(pic1->pic_order_cnt[0], pic1->pic_order_cnt[1]);
    poc2 = MIN(pic2->pic_order_cnt[0], pic2->pic_order_cnt[1]);

    if(poc1 < curr_poc && poc2 < curr_poc)
      return (poc1 < poc2 ? 1 : -1);
    else
      return (poc1 < poc2 ? -1 : 1);
  }
  /* only pic 1 is short term -> greater */
  else if(IS_SHORT_TERM(*pic1, FRAME))
    return (-1);
  /* only pic 2 is short term -> greater */
  else if(IS_SHORT_TERM(*pic2, FRAME))
    return (1);
  /* both are long term reference pictures -> check pic_num (contains the
   * long_term_pic_num */
  else {
    if(pic1->pic_num > pic2->pic_num)
      return (1);
    else if(pic1->pic_num < pic2->pic_num)
      return (-1);
    else
      return (0);
  }
}

i32 CompareFieldsB(const void *ptr1, const void *ptr2, i32 curr_poc) {

  /* Variables */

  dpbPicture_t *pic1, *pic2;
  i32 poc1, poc2;

  /* Code */

  ASSERT(ptr1);
  ASSERT(ptr2);

  pic1 = (dpbPicture_t *) ptr1;
  pic2 = (dpbPicture_t *) ptr2;

  /* both are non-reference pictures */
  if(!IS_REFERENCE_F(*pic1) && !IS_REFERENCE_F(*pic2))
    return (0);
  /* only pic 1 needed for reference -> greater */
  else if(!IS_REFERENCE_F(*pic2))
    return (-1);
  /* only pic 2 needed for reference -> greater */
  else if(!IS_REFERENCE_F(*pic1))
    return (1);
  /* both are short term reference pictures -> check pic_order_cnt */
  else if(IS_SHORT_TERM_F(*pic1) && IS_SHORT_TERM_F(*pic2)) {
    poc1 = IS_SHORT_TERM(*pic1, FRAME) ?
           MIN(pic1->pic_order_cnt[0], pic1->pic_order_cnt[1]) :
           IS_SHORT_TERM(*pic1, TOPFIELD) ? pic1->pic_order_cnt[0] :
           pic1->pic_order_cnt[1];
    poc2 = IS_SHORT_TERM(*pic2, FRAME) ?
           MIN(pic2->pic_order_cnt[0], pic2->pic_order_cnt[1]) :
           IS_SHORT_TERM(*pic2, TOPFIELD) ? pic2->pic_order_cnt[0] :
           pic2->pic_order_cnt[1];

    if(poc1 <= curr_poc && poc2 <= curr_poc)
      return (poc1 < poc2 ? 1 : -1);
    else
      return (poc1 < poc2 ? -1 : 1);
  }
  /* only pic 1 is short term -> greater */
  else if(IS_SHORT_TERM_F(*pic1))
    return (-1);
  /* only pic 2 is short term -> greater */
  else if(IS_SHORT_TERM_F(*pic2))
    return (1);
  /* both are long term reference pictures -> check pic_num (contains the
   * long_term_pic_num */
  else {
    if(pic1->pic_num > pic2->pic_num)
      return (1);
    else if(pic1->pic_num < pic2->pic_num)
      return (-1);
    else
      return (0);
  }
}

/*------------------------------------------------------------------------------

    Function: h264bsdReorderRefPicList

        Functional description:
            Function to perform reference picture list reordering based on
            reordering commands received in the slice header. See details
            of the process in the H.264 standard.

        Inputs:
            dpb             pointer to dpb storage structure
            order           pointer to reordering commands
            curr_frame_num    current frame number
            num_ref_idx_active number of active reference indices for current
                            picture

        Outputs:
            dpb             'list' field of the structure reordered

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     if non-existing pictures referred to in the
                           reordering commands

------------------------------------------------------------------------------*/

u32 h264bsdReorderRefPicList(dpbStorage_t * dpb,
                             refPicListReordering_t * order,
                             u32 curr_frame_num, u32 num_ref_idx_active) {

  /* Variables */

  u32 i, j, k, pic_num_pred, ref_idx;
  i32 pic_num, pic_num_no_wrap, index;
  u32 is_short_term;

  /* Code */

  ASSERT(order);
  ASSERT(curr_frame_num <= dpb->max_frame_num);
  ASSERT(num_ref_idx_active <= MAX_NUM_REF_IDX_L0_ACTIVE);

  num_ref_idx_active = MIN(num_ref_idx_active, 16);

  /* set dpb picture numbers for sorting */
  SetPicNums(dpb, curr_frame_num);

  if(!order->ref_pic_list_reordering_flag_l0)
    return (HANTRO_OK);

  ref_idx = 0;
  pic_num_pred = curr_frame_num;

  i = 0;
  while(order->command[i].reordering_of_pic_nums_idc < 3) {
    /* short term */
    if(order->command[i].reordering_of_pic_nums_idc < 2) {
      if(order->command[i].reordering_of_pic_nums_idc == 0) {
        pic_num_no_wrap =
          (i32) pic_num_pred - (i32) order->command[i].abs_diff_pic_num;
        if(pic_num_no_wrap < 0)
          pic_num_no_wrap += (i32) dpb->max_frame_num;
      } else {
        pic_num_no_wrap =
          (i32) (pic_num_pred + order->command[i].abs_diff_pic_num);
        if(pic_num_no_wrap >= (i32) dpb->max_frame_num)
          pic_num_no_wrap -= (i32) dpb->max_frame_num;
      }
      pic_num_pred = (u32) pic_num_no_wrap;
      pic_num = pic_num_no_wrap;
      /*
       * if((u32) pic_num_no_wrap > curr_frame_num)
       * pic_num -= (i32) dpb->max_frame_num;
       */
      is_short_term = HANTRO_TRUE;
    }
    /* long term */
    else {
      pic_num = (i32) order->command[i].long_term_pic_num;
      is_short_term = HANTRO_FALSE;

    }
    /* find corresponding picture from dpb */
    index = FindDpbPic(dpb, pic_num, is_short_term, FRAME);
    if(index < 0 || !IS_EXISTING(dpb->buffer[index], FRAME))
      return (HANTRO_NOK);

    /* shift pictures */
    for(j = num_ref_idx_active; j > ref_idx; j--)
      dpb->list[j] = dpb->list[j - 1];
    /* put picture into the list */
    dpb->list[ref_idx++] = (u32)index;
    /* remove later references to the same picture */
    for(j = k = ref_idx; j <= num_ref_idx_active; j++)
      if(dpb->list[j] != (u32)index)
        dpb->list[k++] = dpb->list[j]; //Mark for klocwork: k<=j <= num_ref_idx_active <= MAX_NUM_REF_IDX_L0_ACTIVE, it's not a problem

    i++;
  }

  return (HANTRO_OK);

}



/*------------------------------------------------------------------------------

    Function: h264bsdReorderRefPicListCheck

        Functional description:
            Function to perform reference picture list reordering based on
            reordering commands received in the slice header. See details
            of the process in the H.264 standard.

        Inputs:
            dpb             pointer to dpb storage structure
            order           pointer to reordering commands
            curr_frame_num    current frame number
            num_ref_idx_active number of active reference indices for current
                            picture

        Outputs:
            dpb             'list' field of the structure reordered

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     if non-existing pictures referred to in the
                           reordering commands

------------------------------------------------------------------------------*/
u32 h264bsdReorderRefPicListCheck(dpbStorage_t * dpb,
                                  refPicListReordering_t * order,
                                  u32 curr_frame_num, u32 num_ref_idx_active,
                                  u32 gaps_in_frame_num_value_allowed_flag,
                                  u32 base_opposite_field_pic,
                                  u32 field_pic_flag) {

  /* Variables */

  u32 i, /*j, k, */pic_num_pred, ref_idx;
  i32 pic_num, pic_num_no_wrap, index;
  u32 is_short_term;
  u32 is_dpb_buffers_valid[16] = {0};

  /* Code */

  ASSERT(order);
  ASSERT(curr_frame_num <= dpb->max_frame_num);

  dpb->invalid_pic_num_count = 0;

#if 0
  if ((!field_pic_flag && (num_ref_idx_active > MAX_NUM_REF_IDX_L0_ACTIVE)) ||
      (field_pic_flag && (num_ref_idx_active > MAX_NUM_REF_IDX_L0_ACTIVE * 2)))
    return (HANTRO_NOK);
#else
  /* For field cases, reorder checking needs reviewing. */
  if (field_pic_flag) return (HANTRO_OK);
#endif

  /* set dpb picture numbers for sorting */
  //SetPicNums(dpb, curr_frame_num);

  if(!order->ref_pic_list_reordering_flag_l0)
    return (HANTRO_OK);

  ref_idx = 0;
  pic_num_pred = curr_frame_num;

  i = 0;
  while(order->command[i].reordering_of_pic_nums_idc < 3) {
    /* short term */
    if(order->command[i].reordering_of_pic_nums_idc < 2) {
      if(order->command[i].reordering_of_pic_nums_idc == 0) {
        pic_num_no_wrap =
          (i32) pic_num_pred - (i32) order->command[i].abs_diff_pic_num;
        if(pic_num_no_wrap < 0)
          pic_num_no_wrap += (i32) dpb->max_frame_num;
      } else {
        pic_num_no_wrap =
          (i32) (pic_num_pred + order->command[i].abs_diff_pic_num);
        if(pic_num_no_wrap >= (i32) dpb->max_frame_num)
          pic_num_no_wrap -= (i32) dpb->max_frame_num;
      }
      pic_num_pred = (u32) pic_num_no_wrap;
      pic_num = pic_num_no_wrap;
      /*
       * if((u32) pic_num_no_wrap > curr_frame_num)
       * pic_num -= (i32) dpb->max_frame_num;
       */
      is_short_term = HANTRO_TRUE;
    }
    /* long term */
    else {
      pic_num = (i32) order->command[i].long_term_pic_num;
      is_short_term = HANTRO_FALSE;
    }
    /* find corresponding picture from dpb */
    index = FindDpbPic(dpb, pic_num, is_short_term, FRAME);
#ifdef SUPPORT_GDR
    if (index < 0) {
      /* P/B GDR frame need reference, but not find. */
      storage_t *storage = (storage_t*) dpb->storage;
      if (storage->is_gdr_frame && !IS_I_SLICE(storage->slice_header->slice_type)) {
        /* gdr frame is not I frame && don't have ref pic: need set fake ref. */
        index = 0;
        SET_STATUS(dpb->buffer[index], SHORT_TERM, FRAME);
        dpb->buffer[index].pic_num = pic_num;
        dpb->buffer[index].frame_num = pic_num;
        dpb->buffer[index].dmv_data = &dpb->dmv_buffers[0];
        /* make sure the reference of first GDR frame has been decoded. */
        {
          char *sync_base =
            (char *) (dpb->buffer[index].dmv_data->virtual_address) - 32;
          u32 sync_size = 32; /* reset all 32 bytes */
          (void) DWLmemset(sync_base, 0xFF, sync_size);
        }
        H264BindDMVBuffer(dpb, dpb->buffer[index].dmv_data);
      }
    }
#endif
    if(index < 0 || !IS_EXISTING(dpb->buffer[index], FRAME)) {
      if (!gaps_in_frame_num_value_allowed_flag &&
          !base_opposite_field_pic &&
          (pic_num == (i32)((dpb->max_frame_num + curr_frame_num - 1) % dpb->max_frame_num)))
        return HANTRO_NOK;
      dpb->pic_num_invalid[dpb->invalid_pic_num_count++] = pic_num;
      //return (HANTRO_NOK);
    } else {
      is_dpb_buffers_valid[index] = 1;
    }

#if 0
    /* shift pictures */
    for(j = num_ref_idx_active; j > ref_idx; j--)
      dpb->list[j] = dpb->list[j - 1];
    /* put picture into the list */
    dpb->list[ref_idx++] = (u32)index;
    /* remove later references to the same picture */
    for(j = k = ref_idx; j <= num_ref_idx_active; j++)
      if(dpb->list[j] != (u32)index)
        dpb->list[k++] = dpb->list[j];
#endif

    i++;
  }

  (void)is_dpb_buffers_valid;
  (void)ref_idx;
  (void)num_ref_idx_active;

  return (HANTRO_OK);

}


/*------------------------------------------------------------------------------

    Function: Mmcop1

        Functional description:
            Function to mark a short-term reference picture unused for
            reference, memory_management_control_operation equal to 1

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     failure, picture does not exist in the buffer

------------------------------------------------------------------------------*/

static u32 Mmcop1(dpbStorage_t * dpb, u32 curr_pic_num, u32 difference_of_pic_nums,
                  u32 pic_struct) {

  /* Variables */

  i32 index, pic_num;
  u32 field = FRAME;

  /* Code */

  ASSERT(curr_pic_num < dpb->max_frame_num);

  if(pic_struct == FRAME) {
    pic_num = (i32) curr_pic_num - (i32) difference_of_pic_nums;
    if(pic_num < 0)
      pic_num += dpb->max_frame_num;
  } else {
    pic_num = (i32) curr_pic_num *2 + 1 - (i32) difference_of_pic_nums;

    if(pic_num < 0)
      pic_num += dpb->max_frame_num * 2;
    field = (pic_num & 1) ^ (u32)(pic_struct == TOPFIELD);
    pic_num /= 2;
  }

  index = FindDpbPic(dpb, pic_num, HANTRO_TRUE, field);
  if(index < 0)
    return (HANTRO_NOK);

  SET_STATUS(dpb->buffer[index], UNUSED, field);
  if(IS_UNUSED(dpb->buffer[index], FRAME)) {
    H264UnBindDMVBuffer(dpb, dpb->buffer[index].dmv_data);
    DpbBufFree(dpb, index);
  }

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: Mmcop2

        Functional description:
            Function to mark a long-term reference picture unused for
            reference, memory_management_control_operation equal to 2

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     failure, picture does not exist in the buffer

------------------------------------------------------------------------------*/

static u32 Mmcop2(dpbStorage_t * dpb, u32 long_term_pic_num, u32 pic_struct) {

  /* Variables */

  i32 index;
  u32 field = FRAME;

  /* Code */

  if(pic_struct != FRAME) {
    field = (long_term_pic_num & 1) ^ (u32)(pic_struct == TOPFIELD);
    long_term_pic_num /= 2;
  }
  index = FindDpbPic(dpb, (i32) long_term_pic_num, HANTRO_FALSE, field);
  if(index < 0)
    return (HANTRO_NOK);

  SET_STATUS(dpb->buffer[index], UNUSED, field);
  if(IS_UNUSED(dpb->buffer[index], FRAME)) {
    H264UnBindDMVBuffer(dpb, dpb->buffer[index].dmv_data);
    DpbBufFree(dpb, index);
  }

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: Mmcop3

        Functional description:
            Function to assing a long_term_frame_idx to a short-term reference
            frame (i.e. to change it to a long-term reference picture),
            memory_management_control_operation equal to 3

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     failure, short-term picture does not exist in the
                           buffer or is a non-existing picture, or invalid
                           long_term_frame_idx given

------------------------------------------------------------------------------*/

static u32 Mmcop3(dpbStorage_t * dpb, u32 curr_pic_num, u32 difference_of_pic_nums,
                  u32 long_term_frame_idx, u32 pic_struct) {

  /* Variables */

  i32 index, pic_num;
  u32 i;
  u32 field = FRAME;

  /* Code */

  ASSERT(dpb);
  ASSERT(curr_pic_num < dpb->max_frame_num);

  if(pic_struct == FRAME) {
    pic_num = (i32) curr_pic_num - (i32) difference_of_pic_nums;
    if(pic_num < 0)
      pic_num += dpb->max_frame_num;
  } else {
    pic_num = (i32) curr_pic_num *2 + 1 - (i32) difference_of_pic_nums;

    if(pic_num < 0)
      pic_num += dpb->max_frame_num * 2;
    field = (pic_num & 1) ^ (u32)(pic_struct == TOPFIELD);
    pic_num /= 2;
  }

  if((dpb->max_long_term_frame_idx == NO_LONG_TERM_FRAME_INDICES) ||
      (long_term_frame_idx > dpb->max_long_term_frame_idx))
    return (HANTRO_NOK);

  /* check if a long term picture with the same long_term_frame_idx already
   * exist and remove it if necessary */
  for(i = 0; i <= dpb->dpb_size; i++)
    if(IS_LONG_TERM_F(dpb->buffer[i]) &&
        (u32) dpb->buffer[i].pic_num == long_term_frame_idx &&
        dpb->buffer[i].frame_num != (u32)pic_num) {
      SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
      if(IS_UNUSED(dpb->buffer[i], FRAME)) {
        H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
        DpbBufFree(dpb, i);
      }
      break;
    }

  index = FindDpbPic(dpb, pic_num, HANTRO_TRUE, field);
  if(index < 0)
    return (HANTRO_NOK);
  if(!IS_EXISTING(dpb->buffer[index], field))
    return (HANTRO_NOK);

  SET_STATUS(dpb->buffer[index], LONG_TERM, field);
  H264BindDMVBuffer(dpb, dpb->buffer[index].dmv_data);
  dpb->buffer[index].pic_num = (i32) long_term_frame_idx;

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: Mmcop4

        Functional description:
            Function to set max_long_term_frame_idx,
            memory_management_control_operation equal to 4

        Returns:
            HANTRO_OK      success

------------------------------------------------------------------------------*/

static u32 Mmcop4(dpbStorage_t * dpb, u32 max_long_term_frame_idx) {

  /* Variables */

  u32 i;

  /* Code */

  dpb->max_long_term_frame_idx = max_long_term_frame_idx;

  for(i = 0; i <= dpb->dpb_size; i++) {
    if(IS_LONG_TERM(dpb->buffer[i], TOPFIELD) &&
        (((u32) dpb->buffer[i].pic_num > max_long_term_frame_idx) ||
         (dpb->max_long_term_frame_idx == NO_LONG_TERM_FRAME_INDICES))) {
      SET_STATUS(dpb->buffer[i], UNUSED, TOPFIELD);
      if(IS_UNUSED(dpb->buffer[i], FRAME)) {
        H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
        DpbBufFree(dpb, i);
      }
    }
    if(IS_LONG_TERM(dpb->buffer[i], BOTFIELD) &&
        (((u32) dpb->buffer[i].pic_num > max_long_term_frame_idx) ||
         (dpb->max_long_term_frame_idx == NO_LONG_TERM_FRAME_INDICES))) {
      SET_STATUS(dpb->buffer[i], UNUSED, BOTFIELD);
      if(IS_UNUSED(dpb->buffer[i], FRAME)) {
        H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
        DpbBufFree(dpb, i);
      }
    }
  }

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: Mmcop5

        Functional description:
            Function to mark all reference pictures unused for reference and
            set max_long_term_frame_idx to NO_LONG_TERM_FRAME_INDICES,
            memory_management_control_operation equal to 5. Function flushes
            the buffer and places all pictures that are needed for display into
            the output buffer.

        Returns:
            HANTRO_OK      success

------------------------------------------------------------------------------*/

static u32 Mmcop5(dpbStorage_t * dpb) {

  /* Variables */

  u32 i;

  /* Code */

  for(i = 0; i < 16; i++) {
    if(IS_REFERENCE_F(dpb->buffer[i])) {
      SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
      H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
      DpbBufFree(dpb, i);
    }
  }

  /* output all pictures */
  while(OutputPicture(dpb) == HANTRO_OK)
    ;
  dpb->num_ref_frames = 0;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
  dpb->prev_ref_frame_num = 0;

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: Mmcop6

        Functional description:
            Function to assign long_term_frame_idx to the current picture,
            memory_management_control_operation equal to 6

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     invalid long_term_frame_idx or no room for current
                           picture in the buffer

------------------------------------------------------------------------------*/

static u32 Mmcop6(dpbStorage_t * dpb, u32 frame_num, i32 * pic_order_cnt,
                  u32 long_term_frame_idx, u32 pic_struct) {

  /* Variables */

  u32 i;

  /* Code */

  ASSERT(frame_num < dpb->max_frame_num);

  if((dpb->max_long_term_frame_idx == NO_LONG_TERM_FRAME_INDICES) ||
      (long_term_frame_idx > dpb->max_long_term_frame_idx))
    return (HANTRO_NOK);

  /* check if a long term picture with the same long_term_frame_idx already
   * exist and remove it if necessary */
  for(i = 0; i <= dpb->dpb_size; i++)
    if(IS_LONG_TERM_F(dpb->buffer[i]) &&
        (u32) dpb->buffer[i].pic_num == long_term_frame_idx &&
        dpb->buffer + i != dpb->current_out) {
      SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
      if(IS_UNUSED(dpb->buffer[i], FRAME)) {
        H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
        DpbBufFree(dpb, i);
      }
      break;
    }

  /* another field of current frame already marked */
  if(pic_struct != FRAME && dpb->current_out->status[(u32)!pic_struct] != EMPTY) {
    dpb->current_out->pic_num = (i32) long_term_frame_idx;
    SET_POC(*dpb->current_out, pic_order_cnt, pic_struct);
    SET_STATUS(*dpb->current_out, LONG_TERM, pic_struct);
    H264BindDMVBuffer(dpb, dpb->current_out->dmv_data);
    return (HANTRO_OK);
  } else if(dpb->num_ref_frames <= dpb->max_ref_frames) {
    dpb->current_out->frame_num = frame_num;
    dpb->current_out->pic_num = (i32) long_term_frame_idx;
    SET_POC(*dpb->current_out, pic_order_cnt, pic_struct);
    SET_STATUS(*dpb->current_out, LONG_TERM, pic_struct);
    H264BindDMVBuffer(dpb, dpb->current_out->dmv_data);
    if(dpb->no_reordering)
      dpb->current_out->to_be_displayed = HANTRO_FALSE;
    else
      dpb->current_out->to_be_displayed = HANTRO_TRUE;
    dpb->num_ref_frames++;
    dpb->fullness++;
    return (HANTRO_OK);
  }
  /* if there is no room, return an error */
  else
    return (HANTRO_NOK);

}

/*------------------------------------------------------------------------------

    Function: h264bsdMarkDecRefPic

        Functional description:
            Function to perform reference picture marking process. This
            function should be called both for reference and non-reference
            pictures.  Non-reference pictures shall have mark pointer set to
            NULL.

        Inputs:
            dpb         pointer to the DPB data structure
            mark        pointer to reference picture marking commands
            image       pointer to current picture to be placed in the buffer
            frame_num    frame number of the current picture
            pic_order_cnt picture order count for the current picture
            is_idr       flag to indicate if the current picture is an
                        IDR picture
            current_pic_id    identifier for the current picture, from the
                            application, stored along with the picture
            num_err_mbs       number of concealed macroblocks in the current
                            picture, stored along with the picture

        Outputs:
            dpb         'buffer' modified, possible output frames placed into
                        'out_buf'

        Returns:
            HANTRO_OK   success
            HANTRO_NOK  failure

------------------------------------------------------------------------------*/

u32 h264bsdMarkDecRefPic(dpbStorage_t * dpb,
                         const decRefPicMarking_t * mark,
                         const image_t * image,
                         u32 frame_num, i32 * pic_order_cnt,
                         u32 is_idr, u32 current_pic_id, u32 num_err_mbs,
                         u32 tiled_mode, u32 pic_code_type ) {

  /* Variables */

  u32 status;
  u32 marked_as_long_term;
  u32 to_be_displayed;
  u32 second_field = 0;
  u32 error_ratio = 0;
  storage_t *storage = dpb->storage;

  /* Code */

  ASSERT(dpb);
  ASSERT(mark || !is_idr);
  /* removed for XXXXXXXX compliance */
  /*
   * ASSERT(!is_idr ||
   * (frame_num == 0 &&
   * image->pic_struct == FRAME ? MIN(pic_order_cnt[0],pic_order_cnt[1]) == 0 :
   * pic_order_cnt[image->pic_struct] == 0));
   */
  ASSERT(frame_num < dpb->max_frame_num);
  ASSERT(image->pic_struct <= FRAME);

  if(image->pic_struct < FRAME) {
    ASSERT(dpb->current_out->status[image->pic_struct] == EMPTY);
    if(dpb->current_out->status[(u32)!image->pic_struct] != EMPTY) {
      second_field = 1;
      DPB_TRACE("MARKING SECOND FIELD %d\n",
                   dpb->current_out - dpb->buffer);
    } else {
      DPB_TRACE("MARKING FIRST FIELD %d\n",
                   dpb->current_out - dpb->buffer);
    }
  } else {
    DPB_TRACE("MARKING FRAME %d\n", dpb->current_out - dpb->buffer);
  }

  dpb->no_output = DISPLAY_SMOOTHING && second_field && !dpb->delayed_out;

  if(!second_field && image->data != dpb->current_out->data) {
    APITRACEERR("%s\n","TRYING TO MARK NON-ALLOCATED IMAGE");
    return (HANTRO_NOK);
  }

  dpb->last_contains_mmco5 = HANTRO_FALSE;
  status = HANTRO_OK;

  to_be_displayed = dpb->no_reordering ? HANTRO_FALSE : HANTRO_TRUE;

  /* non-reference picture, stored for display reordering purposes */
  if(mark == NULL) {
    dpbPicture_t *current_out = dpb->current_out;

    SET_STATUS(*current_out, UNUSED, image->pic_struct);
    if(IS_UNUSED(*current_out, FRAME)) {
      H264UnBindDMVBuffer(dpb, current_out->dmv_data);
    }
    current_out->frame_num = frame_num;
    current_out->pic_num = (i32) frame_num;
    SET_POC(*current_out, pic_order_cnt, image->pic_struct);
    /* TODO: if current pic is first field of pic and will be output ->
     * output will only contain first field, second (if present) will
     * be output separately. This shall be fixed when field mode output
     * is implemented */
    if(!dpb->no_reordering && (!second_field ||   /* first field of frame */
                               (!dpb->delayed_out &&
                                !current_out->
                                to_be_displayed) /* first already output */ ))
      dpb->fullness++;
    current_out->to_be_displayed = to_be_displayed;
  }
  /* IDR picture */
  else if(is_idr) {
    dpbPicture_t *current_out = dpb->current_out;

    /* Reset the status of idr picture in case of errorneous stream */
    SET_STATUS(*current_out, EMPTY, FRAME);
    H264UnBindDMVBuffer(dpb, dpb->current_out->dmv_data);
    current_out->to_be_displayed = 0;

    /* flush the buffer */
    (void) Mmcop5(dpb);
    /* added for XXXXXXXX compliance */
    dpb->prev_ref_frame_num = frame_num;
    /* if no_output_of_prior_pics_flag was set -> the pictures preceding the
     * IDR picture shall not be output -> set output buffer empty */
    if(mark->no_output_of_prior_pics_flag) {
      RemoveTempPpOutputAll(dpb);
      RemoveTempOutputAll(dpb->fb_list);

      dpb->num_out = 0;
      dpb->out_index_w = dpb->out_index_r = 0;
    }

    if(mark->long_term_reference_flag) {
      SET_STATUS(*current_out, LONG_TERM, image->pic_struct);
      H264BindDMVBuffer(dpb, dpb->current_out->dmv_data);
      dpb->max_long_term_frame_idx = dpb->max_ref_frames - 1;
    } else {
      SET_STATUS(*current_out, SHORT_TERM, image->pic_struct);
      H264BindDMVBuffer(dpb, dpb->current_out->dmv_data);
      dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
    }
    /* changed for XXXXXXXX compliance */
    current_out->frame_num = frame_num;
    current_out->pic_num = (i32) frame_num;
    SET_POC(*current_out, pic_order_cnt, image->pic_struct);
    current_out->to_be_displayed = to_be_displayed;
    dpb->fullness = 1;
    dpb->num_ref_frames = 1;
  }
  /* reference picture */
  else {
    marked_as_long_term = HANTRO_FALSE;
    if(mark->adaptive_ref_pic_marking_mode_flag) {
      const memoryManagementOperation_t *operation;

      operation = mark->operation;    /* = &mark->operation[0] */

      while(operation->memory_management_control_operation) {

        switch (operation->memory_management_control_operation) {
        case 1:
          (void)   Mmcop1(dpb,
                          frame_num, operation->difference_of_pic_nums,
                          image->pic_struct);
          break;

        case 2:
          (void)   Mmcop2(dpb, operation->long_term_pic_num,
                          image->pic_struct);
          break;

        case 3:
          (void)   Mmcop3(dpb,
                          frame_num,
                          operation->difference_of_pic_nums,
                          operation->long_term_frame_idx,
                          image->pic_struct);
          break;

        case 4:
          status = Mmcop4(dpb, operation->max_long_term_frame_idx);
          break;

        case 5:
          status = Mmcop5(dpb);
          dpb->last_contains_mmco5 = HANTRO_TRUE;
          frame_num = 0;
          break;

        case 6:
          status = Mmcop6(dpb,
                          frame_num,
                          pic_order_cnt, operation->long_term_frame_idx,
                          image->pic_struct);
          if(status == HANTRO_OK)
            marked_as_long_term = HANTRO_TRUE;
          break;

        default:   /* invalid memory management control operation */
          status = HANTRO_NOK;
          break;
        }

        if(status != HANTRO_OK) {
          break;
        }

        operation++;    /* = &mark->operation[i] */
      }
      /* all the marking done, check num_ref_frames */
      if(dpb->num_ref_frames > dpb->max_ref_frames)
        status = HANTRO_NOK;
    }
    /* force sliding window marking if first field of current frame was
     * non-reference frame (don't know if this is allowed, but may happen
     * at least in erroneous streams) */
    else if(!second_field ||
            dpb->current_out->status[(u32)!image->pic_struct] == UNUSED) {
      status = SlidingWindowRefPicMarking(dpb);
    }
    /* if current picture was not marked as long-term reference by
     * memory management control operation 6 -> mark current as short
     * term and insert it into dpb (if there is room) */
    if(!marked_as_long_term) {
      if(dpb->num_ref_frames < dpb->max_ref_frames || second_field) {
        dpbPicture_t *current_out = dpb->current_out;

        current_out->frame_num = frame_num;
        current_out->pic_num = (i32) frame_num;
        SET_STATUS(*current_out, SHORT_TERM, image->pic_struct);
        H264BindDMVBuffer(dpb, current_out->dmv_data);
        SET_POC(*current_out, pic_order_cnt, image->pic_struct);
        if(!second_field) {
          current_out->to_be_displayed = to_be_displayed;
          dpb->fullness++;
          dpb->num_ref_frames++;
        }
        /* first field non-reference and already output (kind of) */
        else if (dpb->current_out->status[(u32)!image->pic_struct] == UNUSED &&
                 dpb->current_out->to_be_displayed == 0) {
          dpb->fullness++;
          dpb->num_ref_frames++;
        }
      }
      /* no room */
      else {
        u32 i;
        dpbPicture_t *current_out = dpb->current_out;

        DPB_TRACE("NO ROOM IN DPB, probably corrupted stream, frame_num %d\n", frame_num);
        for(i = 0; i <= dpb->dpb_size; i++) {
          if((dpb->buffer[i].status[0] != EMPTY && dpb->buffer[i].status[1] == EMPTY) ||
              (dpb->buffer[i].status[0] == EMPTY && dpb->buffer[i].status[1] != EMPTY) ||
              (dpb->buffer[i].status[0] == NON_EXISTING && dpb->buffer[i].status[1] == NON_EXISTING)) {
            if (storage->pp_enabled && dpb->buffer[i].ds_data &&
                (dpb->buffer[i].to_be_displayed ||
                 (dpb->buffer[i].status[0] == NON_EXISTING &&
                  dpb->buffer[i].status[1] == NON_EXISTING))) {
              InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
              SET_SEI_UNUSED(dpb->buffer[i].sei_param);
            }
            dpb->buffer[i].to_be_displayed = 0;
            if (IS_REFERENCE_F(dpb->buffer[i]))
              DpbBufFree(dpb, i);
            SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
            if (dpb->buffer[i].dmv_data) {
              H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
              H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
            }
          }
        }

        if (dpb->num_ref_frames >= dpb->max_ref_frames)
          status = SlidingWindowRefPicMarking(dpb);

        if(dpb->num_ref_frames < dpb->max_ref_frames || second_field) {
          current_out->frame_num = frame_num;
          current_out->pic_num = (i32) frame_num;
          SET_STATUS(*current_out, SHORT_TERM, image->pic_struct);
          H264BindDMVBuffer(dpb, current_out->dmv_data);
          SET_POC(*current_out, pic_order_cnt, image->pic_struct);
          dpb->fullness++;
          dpb->num_ref_frames++;
          current_out->to_be_displayed = to_be_displayed;
        }
        status = HANTRO_NOK;
      }
    }
  }

  {
    dpbPicture_t *current_out = dpb->current_out;
    current_out->pic_id = current_pic_id;
    error_ratio = num_err_mbs * EC_ROUND_COEFF / storage->pic_size_in_mbs;
    if (current_out->is_field_pic && second_field) {
      current_out->error_ratio[second_field] = current_out->error_ratio[second_field] > 0 ?
                                               current_out->error_ratio[second_field] : error_ratio;
    } else {
      current_out->error_ratio[0] = error_ratio;
      current_out->error_ratio[1] = error_ratio;
    }
    current_out->tiled_mode = tiled_mode;
    current_out->is_field_pic = image->pic_struct != FRAME;
    current_out->is_bottom_field = image->pic_struct == BOTFIELD;
    current_out->mono_chrome = dpb->mono_chrome;
    if (!current_out->is_field_pic)
      current_out->pic_struct = image->pic_struct;
    else if (second_field)
      current_out->pic_struct = (image->pic_struct == BOTFIELD) ? TOPFIELD : BOTFIELD;
    else
      current_out->pic_struct = image->pic_struct;
    current_out->sar_width = image->sar_width;
    current_out->sar_height = image->sar_height;
    if (image->pic_struct == TOPFIELD) {
      current_out->is_idr[0] = is_idr;
      current_out->pic_code_type[0] = pic_code_type;
      current_out->decode_id[0] = current_pic_id;
    } else if (image->pic_struct == BOTFIELD) {
      current_out->is_idr[1] = is_idr;
      current_out->pic_code_type[1] = pic_code_type;
      current_out->decode_id[1] = current_pic_id;
    } else { /* FRAME */
      current_out->is_idr[0] =  current_out->is_idr[1] = is_idr;
      current_out->pic_code_type[0] =  current_out->pic_code_type[1] = pic_code_type;
      current_out->decode_id[0] = current_out->decode_id[1] = current_pic_id;
    }
    current_out->is_gdr_frame = storage->is_gdr_frame;
  }

  u32 i, j;
  if (dpb->num_ref_frames >= dpb->max_ref_frames) {
    for(i = 0; i < dpb->max_ref_frames; i++) {
      if (dpb->num_ref_frames < dpb->max_ref_frames) break;
      for(j = i+1; j < dpb->max_ref_frames; j++) {
        if(((dpb->buffer[i].status[0] == SHORT_TERM && dpb->buffer[i].status[1] == EMPTY) ||
            (dpb->buffer[i].status[0] == EMPTY && dpb->buffer[i].status[1] == SHORT_TERM)) &&
            ((dpb->buffer[j].status[0] == SHORT_TERM && dpb->buffer[j].status[1] == EMPTY) ||
             (dpb->buffer[j].status[0] == EMPTY && dpb->buffer[j].status[1] == SHORT_TERM)) &&
            (dpb->buffer[i].pic_num == dpb->buffer[j].pic_num)) {
          DPB_TRACE("Same frame num in DPB buf %d and DBP buf %d -> flush\n", i, j);
          if (&dpb->buffer[i] != dpb->current_out) {
            SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
            H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
            H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
            if(storage->pp_enabled /*&& dpb->buffer[i].to_be_displayed*/) {
              InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
              SET_SEI_UNUSED(dpb->buffer[i].sei_param);
            }
            dpb->buffer[i].to_be_displayed = 0;
            DpbBufFree(dpb, i);
          }
          if (&dpb->buffer[j] != dpb->current_out) {
            SET_STATUS(dpb->buffer[j], UNUSED, FRAME);
            H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
            H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
            if(storage->pp_enabled && dpb->buffer[j].to_be_displayed) {
              InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[j].ds_data)));
              SET_SEI_UNUSED(dpb->buffer[j].sei_param);
            }
            dpb->buffer[j].to_be_displayed = 0;
            DpbBufFree(dpb, j);
          }
          //if (found) break;
        }
      }
    }
  }

  if (dpb->num_ref_frames > dpb->max_ref_frames) {
    for(i = 0; i <= dpb->dpb_size; i++) {
      if (dpb->num_ref_frames <= dpb->max_ref_frames) break;
      if ((dpb->buffer[i].status[0] != EMPTY && dpb->buffer[i].status[1] == EMPTY) ||
          (dpb->buffer[i].status[0] == EMPTY && dpb->buffer[i].status[1] != EMPTY) ||
          (dpb->buffer[i].status[0] == NON_EXISTING && dpb->buffer[i].status[1] == NON_EXISTING)) {
        if (&dpb->buffer[i] != dpb->current_out) {
          SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
          if (dpb->buffer[i].dmv_data) {
            H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
            //H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
          }
          if ((dpb->buffer[i].to_be_displayed ||
               (dpb->buffer[i].status[0] == NON_EXISTING &&
                dpb->buffer[i].status[1] == NON_EXISTING))) {
            if (storage->pp_enabled && dpb->buffer[i].ds_data) {
              InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
              SET_SEI_UNUSED(dpb->buffer[i].sei_param);
            }
            if (dpb->buffer[i].dmv_data)
              H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
          }
          dpb->buffer[i].to_be_displayed = 0;
          DpbBufFree(dpb, i);
        }
      }
    }

    if (dpb->num_ref_frames > dpb->max_ref_frames)
      status = SlidingWindowRefPicMarking(dpb);
  }

  return (status);
}

/*------------------------------------------------------------------------------
    Function name   : h264DpbUpdateOutputList
    Description     :
    Return type     : void
    Argument        : dpbStorage_t * dpb
    Argument        : const image_t * image
------------------------------------------------------------------------------*/
void h264DpbUpdateOutputList(dpbStorage_t * dpb) {
  u32 i;

  /* dpb was initialized not to reorder the pictures -> output current
   * picture immediately */
  if(dpb->no_reordering) {
    /* TODO: This does not work when field is missing from output */

    dpbOutPicture_t *dpb_out = &dpb->out_buf[dpb->out_index_w];
    const dpbPicture_t *current_out = dpb->current_out;

    dpb_out->data = current_out->data;
    dpb_out->pp_data = current_out->ds_data;
    dpb_out->dmv_data = current_out->dmv_data;
    dpb_out->is_idr[0] = current_out->is_idr[0];
    dpb_out->is_idr[1] = current_out->is_idr[1];
    dpb_out->pic_id = current_out->pic_id;
    dpb_out->pic_code_type[0] = current_out->pic_code_type[0];
    dpb_out->pic_code_type[1] = current_out->pic_code_type[1];
    dpb_out->decode_id[0] = current_out->decode_id[0];
    dpb_out->decode_id[1] = current_out->decode_id[1];
    dpb_out->sei_param[0] = current_out->sei_param[0];
    dpb_out->sei_param[1] = current_out->sei_param[1];
    dpb_out->error_ratio[0] = current_out->error_ratio[0];
    dpb_out->error_ratio[1] = current_out->error_ratio[1];
    dpb_out->error_info = current_out->error_info;
    dpb_out->is_openb = current_out->openB_flag;
    dpb_out->interlaced = dpb->interlaced;
    dpb_out->field_picture = current_out->is_field_pic;
    dpb_out->mem_idx = current_out->mem_idx;
    dpb_out->tiled_mode = current_out->tiled_mode;
    dpb_out->crop = current_out->crop;
    dpb_out->pic_width = current_out->pic_width;
    dpb_out->pic_height = current_out->pic_height;
    dpb_out->sar_width = current_out->sar_width;
    dpb_out->sar_height = current_out->sar_height;
    dpb_out->top_field = current_out->is_bottom_field ? 0 : 1;
    dpb_out->pic_struct = current_out->pic_struct;
    dpb_out->corrupted_second_field = current_out->corrupted_second_field;
    dpb_out->bit_depth_luma = dpb->bit_depth_luma;
    dpb_out->bit_depth_chroma = dpb->bit_depth_chroma;
    dpb_out->mono_chrome = dpb->mono_chrome;
    dpb_out->chroma_format_idc = dpb->chroma_format_idc;
    dpb_out->is_gdr_frame = current_out->is_gdr_frame;
    dpb_out->temporal_id = current_out->temporal_id;
    if(current_out->is_field_pic) {
      if(current_out->status[0] == EMPTY || current_out->status[1] == EMPTY || current_out->corrupted_second_field) {
        dpb_out->field_picture = 1;
        dpb_out->top_field = (current_out->status[0] == EMPTY) ? 0 : 1;
        if (current_out->corrupted_second_field)
          dpb_out->top_field = (dpb_out->pic_struct == TOPFIELD) ? 1 : 0;

        DPB_TRACE("dec pic %d MISSING FIELD! %s\n", dpb_out->pic_id,
                     dpb_out->top_field ? "BOTTOM" : "TOP");
      }
    }

    dpb->num_out++;
    dpb->out_index_w++;
    if (dpb->out_index_w == dpb->dpb_size + 1)
      dpb->out_index_w = 0;

    MarkTempOutput(dpb->fb_list, current_out->mem_idx);
  } else {
    /* output pictures if buffer full */
    while(dpb->fullness > dpb->dpb_size) {
      i = OutputPicture(dpb);
      if (i != HANTRO_OK)
        dpb->fullness = 0;
      //ASSERT(i == HANTRO_OK);
      (void) i;
    }
  }

  /* if current_out is the last element of list -> exchange with first empty
   * slot so that only first 16 elements used as reference */
  if(dpb->current_out == dpb->buffer + dpb->dpb_size) {
    for(i = 0; i < dpb->dpb_size; i++) {
      if(!dpb->buffer[i].to_be_displayed &&
          !IS_REFERENCE_F(dpb->buffer[i])) {
        dpbPicture_t tmp_pic = *dpb->current_out;
        *dpb->current_out = dpb->buffer[i];
        dpb->current_out_pos = i;
        dpb->buffer[i] = tmp_pic;
        dpb->current_out = dpb->buffer + i;
        break;
      }
    }
  }
}

/*------------------------------------------------------------------------------

    Function: h264bsdGetRefPicData

        Functional description:
            Function to get reference picture data from the reference picture
            list

        Returns:
            pointer to desired reference picture data
            NULL if invalid index or non-existing picture referred

------------------------------------------------------------------------------*/

i32 h264bsdGetRefPicData(const dpbStorage_t * dpb, u32 index) {

  /* Variables */

  /* Code */
  if(index > 16 || dpb->buffer[dpb->list[index]].data == NULL)
    return -1;
  else if(!IS_EXISTING(dpb->buffer[dpb->list[index]], FRAME))
    return -1;
  else
    return (i32) (dpb->list[index]);

}

/*------------------------------------------------------------------------------

    Function: h264bsdGetRefPicDataVlcMode

        Functional description:
            Function to get reference picture data from the reference picture
            list

        Returns:
            pointer to desired reference picture data
            NULL if invalid index or non-existing picture referred

------------------------------------------------------------------------------*/

struct DWLLinearMem h264bsdGetRefPicDataVlcMode(const dpbStorage_t * dpb, u32 index,
                                u32 field_mode) {

  /* Variables */
  struct DWLLinearMem empty;
  (void)DWLmemset(&empty, 0, sizeof(struct DWLLinearMem));

  /* Code */

  if(!field_mode) {
    if(index >= dpb->dpb_size)
      return empty;
    else if(!IS_EXISTING(dpb->buffer[index], FRAME))
      return empty;
    else
      return *(dpb->buffer[index].data);
  } else {
    const u32 field = (index & 1) ? BOTFIELD : TOPFIELD;
    if(index / 2 >= dpb->dpb_size)
      return empty;
    else if(!IS_EXISTING(dpb->buffer[index / 2], field))
      return empty;
    else
      return *(dpb->buffer[index / 2].data);
  }

}

/*------------------------------------------------------------------------------

    Function: h264bsdAllocateDpbImage

        Functional description:
            function to allocate memory for a image. This function does not
            really allocate any memory but reserves one of the buffer
            positions for decoding of current picture

        Returns:
            pointer to memory area for the image

------------------------------------------------------------------------------*/

void *h264bsdAllocateDpbImage(dpbStorage_t * dpb, u32 pic_id) {

  /* Variables */

  u32 i;
  u32 dmv_buf_id = 0;
  storage_t *storage = dpb->storage;
  u32 mem_idx[MAX_PIC_BUFFERS];
  struct DWLLinearMem *pp_data = NULL;

  /* Code */

  /*
   * ASSERT(!dpb->buffer[dpb->dpb_size].to_be_displayed &&
   * !IS_REFERENCE(dpb->buffer[dpb->dpb_size]));
   * ASSERT(dpb->fullness <= dpb->dpb_size);
   */

  /* initialization */
  for (i = 0; i < MAX_PIC_BUFFERS; i++)
    mem_idx[i] = 0xFF;

  /* find all unused and not-to-be-displayed pic and store their memIdx */
  for(i = 0; i <= dpb->dpb_size; i++) {
    if(!dpb->buffer[i].to_be_displayed && !IS_REFERENCE_F(dpb->buffer[i])) {
      mem_idx[i] = dpb->buffer[i].mem_idx;
    }
  }

  /* find the first unused and not-to-be-displayed pic */
  for(i = 0; i <= dpb->dpb_size; i++) {
    if(mem_idx[i] != 0xFF)
      break;
  }

  // Workaround for errorneous stream
  u32 dpb_full = HANTRO_FALSE;
  if (i > dpb->dpb_size) {
    i32 index = -1;
    i32 pic_num = 0;

    /* find the oldest short term picture */
    for(i = 0; i < dpb->dpb_size; i++)
      if(IS_SHORT_TERM_F(dpb->buffer[i])) {
        if((dpb->buffer[i].pic_num < pic_num) || (index == -1)) {
          index = (i32) i;
          pic_num = dpb->buffer[i].pic_num;
        }
      }
    if(index >= 0)
      i = index;
    else
      i = dpb->dpb_size;

    mem_idx[i] = dpb->buffer[i].mem_idx;
    if (storage->pp_enabled && dpb->buffer[i].ds_data) {
      InputQueueReturnBuffer(storage->pp_buffer_queue,DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
      SET_SEI_UNUSED(dpb->buffer[i].sei_param);
    }
    H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
    dpb_full = HANTRO_TRUE;
    DPB_TRACE("DPB full! Corrupt stream. Flushing slot %d, pic_num %d\n", i, pic_num);
  }

  /* find first unused dmv buffer */
#ifndef  ASIC_TRACE_SUPPORT
  if (dpb->tot_dmv_buffers > 0 && storage->pp_enabled &&
      storage->high10p_mode) {
    pthread_mutex_lock(dpb->dmv_buffer_mutex);
    for (dmv_buf_id = 0; dmv_buf_id < dpb->tot_dmv_buffers; dmv_buf_id++) {
      if (dpb->dmv_buf_status[dmv_buf_id] == BUF_FREE) {
        break;
      }
      if (dpb_full) {
        dmv_buf_id = dpb->buffer[i].dmv_mem_idx;
        break;
      }
    }
    pthread_mutex_unlock(dpb->dmv_buffer_mutex);

#ifdef GET_FREE_BUFFER_NON_BLOCK
    if (dmv_buf_id == dpb->tot_dmv_buffers)
      return NULL;
#else
    if (dmv_buf_id == dpb->tot_dmv_buffers) {
      pthread_mutex_lock(dpb->dmv_buffer_mutex);
      dmv_buf_id = 0;
      while (dmv_buf_id < dpb->tot_dmv_buffers) {
        if (dpb->dmv_buf_status[dmv_buf_id] == BUF_FREE) {
          break;
        }

        dmv_buf_id++;
        if (dmv_buf_id == dpb->tot_dmv_buffers) {
          pthread_cond_wait(dpb->dmv_buffer_cv, dpb->dmv_buffer_mutex);
          dmv_buf_id = 0;
        }
      }
      pthread_mutex_unlock(dpb->dmv_buffer_mutex);
    }
#endif
  }
#else
  (void)dpb_full;
#endif

  if (storage->pp_enabled) {
#ifdef GET_FREE_BUFFER_NON_BLOCK
     pp_data = InputQueueGetBuffer(storage->pp_buffer_queue, 0);
     if (pp_data == NULL) {
        /* can't get pp buffer, so return sei_param */
       if (storage->sei_param_curr &&
          storage->sei_param_curr->decode_id == pic_id)
          storage->sei_param_curr->sei_status = SEI_UNUSED;
       return NULL;
     }
#else
    pp_data = InputQueueGetBuffer(storage->pp_buffer_queue, 1);
#endif
  }
  ASSERT(i <= dpb->dpb_size);
  dpb->current_out = &dpb->buffer[i];
  dpb->current_out_pos = i;
  dpb->current_out->status[0] = dpb->current_out->status[1] = EMPTY;
  dpb->current_out->decode_id[0] = dpb->current_out->decode_id[1] = -1;
  dpb->current_out->sei_param[0] = dpb->current_out->sei_param[1] = NULL;

#if !defined(ASIC_TRACE_SUPPORT) || !defined(SUPPORT_MULTI_CORE)
  /* To avoid multicore top simultion buffer confliction, we always find a new
     free buffer. */
  if(IsBufferReferenced(dpb->fb_list, dpb->current_out->mem_idx))
#endif
  {
    /* inidicate the buffer type: FB_ALLOCATED or FB_FREE? */
    u32 is_buffer_free;
    u32 new_id = GetFreePicBuffer(dpb->fb_list, mem_idx, &is_buffer_free);
    if(new_id == FB_NOT_VALID_ID) {
      if (storage->pp_enabled && pp_data) {
        /* Failed to get reference buffer, need to return pp output buffer */
        InputQueueReturnBuffer(storage->pp_buffer_queue,
                               DWL_GET_DEVMEM_ADDR(*pp_data));
      }
      /* can't get pp buffer, so return sei_param */
      if (storage->sei_param_curr &&
          storage->sei_param_curr->decode_id == pic_id)
        storage->sei_param_curr->sei_status = SEI_UNUSED;
      return NULL;
    }
    if(new_id != dpb->current_out->mem_idx) {
      if (is_buffer_free) {
        SetFreePicBuffer(dpb->fb_list, dpb->current_out->mem_idx);
        dpb->current_out->mem_idx = new_id;
        dpb->current_out->data = GetDataById(dpb->fb_list, new_id);
        if (dpb->current_out->data == NULL) return NULL;
      } else {
        for(i = 0; i <= dpb->dpb_size; i++) {
          if(dpb->buffer[i].mem_idx == new_id)
            break;
        }
        dpb->current_out = &dpb->buffer[i];
      }
    }
  }
#ifndef ASIC_TRACE_SUPPORT
  if (storage->pp_enabled && storage->high10p_mode) {
    dpb->current_out->dmv_data = &dpb->dmv_buffers[dmv_buf_id];
    dpb->current_out->dmv_mem_idx = dmv_buf_id;
  } else
#endif
  {
    dpb->current_out->dmv_mem_idx = dpb->current_out->mem_idx;
    dpb->current_out->dmv_data = &dpb->dmv_buffers[dpb->current_out->mem_idx];
    dpb->current_out->dmv_data->bus_address =
        dpb->current_out->data->bus_address + dpb->dir_mv_offset;
    dpb->current_out->dmv_data->virtual_address =
        (u32 *)((u8 *)(dpb->current_out->data->virtual_address) + dpb->dir_mv_offset);
  }

  dpb->current_out_pos = i;
  dpb->current_out->status[0] = dpb->current_out->status[1] = EMPTY;
  H264OutputDMVBuffer(dpb, dpb->current_out->dmv_data->bus_address);
  H264UnBindDMVBuffer(dpb, dpb->current_out->dmv_data);
  dpb->current_out->decode_id[0] = dpb->current_out->decode_id[1] = -1;
  if (storage->sei_param_curr &&
      storage->sei_param_curr->decode_id == pic_id) {
    dpb->current_out->sei_param[0] = storage->sei_param_curr;
    dpb->current_out->sei_param[0]->sei_status = SEI_USED;
  } else {
    dpb->current_out->sei_param[0] = NULL;
  }
  dpb->current_out->corrupted_first_field_or_frame = 0;
  dpb->current_out->corrupted_second_field = 0;
  dpb->current_out->pic_width = dpb->pic_width;
  dpb->current_out->pic_height = dpb->pic_height;
  dpb->current_out->bit_depth_luma = dpb->bit_depth_luma;
  dpb->current_out->bit_depth_chroma = dpb->bit_depth_chroma;
  dpb->current_out->chroma_format_idc = dpb->chroma_format_idc;
  dpb->current_out->temporal_id = dpb->svc_info.temporal_id;
  dpb->current_out->ds_data = pp_data;
#ifdef ENABLE_FPGA_VERIFICATION
  if (storage->pp_enabled) {
    DWLmemset(dpb->current_out->ds_data->virtual_address,
#ifdef ENABLE_JM_VERIFICATION
              0x80, /* memest to 0x80 to match with JM */
#else
              0x0,
#endif
              dpb->current_out->ds_data->size);
#ifdef SUPPORT_DMA
    /* update device buffer by host buffer */
    DWLDMATransData((addr_t)dpb->current_out->ds_data->bus_address,
                    (void *)dpb->current_out->ds_data->virtual_address,
                    dpb->current_out->ds_data->size, HOST_TO_DEVICE);
#endif
  }
#endif

  dpb->current_out->openB_flag = 0;
  dpb->current_out->mono_chrome = dpb->mono_chrome;

  if (dpb->bumping_flag) {
    while(h264DpbHRDBumping(dpb) == HANTRO_OK);
    dpb->bumping_flag = 0;
  }

  //ASSERT(dpb->current_out->data);
  (void)dmv_buf_id;
  return dpb->current_out->data;
}

/*------------------------------------------------------------------------------

    Function: SlidingWindowRefPicMarking

        Functional description:
            Perform sliding window reference picture marking process.

        Outputs:
            HANTRO_OK      success
            HANTRO_NOK     failure, no short-term reference frame found that
                           could be marked unused

------------------------------------------------------------------------------*/

static u32 SlidingWindowRefPicMarking(dpbStorage_t * dpb) {

  /* Variables */

  i32 index, pic_num;
  u32 i;

  /* Code */

  if(dpb->num_ref_frames < dpb->max_ref_frames) {
    return (HANTRO_OK);
  } else {
    index = -1;
    pic_num = 0;
    /* find the oldest short term picture */
    for(i = 0; i < dpb->dpb_size; i++)
      if(IS_SHORT_TERM_F(dpb->buffer[i])) {
        if(dpb->buffer[i].pic_num < pic_num || index == -1) {
          index = (i32) i;
          pic_num = dpb->buffer[i].pic_num;
        }
      }
    if(index >= 0) {
      SET_STATUS(dpb->buffer[index], UNUSED, FRAME);
      H264UnBindDMVBuffer(dpb, dpb->buffer[index].dmv_data);
      DpbBufFree(dpb, index);

      return (HANTRO_OK);
    }
  }

  return (HANTRO_NOK);

}

u32 h264bsdUpdateDpb(dpbStorage_t *dpb,
                     const void *dwl,
                     struct dpbInitParams *p_dpb_params) {
  FrameBufferList *fb_list = dpb->fb_list;
  u32 i = 0, old_dpb_size = 0;
  u32 ref_buffer_align = MAX(16, ALIGN((((storage_t *)(dpb->storage))->align)));
  storage_t *storage = dpb->storage;
  u32 dir_mv_offset = 0;

  ASSERT(p_dpb_params->max_frame_num);
  ASSERT(p_dpb_params->dpb_size);
  ASSERT(p_dpb_params->pic_size_in_mbs);
  ASSERT(p_dpb_params->max_ref_frames <= MAX_NUM_REF_PICS);
  ASSERT(p_dpb_params->max_ref_frames <= p_dpb_params->dpb_size);

  dpb->pic_size_in_mbs = p_dpb_params->pic_size_in_mbs;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
  old_dpb_size = dpb->dpb_size;
  dpb->max_ref_frames = MAX(p_dpb_params->max_ref_frames, 1);
  if(p_dpb_params->no_reordering)
    dpb->dpb_size = dpb->max_ref_frames;
  else
    dpb->dpb_size = p_dpb_params->dpb_size;
#ifdef SUPPORT_GDR
  /* GDR need a fake reference frame. */
  dpb->dpb_size = MAX(dpb->dpb_size, 2);
#else
  dpb->dpb_size = MAX(dpb->dpb_size, 1);
#endif
  dpb->max_frame_num = p_dpb_params->max_frame_num;
  dpb->no_reordering = p_dpb_params->no_reordering;
  dpb->fullness = 0;
  dpb->num_ref_frames = 0;
  dpb->prev_ref_frame_num = 0;
  dpb->num_out = 0;
  dpb->out_index_w = 0;
  dpb->out_index_r = 0;
  dpb->prev_out_idx = INVALID_MEM_IDX;

  /* max DPB size is (16 + 1) buffers */
  /* DO NOT update: dpb->tot_buffers */
  u32 pic_buff_size = 0;
  for(i = 0; i < dpb->tot_buffers; i++) {
    u32 out_w = 0, out_h = 0;

    if(p_dpb_params->is_high_supported || p_dpb_params->is_high10_supported) {
      /* yuv picture + direct mode motion vectors */
      out_w = NEXT_MULTIPLE(4 * p_dpb_params->pic_width_in_mbs * 16 *
                            p_dpb_params->pixel_width / 8,
                            ALIGN((((storage_t *)(dpb->storage))->align)));
      out_h = p_dpb_params->pic_height_in_mbs * 4;
      if (storage->skip_non_intra && storage->pp_enabled) {
        pic_buff_size = 0;
        storage->dmv_mem_size = 0;
      } else {
        pic_buff_size = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align) +
            (p_dpb_params->mono_chrome ? 0 :
            NEXT_MULTIPLE((out_w * out_h)/2 *((p_dpb_params->chroma_format_idc==2)? 2:1),
            ref_buffer_align));
        storage->dmv_mem_size = NEXT_MULTIPLE((p_dpb_params->pic_size_in_mbs + 32) *
            (p_dpb_params->is_high10_supported? 80 : 64), ref_buffer_align);
          pic_buff_size += storage->dmv_mem_size;
      }
      if (p_dpb_params->is_high10_supported) {
        /* allocate 32 bytes for multicore status fields */
        /* locate it after picture and before direct MV */
        /* align sync_mc buffer, storage sync bytes adjoining to dir mv*/
        {
          if (storage->skip_non_intra && storage->pp_enabled)
            dir_mv_offset = NEXT_MULTIPLE(32, ref_buffer_align);
          else
            dir_mv_offset = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                                + (p_dpb_params->mono_chrome ? 0 :
                                  NEXT_MULTIPLE(out_w * out_h / 2*((p_dpb_params->chroma_format_idc==2)?2:1),
                                  ref_buffer_align))
                                + NEXT_MULTIPLE(32, ref_buffer_align);
        }
        dpb->sync_mc_offset = dir_mv_offset - 32;
      } else {
        {
          if (storage->skip_non_intra && storage->pp_enabled)
            dir_mv_offset = 0;
          else
            dir_mv_offset = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                                + (p_dpb_params->mono_chrome ? 0 :
                                  NEXT_MULTIPLE(out_w * out_h / 2*((p_dpb_params->chroma_format_idc==2)?2:1), ref_buffer_align));
        }

        /* allocate 32 bytes for multicore status fields */
        /* locate it after picture and direct MV */
        dpb->sync_mc_offset = pic_buff_size;
      }
      pic_buff_size += NEXT_MULTIPLE(32, ref_buffer_align);
      /* compression table */
      dpb->cbs_ytbl_offset = pic_buff_size;
      dpb->cbs_ctbl_offset = dpb->cbs_ytbl_offset + p_dpb_params->tbl_sizey;
      pic_buff_size += p_dpb_params->tbl_sizey + p_dpb_params->tbl_sizec;
    } else {
      out_w = NEXT_MULTIPLE(4 * p_dpb_params->pic_width_in_mbs * 16,
                            ALIGN((((storage_t *)(dpb->storage))->align)));
      out_h = p_dpb_params->pic_height_in_mbs * 4;
      if (storage->skip_non_intra && storage->pp_enabled)
        pic_buff_size = 0;
      else
        pic_buff_size = NEXT_MULTIPLE(out_w * out_h,  ref_buffer_align)
                      + NEXT_MULTIPLE(out_w * out_h / 2,  ref_buffer_align);
    }
    if (p_dpb_params->enable2nd_chroma && !p_dpb_params->mono_chrome) {
      dpb->ch2_offset = pic_buff_size;
      if (!(storage->skip_non_intra && storage->pp_enabled))
        pic_buff_size += NEXT_MULTIPLE(out_w * out_h / 2,  ref_buffer_align);
    }

    if (storage->qp_output_enable) {
      storage->qp_mem_size = NEXT_MULTIPLE(p_dpb_params->pic_width_in_mbs, 64)*p_dpb_params->pic_height_in_mbs;
    } else
      storage->qp_mem_size = 0;

    if(storage->qp_output_enable && !storage->pp_enabled) {
      dpb->out_qp_offset = pic_buff_size;
      pic_buff_size += storage->qp_mem_size;
    }
  }

  /* Update DMV buffer info */
  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  dpb->dir_mv_offset = dir_mv_offset;
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    dpb->dmv_buffers[i].bus_address = dpb->pic_buffers[i].bus_address + dpb->dir_mv_offset;
    dpb->dmv_buffers[i].virtual_address = (u32 *)((u8 *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset);
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);

  if (old_dpb_size < dpb->dpb_size) {
    for (i = old_dpb_size + 1; i < dpb->dpb_size + 1; i++) {
      /* Find a unused buffer j. */
      u32 j, id;
      for (j = 0; j < MAX_PIC_BUFFERS; j++) {
        u32 found = 0;
        for (u32 k = 0; k < i; k++) {
          if (dpb->pic_buffers[j].bus_address == dpb->buffer[k].data->bus_address) {
            found = 1;
            break;
          }
        }
        if (!found)
          break;
      }
      ASSERT(j < MAX_PIC_BUFFERS);
      dpb->buffer[i].data = dpb->pic_buffers + j;
      id = GetIdByData(fb_list, (void *)dpb->buffer[i].data);
      MarkIdAllocated(fb_list, id);
      dpb->buffer[i].mem_idx = id;
      dpb->pic_buff_id[j] = id;
    }
  } else {
    for (i = dpb->dpb_size + 1; i < old_dpb_size + 1; i++) {
      MarkIdFree(fb_list, dpb->buffer[i].mem_idx);
    }
  }

  for(i = 0; i < dpb->tot_buffers; i++) {
    if(DWL_DEVMEM_VAILD(dpb->pic_buffers[i]) &&
        ((storage_t *)(dpb->storage))->realloc_int_buf) {
      if (((storage_t *)(dpb->storage))->pp_enabled)
      {
        DWLFreeRefFrm(dwl, dpb->pic_buffers+i);
        dpb->n_int_buf_size = pic_buff_size;
        DWLMallocRefFrm(dwl, pic_buff_size, dpb->pic_buffers+i);
      }
    }
  }

  return (HANTRO_OK);
}

/*------------------------------------------------------------------------------

    Function: h264bsdInitDpb

        Functional description:
            Function to initialize DPB. Reserves memories for the buffer,
            reference picture list and output buffer. dpb_size indicates
            the maximum DPB size indicated by the levelIdc in the stream.
            If no_reordering flag is HANTRO_FALSE the DPB stores dpb_size pictures
            for display reordering purposes. On the other hand, if the
            flag is HANTRO_TRUE the DPB only stores max_ref_frames reference pictures
            and outputs all the pictures immediately.

        Inputs:
            pic_size_in_mbs    picture size in macroblocks
            dpb_size         size of the DPB (number of pictures)
            max_ref_frames    max number of reference frames
            max_frame_num     max frame number
            no_reordering    flag to indicate that DPB does not have to
                            prepare to reorder frames for display

        Outputs:
            dpb             pointer to dpb data storage

        Returns:
            HANTRO_OK       success
            MEMORY_ALLOCATION_ERROR if memory allocation failed

------------------------------------------------------------------------------*/

u32 h264bsdInitDpb(
  const void *dwl,
  dpbStorage_t *dpb,
  struct dpbInitParams *p_dpb_params) {
  FrameBufferList *fb_list = dpb->fb_list;
  void *dmv_buffer_mutex = dpb->dmv_buffer_mutex;
  void *dmv_buffer_cv = dpb->dmv_buffer_cv;

  u32 i;
  u32 ref_buffer_align = MAX(16, ALIGN((((storage_t *)(dpb->storage))->align)));
  storage_t *storage = dpb->storage;

  ASSERT(p_dpb_params->max_frame_num);
  ASSERT(p_dpb_params->dpb_size);
  ASSERT(p_dpb_params->pic_size_in_mbs);
  ASSERT(p_dpb_params->max_ref_frames <= MAX_NUM_REF_PICS);
  ASSERT(p_dpb_params->max_ref_frames <= p_dpb_params->dpb_size);

  /* make sure all is clean */
  (void) DWLmemset(dpb, 0, sizeof(*dpb));
  (void) DWLmemset(dpb->pic_buff_id, FB_NOT_VALID_ID, sizeof(dpb->pic_buff_id));

  /* restore value */
  dpb->fb_list = fb_list;
  dpb->storage = storage;
  dpb->dmv_buffer_mutex = dmv_buffer_mutex;
  dpb->dmv_buffer_cv =dmv_buffer_cv;

  dpb->pic_size_in_mbs = p_dpb_params->pic_size_in_mbs;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
  dpb->max_ref_frames = MAX(p_dpb_params->max_ref_frames, 1);
  if(p_dpb_params->no_reordering)
    dpb->dpb_size = dpb->max_ref_frames;
  else
    dpb->dpb_size = p_dpb_params->dpb_size;
#ifdef SUPPORT_GDR
  /* GDR need a fake reference frame. */
  dpb->dpb_size = MAX(dpb->dpb_size, 2);
#else
  dpb->dpb_size = MAX(dpb->dpb_size, 1);
#endif
  dpb->max_frame_num = p_dpb_params->max_frame_num;
  dpb->no_reordering = p_dpb_params->no_reordering;
  dpb->fullness = 0;
  dpb->num_ref_frames = 0;
  dpb->prev_ref_frame_num = 0;
  dpb->num_out = 0;
  dpb->out_index_w = 0;
  dpb->out_index_r = 0;
  dpb->prev_out_idx = INVALID_MEM_IDX;

  /* max DPB size is (16 + 1) buffers */
  dpb->tot_buffers = dpb->dpb_size + 1;

  /* figure out extra buffers for smoothing, pp, multicore, etc... */

  if (p_dpb_params->n_cores == 1) {
    /* single core configuration */
    if (p_dpb_params->display_smoothing)
      dpb->tot_buffers += p_dpb_params->no_reordering ? 1 : dpb->dpb_size + 1;
  } else {
    /* multi core configuration */

    if (p_dpb_params->display_smoothing && !p_dpb_params->no_reordering) {
      /* at least double buffers for smooth output */
      if (dpb->tot_buffers > p_dpb_params->n_cores) {
        dpb->tot_buffers *= 2;
      } else {
        dpb->tot_buffers += p_dpb_params->n_cores;
      }
    } else {
      /* one extra buffer for each core */
      /* do not allocate twice for multiview */
      if(!p_dpb_params->mvc_view)
        dpb->tot_buffers += p_dpb_params->n_cores;
    }
  }

#ifdef ASIC_TRACE_SUPPORT
#ifdef SUPPORT_MULTI_CORE
  dpb->tot_buffers += 10;   /* add extra 10 buffers for multicore simulation */
#endif
  if ( p_dpb_params->mvc_view )
    dpb->tot_buffers = MIN(dpb->tot_buffers, (MAX_PIC_BUFFERS >> 1));
#endif

  dpb->tot_buffers_reserved = dpb->tot_buffers;
  dpb->out_buf = DWLmalloc((MAX_NUM_REF_PICS + 1) * sizeof(dpbOutPicture_t));

  if(dpb->out_buf == NULL) {
    return (MEMORY_ALLOCATION_ERROR);
  }

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  dpb->tot_dmv_buffers = dpb->tot_buffers;
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
  for(i = 0; i < dpb->tot_buffers; i++) {
    u32 pic_buff_size, out_w = 0, out_h = 0;

    if(p_dpb_params->is_high_supported || p_dpb_params->is_high10_supported) {
      /* yuv picture + direct mode motion vectors */
      out_w = NEXT_MULTIPLE(4 * p_dpb_params->pic_width_in_mbs * 16 *
                            p_dpb_params->pixel_width / 8,
                            ALIGN((((storage_t *)(dpb->storage))->align)));
      out_h = p_dpb_params->pic_height_in_mbs * 4;
      pic_buff_size = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                      + (p_dpb_params->mono_chrome ? 0 :
                        NEXT_MULTIPLE(out_w * out_h / 2*((p_dpb_params->chroma_format_idc==2)?2:1), ref_buffer_align));
      storage->dmv_mem_size = NEXT_MULTIPLE((p_dpb_params->pic_size_in_mbs + 32) *
                                      (p_dpb_params->is_high10_supported? 80 : 64), ref_buffer_align);
      pic_buff_size += storage->dmv_mem_size;
      if (storage->skip_non_intra && storage->pp_enabled) {
        pic_buff_size = 0;
        storage->dmv_mem_size = 0;
      }

      if (p_dpb_params->is_high10_supported) {
        /* allocate 32 bytes for multicore status fields */
        /* locate it after picture and before direct MV */
        /* align sync_mc buffer, storage sync bytes adjoining to dir mv*/
        {
          if (storage->skip_non_intra && storage->pp_enabled)
            dpb->dir_mv_offset = NEXT_MULTIPLE(32, ref_buffer_align);
          else
            dpb->dir_mv_offset = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                                + (p_dpb_params->mono_chrome ? 0 :
                                  NEXT_MULTIPLE(out_w * out_h / 2*((p_dpb_params->chroma_format_idc==2)?2:1), ref_buffer_align))
                                + NEXT_MULTIPLE(32, ref_buffer_align);
        }
        dpb->sync_mc_offset = dpb->dir_mv_offset - 32;
      } else {

        {
          if (storage->skip_non_intra && storage->pp_enabled)
            dpb->dir_mv_offset = 0;
          else
            dpb->dir_mv_offset = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                                + (p_dpb_params->mono_chrome ? 0 :
                                  NEXT_MULTIPLE(out_w * out_h / 2*((p_dpb_params->chroma_format_idc==2)?2:1), ref_buffer_align));
        }

        /* allocate 32 bytes for multicore status fields */
        /* locate it after picture and direct MV */
        dpb->sync_mc_offset = pic_buff_size;
      }
      pic_buff_size += NEXT_MULTIPLE(32, ref_buffer_align);
      /* compression table */
      dpb->cbs_ytbl_offset = pic_buff_size;
      dpb->cbs_ctbl_offset = dpb->cbs_ytbl_offset + p_dpb_params->tbl_sizey;
      pic_buff_size += p_dpb_params->tbl_sizey + p_dpb_params->tbl_sizec;
    } else {
      out_w = NEXT_MULTIPLE(4 * p_dpb_params->pic_width_in_mbs * 16,
                            ALIGN((((storage_t *)(dpb->storage))->align)));
      out_h = p_dpb_params->pic_height_in_mbs * 4;
      if (storage->skip_non_intra && storage->pp_enabled)
        pic_buff_size = 0;
      else
        pic_buff_size = NEXT_MULTIPLE(out_w * out_h, ref_buffer_align)
                      + NEXT_MULTIPLE(out_w * out_h / 2 *
                      ((p_dpb_params->chroma_format_idc==2)?2:1), ref_buffer_align);
    }
    if (p_dpb_params->enable2nd_chroma && !p_dpb_params->mono_chrome) {
      dpb->ch2_offset = pic_buff_size;
      if (!(storage->skip_non_intra && storage->pp_enabled))
        pic_buff_size += NEXT_MULTIPLE(out_w * out_h / 2 *
          ((p_dpb_params->chroma_format_idc==2)?2:1), ref_buffer_align);
    }


    if (storage->qp_output_enable) {
      storage->qp_mem_size = NEXT_MULTIPLE(p_dpb_params->pic_width_in_mbs,  64)*p_dpb_params->pic_height_in_mbs;
    } else
      storage->qp_mem_size = 0;

    if (storage->qp_output_enable && !storage->pp_enabled) {
      dpb->out_qp_offset = pic_buff_size;
      pic_buff_size += storage->qp_mem_size;
    }
    if (!storage->pp_enabled) {
      if (DWL_DEVMEM_COMPARE(dpb->pic_buffers[i], 0))
        return DEC_WAITING_FOR_BUFFER;
    } else {
      dpb->n_int_buf_size = pic_buff_size;
      dpb->pic_buffers[i].mem_type = DWL_MEM_TYPE_DPB;
      if(DWLMallocRefFrm(dwl, pic_buff_size, dpb->pic_buffers + i) != 0)
        return (MEMORY_ALLOCATION_ERROR);
      pthread_mutex_lock(dpb->dmv_buffer_mutex);
      dpb->dmv_buffers[i].bus_address = dpb->pic_buffers[i].bus_address + dpb->dir_mv_offset;
      dpb->dmv_buffers[i].virtual_address = (u32 *)((u8 *)(dpb->pic_buffers[i].virtual_address) + dpb->dir_mv_offset);
      dpb->dmv_buf_status[i] = BUF_FREE;
      pthread_mutex_unlock(dpb->dmv_buffer_mutex);
      if (i < dpb->dpb_size + 1) {
        u32 id = AllocateIdUsed(dpb->fb_list, dpb->pic_buffers + i);
        if (id == FB_NOT_VALID_ID)
          return MEMORY_ALLOCATION_ERROR;

        dpb->buffer[i].mem_idx = id;
        dpb->buffer[i].data = dpb->pic_buffers + i;
        dpb->buffer[i].error_ratio[0] = 0;
        dpb->buffer[i].error_ratio[1] = 1;
        dpb->buffer[i].error_info = DEC_NO_ERROR;

        dpb->pic_buff_id[i] = id;
      } else {

        u32 id = AllocateIdFree(dpb->fb_list, dpb->pic_buffers + i);
        if (id == FB_NOT_VALID_ID)
          return MEMORY_ALLOCATION_ERROR;

        dpb->pic_buff_id[i] = id;
      }

      if (p_dpb_params->is_high_supported || p_dpb_params->is_high10_supported) {
        /* reset direct motion vectors */
        if (!(storage->skip_non_intra && storage->pp_enabled)) {
          //void * base = (char *) (dpb->pic_buffers[i].virtual_address) +
          //              dpb->dir_mv_offset;
          void * base = (char *) (dpb->dmv_buffers[i].virtual_address);
          (void)DWLmemset(base, 0, (p_dpb_params->pic_size_in_mbs + 32) *
                         (p_dpb_params->is_high10_supported? 80 : 64));
#ifdef SUPPORT_DMA
          DWLDMATransData((addr_t)((u8*)dpb->dmv_buffers[i].bus_address),
                          (void *)((u8*)dpb->dmv_buffers[i].virtual_address),
                          (p_dpb_params->pic_size_in_mbs + 32) * (p_dpb_params->is_high10_supported? 80 : 64), HOST_TO_DEVICE);
#endif
        }

        /* set all pictures statuses to available */
        void * base = (char *) (dpb->pic_buffers[i].virtual_address) +
               dpb->sync_mc_offset;
        (void)DWLmemset(base, ~0, 32);
#ifdef SUPPORT_DMA
        DWLDMATransData((addr_t)((u8*)dpb->pic_buffers[i].bus_address + dpb->sync_mc_offset),
                        (void *)((u8*)dpb->pic_buffers[i].virtual_address + dpb->sync_mc_offset),
                        32, HOST_TO_DEVICE);
#endif
      }

    }
  }

  /* Request external pp buffers. */
  if(storage->pp_enabled) {
    if (!((storage_t *)(dpb->storage))->ext_buffer_added) {
      return DEC_WAITING_FOR_BUFFER;
    }
  }

  return (HANTRO_OK);
}

/*------------------------------------------------------------------------------

    Function: h264bsdResetDpb

        Functional description:
            Function to reset DPB. This function should be called when an IDR
            slice (other than the first) activates new sequence parameter set.
            Function calls h264bsdFreeDpb to free old allocated memories and
            h264bsdInitDpb to re-initialize the DPB. Same inputs, outputs and
            returns as for h264bsdInitDpb.

------------------------------------------------------------------------------*/

u32 h264bsdResetDpb(
  const void *dwl,
  dpbStorage_t * dpb,
  struct dpbInitParams *p_dpb_params) {

  /* Code */
  ASSERT(p_dpb_params->max_frame_num);
  ASSERT(p_dpb_params->dpb_size);
  ASSERT(p_dpb_params->pic_size_in_mbs);
  ASSERT(p_dpb_params->max_ref_frames <= MAX_NUM_REF_PICS);
  ASSERT(p_dpb_params->max_ref_frames <= p_dpb_params->dpb_size);
  if (dpb->b_updated)
    return HANTRO_OK;

  u32 pp_enabled = ((storage_t *)(dpb->storage))->pp_enabled;

  if ((dpb->use_adaptive_buffers &&
      ((!pp_enabled && dpb->n_ext_buf_size_added >= dpb->n_new_pic_size) ||
      (pp_enabled && dpb->pic_size_in_mbs >= p_dpb_params->pic_size_in_mbs))) ||
      (!dpb->use_adaptive_buffers && (dpb->pic_size_in_mbs == p_dpb_params->pic_size_in_mbs)))
  {
    u32 new_dpb_size, new_tot_buffers;

    dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
    dpb->max_ref_frames = (p_dpb_params->max_ref_frames != 0) ?
                          p_dpb_params->max_ref_frames : 1;

    if(p_dpb_params->no_reordering)
      new_dpb_size = dpb->max_ref_frames;
    else
      new_dpb_size = p_dpb_params->dpb_size;
#ifdef SUPPORT_GDR
  /* GDR need a fake reference frame. */
  new_dpb_size = MAX(new_dpb_size, 2);
#else
  new_dpb_size = MAX(new_dpb_size, 1);
#endif

    /* max DPB size is (16 + 1) buffers */
    new_tot_buffers = new_dpb_size + 1;

    /* figure out extra buffers for smoothing, pp, multicore, etc... */
    if (p_dpb_params->n_cores == 1) {
      /* single core configuration */
      if (p_dpb_params->display_smoothing)
        new_tot_buffers += p_dpb_params->no_reordering ? 1 : new_dpb_size + 1;
    } else {
      /* multi core configuration */

      if (p_dpb_params->display_smoothing && !p_dpb_params->no_reordering) {
        /* at least double buffers for smooth output */
        if (new_tot_buffers > p_dpb_params->n_cores) {
          new_tot_buffers *= 2;
        } else {
          new_tot_buffers += p_dpb_params->n_cores;
        }
      } else {
        /* one extra buffer for each core */
        /* do not allocate twice for multiview */
        if(!p_dpb_params->mvc_view)
          new_tot_buffers += p_dpb_params->n_cores;
      }
    }

    dpb->no_reordering = p_dpb_params->no_reordering;
    dpb->max_frame_num = p_dpb_params->max_frame_num;
    dpb->flushed = 0;


    u32 pp_enabled = ((storage_t *)(dpb->storage))->pp_enabled;

    if ((dpb->use_adaptive_buffers &&
       (((pp_enabled && new_tot_buffers <= dpb->tot_buffers)) ||
       (!pp_enabled && (new_tot_buffers + dpb->n_guard_size <= dpb->tot_buffers)))) ||
        (!dpb->use_adaptive_buffers && (dpb->dpb_size == new_dpb_size))) {
      /* number of pictures and DPB size are not changing */
      /* no need to reallocate DPB */
      h264bsdUpdateDpb(dpb, dwl, p_dpb_params);
      dpb->b_updated = 1;
      return (HANTRO_OK);
    }
  }

  h264bsdFreeDpb(
    dwl,
    dpb);

  dpb->b_updated = 1;
  return h264bsdInitDpb(
           dwl,
           dpb, p_dpb_params);
}

/*------------------------------------------------------------------------------

    Function: h264bsdInitRefPicList

        Functional description:
            Function to initialize reference picture list. Function just
            sets pointers in the list according to pictures in the buffer.
            The buffer is assumed to contain pictures sorted according to
            what the H.264 standard says about initial reference picture list.

        Inputs:
            dpb     pointer to dpb data structure

        Outputs:
            dpb     'list' field initialized

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdInitRefPicList(dpbStorage_t * dpb) {

  /* Variables */

  u32 i;

  /* Code */

  /*for(i = 0; i < dpb->num_ref_frames; i++) */
  /*dpb->list[i] = &dpb->buffer[i]; */
  for(i = 0; i <= dpb->dpb_size; i++)
    dpb->list[i] = i;
  ShellSort(dpb, dpb->list, 0, 0);

}

/*------------------------------------------------------------------------------

    Function: FindDpbPic

        Functional description:
            Function to find a reference picture from the buffer. The picture
            to be found is identified by pic_num and is_short_term flag.

        Returns:
            index of the picture in the buffer
            -1 if the specified picture was not found in the buffer

------------------------------------------------------------------------------*/

static i32 FindDpbPic(dpbStorage_t * dpb, i32 pic_num, u32 is_short_term,
                      u32 field) {

  /* Variables */

  u32 i = 0;
  u32 found = HANTRO_FALSE;

  /* Code */

  if(is_short_term) {
    while(i <= dpb->dpb_size && !found) {
      if(IS_SHORT_TERM(dpb->buffer[i], field) &&
          dpb->buffer[i].frame_num == (u32)pic_num)
        found = HANTRO_TRUE;
      else
        i++;
    }
  } else {
    ASSERT(pic_num >= 0);
    while(i <= dpb->dpb_size && !found) {
      if(IS_LONG_TERM(dpb->buffer[i], field) &&
          dpb->buffer[i].pic_num == pic_num)
        found = HANTRO_TRUE;
      else
        i++;
    }
  }

  if(found)
    return ((i32) i);
  else
    return (-1);

}

/*------------------------------------------------------------------------------

    Function: SetPicNums

        Functional description:
            Function to set pic_num values for short-term pictures in the
            buffer. Numbering of pictures is based on frame numbers and as
            frame numbers are modulo max_frame_num -> frame numbers of older
            pictures in the buffer may be bigger than the curr_frame_num.
            picNums will be set so that current frame has the largest pic_num
            and all the short-term frames in the buffer will get smaller pic_num
            representing their "distance" from the current frame. This
            function kind of maps the modulo arithmetic back to normal.

------------------------------------------------------------------------------*/

void SetPicNums(dpbStorage_t * dpb, u32 curr_frame_num) {

  /* Variables */

  u32 i;
  i32 frame_num_wrap;

  /* Code */

  ASSERT(dpb);
  ASSERT(curr_frame_num < dpb->max_frame_num);

  for(i = 0; i <= dpb->dpb_size; i++)
    if(IS_SHORT_TERM_F(dpb->buffer[i])) {
      if(dpb->buffer[i].frame_num > curr_frame_num)
        frame_num_wrap =
          (i32) dpb->buffer[i].frame_num - (i32) dpb->max_frame_num;
      else
        frame_num_wrap = (i32) dpb->buffer[i].frame_num;
      dpb->buffer[i].pic_num = frame_num_wrap;
    }

}

/*------------------------------------------------------------------------------

    Function: h264bsdCheckGapsInFrameNum

        Functional description:
            Function to check gaps in frame_num and generate non-existing
            (short term) reference pictures if necessary. This function should
            be called only for non-IDR pictures.

        Inputs:
            dpb         pointer to dpb data structure
            frame_num    frame number of the current picture
            is_ref_pic    flag to indicate if current picture is a reference or
                        non-reference picture

        Outputs:
            dpb         'buffer' possibly modified by inserting non-existing
                        pictures with sliding window marking process

        Returns:
            HANTRO_OK   success
            HANTRO_NOK  error in sliding window reference picture marking or
                        frame_num equal to previous reference frame used for
                        a reference picture

------------------------------------------------------------------------------*/
u32 h264bsdCheckGapsInFrameNum(dpbStorage_t * dpb, u32 frame_num, u32 is_ref_pic,
                               u32 gaps_allowed) {

  /* Variables */

  u32 un_used_short_term_frame_num;
  storage_t *storage = (storage_t* )dpb->storage;

#ifndef ASIC_TRACE_SUPPORT
  u32 dmv_buf_id = 0;
#endif

#if 0
  const void *tmp;
#endif
  /* Code */

  ASSERT(dpb);
  ASSERT(dpb->fullness <= dpb->dpb_size);
  ASSERT(frame_num < dpb->max_frame_num);


  /* If max_ref_frames = 1, gap is not allowed */
  if (dpb->max_ref_frames == 1)
    gaps_allowed = 0;

  if(!gaps_allowed) {
    /* FIXME: below code may need cause side-effect, need to be refined */
#ifndef H264_IGNORE_FRAME_GAP
    u32 ret = HANTRO_OK;
    if((frame_num != dpb->prev_ref_frame_num) &&
        (frame_num != ((dpb->prev_ref_frame_num + 1) % dpb->max_frame_num))) {
      ret = HANTRO_NOK;
      DPB_TRACE("gap detected. frame_num %d -> %d\n", dpb->prev_ref_frame_num, frame_num);
    }

    if(is_ref_pic)
      dpb->prev_ref_frame_num = frame_num;
    else if(frame_num != dpb->prev_ref_frame_num) {
      dpb->prev_ref_frame_num =
        (frame_num + dpb->max_frame_num - 1) % dpb->max_frame_num;
    }
    return ret;
#else
    return HANTRO_OK;
#endif
  }

  if((frame_num != dpb->prev_ref_frame_num) &&
      (frame_num != ((dpb->prev_ref_frame_num + 1) % dpb->max_frame_num))) {
    un_used_short_term_frame_num = (dpb->prev_ref_frame_num + 1) % dpb->max_frame_num;
#if 1
    u32 short_refs = 0;
    u32 long_refs = 0;

    /* find short term picture */
    for(u32 i = 0; i < dpb->dpb_size; i++) {
      if((dpb->buffer[i].status[0] == SHORT_TERM) ||
        (dpb->buffer[i].status[1] == SHORT_TERM)) {
        short_refs++;
      }
      if(IS_LONG_TERM_F(dpb->buffer[i])) {
        long_refs++;
      }
    }
    ASSERT (short_refs || long_refs);
#endif

#if 0
    /* store data pointer of last buffer position to be used as next
     * "allocated" data pointer. if last buffer position after this process
     * contains data pointer located in out_buf (buffer placed in the output
     * shall not be overwritten by the current picture) */
    (void)h264bsdAllocateDpbImage(dpb);
    tmp = dpb->current_out->data;

    {
      u32 i;
      /* find first unused and not-to-be-displayed pic */
      for(i = 0; i <= dpb->dpb_size; i++) {
        if(!dpb->buffer[i].to_be_displayed && !IS_REFERENCE_F(dpb->buffer[i]))
          break;
      }

      ASSERT(i <= dpb->dpb_size);

      dpb->current_out = &dpb->buffer[i];
      dpb->current_out_pos = i;
      dpb->current_out->status[0] = dpb->current_out->status[1] = EMPTY;
    }
#endif

    do {
      SetPicNums(dpb, un_used_short_term_frame_num);
      if (dpb->num_ref_frames == dpb->max_ref_frames && long_refs == 0) {
        sliceHeader_t *slice_header = storage->slice_header + 1;
        /* find short term picture */
        i32 index = -1;
        u32 pic_num = 0;
        short_refs = 0;
        /* find the oldest short term picture */
        for(u32 i = 0; i < dpb->dpb_size; i++) {
          if(IS_SHORT_TERM_F(dpb->buffer[i])) {
            if(dpb->buffer[i].pic_num < pic_num || index == -1) {
              index = (i32) i;
              pic_num = dpb->buffer[i].pic_num;
            }
          }
          if((dpb->buffer[i].status[0] == SHORT_TERM) ||
            (dpb->buffer[i].status[1] == SHORT_TERM)) {
            short_refs++;
          }
        }

        if (!IS_I_SLICE(slice_header->slice_type) && index >= 0 && short_refs == 1) {
          if((dpb->buffer[index].status[0] == SHORT_TERM) ||
            (dpb->buffer[index].status[1] == SHORT_TERM)) {
            dpb->buffer[index].frame_num =
                  (frame_num + dpb->max_frame_num - 1) % dpb->max_frame_num;
            dpb->buffer[index].pic_num =
                  (i32) (frame_num + dpb->max_frame_num - 1) % dpb->max_frame_num;
            un_used_short_term_frame_num = (frame_num + dpb->max_frame_num - 1) % dpb->max_frame_num;
            break;
          }
        }
      }

      if(SlidingWindowRefPicMarking(dpb) != HANTRO_OK) {
        return (HANTRO_NOK);
      }

      /* output pictures if buffer full */
      while(dpb->fullness >= dpb->dpb_size) {
        u32 ret;

        ASSERT(!dpb->no_reordering);
        ret = OutputPicture(dpb);
        ASSERT(ret == HANTRO_OK);
        (void) ret;
      }

      /* add to end of list */
      /*
       * ASSERT(!dpb->buffer[dpb->dpb_size].to_be_displayed &&
       * !IS_REFERENCE(dpb->buffer[dpb->dpb_size])); */
#if 0
      (void)h264bsdAllocateDpbImage(dpb);
#else

      /* find first unused dmv buffer */
#ifndef ASIC_TRACE_SUPPORT
      if (dpb->tot_dmv_buffers > 0 && storage->pp_enabled &&
          storage->high10p_mode) {
        pthread_mutex_lock(dpb->dmv_buffer_mutex);
        for (dmv_buf_id = 0; dmv_buf_id < dpb->tot_dmv_buffers; dmv_buf_id++) {
          if (!(dpb->dmv_buf_status[dmv_buf_id] & BUF_BIND)) {
            break;
          }
        }
        //ASSERT(dmv_buf_id < dpb->tot_dmv_buffers);
        pthread_mutex_unlock(dpb->dmv_buffer_mutex);
      }

      if (dmv_buf_id == dpb->tot_dmv_buffers) {
        pthread_mutex_lock(dpb->dmv_buffer_mutex);
        dmv_buf_id = 0;
        while (dmv_buf_id < dpb->tot_dmv_buffers) {
          if (dpb->dmv_buf_status[dmv_buf_id] == BUF_FREE) {
            break;
          }

          dmv_buf_id++;
          if (dmv_buf_id == dpb->tot_dmv_buffers) {
            pthread_cond_wait(dpb->dmv_buffer_cv, dpb->dmv_buffer_mutex);
            dmv_buf_id = 0;
          }
        }
        pthread_mutex_unlock(dpb->dmv_buffer_mutex);
      }

#endif

      {
        u32 i;
        /* find first unused and not-to-be-displayed pic */
        for(i = 0; i <= dpb->dpb_size; i++) {
          if(!dpb->buffer[i].to_be_displayed && !IS_REFERENCE_F(dpb->buffer[i]))
            break;
        }

        ASSERT(i <= dpb->dpb_size);

        dpb->current_out = &dpb->buffer[i];
        dpb->current_out_pos = i;
      }
#endif
      SET_STATUS(*dpb->current_out, NON_EXISTING, FRAME);
      dpb->current_out->frame_num = un_used_short_term_frame_num;
      dpb->current_out->pic_num = (i32) un_used_short_term_frame_num;
      dpb->current_out->pic_order_cnt[0] = 0;
      dpb->current_out->pic_order_cnt[1] = 0;
      dpb->current_out->to_be_displayed = HANTRO_FALSE;
      dpb->fullness++;
      dpb->num_ref_frames++;

#ifndef ASIC_TRACE_SUPPORT
      if (storage->pp_enabled && storage->high10p_mode) {
        dpb->current_out->dmv_data = &dpb->dmv_buffers[dmv_buf_id];
        dpb->current_out->dmv_mem_idx = dmv_buf_id;
        H264BindDMVBuffer(dpb, dpb->current_out->dmv_data);
      }
#endif
      un_used_short_term_frame_num = (un_used_short_term_frame_num + 1) %
                                     dpb->max_frame_num;

    } while(un_used_short_term_frame_num != frame_num);
#if 0
    (void)h264bsdAllocateDpbImage(dpb);
    /* pictures placed in output buffer -> check that 'data' in
     * buffer position dpb_size is not in the output buffer (this will be
     * "allocated" by h264bsdAllocateDpbImage). If it is -> exchange data
     * pointer with the one stored in the beginning */
    if(dpb->num_out && !DISPLAY_SMOOTHING) {
      u32 i, idx;
      dpbPicture_t *buff = dpb->buffer;

      idx = dpb->out_index_r;
      for(i = 0; i < dpb->num_out; i++) {
        ASSERT(i < dpb->dpb_size);

        if(dpb->out_buf[idx].data == dpb->current_out->data) {
          /* find buffer position containing data pointer
           * stored in tmp
           */

          for(i = 0; i < dpb->dpb_size; i++) {
            if(buff[i].data == tmp) {
              buff[i].data = dpb->current_out->data;
              dpb->current_out->data = (void *) tmp;
              break;
            }
          }

          break;
        }
        if (++idx > dpb->dpb_size)
          idx = 0;
      }
    }
#endif
  }
  /* frame_num for reference pictures shall not be the same as for previous
   * reference picture, otherwise accesses to pictures in the buffer cannot
   * be solved unambiguously */
  else if(is_ref_pic && frame_num == dpb->prev_ref_frame_num) {
    return (HANTRO_NOK);
  }

  /* save current frame_num in prev_ref_frame_num. For non-reference frame
   * prevFrameNum is set to frame number of last non-existing frame above */
  if(is_ref_pic)
    dpb->prev_ref_frame_num = frame_num;
  else if(frame_num != dpb->prev_ref_frame_num) {
    dpb->prev_ref_frame_num =
      (frame_num + dpb->max_frame_num - 1) % dpb->max_frame_num;
  }

  return (HANTRO_OK);
}

/*------------------------------------------------------------------------------

    Function: FindSmallestPicOrderCnt

        Functional description:
            Function to find picture with smallest picture order count. This
            will be the next picture in display order.

        Returns:
            pointer to the picture, NULL if no pictures to be displayed

------------------------------------------------------------------------------*/

dpbPicture_t *FindSmallestPicOrderCnt(dpbStorage_t * dpb) {

  /* Variables */

  u32 i;
  i32 pic_order_cnt;
  dpbPicture_t *tmp;

  /* Code */

  ASSERT(dpb);

  pic_order_cnt = 0x7FFFFFFF;
  tmp = NULL;

  for(i = 0; i <= dpb->dpb_size; i++) {
    /* TODO: currently only outputting frames, asssumes that fields of a
     * frame are output consecutively */
    if(dpb->buffer[i].to_be_displayed &&
        GET_POC(dpb->buffer[i]) < pic_order_cnt)
      /*
       * MIN(dpb->buffer[i].pic_order_cnt[0],dpb->buffer[i].pic_order_cnt[1]) <
       * pic_order_cnt &&
       * dpb->buffer[i].status[0] != EMPTY &&
       * dpb->buffer[i].status[1] != EMPTY)
       */
    {
      if(dpb->buffer[i].pic_order_cnt[1] >= pic_order_cnt) {
        DPB_TRACE("HEP %d %d\n", dpb->buffer[i].pic_order_cnt[1],
                     pic_order_cnt);
      }
      tmp = dpb->buffer + i;
      pic_order_cnt = GET_POC(dpb->buffer[i]);
    }
  }
  return (tmp);

}

/*------------------------------------------------------------------------------

    Function: OutputPicture

        Functional description:
            Function to put next display order picture into the output buffer.

        Returns:
            HANTRO_OK      success
            HANTRO_NOK     no pictures to display

------------------------------------------------------------------------------*/

u32 OutputPicture(dpbStorage_t * dpb) {

  /* Variables */

  dpbPicture_t *tmp;
  dpbOutPicture_t *dpb_out;

  /* Code */

  ASSERT(dpb);

  if(dpb->no_reordering)
    return (HANTRO_NOK);

  tmp = FindSmallestPicOrderCnt(dpb);

  /* no pictures to be displayed */
  if(tmp == NULL)
    return (HANTRO_NOK);

  /* if output buffer full -> ignore oldest */
  if (dpb->num_out == dpb->dpb_size + 1) {
    /* it seems that output overflow can occur with corrupted streams
     * and display smoothing mode
     */

    ClearOutput(dpb->fb_list, dpb->out_buf[dpb->out_index_r].mem_idx);

    dpb->out_index_r++;
    if (dpb->out_index_r == dpb->dpb_size + 1)
      dpb->out_index_r = 0;
    dpb->num_out--;
  }

  /* remove it from DPB */
  tmp->to_be_displayed = HANTRO_FALSE;

#if 0
  if(tmp->openB_flag) {
    if(!IS_REFERENCE_F(*tmp)) {
      if (dpb->fullness)
        dpb->fullness--;
    }
    tmp->openB_flag = 0;
    return (HANTRO_OK);
  }
#endif

  /* updated output list */
  dpb_out = &dpb->out_buf[dpb->out_index_w]; /* next output */
  dpb_out->data = tmp->data;
  dpb_out->pp_data = tmp->ds_data;
  dpb_out->dmv_data = tmp->dmv_data;
  dpb_out->is_idr[0] = tmp->is_idr[0];
  dpb_out->is_idr[1] = tmp->is_idr[1];
  dpb_out->pic_id = tmp->pic_id;
  dpb_out->pic_code_type[0] = tmp->pic_code_type[0];
  dpb_out->pic_code_type[1] = tmp->pic_code_type[1];
  dpb_out->decode_id[0] = tmp->decode_id[0];
  dpb_out->decode_id[1] = tmp->decode_id[1];
  dpb_out->sei_param[0] = tmp->sei_param[0];
  dpb_out->sei_param[1] = tmp->sei_param[1];
  dpb_out->error_ratio[0] = tmp->error_ratio[0];
  dpb_out->error_ratio[1] = tmp->error_ratio[1];
  dpb_out->error_info = tmp->error_info;
  dpb_out->interlaced = dpb->interlaced;
  dpb_out->field_picture = tmp->is_field_pic;
  dpb_out->mem_idx = tmp->mem_idx;
  dpb_out->tiled_mode = tmp->tiled_mode;
  dpb_out->crop = tmp->crop;
  dpb_out->pic_width = tmp->pic_width;
  dpb_out->pic_height = tmp->pic_height;
  dpb_out->sar_width = tmp->sar_width;
  dpb_out->sar_height = tmp->sar_height;
  dpb_out->top_field = tmp->is_bottom_field ? 0 : 1;
  dpb_out->pic_struct = tmp->pic_struct;
  dpb_out->corrupted_second_field = tmp->corrupted_second_field;
  dpb_out->bit_depth_luma = dpb->bit_depth_luma;
  dpb_out->bit_depth_chroma = dpb->bit_depth_chroma;
  dpb_out->mono_chrome = dpb->mono_chrome;
  dpb_out->is_openb = tmp->openB_flag;
  dpb_out->cycles_per_mb = tmp->cycles_per_mb;
  dpb_out->chroma_format_idc = tmp->chroma_format_idc;
  dpb_out->is_gdr_frame = tmp->is_gdr_frame;
  dpb_out->temporal_id = tmp->temporal_id;
#ifdef FPGA_PERF_AND_BW
  dpb_out->bitrate_4k60fps = tmp->bitrate_4k60fps;
  dpb_out->bwrd_in_fs = tmp->bwrd_in_fs;
  dpb_out->bwwr_in_fs = tmp->bwwr_in_fs;
#endif

  if(tmp->is_field_pic) {
    if(tmp->status[0] == EMPTY || tmp->status[1] == EMPTY || tmp->corrupted_second_field) {
      dpb_out->field_picture = 1;
      dpb_out->top_field = (tmp->status[0] == EMPTY) ? 0 : 1;
      if (tmp->corrupted_second_field)
        dpb_out->top_field = (dpb_out->pic_struct == TOPFIELD) ? 1 : 0;

      DPB_TRACE("dec pic %d MISSING FIELD! %s\n", dpb_out->pic_id,
                   dpb_out->top_field ? "BOTTOM" : "TOP");
    }
  }

  dpb->num_out++;
  dpb->out_index_w++;
  if (dpb->out_index_w == dpb->dpb_size + 1)
    dpb->out_index_w = 0;

  if(!IS_REFERENCE_F(*tmp)) {
    if (dpb->fullness)
      dpb->fullness--;
  }

  MarkTempOutput(dpb->fb_list, tmp->mem_idx);

  return (HANTRO_OK);
}

/*------------------------------------------------------------------------------

    Function: h264bsdDpbOutputPicture

        Functional description:
            Function to get next display order picture from the output buffer.

        Return:
            pointer to output picture structure, NULL if no pictures to
            display

------------------------------------------------------------------------------*/

dpbOutPicture_t *h264bsdDpbOutputPicture(dpbStorage_t * dpb) {

  /* Variables */

  u32 tmp_idx;

  /* Code */

  DPB_TRACE("h264bsdDpbOutputPicture: index %d outnum %d\n", (dpb->num_out -
               ((dpb->out_index_w - dpb->out_index_r + dpb->dpb_size + 1)%(dpb->dpb_size+1))),
               dpb->num_out);

  if(dpb->num_out && !dpb->no_output) {
    tmp_idx = dpb->out_index_r++;
    if (dpb->out_index_r == dpb->dpb_size + 1)
      dpb->out_index_r = 0;
    dpb->num_out--;
    dpb->prev_out_idx = dpb->out_buf[tmp_idx].mem_idx;

    return (dpb->out_buf + tmp_idx);
  } else
    return (NULL);
}

/*------------------------------------------------------------------------------

    Function: h264bsdFlushDpb

        Functional description:
            Function to flush the DPB. Function puts all pictures needed for
            display into the output buffer. This function shall be called in
            the end of the stream to obtain pictures buffered for display
            re-ordering purposes.

------------------------------------------------------------------------------*/
void h264bsdFlushDpb(dpbStorage_t * dpb) {
  u32 i;

  if(dpb->delayed_out != 0) {
    DPB_TRACE("%s","h264bsdFlushDpb: Output all delayed pictures!\n");
    dpb->delayed_out = 0;
    dpb->current_out->to_be_displayed = 0; /* remove it from output list */
  }

  /* output all pictures */
  while(OutputPicture(dpb) == HANTRO_OK) ;

  /* flush frames from dpb */
  for(i = 0; i < 16; i++) {
    SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
    H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
    dpb->buffer[i].to_be_displayed = 0;
    DpbBufFree(dpb, i);
  }

  dpb->fullness = 0;
  dpb->num_ref_frames = 0;
  dpb->flushed = 1;
  dpb->no_output = 0;
}

/*------------------------------------------------------------------------------

    Function: h264bsdFreeDpb

        Functional description:
            Function to free memories reserved for the DPB.

------------------------------------------------------------------------------*/

void h264bsdFreeDpb(
  const void *dwl,
  dpbStorage_t * dpb) {

  /* Variables */

  u32 i;

  /* Code */

  ASSERT(dpb);

  (void)dwl;

  for(i = 0; i < dpb->tot_buffers; i++) {
    if(DWL_DEVMEM_VAILD(dpb->pic_buffers[i])) {
      if (((storage_t *)(dpb->storage))->pp_enabled) {
        DWLFreeRefFrm(dwl, dpb->pic_buffers+i);
      }
      if(dpb->pic_buff_id[i] != FB_NOT_VALID_ID)
        ReleaseId(dpb->fb_list, dpb->pic_buff_id[i]);
    }
  }

  if(dpb->out_buf != NULL) {
    DWLfree(dpb->out_buf);
    dpb->out_buf = NULL;
  }

}

/*------------------------------------------------------------------------------

    Function: ShellSort

        Functional description:
            Sort pictures in the buffer. Function implements Shell's method,
            i.e. diminishing increment sort. See e.g. "Numerical Recipes in C"
            for more information.

------------------------------------------------------------------------------*/

void ShellSort(dpbStorage_t * dpb, u32 * list, u32 type, i32 par) {
  u32 i, j;
  u32 step;
  u32 tmp;
  dpbPicture_t *p_pic = dpb->buffer;
  u32 num = dpb->dpb_size + 1;
  ComparePicturesCallBack cmpFunc;

  step = 7;

  if(type)
    cmpFunc = ComparePicturesB;
  else
    cmpFunc = ComparePictures;

  while(step) {
    for(i = step; i < num; i++) {
      tmp = list[i];
      j = i;
      while(j >= step &&
            cmpFunc(p_pic + list[j - step], p_pic + tmp, par) > 0) {
        list[j] = list[j - step];
        j -= step;
      }
      list[j] = tmp;
    }
    step >>= 1;
  }
}

/*------------------------------------------------------------------------------

    Function: ShellSortF

        Functional description:
            Sort pictures in the buffer. Function implements Shell's method,
            i.e. diminishing increment sort. See e.g. "Numerical Recipes in C"
            for more information.

------------------------------------------------------------------------------*/

void ShellSortF(dpbStorage_t * dpb, u32 * list, u32 type, i32 par) {
  u32 i, j;
  u32 step;
  u32 tmp;
  dpbPicture_t *p_pic = dpb->buffer;
  u32 num = dpb->dpb_size + 1;

  step = 7;

  while(step) {
    for(i = step; i < num; i++) {
      tmp = list[i];
      j = i;
      while(j >= step &&
            (type ? CompareFieldsB(p_pic + list[j - step], p_pic + tmp, par)
             : CompareFields(p_pic + list[j - step], p_pic + tmp)) > 0) {
        list[j] = list[j - step];
        j -= step;
      }
      list[j] = tmp;
    }
    step >>= 1;
  }
}

/* picture marked as unused and not to be displayed -> buffer is free for next
 * decoded pictures */
void DpbBufFree(dpbStorage_t *dpb, u32 i) {

  if(dpb->num_ref_frames)
    dpb->num_ref_frames--;

  if(!dpb->buffer[i].to_be_displayed && dpb->fullness > 0) {
    dpb->fullness--;
    SET_SEI_UNUSED(dpb->buffer[i].sei_param);
  }

}

/*------------------------------------------------------------------------------
    Function name   : h264DpbAdjStereoOutput
    Description     :
    Return type     : void
    Argument        : dpbStorage_t * dpb
    Argument        : const image_t * image
------------------------------------------------------------------------------*/
void h264DpbAdjStereoOutput(dpbStorage_t * dpb, u32 target_count) {

  while((dpb->num_out < target_count) && (OutputPicture(dpb) == HANTRO_OK));

  if (dpb->num_out > target_count) {
    dpb->num_out = target_count;
    dpb->out_index_w = dpb->out_index_r + dpb->num_out;
    if (dpb->out_index_w > dpb->dpb_size)
      dpb->out_index_w -= dpb->dpb_size;
  }

}

static u32  GetDpbOutputTime(dpbPicture_t *pic) {
  u32 time0, time1;
  if (pic->is_field_pic) {
    if (pic->status[0] != EMPTY && pic->status[1] != EMPTY) {
      time0 = (u32)(pic->dpb_output_time[0] * 1000);
      time1 = (u32)(pic->dpb_output_time[1] * 1000);
      return MAX(time0,time1);
    } else {
      time0 = (pic->status[0] == EMPTY ? 0xFFFFFFFF : (u32)(pic->dpb_output_time[0] * 1000));
      time1 = (pic->status[1] == EMPTY ? 0xFFFFFFFF : (u32)(pic->dpb_output_time[1] * 1000));
      return MIN(time0,time1);
    }
  } else
    return((u32)(pic->dpb_output_time[0] * 1000));
}

dpbPicture_t *FindSmallestDpbTime(dpbStorage_t * dpb) {

  /* Variables */

  u32 i;
  dpbPicture_t *tmp;
  dpbPicture_t *tmppoc;
  u32 cpb_removal_time;
  u32 dpb_output_time;
  i32 pic_order_cnt;
  /* Code */

  ASSERT(dpb);

  cpb_removal_time = (u32)(dpb->cpb_removal_time * 1000);
  pic_order_cnt = 0x7FFFFFFF;
  tmp = NULL;
  tmppoc = NULL;

  for(i = 0; i <= dpb->dpb_size; i++) {
    /* TODO: currently only outputting frames, asssumes that fields of a
     * frame are output consecutively */
    dpb_output_time = GetDpbOutputTime(&dpb->buffer[i]);
    if(dpb->buffer[i].to_be_displayed && (dpb_output_time <= cpb_removal_time)) {
      tmp = dpb->buffer + i;
      cpb_removal_time = dpb_output_time;
    }
  }
  if (tmp != NULL) {
    for(i = 0; i <= dpb->dpb_size; i++) {
      /* TODO: currently only outputting frames, asssumes that fields of a
       * frame are output consecutively */
      if(dpb->buffer[i].to_be_displayed &&
          GET_POC(dpb->buffer[i]) < pic_order_cnt) {
        tmppoc = dpb->buffer + i;
        pic_order_cnt = GET_POC(dpb->buffer[i]);
      }
    }
  }
  if (tmp == tmppoc)
    return (tmp);
  else
    return (tmppoc);
}

u32 h264DpbHRDBumping(dpbStorage_t * dpb) {

  /* Variables */

  dpbPicture_t *tmp;
  dpbOutPicture_t *dpb_out;

  /* Code */

  ASSERT(dpb);

  if(dpb->no_reordering)
    return (HANTRO_NOK);

  tmp = FindSmallestDpbTime(dpb);

  /* no pictures to be displayed */
  if(tmp == NULL)
    return (HANTRO_NOK);
  /* if output buffer full -> ignore oldest */
  if (dpb->num_out == dpb->dpb_size + 1) {
    /* it seems that output overflow can occur with corrupted streams
     * and display smoothing mode
     */

    ClearOutput(dpb->fb_list, dpb->out_buf[dpb->out_index_r].mem_idx);

    dpb->out_index_r++;
    if (dpb->out_index_r == dpb->dpb_size + 1)
      dpb->out_index_r = 0;
    dpb->num_out--;
  }
  tmp->to_be_displayed = HANTRO_FALSE;

#if 0
  if(tmp->openB_flag) {
    if(!IS_REFERENCE_F(*tmp)) {
      if (dpb->fullness)
        dpb->fullness--;
    }
    tmp->openB_flag = 0;
    return (HANTRO_OK);
  }
#endif

  /* updated output list */
  dpb_out = &dpb->out_buf[dpb->out_index_w]; /* next output */
  dpb_out->data = tmp->data;
  dpb_out->pp_data = tmp->ds_data;
  dpb_out->dmv_data = tmp->dmv_data;
  dpb_out->is_idr[0] = tmp->is_idr[0];
  dpb_out->is_idr[1] = tmp->is_idr[1];
  dpb_out->pic_id = tmp->pic_id;
  dpb_out->pic_code_type[0] = tmp->pic_code_type[0];
  dpb_out->pic_code_type[1] = tmp->pic_code_type[1];
  dpb_out->decode_id[0] = tmp->decode_id[0];
  dpb_out->decode_id[1] = tmp->decode_id[1];
  dpb_out->sei_param[0] = tmp->sei_param[0];
  dpb_out->sei_param[1] = tmp->sei_param[1];
  dpb_out->error_ratio[0] = tmp->error_ratio[0];
  dpb_out->error_ratio[1] = tmp->error_ratio[1];
  dpb_out->error_info = tmp->error_info;
  dpb_out->interlaced = dpb->interlaced;
  dpb_out->field_picture = tmp->is_field_pic;
  dpb_out->mem_idx = tmp->mem_idx;
  dpb_out->tiled_mode = tmp->tiled_mode;
  dpb_out->crop = tmp->crop;
  dpb_out->pic_width = tmp->pic_width;
  dpb_out->pic_height = tmp->pic_height;
  dpb_out->sar_width = tmp->sar_width;
  dpb_out->sar_height = tmp->sar_height;
  dpb_out->top_field = tmp->is_bottom_field ? 0 : 1;
  dpb_out->pic_struct = tmp->pic_struct;
  dpb_out->corrupted_second_field = tmp->corrupted_second_field;
  dpb_out->bit_depth_luma = dpb->bit_depth_luma;
  dpb_out->bit_depth_chroma = dpb->bit_depth_chroma;
  dpb_out->mono_chrome = dpb->mono_chrome;
  dpb_out->is_openb = tmp->openB_flag;
  dpb_out->cycles_per_mb = tmp->cycles_per_mb;
  dpb_out->chroma_format_idc = dpb->chroma_format_idc;
  dpb_out->is_gdr_frame = tmp->is_gdr_frame;
  dpb_out->temporal_id = dpb->svc_info.temporal_id;
#ifdef FPGA_PERF_AND_BW
  dpb_out->bitrate_4k60fps = tmp->bitrate_4k60fps;
  dpb_out->bwrd_in_fs = tmp->bwrd_in_fs;
  dpb_out->bwwr_in_fs = tmp->bwwr_in_fs;
#endif

  if(tmp->is_field_pic) {
    if(tmp->status[0] == EMPTY || tmp->status[1] == EMPTY || tmp->corrupted_second_field) {
      dpb_out->field_picture = 1;
      dpb_out->top_field = (tmp->status[0] == EMPTY) ? 0 : 1;
      if (tmp->corrupted_second_field)
        dpb_out->top_field = (dpb_out->pic_struct == TOPFIELD) ? 1 : 0;

      DPB_TRACE("dec pic %d MISSING FIELD! %s\n", dpb_out->pic_id,
                   dpb_out->top_field ? "BOTTOM" : "TOP");
    }
  }

  dpb->num_out++;
  dpb->out_index_w++;
  if (dpb->out_index_w == dpb->dpb_size + 1)
    dpb->out_index_w = 0;
  if(!IS_REFERENCE_F(*tmp)) {
    if (dpb->fullness)
      dpb->fullness--;
  }

  MarkTempOutput(dpb->fb_list, tmp->mem_idx);

  return (HANTRO_OK);
}

void h264EmptyDpb(dpbStorage_t *dpb) {
  u32 i;
  for(i = 0; i < 16 + 1; i++) {
      SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
      if (dpb->buffer[i].dmv_data != NULL) {
        H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
        H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
      }
      dpb->buffer[i].to_be_displayed = 0;
      dpb->buffer[i].pic_num = 0;
      dpb->buffer[i].frame_num = 0;
      dpb->buffer[i].is_field_pic = 0;
      dpb->buffer[i].is_bottom_field = 0;
      dpb->buffer[i].pic_struct = 0;
      dpb->buffer[i].corrupted_first_field_or_frame = 0;
      dpb->buffer[i].corrupted_second_field = 0;
      dpb->buffer[i].is_idr[0] = dpb->buffer[i].is_idr[1] = 0;
      dpb->buffer[i].pic_order_cnt[0] = dpb->buffer[i].pic_order_cnt[1] = 0;
      dpb->buffer[i].pic_code_type[0] = dpb->buffer[i].pic_code_type[1] = 0;
      dpb->buffer[i].dpb_output_time[0] = dpb->buffer[i].dpb_output_time[1] = 0;
      dpb->buffer[i].openB_flag = 0;
      dpb->buffer[i].cycles_per_mb = 0;
#ifdef FPGA_PERF_AND_BW
      dpb->buffer[i].bitrate_4k60fps = 0;
      dpb->buffer[i].bwrd_in_fs = 0;
      dpb->buffer[i].bwwr_in_fs = 0;
#endif

#ifdef USE_OMXIL_BUFFER
      if (dpb->storage != NULL && ((storage_t *)(dpb->storage))->pp_enabled == 0) {
        dpb->buffer[i].data = NULL;
        dpb->buffer[i].mem_idx = 0;
      }
#endif
  }

  if(dpb->fb_list) {
    RemoveTempOutputAll(dpb->fb_list);
    RemoveOutputAll(dpb->fb_list);
  }

#ifdef USE_OMXIL_BUFFER
  if (dpb->storage != NULL && ((storage_t *)(dpb->storage))->pp_enabled == 0) {
    for (i = 0; i < dpb->tot_buffers; i++) {
      if (DWL_DEVMEM_VAILD(dpb->pic_buffers[i])) {
        if (dpb->pic_buff_id[i] != FB_NOT_VALID_ID) {
          ReleaseId(dpb->fb_list, dpb->pic_buff_id[i]);
        }
      }
    }
    dpb->fb_list->free_buffers = 0;
  }
#endif
  if(dpb->fb_list)
  	ResetOutFifoInList(dpb->fb_list);

  for (i = 0; i <= dpb->dpb_size; i++) {
    dpb->buffer[i].error_ratio[0] = 0;
    dpb->buffer[i].error_ratio[1] = 0;
    dpb->buffer[i].error_info = DEC_NO_ERROR;
  }

  dpb->num_out = 0;
  dpb->out_index_w = 0;
  dpb->out_index_r = 0;
  dpb->current_out = NULL;
  dpb->cpb_removal_time = 0;
  dpb->bumping_flag = 0;
  dpb->current_out_pos = 0;
  dpb->max_long_term_frame_idx = NO_LONG_TERM_FRAME_INDICES;
  dpb->num_ref_frames = 0;
  dpb->fullness = 0;
  dpb->prev_ref_frame_num = 0;
  dpb->flushed = 0;
#ifdef USE_OMXIL_BUFFER
  dpb->tot_buffers = dpb->tot_buffers_reserved;
#endif
  dpb->delayed_out = 0;
  dpb->delayed_id = 0;
#ifdef CLEAR_HDRINFO_IN_SEEK
  dpb->interlaced = 0;
#endif
  dpb->no_output = 0;
  dpb->prev_out_idx = INVALID_MEM_IDX;
  dpb->try_recover_dpb = 0;
  dpb->b_updated = 0;
}

void h264DpbRecover(dpbStorage_t *dpb, u32 curr_frame_num, i32 curr_poc,
                    u32 error_policy) {
  u32 i = 0;
  dpbPicture_t *buffer = dpb->buffer;
  storage_t *storage = dpb->storage;
  u32 min_ref_frame_num, max_ref_frame_num;

  ASSERT(dpb->try_recover_dpb == HANTRO_TRUE);

  if (dpb->max_ref_frames <= curr_frame_num) {
    min_ref_frame_num = curr_frame_num - dpb->max_ref_frames;
  } else {
    min_ref_frame_num = curr_frame_num + dpb->max_frame_num - dpb->max_ref_frames;
  }

  if (curr_frame_num + dpb->max_ref_frames >= dpb->max_frame_num) {
    max_ref_frame_num = curr_frame_num + dpb->max_ref_frames - dpb->max_frame_num;
  } else {
    max_ref_frame_num = curr_frame_num + dpb->max_ref_frames;
  }

  if (error_policy & DEC_EC_SEEK_NEXT_I) {
    /* Error recovery of skipping pictures till next I slice, output all pictures
       in dpb and clear it, just like IDR. */
    (void)h264DpbMarkAllUnused(dpb);
    dpb->try_recover_dpb = HANTRO_FALSE;
    return;
  }

  for (i = 0; i <= dpb->dpb_size; i++) {
    if (buffer + i == dpb->current_out)
      continue;
    else if (IS_SHORT_TERM_F(buffer[i]) &&
             (((min_ref_frame_num <= max_ref_frame_num) &&
               (buffer[i].frame_num < min_ref_frame_num || buffer[i].frame_num > max_ref_frame_num)) ||
              ((min_ref_frame_num > max_ref_frame_num) &&
               (buffer[i].frame_num < min_ref_frame_num && buffer[i].frame_num > max_ref_frame_num)))) {
      buffer[i].status[0] = UNUSED;
      buffer[i].status[1] = UNUSED;
      H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
      H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
      if(storage->pp_enabled && dpb->buffer[i].to_be_displayed) {
        InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
        SET_SEI_UNUSED(dpb->buffer[i].sei_param);
      }
      buffer[i].to_be_displayed = 0;
      DpbBufFree(dpb, i);
    }

    else if (IS_UNUSED(buffer[i], FRAME) && buffer[i].to_be_displayed) {
      i32 diff_poc = (GET_POC(buffer[i]) > curr_poc) ?
                     GET_POC(buffer[i]) - curr_poc :
                     curr_poc - GET_POC(buffer[i]);

      if(buffer[i].to_be_displayed && diff_poc >= 64) {
        if(storage->pp_enabled && dpb->buffer[i].to_be_displayed) {
          InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
          SET_SEI_UNUSED(dpb->buffer[i].sei_param);
        }
        H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
        buffer[i].to_be_displayed = 0;
        DpbBufFree(dpb, i);
      }
    }
  }
  dpb->try_recover_dpb = HANTRO_FALSE;
}

u32 h264DpbMarkAllUnused(dpbStorage_t *dpb) {
  u32 i = 0;

  for(i = 0; i < MAX_DPB_SIZE; i++) {
    if(IS_REFERENCE_F(dpb->buffer[i]) &&
       &dpb->buffer[i] != dpb->current_out) {
      SET_STATUS(dpb->buffer[i], UNUSED, FRAME);
      H264UnBindDMVBuffer(dpb, dpb->buffer[i].dmv_data);
      DpbBufFree(dpb, i);
    }
  }

  /* output all pictures */
  while(OutputPicture(dpb) == HANTRO_OK)
    ;

  return (HANTRO_OK);
}

static u32 is_displayed(dpbStorage_t *dpb1, void *data)
{
  u32 i;
  for (i = 0; i < dpb1->dpb_size; i++) {
    if (dpb1->buffer[i].data == data
      && dpb1->buffer[i].to_be_displayed) {
      return 1;
    }
  }
  return 0;
}

void h264RemoveNoBumpOutput(dpbStorage_t *dpb0, dpbStorage_t *dpb1) {
  u32 i;
  i32 index;
  u32 id;
  storage_t *storage = dpb0->storage;
  u32 size = dpb0->num_out - dpb1->num_out;
  for(i = 0; i < size; i++) {
    index = dpb0->out_index_w - i - 1;
    if (index < 0)
      index += (dpb0->dpb_size + 1);
    id = (u32)index;
    if (storage->pp_enabled && !is_displayed(dpb1, dpb0->out_buf[id].data)) {
      InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb0->out_buf[id].pp_data)));
      H264ReturnDMVBuffer(&storage->dpb[0], dpb0->out_buf[id].dmv_data->bus_address);
      H264ReturnDMVBuffer(&storage->dpb[1], dpb0->out_buf[id].dmv_data->bus_address);
      SET_SEI_UNUSED(dpb0->out_buf[id].sei_param);
    }
    ClearTempOut(dpb0->fb_list, dpb0->out_buf[id].mem_idx);
  }
}

u32 h264FindDpbBufferId(dpbStorage_t *dpb) {
  u32 i, index = 0xFFFFFFFF;
  storage_t *storage = dpb->storage;
  if (!storage->pp_enabled) {
    for(i = 0; i < dpb->tot_buffers; i++) {
      if(DWL_DEVMEM_COMPARE_V2(*(dpb->current_out->data), *(dpb->buffer[i].data))) {
        index = i;
        break;
      }
    }
  } else {
    index = InputQueueFindBufferId(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->current_out->ds_data)));
  }
  return (index);
}

void RemoveTempPpOutputAll(dpbStorage_t *dpb) {
  i32 i;
  storage_t *storage = dpb->storage;
  if (storage->pp_enabled) {
    for (i = 0; i <= dpb->dpb_size; i++) {
      if ((dpb->fb_list->fb_stat[dpb->buffer[i].mem_idx].b_used & 0x08U)/*FB_TEMP_OUTPUT*/ ||
          (dpb->fb_list->fb_stat[dpb->buffer[i].mem_idx].b_used & 0x04U)/*FB_OUTPUT*/) {
        InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->buffer[i].ds_data)));
        H264ReturnDMVBuffer(dpb, dpb->buffer[i].dmv_data->bus_address);
        SET_SEI_UNUSED(dpb->buffer[i].sei_param);
      }
    }
  }
}

void RemoveUnmarkedPpBuffer(dpbStorage_t *dpb) {
  storage_t *storage = dpb->storage;

  i32 i = dpb->num_out;
  u32 tmp = dpb->out_index_r;
  u32 found = 0;

  while((i--) > 0) {
    if (tmp == dpb->dpb_size + 1)
      tmp = 0;

    if(dpb->out_buf[tmp].data == dpb->current_out->data) {
      found = 1;
      break;
    }
    tmp++;
  }


  if (!dpb->current_out->to_be_displayed &&
      !IS_REFERENCE_F(*(dpb->current_out)) &&
      !dpb->no_reordering && !found) {
    if (storage->pp_enabled && dpb->current_out->ds_data) {
      InputQueueReturnBuffer(storage->pp_buffer_queue, DWL_GET_DEVMEM_ADDR(*(dpb->current_out->ds_data)));
      SET_SEI_UNUSED(dpb->current_out->sei_param);
    }
    if (dpb->current_out->dmv_data)
      H264ReturnDMVBuffer(dpb, dpb->current_out->dmv_data->bus_address);
  }
}


void H264BindDMVBuffer(dpbStorage_t *dpb, struct DWLLinearMem *dmv) {
  u32 i;

  if (dmv == NULL)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address == dmv->bus_address) {
      dpb->dmv_buf_status[i] |= BUF_BIND;
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void H264UnBindDMVBuffer(dpbStorage_t *dpb, struct DWLLinearMem *dmv) {
  u32 i;

  if (dmv == NULL)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
    for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address ==dmv->bus_address) {
      dpb->dmv_buf_status[i] &= ~BUF_BIND;
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void H264InvalidDMVBuffer(dpbStorage_t *dpb) {
  u32 i;

  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    dpb->dmv_buf_valid_ref[i] = 0;
  }
}

void H264ValidDMVBuffer(dpbStorage_t *dpb, struct DWLLinearMem *dmv) {
  u32 i;

  if (dmv == NULL)
    return;

  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address == dmv->bus_address) {
      dpb->dmv_buf_valid_ref[i] = 1;
      break;
    }
  }
}

void H264OutputDMVBuffer(dpbStorage_t *dpb, addr_t dmv_bus_address) {
  u32 i;

  if (!dmv_bus_address)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buffers[i].bus_address ==dmv_bus_address) {
      dpb->dmv_buf_status[i] |= BUF_OUTPUT;
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void H264ReturnDMVBuffer(dpbStorage_t *dpb, addr_t dmv_bus_address) {
  u32 i;
  addr_t dpb_buf_addr;

  if (!dmv_bus_address)
    return;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    dpb_buf_addr = dpb->dmv_buffers[i].bus_address  - dpb->dir_mv_offset;
    if (dmv_bus_address > dpb_buf_addr && dmv_bus_address <= dpb_buf_addr + dpb->n_int_buf_size) {
      dpb->dmv_buf_status[i] &= ~BUF_OUTPUT;
      pthread_cond_signal(dpb->dmv_buffer_cv);
      break;
    }
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}

void H264EnableDMVBuffer(dpbStorage_t *dpb, u32 core_id) {
  u32 i;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    if (dpb->dmv_buf_valid_ref[i])
      dpb->dmv_buf_status[i] |= (1 << (BUF_USED + core_id));
  }
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}


void H264DisableDMVBuffer(dpbStorage_t *dpb, u32 core_id) {
  u32 i;

  pthread_mutex_lock(dpb->dmv_buffer_mutex);
  for (i = 0; i < dpb->tot_dmv_buffers; i++) {
    //if (dpb->dmv_buf_status[i] & (1 << (BUF_USED + core_id)))
      dpb->dmv_buf_status[i] &= ~(1 << (BUF_USED + core_id));
  }
  pthread_cond_signal(dpb->dmv_buffer_cv);
  pthread_mutex_unlock(dpb->dmv_buffer_mutex);
}
