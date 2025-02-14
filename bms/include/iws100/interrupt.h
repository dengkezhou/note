
#ifndef __INTERRUPT_X9_H__
#define __INTERRUPT_X9_H__

#define _CPU_INFOMACTION_ADDRESS    0x3C017000
#define _INTR_SYNC_STARTADDRESS     0x3C017800
#define CPU1_CALL_PARAM             _CPU_INFOMACTION_ADDRESS
#define CPU2_CALL_PARAM             (CPU1_CALL_PARAM + 0X4)
#define CPU3_CALL_PARAM             (CPU2_CALL_PARAM + 0X4)
#define CPU1_CALLED                 (CPU3_CALL_PARAM + 0X4)
#define CPU2_CALLED                 (CPU1_CALLED + 0X4)
#define CPU3_CALLED                 (CPU2_CALLED + 0X4)
#define CPU1_INTR_FIN               (CPU3_CALLED + 0X4)
#define CPU2_INTR_FIN               (CPU1_INTR_FIN + 0X4)
#define CPU3_INTR_FIN               (CPU2_INTR_FIN + 0X4)
#define CPU1_WAIT                   (CPU3_INTR_FIN + 0X4)
#define CPU2_WAIT                   (CPU1_WAIT + 0X4)
#define CPU3_WAIT                   (CPU2_WAIT + 0X4)
#define RTL_CPU1_CUR_ACTIVE_TASK_ID (CPU3_WAIT + 0X4)
#define RTL_CPU2_CUR_ACTIVE_TASK_ID (RTL_CPU1_CUR_ACTIVE_TASK_ID + 0X4)
#define RTL_CPU3_CUR_ACTIVE_TASK_ID (RTL_CPU2_CUR_ACTIVE_TASK_ID + 0X4)
#define CPU0_RUN_TASK_CNT           (RTL_CPU3_CUR_ACTIVE_TASK_ID + 0X4)
#define CPU1_RUN_TASK_CNT           (CPU0_RUN_TASK_CNT + 0X4)
#define CPU2_RUN_TASK_CNT           (CPU1_RUN_TASK_CNT + 0X4)
#define CPU3_RUN_TASK_CNT           (CPU2_RUN_TASK_CNT + 0X4)

#define DATA_CPUID   (CPU3_RUN_TASK_CNT + 0X4)
#define DATA_UP      (DATA_CPUID + 0X4)
#define DATA_CPUNB   (DATA_UP + 0X4)
#define DATA_AXI2    (DATA_CPUNB + 0X4)
#define DATA_ACP     (DATA_AXI2 + 0X4)
#define DATA_INT     (DATA_ACP + 0X4)
#define DATA_ICACHE0 (DATA_INT + 0X4)
#define DATA_ICACHE1 (DATA_ICACHE0 + 0X4)
#define DATA_ICACHE2 (DATA_ICACHE1 + 0X4)
#define DATA_ICACHE3 (DATA_ICACHE2 + 0X4)
#define DATA_DCACHE0 (DATA_ICACHE3 + 0X4)
#define DATA_DCACHE1 (DATA_DCACHE0 + 0X4)
#define DATA_DCACHE2 (DATA_DCACHE1 + 0X4)
#define DATA_DCACHE3 (DATA_DCACHE2 + 0X4)
#define DATA_FPU0    (DATA_DCACHE3 + 0X4)
#define DATA_FPU1    (DATA_FPU0 + 0X4)
#define DATA_FPU2    (DATA_FPU1 + 0X4)
#define DATA_FPU3    (DATA_FPU2 + 0X4)
#define DATA_NEON0   (DATA_FPU3 + 0X4)
#define DATA_NEON1   (DATA_NEON0 + 0X4)
#define DATA_NEON2   (DATA_NEON1 + 0X4)
#define DATA_NEON3   (DATA_NEON2 + 0X4)
#define DATA_JZ0     (DATA_NEON3 + 0X4)
#define DATA_JZ1     (DATA_JZ0 + 0X4)
#define DATA_JZ2     (DATA_JZ1 + 0X4)
#define DATA_JZ3     (DATA_JZ2 + 0X4)

