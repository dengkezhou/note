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

#include "h264hwd_storage.h"
#include "h264hwd_util.h"
#include "h264hwd_neighbour.h"
#include "h264hwd_slice_group_map.h"
#include "h264hwd_dpb.h"
#include "h264hwd_nal_unit.h"
#include "h264hwd_slice_header.h"
#include "h264hwd_seq_param_set.h"
#include "h264hwd_decoder.h"
#include "dwl.h"
#include "dec_log.h"
/*------------------------------------------------------------------------------
    2. External compiler flags
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
    3. Module defines
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    4. Local function prototypes
------------------------------------------------------------------------------*/

static u32 CheckPps(picParamSet_t * pps, seqParamSet_t * sps);

/*------------------------------------------------------------------------------

    Function name: h264bsdInitStorage

        Functional description:
            Initialize storage structure. Sets contents of the storage to '0'
            except for the active parameter set ids, which are initialized
            to invalid values.

        Inputs:

        Outputs:
            storage    initialized data stored here

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdInitStorage(storage_t * storage) {

  /* Variables */

  u32 i;

  /* Code */

  ASSERT(storage);

  (void) DWLmemset(storage, 0, sizeof(storage_t));

  storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
  for (i = 0; i < MAX_NUM_VIEWS; i++)
    storage->active_view_sps_id[i] = MAX_NUM_SEQ_PARAM_SETS;
  storage->old_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->aub->first_call_flag = HANTRO_TRUE;
  storage->sei_param_curr = NULL;
  storage->sei_param_num = 0;
}

/*------------------------------------------------------------------------------

    Function: h264bsdStoreSeqParamSet

        Functional description:
            Store sequence parameter set into the storage. If active SPS is
            overwritten -> check if contents changes and if it does, set
            parameters to force reactivation of parameter sets

        Inputs:
            storage        pointer to storage structure
            p_seq_param_set    pointer to param set to be stored

        Outputs:
            none

        Returns:
            HANTRO_OK                success
            MEMORY_ALLOCATION_ERROR  failure in memory allocation

------------------------------------------------------------------------------*/

