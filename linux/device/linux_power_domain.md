# kernel driver

## 1 linux内核驱动加载宏

### 1.1 

Linux内核为不同驱动的加载顺序对应不同的优先级，定义了一些宏：
这些宏位于include/linux/init.h文件中，最终驱动通过使用下面的这些不同的加载宏被放入到不同的段(.section)中，在内核初始化的时候，会调用do_initcalls去处理这些段。

```c
#define ___define_initcall(fn, id, __sec) \
	static initcall_t __initcall_##fn##id __used \
		__attribute__((__section__(#__sec ".init"))) = fn;
#endif

#define __define_initcall(fn, id) ___define_initcall(fn, id, .initcall##id)

/*
 * Early initcalls run before initializing SMP.
 *
 * Only for built-in code, not modules.
 */
#define early_initcall(fn)		__define_initcall(fn, early)

/*
 * A "pure" initcall has no dependencies on anything else, and purely
 * initializes variables that couldn't be statically initialized.
 *
 * This only exists for built-in code, not for modules.
 * Keep main.c:initcall_level_names[] in sync.
 */
#define pure_initcall(fn)		__define_initcall(fn, 0)

#define core_initcall(fn)		__define_initcall(fn, 1)
#define core_initcall_sync(fn)		__define_initcall(fn, 1s)
#define postcore_initcall(fn)		__define_initcall(fn, 2)
#define postcore_initcall_sync(fn)	__define_initcall(fn, 2s)
#define arch_initcall(fn)		__define_initcall(fn, 3)
#define arch_initcall_sync(fn)		__define_initcall(fn, 3s)
#define subsys_initcall(fn)		__define_initcall(fn, 4)
#define subsys_initcall_sync(fn)	__define_initcall(fn, 4s)
#define fs_initcall(fn)			__define_initcall(fn, 5)
#define fs_initcall_sync(fn)		__define_initcall(fn, 5s)
#define rootfs_initcall(fn)		__define_initcall(fn, rootfs)
#define device_initcall(fn)		__define_initcall(fn, 6)
#define device_initcall_sync(fn)	__define_initcall(fn, 6s)
#define late_initcall(fn)		__define_initcall(fn, 7)
#define late_initcall_sync(fn)		__define_initcall(fn, 7s)

#define __initcall(fn) device_initcall(fn)

#define __exitcall(fn)						\
	static exitcall_t __exitcall_##fn __exit_call = fn

#define console_initcall(fn)	___define_initcall(fn,, .con_initcall)
```

### 1.2 __define_initcall

下面重点关注一下__define_initcall的实现：

```c
#define ___define_initcall(fn, id, __sec) \
	static initcall_t __initcall_##fn##id __used \
		__attribute__((__section__(#__sec ".init"))) = fn;
通过__define_initcall(fn, id)宏，依据id将不同的fn放置于不同的段(.section)中。
__attribute__是用于设置函数属性、变量属性以及类型属性；
__attribute__((section("section_name")))其作用是将特定的函数或数据放入指定名为"section_name"的段(.section)中；
“#”的作用是将后面紧跟着的id转换为字符串；“##”则用于连接两个不同的字符。
__attribute__((_used_))的作用是告诉编译器这个静态符号在编译的时候即使没有使用到也要保留这个符号；
__attribute__((__section__(".initcall" #id ".init"))) = fn的作用即为将fn放入定义好的initcalln.init的段中，n代表的是id。
```

## 2 链接脚本中的定义

对于linux内核，链接器所需要处理的链接文件位于arch/arm/kernel/vmlinux.lds.S文件，其对应各段的定义位于include/asm-generic/vmlinux.lds.h文件。
arch/arm/kernel/vmlinux.lds.S文件的.init.data段标识了要将哪些段放入到.init.data段中。我们需要重点关注的是INIT_CALLS 段

```c
✗ 218     .init.data : {
✗ 219         INIT_DATA
✗ 220         INIT_SETUP(16)
✗ 221         INIT_CALLS
✗ 222         CON_INITCALL
✗ 223         SECURITY_INITCALL
✗ 224         INIT_RAM_FS
✗ 225     }
✗ 226     .exit.data : {
✗ 227         ARM_EXIT_KEEP(EXIT_DATA)
✗ 228     }
```

```c
INIT_CALLS 的定义位于include/asm-generic/vmlinux.lds.h文件中，如下代码所示，INIT_CALL段也包含很多不同的段，现在拿INIT_CALLS_LEVEL 为例来说明，INIT_CALLS_LEVEL 段定义为__initcall##level##_start将.initcall##level##.init以及.initcall##level##s.init放入到INIT_CALLS段中。
level对应于在1.2 __define_initcall定义的id
```

