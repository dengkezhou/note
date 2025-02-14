#include <common.h>
#include <ids/cvbs.h>
#include <ids/ids.h>
#include <irq.h>
#include <clock.h>
#include <pads.h>

#define RESOL_WIDTH 1280
#define RESOL_HEIGHT 720

//static int32_t RGB2YCbCr[] = {0, 16, 66, 129, 25, 2010, 1974, 112, 112, 1954, 2030};
static int32_t RGB2YCbCr[] = {0, 16, 66, 129, 25, 2010, 1974, 112, 112, 1954, 2030};
static int len_cfg[][2][8] = {
	//8bit
	[0] = {
		//{ 22, RESOL_HEIGHT, 2, 23, RESOL_HEIGHT, 2, 280, 1440 },
		{ 25, RESOL_HEIGHT, 5, 25, RESOL_HEIGHT, 5, 732, RESOL_WIDTH*2 },
		{ 25, RESOL_HEIGHT, 5, 25, RESOL_HEIGHT, 5, 732, RESOL_WIDTH*2 },
	}, 
	//16bit
	[1] = {
		{ 25, RESOL_HEIGHT, 5, 25, RESOL_HEIGHT, 5, 362, RESOL_WIDTH },
		{ 25, RESOL_HEIGHT, 5, 25, RESOL_HEIGHT, 5, 362, RESOL_WIDTH },
	},
	[2] = {
		{ 28, RESOL_WIDTH, 12, 28, RESOL_WIDTH, 12, 125, RESOL_HEIGHT },
		{ 28, RESOL_WIDTH, 12, 28, RESOL_WIDTH, 12, 125, RESOL_HEIGHT },
	},
};

static int sync_cfg[][2][7] = {
	[0] = {
		//{ 0, 24, 126, 24, 4320, 888, 4320 },
		{ 0, 220, 80, 16500, 16500, 16500, 16500 },
		{ 0, 220, 80, 16500, 16500, 16500, 16500 },
	},
	[1] = {
		{ 0, 110, 40, 8250, 8250, 8250, 8250 },
		{ 0, 110, 40, 8250, 8250, 8250, 8250 },
	},
	[2] = {
		{ 10, 10, 10, 10, 10, 10, 10 },
		{ 10, 10, 10, 10, 10, 10, 10 },
	},
};


static int display[][2] = {
	{ RESOL_WIDTH, RESOL_HEIGHT },
	{ RESOL_WIDTH, RESOL_HEIGHT },
};

static struct reg_check reg[] = {
	REG_CHECK_INIT(TVIF_CLK_CFG_ADDR,		0x80000FFF),
	REG_CHECK_INIT(TVIF_CFG_ADDR,			0xF0073C01),
	REG_CHECK_INIT(TVIF_COEF11_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF12_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF13_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF21_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF22_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF23_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF31_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF32_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_COEF33_ADDR,		0xffffffff),
	REG_CHECK_INIT(TVIF_MATRIX_CFG_ADDR,		0xf0001f1f),
	REG_CHECK_INIT(TVIF_UBA1_LEN_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_UNBA_LEN_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_UBA2_LEN_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_LBA1_LEN_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_LNBA_LEN_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_LBA2_LEN_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_BLANK_LEN_ADDR,		0x00000fff),
	REG_CHECK_INIT(TVIF_VIDEO_LEN_ADDR,		0x00000fff),
	REG_CHECK_INIT(TVIF_HSYNC_ADDR,			0xdfff1fff),
	REG_CHECK_INIT(TVIF_VSYNC_UPPER_ADDR,		0x1fff1fff),
	REG_CHECK_INIT(TVIF_VSYNC_LOWER_ADDR,		0x1fff1fff),
	REG_CHECK_INIT(TVIF_DISP_XSIZE_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_DISP_YSIZE_ADDR,		0x000007ff),
	REG_CHECK_INIT(TVIF_STATUS_ADDR,		0x00000000),
};

int tvif_reg_check(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(reg); i++)
		reg[i].addr += reg_base;

	if (common_reg_check(reg, ARRAY_SIZE(reg), 0xffffffff) || common_reg_check(reg, ARRAY_SIZE(reg), 0))
		return -1;

	return 0;
}

