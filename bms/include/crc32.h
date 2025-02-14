
extern int lib_crc32_init(uint32_t len);
extern int lib_crc32_data(uint8_t *buf, uint32_t len);
extern int lib_crc32_value(uint8_t *buf);
extern uint32_t lib_crc32_le(uint32_t crc, unsigned char const *p, size_t len);
