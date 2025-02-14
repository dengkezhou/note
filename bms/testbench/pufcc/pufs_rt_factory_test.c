/**
 * @file      pufs_rt_factory.c
 * @brief     PUFsecurity PUFrt factory test cases
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

#include "pufs_test_common.h"
#include "pufs_internal.h"
#include "pufs_rt_regs.h"
#include "pufs_rt_internal.h"

/*****************************************************************************
 * Structures
 ****************************************************************************/
struct ptm_test_pattern {
    volatile uint32_t *addr;
    uint32_t cmd;
    uint32_t status_mask;
};

/*****************************************************************************
 * Static functions
 ****************************************************************************/
static uint32_t ptm_cmd_test(uint32_t ntests,
                             const struct ptm_test_pattern* tp)
{
    for (uint32_t i=0; i<ntests; i++)
    {
        if (tp[i].addr == NULL)
            continue;

        *(tp[i].addr) = tp[i].cmd;
        // Only check related bits
        if ((wait_status() & tp[i].status_mask) != tp[i].status_mask)
        {
            LOG_ERROR("Expect status 0x%08lx, but got 0x%08lx",
                      tp[i].status_mask, wait_status());
            return i+1; // 0 is reserved for SUCCESS
        }
    }
    return 0;
}

static pufs_status_t rt_write_set_pin_repair_test(void)
{
    rt_regs->set_pin = PA_REP_1;
    wait_status();

    rt_regs->set_pin = PA_REP_0;
    wait_status();

    for (uint32_t i = 0; i < OTP_LEN / 4; i++)
    {
        if (rt_regs->otp[i] != PUFRT_VALUE32(0xFFFFFFFF))
        {
            LOG_ERROR("%s", "OTP should be init state");
            return E_VERFAIL;
        }
    }
    return SUCCESS;
}

/*****************************************************************************
 * Unrecoverable test functions
 ****************************************************************************/
/**
 * PTM status wrong test
 */
pufs_status_t pufs_rt_ptm_status_wrong_test(void)
{
    uint32_t e;
    struct ptm_test_pattern ptmtp[] =
    {
        { &rt_regs->set_pin, 0xff, 0x00000008 },
        { &rt_regs->auto_repair, 0xff, 0x00000008 },
        { &rt_regs->ini_off_chk, 0xff, 0x00000008 },
        { &rt_regs->repair_pgn, 0xff, 0x00000008 },
        { &rt_regs->puf_qty_chk, 0xff, 0x00000008 },
        { &rt_regs->puf_enroll, 0xff, 0x00000008 },
        { &rt_regs->puf_zeroize, 0xff, 0x00000008 },
        { &rt_regs->otp_zeroize, 0xff, 0x00000008 },
        { &rt_regs->set_flag, 0xff, 0x0000008 },
    };
    
    if ((e = ptm_cmd_test(TCPARAM(struct ptm_test_pattern, ptmtp))) != 0)
    {
        LOG_ERROR(" %ld", e);
        return E_ERROR;
    }
    return SUCCESS;
}
/**
 * PTM status warning test
 * This test focus on the warning of repetition of cmd
 */
