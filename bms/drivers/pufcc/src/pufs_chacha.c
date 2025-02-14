/**
 * @file      pufs_chacha.c
 * @brief     PUFsecurity ChaCha API implementation
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
#include <string.h>
#include <limits.h>
#include <malloc.h>

#include "pufs_pal.h"
#include "pufs_internal.h"
#include "pufs_crypto_internal.h"
#include "pufs_ka_internal.h"
#include "pufs_dma_internal.h"
#include "pufs_chacha_internal.h"

struct pufs_chacha_regs *chacha_regs = NULL;

/*****************************************************************************
 * Static variables
 ****************************************************************************/
#ifdef BAREMETAL
static struct pufs_chacha_context chacha_ctx_static = {.stage = CHACHA_NONE};
#endif /* BAREMETAL */

static char *chacha_status_msg[] = {
    "Busy",
    "Error",
    "ChaCha20 not supported",
    "Key length 128 not supported",
    "Key length 256 not supported",
    "Zero quarter round",
    "Poly1305 not supported",
    "Non-tail block is not multiple of 64-byte in ChaCha20",
    "Zero length",
    "Zero round number of ChaCha20",
    "ChaCha20 and Poly1305 not supported",
};

/*****************************************************************************
 * Static Functions
 ****************************************************************************/
static void chacha_perror(uint32_t status)
{
    uint32_t status_size = sizeof(chacha_status_msg) / sizeof(char *);

    for (uint32_t index = 0; index < status_size; index++)
    {
        if ((status & 0x1) != 0)
            LOG_DEBUG("%s", chacha_status_msg[index]);
        status = status >> 1;
    }
}

static size_t fill_incomplete_block(uint8_t *buf, uint32_t *buflen, const uint8_t *in, uint32_t inlen)
{
    size_t len = 0;
    if (*buflen > 0 && *buflen < CHACHA_BLOCK_SIZE)
    {
        len = (CHACHA_BLOCK_SIZE - *buflen) < inlen ? CHACHA_BLOCK_SIZE - *buflen : inlen;
        memcpy(buf + *buflen, in, len);
        *buflen += len;
    }
    return len;
}

static size_t cut_blocks(uint8_t *buf, uint32_t *buflen, const uint8_t *in, uint32_t inlen)
{
    size_t blocks = inlen / CHACHA_BLOCK_SIZE;
    size_t last_block = inlen % CHACHA_BLOCK_SIZE;

    // always cache a block for final step.
    if (blocks > 0 && last_block == 0)
    {
        blocks -= 1;
        last_block = CHACHA_BLOCK_SIZE;
    }

    memset(buf, 0x0, CHACHA_BLOCK_SIZE);
    if (last_block)
    {
        memcpy(buf, in + (blocks * CHACHA_BLOCK_SIZE), last_block);
        *buflen = last_block;
    }

    return blocks;
}

static pufs_status_t verify_chacha_params(pufs_chacha_params_st *params)
{
    pufs_status_t check;

    if ((params->keytype == PUFKEY) || (params->keytype == SHARESEC))
    {
        LOG_DEBUG("%s", "invalid keytype");
        return E_DENY;
    }

    if ((params->keytype != SWKEY) &&
        ((check = keyslot_check(true,
                                params->keytype,
                                (uint32_t)params->keyaddr,
                                params->keybits)) != SUCCESS))
        return check;

    // RFC8439 2.4 : the size of input nonce is 96 bits.
    if (params->ivlen != 12)
    {
        LOG_DEBUG("%s", "invalid length of nonce(iv). expected length is 12 bytes(96 bits)");
        return E_INVALID;
    }

    return crypto_check_chacha_algo(params->keybits);
}

static uint32_t chacha_get_chacha_cfg(uint32_t round, uint32_t ivlen, uint8_t block_offset)
{
    uint32_t cfg;
    cfg = round & 0x1F;

    if (ivlen == 12)
        cfg |= 0x1 << CHACHA_CHACHA_CFG1_NONCE_TYPE_BITS;
    
    if (block_offset > 0)
        cfg |= (block_offset & 0x3) << CHACHA_CHACHA_CFG1_16_OFFSET_BITS;

    return cfg;
}

static void chacha_write_chacha_cfg(uint32_t round, uint32_t ivlen)
{
    uint32_t cfg = chacha_get_chacha_cfg(round, ivlen, 0);
    chacha_regs->chacha_cfg_1 = cfg;
}

