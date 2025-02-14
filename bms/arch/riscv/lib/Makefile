
ARCHIVE := arch_lib.a

ifdef CONFIG_MMU
srcs-y += \
		 mmu_table.c
endif
ifdef CONFIG_CACHE
srcs-y += \
		 cache.c
endif
ifdef CONFIG_SYSMAP
srcs-y += \
		 sysmap.c
endif
srcs-y += plat.c

ifdef CONFIG_CCI_COHERENCY_EN
srcs-y += cci.c
endif
