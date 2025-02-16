/*
 *  linux/lib/string.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * stupid library routines.. The optimized versions should generally be found
 * as inline code in <asm-xx/string.h>
 *
 * These are buggy as well..
 *
 * * Fri Jun 25 1999, Ingo Oeser <ioe@informatik.tu-chemnitz.de>
 * -  Added strsep() which will replace strtok() soon (because strsep() is
 *    reentrant and should be faster). Use only strsep() in new code, please.
 */

#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <malloc.h>
#include <assert.h>

#if 0 /* not used - was: #ifndef __HAVE_ARCH_STRNICMP */
/**
 * strnicmp - Case insensitive, length-limited string comparison
 * @s1: One string
 * @s2: The other string
 * @len: the maximum number of characters to compare
 */
int strnicmp(const char *s1, const char *s2, size_t len)
{
	/* Yes, Virginia, it had better be unsigned */
	unsigned char c1, c2;

	c1 = 0;	c2 = 0;
	if (len) {
		do {
			c1 = *s1; c2 = *s2;
			s1++; s2++;
			if (!c1)
				break;
			if (!c2)
				break;
			if (c1 == c2)
				continue;
			c1 = tolower(c1);
			c2 = tolower(c2);
			if (c1 != c2)
				break;
		} while (--len);
	}
	return (int)c1 - (int)c2;
}
#endif

char *___strtok;

#ifndef __HAVE_ARCH_STRCPY
/**
 * strcpy - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
char *strcpy(char *dest, const char *src) {
  char *tmp = dest;

  while ((*dest++ = *src++) != '\0')
    /* nothing */;
  return tmp;
}
#endif

#ifndef __HAVE_ARCH_STRNCPY
/**
 * strncpy - Copy a length-limited, %NUL-terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @count: The maximum number of bytes to copy
 *
 * Note that unlike userspace strncpy, this does not %NUL-pad the buffer.
 * However, the result is not %NUL-terminated if the source exceeds
 * @count bytes.
 */
char *strncpy(char *dest, const char *src, size_t count) {
  char *tmp = dest;

  while (count-- && (*dest++ = *src++) != '\0')
    /* nothing */;

  return tmp;
}
#endif

#ifndef __HAVE_ARCH_STRNCAT
/**
 * strncat - Append a length-limited, %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @count: The maximum numbers of bytes to copy
 *
 * Note that in contrast to strncpy, strncat ensures the result is
 * terminated.
 */
char *strncat(char *dest, const char *src, size_t count) {
  char *tmp = dest;

  if (count) {
    while (*dest)
      dest++;
    while ((*dest++ = *src++)) {
      if (--count == 0) {
        *dest = '\0';
        break;
      }
    }
  }

  return tmp;
}
#endif

#ifndef __HAVE_ARCH_STRCMP
/**
 * strcmp - Compare two strings
 * @cs: One string
 * @ct: Another string
 */
int strcmp(const char *cs, const char *ct) {
  register signed char __res;

  while (1) {
    if ((__res = *cs - *ct++) != 0 || !*cs++)
      break;
  }

  return __res;
}
#endif

#ifndef __HAVE_ARCH_STRNCMP
/**
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
int strncmp(const char *cs, const char *ct, size_t count) {
  register signed char __res = 0;

  while (count) {
    if ((__res = *cs - *ct++) != 0 || !*cs++)
      break;
    count--;
  }

  return __res;
}
#endif

#ifndef __HAVE_ARCH_STRCHR
/**
 * strchr - Find the first occurrence of a character in a string
 * @s: The string to be searched
 * @c: The character to search for
 */
char *strchr(const char *s, int c) {
  for (; *s != (char)c; ++s)
    if (*s == '\0')
      return NULL;
  return (char *)s;
}
#endif

#ifndef __HAVE_ARCH_STRLEN
/**
 * strlen - Find the length of a string
 * @s: The string to be sized
 */
size_t strlen(const char *s) {
  const char *sc;

  for (sc = s; *sc != '\0'; ++sc)
    /* nothing */;
  return sc - s;
}
#endif

