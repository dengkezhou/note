ARCHIVE := drv_drd.a
CDNS := cdns
CORE_DIR := cdns/core_driver
DEV_IF_DIR := cdns/dev_if
HOST_IF_DIR := cdns/host_if
DEVICE_DIR := device

CFLAGS += \
		-I$(CORE_DIR)/common/include -I$(CORE_DIR)/common/src\
		-I$(CORE_DIR)/device/include -I$(CORE_DIR)/device/src\
		-I$(CORE_DIR)/drd/include -I$(CORE_DIR)/drd/src\
		-I$(CORE_DIR)/host/include -I$(CORE_DIR)/host/src\
		-I$(DEV_IF_DIR) -I$(HOST_IF_DIR) -I$(CDNS) -I$(DEVICE_DIR)\
		-D __BARE_METAL__ -Wno-address-of-packed-member
srcs-y += \
		$(CORE_DIR)/common/src/cusb_ch9_sanity.c\
		$(CORE_DIR)/device/src/cusbd.c\
		$(CORE_DIR)/device/src/cusbdma.c\
		$(CORE_DIR)/device/src/cusbdma_obj_if.c\
		$(CORE_DIR)/device/src/cusbdma_sanity.c\
		$(CORE_DIR)/device/src/cusbd_obj_if.c\
		$(CORE_DIR)/device/src/cusbd_sanity.c\
		$(CORE_DIR)/device/src/list_sanity.c\
		$(CORE_DIR)/drd/src/fsm_state_a_host.c\
		$(CORE_DIR)/drd/src/fsm_state_a_idle.c\
		$(CORE_DIR)/drd/src/fsm_state_b_idle.c\
		$(CORE_DIR)/drd/src/fsm_state_b_peripheral.c\
		$(CORE_DIR)/drd/src/fsm_state_dev.c\
		$(CORE_DIR)/drd/src/fsm_state_host.c\
		$(CORE_DIR)/drd/src/fsm_usb.c\
		$(CORE_DIR)/drd/src/usb_ssp_drd.c\
		$(CORE_DIR)/drd/src/usb_ssp_drd_hw.c\
		$(CORE_DIR)/drd/src/usb_ssp_drd_obj_if.c\
		$(CORE_DIR)/drd/src/usb_ssp_drd_sanity.c\
		$(CORE_DIR)/host/src/cdn_xhci.c\
		$(CORE_DIR)/host/src/cdn_xhci_common.c\
		$(CORE_DIR)/host/src/cdn_xhci_isr.c\
		$(CORE_DIR)/host/src/cdn_xhci_obj_if.c\
		$(CORE_DIR)/host/src/cdn_xhci_sanity.c\
		$(CORE_DIR)/host/src/xhci_mem_alloc.c\
		$(DEV_IF_DIR)/device_if.c\
		$(HOST_IF_DIR)/host_if.c\
		$(DEVICE_DIR)/mouse.c\
		$(DEVICE_DIR)/loop_dev.c\
		usb.c

