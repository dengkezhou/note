#include <common.h>
#include <cache.h>
#include <irq.h>
#include <rtlfs.h>
#include <div64.h>
#include <vdec.h>

volatile unsigned long VC9000D_BASE = 0xc6000000;
// #define VDEC_DEBUG
#define VDEC_RTL_NOCMP

#ifdef VDEC_DEBUG
#define vdec_dbg(...) printf(__VA_ARGS__)
#else
#define vdec_dbg(...)
#endif


#define MA_OUTW(a,b) writel((b), (a))
#define MA_INW(a) readl((a))

static ssize_t restore_test_file(char *file_name, void *dst);
static int dump_outdata_info(char *basedir, char *file_name, void *dst, uint32_t len);

#ifdef HWMON_TEST
extern int hwmon_main(int argc, char *argv[]);
// hwmon -m 0 -n VDD_SOC -p
static char *hwmon_argv[] = { "-m", "0", "-n", "VDD_SOC", "-p" };
static int hwmon_argc = sizeof(hwmon_argv) / sizeof(hwmon_argv[0]) + 1;
#endif

struct metadata {
    char name[64];

#define TYPE_VCMD     (1U << 1)
#define TYPE_STRM_IN  (1U << 2)
#define TYPE_STRM_OUT (1U << 3)
#define TYPE_FLUSH    (1U << 4)
    uint32_t type;
    void *addr;
    uint32_t len;
} __attribute__((__packed__));

struct outdata {
    char name[64];
    void *src;
    void *dst;
    uint32_t len;
};

#define VCMD_BUF_LEN (2560)

static uint8_t vcmd_buf[VCMD_BUF_LEN] __attribute__((aligned(128)));
volatile static uint32_t vcmd_addr_hi, vcmd_addr_lo;
static ssize_t vcmd_len;

static struct outdata outdata_info[8] = { 0 };
static int outdata_info_index = 0;

static volatile uint32_t g_perf_cycle;
static bool g_inited = false;

static int __attribute__ (( unused )) vdec_memcmp(const void *cs, const void *ct, size_t count) {
    const unsigned char *su1, *su2;
    int res = 0;

    for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
    if ((res = *su1 - *su2) != 0) {
        printf("%p=%x not equal with %p=%x\n", su1, *su1, su2, *su2);
        break;
    }
    return res;
}

int metadata_parse(char *basedir, uint32_t type)
{
    char path[256];
    int fd;

    snprintf(path, sizeof(path), "%s/metadata.bin", basedir);
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("Fail to open %s\n", path);
        return fd;
    }

    struct metadata *p = (struct metadata *)faddr(fd);
    if (!p) {
        printf("Invalid metadata address\n");
        return -1;
    }

    for (; p->type; p++) {
        if ((type == (uint32_t)-1) || (p->type == type)) {
            switch (p->type) {
            case TYPE_VCMD:
                vdec_dbg("Restore %s to %p\n", p->name, vcmd_buf);
                snprintf(path, sizeof(path), "%s/%s", basedir, p->name);
                vcmd_len = restore_test_file(path, vcmd_buf) / 8;
                vcmd_addr_hi = (uint32_t)(((uintptr_t)vcmd_buf >> 32) & 0xffffffff);
                vcmd_addr_lo = (uint32_t)(((uintptr_t)vcmd_buf >> 0 ) & 0xffffffff);
                break;
            case TYPE_STRM_IN:
                vdec_dbg("Restore %s to %p\n", p->name, p->addr);
                snprintf(path, sizeof(path), "%s/%s", basedir, p->name);
                restore_test_file(path, p->addr);
                break;
            case TYPE_STRM_OUT:
                vdec_dbg("Dump %p to %s\n", p->addr, p->name);
                dump_outdata_info(basedir, p->name, p->addr, p->len);
                break;
            case TYPE_FLUSH:
                vdec_dbg("Memset %p to zero, len=%u\n", p->addr, p->len);
                memset(p->addr, 0, p->len);
                break;
            default:
                break;
            }
        }
    }

    close(fd);
    return 0;
}

