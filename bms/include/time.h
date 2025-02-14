#include <linux/time.h>
/*  Return the current time and put it in *TIMER if TIMER is not NULL.  */

extern struct tm *localtime(__const time_t *__timer);
