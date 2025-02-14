
#ifndef __TESTBENCH_H__
#define __TESTBENCH_H__
#include <initcall.h>

extern int testbench_core_init(void);
extern int register_testbench(const char *name, void *cmd_entry,
                              void *rtl_entry);
extern void testbench_initcall(void);
extern void __initcall(void);

#endif /* __TESTBENCH_H__ */
