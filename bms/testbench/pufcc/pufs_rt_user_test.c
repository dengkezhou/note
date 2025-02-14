/**
 * @file      pufs_rt_user.c
 * @brief     PUFsecurity PUFrt user test cases
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
#include <cache.h>

#include "pufs_pal.h"
#include "pufs_internal.h"
#include "pufs_rt.h"
#include "pufs_rt_internal.h"
#include "pufs_rt_test.h"
#include "pufs_memory_map.h"
#include "pufs_test_common.h"

// fixme: find a better way to handle time issue across different platform
//#define ENABLE_TIME // toggle this macro to in/exclude time-related code
#ifdef ENABLE_TIME
#include <sys/time.h>
#endif /*ENABLE_TIME*/

/*****************************************************************************
 * Static functions
 ****************************************************************************/
/**
 * OTP read/write test
 */
static pufs_status_t rt_otp_read_write_test(void)
{
    pufs_status_t check;
    uint32_t r[OTP_LEN/4], w[OTP_LEN/4], n[OTP_LEN/4];
    memset(w, PUFRT_VALUE8(0xff), OTP_LEN);

    // Read old OTP value
    if ((check = pufs_read_otp((uint8_t*)r, OTP_LEN, 0)) != SUCCESS)
        return check;

    // Randomly choose a test value
    for (int i=OTP_LEN/4-1; i>=0; i--)
    {
        // Find the one which is not all zeros for OTP read/write test
        if (r[i] == PUFRT_VALUE32(0))
            continue;

        // Generate test pattern
        if ((check = pufs_rand((uint8_t*)&(w[i]), 1)) != SUCCESS)
            return check;
    }

    // Write and read test
    if ((check = pufs_program_otp((const uint8_t*)w, OTP_LEN, 0)) != SUCCESS)
        return check;
    if ((check = pufs_read_otp((uint8_t*)n, OTP_LEN, 0)) != SUCCESS)
        return check;
    for (int i=OTP_LEN/4-1; i>=0; i--)
    {
        if (PUFRT_VALUE32(n[i]) != (PUFRT_VALUE32(r[i]) & PUFRT_VALUE32(w[i])))
            return E_VERFAIL;
    }

    return SUCCESS;
}

/*****************************************************************************
 * User-mode resettable test functions
 ****************************************************************************/
/**
 * Post-masking test
 */
pufs_status_t pufs_rt_post_mask_test(void)
{
    pufs_status_t check;
    uint32_t lotp[OTP_LEN / WORD_SIZE], rotp[OTP_LEN / WORD_SIZE];
    uint32_t status;

    // Check PMK are clear
    if ((rt_regs->otp_psmsk[0] != 0) ||
        (rt_regs->otp_psmsk[1] != 0) ||
        (rt_regs->puf_psmsk != 0))
    {
        LOG_DEBUG("%s", "PMK is not all 0x00000000, skipped\n");
        return SUCCESS;
    }

    if((check = rt_otp_read_write_test()) != SUCCESS)
        return check;

    if ((check = pufs_read_otp((uint8_t*)lotp, OTP_LEN, 0)) != SUCCESS)
        return check;

    // set and lock post masking
    if ((check = pufs_post_mask(MASK_BIT(OTPKEY_25))) != SUCCESS)
    {
        LOG_ERROR("%s", "failed to set post mask");
        return check;
    }
    for (uint32_t i = 25*(OTP_KEY_LEN/WORD_SIZE); i < 26*(OTP_KEY_LEN/WORD_SIZE);i++)
        lotp[i] = PUFRT_VALUE32(0x0); //post-masked

    // check OTP post-masking
    if ((check = pufs_read_otp((uint8_t*)rotp, OTP_LEN, 0)) != SUCCESS)
        return check;

    for (uint32_t i = 0; i < (OTP_LEN / WORD_SIZE); i++)
    {
        if (lotp[i] != rotp[i])
        {
            LOG_ERROR("%s", "OTP%lu is wrong");
            return E_VERFAIL;
        }
    }

    reg_sw_reset_write();
    if ((status = wait_status()) != 0x0)
    {
        LOG_ERROR("the expected status after sw_reset is %lu"
                  " but we got %lu", (uint32_t)0x0, status);
        return E_ERROR;
    }
    return SUCCESS;
}

