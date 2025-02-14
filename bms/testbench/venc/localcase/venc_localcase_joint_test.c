#include <string.h>
#include <stdio.h>
#include <testbench.h>
#include <cache.h>
#include "venc_localcase.h"
#include "venc_localcase_joint_test.h"

void venc_case_1975_frame0();
void venc_case_1975_frame1();
void venc_case_1975_frame2();
void venc_case_1975_frame3();
void venc_case_1975_frame4();
void venc_case_2200_frame0();

#define VENC_JOINT_TEST_CASE       "1975"
#define VENC_JOINT_TEST_FRAME_NUM  5
#define VENC_JOINT_TEST_FRAME_NUM_2200 1


#define VENC0_JOINT_READY 0x1
#define VENC1_JOINT_READY 0x2

struct venc_joint_test_fd
{
    struct venc_file_all vecn_file[VENC_JOINT_TEST_FRAME_NUM];
};

extern struct venc_file_all g_venc_file;
extern struct venc_localcase * g_venc_cur_case;
extern struct venc_dev_id g_venc_dev_id[2];
extern unsigned long g_venc_addr;

extern unsigned long g_time_begin[];
extern unsigned long g_time[];

static struct  venc_joint_test_fd g_venc_joint_test_fd = {0};


TEST_CASE_FUNC g_venc_joint_test_func_1975[VENC_JOINT_TEST_FRAME_NUM] = {
    venc_case_1975_frame0, venc_case_1975_frame1,
    venc_case_1975_frame2, venc_case_1975_frame3, venc_case_1975_frame4
};

TEST_CASE_FUNC g_venc_joint_test_func_2200[VENC_JOINT_TEST_FRAME_NUM] = {
    venc_case_2200_frame0, venc_case_2200_frame0,
    venc_case_2200_frame0, venc_case_2200_frame0, venc_case_2200_frame0
};

TEST_CASE_FUNC *g_venc_joint_test_func = g_venc_joint_test_func_1975;


void vnec_joint_test_cmp(int id, int count)
{
    int ret;
    struct venc_file_all *venc_file;
    unsigned long output_offset;

    if (id == 0)
        output_offset = VENC_OUTPUT_OFFSET + VENC0_EX_OUTPUT_OFFSET;
    else
        output_offset = VENC_OUTPUT_OFFSET + VENC1_EX_OUTPUT_OFFSET;

    printf("===output offset = %lx\n", output_offset);

    count %= VENC_JOINT_TEST_FRAME_NUM;
    venc_file = &g_venc_joint_test_fd.vecn_file[count];

    void *golden_addr = venc_file->output_data_golden.real_addr;
    int cmp_size = venc_file->output_data_golden.file_size;

    void *output_addr = (void*)(g_venc_cur_case->pic_output + output_offset);

    printf("%d frame number = %d, size = %d ",id, count, cmp_size );

    itcs_dcache_flush_range((unsigned long)output_addr, (cmp_size +63)&(~63) );

    ret = memcmp(golden_addr, output_addr, cmp_size);
    if(ret == 0)
    {
        printf("pass\n");
    }
    else
    {
        printf("output addr = 0x%llx, failed\n", output_addr);
    }
}

