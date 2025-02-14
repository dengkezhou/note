ARCHIVE := testbench_pufcc.a

PUFCC_DIR = ../../drivers/pufcc

CFLAGS += \
		-I$(PUFCC_DIR)/include -I./ -I./include

ifdef CONFIG_COMPILE_FPGA
# CFLAGS += -DPUFS_TV_FULL
endif

srcs-y += \
	pufs_chacha_test.c\
	pufs_cmac_test.c\
	pufs_dma_test.c\
	pufs_ecp_test.c\
	pufs_hmac_test.c\
	pufs_ka_test.c\
	pufs_kdf_test.c\
	pufs_rt_user_test.c\
	pufs_rt_factory_test.c\
	pufs_sm2_test.c\
	pufs_sp38a_test.c\
	pufs_sp38c_test.c\
	pufs_sp38d_test.c\
	pufs_sp38e_test.c\
	pufs_sp90a_test.c\
	pufs_test_common.c\
	pufcc-main.c