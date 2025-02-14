/**








**/

#ifndef _IMAPX_ENC_IRQ_H_
#define _IMAPX_ENC_IRQ_H_

#include <common.h>

#define IMAPX_VENC_ADDR		ITCS_C_VENC_BASE
#define IMAPX_VENC_INTR	    C_VENC_IRQn


int venc_irq_init(void);
void venc_irq_deinit(void);
void venc_irq_wait(void);
void venc_irq(void );


void venc_register_rt(void *rt);
void venc_rt_write_reg(unsigned int addr, unsigned value);
void venc_rt_read_reg(unsigned int addr, unsigned value);
void venc_rt_enable_hw();
void venc_rt_disable_hw();
void venc_rt_wait_hw();


#endif

