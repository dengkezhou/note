#include <timer.h>
#include <common.h>
#include <irq.h>
#include <../arch/riscv/c920/csi_driver/smarth_rv64/include/sys_freq.h>
#include <asm/io.h>
#define CONFIG_TIMER_NUM 3
extern uint32_t g_begintime;
extern uint32_t g_endtime;
extern uint32_t g_endtimematch1;
extern uint32_t g_endtimematch2;
extern uint32_t g_endtimematch3;
extern uint32_t g_match1time;
extern uint32_t g_match2time;
extern uint32_t g_match3time;
extern uint32_t g_matchnum;
extern uint32_t g_intevaltime;

int TTC0_IRQ[3]={C_TTC0_TIMER0_IRQn, C_TTC0_TIMER1_IRQn, C_TTC0_TIMER2_IRQn};
int TTC1_IRQ[3]={C_TTC1_TIMER0_IRQn, C_TTC1_TIMER1_IRQn, C_TTC1_TIMER2_IRQn};
int TTC_IRQ[3]={S_TTC0_TIMER0_IRQn, S_TTC0_TIMER1_IRQn, S_TTC0_TIMER2_IRQn};
char *TTC[3]={"irq0","irq1","irq2"};

int set_clock_type(timer_handle_t handle,const char *module) {
  uint32_t setextclk = 0;
  uint32_t setclk    = 0;
  timer_priv_t *timer_priv = handle;
  switch (timer_priv->idx)
  {
  case 0:
  case 1:
    if (strcmp(module, "apb") == 0) {
    	setclk = itcs_module_set_clock(CPU, "apb",NULL, 100800000, true);//假设
    	printf("set cpu clk freq = %d\n", setclk);
    	return 1;
    } else if (strcmp(module, "ttc") == 0) {
    	setextclk = itcs_module_set_clock(CPU, "ttc", NULL, 1000000, false);
    	printf("set ttc clk freq= %d\n", setextclk);
    	return 0;
    }
  	break;
  case 2:
    if (strcmp(module, "apb") == 0) {
      setclk = itcs_module_set_clock(SAP, "apb",NULL, 100800000, true);//假设
      printf("set cpu clk freq= %d\n", setclk);
      return 1;
      } else if (strcmp(module, "ttc") == 0) {
      setextclk = itcs_module_set_clock(SAP, "ttc", NULL, 1000000, false);
      printf("set ttc clk freq= %d\n", setextclk);
      return 0;
      } 
    break;
  default:
    break;
  } 
  return -1;
}

void timer_ccr_rise_enable(timer_handle_t handle, uint32_t ret){
  uint32_t i=4*ret;
  uint32_t tempreg = 0;
  timer_priv_t *timer_priv = handle;
  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg &= ~CCR_DECC_ENABLE; //默认是就是down
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
}

void timer_ccr_down_enable(timer_handle_t handle, uint32_t ret){
  uint32_t i=4*ret;
  uint32_t tempreg = 0;
  timer_priv_t *timer_priv = handle;
  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg |= CCR_DECC_ENABLE; //默认是就是down
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
}

void timer_match_mode(timer_handle_t handle, uint32_t ret){
  uint32_t tempreg = 0;
  timer_priv_t *timer_priv = handle;
  uint32_t i = ret*4;

  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg |= CCR_RST_ENABLE;

  if(timer_priv->waveformflag == 1){
    tempreg &=0xffffffdf;//bit[5]=0,waveform使能;bit[6]=1,WPOL 极性问题
    tempreg |= CCR_WEN_WPOL_ENABLE;
    printf("A waveform should appear in this mode\n");
  }
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);

  tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
  tempreg &= ~(IER_EVNT_ENABLE | IER_ITRV_ENABLE | IER_M1_ENABLE | IER_M2_ENABLE | IER_M3_ENABLE);
  writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);
  
  if (timer_priv->idx == 0) {
    timer_priv->irq = TTC0_IRQ[ret];
    request_irq(TTC0_IRQ[ret], itcs_timer_irq, TTC[ret],timer_priv);
    }
  else if(timer_priv->idx == 1){
    timer_priv->irq = TTC1_IRQ[ret];
    request_irq(TTC1_IRQ[ret], itcs_timer_irq, TTC[ret],timer_priv);
    }
  else if(timer_priv->idx == 2){
    timer_priv->irq = TTC_IRQ[ret];
    request_irq(TTC_IRQ[ret], itcs_timer_irq, TTC[ret],timer_priv);
 	}
}

