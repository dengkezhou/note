opensbi

## 1 简介

SBI即为 （RISC-V Supervisor Binary Interface），SBI直接运行在系统M模式，可以作为一个bootloader或一个M模式下运行的后台程序。

openSBI源码：https://github.com/riscv-software-src/opensbi

openSBI的代码组织上，把sbi公共代码抽象出来两个库 lib/sbi、lib/utils，及平台相关代码 platform。



编译：

```makefile
make CROSS_COMPILE=riscv64-unknown-linux-gnu- \
	 PLATFORM=generic \
     FW_FDT_PATH=<device tree path>xxx.dtb \
     FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image 
```

定义FW_FDT_PATH可以将设备树文件编译进opensbi中，

定义FW_PAYLOAD_PATH可以将内核或uboot编译进opensbi中，

实现方式是使用了incbin 命令。



编译最终生成3个文件：

fw_jump.elf         跳到指定地址运行下一个阶段的代码。

fw_load.elf          会把下一个阶段的二进制，通常是Uboot/Linux内核，一起打包到fw_load.elf固件里。

fw_dynamic.elf   定义了上一个程序以及下一个程序和fw_dynamic.elf的接口。

## 2 模式切换

openSBI运行在 M模式，具有最高的权限，当切换为s模式，权限降低，在mret后执行下一行命令会出现异常：Illegal instruction #非法指令。所以在切换模式之前需要对内存做一些权限配置。

参看代码lib/sbi/sbi_hart.c  sbi_hart_pmp_configure

### 2.1 PMP

PMP Physical Memory Protection  物理内存保护。

PMP用于限制hart上软件可以访问的物理地址范围，可以提供安全处理和故障隔离功能。

机器模式是最高权限级别，默认情况下在设备的整个内存映射中具有读取、写入和执行的权限。但监管模式和用户模式对内存没有任何权限，除非PMP特别允许。

通过在M模式下修改每个hart对应的控制寄存器，可以指定每个物理内存区域的读、写、执行等访问权限。此外，PMP机制也可以用于S模式中的页表访问。

违反PMP机制的访问将会触发异常  Illegal instruction。

**PMP控制寄存器**

每一个PMP项定义了一个访问控制区域。每个PMP项包括一个8位控制寄存器和一个地址寄存器，仅在M模式下可访问，处理器最多支持64个PMP项。PMP访问控制驱动大小可设置，最小支持4字节区域。

PMP控制寄存器打包存储在CSR寄存器中，在RV64中，每个寄存器64位，可以覆盖8个PMP控制寄存器，一个有8个寄存器，pmpcfg0 ~pmpcfg15，只使用了偶数编号。（RV32中需要16个寄存器）

PMP控制寄存器包括L A X W R五个字段。RWX表示对应区域的读写执行权限，其中R=0且W=1时表示该内存区域被保留。L用于锁定区域，上锁后对控制寄存器的写入被忽略，只能通过系统复位解锁。A字段用于指定地址区域的计算方式。

| 7    | 6-5  | 4-3  | 2    | 1    | 0    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| L    | 0    | A    | X    | W    | R    |

**PMP地址寄存器**

每个PMP地址寄存器对应一个CSR寄存器，命名为pmpaddr0-pmpaddr63。在RV32中，寄存器存储34位物理地址的2-33位（Sv32分页机制），RV64中，寄存器存储56位物理地址的第2-55位（Sv39或Sv48分页机制）

PMP配置代码

```
 /*lib/sbi/sbi_hart.c  sbi_hart_pmp_configure*/ 
  pmp_flags = 0;
  pmp_flags |= PMP_R;
  pmp_flags |= PMP_W;
  pmp_flags |= PMP_X;
  pmp_flags |= PMP_A_TOR;
  unsigned long order = 64;
  pmp_set(pmp_idx++, pmp_flags, 0x18000000, order);
```

### 2.2 Domain

默认的domain是root，使用全局数组root_memregs描述root的每块内存。

region00表示opensbi 代码段区域，没有分配读写权限。

region01表示了全部地址，整体给了rwx权限。

因为order是2的幂，所以若内存区域大小为7，则order = 3，配置的大小就会是2^3 = 8；

若内存区域有包含的关系，按照最先配置的区域来判定，即opensbi的访问权限是0，若添加一个region02，因为region01包含了所有的地址范围，所以无论region2配置的权限和范围是多少，都不会生效。

```
Domain0 Name              : root
Domain0 Boot HART         : 0
Domain0 HARTs             : 0
Domain0 Region00          : 0x0000000100000000-0x000000010003ffff ()
Domain0 Region01          : 0x0000000000000000-0xffffffffffffffff (R,W,X)
```

在配置PMP时，可以从设备树中获取内存区域的权限和大小。使用的是全局变量ftd_regions。

设备树的写法参考文档 docs/domain_support.md。

在配置PMP前，系统会将root domain中没有读写执行权限的内存区域复制到ftd_regions，用于限制低特权模式，对于上述例子而言，即限制了S模式对opensbi 代码段的访问。

