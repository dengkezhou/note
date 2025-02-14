#include <errno.h>
#include <stdint.h>
#include <config.h>
#include <malloc.h>
#include <initcall.h>
#include <irq.h>
#include <clock.h>
#include <pads.h>
#include <i2c.h>
#include <i2s.h>

/* ES8388 I2C BUS ID */
#ifdef CONFIG_COMPILE_ASIC
#define ES8388_I2C_BUS      5
#else
#define ES8388_I2C_BUS      3
#endif

/* ES8388 I2C address */
#define ES8388_I2C_ADDR     0x11

static uint8_t is_probed = 0;

/***************参数定义***************/
#define NORMAL_I2S			0x00
#define NORMAL_LJ			0x01
#define NORMAL_DSPA			0x03
#define NORMAL_DSPB			0x23
#define Format_Len24		0x00
#define Format_Len20		0x01
#define Format_Len18		0x02
#define Format_Len16		0x03
#define Format_Len32		0x04

#define VDDA_3V3			0x00
#define VDDA_1V8			0x01
/***************参数定义***************/

/***************参数选择***************/
#define MSMode_MasterSelOn	0				//产品主从模式选择:默认选择0为SlaveMode,打开为1选择MasterMode
#define Ratio 				512				//实际Ratio=MCLK/LRCK比率,需要和实际时钟比例匹配
#define Format 				NORMAL_I2S		//数据格式选择,需要和实际时序匹配
#define Format_Len			Format_Len16	//数据长度选择,需要和实际时序匹配
#define SCLK_DIV			4				//SCLK分频选择:(选择范围1~28),具体对应关系见相应DS说明
#define SCLK_INV			1				//默认对齐方式为下降沿,1为上升沿对齐,需要和实际时序匹配
#define DoubleSpeed			0				//高采样率下配置DoubleSpeed才能工作(超过96K)

#define VDDA_VOLTAGE		VDDA_3V3		//模拟电压选择为3V3还是1V8,需要和实际硬件匹配
#define ADC_PGA_GAIN		0				//ADC模拟增益:(选择范围0~9),具体对应关系见相应DS说明
#define ADC_Volume			0				//ADC数字增益:(选择范围0~192),0:0DB,-0.5dB/Step
#define DAC_Volume			0				//DAC数字增益:(选择范围0~192),0:0DB,-0.5dB/Step

#define ADC_SEL             0x2             //0x0 – left data = left ADC, right data = right ADC
                                            //0x1 – left data = left ADC, right data = left ADC
                                            //0x2 – left data = right ADC, right data = right ADC
                                            //0x3 – left data = right ADC, right data = left ADC

struct es_gpio {
    int spk_ctl;
    int pa_en;
    int saradc;
    int hp_det;
    int phone_ctl;
};

struct es_i2s {
    int bus;
    struct i2s_ops ops;
    struct i2s_para para;
};

struct es_i2c {
    i2c_dev_t *i2c_dev;
    int addr;
    int bus;
};

struct es_dev {
    struct es_i2c i2c;
    struct es_i2s i2s;
    struct es_gpio gpio;
};

static struct es_dev *es8388_dev;

extern void cdns_i2s0_init(void);
extern void cdns_i2s1_init(void);

static int es_read(uint8_t reg, uint8_t *rbuf, uint32_t rlen)
{
    struct es_dev *dev = es8388_dev;
    i2c_msg_t msg[2];
    int ret;

    if (!dev)
        return -1;

    msg[0].addr = dev->i2c.addr;
    msg[0].flags = 0;
    msg[0].buf = &reg;
    msg[0].len = 1;
    msg[1].addr = dev->i2c.addr;
    msg[1].flags = CDNS_I2C_READ;
    msg[1].buf = rbuf;
    msg[1].len = rlen;
    ret = itcs_i2c_transfer(dev->i2c.i2c_dev, msg, 2);
    if (ret < 0) {
        printf("es83xx read from 0x%x failed\n", reg);
        return ret;
    }

	return 0;
}

static int es_write_byte(uint8_t reg, uint8_t val)
{
    struct es_dev *dev = es8388_dev;
    i2c_msg_t msg;
    uint8_t buf[2];
    int ret;

    if (!dev)
        return -1;

    buf[0] = reg;
    buf[1] = val;

    msg.addr = dev->i2c.addr;
    msg.flags = 0;
    msg.buf = buf;
    msg.len = sizeof(buf);

    ret = itcs_i2c_transfer(dev->i2c.i2c_dev, &msg, 1);
    if (ret < 0) {
        printf("es83xx write 0x%x to 0x%x failed\n", val, reg);
        return ret;
    }

    return 0;
}

static int es_read_byte(uint8_t reg, uint8_t *rbuf)
{
    return es_read(reg, rbuf, 1);
}