```c
  734 #define INIT_SETUP(initsetup_align)                 \ 
  735         . = ALIGN(initsetup_align);             \ 
  736         VMLINUX_SYMBOL(__setup_start) = .;          \ 
  737         KEEP(*(.init.setup))                    \ 
  738         VMLINUX_SYMBOL(__setup_end) = .; 
  739      
  740 #define INIT_CALLS_LEVEL(level)                     \ 
  741         VMLINUX_SYMBOL(__initcall##level##_start) = .;      \ 
  742         KEEP(*(.initcall##level##.init))            \ 
  743         KEEP(*(.initcall##level##s.init))           \ 
  744  
  745 #define INIT_CALLS                          \ 
  746         VMLINUX_SYMBOL(__initcall_start) = .;           \ 
  747         KEEP(*(.initcallearly.init))                \ 
  748         INIT_CALLS_LEVEL(0)                 \ 
  749         INIT_CALLS_LEVEL(1)                 \ 
  750         INIT_CALLS_LEVEL(2)                 \ 
  751         INIT_CALLS_LEVEL(3)                 \ 
  752         INIT_CALLS_LEVEL(4)                 \ 
  753         INIT_CALLS_LEVEL(5)                 \ 
  754         INIT_CALLS_LEVEL(rootfs)                \ 
  755         INIT_CALLS_LEVEL(6)                 \ 
  756         INIT_CALLS_LEVEL(7)                 \                                                                                                                                                           
  757         VMLINUX_SYMBOL(__initcall_end) = .; 
  758          
  759 #define CON_INITCALL                            \ 
  760         VMLINUX_SYMBOL(__con_initcall_start) = .;       \ 
  761         KEEP(*(.con_initcall.init))             \ 
  762         VMLINUX_SYMBOL(__con_initcall_end) = .; 
  763  
  764 #define SECURITY_INITCALL                       \ 
  765         VMLINUX_SYMBOL(__security_initcall_start) = .;      \ 
  766         KEEP(*(.security_initcall.init))            \ 
  767         VMLINUX_SYMBOL(__security_initcall_end) = .; 
  768  
  769 #ifdef CONFIG_BLK_DEV_INITRD 
  770 #define INIT_RAM_FS                         \ 
  771     . = ALIGN(4);                           \ 
  772     VMLINUX_SYMBOL(__initramfs_start) = .;              \ 
  773     KEEP(*(.init.ramfs))                        \ 
  774     . = ALIGN(8);                           \ 
  775     KEEP(*(.init.ramfs.info)) 
  776 #else 
  777 #define INIT_RAM_FS 
  778 #endif
```

## 3 linux内核对initcall的处理流程

下面将分析从start_kernel开始一直到do_initcalls的调用关系。对驱动各模块的加载处理也是在do_initcalls中处理的。

### 3.1 调用关系
所用的这些函数均位于init/main.c文件中

```c
| - start_kernel  ---(init/main.c)
    | - rest_init    ---(init/main.c)
        | - kernel_init   (pid = kernel_thread(kernel_init, NULL, CLONE_FS))   ---(init/main.c)
            | - kernel_init_freeable   ---(init/main.c)
                | - do_basic_setup   ---(init/main.c)
                    | - do_initcalls    ---(init/main.c)
                        | - do_initcall_level
                            | - do_one_initcall

```

### 3.2 do_initcalls
如下所示，do_initcalls调用do_initcall_level进而再调用do_one_initcall去做更具体的处理。initcall_levels 数组中的各个成员均和链接文件(.ld)中的定义是一致的。所有的这些均包含在INITCALLS段中。

```c
   845 extern initcall_t __initcall_start[]; 
   846 extern initcall_t __initcall0_start[]; 
   847 extern initcall_t __initcall1_start[]; 
   848 extern initcall_t __initcall2_start[]; 
   849 extern initcall_t __initcall3_start[]; 
   850 extern initcall_t __initcall4_start[]; 
   851 extern initcall_t __initcall5_start[]; 
   852 extern initcall_t __initcall6_start[]; 
   853 extern initcall_t __initcall7_start[]; 
   854 extern initcall_t __initcall_end[]; 
   855  
   856 static initcall_t *initcall_levels[] __initdata = { 
   857     __initcall0_start,
   858     __initcall1_start,
   859     __initcall2_start,
   860     __initcall3_start,
   861     __initcall4_start,
   862     __initcall5_start,
   863     __initcall6_start,
   864     __initcall7_start,
   865     __initcall_end,
   866 };
   867 
   868 /* Keep these in sync with initcalls in include/linux/init.h */ 
   869 static char *initcall_level_names[] __initdata = { 
   870     "early", 
   871     "core", 
   872     "postcore", 
   873     "arch", 
   874     "subsys", 
   875     "fs", 
   876     "device", 
   877     "late",                                                                                       
   878 };
   879 
   880 static void __init do_initcall_level(int level) 
   881 { 
   882     initcall_t *fn; 
   883  
   884     strcpy(initcall_command_line, saved_command_line); 
   885     parse_args(initcall_level_names[level], 
   886            initcall_command_line, __start___param, 
   887            __stop___param - __start___param, 
   888            level, level, 
   889            NULL, &repair_env_string); 
   890  
   891     for (fn = initcall_levels[level]; fn < initcall_levels[level+1]; fn++) //对各个level驱动初始化，只是init,如果设备树还没有被解析时~
   892         do_one_initcall(*fn); 
   893 } 
   894  
   895 static void __init do_initcalls(void) 
   896 { 
   897     int level;                                               
   898  
   899     for (level = 0; level < ARRAY_SIZE(initcall_levels) - 1; level++) 
   900         do_initcall_level(level); 
   901 }
```

init/main.c中do_one_initcall:

```c
int __init_or_module do_one_initcall(initcall_t fn)
{
	int count = preempt_count();
	char msgbuf[64];
	int ret;

	if (initcall_blacklisted(fn))
		return -EPERM;

	do_trace_initcall_start(fn);
	ret = fn();
	do_trace_initcall_finish(fn, ret);

	msgbuf[0] = 0;

	if (preempt_count() != count) {
		sprintf(msgbuf, "preemption imbalance ");
		preempt_count_set(count);
	}
	if (irqs_disabled()) {
		strlcat(msgbuf, "disabled interrupts ", sizeof(msgbuf));
		local_irq_enable();
	}
	WARN(msgbuf[0], "initcall %pS returned with %s\n", fn, msgbuf);

	add_latent_entropy();
	return ret;
}
```

## 4. 具体样例分析

### 4.1 module_init分析
module_init的宏定义位于drivers/staging/lustre/lustre/include/lustre_compat.h文件中，而module_init会调用到late_initcall宏定义。而late_initcall宏定义参考1.1 linux内核驱动加载宏章的声明，late_initcall

```c
   51 /* 
   52  * OBD need working random driver, thus all our 
   53  * initialization routines must be called after device 
   54  * driver initialization 
   55  */ 
   56 #ifndef MODULE   
   57 #undef module_init 
   58 #define module_init(a)     late_initcall(a) 
   59 #endif
```

### 4.2 builtin_platform_driver 分析

builtin_platform_driver的宏定义位于include/linux/platform_device.h文件中，而builtin_platform_driver会调用到builtin_driver

```c
  231 /* builtin_platform_driver() - Helper macro for builtin drivers that 
  232  * don't do anything special in driver init.  This eliminates some 
  233  * boilerplate.  Each driver may only use this macro once, and 
  234  * calling it replaces device_initcall().  Note this is meant to be 
  235  * a parallel of module_platform_driver() above, but w/o _exit stuff. 
  236  */  
  237 #define builtin_platform_driver(__platform_driver) \ 
  238     builtin_driver(__platform_driver, platform_driver_register)
```

builtin_driver宏定义位于include/linux/device.h文件中，该宏定义会调用到device_initcall宏，而该宏的定义依然是需要参考1.1 linux内核驱动加载宏的声明部分。

```c
  1511 /** 
  1512  * builtin_driver() - Helper macro for drivers that don't do anything 
  1513  * special in init and have no exit. This eliminates some boilerplate. 
  1514  * Each driver may only use this macro once, and calling it replaces 
  1515  * device_initcall (or in some cases, the legacy __initcall).  This is 
  1516  * meant to be a direct parallel of module_driver() above but without 
  1517  * the __exit stuff that is not used for builtin cases. 
  1518  * 
  1519  * @__driver: driver name 
  1520  * @__register: register function for this driver type 
  1521  * @...: Additional arguments to be passed to __register 
  1522  *                                                           
  1523  * Use this macro to construct bus specific macros for registering 
  1524  * drivers, and do not use it on its own. 
  1525  */ 
  1526 #define builtin_driver(__driver, __register, ...) \ 
  1527 static int __init __driver##_init(void) \ 
  1528 { \ 
  1529     return __register(&(__driver) , ##__VA_ARGS__); \   //platform_driver_register(imx_gpc_driver)
  1530 } \ 
  1531 device_initcall(__driver##_init);
```

```c
builtin_platform_driver(imx_gpc_driver)
/*****************************************************************/    
static int __init imx_gpc_driver_init(void)
{
	return platform_driver_register(&imx_gpc_driver);   //platform_driver_register(imx_gpc_driver)
}
device_initcall(imx_gpc_driver_init);
```

也就是do_one_init会调用这个函数

---

PS：虽然宏本身不是函数，但它可以被用来生成函数定义的代码。这种技术在一些情况下可以简化代码编写。

下面是一个简单的示例，展示了如何在宏中定义多行代码：

```c#define PRINT_HELLO() \
#define PRINT_HELLO() \
do { \
        printf("Hello, "); \
        printf("World!\n"); \
    } while(0)
在这个示例中，PRINT_HELLO() 宏定义了一个多行代码块，用于打印 "Hello, World!"。在宏展开时，这个多行代码块会被替换到代码中。
```

需要注意的是，在定义多行代码的宏时，通常会使用 do { ... } while(0) 结构来确保多行代码在展开时能够被当做一个整体使用，避免出现意外的问题。

---

也就是说，builtin_platform_driver比module_init高一个level

```c
#define platform_driver_register(drv) \
	__platform_driver_register(drv, THIS_MODULE)
extern int __platform_driver_register(struct platform_driver *,
					struct module *);
```

drivers/base/paltform.c

```c
/**
 * __platform_driver_register - register a driver for platform-level devices
 * @drv: platform driver structure
 * @owner: owning module/driver
 */
int __platform_driver_register(struct platform_driver *drv,
				struct module *owner)
{
	drv->driver.owner = owner;
	drv->driver.bus = &platform_bus_type;
	drv->driver.probe = platform_drv_probe;
	drv->driver.remove = platform_drv_remove;
	drv->driver.shutdown = platform_drv_shutdown;

	return driver_register(&drv->driver);
}
EXPORT_SYMBOL_GPL(__platform_driver_register);
```

