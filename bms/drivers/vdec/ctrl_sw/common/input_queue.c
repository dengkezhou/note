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

#ifdef _ASSERT_USED
#ifndef ASSERT
#include <assert.h>
#define ASSERT(expr) assert(expr)
#endif
#else
#define ASSERT(expr)
#endif

#include "dwlthread.h"
#ifdef _USE_VSI_STRING_
#include "vsi_string.h"
#else
#include <string.h>
#endif

#include "input_queue.h"
#include "fifo.h"
#include "memalloc.h"
//#define BUFFER_QUEUE_PRINT_STATUS
#ifdef BUFFER_QUEUE_PRINT_STATUS
#define PRINT_COUNTS(x) PrintCounts(x)
#else
#define PRINT_COUNTS(x)
#endif /* BUFFER_QUEUE_PRINT_STATUS */


/* Data structure to hold this picture buffer queue instance data. */
struct IQueue {
  pthread_mutex_t cs; /* Critical section to protect data. */
  i32 max_buffers;    /* Number of max buffers accepted. */
  i32 n_buffers;      /* Number of buffers contained in total. */
  struct DWLLinearMem buffers[MAX_PIC_BUFFERS];
  u32 buffer_used[MAX_PIC_BUFFERS];
  u32 ref_cnt[MAX_PIC_BUFFERS];
  u32 ref_flag[MAX_PIC_BUFFERS];/* flag that buffer get by threaad.(not increase cnt yet) */
  pthread_mutex_t cnt_release_mutex;
  pthread_cond_t cnt_release_cv;
  pthread_mutex_t buf_release_mutex;
  pthread_cond_t buf_release_cv;
  u32 abort;
};

InputQueue InputQueueInit(i32 n_buffers) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("(n_buffers=%i)", n_buffers);
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(n_buffers >= 0);
  struct IQueue* q = (struct IQueue*)DWLcalloc(1, sizeof(struct IQueue));
  if (q == NULL) {
    return NULL;
  }

  q->max_buffers = MAX_PIC_BUFFERS;
  q->n_buffers = 0;
  DWLmemset(q->buffers, 0, sizeof(q->buffers));
  DWLmemset(q->buffer_used, 0, sizeof(q->buffer_used));
  DWLmemset(q->ref_cnt, 0, sizeof(q->ref_cnt));
  DWLmemset(q->ref_flag, 0, sizeof(q->ref_flag));
  pthread_mutex_init(&q->cnt_release_mutex, NULL);
  pthread_cond_init(&q->cnt_release_cv, NULL);
  pthread_mutex_init(&q->buf_release_mutex, NULL);
  pthread_cond_init(&q->buf_release_cv, NULL);
  if (pthread_mutex_init(&q->cs, NULL)) {
    pthread_mutex_destroy(&q->cnt_release_mutex);
    pthread_cond_destroy(&q->cnt_release_cv);
    pthread_mutex_destroy(&q->buf_release_mutex);
    pthread_cond_destroy(&q->buf_release_cv);
    free(q);
    return NULL;
  }

  (void)n_buffers;
  return q;
}

void DecreaseInputQueueCnt(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  i32 i;
  struct DWLLinearMem *buffer = NULL;

  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      buffer = &q->buffers[i];
      break;
    }
  }
  if (buffer == NULL || i == q->n_buffers) {
    return;
  }
  if (!q->ref_cnt[i])
    return;

  pthread_mutex_lock(&q->cnt_release_mutex);
  //ASSERT(q->ref_cnt[i] > 0);
  q->ref_cnt[i]--;

  if ((!q->ref_cnt[i]) && !q->ref_flag[i]) {
    pthread_cond_signal(&q->cnt_release_cv);
  }
  pthread_mutex_unlock(&q->cnt_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}

void IncreaseInputQueueCnt(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  i32 i;
  struct DWLLinearMem *buffer = NULL;

  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      buffer = &q->buffers[i];
      break;
    }
  }
  if (buffer == NULL) {
    return;
  }
  pthread_mutex_lock(&q->cnt_release_mutex);
  //ASSERT(q->ref_flag[i]);
  q->ref_cnt[i]++;
  pthread_mutex_unlock(&q->cnt_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}


