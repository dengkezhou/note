/* Copyright(C)infoTM For Working
 * All right reserved
 *
 */
/**
 * @file semihost2.c
 * @brief
 * @author Bright.Jiang bright.jiang@infotmic.com.cn  godvmxi@126.com
 * @version 0.1
 * @date 2014-07-07
 */
#include <stdio.h>
#include <semihost.h>
#include <common.h>
#include <asm/errno.h>
#include <assert.h>
#include <stdarg.h>
extern void *malloc(size_t size);
extern void *free(void *ptr);
/**
 * @brief fopen
 *
 * @param __filename
 * @param __modes ,just support rb,rb+,wb,wb+
 *
 * @return
 */
FILE *fopen(char *__restrict __filename, char *__restrict __modes) {
  int modes = 0, fd = -1, pos = 0;
  FILE *file;
  assert(__filename != NULL);
  if (strstr(__modes, "rb+")) {
    modes = O_RDONLY | O_CREAT;
    pos   = -1; // to the end of file
  } else if (strstr(__modes, "rb"))
    modes = O_RDONLY;
  else if (strstr(__modes, "wb+"))
    modes = O_WRONLY | O_CREAT;
  else if (strstr(__modes, "wb"))
    modes = O_WRONLY | O_CREAT;
  else if (strstr(__modes, "a+")) {
    modes = O_WRONLY;
    pos   = -1;
  } else {
    printf("fopen mode error ,must between rb,rb+,wb,wb+\n");
    return NULL;
  }
  fd = open(__filename, modes);
  if (fd < 0)
    return NULL;
  file = (FILE *)malloc(sizeof(FILE));
  if (file == NULL)
    return NULL;
  file->fd     = fd;
  file->ssize  = flen(file->fd);
  file->offset = 0;
  if (pos == -1)
    seek(file->fd, file->ssize, SEEK_SET);
  return file;
}
int fclose(FILE *stream) {
  assert(stream != NULL);
  close(stream->fd);
  free(stream);
  return 0;
}

int fseek(FILE *__stream, long int __off, int __whence) {
  assert(__stream != NULL);
  // printf("seek->%d ->%d->%d\n",__stream->offset,__stream->ssize,__whence);
  switch (__whence) {
  case SEEK_SET:
    if (__off < 0) {
      printf("fseek file exceeded the start\n");
      return -1;
    }
    if ((__off) >= __stream->ssize) {
      printf("fseek file exceeded the end\n");
      return -1;
    }
    __stream->offset = __off;
    seek(__stream->fd, __stream->offset, SEEK_SET);
    return 0;
    break;
  case SEEK_CUR:
    if (__off + __stream->offset < 0) {
      printf("fseek file exceeded the start\n");
      return -1;
    }
    if ((__off + __stream->offset) >= __stream->offset) {
      printf("fseek file exceeded the end\n");
      return -1;
    }
    __stream->offset += __off;
    seek(__stream->fd, __stream->offset, SEEK_SET);
    return 0;
    break;
  case SEEK_END:
    if (__off > 0) {
      printf("fseek file exceeded the end\n");
      return -1;
    }
    if ((__stream->offset + __off) < 0) {
      printf("fseek file exceeded the start\n");
      return -1;
    }
    __stream->offset = __stream->ssize + __off;
    seek(__stream->fd, __stream->offset, SEEK_SET);
    break;
  default:
    printf("fseek whence error\n");
    return -1;
  }
  return -1;
}
long int ftell(FILE *__stream) {
  assert(__stream != NULL);
  // seek(__stream->fd,__stream->ssize,SEEK_SET);
  //__stream->offset = __stream->ssize;
  // return flen(__stream->fd);
  return __stream->offset;
}
void rewind(FILE *__stream) {
  assert(__stream != NULL);
  seek(__stream->fd, 0, SEEK_SET);
  __stream->offset = 0;
}
size_t fread(void *__restrict __ptr, size_t __size, size_t __n,
             FILE *__restrict __stream) {
  assert(__ptr != NULL);
  assert(__stream != NULL);
  size_t size     = __size * __n;
  size_t readsize = 0;
  if ((__stream->offset + size) >= __stream->ssize) {
    size = __stream->ssize - __stream->offset;
  }
  readsize = read(__stream->fd, __ptr, size);
  if (readsize != size) {
    printf("fread size error -> %d %d\n", size, readsize);
    return -1;
  }
  __stream->offset = __stream->offset + size;
  return readsize;
}
size_t fwrite(void *__restrict __ptr, size_t __size, size_t __n,
              FILE *__restrict __s) {
  assert(__ptr != NULL);
  assert(__s != NULL);
  size_t size      = __size * __n;
  size_t writesize = 0;
  writesize        = write(__s->fd, __ptr, size);
  if (writesize != size) {
    printf("fwrite size error -> %d %d\n", size, writesize);
    return -1;
  }
  __s->offset += size;
  return writesize;
}
int fprintf(FILE *__restrict __stream, char *__restrict fmt, ...) {
#define MAX_FPRINTF_BUF 256
  assert(__stream != NULL);
  va_list args;
  int len, writesize = 0;
  char buf[MAX_FPRINTF_BUF] = {0};
  va_start(args, fmt);
  //	memset(buf,0,MAX_FPRINTF_BUF);
  len = vsprintf(buf, fmt, args);
  va_end(args);
  len       = strlen(buf);
  writesize = write(__stream->fd, buf, len);
  if (writesize != len) {
    printf("fprintf write size error -> %d  %d\n", len, writesize);
    return -1;
  }
  __stream->offset += len;
  __stream->ssize += len;
  return len;
}
int fflush(FILE *__stream) {
  assert(__stream != NULL);
  return 0;
}
/**
 * @brief feof tests the end-of-file indicator for the stream pointed to by
 * stream, returning nonzero if it is set.
 *
 * @param __stream
 *
 * @return
 */
int feof(FILE *__stream) {
  return __stream->offset >= __stream->ssize ? -1 : 0;
}
