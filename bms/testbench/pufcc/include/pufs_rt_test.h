/**
 * @file      pufs_rt.h
 * @brief     PUFsecurity PUFrt API interface
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

#ifndef __PUFS_RT_TEST_H__
#define __PUFS_RT_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "pufs_common.h"
#include "pufs_test_common.h"

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_rt_auto_load_test(void);
pufs_status_t pufs_rt_tcm_test(void);

pufs_status_t pufs_rt_pdstb_test(void);
pufs_status_t pufs_rt_rand_read_test(void);
pufs_status_t pufs_rt_rand_clk_test(void);
pufs_status_t pufs_rt_rand_resume_test(void);
pufs_status_t pufs_rt_uids_read_test(void);
pufs_status_t pufs_rt_read_mode_test(void);
pufs_status_t pufs_rt_post_mask_test(void);

/// harmful test functions
pufs_status_t pufs_rt_otp_read_write_test(void);
pufs_status_t pufs_rt_otp_rwlck_test(void);
/****************
 * Factory mode *
 ****************/
pufs_status_t pufs_rt_ini_off_check_test(void);
pufs_status_t pufs_rt_ptm_puf_health_chk_test(void);
pufs_status_t pufs_rt_ptm_puf_qty_chk_test(void);
pufs_status_t pufs_rt_uid_zeroize_test(void);
pufs_status_t pufs_rt_otp_zeroize_test(void);
pufs_status_t pufs_rt_ptm_status_warning_test(void);
pufs_status_t pufs_rt_ptm_status_forbid_test(void);
pufs_status_t pufs_rt_ptm_status_wrong_test(void);
pufs_status_t pufs_rt_ptm_puf_enroll_test(void);
pufs_status_t pufs_rt_pif_set_flag_test(void);

// we must reboot system after auto_repair, repair program, or set_pin test
pufs_status_t pufs_rt_repair_program_test(void);
pufs_status_t pufs_rt_auto_repair_test(void);
pufs_status_t pufs_rt_set_pin_test(void);

pufs_status_t pufs_rt_ptr_read_write_test(void);
pufs_status_t pufs_rt_ptc_read_write_test(void);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_RT_TEST_H__ */