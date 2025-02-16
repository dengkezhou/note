/**
 * @file      pufs_tv_hmac.h
 * @brief     PUFsecurity test vectors for HMAC
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

#ifndef __PUFS_TV_HMAC_H__
#define __PUFS_TV_HMAC_H__

static const struct hmac_test_pattern
{
    pufs_hash_t hash;
    uint32_t keybits;
    const void* key;
    uint32_t msglen;
    const void* msg;
    const void* md;
} hmac_tp[] =
{
#ifdef PUFS_TV_FULL
    { SHA_224,
        32, "Jefe",
        28, "what do ya want for nothing?",
        "\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44",
    },
    { SHA_224,
        1048, "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
        152, "This is a test using a larger than block-size key and a larger than block-size data. The key needs to be hashed before being used by the HMAC algorithm.",
        "\x3a\x85\x41\x66\xac\x5d\x9f\x02\x3f\x54\xd5\x17\xd0\xb3\x9d\xbd\x94\x67\x70\xdb\x9c\x2b\x95\xc9\xf6\xf5\x65\xd1",
    },
    { SHA_256,
        32, "Jefe",
        28, "what do ya want for nothing?",
        "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43",
    },
#endif
    { SHA_256,
        1048, "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
        152, "This is a test using a larger than block-size key and a larger than block-size data. The key needs to be hashed before being used by the HMAC algorithm.",
        "\x9b\x09\xff\xa7\x1b\x94\x2f\xcb\x27\x63\x5f\xbc\xd5\xb0\xe9\x44\xbf\xdc\x63\x64\x4f\x07\x13\x93\x8a\x7f\x51\x53\x5c\x3a\x35\xe2",
    },
#ifdef PUFS_TV_FULL
    { SHA_384,
        32, "Jefe",
        28, "what do ya want for nothing?",
        "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa\xb2\x16\x49",
    },
    { SHA_384,
        1048, "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
        152, "This is a test using a larger than block-size key and a larger than block-size data. The key needs to be hashed before being used by the HMAC algorithm.",
        "\x66\x17\x17\x8e\x94\x1f\x02\x0d\x35\x1e\x2f\x25\x4e\x8f\xd3\x2c\x60\x24\x20\xfe\xb0\xb8\xfb\x9a\xdc\xce\xbb\x82\x46\x1e\x99\xc5\xa6\x78\xcc\x31\xe7\x99\x17\x6d\x38\x60\xe6\x11\x0c\x46\x52\x3e",
    },
    { SHA_512,
        32, "Jefe",
        28, "what do ya want for nothing?",
        "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a\x38\xbc\xe7\x37",
    },
    { SHA_512,
        1048, "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
        152, "This is a test using a larger than block-size key and a larger than block-size data. The key needs to be hashed before being used by the HMAC algorithm.",
        "\xe3\x7b\x6a\x77\x5d\xc8\x7d\xba\xa4\xdf\xa9\xf9\x6e\x5e\x3f\xfd\xde\xbd\x71\xf8\x86\x72\x89\x86\x5d\xf5\xa3\x2d\x20\xcd\xc9\x44\xb6\x02\x2c\xac\x3c\x49\x82\xb1\x0d\x5e\xeb\x55\xc3\xe4\xde\x15\x13\x46\x76\xfb\x6d\xe0\x44\x60\x65\xc9\x74\x40\xfa\x8c\x6a\x58",
    },
    { SHA_512,
        1024, "\xc1\x07\x41\x3c\xd5\xea\xd0\xd4\x33\x6c\xac\xb5\xa9\xd0\x7c\x45\x59\x99\x04\xc7\x5a\xe0\xce\xcb\x2d\xda\xfb\x5b\x6c\x7d\x5e\x96\xa5\x7e\xff\x8a\x11\xeb\x51\xf5\x86\x6b\x0b\x11\x12\xf7\xb4\x6c\x13\x74\xb0\xcb\xc7\x2d\xbb\xc0\x91\x53\x28\x26\xdf\x57\x3f\x3e\x7d\xbf\xac\x5e\x3d\x8f\xb9\x0a\x64\xcb\xf4\x15\xa1\x60\x1e\x56\x01\xdb\xb2\xab\xbb\xdc\x55\x51\xdd\x3c\x1a\xcb\xf6\xb6\xc1\x7b\x81\xac\x71\x31\x4d\xb6\x47\xc6\x20\x6c\xa7\x1c\x7e\x98\xfd\xab\x1e\x1e\xdd\xa1\xd2\xc0\xeb\xef\xf0\xf9\x15\x85\x56\xd9\x77\x0c",
        16, "\xf1\xbe\x10\x2a\x42\x46\xc9\xda\x71\xb8\x07\x33\x6c\x31\x88\x3c",
        "\xf9\x3a\x49\x94\x3b\x74\xc7\xb3\xe0\x12\x5b\x2a\x43\x2e\x4e\x58\x2a\x8d\x77\x3a\x9f\x71\x39\xef\x43\xbe\x77\xac\xf7\x0c\x83\x1c\x30\x7d\xb4\x4c\x68\x32\x88\xab\xe6\xc6\xdb\xa6\xe1\x1b\x01\xda\x05\x30\xbb\x2d\x5e\x40\xc1\xd0\x06\x10\x9f\x72\x88\x55\xf7\xb1",
    },
#endif
};

#endif /* __PUFS_TV_HMAC_H__ */
