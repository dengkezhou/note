#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>
#include <ff.h>
#include <ffconf.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

static FRESULT process_files(const TCHAR *path) {
    FRESULT fr;
    DIR dir;
    FILINFO fno;
    FIL file;
    UINT br;
    unsigned char file_hash[HASH_SIZE];
    unsigned char computed_hash[HASH_SIZE];
    TCHAR full_path[FF_MAX_LFN + 1];
    FSIZE_t file_size;
    bool hash_mismatch = false;
    int total_files = 0;

    fr = f_opendir(&dir, path);
    if (fr != FR_OK) {
        printf("Failed to open directory: %s, fr = %d\n", path, fr);
        return fr;
    }

    for (;;) {
        fr = f_readdir(&dir, &fno);
        if (fr != FR_OK || fno.fname[0] == 0) break;

        if (fno.fattrib & AM_DIR) continue;

        printf("Processing file: %s, ", fno.fname);

        snprintf(full_path, sizeof(full_path), "%s/%s", path, fno.fname);
        fr = f_open(&file, full_path, FA_READ);
        if (fr != FR_OK) {
            printf("Failed to open file: %s, fr = %d\n", full_path, fr);
            continue;
        }

        file_size = f_size(&file);
        if (file_size <= HASH_SIZE) {
            printf("File too small: %s\n", fno.fname);
            f_close(&file);
            continue;
        }
        printf("size: %lu\n", file_size);

        memset(computed_hash, 0, sizeof(computed_hash));
        memset(file_hash, 0, sizeof(file_hash));

        f_lseek(&file, file_size - HASH_SIZE);
        f_read(&file, file_hash, HASH_SIZE, &br);
        if (br != HASH_SIZE) {
            printf("Failed to read hash from file\n");
            f_close(&file);
            continue;
        }
        f_close(&file);

        if (sha256_file(full_path, computed_hash, 0, HASH_SIZE) < 0) {
            printf("Failed to compute hash for file: %s\n", fno.fname);
            f_close(&file);
            continue;
        }

        if (memcmp(computed_hash, file_hash, HASH_SIZE)) {
            printf("=====================>\n");
            printf("Hash mismatch for file: %s\n", fno.fname);
            puts("Read hash:\n  ");
            print_buffer(0, file_hash, 1, 32, 32);
            puts("Computed hash:\n  ");
            print_buffer(0, computed_hash, 1, 32, 32);
            printf("<=====================\n");
            hash_mismatch = true;
        }

        total_files++;
    }

    f_closedir(&dir);
    printf("Total files processed: %d\n", total_files);
    if (hash_mismatch) {
        printf("One or more files have hash mismatch\n");
        return FR_DISK_ERR;
    }
    return FR_OK;
}

TESTBENCH_INIT_HELPER(fatfs)
{
    int c;
    FRESULT fr;
    int run_times = 1, pass_times = 0, fail_times = 0;
    char *help_message = "Usage: fatfs [OPTIONS]\n"
                         "Run Fatfs test\n"
                         "\n"
                         "Options:\n"
                         "  -c, --count\tNumber of times to run the test\n"
                         "  -o, --once\tRun the test once\n"
                         "  -h, --help\tShow this message\n";

    while((c = getopt(argc, argv, "c:oh")) != -1) {
        switch (c) {
        case 'c':
            run_times = simple_strtoul(optarg, NULL, 0);
            break;
        case 'h':
            puts(help_message);
            goto exit;
        case 'o':
        default:
            break;
        }
    }

    printf("Running Fatfs test %d times\n", run_times);

    while (run_times) {
        printf("=>Remain %d rounds\n", run_times);
        fr = process_files("/fatfs_tests");
        if (fr == FR_OK) {
            pass_times++;
        } else {
            fail_times++;
        }
        run_times--;
    }

    printf("Fatfs test %d Pass, %d Failed\n", pass_times, fail_times);
exit:
    optind = 1;
    return 0;
}