static volatile uint32_t g_vdec_done = 0;
static bool g_int_test = false;

static int vdec_irq_handler(int irq, void *args)
{
    uint32_t stat = MA_INW(VC9000D_BASE+0X44);

    vdec_dbg("Enter %s, stat %x\n", __func__, stat);

    MA_OUTW(VC9000D_BASE+0X44, stat);
    if (stat & 0x1)
        g_vdec_done++;
    return 0;
}
static void vdec_request_irq(void)
{
    request_irq(C_VDEC_IRQn, vdec_irq_handler, "vdec_irq", NULL);
    request_irq(C_PP_IRQn, vdec_irq_handler, "pp_irq", NULL);
}

static ssize_t restore_test_file(char *file_name, void *dst)
{
    int fd;
    int ret;
    ssize_t file_len;

    if (!file_name || !dst)
        return -1;

    fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        printf("Fail to open %s\n", file_name);
        return fd;
    }

    file_len = flen(fd);
    ret = read(fd, dst, file_len);
    if (ret < 0) {
        printf("Fail to read %s\n", file_name);
        close(fd);
        return -1;
    }

    close(fd);

    itcs_dcache_flush_range((phys_addr_t)dst, file_len);

    return file_len;
}

static int dump_outdata_info(char *basedir, char *file_name, void *dst, uint32_t len)
{
    int i = outdata_info_index;
    int fd;
    char path[256];

    if (!basedir || !file_name || outdata_info_index >= ARRAY_SIZE(outdata_info))
        return -1;

    snprintf(path, sizeof(path), "%s/%s", basedir, file_name);

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("Fail to open %s\n", file_name);
        return fd;
    }


    snprintf(outdata_info[i].name, sizeof(outdata_info[i].name), "%s", file_name);
    outdata_info[i].src = (void *)faddr(fd);
    outdata_info[i].dst = dst;
    outdata_info[i].len = len;

    outdata_info_index++;

    close(fd);

    return 0;
}

static void vc9000d_config(bool init, bool start)
{
    if (init) {
        //printf("vcmd_addr_hi=%08x, vcmd_addr_lo=%08x\n", vcmd_addr_hi, vcmd_addr_lo);
        MA_OUTW(VC9000D_BASE+0X40,0X4);			//initial all register and bus of hw
        MA_OUTW(VC9000D_BASE+0X40,0X0); 			//stop vc9000d
        MA_OUTW(VC9000D_BASE+0X44,0Xffffffff);		//clear all interrupt	
        MA_OUTW(VC9000D_BASE+0X5c,0X100000);		//max burst length is 16
        MA_OUTW(VC9000D_BASE+0X50,vcmd_addr_lo);
        MA_OUTW(VC9000D_BASE+0X54,vcmd_addr_hi);			//high 32 bit address of command buffer
        MA_OUTW(VC9000D_BASE+0X58,(uint32_t)vcmd_len);
        MA_OUTW(VC9000D_BASE+0X60,0X1);			//buffer counter	
        MA_OUTW(VC9000D_BASE+0X64,0);			//gate normal init from ip to cpu,no gate abnromal init	
        MA_OUTW(VC9000D_BASE+0X48,0Xffffffff);		//enable all init	
        MA_OUTW(VC9000D_BASE+0X80,0X8010428);		//axife_config
        MA_OUTW(VC9000D_BASE+0X84,0X1);			//axife_config
        MA_OUTW(VC9000D_BASE+0X88,0X8010428);		//axife_config
        MA_OUTW(VC9000D_BASE+0X8c,0X2);			//axife_config
        MA_OUTW(VC9000D_BASE+0X90,0X801042c);		//axife_config 	
        MA_OUTW(VC9000D_BASE+0X94,0X0);			//axife_config
        MA_OUTW(VC9000D_BASE+0X98,0X10000000);		//axife_config
    }

    if (start)
        MA_OUTW(VC9000D_BASE+0X40,0X281);			//hw begin initial
}

