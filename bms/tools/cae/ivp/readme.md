# ivp相关说明

## 1. 脚本使用说明

执行以下命令

```
提取脚本中所有测试长度：
python3 extract_ivp.py multi ddr
提取脚本中一种测试长度：
python3 extract_ivp.py single ddr
```

指定提取单个测试长度或多个测试长度，可用参数为single或multi；指定运行位置为ddr还是iram。之后将out目录下生成的c文件全部拷贝到bms/driver/cae/ivp下


## 2. bms配置说明

ivp只支持32 bit mode，所以描述符要建在32位地址空间内，这里使用0x14000000，见ivp脚本生成的test_md5.c。bms运行在ddr。
使用c920进行ivp测试，同时make menuconfig关掉cache和mmu，选中driver下的ivp test。rtl仿真时，关掉L2CACHE，如下，并make menuconfig关掉cache和mmu。

```c
liu@liu:~/src/debug/bms$ git diff arch/riscv/e906/rom-main.c
diff --git a/arch/riscv/e906/rom-main.c b/arch/riscv/e906/rom-main.c
index 2c9aa88..0fe0c31 100644
--- a/arch/riscv/e906/rom-main.c
+++ b/arch/riscv/e906/rom-main.c
@@ -73,7 +73,7 @@ int main(void) {
   if (*(uint32_t *)__lds_rtl_case == (uint32_t)RTL_MAGIC) {
 #ifdef CONFIG_BOOT_OTHER_CORE
 #ifdef CONFIG_TB_RUN_DDR
-    itcs_sysm_switch_bram(CPU, L2CACHE_MODE);
+    //itcs_sysm_switch_bram(CPU, L2CACHE_MODE);
 
     itcs_sysmap_config_region(0, 0x18000000, 0x0);
     itcs_sysmap_config_region(1, 0x20000000, 0x1);
@@ -82,7 +82,7 @@ int main(void) {
     itcs_sysmap_config_region(4, 0xd0000000, 0x2);
     itcs_sysmap_config_region(5, 0xe0000000, 0x2);
     itcs_sysmap_config_region(6, 0x100000000, 0x2);
-    itcs_sysmap_config_region(7, 0xfffffff000, 0x1);
+    itcs_sysmap_config_region(7, 0xfffffff000, 0x0);
 
     bootm = itcs_sysm_get_boot_mode(SAP);
     if (bootm == BOOTM_LPDDR4_NO_INTLEAVE)
liu@liu:~/src/debug/frigob/bms$ 

liu@liu:~/src/debug/frigob/bms$ git diff configs/c920/c920_rtl_ddr_soc_defconfig
diff --git a/configs/c920/c920_rtl_ddr_soc_defconfig b/configs/c920/c920_rtl_ddr_soc_defconfig
index 3958e33..b6b1151 100755
--- a/configs/c920/c920_rtl_ddr_soc_defconfig
+++ b/configs/c920/c920_rtl_ddr_soc_defconfig
@@ -22,11 +22,7 @@ CONFIG_NR_CPUS=4
 # CONFIG_COMPILE_ROM is not set
 CONFIG_TB_RUN_DDR=y
 # CONFIG_TB_RUN_IRAM is not set
-CONFIG_CACHE=y
-CONFIG_DCACHE=y
-CONFIG_ICACHE=y
-# CONFIG_CACHE_LITE is not set
-CONFIG_L2CACHE=y
+# CONFIG_CACHE is not set
 # CONFIG_MMU is not set
 # CONFIG_SYSMAP is not set
 CONFIG_64BIT=y
@@ -56,10 +52,12 @@ CONFIG_DRV_SPI_FLASH=y
 CONFIG_DRV_PWM=y
 # CONFIG_DRV_PVT is not set
 CONFIG_DRV_CAE=y
-# CONFIG_DRV_CAE_IVP is not set
+CONFIG_DRV_CAE_IVP=y
 CONFIG_DRV_PUFCC=y
 # CONFIG_DRV_DDR is not set
 # CONFIG_DRV_RXA is not set
+# CONFIG_DRV_LPDDR4 is not set
+# CONFIG_DRV_VC9000D is not set
 CONFIG_COMPILE_TBH=y
 # CONFIG_TBH_CPU is not set
 CONFIG_TBH_DMA=y
@@ -88,6 +86,7 @@ CONFIG_TBH_CAE=y
 CONFIG_TBH_PUFCC=y
 # CONFIG_TBH_DDR is not set
 # CONFIG_TBH_RXA is not set
+# CONFIG_TBH_LPDDR4 is not set
 CONFIG_COMPILE_LIB=y
 CONFIG_LIB_COMMAND=y
 CONFIG_LIB_MATH=y
@@ -102,3 +101,4 @@ CONFIG_LIB_RTL=y
 # CONFIG_LIB_FREERTOS is not set
 # CONFIG_LIB_SBI is not set
 CONFIG_COMPILE_ARCH=y
+CONFIG_HW_MEMDEV=y
liu@liu:~/src/debug/frigob/bms$ 
```
使用e906进行ivp测试，make menuconfig关掉cache和mmu，选择运行位置为ddr，同时选中driver下的ivp test。rtl仿真时，make menuconfig关掉cache和mmu，选中driver下的ivp test，并替换原来的defconfig文件。由于cae比较大rtl编译不过，所以还需修改下列文件。

