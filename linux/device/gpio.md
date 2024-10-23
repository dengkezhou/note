## 一、概述

gpio- Genral Purpose Input Output，通用输入输出，简称IO口 或 总线扩展器。

gpio口是由引脚、功能寄存器组成，可以允许系统与外部设备交互。gpio可以配置为输入模式或输出模式，输入模式下，gpio可以读取来自传感器等外部设备的信号，输出模式下，可以控制外设引脚的电平。

在嵌入式设备中，许多IO端口可以通过内部的复用机制被配置为特定的功能，如spi、uart、usb等接口的引脚，对这些引脚的控制通常需要特定的硬件控制器来进行，一般情况下使用pinctrl子系统进行控制。

功能：

pinctrl： 设置引脚功能复用：func 、gpio；设置上下拉；

gpio（当引脚被设置为gpio模式时）: 设置输入输出方向，设置输出高低电平。

pinctrl设置引脚为gpio模式时，有时会区分设置gpio out 、gpio in，但pinctrl并不能真的影响gpio的方向，如bms代码，pinctrl设置的实际是引脚的输入使能，gpio 方向由 gpio-controller控制。

```c
case ICG_PADS_GPIO_IN:
    pads_writel(iom_addr, PADS_MUXMODE_MASK,
            PADS_MUXMODE_OFFSET, GPIO_MODE);
    pads_writel(iom_addr, PADS_INPUTEN_MASK,
            PADS_INPUTEN_OFFSET, ENABLE);
    break;

case ICG_PADS_GPIO_OUT:
    /* set func1 mode*/
    pads_writel(iom_addr, PADS_MUXMODE_MASK,
            PADS_MUXMODE_OFFSET, GPIO_MODE);
    /* set input disable */
    pads_writel(iom_addr, PADS_INPUTEN_MASK,
            PADS_INPUTEN_OFFSET, DISABLE);
    break;
```

bank：一组GPIO引脚的集合被称为一个bank，一个bank中的引脚在硬件上通常以连续的方式分配在一个物理接口或寄存器中。

## 二、命令行控制gpio

在linux系统中，每一个gpio都被映射为一个文件夹，存放在 /sys/class/gpio/目录下，可以通过cat命令查看gpio信息，通过echo命令 设置gpio。

```shell
设置cpu 90号引脚(uart2 txd)为输出模式，设置电平高/低，并通过示波器对照。

cpu 90号引脚在系统中的引脚号 = cpu_gpio_base + offset = 200 + 90 = 290

bash-5.2# ls
bin  etc   lib    linuxrc  mnt  proc         root  sbin  tmp  var
dev  init  lib64  media    opt  ramdisk.img  run   sys   usr
bash-5.2#
bash-5.2# cd sys/class/gpio/
bash-5.2# ls
export  gpiochip0  gpiochip200  unexport
bash-5.2# echo 290 > export
bash-5.2# ls
export  gpio290  gpiochip0  gpiochip200  unexport
bash-5.2# cd gpio290
bash-5.2# ls
active_low  device  direction  power  subsystem  uevent  value
bash-5.2# echo out > direction

/设置高低电平，与示波器对照查看/
bash-5.2# echo 1 > value   
bash-5.2# echo 0 > value
bash-5.2# echo 1 > value
```

## 三、uboot中pinctrl 和 gpio

以icg 驱动为例，代码只截取了一部分作为说明。

实现一个uboot设备驱动，需要使用U_BOOT_DRIVER宏来定义一个udevice_driver，实现对应的操作集和probe函数。

service dev probe函数会在client dev 获取service dev时调用， probe 过程主要是设置驱动的私有属性或配置属性，如base_addr、gpio_count等，这些属性信息一般通过设备树获取。

有的驱动中会实现bind函数，这是因为uboot只会对设备树root节点的第一层子节点进行分析， 创建udevice 和uclass，而对于其他设备的字节点，需要在驱动中自己bind子节点。bind函数会在 device_bind_common 函数中调用，当没有子节点时，可以为NULL或直接返回"0";