void timer_overflow_mode(timer_handle_t handle, uint32_t ret,timer_match_t match, uint32_t configfreq){
    uint32_t i = 4 * ret;
    uint32_t tempreg = 0;
    timer_priv_t *timer_priv = handle;

    tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
    tempreg &= ~IER_ITRV_ENABLE; //means 2^32 clks, huge!!
    writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

		if (match.match1_en == 1 || match.match2_en == 1 || match.match3_en == 1){
			tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
      tempreg |= CCR_MCHE_ENABLE;
      writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
		}

    if (match.match1_en == 1) {
      tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
      tempreg |= IER_M1_ENABLE;
      writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

      writel((uint64_t)match.match1 * configfreq / 1000000, timer_priv->base + TIMER_MATCH1_C1 + i);
    }

    if (match.match2_en == 1) {
      tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
      tempreg |= IER_M2_ENABLE;
      writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

      writel((uint64_t)match.match2 * configfreq / 1000000, timer_priv->base + TIMER_MATCH2_C1 + i);
    }

    if (match.match3_en == 1) {
      tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
      tempreg |= IER_M3_ENABLE;
      writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

      writel((uint64_t)match.match3 * configfreq / 1000000, timer_priv->base + TIMER_MATCH3_C1 + i);
    }
}

void timer_interval_mode(timer_handle_t handle, uint32_t ret, timer_match_t match, uint32_t configfreq){
  uint32_t i = ret*4;
  uint32_t tempreg = 0;
  uint32_t writefreq = 0;
  timer_priv_t *timer_priv = handle;

  writefreq = (uint64_t)timer_priv->inittime * configfreq / 1000000; //init time unit is um
  writel(writefreq, timer_priv->base + TIMER_IVLR_VALUE_C1 + i);
	DEBUG_LOG_TTC("writenclk_readback = %d\n", readl(timer_priv->base + TIMER_IVLR_VALUE_C1 + i));

  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg |= CCR_INTE_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);

  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg &= ~IER_OVFL_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

	// cacade need counter 2 and 3 clk source from ext	
	if(timer_priv->bytes && timer_priv->timeridx != 0){
	  tempreg = readl(timer_priv->base + TIMER_CLK_CONTROL_C1 + i);
    tempreg |= CLKCR_CSRC_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CLK_CONTROL_C1 + i);
	}

  if (match.match1_en == 1) {
		printf("match.match1_en\n");
    tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
    tempreg |= CCR_MCHE_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
    tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
    tempreg |= IER_M1_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);
    writel((uint64_t)match.match1 * configfreq  / 1000000, timer_priv->base + TIMER_MATCH1_C1 + i);
    }
  if (match.match2_en == 1) {
    tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
    tempreg |= CCR_MCHE_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
    tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
    tempreg |= IER_M2_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);
    writel((uint64_t)match.match2 * configfreq  / 1000000,timer_priv->base + TIMER_MATCH2_C1 + i);
    }
  if (match.match3_en == 1) {
    tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
    tempreg |= CCR_MCHE_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
    tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
    tempreg |= IER_M3_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);
    writel((uint64_t)match.match3 * configfreq  / 1000000,timer_priv->base + TIMER_MATCH3_C1 + i);
    }
}

void timer_eventcount_mode(timer_handle_t handle, uint32_t ret){
    uint32_t i = ret * 4;
    uint32_t tempreg = 0;
    timer_priv_t *timer_priv = handle;

    tempreg = readl(timer_priv->base + TIMER_CLK_CONTROL_C1 + i);
    tempreg |= CLKCR_CSRC_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CLK_CONTROL_C1 + i);
		
    tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
    tempreg |= IER_EVNT_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

    tempreg = readl(timer_priv->base + TIMER_ETCR_C1 + i);
    tempreg |= ETCR_ETEN_ENABLE | ETCR_ECM_ENABLE | ETCR_ETTM_ENABLE |ETCR_EOV_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_ETCR_C1 + i);
}

