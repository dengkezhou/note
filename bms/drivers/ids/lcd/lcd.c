#include <ids/ids.h>
#include <common.h>
#include <irq.h>
#include <ids/lcd.h>
#include <pads.h>
static struct lcd_param panel[] = {
	[0] = {
		.name = "ZDYZ_1280_800",
		.mPixelClock = 72000,
		.mHActive = 1280,
		.mVActive = 800,
		.mHBackPorch = 88,
		.mVBackPorch = 23,
		.mHFrontPorch = 72,
		.mVFrontPorch = 15,
		.mHSyncPulseWidth = 20,
		.mVSyncPulseWidth = 10,
		.mHSyncPolarity = 0,
		.mVSyncPolarity = 0,
		.VclkPolarity = 0,
		.VDPolarity = 0,
		.VdenPolarity = 0,
		.Vpwren = 0,
		.Pwren = 1,
		.rgb_seq = RGB_ORDER,
		.rgb_bpp = RGB888,
		.display_type = TFT_LCD,
	},
	[1] = {
		.name = "ZDYZ_1024_600",
		.mPixelClock = 50000,
		.mHActive = 1024,
		.mVActive = 600,
		.mHBackPorch = 140,
		.mVBackPorch = 20,
		.mHFrontPorch = 160,
		.mVFrontPorch = 12,
		.mHSyncPulseWidth = 20,
		.mVSyncPulseWidth = 3,
		.mHSyncPolarity = 0,
		.mVSyncPolarity = 0,
		.VclkPolarity = 0,
		.VDPolarity = 0,
		.VdenPolarity = 0,
		.Vpwren = 0,
		.Pwren = 1,
		.rgb_seq = RGB_ORDER,
		.rgb_bpp = RGB888,
		.display_type = TFT_LCD,
	},
	[2] = {
		.name = "ZDYZ_800_480",
		.mPixelClock = 30000,
		.mHActive = 800,
		.mVActive = 480,
		.mHBackPorch = 88,
		.mVBackPorch = 32,
		.mHFrontPorch = 40,
		.mVFrontPorch = 13,
		.mHSyncPulseWidth = 48,
		.mVSyncPulseWidth = 3,
		.mHSyncPolarity = 0,
		.mVSyncPolarity = 0,
		.VclkPolarity = 0,
		.VDPolarity = 0,
		.VdenPolarity = 0,
		.Vpwren = 0,
		.Pwren = 1,
		.rgb_seq = RGB_ORDER,
		.rgb_bpp = RGB888,
		.display_type = TFT_LCD,
	},
	[3] = {
		.name = "RTL",
		.mHActive = 1024,
		.mVActive = 600,
		.mHBackPorch = 1,
		.mVBackPorch = 1,
		.mHFrontPorch = 1,
		.mVFrontPorch = 1,    
		.mHSyncPulseWidth = 44,
		.mVSyncPulseWidth = 5,
		.mHSyncPolarity = 0,   
		.mVSyncPolarity = 0,   
		.mPixelClock = 148500,  
		.VclkPolarity = 1,   
		.VDPolarity = 0,     
		.VdenPolarity = 0,   
		.Vpwren = 0,         
		.Pwren = 1,          
		.rgb_seq = RGB_ORDER,
		.rgb_bpp = RGB888,
		.display_type = TFT_LCD,
	},
	[4] = {
		.name = "RTL_SMALL_IMG",
		.mHActive = 80,
		.mVActive = 45,
		.mHBackPorch = 1,
		.mVBackPorch = 1,
		.mHFrontPorch = 1,
		.mVFrontPorch = 1,    
		.mHSyncPulseWidth = 5,
		.mVSyncPulseWidth = 5,
		.mHSyncPolarity = 0,   
		.mVSyncPolarity = 0,   
		.mPixelClock = 148500,  
		.VclkPolarity = 1,   
		.VDPolarity = 0,     
		.VdenPolarity = 0,   
		.Vpwren = 0,         
		.Pwren = 1,          
		.rgb_seq = RGB_ORDER,
		.rgb_bpp = RGB888,
		.display_type = TFT_LCD,
	},
};

uint32_t reg_base = ITCS_C_IDS_BASE;
uint32_t irq_num = 0;

static int pix_clk = 0;

static int rgb_value[6] = {
	0x6, 0x9, 0x12, 0x18, 0x21, 0x24 
};

static struct reg_check reg[] = {
	REG_CHECK_INIT(LCDCON1, 0x0003FF01),
	REG_CHECK_INIT(LCDCON2, 0x07FF07FF),
	REG_CHECK_INIT(LCDCON3, 0x07FF07FF),
	REG_CHECK_INIT(LCDCON4, 0x07FF07FF),
	REG_CHECK_INIT(LCDCON5, 0xBF001FC0),
	REG_CHECK_INIT(LCDCON6, 0x07FF07FF),
};