u32 h264bsdStoreSeqParamSet(storage_t * storage, seqParamSet_t * p_seq_param_set) {

  /* Variables */

  u32 id;

  /* Code */

  ASSERT(storage);
  ASSERT(p_seq_param_set);
  ASSERT(p_seq_param_set->seq_parameter_set_id < MAX_NUM_SEQ_PARAM_SETS);

  id = p_seq_param_set->seq_parameter_set_id;

  /* seq parameter set with id not used before -> allocate memory */
  if(storage->sps[id] == NULL) {
    ALLOCATE(storage->sps[id], 1, seqParamSet_t);
    if(storage->sps[id] == NULL)
      return (MEMORY_ALLOCATION_ERROR);
  }
  /* sequence parameter set with id equal to id of active sps */
  else if(id == storage->active_view_sps_id[0] ||
          id == storage->active_view_sps_id[1] ) {
    /* if seq parameter set contents changes
     *    -> overwrite and re-activate when next IDR picture decoded
     *    ids of active param sets set to invalid values to force
     *    re-activation. Memories allocated for old sps freed
     * otherwise free memeries allocated for just decoded sps and
     * continue */
    u32 view_id = id == storage->active_view_sps_id[1];
    if(h264bsdCompareSeqParamSets(p_seq_param_set,
                                  storage->active_view_sps[view_id]) != 0) {
      FREE(storage->sps[id]->offset_for_ref_frame);
      FREE(storage->sps[id]->vui_parameters);
      /* overwriting active sps of current view */
      if (view_id == storage->view) {
        storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS + 1;
        storage->active_sps = NULL;
        storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS + 1;
        storage->active_pps = NULL;
        storage->old_sps_id = MAX_NUM_SEQ_PARAM_SETS + 1;
      }
      storage->active_view_sps_id[view_id] = MAX_NUM_SEQ_PARAM_SETS + 1;
      storage->active_view_sps[storage->view] = NULL;
    } else {
      FREE(p_seq_param_set->offset_for_ref_frame);
      FREE(p_seq_param_set->vui_parameters);
      return (HANTRO_OK);
    }
  }
  /* overwrite seq param set other than active one -> free memories
   * allocated for old param set */
  else {
    FREE(storage->sps[id]->offset_for_ref_frame);
    FREE(storage->sps[id]->vui_parameters);
  }

  *storage->sps[id] = *p_seq_param_set;

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: h264bsdStorePicParamSet

        Functional description:
            Store picture parameter set into the storage. If active PPS is
            overwritten -> check if active SPS changes and if it does -> set
            parameters to force reactivation of parameter sets

        Inputs:
            storage        pointer to storage structure
            p_pic_param_set    pointer to param set to be stored

        Outputs:
            none

        Returns:
            HANTRO_OK                success
            MEMORY_ALLOCATION_ERROR  failure in memory allocation

------------------------------------------------------------------------------*/

void h264bsdModifyScalingLists(storage_t *storage, picParamSet_t *p_pic_param_set) {
  u32 i;
  seqParamSet_t *sps;

  sps = storage->sps[p_pic_param_set->seq_parameter_set_id];
  /* SPS not yet decoded -> cannot copy */
  /* TODO: set flag to handle "missing" SPS lists properly */
  if (sps == NULL)
    return;

  if (!p_pic_param_set->scaling_matrix_present_flag &&
      sps->scaling_matrix_present_flag) {
    p_pic_param_set->scaling_matrix_present_flag = 1;
    (void)DWLmemcpy(p_pic_param_set->scaling_list, sps->scaling_list,
                    sizeof(sps->scaling_list));
  } else if (sps->scaling_matrix_present_flag) {
    if (!p_pic_param_set->scaling_list_present[0]) {
      /* we trust our memcpy */
      (void)DWLmemcpy(p_pic_param_set->scaling_list[0], sps->scaling_list[0],
                      16*sizeof(u8));
      for (i = 1; i < 3; i++)
        if (!p_pic_param_set->scaling_list_present[i])
          (void)DWLmemcpy(p_pic_param_set->scaling_list[i],
                          p_pic_param_set->scaling_list[i-1],
                          16*sizeof(u8));
    }
    if (!p_pic_param_set->scaling_list_present[3]) {
      (void)DWLmemcpy(p_pic_param_set->scaling_list[3], sps->scaling_list[3],
                      16*sizeof(u8));
      for (i = 4; i < 6; i++)
        if (!p_pic_param_set->scaling_list_present[i])
          (void)DWLmemcpy(p_pic_param_set->scaling_list[i],
                          p_pic_param_set->scaling_list[i-1],
                          16*sizeof(u8));
    }
    for (i = 6; i < 8; i++)
      if (!p_pic_param_set->scaling_list_present[i])
        (void)DWLmemcpy(p_pic_param_set->scaling_list[i], sps->scaling_list[i],
                        64*sizeof(u8));
  }
}

u32 h264bsdStorePicParamSet(storage_t * storage, picParamSet_t * p_pic_param_set) {

  /* Variables */

  u32 id;

  /* Code */

  ASSERT(storage);
  ASSERT(p_pic_param_set);
  ASSERT(p_pic_param_set->pic_parameter_set_id < MAX_NUM_PIC_PARAM_SETS);
  ASSERT(p_pic_param_set->seq_parameter_set_id < MAX_NUM_SEQ_PARAM_SETS);

  id = p_pic_param_set->pic_parameter_set_id;

  /* pic parameter set with id not used before -> allocate memory */
  if(storage->pps[id] == NULL) {
    ALLOCATE(storage->pps[id], 1, picParamSet_t);
    if(storage->pps[id] == NULL)
      return (MEMORY_ALLOCATION_ERROR);
  }
  /* picture parameter set with id equal to id of active pps */
  else if(id == storage->active_pps_id) {
    /* check whether seq param set changes, force re-activation of
     * param set if it does. Set active_sps_id to invalid value to
     * accomplish this */
    if(p_pic_param_set->seq_parameter_set_id != storage->active_sps_id) {
      storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS + 1;
    }
    /* free memories allocated for old param set */
    FREE(storage->pps[id]->run_length);
    FREE(storage->pps[id]->top_left);
    FREE(storage->pps[id]->bottom_right);
    FREE(storage->pps[id]->slice_group_id);
  }
  /* overwrite pic param set other than active one -> free memories
   * allocated for old param set */
  else {
    FREE(storage->pps[id]->run_length);
    FREE(storage->pps[id]->top_left);
    FREE(storage->pps[id]->bottom_right);
    FREE(storage->pps[id]->slice_group_id);
  }

  /* Modify scaling_lists if necessary */
  h264bsdModifyScalingLists(storage, p_pic_param_set);

  *storage->pps[id] = *p_pic_param_set;

  /* to fix klocwork warning we have to allocate new memory for pStorage->pps[id] */
  if (p_pic_param_set->run_length) {
    ALLOCATE(storage->pps[id]->run_length,
        p_pic_param_set->num_slice_groups, u32);
    if (storage->pps[id]->run_length == NULL)
      return(MEMORY_ALLOCATION_ERROR);
    (void)DWLmemcpy(storage->pps[id]->run_length,
        p_pic_param_set->run_length, p_pic_param_set->num_slice_groups * sizeof(u32));
  }

  if (p_pic_param_set->top_left) {
    ALLOCATE(storage->pps[id]->top_left,
        p_pic_param_set->num_slice_groups - 1, u32);
    if (storage->pps[id]->top_left == NULL)
      return(MEMORY_ALLOCATION_ERROR);
    (void)DWLmemcpy(storage->pps[id]->top_left,
        p_pic_param_set->top_left, (p_pic_param_set->num_slice_groups - 1) * sizeof(u32));
  }

  if (p_pic_param_set->bottom_right) {
    ALLOCATE(storage->pps[id]->bottom_right,
        p_pic_param_set->num_slice_groups - 1, u32);
    if (storage->pps[id]->bottom_right == NULL)
      return(MEMORY_ALLOCATION_ERROR);
    (void)DWLmemcpy(storage->pps[id]->bottom_right,
      p_pic_param_set->bottom_right, (p_pic_param_set->num_slice_groups - 1) * sizeof(u32));
  }

  if (p_pic_param_set->slice_group_id) {
    ALLOCATE(storage->pps[id]->slice_group_id,
        p_pic_param_set->pic_size_in_map_units, u32);
    if (storage->pps[id]->slice_group_id == NULL)
      return(MEMORY_ALLOCATION_ERROR);
    (void)DWLmemcpy(storage->pps[id]->slice_group_id,
        p_pic_param_set->slice_group_id, p_pic_param_set->pic_size_in_map_units * sizeof(u32));
  }

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: h264bsdActivateParamSets

        Functional description:
            Activate certain SPS/PPS combination. This function shall be
            called in the beginning of each picture. Picture parameter set
            can be changed as wanted, but sequence parameter set may only be
            changed when the starting picture is an IDR picture.

            When new SPS is activated the function allocates memory for
            macroblock storages and slice group map and (re-)initializes the
            decoded picture buffer. If this is not the first activation the old
            allocations are freed and FreeDpb called before new allocations.

        Inputs:
            storage        pointer to storage data structure
            pps_id           identifies the PPS to be activated, SPS id obtained
                            from the PPS
            slice_type       identifies the type of current slice
            is_idr           flag to indicate if the picture is an IDR picture

        Outputs:
            none

        Returns:
            HANTRO_OK       success
            HANTRO_NOK      non-existing or invalid param set combination,
                            trying to change SPS with non-IDR picture
            MEMORY_ALLOCATION_ERROR     failure in memory allocation

------------------------------------------------------------------------------*/

u32 h264bsdActivateParamSets(storage_t * storage, u32 pps_id, u32 slice_type, u32 is_idr) {
  u32 tmp;

  ASSERT(storage);
  ASSERT(pps_id < MAX_NUM_PIC_PARAM_SETS);

  /* check that pps and corresponding sps exist */
  if((storage->pps[pps_id] == NULL) ||
      (storage->sps[storage->pps[pps_id]->seq_parameter_set_id] == NULL)) {
    return (HANTRO_NOK);
  }

  /* check that pps parameters do not violate picture size constraints */
  tmp = CheckPps(storage->pps[pps_id],
                 storage->sps[storage->pps[pps_id]->seq_parameter_set_id]);
  if(tmp != HANTRO_OK)
    return (tmp);

  /* first activation */
  if(storage->active_pps_id == MAX_NUM_PIC_PARAM_SETS) {
    storage->active_pps_id = pps_id;
    storage->active_pps = storage->pps[pps_id];
    storage->active_sps_id = storage->active_pps->seq_parameter_set_id;
    storage->active_view_sps_id[storage->view] =
      storage->active_pps->seq_parameter_set_id;
    storage->active_sps = storage->sps[storage->active_sps_id];
    storage->active_view_sps[storage->view] =
      storage->sps[storage->active_sps_id];
  } else if(pps_id != storage->active_pps_id) {
    /* sequence parameter set shall not change but before an IDR picture */
    if (storage->pps[pps_id]->seq_parameter_set_id !=
        storage->active_view_sps_id[storage->view]) {
      STREAMTRACE_I("%s","SEQ PARAM SET CHANGING...\n");
      if(is_idr || IS_I_SLICE(slice_type)) {
        storage->active_pps_id = pps_id;
        storage->active_pps = storage->pps[pps_id];
        storage->active_view_sps_id[storage->view] =
          storage->active_pps->seq_parameter_set_id;
        storage->active_view_sps[storage->view] =
          storage->sps[storage->active_view_sps_id[storage->view]];

        if (!storage->mvc_stream)
          storage->pending_flush = 1;
      } else {
        if (storage->view && storage->active_view_sps[1] == NULL)
          storage->view = 0;
        STREAMTRACE_I("%s","TRYING TO CHANGE SPS IN NON-IDR SLICE\n");
        return (HANTRO_NOK);
      }
    } else {
      storage->active_pps_id = pps_id;
      storage->active_pps = storage->pps[pps_id];
    }
  }
  /* In case this view uses same PPS as a previous view, and SPS has
   * not been activated for this view yet. */
  else if(storage->active_view_sps[storage->view] == NULL) {
    storage->active_sps_id = storage->active_pps->seq_parameter_set_id;
    storage->active_view_sps_id[storage->view] =
      storage->active_pps->seq_parameter_set_id;
    storage->active_sps = storage->sps[storage->active_sps_id];
    storage->active_view_sps[storage->view] =
      storage->sps[storage->active_sps_id];
  }

  if (/*is_idr ||*/ storage->view) {
    storage->num_views = storage->view != 0;
  }

  storage->active_sps_id = storage->active_view_sps_id[storage->view];
  storage->active_sps = storage->active_view_sps[storage->view];
  storage->dpb = storage->dpbs[storage->view];
  storage->slice_header = storage->slice_headers[storage->view];

  return (HANTRO_OK);
}

/*------------------------------------------------------------------------------

    Function: h264bsdResetStorage

        Functional description:
            Reset contents of the storage. This should be called before
            processing of new image is started.

        Inputs:
            storage    pointer to storage structure

        Outputs:
            none

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdResetStorage(storage_t * storage) {

  /* Variables */

  u32 i;

  /* Code */

  ASSERT(storage);

  storage->slice->num_decoded_mbs = 0;
  storage->slice->slice_id = 0;
  storage->prev_idr_pic_ready = HANTRO_FALSE;

  if(storage->mb != NULL) {
    for(i = 0; i < storage->pic_size_in_mbs; i++) {
      storage->mb[i].slice_id = 0;
      storage->mb[i].decoded = 0;
    }
  }
}

/*------------------------------------------------------------------------------

    Function: h264bsdIsStartOfPicture

        Functional description:
            Determine if the decoder is in the start of a picture. This
            information is needed to decide if h264bsdActivateParamSets and
            h264bsdCheckGapsInFrameNum functions should be called. Function
            considers that new picture is starting if no slice headers
            have been successfully decoded for the current access unit.

        Inputs:
            storage    pointer to storage structure

        Outputs:
            none

        Returns:
            HANTRO_TRUE        new picture is starting
            HANTRO_FALSE       not starting

------------------------------------------------------------------------------*/

u32 h264bsdIsStartOfPicture(storage_t * storage) {

  /* Variables */

  /* Code */

  if(storage->valid_slice_in_access_unit == HANTRO_FALSE)
    return (HANTRO_TRUE);
  else
    return (HANTRO_FALSE);

}

/*------------------------------------------------------------------------------

    Function: h264bsdIsEndOfPicture

        Functional description:
            Determine if the decoder is in the end of a picture. This
            information is needed to determine when deblocking filtering
            and reference picture marking processes should be performed.

            If the decoder is processing primary slices the return value
            is determined by checking the value of num_decoded_mbs in the
            storage. On the other hand, if the decoder is processing
            redundant slices the num_decoded_mbs may not contain valid
            informationa and each macroblock has to be checked separately.

        Inputs:
            storage    pointer to storage structure

        Outputs:
            none

        Returns:
            HANTRO_TRUE        end of picture
            HANTRO_FALSE       noup

------------------------------------------------------------------------------*/

u32 h264bsdIsEndOfPicture(storage_t * storage) {

  /* Variables */

  u32 i, tmp;

  /* Code */

  ASSERT(storage != NULL);

  /* primary picture */
  if(!storage->slice_header[0].redundant_pic_cnt) {
    if(storage->slice->num_decoded_mbs == storage->pic_size_in_mbs)
      return (HANTRO_TRUE);
  } else {
    ASSERT(storage->mb != NULL);

    for(i = 0, tmp = 0; i < storage->pic_size_in_mbs; i++)
      tmp += storage->mb[i].decoded ? 1 : 0;

    if(tmp == storage->pic_size_in_mbs)
      return (HANTRO_TRUE);
  }

  return (HANTRO_FALSE);

}

/*------------------------------------------------------------------------------

    Function: h264bsdComputeSliceGroupMap

        Functional description:
            Compute slice group map. Just call h264bsdDecodeSliceGroupMap with
            appropriate parameters.

        Inputs:
            storage                pointer to storage structure
            slice_group_change_cycle

        Outputs:
            none

        Returns:
            none

------------------------------------------------------------------------------*/

void h264bsdComputeSliceGroupMap(storage_t * storage,
                                 u32 slice_group_change_cycle) {

  /* Variables */

  /* Code */

  h264bsdDecodeSliceGroupMap(storage->slice_group_map,
                             storage->active_pps, slice_group_change_cycle,
                             storage->active_sps->pic_width_in_mbs,
                             storage->active_sps->pic_height_in_mbs);

}

/*------------------------------------------------------------------------------

    Function: h264bsdCheckAccessUnitBoundary

        Functional description:
            Check if next NAL unit starts a new access unit. Following
            conditions specify start of a new access unit:

                -NAL unit types 6-11, 13-18 (e.g. SPS, PPS)

           following conditions checked only for slice NAL units, values
           compared to ones obtained from previous slice:

                -NAL unit type differs (slice / IDR slice)
                -frame_num differs
                -nal_ref_idc differs and one of the values is 0
                -POC information differs
                -both are IDR slices and idr_pic_id differs

        Inputs:
            strm        pointer to stream data structure
            nu_next     pointer to NAL unit structure
            storage     pointer to storage structure
            rlc         flag to indicate RLC or VLC mode

        Outputs:
            access_unit_boundary_flag  the result is stored here, HANTRO_TRUE for
                                    access unit boundary, HANTRO_FALSE otherwise

        Returns:
            HANTRO_OK           success
            HANTRO_NOK          failure, invalid stream data
            PARAM_SET_ERROR     invalid param set usage

------------------------------------------------------------------------------*/

u32 h264bsdCheckAccessUnitBoundary(strmData_t * strm,
                                   nalUnit_t * nu_next,
                                   storage_t * storage,
                                   u32 * access_unit_boundary_flag, u32 error_check_flag, u32 rlc) {

  /* Variables */

  u32 tmp, pps_id, frame_num, idr_pic_id, pic_order_cnt_lsb, slice_type;
  u32 field_pic_flag = 0, bottom_field_flag = 0;
  i32 delta_pic_order_cnt_bottom, delta_pic_order_cnt[2];
  strmData_t check_strm[1];
  u32 first_mb_in_slice = 0;
  u32 redundant_pic_cnt = 0;
  strmData_t tmp_strm_data[1];
  seqParamSet_t *sps;
  picParamSet_t *pps;
  u32 view = 0;
  aubCheck_t *aub = error_check_flag ? storage->tmp_aub : storage->aub;
  /* Code */

  ASSERT(strm);
  ASSERT(nu_next);
  ASSERT(storage);
  ASSERT(storage->sps);
  ASSERT(storage->pps);

  *check_strm = *strm;
  *tmp_strm_data = *strm;
  STREAMTRACE_I("%s","h264bsdCheckAccessUnitBoundary #\n");
  /* initialize default output to HANTRO_FALSE */
  *access_unit_boundary_flag = HANTRO_FALSE;

  /* TODO field_pic_flag, bottom_field_flag */

  if(((nu_next->nal_unit_type > 5) && (nu_next->nal_unit_type < 12)) ||
      ((nu_next->nal_unit_type > 12) && (nu_next->nal_unit_type <= 18))) {
    *access_unit_boundary_flag = HANTRO_TRUE;
    return (HANTRO_OK);
  } else if(nu_next->nal_unit_type != NAL_CODED_SLICE &&
            nu_next->nal_unit_type != NAL_CODED_SLICE_IDR &&
            nu_next->nal_unit_type != NAL_CODED_SLICE_EXT) {
    return (HANTRO_OK);
  }

  /* check if this is the very first call to this function */
  if(aub->first_call_flag) {
    *access_unit_boundary_flag = HANTRO_TRUE;
    aub->first_call_flag = HANTRO_FALSE;
  }

  /* get picture parameter set id */
  tmp = h264bsdGetPpsId(check_strm, &pps_id, &slice_type);
  if(tmp != HANTRO_OK)
    return (tmp);

  if (nu_next->nal_unit_type == NAL_CODED_SLICE_EXT)
    view = 1;

  /* store sps and pps in separate pointers just to make names shorter */
  pps = storage->pps[pps_id];
  if(pps == NULL || storage->sps[pps->seq_parameter_set_id] == NULL ||
      (storage->active_view_sps_id[view] != MAX_NUM_SEQ_PARAM_SETS &&
       pps->seq_parameter_set_id != storage->active_view_sps_id[view] &&
       !IS_I_SLICE(slice_type) &&
       (nu_next->nal_unit_type == NAL_CODED_SLICE ||
        (nu_next->nal_unit_type == NAL_CODED_SLICE_EXT && nu_next->mvc_ext.non_idr_flag))))
    return (PARAM_SET_ERROR);
  sps = storage->sps[pps->seq_parameter_set_id];

  /* another view does not start new access unit unless new view_id is
   * smaller than previous, but other views are handled like new access units
   * (param set activation etc) */
  if(aub->nu_prev->mvc_ext.view_id != nu_next->mvc_ext.view_id)
    *access_unit_boundary_flag = HANTRO_TRUE;

  if(aub->nu_prev->nal_ref_idc != nu_next->nal_ref_idc &&
      (aub->nu_prev->nal_ref_idc == 0 || nu_next->nal_ref_idc == 0)) {
    *access_unit_boundary_flag = HANTRO_TRUE;
    aub->new_picture = HANTRO_TRUE;
  } else
    aub->new_picture = HANTRO_FALSE;

  if((aub->nu_prev->nal_unit_type == NAL_CODED_SLICE_IDR &&
      nu_next->nal_unit_type != NAL_CODED_SLICE_IDR) ||
      (aub->nu_prev->nal_unit_type != NAL_CODED_SLICE_IDR &&
       nu_next->nal_unit_type == NAL_CODED_SLICE_IDR))
    *access_unit_boundary_flag = HANTRO_TRUE;

  tmp = h264bsdCheckFrameNum(check_strm, sps->max_frame_num, &frame_num);
  if(tmp != HANTRO_OK)
    return (HANTRO_NOK);

  if(aub->prev_frame_num != frame_num &&
      aub->prev_mod_frame_num != frame_num) {
    aub->prev_frame_num = frame_num;
    *access_unit_boundary_flag = HANTRO_TRUE;
  }
#ifdef H264_IGNORE_FRAME_GAP
  else if (nu_next->nal_unit_type == NAL_CODED_SLICE) {
    aub->prev_frame_num = frame_num + 1;
    *access_unit_boundary_flag = HANTRO_TRUE;
  }
#endif

  tmp = h264bsdCheckFieldPicFlag(check_strm, !sps->frame_mbs_only_flag, &field_pic_flag);

  if (field_pic_flag != aub->prev_field_pic_flag) {
    aub->prev_field_pic_flag = field_pic_flag;
    *access_unit_boundary_flag = HANTRO_TRUE;
  }

  tmp = h264bsdCheckBottomFieldFlag(check_strm, field_pic_flag, &bottom_field_flag);

  if(tmp != HANTRO_OK)
    return (HANTRO_NOK);

  STREAMTRACE_I("FIELD %d bottom %d\n",field_pic_flag, bottom_field_flag);

  if (bottom_field_flag != aub->prev_bottom_field_flag) {
    aub->prev_bottom_field_flag = bottom_field_flag;
    *access_unit_boundary_flag = HANTRO_TRUE;
  }

  if(nu_next->nal_unit_type == NAL_CODED_SLICE_IDR) {
    tmp = h264bsdCheckIdrPicId(check_strm, &idr_pic_id);
    if(tmp != HANTRO_OK)
      return (HANTRO_NOK);

    if(aub->nu_prev->nal_unit_type == NAL_CODED_SLICE_IDR &&
        aub->prev_idr_pic_id != idr_pic_id)
      *access_unit_boundary_flag = HANTRO_TRUE;

    /* FFWD workaround */
    if(!*access_unit_boundary_flag && !rlc) {
      /* if prev IDR pic ready and first MB is zero */
      tmp = h264bsdCheckFirstMbInSlice( tmp_strm_data,
                                        nu_next->nal_unit_type,
                                        &first_mb_in_slice );
      if( tmp != HANTRO_OK )
        return (HANTRO_NOK);
      if(storage->prev_idr_pic_ready && first_mb_in_slice == 0) {
        /* Just to make sure, check that next IDR is not marked as
         * redundant */
        tmp = h264bsdCheckRedundantPicCnt( tmp_strm_data, sps, pps,
                                           &redundant_pic_cnt );
        if( tmp != HANTRO_OK )
          return (HANTRO_NOK);
        if( redundant_pic_cnt == 0 ) {
          *access_unit_boundary_flag = HANTRO_TRUE;
        }
      }
    }

    aub->prev_idr_pic_id = idr_pic_id;
  }

  if(sps->pic_order_cnt_type == 0) {
    tmp = h264bsdCheckPicOrderCntLsb(check_strm, sps, nu_next->nal_unit_type,
                                     &pic_order_cnt_lsb);
    if(tmp != HANTRO_OK)
      return (HANTRO_NOK);

    if(aub->prev_pic_order_cnt_lsb != pic_order_cnt_lsb) {
      aub->prev_pic_order_cnt_lsb = pic_order_cnt_lsb;
      *access_unit_boundary_flag = HANTRO_TRUE;
    }

    if(pps->pic_order_present_flag) {
      tmp = h264bsdCheckDeltaPicOrderCntBottom(check_strm, sps,
            nu_next->nal_unit_type,
            &delta_pic_order_cnt_bottom);
      if(tmp != HANTRO_OK)
        return (tmp);

      if(aub->prev_delta_pic_order_cnt_bottom !=
          delta_pic_order_cnt_bottom) {
        aub->prev_delta_pic_order_cnt_bottom =
          delta_pic_order_cnt_bottom;
        *access_unit_boundary_flag = HANTRO_TRUE;
      }
    }
  } else if(sps->pic_order_cnt_type == 1 && !sps->delta_pic_order_always_zero_flag) {
    tmp = h264bsdCheckDeltaPicOrderCnt(check_strm, sps, nu_next->nal_unit_type,
                                       pps->pic_order_present_flag, field_pic_flag,
                                       delta_pic_order_cnt);
    if(tmp != HANTRO_OK)
      return (tmp);

    if(aub->prev_delta_pic_order_cnt[0] != delta_pic_order_cnt[0]) {
      aub->prev_delta_pic_order_cnt[0] = delta_pic_order_cnt[0];
      *access_unit_boundary_flag = HANTRO_TRUE;
    }

    if(pps->pic_order_present_flag)
      if(aub->prev_delta_pic_order_cnt[1] != delta_pic_order_cnt[1]) {
        aub->prev_delta_pic_order_cnt[1] = delta_pic_order_cnt[1];
        *access_unit_boundary_flag = HANTRO_TRUE;
      }
  }

  *aub->nu_prev = *nu_next;

  return (HANTRO_OK);

}

/*------------------------------------------------------------------------------

    Function: CheckPps

        Functional description:
            Check picture parameter set. Contents of the picture parameter
            set information that depends on the image dimensions is checked
            against the dimensions in the sps.

        Inputs:
            pps     pointer to picture paramter set
            sps     pointer to sequence parameter set

        Outputs:
            none

        Returns:
            HANTRO_OK      everything ok
            HANTRO_NOK     invalid data in picture parameter set

------------------------------------------------------------------------------*/
u32 CheckPps(picParamSet_t * pps, seqParamSet_t * sps) {

  u32 i;
  u32 pic_size;

  pic_size = sps->pic_width_in_mbs * sps->pic_height_in_mbs;

  /* check slice group params */
  if(pps->num_slice_groups > 1) {
    /* FMO only supported in Baseline profile */
    if (sps->frame_mbs_only_flag != 1 ||
        sps->chroma_format_idc != 1 ||
        sps->scaling_matrix_present_flag != 0 ||
        pps->entropy_coding_mode_flag != 0 ||
        (pps->weighted_pred_flag != 0 || pps->weighted_bi_pred_idc != 0) ||
        pps->transform8x8_flag != 0 ||
        pps->scaling_matrix_present_flag != 0)
      return(HANTRO_NOK);

    if(pps->slice_group_map_type == 0) {
      ASSERT(pps->run_length);
      for(i = 0; i < pps->num_slice_groups; i++) {
        if(pps->run_length[i] > pic_size)
          return (HANTRO_NOK);
      }
    } else if(pps->slice_group_map_type == 2) {
      ASSERT(pps->top_left);
      ASSERT(pps->bottom_right);
      for(i = 0; i < pps->num_slice_groups - 1; i++) {
        if(pps->top_left[i] > pps->bottom_right[i] ||
            pps->bottom_right[i] >= pic_size)
          return (HANTRO_NOK);

        if((pps->top_left[i] % sps->pic_width_in_mbs) >
            (pps->bottom_right[i] % sps->pic_width_in_mbs))
          return (HANTRO_NOK);
      }
    } else if(pps->slice_group_map_type > 2 && pps->slice_group_map_type < 6) {
      if(pps->slice_group_change_rate > pic_size)
        return (HANTRO_NOK);
    } else if (pps->slice_group_map_type == 6 &&
               pps->pic_size_in_map_units < pic_size)
      return(HANTRO_NOK);
  }

  return (HANTRO_OK);
}

/*------------------------------------------------------------------------------

    Function: h264bsdValidParamSets

        Functional description:
            Check if any valid SPS/PPS combination exists in the storage.
            Function tries each PPS in the buffer and checks if corresponding
            SPS exists and calls CheckPps to determine if the PPS conforms
            to image dimensions of the SPS.

        Inputs:
            storage    pointer to storage structure

        Outputs:
            HANTRO_OK   there is at least one valid combination
            HANTRO_NOK  no valid combinations found

------------------------------------------------------------------------------*/

u32 h264bsdValidParamSets(storage_t * storage) {

  /* Variables */

  u32 i;

  /* Code */

  ASSERT(storage);

  for(i = 0; i < MAX_NUM_PIC_PARAM_SETS; i++) {
    if(storage->pps[i] &&
        storage->sps[storage->pps[i]->seq_parameter_set_id] &&
        CheckPps(storage->pps[i],
                 storage->sps[storage->pps[i]->seq_parameter_set_id]) ==
        HANTRO_OK) {
      return (HANTRO_OK);
    }
  }

  return (HANTRO_NOK);

}

/*------------------------------------------------------------------------------
    Function name   : h264bsdAllocateSwResources
    Description     :
    Return type     : u32
    Argument        : const void *dwl
    Argument        : storage_t * storage
    Argument        : u32 is_high_supported
------------------------------------------------------------------------------*/
u32 h264bsdAllocateSwResources(
  const void *dwl,
  storage_t * storage,
  u32 is_high_supported,
  u32 is_high10_supported,
  u32 n_cores) {
  u32 tmp;
  u32 no_reorder;
  seqParamSet_t *p_sps = storage->active_sps;
  u32 max_dpb_size;
  u32 rfc_luma_size = 0, rfc_chroma_size = 0;
  u32 ref_buffer_align = MAX(16, ALIGN(storage->align));
  struct dpbInitParams dpb_params;
  dpbStorage_t * dpb = storage->dpb;

  storage->pic_size_in_mbs = p_sps->pic_width_in_mbs * p_sps->pic_height_in_mbs;
  storage->curr_image->width = p_sps->pic_width_in_mbs;
  storage->curr_image->height = p_sps->pic_height_in_mbs;
  dpb->storage = storage;

  /* dpb output reordering disabled if
   * 1) application set no_reordering flag
   * 2) POC type equal to 2
   * 3) num_reorder_frames in vui equal to 0 */
  if(storage->no_reordering ||
      p_sps->pic_order_cnt_type == 2 ||
      (p_sps->vui_parameters_present_flag &&
       p_sps->vui_parameters->bitstream_restriction_flag &&
       !p_sps->vui_parameters->num_reorder_frames))
    no_reorder = HANTRO_TRUE;
  else
    no_reorder = HANTRO_FALSE;

  if (storage->view == 0)
    max_dpb_size = p_sps->max_dpb_size;
  else {
    /* stereo view dpb size at least equal to base view size (to make sure
     * that base view pictures get output in correct display order) */
    max_dpb_size = MAX(p_sps->max_dpb_size, storage->active_view_sps[0]->max_dpb_size);
  }
  /* restrict max dpb size of mvc (stereo high) streams, make sure that
   * base address 15 is available/restricted for inter view reference use */
  if (storage->mvc_stream)
    max_dpb_size = MIN(max_dpb_size, 8);

  dpb_params.pic_size_in_mbs = storage->pic_size_in_mbs;
  dpb_params.pic_width_in_mbs = p_sps->pic_width_in_mbs;
  dpb_params.pic_height_in_mbs = p_sps->pic_height_in_mbs;
  dpb_params.dpb_size = max_dpb_size;
  dpb_params.max_ref_frames = p_sps->num_ref_frames;
  if (storage->skip_non_intra && !storage->mvc_stream) {
    dpb_params.max_ref_frames = 1;
    dpb_params.dpb_size = 1;
  }
  dpb_params.max_frame_num = p_sps->max_frame_num;
  dpb_params.no_reordering = no_reorder;
  dpb_params.display_smoothing = storage->use_smoothing;
  dpb_params.mono_chrome = p_sps->mono_chrome;
  dpb_params.chroma_format_idc = p_sps->chroma_format_idc;
  dpb_params.is_high_supported = is_high_supported;
  dpb_params.enable2nd_chroma = storage->enable2nd_chroma && !p_sps->mono_chrome;
  dpb_params.n_cores = n_cores;
  dpb_params.mvc_view = storage->view;
  dpb_params.pp_width = storage->pp_width;
  dpb_params.is_high10_supported = is_high10_supported;
  dpb_params.pixel_width = (p_sps->bit_depth_luma == 8 &&
                            p_sps->bit_depth_chroma == 8) ? 8 : 10;
  if (!storage->pp_tiled_e) {
    dpb_params.pp_height = storage->pp_height;
    dpb_params.pp_stride = NEXT_MULTIPLE(dpb_params.pp_width, ALIGN(storage->align));
  } else {
    dpb_params.pp_height = NEXT_MULTIPLE(storage->pp_height, 16) / 4;
    dpb_params.pp_stride = NEXT_MULTIPLE(4 * dpb_params.pp_width, ALIGN(storage->align));
  }

  H264GetRefFrmSize(storage, &rfc_luma_size, &rfc_chroma_size);
  dpb_params.tbl_sizey = NEXT_MULTIPLE(rfc_luma_size, ref_buffer_align);
  dpb_params.tbl_sizec = NEXT_MULTIPLE(rfc_chroma_size, ref_buffer_align);

  /* Reallocate PP buffers first when pp is enabled. */
  if (storage->pp_enabled) {
    /* If more or larger pp buffers required, release and reallocate them. */
    if (storage->ext_buffer_added && storage->realloc_ext_buf) {
      storage->release_buffer = 1;
      return DEC_WAITING_FOR_BUFFER;
    }
  } else {
    u32 max_ref_frames, new_dpb_size, new_tot_buffers;
    max_ref_frames = (dpb_params.max_ref_frames != 0) ?
                      dpb_params.max_ref_frames : 1;
    if(dpb_params.no_reordering)
      new_dpb_size = max_ref_frames;
    else
      new_dpb_size = dpb_params.dpb_size;

    /* max DPB size is (16 + 1) buffers */
    new_tot_buffers = new_dpb_size + 1;

    /* figure out extra buffers for smoothing, pp, multicore, etc... */
    if (dpb_params.n_cores == 1) {
      /* single core configuration */
      if (dpb_params.display_smoothing)
        new_tot_buffers += dpb_params.no_reordering ? 1 : new_dpb_size + 1;
    } else {
      /* multi core configuration */

      if (dpb_params.display_smoothing && !dpb_params.no_reordering) {
        /* at least double buffers for smooth output */
        if (new_tot_buffers > dpb_params.n_cores) {
          new_tot_buffers *= 2;
        } else {
          new_tot_buffers += dpb_params.n_cores;
        }
      } else {
        /* one extra buffer for each core */
        /* do not allocate twice for multiview */
        if(!dpb_params.mvc_view)
          new_tot_buffers += dpb_params.n_cores;
      }
    }
    if (storage->ext_buffer_added && storage->realloc_ext_buf) {
      storage->release_buffer = 1;
      return DEC_WAITING_FOR_BUFFER;
    }
  }
  /* note that calling ResetDpb here results in losing all
   * pictures currently in DPB -> nothing will be output from
   * the buffer even if noOutputOfPriorPicsFlag is HANTRO_FALSE */
  tmp = h264bsdResetDpb(
          dwl,
          dpb, &dpb_params);

  dpb->pic_width = h264bsdPicWidth(storage) << 4;
  dpb->pic_height = h264bsdPicHeight(storage) << 4;
  dpb->bit_depth_luma = p_sps->bit_depth_luma;
  dpb->bit_depth_chroma = p_sps->bit_depth_chroma;
  dpb->mono_chrome = p_sps->mono_chrome;
  dpb->chroma_format_idc = p_sps->chroma_format_idc;

  if(tmp != HANTRO_OK)
    return (tmp);

  return HANTRO_OK;
}

u32 h264bsdMVCAllocateSwResources(const void *dwl, storage_t * storage,
                                  u32 is_high_supported,
                                  u32 is_high10_supported,
                                  u32 n_cores) {
  u32 tmp;
  u32 no_reorder;
  u32 max_dpb_size;
  u32 ref_buffer_align = MAX(16, ALIGN(storage->align));
  struct dpbInitParams dpb_params;
  seqParamSet_t *sps = storage->active_sps;

  for(u32 i = 0; i < 2; i ++) {
    const seqParamSet_t *p_sps = storage->sps[i] == 0 ? storage->sps[0]: storage->sps[i];
    storage->pic_size_in_mbs = p_sps->pic_width_in_mbs * p_sps->pic_height_in_mbs;
    storage->curr_image->width = p_sps->pic_width_in_mbs;
    storage->curr_image->height = p_sps->pic_height_in_mbs;
    storage->dpbs[i]->storage = storage;

    /* dpb output reordering disabled if
     * 1) application set no_reordering flag
     * 2) POC type equal to 2
     * 3) num_reorder_frames in vui equal to 0 */
    if(storage->no_reordering ||
        p_sps->pic_order_cnt_type == 2 ||
        (p_sps->vui_parameters_present_flag &&
         p_sps->vui_parameters->bitstream_restriction_flag &&
         !p_sps->vui_parameters->num_reorder_frames))
      no_reorder = HANTRO_TRUE;
    else
      no_reorder = HANTRO_FALSE;

    max_dpb_size = p_sps->max_dpb_size;

    /* restrict max dpb size of mvc (stereo high) streams, make sure that
     * base address 15 is available/restricted for inter view reference use */
    max_dpb_size = MIN(max_dpb_size, 8);

    dpb_params.pic_size_in_mbs = storage->pic_size_in_mbs;
    dpb_params.pic_width_in_mbs = p_sps->pic_width_in_mbs;
    dpb_params.pic_height_in_mbs = p_sps->pic_height_in_mbs;
    dpb_params.dpb_size = max_dpb_size;
    dpb_params.max_ref_frames = p_sps->num_ref_frames;
    dpb_params.max_frame_num = p_sps->max_frame_num;
    dpb_params.no_reordering = no_reorder;
    dpb_params.display_smoothing = storage->use_smoothing;
    dpb_params.mono_chrome = p_sps->mono_chrome;
    dpb_params.chroma_format_idc = p_sps->chroma_format_idc;
    dpb_params.is_high_supported = is_high_supported;
    dpb_params.enable2nd_chroma = storage->enable2nd_chroma && !p_sps->mono_chrome;
    dpb_params.n_cores = n_cores;
    dpb_params.mvc_view = 1;
    dpb_params.is_high10_supported = is_high10_supported;
    dpb_params.pixel_width = (sps->bit_depth_luma == 8 &&
                              sps->bit_depth_chroma == 8) ? 8 : 10;
    if (storage->use_video_compressor) {
      u32 pic_width_in_cbsy, pic_height_in_cbsy;
      u32 pic_width_in_cbsc, pic_height_in_cbsc;
      pic_width_in_cbsy = ((p_sps->pic_width_in_mbs * 16 + 8 - 1)/8);
      pic_width_in_cbsy = NEXT_MULTIPLE(pic_width_in_cbsy, 16);
      pic_width_in_cbsc = ((p_sps->pic_width_in_mbs * 16 + 16 - 1)/16);
      pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
      pic_height_in_cbsy = (p_sps->pic_height_in_mbs * 16 + 8 - 1)/8;
      pic_height_in_cbsc = (p_sps->pic_height_in_mbs * 16/2 + 4 - 1)/4;

      dpb_params.tbl_sizey = NEXT_MULTIPLE(pic_width_in_cbsy * pic_height_in_cbsy, ref_buffer_align);
      dpb_params.tbl_sizec = NEXT_MULTIPLE(pic_width_in_cbsc * pic_height_in_cbsc, ref_buffer_align);
    } else
      dpb_params.tbl_sizey = dpb_params.tbl_sizec = 0;

    /* note that calling ResetDpb here results in losing all
     * pictures currently in DPB -> nothing will be output from
     * the buffer even if noOutputOfPriorPicsFlag is HANTRO_FALSE */
    tmp = h264bsdResetDpb(dwl, storage->dpbs[i], &dpb_params);

    storage->dpbs[i]->pic_width = h264bsdPicWidth(storage) << 4;
    storage->dpbs[i]->pic_height = h264bsdPicHeight(storage) << 4;
    storage->dpbs[i]->bit_depth_luma = p_sps->bit_depth_luma;
    storage->dpbs[i]->bit_depth_chroma = p_sps->bit_depth_chroma;
    storage->dpbs[i]->mono_chrome = p_sps->mono_chrome;
    storage->dpbs[i]->chroma_format_idc = p_sps->chroma_format_idc;
  }

  if(tmp != HANTRO_OK)
    return (tmp);

  return HANTRO_OK;
}

u32 h264bsdStoreSEIInfoForCurrentPic(storage_t * storage) {
  dpbStorage_t * dpb = storage->dpb;
  u32 index;

  if (!dpb->current_out)
    return (HANTRO_NOK);

  //dpb->current_out->picStruct[index] = storage->sei_param.pic_timing_info.picStruct;

  if(IS_IDR_NAL_UNIT(storage->prev_nal_unit))
    storage->compute_time_info.is_first_au = 1;
  if(h264bsdComputeTimes(storage) == HANTRO_NOK)
    return HANTRO_NOK;

  dpb->cpb_removal_time = storage->compute_time_info.cpb_removal_time;
  if (dpb->current_out->is_field_pic) {
    index = (dpb->current_out->is_bottom_field ? 1 : 0);
    dpb->current_out->dpb_output_time[index] = storage->compute_time_info.dpb_output_time;
  } else
    dpb->current_out->dpb_output_time[0] = storage->compute_time_info.dpb_output_time;
  return HANTRO_OK;
}

void h264bsdClearStorage(storage_t * storage) {

  /* Variables */

  /* Code */
  u32 i = 0;

  (void)i;

  ASSERT(storage);
  h264bsdResetStorage(storage);

  if(storage->pp_enabled)
    InputQueueReset(storage->pp_buffer_queue);

  storage->skip_redundant_slices = HANTRO_FALSE;
  storage->pic_started = HANTRO_FALSE;
  storage->valid_slice_in_access_unit = HANTRO_FALSE;
  storage->num_err_mbs = 0;
  storage->dpb = storage->dpbs[0];
  storage->slice_header = storage->slice_headers[0];
  storage->bumping_flag = 0;
  storage->prev_buf_not_finished = HANTRO_FALSE;
  storage->prev_buf_pointer = NULL;
  storage->prev_bytes_consumed = 0;
  storage->aso_detected = 0;
  storage->second_field = 0;
  storage->checked_aub = 0;
  storage->picture_broken = 0;
  storage->pending_flush = 0;
  storage->base_opposite_field_pic = 0;
  storage->view = 0;
  storage->out_view = 0;
  storage->next_view = 0;
  storage->non_inter_view_ref = 0;
  storage->last_base_num_out = 0;
  storage->pending_out_pic = NULL;
  storage->realloc_int_buf = 0;
  storage->realloc_ext_buf = 0;
  storage->release_buffer = 0;
  storage->ext_buffer_added = 0;

  DWLmemset(&storage->poc, 0, 2 * sizeof(pocStorage_t));
  DWLmemset(&storage->aub, 0, sizeof(aubCheck_t));
  DWLmemset(&storage->curr_image, 0, sizeof(image_t));
  DWLmemset(&storage->prev_nal_unit, 0, sizeof(nalUnit_t));
  DWLmemset(&storage->slice_headers, 0 ,2 * MAX_NUM_VIEWS * sizeof(sliceHeader_t));
  DWLmemset(&storage->strm, 0, sizeof(strmData_t));
  DWLmemset(&storage->mb_layer, 0, sizeof(macroblockLayer_t));


#ifdef CLEAR_HDRINFO_IN_SEEK
  storage->old_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_sps_id = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_pps_id = MAX_NUM_PIC_PARAM_SETS;
  storage->active_view_sps_id[0] = storage->active_view_sps_id[1] = MAX_NUM_SEQ_PARAM_SETS;
  storage->active_pps = NULL;
  storage->active_sps = NULL;
  storage->active_view_sps[0] = storage->active_view_sps[1] = NULL;
  for(i = 0; i < MAX_NUM_SEQ_PARAM_SETS; i++) {
    if(storage->sps[i]) {
      FREE(storage->sps[i]->offset_for_ref_frame);
      FREE(storage->sps[i]->vui_parameters);
      FREE(storage->sps[i]);
    }
  }

  for(i = 0; i < MAX_NUM_PIC_PARAM_SETS; i++) {
    if(storage->pps[i]) {
      FREE(storage->pps[i]->run_length);
      FREE(storage->pps[i]->top_left);
      FREE(storage->pps[i]->bottom_right);
      FREE(storage->pps[i]->slice_group_id);
      FREE(storage->pps[i]);
    }
  }
#endif

  /* clear sei_param */
#ifdef SUPPORT_SEI
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (storage->sei_param[i] && storage->sei_param[i]->sei_status != SEI_UNUSED) {
      storage->sei_param[i]->sei_status = SEI_UNUSED;
      storage->sei_param[i]->decode_id = -1;
      if (storage->sei_param[i]->t35_param.payload_byte.buffer) {
        storage->sei_param[i]->t35_param.payload_byte.available_size = 0;
        storage->sei_param[i]->t35_param.counter = 0;
      }
      if (storage->sei_param[i]->userdataunreg_param.payload_byte.buffer) {
        storage->sei_param[i]->userdataunreg_param.payload_byte.available_size = 0;
        storage->sei_param[i]->userdataunreg_param.userdataunreg_counter = 0;
      }
    }
  }
#endif
}

