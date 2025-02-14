/*
 * pmic_core.c regulators driver.
 */

#include <common.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <linux/err.h>
#include <pads.h>
#include <i2c.h>
#include <irq.h>
#include <asm/bits.h>
#include <pmic.h>
#include <stdbool.h>

#include "axp15060.h"
#include "isl68221.h"

static struct pmic_dev *pmdev[MAX_PMIC_VARIANTS];
static unsigned int init_flag;

struct pmic_ids {
	char name[16];
	int (* init)(struct pmic_dev *pmdev);
};

static int is_inited(unsigned int pmic){
	return init_flag & BIT(pmic);
}

struct pmic_ids pm_table[16] = {
	{ .name = "axp15060", .init = axp15060_init },
	{ .name = "isl68221", .init = isl68221_init },
	{/* other module*/},
};

static int pmic_add_regulator(struct pmic_dev *dev, struct regulator_dev *rdev, bool state){
	struct regulator_dev *tmp0 = NULL, *tmp1 = NULL;

	if(state) {
		if(!dev->nrdev){
			dev->rdev = rdev;
			dev->nrdev++;
		} else {
			tmp0 = dev->rdev;
			while(tmp0){
				tmp1 = tmp0;
				tmp0 = tmp0->next;
			}
			tmp1->next = rdev;
			dev->nrdev++;
		}
	} else {
		if(!dev->nrdev){
			printf("error: no one regulator active!!!\n");
			return -1;
		} else if(dev->nrdev == 1){
			if (strcmp(rdev->desc->name, dev->rdev->desc->name) == 0){
				dev->rdev = NULL;
				dev->nrdev--;
			}else{
				printf("error: no %s regulator active!!!\n", rdev->desc->name);
				return -1;
			}
		} else {
			tmp0 = dev->rdev;
			tmp1 = tmp0->next;
			while(tmp1){
				if (strcmp(tmp1->desc->name, rdev->desc->name) == 0){
					break;
				}
				tmp0 = tmp1;
				tmp1 = tmp1->next;
			}
			if(strcmp(tmp1->desc->name, rdev->desc->name) == 0){
				tmp0->next = tmp1->next;
				dev->nrdev--;
			}else{
				printf("error: no %s regulator active!!!\n", rdev->desc->name);
				return -1;
			}
		}
	}

	return 0;
}

static int regulator_is_busy(unsigned int pmic,const char *name){
	struct pmic_dev *dev;
	struct regulator_dev *rdev;

	dev = pmdev[pmic];
	rdev = dev->rdev;

	for(int i = 0; i < dev->nrdev; i++){
		if (strcmp(rdev->desc->name, name) == 0)
			 return -1;
		else{
			rdev = rdev->next;
		}
	}
	return 0;
}

static int pmic_init(unsigned int pmic){
	struct pmic_dev *dev;
	int ret;

	if(is_inited(pmic))
		return 0;

	pmdev[pmic] = malloc(sizeof(*dev));
	memset(pmdev[pmic], 0, sizeof(*dev));

	ret = pm_table[pmic].init(pmdev[pmic]);
	if(ret < 0)
		return -1;
	init_flag |= BIT(pmic);

	return 0;
}

/*from name get regulator_dev*/
struct regulator_dev *itcs_regulator_get(unsigned int pmic,const char *name){
	struct regulator_dev *rdev;

	pmic_init(pmic);
	if(regulator_is_busy(pmic, name))
		return NULL;

	rdev = malloc(sizeof(*rdev));
	memset(rdev, 0, sizeof(*rdev));

	rdev->pmic_dev = pmdev[pmic];

	for(int i = 0; i < rdev->pmic_dev->ndesc; i++){
		if (strcmp(rdev->pmic_dev->desc[i].name, name) == 0)
			rdev->desc = &rdev->pmic_dev->desc[i];
	}
	rdev->next = NULL;

	pmic_add_regulator(rdev->pmic_dev, rdev, 1);

	return rdev;
}

void itcs_regulator_put(struct regulator_dev *rdev){
	int ret;

	ret = pmic_add_regulator(rdev->pmic_dev, rdev, 0);
	if(ret){
		printf("regulator put failed!\n");
	}
	free(rdev);
}

// check regulator is enabled
int itcs_regulator_is_enabled(struct regulator_dev *rdev) {
		return rdev->pmic_dev->ops->is_enabled(rdev);
}

//enable regulator
int itcs_regulator_enable(struct regulator_dev *rdev) {
	return rdev->pmic_dev->ops->enable(rdev);
}

//disable regulator
int itcs_regulator_disable(struct regulator_dev *rdev){
	return rdev->pmic_dev->ops->disable(rdev);
}

