
#include "../lpddr4_common.h"

extern volatile int def_low_freq;
extern volatile int def_init_disable;
extern volatile int def_phy_pll_bypass;
extern volatile int def_phy_bist;
extern volatile int def_phy_loopback;
extern volatile int def_pi_training;
extern volatile int def_jtag_boundary_test;
extern volatile int def_axi_base_test;
extern volatile int def_lp_test;
extern volatile int def_dfs_test;
extern volatile int def_zq_cal;
extern volatile int def_axi_priority;
extern volatile int def_mr_test;
extern volatile int def_parallel_test;
extern volatile int def_march_c_test;
extern volatile int def_prbs_test;
extern volatile int def_rambuster;

void lpddr4_wcfg (void ) ;
void lpddr4_loopback_wcfg (void ) ;

extern void lpddr4_pi_training(int port, int is_lpddr4x, int freq);
extern void lpddr4_test_rw(void);
extern int lpddr4_rambuster(int port, int is_lpddr4x);

int lpddr4_rtl_asic_test(void)
{
#ifdef CONFIG_COMPILE_ASIC
	if (def_pi_training) {
		lpddr4_pi_training(0, 1, 2133);
		lpddr4_pi_training(1, 1, 2133);
	}
	if (def_low_freq) {
		lpddr4_pi_training(0, 1, 1066);
		lpddr4_pi_training(1, 1, 1066);
		lpddr4_test_rw();
	}
	if (def_rambuster) {
		lpddr4_rambuster(0, 0);
	}
	if (def_lp_test) {
        lpddr4_lp_srpd_test();
	}
	if (def_mr_test) {
		/* mr5 */
		lpddr4_mrr_test(0, 5);
		/* mr15 */
		lpddr4_mrw_test(15, 0);
	}
	if (def_dfs_test) {
		lpddr4_dfs_test();
	}
	if (def_axi_base_test) {
       	axi_base_test();
	}
	if (def_phy_pll_bypass) {
		lpddr4_phy_pll_bypass_test();
	}
	if (def_phy_bist) {
		phy_dll_bist_test();
	}
	if (def_zq_cal) {
        lpddr4_zq_cal();
	}
	if (def_axi_priority) {
        lpddr4_axi_priority_test();
	}
	if (def_jtag_boundary_test) {
		jtag_boundary_test();
	}
	if (def_march_c_test || def_prbs_test) {
		lpddr4_bist_test();
	}
#else

	if (def_parallel_test) {
		parallel_conflict_test();
		return 0;
	}

	/* pll init. */
	lpddr4_pll_init();

#ifndef CONFIG_COMPILE_ASIC
	if (def_low_freq)
		lpddr4_pll_freq(1066);
#endif

	if (!def_init_disable) {
		if (def_low_freq)
			sys_lpddr4_init_1066(0);
		else
			rtl_sys_lpddr4_init();
	}

	/* mpu sysm port reset release. */
        MA_OUTW(0xc30f0000 + 0x0, 0x0);

	if (def_phy_pll_bypass)
		phy_pll_bypass();

	if (def_pi_training && def_phy_bist != 1 && def_phy_loopback != 1 && def_jtag_boundary_test != 1) {
		/* pi training. */
        	sys_lpddr4_init_row_16();
#ifdef CONFIG_COMPILE_ASIC
		if (def_low_freq)
			lpddr4_pi_init_and_training_533();
		else
#endif
        		lpddr4_pi_init_and_training();
		printf("PI training done\n");
	}

	if (def_phy_bist)
		phy_dll_bist_test();

	if (def_phy_loopback)
        	loopback_test();

	if (def_jtag_boundary_test)
        	jtag_boundary_test();

	if (def_axi_base_test)
       		axi_base_test();

	if (def_lp_test)
        	lpddr4_lp_srpd_test();

	if (def_dfs_test)
		lpddr4_dfs_test();

	if (def_zq_cal)
        	lpddr4_zq_cal();

	if (def_axi_priority)
        	lpddr4_axi_priority_test();

	if (def_mr_test) {
		/* mr5 */
		lpddr4_mrr_test(0, 5);
		/* mr15 */
		lpddr4_mrw_test(15, 0);
	}

	if (def_march_c_test || def_prbs_test)
		lpddr4_bist_test();
#endif
	return 0;
}