```c
liu@liu:~/src/debug/tmp/cae_1$ git diff arch/riscv/e906/soc.ld.S
diff --git a/arch/riscv/e906/soc.ld.S b/arch/riscv/e906/soc.ld.S
index c931c66..5e8d2b1 100644
--- a/arch/riscv/e906/soc.ld.S
+++ b/arch/riscv/e906/soc.ld.S
@@ -9,8 +9,8 @@ MEMORY
        SRAM_DATA               : ORIGIN = 0x0c000000, LENGTH = 0x20000 /* 128KB */
        /* IROM 2MB */
 #ifdef CONFIG_TB_RUN_DDR
-       MEM_TXT         : ORIGIN = 0x40000000, LENGTH = 0x80000    /* 512KB */
-       MEM_DAT     : ORIGIN = 0x40080000, LENGTH = 0xf80000   /* 16MB-512KB */
+       MEM_TXT         : ORIGIN = 0x40000000, LENGTH = 0x800000    /* 512KB */
+       MEM_DAT     : ORIGIN = 0x40800000, LENGTH = 0x800000   /* 16MB-512KB */
 #ifdef CONFIG_CACHE_LITE
        MEM_MALLOC      : ORIGIN = 0x60000000, LENGTH = 0x8000000  /*128MB */
 #else
liu@liu:~/src/debug/tmp/cae_1$ git diff arch/riscv/lib/sysmap.c
diff --git a/arch/riscv/lib/sysmap.c b/arch/riscv/lib/sysmap.c
index f5adef9..386853f 100644
--- a/arch/riscv/lib/sysmap.c
+++ b/arch/riscv/lib/sysmap.c
@@ -13,7 +13,7 @@ sysmap_region_t regions[] = {
 #endif
     {0x20000000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
     {0x40000000, SYSMAP_SYSMAPCFG_SO_Msk},
-    {0x40080000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
+    {0x40800000, SYSMAP_SYSMAPCFG_B_Msk | SYSMAP_SYSMAPCFG_C_Msk},
     {0x49000000, SYSMAP_SYSMAPCFG_B_Msk},
     {0xc0000000, SYSMAP_SYSMAPCFG_SO_Msk},
     {0xfffff000, SYSMAP_SYSMAPCFG_SO_Msk}};
liu@liu:~/src/debug/tmp/cae_1$ 
```


## 3. 描述符结构简要说明

### 3.1 32 bit描述符说明