void timer_test_mode(timer_handle_t handle, uint32_t ret){
    uint32_t i = ret*4;
    uint32_t tempreg = 0;
    timer_priv_t *timer_priv = handle;
    tempreg = readl(timer_priv->base + TIMER_CLK_CONTROL_C1 + i);
    tempreg |= CLKCR_CSRC_ENABLE|CLKCR_PSE_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CLK_CONTROL_C1 + i);
}

void timer_interval_interrupt_enable(timer_handle_t handle, uint32_t ret){
  uint32_t tempreg = 0;
  timer_priv_t *timer_priv = handle;
  uint32_t i = ret * 4;

  tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
  tempreg |= IER_ITRV_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg &= ~CCR_DISC_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);

	if(!timer_priv->bytes || (timer_priv->bytes && timer_priv->timeridx == 0))
  	g_begintime = get_timer(0);
}

void timer_overflow_interrupt_enable(timer_handle_t handle,uint32_t ret){
  uint32_t tempreg = 0;
  timer_priv_t *timer_priv = handle;
  uint32_t i = ret * 4;

  tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
  tempreg |= IER_OVFL_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg &= ~CCR_DISC_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);

	if(!timer_priv->bytes)
  	g_begintime = get_timer(0);
}

void timer_eventcountmode_interrupt_enable(timer_handle_t handle, uint32_t ret){
  timer_priv_t *timer_priv = handle;
  uint32_t tempreg = 0;
  uint32_t i = ret * 4;

  tempreg = readl(timer_priv->base + TIMER_IER_C1 + i);
  tempreg |= IER_EVNT_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_IER_C1 + i);

  tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
  tempreg &= ~CCR_DISC_ENABLE;
  writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1 + i);
}

void INTERRUPT_ENABLE_MARK(timer_handle_t handle, uint32_t tempregisr){
    timer_priv_t *timer_priv = handle;

    if(GET_BIT(tempregisr,5) == 1){
        timer_priv->enum_interrupt = TIMER_EVENTCOUNTMODE_INTERRUPT;
    } else if (GET_BIT(tempregisr, 4) == 1) {
        timer_priv->enum_interrupt = TIMER_OVERFLOW_INTERRUPT;
    } else if (GET_BIT(tempregisr, 0) == 1) {
			if( !timer_priv->bytes || (timer_priv->bytes && timer_priv->timeridx == 2))
        	g_endtime = get_timer(0);
        timer_priv->enum_interrupt = TIMER_INTERVAL_INTERRUPT;
    } else if (GET_BIT(tempregisr, 1) == 1) {
        g_endtimematch1 = get_timer(0);
        timer_priv->enum_interrupt = TIMER_MATCH1_INTERRUPT;
    } else if (GET_BIT(tempregisr, 2) == 1) {
        g_endtimematch2 = get_timer(0);
        timer_priv->enum_interrupt = TIMER_MATCH2_INTERRUPT;
    } else if (GET_BIT(tempregisr, 3) == 1) {
        g_endtimematch3 = get_timer(0);
        timer_priv->enum_interrupt = TIMER_MATCH3_INTERRUPT;
    }
}
#if 0
void CASCADE_ENABLE(timer_handle_t handle){
   timer_priv_t *timer_priv = handle;
   uint64_t tempreg = 0;
   tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1);
   tempreg &= ~CCR_DISC_ENABLE;
   tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C2);
   tempreg &= ~CCR_DISC_ENABLE;
   timer_match_mode(timer_priv,0);
}
#endif
/************************************itcs function******************************************/
int itcs_timer_irq(int idx, void *arg) {
    timer_priv_t *timer_priv = (timer_priv_t *)arg;
    uint32_t tempregisr = 0;
    //应该返回全部的中断标志
    switch (timer_priv->timeridx) {
        case 0:
            tempregisr = readl(timer_priv->base + TIMER_ISR_C1);
            INTERRUPT_ENABLE_MARK(timer_priv, tempregisr);
            break;
        case 1:
            tempregisr = readl(timer_priv->base + TIMER_ISR_C2);
            INTERRUPT_ENABLE_MARK(timer_priv, tempregisr);
            break;
        case 2:
            tempregisr = readl(timer_priv->base + TIMER_ISR_C3);
            INTERRUPT_ENABLE_MARK(timer_priv, tempregisr);
            break;
        default:
            break;
    }

    if (timer_priv->cb_event) {
        timer_priv->cb_event(timer_priv);
    }

    return 0;
}

