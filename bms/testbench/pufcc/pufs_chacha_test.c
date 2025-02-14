/**
 * @file      pufs_chacha_test.c
 * @brief     PUFsecurity ChaCha API test cases
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
#include "pufs_pal.h"
#include "pufs_log.h"
#include "pufs_chacha.h"
#include "pufs_chacha_test.h"
#include "pufs_tv_chacha20.h"
#include "pufs_tv_chacha20-poly1305.h"
#include "pufs_test_common.h"
#include "pufs_memory_map.h"

pufs_status_t init_chacha_test(void)
{
    pufs_status_t check = SUCCESS;
    if ((check = init_crypto_test()) == SUCCESS)
        check = pufs_chacha_module_init(CHACHA_ADDR_OFFSET);
    return check;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_chacha_enc_iuf_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        uint32_t outlen = 0, toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha_enc_init(ctx, &params)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha_enc_update(ctx, out, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if ((check = pufs_chacha_enc_final(ctx, out + outlen, &toutlen)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if (outlen != tp[i].ctlen || memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }
    pufs_chacha_ctx_free(ctx);
    return check;
}

pufs_status_t pufs_chacha_enc_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    pufs_dma_sg_desc_st descs[24];
    uint32_t descs_len = 0;
    void *out = NULL, *in = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        in = malloc(tp[i].ptlen);
        memcpy(in, tp[i].pt, tp[i].ptlen);

        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SSKEY,
        };

        form_sg_descs(descs, &descs_len, 24, out, in, tp[i].ptlen, 32, true);

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha_enc_init(ctx, &params)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha_enc_sg_append(ctx, descs, descs_len, true)) != SUCCESS)
            goto cleanup;
        
        pufs_dma_sg_start();

        if ((check = pufs_chacha_enc_sg_done(ctx)) != SUCCESS)
            goto cleanup;

        if (memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha_enc_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        uint32_t outlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha_enc(out, &outlen, &params, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto cleanup;
        
        if (outlen != tp[i].ctlen || memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha_enc_swkey_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        uint32_t outlen = 0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = (uintptr_t)tp[i].key,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SWKEY,
        };

        if ((check = pufs_chacha_enc(out, &outlen, &params, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto cleanup;
        
        if (outlen != tp[i].ctlen || memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
            check = E_VERFAIL;       

cleanup:
        free(out);

        if (check != SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha_enc_multi_ctx_test(void)
{
    pufs_status_t check = SUCCESS;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern* tp = chacha20_tp;

    pufs_chacha_ctx** ctxs = (pufs_chacha_ctx**)malloc(ntests * sizeof(pufs_chacha_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((ctxs[i] = pufs_chacha_ctx_new()) == NULL)
            goto failed;        
        if ((outs[i] = malloc(tp[i].ctlen)) == NULL)
            goto failed;
        outlens[i] = 0;
    }

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = (uintptr_t)tp[i].key,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SWKEY,
        };

        if ((check = pufs_chacha_enc_init(ctxs[i], &params)) != SUCCESS)
            goto failed;
    }
    uint32_t toutlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        toutlen = 0;

        if ((check = pufs_chacha_enc_update(ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;

        outlens[i] += toutlen;
    }

    for (uint32_t i=0; i<ntests; i++)
    {
        toutlen = 0;

        if ((check = pufs_chacha_enc_final(ctxs[i], outs[i] + outlens[i], &toutlen)) != SUCCESS)
            goto failed;

        outlens[i] += toutlen;
        
        if (outlens[i] != tp[i].ctlen || memcmp(outs[i], tp[i].ct, tp[i].ctlen) != 0)
        {
            check = E_VERFAIL;
            goto failed;
        }
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_chacha_ctx_free(ctxs[i]);
    free(ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);

    return check;
}

pufs_status_t pufs_chacha_dec_iuf_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0, toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha_dec_init(ctx, &params)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha_dec_update(ctx, out, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if ((check = pufs_chacha_dec_final(ctx, out + outlen, &toutlen)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if (outlen != tp[i].ptlen || memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
            break;
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha_dec_sg_test(void)
{
    pufs_status_t check = SUCCESS;
    pufs_dma_sg_desc_st descs[24];
    uint32_t descs_len = 0;
    uint8_t* out = NULL, *in = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        in = malloc(tp[i].ctlen);
        memcpy(in, tp[i].ct, tp[i].ctlen);

        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SSKEY,
        };

        form_sg_descs(descs, &descs_len, 24, out, in, tp[i].ctlen, 64, true);

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha_enc_init(ctx, &params)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha_dec_sg_append(ctx, descs, descs_len, true)) != SUCCESS)
            goto cleanup;
        
        pufs_dma_sg_start();

        if ((check = pufs_chacha_enc_sg_done(ctx)) != SUCCESS)
            goto cleanup;
        
        if (memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(in);

        if (check !=SUCCESS)
            break;
    }

    pufs_chacha_ctx_free(ctx);
    
    return check;
}

pufs_status_t pufs_chacha_dec_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha_dec(out, &outlen, &params, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto cleanup;
        
        if (outlen != tp[i].ptlen || memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
        {
            LOG_ERROR("test case %lu: encrypted data is not matched with expected result.", i + 1);
            check = E_VERFAIL;
        }
cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha_dec_swkey_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_tp) / sizeof(struct chacha20_test_pattern);
    const struct chacha20_test_pattern *tp = chacha20_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0;

        pufs_chacha_params_st params = {
            .counter = tp[i].ibc,
            .keyaddr = (uintptr_t)tp[i].key,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .round = 20,
            .keytype = SWKEY,
        };

        if ((check = pufs_chacha_dec(out, &outlen, &params, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto cleanup;
        
        if (outlen != tp[i].ptlen || memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;

cleanup:
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_enc_iuf_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    uint8_t tag[16];
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        memset(tag, 0x0, 16);
        uint32_t outlen = 0, toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha20_poly1305_enc_init(ctx, &params)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha20_poly1305_enc_update(ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS)
            goto cleanup;
        
        if ((check = pufs_chacha20_poly1305_enc_update(ctx, out, &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if ((check = pufs_chacha20_poly1305_enc_final(ctx, out + outlen, &toutlen, tag)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if (outlen != tp[i].ctlen || memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
        {
            LOG_ERROR("test case %lu: encrypted data is not matched with expected result.", i);
            check = E_VERFAIL;
        }
        
        if (memcmp(tag, tp[i].tag, tp[i].taglen) != 0)
        {
            LOG_ERROR("test case %lu: tag is not matched with expected tag.", i);
            check = E_VERFAIL;
        }
cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_enc_sg_test(void)
{
    uint32_t descs_len = 0;
    pufs_dma_sg_desc_st descs[10];
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL, *aad_in = NULL, *pt_in = NULL;
    uint8_t tag[16];
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        memset(tag, 0x0, 16);
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha20_poly1305_enc_init(ctx, &params)) != SUCCESS)
            goto cleanup;
        
        aad_in = malloc(tp[i].aadlen);
        memcpy(aad_in, tp[i].aad, tp[i].aadlen);
        form_sg_descs(descs, &descs_len, 10, 0x0, aad_in, tp[i].aadlen, 32, false);

        if ((check = pufs_chacha20_poly1305_enc_sg_append(ctx, CHACHA_AEAD_AAD, descs, descs_len, true)) != SUCCESS)
            goto cleanup;

        out = malloc(tp[i].ctlen);
        pt_in = malloc(tp[i].ptlen);
        memcpy(pt_in, tp[i].pt, tp[i].ptlen);
        form_sg_descs(descs, &descs_len, 10, out, pt_in, tp[i].ptlen, 32, true);

        if ((check = pufs_chacha20_poly1305_enc_sg_append(ctx, CHACHA_AEAD_PLAINTEXT, descs, descs_len, true)) != SUCCESS)
            goto cleanup;

        pufs_dma_sg_start();
        
        if ((check = pufs_chacha20_poly1305_enc_sg_done(ctx, tag)) != SUCCESS)
            goto cleanup;
        
        if (memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
        {
            LOG_ERROR("test case %lu: data is not matched with expected result.", i);
            check = E_VERFAIL;
        }
        
        if (memcmp(tag, tp[i].tag, tp[i].taglen) != 0)
        {
            LOG_ERROR("test case %lu: tag is not matched with expected tag.", i);
            check = E_VERFAIL;
        }
cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(aad_in);
        free(pt_in);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_enc_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    uint8_t tag[16];
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        memset(tag, 0x0, 16);
        uint32_t outlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha20_poly1305_enc(out,
                                                &outlen,
                                                tag,
                                                &params,
                                                tp[i].aad,
                                                tp[i].aadlen,
                                                tp[i].pt,
                                                tp[i].ptlen)) != SUCCESS)
            goto cleanup;
        
        if (outlen != tp[i].ctlen || memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
        {
            LOG_ERROR("test case %lu: encrypted data is not matched with expected result.", i);
            check = E_VERFAIL;
        }
        
        if (memcmp(tag, tp[i].tag, tp[i].taglen) != 0)
        {
            LOG_ERROR("test case %lu: tag is not matched with expected tag.", i);
            check = E_VERFAIL;
        }
cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_enc_swkey_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    uint8_t tag[16];
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ctlen);
        memset(tag, 0x0, 16);
        uint32_t outlen = 0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = (uintptr_t)tp[i].key,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SWKEY,
        };

        if((check = pufs_chacha20_poly1305_enc(out,
                                                &outlen,
                                                tag,
                                                &params,
                                                tp[i].aad,
                                                tp[i].aadlen,
                                                tp[i].pt,
                                                tp[i].ptlen)) != SUCCESS)
            goto cleanup;
        
        if (outlen != tp[i].ctlen || memcmp(out, tp[i].ct, tp[i].ctlen) != 0)
        {
            LOG_ERROR("test case %lu: encrypted data is not matched with expected result.", i);
            check = E_VERFAIL;
        }
        
        if (memcmp(tag, tp[i].tag, tp[i].taglen) != 0)
        {
            LOG_ERROR("test case %lu: tag is not matched with expected tag.", i);
            check = E_VERFAIL;
        }
cleanup:
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_enc_multi_ctx_test(void)
{
    pufs_status_t check = SUCCESS;
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern* tp = chacha20_poly1305_tp;

    pufs_chacha_ctx** ctxs = (pufs_chacha_ctx**)malloc(ntests * sizeof(pufs_chacha_ctx*));
    uint32_t* outlens = (uint32_t*)malloc(ntests * sizeof(uint32_t));
    uint8_t** outs = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    uint8_t** tags = (uint8_t**)malloc(ntests * sizeof(uint8_t*));
    for (uint32_t i=0; i<ntests; i++)
    {
        if ((ctxs[i] = pufs_chacha_ctx_new()) == NULL)
            goto failed;        
        if ((outs[i] = malloc(tp[i].ctlen)) == NULL)
            goto failed;
        if ((tags[i] = malloc(16)) == NULL)
            goto failed;
        outlens[i] = 0;
    }

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = (uintptr_t)tp[i].key,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SWKEY,
        };

        if ((check = pufs_chacha20_poly1305_enc_init(ctxs[i], &params)) != SUCCESS)
            goto failed;
    }

     for (uint32_t i=0; i<ntests; i++)
    {
        if ((check = pufs_chacha20_poly1305_enc_update(ctxs[i], NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS)
            goto failed;
    }

    uint32_t toutlen;
    for (uint32_t i=0; i<ntests; i++)
    {
        toutlen = 0;

        if ((check = pufs_chacha20_poly1305_enc_update(ctxs[i], outs[i] + outlens[i], &toutlen, tp[i].pt, tp[i].ptlen)) != SUCCESS)
            goto failed;

        outlens[i] += toutlen;
    }

    for (uint32_t i=0; i<ntests; i++)
    {
        toutlen = 0;
        
        if ((check = pufs_chacha20_poly1305_enc_final(ctxs[i], outs[i] + outlens[i], &toutlen, tags[i])) != SUCCESS)
            goto failed;

        outlens[i] += toutlen;
        
        if (outlens[i] != tp[i].ctlen || memcmp(outs[i], tp[i].ct, tp[i].ctlen) != 0)
        {
            LOG_ERROR("test case %lu: encrypted data is not matched with expected result.", i);
            check = E_VERFAIL;
            goto failed;
        }

        if (memcmp(tags[i], tp[i].tag, tp[i].taglen) != 0)
        {
            LOG_ERROR("test case %lu: tag is not matched with expected tag.", i);
            check = E_VERFAIL;
            goto failed;
        }
    }

failed:
    for (uint32_t i=0; i<ntests; i++)
        pufs_chacha_ctx_free(ctxs[i]);
    free(ctxs);
    free(outlens);
    for (uint32_t i=0; i<ntests; i++)
        free(outs[i]);
    free(outs);
    for (uint32_t i=0; i<ntests; i++)
        free(tags[i]);
    free(tags);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_dec_iuf_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0, toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha20_poly1305_dec_init(ctx, &params)) != SUCCESS)
            goto cleanup;

        if ((check = pufs_chacha20_poly1305_dec_update(ctx, NULL, NULL, tp[i].aad, tp[i].aadlen)) != SUCCESS)
            goto cleanup;
        
        if ((check = pufs_chacha20_poly1305_dec_update(ctx, out, &toutlen, tp[i].ct, tp[i].ctlen)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if ((check = pufs_chacha20_poly1305_dec_final(ctx, out + outlen, &toutlen, tp[i].tag)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if (outlen != tp[i].ptlen || memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        } 
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_dec_sg_test(void)
{
    uint32_t descs_len = 0;
    pufs_dma_sg_desc_st descs[5];
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL, *aad_in = NULL, *ct_in = NULL;;
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha20_poly1305_dec_init(ctx, &params)) != SUCCESS)
            goto cleanup;
        
        aad_in = malloc(tp[i].aadlen);
        memcpy(aad_in, tp[i].aad, tp[i].aadlen);
        form_sg_descs(descs, &descs_len, 5, 0x0, aad_in, tp[i].aadlen, 64, false);

        if ((check = pufs_chacha20_poly1305_dec_sg_append(ctx, CHACHA_AEAD_AAD, descs, descs_len, true)) != SUCCESS)
            goto cleanup;

        out = malloc(tp[i].ctlen);
        ct_in = malloc(tp[i].ctlen);
        memcpy(ct_in, tp[i].ct, tp[i].ctlen);  
        form_sg_descs(descs, &descs_len, 5, out, ct_in, tp[i].ctlen, 64, true);

        if ((check = pufs_chacha20_poly1305_dec_sg_append(ctx, CHACHA_AEAD_PLAINTEXT, descs, descs_len, true)) != SUCCESS)
            goto cleanup;
        
        pufs_dma_sg_start();

        if ((check = pufs_chacha20_poly1305_dec_sg_done(ctx, tp[i].tag)) != SUCCESS)
            goto cleanup;
        
        if (memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;
cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);
        free(aad_in);
        free(ct_in);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_dec_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0, toutlen = 0;
        pufs_ka_slot_t keyslot = (tp[i].keybits > 128) ? SK256_0 : SK128_0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = keyslot,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SSKEY,
        };

        if ((check = pufs_import_plaintext_key(SSKEY, keyslot, tp[i].key, tp[i].keybits)) != SUCCESS ||
            (check = pufs_chacha20_poly1305_dec(out,
                                                &outlen,
                                                &params,
                                                tp[i].aad,
                                                tp[i].aadlen,
                                                tp[i].ct,
                                                tp[i].ctlen,
                                                tp[i].tag)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if (outlen != tp[i].ptlen || memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;

cleanup:
        pufs_clear_key(SSKEY, keyslot, tp[i].keybits);
        free(out);

        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);

    return check;
}

pufs_status_t pufs_chacha20_poly1305_dec_swkey_test(void)
{
    pufs_status_t check = SUCCESS;
    uint8_t* out = NULL;
    const uint32_t ntests = sizeof(chacha20_poly1305_tp) / sizeof(struct chacha20_poly1305_test_pattern);
    const struct chacha20_poly1305_test_pattern *tp = chacha20_poly1305_tp;

    pufs_chacha_ctx *ctx = pufs_chacha_ctx_new();
    if (ctx == NULL)
        return E_ERROR;

    for (uint32_t i=0; i<ntests; i++)
    {
        out = malloc(tp[i].ptlen);
        uint32_t outlen = 0, toutlen = 0;

        pufs_chacha20_poly1305_params_st params = {
            .keyaddr = (uintptr_t)tp[i].key,
            .iv = tp[i].nonce,
            .ivlen = tp[i].noncelen,
            .keybits = tp[i].keybits,
            .keytype = SWKEY,
        };

        if ((check = pufs_chacha20_poly1305_dec(out,
                                                &outlen,
                                                &params,
                                                tp[i].aad,
                                                tp[i].aadlen,
                                                tp[i].ct,
                                                tp[i].ctlen,
                                                tp[i].tag)) != SUCCESS)
            goto cleanup;
        
        outlen += toutlen;
        
        if (outlen != tp[i].ptlen || memcmp(out, tp[i].pt, tp[i].ptlen) != 0)
            check = E_VERFAIL;

cleanup:
        if (check !=SUCCESS)
        {
            LOG_ERROR("Case%lu Failed.",  i);
            break;
        }
    }

    pufs_chacha_ctx_free(ctx);
    free(out);

    return check;
}

pufs_status_t puf_poly1305_test(void)
{
    uint8_t tag[16];
    char *key = "\x85\xd6\xbe\x78\x57\x55\x6d\x33\x7f\x44\x52\xfe\x42\xd5\x06\xa8\x01\x03\x80\x8a\xfb\x0d\xb2\xfd\x4a\xbf\xf6\xaf\x41\x49\xf5\x1b";
    char *message = "Cryptographic Forum Research Group";
    char *result = "\xa8\x06\x1d\xc1\x30\x51\x36\xc6\xc2\x2b\x8b\xaf\x0c\x01\x27\xa9";

    pufs_poly1305_params_st params = {
        .keyaddr = (uintptr_t)key,
        .keybits = 256,
        .keytype = SWKEY,
    };

    if(pufs_poly1305(tag, &params, (uint8_t *)message, 34) != SUCCESS)
        return E_ERROR;

    if (memcmp(tag, result, 16) != 0)
        return E_VERFAIL;

    return SUCCESS;
}
