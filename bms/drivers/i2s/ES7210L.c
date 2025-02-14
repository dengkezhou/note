#include <errno.h>
#include <stdint.h>
#include <config.h>
#include <malloc.h>
#include <initcall.h>
#include <irq.h>
#include <clock.h>
#include <pads.h>
#include <i2c.h>
#include <i2s-mc.h>
#include <common.h>
#include <pads.h>
/**************************************************/
//Revision：1.3.4.2
//Master模式下的NFS格式需要手动调节LRCK分频
/**************************************************/

/***************参数定义***************/
#define ES7210L				0x10			//Read 0x3F == 0x1X，判断IC型号是否为ES7210L
#define STATEconfirm		0x0B			//状态机确认 回读STATEconfirm的寄存值是否为02，确认IC正常工作状态

#define NORMAL_I2S			0x00
#define NORMAL_LJ			0x01
#define NORMAL_DSPA			0x03
#define NORMAL_DSPB			0x23
#define TDM_1LRCK_DSPA		0x10
#define TDM_1LRCK_DSPB		0x11
#define TDM_1LRCK_I2S		0x12
#define TDM_1LRCK_LJ		0x13
#define TDM_NLRCK_DSPA		0x14
#define TDM_NLRCK_DSPB		0x15
#define TDM_NLRCK_I2S		0x16
#define TDM_NLRCK_LJ		0x17
#define Format_Len24		0x00
#define Format_Len20		0x01
#define Format_Len18		0x02
#define Format_Len16		0x03
#define Format_Len32		0x04

#define VDDA_3V3			0x00
#define VDDA_1V8			0x01
#define MCLK_PIN			0x00
#define SCLK_PIN			0x01
/***************参数定义***************/

/***************参数选择***************/
/*mi2s mclk = 24M, LRclk = fs = 24000, sclk = fs * 2 * chn_width, */
#define Device 				ES7210L			//产品选择是ES7210L,只支持1V8供电
#define CHANNELS_MAX		2				//TDM_NFS模式下配置,多少CH做级联,偶数,其他模式下默认2即可
#define MSMode_MasterSelOn	0				//产品主从模式选择:默认选择0为SlaveMode,打开为1选择MasterMode
#define Ratio 				1024				//实际Ratio=MCLK/LRCK比率，需要和实际时钟比例匹配
#define Format 				NORMAL_I2S	    //数据格式选择,需要和实际时序匹配
#define Format_Len			Format_Len32	//数据长度选择,需要和实际时序匹配
#define SCLK_DIV			16				//SCLK分频选择:(选择范围1~127),SCLK=MCLK/SCLK_DIV
#define SCLK_INV			1				//默认对齐方式为下降沿,1为上升沿对齐,需要和实际时序匹配
#define MCLK_SOURCE			MCLK_PIN		//是否硬件没接MCLK需要用SCLK当作MCLK
#define DoubleSpeed			0				//高采样率下配置DoubleSpeed才能工作(ES7210超过48K,ES7210L超过96K)

//#define VDDA_VOLTAGE		VDDA_3V3		//模拟电压选择为3V3还是1V8,需要和实际硬件匹配
#define ADC_PGA_GAIN		0				//ADC模拟增益:(选择范围0~14),具体对应关系见相应DS说明
#define ADC_Volume			191				//ADC数字增益:(选择范围0~255),191:0DB,±0.5dB/Ste调试 
#define Dmic_Selon 			0				//DMIC选择:默认选择关闭0,打开为1
#define Dmic_GAIN 			0				//DMIC增益:(选择范围0~7),6dB/Step
/***************参数选择***************/

/*codec bus*/
#define I2CWRNBYTE_CODEC(reg, value) es7210l_write_byte(reg, value)
#define CODEC_I2C_NUM            4  /*4 个芯片控制 8 路 i2s 通道，4个芯片在同一i2c总线，地址为0x40 ~ 0x43*/
#define ES7210L_I2C_BUS          5
#define ES7210L_CODEC_BASE_ADDR  (0x40 + g_i2c_codec_id)
static i2c_dev_t *g_i2c_dev = NULL;
static int g_i2c_codec_id = 0;

