#include <irq.h>
#include <pads.h>

#define SPI_MODE_SLAVE 1

#define C_SPI1_BASE_ADDR  (0xc2300000UL)
#define S_SPI0_BASE_ADDR  (0xd2300000UL)

//#define SPI_CLK 5577000
#define SPI_CLK 2000000
#define SPI_GET_BASE(port) ( port>0 ? (C_SPI1_BASE_ADDR+((port-1)*0x1000)) : S_SPI0_BASE_ADDR )


#define ARM_SPI_FIFO_DEPTH 64

#define ARM_SPI_CR0        0x00
#define ARM_SPI_CR1        0x04
#define ARM_SPI_DR         0x08
#define ARM_SPI_SR         0x0C

#define ARM_SPI_CPSR       0x10
#define ARM_SPI_IMSC       0x14
#define ARM_SPI_RIS        0x18
#define ARM_SPI_MIS        0x1c

#define SPI_TFIFO_HF_EMPTY (0x8)
#define SPI_RFIFO_HF_FULL  (0x4)
#define SPI_RFIFO_TIMEOUT  (0x2)
#define SPI_RFIFO_OVERRUN  (0x1)

#define SPI_TFIFO_EMPTY  (0x1)
#define SPI_TFIFO_NFULL  (0x2)
#define SPI_RFIFO_NEMPTY (0x4)
#define SPI_RFIFO_FULL   (0x8)
#define SPI_BUSY         (0x10)


static int check_timeout(uint64_t base_tick, int timeout_ms){
  extern unsigned long g_ticks_per_us;
  uint64_t t = get_ticks();
  uint64_t ticks_per_ms =  g_ticks_per_us * 1000;
  if( (t-base_tick) >= (ticks_per_ms * timeout_ms)){
    return 1;
  }
  return 0;
}

// static int arm_spi_irq_handler(int irq, void *arg)
// {
//     uint32_t base = SPI_GET_BASE(0);
//     uint32_t stat = readl(base + ARM_SPI_MIS);
//     printf("%s@%d, stat=%x\n", __func__, __LINE__, stat);

//     writel(stat, base + ARM_SPI_IMSC);
//     return 0;
// }

static int spi_init_ip(int port, int pclk, uint32_t speed_hz){
    int	i, j;
    uint32_t base = SPI_GET_BASE(port);

	for(i = 2; i < 255; i += 2)
	  for(j = 0; j < 256; j++)
		if(pclk / (i * (j + 1)) <= speed_hz)
		  goto calc_finish;

calc_finish:
	if(i >= 255 || j >= 256) {
		printf("spi: calc clock failed(%d, %d), use default.\n", i, j);
		i = 2; j = 39;
	}

	printf("PCLK: %d, PS: %d, SCR: %d, Fout: %d\n", 
				pclk, i, j, pclk / (i * (j + 1)));

    //disable spi
	writel(0, base+ARM_SPI_CR1);
    //disable interrupt
	writel(0, base+ARM_SPI_IMSC);
    //config divisor
	writel(i, base+ARM_SPI_CPSR);
    //config mode
	writel((j << 8) | (3 << 6) | (0 << 4) | (7 << 0), base+ARM_SPI_CR0);
    //config slave mode
#ifdef SPI_MODE_SLAVE
    writel((0 << 3) | (1 << 2) | (1 << 1) | (0 << 0), base+ARM_SPI_CR1);
#else
    writel((1 << 3) | (0 << 2) | (1 << 1) | (0 << 0), base+ARM_SPI_CR1);
#endif
    // config FIFO level
	writel(0x2020, base+0x28);

    // writel(0x0f, base+ARM_SPI_IMSC);

    // request_irq(S_SPI0_IRQn, arm_spi_irq_handler, "spi0-irq", NULL);

	return 0;
}

