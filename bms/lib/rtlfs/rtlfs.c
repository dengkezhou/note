
/* generate rtlfs */
#include <common.h>
#include <semihost.h>
#include <command.h>
#include <initcall.h>
#include <crc32.h>
#include <rtlfs.h>

#define RTLFS_PAGE         0x1000    //4K
#define RTLFS_HEAD         0x100000  //1M support 4096 file&folders
#define RTLFS_CREATED_SIZE 0x40000000//1GB
#define RTLFS_COUNT        (int)(RTLFS_HEAD / sizeof(struct rtlfs_inode))
#if 0
extern void *__lds_rtl_data[];
struct rtlfs_inode {
  int offs;
  int size;
  int dau;
  int sib;
  char name[256 - sizeof(int) * 4];
} *fs = (struct rtlfs_inode *)__lds_rtl_data;
#else
struct rtlfs_inode {
  int offs;
  int size;
  int dau;
  int sib;
  char name[256 - sizeof(int) * 4];
} *fs  = (struct rtlfs_inode *)RTLFS_START_ADDR;
#endif

#define list_array_each(_a, _i, _h, _m) for (_i = _a[_i]._h; _i; _i = _a[_i]._m)

#define list_array_add(_a, _i, _h, _m, _j)                                     \
  ({                                                                           \
    for (_i = _a[_i]._h; _a[_i]._m; _i = _a[_i]._m)                            \
      ;                                                                        \
    _a[_i]._m = _j;                                                            \
    _a[_j]._m = 0;                                                             \
  })

#define list_array_empty(_a, _i, _h) (!_a[_i]._h)

#define list_array_entry(_a, _i, _h) (_a[_a[_i]._h])

int rtlfs_node_alloc(void) {
  int i;

  for (i = 0; i < RTLFS_COUNT; i++) {
    if (!fs[i].name[0])
      return i;
  }

  return -1;
}

int rtlfs_node_crc(int root) {
  if (fs[root].size >= 0)
    printf("%08x  %s\n",
           lib_crc32_le(0, (uint8_t *)fs + fs[root].offs, fs[root].size),
           fs[root].name);

  /* treat the first daughtor */
  if (!list_array_empty(fs, root, dau))
    rtlfs_node_crc(fs[root].dau);

  /* treat the first sibling */
  if (!list_array_empty(fs, root, sib))
    rtlfs_node_crc(fs[root].sib);

  return 0;
}

int rtlfs_node_list(int root, int parent, int indent) {
  int len = strlen(fs[root].name);

  printf("%*s%.*s %s\n", parent, "", indent,
         "|---------------------------"
         "----------------------------",
         fs[root].name);

  /* treat the first daughtor */
  if (!list_array_empty(fs, root, dau))
    rtlfs_node_list(fs[root].dau, parent + indent + 1, len + 1);

  /* treat the first sibling */
  if (!list_array_empty(fs, root, sib))
    rtlfs_node_list(fs[root].sib, parent, indent);

  return 0;
}

/* add node recursively ...
 * recursive ... recursive ...
 */
int rtlfs_node_get(int root, char *file) {
  char *p;
  int i = root;

  p = strsep(&file, "/");

  /* check if the first folder in file path alreadly
   * exists in * root's daughtours. If so, just treate
   * the sub-path still this way.
   */
  list_array_each(fs, i, dau, sib) if (strcmp(p, fs[i].name) == 0) {
    return file ? rtlfs_node_get(i, file) : i;
  }

  return -1;
}

int rtlfs_node_add(int root, char *file, int offs, int size) {
  char *p;
  int i = root, n;

  p = strsep(&file, "/");

  /* check if the first folder in file path alreadly
   * exists in * root's daughtours. If so, just treate
   * the sub-path still this way.
   */
  list_array_each(fs, i, dau, sib) if (strcmp(p, fs[i].name) == 0) {
    return file ? rtlfs_node_add(i, file, offs, size) : -1;
  }

  /* the first folder is not find, treate it as
   * a new one, alloc node and log information.
   */
  n = rtlfs_node_alloc();
  if (n < 0) {
    printf("alloc node failed.\n");
    return -1;
  }

  /* if the root have no daughtours yet, set this
   * first folder as her daughtour. If the root already
   * have a daughtour, set this first folder as her last
   * daughtour's sibling.
   */
  if (list_array_empty(fs, root, dau))
    fs[root].dau = n;
  else
    list_array_add(fs, root, dau, sib, n);

  fs[n].dau = 0;
  fs[n].sib = 0;
  strcpy(fs[n].name, p);
  if (!file) {
    fs[n].offs = offs;
    fs[n].size = size;
  } else {
    /* if this first folder is not the last entry,
     * treate her sub-path */
    rtlfs_node_add(n, file, offs, size);
    /* set size -1 to indicate a folder */
    fs[n].size = -1;
  }

  return 0;
}