```c
static int stm32_pinctrl_bind(struct udevice *dev)
{
	dev_for_each_subnode(node, dev) {
		debug("%s: bind %s\n", __func__, ofnode_get_name(node));

		ofnode_get_property(node, "gpio-controller", &ret);
		if (ret < 0)
			continue;
		/* Get the name of each gpio node */
		name = ofnode_get_name(node);
		if (!name)
			return -EINVAL;

		/* Bind each gpio node */
		ret = device_bind_driver_to_node(dev, "gpio_stm32",
						 name, node, NULL);	
	}
}
```

client设备使用server总线时，使用uclass_driver提供的统一接口。

### 3.1 pinctrl框架分析

#### 3.1.1 pinctrl device_driver

```c
static int icg_pinctrl_probe(struct udevice *dev)
{
    struct icg_pinctrl_priv *priv = dev->priv;
    
    /*get pinctrl addr*/
	base_addr = dev_read_addr(dev);
	priv->base_addr = base_addr;
    
    return 0;
}

static struct pinctrl_ops icg_pinctrl_ops = {
	.set_state = icg_pinctrl_set_state,
};

static const struct udevice_id icg_pinctrl_ids[] = {
	{ .compatible = "icg,icg-pinctrl" },
	{ }
};

U_BOOT_DRIVER(pinctrl_icg) = {
	.name			= "pinctrl_icg",
	.id				= UCLASS_PINCTRL,
	.of_match		= icg_pinctrl_ids,
	.ops			= &icg_pinctrl_ops,
	.bind			= icg_pinctrl_bind,
	.probe			= icg_pinctrl_probe,
	.priv_auto_alloc_size	= sizeof(struct icg_pinctrl_priv),
	.flags = DM_FLAG_PRE_RELOC,
};
```

#### 3.1.2 pinctrl设备树

```c
pinctrl_cpu: pin-controller@1{
    #address-cells = <2>;
    #size-cells = <2>;
    reg = <0 0xc2f09000 0 0x1000>;
    compatible = "icg,icg-pinctrl";
    pin-domain = <ICG_DOMAIN_CPU>;
};
```

#### 3.1.3 pinctrl使用

pinctrl的接口只能通过设备树属性获取，需要在设备树中指定pinctrl-dev 和 pinctrl-node，pinctrl-node结构是自定义的，一般包括引脚号和功能。

```c
&pinctrl_cpu {
	pin_macb0: pinctrl_macb0{
    	pinmux = <29 44>;                                                   
    	function = <ICG_PADS_FUNC ICG_PADS_FUNC0 ICG_PADS_PULL_UP>;
};
    
macb0: ethernet@c4400000 {
		pinctrl-names = "default";
		pinctrl-0 = <&pin_macb0>;
}
```

可以通过pinctrl_select_state(dev, pinctrl-names)来设置pin，对与client device，uboot会在device_probe中会调用pinctrl_select_state(dev, "default")；所以该接口一般不需要手动调用。

```c
int pinctrl_select_state(struct udevice *dev, const char *statename)；
```

设置引脚最终会调用驱动的set_state接口，传进来的参数config对应一个pinconfig device 即 pin_macb0节点，对于pinctrl不需要关心pinconfig，只需要按照正常的设备树操作获取节点信息即可。

需要注意的一点是重定位前pin_node的使用，因为pin_node被当做了一个pinconfig device，所以单纯在pinctrl中添加 flags = DM_FLAG_PRE_RELOC 或 u-boot,dm-pre-reloc 并不能成功的设置pin功能，因为此时pinconfig 的uclass 和 udevice还没有被创建，所以还需要在对应的pin-node节点下也添加 u-boot,dm-pre-reloc。

```c
static int icg_pinctrl_set_state(struct udevice *dev, struct udevice *config)
{
    icg_pinctrl_parse_dtb(config, &info);
    icg_pinctrl_set_mux(dev, info);
    return 0;
    
}
```

#### 3.1.4 pinconfig device

在uboot中，pinctrl的每个子节点都会被认为是一个pinconfig device(gpio-controller除外)，在pinctrl uclass_driver中定义了post_bind函数，用来对pinctrl的子节点进行绑定device 和 device_driver。