// static void spi_fifo_clear_old(int port)
// {
//     uint32_t base = SPI_GET_BASE(port);
//     while(readl(base+ARM_SPI_SR) & SPI_BUSY);
// 	while(readl(base+ARM_SPI_SR) & SPI_RFIFO_NEMPTY) {
// 		readl(base+ARM_SPI_DR);
// 	}
// }
static void spi_fifo_clear_atstart(int port)
{
    uint32_t base = SPI_GET_BASE(port);
    if(!(readl(base+ARM_SPI_SR) & SPI_RFIFO_NEMPTY))//rx empty,retrun
    {
        return;
    }

	if(readl(base+ARM_SPI_SR) & SPI_BUSY)   //busy,return
        return;
	while(readl(base+ARM_SPI_SR) & SPI_RFIFO_NEMPTY) {
		readl(base+ARM_SPI_DR);
	}
}
static void spi_fifo_clear_atend(int port)
{
    uint32_t base = SPI_GET_BASE(port);
    if(!(readl(base+ARM_SPI_SR) & SPI_RFIFO_NEMPTY))//rx empty,return
    {
        return;
    }
	while(readl(base+ARM_SPI_SR) & SPI_BUSY);//wait idel
	while(readl(base+ARM_SPI_SR) & SPI_RFIFO_NEMPTY) {
		readl(base+ARM_SPI_DR);
	}
}

/****************************************************************************
@description: Resets the SPI.
@param: 
    port: Port number, 0~3.
@retval: Reset status, 0-successful otherwise-failed.
*****************************************************************************/
int spi_reset(uint8_t port){
    domain_t domain = CPU;
    char name[8] = {0};
    uint32_t base = SPI_GET_BASE(port);

    if (port == 0)
      domain = SAP;

    snprintf(name, sizeof(name), "spi%u", port);

    writel(0, base+ARM_SPI_CR1);
    writel(0, base+ARM_SPI_CR0);
	writel(0, base+ARM_SPI_IMSC);
	writel(0, base+ARM_SPI_CPSR);

    itcs_module_reset(domain, name);    
    return 0;
}

/****************************************************************************
@description: Initializes the spi.
@param: 
    port: Port number, 0~3.
@retval: Initialization status, 0-successful otherwise-failed.
*****************************************************************************/
int spi_init(uint8_t port){
  domain_t domain = CPU;
  char name[8] = {0};
  int pclk = 0;

  if (port == 0)
    domain = SAP;

  snprintf(name, sizeof(name), "spi%u", port);

  itcs_module_enable(domain, name);
  itcs_module_set_pads(domain, FPGA_BIT_V_EMMC, name);

  pclk = itcs_module_get_clock(domain, "spi");
  spi_init_ip(port, pclk, SPI_CLK);
  return 0;
}



/****************************************************************************
@description: read&write data to spi in block mode with timeout specified.
@param: 
    port: Port number, 0~3.
    rbuf: Buffer pointer to store the data that will be read.
    wbuf: Buffer pointer to store the data that will be write.
    len: Length of the data that will be read&write.
    count: Counts of bytes that will be read&write.
    timeout_ms: Timeout in milliseconds.
@retval: Write status, 0-successful otherwise-failed.
*****************************************************************************/
static unsigned int spi_rx_full_times = 0;

