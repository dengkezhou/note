#include <npu.h>
// #include <rtlfs.h>

#ifdef CONFIG_TB_RUN_DDR1
#define  VERIFY_EVB_ADDR   0x540000000
#else
#define  VERIFY_EVB_ADDR   0x140000000
#endif
// #define  EVB_RESULT_ADDR   0x146000000




static unsigned int base0 = 0xC7000000;
static unsigned int base1 = 0xC7800000;
// static unsigned long int base0 = 0xC7000000;
// static unsigned long int base1 = 0x101000000;

static int rd_val = 0x1;
static int total_size = 0;
char result_file_name[128] = {0};



#ifdef CONFIG_COMPILE_RTL
extern int __lds_print[];
static inline void soc_cmd(int cmd)
{
  volatile int *addr_ptr = (int *)__lds_print;
  *addr_ptr = cmd;
#ifdef CONFIG_C920
  asm("sync.is");
#endif
}
#endif

unsigned char mem3_tlb_buf_bin[] = {
  0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0x15, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x01, 0x15, 0x00, 0x00, 0x02,
  0x15, 0x00, 0x00, 0x03, 0x15, 0x00, 0x00, 0x04, 0x15, 0x00, 0x00, 0x05,
  0x15, 0x00, 0x00, 0x06, 0x15, 0x00, 0x00, 0x07, 0x15, 0x00, 0x00, 0x08,
  0x15, 0x00, 0x00, 0x09, 0x15, 0x00, 0x00, 0x0a, 0x15, 0x00, 0x00, 0x0b,
  0x15, 0x00, 0x00, 0x0c, 0x15, 0x00, 0x00, 0x0d, 0x15, 0x00, 0x00, 0x0e,
  0x15, 0x00, 0x00, 0x0f, 0x15, 0x00, 0x00, 0x10, 0x15, 0x00, 0x00, 0x11,
  0x15, 0x00, 0x00, 0x12, 0x15, 0x00, 0x00, 0x13, 0x15, 0x00, 0x00, 0x14,
  0x15, 0x00, 0x00, 0x15, 0x15, 0x00, 0x00, 0x16, 0x15, 0x00, 0x00, 0x17,
  0x15, 0x00, 0x00, 0x18, 0x15, 0x00, 0x00, 0x19, 0x15, 0x00, 0x00, 0x1a,
  0x15, 0x00, 0x00, 0x1b, 0x15, 0x00, 0x00, 0x1c, 0x15, 0x00, 0x00, 0x1d,
  0x15, 0x00, 0x00, 0x1e, 0x15, 0x00, 0x00, 0x1f, 0x15, 0x00, 0x00, 0x20,
  0x15, 0x00, 0x00, 0x21, 0x15, 0x00, 0x00, 0x22, 0x15, 0x00, 0x00, 0x23,
  0x15, 0x00, 0x00, 0x24, 0x15, 0x00, 0x00, 0x25, 0x15, 0x00, 0x00, 0x26,
  0x15, 0x00, 0x00, 0x27, 0x15, 0x00, 0x00, 0x28, 0x15, 0x00, 0x00, 0x29,
  0x15, 0x00, 0x00, 0x2a, 0x15, 0x00, 0x00, 0x2b, 0x15, 0x00, 0x00, 0x2c,
  0x15, 0x00, 0x00, 0x2d, 0x15, 0x00, 0x00, 0x2e, 0x15, 0x00, 0x00, 0x2f,
  0x15, 0x00, 0x00, 0x30, 0x15, 0x00, 0x00, 0x31, 0x15, 0x00, 0x00, 0x32,
  0x15, 0x00, 0x00, 0x33, 0x15, 0x00, 0x00, 0x34, 0x15, 0x00, 0x00, 0x35,
  0x15, 0x00, 0x00, 0x36, 0x15, 0x00, 0x00, 0x37, 0x15, 0x00, 0x00, 0x38,
  0x15, 0x00, 0x00, 0x39, 0x15, 0x00, 0x00, 0x3a, 0x15, 0x00, 0x00, 0x3b,
  0x15, 0x00, 0x00, 0x3c, 0x15, 0x00, 0x00, 0x3d, 0x15, 0x00, 0x00, 0x3e,
  0x15, 0x00, 0x00, 0x3f, 0x15, 0x00, 0x00, 0x40, 0x15, 0x00, 0x00, 0x41,
  0x15, 0x00, 0x00, 0x42, 0x15, 0x00, 0x00, 0x43, 0x15, 0x00, 0x00, 0x44,
  0x15, 0x00, 0x00, 0x45, 0x15, 0x00, 0x00, 0x46, 0x15, 0x00, 0x00, 0x47,
  0x15, 0x00, 0x00, 0x48, 0x15, 0x00, 0x00, 0x49, 0x15, 0x00, 0x00, 0x4a,
  0x15, 0x00, 0x00, 0x4b, 0x15, 0x00, 0x00, 0x4c, 0x15, 0x00, 0x00, 0x4d,
  0x15, 0x00, 0x00, 0x4e, 0x15, 0x00, 0x00, 0x4f, 0x15, 0x00, 0x00, 0x50,
  0x15, 0x00, 0x00, 0x51, 0x15, 0x00, 0x00, 0x52, 0x15, 0x00, 0x00, 0x53,
  0x15, 0x00, 0x00, 0x54, 0x15, 0x00, 0x00, 0x55, 0x15, 0x00, 0x00, 0x56,
  0x15, 0x00, 0x00, 0x57, 0x15, 0x00, 0x00, 0x58, 0x15, 0x00, 0x00, 0x59,
  0x15, 0x00, 0x00, 0x5a, 0x15, 0x00, 0x00, 0x5b, 0x15, 0x00, 0x00, 0x5c,
  0x15, 0x00, 0x00, 0x5d, 0x15, 0x00, 0x00, 0x5e, 0x15, 0x00, 0x00, 0x5f,
  0x15, 0x00, 0x00, 0x60, 0x15, 0x00, 0x00, 0x61, 0x15, 0x00, 0x00, 0x62,
  0x15, 0x00, 0x00, 0x63, 0x15, 0x00, 0x00, 0x64, 0x15, 0x00, 0x00, 0x65,
  0x15, 0x00, 0x00, 0x66, 0x15, 0x00, 0x00, 0x67, 0x15, 0x00, 0x00, 0x68,
  0x15, 0x00, 0x00, 0x69, 0x15, 0x00, 0x00, 0x6a, 0x15, 0x00, 0x00, 0x6b,
  0x15, 0x00, 0x00, 0x6c, 0x15, 0x00, 0x00, 0x6d, 0x15, 0x00, 0x00, 0x6e,
  0x15, 0x00, 0x00, 0x6f, 0x15, 0x00, 0x00, 0x70, 0x15, 0x00, 0x00, 0x71,
  0x15, 0x00, 0x00, 0x72, 0x15, 0x00, 0x00, 0x73, 0x15, 0x00, 0x00, 0x74,
  0x15, 0x00, 0x00, 0x75, 0x15, 0x00, 0x00, 0x76, 0x15, 0x00, 0x00, 0x77,
  0x15, 0x00, 0x00, 0x78, 0x15, 0x00, 0x00, 0x79, 0x15, 0x00, 0x00, 0x7a,
  0x15, 0x00, 0x00, 0x7b, 0x15, 0x00, 0x00, 0x7c, 0x15, 0x00, 0x00, 0x7d,
  0x15, 0x00, 0x00, 0x7e, 0x15, 0x00, 0x00, 0x7f, 0x15, 0x00, 0x00, 0x80,
  0x15, 0x00, 0x00, 0x81, 0x15, 0x00, 0x00, 0x82, 0x15, 0x00, 0x00, 0x83,
  0x15, 0x00, 0x00, 0x84, 0x15, 0x00, 0x00, 0x85, 0x15, 0x00, 0x00, 0x86,
  0x15, 0x00, 0x00, 0x87, 0x15, 0x00, 0x00, 0x88, 0x15, 0x00, 0x00, 0x89,
  0x15, 0x00, 0x00, 0x8a, 0x15, 0x00, 0x00, 0x8b, 0x15, 0x00, 0x00, 0x8c,
  0x15, 0x00, 0x00, 0x8d, 0x15, 0x00, 0x00, 0x8e, 0x15, 0x00, 0x00, 0x8f,
  0x15, 0x00, 0x00, 0x90, 0x15, 0x00, 0x00, 0x91, 0x15, 0x00, 0x00, 0x92,
  0x15, 0x00, 0x00, 0x93, 0x15, 0x00, 0x00, 0x94, 0x15, 0x00, 0x00, 0x95,
  0x15, 0x00, 0x00, 0x96, 0x15, 0x00, 0x00, 0x97, 0x15, 0x00, 0x00, 0x98,
  0x15, 0x00, 0x00, 0x99, 0x15, 0x00, 0x00, 0x9a, 0x15, 0x00, 0x00, 0x9b,
  0x15, 0x00, 0x00, 0x9c, 0x15, 0x00, 0x00, 0x9d, 0x15, 0x00, 0x00, 0x9e,
  0x15, 0x00, 0x00, 0x9f, 0x15, 0x00, 0x00, 0xa0, 0x15, 0x00, 0x00, 0xa1,
  0x15, 0x00, 0x00, 0xa2, 0x15, 0x00, 0x00, 0xa3, 0x15, 0x00, 0x00, 0xa4,
  0x15, 0x00, 0x00, 0xa5, 0x15, 0x00, 0x00, 0xa6, 0x15, 0x00, 0x00, 0xa7,
  0x15, 0x00, 0x00, 0xa8, 0x15, 0x00, 0x00, 0xa9, 0x15, 0x00, 0x00, 0xaa,
  0x15, 0x00, 0x00, 0xab, 0x15, 0x00, 0x00, 0xac, 0x15, 0x00, 0x00, 0xad,
  0x15, 0x00, 0x00, 0xae, 0x15, 0x00, 0x00, 0xaf, 0x15, 0x00, 0x00, 0xb0,
  0x15, 0x00, 0x00, 0xb1, 0x15, 0x00, 0x00, 0xb2, 0x15, 0x00, 0x00, 0xb3,
  0x15, 0x00, 0x00, 0xb4, 0x15, 0x00, 0x00, 0xb5, 0x15, 0x00, 0x00, 0xb6,
  0x15, 0x00, 0x00, 0xb7, 0x15, 0x00, 0x00, 0xb8, 0x15, 0x00, 0x00, 0xb9,
  0x15, 0x00, 0x00, 0xba, 0x15, 0x00, 0x00, 0xbb, 0x15, 0x00, 0x00, 0xbc,
  0x15, 0x00, 0x00, 0xbd, 0x15, 0x00, 0x00, 0xbe, 0x15, 0x00, 0x00, 0xbf,
  0x15, 0x00, 0x00, 0xc0, 0x15, 0x00, 0x00, 0xc1, 0x15, 0x00, 0x00, 0xc2,
  0x15, 0x00, 0x00, 0xc3, 0x15, 0x00, 0x00, 0xc4, 0x15, 0x00, 0x00, 0xc5,
  0x15, 0x00, 0x00, 0xc6, 0x15, 0x00, 0x00, 0xc7, 0x15, 0x00, 0x00, 0xc8,
  0x15, 0x00, 0x00, 0xc9, 0x15, 0x00, 0x00, 0xca, 0x15, 0x00, 0x00, 0xcb,
  0x15, 0x00, 0x00, 0xcc, 0x15, 0x00, 0x00, 0xcd, 0x15, 0x00, 0x00, 0xce,
  0x15, 0x00, 0x00, 0xcf, 0x15, 0x00, 0x00, 0xd0, 0x15, 0x00, 0x00, 0xd1,
  0x15, 0x00, 0x00, 0xd2, 0x15, 0x00, 0x00, 0xd3, 0x15, 0x00, 0x00, 0xd4,
  0x15, 0x00, 0x00, 0xd5, 0x15, 0x00, 0x00, 0xd6, 0x15, 0x00, 0x00, 0xd7,
  0x15, 0x00, 0x00, 0xd8, 0x15, 0x00, 0x00, 0xd9, 0x15, 0x00, 0x00, 0xda,
  0x15, 0x00, 0x00, 0xdb, 0x15, 0x00, 0x00, 0xdc, 0x15, 0x00, 0x00, 0xdd,
  0x15, 0x00, 0x00, 0xde, 0x15, 0x00, 0x00, 0xdf, 0x15, 0x00, 0x00, 0xe0,
  0x15, 0x00, 0x00, 0xe1, 0x15, 0x00, 0x00, 0xe2, 0x15, 0x00, 0x00, 0xe3,
  0x15, 0x00, 0x00, 0xe4, 0x15, 0x00, 0x00, 0xe5, 0x15, 0x00, 0x00, 0xe6,
  0x15, 0x00, 0x00, 0xe7, 0x15, 0x00, 0x00, 0xe8, 0x15, 0x00, 0x00, 0xe9,
  0x15, 0x00, 0x00, 0xea, 0x15, 0x00, 0x00, 0xeb, 0x15, 0x00, 0x00, 0xec,
  0x15, 0x00, 0x00, 0xed, 0x15, 0x00, 0x00, 0xee, 0x15, 0x00, 0x00, 0xef,
  0x15, 0x00, 0x00, 0xf0, 0x15, 0x00, 0x00, 0xf1, 0x15, 0x00, 0x00, 0xf2,
  0x15, 0x00, 0x00, 0xf3, 0x15, 0x00, 0x00, 0xf4, 0x15, 0x00, 0x00, 0xf5,
  0x15, 0x00, 0x00, 0xf6, 0x15, 0x00, 0x00, 0xf7, 0x15, 0x00, 0x00, 0xf8,
  0x15, 0x00, 0x00, 0xf9, 0x15, 0x00, 0x00, 0xfa, 0x15, 0x00, 0x00, 0xfb,
  0x15, 0x00, 0x00, 0xfc, 0x15, 0x00, 0x00, 0xfd, 0x15, 0x00, 0x00, 0xfe,
  0x15, 0x00, 0x00, 0xff
};


