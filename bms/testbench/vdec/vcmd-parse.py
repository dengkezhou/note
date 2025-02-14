#!/usr/bin/env python3
# coding: utf-8

import argparse
import struct

parser = argparse.ArgumentParser(description='Tool for parse vcmd')
parser.add_argument('vcmd', help='vcmd path')

args = parser.parse_args()


def wreg_parse(val):
    opcode = (val >> 27) & 0x1f
    fix    = (val >> 26) & 0x01
    length = (val >> 16) & 0x3ff
    start_reg = (val >> 00) & 0xffff
    return (opcode, fix, length, start_reg)


def wreg_print(val):
    val = struct.unpack(f'{len(val) // 4}I', val)
    for i, x in enumerate(val):
        if i <= 411:
            print(f'swreg{i}={x:08X}')
        elif i >= 448:
            print(f'swreg{i-64}_pp1={x:08X}')

with open(args.vcmd, 'rb') as f:
    data = f.read()

    wreg_cmd = struct.unpack('I', data[:4])[0]
    _, _, wreg_len, addr = wreg_parse(wreg_cmd)
    wreg_print(data[4: wreg_len * 4])