/*****************************************************************************
 * Test functions
 ****************************************************************************/
/**
 * Deep standby test
 */
pufs_status_t pufs_rt_pdstb_test(void)
{
   pufs_status_t check;
    uint32_t test_value;

    // Read OTP values
    uint8_t otp1[OTP_LEN], otp2[OTP_LEN];
    check = pufs_read_otp(otp1, OTP_LEN, 0);
    if (check != SUCCESS)
    {
        LOG_ERROR("%s", "failed to read OTP");
        goto cleanup;
    }

    if ((check = pufs_rand((uint8_t*)&test_value, 1)) != SUCCESS)
    {
        LOG_ERROR("%s", "failed to get random number");
        goto cleanup;
    }

    rt_write_pdstb(true);

    // Write OTP, but should not take effect
    memset(otp2, PUFRT_VALUE8(test_value), OTP_LEN);
    if ((check = pufs_program_otp(otp2, OTP_LEN, 0)) != SUCCESS)
    {
        LOG_ERROR("%s", "fail to complete otp program operation");
        goto cleanup;
    }

    // Read OTP value
    uint32_t r;
    for (pufs_otp_addr_t i=0; i<OTP_LEN; i+=4)
    {
        if ((check = pufs_read_otp((uint8_t*)&r, 4, i)) != SUCCESS)
        {
            LOG_ERROR("%s", "failed to read OTP");
            goto cleanup;
        }
        if ((check = (r == be2le(0x00000001)) ? SUCCESS : E_ERROR) != SUCCESS)
        {
            LOG_ERROR("%s", "the OTP value should be 0x00000001 in standby");
            goto cleanup;
        }
    }

cleanup:
    rt_write_pdstb(false);

    if (check != SUCCESS)
        return check;

    // Read OTP values
    if ((check = pufs_read_otp(otp2, OTP_LEN, 0)) != SUCCESS)
    {
        LOG_ERROR("%s", "failed to read OTP");
        return check;
    }

    if (memcmp(otp1, otp2, OTP_LEN) != 0)
    {
        LOG_ERROR("%s", "OTP section isn't restored.");
        return E_ERROR;
    }    
    
    return check;
}
/**
 * Read mode test
 */
pufs_status_t pufs_rt_read_mode_test(void)
{
    pufs_status_t check;

    rt_write_read_mode(RD);
    LOG_DEBUG("%s", "setting read mode = RD");

    // Read OTP values
    uint8_t otp1[OTP_LEN], otp2[OTP_LEN];
    check = pufs_read_otp(otp1, OTP_LEN, 0);

    for (uint32_t i=1; i<=2; i++)
    {
        rt_write_read_mode((pufs_read_mode_t)i);
        LOG_DEBUG("setting read mode = %lu ... done\n", i);

        // Read OTP values
        if ((check = pufs_read_otp(otp2, OTP_LEN, 0)) != SUCCESS)
        {
            LOG_ERROR("%s", "failed to reading OTP");
            goto cleanup;
        }
        check = (memcmp(otp1, otp2, OTP_LEN) == 0) ? SUCCESS : E_ERROR;
        if (check != SUCCESS)
        {
            LOG_ERROR("%s", "failed to checking OTP read");
            goto cleanup;
        }
    }

cleanup:
    rt_write_read_mode(RD);
    return check;
}

pufs_status_t pufs_rt_rand_read_test(void)
{
    pufs_status_t check = SUCCESS;
    uint32_t r0 = 0, r1;

    if (rt_regs->rn_status != 0)
    {
        LOG_ERROR("%s", "failed to rng health check");
        return E_ERROR;
    }

    for (uint32_t i=0; i<100; i++)
    {
        if ((check = pufs_rand((uint8_t*)&r1, 1)) != SUCCESS)
            goto cleanup;
        else if ((r1 == 0) || (r1 == r0))
        {
            check = E_ERROR;
            goto cleanup;
        }
        r0 = r1;
    }
    check = SUCCESS;
cleanup:
    return check;
}