// rfc8439_cfg
static uint32_t chacha_get_cfg(bool pad16_en, bool dgst_en, bool p1305_en, bool chch_en, bool aead_encrypt, bool poly1305_swkey)
{
    uint32_t val32 = 0x0;
    if (pad16_en)
        val32 |= 0x1;
    if (dgst_en)
        val32 |= 0x1 << CHACHA_RFC8439_CFG_DGEST_EN_BITS;
    if (p1305_en)
        val32 |= 0x1 << CHACHA_RFC8439_CFG_P1305_EN_BITS;
    if (chch_en)
        val32 |= 0x1 << CHACHA_RFC8439_CFG_CHCH_EN_BITS;
    if (aead_encrypt)
        val32 |= 0x1 << CHACHA_RFC8439_CFG_AEAD_ENCRYPT_BITS;
    if (poly1305_swkey)
        val32 |= 0x1 << CHACHA_RFC8439_CFG_P1305_SWKEY_EN_BITS;

    return val32;
}

static inline void chacha_write_cfg(uint32_t cfg)
{
    chacha_regs->cfg = cfg;
}

static pufs_status_t chacha_ctx_init(pufs_chacha_ctx *chacha_ctx,
                                     pufs_chacha_params_st *params)
{
    pufs_status_t check;
    if ((check = verify_chacha_params(params)) != SUCCESS)
    {
        LOG_DEBUG("invalid ChaCha params: %s", pufs_strstatus(check));
        return check;
    }

    if (params->round == 0)
        params->round = 20; // default round of ChaCha is 20

    if (params->keytype != SWKEY)
        chacha_ctx->keyslot = (uint32_t)params->keyaddr;
    else
        memcpy(chacha_ctx->key, (const void *)params->keyaddr, b2B(params->keybits));

    chacha_ctx->counter = params->counter;
    chacha_ctx->keytype = params->keytype;
    chacha_ctx->keybits = params->keybits;
    chacha_ctx->round = params->round;
    chacha_ctx->ivlen = params->ivlen;
    chacha_ctx->buflen = 0;
    chacha_ctx->pad_enable = false;
    chacha_ctx->aadlen = 0;
    chacha_ctx->txtlen = 0;
    chacha_ctx->poly1305_enable = false;
    chacha_ctx->txt_start = false;
    chacha_ctx->aad_start = false;
    chacha_ctx->chacha_enable = false;
    chacha_ctx->aead_encrypt = false;
    chacha_ctx->dgest_enable = false;
    chacha_ctx->offset = 0;
    chacha_ctx->block_offset = 0;
    
    memset(chacha_ctx->dgst, 0x0, POLY1305_DGST_SIZE);
    memset(chacha_ctx->buf, 0x0, CHACHA_BLOCK_SIZE);
    memcpy(chacha_ctx->iv, params->iv, params->ivlen);

    return SUCCESS;
}

static void chacha_form_iv_with_counter(pufs_chacha_ctx *chacha_ctx)
{
    uint32_t *iv = (uint32_t *)(&chacha_ctx->iv[12]);
    *iv = le2be(chacha_ctx->counter);
}

static void chacha_set_offset(pufs_chacha_ctx *chacha_ctx, uint32_t length)
{
    chacha_ctx->block_offset = (length % CHACHA_BLOCK_SIZE)/BC_BLOCK_SIZE;
    chacha_ctx->offset = length % BC_BLOCK_SIZE;
}

static pufs_status_t chacha_ctx_update(pufs_chacha_ctx *chacha_ctx,
                                       chacha_stage stage,
                                       uint8_t *out,
                                       uint32_t *outlen,
                                       const uint8_t *in,
                                       uint32_t inlen,
                                       bool start,
                                       bool last)
{
    uint32_t status, chacha_cfg;

    chacha_form_iv_with_counter(chacha_ctx);
    chacha_cfg = chacha_get_cfg(chacha_ctx->pad_enable,
                                chacha_ctx->dgest_enable,
                                chacha_ctx->poly1305_enable,
                                chacha_ctx->chacha_enable,
                                chacha_ctx->aead_encrypt,
                                false);

    chacha_write_chacha_cfg(chacha_ctx->round, chacha_ctx->ivlen);
    
    chacha_write_cfg(chacha_cfg);

    crypto_write_iv(chacha_ctx->iv, CHACHA_MAX_IV_LENGTH);
    
    if (stage != CHACHA_TEXT)
        crypto_write_dgst(chacha_ctx->dgst, POLY1305_DGST_SIZE);

    dma_write_data_block_config(start ? false : true, last, true, true, 0);
    dma_write_rwcfg(out, in, inlen);

    dma_write_config_0(false, false, false);

    if (chacha_ctx->keytype == SWKEY)
        crypto_write_sw_key(chacha_ctx->key, SW_KEY_MAXLEN);

    dma_write_key_config_0(chacha_ctx->keytype,
                           ALGO_TYPE_CHACHA,
                           chacha_ctx->keybits,
                           get_key_slot_idx(chacha_ctx->keytype, chacha_ctx->keyslot));

    dma_write_start();

    while (dma_check_busy_status(&status));

    if (status != 0)
    {
        LOG_ERROR("DMA status 0: 0x%08 PRIx32 \n", status);
        chacha_perror(chacha_regs->status);
        return E_ERROR;
    }

    if (out != NULL)
    {
        dma_read_output(out, inlen);
        *outlen = inlen;
    }

    if (stage != CHACHA_TEXT)
        crypto_read_dgest(chacha_ctx->dgst,
                          stage == CHACHA20_POLY1305_TAG ? POLY1305_TAG_SIZE : POLY1305_DGST_SIZE);

    return SUCCESS;
}

