#ifndef _STDIO_CUSTOM_H
#define _STDIO_CUSTOM_H
//#include <common.h>
//#include <semihost.h>
#include <stdarg.h>
//#include <linux/types.h>
#include <log.h>
#include <stdlib/machine/_types.h>
#ifndef __FREERTOS__
#define O_RDONLY 00000000
#define O_WRONLY 00000001
#define O_RDWR   00000002
#define O_CREAT  0x000100
#define O_TRUNC  0x000200
#define O_APPEND 0x000800 /* a+*/
#endif

typedef struct {
  size_t fd;
  ssize_t ssize;
  ssize_t offset;
  size_t error;
} _IO_FILE, FILE;

#ifndef __STD_IO_SEEK__
#define __STD_IO_SEEK__
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif
/*semihosting adapt interface*/
extern int open(const char *file_name, int mode);
extern size_t seek(int file_handle, ssize_t offset, int whence);
extern ssize_t read(int fd, void *buf, size_t count);
extern ssize_t write(int file_handle, const void *buffer, size_t length);
extern int close(int file_handle);
extern ssize_t flen(int file_handle);

/*
 * FILE based functions (can only be used AFTER relocation!)
 */
#ifndef __STD_IO_FILE__
#define __STD_IO_FILE__
#define stdin     ((FILE *)0)
#define stdout    ((FILE *)1)
#define stderr    ((FILE *)2)
#define MAX_FILES 3
#endif
int fclose(FILE *__stream);
int fflush(FILE *__stream);

FILE *fopen(char *__restrict __filename, char *__restrict __modes);
int fprintf(FILE *__restrict __stream, char *__restrict __format, ...);

int sprintf(char *buf, const char *fmt, ...)
    __attribute__((format(__printf__, 2, 3)));
int vsprintf(char *buf, const char *fmt, va_list args);
/* Read formatted input from STREAM.

   This function is a possible cancellation point and therefore not
   marked with .  */
int fscanf(FILE *__restrict __stream, char *__restrict __format, ...);
/* Read formatted input from stdin.

   This function is a possible cancellation point and therefore not
   marked with .  */
int scanf(char *__restrict __format, ...);
/* Read formatted input from S.  */
int sscanf(char *__restrict __s, char *__restrict __format, ...);

/* Read a character from STREAM.

   These functions are possible cancellation points and therefore not
   marked with .  */
// int fgetc (FILE *__stream);
// int getc (FILE *__stream);

/* Read a character from stdin.

   This function is a possible cancellation point and therefore not
   marked with .  */
int getchar(void);

/* The C standard explicitly says this is a macro, so we always do the
   optimization for it.  */
/* These are defined in POSIX.1:1996.

   These functions are possible cancellation points and therefore not
   marked with .  */
int getc_unlocked(FILE *__stream);
int getchar_unlocked(void);
/* Faster version when locking is not necessary.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with .  */
int fgetc_unlocked(FILE *__stream);

/* Write a character to STREAM.

   These functions are possible cancellation points and therefore not
   marked with .

   These functions is a possible cancellation point and therefore not
   marked with .  */
int fputc(int __c, FILE *__stream);
// int putc (int __c, FILE *__stream);

/* Write a character to stdout.

   This function is a possible cancellation point and therefore not
   marked with .  */
int putchar(int __c);

/* The C standard explicitly says this can be a macro,
   so we always do the optimization for it.  */

/* Faster version when locking is not necessary.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with .  */
int fputc_unlocked(int __c, FILE *__stream);
/* These are defined in POSIX.1:1996.

   These functions are possible cancellation points and therefore not
   marked with .  */
int putc_unlocked(int __c, FILE *__stream);
int putchar_unlocked(int __c);

/* Get a word (int) from STREAM.  */
int getw(FILE *__stream);

/* Write a word (int) to STREAM.  */
int putw(int __w, FILE *__stream);

/* Get a newline-terminated string of finite length from STREAM.

   This function is a possible cancellation point and therefore not
   marked with .  */
char *fgets(char *__restrict __s, int __n, FILE *__restrict __stream);

/* Get a newline-terminated string from stdin, removing the newline.
   DO NOT USE THIS FUNCTION!!  There is no limit on how much it will read.

   This function is a possible cancellation point and therefore not
   marked with .  */
char *gets(char *__s);

/* This function does the same as `fgets' but does not lock the stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with .  */
char *fgets_unlocked(char *__restrict __s, int __n, FILE *__restrict __stream);

/* Read up to (and including) a DELIMITER from STREAM into *LINEPTR
   (and null-terminate it). *LINEPTR is a pointer returned from malloc (or
   NULL), pointing to *N characters of space.  It is realloc'd as
   necessary.  Returns the number of characters read (not including the
   null terminator), or -1 on error or EOF.

   These functions are not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation they are cancellation points and
   therefore not marked with .  */

/* Write a string to STREAM.

   This function is a possible cancellation points and therefore not
   marked with .  */
int fputs(char *__restrict __s, FILE *__restrict __stream);

/* Write a string, followed by a newline, to stdout.

   This function is a possible cancellation points and therefore not
   marked with .  */
// int puts ( char *__s);

/* Push a character back onto the input buffer of STREAM.

   This function is a possible cancellation points and therefore not
   marked with .  */
int ungetc(int __c, FILE *__stream);

/* Read chunks of generic data from STREAM.

   This function is a possible cancellation points and therefore not
   marked with .  */
size_t fread(void *__restrict __ptr, size_t __size, size_t __n,
             FILE *__restrict __stream);
/* Write chunks of generic data to STREAM.

   This function is a possible cancellation points and therefore not
   marked with .  */
size_t fwrite(void *__restrict __ptr, size_t __size, size_t __n,
              FILE *__restrict __s);
/* This function does the same as `fputs' but does not lock the stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with .  */

/* Faster versions when locking is not necessary.

   These functions are not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation they are cancellation points and
   therefore not marked with .  */
size_t fread_unlocked(void *__restrict __ptr, size_t __size, size_t __n,
                      FILE *__restrict __stream);
size_t fwrite_unlocked(void *__restrict __ptr, size_t __size, size_t __n,
                       FILE *__restrict __stream);

/* Seek to a certain position on STREAM.

   This function is a possible cancellation point and therefore not
   marked with .  */
int fseek(FILE *__stream, long int __off, int __whence);
/* Return the current position of STREAM.

   This function is a possible cancellation point and therefore not
   marked with .  */
long int ftell(FILE *__stream);
/* Rewind to the beginning of STREAM.

   This function is a possible cancellation point and therefore not
   marked with .  */
void rewind(FILE *__stream);

/* The Single Unix Specification, Version 2, specifies an alternative,
   more adequate interface for the two functions above which deal with
   file offset.  `long int' is not the right type.  These definitions
   are originally defined in the Large File Support API.  */

/* Clear the error and EOF indicators for STREAM.  */
void clearerr(FILE *__stream);
/* Return the EOF indicator for STREAM.  */
int feof(FILE *__stream);
int ferror(FILE *__stream);
int fileno(FILE *__stream);

#endif /* !_STDIO_H */
