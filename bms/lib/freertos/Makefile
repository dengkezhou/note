
ARCHIVE := lib_freertos.a

FREERTOS_KERNEL_BASE = $(CURDIR)/Source

CUSTOM_AFLAGS := 	-I${FREERTOS_KERNEL_BASE}/portable/GCC/riscv/chip_specific_extensions/thead_c910_rv64imafdc -I$(SRCTREE)/include
CUSTOM_CFLAGS += 	-I${FREERTOS_KERNEL_BASE}/include \
			-I${FREERTOS_KERNEL_BASE}/portable/GCC/riscv \
			-I${FREERTOS_KERNEL_BASE} \
			-I${FREERTOS_KERNEL_BASE}/.. \
			-I${FREERTOS_KERNEL_BASE}/portable/GCC/riscv/chip_specific_extensions/thead_c910_rv64imafdc	\
			-I$(SRCTREE)/include

srcs-y += \
		${FREERTOS_KERNEL_BASE}/event_groups.c \
		${FREERTOS_KERNEL_BASE}/queue.c \
		${FREERTOS_KERNEL_BASE}/timers.c \
		${FREERTOS_KERNEL_BASE}/tasks.c \
		${FREERTOS_KERNEL_BASE}/list.c \
		${FREERTOS_KERNEL_BASE}/portable/MemMang/heap_4.c \
		${FREERTOS_KERNEL_BASE}/portable/GCC/riscv/port.c \
		${FREERTOS_KERNEL_BASE}/portable/GCC/riscv/portASM.S \
		${FREERTOS_KERNEL_BASE}/portable/GCC/riscv/stub_function.c \
