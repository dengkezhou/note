

uboot

## 一、设备树

FDT，flatted device tree，扁平设备树，uboot通过解析设备树dtb文件来获取板级设备信息。

可以参考 doc/README.fdt-control。

dtb可以以两种形式编译到Uboot镜像中，第一，使能CONFIG_OF_SEPARATE,uboot会先生成uboot的bin文件，再生成dtb文件，最后将dtb文件追加到uboot bin文件的末尾，通过bin文件结束地址_ end获取设备树地址。第二，使能CONFIG_OF_EMBED，将dtb放到uboot指定的.dtb.init.rodata段中，通过_dtb_dt_begin符号获取设备树地址。

设备树源文件存放在 arch/ARCH/dts下，通过修改Kconfig 和 Makefile来添加设备树。

1.1  设备树分析

在文件 common/board_f.c init_sequence_f的数组中定义了fdt的解析函数 fdtdec_setup，获取设备树的起始地址，分析设备树的合法性(检查头部信息)。

设备树常用接口在lib/fdtdec.c 和 lib/fdtdec_common.c中

```c
/*获取dtb下某个节点的偏移*/
int fdt_path_offset(const void *fdt, const char *path);
/*获取节点的某个字符串属性*/
const void *fdt_getprop(const void *fdt, int nodeoffset, const char *name, int *lenp);
......
```

## 二、驱动模型

dm , driver model 驱动模型为uboot驱动的定义和访问提供了统一的方法，提高了驱动之间的兼容性以及访问的标准型。

可以参考文档 doc/driver-model/README.txt.

### 2.1 dm 架构

uboot DM主要有四个组成部分，

udevice 指设备对象；

driver 设备对象的驱动，和底层设备通信，并为上层提供接口；

uclass 设备类，使用相同方式的操作集的device的类，是一种抽象，为使用相同接口的设备提供了统一的接口，一个uclass 可以对应多个实例的udevice对象。

uclass_driver 对应uclass的驱动程序，提供uclass的操作。

以串口为例，调用关系如图：

![img](./typora-uboot/uboot-dm-1)

结合上图来看：

上层接口都是和uclass的接口直接通讯。
uclass可以理解为一些具有相同属性的udevice对外操作的接口，uclass的驱动是uclass_driver，主要为上层提供接口。
udevice的是指具体设备的抽象，对应驱动是driver，driver主要负责和硬件通信，为uclass提供实际的操作集。
udevice找到对应的uclass的方式主要是通过：udevice对应的driver的id和uclass对应的uclass_driver的id是否匹配。
udevice会和uclass绑定。driver会和udevice绑定。uclass_driver会和uclass绑定。

uclass和udevice都是动态生成的。在解析fdt中的设备的时候，会动态生成udevice。然后找到udevice对应的driver，通过driver中的uclass id得到uclass_driver id。从uclass链表中查找对应的uclass是否已经生成，没有生成的话则动态生成uclass。

### 2.2 dm数据结构

gd 中dm相关部分

```c
 typedef struct global_data {
#ifdef CONFIG_DM
    struct udevice  *dm_root;   /* Root instance for Driver Model */
// DM中的根设备，也是uboot中第一个创建的udevice，也就对应了dts里的根节点。
    struct udevice  *dm_root_f; /* Pre-relocation root instance */
// 在relocation之前DM中的根设备
    struct list_head uclass_root;   /* Head of core tree */
// uclass链表，所有被udevice匹配的uclass都会被挂载到这个链表上
#endif
} gd_t;
```

uclass id, 每一种设备都有对应的uclass id，定义在 include/dm/uclass-id.h中，uclass_deiver 和 driver通过该id匹配。

```c
enum uclass_id {
    /* These are used internally by driver model */
    UCLASS_ROOT = 0,
    UCLASS_DEMO,
    UCLASS_CLK,     /* Clock source, e.g. used by peripherals */
    UCLASS_PINCTRL,     /* Pinctrl (pin muxing/configuration) device */
    UCLASS_SERIAL,      /* Serial UART */
}
```

uclass是uboot自动生成的，有对应的uclass driver 并被udevice匹配成功的uclass会调用uclass_add函数创建，生成的uclass会被噶在到gd->uclass_root的链表上。

通过遍历uclass的链表，匹配uclass id来获取相应的uclass。