void ES7210L_ADC(void);

/*i2c write reg*/
static void es7210l_write_byte(uint8_t reg, uint8_t val)
{
	
	int ret;
    i2c_msg_t msg;
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;

    msg.addr = ES7210L_CODEC_BASE_ADDR;
    msg.flags = 0;
    msg.buf = buf;
    msg.len = sizeof(buf);

   ret = itcs_i2c_transfer(g_i2c_dev, &msg, 1);
    if (ret < 0) {
        printf("es7210l write 0x%x to 0x%x failed, ret = %d\n", val, reg, ret);
        return;
    }
}

static int es7210l_read_byte(uint8_t reg, uint8_t *rbuf, uint32_t rlen)
{
    i2c_dev_t *dev = g_i2c_dev;
    i2c_msg_t msg[2];
    int ret;

    if (!dev)
        return -1;

    msg[0].addr = ES7210L_CODEC_BASE_ADDR;
    msg[0].flags = 0;
    msg[0].buf = &reg;
    msg[0].len = 1;
    msg[1].addr = ES7210L_CODEC_BASE_ADDR;
    msg[1].flags = CDNS_I2C_READ;
    msg[1].buf = rbuf;
    msg[1].len = rlen;
    ret = itcs_i2c_transfer(dev, msg, 2);
    if (ret < 0) {
        printf("es7210l read from 0x%x failed\n", reg);
        return ret;
    }

	return 0;
}

int es7210_es_read_all(void)
{
    uint8_t tmp;
    for (uint8_t i = 0; i <= 0x4c; i++) {
        if (es7210l_read_byte(i, &tmp, 1) < 0)
			return -1;
        printf("%x: 0x%x\n", i, tmp);
    }
	printf("\n");
	return 0;
}

/*es probe*/
int i2s_mc_codec_probe()
{
	int i,ret;
	static int init = 0;

	if(init)
	{
		printf("i2s codec already init\n");
		return 0;
	}

#if 1

	/* power on */
	itcs_pads_set_mode(RTC, 0, PADS_MODE_OUT, 1);

	/*codec reset*/
	ret  = itcs_pads_set_mode(CPU, PADSRANGE(125, 128), PADS_MODE_OUT, 0);
	if (ret)
	{
		printf("codec itcs_pads_set_mode failed, ret =%d\n",ret);
	}
	ret  = itcs_pads_set_value(CPU, PADSRANGE(125, 128), 0);
	if (ret)
	{
		printf("codec itcs_pads_set_value 0 failed, ret =%d\n",ret);
	}

	/*delay 100ms*/
	udelay(100 * 1000);

	ret  = itcs_pads_set_value(CPU, PADSRANGE(125, 128), 1);
	if (ret)
	{
		printf("codec itcs_pads_set_value 1, ret =%d\n",ret);
	}
#endif

	/*i2c init, 总线只需要初始化一次*/
	g_i2c_dev = itcs_i2c_init(ES7210L_I2C_BUS, I2C_MASTER, ADDR_7BITS, 0, I2C_MAX_STANDARD_MODE_FREQ);
	if (g_i2c_dev == NULL)
	{
		printf("itcs_i2c_init failed\n");
		return -1;
	}

	for(i = 0; i < CODEC_I2C_NUM; ++i)
	{
		g_i2c_codec_id = i;
		
		/*codec init*/
		ES7210L_ADC();

		//es7210_es_read_all();
		printf("addr 0x%x inited\n", ES7210L_CODEC_BASE_ADDR);
	}

	init = 1;

	return 0;
}