pufs_status_t pufs_rt_ptm_status_warning_test(void)
{
    uint32_t e, ntest;
    struct ptm_test_pattern ptmtp[] =
    {
        { &rt_regs->puf_enroll, 0xa7, 0x00000000 }, // first enroll
        { &rt_regs->puf_enroll, 0xa7, 0x00000004 },
        { &rt_regs->auto_repair, 0xe9, 0x00000000 }, // raise pif0_repair
        { &rt_regs->auto_repair, 0xe9, 0x00000004 },
        { &rt_regs->repair_pgn, 0xf0, 0x00000004 },
        { &rt_regs->puf_zeroize, 0x4b, 0x00000000 }, // first zeroize
        { &rt_regs->puf_zeroize, 0x4b, 0x00000004 },
        { &rt_regs->puf_zeroize, 0xad, 0x00000000 }, // first zeroize
        { &rt_regs->puf_zeroize, 0xad, 0x00000004 },
        { &rt_regs->puf_zeroize, 0xd2, 0x00000000 }, // first zeroize
        { &rt_regs->puf_zeroize, 0xd2, 0x00000004 },
        { &rt_regs->puf_zeroize, 0x34, 0x00000000 }, // first zeroize
        { &rt_regs->puf_zeroize, 0x34, 0x00000004 },
        { &rt_regs->otp_zeroize, 0x80, 0x00000000 }, // first zeroize
        { &rt_regs->otp_zeroize, 0x80, 0x00000004 },
        { &rt_regs->set_flag, PGMPRT_FLAG, 0x00000000, }, // raise pgmprt
        { &rt_regs->set_flag, PGMPRT_FLAG, 0x00000004, },
        { &rt_regs->set_flag, PUFLCK_FLAG, 0x00000000, }, // raise puflck
        { &rt_regs->set_flag, PUFLCK_FLAG, 0x00000004, },
        { &rt_regs->set_flag, OTPLCK_FLAG, 0x00000000, }, // raise otplck
        { &rt_regs->set_flag, OTPLCK_FLAG, 0x00000004, },
        { &rt_regs->set_flag, SHFREN_FLAG, 0x00000000, }, // raise shfren
        { &rt_regs->set_flag, SHFREN_FLAG, 0x00000004, },
        { &rt_regs->set_flag, SHFWEN_FLAG, 0x00000000, }, // raise shdwen
        { &rt_regs->set_flag, SHFWEN_FLAG, 0x00000004, },
        { &rt_regs->set_flag, TMLCK_FLAG, 0x00000000, }, // lock tmlck
        { &rt_regs->set_flag, TMLCK_FLAG, 0x00000004, },
    };
    ntest = sizeof(ptmtp) / sizeof(struct ptm_test_pattern);

    if ((rt_regs->feature & CFG_FEATURES_RR_MASK) == 0x0)
    {
        for (uint32_t i = 0;i < ntest;i++)
        {
            if (ptmtp[i].addr != NULL &&
                (ptmtp[i].addr == &rt_regs->auto_repair ||
                ptmtp[i].addr == &rt_regs->repair_pgn))
                ptmtp[i].addr = NULL; //skip
        }
    }

    if ((rt_regs->feature & CFG_FEATURES_OTP_ZERO_MASK) == 0x0)
    {
        for (uint32_t i = 0;i < ntest;i++)
        {
            if (ptmtp[i].addr != NULL &&
                ptmtp[i].addr == &rt_regs->otp_zeroize)
                ptmtp[i].addr = NULL; //skip
        }
    }

    if ((e = ptm_cmd_test(ntest, ptmtp)) != 0)
    {
        LOG_ERROR(" %ld", e);
        return E_ERROR;
    }
    return SUCCESS;
}
/**
 * PTM status forbid test
 * This test focus on the forbiddance of cmd when tmlck is locked
 */