unsigned char mem3_tlb_buf_bin_ddr1[] = {
  0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff, 0x0d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff, 0x4d, 0x04, 0x00, 0xff,
  0x4d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff,
  0x8d, 0x04, 0x00, 0xff, 0x8d, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff, 0xcd, 0x04, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff, 0x0d, 0x05, 0x00, 0xff,
  0x0d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff,
  0x4d, 0x05, 0x00, 0xff, 0x4d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff, 0x8d, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff, 0xcd, 0x05, 0x00, 0xff,
  0xcd, 0x05, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff,
  0x0d, 0x06, 0x00, 0xff, 0x0d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff, 0x4d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff, 0x8d, 0x06, 0x00, 0xff,
  0x8d, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff,
  0xcd, 0x06, 0x00, 0xff, 0xcd, 0x06, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff, 0x0d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff, 0x4d, 0x07, 0x00, 0xff,
  0x4d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff,
  0x8d, 0x07, 0x00, 0xff, 0x8d, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff, 0xcd, 0x07, 0x00, 0xff,
  0x55, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x01, 0x55, 0x00, 0x00, 0x02,
  0x55, 0x00, 0x00, 0x03, 0x55, 0x00, 0x00, 0x04, 0x55, 0x00, 0x00, 0x05,
  0x55, 0x00, 0x00, 0x06, 0x55, 0x00, 0x00, 0x07, 0x55, 0x00, 0x00, 0x08,
  0x55, 0x00, 0x00, 0x09, 0x55, 0x00, 0x00, 0x0a, 0x55, 0x00, 0x00, 0x0b,
  0x55, 0x00, 0x00, 0x0c, 0x55, 0x00, 0x00, 0x0d, 0x55, 0x00, 0x00, 0x0e,
  0x55, 0x00, 0x00, 0x0f, 0x55, 0x00, 0x00, 0x10, 0x55, 0x00, 0x00, 0x11,
  0x55, 0x00, 0x00, 0x12, 0x55, 0x00, 0x00, 0x13, 0x55, 0x00, 0x00, 0x14,
  0x55, 0x00, 0x00, 0x15, 0x55, 0x00, 0x00, 0x16, 0x55, 0x00, 0x00, 0x17,
  0x55, 0x00, 0x00, 0x18, 0x55, 0x00, 0x00, 0x19, 0x55, 0x00, 0x00, 0x1a,
  0x55, 0x00, 0x00, 0x1b, 0x55, 0x00, 0x00, 0x1c, 0x55, 0x00, 0x00, 0x1d,
  0x55, 0x00, 0x00, 0x1e, 0x55, 0x00, 0x00, 0x1f, 0x55, 0x00, 0x00, 0x20,
  0x55, 0x00, 0x00, 0x21, 0x55, 0x00, 0x00, 0x22, 0x55, 0x00, 0x00, 0x23,
  0x55, 0x00, 0x00, 0x24, 0x55, 0x00, 0x00, 0x25, 0x55, 0x00, 0x00, 0x26,
  0x55, 0x00, 0x00, 0x27, 0x55, 0x00, 0x00, 0x28, 0x55, 0x00, 0x00, 0x29,
  0x55, 0x00, 0x00, 0x2a, 0x55, 0x00, 0x00, 0x2b, 0x55, 0x00, 0x00, 0x2c,
  0x55, 0x00, 0x00, 0x2d, 0x55, 0x00, 0x00, 0x2e, 0x55, 0x00, 0x00, 0x2f,
  0x55, 0x00, 0x00, 0x30, 0x55, 0x00, 0x00, 0x31, 0x55, 0x00, 0x00, 0x32,
  0x55, 0x00, 0x00, 0x33, 0x55, 0x00, 0x00, 0x34, 0x55, 0x00, 0x00, 0x35,
  0x55, 0x00, 0x00, 0x36, 0x55, 0x00, 0x00, 0x37, 0x55, 0x00, 0x00, 0x38,
  0x55, 0x00, 0x00, 0x39, 0x55, 0x00, 0x00, 0x3a, 0x55, 0x00, 0x00, 0x3b,
  0x55, 0x00, 0x00, 0x3c, 0x55, 0x00, 0x00, 0x3d, 0x55, 0x00, 0x00, 0x3e,
  0x55, 0x00, 0x00, 0x3f, 0x55, 0x00, 0x00, 0x40, 0x55, 0x00, 0x00, 0x41,
  0x55, 0x00, 0x00, 0x42, 0x55, 0x00, 0x00, 0x43, 0x55, 0x00, 0x00, 0x44,
  0x55, 0x00, 0x00, 0x45, 0x55, 0x00, 0x00, 0x46, 0x55, 0x00, 0x00, 0x47,
  0x55, 0x00, 0x00, 0x48, 0x55, 0x00, 0x00, 0x49, 0x55, 0x00, 0x00, 0x4a,
  0x55, 0x00, 0x00, 0x4b, 0x55, 0x00, 0x00, 0x4c, 0x55, 0x00, 0x00, 0x4d,
  0x55, 0x00, 0x00, 0x4e, 0x55, 0x00, 0x00, 0x4f, 0x55, 0x00, 0x00, 0x50,
  0x55, 0x00, 0x00, 0x51, 0x55, 0x00, 0x00, 0x52, 0x55, 0x00, 0x00, 0x53,
  0x55, 0x00, 0x00, 0x54, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x56,
  0x55, 0x00, 0x00, 0x57, 0x55, 0x00, 0x00, 0x58, 0x55, 0x00, 0x00, 0x59,
  0x55, 0x00, 0x00, 0x5a, 0x55, 0x00, 0x00, 0x5b, 0x55, 0x00, 0x00, 0x5c,
  0x55, 0x00, 0x00, 0x5d, 0x55, 0x00, 0x00, 0x5e, 0x55, 0x00, 0x00, 0x5f,
  0x55, 0x00, 0x00, 0x60, 0x55, 0x00, 0x00, 0x61, 0x55, 0x00, 0x00, 0x62,
  0x55, 0x00, 0x00, 0x63, 0x55, 0x00, 0x00, 0x64, 0x55, 0x00, 0x00, 0x65,
  0x55, 0x00, 0x00, 0x66, 0x55, 0x00, 0x00, 0x67, 0x55, 0x00, 0x00, 0x68,
  0x55, 0x00, 0x00, 0x69, 0x55, 0x00, 0x00, 0x6a, 0x55, 0x00, 0x00, 0x6b,
  0x55, 0x00, 0x00, 0x6c, 0x55, 0x00, 0x00, 0x6d, 0x55, 0x00, 0x00, 0x6e,
  0x55, 0x00, 0x00, 0x6f, 0x55, 0x00, 0x00, 0x70, 0x55, 0x00, 0x00, 0x71,
  0x55, 0x00, 0x00, 0x72, 0x55, 0x00, 0x00, 0x73, 0x55, 0x00, 0x00, 0x74,
  0x55, 0x00, 0x00, 0x75, 0x55, 0x00, 0x00, 0x76, 0x55, 0x00, 0x00, 0x77,
  0x55, 0x00, 0x00, 0x78, 0x55, 0x00, 0x00, 0x79, 0x55, 0x00, 0x00, 0x7a,
  0x55, 0x00, 0x00, 0x7b, 0x55, 0x00, 0x00, 0x7c, 0x55, 0x00, 0x00, 0x7d,
  0x55, 0x00, 0x00, 0x7e, 0x55, 0x00, 0x00, 0x7f, 0x55, 0x00, 0x00, 0x80,
  0x55, 0x00, 0x00, 0x81, 0x55, 0x00, 0x00, 0x82, 0x55, 0x00, 0x00, 0x83,
  0x55, 0x00, 0x00, 0x84, 0x55, 0x00, 0x00, 0x85, 0x55, 0x00, 0x00, 0x86,
  0x55, 0x00, 0x00, 0x87, 0x55, 0x00, 0x00, 0x88, 0x55, 0x00, 0x00, 0x89,
  0x55, 0x00, 0x00, 0x8a, 0x55, 0x00, 0x00, 0x8b, 0x55, 0x00, 0x00, 0x8c,
  0x55, 0x00, 0x00, 0x8d, 0x55, 0x00, 0x00, 0x8e, 0x55, 0x00, 0x00, 0x8f,
  0x55, 0x00, 0x00, 0x90, 0x55, 0x00, 0x00, 0x91, 0x55, 0x00, 0x00, 0x92,
  0x55, 0x00, 0x00, 0x93, 0x55, 0x00, 0x00, 0x94, 0x55, 0x00, 0x00, 0x95,
  0x55, 0x00, 0x00, 0x96, 0x55, 0x00, 0x00, 0x97, 0x55, 0x00, 0x00, 0x98,
  0x55, 0x00, 0x00, 0x99, 0x55, 0x00, 0x00, 0x9a, 0x55, 0x00, 0x00, 0x9b,
  0x55, 0x00, 0x00, 0x9c, 0x55, 0x00, 0x00, 0x9d, 0x55, 0x00, 0x00, 0x9e,
  0x55, 0x00, 0x00, 0x9f, 0x55, 0x00, 0x00, 0xa0, 0x55, 0x00, 0x00, 0xa1,
  0x55, 0x00, 0x00, 0xa2, 0x55, 0x00, 0x00, 0xa3, 0x55, 0x00, 0x00, 0xa4,
  0x55, 0x00, 0x00, 0xa5, 0x55, 0x00, 0x00, 0xa6, 0x55, 0x00, 0x00, 0xa7,
  0x55, 0x00, 0x00, 0xa8, 0x55, 0x00, 0x00, 0xa9, 0x55, 0x00, 0x00, 0xaa,
  0x55, 0x00, 0x00, 0xab, 0x55, 0x00, 0x00, 0xac, 0x55, 0x00, 0x00, 0xad,
  0x55, 0x00, 0x00, 0xae, 0x55, 0x00, 0x00, 0xaf, 0x55, 0x00, 0x00, 0xb0,
  0x55, 0x00, 0x00, 0xb1, 0x55, 0x00, 0x00, 0xb2, 0x55, 0x00, 0x00, 0xb3,
  0x55, 0x00, 0x00, 0xb4, 0x55, 0x00, 0x00, 0xb5, 0x55, 0x00, 0x00, 0xb6,
  0x55, 0x00, 0x00, 0xb7, 0x55, 0x00, 0x00, 0xb8, 0x55, 0x00, 0x00, 0xb9,
  0x55, 0x00, 0x00, 0xba, 0x55, 0x00, 0x00, 0xbb, 0x55, 0x00, 0x00, 0xbc,
  0x55, 0x00, 0x00, 0xbd, 0x55, 0x00, 0x00, 0xbe, 0x55, 0x00, 0x00, 0xbf,
  0x55, 0x00, 0x00, 0xc0, 0x55, 0x00, 0x00, 0xc1, 0x55, 0x00, 0x00, 0xc2,
  0x55, 0x00, 0x00, 0xc3, 0x55, 0x00, 0x00, 0xc4, 0x55, 0x00, 0x00, 0xc5,
  0x55, 0x00, 0x00, 0xc6, 0x55, 0x00, 0x00, 0xc7, 0x55, 0x00, 0x00, 0xc8,
  0x55, 0x00, 0x00, 0xc9, 0x55, 0x00, 0x00, 0xca, 0x55, 0x00, 0x00, 0xcb,
  0x55, 0x00, 0x00, 0xcc, 0x55, 0x00, 0x00, 0xcd, 0x55, 0x00, 0x00, 0xce,
  0x55, 0x00, 0x00, 0xcf, 0x55, 0x00, 0x00, 0xd0, 0x55, 0x00, 0x00, 0xd1,
  0x55, 0x00, 0x00, 0xd2, 0x55, 0x00, 0x00, 0xd3, 0x55, 0x00, 0x00, 0xd4,
  0x55, 0x00, 0x00, 0xd5, 0x55, 0x00, 0x00, 0xd6, 0x55, 0x00, 0x00, 0xd7,
  0x55, 0x00, 0x00, 0xd8, 0x55, 0x00, 0x00, 0xd9, 0x55, 0x00, 0x00, 0xda,
  0x55, 0x00, 0x00, 0xdb, 0x55, 0x00, 0x00, 0xdc, 0x55, 0x00, 0x00, 0xdd,
  0x55, 0x00, 0x00, 0xde, 0x55, 0x00, 0x00, 0xdf, 0x55, 0x00, 0x00, 0xe0,
  0x55, 0x00, 0x00, 0xe1, 0x55, 0x00, 0x00, 0xe2, 0x55, 0x00, 0x00, 0xe3,
  0x55, 0x00, 0x00, 0xe4, 0x55, 0x00, 0x00, 0xe5, 0x55, 0x00, 0x00, 0xe6,
  0x55, 0x00, 0x00, 0xe7, 0x55, 0x00, 0x00, 0xe8, 0x55, 0x00, 0x00, 0xe9,
  0x55, 0x00, 0x00, 0xea, 0x55, 0x00, 0x00, 0xeb, 0x55, 0x00, 0x00, 0xec,
  0x55, 0x00, 0x00, 0xed, 0x55, 0x00, 0x00, 0xee, 0x55, 0x00, 0x00, 0xef,
  0x55, 0x00, 0x00, 0xf0, 0x55, 0x00, 0x00, 0xf1, 0x55, 0x00, 0x00, 0xf2,
  0x55, 0x00, 0x00, 0xf3, 0x55, 0x00, 0x00, 0xf4, 0x55, 0x00, 0x00, 0xf5,
  0x55, 0x00, 0x00, 0xf6, 0x55, 0x00, 0x00, 0xf7, 0x55, 0x00, 0x00, 0xf8,
  0x55, 0x00, 0x00, 0xf9, 0x55, 0x00, 0x00, 0xfa, 0x55, 0x00, 0x00, 0xfb,
  0x55, 0x00, 0x00, 0xfc, 0x55, 0x00, 0x00, 0xfd, 0x55, 0x00, 0x00, 0xfe,
  0x55, 0x00, 0x00, 0xff
};



#ifdef CONFIG_COMPILE_RTL
void soc_dump0(uint64_t src_addr, uint32_t size) { 
    //////////// memory dump test///////
    uint32_t cmd_type ;

    // printf("dump 0x%0lx size 0x%0x\n", src_addr, size);

       // memory dump with 64 align

    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( size            & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((size     >> 16) & 0xffff) << 16) | 0xa5fd);
