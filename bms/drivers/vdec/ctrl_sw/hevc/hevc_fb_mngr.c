/*------------------------------------------------------------------------------
--       Copyright (c) 2015-2017, VeriSilicon Inc. All rights reserved        --
--         Copyright (c) 2011-2014, Google Inc. All rights reserved.          --
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

#include "hevcdecapi.h"
#include "hevc_fb_mngr.h"
#include "hevc_dpb.h"
#include "hevc_storage.h"

#include <assert.h>
// #include <errno.h>
// #include <stdio.h>
#include "dec_log.h"
#define FB_UNALLOCATED 0x00U
#define FB_FREE 0x01U
#define FB_ALLOCATED 0x02U
#define FB_OUTPUT 0x04U
#define FB_TEMP_OUTPUT 0x08U

#define FB_HW_ONGOING 0x30U

u32 InitList(struct FrameBufferList *fb_list) {
  (void)DWLmemset(fb_list, 0, sizeof(*fb_list));

  sem_init(&fb_list->out_count_sem, 0, 0);
  pthread_mutex_init(&fb_list->out_count_mutex, NULL);
  /* CV to be signaled when output  queue is empty */
  pthread_cond_init(&fb_list->out_empty_cv, NULL);

  pthread_mutex_init(&fb_list->ref_count_mutex, NULL);
  /* CV to be signaled when a buffer is not referenced anymore */
  pthread_cond_init(&fb_list->ref_count_cv, NULL);

  /* this CV is used to signal the HW has finished processing a picture
   * that is needed for output ( FB_OUTPUT | FB_HW_ONGOING )
   */
  pthread_cond_init(&fb_list->hw_rdy_cv, NULL);

  fb_list->b_initialized = 1;

  return 0;
}

u32 ReInitList(struct FrameBufferList *fb_list) {
  int i;
  // Reset fb_list
  // Output related variables should be kept unchanged.
  //fb_list->out_wr_id = fb_list->out_rd_id = 0;
  //fb_list->free_buffers = fb_list->num_out = 0;
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (!(fb_list->fb_stat[i].b_used & FB_OUTPUT)) {
      fb_list->fb_stat[i].b_used = FB_UNALLOCATED;
    }
    fb_list->fb_stat[i].n_ref_count = 0;
  }

  return 0;
}

void ReleaseList(struct FrameBufferList *fb_list) {
  int i;
  if (!fb_list->b_initialized) return;

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    /* we shall clean our stuff graciously */
    assert(fb_list->fb_stat[i].n_ref_count == 0);
  }

  assert(fb_list->free_buffers == 0);

  fb_list->b_initialized = 0;

  pthread_mutex_destroy(&fb_list->ref_count_mutex);
  pthread_cond_destroy(&fb_list->ref_count_cv);

  pthread_mutex_destroy(&fb_list->out_count_mutex);
  pthread_cond_destroy(&fb_list->out_empty_cv);
  pthread_cond_destroy(&fb_list->hw_rdy_cv);

  sem_destroy(&fb_list->out_count_sem);
}

u32 AllocateIdUsed(struct FrameBufferList *fb_list, const void *data) {
  u32 id = 0;

  /* find first unallocated ID */
  do {
    if (fb_list->fb_stat[id].b_used == FB_UNALLOCATED) break;
    id++;
  } while (id < MAX_PIC_BUFFERS);

  if (id >= MAX_PIC_BUFFERS) return FB_NOT_VALID_ID;

  fb_list->fb_stat[id].b_used = FB_ALLOCATED;
  fb_list->fb_stat[id].n_ref_count = 0;
  fb_list->fb_stat[id].data = data;

  return id;
}