// Note: run rng check before this test.
pufs_status_t pufs_rt_rand_clk_test(void)
{
    pufs_status_t check;
    uint32_t dead_value, rng;
    rt_write_rngclk(false);

    pufs_rand((uint8_t *)&dead_value, 1);

    for (uint32_t num = 0; num < 256; num++)
    {
        pufs_rand((uint8_t *)&rng, 1);
        if (rng != dead_value)
            return E_ERROR;
    }

    rt_write_rngclk(true);

    if ((check = pufs_rt_rand_read_test()) != SUCCESS)
        return check;

    return SUCCESS;
}

pufs_status_t pufs_rt_auto_load_test(void)
{
    uintptr_t addr;
    const uint32_t size = 1024, test_value = 0x00330033;
    uint32_t *autoldbits = NULL;
    uint32_t status = 0;

    if(pufs_pal_mmap(&addr, PUFS_RT_AUTOLOAD_BASE, size) < 0)
    {
        LOG_ERROR("%s", "failed to allocate a space");
        return E_FIRMWARE;
    }

    autoldbits = (uint32_t *)addr;
    // The size of autoldbits register is 8 which is mapped to the first 8 reigsters of OTP. 
    for (uint32_t i = 0; i < 8; i++)
        rt_regs->otp[i] |= test_value;
    
    // we must reset reigsters to make autoldbits works.
    reg_sw_reset_write();
    if ((status = wait_status()) != 0x0)
    {
        LOG_ERROR("the expected status after sw_reset is %lu"
                  " but we got %lu", (uint32_t)0x0, status);
        return E_ERROR;
    }

    for (uint32_t i = 0; i < 8; i++)
    {
        if (autoldbits[i] != rt_regs->otp[i])
        {
            LOG_ERROR("the expected value is %lu but we got %lu", rt_regs->otp[i], autoldbits[i]);
            return E_VERFAIL;
        }
    }
    return SUCCESS;
}

static pufs_status_t rt_tcm_check(uint32_t *tcm_base, uint32_t otp_value)
{
    // low 16-bit
    if (tcm_base[0] != (otp_value & 0xFFFF))
    {
        LOG_ERROR("the expected value is %lu but we got %lu", otp_value & 0xFFFF, tcm_base[0]);
        return E_VERFAIL;
    }
    // high 16-bit
     if (tcm_base[1] != ((otp_value & 0xFFFF0000) >> 16))
    {
        LOG_ERROR("the expected value is %lu but we got %lu", (otp_value & 0xFFFF0000) >> 16, tcm_base[1]);
        return E_VERFAIL;
    }

    return SUCCESS;
}

pufs_status_t pufs_rt_tcm_test(void)
{
    uintptr_t addr;
    uint32_t size = 1024, test_value = 0x0C0C, *tcm_base, otp_value = 0x0;

    if(pufs_pal_mmap(&addr, PUFS_RT_TCM_BASE, size) < 0)
    {
        LOG_ERROR("%s", "failed to allocate a space");
        return E_FIRMWARE;
    }

    tcm_base = (uint32_t *)addr;

    // TCM read/write OTP is started from index 8 of OTP area.
    otp_value = rt_regs->otp[8];
    
    // STEP 1: read OTP from TCM protocol
    if(rt_tcm_check(tcm_base, otp_value) != SUCCESS)
        return E_VERFAIL;

    // STEP 2: write OTP from TCM protocol
    tcm_base[0] |= test_value;
    tcm_base[1] |= test_value;

    otp_value = rt_regs->otp[8];
    if(rt_tcm_check(tcm_base, otp_value) != SUCCESS)
        return E_VERFAIL;

    return SUCCESS;
}

