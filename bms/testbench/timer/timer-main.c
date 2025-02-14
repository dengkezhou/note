#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <timer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t g_begintime;
uint32_t g_endtime;
uint32_t g_endtimematch1;
uint32_t g_endtimematch2;
uint32_t g_endtimematch3;
uint32_t g_match1time;
uint32_t g_match2time;
uint32_t g_match3time;
uint32_t g_matchnum;
uint32_t g_intevaltime;
uint32_t g_stopflag;

#define CONFIG_TIMER_NUM 3

timer_priv_t timer[CONFIG_TIMER_NUM];
timer_match_t timer_match;

void timer_event_cb_fun(timer_handle_t handle) {
  //DEBUG_LOG_TTC("Cin timer_event_cb_fun\n");
  timer_priv_t *timer_priv = handle;

  switch (timer_priv->enum_interrupt) {
  case TIMER_OVERFLOW_INTERRUPT:
    itcs_timer_stop(timer_priv);
    g_stopflag = 1;
    if (timer_priv->risedownflag == 1) {
      printf("Test overflow Timing, Incrementing count Pass\n");
    } else {
      printf("Test overflow Timing, Decrementing count Pass\n");
    }
    break;
  case TIMER_INTERVAL_INTERRUPT:
    if (g_endtime - g_begintime){
			if(timer_priv->bytes){
				if(timer_priv->timeridx == 2){
					itcs_timer_stop(timer_priv);
					DEBUG_LOG_TTC("timer_priv->timeridx = %d, timer period = %d\n", timer_priv->timeridx, g_endtime - g_begintime);
					printf("Test Interval Timing, Incrementing count Pass\n");
					g_stopflag = 1;
				}
			}else{
				itcs_timer_stop(timer_priv);
				DEBUG_LOG_TTC("g_endtime = %d, g_begintime = %d\n", g_endtime, g_begintime);
				DEBUG_LOG_TTC("timer_priv->timeridx = %d, timer period = %d\n", timer_priv->timeridx, g_endtime - g_begintime);
				if(g_intevaltime / 1000 == (g_endtime - g_begintime)){
      		printf("Test Interval Timing, %s count Pass\n", timer_priv->risedownflag ? "Incrementing" : "Decrementing");
				} else 
					printf("Test Interval Timing, but %s count Fail\n", timer_priv->risedownflag ? "Incrementing" : "Decrementing");
				g_stopflag = 1;
			}
    }else{
			itcs_timer_stop(timer_priv);
			DEBUG_LOG_TTC("timer_priv->timeridx = %d\n", timer_priv->timeridx);
      DEBUG_LOG_TTC("g-endtime= %d,g_begintime= %d\n", g_endtime, g_begintime);
      printf("Test Interval Timing, %s count Fail\n", timer_priv->risedownflag ? "Incrementing" : "Decrementing");
			g_stopflag = 1;
    }
    break;
  case TIMER_EVENTCOUNTMODE_INTERRUPT:
    g_stopflag = 1;
    printf("Test Event Timer TestMode Pass\n");
    break;
  case TIMER_MATCH1_INTERRUPT:
    if (g_endtimematch1 - g_begintime) {
			if(!timer_priv->bytes)
      	printf("Test MATCH1 Pass\n");
    }
    else{
			if(!timer_priv->bytes)
      	printf("Test MATCH1 Fail\n"); 
    }
    break;
  case TIMER_MATCH2_INTERRUPT:
    if (g_endtimematch2 - g_begintime) {
			if(!timer_priv->bytes)
      	printf("Test MATCH2 Pass\n");
    }
    else {
			if(!timer_priv->bytes)
      	printf("Test MATCH2 Fail\n"); 
    }
    break;
  case TIMER_MATCH3_INTERRUPT:
    if (g_endtimematch3 - g_begintime) {
			if(!timer_priv->bytes){
				itcs_timer_stop(timer_priv);
      	printf("Test MATCH3 Pass\n");
				g_stopflag = 1;
			}
    }else{
			if(!timer_priv->bytes){
				itcs_timer_stop(timer_priv);
      	printf("Test MATCH3 Fail\n"); 
				g_stopflag = 1;
			}
    }
    break;
  default:
     printf(" TEST Fail\n");
     break;
  }
  return;
}

static void timer_show_usage(void) {
  printf("Usage: ttc [OPTION]...\n\n");
  printf("-h, --help\t\t command help\n");
  printf("-u, --config timer unit id\t\t config unit ttc\n");
  printf("-c, --config timer id\t\t config ttc\n");
  printf("-m, --ttcmode \t\t timermode for ttc\n");
  printf("-r, --risedown\t\t risedown for ttc\n");
  printf("-t, --matchtime(ms)\t\t matchreg time for ttc\n");
  printf("-s, --settime(ms)\t\t settime for interval mode\n");
  printf("-w, --waveform\t\t waveform for ttc\n");
  printf("-o, --option\t\t option of the cascade\n");
}

static char *l_opt_arg1;
char *p;
static char *const short_options    = "u:c:m:r:t:s:w:o:";
static struct option long_options[] = {
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0},
};

static int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