// #ifdef CONFIG_TB_RUN_DDR1
//     cmd_type    = 0x24; 
// #else 
    cmd_type    = 0x25; 
// #endif
    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);
}
#else

void soc_dump0(uint64_t src_addr, uint32_t size) { 
    //////////// memory dump test///////
    // printf("cur dump size %d\n",total_size);
    int ral_size = size - 0x8;
    memcpy((char *)VERIFY_EVB_ADDR + total_size,(char*)src_addr,ral_size);

    total_size += ral_size;
}
int soc_dump0_compare(uint64_t src_addr, uint32_t size) { 
    //////////// memory dump test///////
    int ral_size = size - 0x8;
    int fd = open(result_file_name,O_RDONLY);
#if EVB_DEBUG_LOG
    printf("cur total size %d\n",total_size);
    printf("cur dump size %d\n",ral_size);
    printf("result %s\n",result_file_name);
#endif

    if(fd < 0){
        printf("open result file failed\n");
        return -1;
    }
    uint64_t result = faddr(fd);

    close(fd);
    char *result_addr = ((char*)result+total_size);
    int ret = 0;
#if EVB_DEBUG_LOG
    printf("src addr %x .result addr %x\n",src_addr,result_addr);
#endif
    total_size += ral_size;
    for(int i =0 ; i< ral_size; i++){
        if(((char*)src_addr)[i] != result_addr[i]){
           
            if(result_addr[i] == 0){
                continue;
            }
#if EVB_DEBUG_LOG
            printf("offset %d\n",i);
            printf("dst %x\n",((char*)src_addr)[i]);
            printf("src %x\n",result_addr[i]);
#endif
            printf("This test case is Failed\n");
            result_addr = NULL;
            return -1;
        }
    } 
    // int ret = memcmp((char *)src_addr,(char*)result_addr+total_size,ral_size);
    if(ret == 0){
        printf("cur compare pass\n");
    }else{
        printf("cur compare failed\n");
    }
    result_addr = NULL;
    
    return ret;
}
#endif

void print_buf(char *buf, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%02x ", buf[i]);
    if (i % 32 == 0)
      printf("\n");
  }
  printf("\n\n");
}

int print_idle_register(){
    printf("npu0 idle 0x%x\n",MA_INW(base0+0x04));
    printf("npu1 idle 0x%x\n",MA_INW(base1+0x04));

    return 0;
}



int npu_compare_argv(const char *filename,char * src_addr){

    int fd = open(filename,O_RDONLY);
    int ret = 0;
    if (fd < 0) {
        printf("Fail to open %s\n", filename);
        return fd;
    }
    printf("load %s\n",filename);
    int result_size = flen(fd); 
    
    
    printf("result size %d \n",result_size);
    // int size = flen(fd);
#if 1
    uint64_t des_addr = faddr(fd);
    printf("cmp result addr %x\n",des_addr);
    ret = memcmp(src_addr,(char *)des_addr,result_size);
    printf("ret value %d\n",ret);
    if(ret == 0){
         printf("This test case is Pass\n");
         return ret;
    }
#else
    ret =  memcmp((char *)VERIFY_EVB_ADDR,(char *)EVB_RESULT_ADDR,result_size);
#endif
    // print_buf((char *)EVB_RESULT_ADDR,result_size);
    for(int i =0 ; i< result_size; i++){
        if(src_addr[i]!=((char *)des_addr)[i]){
            printf("offset %d\n",i);
            // printf("dst %x\n",((int*)EVB_RESULT_ADDR)[i]);
            printf("src %x\n",((int*)VERIFY_EVB_ADDR)[i]);
            printf("This test case is Failed\n");
            return -1;
        }
    }  
    ret =0;
    close(fd);
    if(ret == 0){
        printf("This test case is Pass\n");
    }else{
        printf("This test case is Failed\n");
    }
    return ret;
}

int npu_compare(const char *filename){

    int fd = open(filename,O_RDONLY);
    int ret = 0;
    if (fd < 0) {
        printf("Fail to open %s\n", filename);
        return fd;
    }
    printf("load %s\n",filename);
    int result_size = flen(fd); 
    
    printf("result size %d \n",result_size);
  
    // int size = flen(fd);
#if 1
    uint64_t des_addr = faddr(fd);
    printf("cmp result addr %x\n",des_addr);
    ret = memcmp((char *)VERIFY_EVB_ADDR,(char *)des_addr,result_size);
    printf("ret value %d\n",ret);
    close(fd);
    if(ret == 0){
         printf("This test case is Pass\n");
         return ret;
    }
#else
    read(fd,(char*)EVB_RESULT_ADDR,result_size);
    ret =  memcmp((char *)VERIFY_EVB_ADDR,(char *)EVB_RESULT_ADDR,result_size);
    close(fd);
#endif
    // print_buf((char *)EVB_RESULT_ADDR,result_size);
   
    printf("addr %lx  %lx\n",VERIFY_EVB_ADDR,des_addr);
    for(int i =0 ; i< result_size; i++){
        if(((char*)VERIFY_EVB_ADDR)[i]!=((char *)des_addr)[i]){
            if(((char *)des_addr)[i] == 0){
                continue;
            }
            printf("offset %d\n",i);
            printf("dst %x\n",((char*)des_addr)[i]);
            printf("src %x\n",((char*)VERIFY_EVB_ADDR)[i]);
            printf("This test case is Failed\n");
            return -1;
        }
    }  
    ret =0;
   
    if(ret == 0){
        printf("This test case is Pass\n");
    }else{
        printf("This test case is Failed\n");
    }
    return ret;
}
int npu_load_a_file(const char *filename){

    int fd = open(filename,O_RDONLY);
#if EVB_DEBUG_LOG
    printf("load file %s\n",filename);
#endif
    if (fd < 0) {
        printf("fd value %d\n",fd);
        printf("Fail to open %s\n", filename);
        return fd;
    }
    int len = flen(fd);
    int total_size = len -8;
    // unsigned long  p ,des_addr= 0;
    uint64_t des_addr = 0;
#if 0
    read(fd,&des_addr,4);
    // uint64_t last_4_byte = RTL_DUMP_ADDR;
    
    seek(fd,8,0);
    // if(des_addr < 0xff000000){
        printf("add offset\n");
        des_addr += RTL_DUMP_ADDR;
    // }
       
    printf("addr %x\n",des_addr);
    // memset((char*)des_addr,0xa,128);
    read(fd,(char *)des_addr,total_size);
    printf("addr %x  %x\n",((int *)des_addr)[0],((int *)des_addr)[1]);
    close(fd);
    itcs_dcache_flush();
    // udelay(500);
#else
#if CONFIG_TB_RUN_DDR1
    unsigned long fp = faddr(fd);
    memcpy(&des_addr, (void*)fp, 4);
    des_addr = des_addr + RTL_DUMP_ADDR;
#else
    unsigned long fp = faddr(fd);
    memcpy(&des_addr, (void*)fp, 4);
    
    int64_t flag = 0;
    memcpy(&flag,(char*)fp+4,4);
    // printf("size %d\n",flag);
    if(flag == 0x5){
        printf("555\n");
        des_addr = des_addr + 0x500000000;
    }else{
        des_addr = des_addr + 0x100000000;
    }
    
#endif
#if EVB_DEBUG_LOG
    printf("size %d\n",total_size);
    printf("rtlfs addr %lx  load addr %lx \n",fp,des_addr);
#endif
   
    
    memset((char*)des_addr,0,total_size);
    memcpy((char*)des_addr, (char*)(fp) + 8,total_size);
    
    close(fd);
#if EVB_DEBUG_LOG
    printf("addr %x  %x\n",((int *)des_addr)[0],((int *)des_addr)[1]);
#endif
    
#endif
   return 0;

}

// int load_tlb_file(char *filename){
//     int fd = open(filename,O_RDONLY);
//      printf("load file %s\n",filename);
//     if (fd < 0) {
//         printf("Fail to open %s\n", filename);
//         return fd;
//     }
// }

int npu_input_file_batch(const char *filename,int start,int end){


    char temp[128]={0};
    char tail[8] = ".bin\0";

    for(int i = start ; i <= end; i++){
        sprintf(temp, "%s%d%s", filename,i,tail);
       
        if(npu_load_a_file(temp)<0){
            printf(" load %s failed",temp);
            return -1;
        }
    }
    return 0;
}

int npu_input_subfile_batch(const char *filename,int start,int end,int subID){


    char temp[128]={0};
    char tail[8] = ".bin\0";

    for(int i = start ; i <= end; i++){
        sprintf(temp, "%s%d_%d%s", filename,subID,i,tail);
        // printf("load file %s\n",temp);
        if(npu_load_a_file(temp)<0){
            printf(" load %s failed",temp);
            return -1;
        }
    }
    return 0;
}

void test_ddr_bw_all(){

    int value = 0;

    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);

    // printf("0x14 %d\n",MA_INW((base0 + 0x000014)));
    MA_OUTW((base0 + 0x00010C), 0x200000);
    MA_OUTW((base0 + 0x000100), 0x140021);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x10003000);
    MA_OUTW((base0 + 0x0003A4), 0x01ffff);
    rd_val = 0x1;
   
    while(rd_val != 0x0){
        
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        // printf("0x04 0x%x\n",MA_INW((base0+0x4)));
        // printf("0x04 0x%x\n",rd_val);
    }

    printf("npu test finish!\n");
    soc_dump0(RTL_DUMP_ADDR + 0x02000000, 0x005dc008); 
    // return 0;
}

void test_alexnet(){

    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x0003C1);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x20000000);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);
#endif
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x000654), 0x20000000);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20006EF8);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20006EF8);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20006F20);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20006F20);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20009498);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20009498);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }

    printf("npu test finish!\n"); 
    soc_dump0(RTL_DUMP_ADDR + 0x01e49100, 0x0004c268); 
    

    
    // return 0;
}

void test_alexnet_3(){
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x0003C1);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x20000000);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);
#endif
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x000654), 0x20000000);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20006EF8);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20006EF8);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20006F20);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20006F20);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20009498);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20009498);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    soc_dump0(RTL_DUMP_ADDR + 0x01e2b100, 0x0000fd88);
}
void test_lenet_1core(){
    // npu_test_code start
    
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base1 + 0x000090), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x070100);
    MA_OUTW((base0 + 0x0003A8), 0x000002);
    MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x00003C), 0x000000);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000414), 0x000000);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x070100);
    MA_OUTW((base1 + 0x0003A8), 0x000002);
    MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x00003C), 0x000000);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000414), 0x000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);
#endif
   
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x11000000);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x11007030);
    MA_OUTW((base0 + 0x0003A4), 0x010212);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = MA_INW((base0 + 0x000078));
    printf("0x000078 = %d \n" , rd_val);
    printf("npu test finish!\n"); 
    soc_dump0(RTL_DUMP_ADDR + 0x02050000, 0x00049800);
    
    // npu_test_code finish
    
    
}

void reg_common_cfg(){
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000014), 0x00FFFF);
    MA_OUTW((base0 + 0x000090), 0x000040);
    MA_OUTW((base0 + 0x000100), 0x140020);
    MA_OUTW((base0 + 0x000178), 0x002B94);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000014), 0x00FFFF);
    MA_OUTW((base1 + 0x000090), 0x000040);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000178), 0x00529A);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x10000000);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
    udelay(500);
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
//     rd_val = 0x1;
//    while(rd_val != 0x0){
//    rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
//     }

    printf("npu test finish!\n");
}

int nn_multi_core_MC2_sp_sum(){
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000014), 0x00FFFF);
    MA_OUTW((base0 + 0x000090), 0x000040);
    MA_OUTW((base0 + 0x000100), 0x140020);
    MA_OUTW((base0 + 0x000178), 0x002B94);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000014), 0x00FFFF);
    MA_OUTW((base1 + 0x000090), 0x000040);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000178), 0x00529A);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x10000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x000654), 0x10000000);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    udelay(500);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }

    printf("npu test finish!\n"); 

    return 0;
}

int ddr_compare(char *src,int size,int value){

    
    for(int i = 0; i<size;i++){
        if(src[i]!=value){
            return -1;
        }
    }
    return 0;
}
void sp_AluFunction_0(){
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000014), 0x00FFFF);
    MA_OUTW((base0 + 0x000090), 0x000040);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000178), 0x00BBE4);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000014), 0x00FFFF);
    MA_OUTW((base1 + 0x000090), 0x000040);
    MA_OUTW((base1 + 0x000100), 0x140020);
    MA_OUTW((base1 + 0x000178), 0x002BC5);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x10000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x000654), 0x10000000);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    udelay(500);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    printf("npu test finish!\n"); 
}

void sp_AluFunction_1(int flag){
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000014), 0x00FFFF);
    MA_OUTW((base0 + 0x000090), 0x000040);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000178), 0x00FA2D);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000014), 0x00FFFF);
    MA_OUTW((base1 + 0x000090), 0x000040);
    MA_OUTW((base1 + 0x000100), 0x140020);
    MA_OUTW((base1 + 0x000178), 0x00C1AA);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x10000000);
    if(flag == 1){
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    }else{
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    }
    udelay(500);
     rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    printf("npu test finish!\n"); 
}

void sp_AluFunction_test2(int flag){
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000014), 0x00FFFF);
    MA_OUTW((base0 + 0x000090), 0x000040);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000178), 0x00359D);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000014), 0x00FFFF);
    MA_OUTW((base1 + 0x000090), 0x000040);
    MA_OUTW((base1 + 0x000100), 0x140020);
    MA_OUTW((base1 + 0x000178), 0x007433);
    if(flag == 0){
         MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10000000);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    }else if(flag == 1){
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000388), 0x000021);

        MA_OUTW((base0 + 0x000654), 0x10000000);
        MA_OUTW((base1 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    }else{
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    }
    udelay(500);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    udelay(1000000);
}

