
/* rtl flow control */
#include <common.h>
#include <command.h>
#include <initcall.h>
#include <rtl.h>
#include <asm/io.h>

static int __rtl_stage = RTL_NOINIT;
extern char __lds_indicate[];
extern int __lds_print[];

/**
 * @brief rtl_host_set
 *
 * @param offset must less than indicate size
 * @param value
 *
 * @return success 1 ,else offset > indicate size -> -1
 */
int rtl_host_set(int type, uint64_t value) {
  int loop = 0;

  switch (type) {
  case RTL_MEMDST:
  case RTL_MEMSRC:
  case RTL_MEMVAL:
    loop = 4;
    break;
  case RTL_MEMLEN:
    loop = 2;
    break;
  case RTL_MEMTYPE:
    loop = 1;
    break;
  default:
    // printf("Do not support this type: %d, value 0x%lx\n", type, value);
    return -1;
  }
  for (int i = 0; i < loop; i++)
    writel((uint32_t)(type + i) | (((value >> (16 * i)) & 0xffff) << 16),
           (unsigned long)__lds_print);
  return 1;
}
/**
 * @brief rtl_host_get
 *
 * @param offset
 * @param *value ,can not be null
 *
 * @return if value null ,return -1,else 1
 */
int rtl_host_get(int offset) { return readl(__lds_indicate + offset); }

int rtl_move_stage(enum rtl_stage stage) {
  switch (stage) {
  case RTL_STARTING:
    if (__rtl_stage == RTL_NOINIT)
      __rtl_stage = stage;
    break;
  case RTL_PASS:
  case RTL_DONE:
  case RTL_FAIL:
  case RTL_ERROR:
    if (__rtl_stage == RTL_STARTING)
      __rtl_stage = stage;
#ifndef CONFIG_COMPILE_ROM
    /* templately send a finish flag */
    writel((uint32_t)0xaa55, (unsigned long)__lds_print);
#endif
#ifdef CONFIG_C920
    asm("sync.i");
#endif
    break;
  case RTL_NOINIT:
    break;
  case RTL_RELOAD:
  case RTL_RELOAD_SRAM:
    writel((uint32_t)stage, (unsigned long)__lds_print);
#ifdef CONFIG_C920
    asm("sync.i");
#endif
    break;
  default:
    return -1;
  }
  rtl_host_set(0, stage);
  //	writel(stage, (long)__lds_indicate);
  return stage;
}
