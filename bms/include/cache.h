#ifndef __CACHE_H__
#define __CACHE_H__

#ifdef CONFIG_ICACHE
int itcs_icache_status(void);
void itcs_icache_enable(void);
void itcs_icache_disable(void);
void itcs_icache_invalid(void);
#else
static inline int itcs_icache_status(void) { return 0; }
static inline void itcs_icache_enable(void) { }
static inline void itcs_icache_disable(void) { }
static inline void itcs_icache_invalid(void) { }
#endif

#ifdef CONFIG_DCACHE
int itcs_dcache_status(void);
void itcs_dcache_enable(void);
void itcs_dcache_disable(void);
void itcs_dcache_clean(void);
void itcs_dcache_invalid(void);
void itcs_dcache_flush(void);
void itcs_l2cache_invalid(void);
void itcs_l2cache_clean(void);
void itcs_l2cache_flush(void);
void itcs_dcache_flush_range(phys_addr_t start, unsigned long size);
void itcs_dcache_clean_range(phys_addr_t start, unsigned long size);
void itcs_dcache_invalid_range(phys_addr_t start, unsigned long size);
#else
static inline int itcs_dcache_status(void) { return 0; }
static inline void itcs_dcache_enable(void) { }
static inline void itcs_dcache_disable(void) { }
static inline void itcs_dcache_clean(void) { }
static inline void itcs_dcache_invalid(void) { }
static inline void itcs_dcache_flush(void) { }
static inline void itcs_l2cache_invalid(void) { }
static inline void itcs_l2cache_clean(void) { }
static inline void itcs_l2cache_flush(void) { }
static inline void itcs_dcache_flush_range(phys_addr_t start, unsigned long size) { }
static inline void itcs_dcache_clean_range(phys_addr_t start, unsigned long size) { }
static inline void itcs_dcache_invalid_range(phys_addr_t start, unsigned long size) { }
#endif
#endif
