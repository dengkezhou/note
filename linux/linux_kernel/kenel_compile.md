# linux内核编译

## 一、编译命令

内核源码路径: [Index of /pub/linux/kernel/v5.x/](https://cdn.kernel.org/pub/linux/kernel/v5.x/) 

make ARCH=riscv  menuconfig

make ARCH=ricsv CROSS_COMPILE=riscv-xxx-

配置menuconfig时ARCH变量没有保存在.config中，所以cmd每次执行都需要声明ARCH的目标。

## 二、编译流程

### 2.1 menuconfig

使用mconf 脚本，以.config为基础生成新配置的.config。

所以在第一次执行make menuconfig 时，通常是选择对应arch目录下的configs复制为.config，或新建一个空的.config。

```makefile
# script/Kconfig/Makefile
Kconfig := $(KBUILD_KCONFIG)
menuconfig: $(obj)/mconf
    $(Q)$< $(silent) $(Kconfig)
    
# Makefile
KCONFIG_CONFIG ?= .config
```

.config在Make menuconfig 后生成，在make时也是作为第一个依赖被检查。

```makefile
# Makefile实现  
KCONFIG_CONFIG ?= .config

# include的文件被作为目标时，会在执行总目标之前执行该目标。
include include/config/auto.conf.cmd

%/config/auto.conf %/config/auto.conf.cmd %/generated/autoconf.h: $(KCONFIG_CONFIG)
    +$(call cmd,syncconfig)
    
$(KCONFIG_CONFIG):
    @echo >&2 '***'
    @echo >&2 '*** Configuration file "$@" not found!'
```

### 2.2 __all

Makefile 默认的总目标为 __all，但该目标不能在cmd命令行上指定。

```makefile
# MAKECMDGOALS 是Makefile自动化变量，是命令行指定的目标列表。
$(if $(filter __%, $(MAKECMDGOALS)), \
    $(error targets prefixed with '__' are only for internal use))
```

__all的依赖有两种，all、modules ，用来区分编译内核和编译模块。

```makefile
ifeq ($(KBUILD_EXTMOD),)
__all: all
else
__all: modules
endif

# Use make M=dir or set the environment variable KBUILD_EXTMOD to specify the
# directory of external module to build. Setting M= takes precedence.
ifeq ("$(origin M)", "command line")
  KBUILD_EXTMOD := $(M) 
endif
```

所以编译内核模块是通常在源码目录下执行make，在编译驱动模块时，使用命令如下，因为"__all"
 不能作为cmd目标，所以指定modules为总目标。

根据 _ _all 的依赖来看，当cmd指定了M变量时，可以使用默认目标编译驱动模块，但很少看见这样使用，大多数还是使用cmd指定了modules为目标。

```makefile
# /lib/modules/$(shell uname -r)/build 是主机的内核源码目录，使用交叉编译时，该目录需要改变为目标内核的目录。
# M变量是驱动的顶层目录。
all :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
```

当然，编译内核时也包括编译模块

```makefile
ifdef CONFIG_MODULES
# By default, build modules as well
all: modules
...
endif
```

### 2.3 编译内核

当使用默认目标或指定all为目标时，编译整个内核。

all依赖于vmlinux ,一般arch/$(ARCH)/Makefile中也会添加Image作为all的依赖。

```makefile
# Makefile 
SRCARCH     := $(ARCH)
include arch/$(SRCARCH)/Makefile
all: vmlinux

# arch/riscv/Makefile
KBUILD_IMAGE := $(boot)/Image.gz
all: $(notdir $(KBUILD_IMAGE))
```

vmlinux的依赖 vmlinux-deps 指定需要编译的模块和链接脚本。在配置过程中使用libs-y 、drivers-y选择编译的目标。

```makefile
# Makefile
vmlinux: scripts/link-vmlinux.sh autoksyms_recursive $(vmlinux-deps) FORCE
    +$(call if_changed,link-vmlinux)

export KBUILD_LDS          := arch/$(SRCARCH)/kernel/vmlinux.lds
KBUILD_VMLINUX_LIBS := $(patsubst %/,%/lib.a, $(libs-y))
KBUILD_VMLINUX_OBJS += $(patsubst %/,%/built-in.a, $(drivers-y))
vmlinux-deps := $(KBUILD_LDS) $(KBUILD_VMLINUX_OBJS) $(KBUILD_VMLINUX_LIBS)
```

vmlinux执行的命令为 cmd_link-vmlinux (if_changed最终的返回)，使用scripts/link-vmlinux.s链接模块生成目标vmlinux。

```makefile
# Final link of vmlinux with optional arch pass after final link
cmd_link-vmlinux =                                                 \
    $(CONFIG_SHELL) $< "$(LD)" "$(KBUILD_LDFLAGS)" "$(LDFLAGS_vmlinux)";    \
    $(if $(ARCH_POSTLINK), $(MAKE) -f $(ARCH_POSTLINK) $@, true)
```

### 2.4 编译模块

编译内核或指定目标为modules时，都会编译modules。

```makefile
# Build modules
#
# A module can be listed more than once in obj-m resulting in
# duplicate lines in modules.order files.  Those are removed
# using awk while concatenating to the final file.

PHONY += modules
modules: $(if $(KBUILD_BUILTIN),vmlinux) modules_check modules_prepare
    $(Q)$(MAKE) -f $(srctree)/scripts/Makefile.modpost
PHONY += modules_check
modules_check: modules.order
    $(Q)$(CONFIG_SHELL) $(srctree)/scripts/modules-check.sh $<

cmd_modules_order = $(AWK) '!x[$$0]++' $(real-prereqs) > $@

modules.order: $(subdir-modorder) FORCE
    $(call if_changed,modules_order)

targets += modules.order

# Target to prepare building external modules
PHONY += modules_prepare
modules_prepare: prepare
    $(Q)$(MAKE) $(build)=scripts scripts/module.lds
```

编译外部驱动时需要使用变量"M"指定驱动路径

```makefile
# linux/Makefile

# Use make M=dir or set the environment variable KBUILD_EXTMOD to specify the
# directory of external module to build. Setting M= takes precedence.
ifeq ("$(origin M)", "command line")
  KBUILD_EXTMOD := $(M)
endif

build-dir := $(KBUILD_EXTMOD)

#编译驱动相关的 mod.dep 等文件也会放在该目录下
export extmod_prefix = $(if $(KBUILD_EXTMOD),$(KBUILD_EXTMOD)/)
export MODORDER := $(extmod_prefix)modules.order
export MODULES_NSDEPS := $(extmod_prefix)modules.nsdeps
```



### Makefile中的命令

if_changed，顾名思义，当依赖更新时才执行该命令。

真正执行的命令是 cmd_$(1)

```makefile
#scripts/Kbuild.include 

# PHONY targets skipped in both cases.
newer-prereqs = $(filter-out $(PHONY),$?)
# Execute command if command has changed or prerequisite(s) are updated.
if_changed = $(if $(newer-prereqs)$(cmd-check),                              \
    $(cmd);                                                              \
    printf '%s\n' 'cmd_$@ := $(make-cmd)' > $(dot-target).cmd, @:)
    
# printing commands
cmd = @set -e; $(echo-cmd) $(cmd_$(1))
```

 
