#!/usr/bin/python3

import sys
import re
import os

cae_base_addr = "0xc5400000"

match_reg_write = r'\b\w*' + re.escape("reg info write") + r'\b'
match_cmd_descr = r'\b\w*' + re.escape("cdr0 ring dump") + r'\b'
match_result_descr = r'\b\w*' + re.escape("rdr0 ring dump") + r'\b'
match_dma_post = r'\b\w*' + re.escape("dma resource post") + r'\b'

cmd_descr_info_cnt = 16
result_descr_info_cnt = 2

match_writeword = r'\b\w*' + re.escape("WriteWord") + r'\b'
match_wb_ctx_b = r'\b\w*' + re.escape("ContextBuf: Write") + r'\b'
match_wb_in_t = r'\b\w*' + re.escape("InputToken: Write") + r'\b'
match_wb_p_i_b = r'\b\w*' + re.escape("PktInBuf: Write") + r'\b'
match_wb_rdr0_b = r'\b\w*' + re.escape("EIP97.EIP202.RDR0Buf: Write") + r'\b'
match_wb_cdr0_b = r'\b\w*' + re.escape("EIP97.EIP202.CDR0Buf: Write") + r'\b'
match_writeword64 = r'\b\w*' + re.escape("WriteWord64") + r'\b'
match_estimated = r'\b\w*' + re.escape("estimated") + r'\b'
match_record_1 = r'\b\w*' + re.escape("Record 1") + r'\b'
match_complete_packet = r'\b\w*' + re.escape("complete packet") + r'\b'
match_checkblock = r'\b\w*' + re.escape("CheckBlock") + r'\b'
match_sharp = "#"

in_path = "./testscripts/"
out_path = "./out/"

ddk_in_file = "./ddk_in.txt"
ddk_out_file = "ddk_out.txt"

def reg_dump_insert_head(file):
    with open(file, "a") as content:
        content.write("----reg dump----\n")
        content.close()

def sort_key(item):
    return int(item.split(',')[0], 16)

def reg_dump_sort(file):
    data = ""
    with open(file, "r") as content:
        data = content.readlines()
        content.close()

    sorted_data = sorted(data, key = sort_key)
    os.system("rm -rf " + file)
    reg_dump_insert_head(file)
    with open(file, "a") as content:
        for line in sorted_data:
           content.write(line)
        content.close()

def ddk_reg_dump(file, addr, val):
    with open(file + ".reg", "a") as content:
        content.write(addr + val + "\n")
        content.close()

def ddk_descr_dump(file, content):
    with open(file + ".descr", "a") as f_output:
        f_output.write(content)
        f_output.close()

def ivp_reg_dump(file, content):
    with open(file + ".reg", "a") as f_output:
        f_output.write(content + "\n")
        f_output.close()

def ivp_descr_dump(file, content):
    with open(file, "a") as f_output:
        f_output.write(content + "\n")
        f_output.close()

def ivp_leftover_handle(out_file):
    reg_dump_sort(out_file + ".reg")
    dump_combine(out_file + ".reg", out_file + ".cdr")
    dump_combine(out_file + ".reg", out_file + ".data")
    dump_combine(out_file + ".reg", out_file + ".token")
    dump_combine(out_file + ".reg", out_file + ".context")
    dump_combine(out_file + ".reg", out_file + ".rdr")
    os.system("mv " + out_file + ".reg " + out_file)
    os.system("rm -rf " + out_file + ".cdr")
    os.system("rm -rf " + out_file + ".data")
    os.system("rm -rf " + out_file + ".token")
    os.system("rm -rf " + out_file + ".context")
    os.system("rm -rf " + out_file + ".rdr")

def dump_combine(dst_file, src_file):
    with open(src_file, 'r') as src, open(dst_file, 'a') as dst:
        content = src.read()
        dst.write(content)

def get_stop_cnt(in_file):
    tmp_cnt = 0
    with open(in_file, "r") as file_content:
        for line in file_content:
            if (len(re.findall(match_dma_post, line)) > 0):
                tmp_cnt += 1
        return tmp_cnt

def ddk_start_parse(in_file, out_file):
    stop_cnt = get_stop_cnt(in_file)
    tmp_cnt = 0
    with open(in_file, "r") as file_content:
        for line in file_content:
            if tmp_cnt >= stop_cnt:
                break
            if (len(re.findall(match_reg_write, line)) > 0):
                columns = line.split()
                ddk_reg_dump(out_file, columns[3], columns[4])
                continue
            elif len(re.findall(match_cmd_descr, line)) > 0:
                ddk_descr_dump(out_file, line)
                for i in range(cmd_descr_info_cnt):
                   next_line = next(file_content, None)
                   ddk_descr_dump(out_file, next_line)
            elif len(re.findall(match_result_descr, line)) > 0:
                ddk_descr_dump(out_file, line)
                for i in range(result_descr_info_cnt):
                   next_line = next(file_content, None)
                   ddk_descr_dump(out_file, next_line)
            elif (len(re.findall(match_dma_post, line)) > 0):
                tmp_cnt += 1
            else:
                continue
    reg_dump_sort(out_file + ".reg")
    dump_combine(out_file + ".reg", out_file + ".descr")
    os.system("mv " + out_file + ".reg " + out_file)
    os.system("rm -rf " + out_file + ".descr")