u32 AllocateIdFree(struct FrameBufferList *fb_list, const void *data) {
  u32 id = 0;

  /* find first unallocated ID */
  do {
    if (fb_list->fb_stat[id].b_used == FB_UNALLOCATED) break;
    id++;
  } while (id < MAX_PIC_BUFFERS);

  if (id >= MAX_PIC_BUFFERS) return FB_NOT_VALID_ID;

  fb_list->free_buffers++;

  fb_list->fb_stat[id].b_used = FB_FREE;
  fb_list->fb_stat[id].n_ref_count = 0;
  fb_list->fb_stat[id].data = data;
  return id;
}

void ReleaseId(struct FrameBufferList *fb_list, u32 id) {
  assert(id < MAX_PIC_BUFFERS);

  /* it is "bad" to release referenced or unallocated buffers */
  assert(fb_list->fb_stat[id].n_ref_count == 0);
  if (id >= MAX_PIC_BUFFERS) return;

  if(fb_list->fb_stat[id].b_used == FB_UNALLOCATED) return;

  if (fb_list->fb_stat[id].b_used == FB_FREE) {
    assert(fb_list->free_buffers > 0);
    fb_list->free_buffers--;
  }

  fb_list->fb_stat[id].b_used = FB_UNALLOCATED;
  fb_list->fb_stat[id].n_ref_count = 0;
  fb_list->fb_stat[id].data = NULL;
}

u32 IsFreeById(struct FrameBufferList *fb_list, u32 id) {
  assert(id < MAX_PIC_BUFFERS);
  if(fb_list->fb_stat[id].b_used == FB_FREE)
    return HANTRO_OK;
  else
    return HANTRO_NOK;
}

void *GetDataById(struct FrameBufferList *fb_list, u32 id) {
  assert(id < MAX_PIC_BUFFERS);
  assert(fb_list->fb_stat[id].b_used != FB_UNALLOCATED);

  if (id < MAX_PIC_BUFFERS)
  	return (void *)fb_list->fb_stat[id].data;
  else
  	return NULL;
}

void ResetDataById(struct FrameBufferList *fb_list, const void *data, u32 id) {
  assert(id < MAX_PIC_BUFFERS);
  assert(fb_list->fb_stat[id].b_used != FB_UNALLOCATED);

  if (id < MAX_PIC_BUFFERS)
  	fb_list->fb_stat[id].data = data;
}

u32 GetIdByData(struct FrameBufferList *fb_list, const void *data) {
  u32 id = 0;
  assert(data);

  do {
    if (fb_list->fb_stat[id].data == data) break;
    id++;
  } while (id < MAX_PIC_BUFFERS);

  return id < MAX_PIC_BUFFERS ? id : FB_NOT_VALID_ID;
}
void IncrementRefUsage(struct FrameBufferList *fb_list, u32 id) {
  fb_list->fb_stat[id].n_ref_count++;
  DPB_TRACE("IncrementRefUsage# id = %d b_used = %d rc = %d\n", id, fb_list->fb_stat[id].b_used, fb_list->fb_stat[id].n_ref_count);
}

void DecrementRefUsage(struct FrameBufferList *fb_list, u32 id) {
  struct FrameBufferStatus *bs = fb_list->fb_stat + id;

  if (bs->n_ref_count > 0) {
    bs->n_ref_count--;

    if (bs->n_ref_count == 0) {
      if (bs->b_used == FB_FREE) {
        fb_list->free_buffers++;
        DPB_TRACE("DecrementRefUsage# FREE id = %d\n", id);
      }
      /* signal that this buffer is not referenced anymore */
      pthread_cond_signal(&fb_list->ref_count_cv);
    } else if (bs->b_used == FB_FREE) {
      DPB_TRACE("DecrementRefUsage# Free buffer id = %d still referenced\n", id);
    }
  }

  DPB_TRACE("DecrementRefUsage# id = %d b_used = %d rc = %d\n", id, fb_list->fb_stat[id].b_used, fb_list->fb_stat[id].n_ref_count);
}

