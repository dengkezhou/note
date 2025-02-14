#!/bin/bash
${WD_WHISPER} --target=out/eh1.elf --startpc=0x0 --configfile=./tools/whisper_eh1.json --alarm=100 --consoleio=0x80002000 --counters
