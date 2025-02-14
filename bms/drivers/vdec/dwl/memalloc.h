#pragma once

#include <malloc.h>

extern void *aligned_malloc(size_t align, size_t size);
extern void aligned_free(void *ptr);