#define SYNCFLAGS   (DATA_JZ3 + 0X4)
#define DATA_MPCORE (SYNCFLAGS + 0X4)
#define SYNC_CPU    (DATA_MPCORE + 0X4)

#define CPU1_FOUND (0x43505531)
#define CPU2_FOUND (0x43505532)
#define CPU3_FOUND (0x43505533)

#define MMU_ENABLE      (1)
#define DCACHE_ENABLE   (0)
#define ICACHE_ENABLE   (0)
#define L2_CACHE_ENABLE (0)
//========================================================================
// Generic Interrupt Controller for Cortex-A5
//========================================================================
#define rICDDCR *(volatile unsigned *)(GIC_DISTRIBUTOR_ADDR + 0x0)
#define rICDICTR                                                               \
  *(volatile unsigned *)(GIC_DISTRIBUTOR_ADDR + 0x4) // RO	Type Register
#define rICDIIDR                                                               \
  *(volatile unsigned                                                          \
        *)(GIC_DISTRIBUTOR_ADDR +                                              \
           0x8) // RO	Distributor Implementer Identification Register
#define ICDISR_BASE_ADDR                                                       \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x80) // Interrupt Security Registers, offset is 0x80 - 0xFC
// register is (ICDISR_BASE_ADDR + (4 * (N/32))), N is interrupt ID
// bit is N MOD 32
#define ICDISER_BASE_ADDR                                                      \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x100) // Interrupt Set-Enable Registers, offset is 0x100 - 0x17C
// register is (ICDISER_BASE_ADDR + (4 * (N/32))), N is interrupt ID
// bit is N MOD 32
#define ICDICER_BASE_ADDR                                                      \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x180) // Interrupt Clear-Enable Registers, offset is 0x180 - 0x1FC
// register is (ICDICER_BASE_ADDR + (4 * (N/32))), N is interrupt ID
// bit is N MOD 32
#define ICDISPR_BASE_ADDR                                                      \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x200) // Interrupt Set-Pending Registers, offset is 0x200 - 0x27C
// register is (ICDISPR_BASE_ADDR + (4 * (N/32))), N is interrupt ID
// bit is N MOD 32
#define ICDICPR_BASE_ADDR                                                      \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x280) // Interrupt Clear-Pending Registers, offset is 0x280 - 0x2FC
// register is (ICDICPR_BASE_ADDR + (4 * (N/32))), N is interrupt ID
// bit is N MOD 32
#define ICDABR_BASE_ADDR                                                       \
  (GIC_DISTRIBUTOR_ADDR + 0x300) // Active Bit Registers, offset is 0x300 -
                                 // 0x37C
// register is (ICDABR_BASE_ADDR + (4 * (N/32))), N is interrupt ID
// bit is N MOD 32
#define ICDIPR_BASE_ADDR                                                       \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x400) // Interrupt Priority Registers, offset is 0x400 - 0x7F8
// register is (ICDIPR_BASE_ADDR + (4 * (N/4))), N is interrupt ID
// bit is N MOD 4
#define ICDIPTR_BASE_ADDR                                                      \
  (GIC_DISTRIBUTOR_ADDR +                                                      \
   0x800) // Interrupt Processor Targets Registers, offset is 0x800 - 0x81C,
          // ICDIPTR0 - ICDIPTR7 is RO
// register is (ICDIPR_BASE_ADDR + (4 * (N/4))), N is interrupt ID
// bit is N MOD 4
#define ICDICFR_BASE_ADDR                                                      \
  (GIC_DISTRIBUTOR_ADDR + 0xC00) // Interrupt Configuration Registers, offset is
                                 // 0xC00 - 0xCFC, ICDICFR is RO for SGIs
