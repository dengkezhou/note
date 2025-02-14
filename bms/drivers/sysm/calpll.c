#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <clock.h>
#include <common.h>

static int get_para_range(int mode, int freq, int fraction)
{
	switch (mode) {
	case DIVR: {
		int pfdMax = fraction ? PLL_PFD_FAC_MAX : PLL_PFD_INT_MAX;
		int pfdMin = fraction ? PLL_PFD_FAC_MIN : PLL_PFD_INT_MIN;
		int divrMax, divrMin;

		divrMin = DIV_ROUND_UP(freq, pfdMax) - 1;
		divrMax = freq / pfdMin - 1;

		if (divrMin > 64 || divrMax < 0) {
			printf("DIVR freq %d in %s mode: [%d, %d]\n", freq,
			       fraction ? "fraction" : "integer", divrMin,
			       divrMax);
			return -1;
		}
		// printf("get_para_range: [%d, %d]\n", divrMin, divrMax);
		divrMin = max(divrMin, 0);
		divrMax = min(divrMax, 64);
		// printf("+++get_para_range: [%d, %d]\n", divrMin, divrMax);
		return PARA_RANGE(divrMin, divrMax);
	}
	case DIVQ: {
		int divqMax, divqMin;

		divqMin = DIV_ROUND_UP(PLL_VCO_MIN, freq * 2) - 1;
		divqMax = PLL_VCO_MAX / (freq * 2) - 1;

		if (divqMin > 32 || divqMax < 0) {
			printf("DIVQ freq %d in %s mode: [%d, %d]\n", freq,
			       fraction ? "fraction" : "integer", divqMin,
			       divqMax);
			return -1;
		}
		// printf("get_para_range: [%d, %d]\n", divqMin, divqMax);
		divqMin = max(divqMin, 0);
		divqMax = min(divqMax, 32);
		// printf("++get_para_range: [%d, %d]\n", divqMin, divqMax);
		return PARA_RANGE(divqMin, divqMax);
	}
	case DIVQF: {
		int divqMax, divqMin;

		divqMin = DIV_ROUND_UP(PLL_VCO_MIN, freq) - 1;
		divqMax = PLL_VCO_MAX / freq - 1;

		if (divqMin > 6 || divqMax < 0) {
			printf("DIVQF freq %d in %s mode: [%d, %d]\n", freq,
			       fraction ? "fraction" : "integer", divqMin,
			       divqMax);
			return -1;
		}
		// printf("get_para_range: [%d, %d]\n", divqMin, divqMax);
		divqMin = max(divqMin, 0);
		divqMax = min(divqMax, 6);
		// printf("++get_para_range: [%d, %d]\n", divqMin, divqMax);
		return PARA_RANGE(divqMin, divqMax);
	}

	default:
		return -1;
	}
}

int pll_get_actual_clock(plldiv_t *div)
{
	if (div->isqf)
		return (CRYSTAL / (div->divr + 1) * 4 *
			(1 + div->divfi + (float)div->divff / (1 << 24)) /
			(div->divqf + 1));
	else
		return (CRYSTAL / (div->divr + 1) * 4 *
			(1 + div->divfi + (float)div->divff / (1 << 24)) /
			(2 * (div->divq + 1)));
}

int pll_calc_filter_range(unsigned long post_divr_freq, int fraction)
{
	int pfdMax = fraction ? PLL_PFD_FAC_MAX : PLL_PFD_INT_MAX;
	int pfdMin = fraction ? PLL_PFD_FAC_MIN : PLL_PFD_INT_MIN;

	if (post_divr_freq < pfdMin || post_divr_freq > pfdMax) {
		printf("post-divider reference freq out of range: %lu",
		       post_divr_freq);
		return -1;
	}

	switch (post_divr_freq) {
	case 5000 ... 7000:
		return 0;
	case 8000 ... 11000:
		return 1;
	case 12000 ... 18000:
		return 2;
	case 19000 ... 30000:
		return 3;
	case 31000 ... 50000:
		return 4;
	case 51000 ... 80000:
		return 5;
	case 81000 ... 130000:
		return 6;
	case 131000 ... 200000:
		return 7;
	}

	return 7;
}

static int pll_abs(int a)
{
	return (a > 0) ? a : -a;
}

int pll_cal_parameter(struct plldiv *div, int clk, int fraction)
{
	plldiv_t tmp;
	int divrR;
	int divqR;
	float divf;
	int Fpfd, Fout;
	int Fvco;
	int divsub = -1;

	tmp.isqf = false;
	if (clk < PLL_OUTPUT_MIN || clk > PLL_OUTPUT_MAX)
		return -1;

	divqR = get_para_range(DIVQ, clk, fraction);
	if (divqR < 0)
		return -1;

	divrR = get_para_range(DIVR, CRYSTAL, fraction);
	if (divrR < 0)
		return -1;

	for (tmp.divq = GetRangeMin(divqR); tmp.divq <= GetRangeMax(divqR);
	     tmp.divq++) {
		Fvco = clk * 2 * (tmp.divq + 1);
		// printf("Fvco %d\n", Fvco);
		for (tmp.divr = GetRangeMin(divrR);
		     tmp.divr <= GetRangeMax(divrR); tmp.divr++) {
			Fpfd = CRYSTAL / (tmp.divr + 1);
			// printf("Fpfd %d\n", Fpfd);
			divf = (float)Fvco / (4 * Fpfd);
			if (divf < 1)
				continue;

			if (fraction) {
				tmp.divfi = divf - 1;
				tmp.divff = (divf - 1 - tmp.divfi) * (1 << 24);
			} else {
				tmp.divfi = divf - 1;
				tmp.divff = 0;
			}
			/* tmp.divf[8:0], tmp.divff[23:0] */
			if (tmp.divfi > 0x1ff)
				tmp.divfi = 0x1ff;

			if (tmp.divff > 0xffffff)
				tmp.divff = 0xffffff;

			Fout = pll_get_actual_clock(&tmp);
			if (divsub < 0 || divsub > pll_abs(Fout - clk)) {
				divsub = pll_abs(Fout - clk);
				// memcpy(div, &tmp, sizeof(plldiv_t));
				div->clkrate = Fout;
				div->divr = tmp.divr;
				div->divq = tmp.divq;
				div->divfi = tmp.divfi;
				div->divff = tmp.divff;
				div->range =
					pll_calc_filter_range(Fpfd, fraction);
				div->isqf = tmp.isqf;

				if (!divsub)
					goto out;
			}
		}
	}
out:
	// printf("range %d, divr %d, divfi %d, divff %d, divq %d\n", div->range,
	// div->divr, div->divfi, div->divff, div->divq);
	return 0;
}
