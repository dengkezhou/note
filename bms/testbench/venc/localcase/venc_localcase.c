
#include <command.h>
#include <testbench.h>
#include <semihost.h>
#include <getopt.h>
#include <irq.h>
#include <cache.h>

#include <i2c.h>
#include <hwmon.h>

#include "venc_localcase.h"

struct venc_localcase g_venc_case[] = 
{
    {"1152", venc_case_1152_frame, CASE_1152_PIC_SIZE, CASE_1152_PIC_OUTPUT, CASE_1152_PIC_COUNT },
    {"1155", venc_case_1155_frame, CASE_1155_PIC_SIZE, CASE_1155_PIC_OUTPUT, CASE_1155_PIC_COUNT },
    {"1200", venc_case_1200_frame, CASE_1200_PIC_SIZE, CASE_1200_PIC_OUTPUT, CASE_1200_PIC_COUNT },
    {"1522", venc_case_1522_frame, CASE_1522_PIC_SIZE, CASE_1522_PIC_OUTPUT, CASE_1522_PIC_COUNT },
    {"1526", venc_case_1526_frame, CASE_1526_PIC_SIZE, CASE_1526_PIC_OUTPUT, CASE_1526_PIC_COUNT },
    {"1740", venc_case_1740_frame, CASE_1740_PIC_SIZE, CASE_1740_PIC_OUTPUT, CASE_1740_PIC_COUNT },
    {"1741", venc_case_1741_frame, CASE_1741_PIC_SIZE, CASE_1741_PIC_OUTPUT, CASE_1741_PIC_COUNT },
    {"1751", venc_case_1751_frame, CASE_1751_PIC_SIZE, CASE_1751_PIC_OUTPUT, CASE_1751_PIC_COUNT },
    {"1757", venc_case_1757_frame, CASE_1757_PIC_SIZE, CASE_1757_PIC_OUTPUT, CASE_1757_PIC_COUNT },
    {"1763", venc_case_1763_frame, CASE_1763_PIC_SIZE, CASE_1763_PIC_OUTPUT, CASE_1763_PIC_COUNT },
    {"1768", venc_case_1768_frame, CASE_1768_PIC_SIZE, CASE_1768_PIC_OUTPUT, CASE_1768_PIC_COUNT },
    {"1773", venc_case_1773_frame, CASE_1773_PIC_SIZE, CASE_1773_PIC_OUTPUT, CASE_1773_PIC_COUNT },
    {"1778", venc_case_1778_frame, CASE_1778_PIC_SIZE, CASE_1778_PIC_OUTPUT, CASE_1778_PIC_COUNT },
    {"1786", venc_case_1786_frame, CASE_1786_PIC_SIZE, CASE_1786_PIC_OUTPUT, CASE_1786_PIC_COUNT },
    {"1795", venc_case_1795_frame, CASE_1795_PIC_SIZE, CASE_1795_PIC_OUTPUT, CASE_1795_PIC_COUNT },
    {"1811", venc_case_1811_frame, CASE_1811_PIC_SIZE, CASE_1811_PIC_OUTPUT, CASE_1811_PIC_COUNT },
    {"1905", venc_case_1905_frame, CASE_1905_PIC_SIZE, CASE_1905_PIC_OUTPUT, CASE_1905_PIC_COUNT },
    {"1912", venc_case_1912_frame, CASE_1912_PIC_SIZE, CASE_1912_PIC_OUTPUT, CASE_1912_PIC_COUNT },
    {"1913", venc_case_1913_frame, CASE_1913_PIC_SIZE, CASE_1913_PIC_OUTPUT, CASE_1913_PIC_COUNT },
    {"1960", venc_case_1960_frame, CASE_1960_PIC_SIZE, CASE_1960_PIC_OUTPUT, CASE_1960_PIC_COUNT },
    {"1961", venc_case_1961_frame, CASE_1961_PIC_SIZE, CASE_1961_PIC_OUTPUT, CASE_1961_PIC_COUNT },
    {"1979", venc_case_1979_frame, CASE_1979_PIC_SIZE, CASE_1979_PIC_OUTPUT, CASE_1979_PIC_COUNT },
    {"2007", venc_case_2007_frame, CASE_2007_PIC_SIZE, CASE_2007_PIC_OUTPUT, CASE_2007_PIC_COUNT },
    {"2042", venc_case_2042_frame, CASE_2042_PIC_SIZE, CASE_2042_PIC_OUTPUT, CASE_2042_PIC_COUNT },
    {"2200", venc_case_2200_frame, CASE_2200_PIC_SIZE, CASE_2200_PIC_OUTPUT, CASE_2200_PIC_COUNT },
    {"1525", venc_case_1525_frame, CASE_1525_PIC_SIZE, CASE_1525_PIC_OUTPUT, CASE_1525_PIC_COUNT },
    {"1975", venc_case_1975_frame, CASE_1975_PIC_SIZE, CASE_1975_PIC_OUTPUT, CASE_1975_PIC_COUNT }, 
    {"1976", venc_case_1976_frame, CASE_1976_PIC_SIZE, CASE_1976_PIC_OUTPUT, CASE_1976_PIC_COUNT },

