/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     dmic-main.c
 * @brief    dmic testBench
 * @version  V1.0
 * @date     12.29 2023

 * @name     dmic-main
 * @author   lamar.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <pads.h>
#include <dmic.h>
#include <cache.h>

#define RTL_TEST_LEN 48

#ifdef CONFIG_COMPILE_RTL
static int dmic_test(uint32_t channel, dmic_mode mode, unsigned int ms){
	uint32_t input_data[RTL_TEST_LEN] = { 0 };//from TB

	for (int i =0 ;i < RTL_TEST_LEN; i++){
		uint32_t a = i + 1;
		input_data[i] = a | (a << 8) | (a << 16) | (a << 24);
	}
	//char finish_flag = 0;
	//uint32_t len = 0;
	dmic_dev_t *dmic;
	dmic = itcs_dmic_init(channel, mode, 0);

	uint32_t* buf = malloc(sizeof(unsigned int) * RTL_TEST_LEN);
	memset(buf, 0, RTL_TEST_LEN);

	itcs_dmic_read(dmic, buf, RTL_TEST_LEN, true);

	/*result*/
	if(!memcmp(buf, input_data, RTL_TEST_LEN)){
		printf("DMIC%u tansmission is correct.\n", channel);
		printf("Test RTL DMIC Pass.\n");
	}else{
		printf("DMIC%u tansmission is incorrect.\n", channel);
		printf("Test RTL DMIC Failed.\n");
		return -1;
	}
	return 0;
}
#endif

#ifdef CONFIG_COMPILE_FPGA
/*each dmic transfer directly based on int*/
static int dmic_test(uint32_t channel, dmic_mode mode, unsigned int ms){
	//uint8_t finish_flag = 0;
	int ret = 0;
	uint64_t len = 0;

	dmic_dev_t *dmic;

	dmic = itcs_dmic_init(channel, mode, 0);

	DEBUG_LOG("dmic->ouput_clk = %u,ms = %u\n", dmic->ouput_clk, ms);

	/*len is the bytes requested, first 4 is from bit to byte because of double
	 edge, 16 is fifo burst depth, 4 is fifo width byte*/
	//len = (uint64_t)dmic->ouput_clk * ms / 1000 / 4 / (16 * 4) * (16 * 4); 
	len = (uint64_t)dmic->ouput_clk * ms / 1000 / 4 / 4 / 16 * 16; 
	DEBUG_LOG("len = %llu\n", len);
	uint32_t* buf = malloc(sizeof(unsigned int) * len);
	if(buf == NULL){
		printf("aplay buf failed\n");
		return -1;
	}
    memset(buf, 0, len * sizeof(unsigned int));

	itcs_dmic_read(dmic, buf, len, true);/*block read*/

	/*result*/
	printf("Data transmission complete\n");
#ifdef CONFIG_C920
	printf("channel %u, data addr is %#llx,data length is %#llx\n", channel, 
				(uint64_t)(buf), len * 4);	
#elif defined(CONFIG_E906)
	printf("channel %u, data addr is %#x,data length is %#llx\n", channel, 
				(uint32_t)(buf), len * 4);
#endif
	while(1);
	return ret;
}
#endif

static void cdns_dmic_dma_cb(void *arg)
{
    dmic_dev_t* dmic = (dmic_dev_t*)arg;
	itcs_dmic_stop(dmic);
	dmic->rx_status = DMIC_RX_COMPLETE;
    itcs_dma_stop(dmic->dma_chan);
	DEBUG_LOG("dma callback\n");
}

static int dmic_dma_configs(dmic_dev_t* dmic, unsigned int* buf, 
							uint32_t len, struct dma_data* dma_data){
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
#ifdef CONFIG_COMPILE_FPGA
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_1;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_1;
#elif defined(CONFIG_COMPILE_RTL)
	cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_1;
	cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_1;
#endif
	cfg.device_fc = 0;
	ret = itcs_dma_slave_config(dma_chan, &cfg);
	if (ret < 0)
		return -1;

	prep_info.direction = DMA_DEV_TO_MEM;
	prep_info.mode = DMA_SLAVE;
	prep_info.dst = virt_to_phys(buf);
	prep_info.len = len;
	prep_info.callback = cdns_dmic_dma_cb;
	prep_info.callback_param = dmic;
	cookie = itcs_dma_prepare(dma_chan, &prep_info);
	if (cookie < 0)
		return -1;
	dmic->dma_chan = dma_chan;

	dma_data->cookie = cookie;
	dma_data->prep_info = prep_info;
	dma_data->info = info;
	return 0;
}

