ARCHIVE := drv_eth.a

CORE_DIR := gem_gxl/core_driver
TEST_DIR := gem_gxl/reference_code/tests

CUSTOM_CFLAGS += -I$(CORE_DIR)/include \
		 -I$(CORE_DIR)/common \
		 -I$(CORE_DIR)/src \
		 -I$(TEST_DIR) \
		 -D__BARE_METAL__ \
		 -DCEDI_64B_COMPILE

srcs-y += \
	$(CORE_DIR)/src/cedi_obj_if.c \
	$(CORE_DIR)/src/cedi_sanity.c \
	$(CORE_DIR)/src/edd_rx.c \
	$(CORE_DIR)/src/edd_tx.c \
	$(CORE_DIR)/src/edd.c \
	$(TEST_DIR)/cps_bm.c \
	$(TEST_DIR)/edd_common.c \
	$(TEST_DIR)/edd_data.c \
	$(TEST_DIR)/edd_events.c \
	$(TEST_DIR)/edd_support.c \
	eth_lowlevel.c \
	phy/phy.c \
	phy/marvell.c \
	phy/icplus.c \
	phy/lan8742a.c \
	eth.c
