ARCHIVE := testbench_sdmmc.a

CORE_DIR := cdns/core_driver
DFI_DIR := cdns/ccpf_driver
DRIVER_DIR := cdns/driver
CFLAGS += \
		-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/common \
		-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/include \
		-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/src \
		-I$(SRCTREE)/drivers/sdmmc/$(DFI_DIR)/include \
		-I$(SRCTREE)/drivers/sdmmc/$(DFI_DIR)/src \
		-I$(SRCTREE)/drivers/sdmmc/$(DRIVER_DIR)

srcs-y += \
	sdmmc-main.c \
	mmcburn.c