static pufs_status_t chacha_ctx_txt_final(pufs_chacha_ctx *chacha_ctx,
                                          chacha_stage stage,
                                          uint8_t *out,
                                          uint32_t *outlen)
{
    pufs_status_t check;
    check = chacha_ctx_update(chacha_ctx,
                              stage,
                              out,
                              outlen,
                              chacha_ctx->buf,
                              chacha_ctx->buflen,
                              chacha_ctx->txt_start,
                              true);
    if (check == SUCCESS)
        chacha_ctx->txtlen += chacha_ctx->buflen;
    
    chacha_ctx->buflen = 0;
    
    return check;
}

static pufs_status_t chacha_ctx_aad_final(pufs_chacha_ctx *chacha_ctx)
{
    pufs_status_t check = SUCCESS;
    if (chacha_ctx->buflen > 0)
    {
        check = chacha_ctx_update(chacha_ctx,
                             CHACHA20_POLY1305_AAD,
                             NULL,
                             NULL,
                             chacha_ctx->buf,
                             chacha_ctx->buflen,
                             chacha_ctx->aad_start,
                             true);
        if (check == SUCCESS)
            chacha_ctx->aadlen += chacha_ctx->buflen;

        chacha_ctx->buflen = 0;
    }
    
    return check;
}

static pufs_status_t chacha_ctx_aad_update(pufs_chacha_ctx *chacha_ctx,
                                           const uint8_t *in,
                                           uint32_t inlen)
{
    pufs_status_t check;
    uint32_t len, blocks;

    chacha_ctx->poly1305_enable = true;

    len = fill_incomplete_block(chacha_ctx->buf, &chacha_ctx->buflen, in, inlen);
    if (chacha_ctx->buflen == CHACHA_BLOCK_SIZE)
    {
        check = chacha_ctx_update(chacha_ctx,
                                  CHACHA20_POLY1305_AAD,
                                  NULL,
                                  NULL,
                                  chacha_ctx->buf,
                                  chacha_ctx->buflen,
                                  chacha_ctx->aad_start,
                                  false);
        if (check != SUCCESS)
        {
            LOG_DEBUG("failed to update ChaCha txt: %s", pufs_strstatus(check));
            return check;
        }
        chacha_ctx->aadlen += chacha_ctx->buflen;
    }
    in = in + len;
    inlen -= len;
    blocks = cut_blocks(chacha_ctx->buf, &chacha_ctx->buflen, in, inlen);
    if (blocks > 0)
    {
        len = blocks * CHACHA_BLOCK_SIZE;
        check = chacha_ctx_update(chacha_ctx,
                                  CHACHA20_POLY1305_AAD,
                                  NULL,
                                  NULL,
                                  in,
                                  len,
                                  chacha_ctx->aad_start,
                                  false);
        if (check != SUCCESS)
        {
            LOG_DEBUG("failed to update ChaCha txt: %s", pufs_strstatus(check));
            return check;
        }

        if (!chacha_ctx->aad_start)
            chacha_ctx->aad_start = true;

        chacha_ctx->aadlen += len;
    }

    return SUCCESS;
}

static void chacha_set_crypto_io_ctx(pufs_chacha_ctx *chacha_ctx)
{
    chacha_form_iv_with_counter(chacha_ctx);
}

