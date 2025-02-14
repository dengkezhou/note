#include <common.h>
#include <pads.h>
#include <dmic_pcm.h>
#include <malloc.h>

/*config func*/
static int dmic_config(dmic_dev_t* dmic, dmic_mode mode){
    dmic_cfg_t* cfg = dmic->cfg;
    /*default value*/
    cfg->fifo_afull_irq_en = 1;
    cfg->fifo_over_irq_en = 1;
    cfg->fifo_under_irq_en = 1;
    cfg->dma_en = 1;
    cfg->hw_swap = 1;
    cfg->byte_swap = 1;
    cfg->bit_swap = 1;
    cfg->sample_mode = 11;
    cfg->direct_fmt = 1;
    cfg->fifo_dipstick = 16;
    cfg->clk_ratio = 5;

    uint32_t temp = 0;
    //FIFO_UNDER_IRQ_EN
    //temp = FIFO_AFULL_IRQ_EN | FIFO_OVER_IRQ_EN | SAMPLE_MODE(0b11) | DIRECT_FMT | 
            //FIFO_DIPSTICK(16) | CLK_RATIO(3); 
    
    temp = SAMPLE_MODE(0b11) | DIRECT_FMT | FIFO_DIPSTICK(16) | CLK_RATIO(cfg->clk_ratio); 
    temp &= ~(DMA_EN | HW_SWAP | BYTE_SWAP | BIT_SWAP);
    //temp |= HW_SWAP | BYTE_SWAP | BIT_SWAP;
    //temp |= BIT_SWAP;

    cfg->dma_en = 0;
    cfg->hw_swap = 0;
    cfg->byte_swap = 0;
    cfg->bit_swap = 0;

    if(dmic->dma){
        temp |= DMA_EN;
        temp &= ~FIFO_AFULL_IRQ_EN;
        cfg->dma_en = 1;
        DEBUG_LOG("config DMA.\n");
    }
    DEBUG_LOG("config write is %#x\n",temp);
    writel(temp, dmic->membase + ITCS_DMIC_CFG_OFFSET);
    DEBUG_LOG("config read is %#x\n", readl(dmic->membase + ITCS_DMIC_CFG_OFFSET));

    //uint32_t temp1 = readl(dmic->membase + ITCS_DMIC_ISR_OFFSET);
    //DEBUG_LOG("temp1 = %#x\n",temp1);
    return 0;
}

/*irq handler func*/
static int dmic_irqhandler(int irq, void *args) {
    //DEBUG_LOG("irq happened\n");
    dmic_dev_t* dmic = args;
    
    uint32_t temp = readl(dmic->membase + ITCS_DMIC_ISR_OFFSET);
    writel(temp ,dmic->membase + ITCS_DMIC_ISR_OFFSET);
    //DEBUG_LOG("temp = %#x\n",temp);
    //DEBUG_LOG("num. of data in FIFO = %#x\n",((readl(dmic->membase + ITCS_DMIC_FIFO_STAT_OFFSET) & 0x1F0) >> 4));
    
    if(temp & ITCS_INT_FIFO_OVER){
        printf("Interrupt fifo overflow.\n");
    }else if((temp & ITCS_INT_FIFO_AFULL) && (dmic->len > dmic->count)){
        /*loop read 16bytes*/
        //DEBUG_LOG("dmic%d afull\n",dmic->index);
        for(int i = 0; i < 16; i++){
            *(dmic->dst_addr + dmic->count) = readl(dmic->membase + ITCS_DMIC_FIFO_OFFSET);  
            //DEBUG_LOG("data recieved is %#x\n",*(dmic->dst_addr + dmic->count));
            dmic->count = dmic->count + 1;
        }
        //DEBUG_LOG("dmic->count = %u\n", dmic->count);
        return 0;
    }else if((temp & ITCS_INT_FIFO_AFULL) && (dmic->len == dmic->count)){
        uint32_t temp1 = readl(dmic->membase + ITCS_DMIC_CFG_OFFSET);
        temp1 &= ~(FIFO_AFULL_IRQ_EN | FIFO_OVER_IRQ_EN | FIFO_UNDER_IRQ_EN);
        writel(temp1, dmic->membase + ITCS_DMIC_CFG_OFFSET);
        dmic->rx_status = DMIC_RX_COMPLETE;
        return 0;
    }else if(temp & ITCS_INT_FIFO_UNDER){
        printf("Interrupt fifo underflow.\n");
    }else {
        printf("Interrupt abnormal.\n");
    }
    return -1; 
}

/*irq use dma handler func*/
static int dmic_dma_irqhandler(int irq, void *args) {
    //DEBUG_LOG("irq hapenned\n");
    dmic_dev_t* dmic = args;
    uint32_t temp = readl(dmic->membase + ITCS_DMIC_ISR_OFFSET);
    writel(temp ,dmic->membase + ITCS_DMIC_ISR_OFFSET);
    //DEBUG_LOG("temp = %#x\n",temp);
    /*ignore afull irq*/
    if(temp & ITCS_INT_FIFO_OVER){
        printf("Interrupt fifo overflow chan %u.\n", dmic->index);
        return -1;
    }else if(temp & ITCS_INT_FIFO_UNDER){
        printf("Interrupt fifo underflow chan %u.\n", dmic->index);
        return -1;
    }
    return 0; 
}

