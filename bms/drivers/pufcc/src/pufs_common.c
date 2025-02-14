/**
 * @file      pufs_common.c
 * @brief     PUFsecurity API implementation
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
#include <string.h>
#include "initcall.h"
#include "pufs_pal.h"
#include "pufs_reg_ctrl.h"
#include "pufs_internal.h"

#include "pufs_memory_map.h"
#include "pufs_common.h"
#include "pufs_ka.h"
#include "pufs_crypto.h"
#include "pufs_cmac.h"
#include "pufs_rt.h"
#include "pufs_dma.h"
#include "pufs_kdf.h"
#include "pufs_hmac.h"
#include "pufs_sp38a.h"
#include "pufs_sp38c.h"
#include "pufs_sp38d.h"
#include "pufs_sp38e.h"
#include "pufs_sp90a.h"
#include "pufs_ecp.h"
#include "pufs_sm2.h"
#include "pufs_chacha.h"

/*****************************************************************************
 * Variables
 ****************************************************************************/

char *status_msg[] = {
    "Success",
    "Address alignment mismatch",
    "Space overflow",
    "Size too small",
    "Invalid argument",
    "Resource is occupied",
    "Resource is unavailable",
    "Firmware error",
    "Invalid public key or digital signature",
    "Invalid ECC microprogram",
    "Access denied",
    "Not support",
    "Point at infinity",
    "Unspecific error",
};

struct pufs_context pufs_context = {.base_addr = 0x0};

/*****************************************************************************
 * API functions
 ****************************************************************************/

pufs_status_t pufs_module_init(uintptr_t base_addr, size_t size)
{
    pufs_pal_init(NULL);

    if (pufs_pal_mmap(&pufs_context.base_addr, base_addr, size) < 0)
    {
        LOG_ERROR("mmap 0x%08lx failed", base_addr);
        return E_FIRMWARE;
    }
    pufs_context.size = size;
    // LOG_INFO("PUFcc base address 0x%08lx .",  pufs_context.base_addr);

    pufs_dma_module_init(DMA_ADDR_OFFSET);
    pufs_rt_module_init(RT_ADDR_OFFSET);
    pufs_ka_module_init(KA_ADDR_OFFSET);
    pufs_kwp_module_init(KWP_ADDR_OFFSET);
    pufs_crypto_module_init(CRYPTO_ADDR_OFFSET);
    pufs_hmac_module_init(HMAC_HASH_ADDR_OFFSET);
    pufs_sp38a_module_init(SP38A_ADDR_OFFSET);
    pufs_sp38c_module_init(SP38C_ADDR_OFFSET);
    pufs_sp38d_module_init(SP38D_ADDR_OFFSET);
    pufs_sp38e_module_init(SP38E_ADDR_OFFSET);
    pufs_cmac_module_init(CMAC_ADDR_OFFSET);
    pufs_kdf_module_init(KDF_ADDR_OFFSET);
    pufs_pkc_module_init(PKC_ADDR_OFFSET);
    pufs_drbg_module_init(SP90A_ADDR_OFFSET);
    pufs_chacha_module_init(CHACHA_ADDR_OFFSET);

    return SUCCESS;
}

void pufs_release(void)
{
    pufs_pal_ummap(pufs_context.base_addr, pufs_context.size);
    pufs_pal_release();
}

char *pufs_strstatus(pufs_status_t status)
{
    return status_msg[status];
}

void pufs_init(void)
{
    pufs_module_init(PUFIOT_ADDR_START, PUFIOT_MAP_SIZE);
}

module_init(pufs_init);