void MarkHWOutput(struct FrameBufferList *fb_list, u32 id, u32 type) {

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  assert(fb_list->fb_stat[id].b_used & FB_ALLOCATED);
  assert(fb_list->fb_stat[id].b_used ^ type);

  fb_list->fb_stat[id].n_ref_count++;
  fb_list->fb_stat[id].b_used |= type;

  DPB_TRACE("DecrementRefUsage# id = %d b_used = %d rc = %d\n", id, fb_list->fb_stat[id].b_used, fb_list->fb_stat[id].n_ref_count);

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

void ClearHWOutput(struct FrameBufferList *fb_list, u32 id, u32 type, u32 pp_enabled) {
  struct FrameBufferStatus *bs = fb_list->fb_stat + id;

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  assert(bs->b_used & (FB_HW_ONGOING | FB_ALLOCATED));

  if (bs->n_ref_count > 0)
    bs->n_ref_count--;
  bs->b_used &= ~type;

  if (bs->n_ref_count == 0) {
    if (bs->b_used == FB_FREE) {
      fb_list->free_buffers++;
      DPB_TRACE("ClearHWOutput# FREE id = %d\n", id);
    }
    /* signal that this buffer is not referenced anymore */
    pthread_cond_signal(&fb_list->ref_count_cv);
  }

  //if ((bs->b_used & FB_HW_ONGOING) == 0 && (bs->b_used & FB_OUTPUT))
  if(((bs->b_used & FB_HW_ONGOING) == 0) &&
     (pp_enabled || (!pp_enabled && (bs->b_used & FB_OUTPUT))))
    /* signal that this buffer is done by HW */
    pthread_cond_signal(&fb_list->hw_rdy_cv);

  DPB_TRACE("ClearHWOutput# id = %d b_used = %d rc = %d\n", id, fb_list->fb_stat[id].b_used, fb_list->fb_stat[id].n_ref_count);

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

/* Mark a buffer as a potential (temporal) output. Output has to be marked
 * permanent by FinalizeOutputAll or reverted to non-output by
 * RemoveTempOutputAll.
 */
void MarkTempOutput(struct FrameBufferList *fb_list, u32 id) {
  DPB_TRACE("MarkTempOutput# id = %d\n", id);
  pthread_mutex_lock(&fb_list->ref_count_mutex);

  assert(fb_list->fb_stat[id].b_used & FB_ALLOCATED);

  fb_list->fb_stat[id].n_ref_count++;
  fb_list->fb_stat[id].b_used |= FB_TEMP_OUTPUT;

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

/* Mark all temp output as valid output */
void FinalizeOutputAll(struct FrameBufferList *fb_list) {
  i32 i;
  pthread_mutex_lock(&fb_list->ref_count_mutex);

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (fb_list->fb_stat[i].b_used & FB_TEMP_OUTPUT) {
      /* mark permanent output */
      fb_list->fb_stat[i].b_used |= FB_OUTPUT;
      /* clean TEMP flag from output */
      fb_list->fb_stat[i].b_used &= ~FB_TEMP_OUTPUT;

      DPB_TRACE("MarkTempOutput# id = %d\n", i);
    }
  }

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

void ClearOutput(struct FrameBufferList *fb_list, u32 id) {
  struct FrameBufferStatus *bs = fb_list->fb_stat + id;

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  assert(bs->b_used & (FB_OUTPUT | FB_TEMP_OUTPUT));

#ifndef EXT_BUF_SAFE_RELEASE
  if (bs->n_ref_count == 0) {
    pthread_mutex_unlock(&fb_list->ref_count_mutex);
    return;
  }
#endif

  if (bs->n_ref_count > 0)
    bs->n_ref_count--;

  bs->b_used &= ~(FB_OUTPUT | FB_TEMP_OUTPUT);

  if (bs->n_ref_count == 0) {
    if (bs->b_used == FB_FREE) {
      fb_list->free_buffers++;
      DPB_TRACE("FREE id = %d\n", id);
    }
    /* signal that this buffer is not referenced anymore */
    pthread_cond_signal(&fb_list->ref_count_cv);
  } else if (bs->b_used == FB_FREE) {
    DPB_TRACE("Free buffer id = %d still referenced\n", id);
  }

  DPB_TRACE("id = %d b_used = %d rc = %d\n", id, fb_list->fb_stat[id].b_used, fb_list->fb_stat[id].n_ref_count);
  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

u32 PopFreeBuffer(struct FrameBufferList *fb_list) {
  u32 i = 0;
#ifndef ASIC_TRACE_SUPPORT
  fb_list->free_buffer_rd_id = 0;
#endif
  struct FrameBufferStatus *bs = fb_list->fb_stat + fb_list->free_buffer_rd_id;
  do {
    if (bs->b_used == FB_FREE && bs->n_ref_count == 0 && bs->data) {
      bs->b_used = FB_ALLOCATED;
      break;
    }
    i++;
    fb_list->free_buffer_rd_id++;
    if (fb_list->free_buffer_rd_id == MAX_PIC_BUFFERS)
      fb_list->free_buffer_rd_id = 0;
    bs = fb_list->fb_stat + fb_list->free_buffer_rd_id;
  } while (i < MAX_PIC_BUFFERS);

  assert(i < MAX_PIC_BUFFERS);

  fb_list->free_buffers--;

  DPB_TRACE("id = %d\n", fb_list->free_buffer_rd_id);

  return fb_list->free_buffer_rd_id;
}

void PushFreeBuffer(struct FrameBufferList *fb_list, u32 id) {
  assert(id < MAX_PIC_BUFFERS);
  assert(fb_list->fb_stat[id].b_used & FB_ALLOCATED);

  pthread_mutex_lock(&fb_list->ref_count_mutex);

  DPB_TRACE("id = %d\n", id);

  fb_list->fb_stat[id].b_used &= ~FB_ALLOCATED;
  fb_list->fb_stat[id].b_used |= FB_FREE;

  if (fb_list->fb_stat[id].n_ref_count == 0) {
    fb_list->free_buffers++;
    DPB_TRACE("FREE id = %d\n", id);

    /* signal that this buffer is not referenced anymore */
    pthread_cond_signal(&fb_list->ref_count_cv);
  } else
    DPB_TRACE("Free buffer id = %d still referenced\n", id);

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

u32 GetFreePicBuffer(struct FrameBufferList *fb_list, u32 old_id) {
  u32 id;

  pthread_mutex_lock(&fb_list->ref_count_mutex);

#ifndef GET_FREE_BUFFER_NON_BLOCK
  /* Wait until a free buffer is available or "old_id"
   * buffer is not referenced anymore */
  while (fb_list->free_buffers == 0 &&
         fb_list->fb_stat[old_id].n_ref_count != 0 &&
         !fb_list->abort) {
    DPB_TRACE("%s\n", "NO FREE PIC BUFFER");
    pthread_cond_wait(&fb_list->ref_count_cv, &fb_list->ref_count_mutex);
  }
#else
  if (fb_list->free_buffers == 0 &&
      fb_list->fb_stat[old_id].n_ref_count != 0) {
    pthread_mutex_unlock(&fb_list->ref_count_mutex);
    return FB_NOT_VALID_ID;
  }
#endif

  if(fb_list->abort)
    id = FB_NOT_VALID_ID;
#ifndef ASIC_TRACE_SUPPORT
  /* To avoid multicore top simultion buffer confliction, we always find a new
     free buffer. */
  else if (fb_list->fb_stat[old_id].n_ref_count == 0) {
    /*  our old buffer is not referenced anymore => reuse it */
    id = old_id;
  }
#endif
  else {
    id = PopFreeBuffer(fb_list);
  }

  DPB_TRACE("id = %d\n", id);

  pthread_mutex_unlock(&fb_list->ref_count_mutex);

  return id;
}

u32 GetFreeBufferCount(struct FrameBufferList *fb_list) {
  u32 free_buffers;
  pthread_mutex_lock(&fb_list->ref_count_mutex);
  free_buffers = fb_list->free_buffers;
  pthread_mutex_unlock(&fb_list->ref_count_mutex);

  return free_buffers;
}

void SetFreePicBuffer(struct FrameBufferList *fb_list, u32 id) {
  PushFreeBuffer(fb_list, id);
}

void IncrementDPBRefCount(struct DpbStorage *dpb) {
  u32 i;
  //DPB_TRACE("%s", "\n");
  pthread_mutex_lock(&dpb->fb_list->ref_count_mutex);
  for (i = 0; i < dpb->dpb_size; i++) {
    IncrementRefUsage(dpb->fb_list, dpb->buffer[i].mem_idx);
    dpb->ref_id[i] = dpb->buffer[i].mem_idx;
  }
  pthread_mutex_unlock(&dpb->fb_list->ref_count_mutex);
}

void DecrementDPBRefCount(struct DpbStorage *dpb) {
  u32 i;
  //DPB_TRACE("%s", "\n");
  pthread_mutex_lock(&dpb->fb_list->ref_count_mutex);
  for (i = 0; i < dpb->dpb_size; i++) {
    DecrementRefUsage(dpb->fb_list, dpb->ref_id[i]);
  }
  pthread_mutex_unlock(&dpb->fb_list->ref_count_mutex);
}

void DecrementDPBRefCountExt(struct DpbStorage *dpb, u32 *ref_id) {
  u32 i;
  //DPB_TRACE("%s", "\n");
  pthread_mutex_lock(&dpb->fb_list->ref_count_mutex);
  for (i = 0; i < dpb->dpb_size; i++) {
    DecrementRefUsage(dpb->fb_list, ref_id[i]);
  }
  pthread_mutex_unlock(&dpb->fb_list->ref_count_mutex);
}


u32 IsBufferReferenced(struct FrameBufferList *fb_list, u32 id) {
  int n_ref_count;
  DPB_TRACE("%d ? ref_count = %d\n", id, fb_list->fb_stat[id].n_ref_count);
  pthread_mutex_lock(&fb_list->ref_count_mutex);
  n_ref_count = fb_list->fb_stat[id].n_ref_count;
  pthread_mutex_unlock(&fb_list->ref_count_mutex);

  return n_ref_count != 0 ? 1 : 0;
}

u32 IsBufferOutput(struct FrameBufferList *fb_list, u32 id) {
  u32 b_output;
  pthread_mutex_lock(&fb_list->ref_count_mutex);
  b_output = fb_list->fb_stat[id].b_used & FB_OUTPUT ? 1 : 0;
  pthread_mutex_unlock(&fb_list->ref_count_mutex);

  return b_output;
}

void MarkOutputPicInfo(struct FrameBufferList *fb_list, u32 id, u32 errors, u32 cycles,
                       enum DecErrorInfo error_info) {
  i32 i;
  u32 rd_id;

  pthread_mutex_lock(&fb_list->out_count_mutex);

  rd_id = fb_list->out_rd_id;

  for (i = 0; i < fb_list->num_out; i++) {
    if (fb_list->out_fifo[rd_id].mem_idx == id) {
      DPB_TRACE("id = %d\n", id);
      fb_list->out_fifo[rd_id].pic.error_ratio = errors;
      fb_list->out_fifo[rd_id].pic.cycles_per_mb = cycles;
      fb_list->out_fifo[rd_id].pic.error_info = error_info;
      break;
    }

    rd_id = (rd_id + 1) % MAX_PIC_BUFFERS;
  }

  pthread_mutex_unlock(&fb_list->out_count_mutex);
}

void PushOutputPic(struct FrameBufferList *fb_list,
                   const struct HevcDecPicture *pic, u32 id) {
  if (pic != NULL) {
    pthread_mutex_lock(&fb_list->out_count_mutex);
    if(!IsBufferOutput(fb_list, id)) {
      pthread_mutex_unlock(&fb_list->out_count_mutex);
      return;
    }

    while (fb_list->num_out == MAX_PIC_BUFFERS) {
      /* make sure we do not overflow the output */
      /* pthread_cond_signal(&fb_list->out_empty_cv); */
      pthread_mutex_unlock(&fb_list->out_count_mutex);
      sched_yield();
      pthread_mutex_lock(&fb_list->out_count_mutex);
    }

    /* push to tail */
    if (fb_list->out_wr_id >= MAX_PIC_BUFFERS) fb_list->out_wr_id = 0;
    fb_list->out_fifo[fb_list->out_wr_id].pic = *pic;
    fb_list->out_fifo[fb_list->out_wr_id].mem_idx = id;

    fb_list->num_out++;
    fb_list->out_wr_id++;

    assert(fb_list->num_out <= MAX_PIC_BUFFERS);

    pthread_mutex_unlock(&fb_list->out_count_mutex);
  }

  if (pic != NULL)
    DPB_TRACE("num_out = %d\n", fb_list->num_out);
  else {
    if (id == -2) {
      fb_list->flush_all = 1;
      DPB_TRACE("%s\n", "FLUSHED");
    } else
      DPB_TRACE("%s\n", "EOS");
  }

  /* pic == NULL signals the end of decoding in which case we just need to
   * wake-up the output thread (potentially sleeping) */
  sem_post(&fb_list->out_count_sem);
}

u32 PeekOutputPic(struct FrameBufferList *fb_list, struct HevcDecPicture *pic) {
  u32 mem_idx;
  struct HevcDecPicture *out;

#ifndef GET_OUTPUT_BUFFER_NON_BLOCK
  sem_wait(&fb_list->out_count_sem);
#endif

  if (fb_list->abort) {
    return ABORT_MARKER;
  }

  if (fb_list->flush_all) {
    fb_list->flush_all = 0;
    return FLUSH_MARKER;
  }

  pthread_mutex_lock(&fb_list->out_count_mutex);
  if (!fb_list->num_out) {
    pthread_mutex_unlock(&fb_list->out_count_mutex);
    //DPB_TRACE("Output empty, EOS\n");
    return 0;
  }

  pthread_mutex_unlock(&fb_list->out_count_mutex);

  out = &fb_list->out_fifo[fb_list->out_rd_id].pic;
  mem_idx = fb_list->out_fifo[fb_list->out_rd_id].mem_idx;
  pthread_mutex_lock(&fb_list->ref_count_mutex);

  while ((fb_list->fb_stat[mem_idx].b_used & FB_HW_ONGOING) != 0)
    pthread_cond_wait(&fb_list->hw_rdy_cv, &fb_list->ref_count_mutex);

  pthread_mutex_unlock(&fb_list->ref_count_mutex);

  /* pop from head */
  (void)DWLmemcpy(pic, out, sizeof(struct HevcDecPicture));

  DPB_TRACE("id = %d\n", mem_idx);

  pthread_mutex_lock(&fb_list->out_count_mutex);

  fb_list->num_out--;
  if (fb_list->num_out == 0) {
    pthread_cond_signal(&fb_list->out_empty_cv);
  }

  /* go to next output */
  fb_list->out_rd_id++;
  if (fb_list->out_rd_id >= MAX_PIC_BUFFERS) fb_list->out_rd_id = 0;

  pthread_mutex_unlock(&fb_list->out_count_mutex);

  return 1;
}

u32 PopOutputPic(struct FrameBufferList *fb_list, u32 id) {
  if (!IsBufferOutput(fb_list, id)) {
    return 1;
  }

  ClearOutput(fb_list, id);

  return 0;
}

void RemoveTempOutputAll(struct FrameBufferList *fb_list, struct DpbStorage *dpb) {
  i32 i;

  i32 j;

  if (!dpb || !dpb->storage)
    return;

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (dpb->fb_list->fb_stat[i].b_used & FB_TEMP_OUTPUT) {
      for (j = 0; j < MAX_DPB_SIZE + 1; j++) {
        if (dpb->buffer[j].mem_idx == i) {
          /* For raster/dscale buffer, return to input buffer queue. */
          if (dpb->storage->pp_enabled &&
              dpb->buffer[j].pp_data != NULL) {
            InputQueueReturnBuffer(dpb->storage->pp_buffer_queue,
                              DWL_GET_DEVMEM_ADDR(*(dpb->buffer[j].pp_data)));
          }
          if (dpb->buffer[j].dmv_data != NULL)
            HevcReturnDMVBuffer(dpb, dpb->buffer[j].dmv_data->bus_address);
          if (dpb->buffer[j].sei_param)
            dpb->buffer[j].sei_param->sei_status = SEI_UNUSED;
          break;
        }
      }
    }
  }

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (fb_list->fb_stat[i].b_used & FB_TEMP_OUTPUT) {
      ClearOutput(fb_list, i);
    }
  }
}

void RemoveOutputAll(struct FrameBufferList *fb_list, struct DpbStorage *dpb) {
  i32 i, j;
  u32 rd_id, id;

  if (!dpb || !dpb->storage)
    return;

#ifdef USE_OMXIL_BUFFER
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (dpb->fb_list->fb_stat[i].b_used & FB_OUTPUT) {
      for (j = 0; j < MAX_DPB_SIZE + 1; j++) {
        if (dpb->buffer[j].mem_idx == i) {
          /* For raster/dscale buffer, return to input buffer queue. */
          if (dpb->storage->pp_enabled &&
              dpb->buffer[j].pp_data != NULL) {
            InputQueueReturnBuffer(dpb->storage->pp_buffer_queue,
                              DWL_GET_DEVMEM_ADDR(*(dpb->buffer[j].pp_data)));
          }
          if (dpb->buffer[j].dmv_data != NULL)
            HevcReturnDMVBuffer(dpb, dpb->buffer[j].dmv_data->bus_address);
          if (dpb->buffer[j].sei_param)
            dpb->buffer[j].sei_param->sei_status = SEI_UNUSED;
          break;
        }
      }
    }
  }

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if (fb_list->fb_stat[i].b_used & FB_OUTPUT) {
      ClearOutput(fb_list, i);
    }
  }
  (void)rd_id;
  (void)id;
#else
  /* For the buffers that have been output to fb_list->out_fifo, yet not be output via NextPicture.
   *  - If reference buffer: remove these frames from out_fifo.
   *  - raster/down scale buffer: return to raster/downscale buffer queue. */

  rd_id = fb_list->out_rd_id;

  for (i = 0; i < fb_list->num_out; i++) {
    if (!dpb->storage->pp_enabled) {
      id = fb_list->out_fifo[rd_id].mem_idx;
      if (fb_list->fb_stat[id].b_used & FB_OUTPUT) {
        ClearOutput(fb_list, id);
      }
    } else {
      HevcReturnDMVBuffer(dpb, fb_list->out_fifo[rd_id].pic.output_dmv_bus_address);
      if (dpb->storage->pp_enabled) {
        for (i = 0; i < 4; i++)
#ifndef MEM_ONLY_DEV_CHECK
          InputQueueReturnBuffer(dpb->storage->pp_buffer_queue,
                            fb_list->out_fifo[rd_id].pic.pictures[i].output_picture);
#else
          InputQueueReturnBuffer(dpb->storage->pp_buffer_queue,
                            fb_list->out_fifo[rd_id].pic.pictures[i].output_picture_bus_address);
#endif
        if (fb_list->out_fifo[rd_id].pic.sei_param)
          fb_list->out_fifo[rd_id].pic.sei_param->sei_status = SEI_UNUSED;
      }
    }

    rd_id = (rd_id + 1) % MAX_PIC_BUFFERS;
  }
  (void)j;
#endif
}

void RemoveTempOutputId(struct FrameBufferList *fb_list, u32 id) {
  i32 i;

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    if ((fb_list->fb_stat[i].b_used & FB_TEMP_OUTPUT) && (i == id)) {
      ClearOutput(fb_list, i);
    }
  }
}

