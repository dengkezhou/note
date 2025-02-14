/**
 * @file      pufs_dma_test.c
 * @brief     PUFsecurity DMA test cases
 * @copyright 2021 PUFsecurity
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
#include <malloc.h>
#include <string.h>
#include "pufs_dma.h"
#include "pufs_pal.h"
#include "pufs_rt.h"
#include "pufs_dma_test.h"
#include "pufs_test_common.h"
#include "pufs_memory_map.h"
#include "pufs_log.h"

/*****************************************************************************
 * Static functions
 ****************************************************************************/
static pufs_status_t pufs_dma_entropy_read(bool entropy)
{
    pufs_status_t check = SUCCESS;
    uint8_t buff[16] __attribute__((aligned(64)));
    if ((check = pufs_dump_rand_dma(buff, 16, entropy)) != SUCCESS)
    {
        LOG_ERROR("Failed to read dma %s", entropy ? "entropy" : "random");
        goto cleanup;
    }

    print_buffer(0, buff, 1, 16, 16);

    check = E_VERFAIL;
    for (uint32_t i = 0; i < 16; i++)
    {
        if ((buff[i] != 0x0) && (buff[i] != 0xFF))
            check = SUCCESS;
    }
cleanup:
    return check;
}

pufs_status_t init_dma_factory_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_rt_factory_test()) == SUCCESS)
        check = pufs_dma_module_init(DMA_ADDR_OFFSET);
    return check;
}

pufs_status_t init_dma_user_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_rt_user_test()) == SUCCESS)
        check = pufs_dma_module_init(DMA_ADDR_OFFSET);
    return check;
}
/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_dma_fix_addr_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    uint32_t desc_len = 0, msg_len;
    // FIXME: msg must be 32bytes until issue on AXI FIFO is resolved
    const char *msg = "this_is_test_for_dma_and_is_32B.";
    pufs_dma_sg_desc_st descs[2], fix_write_desc;
    void *in = NULL, *out = NULL;

    msg_len = strlen(msg);
    out = malloc(msg_len);
    in = malloc(msg_len);
    memcpy(in, msg, msg_len);

    form_sg_descs(descs, &desc_len, 2, out, in, msg_len, 32, true);
    descs[0].attr.fix_read_addr = true;
    descs[0].read_addr = PUFS_TEST_FIFO_ADDRESS;

    if ((check = pufs_dma_read_write_sg(&descs[0])) != SUCCESS)
        goto cleanup;
    
    fix_write_desc.length = msg_len;
    fix_write_desc.read_addr = PUFS_TEST_READ_ADDRESS;
    fix_write_desc.write_addr =  PUFS_TEST_FIFO_ADDRESS;
    fix_write_desc.attr.fix_write_addr = true;
    fix_write_desc.attr.fix_read_addr = false;
    fix_write_desc.attr.read_protect = 0;
    fix_write_desc.attr.write_protect = 0;

    check = pufs_dma_read_write_sg(&fix_write_desc);

cleanup:
    free(in);
    free(out);
    return check;
}
//Fixme: Untest
pufs_status_t pufs_dma_fix_read_write_addr_test(void)
{
    pufs_status_t check;
    uint8_t out[16];
    pufs_dma_dsc_attr_st attr = {
        .fix_read_addr = true,
        .fix_write_addr = false,
        .read_protect = 0x0,
        .write_protect = 0x0,
    };
    const uint32_t length = 15;
    const char *data = "\x11\x22\x33\x44\x55\x66\x77\x88\x99\xaa\xbb\xcc\xdd\xee\xff";

    // only test the last 4 bytes
    if ((check = pufs_dma_read_write(out, 4, (uint8_t *)data, length, &attr)) != SUCCESS)
    {
        printf("failed to set fix read address\n");
        return check;
    }
    // we fix the read address, so DMA always write the output to the same address
    if (memcmp(out, "\xdd\xee\xff", 3) != 0)
    {
        printf("the result is not matched\n");
        return E_VERFAIL;
    }

    attr.fix_read_addr = false;
    attr.fix_write_addr = true;

    if ((check = pufs_dma_read_write(out, 16, (uint8_t *)data, length, &attr)) != SUCCESS)
    {
        printf("failed to set fix write address\n");
        return check;
    }
    // we fix the write address, so DMA always write the same value 11223344 to output address
    if (memcmp(out + 4, "\x11\x22\x33\x44", 4) != 0)
    {
        printf("the result is not matched\n");
        return E_VERFAIL;
    }

    return SUCCESS;
}

pufs_status_t pufs_dma_entropy_read_test(void)
{
    return pufs_dma_entropy_read(true);
}

pufs_status_t pufs_dma_random_read_test(void)
{
    return pufs_dma_entropy_read(false);
}
