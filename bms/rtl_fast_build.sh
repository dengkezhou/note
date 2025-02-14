#!/bin/bash

# 如果以下位置的'module'名称一致,
#     1. drivers/<module>
#     2. drivers/<module>/Kconfig中的config开关为'DRV_<module>'
#     3. testbench/<module>/Kconfig中的config开关为'TBH_<module>'
#     4. doc/verification/<module>.md
    
#     那么,可以使用rtl_fast_build.sh快速生成rtl case 测试压缩包

# source  /opt/py2/bin/activate

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\034[0;32m'
NC='\033[0m' # No Color

cpus=("c920" "e906")
loc=("ddr" "iram")
all_modules=$(find testbench/ -maxdepth 1 -type d | awk -F / '{print $2}')
# modules=$all_modules
modules=("pufcc") # 修改成你的模块名字

for c in ${cpus[@]}; do
    for m in ${modules[@]}; do
		for l in ${loc[@]}; do

		full_defconfig=configs/$c/${c}_rtl_${l%*[0-9]}_soc_defconfig
		mini_defconfig=configs/$c/${c}_rtl_${l%*[0-9]}_mini_soc_defconfig

		echo -e "\n\n\n${RED}Start build ${m^^} ${l^^}${NC}\n\n\n"

		echo -e "CONFIG_DRV_${m^^}=y\nCONFIG_COMPILE_TBH=y\nCONFIG_TBH_${m^^}=y" | cat $mini_defconfig -  > $full_defconfig
		echo -e "${GREEN}python tools/verify/verify.py rtlcases $c $m $l${NC}"
		python tools/verify/verify.py rtlcases $c $m $l
		echo -e "${GREEN}python tools/verify/verify.py $c $m RTL${NC}"
		python tools/verify/verify.py $c $m RTL
		done
    done
done
