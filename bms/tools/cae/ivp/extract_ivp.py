#!/usr/bin/python3

import sys
import re
import os

cae_base_addr = "ivp_cae_base_addr+"

cdr0_data_base_addr = "0x00000008"
cdr0_token_base_addr = "0x00000010"
cdr0_ring_base_addr = "0x00000000"

cdr1_data_base_addr = "0x00001008"
cdr1_token_base_addr = "0x00001010"
cdr1_ring_base_addr = "0x00001000"

rdr0_data_base_addr = "0x00000808"
rdr0_ring_base_addr = "0x00000800"

rdr1_data_base_addr = "0x00001808"
rdr1_ring_base_addr = "0x00001800"

match_cmdtrig = r'\b\w*' + re.escape("CMD_TRIG") + r'\b'
match_restrigprep = r'\b\w*' + re.escape("RES_TRIG_PREP") + r'\b'
match_restrigproc = r'\b\w*' + re.escape("RES_TRIG_PROC") + r'\b'
match_writeword = r'\b\w*' + re.escape("WriteWord") + r'\b'
match_readword = r'\b\w*' + re.escape("ReadWord") + r'\b'
match_wb_ctx_b = r'\b\w*' + re.escape("ContextBuf: Write") + r'\b'
match_wb_in_t = r'\b\w*' + re.escape("InputToken: Write") + r'\b'
match_wb_p_i_b = r'\b\w*' + re.escape("PktInBuf: Write") + r'\b'
match_wb_p_o_b = r'\b\w*' + re.escape("PktOutBuf: Write") + r'\b'
match_wb_rdr0_b = r'\b\w*' + re.escape("EIP97.EIP202.RDR0Buf: Write") + r'\b'
match_wb_cdr0_b = r'\b\w*' + re.escape("EIP97.EIP202.CDR0Buf: Write") + r'\b'
match_writeword64 = r'\b\w*' + re.escape("WriteWord64") + r'\b'
match_estimated = r'\b\w*' + re.escape("estimated") + r'\b'
match_record_1 = r'\b\w*' + re.escape("Record 1") + r'\b'
match_pollword = r'\b\w*' + re.escape("PollWord") + r'\b'
match_complete_packet = r'\b\w*' + re.escape("complete packet") + r'\b'
match_checkblock = r'\b\w*' + re.escape("CheckBlock") + r'\b'
match_sharp = "#"
match_checkword = r'\b\w*' + re.escape("CheckWord") + r'\b'
checkword_cnt = 0
match_data = r'\b\w*' + re.escape("Data ") + r'\b'
match_waitclock = r'\b\w*' + re.escape("WaitClock") + r'\b'
match_devicereset = r'\b\w*' + re.escape("DeviceReset") + r'\b'
match_0x00000000 = r'\b\w*' + re.escape("0x00000000") + r'\b'
match_passcnt = r'pass_cnt\+\+;'
insert_cnt = 0
match_writeblock = r'\b\w*' + re.escape("WriteBlock") + r'\b'

test_type = sys.argv[1]
location = sys.argv[2]
in_path = "./testscripts/"
out_path = "./out/"

