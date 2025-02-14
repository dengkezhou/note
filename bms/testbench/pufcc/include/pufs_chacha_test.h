/**
 * @file      pufs_chacha_test.h
 * @brief     PUFsecurity ChaCha test function interface
 * @copyright 2022 PUFsecurity
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

#ifndef __PUFS_CHACHA_TEST_H__
#define __PUFS_CHACHA_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_common.h"
#include "pufs_test_common.h"

pufs_status_t init_chacha_test(void);
pufs_status_t pufs_chacha_enc_iuf_test(void);
pufs_status_t pufs_chacha_enc_sg_test(void);
pufs_status_t pufs_chacha_enc_test(void);
pufs_status_t pufs_chacha_enc_swkey_test(void);
pufs_status_t pufs_chacha_enc_multi_ctx_test(void);
pufs_status_t pufs_chacha_dec_iuf_test(void);
pufs_status_t pufs_chacha_dec_sg_test(void);
pufs_status_t pufs_chacha_dec_test(void);
pufs_status_t pufs_chacha_dec_swkey_test(void);
pufs_status_t pufs_chacha20_poly1305_enc_iuf_test(void);
pufs_status_t pufs_chacha20_poly1305_enc_sg_test(void);
pufs_status_t pufs_chacha20_poly1305_enc_test(void);
pufs_status_t pufs_chacha20_poly1305_enc_swkey_test(void);
pufs_status_t pufs_chacha20_poly1305_enc_multi_ctx_test(void);
pufs_status_t pufs_chacha20_poly1305_dec_iuf_test(void);
pufs_status_t pufs_chacha20_poly1305_dec_sg_test(void);
pufs_status_t pufs_chacha20_poly1305_dec_test(void);
pufs_status_t pufs_chacha20_poly1305_dec_swkey_test(void);
pufs_status_t puf_poly1305_test(void);

#ifdef __cplusplus
} 
#endif

#endif
