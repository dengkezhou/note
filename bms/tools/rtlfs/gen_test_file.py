#!/usr/bin/env python3
import sys

def fill_file(file_name, file_size, fill_value):
    # 将文件大小转换为字节数
    file_size_bytes = file_size

    # 创建一个字节数组，用指定的填充值填充
    fill_data = bytes([fill_value]) * file_size_bytes

    # 将填充数据写入文件
    with open(file_name, 'wb') as file:
        file.write(fill_data)

    print(f"文件 '{file_name}' 填充完成。")

# 检查是否提供了足够的参数
if len(sys.argv) < 4:
    print("请提供文件名、文件大小（Byte）和填充值作为参数。")
else:
    # 获取命令行参数
    file_name = sys.argv[1]
    file_size = int(sys.argv[2])
    fill_value = int(sys.argv[3])

    # 调用填充文件函数
    fill_file(file_name, file_size, fill_value)
