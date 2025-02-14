# name of the outputfile (library)
ARCHIVE = drv_venc.a

# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y
INCLUDE_H264 = y
INCLUDE_JPEG = y
#INCLUDE_VP8 = y
INCLUDE_VIDSTAB = y
INCLUDE_ENC_COMMON=n
INCLUDE_TESTING=n
EWL_POLLING_ENABLE=y

# list of used sourcefiles
SRCS_JPEG := \
	jpeg/EncJpeg.c \
	jpeg/EncJpegCodeFrame.c \
	jpeg/EncJpegInit.c \
	jpeg/EncJpegPutBits.c \
	jpeg/JpegEncApi.c \


SRCS_H264 := \
	h264/H264Cabac.c\
	h264/H264CodeFrame.c\
	h264/h264encapi_ext.c \
	h264/H264Init.c\
	h264/H264Mad.c \
	h264/H264NalUnit.c\
	h264/H264PictureBuffer.c\
	h264/H264PictureParameterSet.c\
	h264/H264PutBits.c\
	h264/H264RateControl.c\
	h264/H264Sei.c \
	h264/H264SequenceParameterSet.c\
	h264/H264Slice.c\
	h264/H264EncApi.c\

SRCS_VP8  := \
	vp8/vp8codeframe.c\
	vp8/vp8init.c\
	vp8/vp8putbits.c\
	vp8/vp8header.c\
	vp8/vp8picturebuffer.c\
	vp8/vp8picparameterset.c\
	vp8/vp8entropy.c\
	vp8/vp8macroblocktools.c\
	vp8/vp8ratecontrol.c\
	vp8/vp8encapi.c

SRCS_CAMSTAB := \
	vidstab/vidstabalg.c     \
	vidstab/vidstabapi.c \
	vidstab/vidstabcommon.c \
	vidstab/vidstabinternal.c

SRCS_COMMON :=  \
	common/encasiccontroller_v2.c \
	common/encasiccontroller.c \
	common/encpreprocess.c \
	common/encswhwregisters.c \

SRCS_EWL :=\
	ewl/ewl_x280_common.c \
	ewl/ewl_x280_irq.c \
	ewl/imapx_enc_irq.c

SRCS_TESTING := \
	vp8/vp8testid.c \
	h264/H264TestId.c
	
# Combine the list of all the source files included in the library build
ifeq ($(INCLUDE_H264),y)
	SRCS += $(SRCS_H264)
	INCLUDE_ENC_COMMON=y
endif
ifeq ($(INCLUDE_VP8),y)
	SRCS += $(SRCS_VP8)
	INCLUDE_ENC_COMMON=y
endif
ifeq ($(INCLUDE_JPEG),y)
	SRCS += $(SRCS_JPEG) 
	INCLUDE_ENC_COMMON=y
endif
ifeq ($(INCLUDE_VIDSTAB),y)
	SRCS += $(SRCS_CAMSTAB)
	CUSTOM_DEBFLAGS += -DVIDEOSTAB_ENABLED
	CONFFLAGS += -DVIDEOSTAB_ENABLED
endif
ifeq ($(INCLUDE_TESTING),y)
	SRCS += $(SRC_TESTING)
	CUSTOM_DEBFLAGS += -DINTERNAL_TEST
endif

# add common encoder files
ifeq ($(INCLUDE_ENC_COMMON),y)
	SRCS += $(SRCS_COMMON)
	SRCS += $(SRCS_EWL)
endif

srcs-y += $(SRCS)

# compiler switches
CUSTOM_CFLAGS ?= -w -Wstrict-prototypes -D__KERNEL__   $(CUSTOM_INCLUDE) $(CUSTOM_DEBFLAGS) -O0 

CUSTOM_SETTING_FLAGS ?=   
COMMON_SOURCE_DIR = ./
# show the path to compiler, where to find header files and libraries
CUSTOM_INCLUDE += -I.  \
		  -I$(COMMON_SOURCE_DIR)/inc \
		  -I$(COMMON_SOURCE_DIR)/ewl \
          -I$(COMMON_SOURCE_DIR)/common \
          -I$(COMMON_SOURCE_DIR)/jpeg \
          -I$(COMMON_SOURCE_DIR)/h264 \
          -I$(COMMON_SOURCE_DIR)/vp8 \
          -I$(COMMON_SOURCE_DIR)/vidstab \

