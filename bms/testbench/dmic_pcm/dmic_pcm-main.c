/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     dmic_pcm-main.c
 * @brief    pcm testBench
 * @version  V1.0
 * @date     3.8 2024
 * @name     dmic-main
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <pads.h>
#include <dmic_pcm.h>
#include <cache.h>

/******************************************************************************
 * 1.record audio 1000ms by each channel,stereo,through DMA,and play the pcm data 
 * through iis codec,then play the sound to check whether is acceptable.
 * command: 
 * dmic_pcm -n 0 -m 0 -t 1000 -c 128
 * dmic_pcm -n 1 -m 0 -t 1000 -c 128
 * dmic_pcm -n 2 -m 0 -t 1000 -c 128
 * dmic_pcm -n 3 -m 0 -t 1000 -c 128
 * 
 * multi channels :
 * 
 * dmic_pcm -n 0 -m 1 -t 500 -c 128 -y
*******************************************************************************/

#if defined (CONFIG_TB_RUN_IRAM)
#define DATA_POSITION 0X14200000
#elif defined(CONFIG_TB_RUN_DDR)
#ifdef CONFIG_C920
#define DATA_POSITION 0X120000000
#elif defined(CONFIG_E906)
#define DATA_POSITION 0X45000000
#endif
#elif defined(CONFIG_TB_RUN_DDR1)
#ifdef CONFIG_C920
#define DATA_POSITION 0X520000000
#elif defined(CONFIG_E906)
#define DATA_POSITION 0X45000000
#endif
#endif

static void cdns_dmic_dma_cb(void *arg)
{
	dmic_dev_t* dmic = (dmic_dev_t*)arg;
	//itcs_dmic_stop(dmic);
	dmic->rx_status = DMIC_RX_COMPLETE;
	//itcs_dma_stop(dmic->dma_chan);
	DEBUG_LOG("dma callback\n");
}

static int dmic_dma_configs(dmic_dev_t* dmic, unsigned int* buf, uint32_t len, struct dma_data* dma_data){
	struct dma_chan *dma_chan = NULL;
	struct dma_prep_info prep_info;
	struct dma_slave_config cfg;
	struct dma_info info;
	int ret;

	if (!itcs_is_dma_inited(1))
		itcs_dma_init(1);

	switch (dmic->index) {
	case DMIC_CHAN0:
		info.devname = "dma1";
		info.src_hw_handshake_num = DMAC1_CUART4_TX;
		break;
	case DMIC_CHAN1:
		info.devname = "dma1";
		info.src_hw_handshake_num = DMAC1_CUART4_RX;
		break;
	case DMIC_CHAN2:
		info.devname = "dma1";
		info.src_hw_handshake_num = DMAC1_CUART5_TX;
		break;
	case DMIC_CHAN3:
		info.devname = "dma1";
		info.src_hw_handshake_num = DMAC1_CUART5_RX;
		break;
	}

	dma_cookie_t cookie;

	dma_chan = itcs_dma_request_channel(&info);
	if (!dma_chan){
		DEBUG_LOG("requset channel failed.\n");
		return -1;
	}
	cfg.direction = DMA_DEV_TO_MEM;
	cfg.src_addr = (unsigned long)(dmic->membase + ITCS_DMIC_FIFO_OFFSET);
	cfg.dst_addr = virt_to_phys(buf);
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_16;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_16;

	cfg.device_fc = 0;
	ret = itcs_dma_slave_config(dma_chan, &cfg);
	if (ret < 0){
		DEBUG_LOG("itcs_dma_slave_config failed.\n");
		return -1;
	}

	prep_info.direction = DMA_DEV_TO_MEM;
	prep_info.mode = DMA_SLAVE;
	prep_info.dst = virt_to_phys(buf);
	prep_info.len = len;
	prep_info.callback = cdns_dmic_dma_cb;
	prep_info.callback_param = dmic;
	cookie = itcs_dma_prepare(dma_chan, &prep_info);
	DEBUG_LOG("before cookie.\n");
	if (cookie < 0)
		return -1;
	DEBUG_LOG("after cookie.\n");
	dmic->dma_chan = dma_chan;

	dma_data->cookie = cookie;
	dma_data->prep_info = prep_info;
	dma_data->info = info;
	return 0;
}

