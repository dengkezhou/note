#include <common.h>
#include <command.h>
#include <testbench.h>
#include <sdmmc.h>
#include <getopt.h>

static void show_usage(void)
{
    printf("Usage: mmcburn [OPTION]...\n");
    printf("Options:\n");
    printf("  -d <devn>  Device number\n");
    printf("  -a <addr>  MMC address in bytes\n");
    printf("  -s <size>  Size\n");
    printf("  -m <buf>   Memory address\n");
    printf("  -r         Read\n");
    printf("  -w         Write\n");
}

#define MMC_CHUNK_RW
#ifdef MMC_CHUNK_RW
#define CHUNK_SIZE (32 << 10)
#endif

static int mmc_read(int devn, ulong addr, size_t size, void *buf)
{
    printf("Reading %d bytes from mmc 0x%lx to 0x%lx\n", size, addr, (ulong)buf);
#ifdef MMC_CHUNK_RW
    size_t chunk = CHUNK_SIZE;
    uint8_t *p = buf;
    uint32_t sector = addr >> 9;

    printf("Chunk size: %d\n", chunk);
    while (size) {
        if (size < chunk)
            chunk = size;
        if (itcs_sdmmc_read(devn, sector, chunk, p))
            return -1;
        p += chunk;
        sector += chunk >> 9;
        size -= chunk;
    }
    return 0;
#else
    return itcs_sdmmc_read(devn, addr, size, buf);
#endif
}

static int mmc_write(int devn, ulong addr, size_t size, void *buf)
{
    printf("Writing %d bytes to mmc 0x%lx from 0x%lx\n", size, addr, (ulong)buf);
#ifdef MMC_CHUNK_RW
    size_t chunk = CHUNK_SIZE;
    uint8_t *p = buf;
    uint32_t sector = addr >> 9;

    printf("Chunk size: %d\n", chunk);
    while (size) {
        if (size < chunk)
            chunk = size;
        if (itcs_sdmmc_write(devn, sector, chunk, p))
            return -1;
        p += chunk;
        sector += chunk >> 9;
        size -= chunk;
    }
    return 0;
#else
    return itcs_sdmmc_write(devn, addr, size, buf);
#endif
}

TESTBENCH_INIT_HELPER(mmcburn)
{
    int c;
    int devn = 1;
    uint64_t addr = 0;
    size_t size = 0;
    ulong buf = 0;
    bool read = false, write = false, check = false;

     while((c = getopt(argc, argv, "d:a:s:m:rwch")) != -1) {
        switch (c) {
        case 'd':
            devn = simple_strtoul(optarg, NULL, 10);
            itcs_sdmmc_simple_init(devn);
            break;
        case 'a':
            addr = simple_strtoul(optarg, NULL, 16);
            break;
        case 's':
            size = simple_strtoul(optarg, NULL, 16);
            break;
        case 'm':
            buf = simple_strtoul(optarg, NULL, 16);
            break;
        case 'r':
            read = true;
            break;
        case 'w':
            write = true;
            break;
        case 'h':
        default:
            show_usage();
            goto exit;
        }
     }

     if (read) {
        if (mmc_read(devn, addr, size, (void *)buf))
            printf("Read failed\n");
     } else if (write) {
         if (mmc_write(devn, addr, size, (void *)buf))
            printf("Write failed\n");
     }

exit:
  optind = 1;
  return 0;
}