#if 0
int rtlfs_file_add(int out, int in, int offs, int size) 
{
	int ret, buf[RTLFS_PAGE], count = 0;

//	printf("add file: %d bytes @0x%x\n", size, offs);
	ret = lseek(out, offs, SEEK_SET);
	if(ret & (RTLFS_PAGE - 1)) {
		printf("image is not aligned.\n");
		return -1;
	}

	lseek(in, 0, SEEK_SET);
	for(;;)
	{
		ret = read(in, buf, RTLFS_PAGE);
		/* write page_size,
		 * alway make the image 4K align */
		write(out, buf, RTLFS_PAGE);

		count += ret;
		if(ret < RTLFS_PAGE)
		  break;
	}

	return count;
}
#endif

int rtlfsck(void) { return strncmp(fs->name, "root/", 5) ? -1 : 0; }

int rtlfs_list(int crc) {
  if (rtlfsck() < 0) {
    printf("rtlfs: not ready\n");
    return -1;
  }

  printf("\nimage size: 0x%08x\n", fs->offs);
  printf("use the following to dump image:\n");
  printf("dump binary memory ~/rtl_data.bin 0x%p +0x%x\n\n", fs, fs->offs);

  if (crc)
    return rtlfs_node_crc(0);
  else
    return rtlfs_node_list(0, 0, 0);
}

#define FD_MAX 8
/* for fd for writing, @fd.size refers to the exect file size
 * which will grow whenever write() accours
 * @fs[i].size refers to the mmap(or default) length will will
 * be updated to exect length after munmap/close
 */
struct fd_bundle {
  int id;
  int pos;
  int flags;
  int size;
} fds[FD_MAX];

int fd_write_pending = -1;

int fd_alloc_bundle(void) {
  int i;

  for (i = 0; i < FD_MAX; i++)
    if (fds[i].id == -1) {
      /* set id -2, indicates used */
      fds[i].id = -2;
      return i;
    }

  /* no free node available */
  return -1;
}

int open(const char *path, int flags) {
  int i  = 0;
  int fd = -1;
  char file[256];

  if (strlen(path) > 255) {
    printf("rtlfs: cannot handle long path:\n %s\n", path);
    return -1;
  }

  strcpy(file, path);
  i = rtlfs_node_get(0, file);

  if (flags & (O_CREAT | O_WRONLY | O_RDWR)) {
    /* check if this file already exist */
    if (i >= 0) {
      printf("rtlfs: write to existing file denied\n");
      return -3;
    }

    /* fix rtlfs offset */
    if (fd_write_pending >= 0) {
      fs[fds[fd_write_pending].id].size =
          max(RTLFS_CREATED_SIZE, fds[fd_write_pending].size);
      fs->offs += fs[fds[fd_write_pending].id].size;
      fs->offs         = (fs->offs + RTLFS_PAGE) & ~(RTLFS_PAGE - 1);
      fd_write_pending = -1;
    }

    /* create file node in fs */
    strcpy(file, path);
    if (rtlfs_node_add(0, file, fs->offs, 0) < 0) {
      printf("rtlfs: duplicated node (%s)\n", path);
      return -2;
    }

    /* get the file node after add */
    strcpy(file, path);
    i = rtlfs_node_get(0, file);
  }

  if (i < 0) {
    //printf("rtlfs: cannot access: %s\n", path);
    return -1;
  }

  fd            = fd_alloc_bundle();
  fds[fd].id    = i;
  fds[fd].pos   = 0;
  fds[fd].flags = flags;

  if (flags & (O_CREAT | O_WRONLY | O_RDWR)) {
    fd_write_pending = fd;
    fds[fd].size     = 0;
  }

  return fd;
}

#define check_fd()                                                             \
  do {                                                                         \
    if (fd > FD_MAX) {                                                         \
      printf("accessing wrong fd: %d\n", fd);                                  \
      return -1;                                                               \
    }                                                                          \
  } while (0)

