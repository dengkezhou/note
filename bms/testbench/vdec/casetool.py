#!/usr/bin/env python3
# coding: utf-8

import argparse
import struct
import re
from pathlib import Path

def vcmd_text2bin(input, output, base=10):
    with open(input, 'r') as fi, open(output, 'wb') as fo:
        fi_lines = fi.readlines()
        for line in fi_lines:
            line = line.strip()
            if base == 16:
                line = line[:8]
                data = int(line, base).to_bytes(4, 'little')
            else:
                data = int(line, base).to_bytes(16, 'little')
            fo.write(data)

def vcmd_ctrlflow2bytes(input):
    data = b''
    with open(input, 'r') as fi:
        for line in fi.readlines():
            line = line.split()[2]
            data += int(line, 16).to_bytes(16, 'little')
    
    return data


def vcmd_bytes2text(bytes, output, width = 8):
    if width == 8:
        fmt = f'{len(bytes) // width}Q'
    elif width == 4:
        fmt = f'{len(bytes) // width}I'
    else:
        print('Unsupported width')
        return

    with open(output, 'r') as fo:
        for x in struct(fmt, bytes):
            pass


def vcmd_bin2text(in_path, out_path):
    with open(in_path, 'rb') as fi, open(out_path, 'w') as fo:
        data = fi.read()
        if len(data) % 4 != 0:
            print('Data should align with 4 bytes')
            return
        for x in struct.unpack(f'{len(data) // 4}I', data):
            fo.write(f'{x:08x}\n')


TYPE_VCMD     = (1 << 1)
TYPE_STRM_IN  = (1 << 2)
TYPE_STRM_OUT = (1 << 3)
TYPE_FLUSH    = (1 << 4)

def write_metadata_to_file(outdir = '.', **kwargs):
    struct_format = '=64s I Q I'

    metadata = (
        kwargs.get('name', ''*64).encode(),
        kwargs.get('type', 0),
        kwargs.get('addr', 0),
        kwargs.get('len', 0)
    )

    packed_data = struct.pack(struct_format, *metadata)

    with open(Path(outdir) / 'metadata.bin', 'ab') as file:
        file.write(packed_data)