static pufs_status_t chacha_ctx_sg_append(pufs_chacha_ctx *chacha_ctx,
                                          chacha_stage stage,
                                          pufs_dma_sg_desc_st *descs,
                                          uint32_t descs_len,
                                          bool last)
{
    uint64_t *len_ptr = NULL;
    uint32_t cfg, chacha_cfg;
    pufs_dma_sg_internal_desc_st *desc;
    pufs_dma_dsc_attr_st *attr;
    pufs_dma_sg_desc_opts_st opts = {.offset = 0x0, .done_interrupt = false, .done_pause = false};

    chacha_set_crypto_io_ctx(chacha_ctx);    

    desc = dma_sg_new_read_ctx_descriptor((uintptr_t)chacha_ctx->iv);
    dma_sg_desc_append_to_list(desc);

    cfg = chacha_get_cfg(chacha_ctx->pad_enable,
                         chacha_ctx->dgest_enable,
                         chacha_ctx->poly1305_enable,
                         chacha_ctx->chacha_enable,
                         chacha_ctx->aead_encrypt,
                         false);

    for (uint32_t index = 0; index < descs_len; index++)
    {
        desc = dma_sg_new_data_descriptor();
        if (desc == NULL)
            return E_FIRMWARE;

        attr = &descs[index].attr;
        
        if (stage == CHACHA20_POLY1305_AAD)
            opts.head = !chacha_ctx->aad_start;
        else
            opts.head = !chacha_ctx->txt_start;

        opts.offset = chacha_ctx->offset;

        if (index == descs_len - 1 && last)
            opts.tail = last;
        else
            opts.tail = false;

        chacha_cfg = chacha_get_chacha_cfg(chacha_ctx->round, chacha_ctx->ivlen, chacha_ctx->block_offset);

        dma_sg_desc_write_addr(desc, descs[index].write_addr, descs[index].read_addr, descs[index].length);
        dma_sg_desc_write_dsc_config(desc, attr, &opts);
        dma_sg_desc_write_key_config(desc, chacha_ctx->keytype,
                                     ALGO_TYPE_CHACHA, chacha_ctx->keybits,
                                     get_key_slot_idx(chacha_ctx->keytype, chacha_ctx->keyslot));

        dma_sg_desc_write_crypto_config(desc, chacha_cfg, cfg);
        dma_sg_desc_append_to_list(desc);

        if (stage == CHACHA20_POLY1305_AAD)
        {
            len_ptr = &chacha_ctx->aadlen;
            if (!chacha_ctx->aad_start) chacha_ctx->aad_start = true;
        }
        else
        {
            len_ptr = &chacha_ctx->txtlen;
            if (!chacha_ctx->txt_start) chacha_ctx->txt_start = true;
        }
        
        *(len_ptr) += descs[index].length;
        chacha_set_offset(chacha_ctx, *(len_ptr));
    }

    desc = dma_sg_new_write_ctx_descriptor((uintptr_t)chacha_ctx->iv);
    dma_sg_desc_append_to_list(desc);
    
    return SUCCESS;
}

static pufs_status_t chacha_ctx_sg_done(pufs_chacha_ctx *chacha_ctx)
{
    UNUSED(chacha_ctx);
    return SUCCESS;
}

static pufs_status_t chacha_ctx_aad_sg_append(pufs_chacha_ctx *chacha_ctx,
                                              chacha_stage stage,
                                              pufs_dma_sg_desc_st *descs,
                                              uint32_t descs_len,
                                              bool last)
{
    pufs_status_t check;
    chacha_ctx->poly1305_enable = true;

    if ((check = chacha_ctx_sg_append(chacha_ctx, stage, descs, descs_len, last)) != SUCCESS)
    {
        LOG_ERROR("failed to update AAD: %s", pufs_strstatus(check));
        return check;
    }

    if (last)
        chacha_set_offset(chacha_ctx, 0);
    
    return SUCCESS;
}

static pufs_status_t chacha_ctx_txt_sg_append(pufs_chacha_ctx *chacha_ctx,
                                              chacha_stage stage,
                                              pufs_dma_sg_desc_st *descs,
                                              uint32_t descs_len,
                                              bool last)
{
    pufs_status_t check;
    chacha_ctx->chacha_enable = true;
    
    if ((check = chacha_ctx_sg_append(chacha_ctx, stage, descs, descs_len, last)) != SUCCESS)
    {
        LOG_ERROR("failed to update TEXT: %s", pufs_strstatus(check));
        return check;
    }

    if (last)
        chacha_set_offset(chacha_ctx, 0);

    return SUCCESS;
}

