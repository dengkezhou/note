
ARCHIVE := arch_$(TARGET).a

CUSTOM_AFLAGS := -Iboard/smarth_$(MACHINE)_evb/include -Icsi_core/include \
	-Icsi_driver/include -Icsi_driver/smarth_rv64/include -I. -I$(SRCTREE)/include
CUSTOM_CFLAGS += -Iboard/smarth_$(MACHINE)_evb/include -Icsi_core/include \
	-Icsi_driver/include -Icsi_driver/smarth_rv64/include -I. -I$(SRCTREE)/include

srcs-y += \
	   startup.S \
		 mtrap.S \
		 timer-m.c	\
		 suspend_entry.S \
		 main.c	

ifdef CONFIG_COMPILE_SIM
srcs-y += \
		serial-dwc.c
else
srcs-y += \
		serial-cadence.c
endif