def format_c_header(filename):
    with open(filename, "w") as file_out:
        filename = os.path.basename(filename)
        filename, file_suffix = os.path.splitext(filename)
        file_out.write("#include <common.h>\n")
        file_out.write("#include <malloc.h>\n")
        if filename == "intc_hia":
            file_out.write("#include <irq.h>\n")
        file_out.write("\n")
        file_out.write("extern volatile unsigned int ivp_cae_base_addr;\n")
        file_out.write("\n")
        if filename == "intc_hia":
            file_out.write("static volatile unsigned int pass_cnt=0;\n")
            file_out.write("static volatile unsigned int base_irq;\n")
            file_out.write("\n")
            file_out.write("static int cae_ivp_irq_handler(int irq, void *args)\n")
            file_out.write("{\n")
            file_out.write("if(irq==base_irq+4){\n")
            file_out.write("pass_cnt++;\n")
            file_out.write("}else if(irq==base_irq+0){\n")
            file_out.write("pass_cnt++;\n")
            file_out.write("}else if(irq==base_irq+1){\n")
            file_out.write("pass_cnt++;\n")
            file_out.write("}else if(irq==base_irq+2){\n")
            file_out.write("pass_cnt++;\n")
            file_out.write("}else if(irq==base_irq+3){\n")
            file_out.write("pass_cnt++;\n")
            file_out.write("}else{\n")
            file_out.write("printf(\"ivp wrong irq number: \%d\\n\",irq);\n")
            file_out.write("}\n")
            file_out.write("return 0;\n")
            file_out.write("}\n")
            file_out.write("\n")
        file_out.write("void " + filename + "(void)\n")
        file_out.write("{\n")
        if location == "ddr":
            file_out.write("unsigned int *context_ptr=(unsigned int *)0x14000000;\n")
        elif location == "iram":
            file_out.write("unsigned int *context_ptr=malloc(64*1024);\n")
        else:
            print("wrong location\n")
            sys.exit(0)
        if filename == "eip97_reg_test":
            file_out.write("unsigned int cnt=0;\n")
        file_out.write("printf(\"" + filename + "\\n\");\n")
        file_out.write("if(!context_ptr)\n")
        file_out.write("printf(\"context_ptr malloc failed!\\n\");\n")
        file_out.write("#ifdef CONFIG_COMPILE_FPGA\n")
        file_out.write("memset(context_ptr,0,64*1024);\n")
        file_out.write("#endif\n")
        if filename == "intc_hia":
            file_out.write("if(ivp_cae_base_addr==ITCS_C_CAE0_BASE)\n")
            file_out.write("base_irq=C_CAE0_IRQn;\n")
            file_out.write("else\n")
            file_out.write("base_irq=C_CAE5_IRQn;\n")
            file_out.write("request_irq(base_irq,cae_ivp_irq_handler,\"ring0\",NULL);\n")
            file_out.write("request_irq(base_irq+1,cae_ivp_irq_handler,\"ring1\",NULL);\n")
            file_out.write("request_irq(base_irq+2,cae_ivp_irq_handler,\"ring2\",NULL);\n")
            file_out.write("request_irq(base_irq+3,cae_ivp_irq_handler,\"ring3\",NULL);\n")
            file_out.write("request_irq(base_irq+4,cae_ivp_irq_handler,\"out\",NULL);\n")
        file_out.close()

def format_c_tail(filename):
    global checkword_cnt
    global insert_cnt
    with open(filename, "a") as file_out:
        filename = os.path.basename(filename)
        filename, file_suffix = os.path.splitext(filename)
        if filename == "intc_hia":
            file_out.write("if(pass_cnt==" + str(insert_cnt) + ")\n")
            file_out.write("printf(\"intc_hia Pass\\n\");\n")
            file_out.write("else\n")
            file_out.write("printf(\"intc_hia Failed, pass_cnt: %d\\n\",pass_cnt);\n")
            file_out.write("disable_irq(base_irq);\n")
            file_out.write("disable_irq(base_irq+1);\n")
            file_out.write("disable_irq(base_irq+2);\n")
            file_out.write("disable_irq(base_irq+3);\n")
            file_out.write("disable_irq(base_irq+4);\n")
        if filename == "eip97_reg_test":
            file_out.write("if(cnt==" + str(checkword_cnt) + ")\n")
            file_out.write("printf(\"eip97_reg_test Pass\\n\");\n")
            file_out.write("else\n")
            file_out.write("printf(\"eip97_reg_test Failed, cnt: %d\\n\",cnt);\n")
        if location == "iram":
            file_out.write("free(context_ptr);\n")
        file_out.write("}\n")
        file_out.close()

def append_content(filename, content):
    with open(filename, "a") as f_output:
        f_output.write(content)
        f_output.close()
        
def insert_content(filename, content, match_content, sequence):
    line_number = 0
    with open(filename, "r") as insert_stream:
        for i in range(sequence):
            for i_line in insert_stream:
                line_number += 1
                if len(re.findall(match_content, i_line)) > 0:
                    break
    with open(filename, "r+") as insert_stream:
        s_lines = insert_stream.readlines()
        s_lines.insert(line_number, content)
        insert_stream.seek(0)   
        insert_stream.writelines(s_lines)

