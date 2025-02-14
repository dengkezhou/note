/**
 * @file      pufs_tv_aeskwp.h
 * @brief     PUFsecurity test vectors for AES-KWP
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

#ifndef __PUFS_TV_AESKWP_H__
#define __PUFS_TV_AESKWP_H__

struct kw_test_pattern
#ifndef __KW_TEST_PATTERN__
#define __KW_TEST_PATTERN__
{
    pufs_cipher_t cipher;
    uint32_t keybits;
    const void* key;
    uint32_t ptlen;
    const void* pt;
    uint32_t ctlen;
    const void* ct;
}
#endif /* __KW_TEST_PATTERN__ */
aes_wrap_pad_tp[] =
{
#ifdef PUFS_TV_FULL
    { AES,
      128, "\x6d\xec\xf1\x0a\x1c\xaf\x8e\x3b\x80\xc7\xa4\xbe\x8c\x9c\x84\xe8",
      1, "\x49",
      16, "\x01\xa7\xd6\x57\xfc\x4a\x5b\x21\x6f\x26\x1c\xca\x4d\x05\x2c\x2b",
    },
    { AES,
      192, "\x9c\xa1\x10\x78\xba\xeb\xc1\x59\x7a\x68\xce\x2f\xe3\xfc\x79\xa2\x01\x62\x65\x75\x25\x2b\x88\x60",
      1, "\x76",
      16, "\x86\x6b\xc0\xae\x30\xe2\x90\xbb\x20\xa0\xda\xb3\x1a\x6e\x71\x65",
    },
    { AES,
      256, "\x06\x8b\x05\xd0\x05\x90\x24\x38\xbb\x7a\x83\x7c\x18\xca\x4d\x7a\xba\xb6\x3c\x7d\xe5\x58\x99\x3d\xf6\x84\x92\xb3\xcf\x3c\x1c\x3c",
      1, "\x24",
      16, "\xd5\x45\x25\xe3\x3b\x8d\x29\xaa\x14\x97\xff\xeb\x13\xac\xd1\x0a",
    },
    { AES,
      128, "\x30\xbe\x7f\xf5\x12\x27\xf0\xee\xf7\x86\xcb\x7b\xe2\x48\x25\x10",
      0, NULL,
      16, "\x7f\x61\xa0\xa8\xb2\xfe\x78\x03\xf2\x94\x7d\x23\x3e\xc3\xa2\x55",
    },
    { AES,
      192, "\x21\xfb\x66\x00\xc1\xd3\x4a\x74\xad\xee\x67\x61\x26\x72\x59\x3a\x86\xcf\x23\x54\x21\x73\x53\x50",
      0, NULL,
      16, "\x56\xb4\x5c\x49\xc3\xe3\x79\xb1\x8d\x9c\x38\xb6\x42\x3d\xb1\x33",
    },
#endif
    { AES,
      256, "\xc3\x2c\xb3\xe1\xe4\x1a\x4b\x9f\x4d\xe7\x99\x89\x95\x78\x66\xf5\xdd\x48\xdb\xa3\x8c\x22\xa6\xeb\xb8\x0e\x14\xc8\x4b\xdd\x95\x34",
      0, NULL,
      16, "\xc2\x9b\x05\xc2\x61\x9a\x58\xec\xc1\xd2\x39\xe7\xa3\x42\x73\xcd",
    },
};

#endif /* __PUFS_TV_AESKWP_H__ */
