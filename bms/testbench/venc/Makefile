ARCHIVE := testbench_venc.a

CUSTOM_INCLUDE += -I$(SRCTREE)/drivers/venc/inc \
				  -I./

ifdef CONFIG_DRV_VENC
SRCS += venc-main.c\
		jpeg-encode.c \
		video-stable-encode.c \
		venc-common.c \
		h264-encode.c 

#		h264-api.c 
#		h1-encode.c \
#		h2-encode.c \

endif

ifdef CONFIG_TBH_VENC_JOINT_TEST
     CFLAGS += -DVENC_JOINT_TEST
endif

ifdef CONFIG_TBH_VENC_SPEED_TEST
     CFLAGS += -DDEBUG_VENC_SPEED_TEST
endif

SRCS += $(wildcard localcase/*.c)


srcs-y += $(SRCS)

CUSTOM_CFLAGS += $(CUSTOM_INCLUDE)