```c
/* pinctrl-uclass.c*/
UCLASS_DRIVER(pinctrl) = {
	.id = UCLASS_PINCTRL,
	.post_bind = pinctrl_post_bind,
	.flags = DM_UC_FLAG_SEQ_ALIAS,
	.name = "pinctrl",
};

static int __maybe_unused pinctrl_post_bind(struct udevice *dev)
{
    ....
	if (ops->set_state)
		return pinconfig_post_bind(dev);
	return 0;
}

/**
 * pinconfig_post_bind() - post binding for PINCONFIG uclass
 * Recursively bind its children as pinconfig devices.
 *
 * @dev: pinconfig device
 * @return: 0 on success, or negative error code on failure
 */
static int pinconfig_post_bind(struct udevice *dev)
{
	bool pre_reloc_only = !(gd->flags & GD_FLG_RELOC);
	const char *name;
	ofnode node;
	int ret;

	dev_for_each_subnode(node, dev) {
		if (pre_reloc_only &&
		    !ofnode_pre_reloc(node))
			continue;
		/*
		 * If this node has "compatible" property, this is not
		 * a pin configuration node, but a normal device. skip.
		 */
		ofnode_get_property(node, "compatible", &ret);
		if (ret >= 0)
			continue;
		/* If this node has "gpio-controller" property, skip */
		if (ofnode_read_bool(node, "gpio-controller"))
			continue;
        
		name = ofnode_get_name(node);
		if (!name)
			return -EINVAL;
		ret = device_bind_driver_to_node(dev, "pinconfig", name,
						 node, NULL);
		if (ret)
			return ret;
	}

	return 0;
}

UCLASS_DRIVER(pinconfig) = {
	.id = UCLASS_PINCONFIG,
#if CONFIG_IS_ENABLED(PINCONF_RECURSIVE)
	.post_bind = pinconfig_post_bind,
#endif
	.name = "pinconfig",
};

```



### 3.2 gpio框架分析

#### 3.2.1  gpio device_driver

```c
/*gpio 操作集*/
static const struct dm_gpio_ops gpio_icg_ops = {
	.direction_input	= icg_gpio_direction_input,
	.direction_output	= icg_gpio_direction_output, 
	.get_value		= icg_gpio_get_value,		      			
	.set_value		= icg_gpio_set_value,
	.get_function		= icg_gpio_get_function,
};

static int gpio_icg_probe(struct udevice *dev)
{
	struct icg_gpio_priv *priv = dev->priv;
	/*get addr*/
	base_addr = dev_read_addr(dev);
	priv->base_addr = base_addr;
	return 0;
}

static const struct udevice_id icg_gpio_ids[] = {
	{ .compatible = "icg,gpio-controller" },
	{ }
};

U_BOOT_DRIVER(gpio_icg) = {
	.name = "gpio_icg",
	.id	= UCLASS_GPIO,
	.of_match = icg_gpio_ids,
	.probe = gpio_icg_probe,
	.bind = gpio_icg_bind,
	.priv_auto_alloc_size = sizeof(struct icg_gpio_priv), /*probe时创建私有结构*/
	.ops = &gpio_icg_ops,
	.flags = DM_FLAG_PRE_RELOC,    /*在重定位前进行udevice 和 uclass的创建*/
};

```

#### 3.2.2 gpio设备树

使用一些gpio宏时需要包含头文件 <dt-bindings/gpio/gpio.h>

```c
gpio_cpu: gpio1-controller@c2100000 {
    pin-domain = <ICG_DOMAIN_CPU>; 
    compatible = "icg,gpio-controller";
    reg = <0x0 0xc2100000 0x0 0x1000>;
    power-domains = <&power WS6520_PD_GPIO_CPU>;
    #gpio-cells = <1>;
    ngpios = <150>;
    gpio-controller;
};
```

#### **3.2.3 gpio使用**

使用设备树获取gpio，接口如下，需要再客户dev中的设备树描述

```c
ret = gpio_request_by_name(dev, "reset-gpios", 0, &desc, GPIOD_IS_OUT);
if (ret) {
    printf("macb: no reset-gpio\n");
    return;
}
dm_gpio_set_value(&desc, 1);
dm_gpio_free(dev, &desc);

&macb0 {
	reset-gpios = <&gpio_cpu 41 0>;
};
```

使用gpio引脚号做参数，接口如下：

