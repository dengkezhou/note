#!/bin/bash

set -x
PORT=12233
docker run -it --rm -p $PORT:$PORT -n c906 \
           -e PATH=/csky/bin -v $PWD:/wss \
           tmp/cskysim \
           cskysim -kernel /wss/out/c906.elf -soc /wss/tools/c906_cfg.xml -gdb tcp::$PORT -nographic
    
