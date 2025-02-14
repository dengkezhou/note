#ifndef __SYSMAP_H__
#define __SYSMAP_H__

#define MAX_REGIONS   8
#define sysmap_attr_t uint32_t

typedef struct sysmap_region {
  unsigned long end;
  sysmap_attr_t attr;
} sysmap_region_t;

extern void systemmap_config(void);
#endif
