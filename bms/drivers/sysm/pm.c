#include <common.h>
#include <pm.h>
#include <irq.h>
#include <rtc-sysm.h>

static LIST_HEAD(pm_list);

void itcs_register_pm(dev_pm_t *pm)
{
	if (!pm)
		return;

	list_add_tail(&pm->list, &pm_list);
	//	printf("Register PM %s\n", pm->name);
}

void itcs_pm_show(void)
{
	dev_pm_t *pm = NULL;

	list_for_each_entry(pm, &pm_list, list)
		printf("Register PM: %s\n", pm->name);
}

void itcs_pm_run_suspend(void)
{
	dev_pm_t *pm = NULL;

	list_for_each_entry(pm, &pm_list, list) {
		printf("Suspend: %s\n", pm->name);
		if (pm->ops.suspend)
			pm->ops.suspend(pm->priv);
	}
#ifdef CONFIG_C920
	asm("sync.is");
#endif
}

void itcs_pm_run_resume(void)
{
	dev_pm_t *pm = NULL;

	list_for_each_entry(pm, &pm_list, list) {
		printf("Resume: %s\n", pm->name);
		if (pm->ops.resume)
			pm->ops.resume(pm->priv);
	}
}

void itcs_platform_pm_enter(void)
{
	rtc_set_event(RTC_SLEEP);
	hang();
}
