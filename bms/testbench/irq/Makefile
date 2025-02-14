ARCHIVE := testbench_irq.a

ifdef CONFIG_PLIC
srcs-y += \
	irq-plic-main.c
else
srcs-y += \
	irq-clic-main.c
endif