int timer_main(int argc, char *argv[]) {
  int option_index = 0, c, i = 0;
  uint32_t  matchflag = 0, matchvalue[4] = {-1, -1, -1, -1};
  uint32_t ret = 0;
  uint32_t settime = 0;
  timer_priv_t *timer_priv = ( timer_priv_t *)malloc(sizeof( timer_priv_t));
	memset(timer_priv, 0, sizeof(*timer_priv));
	timer_priv_t *timer_priv1 = ( timer_priv_t *)malloc(sizeof( timer_priv_t));
	memset(timer_priv1, 0, sizeof(*timer_priv1));
	timer_priv_t *timer_priv2 = ( timer_priv_t *)malloc(sizeof( timer_priv_t));
	memset(timer_priv2, 0, sizeof(*timer_priv2));
  timer_match_t timer_match_data;

  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'u':
      timer_priv->idx         = atoi(optarg);
      ret = 1;
      break;
    case 'c':
      timer_priv->timeridx    = atoi(optarg);
      ret = 1;
      break;
    case 'm':
      timer_priv->mode       = atoi(optarg);
      ret = 1;
      break;
    case 'r':
      timer_priv->risedownflag   = atoi(optarg);
      ret = 1;
      break;
    case 'w':
      timer_priv->waveformflag  = atoi(optarg);
      ret=1;
      break;
    case 'o':
      timer_priv->bytes     = atoi(optarg);
      ret=1;
      break;
    case 't':
      l_opt_arg1 = optarg;
      p = strsep(&l_opt_arg1, ":");
      while (p != NULL) {
        ++i;
        printf("%s\n", p);
        matchvalue[i] = atoi(p);
        p             = strsep(&l_opt_arg1, ":");
      }
      g_match1time = matchvalue[1] * 1000; //convert to us
      g_match2time = matchvalue[2] * 1000;
      g_match3time = matchvalue[3] * 1000;
      g_matchnum   = i;
      printf("the num of match = %d\n", g_matchnum);
      break;
    case 's':
      g_intevaltime = atoi(optarg) * 1000;
      ret = 1;
      break;
    case 'h':
    default:
      timer_show_usage();
      ret = -1;
      goto err;
    }
  }

  if (timer_priv->mode == TIMER_MODE_OVERFLOW && g_matchnum == 0 && !timer_priv->bytes) {
		printf("overflow test\n");
    timer_priv = itcs_timer_init(timer_priv, timer_event_cb_fun);
    itcs_timer_config(timer_priv, timer_match_data);
    itcs_timer_start(timer_priv);
    while (!g_stopflag) {
      udelay(500);
    }
  }

  if (timer_priv->mode == TIMER_MODE_INTERVAL && g_matchnum == 0 && !timer_priv->bytes) {
		DEBUG_LOG_TTC("interval test\n");
    timer_priv = itcs_timer_init(timer_priv, timer_event_cb_fun);
    timer_priv->inittime = g_intevaltime;
    itcs_timer_config(timer_priv,  timer_match_data);
    itcs_timer_start(timer_priv);
    while (!g_stopflag) {
      udelay(500);
    }
  }

  if (g_matchnum != 0 && !timer_priv->bytes) {
		printf("match test\n");
    if (timer_priv->mode == 0 || timer_priv->mode == 1) {
      if (g_matchnum == 1) {
        timer_match_data.match1_en = 1;
        timer_match_data.match1 = g_match1time;
      } else if (g_matchnum == 2) {
        timer_match_data.match1_en = 1;
        timer_match_data.match2_en = 1;
        timer_match_data.match1 = g_match1time;
        timer_match_data.match2 = g_match2time;
      } else if (g_matchnum == 3) {
        timer_match_data.match1_en = 1;
        timer_match_data.match2_en = 1;
        timer_match_data.match3_en = 1;
        timer_match_data.match1 = g_match1time;
        timer_match_data.match2 = g_match2time;
        timer_match_data.match3 = g_match3time;
      }
      timer_priv = itcs_timer_init(timer_priv, timer_event_cb_fun);
      timer_priv->inittime = g_intevaltime;
      itcs_timer_config(timer_priv, timer_match_data);
      itcs_timer_start(timer_priv);
      while (!g_stopflag) {
        udelay(500);
      }
    }
  }

	if(timer_priv->bytes){
		printf("cascade test\n");
		//配置参数
		g_intevaltime = 20;

		g_matchnum = 1;
		g_match1time = 10;//us
		timer_match_data.match1_en = 1;
		timer_match_data.match1 = g_match1time;

		timer_priv->mode = 1;
		timer_priv->risedownflag = 1;
		timer_priv->waveformflag = 1;

		timer_priv1->idx = timer_priv->idx;
		timer_priv1->timeridx = 1;
		timer_priv1->mode = 1;
		timer_priv1->risedownflag = 1;
		timer_priv1->waveformflag = 1;
		timer_priv1->bytes = 1;

		timer_priv2->idx = timer_priv->idx;
		timer_priv2->timeridx = 2;
		timer_priv2->mode = 1;
		timer_priv2->risedownflag = 1;
		timer_priv2->bytes = 1;

    timer_priv = itcs_timer_init(timer_priv, timer_event_cb_fun);
    timer_priv->inittime = g_intevaltime;
    itcs_timer_config(timer_priv, timer_match_data);

    timer_priv1 = itcs_timer_init(timer_priv1, timer_event_cb_fun);
    timer_priv1->inittime = g_intevaltime;
    itcs_timer_config(timer_priv1, timer_match_data);

    timer_priv2 = itcs_timer_init(timer_priv2, timer_event_cb_fun);
    timer_priv2->inittime = g_intevaltime;
    itcs_timer_config(timer_priv2, timer_match_data);

		itcs_timer_start(timer_priv2);
		itcs_timer_start(timer_priv1);
		itcs_timer_start(timer_priv);

    while (!g_stopflag) {
      udelay(500);
    }
	}

  if (optind == 1) {
    timer_show_usage();
    ret = -1;
    goto err;
  }

err:
  optind = 1;
  return ret;
}

void timer_init(void) { register_testbench("timer", timer_main, NULL); }

testbench_init(timer_init);
