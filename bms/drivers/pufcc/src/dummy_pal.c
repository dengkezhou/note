/**
 * @file      dummy_pal.c
 * @brief     PUFsecurity platform abstraction layer implementation
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
#include "pufs_pal.h"

#include <domain.h>
#include <cache.h>

/* 
 * dummy_pal.c only contains dummy pal implementation,
 * This file does NOT satisfy the functionality defined in pufs_pal.h.
 * You MUST implement your own pal implementation.
 */

#define UNUSED(x) (void)(x)

extern char __lds_soc_base[];

uintptr_t pufs_pal_phy_addr(uintptr_t virt_addr)
{
    /* Put your implementation here, and return appropriate value */ 
    /* Please refer to pufs_pal.h for more details about this function */
#if defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1)
    return (uintptr_t)(virt_addr - (uintptr_t)__lds_soc_base + (uintptr_t)0x40000000);
#else
    return (uintptr_t)virt_to_phys((void *)virt_addr);
#endif    
}

uintptr_t pufs_pal_virt_addr(uintptr_t phy_addr)
{
    /* Put your implementation here, and return appropriate value */ 
    /* Please refer to pufs_pal.h for more details about this function */
#if defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1)
    return (uintptr_t)(phy_addr - (uintptr_t)0x40000000 + (uintptr_t)__lds_soc_base);
#else
    return (uintptr_t)phys_to_virt(phy_addr);
#endif    
}

void pufs_pal_init(void *config)
{
    /* Put your implementation here */ 
    /* Please refer to pufs_pal.h for more details about this function */
    UNUSED(config);
    if (itcs_module_enable(SAP, "pufcc") < 0)
        printf("pufcc module enable failed\n");

    while (!(readl(0xd0f00000 + 0xa0) & 0x1)) {}
}

void pufs_pal_release(void)
{
    /* Put your implementation here */ 
    /* Please refer to pufs_pal.h for more details about this function */
}

int pufs_pal_mmap(uintptr_t *virt_addr, const uintptr_t phy_addr, size_t size)
{
    /* Put your implementation here, and return appropriate value */ 
    /* Please refer to pufs_pal.h for more details about this function */
    UNUSED(size);
    *virt_addr = (uintptr_t)phys_to_virt(phy_addr);
    return 0;
}

void pufs_pal_ummap(const uintptr_t virt_addr, size_t size)
{
    /* Put your implementation here */ 
    /* Please refer to pufs_pal.h for more details about this function */
    UNUSED(virt_addr);
    UNUSED(size);
}

int pufs_pal_config_dma(void)
{
    /* Put your implementation here, and return appropriate value */ 
    /* Please refer to pufs_pal.h for more details about this function */
    return 0;
}

uintptr_t pufs_pal_dma_write_addr(const void *in, size_t len)
{
    /* Put your implementation here, and return appropriate value */ 
    /* Please refer to pufs_pal.h for more details about this function */
    return PHY_ADDR((uintptr_t)in);
}

uintptr_t pufs_pal_dma_read_addr(const void *out)
{
    /* Put your implementation here, and return appropriate value */ 
    /* Please refer to pufs_pal.h for more details about this function */
    return PHY_ADDR((uintptr_t)out);
}

void pufs_pal_read_from_dma(void *out, size_t len)
{
    /* Put your implementation here */ 
    /* Please refer to pufs_pal.h for more details about this function */
    itcs_dcache_flush();
}