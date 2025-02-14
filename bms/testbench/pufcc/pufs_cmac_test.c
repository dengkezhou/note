/**
 * @file      pufs_cmac_test.c
 * @brief     PUFsecurity CMAC API test cases
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
#include <stdbool.h>
#include <malloc.h>

#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_test_common.h"
#include "pufs_cmac.h"
#include "pufs_cmac_test.h"
#include "pufs_tv_cmac.h"
#include "pufs_memory_map.h"

pufs_status_t init_cmac_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_cmac_module_init(CMAC_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
/**
 * CMAC test function
 */
pufs_status_t pufs_cmac_iuf_test(void)
{
    const uint32_t ntests = sizeof(cmac_tp) / sizeof(struct cmac_test_pattern);
    const struct cmac_test_pattern* tp = cmac_tp;
    pufs_status_t check = SUCCESS;

    pufs_cmac_ctx* cmac_ctx = pufs_cmac_ctx_new();
    if (cmac_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = (pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_cmac_init(cmac_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_cmac_update(cmac_ctx, tp[i].msg, tp[i].msglen)) != SUCCESS) ||
            ((check = pufs_cmac_final(cmac_ctx, &md)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
            goto cleanup;
cleanup:
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_cmac_ctx_free(cmac_ctx);
    return check;
}

pufs_status_t pufs_cmac_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    uint32_t descs_len;
    const uint32_t ntests = sizeof(cmac_tp) / sizeof(struct cmac_test_pattern);
    const struct cmac_test_pattern* tp = cmac_tp;
    void *in = NULL;

    // TODO: descs size is based on the max message length of test cases.
    // change the fixed size to dynamically allocation.
    pufs_dma_sg_desc_st descs[5];

    pufs_cmac_ctx* cmac_ctx = pufs_cmac_ctx_new();
    if (cmac_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        in = malloc(tp[i].msglen);
        memcpy(in, tp[i].msg, tp[i].msglen);
        form_sg_descs(descs, &descs_len, 5, NULL, in, tp[i].msglen, 0, false);

        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_cmac_init(cmac_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS))
            goto cleanup;
        
        if ((check = pufs_cmac_sg_append(cmac_ctx, descs, descs_len, true)) != SUCCESS)
            goto cleanup;
        
        pufs_dma_sg_start();

        if ((check = pufs_cmac_sg_done(cmac_ctx, &md)) != SUCCESS)
            goto cleanup;

        check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen);
cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_cmac_ctx_free(cmac_ctx);
    return check;
}

pufs_status_t pufs_cmac_test(void)
{
    pufs_status_t check = SUCCESS;
    const uint32_t ntests = sizeof(cmac_tp) / sizeof(struct cmac_test_pattern);
    const struct cmac_test_pattern* tp = cmac_tp;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_cmac(&md, tp[i].msg, tp[i].msglen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    return check;
}
pufs_status_t pufs_cmac_swkey_iuf_test(void)
{
    pufs_status_t check;
    const uint32_t ntests = sizeof(cmac_tp) / sizeof(struct cmac_test_pattern);
    const struct cmac_test_pattern* tp = cmac_tp;

    pufs_cmac_ctx* cmac_ctx = pufs_cmac_ctx_new();
    if (cmac_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if (((check = pufs_cmac_init(cmac_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_cmac_update(cmac_ctx, tp[i].msg, tp[i].msglen)) != SUCCESS) ||
            ((check = pufs_cmac_final(cmac_ctx, &md)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_cmac_ctx_free(cmac_ctx);
    return check;
}
pufs_status_t pufs_cmac_swkey_test(void)
{
    pufs_status_t check = SUCCESS;
    const uint32_t ntests = sizeof(cmac_tp) / sizeof(struct cmac_test_pattern);
    const struct cmac_test_pattern* tp = cmac_tp;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if (((check = pufs_cmac(&md, tp[i].msg, tp[i].msglen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;   
        }
    }
    return check;
}
pufs_status_t pufs_cmac_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(cmac_tp) / sizeof(struct cmac_test_pattern);
    const struct cmac_test_pattern* tp = cmac_tp;
    pufs_status_t check = SUCCESS;

    pufs_cmac_ctx** cmac_ctxs = (pufs_cmac_ctx**)malloc(ntests * sizeof(pufs_cmac_ctx*));
    for (uint32_t i=0; i<ntests; i++)
        if ((cmac_ctxs[i] = pufs_cmac_ctx_new()) == NULL)
            goto failed;

    pufs_dgst_st md;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_cmac_init(cmac_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_cmac_update(cmac_ctxs[i], tp[i].msg, tp[i].msglen)) != SUCCESS)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        if (((check = pufs_cmac_final(cmac_ctxs[i], &md)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
            goto failed;

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_cmac_ctx_free(cmac_ctxs[i]);
    free(cmac_ctxs);
    return check;
}
