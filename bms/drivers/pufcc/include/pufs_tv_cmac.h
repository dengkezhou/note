/**
 * @file      pufs_tv_cmac.h
 * @brief     PUFsecurity test vectors for CMAC
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

#ifndef __PUFS_TV_CMAC_H__
#define __PUFS_TV_CMAC_H__

static const struct cmac_test_pattern
{
    pufs_cipher_t cipher;
    uint32_t keybits;
    const void* key;
    uint32_t msglen;
    const void* msg;
    const void* md;
} cmac_tp[] =
{
#ifdef PUFS_TV_FULL
    { AES,
      128, "\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C",
      0, NULL,
      "\xBB\x1D\x69\x29\xE9\x59\x37\x28\x7F\xA3\x7D\x12\x9B\x75\x67\x46"
    },
#endif
    { AES,
      128, "\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C",
      64, "\x6B\xC1\xBE\xE2\x2E\x40\x9F\x96\xE9\x3D\x7E\x11\x73\x93\x17\x2A\xAE\x2D\x8A\x57\x1E\x03\xAC\x9C\x9E\xB7\x6F\xAC\x45\xAF\x8E\x51\x30\xC8\x1C\x46\xA3\x5C\xE4\x11\xE5\xFB\xC1\x19\x1A\x0A\x52\xEF\xF6\x9F\x24\x45\xDF\x4F\x9B\x17\xAD\x2B\x41\x7B\xE6\x6C\x37\x10",
      "\x51\xF0\xBE\xBF\x7E\x3B\x9D\x92\xFC\x49\x74\x17\x79\x36\x3C\xFE"
    },
#ifdef PUFS_TV_FULL
    { AES,
      192, "\x8E\x73\xB0\xF7\xDA\x0E\x64\x52\xC8\x10\xF3\x2B\x80\x90\x79\xE5\x62\xF8\xEA\xD2\x52\x2C\x6B\x7B",
      0, NULL,
      "\xD1\x7D\xDF\x46\xAD\xAA\xCD\xE5\x31\xCA\xC4\x83\xDE\x7A\x93\x67"
    },
    { AES,
      192, "\x8E\x73\xB0\xF7\xDA\x0E\x64\x52\xC8\x10\xF3\x2B\x80\x90\x79\xE5\x62\xF8\xEA\xD2\x52\x2C\x6B\x7B",
      64, "\x6B\xC1\xBE\xE2\x2E\x40\x9F\x96\xE9\x3D\x7E\x11\x73\x93\x17\x2A\xAE\x2D\x8A\x57\x1E\x03\xAC\x9C\x9E\xB7\x6F\xAC\x45\xAF\x8E\x51\x30\xC8\x1C\x46\xA3\x5C\xE4\x11\xE5\xFB\xC1\x19\x1A\x0A\x52\xEF\xF6\x9F\x24\x45\xDF\x4F\x9B\x17\xAD\x2B\x41\x7B\xE6\x6C\x37\x10",
      "\xA1\xD5\xDF\x0E\xED\x79\x0F\x79\x4D\x77\x58\x96\x59\xF3\x9A\x11"
    },
    { AES,
      256, "\x60\x3D\xEB\x10\x15\xCA\x71\xBE\x2B\x73\xAE\xF0\x85\x7D\x77\x81\x1F\x35\x2C\x07\x3B\x61\x08\xD7\x2D\x98\x10\xA3\x09\x14\xDF\xF4",
      0, NULL,
      "\x02\x89\x62\xF6\x1B\x7B\xF8\x9E\xFC\x6B\x55\x1F\x46\x67\xD9\x83"
    },
#endif
    { AES,
      256, "\x60\x3D\xEB\x10\x15\xCA\x71\xBE\x2B\x73\xAE\xF0\x85\x7D\x77\x81\x1F\x35\x2C\x07\x3B\x61\x08\xD7\x2D\x98\x10\xA3\x09\x14\xDF\xF4",
      64, "\x6B\xC1\xBE\xE2\x2E\x40\x9F\x96\xE9\x3D\x7E\x11\x73\x93\x17\x2A\xAE\x2D\x8A\x57\x1E\x03\xAC\x9C\x9E\xB7\x6F\xAC\x45\xAF\x8E\x51\x30\xC8\x1C\x46\xA3\x5C\xE4\x11\xE5\xFB\xC1\x19\x1A\x0A\x52\xEF\xF6\x9F\x24\x45\xDF\x4F\x9B\x17\xAD\x2B\x41\x7B\xE6\x6C\x37\x10",
      "\xE1\x99\x21\x90\x54\x9F\x6E\xD5\x69\x6A\x2C\x05\x6C\x31\x54\x10"
    },
};

#endif /* __PUFS_TV_CMAC_H__ */
