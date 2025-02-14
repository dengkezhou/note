#include <common.h>
#include <initcall.h>
#include <ff.h>

static FATFS fs;

int fatfs_init(void)
{
    FRESULT fr;

    fr = f_mount(&fs, "", 1);
    if (fr != FR_OK)
    {
        printf("f_mount failed, fr = %d\n", fr);
        return -fr;
    }
    return 0;
}

#ifndef CONFIG_COMPILE_ROM
void _fatfs_init(void)
{
    fatfs_init();
}
module_init(_fatfs_init);
#endif