int spi_read_write(uint8_t port, void* rbuf, void* wbuf, int len,  int *count, int timeout_ms){
    uint64_t t = get_ticks();
    uint32_t ris;
    int wc=0;
		//int rc = 0;
    *count = 0;
    uint8_t *tx = (uint8_t *)wbuf;
    uint8_t *rx = (uint8_t *)rbuf;
    //uint8_t *pr = (uint8_t *)rbuf;
    uint32_t base = SPI_GET_BASE(port);
    uint32_t dr = base + ARM_SPI_DR;
    uint32_t risr = base + ARM_SPI_RIS;
    uint32_t icr = base + 0x20;
    int half_read_count = 32;

    // if (rbuf != NULL)
    // {
    //     printf("======wait clear\n");
    // }
    
    //spi_fifo_clear(port);
    //spi_fifo_clear_atstart(port);
    spi_rx_full_times = 0;
    if(tx != NULL){
        while( (readl(base + ARM_SPI_SR) & SPI_TFIFO_NFULL) &&  (wc < len) ){
            writel(*tx, dr);
            tx++;
            wc++;
        }
        
    }

    // if (rbuf != NULL)
    // {
    //     printf("======wait read\n");
    // }

    while(*count < len){
        ris = readl(risr); 
        if(ris & SPI_RFIFO_HF_FULL) {
            if(ris & SPI_RFIFO_OVERRUN){
                writel(1,icr);
                // printf("recv overrun, count=%d\n",*count);
            }
            half_read_count = 32;
            while(half_read_count--){
                if(rx != NULL){
                    *rx = readl(dr); rx++;
                }else{
                    readl(dr);
                }
                if((tx != NULL) && (wc < len)){
                    writel(*tx, dr); tx++;
                    wc++;
                }
                (*count)++;
                
            }
            t = get_ticks();
        } else if(ris & SPI_RFIFO_TIMEOUT){
            printf("spi timeout read, count=%d\n",*count);
            writel(3,icr);
            while(readl(base + ARM_SPI_SR) & SPI_RFIFO_NEMPTY){
                if(rx != NULL){
                    *rx = readl(dr); rx++;
                }else{
                    readl(dr);
                }
                if((tx != NULL) && (wc < len)){
                    writel(*tx, dr); tx++;
                    wc++;
                }
                (*count)++;
            }
        }
        #if 0
        sr =readl(ssr); 
        if(sr & SPI_RFIFO_NEMPTY) {
            if(sr & SPI_RFIFO_FULL){
            	printf("spi_rx_full_times = %d\n",spi_rx_full_times);
                spi_rx_full_times++;
            }
            if(rx != NULL){
                *rx = readl(dr);
                rx++;
                rc++;
                
            }else{
                readl(dr);
            }
            if((tx != NULL) && (wc < len)){
                writel(*tx, dr);
                tx++;
                wc++;
            }
            
            (*count)++;
            t = get_ticks();
        }
        #endif
#if 1
        if (check_timeout(t, timeout_ms)){
            // printf("timeout, count=%d, len=%d\n", *count, len);
            return 1;
        }
#endif

    }

#if 0
    if(pr[50] == 0x41) {
        printf("5041\n");
    }else if(pr[50] == 0x45) {
        printf("5045\n");
    }
#endif 
    spi_fifo_clear_atend(port);
    return 0;
}

int spi_rx_halfplex(uint8_t port, void* rbuf, void* wbuf, int len,  int *count, int timeout_ms)
{
    uint64_t t = get_ticks();
    uint32_t sr;
    uint8_t *rx = (uint8_t *)rbuf;
    uint32_t base = SPI_GET_BASE(port);

    *count = 0;
    if (!rbuf || !len)
        return 0;

    spi_fifo_clear_atstart(port);

    while (*count < len) {
        sr = readl(base + ARM_SPI_SR); 
        if (sr & SPI_RFIFO_NEMPTY) {
            if (sr & SPI_RFIFO_FULL) {
            	printf("spi_rx_full_times = %d\n", spi_rx_full_times);
                spi_rx_full_times++;
            }
            *rx = readl(base + ARM_SPI_DR);
            rx++;
            (*count)++;
        }

        if (check_timeout(t, timeout_ms)) {
            // printf("timeout, count=%d, len=%d\n", *count, len);
            return -1;
        }
    }

    spi_fifo_clear_atend(port);
    return 0;
}

int spi_tx_halfplex(uint8_t port, void* rbuf, void* wbuf, int len,  int *count, int timeout_ms)
{
    uint64_t t = get_ticks();
    uint8_t *tx = (uint8_t *)wbuf;
    uint32_t base = SPI_GET_BASE(port);

    *count = 0;
    if (!wbuf || !len)
        return 0;

    spi_fifo_clear_atstart(port);

    while (*count < len) {
        if (readl(base + ARM_SPI_SR) & SPI_TFIFO_NFULL) {
            writel(*tx, base + ARM_SPI_DR);
            tx++;
            (*count)++;
        }

        if (check_timeout(t, timeout_ms)) {
            // printf("timeout, count=%d, len=%d\n", *count, len);
            return -1;
        }

    }
    printf("count=%d, len=%d\n", *count, len);

    spi_fifo_clear_atend(port);
    return 0;
}