static int frame_test(char *testdir, int frames)
{
    char basedir[128];
    int ret = 0;

    vdec_dbg("IP Base=0x%08x\n", VC9000D_BASE);

    if (!testdir || frames < 0)
        return -1;

    if (!g_inited && !g_int_test) {
        vdec_request_irq();
        g_inited = true;
    }

    g_perf_cycle = 0;

    for (int i = 0; i < frames; i++) {
        vdec_dbg("\n\nframe%d begin!\n", i);
        memset(outdata_info, 0, sizeof(outdata_info));
        outdata_info_index = 0;

        snprintf(basedir, sizeof(basedir), "%s%d", testdir, i);
        ret = metadata_parse(basedir, -1);
        if (ret < 0)
            continue;

        vc9000d_config(true, true);

        if (!g_int_test) {
#ifdef HWMON_TEST
            udelay(2000);
            hwmon_main(hwmon_argc, hwmon_argv);
#endif

            itcs_hwmon_print_one_info(0, 0);

            while (!g_vdec_done) {}
            itcs_dcache_invalid();

            g_vdec_done = 0;

            g_perf_cycle += MA_INW(VC9000D_BASE+0x8fc);

            vdec_dbg("[vdec] cycle count: cur(%u), total(%u)\n", MA_INW(VC9000D_BASE+0x8fc), g_perf_cycle);
#ifndef CONFIG_COMPILE_RTL
            // udelay(1000 * 1000);
#endif

            vdec_dbg("frame%d finish!\n\n", i); 

            for (struct outdata *p = outdata_info; p->len; p++) {
#if !defined(VDEC_RTL_NOCMP)
                if (vdec_memcmp(p->dst, p->src, p->len)) {
                    soc_dump((uint64_t)p->dst, p->len);
                    ret = -1;
                    vdec_dbg("Compare %s Bad\n", p->name);
                } else {
                    vdec_dbg("Compare %s Good\n", p->name);
                }
#elif defined(CONFIG_COMPILE_RTL)
                (void)vdec_memcmp;
                vdec_dbg("Dump %s\n start\n", p->name);
                soc_dump((uint64_t)p->dst, p->len);
                vdec_dbg("Dump %s\n end\n", p->name);
#endif
            }
        }
    }

    return ret;
}

extern int load_file(const char *path, void *dst);

