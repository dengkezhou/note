import pandas as pd
import csv
import argparse

def get_board_values(input_file, column_name):
    # 读取 CSV 文件
    df = pd.read_csv(input_file)
    # 获取指定列的所有不同值
    unique_values = df[column_name].unique()
    # 将不同值转换为元组
    unique_tuple = tuple(unique_values)

    return unique_tuple

def main():
    # 创建解析器
    parser = argparse.ArgumentParser(description='Process some files.')

    # 添加参数
    parser.add_argument('-i', '--input', type=str, required=True, help='Input CSV file')
    parser.add_argument('-o', '--output', type=str, required=True, help='Output CSV file')
    
    # 添加可选参数
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--vdec', action='store_true', help='Use video decoder')
    group.add_argument('--venc', action='store_true', help='Use video encoder')
    group.add_argument('--cpu', action='store_true', help='Use CPU processing')
    group.add_argument('--npu', action='store_true', help='Use NPU processing')

    # 解析参数
    args = parser.parse_args()

    # 打印参数（可以根据需要进行处理）
    print(f'Input file: {args.input}')
    print(f'Output file: {args.output}')

    # 读取输入数据
    idf = pd.read_csv(args.input)

    # 创建一个新的DataFrame用于存储输出数据
    odf = pd.DataFrame()

    no_values = get_board_values(args.input, 'Board')#[1, 2, 4, 5, 7, 8, 9, 11, 12, 13]
    odf[':::NO.'] =  list(range(1, len(no_values) + 1))#no_values
    mv = 800
    core_value = 0
    board = 1

    # 遍历每一行数据，构建输出列
    for index, row in idf.iterrows():
        core_value = row['CORE']
        board = row['Board']
        module = 'CPU'

        if args.vdec:
            module = 'VDEC'
        elif args.venc:
            module = 'VENC'
        if args.cpu:
            mv = row['Voltage']
            module = 'CPU'
        elif args.npu:
            module = 'NPU'
        
        for freq in idf.columns[3:]:  # 从第四列开始是频率列
            # 构建新的列名
            new_column_name = f"{mv}:{freq}:{core_value}:{module}"
            
            # 根据输入值填充0或1
            # 确保在新列中为当前行填充值
            if module == 'CPU':
                if '1' in  str(row[freq]) :
                    odf.at[no_values.index(board), new_column_name] = 1
                else:
                    odf.at[no_values.index(board), new_column_name] = 0
            else:
                if 'X' in  str(row[freq]):
                    odf.at[no_values.index(board), new_column_name] = 0
                else:
                    odf.at[no_values.index(board), new_column_name] = 1


    # 保存为新的CSV文件
    odf.to_csv( args.output, index=False)

if __name__ == '__main__':
    main()