
#ifndef __INITCALL_H__
#define __INITCALL_H__

typedef void (*initcall_t)(void);

#define __initcall_f(fn, l)                                                    \
  initcall_t __initcall_##fn __attribute__((__used__))                         \
      __attribute__((section(".init_f" #l))) = fn

#define core_init(fn)      __initcall_f(fn, 0)
#define module_init(fn)    __initcall_f(fn, 1)
#define testbench_init(fn) __initcall_f(fn, 2)


#define TESTBENCH_INIT_HELPER(name)                                           \
  static int name##_main(int argc, char *argv[]);                                 \
  static void name##_init(void) { register_testbench(#name, name##_main, NULL); } \
  testbench_init(name##_init);                                                    \
  static int name##_main(int argc, char *argv[])

#endif /* __INITCALL_H__ */