#ifndef __HAVE_ARCH_STRNLEN
/**
 * strnlen - Find the length of a length-limited string
 * @s: The string to be sized
 * @count: The maximum number of bytes to search
 */
size_t strnlen(const char *s, size_t count) {
  const char *sc;

  for (sc = s; count-- && *sc != '\0'; ++sc)
    /* nothing */;
  return sc - s;
}
#endif

#if 0
/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void *memset(void *s, int c, size_t count) {
  char *xs = (char *)s;

  while (count--)
    *xs++ = c;

  return s;
}
#endif

#ifndef __HAVE_ARCH_MEMMOVE
/**
 * memmove - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * Unlike memcpy(), memmove() copes with overlapping areas.
 */
void *memmove(void *dest, const void *src, size_t count) {
  char *tmp, *s;

  if (dest == src)
    return dest;

  if (dest <= src) {
    tmp = (char *)dest;
    s   = (char *)src;
    while (count--)
      *tmp++ = *s++;
  } else {
    tmp = (char *)dest + count;
    s   = (char *)src + count;
    while (count--)
      *--tmp = *--s;
  }

  return dest;
}
#endif

#ifndef __HAVE_ARCH_MEMCMP
/**
 * memcmp - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 */
int memcmp(const void *cs, const void *ct, size_t count) {
  const unsigned char *su1, *su2;
  int res = 0;

  for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
    if ((res = *su1 - *su2) != 0)
      break;
  return res;
}
#endif

#ifndef __HAVE_ARCH_STRCAT

char *strcat(char *dest, const char *src) {
  char *tmp = dest;
  assert(src == NULL);
  assert(dest == NULL);
  while (*dest)
    dest++;
  while ((*dest++ = *src++) != '\0')
    ;
  return tmp;
}
#endif

#ifndef __HAVE_ARCH_STRPBRK
/**
 * strpbrk - Find the first occurrence of a set of characters
 * @cs: The string to be searched
 * @ct: The characters to search for
 */
char *strpbrk(const char *cs, const char *ct) {
  const char *sc1, *sc2;

  for (sc1 = cs; *sc1 != '\0'; ++sc1) {
    for (sc2 = ct; *sc2 != '\0'; ++sc2) {
      if (*sc1 == *sc2)
        return (char *)sc1;
    }
  }
  return NULL;
}
#endif

#ifndef __HAVE_ARCH_STRSEP
/**
 * strsep - Split a string into tokens
 * @s: The string to be searched
 * @ct: The characters to search for
 *
 * strsep() updates @s to point after the token, ready for the next call.
 *
 * It returns empty tokens, too, behaving exactly like the libc function
 * of that name. In fact, it was stolen from glibc2 and de-fancy-fied.
 * Same semantics, slimmer shape. ;)
 */
char *strsep(char **s, const char *ct) {
  char *sbegin = *s, *end;

  if (sbegin == NULL)
    return NULL;

  end = strpbrk(sbegin, ct);
  if (end)
    *end++ = '\0';
  *s = end;

  return sbegin;
}
#endif

#ifndef __HAVE_ARCH_STRSTR
/**
 * strstr - find a sub string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
char *strstr(const char *str, const char *sub) {
  // assert(str != NULL);
  // assert(sub != NULL);
  int str_len = strlen(str);
  int sub_len = strlen(sub);
  int i = 0, m = 0, n = 0;
  if (str_len < sub_len) /* 不用比较，肯定不是*/
  {
    return NULL;
  }
  if (str_len != 0 &&
      sub_len == 0) /* aaaaaaaaaaaaaaaaaa, "" ,比较需要花费时间很多*/
  {
    return NULL;
  }
  if (str_len == 0 && sub_len == 0) /* 都为空可以直接返回*/
  {
    return (char *)str;
  }

  for (i = 0; i != strlen(str); ++i) {
    m = 0, n = i;
    if (strlen(str + i) < sub_len) /* 往后找如果原串长度不够了，则肯定不是*/
    {
      return NULL;
    }
    if (str[n] == sub[m]) {
      while (str[n++] == sub[m++]) {
        if (sub[m] == '\0') {
          return (char *)(str + i);
        }
      }
    }
  }
  return NULL;
}
#endif
