/**
 * @file      pufs_chacha_regs.h
 * @brief     PUFsecurity ChaCha register definition
 * @copyright 2021 PUFsecurity
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

#ifndef __PUFS_CHACHA_REGS_H__
#define __PUFS_CHACHA_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*****************************************************************************
 * Register Structures
 ****************************************************************************/
struct pufs_chacha_regs
{
    volatile uint32_t version;
    volatile uint32_t interrupt;
    volatile uint32_t feature;
    uint32_t _pad1;
    volatile uint32_t status;
    uint32_t _pad2;
    uint32_t _pad3[2];
    volatile uint32_t chacha_cfg_1;
    volatile uint32_t cfg; // Poly1305 configs
};

/*****************************************************************************
 * Register Bits
 ****************************************************************************/
#define CHACHA_CHACHA_CFG1_NONCE_TYPE_BITS       8
#define CHACHA_CHACHA_CFG1_16_OFFSET_BITS       16

#define CHACHA_RFC8439_CFG_DGEST_EN_BITS         1
#define CHACHA_RFC8439_CFG_P1305_EN_BITS         2
#define CHACHA_RFC8439_CFG_CHCH_EN_BITS          3
#define CHACHA_RFC8439_CFG_AEAD_ENCRYPT_BITS     4
#define CHACHA_RFC8439_CFG_P1305_SWKEY_EN_BITS   5



#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif /*__PUFS_CHACHA_REGS_H__*/