static int es_hw_init(struct es_dev *dev)
{
    dev->i2c.addr = ES8388_I2C_ADDR;
    dev->i2c.bus = ES8388_I2C_BUS;

    dev->i2c.i2c_dev = itcs_i2c_init(dev->i2c.bus, I2C_MASTER,
            ADDR_7BITS, dev->i2c.addr, I2C_MAX_FAST_MODE_FREQ);
    if (!dev->i2c.i2c_dev)
        return -1;

    return 0;
}

int es_read_all(void)
{
    uint8_t tmp;
    for (uint8_t i = 0; i <= 52; i++) {
        if (es_read_byte(i, &tmp) < 0)
			return -1;
        printf("%u: 0x%x\n", i, tmp);
    }
	printf("\n");
	return 0;
}


/**
 * @return
 *     - (-1)  Error
 *     - (0)   Success
 */
static int es_probe(void)
{
    struct es_dev *pdata;
    int ret = -1;

	if (is_probed)
		return 0;

    pdata = malloc(sizeof(*pdata));
    if (!pdata) {
        ret = -ENOMEM;
        goto err_malloc;
    }

    memset(pdata, 0, sizeof(*pdata));
    es8388_dev = pdata;

    ret = es_hw_init(pdata);
    if (ret < 0) {
        printf("ES8388 HW init failed\n");
        goto err_hw;
    }

	is_probed = 1;

	ret = es_read_all();
	if (ret < 0)
		goto err_hw;

    return 0;

err_hw:
    free(pdata);
err_malloc:
    return ret;
}

/***************参数选择***************/