    {"2300", venc_case_2300_frame, 1, CASE_2200_PIC_OUTPUT, 1 },
    {"2400", venc_case_2400_frame, 1, CASE_2200_PIC_OUTPUT, 1 },
    {"3000", venc_case_3000_frame, 1, CASE_2200_PIC_OUTPUT, 1 },
    
};

struct venc_localcase *g_venc_cur_case = g_venc_case;
struct venc_file_all g_venc_file = {0};

#define VENC_DEV_NUM 2

unsigned long long g_total_size = 0;
unsigned long g_time_begin[VENC_DEV_NUM] = { 0 };
unsigned long g_time[VENC_DEV_NUM] = { 0 };

struct venc_dev_id g_venc_dev_id[VENC_DEV_NUM] = {
    {0, ITCS_C_VENC0_BASE, 0xc9f00000},
    {1, ITCS_C_VENC1_BASE, 0xc9f00400}
};
unsigned long g_venc_addr = ITCS_C_VENC0_BASE;

void venc_write_reg(unsigned int reg, int value)
{
    static int reg_2c_value = 0;
    struct venc_file_all *venc_file = &g_venc_file;
    
    switch (reg)
    {
    case 0x2c :
        reg_2c_value = value;
        value = venc_file->input_data_str.reg_addr;
        break;

    case 0x30 :
    case 0x34 :
        value = venc_file->input_data_str.reg_addr + value - reg_2c_value;
        break;

    case 0x9c :
        if(venc_file->input_data_stab.reg_addr)
            value = venc_file->input_data_stab.reg_addr;
        break;

    case 0xcc:
        if(venc_file->input_data_ctable.reg_addr)
            value = venc_file->input_data_ctable.reg_addr;

        break;
    
    case 0x38:

#ifdef VENC_JOINT_TEST
        if(g_venc_addr == ITCS_C_VENC1_BASE)
            g_time_begin[1] = get_timer_us(0);
        else
            g_time_begin[0] = get_timer_us(0);
#else
        g_time_begin[0] = get_timer_us(0);
#endif
        break;

#ifdef VENC_JOINT_TEST
    case 0x014 :
    case 0x018 :
    case 0x01c :
    case 0x020 :
    case 0x024 :
    case 0x028 :
    case 0x0d0 :
    case 0x39c :
    case 0x070 :
    case 0x074 :
            if(g_venc_addr == ITCS_C_VENC0_BASE)
                value += VENC0_EX_OUTPUT_OFFSET;

            if(g_venc_addr == ITCS_C_VENC1_BASE)
                value += VENC1_EX_OUTPUT_OFFSET;
        break;
#endif

    default:
        break;
    }

    writel(value, g_venc_addr + reg);
    //printf("MA_OUTW(ENCODER_BASE+0X%08x,0X%08x);\n",reg, value);
}