int close(int fd) {
  check_fd();

  /* set rtlfs node to exact length */
  if (fds[fd].flags & (O_CREAT | O_WRONLY | O_RDWR)) {
    fs[fds[fd].id].size = fds[fd].size;
    if (fd_write_pending >= 0) {
      fs->offs += fs[fds[fd_write_pending].id].size;
      fs->offs         = (fs->offs + RTLFS_PAGE) & ~(RTLFS_PAGE - 1);
      fd_write_pending = -1;
    }
  }

  fds[fd].id = -1;
  return 0;
}

ssize_t read(int fd, void *buf, size_t count) {
  check_fd();

  if (count + fds[fd].pos > fs[fds[fd].id].size)
    count = fs[fds[fd].id].size - fds[fd].pos;

  memcpy(buf, (void *)fs + fs[fds[fd].id].offs + fds[fd].pos, count);
  fds[fd].pos += count;

  return count;
}

/* if a new file is open/created, it's defaut length is set
 * to 1M. users can use mmap to enlarge(or shink) this value
 * only once.
 *
 * write attemps exceeding the length will fail
 */
ssize_t write(int fd, const void *buf, size_t count) {
  check_fd();

  if (fs[fds[fd].id].size && fds[fd].pos + count > fs[fds[fd].id].size)
    return -1;

  memcpy((void *)fs + fs[fds[fd].id].offs + fds[fd].pos, buf, count);

  fds[fd].pos += count;
  fds[fd].size = max(fds[fd].size, fds[fd].pos);
#if 0
	if(!(fds[fd].flags & (O_WRONLY | O_RDWR))) {
		printf("no write permission: fd (%d)\n", fd);
		return -1;
	}
#endif
  return count;
}

size_t seek(int fd, ssize_t offset, int whence) {
  check_fd();

  if (whence) {
    printf("rtlfs: whence only support SEEK_SET\n");
    return -1;
  }

  if (fds[fd].flags & (O_CREAT | O_WRONLY | O_RDWR)) {
    printf("rtlfs: cannot seek writing file.\n");
    return -1;
  }

  fds[fd].pos = min(offset, fs[fds[fd].id].size);

  /* user can use seek to enlarge file size */
  if (fds[fd].flags & (O_CREAT | O_WRONLY | O_RDWR))
    fds[fd].size = max(fds[fd].size, fds[fd].pos);

  return fds[fd].pos;
}

ssize_t flen(int fd) {
  check_fd();

  return fs[fds[fd].id].size;
}

uintptr_t  faddr(int fd) {
  check_fd();

  return (uintptr_t ) (RTLFS_START_ADDR + fs[fds[fd].id].offs);
}

void *mmap(int fd, int len) {
  if (fd > FD_MAX) {
    printf("accessing wrong fd: %d\n", fd);
    return NULL;
  }

  if (!len)
    goto __end;

  if (fds[fd].flags & (O_CREAT | O_WRONLY | O_RDWR)) {
    if (!fs[fds[fd].id].size) {
      fs[fds[fd].id].size = len;
      fs->offs += len;
      fs->offs = (fs->offs + RTLFS_PAGE) & ~(RTLFS_PAGE - 1);

      if (fd != fd_write_pending) {
        printf("rtlfs: BUG fd mapping.\n");
        for (;;)
          ;
      }

      fd_write_pending = -1;
    } else if (fs[fds[fd].id].size < len) {
      printf("rtlfs: file(%d) size is already fixed.\n", fd);
      return NULL;
    }
  }

__end:
  return (void *)fs + fs[fds[fd].id].offs;
}

/**
 * @brief munmap ,set file size to exact size ,old size is mmap size,
 * when read fd ,do not use munmap ,may cause file size damage
 * when write fd ,will resize the file size
 *
 * @param fd
 * @param len
 *
 * @return
 */
int munmap(int fd, int len) {
  check_fd();

  /* set file size to exact size */
  if (fds[fd].flags & (O_CREAT | O_WRONLY | O_RDWR))
    fds[fd].size = len ? len : fs[fds[fd].id].size;

  return 0;
}

void rtl_fops_init(void) {
  int i;

  /* init fd bundles */
  for (i = 0; i < FD_MAX; i++)
    fds[i].id = -1;
}

void fs_init(void) {
  rtl_fops_init();
}
module_init(fs_init);
