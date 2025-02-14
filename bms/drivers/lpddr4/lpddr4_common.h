#ifndef __LPDDR4_COMMON_H__
#define __LPDDR4_COMMON_H__

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <dma-ops.h>
#include <asm/io.h>
#include <getopt.h>
#include <cache.h>
#include <pads.h>
#ifdef CONFIG_MMU
#include <mmu_table.h>
#endif

#define CLKGEN_BASE 0xc2f08000

#ifdef CONFIG_E906
/* mpu0 */
#define MLCLKG_BASE (CLKGEN_BASE + 0xc0)
#else
/* mpu1 */
#define MLCLKG_BASE (CLKGEN_BASE + 0xc0 + 0x170)
#endif

#define SCLKGEN_BASE 0xd2f08000

#define CLKGEN_ALDCFG (CLKGEN_BASE + 0x1c)
#define CLKGEN_AEN (CLKGEN_BASE + 0x20)
#define CLKGEN_ASEL (CLKGEN_BASE + 0x24)
#define CLKGEN_ALOCK (CLKGEN_BASE + 0x28)

#define CLKGEN_BLDCFG (CLKGEN_BASE + 0x3c0 + 0x1c)
#define CLKGEN_BEN (CLKGEN_BASE + 0x3c0 + 0x20)
#define CLKGEN_BSEL (CLKGEN_BASE + 0x3c0 + 0x24)
#define CLKGEN_BLOCK (CLKGEN_BASE + 0x3c0 + 0x28)

#define CLKGEN_DLDCFG (CLKGEN_BASE + 0x4c)
#define CLKGEN_DEN (CLKGEN_BASE + 0x50)
#define CLKGEN_DSEL (CLKGEN_BASE + 0x54)
#define CLKGEN_DLOCK (CLKGEN_BASE + 0x58)

#define CLKGEN_ELDCFG (CLKGEN_BASE + 0x7c)
#define CLKGEN_EEN (CLKGEN_BASE + 0x80)
#define CLKGEN_ESEL (CLKGEN_BASE + 0x84)
#define CLKGEN_ELOCK (CLKGEN_BASE + 0x88)

#define CLKGEN_VDIVQ (CLKGEN_BASE + 0x9c)
#define CLKGEN_VLDCFG (CLKGEN_BASE + 0xac)
#define CLKGEN_VEN (CLKGEN_BASE + 0xb0)
#define CLKGEN_VSEL (CLKGEN_BASE + 0xb4)
#define CLKGEN_VLOCK (CLKGEN_BASE + 0xb8)

#define SCLKGEN_ALDCFG (SCLKGEN_BASE + 0x1c)
#define SCLKGEN_AEN (SCLKGEN_BASE + 0x20)
#define SCLKGEN_ALOCK (SCLKGEN_BASE + 0x28)
#define SCLKGEN_ASEL (SCLKGEN_BASE + 0x24)

#define SAPM_BASE (0xd2f08c00)

#define E906_MAP_TO_DDR 0x40000000

#define MA_OUTW(a, b) writel((b), (a))
#define MA_INW(a) readl((a))

typedef enum { AC = 0x0, ADR = 0x1, DATA = 0x2, MEMCLK = 0x3 } Slice_type;

typedef enum {
	AC_SLICE_0 = 0x0,
	AC_SLICE_1 = 0x1,
	ADR_SLICE = 0x2,
	DATA_SLICE_0 = 0x3,
	DATA_SLICE_1 = 0x4,
	DATA_SLICE_2 = 0x5,
	DATA_SLICE_3 = 0x6
} Slice_num;

typedef struct {
	uint32_t pi_dram_init_en;
	uint32_t pi_init_lvl_en;
	uint32_t pi_calvl_en_f0;
	uint32_t pi_calvl_en_f1;
	uint32_t pi_calvl_en_f2;
	uint32_t pi_wrlvl_en_f0;
	uint32_t pi_wrlvl_en_f1;
	uint32_t pi_wrlvl_en_f2;
	uint32_t pi_rdlvl_gate_en_f0;
	uint32_t pi_rdlvl_gate_en_f1;
	uint32_t pi_rdlvl_gate_en_f2;
	uint32_t pi_rdlvl_en_f0;
	uint32_t pi_rdlvl_en_f1;
	uint32_t pi_rdlvl_en_f2;
	uint32_t pi_wdqlvl_en_f0;
	uint32_t pi_wdqlvl_en_f1;
	uint32_t pi_wdqlvl_en_f2;
} pi_lvl_en_t;

void write_register(uint32_t address, uint32_t data);
void write_apbmux_register(uint32_t address, uint32_t data);
void write_boundary_register(uint32_t address, uint32_t data);
void write_register_array(uint32_t array[]);
uint32_t read_register(uint32_t address);
uint32_t read_apbmux_register(uint32_t address);
uint32_t read_boundary_register(uint32_t address);

void sys_lpddr4_init(void);
void fpga_axi_init(void);
void fpga_sys_lpddr4_start(void);

void lpddr4_pll_init(void);
void lpddr4_pll_freq(uint32_t freq);
void sys_lpddr4_init_1066(int mpu_no);
void rtl_sys_lpddr4_init(void);
void lpddr4_zq_cal(void);
void phy_pll_bypass(void);
void sys_lpddr4_start_1066(void);
void sys_lpddr4_start(void);
void phy_dll_bist_test(void);
void loopback_test(void);
void jtag_boundary_test(void);
void axi_base_test(void);
void lpddr4_lp_srpd_test(void);
void sys_lpddr4_init_row_16(void);
void lpddr4_pi_init_and_training(void);
void lpddr4_dfs_test(void);
void lpddr4_axi_priority_test(void);
void loopback_phy_manual_training(uint32_t loopback_mode);
void mc_dfi_update_count_set(void);
void mc_dfi_auto_update_conf(void);
void mc_refresh_conf(void);
void phy_disable_dly_ctrl_power_reduction(void);
void phy_wait_for_dfi_complete_init(uint32_t data_slice_check,uint32_t acs_slice_check,uint32_t adr_slice_check,uint32_t ac_slice_check);
void mc_lpi_wakeup_en(void);
void phy_sw_master_mode(void);
void phy_cs_training_disable(int mpu_no);
void phy_auto_update_conf(void);
void phy_input_enable(void);
void lp_aref_enable(uint32_t enable);
float clk_max(float ns,float nclk);
void axi_init(void);

uint64_t lpddr4_mrr_test(uint32_t cs,uint32_t mr);
void lpddr4_mrw_test(uint32_t mr,uint32_t data);
int parallel_conflict_test(void);
void lpddr4_pi_init_and_training_533(void);
void lpddr4_bist_test(void);

#endif