pufs_status_t pufs_rt_ptm_status_forbid_test(void)
{
    uint32_t e, ntest;
    struct ptm_test_pattern ptmtp[] =
    {
        { &rt_regs->set_pin, PUFORG_0, 0x00000010 },
        { &rt_regs->set_pin, PUFORG_1, 0x00000010 },
        { &rt_regs->set_pin, PA_REP_0, 0x00000010 },
        { &rt_regs->set_pin, PA_REP_1, 0x00000010 },
        { &rt_regs->auto_repair, 0xe9, 0x00000010 },
        { &rt_regs->ini_off_chk, 0x00, 0x00000010 },
        { &rt_regs->repair_pgn, 0xf0, 0x00000010 },
        { &rt_regs->puf_enroll, 0xa7, 0x00000010 },
        { &rt_regs->puf_zeroize, 0x4b, 0x00000010 },
        { &rt_regs->puf_zeroize, 0xad, 0x00000010 },
        { &rt_regs->puf_zeroize, 0xd2, 0x00000010 },
        { &rt_regs->puf_zeroize, 0x34, 0x00000010 },
        { &rt_regs->set_flag, PGMPRT_FLAG, 0x00000010 },
        { &rt_regs->set_flag, TMLCK_FLAG, 0x00000010 },
        { &rt_regs->set_flag, PUFLCK_FLAG, 0x00000010 },
        { &rt_regs->set_flag, OTPLCK_FLAG, 0x00000010 },
        { &rt_regs->set_flag, SHFREN_FLAG, 0x00000010 },
        { &rt_regs->set_flag, SHFWEN_FLAG, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x80, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x81, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x82, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x83, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x84, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x85, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x86, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x87, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x88, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x89, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x8a, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x8b, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x8c, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x8d, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x8e, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x8f, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x90, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x91, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x92, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x93, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x94, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x95, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x96, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x97, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x98, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x99, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x9a, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x9b, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x9c, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x9d, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x9e, 0x00000010 },
        { &rt_regs->otp_zeroize, 0x9f, 0x00000010 },
    };
    ntest = sizeof(ptmtp) / sizeof(struct ptm_test_pattern);

    if ((rt_regs->feature & CFG_FEATURES_RR_MASK) == 0x0)
    {
        for (uint32_t i = 0;i < ntest;i++)
        {
            if (ptmtp[i].addr == &rt_regs->auto_repair ||
                ptmtp[i].addr == &rt_regs->repair_pgn)
                ptmtp[i].addr = NULL; //skip
        }
    }

    if ((rt_regs->feature & CFG_FEATURES_OTP_ZERO_MASK) == 0x0)
    {
        for (uint32_t i = 0;i < ntest;i++)
        {
            if (ptmtp[i].addr == &rt_regs->otp_zeroize)
                ptmtp[i].addr = NULL; //skip
        }
    }

    if ((e = ptm_cmd_test(TCPARAM(struct ptm_test_pattern, ptmtp))) != 0)
    {
        LOG_ERROR(" %ld", e);
        return E_ERROR;
    }
    return SUCCESS;
}

pufs_status_t pufs_rt_uid_zeroize_test(void)
{
    pufs_status_t check;
    uint32_t pif_zeroize = 0xffffffff;
    uint32_t expect[8];
    pufs_uid_st  uid;
    memset(expect, PUFRT_VALUE8(0x0), 32);

    rt_write_enroll();
    for (pufs_rt_slot_t slot = PUFSLOT_0; slot <= PUFSLOT_3;slot++)
    {
        uint32_t slot_number = (uint32_t)slot;
        if ((check = pufs_zeroize(slot)) != SUCCESS)
        {
            LOG_ERROR("failed to zeroize PUF%lu", slot_number);
            return check;
        }

        pufs_get_uid(&uid, slot);
        if (memcmp(uid.uid, expect, OTP_KEY_LEN) != 0)
        {
            LOG_ERROR("PUF%lu is not zeroized", slot_number);
            return E_VERFAIL;
        }

        pif_zeroize &= (0xfffffffc << (slot_number*2));
        if (rt_regs->pif[12] != PUFRT_VALUE32(pif_zeroize))
        {
            LOG_ERROR("Zeroization flag of PUF%lu is incorrect", slot_number);
            return E_VERFAIL;
        }
    }
    return SUCCESS;
}

pufs_status_t pufs_rt_otp_zeroize_test(void)
{
    pufs_status_t check;
    uint32_t pif14_otp_zeroize = 0xffffffff;
    uint32_t lotp[8], expect[8];
    memset(expect, PUFRT_VALUE8(0x0), 32);

    for (pufs_rt_slot_t slot = OTPKEY_0; slot <= OTPKEY_15;slot++)
    {
        uint32_t slot_number = (uint32_t)slot - PUFSLOT_3 - 1;
        if ((check = pufs_zeroize(slot)) != SUCCESS)
        {
            LOG_ERROR("failed to zeroize OTP%lu", slot_number);
            return check;
        }

        pufs_read_otp((uint8_t*)lotp, OTP_KEY_LEN, slot_number*OTP_KEY_LEN);
        if (memcmp(lotp, expect, OTP_KEY_LEN) != 0)
        {
            LOG_ERROR("OTP%lu is not zeroized", slot_number);
            return E_VERFAIL;
        }

        pif14_otp_zeroize &= (0xfffffffc << (slot_number*2));
        if (rt_regs->pif[14] != PUFRT_VALUE32(pif14_otp_zeroize))
        {
            LOG_ERROR("Zeroization flag of OTP%lu is incorrect", slot_number);
            return E_VERFAIL;
        }
    }
    return SUCCESS;
}