```c
struct uclass {
    void *priv;  // uclass的私有数据指针
    struct uclass_driver *uc_drv; // 对应的uclass driver
    struct list_head dev_head; // 链表头，连接所属的所有udevice
    struct list_head sibling_node; // 链表节点，用于把uclass连接到uclass_root链表上
};
```

uclass_driver, 可以使用宏UCLASS_DRIVER 定义一个uclass_dirver全局变量，改变了会被展开为 _u_boot_list_2_uclass_2_serial，保存在 _u_boot_list_2_uclass_2_serial段中，通过该宏定义的段顺序排在一起，形成一个表，简称uclass_driver table。

uclass自动生成后会将对应的uclass_dirver 绑定到 uclass.uc_drv指针上。

```c
/*include/dm/uclass.h*/
struct uclass_driver {
    const char *name; // 该uclass_driver的命令
    enum uclass_id id; // 对应的uclass id
    ...;
    void *ops;
}

UCLASS_DRIVER(serial) = {
    .id        = UCLASS_SERIAL,
    .name        = "serial",
    .flags        = DM_UC_FLAG_SEQ_ALIAS,   
    .post_probe    = serial_post_probe,
    .pre_remove    = serial_pre_remove,
    .per_device_auto_alloc_size = sizeof(struct serial_dev_priv),
};
```

udevice ,在dtb存在的情况下，由uboot解析dtb后动态生成，保存在对应的uclass.dev_head链表中，遍历该链表匹配设备名，可以找到对应的udevice。

```c
/*include/dm/device.h*/
struct udevice {
    const struct driver *driver; // 该udevice对应的driver
    const char *name; // 设备名
    void *platdata; // 该udevice的平台数据
    void *parent_platdata; // 提供给父设备使用的平台数据
    void *uclass_platdata; // 提供给所属uclass使用的平台数据
    int of_offset; // 该udevice的dtb节点偏移，代表了dtb里面的这个节点node
    ulong driver_data; // 驱动数据
    struct udevice *parent; // 父设备
    void *priv; // 私有数据的指针
    struct uclass *uclass; // 所属uclass
    void *uclass_priv; // 提供给所属uclass使用的私有数据指针
    void *parent_priv; // 提供给其父设备使用的私有数据指针
    struct list_head uclass_node; // 用于连接到其所属uclass的链表上
    struct list_head child_head; // 链表头，连接其子设备
    struct list_head sibling_node; // 用于连接到其父设备的链表上
    uint32_t flags; // 标识
    int req_seq;
    int seq;
#ifdef CONFIG_DEVRES
    struct list_head devres_head;
#endif
};
```

driver 和uclass_driver的方式是类似的，通过宏U_BOOT_DRIVER定义一个driver,得到一个全局变量struct driver _u_boot_list_2_driver_2_serial_s5p，所有的driver最终也会形成一个driver table。

在device初始化时，将driver绑定到对应的udevice.driver指针上。

```c
U_BOOT_DRIVER(serial_s5p) = {
    .name    = "serial_s5p",
    .id    = UCLASS_SERIAL,
    .of_match = s5p_serial_ids,
    .ofdata_to_platdata = s5p_serial_ofdata_to_platdata,
    .platdata_auto_alloc_size = sizeof(struct s5p_serial_platdata),
    .probe = s5p_serial_probe,
    .ops    = &s5p_serial_ops,
    .flags = DM_FLAG_PRE_RELOC,
};
```

设备的描述：uboot可以通过两种方式来添加设备，1-直接定义平台设备udevice结构体（除了root节点一般不使用），2-在设备树上添加设备信息，最终被uboot解析为udevice结构。

### 2.3 dm初始化

DM的初始化即对设备信息的描述，主要包括：1-创建根设备root的udevice，存放在gd->dm_root中，初始化uclass链表 gd->uclass_root，2-解析设备树，创建udevice、uclass，绑定对应的driver，uclass_driver ,  绑定udevice和uclass，调用部分driver函数进行初始化。

dm初始化的接口在 initf_dm、initr_dm中，调用函数dm_init_and_scan对DM进行初始化，设备树节点中有一个"uboot,dm_pre-reloc"属性，如果定义则表示这设备是否需要在relocalte之前调用，传递给dm_init_and_scan的参数为ture时，只会初始化有该属性的设备。

