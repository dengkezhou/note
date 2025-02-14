/**
 * @file      pufs_test_common.h
 * @brief     PUFsecurity Crypto Test Common Utility Interface
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

#ifndef __PUFS_TEST_COMMON_H__
#define __PUFS_TEST_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "pufs_dma.h"
#include "pufs_common.h"

/**
 * @brief A wrapper function of memcmp
 * 
 * @param __s1  buf1
 * @param __s2  buf2
 * @param __n   number of bytes to be compared in buf1 and buf2
 * @return      SUCCESS if contents are identical, otherwise E_VERFAIL 
 */
static inline 
pufs_status_t pufs_test_memcmp(const void *__s1, const void *__s2, size_t __n)
{
    return memcmp(__s1, __s2, __n) == 0 ? SUCCESS : E_VERFAIL;
}

typedef struct pufcc_test_func {
    pufs_status_t (*test)(void);
    const char *desc;
} pufcc_test_func_st;

typedef struct pufcc_test_group {
    const char *desc;
    pufs_status_t (*init)(void);
    pufcc_test_func_st *tests;
} pufcc_test_group_st;

pufs_status_t init_rt_factory_test(void);
pufs_status_t init_rt_user_test(void);
pufs_status_t init_crypto_test(void);
pufs_status_t init_pkc_test(void);

void form_sg_descs(pufs_dma_sg_desc_st *descs,
                   uint32_t *descs_len,
                   const uint32_t max_descs_len,
                   const void *out,
                   const void *in,
                   const uint32_t inlen,
                   uint32_t block_size,
                   bool set_read);

#ifdef __cplusplus
} 
#endif

#endif /* __PUFS_TEST_COMMON_H__ */