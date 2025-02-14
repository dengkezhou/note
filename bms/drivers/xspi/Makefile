ARCHIVE := drv_xspi.a


CFLAGS +=  -Iccp_driver/common/ -Iccp_driver/include/ -Iccp_driver/src/\
		   -Icore_driver/include/ -Icore_driver/src/ -D __BARE_METAL__ -Wno-address-of-packed-member

srcs-y += \
				ccp_driver/src/ccp_obj_if.c\
				ccp_driver/src/ccp_sanity.c\
				ccp_driver/src/ccp.c\
				ccp_driver/src/ccpext_obj_if.c\
				ccp_driver/src/ccpext_sanity.c\
				core_driver/src/xspi_core.c\
				core_driver/src/xspi_full_addons.c\
				core_driver/src/xspi_generic.c\
				core_driver/src/xspi_main.c\
				core_driver/src/xspi_obj_if.c\
				core_driver/src/xspi_sanity.c\
				core_driver/src/xspi_seq.c\
				xspi.c\
				xspi_init.c\
				dma_ctrl.c