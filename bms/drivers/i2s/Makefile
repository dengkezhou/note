ARCHIVE := drv_i2s.a

ifdef CONFIG_CDNS_I2S_SC
srcs-y += cdns-i2s-sc.c
endif

ifdef CONFIG_CDNS_I2S_MC
srcs-y += cdns-i2s-mc.c
srcs-y += ES7210L.c
endif

subdirs-$(CONFIG_DRV_CODEC_ES8388) += es8388