drv是在驱动中写的，代码比如：

```c
static struct platform_driver icg_pm_domains_driver = {
	.probe = icg_pm_domain_probe,
	.driver = {
		.name = "icg_pm_domains",
		.of_match_table = icg_pm_domain_matches,
	},
};
```



drivers/base/driver.c

```c
int driver_register(struct device_driver *drv)
{
	int ret;
	struct device_driver *other;

	if (!drv->bus->p) {
		pr_err("Driver '%s' was unable to register with bus_type '%s' because the bus was not initialized.\n",
			   drv->name, drv->bus->name);
		return -EINVAL;
	}

	if ((drv->bus->probe && drv->probe) ||
	    (drv->bus->remove && drv->remove) ||
	    (drv->bus->shutdown && drv->shutdown))
		pr_warn("Driver '%s' needs updating - please use "
			"bus_type methods\n", drv->name);

	other = driver_find(drv->name, drv->bus);
	if (other) {
		pr_err("Error: Driver '%s' is already registered, "
			"aborting...\n", drv->name);
		return -EBUSY;
	}

	ret = bus_add_driver(drv); //该函数遍历该总线类型上已经注册的所有设备，尝试将这些设备与新注册的驱动进行匹配。
	if (ret)
		return ret;
	ret = driver_add_groups(drv, drv->groups);
	if (ret) {
		bus_remove_driver(drv);
		return ret;
	}
	kobject_uevent(&drv->p->kobj, KOBJ_ADD);

	return ret;
}
EXPORT_SYMBOL_GPL(driver_register);
```

在bus_add_driver中实现driver probe:

```c
bus_add_driver  //drivers/base/bus.c
    driver_attach(drv) //drivers/base/dd.c
    	bus_for_each_dev(drv->bus, NULL, drv, __driver_attach); //遍历该总线上所有的device，执行一次__driver_attach()，看能不能将驱动关联(attach)到某个设备上去。
			__driver_attach
               driver_match_device(drv, dev);//调用驱动的总线上的match函数，查看驱动与设备是否匹配，如果设备树还没解析，是没用的,会直接返回0，不再执行下面的函数~
               device_driver_attach
                	driver_probe_device(drv, dev)
                		really_probe(dev, drv)
                				if (dev->pm_domain && dev->pm_domain->activate) {
									ret = dev->pm_domain->activate(dev);
									if (ret)
										goto probe_failed;
								}

								if (dev->bus->probe) {   //(如果bus->probe非空，则调用bus->probe)
									ret = dev->bus->probe(dev);
									if (ret)
									goto probe_failed;
								} else if (drv->probe) {   //调用驱动的probe函数
									ret = drv->probe(dev);  //先pm_domain_attach,然后drv->probe(dev);
									if (ret)
									goto probe_failed;
								}
```

## 5. kernel power domian 分析

### 5.1 如何使用power domain？

power domian的使用方法非常的简单，如果不想去深入分析power domain如何工作的，只想使用kernel提供的方法，那么只需在dts中定义一个power domain节点，同时在驱动中注册该power domain即可

参考：Documentation\devicetree\bindings\power

```c
//DTS中定义power domain节点，这里以内核文档提供的例程
	parent: power-controller@12340000 { 
        compatible = "foo,power-controller";
		reg = <0x12340000 0x1000>;
		#power-domain-cells = <1>;   //这里表明parent节点是一个power domain，也就是内核文档所形容的provider，parent管理它下面挂接着的其它模块，为它们提供电源
     };

	child: power-controller@12341000 { 
        compatible = "foo,power-controller";
		reg = <0x12341000 0x1000>;
		power-domains = <&parent 0>; //这里表明child节点是parent下面的一个模块，它使用parent提供的电源
		#power-domain-cells = <1>; 
     };
```

从上面的dts语法中可以看出，一个系统的电源域从dts中可以很容易就看出来，#power-domain-cells声明该节点是一个power domain，power-domains = <&xxx x>表明该节点属于xxx电源域，<font color = red>那么系统中某个电源域下面有多少个模块就从dts中看有多少个节点引用了该电源域即可</font>。

```c
/**
 * pm_genpd_init - Initialize a gener
 ic I/O PM domain object.
 * @genpd: PM domain object to initialize.
 * @gov: PM domain governor to associate with the domain (may be NULL).
 * @is_off: Initial value of the domain's power_is_off field.
 *
 * Returns 0 on successful initialization, else a negative error code.
 */
int pm_genpd_init(struct generic_pm_domain *genpd,
		  struct dev_power_governor *gov, bool is_off)  //初始化一个 generic_pm_domain 实例
    
    
/**
 * of_genpd_add_provider_onecell() - Register a onecell PM domain provider
 * @np: Device node pointer associated with the PM domain provider.
 * @data: Pointer to the data associated with the PM domain provider.
 */

//下面两个接口都可以用来向内核注册一个power domian
int of_genpd_add_provider_onecell(struct device_node *np,
				  struct genpd_onecell_data *data)     
int of_genpd_add_provider_simple(struct device_node *np,
				  struct generic_pm_domain *genpd)
```

### 5.2 内核实现power domain

#### provider 分析

