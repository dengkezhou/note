#模块的编译需要指明内核文件路径
KERNEL_VER = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(KERNEL_VER)/build/

PWD = $(shell pwd)  #文件路径,不一定是PWD。

#cc 和 ARCH 根据编译器和CPU类型定义,且一般定义在srcipt文件中,是有source加载。

#目标文件
MODULE := char_dev


obj-m := $(MODULE).o        #-m 表明是modules编译


 #需要编译的文件
$(MODULE)-objs := drv_probe.o 

         
all:
	make -C $(KERNEL_DIR) M=$(PWD) modules  #编译指令
    
install:
	sudo insmod ./$(MODULE).ko
	sudo chmod 666 /dev/$(MODULE)   

remove:
	sudo rmmod $(MODULE)

#加载ko生成的设备文件权限为600,且一般是root所有,应用程序使用open接口时,可能没有权限。
#生成的设备文件名,和 makefile中 MODULE宏无关,设备文件是驱动注册设备时创建的。MODULE宏是生成的ko文件名称。
	
.PHONY:clean
clean:
	rm -rf *.ko *.o  *.mod *.mod.c *.symvers *.order .*.cmd