
OBJTREE		:= $(CURDIR)/out
SRCTREE		:= $(CURDIR)
		
$(shell [ -d ${OBJTREE} ] || mkdir -p ${OBJTREE})
$(shell [ -d ${OBJTREE}/built_archives ] || mkdir -p ${OBJTREE}/built_archives)
$(shell [ -d ${OBJTREE}/include ] || mkdir -p ${OBJTREE}/include)
$(shell echo "#define BMS_COMMIT_ID \"commit `git log -1 | head -1 | cut -f2 -d' '`\"" > $(OBJTREE)/include/version.h)
$(shell echo "#define BMS_COMPILE_INFO \"`logname`@`hostname`, `date +"%D %T"`\"" >> $(OBJTREE)/include/version.h)
$(shell mktemp > $(OBJTREE)/.force)
FORCE := $(OBJTREE)/.force
export	SRCTREE OBJTREE FORCE

CROSS_COMPILE := /opt/toolchain/t-head-rv64/bin/riscv64-unknown-elf-

CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)ld
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy

export CC AR LD OBJDUMP OBJCOPY

HEADER := include \
		  include/common \
		  include/stdlib \
		  include/drivers \
		  include/stdlib/sys

HEADER := $(addprefix -I$(SRCTREE)/, $(HEADER))
export HEADER 

MAKE := make -s
export MAKE

BUILD_LIB := $(SRCTREE)/scripts/build_lib.mk
BUILD_SUBDIRS := $(SRCTREE)/scripts/build_subdirs.mk
BUILD_BINARY := $(SRCTREE)/scripts/build_binary.mk
export BUILD_LIB BUILD_SUBDIRS BUILD_BINARY

include $(BUILD_SUBDIRS)

OUTPUT := $(OBJTREE)

KCONFIG_CONFIG  ?= $(OBJTREE)/.config
export KCONFIG_CONFIG
KCONFIG_AUTOCONFIG ?= $(SRCTREE)/include/config/auto.conf
export KCONFIG_AUTOCONFIG

config-target := 0
mixed-target := 0
dot-config := 1

no-dot-config-targets := clean help

ifneq ($(filter $(no-dot-config-targets), $(MAKECMDGOALS)),)
	ifeq ($(filter-out $(no-dot-config-targets), $(MAKECMDGOALS)),)
		dot-config := 0
	endif
endif

ifneq ($(filter config %config, $(MAKECMDGOALS)),)
	config-target := 1
	ifneq ($(words $(MAKECMDGOALS)), 1)
			mixed-target := 1
	endif
endif

ifeq ($(mixed-target), 1)
# We're called with mixed targets (*config and build targets)
# Handle them one by one

PHONY += $(MAKECMDGOALS) __build_one_by_one

$(filter-out __build_one_by_one, $(MAKECMDGOALS)): __build_one_by_one
	@:
__build_one_by_one:
	$(Q)set -e; \
	for i in $(MAKECMDGOALS); do \
		$(MAKE) -f $(SRCTREE)/Makefile $$i; \
	done
else

ifeq ($(config-target), 1)
config: FORCE
	@$(MAKE) -f $(SRCTREE)/scripts/Makefile $@
%config: FORCE
	@$(MAKE) -f $(SRCTREE)/scripts/Makefile $@
else

ifeq ($(dot-config), 1)
# Read in config
-include $(KCONFIG_AUTOCONFIG)

# Read in dependencies to all Kconfig* files, make sure to run
# oldconfig if changes are detected.
-include include/config/auto.conf.cmd

# To avoid any implicit rule to kick in, define an empty command
$(KCONFIG_CONFIG) include/config/auto.conf.cmd: ;
# If .config is newer than include/config/auto.conf, someone tinkered
# with it and forgot to run make oldconfig.
# if auto.conf.cmd is missing then we are probably in a cleaned tree so
# we execute the config step to be sure to catch updated Kconfig files
$(KCONFIG_AUTOCONFIG): $(KCONFIG_CONFIG) include/config/auto.conf.cmd
	@$(MAKE) -f $(SRCTREE)/scripts/Makefile silentoldconfig
endif

-include $(KCONFIG_AUTOCONFIG)

PHONY += help clean
help:
	@echo  'Cleaning targets:'
	@echo  'clean - Remove most generated files but keep the config'
	@$(MAKE) -f $(SRCTREE)/scripts/Makefile help
clean:
	@rm -rf out/
	@$(MAKE) -f $(SRCTREE)/scripts/Makefile clean
endif
endif

PHONY += FORCE
FORCE:

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
