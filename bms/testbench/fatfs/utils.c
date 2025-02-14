#include <common.h>
#include <command.h>
#include <testbench.h>
#include <getopt.h>
#include <ff.h>
#include <ffconf.h>
#include <malloc.h>

#include "utils.h"

struct hash_context {
    void* context;
};

static int hash_init(struct hash_context *ctx)
{
    pufs_status_t check;
    ctx->context = pufs_hash_ctx_new();

    check = pufs_hash_init(ctx->context, SHA_256);
    if (check != SUCCESS) {
        printf("Failed to initialize hash context, check = %d\n", check);
        return -1;
    }
    return 0;
}

static int hash_update(struct hash_context *ctx, const unsigned char* data, size_t len)
{
    return pufs_hash_update(ctx->context, data, len) == SUCCESS ? 0 : -1;
}

static int hash_final(struct hash_context *ctx, unsigned char* output)
{
    pufs_dgst_st md;
    pufs_status_t check = pufs_hash_final(ctx->context, &md);
    memcpy(output, md.dgst, HASH_SIZE);
    return check == SUCCESS ? 0 : -1;
}

static void hash_free(struct hash_context *ctx)
{
    pufs_hash_ctx_free(ctx->context);
}

#define BUFFER_SIZE 8192

int sha256_file(const char *path, unsigned char *output, size_t start, size_t end)
{
    FRESULT fr;
    FIL file;
    struct hash_context hash_ctx;
    unsigned char computed_hash[HASH_SIZE] = {0};
    FSIZE_t file_size, bytes_to_hash;
    UINT br;
    int ret = 0;

    void *read_buffer = malloc(BUFFER_SIZE);
    if (!read_buffer) {
        printf("Failed to allocate read buffer\n");
        return -1;
    }

    fr = f_open(&file, path, FA_READ);
    if (fr != FR_OK) {
        printf("Failed to open file: %s, fr = %d\n", path, fr);
        return -1;
    }

    file_size = f_size(&file);

    if (hash_init(&hash_ctx) < 0) {
        f_close(&file);
        return -1;
    }

    FSIZE_t bytes_read = 0;
    bytes_to_hash = file_size - end;
    while (bytes_read < bytes_to_hash) {
        UINT to_read = (bytes_to_hash - bytes_read > BUFFER_SIZE) ?
                        BUFFER_SIZE :
                        (UINT)(bytes_to_hash - bytes_read);
        fr = f_read(&file, read_buffer, to_read, &br);
        if (fr != FR_OK || br == 0) break;

        if (hash_update(&hash_ctx, read_buffer, br) < 0) {
            printf("Failed to update hash\n");
            ret = -1;
            break;
        }
        bytes_read += br;
    }

    if (hash_final(&hash_ctx, computed_hash) < 0) {
        printf("Failed to finalize hash\n");
        ret = -1;
    }

    memcpy(output, computed_hash, HASH_SIZE);

    f_close(&file);
    hash_free(&hash_ctx);

    return ret;
}

int sha256_mem(const void *data, size_t len, unsigned char *output)
{
    struct hash_context hash_ctx;
    unsigned char computed_hash[HASH_SIZE] = {0};
    int ret = 0;

    if (hash_init(&hash_ctx) < 0) {
        return -1;
    }

    if (hash_update(&hash_ctx, data, len) < 0) {
        printf("Failed to update hash\n");
        ret = -1;
    }

    if (hash_final(&hash_ctx, computed_hash) < 0) {
        printf("Failed to finalize hash\n");
        ret = -1;
    }

    memcpy(output, computed_hash, HASH_SIZE);
    hash_free(&hash_ctx);

    return ret;
}