static int wait_for_blocking(dmic_dev_t* dmic, bool blocked)
{
	int ret;
	while (blocked) {
		ret = itcs_dmic_is_completed(dmic);
        if (ret) {
			break;
	    }
		udelay(1);
	}
	return 0;
}

static int pcm_en(dmic_dev_t* dmic){
    int temp = 0;
    //DMIC Filter Enable Registe
    writel(0x0, dmic->membase + ITCS_DMIC_FILTER_OFFSET);
    temp = ITCS_PCM_ON;
    writel(temp, dmic->membase + ITCS_DMIC_FILTER_OFFSET);

    //DMIC Decimation Register
    temp = ITCS_PCM_128;
    //writel(temp, dmic->membase + ITCS_DMIC_DECIMATION_OFFSET);
    writel(0xf, dmic->membase + ITCS_DMIC_DECIMATION_OFFSET);

    //DMIC Low Pass Frequency Register
    temp = ITCS_PCM_LP(dmic->pcm->lp_alfa);
    writel(temp, dmic->membase + ITCS_DMIC_LP_OFFSET);


    //DMIC High Pass Frequency Register
    temp = ITCS_PCM_HP(dmic->pcm->hp_alfa);
    writel(temp, dmic->membase + ITCS_DMIC_HP_OFFSET);

    //DMIC Filter Volume Register
    temp = ITCS_PCM_VOL(dmic->pcm->vol);
    writel(temp, dmic->membase + ITCS_DMIC_VOL_OFFSET);
    return 0;
}

static int dmic_en(dmic_dev_t* dmic, bool is_enable){
    uint32_t temp = 0;
    temp = readl(dmic->membase + ITCS_DMIC_CTL_OFFSET);
    if(is_enable){
        //temp |= ITCE_FIFO_EN | ITCS_DMIC_ON;
        temp |= ITCE_FIFO_EN | ITCS_DMIC_ON | ITCS_PDM_CLK_EN;
        writel(0x0, dmic->membase + ITCS_DMIC_CTL_OFFSET);
        if(dmic->mode){
            writel(temp, dmic->membase + ITCS_DMIC_CTL_OFFSET);
        } else {
            if(dmic->index == 0)
                writel(temp, dmic->membase + ITCS_DMIC_CTL_OFFSET);
            else if(dmic->index == 1)
                writel(temp | 1 << 6, dmic->membase + ITCS_DMIC_CTL_OFFSET);
            else if(dmic->index == 2)
                writel(temp | 2 << 6, dmic->membase + ITCS_DMIC_CTL_OFFSET);
            else if (dmic->index == 3)
                writel(temp | 3 << 6, dmic->membase + ITCS_DMIC_CTL_OFFSET);
        }
        printf("ctrl_reg = %#X\n", readl(dmic->membase + ITCS_DMIC_CTL_OFFSET));

    }else{
        temp &= ~(ITCS_DMIC_ON | ITCS_PDM_CLK_EN);
        writel(temp, dmic->membase + ITCS_DMIC_CTL_OFFSET);
    }
    return 0;
}

