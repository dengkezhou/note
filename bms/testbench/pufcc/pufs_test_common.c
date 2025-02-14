/**
 * @file      pufs_test_common.c
 * @brief     PUFsecurity Crypto Test Common Utility Functions
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

#include "pufs_pal.h"
#include "pufs_test_common.h"
#include "pufs_common.h"
#include "pufs_ka.h"
#include "pufs_crypto.h"
#include "pufs_rt.h"
#include "pufs_rt_internal.h"
#include "pufs_dma.h"
#include "pufs_kdf.h"
#include "pufs_ecp.h"
#include "pufs_hmac.h"
#include "pufs_memory_map.h"

pufs_status_t init_rt_factory_test(void)
{
    pufs_status_t check = pufs_rt_module_init(RT_ADDR_OFFSET);
    if (check != SUCCESS)
        return check;
    return (rt_check_enrolled() || rt_check_tmlck_enable()) ?
            E_ERROR : SUCCESS;
}

pufs_status_t init_rt_user_test(void)
{
    pufs_status_t check = pufs_rt_module_init(RT_ADDR_OFFSET);
    if (check != SUCCESS)
        return check;
    rt_write_enroll();
    return rt_check_tmlck_enable() ?
            SUCCESS : rt_write_set_flag(TMLCK_FLAG, 0x0);
}

pufs_status_t init_crypto_test(void)
{
    pufs_status_t check = SUCCESS;
    // Every crypto test run under user mode
    if ((check = init_rt_user_test()) == SUCCESS &&
        (check = pufs_dma_module_init(DMA_ADDR_OFFSET)) == SUCCESS &&
        (check = pufs_ka_module_init(KA_ADDR_OFFSET)) == SUCCESS &&
        (check = pufs_kwp_module_init(KWP_ADDR_OFFSET)) == SUCCESS)
        check = pufs_crypto_module_init(CRYPTO_ADDR_OFFSET);
    return check;
}

pufs_status_t init_pkc_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS &&
        (check = pufs_pkc_module_init(PKC_ADDR_OFFSET)) == SUCCESS &&
        (check = pufs_hmac_module_init(HMAC_HASH_ADDR_OFFSET)) == SUCCESS)
        check = pufs_kdf_module_init(KDF_ADDR_OFFSET);
    return check;
}

void form_sg_descs(pufs_dma_sg_desc_st *descs,
                   uint32_t *descs_len,
                   const uint32_t max_descs_len,
                   const void *out,
                   const void *in,
                   const uint32_t inlen,
                   uint32_t block_size,
                   bool set_read)
{
    pufs_dma_dsc_attr_st attr = {.fix_read_addr = 0x0, .fix_write_addr = 0x0, .read_protect = 0x0, .write_protect = 0x0};
    uintptr_t start_w = (uintptr_t)in, start_r = (uintptr_t)out;
    uint32_t len = inlen; 
    *descs_len = 0;
    if (block_size == 0) block_size = 2 * BC_BLOCK_SIZE;;

    if (len == 0)
    {
        descs[0].length = 0;
        descs[0].write_addr = PHY_ADDR(start_w);
        descs[0].read_addr = (set_read == true) ? PHY_ADDR(start_r) : 0x0;
        descs[0].attr = attr;

        *descs_len = 1;
        return;
    }

    for (uint32_t index = 0; index < max_descs_len && len > 0; index++)
    {
        descs[index].attr = attr;
        descs[index].write_addr = PHY_ADDR(start_w);
        descs[index].read_addr = (set_read == true) ? PHY_ADDR(start_r) : 0x0;

        if (len >= block_size)
            descs[index].length = block_size;
        else
            descs[index].length = len % block_size;

        len = (len > block_size) ? len - block_size : 0;
        start_w += block_size;
        start_r += block_size;
        *descs_len += 1;
    }
}