/**
 * Set OTP rwlck test
 */
static pufs_status_t pufs_set_otp_rwlck(pufs_otp_lock_t lock)
{
    pufs_status_t check;

    // Set OTP rwlck test on OTP words
    for (pufs_otp_addr_t i=0; i<OTP_LEN; i+=4)
    {
        // Set OTP rwlck
        if ((check = pufs_lock_otp(i, 4, lock)) != SUCCESS)
            return check;

        // Read OTP rwlck and check
        if (pufs_get_otp_rwlck(i) != lock)
            return E_DENY;
    }

    return SUCCESS;
}

/*****************************************************************************
 * User-mode harmful test functions
 ****************************************************************************/
/**
 * OTP read/write behavior test
 */
pufs_status_t pufs_rt_otp_read_write_test(void)
{
    pufs_status_t check;

    if ((check = rt_otp_read_write_test()) != SUCCESS ||
        (check = rt_otp_read_write_test()) != SUCCESS)
        return check;
    
    return SUCCESS;
}
/**
 * OTP rwlck setting and functionality test
 */
pufs_status_t pufs_rt_otp_rwlck_test(void)
{
    uint8_t otp1[OTP_LEN], otp2[OTP_LEN];
    pufs_status_t check;

    // Check RW access
    if ((check = pufs_set_otp_rwlck(RW)) != SUCCESS)
    {
        printf("failed to set OTP RW\n");
        return check;
    }

    if ((check = rt_otp_read_write_test()) != SUCCESS)
    {
        printf("failed to pass OTP read write test\n");
        return check;
    }

    // Read OTP values
    if ((check = pufs_read_otp(otp1, OTP_LEN, 0)) != SUCCESS)
    {
        printf("failed to read OTP value\n");
        return check;
    }

    // Set RO access
    if ((check = pufs_set_otp_rwlck(RO)) != SUCCESS)
    {
        printf("failed to set OTP RO\n");
        return check;
    }

    // Write OTP to zeroes (success is not expected due to RO access)
    memset(otp2, PUFRT_VALUE8(0), OTP_LEN);
    pufs_program_otp(otp2, OTP_LEN, 0);

    // Read OTP values
    if ((check = pufs_read_otp(otp2, OTP_LEN, 0)) != SUCCESS)
    {
        printf("failed to read OTP value\n");
        return check;
    }

    if (memcmp(otp1, otp2, OTP_LEN) != 0)
    {
        printf("RO OTP test failed\n");
        return E_VERFAIL;
    }

    // Set NA access
    if ((check = pufs_set_otp_rwlck(NA)) != SUCCESS)
    {
        printf("failed to set OTP NA\n");
        return check;
    }

    // Read OTP values
    if ((check = pufs_read_otp(otp1, OTP_LEN, 0)) != SUCCESS)
    {
        printf("failed to read OTP value\n");
        return check;
    }

    // Check NA access functionality
    memset(otp2, PUFRT_VALUE8(0), OTP_LEN);

    if (memcmp(otp1, otp2, OTP_LEN) != 0)
    {
        printf("NA OTP test failed\n");
        return E_VERFAIL;
    }

    return SUCCESS;
}

pufs_status_t pufs_rt_ptr_read_write_test(void)
{
    uint32_t rand[8];
    pufs_rand((uint8_t *)&rand, 8);

    for (uint32_t index = 0; index < 8; index += 2)
        rt_regs->ptr[index] = rand[index];
    for (uint32_t index = 1; index < 8; index += 2)
        rt_regs->ptr[index] = rand[index];
    for (uint32_t index = 1; index < 8; ++index)
    {
        if (rt_regs->ptr[index] != rand[index])
        {
            LOG_ERROR("expected value of ptr[%lu] 0x%08lx but got 0x%08lx", index, rand[index], rt_regs->ptr[index]);
            return E_VERFAIL;
        }
    }
    return SUCCESS;
}