timer_handle_t itcs_timer_init(timer_handle_t handle, timer_event_cb_t cb_event) {  
  timer_priv_t *timer_priv = handle;
  uint32_t tempreg = 0;

  printf("UNIT %d Timer Count %d MODE %d \n", timer_priv->idx,
         timer_priv->timeridx, timer_priv->mode);
  if (timer_priv->idx < 0 || timer_priv->idx >= CONFIG_TIMER_NUM) {
    return NULL;
  }

  if(timer_priv->bytes == 1 && timer_priv->timeridx == 0){
    switch (timer_priv->idx)
    {
    case 0:
      tempreg = readl(C_SYSM_TTC + TIMER_CVR_VALUE_C3);
      tempreg |=CVAL0;
      writel(tempreg,C_SYSM_TTC + TIMER_CVR_VALUE_C3);
      tempreg = readl(C_SYSM_TTC + TIMER_CVR_VALUE_C3);
      printf("tempreg is 0x%x\n",tempreg);
      if(GET_BIT(tempreg,0)==1) printf(" 64bytes condition \n");
      else if(GET_BIT(tempreg,0)==0) printf("32bytes condition \n");
      //CASCADE_ENABLE(timer_priv->base);
      break;
    case 1:
      tempreg = readl(C_SYSM_TTC + TIMER_CVR_VALUE_C3);
      tempreg |= CVAL1;
      writel(tempreg,C_SYSM_TTC + TIMER_CVR_VALUE_C3);
      if(GET_BIT(tempreg,1)==1) printf("64bytes condition \n");
      else if(GET_BIT(tempreg,1)==0) printf("32bytes condition\n");
      //CASCADE_ENABLE(timer_priv->base);
      break;
    case 2:
      tempreg = readl(S_SYSM_TTC + TIMER_CVR_VALUE_C3);
      tempreg |= CVAL0;
      writel(tempreg,S_SYSM_TTC + TIMER_CVR_VALUE_C3);
      if(GET_BIT(tempreg,0)==1) printf("64bytes condition \n");
      else if(GET_BIT(tempreg,0)==0) printf("32bytes condition\n");
      //CASCADE_ENABLE(timer_priv->base);
      break;
    default:
      break;
    }
  }

  set_clock_type(timer_priv,"apb");
	//set_clock_type(timer_priv,"ttc");

	switch (timer_priv->idx) {
	case 0:
		if(!timer_priv->bytes || (timer_priv->bytes && timer_priv->timeridx == 0))
	  	itcs_module_enable(CPU,"ttc0");
	  timer_priv->base = ITCS_C_TTC0_BASE;
	  break;
	case 1:
		if(!timer_priv->bytes || (timer_priv->bytes && timer_priv->timeridx == 0))
	  	itcs_module_enable(CPU,"ttc1");
	  timer_priv->base = ITCS_C_TTC1_BASE;
	  break;
	case 2:
		if(!timer_priv->bytes || (timer_priv->bytes && timer_priv->timeridx == 0))
	  	itcs_module_enable(SAP,"ttc");
	  timer_priv->base = ITCS_S_TTC_BASE;
	  break;
	default:
	  break;
	}

  timer_match_mode(timer_priv,timer_priv->timeridx);

  timer_priv->cb_event = cb_event;

  return (timer_handle_t)timer_priv;
}

