/**
 * @file      pufs_hmac_test.h
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

#ifndef __PUFS_HMAC_TEST_H__
#define __PUFS_HMAC_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_common.h"
#include "pufs_test_common.h"

pufs_status_t init_hmac_test(void);
pufs_status_t pufs_sha2_iuf_test(void);
pufs_status_t pufs_sha2_sg_test(void);
pufs_status_t pufs_sha2_test(void);
pufs_status_t pufs_sha2_multi_ctx_test(void);
pufs_status_t pufs_sm3_iuf_test(void);
pufs_status_t pufs_sm3_sg_test(void);
pufs_status_t pufs_sm3_test(void);
pufs_status_t pufs_sm3_multi_ctx_test(void);
pufs_status_t pufs_hmac_iuf_test(void);
pufs_status_t pufs_hmac_sg_test(void);
pufs_status_t pufs_hmac_test(void);
pufs_status_t pufs_hmac_swkey_iuf_test(void);
pufs_status_t pufs_hmac_swkey_test(void);
pufs_status_t pufs_hmac_multi_ctx_test(void);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_HMAC_H__ */
