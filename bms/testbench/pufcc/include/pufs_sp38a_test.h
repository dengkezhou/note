/**
 * @file      pufs_sp38a.h
 * @brief     PUFsecurity SP38A API interface
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

#ifndef __PUFS_SP38A_TEST_H__
#define __PUFS_SP38A_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_common.h"
#include "pufs_test_common.h"

pufs_status_t init_sp38a_test(void);
/*****************************************************************************
 * Test functions
 ****************************************************************************/
pufs_status_t pufs_aes_ecb_enc_iuf_test(void);
pufs_status_t pufs_aes_ecb_enc_sg_test(void);
pufs_status_t pufs_aes_ecb_enc_test(void);
pufs_status_t pufs_aes_ecb_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_ecb_enc_swkey_test(void);
pufs_status_t pufs_aes_ecb_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_ecb_dec_iuf_test(void);
pufs_status_t pufs_aes_ecb_dec_sg_test(void);
pufs_status_t pufs_aes_ecb_dec_test(void);
pufs_status_t pufs_aes_ecb_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_ecb_dec_swkey_test(void);
pufs_status_t pufs_aes_ecb_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_cfb_enc_iuf_test(void);
pufs_status_t pufs_aes_cfb_enc_sg_test(void);
pufs_status_t pufs_aes_cfb_enc_test(void);
pufs_status_t pufs_aes_cfb_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_cfb_enc_swkey_test(void);
pufs_status_t pufs_aes_cfb_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_cfb_dec_iuf_test(void);
pufs_status_t pufs_aes_cfb_dec_sg_test(void);
pufs_status_t pufs_aes_cfb_dec_test(void);
pufs_status_t pufs_aes_cfb_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_cfb_dec_swkey_test(void);
pufs_status_t pufs_aes_cfb_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_ofb_enc_iuf_test(void);
pufs_status_t pufs_aes_ofb_enc_sg_test(void);
pufs_status_t pufs_aes_ofb_enc_test(void);
pufs_status_t pufs_aes_ofb_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_ofb_enc_swkey_test(void);
pufs_status_t pufs_aes_ofb_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_ofb_dec_iuf_test(void);
pufs_status_t pufs_aes_ofb_dec_sg_test(void);
pufs_status_t pufs_aes_ofb_dec_test(void);
pufs_status_t pufs_aes_ofb_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_ofb_dec_swkey_test(void);
pufs_status_t pufs_aes_ofb_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_enc_iuf_test(void);
pufs_status_t pufs_aes_cbc_enc_sg_test(void);
pufs_status_t pufs_aes_cbc_enc_test(void);
pufs_status_t pufs_aes_cbc_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_enc_swkey_test(void);
pufs_status_t pufs_aes_cbc_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_dec_iuf_test(void);
pufs_status_t pufs_aes_cbc_dec_sg_test(void);
pufs_status_t pufs_aes_cbc_dec_test(void);
pufs_status_t pufs_aes_cbc_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_dec_swkey_test(void);
pufs_status_t pufs_aes_cbc_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_cs1_enc_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs1_enc_sg_test(void);
pufs_status_t pufs_aes_cbc_cs1_enc_test(void);
pufs_status_t pufs_aes_cbc_cs1_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs1_enc_swkey_test(void);
pufs_status_t pufs_aes_cbc_cs1_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_cs1_dec_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs1_dec_sg_test(void);
pufs_status_t pufs_aes_cbc_cs1_dec_test(void);
pufs_status_t pufs_aes_cbc_cs1_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs1_dec_swkey_test(void);
pufs_status_t pufs_aes_cbc_cs1_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_cs2_enc_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs2_enc_sg_test(void);
pufs_status_t pufs_aes_cbc_cs2_enc_test(void);
pufs_status_t pufs_aes_cbc_cs2_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs2_enc_swkey_test(void);
pufs_status_t pufs_aes_cbc_cs2_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_cs2_dec_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs2_dec_sg_test(void);
pufs_status_t pufs_aes_cbc_cs2_dec_test(void);
pufs_status_t pufs_aes_cbc_cs2_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs2_dec_swkey_test(void);
pufs_status_t pufs_aes_cbc_cs2_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_cs3_enc_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs3_enc_sg_test(void);
pufs_status_t pufs_aes_cbc_cs3_enc_test(void);
pufs_status_t pufs_aes_cbc_cs3_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs3_enc_swkey_test(void);
pufs_status_t pufs_aes_cbc_cs3_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_cbc_cs3_dec_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs3_dec_sg_test(void);
pufs_status_t pufs_aes_cbc_cs3_dec_test(void);
pufs_status_t pufs_aes_cbc_cs3_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_cbc_cs3_dec_swkey_test(void);
pufs_status_t pufs_aes_cbc_cs3_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_ctr_enc_iuf_test(void);
pufs_status_t pufs_aes_ctr_enc_sg_test(void);
pufs_status_t pufs_aes_ctr_enc_test(void);
pufs_status_t pufs_aes_ctr_enc_swkey_iuf_test(void);
pufs_status_t pufs_aes_ctr_enc_swkey_test(void);
pufs_status_t pufs_aes_ctr_enc_multi_ctx_test(void);
pufs_status_t pufs_aes_ctr_dec_iuf_test(void);
pufs_status_t pufs_aes_ctr_dec_sg_test(void);
pufs_status_t pufs_aes_ctr_dec_test(void);
pufs_status_t pufs_aes_ctr_dec_swkey_iuf_test(void);
pufs_status_t pufs_aes_ctr_dec_swkey_test(void);
pufs_status_t pufs_aes_ctr_dec_multi_ctx_test(void);
pufs_status_t pufs_aes_ctr_counter_test(void);
pufs_status_t pufs_sm4_ecb_enc_iuf_test(void);
pufs_status_t pufs_sm4_ecb_enc_test(void);
pufs_status_t pufs_sm4_ecb_enc_swkey_iuf_test(void);
pufs_status_t pufs_sm4_ecb_enc_swkey_test(void);
pufs_status_t pufs_sm4_ecb_enc_multi_ctx_test(void);
pufs_status_t pufs_sm4_ecb_dec_iuf_test(void);
pufs_status_t pufs_sm4_ecb_dec_test(void);
pufs_status_t pufs_sm4_ecb_dec_swkey_iuf_test(void);
pufs_status_t pufs_sm4_ecb_dec_swkey_test(void);
pufs_status_t pufs_sm4_ecb_dec_multi_ctx_test(void);
pufs_status_t pufs_sm4_cfb_enc_iuf_test(void);
pufs_status_t pufs_sm4_cfb_enc_test(void);
pufs_status_t pufs_sm4_cfb_enc_swkey_iuf_test(void);
pufs_status_t pufs_sm4_cfb_enc_swkey_test(void);
pufs_status_t pufs_sm4_cfb_enc_multi_ctx_test(void);
pufs_status_t pufs_sm4_cfb_dec_iuf_test(void);
pufs_status_t pufs_sm4_cfb_dec_test(void);
pufs_status_t pufs_sm4_cfb_dec_swkey_iuf_test(void);
pufs_status_t pufs_sm4_cfb_dec_swkey_test(void);
pufs_status_t pufs_sm4_cfb_dec_multi_ctx_test(void);
pufs_status_t pufs_sm4_ofb_enc_iuf_test(void);
pufs_status_t pufs_sm4_ofb_enc_test(void);
pufs_status_t pufs_sm4_ofb_enc_swkey_iuf_test(void);
pufs_status_t pufs_sm4_ofb_enc_swkey_test(void);
pufs_status_t pufs_sm4_ofb_enc_multi_ctx_test(void);
pufs_status_t pufs_sm4_ofb_dec_iuf_test(void);
pufs_status_t pufs_sm4_ofb_dec_test(void);
pufs_status_t pufs_sm4_ofb_dec_swkey_iuf_test(void);
pufs_status_t pufs_sm4_ofb_dec_swkey_test(void);
pufs_status_t pufs_sm4_ofb_dec_multi_ctx_test(void);
pufs_status_t pufs_sm4_cbc_enc_iuf_test(void);
pufs_status_t pufs_sm4_cbc_enc_test(void);
pufs_status_t pufs_sm4_cbc_enc_swkey_iuf_test(void);
pufs_status_t pufs_sm4_cbc_enc_swkey_test(void);
pufs_status_t pufs_sm4_cbc_enc_multi_ctx_test(void);
pufs_status_t pufs_sm4_cbc_dec_iuf_test(void);
pufs_status_t pufs_sm4_cbc_dec_test(void);
pufs_status_t pufs_sm4_cbc_dec_swkey_iuf_test(void);
pufs_status_t pufs_sm4_cbc_dec_swkey_test(void);
pufs_status_t pufs_sm4_cbc_dec_multi_ctx_test(void);
pufs_status_t pufs_sm4_ctr_enc_iuf_test(void);
pufs_status_t pufs_sm4_ctr_enc_test(void);
pufs_status_t pufs_sm4_ctr_enc_swkey_iuf_test(void);
pufs_status_t pufs_sm4_ctr_enc_swkey_test(void);
pufs_status_t pufs_sm4_ctr_enc_multi_ctx_test(void);
pufs_status_t pufs_sm4_ctr_dec_iuf_test(void);
pufs_status_t pufs_sm4_ctr_dec_test(void);
pufs_status_t pufs_sm4_ctr_dec_swkey_iuf_test(void);
pufs_status_t pufs_sm4_ctr_dec_swkey_test(void);
pufs_status_t pufs_sm4_ctr_dec_multi_ctx_test(void);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_SP38A_TEST_H__ */
