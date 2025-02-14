#include <common.h>
#include <cache.h>
#include <irq.h>
#include <rtlfs.h>
#include <div64.h>
#include <vdec.h>

static volatile unsigned long VC9000D_BASE = 0xc6100000;
// #define VDEC_DEBUG

#ifdef VDEC_DEBUG
#define vdec_dbg(...) printf(__VA_ARGS__)
#else
#define vdec_dbg(...)
#endif


#define MA_OUTW(a,b) writel((b), (a))
#define MA_INW(a) readl((a))

static ssize_t restore_test_file(char *file_name, void *dst);
static int dump_outdata_info(char *basedir, char *file_name, void *dst, uint32_t len);

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
static volatile uint32_t vcmd_addr_hi, vcmd_addr_lo;
static ssize_t vcmd_len;

static struct outdata outdata_info[8] = { 0 };
static int outdata_info_index = 0;

static volatile uint32_t g_perf_cycle;
static bool g_inited = false;


static int metadata_parse(char *basedir, uint32_t type)
{
    char path[256];

#if 1
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
#else
    struct metadata *p = metadata_demo;
#endif
    for (; p->type; p++) {
        if ((type = (uint32_t)-1) || (p->type == type)) {
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

    itcs_dcache_flush();
    close(fd);
    return 0;
}

static volatile uint32_t g_vdec_done = 0;

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
    // request_irq(C_VDEC_IRQn, vdec_irq_handler, "vdec_irq", NULL);
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

static uint8_t uni_vcmd_buf[5][VCMD_BUF_LEN] __attribute__((aligned(128)));
static bool g_vdec_busy = false;

int vdec_pp_h264_perf_test_init(void *para)
{
    int ret = -1;
    char basedir[128];

    if (!g_inited) {
        itcs_vdec_init();
        vdec_request_irq();
        g_inited = true;
    }

    for (int i = 0; i < 5; i++) {
        snprintf(basedir, sizeof(basedir), "vdec_pp/h264_h264@408/testdata/frame%d", i);
        ret = metadata_parse(basedir, -1);
        if (ret < 0)
            return ret;
        
        memcpy(&uni_vcmd_buf[i], vcmd_buf, sizeof(vcmd_buf));
    }

    itcs_dcache_flush();
    g_perf_cycle = 0;
    g_vdec_done = 0;
    g_vdec_busy = false;

    return 0;
}


int vdec_pp_h264_perf_test_start(int index)
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

int vdec_pp_h264_perf_test_get_status(void)
{
    if (g_vdec_done) {
        g_vdec_done = 0;
        g_vdec_busy = false;
        return 1;
    }

    return 0;
}