//get regulator voltage
int itcs_regulator_get_voltage(struct regulator_dev *rdev){
	return rdev->pmic_dev->ops->get_voltage(rdev);
}

//get regulator current 
int itcs_regulator_get_current(struct regulator_dev *rdev){
	if (rdev->pmic_dev->ops->get_current)
  	return rdev->pmic_dev->ops->get_current(rdev);

	return -1;
}

//set voltage
int itcs_regulator_set_voltage(struct regulator_dev *rdev, int min_uV, int max_uV){
	return rdev->pmic_dev->ops->set_voltage(rdev, min_uV, max_uV);
}

int itcs_print_pmic_all_voltages(unsigned int pmic) {
	struct pmic_dev *dev;
	struct regulator_dev *rdev, *tmp;
	int ret;

	pmic_init(pmic);

	dev = pmdev[pmic];

	if(pmic == 0)
		printf("pmic apx15060:\n");

	for (int i = 0; i < dev->ndesc; i++) {
		rdev = itcs_regulator_get(pmic, dev->desc[i].name);
		if (!rdev){
			//already exist, traverse
			tmp = dev->rdev;
			while(tmp && strcmp(dev->desc[i].name, tmp->desc->name)){
				tmp = tmp->next;
			}
			if(!tmp){
				return -1;
			}
			rdev = tmp;
		}
		if(!strcmp(rdev->desc->name, "sw")){
			continue;
		}
		ret = itcs_regulator_get_voltage(rdev);
		if (ret < 0) {
			printf("	%s: get voltage error!\n", dev->desc[i].name);
			itcs_regulator_put(rdev);
			return ret;
		}
		itcs_regulator_put(rdev);
		printf("	%-8s: %d\n", dev->desc[i].name, ret);
	}

	return 0;
}

int itcs_pmic_info(unsigned int pmic){
	struct pmic_dev *dev;
	struct regulator_dev *rdev, *tmp;

	pmic_init(pmic);

	dev = pmdev[pmic];

	if(pmic == 0) {
		printf("pmic apx15060:\n");
	} else if (pmic == 1) {
		printf("pmic isl68221:\n");
	} else {
		return -1;
	}
	printf("%-10s %-25s %-15s %-10s %-20s\n", "Name", "Voltage Range(mv)", "Step", "Enabled", "Current Voltage(mv)");
	printf("-------------------------------------------------------------------------------\n");

	for (int i = 0; i < dev->ndesc; i++) {
		rdev = itcs_regulator_get(pmic, dev->desc[i].name);
		if (!rdev){
			//already exist, traverse
			tmp = dev->rdev;
			while(tmp && strcmp(dev->desc[i].name, tmp->desc->name)){
				tmp = tmp->next;
			}
			if(!tmp){
				return -1;
			}
			rdev = tmp;
		}
		if(!strcmp(rdev->desc->name, "sw") || !strcmp(rdev->desc->name, "rtc-ldo")){
			continue;
		}
		if(rdev->desc->linear_ranges){
			printf("%-10s ", rdev->desc->name);

			for (int j = 0; j < rdev->desc->n_linear_ranges; j++) {
				if(j == 0){
					printf("%-5d-%5d%15s ", rdev->desc->linear_ranges[j].min / 1000, (rdev->desc->linear_ranges[j].min + 
						 rdev->desc->linear_ranges[j].step * 
						(rdev->desc->linear_ranges[j].max_sel - rdev->desc->linear_ranges[j].min_sel)) / 1000, "");
					printf("%-15d ", rdev->desc->linear_ranges[j].step / 1000);
					printf("%-10s ", rdev->pmic_dev->ops->is_enabled ? "Yes" : "No");
					printf("%-20d", itcs_regulator_get_voltage(rdev) / 1000);
				} else {
					printf("\n%8sor %-5d-%5d%15s ", "", rdev->desc->linear_ranges[j].min / 1000, (rdev->desc->linear_ranges[j].min + 
						 rdev->desc->linear_ranges[j].step * 
						(rdev->desc->linear_ranges[j].max_sel - rdev->desc->linear_ranges[j].min_sel)) / 1000, "");
					printf("%-15d", rdev->desc->linear_ranges[j].step / 1000);
				}
				if( j == rdev->desc->n_linear_ranges - 1){
					printf("\n");
				}
			}
		} else {
			printf("%-10s %-5d-%5d%15s %-15d ", rdev->desc->name, rdev->desc->min_uV / 1000, 
					rdev->desc->max_uV / 1000, "", rdev->desc->uV_step / 1000);
			printf("%-10s ", rdev->pmic_dev->ops->is_enabled ? "Yes" : "No");
			printf("%-20d\n", itcs_regulator_get_voltage(rdev) / 1000);
		}
		itcs_regulator_put(rdev);
	}

	return 0;
}
