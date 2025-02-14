#!/usr/bin/env python3
import os
import hashlib
import random
import shutil

KB = 1024 ** 1
MB = 1024 ** 2

def generate_test_files(sizes, base_path="fatfs_tests"):

    try:
        shutil.rmtree(base_path)
        print(f"Removed existing '{base_path}' directory")
    except FileNotFoundError:
        pass

    os.makedirs(base_path, exist_ok=True)

    for i, size in enumerate(sizes):
        file_path = os.path.join(base_path, f"test_file_{i}.bin")
        with open(file_path, "wb") as f:
            random_data = os.urandom(size)
            f.write(random_data)

            sha256_hash = hashlib.sha256(random_data).digest() # Binary hash
            f.write(sha256_hash)

def random_size(start=512, total_size=200 * MB):
    if not total_size:
        return [
            512,
            2 * KB,
            32 * KB,
            128 * KB,
            1 * MB,
            4 * MB,
            32 * MB,
            64 * MB,
            372,
            2317,
            5432,
            12345,
            123456,
            1234567,
            98765432,
        ]

    sizes = []
    while total_size > start:
        mu = (start + total_size) / 2
        sigma = (total_size - start) / 8
        n = int(random.gauss(mu, sigma))
        total_size -= n
        sizes.append(n)
    return sizes

if __name__ == "__main__":
    file_sizes = random_size(total_size=200*MB)
    generate_test_files(file_sizes)

    print(f"Test {len(file_sizes)} files generated in '{os.path.abspath('fatfs_tests')}'")

