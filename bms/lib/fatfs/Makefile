
ARCHIVE := lib_fatfs.a

CORE_DIR := cdns/core_driver
CFLAGS += \
	-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/common \
	-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/include \
	-I$(SRCTREE)/drivers/sdmmc/$(CORE_DIR)/src

srcs-y += \
	ff.c \
	diskio.c \
	ffunicode.c \
	ffsystem.c \
	fatfs.c

ifdef CONFIG_FS_API_WRAPPER
srcs-y += \
	fs-wrapper.c
endif
