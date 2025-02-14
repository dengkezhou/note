#ifndef __RTLFS_H__
#define __RTLFS_H__

#if CONFIG_TB_RUN_DDR1
#define RTLFS_START_ADDR  ((unsigned long)(CONFIG_RTLFS_LOCATION + 0x400000000))
#else
#define RTLFS_START_ADDR  ((unsigned long)CONFIG_RTLFS_LOCATION)
#endif

extern int rtlfsck(void);
extern int rtlfs_list(int crc);
extern uintptr_t faddr(int fd);
extern void *mmap(int fd, int len);
extern int munmap(int fd, int len);

#endif /* __RTLFS_H__ */