int es8388_codec_init(void)
{
    if (es_probe() < 0) {
        printf("es8388 probe failed\n");
        return -1;
    }
	es_write_byte(0x00,0x80);  
	es_write_byte(0x00,0x06);   
	es_write_byte(0x02,0xF3);   
	es_write_byte(0x02,0xF0);   
	es_write_byte(0x35,0xA0);   
	es_write_byte(0x36,0x08); 

	if	(Ratio == 128)//Ratio=MCLK/LRCK=256：12M288/48K；4M096/16K; 2M048/8K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x08,(MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		if(DoubleSpeed == 0)
		{
			es_write_byte(0x37,0xC0);  
			es_write_byte(0x39,0xC0); 
		}
		if(DoubleSpeed == 1)
		{
			es_write_byte(0x37,0xD0);  
			es_write_byte(0x39,0xD0); 
		}
 	
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x00);//128Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x00);//128Ratio 	
	}
	if (Ratio == 250)//Ratio=MCLK/LRCK=250：12M/48K；4M/16K; 2M/8K；8K采样率下DVDD必须接1V8
	{ 	//ES8388在MasterMode下才支持250
		es_write_byte(0x08,(MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);

		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
 		
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x12);//250Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x12);//250Ratio 
	}
	if	(Ratio == 256)//Ratio=MCLK/LRCK=256：12M288/48K；4M096/16K; 2M048/8K
	{ 
		es_write_byte(0x37,0xD0);  
		es_write_byte(0x39,0xD0); 
		if(DoubleSpeed == 0)
		{
			es_write_byte(0x08,(MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
			es_write_byte(0x0D,(DoubleSpeed<<5) + 0x02);//256Ratio
			es_write_byte(0x18,(DoubleSpeed<<5) + 0x02);//256Ratio 
		}
		if(DoubleSpeed == 1)
		{
			es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
			es_write_byte(0x0D,(DoubleSpeed<<5) + 0x00);//128Ratio
			es_write_byte(0x18,(DoubleSpeed<<5) + 0x00);//128Ratio 
		}
	}
	if	(Ratio == 384)//Ratio=MCLK/LRCK=285：12M288/32K；6M144/16K; 3M072/8K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
		es_write_byte(0x08,(MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x03);//384Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x03);//384Ratio 
	}
	if	(Ratio == 512)//Ratio=MCLK/LRCK=512：24M576/48K；12M288/24K；4M096/8K; 
	{ 
		if(DoubleSpeed == 0)
		{
			es_write_byte(0x37,0xD0);  
			es_write_byte(0x39,0xD0); 
		}
		if(DoubleSpeed == 1)
		{
			es_write_byte(0x37,0xC0);  
			es_write_byte(0x39,0xC0); 
		}
		es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x02);//256Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x02);//256Ratio 
	}
	if	(Ratio == 768)//Ratio=MCLK/LRCK=768：12M288/16K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
		es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x03);//384Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x03);//384Ratio 
	}
	if (Ratio == 1500)//Ratio=MCLK/LRCK=1500：12M/8K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
		es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x17);//750Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x17);//750Ratio 
	}
	if	(Ratio == 1536)//Ratio=MCLK/LRCK=1536：12M288/8K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
		es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x06);//768Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x06);//768Ratio 
	}
	if (Ratio == 3000)//Ratio=MCLK/LRCK=1500：24M/8K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
		es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x1B);//1500Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x1B);//1500Ratio 
	}
	if	(Ratio == 3072)//Ratio=MCLK/LRCK=3072：24M576/8K；8K采样率下DVDD必须接1V8
	{ 
		es_write_byte(0x37,0xC0);  
		es_write_byte(0x39,0xC0); 
		es_write_byte(0x08,0x40 + (MSMode_MasterSelOn<<7) + (SCLK_INV<<5) + SCLK_DIV);
		es_write_byte(0x0D,(DoubleSpeed<<5) + 0x0A);//3072Ratio
		es_write_byte(0x18,(DoubleSpeed<<5) + 0x0A);//3072Ratio 
	}
	if	(VDDA_VOLTAGE == VDDA_1V8)//AVDD=1v8
	{
		es_write_byte(0x36,0xC8);  
		es_write_byte(0x3B,0x20); 
	}
	es_write_byte(0x07,0x7C);   
	es_write_byte(0x2B,0x80);   
	es_write_byte(0x2D,0x10);   
	es_write_byte(0x00,0x30);   
	es_write_byte(0x01,0x00); 
	udelay(10 * 1000); 
	es_write_byte(0x03,0x00);   
	es_write_byte(0x06,0xFF);   
	es_write_byte(0x09,(ADC_PGA_GAIN<<4) + ADC_PGA_GAIN);//模拟PGA:+24dB  
	es_write_byte(0x0A,0xFC);   
	es_write_byte(0x0B,0x00);   
	es_write_byte(0x0C,Format + (Format_Len<<2) + (ADC_SEL << 6));
	es_write_byte(0x10,ADC_Volume);//数字增益 ADCL   
	es_write_byte(0x11,ADC_Volume);//数字增益 ADCR    
	es_write_byte(0x12,0x05);
	es_write_byte(0x13,0x82);
	es_write_byte(0x14,0x32);
	es_write_byte(0x15,0x06);
	es_write_byte(0x16,0x00);
	es_write_byte(0x17,(Format<<1) + (Format_Len<<3));
	es_write_byte(0x19,0x04);
	es_write_byte(0x1A,DAC_Volume);//数字增益 DACL   
	es_write_byte(0x1B,DAC_Volume);//数字增益 DACR    
	es_write_byte(0x26,0x12);
	es_write_byte(0x2E,0x00);  
	es_write_byte(0x2F,0x00);   
	es_write_byte(0x30,0x00); 
	es_write_byte(0x31,0x00);  
	es_write_byte(0x02,0x00);
	udelay(30 * 1000);    
	es_write_byte(0x00,0x37); 
	es_write_byte(0x01,0x60); 
	es_write_byte(0x27,0xB8);   
	es_write_byte(0x2A,0xB8); 
	es_write_byte(0x04,0x3C);  
	es_write_byte(0x00,0x16);
	es_write_byte(0x19,0x00);
	es_write_byte(0x2E,0x1E); //0DB 
	es_write_byte(0x2F,0x1E); //0DB    
	es_write_byte(0x30,0x1E); //0DB  
	es_write_byte(0x31,0x1E); //0DB 

	return 0;
}

void es8388_standby(void)//待机配置--搭配ES8388_Resume(void)//恢复配置
{
	es_write_byte(0x19,0x06);
	es_write_byte(0x2E,0x00);
	es_write_byte(0x2F,0x00);
	es_write_byte(0x30,0x00);
	es_write_byte(0x31,0x00);
	es_write_byte(0x27,0x38);
	es_write_byte(0x2A,0x38);
	es_write_byte(0x04,0x00);
	es_write_byte(0x04,0xC0);
	es_write_byte(0x03,0xFF);
	es_write_byte(0x02,0xF3);
	es_write_byte(0x2B,0x9C);
	es_write_byte(0x00,0x06);
	es_write_byte(0x01,0x58);
}

void es8388_resume(void)//恢复配置(未下电)--搭配ES8388_Standby(void)
{
	es_write_byte(0x2B,0x80);
	es_write_byte(0x27,0xB8);
	es_write_byte(0x2A,0xB8);
	es_write_byte(0x02,0x00);
	es_write_byte(0x03,0x09);
	udelay(30 * 1000);
	es_write_byte(0x00,0x36);
	es_write_byte(0x01,0x60);
	es_write_byte(0x04,0x3C);
	es_write_byte(0x2E,0x1E);
	es_write_byte(0x2F,0x1E);
	es_write_byte(0x30,0x1E);
	es_write_byte(0x31,0x1E);
	es_write_byte(0x19,0x02);
}