#ifdef CONFIG_COMPILE_RTL
static int dmic_dma_single_test(uint32_t channel, dmic_mode mode, 
								unsigned int ms){
	int ret = 0;
	//uint64_t len = 0;
	struct dma_data dma_data;
	dmic_dev_t *dmic;

	uint32_t input_data[RTL_TEST_LEN] = { 0 };//from TB
	for (int i = 0 ;i < RTL_TEST_LEN; i++){
		uint32_t a = i + 1;
		input_data[i] = a | (a << 8) | (a << 16) | (a << 24);
	}

	dmic = itcs_dmic_init(channel, mode, 1);

	/*16 is fifo bits for one sound channel,keep multiple 16 Bytes*/
	uint32_t* buf = malloc(sizeof(unsigned int) * RTL_TEST_LEN);
    memset(buf, 0, RTL_TEST_LEN);
	DEBUG_LOG("buf = %#x\n", buf);

	dmic_dma_configs(dmic, buf, RTL_TEST_LEN, &dma_data);
	DEBUG_LOG("cookie = %d\n", dma_data.cookie);

	*((uint32_t *)0xc5f01820) = 0xF;//dma handshake distinguish
	itcs_dcache_flush();
	itcs_dma_start(dmic->dma_chan);
	itcs_dmic_read(dmic, buf, RTL_TEST_LEN, false);
	while (1) {
		if (itcs_dmic_is_completed(dmic)) {
			break;
		}
		udelay(1);
	}
	/*result*/
	itcs_dcache_flush();
	if(!memcmp(buf, input_data, RTL_TEST_LEN)){
		printf("DMIC%u tansmission is correct.\n", channel);
		printf("Test RTL DMA DMIC Pass.\n");
	}else{
		printf("DMIC%u tansmission is incorrect.\n", channel);
		printf("Test RTL DMA DMIC Failed.\n");
		return -1;
	}
	return ret;
}