```c
/*lable 只作为标签，可以不设*/
int gpio_request(unsigned gpio, const char *label);
int gpio_free(unsigned gpio);
int gpio_direction_output(unsigned gpio, int value);
int gpio_direction_input(unsigned gpio);
int gpio_set_value(unsigned gpio, int value);
```

使用gpio引脚号做参数获取gpio dev，需要匹配个gpio-dev的gpio_count 和 gpio_base。

```c
/* uclass-gpio.c */
static int gpio_to_device(unsigned int gpio, struct gpio_desc *desc)
{
	struct gpio_dev_priv *uc_priv;
	struct udevice *dev;
	int ret;

	for (ret = uclass_first_device(UCLASS_GPIO, &dev);
	     dev;
	     ret = uclass_next_device(&dev)) {
		uc_priv = dev_get_uclass_priv(dev);
		if (gpio >= uc_priv->gpio_base &&
		    gpio < uc_priv->gpio_base + uc_priv->gpio_count) {
			desc->dev = dev;
			desc->offset = gpio - uc_priv->gpio_base;
			desc->flags = 0;
			return 0;
		}
	}

	/* No such GPIO */
	return ret ? ret : -ENOENT;
}
```

gpio_count 由gpio控制器自己设置。

```c
static int gpio_icg_probe(struct udevice *dev)
{
    struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	uc_priv->gpio_count = ngpios; /*ngpios可以自己设置，可以从设备树中获取*/
	uc_priv->bank_name = dev->name;
}
```

gpio_base由 uclass_drv动态设置，当有gpio 控制器 probe 或 remove时，gpio_base会重新分配，所以需要注意，当多个gpio控制器在设备树中的描述顺序发生改变时，其对应的gpio base也会发生改变。

在linux kernel中，gpio_base 和 gpio_count 都由gpio控制器自己设置，而不会renumber。

```c
/* We need to renumber the GPIOs when any driver is probed/removed */
static int gpio_renumber(struct udevice *removed_dev)
{
	struct gpio_dev_priv *uc_priv;
	struct udevice *dev;
	struct uclass *uc;
	unsigned base;
	int ret;

	ret = uclass_get(UCLASS_GPIO, &uc);
	if (ret)
		return ret;

	/* Ensure that we have a base for each bank */
	base = 0;
	uclass_foreach_dev(dev, uc) {
		if (device_active(dev) && dev != removed_dev) {
			uc_priv = dev_get_uclass_priv(dev);
			uc_priv->gpio_base = base;
			base += uc_priv->gpio_count;
		}
	}
	return 0;
}
```

### 3.3 pinctrl 和 gpio 的关联

在uboot中，可以将gpio 作为 pinctrl的子节点使用，pinctrl实现对应的bind函数完成对应gpio的设备节点创建，并获取gpio的dev保存。

或设备树中pinctrl 和 gpio独立, 通过 uclass_get_device接口遍历所有的pinctrl 或 gpio设备，找到自己需要的dev。（不推荐）

## 四、kernel中的pinctrl和gpio

在内核使用struct platform_driver定义一个总线设备

### 4.1 pinctrl框架分析

#### 4.1.1 pinctrl device

```c
static const struct of_device_id icg_pctl_of_match[] = {
	{ .compatible = "icg,icg-pinctrl" },
	{}
};

static struct platform_driver icg_pctl_driver = {
	.driver = {
		.name = "icg,icg-pinctrl",
		.of_match_table = icg_pctl_of_match,
	},
	.probe = icg_pctl_probe,
};

static int __init icg_pctl_init(void)
{
	return platform_driver_register(&icg_pctl_driver);
}
arch_initcall(icg_pctl_init);
```

在kernel中私有属性结构体需要deiver 自己malloc空间，主要包括基地址base_addr ，操作集pctldev，设备树信息pin_node。