static pufs_status_t chacha_ctx_txt_update(pufs_chacha_ctx *chacha_ctx,
                                           chacha_stage stage,
                                           uint8_t *out,
                                           uint32_t *outlen,
                                           const uint8_t *in,
                                           uint32_t inlen)
{
    pufs_status_t check;
    uint32_t len, blocks, temp_outlen;
    chacha_ctx->chacha_enable = true;
    len = fill_incomplete_block(chacha_ctx->buf, &chacha_ctx->buflen, in, inlen);
    if (chacha_ctx->buflen == CHACHA_BLOCK_SIZE)
    {
        check = chacha_ctx_update(chacha_ctx,
                                  stage,
                                  out,
                                  &temp_outlen,
                                  chacha_ctx->buf,
                                  chacha_ctx->buflen,
                                  chacha_ctx->txt_start,
                                  false);
        if (check != SUCCESS)
        {
            LOG_DEBUG("failed to update ChaCha txt: %s", pufs_strstatus(check));
            return check;
        }
        out += temp_outlen;
        *outlen += temp_outlen;
        chacha_ctx->counter += 1;
        chacha_ctx->txtlen += chacha_ctx->buflen;
    }
    in = in + len;
    inlen -= len;
    blocks = cut_blocks(chacha_ctx->buf, &chacha_ctx->buflen, in, inlen);
    if (blocks > 0)
    {
        len = blocks * CHACHA_BLOCK_SIZE;
        check = chacha_ctx_update(chacha_ctx,
                                  stage,
                                  out,
                                  &temp_outlen,
                                  in,
                                  len,
                                  chacha_ctx->txt_start,
                                  false);
        if (check != SUCCESS)
        {
            LOG_DEBUG("failed to update ChaCha txt: %s", pufs_strstatus(check));
            return check;
        }
        out += len;
        *outlen += temp_outlen; 
        chacha_ctx->counter += blocks;
        chacha_ctx->txtlen += len;

        if (!chacha_ctx->txt_start)
            chacha_ctx->txt_start = true;
    }

    return SUCCESS;
}

static pufs_status_t chacha20_poly1305_init(pufs_chacha_ctx *chacha_ctx,
                                            pufs_chacha20_poly1305_params_st *params,
                                            bool encrypt)
{
    pufs_status_t check;
    pufs_chacha_params_st chacha_params = {
        .iv = params->iv,
        .ivlen = params->ivlen,
        .counter = 1, // The the initial counter of AEAD is 1
        .keyaddr = params->keyaddr,
        .keybits = params->keybits,
        .keytype = params->keytype,
        .round = 20,
    };
    check = chacha_ctx_init(chacha_ctx, &chacha_params);
    chacha_ctx->aead_encrypt = encrypt;
    return check;
}

static pufs_status_t chacha20_poly1305_update(pufs_chacha_ctx *chacha_ctx,
                                              uint8_t *out,
                                              uint32_t *outlen,
                                              const uint8_t *in,
                                              uint32_t inlen)
{
    chacha_ctx->pad_enable = true;
    chacha_ctx->dgest_enable = true;

    // AAD case
    if (!chacha_ctx->chacha_enable && out == NULL)
        return chacha_ctx_aad_update(chacha_ctx, in, inlen);

    // Text case
    if (out != NULL)
    {
        if (!chacha_ctx->chacha_enable) // The input data is changed from AAD to Text
            chacha_ctx_aad_final(chacha_ctx);

        return chacha_ctx_txt_update(chacha_ctx, CHACHA20_POLY1305_TEXT, out, outlen, in, inlen);
    }

    return E_ERROR;
}

static pufs_status_t chacha20_poly1305_sg_append(pufs_chacha_ctx *chacha_ctx,
                                                 pufs_chacha_aead_data_t data_type,
                                                 pufs_dma_sg_desc_st *descs,
                                                 uint32_t descs_len,
                                                 bool last)
{
    chacha_ctx->pad_enable = true;
    chacha_ctx->dgest_enable = true;

    if (data_type == CHACHA_AEAD_AAD)
        return chacha_ctx_aad_sg_append(chacha_ctx, CHACHA20_POLY1305_AAD, descs, descs_len, last);
    else
        return chacha_ctx_txt_sg_append(chacha_ctx, CHACHA20_POLY1305_TEXT, descs, descs_len, last);

    return E_ERROR;
}

static pufs_status_t chacha20_poly1305_tag(pufs_chacha_ctx *chacha_ctx, uint8_t *out)
{
    pufs_status_t check;
    chacha_ctx->pad_enable = false;
    chacha_ctx->chacha_enable = false;
    chacha_ctx->poly1305_enable = true;
    chacha_ctx->dgest_enable = false;
    
    // RFC8439 2.8.1 Pseudocode for the AEAD Construction
    // mac_data |= num_to_8_le_bytes(aad.length)
    memcpy(chacha_ctx->buf, &chacha_ctx->aadlen, 8);
    // mac_data |= num_to_8_le_bytes(ciphertext.length)
    memcpy(chacha_ctx->buf + 8, &chacha_ctx->txtlen, 8);
    chacha_ctx->buflen = 16;

    check = chacha_ctx_update(chacha_ctx,
                              CHACHA20_POLY1305_TAG,
                              NULL,
                              NULL,
                              chacha_ctx->buf,
                              chacha_ctx->buflen,
                              true,
                              true);
    if (check == SUCCESS)
        memcpy(out, chacha_ctx->dgst, POLY1305_TAG_SIZE);

    return check;
}

