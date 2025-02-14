#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os, sys
import re
import csv
from enum import Enum

class Linetype(Enum):
    OTHER = 0
    MODULENAME = 1
    CASENAME  = 2
    DESCRIPTION = 3
    EXPECTATION = 4
    COMMAND = 5
    LABEL = 6
    SKIPLINE = 7

def check_line_type(line):
    if re.match(r'###',line):
        return Linetype['SKIPLINE']

    if re.match(r'##',line):
        return Linetype['CASENAME']

    if re.match(r'#',line):
        return Linetype['MODULENAME']

    if re.match(r'----',line):
        return Linetype['LABEL']
    
    if line.find("Description") >= 0:
        return Linetype['DESCRIPTION']

    if line.find("Expectation") >= 0:
        return Linetype['EXPECTATION']

    if line.find("FPGA&RTL Params") >= 0:
        return Linetype['COMMAND']

    return Linetype['OTHER']

with open('abc.csv', 'a', newline='') as csvfile:
    w = csv.writer(csvfile)
    # 写入列头
    w.writerow(["测试ID号", "测试例名", "Action","Result","测试例组"])

# 打开文件
directory = "my_markdown_folder"
# 获取目录下的.md文件列表
files = os.listdir(directory)
md_files = [os.path.join(directory, f) for f in files if f.endswith('.md')]

id = 0
subid = 0
# 遍历每个.md文件，将指定行的数据写入Excel表格
for md_file in md_files:
    with open(md_file, 'r', encoding='UTF-8') as f:
        # 按行读，如果是想要的加到列表里，标记每一行对应的标题
        transmit=[]
        #module = {}
        flag_descri =0
        flag_expec = 0
        descri = ''
        expec = ''
        for line in f.readlines():
            line = line.strip(' \t\n')
            # skip space line and c language structure
            if line == '' or re.match(r'```', line):
                continue
            # print line
            linetype = check_line_type(line)
            if linetype ==Linetype['MODULENAME']:
                id=id+1
                continue
            if linetype == Linetype['SKIPLINE']:
                continue
            if linetype ==Linetype['COMMAND']:
                transmit.append(expec.strip())
                transmit.append(id)
                flag_expec = 0
                with open('abc.csv', 'a', newline='') as csvfile:
                    w = csv.writer(csvfile)
                    # 写入列头
                    w.writerow(transmit)
                continue
            if linetype == Linetype['LABEL']:
                continue
            if linetype == Linetype['CASENAME']:
                transmit=[]
                subid = subid+1
                transmit.append(subid)
                transmit.append(line.strip('#'))
                descri = ''
                expec = ''
                continue
            if linetype == Linetype['DESCRIPTION']:
                flag_descri = 1
                continue
            if linetype == Linetype['EXPECTATION']:
                transmit.append(descri.strip())
                flag_descri = 0
                flag_expec = 1
                continue
            if linetype == Linetype['OTHER']:
                if flag_descri == 1:
                    descri += '\n' + line    
                    continue
                elif flag_expec == 1:
                    expec += '\n' + line
                    continue
                else:
                    continue
os.rename('abc.csv','tests.csv' )
#print(id)
