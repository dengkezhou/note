COPTIONS := -march=rv64imafdcv_zicbom_zicbop_zicboz_zicond1p0_zihintntl0p2_zihintpause_zawrs_zfa0p1_zfbfmin0p8_zfh_zca_zcb_zcd_zba_zbb_zbc_zbs_zvfbfmin0p8_zvfbfwma0p8_svinval_svpbmt_xtheadc_xtheadvdot -mabi=lp64d -mcmodel=medany

CFLAGS := ${HEADER} -I$(OBJTREE)/include -I$(SRCTREE)/arch/riscv/$(MACHINE)/csi_core/include \
					-Os -ffunction-sections -fdata-sections -Wall -c -g2 -fno-builtin -D__KERNEL__ \
					-include sys/cdefs.h $(COPTIONS)
AFLAGS := -Wall -c -g2 -x assembler-with-cpp -I$(OBJTREE)/include $(COPTIONS)
CUSTOM_AFLAGS := -I$(SRCTREE)/include
ARFLAGS := cr
LDFLAGS := -nostartfiles -static -nostdlib -L. -Wl,-gc-sections $(COPTIONS) \

ifdef CONFIG_COMPILE_ROM
TARGET := rom
else
TARGET := soc
endif
BINARY ?= $(TARGET).elf

# linker script
ifdef CONFIG_COMPILE_SIM
LINKERFILE_SRC := $(SRCTREE)/arch/riscv/$(MACHINE)/cskysim_link.ld.S
else
ifdef CONFIG_COMPILE_ROM
LINKERFILE_SRC := $(SRCTREE)/arch/riscv/$(MACHINE)/rom.ld.S
else
LINKERFILE_SRC := $(SRCTREE)/arch/riscv/$(MACHINE)/soc.ld.S
endif
endif
LINKERFILE_DST := $(OBJTREE)/$(TARGET).lds
LDFLAGS += -T ${LINKERFILE_DST}
PLATFORM_HEAD := include/generated/autoconf.h

export TARGET BINARY
export CFLAGS ARFLAGS AFLAGS LDFLAGS LINKERFILE_DST LINKERFILE_SRC

libs-$(CONFIG_LIB_COMMAND) += lib_command.a
libs-$(CONFIG_LIB_MATH) += lib_math.a
libs-$(CONFIG_LIB_SHELL) += lib_shell.a
libs-$(CONFIG_LIB_STDLIB) += lib_stdlib.a
libs-$(CONFIG_LIB_COMMON) += lib_common.a
libs-$(CONFIG_LIB_CONSOLE) += lib_console.a
libs-$(CONFIG_LIB_CRYPTO) += lib_crypto.a
libs-$(CONFIG_LIB_INTERRUPT) += lib_interrupt.a
libs-$(CONFIG_LIB_FATFS) += lib_fatfs.a
libs-$(CONFIG_LIB_RTLFS) += lib_rtlfs.a
libs-$(CONFIG_LIB_RTL) += lib_rtl.a
libs-$(CONFIG_LIB_FREERTOS) += lib_freertos.a
libs-$(CONFIG_LIB_SBI) += lib_sbi.a