int lcd_reg_check(void)
{
	int i;

	for (i = 0;i < ARRAY_SIZE(reg);i++)
		reg[i].addr += reg_base;
	
   if (common_reg_check(reg, ARRAY_SIZE(reg), 0xffffffff) || common_reg_check(reg, ARRAY_SIZE(reg), 0))
		return -1;

	return 0;
}

void lcd_set_output_if(enum EXT_DISPLAY_TYPE flags)
{
	uint32_t val;

	val = ids_readl(reg_base + LCDCON5);
	val &= ~(0x3 << LCDCON5_DSPTYPE);
	val |= (flags << LCDCON5_DSPTYPE);
	ids_writel(val, reg_base + LCDCON5);
}

void lcd_set_rgb_cfgorder(int order)
{
	uint32_t val;

	val = ids_readl(reg_base + LCDCON5);
	val &= ~(0x3f << LCDCON5_RGBORDER);
	val |= (order << LCDCON5_RGBORDER);
	ids_writel(val, reg_base + LCDCON5);
}

void lcd_in_polarity(void)
{
	uint32_t val, value;

	val = ids_readl(reg_base + LCDCON5);
	value = val & (0x1f << LCDCON5_INVVDEN);
	value = ~value;
	val &= ~(0x1f << LCDCON5_INVVDEN);
	val |= value;
	ids_writel(val, reg_base + LCDCON5);
}


static void lcd_disable_auto_change(void)
{
	ids_writel((0xf << LCDVCLKFSR_CDOWN) | (0x1 << LCDVCLKFSR_RFRM_NUM),
			reg_base + LCDVCLKFSR);
}

void lcd_set_panel(int lineval, int hozval)
{
	uint32_t lcdcon = 0;
	lcdcon = ((lineval - 1) << LCDCON6_LINEVAL) | 
			 ((hozval - 1) << LCDCON6_HOZVAL);
	ids_writel(lcdcon, reg_base + LCDCON6);
}

void lcd_set_vsync_polarity(int flags)
{
	uint32_t val;
	
	val = ids_readl(reg_base + LCDCON5);
	val &= ~(0x1 << LCDCON5_INVVFRAME);
	val |= (flags << LCDCON5_INVVFRAME);
	ids_writel(val, reg_base + LCDCON5);
}

static void lcd_set_reg(struct lcd_param *lcd)
{
	uint32_t lcdcon = 0;
	int rate, div;
	
	lcdcon = (0<<LCDCON1_VMMODE) | (3<<LCDCON1_PNRMODE) |
			 (12<<LCDCON1_STNBPP) | (0<<LCDCON1_ENVID);
	//rate = module_get_clock(IDS0EITF_CLK_BASE);
	rate = pix_clk;
	div = rate / (lcd->mPixelClock * 1000);
	if (div < 1)
		div = 1;
	lcdcon |= (((div - 1) & 0x3ff) << LCDCON1_CLKVAL);
	ids_writel(lcdcon, reg_base + LCDCON1);

	lcdcon = ((lcd->mVBackPorch - 1)<< LCDCON2_VBPD) | 
			 ((lcd->mVFrontPorch - 1)<< LCDCON2_VFPD);
	ids_writel(lcdcon, reg_base + LCDCON2);

	lcdcon = ((lcd->mVSyncPulseWidth - 1)<< LCDCON3_VSPW) |
			 ((lcd->mHSyncPulseWidth - 1)<< LCDCON3_HSPW);
	ids_writel(lcdcon, reg_base + LCDCON3);

	lcdcon = ((lcd->mHBackPorch - 1)<< LCDCON4_HBPD) |
			 ((lcd->mHFrontPorch - 1)<< LCDCON4_HFPD);
	ids_writel(lcdcon, reg_base + LCDCON4);

	lcdcon = (lcd->rgb_bpp << LCDCON5_RGB565) |
			 (rgb_value[lcd->rgb_seq] << LCDCON5_RGBORDER) |
			 (TFT_LCD << LCDCON5_DSPTYPE) |
			 (lcd->VclkPolarity << LCDCON5_INVVCLK) |
			 (lcd->mHSyncPolarity << LCDCON5_INVVLINE) |
			 (lcd->mVSyncPolarity << LCDCON5_INVVFRAME) |
			 (lcd->VDPolarity << LCDCON5_INVVD) |
			 (lcd->VdenPolarity << LCDCON5_INVVDEN) |
			 (lcd->Vpwren << LCDCON5_INVPWREN) |
			 (lcd->Pwren << LCDCON5_PWREN);
	ids_writel(lcdcon, reg_base + LCDCON5);

	lcdcon = ((lcd->mVActive - 1) << LCDCON6_LINEVAL) | 
			 ((lcd->mHActive - 1) << LCDCON6_HOZVAL);
	ids_writel(lcdcon, reg_base + LCDCON6);

	/* unmask all interrupt */
	ids_writel(0x0, reg_base + IDSINTMSK); 
	/* VCLK frequency auto change */
	lcd_disable_auto_change();
}