static void tvif_ids_writel(uint32_t offset, uint32_t data,
					uint8_t shift, uint8_t width)
{
	uint64_t mask = ((uint64_t)1 << width) - 1;
	uint32_t val;

	val = ids_readl(reg_base + offset);
	val &= ~(mask << shift);
	val |= (data & mask) << shift;
	ids_writel(val, reg_base + offset);
}

static uint32_t tvif_ids_readl(uint32_t offset, uint8_t shift, uint8_t width)
{
	uint64_t mask = ((uint64_t)1 << width) - 1;
	uint32_t val;

	val = ids_readl(reg_base + offset);
	val &= (mask << shift);
	val >>= shift;

	return val;
}

void tvif_set_matrix(struct cvbs_matrix *param)
{
	if (!param)
		return;
	
	if (param->bypass) {
		tvif_ids_writel(TVIF_MATRIX_CFG_ADDR, param->bypass, TVIF_MATRIX_CFG_PASSBY, 1);
		return;
	}

	tvif_ids_writel(TVIF_MATRIX_CFG_ADDR, param->mode, TVIF_MATRIX_CFG_toRGB, 1);
	tvif_ids_writel(TVIF_MATRIX_CFG_ADDR, param->inv_MSB_in, TVIF_MATRIX_CFG_INV_MSB_IN, 1);
	tvif_ids_writel(TVIF_MATRIX_CFG_ADDR, param->inv_MSB_out, TVIF_MATRIX_CFG_INV_MSB_OUT, 1);
	if (param->mode == MATRIX_RGB2YUV) {
		tvif_ids_writel(TVIF_MATRIX_CFG_ADDR, param->coef.out_oft_b, TVIF_MATRIX_CFG_OFT_B, 5);
		tvif_ids_writel(TVIF_MATRIX_CFG_ADDR, param->coef.out_oft_a, TVIF_MATRIX_CFG_OFT_A, 5);
		tvif_ids_writel(TVIF_COEF11_ADDR, param->coef.out_coef11, 0, 32);
		tvif_ids_writel(TVIF_COEF12_ADDR, param->coef.out_coef12, 0, 32);
		tvif_ids_writel(TVIF_COEF13_ADDR, param->coef.out_coef13, 0, 32);
		tvif_ids_writel(TVIF_COEF21_ADDR, param->coef.out_coef21, 0, 32);
		tvif_ids_writel(TVIF_COEF22_ADDR, param->coef.out_coef22, 0, 32);
		tvif_ids_writel(TVIF_COEF23_ADDR, param->coef.out_coef23, 0, 32);
		tvif_ids_writel(TVIF_COEF31_ADDR, param->coef.out_coef31, 0, 32);
		tvif_ids_writel(TVIF_COEF32_ADDR, param->coef.out_coef32, 0, 32);
		tvif_ids_writel(TVIF_COEF33_ADDR, param->coef.out_coef33, 0, 32);
	}
}

void tvif_set_len_cfg(struct cvbs_len_cfg *cfg)
{
	if (!cfg)
		return;
#if 0
	printf("tvif_set_len_cfg\n");
	printf("%d\n", cfg->uba1_len);
	printf("%d\n", cfg->unba_len);
	printf("%d\n", cfg->uba2_len);
	printf("%d\n", cfg->lba1_len);
	printf("%d\n", cfg->lnba_len);
	printf("%d\n", cfg->lba2_len);
	printf("%d\n", cfg->blank_len);
	printf("%d\n", cfg->video_len);
#endif
	tvif_ids_writel(TVIF_UBA1_LEN_ADDR, cfg->uba1_len, 0, 11);
	tvif_ids_writel(TVIF_UNBA_LEN_ADDR, cfg->unba_len, 0, 11);
	tvif_ids_writel(TVIF_UBA2_LEN_ADDR, cfg->uba2_len, 0, 11);
	tvif_ids_writel(TVIF_LBA1_LEN_ADDR, cfg->lba1_len, 0, 11);
	tvif_ids_writel(TVIF_LNBA_LEN_ADDR, cfg->lnba_len, 0, 11);
	tvif_ids_writel(TVIF_LBA2_LEN_ADDR, cfg->lba2_len, 0, 11);
	tvif_ids_writel(TVIF_BLANK_LEN_ADDR, cfg->blank_len, 0, 12);
	tvif_ids_writel(TVIF_VIDEO_LEN_ADDR, cfg->video_len, 0, 12);
}

