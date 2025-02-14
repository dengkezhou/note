/**
 * @file      pufs_sp90a_test.c
 * @brief     PUFsecurity SP90A API test cases
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

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "pufs_test_common.h"
#include "pufs_log.h"
#include "pufs_sp38a.h"
#include "pufs_sp90a.h"
#include "pufs_tv_drbgctr.h"
#include "pufs_rt.h"
#include "pufs_memory_map.h"

/*****************************************************************************
 * Static functions
 ****************************************************************************/
static pufs_status_t pufs_drbg_test_testmode(void)
{
    const uint32_t ntests = sizeof(drbg_tp) / sizeof(struct drbg_test_pattern);
    const struct drbg_test_pattern* tp = drbg_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint8_t out[64];
        bool df = (tp[i].nonce != NULL);

        // instantiate
        pufs_drbg_testmode_entropy(tp[i].e_inst, tp[i].e_instlen);
        if ((check = pufs_drbg_instantiate(AES_CTR_DRBG, tp[i].security, df, tp[i].nonce, tp[i].noncelen, tp[i].pstr, tp[i].pstrlen)) != SUCCESS)
            goto uninst;

        // reseed
        if (tp[i].e_reseed != NULL)
        {
            pufs_drbg_testmode_entropy(tp[i].e_reseed, tp[i].e_reseedlen);
            if ((check = pufs_drbg_reseed(df, tp[i].adin_reseed, tp[i].adin_reseedlen)) != SUCCESS)
                goto uninst;
        }

        bool pr;
        // 1st generate
        pr = (tp[i].e_gen1 != NULL);
        if (pr)
            pufs_drbg_testmode_entropy(tp[i].e_gen1, tp[i].e_gen1len);
        if ((check = pufs_drbg_generate(out, B2b(tp[i].outlen), pr, df, tp[i].adin_gen1, tp[i].adin_gen1len, true)) != SUCCESS)
            goto uninst;

        // 2nd generate
        pr = (tp[i].e_gen2 != NULL);
        if (pr)
            pufs_drbg_testmode_entropy(tp[i].e_gen2, tp[i].e_gen2len);
        if ((check = pufs_drbg_generate(out, B2b(tp[i].outlen), pr, df, tp[i].adin_gen2, tp[i].adin_gen2len, true)) != SUCCESS)
            goto uninst;

        if (memcmp(out, tp[i].out, tp[i].outlen) != 0)
            check = E_VERFAIL;
uninst:
        if (check != SUCCESS)
            LOG_ERROR("Case%lu Failed.",  i);

        pufs_status_t uinst_check = SUCCESS;
        if ((uinst_check = pufs_drbg_uninstantiate()) != SUCCESS)
            LOG_ERROR("Case%lu, %s", i, "Fail to uninstantiate drbg");

        if (check != SUCCESS || uinst_check != SUCCESS)
            return check != SUCCESS ? check : uinst_check;
    }
    return check;
}
static pufs_status_t pufs_drbg_test_normal(bool df)
{
    uint8_t out[2][64];
    uint8_t in[32];
    pufs_status_t check = SUCCESS;

    // Random input
    if ((check = pufs_rand(in, 8)) != SUCCESS)
        return check;

    // 2 trial
    for (uint32_t i=0; i<2; i++)
    {
        // instantiate + reseed + 1st generate + 2nd generate
        if (((check = pufs_drbg_instantiate(AES_CTR_DRBG, 256, df, in, 32, in, 32)) == SUCCESS) &&
            ((check = pufs_drbg_reseed(df, in, 32)) == SUCCESS) &&
            ((check = pufs_drbg_generate(out[i], 64, true, df, in, 32, false)) == SUCCESS))
            check = pufs_drbg_generate(out[i], 64, true, df, in, 32, false);

        pufs_status_t uinst_check = SUCCESS;
        if ((uinst_check = pufs_drbg_uninstantiate()) != SUCCESS)
        {
            LOG_ERROR("Trial%lu, %s", i, "Fail to uninstantiate drbg");
            check = check == SUCCESS ? uinst_check : check;
        }

        if (check != SUCCESS)
            return check;
    }
    // check output difference
    check = pufs_test_memcmp(out[0], out[1], 64);

    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t init_sp90a_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS &&
        (check = pufs_sp38a_module_init(SP38A_ADDR_OFFSET)) == SUCCESS)
        check = pufs_drbg_module_init(SP90A_ADDR_OFFSET);
    return check;
}

pufs_status_t pufs_drbg_test(void)
{
    // enable DRBG test mode
    pufs_drbg_enable_testmode();

    if (pufs_drbg_is_testmode()) {
        return pufs_drbg_test_testmode();
    } else {
        pufs_status_t check = SUCCESS;
        if ((check = pufs_drbg_test_normal(false)) != SUCCESS)
            return check;
        return pufs_drbg_test_normal(true);
    }
}
