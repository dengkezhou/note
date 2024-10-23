## linux 内核链接脚本

链接最终使用的脚本是 arch/$(ARCH)/kernel/vmlinux.lds

该文件由 arch/$(ARCH)/kernel/vmlinux.lds.S 生成。

内核各个段的vma 和 lma 相差了LOAD_OFFSET，LOAD_OFFSET也是编译后vmlinux的起始地址。

```c
// include/asm-generic/vmlinux.lds.h
/* Section used for early init (in .S files) */
#define HEAD_TEXT  KEEP(*(.head.text))

#define HEAD_TEXT_SECTION                           \
    .head.text : AT(ADDR(.head.text) - LOAD_OFFSET) {       \
        HEAD_TEXT                       \
    }

```

看起来，vma更像是从0地址开始的偏移。

### 问题记录

### 1 debug信息

打开debug_info，将vmlinux通过gdbserver加载到FPGA的ddr中，ddr的起始地址为0x100000000，发现运行的debug信息和运行信息对应不上。

观察pc指针虽然指向了0x100000000，gdb反汇编正常，但在源文件中显现执行的却是free_initmem，该函数是.text段的第一个函数。

修改链接脚本，将 _start函数所在的.head.text段去掉，将其中内容放在.text段首部，编译重现执行，运行正常。

原因待查。

