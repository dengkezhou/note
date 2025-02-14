
ARCHIVE := drv_cae.a

TMP_TOP_DIR = rambus_ddk

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
TMP_DEFINITIONS += -DDRIVER_64BIT_DEVICE
endif
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

subdirs-$(CONFIG_DRV_CAE_IVP) += ivp

srcs-y += \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_driver97_init.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/AXI4/adapter_init.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/lkm/adapter_interrupts.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/lkm/adapter_sleep.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/lkm/adapter_lock.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_global_init.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_global_eip97.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_pec_dma.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_ring_eip202.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_sglist.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_dmabuf.c \
	$(TMP_TOP_DIR)/Integration/SLAD_Adapter/src/adapter_lock_internal.c \
	$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/src/eip97_global_init.c \
	$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/src/eip202_global_init.c \
	$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/src/eip97_global_event.c \
	$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/src/eip97_global_prng.c \
	$(TMP_TOP_DIR)/Kit/EIP97/GlobalControl/src/eip97_global_fsm.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_cdr_init.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_cdr_dscr.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_cdr_event.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_cd_format.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_cdr_fsm.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_rdr_init.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_rdr_dscr.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_rdr_event.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_rd_format.c \
	$(TMP_TOP_DIR)/Kit/EIP97/RingControl/src/eip202_rdr_fsm.c \
	$(TMP_TOP_DIR)/Kit/IOToken/src/iotoken.c \
	$(TMP_TOP_DIR)/Kit/EIP201/src/eip201.c \
	$(TMP_TOP_DIR)/Kit/RingHelper/src/ringhelper.c \
	$(TMP_TOP_DIR)/Integration/DriverFramework/src/LKM/AXI4/lkm.c \
	$(TMP_TOP_DIR)/Integration/DriverFramework/src/LKM/AXI4/device_lkm.c \
	$(TMP_TOP_DIR)/Integration/DriverFramework/src/LKM/dmares_lkm.c \
	$(TMP_TOP_DIR)/Integration/DriverFramework/src/dmares_gen.c \
	$(TMP_TOP_DIR)/Integration/DriverFramework/src/device_generic.c \
	$(TMP_TOP_DIR)/Kit/Log/src/log.c \
	$(TMP_TOP_DIR)/Kit/SABuilder/src/sa_builder.c \
	$(TMP_TOP_DIR)/Kit/SABuilder/src/sa_builder_ipsec.c \
	$(TMP_TOP_DIR)/Kit/SABuilder/src/sa_builder_ssltls.c \
	$(TMP_TOP_DIR)/Kit/SABuilder/src/sa_builder_basic.c \
	$(TMP_TOP_DIR)/Kit/SABuilder/src/sa_builder_srtp.c \
	$(TMP_TOP_DIR)/Kit/TokenBuilder/src/token_builder_core.c \
	$(TMP_TOP_DIR)/Kit/TokenBuilder/src/token_builder_context.c \
	$(TMP_TOP_DIR)/Examples/DemoApp_PEC/src/da_pec_support.c \
	cipher.c \
	cipher_params.c \
	digest.c \
	digest_params.c \
	misc.c \
	cae.c \
	entity/cipher_entity.c \
	entity/cipher_entity_params.c \
	entity/digest_entity.c \
	entity/digest_entity_params.c \
	entity/misc_entity.c \
	entity/misc_entity_params.c
