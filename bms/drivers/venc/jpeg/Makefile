# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y
CUSTOM_SETTING_FLAGS =  
COMMON_SOURCE_DIR = ../
# show the path to compiler, where to find header files and libraries
CUSTOM_INCLUDE = -I.  -I$(COMMON_SOURCE_DIR)/dwl \
          -I$(COMMON_SOURCE_DIR)/common  -I$(SRCTREE)/include/venc \
          -I$(COMMON_SOURCE_DIR)/jpeg

# compiler switches
CUSTOM_CFLAGS ?= -w -Wstrict-prototypes -D__KERNEL__   $(CUSTOM_INCLUDE) $(CUSTOM_DEBFLAGS)  $(CUSTOM_SETTING_FLAGS)

# list of used sourcefiles
SRCS := \
	EncJpeg.c \
	EncJpegCodeFrame.c \
	EncJpegInit.c \
	EncJpegPutBits.c \
	JpegEncApi.c \
	../common/encasiccontroller.c \
	../common/encasiccontroller_v2.c \
	../common/encpreprocess.c \
	../common/encswhwregisters.c\


# name of the outputfile (library)
ARCHIVE = drv_venc_jpeg.a

#sinclude $(OUTPUT)/.depend
include $(BUILD_LIB)