```c
static int initf_dm(void)
{
#if defined(CONFIG_DM) && defined(CONFIG_SYS_MALLOC_F_LEN)
    int ret;
    ret = dm_init_and_scan(true); // 调用dm_init_and_scan对DM进行初始化和设备的解析
    if (ret)
        return ret;
#endif
    return 0;
}

#ifdef CONFIG_DM
static int initr_dm(void)
{
    int ret;
    /* Save the pre-reloc driver model and start a new one */
    gd->dm_root_f = gd->dm_root; // 存储relocate之前的根设备
    gd->dm_root = NULL;
    ret = dm_init_and_scan(false); // 调用dm_init_and_scan对DM进行初始化和设备的解析
    if (ret)
        return ret;
    return 0;
}
#endif

/*driver/core/root.c*/
int dm_init_and_scan(bool pre_reloc_only)
{
    int ret;

    ret = dm_init();    // DM的初始化
    if (ret) {
        debug("dm_init() failed: %d\n", ret);
        return ret;
    }
    ret = dm_scan_platdata(pre_reloc_only); //  从平台设备中解析udevice和uclass
    if (ret) {
        debug("dm_scan_platdata() failed: %d\n", ret);
        return ret;
    }

    if (CONFIG_IS_ENABLED(OF_CONTROL)) {
        ret = dm_scan_fdt(gd->fdt_blob, pre_reloc_only); // 从dtb中解析udevice和uclass
        if (ret) {
            debug("dm_scan_fdt() failed: %d\n", ret);
            return ret;
        }
    }

    ret = dm_scan_other(pre_reloc_only);
    if (ret)
        return ret;

    return 0;
}
```

dm_init会创建根设备root的udevice，存放在gd->dm_root中，初始化uclass链表gd->uclass_root。

dm_scan_fdt会从设备树中解析udevice 和 uclass

```c

int dm_scan_fdt(const void *blob, bool pre_reloc_only)
// 此时传进来的参数blob=gd->fdt_blob， pre_reloc_only=0
{
    return dm_scan_fdt_node(gd->dm_root, blob, 0, pre_reloc_only);
// 直接调用dm_scan_fdt_node
}

int dm_scan_fdt_node(struct udevice *parent, const void *blob, int offset,
             bool pre_reloc_only)
// 此时传进来的参数
// parent=gd->dm_root，表示以root设备作为父设备开始解析
// blob=gd->fdt_blob，指定了对应的dtb
// offset=0，从偏移0的节点开始扫描
// pre_reloc_only=0，不只是解析relotion之前的设备
{
    int ret = 0, err;

        /*  以下步骤相当于是遍历每一个dts节点并且调用lists_bind_fdt对其进行解析 */

    for (offset = fdt_first_subnode(blob, offset);
        // 获得blob设备树的offset偏移下的节点的第一个子节点
         offset > 0;
         offset = fdt_next_subnode(blob, offset)) {
               // 循环查找下一个子节点
        if (!fdtdec_get_is_enabled(blob, offset)) {
                        // 判断节点状态是否是disable，如果是的话直接忽略
            dm_dbg("   - ignoring disabled device\n");
            continue;
        }
        err = lists_bind_fdt(parent, blob, offset, NULL);
                // 解析绑定这个节点，dm_scan_fdt的核心，下面具体分析
        if (err && !ret) {
            ret = err;
            debug("%s: ret=%d\n", fdt_get_name(blob, offset, NULL),
                  ret);
        }
    }
    return ret;
}
```

**lists_bind_fdt是从dtb中解析udevice和uclass的核心**。

```c
/*driver/core/lists.c*/
int lists_bind_fdt(struct udevice *parent, const void *blob, int offset,
           struct udevice **devp)
// parent指定了父设备，通过blob和offset可以获得对应的设备的dts节点，对应udevice结构通过devp返回
{
    struct driver *driver = ll_entry_start(struct driver, driver);
// 获取driver table地址
    const int n_ents = ll_entry_count(struct driver, driver);
// 获取driver table长度
    const struct udevice_id *id;
    struct driver *entry;
    struct udevice *dev;
    bool found = false;
    const char *name;
    int result = 0;
    int ret = 0;

    dm_dbg("bind node %s\n", fdt_get_name(blob, offset, NULL));
// 打印当前解析的节点的名称
    if (devp)
        *devp = NULL;
    for (entry = driver; entry != driver + n_ents; entry++) {
// 遍历driver table中的所有driver，具体参考三、4一节
        ret = driver_check_compatible(blob, offset, entry->of_match,
                          &id);
// 判断driver中的compatibile字段和dts节点是否匹配
        name = fdt_get_name(blob, offset, NULL);
// 获取节点名称
        if (ret == -ENOENT) {
            continue;
        } else if (ret == -ENODEV) {
            dm_dbg("Device '%s' has no compatible string\n", name);
            break;
        } else if (ret) {
            dm_warn("Device tree error at offset %d\n", offset);
            result = ret;
            break;
        }

        dm_dbg("   - found match at '%s'\n", entry->name);
        ret = device_bind(parent, entry, name, NULL, offset, &dev);
// 找到对应的driver，调用device_bind进行绑定，会在这个函数中创建对应udevice和uclass并切进行绑定，后面继续说明
        if (ret) {
            dm_warn("Error binding driver '%s': %d\n", entry->name,
                ret);
            return ret;
        } else {
            dev->driver_data = id->data;
            found = true;
            if (devp)
                *devp = dev;
// 将udevice设置到devp指向的地方中，进行返回
        }
        break;
    }

    if (!found && !result && ret != -ENODEV) {
        dm_dbg("No match for node '%s'\n",
               fdt_get_name(blob, offset, NULL));
    }

    return result;
}
```

