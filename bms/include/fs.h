#pragma once

#include <stdio.h>

extern void fs_init(void);
extern int open(const char *path, int flags);
extern ssize_t read(int fd, void *buf, size_t count);
extern size_t seek(int fd, ssize_t offset, int whence);
extern ssize_t flen(int fd);
extern uintptr_t  faddr(int fd);
extern int close(int fd);