int h264_test(int case_index, int frame)
{
    int ret;
    char basedir[128];

    snprintf(basedir, sizeof(basedir), "rtlfs-h264_h264@%d.bin", case_index);
    //if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
    //    printf("Fail to load %s\n", basedir);
    //    return -1;
    //}

    snprintf(basedir, sizeof(basedir), "vdec/h264_h264@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    printf("\nTest h264_h264@%d %s\n", case_index, ret ? "Failed" : "Pass");
    return 0;
}

int h265_test(int case_index, int frame)
{
    int ret;
    char basedir[128];

    snprintf(basedir, sizeof(basedir), "rtlfs-hevc_hevc@%d.bin", case_index);
    if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
        printf("Fail to load %s\n", basedir);
        return -1;
    }

    snprintf(basedir, sizeof(basedir), "vdec/hevc_hevc@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    printf("\nTest hevc_hevc@%d %s\n", case_index, ret ? "Failed" : "Pass");
    return 0;
}

int jpeg_test(int case_index, int frame)
{
    int ret;
    char basedir[128];

    snprintf(basedir, sizeof(basedir), "rtlfs-jpeg_jpeg@%d.bin", case_index);
    if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
        printf("Fail to load %s\n", basedir);
        return -1;
    }

    snprintf(basedir, sizeof(basedir), "vdec/jpeg_jpeg@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    printf("\nTest jpeg_jpeg@%d %s\n", case_index, ret ? "Failed" : "Pass");
    return 0;
}

int pp_test(int case_index, int frame)
{
    int ret;
    char basedir[128];

    snprintf(basedir, sizeof(basedir), "rtlfs-pponly@%d.bin", case_index);
    if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
        printf("Fail to load %s\n", basedir);
        return -1;
    }

    snprintf(basedir, sizeof(basedir), "vdec/pponly@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    printf("\nTest pponly@%d %s\n", case_index, ret ? "Failed" : "Pass");
    return 0;
}


int int_test(int case_index, int frame)
{
    int ret;
    char basedir[128];
    volatile uint32_t *swreg1 = (volatile uint32_t *)0xc6000804;

    g_int_test = true;

    snprintf(basedir, sizeof(basedir), "rtlfs-int@%d.bin", case_index);
    if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
        printf("Fail to load %s\n", basedir);
        return -1;
    }

    snprintf(basedir, sizeof(basedir), "vdec/int@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);

    // udelay(5);

    switch (case_index)
    {
    case 0:
        while ((*swreg1 & 0x00001100) != 0x00001100) { }
        MA_OUTW(VC9000D_BASE+0X804, 0X21);
        while ((*swreg1 & 0x00000f00) != 0x00000900) { }
        ret = 0;
        break;
    case 1:
        while ((*swreg1 & 0x0000f000) != 0x00002000) { }
        ret = 0;
        break;
    case 2:
        while ((*swreg1 & 0x000f0000) != 0x00040000) { }
        ret = 0;
        break;
    case 3:
        while ((*swreg1 & 0x00f00000) != 0x00200000) { }
        ret = 0;
        break;
    default:
        ret = -1;
        break;
    }
    printf("\nTest int@%d %s\n", case_index, ret ? "Failed" : "Pass");
    return 0;
}

int jpeg_perf_test(int case_index, int frame)
{
    char basedir[128];
    int ret, fps = 0;
    uint64_t clk = itcs_module_get_clock(CPU, "vdec");

    // snprintf(basedir, sizeof(basedir), "rtlfs-jpeg_jpeg@%d.bin", case_index);
    // if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
    //     printf("Fail to load %s\n", basedir);
    //     return -1;
    // }

    snprintf(basedir, sizeof(basedir), "vdec/jpeg_jpeg@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    fps = clk / (uint64_t)(g_perf_cycle / (uint32_t)frame);

    printf("\n\nJPEG perfermance test %s, %d fps\n\n", ret ? "Failed" : "Pass", fps);
    return fps;
}

int h264_perf_test(int case_index, int frame)
{
    char basedir[128];
    int ret, fps = 0;
    uint64_t clk = itcs_module_get_clock(CPU, "vdec");

    // snprintf(basedir, sizeof(basedir), "rtlfs-h264_h264@%d.bin", case_index);
    // if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
    //     printf("Fail to load %s\n", basedir);
    //     return -1;
    // }

    snprintf(basedir, sizeof(basedir), "vdec/h264_h264@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    fps = clk / (uint64_t)(g_perf_cycle / (uint32_t)frame);

    printf("\n\nH264 perfermance test %s, %d fps\n\n", ret ? "Failed" : "Pass", fps);
    return fps;
}

int h265_perf_test(int case_index, int frame)
{
    char basedir[128];
    int ret, fps = 0;
    uint64_t clk = itcs_module_get_clock(CPU, "vdec");

    // snprintf(basedir, sizeof(basedir), "rtlfs-hevc_hevc@%d.bin", case_index);
    // if (load_file(basedir, (void *)RTLFS_START_ADDR) < 0) {
    //     printf("Fail to load %s\n", basedir);
    //     return -1;
    // }

    snprintf(basedir, sizeof(basedir), "vdec/hevc_hevc@%d/testdata/frame", case_index);

    ret = frame_test(basedir, frame);
    fps = clk / (uint64_t)(g_perf_cycle / (uint32_t)frame);

    printf("\n\nH265 perfermance test %s, %d fps\n\n", ret ? "Failed" : "Pass", fps);
    return fps;
}

void vdec_test_all(void)
{
    struct {
        char *name;
        int case_index;
        int frame;
        int (*func)(int, int);
    } vdec_test_cases[] = {
        {
            .name = "H264 Decode",
            .case_index = 4,
            .frame = 5,
            .func = h264_perf_test,
        }, {
            .name = "H265 Decode",
            .case_index = 4,
            .frame = 5,
            .func = h265_perf_test,
        }, {
            .name = "JPEG Decode",
            .case_index = 200,
            .frame = 1,
            .func = jpeg_perf_test,
        }, {
            .name = "H264+PP Decode",
            .case_index = 400,
            .frame = 5,
            .func = h264_perf_test,
        }, {
            .name = "H265+PP Decode",
            .case_index = 300,
            .frame = 5,
            .func = h265_perf_test,
        }, {
            .name = "JPEG+PP Decode",
            .case_index = 210,
            .frame = 1,
            .func = jpeg_perf_test,
        },
        { /* sentinel */ }
    }, *pt;

    struct {
        int64_t bpll;
        int64_t vdec;
    }  freq_lists[] = {
        { 2376000000, 594000000 },
        // { 1968000000, 656000000 },
        // { 2112000000, 704000000 },
        // { 2256000000, 752000000 },
        // { 2376000000, 792000000 },
        // { 1704000000, 852000000 },
        // { 1800000000, 900000000 },
        // { 2016000000, 100800000 },
        // { 2112000000, 105600000 },
        // { 2208000000, 110400000 },
        { /* sentinel */ }
    }, *pf;

    //if (load_file("rtlfs-perf_all.bin", (void *)RTLFS_START_ADDR) < 0) {
    //    printf("Fail to load %s\n", "rtlfs-perf-all.bin");
    //    return;
    //}

    for (pf = &freq_lists[0]; pf->bpll; pf++) {
        puts("\n\n======================================>");
        itcs_pll_set_clock(CPU, "bpll", pf->bpll, 0);
        itcs_module_set_clock(CPU, "vdec", "bpll", pf->vdec, 0);
        printf("vdec clock: %d\n", itcs_module_get_clock(CPU, "vdec"));
        for (pt = &vdec_test_cases[0]; pt->name; pt++) {
            printf("Start %s Test\n", pt->name);
            pt->func(pt->case_index, pt->frame);
        }
        puts("<======================================\n\n");
    }
}

static uint8_t uni_vcmd_buf[5][VCMD_BUF_LEN] __attribute__((aligned(128)));
static bool g_vdec_busy = false;

int vdec_h264_perf_test_init(void *para)
{
    int ret = -1;
    char basedir[128];
    int case_index = 400;

    if (!g_inited) {
        itcs_vdec_init(VDEC_DEFAULT_FREQ);
        vdec_request_irq();
        g_inited = true;
    }

    for (int i = 0; i < 5; i++) {
        snprintf(basedir, sizeof(basedir), "vdec/h264_h264@400/testdata/frame%d", i);
        ret = metadata_parse(basedir, -1);
        if (ret < 0)
            return ret;
        
        memcpy(&uni_vcmd_buf[i], vcmd_buf, sizeof(vcmd_buf));
    }

    itcs_dcache_flush_range((phys_addr_t)uni_vcmd_buf, sizeof(uni_vcmd_buf));
    g_perf_cycle = 0;
    g_vdec_done = 0;
    g_vdec_busy = false;

    return 0;
}


int vdec_h264_perf_test_start(int index)
{
    if (index < 0)
        index = 0;

    if (index >= 5)
        index %= 5;

    if (!g_vdec_busy) {
        vcmd_addr_hi = (uint32_t)(((uintptr_t)&uni_vcmd_buf[index] >> 32) & 0xffffffff);
        vcmd_addr_lo = (uint32_t)(((uintptr_t)&uni_vcmd_buf[index] >> 0 ) & 0xffffffff);
        vc9000d_config(true, true);
        g_vdec_busy = true;
    }

    return 0;
}

int vdec_h264_perf_test_get_status(void)
{
    if (g_vdec_done) {
        g_vdec_done = 0;
        g_vdec_busy = false;
        return 1;
    }

    return 0;
}

int uni_self_test(void)
{
    vdec_h264_perf_test_init(NULL);
    for (int i = 0; i < 5;) {
        vdec_h264_perf_test_start(i);
        if (vdec_h264_perf_test_get_status()) {
            vdec_dbg("%s frame%d Done\n", __func__, i);
            i++;
        }
    }

    return 0;
}