def ivp_handle_file(in_filename, out_file):
    cdr_again_flg = 0
    data_again_flg = 0
    token_again_flg = 0
    context_again_flg = 0
    rdr_again_flg = 0
    with open(in_filename, "r") as f_input:
        for line in f_input:
            if len(re.findall(match_estimated, line)) > 0:
                while True:
                    line = next(f_input, None)
                    if line:
                        if len(re.findall(match_record_1, line)) > 0:
                            break
                        else:
                            continue
                    else:
                        return

            if len(re.findall(match_writeword, line)) > 0:
                columns = line.split()
                ivp_reg_dump(out_file, str(hex(int(cae_base_addr, 16) + int(columns[2], 16))) + "," + columns[3])
            elif len(re.findall(match_writeword64, line)) > 0:
                columns = line.split()
                ivp_reg_dump(out_file, str(hex(int(cae_base_addr, 16) + int(columns[2], 16))) + "," + columns[3])
                ivp_reg_dump(out_file, str(hex(int(cae_base_addr, 16) + int(columns[2], 16) + 0x4)) + "," + columns[3])
            elif (len(re.findall(match_wb_cdr0_b, line)) > 0) or len(re.findall(match_wb_p_i_b, line)) > 0 or \
                 (len(re.findall(match_wb_in_t, line)) > 0) or (len(re.findall(match_wb_ctx_b, line))) or \
                 (len(re.findall(match_wb_rdr0_b, line)) > 0):
                for i in range(2):
                    next_line = next(f_input, None)
                columns = next_line.split()

                if len(re.findall(match_wb_cdr0_b, line)) > 0:
                    if cdr_again_flg == 0:
                        tmp_out_file = out_file + ".cdr"
                        ivp_descr_dump(tmp_out_file, "----cdr0 ring dump: " + columns[2] + "----")
                        cdr_again_flg = 1
                    else:
                        continue
                elif len(re.findall(match_wb_p_i_b, line)) > 0:
                    if data_again_flg == 0:
                        tmp_out_file = out_file + ".data"
                        ivp_descr_dump(tmp_out_file, "----cdr0 data dump: " + columns[2] + "----")
                        data_again_flg = 1
                    else:
                        continue
                elif len(re.findall(match_wb_in_t, line)) > 0:
                    if token_again_flg == 0:
                        tmp_out_file = out_file + ".token"
                        ivp_descr_dump(tmp_out_file, "----cdr0 input token dump: " + columns[2] + "----")
                        token_again_flg = 1
                    else:
                        continue
                elif len(re.findall(match_wb_ctx_b, line)) > 0:
                    if context_again_flg == 0:
                        tmp_out_file = out_file + ".context"
                        ivp_descr_dump(tmp_out_file, "----cdr0 context buf dump: " + columns[2] + "----")
                        context_again_flg = 1
                    else:
                        continue
                elif len(re.findall(match_wb_rdr0_b, line)) > 0:
                    if rdr_again_flg == 0:
                        tmp_out_file = out_file + ".rdr"
                        ivp_descr_dump(tmp_out_file, "----rdr0 ring dump: " + columns[2] + "----")
                        rdr_again_flg = 1
                    else:
                        continue

                for i in range(2):
                    next_line = next(f_input, None)
                if next_line:
                    while True:
                        columns = next_line.split()
                        for i in range(len(columns)):
                                ivp_descr_dump(tmp_out_file, "0x" + columns[i])
                        next_line = next(f_input, None)
                        if next_line.startswith(match_sharp):
                            break
                        else:
                            continue
            elif len(re.findall(match_complete_packet, line)) > 0:
                while True:
                    tmp_line = next(f_input, None)
                    if tmp_line is None:
                        break
                    if len(re.findall(match_writeword, tmp_line)) > 0:
                        columns = tmp_line.split()
                        ivp_reg_dump(out_file, str(hex(int(cae_base_addr, 16) + int(columns[2], 16))) + "," + columns[3])
                    elif len(re.findall(match_checkblock, tmp_line)) > 0:
                        return
            else:
                continue

def ivp_traversal_file(directory):
    for name in os.listdir(directory):
        path = os.path.join(directory, name)
        if os.path.isfile(path):
            in_file = path
            print(in_file)
            out_file = os.path.basename(path)
            out_file, file_suffix = os.path.splitext(out_file)
            out_file = out_path + out_file + ".txt"
            print(out_file)
            if in_file == "./testscripts/intc/intc_hia.ivp" or \
               in_file == "./testscripts/reg_test/eip97_reg_test.ivp":
                return
            ivp_handle_file(in_file, out_file)
            ivp_leftover_handle(out_file)
        elif os.path.isdir(path):
            ivp_traversal_file(path)

def ivp_start_parse(in_path):
    ivp_traversal_file(in_path)

if __name__ == "__main__":
    test_type = sys.argv[1]
    print("start parse...")
    print("input path: " + in_path)
    print("output path: " + out_path)

    if not os.path.exists(out_path):
        os.system("mkdir -p out")
    else:
        os.system("rm -rf ./out/")
        os.system("mkdir -p out")

    if test_type == "ivp":
        print("parse ivp start!")
        ivp_start_parse(in_path)
        print("parse ivp finished!")
    elif test_type == "ddk":
        print("parse ddk start!")
        ddk_start_parse(ddk_in_file, out_path + ddk_out_file)
        print("parse ddk finished!")
    else:
        print("wrong params!")