int venc_joint_test_main(int argc, char *argv[])
{
    volatile int ret;
    int i, id, status;
    int loop_1, loop;
    static struct venc_join_test_param param;

    if(argc >= 2)
        memcpy(param.case_name, argv[1], sizeof(param.case_name));
    else
        memcpy(param.case_name, VENC_JOINT_TEST_CASE, sizeof(param.case_name));

    if(argc >= 3)
        loop = atoi(argv[2]);
    else
        loop = 1;

#ifdef CONFIG_COMPILE_ASIC
    ret = venc_load_total_file(param.case_name);
    if (ret)
        return ret;
#endif


    for(i = 0; i < 2; ++i)
    {
        param.id = i;
        ret = venc_joint_test_init(&param);
        if (ret)
        {
            printf("venc_joint_test_init failed\n");
            return -1;
        }
    }

    for (i = 0; i < loop; ++i)
    {
        void venc_test_clk_rate(int loop);
        venc_test_clk_rate(i);

        g_time[0] = 0;
        g_time[1] = 0;
        status = 0;

        venc_joint_test_start(0, 0);
        venc_joint_test_start(1, 0);
        for(loop_1 = 0; loop_1 < VENC_JOINT_TEST_FRAME_NUM;)
        {
            id = 0;
            ret = venc_joint_test_get_status(id);
            if (ret == 1 && (status & VENC0_JOINT_READY) == 0)
            {
                g_time[id] += get_timer_us(g_time_begin[id]);
                status |= VENC0_JOINT_READY;
            }

            id = 1;
            ret = venc_joint_test_get_status(id);
            if (ret == 1 && (status & VENC1_JOINT_READY) == 0)
            {
                g_time[id] += get_timer_us(g_time_begin[id]);
                status |= VENC1_JOINT_READY;
            }

            if (status == (VENC0_JOINT_READY | VENC1_JOINT_READY))
            {
                status = 0;
                vnec_joint_test_cmp(0, loop_1);
                vnec_joint_test_cmp(1, loop_1);
                loop_1 ++;
                venc_joint_test_start(0, loop_1);
                venc_joint_test_start(1, loop_1);
            }
        }

        for(id = 0; id < 2; ++id)
             printf("venc %d, time = %d ms, frame = %d, fps = %d\n",
                id, g_time[id], VENC_JOINT_TEST_FRAME_NUM, VENC_JOINT_TEST_FRAME_NUM * 1000 *1000 / g_time[id]);
    }
    return 0;
}

int venc_joint_test_init(void * param)
{
    int i, ret, frame_num_cnt;
    static int init = 0;
    struct venc_join_test_param *context ;
    struct venc_file_all file_tmp;
    
    context = (struct venc_join_test_param *)param;

    ret = venc_module_enable(context->id);
    if (ret)
    {
        printf("module enable failed, ret = %d\n", ret);
        return ret;
    }

    if(init)
    {
        return 0;
    }

    g_venc_cur_case = venc_get_case(context->case_name);
    if (g_venc_cur_case == NULL)
    {
        printf("venc test, no such case\n");
        return -1;
    }

    if (memcmp(context->case_name, "2200", 5) == 0)
    {
        g_venc_joint_test_func = g_venc_joint_test_func_2200;
        frame_num_cnt = VENC_JOINT_TEST_FRAME_NUM_2200;
    }else
        frame_num_cnt = VENC_JOINT_TEST_FRAME_NUM;

    memset(&g_venc_joint_test_fd, 0, sizeof(struct venc_joint_test_fd));
    memset(&file_tmp, 0, sizeof(struct venc_file_all));

    for(i = 0; i < VENC_JOINT_TEST_FRAME_NUM; ++i)
    {
        /*file_tmp 不能重新置0，对于ctabl、stab文件，下一帧会使用上一帧的数据*/
        ret = venc_load_file(&file_tmp, context->case_name, i % frame_num_cnt); 
        if (ret)
        {
            return ret;
        }
        venc_free_file(&file_tmp);

        memcpy (&g_venc_joint_test_fd.vecn_file[i], &file_tmp, sizeof(struct venc_file_all ));
    }

    init = 1;
    return 0;
}

int venc_joint_test_start(int id, int count)
{
    int frame_count;
    

    g_venc_addr = g_venc_dev_id[id].base_addr;
    
    frame_count = count % VENC_JOINT_TEST_FRAME_NUM;

    //printf("venc_joint_test_start id = %d, conut = %d\n", id, frame_count);

    memcpy (&g_venc_file, &g_venc_joint_test_fd.vecn_file[frame_count], sizeof(struct venc_file_all ));
    
    g_venc_joint_test_func[frame_count]();

    return 0;
    
}



int venc_joint_test_get_status(int id)
{
    int value;

    g_venc_addr = g_venc_dev_id[id].base_addr;
    value = venc_read_reg(0x4);
    if (value == 0x5)
    {
        return 1;
    }

    return 0;
}


void venc_joint_test_init_reg(void)
{
    register_testbench("venc_joint", venc_joint_test_main, NULL);
}

testbench_init(venc_joint_test_init_reg);