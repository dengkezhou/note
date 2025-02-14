/**








**/

#include <imapx_enc_irq.h>
#include <assert.h>

//volatile int gVENCIntr=0;
//static rtl_trace_callback_t gRt={0};

uint32_t venc0_irq_mode_enable  = 0 ;
uint32_t venc0_irq_value = 0;
uint32_t venc0_dmmu_mode_enable  = 0; //0 not use dmmu 1:use dmmu
uint32_t venc0_irq_async_mode_enable = 0;
/**
 * @brief update_venc0_dmmu_address 
 *
 * @param swreg
 * @param value
 * @param dmmuAddress
 *
 * @return  0: not use dmmu mode or not used dmmu fix this value , 1 ,dmmu enable  -1 ,other exception 
 */
#define VENC0_DMMU_DEFAULT_MAP_SIZE  10240000
uint32_t update_venc0_dmmu_address(uint32_t swreg,uint32_t ddrAddress,uint32_t *dmmuAddress){
//	printf("write reg -> %d 0x%X \n",swreg,ddrAddress);
	assert(dmmuAddress != NULL);
	if(!venc0_dmmu_mode_enable) {
		return 0;//not use dmmu map
	}
	uint32_t dmmuFixFlag = 0;
	switch(swreg){
		case 5: //stream start
		case 11: // out jpeg y
		case 12: // out jpeg crcb
		case 13: //out jpeg cb
		case 51: //h264 vp8 ??
			dmmuFixFlag = 1;
			break;
		default :
			dmmuFixFlag = 0;
			break;
	}
	if(dmmuFixFlag){
		if(ddrAddress == 0 ){
			*dmmuAddress = 0;
			printf("dmmu 0 no need map\n");
			return 0;
		}
    #if 0
		else if(  ddrAddress < DRAM_BASE_PA ){
			printf("address range is not in ddr range ->0x%X 0x%X\n",ddrAddress,DRAM_BASE_PA);
			return -1;
		}
		else {
			//*dmmuAddress = dmmu_map("venc0",ddrAddress,VENC0_DMMU_DEFAULT_MAP_SIZE);

			//printf("dmmu map 0x%X -> 0x%X\n",ddrAddress,*dmmuAddress);
			return 1;
		}
    #endif

	}
	else {
		return 0;
	}
}
int venc0_h1_irq_handler(int irq ,void *s )
{	
	volatile unsigned int val;
	volatile unsigned int *pVal = (unsigned int *)IMAPX_VENC_ADDR;
	venc0_irq_value =  *pVal;

	val = pVal[1];
	if(val&0xFF){
		pVal[1] &= (~0x01);
	}

	return 0;
}

void venc_irq_wait(void)
{
	volatile unsigned int *pVal = (unsigned int *)IMAPX_VENC_ADDR;
//	printf("%s +++++++++++++++++\n",__func__);
	if(venc0_irq_mode_enable) {
		//printf("waiting for venc0 irq\n");
		if(venc0_irq_async_mode_enable ){
		//	printf("irq sync mode\n");
			return ;
		}
		while(1 ){
			if(venc0_irq_value &0xff){
				//printf("venc0 irq happened\n");
				break;
			}
		}

	}
	else {
		while((pVal[1] & 0x1) == 0);
		pVal[1] &= (~0x01);	
	}
}

int venc_irq_init(void)
{
	int ret ;
	ret = request_irq(IMAPX_VENC_INTR,venc0_h1_irq_handler,"venc0_irq", NULL);
	return ret;

}

void venc_irq_deinit(void)
{
	///remveo venc1 irq ,not support now 
}

void venc_register_rt(void *rt)
{
}

void venc_rt_write_reg(unsigned int addr, unsigned value)
{
}

void venc_rt_read_reg(unsigned int addr, unsigned value)
{
}

