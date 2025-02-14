
ARCHIVE := testbench_task.a

COMMON_SOURCE_DIR = ./#$(pwd)
FREERTOS_KERNEL_DIR		  = $(COMMON_SOURCE_DIR)/../../lib/freertos
FREERTOS_KERNEL_BASE = $(FREERTOS_KERNEL_DIR)/FreeRTOS-Kernel

# show the path to compiler, where to find header files and libraries
CUSTOM_INCLUDE = -I.  \
		-I$(COMMON_SOURCE_DIR) \
		-I$(COMMON_SOURCE_DIR)/../../include \
		-I${FREERTOS_KERNEL_BASE}/include \
		-I$(FREERTOS_KERNEL_DIR) \
		-I${FREERTOS_KERNEL_BASE}/portable/GCC/RISC-V

srcs-y += \
		task-main.c
CUSTOM_CFLAGS ?=  $(CUSTOM_INCLUDE) -Wstrict-prototypes -D__KERNEL__ -O0  