// register is (ICDIPR_BASE_ADDR + (4 * (N/16))), N is interrupt ID
// bit is N MOD 16
#define rICDSGIR				(*(volatile unsigned *)(GIC_DISTRIBUTOR_ADDR + 0xF00)	//Software Genrrated Interrupt Register, RO

#define rICCICR                                                                \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0x0) // CPU Interface Control Register
#define rICCPMR                                                                \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0x4) // Interrupt Priority Mask Register
#define rICCBPR                                                                \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR + 0x8) // Binary Point Register
#define rICCIAR                                                                \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0xC) // Interrupt Acknowledge Register, RO
#define rICCEOIR                                                               \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0x10) // End of Interrupt Register, WO
#define rICCRPR                                                                \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0x14) // Runing Priority Interrupt Register, RO
#define rICCHPIR                                                               \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0x18) // Highest Pending Interrupt Register, RO
#define rICCABPR                                                               \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0x1C) // Aliased Binary Point Register
#define rICCIIDR                                                               \
  *(volatile unsigned *)(GIC_CPUI_BASE_ADDR +                                  \
                         0xFC) // CPU Interface Identification Register

/**
FUNC: initialize this lib.
PARAMS:
RETURN:
**/
//#if defined(_IMAPX_ARM1136JFS_)
//#if defined(_IMAPX_200_)
#define IMAPX200_EINT0 (0)
#define IMAPX200_EINT1 (1)
#define IMAPX200_EINT2 (2)
#define IMAPX200_EINT3 (3)

#define IMAPX200_EINT4 (4)
#define IMAPX200_EINT5 (5)
#define IMAPX200_AC97  (6)
#define IMAPX200_IIS   (7)
#define IMAPX200_RTC   (8)
#define IMAPX200_WDT   (9)

#define IMAPX200_PWM0  (10)
#define IMAPX200_PWM1  (11)
#define IMAPX200_PWM2  (12)
#define IMAPX200_UART2 (13)
#define IMAPX200_IIC0  (14)
#define IMAPX200_PWM3  (15)

#define IMAPX200_IDS    (16)
#define IMAPX200_CAM    (17)
#define IMAPX200_TIMER0 (18)
#define IMAPX200_TIMER1 (19)
#define IMAPX200_DMA    (20)
#define IMAPX200_SSI0   (21)

#define IMAPX200_SSI2  (22)
#define IMAPX200_UART1 (23)
#define IMAPX200_NAND  (24)
#define IMAPX200_OTG   (25)
#define IMAPX200_OHCI  (26)
#define IMAPX200_NULL0 (27)

#define IMAPX200_EMIF  (28)
#define IMAPX200_DBG   (29)
#define IMAPX200_POW   (30)
#define IMAPX200_NULL1 (31)

#define IMAPX200_ETH   (32)
#define IMAPX200_UART3 (33)
#define IMAPX200_IIC1  (34)
#define IMAPX200_IDE   (35)
#define IMAPX200_SDIO1 (36)
#define IMAPX200_SDIO2 (37)

#define IMAPX200_PWM4 (38)
#define IMAPX200_IPC  (39)
#define IMAPX200_ENC  (40)
#define IMAPX200_DEC  (41)
#define IMAPX200_GPS  (42)
#define IMAPX200_MEMP (43)

#define IMAPX200_EHCI  (44)
#define IMAPX200_PIC0  (45)
#define IMAPX200_KB    (46)
#define IMAPX200_GPIO  (47)
#define IMAPX200_SDIO0 (48)
#define IMAPX200_NULL2 (49)

#define IMAPX200_PIC1  (50)
#define IMAPX200_UART0 (51)
#define IMAPX200_SSI1  (52)
#define IMAPX200_ALARM (53)
#define IMAPX200_3D    (54)
#define IMAPX200_NULL3 (55)

#define IMAPX200_ISP (54)

#define IMAPX200_SIMC IMAPX200_AC97 /* add simc */
#define IMAPX200_SECC IMAPX200_NAND /* add secc */

