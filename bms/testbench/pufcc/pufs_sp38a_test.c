/**
 * @file      pufs_sp38a_test.c
 * @brief     PUFsecurity SP38A API test cases
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
#include <stdbool.h>
#include <malloc.h>

#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_sp38a.h"
#include "pufs_sp38a_test.h"
#include "pufs_tv_aesecb.h"
#include "pufs_tv_aescfb.h"
#include "pufs_tv_aesofb.h"
#include "pufs_tv_aescbc.h"
#include "pufs_tv_aesctr.h"
#include "pufs_tv_sm4ecb.h"
#include "pufs_tv_sm4cfb.h"
#include "pufs_tv_sm4ofb.h"
#include "pufs_tv_sm4cbc.h"
#include "pufs_tv_sm4ctr.h"
#include "pufs_test_common.h"
#include "pufs_memory_map.h"

pufs_status_t init_sp38a_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_sp38a_module_init(SP38A_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Static functions
 ****************************************************************************/
/*
 * ECB
 */
static pufs_status_t pufs_ecb_enc_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ecb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ecb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ecb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ecb_enc_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx *sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ptlen, 0, true);

        if ((check = pufs_enc_ecb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS)
            goto done;

        if ((check = pufs_enc_ecb_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;
        
        pufs_dma_sg_start();

        if ((check = pufs_enc_ecb_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);
    
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ecb_enc_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ecb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ecb_enc_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_ecb_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ecb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ecb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ecb_enc_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_ecb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ecb_enc_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_ecb_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ecb_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ecb_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

static pufs_status_t pufs_ecb_dec_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ecb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ecb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ecb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
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
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ecb_dec_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx *sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ctlen, 0, true);

        if ((check = pufs_dec_ecb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS)
            goto done;
        
        if ((check = pufs_dec_ecb_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_dec_ecb_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ecb_dec_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ecb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ecb_dec_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_ecb_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ecb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ecb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ecb_dec_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    uint32_t outlen;
    pufs_status_t check = SUCCESS;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_ecb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ecb_dec_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_ecb_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_ecb_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_ecb_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

/*
 * CFB
 */
static pufs_status_t pufs_cfb_enc_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_cfb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_enc_cfb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_cfb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_cfb_enc_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx *sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);
        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ptlen, 0, true);

        if ((check = pufs_enc_cfb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto done;
        
        if ((check = pufs_enc_cfb_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_enc_cfb_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_cfb_enc_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint8_t *out = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_cfb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cfb_enc_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    uint8_t *out = NULL;
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_cfb_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_enc_cfb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_cfb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_cfb_enc_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_cfb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cfb_enc_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_cfb_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_cfb_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_cfb_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

static pufs_status_t pufs_cfb_dec_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    uint8_t *out = NULL;
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_cfb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_dec_cfb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_cfb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
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
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_cfb_dec_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx *sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ctlen, 0, true);

        if ((check = pufs_dec_cfb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto done;

        if ((check = pufs_dec_cfb_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_dec_cfb_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen);

done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_cfb_dec_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_cfb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits) != SUCCESS)) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cfb_dec_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    uint8_t *out = NULL;
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_cfb_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_dec_cfb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_cfb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_cfb_dec_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_cfb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cfb_dec_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_cfb_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_cfb_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_cfb_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

/*
 * OFB
 */
static pufs_status_t pufs_ofb_enc_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ofb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_enc_ofb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ofb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ofb_enc_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx *sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ptlen, 0, true);

        if ((check = pufs_enc_ofb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto done;
        
        if ((check = pufs_enc_ofb_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_enc_ofb_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ofb_enc_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ofb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits) != SUCCESS)) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ofb_enc_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_ofb_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_enc_ofb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ofb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ofb_enc_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_ofb(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ofb_enc_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_ofb_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ofb_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ofb_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS))
            goto failed;        
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

static pufs_status_t pufs_ofb_dec_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ofb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_dec_ofb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ofb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
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
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ofb_dec_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ctlen, 0, true);

        if ((check = pufs_dec_ofb_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto done;
        
        if ((check = pufs_dec_ofb_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_dec_ofb_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ofb_dec_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ofb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ofb_dec_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    uint8_t *out = NULL;
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_ofb_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = pufs_dec_ofb_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ofb_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ofb_dec_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint8_t *out = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_ofb(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ofb_dec_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_ofb_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_ofb_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_ofb_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

/*
 * CBC
 */
static pufs_status_t pufs_cbc_enc_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp, int cs)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    uint8_t *out = NULL;
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_cbc_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = pufs_enc_cbc_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_cbc_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_cbc_enc_sg_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp, int cs)
{ 
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ptlen, 0, true);

        if ((check = pufs_enc_cbc_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, cs)) != SUCCESS)
            goto done;

        if ((check = pufs_enc_cbc_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_enc_cbc_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_cbc_enc_test(uint32_t ntests,
                              const struct bc_test_pattern* tp, int cs)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_cbc(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cbc_enc_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp,
                                        int cs)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_cbc_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = pufs_enc_cbc_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_cbc_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_cbc_enc_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp, int cs)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_cbc(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cbc_enc_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp,
                                        int cs)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_cbc_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, cs)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_cbc_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_cbc_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

static pufs_status_t pufs_cbc_dec_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp, int cs)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_cbc_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = pufs_dec_cbc_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_cbc_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
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
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_cbc_dec_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp, int cs)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ctlen, 0, true);

        if ((check = pufs_dec_cbc_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, cs)) != SUCCESS)
            goto done;
        
        if ((check = pufs_dec_cbc_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_dec_cbc_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_cbc_dec_test(uint32_t ntests,
                              const struct bc_test_pattern* tp, int cs)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_cbc(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits) != SUCCESS)) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cbc_dec_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp,
                                        int cs)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_cbc_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, cs)) != SUCCESS) ||
            ((check = pufs_dec_cbc_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen) != SUCCESS)) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_cbc_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_cbc_dec_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp, int cs)
{
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint8_t *out = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_cbc(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, cs) != SUCCESS)) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_cbc_dec_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp,
                                        int cs)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_cbc_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, cs)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_cbc_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_cbc_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

