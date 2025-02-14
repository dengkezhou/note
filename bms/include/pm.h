#ifndef __PM_H__
#define __PM_H__

#include <linux/list.h>

typedef struct dev_pm_ops {
  int (*prepare)(void *privdata);
  void (*complete)(void *privdata);
  int (*suspend)(void *privdata);
  int (*resume)(void *privdata);
  int (*freeze)(void *privdata);
  int (*thaw)(void *privdata);
  int (*poweroff)(void *privdata);
  int (*restore)(void *privdata);
  int (*suspend_late)(void *privdata);
  int (*resume_early)(void *privdata);
  int (*freeze_late)(void *privdata);
  int (*thaw_early)(void *privdata);
  int (*poweroff_late)(void *privdata);
  int (*restore_early)(void *privdata);
  int (*suspend_noirq)(void *privdata);
  int (*resume_noirq)(void *privdata);
  int (*freeze_noirq)(void *privdata);
  int (*thaw_noirq)(void *privdata);
  int (*poweroff_noirq)(void *privdata);
  int (*restore_noirq)(void *privdata);
  int (*runtime_suspend)(void *privdata);
  int (*runtime_resume)(void *privdata);
  int (*runtime_idle)(void *privdata);
} dev_pm_ops_t;

typedef struct dev_pm {
  char name[32];
  struct list_head list;
  void *priv;
  dev_pm_ops_t ops;
} dev_pm_t;

extern void itcs_register_pm(dev_pm_t *pm);
extern void itcs_pm_show(void);
extern void itcs_pm_run_suspend(void);
extern void itcs_pm_run_resume(void);
extern void itcs_platform_pm_enter(void);

#define SIMPLE_PM_OPS(pmname, suspendfn, resumefn, _priv)                      \
  dev_pm_t pm_##pmname = {.name = #pmname,                                     \
                          .priv = _priv,                                       \
                          .ops  = {                                            \
                              .suspend = suspendfn,                           \
                              .resume  = resumefn,                            \
                          }}

#endif