该限制也使得opensbi的内置设备树不能被内核访问，在opensbi执行完成后，会复制fdt到next_arg1的位置。

```c
/* lib/sbi/sbi_domain.c */
//fw_start为起始的内存即opensbi的代码段,称为firmware memory region，配置为root的region00，权限=0 限制其他模式访问。
int sbi_domain_init(struct sbi_scratch *scratch, u32 cold_hartid)
{
	u32 i;
	const struct sbi_platform *plat = sbi_platform_ptr(scratch);

	/* Root domain firmware memory region */
	sbi_domain_memregion_init(scratch->fw_start, scratch->fw_size, 0,    
				  &root_fw_region);                  
    ....      
}

/* lib/utils/fdt/fdt_domain.c */
//将root中限制了访问的内存区域复制到fdt的PMP配置中，保证所有的domain配置中都不能访问该段内存。
//因为区域配置重叠时优先以第一个配置生效，所以后续代码会将该reg放在fdt的region00上，不在此显示了。
static int __fdt_parse_domain(void *fdt, int domain_offset, void *opaque)
{
    ...
        /*
     * Copy over root domain memregions which don't allow
     * read, write and execute from lower privilege modes.
     *
     * These root domain memregions without read, write,
     * and execute permissions include:
     * 1) firmware region protecting the firmware memory
     * 2) mmio regions protecting M-mode only mmio devices
     */
    sbi_domain_for_each_memregion(&root, reg) {
        if ((reg->flags & SBI_DOMAIN_MEMREGION_READABLE) ||
            (reg->flags & SBI_DOMAIN_MEMREGION_WRITEABLE) ||
            (reg->flags & SBI_DOMAIN_MEMREGION_EXECUTABLE))
            continue;
        if (FDT_DOMAIN_REGION_MAX_COUNT <= val32)
            return SBI_EINVAL;
        sbi_memcpy(&regions[val32++], reg, sizeof(*reg));  
    }
    ...
}

/*lib/sbi/sbi_domain.c */
//检查pmp配置中有fireware memory region
static int sanitize_domain(const struct sbi_platform *plat,
			   struct sbi_domain *dom)
{
    .....
	/* Count memory regions and check presence of firmware region */
	count = 0;
	have_fw_reg = FALSE;
	sbi_domain_for_each_memregion(dom, reg) {
		if (reg->order == root_fw_region.order &&
		    reg->base == root_fw_region.base &&
		    reg->flags == root_fw_region.flags)
			have_fw_reg = TRUE;
		count++;
	}
	if (!have_fw_reg) {
		sbi_printf("%s: %s does not have firmware region\n",
			   __func__, dom->name);
		return SBI_EINVAL;
	}
    .......
}
```

所以想要在opensbi源码中写一段打印函数当做跳转地址，需要修改fireware的权限为7（读写执行）；

若是使用了fdt自定义的PMP配置，还需要去除fireware memory检查，或者写一个具有属性的配置。

##  3 openSBI与内核

openSBI可以访问所有的硬件资源，向OS提供了统一的系统调用环境，OS通过特殊的指令进入M模式，并执行SBI的callback。

## 4 程序运行

使用设备树来描述硬件信息，以下程序分析也是根据设备树来进行设备初始化。

使用opensbi v0.9版本的代码

### 4.1 串口

串口在 sbi_init -> init_coldboot -> sbi_console_init中进行串口初始化。

```c
/*lib/sbi/sbi_console.c*/
int sbi_console_init(struct sbi_scratch *scratch)
{
	return sbi_platform_console_init(sbi_platform_ptr(scratch));
}

static inline int sbi_platform_console_init(const struct sbi_platform *plat)
{
	if (plat && sbi_platform_ops(plat)->console_init)
		return sbi_platform_ops(plat)->console_init();
	return 0;
}
```

platform的结构体定义在对应的platform/generic/platform.c中 （在编译过程中指定了PLATFORM=generic，不同平台有不同的目录）

```c
const struct sbi_platform_operations platform_ops = {
    ...
    .console_init       = fdt_serial_init,
    ...
};

struct sbi_platform platform = {
     ...
    .platform_ops_addr  = (unsigned long)&platform_ops
};
```

fdt_serial_init 定义在 lib/utils/serial/fdt_serial.c 中

根据设备树stdout-path指定了设备树串口节点属性匹配opensbi中支持的驱动serial_drivers。

```c
int fdt_serial_init(void)
{
   ...
   /* Find offset of node pointed by stdout-path */
	coff = fdt_path_offset(fdt, "/chosen");
	if (-1 < coff) {
		prop = fdt_getprop(fdt, coff, "stdout-path", &len);
		if (prop && len)
			noff = fdt_path_offset(fdt, prop);
	}
    /* First check DT node pointed by stdout-path */
	for (pos = 0; pos < array_size(serial_drivers) && -1 < noff; pos++) {
		drv = serial_drivers[pos];

		match = fdt_match_node(fdt, noff, drv->match_table);
		if (!match)
			continue;

		if (drv->init) {
			rc = drv->init(fdt, noff, match);
			if (rc)
				return rc;
		}
		current_driver = drv;
		break;
	}
    ....
}
```

