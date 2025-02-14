#include <common.h>
#include <crc32.h>
#include <hash.h>

#define MAX_HM_COUNT 8

static struct hash_module hm_list[MAX_HM_COUNT];
static int hm_count           = 0;
static struct hash_module *gm = NULL;

int register_hash_module(struct hash_module *m) {
  if (!m)
    return -1;

  printf("hash: add new module %s\n", m->name);
  memcpy((void *)&hm_list[hm_count], (void *)m, sizeof(struct hash_module));
  hm_count++;

  return 0;
}

struct hash_module *lib_hash_get_module(const char *name) {
  int i;
  for (i = 0; i < hm_count; i++) {
    if (strcmp(name, hm_list[i].name) == 0)
      return &hm_list[i];
  }

  return NULL;
}

int lib_hash_init(const char *name, uint32_t len) {
  struct hash_module *m = lib_hash_get_module(name);

  if (!m) {
    printf("hash: request hase module(%s) not found.\n", name);
    return -1;
  }

  gm = m;

  return gm->init(len);
}

int lib_hash_data(void *buf, uint32_t len) {
  if (!gm)
    return -1;

  return gm->data(buf, len);
}

int lib_hash_value(void *buf) {
  if (!gm)
    return -1;

  return gm->value(buf);
}

int lib_hash_len(void) {
  if (!gm)
    return -1;
  return gm->len;
}