u32 IsOutputEmpty(struct FrameBufferList *fb_list) {
  u32 num_out;
  pthread_mutex_lock(&fb_list->out_count_mutex);
  num_out = fb_list->num_out;
  pthread_mutex_unlock(&fb_list->out_count_mutex);

  return num_out == 0 ? 1 : 0;
}

void WaitOutputEmpty(struct FrameBufferList *fb_list) {
  if (!fb_list->b_initialized) return;

  pthread_mutex_lock(&fb_list->out_count_mutex);
  while (fb_list->num_out != 0) {
    pthread_cond_wait(&fb_list->out_empty_cv, &fb_list->out_count_mutex);
  }
  pthread_mutex_unlock(&fb_list->out_count_mutex);
}


void MarkListNotInUse(struct FrameBufferList *fb_list) {
  int i;
  pthread_mutex_lock(&fb_list->ref_count_mutex);
  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    fb_list->fb_stat[i].n_ref_count = 0;
  }
  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}


void WaitListNotInUse(struct FrameBufferList *fb_list) {
  int i;

  //DPB_TRACE("%s", "\n");

  if (!fb_list->b_initialized) return;

  for (i = 0; i < MAX_PIC_BUFFERS; i++) {
    pthread_mutex_lock(&fb_list->ref_count_mutex);
    /* Wait until all buffers are not referenced */
    while (fb_list->fb_stat[i].n_ref_count != 0 && !fb_list->abort) {
      pthread_cond_wait(&fb_list->ref_count_cv, &fb_list->ref_count_mutex);
    }
    pthread_mutex_unlock(&fb_list->ref_count_mutex);
  }
}

