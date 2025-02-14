ARCHIVE := testbench_xspi.a
INC := ../../drivers/xspi

CFLAGS +=  -I$(INC)/ccp_driver/common/   -I$(INC)/ccp_driver/include/ -I$(INC)/ccp_driver/src/\
		   -I$(INC)/core_driver/include/ -I$(INC)/core_driver/src/  -I../../drivers/spi_flash/\
		   -I../../drivers/spi_flash/xspi_flash -I../../drivers/spi/ -Wno-address-of-packed-member
srcs-y += \
				xspi-main.c
