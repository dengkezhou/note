# CACHE&MMu相关接口说明

## 头文件

```c
#include <mmu_table.h>
#include <cache.h>
```

## 接口说明

### L1 CACHE

* ICACHE状态查询

```c
int itcs_icache_status(void)
```

查询ICACHE状态  
|返回值|返回值说明|
|--|--|
|非0|ICACHE处于使能状态|
|0|ICACHE处于禁止状态|

* ICACHE使能

```c
void itcs_icache_enable(void)
```

打开L1 ICACHE

* ICACHE禁止

```c
void itcs_icache_disable(void)
```

关闭L1 ICAHCE

* ICACHE无效

```c
void itcs_icache_invalid(void)
```

遍历WAY/SET，使ICACHE/L2 CACHE中的数据无效

* DCACHE状态查询

```c
void itcs_dcache_status(void)
```


查询DCACHE状态  
|返回值|返回值说明|
|--|--|
|非0|DCACHE处于使能状态|
|0|DCACHE处于禁止状态|

* DCACHE使能

```c
void itcs_dcache_enable(void)
```

打开L1 DCACHE

```c
void itcs_dcache_disable(void)
```

关闭L1 DCAHCE

* DCACHE同步

```c
void itcs_dcache_clean(void)
```

遍历WAY/SET遍历，清理DCACHE/L2 CACHE中的数据，如有脏数据将被写回到MEMORY

* DCACHE无效

```c
void itcs_dcache_invalid(void)
```

遍历WAY/SET，使DCACHE/L2 CACHE中的数据无效

* DCACHE同步并无效

```c
void itcs_dcache_flush(void)
```

效果等同于先清理dcache_clean，再dcache_invalid

* L2 CACHE无效

```c
void itcs_l2cache_invalid(void)
```

遍历WAY/SET，使L2 CACHE中的数据无效

* L2 CACHE同步

```c
void itcs_l2cache_clean(void)
```

遍历WAY/SET遍历，清理L2 CACHE中的数据，如有脏数据将被写回下一级MEMORY

* L2 CACHE同步并无效

```c
void itcs_l2cache_flush(void)
```

效果等同于先清理l2cache_clean，再l2cache_invalid

* DCACHE按范围同步

```c
void itcs_dcache_clean_range(phy_addr_t start, unsigned long size)
```

在从物理地址start开始，长size字节的范围内，清理所对应的 dcache/l2 cache 表项，操作所有核和 L2CACHE
|参数名|参数说明|
|--|--|
|start|需要清理的起始物理地址|
|size|需要清理的数据大小（字节）|

* DCACHE按范围无效

```c
void itcs_dcache_invalid_range(phy_addr_t start, unsigned long size)
```

在从物理地址start开始，长size字节的范围内，所对应的 dcache/l2 cache 表项无效，操作所有核和 L2CACHE
|参数名|参数说明|
|--|--|
|start|需要无效的起始物理地址|
|size|需要无效的数据大小（字节）|

* DCACHE按范围同步并无效

```c
void itcs_dcache_flush_range(phy_addr_t start, unsigned long size)
```

效果等同于先清理dcache_clean_range，再dcache_invalid_range
|参数名|参数说明|
|--|--|
|start|需要清理的起始物理地址|
|size|需要清理的数据大小（字节|

* MMU配置页表
  
```c
void configure_mmu(void) 
```

 MMU配置页表，并使能MMU

* MMU打开

```c
void mmu_enable(void) 
```

使能MMU

* MMU关闭
  
```c
void mmu_disable(void) 
```

关闭MMU

## 示例代码

```c
#include <mmu_table.h>
#include <cache.h>
#include <malloc.h>
#include <asm/io.h>
int demo_main(int argc, char *argv[])
{
    uint8_t *buf = (uint8_t *)malloc(0x40);

    if (!buf)
        return -1;

    configure_mmu();

    itcs_dcache_enable();
    itcs_dcache_clean();

    itcs_dcache_flush_range(virt_to_phys(buf), 0x40);
    itcs_dcache_disable();
}
```