#define IMAPX200_INTR_PORT1 IMAPX200_ETH
//#elif defined(_IMAPX_ARMA5NEON_)
//#elif defined(_IMAPX_800_)
//========================================================================
// GIC INTERRUPT DESCRIPTION
//========================================================================
//========================================================================
// GIC INTERRUPT ID
//========================================================================
#define MIIS_INT_ID   (32) // IIS Master Module Interrupt
#define IISM_INT_ID   (33) // IIS Slave Module0 Interrupt
#define IISS_INT_ID   (34) // IIS Slave Module1 Interrupt
#define CMNT0_INT_ID  (35) // Common Timer0 Interrupt
#define CMNT1_INT_ID  (36) // Common Timer1 Interrupt
#define PWM0_INT_ID   (37) // PWM0 Interrupt
#define PWM1_INT_ID   (38) // PWM1 Interrupt
#define PWM2_INT_ID   (39) // PWM2 Interrupt
#define PWM3_INT_ID   (40) // PWM3 Interrupt
#define PWM4_INT_ID   (41) // PWM4 Interrupt
#define IIC0_INT_ID   (42) // IIC0 Interrupt
#define IIC1_INT_ID   (43) // IIC1 Interrupt
#define IIC2_INT_ID   (44) // IIC2 Interrupt
#define IIC3_INT_ID   (45) // IIC3 Interrupt
#define PCM_INT_ID    (46) // PCM Interrupt
#define SPI0_INT_ID   (47) // SPI0 Interrupt
#define SPI1_INT_ID   (48) // SPI1 Interrupt
#define SPI2_INT_ID   (49) // SPI2 Interrupt
#define SPDIF_INT_ID  (50) // SPDIF Interrupt
#define SIMC0_INT_ID  (51) // SimCard0 Interrupt
#define SIMC1_INT_ID  (52) // SimCard1 Interrupt
#define UART0_INT_ID  (53) // UART0 Interrupt
#define UART1_INT_ID  (54) // UART1 Interrupt
#define UART2_INT_ID  (55) // UART2 Interrupt
#define UART3_INT_ID  (56) // UART3 Interrupt
#define PS2_0_INT_ID  (57) // PS2 Module0 Interrupt
#define PS2_1_INT_ID  (58) // PS2 Module1 Interrupt
#define AC97_INT_ID   (59) // AC97 Interrupt
#define KEYP_INT_ID   (60) // KeyPAD Interrupt
#define KEYPW_INT_ID  (61) // KeyPAD Wakeup Interrupt
#define ACODEC_INT_ID (62) // AudioCodec Interrupt
//#define TSC_INT_ID							(63)
////Touch Screen Controller Interrupt
#define TSC_INT_ID   (62) // Touch Screen Controller Interrupt
#define GPIOG_INT_ID (63) // GPIO Global Interrupt
#define GPIO0_INT_ID (64) // GPIO Interrupt 0
#define GPIO1_INT_ID (65) // GPIO Interrupt 1
#define GPIO2_INT_ID (66) // GPIO Interrupt 2
#define GPIO3_INT_ID (67) // GPIO Interrupt 3
#define GPIO4_INT_ID (68) // GPIO Interrupt 4
#define GPIO5_INT_ID (69) // GPIO Interrupt 5
#define DMIC_INT_ID                                                            \
  (70)                   // DMIC interrupt
                         // 71 pwm audio ??
#define IIC4_INT_ID (72) // IIC 4 Interrupt
#define IIC5_INT_ID (73) // IIC 5 Interrupt

