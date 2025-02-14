#!/usr/bin/env python3
import sys
def hex_bin(hexfile,binfile):
    with open(hexfile, 'r') as fh, open (binfile, 'wb') as fb:
        for line in fh.readlines():
            data = int(line.strip(), 16).to_bytes(8, 'little')
            fb.write(data)
def del_head(hexfile,binfile):
    with open(hexfile, 'r') as fh, open (binfile, 'wb') as fb:
        
        i = 0
        for line in fh.readlines():
            line=line.strip()
            if line=='':
                continue
            if(i==0):
                addr = line[0:9]
                data = int(addr, 16).to_bytes(8, 'little')
                fb.write(data)
                i = i+1
            s1=line[-8:]
            #data = int(s1.strip(), 16).to_bytes(8, 'little')
            data = int(s1, 16).to_bytes(4, 'little')
            fb.write(data)


            
if __name__=='__main__':
    print(sys.argv)
    # change_hex('mem2.hex','output.hex')
    if(sys.argv[1] == '2'):
        file_name = "mem"
        for j in range(0,int(sys.argv[2])):
            str1 = str(j)
            del_head(file_name+str1+'.init',file_name+str1+'.bin')
        exit()
    if(sys.argv[1]=='0'):
        for i in range(3,int(sys.argv[2])+3):   
            hex_file=(sys.argv[i]+'.init')
            bin_file=(sys.argv[i]+'.bin')
            del_head(hex_file,bin_file)
    else:
        for i in range(2,int(sys.argv[1])+2):
            hex_file=(sys.argv[i]+'.hex')
            bin_file=(sys.argv[i]+'.bin')
            hex_bin(hex_file,bin_file)
    # del_head('mem0_result.cmp','mem0_result.bin')
    
    # hex_file = 'mem5.hex'
    # bin_file = 'mem5.bin'
    # hex_bin(hex_file,bin_file)
    # hex_file = 'mem0_cmd_buffer.hex'
    # bin_file = 'mem0_cmd_buffer.bin'
    # hex_bin(hex_file,bin_file)
    # hex_file = 'mem1_vshader_buffer.hex'
    # bin_file = 'mem1_vshader_buffer.bin'
    # hex_bin(hex_file,bin_file)
    # arguments = sys.argv
    # hex_bin(arguments[1],arguments[2])
        