/*
 * CTR
 */
static pufs_status_t pufs_ctr_enc_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ctr_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = pufs_enc_ctr_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen) != SUCCESS)) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ctr_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ctr_enc_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx *sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ptlen, 0, true);

        if ((check = pufs_enc_ctr_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, 128)) != SUCCESS)
            goto done;

        if ((check = pufs_enc_ctr_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;
        
        pufs_dma_sg_start();

        if ((check = pufs_enc_ctr_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen) ;
done:        
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);
        
        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ctr_enc_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint8_t *out = NULL;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_enc_ctr(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ctr_enc_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_ctr_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = pufs_enc_ctr_update(sp38a_ctx, out + outlen, &toutlen, tp[i].pt, tp[i].ptlen) != SUCCESS)) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_enc_ctr_final(sp38a_ctx, out + outlen, &toutlen) != SUCCESS)) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ctr_enc_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        if (((check = pufs_enc_ctr(out, &outlen, tp[i].pt, tp[i].ptlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = (outlen != tp[i].ctlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].ct, tp[i].ctlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ctr_enc_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_enc_ctr_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, 128)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ctr_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_enc_ctr_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ctlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].ct, tp[i].ctlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

static pufs_status_t pufs_ctr_dec_iuf_test(uint32_t ntests,
                                  const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ctr_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = pufs_dec_ctr_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ctr_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
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
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ctr_dec_sg_test(uint32_t ntests,
                                 const struct bc_test_pattern* tp)
{
    pufs_dma_sg_desc_st descs[4];
    uint32_t descs_len;
    pufs_status_t check = SUCCESS;
    void *out = NULL, *in = NULL;

    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto done;

        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);

        form_sg_descs(descs, &descs_len, 4, out, in, tp[i].ctlen, 0, true);

        if ((check = pufs_dec_ctr_init(sp38a_ctx, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, 128)) != SUCCESS)
            goto done;

        if ((check = pufs_dec_ctr_sg_append(sp38a_ctx, descs, descs_len, true)) != SUCCESS)
            goto done;

        pufs_dma_sg_start();

        if ((check = pufs_dec_ctr_sg_done(sp38a_ctx)) != SUCCESS)
            goto done;

        check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen);
done:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}
static pufs_status_t pufs_ctr_dec_test(uint32_t ntests,
                              const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_dec_ctr(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SSKEY, keyslot, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_clear_key(SSKEY, keyslot, tp[i].keybits)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ctr_dec_swkey_iuf_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    pufs_sp38a_ctx* sp38a_ctx = pufs_sp38a_ctx_new();
    if (sp38a_ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        uint32_t outlen = 0;
        uint32_t toutlen = 0;
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_ctr_init(sp38a_ctx, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = pufs_dec_ctr_update(sp38a_ctx, out + outlen, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = pufs_dec_ctr_final(sp38a_ctx, out + outlen, &toutlen)) != SUCCESS) ||
            ((outlen = (outlen + toutlen)), false) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    pufs_sp38a_ctx_free(sp38a_ctx);
    return check;
}

static pufs_status_t pufs_ctr_dec_swkey_test(uint32_t ntests,
                                    const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    uint8_t *out = NULL;
    uint32_t outlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        if (((check = pufs_dec_ctr(out, &outlen, tp[i].ct, tp[i].ctlen, tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, 128)) != SUCCESS) ||
            ((check = (outlen != tp[i].ptlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
            ((check = pufs_test_memcmp(out, tp[i].pt, tp[i].ptlen)) != SUCCESS))
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
        free(out);
    }
    return check;
}

static pufs_status_t pufs_ctr_dec_multi_ctx_test(uint32_t ntests,
                                        const struct bc_test_pattern* tp)
{
    pufs_status_t check = SUCCESS;
    pufs_sp38a_ctx** sp38a_ctxs = (pufs_sp38a_ctx**)malloc(ntests * sizeof(pufs_sp38a_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
        if ((sp38a_ctxs[i] = pufs_sp38a_ctx_new()) == NULL)
            goto failed;
    for (uint32_t i=0; i<ntests; i++)
        if ((outs[i] = malloc(80)) == NULL)
            goto failed;

    for (uint32_t i=0; i<ntests; i++)
        outlens[i] = 0;
    for (uint32_t i=0; i<ntests; i++)
        if ((check = pufs_dec_ctr_init(sp38a_ctxs[i], tp[i].cipher, SWKEY, tp[i].key, tp[i].keybits, tp[i].iv, 128)) != SUCCESS)
            goto failed;
    uint32_t toutlen = 0;
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_ctr_update(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
    }
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_dec_ctr_final(sp38a_ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;
        outlens[i] += toutlen;
        if (((check = (outlens[i] == tp[i].ptlen ? SUCCESS : E_VERFAIL)) != SUCCESS) ||
            ((check = pufs_test_memcmp(outs[i], tp[i].pt, tp[i].ptlen)) != SUCCESS))
            goto failed;
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_sp38a_ctx_free(sp38a_ctxs[i]);
    free(sp38a_ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
/*
 * AES
 */
pufs_status_t pufs_aes_ecb_enc_iuf_test(void)
{
    return pufs_ecb_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_enc_sg_test(void)
{
    return pufs_ecb_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_enc_test(void)
{
    return pufs_ecb_enc_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_enc_swkey_iuf_test(void)
{
    return pufs_ecb_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_enc_swkey_test(void)
{
    return pufs_ecb_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_enc_multi_ctx_test(void)
{
    return pufs_ecb_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_dec_iuf_test(void)
{
    return pufs_ecb_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_dec_sg_test(void)
{
    return pufs_ecb_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_dec_test(void)
{
    return pufs_ecb_dec_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_dec_swkey_iuf_test(void)
{
    return pufs_ecb_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_dec_swkey_test(void)
{
    return pufs_ecb_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_ecb_dec_multi_ctx_test(void)
{
    return pufs_ecb_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_ecb_tp));
}
pufs_status_t pufs_aes_cfb_enc_iuf_test(void)
{
    return pufs_cfb_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_enc_sg_test(void)
{
    return pufs_cfb_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_enc_test(void)
{
    return pufs_cfb_enc_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_enc_swkey_iuf_test(void)
{
    return pufs_cfb_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_enc_swkey_test(void)
{
    return pufs_cfb_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_enc_multi_ctx_test(void)
{
    return pufs_cfb_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_dec_iuf_test(void)
{
    return pufs_cfb_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_dec_sg_test(void)
{
    return pufs_cfb_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_dec_test(void)
{
    return pufs_cfb_dec_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_dec_swkey_iuf_test(void)
{
    return pufs_cfb_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_dec_swkey_test(void)
{
    return pufs_cfb_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_cfb_dec_multi_ctx_test(void)
{
    return pufs_cfb_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cfb_tp));
}
pufs_status_t pufs_aes_ofb_enc_iuf_test(void)
{
    return pufs_ofb_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_enc_sg_test(void)
{
    return pufs_ofb_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_enc_test(void)
{
    return pufs_ofb_enc_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_enc_swkey_iuf_test(void)
{
    return pufs_ofb_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_enc_swkey_test(void)
{
    return pufs_ofb_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_enc_multi_ctx_test(void)
{
    return pufs_ofb_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_dec_iuf_test(void)
{
    return pufs_ofb_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_dec_sg_test(void)
{
    return pufs_ofb_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_dec_test(void)
{
    return pufs_ofb_dec_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_dec_swkey_iuf_test(void)
{
    return pufs_ofb_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_dec_swkey_test(void)
{
    return pufs_ofb_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_ofb_dec_multi_ctx_test(void)
{
    return pufs_ofb_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_ofb_tp));
}
pufs_status_t pufs_aes_cbc_enc_iuf_test(void)
{
    return pufs_cbc_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_enc_sg_test(void)
{
    return pufs_cbc_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_enc_test(void)
{
    return pufs_cbc_enc_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_enc_swkey_iuf_test(void)
{
    return pufs_cbc_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_enc_swkey_test(void)
{
    return pufs_cbc_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_enc_multi_ctx_test(void)
{
    return pufs_cbc_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_dec_iuf_test(void)
{
    return pufs_cbc_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_dec_sg_test(void)
{
    return pufs_cbc_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_dec_test(void)
{
    return pufs_cbc_dec_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_dec_swkey_iuf_test(void)
{
    return pufs_cbc_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_dec_swkey_test(void)
{
    return pufs_cbc_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_dec_multi_ctx_test(void)
{
    return pufs_cbc_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_tp), 0);
}
pufs_status_t pufs_aes_cbc_cs1_enc_iuf_test(void)
{
    return pufs_cbc_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_enc_sg_test(void)
{
    return pufs_cbc_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_enc_test(void)
{
    return pufs_cbc_enc_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_enc_swkey_iuf_test(void)
{
    return pufs_cbc_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_enc_swkey_test(void)
{
    return pufs_cbc_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_enc_multi_ctx_test(void)
{
    return pufs_cbc_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_dec_iuf_test(void)
{
    return pufs_cbc_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_dec_sg_test(void)
{
    return pufs_cbc_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_dec_test(void)
{
    return pufs_cbc_dec_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_dec_swkey_iuf_test(void)
{
    return pufs_cbc_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_dec_swkey_test(void)
{
    return pufs_cbc_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs1_dec_multi_ctx_test(void)
{
    return pufs_cbc_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs1_tp), 1);
}
pufs_status_t pufs_aes_cbc_cs2_enc_iuf_test(void)
{
    return pufs_cbc_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_enc_sg_test(void)
{
    return pufs_cbc_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_enc_test(void)
{
    return pufs_cbc_enc_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_enc_swkey_iuf_test(void)
{
    return pufs_cbc_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_enc_swkey_test(void)
{
    return pufs_cbc_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_enc_multi_ctx_test(void)
{
    return pufs_cbc_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_dec_iuf_test(void)
{
    return pufs_cbc_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_dec_sg_test(void)
{
    return pufs_cbc_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_dec_test(void)
{
    return pufs_cbc_dec_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_dec_swkey_iuf_test(void)
{
    return pufs_cbc_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_dec_swkey_test(void)
{
    return pufs_cbc_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs2_dec_multi_ctx_test(void)
{
    return pufs_cbc_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs2_tp), 2);
}
pufs_status_t pufs_aes_cbc_cs3_enc_iuf_test(void)
{
    return pufs_cbc_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_enc_sg_test(void)
{
    return pufs_cbc_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_enc_test(void)
{
    return pufs_cbc_enc_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_enc_swkey_iuf_test(void)
{
    return pufs_cbc_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_enc_swkey_test(void)
{
    return pufs_cbc_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_enc_multi_ctx_test(void)
{
    return pufs_cbc_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_dec_iuf_test(void)
{
    return pufs_cbc_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_dec_sg_test(void)
{
    return pufs_cbc_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_dec_test(void)
{
    return pufs_cbc_dec_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_dec_swkey_iuf_test(void)
{
    return pufs_cbc_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_dec_swkey_test(void)
{
    return pufs_cbc_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_cbc_cs3_dec_multi_ctx_test(void)
{
    return pufs_cbc_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_cbc_cs3_tp), 3);
}
pufs_status_t pufs_aes_ctr_enc_iuf_test(void)
{
    return pufs_ctr_enc_iuf_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_enc_sg_test(void)
{
    return pufs_ctr_enc_sg_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_enc_test(void)
{
    return pufs_ctr_enc_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_enc_swkey_iuf_test(void)
{
    return pufs_ctr_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_enc_swkey_test(void)
{
    return pufs_ctr_enc_swkey_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_enc_multi_ctx_test(void)
{
    return pufs_ctr_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_dec_iuf_test(void)
{
    return pufs_ctr_dec_iuf_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_dec_sg_test(void)
{
    return pufs_ctr_dec_sg_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_dec_test(void)
{
    return pufs_ctr_dec_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_dec_swkey_iuf_test(void)
{
    return pufs_ctr_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_dec_swkey_test(void)
{
    return pufs_ctr_dec_swkey_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_dec_multi_ctx_test(void)
{
    return pufs_ctr_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, aes_ctr_tp));
}
pufs_status_t pufs_aes_ctr_counter_test(void)
{
    pufs_status_t check = SUCCESS;
    uint32_t outlen;
    uint8_t *ctr20 = NULL, *ctr40 = NULL, *ctr80 = NULL;
    
    ctr20 = malloc(32 * 3);
    ctr40 = malloc(32 * 3);
    ctr80 = malloc(32 * 3);

    const void* key = "\x63\x68\x69\x63\x6b\x65\x6e\x20\x74\x65\x72\x69\x79\x61\x6b\x69";
    const void* iv = "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";
    const void* iv80 = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    const void* iv40 = "\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00";
    const void* iv20 = "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00";
    const void* zero = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    if (((check = pufs_enc_ctr(ctr20, &outlen, zero, 32, AES, SWKEY, key, 128, iv, 32)) != SUCCESS) ||
        ((check = (outlen != 32 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr40, &outlen, zero, 32, AES, SWKEY, key, 128, iv, 64)) != SUCCESS) ||
        ((check = (outlen != 32 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr80, &outlen, zero, 32, AES, SWKEY, key, 128, iv, 128)) != SUCCESS) ||
        ((check = (outlen != 32 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr20 + 32, &outlen, zero, 16, AES, SWKEY, key, 128, iv, 32)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr20 + 48, &outlen, zero, 16, AES, SWKEY, key, 128, iv20, 32)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr40 + 32, &outlen, zero, 16, AES, SWKEY, key, 128, iv, 64)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr40 + 48, &outlen, zero, 16, AES, SWKEY, key, 128, iv40, 64)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr80 + 32, &outlen, zero, 16, AES, SWKEY, key, 128, iv, 128)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_enc_ctr(ctr80 + 48, &outlen, zero, 16, AES, SWKEY, key, 128, iv80, 128)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr20, ctr20 + 32,32)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr40, ctr40 + 32,32)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr80, ctr80 + 32,32)) != SUCCESS))
        goto done;

    if (((check = pufs_dec_ctr(ctr20, &outlen, zero, 32, AES, SWKEY, key, 128, iv, 32)) != SUCCESS) ||
        ((check = (outlen != 32 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr40, &outlen, zero, 32, AES, SWKEY, key, 128, iv, 64)) != SUCCESS) ||
        ((check = (outlen != 32 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr80, &outlen, zero, 32, AES, SWKEY, key, 128, iv, 128)) != SUCCESS) ||
        ((check = (outlen != 32 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr20, ctr20 + 32,32)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr40, ctr40 + 32,32)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr80, ctr80 + 32,32)) != SUCCESS))
        goto done;

    if (((check = pufs_dec_ctr(ctr20 + 32, &outlen, zero, 16, AES, SWKEY, key, 128, iv, 32)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr20 + 48, &outlen, zero, 16, AES, SWKEY, key, 128, iv20, 32)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr40 + 32, &outlen, zero, 16, AES, SWKEY, key, 128, iv, 64)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr40 + 48, &outlen, zero, 16, AES, SWKEY, key, 128, iv40, 64)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr80 + 32, &outlen, zero, 16, AES, SWKEY, key, 128, iv, 128)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_dec_ctr(ctr80 + 48, &outlen, zero, 16, AES, SWKEY, key, 128, iv80, 128)) != SUCCESS) ||
        ((check = (outlen != 16 ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr20, ctr20 + 32,32)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr40, ctr40 + 32,32)) != SUCCESS) ||
        ((check = pufs_test_memcmp(ctr80, ctr80 + 32,32)) != SUCCESS))
        goto done;
done:
    free(ctr20);
    free(ctr40);
    free(ctr80);
    return check;
}

/*
 * SM4
 */
pufs_status_t pufs_sm4_ecb_enc_iuf_test(void)
{
    return pufs_ecb_enc_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_enc_test(void)
{
    return pufs_ecb_enc_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_enc_swkey_iuf_test(void)
{
    return pufs_ecb_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_enc_swkey_test(void)
{
    return pufs_ecb_enc_swkey_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_enc_multi_ctx_test(void)
{
    return pufs_ecb_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_dec_iuf_test(void)
{
    return pufs_ecb_dec_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_dec_test(void)
{
    return pufs_ecb_dec_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_dec_swkey_iuf_test(void)
{
    return pufs_ecb_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_dec_swkey_test(void)
{
    return pufs_ecb_dec_swkey_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_ecb_dec_multi_ctx_test(void)
{
    return pufs_ecb_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_ecb_tp));
}
pufs_status_t pufs_sm4_cfb_enc_iuf_test(void)
{
    return pufs_cfb_enc_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_enc_test(void)
{
    return pufs_cfb_enc_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_enc_swkey_iuf_test(void)
{
    return pufs_cfb_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_enc_swkey_test(void)
{
    return pufs_cfb_enc_swkey_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_enc_multi_ctx_test(void)
{
    return pufs_cfb_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_dec_iuf_test(void)
{
    return pufs_cfb_dec_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_dec_test(void)
{
    return pufs_cfb_dec_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_dec_swkey_iuf_test(void)
{
    return pufs_cfb_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_dec_swkey_test(void)
{
    return pufs_cfb_dec_swkey_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_cfb_dec_multi_ctx_test(void)
{
    return pufs_cfb_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_cfb_tp));
}
pufs_status_t pufs_sm4_ofb_enc_iuf_test(void)
{
    return pufs_ofb_enc_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_enc_test(void)
{
    return pufs_ofb_enc_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_enc_swkey_iuf_test(void)
{
    return pufs_ofb_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_enc_swkey_test(void)
{
    return pufs_ofb_enc_swkey_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_enc_multi_ctx_test(void)
{
    return pufs_ofb_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_dec_iuf_test(void)
{
    return pufs_ofb_dec_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_dec_test(void)
{
    return pufs_ofb_dec_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_dec_swkey_iuf_test(void)
{
    return pufs_ofb_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_dec_swkey_test(void)
{
    return pufs_ofb_dec_swkey_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_ofb_dec_multi_ctx_test(void)
{
    return pufs_ofb_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_ofb_tp));
}
pufs_status_t pufs_sm4_cbc_enc_iuf_test(void)
{
    return pufs_cbc_enc_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_enc_test(void)
{
    return pufs_cbc_enc_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_enc_swkey_iuf_test(void)
{
    return pufs_cbc_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_enc_swkey_test(void)
{
    return pufs_cbc_enc_swkey_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_enc_multi_ctx_test(void)
{
    return pufs_cbc_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_dec_iuf_test(void)
{
    return pufs_cbc_dec_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_dec_test(void)
{
    return pufs_cbc_dec_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_dec_swkey_iuf_test(void)
{
    return pufs_cbc_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_dec_swkey_test(void)
{
    return pufs_cbc_dec_swkey_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_cbc_dec_multi_ctx_test(void)
{
    return pufs_cbc_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_cbc_tp), 0);
}
pufs_status_t pufs_sm4_ctr_enc_iuf_test(void)
{
    return pufs_ctr_enc_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_enc_test(void)
{
    return pufs_ctr_enc_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_enc_swkey_iuf_test(void)
{
    return pufs_ctr_enc_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_enc_swkey_test(void)
{
    return pufs_ctr_enc_swkey_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_enc_multi_ctx_test(void)
{
    return pufs_ctr_enc_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_dec_iuf_test(void)
{
    return pufs_ctr_dec_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_dec_test(void)
{
    return pufs_ctr_dec_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_dec_swkey_iuf_test(void)
{
    return pufs_ctr_dec_swkey_iuf_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_dec_swkey_test(void)
{
    return pufs_ctr_dec_swkey_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
pufs_status_t pufs_sm4_ctr_dec_multi_ctx_test(void)
{
    return pufs_ctr_dec_multi_ctx_test(TCPARAM(struct bc_test_pattern, sm4_ctr_tp));
}
