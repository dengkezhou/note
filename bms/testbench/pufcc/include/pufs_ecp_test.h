/**
 * @file      pufs_ecp.h
 * @brief     PUFsecurity ECP API interface
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

#ifndef __PUFS_ECP_TEST_H__
#define __PUFS_ECP_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_test_common.h"

/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_rsa_verify_test(void);
pufs_status_t pufs_rsa_sign_test(void);
pufs_status_t pufs_rsa_x931_verify_test(void);
pufs_status_t pufs_rsa_x931_sign_test(void);
pufs_status_t pufs_rsa_p1v15_verify_test(void);
pufs_status_t pufs_rsa_p1v15_sign_test(void);
pufs_status_t pufs_rsa_pss_verify_test(void);
pufs_status_t pufs_rsa_pss_sign_test(void);
pufs_status_t pufs_ecp_ecpuk_test(void);
pufs_status_t pufs_ecp_ecpkv_test(void);
pufs_status_t pufs_ecp_sprk_gen_test(void);
pufs_status_t pufs_ecp_eprk_gen_test(void);
pufs_status_t pufs_ecp_ecccdh_2e2s_test(void);
pufs_status_t pufs_ecp_ecccdh_2e_test(void);
pufs_status_t pufs_ecp_ecccdh_oss_test(void);
pufs_status_t pufs_ecp_ecdsa_verify_test(void);
pufs_status_t pufs_ecp_ecdsa_verify_otpkey_test(void);
pufs_status_t pufs_ecp_ecdsa_sign_k_test(void);
pufs_status_t pufs_ecp_ecdsa_sign_verify_test(void);
pufs_status_t pufs_ecp_ecdsa_verify_msg_test(void);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_ECP_TEST_H__ */
