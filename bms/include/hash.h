#ifndef __IUW_HASH_H__
#define __IUW_HASH_H__
enum hash_type {
  IUW_HASH_CRC = 0,
  IUW_HASH_MD5,
  IUW_HASH_SHA1,
  IUW_HASH_SHA256,
};

struct hash_module {
  const char *name;
  int len;
  int (*init)(uint32_t len);
  int (*data)(uint8_t *buf, uint32_t len);
  int (*value)(uint8_t *buf);
};

extern int register_hash_module(struct hash_module *m);
extern int lib_hash_init(const char *name, uint32_t len);
extern int lib_hash_data(void *buf, uint32_t len);
extern int lib_hash_value(void *buf);
extern int lib_hash_len(void);

#endif /* __IUW_HASH_H__ */
