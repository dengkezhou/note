#include <common.h>
#include <command.h>
#include <testbench.h>
#include <semihost.h>
#include <asm/io.h>
#include <asm/sizes.h>
#include <irq.h>
#include <rtlfs.h>
#include <crc32.h>
#include <malloc.h>
#include <hash.h>

struct file_desc {
  int fd;
  char *f;
  int l;
  int c;
};

int rtlfs_testwritesize(void) {
  int sz[] = {64, 32, 16, 8};
  int fd, i;
  char name[16];

  for (i = 0; i < ARRAY_SIZE(sz); i++) {
    sprintf(name, "test%d_%dk", i, sz[i]);
    printf("creating %s\n", name);
    fd = open(name, O_CREAT | O_WRONLY);
    if (fd < 0) {
      printf("create %s failed.\n", name);
      return -1;
    }

    write(fd, name, sz[i] << 10);
    close(fd);
    printf("done!\n");
  }
  return 0;
}

int rtlfs_testwrite(void) {
  int fd, i, j, count, sz, ret;
  uint8_t buf[2048], *p; /* just use the stack location */
  struct file_desc desc[] = {
      {-1, "folder1/write_1k", 1024},
      {-1, "this_is_a_big_very_very_very_long_folder/write_4k", 4096},
      {-1, "write_3.9k", 4095},
      {-1, "write_5k", 5021},
      {-1, "folder2/daughter/d2/write_3m", 3 * SZ_1M + 44},
      {-1, "folder2/daughter/d2/d3/write_5m", 5 * SZ_1M},
      {-1, "new_folder/write_1k", 1111},
  };

  printf("\n::: race writing test\n");
  /* create file */
  for (i = 0; i < ARRAY_SIZE(desc); i++) {
    desc[i].fd = open(desc[i].f, O_CREAT | O_WRONLY);
    if (desc[i].fd < 0) {
      printf("failed open: %s\n", desc[i].f);
      return -1;
    }

    if (desc[i].l > SZ_1M) {
      p = mmap(desc[i].fd, desc[i].l + 500 * SZ_1K);
      //			printf("mmapped file %p: %s\n", p, desc[i].f);
      munmap(desc[i].fd, 0);
    }
  }

  /* write file */
  for (i = 0; i < ARRAY_SIZE(desc); i++) {

    if (i < 2) { /* use write method */
      count = desc[i].l;
      lib_hash_init("crc32", count);
      while (count) {
        /* just fill buffer differently for every file */
        for (j = 0; j < 2048; j++)
          buf[j] = (uint8_t)((i << 3) | (desc[i].fd << 6) | count);

        sz  = count > 2048 ? 2048 : count;
        ret = write(desc[i].fd, buf, sz);
        lib_hash_data(buf, sz);

        if (ret != sz) {
          printf("write error: write %d, return %d\n", sz, ret);
        }

        count -= sz;
      }
    } else {
      lib_hash_init("crc32", desc[i].l);
      p = mmap(desc[i].fd, desc[i].l + 400 * SZ_1K);
      if (!p) {
        printf("failed to mmap %s\n", desc[i].f);
        continue;
      }
      memcpy(p, buf, desc[i].l);
      /* odd file unmap with exact size
       * even file unmap with 0 (use defaut size)
       */
      munmap(desc[i].fd, (i & 1) ? desc[i].l : 0);
      lib_hash_data(buf, desc[i].l);
    }

    lib_hash_value((void *)&desc[i].c);
    printf("write: %8d (size %s) %s\n", desc[i].l,
           ((i < 2) || (i & 1)) ? "fixed" : "float", desc[i].f);
  }

  /* close file & check routine
   * < 2: data in these files is provided by write, so
   *      the final file length is exact
   * odd: data in these files is unmap with exact length
   *      so the final length is exact too
   * even:data in these files is unmap with zero
   *      so the final length is the same with the mapped one,
   *      if mmap() does not provide @len either, final length
   *      will be RTLFS_CREATED_SIZE
   * the last file size equals to the mmap() size 410711 (1111 + 400K)
   */
  printf("\n::: race writing test result\n");
  for (i = 0; i < ARRAY_SIZE(desc); i++) {
    ret = close(desc[i].fd);
    if (ret) {
      printf("FAIL: failed to close file: %s\n", desc[i].f);
      continue;
    }

    fd = open(desc[i].f, O_RDONLY);
    if (fd < 0) {
      printf("FAIL: cannot open file: %s\n", desc[i].f);
      continue;
    }

    p = mmap(fd, 0);
    lib_hash_init("crc32", desc[i].l);
    lib_hash_data(p, desc[i].l);
    lib_hash_value((void *)&ret);
    munmap(fd, 0);

    if (ret != desc[i].c) {
      printf("FAIL: crc different (%08x, %08x), %s\n", desc[i].c, ret,
             desc[i].f);
      close(fd);
      continue;
    } else
      printf("OKAY: %8d %s\n", flen(fd), desc[i].f);

    close(fd);
  }

  /* exist test */
  printf("\n::: existence test\n");
  fd = open("folder2/daughter/d2/rnd_binary_4097", O_CREAT | O_WRONLY);
  if (fd < 0)
    printf("OKAY: exist test\n");
  else {
    printf("FAIL: exist test\n");
    return -1;
  }

  return 0;
}

int rtlfs_main(int argc, char *argv[]) {
  int fd, ret;
  uint8_t *buf;

  if (rtlfsck() < 0) {
    printf("rtlfs: not ready\n");
    return -1;
  }

  if (strncmp(argv[1], "ls", 2) == 0) {
    return rtlfs_list(0);
  } else if (strncmp(argv[1], "crc", 3) == 0) {
    return rtlfs_list(1);
  } else if (strncmp(argv[1], "readfile", 8) == 0) {
    if (argc < 3) {
      printf("rtlfs readfile PATH.\n");
      return -1;
    }

    fd = open(argv[2], O_RDONLY);
    printf("fd: %d\n", fd);

    if (fd == -1) {
      printf("fd: invalid.\n");
      return -1;
    }

    uintptr_t addr = faddr(fd);
    printf("file addr=0x%llx\n", addr);

    buf = (uint8_t *)malloc(0x100);
    ret = read(fd, buf, 0x100);
    printf("fd: %d bytes read.\n", ret);

    print_buffer((unsigned long)buf, (void *)buf, 4, 0x100 / 4, 4);
    ret = close(fd);

    printf("fd: closed (%d)\n", ret);
    free(buf);
  } else if (strncmp(argv[1], "size", 5) == 0) {
    rtlfs_testwritesize();
  } else if (strncmp(argv[1], "write", 5) == 0) {
    rtlfs_testwrite();
  }

  return 1;
}

void rtlfs_init(void) { register_testbench("rtlfs", rtlfs_main, NULL); }

testbench_init(rtlfs_init);
