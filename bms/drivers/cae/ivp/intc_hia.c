#include <common.h>
#include <malloc.h>
#include <irq.h>

extern volatile unsigned int ivp_cae_base_addr;

static volatile unsigned int pass_cnt=0;
static volatile unsigned int base_irq;

static int cae_ivp_irq_handler(int irq, void *args)
{
if(irq==base_irq+4){
pass_cnt++;
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f808);
}else if(irq==base_irq+0){
pass_cnt++;
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e008);
}else if(irq==base_irq+1){
pass_cnt++;
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d008);
}else if(irq==base_irq+2){
pass_cnt++;
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c008);
}else if(irq==base_irq+3){
pass_cnt++;
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b008);
}else{
printf("ivp wrong irq number: \%d\n",irq);
}
return 0;
}

void intc_hia(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("intc_hia\n");
if(!context_ptr)
printf("context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
memset(context_ptr,0,64*1024);
#endif
if(ivp_cae_base_addr==ITCS_C_CAE0_BASE)
base_irq=C_CAE0_IRQn;
else
base_irq=C_CAE5_IRQn;
request_irq(base_irq,cae_ivp_irq_handler,"ring0",NULL);
request_irq(base_irq+1,cae_ivp_irq_handler,"ring1",NULL);
request_irq(base_irq+2,cae_ivp_irq_handler,"ring2",NULL);
request_irq(base_irq+3,cae_ivp_irq_handler,"ring3",NULL);
request_irq(base_irq+4,cae_ivp_irq_handler,"out",NULL);
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000f800);
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000f808);
udelay(1);
udelay(1);
writel(0x40000000&0xffffffff,ivp_cae_base_addr+0x0000003c);
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000e008);
udelay(1);
udelay(1);
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000d008);
udelay(1);
udelay(1);
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000c008);
udelay(1);
udelay(1);
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000b008);
udelay(1);
udelay(1);
if(pass_cnt==5)
printf("intc_hia Pass\n");
else
printf("intc_hia Failed, pass_cnt: %d\n",pass_cnt);
disable_irq(base_irq);
disable_irq(base_irq+1);
disable_irq(base_irq+2);
disable_irq(base_irq+3);
disable_irq(base_irq+4);
}