void mobilenet_test(){
    MA_OUTW(base0 +0x078,0);
    MA_OUTW(base1+0x078,0);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base1 + 0x000090), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x070100);
    MA_OUTW((base0 + 0x0003A8), 0x000002);
    MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x00003C), 0x000000);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000414), 0x000000);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x070100);
    MA_OUTW((base1 + 0x0003A8), 0x000002);
    MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x00003C), 0x000000);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000414), 0x000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x0003B4), 0x040020);
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x0003B4), 0x040020);
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x4003500);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    MA_OUTW((base1 + 0x000654), 0x4003500);
    MA_OUTW((base1 + 0x0003A4), 0x010015);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x408B970);
    MA_OUTW((base0 + 0x0003A4), 0x01002B);
    MA_OUTW((base1 + 0x000654), 0x408B970);
    MA_OUTW((base1 + 0x0003A4), 0x01002B);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = MA_INW((base1 + 0x000078));
    int rd_val_0 = MA_INW((base1 + 0x000078));
    unsigned int core_clk = 1008000000;
    printf("npu1 0x000078 = %d \n" , rd_val);
    printf("npu1 fps %d\n",core_clk/rd_val);

    printf("npu0 0x000078 = %d \n" , rd_val_0);
    printf("npu0 fps %d\n",core_clk/rd_val_0);
    printf("npu test finish!\n"); 
    soc_dump0(0x100000000 + 0x10029900, 0x00062008);
}

