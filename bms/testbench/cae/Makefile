ARCHIVE := testbench_cae.a

TMP_TOP_DIR = ../../drivers/cae/rambus_ddk

INCLUDE_CONF := \
		-I$(TMP_TOP_DIR)/conf

INCLUDE_EXAMPLES := \
		-I$(TMP_TOP_DIR)/Examples/DemoApp_PEC/src

INCLUDE_INTEGRATION := \
		-I$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src \
		-I$(TMP_TOP_DIR)/Integration/SLAD_Adapter/incl \
		-I$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/AXI4 \
		-I$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/lkm \
		-I$(TMP_TOP_DIR)/Integration/SHDevXS/incl \
		-I$(TMP_TOP_DIR)/Integration/UMDevXS/KernelPart/incl \
		-I$(TMP_TOP_DIR)/Integration/DriverFramework/src/LKM \
		-I$(TMP_TOP_DIR)/Integration/DriverFramework/src/LKM/AXI4 \
		-I$(TMP_TOP_DIR)/Integration/DriverFramework/src

INCLUDE_KIT := \
		-I$(TMP_TOP_DIR)/Kit/DriverFramework/Basic_Defs_API/incl \
		-I$(TMP_TOP_DIR)/Kit/DriverFramework/CLib_Abstraction_API/incl \
		-I$(TMP_TOP_DIR)/Kit/DriverFramework/Device_API/incl \
		-I$(TMP_TOP_DIR)/Kit/DriverFramework/DMAResource_API/incl \
		-I$(TMP_TOP_DIR)/Kit/EIP201/incl \
		-I$(TMP_TOP_DIR)/Kit/EIP201/src \
		-I$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/incl \
		-I$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/src \
		-I$(TMP_TOP_DIR)/Kit/EIP97/FlowControl/incl \
		-I$(TMP_TOP_DIR)/Kit/EIP97/FlowControl/src \
		-I$(TMP_TOP_DIR)/Kit/EIP97/RingControl/incl \
		-I$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src \
		-I$(TMP_TOP_DIR)/Kit/IOToken/incl \
		-I$(TMP_TOP_DIR)/Kit/IOToken/src \
		-I$(TMP_TOP_DIR)/Kit/Log/incl \
		-I$(TMP_TOP_DIR)/Kit/Log/src/printf \
		-I$(TMP_TOP_DIR)/Kit/RingHelper/incl \
		-I$(TMP_TOP_DIR)/Kit/SABuilder/incl \
		-I$(TMP_TOP_DIR)/Kit/SABuilder/src \
		-I$(TMP_TOP_DIR)/Kit/TokenBuilder/incl \
		-I$(TMP_TOP_DIR)/Kit/TokenBuilder/src

ifndef CONFIG_E906
TMP_DEFINITIONS += -DDRIVER_64BIT_HOST
endif
TMP_DEFINITIONS += -DDRIVER_64BIT_DEVICE
TMP_DEFINITIONS += -DEIP97_BUS_VERSION_AXI4
ifdef CONFIG_E906
TMP_DEFINITIONS += -DARCH_ARM
else
TMP_DEFINITIONS += -DARCH_ARM64
endif
TMP_DEFINITIONS += -Wall
TMP_DEFINITIONS += -DDA_PEC_EIP97
TMP_DEFINITIONS += -DDDK_PEC_IF_ID=0

CUSTOM_CFLAGS += $(INCLUDE_CONF) $(INCLUDE_EXAMPLES) $(INCLUDE_INTEGRATION) $(INCLUDE_KIT) $(TMP_DEFINITIONS)

srcs-y += \
	speed.c \
	cae-main.c
