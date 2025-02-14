/**
 * @file      pufs_hmac_test.c
 * @brief     PUFsecurity HMAC API test cases
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
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_test_common.h"
#include "pufs_hmac.h"
#include "pufs_hmac_test.h"
#include "pufs_tv_sha2.h"
#include "pufs_tv_sm3.h"
#include "pufs_tv_hmac.h"
#include "pufs_memory_map.h"

/*****************************************************************************
 * Static functions
 ****************************************************************************/
static pufs_status_t pufs_hash_iuf_test(uint32_t ntests,
                               const struct hash_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_hash_ctx* hash_ctx = pufs_hash_ctx_new();
    if (hash_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if ((check = pufs_hash_init(hash_ctx, tp[i].hash)) != SUCCESS ||
            (check = pufs_hash_update(hash_ctx, tp[i].msg, tp[i].msglen)) != SUCCESS ||
            (check = pufs_hash_final(hash_ctx, &md)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_hash_ctx_free(hash_ctx);
    return check;
}

static pufs_status_t pufs_hash_sg_test(uint32_t ntests,
                              const struct hash_test_pattern* tp)
{
    // TODO: descs size is based on the max message length of test cases.
    // change the fixed size to dynamically allocation.
    pufs_dma_sg_desc_st descs[10]; // hardcode
    uint32_t descs_len = 0, block_size = 0;
    pufs_status_t check = SUCCESS;
    void *in = NULL, *_in = NULL;

    pufs_hash_ctx* hash_ctx = pufs_hash_ctx_new();
    if (hash_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        switch (tp[i].hash)
        {
        case SHA_224:
        case SHA_256:
        case SM3:
            block_size = 64;
            break;
        case SHA_384:
        case SHA_512:
        case SHA_512_224:
        case SHA_512_256:
            block_size = 128;
            break;
        default:
            break;
        }

        _in = malloc(tp[i].msglen + 64);
        in = (void *)(((uintptr_t)_in) & (~(uintptr_t)63));
        memcpy(in, tp[i].msg, tp[i].msglen);
        form_sg_descs(descs, &descs_len, 10, NULL, in, tp[i].msglen, block_size, false);

        // 1. initialize the context
        // 2. append the descriptors to dma desc list
        if ((check = pufs_hash_init(hash_ctx, tp[i].hash)) != SUCCESS ||
            (check = pufs_hash_sg_append(hash_ctx, descs, descs_len, true)) != SUCCESS)
            goto cleanup;
      
        // start dma to compute the result
        pufs_dma_sg_start();

        // output the final result
        if ((check = pufs_hash_sg_done(hash_ctx, &md)) != SUCCESS)
            goto cleanup;

        check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen);
cleanup:
        free(_in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_hash_ctx_free(hash_ctx);
    return check;
}

static pufs_status_t pufs_hash_test(uint32_t ntests,
                           const struct hash_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if ((check = pufs_hash(&md, tp[i].msg, tp[i].msglen, tp[i].hash)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    return check;
}
static pufs_status_t pufs_hash_multi_ctx_test(uint32_t ntests,
                                     const struct hash_test_pattern* tp)
{
    pufs_hash_ctx** hash_ctxs = (pufs_hash_ctx**)malloc(ntests * sizeof(pufs_hash_ctx*));
    pufs_status_t check = SUCCESS;
    
    for (uint32_t i=0; i<ntests; i++)
        if ((hash_ctxs[i] = pufs_hash_ctx_new()) == NULL)
            goto failed;

    pufs_dgst_st md;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_hash_init(hash_ctxs[i], tp[i].hash)) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_hash_update(hash_ctxs[i], tp[i].msg, tp[i].msglen)) != SUCCESS)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_hash_final(hash_ctxs[i], &md)) != SUCCESS)
            goto failed;
        if (memcmp(tp[i].md, md.dgst, md.dlen) != 0)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            check = E_VERFAIL;
        }
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_hash_ctx_free(hash_ctxs[i]);
    free(hash_ctxs);
    return check;
}

