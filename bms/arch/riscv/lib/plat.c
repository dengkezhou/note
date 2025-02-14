#include <plat.h>
#include <rtl.h>
#include <sysm.h>
#include <cache.h>

/**
 * memset - set value one area of memory
 * @dest: Where to set value
 * @value: value
 * @count: The size to set.
 *
 */
void * memset(void *s, int c, size_t count)
{
#ifdef CONFIG_HW_MEMDEV
	int domain = itcs_sysm_identity();
	unsigned long start = (domain == CPU) ? ITCS_CDDR_ADDR : ITCS_SDDR_ADDR;
	unsigned long end = (domain == CPU) ? (ITCS_CDDR_END + 0x400000000) : ITCS_SDDR_END;
  if(((unsigned long)s < start) || ((unsigned long)s > end) || (count < 16)) {
		char *xs = (char *)s;

  	while (count--)
    	*xs++ = c;
  }
  else {
#ifdef CONFIG_CACHE
	itcs_dcache_flush_range((unsigned long)s, count);
#endif
    rtl_host_set(RTL_MEMDST, (unsigned long)s);
    rtl_host_set(RTL_MEMVAL, c);
    rtl_host_set(RTL_MEMLEN, count);
		rtl_host_set(RTL_MEMTYPE, SMEM_BYTE_ALIGN);
		/* wait memset finish. */
#ifdef CONFIG_C920
		asm("sync.is");
#elif defined(CONFIG_E906)
		udelay(1);
#endif
  }
#else
  char *xs = (char *)s;

  while (count--)
    *xs++ = c;
#endif
  return s;
}

/*
 * Copy @len bytes from @src to @dst
 */
void *memcpy(void *dst, const void *src, size_t len) {
  const char *s = src;
  char *d       = dst;
#ifdef CONFIG_HW_MEMDEV
	int domain = itcs_sysm_identity();
	unsigned long start = (domain == CPU) ? ITCS_CDDR_ADDR : ITCS_SDDR_ADDR;
	unsigned long end = (domain == CPU) ? (ITCS_CDDR_END + 0x400000000) : ITCS_SDDR_END;
  if(((unsigned long)d < start) || ((unsigned long)d > end) || (len < 16)
			|| ((unsigned long)s < start) || ((unsigned long)s > end)) {
		if (((uintptr_t)s & 0x3) || ((uintptr_t)d & 0x3))
			goto skip;

		while (len >= 4) {
			*(uint32_t *)d = *(uint32_t *)s;
			d += 4;
			s += 4;
			len = len >= 4 ? len - 4 : len;
		}

skip:
		while (len--)
			*d++ = *s++;
  }
  else {
#ifdef CONFIG_CACHE
  	itcs_dcache_flush_range((unsigned long)d, len);
	itcs_dcache_flush_range((unsigned long)s, len);
#endif

    rtl_host_set(RTL_MEMDST, (unsigned long)d);
		rtl_host_set(RTL_MEMSRC, (unsigned long)s);
    rtl_host_set(RTL_MEMLEN, len);
		rtl_host_set(RTL_MEMTYPE, CMEM_BYTE_ALIGN);
		/* wait memcpy finish. */
#ifdef CONFIG_C920
		asm("sync.is");
#elif defined(CONFIG_E906)
		udelay(1);
#endif
  }

#else
  if (((uintptr_t)s & 0x3) || ((uintptr_t)d & 0x3))
    goto skip;

  while (len >= 4) {
    *(uint32_t *)d = *(uint32_t *)s;
    d += 4;
    s += 4;
    len = len >= 4 ? len - 4 : len;
  }

skip:
  while (len--)
    *d++ = *s++;
#endif
  return d;
}

#ifdef CONFIG_COMPILE_RTL
extern int __lds_print[];
static inline void soc_cmd(int cmd)
{
  volatile int *addr_ptr = (int *)__lds_print;
  *addr_ptr = cmd;
#ifdef CONFIG_C920
  asm("sync.is");
#endif
}


void soc_dump(uint64_t src_addr, uint32_t size) {
    uint32_t cmd_type ;

    cmd_type    = 0x23;

    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( size            & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((size     >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd(((cmd_type         & 0xffff) << 16) | 0xa5fe);
}
#else
void soc_dump(uint64_t src_addr, uint32_t size) { }
#endif
