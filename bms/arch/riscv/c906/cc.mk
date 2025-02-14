COPTIONS := -march=rv64gcvxthead -mabi=lp64v -mcmodel=medlow
CFLAGS := ${HEADER} -I$(OBJTREE)/include -Os -ffunction-sections -fdata-sections \
	-Wall -c -g2 -fno-builtin -D__KERNEL__ -include sys/cdefs.h $(COPTIONS)
AFLAGS := -Wall -c -g2 -x assembler-with-cpp $(COPTIONS)
ARFLAGS := cr
LDFLAGS := -nostartfiles -static -nostdlib -L. -Wl,-gc-sections $(COPTIONS) \

# linker script
LDFLAGS += -T$(SRCTREE)/arch/riscv/c906/link.lds

TARGET := c906
BINARY ?= $(TARGET).elf

export CFLAGS ARFLAGS AFLAGS LDFLAGS TARGET BINARY

libs-$(CONFIG_LIB_COMMAND) += lib_command.a
libs-$(CONFIG_LIB_MATH) += lib_math.a
libs-$(CONFIG_LIB_SHELL) += lib_shell.a
libs-$(CONFIG_LIB_STDLIB) += lib_stdlib.a
libs-$(CONFIG_LIB_COMMON) += lib_common.a
libs-$(CONFIG_LIB_CONSOLE) += lib_console.a
libs-$(CONFIG_LIB_CRYPTO) += lib_crypto.a
libs-$(CONFIG_LIB_INTERRUPT) += lib_interrupt.a
libs-$(CONFIG_LIB_RTLFS) += lib_rtlfs.a
libs-$(CONFIG_LIB_FREERTOS) += lib_freertos.a

libs-$(CONFIG_DRV_DMA) += drv_dma.a
libs-$(CONFIG_DRV_SYSM) += drv_sysm.a

libs-$(CONFIG_TBH_CPU) += testbench_cpu.a
libs-$(CONFIG_TBH_DMA) += testbench_dma.a
libs-$(CONFIG_TBH_IRQ) += testbench_irq.a
libs-$(CONFIG_TBH_RTLFS) += testbench_rtlfs.a
libs-$(CONFIG_TBH_SKULL) += testbench_skull.a
libs-$(CONFIG_TBH_TASK) += testbench_task.a

libs-y += arch_$(TARGET).a
