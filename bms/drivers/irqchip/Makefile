
ARCHIVE := drv_irqchip.a

ifdef CONFIG_PLIC
srcs-y += \
				irq-sifive-plic.c
else
srcs-y += \
				irq-clic.c
endif
