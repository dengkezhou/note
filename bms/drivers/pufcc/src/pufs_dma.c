/**
 * @file      pufs_dma.c
 * @brief     PUFsecurity DMA API implementation
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
#include <malloc.h>
#include <cache.h>
//#include <fcntl.h>
//#include <unistd.h>

#include "pufs_pal.h"
#include "pufs_internal.h"
#include "pufs_rt_internal.h"
#include "pufs_dma_internal.h"

struct pufs_dma pufs_dma = {.regs = NULL};

/*****************************************************************************
 * Internal functions
 ****************************************************************************/
void dma_write_rwcfg(const uint8_t *out, const uint8_t *in, uint32_t len)
{
    pufs_dma.regs->dsc_cfg_2 = len;
    pufs_dma.regs->dsc_cfg_0 = pufs_pal_dma_write_addr(in, len);
    pufs_dma.regs->dsc_cfg_1 = pufs_pal_dma_read_addr(out);
}

#ifndef DMADIRECT
void clear_dma_read(uint32_t len)
{
    memset((void *)pufs_dma.read_virt_addr, 0x0, len);
}
#endif /* DMADIRECT */

pufs_status_t pufs_dump_rand_dma(uint8_t *rand, uint32_t len, bool entropy)
{
    uint32_t val32;
    // check feature
    if ((pufs_dma.regs->feature & DMA_FEATURE_RNG_MASK) == 0)
        return E_UNSUPPORT;

    if (dma_check_busy_status(NULL))
        return E_BUSY;

    dma_write_config_0(true, false, false);
    dma_write_rwcfg(rand, NULL, len); // config DMA descriptor
    dma_write_key_config_0(0, ALGO_TYPE_NONE, 0, 0);

    dma_write_start();

    if (entropy)
        pufs_fre_cont_ctrl(true);
    else
        pufs_rng_cont_ctrl(true);

    while(dma_check_busy_status(&val32));

    if (entropy)
        pufs_fre_cont_ctrl(false);
    else
        pufs_rng_cont_ctrl(false);

    if (val32 != 0)
    {
        LOG_ERROR("DMA status 0: 0x%08lx\n", val32);
        return E_ERROR;
    }

    dma_read_output(rand, len);

    return SUCCESS;
}

void dma_read_output(uint8_t *addr, uint32_t len)
{
    pufs_pal_read_from_dma(addr, len);
}

void dma_write_key_config_0(pufs_key_type_t keytype, pufs_algo_type_t algo, uint32_t size, uint32_t slot_index)
{
    uint32_t value = 0;
    value |= slot_index << DMA_KEY_CFG_0_KEY_IDX_BITS;
    value |= size << DMA_KEY_CFG_0_KEY_SIZE_BITS;
    value |= algo << DMA_KEY_CFG_0_KEY_DST_BITS;
    value |= keytype;
    pufs_dma.regs->key_cfg_0 = value;
}

void dma_write_config_0(bool rng_enable, bool sgdma_enable, bool no_cypt)
{
    uint32_t value = 0;
    if (rng_enable)
        value |= 0x1;
    if (sgdma_enable)
        value |= 0x1 << 1;
    if (no_cypt)
        value |= 0x1 << 2;
    pufs_dma.regs->cfg_0 = value;
}

void dma_write_cl_config_0(uint32_t value)
{
    pufs_dma.regs->cl_cfg_0 = value;
}

void dma_write_data_block_config(bool head, bool tail, bool dn_intrpt, bool dn_pause, uint32_t offset)
{
    uint32_t value = 0;
    if (head)
        value |= 0x1 << DMA_DSC_CFG_4_HEAD_BITS;
    if (tail)
        value |= 0x1 << DMA_DSC_CFG_4_TAIL_BITS;
    if (dn_intrpt)
        value |= 0x1 << DMA_DSC_CFG_4_DN_INTRPT_BITS;
    if (dn_pause)
        value |= 0x1 << DMA_DSC_CFG_4_DN_PAUSE_BITS;
    value |= offset << DMA_DSC_CFG_4_OFFSET_BITS;
    
    pufs_dma.regs->dsc_cfg_4 = value;
}

