
ARCHIVE := arch_c906.a

CUSTOM_AFLAGS := -Iboard/smarth_c906_evb/include -Icsi_core/include \
	-Icsi_driver/include -Icsi_driver/smarth_rv64/include -I.
CUSTOM_CFLAGS := -Iboard/smarth_c906_evb/include -Icsi_core/include \
	-Icsi_driver/include -Icsi_driver/smarth_rv64/include -I.

srcs-y += \
	   board/smarth_c906_evb/board_init.c \
	   csi_driver/smarth_rv64/system.c \
	   csi_driver/smarth_rv64/ck_irq.c \
	   csi_driver/smarth_rv64/novic_irq_tbl.c \
	   csi_driver/smarth_rv64/dw_timer.c \
	   csi_driver/smarth_rv64/ck_usart.c \
	   csi_driver/smarth_rv64/trap_c.c \
	   csi_driver/smarth_rv64/dw_gpio.c \
	   csi_driver/smarth_rv64/isr.c \
	   csi_driver/smarth_rv64/lib.c \
	   csi_driver/smarth_rv64/pinmux.c \
	   csi_driver/smarth_rv64/sys_freq.c \
	   csi_driver/smarth_rv64/devices.c \
	   csi_driver/smarth_rv64/startup.S \
	   csi_driver/smarth_rv64/vectors.S \
	   wrapper.c	\
		 main.c