def sim_ctrl_flow_to_bin(input, output):
    def split_frame(lines):
        pattern = r'# Frame \d+'
        line_numbers = []
        for i, line in enumerate(lines, start=0):
            if re.search(pattern, line):
                line_numbers.append(i)
        
        return line_numbers
    
    def get_vcmd_data(lines, outdir = '.'):
        pattern1 = r'INIT_DDR: 0x[0-9a-fA-F]{16} (0x[0-9a-fA-F]{32})'
        pattern2 = r'VCMD.*configuration: addr.*to.*(0x[0-9a-fA-F]{16}).*'
        vcmd_bin = b''
        for line in lines:
            res = re.search(pattern1, line)
            if res:
                vcmd_bin += int(res.groups()[0], 16).to_bytes(16, 'little')

            res = re.search(pattern2, line)
            if res:
                addr = int(res.groups()[0], 16)
        write_metadata_to_file(outdir, 
                                name = 'vcmd.bin',
                                type = TYPE_VCMD,
                                addr = addr
                                )
        return vcmd_bin

    def get_strm_data(lines, outdir = '.'):
        pattern = r'INIT_DDR: .*frame.*/(.*?) (0x[0-9a-fA-F]{16})'
        for line in lines:
            res = re.search(pattern, line)
            if res:
                file_name = res.groups()[0]
                addr = int(res.groups()[1], 16)
                # gdb_cmd = f'restore {file_name} binary {addr}'
                # print(gdb_cmd)

                write_metadata_to_file(outdir, 
                                       name = file_name,
                                       type = TYPE_STRM_IN,
                                       addr = addr,
                                       )
    
    def get_output_data(lines, outdir = '.'):
        pattern = r'CHECK_DDR: .*frame.*/(.*?) (0x[0-9a-fA-F]{16}) (0x[0-9a-fA-F]+)'
        for line in lines:
            res = re.search(pattern, line)
            if res:
                file_name = res.groups()[0]
                addr = int(res.groups()[1], 16)
                len = int(res.groups()[2], 16)
                # addr_e = hex(int(addr_s, 16) + int(len, 16))
                # gdb_cmd = f'dump binary memory {file_name} {addr_s} {addr_e}'
                # print(gdb_cmd)
                write_metadata_to_file(outdir, 
                                       name = file_name,
                                       type = TYPE_STRM_OUT,
                                       addr = addr,
                                       len = len
                                       )


    def get_flush_data(lines, outdir = '.'):
        pattern = r'FLUSH_DDR: base (0x[0-9a-fA-F]{16}).*len (\d+).*'
        for line in lines:
            res = re.search(pattern, line)
            if res:
                addr = int(res.groups()[0], 16)
                len = int(res.groups()[1], 10)
                # gdb_cmd = f'memset({addr}, 0, {len})'
                # print(gdb_cmd)
                write_metadata_to_file(outdir, 
                                       type = TYPE_FLUSH,
                                       addr = addr,
                                       len = len
                                       )


    all_lines = []
    with open(input, 'r') as f: 
        all_lines = f.readlines()

    frame_lines = split_frame(all_lines)
    # print(f'Total frames: {frame_lines}')

    for i, _ in enumerate(frame_lines):
        # print('\n' + all_lines[frame_lines[i]])
        line_start = frame_lines[i]
        line_end = frame_lines[i+1] - 1 if i + 1 < len(frame_lines) else None
        frame_line = all_lines[line_start:line_end]

        basedir = Path(output) / f'frame{i}'
        vcmd_file = basedir / 'vcmd.bin'

        basedir.mkdir(parents=True, exist_ok=True)
        Path(basedir / 'metadata.bin').unlink(missing_ok=True)

        with open(vcmd_file, 'wb') as fo:
            fo.write(get_vcmd_data(frame_line, basedir))
            get_strm_data(frame_line, basedir)
            get_output_data(frame_line, basedir)
            get_flush_data(frame_line, basedir)
        
        write_metadata_to_file(basedir)
        

parser = argparse.ArgumentParser(description='Tool for parse vc9000d localcase')
parser.add_argument('-c', '--case-dir', help='case dir', default='.')
parser.add_argument('-o', '--out-dir', help='out dir', default='.')
parser.add_argument('-d', '--dump-to-case', help='save output to case dir', action='store_true')

args = parser.parse_args()

sim_flow_file = Path(args.case_dir) / 'testdata/simulation_ctrl_flow_core0.txt'

if args.dump_to_case:
    args.out_dir = Path(args.case_dir) / 'testdata'

"""
./casetool.py \
  --case-dir ~/Documents/vc9000d_golden_data_150000000/h264_h264@0 \
  --out-dir /home/builder/workspace/bms-worktree/frigob/rtl/vdec-testdata/h264_h264@0/testdata

restore ~/workspace/bms-worktree/frigob/rtl/vdec-localcase/tools/rtlfs/rtlfs.bin binary 0x140000000
restore ~/workspace/bms-worktree/frigob/rtl/vdec-localcase/tools/rtlfs/rtlfs-h264_h264@401.bin binary 0x140000000
restore ~/workspace/bms-worktree/frigob/rtl/vdec-rtlfs/rtlfs-h264_h264@4.bin binary 0x140000000

for d in `find /home/builder/workspace/bms-worktree/frigob/rtl/vdec-testdata -maxdepth 1 -type d -name  '*@*'`; do
    casedir=`realpath $d`
    echo "./casetool.py -d --case-dir $casedir"
    ./casetool.py -d --case-dir $casedir
done
"""
sim_ctrl_flow_to_bin(sim_flow_file, args.out_dir)