先来看一个非常重要的数据结构，这个数据结构是内核为device电源管理所抽象出来的回调函数，我们关心最后三个即可，即runtime_pm方法，后面的分析我们会发现设备的suspend和resume最终都调用该结构体下的某个函数。

```c
struct dev_pm_ops {
	int (*prepare)(struct device *dev);
	void (*complete)(struct device *dev);
	int (*suspend)(struct device *dev);
	int (*resume)(struct device *dev);
	int (*freeze)(struct device *dev);
	int (*thaw)(struct device *dev);
	int (*poweroff)(struct device *dev);
	int (*restore)(struct device *dev);
	int (*suspend_late)(struct device *dev);
	int (*resume_early)(struct device *dev);
	int (*freeze_late)(struct device *dev);
	int (*thaw_early)(struct device *dev);
	int (*poweroff_late)(struct device *dev);
	int (*restore_early)(struct device *dev);
	int (*suspend_noirq)(struct device *dev);
	int (*resume_noirq)(struct device *dev);
	int (*freeze_noirq)(struct device *dev);
	int (*thaw_noirq)(struct device *dev);
	int (*poweroff_noirq)(struct device *dev);
	int (*restore_noirq)(struct device *dev);
	int (*runtime_suspend)(struct device *dev);  //runtime suspend函数
	int (*runtime_resume)(struct device *dev);   //runtime resume函数
	int (*runtime_idle)(struct device *dev);     
};
```

前面提到过驱动想要注册一个power domain只需要两个函数即可，那么分析power domain就从这两个函数入手吧。

pm_genpd_init这个函数从注释可以看出它初始化了一个power domain实例，从入口参数结合具体的实现代码，可以很容易得到struct generic_pm_domain结构体就对应着一个power domain实例。

```c
struct generic_pm_domain {
	struct dev_pm_domain domain;	/* PM domain operations */
	struct list_head gpd_list_node;	/* Node in the global PM domains list */
	struct list_head master_links;	/* Links with PM domain as a master */
	struct list_head slave_links;	/* Links with PM domain as a slave */
	struct list_head dev_list;	/* List of devices */
	struct mutex lock;
	struct dev_power_governor *gov;
	struct work_struct power_off_work;
	struct fwnode_handle *provider;	/* Identity of the domain provider */
	bool has_provider;
	const char *name;
	atomic_t sd_count;	/* Number of subdomains with power "on" */
	enum gpd_status status;	/* Current state of the domain */
	unsigned int device_count;	/* Number of devices */
	unsigned int suspended_count;	/* System suspend device counter */
	unsigned int prepared_count;	/* Suspend counter of prepared devices */
	int (*power_off)(struct generic_pm_domain *domain); //驱动只要实现该函数即可
	int (*power_on)(struct generic_pm_domain *domain);  //驱动只要实现该函数即可
	struct gpd_dev_ops dev_ops;
	s64 max_off_time_ns;	/* Maximum allowed "suspended" time. */
	bool max_off_time_changed;
	bool cached_power_down_ok;
	int (*attach_dev)(struct generic_pm_domain *domain,
			  struct device *dev);
	void (*detach_dev)(struct generic_pm_domain *domain,
			   struct device *dev);
	unsigned int flags;		/* Bit field of configs for genpd */
	struct genpd_power_state states[GENPD_MAX_NUM_STATES];
	unsigned int state_count; /* number of states */
	unsigned int state_idx; /* state that genpd will go to when off */
};
```

该结构体成员很多，看着很复杂，但是真正需要驱动去赋值的成员只有两个，那就是int (*power_off)(struct generic_pm_domain *domain); 与int (*power_on)(struct generic_pm_domain *domain);，其它的power domain framework已经帮我们做好了，这里我们也可以猜到一个电源域的打开与关闭最终是通过驱动注册的这两个函数操作的，因为该电源域的操作只有编写驱动的工程师才最了解，比如它的寄存器地址、bit位等等。

当驱动得到一个power domain实例后，便可以调用of_genpd_add_provider_simple函数向内核注册一个power domain了，来进入该函数看看，做了哪些事情，看不太懂，但是从入口参数看，传进去了驱动实现的struct generic_pm_domain和power domain的node节点。后续这两个参数应该会有作用。

```c
int of_genpd_add_provider_simple(struct device_node *np,
				 struct generic_pm_domain *genpd)
{
	int ret = -EINVAL;

	if (!np || !genpd)
		return -EINVAL;

	mutex_lock(&gpd_list_lock);

	if (!genpd_present(genpd))
		goto unlock;

	genpd->dev.of_node = np;

	/* Parse genpd OPP table */
	if (genpd->set_performance_state) {
		ret = dev_pm_opp_of_add_table(&genpd->dev);
		if (ret) {
			if (ret != -EPROBE_DEFER)
				dev_err(&genpd->dev, "Failed to add OPP table: %d\n",
					ret);
			goto unlock;
		}

		/*
		 * Save table for faster processing while setting performance
		 * state.
		 */
		genpd->opp_table = dev_pm_opp_get_opp_table(&genpd->dev);
		WARN_ON(IS_ERR(genpd->opp_table));
	}

	ret = genpd_add_provider(np, genpd_xlate_simple, genpd);
	if (ret) {
		if (genpd->set_performance_state) {
			dev_pm_opp_put_opp_table(genpd->opp_table);
			dev_pm_opp_of_remove_table(&genpd->dev);
		}

		goto unlock;
	}

	genpd->provider = &np->fwnode;
	genpd->has_provider = true;

unlock:
	mutex_unlock(&gpd_list_lock);

	return ret;
}
```