void ES7210L_ADC(void)
{
	I2CWRNBYTE_CODEC(0x00,0xFF);	
	I2CWRNBYTE_CODEC(0x00,0x32);	
	I2CWRNBYTE_CODEC(0x09,0x20);	
	I2CWRNBYTE_CODEC(0x0A,0x10);	
	I2CWRNBYTE_CODEC(0x23,0x2A);	
	I2CWRNBYTE_CODEC(0x22,0x0A);	
	I2CWRNBYTE_CODEC(0x21,0x2A);	
	I2CWRNBYTE_CODEC(0x20,0x0A);	
	
/***************模式选择***************/
	I2CWRNBYTE_CODEC(0x08,(CHANNELS_MAX<<3) + (SCLK_INV<<3) + 0x04 + (DoubleSpeed<<1));
	if(Format == TDM_1LRCK_DSPA)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x03);
		I2CWRNBYTE_CODEC(0x12,0x01);
	}
	if(Format == TDM_1LRCK_DSPB)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x23);
		I2CWRNBYTE_CODEC(0x12,0x01);
	}	
	if(Format == TDM_1LRCK_I2S)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x00);//	
		I2CWRNBYTE_CODEC(0x12,0x02);
	}
	if(Format == TDM_1LRCK_LJ)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x01);//	
		I2CWRNBYTE_CODEC(0x12,0x02);
	}
	if(Format == TDM_NLRCK_DSPA)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x03);
		I2CWRNBYTE_CODEC(0x12,0x03);//N TDMIN 后1P配置 没标志位
		I2CWRNBYTE_CODEC(0x12,0x07);//N TDMIN 第1P配置 开启标志位识别		
	}
	if(Format == TDM_NLRCK_DSPB)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x23);	
		I2CWRNBYTE_CODEC(0x12,0x03);//N TDMIN 后3P配置 没标志位
		I2CWRNBYTE_CODEC(0x12,0x07);//N TDMIN 第1P配置 开启标志位识别		
	}
	if(Format == TDM_NLRCK_I2S)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x00);
		I2CWRNBYTE_CODEC(0x12,0x03);//N TDMIN 后1P配置 没标志位
		I2CWRNBYTE_CODEC(0x12,0x07);//N TDMIN 第1P配置 开启标志位识别		
	}
	if(Format == TDM_NLRCK_LJ)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x01);	
		I2CWRNBYTE_CODEC(0x12,0x03);//N TDMIN 后3P配置 没标志位
		I2CWRNBYTE_CODEC(0x12,0x07);//N TDMIN 第1P配置 开启标志位识别		
	}
	if(Format == NORMAL_I2S)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x00);	
		I2CWRNBYTE_CODEC(0x12,0x00);	
	}
	if(Format == NORMAL_LJ)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x01);	
		I2CWRNBYTE_CODEC(0x12,0x00);	
	}
	if(Format == NORMAL_DSPA)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x03);	
		I2CWRNBYTE_CODEC(0x12,0x00);	
	}
	if(Format == NORMAL_DSPB)
	{
		I2CWRNBYTE_CODEC(0x11,(Format_Len<<5) + 0x23);	
		I2CWRNBYTE_CODEC(0x12,0x00);	
	}