在device_bind中实现了udevice和uclass的创建和绑定以及一些初始化操作

```c
/*driver/core/device.c*/
int device_bind(struct udevice *parent, const struct driver *drv,
        const char *name, void *platdata, int of_offset,
        struct udevice **devp)
// parent:父设备
// drv：设备对应的driver
// name：设备名称
// platdata：设备的平台数据指针
// of_offset：在dtb中的偏移，即代表了其dts节点
// devp：所创建的udevice的指针，用于返回
{
    struct udevice *dev;
    struct uclass *uc;
    int size, ret = 0;

    ret = uclass_get(drv->id, &uc);
        // 获取driver id对应的uclass，如果uclass原先并不存在，那么会在这里创建uclass并其uclass_driver进行绑定

    dev = calloc(1, sizeof(struct udevice));
        // 分配一个udevice

    dev->platdata = platdata; // 设置udevice的平台数据指针
    dev->name = name; // 设置udevice的name
    dev->of_offset = of_offset; // 设置udevice的dts节点偏移
    dev->parent = parent; // 设置udevice的父设备
    dev->driver = drv;    // 设置udevice的对应的driver，相当于driver和udevice的绑定
    dev->uclass = uc;    // 设置udevice的所属uclass

    dev->seq = -1;
    dev->req_seq = -1;
    if (CONFIG_IS_ENABLED(OF_CONTROL) && CONFIG_IS_ENABLED(DM_SEQ_ALIAS)) {
        /*
         * Some devices, such as a SPI bus, I2C bus and serial ports
         * are numbered using aliases.
         *
         * This is just a 'requested' sequence, and will be
         * resolved (and ->seq updated) when the device is probed.
         */
        if (uc->uc_drv->flags & DM_UC_FLAG_SEQ_ALIAS) {
            if (uc->uc_drv->name && of_offset != -1) {
                fdtdec_get_alias_seq(gd->fdt_blob,
                        uc->uc_drv->name, of_offset,
                        &dev->req_seq);
            }
                    // 设置udevice的alias请求序号
        }
    }

    if (!dev->platdata && drv->platdata_auto_alloc_size) {
        dev->flags |= DM_FLAG_ALLOC_PDATA;
        dev->platdata = calloc(1, drv->platdata_auto_alloc_size);
                // 为udevice分配平台数据的空间，由driver中的platdata_auto_alloc_size决定
    }

    size = uc->uc_drv->per_device_platdata_auto_alloc_size;
    if (size) {
        dev->flags |= DM_FLAG_ALLOC_UCLASS_PDATA;
        dev->uclass_platdata = calloc(1, size);
                // 为udevice分配给其所属uclass使用的平台数据的空间，由所属uclass的driver中的per_device_platdata_auto_alloc_size决定
    }

    /* put dev into parent's successor list */
    if (parent)
        list_add_tail(&dev->sibling_node, &parent->child_head);
        // 添加到父设备的子设备链表中

    ret = uclass_bind_device(dev);
        // uclass和udevice进行绑定，主要是实现了将udevice链接到uclass的设备链表中

    /* if we fail to bind we remove device from successors and free it */
    if (drv->bind) {
        ret = drv->bind(dev);
        // 执行udevice对应driver的bind函数
    }

    if (parent && parent->driver->child_post_bind) {
        ret = parent->driver->child_post_bind(dev);
        // 执行父设备的driver的child_post_bind函数
    }
    if (uc->uc_drv->post_bind) {
        ret = uc->uc_drv->post_bind(dev);
        if (ret)
            goto fail_uclass_post_bind;
        // 执行所属uclass的post_bind函数
    }

    if (devp)
        *devp = dev;
        // 将udevice进行返回

    dev->flags |= DM_FLAG_BOUND;
        // 设置已经绑定的标志
        // 后续可以通过dev->flags & DM_FLAG_ACTIVATED或者device_active宏来判断设备是否已经被激活

    return 0;
}
```