// Note: check HMC_TYPE before run the test (0x02ac, [19:16] = 7)
pufs_status_t pufs_rt_ptc_read_write_test(void)
{
    uint32_t ptc_page, index, value;
    for (ptc_page = 0; ptc_page < 2; ptc_page++)
    {
        value = rt_regs->cfg;
        value = (value & (~PTM_CFG_REG_PTC_PAGE_MASK)) |
                (ptc_page << PTM_CFG_REG_PTC_PAGE_BITS);
        rt_regs->cfg = value;

        for (index = 0; index < 16; index++)
        {
            if (rt_regs->ptc[index] != 0x0)
            {
                LOG_ERROR("1 feature(0x%08lx) cfg(0x%08lx) original ptc[%lu:%lu] value 0x%08lx but got 0x%08lx", rt_regs->feature, rt_regs->cfg, ptc_page, index, (uint32_t)0x0, rt_regs->ptc[index]);
                return E_VERFAIL;
            }
        }
    }
    for (ptc_page = 0; ptc_page < 2; ptc_page++)
    {
        value = rt_regs->cfg;
        value = (value & (~PTM_CFG_REG_PTC_PAGE_MASK)) |
                (ptc_page << PTM_CFG_REG_PTC_PAGE_BITS);
        rt_regs->cfg = value;

        for (index = 0; index < 16; index++)
        {
            if (rt_regs->ptc[index] != 0x0)
            {
                LOG_ERROR("2 feature(0x%08lx) cfg(0x%08lx) original ptc[%lu:%lu] value 0x%08lx but got 0x%08lx", rt_regs->feature, rt_regs->cfg, ptc_page, index, (uint32_t)0x0, rt_regs->ptc[index]);
                return E_VERFAIL;
            }
            rt_regs->ptc[index] = 0x1;
            if (rt_regs->ptc[index] != 0x1)
            {
                LOG_ERROR("expected ptc[%lu:%lu] value 0x%08lx but got 0x%08lx", ptc_page, index, (uint32_t)0x1, rt_regs->ptc[index]);
                return E_VERFAIL;
            }
        }
    }
    return SUCCESS;
}
// FIXME: find a better way to handle timing issue
pufs_status_t pufs_rt_rand_resume_test(void)
{
    pufs_status_t check = SUCCESS;
#ifdef ENABLE_TIME
    struct timeval start_time, end_time;
#endif
    uint32_t dead_value = 0xdeaddead, rng;
    bool rules[] = {
    //  pdstd  rngclken rngresume RN_is_Dead
        true,  true,    false,    false,
        true,  true,    true,     true,
        true,  false,   false,    true,
        true,  false,   true,     true,
        false, true,    false,    false,
        false, true,    true,     true,
        false, false,   false,    true,
        false, false,   true,     true,
    };

    for (uint32_t i = 0;i+3 < sizeof(rules);i+=4)
    {
        rt_write_pdstb(rules[i]);
        rt_write_rngclk(rules[i+1]);
        rt_write_rng_resume(rules[i+2]);
#ifdef ENABLE_TIME
        gettimeofday(&start_time, NULL);
#endif
        if ((check = pufs_rand((uint8_t*)&rng, 1) != SUCCESS))
            goto cleanup;

        if (rules[i+3] && rng != dead_value)
        {
            check = E_VERFAIL;
            goto cleanup;
        }

        if (!rules[i+3] && (check = pufs_rt_rand_read_test()) != SUCCESS)
            goto cleanup;
#ifdef ENABLE_TIME
        gettimeofday(&end_time, NULL);
        while (end_time.tv_usec - start_time.tv_usec < 20)  gettimeofday(&end_time, NULL);
#endif
    }

cleanup:
#ifdef ENABLE_TIME
    gettimeofday(&end_time, NULL);
    while (end_time.tv_usec - start_time.tv_usec < 20)  gettimeofday(&end_time, NULL);
#endif
    rt_write_pdstb(false);
    rt_write_rngclk(true);
    rt_write_rng_resume(false);

    return check;
}

