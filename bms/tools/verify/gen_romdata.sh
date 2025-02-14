#!/bin/sh

#addr=`grep -n "load address"  out/rom.map | head -1 | tr -s " " |cut -d " " -f 6`
datastring=`grep -n "load address"  out/rom.map | head -1 | tr -s " "`
dataaddr=`echo $datastring | cut -d " " -f 6`
datalen=`echo $datastring | cut -d " " -f 3`

dd if=out/rom.bin of=out/rom_data.bin skip=$(($dataaddr)) bs=1 count=$(($datalen))