#### consumer 分析

consumer只需在dts中声明即可和provider耦合，那要分析如何完成耦合的，就需要consumer被加载的时候开始分析，consumer其实就是一个电源域下的device，device的加载就涉及到platform bus了。

```c
drivers/base/platform.c
    
static int platform_drv_probe(struct device *_dev)
{
	struct platform_driver *drv = to_platform_driver(_dev->driver);
	struct platform_device *dev = to_platform_device(_dev);
	int ret;

	ret = of_clk_set_defaults(_dev->of_node, false);
	if (ret < 0)bus_add_driver
		return ret;

	ret = dev_pm_domain_attach(_dev, true);  //将设备与电源域进行耦合
	...
}


/**
 * genpd_dev_pm_attach - Attach a device to its PM domain using DT.
 * @dev: Device to attach.
 *
 * Parse device's OF node to find a PM domain specifier. If such is found,
 * attaches the device to retrieved pm_domain ops.
 *
 * Both generic and legacy Samsung-specific DT bindings are supported to keep
 * backwards compatibility with existing DTBs.
 *
 * Returns 0 on successfully attached PM domain or negative error code. Note
 * that if a power-domain exists for the device, but it cannot be found or
 * turned on, then return -EPROBE_DEFER to ensure that the device is not
 * probed and to re-try again later.
 */
drivers/base/power/domain.c:
int genpd_dev_pm_attach(struct device *dev)
{
	struct of_phandle_args pd_args;
	struct generic_pm_domain *pd;
	unsigned int i;
	int ret;

	if (!dev->of_node)
		return -ENODEV;

	if (dev->pm_domain)
		return -EEXIST;

	ret = of_parse_phandle_with_args(dev->of_node, "power-domains",
					"#power-domain-cells", 0, &pd_args); //该函数的作用就是解析device引用的power domain节点的所包含的参数，最终赋值给pd_args结构
	if (ret < 0) {
		if (ret != -ENOENT)
			return ret;

		/*
		 * Try legacy Samsung-specific bindings
		 * (for backwards compatibility of DT ABI)
		 */
		pd_args.args_count = 0;
		pd_args.np = of_parse_phandle(dev->of_node,
						"samsung,power-domain", 0);
		if (!pd_args.np)
			return -ENOENT;
	}

	mutex_lock(&gpd_list_lock);
	pd = genpd_get_from_provider(&pd_args);  //根据pd_args结构成员获取provider dts的phandle
	of_node_put(pd_args.np);
	if (IS_ERR(pd)) {
		mutex_unlock(&gpd_list_lock);
		dev_dbg(dev, "%s() failed to find PM domain: %ld\n",
			__func__, PTR_ERR(pd));
		return -EPROBE_DEFER;
	}

	dev_dbg(dev, "adding to PM domain %s\n", pd->name);

	for (i = 1; i < GENPD_RETRY_MAX_MS; i <<= 1) {
		ret = genpd_add_device(pd, dev, NULL);   //给该power domain添加设备信息
		if (ret != -EAGAIN)
			break;

		mdelay(i);
		cond_resched();
	}
	mutex_unlock(&gpd_list_lock);

	if (ret < 0) {
		dev_err(dev, "failed to add to PM domain %s: %d",
			pd->name, ret);
		goto out;
	}

	dev->pm_domain->detach = genpd_dev_pm_detach;  //一些初始化过程
	dev->pm_domain->sync = genpd_dev_pm_sync;     //一些初始化过程

	mutex_lock(&pd->lock);
	ret = genpd_power_on(pd, 0);   //power domain 上电！！！！！    struct generic_pm_domain *pd
	mutex_unlock(&pd->lock);
out:
	return ret ? -EPROBE_DEFER : 0;
}

static int genpd_add_device(struct generic_pm_domain *genpd, struct device *dev,
			    struct gpd_timing_data *td)
{
	struct generic_pm_domain_data *gpd_data;
	int ret = 0;

	dev_dbg(dev, "%s()\n", __func__);

	if (IS_ERR_OR_NULL(genpd) || IS_ERR_OR_NULL(dev))
		return -EINVAL;

	gpd_data = genpd_alloc_dev_data(dev, genpd, td);
	if (IS_ERR(gpd_data))
		return PTR_ERR(gpd_data);

	mutex_lock(&genpd->lock);

	if (genpd->prepared_count > 0) {
		ret = -EAGAIN;
		goto out;
	}

	ret = genpd->attach_dev ? genpd->attach_dev(genpd, dev) : 0;
	if (ret)
		goto out;

	genpd->device_count++;
	genpd->max_off_time_changed = true;

	list_add_tail(&gpd_data->base.list_node, &genpd->dev_list);

 out:
	mutex_unlock(&genpd->lock);

	if (ret)
		genpd_free_dev_data(dev, gpd_data);
	else
		dev_pm_qos_add_notifier(dev, &gpd_data->nb);

	return ret;
}

static struct generic_pm_domain_data *genpd_alloc_dev_data(struct device *dev,
					struct generic_pm_domain *genpd,
					struct gpd_timing_data *td)
{
	struct generic_pm_domain_data *gpd_data;
	int ret;

	ret = dev_pm_get_subsys_data(dev);
	if (ret)
		return ERR_PTR(ret);

	gpd_data = kzalloc(sizeof(*gpd_data), GFP_KERNEL);
	if (!gpd_data) {
		ret = -ENOMEM;
		goto err_put;
	}

	if (td)
		gpd_data->td = *td;

	gpd_data->base.dev = dev;
	gpd_data->td.constraint_changed = true;
	gpd_data->td.effective_constraint_ns = -1;
	gpd_data->nb.notifier_call = genpd_dev_pm_qos_notifier;

	spin_lock_irq(&dev->power.lock);

	if (dev->power.subsys_data->domain_data) {
		ret = -EINVAL;
		goto err_free;
	}

	dev->power.subsys_data->domain_data = &gpd_data->base;

	spin_unlock_irq(&dev->power.lock);

	dev_pm_domain_set(dev, &genpd->domain);  //重点来啦，设置了struct device的struct dev_pm_domain *pm_domain成员

	return gpd_data;

 err_free:
	spin_unlock_irq(&dev->power.lock);
	kfree(gpd_data);
 err_put:
	dev_pm_put_subsys_data(dev);
	return ERR_PTR(ret);
}
```

