import sys
import struct

if len(sys.argv) != 2:
    print("Usage: python script.py input.bin")
    exit()

input_file = sys.argv[1]
with open(input_file, 'rb') as f:
    data = f.read()

array_length = len(data)

array_data = struct.unpack(f'{array_length}B', data)

output_str = f"unsigned char bms_image_arr[BMS_IMAGE_LENGTH] = {{\n    "
for i, val in enumerate(array_data):
    if i > 0:
        output_str += ", "
    if (i + 1) % 16 == 0:
        output_str += "\n    "
    output_str += f"0x{val:02X}"
output_str += "\n};\n"

macro_def = f"#define BMS_IMAGE_LENGTH {array_length}\n"
output_str = macro_def + output_str

output_file = 'image.c'
with open(output_file, 'w') as f:
    f.write(output_str)

print(f'Array length: {array_length}')

