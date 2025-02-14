
#include <csi_config.h>
#include <drv_usart.h>
#include <drv_timer.h>
#include <stdio.h>
#include <div64.h>

usart_handle_t console_handle = 0;

// fake functions to make compile pass
int clock_timer_start(void) { return 0; }

int clock_timer_init(void) { return 0; }

void mm_heap_initialize(void) {}

// timer functions

static uint32_t APB_FREQ;
static uint32_t TIMER_LOADCOUNT;

static timer_handle_t timer_handle;
static unsigned int Timer_LoopCount; /* Count unit is 10 seconds */
static uint8_t timer_count_rise =
    0; /*1: timer cont increasing, 0: timer cont diminishing*/
static unsigned int Timer_LastCV = 0;

static void timer_event_cb_fun(int32_t idx, timer_event_e event) {
  printf("enter cb for mode free_runing \n");
  if (TIMER_EVENT_TIMEOUT == event) {
    Timer_LoopCount++;
  }
  return;
}

void udelay(unsigned long us) { return; }

// in ms

unsigned long long get_ticks(void) {
  unsigned int cv;

  int ret = csi_timer_get_current_value(timer_handle, &cv);

  if (ret != 0) {
    return 0;
  }

  if ((cv > Timer_LastCV) ^ timer_count_rise) {
    Timer_LoopCount++;
    printf("reloaded %d\n", Timer_LoopCount);
  }

  Timer_LastCV = cv;

  if (timer_count_rise) {
    return (unsigned long long)(Timer_LoopCount) * (TIMER_LOADCOUNT + 1) + cv;
  }

  return (unsigned long long)(Timer_LoopCount + 1) * (TIMER_LOADCOUNT + 1) -
         cv - 1;
}

unsigned long get_timer(unsigned long base) {
  return lldiv(get_ticks(), APB_FREQ / 1000);
}

// console
int console_puts(const char *str) {
  while (*str)
    csi_usart_putchar(console_handle, *str++);

  return 0;
}

int console_getc(void) {
  uint8_t ch;
  csi_usart_getchar(console_handle, &ch);
  return ch;
}

int console_putc(const char c) {
  csi_usart_putchar(console_handle, c);
  return c;
}

int console_tstc(void) { return 0; }

#define NULL ((void *)0)
void init_core(void) {
  uint32_t timer_loadtimer;
  timer_handle = csi_timer_initialize(0, timer_event_cb_fun);
  if (timer_handle == NULL) {
    printf("timer init failed\n");
    return;
  }

  APB_FREQ        = drv_get_timer_freq(0);
  timer_loadtimer = 10 * 1000000; /*10Mus=10s */
  TIMER_LOADCOUNT = timer_loadtimer * (APB_FREQ / 1000000);

  int ret = csi_timer_config(timer_handle, TIMER_MODE_RELOAD);

  if (ret != 0) {
    return;
  }

  ret = csi_timer_set_timeout(timer_handle, timer_loadtimer);
  if (ret != 0) {
    return;
  }

  unsigned int cv1, cv2;
  csi_timer_get_current_value(timer_handle, &cv1);
  csi_timer_get_current_value(timer_handle, &cv2);

  if (cv2 > cv1) {
    timer_count_rise = 1;
  }

  Timer_LoopCount = 0;
  ret             = csi_timer_start(timer_handle);

  if (ret != 0) {
    return;
  }
}