void tvif_set_sync_cfg(struct cvbs_sync_cfg *cfg)
{
	if (!cfg)
		return;
#if 1
	printf("tvif_set_sync_cfg\n");
	printf("%d\n", cfg->Hsync_VBI_ctrl);
	printf("%d\n", cfg->Hsync_delay);
	printf("%d\n", cfg->Hsync_extend);
	printf("%d\n", cfg->Vsync_delay_upper);
	printf("%d\n", cfg->Vsync_extend_upper);
	printf("%d\n", cfg->Vsync_delay_lower);
	printf("%d\n", cfg->Vsync_extend_lower);
#endif
	tvif_ids_writel(TVIF_HSYNC_ADDR, cfg->Hsync_VBI_ctrl, TVIF_HSYNC_VBI_CTRL, 2);
	tvif_ids_writel(TVIF_HSYNC_ADDR, cfg->Hsync_delay, TVIF_HSYNC_DELAY, 13);
	tvif_ids_writel(TVIF_HSYNC_ADDR, cfg->Hsync_extend, TVIF_HSYNC_EXTEND, 13);
	tvif_ids_writel(TVIF_VSYNC_UPPER_ADDR, cfg->Vsync_delay_upper, TVIF_VSYNC_DELAY, 13);
	tvif_ids_writel(TVIF_VSYNC_UPPER_ADDR, cfg->Vsync_extend_upper, TVIF_VSYNC_EXTEND, 16);
	tvif_ids_writel(TVIF_VSYNC_LOWER_ADDR, cfg->Vsync_delay_lower, TVIF_VSYNC_DELAY, 13);
	tvif_ids_writel(TVIF_VSYNC_LOWER_ADDR, cfg->Vsync_extend_lower, TVIF_VSYNC_EXTEND, 16);
}

void tvif_set_display(struct cvbs_display *cfg)
{
	if (!cfg)
		return;

	tvif_ids_writel(TVIF_DISP_XSIZE_ADDR, cfg->xsize - 1, 0, 11);
	tvif_ids_writel(TVIF_DISP_YSIZE_ADDR, cfg->ysize - 1, 0, 11);
}

void tvif_get_display(int *xsize, int *ysize)
{
	*xsize = tvif_ids_readl(TVIF_DISP_XSIZE_ADDR, 0, 11) + 1;
	*ysize = tvif_ids_readl(TVIF_DISP_YSIZE_ADDR, 0, 11) + 1;
}

void tvif_set_clk(int num)
{
	uint32_t val;
	int clk;
	
	clk = itcs_module_get_clock(CPU,"ids_etc");
	printf("ids tvif set clk = %d\n", clk);

	val = (1 << TVIF_CLK_CFG_EN_CLOCK) | (0 << TVIF_CLK_CFG_PB_CLOCK) |
		  (1 << TVIF_CLK_CFG_INV_CLOCK) | (1 << TVIF_CLK_CFG_SEL_CLOCK) |
		  (0 << TVIF_CLK_CFG_DIVER_CLOCK);
	tvif_ids_writel(TVIF_CLK_CFG_ADDR, val, 0, 32);

	clk += 1;//remove warning
}

void tvif_set_cfg(struct cvbs_cfg *cfg)
{
	uint32_t val;

	val = (cfg->itu601_656n << TVIF_CFG_ITU601_656n) |
		  (cfg->Bit16ofITU60 << TVIF_CFG_BIT16ofITU601) |
		  (cfg->Direct_data << TVIF_CFG_DIRECT_DATA) |
		  (cfg->bitsSwap << TVIF_CFG_BITSWAP) |
		  (cfg->dataOrder << TVIF_CFG_DATA_ORDER) |    
		  (cfg->invVsync << TVIF_CFG_INV_VSYNC) |    
		  (cfg->invHsync << TVIF_CFG_INV_HSYNC) |    
		  (cfg->invHref << TVIF_CFG_INV_HREF) |    
		  (cfg->invField << TVIF_CFG_INV_FIELD) |    
		  (cfg->beginEAV << TVIF_CFG_Begin_by_EAV);
	printf("config reg 0x%x val= 0x%x\n", reg_base+TVIF_CFG_ADDR, val);
	tvif_ids_writel(TVIF_CFG_ADDR, val, 0, 32);
}