/***************模式选择***************/
		
	I2CWRNBYTE_CODEC(0x40,0xC3);
	
	I2CWRNBYTE_CODEC(0x14,0x3C);
	I2CWRNBYTE_CODEC(0x15,0x3C);

	I2CWRNBYTE_CODEC(0x17,0x10);
	I2CWRNBYTE_CODEC(0x41,0x71);
	I2CWRNBYTE_CODEC(0x42,0x71);
	I2CWRNBYTE_CODEC(0x47,0x06);	
	I2CWRNBYTE_CODEC(0x48,0x26);	
	I2CWRNBYTE_CODEC(0x49,0x06);	
	I2CWRNBYTE_CODEC(0x4A,0x26);

	if(Dmic_Selon == 1)
	{
		I2CWRNBYTE_CODEC(0x10,0xC0 + (Dmic_GAIN<<3) + Dmic_GAIN);	
	}	
	//ADC GAIN
	I2CWRNBYTE_CODEC(0x43,0x10 + ADC_PGA_GAIN);	
	I2CWRNBYTE_CODEC(0x44,0x10 + ADC_PGA_GAIN);	
	I2CWRNBYTE_CODEC(0x45,0x10 + ADC_PGA_GAIN);	
	I2CWRNBYTE_CODEC(0x46,0x10 + ADC_PGA_GAIN);	
	//ADC GAIN
	//ADC Volume
	I2CWRNBYTE_CODEC(0x1B,ADC_Volume);	
	I2CWRNBYTE_CODEC(0x1C,ADC_Volume);	
	I2CWRNBYTE_CODEC(0x1D,ADC_Volume);	
	I2CWRNBYTE_CODEC(0x1E,ADC_Volume);	
	//ADC Volume
	
