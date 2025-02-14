#include <common.h>
#include <asm/io.h>
#include <ids/ids.h>

static void scaler_writel(uint32_t reg_addr, uint32_t data,
					uint8_t shift, uint8_t width)
{
	uint32_t mask = (uint32_t)((uint64_t)(((uint64_t)1 << (uint64_t)width)) - 1);
	uint32_t val;

	val = readl(reg_base + reg_addr);
	val &= ~(mask << shift);
	val |= (data & mask) << shift;
	//printf("scaler_writel val=0x%x\n",val);
	writel(val, reg_base + reg_addr);
}

static uint32_t scaler_readl(uint32_t reg_addr, uint8_t shift, uint8_t width)
{
	uint32_t mask = (uint32_t)((uint64_t)(((uint64_t)1 << (uint64_t)width)) - 1);
	uint32_t val;

	val = readl(reg_base + reg_addr);
	val &= (mask << shift);
	val >>= shift;

	return val;
}

void scaler_set_zoom_coef(uint32_t *coef)
{
	int i;
	
	if (!coef[0])
		return;
	for (i = 0; i < coef[0] / 2; i++) {
		scaler_writel(SCALER_COE_INTERP_00 + i * 8, coef[i * 2 + 2], 0, 14);
		scaler_writel(SCALER_COE_INTERP_00 + i * 8 + 4, coef[i * 2 + 1], 0, 14);
	}
}

void scaler_set_zoom_algorithm(int flags, int val)
{
	uint32_t reg_off = 0;
	
	if (flags == ZOOMOUT)
		reg_off += 4;
	
	scaler_writel(reg_off + SCALER_ALG_ZOOM_IN, val, 0, 4);
}

void scaler_set_zoominout(struct zoom_cfg *cfg)
{
	int type;

	if (!cfg)
		return;

	type = cfg->type;
	if (cfg->mode == ZOOMIN)
		type -= 2;
	
	scaler_set_zoom_algorithm(cfg->mode, type);
	scaler_set_zoom_coef(cfg->coe_interp);
}

static uint32_t scaler_cal_ratio(int in, int out)               
{                                                               
	uint32_t inter;                                             

	if (!out) {                                                 
		ids_err("Scaler output resolution cannot be zero\n");
		return -1;                                              
	}                                                           

	inter = in * 8192 / out;                                    
	return inter;                                               
}                                                               

int scaler_set_reslution_ratio(struct scaler_resolution *input, struct scaler_resolution *output)
{
	uint32_t ratio, val = 0;

	ratio = scaler_cal_ratio(input->vertical, output->vertical);
	scaler_writel(SCALER_RATIO_V, ratio, 0, 17);
	if (((ratio >> 13) & 0xf) >= 4) {
		printf("need use average 4*4 mode\n");
		val = 1;
	}
	//printf("ratio ver is 0x%x\n", ratio);
	ratio = scaler_cal_ratio(input->horizontal, output->horizontal);
	scaler_writel(SCALER_RATIO_H, ratio, 0, 17);
	if (((ratio >> 13) & 0xf) >= 4) {
		printf("need use average 4*4 mode\n");
		val = 1;
	}
	//printf("ratio her is 0x%x\n", ratio);
	return val;
}

void scaler_set_resolution(int flags, struct scaler_resolution *resolution)
{
	uint32_t reg_off = 0;
	uint32_t val= 0;

	if (flags == SCALER_OUTPUT_ADDR)
		reg_off += 0x4;
	val = (resolution->vertical << 16) | resolution->horizontal;
	//printf("scaler resolution val 0x%x\n", val);
	scaler_writel(reg_off + SCALER_RSL_IN_V_H, val, 0, 32);
}

void scaler_get_resolution(int flags, struct scaler_resolution *resolution)
{
	uint32_t reg_off = 0;

	if (flags == SCALER_OUTPUT_ADDR)
		reg_off += 0x4;

	resolution->vertical = scaler_readl(reg_off + SCALER_RSL_IN_V_H, 16, 13);
	resolution->horizontal = scaler_readl(reg_off + SCALER_RSL_IN_V_H, 0, 13);
}

void scaler_init(struct scaler_module *dev)
{
	if (!dev)	
		return;

	//scaler_writel(SCALER_CNTL_REG, 1, 0, 1);
	//scaler_writel(SCALER_CNTL_REG, dev->bypass, 1, 1);
	//if (dev->bypass) {
	scaler_set_resolution(SCALER_INPUT_ADDR, &(dev->in_resolute));
	scaler_set_resolution(SCALER_OUTPUT_ADDR, &(dev->out_resolute));
	scaler_set_reslution_ratio(&(dev->in_resolute), &(dev->out_resolute));
	//}
	//scaler_writel(SCALER_CNTL_REG, 1, 0, 1);
	scaler_writel(SCALER_CNTL_REG, (dev->bypass << 1) | 0x5, 0, 3);
}

void scaler_para_load(int flags)
{
	scaler_writel(SCALER_CNTL_REG, flags, 2, 1);
}