int load_file(const char *path, void *dst);
int venc_load_total_file(char * case_name)
{
#if VENC_DATA_FROM == VENC_READ_DATA_FROM_RTLFS
    int ret;
    char name[128] = {0};

    sprintf(name, "venc/rtlfs_%s.bin", case_name);

    ret = load_file(name, (void *)VENC_RTLFS_ADDR);
    if (ret)
    {
        printf("venc load %s failed, ret = %d\n", name, ret);
        return -1;
    }

    printf("venc load %s, addr = %lx\n", case_name, VENC_RTLFS_ADDR);
#endif

    return 0;
}

int venc_module_enable(int id)
{
    int ret;
    char module_name[8] = {0};

    sprintf(module_name, "venc%d", id);

    /*bus6*/
    #ifndef CONFIG_COMPILE_FPGA
    int rate;
    ret = itcs_module_set_clock(CPU, "bus6", "dpll", 500000000, false);
    if (ret < 0)
        return ret;
    
    rate = itcs_module_get_clock(CPU, "bus6");
    printf("bus6 clk rate = %d\n",rate);
    #endif

    /*module enable*/
    ret = itcs_module_enable(CPU, module_name);
    if (ret < 0)
        return ret; 

#ifdef CONFIG_TB_RUN_DDR1
    /*set venc high addr*/
    writel(0x55, g_venc_dev_id[id].sysm_addr + 0x20);
    printf("venc %d set high add\n", id);
#endif

    /*share memory*/
    writel(1, g_venc_dev_id[id].sysm_addr + 0x24); 

    g_venc_addr =  g_venc_dev_id[id].base_addr;

    return 0;
}

int venc_read_reg(unsigned int reg)
{
   return readl(g_venc_addr + reg);
}

int venc_wait_intr(int delay, int loop_count)
{
    volatile int value;

    #ifdef CONFIG_COMPILE_RTL 
    delay = 1;
    loop_count = 0xfffffff;
    #endif

    #ifdef DEBUG_VENC_SPEED_TEST
    delay = 1;
    loop_count = 0xfffffff;
    #endif

    while (1)
    {
        value = venc_read_reg(0x4);
        if (value == 0x5)
        {
            g_time[0] += get_timer_us(g_time_begin[0]);
            return 0;
        }

        if (loop_count <= 0)
        {
            return -1;
        }

        //udelay(delay);
        //loop_count --;
    }
}

#ifndef DEBUG_VENC_SPEED_TEST
void venc_print_buf(char *buf, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i % 8 == 0)
        {
            VENC_NORMAL_LOG("\n");
        }
        VENC_NORMAL_LOG("%02x  ", buf[i]);
    }
    VENC_NORMAL_LOG("\n");
}
#endif

void itcs_print_clk()
{
    unsigned long rate;
    int i = 0;
    char* clk_name[] = {
        "apll", "bpll", "cpll",
        "dpll", "epll", "vpll",
        NULL
    };

    char* modlue_clk_name[] = {
        "cpu", "cpub", "apb",
        "bus1", "bus2", "bus3",
        "bus4", "bus5", "bus6",
        NULL
    };


    itcs_pll_set_clock(CPU, "apll", 1584000000, false);
    itcs_pll_set_clock(CPU, "bpll", 2376000000, false);
    itcs_pll_set_clock(CPU, "cpll", 2016000000, false);
    itcs_pll_set_clock(CPU, "dpll", 1500000000, false);
    itcs_pll_set_clock(CPU, "epll", 2424000000, true);
    //itcs_pll_set_clock(CPU, "vpll", 2112000000, false);
#if 1 
    itcs_module_set_clock(CPU, "cpu", "apll", 1584000000, false);
    itcs_module_set_clock(CPU, "cpub", "apll", 396000000, false);
    itcs_module_set_clock(CPU, "apb", "apll", 99000000, false);

    itcs_module_set_clock(CPU, "bus1", "dpll", 375000000, false);
    itcs_module_set_clock(CPU, "bus2", "dpll", 375000000, false);
    itcs_module_set_clock(CPU, "bus3", "epll", 500000000, false);
    itcs_module_set_clock(CPU, "bus4", "epll", 606000000, false);
    itcs_module_set_clock(CPU, "bus5", "epll", 606000000, false);
    itcs_module_set_clock(CPU, "bus6", "epll", 500000000, false);
#endif
    while(clk_name[i] != NULL)
    {
        rate = itcs_pll_get_clock(CPU, clk_name[i]);
        printf("clk %s rate = %ld\n", clk_name[i], rate);
        i++;
    }   

    i = 0;
    while(modlue_clk_name[i] != NULL)
    {
        rate = itcs_module_get_clock(CPU, modlue_clk_name[i]);
        printf("clk %s rate = %ld\n", modlue_clk_name[i], rate);
        i++;
    }       
}