这里只是绑定，即调用了driver的bind函数，但是设备还没有真正激活，即没有调用driver的probe函数。

### 2.4 dm的工作流程

激活一个设备主要是通过device_probe函数

```c
int device_probe(struct udevice *dev)
{
    const struct driver *drv;
    int size = 0;
    int ret;
    int seq;

    if (dev->flags & DM_FLAG_ACTIVATED)
        return 0;
// 表示这个设备已经被激活了

    drv = dev->driver;
    assert(drv);
// 获取这个设备对应的driver

    /* Allocate private data if requested and not reentered */
    if (drv->priv_auto_alloc_size && !dev->priv) {
        dev->priv = alloc_priv(drv->priv_auto_alloc_size, drv->flags);
// 为设备分配私有数据
    }

    /* Allocate private data if requested and not reentered */
    size = dev->uclass->uc_drv->per_device_auto_alloc_size;
    if (size && !dev->uclass_priv) {
        dev->uclass_priv = calloc(1, size);
// 为设备所属uclass分配私有数据
    }

// 这里过滤父设备的probe

    seq = uclass_resolve_seq(dev);
    if (seq < 0) {
        ret = seq;
        goto fail;
    }
    dev->seq = seq;

    dev->flags |= DM_FLAG_ACTIVATED;
// 设置udevice的激活标志

    ret = uclass_pre_probe_device(dev);
// uclass在probe device之前的一些函数的调用

    if (drv->ofdata_to_platdata && dev->of_offset >= 0) {
        ret = drv->ofdata_to_platdata(dev);
// 调用driver中的ofdata_to_platdata将dts信息转化为设备的平台数据
    }

    if (drv->probe) {
        ret = drv->probe(dev);
// 调用driver的probe函数，到这里设备才真正激活了
    }

    ret = uclass_post_probe_device(dev);

    return ret;
}

```

通过uclss来获取一个udevice并且进行probe，有如下接口:

```c
int uclass_get_device(enum uclass_id id, int index, struct udevice **devp)  //通过索引从uclass的设备链表中获取udevice，并且进行probe
int uclass_get_device_by_name(enum uclass_id id, const char *name,
                  struct udevice **devp) //通过设备名从uclass的设备链表中获取udevice，并且进行probe
int uclass_get_device_by_seq(enum uclass_id id, int seq, struct udevice **devp) //通过序号从uclass的设备链表中获取udevice，并且进行probe
int uclass_get_device_by_of_offset(enum uclass_id id, int node,
                   struct udevice **devp) //通过dts节点的偏移从uclass的设备链表中获取udevice，并且进行probe
int uclass_get_device_by_phandle(enum uclass_id id, struct udevice *parent,
                 const char *name, struct udevice **devp) //通过设备的“phandle”属性从uclass的设备链表中获取udevice，并且进行probe
int uclass_first_device(enum uclass_id id, struct udevice **devp) //从uclass的设备链表中获取第一个udevice，并且进行probe
int uclass_next_device(struct udevice **devp) //从uclass的设备链表中获取下一个udevice，并且进行probe
```

这些接口主要是获取设备的方法上有所区别，但是probe设备的方法都是一样的，都是通过调用uclass_get_device_tail->device_probe来probe设备的。 

## 三、dm 问题

### 3.1 设备probe

根据dm初始化流程可知，在uboot重定位之前，分析设备树只创建了有 pre_reloc 标签的uclass、udevice，所以设备 的udevice创建和 probe过程必然发生在重定位之后，即 board_r.c 中的init_r过程。

设备树中定义的控制器在创建uclass、udevice时，会调用driver的bind函数，但不会调用probe函数；控制器设备相当于一个服务器，只有在第一个客户端设备进行初始化时才会调用控制器设备的probe；如gpio_hog_probe_all 时才会进行gpio ctrller的probe。

使设备在重定位之前就创建uclass 和 udevice，可以在driver驱动中添加 .flag = DM_FLAG_PRE_RELOC