//这里的Ratio是指的实际的Ratio
//比如 12M288-48K 6CH NFS的情况下,实际的LRCK为16K Ratio=12m288/16=768
	I2CWRNBYTE_CODEC(0x03,SCLK_DIV);//Master Mode下SCLK DIV	
	I2CWRNBYTE_CODEC(0x06,0x00);
	if( Ratio == 3000 )//MCLK/LRCK=3000,24M-8K
	{
		I2CWRNBYTE_CODEC(0x04,0x0B);//Master Mode下LRCK DIV=3000	
		I2CWRNBYTE_CODEC(0x05,0xB8);

		I2CWRNBYTE_CODEC(0x02,0x0F);//3000 *4/15=800	
		I2CWRNBYTE_CODEC(0x07,0x32);//800				
	}
	if( Ratio == 2400 )//MCLK/LRCK=2400
	{
		I2CWRNBYTE_CODEC(0x04,0x09);//Master Mode下LRCK DIV=2400
		I2CWRNBYTE_CODEC(0x05,0x60);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x85);	}//2400 /5=480	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x8A);	}//2400 /10=240
		I2CWRNBYTE_CODEC(0x07,0x1E);//480
	}
	if( Ratio == 2048 )//MCLK/LRCK=2048
	{
		I2CWRNBYTE_CODEC(0x04,0x08);//Master Mode下LRCK DIV=2048	
		I2CWRNBYTE_CODEC(0x05,0x00);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x84);	}
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x88);	}
		I2CWRNBYTE_CODEC(0x07,0x20);	
	}
	if( Ratio == 1600 )//MCLK/LRCK=1600
	{
		I2CWRNBYTE_CODEC(0x04,0x06);//Master Mode下LRCK DIV=1600	
		I2CWRNBYTE_CODEC(0x05,0x40);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x82);	}//1600/2=800
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x84);	}//1600/4=400
		I2CWRNBYTE_CODEC(0x07,0x32);//OSR=800	
	}
	if (Ratio == 1500 )//MCLK/LRCK=1500
	{
		I2CWRNBYTE_CODEC(0x04,0x05);//Master Mode下LRCK DIV=1500	
		I2CWRNBYTE_CODEC(0x05,0xDC);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x4F);	}//1500 *8/15=800	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x0F);	}//1500 *4/15=400
		I2CWRNBYTE_CODEC(0x07,0x32);//800	
	}
	if( Ratio == 1200 )//MCLK/LRCK=1200
	{	
		I2CWRNBYTE_CODEC(0x04,0x04);//Master Mode下LRCK DIV=1200
		I2CWRNBYTE_CODEC(0x05,0xB0);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0xC5);	}//1200 *2/5=480	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x85);	}//1200 *1/5=240
		I2CWRNBYTE_CODEC(0x07,0x1E);//480
	}
	if( Ratio == 1024 )//MCLK/LRCK=1024
	{
		I2CWRNBYTE_CODEC(0x04,0x04);//Master Mode下LRCK DIV=1024	
		I2CWRNBYTE_CODEC(0x05,0x00);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x82);	}
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x84);	}
		I2CWRNBYTE_CODEC(0x07,0x20);	
	}
	if( Ratio == 800 )//MCLK/LRCK=800
	{
		I2CWRNBYTE_CODEC(0x04,0x03);//Master Mode下LRCK DIV=800	
		I2CWRNBYTE_CODEC(0x05,0x20);
		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x81);	}//800/1=800
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x82);	}//800/2=400
		I2CWRNBYTE_CODEC(0x07,0x32);//OSR=800	
	}
	if( Ratio == 768 )//MCLK/LRCK=768
	{
		I2CWRNBYTE_CODEC(0x04,0x03);//Master Mode下LRCK DIV=768	
		I2CWRNBYTE_CODEC(0x05,0x00);

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0xC3);	}//768 *2/3=512	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x83);	}//768 *1/3=256	
		I2CWRNBYTE_CODEC(0x07,0x20);
	}
	if( Ratio == 600 )//MCLK/LRCK=600
	{		
		I2CWRNBYTE_CODEC(0x04,0x02);//Master Mode下LRCK DIV=600
		I2CWRNBYTE_CODEC(0x05,0x58);
	
		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x05);	}//600 *4/5=480	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0xC5);	}//600 *2/5=240
		I2CWRNBYTE_CODEC(0x07,0x1E);//480		
	}	
	if( Ratio == 512 )//MCLK/LRCK=512
	{
		I2CWRNBYTE_CODEC(0x04,0x02);//Master Mode下LRCK DIV=512
		I2CWRNBYTE_CODEC(0x05,0x00);

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x81);	}//512*1=512
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x82);	}//512/2=256
		I2CWRNBYTE_CODEC(0x07,0x20);		
	}	
	if( Ratio == 400 )//MCLK/LRCK=400
	{	
		I2CWRNBYTE_CODEC(0x04,0x01);//Master Mode下LRCK DIV=400	
		I2CWRNBYTE_CODEC(0x05,0x90);	

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0xC1);	}//400*2=800
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x81);	}//400*1=400
		I2CWRNBYTE_CODEC(0x07,0x32);//OSR=800		
	}
	if( Ratio == 384 )//MCLK/LRCK=384
	{
		I2CWRNBYTE_CODEC(0x04,0x01);//Master Mode下LRCK DIV=384	
		I2CWRNBYTE_CODEC(0x05,0x80);

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x03);	}//384 *4/3=512	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0xC3);	}//384 *2/3=256	
		I2CWRNBYTE_CODEC(0x07,0x20);
	}
	if( Ratio == 256 )//MCLK/LRCK=256
	{
		I2CWRNBYTE_CODEC(0x04,0x01);//Master Mode下LRCK DIV=256	
		I2CWRNBYTE_CODEC(0x05,0x00);
	
		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0xC1);	}//256*2=512
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x81);	}//256*1=256
		I2CWRNBYTE_CODEC(0x07,0x20);
	}
	if( Ratio == 192 )//MCLK/LRCK=192
	{
		I2CWRNBYTE_CODEC(0x04,0x00);//Master Mode下LRCK DIV=192
		I2CWRNBYTE_CODEC(0x05,0xC0);

		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x43);	}//192 *8/3=512	
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x03);	}//192 *4/3=256	
		I2CWRNBYTE_CODEC(0x07,0x20);
	}
	if( Ratio == 128 )//MCLK/LRCK=128
	{
		I2CWRNBYTE_CODEC(0x04,0x00);//Master Mode下LRCK DIV=128	
		I2CWRNBYTE_CODEC(0x05,0x80);
		
		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x01);	}//128*4=512
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0xC1);	}//128*2=256
		I2CWRNBYTE_CODEC(0x07,0x20);
	}		
	if( Ratio == 64 )//MCLK/LRCK=64
	{
		I2CWRNBYTE_CODEC(0x04,0x00);//Master Mode下LRCK DIV=64
		I2CWRNBYTE_CODEC(0x05,0x40);	
		if( DoubleSpeed == 0 )	{	I2CWRNBYTE_CODEC(0x02,0x41);	}//64*8=512
		if( DoubleSpeed == 1 )	{	I2CWRNBYTE_CODEC(0x02,0x01);	}//64*4=256
		I2CWRNBYTE_CODEC(0x07,0x20);
	}	
	if( Ratio == 32 )//MCLK/LRCK=32 PS:32FS下 DoubleSpeed必须配置1
	{
		I2CWRNBYTE_CODEC(0x04,0x00);//Master Mode下LRCK DIV=32
		I2CWRNBYTE_CODEC(0x05,0x20);

		I2CWRNBYTE_CODEC(0x02,0x41);	
		I2CWRNBYTE_CODEC(0x07,0x20);	
	}

	/*dmic clk / 2*/
	I2CWRNBYTE_CODEC(0x0e, 0xb);

	/*enable dmic*/
	I2CWRNBYTE_CODEC(0x10, 0xff);

	I2CWRNBYTE_CODEC(0x4B,0x0F);	
	I2CWRNBYTE_CODEC(0x4C,0x0F);	
	if(MSMode_MasterSelOn == 0)//ES7210 Slave
	{	
		I2CWRNBYTE_CODEC(0x00,0x71);	
		I2CWRNBYTE_CODEC(0x00,0x41);
	}		
	if(MSMode_MasterSelOn == 1)//ES7210 Master
	{
		I2CWRNBYTE_CODEC(0x01,0x40);	
		I2CWRNBYTE_CODEC(0x00,0x71);	
		I2CWRNBYTE_CODEC(0x00,0x01);		
		I2CWRNBYTE_CODEC(0x08,(CHANNELS_MAX<<3) + (SCLK_INV<<3) + 0x04 + (DoubleSpeed<<1) + MSMode_MasterSelOn);					
	}	
}   