int load_file(const char *path, void *dst)
{
    FRESULT fr;
    FIL file;
    FSIZE_t file_size;
    UINT br;

    if (!path || !dst) {
        printf("Invalid arguments\n");
        return -1;
    }

    printf("Loading file %s to %p\n", path, dst);

    fr = f_open(&file, path, FA_READ);
    if (fr != FR_OK) {
        printf("Failed to open file: %s, fr = %d\n", path, fr);
        return -1;
    }

    file_size = f_size(&file);
    fr = f_read(&file, dst, file_size, &br);
    if (fr != FR_OK || br != file_size) {
        printf("Failed to read file: %s, fr = %d, br = %d\n", path, fr, br);
        f_close(&file);
        return -1;
    }

    f_close(&file);
    return 0;
}

TESTBENCH_INIT_HELPER(load_file)
{
    int c;
    char *file = NULL;
    unsigned long addr = 0;
    bool auto_alloc = false;
    char *help_message = "Usage: load_file [OPTIONS]\n"
                         "Load file to memory\n"
                         "\n"
                         "Options:\n"
                         "  -a, --auto-alloc\tAuto allocate memory\n"
                         "  -f, --file\t\tFile path\n"
                         "  -m, --addr\t\tMemory address\n"
                         "  -h, --help\t\tShow this message\n";

    while((c = getopt(argc, argv, "af:hm:")) != -1) {
    switch (c) {
    case 'a':
        auto_alloc = true;
        (void)auto_alloc;
        break;
    case 'f':
        file = optarg;
        break;
    case 'm':
        addr = simple_strtoul(optarg, NULL, 0);
        break;
    case 'h':
    default:
        puts(help_message);
        goto exit;
    }
    }

    if (load_file(file, (void *)addr) < 0) {
        printf("Failed to load file: %s\n", file);
        goto exit;
    } else {
        printf("Loaded file %s to memory at %p\n", file, (void *)addr);
    }

exit:
    optind = 1;
    return 0;
}

TESTBENCH_INIT_HELPER(sha256_file)
{
    int c;
    char *file = NULL;
    unsigned char hash[HASH_SIZE] = {0};
    size_t cut_end = 0;
    char *help_message = "Usage: sha256_file [OPTIONS]\n"
                         "Compute SHA256 hash of file\n"
                         "\n"
                         "Options:\n"
                         "  -f, --file\t\tFile path\n"
                         "  -e, --cut-end\t\tCut end of file\n"
                         "  -h, --help\t\tShow this message\n";

    while((c = getopt(argc, argv, "e:f:h")) != -1) {
    switch (c) {
    case 'e':
        cut_end = simple_strtoul(optarg, NULL, 0);
        break;
    case 'f':
        file = optarg;
        break;
    case 'h':
    default:
        puts(help_message);
        goto exit;
    }
    }

    sha256_file(file, hash, 0, cut_end);

    printf("SHA256 hash of file %s:\n", file);
    print_buffer(0, hash, 1, 32, 32);

exit:
    optind = 1;
    return 0;
}

TESTBENCH_INIT_HELPER(sha256_mem)
{
    int c;
    unsigned long addr = 0;
    size_t len = 0;
    unsigned char hash[HASH_SIZE] = {0};
    char *help_message = "Usage: sha256_mem [OPTIONS]\n"
                         "Compute SHA256 hash of memory\n"
                         "\n"
                         "Options:\n"
                         "  -m, --addr\t\tMemory address\n"
                         "  -l, --len\t\tMemory length\n"
                         "  -h, --help\t\tShow this message\n";

    while((c = getopt(argc, argv, "l:m:h")) != -1) {
    switch (c) {
    case 'l':
        len = simple_strtoul(optarg, NULL, 0);
        break;
    case 'm':
        addr = simple_strtoul(optarg, NULL, 0);
        break;
    case 'h':
    default:
        puts(help_message);
        goto exit;
    }
    }

    sha256_mem((void *)addr, len, hash);

    printf("SHA256 hash of memory at %p:\n", (void *)addr);
    print_buffer(0, hash, 1, 32, 32);

exit:
    optind = 1;
    return 0;
}