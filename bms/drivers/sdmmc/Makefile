ARCHIVE := drv_sdmmc.a

CORE_DIR := cdns/core_driver
DRIVER_DIR := cdns/driver

CFLAGS += -D __BARE_METAL__ -Wno-address-of-packed-member
CFLAGS += \
		-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/common \
		-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/include \
		-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/src \
		-I$(SRCTREE)/drivers/sdmmc/$(DRIVER_DIR)

srcs-y += \
		$(CORE_DIR)/src/csdd_obj_if.c \
		$(CORE_DIR)/src/csdd_sanity.c \
		$(CORE_DIR)/src/sdio_card_general.c \
		$(CORE_DIR)/src/sdio_cq.c \
		$(CORE_DIR)/src/sdio_debug.c \
		$(CORE_DIR)/src/sdio_dma.c \
		$(CORE_DIR)/src/sdio_errors.c \
		$(CORE_DIR)/src/sdio_host.c \
		$(CORE_DIR)/src/sdio_memory_card.c \
		$(CORE_DIR)/src/sdio_phy.c \
		$(CORE_DIR)/src/sdio_request.c \
		$(CORE_DIR)/src/sdio_sd4_host.c \
		$(CORE_DIR)/src/sdio_utils.c \
		$(CORE_DIR)/src/sdio.c \
		$(DRIVER_DIR)/cps_bm.c \
		$(DRIVER_DIR)/dfi.c \
		sdmmc.c

