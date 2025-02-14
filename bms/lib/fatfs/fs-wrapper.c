#include <initcall.h>
#include <ff.h>
#include <fs.h>

#define FD_MAX 8

static FIL fds[FD_MAX] = {0};

#define check_fd()                                                             \
  do {                                                                         \
    if (fd >= FD_MAX || fd < 0) {                                              \
      printf("accessing wrong fd: %d\n", fd);                                  \
      return -1;                                                               \
    }                                                                          \
  } while (0)

static int flag_remap(int flags)
{
    int ret = 0;
    if (flags == O_RDONLY)
        ret |= FA_READ;
    if (flags & O_WRONLY)
        ret |= FA_WRITE;
    if (flags & O_RDWR)
        ret |= FA_READ | FA_WRITE;
    if (flags & O_CREAT)
        ret |= FA_CREATE_ALWAYS;
    if (flags & O_TRUNC)
        ret |= FA_CREATE_ALWAYS;
    if (flags & O_APPEND)
        ret |= FA_OPEN_APPEND;
    return ret;
}

int open(const char *path, int flags)
{
    for (int i = 0; i < FD_MAX; i++)
    {
        if (!fds[i].obj.fs)
        {
            if (f_open(&fds[i], path, flag_remap(flags)) == FR_OK)
                return i;
            else
                return -1;
        }
    }
    return -1;
}

int close(int fd)
{
    check_fd();

    if (f_close(&fds[fd]) == FR_OK)
        return 0;
    else
        return -1;
}

ssize_t read(int fd, void *buf, size_t count)
{
    UINT br;
    check_fd();

    if (f_read(&fds[fd], buf, count, &br) == FR_OK)
        return br;
    else
        return -1;

}
size_t seek(int fd, ssize_t offset, int whence)
{
    check_fd();

    if (f_lseek(&fds[fd], offset) == FR_OK)
        return offset;
    else
        return -1;

}
ssize_t flen(int fd)
{
    check_fd();

    return f_size(&fds[fd]);
}

uintptr_t faddr(int fd)
{
    return 0;
}



