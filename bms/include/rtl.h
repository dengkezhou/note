#ifndef __RTL_H__
#define __RTL_H__

#define RTL_MAGIC 0x97979897
extern int try_rtl(void);

#define RTL_INDICATE_SIZE 0x200

#define RTL_MSG_KEY         0x0
#define RTL_MSG_MEMCPY_DEST 0x4
#define RTL_MSG_MEMCPY_SRC  0x8
#define RTL_MSG_MEMCPY_SIZE 0xc
enum rtl_stage {
  RTL_NOINIT   = 0,    /* RTL is not running */
  RTL_STARTING = 0x85, /* RTL test is beginning to start */
  RTL_PASS     = 0x50, /* RTL test is finished, and result OK */
  RTL_DONE = 0x26, /* RTL test is finished, but you need to manually check the
                      result */
  RTL_FAIL        = 0x46, /* RTL test is finished, and result FAILED */
  RTL_ERROR       = 0xee, /* RTL test program error */
  RTL_MEMCPY      = 0x77, /* RTL host memcpy action */
  RTL_MEMDST      = 0xa5f4,
  RTL_MEMSRC      = 0xa5f0,
  RTL_MEMVAL      = 0xa5f8,
  RTL_MEMLEN      = 0xa5fc,
  RTL_MEMTYPE     = 0xa5fe,
  RTL_RELOAD      = 0xb001a53c,
  RTL_RELOAD_SRAM = 0xb002a53c
};

extern int rtl_move_stage(enum rtl_stage stage);
int rtl_host_set(int type, uint64_t value);
int rtl_host_get(int offset);

#endif /* __RTL_H__ */