void ES7210L_Standby(void)//待机配置(0UA)--搭配ES7210L_Resume(void)//恢复配置
{
	I2CWRNBYTE_CODEC(0x06,0x00);	  
	I2CWRNBYTE_CODEC(0x4B,0xFF);	  
	I2CWRNBYTE_CODEC(0x4C,0xFF);	  
	I2CWRNBYTE_CODEC(0x0B,0xD0);	  
	I2CWRNBYTE_CODEC(0x40,0x80);	  
	I2CWRNBYTE_CODEC(0x01,0x7F);	  
	I2CWRNBYTE_CODEC(0x06,0x07);
	I2CWRNBYTE_CODEC(0x43,0x00);	
	I2CWRNBYTE_CODEC(0x44,0x00);	
	I2CWRNBYTE_CODEC(0x45,0x00);	
	I2CWRNBYTE_CODEC(0x46,0x00);	  
}

void ES7210L_Resume(void)//恢复配置(未下电)--搭配ES7210L_Standby(void)
{
	I2CWRNBYTE_CODEC(0x43,0x10);	
	I2CWRNBYTE_CODEC(0x44,0x10);	
	I2CWRNBYTE_CODEC(0x45,0x10);	
	I2CWRNBYTE_CODEC(0x46,0x10);
	I2CWRNBYTE_CODEC(0x06,0x00);	
	I2CWRNBYTE_CODEC(0x01,0x20);	
	I2CWRNBYTE_CODEC(0x40,0x42);
	I2CWRNBYTE_CODEC(0x0B,0x02);	
	I2CWRNBYTE_CODEC(0x4B,0x00);	  
	I2CWRNBYTE_CODEC(0x4C,0x00);	
}