void venc_test_hwmon() {
    static int init = 0;
    if (!init)
    {
        itcs_print_clk();
        init = 1;
    }

    //itcs_print_pmic_all_voltages(0);
    //itcs_print_pmic_all_voltages(1);
    itcs_hwmon_print_all_info(0);
    printf("=====================\n");
}

#if 1
void venc_test_power_consumption(int stop)
{
    int ret;
    int hwmon_id = 0;
    static struct hwmon_sub *hwmonsub = NULL;
    char *name = "VDD_SOC";


    static int loop = 0;
    static int vlt = 0;
    static int current = 0;
    static int power = 0;

    if (hwmonsub == NULL)
    {
        ret = itsc_hwmon_init(hwmon_id);
        if (ret)
            printf("hwmon init error!\n");

        hwmonsub = itcs_hwmon_get(hwmon_id, name);
        if (hwmonsub == NULL)
            printf("hwmon get error!\n");
    }

    loop++;
    vlt += itcs_hwmon_get_bus_voltage(hwmonsub);
    current += itcs_hwmon_get_current(hwmonsub);
    power += itcs_hwmon_get_power(hwmonsub);

    if(loop == 20)
        stop = 1;

    if (stop)
    {
        printf("loop: %d=====venc_test_power_consumption=====\n", loop);
        printf("Name: %s: bus_voltage = %dmV\n", hwmonsub->name, vlt / loop);
        printf("Name: %s: current = %dmA\n", hwmonsub->name, current / loop);
        printf("Name: %s: power = %duW\n", hwmonsub->name, power / loop);
        loop = 0;
        vlt = 0;
        current = 0;
        power = 0;
    }
}
#endif


void venc_wait_and_cmp(int len)
{
    
#ifdef VENC_JOINT_TEST
    return;
#endif

    int ret;
    static int frame_number = 0;
    static int total_pass = 1;
    struct venc_file_all *venc_file = &g_venc_file;

#ifndef DEBUG_VENC_SPEED_TEST
    void *golden_addr = venc_file->output_data_golden.real_addr;
    int cmp_size = venc_file->output_data_golden.file_size;

    void *output_addr = (void*)(g_venc_cur_case->pic_output + VENC_OUTPUT_OFFSET);
    if(frame_number == 5 && memcmp(g_venc_cur_case->case_name, "2042", 4) == 0)
    {
         output_addr = (void*)CASE_2042_OUTPUT5_ADDR;
    }
#endif

    itcs_hwmon_print_one_info(0, 0);

    ret =  venc_wait_intr(1000 * 100, 100);
    if (ret)
    {
        printf("wait irq = 0x5 failed\n");
        total_pass = 0;
    }
#ifndef DEBUG_VENC_SPEED_TEST
    else
    {
        VENC_NORMAL_LOG("wait irq = 0x5 success\n");
        itcs_dcache_flush();

        VENC_NORMAL_LOG("venc localcase %s, frame number = %d, size = %d ",g_venc_cur_case->case_name, frame_number, cmp_size );
        VENC_NORMAL_LOG("venc hw output size = 0x%x\n", (venc_read_reg(0x60) +7)/ 8);

        ret = memcmp(golden_addr, output_addr, cmp_size);
        if(ret == 0)
        {
            VENC_NORMAL_LOG("pass\n");
        }
        else
        {
            VENC_NORMAL_LOG("output addr = 0x%llx, failed\n", output_addr);
            venc_print_buf((char*)golden_addr, 32);
            venc_print_buf((char*)output_addr, 32);
            total_pass = 0;
        }
    }
#endif

    frame_number++;
    venc_free_file(venc_file);

    g_total_size += venc_file->input_data_str.file_size;

    if(frame_number < g_venc_cur_case->pic_count)
    {
        #ifndef VENC_JOINT_TEST
        /*next frame*/
        venc_load_file(venc_file, g_venc_cur_case->case_name, frame_number);  
        #endif

    }else{
        /*end*/
        VENC_NORMAL_LOG("venc localcase %s, frame number = %d  ",g_venc_cur_case->case_name, frame_number);
        if(total_pass)
        {
            VENC_NORMAL_LOG("total Pass\n");
        }else{
            VENC_NORMAL_LOG("total Failed\n");
        }

        frame_number = 0;
        total_pass = 1;
    }
    return;

}

