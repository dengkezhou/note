
/* generate rtlfs */
#include <common.h>
#include <semihost.h>
#include <command.h>
#include <initcall.h>
#include <sysm.h>
#include <rtl.h>

extern char __lds_rtl_case[];

struct rtl_case {
  int id;
  int len;
  int soffs;
  /* the position of case packaging where command residence
   * not necessary 8 bytes */
  char cmd[8];
} *rtl_cases = (struct rtl_case *)(__lds_rtl_case + 8);

struct rtl_desc {
  int magic;
  int id;
} *rtl_descs = (struct rtl_desc *)(__lds_rtl_case);

struct rtl_case *rtl_get_next_case(struct rtl_case *p) {
  p = (struct rtl_case *)(p->cmd + ((p->len + 8) & ~7));

  //	printf("p===%p\n", p);

  if (!p->len)
    return NULL;

  return p;
}

char *rtl_get_command(struct rtl_case *p, domain_t domain) {
  if (domain == CPU) {
    if (p->soffs > 0)
      p->cmd[p->soffs] = '\0';
    return p->cmd;
  }

  return (p->soffs <= 0) ? NULL : p->cmd + p->soffs + 1;
}

int rtl_run_case(int id) {
  struct rtl_case *p = rtl_cases;
#ifdef CONFIG_COMPILE_ROM
  int ident = SAP;
#else
  int ident = CPU;
#endif
  char *cmd;
  int ret = 0;

  printf("run RTL testlink_id: 0x%x\n", id);

  do {
    //		printf("p->id: %d, p->len: %d\n", p->id, p->len);
    if (p->id == id) {
      /* run command p->cmd */
      cmd = rtl_get_command(p, ident);
      printf("rtl command: %s\n", cmd);
      ret = parse_command(cmd, 0);
    }
  } while ((p = rtl_get_next_case(p)));

  return ret;
}

int try_rtl(void) {
  int ret;
  if (rtl_descs->magic == RTL_MAGIC && rtl_descs->id) {
    rtl_move_stage(RTL_STARTING);
    ret = rtl_run_case(rtl_descs->id);

    if (ret == 0)
      rtl_move_stage(RTL_PASS);
    else if (ret == 1)
      rtl_move_stage(RTL_DONE);
    else if (ret < 0)
      rtl_move_stage(RTL_FAIL);
    else
      rtl_move_stage(RTL_ERROR);

    return 1;
  }

  return 0;
}