贴出来了这么多代码，可见consumer的分析确实蛮复杂，接下来做个总结：

1. 驱动在probe的时候会调用dev_pm_domain_attach函数检查设备是否属于power domain设备，如果是，则获取设备的power domain信息，从哪里获取信息？就是从前面power domain驱动调用of_genpd_add_provider_simple函数注册进来的信息
2. 调用genpd_add_device函数，将设备添加到该power domain中，主要完成一些struct generic_pm_domain成员的赋值操作
3. 最后最重要的就是调用dev_pm_domain_set该函数，设置了struct device中的struct dev_pm_domain成员，该成员被赋值为struct generic_pm_domain中的struct dev_pm_domain成员

下面再介绍一个对power domain很重要的结构体，那就是struct dev_pm_domain

```c
/*
 * Power domains provide callbacks that are executed during system suspend,
 * hibernation, system resume and during runtime PM transitions along with
 * subsystem-level and driver-level callbacks.
 *
 * @detach: Called when removing a device from the domain.
 * @activate: Called before executing probe routines for bus types and drivers.
 * @sync: Called after successful driver probe.
 * @dismiss: Called after unsuccessful driver probe and after driver removal.
 */
struct dev_pm_domain {
	struct dev_pm_ops	ops;  //有没有发现，这个结构体嵌入了设备power manage的结构体
	void (*detach)(struct device *dev, bool power_off);
	int (*activate)(struct device *dev);
	void (*sync)(struct device *dev);
	void (*dismiss)(struct device *dev);
};
```

该结构体最重要的就是嵌入了struct dev_pm_ops结构体，该结构体是设备低功耗的具体操作函数.

我们再来看看pm_genpd_init函数里具体的实现

```c
int pm_genpd_init(struct generic_pm_domain *genpd,
		  struct dev_power_governor *gov, bool is_off)
{
	......
        
	genpd->domain.ops.runtime_suspend = genpd_runtime_suspend;
	genpd->domain.ops.runtime_resume = genpd_runtime_resume;
	genpd->domain.ops.prepare = pm_genpd_prepare;
	genpd->domain.ops.suspend_noirq = pm_genpd_suspend_noirq;
	genpd->domain.ops.resume_noirq = pm_genpd_resume_noirq;
	genpd->domain.ops.freeze_noirq = pm_genpd_freeze_noirq;
	genpd->domain.ops.thaw_noirq = pm_genpd_thaw_noirq;
	genpd->domain.ops.poweroff_noirq = pm_genpd_suspend_noirq;
	genpd->domain.ops.restore_noirq = pm_genpd_restore_noirq;
	genpd->domain.ops.complete = pm_genpd_complete;

	......
}
```

关注重点，power domain framework在初始化一个struct generic_pm_domain实例的时候，dev_pm_domain下的dev_pm_ops被初始化为power domain特有的函数，即设备属于power domain时，设备在发起suspend和resume流程时，都是调用到power domain的genpd_runtime_suspend和genpd_runtime_resume函数

