/**
 * @file      pufs_dma_internal.c
 * @brief     PUFsecurity DMA API internal test cases
 * @copyright 2020 PUFsecurity
 */
/* THIS SOFTWARE IS SUPPLIED BY PUFSECURITY ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. TO THE FULLEST
 * EXTENT ALLOWED BY LAW, PUFSECURITY'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES,
 * IF ANY, THAT YOU HAVE PAID DIRECTLY TO PUFSECURITY FOR THIS SOFTWARE.
 */

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fcntl.h>
//#include <unistd.h>

#include "pufs_internal.h"
#include "pufs_dma_internal.h"
#include "pufs_dma_regs.h"

/*****************************************************************************
 * Static variables
 ****************************************************************************/
#define RBSIZE 0x4000000
static uint8_t randbuf[RBSIZE];

/*****************************************************************************
 * Internal test functions
 ****************************************************************************/
void pufs_dma_test(void)
{
    const uint32_t DMA_TEST_MAXSIZE = 1024;
    uint8_t in[DMA_TEST_MAXSIZE];
    uint8_t out[DMA_TEST_MAXSIZE];
    uint8_t zero[DMA_TEST_MAXSIZE];
    uint32_t val32;

    // Step 0: prepare zero array
    memset(zero, 0, DMA_TEST_MAXSIZE);
    memset(in, 0xa5, DMA_TEST_MAXSIZE);

    // Step 1: put data into dma read buffer
    dma_write_rwcfg(NULL, in, DMA_TEST_MAXSIZE);
#ifndef DMADIRECT
    uint32_t dma_cfg_rd = pufs_dma.write_addr;
    uint32_t dma_cfg_wr = pufs_dma.read_addr;
#else
    uint32_t dma_cfg_rd = (uint32_t)in;
    uint32_t dma_cfg_wr = (uint32_t)out;
#endif /* DMADIRECT */

    LOG_INFO("DMA test: ");
    // Step 2: Testing
    for (uint32_t i=0; i<4; i++) // for unaligned DMA R/W address
    for (uint32_t j=1; i+j < DMA_TEST_MAXSIZE; j++) // for data of different length
    {
        uint32_t idx;
        // Step 2.1: clear DMA write space
        memset(out, 0, DMA_TEST_MAXSIZE);
        clear_dma_read(DMA_TEST_MAXSIZE);
        dma_read_output(out, DMA_TEST_MAXSIZE);
        for (idx=0; idx<DMA_TEST_MAXSIZE; idx++)
            if (out[idx] != 0)
            {
                LOG_ERROR("%s", "clear DMA failed!");
                return;
            }
        // Step 2.2: Configure DMA
        val32 = 0x04;
        dma_write_config_0(false, false, true);
        val32 = dma_cfg_rd + i;
        pufs_dma.regs->dsc_cfg_0 = val32;
        val32 = dma_cfg_wr + i;
        pufs_dma.regs->dsc_cfg_1 = val32;
        val32 = j;
        pufs_dma.regs->dsc_cfg_2 = val32;
        val32 = 0x1<<29 | 0x1<<28 | 0xa<<24;
        pufs_dma.regs->dsc_cfg_4 = val32;
        val32 = 0xf<<4; // no_crypto selection
        pufs_dma.regs->key_cfg_0 = val32;

        dma_write_start();
        // Step 2.3: Wait for DMA done
        while(dma_check_busy_status(&val32));

        if (val32 != 0)
        {
            LOG_ERROR("DMA status 0: 0x%08lx\n", val32);
            return;
        }

        // Step 3.4: Read and check data written by DMA
        dma_read_output(out, DMA_TEST_MAXSIZE);
        
        for (idx=0; idx<i; idx++)
            if (out[idx] != 0)
                LOG_ERROR("DMA write before aligned error(%lu)!", idx);
        for (;idx< i+j; idx++)
            if (out[idx] != in[idx])
                LOG_ERROR("DMA write error(%lu)!", idx);
        for (;idx< DMA_TEST_MAXSIZE; idx++)
            if (out[idx] != 0)
                LOG_ERROR("DMA write before aligned error(%lu)!", idx);
    }
    LOG_INFO("done.\n");
}
void pufs_dump_rand_dma_test(bool entropy)
{
    char fname[12];
    LOG_INFO("Dump random number via DMA test: \n");

    for (int i = 0; i < 100; i++)
    {
        FILE* fp;
        size_t wlen;

        if (entropy)
            snprintf(fname, 12, "ent%02d.bin", i);
        else
            snprintf(fname, 12, "trng%02d.bin", i);
        if ((fp = fopen(fname, "w")) == NULL)
        {
            LOG_INFO("Cannot open file %s!\n", fname);
            return;
        }

        reg_sw_reset_write();
        if (pufs_dump_rand_dma(randbuf, RBSIZE, entropy) != SUCCESS)
        {
            LOG_INFO("!\n");
            return;
        }

        if ((wlen = fwrite(randbuf, 1, RBSIZE, fp)) != RBSIZE)
            fprintf(fp, "Write to %s is not completed!\n", fname);
        else
            fprintf(fp, ".");
        fclose(fp);
    }

    
}