void dma_write_data_dsc_config(pufs_dma_sg_desc_opts_st *opts, pufs_dma_dsc_attr_st *attr, bool no_crypto)
{
    uint32_t value = 0;
    
    if (opts)
    {
        if (opts->head) 
            value |= 0x1 << DMA_DSC_CFG_4_HEAD_BITS;
        if (opts->tail)
        value |= 0x1 << DMA_DSC_CFG_4_TAIL_BITS;
        if (opts->done_interrupt)
            value |= 0x1 << DMA_DSC_CFG_4_DN_INTRPT_BITS;
        if (opts->done_pause)
            value |= 0x1 << DMA_DSC_CFG_4_DN_PAUSE_BITS;
        if (opts->offset)
            value |= opts->offset << DMA_DSC_CFG_4_OFFSET_BITS;
    }
    if (attr)
    {
        if (no_crypto)
            value |= 0x1 << DMA_DSC_CFG_4_NO_CRYP_BITS;
        if (attr->fix_read_addr)
            value |= 0x1 << DMA_DSC_CFG_4_FIX_READ_BITS;
        if (attr->fix_write_addr)
            value |= 0x1 << DMA_DSC_CFG_4_FIX_WRITE_BITS;
        if (attr->read_protect)
            value |= 0x1 << DMA_DSC_CFG_4_READ_PROT_BITS;
        if (attr->write_protect)
            value |= 0x1 << DMA_DSC_CFG_4_WRITE_PROT_BITS;
    }
    pufs_dma.regs->dsc_cfg_4 = value;
}

void dma_write_start(void)
{
    itcs_dcache_flush();
    pufs_dma.regs->start = 0x1;
}

bool dma_check_busy_status(uint32_t *status)
{
    uint32_t stat = pufs_dma.regs->status_0;
    bool busy = (stat & DMA_STATUS_0_BUSY_MASK) != 0;
    
    if (status != NULL)
        *status = stat;

    return busy;
}

// FIXME: change to use PAL APIs
pufs_status_t pufs_dma_read_write(uint8_t *out, uint32_t outlen,
                                  const uint8_t *data, const uint32_t data_length,
                                  pufs_dma_dsc_attr_st *attr)
{
    uint32_t status;
    pufs_dma_sg_desc_opts_st opts = {.head = false, .tail = false, .done_interrupt = true, .done_pause = true, .offset = 0x0};

#ifdef BAREMETAL
    UNUSED(outlen);
#endif

    if (dma_check_busy_status(NULL))
        return E_BUSY;
    
    dma_write_config_0(false, false, false);
    dma_write_rwcfg(out, data, data_length);
    dma_write_key_config_0(0, ALGO_TYPE_NONE, 0, 0);
    dma_write_data_dsc_config(&opts, attr, true);

    dma_write_start();

    while(dma_check_busy_status(&status));

    if (status != 0)
    {
        LOG_ERROR("DMA status 0: 0x%08lx\n", status);
        return E_ERROR;
    }
    dma_read_output(out, outlen);

    return SUCCESS;
}

// FIXME: change to use PAL APIs
pufs_status_t pufs_dma_read_write_sg( pufs_dma_sg_desc_st *descs)
{
    pufs_dma_sg_internal_desc_st *desc;
    pufs_dma_sg_desc_opts_st opts = {.head = false, .tail = false, .done_interrupt = true, .done_pause = true, .offset = 0x0, .no_crypto = true};

    desc = dma_sg_new_data_descriptor();
    dma_sg_desc_write_addr(desc, descs->write_addr, descs->read_addr, descs->length);
    dma_sg_desc_write_dsc_config(desc, &descs->attr, &opts);
    dma_sg_desc_write_key_config(desc, 0, ALGO_TYPE_NONE, 0, 0);
    dma_sg_desc_write_crypto_config(desc, 0x0, 0x0);    
    dma_write_data_dsc_config(NULL, NULL, true);
    dma_sg_desc_append_to_list(desc);

    return pufs_dma_sg_start();
}

/*****************************************************************************
 * API functions
 ****************************************************************************/
pufs_status_t pufs_dma_module_init(uintptr_t dma_offset)
{
    pufs_status_t ret;
    pufs_dma.regs = (struct pufs_dma_regs *)(pufs_context.base_addr + dma_offset);
    if((ret = version_check(DMA_VERSION, pufs_dma.regs->version)) != SUCCESS)
        return ret;
    if (pufs_pal_config_dma() < 0)
        return E_FIRMWARE;

    return SUCCESS;
}
void pufs_dma_set_dsc_attr(pufs_dma_dsc_attr_st *attr)
{
    uint32_t value = 0;
    if (attr->fix_read_addr)
        value |= 1 << DMA_DSC_CFG_4_FIX_READ_BITS;
    if (attr->fix_write_addr)
        value |= 1 << DMA_DSC_CFG_4_FIX_WRITE_BITS;
    value |= attr->read_protect << DMA_DSC_CFG_4_READ_PROT_BITS;
    value |= attr->write_protect << DMA_DSC_CFG_4_WRITE_PROT_BITS;

    pufs_dma.regs->dsc_cfg_4 |= value;
}

void pufs_dma_module_release(void)
{
    // TODO: relase mmap for DMA addresses
}