libs-$(CONFIG_DRV_DMA) += drv_dma.a
libs-$(CONFIG_DRV_SYSM) += drv_sysm.a
libs-$(CONFIG_DRV_IRQCHIP) += drv_irqchip.a
libs-$(CONFIG_DRV_TIMER) += drv_timer.a
libs-$(CONFIG_DRV_I2C) += drv_i2c.a
libs-$(CONFIG_DRV_EEPROM) += drv_eeprom.a
libs-$(CONFIG_DRV_I2S) += drv_i2s.a
libs-$(CONFIG_DRV_WDT) += drv_wdt.a
libs-$(CONFIG_DRV_UART) += drv_uart.a
libs-$(CONFIG_DRV_ETH) += drv_eth.a
libs-$(CONFIG_DRV_SDMMC) += drv_sdmmc.a
libs-$(CONFIG_DRV_DRD) += drv_drd.a
libs-$(CONFIG_DRV_RTC) += drv_rtc.a
libs-$(CONFIG_DRV_SPI) += drv_spi.a
libs-$(CONFIG_DRV_XSPI) += drv_xspi.a
libs-$(CONFIG_DRV_SPI_FLASH) += drv_spi_flash.a
libs-$(CONFIG_DRV_MU) += drv_mu.a
libs-$(CONFIG_DRV_PWM) += drv_pwm.a
libs-$(CONFIG_DRV_PVT) += drv_pvt.a
libs-$(CONFIG_DRV_CAE) += drv_cae.a
libs-$(CONFIG_DRV_PUFCC) += drv_pufcc.a
libs-$(CONFIG_DRV_DDR) += drv_ddr.a
libs-$(CONFIG_DRV_RXA) += drv_rxa.a
libs-$(CONFIG_DRV_VDEC) += drv_vdec.a
libs-$(CONFIG_DRV_DMIC) += drv_dmic.a
libs-$(CONFIG_DRV_VENC) += drv_venc.a
libs-$(CONFIG_DRV_IDS) += drv_ids.a
libs-$(CONFIG_DRV_PMIC) += drv_pmic.a
libs-$(CONFIG_DRV_LPDDR4) += drv_lpddr4.a
libs-$(CONFIG_DRV_DMIC_PCM) += drv_dmic_pcm.a
libs-$(CONFIG_DRV_HWMON) += drv_hwmon.a

libs-$(CONFIG_TBH_CPU) += testbench_cpu.a
libs-$(CONFIG_TBH_DMA) += testbench_dma.a
libs-$(CONFIG_TBH_IRQ) += testbench_irq.a
libs-$(CONFIG_TBH_TIMER) += testbench_timer.a
libs-$(CONFIG_TBH_I2C) += testbench_i2c.a
libs-$(CONFIG_TBH_RTLFS) += testbench_rtlfs.a
libs-$(CONFIG_TBH_SKULL) += testbench_skull.a
libs-$(CONFIG_TBH_TASK) += testbench_task.a
libs-$(CONFIG_TBH_WDT) += testbench_wdt.a
libs-$(CONFIG_TBH_UART) += testbench_uart.a
libs-$(CONFIG_TBH_ETH) += testbench_eth.a
libs-$(CONFIG_TBH_I2S) += testbench_i2s.a
libs-$(CONFIG_TBH_VDEC) += testbench_vdec.a
libs-$(CONFIG_TBH_SDMMC) += testbench_sdmmc.a
libs-$(CONFIG_TBH_SYSM) += testbench_sysm.a
libs-$(CONFIG_TBH_DRD) += testbench_drd.a
libs-$(CONFIG_TBH_RTC) += testbench_rtc.a
libs-$(CONFIG_TBH_SPI) += testbench_spi.a
libs-$(CONFIG_TBH_XSPI) += testbench_xspi.a
libs-$(CONFIG_TBH_MU) += testbench_mu.a
libs-$(CONFIG_TBH_PWM) += testbench_pwm.a
libs-$(CONFIG_TBH_PVT) += testbench_pvt.a
libs-$(CONFIG_TBH_CAE) += testbench_cae.a
libs-$(CONFIG_TBH_PUFCC) += testbench_pufcc.a
libs-$(CONFIG_TBH_DDR) += testbench_ddr.a
libs-$(CONFIG_TBH_RXA) += testbench_rxa.a
libs-$(CONFIG_TBH_NPU) += testbench_npu.a
libs-$(CONFIG_TBH_DMIC) += testbench_dmic.a
libs-$(CONFIG_TBH_VENC) += testbench_venc.a
libs-$(CONFIG_TBH_IDS) += testbench_ids.a
libs-$(CONFIG_TBH_LPDDR4) += testbench_lpddr4.a
libs-$(CONFIG_TBH_DMIC_PCM) += testbench_dmic_pcm.a
libs-$(CONFIG_TBH_FATFS) += testbench_fatfs.a
libs-$(CONFIG_TBH_PMIC) += testbench_pmic.a
libs-$(CONFIG_TBH_HWMON) += testbench_hwmon.a

libs-y += \
		arch_$(TARGET).a	\
		arch_lib.a

