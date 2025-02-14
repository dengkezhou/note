
CROSS_COMPILE := ${TOOLCHAIN_LINARO_A64}

CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)ld
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy

COPTIONS := -g3 -march=armv8-a
CFLAGS := ${HEADER} -I$(OBJTREE)/include -Os -ffunction-sections -fdata-sections \
	-Wall -c -fno-builtin -D__KERNEL__ -include sys/cdefs.h $(COPTIONS)
AFLAGS := -Wall -c -x assembler-with-cpp $(COPTIONS)
ARFLAGS := cr
LDFLAGS := -nostartfiles -static -nostdlib -L. -Wl,-gc-sections -Wl,--build-id=none $(COPTIONS) \

# linker script
LDFLAGS += -T$(SRCTREE)/drivers/core-q3/link.lds

export CC AR LD OBJDUMP OBJCOPY
export CFLAGS ARFLAGS AFLAGS LDFLAGS