pufs_status_t pufs_rt_ptm_puf_enroll_test(void)
{
    uint32_t status;
    rt_write_enroll();
    if ((status = wait_status()) != 0x0)
        return E_ERROR;

    for (uint32_t index = 0; index < 64; index++)
    {
        if ((rt_regs->puf[index] == 0xFFFFFFFF || rt_regs->puf[index] == 0x0))
            return E_VERFAIL;
    }
    return SUCCESS;
}

// OTP MUST be the initial state
pufs_status_t pufs_rt_auto_repair_test(void)
{
    uint32_t status;

    for (uint32_t i = 0; i < OTP_LEN / 4; i++)
    {
        if (rt_regs->otp[i] != PUFRT_VALUE32(0xFFFFFFFF))
        {
            LOG_ERROR("%s", "OTP should be init state");
            return E_VERFAIL;
        }
    }

    rt_regs->otp[107] = 0xEFFFFFFE;
    rt_regs->otp[195] = 0xFFEFFEFF;

    rt_regs->auto_repair = 0xE9;
    if ((status = wait_status()) != 0x200)
    {
        LOG_ERROR("expected status after auto_repair is 0x200, "
                  "but got %lu", status);
        return E_ERROR;
    }

    if (rt_regs->repair_reg != 0x2)
    {
        LOG_ERROR("expected repair cells is 2, but got %lu",
                   rt_regs->repair_reg);
        return E_ERROR;
    }

    return rt_write_set_pin_repair_test();
}

// OTP MUST be the initial state
pufs_status_t pufs_rt_repair_program_test(void)
{
    uint32_t status;
    pufs_status_t check;
    
    rt_regs->otp[0] = 0xFFEFEEEF;
    rt_regs->otp[3] = 0xEFFFFFFE;
    rt_regs->otp[33] = 0xFFEFEFEF;
    rt_regs->otp[91] = 0xFFEFFEFF;

    rt_regs->ini_off_chk = 0x0;
    wait_status();
    
    // excpected failed count of OTP cells is 4
    if (rt_regs->repair_reg != 0x4)
    {
        LOG_ERROR("excpected failed count of OTP cells is 4, but got %lu", rt_regs->repair_reg);
        return E_ERROR;
    }

    rt_regs->repair_pgn = 0xF0;
    wait_status();

    if (rt_regs->repair_reg != 0x4)
    {
        LOG_ERROR("excpected repair cells is 4, but got %lu", rt_regs->repair_reg);
        return E_ERROR;
    }

    check = rt_write_set_pin_repair_test();
    if (check != SUCCESS)
        return check;

    rt_regs->ini_off_chk = 0x5A;
    if ((status = wait_status()) != 0x0)
    {
        LOG_ERROR("%s", "status should be 0x0 after repairing");
        return E_VERFAIL;
    }

    return SUCCESS;
}

static pufs_status_t ptm_puf_qty_chk_cmd_test(uint32_t cmd, uint32_t expected)
{
    uint32_t status;
    rt_regs->puf_qty_chk = cmd;
    status = wait_status();
    if (status != expected)
    {
        LOG_ERROR("expected status is %lu but got %lu", expected, status);
        return E_VERFAIL;
    }
    return SUCCESS;
}

pufs_status_t pufs_rt_ptm_puf_qty_chk_test(void)
{
    pufs_status_t check = SUCCESS;
    for (uint32_t i = 0;i < PUF_LEN;i++) 
    {
        if (rt_regs->puf[i] != PUFRT_VALUE32(0xffffffff))
            return E_ERROR;
    }

    if ((check = ptm_puf_qty_chk_cmd_test(0x0, 0x4)) != SUCCESS)
        return check;
        
    rt_write_enroll();
    wait_status();

    return ptm_puf_qty_chk_cmd_test(0x0, 0x0);
}

