ARCHIVE := testbench_eth.a

CORE_DIR := ../../drivers/eth/gem_gxl/core_driver
TEST_DIR := ../../drivers/eth/gem_gxl/reference_code/tests
CUSTOM_CFLAGS += -I$(CORE_DIR)/include -I$(CORE_DIR)/common -I$(CORE_DIR)/src -I$(TEST_DIR) -D__BARE_METAL__

srcs-y += \
	eth-main.c \

