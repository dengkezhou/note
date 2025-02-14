/**
 * @file      pufs_sp38d_test.c
 * @brief     PUFsecurity SP38D API test cases
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
#include "pufs_sp38d.h"
#include "pufs_tv_aesgcm.h"
#include "pufs_memory_map.h"

/*****************************************************************************
 * Static variables
 ****************************************************************************/
static uint8_t tag[BC_BLOCK_SIZE];

pufs_status_t init_sp38d_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_sp38d_module_init(SP38D_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_aes_gcm_enc_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38d_ctx* sp38d_ctx = pufs_sp38d_ctx_new();
    if (sp38d_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_gcm_init(sp38d_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS) ||
            ((check = pufs_enc_gcm_update(sp38d_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_enc_gcm_update(sp38d_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_gcm_final(sp38d_ctx, out + outlen, &toutlen, tag, tp[i].taglen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38d_ctx_free(sp38d_ctx);
    return check;
}

pufs_status_t pufs_aes_gcm_enc_sg_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len = 0;
    pufs_status_t check = SUCCESS;
    void *aad_in = NULL, *pt_in = NULL, *out = NULL;

    pufs_sp38d_ctx* sp38d_ctx = pufs_sp38d_ctx_new();
    if (sp38d_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        descs_len = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        if ((check = pufs_enc_gcm_init(sp38d_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS)
            goto done;
        
        aad_in = malloc(tp[i].aadlen);
        memcpy(aad_in, tp[i].aad, tp[i].aadlen);
        if (tp[i].aadlen > 0)
        {
            form_sg_descs(descs, &descs_len, 4, NULL, aad_in, tp[i].aadlen, 0, false);
            if ((check = pufs_enc_gcm_sg_append(sp38d_ctx, GCM_AAD, descs, descs_len, true)) != SUCCESS)
                goto done;
        }
        
        out = malloc(tp[i].ctlen);
        pt_in = malloc(tp[i].ptlen);
        memcpy(pt_in, tp[i].pt, tp[i].ptlen);
        if (tp[i].ptlen > 0)
        {
            form_sg_descs(descs, &descs_len, 4, out, pt_in, tp[i].ptlen, 0, true);
            if ((check = pufs_enc_gcm_sg_append(sp38d_ctx, GCM_PLAINTEXT, descs, descs_len, true)) != SUCCESS)
                goto done;
        }

        pufs_dma_sg_start();

        if ((check = pufs_enc_gcm_sg_done(sp38d_ctx, tag, tp[i].taglen)) != SUCCESS)
            goto done;

        if (memcmp(out, tp[i].ct, tp[i].ctlen) != 0 || memcmp(tag, tp[i].tag, tp[i].taglen) != 0)
            check = E_VERFAIL;
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(pt_in);
        free(aad_in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38d_ctx_free(sp38d_ctx);
    return check;
}

pufs_status_t pufs_aes_gcm_enc_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_gcm(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, tp[i].ivlen, tp[i].aad, tp[i].aadlen, tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_gcm_enc_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38d_ctx* sp38d_ctx = pufs_sp38d_ctx_new();
    if (sp38d_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        if (((check = pufs_enc_gcm_init(sp38d_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS) ||
            ((check = pufs_enc_gcm_update(sp38d_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_enc_gcm_update(sp38d_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_gcm_final(sp38d_ctx, out + outlen, &toutlen, tag, tp[i].taglen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38d_ctx_free(sp38d_ctx);
    return check;
}

pufs_status_t pufs_aes_gcm_enc_swkey_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen == 0 ? 1 : tp[i].ctlen);
        if (((check = pufs_enc_gcm(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, tp[i].ivlen, tp[i].aad, tp[i].aadlen, tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tag, tp[i].tag, tp[i].taglen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_gcm_enc_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;

    pufs_sp38d_ctx** sp38d_ctxs = (pufs_sp38d_ctx**)malloc(ntests * sizeof(pufs_sp38d_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    uint8_t** tags = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38d_ctxs[i] = pufs_sp38d_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(51)) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((tags[i] = malloc(16)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_gcm_init(sp38d_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_gcm_update(sp38d_ctxs[i], NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_gcm_update(sp38d_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_gcm_final(sp38d_ctxs[i], outs[i] + outlens[i], &toutlen, tags[i], tp[i].taglen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((check = pufs_test_memcmp(tags[i], tp[i].tag, tp[i].taglen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38d_ctx_free(sp38d_ctxs[i]);
    free(sp38d_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    for (uint32_t i=0; i<ntests; i++)
        free(tags[i]);
    free(tags);
    return check;
}

pufs_status_t pufs_aes_gcm_dec_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38d_ctx* sp38d_ctx = pufs_sp38d_ctx_new();
    if (sp38d_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_gcm_init(sp38d_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS) ||
            ((check = pufs_dec_gcm_update(sp38d_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_dec_gcm_update(sp38d_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_gcm_final(sp38d_ctx, out + outlen, &toutlen, tp[i].tag, tp[i].taglen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38d_ctx_free(sp38d_ctx);
    return check;
}

pufs_status_t pufs_aes_gcm_dec_sg_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len = 0;
    pufs_status_t check = SUCCESS;
    void *aad_in = NULL, *ct_in = NULL, *out = NULL;

    pufs_sp38d_ctx* sp38d_ctx = pufs_sp38d_ctx_new();
    if (sp38d_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        if ((check = pufs_dec_gcm_init(sp38d_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS)
            goto done;
        
        aad_in = malloc(tp[i].aadlen);
        memcpy(aad_in, tp[i].aad, tp[i].aadlen);
        if (tp[i].aadlen > 0)
        {
            form_sg_descs(descs, &descs_len, 4, NULL, aad_in, tp[i].aadlen, 0, false);
            if ((check = pufs_dec_gcm_sg_append(sp38d_ctx, GCM_AAD, descs, descs_len, true)) != SUCCESS)
                goto done;
        }
        
        out = malloc(tp[i].ptlen);
        ct_in = malloc(tp[i].ctlen);
        memcpy(ct_in, tp[i].ct, tp[i].ctlen);
        if (tp[i].ctlen > 0)
        {
            form_sg_descs(descs, &descs_len, 4, out, ct_in, tp[i].ctlen, 0, true);
            if ((check = pufs_dec_gcm_sg_append(sp38d_ctx, GCM_PLAINTEXT, descs, descs_len, true)) != SUCCESS)
                goto done;
        }

        pufs_dma_sg_start();

        if ((check = pufs_dec_gcm_sg_done(sp38d_ctx, tp[i].tag, tp[i].taglen)) != SUCCESS)
            goto done;

        if (memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(ct_in);
        free(aad_in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38d_ctx_free(sp38d_ctx);
    return check;
}

pufs_status_t pufs_aes_gcm_dec_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_gcm(out, &outlen, tp[i].ct, tp[i].ctlen,
             tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, tp[i].ivlen, tp[i].aad, tp[i].aadlen, tp[i].tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_gcm_dec_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38d_ctx* sp38d_ctx = pufs_sp38d_ctx_new();
    if (sp38d_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        if (((check = pufs_dec_gcm_init(sp38d_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS) ||
            ((check = pufs_dec_gcm_update(sp38d_ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS) ||
            ((check = pufs_dec_gcm_update(sp38d_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_gcm_final(sp38d_ctx, out + outlen, &toutlen, tp[i].tag, tp[i].taglen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38d_ctx_free(sp38d_ctx);
    return check;
}

pufs_status_t pufs_aes_gcm_dec_swkey_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen == 0 ? 1 : tp[i].ptlen);
        if (((check = pufs_dec_gcm(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, tp[i].ivlen, tp[i].aad, tp[i].aadlen, tp[i].tag, tp[i].taglen)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_gcm_dec_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(aes_gcm_tp) / sizeof(struct gcm_test_pattern);
    const struct gcm_test_pattern* tp __attribute__((unused)) = aes_gcm_tp;
    pufs_status_t check = SUCCESS;

    pufs_sp38d_ctx** sp38d_ctxs = (pufs_sp38d_ctx**)malloc(ntests * sizeof(pufs_sp38d_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38d_ctxs[i] = pufs_sp38d_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(51)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_gcm_init(sp38d_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, tp[i].ivlen)) != SUCCESS)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_gcm_update(sp38d_ctxs[i], NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_gcm_update(sp38d_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_gcm_final(sp38d_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].tag, tp[i].taglen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (outlens[i] != tp[i].ptlen ||
            memcmp(outs[i], tp[i].pt, tp[i].ptlen) != 0)
        {
            check = E_VERFAIL;
            goto failed;
        }
    }

failed:
    if (check != SUCCESS)
        LOG_INFO("\t[FAILED] %s\n", "{ ERROR MESSAGE HERE! }");

    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38d_ctx_free(sp38d_ctxs[i]);
    free(sp38d_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}
