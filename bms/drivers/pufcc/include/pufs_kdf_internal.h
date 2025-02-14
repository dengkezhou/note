/**
 * @file      pufs_kdf_internal.h
 * @brief     PUFsecurity KDF internal interface
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

#ifndef __PUFS_KDF_INTERNAL_H__
#define __PUFS_KDF_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_kdf.h"

/*****************************************************************************
 * Macros
 ****************************************************************************/

#define KDF_VERSION 0x484B4400

/*****************************************************************************
 * Variables
 ****************************************************************************/

extern struct pufs_kdf_regs *kdf_regs;

/*****************************************************************************
 * Parameter struct for internal functions
 ****************************************************************************/

struct pufs_kdf_cfg_params {
    pufs_key_type_t   keytype;
    pufs_ka_slot_t    keyslot;
    uint32_t          outbits;
    pufs_prf_family_t prf;
    pufs_kdf_md_t     method;
    pufs_hash_t       hash;
    uint32_t          zbits;
    bool              feedback;
    const uint8_t*    iv;
};

struct pufs_kdf_cnt_params {
    bool                feedback;
    uint8_t             length;
    pufs_kdf_cnt_pos_t  position;
    uint32_t            order;
};


/*****************************************************************************
 * Internal Functions
 ****************************************************************************/

pufs_status_t pufs_sm2kdf(
    pufs_key_type_t keytype,
    pufs_ka_slot_t keyslot,
    uint32_t outbits,
    pufs_key_type_t ztype,
    size_t zaddr,
    uint32_t zbits,
    const uint8_t* info,
    uint32_t infolen,
    uint8_t *out);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_KDF_INTERNAL_H__ */
