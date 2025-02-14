#!/usr/bin/env python3
import os

#support 4096 files & folders
header_size = 0x100000
bin_file_path = 'rtlfs.bin'

# 创建一个空的inode
def create_empty_inode(index):
    inode = {
        'index': index,
        'data': bytearray(256)
    }
    return inode

# 创建一个0x80000大小的全0二进制文件
def create_empty_bin_file(file_path, size):
    with open(file_path, 'wb') as f:
        f.write(b'\x00' * size)

def write_file_to_rtlfsbin(source_file_path, destination_file_path):
    file_length = os.path.getsize(source_file_path)
    with open(source_file_path, 'rb') as source_file:
        with open(destination_file_path, 'ab') as destination_file:
            source_file.seek(0)
            destination_file.seek(0, 2)
            chunk_size = 1024  # 一次读取的块大小
            bytes_written = 0  # 已写入的字节数
            while bytes_written < file_length:
                remaining_bytes = file_length - bytes_written
                chunk = source_file.read(min(chunk_size, remaining_bytes))
                if not chunk:
                    break
                destination_file.write(chunk)
                bytes_written += len(chunk)
            # Check if the file size is not aligned to 8 bytes
            if file_length % 16 != 0:
                padding_size = 16 - (file_length % 16)
                padding = b'\x00' * padding_size
                destination_file.write(padding)
                return padding_size
    return 0

def build_inode_structure(path):
    global header_size 
    global bin_file_path
    def get_inode(path):
        inode = {
            'index': len(inode_structure),
            'offset': 0,
            'size': 0,
            'dau': 0,
            'sib': 0,
            'name': os.path.basename(path)
        }
        return inode

    def add_inode(inode):
        inode_structure.append(inode)

    def add_root():
        inode = get_inode(path)
        inode['name'] = 'root/'
        inode['size'] = 0xffffffff
        add_inode(inode)
    

    def traverse_folder(folder_path, parent_inode_index, offset):
        raw = 0
        index = 0
        last_index = 0
        for item in sorted(os.listdir(folder_path)):
            raw = raw + 1
            item_path = os.path.join(folder_path, item)
            if os.path.isdir(item_path):
                inode = get_inode(item_path)
                add_inode(inode)
                index = inode['index']
                inode['size'] = 0xffffffff
                if raw == 1 and index != 0:
                    inode_structure[index-1]['dau'] = index
                if raw != 1:
                    inode_structure[last_index]['sib'] = index

                offset = traverse_folder(item_path, index, offset)
                last_index = index

            elif os.path.isfile(item_path):
                inode = get_inode(item_path)
                inode['offset'] = offset
                inode['size'] = os.path.getsize(item_path)
                add_inode(inode)
                index = inode['index']
                
                if raw == 1 and index != 0:
                    inode_structure[index-1]['dau'] = index
                if raw != 1:
                    inode_structure[last_index]['sib'] = index
                last_index = index
                pending = write_file_to_rtlfsbin(item_path, bin_file_path)
                offset += inode['size'] + pending

        return offset

    inode_structure = []
    add_root()
    traverse_folder(path, -1, header_size)
    return inode_structure


def fill_header_partition(inode_structure, file_path):
    # 每个 finode 结构的大小
    finode_size = 256

    # 打开文件以进行写入
    with open(file_path, 'r+b') as file:
        # 定位到头部区域的起始位置
        file.seek(0)

        # 遍历 inode_structure
        for inode in inode_structure:
            # 计算当前 inode 的偏移量（相对于头部区域）
            inode_offset = inode['index'] * finode_size

            # 定位到当前 inode 的偏移量
            file.seek(inode_offset)

            # 将 inode 的数据填充到文件的相应位置
            file.write(inode['offset'].to_bytes(4, 'little'))  # 写入 offset
            file.write(inode['size'].to_bytes(4, 'little'))  # 写入 size
            file.write(inode['dau'].to_bytes(4, 'little'))  # 写入 dau
            file.write(inode['sib'].to_bytes(4, 'little'))  # 写入 sib
            file.write(inode['name'].encode('utf-8'))  # 写入 name

    print("数据填充完成。")

# 主函数
def main():
    global header_size
    global bin_file_path
    
    create_empty_bin_file(bin_file_path, header_size)

    current_index = 0
    current_dir = './rtlfs_file/'  # 当前目录

    inode_structure = build_inode_structure(current_dir)
    print("{:<10} {:<10} {:<10} {:<10} {:<10} {:<10}".format('index:', 'offset:', 'size:', 'dau:', 'sib:', 'name:'))
    for inode in inode_structure:
        print("{:<10} {:<10X} {:<10X} {:<10} {:<10} {:<10}".format(inode['index'], inode['offset'], inode['size'], inode['dau'], inode['sib'], inode['name']))
        inode = create_empty_inode(current_index)
    
    fill_header_partition(inode_structure, bin_file_path)


if __name__ == '__main__':
    main()
