/**
 * @file      pufs_tv_sm4ctr.h
 * @brief     PUFsecurity test vectors for SM4-CTR
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

#ifndef __PUFS_TV_SM4CTR_H__
#define __PUFS_TV_SM4CTR_H__

static const struct bc_test_pattern
#ifndef __BC_TEST_PATTERN__
#define __BC_TEST_PATTERN__
{
    pufs_cipher_t cipher;
    uint32_t keybits;
    const void* key;
    uint32_t ptlen;
    const void* pt;
    uint32_t ivlen;
    const void* iv;
    uint32_t ctlen;
    const void* ct;
}
#endif /* __BC_TEST_PATTERN__ */
sm4_ctr_tp[] =
{
    { SM4,
      128, "\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10",
      64, "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xbb\xbb\xbb\xbb\xbb\xbb\xbb\xbb\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xee\xee\xee\xee\xee\xee\xee\xee\xff\xff\xff\xff\xff\xff\xff\xff\xee\xee\xee\xee\xee\xee\xee\xee\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
      16, "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f",
      64, "\xac\x32\x36\xcb\x97\x0c\xc2\x07\x91\x36\x4c\x39\x5a\x13\x42\xd1\xa3\xcb\xc1\x87\x8c\x6f\x30\xcd\x07\x4c\xce\x38\x5c\xdd\x70\xc7\xf2\x34\xbc\x0e\x24\xc1\x19\x80\xfd\x12\x86\x31\x0c\xe3\x7b\x92\x2a\x46\xb8\x94\xbe\xe4\xfe\xb7\x9a\x38\x22\x94\x0c\x93\x54\x05",
    },
};

#endif /* __PUFS_TV_SM4CTR_H__ */
