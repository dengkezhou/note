
#include <common.h>
#include <stdio.h>
#include <command.h>
#include <testbench.h>
#include <asm/io.h>
#include <pufs_memory_map.h>
#include <pufs_rt.h>

static unsigned char le_otp_bin[1024] = {
};

TESTBENCH_INIT_HELPER(ttotp)
{
    pufs_status_t check = SUCCESS;

    puts("This command will burn the OTP with the following data:\n");
    puts("Plesae confirm the OTP data is correct before proceeding.\n");
    print_buffer(0, le_otp_bin, 1, sizeof(le_otp_bin), 32);

    puts("\n\nYou must type \"yes\" twice to continue.\n");

    puts("Type 'yes' to continue: ");
    char buf[4];
    if (gets_s(buf, sizeof(buf)) == NULL || strcmp(buf, "yes") != 0)
        return 1;

    puts("Type 'yes' again to confirm: ");
    if (gets_s(buf, sizeof(buf)) == NULL || strcmp(buf, "yes") != 0)
        return 1;

    puts("Burning OTP...\n");
    pufs_module_init(PUFIOT_ADDR_START, PUFIOT_MAP_SIZE);

    if ((check = pufs_program_otp((const uint8_t*)le_otp_bin, sizeof(le_otp_bin), 0)) != SUCCESS)
        printf("Fail to program otp\n");

    puts("Burning OTP done\n");

    return 0;
}
