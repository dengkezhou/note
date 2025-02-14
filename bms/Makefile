include scripts/env.mk
include scripts/common.mk

subdirs-$(CONFIG_COMPILE_DRV) += drivers
subdirs-$(CONFIG_COMPILE_LIB) += lib  
subdirs-$(CONFIG_COMPILE_TBH) += testbench
subdirs-$(CONFIG_COMPILE_ARCH) += arch

include $(BUILD_SUBDIRS)
include $(BUILD_BINARY)
