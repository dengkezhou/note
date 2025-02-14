#!/usr/bin/env python3
import os

header_size = 0x100000
current_path = os.getcwd()
bin_file_path = current_path + '/rtlfs.bin'

# 创建一个空的inode
def create_empty_inode(index):
    inode = {
        'index': index,
        'offset': 0,
        'size': 0,
        'dau': 0,
        'sib': 0,
        'name': ''
    }
    return inode

def read_file_from_rtlfsbin(source_file_path, destination_file_path, offset, size):
    with open(source_file_path, 'rb') as source_file:
        with open(destination_file_path, 'wb') as destination_file:
            source_file.seek(offset)
            bytes_read = 0
            while bytes_read < size:
                remaining_bytes = size - bytes_read
                chunk_size = min(1024, remaining_bytes)
                chunk = source_file.read(chunk_size)
                if not chunk:
                    break
                destination_file.write(chunk)
                bytes_read += len(chunk)

def get_parent_path(path):
    parent_path = os.path.dirname(path)
    return parent_path + '/'



def read_header_partition_and_build_folder(file_path):
    f_path = 'root/'
    # 每个 finode 结构的大小
    finode_size = 256
    index = 0
    
    def read_one_inode(index, f_path):
        file.seek(index * finode_size)
        inode = create_empty_inode(index)
        # 读取 inode 的数据
        inode['offset'] = int.from_bytes(file.read(4), 'little')  # 读取 offset
        inode['size'] = int.from_bytes(file.read(4), 'little')  # 读取 size
        inode['dau'] = int.from_bytes(file.read(4), 'little')  # 读取 dau
        inode['sib'] = int.from_bytes(file.read(4), 'little')  # 读取 sib
        # 读取 name
        name_bytes = bytearray()
        for i in range(0, 240, 1):
            byte = file.read(1)
            if byte == b'\x00':
                break
            name_bytes += byte

        inode['name'] = name_bytes.decode('ascii')

        if index == 0:
            if inode['name'] != 'root/':
                return False
            index = index + 1
            read_one_inode(index, f_path)
        else:
            if inode['name'] == '':
                return True
            if inode['size'] == 0:#folder
                f_path = f_path + inode['name'] + '/'
                index = inode['dau']
                if index != 0:
                    read_one_inode(index, f_path)
                index = inode['sib']
                if index != 0:
                    read_one_inode(index, f_path)
                else:
                    f_path = get_parent_path(f_path)
            else:#file
                name = f_path + inode['name']
                size_hex = hex(inode['size'])

                print(f"file: {name:<32}  size: {size_hex:<10} ")
                index = inode['sib']
                if index != 0:
                    read_one_inode(index, f_path)
                else:
                    f_path = get_parent_path(f_path)
    
            

    # 打开文件以进行读取
    with open(file_path, 'rb') as file:
        return read_one_inode(index, f_path)



def extract_rtlfsbin(bin_file_path):
    print('Parsing rtlfs.bin...')
    print('----------------------------------------------------------------------------------------')
    read_header_partition_and_build_folder(bin_file_path)
    print('----------------------------------------------------------------------------------------')
    print('Parse rtlfs.bin done')

# 主函数
def main():
    global bin_file_path
    extract_rtlfsbin(bin_file_path)

if __name__ == '__main__':
    main()
