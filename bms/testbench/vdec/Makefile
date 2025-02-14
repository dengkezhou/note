ARCHIVE := testbench_vdec.a

DWL_DIR := dwl
CTRL_SW := ctrl_sw

CFLAGS += \
	-DNON_PTHREAD_H \
	-D__BARE_METAL__ \
	-DFIFO_DATATYPE=void* \
	-DCUSTOM_UNIQUE_ID=0xdeadbeef \
	-DENABLE_H264_SUPPORT \
	-DENABLE_HEVC_SUPPORT \
	-DENABLE_JPEG_SUPPORT

CFLAGS += \
	-I$(SRCTREE)/drivers/vdec/$(DWL_DIR) \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/inc \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/common \
	-I$(SRCTREE)/drivers/vdec/$(CTRL_SW)/config

srcs-y += vdec-tb.c localcase.c

ifdef CONFIG_COMPILE_RTL
CFLAGS += -DVDEC_RTL_NOCMP
endif