serial_drivers是一个数组，保存了已经支持的驱动，若需要支持自定义的串口，需要在此添加一个串口驱动。

在v1.3版本，该变量名称为fdt_serial_drivers，是根据配置生成的一个结构体，需要在lib/utils/serial的objects.mk中添加

```
libsbiutils-objs-$(CONFIG_FDT_SERIAL_INTCHAINS) += serial/fdt_serial_intchains.o
carray-fdt_serial_drivers-$(CONFIG_FDT_SERIAL_INTCHAINS) += fdt_serial_intchains
```

```c
static struct fdt_serial *serial_drivers[] = {
	&fdt_serial_uart8250,
	&fdt_serial_sifive,
	&fdt_serial_htif,
	&fdt_serial_shakti,
};

/* include/sbi_utils/serial/fdt_serial.h */
struct fdt_serial {
	const struct fdt_match *match_table;
	int (*init)(void *fdt, int nodeoff, const struct fdt_match *match);
};
```

init函数需要完成串口的初始化，并设置opensbi使用的串口。

设置串口需要调用 sbi_console_set_device函数，本质是为console_dev 全局变量赋值，sbi_print函数会调用其读写接口进行输入输出。

```c
/* lib/sbi/sbi_console.c */
void sbi_console_set_device(const struct sbi_console_device *dev)
{
	if (!dev || console_dev)
		return;

	console_dev = dev;
}

/* include/sbi/sbi_console.h */
struct sbi_console_device {
	/** Name of the console device */
	char name[32];

	/** Write a character to the console output */
	void (*console_putc)(char ch);

	/** Read a character from the console input */
	int (*console_getc)(void);
};
```

### 4.2 platform 驱动

定义一个 platform driver

```c
static int icg_pmic_final_init(bool cold_boot, const struct fdt_match *match)
{
	if (cold_boot) {

		sbi_printf("-------icg pmic\n");

		/* TODO: probe pmic */
		sbi_system_reset_add_device(&pm_reset);	
	}
	return 0;
}

static const struct fdt_match icg_pmic_match[] = {
	{ .compatible = "thead,icg-evb" },
	{},
};


const struct platform_override icg_pmic = {
	.match_table = icg_pmic_match,
	.final_init = icg_pmic_final_init,
};
```

在 objects.mk 中声明该drv

```makefile
carray-platform_override_modules-$(CONFIG_ICG_PMIC_DEV) += icg_pmic
platform-objs-$(CONFIG_ICG_PMIC_DEV) += icg/icg_pmic.o
```

在 opensbi 编译过程中，所有声明的驱动会查询，并被放入一个数组中, 并在匹配root节点( 只匹配root 节点的属性，且只挂载一个 )。

```c
/* platform/generic/platform.c */

/* List of platform override modules generated at compile time */
extern const struct platform_override *platform_override_modules[];
extern unsigned long platform_override_modules_size;


static void fw_platform_lookup_special(void *fdt, int root_offset)
{
	const struct platform_override *plat;
	const struct fdt_match *match;
	int pos;

	for (pos = 0; pos < platform_override_modules_size; pos++) {
		plat = platform_override_modules[pos];
		if (!plat->match_table)
			continue;

		match = fdt_match_node(fdt, root_offset, plat->match_table);
		if (!match)
			continue;

		generic_plat = plat;
		generic_plat_match = match;
		break;
	}
}
```

### 4.3 其他类型驱动

和 platform driver 的初始化方式一样，如 reste driver，区别在于compatible匹配 可以匹配设备树的所有节点。 

```c
/* List of FDT reset drivers generated at compile time */
extern struct fdt_reset *fdt_reset_drivers[];
extern unsigned long fdt_reset_drivers_size;

int fdt_reset_driver_init(void *fdt, struct fdt_reset *drv)
{
	int noff, rc = SBI_ENODEV;
	const struct fdt_match *match;

	noff = fdt_find_match(fdt, -1, drv->match_table, &match);
	if (noff < 0)
		return SBI_ENODEV;

	if (drv->init) {
		rc = drv->init(fdt, noff, match);
		if (rc && rc != SBI_ENODEV) {
			sbi_printf("%s: %s init failed, %d\n",
				   __func__, match->compatible, rc);
		}
	}

	return rc;
}

void fdt_reset_init(void)
{
	int pos;
	void *fdt = fdt_get_address();

	for (pos = 0; pos < fdt_reset_drivers_size; pos++)
		fdt_reset_driver_init(fdt, fdt_reset_drivers[pos]);
}
```

特别的，若实现了 platform driver， 可以直接在 platform driver init 中调用 fdt_reset_driver_init 去初始化一个reset 驱动。