def search_and_write_file(in_filename, out_filename):
    global checkword_cnt
    global insert_cnt
    format_c_header(out_filename)
    with open(in_filename, "r") as f_input:
        for line in f_input:
            if test_type == "single":
                if len(re.findall(match_estimated, line)) > 0:
                    while True:
                        line = next(f_input, None)
                        if len(re.findall(match_record_1, line)) > 0:
                            break
                        else:
                            continue

            if (len(re.findall(match_cmdtrig, line)) > 0) or (len(re.findall(match_restrigprep, line)) > 0) or \
               (len(re.findall(match_restrigproc, line)) > 0):
                continue
            elif (len(re.findall(match_waitclock, line)) > 0) and (in_filename == "./testscripts/intc/intc_hia.ivp"):
                append_content(out_filename, "udelay(1);\n")
            elif (len(re.findall(match_writeword, line)) > 0) and (in_filename == "./testscripts/intc/intc_hia.ivp") and \
                 (len(re.findall(match_0x00000000, line)) > 0):
                insert_cnt += 1
                columns = line.split()
                insert_content(out_filename, "writel(" + columns[3] + "&" + columns[4] + "," + cae_base_addr + columns[2] + ");\n", match_passcnt, insert_cnt)
            elif (len(re.findall(match_devicereset, line)) > 0) and (in_filename == "./testscripts/reg_test/eip97_reg_test.ivp"):
                append_content(out_filename, "itcs_module_reset(CPU,\"cae\");\n")
            elif (len(re.findall(match_checkword, line)) > 0) and (in_filename == "./testscripts/reg_test/eip97_reg_test.ivp"):
                checkword_cnt += 1
                columns = line.split()
                append_content(out_filename, "if((readl(ivp_cae_base_addr+" + columns[2] + ")&" + columns[4] + ")==(" + columns[3] + "&" + columns[4] + "))\n")
                append_content(out_filename, "cnt++;\n")
                append_content(out_filename, "else\n")
                append_content(out_filename, "printf(\"cnt: " + str(checkword_cnt) + "\\n\");\n")
            elif len(re.findall(match_writeword, line)) > 0:
                columns = line.split()
                append_content(out_filename, "writel(" + columns[3] + "&" + columns[4] + "," + cae_base_addr + columns[2] + ");\n")
            elif len(re.findall(match_writeword64, line)) > 0:
                columns = line.split()
                if (columns[2] == cdr0_data_base_addr) or (columns[2] == cdr0_token_base_addr) or \
	           (columns[2] == cdr0_ring_base_addr) or (columns[2] == cdr1_data_base_addr) or \
	           (columns[2] == cdr1_token_base_addr) or (columns[2] == rdr0_data_base_addr) or \
	    	   (columns[2] == rdr1_data_base_addr) or columns[2] == cdr1_ring_base_addr or \
                   (columns[2] == rdr0_ring_base_addr) or (columns[2] == rdr1_ring_base_addr):
                    append_content(out_filename, "writel(((unsigned long)context_ptr+" + columns[3] + ")&" + columns[4] + "," + cae_base_addr + columns[2] + ");\n")
                    append_content(out_filename, "writel((((unsigned long)context_ptr+" + columns[3] + ")>>32)&(" + columns[4] + ">>32)," + cae_base_addr + columns[2] + "+0x4" + ");\n")
                else:
                    append_content(out_filename, "writel(" + columns[3] + "&" + columns[4] + "," + cae_base_addr + columns[2] + ");\n")
                    append_content(out_filename, "writel(" + columns[3] + "&" + columns[4] + ">>32," + cae_base_addr + columns[2] + "+0x4" + ");\n")
            elif len(re.findall(match_readword, line)) > 0:
                columns = line.split()
                append_content(out_filename, "readl(" + cae_base_addr + columns[2] + ");\n")
            elif len(re.findall(match_wb_p_o_b, line)) > 0:
                continue
            elif (len(re.findall(match_wb_ctx_b, line)) > 0) or (len(re.findall(match_wb_in_t, line)) > 0) or \
                 (len(re.findall(match_wb_p_i_b, line)) > 0) or (len(re.findall(match_wb_rdr0_b, line)) > 0) or \
                 (len(re.findall(match_wb_cdr0_b, line)) > 0):
                 for i in range(2):
                    next_line = next(f_input, None)
                 if next_line:
                    columns = next_line.split()
                    offset = columns[2]
                    offset_cnt = 0
                    offset_base = columns[2]
                    for i in range(2):
                        next_line = next(f_input, None)
                    if next_line:
                        while True:
                            columns = next_line.split()
                            for i in range(len(columns)):
                                if ((len(re.findall(match_wb_cdr0_b, line)) > 0) and ((i == 5))):
                                    append_content(out_filename, "*((unsigned int *)((unsigned long)context_ptr+" + offset + "))=0x" + columns[i] + "+(unsigned long)context_ptr" + ";\n")
                                else:
                                    append_content(out_filename, "*((unsigned int *)((unsigned long)context_ptr+" + offset + "))=0x" + columns[i] + ";\n")
                                offset_cnt += 1
                                offset = offset_base + "+4*" + str(offset_cnt)
                            next_line = next(f_input, None)
                            if next_line.startswith(match_sharp):
                                if (len(re.findall(match_wb_p_i_b, line)) > 0) and (in_filename == "./testscripts/packets_basic_crypto/test_bypass.ivp"):
                                    next_line = next(f_input, None)
                                    if len(re.findall(match_writeblock, next_line)) > 0:
                                        columns = next_line.split()
                                        offset = columns[2]
                                        offset_cnt = 0
                                        offset_base = columns[2]
                                        for i in range(2):
                                            next_line = next(f_input, None)
                                        continue
                                    else:
                                        break
                                else:
                                    break
                            else:
                                continue
            elif len(re.findall(match_writeword, line)) > 0:
                columns = line.split()
                append_content(out_filename, "writel(" + columns[3] + "&" + columns[4] + "," + cae_base_addr + columns[2] + ");\n")
            elif len(re.findall(match_pollword, line)) > 0:
                columns = line.split()
                append_content(out_filename, "while(1){\n")
                append_content(out_filename, "if((readl(" + cae_base_addr + columns[2] + ")&" + columns[4] + ")==" + columns[3] + ")\n")
                append_content(out_filename, "break;\n")
                append_content(out_filename, "}\n")
            elif len(re.findall(match_complete_packet, line)) > 0:
                finish_cur_flag = 0
                while True:
                    tmp_line = next(f_input, None)
                    if tmp_line is None:
                        break
                    if len(re.findall(match_writeword, tmp_line)) > 0:
                        columns = tmp_line.split()
                        append_content(out_filename, "writel(" + columns[3] + "&" + columns[4] + "," + cae_base_addr + columns[2] + ");\n")
                    elif len(re.findall(match_checkblock, tmp_line)) > 0:
                        columns = tmp_line.split()
                        append_content(out_filename, "if(!memcmp((unsigned char *)context_ptr+" + columns[2] + ",\"")
                        tmp_line = next(f_input, None)
                        if len(re.findall(match_data, tmp_line)) > 0:
                            columns = tmp_line.split()
                            result_len = columns[1]
                        result = ""
                        while True:
                            tmp_line = next(f_input, None)    
                            if tmp_line is not None:
                                null_line = tmp_line.strip()
                                result_end_flag = tmp_line.startswith(match_sharp)
                            else:
                                null_line = "not null line"
                                result_end_flag = False
                            if result_end_flag or not null_line or tmp_line is None:
                                 target_str = result
                                 insert_str = "\\x"
                                 target_str = insert_str.join(target_str[i:i+2] for i in range(0, len(target_str), 2))
                                 append_content(out_filename, "\\x" + target_str + "\"," + result_len + "))\n")
                                 append_content(out_filename, "printf(\"strip: " + result[:16] + ", Pass\\n\");\n")
                                 append_content(out_filename, "else\n")
                                 append_content(out_filename, "printf(\"strip: " + result[:16] + ", Failed\\n\");\n")
                                 if test_type == "single":
                                     format_c_tail(out_filename)
                                     return
                                 else:
                                     finish_cur_flag = 1
                                     break
                            else:
                                 columns = tmp_line.split()
                                 for i in range(len(columns)):
                                     hex_str = bytes.fromhex(columns[i])
                                     hex_str = hex_str[::-1]
                                     hex_str = hex_str.hex()
                                     result += hex_str
                        if test_type == "multi":
                            if finish_cur_flag == 1:
                                break
            else:
                continue
    if test_type == "multi":
        format_c_tail(out_filename)

def extract(in_filename, out_filename):
    if (test_type != "single") and (test_type != "multi"):
        print("wrong test type\n")
        sys.exit(0)
    search_and_write_file(in_filename, out_filename)

def traversal_file(directory):
    if not os.path.exists(out_path):
        os.system("mkdir -p out")
    for name in os.listdir(directory):
        path = os.path.join(directory, name)
        if os.path.isfile(path):
            in_file = path
            print(in_file)
            out_file = os.path.basename(path)
            out_file, file_suffix = os.path.splitext(out_file)
            out_file = out_path + out_file + ".c"
            print(out_file)
            extract(in_file, out_file)
        elif os.path.isdir(path):
            traversal_file(path)

if __name__ == "__main__":
    print("start extract")
    print("input path: " + in_path)
    print("output path: " + out_path)
    traversal_file(in_path)
    print("extract finished")
