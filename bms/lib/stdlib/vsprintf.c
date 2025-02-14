/*
 *  linux/lib/vsprintf.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/* vsprintf.c -- Lars Wirzenius & Linus Torvalds. */
/*
 * Wirzenius wrote this portably, Torvalds fucked it up :-)
 */

#include <stdarg.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>

#include <common.h>
#if !defined(CONFIG_PANIC_HANG)
#include <command.h>
#endif

#ifdef CONFIG_SYS_64BIT_VSPRINTF
#include <div64.h>
#define NUM_TYPE long
#else
#define NUM_TYPE long
#define do_div(n, base)                                                        \
  ({                                                                           \
    unsigned int __res;                                                        \
    __res = ((unsigned NUM_TYPE)n) % base;                                     \
    n     = ((unsigned NUM_TYPE)n) / base;                                     \
    __res;                                                                     \
  })
#endif
#define noinline __attribute__((noinline))

const char hex_asc[] = "0123456789abcdef";
#define hex_asc_lo(x) hex_asc[((x)&0x0f)]
#define hex_asc_hi(x) hex_asc[((x)&0xf0) >> 4]

static inline char *pack_hex_byte(char *buf, u8 byte) {
  *buf++ = hex_asc_hi(byte);
  *buf++ = hex_asc_lo(byte);
  return buf;
}

unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base) {
  unsigned long result = 0, value;

  if (*cp == '0') {
    cp++;
    if ((*cp == 'x') && isxdigit(cp[1])) {
      base = 16;
      cp++;
    }
    if (!base) {
      base = 8;
    }
  }
  if (!base) {
    base = 10;
  }
  while (isxdigit(*cp) &&
         (value = isdigit(*cp) ? *cp - '0'
                               : (islower(*cp) ? toupper(*cp) : *cp) - 'A' +
                                     10) < base) {
    result = result * base + value;
    cp++;
  }
  if (endp)
    *endp = (char *)cp;
  return result;
}

long simple_strtol(const char *cp, char **endp, unsigned int base) {
  if (*cp == '-')
    return -simple_strtoul(cp + 1, endp, base);
  return simple_strtoul(cp, endp, base);
}

int ustrtoul(const char *cp, char **endp, unsigned int base) {
  unsigned long result = simple_strtoul(cp, endp, base);
  switch (**endp) {
  case 'G':
    result *= 1024;
    /* fall through */
  case 'M':
    result *= 1024;
    /* fall through */
  case 'K':
  case 'k':
    result *= 1024;
    if ((*endp)[1] == 'i') {
      if ((*endp)[2] == 'B')
        (*endp) += 3;
      else
        (*endp) += 2;
    }
  }
  return result;
}

#ifdef CONFIG_SYS_64BIT_STRTOUL
unsigned long long simple_strtoull(const char *cp, char **endp,
                                   unsigned int base) {
  unsigned long long result = 0, value;

  if (*cp == '0') {
    cp++;
    if ((*cp == 'x') && isxdigit(cp[1])) {
      base = 16;
      cp++;
    }
    if (!base) {
      base = 8;
    }
  }
  if (!base) {
    base = 10;
  }
  while (isxdigit(*cp) &&
         (value = isdigit(*cp) ? *cp - '0'
                               : (islower(*cp) ? toupper(*cp) : *cp) - 'A' +
                                     10) < base) {
    result = result * base + value;
    cp++;
  }
  if (endp)
    *endp = (char *)cp;
  return result;
}
#endif /* CONFIG_SYS_64BIT_STRTOUL */

/* we use this so that we can do without the ctype library */
#define is_digit(c) ((c) >= '0' && (c) <= '9')

int skip_atoi(const char **s) {
  int i = 0;

  while (is_digit(**s))
    i = i * 10 + *((*s)++) - '0';
  return i;
}