static pufs_status_t chacha20_poly1305_sg_done(pufs_chacha_ctx *chacha_ctx, uint8_t *tag)
{
    pufs_status_t check;
    
    if ((check = chacha20_poly1305_tag(chacha_ctx, tag)) != SUCCESS)
    {
        LOG_ERROR("failed to generate tag %s", pufs_strstatus(check));
        return check;
    }

    return chacha_ctx_sg_done(chacha_ctx);
}

static pufs_status_t chacha20_poly1305_final(pufs_chacha_ctx *chacha_ctx,
                                             uint8_t *out,
                                             uint32_t *outlen,
                                             uint8_t *tag)
{
    pufs_status_t check;
    
    chacha_ctx->pad_enable = true;
    if ((check = chacha_ctx_txt_final(chacha_ctx, CHACHA20_POLY1305_TEXT, out, outlen)) != SUCCESS)
        return check;

    return chacha20_poly1305_tag(chacha_ctx, tag);
}

/*****************************************************************************
 * API Functions
 ****************************************************************************/
pufs_status_t pufs_chacha_module_init(uint32_t chacha_offset)
{
    chacha_regs = (struct pufs_chacha_regs *)(pufs_context.base_addr + chacha_offset);
    return version_check(CHACHA_VERSION, chacha_regs->version);
}

pufs_chacha_ctx *pufs_chacha_ctx_new(void)
{
    return malloc(sizeof(pufs_chacha_ctx));
}

void pufs_chacha_ctx_free(pufs_chacha_ctx *chacha_ctx)
{
    free(chacha_ctx);
}

pufs_status_t pufs_chacha_enc_init(pufs_chacha_ctx *chacha_ctx,
                                   pufs_chacha_params_st *params)
{
    return chacha_ctx_init(chacha_ctx, params);
}

pufs_status_t pufs_chacha_enc_update(pufs_chacha_ctx *chacha_ctx,
                                     uint8_t *out,
                                     uint32_t *outlen,
                                     const uint8_t *in,
                                     uint32_t inlen)
{
    return chacha_ctx_txt_update(chacha_ctx, CHACHA_TEXT, out, outlen, in, inlen);
}

pufs_status_t pufs_chacha_enc_sg_append(pufs_chacha_ctx *chacha_ctx,
                                        pufs_dma_sg_desc_st *descs,
                                        uint32_t descs_len,
                                        bool last)
{
    return chacha_ctx_txt_sg_append(chacha_ctx, CHACHA_TEXT, descs, descs_len, last);
}

pufs_status_t pufs_chacha_enc_sg_done(pufs_chacha_ctx *chacha_ctx)
{
    return chacha_ctx_sg_done(chacha_ctx);
}

pufs_status_t pufs_chacha_enc_final(pufs_chacha_ctx *chacha_ctx,
                                    uint8_t *out,
                                    uint32_t *outlen)
{
    return chacha_ctx_txt_final(chacha_ctx, CHACHA_TEXT, out, outlen);
}

pufs_status_t pufs_chacha_enc(uint8_t *out,
                              uint32_t *outlen,
                              pufs_chacha_params_st *params,
                              const uint8_t *in,
                              uint32_t inlen)
{
    pufs_status_t check;
    pufs_chacha_ctx ctx;
    uint32_t temp_outlen = 0;

    if ((check = pufs_chacha_enc_init(&ctx, params)) != SUCCESS)
        return check;
    
    if ((check = pufs_chacha_enc_update(&ctx, out, &temp_outlen, in, inlen)) != SUCCESS)
        return check;

    *outlen += temp_outlen;

    if ((check = pufs_chacha_enc_final(&ctx, out + *outlen, &temp_outlen)) != SUCCESS)
        return check;

    *outlen += temp_outlen;

    return SUCCESS;
}

pufs_status_t pufs_chacha_dec_init(pufs_chacha_ctx *chacha_ctx,
                                   pufs_chacha_params_st *params)
{
    return chacha_ctx_init(chacha_ctx, params);
}

pufs_status_t pufs_chacha_dec_update(pufs_chacha_ctx *chacha_ctx,
                                     uint8_t *out,
                                     uint32_t *outlen,
                                     const uint8_t *in,
                                     uint32_t inlen)
{
    return chacha_ctx_txt_update(chacha_ctx, CHACHA_TEXT, out, outlen, in, inlen);
}