pufs_status_t init_hmac_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_hmac_module_init(HMAC_HASH_ADDR_OFFSET);
    return check;
}
/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_sha2_iuf_test(void)
{
    return pufs_hash_iuf_test(TCPARAM(struct hash_test_pattern, sha2_tp));
}
pufs_status_t pufs_sha2_sg_test(void)
{
    return pufs_hash_sg_test(TCPARAM(struct hash_test_pattern, sha2_tp));
}
pufs_status_t pufs_sha2_test(void)
{
    return pufs_hash_test(TCPARAM(struct hash_test_pattern, sha2_tp));
}
pufs_status_t pufs_sha2_multi_ctx_test(void)
{
    return pufs_hash_multi_ctx_test(TCPARAM(struct hash_test_pattern, sha2_tp));
}
pufs_status_t pufs_sm3_iuf_test(void)
{
    return pufs_hash_iuf_test(TCPARAM(struct hash_test_pattern, sm3_tp));
}
pufs_status_t pufs_sm3_sg_test(void)
{
    return pufs_hash_sg_test(TCPARAM(struct hash_test_pattern, sm3_tp));
}
pufs_status_t pufs_sm3_test(void)
{
    return pufs_hash_test(TCPARAM(struct hash_test_pattern, sm3_tp));
}
pufs_status_t pufs_sm3_multi_ctx_test(void)
{
    return pufs_hash_multi_ctx_test(TCPARAM(struct hash_test_pattern, sm3_tp));
}
pufs_status_t pufs_hmac_iuf_test(void)
{
    uint32_t cases = 0;
    const uint32_t ntests = sizeof(hmac_tp) / sizeof(struct hmac_test_pattern);
    const struct hmac_test_pattern* tp = hmac_tp;

    // due to the limitation of key storage, we filter the test case which keybits is > 512;
    for (uint32_t i = 0; i < ntests; i++)
        cases = tp[i].keybits > 512 ? cases : cases + 1;

    uint32_t kbits;
    pufs_status_t check = SUCCESS;
    pufs_hmac_ctx* hmac_ctx = pufs_hmac_ctx_new();
    if (hmac_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if ((kbits = tp[i].keybits) > 512)
        {
            continue;
        }
        pufs_ka_slot_t keyslot = (kbits > 256) ? SK512_0 : (kbits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, kbits)) != SUCCESS) ||
            ((check = pufs_hmac_init(hmac_ctx, tp[i].hash, SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_hmac_update(hmac_ctx, tp[i].msg, tp[i].msglen)) != SUCCESS) ||
            ((check = pufs_hmac_final(hmac_ctx, &md)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_hmac_ctx_free(hmac_ctx);
    return check;
}
pufs_status_t pufs_hmac_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    uint32_t kbits, descs_len = 0, block_size = 0, cases = 0;
    void * in = NULL;
    pufs_dma_sg_desc_st descs[10];
    const uint32_t ntests = sizeof(hmac_tp) / sizeof(struct hmac_test_pattern);
    const struct hmac_test_pattern* tp = hmac_tp;
    
    // due to the limitation of key storage, we filter the test case which keybits is > 512;
    for (uint32_t i = 0; i < ntests; i++)
        cases = tp[i].keybits > 512 ? cases : cases + 1;

    pufs_hmac_ctx* hmac_ctx = pufs_hmac_ctx_new();
    if (hmac_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if ((kbits = tp[i].keybits) > 512)
        {
            continue;
        }
        pufs_ka_slot_t keyslot = (kbits > 256) ? SK512_0 : (kbits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, kbits)) != SUCCESS)
            goto cleanup;

        switch (tp[i].hash)
        {
        case SHA_224:
        case SHA_256:
        case SM3:
            block_size = 64;
            break;
        case SHA_384:
        case SHA_512:
        case SHA_512_224:
        case SHA_512_256:
            block_size = 128;
            break;
        default:
            break;
        }

        in = malloc(tp[i].msglen);
        memcpy(in, tp[i].msg, tp[i].msglen);
        form_sg_descs(descs, &descs_len, 10, NULL, in, tp[i].msglen, block_size, false);
        
        if ((check = pufs_hmac_init(hmac_ctx, tp[i].hash, SSKEY, keyslot, kbits)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_hmac_sg_append(hmac_ctx, descs, descs_len, true)) != SUCCESS)
            goto cleanup;

        pufs_dma_sg_start();

        if ((check = pufs_hmac_sg_done(hmac_ctx, &md)) != SUCCESS)
            goto cleanup;

        if (memcmp(tp[i].md, md.dgst, md.dlen) != 0)
            check = E_VERFAIL;
cleanup:
        free(in);
        pufs_clear_key(SSKEY, keyslot, kbits);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_hmac_ctx_free(hmac_ctx);
    return check;
}
pufs_status_t pufs_hmac_test(void)
{
    uint32_t cases = 0;
    const uint32_t ntests = sizeof(hmac_tp) / sizeof(struct hmac_test_pattern);
    const struct hmac_test_pattern* tp = hmac_tp;
    pufs_status_t check = SUCCESS;

    // due to the limitation of key storage, we filter the test case which keybits is > 512;
    for (uint32_t i = 0; i < ntests; i++)
        cases = tp[i].keybits > 512 ? cases : cases + 1;

    uint32_t kbits;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if ((kbits = tp[i].keybits) > 512)
        {
            continue;
        }
        pufs_ka_slot_t keyslot = (kbits > 256) ? SK512_0 : (kbits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, kbits)) != SUCCESS) ||
            ((check = pufs_hmac(&md, tp[i].msg, tp[i].msglen, tp[i].hash, SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, kbits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    return check;
}
pufs_status_t pufs_hmac_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(hmac_tp) / sizeof(struct hmac_test_pattern);
    const struct hmac_test_pattern* tp = hmac_tp;
    pufs_status_t check = SUCCESS;

    pufs_hmac_ctx* hmac_ctx = pufs_hmac_ctx_new();
    if (hmac_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if (((check = pufs_hmac_init(hmac_ctx, tp[i].hash, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_hmac_update(hmac_ctx, tp[i].msg, tp[i].msglen)) != SUCCESS) ||
            ((check = pufs_hmac_final(hmac_ctx, &md)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_hmac_ctx_free(hmac_ctx);
    return check;
}
pufs_status_t pufs_hmac_swkey_test(void)
{
    const uint32_t ntests = sizeof(hmac_tp) / sizeof(struct hmac_test_pattern);
    const struct hmac_test_pattern* tp = hmac_tp;
    pufs_status_t check = SUCCESS;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_dgst_st md;
        if ((check = pufs_hmac(&md, tp[i].msg, tp[i].msglen, tp[i].hash, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_test_memcmp(tp[i].md, md.dgst, md.dlen)) != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    return check;
}
pufs_status_t pufs_hmac_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(hmac_tp) / sizeof(struct hmac_test_pattern);
    const struct hmac_test_pattern* tp = hmac_tp;
    pufs_status_t check = SUCCESS;
    
    pufs_hmac_ctx** hmac_ctxs = (pufs_hmac_ctx**)malloc(ntests * sizeof(pufs_hmac_ctx*));
    for (uint32_t i=0; i<ntests; i++)
        if ((hmac_ctxs[i] = pufs_hmac_ctx_new()) == NULL)
            goto failed;

    pufs_dgst_st md;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_hmac_init(hmac_ctxs[i], tp[i].hash, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_hmac_update(hmac_ctxs[i], tp[i].msg, tp[i].msglen)) != SUCCESS)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_hmac_final(hmac_ctxs[i], &md)) != SUCCESS)
            goto failed;
        if (memcmp(tp[i].md, md.dgst, md.dlen) != 0)
        {
            check = E_VERFAIL;
            goto failed;
        }
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_hmac_ctx_free(hmac_ctxs[i]);
    free(hmac_ctxs);
    return check;
}
