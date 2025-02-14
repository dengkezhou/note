#ifndef __ARCH_ARM_POSIX_TYPES_H
#define __ARCH_ARM_POSIX_TYPES_H

#include <generated/autoconf.h>

#ifdef CONFIG_64BIT
#define __BITS_PER_LONG 64
#else
#define __BITS_PER_LONG 32
#endif
//#include <asm/bitsperlong.h>
/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.
 *
 * First the types that are often defined in different ways across
 * architectures, so that you can override them.
 */
#ifndef __kernel_long_t
typedef unsigned short __kernel_nlink_t;
#endif

#ifndef __kernel_long_t
typedef long __kernel_long_t;
typedef unsigned long __kernel_ulong_t;
#endif

#ifndef __kernel_ino_t
typedef __kernel_ulong_t __kernel_ino_t;
#endif

#ifndef __kernel_mode_t
typedef unsigned int __kernel_mode_t;
#endif

#ifndef __kernel_pid_t
typedef int __kernel_pid_t;
#endif

#ifndef __kernel_ipc_pid_t
typedef int __kernel_ipc_pid_t;
#endif

#ifndef __kernel_uid_t
typedef unsigned int __kernel_uid_t;
typedef unsigned int __kernel_gid_t;
#endif

#ifndef __kernel_suseconds_t
typedef __kernel_long_t __kernel_suseconds_t;
#endif

#ifndef __kernel_daddr_t
typedef int __kernel_daddr_t;
#endif

#ifndef __kernel_uid32_t
typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;
#endif

#ifndef __kernel_old_uid_t
typedef __kernel_uid_t __kernel_old_uid_t;
typedef __kernel_gid_t __kernel_old_gid_t;
#endif

#ifndef __kernel_old_dev_t
typedef unsigned int __kernel_old_dev_t;
#endif

/*
 * Most 32 bit architectures use "unsigned int" size_t,
 * and all 64 bit architectures use "unsigned long" size_t.
 */
#ifndef __kernel_size_t
#if __BITS_PER_LONG != 64
typedef unsigned int __kernel_size_t;
typedef int __kernel_ssize_t;
typedef int __kernel_ptrdiff_t;
#else
typedef __kernel_ulong_t __kernel_size_t;
typedef __kernel_long_t __kernel_ssize_t;
typedef __kernel_long_t __kernel_ptrdiff_t;
#endif
#endif

#ifndef __kernel_fsid_t
typedef struct {
  int val[2];
} __kernel_fsid_t;
#endif

/*
 * anything below here should be completely generic
 */
typedef __kernel_long_t __kernel_off_t;
typedef long long __kernel_loff_t;
typedef __kernel_long_t __kernel_time_t;
typedef __kernel_long_t __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef char *__kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;

#if defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ < 2)

#undef __FD_SET
#define __FD_SET(fd, fdsetp)                                                   \
  (((fd_set *)fdsetp)->fds_bits[fd >> 5] |= (1 << (fd & 31)))

#undef __FD_CLR
#define __FD_CLR(fd, fdsetp)                                                   \
  (((fd_set *)fdsetp)->fds_bits[fd >> 5] &= ~(1 << (fd & 31)))

#undef __FD_ISSET
#define __FD_ISSET(fd, fdsetp)                                                 \
  ((((fd_set *)fdsetp)->fds_bits[fd >> 5] & (1 << (fd & 31))) != 0)

#undef __FD_ZERO
#define __FD_ZERO(fdsetp) (memset(fdsetp, 0, sizeof(*(fd_set *)fdsetp)))

#endif

#endif