void tvif_ctrl(int flags)
{
	tvif_ids_writel(TVIF_CFG_ADDR, flags, TVIF_CFG_TVIF_EN, 1);
}

int tvif_frame_irq(void)
{
	uint32_t status;
	int ret = -1;
	//printf("irq reg = 0x%x\n", reg_base + IDSINTPND);
	status = ids_readl(reg_base + IDSINTPND);
	if (status & (1 << IDSINTPND_TVIFINT)) {
		ids_dbg("success to send a tvif frame\n");
		ret = 0;
		irq_num++;
	}
	ids_writel(status, reg_base + IDSSRCPND);
	ids_writel(status, reg_base + IDSINTPND);

	return ret;	
}

void tvif_wait_frame(void)
{
	while (tvif_frame_irq())
		;
}

void tvif_irq_mode(void)
{
	int ret;

	ret = request_irq(C_IDS_IRQn, (irq_handler_t)tvif_frame_irq, "tvif", NULL);
	if (ret < 0) {
		ids_err("Tvif request irq err\n");
		return;
	}	
}

static void tvif_default_cfg(int flags, int mode, int bit)
{
	struct cvbs_default_cfg def;
	

	if ((flags != f_PAL) && (flags != f_NTSC))
		return;

	def.cfg.itu601_656n = mode;
	def.cfg.Bit16ofITU60 = bit;
	if (bit == CVBS_24BIT)
		def.cfg.Direct_data = CVBS_RGB;
	else
		def.cfg.Direct_data = CVBS_YUV;
	def.cfg.bitsSwap = DISABLE;
	if (bit == CVBS_8BIT)
		def.cfg.dataOrder = 0;
	else
		def.cfg.dataOrder = 1;
	
	def.cfg.invVsync = ENABLE;
	def.cfg.invHsync = ENABLE; 
	def.cfg.invHref = DISABLE;
	def.cfg.invField = DISABLE;
	def.cfg.beginEAV = LINE_WITH_EAV;
	def.param.mode = MATRIX_RGB2YUV;
	if (bit == CVBS_24BIT)
		def.param.bypass = 1;
	else
		def.param.bypass = 0;
	def.param.inv_MSB_in = DISABLE;
	def.param.inv_MSB_out = DISABLE;
	memcpy(&(def.param.coef), RGB2YCbCr, 4 * ARRAY_SIZE(RGB2YCbCr));
	memcpy(&(def.display), display[flags], 4 * ARRAY_SIZE(display[flags]));
	memcpy(&(def.sync_cfg), sync_cfg[bit][flags], 4 * ARRAY_SIZE(sync_cfg[bit][flags]));
	memcpy(&(def.len_cfg), len_cfg[bit][flags], 4 * ARRAY_SIZE(len_cfg[bit][flags]));

	tvif_set_display(&(def.display));
	tvif_set_clk(1);
	tvif_set_cfg(&(def.cfg));
	tvif_set_matrix(&(def.param));
	tvif_set_len_cfg(&(def.len_cfg));
	tvif_set_sync_cfg(&(def.sync_cfg));
}

int tvif_close(void)
{
	return 0;
	//return cvbs_close();
}

int tvif_cfg(int flags, int mode, int bit)
{
	
	tvif_default_cfg(flags, mode, bit);
	return 0;
	//return cvbs_dev_cfg();
}

int tvif_open()
{
	#if 0
	int ret;

	ret = cvbs_open(name);
	if (ret < 0) {
		cvbs_err("Tvif: cannot find %s cvbs chip\n", name);
		return -1;
	}
	#endif
	return 0;
}

int tvif_init(void)
{

	itcs_module_set_clock(CPU, "ids_etc", "dpll", 201600000, false);
	//itcs_module_set_clock(CPU, "ids_eitf", "dpll", 148500000, false);
	itcs_module_set_clock(CPU, "ids_eitf", "dpll", 74250000, false);

	printf("ids_etc clk = %lld\n",itcs_module_get_clock(CPU, "ids_etc"));
	printf("ids_eitf clk = %lld\n",itcs_module_get_clock(CPU, "ids_eitf"));

	lcd_set_output_if(TV_DISPLAY);

	return 0;
}