- 命令描述符大致结构：

  ​    31.........0

  0  additional_cdata_size(31 - 24) | first_seg(23) | last_seg(22) | reserved(21 - 17) | particle_size(16 - 0)

  1  input_data_pointer

  2  input_token_pointer

  3  token header(type(31 - 30) | U(29) | IV(28 - 26) | C(25) | ToO(24 - 22) | RC(21 - 20) | CT(19) | CP(18) | IP(17) | packet_len(16 - 0))

  4  application_id

  5  context buf pointer

  token header参考96 hardware reference and programmer manual revd.pdf中的7.2.1.1

- input token结构包括：

  0  cw0 (optional)

  1  cw1 (optional)

  2  process instruction(direction)

  3  process instruction(insert)

- context buf结构包括：

  0  cw0

  1  cw1

  cw0与cw1结构可参考96 operations manual with token examples revc.pdf中的3.2或4.1

- 结果描述符大致结构：

  ​    31.........0

  0  first_seg | last_seg | particle_size | particle_fill_level

  1  output_data_pointer


## 4. ivp与ddk fpga寄存器、描述符对比

### 4.1 在fpga上运行ddk获取寄存器、描述符数据

使用e906_fpga_soc_defconfig，将编译位置选iram，关闭cache，eclipse运行soc.elf，获取ddk寄存器配置和硬件描述符信息，保存其为ddk_in.txt。

### 4.2 使用ivp_ddk_parse.py生成ddk端寄存器、描述符数据

执行命令python3 ivp_ddk_parse.py ddk，在out目录会生成ddk_out.txt。

### 4.3 使用ivp_ddk_parse.py生成ivp端寄存器、描述符数据

执行命令python3 ivp_ddk_parse.py ivp，在out目录会生成对应ivp的txt文件。

### 4.4 cm_ivp_ddk目录

该目录下ddk_out.txt和test_md5_rfc.txt分别为ddk、ivp的dump信息，这里以md5为示例。

## 5. ivp与ddk rtl总线寄存器、描述符比较（不推荐）

### 5.1 获得数据文件

首先git clone frigo_de，之后开始跑cae某一具体算法的rtlcase，

```
cd frigo_de/
csh
source sourceme
cds
vim def.cfg，注释掉B2M4_DUMMY，B3M0_DUMMY。打开其他所有define
cd sw_case
unlink case
ln -s xxx case
./gen_case.h
cd ..
make runcase CASE=xxx
```

rtlcase跑完后，会在fronted/sim/work下生成cae_ahb_slave.dat和cae_axi_master.dat，前者为cae寄存器读写操作，后者为内存读写操作。下次再跑rtlcase只需要以下操作，

```
make rerun CASE=xxx
```

git pull完需要重新编译，需使用make runcase CASE=xxx。

### 5.2 比较步骤

首先确定输入数据，key，iv等是否正确，
- 寄存器比较：

  首先确定命令描述符在内存中的地址，看下cae_ahb_slave.dat中0xc5400000和0xc5400004寄存器中的值，

  再确定结果描述符在内存中的地址，看下0xc5400800和0xc5400804寄存器中的值

- 内存中命令描述符比较：

  在cae_axi_master.dat文件中，从描述符首地址偏移为8字节的位置确定输入数据的地址，从此数据地址检查输入数据是否正确；从描述符首地址偏移为16字节的位置确定token的地址，以此地址检查cw0，cw1和direction值大致是否正确；从描述符首地址偏移为40字节的位置确定context的地址，按顺序检查此地址中cw0，cw1，key和iv的值是否正确


- 内存中结果描述符比较：

  确定好结果描述符在内存中的地址后，在cae_axi_master.dat文件中，以此地址找到结果描述符，在偏移为8字节的位置确定输出数据的地址，以此地址找到输出数据并确认

### 5.3 其他

axi总线数据读取顺序：

- 读结果描述符中的particle和结果数据地址
- 再读命令描述符
- 读命令描述符中token中的cw0，cw1
- 读命令描述符中输入数据
- 读命令描述符中context中的key，iv
- 写输出结果到结果描述符中的结果数据地址

写完结果描述符已经准备好的数目寄存器，cae dma就开始工作了。