```c
struct icg_pinctrl_info {
	struct device *dev;
	void __iomem *base_addr;
	unsigned int domain;
	struct pinctrl_dev *pctldev;

	/*保存所有设备树节点*/
	struct icg_pinctrl_group *groups;
	unsigned int ngroups;

	/*获取单个group的所有pin值*/
	unsigned int pin_list[ICG_GROUP_PIN_MAX];

	/*gpio range，gpio-ctrl 设置 gpio-func时以此匹配pinctrl*/
	struct pinctrl_gpio_range gpio_range;
};

/*设置pctl_dest、drvdata, 分析设备树，保存子节点gpio 和 node 信息*/
static int icg_pctl_probe(struct platform_device *pdev)
{
	struct icg_pinctrl_info *info;
	struct pinctrl_desc *pctl_desc;
	struct resource *res;
	int ret;

	pctl_desc = devm_kzalloc(&pdev->dev, sizeof(*pctl_desc), GFP_KERNEL);
	if (!pctl_desc) {
		ICG_PINCTRL_LOG("icg_pctl_probe pctl_desc malloc failed\n");
		return -ENOMEM;
	}
	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info) {
		ICG_PINCTRL_LOG("icg_pctl_probe info malloc failed\n");
		return -ENOMEM;
	}

	/*set info*/
	info->dev = &pdev->dev;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ICG_PINCTRL_LOG("missing IO resource\n");
		return -ENODEV;
	}
	info->base_addr = devm_ioremap_resource(&pdev->dev, res);
	ICG_PINCTRL_LOG("pinctrl get addr = 0x%lx, phyaddr = %llx\n",
			(unsigned long)info->base_addr, res->start);
	platform_set_drvdata(pdev, info);

	/*set info->fdt*/
	ret = icg_pctl_probe_fdt(pdev, info);
	if (ret) {
		printk("icg_pctl_probe_fdt failed, ret =%d\n", ret);
		return ret;
	}

	/*set desc*/
	pctl_desc->owner = THIS_MODULE;
	pctl_desc->pctlops = &icg_pctlops;
	pctl_desc->pmxops = &icg_pmxops;
	pctl_desc->confops = NULL;
	pctl_desc->name = dev_name(&pdev->dev);
	ret = icg_pinctrl_set_descpin(pdev, pctl_desc, info);
	if (ret)
		return ret;

	/*register pin*/
	info->pctldev = devm_pinctrl_register(&pdev->dev, pctl_desc, info);
	if (IS_ERR(info->pctldev)) {
		dev_err(&pdev->dev, "Failed pinctrl registration\n");
		return PTR_ERR(info->pctldev);
	}

	/*register gpio rage*/
	pinctrl_add_gpio_range(info->pctldev, &info->gpio_range);

	ICG_PINCTRL_LOG("pinctrl probe success, domain = %d\n", info->domain);
	return 0;
}
```

linux中pinctrl 的node不再作为device被使用，而是被当做pinctrl的配置信息，由pinctrl驱动提前分析保存。

```c
/* 从设备树中pin描述结构，成员与设备树pin_node一一对应*/
struct icg_pinctrl_parm {
	struct icg_pinctrl_pins_parm pins;
	struct icg_pinctrl_func_parm func;
};

/* group中包含引脚和功能，获取的pin selecter 和 func selecter会是同一个*/
struct icg_pinctrl_group {
	struct icg_pinctrl_parm pin_node;
	const char *name;
	unsigned int npins;
};

int icg_pctl_probe_fdt(struct platform_device *pdev,
		       struct icg_pinctrl_info *info)
{

	/*set group*/
	info->ngroups = of_get_child_count(np); /*minus gpio node*/
	if (info->ngroups == 0) {
		return 0;
	}
	info->groups = devm_kzalloc(
		&pdev->dev, sizeof(*info->groups) * info->ngroups, GFP_KERNEL);
	if (!info->groups) {
		return -ENOMEM;
	}

	i = 0;
	/*遍历所有子节点*/
	for_each_child_of_node (np, child) {
		if (of_property_read_bool(child, "gpio-controller")) {
			continue;
		} else {
			icg_pctl_parse_fdt_group(pdev, child, &info->groups[i]);
			i++;
		}
	}
	return 0;
}

/*分析每个 group/node 的节点*/
static int icg_pctl_parse_fdt_group(struct platform_device *pdev,
				    struct device_node *np,
				    struct icg_pinctrl_group *group)
{
	/*获取pin start end*/
	/*获取func value pull*/
    of_property_read_u32_array(...);
	return 0;
}
```

pinctrl 的操作集由struct pinctrl_dev *pctldev 描述，该结构体具体的实现在pinctrl使用中描述。

