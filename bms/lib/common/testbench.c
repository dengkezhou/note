
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <initcall.h>

struct testbench_node {
  const char *name;
  int (*cmd_entry)(int argc, char *argv[]);
  int (*rtl_entry)(int index);
};

static struct testbench_node *testbench_list;
static int testbench_count = 0, testbench_max = 0;

static void testbench_core_init(void) {
#ifdef CONFIG_COMPILE_RTL
	int listlen = 0x200;
#else
	int listlen = 0x1000;
#endif
  testbench_list = (struct testbench_node *)malloc(listlen);
	if (!testbench_list) {
		printf("Err to alloc testbench\n");
		return;
	}
  memset((void *)testbench_list, 0, listlen);

  testbench_max = listlen / sizeof(struct testbench_node);

  printf("testbench: initialized buffer for %d benches\n", testbench_max);
}

int register_testbench(const char *name, void *cmd_entry, void *rtl_entry) {
  if (testbench_count >= testbench_max) {
    printf("testbench: buffer is full, register failed.\n");
    return -1;
  }

  testbench_list[testbench_count].cmd_entry = cmd_entry;
  testbench_list[testbench_count].rtl_entry = rtl_entry;
  testbench_list[testbench_count].name      = name;

  /* register command */
  register_command(name, cmd_entry);

  printf("testbench: registered for %s\n", name);
  testbench_count++;
  return 0;
}

module_init(testbench_core_init);