void H264GetRefFrmSize(storage_t *storage, u32 *rfc_luma_size, u32 *rfc_chroma_size) {
  seqParamSet_t *sps = storage->active_sps;

  if (storage->use_video_compressor) {
    u32 pic_width_in_cbsy, pic_height_in_cbsy;
    u32 pic_width_in_cbsc, pic_height_in_cbsc;
    pic_width_in_cbsy = ((sps->pic_width_in_mbs * 16 + 8 - 1)/8);
    pic_width_in_cbsy = NEXT_MULTIPLE(pic_width_in_cbsy, 16);
    pic_width_in_cbsc = ((sps->pic_width_in_mbs * 16 + 16 - 1)/16);
    pic_width_in_cbsc = NEXT_MULTIPLE(pic_width_in_cbsc, 16);
    pic_height_in_cbsy = (sps->pic_height_in_mbs * 16 + 8 - 1)/8;
    pic_height_in_cbsc = (sps->pic_height_in_mbs * 16/2 + 4 - 1)/4;
    if(sps->chroma_format_idc==2)
      pic_height_in_cbsc = (sps->pic_height_in_mbs * 16 + 4 - 1)/4;

    *rfc_luma_size = NEXT_MULTIPLE(pic_width_in_cbsy * pic_height_in_cbsy, 16);
    *rfc_chroma_size = NEXT_MULTIPLE(pic_width_in_cbsc * pic_height_in_cbsc, 16);
  } else {
    *rfc_luma_size = *rfc_chroma_size = 0;
  }
}