pufs_status_t pufs_chacha_dec_sg_append(pufs_chacha_ctx *chacha_ctx,
                                        pufs_dma_sg_desc_st *descs,
                                        uint32_t descs_len,
                                        bool last)
{
    return chacha_ctx_txt_sg_append(chacha_ctx, CHACHA_TEXT, descs, descs_len, last);
}

pufs_status_t pufs_chacha_dec_final(pufs_chacha_ctx *chacha_ctx,
                                    uint8_t *out,
                                    uint32_t *outlen)
{
    return chacha_ctx_txt_final(chacha_ctx, CHACHA_TEXT, out, outlen);
}

pufs_status_t pufs_chacha_dec(uint8_t *out,
                              uint32_t *outlen,
                              pufs_chacha_params_st *params,
                              const uint8_t *in,
                              uint32_t inlen)
{
    pufs_status_t check;
    pufs_chacha_ctx ctx;
    uint32_t temp_outlen = 0;

    if ((check = pufs_chacha_dec_init(&ctx, params)) != SUCCESS)
        return check;
    
    if ((check = pufs_chacha_dec_update(&ctx, out, &temp_outlen, in, inlen)) != SUCCESS)
        return check;

    *outlen += temp_outlen;

    if ((check = pufs_chacha_dec_final(&ctx, out + *outlen, &temp_outlen)) != SUCCESS)
        return check;

    *outlen += temp_outlen;

    return SUCCESS;
}

pufs_status_t pufs_chacha20_poly1305_enc_init(pufs_chacha_ctx *chacha_ctx,
                                              pufs_chacha20_poly1305_params_st *params)
{
    return chacha20_poly1305_init(chacha_ctx, params, true);
}

pufs_status_t pufs_chacha20_poly1305_enc_update(pufs_chacha_ctx *chacha_ctx,
                                                uint8_t *out,
                                                uint32_t *outlen,
                                                const uint8_t *in,
                                                uint32_t inlen)
{
    return chacha20_poly1305_update(chacha_ctx, out, outlen, in, inlen);
}

pufs_status_t pufs_chacha20_poly1305_enc_sg_append(pufs_chacha_ctx *chacha_ctx,
                                                   pufs_chacha_aead_data_t data_type,
                                                   pufs_dma_sg_desc_st *descs,
                                                   uint32_t descs_len,
                                                   bool last)
{
    return chacha20_poly1305_sg_append(chacha_ctx, data_type, descs, descs_len, last);
}

pufs_status_t pufs_chacha20_poly1305_enc_sg_done(pufs_chacha_ctx *chacha_ctx, uint8_t *tag)
{
    return chacha20_poly1305_sg_done(chacha_ctx, tag);
}

pufs_status_t pufs_chacha20_poly1305_enc_final(pufs_chacha_ctx *chacha_ctx,
                                               uint8_t *out,
                                               uint32_t *outlen,
                                               uint8_t *tag)
{
    return chacha20_poly1305_final(chacha_ctx, out, outlen, tag);
}

pufs_status_t pufs_chacha20_poly1305_enc(uint8_t *out,
                                         uint32_t *outlen,
                                         uint8_t *tag,
                                         pufs_chacha20_poly1305_params_st *params,
                                         const uint8_t *aad,
                                         uint32_t aadlen,
                                         const uint8_t *in,
                                         uint32_t inlen)
{
    pufs_status_t check;
    pufs_chacha_ctx ctx;
    uint32_t temp_outlen = 0;

    if ((check = pufs_chacha20_poly1305_enc_init(&ctx, params)) != SUCCESS || 
        (check = pufs_chacha20_poly1305_enc_update(&ctx, NULL, NULL, aad, aadlen)) != SUCCESS)
        return check;

    if ((check = pufs_chacha20_poly1305_enc_update(&ctx, out, &temp_outlen, in, inlen)) != SUCCESS)
        return check;
    
    *outlen += temp_outlen;

    if ((check = pufs_chacha20_poly1305_enc_final(&ctx, out + *outlen, &temp_outlen, tag)) != SUCCESS)
        return check;
    
    *outlen += temp_outlen;

    return SUCCESS;
}

pufs_status_t pufs_chacha20_poly1305_dec_init(pufs_chacha_ctx *chacha_ctx,
                                              pufs_chacha20_poly1305_params_st *params)
{
    return chacha20_poly1305_init(chacha_ctx, params, false);
}

pufs_status_t pufs_chacha20_poly1305_dec_update(pufs_chacha_ctx *chacha_ctx,
                                                uint8_t *out,
                                                uint32_t *outlen,
                                                const uint8_t *in,
                                                uint32_t inlen)
{
    return chacha20_poly1305_update(chacha_ctx, out, outlen, in, inlen);
}

