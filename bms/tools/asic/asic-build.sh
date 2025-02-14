#!/bin/bash

CUR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TOP_DIR=$(realpath $CUR_DIR/../..)
ARCHIVE=0
CLEAN_BUILD=0
DEUBG_FILES=0
SAVED_FILES=""
HASH_TYPE="crc"
SIGN_TYPE="none"
EXTEND_BOOTFR=0
DDR_INTLEAVE=0

RAM="ddr"
SOC="c920"
declare -a RAM_LIST=($RAM)
declare -a SOC_LIST=($SOC)
ARTIFACTS=${ARTIFACTS:-${TOP_DIR}/tools/asic/artifacts}

JUMP_TYPE=${JUMP_TYPE:-"cpu"}

trap failure SIGINT

failure () {
    echo "Failed: exiting ..."

    exit 1
}

show_help () {
    echo "Usage: asic-build.sh [options]"
    echo "Options:"
    echo "  -r, --ram: ram type (ddr, ddr1, iram), default is ddr"
    echo "  --int: use ddr intleave mode"
    echo "  -s, --soc: soc type (c920, e906), default is c920"
    echo "  -a: archive the output, default is not archive"
    echo "  --debug: save more files (.elf, .lds, .map, .config) for debug, default is not save"
    echo "  -c: clean artifacts before build, default is not clean"
    echo "  --conf: use configuration file"
    echo "  --sign: sign type (none, sm2, ecdsa), default is none"
    echo "  --hash: hash type (crc, sha256, sm3, sm2_e), default is crc"
    echo "  --extend-bootfr: extend boot.fr to 750KB for boot speed test, default is not extend"
    echo "  -h, --help: show this help message"
    echo "Example:"
    echo "  Build ddr target for c920:      ./tools/asic/asic-build.sh -r ddr -s c920"
    echo "  Build ddr1 target for c920:     ./tools/asic/asic-build.sh -r ddr1 -s c920"
    echo "  Build intleave target for c920: ./tools/asic/asic-build.sh -r ddr -s c920 --int"
    echo "  Build iram target for c920:     ./tools/asic/asic-build.sh -r iram -s c920"
    echo "  Build ddr target for e906:      ./tools/asic/asic-build.sh -r ddr -s e906"
    echo "  Build ddr1 target for e906:     ./tools/asic/asic-build.sh -r ddr1 -s e906"
    echo "  Build intleave target for e906: ./tools/asic/asic-build.sh -r ddr -s e906 --int"
    echo "  Build iram target for e906:     ./tools/asic/asic-build.sh -r iram -s e906"
}

gen_boot_fr () {
    local src=$1
    local dst=$2

    cd $TOP_DIR

    if [ $EXTEND_BOOTFR -eq 1 ]; then
        head -c $(( 512 * 1024 - $(stat -c %s $src) - 512)) /dev/urandom >> $src
    fi

    local ec_keys_dir=$TOP_DIR/tools/asic/ec_keys
    local opts="-h crc"

    case $HASH_TYPE in
    crc)
        opts="-h crc"
        ;;
    sha256)
        opts="-h sha256"
        ;;
    sm3)
        opts="-h sm3"
        ;;
    sm2_e)
        opts="-h sm2_e -u ${ec_keys_dir}/SM2PublicKey.pem"
        ;;
    *)
        echo "Invalid hash type: $HASH_TYPE, use crc as default"
        ;;
    esac

    case $SIGN_TYPE in
    none)
        ;;
    sm2)
        opts="$opts -g sm2 -p ${ec_keys_dir}/SM2PrivateKey.pem"
        ;;
    ecdsa)
        opts="$opts -g ecdsa -p ${ec_keys_dir}/ec_prime256v1_prikey.pem"
        ;;
    *)
        echo "Invalid sign type: $SIGN_TYPE, use none as default"
        opts="$opts -g none"
        ;;
    esac

    tools/asic/iuw64 genisi -r -j ${JUMP_TYPE} \
        -t boot -a 0x14200000 -e 0x14200200 \
        -n boot.fr -d $src -o $dst $opts || failure
}

build_source () {
    local defconfig=$1

    cd $TOP_DIR
    rm -rf out || true

    make $defconfig || failure
    if [ "$SOC" == "c920" ]; then
        sed -i '/\bCONFIG_BOOT_OTHER_CORE\b/c\CONFIG_BOOT_OTHER_CORE=y' out/.config
    fi

    if [ "$RAM" == "ddr" ]; then
        sed -i '/CONFIG_TB_RUN_IRAM/c# CONFIG_TB_RUN_IRAM is not set' out/.config
        sed -i '/\bCONFIG_TB_RUN_DDR\b/c\CONFIG_TB_RUN_DDR=y' out/.config
        sed -i '/CONFIG_BOOTM/c\CONFIG_BOOTM=0xf' out/.config
        if [ $DDR_INTLEAVE -eq 1 ]; then
            sed -i '/CONFIG_BOOTM/c\CONFIG_BOOTM=0xe' out/.config
        fi
    elif [ "$RAM" == "ddr1" ]; then
        sed -i '/CONFIG_TB_RUN_IRAM/c# CONFIG_TB_RUN_IRAM is not set' out/.config
        sed -i '/\bCONFIG_TB_RUN_DDR1\b/c\CONFIG_TB_RUN_DDR1=y' out/.config
        sed -i '/CONFIG_BOOTM/c\CONFIG_BOOTM=0xd' out/.config
        
    elif [ "$RAM" == "iram" ]; then
        sed -i '/\bCONFIG_TB_RUN_IRAM\b/c\CONFIG_TB_RUN_IRAM=y' out/.config
        sed -i '/\bCONFIG_TB_RUN_DDR\b/c# CONFIG_TB_RUN_DDR is not set' out/.config
        sed -i '/\bCONFIG_TB_RUN_DDR1\b/c# CONFIG_TB_RUN_DDR1 is not set' out/.config
    fi

    (make -j$((`nproc` + 1)); make) || failure
}