这也是很好理解的，因为设备一旦属于一个power domain，设备发起suspend和resume必须要让power domain framework感知到，这样它才能知道每个power domain下的设备当前状态，才能在合适的时机去调用provider的power on和power off函数!但是设备具体的suspend和resume肯定还是驱动自己编写，只有驱动对自己的设备最熟悉，其实可以猜到genpd_runtime_suspend函数只是完成一些power domain framework的一些逻辑，最终还是要调用到设备自己的suspend函数，可以看看代码验证一下猜想。
```c
static int genpd_runtime_resume(struct device *dev)
{
	struct generic_pm_domain *genpd;
	struct gpd_timing_data *td = &dev_gpd_data(dev)->td;
	bool runtime_pm = pm_runtime_enabled(dev);
	ktime_t time_start;
	s64 elapsed_ns;
	int ret;
	bool timed = true;

	dev_dbg(dev, "%s()\n", __func__);

	genpd = dev_to_genpd(dev);
	if (IS_ERR(genpd))
		return -EINVAL;

	/*
	 * As we don't power off a non IRQ safe domain, which holds
	 * an IRQ safe device, we don't need to restore power to it.
	 */
	if (irq_safe_dev_in_no_sleep_domain(dev, genpd)) {
		timed = false;
		goto out;
	}

	genpd_lock(genpd);
	ret = genpd_power_on(genpd, 0);
	genpd_unlock(genpd);

	if (ret)
		return ret;

 out:
	/* Measure resume latency. */
	time_start = 0;
	if (timed && runtime_pm)
		time_start = ktime_get();

	ret = genpd_start_dev(genpd, dev);
	if (ret)
		goto err_poweroff;

	ret = __genpd_runtime_resume(dev);
	if (ret)
		goto err_stop;

	/* Update resume latency value if the measured time exceeds it. */
	if (timed && runtime_pm) {
		elapsed_ns = ktime_to_ns(ktime_sub(ktime_get(), time_start));
		if (elapsed_ns > td->resume_latency_ns) {
			td->resume_latency_ns = elapsed_ns;
			dev_dbg(dev, "resume latency exceeded, %lld ns\n",
				elapsed_ns);
			genpd->max_off_time_changed = true;
			td->constraint_changed = true;
		}
	}

	return 0;

err_stop:
	genpd_stop_dev(genpd, dev);
err_poweroff:
	if (!pm_runtime_is_irq_safe(dev) ||
		(pm_runtime_is_irq_safe(dev) && genpd_is_irq_safe(genpd))) {
		genpd_lock(genpd);
		genpd_power_off(genpd, true, 0);
		genpd_unlock(genpd);
	}

	return ret;
}


static int __genpd_runtime_resume(struct device *dev)
{
	int (*cb)(struct device *__dev);

	if (dev->type && dev->type->pm)
		cb = dev->type->pm->runtime_resume;
	else if (dev->class && dev->class->pm)
		cb = dev->class->pm->runtime_resume;
	else if (dev->bus && dev->bus->pm)
		cb = dev->bus->pm->runtime_resume;
	else
		cb = NULL;

	if (!cb && dev->driver && dev->driver->pm)
		cb = dev->driver->pm->runtime_resume;

	return cb ? cb(dev) : 0;
}
```

这里验证了本人的猜想，genpd_runtime_suspend函数最终调用了__genpd_runtime_suspend函数，而该函数的作用就是取具体的设备低功耗操作函数，对于platform设备，dev->bus及dev->bus->pm为真，**所以最终cb应该是cb = dev->bus->pm->runtime_suspend，**

这个时候有些朋友可能会有疑问，设备驱动似乎并没有去初始化dev->bus->pm->runtime_suspend函数呀。是的，驱动没有做，但是内核帮我们做了呀~哈哈，来看看代码。
```c
int __platform_driver_register(struct platform_driver *drv,
				struct module *owner)
{
	drv->driver.owner = owner;
	drv->driver.bus = &platform_bus_type;
	drv->driver.probe = platform_drv_probe;
	drv->driver.remove = platform_drv_remove;
	drv->driver.shutdown = platform_drv_shutdown;

	return driver_register(&drv->driver);
}

struct bus_type platform_bus_type = {
	.name		= "platform",
	.dev_groups	= platform_dev_groups,
	.match		= platform_match,
	.uevent		= platform_uevent,
	.pm		= &platform_dev_pm_ops,
};

static const struct dev_pm_ops platform_dev_pm_ops = {
	.runtime_suspend = pm_generic_runtime_suspend,
	.runtime_resume = pm_generic_runtime_resume,
	USE_PLATFORM_PM_SLEEP_OPS
};

int pm_generic_runtime_suspend(struct device *dev)
{
	const struct dev_pm_ops *pm = dev->driver ? dev->driver->pm : NULL;
	int ret;

	ret = pm && pm->runtime_suspend ? pm->runtime_suspend(dev) : 0;

	return ret;
}
```

本人对platform的理解还不够深刻，这里就不深入分析platform了，但是从代码中可以看出，platform driver在注册的时候，会传入platform_bus_type结构体，该结构体dev_pm_ops成员被赋值为platform_dev_pm_ops结构体，该结构体实现了platform具体的suspend和resume操作，pm_generic_runtime_suspend该函数呢，最终调用的是dev->driver->pm中的实现方法，也就是驱动实现的runtime suspend和runtime resume！！！

写到这里，我似乎又多了一点理解，不管是platform bus还是power domain，他们的dev_pm_ops结构体的实现都没有具体的suspend和resume，它们只决定去哪里或者dev_pm_ops，具体的实现还是device driver。只不过power domain相对于platform bus更上层，power domain可以从dev bus、dev type、dev class那里获取dev_pm_ops，而platform则只能从device driver获取具体的实现函数。

linux/include/linux/pm_domain.h:

struct genpd_onecell_data {
	struct generic_pm_domain **domains;
	unsigned int num_domains;
	genpd_xlate_t xlate;
};















