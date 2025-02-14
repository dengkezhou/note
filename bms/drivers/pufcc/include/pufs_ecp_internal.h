/**
 * @file      pufs_ecp.h
 * @brief     PUFsecurity ECP internal interface
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

#ifndef __PUFS_ECP_INTERNAL_H__
#define __PUFS_ECP_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "pufs_ecp.h"
#include "pufs_ecp_regs.h"

#define ECP_VERSION 0xECF09303
#if !defined(ECP_VERSION)
    #define ECP_VERSION 0xECF39303
#endif

/*****************************************************************************
 * Variables
 ****************************************************************************/
extern struct pufs_ecp_regs *ecp_regs;

/*****************************************************************************
 * Enumerations
 ****************************************************************************/
typedef enum {
    P1024 = 0x85,
    P2048,
    P3072,
    P4096,
    N_ECP_FIELD_T,
} pufs_ecp_field_t;

/*****************************************************************************
 * Internal Functions
 ****************************************************************************/

/**
 * @brief   Set SM2 curve domain parameters.
 * @return  SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_ecp_set_sm2_curve(void);

/**
 * @brief Compute x1,y1 / x2,y2 points for SM2 encryption
 *
 * @param[in]  puk   Public key.
 * @param[out] x1y1  EC point for C1
 * @param[out] x2y2  EC point for C2 and C3
 * @return           SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_ecp_sm2_enc_oss(pufs_ec_point_st *puk,
                                   pufs_ec_point_st *x1y1,
                                   pufs_ec_point_st *x2y2);

/**
 * @brief Compute x2,y2 points for SM2 decryption
 *
 * @param[in]  prk   Private key slot.
 * @param[in]  x1y1  EC point for C1
 * @param[out] x2y2  EC point for C2 and C3
 * @return           SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_ecp_sm2_dec_oss(pufs_ka_slot_t prk,
                                   pufs_ec_point_st *x1y1,
                                   pufs_ec_point_st *x2y2);

/**
 * @brief Sign digest using SM2 digital signature algorithm
 *
 * @param[out]    sig  Signature.
 * @param[in]      md  Message digest
 * @param[in] prktype  Private key type.
 * @param[in] prkslot  Private key slot.
 * @return             SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_ecp_sm2_sign_dgst(pufs_ecdsa_sig_st *sig,
                                     pufs_dgst_st *md,
                                     pufs_key_type_t prktype,
                                     pufs_ka_slot_t prkslot);


/**
 * @brief Verify signature using SM2 digital signature algorithm
 *
 * @param[in]     sig  Signature.
 * @param[in]      md  Message digest
 * @param[in]     puk  Public Key.
 * @return             SUCCESS on success, otherwise an error code.
 */
pufs_status_t pufs_ecp_sm2_verify_dgst(pufs_ecdsa_sig_st *sig,
                                       pufs_dgst_st *md,
                                       pufs_ec_point_st *puk);


pufs_status_t pufs_ecp_sm2_kekdf(pufs_ec_point_st *key,
                                 pufs_ec_point_st *tpukl,
                                 pufs_ec_point_st *tpukr,
                                 pufs_ec_point_st *pukr,
                                 pufs_ka_slot_t tprkslotl,
                                 pufs_ka_slot_t prkslotl);                          

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /* __PUFS_ECP_INTERNAL_H__ */