static int dmic_dma_test(dmic_mode mode,unsigned int ms){
	dmic_dev_t *dmic0, *dmic1, *dmic2, *dmic3;
	struct dma_data dma_data0, dma_data1, dma_data2, dma_data3;

	uint32_t input_data[RTL_TEST_LEN] = { 0 };//from TB

	for (int i =0 ;i < RTL_TEST_LEN; i++){
		uint32_t a = i + 1;
		input_data[i] = a | (a << 8) | (a << 16) | (a << 24);
	}

	dmic0 = itcs_dmic_init(DMIC_CHAN0, mode, 1);
	dmic1 = itcs_dmic_init(DMIC_CHAN1, mode, 1);
	dmic2 = itcs_dmic_init(DMIC_CHAN2, mode, 1);
	dmic3 = itcs_dmic_init(DMIC_CHAN3, mode, 1);

	uint32_t* buf0 = malloc(sizeof(unsigned int) * RTL_TEST_LEN);
	uint32_t* buf1 = malloc(sizeof(unsigned int) * RTL_TEST_LEN);
	uint32_t* buf2 = malloc(sizeof(unsigned int) * RTL_TEST_LEN);
	uint32_t* buf3 = malloc(sizeof(unsigned int) * RTL_TEST_LEN);

	dmic_dma_configs(dmic0, buf0, RTL_TEST_LEN, &dma_data0);
	dmic_dma_configs(dmic1, buf1, RTL_TEST_LEN, &dma_data1);
	dmic_dma_configs(dmic2, buf2, RTL_TEST_LEN, &dma_data2);
	dmic_dma_configs(dmic3, buf3, RTL_TEST_LEN, &dma_data3);
	*((uint32_t *)0xc5f01820) = 0x0F; //dma handshake distinguish

	itcs_dcache_flush();
	itcs_dma_start(dmic0->dma_chan);
	itcs_dma_start(dmic1->dma_chan);
	itcs_dma_start(dmic2->dma_chan);
	itcs_dma_start(dmic3->dma_chan);

	itcs_dmic_sync(dmic0);
	itcs_dmic_sync(dmic1);
	itcs_dmic_sync(dmic2);
	itcs_dmic_sync(dmic3);

	itcs_dmic_read(dmic0, buf0, RTL_TEST_LEN, false);
	itcs_dmic_read(dmic1, buf1, RTL_TEST_LEN, false);
	itcs_dmic_read(dmic2, buf2, RTL_TEST_LEN, false);
	itcs_dmic_read(dmic3, buf3, RTL_TEST_LEN, false);
	
	/*circulation wait for complete*/
	//uint64_t overtime = 0;
	uint8_t finish_flag = 0;
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
		if(finish_flag == 15){
			break;
		}else {
			udelay(1);
		}
	}
	itcs_dcache_flush();
		/*result*/
	if (finish_flag == 15) {
		/*compare data*/
		if(!memcmp(buf0, input_data, RTL_TEST_LEN)){
			printf("DMIC0 tansmission is correct.\n");
		}else{
			printf("DMIC0 tansmission is incorrect.\n");
			printf("Test RTL DMA DMIC Failed.\n");
			return -1;
		}
		if(!memcmp(buf1, input_data, RTL_TEST_LEN)){
			printf("DMIC1 tansmission is correct.\n");
		}else{
			printf("DMIC1 tansmission is incorrect.\n");
			printf("Test RTL DMA DMIC Failed.\n");
			return -1;
		}
		if(!memcmp(buf2, input_data, RTL_TEST_LEN)){
			printf("DMIC2 tansmission is correct.\n");
		}else{
			printf("DMIC2 tansmission is incorrect.\n");
			printf("Test RTL DMA DMIC Failed.\n");
			return -1;
		}
		if(!memcmp(buf3, input_data, RTL_TEST_LEN)){
			printf("DMIC3 tansmission is correct.\n");
		}else{
			printf("DMIC3 tansmission is incorrect.\n");
			printf("Test RTL DMA DMIC Failed.\n");
			return -1;
		}
	}else{
		printf("Data transmission failed.\n");
		return -1;
	}

	printf("Test RTL DMA DMIC Pass.\n");

	/*
	itcs_dma_release_channel(dmic0->dma_chan);
	itcs_dma_release_channel(dmic1->dma_chan);
	itcs_dma_release_channel(dmic2->dma_chan);
	itcs_dma_release_channel(dmic3->dma_chan);
	*/
	return 0;
}
#endif


#ifdef CONFIG_COMPILE_FPGA
/*dmic transfer based on DMA*/
static int dmic_dma_single_test(uint32_t channel, dmic_mode mode, 
								unsigned int ms){
	int ret = 0;
	uint64_t len = 0;
	struct dma_data dma_data;
	dmic_dev_t *dmic;

	dmic = itcs_dmic_init(channel, mode, 1);

	DEBUG_LOG("dmic->ouput_clk = %u,ms = %u\n", dmic->ouput_clk, ms);
	len = (uint64_t)dmic->ouput_clk * ms / 1000 / 4 / 16 * 16; 
	/*16 is fifo bits for one sound channel,keep multiple 16 Bytes*/
	DEBUG_LOG("len = %llu\n", len);
	if(len > (uint32_t)0xFFFFFFFF){
		printf("test time too long,data overfolw!\n");
	}
	uint32_t* buf = malloc(sizeof(unsigned int) * len);
    memset(buf, 0, len);
	DEBUG_LOG("buf = %#x\n", buf);

	dmic_dma_configs(dmic, buf, len, &dma_data);
	DEBUG_LOG("cookie = %d\n", dma_data.cookie);

	*((uint32_t *)0xc5f01820) = 0x0F;//dma handshake distinguish
	itcs_dcache_flush();
	/*
	uint32_t temp = readl(dmic->membase + ITCS_DMIC_CTL_OFFSET);
    temp &= ~(ITCS_PDM_CLK_EN | ITCS_DMIC_ON);
    writel(temp, dmic->membase + ITCS_DMIC_CTL_OFFSET);
	*/
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
	printf("Data transmission complete\n");
#ifdef CONFIG_C920
	printf("channel %u, data addr is %#llx,data length is %#llx\n", channel, 
			(uint64_t)(buf), len);
#elif defined(CONFIG_E906)
	printf("channel %u, data addr is %#x,data length is %#llx\n", channel, 
			(uint32_t)(buf), len);
#endif
	while(1);
	return ret;
}

