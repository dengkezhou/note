ARCHIVE := drv_pufcc.a

INCLUDE_DIRS=./include
SRC_DIR=src

#CFLAGS +=  -Wall -Werror -Wextra -pedantic -pedantic-errors -Wstrict-prototypes -std=c11 -fPIC -O2
CFLAGS += -Wl,-wrap=malloc -Wl,-wrap=free -Wl,-wrap=calloc
CFLAGS += -I$(INCLUDE_DIRS)

srcs-y += \
		$(SRC_DIR)/dummy_pal.c\
		$(SRC_DIR)/pufs_chacha.c\
		$(SRC_DIR)/pufs_cmac.c\
		$(SRC_DIR)/pufs_common.c\
		$(SRC_DIR)/pufs_crypto.c\
		$(SRC_DIR)/pufs_dma.c\
		$(SRC_DIR)/pufs_dma_desc.c\
		$(SRC_DIR)/pufs_dma_internal.c\
		$(SRC_DIR)/pufs_ecc.c\
		$(SRC_DIR)/pufs_ecp.c\
		$(SRC_DIR)/pufs_ecp_mprog.c\
		$(SRC_DIR)/pufs_hmac.c\
		$(SRC_DIR)/pufs_internal.c\
		$(SRC_DIR)/pufs_ka.c\
		$(SRC_DIR)/pufs_kdf.c\
		$(SRC_DIR)/pufs_reg_ctrl.c\
		$(SRC_DIR)/pufs_rt.c\
		$(SRC_DIR)/pufs_sm2.c\
		$(SRC_DIR)/pufs_sp38a.c\
		$(SRC_DIR)/pufs_sp38c.c\
		$(SRC_DIR)/pufs_sp38d.c\
		$(SRC_DIR)/pufs_sp38e.c\
		$(SRC_DIR)/pufs_sp90a.c



