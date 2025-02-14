# Comment/uncomment the following line to disable/enable debugging
DEBUG = y
CUSTOM_SETTING_FLAGS = -DDEC_X170_OUTPUT_FORMAT=DEC_X170_OUTPUT_FORMAT_RASTER_SCAN
COMMON_SOURCE_DIR = ../
# show the path to compiler, where to find header files and libraries
CUSTOM_INCLUDE = -I.  -I$(COMMON_SOURCE_DIR)/dwl \
          -I$(COMMON_SOURCE_DIR)/avs -I$(COMMON_SOURCE_DIR)/config \
          -I$(COMMON_SOURCE_DIR)/common  -I$(SRCTREE)/include/vdec

# compiler switches
CUSTOM_CFLAGS ?= -w -Wstrict-prototypes -D__KERNEL__   $(CUSTOM_INCLUDE) $(CUSTOM_DEBFLAGS)  $(CUSTOM_SETTING_FLAGS)

# list of used sourcefiles
SRC_AVS := \
	avsdecapi.c \
	avsdecapi_internal.c \
	avs_strm.c \
	avs_headers.c \
	avs_utils.c \
	avs_vlc.c \
	../common/regdrv.c \
	../common/refbuffer.c \
	../common/tiledref.c \
	../common/bqueue.c

SRCS = $(SRC_AVS)

# name of the outputfile (library)
ARCHIVE = drv_vdec_avs.a

#sinclude $(OUTPUT)/.depend
include $(BUILD_LIB)