int lcd_frame_irq(void)
{
	uint32_t status;
	uint32_t vclkfsr;
	int ret = -1;

	status = ids_readl(reg_base + IDSINTPND);

	if (status & (1 << IDSINTPND_LCDINT)) {
		ids_dbg("success to send a frame\n");
		ret = 0;
	}

	if (status & (1 << IDSINTPND_VCLKINT))
		ids_dbg("too fast to send frames");

	if (status & (1 << IDSINTPND_OSDERR))
		ids_err("OSD occur error, need to reset OSD\n");
	
	vclkfsr = ids_readl(reg_base + LCDVCLKFSR);
	if (vclkfsr & (1 << LCDVCLKFSR_VCLKFAC)) {
		ids_dbg("CDOWN = 0x%x, RFRM_NUM = 0x%x, CLKVAL = 0x%x\n",
			   (vclkfsr >> LCDVCLKFSR_CDOWN) & 0xF,
			   (vclkfsr >> LCDVCLKFSR_RFRM_NUM) & 0x3F,
			   (vclkfsr >> LCDVCLKFSR_CLKVAL) & 0x3FF);
		ids_writel(vclkfsr, reg_base + LCDVCLKFSR);
	}
	ids_writel(status, reg_base + IDSSRCPND);
	ids_writel(status, reg_base + IDSINTPND);

	irq_num++;
	return ret;
}

void lcd_wait_frame(void)
{
	while (lcd_frame_irq())
		;
}

void lcd_get_screen_size(int *width, int *height)
{
	uint32_t val;

	val = ids_readl(reg_base + LCDCON6);
	*width = (val & 0xfff) + 1;
	*height = ((val >> LCDCON6_LINEVAL) & 0xfff) + 1;
	//printf("lcd screen size %d*%d\n", *width, *height);
}

void lcd_set_screen_size(int width, int height)
{
	uint32_t val = 0;

	val = (((height - 1) & 0x7ff) << LCDCON6_LINEVAL) | ((width - 1) & 0x7ff);
	ids_writel(val, reg_base + LCDCON6);
}

int lcd_close(void)
{
	lcd_enable(0);
	return 0;
}

int lcd_open(char *name)
{
	int i;

	for (i = 0;i < ARRAY_SIZE(panel);i++)
		if (!strcmp(name, panel[i].name)) 
			break;

	if (i == ARRAY_SIZE(panel))
		return -1;

	lcd_set_reg(&panel[i]);
	return 0;
}

void lcd_irq_mode(void)
{
	int ret;

	ret = request_irq(C_IDS_IRQn, (irq_handler_t)lcd_frame_irq, "lcd", NULL);
	if (ret < 0) {
		ids_err("Lcd request irq err\n");
		return;
	}
		
}

void lcd_enable(int enable)
{
	uint32_t val;

	val = ids_readl(reg_base + LCDCON1);
	if (enable)
		val |= (1 << LCDCON1_ENVID);
	else
		val &= ~(0 << LCDCON1_ENVID);
	ids_writel(val, reg_base + LCDCON1);
}

int lcd_init(void)
{
	reg_base = ITCS_C_IDS_BASE;
	itcs_module_enable(CPU, "ids");
	itcs_module_set_clock(CPU, "bus6", "dpll", 500000000, false);
  	printf("bus6 clk = %lld\n",itcs_module_get_clock(CPU, "bus6"));
	itcs_module_set_clock(CPU, "ids_etc", "dpll", 201600000, false);
	itcs_module_set_clock(CPU, "ids_eitf", "dpll", 50000000, false);
	
	pix_clk = 50000000;
#ifdef CONFIG_COMPILE_ASIC

	itcs_pads_set_mode(RTC, 0, PADS_MODE_OUT, 1);
#endif
	//reset pin
#ifdef CONFIG_COMPILE_ASIC
	itcs_pads_set_mode(SAP, 17, PADS_MODE_OUT, 0);
#else
	itcs_pads_set_mode(CPU, 78, PADS_MODE_OUT, 0);
#endif

#ifdef CONFIG_COMPILE_FPGA
	udelay(1000*1000);
#else
	udelay(100);
#endif

#ifdef CONFIG_COMPILE_ASIC
	itcs_pads_set_value(SAP, 17, 1);
#else
	itcs_pads_set_value(CPU, 78, 1);
#endif


	//back light pin
#ifdef CONFIG_COMPILE_ASIC
	itcs_pads_set_mode(CPU, 77, PADS_MODE_OUT, 1);
#else
	itcs_pads_set_mode(CPU, 79, PADS_MODE_OUT, 1);
#endif
	printf("ids lcd init done\n");

printf("ids dma high addr = 0x%x\n", readl(0xc9f00820));

#ifdef CONFIG_TB_RUN_DDR1
	printf("set ids dma high addr to 0x55\n");
	writel(0x55, 0xc9f00820);
	printf("ids dma high addr = 0x%x\n", readl(0xc9f00820));
#endif

	//rgb interface pin
	itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "ids");

	return 0;
}