int32_t itcs_timer_config(timer_handle_t handle, timer_match_t match) { 
  uint32_t configfreq = 0;
  timer_priv_t *timer_priv = handle;

  if(timer_priv->idx==1||timer_priv->idx==0){
    configfreq = itcs_module_get_clock(CPU,"apb");
  }
  else if(timer_priv->idx==2){
    configfreq = itcs_module_get_clock(SAP,"apb");
  }
  printf("configfreq = %d\n",configfreq);

  if (timer_priv->risedownflag == 1) {
    timer_ccr_rise_enable(timer_priv,timer_priv->timeridx);
  } else if(timer_priv->risedownflag ==0){
    timer_ccr_down_enable(timer_priv,timer_priv->timeridx);
  }

  switch (timer_priv->mode) {
  case TIMER_MODE_OVERFLOW:
    timer_overflow_mode(timer_priv,timer_priv->timeridx, match, configfreq);
		break;
  case TIMER_MODE_INTERVAL:
    timer_interval_mode(timer_priv,timer_priv->timeridx, match, configfreq);
		break;
  case TIMER_MODE_EVENTCOUNTMODE:
    timer_eventcount_mode(timer_priv,timer_priv->timeridx);
    break;
  case TIMER_MODE_TEST:
    timer_test_mode(timer_priv,timer_priv->timeridx);
		break;
  default:
    return -1;
  }

  return 0;
}

int32_t itcs_timer_start(timer_handle_t handle) {
  timer_priv_t *timer_priv = handle;
  //printf("UNIT %d Timer Count %d MODE %d \n", timer_priv->idx,
  //       timer_priv->timeridx, timer_priv->mode);

  switch (timer_priv->mode) {
  case TIMER_MODE_OVERFLOW:
    timer_overflow_interrupt_enable(timer_priv, timer_priv->timeridx);
		break;
  case TIMER_MODE_INTERVAL:
    timer_interval_interrupt_enable(timer_priv, timer_priv->timeridx);
		break;
  case TIMER_MODE_EVENTCOUNTMODE:
    timer_eventcountmode_interrupt_enable(timer_priv,timer_priv->timeridx);
		break;
  default:
    return -1;
  }
  return 0;
}

int32_t itcs_timer_stop(timer_handle_t handle) {
  uint32_t tempreg;
  timer_priv_t *timer_priv = handle;

  switch (timer_priv->timeridx) {
  case 0:
    tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1);
    tempreg |= CCR_DISC_ENABLE; /*打开是关闭*/
    writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C1);
    break;
  case 1:
    tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C2);
    tempreg |= CCR_DISC_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C2);
    break;
  case 2:
    tempreg = readl(timer_priv->base + TIMER_CCR_CONTROL_C3);
    tempreg |= CCR_DISC_ENABLE;
    writel(tempreg, timer_priv->base + TIMER_CCR_CONTROL_C3);
    break;
  default:
    return -1;
  }
  //printf("STOP UNIT %d TIMER CountNo %d SUCCESS\n", timer_priv->idx,
  //      timer_priv->timeridx);
  return 0;
}

int set_freq_div(timer_handle_t handle, uint32_t divnum) {
  uint32_t reg;
  timer_priv_t *timer_priv = handle;
  switch (timer_priv->timeridx) {
  case 0:
    reg = readl(timer_priv->base + TIMER_CCR_CONTROL_C1);
    reg = (reg & 0xffffffe1) | (divnum << 1);
    writel(reg, timer_priv->base + TIMER_CCR_CONTROL_C1);
    break;
  case 1:
    reg = readl(timer_priv->base + TIMER_CCR_CONTROL_C2);
    reg = (reg & 0xffffffe1) | (divnum << 1);
    writel(reg, timer_priv->base + TIMER_CCR_CONTROL_C2);
    break;
  case 2:
    reg = readl(timer_priv->base + TIMER_CCR_CONTROL_C3);
    reg = (reg & 0xffffffe1) | (divnum << 1);
    writel(reg, timer_priv->base + TIMER_CCR_CONTROL_C3);
    break;
  default:
    return -1;
  }
  printf("SET DIV FREQ SUCCESS!\n");
  return 0;
}
