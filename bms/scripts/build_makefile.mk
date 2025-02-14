-include $(KCONFIG_AUTOCONFIG)

srcs-y :=
libs-y :=

kbuild-dir := $(subst $(OBJTREE), $(SRCTREE), $(OUTPUT))
kbuild-file := $(kbuild-dir)/Makefile

CURDIR := $(kbuild-dir)

include $(kbuild-file)

SRCS := $(sort $(srcs-y))
LIBS := $(sort $(libs-y))

ifneq ($(ARCHIVE),)
#for wildcard
ifneq ($(findstring $(wildcard $(CURDIR)), $(SRCS)),)
SRCS := $(subst $(wildcard $(CURDIR))/,, $(SRCS))
endif
include $(BUILD_LIB)
endif

ifneq ($(subdirs-y),)
include $(BUILD_SUBDIRS)
endif