```c
struct pinctrl_desc {
	const char *name;
	const struct pinctrl_pin_desc *pins;    /*声明每一个*/
	unsigned int npins;
	const struct pinctrl_ops *pctlops;      /*获取 pin-node 信息*/
	const struct pinmux_ops *pmxops;        /*设置 功能复用*/
	const struct pinconf_ops *confops;
}

static const struct pinctrl_ops icg_pctlops = {
	.get_groups_count = icg_pctl_get_groups_cnt,
	.get_group_name = icg_pctl_get_group_name,
	.get_group_pins = icg_pctl_get_group_pins,
	.dt_node_to_map = icg_pctl_dt_node_to_map,
	.dt_free_map = icg_pctl_dt_free_map,
};

static const struct pinctrl_ops icg_pctlops = {
	.get_groups_count = icg_pctl_get_groups_cnt,
	.get_group_name = icg_pctl_get_group_name,
	.get_group_pins = icg_pctl_get_group_pins,
	.dt_node_to_map = icg_pctl_dt_node_to_map,
	.dt_free_map = icg_pctl_dt_free_map,
};
```

#### 4.1.2 pinctrl使用

使用 devm_pinctrl_get_select_default(dev)；或   devm_pinctrl_get_select(dev, PINCTRL_STATE_DEFAULT)配置引脚。

```c
/*include/linux/pinctrl/consumer.h*/
static inline struct pinctrl * __must_check devm_pinctrl_get_select(
					struct device *dev, const char *name)
{
	struct pinctrl *p;
	struct pinctrl_state *s;
	int ret;

	p = devm_pinctrl_get(dev);          /* 获取pinctrl资源 */
    s = pinctrl_lookup_state(p, name);	/* 获取配置node节点*/
    ret = pinctrl_select_state(p, s);	/* 设置pins*/
    
    return p;
}
```

devm_pinctrl_get--> create_pinctrl-->pinctrl_dt_to_map中会将找到的pin-node信息做map操作，对应操作集的dt_node_to_map，一个map即一个pin_group，并通过pin-node 的name和group进行匹配。

map时需要设置map type，用来区分使用pinmux 还是pinconfig。

map 包括了pin group 和 func group，但因为icg中将两者信息放在了一个结构体，所以用同一个name标识。

```c
static int icg_pctl_dt_node_to_map(struct pinctrl_dev *pctldev,
				   struct device_node *np,
				   struct pinctrl_map **map, unsigned *num_maps)
{
	struct icg_pinctrl_info *info = pinctrl_dev_get_drvdata(pctldev);
	const struct icg_pinctrl_group *group;
	struct pinctrl_map *new_map;
	struct device_node *parent;
	int map_num;

	/*
	 * first find the group of this node and check if we need to create
	 * config maps for pins
	 */
	group = icg_pinctrl_name_to_group(info, np->name);
	if (!group) {
		dev_err(info->dev, "unable to find group for node %pOFn\n", np);
		return -EINVAL;
	}
	ICG_PINCTRL_LOG("find group %s\n", np->name);

	/*按照group进行map, 只需要设置name*/
	map_num = 1;
	new_map = kcalloc(map_num, sizeof(*new_map), GFP_KERNEL);
	if (!new_map)
		return -ENOMEM;

	*map = new_map;
	*num_maps = map_num;

	/* create mux map */
	ICG_PINCTRL_LOG("group node find parent-pinctrl\n");
	parent = of_get_parent(np);
	if (!parent) {
		kfree(new_map);
		return -EINVAL;
	}
	new_map[0].type = PIN_MAP_TYPE_MUX_GROUP;
	new_map[0].data.mux.function = np->name;
	new_map[0].data.mux.group = np->name;
	of_node_put(parent);

	ICG_PINCTRL_LOG("icg_pctl_dt_node_to_map success\n");

	return 0;
}
```

pinctrl_select_state-->pinctrl_commit_state-->pinmux_enable_setting ,最终会调用操作集合中的 set_mux 来设置pin 功能；其中参数为group 的索引。

```c
int pinmux_enable_setting(const struct pinctrl_setting *setting)
{
	pctlops->get_group_pins();
    for (i = 0; i < num_pins; i++) {
    	pin_request();
        pin_desc_get();
        ops->set_mux();
    }
}
```