static int pcm_multi_chan_test(uint32_t channel, dmic_mode mode, unsigned int ms, uint32_t decimation){
	dmic_dev_t *dmic0, *dmic1, *dmic2, *dmic3;
	uint64_t len0 = 0, len1 = 0, len2 = 0, len3 = 0;
	struct dma_data dma_data0, dma_data1, dma_data2, dma_data3;

	dmic0 = itcs_dmic_init(DMIC_CHAN0, mode, 1, decimation);
	dmic1 = itcs_dmic_init(DMIC_CHAN1, mode, 1, decimation);
	dmic2 = itcs_dmic_init(DMIC_CHAN2, mode, 1, decimation);
	dmic3 = itcs_dmic_init(DMIC_CHAN3, mode, 1, decimation);

	/*calculate bytes to be record*/
	len0 = len1 = len2 = len3 = (uint64_t)dmic0->ouput_clk * ms / 1000 / decimation * 16 / 8 * 2; //Bytes
			     
	void* buf0 = (void*)(unsigned long)(DATA_POSITION);
	memset(buf0, 0, len0);
	DEBUG_LOG("buf0 = %#x\n", buf0);

	void* buf1 = (void*)(unsigned long)(DATA_POSITION + len0);
	memset(buf1, 0, len1);
	DEBUG_LOG("buf1 = %#x\n", buf1);

	void* buf2 = (void*)(unsigned long)(DATA_POSITION + len0 + len1);
	memset(buf2, 0, len2);
	DEBUG_LOG("buf2 = %#x\n", buf2);

	void* buf3 = (void*)(unsigned long)(DATA_POSITION + len0 + len1 + len2);
	memset(buf3, 0, len3);
	DEBUG_LOG("buf3 = %#x\n", buf3);

	dmic_dma_configs(dmic0, buf0, len0, &dma_data0);
	dmic_dma_configs(dmic1, buf1, len1, &dma_data1);
	dmic_dma_configs(dmic2, buf2, len2, &dma_data2);
	dmic_dma_configs(dmic3, buf3, len3, &dma_data3);

	*((uint32_t *)0xc5f01820) = 0xF;//dma handshake distinguish

	itcs_dcache_flush();
	itcs_dma_start(dmic0->dma_chan);
	itcs_dma_start(dmic1->dma_chan);
	itcs_dma_start(dmic2->dma_chan);
	itcs_dma_start(dmic3->dma_chan);

	itcs_dmic_read(dmic0, buf0, len0, false);
	itcs_dmic_read(dmic1, buf1, len1, false);
	itcs_dmic_read(dmic2, buf2, len2, false);
	itcs_dmic_read(dmic3, buf3, len3, false);

	/*circulation wait for complete*/
	char finish_flag = 0;

	while (1) {
		if (itcs_dmic_is_completed(dmic0)) {
			finish_flag |= 1 << 0;
		}
		if (itcs_dmic_is_completed(dmic1)) {
			finish_flag |= 1 << 1;
		}
		if (itcs_dmic_is_completed(dmic2)) {
			finish_flag |= 1 << 2;
		}
		if (itcs_dmic_is_completed(dmic3)) {
			finish_flag |= 1 << 3;
		}

		if(finish_flag == 15)
			break;

		udelay(1);

	}

	itcs_dcache_flush();
	//itcs_dcache_invalid();

	/*result*/
	if (finish_flag == 15) {
		printf("\n");
		printf("Data transmission complete\n");
		printf("Data0 addr is %p,data length is %#x\n", buf0, len0);
		printf("Data1 addr is %p,data length is %#x\n", buf1, len1);
		printf("Data2 addr is %p,data length is %#x\n", buf2, len2);
		printf("Data3 addr is %p,data length is %#x\n", buf3, len3);
		printf("total length = %#x\n", len0 * 4);
	}else{
		printf("Data transmission failed.\n");
		return -1;
	}

	return 0;
}