#define WDT_INT_ID    (78) // watch dog
#define GPIO6_INT_ID  (74) // GPIO Interrupt 5
#define GPIO7_INT_ID  (75) // GPIO Interrupt 5
#define GPIO8_INT_ID  (76) // GPIO Interrupt 5
#define GPIO9_INT_ID  (77) // GPIO Interrupt 5
#define GPIO10_INT_ID (77) // GPIO Interrupt 5 /* TODO ?? */
#define WTD_INT_ID    (78) /* TODO ?? */
#define PMC1_INT_ID   (79)
// RSVD
#define IDS0_INT_ID    (80) // IDS0 Interrupt
#define MIPIDSI_INT_ID (81) // MIPI DSI Interrupt
// RSVD
#define IDS1_INT_ID   (96) // IDS1 Interrupt
#define HDMITX_INT_ID (97) // HDMI Transmitter Interrrupt
#define HDMIWK_INT_ID (98) // HDMI Transmitter Interrrupt
// RSVD
//#define	GPSACQ_INT_ID						(98)
////GPS Acquisition Interrupt #define	GPSTCK_INT_ID (99)	//GPS Track
// Interrupt
#define GPSACQ_INT_ID (99)  // GPS Acquisition Interrupt
#define GPSTCK_INT_ID (100) // GPS Track Interrupt
// RSVD
#define CRYPTO_INT_ID    (101) // Crypto Interrupt
#define GPUPP0_INT_ID    (112)
#define GPUPP0MMU_INT_ID (113) // GPU PP0 MMU Interrupt
#define GPUPP1_INT_ID    (114) // GPU PP1 Interrupt
#define GPUPP1MMU_INT_ID (115) // GPU PP1 MMU Interrupt
#define GPUPP2_INT_ID    (116) // GPU PP2 Interrupt
#define GPUPP2MMU_INT_ID (117) // GPU PP2 MMU Interrupt
#define GPUPP3_INT_ID    (118) // GPU PP3 Interrupt
#define GPUPP3MMU_INT_ID (119) // GPU PP3 MMU Interrupt
#define GPUGP_INT_ID     (120) // GPU GP Interrupt
#define GPUGPMMU_INT_ID  (121) // GPU GP MMU Interrupt
#define GPUPMU_INT_ID    (122) // GPU PMU Interrupt
// RSVD
#define VDEC0_INT_ID (128) // VDEC H264  Interrupt
#define VENC0_INT_ID (129) // VENC Interrupt
#define VDEC1_INT_ID (130) // VDEC H265 Interrupt
#define VENC1_INT_ID (131) // VENC Interrupt
// RSVD
#define ISP_INT_ID      (144) // ISP Interrupt
#define MIPICSI0_INT_ID (145) // MIPI CSI 0 Interrupt
#define MIPICSI1_INT_ID (146) // MIPI CSI 1 Interrupt
#define MIPICSI2_INT_ID (147) // MIPI CSI 2 Interrupt
#define TSIF0_INT_ID    (148)
#define TSIF1_INT_ID    (149)
// RSVD
#define USBHEHCI_INT_ID (160) // USB Host EHCI Interrupt
#define USBHOHCI_INT_ID (161) // USB Host OHCI Interrupt
#define USBOTG_INT_ID   (162) // USB OTG Interrupt
#define SD1_INT_ID      (163) // SDEMMC1 Interrupt
#define SD2_INT_ID      (164) // SDEMMC2 Interrupt
//#define	ETH_INT_ID (165)
////Eethernet Interrupt #define	CRYPTO_INT_ID
//(166)	//Crypto Interrupt RSVD
#define NF2_INT_ID    (176) // NF2 Controller Interrupt
#define SD0_INT_ID    (165) // SDEMMC0 Interrupt
#define OTGPHY_INT_ID (166) // SDEMMC0 Interrupt
#define SATA_INT_ID   (178) // SATA2 Interrupt
#define ETH_INT_ID    (179) // Eethernet Interrupt
// RSVD
#define MPOOL_INT_ID (180) // MemPool Interrupt
// RSVD
#define DMAIRQ0_INT_ID  (192) // DMA IRQ0 Interrupt
#define DMAIRQ1_INT_ID  (193) // DMA IRQ1 Interrupt
#define DMAIRQ2_INT_ID  (194) // DMA IRQ2 Interrupt
#define DMAIRQ3_INT_ID  (195) // DMA IRQ3 Interrupt
#define DMAIRQ4_INT_ID  (196) // DMA IRQ4 Interrupt
#define DMAIRQ5_INT_ID  (197) // DMA IRQ5 Interrupt
#define DMAIRQ6_INT_ID  (198) // DMA IRQ6 Interrupt
#define DMAIRQ7_INT_ID  (199) // DMA IRQ7 Interrupt
#define DMAIRQ8_INT_ID  (200) // DMA IRQ8 Interrupt
#define DMAIRQ9_INT_ID  (201) // DMA IRQ9 Interrupt
#define DMAIRQ10_INT_ID (202) // DMA IRQ10 Interrupt
#define DMAIRQ11_INT_ID (203) // DMA IRQ11 Interrupt
#define DMAIRQA_INT_ID  (204) // DMA IRQ About Interrupt
// RSVD
#define RTCTICK_INT_ID (208) // RTC Tick Interrupt
#define RTC_INT_ID     (209) // RTC Interrupt
#define SYSMPM_INT_ID  (210) // System Management Power Mode Interrupt
#define SYSMPW_INT_ID  (211) // System Management Power Warning Interrupt
#define SYSMSD_INT_ID  (212) // System Management Shut Down Interrupt
#define SYSMSL_INT_ID  (213) // System Management Sleep Interrupt