void InputQueueReset(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  if (q->n_buffers) {/* Destory mutex before releasing. */
    pthread_mutex_destroy(&q->cs);
    pthread_mutex_destroy(&q->buf_release_mutex);
    pthread_cond_destroy(&q->buf_release_cv);
    pthread_mutex_destroy(&q->cnt_release_mutex);
    pthread_cond_destroy(&q->cnt_release_cv);
  }

#ifdef USE_OMXIL_BUFFER
  q->max_buffers = MAX_PIC_BUFFERS;
  q->n_buffers = 0;
  DWLmemset(q->buffers, 0, sizeof(q->buffers));
  DWLmemset(q->buffer_used, 0, sizeof(q->buffer_used));
  DWLmemset(q->ref_cnt, 0, sizeof(q->ref_cnt));
  DWLmemset(q->ref_flag, 0, sizeof(q->ref_flag));
#else
  DWLmemset(q->ref_cnt, 0, sizeof(q->ref_cnt));
  DWLmemset(q->ref_flag, 0, sizeof(q->ref_flag));
#endif
  pthread_mutex_init(&q->cs, NULL);
  pthread_mutex_init(&q->buf_release_mutex, NULL);
  pthread_cond_init(&q->buf_release_cv, NULL);
  pthread_mutex_init(&q->cnt_release_mutex, NULL);
  pthread_cond_init(&q->cnt_release_cv, NULL);
}

void InputQueueRelease(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
#ifdef EXT_BUF_SAFE_RELEASE
  i32 i;
  for (i = 0; i < q->n_buffers; i++) {
    if (q->ref_cnt[i] && !q->buffer_used[i]) {
      q->ref_cnt[i] = 0;
      q->ref_flag[i] = 0;
    }
  }
#endif
  pthread_mutex_destroy(&q->buf_release_mutex);
  pthread_cond_destroy(&q->buf_release_cv);
  pthread_mutex_destroy(&q->cnt_release_mutex);
  pthread_cond_destroy(&q->cnt_release_cv);
  pthread_mutex_destroy(&q->cs);
  free(q);
}

struct DWLLinearMem *InputQueueGetBuffer(InputQueue queue, u32 wait) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  struct DWLLinearMem *buffer;
  i32 i;
  struct IQueue* q = (struct IQueue*)queue;

  pthread_mutex_lock(&q->cnt_release_mutex);
  for (i = 0; i < q->n_buffers; i++) {
    if ((!q->ref_cnt[i]) && (!q->ref_flag[i])) {
      q->ref_flag[i] = 1;
      break;
    }
  }
  if (i == q->n_buffers) {
    if (!wait) {
      pthread_mutex_unlock(&q->cnt_release_mutex);
      return NULL;
    } else {
      /* wait for a buffer free */
      while(i == q->n_buffers) {
        for (i = 0; i < q->n_buffers; i++) {
           if ((!q->ref_cnt[i]) && (!q->ref_flag[i])) {
            q->ref_flag[i] = 1;
            break;
          }
        }
        pthread_cond_wait(&q->cnt_release_cv, &q->cnt_release_mutex);
      }
    }
  }
  pthread_mutex_unlock(&q->cnt_release_mutex);
  buffer = &q->buffers[i];

#ifdef GET_FREE_BUFFER_NON_BLOCK
  if (q->buffer_used[i] && !q->abort) {
    pthread_mutex_lock(&q->cnt_release_mutex);
    q->ref_flag[i] = 0;
    pthread_mutex_unlock(&q->cnt_release_mutex);
    return NULL;
  }
#endif
  IncreaseInputQueueCnt(queue, DWL_GET_DEVMEM_ADDR(*buffer));

  pthread_mutex_lock(&q->buf_release_mutex);
  while(q->buffer_used[i] && !q->abort)
    pthread_cond_wait(&q->buf_release_cv, &q->buf_release_mutex);
  pthread_mutex_unlock(&q->buf_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("# %i\n", i);
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  return buffer;
}

void InputQueueAddBuffer(InputQueue queue, struct DWLLinearMem *buffer) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  pthread_mutex_lock(&q->cs);

  q->buffers[q->n_buffers] = *buffer;
  /* Add one picture buffer among empty picture buffers. */
  q->n_buffers++;
  pthread_mutex_unlock(&q->cs);

#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}

void InputQueueUpdateBuffer(InputQueue queue, struct DWLLinearMem *buffer, u32 index) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  pthread_mutex_lock(&q->cs);

  ASSERT(index < q->n_buffers);
  q->buffers[index] = *buffer;

  pthread_mutex_unlock(&q->cs);

#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}