int __venc_load_file(struct venc_file_once *tmp)
{
    int fd;
    fd = open(tmp->file_name, O_RDONLY);
    if (fd == -1) {
        tmp->fd = fd;
        //tmp->reg_addr = 0;
        return -1;
    }
    tmp->file_size = flen(fd);

#if VENC_DATA_FROM == VENC_READ_DATA_FROM_SD
    read(fd, tmp->real_addr, tmp->file_size);
#elif VENC_DATA_FROM == VENC_READ_DATA_FROM_RTLFS
    tmp->real_addr = (void *)faddr(fd);
#endif

    itcs_dcache_flush_range((phys_addr_t)tmp->real_addr, tmp->file_size);
    
    tmp->reg_addr = (unsigned int)(unsigned long)tmp->real_addr;

    //printf("input %s addr = %p , %x\n",tmp->file_name,  tmp->real_addr, tmp->reg_addr);
    //printf("size = %d\n", tmp->file_size);
    //venc_print_buf(tmp->real_addr, 32);
    
    tmp->fd = fd;
    return 0;
}

int venc_load_file(struct venc_file_all *venc_file, char *case_name, int frame_num)
{
    int ret;
    static int init = 0;

    if(!init)
    {
        memset (venc_file, 0, sizeof(struct venc_file_all));  /* next pic code may be use the pre ctable, so can't set 0 */
        init = 1;
        
#if VENC_DATA_FROM == VENC_READ_DATA_FROM_SD
        venc_file->input_data_str.real_addr     = (void *)VENC_INPUT_DATA;
        venc_file->input_data_ctable.real_addr  = (void *)VENC_INPUT_CTABLE;
        venc_file->input_data_stab.real_addr    = (void *)VENC_INPUT_STAB;
        venc_file->output_data_golden.real_addr = (void *)VENC_OUTPUT_GOLDEN;
#endif
    }
    
    sprintf(venc_file->input_data_str.file_name, "venc/case_%s/frame%d_input/h1_input_data.trc.bin", case_name, frame_num);
    sprintf(venc_file->input_data_ctable.file_name, "venc/case_%s/frame%d_input/h1_input_ctable_data.trc.bin", case_name, frame_num);
    sprintf(venc_file->input_data_stab.file_name, "venc/case_%s/frame%d_input/h1_input_stab_data.trc.bin", case_name, frame_num);
    sprintf(venc_file->output_data_golden.file_name, "venc/case_%s/frame%d_output/h1_output_strm.trc.bin", case_name, frame_num);


    ret = __venc_load_file(&venc_file->input_data_str);
    if(ret)
    {
        printf("read %s failed, ret = %d\n", venc_file->input_data_str, ret);
        return -1;
    }

    __venc_load_file(&venc_file->output_data_golden);
    __venc_load_file(&venc_file->input_data_ctable);
    __venc_load_file(&venc_file->input_data_stab);


    return 0;
}

 void __venc_free_file(struct venc_file_once *tmp)
{
    if(tmp->fd >= 0)
    {
        close(tmp->fd);
    }
    tmp->fd = -1;

    return;
}

