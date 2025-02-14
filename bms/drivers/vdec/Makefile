ARCHIVE := drv_vdec.a

DWL_DIR := dwl
CTRL_SW := ctrl_sw

CFLAGS += -Wno-address-of-packed-member \
	-DNON_PTHREAD_H \
	-D__BARE_METAL__ \
	-DFIFO_DATATYPE=void* \
	-DCUSTOM_UNIQUE_ID=0xdeadbeef

CFLAGS += \
	-I$(SRCTREE)/drivers/vdec/$(DWL_DIR) \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/inc \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/common \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/config

ifdef CONFIG_DRV_VDEC_H264
CFLAGS += \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/h264high \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/h264high/legacy \
	-DENABLE_H264_SUPPORT
endif

ifdef CONFIG_DRV_VDEC_HEVC
CFLAGS += \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/hevc \
	-DENABLE_HEVC_SUPPORT
endif

ifdef CONFIG_DRV_VDEC_JPEG
CFLAGS += \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/jpeg \
	-DENABLE_JPEG_SUPPORT
endif

DWL_SRCS  := $(wildcard ${DWL_DIR}/*.c)
COMMON_SRCS := $(shell find $(CTRL_SW)/common -name '*.c')
H264_SRCS := $(shell find $(CTRL_SW)/h264high -name '*.c')
HEVC_SRCS := $(shell find $(CTRL_SW)/hevc -name '*.c')
JPEG_SRCS := $(shell find $(CTRL_SW)/jpeg -name '*.c')

srcs-y += vdec.c

ifdef CONFIG_DRV_VDEC_H264
srcs-y += $(H264_SRCS)
NEED_COMMON_SRC := 1
endif

ifdef CONFIG_DRV_VDEC_HEVC
srcs-y += $(HEVC_SRCS)
NEED_COMMON_SRC := 1
endif

ifdef CONFIG_DRV_VDEC_JPEG
srcs-y += $(JPEG_SRCS)
NEED_COMMON_SRC := 1
endif

ifeq ($(NEED_COMMON_SRC), 1)
srcs-y += $(DWL_SRCS) $(COMMON_SRCS)
endif