u32 InputQueueFindBufferId(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  u32 i, index = 0xFFFFFFFF;
  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      index = i;
      break;
    }
  }
  return (index);
}
#if 0
void InputQueueWaitPending(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;

  while (FifoCount(q->fifo_in) != (u32)q->n_buffers) sched_yield();

#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}
#endif

struct DWLLinearMem *InputQueueReturnBuffer(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  u32 i;
  struct DWLLinearMem *buffer = NULL;
  struct IQueue* q = (struct IQueue*)queue;

  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      buffer = &q->buffers[i];
      break;
    }
  }
  if (buffer == NULL) {
    return NULL;
  }

  pthread_mutex_lock(&q->buf_release_mutex);
  q->buffer_used[i] = 0;
  pthread_cond_signal(&q->buf_release_cv);
  pthread_mutex_unlock(&q->buf_release_mutex);

  pthread_mutex_lock(&q->cnt_release_mutex);
  q->ref_flag[i] = 0;
  pthread_mutex_unlock(&q->cnt_release_mutex);
  DecreaseInputQueueCnt(queue, addr);


#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */

  return buffer;
}

void InputQueueSetAbort(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  struct IQueue* q = (struct IQueue*)queue;
  pthread_mutex_lock(&q->buf_release_mutex);
  q->abort = 1;
  pthread_cond_signal(&q->buf_release_cv);
  pthread_mutex_unlock(&q->buf_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}

void InputQueueClearAbort(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  struct IQueue* q = (struct IQueue*)queue;
  pthread_mutex_lock(&q->buf_release_mutex);
  q->abort = 0;
  pthread_mutex_unlock(&q->buf_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}

void InputQueueReturnAllBuffer(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  struct IQueue* q = (struct IQueue*)queue;
  i32 i;
//  struct DWLLinearMem *buffer = NULL;

  for (i = 0; i < q->n_buffers; i++) {
    pthread_mutex_lock(&q->cnt_release_mutex);
    q->ref_cnt[i] = 0;
    q->ref_flag[i] = 0;
    pthread_cond_signal(&q->cnt_release_cv);
    pthread_mutex_unlock(&q->cnt_release_mutex);

    /* Add one picture buffer among empty picture buffers. */
    pthread_mutex_lock(&q->buf_release_mutex);
    q->buffer_used[i] = 0;
    pthread_cond_signal(&q->buf_release_cv);
    pthread_mutex_unlock(&q->buf_release_mutex);
  }
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}

u32 InputQueueWaitNotUsed(InputQueue queue) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  i32 i;
  struct IQueue* q = (struct IQueue*)queue;
  for(i = 0; i < q->n_buffers; i++) {
    pthread_mutex_lock(&q->buf_release_mutex);
#if 1
    while (q->buffer_used[i] && !q->abort)
      pthread_cond_wait(&q->buf_release_cv, &q->buf_release_mutex);
#else
    if (q->buffer_used[i]) {
      pthread_mutex_unlock(&q->buf_release_mutex);
      return 1;
    }
#endif
    pthread_mutex_unlock(&q->buf_release_mutex);
  }
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif
  return 0;
}

void InputQueueWaitBufNotUsed(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  i32 i;
  struct DWLLinearMem *buffer = NULL;
  struct IQueue* q = (struct IQueue*)queue;
  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      buffer = &q->buffers[i];
      break;
    }
  }
  if (buffer == NULL) {
    return;
  }
  pthread_mutex_lock(&q->buf_release_mutex);
  while (q->buffer_used[i] && !q->abort)
    pthread_cond_wait(&q->buf_release_cv, &q->buf_release_mutex);
  pthread_mutex_unlock(&q->buf_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}
void InputQueueSetBufAsUsed(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  i32 i;
  struct DWLLinearMem *buffer = NULL;
  struct IQueue* q = (struct IQueue*)queue;
  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      buffer = &q->buffers[i];
      break;
    }
  }
  if (buffer == NULL) {
    return;
  }
  pthread_mutex_lock(&q->buf_release_mutex);
  q->buffer_used[i] = 1;
  pthread_mutex_unlock(&q->buf_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
}

u32 InputQueueCheckBufUsed(InputQueue queue, DWLMemAddr addr) {
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("()");
  printf("\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  ASSERT(queue);
  i32 i;
  struct DWLLinearMem *buffer = NULL;
  struct IQueue* q = (struct IQueue*)queue;
  for (i = 0; i < q->n_buffers; i++) {
    if (DWL_DEVMEM_COMPARE(q->buffers[i], addr)) {
      buffer = &q->buffers[i];
      break;
    }
  }
  if (buffer == NULL) {
    return 0;
  }
  pthread_mutex_lock(&q->buf_release_mutex);
  if (q->ref_cnt[i]) {
    pthread_mutex_unlock(&q->buf_release_mutex);
    return 1;
  }
  pthread_mutex_unlock(&q->buf_release_mutex);
#ifdef BUFFER_QUEUE_PRINT_STATUS
  printf(__FUNCTION__);
  printf("#\n");
#endif /* BUFFER_QUEUE_PRINT_STATUS */
  return 0;
}
