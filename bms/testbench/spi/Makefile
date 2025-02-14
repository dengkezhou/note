ARCHIVE := testbench_spi.a

INC := ../../drivers/xspi/

CFLAGS +=  -I../../drivers/spi/  
CFLAGS +=  -I$(INC)/ccp_driver/common/   -I$(INC)/ccp_driver/include/ -I$(INC)/ccp_driver/src/\
		   -I$(INC)/core_driver/include/ -I$(INC)/core_driver/src/  -I../../drivers/spi_flash/\
		   -I../../drivers/spi_flash/spi_nand -I../../drivers/spi_flash/spi_nor\
		   -I../../drivers/spi/ -Wno-address-of-packed-member
srcs-y += \
				arm-spi-main.c
