ARCHIVE := testbench_drd.a
CDNS := ../../drivers/drd/cdns
CORE_DIR := ../../drivers/drd/cdns/core_driver
DEV_IF_DIR := ../../drivers/drd/cdns/dev_if
HOST_IF_DIR := ../../drivers/drd/cdns/host_if
DEVICE_DIR := ../../drivers/drd/device

CFLAGS += \
		-I$(CORE_DIR)/common/include -I$(CORE_DIR)/common/src\
		-I$(CORE_DIR)/device/include -I$(CORE_DIR)/device/src\
		-I$(CORE_DIR)/drd/include -I$(CORE_DIR)/drd/src\
		-I$(CORE_DIR)/host/include -I$(CORE_DIR)/host/src\
		-I$(DEV_IF_DIR) -I$(HOST_IF_DIR) -I$(CDNS) -I$(DEVICE_DIR)\
		-D __BARE_METAL__ -Wno-address-of-packed-member
srcs-y += \
	usb-main.c \