void venc_free_file(struct venc_file_all *venc_file)
{
    __venc_free_file(&venc_file->input_data_str);
    __venc_free_file(&venc_file->input_data_ctable);
    __venc_free_file(&venc_file->input_data_stab);
    __venc_free_file(&venc_file->output_data_golden);

}


struct venc_localcase * venc_get_case(char *case_name)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(g_venc_case); ++i)
    {
        if (memcmp(case_name, g_venc_case[i].case_name, 4) == 0)
        {
            return g_venc_case + i;
        }
            
    }
    return NULL;
}


static unsigned long venc_set_clk_rate(unsigned long rate)
{

#ifndef CONFIG_COMPILE_FPGA
    int ret;

    itcs_pll_set_clock(CPU, "dpll", rate, false);

    ret = itcs_module_set_clock(CPU, "bus6", "dpll", rate, false);
    if (ret < 0)
        return ret;


    ret = itcs_module_set_clock(CPU, "bus6", "dpll", rate, false);
    if (ret < 0)
        return ret;

    rate = itcs_module_get_clock(CPU, "bus6");
    
#endif

    return rate;
}


void venc_test_clk_rate(int loop)
{
    unsigned long rate;
    unsigned long rate_base = 500 * 1000 * 1000;
    int step                = 50 * 1000 * 1000;

    rate = rate_base + step * loop;
    rate = venc_set_clk_rate(rate);

    printf("=========loop = %d, venc get clk = %ld\n", loop, rate);

    udelay(1000 *100);
}

/*venc case_name*/
int venc_localcase_encode(int argc, char *argv[])
{
    int ret;
    int id;
    unsigned int test_loop = 1;

    venc_test_hwmon();
    //return 0;

    //unsigned long time_begin, time;

    if (argc > 4)
    {
        printf("use venc case_name\n");
        return 0;
    }else if(argc == 4)
    {
        test_loop = atoi(argv[3]);
        printf("test_loop = 0x%d\n", test_loop);
    }

    id = atoi(argv[2]);
    printf("test id = %d\n", id);

    ret = venc_module_enable(id);
    if (ret)
    {
        printf("module enable failed, ret = %d\n", ret);
        return ret;
    }

#ifdef CONFIG_COMPILE_ASIC
    ret = venc_load_total_file(argv[1]);
    if (ret)
        return ret;
#endif

    /*encode*/
    g_venc_cur_case = venc_get_case(argv[1]);

    g_total_size = 0;
    g_time[0] = 0;
    int i = 0;
    
    if(g_venc_cur_case)
    {
        int frame_num = test_loop * g_venc_cur_case->pic_count;

        //time_begin = get_timer_us(0);
        while(test_loop--) {

            g_total_size = 0;
            g_time[0] = 0;
            frame_num = g_venc_cur_case->pic_count;
            //venc_test_clk_rate(i);
            i++;

            ret = venc_load_file(&g_venc_file, g_venc_cur_case->case_name, 0);
            if(ret)
            {
                return -1;
            }

            g_venc_cur_case->func();

            printf("time = %ld us, totol size = %lld, frame num = %d\n", g_time[0], g_total_size, frame_num);
            printf("fps = %d, bps = %d\n", (unsigned long)frame_num * 1000 * 1000  / g_time[0], 
                                        (unsigned long)g_total_size * 1000  * 1000 / g_time[0]);
        }
        //time = get_timer_us(time_begin);
        #ifndef VENC_JOINT_TEST
        //printf("time = %ld ms, totol size = %lld, frame num = %d\n", g_time[0], g_total_size, frame_num);
        //printf("fps = %d, bps = %d\n", frame_num * 1000  / g_time[0], g_total_size * 1000  / g_time[0]);
        #endif
    }
    else
    {
        printf("no such case\n");
    }

    return 0;
}

void venc_localcase_init(void)
{
    register_testbench("venc", venc_localcase_encode, NULL);
}

testbench_init(venc_localcase_init);





