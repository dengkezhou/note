
ARCHIVE := arch_$(TARGET).a

CUSTOM_AFLAGS := -Iboard/smartl_$(MACHINE)_evb/include -Icsi_core/include \
	-Icsi_driver/include -Icsi_driver/smartl_rv32/include -I. -I$(SRCTREE)/include
CUSTOM_CFLAGS += -Iboard/smartl_$(MACHINE)_evb/include -Icsi_core/include \
	-Icsi_driver/include -Icsi_driver/smartl_rv32/include -I. -I$(SRCTREE)/include

srcs-y += \
	   startup.S \
		 mtrap.S \
		 timer-m.c

ifdef CONFIG_COMPILE_ROM
srcs-y += \
			rom-main.c	

ifndef CONFIG_TB_RUN_IRAM
ifdef CONFIG_COMPILE_ASIC
srcs-y += \
			lpddr4-asic.c
else
srcs-y += \
			lpddr4.c
endif
endif

else
srcs-y += \
			soc-main.c	
endif

ifdef CONFIG_COMPILE_SIM
srcs-y += \
		serial-dwc.c
else
srcs-y += \
		serial-cadence.c
endif