static double Ceil(double a) {
  u32 tmp;
  tmp = (u32)a;
  if ((double)(tmp) < a)
    return ((double)(tmp + 1));
  else
    return ((double)(tmp));
}

u32 h264bsdComputeTimes(storage_t *storage) {
  seqParamSet_t *p_seq_param_set;
  computeTimeInfo_t *time_info;
  struct H264SEIParameters *p_sei_parameters;
  u32 cbr_flag = 0;
  u32 bit_rate_value = 0;
  u32 bit_rate_scale = 0;
  u32 bit_rate;

  p_seq_param_set = storage->active_sps;
  time_info = &storage->compute_time_info;
  p_sei_parameters = storage->sei_param_curr;

  // compute tc
  if (!p_seq_param_set || !p_seq_param_set->vui_parameters || !p_sei_parameters)
    return (HANTRO_NOK);

  if (!p_sei_parameters->pictiming_present_flag ||
      !p_sei_parameters->bufperiod_present_flag) {
    // p_sei_parameters->pictiming_present_flag = 0;
    return (HANTRO_NOK);
  }

  if (!p_sei_parameters->pic_param.cpb_removal_delay &&
      !p_sei_parameters->pic_param.dpb_output_delay) {
    // p_sei_parameters->pic_timing_info.exist_flag = 0;
    return (HANTRO_NOK);
  }

  if(time_info->is_first_au) {
    if(p_seq_param_set->vui_parameters->update_hrdparameter_flag)
      time_info->hrd_init_flag = 1;
    else
      time_info->hrd_init_flag = 0;
    p_seq_param_set->vui_parameters->update_hrdparameter_flag = 0;
  }
  if(p_seq_param_set->vui_parameters->timing_info_present_flag)
    time_info->clock_tick =
      (double)p_seq_param_set->vui_parameters->num_units_in_tick /
      p_seq_param_set->vui_parameters->time_scale;
  else
    time_info->clock_tick = 0;

  if(p_seq_param_set->vui_parameters->nal_hrd_parameters_present_flag) {
    cbr_flag = p_seq_param_set->vui_parameters->nal_hrd_parameters.cbr_flag[0];
    bit_rate_scale = p_seq_param_set->vui_parameters->nal_hrd_parameters.bit_rate_scale;
    bit_rate_value = p_seq_param_set->vui_parameters->nal_hrd_parameters.bit_rate_value[0];
  }

  else {
    cbr_flag = p_seq_param_set->vui_parameters->vcl_hrd_parameters.cbr_flag[0];
    bit_rate_scale = p_seq_param_set->vui_parameters->vcl_hrd_parameters.bit_rate_scale;
    bit_rate_value = p_seq_param_set->vui_parameters->vcl_hrd_parameters.bit_rate_value[0];
  }

  //compute trn

  if (time_info->is_first_au)
  {
    if (time_info->hrd_init_flag)
    {
      time_info->nominal_removal_time =
          p_sei_parameters->buf_param.initial_cpb_removal_delay[0] / 90000.0;
    }
    else
    {
      time_info->nominal_removal_time = time_info->prev_nominal_removal_time +
        time_info->clock_tick * p_sei_parameters->pic_param.cpb_removal_delay;
    }
    time_info->prev_nominal_removal_time = time_info->nominal_removal_time;
    time_info->nominal_removal_time_first = time_info->nominal_removal_time;
  }
  else
  {
    time_info->nominal_removal_time = time_info->nominal_removal_time_first +
      time_info->clock_tick * p_sei_parameters->pic_param.cpb_removal_delay;
  }

  if (time_info->is_first_au)
  {
    time_info->initial_arrival_time_earliest = time_info->nominal_removal_time -
      (p_sei_parameters->buf_param.initial_cpb_removal_delay[0] / 90000.0);
  }
  else
    time_info->initial_arrival_time_earliest = time_info->nominal_removal_time -
      ((p_sei_parameters->buf_param.initial_cpb_removal_delay[0] +
      p_sei_parameters->buf_param.initial_cpb_removal_delay_offset[0]) / 90000.0);

  //compute tai
  if (time_info->is_first_au)
    time_info->initial_arrival_time = 0;
  else if (cbr_flag == 1)
    time_info->initial_arrival_time = time_info->final_arrival_time;
  else
    time_info->initial_arrival_time =
        (time_info->final_arrival_time >= time_info->initial_arrival_time_earliest) ? time_info->final_arrival_time : time_info->initial_arrival_time_earliest;

  //compute taf
  bit_rate = bit_rate_value * (2 << (6 + bit_rate_scale));
  time_info->final_arrival_time =
      time_info->initial_arrival_time + ((double)time_info->access_unit_size) / bit_rate;

  //compute tr
  if(!p_seq_param_set->vui_parameters->low_delay_hrd_flag || (time_info->nominal_removal_time >= time_info->final_arrival_time))
    time_info->cpb_removal_time = time_info->nominal_removal_time;
  else
    time_info->cpb_removal_time =
      time_info->nominal_removal_time + time_info->clock_tick *
      Ceil((time_info->final_arrival_time - time_info->nominal_removal_time) /
            time_info->clock_tick);

  //compute to_dpb
  time_info->dpb_output_time = time_info->cpb_removal_time +
    time_info->clock_tick * p_sei_parameters->pic_param.dpb_output_delay;
  time_info->is_first_au = 0;
  return (HANTRO_OK);
}
