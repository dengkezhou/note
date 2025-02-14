/**
 * @file      pufs_sp38e_test.c
 * @brief     PUFsecurity SP38E API test cases
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
#include "pufs_sp38e.h"
#include "pufs_tv_aesxts.h"
#include "pufs_memory_map.h"

#define XTS_DESC_LEN 4

pufs_status_t init_sp38e_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_sp38e_module_init(SP38E_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_aes_xts_enc_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;

    pufs_sp38e_ctx* sp38e_ctx = pufs_sp38e_ctx_new();
    if (sp38e_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot1 = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t keyslot2 = (tp[i].keybits > 128) ? SK256_1 : SK128_1;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot1, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot2, (uint8_t*)tp[i].key + b2B(tp[i].keybits), tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_xts_init(sp38e_ctx, tp[i].cipher, SSKEY, keyslot1, tp[i].keybits, SSKEY, keyslot2, tp[i].iv, 0)) != SUCCESS) ||
            ((check = pufs_enc_xts_update(sp38e_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_xts_final(sp38e_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot1, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot2, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38e_ctx_free(sp38e_ctx);
    return check;
}

pufs_status_t pufs_aes_xts_enc_sg_test(void)
{
    pufs_dma_sg_desc_st descs[XTS_DESC_LEN];
    uint32_t descs_len = 0;
    pufs_sp38e_ctx *sp38e_ctx;
    pufs_status_t check = SUCCESS;

    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    void *in = NULL, *out = NULL;

    sp38e_ctx = pufs_sp38e_ctx_new();
    if (sp38e_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot1 = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t keyslot2 = (tp[i].keybits > 128) ? SK256_1 : SK128_1;

        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);
        form_sg_descs(descs, &descs_len, XTS_DESC_LEN, out, in, tp[i].ptlen, 0, true);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot1, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot2, (uint8_t*)tp[i].key + b2B(tp[i].keybits), tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_xts_init(sp38e_ctx, tp[i].cipher, SSKEY, keyslot1, tp[i].keybits, SSKEY, keyslot2, tp[i].iv, 0)) != SUCCESS) ||
            ((check = pufs_enc_xts_sg_append(sp38e_ctx, descs, descs_len, true)) != SUCCESS))
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_enc_xts_sg_done(sp38e_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen);
done:
        pufs_clear_key(SSKEY, keyslot1, tp[i].keybits);
        pufs_clear_key(SSKEY, keyslot2, tp[i].keybits);
        free(in);
        free(out);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38e_ctx_free(sp38e_ctx);
    return check;
}

pufs_status_t pufs_aes_xts_enc_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        pufs_ka_slot_t keyslot1 = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t keyslot2 = (tp[i].keybits > 128) ? SK256_1 : SK128_1;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot1, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot2, (uint8_t*)tp[i].key + b2B(tp[i].keybits), tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_xts(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot1, tp[i].keybits, SSKEY, keyslot2, tp[i].iv, 0)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot1, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot2, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_xts_enc_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38e_ctx* sp38e_ctx = pufs_sp38e_ctx_new();
    if (sp38e_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        if (((check = pufs_enc_xts_init(sp38e_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, SWKEY, tp[i].key + b2B(tp[i].keybits), tp[i].iv, 0)) != SUCCESS) ||
            ((check = pufs_enc_xts_update(sp38e_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_xts_final(sp38e_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38e_ctx_free(sp38e_ctx);
    return check;
}

pufs_status_t pufs_aes_xts_enc_swkey_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_xts(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, SWKEY, tp[i].key + b2B(tp[i].keybits), tp[i].iv, 0)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_xts_enc_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;

    pufs_sp38e_ctx** sp38e_ctxs = (pufs_sp38e_ctx**)malloc(ntests * sizeof(pufs_sp38e_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38e_ctxs[i] = pufs_sp38e_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(48)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_xts_init(sp38e_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, SWKEY, tp[i].key + b2B(tp[i].keybits), tp[i].iv, 0)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_xts_update(sp38e_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_xts_final(sp38e_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (outlens[i] != tp[i].ctlen ||
            memcmp(outs[i], tp[i].ct, tp[i].ctlen) != 0)
        {
            check = E_VERFAIL;
            goto failed;
        }
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38e_ctx_free(sp38e_ctxs[i]);
    free(sp38e_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

pufs_status_t pufs_aes_xts_dec_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38e_ctx* sp38e_ctx = pufs_sp38e_ctx_new();
    if (sp38e_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot1 = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t keyslot2 = (tp[i].keybits > 128) ? SK256_1 : SK128_1;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot1, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot2, (uint8_t*)tp[i].key + b2B(tp[i].keybits), tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_xts_init(sp38e_ctx, tp[i].cipher, SSKEY, keyslot1, tp[i].keybits, SSKEY, keyslot2, tp[i].iv, 0)) != SUCCESS) ||
            ((check = pufs_dec_xts_update(sp38e_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_xts_final(sp38e_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot1, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot2, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38e_ctx_free(sp38e_ctx);
    return check;
}

pufs_status_t pufs_aes_xts_dec_sg_test(void)
{
    pufs_dma_sg_desc_st descs[XTS_DESC_LEN];
    uint32_t descs_len = 0;
    pufs_sp38e_ctx *sp38e_ctx;
    pufs_status_t check = SUCCESS;
    void *in = NULL, *out = NULL;

    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;

    sp38e_ctx = pufs_sp38e_ctx_new();
    if (sp38e_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot1 = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t keyslot2 = (tp[i].keybits > 128) ? SK256_1 : SK128_1;

        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);
        form_sg_descs(descs, &descs_len, XTS_DESC_LEN, out, in, tp[i].ctlen, 0, true);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot1, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot2, (uint8_t*)tp[i].key + b2B(tp[i].keybits), tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_xts_init(sp38e_ctx, tp[i].cipher, SSKEY, keyslot1, tp[i].keybits, SSKEY, keyslot2, tp[i].iv, 0)) != SUCCESS) ||
            ((check = pufs_dec_xts_sg_append(sp38e_ctx, descs, descs_len, true)) != SUCCESS))
        {
            check = E_INVALID;
            goto done;
        }

        pufs_dma_sg_start();

        if ((check = pufs_dec_xts_sg_done(sp38e_ctx)) != SUCCESS)
            goto done;
        
        if (memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;
done:
        pufs_clear_key(SSKEY, keyslot1, tp[i].keybits);
        pufs_clear_key(SSKEY, keyslot2, tp[i].keybits);
        free(in);
        free(out);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38e_ctx_free(sp38e_ctx);
    return check;
}

pufs_status_t pufs_aes_xts_dec_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        pufs_ka_slot_t keyslot1 = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        pufs_ka_slot_t keyslot2 = (tp[i].keybits > 128) ? SK256_1 : SK128_1;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot1, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_import_plaintext_key(SSKEY, keyslot2, (uint8_t*)tp[i].key + b2B(tp[i].keybits), tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_xts(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot1, tp[i].keybits, SSKEY, keyslot2, tp[i].iv, 0)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot1, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot2, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            return check;
        }
        free(out);
    }
    return check;
}

pufs_status_t pufs_aes_xts_dec_swkey_iuf_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38e_ctx* sp38e_ctx = pufs_sp38e_ctx_new();
    if (sp38e_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        if (((check = pufs_dec_xts_init(sp38e_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, SWKEY, tp[i].key + b2B(tp[i].keybits), tp[i].iv, 0)) != SUCCESS) ||
            ((check = pufs_dec_xts_update(sp38e_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_xts_final(sp38e_ctx, out + outlen, &toutlen) != SUCCESS)) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38e_ctx_free(sp38e_ctx);
    return check;
}

pufs_status_t pufs_aes_xts_dec_swkey_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_xts(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, SWKEY, tp[i].key + b2B(tp[i].keybits), tp[i].iv, 0)) != SUCCESS) ||
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

pufs_status_t pufs_aes_xts_dec_multi_ctx_test(void)
{
    const uint32_t ntests = sizeof(aes_xts_tp) / sizeof(struct bc_test_pattern);
    const struct bc_test_pattern* tp = aes_xts_tp;
    pufs_status_t check = SUCCESS;

    pufs_sp38e_ctx** sp38e_ctxs = (pufs_sp38e_ctx**)malloc(ntests * sizeof(pufs_sp38e_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38e_ctxs[i] = pufs_sp38e_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(48)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_xts_init(sp38e_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, SWKEY, tp[i].key + b2B(tp[i].keybits), tp[i].iv, 0)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_xts_update(sp38e_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_xts_final(sp38e_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38e_ctx_free(sp38e_ctxs[i]);
    free(sp38e_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}