pufs_status_t pufs_rt_ptm_puf_health_chk_test(void)
{
#ifndef CONFIG_COMPILE_ASIC
    pufs_status_t check = SUCCESS;
    for (uint32_t i = 0;i < PUF_LEN;i++) 
    {
        if (rt_regs->puf[i] != PUFRT_VALUE32(0xffffffff))
            return E_ERROR;
    }

    if ((check = ptm_puf_qty_chk_cmd_test(0xdc, 0x6)) != SUCCESS)
        return check;
#endif
    rt_write_enroll();
    wait_status();
    return ptm_puf_qty_chk_cmd_test(0xdc, 0x0);
}

pufs_status_t pufs_rt_ini_off_check_test(void)
{
    rt_regs->ini_off_chk = 0x0;
    uint32_t status = wait_status();
    if (status != 0)
    {
        LOG_ERROR("status expected is 0x0 but got %lu", status);
        return E_ERROR;
    }
    if (rt_regs->repair_reg != 0x0)
    {
        LOG_ERROR("repair_reg expected is 0x0 but got %lu", rt_regs->repair_reg);
        return E_ERROR;
    }
    return SUCCESS;
}

pufs_status_t pufs_rt_set_pin_test(void)
{
    uint32_t test_value = 0x44556677;
    rt_regs->otp[1] = test_value;

    rt_regs->set_pin = PA_REP_1;
    wait_status();
    if (rt_regs->otp[1] != PUFRT_VALUE32(0xFFFFFFFF))
    {
        LOG_ERROR("expected value is init state but got %lu", rt_regs->otp[1]);
        return E_VERFAIL;
    }

    rt_regs->set_pin = PA_REP_0;
    wait_status();
    if (rt_regs->otp[1] != test_value)
    {
        LOG_ERROR("expected value is %lu but got %lu", test_value, rt_regs->otp[1]);
        return E_VERFAIL;
    }

    return SUCCESS;
}

pufs_status_t pufs_rt_pif_set_flag_test(void)
{
    pufs_status_t res;
    uint32_t status;
    if ((res = rt_write_set_flag(SHFWEN_FLAG, &status)) != SUCCESS ||
        status != 0x0)
        return E_ERROR;

    if ((res = rt_write_set_flag(SHFREN_FLAG, &status)) != SUCCESS ||
        status != 0x0)
        return E_ERROR;
    
    if ((res = rt_write_set_flag(PGMPRT_FLAG, &status)) != SUCCESS ||
        status != 0x0)
        return E_ERROR;
    
    if ((res = rt_write_set_flag(PUFLCK_FLAG, &status)) != SUCCESS ||
        status != 0x0)
        return E_ERROR;
    
    if ((res = rt_write_set_flag(OTPLCK_FLAG, &status)) != SUCCESS ||
        status != 0x0)
        return E_ERROR;

    if ((res = rt_write_set_flag(TMLCK_FLAG, &status)) != SUCCESS ||
        status != 0x0)
        return E_ERROR;

    return SUCCESS;
}

pufs_status_t pufs_rt_uids_read_test(void)
{
    pufs_status_t check;
    pufs_uid_st uid;

    rt_write_enroll();

    for (pufs_rt_slot_t slot = PUFSLOT_0; slot < PUFSLOT_3;slot++)
    {
        if ((check = pufs_get_uid(&uid, slot)) != SUCCESS)
            return check;

        uint32_t *uid_word = (uint32_t*) uid.uid;
        for (uint32_t j = 0;j < UIDLEN/WORD_SIZE; j++)
        {
            if (*uid_word == PUFRT_VALUE32(0x0))
                return E_VERFAIL;
        }
    }

    if ((check = rt_write_set_flag(TMLCK_FLAG, 0x0)) != SUCCESS)
        return check;

    for (pufs_rt_slot_t slot = PUFSLOT_0; slot < PUFSLOT_3;slot++)
    {
        if ((check = pufs_get_uid(&uid, slot)) != SUCCESS)
            return check;

        uint32_t *uid_word = (uint32_t*) uid.uid;
        for (uint32_t j = 0;j < UIDLEN/WORD_SIZE; j++)
        {
            if ((slot == PUFSLOT_0 && *uid_word == PUFRT_VALUE32(0x0)) ||
                (slot != PUFSLOT_0 && *uid_word != PUFRT_VALUE32(0x0)))
                return E_VERFAIL;
        }
    }

    return SUCCESS;
}

