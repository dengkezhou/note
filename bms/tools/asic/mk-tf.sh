#!/bin/bash

CUR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TOP_DIR=$(realpath $CUR_DIR/../..)

RAM="ddr"
SOC="c920"
IMAGE_DIR=""
DDR_INTLEAVE=0

TMP="/tmp/tmp.bmsXXXXXX"

trap failure SIGINT

cleanup () {
    umount /tmp/tmp.bms* 2>/dev/null || true
    rm -rf /tmp/tmp.bms* || true
}

failure () {
    echo "Failed: exiting ..."
    cleanup
    exit 1
}

make_partition () {
    if [ ! -b "$1" ]; then
        echo "Invalid device: $1"
        exit 1
    fi

    umount $1* 2>/dev/null || true
    (echo ",2G,0xc," | sfdisk -f -q $1 2> /dev/null ) || failure
    blockdev --rereadpt $1
    mkfs.fat -F 32 ${1}1 > /dev/null || failure
}

extract_archive () {
    local archive=$1
    local dir=$(mktemp -d $TMP)

    echo "Extracting archive $archive ..."

    tar -xvf $archive -C $dir || failure

    echo "Archive extracted to $dir"

    IMAGE_DIR=$dir
}

copy_image () {
    local device=$1
    local tmp_mnt=$(mktemp -d $TMP)

    mount ${device}1 $tmp_mnt || failure

    cp -a $IMAGE_DIR/* $tmp_mnt/ 2> /dev/null

    umount $tmp_mnt || failure
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
        -f|--file)
            FILE="$2"
            shift 2
            ;;
        -d|--device)
            DEVICE="$2"
            shift 2
            ;;
        -r|--ram)
            RAM="$2"
            shift 2
            ;;
        -s|--soc)
            SOC="$2"
            shift 2
            ;;
        -i|--int)
            DDR_INTLEAVE=1
            shift
            ;;
        -h|--help)
            echo "Usage: mk-tf.sh [options]"
            echo "Options:"
            echo "  -d, --device: device name, e.g. /dev/sdb"
            echo "  -h, --help: show this help message"
            echo "  -r, --ram: ram type (ddr, ddr1, iram), default is ddr"
            echo "  -i, --int: ddr intleave mode"
            echo "  -s, --soc: soc type (c920, e906), default is c920"
            echo "  -f, --file: archive file"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

fi # USE_CONF=0

if [ $EUID -ne 0 ]; then
    echo "Please run as root"
    exit 1
fi

if [ ! -b "$DEVICE" ]; then
    echo "Invalid device: $DEVICE"
    exit 1
fi

if [ -f "$FILE" ]; then
    extract_archive $FILE
elif [ -d "$FILE" ]; then
    IMAGE_DIR=$(realpath $FILE)
else
    IMAGE_DIR="${TOP_DIR}/tools/asic/artifacts/${SOC}_${RAM}"
    if [ $DDR_INTLEAVE -eq 1 ]; then
        IMAGE_DIR="${TOP_DIR}/tools/asic/artifacts/${SOC}_${RAM}_int"
    fi
fi

if [ ! -d "$IMAGE_DIR" ]; then
    echo "Invalid image directory: $IMAGE_DIR"
    exit 1
fi

echo "Image directory: $IMAGE_DIR"

make_partition $DEVICE

copy_image $DEVICE

echo -e "\n\nSuccessfull copied ${SOC}_${RAM} image to $DEVICE"

cleanup
 