static int pcm_single_test(uint32_t channel, dmic_mode mode, unsigned int ms, uint32_t decimation){
	int ret = 0;
	uint64_t len = 0;
	struct dma_data dma_data;
	dmic_dev_t *dmic;

	dmic = itcs_dmic_init(channel, mode, 1 ,decimation);

	DEBUG_LOG("dmic->ouput_clk = %u,ms = %u\n", dmic->ouput_clk, ms);

	/*calculate bytes to be record*/
	if(decimation == 128){
		len = (uint64_t)dmic->ouput_clk * ms / 1000 / 128 * 16 / 8 * 2; //Bytes numbr
	}else if(decimation == 64){
		len = (uint64_t)dmic->ouput_clk * ms / 1000 / 128 * 16 / 8 * 2 * 2; //Bytes numbr
	}else if(decimation == 1){
		len = (uint64_t)dmic->ouput_clk * ms / 1000 / 8 * 2 * 2;
	}

	/*16 is fifo bits for one sound channel,keep multiple 16 Bytes*/
	DEBUG_LOG("len = %llu\n", len);//Bytes
	if(len > (uint32_t)0xFFFFFFFF){
		printf("test time too long,data overfolw!\n");
	}

	uint32_t* buf = (void*)(DATA_POSITION);

	memset(buf, 0xA5, len);
	DEBUG_LOG("buf_addr = %#lx\n", buf);

	dmic_dma_configs(dmic, buf, len, &dma_data);
	DEBUG_LOG("cookie = %d\n", dma_data.cookie);
	*((uint32_t *)0xc5f01820) = 0x0F;//dma handshake distinguish set
	itcs_dcache_flush();

	itcs_dma_start(dmic->dma_chan);
	itcs_dmic_read(dmic, buf, len, false);

	while (1) {
		if (itcs_dmic_is_completed(dmic)) {
			break;
		}
		udelay(1);
	}

	/*result*/
	itcs_dcache_flush();
	//itcs_dcache_invalid();
	printf("Data transmission complete\n");

#ifdef CONFIG_C920
	printf("channel %u, data addr is %#llx,data length is %#llx\n", channel, 
			(uint64_t)(buf), len);
#elif defined(CONFIG_E906)
	printf("channel %u, data addr is %#x,data length is %#llx\n", channel, 
			(uint32_t)(buf), len);
#endif
	/*save record data in sd card fatfs_write*/

	return ret;
}

static void dmic_show_usage(void)
{
	printf("Usage: dmic [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-n\t\tchannel\n");
	printf("-m\t\tmode, 0: one channel, 1: multi channel\n");
	printf("-t\t\ttime, unit: ms\n");
	printf("-c\t\tdecimation\n");
	printf("-y\t\tmulti-channel test\n");
}

int pcm_main(int argc, char *argv[])
{
#ifdef CONFIG_COMPILE_ASIC
	//printf("orin 0xd2e00208 = %#X\n", readl(0xd2e00208));
	writel(0x28, 0xd2e00208); //set rgmii2 region voltage 1.8v
	//printf("0xd2e00208 = %#X\n", readl(0xd2e00208));
	//printf("0xc2f02c04 = %#X\n", readl(0xc2f02c04));
#endif
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "n:m:t:c:hy";
	static const struct option long_options[] = {
		{ "help", 0, 0, 'h' }, { 0, 0, 0, 0 },
	};
	uint32_t channel = 4, mode = 6, time = 0, decimation = 128, multi = 0;
	//DEBUG_LOG("dma = %u\n", dma);
	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'n':
			channel = simple_strtoul(optarg, NULL, 10);
			break;
		case 'm':
			mode = simple_strtoul(optarg, NULL, 10);
			break;
		case 't':
			time = simple_strtoul(optarg, NULL, 10);
			break;
		case 'c':
			decimation = simple_strtoul(optarg, NULL, 10);
			break;
		case 'y':
			multi = 1;
			break;
		case 'h':
		default:
			dmic_show_usage();
			ret = -1;
			goto err;
		}
	}

	if(multi)
		ret = pcm_multi_chan_test(channel, mode, time, decimation);
	else
		ret = pcm_single_test(channel, mode, time, decimation);

	if (optind == 1) {
		dmic_show_usage();
		ret = -1;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

void dmic_pcm_init(void)
{
	register_testbench("dmic_pcm", pcm_main, NULL);
}

testbench_init(dmic_pcm_init);