void SetAbortStatusInList(struct FrameBufferList *fb_list) {
  if(fb_list == NULL || !fb_list->b_initialized)
    return;

  pthread_mutex_lock(&fb_list->ref_count_mutex);
  fb_list->abort = 1;
  pthread_cond_signal(&fb_list->ref_count_cv);
  pthread_mutex_unlock(&fb_list->ref_count_mutex);
  sem_post(&fb_list->out_count_sem);
}

void ClearAbortStatusInList(struct FrameBufferList *fb_list) {
  if(fb_list == NULL || !fb_list->b_initialized)
    return;

  pthread_mutex_lock(&fb_list->ref_count_mutex);
  fb_list->abort = 0;
  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

void ResetOutFifoInList(struct FrameBufferList *fb_list) {
  (void)DWLmemset(fb_list->out_fifo, 0, MAX_PIC_BUFFERS * sizeof(struct OutElement));
  fb_list->out_wr_id = 0;
  fb_list->out_rd_id = 0;
  fb_list->num_out = 0;
}


void MarkIdAllocated(struct FrameBufferList *fb_list, u32 id) {
  DPB_TRACE("MarkIdAllocated# id = %d\n", id);
  pthread_mutex_lock(&fb_list->ref_count_mutex);

  if (fb_list->fb_stat[id].b_used & FB_FREE) {
    fb_list->fb_stat[id].b_used &= ~FB_FREE;
    if (fb_list->fb_stat[id].n_ref_count == 0)
      fb_list->free_buffers--;
  }
  fb_list->fb_stat[id].b_used |= FB_ALLOCATED;

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}

void MarkIdFree(struct FrameBufferList *fb_list, u32 id)
{
  DPB_TRACE("MarkIdFree# id = %d\n", id);
  pthread_mutex_lock(&fb_list->ref_count_mutex);

  if (fb_list->fb_stat[id].b_used & FB_ALLOCATED) {
    fb_list->fb_stat[id].b_used &= ~FB_ALLOCATED;
    if (fb_list->fb_stat[id].n_ref_count == 0)
      fb_list->free_buffers++;
  }
  fb_list->fb_stat[id].b_used |= FB_FREE;

  pthread_mutex_unlock(&fb_list->ref_count_mutex);
}
