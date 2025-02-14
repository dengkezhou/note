#pragma once

#include <pufs_memory_map.h>
#include <pufs_hmac.h>


#define HASH_SIZE 32

extern int sha256_file(const char *path, unsigned char *output, size_t start, size_t end);
extern int sha256_mem(const void *data, size_t len, unsigned char *output);