#define SYSRTC_IO3_ID      (208)
#define SYSRTC_SLEEP_ID    (210)
#define SYSRTC_SHUTDOWN_ID (211)
#define SYSRTC_POWERIND_ID (212)
#define SYSRTC_IO0_ID      (213)
#define SYSRTC_IO1_ID      (214)
#define SYSRTC_IO2_ID      (215)
#define SYSRTC_TOTAL_ID    (216)
// RSVD
#define CPU0PMU_INT_ID    (224) // CPU0 Performance Monitoring Unit Interrupt
#define CPU1PMU_INT_ID    (225) // CPU1 Performance Monitoring Unit Interrupt
#define CPU2PMU_INT_ID    (226) // CPU2 Performance Monitoring Unit Interrupt
#define CPU3PMU_INT_ID    (227) // CPU3 Performance Monitoring Unit Interrupt
#define CPU0COMMTX_INT_ID (228) // CPU0 COMMTX Interrupt
#define CPU1COMMTX_INT_ID (229) // CPU1 COMMTX Interrupt
#define CPU2COMMTX_INT_ID (230) // CPU2 COMMTX Interrupt
#define CPU3COMMTX_INT_ID (231) // CPU3 COMMTX Interrupt
#define CPU0COMMRX_INT_ID (232) // CPU0 COMMRX Interrupt
#define CPU1COMMRX_INT_ID (233) // CPU1 COMMRX Interrupt
#define CPU2COMMRX_INT_ID (234) // CPU2 COMMRX Interrupt
#define CPU3COMMRX_INT_ID (235) // CPU3 COMMRX Interrupt
#define CPU0CTI_INT_ID    (236) // CPU0 Cross Trigger Interface Interrupt
#define CPU1CTI_INT_ID    (237) // CPU1 Cross Trigger Interface Interrupt
#define CPU2CTI_INT_ID    (238) // CPU2 Cross Trigger Interface Interrupt
#define CPU3CTI_INT_ID    (239) // CPU3 Cross Trigger Interface Interrupt
#define CPUL2C_INT_ID     (240) // CPU L2 Cache Interrupt
#define G2D_INT_ID        (249) // G2D Interrupt
// RSVD
#define GIC_INTR_MAX (256)
//#endif

#if 0
typedef void(*INTR_ISR)(void);

int intr_register(int intr, INTR_ISR isr, int flag);
int intr_enable(int intr);
int intr_disable(int intr);
int intr_clear(int intr);
int intr_mask(int intr);
int intr_unmask(int intr);
int intr_dis_disable(void);
#endif

#endif // __INTERRUPT_X9_H__