需要注意的是pin_request，该函数会从注册的引脚中获取指定的pin并做标记，pin的范围由desc->base 和 npins 决定，调用 devm_pinctrl_register(&pdev->dev, pctl_desc, info) 注册。

```c
/* pinctrl/core.h */
static inline struct pin_desc *pin_desc_get(struct pinctrl_dev *pctldev,
					    unsigned int pin)
{
	return radix_tree_lookup(&pctldev->pin_desc_tree, pin);
}

/* 设置pindesc的引脚，不指定具体功能或name，只需要保证在pin_request时能申请到pin */
static int icg_pinctrl_set_descpin(struct platform_device *pdev,
				   struct pinctrl_desc *pctl_desc,
				   struct icg_pinctrl_info *info)
{
	int i;
	struct pinctrl_pin_desc *pins;

	pctl_desc->npins = info->gpio_range.npins;
	pins = devm_kzalloc(&pdev->dev,
			    sizeof(struct pinctrl_pin_desc) * pctl_desc->npins,
			    GFP_KERNEL);
	if (!pins) {
		ICG_PINCTRL_LOG("pctl_desc->pins malloc failed\n");
		return -ENOMEM;
	}

	for (i = 0; i < pctl_desc->npins; ++i) {
		pins[i].number = i;
		pins[i].name = NULL;
	}

	pctl_desc->pins = pins;
	return 0;
}
```

### 4.2 gpio框架分析

linux gpio 与  uboot差不多，区别在由linux gpio_base可以由gpio 驱动设置，而不再自动分配。

```c
static int icg_gpio_probe(struct platform_device *pdev)
{
	struct gpio_chip *chip;
	of_property_read_u32_array(pdev->dev.of_node, "gpio-base", &chip->base, 1);
	of_property_read_u32_array(pdev->dev.of_node, "ngpios", &ngpios, 1);
	chip->ngpio = ngpios;
}
```

设置gpio方向时，需要调用pinctrl去设置gpio模式，

```c
static int icg_gpio_direction_output(struct gpio_chip *gc, unsigned offset,
				     int value)
{
	int ret;
	unsigned int tmp;
	struct icg_gpio *gpio = gpiochip_get_data(gc);
	unsigned long addr =
		(unsigned long)gpio->base_addr + ICG_GPIO_IOCTL_OFFSET(offset);

	ret = pinctrl_gpio_direction_output(gc->base + offset);
	if (ret) {
		printk("gpio: pinctrl_gpio_direction_output ret = %d\n", ret);
		return ret;
	}
    
    icg_gpio_set_dir();
}
```

pinctrl_gpio_direction_output 函数通过gpio引脚号来匹配对应的pinctrl,需要pinctrl提前注册号gpio_range。

```c
static int icg_pctl_probe(struct platform_device *pdev)
{
	of_property_read_u32_array(pdev->dev.of_node, "npins",
				   &info->gpio_range.npins, 1);
	of_property_read_u32_array(pdev->dev.of_node, "pin-base",
				   &info->gpio_range.pin_base, 1);
	info->gpio_range.pins = NULL;
	info->gpio_range.base = info->gpio_range.pin_base;
	/*register gpio rage*/
	pinctrl_add_gpio_range(info->pctldev, &info->gpio_range);
}
```

#### 4.2.1 gpio 使用

与uboot gpio使用一致。

```c
/*从设备树信息中获取gpio*/
/*con_id：linux实际查找的字符串属性是 con_id-gpio 或 con_id-gpios，需要注意*/
struct gpio_desc *__must_check devm_gpiod_get(struct device *dev,
					      const char *con_id,
					      enum gpiod_flags flags);
void devm_gpiod_put(struct device *dev, struct gpio_desc *desc);
void gpiod_set_value(struct gpio_desc *desc, int value);
int gpiod_direction_input(struct gpio_desc *desc);
int gpiod_direction_output(struct gpio_desc *desc, int value);

#include <linux/gpio.h>
/*应用层依据gpio号获取gpio*/
int gpio_request(unsigned gpio, const char *label);
void gpio_free(unsigned gpio);
int gpio_direction_input(unsigned gpio);
int gpio_direction_output(unsigned gpio, int value);
int gpio_get_value(unsigned gpio);
void gpio_set_value(unsigned gpio, int value);
```

