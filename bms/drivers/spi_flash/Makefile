ARCHIVE := drv_spi_flash.a

XSPIINC := ../xspi
SPIINC := ../spi

CFLAGS +=  -I$(XSPIINC)/ccp_driver/common/   -I$(XSPIINC)/ccp_driver/include/ -I$(XSPIINC)/ccp_driver/src/\
		   -I$(XSPIINC)/core_driver/include/ -I$(XSPIINC)/core_driver/src/  -I$(SPIINC)/\
		   -I./spi_nand/ -I./spi_nor/ -I./xspi_nor/ -I./xspi_nand/ -I./xspi_flash/ -I./xspi_hyper_flash/ -I./\
		   -I./xspi_hyper_ram/\
		   -Wno-address-of-packed-member

srcs-y += \
				spi_flash.c
				
ifdef CONFIG_DRV_SPI
srcs-y += \
				spi_nand/spi_nand_flash.c\
				spi_nor/spi_nor_flash.c
				
endif

ifdef CONFIG_DRV_XSPI
srcs-y += \
				xspi_flash/xspi_flash.c\
				xspi_nor/xspi_nor_flash.c\
				xspi_nor/mxic_nor.c\
				xspi_nor/gd_nor.c\
				xspi_nand/xspi_nand_flash.c\
				xspi_hyper_flash/xspi_hyper_flash.c\
				xspi_hyper_ram/xspi_hyper_ram.c
endif