dmic_dev_t* itcs_dmic_init(dmic_chan chan, dmic_mode mode, unsigned int dma, 
                            uint32_t decimation){
    //int ret = 0;
    dmic_dev_t* dmic = malloc(sizeof(*dmic));
    char dmic_name[8] = { 0 };
    memset(dmic, 0, sizeof(dmic_dev_t));

    dmic->index = chan;
    dmic->mode = mode;
    dmic->dma = dma;
    dmic->count = 0;
    dmic->rx_status = DMIC_READY;

    struct pcm* pcm = malloc(sizeof(struct pcm));
    memset(pcm, 0 ,sizeof(struct pcm));

    pcm->decimation = decimation;
    pcm->hp_alfa = 255;
    pcm->lp_alfa = 194;
    pcm->vol = 15;
    dmic->pcm = pcm;

    /*module enable,get clk, set pads*/
    sprintf(dmic_name, "dmic%d", chan);
    DEBUG_LOG("dmic_name is %s\n", dmic_name);
    dmic->name = dmic_name;
    if(dmic->mode){
        itcs_module_enable(CPU, dmic_name);
        dmic->input_clk = itcs_module_set_clock(CPU, "dmic", "epll", 24000000, false);
    } else {
        itcs_module_enable(CPU, "dmic0");
        itcs_module_enable(CPU, dmic_name);
        dmic->input_clk = itcs_module_set_clock(CPU, "dmic", "epll", 24000000, false);
    }
	
    DEBUG_LOG("set input clk = %u\n", itcs_module_get_clock(CPU, "dmic"));
    dmic->input_clk = 24000000;
    DEBUG_LOG("input clk = %u\n", dmic->input_clk);

    switch(chan){
    case DMIC_CHAN0:
        dmic->membase = (void *)ITCS_C_DMIC0_BASE;
        itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "dmic0_0");
        itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "dmic0_1");
        dmic->irq = C_DMIC0_IRQn;
        break;
    case DMIC_CHAN1:
        dmic->membase = (void *)ITCS_C_DMIC1_BASE;
        itcs_module_set_pads_by_index("dmic1_0", 0);
        itcs_module_set_pads_by_index("dmic1_1", 0);
        dmic->irq = C_DMIC1_IRQn;
        break;
    case DMIC_CHAN2:
        dmic->membase = (void *)ITCS_C_DMIC2_BASE;
        itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "dmic2_0");
        itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "dmic2_1");
        dmic->irq = C_DMIC2_IRQn;
        break;
    case DMIC_CHAN3:
        dmic->membase = (void *)ITCS_C_DMIC3_BASE;
        itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "dmic3_0");
        itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "dmic3_1");
        dmic->irq = C_DMIC3_IRQn;
        break;
    }

    /*config*/
    dmic_cfg_t* cfg = malloc(sizeof(*cfg));
    memset(cfg, 0 ,sizeof(dmic_cfg_t));
    dmic->cfg = cfg;
    dmic_config(dmic, mode);

    dmic->ouput_clk = dmic->input_clk / (cfg->clk_ratio + 1) / 2;
    DEBUG_LOG("input clk = %u\n", dmic->input_clk);
    DEBUG_LOG("output clk = %u\n", dmic->ouput_clk);
    DEBUG_LOG("dmic%u irq = %u\n", chan, dmic->irq);
    /*irq*/

    if(dma == 0){
        switch(chan){
        case DMIC_CHAN0:
            request_irq(dmic->irq, dmic_irqhandler, "dmic0", dmic);
            break;
        case DMIC_CHAN1:
            request_irq(dmic->irq, dmic_irqhandler, "dmic1", dmic);
            break;
        case DMIC_CHAN2:
            request_irq(dmic->irq, dmic_irqhandler, "dmic2", dmic);
            break;
        case DMIC_CHAN3:
            request_irq(dmic->irq, dmic_irqhandler, "dmic3", dmic);
            break;
        }
    }else{
        switch(chan){
        case DMIC_CHAN0:
            request_irq(dmic->irq, dmic_dma_irqhandler, "dmic0", dmic);
            break;
        case DMIC_CHAN1:
            request_irq(dmic->irq, dmic_dma_irqhandler, "dmic1", dmic);
            break;
        case DMIC_CHAN2:
            request_irq(dmic->irq, dmic_dma_irqhandler, "dmic2", dmic);
            break;
        case DMIC_CHAN3:
            request_irq(dmic->irq, dmic_dma_irqhandler, "dmic3", dmic);
            break;        
        }
    }
    /*return dmic_dev_t*/
    return dmic;
}

int itcs_dmic_sync(dmic_dev_t* dmic){
    int temp = 0;
    temp = readl(dmic->membase + ITCS_DMIC_CTL_OFFSET);
    switch (dmic->index){
    case 0:
        //temp |= ITCS_MCH_SYNC_EN;
        break;
    case 1:
        if(dmic->mode == 0 || dmic->mode == 2 || dmic->mode == 3 || dmic->mode == 5){
            temp |= ITCS_MCH_SYNC_EN;
            break;
        }else{
            break;
        }  
    case 2:
        if(dmic->mode == 1 || dmic->mode == 3 || dmic->mode == 0){
            temp |= ITCS_MCH_SYNC_EN;
            break;
        }else{
            break;
        } 
    case 3:
        if(dmic->mode == 1 || dmic->mode == 2 || dmic->mode == 4 || dmic->mode == 0){
            temp |= ITCS_MCH_SYNC_EN;
            break;
        }else{
            break;
        } 
    }
    writel(temp, dmic->membase + ITCS_DMIC_CTL_OFFSET);
    return 0;
}


int itcs_dmic_read(dmic_dev_t* dmic, unsigned int *buf, unsigned int len, bool blocked){
    dmic->dst_addr = buf; 
    dmic->len = len;
    dmic->rx_status = DMIC_RX_RUNNING;

    pcm_en(dmic);

    dmic_en(dmic, true);

    if(blocked == true)
        return wait_for_blocking(dmic, 1);
    else
        return 0;
}

int itcs_dmic_is_completed(dmic_dev_t* dmic){
    if(dmic->rx_status == DMIC_RX_COMPLETE){
        return 1;
    }else{
        return 0;
    }
}

int itcs_dmic_stop(dmic_dev_t* dmic){
    dmic_en(dmic,false);
    return 0;
}