void test_conv_int16(){
     printf("npu nn_convolution_int16 test start!\n"); 
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000014), 0x00FFFF);
        MA_OUTW((base0 + 0x000090), 0x000040);
        MA_OUTW((base0 + 0x000100), 0x140020);
        MA_OUTW((base0 + 0x000178), 0x002B94);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000014), 0x00FFFF);
        MA_OUTW((base1 + 0x000090), 0x000040);
        MA_OUTW((base1 + 0x000100), 0x140021);
        MA_OUTW((base1 + 0x000178), 0x00529A);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
 #ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        udelay(500);
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000088);
}
int npu_only_rtl(char *cmd_s){
    int status = -1;
    set_npu_clock();
    

    if(strncmp(cmd_s, "-alexnet_int8_1", strlen(cmd_s)) == 0){
        printf("npu alexnet_int8_001_power_DV test start!\n");
        test_alexnet();
       
        soc_dump0(RTL_DUMP_ADDR + 0x01e49100, 0x0004c268);

    }else if(strncmp(cmd_s, "-alexnet_int8_3",  strlen(cmd_s)) == 0){
        printf("npu alexnet_int8_003_power_DV test start!\n"); 
        test_alexnet();
        
        soc_dump0(RTL_DUMP_ADDR + 0x01e2b100, 0x0000fd88);
    }else if (strncmp(cmd_s, "-bw_test_read",  strlen(cmd_s)) == 0)
    {
        printf("npu ddr_bw_test_write_only test start!\n"); 
        test_ddr_bw_all();

    }else if(strncmp(cmd_s, "-bw_test_write_read",  strlen(cmd_s)) == 0){

        printf("npu ddr_bw_test_write_only test start!\n"); 
        test_ddr_bw_all(); 

    }else if (strncmp(cmd_s, "-bw_test_write",  strlen(cmd_s)) == 0)
    {
        printf("npu ddr_bw_test_write_only test start!\n"); 
        test_ddr_bw_all();
        

    }else if(strncmp(cmd_s, "-image_blend",  strlen(cmd_s)) == 0){
        printf("npu image_blend test start!\n"); 
        MA_OUTW((base0 + 0x000014), 0xFFFFFFF);
        MA_OUTW((base0 + 0x00010C), 0x020000);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x8000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x40000000, 0x0000c008);

    }else if (strncmp(cmd_s, "-image_filter",  strlen(cmd_s)) == 0)
    {
         printf("npu image_filter test start!\n"); 
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x08000000, 0x000c0008);
    }else if(strncmp(cmd_s, "-lenet_1core",  strlen(cmd_s)) == 0){
        printf("npu lenet_1core_DV test start!\n"); 
        test_lenet_1core();
    }else if (strncmp(cmd_s, "-mmu_extend4gAddr",  strlen(cmd_s)) == 0)
    {     
         printf("npu mmu_extend4gAddr test start!\n"); 
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
     
    MA_OUTW((base0 + 0x000090), 0x000040);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x010030);
        rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x40200000, 0x00001008);
        
    }else if(strncmp(cmd_s, "-nn_40bitVA_k1",  strlen(cmd_s)) == 0){

        printf("npu nn_40bitVA_kernel_1x1 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);

    }else if (strncmp(cmd_s, "-nn_40bitVA_k3",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_40bitVA_kernel_3x3 test start!\n"); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        
    }else if(strncmp(cmd_s, "-nn_convolution_fp16",  strlen(cmd_s)) == 0){
        printf("npu nn_convolution_int16 test start!\n"); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000088);
    }else if (strncmp(cmd_s, "-nn_convolution_int16",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_convolution_int16 test start!\n");
        test_conv_int16();
        
    }else if(strncmp(cmd_s, "-nn_convolution_int8",  strlen(cmd_s)) == 0){
        printf("npu nn_convolution_int8 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);

    }else if (strncmp(cmd_s, "-nn_ddr_read",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_ddr_read test start!\n"); 
        reg_common_cfg();
        nn_read_and_ot_dump();
    }else if(strncmp(cmd_s, "-nn_ddr_write",  strlen(cmd_s)) == 0){
        printf("npu nn_ddr_write test start!\n");
        reg_common_cfg();
        nn_write_dump();
    }else if (strncmp(cmd_s, "-nn_kernel_3",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_kernel_3x3 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
    }else if(strncmp(cmd_s, "-nn_max_ot",  strlen(cmd_s)) == 0){
        printf("npu nn_max_OT test start!\n");
        reg_common_cfg();
        nn_read_and_ot_dump();

    }else if (strncmp(cmd_s, "-nn_MC2_AluFunction_0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_AluFunction_0 test start!\n"); 
        nn_multi_core_MC2_sp_sum();
        udelay(3000000);
        AluFunction_0_test_dump();
    }else if(strncmp(cmd_s, "-nn_MC2_kernel3x3_pool",  strlen(cmd_s)) == 0){

        printf("npu nn_MC2_kernel3x3_pooling0 test start!\n");
        nn_multi_core_MC2_sp_sum();
        udelay(3000000);
        kernel3x3_pooling0();

    }else if (strncmp(cmd_s, "-nn_MC2_PerChQuantization",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_MC2_PerChQuantization test start!\n"); 
        nn_multi_core_MC2_sp_sum();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00004048);
        
    }else if(strncmp(cmd_s, "-nn_MC2_sp_AluFunction_0",  strlen(cmd_s)) == 0){

        printf("npu nn_MC2_sp_AluFunction_test0 test start!\n");
        sp_AluFunction_0();
        sp_AluFunction_0_dump();

    }else if (strncmp(cmd_s, "-nn_MC2_sp_AluFunction_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_AluFunction_test1 test start!\n");
        sp_AluFunction_1(1);
        sp_AluFunction_test1_dump();

    }else if(strncmp(cmd_s, "-nn_MC2_sp_AluFunction_2",  strlen(cmd_s)) == 0){
         printf("npu nn_MC2_sp_AluFunction_test2 test start!\n");
         sp_AluFunction_test2(0);
         udelay(3000000);
         sp_AluFunction_2_dump();

    }else if (strncmp(cmd_s, "-nn_MC2_sp_sum_engine_control1_ch2_fromV11V12",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_sum_engine_control1_ch2_fromV11V12 test start!\n"); 
        nn_multi_core_MC2_sp_sum();
        control1_ch2_fromV11V12();

    }else if (strncmp(cmd_s, "-nn_MC2_sp_sum_engine_control2_ch2_storageSame",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_sum_engine_control2_ch2_storageSame test start!\n"); 
        nn_multi_core_MC2_sp_sum();
        storageSame_dump();

    }else if(strncmp(cmd_s, "-nn_multi_core_AluFunction_0",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_AluFunction_0 test start!\n");
        reg_common_cfg();
        AluFunction_0_test_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_AluFunction_1",  strlen(cmd_s)) == 0)
    {
         printf("npu nn_multi_core_AluFunction_1 test start!\n");
        reg_common_cfg();
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820008b0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82001160, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82001a10, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820022c0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82002b70, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82003420, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82003cd0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82004580, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82004e30, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820056e0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82005f90, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82006840, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820070f0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820079a0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82008250, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82008b00, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820093b0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82009c60, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a510, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200adc0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b670, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200bf20, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200c7d0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d080, 0x00000044);
        
    }else if(strncmp(cmd_s, "-nn_multi_core_AluFunction_2",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_AluFunction_2 test start!\n");
        reg_common_cfg();
        AluFunction_0_test_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_AluFunction_3",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_AluFunction_3 test start!\n");
        reg_common_cfg();
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200033c, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82000678, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820009b4, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82000cf0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200102c, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001368, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820016a4, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820019e0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001d1c, 0x000000e8);
        
    }else if(strncmp(cmd_s, "-nn_multi_core_AluFunction_4",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_AluFunction_4 test start!\n");
        reg_common_cfg();
        printf("npu test finish!\n");
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820003e0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820007c0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000ba0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f80, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001360, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001740, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001b20, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001f00, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820022e0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820026c0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82002aa0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82002e80, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003260, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003640, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003a20, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003e00, 0x00000048);

    }else if (strncmp(cmd_s, "-nn_multi_core_convolutionStride_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_convolutionStride_1 test start!\n");
        reg_common_cfg();
        convStride_1_dump();
        
    }else if(strncmp(cmd_s, "-nn_multi_core_depthWise_1",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_depthWise_1 test start!\n");
        reg_common_cfg();
        
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000230, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f50, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001180, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001ea0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x820020d0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002df0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003020, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003d40, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003f70, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004c90, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004ec0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005be0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005e10, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006b30, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006d60, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007a80, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007cb0, 0x000000f0);

    }else if (strncmp(cmd_s, "-nn_multi_core_in2ndChNum_16",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_in2ndChNum_16 test start!\n");
        reg_common_cfg();
        in2ndChnum_16_dump();

    }else if(strncmp(cmd_s, "-nn_multi_core_inChNum_16",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_inChNum_16 test start!\n");
        reg_common_cfg();
        inChnum_16_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_inImageDataType_0",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_inImageDataType_0 test start!\n");
        reg_common_cfg();
        image_Type_0_2_dump();
    }else if (strncmp(cmd_s, "-nn_multi_core_inImageDataType_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_inImageDataType_1 test start!\n");
        reg_common_cfg();
        kernel_image_Date1_dump();
        
    }else if(strncmp(cmd_s, "-nn_multi_core_inImageDataType_2",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_inImageDataType_2 test start!\n");
        reg_common_cfg();
        image_Type_0_2_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_inImageDataType_4",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_inImageDataType_4 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000248, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000490, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x820006d8, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000920, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000b68, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000db0, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000ff8, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001240, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001488, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x820016d0, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001918, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001b60, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001da8, 0x00000088);

    }else if(strncmp(cmd_s, "-nn_multi_core_inImageDataType_7",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_inImageDataType_7 test start!\n");
        reg_common_cfg();
        inimage_Data_7_8_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_inImageDataType_8",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_inImageDataType_8 test start!\n");
        reg_common_cfg();
        inimage_Data_7_8_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_kernel1_pooling0",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_kernel1x1_pooling0 test start!\n");
        reg_common_cfg(); 
        kernel1_pooling_0_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_kernel3_pooling0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_kernel3x3_pooling0 test start!\n");
        reg_common_cfg();
        kernel3x3_pooling0();
        
    }else if(strncmp(cmd_s, "-nn_multi_core_kernelDataType_0",  strlen(cmd_s)) == 0){

         printf("npu nn_multi_core_kernelDataType_0 test start!\n");
         reg_common_cfg();
         kernelData_0_2_dump();
    }else if (strncmp(cmd_s, "-nn_multi_core_kernelDataType_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_kernelDataType_1 test start!\n"); 
        reg_common_cfg();
        kernel_image_Date1_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_kernelDataType_2",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_kernelDataType_2 test start!\n");
        reg_common_cfg();
        kernelData_0_2_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_kernelDataType_4",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_kernelDataType_4 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82001f08, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82003e10, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82005d18, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82007c20, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82009b28, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ba30, 0x00000128);
    }else if (strncmp(cmd_s, "-nn_multi_core_kernelDataType_7",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_kernelDataType_7 test start!\n");
        reg_common_cfg();
        kernelData_7_dump();
        
    }else if(strncmp(cmd_s, "-nn_multi_core_nnCoefDecompBypass_0",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_nnCoefDecompBypass_0 test start!\n"); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001730, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82002e60, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82004590, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82005cc0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820073f0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82008b20, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a250, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b980, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d0b0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e7e0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ff10, 0x000000e8);
    }else if (strncmp(cmd_s, "-nn_multi_core_nnCoefDecompBypass_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_nnCoefDecompBypass_1 test start!\n"); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82001368, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x820026d4, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82003a3c, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82004da8, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82006110, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200747c, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x820087e4, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82009b50, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200aeb8, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200c224, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d58c, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e8f8, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200fc60, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82010fcc, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82012334, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x820136a0, 0x00000140);

    }else if(strncmp(cmd_s, "-nn_multi_core_nnConvOnedMode_1",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_nnConvOnedMode_1 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820000ac, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a40, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000af0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82001480, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001530, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001ec0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001f70, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82002904, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820029b0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003344, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820033f4, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82003d84, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003e34, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820047c4, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82004874, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82005208, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820052b4, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82005c48, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82005cf8, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82006688, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82006738, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820070c8, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82007178, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82007b0c, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82007bb8, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x8200854c, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820085fc, 0x00000044);
    }else if (strncmp(cmd_s, "-nn_multi_core_NN_xdp3_kx3_outTilex64",  strlen(cmd_s)) == 0)
    {
        
        printf("npu nn_multi_core_NN_fast_xdp3_kx3_outTilex64 test start!\n");
        
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000c4);
        soc_dump0(RTL_DUMP_ADDR + 0x82000604, 0x000000c8);
        soc_dump0(RTL_DUMP_ADDR + 0x82000c0c, 0x000000c4);
        soc_dump0(RTL_DUMP_ADDR + 0x82001210, 0x000000c8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001818, 0x000000c4);
        soc_dump0(RTL_DUMP_ADDR + 0x82001e1c, 0x000000c8);
    }else if(strncmp(cmd_s, "-nn_multi_core_outChNum_16",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outChNum_16 test start!\n");
        reg_common_cfg();
        outChNum_16_dump();
    }else if (strncmp(cmd_s, "-nn_multi_core_outImageDataType_0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_outImageDataType_0 test start!\n");
        reg_common_cfg();
        OutimageData_0_2_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_outImageDataType_1",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outImageDataType_1 test start!\n");
        reg_common_cfg();
        OutimageData_1_7_dump();
    }else if (strncmp(cmd_s, "-nn_multi_core_outImageDataType_2",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_multi_core_outImageDataType_2 test start!\n");
        reg_common_cfg();
        OutimageData_0_2_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_outImageDataType_4",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outImageDataType_4 test start!\n");
        reg_common_cfg();
        OutimageData_4_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_outImageDataType_7",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_outImageDataType_7 test start!\n");
        reg_common_cfg();
        OutimageData_1_7_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_outImageDataType_8",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outImageDataType_8 test start!\n");
        reg_common_cfg();
        OutimageData_8_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_pooling_1",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_multi_core_pooling_1 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82000d10, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82001a20, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82002730, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82003440, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82004150, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82004e60, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82005b70, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82006880, 0x000000bc);
        
    }else if(strncmp(cmd_s, "-nn_multi_core_pooling_3",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_pooling_3 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000078);
        soc_dump0(RTL_DUMP_ADDR + 0x820000e8, 0x00000078);
        soc_dump0(RTL_DUMP_ADDR + 0x82000bc8, 0x00000078);
        soc_dump0(RTL_DUMP_ADDR + 0x82000cb0, 0x00000078);

    }else if (strncmp(cmd_s, "-nn_multi_core_PoolSize2x2_PoolStride1_iv4_img1st1_indata0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_PoolSize2x2_PoolStride1_iv4_img1st1_indata0 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x820019c0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82003380, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82004d40, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82006700, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x820080c0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82009a80, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b440, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ce00, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e7c0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82010180, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82011b40, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82013500, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82014ec0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82016880, 0x000000dc);
        
    }else if(strncmp(cmd_s, "-nn_multi_core_PoolSize2x2_PoolStride2_iv4_img1st1_indata0",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_PoolSize2x2_PoolStride2_iv4_img1st1_indata0 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000048, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000090, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820000d8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000120, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000168, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820001b0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820001f8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000240, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000288, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820002d0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000318, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000500, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000548, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000590, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820005d8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000620, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000668, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820006b0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820006f8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000740, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000788, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820007d0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000818, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a00, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a48, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a90, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000ad8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000b20, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000b68, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000bb0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000bf8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000c40, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000c88, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000cd0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000d18, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f00, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f48, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f90, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000fd8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001020, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001068, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820010b0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820010f8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001140, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001188, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820011d0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001218, 0x0000001c);
    }else if (strncmp(cmd_s, "-nn_multi_core_PoolSize3x3_PoolStride1_iv4_img1st1_indata0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_PoolSize3x3_PoolStride1_iv4_img1st1_indata0 test start!\n");
        reg_common_cfg(); 
         soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200022c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000458, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000684, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000d08, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f34, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001160, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200138c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001a10, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001c3c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001e68, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002094, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002718, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002944, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002b70, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002d9c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003420, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200364c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003878, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003aa4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004128, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004354, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004580, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820047ac, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004e30, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200505c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005288, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820054b4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005b38, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005d64, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005f90, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820061bc, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006840, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006a6c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006c98, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006ec4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007548, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007774, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820079a0, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007bcc, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82008250, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200847c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820086a8, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820088d4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82008f58, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82009184, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820093b0, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820095dc, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82009c60, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82009e8c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a0b8, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a2e4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a968, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ab94, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200adc0, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200afec, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b670, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b89c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200bac8, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200bcf4, 0x000000d0);
        
    }else if(strncmp(cmd_s, "-nn_multi_core_PoolSize3x3_PoolStride2_iv4_img1st1_indata0",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_PoolSize3x3_PoolStride2_iv4_img1st1_indata0 test start!\n");
        reg_common_cfg();
         soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82001ee0, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82003dc0, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82005ca0, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82007b80, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82009a60, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b940, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d820, 0x000002ac);
    }else if (strncmp(cmd_s, "-nn_multi_core_sp_AluFunction_test0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_sp_AluFunction_test0 test start!\n");
        sp_AluFunction_0();
        sp_AluFunction_0_dump();
    }else if(strncmp(cmd_s, "-nn_multi_core_sp_AluFunction_test1",  strlen(cmd_s)) == 0){
        printf("npu nn_MC2_sp_AluFunction_test1 test start!\n");
        sp_AluFunction_1(1);
        sp_AluFunction_test1_dump();

    }else if (strncmp(cmd_s, "-nn_multi_core_sp_AluFunction_test2",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_sp_AluFunction_test2 test start!\n");
        sp_AluFunction_test2(1);
        sp_AluFunction_2_dump();
        
    }else if(strncmp(cmd_s, "-nn_multi_core_sp_sum_engine_control1_ch2_fromV11V12",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_sp_sum_engine_control1_ch2_fromV11V12 test start!\n"); 
        nn_multi_core_MC2_sp_sum();
        control1_ch2_fromV11V12();

    }else if (strncmp(cmd_s, "-nn_multi_core_sp_sum_engine_control2_ch2_storageSame",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_sum_engine_control2_ch2_storageSame test start!\n"); 
        nn_multi_core_MC2_sp_sum();
        storageSame_dump();

    }else if(strncmp(cmd_s, "-nn_multi_core_v8_conv_int_bring_up_3",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_v8_conv_int_bring_up_3 test start!\n"); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
    }else if (strncmp(cmd_s, "-nn_multi_core_vipsram_mode_1010",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_vipsram_mode_1010 test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001730, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82002e60, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82004590, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82005cc0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820073f0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82008b20, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a250, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b980, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d0b0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e7e0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ff10, 0x000000e8);
        
    }else if (strncmp(cmd_s, "-nn_PerChQuantization",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_PerChQuantization test start!\n");
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00004048);
        
    }else if(strncmp(cmd_s, "-nn_sp_AluFunction_test0",  strlen(cmd_s)) == 0){
        
        printf("npu nn_sp_AluFunction_test0 test start!\n");
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000014), 0x00FFFF);
        MA_OUTW((base0 + 0x000090), 0x000040);
        MA_OUTW((base0 + 0x000100), 0x140021);
        MA_OUTW((base0 + 0x000178), 0x00BBE4);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000014), 0x00FFFF);
        MA_OUTW((base1 + 0x000090), 0x000040);
        MA_OUTW((base1 + 0x000100), 0x140020);
        MA_OUTW((base1 + 0x000178), 0x002BC5);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
        sp_AluFunction_0_dump();

    }else if (strncmp(cmd_s, "-nn_sp_AluFunction_test1",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_sp_AluFunction_test1 test start!\n");
        sp_AluFunction_1(0);
        sp_AluFunction_test1_dump();
        
    }else if(strncmp(cmd_s, "-nn_sp_AluFunction_test2",  strlen(cmd_s)) == 0){
        printf("npu nn_sp_AluFunction_test2 test start!\n");
        sp_AluFunction_test2(3);
        sp_AluFunction_2_dump();

    }else if (strncmp(cmd_s, "-nn_sp_sum_engine_control1_ch2_fromV11V12",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_sp_sum_engine_control1_ch2_fromV11V12 test start!\n"); 
        reg_common_cfg();
        control1_ch2_fromV11V12();

    }else if(strncmp(cmd_s, "-nn_sp_sum_engine_control2_ch2_storagesame",  strlen(cmd_s)) == 0){

        printf("npu nn_sp_sum_engine_control2_ch2_storageSame test start!\n");
        reg_common_cfg();
        storageSame_dump();
    }else if (strncmp(cmd_s, "-nn_tensorAdd",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_tensorAdd test start!\n");
        reg_common_cfg();
         soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
    }else if(strncmp(cmd_s, "-nn_transpose",  strlen(cmd_s)) == 0){
        printf("npu nn_transpose test start!\n"); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000408);
    }else if (strncmp(cmd_s, "-shader_copy_cram2",  strlen(cmd_s)) == 0)
    {
         printf("npu shader_copy_cram2 test start!\n"); 
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
        MA_OUTW((base0 + 0x0003B4), 0x1FF0001);
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x10200000, 0x00001008);
    }else if(strncmp(cmd_s, "-shader_copy",  strlen(cmd_s)) == 0){
        printf("npu shader_copy test start!\n"); 
        MA_OUTW((base0 + 0x00010C), 0x020000);
        MA_OUTW((base1 + 0x00010C), 0x020000);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x010030);
        MA_OUTW((base1 + 0x0003A4), 0x010030);
        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x20200000, 0x00001008);


    }else if (strncmp(cmd_s, "-sys_semaphore",  strlen(cmd_s)) == 0)
    {
        printf("npu sys_semaphore test start!\n"); 
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
        MA_OUTW((base0 + 0x0003B4), 0x1FF0001);
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
        MA_OUTW((base1 + 0x0003B4), 0x1FF0001);
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x10001000);
        MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x40200000, 0x00001008);
        soc_dump0(RTL_DUMP_ADDR + 0x41200000, 0x00001008);
        soc_dump0(RTL_DUMP_ADDR + 0x42200000, 0x00001008);
        
    }else if(strncmp(cmd_s, "-localStorageAccess",  strlen(cmd_s)) == 0){
        int rate = itcs_module_get_clock(CPU, "vip0");
        printf("vip rate is %d\n", rate);
        
#ifdef CONFIG_TB_RUN_DDR1
        MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
        MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 +0x000388),0x000021);
        MA_OUTW((base0 +0x000654),0x103D0000);
        MA_OUTW((base0 +0x0003A4),0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        MA_OUTW((base0 +0x000654),0x103E0000);
        MA_OUTW((base0 +0x0003A4),0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        MA_OUTW((base0 +0x000654),0x103F0000);
        MA_OUTW((base0 +0x0003A4),0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        printf("npu test finish\n");
        soc_dump0(RTL_DUMP_ADDR +0x01e20100, 0x000008);
    }else if(strncmp(cmd_s, "-resnet_v1_50_block1_v2_int8_DV",  strlen(cmd_s)) == 0){
        printf("npu resnet_v1_50_block1_v2_int8_DV test start\n");
        MA_OUTW((base0 +0x000014),0xFFFFFFFF);
        MA_OUTW((base0 +0x000090),0x0003c1);
        #ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 +0x000388),0x000021);
        MA_OUTW((base0 +0x000654),0x20000000);
        MA_OUTW((base0 +0x0003A4),0x01FFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 +0x000388),0x01FFFF);

        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
        MA_OUTW((base0 +0x000654),0x20004A38);
        MA_OUTW((base0 +0x0003A4),0x01FFFF);
        MA_OUTW((base1 +0x000654),0x20004A38);
        MA_OUTW((base1 +0x0003A4),0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
        MA_OUTW((base0 +0x000654),0x200072A0);
        MA_OUTW((base0 +0x0003A4),0x01FFFF);
        MA_OUTW((base1 +0x000654),0x200072A0);
        MA_OUTW((base1 +0x0003A4),0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
        printf("npu test finish\n");
        soc_dump0(RTL_DUMP_ADDR +0x01e20100, 0x000c4008);
    }else if(strncmp(cmd_s, "-mask_image",  strlen(cmd_s)) == 0){
        printf("npu mask image test start\n");
        MA_OUTW((base0 +0x000010c),0x020000);
        
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 +0x0000388),0x021);
        MA_OUTW((base0 +0x000654),0x30001000);
        MA_OUTW((base0 +0x0003A4),0x01011c);
        rd_val = 0x1;
        if(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        printf("npu test finish\n");
        soc_dump0(RTL_DUMP_ADDR +0x20000000, 0x0012c008);
    }else{
        printf("command id not match\n");
    }
    

    return status;
}


int npu_only_evb(char * cmd_s){
    int status = -1;
    // set_npu_clock();
    
    char concat[128] = {0};
    sprintf(concat,"%s%s",cmd_s,"_data/mem");
    char tlb_buf_load[128]={0};
    sprintf(tlb_buf_load,"%s%s",cmd_s,"_data/mem3_tlb_buf.bin");
    memset(result_file_name,0,128);
    sprintf(result_file_name,"%s%s",cmd_s,"_data/result.bin");
    total_size = 0;
#ifdef CONFIG_TB_RUN_DDR1
    memcpy((void *)(0xff000000+RTL_DUMP_ADDR),mem3_tlb_buf_bin_ddr1,2048);
#else
    memcpy((void *)(0xff000000+RTL_DUMP_ADDR),mem3_tlb_buf_bin,2048);
#endif
    printf("tl buffer %x \n",((int*)(0xff000000+RTL_DUMP_ADDR))[0]);
    printf("tl buffer %x \n",((int*)(0xff000000+RTL_DUMP_ADDR))[511]);
    if(strncmp(cmd_s, "alexnet_int8_001_power_DV", strlen(cmd_s)) == 0){
        printf("npu alexnet_int8_001_power_DV test start!\n");
        npu_input_file_batch("alexnet_int8_001_power_DV/mem",0,70);
        // itcs_dcache_flush();
        test_alexnet();
        udelay(3000000);
        // itcs_dcache_invalid();
        soc_dump0(RTL_DUMP_ADDR + 0x01e49100, 0x0004c268);
        
        // printf("result %x\n",((int *)(RTL_DUMP_ADDR + 0x01e49100))[0]);
        status = npu_compare("alexnet_int8_001_power_DV/result.bin");
        // return status;
    }else if(strncmp(cmd_s, "alexnet_int8_003_power_DV",  strlen(cmd_s)) == 0){
        printf("npu alexnet_int8_003_power_DV test start!\n"); 
        npu_input_file_batch("alexnet_int8_003_power_DV/mem",0,70);
        test_alexnet_3();
        udelay(3000000);
        // soc_dump0(RTL_DUMP_ADDR + 0x01e2b100, 0x0000fd80);
        status = npu_compare("alexnet_int8_003_power_DV/result.bin");
        // return status;
    }else if (strncmp(cmd_s, "ddr_bw_test_read_only",  strlen(cmd_s)) == 0)
    {
        printf("npu ddr_bw_test_write_only test start!\n"); 
        npu_load_a_file("ddr_bw_test_read_only/mem0_cmd_buffer.bin");
        npu_load_a_file("ddr_bw_test_read_only/mem1_shader_buffer.bin");
        npu_load_a_file("ddr_bw_test_read_only/mem2_initial_buffer.bin");
        // memset((char *)0x002000000+,0,6144000);
        npu_load_a_file("ddr_bw_test_read_only/mem3_input_buffer.bin");
        // memset((char *)0x101000000,0,6144000);
        // npu_load_a_file("tlb.bin");
        test_ddr_bw_all();
        // npu_compare("ddr_bw_test_write_only/result.bin");
        // status = npu_compare("ddr_bw_test_read_only/result.bin");
        status = ddr_compare((char*)(RTL_DUMP_ADDR + 0x02000000),6144000,0);
        if(status == 0){
            printf(" ddr Pass\n");
        }else{
            printf(" ddr Failed\n");
        }
        return status;
    }else if(strncmp(cmd_s, "ddr_bw_test_write_read",  strlen(cmd_s)) == 0){

        printf("npu ddr_bw_test_write_read test start!\n");
        npu_load_a_file("ddr_bw_test_read_write/mem0_cmd_buffer.bin");
        npu_load_a_file("ddr_bw_test_read_write/mem1_shader_buffer.bin");
        npu_load_a_file("ddr_bw_test_read_write/mem2_initial_buffer.bin");
        // memset((char *)0x102000000,0,6144000);
        npu_load_a_file("ddr_bw_test_read_write/mem3_input_buffer.bin");
        // memset((char *)0x101000000,0,6144000);
        // npu_load_a_file("ddr_bw_test_write_read/mem3_tlb_buf.bin"); 
        test_ddr_bw_all(); 
        // npu_compare("ddr_bw_test_write_read/mem0_result.bin");

        // status = npu_compare("ddr_bw_test_write_only/result.bin");
        status = ddr_compare((char*)(RTL_DUMP_ADDR + 0x02000000),6144000,0);
        if(status == 0){
            printf(" ddr Pass\n");
        }else{
            printf(" ddr Failed\n");
        }
        return status;
    }else if (strncmp(cmd_s, "ddr_bw_test_write_only",  strlen(cmd_s)) == 0)
    {
        printf("npu ddr_bw_test_write_only test start!\n"); 
        npu_load_a_file("ddr_bw_test_write_only/mem0_cmd_buffer.bin");
        npu_load_a_file("ddr_bw_test_write_only/mem1_shader_buffer.bin");
        npu_load_a_file("ddr_bw_test_write_only/mem2_initial_buffer.bin");
        // memset((char *)0x102000000,1,6144000);
        npu_load_a_file("ddr_bw_test_write_only/mem3_input_buffer.bin");
        // memset((char *)0x101000000,0,6144000);
        // npu_load_a_file("ddr_bw_test_write_only/mem3_tlb_buf.bin");
       
        test_ddr_bw_all();
         udelay(5000000);
        // status = npu_compare("ddr_bw_test_write_only/result.bin");
        status = ddr_compare((char*)(RTL_DUMP_ADDR + 0x02000000),6144000,0);
        if(status == 0){
            printf(" ddr Pass\n");
        }else{
            printf(" ddr Failed\n");
        }
        return status;

    }else if(strncmp(cmd_s, "image_blend",  strlen(cmd_s)) == 0){
        printf("npu image_blend test start!\n"); 
        npu_load_a_file("image_blend_data/mem0_cmd_buffer.bin");
        npu_load_a_file("image_blend_data/mem1_shader_buffer.bin");
        npu_load_a_file("image_blend_data/mem2_clear_buffer.bin");
        npu_load_a_file("image_blend_data/mem3_image_buffer0.bin");
        // npu_load_a_file("image_blend_data/mem3_tlb_buf.bin");
        npu_load_a_file("image_blend_data/mem4_image_buffer1.bin");
        MA_OUTW((base0 + 0x000014), 0xFFFFFFF);
        MA_OUTW((base0 + 0x00010C), 0x020000);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x8000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        printf("npu test finish!\n"); 
        // udelay(3000000);
        soc_dump0(RTL_DUMP_ADDR + 0x40000000, 0x0000c008);
        // npu_compare("image_blend_data/mem0_result.bin");
        status = npu_compare(result_file_name);
        // return status;

    }else if (strncmp(cmd_s, "image_filter",  strlen(cmd_s)) == 0)
    {
         printf("npu image_filter test start!\n"); 
        npu_load_a_file("image_filter_data/mem0_cmd_buf.bin");
        npu_load_a_file("image_filter_data/mem1_pshader_buf.bin");
        npu_load_a_file("image_filter_data/mem2_tex_buf.bin");
        npu_load_a_file("image_filter_data/mem3_clear_buf.bin");
        // npu_load_a_file("image_filter_data/mem3_tlb_buf.bin");
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }

        printf("npu test finish!\n"); 
        udelay(3000000);
        soc_dump0(RTL_DUMP_ADDR + 0x08000000, 0x000c0008);
        status = npu_compare(result_file_name);
        // return status;
        // npu_compare("image_filter_data/mem0_result.bin");
    }else if(strncmp(cmd_s, "lenet_1core_DV",  strlen(cmd_s)) == 0){
        printf("npu lenet_1core_DV test start!\n"); 
        npu_input_file_batch(concat,0,110);
        // itcs_dcache_flush();
        test_lenet_1core();
        udelay(3000000);
        // itcs_dcache_invalid();
        status = npu_compare_argv(result_file_name,(char*)(0x02050000+RTL_DUMP_ADDR));
        
        // npu_compare("lenet_1core_DV_data/mem0_result.bin");

    }else if (strncmp(cmd_s, "mmu_extend4gAddr",  strlen(cmd_s)) == 0)
    {     
         printf("npu mmu_extend4gAddr test start!\n"); 
        npu_load_a_file("mmu_extend4gAddr/mem0_cmd_buf.bin");
        npu_load_a_file("mmu_extend4gAddr/mem1_sh_buf.bin");
        npu_load_a_file("mmu_extend4gAddr/mem2_src_buf.bin");
        // npu_load_a_file("mmu_extend4gAddr/mem3_tlb_buf.bin");

        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
        
        // MA_OUTW((base0 + 0x000090), 0x000040);

#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x010030);
        rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
         udelay(3000000);
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x40200000, 0x00001008);
        
        status = npu_compare("mmu_extend4gAddr/result.bin");
        
        
    }else if(strncmp(cmd_s, "nn_40bitVA_kernel_1x1",  strlen(cmd_s)) == 0){

        printf("npu nn_40bitVA_kernel_1x1 test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_40bitVA_kernel_3x3",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_40bitVA_kernel_3x3 test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_convolution_fp16",  strlen(cmd_s)) == 0){
        printf("npu nn_convolution_fp16 test start!\n"); 
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        ////npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000088);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_convolution_int16",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_convolution_int16 test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        ////npu_load_a_file(tlb_buf_load);
        test_conv_int16();
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_convolution_int8",  strlen(cmd_s)) == 0){
        printf("npu nn_convolution_int8 test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        ////npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_ddr_read",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_ddr_read test start!\n"); 
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,5);
        ////npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        udelay(300000);
        status = nn_read_and_ot_dump();
    }else if(strncmp(cmd_s, "nn_ddr_write",  strlen(cmd_s)) == 0){
        printf("npu nn_ddr_write test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        // udelay(300000);
        status = nn_write_dump();
       
    }else if (strncmp(cmd_s, "nn_kernel_3x3",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_kernel_3x3 test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_max_OT",  strlen(cmd_s)) == 0){
        printf("npu nn_max_OT test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        udelay(300000);
        itcs_dcache_invalid();
        status = nn_read_and_ot_dump();

    }else if (strncmp(cmd_s, "nn_MC2_AluFunction_0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_AluFunction_0 test start!\n"); 
        npu_input_subfile_batch(concat,0,2,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        nn_multi_core_MC2_sp_sum();
        
        status = AluFunction_0_test_dump();
    }else if(strncmp(cmd_s, "nn_MC2_kernel3x3_pooling0",  strlen(cmd_s)) == 0){

        printf("npu nn_MC2_kernel3x3_pooling0 test start!\n");
        npu_input_subfile_batch(concat,0,59,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        memset((char*)0x180000000,0,0x2310);
        nn_multi_core_MC2_sp_sum();
        udelay(3000000);

        status = kernel3x3_pooling0();

    }else if (strncmp(cmd_s, "nn_MC2_PerChQuantization",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_MC2_PerChQuantization test start!\n");
        npu_input_file_batch(concat,0,0); 
        npu_input_file_batch(concat,2,5);
        // npu_load_a_file(tlb_buf_load);
        nn_multi_core_MC2_sp_sum();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00004048);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_MC2_sp_AluFunction_test0",  strlen(cmd_s)) == 0){

        printf("npu nn_MC2_sp_AluFunction_test0 test start!\n");
        npu_input_subfile_batch(concat,0,43,0); 
        
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_0();
        // itcs_dcache_invalid();
        status = sp_AluFunction_0_dump();

    }else if (strncmp(cmd_s, "nn_MC2_sp_AluFunction_test1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_AluFunction_test1 test start!\n");
        npu_input_subfile_batch(concat,0,15,0); 
        
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_1(1);
        status = sp_AluFunction_test1_dump();

    }else if(strncmp(cmd_s, "nn_MC2_sp_AluFunction_test2",  strlen(cmd_s)) == 0){
         printf("npu nn_MC2_sp_AluFunction_test2 test start!\n");
         npu_input_subfile_batch(concat,0,18,0); 
        
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
         sp_AluFunction_test2(0);
         status = sp_AluFunction_2_dump();

    }else if (strncmp(cmd_s, "nn_MC2_sp_sum_engine_control1_ch2_fromV11V12",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_sum_engine_control1_ch2_fromV11V12 test start!\n"); 
        npu_input_subfile_batch(concat,0,23,0); 
        npu_input_subfile_batch(concat,0,30,11); 
        npu_input_subfile_batch(concat,0,5,5); 
        npu_input_file_batch(concat,2,4);
        npu_input_file_batch(concat,9,10);
        npu_input_file_batch(concat,15,16);
        //npu_load_a_file(tlb_buf_load);
        nn_multi_core_MC2_sp_sum();
        status = control1_ch2_fromV11V12();

    }else if (strncmp(cmd_s, "nn_MC2_sp_sum_engine_control2_ch2_storageSame",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_MC2_sp_sum_engine_control2_ch2_storageSame test start!\n");
        npu_input_subfile_batch(concat,0,21,0);

        npu_input_file_batch(concat,10,11);
        npu_input_file_batch(concat,2,5);
        npu_input_subfile_batch(concat,0,251,6);
        //npu_load_a_file(tlb_buf_load);
        nn_multi_core_MC2_sp_sum();
        status = storageSame_dump();

    }else if(strncmp(cmd_s, "nn_multi_core_AluFunction_0",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_AluFunction_0 test start!\n");
        npu_input_subfile_batch(concat,0,2,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = AluFunction_0_test_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_AluFunction_1",  strlen(cmd_s)) == 0)
    {
         printf("npu nn_multi_core_AluFunction_1 test start!\n");
         npu_input_subfile_batch(concat,0,41,0);
         npu_input_subfile_batch(concat,0,24,1);
         npu_input_file_batch(concat,2,5);
        reg_common_cfg();
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820008b0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82001160, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82001a10, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820022c0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82002b70, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82003420, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82003cd0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82004580, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82004e30, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820056e0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82005f90, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82006840, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820070f0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820079a0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82008250, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82008b00, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820093b0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82009c60, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a510, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200adc0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b670, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200bf20, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200c7d0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d080, 0x00000044);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_AluFunction_2",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_AluFunction_2 test start!\n");
        npu_input_subfile_batch(concat,0,2,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = AluFunction_0_test_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_AluFunction_3",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_AluFunction_3 test start!\n");
        npu_input_subfile_batch(concat,0,19,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        udelay(2000000);
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200033c, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82000678, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820009b4, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82000cf0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200102c, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001368, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820016a4, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820019e0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001d1c, 0x000000e8);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_AluFunction_4",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_AluFunction_4 test start!\n");
        npu_input_subfile_batch(concat,0,1,0);
        npu_input_subfile_batch(concat,0,16,1);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        printf("npu test finish!\n");
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820003e0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820007c0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000ba0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f80, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001360, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001740, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001b20, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001f00, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820022e0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820026c0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82002aa0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82002e80, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003260, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003640, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003a20, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003e00, 0x00000048);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_convolutionStride_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_convolutionStride_1 test start!\n");
        npu_input_subfile_batch(concat,0,65,0);
       
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = convStride_1_dump();
        
    }else if(strncmp(cmd_s, "nn_multi_core_depthWise_1",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_depthWise_1 test start!\n");
        npu_input_subfile_batch(concat,0,31,0);
       
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        udelay(10000);
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000230, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f50, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001180, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001ea0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x820020d0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002df0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003020, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003d40, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003f70, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004c90, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004ec0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005be0, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005e10, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006b30, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006d60, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007a80, 0x000000f0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007cb0, 0x000000f0);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_in2ndChNum_16",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_in2ndChNum_16 test start!\n");
        npu_input_subfile_batch(concat,0,38,0);
        npu_input_subfile_batch(concat,0,13,1);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = in2ndChnum_16_dump();

    }else if(strncmp(cmd_s, "nn_multi_core_inChNum_16",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_inChNum_16 test start!\n");
        npu_input_subfile_batch(concat,0,12,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = inChnum_16_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_inImageDataType_0",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_inImageDataType_0 test start!\n");
        npu_input_subfile_batch(concat,0,19,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = image_Type_0_2_dump();
    }else if (strncmp(cmd_s, "nn_multi_core_inImageDataType_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_inImageDataType_1 test start!\n");
        npu_input_subfile_batch(concat,0,35,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = kernel_image_Date1_dump();
        
    }else if(strncmp(cmd_s, "nn_multi_core_inImageDataType_2",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_inImageDataType_2 test start!\n");
        npu_input_subfile_batch(concat,0,19,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = image_Type_0_2_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_inImageDataType_4",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_inImageDataType_4 test start!\n");
        npu_input_subfile_batch(concat,0,15,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000248, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000490, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x820006d8, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000920, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000b68, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000db0, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82000ff8, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001240, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001488, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x820016d0, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001918, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001b60, 0x00000088);
        soc_dump0(RTL_DUMP_ADDR + 0x82001da8, 0x00000088);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_inImageDataType_7",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_inImageDataType_7 test start!\n");
        npu_input_subfile_batch(concat,0,31,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = inimage_Data_7_8_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_inImageDataType_8",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_inImageDataType_8 test start!\n");
        npu_input_subfile_batch(concat,0,31,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = inimage_Data_7_8_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_kernel1x1_pooling0",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_kernel1x1_pooling0 test start!\n");
        npu_input_subfile_batch(concat,0,2,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg(); 
        status = kernel1_pooling_0_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_kernel3x3_pooling0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_kernel3x3_pooling0 test start!\n");
        npu_input_subfile_batch(concat,0,59,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = kernel3x3_pooling0();
        
    }else if(strncmp(cmd_s, "nn_multi_core_kernelDataType_0",  strlen(cmd_s)) == 0){

         printf("npu nn_multi_core_kernelDataType_0 test start!\n");
         npu_input_subfile_batch(concat,0,35,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
         reg_common_cfg();
         status = kernelData_0_2_dump();
    }else if (strncmp(cmd_s, "nn_multi_core_kernelDataType_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_kernelDataType_1 test start!\n"); 
        npu_input_subfile_batch(concat,0,35,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = kernel_image_Date1_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_kernelDataType_2",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_kernelDataType_2 test start!\n");
        npu_input_subfile_batch(concat,0,44,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = kernelData_0_2_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_kernelDataType_4",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_kernelDataType_4 test start!\n");
        npu_input_subfile_batch(concat,0,35,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82001f08, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82003e10, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82005d18, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82007c20, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x82009b28, 0x00000128);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ba30, 0x00000128);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_kernelDataType_7",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_kernelDataType_7 test start!\n");
        npu_input_subfile_batch(concat,0,29,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = kernelData_7_dump();
        
    }else if(strncmp(cmd_s, "nn_multi_core_nnCoefDecompBypass_0",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_nnCoefDecompBypass_0 test start!\n");
        npu_input_subfile_batch(concat,0,2,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load); 
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001730, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82002e60, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82004590, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82005cc0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820073f0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82008b20, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a250, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b980, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d0b0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e7e0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ff10, 0x000000e8);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_nnCoefDecompBypass_1",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_nnCoefDecompBypass_1 test start!\n"); 
        npu_input_subfile_batch(concat,0,129,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82001368, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x820026d4, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82003a3c, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82004da8, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82006110, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200747c, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x820087e4, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82009b50, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200aeb8, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200c224, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d58c, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e8f8, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x8200fc60, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82010fcc, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x82012334, 0x00000140);
        soc_dump0(RTL_DUMP_ADDR + 0x820136a0, 0x00000140);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_nnConvOnedMode_1",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_nnConvOnedMode_1 test start!\n");
        npu_input_subfile_batch(concat,0,8,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820000ac, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a40, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82000af0, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82001480, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001530, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001ec0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82001f70, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82002904, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820029b0, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003344, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820033f4, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82003d84, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82003e34, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820047c4, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82004874, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82005208, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x820052b4, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82005c48, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82005cf8, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82006688, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82006738, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820070c8, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82007178, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x82007b0c, 0x00000044);
        soc_dump0(RTL_DUMP_ADDR + 0x82007bb8, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x8200854c, 0x00000048);
        soc_dump0(RTL_DUMP_ADDR + 0x820085fc, 0x00000044);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_NN_fast_xdp3_kx3_outTilex64",  strlen(cmd_s)) == 0)
    {
        
        printf("npu nn_multi_core_NN_fast_xdp3_kx3_outTilex64 test start!\n");
        npu_input_subfile_batch(concat,0,7,0);
        npu_input_file_batch(concat,2,5);
        memset((char* )RTL_DUMP_ADDR + 0x82000000,0, 0x000000c4);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000c4);
        soc_dump0(RTL_DUMP_ADDR + 0x82000604, 0x000000c8);
        soc_dump0(RTL_DUMP_ADDR + 0x82000c0c, 0x000000c4);
        soc_dump0(RTL_DUMP_ADDR + 0x82001210, 0x000000c8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001818, 0x000000c4);
        soc_dump0(RTL_DUMP_ADDR + 0x82001e1c, 0x000000c8);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_outChNum_16",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outChNum_16 test start!\n");
        npu_input_subfile_batch(concat,0,22,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = outChNum_16_dump();
    }else if (strncmp(cmd_s, "nn_multi_core_outImageDataType_0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_outImageDataType_0 test start!\n");
        npu_input_subfile_batch(concat,0,17,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = OutimageData_0_2_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_outImageDataType_1",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outImageDataType_1 test start!\n");
        npu_input_subfile_batch(concat,0,53,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = OutimageData_1_7_dump();
    }else if (strncmp(cmd_s, "nn_multi_core_outImageDataType_2",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_multi_core_outImageDataType_2 test start!\n");
        npu_input_subfile_batch(concat,0,17,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = OutimageData_0_2_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_outImageDataType_4",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outImageDataType_4 test start!\n");
        npu_input_subfile_batch(concat,0,17,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = OutimageData_4_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_outImageDataType_7",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_outImageDataType_7 test start!\n");
        npu_input_subfile_batch(concat,0,53,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = OutimageData_1_7_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_outImageDataType_8",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_outImageDataType_8 test start!\n");
        npu_input_subfile_batch(concat,0,17,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = OutimageData_8_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_pooling_1",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_multi_core_pooling_1 test start!\n");
        npu_input_subfile_batch(concat,0,12,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        udelay(2000000);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82000d10, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82001a20, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82002730, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82003440, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82004150, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82004e60, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82005b70, 0x000000bc);
        soc_dump0(RTL_DUMP_ADDR + 0x82006880, 0x000000bc);
        status = npu_compare(result_file_name);
        
    }else if(strncmp(cmd_s, "nn_multi_core_pooling_3",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_pooling_3 test start!\n");
        npu_input_subfile_batch(concat,0,89,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        udelay(2000000);
        // itcs_dcache_invalid();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000078);
        soc_dump0(RTL_DUMP_ADDR + 0x820000e8, 0x00000078);
        soc_dump0(RTL_DUMP_ADDR + 0x82000bc8, 0x00000078);
        soc_dump0(RTL_DUMP_ADDR + 0x82000cb0, 0x00000078);
        
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_PoolSize2x2_PoolStride1_iv4_img1st1_indata0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_PoolSize2x2_PoolStride1_iv4_img1st1_indata0 test start!\n");
        npu_input_subfile_batch(concat,0,12,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x820019c0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82003380, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82004d40, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82006700, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x820080c0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82009a80, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b440, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ce00, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e7c0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82010180, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82011b40, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82013500, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82014ec0, 0x000000dc);
        soc_dump0(RTL_DUMP_ADDR + 0x82016880, 0x000000dc);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_PoolSize2x2_PoolStride2_iv4_img1st1_indata0",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_PoolSize2x2_PoolStride2_iv4_img1st1_indata0 test start!\n");
        npu_input_subfile_batch(concat,0,17,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000048, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000090, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820000d8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000120, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000168, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820001b0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820001f8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000240, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000288, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820002d0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000318, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000500, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000548, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000590, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820005d8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000620, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000668, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820006b0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820006f8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000740, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000788, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820007d0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000818, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a00, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a48, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000a90, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000ad8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000b20, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000b68, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000bb0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000bf8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000c40, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000c88, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000cd0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000d18, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f00, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f48, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f90, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82000fd8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001020, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001068, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820010b0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820010f8, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001140, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001188, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x820011d0, 0x0000001c);
        soc_dump0(RTL_DUMP_ADDR + 0x82001218, 0x0000001c);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_PoolSize3x3_PoolStride1_iv4_img1st1_indata0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_PoolSize3x3_PoolStride1_iv4_img1st1_indata0 test start!\n");
        npu_input_subfile_batch(concat,0,25,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg(); 
         soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200022c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000458, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000684, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000d08, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82000f34, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001160, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200138c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001a10, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001c3c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82001e68, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002094, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002718, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002944, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002b70, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82002d9c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003420, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200364c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003878, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82003aa4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004128, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004354, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004580, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820047ac, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82004e30, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200505c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005288, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820054b4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005b38, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005d64, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82005f90, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820061bc, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006840, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006a6c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006c98, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82006ec4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007548, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007774, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820079a0, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82007bcc, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82008250, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200847c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820086a8, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820088d4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82008f58, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82009184, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820093b0, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x820095dc, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82009c60, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x82009e8c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a0b8, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a2e4, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a968, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ab94, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200adc0, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200afec, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b670, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b89c, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200bac8, 0x000000d0);
        soc_dump0(RTL_DUMP_ADDR + 0x8200bcf4, 0x000000d0);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_multi_core_PoolSize3x3_PoolStride2_iv4_img1st1_indata0",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_PoolSize3x3_PoolStride2_iv4_img1st1_indata0 test start!\n");
        npu_input_subfile_batch(concat,0,134,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
         soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82001ee0, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82003dc0, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82005ca0, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82007b80, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x82009a60, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b940, 0x000002ac);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d820, 0x000002ac);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_sp_AluFunction_test0",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_sp_AluFunction_test0 test start!\n");
        npu_input_subfile_batch(concat,0,43,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_0();
        status = sp_AluFunction_0_dump();
    }else if(strncmp(cmd_s, "nn_multi_core_sp_AluFunction_test1",  strlen(cmd_s)) == 0){
        printf("npu nn_MC2_sp_AluFunction_test1 test start!\n");
        npu_input_subfile_batch(concat,0,15,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_1(1);
        status = sp_AluFunction_test1_dump();

    }else if (strncmp(cmd_s, "nn_multi_core_sp_AluFunction_test2",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_sp_AluFunction_test2 test start!\n");
        const char *load_file = "nn_MC2_sp_AluFunction_test2_data/mem";
        npu_input_subfile_batch(load_file,0,18,0);
        npu_input_file_batch(load_file,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_test2(1);
        status = sp_AluFunction_2_dump();
        
    }else if(strncmp(cmd_s, "nn_multi_core_sp_sum_engine_control1_ch2_fromV11V12",  strlen(cmd_s)) == 0){

        printf("npu nn_multi_core_sp_sum_engine_control1_ch2_fromV11V12 test start!\n"); 
        npu_input_subfile_batch(concat,0,23,0);
        npu_input_subfile_batch(concat,0,30,11);
        npu_input_subfile_batch(concat,0,5,5);
        npu_input_file_batch(concat,2,4);
        npu_input_file_batch(concat,10,10);
        npu_input_file_batch(concat,15,16);
        //npu_load_a_file(tlb_buf_load);
        nn_multi_core_MC2_sp_sum();
        status = control1_ch2_fromV11V12();

    }else if (strncmp(cmd_s, "nn_multi_core_sp_sum_engine_control2_ch2_storageSame",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_sp_sum_engine_control2_ch2_storageSame test start!\n"); 
        npu_input_subfile_batch(concat,0,21,0);
        npu_input_subfile_batch(concat,0,251,6);
      
        npu_input_file_batch(concat,2,5);
        npu_input_file_batch(concat,10,11);
     
        //npu_load_a_file(tlb_buf_load);
        nn_multi_core_MC2_sp_sum();
        status = storageSame_dump();

    }else if(strncmp(cmd_s, "nn_multi_core_v8_conv_int_bring_up_3",  strlen(cmd_s)) == 0){
        printf("npu nn_multi_core_v8_conv_int_bring_up_3 test start!\n"); 
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_multi_core_vipsram_mode_1010",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_multi_core_vipsram_mode_1010 test start!\n");
        npu_input_subfile_batch(concat,0,2,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82001730, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82002e60, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82004590, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82005cc0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x820073f0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x82008b20, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200a250, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200b980, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200d0b0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200e7e0, 0x000000e8);
        soc_dump0(RTL_DUMP_ADDR + 0x8200ff10, 0x000000e8);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "nn_PerChQuantization",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_PerChQuantization test start!\n");
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00004048);
        status = npu_compare(result_file_name);
        
    }else if(strncmp(cmd_s, "nn_sp_AluFunction_test0",  strlen(cmd_s)) == 0){
        
        printf("npu nn_sp_AluFunction_test0 test start!\n");
        npu_input_subfile_batch(concat,0,43,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000014), 0x00FFFF);
        MA_OUTW((base0 + 0x000090), 0x000040);
        MA_OUTW((base0 + 0x000100), 0x140021);
        MA_OUTW((base0 + 0x000178), 0x00BBE4);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000014), 0x00FFFF);
        MA_OUTW((base1 + 0x000090), 0x000040);
        MA_OUTW((base1 + 0x000100), 0x140020);
        MA_OUTW((base1 + 0x000178), 0x002BC5);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10000000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
        status = sp_AluFunction_0_dump();

    }else if (strncmp(cmd_s, "nn_sp_AluFunction_test1",  strlen(cmd_s)) == 0)
    {   
        printf("npu nn_sp_AluFunction_test1 test start!\n");
        npu_input_subfile_batch(concat,0,15,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_1(0);
        status = sp_AluFunction_test1_dump();
        
    }else if(strncmp(cmd_s, "nn_sp_AluFunction_test2",  strlen(cmd_s)) == 0){
        printf("npu nn_sp_AluFunction_test2 test start!\n");
        npu_input_subfile_batch(concat,0,18,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        sp_AluFunction_test2(3);
        status  = sp_AluFunction_2_dump();
        

    }else if (strncmp(cmd_s, "nn_sp_sum_engine_control1_ch2_fromV11V12",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_sp_sum_engine_control1_ch2_fromV11V12 test start!\n"); 
        
        npu_input_subfile_batch(concat,0,23,0);
        npu_input_subfile_batch(concat,0,30,11);
        npu_input_file_batch(concat,15,16);
        npu_input_file_batch(concat,9,10);
        npu_input_file_batch(concat,2,4);
        npu_input_subfile_batch(concat,0,5,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = control1_ch2_fromV11V12();

    }else if(strncmp(cmd_s, "nn_sp_sum_engine_control2_ch2_storageSame",  strlen(cmd_s)) == 0){

        printf("npu nn_sp_sum_engine_control2_ch2_storageSame test start!\n");
        npu_input_subfile_batch(concat,0,21,0);
        
        npu_input_file_batch(concat,10,11);
       
        npu_input_file_batch(concat,2,5);
        npu_input_subfile_batch(concat,0,251,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        status = storageSame_dump();
    }else if (strncmp(cmd_s, "nn_tensorAdd",  strlen(cmd_s)) == 0)
    {
        printf("npu nn_tensorAdd test start!\n");
        npu_input_file_batch(concat,0,5);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000048);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "nn_transpose",  strlen(cmd_s)) == 0){
        printf("npu nn_transpose test start!\n"); 
        npu_input_file_batch(concat,0,0);
        npu_input_file_batch(concat,2,6);
        //npu_load_a_file(tlb_buf_load);
        reg_common_cfg();
        soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000408);
        status = npu_compare(result_file_name);
    }else if (strncmp(cmd_s, "shader_copy_cram2",  strlen(cmd_s)) == 0)
    {
         printf("npu shader_copy_cram2 test start!\n"); 
        npu_load_a_file("shader_copy_cram2_data/mem0_cmd_buf.bin");
        npu_load_a_file("shader_copy_cram2_data/mem1_sh_buf.bin");
        npu_load_a_file("shader_copy_cram2_data/mem2_src_buf.bin");
        // npu_load_a_file("shader_copy_cram2_data/mem3_tlb_buf.bin");
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
  #ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        if(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x10200000, 0x00001008);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "shader_copy",  strlen(cmd_s)) == 0){
        printf("npu shader_copy test start!\n"); 
        npu_load_a_file("shader_copy_data/mem0_cmd_buf.bin");
        npu_load_a_file("shader_copy_data/mem1_sh_buf.bin");
        npu_load_a_file("shader_copy_data/mem2_src_buf.bin");
        // npu_load_a_file("shader_copy_data/mem3_tlb_buf.bin");
        npu_load_a_file("shader_copy_data/mem0_cmd_buf1.bin");
        npu_load_a_file("shader_copy_data/mem1_sh_buf1.bin");
        npu_load_a_file("shader_copy_data/mem2_src_buf1.bin");
        MA_OUTW((base0 + 0x00010C), 0x020000);
        MA_OUTW((base1 + 0x00010C), 0x020000);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x010030);
        MA_OUTW((base1 + 0x0003A4), 0x010030);
        rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        // itcs_dcache_invalid();
        soc_dump0(RTL_DUMP_ADDR + 0x20200000, 0x00001008);
        status = npu_compare(result_file_name);

    }else if (strncmp(cmd_s, "sys_semaphore",  strlen(cmd_s)) == 0)
    {
        printf("npu sys_semaphore test start!\n"); 
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
        MA_OUTW((base0 + 0x0003B4), 0x1FF0001);
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x10001000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
        MA_OUTW((base1 + 0x0003B4), 0x1FF0001);
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x10001000);
        MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
            rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
            }
            rd_val = 0x1;
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
            }

        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x40200000, 0x00001008);
        soc_dump0(RTL_DUMP_ADDR + 0x41200000, 0x00001008);
        soc_dump0(RTL_DUMP_ADDR + 0x42200000, 0x00001008);
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "LocalStorageAccess",  strlen(cmd_s)) == 0){


        // memset((char*)0x1103D0000,0,0x1000);
        // memset((char*)0x1103E0000,0,0x1000);
        // memset((char*)0x1103F0000,0,0x1000);
        memset((char*)0x1004f0000,0,0x1000);
        // npu_load_a_file("LocalStorageAccess_data/mem0_cmd_buffer_0_0.bin");
        npu_load_a_file("LocalStorageAccess_data/mem0_cmd_buffer_0_1.bin");
        // npu_load_a_file("LocalStorageAccess_data/mem1_cmd_buffer_1_0.bin");
        npu_load_a_file("LocalStorageAccess_data/mem1_cmd_buffer_1_1.bin");
        // npu_load_a_file("LocalStorageAccess_data/mem2_cmd_buffer_2_0.bin");
        npu_load_a_file("LocalStorageAccess_data/mem2_cmd_buffer_2_1.bin");
        
        npu_load_a_file("LocalStorageAccess_data/mem3_shader_buffer.bin");
        // npu_load_a_file("LocalStorageAccess_data/mem4_clear_buffer.bin");
        npu_load_a_file("LocalStorageAccess_data/mem3_tlb_buf.bin");

        // itcs_dcache_flush();
#ifdef CONFIG_TB_RUN_DDR1
        MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
        MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
 
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x103D0000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        udelay(1000);
    while(rd_val != 0x0){
    rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        MA_OUTW((base0 + 0x000654), 0x103E0000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
            rd_val = 0x1;
            udelay(1000);
        while(rd_val != 0x0){
        rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        MA_OUTW((base0 + 0x000654), 0x103F0000);
        MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
        rd_val = 0x1;
        udelay(1000);
    while(rd_val != 0x0){
    rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
 

        // itcs_dcache_invalid();

        udelay(20000);
        printf("npu test finish!\n"); 
        soc_dump0(RTL_DUMP_ADDR + 0x037fdf00, 0x00000088);
        
       
     
        status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "resnet_v1_50_block1_v2_int8_DV",  strlen(cmd_s)) == 0){
        printf("npu resnet_v1_50_block1_v2_int8_DV test start\n");
        npu_input_file_batch(concat,0,296);
        
        printf("npu resnet_v1_50_block1_v2_int8_DV test start!\n"); 
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x0003C1);
       #ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x20000000);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base1 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base1 + 0x0003B4), 0x1FF0001);//ddr0
#endif
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x000654), 0x20000000);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
    
   while(rd_val != 0x0){
    
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x20004A38);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x20004A38);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
  
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
  
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x200072A0);
    MA_OUTW((base0 + 0x0003A4), 0x01FFFF);
    MA_OUTW((base1 + 0x000654), 0x200072A0);
    MA_OUTW((base1 + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
   while(rd_val != 0x0){
   
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
  
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }

    printf("npu test finish!\n"); 
    soc_dump0(RTL_DUMP_ADDR + 0x01e20100, 0x000c4008);
    status = npu_compare(result_file_name);
    }else if(strncmp(cmd_s, "mask_image",  strlen(cmd_s)) == 0){
        printf("npu mask image test start\n");

        npu_load_a_file("mask_image_data/mem0_command_buffer.bin");
        npu_load_a_file("mask_image_data/mem1_vshader_buffer.bin");
        npu_load_a_file("mask_image_data/mem2_clear_buffer.bin");
        npu_load_a_file("mask_image_data/mem3_input_buffer.bin");
        // npu_load_a_file("mask_image_data/mem3_tlb_buf.bin");
        // itcs_dcache_flush();
        // itcs_dcache_flush();
        MA_OUTW((base0 +0x000010c),0x020000);
        
#ifdef CONFIG_TB_RUN_DDR1
    MA_OUTW((base0 + 0x0003B4), 0x5FF0001);
#else
    MA_OUTW((base0 + 0x0003B4), 0x1FF0001);//ddr0
#endif
        MA_OUTW((base0 +0x0000388),0x021);
        MA_OUTW((base0 +0x000654),0x30001000);
        MA_OUTW((base0 +0x0003A4),0x01011c);
        rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        printf("npu test finish\n");
        // itcs_dcache_invalid_range(0x120000000,0x0012c000);
        // udelay(1000000);
        soc_dump0(RTL_DUMP_ADDR +0x20000000, 0x0012c008);
        // udelay(5000000);
        // memcpy((char*)0x140000000,(char*)0x120000000,0x0012c000);
        status =npu_compare(result_file_name);
       
        // return status;
    }else if(strncmp(cmd_s, "yolov5_core0",  strlen(cmd_s)) == 0){
        clk_up_test(yolov5_id3_core0_DV);
    //    yolov5_id3_core0_DV();
        // return status;
    }else if(strncmp(cmd_s, "yolov5_core1",  strlen(cmd_s)) == 0){
        
       clk_up_test(yolov5s_id3_core1_DV);
        // return status;
    }else if(strncmp(cmd_s, "yolov5_2core",  strlen(cmd_s)) == 0){
        
       clk_up_test(yolov5s_id3_2core_DV);
        // return status;
    }else if(strncmp(cmd_s, "mobilenet_node0_2_DV",  strlen(cmd_s)) == 0){
        
    //    clk_up_test(yolov5s_id3_2core_DV);
        npu_input_file_batch(concat,0,12);
        mobilenet_test();
        status = npu_compare(result_file_name);
        // return status;
    }else{
        printf("command id not match\n");
    }
    printf("dump file total size %d\n",total_size);
    printf("write bus bandwidth %d\n",MA_INW(base0+0x44));
    
    if(status == 0){
        printf("%s Pass\n",cmd_s);
    }else{
        printf("%s failed\n",cmd_s);
    }
    return status;
}

int test_npu_freq(void)
{
    unsigned long start_time = 0, end_time = 0;
    unsigned int base = 0xc7000000; 
    start_time = get_timer_us(0);
    MA_OUTW((base + 0x00078), 0);
    udelay(100); 
    unsigned long cycle = MA_INW((base + 0x00078));
    end_time = get_timer_us(0);
    unsigned int diff = end_time - start_time;
    printf("cycle: %lu, diff: %u\n", cycle, diff); 
    unsigned int freq = cycle * 1000000 / diff;
    printf("npu freq: %d Hz\n", freq);
    return 0;
}

int npu_9200_evb_test(char *input_cmd) {

    int ret = 0;
    test_npu_freq();
    char *buf[]={
        "alexnet_int8_001_power_DV",
        "alexnet_int8_003_power_DV",
        "ddr_bw_test_read_only",
        "ddr_bw_test_write_read",
        "ddr_bw_test_write_only",
        "image_blend",
        "image_filter",
        "lenet_1core_DV",
        "mmu_extend4gAddr",
        "nn_40bitVA_kernel_1x1",
        "nn_40bitVA_kernel_3x3",
        "nn_convolution_fp16",
        "nn_convolution_int16",
        "nn_convolution_int8",
        "nn_ddr_read",
        "nn_ddr_write",
        "nn_kernel_3x3",
        "nn_max_OT",
        "nn_MC2_AluFunction_0",
        "nn_MC2_kernel3x3_pooling0",
        "nn_MC2_PerChQuantization",
        "nn_MC2_sp_AluFunction_test0",
        "nn_MC2_sp_AluFunction_test1",
        "nn_MC2_sp_AluFunction_test2",
        "nn_MC2_sp_sum_engine_control1_ch2_fromV11V12",
        "nn_MC2_sp_sum_engine_control2_ch2_storageSame",
        "nn_multi_core_AluFunction_0", 
        "nn_multi_core_AluFunction_1",
        "nn_multi_core_AluFunction_2", 
        "nn_multi_core_AluFunction_3", 
        "nn_multi_core_AluFunction_4",
        "nn_multi_core_convolutionStride_1",
        "nn_multi_core_depthWise_1",
        "nn_multi_core_in2ndChNum_16",
        "nn_multi_core_inChNum_16",
        "nn_multi_core_inImageDataType_0",
        "nn_multi_core_inImageDataType_1",
        "nn_multi_core_inImageDataType_2",
        "nn_multi_core_inImageDataType_4",
        "nn_multi_core_inImageDataType_7",
        "nn_multi_core_inImageDataType_8",
        "nn_multi_core_kernel1x1_pooling0",
        "nn_multi_core_kernel3x3_pooling0",
        "nn_multi_core_kernelDataType_0", 
        "nn_multi_core_kernelDataType_1",
        "nn_multi_core_kernelDataType_2",
        "nn_multi_core_kernelDataType_4",
        "nn_multi_core_kernelDataType_7", 
        "nn_multi_core_nnCoefDecompBypass_0",
        "nn_multi_core_nnCoefDecompBypass_1",
        "nn_multi_core_nnConvOnedMode_1",
        "nn_multi_core_NN_fast_xdp3_kx3_outTilex64",
        "nn_multi_core_outChNum_16",
        "nn_multi_core_outImageDataType_0",
        "nn_multi_core_outImageDataType_1",
        "nn_multi_core_outImageDataType_2",
        "nn_multi_core_outImageDataType_4",
        "nn_multi_core_outImageDataType_7",
        "nn_multi_core_outImageDataType_8",
        "nn_multi_core_pooling_1",
        "nn_multi_core_pooling_3",
        "nn_multi_core_PoolSize2x2_PoolStride1_iv4_img1st1_indata0",
        "nn_multi_core_PoolSize2x2_PoolStride2_iv4_img1st1_indata0", 
        "nn_multi_core_PoolSize3x3_PoolStride1_iv4_img1st1_indata0",
        "nn_multi_core_PoolSize3x3_PoolStride2_iv4_img1st1_indata0",
        "nn_multi_core_sp_AluFunction_test0",
        "nn_multi_core_sp_AluFunction_test1",
        "nn_multi_core_sp_AluFunction_test2",
        "nn_multi_core_sp_sum_engine_control1_ch2_fromV11V12", 
        "nn_multi_core_sp_sum_engine_control2_ch2_storageSame",
        "nn_multi_core_v8_conv_int_bring_up_3", 
        "nn_multi_core_vipsram_mode_1010",
        "nn_PerChQuantization",
        "nn_sp_AluFunction_test0",
        "nn_sp_AluFunction_test1",
        "nn_sp_AluFunction_test2",
        "nn_sp_sum_engine_control1_ch2_fromV11V12", 
        "nn_sp_sum_engine_control2_ch2_storageSame",
        "nn_tensorAdd",
        "nn_transpose",
        "shader_copy_cram2",
        "shader_copy",  
        "LocalStorageAccess",
        "resnet_v1_50_block1_v2_int8_DV",
        "mask_image"
    };
    if(strncmp(input_cmd, "all",  strlen(input_cmd))==0){
        for(int i = 0 ; i < sizeof(buf)/sizeof(char *) ;i++){
   
        ret |= npu_only_evb(buf[i]);
        udelay(1000000);
     }
    }else{
        printf("single case\n");
        ret = npu_only_evb(input_cmd);
    }
    
    return ret;
}