build_asic_rom () {
    echo "Building asic rom ======================"

    JUMP_TYPE="sap"

    build_source e906_asic_orom_defconfig

    echo "Build asic rom successful ======================"
}

# 1. Build asic rom -> soc.bin
# 2. Generate boot.fr from the soc.bin -> boot.fr
# 3. Build ddr target -> soc.bin
# 4. Package output soc.bin and boot.fr
build_target () {
    local defconfig="${SOC}_asic_${RAM%%[0-9]*}_defconfig"

    echo "Building ${SOC^^} ${RAM^^} target ======================"

    build_asic_rom
    gen_boot_fr $TOP_DIR/out/rom.bin $OUTPUT_DIR/boot.fr
    if [ $DEUBG_FILES -eq 1 ]; then
        eval cp $TOP_DIR/out/rom.${SAVED_FILES} $OUTPUT_DIR/ 2>/dev/null
        cp $TOP_DIR/out/.config $OUTPUT_DIR/rom.config
    fi

    build_source $defconfig
    cp $TOP_DIR/out/soc.bin $OUTPUT_DIR/
    if [ $DEUBG_FILES -eq 1 ]; then
        eval cp $TOP_DIR/out/soc.${SAVED_FILES} $OUTPUT_DIR/ 2>/dev/null
        cp $TOP_DIR/out/.config $OUTPUT_DIR/soc.config
    fi

    echo "Build ${SOC^^} ${RAM^^} target successful ======================"
}

archive_target () {
    local build_time=$(date '+%Y-%m-%d_%H-%M-%S')

    echo "Archiving target ======================"
    tar -czf $ARTIFACTS/${SOC}_${RAM}_${build_time}.tar.gz -C $OUTPUT_DIR . || failure
    echo "Archiving target successful ======================"
}

check_valid () {
    case $RAM in
    iram|ddr|ddr1)
        ;;
    *)
        echo "Invalid ram type: $RAM"
        return 1
        ;;
    esac

    case $SOC in
    c920|e906)
        ;;
    *)
        echo "Invalid soc type: $SOC"
        return 1
        ;;
    esac
}

USE_CONF=0
for arg in "$@"; do
    case $arg in
        --conf)
            source $2 && USE_CONF=1
            shift 2
            ;;
        *)
            ;;
    esac
done

if [ $USE_CONF -eq 0 ]; then

while [[ $# -gt 0 ]]; do
    key="$1"

    case $key in
    --all)
        RAM_LIST=("ddr" "ddr1" "iram")
        SOC_LIST=("c920" "e906")
        shift
        ;;
    -a)
        ARCHIVE=1
        shift
        ;;
    -c)
        CLEAN_BUILD=1
        shift
        ;;
    --extend-bootfr)
        EXTEND_BOOTFR=1
        shift
        ;;
    --debug)
        DEUBG_FILES=1
        SAVED_FILES="{bin,elf,lds,map,S}"
        shift
        ;;
    --int)
        DDR_INTLEAVE=1
        shift
        ;;
    -r|--ram)
        IFS=',' read -r -a RAM_LIST <<< "$2"
        shift 2
        ;;
    -s|--soc)
        IFS=',' read -r -a SOC_LIST <<< "$2"
        shift 2
        ;;
    --sign)
        SIGN_TYPE="$2"
        shift 2
        ;;
    -h|--help)
        show_help
        exit 0
        ;;
    --hash)
        HASH_TYPE="$2"
        shift 2
        ;;
    *)
        echo "Unknown option: $key"
        exit 1
        ;;
    esac
done

fi # USE_CONF=0

SUCCESS_TARGETS=""

for s in "${SOC_LIST[@]}"; do
    for r in "${RAM_LIST[@]}"; do
        SOC=$s
        RAM=$r

        check_valid || continue

        OUTPUT_DIR=${ARTIFACTS}/${SOC}_${RAM}
        if [ $DDR_INTLEAVE -eq 1 ]; then
            OUTPUT_DIR=${ARTIFACTS}/${SOC}_${RAM}_int
        fi

        if [ $CLEAN_BUILD -eq 1 ]; then
            rm -rf $OUTPUT_DIR
        fi

        mkdir -p $OUTPUT_DIR

        build_target

        if [ $ARCHIVE -eq 1 ]; then
            archive_target
        fi

        SUCCESS_TARGETS="${SUCCESS_TARGETS} ${SOC}_${RAM}"
    done
done

echo -e "\n\n"
echo "===================================="
echo "===================================="

echo "Build successful: ${SUCCESS_TARGETS:-"None"}"

echo "===================================="
echo "===================================="
echo -e "\n\n"


