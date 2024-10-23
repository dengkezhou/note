内核启动（riscv）

### 1 启动时参数

```
a0 : hart id
a1 : DTB physical address
```

### 2 setup_vm 初始化页表

```
参数  a0 = a1 (DTB的物理地址)
表大小 map_size 2M
虚拟地址与物理地址的偏移 va_pa_offset = PAGE_OFFSET - &_start  = 0， 即使用对等映射。
```

使用fpga启动内核时，gdb加载设备树文件到地址 0x104000000，在setup_vm之前需要给a1赋值为0x104000000，

setup_vm中计算设备树的虚拟地址，得到结果即 DTB_EARLY_BASE_VA，和实际地址不匹配，所以需要定义 DTB_EARLY_BASE_VA 为0x104000000 。（宏位于文件 arch/riscv/mm/init.c）

```
dtb_early_va = (void *)DTB_EARLY_BASE_VA + (dtb_pa & (PMD_SIZE - 1));
```

### 3 分析设备树

start_kernel -> setup_arch -> parse_dtb 中分析设备树文件。

从 dtb_early_va 中读取设备树文件，并设置 cpu 、memory 等参数。

### 4 内存管理

### 4.1 早期内存管理

####  memblock 

全局变量memblock定义在 mm/memblock.c 中

struct memblock memblock __initdata_memblock = { ...}

```
/**
 * struct memblock - memblock allocator metadata
 * @bottom_up: is bottom up direction?
 * @current_limit: physical address of the current allocation limit
 * @memory: usable memory regions
 * @reserved: reserved memory regions
 */
struct memblock {
    bool bottom_up;  /* is bottom up direction? */
    phys_addr_t current_limit;
    struct memblock_type memory;            /*可使用的内存*/
    struct memblock_type reserved;          /*保留的内存，如代码段、dtb空间*/
};

/**
 * struct memblock_type - collection of memory regions of certain type
 * @cnt: number of regions
 * @max: size of the allocated array
 * @total_size: size of all regions
 * @regions: array of regions
 * @name: the memory type symbolic name
 */
struct memblock_type {
    unsigned long cnt;
    unsigned long max;
    phys_addr_t total_size;
    struct memblock_region *regions;
    char *name;
};
```

#### page 

page的计算方式，使用后SPARSEMEM_VMEMMAP方式

```
struct page *page = pfn_to_page (pfn)
```

pfn是物理页帧，对应页的物理地址

```
pfn = phys_addr / PAGE_SIZE
```

pfn_to_page 是一个宏定义，主要由vmalloc 和 vmemmap两组宏定义计算( )

```C
//include/asm-generic/memory_model.h

#elif defined(CONFIG_SPARSEMEM_VMEMMAP)
/* memmap is virtually contiguous.  */
#define __pfn_to_page(pfn)	(vmemmap + (pfn))
#define __page_to_pfn(page)	(unsigned long)((page) - vmemmap)

//arch/riscv/include/asm/pgtable.h
#ifdef CONFIG_MMU
#define vmemmap     ((struct page *)VMEMMAP_START)
#define VMEMMAP_START   (VMALLOC_START - VMEMMAP_SIZE)
#define VMEMMAP_SIZE    BIT(VMEMMAP_SHIFT)
#define VMEMMAP_SHIFT  (CONFIG_VA_BITS - PAGE_SHIFT - 1 + STRUCT_PAGE_MAX_SHIFT)

#define VMALLOC_START    (PAGE_OFFSET - VMALLOC_SIZE)
#define VMALLOC_SIZE     (KERN_VIRT_SIZE >> 1)
#define KERN_VIRT_SIZE   (-PAGE_OFFSET)

//其他
#define BIT(nr)			(UL(1) << (nr))
config VA_BITS
    int
    default 32 if 32BIT
    default 39 if 64BIT
#define PAGE_SHIFT	12
#define STRUCT_PAGE_MAX_SHIFT	(order_base_2(sizeof(struct page)))  
//order_base_2(n) 计算为log2 n 向上取整，特别的 ob2(0) = 0 
```

```

```

