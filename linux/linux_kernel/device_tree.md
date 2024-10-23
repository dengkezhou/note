设备树

## 一、概述

设备树(Device Tree)是描述硬件资源的数据结构，它通过bootloader将硬件资源信息传给内核，使内核和硬件资源描述相对独立。所以，对于同一SOC的不同主板，只需要跟换设备树文件而不需要跟换内核文件。

设备树可以描述的信息包括：cpu的数量的类别、内存基地址和大小、总线和桥、外设连接、中断控制器和中断使用情况、GPIO控制器和GPIO使用情况、Clock控制器和Clock使用情况。

另外，设备树对于可热插拔的设备不进行具体描述，它只描述于控制热插拔设备的控制器。

## 二、编译

设备树源文件(Device Tree Source)是一种ASCII形式的文本文件，有自己的语法，一般以.dts为后缀。

编译工具为DTC工具，位于linux内核代码的 scripts/dtc目录下，依赖dtc.c flattree.c fstree.c 等c文件，通过gcc编译得到，

DTS文件通过DTC工具编译生出二进制目标文件，以.dtb为后缀。

linux内核中使用 dtb-y 变量来指定编译的设备树dtb目标，通过隐藏规则编译对应的dts文件。

```makefile
dtb-$(CONFIG_SOC_XXX) += \
	xxx.dtb
```

一般而言，一个dts文件对应一种machine，对于多种机器共用的设备节点，可以提取出来保存在.dtsi文件中，当做设备树的头文件。

## 三、语法

dts文件是一种ASCII文本文件，方便阅读和修改。一般每一个设备都对应一个dts文件。

使用 /**/进行注释

### 3.1 设备节点

在树形结构上，每个设备都是一个节点，称为设备节点，每个节点都通过一些属性来描述设备信息。

```dtd
1	/ {
2		aliases {
3			can0 = &flexcan1;
4		};
5
6		cpus {
7 			#address-cells = <1>;
8 			#size-cells = <0>;
9
10			cpu0: cpu@0 {
11 				compatible = "arm,cortex-a7";
12 				device_type = "cpu";
13 				reg = <0>;
14			};
15		};
16
17		intc: interrupt-controller@00a01000 {
18 			compatible = "arm,cortex-a7-gic";
19 			#interrupt-cells = <3>;
20 			interrupt-controller;
21 			reg = <0x00a01000 0x1000>,
22				  <0x00a02000 0x100>;
23 		};
24   }
```

第1行 “/” 是根节点，每个设备树文件只有一个根节点，不同文件的相同根节点在编译时会被合并。

第2、6、17行，aliases、cpus和intc是三个子节点，在设备树中节点命名格式如下：

```
node-name@unit-address
lable: node-name@unit-address
```

node-name是设备名，为字符串；

unit-address是设备的地址或寄存器基地址，为16进制数，当定义reg属性时，会使用reg的值作为基地址。

lable是设备名的标签，目的是方便访问设备，可以通过 &lable 来访问 node-name@unit-address。

第10行，cpu0是cpus的一个子节点。

### 3.2 属性

属性是一种键值对，键一般是字符串，值可以是空、32位无符号整数、字符串、字符串列表。

属性有标准属性和自定义属性，以下是几种标准属性：

**compatible**: 兼容性，用于设备和驱动的绑定，值一般是字符串列表，manufactuer是厂家名，model是驱动名，可以有多个字符串，字符串之间以“,”隔开。

```
compatible = "manufacturer,model" 
```

**model** : 设备模块信息，一般为设备名，值为字符串。

**status** ：设备状态信息，值为固定的字符串，可选：

| 值         | 描述                           |
| ---------- | ------------------------------ |
| "okay"     | 表明设备可操作                 |
| "disabled" | 表面设备当前不可操作           |
| "fail"     | 表面设备不可操作，且检测到错误 |
| "fail-sss" | 同fail, sss是错误的内容        |

**#address-cells 和 #size-cells** ： 子节点地址信息，可以使用在任何拥有子节点的设备中，值为32位无符号整形。#address-cells 属性值决定了子节点reg属性中地址信息所占用的字长，#size-cells属性值决定了子节点reg属性中长度信心所占的字长。

**reg** : 一般和地址有关，值为32位无符号整形，信息有起始地址和长度，每个address 和 length是一个组合。

**#address-cells** 值为0、1时分别表示不设置地址和使用32位长度的地址，reg格式为

```
reg = <address1 length1 address2 length2...>
```

**#address-cells** 值为2时，使用64位地址，此时reg的格式为

```
reg = <address_high address_low length ...>
```

device_type : 设备类型，其值为字符串，当前只用于描述 "cpu" 和 "memory" 

### 3.3 .dtsi头文件

设备树可以使用 #include 包含 .dtsi 头文件 和 .h头文件。头文件的内容一般是多个设备共有的属性。

包含的头文件也可以是 dts源文件，但如同包含 c文件一样不推荐使用。

### 四、结构

一般来说，每一种设备节点的属性都有一些套路，可以设置哪些属性，属性值怎么设置。

可以查看内核的文档，比如Documentation/devicetree/bindings/i2c/i2c-imx.txt

**节点与节点之间的联系** 通常通过“标号引用”和“包含”来实现。

**标号引用**，在节点名称前加上标号，其他节点可以通过 ""

