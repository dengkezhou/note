ARCHIVE := testbench_cpu.a
CUSTOM_CFLAGS += -I$(CURDIR) -DTIME -DNOENUM -Wno-implicit -fno-builtin-printf -fno-common -falign-functions=4 -DDHRY_ITERS=1000000 -DPERFORMANCE_RUN=1 -DITERATIONS=10 -I. -I$(SRCTREE)/include
CUSTOM_AFLAGS += -I$(CURDIR) -DTIME -DNOENUM -Wno-implicit -fno-builtin-printf -fno-common -falign-functions=4 -DDHRY_ITERS=1000000 -DPERFORMANCE_RUN=1 -DITERATIONS=10 -I. -I$(SRCTREE)/include
srcs-y += \
	dhrystone/dhry_1.c \
	dhrystone/dhry_2.c \
	coremark/core_list_join.c	\
	coremark/core_main.c \
	coremark/core_matrix.c	\
	coremark/core_state.c	\
	coremark/core_util.c	\
	pmu.c

ifndef CONFIG_E902
srcs-y += pmu.c
endif

srcs-$(CONFIG_64BIT) += \
	coremark/linux64/core_portme.c

srcs-$(CONFIG_32BIT) += \
	coremark/linux/core_portme.c

srcs-$(CONFIG_E906) += \
	cpu-e906-main.c

srcs-$(CONFIG_C920) += \
	cpu-c920-main.c

srcs-$(CONFIG_E902) += \
	cpu-e902-main.c
