/**
 * @file      pufs_tv_sm3.h
 * @brief     PUFsecurity test vectors for SM3
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

#ifndef __PUFS_TV_SM3_H__
#define __PUFS_TV_SM3_H__

static const struct hash_test_pattern
#ifndef __HASH_TEST_PATTERN__
#define __HASH_TEST_PATTERN__
{
    pufs_hash_t hash;
    uint32_t msglen;
    const void* msg;
    const void* md;
}
#endif /* __HASH_TEST_PATTERN__ */
sm3_tp[] =
{
    { SM3,
        3, "abc",
        "\x66\xc7\xf0\xf4\x62\xee\xed\xd9\xd1\xf2\xd4\x6b\xdc\x10\xe4\xe2\x41\x67\xc4\x87\x5c\xf2\xf7\xa2\x29\x7d\xa0\x2b\x8f\x4b\xa8\xe0",
    },
    { SM3,
        64, "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd",
        "\xde\xbe\x9f\xf9\x22\x75\xb8\xa1\x38\x60\x48\x89\xc1\x8e\x5a\x4d\x6f\xdb\x70\xe5\x38\x7e\x57\x65\x29\x3d\xcb\xa3\x9c\x0c\x57\x32",
    },
    { SM3,
        0, NULL,
        "\x1a\xb2\x1d\x83\x55\xcf\xa1\x7f\x8e\x61\x19\x48\x31\xe8\x1a\x8f\x22\xbe\xc8\xc7\x28\xfe\xfb\x74\x7e\xd0\x35\xeb\x50\x82\xaa\x2b",
    },
};

#endif /* __PUFS_TV_SM3_H__ */