pufs_status_t pufs_chacha20_poly1305_dec_sg_append(pufs_chacha_ctx *chacha_ctx,
                                                   pufs_chacha_aead_data_t data_type,
                                                   pufs_dma_sg_desc_st *descs,
                                                   uint32_t descs_len,
                                                   bool last)
{
    return chacha20_poly1305_sg_append(chacha_ctx, data_type, descs, descs_len, last);
}

pufs_status_t pufs_chacha20_poly1305_dec_sg_done(pufs_chacha_ctx *chacha_ctx, const uint8_t *tag)
{
    pufs_status_t check;
    uint8_t temp_tag[POLY1305_TAG_SIZE];

    if((check = chacha20_poly1305_sg_done(chacha_ctx, temp_tag)) != SUCCESS)
        return check;
    
    if (memcmp(tag, temp_tag, POLY1305_TAG_SIZE) != 0)
    {
        LOG_DEBUG("%s", "invalid tag");
        return E_VERFAIL;
    }
    return SUCCESS;
}

pufs_status_t pufs_chacha20_poly1305_dec_final(pufs_chacha_ctx *chacha_ctx,
                                               uint8_t *out,
                                               uint32_t *outlen,
                                               const uint8_t* tag)
{
    pufs_status_t check;
    uint8_t temp_tag[POLY1305_TAG_SIZE];
    if((check = chacha20_poly1305_final(chacha_ctx, out, outlen, temp_tag)) != SUCCESS)
        return check;
    
    if (memcmp(tag, temp_tag, POLY1305_TAG_SIZE) != 0)
    {
        LOG_DEBUG("%s", "invalid tag");
        return E_VERFAIL;
    }
    return SUCCESS;
}

pufs_status_t pufs_chacha20_poly1305_dec(uint8_t *out,
                                         uint32_t *outlen,
                                         pufs_chacha20_poly1305_params_st *params,
                                         const uint8_t *aad,
                                         uint32_t aadlen,
                                         const uint8_t *in,
                                         uint32_t inlen,
                                         const uint8_t *tag)
{
    pufs_status_t check;
    pufs_chacha_ctx ctx;
    uint32_t temp_outlen = 0;

    if ((check = pufs_chacha20_poly1305_dec_init(&ctx, params)) != SUCCESS || 
        (check = pufs_chacha20_poly1305_dec_update(&ctx, NULL, NULL, aad, aadlen)) != SUCCESS)
        return check;

    if ((check = pufs_chacha20_poly1305_dec_update(&ctx, out, &temp_outlen, in, inlen)) != SUCCESS)
        return check;
    
    *outlen += temp_outlen;

    if ((check = pufs_chacha20_poly1305_dec_final(&ctx, out + *outlen, &temp_outlen, tag)) != SUCCESS)
        return check;
    
    *outlen += temp_outlen;

    return SUCCESS;
}

pufs_status_t pufs_poly1305(uint8_t *tag, pufs_poly1305_params_st *params,
                            const uint8_t *in, const uint32_t inlen)
{
    uint32_t status, chacha_cfg;
    uint8_t dgst[POLY1305_DGST_SIZE];

    if (tag == NULL || params == NULL)
        return E_ERROR;
    
    if (params->keybits != 256)
    {
        LOG_ERROR("%s", "the key bits must be 256 bits");
        return E_INVALID;
    }

    memset(dgst, 0x0, POLY1305_DGST_SIZE);

    chacha_cfg = chacha_get_cfg(false, false, true, false, false, true);
    chacha_write_cfg(chacha_cfg);
    
    if (params->keytype == SWKEY)
        crypto_write_sw_key((uint8_t *)params->keyaddr, SW_KEY_MAXLEN);

    // initialize dgst
    crypto_write_dgst(dgst, POLY1305_DGST_SIZE);

    dma_write_data_block_config(true, true, true, true, 0);
    dma_write_rwcfg(NULL, in, inlen);
    dma_write_config_0(false, false, false);
    dma_write_key_config_0(params->keytype,
                           ALGO_TYPE_CHACHA,
                           params->keybits,
                           get_key_slot_idx(params->keytype, params->keyaddr));

    dma_write_start();

    while (dma_check_busy_status(&status));

    if (status != 0)
    {
        LOG_ERROR("DMA status 0: 0x%08 PRIx32 \n", status);
        chacha_perror(chacha_regs->status);
        return E_ERROR;
    }

    crypto_read_dgest(tag, POLY1305_TAG_SIZE);

    return SUCCESS;
}