static int dmic_dma_test(dmic_mode mode,unsigned int ms){
	dmic_dev_t *dmic0, *dmic1, *dmic2, *dmic3;
	uint64_t len0 = 0, len1 = 0, len2 = 0, len3 = 0;
	struct dma_data dma_data0, dma_data1, dma_data2, dma_data3;
	int ret = 0;

	dmic0 = itcs_dmic_init(DMIC_CHAN0, mode, 1);
	dmic1 = itcs_dmic_init(DMIC_CHAN1, mode, 1);
	dmic2 = itcs_dmic_init(DMIC_CHAN2, mode, 1);
	dmic3 = itcs_dmic_init(DMIC_CHAN3, mode, 1);

	len0 = (uint64_t)dmic0->ouput_clk * ms / 1000 / 4 / 4 / 16 * 16; 
	/*32 is fifo bits,keep multiple 16 Bytes*/
	DEBUG_LOG("len = %llu\n", len0);
	len1 = (uint64_t)dmic1->ouput_clk * ms / 1000 / 4 / 4 / 16 * 16;
	len2 = (uint64_t)dmic2->ouput_clk * ms / 1000 / 4 / 4 / 16 * 16;
	len3 = (uint64_t)dmic3->ouput_clk * ms / 1000 / 4 / 4 / 16 * 16;
	uint32_t* buf0 = malloc(sizeof(unsigned int) * len0);
	memset(buf0, 0, sizeof(unsigned int) * len0);
	DEBUG_LOG("buf0 = %#x\n", buf0);
	uint32_t* buf1 = malloc(sizeof(unsigned int) * len1);
	memset(buf1, 0, sizeof(unsigned int) * len1);
	DEBUG_LOG("buf1 = %#x\n", buf1);
	uint32_t* buf2 = malloc(sizeof(unsigned int) * len2);
	memset(buf2, 0, sizeof(unsigned int) * len2);
	DEBUG_LOG("buf2 = %#x\n", buf2);
	uint32_t* buf3 = malloc(sizeof(unsigned int) * len3);
	memset(buf3, 0, sizeof(unsigned int) * len3);
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
	//uint64_t overtime = 0;
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
		if(finish_flag == 15){
			break;
		}else {
			udelay(1);
		}
		/*
		overtime++;
		if(overtime > 3000){
			printf("overtime!\n");
			break;
		}
		*/
	}

	itcs_dcache_flush();
	//while(1);

	/*result*/
	if (finish_flag == 15) {
		printf("\n");
		printf("Data transmission complete\n");
		printf("Data0 addr is %p,data length is %#x\n", buf0, len0);
		printf("Data1 addr is %p,data length is %#x\n", buf1, len1);
		printf("Data2 addr is %p,data length is %#x\n", buf2, len2);
		printf("Data3 addr is %p,data length is %#x\n", buf3, len3);
	}else{
		printf("Data transmission failed.\n");
	}
	/*
	itcs_dma_release_channel(dmic0->dma_chan);
	itcs_dma_release_channel(dmic1->dma_chan);
	itcs_dma_release_channel(dmic2->dma_chan);
	itcs_dma_release_channel(dmic3->dma_chan);
	*/
	return ret;
}
#endif

static void dmic_show_usage(void)
{
	printf("Usage: dmic [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-n\t\tchannel\n");
	printf("-m\t\tmode\n");
	printf("-t\t\ttime\n");
	printf("-d\t\tdma mode\n");
}

int dmic_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0 ,single = 0;
	static const char short_options[] = "n:m:t:dsh";
	static const struct option long_options[] = {
		{ "help", 0, 0, 'h' }, { 0, 0, 0, 0 },
	};
	uint32_t channel = 4, mode = 0, time = 0, dma = 0;
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
		case 'd':
			dma = 1;
			break;
		case 's':
			single = 1;
			break;
		case 'h':
		default:
			dmic_show_usage();
			ret = -1;
			goto err;
		}
	}
	if(dma == 0)
		ret = dmic_test(channel, mode, time);
	else if(single == 1)
		ret = dmic_dma_single_test(channel, mode, time);
	else
		ret = dmic_dma_test(mode, time);

	if (optind == 1) {
		dmic_show_usage();
		ret = -1;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

void dmic_init(void)
{
	register_testbench("dmic", dmic_main, NULL);
}

testbench_init(dmic_init);
